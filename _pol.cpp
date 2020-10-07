#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



template <typename T>
T fastpow(T a, T b) {
	if (!b)
		return 1;
	return b % 2 ? a * fastpow(a, b - 1) : fastpow(a * a, b / 2);
}



template <typename T>
struct polynomial {
	T exponentiation = NULL;
	std::vector <T> coefficient;

	T val(T x) {
		T value = 0;
		for (T i = 0; i <= exponentiation; ++i)
			value += coefficient[i] * fastpow(x, exponentiation - i);
		return value;
	}

	polynomial <T> operator+(polynomial <T> &b) {
		polynomial <T> c;
		std::vector <T> vec1 = coefficient, vec2 = b.coefficient;
		reverse(vec1.begin(), vec1.end());
		reverse(vec2.begin(), vec2.end());
		for (T i = 0; i <= std::min(exponentiation, b.exponentiation); ++i)
			c.coefficient.push_back(vec1[i] + vec2[i]);
		if (exponentiation > b.exponentiation) {
			for (T i = b.exponentiation + 1; i <= exponentiation; ++i)
				c.coefficient.push_back(vec1[i]);
		}
		else {
			for (T i = exponentiation + 1; i <= b.exponentiation; ++i)
				c.coefficient.push_back(vec2[i]);
		}
		c.to_normal_view();
		return c;
	}

	polynomial <T> operator-(polynomial <T> &b) {
		polynomial <T> c;
		std::vector <T> vec1 = coefficient, vec2 = b.coefficient;
		reverse(vec1.begin(), vec1.end());
		reverse(vec2.begin(), vec2.end());
		for (T i = 0; i <= std::min(exponentiation, b.exponentiation); ++i)
			c.coefficient.push_back(vec1[i] - vec2[i]);
		if (exponentiation > b.exponentiation) {
			for (T i = b.exponentiation + 1; i <= exponentiation; ++i)
				c.coefficient.push_back(vec1[i]);
		}
		else {
			for (T i = exponentiation + 1; i <= b.exponentiation; ++i)
				c.coefficient.push_back(-vec2[i]);
		}
		c.to_normal_view();
		return c;
	}

	polynomial <T> operator*(polynomial <T> &b) {
		polynomial <T> c;
		std::vector <T> vec1 = coefficient, vec2 = b.coefficient;
		reverse(vec1.begin(), vec1.end());
		reverse(vec2.begin(), vec2.end());
		while (vec1.size() < vec2.size())
			vec1.push_back(0);
		while (vec2.size() < vec1.size())
			vec2.push_back(0);
		c.coefficient.resize(vec1.size() + vec2.size(), 0);
		for (size_t i = 0; i < vec1.size(); ++i) {
			for (size_t j = 0; j < vec2.size(); ++j)
				c.coefficient[i + j] += vec1[i] * vec2[j];
		}
		c.to_normal_view();
		return c;
	}

	void to_normal_view() {
		while (!(coefficient.empty() || coefficient[coefficient.size() - 1]))
			coefficient.pop_back();		
		if (!coefficient.size())
			coefficient.push_back(0);
		reverse(coefficient.begin(), coefficient.end());
		exponentiation = coefficient.size() - 1;
	}

