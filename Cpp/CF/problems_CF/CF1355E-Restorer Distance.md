---
title: "Restorer Distance"
layout: "post"
diff: 提高+/省选-
pid: CF1355E
tag: []
---

# Restorer Distance

## 题目描述

You have to restore the wall. The wall consists of $ N $ pillars of bricks, the height of the $ i $ -th pillar is initially equal to $ h_{i} $ , the height is measured in number of bricks. After the restoration all the $ N $ pillars should have equal heights.

You are allowed the following operations:

- put a brick on top of one pillar, the cost of this operation is $ A $ ;
- remove a brick from the top of one non-empty pillar, the cost of this operation is $ R $ ;
- move a brick from the top of one non-empty pillar to the top of another pillar, the cost of this operation is $ M $ .

You cannot create additional pillars or ignore some of pre-existing pillars even if their height becomes $ 0 $ .

What is the minimal total cost of restoration, in other words, what is the minimal total cost to make all the pillars of equal height?

## 输入格式

The first line of input contains four integers $ N $ , $ A $ , $ R $ , $ M $ ( $ 1 \le N \le 10^{5} $ , $ 0 \le A, R, M \le       10^{4} $ ) — the number of pillars and the costs of operations.

The second line contains $ N $ integers $ h_{i} $ ( $ 0 \le       h_{i} \le 10^{9} $ ) — initial heights of pillars.

## 输出格式

Print one integer — the minimal cost of restoration.

## 样例 #1

### 输入

```
3 1 100 100
1 3 8
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 100 1 100
1 3 8
```

### 输出

```
9
```

## 样例 #3

### 输入

```
3 100 100 1
1 3 8
```

### 输出

```
4
```

## 样例 #4

### 输入

```
5 1 2 4
5 5 3 6 5
```

### 输出

```
4
```

## 样例 #5

### 输入

```
5 1 2 2
5 5 3 6 5
```

### 输出

```
3
```

