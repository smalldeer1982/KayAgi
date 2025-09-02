---
title: "Recover the Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1710D
tag: ['构造']
---

# Recover the Tree

## 题目描述

Rhodoks has a tree with $ n $ vertices, but he doesn't remember its structure. The vertices are indexed from $ 1 $ to $ n $ .

A segment $ [l,r] $ ( $ 1 \leq l \leq r \leq n $ ) is good if the vertices with indices $ l $ , $ l + 1 $ , ..., $ r $ form a connected component in Rhodoks' tree. Otherwise, it is bad.

For example, if the tree is the one in the picture, then only the segment $ [3,4] $ is bad while all the other segments are good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/4fd7c832e9131d61a7e54d528e57f32ae63951c2.png)For each of the $ \frac{n(n+1)}{2} $ segments, Rhodoks remembers whether it is good or bad. Can you help him recover the tree? If there are multiple solutions, print any.

It is guaranteed that the there is at least one tree satisfying Rhodoks' description.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 1000 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2000 $ ) — the number of vertices in the tree.

Then $ n $ lines follow. The $ i $ -th of these lines contains a string $ good_i $ of length $ n+1-i $ consisting of 0 and 1. If the segment $ [i,i+j-1] $ is good then the $ j $ -th character of $ good_i $ is 1, otherwise $ j $ -th character of $ good_i $ is 0.

It is guaranteed that the there is at least one tree consistent with the given data.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2000 $ .

## 输出格式

For each test case, print $ n-1 $ lines describing the tree you recover.

The $ i $ -th line should contain two integers $ u_i $ and $ v_i $ ( $ 1 \leq u_i,v_i \leq n $ ), denoting an edge between vertices $ u_i $ and $ v_i $ .

If there are multiple solutions, print any.

## 说明/提示

The first test case is explained in the statement.

In the second test case, one possible tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/5e8ee8c45791f0ab519d49ee3373b652d0c902bd.png)In the third test case, one possible tree is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/e951e91b803c38b61a8bd56acc10554d42a981b3.png)

## 样例 #1

### 输入

```
3
4
1111
111
10
1
6
111111
11111
1111
111
11
1
12
100100000001
11100000001
1000000000
100000000
10010001
1110000
100000
10000
1001
111
10
1
```

### 输出

```
1 2
2 3
2 4
1 2
2 3
3 4
4 5
5 6
2 3
6 7
10 11
2 4
6 8
10 12
1 4
5 8
9 12
5 12
2 12
```

