#include "branch.h"
#include "../dot.h"

Branch::Branch(const Vec2 &pos): Tile(pos) {}

void Branch::add_dot(Dot *dot){
  dot->state = STATE_DISABLED; // capture this dot here

  if(dot->dir.x == 0)
    secondary.push(dot); // vertical
  else
    primary.push(dot); // horizontal

  while(primary.size() > 0 && secondary.size() > 0){
    auto p = primary.back(); // convenience
    auto s = secondary.back();

    p->state = STATE_SKIP; // release primary but don't move until next step
    s->state = STATE_DEAD; // kill secondary

    if(s->value == 0) // if secondary (vertical) value is 0
      p->dir = s->dir; // redirect primary to secondary's direction

    primary.pop();
    secondary.pop();
  }
}