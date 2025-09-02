---
title: "DFS Checker (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: CF2002D2
tag: ['最近公共祖先 LCA']
---

# DFS Checker (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, you are given a generic tree and the constraints on $ n $ and $ q $ are higher. You can make hacks only if both versions of the problem are solved.

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a permutation $ p_1, p_2, \ldots, p_n $ of $ [1,2,\ldots,n] $ .

You need to answer $ q $ queries. For each query, you are given two integers $ x $ , $ y $ ; you need to swap $ p_x $ and $ p_y $ and determine if $ p_1, p_2, \ldots, p_n $ is a valid DFS order $ ^\dagger $ of the given tree.

Please note that the swaps are persistent through queries.

 $ ^\dagger $ A DFS order is found by calling the following $ \texttt{dfs} $ function on the given tree.

```
<pre class="lstlisting">```
dfs_order = []<br></br><br></br>function dfs(v):<br></br>    append v to the back of dfs_order<br></br>    pick an arbitrary permutation s of children of v<br></br>    for child in s:<br></br>        dfs(child)<br></br>dfs(1)<br></br>
```
```

Note that the DFS order is not unique.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ q $ ( $ 2\le n\le 3\cdot 10^5 $ , $ 2\le q\le 10^5 $ ) — the number of vertices in the tree and the number of queries.

The next line contains $ n-1 $ integers $ a_2,a_3,\ldots,a_n $ ( $ 1\le a_i<i $ ) — the parent of each vertex in the given tree.

The next line contains $ n $ integers $ p_1,p_2,\ldots,p_n $ ( $ 1\le p_i\le n $ , all $ p_i $ are distinct) — the initial permutation $ p $ .

The next $ q $ lines each contain two integers $ x $ , $ y $ ( $ 1\le x,y\le n,x\neq y $ ) — the positions of the elements to swap in the permutation.

It is guaranteed that the sum of all $ n $ does not exceed $ 3\cdot 10^5 $ , and the sum of all $ q $ does not exceed $ 10^5 $ .

## 输出格式

For each test case, print $ q $ lines corresponding to the $ q $ queries. For each query, output $ \texttt{YES} $ if there is a DFS order that exactly equals the current permutation, and output $ \texttt{NO} $ otherwise.

You can output $ \texttt{Yes} $ and $ \texttt{No} $ in any case (for example, strings $ \texttt{yEs} $ , $ \texttt{yes} $ , $ \texttt{Yes} $ , and $ \texttt{YES} $ will be recognized as a positive response).

## 说明/提示

In the first test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,3,2],[1,2,3],[3,2,1] $ , respectively. The first two permutations are valid DFS orders; the third is not a DFS order.

In the second test case, the permutation $ p_1, p_2, \ldots, p_n $ after each modification is $ [1,2,5,4,3,6,7],[1,3,5,4,2,6,7],[1,3,7,4,2,6,5],[1,3,7,6,2,4,5] $ , respectively.

## 样例 #1

### 输入

```
3
3 3
1 1
1 2 3
2 3
3 2
1 3
7 4
1 1 2 2 3 3
1 2 3 4 5 6 7
3 5
2 5
3 7
4 6
5 4
1 1 3 4
2 3 4 5 1
5 1
4 5
3 4
2 3
```

### 输出

```
YES
YES
NO
YES
NO
NO
YES
YES
NO
NO
YES
```

