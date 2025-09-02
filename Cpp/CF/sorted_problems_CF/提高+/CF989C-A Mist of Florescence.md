---
title: "A Mist of Florescence"
layout: "post"
diff: 提高+/省选-
pid: CF989C
tag: ['连通块', '构造']
---

# A Mist of Florescence

## 题目描述

**题目大意：**

让你构造一个$n*m$矩阵，这个矩阵由4种字符填充构成，给定4个整数，即矩阵中每种字符构成的四联通块个数，$n,m$需要你自己定，但是不能超过50

## 输入格式

一行，四个整数$a,b,c,d$，即每种字符构成的四联通块个数，$1<=a,b,c,d<=100$

## 输出格式

一个矩阵

感谢@守望 提供翻译

## 样例 #1

### 输入

```
5 3 2 1

```

### 输出

```
4 7
DDDDDDD
DABACAD
DBABACD
DDDDDDD
```

## 样例 #2

### 输入

```
50 50 1 1

```

### 输出

```
4 50
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
ABABABABABABABABABABABABABABABABABABABABABABABABAB
BABABABABABABABABABABABABABABABABABABABABABABABABA
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
```

## 样例 #3

### 输入

```
1 6 4 5

```

### 输出

```
7 7
DDDDDDD
DDDBDBD
DDCDCDD
DBDADBD
DDCDCDD
DBDBDDD
DDDDDDD
```

