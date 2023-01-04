#pragma once
#ifndef COMPUTER
#include<iostream>
#include<string>
#include"Cpu.h"
#include"Ram.h"
#include"MainBoard.h"


class Computer
{
private:
    std::string computerModel;
    Cpu cpu;
    Ram ram;
    MainBoard mainBoard;

    static const std::string computerBrand;// 静态数据成员，为所有对象共享，表示所有电脑都是联想品牌
public:
    Computer();
    Computer(std::string,enum_cpu_model,enum_ram_model,enum_mainBoard_model);

    ~Computer();

    void computerRun();
    void computerStop();

    static const  std::string getBrand();//静态函数成员，作用：获取私有静态数据

    friend void advertising();// 友元函数，能够访问该类的私有数据成员
};

void advertising();


#define COMPUTER
#endif // !COMPUTER

