---
title: "Interesting Sections"
layout: "post"
diff: 省选/NOI-
pid: CF1609F
tag: []
---

# Interesting Sections

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609F/37581220fa7958c8fff17f022427b5b4d5e4d291.png)William has an array of non-negative numbers $ a_1, a_2, \dots, a_n $ . He wants you to find out how many segments $ l \le r $ pass the check. The check is performed in the following manner:

1. The minimum and maximum numbers are found on the segment of the array starting at $ l $ and ending at $ r $ .
2. The check is considered to be passed if the binary representation of the minimum and maximum numbers have the same number of bits equal to 1.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ), the size of array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^{18} $ ), the contents of array $ a $ .

## 输出格式

Output a single number — the total number of segments that passed the check.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
10
0 5 7 3 9 10 1 6 13 7
```

### 输出

```
18
```

