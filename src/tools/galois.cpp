#include "galois.h"

static Galois galoisInvTable[256];
static bool galoisInvTableGenerated = false;
static void genGaloisInvTable() {
	galoisInvTable[0] = (Galois)0;
	galoisInvTable[1] = (Galois)1;
	for (int i = 2; i < 256; i++) {
		for (int j = i + 1; j < 256; j++) {
			if ((Galois)i * (Galois)j == (Galois)1) {
				galoisInvTable[i] = (Galois)j;
				galoisInvTable[j] = (Galois)i;
			}
		}
	}
	galoisInvTableGenerated = true;
}

Galois::Galois() : m_x(0) {}
Galois::Galois(uint8_t x) : m_x(x) {}
Galois::Galois(const Galois& g) : m_x(g.m_x) {}

Galois& Galois::operator=(const Galois& g) {
	m_x = g.m_x;
	return *this;
}

bool Galois::operator==(const Galois& g) const {
	return m_x == g.m_x;
}
bool Galois::operator!=(const Galois& g) const {
	return m_x != g.m_x;
}

Galois Galois::operator-() const {
	return *this;
}

Galois Galois::operator+(const Galois& g) const {
	return Galois(m_x ^ g.m_x);
}
Galois Galois::operator-(const Galois& g) const {
	return Galois(m_x ^ g.m_x);
}
Galois Galois::operator*(const Galois& g) const {
	uint8_t p = 0;
	uint8_t high;
	uint8_t a = m_x;
	uint8_t b = g.m_x;
	for (int i = 0; i < 8; i++) {
		if (b & 1)
			p ^= a;
		high = (a & 0x80) != 0;
		a <<= 1;
		if (high)
			a ^= 0x1b;
		b >>= 1;
	}
	return (Galois)p;
}

Galois& Galois::operator+=(const Galois& g) {
	return *this = *this + g;
}
Galois& Galois::operator-=(const Galois& g) {
	return *this = *this - g;
}
Galois& Galois::operator*=(const Galois& g) {
	return *this = *this * g;
}

Galois Galois::inv() const {
	if (!galoisInvTableGenerated)
		genGaloisInvTable();
	return galoisInvTable[m_x];
}
Galois Galois::inv(Galois g) {
	if (!galoisInvTableGenerated)
		genGaloisInvTable();
	return galoisInvTable[g.m_x];
}

Galois::operator uint8_t() const {
	return m_x;
}
Galois::operator int() const {
	return (int)m_x;
}
