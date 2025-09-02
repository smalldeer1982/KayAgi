---
title: "Fancy Number"
layout: "post"
diff: 普及+/提高
pid: CF118C
tag: []
---

# Fancy Number

## 题目描述

A car number in Berland consists of exactly $ n $ digits. A number is called beautiful if it has at least $ k $ equal digits. Vasya wants to change the digits in his car's number so that the number became beautiful. To replace one of $ n $ digits Vasya has to pay the sum of money, equal to the absolute difference between the old digit and the new one.

Help Vasya: find the minimum sum of money he should pay to make the number of his car beautiful. You should also find the resulting beautiful number. If there are several such numbers, then print the lexicographically minimum one.

## 输入格式

The first line contains two space-separated integers $ n $ and $ k $ ( $ 2<=n<=10^{4},2<=k<=n $ ) which represent how many digits the number has and how many equal digits a beautiful number should have. The second line consists of $ n $ digits. It describes the old number of Vasya's car. It is guaranteed that the number contains no spaces and only contains digits.

## 输出格式

On the first line print the minimum sum of money Vasya needs to change the number. On the second line print the car's new number. If there are several solutions, print the lexicographically minimum one.

## 说明/提示

In the first sample replacing the second digit with an "8" costs $ |9-8|=1 $ . Replacing the fifth digit with an "8" costs the same. Replacing the sixth digit costs $ |6-8|=2 $ . As a result, Vasya will pay $ 1+1+2=4 $ for a beautiful number "888188".

The lexicographical comparison of strings is performed by the < operator in modern programming languages. The string $ x $ is lexicographically smaller than the string $ y $ , if there exists such $ i $ ( $ 1<=i<=n $ ), that $ x_{i}&lt;y_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ x_{j}=y_{j} $ . The strings compared in this problem will always have the length $ n $ .

## 样例 #1

### 输入

```
6 5
898196

```

### 输出

```
4
888188

```

## 样例 #2

### 输入

```
3 2
533

```

### 输出

```
0
533

```

## 样例 #3

### 输入

```
10 6
0001112223

```

### 输出

```
3
0000002223

```

