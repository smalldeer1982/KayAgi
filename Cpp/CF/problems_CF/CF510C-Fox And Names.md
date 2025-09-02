---
title: "Fox And Names"
layout: "post"
diff: 普及+/提高
pid: CF510C
tag: ['字符串', '图论建模', '拓扑排序']
---

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ): number of names.

Each of the following $ n $ lines contain one string $ name_{i} $ ( $ 1<=|name_{i}|<=100 $ ), the $ i $ -th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 样例 #1

### 输入

```
3
rivest
shamir
adleman

```

### 输出

```
bcdefghijklmnopqrsatuvwxyz

```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever

```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz

```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck

```

### 输出

```
acbdefhijklmnogpqrstuvwxyz

```

