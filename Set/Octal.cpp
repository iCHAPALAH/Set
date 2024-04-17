#include "Octal.h"

Octal::Octal()
{
	size = 0;
	for (size_t i = 0; i < MAX; ++i)
		number[i] = 0;
}

bool Octal::operator==(const Octal& x) const
{
	return !(*this < x) && !(x < *this);
}

bool Octal::operator<(const Octal& x) const
{
	bool result = false;
	if (this->size < x.size)
		result = true;
	else if (this->size == x.size)
	{
		bool trigger = true;
		for (size_t i = x.size; i != 0 && trigger; --i)
			if (this->number[i - 1] != x.number[i - 1])
			{
				trigger = false;
				result = this->number[i - 1] < x.number[i - 1];
			}
	}
	return result;
}

std::ostream& operator<<(std::ostream& stream, const Octal& x)
{
	for (size_t i = x.size; i != 0; --i)
		stream << +x.number[i - 1];
	return stream;
}

std::istream& operator>>(std::istream& stream, Octal& x)
{
	x.size = 0;
	bool trigger = true;
	while (!stream.fail() && trigger)
	{
		char c = stream.peek();
		if (c == ' ' || c == '\n')
			stream.get();
		else if (c >= '0' && c <= '7')
			trigger = false;
		else
			stream.setstate(std::ios::failbit);
	}
	while (!stream.fail() && !trigger)
	{
		char c = stream.peek();
		if (c >= '0' && c <= '7')
			x.number[x.size++] = stream.get() - '0';
		else
			trigger = true;
	}
	for (int i = 0; i < x.size / 2; ++i)
		std::swap(x.number[i], x.number[x.size - i - 1]);
	return stream;
}