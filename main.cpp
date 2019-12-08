#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
   BTree<int> primero(3);
   primero.insert(10);
   primero.insert(25);
   primero.insert(43);
   primero.insert(31);
    primero.insert(16);
    primero.insert(11);
    primero.insert(14);
    primero.insert(34);
    primero.insert(23);
    primero.insert(22);
    primero.insert(43);
    primero.insert(65);
    primero.insert(24);

    return EXIT_SUCCESS;
}