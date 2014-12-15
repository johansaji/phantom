
include make.conf

all: ${APP}

$(APP):
	g++ src/ServerMain.cpp -I./include
