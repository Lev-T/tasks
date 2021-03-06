#
# @file Makefile
# Makefile for programming tasks of ILab Compiler project
# @author Boris Shurygin
#
# Main targets are:
#   all - build all targets in debug and release modes
#   debug - build debug vesion of all targets
#   release - build release version all targets
#   doc - run doxygen to generate documentation from source code
#
#   targets are buit in two steps:
#     1. Generate additional .dep files
#     2. Compile all .cpp to .o
#     3. Link .o files into targets
#

# Tools
CC      = gcc
CXX     = g++
PERL     = perl
MKDIR   = mkdir
RM      = rm
GREP    = grep
TOUCH   = touch
DOXYGEN = doxygen
LEX     = flex++
CTAGS   = ctags

#Directories
BIN_DIR := bin
BUILD_DIR := build
OBJECT_DIR := $(BUILD_DIR)/objects
SOURCES := sources
DEBUG_OBJECTS_DIR := $(OBJECT_DIR)/debug
RELEASE_OBJECTS_DIR := $(OBJECT_DIR)/release
LEX_TARGET_DIR = $(BUILD_DIR)/lex_targets

#Source files excluded from build.
#Use carefully each file name matches as a substring, specify directory for better results
EXCLUDED_CPP=

#Macros for fitering, example $(call FILTER_OUT,g, seven eight nine ten)
FILTER = $(foreach filter,$(1),$(foreach substr,$(2),$(if $(findstring $(filter),$(substr)),$(substr),)))
FILTER_OUT = $(filter-out $(call FILTER,$(1),$(2)),$(2))

#Includes
RELEASE_INCLUDE_FLAGS = 
DEBUG_INCLUDE_FLAGS = 

# Final debug and release flags
DEBUG_OPT_FLAGS = -g -O0 -D_DEBUG -MMD -MP
RELEASE_OPT_FLAGS = -O3 -MMD -MP

DEBUG_CPPFLAGS = $(DEBUG_OPT_FLAGS) $(DEBUG_INCLUDE_FLAGS)
RELEASE_CPPFLAGS = $(RELEASE_OPT_FLAGS) $(RELEASE_INCLUDE_FLAGS)

# Library sets for debug and release
DEBUG_LIB_NAMES = #rt
RELEASE_LIB_NAMES = #rt

DEBUG_LIB_DIRS = -L/usr/lib
RELEASE_LIB_DIRS = -L/usr/lib

DEBUG_LIBS = $(addprefix -l, $(DEBUG_LIB_NAMES))
DEBUG_LIB_FLAGS =
RELEASE_LIBS = $(addprefix -l, $(RELEASE_LIB_NAMES))
RELEASE_LIB_FLAGS =

# Contains all names of .lex files
LEX_FILES:=$(wildcard $(SOURCES)/*/*.lex)
# Change suffix .lex to _lex.cpp, this creates .cpp targets so flex-generated
# sources could be updated once we modify .lex files
LEX_TARGETS=$(LEX_FILES:.lex=_lex.cpp)

# Uses wildecard to create a string containing all the project headers with their relative paths	
HEADERS:= $(wildcard $(SOURCES)/*/*.h wildcard $(SOURCES)/*/*.hpp)

# Obtain string with all the *.cpp/*.c source files in project
SOURCES_CPP_ALL:= $(wildcard $(SOURCES)/*/*.cpp $(SOURCES)/*/*.c) 
SOURCES_CPP_WO_LEX:=$(call FILTER_OUT,$(LEX_TARGETS),$(SOURCES_CPP_ALL))
SOURCES_CPP:= $(call FILTER_OUT,$(EXCLUDED_CPP),$(SOURCES_CPP_WO_LEX)) $(LEX_TARGETS)

# Target directories
TARGET_DIRS:= UnitTest

DEBUG_SRC_NAMES= $(patsubst $(SOURCES)/%,$(DEBUG_OBJECTS_DIR)/%,$(SOURCES_CPP))
DEBUG_OBJS = $(DEBUG_SRC_NAMES:.cpp=.o)
DEBUG_DEPS = $(DEBUG_SRC_NAMES:.cpp=.d)
DEBUG_LIB_OBJS = $(call FILTER_OUT,$(TARGET_DIRS),$(DEBUG_OBJS))

RELEASE_SRC_NAMES= $(patsubst $(SOURCES)/%,$(RELEASE_OBJECTS_DIR)/%,$(SOURCES_CPP))
RELEASE_OBJS = $(RELEASE_SRC_NAMES:.cpp=.o)
RELEASE_DEPS = $(RELEASE_SRC_NAMES:.cpp=.d)
RELEASE_LIB_OBJS = $(call FILTER_OUT,$(TARGET_DIRS),$(RELEASE_OBJS))
	
# All build targets
all: release debug

# Build tags
tags: $(SOURCES_CPP_WO_LEX)
	@echo [tags]
	@$(CTAGS) -R --c++-kinds=+p --fields=+iaS --extra=+q --tag-relative=yes -f $(SOURCES)/tags $(SOURCES)

#
# Cleanup routines
#
.PHONY: clean clean_lex clean_bin clean_objs

clean: clean_lex clean_bin clean_objs clean_tags
clean_lex:
	$(eval EXISTING_LEX_CPP = $(wildcard $(SOURCES)/*/*_lex.cpp))
	-$(RM) -f $(EXISTING_LEX_CPP)
