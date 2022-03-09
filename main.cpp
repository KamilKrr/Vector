#include"vector.h"
#include <iostream>

using namespace std;


int main(){

    Vector v1{3};
    Vector v2(3);

    cout << v1.capacity();
    cout << v2.capacity();


    return 0;
}