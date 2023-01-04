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

    static const std::string computerBrand;// ��̬���ݳ�Ա��Ϊ���ж�������ʾ���е��Զ�������Ʒ��
public:
    Computer();
    Computer(std::string,enum_cpu_model,enum_ram_model,enum_mainBoard_model);

    ~Computer();

    void computerRun();
    void computerStop();

    static const  std::string getBrand();//��̬������Ա�����ã���ȡ˽�о�̬����

    friend void advertising();// ��Ԫ�������ܹ����ʸ����˽�����ݳ�Ա
};

void advertising();


#define COMPUTER
#endif // !COMPUTER

