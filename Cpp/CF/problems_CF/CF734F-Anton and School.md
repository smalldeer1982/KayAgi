---
title: "Anton and School"
layout: "post"
diff: 省选/NOI-
pid: CF734F
tag: []
---

# Anton and School

## 题目描述

Anton goes to school, his favorite lessons are arraystudying. He usually solves all the tasks pretty fast, but this time the teacher gave him a complicated one: given two arrays $ b $ and $ c $ of length $ n $ , find array $ a $ , such that:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734F/bffe7b936d76e107bd6e7aac7baeb51f54bd3fd0.png)

where $ a and b $ means bitwise AND, while $ a or b $ means bitwise OR.

Usually Anton is good in arraystudying, but this problem is too hard, so Anton asks you to help.

## 输入格式

The first line of the input contains a single integers $ n $ ( $ 1<=n<=200000 $ ) — the size of arrays $ b $ and $ c $ .

The second line contains $ n $ integers $ b_{i} $ ( $ 0<=b_{i}<=10^{9} $ ) — elements of the array $ b $ .

Third line contains $ n $ integers $ c_{i} $ ( $ 0<=c_{i}<=10^{9} $ ) — elements of the array $ c $ .

## 输出格式

If there is no solution, print $ -1 $ .

Otherwise, the only line of the output should contain $ n $ non-negative integers $ a_{i} $ — elements of the array $ a $ . If there are multiple possible solutions, you may print any of them.

## 样例 #1

### 输入

```
4
6 8 4 4
16 22 10 10

```

### 输出

```
3 5 1 1 

```

## 样例 #2

### 输入

```
5
8 25 14 7 16
19 6 9 4 25

```

### 输出

```
-1

```

