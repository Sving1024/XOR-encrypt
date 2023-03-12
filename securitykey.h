#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define KEY_LENGTH 24
#define RANDOM_KEY 1
#define INPUT_KEY 0
#define INPUT_ERROR 2
int genkey(unsigned char skey[]) {
	srand(time(NULL));
	for (int range = 0; range <= KEY_LENGTH - 1; range++)
		skey[range] = 16 + rand() % 240;
	return 0;
}
void printkey(unsigned char key[]) {
	for (int range = 0; range <= KEY_LENGTH - 1;range++) {
		printf("%hhX", key[range]);
		if (range % 2 == 1&&range<KEY_LENGTH-1)
			printf("-");
	}
	printf("\n");
	return;
}
int getkey(unsigned char key[]) {
	int return_val=-1;
	char ch,ch2;
	printf("enter the key pls(space to use random key):");
	ch2 = getchar();
	if (ch2 == '\n' || ch2 == ' ') {
		return_val = RANDOM_KEY;
	}
	else {
		ungetc(ch2, stdin);
		for (int range = 0; range <= KEY_LENGTH - 1; range++) {
			int return1;
			return1=scanf("%2hhx", &ch);
			if (return1 != 1) {
				return_val = INPUT_ERROR;
				break;
			}
			key[range] = ch;
			if (range % 2 == 1 && (range / 2) < (KEY_LENGTH - 1) / 2) {
				char a = getchar();
				if (a == '-')
					continue;
				else {
					return_val = INPUT_ERROR;
					break;
				}

			}
		}
		if (return_val != INPUT_ERROR) {
			getchar();
			return_val = INPUT_KEY;
		}
		else {
			while (getchar()!= '\n')
				continue;
		}
	}
	return return_val;
}