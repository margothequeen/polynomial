#include <iostream>
#include <vector>
#include <string>



long long fastpow(long long a, long long b) {
	if (!b)
		return 1LL;
	return b % 2LL ? a * fastpow(a, b - 1LL) : fastpow(a * a, b / 2LL);
}



struct polynomial {
	long long exponentiation = NULL;
	std::vector <long long> coefficient;

	long long val(long long x) {
		long long value = 0LL;
		for (long long i = 0LL; i <= exponentiation; ++i)
			value += coefficient[(size_t)i] * fastpow(x, exponentiation - i);
		return value;
	}

	polynomial sum(polynomial& b) {
		polynomial c;
		std::vector <long long> vec1 = coefficient, vec2 = b.coefficient;
		reverse(vec1.begin(), vec1.end());
		reverse(vec2.begin(), vec2.end());
		for (long long i = 0; i <= std::min(exponentiation, b.exponentiation); ++i)
			c.coefficient.push_back(vec1[(size_t)i] + vec2[(size_t)i]);
		if (exponentiation > b.exponentiation) {
			for (long long i = b.exponentiation + 1; i <= exponentiation; ++i)
				c.coefficient.push_back(vec1[(size_t)i]);
		}
		else {
			for (long long i = exponentiation + 1; i <= b.exponentiation; ++i)
				c.coefficient.push_back(vec2[(size_t)i]);
		}
		while (c.coefficient.size() && !c.coefficient[c.coefficient.size() - 1])
			c.coefficient.pop_back();
		reverse(c.coefficient.begin(), c.coefficient.end());
		if (!c.coefficient.size())
			c.coefficient.push_back(0);
		c.exponentiation = c.coefficient.size() - 1;
		return c;
	}

	polynomial dif(polynomial& b) {
		polynomial c = b;
		for (long long i = 0; i <= c.exponentiation; ++i)
			c.coefficient[(size_t)i] *= (-1);
		return sum(c);
	}

	polynomial mul(polynomial& b) {
		polynomial c;
		std::vector <long long> vec1 = coefficient, vec2 = b.coefficient;
		reverse(vec1.begin(), vec1.end());
		reverse(vec2.begin(), vec2.end());
		while (vec1.size() < vec2.size())
			vec1.push_back(0LL);
		while (vec2.size() < vec1.size())
			vec2.push_back(0LL);
		c.coefficient.resize(vec1.size() + vec2.size(), 0LL);
		for (size_t i = 0; i < vec1.size(); ++i) {
			for (size_t j = 0; j < vec2.size(); ++j)
				c.coefficient[i + j] += vec1[i] * vec2[j];
		}
		while (c.coefficient.size() && !c.coefficient[c.coefficient.size() - 1])
			c.coefficient.pop_back();
		reverse(c.coefficient.begin(), c.coefficient.end());
		if (!c.coefficient.size())
			c.coefficient.push_back(0LL);
		c.exponentiation = c.coefficient.size() - 1;
		return c;
	}

