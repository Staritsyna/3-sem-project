#include "plot_trace.h"
#include "input.h"

#include <iostream>


int main() {
	try{
	int n;
	std::cout << "Enter the number of particles " << std::endl;
  	std::cin >> n ;
	input(n);
	plot_trace3D(n);
	}
	catch (std::string s) {
          	std::cout<< "Error: " << s <<std::endl;
          	std::cerr<<s<<std::endl;
       }
	
}
