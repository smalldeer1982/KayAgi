---
title: "Milutin's Plums"
layout: "post"
diff: 省选/NOI-
pid: CF1423M
tag: []
---

# Milutin's Plums

## 题目描述

As you all know, the plum harvesting season is on! Little Milutin had his plums planted in an orchard that can be represented as an $ n $ by $ m $ matrix. While he was harvesting, he wrote the heights of all trees in a matrix of dimensions $ n $ by $ m $ .

At night, when he has spare time, he likes to perform various statistics on his trees. This time, he is curious to find out the height of his lowest tree. So far, he has discovered some interesting properties of his orchard. There is one particular property that he thinks is useful for finding the tree with the smallest heigh.

Formally, let $ L(i) $ be the leftmost tree with the smallest height in the $ i $ -th row of his orchard. He knows that $ L(i) \le L(i+1) $ for all $ 1 \le i \le n - 1 $ . Moreover, if he takes a submatrix induced by any subset of rows and any subset of columns, $ L(i) \le L(i+1) $ will hold for all $ 1 \le i \le n'-1 $ , where $ n' $ is the number of rows in that submatrix.

Since the season is at its peak and he is short on time, he asks you to help him find the plum tree with minimal height.

## 输入格式

This problem is interactive.

The first line of input will contain two integers $ n $ and $ m $ , representing the number of rows and the number of columns in Milutin's orchard. It is guaranteed that $ 1 \le n, m \le 10^6 $ .

The following lines will contain the answers to your queries.

## 输出格式

Once you know have found the minimum value $ r $ , you should print ! $ r $  to the standard output.

Interaction

Your code is allowed to query for an entry $ (i, j) $ of a matrix (i.e. get the height of the tree which is in the $ i $ -th row and $ j $ -th column). The query should be formatted as ? $ i $ $ j $ , so that $ 1 \le i \le n $ and $ 1 \le j \le m $ .

You may assume that the entries of the matrix will be integers between $ 1 $ and $ 10^9 $ .

Your solution should use not more than $ \mathbf{4 \cdot (n + m)} $ queries.

This is an interactive problem. You have to use a flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

## 样例 #1

### 输入

```
5 5
13 15 10 9 15
15 17 12 11 17
10 12 7 6 12
17 19 14 13 19
16 18 13 12 18
```

### 输出

```

```

