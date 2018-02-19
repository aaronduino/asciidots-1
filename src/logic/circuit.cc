#include "circuit.h"
#include <fstream>
#include <set>
#include "../io/io.h"
#include "tiles/tiles.h"
#include <iostream>

void Circuit::load_circuit(const std::string &path){
  body = std::vector<std::string>(); // clear body

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

  parse_body(); // init body
}

char Circuit::get_tile(const int32_t &y, const int32_t &x) const{
  if(y >= (int32_t)height || y < 0) // vertically out of bounds, return blank
    return ' ';

  std::string row = body[y]; // pull the row, horizontal bounds vary
  if(x >= (int32_t)row.length() || x < 0) // horizontally out of bounds
    return ' ';

  return row[x]; // within bounds, return the actual character
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
  /* find a direction for the spawned dot to point
     if multiple possible exits, use first in clock order */
  Vec2 compass[4] = { Vec2(0, -1), Vec2(1, 0), Vec2(0, 1), Vec2(-1, 0) };
  std::vector<Vec2> exits;
  for(int i = 0; i < 4; i++){
    // prevent underflow
    if((x == 0 && compass[i].x < 0) || (y == 0 && compass[i].y < 0))
      continue;

    char tile = get_tile(y + compass[i].y, x + compass[i].x);

    if(tile == ' ' || tile == '.') // empty space isn't an exit
      continue;

    if(valid_travel(tile, compass[i])) // if we can legally leave this way
      exits.push_back(compass[i]); // it's an exit
  }

  if(exits.size() > 0) // gotta be at least one exit
    dots.push_back(new Dot(Vec2(x, y), exits[0]));
}

void Circuit::parse_body(){
  std::set<char> flowChars = { '<', '>', '^', 'v', '\\', '/' };
  std::set<char> readChars = { '#', '@' };
  std::set<char> operators = { '+','-','*','/','%','&','|','^','=','!' };

  // step through all tiles in reading order
  for(uint32_t y = 0; y < height; y++) for(uint32_t x = 0; x < width; x++){
    char tile = get_tile(y, x); // convenience
    Vec2 pos(x, y);

    if(tile == '.'){ // spawns
      spawn_dot(y, x);
    }

    else if(
      get_tile(y, x-1) == '{' && // horizontal operators
      get_tile(y, x+1) == '}' &&
      operators.find(tile) != operators.end()){
        tiles.push_back(new Operator(pos, tile, false));
    }
    else if(
      get_tile(y, x-1) == '[' && // vertical operators
      get_tile(y, x+1) == ']' &&
      operators.find(tile) != operators.end()){
        tiles.push_back(new Operator(pos, tile, true));
    }

    else if(tile == '~') // branches
      tiles.push_back(new Branch(pos));

    else if(flowChars.find(tile) != flowChars.end()) // flow chars
      tiles.push_back(new Flow(pos, tile));

    else if(tile == '*') // clones
      tiles.push_back(new Clone(pos));

    else if(readChars.find(tile) != readChars.end()) // read chars
      tiles.push_back(new Read(pos, tile));

    else if(tile == '$') // write
      tiles.push_back(new Write(pos));
  }
}

bool Circuit::step(){
  bool activity = false;

  for(uint32_t i = 0; i < dots.size(); i++){ // step each dot
    // don't step disabled or skip dots
    if(dots[i]->state == STATE_DISABLED || dots[i]->state == STATE_SKIP)
      continue;

    activity = true;

    dots[i]->move(); // move the dot forward

    // what tile did it land on
    char tile = get_tile(dots[i]->pos.y, dots[i]->pos.x);

    process_io(dots[i], tile); // handle reading/writing states

    // don't process the tile if it did IO this step
    if(dots[i]->state == STATE_READVALUE || dots[i]->state == STATE_READID)
      continue;

    if(tile == ' ' || !valid_travel(tile, dots[i]->dir)){ // check for deaths
      dots[i]->state = STATE_DEAD;
      continue;
    }

    // find an active tile at this position TODO: improve this search
    for(uint32_t j = 0; j < tiles.size(); j++){
      if(tiles[j]->pos == dots[i]->pos)
        tiles[j]->add_dot(dots[i]); // pass the dot to the tile here
    }
  }

  post_step(); // perform post-step cleanups

  return activity;
}

void Circuit::post_step(){
  // post-step state tasks
  for(uint32_t i = 0; i < dots.size(); i++){
    if(dots[i]->state == STATE_DEAD){ // if the dot died this step, remove it
      dots.erase(dots.begin() + i);
      i--; // elements all moved down a space, so step back
    }

    // spawn clones if necessary
    else if(dots[i]->state == STATE_CLONE){
      // spawn two dots, turn one left, one right, have them skipped
      for(int j = 0; j < 2; j++){
        dots.push_back(new Dot(*dots[i]));
        dots.back()->state = STATE_SKIP;
        dots.back()->turn(j*2 - 1); // 0 = -1, 1 = 1
      }
      dots[i]->state = STATE_NONE; // clones spawned, no more please
    }

    else if(dots[i]->state == STATE_SKIP) // remove skip states
      dots[i]->state = STATE_NONE; // they're only effective within their step
  }
}

void Circuit::collect_inputs(){
  for(uint32_t i = 0; i < dots.size(); i++){
    if(dots[i]->state == STATE_INPUT){
      dots[i]->value = input();
      dots[i]->state = STATE_NONE;
    }
  }
}

void Circuit::process_io(Dot *dot, const char &tile){
  std::set<int> readStates = {
    STATE_HASH, STATE_AT, STATE_READVALUE, STATE_READID
  };

  // reading
  if(readStates.find(dot->state) != readStates.end()){
    bool isDigit = tile >= '0' && tile <= '9';   // is this tile a digit

    if(isDigit){ // only clear values and start a read if tile is a digit
      if(dot->state == STATE_HASH){
        dot->state = STATE_READVALUE;
        dot->value = 0;
      }
      else if(dot->state == STATE_AT){
        dot->state = STATE_READID;
        dot->id = 0;
      }

      // if we're in a READVALUE/READID state, push this digit onto value/id
      if(dot->state == STATE_READVALUE){
        dot->value *= 10;
        dot->value += tile - '0';
      }
      else if(dot->state == STATE_READID){
        dot->id *= 10;
        dot->id += tile - '0';
      }
    }
    else if(tile == '?')
      dot->state = STATE_INPUT;
    else // tile not a digit, disable any reading modes
      dot->state = STATE_NONE;
  }
  
  // writing
  else if(dot->state == STATE_WRITE){
    if(tile == '#')
      output(std::to_string(dot->value));
    else if(tile == '@')
      output(std::to_string(dot->id));

    dot->state = STATE_NONE;
  }
}