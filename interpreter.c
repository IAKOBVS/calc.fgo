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

#define BUSTER_CHAIN_MOD 0.2

inline void printdbl(double var)
{
	printf("%f\n", var);
}

inline void printint(int var)
{
	printf("%d\n", var);
}

inline void printfl(float var)
{
	printf("%f\n", var);
}

void verbose(){

}

inline int intToFloat(float var)
{
	if (!var)
		return 1;
	else
		return var;
}

int countTilNull(char *argv[], int currArgv)
{
	int i = 0;
	while (argv[currArgv][i] != '\0') ++i;

	return i;
}

int startsWith(int substrLen, char substr[], char *argv[], int currArgv, int argvLen)
{
	if (argv[currArgv][0] != substr[0])
		return 0;

	int substrEnd = substrLen - 1;

	for (int i = 0; i<argvLen; ++i)
		if (argv[currArgv][i] == substr[i])
			if (i == substrEnd)
				return 1;

	return 0;
}

int getBuff(char *argv[], int currArg, int argvLen)
{
	char numInString[argvLen-2];
	int j = 0;
	for (int i = 2; i<=argvLen; ++i, ++j)
		numInString[j] = argv[currArg][i];

	return (strtol(numInString, NULL, 10));
}

int getBuffVar(char *argv[], int currArg, int argvLen, int startAt)
{
	char numInString[argvLen-startAt];
	int j = 0;
	for (int i = startAt; i<=argvLen; ++i, ++j)
		numInString[j] = argv[currArg][i];

	return (strtol(numInString, NULL, 10));
}

float whichNpDamageModifier(int np, float caseOne, float caseTwo, float caseThree, float caseFour, float caseDefault)
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

void getCardDmg(int noChain, int total, int powerMod, int npAt, int critDamageMod, int critFirst, int critSecond, int critThird, int cardType, int busterFirst, int busterSecond, int busterThird, int artsFirst, int artsSecond, int artsThird, int quickFirst, int quickSecond, int quickThird, int servantAtk, int artsMod, int busterMod, int quickMod)
{
	if (noChain)
		printf("no card chain\n");

	float floatCrit;

	float cardFirst = 0;
	float cardSecond = 0;
	float cardThird = 0;

	float busterPercent = 1;
	float artsPercent = 1;
	float quickPercent = 1;
	
	float powerPercent = 1;

	if (busterMod)
		busterPercent = 1.0 + ((float)busterMod * 0.01);

	if (artsMod)
		artsPercent = 1.0 + ((float)artsMod * 0.01);

	if (quickMod)
		quickPercent = 1.0 + ((float)quickMod * 0.01);

	if (powerMod)
		powerPercent = 1.0 + ((float)powerMod * 0.01);

	floatCrit = 1.0 + (((float)critDamageMod + (float)powerMod) * 0.01);

	switch (npAt) {
	case 1:
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
		cardFirst = -1;
		break;
	case 2:
		switch (cardType) {
		case BUSTER:
			busterSecond = 1;
			break;
		case ARTS:
			artsSecond = 1;
			break;
		case QUICK:
			quickSecond = 1;
		}
		cardSecond = -1;
		break;
	case 3:
		switch (cardType) {
		case BUSTER:
			busterThird = 1;
			break;
		case ARTS:
			artsThird = 1;
			break;
		case QUICK:
			quickThird = 1;
		}
		cardThird = -1;
	}

	if (busterFirst) {
		if (!cardFirst)
			cardFirst = cardFirst + 0.5;
		if (!cardSecond)
			cardSecond = cardSecond + 0.5;
		if (!cardThird)
			cardThird = cardThird + 0.5;

		cardFirst = cardFirst + 1.5;
		cardFirst = cardFirst * busterPercent;

	} else if (quickFirst) {
		cardFirst = cardFirst + 0.8;
		cardFirst = cardFirst * quickPercent;

	} else if (artsFirst) {
		cardFirst = cardFirst + 1.0;
		cardFirst = cardFirst * artsPercent;
	}

	if (busterSecond) {
		cardSecond = cardSecond + 1.8;
		cardSecond = cardSecond * busterPercent;

	} else if (quickSecond) {
		cardSecond = cardSecond + 0.96;
		cardSecond = cardSecond * quickPercent;

	} else if (artsSecond) {
		cardSecond = cardSecond + 1.2;
		cardSecond = cardSecond * artsPercent;
	}

	if (busterThird) {
		cardThird = cardThird + 2.1;
		cardThird = cardThird * busterPercent;

	} else if (quickThird) {
		cardThird = cardThird + 1.12;
		cardThird = cardThird * quickPercent;

	} else if (artsThird) {
		cardThird = cardThird + 1.4;
		cardThird = cardThird * artsPercent;
	}

	if (critFirst)
		cardFirst = cardFirst * floatCrit;
	else
		cardFirst = cardFirst * powerPercent;

	if (critSecond)
		cardSecond = cardSecond * floatCrit;
	else
		cardSecond = cardSecond * powerPercent;

	if (critThird)
		cardThird = cardThird * floatCrit;
	else
		cardThird = cardThird * powerPercent;

	cardFirst = cardFirst * (float)total;
	cardSecond = cardSecond * (float)total;
	cardThird = cardThird * (float)total;

	if (busterFirst && busterSecond && busterThird) {
		float busterChainMod = BUSTER_CHAIN_MOD * (float)servantAtk;

		if (npAt != 1)
			cardFirst = cardFirst + busterChainMod;
		if (npAt != 2)
			cardSecond = cardSecond + busterChainMod;
		if (npAt != 3)
			cardThird = cardThird + busterChainMod;
	}

	if (cardFirst > 0)
		printf("%'g -- 1\n", cardFirst);
	if (cardSecond > 0)
		printf("%'g -- 2\n", cardSecond);
	if (cardThird > 0)
		printf("%'g -- 3\n", cardThird);
}

