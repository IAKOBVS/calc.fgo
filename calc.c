#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define BASE_MULTIPLIER 0.23

#define SABER 1
#define ARCHER 2
#define LANCER 3
#define RIDER 4
#define CASTER 5
#define ASSASSIN 6
#define BERSERKER 7
#define ALTER_EGO 8
#define MOON_CANCER 9
#define RULER 10
#define AVENGER 11
#define FOREIGNER 12
#define PRETENDER 13

#define KNIGHT 1
#define CAVALRY 2
#define EXTRA 3

#define MAN 1
#define EARTH 2
#define SKY 3
#define STAR 4
#define BEAST 5

#define BUSTER 1
#define ARTS 2
#define QUICK 3

#define ST 1
#define AOE 2

/* void printstr(char str[]) */
/* { */
/* 	printf("%s\n", str); */
/* } */

/* void printint(int var) */
/* { */
/* 	printf("%d\n", var); */
/* } */

/* void printfl(float var) */
/* { */
/* 	printf("%f\n", var); */
/* } */

float whichNpMod(int np, float caseOne, float caseTwo, float caseThree, float caseFour, float caseDefault)
{
	switch (np) {
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

/* float toPercent(int var) */
/* { */
/* 	if (!var) { */
/* 		return 1.0; */
/* 	} */
/* 	return 1.0 * (float)var * 0.01; */
/* } */

int getBuff(char *argv[], int currArg, int argvLen)
{
	char numInString[argvLen];
	int j = 0;
	for (int i = 2; i <= argvLen; ++i) {
		numInString[j] = argv[currArg][i];
		j++;
	}
	return (strtol(numInString, NULL, 10));
}

int inStr(int substrLen, char substr[], char *argv[], int currArgv, int argvLen)
{
	if (argv[currArgv][0] != substr[0]) {
		return 0;
	}

	int substrEnd = substrLen - 1;

	for (int i = 0; i <= argvLen; ++i) {
		if (argv[currArgv][i] == substr[i]) {
			if (i == substrEnd) {
				return 1;
			}
		}
	}
	return 0;
}

int countTilNull(char *argv[], int currArgv)
{
	int i = 0;
	while (argv[currArgv][i] != '\0') {
		++i;
	}
	return i;
}

int main(int argc, char *argv[])
{
	if (!argv[1]) {
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
	int noCardType = 1;

	int attackStat = 0;
	int class = 0;
	int classEnemy = 0;

	/* int classType = 0; */
	int classTypeEnemy = 0;

	int cardType = 0;

	int attribute = 0;
	int attributeEnemy = 0;

	int npType = 0;

	int np = 5;

	float superEffective = 1;
	int npStrengthening = 0;

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

	int busterAt = 0;

	int quickFirst = 0;
	int quickSecond = 0;
	int quickThird = 0;

	int npAt = 0;

	for (int currArgv = 1; currArgv < argc; ++currArgv) {

		int argvLen = countTilNull(argv, currArgv);

		if (inStr(2, "au", argv, currArgv, argvLen)) {
			attackUp = attackUp + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "ad", argv, currArgv, argvLen)) {
			attackDown = attackDown - getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "dd", argv, currArgv, argvLen)) {
			defenseDown = defenseDown + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "du", argv, currArgv, argvLen)) {
			defenseUp = defenseUp + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "di", argv, currArgv, argvLen)) {
			defenseIgnore = 1;

		} else if (inStr(2, "bm", argv, currArgv, argvLen)) {
			busterMod = busterMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "qMod", argv, currArgv, argvLen)) {
			quickMod = quickMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "am", argv, currArgv, argvLen)) {
			artsMod = artsMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "pm", argv, currArgv, argvLen)) {
			powerMod = powerMod + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "nu", argv, currArgv, argvLen)) {
			npUp = npUp + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "cd", argv, currArgv, argvLen)) {
			criticalDamage = criticalDamage + getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "se", argv, currArgv, argvLen)) {
			superEffective = getBuff(argv, currArgv, argvLen) / 100.0;

		} else if (inStr(2, "at", argv, currArgv, argvLen)) {
			attackStat = getBuff(argv, currArgv, argvLen) + 1000;

		} else if (inStr(2, "np", argv, currArgv, argvLen)) {
			np = getBuff(argv, currArgv, argvLen);

		} else if (inStr(2, "sr", argv, currArgv, argvLen)) {
			npStrengthening = 1;

		} else if (inStr(2, "vi", argv, currArgv, argvLen)) {
			busterMod = busterMod + 100;
			if (cardType == BUSTER) {
				criticalDamage = criticalDamage + 100;
			}

		} else if (inStr(2, "ss", argv, currArgv, argvLen)) {
			attackUp = attackUp + 40;
			busterMod = busterMod + 30;
			quickMod = quickMod + 130;
			if (cardType == BUSTER) {
				criticalDamage = criticalDamage + 200;
			}

		} else if (inStr(2, "sk", argv, currArgv, argvLen)) {
			attackUp = attackUp + 60;
			quickMod = quickMod + 100;
			if (cardType == QUICK) {
				criticalDamage = criticalDamage + criticalDamage + 200;
			}

		} else if (inStr(2, "ca", argv, currArgv, argvLen)) {
			artsMod = artsMod + 100;
			attackUp = attackUp + 40;

		} else {

			if (!cardType) {
				if (inStr(2, "st", argv, currArgv, argvLen)) {
					cardType = ST;
					continue;

				} else if (inStr(2, "ao", argv, currArgv, argvLen)) {
					cardType = AOE;
					continue;
				}
			}

			if (noCardType) {

				if (inStr(2, "aa", argv, currArgv, argvLen)) {
					cardType = ARTS;
					continue;

				} else if (inStr(2, "bb", argv, currArgv, argvLen)) {
					cardType = BUSTER;
					continue;

				} else if (inStr(2, "qq", argv, currArgv, argvLen)) {
					cardType = QUICK;
					continue;
				}
			}

			if (!class) {

				if (inStr(3, "sab", argv, currArgv, argvLen)) {
					class = SABER;
					/* classType = KNIGHT; */
					continue;

				} else if (inStr(3, "arc", argv, currArgv, argvLen)) {
					class = ARCHER;
					/* classType = KNIGHT; */
					continue;

				} else if (inStr(3, "lan", argv, currArgv, argvLen)) {
					class = LANCER;
					/* classType = KNIGHT; */
					continue;

				} else if (inStr(3, "rid", argv, currArgv, argvLen)) {
					class = RIDER;
					/* classType = CAVALRY; */
					continue;

				} else if (inStr(3, "ass", argv, currArgv, argvLen)) {
					class = ASSASSIN;
					/* classType = CAVALRY; */
					continue;

				} else if (inStr(3, "cas", argv, currArgv, argvLen)) {
					class = CASTER;
					/* classType = CAVALRY; */
					continue;

				} else if (inStr(3, "zer", argv, currArgv, argvLen)) {
					class = BERSERKER;
					continue;

				} else if (inStr(3, "ave", argv, currArgv, argvLen)) {
					class = AVENGER;
					continue;

				} else if (inStr(3, "alt", argv, currArgv, argvLen)) {
					class = ALTER_EGO;
					continue;

				} else if (inStr(3, "moo", argv, currArgv, argvLen)) {
					class = MOON_CANCER;
					continue;

				} else if (inStr(3, "for", argv, currArgv, argvLen)) {
					class = FOREIGNER;
					continue;

				} else if (inStr(3, "pre", argv, currArgv, argvLen)) {
					class = PRETENDER;
					continue;
				}
			}

			if (!classEnemy) {

				if (inStr(4, "esab", argv, currArgv, argvLen)) {
					classEnemy = SABER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (inStr(4, "earc", argv, currArgv, argvLen)) {
					classEnemy = ARCHER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (inStr(4, "elan", argv, currArgv, argvLen)) {
					classEnemy = LANCER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (inStr(4, "erid", argv, currArgv, argvLen)) {
					classEnemy = RIDER;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (inStr(4, "eass", argv, currArgv, argvLen)) {
					classEnemy = ASSASSIN;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (inStr(4, "ecas", argv, currArgv, argvLen)) {
					classEnemy = CASTER;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (inStr(4, "ezer", argv, currArgv, argvLen)) {
					classEnemy = BERSERKER;
					continue;

				} else if (inStr(4, "erul", argv, currArgv, argvLen)) {
					classEnemy = RULER;
					continue;

				} else if (inStr(4, "eave", argv, currArgv, argvLen)) {
					classEnemy = AVENGER;
					continue;

				} else if (inStr(4, "emoo", argv, currArgv, argvLen)) {
					classEnemy = MOON_CANCER;
					continue;

				} else if (inStr(4, "efor", argv, currArgv, argvLen)) {
					classEnemy = FOREIGNER;
					continue;

				} else if (inStr(4, "epre", argv, currArgv, argvLen)) {
					classEnemy = PRETENDER;
					continue;
				}
			}

			if (!attribute) {

				if (inStr(3, "man", argv, currArgv, argvLen)) {
					attribute = MAN;
					continue;

				} else if (inStr(3, "sky", argv, currArgv, argvLen)) {
					attribute = SKY;
					continue;

				} else if (inStr(3, "ear", argv, currArgv, argvLen)) {
					attribute = EARTH;
					continue;

				} else if (inStr(3, "star", argv, currArgv, argvLen)) {
					attribute = STAR;
					continue;

				} else if (inStr(3, "beast", argv, currArgv, argvLen)) {
					attribute = BEAST;
					continue;
				}
			}

			if (!attributeEnemy) {

				if (inStr(4, "eman", argv, currArgv, argvLen)) {
					attributeEnemy = MAN;
					continue;

				} else if (inStr(4, "esky", argv, currArgv, argvLen)) {
					attributeEnemy = SKY;
					continue;

				} else if (inStr(4, "eear", argv, currArgv, argvLen)) {
					attributeEnemy = EARTH;
					continue;

				} else if (inStr(4, "esta", argv, currArgv, argvLen)) {
					attributeEnemy = STAR;
					continue;

				} else if (inStr(4, "ebea", argv, currArgv, argvLen)) {
					attributeEnemy = BEAST;
					continue;
				}
			}

			if (noChain) {

				if (inStr(4, "npbb", argv, currArgv, argvLen)) {

					npAt = 1;

					switch (cardType) {
					case BUSTER:
						busterFirst = 1;
						break;
					case ARTS:
						artsFirst = 1;
						break;
					case QUICK:
						quickFirst = 1;
					}

					busterSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(4, "npaa", argv, currArgv, argvLen)) {

					npAt = 1;

					switch (cardType) {
					case BUSTER:
						busterFirst = 1;
						break;
					case ARTS:
						artsFirst = 1;
						break;
					case QUICK:
						quickFirst = 1;
					}

					artsSecond = 1;
					artsThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(4, "npqq", argv, currArgv, argvLen)) {

					npAt = 1;

					switch (cardType) {
					case BUSTER:
						busterFirst = 1;
						break;
					case ARTS:
						artsFirst = 1;
						break;
					case QUICK:
						quickFirst = 1;
					}

					quickSecond = 1;
					quickThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bbb", argv, currArgv, argvLen)) {

					busterFirst = 1;
					busterSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bba", argv, currArgv, argvLen)) {

					busterFirst = 1;
					busterSecond = 1;
					artsThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bbq", argv, currArgv, argvLen)) {

					busterFirst = 1;
					busterSecond = 1;
					quickThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bab", argv, currArgv, argvLen)) {

					busterFirst = 1;
					artsSecond = 1;
					busterThird = 1;
					noChain = 0;
					continue;

				} else if (inStr(3, "bqb", argv, currArgv, argvLen)) {

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

	/* checkclass */
	switch (class) {
	case SABER:
		switch (classEnemy) {
		case LANCER:
			classAdv = 2;
			break;
		case ARCHER:
			classAdv = 0.5;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case ARCHER:
		classMod = 0.95;

		switch (classEnemy) {
		case SABER:
			classAdv = 2;
			break;
		case LANCER:
			classAdv = 0.5;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case LANCER:
		classMod = 1.05;

		switch (classEnemy) {
		case ARCHER:
			classAdv = 2;
			break;
		case SABER:
			classAdv = 0.5;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case ASSASSIN:
		classMod = 0.9;

		switch (classEnemy) {
		case RIDER:
			classAdv = 2;
			break;
		case CASTER:
			classAdv = 0.5;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case CASTER:
		classMod = 0.9;

		switch (classEnemy) {
		case ASSASSIN:
			classAdv = 2;
			break;
		case RIDER:
			classAdv = 0.5;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case RIDER:
		switch (classEnemy) {
		case CASTER:
			classAdv = 2;
			break;
		case ASSASSIN:
			classAdv = 0.5;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case BERSERKER:
		classMod = 1.1;

		switch (classEnemy) {
		case FOREIGNER:
			classAdv = 2;
			break;
		default:
			classAdv = 1.5;
		}
		break;
	case RULER:
		classMod = 1.1;

		switch (classEnemy) {
		case MOON_CANCER:
			classAdv = 2;
			break;
		case AVENGER:
			classAdv = 0.5;
		}
		break;
	case ALTER_EGO:
		classMod = 1.0;

		switch (classTypeEnemy) {
		case KNIGHT:
			classAdv = 0.5;
			break;
		case CAVALRY:
			classAdv = 2;
			break;
		default:
			switch (classEnemy) {
			case FOREIGNER:
				classAdv = 2;
				break;
			case PRETENDER:
				classAdv = 0.5;
			}
		}
		break;
	case AVENGER:
		classMod = 1.1;

		switch (classTypeEnemy) {
		case RULER:
			classAdv = 2;
			break;
		case MOON_CANCER:
			classAdv = 0.5;
		}
		break;
	case MOON_CANCER:
		switch (classTypeEnemy) {
		case AVENGER:
			classAdv = 2;
			break;
		case RULER:
			classAdv = 0.5;
		}
		break;
	case FOREIGNER:
		switch (classTypeEnemy) {
		case FOREIGNER:
			classAdv = 2;
			break;
		case PRETENDER:
			classAdv = 2;
			break;
		case ALTER_EGO:
			classAdv = 0.5;
		}
		break;
	case PRETENDER:
		switch (classTypeEnemy) {
		case KNIGHT:
			classAdv = 1.5;
			break;
		case CAVALRY:
			classAdv = 0.5;
			break;
		case 0:
			switch (classEnemy) {
			case ALTER_EGO:
				classAdv = 2;
				break;
			case FOREIGNER:
				classAdv = 0.5;
			}
		}
		break;
	default:
		printf("%s\n", "class not specified, defaults to no class advantage!");
	}

	if (classEnemy == BERSERKER) {
		classAdv = 2;
	} else if (classEnemy == ALTER_EGO) {

	}

	float attributeMod = 1;

	/* checkattribute */
	switch (attribute) {
	case MAN:
		switch (attributeEnemy) {
		case SKY:
			attributeMod = 1.1;
			break;
		case EARTH:
			attributeMod = 0.9;
		}
		break;
	case SKY:
		switch (attributeEnemy) {
		case MAN:
			attributeMod = 0.9;
			break;
		case EARTH:
			attributeMod = 1.1;
		}
		break;
	case EARTH:
		switch (attributeEnemy) {
		case MAN:
			attributeMod = 1.1;
			break;
		case SKY:
			attributeMod = 0.9;
		}
		break;
	case STAR:

		if (BEAST) {
			attributeMod = 1.1;
		}
		break;
	case BEAST:

		if (STAR) {
			attributeMod = 1.1;
		}
		break;
	default:
		printf("%s\n", "attribute not specified!");
	}

	float total = 1;

	float npMod = 1;
	float cardMod = 1;

	if (!attackStat) {
		attackStat = 1;
		printf("%s\n", "attack stat not specified!");
	}

	/* checkcardtype */
	switch (cardType) {
	case ARTS:
		if (artsMod) {
			artsMod = 1.0 + (float)artsMod * 0.01;
			total = total * artsMod;
		}

		switch (npType) {
		case AOE:
			if (npStrengthening) {
				npMod = whichNpMod(np, 5, 7.5, 8.25, 8.625, 9);

			} else {
				npMod = whichNpMod(np, 4.5, 6, 6.75, 7.125, 7.5);
			}

			break;
		case ST:
			if (npStrengthening) {
				npMod = whichNpMod(np, 12, 15, 16.5, 17.25, 18);

			} else {
				npMod = whichNpMod(np, 9, 12, 13.5, 14.25, 15);
			}
		}
		break;
	case BUSTER:
		if (busterMod) {
			busterMod = 1.0 + (float)busterMod * 0.01;
			total = total * busterMod;
		}
		cardMod = 1.5;

		switch (npType) {
		case AOE:
			if (npStrengthening) {
				npMod = whichNpMod(np, 4, 5, 5.5, 5.75, 6);

			} else {
				npMod = whichNpMod(np, 3, 4, 4.5, 4.75, 5);
			}
			break;
		case ST:
			if (npStrengthening) {
				npMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				npMod = whichNpMod(np, 6, 8, 9, 9.5, 10);
			}
			break;
		}
		break;

	case QUICK:
		if (quickMod) {
			quickMod = 1.0 * (float)quickMod * 0.01;
			total = total * quickMod;
		}
		cardMod = 0.8;

		switch (npType) {
		case AOE:
			if (npStrengthening) {
				npMod = whichNpMod(np, 8, 10, 11, 11.5, 12);

			} else {
				npMod = whichNpMod(np, 6, 8, 9, 9.5, 10);
			}
			break;
		case ST:
			if (npStrengthening) {
				npMod = whichNpMod(np, 16, 20, 22, 23, 24);

			} else {
				npMod = whichNpMod(np, 12, 16, 18, 19, 20);
			}
		}

	default:
		printf("%s\n", "card type not specified!");
	}

	if (defenseDown > 100) {
		defenseDown = 100;
		printf("%s\n", "def down exceeds 100, defaults to 100!");
	}

	if (defenseIgnore) {
		defenseUp = defenseUp - 100;
	}

	setlocale(LC_NUMERIC, "");

	if ((attackUp + defenseDown - attackDown - defenseUp)) {
		total = total *	(1.0 + ((float)(attackUp + defenseDown - attackDown - defenseUp)) * 0.01);
	}
	total = total * BASE_MULTIPLIER * classAdv * classMod * attributeMod * ((float)attackStat) * cardMod;

	/* total = total * BASE_MULTIPLIER * (1.0 + ((float)(attackUp + defenseDown
	 * - attackDown - defenseUp)) * 0.01) * classAdv * classMod * attributeMod *
	 * ((float)attackStat) * cardMod; */

	/* float totalCard = total * (1.0 + ((float)(criticalDamage + powerMod)) *
	 * 0.01); */

	float totalCard = 1;
	if ((criticalDamage + powerMod)) {
		totalCard = 1.0 + (float)(criticalDamage + powerMod) * 0.01;
	}
	totalCard = totalCard * total;

	float cardFirst = 1;
	float cardSecond = 1;
	float cardThird = 1;

	/* checkchain */
	if (!noChain) {
		if (npAt != 1) {
			switch (cardType) {
				case BUSTER:
					busterFirst = 1;
					break;
				case QUICK:
					quickFirst = 1;
					break;
				case ARTS:
					artsFirst = 1;
			}
		}
		if (busterFirst) {

			if (npAt != 1) {
				cardFirst = 1.5;
			}

			if (busterSecond) {
				cardSecond = 1.8;
			}

			if (busterThird) {
				cardThird = 2.1;
			}
		} else if (quickFirst) {

			if (npAt != 1) {
				cardFirst = 0.8;
			}
			if (quickSecond) {
				cardSecond = 0.96;
			}
			if (quickThird) {
				cardThird = 1.12;
			}
		} else if (artsFirst) {

			if (npAt != 1) {
				cardFirst = 1;
			}
			if (artsSecond) {
				cardSecond = 1.2;
			}
			if (artsThird) {
				cardThird = 1.12;
			}
		}

		if (npAt != 1) {
			cardFirst = cardFirst * totalCard;
			printf("%f\n", cardFirst);
		}

		if (npAt != 2) {
			cardSecond = cardSecond * totalCard;
			printf("%f\n", cardSecond);
		}

		if (npAt != 3) {
			cardThird = cardThird * totalCard;
			printf("%f\n", cardThird);
		}
	}

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
	if ((npUp + powerMod)) {
		totalNp = 1.0 + (float)(npUp + powerMod) * 0.01;
		/* printf("%s\n","totalNp"); */
		/* printf("%'g\n",totalNp); */
	}
	totalNp = totalNp * superEffective * npMod * total;
	printf("%'g\n", totalNp);

	/* printf("%s\n","totalNp"); */

	/* totalNp = total * (1.0 + ((float)(npUp + powerMod)) * 0.01) *
	 * (float)superEffective * (float)npMod; */
	/* printf("%s\n","totalNp"); */

	/* printf("%'g\n", totalCard); */
	/* printf("%'g\n", totalNp); */

	/* printf("%'f\n", totalCard); */
	/* printf("%'f\n", totalNp); */

	return 0;
}
