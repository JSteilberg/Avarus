CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++1z -pedantic -Wstrict-aliasing -Weffc++
INC = -I./include/ -I./lua_jit
LIB = -L./lib/
COMP = $(CXX) $(CXXFLAGS) $(INC) -c

macos: main.o Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
			Atlas.o GameState.o Logger.o Entity.o ConfigLoader.o Console.o \
			ConsoleLoop.o EditableBuffer.o TextBox.o LuaHost.o
	$(CXX) $(CXXFLAGS) $(LIB) -o Avarus.out main.o \
		Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
		Atlas.o GameState.o Logger.o Entity.o ConfigLoader.o Console.o \
		ConsoleLoop.o EditableBuffer.o TextBox.o LuaHost.o \
		-lsfml-graphics -lsfml-window -lsfml-system -lBox2D -lluajit -pagezero_size 10000 -image_base 100000000

linux: main.o Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
			Atlas.o GameState.o Logger.o Entity.o ConfigLoader.o Console.o \
			ConsoleLoop.o EditableBuffer.o TextBox.o LuaHost.o
	$(CXX) $(CXXFLAGS) $(LIB) -o Avarus.out main.o \
		Game.o MainLoop.o Parser.o IdRegister.o Player.o DebugOverlay.o \
		Atlas.o GameState.o Logger.o Entity.o ConfigLoader.o Console.o \
		ConsoleLoop.o EditableBuffer.o TextBox.o LuaHost.o \
		-lsfml-graphics -lsfml-window -lsfml-system -lBox2D -lluajit -ldl


tools: KeyCode.o Logger.o
	$(CXX) $(CXXFLAGS) $(LIB) -o KeyCode.out KeyCode.o Logger.o \
	-lsfml-graphics -lsfml-window -lsfml-system

KeyCode.o: src/tools/KeyCode.cpp
	$(COMP) src/tools/KeyCode.cpp

main.o: src/main.cpp
	$(COMP) src/main.cpp

Game.o: src/Game.cpp include/Game.hpp
	$(COMP) src/Game.cpp

MainLoop.o: src/gamestate/MainLoop.cpp include/MainLoop.hpp
	$(COMP) src/gamestate/MainLoop.cpp

GameState.o: src/gamestate/GameState.cpp include/GameState.hpp
	$(COMP) src/gamestate/GameState.cpp

Parser.o:	src/parser/Parser.cpp include/Parser.hpp
	$(COMP) src/parser/Parser.cpp

IdRegister.o: src/IdRegister.cpp include/IdRegister.hpp
	$(COMP) src/IdRegister.cpp

Logger.o: src/Logger.cpp include/Logger.hpp
	$(COMP) src/Logger.cpp

Chunk.o: src/physics/Chunk.cpp include/Chunk.hpp
	$(COMP) src/physics/Chunk.cpp

DebugOverlay.o: src/gui/DebugOverlay.cpp include/DebugOverlay.hpp
	$(COMP) src/gui/DebugOverlay.cpp

Entity.o: src/physics/Entity.cpp include/Entity.hpp
	$(COMP) src/physics/Entity.cpp

ObjRegister.o: src/ObjRegister.cpp include/ObjRegister.hpp
	$(COMP) src/ObjRegister.cpp

Player.o: src/physics/Player.cpp include/Player.hpp
	$(COMP) src/physics/Player.cpp

Atlas.o: src/atlas/Atlas.cpp include/Atlas.hpp
	$(COMP) src/atlas/Atlas.cpp

ConfigLoader.o: src/parser/ConfigLoader.cpp include/ConfigLoader.hpp
	$(COMP) src/parser/ConfigLoader.cpp

Console.o: src/gui/Console.cpp include/Console.hpp
	$(COMP) src/gui/Console.cpp

ConsoleLoop.o: src/gamestate/ConsoleLoop.cpp include/ConsoleLoop.hpp
	$(COMP) src/gamestate/ConsoleLoop.cpp

EditableBuffer.o: src/gui/EditableBuffer.cpp include/EditableBuffer.hpp
	$(COMP) src/gui/EditableBuffer.cpp

TextBox.o: src/gui/TextBox.cpp include/TextBox.hpp
	$(COMP) src/gui/TextBox.cpp

LuaHost.o: src/lua/LuaHost.cpp include/LuaHost.hpp
	$(COMP) src/lua/LuaHost.cpp

clean:
	rm -rf *.o
