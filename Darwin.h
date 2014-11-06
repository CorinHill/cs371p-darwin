


#ifndef __DARWIN_H__
#define __DARWIN_H__

#include <vector>
#include <stdexcept>
#include <cassert>


#define EMPTY    0
#define WALL     1
#define CREATURE 2
enum Direction   {NORTH, SOUTH, EAST, WEST};
enum Instruction {HOP, LEFT, RIGHT, INFECT, IF_E, IF_W, IF_R, IF_N, GO};
struct Line {
  Instruction ins;
  int target;
};
class World; class Species; class Creature;


class World {
private:
  std::vector<int>      _g;
  std::vector<Creature> _c;
  size_t _xsize;
  size_t _ysize;
public:
  World(size_t y = 0, size_t x = 0) :
    _g(x*y), _c(),  _xsize(x), _ysize(y) { }
  void addCreature(Creature& c, unsigned x, unsigned y);
  void round();
  void print(std::ostream& o);
};

class Species {
private:
  std::vector<Line> program;
  char              name;
public:
  Species(char c = '?') :
    program(), name(c) {}
  void addInstruction(Line l);
  void addInstruction(Instruction i, int t);
  Line seeInstruction(unsigned i);
  void print(std::ostream& o);
};

class Creature {
private:
  Species&  _sp;
  unsigned  _pc;
  Direction _dir;

  void turn_l();
  void turn_r();
public:
  Creature(Species& sp, Direction dir = NORTH) :
    _sp(sp), _pc(0), _dir(dir) {}
  int       act(int ahead, Species* other);
  Direction facing() const;
  Species& species() const;
  void      infect(Species& other);
  void print(std::ostream& o);
};

#endif
