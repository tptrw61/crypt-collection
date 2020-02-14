#include <stdio.h>
#include <string>
#include "../inc/crypt.h"
#include "../inc/text_cipher.h"
#include "../inc/data_cipher.h"

//int driver(char op, int argc, char **argv);
using DriverFunc = int (*)(char , int, char **);

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "%s: missing type. See '%s -h' for details\n", argv[0], argv[0]);
		return 1;
	}
	std::string cryptType = argv[1];
	if (cryptType.compare("-h") == 0 || cryptType.compare("--help") == 0) {
		printf("usage: %s [-h|--help] <type> <operation> <type-opts> [file]\n", argv[0]);
		printf("\n---TEXT TYPES---\n");
		printf(" %s - Caeser Cipher\n", TEXT_SHIFT);
		printf("\n---DATA TYPES---\n");
		printf("----------------\n");
		printf("More to come...\n");
		return 0;
	}
	//
	DriverFunc driver = nullptr;
	if (cryptType.compare(TEXT_SHIFT) == 0) {
		driver = Crypt::Text::Driver::shift;
	} else {
		fprintf(stderr, "%s: invalid type '%s'. See '%s -h' for details\n", argv[0], argv[1], argv[0]);
		return 1;
	}

	//check that operation argument exists
	char op = '?';
	if (argc == 2) {
		op = ' ';
	} else {
		std::string oper = "0", optoper = "-0";
		char c, C;
		for (c = 'a', C = 'A'; c <= 'z'; c++, C++) {
			oper[0] = c;
			optoper[1] = c;
			if (oper.compare(argv[2]) == 0 || optoper.compare(argv[2]) == 0)
				op = c;
			oper[0] = C;
			optoper[1] = C;
			if (oper.compare(argv[2]) == 0 || optoper.compare(argv[2]) == 0)
				op = C;
		}
		oper = "--help";
		if (oper.compare(argv[2]) == 0)
			op = 'h';
	}

	return driver(op, argc, argv);
}
