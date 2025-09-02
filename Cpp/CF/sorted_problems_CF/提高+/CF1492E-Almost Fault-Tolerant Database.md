---
title: "Almost Fault-Tolerant Database"
layout: "post"
diff: 提高+/省选-
pid: CF1492E
tag: []
---

# Almost Fault-Tolerant Database

## 题目描述

You are storing an integer array of length $ m $ in a database. To maintain internal integrity and protect data, the database stores $ n $ copies of this array.

Unfortunately, the recent incident may have altered the stored information in every copy in the database.

It's believed, that the incident altered at most two elements in every copy. You need to recover the original array based on the current state of the database.

In case there are multiple ways to restore the array, report any. If there is no array that differs from every copy in no more than two positions, report that as well.

## 输入格式

The first line contains integers $ n $ and $ m $ ( $ 2 \le n $ ; $ 1 \le m $ ; $ n \cdot m \le 250\,000 $ ) — the number of copies and the size of the array.

Each of the following $ n $ lines describes one of the currently stored copies in the database, it consists of $ m $ integers $ s_{i, 1}, s_{i, 2}, \dots, s_{i, m} $ ( $ 1 \le s_{i, j} \le 10^9 $ ).

## 输出格式

If there is an array consistent with all given copies, print "Yes" and then the array itself. The array must have length $ m $ and contain integers between $ 1 $ and $ 10^9 $ only.

Otherwise, print "No".

If there are multiple possible arrays, print any of them.

## 说明/提示

In the first example, the array $ [1, 10, 1, 100] $ differs from first and second copies in just one position, and from the third copy in two positions.

In the second example, array $ [1, 1, 1, 1, 1, 1, 1] $ is the same as the first copy and differs from all other copies in at most two positions.

In the third example, there is no array differing in at most two positions from every database's copy.

## 样例 #1

### 输入

```
3 4
1 10 10 100
1 1 1 100
10 100 1 100
```

### 输出

```
Yes
1 10 1 100
```

## 样例 #2

### 输入

```
10 7
1 1 1 1 1 1 1
1 1 1 1 1 1 2
1 1 1 1 1 2 2
1 1 1 1 2 2 1
1 1 1 2 2 1 1
1 1 2 2 1 1 1
1 2 2 1 1 1 1
2 2 1 1 1 1 1
2 1 1 1 1 1 1
1 1 1 1 1 1 1
```

### 输出

```
Yes
1 1 1 1 1 1 1
```

## 样例 #3

### 输入

```
2 5
2 2 1 1 1
1 1 2 2 2
```

### 输出

```
No
```

