#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define OPEN_FAILURE -1
#define KEY_LENGTH 24
#define RANDOM_KEY 1
#define INPUT_KEY 0
#define INPUT_ERROR 2
unsigned long long int charkey2int(char key[],long long outkey[]) {
	unsigned long long int i_key = 0;
	int counter = 0;
	for (int range = 0; range < KEY_LENGTH; range++) {
		printf("%hhx\n", key[range]);
	}
	for (int range = 0; counter < KEY_LENGTH/8 ; range++) {
		//printf("%hhx\n", key[range]);
		//printf("i_key before:%llx\n", i_key);
		i_key <<= 8;
		//printf("%llx\n", i_key);
		i_key += key[range];
		//printf("%llx\n", i_key);
		if (range % 8 == 7) {
			outkey[counter] = i_key;
			counter++;
		}
	}
	printf("%llx\n", i_key);
	return i_key;
}
long int file_size(char file[]) {
	long int size1;
	FILE *fp = fopen(file, "rb");
	if (fp == NULL) {
		size1 = OPEN_FAILURE;
	}
	else {
		fseek(fp, 0, SEEK_END);
		size1 = ftell(fp);
		fclose(fp);
	}
	return size1;
}
int xeoren(char input[], char output[], unsigned char key[]) {
	char ch,ch_output;
	int range = 0;
	int return_val;
	long counter = 1;
	FILE* fp_input = fopen(input, "rb"), * fp_output = fopen(output, "wb");
	if (fp_input != NULL && fp_output != NULL) {
		while (counter <= file_size(input)) {
			ch = getc(fp_input);
			ch_output = ch ^ key[range];
			putc(ch_output, fp_output);
			printf("%d:%hhx\n", counter, ch_output);
			range++;
			counter++;
			if (range >= 24)
				range = 0;
		}
		return_val = 0;
	}
	else {
		return_val = OPEN_FAILURE;
	}
	fclose(fp_input);
	fclose(fp_output);
	return return_val;
}
int genkey(unsigned char skey[]) {
	srand(time(NULL));
	for (int range = 0; range < KEY_LENGTH; range++)
		skey[range] = 16 + rand() % 240;
	return 0;
}
void printkey(unsigned char key[]) {
	for (int range = 0; range <= KEY_LENGTH - 1; range++) {
		printf("%hhX", key[range]);
		if (range % 2 == 1 && range < KEY_LENGTH - 1)
			printf("-");
	}
	printf("\n");
	return;
}
int getkey(unsigned char key[]) {
	int return_val = -1;
	char ch, ch2;
	printf("enter the key pls(space to use random key):");
	ch2 = getchar();
	if (ch2 == '\n' || ch2 == ' ') {
		return_val = RANDOM_KEY;
	}
	else {
		ungetc(ch2, stdin);
		for (int range = 0; range <= KEY_LENGTH - 1; range++) {
			int return1;
			return1 = scanf("%2hhx", &ch);
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
			while (getchar() != '\n')
				continue;
		}
	}
	return return_val;
}