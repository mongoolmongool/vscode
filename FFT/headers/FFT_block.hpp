#include <complex_number.hpp>

class FFT_block {
public :
    FFT_block(std::vector<complex_number> values);

    std::unique_ptr<FFT_block>& get_even();
    std::unique_ptr<FFT_block>& get_odd();

    std::vector<complex_number>& get_freq_spec();

    void print();

    void compute_the_block(); // This is "THE MOST IMPORTANT FUNCTION" in this project!!!

private :
    std::vector<complex_number> fft_samples;
    std::vector<complex_number> frequency_spectrum;

    std::unique_ptr<FFT_block> even_block = nullptr;
    std::unique_ptr<FFT_block> odd_block = nullptr;

    std::size_t size;    
};