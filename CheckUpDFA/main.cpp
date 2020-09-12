#include "DFA.h"

int main(int argc, char *argv[])
{
    DFA *DFA_instance = new DFA;
    char* filepath = (char*)"./MiniDFA.txt";
    DFA_instance->ReadDFA(filepath);
    if(DFA_instance->run(argv[1]))
        std::cout<<"true"<<std::endl;
    else
        std::cout<<"false"<<std::endl;
    return 0;
}
