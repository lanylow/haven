CC = g++

PATH_BUILD := build
PATH_SRC := src

SRC := $(shell find ${PATH_SRC} -name '*.cpp' | sort)
OBJ := $(patsubst ${PATH_SRC}/%.cpp, $(PATH_BUILD)/%.o, $(SRC))

all: haven

haven: $(OBJ)
	$(CC) $(LDFLAGS) -o $(PATH_BUILD)/$@ $(OBJ)

$(PATH_BUILD)/%.o: $(PATH_SRC)/%.cpp | $(PATH_BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PATH_BUILD):
	mkdir -p $(patsubst $(PATH_SRC)%, $(PATH_BUILD)%, $(shell find $(PATH_SRC) -type d))

.PHONY: all