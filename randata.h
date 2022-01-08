#ifndef RANDATA_H
#define RANDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class randata{
 public:
  randata();
  ~randata();

  string wrestler_name();
  string team_name();

  static string adjectives [100];
  static string nouns [85];

  static string first_names [86];
  static string last_names [50];

  random_device rd;
  mt19937 gen;

  normal_distribution<> d;
  
  
};


#endif
  
  
