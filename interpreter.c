#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

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
	while (argv[currArgv][i++])
		;

	return i;
}

int subInStr(char *substr, char *str)
{
	while (*substr)
		if (*substr++ != *str++)
			return 0;
	return 1;
}

int getNum(char *argv, int argvLen)
{
	char strWithNum[argvLen];

	int i;
	for (int j=0, i=0; i<argvLen; ++i)
		if (isdigit(argv[i])) {
			strWithNum[j++] = argv[i];
		}
	return strtol(strWithNum, NULL, 10);
}

int servantAtk;
int class;
int classEnemy;

int classTypeEnemy;

int cardType;

int attribute;
int attributeEnemy;

int npType;

int np;

float superEffectiveModifier;
int npStrengthening;

int atkMod;
int atkModDown;

int defMod;
int defModDown;
int defenseIgnore;

int artsMod;
int busterMod;
int quickMod;

int powerMod;
int npDamageMod;
int critDamageMod;

int noChain;

int busterFirst;
int busterSecond;
int busterThird;

int artsFirst;
int artsSecond;
int artsThird;

int quickFirst;
int quickSecond;
int quickThird;

int npAt;

int critFirst;
int critSecond;
int critThird;

int verbose;
int fou;

void parseArgs(int argc, char *argv[])
{
	for (int currArgv=1; currArgv<argc; ++currArgv) {

		setvbuf(stdout, NULL, _IONBF, 0); 
		int argvLen = strlen(argv[currArgv]);

		if (subInStr("au", argv[currArgv])) {
			atkMod = atkMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("ad", argv[currArgv])) {
			atkModDown = atkModDown + getNum(argv[currArgv], argvLen);

		} else if (subInStr("dd", argv[currArgv])) {
			defModDown = defModDown + getNum(argv[currArgv], argvLen);

		} else if (subInStr("du", argv[currArgv])) {
			defMod = defMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("di", argv[currArgv])) {
			defenseIgnore = 1;

		} else if (subInStr("bm", argv[currArgv])) {
			busterMod = busterMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("qm", argv[currArgv])) {
			quickMod = quickMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("am", argv[currArgv])) {
			artsMod = artsMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("pm", argv[currArgv])) {
			powerMod = powerMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("nu", argv[currArgv])) {
			npDamageMod = npDamageMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("cd", argv[currArgv])) {
			critDamageMod = critDamageMod + getNum(argv[currArgv], argvLen);

		} else if (subInStr("crit", argv[currArgv])) {
			critFirst = 1;
			critSecond = 1;
			critThird = 1;

		} else if (subInStr("cr1", argv[currArgv])) {
			critFirst = 1;

		} else if (subInStr("cr2", argv[currArgv])) {
			critSecond = 1;

		} else if (subInStr("cr3", argv[currArgv])) {
			critThird = 1;

		} else if (subInStr("se", argv[currArgv])) {
			superEffectiveModifier = getNum(argv[currArgv], argvLen);

		} else if (subInStr("atk", argv[currArgv])) {
			servantAtk = getNum(argv[currArgv], argvLen);

		} else if (subInStr("np", argv[currArgv])) {
			np = getNum(argv[currArgv], argvLen);

		} else if (subInStr("sr", argv[currArgv])) {
			npStrengthening = 1;

		} else if (subInStr("vi", argv[currArgv])) {
			busterMod = busterMod + 50;
			if (cardType == BUSTER)
				critDamageMod = critDamageMod + 50;

		} else if (subInStr("ss", argv[currArgv])) {
			atkMod = atkMod + 20;
			busterMod = busterMod + 15;
			quickMod = quickMod + 65;
			if (cardType == BUSTER)
				critDamageMod = critDamageMod + 100;

		} else if (subInStr("sk", argv[currArgv])) {
			atkMod = atkMod + 30;
			quickMod = quickMod + 50;
			if (cardType == QUICK)
				critDamageMod = critDamageMod + critDamageMod + 100;

		} else if (subInStr("ca", argv[currArgv])) {
			artsMod = artsMod + 50;
			atkMod = atkMod + 20;

		} else if (subInStr("gf", argv[currArgv])) {
			fou = getNum(argv[currArgv], argvLen);
			if (fou > 2000)
				fou = 2000;

		} else if (subInStr("-v", argv[currArgv])) {
			verbose = 1;

		} else {
			if (!npType) {
				if (subInStr("st", argv[currArgv])) {
					npType = ST;
					continue;

				} else if (subInStr("ao", argv[currArgv])) {
					npType = AOE;
					continue;
				}
			}
			if (!cardType) {
				if (subInStr("aa", argv[currArgv])) {
					cardType = ARTS;
					continue;

				} else if (subInStr("bb", argv[currArgv])) {
					cardType = BUSTER;
					continue;

				} else if (subInStr("qq", argv[currArgv])) {
					cardType = QUICK;
					continue;
				}
			}
			if (!class) {
				if (subInStr("sab", argv[currArgv])) {
					class = SABER;
					/* classType = KNIGHT; */
					continue;

				} else if (subInStr("arc", argv[currArgv])) {
					class = ARCHER;
					/* classType = KNIGHT; */
					continue;

				} else if (subInStr("lan", argv[currArgv])) {
					class = LANCER;
					/* classType = KNIGHT; */
					continue;

				} else if (subInStr("rid", argv[currArgv])) {
					class = RIDER;
					/* classType = CAVALRY; */
					continue;

				} else if (subInStr("ass", argv[currArgv])) {
					class = ASSASSIN;
					/* classType = CAVALRY; */
					continue;

				} else if (subInStr("cas", argv[currArgv])) {
					class = CASTER;
					/* classType = CAVALRY; */
					continue;

				} else if (subInStr("zer", argv[currArgv])) {
					class = BERSERKER;
					continue;

				} else if (subInStr("ave", argv[currArgv])) {
					class = AVENGER;
					continue;

				} else if (subInStr("alt", argv[currArgv])) {
					class = ALTER_EGO;
					continue;

				} else if (subInStr("moo", argv[currArgv])) {
					class = MOON_CANCER;
					continue;

				} else if (subInStr("for", argv[currArgv])) {
					class = FOREIGNER;
					continue;

				} else if (subInStr("pre", argv[currArgv])) {
					class = PRETENDER;
					continue;
				}
			}
			if (!classEnemy) {
				if (subInStr("esab", argv[currArgv])) {
					classEnemy = SABER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (subInStr("earc", argv[currArgv])) {
					classEnemy = ARCHER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (subInStr("elan", argv[currArgv])) {
					classEnemy = LANCER;
					classTypeEnemy = KNIGHT;
					continue;

				} else if (subInStr("erid", argv[currArgv])) {
					classEnemy = RIDER;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (subInStr("eass", argv[currArgv])) {
					classEnemy = ASSASSIN;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (subInStr("ecas", argv[currArgv])) {
					classEnemy = CASTER;
					classTypeEnemy = CAVALRY;
					continue;

				} else if (subInStr("ezer", argv[currArgv])) {
					classEnemy = BERSERKER;
					continue;

				} else if (subInStr("erul", argv[currArgv])) {
					classEnemy = RULER;
					continue;

				} else if (subInStr("eave", argv[currArgv])) {
					classEnemy = AVENGER;
					continue;

				} else if (subInStr("emoo", argv[currArgv])) {
					classEnemy = MOON_CANCER;
					continue;

				} else if (subInStr("efor", argv[currArgv])) {
					classEnemy = FOREIGNER;
					continue;

				} else if (subInStr("epre", argv[currArgv])) {
					classEnemy = PRETENDER;
					continue;
				}
			}
			if (!attribute) {
				if (subInStr("man", argv[currArgv])) {
					attribute = MAN;
					continue;

				} else if (subInStr("sky", argv[currArgv])) {
					attribute = SKY;
					continue;

				} else if (subInStr("ear", argv[currArgv])) {
					attribute = EARTH;
					continue;

				} else if (subInStr("sta", argv[currArgv])) {
					attribute = STAR;
					continue;

				} else if (subInStr("bea", argv[currArgv])) {
					attribute = BEAST;
					continue;
				}
			}
			if (!attributeEnemy) {
				if (subInStr("eman", argv[currArgv])) {
					attributeEnemy = MAN;
					continue;

				} else if (subInStr("esky", argv[currArgv])) {
					attributeEnemy = SKY;
					continue;

				} else if (subInStr("eear", argv[currArgv])) {
					attributeEnemy = EARTH;
					continue;

				} else if (subInStr("esta", argv[currArgv])) {
					attributeEnemy = STAR;
					continue;

				} else if (subInStr("ebea", argv[currArgv])) {
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
}

float whichNpDamageModifier(float caseOne, float caseTwo, float caseThree, float caseFour, float caseDefault)
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

void getCardDmg(float total)
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

	floatCrit = 2.0 + (((float)critDamageMod + (float)powerMod) * 0.01);

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

void getNpDamage(float *npDamageMultiplier, float *superEffectiveModifier, float total)
{
	float totalNp = 1;
	float whichCardMod = 1;

	switch (cardType) {
	case ARTS:
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(5, 7.5, 8.25, 8.625, 9);
			else
				*npDamageMultiplier = whichNpDamageModifier(4.5, 6, 6.75, 7.125, 7.5);

			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(12, 15, 16.5, 17.25, 18);
			else
				*npDamageMultiplier = whichNpDamageModifier(9, 12, 13.5, 14.25, 15);
		}
		break;
	case BUSTER:
		whichCardMod = 1.5;
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(4, 5, 5.5, 5.75, 6);
			else
				*npDamageMultiplier = whichNpDamageModifier(3, 4, 4.5, 4.75, 5);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(8, 10, 11, 11.5, 12);
			else
				*npDamageMultiplier = whichNpDamageModifier(6, 8, 9, 9.5, 10);
			break;
		}
		break;
	case QUICK:
		whichCardMod = 0.8;
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(8, 10, 11, 11.5, 12);
			else
				*npDamageMultiplier = whichNpDamageModifier(6, 8, 9, 9.5, 10);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = whichNpDamageModifier(16, 20, 22, 23, 24);
			else
				*npDamageMultiplier = whichNpDamageModifier(12, 16, 18, 19, 20);
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

void getClassMod(float *classMod, float *classAtkBonus)
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

void getAttributeMod(float *attributeModifier)
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
	servantAtk = 1;
	class = 0;
	classEnemy = 0;

	classTypeEnemy = 0;

	cardType = 0;

	attribute = 0;
	attributeEnemy = 0;

	npType = 0;

	np = 5;

	superEffectiveModifier = 1;
	npStrengthening = 0;

	atkMod = 0;
	atkModDown = 0;

	defMod = 0;
	defModDown = 0;
	defenseIgnore = 0;

	artsMod = 0;
	busterMod = 0;
	quickMod = 0;

	powerMod = 0;
	npDamageMod = 0;
	critDamageMod = 0;

	noChain = 1;

	busterFirst = 0;
	busterSecond = 0;
	busterThird = 0;

	artsFirst = 0;
	artsSecond = 0;
	artsThird = 0;

	quickFirst = 0;
	quickSecond = 0;
	quickThird = 0;

	npAt = 0;

	critFirst = 0;
	critSecond = 0;
	critThird = 0;

	verbose = 0;
	fou = 1000;

	parseArgs(argc, argv);

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

	getClassMod(&classMod, &classAtkBonus);

	getAttributeMod(&attributeModifier);

	total = total
		* (1 + ((float)(atkMod + defModDown - defMod - atkModDown) * 0.01))
		* BASE_MULTIPLIER * classAtkBonus * classMod * attributeModifier
		* ((float)(servantAtk + fou));

	getCardDmg(total);

	getNpDamage(&npDamageMultiplier, &superEffectiveModifier, total);

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


/* parseArgs(argv, argc, &atkMod, &atkModDown, &defModDown, &defMod, &defenseIgnore, &busterMod, &quickMod, &artsMod, &powerMod, &critDamageMod, &critFirst, &critSecond, &critThird, &superEffectiveModifier, &servantAtk, &npStrengthening, &npDamageMod, &np, &class, &classEnemy, &classTypeEnemy, &cardType, &npType, &verbose, &attribute, &attributeEnemy, &noChain, &busterFirst, &busterSecond, &busterThird, &artsFirst, &artsSecond, &artsThird, &quickFirst, &quickSecond, &quickThird, &npAt); */