void getNpDamage(int cardType, int np, int npStrengthening, int npType, float *npDamageMultiplier, float *superEffectiveModifier, int total, int npDamageMod, int powerMod)
{
	float totalNp = 1;
	float whichCardMod = 1;

	switch (cardType) {
	case ARTS:
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(np, 5, 7.5, 8.25, 8.625, 9);
			else
				*npDamageMultiplier = whichNpDamageModifier(np, 4.5, 6, 6.75, 7.125, 7.5);

			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(np, 12, 15, 16.5, 17.25, 18);
			else
				*npDamageMultiplier = whichNpDamageModifier(np, 9, 12, 13.5, 14.25, 15);
		}
		break;
	case BUSTER:
		whichCardMod = 1.5;
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(np, 4, 5, 5.5, 5.75, 6);
			else
				*npDamageMultiplier = whichNpDamageModifier(np, 3, 4, 4.5, 4.75, 5);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(np, 8, 10, 11, 11.5, 12);
			else
				*npDamageMultiplier = whichNpDamageModifier(np, 6, 8, 9, 9.5, 10);
			break;
		}
		break;
	case QUICK:
		whichCardMod = 0.8;
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(np, 8, 10, 11, 11.5, 12);
			else
				*npDamageMultiplier = whichNpDamageModifier(np, 6, 8, 9, 9.5, 10);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(np, 16, 20, 22, 23, 24);
			else
				*npDamageMultiplier = whichNpDamageModifier(np, 12, 16, 18, 19, 20);
		}
	default:
		printf("card type not specified!\n");
	}

	float npPercent;

	npPercent = 1.0 + ((float)(npDamageMod + powerMod) * 0.01);

	totalNp = total
	* *superEffectiveModifier * *npDamageMultiplier * whichCardMod
	* npPercent;

	printf("%'g\n%'g ~ %'g\n", totalNp, (totalNp*0.9), (totalNp*1.1));
}

