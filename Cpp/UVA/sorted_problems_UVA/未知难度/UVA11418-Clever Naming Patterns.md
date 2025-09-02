---
title: "Clever Naming Patterns"
layout: "post"
diff: 难度0
pid: UVA11418
tag: []
---

# Clever Naming Patterns

## 题目描述

Piotr 在组织一场比赛。比赛需要由 $n$ 道题构成，每道题目名称的首字母都依次由 $A$、$B$、$C$…… 命名。Piotr 一共有 $n$ 个题目组，他需要从每个组里面抽出来一道题作为比赛的某一个题。请问，他应该如何组题使以 $A$、$B$、$C$…… 开头的题目都有，且每个题目组都要抽出 $1$ 道题目。

保证唯一解。

## 输入格式

第一行一个整数 $T$，表示数据组数。对于每一组数据：

第一行一个整数 $n$，表示比赛题目的数量以及 Piotr 拥有的题目组的数量。

接下来 $n$ 行，每行以一个整数 $k_i$ 开头，表示第 $i$ 个题目组有 $k_i$ 道题目，接下来输入 $k_i$ 个字符串，表示此题目组中的题目的名称。

**注意：在输入字符串后，需要先把每一个字符串的首字母改成大写英文字母，把后面的字母改成小写字母，然后再进行后面的操作，且输出时也按此格式输出。**

## 输出格式

对于每组数据：

第一行输出 `Case #x:`，$x$ 表示数据的编号。

接下来 $n$ 行，每行一个字符串，表示比赛的第 $i$ 道题目的名称。

## 样例 #1

### 输入

```
4
3
2 Apples Oranges
1 Bananas
5 Apricots Blueberries Cranberries Zuccini Yams
1
1 ApPlEs
2
2 a b
1 axe
4
4 Aa Ba Ca Da
3 Ab Bb Cb
2 Ac Bc
1 Ad
```

### 输出

```
Case #1:
Apples
Bananas
Cranberries
Case #2:
Apples
Case #3:
Axe
B
Case #4:
Ad
Bc
Cb
Da
```

