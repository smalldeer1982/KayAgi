---
title: "PROFIT - Maximum Profit"
layout: "post"
diff: 提高+/省选-
pid: SP1476
tag: []
---

# PROFIT - Maximum Profit

## 题目描述

CS&T, the well-known cellphone company, is going to set some new service stations among n possible ones, which are numbered 1,2,...,n. The costs of setting these stations are known as P1,P2,..,Pn. Also the company has made a survey among the cellphone users, and now they know that there are m user groups numbered 1,2,...,m, which will communicate by service station Ai and Bi, and the company can profit Ci.

Now CS&T wants to know which service stations are to be set that the company will profit most.

## 输入格式

```
T [The number of tests]
n m [n<=5000 m<=50000]
P1 P2 P3 ... Pn [Pi<=100]
A1 B1 C1 
A2 B2 C2
...
Am Bm Cm [1<=Ai,Bi<=n, Ci<=100]
[other tests]
At least 80% of the tests satisfy that n<=200, m<=1000.
```

## 输出格式

```
MaximumProfit
[other tests]
```

## 样例 #1

### 输入

```
1
5 5
1 2 3 4 5
1 2 3
2 3 4
1 3 3
1 4 2
4 5 3
```

### 输出

```
4
Hints:
The service stations to be set are 1,2,3.
```

