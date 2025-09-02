---
title: "DCEPC204 - Unlock it !"
layout: "post"
diff: 难度0
pid: SP10809
tag: []
---

# DCEPC204 - Unlock it !

## 题目描述

Vaibhav loves playing with numbers. To enjoy his summer holidays he decides to join the group "number players" of his school. He decides to visit the group hall. At the gate he finds a lock and a paper. The gate can only be unlocked by solving the puzzle written on the paper. Vaibhav is stuck with his puzzle, help him in solving it.  
  
Here is the puzzle description:  
  
Given a sequence F(N)  
  
F(0)=1  
  
F(1)=1  
  
F(2)=1  
  
F(n) = product of all odd primes less than or equal to n (for n<=10)  
  
F(n) = (2^(n/4)) \* F(n/5)\* F(n/10) (for n>10)

**For every fraction , a ceil value is taken for evaluation.**

 **For eg. F(11)=2^ceil(11/4) \* F(ceil(11/5)) \* F(ceil(11/10)) = 2^3 \* F(3) \* F(2) = 24**  
  
Given N. Find the max value of **(a^b)%mod** such that a and b satisfies the relation gcd(a,b) = F(N).  
  
Gcd : Greatest common divisor

## 输入格式

First line gives T, total number of testcases.  
  
Next T line gives number N

## 输出格式

For each test case, print the desired value on a new line

## 样例 #1

### 输入

```
\n1\n2\n\n
```

### 输出

```
1024
```