void getClassMod(int class, int classEnemy, int classTypeEnemy, float *classMod, float *classAtkBonus)
{
	switch (class) {
	case SABER:
		switch (classEnemy) {
		case LANCER:
			*classAtkBonus = 2;
			break;
		case ARCHER:
			*classAtkBonus = 0.5;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case ARCHER:
		*classMod = 0.95;

		switch (classEnemy) {
		case SABER:
			*classAtkBonus = 2;
			break;
		case LANCER:
			*classAtkBonus = 0.5;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case LANCER:
		*classMod = 1.05;

		switch (classEnemy) {
		case ARCHER:
			*classAtkBonus = 2;
			break;
		case SABER:
			*classAtkBonus = 0.5;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case ASSASSIN:
		*classMod = 0.9;

		switch (classEnemy) {
		case RIDER:
			*classAtkBonus = 2;
			break;
		case CASTER:
			*classAtkBonus = 0.5;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case CASTER:
		*classMod = 0.9;

		switch (classEnemy) {
		case ASSASSIN:
			*classAtkBonus = 2;
			break;
		case RIDER:
			*classAtkBonus = 0.5;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case RIDER:
		switch (classEnemy) {
		case CASTER:
			*classAtkBonus = 2;
			break;
		case ASSASSIN:
			*classAtkBonus = 0.5;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case BERSERKER:
		*classMod = 1.1;

		switch (classEnemy) {
		case FOREIGNER:
			*classAtkBonus = 2;
			break;
		default:
			*classAtkBonus = 1.5;
		}
		break;
	case RULER:
		*classMod = 1.1;

		switch (classEnemy) {
		case MOON_CANCER:
			*classAtkBonus = 2;
			break;
		case AVENGER:
			*classAtkBonus = 0.5;
		}
		break;
	case ALTER_EGO:
		*classMod = 1.0;

		switch (classTypeEnemy) {
		case KNIGHT:
			*classAtkBonus = 0.5;
			break;
		case CAVALRY:
			*classAtkBonus = 2;
			break;
		default:
			switch (classEnemy) {
			case FOREIGNER:
				*classAtkBonus = 2;
				break;
			case PRETENDER:
				*classAtkBonus = 0.5;
			}
		}
		break;
	case AVENGER:
		*classMod = 1.1;

		switch (classTypeEnemy) {
		case RULER:
			*classAtkBonus = 2;
			break;
		case MOON_CANCER:
			*classAtkBonus = 0.5;
		}
		break;
	case MOON_CANCER:
		switch (classTypeEnemy) {
		case AVENGER:
			*classAtkBonus = 2;
			break;
		case RULER:
			*classAtkBonus = 0.5;
		}
		break;
	case FOREIGNER:
		switch (classTypeEnemy) {
		case FOREIGNER:
			*classAtkBonus = 2;
			break;
		case PRETENDER:
			*classAtkBonus = 2;
			break;
		case ALTER_EGO:
			*classAtkBonus = 0.5;
		}
		break;
	case PRETENDER:
		switch (classTypeEnemy) {
		case KNIGHT:
			*classAtkBonus = 1.5;
			break;
		case CAVALRY:
			*classAtkBonus = 0.5;
			break;
		case 0:
			switch (classEnemy) {
			case ALTER_EGO:
				*classAtkBonus = 2;
				break;
			case FOREIGNER:
				*classAtkBonus = 0.5;
			}
		}
		break;
	default:
		printf("class not specified, defaults to no class advantage!\n");
	}

	if (classEnemy == BERSERKER)
		*classAtkBonus = 2;
}

void getAttributeMod(int attribute, int attributeEnemy, float *attributeModifier)
{
	switch (attribute) {
	case MAN:
		switch (attributeEnemy) {
		case SKY:
			*attributeModifier = 1.1;
			break;
		case EARTH:
			*attributeModifier = 0.9;
		}
		break;
	case SKY:
		switch (attributeEnemy) {
		case MAN:
			*attributeModifier = 0.9;
			break;
		case EARTH:
			*attributeModifier = 1.1;
		}
		break;
	case EARTH:
		switch (attributeEnemy) {
		case MAN:
			*attributeModifier = 1.1;
			break;
		case SKY:
			*attributeModifier = 0.9;
		}
		break;
	case STAR:

		if (attributeEnemy == BEAST) {
			*attributeModifier = 1.1;
		}
		break;
	case BEAST:

		if (attributeEnemy == STAR) {
			*attributeModifier = 1.1;
		}
		break;
	default:
		printf("attribute not specified!\n");
	}
}

int main(int argc, char *argv[])
{
	if (!argv[1]) {
		printf("Usage: calc arguments\n\n");
		printf("arguments:\n");
		printf("bb = buster servant\n");
		printf("aa = arts servant\n");
		printf("qq = quick servant\n\n");
		printf("st = single target np\n");
		printf("aoe = aoe np\n\n");
		printf("atk = attack stat\n");
		printf("au = attack up\n");
		printf("ad = attack down\n\n");
		printf("du = defense up\n");
		printf("dd = defense down\n");
		printf("di = defense ignore\n\n");
		printf("artsMod = arts up\n");
		printf("bm = buster up\n");
		printf("qm = quick up\n\n");
		printf("se = super effective; e.g., gilgamesh, se150\n");
		printf("sr = np strengthening\n");
		printf("nu = np damage up\n");
		printf("pm = powermod; e.g., arjuna alter, pm50\n");
		printf("cd = critical damage\n");
		exit(0);
	}
	int servantAtk = 1;
	int class = 0;
	int classEnemy = 0;

	/* int classType = 0; */

	int classTypeEnemy = 0;

	int cardType = 0;

	int attribute = 0;
	int attributeEnemy = 0;

	int npType = 0;

	int np = 5;

	float superEffectiveModifier = 1;
	int npStrengthening = 0;

	int atkMod = 0;
	int atkModDown = 0;

	int defMod = 0;
	int defModDown = 0;
	int defenseIgnore = 0;

	int artsMod = 0;
	int busterMod = 0;
	int quickMod = 0;

	int powerMod = 0;
	int npDamageMod = 0;
	int critDamageMod = 0;

	int noChain = 1;

	int busterFirst = 0;
	int busterSecond = 0;
	int busterThird = 0;

	int artsFirst = 0;
	int artsSecond = 0;
	int artsThird = 0;

	int quickFirst = 0;
	int quickSecond = 0;
	int quickThird = 0;

	int npAt = 0;

	int critFirst = 0;
	int critSecond = 0;
	int critThird = 0;

	int verbose = 0;
	int fou = 1000;

	for (int currArgv=1; currArgv<argc; ++currArgv) {

		int argvLen = strlen(argv[currArgv]);

		if (startsWith(2, "au", argv, currArgv, argvLen)) {
			atkMod = atkMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "ad", argv, currArgv, argvLen)) {
			atkModDown = atkModDown + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "dd", argv, currArgv, argvLen)) {
			defModDown = defModDown + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "du", argv, currArgv, argvLen)) {
			defMod = defMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "di", argv, currArgv, argvLen)) {
			defenseIgnore = 1;

		} else if (startsWith(2, "bm", argv, currArgv, argvLen)) {
			busterMod = busterMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "qm", argv, currArgv, argvLen)) {
			quickMod = quickMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "am", argv, currArgv, argvLen)) {
			artsMod = artsMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "pm", argv, currArgv, argvLen)) {
			powerMod = powerMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "nu", argv, currArgv, argvLen)) {
			npDamageMod = npDamageMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "cd", argv, currArgv, argvLen)) {
			critDamageMod = critDamageMod + getBuff(argv, currArgv, argvLen);

		} else if (startsWith(4, "crit", argv, currArgv, argvLen)) {
			critFirst = 1;
			critSecond = 1;
			critThird = 1;

		} else if (startsWith(3, "cr1", argv, currArgv, argvLen)) {
			critFirst = 1;

		} else if (startsWith(3, "cr2", argv, currArgv, argvLen)) {
			critSecond = 1;

		} else if (startsWith(3, "cr3", argv, currArgv, argvLen)) {
			critThird = 1;

		} else if (startsWith(2, "se", argv, currArgv, argvLen)) {
			superEffectiveModifier = getBuff(argv, currArgv, argvLen) / 100.0;

		} else if (startsWith(3, "atk", argv, currArgv, argvLen)) {
			servantAtk = getBuffVar(argv, currArgv, argvLen, 3);

		} else if (startsWith(2, "np", argv, currArgv, argvLen)) {
			np = getBuff(argv, currArgv, argvLen);

		} else if (startsWith(2, "sr", argv, currArgv, argvLen)) {
			npStrengthening = 1;

		} else if (startsWith(2, "vi", argv, currArgv, argvLen)) {
			busterMod = busterMod + 50;
			if (cardType == BUSTER) {
				critDamageMod = critDamageMod + 50;
			}

		} else if (startsWith(2, "ss", argv, currArgv, argvLen)) {
			atkMod = atkMod + 20;
			busterMod = busterMod + 15;
			quickMod = quickMod + 65;
			if (cardType == BUSTER) {
				critDamageMod = critDamageMod + 100;
			}

		} else if (startsWith(2, "sk", argv, currArgv, argvLen)) {
			atkMod = atkMod + 30;
			quickMod = quickMod + 50;
			if (cardType == QUICK) {
				critDamageMod = critDamageMod + critDamageMod + 100;
			}

		} else if (startsWith(2, "ca", argv, currArgv, argvLen)) {
			artsMod = artsMod + 50;
			atkMod = atkMod + 20;

		} else if (startsWith(2, "gf", argv, currArgv, argvLen)) {
			fou = getBuff(argv, currArgv, argvLen);
			if (fou > 2000) {
				fou = 2000;
			}

		} else if (startsWith(2, "-v", argv, currArgv, argvLen)) {
			verbose = 1;

		} else {
			if (!npType) {
				if (startsWith(2, "st", argv, currArgv, argvLen)) {
					npType = ST;
					continue;

				} else if (startsWith(2, "ao", argv, currArgv, argvLen)) {
					npType = AOE;
					continue;
				}
			}
			if (!cardType) {
				if (startsWith(2, "aa", argv, currArgv, argvLen)) {
					cardType = ARTS;
					continue;

				} else if (startsWith(2, "bb", argv, currArgv, argvLen)) {
					cardType = BUSTER;
					continue;

				} else if (startsWith(2, "qq", argv, currArgv, argvLen)) {
					cardType = QUICK;
					continue;
				}
			}
			if (!class) {
				if (startsWith(3, "sab", argv, currArgv, argvLen)) {
					class = SABER;
					/* classType = KNIGHT; */
					continue;

				} else if (startsWith(3, "arc", argv, currArgv, argvLen)) {
					class = ARCHER;
					/* classType = KNIGHT; */
					continue;

				} else if (startsWith(3, "lan", argv, currArgv, argvLen)) {
					class = LANCER;
					/* classType = KNIGHT; */
					continue;

				} else if (startsWith(3, "rid", argv, currArgv, argvLen)) {
					class = RIDER;
					/* classType = CAVALRY; */
					continue;

				} else if (startsWith(3, "ass", argv, currArgv, argvLen)) {
					class = ASSASSIN;
					/* classType = CAVALRY; */
					continue;

				} else if (startsWith(3, "cas", argv, currArgv, argvLen)) {
					class = CASTER;
					/* classType = CAVALRY; */
					continue;

				} else if (startsWith(3, "zer", argv, currArgv, argvLen)) {
					class = BERSERKER;
					continue;

				} else if (startsWith(3, "ave", argv, currArgv, argvLen)) {
					class = AVENGER;
					continue;

				} else if (startsWith(3, "alt", argv, currArgv, argvLen)) {
					class = ALTER_EGO;
					continue;

				} else if (startsWith(3, "moo", argv, currArgv, argvLen)) {
					class = MOON_CANCER;
					continue;

				} else if (startsWith(3, "for", argv, currArgv, argvLen)) {
					class = FOREIGNER;
					continue;

				} else if (startsWith(3, "pre", argv, currArgv, argvLen)) {
					class = PRETENDER;
					continue;
				}
			}
			if (!classEnemy) {
				if (startsWith(4, "esab", argv, currArgv, argvLen)) {
					classEnemy = SABER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (startsWith(4, "earc", argv, currArgv, argvLen)) {
					classEnemy = ARCHER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (startsWith(4, "elan", argv, currArgv, argvLen)) {
					classEnemy = LANCER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (startsWith(4, "erid", argv, currArgv, argvLen)) {
					classEnemy = RIDER;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (startsWith(4, "eass", argv, currArgv, argvLen)) {
					classEnemy = ASSASSIN;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (startsWith(4, "ecas", argv, currArgv, argvLen)) {
					classEnemy = CASTER;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (startsWith(4, "ezer", argv, currArgv, argvLen)) {
					classEnemy = BERSERKER;
					continue;

				} else if (startsWith(4, "erul", argv, currArgv, argvLen)) {
					classEnemy = RULER;
					continue;

				} else if (startsWith(4, "eave", argv, currArgv, argvLen)) {
					classEnemy = AVENGER;
					continue;

				} else if (startsWith(4, "emoo", argv, currArgv, argvLen)) {
					classEnemy = MOON_CANCER;
					continue;

				} else if (startsWith(4, "efor", argv, currArgv, argvLen)) {
					classEnemy = FOREIGNER;
					continue;

				} else if (startsWith(4, "epre", argv, currArgv, argvLen)) {
					classEnemy = PRETENDER;
					continue;
				}
			}
			if (!attribute) {
				if (startsWith(3, "man", argv, currArgv, argvLen)) {
					attribute = MAN;
					continue;

				} else if (startsWith(3, "sky", argv, currArgv, argvLen)) {
					attribute = SKY;
					continue;

				} else if (startsWith(3, "ear", argv, currArgv, argvLen)) {
					attribute = EARTH;
					continue;

				} else if (startsWith(3, "sta", argv, currArgv, argvLen)) {
					attribute = STAR;
					continue;

				} else if (startsWith(3, "bea", argv, currArgv, argvLen)) {
					attribute = BEAST;
					continue;
				}
			}
			if (!attributeEnemy) {
				if (startsWith(4, "eman", argv, currArgv, argvLen)) {
					attributeEnemy = MAN;
					continue;

				} else if (startsWith(4, "esky", argv, currArgv, argvLen)) {
					attributeEnemy = SKY;
					continue;

				} else if (startsWith(4, "eear", argv, currArgv, argvLen)) {
					attributeEnemy = EARTH;
					continue;

				} else if (startsWith(4, "esta", argv, currArgv, argvLen)) {
					attributeEnemy = STAR;
					continue;

				} else if (startsWith(4, "ebea", argv, currArgv, argvLen)) {
					attributeEnemy = BEAST;
					continue;
				}
			}
			if (noChain) {
				/* checkfirstcard */
				if (argv[currArgv][0] == 'a'){
					artsFirst = 1;
					noChain = 0;

				} else if (argv[currArgv][0] == 'b'){
					busterFirst = 1;
					noChain = 0;

				} else if (argv[currArgv][0] == 'q'){
					quickFirst = 1;
					noChain = 0;

				} else if (argv[currArgv][0] == 'n') {
					npAt = 1;
					noChain = 0;

				} else {
					continue;
				}
				/* checksecondcard */
				if (argv[currArgv][1] == 'a'){
					artsSecond = 1;

				} else if (argv[currArgv][1] == 'b'){
					busterSecond = 1;

				} else if (argv[currArgv][1] == 'q'){
					quickSecond = 1;

				} else if (argv[currArgv][1] == 'n') {
					npAt = 2;

				} else {
					continue;
				}
				/* checkthirdcard */
				if (argv[currArgv][2] == 'a'){
					artsThird = 1;

				} else if (argv[currArgv][2] == 'b'){
					busterThird = 1;

				} else if (argv[currArgv][2] == 'q'){
					quickThird = 1;

				} else if (argv[currArgv][2] == 'n') {
					npAt = 3;

				} else {
					continue;
				}
			}
		}
	}
	setlocale(LC_NUMERIC, "");

	float total = 1;
	float classAtkBonus = 1;
	float classMod = 1;
	float attributeModifier = 1;
	float npDamageMultiplier = 1;

	if (defModDown > 100) {
		defModDown = 100;
		printf("def down exceeds 100, defaults to 100!\n");
	}

	if (defenseIgnore)
		defMod = defMod - 100;

	getClassMod(class, classEnemy, classTypeEnemy, &classMod, &classAtkBonus);

	getAttributeMod(attribute, attributeEnemy, &attributeModifier);

	total = total
		* (1 + ((float)(atkMod + defModDown - defMod - atkModDown) * 0.01))
		* BASE_MULTIPLIER * classAtkBonus * classMod * attributeModifier
		* ((float)(servantAtk + fou));

	getCardDmg(noChain, total, powerMod, npAt, critDamageMod, critFirst, critSecond, critThird, cardType, busterFirst, busterSecond, busterThird, artsFirst, artsSecond, artsThird, quickFirst, quickSecond, quickThird, servantAtk, artsMod, busterMod, quickMod);

	getNpDamage(cardType, np, npStrengthening, npType, &npDamageMultiplier, &superEffectiveModifier, total, npDamageMod, powerMod);

	if (verbose) {
		printf("\nservantAtk:\n");
		printf("%d\n", servantAtk);

		printf("classAtkBonus:\n");
		printf("%f\n",attributeModifier);

		printf("\nAtk up:\n");
		printf("%d\n", atkMod);

		printf("busterMod:\n");
		printf("%d\n", busterMod);

		printf("artsMod:\n");
		printf("%d\n", busterMod);

		printf("quickMod:\n");
		printf("%d\n", busterMod);

		printf("powerMod:\n");
		printf("%d\n", powerMod);

		printf("npDamageMod:\n");
		printf("%d\n", npDamageMod);

		printf("npDamageMultiplier:\n");
		printf("%f\n",npDamageMultiplier);

		printf("atrributeMod:\n");
		printf("%f\n",classAtkBonus);

		printf("classMod:\n");
		printf("%f\n",classMod);

		printf("npDamageMultiplier:\n");
		printf("%f\n",npDamageMultiplier);
		}
	return 0;
}

/* [servantAtk 
 * npDamageMultiplier 
 * (firstCardBonus + (cardDamageValue * (1 + cardMod))) 
 * classAtkBonus 
 * triangleModifier 
 * attributeModifier 
 * randomModifier 
 * 0.23 
 * (1 + atkMod - defMod) 
 * criticalModifier 
 * extraCardModifier 
 * (1 - specialDefMod) 
 * {1 + powerMod + selfDamageMod + (critDamageMod * isCrit) + (npDamageMod * isNP)} 
 * {1 + ((superEffectiveModifier - 1) * isSuperEffective)}] 
   + dmgPlusAdd + selfDmgCutAdd + (servantAtk * busterChainMod) */

/* void parseArgs(char *argv[], int argc, int *atkMod, int *atkModDown, int *defModDown, int *defMod, int *defenseIgnore, int *busterMod, int *quickMod, int *artsMod, int *powerMod, int *critDamageMod, int *critFirst, int *critSecond, int *critThird, float *superEffectiveModifier, int *servantAtk, int *npStrengthening, int *npDamageMod, int *np, int *class, int *classEnemy, int *classTypeEnemy, int *cardType, int *npType, int *verbose, int *attribute, int *attributeEnemy, int *noChain, int *busterFirst, int *busterSecond, int *busterThird, int *artsFirst, int *artsSecond, int *artsThird, int *quickFirst, int *quickSecond, int *quickThird, int *npAt) */
/* { */
/* 	for (int currArgv=1; currArgv<argc; ++currArgv) { */

/* 		int argvLen = countTilNull(argv, currArgv); */

/* 		if (startsWith(2, "au", argv, currArgv, argvLen)) { */
/* 			*atkMod = *atkMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "ad", argv, currArgv, argvLen)) { */
/* 			*atkModDown = *atkModDown - getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "dd", argv, currArgv, argvLen)) { */
/* 			*defModDown = *defModDown + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "du", argv, currArgv, argvLen)) { */
/* 			*defMod = *defMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "di", argv, currArgv, argvLen)) { */
/* 			*defenseIgnore = 1; */

/* 		} else if (startsWith(2, "bm", argv, currArgv, argvLen)) { */
/* 			*busterMod = *busterMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "qm", argv, currArgv, argvLen)) { */
/* 			*quickMod = *quickMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "am", argv, currArgv, argvLen)) { */
/* 			*artsMod = *artsMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "pm", argv, currArgv, argvLen)) { */
/* 			*powerMod = *powerMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "nu", argv, currArgv, argvLen)) { */
/* 			*npDamageMod = *npDamageMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "cd", argv, currArgv, argvLen)) { */
/* 			*critDamageMod = *critDamageMod + getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(4, "*crit", argv, currArgv, argvLen)) { */
/* 			*critFirst = 1; */
/* 			*critSecond = 1; */
/* 			*critThird = 1; */

/* 		} else if (startsWith(3, "cr1", argv, currArgv, argvLen)) { */
/* 			*critFirst = 1; */

/* 		} else if (startsWith(3, "cr2", argv, currArgv, argvLen)) { */
/* 			*critSecond = 1; */

/* 		} else if (startsWith(3, "cr3", argv, currArgv, argvLen)) { */
/* 			*critThird = 1; */

/* 		} else if (startsWith(2, "se", argv, currArgv, argvLen)) { */
/* 			*superEffectiveModifier = getBuff(argv, currArgv, argvLen) / 100.0; */

/* 		} else if (startsWith(3, "*atk", argv, currArgv, argvLen)) { */
/* 			*servantAtk = getBuffVar(argv, currArgv, argvLen, 3) + 1000; */

/* 		} else if (startsWith(2, "*np", argv, currArgv, argvLen)) { */
/* 			*np = getBuff(argv, currArgv, argvLen); */

/* 		} else if (startsWith(2, "sr", argv, currArgv, argvLen)) { */
/* 			*npStrengthening = 1; */

/* 		} else if (startsWith(2, "vi", argv, currArgv, argvLen)) { */
/* 			*busterMod = *busterMod + 50; */
/* 			if (*cardType == BUSTER) { */
/* 				*critDamageMod = *critDamageMod + 50; */
/* 			} */

/* 		} else if (startsWith(2, "ss", argv, currArgv, argvLen)) { */
/* 			*atkMod = *atkMod + 20; */
/* 			*busterMod = *busterMod + 15; */
/* 			*quickMod = *quickMod + 65; */
/* 			if (*cardType == BUSTER) { */
/* 				*critDamageMod = *critDamageMod + 100; */
/* 			} */

/* 		} else if (startsWith(2, "sk", argv, currArgv, argvLen)) { */
/* 			*atkMod = *atkMod + 30; */
/* 			*quickMod = *quickMod + 50; */
/* 			if (*cardType == QUICK) { */
/* 				*critDamageMod = *critDamageMod + *critDamageMod + 100; */
/* 			} */

/* 		} else if (startsWith(2, "ca", argv, currArgv, argvLen)) { */
/* 			*artsMod = *artsMod + 50; */
/* 			*atkMod = *atkMod + 20; */

/* 		} else if (startsWith(2, "-v", argv, currArgv, argvLen)) { */
/* 			*verbose = 1; */

/* 		} else { */
/* 			if (!*npType) { */
/* 				if (startsWith(2, "st", argv, currArgv, argvLen)) { */
/* 					*npType = ST; */
/* 					continue; */

/* 				} else if (startsWith(2, "ao", argv, currArgv, argvLen)) { */
/* 					*npType = AOE; */
/* 					continue; */
/* 				} */
/* 			} */
/* 			if (!*cardType) { */
/* 				if (startsWith(2, "aa", argv, currArgv, argvLen)) { */
/* 					*cardType = ARTS; */
/* 					continue; */

/* 				} else if (startsWith(2, "bb", argv, currArgv, argvLen)) { */
/* 					*cardType = BUSTER; */
/* 					continue; */

/* 				} else if (startsWith(2, "qq", argv, currArgv, argvLen)) { */
/* 					*cardType = QUICK; */
/* 					continue; */
/* 				} */
/* 			} */
/* 			if (!*class) { */
/* 				if (startsWith(3, "sab", argv, currArgv, argvLen)) { */
/* 					*class = SABER; */
/* 					/1* *classType = KNIGHT; *1/ */
/* 					continue; */

/* 				} else if (startsWith(3, "arc", argv, currArgv, argvLen)) { */
/* 					*class = ARCHER; */
/* 					/1* *classType = KNIGHT; *1/ */
/* 					continue; */

/* 				} else if (startsWith(3, "lan", argv, currArgv, argvLen)) { */
/* 					*class = LANCER; */
/* 					/1* *classType = KNIGHT; *1/ */
/* 					continue; */

/* 				} else if (startsWith(3, "rid", argv, currArgv, argvLen)) { */
/* 					*class = RIDER; */
/* 					/1* *classType = CAVALRY; *1/ */
/* 					continue; */

/* 				} else if (startsWith(3, "ass", argv, currArgv, argvLen)) { */
/* 					*class = ASSASSIN; */
/* 					/1* *classType = CAVALRY; *1/ */
/* 					continue; */

/* 				} else if (startsWith(3, "cas", argv, currArgv, argvLen)) { */
/* 					*class = CASTER; */
/* 					/1* *classType = CAVALRY; *1/ */
/* 					continue; */

/* 				} else if (startsWith(3, "zer", argv, currArgv, argvLen)) { */
/* 					*class = BERSERKER; */
/* 					continue; */

/* 				} else if (startsWith(3, "ave", argv, currArgv, argvLen)) { */
/* 					*class = AVENGER; */
/* 					continue; */

/* 				} else if (startsWith(3, "alt", argv, currArgv, argvLen)) { */
/* 					*class = ALTER_EGO; */
/* 					continue; */

/* 				} else if (startsWith(3, "moo", argv, currArgv, argvLen)) { */
/* 					*class = MOON_CANCER; */
/* 					continue; */

/* 				} else if (startsWith(3, "for", argv, currArgv, argvLen)) { */
/* 					*class = FOREIGNER; */
/* 					continue; */

/* 				} else if (startsWith(3, "pre", argv, currArgv, argvLen)) { */
/* 					*class = PRETENDER; */
/* 					continue; */
/* 				} */
/* 			} */
/* 			if (!*classEnemy) { */
/* 				if (startsWith(4, "esab", argv, currArgv, argvLen)) { */
/* 					*classEnemy = SABER; */
/* 					*classTypeEnemy = KNIGHT; */
/* 					continue; */

/* 				} else if (startsWith(4, "earc", argv, currArgv, argvLen)) { */
/* 					*classEnemy = ARCHER; */
/* 					*classTypeEnemy = KNIGHT; */
/* 					continue; */

/* 				} else if (startsWith(4, "elan", argv, currArgv, argvLen)) { */
/* 					*classEnemy = LANCER; */
/* 					*classTypeEnemy = KNIGHT; */
/* 					continue; */

/* 				} else if (startsWith(4, "erid", argv, currArgv, argvLen)) { */
/* 					*classEnemy = RIDER; */
/* 					*classTypeEnemy = CAVALRY; */
/* 					continue; */

/* 				} else if (startsWith(4, "eass", argv, currArgv, argvLen)) { */
/* 					*classEnemy = ASSASSIN; */
/* 					*classTypeEnemy = CAVALRY; */
/* 					continue; */

/* 				} else if (startsWith(4, "ecas", argv, currArgv, argvLen)) { */
/* 					*classEnemy = CASTER; */
/* 					*classTypeEnemy = CAVALRY; */
/* 					continue; */

/* 				} else if (startsWith(4, "ezer", argv, currArgv, argvLen)) { */
/* 					*classEnemy = BERSERKER; */
/* 					continue; */

/* 				} else if (startsWith(4, "erul", argv, currArgv, argvLen)) { */
/* 					*classEnemy = RULER; */
/* 					continue; */

/* 				} else if (startsWith(4, "eave", argv, currArgv, argvLen)) { */
/* 					*classEnemy = AVENGER; */
/* 					continue; */

/* 				} else if (startsWith(4, "emoo", argv, currArgv, argvLen)) { */
/* 					*classEnemy = MOON_CANCER; */
/* 					continue; */

/* 				} else if (startsWith(4, "efor", argv, currArgv, argvLen)) { */
/* 					*classEnemy = FOREIGNER; */
/* 					continue; */

/* 				} else if (startsWith(4, "epre", argv, currArgv, argvLen)) { */
/* 					*classEnemy = PRETENDER; */
/* 					continue; */
/* 				} */
/* 			} */
/* 			if (!*attribute) { */
/* 				if (startsWith(3, "man", argv, currArgv, argvLen)) { */
/* 					*attribute = MAN; */
/* 					continue; */

/* 				} else if (startsWith(3, "sky", argv, currArgv, argvLen)) { */
/* 					*attribute = SKY; */
/* 					continue; */

/* 				} else if (startsWith(3, "ear", argv, currArgv, argvLen)) { */
/* 					*attribute = EARTH; */
/* 					continue; */

/* 				} else if (startsWith(3, "sta", argv, currArgv, argvLen)) { */
/* 					*attribute = STAR; */
/* 					continue; */

/* 				} else if (startsWith(3, "bea", argv, currArgv, argvLen)) { */
/* 					*attribute = BEAST; */
/* 					continue; */
/* 				} */
/* 			} */
/* 			if (!*attributeEnemy) { */
/* 				if (startsWith(4, "eman", argv, currArgv, argvLen)) { */
/* 					*attributeEnemy = MAN; */
/* 					continue; */

/* 				} else if (startsWith(4, "esky", argv, currArgv, argvLen)) { */
/* 					*attributeEnemy = SKY; */
/* 					continue; */

/* 				} else if (startsWith(4, "eear", argv, currArgv, argvLen)) { */
/* 					*attributeEnemy = EARTH; */
/* 					continue; */

/* 				} else if (startsWith(4, "esta", argv, currArgv, argvLen)) { */
/* 					*attributeEnemy = STAR; */
/* 					continue; */

/* 				} else if (startsWith(4, "ebea", argv, currArgv, argvLen)) { */
/* 					*attributeEnemy = BEAST; */
/* 					continue; */
/* 				} */
/* 			} */
/* 			if (*noChain) { */
/* 				/1* checkfirst*card *1/ */
/* 				if (argv[currArgv][0] == 'a'){ */
/* 					*artsFirst = 1; */
/* 					*noChain = 0; */

/* 				} else if (argv[currArgv][0] == 'b'){ */
/* 					*busterFirst = 1; */
/* 					*noChain = 0; */

/* 				} else if (argv[currArgv][0] == 'q'){ */
/* 					*quickFirst = 1; */
/* 					*noChain = 0; */

/* 				} else if (argv[currArgv][0] == 'n') { */
/* 					*npAt = 1; */
/* 					*noChain = 0; */

/* 				} else { */
/* 					continue; */
/* 				} */
/* 				/1* checksecond*card *1/ */
/* 				if (argv[currArgv][1] == 'a'){ */
/* 					*artsSecond = 1; */

/* 				} else if (argv[currArgv][1] == 'b'){ */
/* 					*busterSecond = 1; */

/* 				} else if (argv[currArgv][1] == 'q'){ */
/* 					*quickSecond = 1; */

/* 				} else if (argv[currArgv][1] == 'n') { */
/* 					*npAt = 2; */

/* 				} else { */
/* 					continue; */
/* 				} */
/* 				/1* checkthird*card *1/ */
/* 				if (argv[currArgv][2] == 'a'){ */
/* 					*artsThird = 1; */

/* 				} else if (argv[currArgv][2] == 'b'){ */
/* 					*busterThird = 1; */

/* 				} else if (argv[currArgv][2] == 'q'){ */
/* 					*quickThird = 1; */

/* 				} else if (argv[currArgv][2] == 'n') { */
/* 					*npAt = 3; */

/* 				} else { */
/* 					continue; */
/* 				} */
/* 			} */
/* 		} */
/* 	} */
/* } */

/* parseArgs(argv, argc, &atkMod, &atkModDown, &defModDown, &defMod, &defenseIgnore, &busterMod, &quickMod, &artsMod, &powerMod, &critDamageMod, &critFirst, &critSecond, &critThird, &superEffectiveModifier, &servantAtk, &npStrengthening, &npDamageMod, &np, &class, &classEnemy, &classTypeEnemy, &cardType, &npType, &verbose, &attribute, &attributeEnemy, &noChain, &busterFirst, &busterSecond, &busterThird, &artsFirst, &artsSecond, &artsThird, &quickFirst, &quickSecond, &quickThird, &npAt); */
