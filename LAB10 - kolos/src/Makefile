SRC_DIR = sources

all:
	g++ -I include -L lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
run: all
	./main.exe
clean:
	del main.exe