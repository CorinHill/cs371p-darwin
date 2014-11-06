#include <cstdio>
#include <cstdlib>
#include "Darwin.h"

void World::addCreature(Creature& c, unsigned x, unsigned y) {
  try {
    _g.at(x + y*_xsize) = _c.size() + 1; // Want to do this first so I don't add the creature if the position is invalid. However, I use 0 as the empty notation, so add 1...
    _c.push_back(c);
  } catch (std::out_of_range e) {
  }
}

void World::round() {
  std::vector<int>::iterator b = _g.begin(), e = _g.end();
  while(b != e) {
    if(*b) {
      int action = _c.at(*b - 1).act();
      if(action < 0) {
        //Invalid species or creature
      } else if (action == 1) {
        //HOP
      } else if (action == 2) {
        //INFECT
      } else { //action should be 0, creature turned
        assert(action==0);
      }
    }
    ++b;
  }
}

void World::print(std::ostream& o) {
  o << "  ";
  for(int i = 0; i < _xsize; ++i)
    o << i%10;
  o << endl;
  for(int j = 0; j < _ysize; ++j) {
    o << j%10 << ' ';
    for(int i = 0; i < _xsize; ++i)
      o << _c.at(_g.at(i + j*_xsize) - 1).cname();
    o << endl;
  }
}

void Species::addInstruction(Line l) {
  program.push_back(l);
}

Line Species::seeInstruction(unsigned i) throw std::out_of_range{
  return program.at(i);
}

void Creature::turn_l() {
  switch(_dir) {
  case NORTH: _dir = WEST; break;
  case SOUTH: _dir = EAST; break;
  case EAST: _dir = NORTH; break;
  case WEST: _dir = SOUTH; break;
  }
}

void Creature::turn_r() {
  switch(_dir) {
  case NORTH: _dir = EAST; break;
  case SOUTH: _dir = WEST; break;
  case EAST: _dir = SOUTH; break;
  case WEST: _dir = NORTH; break;
  }
}

int Creature::act(int ahead, Species* other) throw std::out_of_range {
  int action = -1;
  while(action < 0) {
    Line line = _sp.seeInstruction(_pc);
    ++_pc;
    switch(line.ins) {
    case HOP   : action = 1; break;
    case LEFT  : action = 0;
      turn_l(); break;
    case RIGHT : action = 0;
      turn_r(); break;
    case INFECT: action = 0;
      if(ahead==CREATURE && other==&_sp) action = 2;
      break;
    case IF_E  :
      if(ahead == EMPTY) _pc = line.target;
      break;
    case IF_W  :
      if(ahead == WALL) _pc = line.target;
      break;
    case IF_R  :
      if(std::rand()&1) _pc = line.target;
      break;
    case IF_N  :
      if(ahead == CREATURE) _pc = line.target;
      break;
    case GO    :
      _pc = line.target;
      break;
    }
  }
  return action;
}

Direction Creature::facing() {
  return _dir;
}

void Creature::infect(Species& other) {
  _sp = other;
  _pc = 0;
}
