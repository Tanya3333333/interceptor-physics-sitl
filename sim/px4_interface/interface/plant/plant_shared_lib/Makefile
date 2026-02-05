# Platform detection
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
else
    PLATFORM := linux
endif

# Compiler / target
ifeq ($(PLATFORM),windows)
    CC := x86_64-w64-mingw32-gcc
    TARGET := libPlant.dll
    PIC :=
else
    CC := gcc
    TARGET := libPlant.so
    PIC := -fPIC
endif

# Paths
PLANT_DIR := ../plant_model/quadcopter_plant_model

# Auto-find include dir
PLANT_INC := $(shell find $(PLANT_DIR) -name UAV_Dynamics.h -print -quit | xargs -r dirname)

# Flags
CFLAGS := $(PIC) -O2 -I$(PLANT_INC) -I$(PLANT_DIR)

# Sources and objects
SRC := libPlant.c
OBJ := libPlant.o

# Compile all .c files in plant model
PLANT_SRC := $(shell find $(PLANT_DIR) -name '*.c')
PLANT_OBJ := $(PLANT_SRC:.c=.o)

# Rules
all: $(TARGET)

# Build main libPlant.o
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

# Build all plant object files
$(PLANT_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link shared library
$(TARGET): $(OBJ) $(PLANT_OBJ)
	$(CC) -shared $(OBJ) $(PLANT_OBJ) -o $(TARGET)

# Clean
clean:
	rm -f $(OBJ) $(PLANT_OBJ) libPlant.so libPlant.dll
