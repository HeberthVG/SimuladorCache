#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#ifndef CACHE_H
#define CACHE_H

struct block{
    int Boffset, tag, index, data;
};

class Cache{
public:
	Cache(int blockSize, int CSize);
	///
	Cache(int blockSize, int CSize, int asoc);
	///constructor de copia.
	~Cache();
	///destructor del objeto.
    block read(int dir);
    //Lee el bloque en la dirección dir.
    void write(int dir);
    //Escribe en un bloque en la dirección dir.
	
	
private:
	int blockSize, cacheSize, bNum, asoc, sets, hit, miss;
	block *mem;
    block **mema;
};
#endif