RM := rm -rf
MK := mkdir
CP := cp -v

CFLAGS := -c

BUILD_DIR := _build
RELEASE_DIR := /usr/local/bin
OUTPUT_BIN := yahtzee

INCLUDE_PATH := 

SOURCE_FILES := main.cpp
SOURCE_FILES += Dice.cpp
SOURCE_FILES += HumanPlayer.cpp
SOURCE_FILES += Player.cpp
SOURCE_FILES += Score.cpp
SOURCE_FILES += Yahtzee.cpp

SOURCE_OBJECTS := $(addprefix $(BUILD_DIR)/, $(SOURCE_FILES:.cpp=.o) )

all: release

debug: CFLAGS += -DDEBUG -g -O0
debug: clean $(BUILD_DIR)/$(OUTPUT_BIN)

release: CFLAGS += -DNDEBUG -O3
release: clean $(BUILD_DIR)/$(OUTPUT_BIN)

.PHONY: install
install: release
	sudo $(CP) $(BUILD_DIR)/$(OUTPUT_BIN) $(RELEASE_DIR)/$(OUTPUT_BIN)

$(BUILD_DIR):
	$(MK) $@

$(BUILD_DIR)/%.o: %.cpp
	c++ $(CFLAGS) $(INCLUDE_PATH) -M $< -MF $(@:.o=.d) -MT $@
	c++ $(CFLAGS) $(INCLUDE_PATH) -c -o $@ $<

$(BUILD_DIR)/$(OUTPUT_BIN): $(BUILD_DIR) $(SOURCE_OBJECTS)
	c++ $(LDFLAGS) $(SOURCE_OBJECTS) -o $@

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)
