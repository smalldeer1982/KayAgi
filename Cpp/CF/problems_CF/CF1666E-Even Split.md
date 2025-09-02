---
title: "Even Split"
layout: "post"
diff: 提高+/省选-
pid: CF1666E
tag: []
---

# Even Split

## 题目描述

A revolution has recently happened in Segmentland. The new government is committed to equality, and they hired you to help with land redistribution in the country.

Segmentland is a segment of length $ l $ kilometers, with the capital in one of its ends. There are $ n $ citizens in Segmentland, the home of $ i $ -th citizen is located at the point $ a_i $ kilometers from the capital. No two homes are located at the same point. Each citizen should receive a segment of positive length with ends at integer distances from the capital that contains her home. The union of these segments should be the whole of Segmentland, and they should not have common points besides their ends. To ensure equality, the difference between the lengths of the longest and the shortest segments should be as small as possible.

## 输入格式

The first line of the input contains two integers $ l $ and $ n $ ( $ 2 \leq l \leq 10^9; 1 \leq n \leq 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 < a_1 < a_2 < \dots < a_n < l $ ).

## 输出格式

Output $ n $ pairs of numbers $ s_i, f_i $ ( $ 0 \leq s_i < f_i \leq l $ ), one pair per line. The pair on $ i $ -th line denotes the ends of the $ [s_i, f_i] $ segment that $ i $ -th citizen receives.

If there are many possible arrangements with the same difference between the lengths of the longest and the shortest segments, you can output any of them.

## 说明/提示

In the first example, it is possible to make all segments equal. Viva la revolucion!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666E/ebc3505f8c3c8786f0534e1e2096e45f0a6d83b4.png)In the second example, citizens live close to the capital, so the length of the shortest segment is 2 and the length of the longest segment is 8.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666E/f5172aa3d9343b9ef6923515224c875f543253cd.png)

## 样例 #1

### 输入

```
6 3
1 3 5
```

### 输出

```
0 2
2 4
4 6
```

## 样例 #2

### 输入

```
10 2
1 2
```

### 输出

```
0 2
2 10
```

