---
title: "GCDS - Sabbir and gcd problem"
layout: "post"
diff: 普及+/提高
pid: SP30919
tag: []
---

# GCDS - Sabbir and gcd problem

## 题目描述

Sabbir is a little boy. He loves math very much. one day his friend taskin gave him a very hard task. taskin gave him _**n**_ numbers _**a $ _{1} $ ,a $ _{2} $ ,a $ _{3} $ ,......a $ _{n} $**_

taskin asked for a minimum integer number _**x**_ (**x > 1**) such that _**gcd(x,a $ _{1} $ ) = 1, gcd(x,a $ _{2} $ ) = 1, ...... gcd(x,a $ _{n} $ ) = 1**_,

in other words you have to find a minimum integer _**_x_ ( x > 1 )**_ such that

[**![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP30919/9a61eb88995ea804d556f658307451f21ac90d9b.png)&space;=&space;1 "\forall i ,\ i\epsilon [1....n] ,\ gcd(x,a_{i}) = 1")**](https://www.codecogs.com/eqnedit.php?latex=\forall&space;i&space;,\&space;i\epsilon&space;[1....n]&space;,\&space;gcd(x,a_{i})&space;=&space;1)

**Note:** **gcd is greatest common divisor**

## 输入格式

In the first line there will be an integer **T ,** denoting the number of test cases,

each test case is consists of 2 lines..

in the first line there will be **n ,** denoting the number of integers and next line contains **n** space separated integers **$a _ 1, a _ 2, \cdots, a _ n$**

[![](https://latex.codecogs.com/gif.latex?1&space;\leq&space;T&space;\leq&space;10 "1 \leq T \leq 10")](https://www.codecogs.com/eqnedit.php?latex=1&space;\leq&space;T&space;\leq&space;10)

[![](https://latex.codecogs.com/gif.latex?1&space;\leq&space;n&space;\leq&space;10^{5} "1 \leq n \leq 10^{5}")](https://www.codecogs.com/eqnedit.php?latex=1&space;\leq&space;n&space;\leq&space;10^{5})

[](https://www.codecogs.com/eqnedit.php?latex=1&space;\leq&space;n&space;\leq&space;10^{5}) [![](https://latex.codecogs.com/gif.latex?1&space;\leq&space;a_{i}&space;\leq&space;10^{7} "1 \leq a_{i} \leq 10^{7}")](https://www.codecogs.com/eqnedit.php?latex=1&space;\leq&space;a_{i}&space;\leq&space;10^{7})

## 输出格式

for every case print one integer **x** in one line .

Note: **x** should be greater than 1.

## 样例 #1

### 输入

```
3
3
5 7 25
4
1 2 3 4
1
2
```

### 输出

```
2
5
3
```

