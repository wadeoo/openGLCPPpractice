#include "MainBoard.h"

MainBoard::MainBoard()
{
}

MainBoard::MainBoard(enum_mainBoard_model mModel)
{
	mainBoardModel = mModel;
}

MainBoard::~MainBoard()
{
}

void MainBoard::MainBoardRun()
{
	std::cout << "���� ������" << std::endl;
}

void MainBoard::MainBoardStop()
{
	std::cout << "���� ֹͣ��" << std::endl;
}
