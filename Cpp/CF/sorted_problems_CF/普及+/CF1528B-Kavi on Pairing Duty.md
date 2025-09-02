---
title: "Kavi on Pairing Duty"
layout: "post"
diff: 普及+/提高
pid: CF1528B
tag: []
---

# Kavi on Pairing Duty

## 题目描述

Kavi has $ 2n $ points lying on the $ OX $ axis, $ i $ -th of which is located at $ x = i $ .

Kavi considers all ways to split these $ 2n $ points into $ n $ pairs. Among those, he is interested in good pairings, which are defined as follows:

Consider $ n $ segments with ends at the points in correspondent pairs. The pairing is called good, if for every $ 2 $ different segments $ A $ and $ B $ among those, at least one of the following holds:

- One of the segments $ A $ and $ B $ lies completely inside the other.
- $ A $ and $ B $ have the same length.

Consider the following example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/41a58a6a051949b924acfc162dd6465703f68210.png) $ A $ is a good pairing since the red segment lies completely inside the blue segment.

 $ B $ is a good pairing since the red and the blue segment have the same length.

 $ C $ is not a good pairing since none of the red or blue segments lies inside the other, neither do they have the same size.

Kavi is interested in the number of good pairings, so he wants you to find it for him. As the result can be large, find this number modulo $ 998244353 $ .

Two pairings are called different, if some two points are in one pair in some pairing and in different pairs in another.

## 输入格式

The single line of the input contains a single integer $ n $ $ (1\le n \le 10^6) $ .

## 输出格式

Print the number of good pairings modulo $ 998244353 $ .

## 说明/提示

The good pairings for the second example are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/26cefe71c208095e0e610c498701d052b950b5a2.png)In the third example, the good pairings are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/4bfe3f3beac587d75fee5d30f6490c2823b90e1d.png)

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
```

### 输出

```
6
```

## 样例 #4

### 输入

```
100
```

### 输出

```
688750769
```

