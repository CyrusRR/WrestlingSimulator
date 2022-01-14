// Cyrus Rody-Ramazani 1/6/22
#include "indv_tourney.h"
// Constructor, takes in weight class
indv_tourney::indv_tourney(string wgt){
  weightclass = wgt;
  // calls setup function
  set_up();
  // calls bracket-line setup
  bline_set_up();
  // Generates 16 random wrestlers
  random_wrestlers(false);
  // Makes the bracket
  bracket_setup();

  ismeet = false;
}

indv_tourney::indv_tourney(int wgt, vector <team *>& tourn_teams){
  weightclass = tourn_teams[0]->lineup[wgt]->weight;
  // calls setup function
  set_up();
  // calls bracket-line setup
  bline_set_up();
  // Generates 16 random wrestlers

  // use randomizer class to generate random names and ratings
  ismeet = true;
  
  for (int i = 0; i < 16; i ++){
    competitors.push_back(tourn_teams[i]->lineup[wgt]);
  }
  // Makes the bracket
  bracket_setup();
}




indv_tourney::~indv_tourney(){
  // deletes every wrestler made
  if (!ismeet){
    for (int i =0; i < competitors.size(); i++){
      delete competitors[i];
    }
  }

  competitors.clear();

  // deletes every match
  for (int i =0; i < matches.size(); i++){
    delete matches[i];
    matches[i] = NULL;
  }

  matches.clear();
  bracket = "";
  prev_champ = NULL;
}

void indv_tourney::bline_set_up(){

  int i =0;
  string s = "----------------- ";
  while (i <= 66){
    if (i<61) bracket_lines.push_back(s);
    else if (i == 61) bracket_lines.push_back("1st:\t");
    else if (i == 62) bracket_lines.push_back("2nd:\t");
    else if (i == 63) bracket_lines.push_back("3rd:\t");
    else bracket_lines.push_back(to_string(i-60)+"th:\t");
    
    i++;
  }
    
  
    // Puts all lines in bracket into the vector. Not pretty code, will fix.
  
}
// Sets up bracket, places the wrestlers names in outer bracket lines 

void indv_tourney::bracket_setup(){
  if (competitors.size() != 16) return;
  for (int i = 0; i < 16; i ++){
    bracket_lines[i] = "--" + competitors[i]->name.substr(0,4) + " "+ competitors[i]->name[competitors[i]->name.find(' ')+1] + ".--(" + to_string(competitors[i]->overall) +")-- ";
  }
}

// Just a shortcut to have multiple spaces in bracket
string spacing(int mult){
  string sp = "                  ";
  string ret = "";
  while (mult > 0){
    ret += sp;
    mult--;
  }
  return ret;
}

