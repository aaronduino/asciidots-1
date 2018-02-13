#include "circuit.h"
#include <fstream>
#include <set>
#include "../io/io.h"
#include "tiles/flow.h"
#include "tiles/clone.h"
#include "tiles/read.h"
#include "tiles/write.h"
#include "tiles/operator.h"
#include "tiles/branch.h"

void Circuit::load_circuit(const std::string &path){
  // clear body
  body = std::vector<std::string>();

  std::ifstream file(path);
  std::string line;
  
  width = height = 0;

  while(getline(file, line)){
    body.push_back(line);

    // increase bounds
    height++;
    if(line.length() > width) // use widest
      width = line.length();
  }

  file.close();

  // init body
  parse_body();
}

char Circuit::get_tile(const int64_t &y, const int64_t &x){
  std::string row = body[y];

  // if out of bounds, return ' '
  if(x >= (int64_t)row.length() || x < 0 || y >= (int64_t)height || y < 0)
    return ' ';
  else
    return row[x];
}

// assumes legal travel, returns false if illegal
bool Circuit::valid_travel(const char &tile, const Vec2 &dir){
  // moving vertical, entering a horizontal?
  if(dir.x == 0 && (tile == '-' || tile == '(' || tile == ')'))
      return false;
  // moving horizontal, entering a vertical?
  else if(dir.y == 0 && tile == '|')
    return false;
  else
    return true;
}

void Circuit::spawn_dot(const uint32_t &y, const uint32_t &x){
  // find a direction for the dot to spawn pointing
  Vec2 compass[4] = { Vec2(0, -1), Vec2(1, 0), Vec2(0, 1), Vec2(-1, 0) };
  std::vector<Vec2> exits;
  for(int i = 0; i < 4; i++){
    // prevent underflow
    if((x == 0 && compass[i].x < 0) || (y == 0 && compass[i].y < 0))
      continue;

    char tile = get_tile(y + compass[i].y, x + compass[i].x);

    if(tile == ' ') // empty space isn't an exit
      continue;

    // only an exit if we can legally go this way
    if(valid_travel(tile, compass[i]))
      exits.push_back(compass[i]);
  }

  // only spawn if there's a possible unambiguous exit
  if(exits.size() == 1)
    dots.push_back(new Dot(Vec2(x, y), exits[0]));
}

void Circuit::parse_body(){
  std::set<char> flowChars = { '<', '>', '^', 'v', '\\', '/' };
  std::set<char> readChars = { '#', '@' };
  std::set<char> operators = { '+','-','*','/','%','&','|','^','=','!' };

  // step through all tiles in reading order
  for(uint32_t y = 0; y < height; y++) for(uint32_t x = 0; x < width; x++){
    // this tile
    char tile = get_tile(y, x);
    Vec2 pos(x, y);

    if(tile == '.')
      spawn_dot(y, x);

    else if(
      get_tile(y, x-1) == '{' &&
      get_tile(y, x+1) == '}' &&
      operators.find(tile) != operators.end()){
        tiles.push_back(new Operator(pos, tile, false));
    }
    else if(
      get_tile(y, x-1) == '[' &&
      get_tile(y, x+1) == ']' &&
      operators.find(tile) != operators.end()){
        tiles.push_back(new Operator(pos, tile, true));
    }

    else if(tile == '~')
      tiles.push_back(new Branch(pos));

    else if(flowChars.find(tile) != flowChars.end())
      tiles.push_back(new Flow(pos, tile));

    else if(tile == '*')
      tiles.push_back(new Clone(pos));

    else if(readChars.find(tile) != readChars.end())
      tiles.push_back(new Read(pos, tile));

    else if(tile == '$')
      tiles.push_back(new Write(pos));
  }
}

bool Circuit::step(){
  // step every dot
  for(uint32_t i = 0; i < dots.size(); i++){
    // don't step disabled or skip dots
    if(dots[i]->state == STATE_DISABLED || dots[i]->state == STATE_SKIP)
      continue;

    // take a step
    dots[i]->move();

    // what tile did it land on
    char tile = get_tile(dots[i]->pos.y, dots[i]->pos.x);

    // handle reading/writing states
    process_io(dots[i], tile);

    // don't process the tile if it's for IO
    if(dots[i]->state == STATE_READVALUE || dots[i]->state == STATE_READID)
      continue;

    // check for deaths
    if(tile == ' ' || !valid_travel(tile, dots[i]->dir))
      dots[i]->state = STATE_DEAD;

    // find an active tile at this position TODO: improve this search
    for(uint32_t j = 0; j < tiles.size(); j++){
      if(tiles[j]->pos == dots[i]->pos)
        tiles[j]->add_dot(dots[i]);
    }
  }

  // post step processing
  post_step();

  return true; // activity occurred this step TODO: don't fake this
}

void Circuit::post_step(){
  // post-step state tasks
  for(uint32_t i = 0; i < dots.size(); i++){
    // if the dot died this step, remove it
    // remove dots that died this step
    if(dots[i]->state == STATE_DEAD){
      dots.erase(dots.begin() + i);
      i--;
    }

    // spawn dots for dots that cloned this step
    else if(dots[i]->state == STATE_CLONE){
      // spawn two dots, turn one left, one right, have them skipped
      for(int j = 0; j < 2; j++){
        dots.push_back(new Dot(*dots[i]));
        dots.back()->state = STATE_SKIP;
        dots.back()->turn(j*2 - 1); // 0 = -1, 1 = 1
      }
      dots[i]->state = STATE_NONE;
    }

    // remove skip tags, skips are only for the step they're set within
    else if(dots[i]->state == STATE_SKIP)
      dots[i]->state = STATE_NONE;
  }
}

void Circuit::process_io(Dot *dot, const char &tile){
  std::set<int> readStates = {
    STATE_HASH, STATE_AT, STATE_READVALUE, STATE_READID
  };

  // reading
  if(readStates.find(dot->state) != readStates.end()){
    // is this tile a digit
    bool isDigit = tile >= '0' && tile <= '9';  

    // last tile was # or @. ensures value/id is only cleared if this is a digit
    if(isDigit){
      if(dot->state == STATE_HASH){
        dot->state = STATE_READVALUE;
        dot->value = 0;
      }
      else if(dot->state == STATE_AT){
        dot->state = STATE_READID;
        dot->id = 0;
      }

      // if we're in a READVALUE or READID state, push this digit onto value/id
      if(dot->state == STATE_READVALUE){
        dot->value *= 10;
        dot->value += tile - '0';
      }
      else if(dot->state == STATE_READID){
        dot->id *= 10;
        dot->id += tile - '0';
      }
    }
    else
      dot->state = STATE_NONE;
  }
  // writing
  else if(dot->state == STATE_WRITE){
    if(tile == '#')
      output(std::to_string(dot->value));
    else if(tile == '@')
      output(std::to_string(dot->id));
  }
}