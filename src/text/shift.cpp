#include "shift.h"

#define CRYPT Crypt::Text
#define SHIFT CRYPT::Shift

static char shiftChar(char c, int shift) {
	if (c >= 'a' && c <= 'z') {
		c -= 'a';
		c += shift;
		c %= 26;
		if (c < 0)
			c += 26;
		return c + 'a';
	}
	if (c >= 'A' && c <= 'Z') {
		c -= 'A';
		c += shift;
		c %= 26;
		if (c < 0)
			c += 26;
		return c + 'A';
	}
	return c;
}

SHIFT::Shift() : m_shift(0) {}
SHIFT::Shift(int shift) : m_shift(shift) {}
SHIFT::~Shift() {}

std::string SHIFT::encrypt(const StrType& s) const {
	return encrypt(s, m_shift);
}
std::string SHIFT::encrypt(const StrType& s, int shift) {
	std::string e;
	for (size_t i = 0; i < s.size(); i++)
		e.push_back(shiftChar(s[i], shift));
	return e;
}

std::string SHIFT::decrypt(const StrType& s) const {
	return decrypt(s, m_shift);
}
std::string SHIFT::decrypt(const StrType& s, int shift) {
	std::string d;
	for (size_t i = 0; i < s.size(); i++)
		d.push_back(shiftChar(s[i], -shift));
	return d;
}
