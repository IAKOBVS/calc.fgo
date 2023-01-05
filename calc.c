#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> /* thousand separator */

float whichNpMod(int NP, float caseOne, float caseTwo, float caseThree, float caseFour, float caseDefault){
	switch (NP){
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

int inStr(int substrLen, const char substr[], char *argv[], int currArgv, int argvLen){
	if (argv[currArgv][0] != substr[0]){
		return 0;
	}
	for (int i=0; i<argvLen; ++i){
		if (argv[currArgv][i] == substr[i]){
			if (i == 1){
				return 1;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[]){

	int ATTACK_STAT = 0;

	int AOE = 0;
	int ST = 0;

	int NP = 5;

	int ARTS = 0;
	int BUSTER = 0;
	int QUICK = 0;

	int au = 0;
	int ad = 0;

	int du = 0;
	int dd = 0;
	int DEFENSE_IGNORE = 0;

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

			if (inStr(2, "au", argv, currArgv, argvLen)){
				au = au + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "ad", argv, currArgv, argvLen)){
				ad = ad - getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "dd", argv, currArgv, argvLen)){
				dd = dd + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "du", argv, currArgv, argvLen)){
				du = du + getBuff(argv, currArgv, argvLen);


			} else if (inStr(2, "di", argv, currArgv, argvLen)){
				DEFENSE_IGNORE = 1;

			} else if (inStr(2, "bm", argv, currArgv, argvLen)){
				bm = bm + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "qm", argv, currArgv, argvLen)){
				qm = qm + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "am", argv, currArgv, argvLen)){
				am = am + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "pm", argv, currArgv, argvLen)){
				pm = pm + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "nm", argv, currArgv, argvLen)){
				nm = nm + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "cd", argv, currArgv, argvLen)){
				cd = cd + getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "se", argv, currArgv, argvLen)){
				se = getBuff(argv, currArgv, argvLen) / 100.0;


				/* attack stat */
			} else if (inStr(2, "sa", argv, currArgv, argvLen)){
				ATTACK_STAT = getBuff(argv, currArgv, argvLen);

			} else if (inStr(2, "np", argv, currArgv, argvLen)){
				NP = getBuff(argv, currArgv, argvLen);

				/* st or aeo */
			} else if (inStr(2, "st", argv, currArgv, argvLen)){
				ST = 1;

			} else if (inStr(2, "ao", argv, currArgv, argvLen)){
				AOE = 1;


				/* strengthening */
			} else if (inStr(2, "sr", argv, currArgv, argvLen)){
				/* sr = 1.33333333333; */
				sr = 1.2;


				/* card type */
			} else if (inStr(2, "aa", argv, currArgv, argvLen)){
				ARTS = 1;

			} else if (inStr(2, "bb", argv, currArgv, argvLen)){
				BUSTER = 1;

			} else if (inStr(2, "qq", argv, currArgv, argvLen)){
				QUICK = 1;


				/* aliases */
			} else if (inStr(2, "vi", argv, currArgv, argvLen)){
				bm = bm + 100;
				if (BUSTER){
					cd = cd + 100;
				}

			} else if (inStr(2, "ss", argv, currArgv, argvLen)){
				au = au + 40;
				bm = bm + 30;
				qm = qm + 130;
				if (BUSTER){
					cd = cd + 200;
				}

			} else if (inStr(2, "sk", argv, currArgv, argvLen)){
				au = au + 60;
				qm = qm + 100;
				if (QUICK){
					cd = cd + cd + 200;
				}

			} else if (inStr(2, "ca", argv, currArgv, argvLen)){
				am = am + 100;
				au = au + 40;
		}
	}

	float total = 1;

	float totalNp = 1;
	float totalCard = 1;

	float NPMod = 1;
	float cardMod = 1;

	if (ARTS){
		total = total * toPercent(am);

		if (AOE){
			if (sr){
				NPMod = whichNpMod(NP, 5, 7.5, 8.25, 8.625, 9);

			} else {
				NPMod = whichNpMod(NP, 4.5, 6, 6.75, 7.125, 7.5);

			}
		} else if (ST){

			if (sr){
				NPMod = whichNpMod(NP, 12, 15, 16.5, 17.25, 18);

			} else {
				NPMod = whichNpMod(NP, 9, 12, 13.5, 14.25, 15);

			}
		}

	} else if (BUSTER){
		total = total * toPercent(bm);
		cardMod = 1.5;

		if (AOE){
			if (sr){
				NPMod = whichNpMod(NP, 4, 5, 5.5, 5.75, 6);

			} else {
				NPMod = whichNpMod(NP, 3, 4, 4.5, 4.75, 5);

			}

		} else if (ST){
			if (sr){
				NPMod = whichNpMod(NP, 8, 10, 11, 11.5, 12);

			} else {
				NPMod = whichNpMod(NP, 6, 8, 9, 9.5, 10);

			}
		}
	} else if (QUICK){
		total = total * toPercent(qm);
		cardMod = 0.8;

		if (AOE){
			if (sr){
				NPMod = whichNpMod(NP, 8, 10, 11, 11.5, 12);

			} else {
				NPMod = whichNpMod(NP, 6, 8, 9, 9.5, 10);

			}

		} else if (ST){
			if (sr){
				NPMod = whichNpMod(NP, 16, 20, 22, 23, 24);

			} else {
				NPMod = whichNpMod(NP, 12, 16, 18, 19, 20);

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

	if (dd < 100){
		dd = 100;
		printf("%s\n", "Def down exceeds 100, defaults to 100!");
	}

	if (DEFENSE_IGNORE){
		du = du - 100;
	}

	total = total * toPercent((au + dd - ad - du)) * CONST_MULT;

	totalCard = totalCard * total * toPercent((cd + pm)) * cardMod;

	totalNp = totalNp * total * toPercent((nm + pm)) * se * NPMod * cardMod;

	/* thousand separator */

	setlocale(LC_NUMERIC, "");

	printf("%'g\n", totalCard);
	printf("%'g\n", totalNp);

	/* printf("%f\n", totalCard); */
	/* printf("%f\n", totalNp); */
	return 0;
}
