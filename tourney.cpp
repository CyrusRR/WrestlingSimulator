#include "tourney.h"

tourney::tourney(){
  set_up();
}

void tourney::bracket_navigate(){
  cout << show_bracket() << endl;
  int resp = 0;
  string selection = "";
  bool exit = false;
  while (!exit){
    cout << "Press f to simulate the next match, numbers 1-7 to look at the box scores of each match, 8 to view the bracket again, and 0 to return to the main menu"<< endl;
    cin >> selection;
    if (selection == "f"){
      if (games != 7){
	next_game();
	switch(games){
	case 1:
	  aq = "(1)----" + a_quarter->winner->abbrv + "----- ";
	  break;
	    
	case 2:
	  bq = "(2)----" + b_quarter->winner->abbrv + "----- ";
	  break;
	      
	case 3:
	  cq = "(3)----" + c_quarter->winner->abbrv + "----- ";
	  break;
	
	case 4:
	  dq = "(4)----" + d_quarter->winner->abbrv + "----- ";
	  break;
      
	case 5:
	  as = "(5)----" + a_semi->winner->abbrv + "----- ";
	  break;
	      
	case 6:
	  bs = "(6)----" + b_semi->winner->abbrv + "----- ";
	  break;
	      
	case 7:
	  ch = "(7)----" + champ->winner->abbrv + "----- ";
	  break;     
	}
	cout << show_bracket() << endl;
	continue;
      }
      cout << "The tournament has completed!" << endl;
      continue;

    }
    else{
      resp = stoi(selection);
      switch(resp){
      
      case 1:
	stats(a_quarter);
	break;
	  
      case 2:
	stats(b_quarter);
	break;
	  
      case 3:
	stats(c_quarter);
	break;
	  
      case 4:
	stats(d_quarter);
	  
	break;
	  
      case 5:
	stats(a_semi);
	break;
	  
      case 6:
	stats(b_semi);
	break;
	  
      case 7:
	stats(champ);
	break;

      case 8:
	cout << show_bracket() << endl;
	break;
      case 0:
	return;
      }
    }
  }
  return;
}

void tourney::bracket_sim(bool started){
  if (!started){
    refresh();
    random_shuffle(teams.begin(),teams.end());
    if (teams.size() != 8){
      cout << "Please provide 8 teams for the tournament" << endl;
      return;
    }
    bracket_setup();
    bracket_navigate();
  }
  else{
    bracket_setup();
    if (games == 0) cout << show_bracket() << endl;
    else  bracket_navigate();
  }
}

void tourney::view_teams(){
  for (int i =0; i< teams.size(); i++){
    if (i == 4) cout << endl;
    cout << teams[i]->name << ", ";
  }
      
  cout << endl;
}


void tourney::set_up(){
  a_quarter = NULL;
  b_quarter = NULL;
  c_quarter = NULL;
  d_quarter = NULL;
  a_semi = NULL;
  b_semi = NULL;
  champ = NULL;
  prev_champ = NULL;
  games =0;

  aq = "(1)------------- ";
  bq = "(2)------------- ";
  cq = "(3)------------- ";
  dq = "(4)------------- ";
  as = "(5)------------- ";
  bs = "(6)------------- ";
  ch = "(7)------------- ";


  t1 = "--------------- ";
  t2 = "--------------- ";
  t3 = "--------------- ";
  t4 = "--------------- ";
  t5 = "--------------- ";
  t6 = "--------------- ";
  t7 = "--------------- ";
  t8 = "--------------- ";
}

tourney::~tourney(){
  for (int i =0; i < teams.size(); i ++){
    delete teams[i];
  }
  teams.clear();

  delete a_quarter;
  delete b_quarter;
   
  delete c_quarter;
  delete d_quarter;
  delete a_semi;
  delete b_semi;

  delete champ;
	      
}

void tourney::refresh(){
  if (a_quarter != NULL) delete a_quarter;
  if (b_quarter != NULL) delete b_quarter;
  if (c_quarter != NULL) delete c_quarter;
  if (d_quarter != NULL) delete d_quarter;
  if (a_semi != NULL) delete a_semi;
  if (b_semi != NULL)  delete b_semi;
  if (champ != NULL) delete champ;

  set_up();
}


void tourney::bracket_setup(){
  if (teams.size() != 8) return;
  t1 = "---" + teams[0]->abbrv + "-(" + to_string((teams[0]->team_overall)) + ")--- ";
  t2 = "---" + teams[1]->abbrv + "-(" + to_string((teams[1]->team_overall)) + ")--- ";
  t3 = "---" + teams[2]->abbrv + "-(" + to_string((teams[2]->team_overall)) + ")--- ";
  t4 = "---" + teams[3]->abbrv + "-(" + to_string((teams[3]->team_overall)) + ")--- ";
  t5 = "---" + teams[4]->abbrv + "-(" + to_string((teams[4]->team_overall)) + ")--- ";
  t6 = "---" + teams[5]->abbrv + "-(" + to_string((teams[5]->team_overall)) + ")--- ";
  t7 = "---" + teams[6]->abbrv + "-(" + to_string((teams[6]->team_overall)) + ")--- ";
  t8 = "---" + teams[7]->abbrv + "-(" + to_string((teams[7]->team_overall)) + ")--- ";
}


