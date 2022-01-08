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
  champ = NULL; 
}

void indv_tourney::bline_set_up(){
  // Puts all lines in bracket into the vector. Not pretty code, will fix.
  bracket_lines.push_back(w0);
  bracket_lines.push_back(w1);
  bracket_lines.push_back(w2);

 
  bracket_lines.push_back(w3);
  bracket_lines.push_back(w4);

  
  bracket_lines.push_back(w5);
  bracket_lines.push_back(w6);

  bracket_lines.push_back(w7);
  bracket_lines.push_back(w8);

  
  bracket_lines.push_back(w9);
  bracket_lines.push_back(w10);

    
  bracket_lines.push_back(w11);
  bracket_lines.push_back(w12);

  
  bracket_lines.push_back(w13);
  bracket_lines.push_back(w14);

  bracket_lines.push_back(w15);
 

  
  bracket_lines.push_back(asx);
  //8
  bracket_lines.push_back(bsx);
  bracket_lines.push_back(csx);
  bracket_lines.push_back(dsx);

    
  //24
  bracket_lines.push_back(esx);
  bracket_lines.push_back(fsx);
  bracket_lines.push_back(hsx);
  bracket_lines.push_back(gsx);
 
  
  bracket_lines.push_back(aq);//12
  bracket_lines.push_back(cq);
  bracket_lines.push_back(bq);//28
  bracket_lines.push_back(dq);
  
  bracket_lines.push_back(as); // 14

  
  bracket_lines.push_back(bs);
  bracket_lines.push_back(ch);
		    
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
string indv_tourney::show_bracket(){
  bracket = "";
  // 2 forms, tab with vertial line and without
  string spc = "                 |";
  string sp = "                  ";


  // Builds the bracket at 4 levels, each component of the final four
  for (int i=0; i  < 4; i++){
    /*
Built to look like wrestler -----                ---- wrestler
                                 |              |
                                 |-----    -----|           
                                 |              | 
                    wrestler -----              ----- wrestler
                                        etc,
     */
    // Top part of each quarter:
    if (i ==0) bracket+=  bracket_lines[i] + spacing(7) + bracket_lines[i+4]  +  "\n";
    else if (i ==1) bracket+=  bracket_lines[i] + spc + spc + sp + sp + spc + spc + sp + bracket_lines[i+4]  +  "\n";
    else if (i == 2) bracket+=  bracket_lines[i] + sp + spc + sp + sp + spc + sp + sp + bracket_lines[i+4]  +  "\n";

    else  bracket+=  bracket_lines[i] + spc + spacing(4) + spc + sp + bracket_lines[i+4]  +  "\n";


    // Middle of each quarter: Building connecting line in between
    for (int j = 0; j < 5; j++){
      bracket+= spc;
      // At middle, new line ofshoot
      if (j == 2){
	if  (i == 2) bracket +=  bracket_lines[18] + spc + sp +  bracket_lines[30] + spc + sp + bracket_lines[22] + "\n";
	else if  (i == 1) bracket +=  bracket_lines[17] + spc + "          Individual Tournament:      " + weightclass + "            |" + sp + bracket_lines[21] + "\n";
	else if (i == 0 || i == 3) bracket +=  bracket_lines[i +16] + spacing(5) + bracket_lines[i +20] + "\n";

      }
      // Connecting line i between
      else if ((j >2 && i%2 ==0) || (j <2 && i%2 !=0) ) {
	if (i == 1 || i == 2) bracket += spc + spc + sp + sp + spc + spc + spc+ "\n";
	else  bracket += spc +spacing(4)+ spc + spc+ "\n";
      }
      else{
	if (i == 1 || i == 2) bracket += sp + spc + sp + sp + spc + sp + spc+ "\n";
	else bracket += spacing(6) + spc+ "\n";
      }
    }
    // End of each quarter  
    if (i == 0) bracket+=  bracket_lines[i+8] + spc + spacing(4) + spc + sp + bracket_lines[i+12]  +  "\n" +sp + spc + spacing(4) + spc + sp +"\n" +sp + spc + bracket_lines[24] + sp +sp + sp +bracket_lines[26] + sp + "\n" +sp + spc + spc + sp + sp + spc + spc + sp + "\n" ;
    
    else if (i ==1) bracket+=  bracket_lines[i+8] + sp + spc + sp + sp + spc + sp + sp + bracket_lines[i+12]  +  "\n" +sp + sp + spc +  bracket_lines[28] + sp +  bracket_lines[29] + sp + sp + sp + +  "\n" +sp + sp + spc + sp + sp + spc + sp + sp + sp +  "\n" +sp + sp + spc + sp + sp + spc + sp + sp + sp + "\n";
    
    else if (i ==2) bracket+=  bracket_lines[i+8] + spc + spc + sp + sp + spc + spc + sp + bracket_lines[i+12]  +  "\n" +sp + spc + spc + sp + sp + spc + spc + sp +"\n" +sp + spc + bracket_lines[25] + sp + sp + sp +bracket_lines[27] + sp + "\n" +sp + spc + spacing(4) + spc + sp + "\n" ;

    else  bracket+=  bracket_lines[i+8] + spacing(7) + bracket_lines[i+12]  +  "\n\n\n";	
  }
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

  
  while (true){
    // Keep printing bracket & instructions
    cout << show_bracket() << endl;
    cout << "Enter 'f' to advance, the index of match (1-15) to view it, or 0 to go back"<< endl;
    cin >> com;

    
    // press f (forward) to sim next match
    if (com == "f"){
      next_game();
      continue;
    }

    // if 0, quit out
    else if (stoi(com) == 0) return;

    
    // if selected match has yet to be played, continue
    else if ((stoi(com) < 9 && matches[stoi(com)+6] == NULL) || ((stoi(com) < 16 && stoi(com) >= 9) && matches[stoi(com)-9] == NULL)){
      cout << "This match has yet to be wrestled"<< endl;
      continue;
    }
    
    // if has been played (first round). Needed to split it up due to organization of matches vector, which was arranged to make building the bracket easier.
    else if (stoi(com) < 9){
      // show play by play
      cout << matches[stoi(com) +6]->play_by_play() << endl;
      while (true) {
	
	// Look at player ratings, or the play-by-play
	cout << "Enter 1 to view " << matches[stoi(com) +6]->w1->name<< "'s ratings, 2 to view " << matches[stoi(com) +6]->w2->name <<"'s ratings, 3 to view the play-by-play, or 0 to go back"<< endl;
	cin >> inter;
	
	if (inter == 0) break;

	switch(inter){
	case 1:
	  matches[stoi(com)+6]->w1->print();
	  break;
	case 2:
	  matches[stoi(com)+6]->w2->print();
	  break;
	case 3:
	  cout << matches[stoi(com)+6]->play_by_play() << endl;
	  break;
	default:
	  break;
	}	
      }
    }

    // if past quarterfinals, then index from different spot in vector.
    else if (stoi(com) < 16) {
      cout << matches[stoi(com) -9]->play_by_play() << endl;
      while (true) {
	//Player ratings, play by play, etc.

	cout << "Enter 1 to view " <<matches[stoi(com) -9]->w1->name<< "'s ratings, 2 to view " << matches[stoi(com) -9]->w2->name<< "'s ratings, 3 to view the play-by-play, or 0 to go back"<< endl;
	cin >> inter;

	if (inter == 0) break;

	switch(inter){
	case 1:
	  matches[stoi(com) -9]->w1->print();
	  break;
	case 2:
	  matches[stoi(com) -9]->w2->print();
	  break;
	case 3:
	  cout << matches[stoi(com) -9]->play_by_play() << endl;
	  break;
	default:
	  break;
	}
       
	
      }
    }

    else continue;					 
    
  }
}


// Used to make player abbreviations in bracket

string indv_tourney::abbreviate(int index, bool winner){
  // If single/double digits, change spacing
  string s = " ";
  if (games >= 9) s = "";

  // Return (Match_index)-FirstFourLetters LastInit.-(Overall)--
  if (winner) return "(" + to_string(games+1) + ")-" + matches[index]->w1->name.substr(0,4) + " "+  matches[index]->w1->name[matches[index]->w1->name.find(' ')+1] + ".-(" + to_string(matches[index]->w1->overall) +")-" +s;

  return "(" + to_string(games+1) + ")-"  + matches[index]->w2->name.substr(0,4) + " "+  matches[index]->w2->name[matches[index]->w2->name.find(' ')+1] + ".-(" + to_string(matches[index]->w2->overall) +")-"+ s;
}


// Avoid changing the wrestling class which would make the dual_tourney messed up, instead, read in from a match_sim the wrestler * victor from the match_sim->winner bool.
wrestler * indv_tourney::victor(match_sim * match){
  if (match->winner) return match->w1;
  return match->w2;
}


// Sims the next game in the tourney
void indv_tourney::next_game(){
  // if first round
  if (games < 8) {
    // Specific indexing for how the matches vector is organized
    matches[games+7] = new match_sim(competitors[games], competitors[games + 8]);
    // Make them wrestler
    matches[games+7]->wrastle();
    // Make new bracket line
    bracket_lines[games + 16] = abbreviate(games+7, matches[games+7]->winner);
  }

  else if (games < 12){
    // If round of 8
    // Need very weird indexing - matches vector layout
    matches[games-8] = new match_sim(victor(matches[(2*games) -9]), victor(matches[(2*games) -8]));
    matches[games-8]->wrastle();
    bracket_lines[games + 16] = abbreviate(games-8,  matches[games-8]->winner);
    
  }

  else if (games < 14){
    // if final four
    matches[games-8] = new match_sim(victor(matches[(games*2)-24]),victor(matches[(2*games) -23]));
    matches[games-8]->wrastle();
    bracket_lines[games + 16] =  abbreviate(games-8, matches[games-8]->winner);
  }

  else{
    // if championship
    matches[6] = new match_sim(victor(matches[4]), victor(matches[5]));
    matches[6]->wrastle();
    bracket_lines[30] = "(15)" + victor(matches[6])->name.substr(0,4) + " " + victor(matches[6])->name[victor(matches[6])->name.find(' ')+1] + ". Wins! ";
    cout << victor(matches[6])->name <<" Wins!" << endl;
  }

  
games++;

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
  // Sets up matches vector, sets pointer to null, sets bracket lines back to defaults
  a_quarter = NULL;
  b_quarter = NULL;
  c_quarter = NULL;
  d_quarter = NULL;

  a_semi = NULL;
  b_semi = NULL;

  
  a_sixteen = NULL;
  b_sixteen = NULL;
  c_sixteen = NULL;
  d_sixteen = NULL;

  e_sixteen = NULL;
  f_sixteen = NULL;
  g_sixteen = NULL;
  h_sixteen = NULL;

  champ = NULL;

    

  matches.push_back(a_sixteen);
  matches.push_back(b_sixteen);
  matches.push_back(c_sixteen);
  matches.push_back(d_sixteen);
  matches.push_back(e_sixteen);
  matches.push_back(f_sixteen);
  matches.push_back(g_sixteen);
  matches.push_back(h_sixteen);


  matches.push_back(a_quarter);
  matches.push_back(b_quarter);
  matches.push_back(c_quarter);
  matches.push_back(d_quarter);

  
  matches.push_back(a_semi);
  matches.push_back(b_semi);
  matches.push_back(champ);

  prev_champ = NULL;
  
  games =0;
  bracket = "";
  
  asx = "(1)-------------- ";
  bsx = "(2)-------------- ";
  csx = "(3)-------------- ";
  dsx = "(4)-------------- ";
  esx = "(5)-------------- ";
  fsx = "(6)-------------- ";
  gsx = "(7)-------------- ";
  hsx = "(8)-------------- ";

  aq = "(9)-------------- ";
  bq = "(10)------------- ";
  cq = "(11)------------- ";
  dq = "(12)------------- ";
  
  as = "(13)------------- ";
  bs = "(14)------------- ";
  
  ch = "(15)------------- ";


  w0 = "----------------- ";
  w1 = "----------------- ";
  w2 = "----------------- ";
  w3 = "----------------- ";
  w4 = "----------------- ";
  w5 = "----------------- ";
  w6 = "----------------- ";
  w7 = "----------------- ";
  w8 = "----------------- ";
  w9 = "----------------- ";

  
  w10 = "---------------- ";
  w11 = "---------------- ";
  w12 = "---------------- ";
  w13 = "---------------- ";
  w14 = "---------------- ";
  w15 = "---------------- ";
 
}
