---
title: "Polycarpus the Safecracker"
layout: "post"
diff: 提高+/省选-
pid: CF161E
tag: []
---

# Polycarpus the Safecracker

## 题目描述

Polycarpus has $ t $ safes. The password for each safe is a square matrix consisting of decimal digits '0' ... '9' (the sizes of passwords to the safes may vary). Alas, Polycarpus has forgotten all passwords, so now he has to restore them.

Polycarpus enjoys prime numbers, so when he chose the matrix passwords, he wrote a prime number in each row of each matrix. To his surprise, he found that all the matrices turned out to be symmetrical (that is, they remain the same after transposition). Now, years later, Polycarp was irritated to find out that he remembers only the prime numbers $ p_{i} $ , written in the first lines of the password matrices.

For each safe find the number of matrices which can be passwords to it.

The number of digits in $ p_{i} $ determines the number of rows and columns of the $ i $ -th matrix. One prime number can occur in several rows of the password matrix or in several matrices. The prime numbers that are written not in the first row of the matrix may have leading zeros.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1<=t<=30 $ ) — the number of safes. Next $ t $ lines contain integers $ p_{i} $ ( $ 10<=p_{i}<=99999 $ ), $ p_{i} $ is a prime number written in the first row of the password matrix for the $ i $ -th safe. All $ p_{i} $ 's are written without leading zeros.

## 输出格式

Print $ t $ numbers, the $ i $ -th of them should be the number of matrices that can be a password to the $ i $ -th safe. Print the numbers on separate lines.

## 说明/提示

Here is a possible password matrix for the second safe:

`<br></br>239<br></br>307<br></br>977<br></br>`Here is a possible password matrix for the fourth safe:

`<br></br>9001<br></br>0002<br></br>0002<br></br>1223 <br></br>`

## 样例 #1

### 输入

```
4
11
239
401
9001

```

### 输出

```
4
28
61
2834

```

