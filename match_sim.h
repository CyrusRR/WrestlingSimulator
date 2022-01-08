#ifndef MATCH_SIM_H
#define MATCH_SIM_H

#include <iostream>
#include <string>
#include <random>

#include "wrestler.h"

using namespace std;


class match_sim{
 public:
  match_sim(wrestler *, wrestler *);
  ~match_sim();
  bool wrastle();
  void period(int);
  void neutral();
  void takedown(bool);
  void bottom(bool);
  void top(bool);
  void ride_control(bool);
  void turn(bool);
  string play_by_play();
  string get_time();
  string get_score();

  bool points(int, bool);
  bool time_increase();

  int time;
  int max_time;
  int result;
  int w1_score;
  int w2_score;


  bool winner;
  int per;

  string pbp;

  wrestler * w1;
  wrestler * w2;

  bool last_ot;
};

#endif
  
  
