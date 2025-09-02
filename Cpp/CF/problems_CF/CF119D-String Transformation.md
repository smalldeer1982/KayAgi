---
title: "String Transformation"
layout: "post"
diff: 省选/NOI-
pid: CF119D
tag: []
---

# String Transformation

## 题目描述

Let $ s $ be a string whose length equals $ n $ . Its characters are numbered from 0 to $ n-1 $ , $ i $ and $ j $ are integers, $ 0<=i&lt;j&lt;n $ . Let's define function $ f $ as follows:

 $ f(s,i,j)=s[i+1...\ j-1]+r(s[j...\ n-1])+r(s[0...\ i]) $ .

Here $ s[p...\ q] $ is a substring of string $ s $ , that starts in position $ p $ and ends in position $ q $ (inclusive); "+" is the string concatenation operator; $ r(x) $ is a string resulting from writing the characters of the $ x $ string in the reverse order. If $ j=i+1 $ , then the substring $ s[i+1...\ j-1] $ is considered empty.

You are given two strings $ a $ and $ b $ . Find such values of $ i $ and $ j $ , that $ f(a,i,j)=b $ . Number $ i $ should be maximally possible. If for this $ i $ there exists several valid values of $ j $ , choose the minimal $ j $ .

## 输入格式

The first two input lines are non-empty strings $ a $ and $ b $ correspondingly. Each string's length does not exceed $ 10^{6} $ characters. The strings can contain any characters with ASCII codes from 32 to 126 inclusive.

## 输出格式

Print two integers $ i $ , $ j $ — the answer to the problem. If no solution exists, print "-1 -1" (without the quotes).

## 样例 #1

### 输入

```
Die Polizei untersucht eine Straftat im IT-Bereich.
untersucht eine Straftat.hciereB-TI mi  ieziloP eiD

```

### 输出

```
11 36

```

## 样例 #2

### 输入

```
cbaaaa
aaaabc

```

### 输出

```
4 5

```

## 样例 #3

### 输入

```
123342
3324212

```

### 输出

```
-1 -1
```

