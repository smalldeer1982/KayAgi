---
title: "Tree Modification"
layout: "post"
diff: 提高+/省选-
pid: CF1375G
tag: []
---

# Tree Modification

## 题目描述

You are given a tree with $ n $ vertices. You are allowed to modify the structure of the tree through the following multi-step operation:

1. Choose three vertices $ a $ , $ b $ , and $ c $ such that $ b $ is adjacent to both $ a $ and $ c $ .
2. For every vertex $ d $ other than $ b $  that is adjacent to $ a $ , remove the edge connecting $ d $ and $ a $ and add the edge connecting $ d $ and $ c $ .
3. Delete the edge connecting $ a $ and $ b $ and add the edge connecting $ a $ and $ c $ .

As an example, consider the following tree:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1375G/eafeabf55552a872e419f2e9d6a1d53612765f20.png)The following diagram illustrates the sequence of steps that happen when we apply an operation to vertices $ 2 $ , $ 4 $ , and $ 5 $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1375G/c824e4b3dc28492ea8b0c323d7e50d614cefde05.png)It can be proven that after each operation, the resulting graph is still a tree.

Find the minimum number of operations that must be performed to transform the tree into a star. A star is a tree with one vertex of degree $ n - 1 $ , called its center, and $ n - 1 $ vertices of degree $ 1 $ .

## 输入格式

The first line contains an integer $ n $ ( $ 3 \le n \le 2       \cdot 10^5 $ ) — the number of vertices in the tree.

The $ i $ -th of the following $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $ ) denoting that there exists an edge connecting vertices $ u_i $ and $ v_i $ . It is guaranteed that the given edges form a tree.

## 输出格式

Print a single integer — the minimum number of operations needed to transform the tree into a star.

It can be proven that under the given constraints, it is always possible to transform the tree into a star using at most $ 10^{18} $ operations.

## 说明/提示

The first test case corresponds to the tree shown in the statement. As we have seen before, we can transform the tree into a star with center at vertex $ 5 $ by applying a single operation to vertices $ 2 $ , $ 4 $ , and $ 5 $ .

In the second test case, the given tree is already a star with the center at vertex $ 4 $ , so no operations have to be performed.

## 样例 #1

### 输入

```
6
4 5
2 6
3 2
1 2
2 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
2 4
4 1
3 4
```

### 输出

```
0
```

