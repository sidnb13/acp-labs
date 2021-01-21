#include <cstdio>
#include <cstring>
#include <iostream>


class Disc {
	int size{};
	
public:
	Disc() = default;
	explicit Disc(const int& size);
	~Disc() = default;
    [[nodiscard]] int getSize() const;
	bool setSize(const int& s);
	[[nodiscard]] std::string toString() const;
};
