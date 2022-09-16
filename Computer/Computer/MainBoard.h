#pragma once
#ifndef MAIN_BOARD
#define MAIN_BOARD
#include<iostream>


enum enum_mainBoard_model
{
	A,B,C,D
};
class MainBoard
{
private:
	enum_mainBoard_model mainBoardModel;
public:
	MainBoard();
	MainBoard(enum_mainBoard_model);

	~MainBoard();

	void MainBoardRun();
	void MainBoardStop();

};


#endif // !MAIN_BOARD

