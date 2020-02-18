#include "../../inc/util/galois.h"

#define GALOIS Crypt::Util::Galois
using Gal = GALOIS;

static Gal galoisInvTable[256];
static bool galoisInvTableGenerated = false;
static void genGaloisInvTable() {
	galoisInvTable[0] = (Gal)0;
	galoisInvTable[1] = (Gal)1;
	for (int i = 2; i < 256; i++) {
		for (int j = i + 1; j < 256; j++) {
			if ((Gal)i * (Gal)j == (Gal)1) {
				galoisInvTable[i] = (Gal)j;
				galoisInvTable[j] = (Gal)i;
			}
		}
	}
	galoisInvTableGenerated = true;
}

GALOIS::Galois() : m_x(0) {}
GALOIS::Galois(uint8_t x) : m_x(x) {}
GALOIS::Galois(const Galois& g) : m_x(g.m_x) {}

Gal& GALOIS::operator=(const Galois& g) {
	m_x = g.m_x;
	return *this;
}

bool GALOIS::operator==(const Galois& g) const {
	return m_x == g.m_x;
}
bool GALOIS::operator!=(const Galois& g) const {
	return m_x != g.m_x;
}

Gal GALOIS::operator-() const {
	return *this;
}

Gal GALOIS::operator+(const Galois& g) const {
	return Galois(m_x ^ g.m_x);
}
Gal GALOIS::operator-(const Galois& g) const {
	return Galois(m_x ^ g.m_x);
}
Gal GALOIS::operator*(const Galois& g) const {
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

Gal& GALOIS::operator+=(const Galois& g) {
	return *this = *this + g;
}
Gal& GALOIS::operator-=(const Galois& g) {
	return *this = *this - g;
}
Gal& GALOIS::operator*=(const Galois& g) {
	return *this = *this * g;
}

Gal GALOIS::inv() const {
	if (!galoisInvTableGenerated)
		genGaloisInvTable();
	return galoisInvTable[m_x];
}
Gal GALOIS::inv(Galois g) {
	if (!galoisInvTableGenerated)
		genGaloisInvTable();
	return galoisInvTable[g.m_x];
}

GALOIS::operator uint8_t() const {
	return m_x;
}
GALOIS::operator int() const {
	return (int)m_x;
}
