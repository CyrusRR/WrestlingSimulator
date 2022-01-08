# Cyrus Rody-Ramazani - 1/8/22

# C++ compiler
CXX = clang++

# Flags 
CXXFLAGS =  -Wall -g

# .o files
OBJECTS = wrestler.o match_sim.o team.o team_duel.o tourney.o randata.o main.o indv_tourney.o meet.o

# Compile into a.out
a.out: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS)

# clean up
clean:
	-rm *.o a.out
