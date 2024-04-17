#pragma once
#include <iostream>

const size_t MAX = 100;

class Octal
{
	unsigned char number[MAX];
	size_t size;
public:
	Octal();
	bool operator==(const Octal& x) const;
	bool operator<(const Octal& x) const;
	friend std::ostream& operator<<(std::ostream& stream, const Octal& x);
	friend std::istream& operator>>(std::istream& stream, Octal& x);
};