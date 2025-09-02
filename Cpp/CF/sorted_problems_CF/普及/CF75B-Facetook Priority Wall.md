---
title: "Facetook Priority Wall"
layout: "post"
diff: 普及/提高-
pid: CF75B
tag: []
---

# Facetook Priority Wall

## 题目描述

Facetook 是一个知名的社交网站，它将推出一个名为 Facetook Priority Wall 的新功能。这一功能将根据优先级因子对你朋友的所有帖子进行排序。

优先级因子将受到三种行为的影响：
1. ```"X posted on Y's wall"``` (15 分), 
2. ```"X commented on Y's post"``` (10 分), 
3. ```"X likes Y's post"``` (5 分).

$X$ 和 $Y$ 是两个不同的名字。每一种行为都会使 $X$ 和 $Y$ 之间的优先级因子增加对应分数 ($X$ 和 $Y$ 之间的优先级因子与 $Y$ 和 $X$ 之间的优先级因子相同) 。

给定 $n$ 个上述格式的行为（没有行为序号和行为分数），你要将所有除自己名字以外的名字按照优先级因子打印出来。

## 输入格式

第一行输入包含你的名字。第二行输入包含一个整数 $n$ 代表行为数。 接下来有 $n$ 行输入，保证每个行为都是上面给出的格式中的一个操作。一行中的两个单词之间只有一个空格，没有多余的空格。所有的字母都是小写的。

输入的所有名称将由至少一个字母和最多 10 个小写拉丁字母组成。

## 输出格式

输出 $m$ 行， $m$ 是所有不同名字的数量（不包括你自己的名字）。每行只包含一个名字。名字要按照优先级因子。

降序顺序排列（优先级因子分数高的排前面）。如果有同分情况，按照名字的词典编纂的字母序排列。

## 样例 #1

### 输入

```
ahmed
3
ahmed posted on fatma's wall
fatma commented on ahmed's post
mona likes ahmed's post

```

### 输出

```
fatma
mona

```

## 样例 #2

### 输入

```
aba
1
likes likes posted's post

```

### 输出

```
likes
posted

```

