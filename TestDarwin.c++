#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "gtest/gtest.h"
#include "Darwin.h"


TEST(Species, instructions1) {
  Line l0 = {LEFT, 0};
  Line l1 = {GO, 0};

  Species food('f');
  food.addInstruction(LEFT, 0);
  food.addInstruction(GO, 0);

  ASSERT_EQ(food.seeInstruction(0).ins, l0.ins);
  ASSERT_EQ(food.seeInstruction(1).ins, l1.ins);
}

TEST(Species, instructions2) {
  Line l0 = {LEFT, 0};
  Line l1 = {GO, 0};
  
  Species food('f');
  food.addInstruction(l0);
  food.addInstruction(l1);

  ASSERT_EQ(food.seeInstruction(0).ins, l0.ins);
  ASSERT_EQ(food.seeInstruction(1).ins, l1.ins);
}

TEST(Species, instructions3) {
  Line l0 = {LEFT, 0};
  Line l2 = {GO, 0};
  
  Species food('f');
  food.addInstruction(LEFT, 0);
  food.addInstruction(INFECT, 0);
  food.addInstruction(GO,1);

  ASSERT_EQ(food.seeInstruction(0).ins, l0.ins);
  ASSERT_EQ(food.seeInstruction(2).ins, l2.ins);
}

TEST(Species, instructions4) {
  Line l0 = {IF_N, 3};
  Line l1 = {LEFT, 0};
  Line l2 = {GO, 0};
  Line l3 = {INFECT, 0};

  Species trap('t');
  trap.addInstruction(l0);
  trap.addInstruction(l1);
  trap.addInstruction(l2);
  trap.addInstruction(l3);
  trap.addInstruction(l2);

  ASSERT_EQ(trap.seeInstruction(0).ins,l0.ins);
  ASSERT_EQ(trap.seeInstruction(1).ins,l1.ins);
  ASSERT_EQ(trap.seeInstruction(2).ins,l2.ins);
  ASSERT_EQ(trap.seeInstruction(4).ins,l2.ins);
}

TEST(Species, instructions5) {
  Line l0 = {INFECT, 0};
  Line l1 = {GO, 0};

  Species x;
  x.addInstruction(l0);
  x.addInstruction(l1);

  ASSERT_EQ(x.seeInstruction(0).ins,l0.ins);
  ASSERT_EQ(x.seeInstruction(1).ins,l1.ins);
}

TEST(Species, instructions6) {
  Species x;

  try {
    x.seeInstruction(0);
    ASSERT_FALSE(false);
  } catch( std::out_of_range e) {
    ASSERT_TRUE(true);
  }
}

TEST(Species, print1) {
  Species x;

  std::ostringstream oss;
  x.print(oss);
  ASSERT_EQ(oss.str(),"?");
}

TEST(Species, print2) {
  Species f('f');

  std::ostringstream oss;
  f.print(oss);
  ASSERT_EQ(oss.str(), "f");
}



TEST(Creature, facing1) {
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c(f,NORTH);

  ASSERT_EQ(c.facing(), NORTH);
}

TEST(Creature, facing2) {
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c(f,EAST);

  ASSERT_EQ(c.facing(), EAST);
}

TEST(Creature, facing3) {
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c(f,SOUTH);

  ASSERT_EQ(c.facing(), SOUTH);
}

TEST(Creature, facing4) {
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c(f,WEST);

  ASSERT_EQ(c.facing(), WEST);
}

TEST(Creature, act1) {
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c(f,NORTH);
  ASSERT_EQ(c.act(0,&f), 0);

  ASSERT_EQ(c.facing(), WEST);
}

TEST(Creature, act2) {
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c(f,NORTH);
  c.act(1,&f);
  c.act(2,&f);
  c.act(0,&f);

  ASSERT_EQ(c.facing(), EAST);
}

TEST(Creature, act3) {
  Species t('t');
  t.addInstruction(IF_N,3);
  t.addInstruction(RIGHT,0);
  t.addInstruction(GO,0);
  t.addInstruction(INFECT,0);
  t.addInstruction(GO,0);
  Creature c(t,NORTH);
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);

  ASSERT_EQ(c.act(2,&f),2);
  ASSERT_EQ(c.act(1,&f),0);
  ASSERT_EQ(c.act(2,&t),0);
}

TEST(Creature, sp1) {
  Species t('t');
  Creature c(t);

  ASSERT_EQ(c.species(),&t);
}

TEST(Creature, sp2) {
  Species t;
  Creature c(t);

  ASSERT_EQ(c.species(), &t);
}

TEST(Creature, sp3) {
  Species t;
  Species f;
  Creature c(t);

  ASSERT_EQ(c.species(), &t);
  ASSERT_NE(c.species(), &f);
}

