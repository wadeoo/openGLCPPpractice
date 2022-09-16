#include <iostream>


void func();

int main() {
	func();
	func();

}


void func() {
	int i = 5;
	static int a = 2;
	i++;
	a++;
	std::cout << "i = " << i << ", " << "a = " << a << std::endl;
}
