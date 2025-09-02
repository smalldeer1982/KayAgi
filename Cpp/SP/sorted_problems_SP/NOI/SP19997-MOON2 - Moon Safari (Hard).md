---
title: "MOON2 - Moon Safari (Hard)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP19997
tag: []
---

# MOON2 - Moon Safari (Hard)

## 题目描述

 [Air](http://en.wikipedia.org/wiki/Air_(French_band)) is a music duo from France. You will be told the secret of the critically acclaimed album [Moon Safari](http://en.wikipedia.org/wiki/Moon_Safari): mathematics. The goal of your new task is to compute an ethereal sum.

 ![AirSum](../../content/francky:AirSum "AirSum")Three trips on the moon are provided, [Moon](http://www.spoj.com/problems/MOON/) (easy), [Moon1](http://www.spoj.com/problems/MOON1/) (medium), [Moon2](http://www.spoj.com/problems/MOON2/) (hard) with different constraints.

## 输入格式

The first line contains an integer _T_, the number of test cases. On the next _T_ lines, you will be given three integers _N_, _a_ and _r_.

## 输出格式

Output _T_ lines, one for each test case, with _S $ _{N,a,r} $_  = sum( _a^i i^r_, for _i_ in \[_1..N_\] ). Since the answer can get very big, output it modulo 10 $ ^{9} $ +7.

## 样例 #1

### 输入

```
2
3 4 5
6 7 8
```

### 输出

```
16068
329990641
```

