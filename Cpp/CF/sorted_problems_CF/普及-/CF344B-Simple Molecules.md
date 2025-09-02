---
title: "Simple Molecules"
layout: "post"
diff: 普及-
pid: CF344B
tag: []
---

# Simple Molecules

## 题目描述

Mad scientist Mike is busy carrying out experiments in chemistry. Today he will attempt to join three atoms into one molecule.

A molecule consists of atoms, with some pairs of atoms connected by atomic bonds. Each atom has a valence number — the number of bonds the atom must form with other atoms. An atom can form one or multiple bonds with any other atom, but it cannot form a bond with itself. The number of bonds of an atom in the molecule must be equal to its valence number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF344B/e6377325271b4515d315f9767d5c5b94bf56f174.png)Mike knows valence numbers of the three atoms. Find a molecule that can be built from these atoms according to the stated rules, or determine that it is impossible.

## 输入格式

The single line of the input contains three space-separated integers $ a $ , $ b $ and $ c $ ( $ 1<=a,b,c<=10^{6} $ ) — the valence numbers of the given atoms.

## 输出格式

If such a molecule can be built, print three space-separated integers — the number of bonds between the 1-st and the 2-nd, the 2-nd and the 3-rd, the 3-rd and the 1-st atoms, correspondingly. If there are multiple solutions, output any of them. If there is no solution, print "Impossible" (without the quotes).

## 说明/提示

The first sample corresponds to the first figure. There are no bonds between atoms 1 and 2 in this case.

The second sample corresponds to the second figure. There is one or more bonds between each pair of atoms.

The third sample corresponds to the third figure. There is no solution, because an atom cannot form bonds with itself.

The configuration in the fourth figure is impossible as each atom must have at least one atomic bond.

## 样例 #1

### 输入

```
1 1 2

```

### 输出

```
0 1 1

```

## 样例 #2

### 输入

```
3 4 5

```

### 输出

```
1 3 2

```

## 样例 #3

### 输入

```
4 1 1

```

### 输出

```
Impossible

```

