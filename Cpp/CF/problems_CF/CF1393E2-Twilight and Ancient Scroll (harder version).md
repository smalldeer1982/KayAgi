---
title: "Twilight and Ancient Scroll (harder version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1393E2
tag: []
---

# Twilight and Ancient Scroll (harder version)

## 题目描述

This is a harder version of the problem E with larger constraints.

Twilight Sparkle has received a new task from Princess Celestia. This time she asked to decipher the ancient scroll containing important knowledge of pony origin.

To hide the crucial information from evil eyes, pony elders cast a spell on the scroll. That spell adds exactly one letter in any place to each word it is cast on. To make the path to the knowledge more tangled elders chose some of words in the scroll and cast a spell on them.

Twilight Sparkle knows that the elders admired the order in all things so the scroll original scroll contained words in lexicographically non-decreasing order. She is asked to delete one letter from some of the words of the scroll (to undo the spell) to get some version of the original scroll.

Unfortunately, there may be more than one way to recover the ancient scroll. To not let the important knowledge slip by Twilight has to look through all variants of the original scroll and find the required one. To estimate the maximum time Twilight may spend on the work she needs to know the number of variants she has to look through. She asks you to find that number! Since that number can be very big, Twilight asks you to find it modulo $ 10^9+7 $ .

It may occur that princess Celestia has sent a wrong scroll so the answer may not exist.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le       10^5 $ ): the number of words in the scroll.

 The $ i $ -th of the next $ n $ lines contains a string consisting of lowercase English letters: the $ i $ -th word in the scroll. The length of each word is at least one. The sum of lengths of words does not exceed $ 10^6 $ .

## 输出格式

Print one integer: the number of ways to get a version of the original from the scroll modulo $ 10^9+7 $ .

## 说明/提示

Notice that the elders could have written an empty word (but they surely cast a spell on it so it holds a length $ 1 $ now).

## 样例 #1

### 输入

```
3
abcd
zaza
ataka
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
dfs
bfs
sms
mms
```

### 输出

```
8
```

## 样例 #3

### 输入

```
3
abc
bcd
a
```

### 输出

```
0
```

## 样例 #4

### 输入

```
6
lapochka
kartyshka
bigbabytape
morgenshtern
ssshhhiiittt
queen
```

### 输出

```
2028
```

