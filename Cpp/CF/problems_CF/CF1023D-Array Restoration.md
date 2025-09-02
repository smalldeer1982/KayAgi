---
title: "Array Restoration"
layout: "post"
diff: 普及+/提高
pid: CF1023D
tag: ['线段树']
---

# Array Restoration

## 题目描述

Initially there was an array $ a $ consisting of $ n $ integers. Positions in it are numbered from $ 1 $ to $ n $ .

Exactly $ q $ queries were performed on the array. During the $ i $ -th query some segment $ (l_i, r_i) $ $ (1 \le l_i \le r_i \le n) $ was selected and values of elements on positions from $ l_i $ to $ r_i $ inclusive got changed to $ i $ . The order of the queries couldn't be changed and all $ q $ queries were applied. It is also known that every position from $ 1 $ to $ n $ got covered by at least one segment.

We could have offered you the problem about checking if some given array (consisting of $ n $ integers with values from $ 1 $ to $ q $ ) can be obtained by the aforementioned queries. However, we decided that it will come too easy for you.

So the enhancement we introduced to it is the following. Some set of positions (possibly empty) in this array is selected and values of elements on these positions are set to $ 0 $ .

Your task is to check if this array can be obtained by the aforementioned queries. Also if it can be obtained then restore this array.

If there are multiple possible arrays then print any of them.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of elements of the array and the number of queries perfomed on it.

The second line contains $ n $ integer numbers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le q $ ) — the resulting array. If element at some position $ j $ is equal to $ 0 $ then the value of element at this position can be any integer from $ 1 $ to $ q $ .

## 输出格式

Print "YES" if the array $ a $ can be obtained by performing $ q $ queries. Segments $ (l_i, r_i) $ $ (1 \le l_i \le r_i \le n) $ are chosen separately for each query. Every position from $ 1 $ to $ n $ should be covered by at least one segment.

Otherwise print "NO".

If some array can be obtained then print $ n $ integers on the second line — the $ i $ -th number should be equal to the $ i $ -th element of the resulting array and should have value from $ 1 $ to $ q $ . This array should be obtainable by performing exactly $ q $ queries.

If there are multiple possible arrays then print any of them.

## 说明/提示

In the first example you can also replace $ 0 $ with $ 1 $ but not with $ 3 $ .

In the second example it doesn't really matter what segments to choose until query $ 10 $ when the segment is $ (1, 3) $ .

The third example showcases the fact that the order of queries can't be changed, you can't firstly set $ (1, 3) $ to $ 6 $ and after that change $ (2, 2) $ to $ 5 $ . The segment of $ 5 $ should be applied before segment of $ 6 $ .

There is a lot of correct resulting arrays for the fourth example.

## 样例 #1

### 输入

```
4 3
1 0 2 3

```

### 输出

```
YES
1 2 2 3

```

## 样例 #2

### 输入

```
3 10
10 10 10

```

### 输出

```
YES
10 10 10 

```

## 样例 #3

### 输入

```
5 6
6 5 6 2 2

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
3 5
0 0 0

```

### 输出

```
YES
5 4 2

```

