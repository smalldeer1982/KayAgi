---
title: "Village (Maximum)"
layout: "post"
diff: 省选/NOI-
pid: CF1387B2
tag: ['贪心', '树形数据结构']
---

# Village (Maximum)

## 题目描述

### 题意

[最小值版本](https://www.luogu.com.cn/problem/CF1387B1)

村里 $n$ 个房子构成了一个 $n$ 点 $n-1$ 条边的**树**结构（下标从 $1$ 开始），每条边长度均为 $1$。一开始每个房子里分别有一个村民。

现在所有村民都需要搬家（改变自己所在的点），搬家后依然需要满足每个房子里**有且只有一个**村民。也就是说，如果原本位于点 $i$ 的村民搬到了点 $v_i$，那么应当满足：

- 对于任意点 $i$，有 $i \neq v_i$。

- 对于任意两个不同的点 $i$ 与 $j$，有 $v_i \neq v_j$。

村民 $i$ 搬家的花费是点 $i$ 到点 $v_i$ 的树上距离（即树上二点间相隔的边数），总花费为所有村民花费之和。求总花费的**最大值**及其方案。

## 输入格式

第一行一个正整数 $n$，表示树的点数。

接下来 $n-1$ 行每行二整数 $a$ 和 $b$，表示树上有一条连接 $a$ 和 $b$，长度为 $1$ 的边。

## 输出格式

第一行一个整数，表示总花费的**最大值**。

第二行 $n$ 个整数 $v_1 \dots v_n$，表示搬家的方案：如果原本位于点 $i$ 的村民搬到了点 $v_i$。

输出**任意一组**合法方案即可。

## 说明/提示

- $2 \leq n \leq 10^5$

- $1 \leq a,b \leq n$

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
8
4 3 2 1
```

## 样例 #2

### 输入

```
7
4 2
5 7
3 4
6 3
1 3
4 5
```

### 输出

```
18
2 7 4 1 3 5 6
```



---

---
title: "Middle Duplication"
layout: "post"
diff: 省选/NOI-
pid: CF1623E
tag: ['贪心', '树形数据结构']
---

# Middle Duplication

## 题目描述

A binary tree of $ n $ nodes is given. Nodes of the tree are numbered from $ 1 $ to $ n $ and the root is the node $ 1 $ . Each node can have no child, only one left child, only one right child, or both children. For convenience, let's denote $ l_u $ and $ r_u $ as the left and the right child of the node $ u $ respectively, $ l_u = 0 $ if $ u $ does not have the left child, and $ r_u = 0 $ if the node $ u $ does not have the right child.

Each node has a string label, initially is a single character $ c_u $ . Let's define the string representation of the binary tree as the concatenation of the labels of the nodes in the in-order. Formally, let $ f(u) $ be the string representation of the tree rooted at the node $ u $ . $ f(u) $ is defined as follows: $ $$$ f(u) = \begin{cases} \texttt{<empty string>}, & \text{if }u = 0; \\ f(l_u) + c_u + f(r_u) & \text{otherwise}, \end{cases}  $ $  where  $ + $  denotes the string concatenation operation.</p><p>This way, the string representation of the tree is  $ f(1) $ .</p><p>For each node, we can <span class="tex-font-style-it">duplicate</span> its label <span class="tex-font-style-bf">at most once</span>, that is, assign  $ c\_u $  with  $ c\_u + c\_u $ , but only if  $ u $  is the root of the tree, or if its parent also has its label duplicated.</p><p>You are given the tree and an integer  $ k $ . What is the lexicographically smallest string representation of the tree, if we can duplicate labels of at most  $ k $  nodes?</p><p>A string  $ a $  is lexicographically smaller than a string  $ b $  if and only if one of the following holds: </p><ul> <li>  $ a $  is a prefix of  $ b $ , but  $ a \\ne b $ ; </li><li> in the first position where  $ a $  and  $ b $  differ, the string  $ a $  has a letter that appears earlier in the alphabet than the corresponding letter in  $ b$$$.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5 $ ).

The second line contains a string $ c $ of $ n $ lower-case English letters, where $ c_i $ is the initial label of the node $ i $ for $ 1 \le i \le n $ . Note that the given string $ c $ is not the initial string representation of the tree.

The $ i $ -th of the next $ n $ lines contains two integers $ l_i $ and $ r_i $ ( $ 0 \le l_i, r_i \le n $ ). If the node $ i $ does not have the left child, $ l_i = 0 $ , and if the node $ i $ does not have the right child, $ r_i = 0 $ .

It is guaranteed that the given input forms a binary tree, rooted at $ 1 $ .

## 输出格式

Print a single line, containing the lexicographically smallest string representation of the tree if at most $ k $ nodes have their labels duplicated.

## 说明/提示

The images below present the tree for the examples. The number in each node is the node number, while the subscripted letter is its label. To the right is the string representation of the tree, with each letter having the same color as the corresponding node.

Here is the tree for the first example. Here we duplicated the labels of nodes $ 1 $ and $ 3 $ . We should not duplicate the label of node $ 2 $ because it would give us the string "bbaaab", which is lexicographically greater than "baaaab".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/8e9bc3e39a0385947c6f1b7db86d59f03e67d645.png)In the second example, we can duplicate the labels of nodes $ 1 $ and $ 2 $ . Note that only duplicating the label of the root will produce a worse result than the initial string.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/dca73cc51ea6acbb902f1315cd4594d96b4d3160.png)In the third example, we should not duplicate any character at all. Even though we would want to duplicate the label of the node $ 3 $ , by duplicating it we must also duplicate the label of the node $ 2 $ , which produces a worse result.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/967abfb10aaf17f05381c2a0e362eea9288d9011.png)There is no way to produce string "darkkcyan" from a tree with the initial string representation "darkcyan" :(.

## 样例 #1

### 输入

```
4 3
abab
2 3
0 0
0 4
0 0
```

### 输出

```
baaaab
```

## 样例 #2

### 输入

```
8 2
kadracyn
2 5
3 4
0 0
0 0
6 8
0 7
0 0
0 0
```

### 输出

```
daarkkcyan
```

## 样例 #3

### 输入

```
8 3
kdaracyn
2 5
0 3
0 4
0 0
6 8
0 7
0 0
0 0
```

### 输出

```
darkcyan
```



---

