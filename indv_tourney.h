#ifndef INDV_TOURNEY_H
#define INDV_TOURNEY_H


#include <iostream>
#include <string>
#include <random>
#include <vector>

// Uses wrestlers, match simulations, and randomizers
#include "wrestler.h"
#include "match_sim.h"
#include "randata.h"
#include "team.h"

using namespace std;

class indv_tourney{
 public:
  // Constructor and destructor
  indv_tourney(string);
  indv_tourney(int, vector <team*> &);
  ~indv_tourney();

  // Array of wrestlers
  vector <wrestler *> competitors;

  // Bracket management
  string show_bracket();
  void bracket_setup();
  void bracket_sim(bool);
  void bracket_navigate();
  void bline_set_up();

  
  // sim next match
  void next_game();

  // used in constructors, set up bracket and members
  void set_up();

  // generate wrestlers(15 if false (keep previous champ), 16 if true)
  void random_wrestlers(bool);
 
  void view_wrestlers();

  
  // Return a bracket line based on  of matches[int index]->winner, if bool, is a double digits bracket line
  string abbreviate(int, bool);

  // pull the winner of a match_sim

  wrestler * victor(match_sim *);
  
  // all matches being simulated (8 of rd 1), (4 of rd 2), (2 of rd 3), (1 of champ)
  match_sim *a_sixteen;
  match_sim *b_sixteen;
  match_sim *c_sixteen;
  match_sim *d_sixteen;
  match_sim *e_sixteen;
  match_sim *f_sixteen;
  match_sim *g_sixteen;
  match_sim *h_sixteen;

  match_sim *a_quarter;
  match_sim *b_quarter;
  match_sim *c_quarter;
  match_sim *d_quarter;

  match_sim *a_semi;
  match_sim *b_semi;

  match_sim *champ;

  // Pointer to previous champion (if desired game mode)
  wrestler * prev_champ;

  // Bracket line strings
  string asx,bsx,csx,dsx,esx,fsx,gsx,hsx,aq,bq,cq,dq,as,bs,ch,w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15;

  
  // Match index
  int games;

  // The bracket
  string bracket;

  // The weight class
  string weightclass;

  // All bracket line strings
  vector <string> bracket_lines;

  
  // All matches in tourney
  vector <match_sim * > matches;

  bool ismeet;
   
};

#endif

