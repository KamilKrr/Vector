#include "vector.h"
#include <iostream>

using namespace std;


int main(){

    Vector v{1, 2, 3, 4};

    auto it = v.begin();

    cout << *it;
    it++;
    cout << *it;
    it++;
    cout << *it;
    it++;
    cout << *it;

    //this should no longer be possible
    it++;
    cout << *it;
    it++;
    cout << *it;

    return 0;
}
