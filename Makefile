TARGET = simulador

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

COMPILER = g++
FLAGS = -Wall
LIBS = -lGL -lGLEW -lglfw

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	@echo "Compiling $(TARGET)."
	@$(COMPILER) $(OBJS) -o $(TARGET) $(LIBS)
	@echo "File $(TARGET) Compiled."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Building $@."
	@mkdir -p $(BUILD_DIR)
	@$(COMPILER) $(FLAGS) -I$(INCLUDE_DIR) -c $< -o $@
	@echo "File $@ Builded."

objs: $(TARGET)
	@echo "Objects made."

run: objs
	@echo "Runing aplication."
	@./$(TARGET)
	@echo "Aplication finished."

clean:
	@echo "Cleaning objects"
	@rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Objects cleaned."

debug: clean
debug: FLAGS += -DDEBUG 
debug: run

.PHONY: clean run help
