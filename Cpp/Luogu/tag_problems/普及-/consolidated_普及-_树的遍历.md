---
title: "[GESP202503 六级] 树上漫步"
layout: "post"
diff: 普及-
pid: P11962
tag: ['2025', '二分图', '树的遍历', 'GESP']
---
# [GESP202503 六级] 树上漫步
## 题目描述

小 A 有一棵 $n$ 个结点的树，这些结点依次以 $1,2,\cdots,n$ 标号。

小 A 想在这棵树上漫步。具体来说，小 A 会从树上的某个结点出发，每⼀步可以移动到与当前结点相邻的结点，并且小 A 只会在偶数步（可以是零步）后结束漫步。

现在小 A 想知道，对于树上的每个结点，从这个结点出发开始漫步，经过偶数步能结束漫步的结点有多少个（可以经过重复的节点）。
## 输入格式

第一行，一个正整数 $n$。

接下来 $n-1$ 行，每行两个整数 $u_i,v_i$，表示树上有⼀条连接结点 $u_i$ 和结点 $v_i$ 的边。
## 输出格式

一行，$n$ 个整数。第 $i$ 个整数表示从结点 $i$ 出发开始漫步，能结束漫步的结点数量。
## 样例

### 样例输入 #1
```
3
1 3
2 3
```
### 样例输出 #1
```
2 2 1
```
### 样例输入 #2
```
4
1 3
3 2
4 3
```
### 样例输出 #2
```
3 3 1 3
```
## 提示

对于 $40\%$ 的测试点，保证 $1\leq n\leq 10^3$。

对于所有测试点，保证 $1\leq n\leq 2\times 10^5$。


---

---
title: "[蓝桥杯 2025 国 Python A] 哨兵"
layout: "post"
diff: 普及-
pid: P12873
tag: ['图论', '2025', '树的遍历', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 Python A] 哨兵
## 题目背景

建议 Python 用户选择 PyPy3 提交本题。
## 题目描述

小蓝是一位国王，他的王国里有 $n$ 座城市，通过 $n-1$ 条路来连通。他想在城市中部署三组哨兵 $A$、$B$、$C$，每组哨兵部署在一个城市里面，一个城市可以部署多组哨兵。其中 $A$ 到 $B$ 的距离需要和 $A$ 到 $C$ 的距离相同。小蓝想知道 $B$ 到 $C$ 的距离最大是多少。
## 输入格式

输入的第一行包含一个正整数 $n$。

接下来 $n-1$ 行，每行包含两个正整数 $u_i, v_i$，用一个空格分隔，表示城市 $u_i$ 和城市 $v_i$ 之间有一条路。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
8
1 2
1 3
1 4
4 5
4 6
6 7
7 8
```
### 样例输出 #1
```
4
```
## 提示

**【样例说明】**

其中一种方案：$A$ 部署在 $5$，$B$ 部署在 $3$，$C$ 部署在 $7$。

**【评测用例规模与约定】**

对于 20% 的评测用例，$1 \leq n \leq 500$；

对于所有评测用例，$1 \leq n \leq 5000$，$1 \leq u_i, v_i \leq n$。


---

---
title: "[EC Final 2021] DFS Order"
layout: "post"
diff: 普及-
pid: P9872
tag: ['2021', 'O2优化', '深度优先搜索 DFS', '树的遍历', 'ICPC']
---
# [EC Final 2021] DFS Order
## 题目描述

Prof. Pang has a rooted tree which is rooted at $1$ with $n$ nodes. These $n$ nodes are numbered from $1$ to $n$.

Now he wants to start the depth-first search at the root. He wonders for each node $v$, what is the minimum and the maximum position it can appear in the $\textbf{depth-first search order}$. The depth-first search order is the order of nodes visited during the depth-first search. A node appears in the $j$-th ($1\le j\le n$) position in this order means it is visited after $j-1$ other nodes. Because sons of a node can be iterated in arbitrary order, multiple possible depth-first orders exist. Prof. Pang wants to know for each node $v$, what are the minimum value and the maximum value of $j$ such that $v$ appears in the $j$-th position.

Following is a pseudo-code for the depth-first search on a rooted tree. After its execution, $\texttt{dfs\_order}$ is the depth-first search order.

```
let dfs_order be an empty list

def dfs(vertex x):
    append x to the end of dfs_order.
    for (each son y of x): // sons can be iterated in arbitrary order.
        dfs(y)

dfs(root)
```
## 输入格式

The first line contains a single integer $T~(1 \le T \le 10^6)$ denoting the number of test cases.

For each test case, the first line contains an integer $n~(1 \le n \le 10 ^ 5)$. Each of the next $n-1$ lines contains two integers $x$ and $y$, indicating node $x$ is node $y$'s parent ($1\le x, y\le n$). These edges form a tree rooted at $1$.

It is guaranteed that the sum of $n$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, print $n$ lines. The $i$-th line contains two integers denoting the minimum and the maximum position node $i$ can appear in the depth-first search order.
## 样例

### 样例输入 #1
```
2
4
1 2
2 3
3 4
5
1 2
2 3
2 4
1 5
```
### 样例输出 #1
```
1 1
2 2
3 3
4 4
1 1
2 3
3 5
3 5
2 5
```
## 题目翻译

给定一棵以 $1$ 为根节点的树，若按**任意顺序**进行深度优先搜索，则第 $i$ 个点最小是第几个被搜到的以及最大是第几个？


---