	void print(std::string t) {
		if (t == "yes") {
			for (size_t i = 0; i <= exponentiation; ++i)
				std::cout << coefficient[i] << ' ';
			std::cout << '\n';
		}
		else {
			if (!exponentiation) {
				std::cout << coefficient[0] << '\n';
				return;
			}
			if (exponentiation == 1) {
				if (coefficient[0] != 1) {
					if (coefficient[0] != -1)
						std::cout << coefficient[0];
					else
						std::cout << '-';
				}
				std::cout << 'x';
				if (coefficient[1]) {
					if (coefficient[1] > 0)
						std::cout << '+';
					std::cout << coefficient[1];
				}
				std::cout << '\n';
				return;
			}
			if (coefficient[0] != 1) {
				if (coefficient[0] != -1)
					std::cout << coefficient[0];
				else
					std::cout << '-';
			}
			std::cout << "x^" << exponentiation;
			for (T i = 1; i <= exponentiation - 2; ++i) {
				if (coefficient[i]) {
					if (coefficient[i] > 0)
						std::cout << '+';
					if (coefficient[i] == -1)
						std::cout << '-';
					else {
						if (coefficient[i] != 1)
							std::cout << coefficient[i];
					}
					std::cout << "x^" << exponentiation - i;
				}
			}
			if (coefficient[exponentiation - 1]) {
				if (coefficient[exponentiation - 1] > 0)
					std::cout << '+';
				if (coefficient[exponentiation - 1] == -1)
					std::cout << '-';
				else {
					if (coefficient[exponentiation - 1] != 1)
						std::cout << coefficient[exponentiation - 1];
				}
				std::cout << 'x';
			}
			if (coefficient[exponentiation]) {
				if (coefficient[exponentiation] > 0)
					std::cout << '+';
				std::cout << coefficient[exponentiation];
			}
			std::cout << '\n';
		}
	}
};


template <typename T>
std::istream& operator>> (std::istream& in, polynomial <T> &pol) {
	using namespace std;
	string _str;
	getline(cin, _str);
	vector<char> str;
	for (int i = 0; i < _str.size(); i++) {
		if (_str[i] != ' ') {
			str.push_back(_str[i]);
		}
	}
	int cod = 0, pos = 0, num = 0, numc = 0;
	bool sign = 0;;
	while (pos < str.size()) {
		if (str[pos] >= '0' && str[pos] <= '9') {
			num = num * 10 + (str[pos] - '0');
			pos++;
		}
		else if ((str[pos] >= 'a' && str[pos] <= 'z') || (str[pos] >= 'A' && str[pos] <= 'Z')) {
			if (sign) {
				num = -num;
			}
			pos++;
			long long num1 = 1;
			if (pos < str.size() && str[pos] == '^') {
				pos++;
				num1 = 0;
				while (str[pos] >= '0' && str[pos] <= '9') {
					num1 = num1 * 10 + (str[pos] - '0');
					pos++;
				}
			}
			if (pol.exponentiation == NULL) {
				pol.exponentiation = num1;
				pol.coefficient.resize(num1 + 1);
			}
			for (numc; numc < pol.exponentiation - num1; numc++) {
				pol.coefficient[numc] = 0;
			}
			if (num == 0) {
				pol.coefficient[numc] = 1;
			}
			else {
				pol.coefficient[numc] = num;
			}
			num = 0;
			numc++;
		}
		else if (str[pos] == '-') {
			sign = 1;
			pos++;
		}
		else if (str[pos] == '+') {
			sign = 0;
			pos++;
		}
	}
	if (sign) {
		num = -num;
	}
	for (numc; numc < pol.exponentiation; numc++) {
		pol.coefficient[numc] = 0;
	}
	pol.coefficient[numc] = num;
	return in;
}


template <typename T>
polynomial <T> pw(polynomial <T> a, T k) {
	if (!k)
		return { 0, { 1 } };
	return k % 2 ? a * pw(a, k - 1) : pw(a * a, k / 2);
}


signed main() {
	std::cout << "available operations:\nval\n+\n-\n*\nexit\n";
	std::string s, t;
	while (true) {
		std::cin >> s;
		if (s == "val") {
			polynomial <long long> a;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a;
			long long x;
			std::cin >> x;
			std::cout << a.val(x) << '\n';
		}
		if (s == "+") {
			std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
			std::cin >> t;
			while (t != "yes" && t != "no") {
				std::cout << "wrong input\n";
				std::cin >> t;
			}
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(a + b).print(t);
		}
		if (s == "-") {
			std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
			std::cin >> t;
			while (t != "yes" && t != "no") {
				std::cout << "wrong input\n";
				std::cin >> t;
			}
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(a - b).print(t);
		}
		if (s == "*") {
			std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
			std::cin >> t;
			while (t != "yes" && t != "no") {
				std::cout << "wrong input\n";
				std::cin >> t;
			}
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(a * b).print(t);
		}
		if (s == "exit")
			return 0;
	}
}
