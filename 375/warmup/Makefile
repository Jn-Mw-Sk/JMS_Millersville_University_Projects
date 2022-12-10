########################################################
# Makefile for CSCI 375
#   In many cases you will ONLY need to modify the
#   SRCS variable below
# Author: Gary M. Zoppetti, Ph.D. and Chad Hogg
########################################################

########################################################
# Variable definitions
########################################################
# C++ compiler
CXX := g++
#CXX := clang++

# Include directories, prefaced with "-I"
INCDIRS  := 

# C++ compiler flags
# Use the first for debugging, the second for release
CXXFLAGS := -g -Wall -std=c++14 $(INCDIRS)
#CXXFLAGS := -O3 -Wall -std=c++14 $(INCDIRS)

# Linker. For C++ should be $(CXX).
LINK := $(CXX)

# Linker flags. Usually none.
LDFLAGS := 

# Library paths, prefaced with "-L". Usually none.
LDPATHS := 

UNAME := $(shell uname)
# Libraries used, prefaced with "-l".
ifeq ($(UNAME),Darwin)
LDLIBS := -framework OpenGL -lGLEW -lglfw
else
LDLIBS := -lGLEW -lglfw -lGL
endif

# All source files, separated by spaces. Don't include header files. 
SRCS := Main.cpp ShaderProgram.cpp

# All header files, separated by spaces. Don't include source files.
HDRS := ShaderProgram.hpp

# All shader files, separated by spaces.
SHDR := Vec2.vert Vec2.frag

# All files that must be submitted.
SUBMIT := $(SRCS) $(HDRS) $(SHDR) Makefile

# The name of the AutoLab course we will submit to.
COURSE := 375-s22

# The name of the current assignment.
ASSIGNMENT := a01primitives

# Extension for source files. Do NOT modify.
SOURCESUFFIX := cpp

# Determines object files based on SRCS.
OBJS := $(SRCS:.$(SOURCESUFFIX)=.o)

# Executable name. Defaults to basename of first name in SRCS.
EXEC := $(patsubst %.o, %, $(word 1, $(OBJS)))

# Command to generate dependency rules for make. 
MAKEDEPEND := $(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM -MP

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

all : $(EXEC)

$(EXEC) : $(OBJS)
	$(LINK) $(LDFLAGS) $(LDPATHS) $^ -o $@ $(LDLIBS)

-include Makefile.deps

#############################################################

.PHONY : clean submit
clean :
	$(RM) $(EXEC) $(OBJS) a.out core
	$(RM) Makefile.deps *~

submit :
	git tag $(ASSIGNMENT) -f -m "Final submission of $(ASSIGNMENT)."
	git push --tags -f
	zip handin.zip $(SUBMIT)
	autolab submit $(COURSE):$(ASSIGNMENT) handin.zip
	rm handin.zip

.PHONY :  Makefile.deps
Makefile.deps :
	$(MAKEDEPEND) $(SRCS) > $@

#############################################################
#############################################################
