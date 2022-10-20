#ifndef STC_TASKS_LCG_REVERSE_H_INCLUDED
#define STC_TASKS_LCG_REVERSE_H_INCLUDED

#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <numeric>

namespace lcg { 

/*
* Предсказывает все возможные варианты пятого числа в 
* последовательности LCG генератора, вычисляя изначальные
* параметры генератора
*/
template< 
	typename T, 
	std::enable_if_t<std::is_integral<T>::value, bool> = true
>
class Predictor {
public:
	Predictor() = delete;

	Predictor(const std::array<T, 4>& sequence, T max_m)
		: _x{ sequence }, _predictions{}, _max_m{ max_m }
	{
		solve();
	}

	~Predictor() {
		//empty
	}

public:
	void print_to_console() const noexcept {
		std::cout << "-------------------------------------------------------------------" << std::endl;
		for (const auto& [params, predicted] : _predictions) {
			if (std::gcd(params[1], params[2]) == 1 && is_divisible_by_all_primes(params[0] - 1, params[2])) {
				std::cout << "Most likely initial combination is: " << std::endl;
			}
			std::cout << "Predicted #5: " << predicted << " with params: a: " 
				<< params[0] << " c: " << params[1] << " m: " << params[2] << std::endl;
			std::cout << "-------------------------------------------------------------------" << std::endl;
		}
	}

	auto [[nodiscard]] get_all_predictions() const noexcept {
		return _predictions;
	}

private:
	/*
	*	true, если x делится на все простые
	*	множители y
	*/
	bool is_divisible_by_all_primes(T x, T y) const noexcept
	{
		if (y == 1)
			return true;
		if (std::gcd(x, y) == 1)
			return false;
		return is_divisible_by_all_primes(x, y / std::gcd(x, y));
	}

	std::vector<T> [[nodiscard]] get_all_dividers(const T val) const noexcept {
		std::vector<T> result{};
		for (T i{ 1 }; i <= val / 2 + 1; ++i) { 
			if (val % i == 0) {
				result.push_back(i);
			}
		}
		result.push_back(val);
		return result;
	}

	void solve() noexcept {
		auto N = std::abs((_x[3] - _x[1]) * (_x[1] - _x[0]) - (_x[2] - _x[1]) * (_x[2] - _x[0]));

		std::vector<T> all_dividers{ get_all_dividers(N) };
		auto it_to_first_over_max = std::upper_bound(
			all_dividers.begin(), all_dividers.end(),
			_max_m
		);
		all_dividers.erase(it_to_first_over_max, all_dividers.end());
		auto it_to_first_lower_min = std::lower_bound(
			all_dividers.begin(), all_dividers.end(),
			*std::max_element(_x.begin(), _x.end())
		);
		all_dividers.erase(all_dividers.begin(), it_to_first_lower_min);
		for (const auto& m_candidate : all_dividers) {
			std::cout << "Bruteforcing a, c for m = " << m_candidate << std::endl;
			for (T a_candidate{ 1 }; a_candidate < m_candidate; ++a_candidate) {
				for (T c_candidate{ 0 }; c_candidate < m_candidate; ++c_candidate) {
					auto x2_pred = (a_candidate * _x[0] + c_candidate) % m_candidate;
					if (x2_pred == _x[1]) {
						auto x3_pred = (a_candidate * x2_pred + c_candidate) % m_candidate;
						if (x3_pred == _x[2]) {
							auto x4_pred = (a_candidate * x3_pred + c_candidate) % m_candidate;
							if (x4_pred == _x[3]) {
								_predictions[{ a_candidate, c_candidate, m_candidate }] = 
									(a_candidate * x4_pred + c_candidate) % m_candidate;
							}
						}
					}
				}
			}
		}
	}

private:
	const std::array<T, 4> _x;
	std::map<std::array<T, 3>, T> _predictions; // Key = {lcg_params} Value = fifth_predicted
	const T _max_m;
};

} //namespace lcg

#endif