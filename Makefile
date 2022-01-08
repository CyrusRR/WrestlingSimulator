# Cyrus Rody-Ramazani - clr3dw - lab 10 -inlab 11/22/21
# This Makefile shows how to link assembly with C/C++

# Defines the C++ compiler we'll be using
CXX = clang++

# Defines the flags we'll be passing to the C++ compiler
CXXFLAGS =  -Wall -g

# All of the .o files for our program
OBJECTS = wrestler.o match_sim.o team.o team_duel.o tourney.o randata.o main.o indv_tourney.o meet.o

# Compile our files into a.out
a.out: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS)

# This will clean up (remove) all our object files.  The -f option
# tells rm to forcily remove the files (i.e. don't ask if they should
# be removed or not).  This removes object files (*.o) and Emacs
# backup files (*~)
clean:
	-rm *.o a.out
