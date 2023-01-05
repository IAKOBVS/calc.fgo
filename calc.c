#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> /* thousand separator */

float whichNpMod(int np, float caseOne, float caseTwo, float caseThree, float caseFour, float caseDefault){
	switch (np){
		case 1:
			return caseOne;
		case 2:
			return caseTwo;
		case 3:
			return caseThree;
		case 4:
			return caseFour;
		default:
			return caseDefault;
	}
}

float toPercent(int var){
	if (!var){
		return 1;
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
		return 1;
	}
	return var;
}

int ifNotZero(float var){
	if (!var){
		return 1;
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

	int ATTACK_STAT = 0;

	int AOE = 0;
	int ST = 0;

	int np;

	int ARTS = 0;
	int BUSTER = 0;
	int QUICK = 0;

	int au = 0;
	int ad = 0;

	int am = 0;
	int bm = 0;
	int qm = 0;

	float se = 1;
	float sr = 0;

	int pm = 0;
	int nm = 0;
	int cd = 0;

	for (int currArgv=1; currArgv<argc; ++currArgv){

		int argvLen = strlen(argv[currArgv]);

			if (strInStr(2, "au", argv, currArgv)){
				au = au + getBuff(argv, currArgv, argvLen);

			} else if (strInStr(2, "ad", argv, currArgv)){
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

				/* attack stat */
			} else if (strInStr(2, "sa", argv, currArgv)){
				ATTACK_STAT = getBuff(argv, currArgv, argvLen);

				/* st or aeo */
			} else if (strInStr(2, "st", argv, currArgv)){
				ST = 1;

			} else if (strInStr(2, "ao", argv, currArgv)){
				AOE = 1;

				/* strengthening */
			} else if (strInStr(2, "sr", argv, currArgv)){
				/* sr = 1.33333333333; */
				sr = 1.2;

				/* card type */
			} else if (strInStr(2, "aa", argv, currArgv)){
				ARTS = 1;

			} else if (strInStr(2, "bb", argv, currArgv)){
				BUSTER = 1;

			} else if (strInStr(2, "qq", argv, currArgv)){
				QUICK = 1;

				/* aliases */
			} else if (strInStr(2, "vi", argv, currArgv)){
				bm = bm + 100;
				if (BUSTER){
					cd = cd + 100;
				}

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
				if (QUICK){
					cd = cd + cd + 200;
				}

			} else if (strInStr(2, "ca", argv, currArgv)){
				am = am + 100;
				au = au + 40;
		}
	}

	float total = 1;

	float totalNp = 1;
	float totalCard = 1;

	float npMod = 1;
	float cardMod = 1;

	if (ARTS){
		total = toPercent(am);

		if (AOE){
			if (sr){
				npMod = whichNpMod(np, 5, 7.5, 8.25, 8.625, 9);

			} else {
				npMod = whichNpMod(np, 4.5, 6, 6.75, 7.125, 7.5);

			}
		} else if (ST){

			if (sr){
				npMod = whichNpMod(np, 12, 15, 16.5, 17.25, 18);

			} else {
				npMod = whichNpMod(np, 9, 12, 13.5, 14.25, 15);

			}
		}

	} else if (BUSTER){
		total = toPercent(bm);
		cardMod = 1.5;

		if (AOE){
			if (sr){
				npMod = whichNpMod(np, 4, 5, 5.5, 5.75, 6);

			} else {
				npMod = whichNpMod(np, 3, 4, 4.5, 4.75, 5);

			}

		} else if (ST){
			if (sr){
				npMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				npMod = whichNpMod(np, 6, 8, 9, 9.5, 10);

			}
		}
	} else if (QUICK){
		total = toPercent(qm);
		cardMod = 0.8;

		if (AOE){
			if (sr){
				npMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				npMod = whichNpMod(np, 6, 8, 9, 9.5, 10);

			}

		} else if (ST){
			if (sr){
				npMod = whichNpMod(np, 16, 20, 22, 23, 24);

			} else {
				npMod = whichNpMod(np, 12, 16, 18, 19, 20);

			}
		}
	} else{
		printf("%s\n", "Card type not specified!");
	}

	if (!AOE && !ST){
		printf("%s\n", "NP type not specified!");
	}

	if (ATTACK_STAT){
		total = total * ATTACK_STAT;

	} else{
		printf("%s\n", "Attack stat not specified!");
	}

	const float CONST_MULT= 0.23;

	total = total * toPercent((au-ad)) * CONST_MULT;

	totalCard = totalCard * total * toPercent((cd + pm)) * cardMod;

	totalNp = totalNp * total * toPercent((nm + pm)) * se * npMod * cardMod;

	/* thousand separator */

	setlocale(LC_NUMERIC, "");

	printf("%'g\n", totalCard);
	printf("%'g\n", totalNp);

	/* printf("%f\n", totalCard); */
	/* printf("%f\n", totalNp); */
	return 0;
}
