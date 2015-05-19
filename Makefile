include Makefile.conf


SRC_DIR    = ./src
INC_DIR    = ./include
APP        = phantom

SRCS       = Server.cpp \
             Main.cpp

SOURCES   := $(foreach SRC, $(SRCS), $(SRC_DIR)/$(SRC))
INCLUDES  := $(wildcard $(INC_DIR)/*.h)
OBJECTS   := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DIRS      := $(LIB_DIR) $(OBJ_DIR) $(ENV_DIR) $(TEST_DIR)

################################################################################

all: $(OBJ_DIR) $(APP)
	@echo "--- $(LIB_NAME) Build completed ---"
	@echo "For rebuilding :-  make clean && make"

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo "[CC] $@ ..."
	@$(CC) -c $^ $(CFLAGS) -I$(INC_DIR) $(INCLUDE) -o $@ 

$(DIRS):
	@echo "Creating $@"
	mkdir -p $(DIRS)

clean:
	@echo "[RM] $(OBJECTS) ..."
	@rm -f $(OBJECTS)

distclean:
	@echo "[RM] $(DIRS) ..."
	@rm -rf $(DIRS)

$(APP): $(OBJECTS)
	@echo "[LD] $(OBJECTS)"
	@$(CC) $(OBJECTS) $(LFLAGS) $(LIBS_PATHS) -o $@
	@ln -s $(LIB_NAME)  $(SOFT_NAME)
	@mv $(SOFT_NAME) $(LIB_DIR)

tests:
	make -C test
