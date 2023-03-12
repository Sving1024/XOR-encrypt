#include "securitykey.h"
#include "encrypt.h"
int main(int argc,char *argv[]) {
	unsigned char skey[KEY_LENGTH];
	int num1;
	bool next = false;
	if (argc < 3) {
		printf("Useage: applicationname input_file output_file");
	}
	else {
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
		printkey(skey);
		printf("countiune?[enter]");
		getchar();
		if (xeoren(argv[1], argv[2], skey) == OPEN_FAILURE) {
			printf("failed in openng files:%s or %s", argv[1], argv[2]);
			printf("Useage: applicationname input_file output_file");
		}
	}
	
	return 0;
}
