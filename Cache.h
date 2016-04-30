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
	
	
private:
	int blockSize, cacheSize, bNum, asoc, sets, hit, miss;
	block *mem;
    block **mema;
};
#endif