TEST(Creature, infect1) {
  Species t('t');
  t.addInstruction(IF_N,3);
  t.addInstruction(RIGHT,0);
  t.addInstruction(GO,0);
  t.addInstruction(INFECT,0);
  t.addInstruction(GO,0);
  Creature c(t,NORTH);
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);

  ASSERT_EQ(c.species(),&t);
  c.infect(&f);
  ASSERT_EQ(c.species(),&f);
}

TEST(Creature, infect2) {
  Species t('t');
  t.addInstruction(IF_N,3);
  t.addInstruction(RIGHT,0);
  t.addInstruction(GO,0);
  t.addInstruction(INFECT,0);
  t.addInstruction(GO,0);
  Creature c1(t,NORTH);
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c2(f);

  ASSERT_EQ(c1.species(),&t);
  ASSERT_EQ(c2.species(),&f);
  c1.infect(c2.species());
  ASSERT_EQ(c1.species(),&f);
  c1.infect(c1.species());
  ASSERT_EQ(c1.species(),&f);
}

TEST(Creature, infect3) {
  Species t('t');
  t.addInstruction(IF_N,3);
  t.addInstruction(RIGHT,0);
  t.addInstruction(GO,0);
  t.addInstruction(INFECT,0);
  t.addInstruction(GO,0);
  Species f('f');
  f.addInstruction(LEFT,0);
  f.addInstruction(GO,0);
  Creature c1(t);
  Creature c2(t);

  ASSERT_EQ(c1.species(),&t);
  ASSERT_EQ(c2.species(),&t);
  c1.infect(&f);
  ASSERT_EQ(c1.species(),&f);
  ASSERT_EQ(c2.species(),&t);
}

TEST(Creature, print1) {
  Species x;
  Creature c(x);

  std::ostringstream oss;
  c.print(oss);
  ASSERT_EQ("?",oss.str());
}

TEST(Creature, print2) {
  Species f('f');
  Creature c(f);

  std::ostringstream oss;
  c.print(oss);
  ASSERT_EQ("f",oss.str());
}






TEST(World, darwin1) {
  World w(1,1);
  Species f('f');
  Creature c1(f);
  w.addCreature(c1,0,0);

  std::ostringstream oss;
  w.print(oss);
  ASSERT_EQ("  0\n0 f\n",oss.str());
}

TEST(World, darwin2) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Creature c1(h);
  w.addCreature(c1,1,1);

  std::ostringstream oss;
  w.print(oss);
  ASSERT_EQ("  01\n0 ..\n1 .h\n",oss.str());
}

  
TEST(World, darwin3) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Creature c1(h);
  w.addCreature(c1,1,1);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 .h\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 .h\n1 ..\n",oss2.str());
}

TEST(World, print1) {
  World w(0,0);

  std::ostringstream oss;
  w.print(oss);
  ASSERT_EQ(oss.str(),"  \n");
}


TEST(World, round1) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Creature c1(h);
  Creature c2(h);
  w.addCreature(c1,1,1);
  w.addCreature(c2,1,0);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 hh\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 hh\n1 ..\n",oss2.str());
}

TEST(World, round2) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Creature c1(h);
  Creature c2(h,EAST);
  w.addCreature(c1,1,1);
  w.addCreature(c2,1,0);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 hh\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 .h\n1 h.\n",oss2.str());
}

TEST(World, round3) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Creature c1(h);
  Creature c2(h,WEST);
  w.addCreature(c1,1,1);
  w.addCreature(c2,1,0);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 hh\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 .h\n1 h.\n",oss2.str());
}

TEST(World, round4) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Creature c1(h,WEST);
  Creature c2(h);
  w.addCreature(c1,1,1);
  w.addCreature(c2,1,0);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 hh\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 h.\n1 h.\n",oss2.str());
}

TEST(World, round5) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Species t('t');
  t.addInstruction(INFECT,0);
  t.addInstruction(GO,0);
  Creature c1(h);
  Creature c2(t,EAST);
  w.addCreature(c1,1,1);
  w.addCreature(c2,1,0);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 th\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 ..\n1 tt\n",oss2.str());
}

TEST(World, round6) {
  World w(2,2);
  Species h('h');
  h.addInstruction(HOP,0);
  h.addInstruction(GO,0);
  Species t('t');
  t.addInstruction(INFECT,0);
  t.addInstruction(GO,0);
  Creature c1(t,WEST);
  Creature c2(h);
  w.addCreature(c1,1,1);
  w.addCreature(c2,1,0);

  std::ostringstream oss1,oss2;
  w.print(oss1);
  ASSERT_EQ("  01\n0 ..\n1 ht\n",oss1.str());
  w.round();
  w.print(oss2);
  ASSERT_EQ("  01\n0 h.\n1 .t\n",oss2.str());
}

