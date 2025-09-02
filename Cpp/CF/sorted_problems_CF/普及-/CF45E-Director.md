---
title: "Director"
layout: "post"
diff: 普及-
pid: CF45E
tag: []
---

# Director

## 题目描述

给出$n$个名字和$n$个附名，请你将名字和附名两两配对，使得首字母相同的名字对数最多，并以最小字典序输出。

## 输入格式

第一行一个正整数$n(1 \leq n \leq 100)$

接下来$n$行每行一个长度不超过$10$的字符串描述一个名字。接下来$n$行每行一个长度不超过$10$的字符串描述一个附名。数据保证字符串两两不同，字符串的第一个字母为大写拉丁字母，其余为小写拉丁字母

## 输出格式

$Name_1\ Surname_1,\ Name_2\ Surname_2,\ ... \,,\ Name_n\ Surname_n$

其中$Name_i$与$Surname_i$为一对配对的名字与附名，其间用一个空格隔开。每一对名字之间用一个逗号加一个空格隔开。$Surname_n$之后不能出现额外的空格或者逗号

## 样例 #1

### 输入

```
4
Ann
Anna
Sabrina
John
Petrov
Ivanova
Stoltz
Abacaba

```

### 输出

```
Ann Abacaba, Anna Ivanova, John Petrov, Sabrina Stoltz
```

## 样例 #2

### 输入

```
4
Aa
Ab
Ac
Ba
Ad
Ae
Bb
Bc

```

### 输出

```
Aa Ad, Ab Ae, Ac Bb, Ba Bc
```

