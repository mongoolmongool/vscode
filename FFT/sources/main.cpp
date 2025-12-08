#include <FFT.hpp>

int main() {

    // complex_number cn1(0,0, true);
    // complex_number cn2(1,0, true);
    // complex_number cn3(4, 0, true);
    // complex_number cn4(9, 0, true);

    // std::vector<complex_number> first_sample;

    // first_sample.push_back(cn1);
    // first_sample.push_back(cn2);
    // first_sample.push_back(cn3);
    // first_sample.push_back(cn4);

    std::string file = "data.txt";
    FFT FFT(file);
    std::vector<complex_number> result;
    
    result = FFT.compute();

    for(int i = 0; i < result.size(); i++) {
        std::cout << "| " << result[i] << " |";
    }

    std::cout << '\n';
    
    return 0;
}