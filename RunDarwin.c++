
// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2014
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
  using namespace std;

  // ----
  // food
  // ----
  Species food('f');
  food.addInstruction(LEFT,0);
  food.addInstruction(GO,0);
  /*
   0: left
   1: go 0
  */

  // ------
  // hopper
  // ------
  Species hop('h');
  hop.addInstruction(HOP,0);
  hop.addInstruction(GO,0);
  /*
   0: hop
   1: go 0
  */

  // -----
  // rover
  // -----
  Species rover('r');
  rover.addInstruction(IF_N,9);
  rover.addInstruction(IF_E,7);
  rover.addInstruction(IF_R,5);
  rover.addInstruction(LEFT,0);
  rover.addInstruction(GO,0);
  rover.addInstruction(RIGHT,0);
  rover.addInstruction(GO,0);
  rover.addInstruction(HOP,0);
  rover.addInstruction(GO,0);
  rover.addInstruction(INFECT,0);
  rover.addInstruction(GO,0);
  /*
   0: if_enemy 9
   1: if_empty 7
   2: if_random 5
   3: left
   4: go 0
   5: right
   6: go 0
   7: hop
   8: go 0
   9: infect
  10: go 0
  */

  // ----
  // trap
  // ----
  Species trap('t');
  trap.addInstruction(IF_N,3);
  trap.addInstruction(LEFT,0);
  trap.addInstruction(GO,0);
  trap.addInstruction(INFECT,0);
  trap.addInstruction(GO,0);
  /*
   0: if_enemy 3
   1: left
   2: go 0
   3: infect
   4: go 0
  */

  // ----
  // best
  // ----
  Species best('b');
  best.addInstruction(IF_N,10);
  best.addInstruction(IF_E,7);
  best.addInstruction(IF_R,5);
  best.addInstruction(LEFT,0);
  best.addInstruction(GO,0);
  best.addInstruction(RIGHT,0);
  best.addInstruction(GO,0);
  best.addInstruction(IF_R,5);
  best.addInstruction(HOP,0);
  best.addInstruction(GO,0);
  best.addInstruction(INFECT,0);
  best.addInstruction(GO,0);
  /*
   0: if_enemy 10
   1: if_empty 7
   2: if_random 5
   3: left
   4: go 0
   5: right
   6: go 0
   7: if_random 5
   8: hop
   9: go 0
  10: infect
  11: go 0
   */

  // ----------
  // darwin 8x8
  // ----------
  {
  cout << "*** Darwin 8x8 ***" << endl;
  World d8x8(8,8);
  Creature f1(food,EAST);
  d8x8.addCreature(f1,0,0);
  Creature h1(hop,NORTH);
  d8x8.addCreature(h1,3,3);
  Creature h2(hop,EAST);
  d8x8.addCreature(h2,3,4);
  Creature h3(hop,SOUTH);
  d8x8.addCreature(h3,4,4);
  Creature h4(hop,WEST);
  d8x8.addCreature(h4,4,3);
  Creature f2(food,NORTH);
  d8x8.addCreature(f2,7,7);
  /*
  8x8 Darwin
  Food,   facing east,  at (0, 0)
  Hopper, facing north, at (3, 3)
  Hopper, facing east,  at (3, 4)
  Hopper, facing south, at (4, 4)
  Hopper, facing west,  at (4, 3)
  Food,   facing north, at (7, 7)
  Simulate 5 moves.
  Print every grid.
  */
  for(int i=0;i<6;++i){
    cout << "Turn = " << i << '.' << endl;
    d8x8.print(cout);
    cout << endl;
    d8x8.round();
  }
  } 
  // ----------
  // darwin 7x9
  // ----------
  {
  cout << "*** Darwin 7x9 ***" << endl;
  srand(0);
  World d7x9(7,9);
  Creature t1(trap,SOUTH);
  d7x9.addCreature(t1,0,0);
  Creature h1(hop,EAST);
  d7x9.addCreature(h1,3,2);
  Creature r1(rover,NORTH);
  d7x9.addCreature(r1,5,4);
  Creature t2(trap,WEST);
  d7x9.addCreature(t2,6,8);
  /*
  7x9 Darwin
  Trap,   facing south, at (0, 0)
  Hopper, facing east,  at (3, 2)
  Rover,  facing north, at (5, 4)
  Trap,   facing west,  at (6, 8)
  Simulate 5 moves.
  Print every grid.
  */
  for(int i=0;i<6;++i){
    cout << "Turn = " << i << '.' << endl;
    d7x9.print(cout);
    cout << endl;
    d7x9.round();
  }
  }
  // ------------
  // darwin 72x72
  // without best
  // ------------
  {
  cout << "*** Darwin 72x72 without Best ***" << endl;
  srand(0);
  World d72x72_nobest(72,72);
  int r = rand()%5184;
  int s = rand()%4;
  Direction d;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f1(&food,d);
  d72x72_nobest.addCreature(f1, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f2(&food,d);
  d72x72_nobest.addCreature(f2, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f3(&food,d);
  d72x72_nobest.addCreature(f3, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f4(&food,d);
  d72x72_nobest.addCreature(f4, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f5(&food,d);
  d72x72_nobest.addCreature(f5, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f6(&food,d);
  d72x72_nobest.addCreature(f6, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f7(&food,d);
  d72x72_nobest.addCreature(f7, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f8(&food,d);
  d72x72_nobest.addCreature(f8, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f9(&food,d);
  d72x72_nobest.addCreature(f9, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature f0(&food,d);
  d72x72_nobest.addCreature(f0, r/72, r%72);

  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h1(&hop,d);
  d72x72_nobest.addCreature(h1, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h2(&hop,d);
  d72x72_nobest.addCreature(h2, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h3(&hop,d);
  d72x72_nobest.addCreature(h3, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h4(&hop,d);
  d72x72_nobest.addCreature(h4, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h5(&hop,d);
  d72x72_nobest.addCreature(h5, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h6(&hop,d);
  d72x72_nobest.addCreature(h6, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h7(&hop,d);
  d72x72_nobest.addCreature(h7, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h8(&hop ,d);
  d72x72_nobest.addCreature(h8, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h9(&hop ,d);
  d72x72_nobest.addCreature(h9, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature h0(&hop ,d);
  d72x72_nobest.addCreature(h0, r/72, r%72);

  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r1(&rover,d);
  d72x72_nobest.addCreature(r1, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r2(&rover,d);
  d72x72_nobest.addCreature(r2, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r3(&rover,d);
  d72x72_nobest.addCreature(r3, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r4(&rover,d);
  d72x72_nobest.addCreature(r4, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r5(&rover,d);
  d72x72_nobest.addCreature(r5, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r6(&rover,d);
  d72x72_nobest.addCreature(r6, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r7(&rover,d);
  d72x72_nobest.addCreature(r7, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r8(&rover ,d);
  d72x72_nobest.addCreature(r8, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r9(&rover ,d);
  d72x72_nobest.addCreature(r9, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature r0(&rover ,d);
  d72x72_nobest.addCreature(r0, r/72, r%72);




r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t1(&trap,d);
  d72x72_nobest.addCreature(t1, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t2(&trap,d);
  d72x72_nobest.addCreature(t2, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t3(&trap,d);
  d72x72_nobest.addCreature(t3, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t4(&trap,d);
  d72x72_nobest.addCreature(t4, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t5(&trap,d);
  d72x72_nobest.addCreature(t5, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t6(&trap,d);
  d72x72_nobest.addCreature(t6, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t7(&trap,d);
  d72x72_nobest.addCreature(t7, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t8(&trap ,d);
  d72x72_nobest.addCreature(t8, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t9(&trap ,d);
  d72x72_nobest.addCreature(t9, r/72, r%72);
  r = rand()%5184;
  s = rand()%4;
  switch(s) {
  case 0: d = WEST; break;
  case 1: d = NORTH; break;
  case 2: d = EAST; break;
  case 3: d = SOUTH; break;
  }
  Creature t0(&trap ,d);
  d72x72_nobest.addCreature(t0, r/72, r%72);


/*
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature f(food,d);
    d72x72_nobest.addCreature(f, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature h(hop,d);
    d72x72_nobest.addCreature(h, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature o(rover,d);
    d72x72_nobest.addCreature(o, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature t(trap,d);
    d72x72_nobest.addCreature(t, r/72, r%72);
  }*/
  /*
  Randomly place the following creatures facing randomly.
  Call rand(), mod it with 5184 (72x72), and use that for the position
  in a row-major order grid.
  Call rand() again, mod it with 4 and use that for it's direction with
  the ordering: west, north, east, south.
  Do that for each kind of creature.
  10 Food
  10 Hopper
  10 Rover
  10 Trap
  Simulate 1000 moves.
  Print the first 10 grids          (i.e. 0, 1, 2...9).
  Print every 100th grid after that (i.e. 100, 200, 300...1000).
  */
  for(int i = 0; i < 1001; ++i) {
    if(i < 10 || i%100 == 0) {
      cout << "Turn = " << i << '.' << endl;
      d72x72_nobest.print(cout);
      cout << endl;
    }
    d72x72_nobest.round();
  }
  }
  // ------------
  // darwin 72x72
  // with best
  // ------------
  {
  cout << "*** Darwin 72x72 with Best ***" << endl;
  srand(0);
  World d72x72_best(72,72);
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature f(food,d);
    d72x72_best.addCreature(f, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature h(hop,d);
    d72x72_best.addCreature(h, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature o(rover,d);
    d72x72_best.addCreature(o, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature t(trap,d);
    d72x72_best.addCreature(t, r/72, r%72);
  }
  for(int i = 0; i < 10; ++i) {
    int r = rand()%5184;
    int s = rand()%4;
    Direction d;
    switch(s) {
      case 0: d = WEST;
      case 1: d = NORTH;
      case 2: d = EAST;
      case 3: d = SOUTH;
    }
    Creature b(best,d);
    d72x72_best.addCreature(b, r/72, r%72);
  }
  /*
  Randomly place the following creatures facing randomly.
  Call rand(), mod it with 5184 (72x72), and use that for the position
  in a row-major order grid.
  Call rand() again, mod it with 4 and use that for it's direction with
  the ordering: 0:west, 1:north, 2:east, 3:south.
  Do that for each kind of creature.
  10 Food
  10 Hopper
  10 Rover
  10 Trap
  10 Best
  Simulate 1000 moves.
  Best MUST outnumber ALL other species for the bonus pts.
  Print the first 10 grids          (i.e. 0, 1, 2...9).
  Print every 100th grid after that (i.e. 100, 200, 300...1000).
  */
  for(int i = 0; i < 1001; ++i) {
    if(i < 10 || i%100 == 0) {
      cout << "Turn = " << i << '.' << endl;
      d72x72_best.print(cout);
      cout << endl;
    }
    d72x72_best.round();
  }
  }
  return 0;
}
