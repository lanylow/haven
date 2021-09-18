PATH_BUILD := build
PATH_SRC := src

SRC := $(shell find ${PATH_SRC} -name '*.cpp' | sort)
OBJ := $(patsubst ${PATH_SRC}/%.cpp, $(PATH_BUILD)/%.o, $(SRC))

all: clean haven

clean:
	rm -rf ./build

haven: $(OBJ)
	g++ $(LDFLAGS) -std=c++17 -s -O3 -o $(PATH_BUILD)/$@ $(OBJ)

$(PATH_BUILD)/%.o: $(PATH_SRC)/%.cpp | $(PATH_BUILD)
	g++ $(CFLAGS) -std=c++17 -c -o $@ $<

$(PATH_BUILD):
	mkdir -p $(patsubst $(PATH_SRC)%, $(PATH_BUILD)%, $(shell find $(PATH_SRC) -type d))

.PHONY: all