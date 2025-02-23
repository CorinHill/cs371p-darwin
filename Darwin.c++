#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include "Darwin.h"

void World::addCreature(Creature& c, unsigned y, unsigned x) {
  try {
    _g.at(x + y*_xsize) = _c.size() + 1; // Want to do this first so I don't add the creature if the position is invalid. However, I use 0 as the empty notation, so add 1...
    _c.push_back(c);
  } catch (std::out_of_range e) {
  }
}


void World::round() {
  std::unordered_set<int> acted;
  for(unsigned j = 0; j < _ysize; ++j) {
    for(unsigned i = 0; i < _xsize; ++i) {
      int curr_index = i + j*_xsize;
      int g = _g.at(curr_index);
      if (g && !acted.count(g) ) {
        acted.insert(g);
        Creature& c = _c.at( g - 1 );
        int ahead = WALL;
        Creature* o = NULL;
        int next_index, bound;
        switch(c.facing()) {
        case NORTH: next_index = curr_index - _xsize; bound =                  (curr_index<(int)_xsize)?1:0; break;
        case EAST : next_index = curr_index + 1;      bound = (curr_index%(int)_xsize == (int)_xsize-1)?1:0; break;
        case SOUTH: next_index = curr_index + _xsize; bound = (curr_index>=(int)_xsize*((int)_ysize-1))?1:0; break;
        case WEST : next_index = curr_index - 1;      bound =             (curr_index%(int)_xsize == 0)?1:0; break;
        }
        if( !bound ) {
          int tmp = _g.at(next_index);
          if( tmp ) {
            ahead = CREATURE;
            o     = &_c.at(tmp - 1);
          } else
            ahead = EMPTY;
        }
        int action = c.act( ahead, (o)?o->species():c.species() );
        if( action == 1 ) {
          if( ahead == EMPTY ) {
            _g[next_index] = _g[curr_index];
            _g[curr_index] = 0;
          }
        } else if ( action == 2 ) {
          if( ahead == CREATURE && o ) {
            o->infect( c.species() );
          }
        }
      }
    }
  }

/*  std::vector<int>::iterator b = _g.begin(), e = _g.end();
  int i = 0;
  while(b != e) {
    if(*b) {
      Creature& c = _c.at(*b - 1);
      Direction d = c.facing();
      Creature* o = NULL;
      int ahead = WALL;

      int index;
      switch(d) {
      case NORTH: index = i-1     ; break;
      case SOUTH: index = i+1     ; break;
      case EAST : index = i+_ysize; break;
      case WEST : index = i-_ysize; break;
      }
      if( index > 0 && index < (int)_g.size() ) {
        int thisisdumb = _g.at(index);
        if(thisisdumb) {
          ahead = CREATURE;
          o     = &_c.at(thisisdumb - 1);
        } else
          ahead = EMPTY;
      }

      int action = c.act( ahead, (o)?o->species():c.species() );
      if(action < 0) {
        //Invalid species or creature
      } else if (action == 1) {
        if( ahead == EMPTY ) { //Should be redundant
          _g[index] = *b;
          *b = 0;
        } //else?
      } else if (action == 2) {
        if( ahead == CREATURE && o != NULL) //Hopefully redundant
          (*o).infect( c.species() );
      } else { //action should be 0, creature turned or did nothing
        assert(action==0);
      }
      printf("%c\n",c.species().name);
    } else printf("%c\n",'.');
    ++b; ++i;
  }
*/
}

void World::print(std::ostream& o) {
  o << ' ' << ' ';
  for(unsigned i = 0; i < _xsize; ++i)
    o << i%10;
  o << std::endl;
  for(unsigned j = 0; j < _ysize; ++j) {
    o << j%10 << ' ';
    for(unsigned i = 0; i < _xsize; ++i) {
      int index = _g.at(i + j*_xsize);
      if( index )
         _c.at(index - 1).print(o);
      else
         o << '.';
    }
    o << std::endl;
  }
}

void Species::addInstruction(Line l) {
  program.push_back(l);
}
void Species::addInstruction(Instruction i, int t) {
  Line l = {i, t};
  addInstruction(l);
}

Line Species::seeInstruction(unsigned i) {
  return program.at(i);
}

void Species::print(std::ostream& o) {
  o << name;
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

int Creature::act(int ahead, Species* other) {
  int action = -1;
  while(action < 0) {
    Line line = _sp->seeInstruction(_pc);
    ++_pc;
    switch(line.ins) {
    case HOP   : action = 1; break;
    case LEFT  : action = 0;
      turn_l(); break;
    case RIGHT : action = 0;
      turn_r(); break;
    case INFECT: action = 0;
      if(ahead==CREATURE && other!=_sp) action = 2;
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
      if(ahead == CREATURE && other!=_sp) _pc = line.target;
      break;
    case GO    :
      _pc = line.target;
      break;
    }
  }
  return action;
}

Direction Creature::facing() const{
  return _dir;
}

Species* Creature::species() const{
  return _sp;
}

void Creature::infect(Species* other) {
  _sp = other;
  _pc = 0;
}

void Creature::print(std::ostream& o) {
  _sp->print(o);
}
