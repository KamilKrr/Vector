#include "vector.h"
#include <iostream>

using namespace std;


int main(){

    Vector<double> x(0);
 	Vector<double> y(0);
  	cout << x.size();
	for(std::size_t i{0};i<100;++i){
		x.insert(x.begin(),5);
		y.push_back(3);
	}
	cout << x.size() << y.size();

    return 0;
}
