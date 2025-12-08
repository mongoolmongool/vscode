#pragma once

#include <vector>
#include <random>

class Yoot {
public :
    Yoot(bool Is_normal);
    bool get_is_normal();
    const float get_back_probability();
    void set_status(bool Status);
    bool& get_status();
    void roll_a_yoot();

private :
    bool is_normal; // 빽도 윷이 아니면 true, 맞으면 false
    const float front_probability = 0.4; // front가 4개면 모
    const float back_probability = 0.6; // back이 4개면 윷
    bool status; // true가 back, false가 front
};

// 윷의 기능에 뭐가 있을까...
// 윷 던지기
// 빽도
// 낙

class Yoots { // 낙도 구현이 되어야 함
public :
    Yoots();
    void Initialize_num_of_backs();
    int get_num_of_backs();
    int roll();
    bool Is_Nak();

    void print();

private :
    std::vector<Yoot> yoots; // 윷 4개
    int num_of_backs; // if this is 0, it means "모"
    bool nak;
};