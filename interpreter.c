#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

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
#define BASE_MULTIPLIER 0.23

#define FIRST 1
#define SECOND 0b10
#define THIRD 0b100

#define VERBOSE 1
#define STR 0b10
#define DEF_IGNORE 0b100

float superEffectiveModifier = 1;
char cardChain[3];
int servantAtk = 1;
int np = 5;
int fou = 1000;
int npAt;
int critAt;
int class;
int classEnemy;
int classTypeEnemy;
int cardType;
int attribute;
int attributeEnemy;
int npType;
int npStrengthening;
int atkMod;
int atkModDown;
int defMod;
int defModDown;
int artsMod;
int busterMod;
int quickMod;
int powerMod;
int npDamageMod;
int critDamageMod;
int verbose;
int enabled;

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
	for (int i=0, j=0; i<argvLen; ++i)
		if (isdigit(argv[i]))
			strWithNum[j++] = argv[i];
	return strtol(strWithNum, NULL, 10);
}

void parseArgv(int argc, char *argv[])
{
	for (int currArgv=1; currArgv<argc; ++currArgv) {
		setvbuf(stdout, NULL, _IONBF, 0); 
		int argvLen = strlen(argv[currArgv]);
		if (subInStr("au", argv[currArgv])) {
			atkMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("ad", argv[currArgv])) {
			atkModDown += getNum(argv[currArgv], argvLen);
		} else if (subInStr("dd", argv[currArgv])) {
			defModDown += getNum(argv[currArgv], argvLen);
		} else if (subInStr("du", argv[currArgv])) {
			defMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("di", argv[currArgv])) {
			enabled |= DEF_IGNORE;
		} else if (subInStr("bm", argv[currArgv])) {
			busterMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("qm", argv[currArgv])) {
			quickMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("am", argv[currArgv])) {
			artsMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("pm", argv[currArgv])) {
			powerMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("nu", argv[currArgv])) {
			npDamageMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("cd", argv[currArgv])) {
			critDamageMod += getNum(argv[currArgv], argvLen);
		} else if (subInStr("crit", argv[currArgv])) {
			critAt = FIRST | SECOND | THIRD;
		} else if (subInStr("cr1", argv[currArgv])) {
			critAt = FIRST;
		} else if (subInStr("cr2", argv[currArgv])) {
			critAt = SECOND;
		} else if (subInStr("cr3", argv[currArgv])) {
			critAt = THIRD;
		} else if (subInStr("se", argv[currArgv])) {
			superEffectiveModifier = getNum(argv[currArgv], argvLen);
		} else if (subInStr("atk", argv[currArgv])) {
			servantAtk = getNum(argv[currArgv], argvLen);
		} else if (subInStr("np", argv[currArgv])) {
			np = getNum(argv[currArgv], argvLen);
		} else if (subInStr("sr", argv[currArgv])) {
			enabled |= STR;
		} else if (subInStr("vi", argv[currArgv])) {
			busterMod += 50;
			if (cardType == BUSTER)
				critDamageMod += 50;
		} else if (subInStr("ss", argv[currArgv])) {
			atkMod += 20;
			busterMod += 15;
			quickMod += 65;
			if (cardType == BUSTER)
				critDamageMod += 100;
		} else if (subInStr("sk", argv[currArgv])) {
			atkMod += 30;
			quickMod += 50;
			if (cardType == QUICK)
				critDamageMod += 100;
		} else if (subInStr("ca", argv[currArgv])) {
			artsMod += 50;
			atkMod += 20;
		} else if (subInStr("gf", argv[currArgv])) {
			fou = getNum(argv[currArgv], argvLen);
			if (fou > 2000)
				fou = 2000;
		} else if (subInStr("-v", argv[currArgv])) {
			enabled |= VERBOSE;
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
			if (!cardChain[0] && argvLen == 3) {
				for (int i=0; i<3; ++i) {
					switch (argv[currArgv][i]) {
					case 'a':
					case 'b':
					case 'q':
					case 'n':
						continue;
						break;
					default:
						return;
					}
					i = 0;
					switch (argv[currArgv][i]) {
					case 'a':
						cardChain[i] = 'a';
						break;
					case 'b':
						cardChain[i] = 'b';
						break;
					case 'q':
						cardChain[i] = 'q';
						break;
					case 'n':
						cardChain[i] = 'n';
						npAt = ++i;
					}
				}
			}
		}
	}
	if (cardChain[0])
		switch (cardType) {
		case BUSTER:
			cardChain[--npAt] = 'b';
			break;
		case ARTS:
			cardChain[--npAt] = 'a';
			break;
		case QUICK:
			cardChain[--npAt] = 'q';
		}
}

