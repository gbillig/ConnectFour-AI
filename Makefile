CC = gcc
CFLAGS = -Wall -g -c
LD = gcc
LDFLAGS = -g
LDLIBS = -lm

OBJS = \
bin/connect_four_ai.o \
bin/heuristic.o \
bin/heuristic2.o \
bin/heuristic3.o


SRC = \
src/connect_four_ai.c \
src/heuristic.c \
src/heuristic2.c \
src/heuristic3.c

INC = \
inc/definitions.c \
inc/heuristic.c \
inc/heuristic2.c \
inc/heuristic3.c

OUT = \
bin/connect_four_ai

# All Target
all: $(OUT)

$(OUT): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f bin/*.o bin/connect_four_ai
