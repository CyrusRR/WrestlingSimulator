#include "tourney.h"
#include "indv_tourney.h"
#include "meet.h"
#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"



int main_menu (string main_option[], int n_main_opt);

int duel_bracket_menu (string du_option[], int n_opt);

int indv_bracket_menu (string in_option[], int indv_opt);

int meet_menu (string meet_option[], int meet_opt);

string indv_option[] = {
  "Quit",
  "Launch New Individual Tournament (Single Weight Class)",
  "Launch New Meet (Full Roster)",
};

string dual_option[] = {
  "Quit",
  "Use Default Teams",
  "Use Random Teams",
  "Create New Teams",
  "View Teams",
  "Clear Teams",
  "New Teams - Keep Last Champion",
  "Launch New Tournament",
  "Show Bracket",

};

string main_option[] = {
  "Quit",
  "About",
  "Launch Dual Tournament Mode",
  "Launch Meet",
  "Launch Season",
  "Launch Individual Tournament Mode",
  ""
  
};


string meet_option[] = {
  "Quit",
  "Show Teams",
  "Launch Meet/View Brackets",
  "Show Team Scores"
};

int const n_indv_choice = 3;
int const n_main_choice = 7;
int const n_choice = 9;
int const meet_choice = 4;

void clrstrm(){
  cout << "\033[2J\033[1;1H";
}

