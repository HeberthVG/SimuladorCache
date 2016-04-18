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
#include <cstdio>
#include <cmath>

using namespace std;

int main() {

    unsigned int dir, mask = 0;
    int i = 0, j;
    int cache=256, tamB=32, numB, asoc = 1, bBoffset, bindex, btag, sets;
    numB = cache/tamB;
    bBoffset = log2(tamB);
    sets = numB/asoc;
    bindex = log2(sets);
    btag = 32 - bindex - bBoffset;
    cout << "btag " << btag << " bindex " << bindex << " bBoffset " << bBoffset << endl;
    int Boffset, tag, index;
    mask = pow(2,bBoffset)-1;
    ifstream inst("aligned.trace");
    while (i<1) { //Para probar con las primeras 2 lineas
        i++;
        inst >> hex >> dir;
        cout << "Direccion: " << dir << endl;

        cout << "El byte offset es: ";
        Boffset = dir & mask;
        cout << Boffset << endl;

        cout << "El index es: ";
        mask = (pow(2,bindex) - 1) * pow(2,bBoffset);
        index = (dir & mask) / pow(2,bBoffset);
        cout << index << endl;

        cout << "El tag es: ";
        mask = (pow(2,btag) - 1) * pow(2,bBoffset+bindex);
        index = (dir & mask) / pow(2,bBoffset+bindex);
        cout << index << endl;
    }
    inst.close();
    return 0;
}
