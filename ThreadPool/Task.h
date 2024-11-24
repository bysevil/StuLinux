#pragma once
#include<iostream>
#include<thread>
#include<sstream>

class Task {
public:
    void Start() {
        std::stringstream ss;
        ss << "[" << std::this_thread::get_id() <<"][" << _num << "]#" << "n1:" << _num1 << " + " << \
            "n2:" << _num2 << " = " << _num1 + _num2 << std::endl;
        std::cout << ss.str();
    }

    Task(int num,int num1, int num2)
        :_num(num)
        ,_num1(num1)
        , _num2(num2)
    {
    }

private:
    int _num;
    int _num1;
    int _num2;
};