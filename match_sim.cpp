// Cyrus Rody-Ramazani 1/5/22
#include <iostream>
#include <random>

#include "match_sim.h"

// Match constructor, takes in 2 wrestler *
match_sim::match_sim(wrestler * wr1, wrestler * wr2){
  w1 = wr1;
  w2 = wr2;
  // Sets result, scores, max_time, play by play, period, last overtime period
  max_time = 0;
  result = 0;
  w1_score =0;
  w2_score = 0;
  pbp = "";
  per =1;
  last_ot = false;
}

match_sim::~match_sim(){
  w1 = NULL;
  w2 = NULL;
}

void match_sim::period(int  p){
  // Takes in int p argument, 3 min first period, 2 min 2nd &3rd, 1.5 min ot
  switch(p) {
  case 1:
    time = 0;
    max_time = 175;
    neutral();
    break;
  
  case 2:// Not exactly how it works, but as simple version, wr1 starts on top first, then wr2 in period 3.
    time = 0;
    max_time = 115;
    ride_control(true);
    break;
    
  case 3:
    time = 0;
    max_time = 115;
    ride_control(false);
    break;

  case 4:
    // Not exactly how overtime rules work, but have them switch off top and bottom
    time = 0;
    max_time = 85;
    last_ot = !last_ot;
    ride_control((last_ot));
    break;
  }

}

// Method keeps track of the points, if order is true, give to wr1, else give to wr2
bool match_sim::points(int inc, bool order){
  if (order) w1_score += inc;
  else w2_score += inc;

  // Check for tech fall
  if (w1_score - w2_score >= 15) {
    result = 7;
    return false;
  }
  if (w2_score - w1_score >= 15) {
    result = 8;
    return false;
  }
  // return true if not tech fall
  return true;
   
}
// Recursive call to increase time by increments of 5 as long as time <= max_time
bool match_sim::time_increase(){
  
  if (time <= max_time){
    time += 5;
    if (rand() %10 <= 6){
      //60% chance to move to 5 more secs
      time_increase();
    }
    return true;
  }
  // quit if 
  return false;
    
}
// Convert seconds to minutes:seconds, print out string form
string match_sim::get_time(){
  if (time%60 <10){
    return " (" + to_string(time/60) + ":0" + to_string(time %60) + ")";
  }
  return " (" + to_string(time/60) + ":" +to_string(time %60) + ")";
							   
							   
}
// Prints out the final score
string match_sim::get_score(){
  return " (" + to_string(w1_score) + "-"+ to_string(w2_score) +")";
	   
}

/*


ACTUAL WRESTLING METHODS

All these method are bascially the same logic:

If random number (1 to 100) - (wrestler ability - other wrestler ability) > threshold (normally 50), then success, move to next.

Each one adds to play by play

Most take in bool argument, if true, w1 has control, or is on top, etc, if false, w2 has control or is on top.

Every one calls time_increase() to see if there's enough time left, if not, it ends.

All ones that can give points call points(int, bool)


*/

// To decide who has control to try and takedown in neutral
void match_sim::neutral(){
  if(((rand()%100) + w1->control - w2->control) > 50){
     
    if (time_increase()){
      // if w1 gets it, call takedown(true)
      pbp += w1->name + " takes control" + get_time()+ get_score()+  '\n';
      takedown(true);
    }
  }
    
  else{
    if (time_increase()){
      // if not, other person gets it.
      pbp += w2->name + " takes control" + get_time()+ get_score()+ '\n';
      takedown(false);
    }
  }
}




// Takedown method
// Compare takedown w/ defense
void match_sim::takedown(bool order){
  if (order){
    // threshold is 55, compare takedown to defense
    if (((rand() %100) + w1->takedown - w2->defense) > 55){
      if (time_increase()){
	pbp += w1->name + " takes down "+ w2->name+ get_time()+ get_score()+'\n';
	// Move to determine who has control to make a move( when w1 on top)
	if (points(2, true)) ride_control(true);
      }
    }
    else{
      // Threshold not met, back to netural
      if (time_increase()){
	pbp += w1->name + " fails to take down "+ w2->name+ get_time()+ get_score()+'\n';
	neutral();
      }
    }
  }
  else{// Same as above, w2 has control
    if (((rand() %100) + w2->takedown - w1->defense) > 55){
      if (time_increase()){
	pbp += w2->name + " takes down "+ w1->name+ get_time()+ get_score()+'\n';
	if (points(2, false)) ride_control(false);
      }
    }
    else{
      if (time_increase()){
	pbp += w2->name + " fails to take down "+ w1->name+ get_time()+ get_score()+'\n';
	neutral();
      }
    }
  }
}



