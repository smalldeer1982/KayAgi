---
title: "A Tale of Two Lands"
layout: "post"
diff: 普及/提高-
pid: CF1166C
tag: []
---

# A Tale of Two Lands

## 题目描述

The legend of the foundation of Vectorland talks of two integers $ x $ and $ y $ . Centuries ago, the array king placed two markers at points $ |x| $ and $ |y| $ on the number line and conquered all the land in between (including the endpoints), which he declared to be Arrayland. Many years later, the vector king placed markers at points $ |x - y| $ and $ |x + y| $ and conquered all the land in between (including the endpoints), which he declared to be Vectorland. He did so in such a way that the land of Arrayland was completely inside (including the endpoints) the land of Vectorland.

Here $ |z| $ denotes the absolute value of $ z $ .

Now, Jose is stuck on a question of his history exam: "What are the values of $ x $ and $ y $ ?" Jose doesn't know the answer, but he believes he has narrowed the possible answers down to $ n $ integers $ a_1, a_2, \dots, a_n $ . Now, he wants to know the number of unordered pairs formed by two different elements from these $ n $ integers such that the legend could be true if $ x $ and $ y $ were equal to these two values. Note that it is possible that Jose is wrong, and that no pairs could possibly make the legend true.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of choices.

The second line contains $ n $ pairwise distinct integers $ a_1, a_2, \dots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the choices Jose is considering.

## 输出格式

Print a single integer number — the number of unordered pairs $ \{x, y\} $ formed by different numbers from Jose's choices that could make the legend true.

## 说明/提示

Consider the first sample. For the pair $ \{2, 5\} $ , the situation looks as follows, with the Arrayland markers at $ |2| = 2 $ and $ |5| = 5 $ , while the Vectorland markers are located at $ |2 - 5| = 3 $ and $ |2 + 5| = 7 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/49a110f22f2f955554c4787453bc1d910bd25e72.png)The legend is not true in this case, because the interval $ [2, 3] $ is not conquered by Vectorland. For the pair $ \{5, -3\} $ the situation looks as follows, with Arrayland consisting of the interval $ [3, 5] $ and Vectorland consisting of the interval $ [2, 8] $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/764d6883589527503a65e13f965f521d456c3d05.png)As Vectorland completely contains Arrayland, the legend is true. It can also be shown that the legend is true for the pair $ \{2, -3\} $ , for a total of two pairs.

In the second sample, the only pair is $ \{3, 6\} $ , and the situation looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/18e49be72c9003e62671bf9e2781a2db66c67ab9.png)Note that even though Arrayland and Vectorland share $ 3 $ as endpoint, we still consider Arrayland to be completely inside of Vectorland.

## 样例 #1

### 输入

```
3
2 5 -3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2
3 6

```

### 输出

```
1

```

