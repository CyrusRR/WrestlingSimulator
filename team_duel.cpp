#include "team_duel.h"


team_duel::team_duel(team * first, team * second){
  a = first;
  b = second;
  a_score= 0;
  b_score= 0;
  for (int i =0; i< 10; i++){
    matches.push_back(new match_sim(a->lineup[i], b->lineup[i]));
    matches[i]->wrastle();
    switch (matches[i]->result){
    case 1:
      a_score +=3;
      break;
    case 2:
      b_score +=3;
      break;
    case 3:
      a_score +=4;
      break;
    case 4:
      b_score +=4;
      break;
    case 5:
      a_score +=6;
      break;
    case 6:
      b_score +=6;
      break;
    case 7:
      a_score +=5;
      break;
    case 8:
      b_score +=5;
      break;
    default:
      break;
    }
  }
  if (a_score >= b_score)  winner = first;
  else winner = second;
}

team_duel::~team_duel(){
  a = NULL;
  b = NULL;
  winner = NULL;
  for (int i = 0; i < matches.size(); i ++){
    delete matches[i];
  }
}
   


string divider = "|\n|---------------|---------------|---------------|\n|_______________|_______________|_______________|\n";


string team_duel::box_score(){
  string summary =  "\n"+ a->name +"  (" + to_string(a->team_overall)+ ") vs. "+ b->name + "  (" + to_string(b->team_overall)+ ")\n_________________________________________________\n|      125      |      133      |      141      |\n";
  for (int i=0;i<10; i++){
    summary += decision(matches[i]);
    if (i == 9) summary += "|               |               ";
    if ((i+1)%3 ==0){
      if (i != 8){
	summary += divider + "|      " + matches[i+1]->w1->weight + "      |      " + matches[i+2]->w1->weight + "      |      " + matches[i+3]->w1->weight +"      |\n";
      }
      else{
	summary += divider + "|      " + matches[i+1]->w1->weight + "      |               |               |\n";
      }
	
    }
  }

  summary +=  "|\n|_______________|_______________|_______________|\n  Final Score:  " + a->abbrv + ": " + to_string(a_score)+ ", " + b->abbrv + ": " + to_string(b_score);
  if (a_score > b_score){
    cout << "here1" << endl;
    return summary + "  " + a->abbrv +" wins!";
  }
  else if (b_score > a_score){
    cout << "here2" << endl;
    return summary + "  " + b->abbrv +" wins!";
  }
  else{
        cout << "here3" << endl;
    return summary + "  It's a tie!";
  }
}



string team_duel::decision(match_sim * match){
  switch (match->result){
  case 1:
    if (match->get_score().length() ==6){
      return "| " +a->abbrv + " RD" + match->get_score() + " ";
    }
    if (match->get_score().length() ==7){
      return "| " +a->abbrv + " RD" + match->get_score();
    }
    if (match->get_score().length() ==8){
      return "|" +a->abbrv + " RD" + match->get_score();
    }
  case 2:
    if (match->get_score().length() ==6){
      return "| " +b->abbrv + " RD" + match->get_score() + " ";
    }
    if (match->get_score().length() ==7){
      return "| " +b->abbrv + " RD" + match->get_score();
    }
    if (match->get_score().length() ==8){
      return "|" +b->abbrv + " RD" + match->get_score();
    }

  case 3:
    if (match->get_score().length() ==6){
      return "| " +a->abbrv + " MD" + match->get_score() + " ";
    }
    if (match->get_score().length() ==7){
      return "| " +a->abbrv + " MD" + match->get_score();
    }
    if (match->get_score().length() ==8){
      return "|" +a->abbrv + " MD" + match->get_score();
    }

  case 4:
    if (match->get_score().length() ==6){
      return "| " +b->abbrv + " MD" + match->get_score() + " ";
    }
    if (match->get_score().length() ==7){
      return "| " +b->abbrv + " MD" + match->get_score();
    }
    if (match->get_score().length() ==8){
      return "|" +b->abbrv + " MD" + match->get_score();
    }

  case 5:
    return "|   " +a->abbrv + " FALL   ";
  case 6:
    return "|   " +b->abbrv + " FALL   ";
    
  case 7:
    if (match->get_score().length() ==6){
      return "| " +a->abbrv + " TF" + match->get_score() + " ";
    }
    if (match->get_score().length() ==7){
      return "| " +a->abbrv + " TF" + match->get_score();
    }
    if (match->get_score().length() ==8){
      return "|" +a->abbrv + " TF" + match->get_score();
    }

  case 8:
    if (match->get_score().length() ==6){
      return "| " +b->abbrv + " TF" + match->get_score() + " ";
    }
    if (match->get_score().length() ==7){
      return "| " +b->abbrv + " TF" + match->get_score();
    }
    if (match->get_score().length() ==8){
      return "|" +b->abbrv + " TF" + match->get_score();
   
      
    }
  default:
    return "Oh shit";
  }
}




  


