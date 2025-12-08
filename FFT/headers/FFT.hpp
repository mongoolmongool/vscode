#include <FFT_block.hpp>

class FFT{
public :
    FFT() {}
    FFT(const std::string& dataset);
    FFT(std::vector<complex_number>& data);

    void set_root(std::unique_ptr<FFT_block> root);

    std::vector<complex_number>& compute();

private :
    std::unique_ptr<FFT_block> root = nullptr;
};

std::vector<complex_number> read_signal(const std::string& filename);