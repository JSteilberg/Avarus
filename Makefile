CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++0x -pedantic -Weffc++ -Wstrict-aliasing
INC = -I./include/ 
LIB = 
COMP = $(CXX) $(CXXFLAGS) $(INC) -c

main: main.o Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
			Atlas.o Corporeal.o GameState.o Logger.o Entity.o
	$(CXX) $(CXXFLAGS) $(LIB) -o Avarus main.o \
		Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
		Atlas.o Corporeal.o GameState.o Logger.o Entity.o \
		-lsfml-graphics -lsfml-window -lsfml-system -lBox2D

main.o: src/main.cpp
	$(COMP) src/main.cpp

Game.o: src/Game.cpp
	$(COMP) src/Game.cpp

MainLoop.o: src/gamestate/MainLoop.cpp
	$(COMP) src/gamestate/MainLoop.cpp

GameState.o: src/gamestate/GameState.cpp
	$(COMP) src/gamestate/GameState.cpp

Parser.o:	src/parser/Parser.cpp
	$(COMP) src/parser/Parser.cpp

IdRegister.o: src/IdRegister.cpp
	$(COMP) src/IdRegister.cpp

Logger.o: src/Logger.cpp
	$(COMP) src/Logger.cpp

Chunk.o: src/physics/Chunk.cpp
	$(COMP) src/physics/Chunk.cpp

Corporeal.o: src/physics/Corporeal.cpp
	$(COMP) src/physics/Corporeal.cpp

DebugOverlay.o:
	$(COMP) src/DebugOverlay.cpp

Entity.o: src/physics/Entity.cpp
	$(COMP) src/physics/Entity.cpp

ObjRegister.o: src/ObjRegister.cpp
	$(COMP) src/ObjRegister.cpp

Player.o: src/physics/Player.cpp
	$(COMP) src/physics/Player.cpp

Atlas.o: src/atlas/Atlas.cpp
	$(COMP) src/atlas/Atlas.cpp


clean:
	rm -rf *.o
