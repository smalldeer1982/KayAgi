---
title: "Spit Problem"
layout: "post"
diff: 入门
pid: CF29A
tag: ['模拟', '枚举', '排序']
---

# Spit Problem

## 题目描述

In a Berland's zoo there is an enclosure with camels. It is known that camels like to spit. Bob watched these interesting animals for the whole day and registered in his notepad where each animal spitted. Now he wants to know if in the zoo there are two camels, which spitted at each other. Help him to solve this task.

The trajectory of a camel's spit is an arc, i.e. if the camel in position $ x $ spits $ d $ meters right, he can hit only the camel in position $ x+d $ , if such a camel exists.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the amount of camels in the zoo. Each of the following $ n $ lines contains two integers $ x_{i} $ and $ d_{i} $ ( $ -10^{4}<=x_{i}<=10^{4},1<=|d_{i}|<=2·10^{4} $ ) — records in Bob's notepad. $ x_{i} $ is a position of the $ i $ -th camel, and $ d_{i} $ is a distance at which the $ i $ -th camel spitted. Positive values of $ d_{i} $ correspond to the spits right, negative values correspond to the spits left. No two camels may stand in the same position.

## 输出格式

If there are two camels, which spitted at each other, output YES. Otherwise, output NO.

## 样例 #1

### 输入

```
2
0 1
1 -1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
0 1
1 1
2 -2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
2 -10
3 10
0 5
5 -5
10 1

```

### 输出

```
YES

```

