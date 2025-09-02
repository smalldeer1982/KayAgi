---
title: "Brain Network (easy)"
layout: "post"
diff: 普及/提高-
pid: CF690C1
tag: []
---

# Brain Network (easy)

## 题目描述

One particularly well-known fact about zombies is that they move and think terribly slowly. While we still don't know why their movements are so sluggish, the problem of laggy thinking has been recently resolved. It turns out that the reason is not (as previously suspected) any kind of brain defect – it's the opposite! Independent researchers confirmed that the nervous system of a zombie is highly complicated – it consists of $ n $ brains (much like a cow has several stomachs). They are interconnected by brain connectors, which are veins capable of transmitting thoughts between brains. There are two important properties such a brain network should have to function properly:

1. It should be possible to exchange thoughts between any two pairs of brains (perhaps indirectly, through other brains).
2. There should be no redundant brain connectors, that is, removing any brain connector would make property 1 false.

If both properties are satisfied, we say that the nervous system is valid. Unfortunately (?), if the system is not valid, the zombie stops thinking and becomes (even more) dead. Your task is to analyze a given nervous system of a zombie and find out whether it is valid.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ) denoting the number of brains (which are conveniently numbered from $ 1 $ to $ n $ ) and the number of brain connectors in the nervous system, respectively. In the next $ m $ lines, descriptions of brain connectors follow. Every connector is given as a pair of brains $ a b $ it connects ( $ 1<=a,b<=n $ , $ a≠b $ ).

## 输出格式

The output consists of one line, containing either yes or no depending on whether the nervous system is valid.

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 1
4 1

```

### 输出

```
no

```

## 样例 #2

### 输入

```
6 5
1 2
2 3
3 4
4 5
3 6

```

### 输出

```
yes

```

