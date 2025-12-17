CC=gcc
CFLAGS=-fPIC -O2 -I ../simulink_plant-model

SRC=libPlant.c
OBJ=libPlant.o

FDM_DIR=../simulink_plant-model

FDMOBJ= \
	$(FDM_DIR)/UAV_Dynamics.o

TARGET=libPlant.so

all: $(TARGET)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(TARGET): $(OBJ) $(FDMOBJ)
	$(CC) -shared $(OBJ) $(FDMOBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
