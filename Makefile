
OBJ_DIR=obj_bin
SRC_DIR=src
INC_DIR=./include

INCLUDES=-I$(INC_DIR)
LIBS=-L./ -lmongoose


OBJS = $(OBJ_DIR)/ServerMain.o \
       $(OBJ_DIR)/HTTPServer.o \
       $(OBJ_DIR)/HTTPRequest.o


include make.conf
CPPFLAGS+=$(INCLUDES)
LDFLAGS+=$(LIBS)

.PHONY: clean

all: ${APP}

$(OBJ_DIR)/%.o :$(SRC_DIR)/%.cpp
	@echo "[cc] $<"
	@$(CC) -o $@ -c $< $(CPPFLAGS) $(CCFLAGS)

$(APP): $(OBJ_DIR) ${OBJS}
	@echo "Linking $@"
	@$(CC) -o $@ ${OBJS} $(LDFLAGS)

$(OBJ_DIR):
	mkdir -p $@

clean:
	@echo "Cleaning....."
	@rm -rf ${APP} $(OBJ_DIR)
