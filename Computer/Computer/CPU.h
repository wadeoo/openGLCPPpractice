#pragma	once
#ifndef COMPUTER
	#define COMPUTER
#include<iostream>


enum enum_cpu_model
{
	i1, i2, i3, i4
};

class Cpu
{
private:
	enum_cpu_model cpuModel;
public:
	Cpu();
	Cpu(enum_cpu_model);
	~Cpu();

	void cpuRun();
	void cpuStop();
};



#endif // !1

