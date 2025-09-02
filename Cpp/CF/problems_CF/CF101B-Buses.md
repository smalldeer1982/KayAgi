---
title: "Buses"
layout: "post"
diff: 普及+/提高
pid: CF101B
tag: []
---

# Buses

## 题目描述

Little boy Gerald studies at school which is quite far from his house. That's why he has to go there by bus every day. The way from home to school is represented by a segment of a straight line; the segment contains exactly $ n+1 $ bus stops. All of them are numbered with integers from $ 0 $ to $ n $ in the order in which they follow from Gerald's home. The bus stop by Gerald's home has number $ 0 $ and the bus stop by the school has number $ n $ .

There are $ m $ buses running between the house and the school: the $ i $ -th bus goes from stop $ s_{i} $ to $ t_{i} $ ( $ s_{i}&lt;t_{i} $ ), visiting all the intermediate stops in the order in which they follow on the segment. Besides, Gerald's no idiot and he wouldn't get off the bus until it is still possible to ride on it closer to the school (obviously, getting off would be completely pointless). In other words, Gerald can get on the $ i $ -th bus on any stop numbered from $ s_{i} $ to $ t_{i}-1 $ inclusive, but he can get off the $ i $ -th bus only on the bus stop $ t_{i} $ .

Gerald can't walk between the bus stops and he also can't move in the direction from the school to the house.

Gerald wants to know how many ways he has to get from home to school. Tell him this number. Two ways are considered different if Gerald crosses some segment between the stops on different buses. As the number of ways can be too much, find the remainder of a division of this number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains two space-separated integers: $ n $ and $ m $ ( $ 1<=n<=10^{9},0<=m<=10^{5} $ ). Then follow $ m $ lines each containing two integers $ s_{i},t_{i} $ . They are the numbers of starting stops and end stops of the buses ( $ 0<=s_{i}&lt;t_{i}<=n $ ).

## 输出格式

Print the only number — the number of ways to get to the school modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The first test has the only variant to get to school: first on bus number one to the bus stop number one; then on bus number two to the bus stop number two.

In the second test no bus goes to the third bus stop, where the school is positioned. Thus, the correct answer is $ 0 $ .

In the third test Gerald can either get or not on any of the first four buses to get closer to the school. Thus, the correct answer is $ 2^{4}=16 $ .

## 样例 #1

### 输入

```
2 2
0 1
1 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 2
0 1
1 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 5
0 1
0 2
0 3
0 4
0 5

```

### 输出

```
16

```

