# Binary Key

## 题目描述

Let's assume that $ p $ and $ q $ are strings of positive length, called the container and the key correspondingly, string $ q $ only consists of characters 0 and 1. Let's take a look at a simple algorithm that extracts message $ s $ from the given container $ p $ :

`<br></br>i = 0;<br></br>j = 0;<br></br>s = <>;<br></br>while i is less than the length of the string p<br></br>{<br></br>    if q[j] == 1, then add to the right of string s character p[i];<br></br>    increase variables i, j by one;<br></br>    if the value of the variable j equals the length of the string q, then j = 0; <br></br>}<br></br>`In the given pseudocode $ i $ , $ j $ are integer variables, $ s $ is a string, '=' is an assignment operator, '==' is a comparison operation, '\[\]' is the operation of obtaining the string character with the preset index, '<>' is an empty string. We suppose that in all strings the characters are numbered starting from zero.

We understand that implementing such algorithm is quite easy, so your task is going to be slightly different. You need to construct the lexicographically minimum key of length $ k $ , such that when it is used, the algorithm given above extracts message $ s $ from container $ p $ (otherwise find out that such key doesn't exist).

## 说明/提示

String $ x=x_{1}x_{2}...\ x_{p} $ is lexicographically smaller than string $ y=y_{1}y_{2}...\ y_{q} $ , if either $ p&lt;q $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{p}=y_{p} $ , or there exists such integer $ r $ ( $ 0<=r&lt;min(p,q)) $ that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ . Symbols are compared according to their ASCII codes.

## 样例 #1

### 输入

```
abacaba
aba
6
```

### 输出

```
100001
```

## 样例 #2

### 输入

```
abacaba
aba
3
```

### 输出

```
0
```

