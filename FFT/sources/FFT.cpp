#include <FFT.hpp>

FFT::FFT(std::vector<complex_number>& data) {
    root = std::make_unique<FFT_block>(data);
}

FFT::FFT(const std::string& dataset) {
    std::vector<complex_number> data = read_signal(dataset);
    root = std::make_unique<FFT_block>(data);
}

void FFT::set_root(std::unique_ptr<FFT_block> root) {
    this->root = std::move(root);
}

std::vector<complex_number>& FFT::compute() {
    root->compute_the_block();
    return root->get_freq_spec();
}

std::vector<complex_number> read_signal(const std::string& filename) {
    std::vector<complex_number> data;
    std::ifstream infile(filename);

    if(!infile.is_open()) {
        // file cannot be opened!
        return data;
    }

    double real;
    while (infile >> real) {
        data.emplace_back(real, 0, true);
    }

    return data;
}