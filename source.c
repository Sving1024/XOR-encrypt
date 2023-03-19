#include <string.h>
#include "encrypt.h"
int main(int argc,char *argv[]) {
	unsigned char skey[KEY_LENGTH];
	int num1;
	unsigned long long int i_key[3];
	bool next = false;
	if (argc < 2) {
		printf("Useage: applicationname input_file");
	}
	else {
		int size_argv = strlen(argv[1]);
		char out[size_argv + 4];
		strncpy(out, argv[1], size_argv + 4);
		strncat(out, ".xe", size_argv + 4);
		while (next != true) {
			num1 = getkey(skey);
			switch (num1) {
			case INPUT_KEY:
				next = true;
				break;
			case RANDOM_KEY:
				genkey(skey);
				next = true;
				break;
			case INPUT_ERROR:
				printf("INPUT ERROR\n");
				break;
			default:
				printf("undefined return value\n");
				break;
			}
		}
		printf("%s", out);
		printf("\n\t");
		printkey(skey);
		printf("countiune?[enter]");
		getchar();
		if (xeoren(argv[1], out, skey) == OPEN_FAILURE) {
			printf("failed in openng files:%s or %s", argv[1], argv[2]);
			printf("Useage: applicationname input_file output_file");
		}
	}
	
	return 0;
}
