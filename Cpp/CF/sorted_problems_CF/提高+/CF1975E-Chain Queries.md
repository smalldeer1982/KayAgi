---
title: "Chain Queries"
layout: "post"
diff: 提高+/省选-
pid: CF1975E
tag: ['线段树', '树链剖分']
---

# Chain Queries

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . Initially, all vertices are colored white or black.

You are asked to perform $ q $ queries:

- "u" — toggle the color of vertex $ u $ (if it was white, change it to black and vice versa).

After each query, you should answer whether all the black vertices form a chain. That is, there exist two black vertices such that the simple path between them passes through all the black vertices and only the black vertices. Specifically, if there is only one black vertex, they form a chain. If there are no black vertices, they do not form a chain.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1\leq n,q\leq 2\cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ c_1,c_2,\ldots,c_n $ ( $ c_i \in \{ \mathtt{0}, \mathtt{1} \} $ ) — the initial color of the vertices. $ c_i $ denotes the color of vertex $ i $ where $ \mathtt{0} $ denotes the color white, and $ \mathtt{1} $ denotes the color black.

Then $ n - 1 $ lines follow, each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i,y_i \le n $ ), indicating an edge between vertices $ x_i $ and $ y_i $ . It is guaranteed that these edges form a tree.

The following $ q $ lines each contain an integer $ u_i $ ( $ 1 \le u_i \le n $ ), indicating the color of vertex $ u_i $ needs to be toggled.

It is guaranteed that the sum of $ n $ and $ q $ over all test cases respectively does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each query, output "Yes" if the black vertices form a chain, and output "No" otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the second test case, the color of the vertices are as follows:

The initial tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/d67482a066522c11f266b4eca3d7a1ef0055849d.png)The first query toggles the color of vertex $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/4a07e30139deb2cb81867b3706db8e9ec51e4318.png)The second query toggles the color of vertex $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/fd56e11f35468c4b51183822460fd341cde05e88.png)The third query toggles the color of vertex $ 2 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/f1f02d1c42e642ef8cfd2174f0e71d8955cb85ac.png)The fourth query toggles the color of vertex $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1975E/72ebf27a994a252cc8de91446a4beacafa646ddb.png)

## 样例 #1

### 输入

```
2
2 1
1 0
1 2
1
5 4
1 0 0 0 0
1 2
1 3
1 5
3 4
4
3
2
5
```

### 输出

```
No
No
Yes
Yes
No
```

## 样例 #2

### 输入

```
4
5 3
1 1 1 1 1
3 5
2 5
3 4
1 5
1
1
1
4 4
0 0 0 0
1 2
2 3
1 4
1
2
3
2
1 1
1
1
1 1
0
1
```

### 输出

```
Yes
No
Yes
Yes
Yes
Yes
No
No
Yes
```

