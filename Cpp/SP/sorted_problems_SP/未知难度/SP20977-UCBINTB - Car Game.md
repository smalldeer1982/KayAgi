---
title: "UCBINTB - Car Game"
layout: "post"
diff: 难度0
pid: SP20977
tag: []
---

# UCBINTB - Car Game

## 题目描述

Traveling by car can sometimes be very boring. The natural cure for this boredom is to play a word

## 输入格式

The first line of input contains two positive integers (N 5000) and (M 10000), the number of words

in the dictionary and the number of license plates to be handled. Each of the following N lines contains

a word from the dictionary, a string no more than 100 characters long containing only lower case letters

from the English alphabet. This is followed by M lines each containing a string of three uppercase letters

from the English alphabet, representing a license plate.

## 输出格式

For each license plate in the input you should output one line containing either the first valid word in

the dictionary or the sentence "No valid word" if no such word exists.

## 样例 #1

### 输入

```
5 3
banana
car
sand
uncharacteristically
counterrevolutionaries
RRR
DNA
SND
```

### 输出

```
counterrevolutionaries
No valid word
sand
```

