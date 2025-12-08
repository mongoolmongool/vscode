#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <numbers>
#include <fstream>
#include <string>

class complex_number{
public :
    // constructor
    complex_number() : real_part(0), imaginary_part(0), magnitude(0), argument(0) {}
    // 이 constructor가 있어야만 vector의 resize함수를 빈 상태에서 써줄 수가 있었다!

    // "true" means "Cartesian Form", "false" means "Polar Form"
    complex_number(double Re_or_Mag, double Im_or_Arg, bool C_or_P);


    // complex_number(float Mag, float Arg, ) : magnitue(Mag), argument(Arg) {
    //     update_cartesian();
    // }
    // 있었는데요? 없었습니다. 위에 꺼랑 통합됐어요.

    // copy constructor
    complex_number(const complex_number& CN);

    // operator overloading
    double& operator[](const int i); // for a fast access, modifying
    const double& operator[](const int i) const; // reading
    complex_number operator+(const complex_number& CN);
    complex_number operator-(const complex_number& CN);
    complex_number operator*(const complex_number& CN);
    complex_number operator/(const complex_number& CN);
    complex_number& operator=(const complex_number& CN);
    complex_number power(const int& n);

    // print!
    void print();

    // update real_part, imaginary_part, magnitude, argument
    void update_cartesian();
    void update_polar();

private :
    double real_part; // Real number
    double imaginary_part; // Imaginary number
    double magnitude; // root(re^2 + im^2)
    double argument; // atan(Im/Re), 위상, arg
    
    // (real_part) + i*(imaginary_part) = magnitude*e^(i*arg) = magnitude*(cos(arg(z)) + i*sin(arg(z)))
};

std::ostream& operator<<(std::ostream& os, const complex_number& CN); // FOR MORE C++ LIKE OPERATION...

void cast(double& x);