// Ride control method, when wrestlers in top/bottom, determine who gets hold to make a move: Compare tcon (top control) with bcon (bottom control)
void match_sim::ride_control( bool order){
  if (order){// Threshold of 50
    if (((rand() %100) + w1->tcon - w2->bcon) > 50){
      if (time_increase()){
	pbp += w1->name + " gains control on top."+ get_time()+ get_score()+'\n';
	top(true);
      }
    }
    else{
      if (time_increase()){
	pbp += w2->name + " gains control on bottom."+ get_time()+ get_score()+'\n';
	bottom(false);
      }
    }
  }
  else{//If w2 on top
    if (((rand() %100) + w2->tcon - w1->bcon) > 50){
      if (time_increase()){
	pbp += w2->name + " gains control on top."+ get_time()+get_score()+ '\n';
	top(false);
      }
     
    }
    else{
      if (time_increase()){
	pbp += w1->name + " gains control on bottom."+  get_time()+get_score()+'\n';
	bottom(true);
      }
    }
  }
}


// Wrestler on top has control, to make an attempt to turn for pin/back points
// Compare top wrestler's turn with bottom wrestler's belly
void match_sim::top(bool order){
  if (order){// Threshold of 70
    if (((rand() %100) + w1->turn - w2->belly) > 70){
      if (time_increase()){
	pbp += w1->name + " turns " + w2->name + "!" +  get_time()+get_score()+'\n';
	turn(true);
      }
    }
    else{
      if (time_increase()){
	pbp += w1->name + " fails to turn " + w2->name + get_time()+ get_score()+'\n';
	ride_control(true);
      }
    }
  }
  else{
    if (((rand() %100) + w2->turn - w1->belly) > 70){
      if (time_increase()){
	pbp += w2->name + " turns " + w1->name + "!" +  get_time()+get_score()+'\n';
	turn(false);
      }
     
    }
    else{
      if (time_increase()){
	pbp += w2->name + " fails to turn " + w1->name +  get_time()+get_score()+'\n';
	ride_control(false);
      }
    }
  }
}

// If bottom wrestler has control. Compare bottom move with top return. For reversal, then compare bottom takedown with top return
void match_sim::bottom(bool order){
  if (order){
    
    if (((rand() %100) + w1->move - w2->ret) > 50){ //Threshold of 50 for any move to be made
     
      if (((rand() %100) + w1->takedown - w2->ret) > 60){// Subsequent threshold of 60 for reversal
	if (time_increase()){
	  pbp += w1->name + " reverses " + w2->name + "!" + get_time()+get_score()+ '\n';
	  if (points(2,true))  ride_control(true);
	}
      }

      else{
	if (time_increase()){// If doesn't make reversal thershold, get escape, go to neutral
	  pbp += w1->name + " escapes!" +  get_time()+get_score()+'\n';
	  if (points(1,true)) neutral();

	}
      }
     
    }

    else{
      if (time_increase()){// Else, return to determine ride control
	pbp += w1->name + " fails to escape from " + w2->name +  get_time()+get_score()+'\n';
	ride_control(false);
      }
    }

  }


  
  else{// Same if w2 on bottom
    if (((rand() %100) + w2->move - w1->ret) > 50){
      if (((rand() %100) + w2->takedown - w1->ret) > 60){
	if (time_increase()){
	  pbp += w2->name + " reverses " + w1->name + "!" + get_time()+ get_score()+'\n';
	  if (points(2,false)) ride_control(false);
	}
      }else{
	if (time_increase()){
	  pbp += w2->name + " escapes!" +  get_time()+get_score()+'\n';
	  if (points(1,false)) neutral();
	}
      }
    }else{
      if (time_increase()){
	pbp += w2->name + " fails to escape from " + w1->name +  get_time()+get_score()+'\n';
	ride_control(true);
      }
    }
  }
}