float getNpDamageModifier(float caseOne, float caseTwo, float caseThree, float caseFour, float caseDefault)
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
	if (!cardChain[0]) {
		printf("no card chain\n");
		return;
	}
	float floatCrit;
	float cardAt[3] = {0};
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
	switch (cardChain[0]) {
	case 'b':
		if (cardChain[0])
			cardAt[0] += 0.5;
		if (cardChain[1])
			cardAt[1] += 0.5;
		if (cardChain[2])
			cardAt[2] += 0.5;
		cardAt[0] = (cardAt[0] + 1.5) * busterPercent;
		break;
	case 'q':
		cardAt[0] = (cardAt[0] + 0.8) * quickPercent;
		break;
	case 'a':
		cardAt[0] = (cardAt[0] + 1.0) * artsPercent;
	}
	switch (cardChain[1]) {
	case 'b':
		cardAt[1] = (cardAt[1] + 1.8) * busterPercent;
		break;
	case 'q':
		cardAt[1] = (cardAt[1] + 0.96) * quickPercent;
		break;
	case 'a':
		cardAt[1] = (cardAt[1] + 1.2) * artsPercent;
	}
	switch (cardChain[1]) {
	case 'b':
		cardAt[2] = (cardAt[2] + 2.1) * busterPercent;
		break;
	case 'q':
		cardAt[2] = (cardAt[2] + 1.12) * quickPercent;
		break;
	case 'a':
		cardAt[2] = (cardAt[2] + 1.4) * artsPercent;
	}
	if (critAt & FIRST)
		cardAt[0] *= floatCrit * (float)total;
	else
		cardAt[0] *= powerPercent * (float)total;
	if (critAt & SECOND)
		cardAt[1] *= floatCrit * (float)total;
	else
		cardAt[1] *= powerPercent * (float)total;
	if (critAt & THIRD)
		cardAt[2] *= floatCrit * (float)total;
	else
		cardAt[2] *= powerPercent * (float)total;
	if (cardChain[0] == 'b' && cardChain[1] == 'b' && cardChain[2] == 'b') {
		float busterChainMod = BUSTER_CHAIN_MOD * (float)servantAtk;
		switch (npAt) {
		case 1:
			cardAt[1] += busterChainMod;
			cardAt[2] += busterChainMod;
			break;
		case 2:
			cardAt[0] += busterChainMod;
			cardAt[2] += busterChainMod;
			break;
		case 3:
			cardAt[0] += busterChainMod;
			cardAt[1] += busterChainMod;
			break;
		default:
			cardAt[0] += busterChainMod;
			cardAt[1] += busterChainMod;
			cardAt[2] += busterChainMod;
		}
	}
	if (cardAt[0] > 0)
		printf("%'g -- 1\n", cardAt[0]);
	if (cardAt[1] > 0)
		printf("%'g -- 2\n", cardAt[1]);
	if (cardAt[2] > 0)
		printf("%'g -- 3\n", cardAt[2]);
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
				*npDamageMultiplier = getNpDamageModifier(5, 7.5, 8.25, 8.625, 9);
			else
				*npDamageMultiplier = getNpDamageModifier(4.5, 6, 6.75, 7.125, 7.5);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = getNpDamageModifier(12, 15, 16.5, 17.25, 18);
			else
				*npDamageMultiplier = getNpDamageModifier(9, 12, 13.5, 14.25, 15);
		}
		break;
	case BUSTER:
		whichCardMod = 1.5;
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = getNpDamageModifier(4, 5, 5.5, 5.75, 6);
			else
				*npDamageMultiplier = getNpDamageModifier(3, 4, 4.5, 4.75, 5);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = getNpDamageModifier(8, 10, 11, 11.5, 12);
			else
				*npDamageMultiplier = getNpDamageModifier(6, 8, 9, 9.5, 10);
			break;
		}
		break;
	case QUICK:
		whichCardMod = 0.8;
		switch (npType) {
		case AOE:
			if (npStrengthening)
				*npDamageMultiplier = getNpDamageModifier(8, 10, 11, 11.5, 12);
			else
				*npDamageMultiplier = getNpDamageModifier(6, 8, 9, 9.5, 10);
			break;
		case ST:
			if (npStrengthening)
				*npDamageMultiplier = getNpDamageModifier(16, 20, 22, 23, 24);
			else
				*npDamageMultiplier = getNpDamageModifier(12, 16, 18, 19, 20);
		}
	default:
		printf("card type not specified!\n");
	}
	float npPercent;
	npPercent = 1.0 + (float)npDamageMod * 0.01;
	totalNp = total
	* *superEffectiveModifier * *npDamageMultiplier * whichCardMod
	* npPercent;
	printf("%'g\n%'g ~ %'g\n", totalNp, (totalNp * 0.9), (totalNp * 1.1));
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
		if (attributeEnemy == BEAST)
			*attributeModifier = 1.1;
		break;
	case BEAST:
		if (attributeEnemy == STAR)
			*attributeModifier = 1.1;
		break;
	default:
		printf("attribute not specified!\n");
	}
}

