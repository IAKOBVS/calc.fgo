#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumBuff(char *argv[], int currArg, int argvLen){
	char numInString[argvLen];
	int j=0;
	for (int i=2; i<argvLen; ++i){
		numInString[j] = argv[currArg][i];
		j++;
	}
	return strtol(numInString, NULL, 10);
}

float ifNotZero(float var, float total){
	if (var != 0){
		return total * var;
	}
	return total;
}

int strInStr(int substrLen, const char substr[substrLen], char *argv[], int currArgv){
	if (argv[currArgv][0] != substr[0]){
		return 0;
	}
	int i=0;
	while (argv[currArgv][i] != 0){
		if (argv[currArgv][i] == substr[i]){
			if (i == 1){
				return 1;
			}
		}
		++i;
	}
	return 0;
}

int main(int argc, char *argv[]){

	int ARTS = 0;
	int BUSTER = 0;
	int QUICK = 0;

	int at = 0;
	int am = 0;
	int bm = 0;
	int qm = 0;
	int se = 0;
	float st = 0;
	int pm = 0;
	int np = 0;
	int cd = 0;

	for (int currArgv=1; currArgv<argc; ++currArgv){

		int argvLen = strlen(argv[currArgv]);

			if (strInStr(2, "at", argv, currArgv)){
				at = at + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "bm", argv, currArgv)){
				bm = bm + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "qm", argv, currArgv)){
				qm = qm + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "am", argv, currArgv)){
				am = am + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "pm", argv, currArgv)){
				pm = pm + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "np", argv, currArgv)){
				np = np + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "cd", argv, currArgv)){
				cd = cd + sumBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "se", argv, currArgv)){
				se = sumBuff(argv, currArgv, argvLen) / 100.0;

			} else if (strInStr(2, "st", argv, currArgv)){
				st = 1.33333333333;

			} else if (strInStr(2, "aa", argv, currArgv)){
				ARTS = 1;

			} else if (strInStr(2, "bb", argv, currArgv)){
				BUSTER = 1;

			} else if (strInStr(2, "qq", argv, currArgv)){
				QUICK = 1;

			/* aliases */
			} else if (strInStr(2, "vi", argv, currArgv)){
				bm = bm + 100;
				cd = cd + 100;

			} else if (strInStr(2, "ss", argv, currArgv)){
				at = at + 40;
				bm = bm + 30;
				qm = qm + 130;
				if (BUSTER != 0){
					cd = cd + 200;
				}

			} else if (strInStr(2, "sk", argv, currArgv)){
				at = at + 60;
				qm = qm + 100;
				cd = cd + cd + 200;

			} else if (strInStr(2, "ca", argv, currArgv)){
				am = am + 100;
				at = at + 40;
			}
	}
	float total = 1;

	if (ARTS != 0){
		total = ifNotZero(am, total);

	} else if (BUSTER != 0){
		total = ifNotZero(bm, total);

	} else if (QUICK != 0){
		total = ifNotZero(qm, total);
	}

	total = ifNotZero(at, total);
	total = ifNotZero(pm, total);
	total = ifNotZero(np, total);
	total = ifNotZero(se, total);
	total = ifNotZero(st, total);

	printf("%f\n", total);
	return 0;
}
