#To compile release version:

$make clean && make release
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG solution.cpp -o solution.o
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG walk.cpp -o walk.o
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG main.cpp -o main.o
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG saw.cpp -o saw.o
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG labssolution.cpp -o labssolution.o
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG solver.cpp -o solver.o
g++ -c -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG saj.cpp -o saj.o
g++ -std=c++0x -s -O3 -W -Wall -g0 -mtune=native -march=native -DNDEBUG solution.o walk.o main.o saw.o labssolution.o solver.o saj.o -o solvB

# To compile debug version:

$make clean && make debug
g++ -c -std=c++0x -O0 -W -Wall -g3 solution.cpp -o solution.do
g++ -c -std=c++0x -O0 -W -Wall -g3 walk.cpp -o walk.do
g++ -c -std=c++0x -O0 -W -Wall -g3 main.cpp -o main.do
g++ -c -std=c++0x -O0 -W -Wall -g3 saw.cpp -o saw.do
g++ -c -std=c++0x -O0 -W -Wall -g3 labssolution.cpp -o labssolution.do
g++ -c -std=c++0x -O0 -W -Wall -g3 solver.cpp -o solver.do
g++ -c -std=c++0x -O0 -W -Wall -g3 saj.cpp -o saj.do
g++ -std=c++0x -O0 -W -Wall -g3 solution.do walk.do main.do saw.do labssolution.do solver.do saj.do -o solvB

# Examples

$./solvB
Usage: ./solvB functionName walkName instanceDef [options]

This program takes three required argument values in this order:

    functionName walkName instanceDef

and a number of optional argument values under arbitrary order under the
following names:

    cntProbeLmt cntRestartLmt coordInit runtimeLmt seed valueTarget
    walkLengthCoef walkLengthLmt walkRestart writeInit writeStdout
    writeTrace writeWalk writeWarning

Here are examples of two invocations:

    fB.labs sawCT

    fB.labs sawCT 7 -cntProbeLmt 2000 -cntRestartLmt 100 -coordInit 0101011
		    -runtimeLmt 30 -seed 123 -valueTarget 3 -walkLengthCoef U
		    -walkRestart 0 -writeInit -writeStdout -writeTrace -writeWalk
		    -writeWarning

Argument descriptions:
    functionName ... name of the objective function to be optimized under
		    cordType=B (binary coordinates), e.g. fB.labs
    walkName ....... name of the walk to be invoked by the solver,
		    e.g. sawCT or sajJT
    instanceDef .... name of the instance to be solved, e.g. an integer
		    when the function name is fB.labs, a file name
		    when the function name is fPT.hgrPlace, etc.
		    A value of nDim, the full length of binary coordinate,
		    is extracted from instanceDef

    -cntProbeLmt    integer ... stop when this value is reached, default = 2^31 - 1
    -cntRestartLmt  integer ... stop when this value is reached, default = 2^31 - 1
    -coordInit    bitString ... initial binary string of length nDim,
				default = a random binary string
    -runtimeLmt     seconds ... stop after this number of seconds; default = 30
    -seed           integer ... **long** integer to initialize the random
				number generator; default = internal random
    -valueTarget    integer ... stop when this value is reached,
				default = internal best known value to date
    -walkLengthCoef integer ... factor that determines the value of walkLengthLmt:
				default = U, implying that walkLengthLmt = 2^31 - 1,
				otherwise walkLengthLmt = walkLengthCoef*nDim
				(nDim = full length of the binary coordinate)
    -walkLengthLmt  integer ... stop when this value is reached, default = 2^31 - 1
    -walkRestart    boolean ... the solver can restart each walk from a new random
				coordinate, default = 0
    -writeInit      boolean ... write all initialized arrays to stdout, default = 0
    -writeStdout    boolean ... write the performance summary to stdout, default = 1
    -writeTrace     boolean ... write traces to stdout, default = 0
    -writeWalk      boolean ... write tabulated walk data to file, default = 0
    -writeWarning   boolean ... write all warnings to stdout, default = 0
    -help                   ... display this help and exit.
------------------------------------------------------------------------------------------------
Copyright 2014
* Authors *
* Solver *

$ ./solvB fB.labs sawCT 13
instanceDef         13
nDim                13
nAsymp              13
functionName        fB.labs
solverName          sawCT
walkLengthCoef      U
walkLengthLmt       2147483635
walkLength          205
cntRestartLmt       2147483647
cntRestart          0
cntProbeLmt         2147483647
cntProbe            2431
runtimeLmt          30
runtime             0
speed               inf
seedFirst           42
coordInit           0011111000010
coordBest           1111100110101
valueInit           78
valueBest           6
valueTarget         6
targetReached       1
isCensored          0
hostID              x86_64-3.2.0-58-generic-Linux

$./solvB fB.labs sawCT 7  -cntProbeLmt 2000 -cntRestartLmt 100 -coordInit 0101011
	 -runtimeLmt 30 -seed 123 -valueTarget 3 -walkLengthCoef U -walkRestart 0
	 -writeInit -writeStdout -writeTrace -writeWalk -writeWarning
 # instanceDef       7
 # nDim              7
 # nAsymp            7
 # functionName      fB.labs
 # solverName        sawCT
 # walkLengthCoef    2147483647
 # walkLengthLmt     2147483641
 # cntRestartLmt     100
 # cntProbeLmt       2000
 # runtimeLmt        30
 # seedFirst         123
 # coordInit         0101011
 # valueInit         31
 # valueTarget       3
 # hostID            x86_64-3.2.0-58-generic-Linux
 step cntRestart distance coord   value neighbSize cntProbe targetReached
 0    0          0        0101011 31    0          1        0
 0    0          1        1101011 11    1          2        0
 0    0          1        0001011 7     2          3        0
 0    0          1        0111011 11    3          4        0
 0    0          1        0100011 7     4          5        0
 0    0          1        0101111 11    5          6        0
 0    0          1        0101001 23    6          7        0
 0    0          1        0101010 91    7          8        0
 1    0          0        0001011 7     0          8        0
 1    0          1        1001011 19    1          9        0
 1    0          1        0011011 19    2          10       0
 1    0          1        0000011 23    3          11       0
 1    0          1        0001111 35    4          12       0
 1    0          1        0001001 7     5          13       0
 1    0          1        0001010 19    6          14       0
 2    0          0        0001001 7     0          14       0
 2    0          1        1001001 35    1          15       0
 2    0          1        0101001 23    2          16       0
 2    0          1        0011001 35    3          17       0
 2    0          1        0000001 31    4          18       0
 2    0          1        0001101 3     5          19       1
 instanceDef         7
 nDim                7
 nAsymp              7
 functionName        fB.labs
 solverName          sawCT
 walkLengthCoef      U
 walkLengthLmt       2147483641
 walkLength          3
 cntRestartLmt       100
 cntRestart          0
 cntProbeLmt         2000
 cntProbe            19
 runtimeLmt          30
 runtime             0
 speed               inf
 seedFirst           123
 coordInit           0101011
 coordBest           0001101
 valueInit           31
 valueBest           3
 valueTarget         3
 targetReached       1
 isCensored          97
 hostID              x86_64-3.2.0-58-generic-Linux
