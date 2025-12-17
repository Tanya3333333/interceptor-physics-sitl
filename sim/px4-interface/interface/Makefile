CC=gcc
CFLAGS=-fPIC -O2 -I ../matlab-code-generated-fdm

SRC=libPlant.c
OBJ=libPlant.o

FDM_DIR=../matlab-code-generated-fdm

FDMOBJ= \
	$(FDM_DIR)/UAV_Dynamics.o \
	$(FDM_DIR)/UAV_Dynamics_data.o \
	$(FDM_DIR)/rt_nonfinite.o \
	$(FDM_DIR)/rtGetInf.o \
	$(FDM_DIR)/rtGetNaN.o 

TARGET=libPlant.so

all: $(TARGET)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(TARGET): $(OBJ) $(FDMOBJ)
	$(CC) -shared $(OBJ) $(FDMOBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
