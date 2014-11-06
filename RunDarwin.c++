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
    trap.addInstruction(IF_E,3);
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

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
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

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
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

    return 0;}
