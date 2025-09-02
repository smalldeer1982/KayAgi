---
title: "DCEPCA03 - Totient Extreme"
layout: "post"
diff: 难度0
pid: SP12914
tag: []
---

# DCEPCA03 - Totient Extreme

## 题目描述

Given the value of N, you will have to find the value of H. The meaning of H is given in the following code:

 H=0;  
 For (i=1; i<=n; i++) {  
 For (j=1; j<=n; j++) {  
 H = H + totient(i) \* totient(j);  
 }  
 }

**Totient** or phi function, φ(n) is an arithmetic function that counts the number of positive integers less than or equal to n that are relatively prime to n. That is, if n is a positive integer, then φ(n) is the number of integers k in the range 1

## 输入格式

The first line contains T, the number of test cases. It is followed by T lines each containing a number N .

## 输出格式

For each line of input produce one line of output. This line contains the value of H for the corresponding N.

## 样例 #1

### 输入

```
2
3
10
```

### 输出

```
16
1024
```

