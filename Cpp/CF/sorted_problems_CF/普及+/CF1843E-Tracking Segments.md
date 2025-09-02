---
title: "Tracking Segments"
layout: "post"
diff: 普及+/提高
pid: CF1843E
tag: []
---

# Tracking Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ zeros. You are also given a set of $ m $ not necessarily different segments. Each segment is defined by two numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) and represents a subarray $ a_{l_i}, a_{l_i+1}, \dots, a_{r_i} $ of the array $ a $ .

Let's call the segment $ l_i, r_i $ beautiful if the number of ones on this segment is strictly greater than the number of zeros. For example, if $ a = [1, 0, 1, 0, 1] $ , then the segment $ [1, 5] $ is beautiful (the number of ones is $ 3 $ , the number of zeros is $ 2 $ ), but the segment $ [3, 4] $ is not is beautiful (the number of ones is $ 1 $ , the number of zeros is $ 1 $ ).

You also have $ q $ changes. For each change you are given the number $ 1 \le x \le n $ , which means that you must assign an element $ a_x $ the value $ 1 $ .

You have to find the first change after which at least one of $ m $ given segments becomes beautiful, or report that none of them is beautiful after processing all $ q $ changes.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le m \le n \le 10^5 $ ) — the size of the array $ a $ and the number of segments, respectively.

Then there are $ m $ lines consisting of two numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) —the boundaries of the segments.

The next line contains an integer $ q $ ( $ 1 \le q \le n $ ) — the number of changes.

The following $ q $ lines each contain a single integer $ x $ ( $ 1 \le x \le n $ ) — the index of the array element that needs to be set to $ 1 $ . It is guaranteed that indexes in queries are distinct.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum change number after which at least one of the segments will be beautiful, or $ -1 $ if none of the segments will be beautiful.

## 说明/提示

In the first case, after first 2 changes we won't have any beautiful segments, but after the third one on a segment $ [1; 5] $ there will be 3 ones and only 2 zeros, so the answer is 3.

In the second case, there won't be any beautiful segments.

## 样例 #1

### 输入

```
6
5 5
1 2
4 5
1 5
1 3
2 4
5
5
3
1
2
4
4 2
1 1
4 4
2
2
3
5 2
1 5
1 5
4
2
1
3
4
5 2
1 5
1 3
5
4
1
2
3
5
5 5
1 5
1 5
1 5
1 5
1 4
3
1
4
3
3 2
2 2
1 3
3
2
3
1
```

### 输出

```
3
-1
3
3
3
1
```

