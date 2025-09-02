---
title: "Symmetree"
layout: "post"
diff: 省选/NOI-
pid: CF1800G
tag: []
---

# Symmetree

## 题目描述

Kid was gifted a tree of $ n $ vertices with the root in the vertex $ 1 $ . Since he really like symmetrical objects, Kid wants to find out if this tree is symmetrical.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1800G/d38e017cff0afa58cfae306135ac70824868e32a.png) For example, the trees in the picture above are symmetrical.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1800G/c7cdf18345f431d81f3f4995e8b80d43eac66d45.png) And the trees in this picture are not symmetrical.Formally, a tree is symmetrical if there exists an order of children such that:

- The subtree of the leftmost child of the root is a mirror image of the subtree of the rightmost child;
- the subtree of the second-left child of the root is a mirror image of the subtree of the second-right child of the root;
- ...
- if the number of children of the root is odd, then the subtree of the middle child should be symmetrical.

## 输入格式

The first line of input data contains single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

The first line of each case contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

The following $ n-1 $ lines contain two integers each $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \neq v $ ) — indices of vertices connected by an edge.

It is guaranteed that the sum of $ n $ over all cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ t $ strings, each of which is the answer to the corresponding test case. As an answer, output "YES" if this tree is symmetrical, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 样例 #1

### 输入

```
6
6
1 5
1 6
1 2
2 3
2 4
7
1 5
1 3
3 6
1 4
4 7
4 2
9
1 2
2 4
2 3
3 5
1 7
7 6
7 8
8 9
10
2 9
9 10
2 3
6 7
4 3
1 2
3 8
2 5
6 5
10
3 2
8 10
9 7
4 2
8 2
2 1
4 5
6 5
5 7
1
```

### 输出

```
YES
NO
YES
NO
NO
YES
```

