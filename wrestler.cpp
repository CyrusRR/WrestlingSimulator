#include "wrestler.h"


wrestler::wrestler(){
  name = "";
  school = "";
  weight = "";
  overall = 0;
}
void wrestler::print(){
  cout << "Name " << name << endl;
  cout << "School " << school << endl;
  cout << "Weight " << weight << endl;
  cout << "Overall " << overall << endl;
  cout << "Control " << control << endl;
  cout << "Takedown " << takedown << endl;
  cout << "Defense " << defense << endl;
  cout << "Top Control " << tcon << endl;
  cout << "Return " << ret << endl;
  cout << "Turn " << turn << endl;
  cout << "Fall " << fall << endl;
  cout << "Bottom Control " << bcon << endl;
  cout << "Move " << move << endl;
  cout << "Belly " << belly << endl;
  cout << "Bridge " << bridge << endl;
    
    
    
}

int wrestler::rand_rating(double input){
  if (input > 99) return 99;
  if (input < 35) return 35;
  return (int) input;
}

wrestler::~wrestler(){
}



wrestler::wrestler(string nm, string wgt, int team_overall){
  randata * randomizer = new randata();

  randomizer->d =  normal_distribution<> (team_overall,6);
  
  name = nm;
  school = "";
  weight = wgt;
  nurture = rand_rating(randomizer->d(randomizer->gen));


  randomizer->d =  normal_distribution<> (nurture,4);


  
  control = rand_rating(randomizer->d(randomizer->gen));
  takedown =  rand_rating(randomizer->d(randomizer->gen));
  defense = rand_rating(randomizer->d(randomizer->gen));
  tcon =rand_rating(randomizer->d(randomizer->gen));
  ret = rand_rating(randomizer->d(randomizer->gen));
  turn = rand_rating(randomizer->d(randomizer->gen));
  fall = rand_rating(randomizer->d(randomizer->gen));
  bcon =rand_rating(randomizer->d(randomizer->gen));
  move = rand_rating(randomizer->d(randomizer->gen));
  belly =rand_rating(randomizer->d(randomizer->gen));
  bridge = rand_rating(randomizer->d(randomizer->gen));


  overall= (control + takedown+ defense + tcon + ret + turn + fall + bcon + move + belly + bridge)/11;
  delete randomizer;
}



wrestler * wrestler::copyOf(){
  wrestler * other = new wrestler();
  other->overall = overall;
  other->nurture = nurture;
  other->name = name;
  other->school = school;
  other->weight = weight;
  other->control = control;
  other->takedown=takedown;
  other->defense = defense;
  other->tcon = tcon;
  other->ret = ret;
  other->turn = turn;
  other->fall = fall;
  other->bcon = bcon;
  other->move = move;
  other->belly = belly;
  other->bridge = bridge;
  return other;
}

