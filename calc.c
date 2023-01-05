#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float toPercent(int var){
	if (!var){
		return 1.0;
	}
	return (1.0 + (float)var * 0.01);
}

int getBuff(char *argv[], int currArg, int argvLen){
	char numInString[argvLen];
	int j=0;
	for (int i=2; i<argvLen; ++i){
		numInString[j] = argv[currArg][i];
		j++;
	}
	return (strtol(numInString, NULL, 10));
}

float ifNotZeroFl(float var){
	if (!var){
		return 1.0;
	}
	return var;
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

	int attackStat = 0;

	int ARTS = 0;
	int BUSTER = 0;
	int QUICK = 0;

	int au = 0;
	int ad = 0;

	int am = 0;
	int bm = 0;
	int qm = 0;

	float se = 0;
	float st = 0;

	int pm = 0;
	int nm = 0;
	int cd = 0;

	for (int currArgv=1; currArgv<argc; ++currArgv){

		int argvLen = strlen(argv[currArgv]);

			if (strInStr(2, "au", argv, currArgv)){
				au = au + getBuff(argv, currArgv, argvLen);

			if (strInStr(2, "ad", argv, currArgv)){
				ad = ad - getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "bm", argv, currArgv)){
				bm = bm + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "qm", argv, currArgv)){
				qm = qm + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "am", argv, currArgv)){
				am = am + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "pm", argv, currArgv)){
				pm = pm + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "nm", argv, currArgv)){
				nm = nm + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "cd", argv, currArgv)){
				cd = cd + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "se", argv, currArgv)){
				se = getBuff(argv, currArgv, argvLen) / 100.0;

			/* base stat */
			} else if (strInStr(2, "sa", argv, currArgv)){
				attackStat = getBuff(argv, currArgv, argvLen);
			/* */

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
				au = au + 40;
				bm = bm + 30;
				qm = qm + 130;
				if (BUSTER){
					cd = cd + 200;
				}

			} else if (strInStr(2, "sk", argv, currArgv)){
				au = au + 60;
				qm = qm + 100;
				cd = cd + cd + 200;

			} else if (strInStr(2, "ca", argv, currArgv)){
				am = am + 100;
				au = au + 40;
			}
		}
	}
	au = au - ad;

	float total = 1;

	if (ARTS){
		total = toPercent(am);

	} else if (BUSTER){
		total = toPercent(bm);

	} else if (QUICK){
		total = toPercent(qm);
	}

	if (attackStat){
		total = total * (float)attackStat;
	}
	
	const float constMult = 0.23;

	total = total * toPercent(au) * constMult;

	float totalCard = 1;
	float totalNp = 1;

	cd = cd + pm;
	totalCard = total * toPercent(cd);

	nm = nm + pm;
	totalNp = total * toPercent(nm) * ifNotZeroFl(se) * ifNotZeroFl(st);

	/* setlocale(LC_NUMERIC, ""); */

	/* printf("%'g\n", totalCard); */
	/* printf("%'g\n", totalNp); */

	printf("%f\n", totalCard);
	printf("%f\n", totalNp);

	printf("%d\n", attackStat);
	return 0;
}