int main() {
  int command;
  string response;

  srand(time(NULL));
  while (true){
    command = main_menu(main_option, n_main_choice);
    switch (command) {
    case 2:{
      clrstrm();
      cout << "Hi, this is my game!" << endl;
      break;
    }
    case 3:{
      clrstrm();
      bool duals = true;
      tourney * tournament = new tourney();
  
      while (duals) {
	command = duel_bracket_menu(dual_option, n_choice);
	switch (command){

    
	case 2:{
	  clrstrm();
	  if (tournament->teams.size()>= 8) break;
	  cout << "These are the selected teams \n" << endl;
	  tournament->teams.push_back(new team("Western Albemarle High School"));

	  tournament->teams.push_back(new team("Cave Springs High School"));

	  tournament->teams.push_back(new team("Albemarle High School"));

	  tournament->teams.push_back(new team("Christiansburg High School"));

	  tournament->teams.push_back(new team("Monticello High School"));
  
	  tournament->teams.push_back(new team("Fluvanna High School"));

	  tournament->teams.push_back(new team("Charlottesville High School"));

	  tournament->teams.push_back(new team("New Kent High School"));

	  tournament->view_teams();
	  break;
	}

	case 3:{
	  clrstrm();
	  tournament->random_teams(true);
	  tournament->view_teams();
	  break;
	}
	case 4: {
	  clrstrm();
	  string fullname;
	  int rating = 0;
	  while (tournament->teams.size() <= 7){
	    cout << " What do you want to name team "<< to_string(tournament->teams.size()+1) <<"? ";
	    cin >> ws; 
	    getline(cin, fullname);

	    cout << " What should " << fullname << "'s overall be? ";
	    cin >> rating;

	    if (rating > 99) rating = 99;
	    if (rating < 40) rating = 40;
	

	    tournament->teams.push_back(new team(fullname, rating));
	  }
      
	  break;
	}
    
	case 5:{
	  if (tournament->teams.size() == 0) {
	    clrstrm();
	    cout << "No Teams Selected" << endl;
	    break;
	  }
	  int team = 0;
      

	  while (true){
	    clrstrm();
	    cout << endl;
	    tournament->view_teams();
	    cout << endl;

	    cout << "\nPress 1-8 to view the desired team, or 0 to return to the main menu \n"<< endl;
	    cin >> team;
	    if (team == 0) {
	      clrstrm();
	      break;
	    }

	    string weight = "";
	    while (true){
	      cout << tournament->teams[team-1]->info() << endl;
	      cout << "Enter the weight class to the wrestler's ratings, or 0 to the team menu\n" << endl;
	      cin >> weight;
	      if (weight == "0"){
		clrstrm();
		
		cout << endl;
		tournament->view_teams();
		break;
	      }
	      string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};

	      for (int i = 0; i < 10; i++){
		clrstrm();
		if (weights[i] == weight){
		  cout << endl;
		  tournament->teams[team-1]->lineup[i]->print();
		  cout << endl;
		  break;
		}
	      }
	    }	
	  }	
	  break;
	}
	case 6:{
	  clrstrm();
	  delete tournament;
	  tournament = new tourney();
	  tournament->set_up();
	  cout << "Teams Cleared"<< endl;
	  break;
	}

            
      
	case 7:
	  if (tournament->teams.size() == 0 || tournament->champ == NULL ){
	    clrstrm();
	    cout << "Need to have a first tournament to determine a champion"<< endl;
	    break;
	
	  }
	  else{
	    clrstrm();
	    if (tournament->prev_champ != NULL)  tournament->prev_champ = NULL;
	  
	
	    tournament->prev_champ = tournament->champ->winner->copyOf();

	    for (int i = 0; i < tournament->teams.size(); i++){
	      delete tournament->teams[i];
	    }

	    delete tournament->a_quarter;
	    delete tournament->b_quarter;
	    delete tournament->c_quarter;
	    delete tournament->d_quarter;
	    delete tournament->a_semi;
	    delete tournament->b_semi;
	    delete tournament->champ;

	    tournament->a_quarter = NULL;
	    tournament->b_quarter = NULL;
	    tournament->c_quarter = NULL;
	    tournament->d_quarter = NULL;
	    tournament->a_semi = NULL;
	    tournament->b_semi = NULL;
	    tournament->champ = NULL;
	
	    tournament->teams.clear();

	
	    tournament->random_teams(false);
	
	    tournament->teams.push_back(tournament->prev_champ->copyOf());
	    cout << "These are the selected teams " << endl;
	    tournament->view_teams();
	    cout << endl;
	    tournament->bracket_sim(false);
	    break;
	  }

	case 8:{
	  cout << "Are you sure you want to launch a new tournament? This will erase any previous progress any ongoing tournament (y/n)" << endl;
	  cin >> response;
	  if (response[0] == 'y'){
	    clrstrm();
	    tournament->bracket_sim(false);
	    break;
	  }
	  break;
      

	}
	case 9:{
	  tournament->bracket_sim(true);
	  break;
     
	}
	case 1:{
	  cout << "\tDo you really want to quit? (y/n) > ";
	  cin >> response;

	  // Exit normally
	  if (response[0] == 'y' || response[0] == 'Y') {
	    delete tournament;
	    duals = false;
	    clrstrm();
	    break;
	  }
      
	  break;
	}
	}
      }
      break;
    }
    case 6:{
      bool indv = true;
      int co = 0;
      indv_tourney * itourn = NULL;


      while (indv){
	co = indv_bracket_menu(indv_option, n_indv_choice);
	switch(co){
	case 1:{
	  indv = false;
	  break;
	}
	case 2: {
	  cout << "What weight class would you like to simulate?"<< endl;
	  cin >> response;
	  itourn= new indv_tourney(response);
	  itourn->bracket_navigate();
	  cout << itourn->show_bracket(true)<< endl;
	  delete itourn;
	  itourn = NULL;
	  break;
	}
	case 3:{
	  cout << "" << endl;
	  break;
	}
	default: 
	  break;
	}
	  
      }
      break;
    }

    case 5:{
      cout << "work in progress" << endl;
      break;
	  
    }
    case 4:{
      bool m = true;
      int in = 0;
      meet * ranmeet = new meet();
      cout << RED "red\n" RESET;
      cout << GRN "green\n" RESET << endl;

      while (m){
	in = meet_menu(meet_option, meet_choice);
	switch (in){
	case 1:
	  m = false;
	  delete ranmeet;
	  break;
	case 2: 
	  ranmeet->show_teams();
	  break;
	case 3:
	  ranmeet->run();
	  break;
	case 4:
	  ranmeet->tm_scores();
	  cout << endl<< ranmeet->final_ranking()<< endl;
	  break;
	

      default:
	break;
	}


      }
      break;
    }
    case 1:{
      cout << "\tDo you really want to quit? (y/n) > ";
      cin >> response;

      // Exit normally
      if (response[0] == 'y' || response[0] == 'Y') {
	return 0;
      }
      break;
    }
    default: break;
    }
  }
}


