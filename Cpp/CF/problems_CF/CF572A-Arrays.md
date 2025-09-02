---
title: "Arrays"
layout: "post"
diff: 普及-
pid: CF572A
tag: []
---

# Arrays

## 题目描述

You are given two arrays $ A $ and $ B $ consisting of integers, sorted in non-decreasing order. Check whether it is possible to choose $ k $ numbers in array $ A $ and choose $ m $ numbers in array $ B $ so that any number chosen in the first array is strictly less than any number chosen in the second array.

## 输入格式

The first line contains two integers $ n_{A},n_{B} $ ( $ 1<=n_{A},n_{B}<=10^{5} $ ), separated by a space — the sizes of arrays $ A $ and $ B $ , correspondingly.

The second line contains two integers $ k $ and $ m $ ( $ 1<=k<=n_{A},1<=m<=n_{B} $ ), separated by a space.

The third line contains $ n_{A} $ numbers $ a_{1},a_{2},...\ a_{nA} $ ( $ -10^{9}<=a_{1}<=a_{2}<=...<=a_{nA}<=10^{9} $ ), separated by spaces — elements of array $ A $ .

The fourth line contains $ n_{B} $ integers $ b_{1},b_{2},...\ b_{nB} $ ( $ -10^{9}<=b_{1}<=b_{2}<=...<=b_{nB}<=10^{9} $ ), separated by spaces — elements of array $ B $ .

## 输出格式

Print "YES" (without the quotes), if you can choose $ k $ numbers in array $ A $ and $ m $ numbers in array $ B $ so that any number chosen in array $ A $ was strictly less than any number chosen in array $ B $ . Otherwise, print "NO" (without the quotes).

## 说明/提示

In the first sample test you can, for example, choose numbers 1 and 2 from array $ A $ and number 3 from array $ B $ (1 < 3 and 2 < 3).

In the second sample test the only way to choose $ k $ elements in the first array and $ m $ elements in the second one is to choose all numbers in both arrays, but then not all the numbers chosen in $ A $ will be less than all the numbers chosen in $ B $ : ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF572A/8f3fbb0b873bf77b8e348f9f28840bbc5c624918.png).

## 样例 #1

### 输入

```
3 3
2 1
1 2 3
3 4 5

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 3
3 3
1 2 3
3 4 5

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5 2
3 1
1 1 1 1 1
2 2

```

### 输出

```
YES

```

