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

int inStr(const char substr[], char *argv[], int currArgv){
	if (argv[currArgv][0] != substr[0]){
		return 0;
	}
	int substrLen = strlen(substr);
	int substrEnd = substrLen - 1;
	for (int i=0; i<substrLen; ++i){
		if (argv[currArgv][i] == substr[i]){
			if (i == (substrEnd)){
				return 1;
			}
		}
	}
	return 0;
}

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

	/* enemy */
	const char *class;
	const char *classEnemy;

	/* knight, cavalry, extra, berserker */
	/* 1, 2, 3, 9 */
	int classType = 0;
	int classTypeEnemy = 0;

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

		if (inStr("au", argv, currArgv)){
			au = au + getBuff(argv, currArgv, argvLen);

		} else if (inStr("ad", argv, currArgv)){
			ad = ad - getBuff(argv, currArgv, argvLen);

		} else if (inStr("dd", argv, currArgv)){
			dd = dd + getBuff(argv, currArgv, argvLen);

		} else if (inStr("du", argv, currArgv)){
			du = du + getBuff(argv, currArgv, argvLen);


		} else if (inStr("di", argv, currArgv)){
			defenseIgnore = 1;

		} else if (inStr("bm", argv, currArgv)){
			bm = bm + getBuff(argv, currArgv, argvLen);

		} else if (inStr("qm", argv, currArgv)){
			qm = qm + getBuff(argv, currArgv, argvLen);

		} else if (inStr("am", argv, currArgv)){
			am = am + getBuff(argv, currArgv, argvLen);

		} else if (inStr("pm", argv, currArgv)){
			pm = pm + getBuff(argv, currArgv, argvLen);

		} else if (inStr("nm", argv, currArgv)){
			nm = nm + getBuff(argv, currArgv, argvLen);

		} else if (inStr("cd", argv, currArgv)){
			cd = cd + getBuff(argv, currArgv, argvLen);

		} else if (inStr("se", argv, currArgv)){
			se = getBuff(argv, currArgv, argvLen) / 100.0;


			/* attack stat */
		} else if (inStr("at", argv, currArgv)){
			attackStat = getBuff(argv, currArgv, argvLen);

		} else if (inStr("np", argv, currArgv)){
			np = getBuff(argv, currArgv, argvLen);

			/* st or aeo */
		} else if (inStr("st", argv, currArgv)){
			st = 1;

		} else if (inStr("ao", argv, currArgv)){
			aoe = 1;

			/* strengthening */
		} else if (inStr("sr", argv, currArgv)){
			sr = 1;


			/* card type */
		} else if (inStr("aa", argv, currArgv)){
			arts = 1;

		} else if (inStr("bb", argv, currArgv)){
			buster = 1;

		} else if (inStr("qq", argv, currArgv)){
			quick = 1;


			/* class */
		} else if (inStr("cl", argv, currArgv)){
			++currArgv;

			if (inStr("saber", argv, currArgv)){
				class = "saber";
				classType = 1;

			} else if (inStr("archer", argv, currArgv)){
				class = "archer";
				classType = 1;

			} else if (inStr("lancer", argv, currArgv)){
				class = "lancer";
				classType = 1;

			} else if (inStr("rider", argv, currArgv)){
				class = "rider";
				classType = 2;

			} else if (inStr("assassin", argv, currArgv)){
				class = "assassin";
				classType = 2;

			} else if (inStr("caster", argv, currArgv)){
				class = "caster";
				classType = 2;

			} else if (inStr("berserker", argv, currArgv)){
				class = "berserker";

			} else if (inStr("ruler", argv, currArgv)){
				class = "ruler";

			} else if (inStr("avenger", argv, currArgv)){
				class = "avenger";

			} else if (inStr("alterego", argv, currArgv)){
				class = "alterEgo";

			} else if (inStr("mooncancer", argv, currArgv)){
				class = "moonCancer";

			} else if (inStr("foreigner", argv, currArgv)){
				class = "foreigner";


			} else if (inStr("pretender", argv, currArgv)){
				class = "pretender";

			}

		} else if (inStr("en", argv, currArgv)){

			if (inStr("saber", argv, currArgv)){
				classEnemy = "saber";
				classTypeEnemy = 1;

			} else if (inStr("archer", argv, currArgv)){
				classEnemy = "archer";
				classTypeEnemy = 1;

			} else if (inStr("lancer", argv, currArgv)){
				classEnemy = "lancer";
				classTypeEnemy = 1;

			} else if (inStr("rider", argv, currArgv)){
				classEnemy = "rider";
				classTypeEnemy = 2;

			} else if (inStr("assassin", argv, currArgv)){
				classEnemy = "assassin";
				classTypeEnemy = 2;

			} else if (inStr("caster", argv, currArgv)){
				classEnemy = "caster";
				classTypeEnemy = 2;

			} else if (inStr("berserker", argv, currArgv)){
				classEnemy = "berserker";

			} else if (inStr("ruler", argv, currArgv)){
				classEnemy = "ruler";

			} else if (inStr("avenger", argv, currArgv)){
				classEnemy = "avenger";

			} else if (inStr("alterego", argv, currArgv)){
				classEnemy = "alterEgo";

			} else if (inStr("mooncancer", argv, currArgv)){
				classEnemy = "moonCancer";

			} else if (inStr("foreigner", argv, currArgv)){
				classEnemy = "foreigner";


			} else if (inStr("pretender", argv, currArgv)){
				classEnemy = "pretender";

			}
			/* aliases */
		} else if (inStr("vi", argv, currArgv)){
			bm = bm + 100;
			if (buster){
				cd = cd + 100;
			}

		} else if (inStr("ss", argv, currArgv)){
			au = au + 40;
			bm = bm + 30;
			qm = qm + 130;
			if (buster){
				cd = cd + 200;
			}

		} else if (inStr("sk", argv, currArgv)){
			au = au + 60;
			qm = qm + 100;
			if (quick){
				cd = cd + cd + 200;
			}

		} else if (inStr("ca", argv, currArgv)){
			am = am + 100;
			au = au + 40;
		}
	}

	
	if (!strcmp(class, "saber")){
		if (!strcmp(classEnemy, "lancer")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "archer")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "archer")){
		classMod = 0.95;

		if (!strcmp(classEnemy, "saber")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "lancer")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "lancer")){
		classMod = 1.05;

		if (!strcmp(classEnemy, "archer")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "saber")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "assassin")){
		classMod = 0.9;

		if (!strcmp(classEnemy, "rider")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "caster")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "caster")){
		classMod = 0.9;

		if (!strcmp(classEnemy, "assassin")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "rider")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "rider")){

		if (!strcmp(classEnemy, "caster")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "assassin")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "berserker")){
		classMod = 1.1; 

		if (!strcmp(classEnemy, "foreigner")){
			classAdv= 0.5;

		} else{
			classAdv = 1.5;
		}

	} else if (!strcmp(class, "ruler")){
		classMod = 1.1;

		if (!strcmp(classEnemy, "moonCancer")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "avenger")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "alterEgo")){

		switch (classTypeEnemy){
			case 1:
				classAdv = 0.5;
				break;
			case 2:
				classAdv = 1.5;
				break;
			default:
				if (!strcmp(class, "foreigner")){
					classAdv = 2;
				}
		}

	} else if (!strcmp(class, "avenger")){
		classMod = 1.1;

		if (!strcmp(classEnemy, "ruler")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "moonCancer")){
			classAdv= 0.5;

	} else if (!strcmp(class, "moonCancer")){

		if (!strcmp(classEnemy, "avenger")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "foreigner")){

		if (!strcmp(classEnemy, "foreigner")){
			classAdv = 2;

		} else if (!strcmp(classEnemy, "alterEgo")){
			classAdv= 0.5;
		}

	} else if (!strcmp(class, "pretender")){
		classMod = 0.9;

		switch (classTypeEnemy){
			case 1:
				classAdv = 1.5;
				break;
			case 2:
				classAdv = 0.5;
				break;
			default:
				if (!strcmp(class, "alterEgo")){
					classAdv = 2;
				}
		}

		} else if (!strcmp(classEnemy, "caster")){
			classAdv= 0.5;

		} else if (!strcmp(classEnemy, "ruler")){
			classAdv= 0.5;
		}

	} else if (strcmp(classEnemy, "berserker")){
		printf("%s\n","Class not specified, defaults to no class advantage!");
	}

	if (strcmp(classEnemy, "berserker") && strcmp(class, "berserker")){
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

	/* printf("%f\n", totalCard); */
	/* printf("%f\n", totalNp); */
	return 0;
}
