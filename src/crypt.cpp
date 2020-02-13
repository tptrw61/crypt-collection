#include <stdio.h>
#include <string>
#include "../inc/crypt.h"
#include "../inc/text_cipher.h"
#include "../inc/data_cipher.h"

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "%s: missing type. See '%s -h' for details\n", argv[0], argv[0]);
		return 1;
	}
	std::string cryptType = argv[1];
	if (cryptType.compare("-h") == 0 || cryptType.compare("--help") == 0) {
		printf("usage: %s [-h|--help] <type> <e|d> <type-opts> [file]\n", argv[0]);
		printf("---TEXT TYPES---\n");
		printf(TEXT_SHIFT" - Caeser Cipher\n");
		printf("---DATA TYPES---\n");
		printf("----------------\n");
		printf("More to come...\n");
		return 0;
	}
	//
	if (cryptType.compare(TEXT_SHIFT) == 0) {
		//
	} else {
		fprintf(stderr, "%s: invalid type '%s'. See '%s -h' for details\n", argv[0], argv[1], argv[0]);
		return 1;
	}
	//
	std::string cryptDir = argv[2];
	if (cryptDir.compare("e") == 0) {}
	return 0;
}
