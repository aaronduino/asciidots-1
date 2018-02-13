#include "branch.h"
#include "../dot.h"

Branch::Branch(const Vec2 &pos): Tile(pos){
  this->pos = pos;
}

void Branch::add_dot(Dot *dot){
  dot->state = STATE_DISABLED;

  if(dot->dir.x == 0)
    secondary.push(dot);
  else
    primary.push(dot);

  while(primary.size() > 0 && secondary.size() > 0){
    // just convenient
    auto p = primary.back();
    auto s = secondary.back();

    // release primary, kill secondary
    p->state = STATE_NONE;
    s->state = STATE_DEAD;

    // if secondary's value is 0, transfer its direction
    if(s->value == 0)
      p->dir = s->dir;

    // primary has been released, but don't let it move this step
    p->state = STATE_SKIP;

    // forget them, they're gone
    primary.pop();
    secondary.pop();
  }
}