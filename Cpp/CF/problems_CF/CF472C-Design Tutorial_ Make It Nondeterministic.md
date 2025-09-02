---
title: "Design Tutorial: Make It Nondeterministic"
layout: "post"
diff: 普及/提高-
pid: CF472C
tag: []
---

# Design Tutorial: Make It Nondeterministic

## 题目描述

很多场合，名字是按姓的字典序排序的，但有的时候东方人和西方人姓名的顺序不一样，不知道哪个是姓，哪个是名，于是问题来了。给你n个人的姓名，每个姓名由两个字符串构成，有些姓在前，有的姓在后。现在给出这些人的排序，问这样的序列是否可能是这些名字的字典序排序。

## 输入格式

输入n  
然后n行每行输入两个字符串。  
最后一行输入一种n个数字的排列。

## 输出格式

如果可能是排列的顺序就输出YES，  
否则输出NO。
### 数据规模和约定
1<=n<=10^5  1<=字符串长度<=50。  
字符串一样时，顺序可任意。

## 样例 #1

### 输入

```
3
gennady korotkevich
petr mitrichev
gaoyuan chen
1 2 3

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
3
gennady korotkevich
petr mitrichev
gaoyuan chen
3 1 2

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
2
galileo galilei
nicolaus copernicus
2 1

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
10
rean schwarzer
fei claussell
alisa reinford
eliot craig
laura arseid
jusis albarea
machias regnitz
sara valestin
emma millstein
gaius worzel
1 2 3 4 5 6 7 8 9 10

```

### 输出

```
NO

```

## 样例 #5

### 输入

```
10
rean schwarzer
fei claussell
alisa reinford
eliot craig
laura arseid
jusis albarea
machias regnitz
sara valestin
emma millstein
gaius worzel
2 4 9 6 5 7 1 3 8 10

```

### 输出

```
YES

```

