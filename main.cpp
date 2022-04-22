#include "vector.h"
#include <iostream>

using namespace std;


int main(){

    /*
	Vector x(0);
 	Vector y(0);
  	cout << x.size();
	for(std::size_t i{0};i<100;++i){
		x.insert(x.begin(),5);
		y.push_back(3);
	}
	cout << x.size() << y.size();

    return 0;*/

	Vector v({0,1,2,3,4,5,6,7,8,9});
	auto end{v.end()};

	++end;
	cout << (end == v.end());
	end++;
	cout << (end == v.end());
	cout << *end;
}
