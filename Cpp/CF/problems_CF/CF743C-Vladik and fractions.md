---
title: "Vladik and fractions"
layout: "post"
diff: 普及/提高-
pid: CF743C
tag: []
---

# Vladik and fractions

## 题目描述

Vladik and Chloe decided to determine who of them is better at math. Vladik claimed that for any positive integer $ n $ he can represent fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/98fe6e67c0215dd9544c203cfb728334ac03fc69.png) as a sum of three distinct positive fractions in form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/140afc1972028e64ad54d4357592e925861bdf13.png).

Help Vladik with that, i.e for a given $ n $ find three distinct positive integers $ x $ , $ y $ and $ z $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743C/388f8aea1d0cb4eefcbda4cfdf528ffa9edb155f.png). Because Chloe can't check Vladik's answer if the numbers are large, he asks you to print numbers not exceeding $ 10^{9} $ .

If there is no such answer, print -1.

## 输入格式

The single line contains single integer $ n $ ( $ 1<=n<=10^{4} $ ).

## 输出格式

If the answer exists, print $ 3 $ distinct numbers $ x $ , $ y $ and $ z $ ( $ 1<=x,y,z<=10^{9} $ , $ x≠y $ , $ x≠z $ , $ y≠z $ ). Otherwise print -1.

If there are multiple answers, print any of them.

## 说明/提示

对于$100$%的数据满足$n \leq 10^4$  
要求答案中$x,y,z \leq 2* 10^{9}$

## 样例 #1

### 输入

```
3

```

### 输出

```
2 7 42

```

## 样例 #2

### 输入

```
7

```

### 输出

```
7 8 56

```

