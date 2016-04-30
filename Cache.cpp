/*
    Universidad de Costa Rica
    Escuela de Ingeniería Eléctrica
    Estructuras de Computadoras Digitales II
    IE-0521
    Tarea Programada 1
    Carlos Solano       B36685
    Heberth Valverde    B37174
*/

// Simulador de una memoria caché

#include "Cache.h"

using namespace std;


 Cache::Cache(int bS, int S)
 {
	this->blockSize=bS;
	this->cacheSize=S;
	this->bNum=S/bS;
     
     mem=new block [bNum];
     block l={0};
     //Inicializar cache
     for(int a=0;a<bNum;a++)
     {
         this->mem[a]= l;
     }
 }

Cache::Cache(int bS, int S, int as)
{
    //Parametros del cache.
    this->blockSize=bS;
    this->cacheSize=S;
    this->bNum=S/bS;
    this->asoc=as;
    if(asoc>0){
        this->bsets=bNum/as;
    }
    else this->bsets=bNum;
    //Inicializa los contadores de misses y hits.
    this->hitR=0;
    this->missR=0;
    this->hitW=0;
    this->missW=0;
    //Cantidad de bits necesarios por bloque.
    this->boffset=log2(bS);
    this->bindex=log2(bsets);
    this->btag=bS-bindex-boffset;
    
    //Se crea la matriz.
    mema=new block *[bsets];
    for(int a=0;a<bsets;a++)
    {
        mema[a]=new block[as];
    }
    
    //Inicializar cache.
    block l={0};
    for(int a=0;a<bsets;a++)
    {
        for(int b=0;b<as;b++)
        {
            this->mema[a][b]=l;
        }
    }
}

block Cache::read(int index, int asoc){
    return this->mema[index][asoc];
}
void Cache::write(int index, int asoc, int tag){
    this->mema[index][asoc].tag=tag;
}


void Cache::hitRp(){
    this->hitR++;
}
void Cache::missRp(){
    this->missR++;
}
void Cache::hitWp(){
    this->hitW++;
}
void Cache::missWp(){
    this->missW++;
}

int Cache::gethitR(){
    return this->hitR;
}
int Cache::getmissR(){
    return this->missR;
}
int Cache::gethitW(){
    return this->hitW;
}
int Cache::getmissW(){
    return this->missW;
}

/*
int main() {

    unsigned int dir, maskIndex, maskBO, maskTag;
    int i, j, k, remp;
    //tanCache, tamB y asoc deberían ser definidos por argumentos al compilar el programa
    int tamCache=256, tamB=32, numB, asoc = 1, bBoffset, bindex, btag, sets, hit, miss, tamLinea;
    char tipo;
    bool nohit;

    //Parametros del cache
    numB = tamCache/tamB;
    bBoffset = log2(tamB);
    sets = numB/asoc;
    tamLinea = tamB*asoc;
    bindex = log2(sets);
    btag = 32 - bindex - bBoffset;

    //cout << "btag " << btag << " bindex " << bindex << " bBoffset " << bBoffset << endl;
    int Boffset, tag, index;
    int cache[sets][tamLinea];
    ifstream inst("aligned.trace");

    //Inicializar cache
    for(i=0; i<numB; i++) {
        for(j=0; j<tamB; j++) {
            cache[i][j] = 0;
        }
    }

    //Mascaras para obtener el tag, index y byte-offset de la direccion
    maskBO = pow(2,bBoffset)-1;
    maskIndex = (pow(2,bindex) - 1) * pow(2,bBoffset);
    maskTag = (pow(2,btag) - 1) * pow(2,bBoffset+bindex);

    //Se inicializan contadores
    i = 0;
    hit = 0;
    miss = 0;
    srand(time(0));
    ////////////////////////////////////////////////////////////////////////////////
    //Para que lea todo el archivo
    //ATENCION: DURA MUCHO
    //Comentarlo si se quiere leer solo una parte
    ///////////////////////////////////////////////////////////////////////////////
    //while (!inst.eof()) {
    //Para probar con las primeras 1000 lineas
    while (i<1000) {
        i++;
        inst >> hex >> dir;
        cout << i << ". Direccion: " << dir;

        cout << " Byte-offset: ";
        Boffset = dir & maskBO;
        cout << Boffset;

        cout << " Index: ";
        index = (dir & maskIndex) / pow(2,bBoffset);
        cout << index;

        cout << " Tag: ";
        tag = (dir & maskTag) / pow(2,bBoffset+bindex);
        cout << tag;

        inst >> tipo;
        cout << " Tipo: " << tipo << endl;

        nohit = true;
        for(k=0; k<asoc; k++) {//Revisa si el tag coincide con todos los posible campos
            if (tag==cache[index][Boffset+32*k]) {
                hit++;
                nohit = false;
                break;
            }
        }
        //Si el tag no coincide trae todo un nuevo bloque al cache
        if(nohit) {
            miss++;
            remp = rand()%asoc;
            for (j=0; j<=maskBO; j++) {
                cache[index][j+32*remp] = tag;  //Reemplaza uno de los bloques al azar
            }
        }
    }

    cout << "Catidad de hits: " << hit << endl;
    cout << "Cantidad de misses: " << miss << endl;
    inst.close();
    return 0;
}
*/
