#
#  @file    makefile
#  @author  Ferenc Nemeth
#  @date    18 Nov 2018
#  @brief   Makefile for Maze generation algorithms.
# 
#           Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
# 

CXX = g++

# Every maze generation algorithm
MODULES += mazes/aldous_broder
MODULES += mazes/binary_tree
MODULES += mazes/kruskal
MODULES += mazes/prim
MODULES += mazes/recursive_backtracking
MODULES += mazes/recursive_division

# Common
MODULES += common/file_system
MODULES += common/main
MODULES += common/maze_generator

# Solver
MODULES += solver

WILDSRC  = $(addsuffix /*.cpp,$(MODULES))
SOURCES  = $(wildcard $(WILDSRC))
OBJECTS  = $(SOURCES:.cpp=.o)
DEPENDS  = $(OBJECTS:.o=.d)
INCLUDES = $(addprefix -I,$(MODULES))

CXXFLAGS = -std=c++14 -Wall -Wextra $(INCLUDES) `pkg-config --cflags opencv`
LDFLAGS = `pkg-config --libs opencv`

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o maze_generator $^ $(LDFLAGS)
	@echo "-----------"
	@echo "Build done!"
	@echo "-----------"

-include $(DEPENDS)

%.d: %.cpp
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(DEPENDS)
	rm -f maze_generator
	@echo "--------"
	@echo "Cleaned!"
	@echo "--------"

.PHONY: clean_output
clean_output:
	rm -f output/*
	@echo "--------"
	@echo "Cleaned!"
	@echo "--------"

