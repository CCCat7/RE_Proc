#include "DFA.h"

DFA::DFA(){}

DFA::~DFA(){}

void DFA::ReadDFA(char* filename)
{
    std::ifstream fp;
	fp.open(filename);
    if(!fp.is_open()) {
        std::cout << filename << " open error." << std::endl;
        exit(0);
    }

	std::string tempstr;
	while(getline(fp, tempstr)) {
		if(tempstr == "Q: ") {
			std::string stateline;
			getline(fp, stateline);
			std::string state;
			for(size_t i = 0; i < stateline.size(); i++) {
				if(stateline[i]==' ') {
					size_t res = atoi(state.c_str());
					this->Q.insert(res);
					state.clear();
				}
				else
					state += stateline[i];
			} 
		}
        else if(tempstr == "Sigma: ") {
			std::string sigmaline;
			getline(fp, sigmaline);
			for(size_t i = 0; i < sigmaline.size(); i++) {
				if(sigmaline[i] == ' ')
					continue;
				else
					this->Sigma.insert(sigmaline[i]);
			} 
		}
		else if(tempstr == "q0: ") {
			std::string q0line;
			getline(fp, q0line);
			size_t res = atoi(q0line.c_str());
			this->Q0 = res;
		}
		else if(tempstr == "F: ") {
			std::string fline;
			getline(fp, fline);
			std::string state;
			for(size_t i = 0; i < fline.size(); i++) {
				if(fline[i]==' ') {
					size_t res = atoi(state.c_str());
					this->F.insert(res);
					state.clear();
				}
				else
					state += fline[i];
			} 
		}
		else if(tempstr == "Delta: ") {
			std::string deltaline;
			while(!fp.eof())
			{
				deltaline.clear();
				getline(fp, deltaline);
                if(deltaline[0] != '(')
                    break;
				size_t index(1);
				std::string qBegin;
				char transchar;
				std::string qEnd;
				while(deltaline[index] != ',') { //提取起始状态
					qBegin += deltaline[index];
					index++;
				}
				index += 1;  //,{
				transchar = deltaline[index];
				index += 6;

				for(size_t i = index; i < deltaline.size(); i++)
				{
					qEnd += deltaline[i];
				}

				size_t _qBegin = atoi(qBegin.c_str());
				size_t _qEnd = atoi(qEnd.c_str());
				std::pair<size_t, char> left(_qBegin, transchar);
                this->Delta.insert(std::pair<std::pair<size_t, char>, size_t>(left, _qEnd));
			}
			break;
		}
		tempstr.clear();
	}
    fp.close();
}

bool DFA::run(std::string str)
{
    // for(auto a:this->Delta) {
    //     std::cout << a.first.first << ',' <<a.first.second <<' ' << a.second<<std::endl;
    // }
    str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
    size_t Qnow = this->Q0;
    // std::cout << Qnow << std::endl;
    // std::cout << str << std::endl;
    for(size_t i = 0; i < str.size(); i++) {
        std::pair<size_t, char> Delta_temp(Qnow, str[i]);
        if(this->Delta.find(Delta_temp) != this->Delta.end()) {
            Qnow = this->Delta[Delta_temp];
            //std::cout << Qnow << std::endl;
        }
        else
            return false;
    }
    if(this->F.find(Qnow) != this->F.end())
        return true;
    return false;
}

