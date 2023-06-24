CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRCS_K = kruskal.c
SRCS_P = prims.c

# Object files
OBJS_K = $(SRCS_K:.c=.o)
OBJS_P = $(SRCS_P:.c=.o)

# Target executables
TARGET_K = kruskal_program
TARGET_P = prims_program

.PHONY: all clean

all: $(TARGET_K) $(TARGET_P)

$(TARGET_K): $(OBJS_K)
	$(CC) $(CFLAGS) $(OBJS_K) -o $(TARGET_K)

$(TARGET_P): $(OBJS_P)
	$(CC) $(CFLAGS) $(OBJS_P) -o $(TARGET_P)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_K) $(OBJS_P) $(TARGET_K) $(TARGET_P)
