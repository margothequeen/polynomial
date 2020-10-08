#include "C:\mylib\polynomial.lib"

signed main() {
	std::string s, t;
	std::cout << "do you need only coefficients?\nchoose 'yes' or 'no'\n";
	std::cin >> t;
	while (t != "yes" && t != "no") {
		std::cout << "wrong input\n";
		std::cin >> t;
	}
	std::cout << "available operations:\nval\n+\n-\n*\ngcd\nexit\n";
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
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(a + b).print(t);
		}
		if (s == "-") {
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(a - b).print(t);
		}
		if (s == "*") {
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(a * b).print(t);
		}
		if (s == "gcd") {
			std::cout << "sorry, this action temporarily unavailable\n";
			/*
			polynomial <long long> a, b;
			std::string q;
			std::getline(std::cin, q);
			std::cin >> a >> b;
			(gcd(a, b)).print("");
			*/
		}
		if (s == "exit")
			return 0;
	}
}
