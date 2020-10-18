# created: october 31 2019
# last updated: november 14 2019 

CC := gcc

CFLAGS := `sdl2-config --libs --cflags` -lSDL2_image -ggdb3 -O0 --std=c99 -Wall -lSDL2main -lSDL2 -lm

HDRS :=

SRCS := dvd.c

OBJS := $(SRCS:.c=.o)

EXEC := dvdlogo

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

install: 
	cp $(EXEC) /usr/bin

$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all install clean