// Not pretty code, need to fix. Writes the entire bracket to a string and returns in
string indv_tourney::show_bracket(bool de){
  bracket = "";
  // 2 forms, tab with vertial line and without
  string spc = "                 |";
  string sp = "                  ";


  // Builds the bracket at 4 levels, each component of the final four
  
  bracket+= bracket_lines[0] + spacing(9) + bracket_lines[4] + "\n";
  bracket+= spc + spacing(8) + spc + "\n";
  bracket+= spc + bracket_lines[16] + spacing(7) +bracket_lines[24] + "\n";
  bracket+= spc + spc+ spacing(6) + spc +spc + "\n";
  bracket+= bracket_lines[8] + spc + spacing(6) +spc+sp+ bracket_lines[12] +"\n";

  bracket+= sp + spc + bracket_lines[36] +spacing(5)+bracket_lines[40] +"\n";

  bracket+= bracket_lines[1] + spc + spc+spacing(4)+ spc+spc+sp+ bracket_lines[5] + "\n";
  bracket+= spc + spc+ spc+spacing(4) +spc+ spc +spc + "\n";
  bracket+= spc + bracket_lines[18] +spc+ spacing(4)+spc +sp+bracket_lines[26] + "\n";
  bracket+= spc + sp+ spc+spacing(4) +spc+ sp +spc + "\n";
  bracket+= bracket_lines[9] +sp + spc+spacing(4)+spc+ sp+sp+ bracket_lines[13] + "\n";
 
  bracket+= sp + sp +spc+ bracket_lines[50] + spacing(3)+ bracket_lines[52]+"\n";
  
  bracket+= bracket_lines[2] + sp + spc+spacing(4) +spc+sp+sp+bracket_lines[6] + "\n";
  bracket+= spc + sp+ spc+spacing(4) +spc+ sp +spc + "\n";
  bracket+= spc + bracket_lines[20] + spc+spacing(2)+bracket_lines[60]+sp+spc +sp+bracket_lines[28] + "\n";
  bracket+= spc + spc+spc+ spacing(4) +spc+spc + spc + "\n";
  bracket+= bracket_lines[10] + spc +spc+spacing(4)+spc +spc+sp+ bracket_lines[14] + "\n";
  
  bracket+= sp + spc + bracket_lines[38] +spacing(5)+bracket_lines[42] +"\n";

  bracket+= bracket_lines[3] + spc+spacing(6) +spc+sp+ bracket_lines[7] + "\n";
  bracket+= spc + spc+ spacing(6) +spc+ spc + "\n";
  bracket+= spc + bracket_lines[22] + spacing(7) +bracket_lines[30] + "\n";
  bracket+= spc +  spacing(8) + spc + "\n";
  bracket+= bracket_lines[11] + spacing(9)+ bracket_lines[15] + "\n";

  bracket += "\n---------------------------------------------------------------------------------------   Consolation Bracket   -------------------------------------------------------------------------------------\n\n";
    
  bracket += sp+sp+sp+bracket_lines[51]+spacing(3)+bracket_lines[55]+"\n";
  bracket += sp+sp+sp+spc+spacing(3)+spc+"\n";
  bracket += sp+bracket_lines[43]+sp+spc+spacing(3)+spc+"\n";
  bracket += sp+spc+sp+spc+spacing(3)+spc+"\n";
  bracket += bracket_lines[17]+spc+bracket_lines[44]+spc+bracket_lines[54]+spacing(1)+"                      5th Place    |"+bracket_lines[58]+"\n";
  bracket += spc+spc+spc+spc+spc+spacing(2)+spc+"\n";
  bracket += spc+bracket_lines[32]+spc+spc+spc+spacing(2)+spc+"\n";
  bracket += spc+sp+spc+spc+spc+spacing(2)+spc+"\n";
  bracket += bracket_lines[19]+sp+spc+bracket_lines[48]+spc+spacing(2)+bracket_lines[57]+"\n";
  bracket += sp+sp+spc+sp+spc+"\n";
  bracket += sp+bracket_lines[41]+spc+sp+spc+"\n";
  bracket += sp+spc+spc+sp+spc+"\n";
  bracket += bracket_lines[21]+spc+bracket_lines[45]+"                      3rd Place    |"+bracket_lines[59]+"\n";
  bracket += spc+spc+sp+sp+spc+"\n";
  bracket += spc+bracket_lines[33]+sp+sp+spc+"\n";
  bracket += spc+sp+sp+sp+spc+"\n";
  bracket += bracket_lines[23]+sp+sp+bracket_lines[53]+spc+"\n";
  bracket += sp+sp+sp+spc+spc+"\n";
  bracket += sp+bracket_lines[39]+sp+spc+spc+"\n";
  bracket += sp+spc+sp+spc+spc+"\n";
  bracket += bracket_lines[25]+spc+bracket_lines[46]+spc+bracket_lines[56]+spacing(2) + "\t\t\t\tFinishers\n";
  bracket += spc+spc+spc+spc+spacing(3)+"\n";
  bracket += spc+bracket_lines[34]+spc+spc+spacing(3)+bracket_lines[61]+"\n";
  bracket += spc+sp+spc+spc+spacing(3)+"\n";
  bracket += bracket_lines[27]+sp+spc+bracket_lines[49]+spacing(3)+bracket_lines[62]+"\n";
  bracket += sp+sp+spc+spacing(3)+"\n";
  bracket += sp+bracket_lines[37]+spc+spacing(4)+bracket_lines[63]+"\n";
  bracket += sp+spc+spc+spacing(4)+"\n";
  bracket += bracket_lines[29]+spc+bracket_lines[47]+spacing(4)+bracket_lines[64]+"\n";
  bracket += spc+spc+sp+sp+sp+sp+"\n";
  bracket += spc+bracket_lines[35]+spacing(5)+bracket_lines[65]+"\n";
  bracket += spc+sp+sp+sp+sp+sp+"\n";
  bracket += bracket_lines[31]+spacing(6)+bracket_lines[66]+"\n";
  
  
  return bracket;
}

