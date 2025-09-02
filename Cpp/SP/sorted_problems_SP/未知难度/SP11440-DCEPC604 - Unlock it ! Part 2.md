---
title: "DCEPC604 - Unlock it ! Part 2"
layout: "post"
diff: 难度0
pid: SP11440
tag: []
---

# DCEPC604 - Unlock it ! Part 2

## 题目描述

Now you all helped Vaibhav solve the puzzle and open the gate last time (although not  
too much help). But as soon as he opens the gate, there is another puzzle to open the front door. Let’s see whether this time you all are able to help him or not.

Fac(n) = no of zeroes in n!  
Fact(n)= Fac(n)%25+1  
  
 F(0)=1  
  
 F(1)=1  
  
 F(2)=1  
  
 F(n) = product of all odd primes less than or equal to n (for n<=10)  
  
 F(n) = 4^fact(n) \* f(n/5) \* f(n/10) (for n>10)

**For every fraction , a floor value is taken for evaluation.**

**For eg. F(11)=4^fact(11) \* F(floor(11/5)) \* F(floor(11/10)) = 4^3 \* F(2) \* F(1) = 64**  
  
Given N. Find the max value of **(a^b)%mod** such that a and b satisfies the relation gcd(a,b) = F(N).  
  
Gcd : Greatest common divisor

## 输入格式

First line gives T, total number of testcases.  
Next T line gives number N

## 输出格式

For each test case, print the desired value on a new line.

## 样例 #1

### 输入

```
\n1
2&nbsp;
```

### 输出

```
\n1024
```