string tourney::show_bracket(){
  string spc = "               |";
  string sp = "                ";
  string s = "               ";
  bracket = t1;
  for (int i=0; i  < 35; i++){

    if (i == 12) bracket += "\n"  + s + bq + spc;
    else if (i == 22) bracket += "\n"  + s + cq + spc;

    else if (i == 3 || i == 4 || i == 31 || i ==30 ){
      bracket += "\n" +  spc + spc;
    }

    else if ( i == 11 || i ==10 || i == 24 || i == 23  ){
      bracket += "\n" +  spc + spc + spc;
    }

    else if (i == 5 ) bracket +=  "\n"+t2  + spc;
    else if (i == 29) bracket +=  "\n"+t7  + spc;
     

    

    else if (i == 15) bracket +=  "\n"+t4  + sp +  spc;
    else if (i == 19) bracket +=  "\n"+t5  + sp +  spc;


    else if (i  == 16 || i == 18){
      bracket +=  "\n"+sp  + sp +  spc;
    }
    else if (i == 17) bracket +=  "\n" + sp + sp +s + ch;

    else if (i == 6 || i ==8 || i == 28 ||  i == 26){
      bracket += "\n" + sp + spc;
      if ( i == 8 || i == 26) bracket += spc;  
    }
    else if (i == 7) bracket  += "\n" + sp + s +  as;
    else if (i == 27) bracket  += "\n" + sp + s +  bs;



    else if (i == 9) bracket +=  "\n"+t3 +spc + spc;
    else if (i == 25) bracket +=  "\n"+t6 +spc + spc;

    else if (i == 2)bracket +=  "\n" + s+ aq;
    else if (i == 32)bracket +=  "\n" + s+ dq;


    else if (i < 2|| i>32){
      bracket+= "\n" + spc;
    }

    else{
      bracket+= "\n" + spc + sp + spc;
    }
    
  }
  bracket += "\n"+t8;
  return bracket;
}

void tourney::random_teams(bool eight){
  if (teams.size()== 0){
    randata * randomizer = new randata();
    int i = 7;
    if (eight){i = 8;}
    while (i > 0){
      teams.push_back(new team(randomizer->team_name()));
      i--;
    }
    delete randomizer;

  }
}

void tourney::stats(team_duel* duel){
  if (duel == NULL) cout << "This match has yet to occur" << endl;
  else{
    cout << duel->box_score() << endl;
    string wc = "125";
    string weights[] = {"125","133","141","149","157","165","174","184","197","HWT"};
    while (true){
      cout << "Enter the weight class to view the play-by-play, else enter 1 to view "<<  duel->a->name <<"'s lineup, 2 to view " << duel->b->name <<"'s lineup, 8 to view the box score, or 0 to go back to the bracket" << endl;
      cin >> wc;
      if (wc == "1"){
	cout << duel->a->info() << endl;
      }
      else if (wc == "2"){
	cout << duel->b->info() << endl;
      }
      else if (wc == "0"){
	cout << show_bracket() << endl;
	break;
      }
      else if (wc == "8"){
	cout << duel->box_score() << endl;
      }

      else {
	for (int i = 0; i < 10; i ++){
	  if (wc == weights[i]){
	    cout << duel->matches[i]->play_by_play() << endl;
	    while (true){
	      cout << "Enter 1 to look at (" + duel->a->abbrv + ") " + duel->matches[i]->w1->name + "'s ratings, 2 to look at (" + duel->b->abbrv + ") " + duel->matches[i]->w2->name + "'s ratings, 3 to view the play_by_play again, or 0 to go back to the box score" << endl;
	      cin >> wc;
	      
	      if (wc == "1") duel->matches[i]->w1->print();
	      else if (wc == "2") duel->matches[i]->w2->print();
	      else if (wc == "3") cout << duel->matches[i]->play_by_play()<< endl;
	      else if (wc == "0") {
		cout << duel->box_score() << endl;
		break;
	      }
	      
	     
	    }
	  }
	}
      }
    }
  }
}

void tourney::next_game(){

  switch (games){
  case 0:
    a_quarter = new team_duel(teams[0], teams[1]);
    break;
  case 1:
    b_quarter = new team_duel(teams[2], teams[3]);
    break;
  case 2:
    c_quarter = new team_duel(teams[4], teams[5]);
    break;
  case 3:
    d_quarter = new team_duel(teams[6], teams[7]);
    break;
  case 4:
    a_semi = new team_duel(a_quarter->winner,  b_quarter->winner);
    break;
  case 5:
    b_semi = new team_duel(c_quarter->winner,  d_quarter->winner);
    break;
  case 6:
    champ = new team_duel(a_semi->winner,  b_semi->winner);
    cout << champ->winner->name + " Wins!"<< endl;
    break;	    
  }
  games++;
}





