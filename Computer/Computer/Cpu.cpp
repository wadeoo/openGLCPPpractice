#include "Cpu.h"


Cpu::Cpu() {};

Cpu::Cpu(enum_cpu_model cModel) {
	cpuModel = cModel;
}

Cpu::~Cpu() {};

void Cpu::cpuRun() {
	std::cout << "中央处理单元 启动！"<<std::endl;
}


void Cpu::cpuStop() {
	std::cout << "中央处理单元 停止！"<<std::endl;
}


