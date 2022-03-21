CO := g++
FLG := -Wall -pedantic
LIB_FLG := -lsfml-graphics -lsfml-window -lsfml-system

MAIN := main

DIR = `basename $(CURDIR)`

SRC := src
OBJS := objs
BIN := bin

FILES := AVL BST Button main config Tree Visualizer

SFML_PATH_INCLUDE := dependencies/SFML-2.5.1/include
SFML_PATH_LIB := dependencies/SFML-2.5.1/lib

OBJECTS	:= $(patsubst %,$(OBJS)/%.o,$(FILES))

all: $(BIN)/$(MAIN).x

$(OBJS)/%.o: $(SRC)/%.cpp
	@$(CO) $(FLG) -c $< -o $@ -I $(SFML_PATH_INCLUDE)

$(BIN)/$(MAIN).x: $(OBJECTS)
	@$(CO) $^ -o $@ -L $(SFML_PATH_LIB) $(LIB_FLG)

run: $(BIN)/$(MAIN).x
	./$(BIN)/$(MAIN).x

clean:
	rm --force $(BIN)/*.x  $(OBJS)/*.o

tar: clean
	@(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
