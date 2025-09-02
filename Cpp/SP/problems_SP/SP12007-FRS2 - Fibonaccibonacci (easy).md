---
title: "FRS2 - Fibonaccibonacci (easy)"
layout: "post"
diff: 提高+/省选-
pid: SP12007
tag: []
---

# FRS2 - Fibonaccibonacci (easy)

## 题目描述

Leo would like to play with some really big numbers, OK...

Let FIB the Fibonacci function :  
 FIB(0)=0 ; FIB(1)=1  
 and  
 for N>=2 FIB(N) = FIB(N-1) + FIB(N-2)  
  
 Example : we have FIB(6)=8, and FIB(8)=21, so FIB(FIB(6))=21

## 输入格式

The input begins with the number T of test cases in a single line.  
 In each of the next T lines there are an integer N.

## 输出格式

For each test case, print FIB(FIB(N)) ,  
 as the answer could not fit in a 64bit container,  
 give your answer modulo 1000000007.

## 样例 #1

### 输入

```
3
0
5
6
```

### 输出

```
0
5
21
```

