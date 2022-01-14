#include "meet.h"

meet::meet(){
  randata * randomizer = new randata();
  for (int i =0; i < 16; i++){
    schools.push_back(new team(randomizer->team_name(), randomizer->d(randomizer->gen)));
  }
  delete randomizer;
  for (int i = 0; i < 10; i++){
    classes.push_back(new indv_tourney(i, schools));
  }
  previous_winner = NULL;
  completed = false;
}

meet::~meet(){
  for (int i =0; i < 16; i++){
    delete schools[i];
  }
  for (int i = 0; i < 10; i++){
    delete classes[i];
  }
  previous_winner = NULL;
}

void meet::tally(string tm, int result){

  switch(result){
  case 1:
    team_scores[tm] ++;
    break;
  case 2:
    team_scores[tm] ++;
    break;
  case 3:
    team_scores[tm] +=2;
    break;
  case 4:
    team_scores[tm] +=2;
    break;
  case 5:
    team_scores[tm] +=3;
    break;
  case 6:
    team_scores[tm] +=3;
    break;
  case 7:
    team_scores[tm] +=2.5;
    break;
  case 8:
    team_scores[tm] +=2.5;
    break;
  
  }
}

void meet::placing(indv_tourney * c){
  team_scores[c->victor(c->matches[26],false)->school] += 4;
  team_scores[c->victor(c->matches[26],true)->school] += 6;
  team_scores[c->victor(c->matches[27],false)->school] += 7;
  team_scores[c->victor(c->matches[27],true)->school] += 9;
  team_scores[c->victor(c->matches[28],false)->school] += 10;
  team_scores[c->victor(c->matches[28],true)->school] += 12;
}

void meet::tm_scores(){
  cout << endl;
  if (completed){
    for (int i =0; i< schools.size(); i++){
      cout << schools[i]->team_overall << " "<< schools[i]->name << " " <<team_scores[schools[i]->name] << endl;
    }
  }
  else cout << "Please run the meet first" << endl;
}


team * meet::run(){
  string waits = "\n125\n133\n141\n149\n157\n165\n174\n184\n197\nHWT\n";
  string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};
  string wclass = "";
  if (!completed){
    for (int i = 0; i < 10; i++){
      for (int j = 0; j < 29; j ++){
	classes[i]->next_game();
	tally(classes[i]->victor(classes[i]->matches[j],true)->school, classes[i]->matches[j]->result);
      }
      placing(classes[i]);
      
    }
    completed = true;
  }
  


  while (true){
    cout << "\nEnter the weight class bracket you would like to look at, or 0 to go back\n" << waits << endl;
    cin >> wclass;
    if (wclass == "0") break;
    for (int i = 0; i < 10; i++){
      if (weights[i] == wclass){
	classes[i]->bracket_navigate();
	break;
      }
    }
  }
  return NULL;
}
// winner-> temp
// second
// third


// new
// winner
// second

string meet::final_ranking(){
  string winner = "";
  string second = "";
  string third = "";
  string temp = "";

  int one=0;
  int two =0;
  int three =0;
  int te = 0;

  

  for (int i=0; i < schools.size(); i++){
    temp = schools[i]->name;
    te = team_scores[schools[i]->name];
    if (te > three){
      if (te > two){
	if (te > one){
	  swap(temp, winner);
	  swap(te, one);
	  swap(temp,second);
	  swap(te, two);
	  swap(temp,third);
	  swap(te, three);
	}
	else{
	  swap(temp,second);
	  swap(te, two);
	  swap(temp,third);
	  swap(te, three);
	}
      }
      else{
	swap(temp,third);
	swap(te, three);
      }
    }
  }
  if (one + two + three == 0) return "";
  return "\tTop Placing Teams\n\n1st:\t" + to_string(one) +"\t" +winner +"\n"+ "2nd:\t" + to_string(two) +"\t" +second +"\n" +"3rd:\t" + to_string(three) +"\t" +third;
}


void swap(string& a, string& b){
  string temp = "";
  temp = a;
  a = b;
  b = temp;
}

void swap(int a, int b){
  int te = 0;
  te = a;
  a = b;
  b = te;
}


void meet::show_teams(){
  cout << endl;
  int j = 0;
  string tmz = "";
  string wclass = "";
  string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};
  for (int i = 0; i < 16; i++){
    tmz += to_string(i+1) + " -- " + schools[i]->name + " (" + to_string(schools[i]->team_overall) +  ") \n";
  }
  while (true){
		   
    cout << endl << tmz << endl<< "Enter the index of the team you would like to view the lineup of, or 0 to go back" << endl <<endl;
    cin >> j;
    if (j == 0) return;

    else if (j <17){
      while (true){
	cout <<  schools[j-1]->info()<< endl<<"Enter the weight class to the wrestler's ratings, or 0 to return to the team menu\n" << endl;

	cin >> wclass;
	if (wclass == "0") {
	  break;
	}
     
	for (int i =0; i < 10; i++){
	  if (weights[i] == wclass){
	    cout << endl;
	    schools[j-1]->lineup[i]->print();
	    cout << endl;
	    break;
	  }
	}
      }
	 
    }
     
  }
}




