CC 			= cl65
CFLAGS		= 
LDFLAGS    	= 
OUTPUT		= program.prg

all: clean compile

clean:
	rm -f *.prg

compile:
	$(CC) $(CFLAGS) *.c $(LDFLAGS) -o $(OUTPUT)

run:
	x64sc -autostartprgmode 1 $(OUTPUT)

