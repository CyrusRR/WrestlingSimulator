//Cyrus Rody-Ramazani - clr3dw - lab 11 - inlab 11/30/21 - middleearth.h
#ifndef WRESTLER_H
#define WRESTLER_H

#include <iostream>
#include <string>
#include <random>

#include "randata.h"

using namespace std;


class wrestler {
 public:
  wrestler(string, string, int);
  wrestler();
  ~wrestler();
  
  wrestler * copyOf();
  
  void print();

  int(rand_rating(double));

  string name, school, weight;
  int overall, nurture, control, takedown, defense, tcon, ret, turn, fall, bcon, move, belly, bridge;

};

#endif
