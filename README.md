# calc.c
A simple FGO damage calculator.
## Dependencies
getList and GLOBAL from https://github.com/IAKOBVS/scripts4fgo, which requires jq, recode, and wget
## Installation
```
gcc calc.c -o /path/to/bins
```
## Usage:
```
autocalc servant arguments
```
## Arguments:
```
atk = atk stat
am = arts up
bm = buster up
qm = quick up
np = np damage
pm = powermod
se = special attack (e.g., se150)
```
