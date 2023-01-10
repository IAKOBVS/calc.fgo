# calc.c
A simple FGO damage calculator.
## Dependencies
getList and GLOBAL from https://github.com/IAKOBVS/scripts4fgo, which requires jq, recode, and wget
## Installation
```
gcc interpreter.c -o /path/to/bins/calc
```
## Usage:
```
autocalc <arguments>
```
## Arguments:
```
atk = atk stat
au = atk up
am = arts up
bm = buster up
qm = quick up
np = np damage
pm = powermod
se = special attack (e.g., se150)

enemy
attribute; e.g., eearth, esky
class; e.g., esaber, eavenger
```