clean_bin:
	-$(RM) -rf $(BIN_DIR)
clean_objs:
	-$(RM) -rf $(OBJECT_DIR)
clean_tags:
	-$(RM) -rf tags

# Debug targets
debug: utestd  
utestd: gen utestd_link

# Additional generation target (if ever needed)
gen: lex

# Release targets
release: utest

utest: gen utest_link

#
# Linking targets for debug and release modes
#
utestd_link: $(DEBUG_OBJS)
	@echo [linking] $(BIN_DIR)/utestd
	@$(MKDIR) -p $(BIN_DIR)
	@$(CXX) $(DEBUG_LIB_FLAGS) -o $(BIN_DIR)/utestd $(DEBUG_OBJS) $(DEBUG_LIB_DIRS) $(DEBUG_LIBS)

utest_link: $(RELEASE_OBJS)
	@echo [linking] $(BIN_DIR)/utest
	@$(MKDIR) -p $(BIN_DIR)
	@$(CXX) $(RELEASE_LIB_FLAGS) -o $(BIN_DIR)/utest $(RELEASE_OBJS) $(RELEASE_LIB_DIRS) $(RELEASE_LIBS)

#
# Generation of cpp files with flex
#
lex: $(LEX_TARGETS)

# Rule for flex++ run
$(SOURCES)/%_lex.cpp: $(SOURCES)/%.lex
	@echo [flex++] $*_lex.cpp
	@$(LEX) -o $(SOURCES)/$*_lex.cpp $<
	@$(TOUCH) $@

#
# Rules that run CPP compiler
#
#Dependences generation for debug mode
#$(DEBUG_OBJECTS_DIR)/%.d: $(SOURCES)/%.cpp
#	@echo [generating deps] from $*.cpp to $@
#	@$(MKDIR) -p $(dir $@)
#	@$(CXX) -MM $(DEBUG_CPPFLAGS) $< -MF $@ -MT "$@ $(@:.d=.o)"
#	@$(TOUCH) $@

-include $(DEBUG_DEPS)

#Objects generation for debug mode
$(DEBUG_OBJECTS_DIR)/%.o: $(SOURCES)/%.cpp
	@echo [compiling] $*.cpp to $@
	@$(MKDIR) -p $(dir $@)
	@$(CXX) -c $(DEBUG_CPPFLAGS) $< -o $@
	@$(TOUCH) $@


#Dependences generation for release mode
#$(RELEASE_OBJECTS_DIR)/%.d: $(SOURCES)/%.cpp
#	@echo [generating deps] from $*.cpp to $@
#	@$(MKDIR) -p $(dir $@)
#	@$(CXX) -MM $(RELEASE_CPPFLAGS) $< -MF $@ -MT "$@ $(@:.d=.o)"
#	@$(TOUCH) $@

-include $(RELEASE_DEPS)

#Objects generation for release mode
$(RELEASE_OBJECTS_DIR)/%.o: $(SOURCES)/%.cpp
	@echo [compiling] $*.cpp to $@
	@$(MKDIR) -p $(dir $@)
	@$(CXX) -c $(RELEASE_CPPFLAGS) $< -o $@	
	@$(TOUCH) $@

#
# Documentation
#
doc: 
	@echo [doxygen]
	@cd autodoc;$(DOXYGEN) Doxyfile


#$(eval EXISTING_MOCS = $(wildcard $(SOURCES)/*/*_moc.cpp))
#$(eval EXISTING_RESOURCES = $(RESOURCES:.qrc=.cpp))
#-$(RM) -f $(EXISTING_RESOURCES)
#-$(RM) -f $(EXISTING_MOCS)




