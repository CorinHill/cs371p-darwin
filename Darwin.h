


#ifndef __DARWIN_H__
#define __DARWIN_H__

#include <vector>
#include <stdexcept>
#include <cassert>


#define EMPTY    0
#define WALL     1
#define CREATURE 2
enum Direction   {NORTH, SOUTH, EAST, WEST};
enum Instruction {HOP, LEFT, RIGHT, INFECT, IF_E, IF_W, IF_R, IF_N, GO}
struct Line {
  Instruction ins;
  int target;
}
class World, Species, Creature;


class World {
private:
  std::vector<int>      _g;
  std::vector<Creature> _c;
  size_t _x;
  size_t _y;
public:
  World(size_t x = 0, size_t y = 0) :
    _g(x*y), _c(),  _x(x), _y(y) {
  }
  void addCreature(const Creature& c, unsigned x, unsigned y);
  void round();
  void print(ostream& o);
};

class Species {
private:
  std::vector<Line> program;
public:
  void addInstruction(Line l);
  void seeInstruction(unsigned i);
};

class Creature {
private:
  Species&  _sp;
  unsigned  _pc;
  Direction _dir;

  void turn_l();
  void turn_r();
public:
  Creature(const Species& sp, Direction dir = NORTH) :
    _sp(sp), _pc(0), _dir(dir) {
  }
  int       act(int ahead, const Species& other);
  Direction facing() const;
  void      infect();
};

#endif