/*
	  for (int i = 0; i < matches.size(); i++){
	  cout << i << ": ";
	  if (matches[i] != NULL) cout << matches[i]->w1->name << " " << matches[i]->w2->name << endl;
	  else cout << endl;
	  }
	*/

// Used to parse through the bracket
void indv_tourney::bracket_navigate(){
  string com = "";
  int inter = 0;

  int j = 0;

  
  while (true){
    // Keep printing bracket & instructions
    cout << show_bracket(true) << endl;
    cout << "Enter 'f' to advance, the index of match (1-29) to view it, or 0 to go back"<< endl;
    cin >> com;

    
    // press f (forward) to sim next match
    if (com == "f"){
      next_game();
      continue;
    }

    j = stoi(com);

    // if 0, quit out
    if (j == 0) return;

    j--;
    
    // if selected match has yet to be played, continue
    if (j < 30 && matches[j] == NULL){
      cout << "This match has yet to be wrestled"<< endl;
      continue;
    }
    
    // if has been played. Needed to split it up due to organization of matches vector, which was arranged to make building the bracket easier.
    else if (j < 30){
      // show play by play
      cout << matches[j]->play_by_play() << endl;
      while (true) {
	
	// Look at player ratings, or the play-by-play
	cout << "Enter 1 to view " << matches[j]->w1->name<< "'s ratings, 2 to view " << matches[j]->w2->name <<"'s ratings, 3 to view the play-by-play, or 0 to go back"<< endl;
	cin >> inter;
	
	if (inter == 0) break;

	switch(inter){
	case 1:
	  matches[j]->w1->print();
	  break;
	case 2:
	  matches[j]->w2->print();
	  break;
	case 3:
	  cout << matches[j]->play_by_play() << endl;
	  break;
	default:
	  break;
	}	
      }
    }					    
  }
}


// Used to make player abbreviations in bracket

string indv_tourney::abbreviate(int index, bool wrestler,  bool winner){
  // If single/double digits, change spacing
  string s = " ";
  if (games >= 9) s = "";

  // Return (Match_index)-FirstFourLetters LastInit.-(Overall)--
  if (wrestler){
    if (winner) return "(" + to_string(games+1) + ")-" + matches[index]->w1->name.substr(0,4) + " "+  matches[index]->w1->name[matches[index]->w1->name.find(' ')+1] + ".-(" + to_string(matches[index]->w1->overall) +")-" +s;
    else return "---"  + matches[index]->w2->name.substr(0,4) + " "+  matches[index]->w2->name[matches[index]->w2->name.find(' ')+1] + ".-(" + to_string(matches[index]->w2->overall) +")-- ";
  }
  else{
    if (winner) return "(" + to_string(games+1) + ")-"  + matches[index]->w2->name.substr(0,4) + " "+  matches[index]->w2->name[matches[index]->w2->name.find(' ')+1] + ".-(" + to_string(matches[index]->w2->overall) +")-"+ s;
    else return "---" + matches[index]->w1->name.substr(0,4) + " "+  matches[index]->w1->name[matches[index]->w1->name.find(' ')+1] + ".-(" + to_string(matches[index]->w1->overall) +")-- ";
  }
}


// Avoid changing the wrestling class which would make the dual_tourney messed up, instead, read in from a match_sim the wrestler * victor from the match_sim->winner bool.
wrestler * indv_tourney::victor(match_sim * match, bool vict){
  if (match->winner) {
    if (vict) return match->w1;
    else return match->w2;
  }
  else{
    if (vict) return match->w2;
    else return match->w1;
  }
}


