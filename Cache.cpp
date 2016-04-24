/*
    Universidad de Costa Rica
    Escuela de Ingeniería Eléctrica
    Estructuras de Computadoras Digitales II
    IE-0521
    Tarea Programada 1
    Carlos Solano       B3.... (Se me olvidó su carné xD)
    Heberth Valverde    B37174
*/

// Simulador de una memoria caché

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    unsigned int dir, maskIndex, maskBO, maskTag;
    int i, j;
    //tanCache, tamB y asoc deberían ser definidos por argumentos al compilar el programa
    int tamCache=256, tamB=32, numB, asoc = 1, bBoffset, bindex, btag, sets, hit, miss;
    char tipo;

    //Parametros del cache
    numB = tamCache/tamB;
    bBoffset = log2(tamB);
    sets = numB/asoc;
    bindex = log2(sets);
    btag = 32 - bindex - bBoffset;

    //cout << "btag " << btag << " bindex " << bindex << " bBoffset " << bBoffset << endl;
    int Boffset, tag, index;
    int cache[numB][tamB];
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
    ////////////////////////////////////////////////////////////////////////////////
    //Para que lea todo el archivo
    //ATENCION: DURA MUCHO
    //Comentarlo si se quiere leer solo una parte
    ///////////////////////////////////////////////////////////////////////////////
    //while (!inst.eof()) {
    //Para probar con las primeras 100 lineas
    while (i<100) {
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

        if (tag==cache[index][Boffset]) {
            hit++;
        }
        //Si el tag no coincide trae todo un nuevo bloque al cache
        else {
            miss++;
            for (j=0; j<=maskBO; j++) {
                cache[index][j] = tag;
            }
        }
    }

    cout << "Catidad de hits: " << hit << endl;
    cout << "Cantidad de misses: " << miss << endl;
    inst.close();
    return 0;
}
