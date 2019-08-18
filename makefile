
all: tool mainex

tool: 
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Set.cpp -o lib/set.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Graph.cpp -o lib/graph.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Timer.cpp -o lib/time.o
		
mainex: 
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/main/Reader.cpp -o lib/reader.o
	g++ -std=gnu++11 -Wextra -ansi -O3 -funroll-all-loops lib/reader.o lib/set.o lib/graph.o src/main/Main.cpp -o bin/main
