
all: tool mainex

tool: 
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Set.cpp -o lib/set.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Graph.cpp -o lib/graph.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Timer.cpp -o lib/time.o
		
mainex: 
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/main/Reader.cpp -o lib/reader.o
	g++ -Wextra -ansi -O3 -funroll-all-loops lib/reader.o lib/set.o lib/graph.o src/main/Main.cpp -o bin/main
