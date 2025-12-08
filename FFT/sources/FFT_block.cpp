#include <FFT_block.hpp>

FFT_block::FFT_block(std::vector<complex_number> values) {
    fft_samples = values;
    size = fft_samples.size();

    if (size > 1) {
        std::vector<complex_number> even_values;
        std::vector<complex_number> odd_values;
    
        for (int i = 0; i < (size / 2); i++) {
            even_values.push_back(fft_samples[2*i]);
            odd_values.push_back(fft_samples[2*i+1]);
        }

        even_block = std::make_unique<FFT_block>(even_values);
        odd_block = std::make_unique<FFT_block>(odd_values);
    }
}

std::unique_ptr<FFT_block>& FFT_block::get_even() {
    return even_block;
}

std::unique_ptr<FFT_block>& FFT_block::get_odd() {
    return odd_block;
}

std::vector<complex_number>& FFT_block::get_freq_spec() {
    return frequency_spectrum;
}

void FFT_block::print() {
    if (size > 1) {
        for (int i = 0; i < size; i++) {
            std::cout << "| " << fft_samples[i] << " |";
        }
    }

    if (size == 1) {
        std::cout << fft_samples[0];
    }

    std::cout << '\n';
}

void FFT_block::compute_the_block() {
    if (even_block && even_block->frequency_spectrum.size() == 0) {
        even_block->compute_the_block();
        odd_block->compute_the_block();
    }

    if (size == 1) {
        frequency_spectrum.push_back(fft_samples[0]);
    }

    else {
        frequency_spectrum.resize(size);
        int M = size / 2; // half_of_the_size

        // std::vector<complex_number> freq_before_M;
        // std::vector<complex_number> freq_after_M;


        for (int n = 0; n < M; n++) {
            complex_number freq_ev_n = even_block->frequency_spectrum[n];
            complex_number freq_od_n = odd_block->frequency_spectrum[n];

            complex_number W_N(1, -2 * std::numbers::pi / size * n, false);
            // 어차피 W_N의 크기는 1이니 별도의 power를 쓸 필요가 없음!

            complex_number freq_n = freq_ev_n + W_N * freq_od_n;
            complex_number freq_n_plus_M = freq_ev_n - W_N * freq_od_n;

            frequency_spectrum[n] = freq_n;
            frequency_spectrum[n + M] = freq_n_plus_M;
        }
    }
}