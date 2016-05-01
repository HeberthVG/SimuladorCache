#include"Cache.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    unsigned int dir, maskIndex, maskBO, maskTag;
    int i, k, remp;
    
    //tanCache, tamB y asoc deberían ser definidos por argumentos al compilar el programa
    int tamCache=256, tamB=32, numB, asoc = 1, bBoffset, bindex, btag, sets;
    char tipo;
    bool nohit;
    
    try {
        asoc=atoi(argv[1]);
        tamCache=atoi(argv[2]);
        tamB=atoi(argv[3]);
    } catch (...) {
        return 1;
    }
    
    numB = tamCache/tamB;
    bBoffset = log2(tamB);
    sets = numB/asoc;
    bindex = log2(sets);
    btag = 32 - bindex - bBoffset;
    
    Cache newCache(tamB, tamCache, asoc);
    //Se crea un nuevo cache.
    
    //cout << "btag " << btag << " bindex " << bindex << " bBoffset " << bBoffset << endl;
    int Boffset, tag, index;
    ifstream inst("aligned.trace");
    
    //Mascaras para obtener el tag, index y byte-offset de la direccion
    maskBO = pow(2,bBoffset)-1;
    maskIndex = (pow(2,bindex) - 1) * pow(2,bBoffset);
    maskTag = (pow(2,btag) - 1) * pow(2,bBoffset+bindex);
    
    //Se inicializan contadores
    i = 0;
    srand(time(0));
    ////////////////////////////////////////////////////////////////////////////////
    //Para que lea todo el archivo
    //ATENCION: DURA MUCHO
    //Comentarlo si se quiere leer solo una parte
    ///////////////////////////////////////////////////////////////////////////////
    //while (!inst.eof()) {
    //Para probar con las primeras 1000 lineas
    while (!inst.eof()) {
        i++;
        inst >> hex >> dir;
         //cout << i << ". Direccion: " << dir;
        
         //cout << " Byte-offset: ";
        Boffset = dir & maskBO;
         //cout << Boffset;
        
         //cout << " Index: ";
        index = (dir & maskIndex) / pow(2,bBoffset);
         //cout << index;
        
         //cout << " Tag: ";
        tag = (dir & maskTag) / pow(2,bBoffset+bindex);
         //cout << tag;
        
        inst >> tipo;
         //cout << " Tipo: " << tipo << endl;
        
        nohit = true;
        
        switch (tipo) {
            case 'L':
                for(k=0; k<asoc; k++) {
                    //Revisa si el tag coincide con todos los posible campos
                    if (tag==newCache.read(index, k).tag) {
                        newCache.hitRp();
                        nohit = false;
                        break;
                    }
                }
                //Si el tag no coincide trae todo un nuevo bloque al cache
                if(nohit) {
                    newCache.missRp();
                    remp = rand()%asoc;
                    newCache.write(index, remp, tag);
                    //Reemplaza uno de los bloques al azar
                }
                break;
            case 'S':
                for(k=0; k<asoc; k++) {
                    //Revisa si el tag coincide con todos los posible campos
                    if (tag==newCache.read(index, k).tag) {
                        newCache.hitWp();
                        nohit = false;
                        break;
                    }
                }
                //Si el tag no coincide entonces se escribe en memoria.
                if(nohit) {
                    newCache.missWp();
                    remp = rand()%asoc;
                    newCache.write(index, remp, tag);
                    //Reemplaza uno de los bloques al azar
                }
                break;
                
            default:
                break;
        }
        
        
    }
    
    cout << "Catidad de hits por reads: " << newCache.gethitR() << endl;
    cout << "Cantidad de misses por reads: " << newCache.getmissR() << endl;
    cout << "Catidad de hits por writes: " << newCache.gethitW() << endl;
    cout << "Cantidad de misses por writes: " << newCache.getmissW() << endl;
    
    ofstream outputFile("CacheResults.txt");
    outputFile << "Resultados de un cache con: " << " *tamaño de cache: " << tamCache << " *tamaño de bloque: " << tamB << " *asociatividad: "<< asoc << "-way." << endl;
    outputFile << "Catidad de hits por reads: " << newCache.gethitR() << endl;
    outputFile << "Cantidad de misses por reads: " << newCache.getmissR() << endl;
    outputFile << "Catidad de hits por writes: " << newCache.gethitW() << endl;
    outputFile << "Cantidad de misses por writes: " << newCache.getmissW() << endl;
    //Escribe el resultado en un archivo de texto.
    
    inst.close();
    outputFile.close();
    return 0;
}
