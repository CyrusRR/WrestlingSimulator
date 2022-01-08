#ifndef MEET_H
#define MEET_H


#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "wrestler.h"
#include "indv_tourney.h"
#include "team.h"
#include "randata.h"

using namespace std;

class meet{
 public:
  meet();
  ~meet();

  vector <indv_tourney *> classes;

  vector <team *> schools;

  team * previous_winner;

  team * run();

  void show_teams();
  bool completed;
  
};

#endif

