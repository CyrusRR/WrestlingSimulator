#include "team.h"
#include "wrestler.h"
#include "randata.h"
#include <iostream>

team::team(){
  name = "";
  abbrv = "";
  team_overall = 0.0;
}

team::team(string nm, int rating){
  name = nm;
  abbrv = "";
  abbrv.push_back(name.at(0));
  int a = name.find(' ');
  abbrv.push_back(name.at(a+1));
  abbrv += "HS";//+ nm[0];
  string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};

  randata * randomizer = new randata();
  team_overall = 0;

  for (int i =0; i< 10; i++){
    lineup.push_back(new wrestler(randomizer->wrestler_name(), weights[i], rating));
    lineup[i]->school = name;
    team_overall += lineup[i]->overall;
  }
  team_overall = team_overall/10;
  delete randomizer;
  
}
  

team::team(string nm){
  name = nm;
  abbrv = "";
  abbrv.push_back(name.at(0));
  int a = name.find(' ');
  abbrv.push_back(name.at(a+1));
  abbrv += "HS";//+ nm[0];
  string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};

  randata * randomizer = new randata();
  
  int t_o = (int) randomizer->d(randomizer->gen);
  
  if (t_o <40) t_o = 40;
  
  team_overall = 0;
  

  for (int i =0; i< 10; i++){
    lineup.push_back(new wrestler(randomizer->wrestler_name(), weights[i], t_o));
    lineup[i]->school = name;
    team_overall += lineup[i]->overall;
  }
  team_overall = team_overall/10;
  delete randomizer;
  
}

team::~team(){
  for (int i = 0; i < lineup.size(); i ++){
    delete lineup[i];
  }

}

string team::info(){
  string resp = "\n" + name + " (" + abbrv + ") - " + to_string(team_overall)+ "\n";
    for (int i = 0; i < lineup.size(); i++){
      resp += lineup[i]->weight + ": " + lineup[i]->name + " - " + to_string(lineup[i]->overall) + "\n";
    }							      
  return resp;
}

team * team::copyOf(){
  team * second = new team();
  second->name = name;
  second->abbrv = abbrv;
  second->team_overall = team_overall;
  for (int i = 0; i < lineup.size(); i ++){
    second->lineup.push_back(lineup[i]->copyOf());
  }
  return second;
}
    


