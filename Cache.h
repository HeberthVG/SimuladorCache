#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#ifndef CACHE_H
#define CACHE_H

struct block{
    int tag;
};

class Cache{
public:
	Cache(int blockSize, int CSize);
	///
	Cache(int blockSize, int CSize, int asoc);
	///constructor de copia.
	//~Cache();
	///destructor del objeto.
    block read(int index, int asoc);
    //Lee el bloque.
    void write(int index, int asoc, int tag);
    //Escribe en un bloque en la dirección dir.
    void hitp();
    void missp();
    //Incrementa el contador del miss o el hit
    int gethit();
    int getmiss();
    //Devuelve la cantidad de hit o miss.
    
	
	
private:
	int blockSize, cacheSize, bNum, asoc, bsets, hit, miss, boffset, bindex, btag;
	block *mem;
    block **mema;
};
#endif
