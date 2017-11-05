#include "operator.h"

Operator::Operator(Point position, char opChar, bool horizontal){
  this->position = position;
  this->opChar = opChar;
  this->horizontal = horizontal;
}

void Operator::AddDot(Dot &dot){
  if(!holding){
    heldDot = &dot;
    holding = true;
  }
  else{
    // both dots were aligned same, kill newest arrival
    if(heldDot->IsHorizontal() == dot.IsHorizontal())
      dot.deathMarked = true;
    else{
      // decide which dot is primary and secondary
      Dot primary = *heldDot;
      Dot secondary = dot;
      if(dot.IsHorizontal() == horizontal){
        primary = dot;
        secondary = *heldDot;
      }

      primary.value = this->Operate(primary.value, secondary.value);
      primary.enabled = true;
      secondary.deathMarked = true;
    }
  }
}

double Operator::Operate(double lhs, double rhs){
  switch(opChar){
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    default:
      return lhs;
  }
}
