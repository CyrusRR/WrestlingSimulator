#ifndef MEET_H
#define MEET_H


#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <unordered_map>

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

  unordered_map <string, double> team_scores;

  team * previous_winner;

  team * run();

  void show_teams();
  bool completed;

  int match_res;
  string sch;

  void tally(string, int);

  void placing(indv_tourney *);

  void tm_scores();

  string final_ranking();
  

  
  
};

#endif

