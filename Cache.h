#ifndef CACHE_H
#define CACHE_H

class Cache{
public:
	Cache(int blockSize, int CSize);
	///
	Cache(const Cache &m);
	///constructor de copia.
	~Cache();
	///destructor del objeto.
	
	
private:
	int blockSize, cacheSize, bNum, asoc, sets, hit, miss;
	int memx[][];
	float **ptr_data;
};

class Cache{
public:
	Cache(int blockSize, int CSize);
	///
	Cache(const Cache &m);
	///constructor de copia.
	~Cache();
	///destructor del objeto.
	
	
private:
	int blockSize, cacheSize, bNum, asoc, sets, hit, miss;
	int memx[][];
	float **ptr_data;
};

struct block{
	int Boffset, tag, index;
};
#endif