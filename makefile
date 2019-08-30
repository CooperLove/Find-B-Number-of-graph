#cplex addresses!!!
#folder include
INCCPLEX= -I/opt/ibm/ILOG/CPLEX_Studio1251/cplex/include/
#folder lib
LIBCPLEX= -L/opt/ibm/ILOG/CPLEX_Studio1251/cplex/lib/x86-64_sles10_4.1/static_pic/ -m64 -lcplex -lm -lpthread
#folder concert
CONCPLEX= -I/opt/ibm/ILOG/CPLEX_Studio1251/concert/include/

all: solver tool mainex

solver:
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/Colorable.cpp -o lib/col.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/Enumeration.cpp -o lib/enum.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/solver/TreeNode.cpp -o lib/tnode.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/solver/VertexOrder.cpp -o lib/vord.o
	
tool: 
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Set.cpp -o lib/set.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Graph.cpp -o lib/graph.o
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Timer.cpp -o lib/time.o
		
mainex: 
	g++ -std=gnu++11 -c -Wextra -ansi -O3 -funroll-all-loops src/main/Reader.cpp -o lib/reader.o
	g++ -std=gnu++11 -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) lib/reader.o lib/set.o lib/graph.o lib/col.o lib/enum.o lib/tnode.o lib/vord.o src/main/Main.cpp -o bin/main2 $(LIBCPLEX)
