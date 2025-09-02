---
title: "Paint the Tree"
layout: "post"
diff: 普及+/提高
pid: CF1975D
tag: ['贪心', '树形数据结构']
---

# Paint the Tree

## 题目描述

378QAQ has a tree with $ n $ vertices. Initially, all vertices are white.

There are two chess pieces called $ P_A $ and $ P_B $ on the tree. $ P_A $ and $ P_B $ are initially located on vertices $ a $ and $ b $ respectively. In one step, 378QAQ will do the following in order:

1. Move $ P_A $ to a neighboring vertex. If the target vertex is white, this vertex will be painted red.
2. Move $ P_B $ to a neighboring vertex. If the target vertex is colored in red, this vertex will be painted blue.

Initially, the vertex $ a $ is painted red. If $ a=b $ , the vertex $ a $ is painted blue instead. Note that both the chess pieces must be moved in each step. Two pieces can be on the same vertex at any given time.

378QAQ wants to know the minimum number of steps to paint all vertices blue.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 1\leq n\leq 2\cdot 10^5 $ ).

The second line of each test case contains two integers $ a $ and $ b $ ( $ 1\leq a,b\leq n $ ).

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimum number of steps to paint all vertices blue.

## 说明/提示

In the first test case, 378QAQ can paint all vertices blue in the following order:

- Initially, $ P_A $ is located on the vertex $ 1 $ , and $ P_B $ is located on the vertex $ 2 $ . The vertex $ 1 $ is painted red and the vertex $ 2 $ is white.
- 378QAQ moves $ P_A $ to the vertex $ 2 $ and paints it red. Then 378QAQ moves $ P_B $ to the vertex $ 1 $ and paints it blue.
- 378QAQ moves $ P_A $ to the vertex $ 1 $ . Then 378QAQ moves $ P_B $ to the vertex $ 2 $ and paints it blue.

## 样例 #1

### 输入

```
3
2
1 2
1 2
5
1 2
1 2
1 3
1 4
1 5
8
5 4
7 1
1 5
1 8
8 3
7 2
8 6
3 4
```

### 输出

```
2
8
13
```

