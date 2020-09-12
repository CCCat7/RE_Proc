#ifndef DFA_H
#define DFA_H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>

class DFA
{
private:
    std::set<size_t> Q;             //状态集
    std::set<char> Sigma;           //字母表
    std::size_t Q0;                    //初始状态
    std::set<size_t> F;                //终止状态集
    std::map<std::pair<size_t, char>, size_t> Delta;  //状态转移函数
public:
    DFA();
    ~DFA();
    void ReadDFA(char* filename);
    bool run(std::string);
};

#endif