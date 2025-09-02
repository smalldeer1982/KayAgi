---
title: "MATH1 - Math I"
layout: "post"
diff: 难度0
pid: SP369
tag: []
---

# MATH1 - Math I

## 题目描述

给你$n$ 个元素$a_1,a_2,a_3...a_n(0\leq a_i\leq n)$ ，这$n$ 个数的和不超过$n$ ，你的任务是找另一个序列$x_1,x_2,x_3...x_n$ （注意$x_i$ 可以为负数）满足以下要求：  
$\centerdot (x_i-x_{i+1}+a_{i+1}=0)or(x_i-x_{i+1}+a_{i+1}=1)(1\leq i\leq n-1)$   
$\centerdot (x_n-x_1+a_1=0)or(x_n-x_1+a_1=1)$   
$\centerdot|x_1|+|x_2|+|x_3|+...+|x_n|$ 最小

## 输入格式

第一行一个整数$T(T\leq 20)$ ，表示$T$ 组数据，对于每组数据：  
$\centerdot$  第一行一个整数$n$    
$\centerdot$  第二行$n$ 个整数$a_1,a_2,a_3...a_n$

## 输出格式

每组数据一行一个数为$|x_1|+|x_2|+...+|x_n|$ 

感谢@Fheiwn 提供的翻译

## 样例 #1

### 输入

```
2
4
2 1 0 0
5
0 1 2 2 0
```

### 输出

```
1
3

Output Details:
In the former case, the optimal solution is (x1=0, x2=0, x3=0, x4=-1)
In the latter case, the optimal solution is (x1=-1, x2=-1, x3=0, x4=1, x5=0)
```