// If top gets control. Compare turn and belly for back points, fall and bridge for pin
void match_sim::turn(bool order){
  if (order){
   
    if (((rand() %100) + w1->turn - w2->belly) > 50){
      if (((rand() %100) + w1->turn - w2->belly) > 50){
	if (((rand() %100) + w1->fall - w2->bridge) > 70){
	  if (time_increase()){
	    pbp += w1->name + " pins " + w2->name + "!" +  get_time()+get_score()+'\n';
	    result = 5; // w1 pin result
	  }
	}
	else{
	  if (time_increase()){
	    pbp += w1->name + " gets 3 back points on " + w2->name + get_time()+ get_score()+'\n';
	    // 4 back points, return to determine control
	    if (points(4,true))ride_control(true);
	  }
	}}
      else{
	if (time_increase()){
	  pbp += w1->name + " gets 2 back points on " + w2->name +  get_time()+get_score()+'\n';// 2 back points, return to determine control
	  if (points(2,true)) ride_control(true);
	}
      }}
    else{
      if (time_increase()){
	pbp += w1->name + " gets no back points on " + w2->name +  get_time()+get_score()+'\n';
	ride_control(true);
      }
    }}
  else{// Same, if w2 on top
    if (((rand() %100) + w2->turn - w1->belly) > 50){
      if (((rand() %100) + w2->turn - w1->belly) > 50){
	if (((rand() %100) + w2->fall - w1->bridge) > 70){
	  if (time_increase()){
	    pbp += w2->name + " pins " + w1->name + "!" +  get_time()+get_score()+'\n';
	    result = 6;
	  }
	}
	else{
	  if (time_increase()){
	    pbp += w2->name + " gets 3 back points on " + w1->name + get_time()+ get_score()+'\n';
	  
	    if (points(4,false)) ride_control(false);
	  }
	}}
      else{
	if (time_increase()){
	  pbp += w2->name + " gets 2 back points on " + w1->name +  get_time()+get_score()+'\n';
		
	  if (points(2,false)) ride_control(false);
	}
      }}
    else{
      if (time_increase()){
	pbp += w2->name + " gets no back points on " + w1->name + get_time()+ get_score()+'\n';
	ride_control(false);
      }
    }}
}
    
	 
     
     
// Runs the actual wrestling

bool match_sim::wrastle(){
  winner = true;// winner is true if w1 wins, false if w2 wins(default value doens't matter
  //
  while (per <= 3 & result == 0){// Period headers
    pbp += "--------------------------------------------------\n";
    pbp += "Period " + to_string(per) + '\n';
    pbp += "--------------------------------------------------\n";
    period(per);
    per ++;
  }
  if (per >3){// If all 3 periods up and there's a tie & no pin,
    if (w1_score == w2_score && result != 6 && result != 5){//run overtime
      int ot_per = 1;
	while (w1_score == w2_score){
	  pbp += "--------------------------------------------------\n";
	  pbp += "Overtime  " + to_string(ot_per) + '\n';
	  pbp += "--------------------------------------------------\n";
	  period(4);// Immediately stop if a pin
	  if (result == 6 || result == 5) break;
	  ot_per++;
	}
    }
    if (result < 5){// if not a pin or tech fall
      if (w1_score > w2_score){// determine winner
	if ((w1_score - w2_score) >=8) result =3;// major decision
	else result = 1;
      }
      else{
	if ((w2_score - w1_score) >=8) result =4;
	else result = 2;
      }
    }
  }
  
  if (result != 0){
  switch (result)
    {// w1 wins with regular decision
    case 1:
      pbp += w1->name + " defeats " + w2->name + ", "+ to_string(w1_score) + "-" + to_string(w2_score)+"! (RD)" + '\n';
      break;// winner is already true, so not changed
	
    case 2:// w2 wins with regular decision
      pbp += w2->name + " defeats " + w1->name + ", "+ to_string(w2_score) + "-" + to_string(w1_score) +"! (RD)" + '\n';
      winner = false;
      break;

      
    case 3:// w1 wins with major decision
      pbp += w1->name + " defeats " + w2->name + ", "+ to_string(w1_score) + "-" + to_string(w2_score)+"! (MD)" + '\n';
      break;
	

    case 4: // w2 wins with major decision
      pbp += w2->name + " defeats " + w1->name + ", "+ to_string(w2_score) + "-" + to_string(w1_score) +"! (MD)" + '\n';
      winner = false;
      break;

   
    case 5:// w1 pin
      pbp += w1->name + " pins " + w2->name + "!" + '\n';
      break;

    case 6:// w2 pin
      pbp += w2->name + " pins " + w1->name + "!" + '\n';
      winner = false;
      break;
      
    case 7:// w1 techfall
      pbp += w1->name + " tech-falls " + w2->name + ", " + to_string(w1_score) + "-" + to_string(w2_score) + "!" + '\n';
      break;
      
    case 8:// w2 techfall
      pbp += w2->name + " tech-falls " + w1->name + ", " + to_string(w2_score) + "-" + to_string(w1_score) + "!" + '\n';
      winner = false;
      break;
    }
   
      

    
 }
 return winner;
}

// returns a string of playbyplay
string match_sim::play_by_play(){
  return pbp;
}


  


