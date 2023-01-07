#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
/* thousand separator */

void printstr(char str[]){
	printf("%s\n", str);
}

void printint(int var){
	printf("%d\n", var);
}

void printfl(float var){
	printf("%f\n", var);
}

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
		return 1.0;
	}
	return 1.0 * (float)var * 0.01;
}

int getBuff(char *argv[], int currArg, int argvLen){
	/* setvbuf(stdout, NULL, _IONBF, 0); */ 
	char numInString[argvLen];
	int j=0;
	for (int i=2; i<=argvLen; ++i){
		numInString[j] = argv[currArg][i];
		/* printf("%s\n","numInString"); */
		/* puts(numInString); */
		j++;
	}
	/* printf("%s\n","result"); */
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

	for (int i=0; i<=argvLen; ++i){
		if (argv[currArgv][i] == substr[i]){
			if (i == substrEnd){
				return 1;
			}
		}
	}
	return 0;
}

int countTilNull(char *argv[], int currArgv){
	int i = 0;
	while (argv[currArgv][i] != '\0'){
		++i;
	}
	return i;
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
		printf("%s\n", "at = attack stat");
		printf("%s\n", "au = attack up");
		printf("%s\n\n", "ad = attack down");
		printf("%s\n", "du = defense up");
		printf("%s\n", "dd = defense down");
		printf("%s\n\n", "di = defense ignore");
		printf("%s\n", "artsMod = arts up");
		printf("%s\n", "bm = buster up");
		printf("%s\n\n", "qm = quick up");
		printf("%s\n", "se = super effective; e.g., gilgamesh, se150");
		printf("%s\n", "sr = np strengthening");
		printf("%s\n", "nu = np damage up");
		printf("%s\n", "pm = powermod; e.g., arjuna alter, pm50");
		printf("%s\n", "cd = critical damage");
		exit(0);
	}

	int noClass = 1;
	int noClassEnemy = 1;
	int noAttribute = 1;
	int noAttributeEnemy = 1;
	int noCardType = 1;

	int attackStat = 0;

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

	/* knight = 1 */
	/* cavalry = 2 */	
	int classTypeEnemy = 0;

	int man = 0;
	int sky = 0;
	int earth = 0;
	int star = 0;
	int beast = 0;

	int manEnemy = 0;
	int skyEnemy = 0;
	int earthEnemy = 0;
	int starEnemy = 0;
	int beastEnemy = 0;

	int aoe = 0;
	int st = 0;

	int np = 5;

	float superEffective = 1;
	int npStrengthening = 0;

	int arts = 0;
	int buster = 0;
	int quick = 0;

	int attackUp = 0;
	int attackDown = 0;

	int defenseUp = 0;
	int defenseDown = 0;
	int defenseIgnore = 0;

	int artsMod = 0;
	int busterMod = 0;
	int quickMod = 0;

	int powerMod = 0;
	int npUp = 0;
	int criticalDamage = 0;

	int noChain = 1;

	int artsFirst = 0;
	int artsSecond = 0;
	int artsThird = 0;

	int busterFirst = 0;
	int busterSecond = 0;
	int busterThird = 0;

	int quickFirst = 0;
	int quickSecond = 0;
	int quickThird = 0;

	for (int currArgv=1; currArgv<argc; ++currArgv){

		int argvLen = countTilNull(argv, currArgv);

		if (inStr(2, "au", argv, currArgv, argvLen)){
			attackUp = attackUp + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "ad", argv, currArgv, argvLen)){
			attackDown = attackDown - getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "dd", argv, currArgv, argvLen)){
			defenseDown = defenseDown + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "du", argv, currArgv, argvLen)){
			defenseUp = defenseUp + getBuff(argv, currArgv, argvLen);


		} else if (inStr(2, "di", argv, currArgv, argvLen)){
			defenseIgnore = 1;

		} else if (inStr(2, "bm", argv, currArgv, argvLen)){
			busterMod = busterMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "qMod", argv, currArgv, argvLen)){
			quickMod = quickMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "am", argv, currArgv, argvLen)){
			artsMod = artsMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "pm", argv, currArgv, argvLen)){
			powerMod = powerMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "nu", argv, currArgv, argvLen)){
			npUp = npUp + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "cd", argv, currArgv, argvLen)){
			criticalDamage = criticalDamage + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "se", argv, currArgv, argvLen)){
			superEffective = getBuff(argv, currArgv, argvLen) / 100.0;

			/* attack stat */
		} else if (inStr(2, "at", argv, currArgv, argvLen)){
			attackStat = getBuff(argv, currArgv, argvLen) + 1000;
			/* printf("%d\n", attackStat); */

		} else if (inStr(2, "np", argv, currArgv, argvLen)){
			np = getBuff(argv, currArgv, argvLen);

			/* st or aeo */
		} else if (inStr(2, "st", argv, currArgv, argvLen)){
			st = 1;

		} else if (inStr(2, "ao", argv, currArgv, argvLen)){
			aoe = 1;

			/* strengthening */
		} else if (inStr(2, "sr", argv, currArgv, argvLen)){
			npStrengthening = 1;

			/* aliases */
		} else if (inStr(2, "vi", argv, currArgv, argvLen)){
			busterMod = busterMod + 100;
			if (buster){
				criticalDamage = criticalDamage + 100;
			}

		} else if (inStr(2, "ss", argv, currArgv, argvLen)){
			attackUp = attackUp + 40;
			busterMod = busterMod + 30;
			quickMod = quickMod + 130;
			if (buster){
				criticalDamage = criticalDamage + 200;
			}

		} else if (inStr(2, "sk", argv, currArgv, argvLen)){
			attackUp = attackUp + 60;
			quickMod = quickMod + 100;
			if (quick){
				criticalDamage = criticalDamage + criticalDamage + 200;
			}

		} else if (inStr(2, "ca", argv, currArgv, argvLen)){
			artsMod = artsMod + 100;
			attackUp = attackUp + 40;

		} else{
			if (noCardType){

				if (inStr(2, "aa", argv, currArgv, argvLen)){
					arts = 1;
					noCardType = 0;
					continue;

				} else if (inStr(2, "bb", argv, currArgv, argvLen)){
					buster = 1;
					noCardType = 0;
					continue;

				} else if (inStr(2, "qq", argv, currArgv, argvLen)){
					quick = 1;
					noCardType = 0;
					continue;
				}
			}

			if (noClass){

				if (inStr(3, "sab", argv, currArgv, argvLen)){
					saber = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "arc", argv, currArgv, argvLen)){
					archer = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "lan", argv, currArgv, argvLen)){
					lancer = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "rid", argv, currArgv, argvLen)){
					rider = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "ass", argv, currArgv, argvLen)){
					assassin = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "cas", argv, currArgv, argvLen)){
					caster = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "zer", argv, currArgv, argvLen)){
					berserker = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "rul", argv, currArgv, argvLen)){
					ruler = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "ave", argv, currArgv, argvLen)){
					avenger = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "alt", argv, currArgv, argvLen)){
					alterEgo = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "moo", argv, currArgv, argvLen)){
					moonCancer = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "for", argv, currArgv, argvLen)){
					foreigner = 1;
					noClass = 0;
					continue;

				} else if (inStr(3, "pre", argv, currArgv, argvLen)){
					pretender = 1;
					noClass = 0;
					continue;
				}

			}

			if (noClassEnemy){

				if (inStr(4, "esab", argv, currArgv, argvLen)){
					saberEnemy = 1;
					classTypeEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "earc", argv, currArgv, argvLen)){
					archerEnemy = 1;
					classTypeEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "elan", argv, currArgv, argvLen)){
					lancerEnemy = 1;
					classTypeEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "erid", argv, currArgv, argvLen)){
					riderEnemy = 1;
					classTypeEnemy = 4;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "eass", argv, currArgv, argvLen)){
					assassinEnemy = 1;
					classTypeEnemy = 4;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "ecas", argv, currArgv, argvLen)){
					casterEnemy = 1;
					classTypeEnemy = 4;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "ezer", argv, currArgv, argvLen)){
					berserkerEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "erul", argv, currArgv, argvLen)){
					rulerEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "eave", argv, currArgv, argvLen)){
					avengerEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "ealt", argv, currArgv, argvLen)){
					alterEgoEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "emoo", argv, currArgv, argvLen)){
					moonCancerEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "efor", argv, currArgv, argvLen)){
					foreignerEnemy = 1;
					noClassEnemy = 0;
					continue;

				} else if (inStr(4, "epre", argv, currArgv, argvLen)){
					pretenderEnemy = 1;
					noClassEnemy = 0;
					continue;

				}
			}

			if (noAttribute){

				if (inStr(3, "man", argv, currArgv, argvLen)){
					man = 1;
					noAttribute = 0;
					continue;

				} else if (inStr(3, "sky", argv, currArgv, argvLen)){
					sky = 1;
					noAttribute = 0;
					continue;

				} else if (inStr(3, "ear", argv, currArgv, argvLen)){
					earth = 1;
					noAttribute = 0;
					continue;

				} else if (inStr(3, "star", argv, currArgv, argvLen)){
					star = 1;
					noAttribute = 0;
					continue;

				} else if (inStr(3, "beast", argv, currArgv, argvLen)){
					beast = 1;
					noAttribute = 0;
					continue;

				}
			}

			if (noAttributeEnemy){

				if (inStr(4, "eman", argv, currArgv, argvLen)){
					manEnemy = 1;
					noAttributeEnemy = 0;
					continue;

				} else if (inStr(4, "esky", argv, currArgv, argvLen)){
					skyEnemy = 1;
					noAttributeEnemy = 0;
					continue;

				} else if (inStr(4, "eear", argv, currArgv, argvLen)){
					earthEnemy = 1;
					noAttributeEnemy = 0;
					continue;

				} else if (inStr(4, "esta", argv, currArgv, argvLen)){
					starEnemy = 1;
					noAttributeEnemy = 0;
					continue;

				} else if (inStr(4, "ebea", argv, currArgv, argvLen)){
					beastEnemy = 1;
					noAttributeEnemy = 0;
					continue;
				}
			}
			if (noChain){

				if (inStr(3, "npbb", argv, currArgv, argvLen)){

					if (buster){
						busterFirst = 1;

					} else if (arts){
						artsFirst = 1;

					} else if (quick){
						quickFirst = 1;
					}

					busterSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

					} else if (inStr(3, "npaa", argv, currArgv, argvLen)){

					if (buster){
						busterFirst = 1;

					} else if (arts){
						artsFirst = 1;

					} else if (quick){
						quickFirst = 1;
					}

					artsSecond = 1;
					artsThird = 1;
					noChain = 0;
					continue;

			} else if (inStr(3, "bbb", argv, currArgv, argvLen)){

					busterFirst = 1;
					busterSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bba", argv, currArgv, argvLen)){

					busterFirst = 1;
					busterSecond = 1;
					artsThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bbq", argv, currArgv, argvLen)){

					busterFirst = 1;
					busterSecond = 1;
					quickThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bab", argv, currArgv, argvLen)){

					busterFirst = 1;
					artsSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bqb", argv, currArgv, argvLen)){

					busterFirst = 1;
					quickSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

				}

			}
		}
	}


	float classMod = 1;
	float classAdv = 1;

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

	float attributeMod = 1;

	if (man){
		if (skyEnemy){
			attributeMod = 1.1;

		} else if (earthEnemy){
			attributeMod = 0.9;

		}
	} else if (sky){
		if (manEnemy){
			attributeMod = 0.9;

		} else if (earthEnemy){
			attributeMod = 1.1;

		}
	} else if (earth){
		if (manEnemy){
			attributeMod = 1.1;
		} else if (skyEnemy){
			attributeMod = 0.9;
		}
	} else if (star){
		if (beastEnemy){
			attributeMod = 1.1;
		}
	} else if (beast){
		if (starEnemy){
			attributeMod = 1.1;
		}
	}

	float total = 1;

	float npMod = 1;
	float cardMod = 1;

	if (!attackStat){
		attackStat = 1;
		printf("%s\n", "attack stat not specified!");
	}

	if (arts){
		total = total * toPercent(artsMod);

		if (aoe){
			if (npStrengthening){
				npMod = whichNpMod(np, 5, 7.5, 8.25, 8.625, 9);

			} else {
				npMod = whichNpMod(np, 4.5, 6, 6.75, 7.125, 7.5);

			}
		} else if (st){

			if (npStrengthening){
				npMod = whichNpMod(np, 12, 15, 16.5, 17.25, 18);

			} else {
				npMod = whichNpMod(np, 9, 12, 13.5, 14.25, 15);

			}
		}

	} else if (buster){
		if (busterMod){
			total = 1.0  + (float)busterMod * 0.01;
		}
		/* total = total * toPercent(busterMod); */
		/* printf("%s\n", "busterMod"); */
		/* printf("%f\n", total); */
		cardMod = 1.5;

		if (aoe){
			if (npStrengthening){
				npMod = whichNpMod(np, 4, 5, 5.5, 5.75, 6);

			} else {
				npMod = whichNpMod(np, 3, 4, 4.5, 4.75, 5);
				/* printf("%f\n", npMod); */

			}

		} else if (st){
			if (npStrengthening){
				npMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				npMod = whichNpMod(np, 6, 8, 9, 9.5, 10);

			}
		}
	} else if (quick){
		total = total * toPercent(quickMod);
		cardMod = 0.8;

		if (aoe){
			if (npStrengthening){
				npMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				npMod = whichNpMod(np, 6, 8, 9, 9.5, 10);

			}

		} else if (st){
			if (npStrengthening){
				npMod = whichNpMod(np, 16, 20, 22, 23, 24);

			} else {
				npMod = whichNpMod(np, 12, 16, 18, 19, 20);

			}
		}

	} else{
		printf("%s\n", "card type not specified!");
	}

	if (!aoe && !st){
		printf("%s\n", "np type not specified!");
	}

	if (defenseDown > 100){
		defenseDown = 100;
		printf("%s\n", "def down exceeds 100, defaults to 100!");
	}

	if (defenseIgnore){
		defenseUp = defenseUp - 100;
	}

	setlocale(LC_NUMERIC, "");

	const float BASE_MULTIPLIER = 0.23;

	if ((attackUp + defenseDown - attackDown - defenseUp)){
		total = total * (1.0 + ((float)(attackUp + defenseDown - attackDown - defenseUp)) * 0.01);
	}
	total = total * BASE_MULTIPLIER * classAdv * classMod * attributeMod * ((float)attackStat) * cardMod;

	/* total = total * BASE_MULTIPLIER * (1.0 + ((float)(attackUp + defenseDown - attackDown - defenseUp)) * 0.01) * classAdv * classMod * attributeMod * ((float)attackStat) * cardMod; */

	/* float totalCard = total * (1.0 + ((float)(criticalDamage + powerMod)) * 0.01); */

	/* printf("%s\n", "attackStat"); */
	/* printf("%d\n", attackStat); */
	/* printf("%s\n", "busterMod"); */
	/* printf("%d\n", busterMod); */
	/* printf("%s\n", "powerMod"); */
	/* printf("%d\n", powerMod); */
	/* printf("%s\n", "npUp"); */
	/* printf("%d\n", npUp); */
	/* printstr("npMod"); */
	/* printf("%f\n",npMod); */
	/* printstr("classAdv"); */
	/* printf("%f\n",attributeMod); */
	/* printstr("atrributeMod"); */
	/* printf("%f\n",classAdv); */
	/* printstr("classMod"); */
	/* printf("%f\n",classMod); */
	/* printstr("npMod"); */
	/* printf("%f\n",npMod); */
	/* printstr("total"); */
	/* printf("%f\n",total); */

	float totalNp = 1;
	if ((npUp + powerMod)){
		totalNp = 1.0 + (float)(npUp + powerMod) * 0.01;
		/* printf("%s\n","totalNp"); */
		/* printf("%'g\n",totalNp); */
	}
	totalNp = totalNp * superEffective * npMod * total;
	printf("%'g\n",totalNp);
	/* printf("%s\n","totalNp"); */

	/* totalNp = total * (1.0 + ((float)(npUp + powerMod)) * 0.01) * (float)superEffective * (float)npMod; */
	/* printf("%s\n","totalNp"); */


	/* printf("%'g\n", totalCard); */
	/* printf("%'g\n", totalNp); */

	/* printf("%'f\n", totalCard); */
	/* printf("%'f\n", totalNp); */
	return 0;
}
