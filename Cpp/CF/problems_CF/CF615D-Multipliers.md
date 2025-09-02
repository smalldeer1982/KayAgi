---
title: "Multipliers"
layout: "post"
diff: 提高+/省选-
pid: CF615D
tag: []
---

# Multipliers

## 题目描述

Ayrat has number $ n $ , represented as it's prime factorization $ p_{i} $ of size $ m $ , i.e. $ n=p_{1}·p_{2}·...·p_{m} $ . Ayrat got secret information that that the product of all divisors of $ n $ taken modulo $ 10^{9}+7 $ is the password to the secret data base. Now he wants to calculate this value.

## 输入格式

The first line of the input contains a single integer $ m $ ( $ 1<=m<=200000 $ ) — the number of primes in factorization of $ n $ .

The second line contains $ m $ primes numbers $ p_{i} $ ( $ 2<=p_{i}<=200000 $ ).

## 输出格式

Print one integer — the product of all divisors of $ n $ modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample $ n=2·3=6 $ . The divisors of $ 6 $ are $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ , their product is equal to $ 1·2·3·6=36 $ .

In the second sample $ 2·3·2=12 $ . The divisors of $ 12 $ are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 6 $ and $ 12 $ . $ 1·2·3·4·6·12=1728 $ .

## 样例 #1

### 输入

```
2
2 3

```

### 输出

```
36

```

## 样例 #2

### 输入

```
3
2 3 2

```

### 输出

```
1728

```

