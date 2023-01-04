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

	const char *buffs[8];
	buffs[0] = "am";
	buffs[1] = "bm";
	buffs[2] = "qm";
	buffs[3] = "at";
	buffs[4] = "pm";
	buffs[5] = "np";
	buffs[6] = "se";
	buffs[7] = "st";

	int at = 0;
	int am = 0;
	int bm = 0;
	int qm = 0;
	int se = 0;
	float st = 0;
	int pm = 0;
	int np = 0;

	for (int currArgv=1; currArgv<argc; ++currArgv){

		int argvLen = strlen(argv[currArgv]);
		for (int i=0; i<=7; ++i){

			if (strInStr(2, buffs[i], argv, currArgv)){

				if (strcmp(buffs[i], "at") == 0){
					at = at + sumBuff(argv, currArgv, argvLen);

				} else if (strcmp(buffs[i], "bm") == 0){
					bm = bm + sumBuff(argv, currArgv, argvLen);

				} else if (strcmp(buffs[i], "qm") == 0){
					qm = qm + sumBuff(argv, currArgv, argvLen);

				} else if (strcmp(buffs[i], "am") == 0){
					am = am + sumBuff(argv, currArgv, argvLen);

				} else if (strcmp(buffs[i], "pm") == 0){
					pm = pm + sumBuff(argv, currArgv, argvLen);

				} else if (strcmp(buffs[i], "np") == 0){
					np = np + sumBuff(argv, currArgv, argvLen);

				} else if (strcmp(buffs[i], "se") == 0){
					se = sumBuff(argv, currArgv, argvLen) / 100.0;

				} else if (strcmp(buffs[i], "st") == 0){
					st = 1.33333333333;

				}
			} else{
				if (strInStr(2, "aa", argv, currArgv)){
					ARTS = 1;

				} else if (strInStr(2, "bb", argv, currArgv)){
					BUSTER = 1;

				} else if (strInStr(2, "qq", argv, currArgv)){
					QUICK = 1;
				}
			}
		}
	}
	float total = 1;

	if (ARTS){
		total = ifNotZero(am, total);

	} else if (BUSTER){
		total = ifNotZero(bm, total);

	} else if (QUICK){
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
