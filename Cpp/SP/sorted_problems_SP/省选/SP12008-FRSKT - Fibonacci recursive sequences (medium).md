---
title: "FRSKT - Fibonacci recursive sequences (medium)"
layout: "post"
diff: 省选/NOI-
pid: SP12008
tag: []
---

# FRSKT - Fibonacci recursive sequences (medium)

## 题目描述

Let FIB the Fibonacci function :  
 FIB(0)=0 ; FIB(1)=1  
 and  
 for N>=2 FIB(N) = FIB(N-1) + FIB(N-2)

Example : we have FIB(6)=8, and FIB(8)=21.

Let F(K, N) a new function:   
 F(0, N) = N for all integers N.  
 F(K, N) = F(K-1, FIB(N) ) for K>0 and all integers N.

Example : F(2, 6) = F(1, FIB(6) ) = F(0, FIB( FIB(6) ) ) = FIB( FIB(6) ) = FIB(8) = 21

## 输入格式

The input begins with the number T of test cases in a single line.  
 In each of the next T lines there are three integers: K, N, M.

## 输出格式

For each test case, print F(K, N),  
 as the answer could not fit in a 64bit container,  
 give your answer modulo M.

## 样例 #1

### 输入

```
3
4 5 1000
3 4 1000
2 6 1000
```

### 输出

```
5
1
21
```

