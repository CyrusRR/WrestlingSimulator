#ifndef TEAM_DUEL_H
#define TEAM_DUEL_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "match_sim.h"
#include "team.h"

using namespace std;


class team_duel{
 public:
  team_duel(team *, team *);
  ~team_duel();

  vector <match_sim *> matches;

  string box_score();
  string decision(match_sim*);

  team * a;
  team * b;

  int a_score;
  int b_score;

  string title;
  team * winner;
};
#endif

