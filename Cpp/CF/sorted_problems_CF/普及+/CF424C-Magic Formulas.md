---
title: "Magic Formulas"
layout: "post"
diff: 普及+/提高
pid: CF424C
tag: []
---

# Magic Formulas

## 题目描述

People in the Tomskaya region like magic formulas very much. You can see some of them below.

Imagine you are given a sequence of positive integer numbers $ p_{1} $ , $ p_{2} $ , ..., $ p_{n} $ . Lets write down some magic formulas:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/bc5cfed2fc930604306d4050665204f7083b9e3e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/7e1ac84d84d4d0097a495218327d72c2379cae8d.png)Here, "mod" means the operation of taking the residue after dividing.

The expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the bitwise $ xor $ (excluding "OR") operation to integers $ x $ and $ y $ . The given operation exists in all modern programming languages. For example, in languages C++ and Java it is represented by "^", in Pascal — by "xor".

People in the Tomskaya region like magic formulas very much, but they don't like to calculate them! Therefore you are given the sequence $ p $ , calculate the value of $ Q $ .

## 输入格式

The first line of the input contains the only integer $ n $ ( $ 1<=n<=10^{6} $ ). The next line contains $ n $ integers: $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=2·10^{9} $ ).

## 输出格式

The only line of output should contain a single integer — the value of $ Q $ .

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
3

```