void printVerbose(float attributeModifier, float npDamageMultiplier, float classAtkBonus, float classMod)
{
	printf("servantAtk:\n%d\n", servantAtk);
	printf("classAtkBonus:\n%'g\n", attributeModifier);
	printf("Atk up:\n%d\n", atkMod);
	printf("busterMod:\n%d\n", busterMod);
	printf("artsMod:\n%d\n", artsMod);
	printf("quickMod:\n%d\n", quickMod);
	printf("powerMod:\n%d\n", powerMod);
	printf("npDamageMod:\n%d\n", npDamageMod);
	printf("atrributeModifier:\n%'g\n", attributeModifier);
	printf("classAtkBonus: \n%'g\n",classAtkBonus);
	printf("classMod:\n%'g\n", classMod);
	printf("npDamageMultiplier:\n%'g\n", npDamageMultiplier);
}

void printHelp(void)
{
	printf("Usage: calc arguments\n\n"
	"arguments:\n"
	"bb = buster servant\n"
	"aa = arts servant\n"
	"qq = quick servant\n"
	"\n"
	"st = single target np\n"
	"aoe = aoe np\n"
	"\n"
	"atk = attack stat\n"
	"au = attack up\n"
	"ad = attack down\n"
	"\n"
	"du = defense up\n"
	"dd = defense down\n"
	"di = defense ignore\n"
	"\n"
	"artsMod = arts up\n"
	"bm = buster up\n"
	"qm = quick up\n"
	"\n"
	"se = super effective; e.g., gilgamesh, se150\n"
	"sr = np strengthening\n"
	"nu = np damage up\n"
	"pm = powermod; e.g., arjuna alter, pm50\n"
	"cd = critical damage\n");
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printHelp();
		return 0;
	}
	parseArgv(argc, argv);
	if (defModDown > 100)
		defModDown = 100, printf("def down exceeds 100, defaults to 100!\n");
	if (enabled & DEF_IGNORE)
		defMod -= 100;
	float total = 1;
	float classMod = 1;
	float classAtkBonus = 1;
	float attributeModifier = 1;
	float npDamageMultiplier = 1;
	getClassMod(&classMod, &classAtkBonus);
	getAttributeMod(&attributeModifier);
	total = total
		* (1 + ((float)(atkMod + defModDown - defMod - atkModDown) * 0.01))
		* BASE_MULTIPLIER * classAtkBonus * classMod * attributeModifier
		* ((float)(servantAtk + fou));
	setlocale(LC_NUMERIC, "");
	getCardDmg(total);
	getNpDamage(&npDamageMultiplier, &superEffectiveModifier, total);
	if (enabled & VERBOSE)
		printVerbose(attributeModifier, npDamageMultiplier, classAtkBonus, classMod);
	return 0;
}
