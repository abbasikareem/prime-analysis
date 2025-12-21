#include <fstream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <algorithm>

enum class Alg {
    TRIAL_DIVISION,
    SIEVE
};

uint32_t sieve_of_eratosthenes(uint32_t n) {
	std::vector<bool> sieve(n + 1, true);
	sieve[0] = sieve[1] = false;
	
	for (uint64_t i = 2; n / i >= i; ++i) {
		if (sieve[i]) {
			for (uint64_t j = i * i; j < n + 1; j += i) {
				sieve[j] = false;
			}
		}
	}

    uint32_t count = 0;
    for (bool s : sieve) {
        if (s) ++count;
    }
    
    return count;
}

uint64_t trial_division(uint32_t n) {
	std::vector<uint64_t> primes(n, 0);
	primes[0] = 2;
	
	uint32_t count = 1;
	uint64_t candidate = 3;
	while (count < n) {
		uint64_t sqrt_candidate = static_cast<uint64_t>(std::sqrt(static_cast<double>(candidate)));
		auto end_it = std::upper_bound(primes.begin(), primes.begin() + count, sqrt_candidate);
        
		bool conflict = false;

		for (auto it = primes.begin(); it != end_it && !conflict; ++it) {
			if (candidate % *it == 0) {
				conflict = true;
			}
		}

		if (!conflict) {
			primes[count++] = candidate;
		}

		candidate += 2;
	}

    return primes.back();
}

double run_benchmark(Alg algorithm, uint32_t n) {
    volatile uint32_t sink;
	
	auto start = std::chrono::steady_clock::now();
	
	switch (algorithm) {
		case Alg::TRIAL_DIVISION:
			sink = trial_division(n);
			break;
		case Alg::SIEVE:
			sink = sieve_of_eratosthenes(n);
			break;
	}

	auto end = std::chrono::steady_clock::now();
	
	return std::chrono::duration<double, std::milli>(end - start).count();
}

int main(int argc, char** argv) {
	std::ofstream td_outfile;
	td_outfile.open("benchmarks/trial-division.csv");
	td_outfile << "n,ms\n";

	std::ofstream s_outfile;
	s_outfile.open("benchmarks/sieve.csv");
	s_outfile << "n,ms\n";

	for (uint32_t n = 10; n < 10000000; n *= 1.5) {
		for (uint8_t i = 0; i < 5; ++i) {
			double td_time = run_benchmark(Alg::TRIAL_DIVISION, n);
			double s_time = run_benchmark(Alg::SIEVE, n);

			td_outfile << n << ',' << td_time << '\n';
			s_outfile << n << ',' << s_time << '\n';
		}
		std::cout << "completed tests with n = " << n << std::endl;
	}

	td_outfile.close();
	s_outfile.close();
}