	void print(std::string t) {
		if (t == "yes") {
			for (size_t i = 0; i < coefficient.size(); ++i)
				std::cout << coefficient[i] << ' ';
			std::cout << '\n';
		}
		else {
			if (!exponentiation) {
				std::cout << coefficient[0] << '\n';
				return;
			}
			if (exponentiation == 1) {
				if (coefficient[0] != 1LL) {
					if (coefficient[0] != -1)
						std::cout << coefficient[0];
					else
						std::cout << '-';
				}
				std::cout << 'x';
				if (coefficient[1]) {
					if (coefficient[1] > 0LL)
						std::cout << '+';
					std::cout << coefficient[1];
				}
				std::cout << '\n';
				return;
			}
			if (coefficient[0] != 1LL) {
				if (coefficient[0] != -1LL)
					std::cout << coefficient[0];
				else
					std::cout << '-';
			}
			std::cout << "x^" << exponentiation;
			for (long long i = 1; i <= exponentiation - 2LL; ++i) {
				if (coefficient[(size_t)i]) {
					if (coefficient[(size_t)i] > 0LL)
						std::cout << '+';
					if (coefficient[(size_t)i] == -1LL)
						std::cout << '-';
					else {
						if (coefficient[(size_t)i] != 1LL)
							std::cout << coefficient[(size_t)i];
					}
					std::cout << "x^" << exponentiation - i;
				}
			}
			if (coefficient[(size_t)(exponentiation - 1LL)]) {
				if (coefficient[(size_t)(exponentiation - 1LL)] > 0LL)
					std::cout << '+';
				if (coefficient[(size_t)(exponentiation - 1LL)] == -1LL)
					std::cout << '-';
				else {
					if (coefficient[(size_t)(exponentiation - 1LL)] != 1LL)
						std::cout << coefficient[(size_t)(exponentiation - 1LL)];
				}
				std::cout << 'x';
			}
			if (coefficient[(size_t)exponentiation]) {
				if (coefficient[(size_t)exponentiation] > 0LL)
					std::cout << '+';
				std::cout << coefficient[(size_t)exponentiation];
			}
			std::cout << '\n';
		}
	}
};

polynomial pw(polynomial a, long long k) {
	if (!k) {
		polynomial ans;
		ans.exponentiation = 0LL;
		ans.coefficient = { 1LL };
		return ans;
	}
	return k % 2LL ? pw(a, k - 1LL).mul(a) : pw(a.mul(a), k / 2LL);
}

signed main() {
	std::string s, t;
	while (true) {
		std::cin >> s;
		if (s == "val") {
			polynomial a;
			std::cin >> a.exponentiation;
			a.coefficient.resize((size_t)(a.exponentiation + 1LL));
			for (size_t i = 0; i < a.coefficient.size(); ++i)
				std::cin >> a.coefficient[i];
			long long x;
			std::cin >> x;
			std::cout << a.val(x) << '\n';
		}
		if (s == "sum") {
			std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
			std::cin >> t;
			while (t != "yes" && t != "no") {
				std::cout << "wrong input\n";
				std::cin >> t;
			}
			polynomial a, b;
			std::cin >> a.exponentiation;
			a.coefficient.resize((size_t)(a.exponentiation + 1LL));
			for (size_t i = 0; i < a.coefficient.size(); ++i)
				std::cin >> a.coefficient[i];
			std::cin >> b.exponentiation;
			b.coefficient.resize((size_t)(b.exponentiation + 1LL));
			for (size_t i = 0; i < b.coefficient.size(); ++i)
				std::cin >> b.coefficient[i];
			a.sum(b).print(t);
		}
		if (s == "dif") {
			std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
			std::cin >> t;
			while (t != "yes" && t != "no") {
				std::cout << "wrong input\n";
				std::cin >> t;
			}
			polynomial a, b;
			std::cin >> a.exponentiation;
			a.coefficient.resize((size_t)(a.exponentiation + 1LL));
			for (size_t i = 0; i < a.coefficient.size(); ++i)
				std::cin >> a.coefficient[i];
			std::cin >> b.exponentiation;
			b.coefficient.resize((size_t)(b.exponentiation + 1LL));
			for (size_t i = 0; i < b.coefficient.size(); ++i)
				std::cin >> b.coefficient[i];
			a.dif(b).print(t);
		}
		if (s == "mul") {
			std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
			std::cin >> t;
			while (t != "yes" && t != "no") {
				std::cout << "wrong input\n";
				std::cin >> t;
			}
			polynomial a, b;
			std::cin >> a.exponentiation;
			a.coefficient.resize((size_t)(a.exponentiation + 1LL));
			for (size_t i = 0; i < a.coefficient.size(); ++i)
				std::cin >> a.coefficient[i];
			std::cin >> b.exponentiation;
			b.coefficient.resize((size_t)(b.exponentiation + 1LL));
			for (size_t i = 0; i < b.coefficient.size(); ++i)
				std::cin >> b.coefficient[i];
			a.mul(b).print(t);
		}
		if (s == "exit")
			return 0;
	}
}
