***** SimuladorCache *****

A cache simulator that calculates miss rates depending on asociativity, cache size and block size.

AUTHORS:

    Carlos Eduardo Solano, B36685
    Heberth Valverde, B37174

CHANGELOG:

    -v1: initial release.

REQUIREMENTS:

    -C++ compiler g++.
    -iostream, fstream, cmath, ctime, cstdlib libraries.
    -make
    
INSTALL:

    $ cd SimuladorCache
    $ make

RUN:

    All parameters are ints.
    $ ./Run  <associativity [bytes]>  <cache size [bytes]> <block size [bytes]>

    Associativity:
        1 for direct mapping.
        2 for 2-way associative.
        4 for 4-way associative.
        And so on...

If you get an error ‘to_string’ was not declared in this scope use flag -std=c++0:

    $ g++ -std=c++0x main.cpp Cache.cpp -o Run

USE: 

    $ ./Run  1  256000 8
    -Get miss rate for a cache of size 256 kB, block size of 8 B and direct mapping.

NOTE: please put and rename "*.trace" to "memory.trace" into ~/"path-to"/SimuladorCache/
