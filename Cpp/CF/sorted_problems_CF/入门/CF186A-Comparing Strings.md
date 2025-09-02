---
title: "Comparing Strings"
layout: "post"
diff: 入门
pid: CF186A
tag: []
---

# Comparing Strings

## 题目描述

Some dwarves that are finishing the StUDY (State University for Dwarven Youngsters) Bachelor courses, have been told "no genome, no degree". That means that all dwarves should write a thesis on genome. Dwarven genome is far from simple. It is represented by a string that consists of lowercase Latin letters.

Dwarf Misha has already chosen the subject for his thesis: determining by two dwarven genomes, whether they belong to the same race. Two dwarves belong to the same race if we can swap two characters in the first dwarf's genome and get the second dwarf's genome as a result. Help Dwarf Misha and find out whether two gnomes belong to the same race or not.

## 输入格式

The first line contains the first dwarf's genome: a non-empty string, consisting of lowercase Latin letters.

The second line contains the second dwarf's genome: a non-empty string, consisting of lowercase Latin letters.

The number of letters in each genome doesn't exceed $ 10^{5} $ . It is guaranteed that the strings that correspond to the genomes are different. The given genomes may have different length.

## 输出格式

Print "YES", if the dwarves belong to the same race. Otherwise, print "NO".

## 说明/提示

- First example: you can simply swap two letters in string "ab". So we get "ba".
- Second example: we can't change string "aa" into string "ab", because "aa" does not contain letter "b".

## 样例 #1

### 输入

```
ab
ba

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
aa
ab

```

### 输出

```
NO

```

