#include <stdio.h>
#include <stdlib.h>
#define OPEN_FAILURE -1
unsigned long int charkey2int(char key[]) {
	unsigned long int i_key = 0;
	for (int range = 0; range < 16; range++) {
		printf("%hhx\n", key[range]);
		printf("i_key before:%lx\n", i_key);
		i_key += (long)key[range];
		i_key *= 256;
		printf("%lx\n", i_key);
	}
	printf("%lx\n", i_key);
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