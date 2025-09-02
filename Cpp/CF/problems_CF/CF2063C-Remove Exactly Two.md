---
title: "Remove Exactly Two"
layout: "post"
diff: 普及/提高-
pid: CF2063C
tag: []
---

# Remove Exactly Two

## 题目描述

Recently, Little John got a tree from his aunt to decorate his house. But as it seems, just one tree is not enough to decorate the entire house. Little John has an idea. Maybe he can remove a few vertices from the tree. That will turn it into more trees! Right?You are given a tree $ ^{\text{∗}} $ of $ n $ vertices. You must perform the following operation exactly twice.

- Select a vertex $ v $ ;
- Remove all edges incident to $ v $ , and also the vertex $ v $ .

Please find the maximum number of connected components after performing the operation exactly twice.

Two vertices $ x $ and $ y $ are in the same connected component if and only if there exists a path from $ x $ to $ y $ . For clarity, note that the graph with $ 0 $ vertices has $ 0 $ connected components by definition. $ ^{\text{†}} $

 $ ^{\text{∗}} $ A tree is a connected graph without cycles.

 $ ^{\text{†}} $ But is such a graph connected?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

Each of the next $ n-1 $ lines contains two integers $ u_i $ and $ v_i $ , denoting the two vertices connected by an edge ( $ 1 \le u_i,v_i \le n $ , $ u_i \neq v_i $ ). It is guaranteed that the given edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum number of connected components on a separate line.

## 说明/提示

On the first test case, removing a vertex twice will make the graph empty. By definition, the number of connected components in the graph with $ 0 $ vertices is $ 0 $ . Therefore, the answer is $ 0 $ .

On the second test case, removing two vertices $ 1 $ and $ 2 $ leaves $ 2 $ connected components. As it is impossible to make $ 3 $ connected components with $ 2 $ vertices, the answer is $ 2 $ .

On the third test case, removing two vertices $ 1 $ and $ 5 $ leaves $ 4 $ connected components, which are $ \left\{ 2,4\right\} $ , $ \left\{ 3\right\} $ , $ \left\{ 6\right\} $ , and $ \left\{ 7\right\} $ . It can be shown that it is impossible to make $ 5 $ connected components. Therefore, the answer is $ 4 $ .

## 样例 #1

### 输入

```
3
2
1 2
4
1 2
2 3
2 4
7
1 2
1 3
2 4
4 5
5 6
5 7
```

### 输出

```
0
2
4
```

