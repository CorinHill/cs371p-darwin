


#ifndef __DARWIN_H__
#define __DARWIN_H__

#include <vector>
#include <stdexcept>
#include <cassert>


#define EMPTY    0
#define WALL     1
#define CREATURE 2
enum Direction   {NORTH=1, SOUTH=3, EAST=2, WEST=0};
enum Instruction {HOP, LEFT, RIGHT, INFECT, IF_E, IF_W, IF_R, IF_N, GO};
struct Line {
  Instruction ins;
  int target;
  bool operator==(const Line other) {
    return (ins==other.ins)&&(target==other.target);
  }
};
class World; class Species; class Creature;

/**
 * Describes an instance of Darwin's World and all therein creatures
 */
class World {
private:
  std::vector<int>      _g;
  std::vector<Creature> _c;
  size_t _xsize;
  size_t _ysize;
public:
  World(size_t y = 0, size_t x = 0) :
    _g(x*y), _c(),  _xsize(x), _ysize(y) {
    _c.reserve(20);
  }

  // -------------
  //  addCreature
  // -------------
  /**
   * Adds creatures to this world at a specified position
   * @param c Creature&, the creature to be added
   * @param x int, x position of creature in the world
   * @param y int, y position of creature in the world
   */
  void addCreature(Creature& c, unsigned y, unsigned x);
  // ---------
  //   round
  // ---------
  /**
   * Executes one round or time unit in the world
   * Each creature can act once
   */
  void round();
  // --------
  //   print
  // --------
  /**
   * Prints this world with numeric axis
   * @param o ostream&, the stream to which will be printed
   */
  void print(std::ostream& o);
};

/**
 * Describes a species behavior and name
 */
class Species {
private:
  std::vector<Line> program;
public:
  char              name;
  Species(char c = '?') :
    program(), name(c) {}
  // --------------
  // addInstruction
  // --------------
  /**
   * Appends a new instruction to this Species program
   * @param l Line, contains a line of valid creature code
   */
  void addInstruction(Line l);
  // --------------
  // addInstruction
  // --------------
  /**
   * Appends a new instruction to this Species program
   * @param i Instruction, valid creature code instruction
   * @param t int, destination if this instruction jumps, otherwise 0
   */
  void addInstruction(Instruction i, int t);
  // --------------
  // seeInstruction
  // --------------
  /**
   * Indexes this species' program
   * @param i usigned int, the line index
   * @return the desired line of creature code
   */
  Line seeInstruction(unsigned i);
  // -----------
  //     print
  // -----------
  /**
   * prints this species name (one character)
   * @param o ostream&, the stream to which will be printed
   */
  void print(std::ostream& o);
};

/**
 * Describes a unique creature
 */
class Creature {
private:
  Species*  _sp;
  unsigned  _pc;
  Direction _dir;

  void turn_l();
  void turn_r();
public:
  Creature(Species* sp, Direction dir = NORTH) :
    _sp(sp), _pc(0), _dir(dir) {}
  Creature(Species& sp, Direction dir = NORTH) :
    _sp(&sp), _pc(0), _dir(dir) {}
  // ---------
  //    act
  // ---------
  /**
   * Based on given information about what is in front of this creature,
   * Act according to the genetic (species) program
   * @param ahead int, the type of obstacle of empty
   * @param other Species*, the species of an enemy if there is one in front
   * @return the type of action taken
   */
  int       act(int ahead, Species* other);
  // ------
  // facing
  // ------
  /**
   * Described the direction this creature faces
   * @return the aforementioned description
   */
  Direction facing() const;
  // -------
  // species
  // -------
  /**
   * Desribes the species to which this creature belongs
   * @return the species
   */
  Species* species() const;
  // ------
  // infect
  //-------
  /**
   * Changes this creatures species to that given, and resets the pc
   * @param other Species*, the new species of this creature
   */
  void      infect(Species* other);
  // -----
  // print
  // -----
  /**
   * Prints the species name of this creature.
   * Internally calls Species::print
   * @param o ostream&, the stream to which will be printed
   */
  void print(std::ostream& o);
};

#endif
