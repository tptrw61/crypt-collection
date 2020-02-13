#ifndef GALOIS_H_INCLUDED
#define GALOIS_H_INCLUDED
#include <stdint.h>

#

class Galois {
private:
	uint8_t m_x;
public:
	Galois();
	explicit Galois(uint8_t x);
	Galois(const Galois& g);
	
	Galois& operator=(const Galois& g);

	bool operator==(const Galois& g) const;
	bool operator!=(const Galois& g) const;

	Galois operator-() const;

	Galois operator+(const Galois& g) const;
	Galois operator-(const Galois& g) const;
	Galois operator*(const Galois& g) const;

	Galois& operator+=(const Galois& g);
	Galois& operator-=(const Galois& g);
	Galois& operator*=(const Galois& g);

	Galois inv() const;
	static Galois inv(Galois g);

	explicit operator uint8_t() const;
	explicit operator int() const;
};

#endif //GALOIS_H_INCLUDED
