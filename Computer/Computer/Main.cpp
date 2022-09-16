#include "Computer.h"

int main() {
	std::string compModel="laptop";
	Computer computer(compModel,i1,DDR2,B);

	computer.computerRun();
	computer.computerStop();

	std::cout << computer.getBrand() << std::endl;
	advertising();

}