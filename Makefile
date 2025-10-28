CC = gcc

CFLAGS = -Wall -Wextra 
LDFLAGS = -lSDL2 -lm

TARGET = first

SRC = main.c raycasting.c counting_angles.c graphics.c movement.c map.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

 
all: $(OBJ_DIR) $(TARGET)
 
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@ 

$(OBJ_DIR)/main.o: main.c includes.h raycasting.h counting_angles.h graphics.h movement.h
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)/movement.o: movement.c includes.h raycasting.h movement.h counting_angles.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/raycasting.o: raycasting.c includes.h map.h counting_angles.h graphics.h drawing_data.h raycasting.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/counting_angles.o: counting_angles.c includes.h counting_angles.h raycasting.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/graphics.o: graphics.c includes.h graphics.h drawing_data.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/map.o: map.c map.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ_DIR)


