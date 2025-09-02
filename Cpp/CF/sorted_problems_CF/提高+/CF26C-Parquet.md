---
title: "Parquet"
layout: "post"
diff: 提高+/省选-
pid: CF26C
tag: []
---

# Parquet

## 题目描述

Once Bob decided to lay a parquet floor in his living room. The living room is of size $ n×m $ metres. Bob had planks of three types: $ a $ planks $ 1×2 $ meters, $ b $ planks $ 2×1 $ meters, and $ c $ planks $ 2×2 $ meters. Help Bob find out, if it is possible to parquet the living room with such a set of planks, and if it is possible, find one of the possible ways to do so. Bob doesn't have to use all the planks.

## 输入格式

The first input line contains 5 space-separated integer numbers $ n $ , $ m $ , $ a $ , $ b $ , $ c $ ( $ 1<=n,m<=100,0<=a,b,c<=10^{4} $ ), $ n $ and $ m $ — the living room dimensions, $ a $ , $ b $ and $ c $ — amount of planks $ 1×2 $ , $ 2×1 $ и $ 2×2 $ respectively. It's not allowed to turn the planks.

## 输出格式

If it is not possible to parquet the room with such a set of planks, output IMPOSSIBLE. Otherwise output one of the possible ways to parquet the room — output $ n $ lines with $ m $ lower-case Latin letters each. Two squares with common sides should contain the same letters, if they belong to one and the same plank, and different letters otherwise. Different planks can be marked with one and the same letter (see examples). If the answer is not unique, output any.

## 样例 #1

### 输入

```
2 6 2 2 1

```

### 输出

```
aabcca
aabdda

```

## 样例 #2

### 输入

```
1 1 100 100 100

```

### 输出

```
IMPOSSIBLE

```

## 样例 #3

### 输入

```
4 4 10 10 10

```

### 输出

```
aabb
aabb
bbaa
bbaa

```

