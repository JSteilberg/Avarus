CXX = clang++
CXXFLAGS = -Wall -Wextra -g -std=c++0x -pedantic -Wstrict-aliasing
INC = -I./include/ 
LIB = -L./lib/
COMP = $(CXX) $(CXXFLAGS) $(INC) -c

main: main.o Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
			Atlas.o GameState.o Logger.o Entity.o ConfigLoader.o
	$(CXX) $(CXXFLAGS) $(LIB) -o Avarus main.o \
		Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
		Atlas.o GameState.o Logger.o Entity.o ConfigLoader.o \
		-lsfml-graphics -lsfml-window -lsfml-system -lBox2D

tools: KeyCode.o Logger.o
	$(CXX) $(CXXFLAGS) $(LIB) -o KeyCode KeyCode.o Logger.o \
	-lsfml-graphics -lsfml-window -lsfml-system

KeyCode.o: src/tools/KeyCode.cpp
	$(COMP) src/tools/KeyCode.cpp

main.o: src/main.cpp
	$(COMP) src/main.cpp

Game.o: src/Game.cpp
	$(COMP) src/Game.cpp

MainLoop.o: src/gamestate/MainLoop.cpp include/MainLoop.h
	$(COMP) src/gamestate/MainLoop.cpp

GameState.o: src/gamestate/GameState.cpp include/GameState.h
	$(COMP) src/gamestate/GameState.cpp

Parser.o:	src/parser/Parser.cpp include/Parser.h
	$(COMP) src/parser/Parser.cpp

IdRegister.o: src/IdRegister.cpp include/IdRegister.h
	$(COMP) src/IdRegister.cpp

Logger.o: src/Logger.cpp include/Logger.h
	$(COMP) src/Logger.cpp

Chunk.o: src/physics/Chunk.cpp include/Chunk.h
	$(COMP) src/physics/Chunk.cpp

DebugOverlay.o: src/DebugOverlay.cpp include/DebugOverlay.h
	$(COMP) src/DebugOverlay.cpp

Entity.o: src/physics/Entity.cpp include/Entity.h
	$(COMP) src/physics/Entity.cpp

ObjRegister.o: src/ObjRegister.cpp include/ObjRegister.h
	$(COMP) src/ObjRegister.cpp

Player.o: src/physics/Player.cpp include/Player.h
	$(COMP) src/physics/Player.cpp

Atlas.o: src/atlas/Atlas.cpp include/Atlas.h
	$(COMP) src/atlas/Atlas.cpp

ConfigLoader.o: src/parser/ConfigLoader.cpp include/ConfigLoader.h
	$(COMP) src/parser/ConfigLoader.cpp


clean:
	rm -rf *.o
