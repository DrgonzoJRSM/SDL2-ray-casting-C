CC = gcc

CFLAGS = -Wall -Wextra 
LDFLAGS = -lSDL2 -lSDL2_image -lm

TARGET = first

SRC = main.c raycasting.c counting_angles.c graphics.c movement.c map.c

OBJ_DIR = obj_files
HEADER_DIR = header_files
SRC_DIR = src_files

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(OBJ_DIR) $(TARGET)
 
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@ 

$(OBJ_DIR)/main.o: main.c $(HEADER_DIR)/config.h $(HEADER_DIR)/includes.h $(HEADER_DIR)/raycasting.h $(HEADER_DIR)/counting_angles.h $(HEADER_DIR)/graphics.h $(HEADER_DIR)/movement.h
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)/movement.o: $(SRC_DIR)/movement.c $(HEADER_DIR)/movement.h $(HEADER_DIR)/includes.h $(HEADER_DIR)/raycasting.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/raycasting.o: $(SRC_DIR)/raycasting.c $(HEADER_DIR)/raycasting.h $(HEADER_DIR)/config.h $(HEADER_DIR)/includes.h $(HEADER_DIR)/map.h $(HEADER_DIR)/counting_angles.h $(HEADER_DIR)/graphics.h $(HEADER_DIR)/drawing_data.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/counting_angles.o: $(SRC_DIR)/counting_angles.c $(HEADER_DIR)/counting_angles.h $(HEADER_DIR)/config.h $(HEADER_DIR)/includes.h $(HEADER_DIR)/raycasting.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/graphics.o: $(SRC_DIR)/graphics.c $(HEADER_DIR)/graphics.h $(HEADER_DIR)/config.h $(HEADER_DIR)/includes.h $(HEADER_DIR)/drawing_data.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/map.o: $(SRC_DIR)/map.c $(HEADER_DIR)/map.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ_DIR)