// Sims the next game in the tourney
void indv_tourney::next_game(){
  // if first round
  if (games < 8) {
    // Specific indexing for how the matches vector is organized
    matches[games] = new match_sim(competitors[games], competitors[games + 8]);
    // Make them wrestler
    matches[games]->wrastle();
    // Make new bracket line
    bracket_lines[(2*games) + 16] = abbreviate(games, matches[games]->winner, true);
    bracket_lines[(2*games) + 17] = abbreviate(games, matches[games]->winner, false);
  }

  else if (games < 12){
    // If round of 8
    matches[games] = new match_sim(victor(matches[(2*games)-16], false), victor(matches[(2*games) -15], false));
    matches[games]->wrastle();
    bracket_lines[games+24] =abbreviate(games, matches[games]->winner, true);
    
  }

  else if (games < 16){
    // if final four
    matches[games] = new match_sim(victor(matches[(games*2)-24], true),victor(matches[(2*games) -23], true));
    matches[games]->wrastle();
    bracket_lines[(2*games)+12] =  abbreviate(games, matches[games]->winner, true);
    bracket_lines[(2*games)+13] =  abbreviate(games, matches[games]->winner, false);

  }
  else if (games <20){
    matches[games] = new match_sim(victor(matches[31-games], false),victor(matches[games -8], true));
    matches[games]->wrastle();
    bracket_lines[games +28] =  abbreviate(games, matches[games]->winner, true);
    
  }

  else if (games <22){
    matches[games] = new match_sim(victor(matches[(games*2)-24], true),victor(matches[(2*games) -23], true));
    matches[games]->wrastle();
    bracket_lines[games +28] =  abbreviate(games, matches[games]->winner, true);
    
  }

  else if (games < 24){
    matches[games] = new match_sim(victor(matches[(games*2)-32], true),victor(matches[(2*games) -31], true));
    matches[games]->wrastle();
    bracket_lines[(2*games)+6] =  abbreviate(games, matches[games]->winner, true);
    bracket_lines[(2*games)+7] =  abbreviate(games, matches[games]->winner, false);
    
  }

  else if (games < 26){
    matches[games] = new match_sim(victor(matches[games-2], false),victor(matches[games-4], true));
    matches[games]->wrastle();
    bracket_lines[(2*games)+6] =  abbreviate(games, matches[games]->winner, true);
    bracket_lines[(2*games)+7] =  abbreviate(games, matches[games]->winner, false);
    
  }

  else if (games == 26){
    matches[games] = new match_sim(victor(matches[24], false),victor(matches[25], false));
    matches[games]->wrastle();
    bracket_lines[58] =  abbreviate(games, matches[games]->winner, true);
    bracket_lines[66] +=finalist(victor(matches[games], false));
    bracket_lines[65] +=finalist(victor(matches[games], true));
  }

  else if (games == 27){
    matches[games] = new match_sim(victor(matches[24], true),victor(matches[25], true));
    matches[games]->wrastle();
    bracket_lines[59] =  abbreviate(games, matches[games]->winner, true);
    bracket_lines[64] += finalist(victor(matches[games], false));
    bracket_lines[63] += finalist(victor(matches[games], true));
  }

  else if (games == 28){
    matches[games] = new match_sim(victor(matches[22], true),victor(matches[23], true));
    matches[games]->wrastle();
    bracket_lines[60] =  abbreviate(games, matches[games]->winner, true);
    bracket_lines[62] +=finalist(victor(matches[games], false));
    bracket_lines[61] +=finalist(victor(matches[games], true));
  }
    
    // bracket_lines[30] = "(15)" + victor(matches[6])->name.substr(0,4) + " " + victor(matches[6])->name[victor(matches[6])->name.find(' ')+1] + ". Wins! ";
    // cout << victor(matches[6])->name <<" Wins!" << endl;
games++;

}

string indv_tourney::finalist(wrestler * w){
   if (w->name.length() < 11) return "(" + to_string(w->overall) + ") " + w->name+ "\t\t\t"+ w->school;
  if (w->name.length() < 18) return "(" + to_string(w->overall) + ") " + w->name+ "\t\t"+ w->school;
  return  "(" + to_string(w->overall) + ") "+ w->name.substr(0,17)+ "\t\t"+ w->school;
}

 

// generate 16 random wrestlers, 15 if wanting to retain the previous winner
void indv_tourney::random_wrestlers(bool keep_champ){
  // use randomizer class to generate random names and ratings
  randata * randomizer = new randata();
  int i = 0;
  if (keep_champ){
    i ++;
    competitors.push_back(prev_champ);
  }
  for (; i < 16; i ++){
    competitors.push_back(new wrestler(randomizer->wrestler_name(), weightclass, randomizer->d(randomizer->gen)));
  }
  delete randomizer;
  
  
}



// prints the wrestlers

void indv_tourney::view_wrestlers(){
  for (int i =0; i < competitors.size(); i++){
    if (i % 4 == 0) cout << endl;
    cout << competitors[i]->name << ", ";
  }
  cout << endl;
}

// Setup method called in constructor
void indv_tourney :: set_up(){

  int i =0;
  while (i <28){
    matches.push_back(NULL);
    i++;
  }

  prev_champ = NULL;
  
  games =0;
  bracket = "";
  

 
}
