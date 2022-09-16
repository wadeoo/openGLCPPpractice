#pragma once
#ifndef RAM
#define RAM
#include<iostream>


enum enum_ram_model
{
	DDR1,DDR2,DDR3,DDR4
};

class Ram
{
private:
	enum_ram_model	ramModel;
public:

	Ram();

	Ram(enum_ram_model);
	~Ram();

	void ramRun();
	void ramStop();
};


#endif // !RAM

