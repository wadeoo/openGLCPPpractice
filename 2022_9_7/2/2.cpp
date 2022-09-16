#include<iostream>

int i = 1;
void main(void) {
	static int a;
	int b = -10;
	int c = 0;

	void other(void);
	std::cout << "---MAIN---\n";
	std::cout << "i: " << i << " a: " << a << " b: " << b << " c: " << std::endl;

	c += 8;
	other();

	std::cout << "---MAIN---\n";
	std::cout << "i: " << i << " a: " << a << " b: " << b << " c: " << std::endl;
	i += 10;
	other();
	
}


void other(void) {
	static int a = 2;
	static int b;
	int c = 10;

	a += 2;
	i += 32;
	c += 5;

	std::cout << "---OTHER---\n";

	std::cout << "i: " << i << " a:" << a << " b: " << b << " c: " << c << std::endl;

	b = a;

}