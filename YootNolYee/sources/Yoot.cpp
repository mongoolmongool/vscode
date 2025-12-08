#include "Yoot.hpp"
#include <random>
#include <iostream>

Yoot::Yoot(bool Is_normal) : is_normal(Is_normal) {}

bool Yoot::get_is_normal() {
    return is_normal;
}

const float Yoot::get_back_probability() {
    return back_probability;
}

void Yoot::set_status(bool Status) {
    this->status = Status;
}

bool& Yoot::get_status() {
    return status;
}

void Yoot::roll_a_yoot() {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::bernoulli_distribution distribution(0.6); // 1이 나올 확률이 0.6
    status = (bool)distribution(gen); // back일 확률이 0.6인 이항분포
}

Yoots::Yoots() {
    Yoot yoot1(true); Yoot yoot2(true); Yoot yoot3(true); // 정상 윷
    Yoot yoot4(false); // 빽도 윷

    yoots.push_back(yoot1);
    yoots.push_back(yoot2);
    yoots.push_back(yoot3);
    yoots.push_back(yoot4);
    // yoots -> || yoot1 || yoot2 || yoot3 || yoot4 ||
}

void Yoots::Initialize_num_of_backs() {
    num_of_backs = 0;
}

int Yoots::get_num_of_backs() {
    return num_of_backs;
}

bool Yoots::Is_Nak() {
    return nak;
}

int Yoots::roll() { // 아마 get_the_result()랑 합칠 수도 있을듯?
    // 윷을 던지는 인터페이스 구현
    // 윷 하나 하나의 앞,뒤 결정
    // num_of_fronts에 따라서 
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::bernoulli_distribution distribution(0.08);
    nak = (bool)distribution(gen);

    if(Is_Nak()) {
        return 0;
    }

    Initialize_num_of_backs();
    for (int i = 0; i < yoots.size(); i++) {
        yoots[i].roll_a_yoot();

        if(yoots[i].get_status()) {
            num_of_backs++;
        }
    }

    switch(num_of_backs) {
        case 4 : // 윷
            return 4;
        
        case 3 : // 걸
            return 3;
        
        case 2 : // 개
            return 2;

        case 1 : // 도
            if(yoots[3].get_status()) { // 빽도 윷이 back인 경우
                return -1;
            }
            
            else { // 빽도 윷이 front인 경우
                return 1;
            }

        case 0 : // 모
            return 5;
    }
    return 6; // 그저 오류를 없애기 위함.
}

void Yoots::print() {
    if(Is_Nak()) {
    	std::cout << " --------------------\n";
    	std::cout << "|  |         |       |\n";
	    std::cout << "|  |         | _____ |\n";
    	std::cout << "|  |         |       |\n";
    	std::cout << "|   -------- |       |\n";
    	std::cout << "|                    |\n";
    	std::cout << "|  -------------     |\n";
    	std::cout << "|               |    |\n";
    	std::cout << "|               |    |\n";
    	std::cout << " --------------------\n\n";
        return;
    }

    switch(num_of_backs) {
        case 4 : // 윷
           	std::cout << " -----  -----  -----  -----\n";
            std::cout << "|     ||     ||     ||     |\n";
            std::cout << "|     ||     ||     ||     |\n";
   	        std::cout << "|     ||     ||     ||     |\n";
            std::cout << "|     ||     ||     ||     |\n";
            std::cout << " -----  -----  -----  -----\n";
            break;
        
        case 3 : // 걸
           	std::cout << " -----  -----  -----  -----\n";
            std::cout << "|     ||  x  ||     ||     |\n";
            std::cout << "|     ||  x  ||     ||     |\n";
   	        std::cout << "|     ||  x  ||     ||     |\n";
            std::cout << "|     ||  x  ||     ||     |\n";
            std::cout << " -----  -----  -----  -----\n";
            break;
        
        case 2 : // 개
           	std::cout << " -----  -----  -----  -----\n";
            std::cout << "|     ||  x  ||  x  ||     |\n";
            std::cout << "|     ||  x  ||  x  ||     |\n";
   	        std::cout << "|     ||  x  ||  x  ||     |\n";
            std::cout << "|     ||  x  ||  x  ||     |\n";
            std::cout << " -----  -----  -----  -----\n";
            break;

        case 1 : // 도
            if(yoots[3].get_status()) { // 빽도 윷이 back인 경우
            	std::cout << " -----  -----  -----  -----\n";
	            std::cout << "|  x  ||  x  ||  *  ||  x  |\n";
	            std::cout << "|  x  ||  x  ||     ||  x  |\n";
    	        std::cout << "|  x  ||  x  ||     ||  x  |\n";
	            std::cout << "|  x  ||  x  ||  *  ||  x  |\n";
	            std::cout << " -----  -----  -----  -----\n";
                break;
            }
            
            else { // 빽도 윷이 front인 경우
            	std::cout << " -----  -----  -----  -----\n";
	            std::cout << "|     ||  x  ||  x  ||  x  |\n";
	            std::cout << "|     ||  x  ||  x  ||  x  |\n";
    	        std::cout << "|     ||  x  ||  x  ||  x  |\n";
	            std::cout << "|     ||  x  ||  x  ||  x  |\n";
	            std::cout << " -----  -----  -----  -----\n"; 
                break;
            }

        case 0 : // 모
        	std::cout << " -----  -----  -----  -----\n";
	        std::cout << "|  x  ||  x  ||  x  ||  x  |\n";
	        std::cout << "|  x  ||  x  ||  x  ||  x  |\n";
	        std::cout << "|  x  ||  x  ||  x  ||  x  |\n";
	        std::cout << "|  x  ||  x  ||  x  ||  x  |\n";
	        std::cout << " -----  -----  -----  -----\n";   
            break;
    }
}