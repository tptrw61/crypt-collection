#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "../../../inc/text/shift.h"

using Shift = Crypt::Text::Shift;

static bool isInt(const char *s) {
	if (s == NULL)
		return 0;
	const char *sp;
	size_t size;
	if (s[0] == '-')
		sp = s+1;
	else
		sp = s;
	size = strlen(sp);
	if (size == 0)
		return 0;
	for (; *sp != '\0'; sp++)
		if (*sp < '0' || *sp > '9')
			return 0;
	return 1;
}

int Crypt::Text::Driver::shift(char op, int argc, char **argv) {
	int ac = argc - 3;
	char **av = argv + 3;
	if (op == ' ') {
		fprintf(stderr, "%s: missing operation\n", argv[0]);
		return 1;
	}
	switch (op) {
		case 'h':
		case 'e':
		case 'd':
			break;
		default:
			fprintf(stderr, "%s: invalid operation '%s'\n", argv[0], argv[2]);
			return 1;
	}
	if (op == 'h') {
		// TODO print help message
		printf("usage: %s %s <oper> <shiftn> [file...]\n", argv[0], argv[1]);
		printf("---OPERATIONS---\n");
		printf(" e - encrypt\n");
		printf(" d - decrypt\n");
		printf(" h - help message\n");
		return 0;
	}
	if (ac == 0) {
		fprintf(stderr, "%s: missing shift distance\n", argv[0]);
		return 1;
	}
	if (!isInt(av[0])) {
		fprintf(stderr, "%s: shift distance must be an integer\n", argv[0]);
		return 1;
	}

	std::string s;
	char *buffer = NULL;
	size_t n = 0;
	size_t buflen;
	Shift shift(atoi(av[0]));
	auto readin = [&](FILE *strm) -> void {
		while (getline(&buffer, &n, strm) != EOF) {
			buflen = strlen(buffer);
			if (buffer[buflen-1] == '\n')
				buffer[buflen-1] = '\0';
			if (op == 'e')
				s = shift.encrypt(buffer);
			else
				s = shift.decrypt(buffer);
			printf("%s\n", s.c_str());
		}
	};
	if (ac == 1) {
		readin(stdin);
	} else {
		FILE *file;
		for (int i = 1; i < ac; i++) {
			file = fopen(av[i], "r");
			if (file == NULL) {
				perror(argv[0]);
				continue;
			}
			readin(file);
			fclose(file);
		}
	}
	free(buffer);
	return 0;
}
