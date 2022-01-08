#ifndef TOURNEY_H
#define TOURNEY_H


#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "team.h"
#include "team_duel.h"
#include "randata.h"
using namespace std;


class tourney{
 public:
  tourney();
  ~tourney();
  vector <team *> teams;
  string show_bracket();
  void next_game();
  void bracket_setup();

  void bracket_sim(bool);
  void bracket_navigate();

  void stats(team_duel *);
  void refresh();
  void set_up();
  void random_teams(bool);

  void view_teams();
  team_duel *a_quarter;
  team_duel *b_quarter;
  team_duel *c_quarter;
  team_duel *d_quarter;
  team_duel *a_semi;
  team_duel *b_semi;
  team_duel *champ;
  team * prev_champ;

  string aq,bq,cq,dq,as,bs,ch,t1,t2,t3,t4,t5,t6,t7,t8;

  int games;
  string bracket;

};

#endif
