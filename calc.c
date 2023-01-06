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

int inStr(int substrLen, char substr[], char *argv[], int currArgv, int argvLen){
	if (argv[currArgv][0] != substr[0]){
		return 0;
	}

	int substrEnd = substrLen - 1;

	for (int i=0; i<argvLen ; ++i){
		if (argv[currArgv][i] == substr[i]){
			if (i == substrEnd){
				return 1;
			}
		}
	}
	return 0;
}

/* int inLastOfStr(int substrLen, char substr[], char *argv[], int currArgv, int argvLen){ */
/* 	if (argv[currArgv][0] != substr[0]){ */
/* 		return 0; */
/* 	} */

/* 	int substrEnd = substrLen + 2 - 1; */

/* 	for (int i=2; i<argvLen ; ++i){ */
/* 		if (argv[currArgv][i] == substr[i]){ */
/* 			if (i == substrEnd){ */
/* 				return 1; */
/* 			} */
/* 		} */
/* 	} */
/* 	return 0; */
/* } */

int main(int argc, char *argv[]){
	if (!argv[1]){
		printf("%s\n\n", "Usage: calc arguments");
		printf("%s\n", "arguments:");
		printf("%s\n", "bb = buster servant");
		printf("%s\n", "aa = arts servant");
		printf("%s\n\n", "qq = quick servant");
		printf("%s\n", "st = single target np");
		printf("%s\n\n", "aoe = aoe np");
		printf("%s\n", "sa = attack stat");
		printf("%s\n", "au = attack up");
		printf("%s\n\n", "ad = attack down");
		printf("%s\n", "du = defense up");
		printf("%s\n", "dd = defense down");
		printf("%s\n\n", "di = defense ignore");
		printf("%s\n", "am = arts up");
		printf("%s\n", "bm = buster up");
		printf("%s\n\n", "qm = quick up");
		printf("%s\n", "se = special attack; e.g., gilgamesh, se150");
		printf("%s\n", "sr = np strengthening");
		printf("%s\n", "pm = powermod; e.g., arjuna alter, pm50");
		printf("%s\n", "cd = crit up");
		exit(0);
	}

	int attackStat = 0;

	/* knight, cavalry, extra */
	/* 1, 2, 3 */
	int classTypeEnemy = 0;

	int saber = 0;
	int archer = 0;
	int lancer = 0;
	
	int rider = 0;
	int caster = 0;
	int assassin = 0;
	int berserker = 0;
	
	int avenger = 0;
	int ruler = 0;
	int alterEgo = 0;
	int moonCancer = 0;
	int pretender = 0;
	int foreigner = 0;

	int saberEnemy = 0;
	int archerEnemy = 0;
	int lancerEnemy = 0;
	
	int riderEnemy = 0;
	int casterEnemy = 0;
	int assassinEnemy = 0;
	int berserkerEnemy = 0;
	
	int avengerEnemy = 0;
	int rulerEnemy = 0;
	int alterEgoEnemy = 0;
	int moonCancerEnemy = 0;
	int pretenderEnemy = 0;
	int foreignerEnemy = 0;

	float classMod = 1;
	float classAdv = 1;

	int aoe = 0;
	int st = 0;

	int np = 5;

	int arts = 0;
	int buster = 0;
	int quick = 0;

	int au = 0;
	int ad = 0;

	int du = 0;
	int dd = 0;
	int defenseIgnore = 0;

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
			defenseIgnore = 1;

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
		} else if (inStr(2, "at", argv, currArgv, argvLen)){
			attackStat = getBuff(argv, currArgv, argvLen) + 1000;

		} else if (inStr(2, "np", argv, currArgv, argvLen)){
			np = getBuff(argv, currArgv, argvLen);

			/* st or aeo */
		} else if (inStr(2, "st", argv, currArgv, argvLen)){
			st = 1;

		} else if (inStr(2, "ao", argv, currArgv, argvLen)){
			aoe = 1;

			/* strengthening */
		} else if (inStr(2, "sr", argv, currArgv, argvLen)){
			sr = 1;


			/* card type */
		} else if (inStr(2, "aa", argv, currArgv, argvLen)){
			arts = 1;

		} else if (inStr(2, "bb", argv, currArgv, argvLen)){
			buster = 1;

		} else if (inStr(2, "qq", argv, currArgv, argvLen)){
			quick = 1;


			/* class */
		/* } else if (inStr(2, "cl", argv, currArgv, argvLen)){ */

		} else if (inStr(3, "sab", argv, currArgv, argvLen)){
			saber = 1;
			/* classType = 1; */

		} else if (inStr(3, "arc", argv, currArgv, argvLen)){
			archer = 1;
			/* classType = 1; */

		} else if (inStr(3, "lan", argv, currArgv, argvLen)){
			lancer = 1;
			/* classType = 1; */

		} else if (inStr(3, "rid", argv, currArgv, argvLen)){
			rider = 1;
			/* classType = 3; */

		} else if (inStr(3, "ass", argv, currArgv, argvLen)){
			assassin = 1;
			/* classType = 3; */

		} else if (inStr(3, "cas", argv, currArgv, argvLen)){
			caster = 1;
			/* classType = 3; */

		} else if (inStr(3, "zer", argv, currArgv, argvLen)){
			berserker = 1;

		} else if (inStr(3, "rul", argv, currArgv, argvLen)){
			ruler = 1;

		} else if (inStr(3, "ave", argv, currArgv, argvLen)){
			avenger = 1;

		} else if (inStr(3, "alt", argv, currArgv, argvLen)){
			alterEgo = 1;

		} else if (inStr(3, "moo", argv, currArgv, argvLen)){
			moonCancer = 1;

		} else if (inStr(3, "for", argv, currArgv, argvLen)){
			foreigner = 1;

		} else if (inStr(3, "pre", argv, currArgv, argvLen)){
			pretender = 1;

		/* } else if (inStr(2, "en", argv, currArgv, argvLen)){ */

		} else if (inStr(3, "sab", argv, currArgv, argvLen)){
			saberEnemy = 1;
			classTypeEnemy = 1;

		} else if (inStr(3, "arc", argv, currArgv, argvLen)){
			archerEnemy = 1;
			classTypeEnemy = 1;

		} else if (inStr(3, "lan", argv, currArgv, argvLen)){
			lancerEnemy = 1;
			classTypeEnemy = 1;

		} else if (inStr(3, "rid", argv, currArgv, argvLen)){
			riderEnemy = 1;
			classTypeEnemy = 3;

		} else if (inStr(3, "ass", argv, currArgv, argvLen)){
			assassinEnemy = 1;
			classTypeEnemy = 3;

		} else if (inStr(3, "cas", argv, currArgv, argvLen)){
			casterEnemy = 1;
			classTypeEnemy = 3;

		} else if (inStr(3, "zer", argv, currArgv, argvLen)){
			berserkerEnemy = 1;

		} else if (inStr(3, "rul", argv, currArgv, argvLen)){
			rulerEnemy = 1;

		} else if (inStr(3, "ave", argv, currArgv, argvLen)){
			avengerEnemy = 1;

		} else if (inStr(3, "alt", argv, currArgv, argvLen)){
			alterEgoEnemy = 1;

		} else if (inStr(3, "moo", argv, currArgv, argvLen)){
			moonCancerEnemy = 1;

		} else if (inStr(3, "for", argv, currArgv, argvLen)){
			foreignerEnemy = 1;

		} else if (inStr(3, "pre", argv, currArgv, argvLen)){
			pretenderEnemy = 1;

			/* aliases */
		} else if (inStr(2, "vi", argv, currArgv, argvLen)){
			bm = bm + 100;
			if (buster){
				cd = cd + 100;
			}

		} else if (inStr(2, "ss", argv, currArgv, argvLen)){
			au = au + 40;
			bm = bm + 30;
			qm = qm + 130;
			if (buster){
				cd = cd + 200;
			}

		} else if (inStr(2, "sk", argv, currArgv, argvLen)){
			au = au + 60;
			qm = qm + 100;
			if (quick){
				cd = cd + cd + 200;
			}

		} else if (inStr(2, "ca", argv, currArgv, argvLen)){
			am = am + 100;
			au = au + 40;
		}
	}

	if (saber){
		if (lancerEnemy){
			classAdv = 2;

		} else if (archerEnemy){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else if (archer){
		classMod = 0.95;

		if (saberEnemy){
			classAdv = 2;

		} else if (lancerEnemy){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else if (lancer){
		classMod = 1.05;

		if (archerEnemy){
			classAdv = 2;

		} else if (saberEnemy){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else if (assassin){
		classMod = 0.9;

		if (riderEnemy){
			classAdv = 2;

		} else if (casterEnemy){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else if (caster){
		classMod = 0.9;

		if (assassinEnemy){
			classAdv = 2;

		} else if (riderEnemy){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else if (rider){

		if (casterEnemy){
			classAdv = 2;

		} else if (assassinEnemy){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;

		}

	} else if (berserker){
		classMod = 1.1; 

		if (foreignerEnemy){
			classAdv= 0.5;

		} else{
			classAdv = 1.5;
		}

	} else if (ruler){
		classMod = 1.1;

		if (moonCancerEnemy){
			classAdv = 2;

		} else if (avengerEnemy){
			classAdv= 0.5;
		}

	} else if (alterEgo){

		switch (classTypeEnemy){
			case 1:
				classAdv = 0.5;
				break;
			case 2:
				classAdv = 1.5;
				break;
			default:
				if (foreignerEnemy){
					classAdv = 2;
				} else if (pretenderEnemy){
					classAdv = 0.5;
				}
		}

	} else if (avenger){
		classMod = 1.1;

		if (rulerEnemy){
			classAdv = 2;

		} else if (moonCancerEnemy){
			classAdv= 0.5;

	} else if (moonCancer){

		if (avengerEnemy){
			classAdv = 2;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else if (foreigner){

		if (foreignerEnemy){
			classAdv = 2;

		} else if (alterEgoEnemy){
			classAdv= 0.5;
		}

	} else if (pretender){
		classMod = 0.9;

		switch (classTypeEnemy){
			case 1:
				classAdv = 1.5;
				break;
			case 2:
				classAdv = 0.5;
				break;
			default:
				if (alterEgoEnemy){
					classAdv = 2;

				} else if (pretenderEnemy){
					classAdv = 0.5;

				}
		}

		} else if (caster){
			classAdv= 0.5;

		} else if (rulerEnemy){
			classAdv= 0.5;
		}

	} else{
		printf("%s\n","class not specified, defaults to no class advantage!");
	}

	if (berserkerEnemy){
		classAdv = 2;
	}

	float total = 1;

	float totalNp = 1;
	float totalCard = 1;

	float NPMod = 1;
	float cardMod = 1;

	if (attackStat){
		total = total * attackStat;

	} else{
		printf("%s\n", "attack stat not specified!");
	}

	if (arts){
		total = total * toPercent(am);

		if (aoe){
			if (sr){
				NPMod = whichNpMod(np, 5, 7.5, 8.25, 8.625, 9);

			} else {
				NPMod = whichNpMod(np, 4.5, 6, 6.75, 7.125, 7.5);

			}
		} else if (st){

			if (sr){
				NPMod = whichNpMod(np, 12, 15, 16.5, 17.25, 18);

			} else {
				NPMod = whichNpMod(np, 9, 12, 13.5, 14.25, 15);

			}
		}

	} else if (buster){
		total = total * toPercent(bm);
		cardMod = 1.5;

		if (aoe){
			if (sr){
				NPMod = whichNpMod(np, 4, 5, 5.5, 5.75, 6);

			} else {
				NPMod = whichNpMod(np, 3, 4, 4.5, 4.75, 5);

			}

		} else if (st){
			if (sr){
				NPMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				NPMod = whichNpMod(np, 6, 8, 9, 9.5, 10);

			}
		}
	} else if (quick){
		total = total * toPercent(qm);
		cardMod = 0.8;

		if (aoe){
			if (sr){
				NPMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				NPMod = whichNpMod(np, 6, 8, 9, 9.5, 10);

			}

		} else if (st){
			if (sr){
				NPMod = whichNpMod(np, 16, 20, 22, 23, 24);

			} else {
				NPMod = whichNpMod(np, 12, 16, 18, 19, 20);

			}
		}

	} else{
		printf("%s\n", "card type not specified!");
	}

	if (!aoe && !st){
		printf("%s\n", "np type not specified!");
	}

	if (dd > 100){
		dd = 100;
		printf("%s\n", "def down exceeds 100, defaults to 100!");
	}

	if (defenseIgnore){
		du = du - 100;
	}

	const float CONST_MULT= 0.23;

	total = total * toPercent((au + dd - ad - du)) * CONST_MULT * classAdv * classMod;

	totalCard = totalCard * total * toPercent((cd + pm)) * cardMod;

	totalNp = totalNp * total * toPercent((nm + pm)) * se * NPMod * cardMod;

	/* thousand separator */

	setlocale(LC_NUMERIC, "");

	printf("%'g\n", totalCard);
	printf("%'g\n", totalNp);

	printf("%d\n", saber);

	/* printf("%f\n", totalCard); */
	/* printf("%f\n", totalNp); */
	return 0;
}
