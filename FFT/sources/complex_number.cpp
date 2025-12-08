#include <complex_number.hpp>

complex_number::complex_number(double Re_or_Mag, double Im_or_Arg, bool C_or_P) {
    // Cartesian Form Version
    if (C_or_P) {
        real_part = Re_or_Mag;
        imaginary_part = Im_or_Arg;
        update_polar();
    }
    
    // Polar Form Version
    if(!C_or_P) {
        magnitude = Re_or_Mag;
        argument = Im_or_Arg;
        update_cartesian();
    }
}

complex_number::complex_number(const complex_number& CN) {
    real_part = CN[0];
    imaginary_part = CN[1];
    magnitude = CN.magnitude;
    argument = CN.argument;
}

double& complex_number::operator[](const int i) {
    if (i == 0) {
        return real_part;
    }

    else if (i == 1) {
        return imaginary_part;
    }
    else throw std::out_of_range("Index must be 0 or 1"); // I don't know this clearly...
}

const double& complex_number::operator[](const int i) const {
    if (i == 0) {
        return real_part;
    }

    else if (i == 1) {
        return imaginary_part;
    }
    else throw std::out_of_range("Index must be 0 or 1"); // I don't know this clearly..
}

complex_number complex_number::operator+(const complex_number& CN) {
    return complex_number(real_part + CN[0], imaginary_part + CN[1], true);
}

complex_number complex_number::operator-(const complex_number& CN) {
    return complex_number(real_part - CN[0], imaginary_part - CN[1], true);
}

complex_number complex_number::operator*(const complex_number& CN) {
    double new_real;
    double new_imag;

    new_real = real_part * CN[0] - imaginary_part * CN[1];
    new_imag = real_part * CN[1] + imaginary_part * CN[0];

    return complex_number(new_real, new_imag, true);
}

complex_number complex_number::operator/(const complex_number& CN) {
    // if (CN[0] != 0 || CN[1] != 0)
    double new_real;
    double new_imag;
    
    new_real = (real_part * CN[0] + imaginary_part * CN[1]) / (CN[0]*CN[0] + CN[1]*CN[1]);
    new_imag = (imaginary_part * CN[0] - real_part * CN[1]) / (CN[0]*CN[0] + CN[1]*CN[1]);

    return complex_number(new_real, new_imag, true);
}

complex_number& complex_number::operator=(const complex_number& CN) {
    real_part = CN[0];
    imaginary_part = CN[1];
    magnitude = CN.magnitude;
    argument = CN.argument;
    return (*this);
}

complex_number complex_number::power(const int& n) {
    return complex_number(std::pow(this->magnitude, n), argument * n, false);
}

void complex_number::print() {
    if (real_part != 0) {
        std::cout << real_part;
    }

    if (imaginary_part != 0) {
        if(real_part != 0) {
            std::cout << (imaginary_part > 0 ? " + " : " - ");
            std::cout << (imaginary_part > 0 ? imaginary_part : -imaginary_part);
            std::cout << "i";
        }

        else {
            std::cout << (imaginary_part > 0 ? "" : "-");
            std::cout << (imaginary_part > 0 ? imaginary_part : -imaginary_part);
            std::cout << "i";
        }
    }
    
    if (real_part == 0 && imaginary_part == 0) {
        std::cout << 0;
    }
}

void complex_number::update_cartesian() {
    real_part = magnitude*std::cos(argument);
    imaginary_part = magnitude*std::sin(argument);

    cast(real_part);
    cast(imaginary_part);
}

void complex_number::update_polar() {
    magnitude = std::sqrt(real_part * real_part + imaginary_part * imaginary_part);
    argument = std::atan2(imaginary_part, real_part); // -pi() <= atan2(x) <= +pi()
    // if (argument < 0) {
    //     argument += 2*std::numbers::pi;
    // } 굳이???
}

std::ostream& operator<<(std::ostream& os, const complex_number& CN) {

    if (CN[0] != 0) {
        os << CN[0];
    }

    if (CN[1] != 0) {
        if(CN[0] != 0) {
            os << (CN[1] > 0 ? " + " : " - ");
            os << (CN[1] > 0 ? CN[1] : -CN[1]);
            os << "i";
        }

        else {
            os << (CN[1] > 0 ? "" : "-");
            os << (CN[1] > 0 ? CN[1] : -CN[1]);
            os << "i";
        }
    }
    
    if (CN[0] == 0 && CN[1] == 0) {
        os << 0;
    }

    return os;
}

void cast(double& x) {
    double epsilon = 1e-9;
    if (std::abs(x - std::round(x)) < epsilon) {
        x = std::round(x);
    }
}