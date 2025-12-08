#include <iostream>
#include "add.hpp"

int main() {
	int a = 3; int b = 7;
	std::cout << "a+b = " << a+b << '\n';
	std::cout << "add(a,b) = " << add(a,b) << '\n';
    return 0;
}