int duel_bracket_menu (string dual_option[], int n_opt) {
  int choice, i;
  string input;


  cout << "\n\n\n     - - - - - - - - DUAL TOURNAMENT SIMULATOR - - - - - - - -" << endl;
  
  cout << endl;

  for (i = 0; i < n_opt; i++) {
    cout << "\t" << i + 1 << " - " << dual_option[i] << endl;
  }

  cout << endl;
  cout << "     - - - - - - - Created by Cyrus Rody-Ramazani  - - - - - -\n\n" << endl;

  while (input.empty()) {
    cout << "     Enter number of choice > ";
    cin >> input;

    if (isdigit(input[0])) {
      choice = atoi(input.c_str());

      if (choice <= n_opt && choice > 0) {
	return choice;
      } else {
	cout << "\tYour response MUST be between 1 and " << n_opt << endl;
	input.clear();
      }
    } else {
   
      cout << "\tYour response MUST be a number!" << endl;
      input.clear();
    }
  }

  return 1;
}

 int indv_bracket_menu (string indv_option[], int indv_opt) {
  int choice, i;
  string input;


  cout << "\n\n\n     - - - - - - - INDIVIDUAL TOURNAMENT SIMULATOR - - - - - -" << endl;
  
  cout << endl;

  for (i = 0; i < indv_opt; i++) {
    cout << "\t" << i + 1 << " - " << indv_option[i] << endl;
  }

  cout << endl;
  cout << "     - - - - - - - Created by Cyrus Rody-Ramazani  - - - - - -\n\n" << endl;
  

  while (input.empty()) {
    cout << "     Enter number of choice > ";
    cin >> input;

    if (isdigit(input[0])) {
      choice = atoi(input.c_str());

      if (choice <= indv_opt && choice > 0) {
	return choice;
      } else {
	cout << "\tYour response MUST be between 1 and " << indv_opt << endl;
	input.clear();
      }
    } else {
   
      cout << "\tYour response MUST be a number!" << endl;
      input.clear();
    }
  }

  return 1;
}

int meet_menu (string meet_option[], int meet_opt) {
  int choice, i;
  string input;


  cout << "\n\n\n     - - - - - - - - - - - MEET  SIMULATOR - - - - - - - - - -" << endl;
  
  cout << endl;

  for (i = 0; i < meet_opt; i++) {
    cout << "\t" << i + 1 << " - " << meet_option[i] << endl;
  }

  cout << endl;
  cout << "     - - - - - - - Created by Cyrus Rody-Ramazani  - - - - - -\n\n" << endl;

  while (input.empty()) {
    cout << "     Enter number of choice > ";
    cin >> input;

    if (isdigit(input[0])) {
      choice = atoi(input.c_str());

      if (choice <= meet_opt && choice > 0) {
	return choice;
      } else {
	cout << "\tYour response MUST be between 1 and " << meet_opt << endl;
	input.clear();
      }
    } else {
   
      cout << "\tYour response MUST be a number!" << endl;
      input.clear();
    }
  }

  return 1;
}


int main_menu (string main_option[], int n_main_opt) {
  int choice, i;
  string input;


  cout << "\n\n\n     - - - - - - - - - - WRESTLING SIMULATOR - - - - - - - - -" << endl;
  
  cout << endl;

  for (i = 0; i < n_main_opt; i++) {
    cout << "\t" << i + 1 << " - " << main_option[i] << endl;
  }

  cout << endl;
  cout << "     - - - - - - - Created by Cyrus Rody-Ramazani  - - - - - -\n\n" << endl;

  while (input.empty()) {
    cout << "     Enter number of choice > ";
    cin >> input;

    if (isdigit(input[0])) {
      choice = atoi(input.c_str());

      if (choice <= n_main_opt && choice > 0) {
	return choice;
      } else {
	cout << "\tYour response MUST be between 1 and " << n_main_opt << endl;
	input.clear();
      }
    } else {
   
      cout << "\tYour response MUST be a number!" << endl;
      input.clear();
    }
  }

  return 1;
}

