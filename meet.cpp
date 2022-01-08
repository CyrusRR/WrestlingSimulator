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


team * meet::run(){
  string waits = "\n125\n133\n141\n149\n157\n165\n174\n184\n197\nHWT\n";
  string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};
  string wclass = "";
  if (!completed){
    for (int i = 0; i < 10; i++){
      for (int j = 0; j < 15; j ++){
	classes[i]->next_game();
      }
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




