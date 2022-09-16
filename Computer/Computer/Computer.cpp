#include "Computer.h"

const std::string Computer::computerBrand{ "联想" };

Computer::Computer()
{
}

Computer::Computer(std::string compModel,enum_cpu_model cModel
	,enum_ram_model rModel, enum_mainBoard_model mModel)
	:computerModel{compModel},cpu{cModel},ram{rModel},mainBoard{mModel}
{
}

Computer::~Computer()
{
}

void Computer::computerRun()
{
	cpu.cpuRun();
	ram.ramRun();
	mainBoard.MainBoardRun();
	std::cout << "计算机 启动！" << std::endl;


}

void Computer::computerStop()
{
	cpu.cpuStop();
	ram.ramStop();
	mainBoard.MainBoardStop();
	std::cout << "计算机 停止！" << std::endl;
}

const std::string Computer::getBrand()
{
	return computerBrand;
}

void advertising()
{
	std::cout << Computer::computerBrand << "就是好" << std::endl;
}
