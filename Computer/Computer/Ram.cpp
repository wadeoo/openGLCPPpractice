#include "Ram.h"

Ram::Ram()
{
}

Ram::Ram(enum_ram_model rModel)
{
	ramModel = rModel;
}

Ram::~Ram()
{
}

void Ram::ramRun()
{
	std::cout << "内存条儿 启动！"<<std::endl;
}

void Ram::ramStop()
{
	std::cout << "内存条儿 停止！" << std::endl;
}
