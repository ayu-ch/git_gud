CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS = -lssl -lcrypto

SRC = main.c init.c hash_object.c cat-file.c utils.c
OBJ = $(SRC:.c=.o)
TARGET = git_gud

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./$(TARGET)

clear:
	rm -rf $(OBJ) $(TARGET)

rebuild: clean all
