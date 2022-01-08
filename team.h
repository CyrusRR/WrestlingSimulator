#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "wrestler.h"

using namespace std;


class team{
public:
  team();
  ~team();
  team(string, int);
  team(string);
  team * copyOf();

  string info();

  string name;
  string abbrv;

  int team_overall;

  vector <wrestler*> lineup;
  
};

#endif
