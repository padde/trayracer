################################################################################
# MAKEFILE FOR RAYTRACER
# 
################################################################################
# Author:      Patrick Oscity
#              Bauhaus-Universitaet Weimar
# Last change: 2010-01-22
# 
################################################################################
# This Makefile is written for GNU Make under Mac OS X 10.6
# 
################################################################################
# The needed libraries can be installed with MacPorts:
# ~$ sudo port install mesa
# ~$ sudo port install boost
# ~$ sudo port install unittest-cpp



################################################################################
# default target

default: build



################################################################################
# global variables

INC_PATH =./include
SRC_PATH =./src
OBJ_PATH =./build



################################################################################
# compiler

CXX =g++
CXX_FLAGS =-Wall
# CXX_FLAGS =-Wall -pedantic -O3 -fast -D NDEBUG
INCLUDE =\
	-I/opt/local/include/ \
	-I/private/var/lib/unittest++/src/ \
	-I$(INC_PATH)/datatypes/ \
	-I$(INC_PATH)/shape/ \
	-I$(INC_PATH)/file/ \
	-I$(INC_PATH)/glut/ \
	$(NULL)


################################################################################
# linker

LIB =-lGL -lglut -lunittest++ -lboost_thread-mt
LIB_PATH =-L/opt/local/lib/



################################################################################
# removing files

RM =rm -f



################################################################################
# all targets

HEADER =\
	$(INC_PATH)/datatypes/rgb.hpp \
	$(INC_PATH)/datatypes/pixel.hpp \
	$(INC_PATH)/datatypes/point.hpp \
	$(INC_PATH)/datatypes/vector.hpp \
	$(INC_PATH)/datatypes/ray.hpp \
	$(INC_PATH)/datatypes/matrix.hpp \
	$(INC_PATH)/datatypes/orthonormalbasis.hpp \
	$(INC_PATH)/shape/shape.hpp \
	$(INC_PATH)/shape/sphere.hpp \
	$(INC_PATH)/shape/triangle.hpp \
	$(INC_PATH)/file/ppmwriter.hpp \
	$(INC_PATH)/glut/glutwindow.hpp \
	$(NULL)

SOURCE =$(HEADER:$(INC_PATH)%.hpp=$(SRC_PATH)%.cpp)

OBJECT =$(SOURCE:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)



################################################################################
# main

MAIN_SOURCE =\
	$(SRC_PATH)/try.cpp \
	$(NULL)

MAIN_OBJECT =$(MAIN_SOURCE:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)

MAIN_OUTPUT =$(OBJ_PATH)/try.out

main: $(OBJECT) $(MAIN_OBJECT)
	$(CXX) $(OBJECT) $(MAIN_OBJECT) $(LIB) $(LIB_PATH) -o $(MAIN_OUTPUT)
	$(MAIN_OUTPUT)



################################################################################
# test

TEST_SOURCE =\
	$(SRC_PATH)/test/test.cpp \
	$(SRC_PATH)/test/test_point.cpp \
	$(SRC_PATH)/test/test_vector.cpp \
	$(SRC_PATH)/test/test_ray.cpp \
	$(SRC_PATH)/test/test_matrix.cpp \
	$(SRC_PATH)/test/test_orthonormalbasis.cpp \
	$(NULL)

TEST_OBJECT =$(TEST_SOURCE:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)

TEST_OUTPUT =$(OBJ_PATH)/test/test.out

test: $(OBJECT) $(TEST_OBJECT)
	$(CXX) $(OBJECT) $(TEST_OBJECT) $(LIB) $(LIB_PATH) -o $(TEST_OUTPUT)
	$(TEST_OUTPUT)



################################################################################
# (clean and) build everything

build: test main

cleanbuild: realclean build clean



################################################################################
# routines for building objects

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c $< -o $@



################################################################################
# clean routines

.PHONY: clean
clean:
	-$(RM) $(OBJECT) $(TEST_OBJECT) $(MAIN_OBJECT)

.PHONY: realclean
realclean: clean
	-$(RM) $(TEST_OUTPUT) $(MAIN_OUTPUT)


