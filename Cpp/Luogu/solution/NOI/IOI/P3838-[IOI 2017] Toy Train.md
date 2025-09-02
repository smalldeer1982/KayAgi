# [IOI 2017] Toy Train

## 题目背景

### 由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。

## 题目描述

Arezou 和她的兄弟 Borzou 是双胞胎。他们收到的生日礼物是一套好玩的玩具火车。他们用它建了一下 $n$ 个车站和 $m$ 段单向轨道的铁路系统。这些车站的编号是从 $0$ 到 $n-1$。每段轨道都始于某一车站，然后终于同一车站或其他车站。每个车站至少会有一段轨道以它为起点。

其中有些车站是充电车站。无论何时，如果火车抵达某个充电车站。无论何时，如果火车抵达某个充电车站，它都会被充到满电。满电火车拥有足够的动力连续地试过 $n$ 段轨道，但是如果不再充电的话，在即将进入第 $n+1$ 段轨道时它就会因电已用光而停车。

每个车站都有一个轨道开关，可以扳向任一以该车站为起点的轨道。火车从某个车站驶出时，驶向的正是该车站的开关所扳向的轨道。

这对双胞胎打算用他们的火车玩个游戏。他们已经分完了所有的车站：每个车站要么归 Arezou，要么归 Borzou。游戏里面只有一列火车。游戏开始时，这列火车停在车站 $s$ ，并且充满了电。为启动游戏，车站 $s$ 的拥有者把车站 $s$ 的开关扳向某个以 $s$ 为起点的轨道。随后他们启动火车，火车也就开始沿着轨道行驶。无论何时，在火车首次进入某一车站时，该车站的拥有者都要扳定车站开关。开关一旦扳定，它就会保持状态不变直到游戏结束。因此，火车如果开到了一个曾经进过的车站，就会沿着与之前相同的轨道开出该车站。

由于车站数量是有限的，火车的行驶最终都会落入某个环路。环路是指一系列**不同**的车站 $c_0,c_1,\cdots ,c_{k-1}$，其中火车在离开车站 $c_i\ \ (0\leqslant i < k-1)$ 后驶上连向车站 $c_{i+1}$ 的轨道，在离开车站 $c_{k-1}$ 后驶上连向车站 $c_0$ 的轨道。一个环路可能只包括一个车站（此时 $k=1$），即火车从车站 $c_0$ 驶出后又驶上了连向车站 $c_0$ 的轨道。

如果火车能够连续行驶跑完，Arezou 就赢了。否则火车最后会把电用光而停车，这样 Borzou 就赢了。换句话说，如果 $c_0,c_1,\cdots ,c_{k-1}$中至少有一个充电车站，且使得火车能够不断地充电而沿着环路跑个没完，Arezou 赢。否则，它就会最终把电用光（有可能是在沿着环路跑好几圈后），Borzou 赢。

现在给你一个这样的铁路系统。Arezou 和 Borzou将会玩 $n$ 轮游戏。其中在第 $s$ 轮游戏中（$0\leqslant s \leqslant n-1$），火车最初停在车站 $s$ 上。你的任务是，对每一轮游戏，判断是否无论 Borzou 怎么玩，Arezou 都必胜。

## 实现细节

你需要实现下面的函数

(C++) `std::vector who_wins(std::vector<int> a, std::vector<int> r, std::vector<int> u, std::vector<int> v)`

(Java) `int[] who_wins(int[] a, int[] r, int[] u, int[] v)`

- $a$：长度为 $n$ 的数组。如果 Arezou 拥有车站 $i$，则 $a_i=1$；否则 Borzou 拥有车站 $i$，且 $a_i=0$。

- $r$：长度为$n$的数组。如果车站$i$是充电车站，则$r[i]=1$。否则$r[i]=0$。

- $u$ 和 $v$：长度为 $m$ 的数组。对于所有 $0\leqslant i \leqslant m-1$，存在某一单向轨道，其起点为 $u_i$，终点为 $v_i$。

- 该函数需要返回一个长度为 $n$ 的数组  $w$。对于每个 $0\leqslant i \leqslant n-1$，如果在火车最初停在车站 $i$ 的游戏中，不管 Borzou 怎么玩，Arezou 都能赢，则 $w_i$ 的值应为 $1$。否则 $w_i$ 的值应为 $0$。


## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/pic/6727.png) 

- 这里有 $2$ 个车站。Borzou 拥有充电车站 $1$。Arezou拥有充电车站 $1$，但是它不是充电车站。

- 这里有 $4$ 段轨道 $(0,0),(0,1),(1,0)$ 和 $(1,1)$，其中 $(i,j)$ 表示一个以车站 $i$ 为起点、车站$j$为终点的单向轨道。

- 考虑火车最初停在车站 $0$ 的游戏。如果 Borzou 将车站 $0$ 的开关扳向轨道 $(0,0)$，那么火车就会沿着这个环形轨道绕个没完（注意，车站 $0$ 是一个充电车站）。在这种情况下，Arezou 赢。否则，如果 Borzou 把车站 $0$ 的开关扳向轨道 $(0,1)$，Arezou 可以把车站 $1$ 的开关扳向轨道 $(1,0)$。这样的话，火车将会在两个车站之间绕个不停。Arezou 还是会赢，因为车站$0$是充电车站，火车将跑个没完。因此，无论 Borzou 怎么玩，Arezou 都会赢。

- 根据类似的逻辑，在火车最初停在车站 $1$ 的游戏中，无论 Borzou 怎么玩，Arezou 也都会赢。因此，函数应当返回 $[1,1]$。


## 数据范围和限制

- $1\leqslant n \leqslant 5000$
- $n \leqslant m \leqslant 20000$
- 至少会有一个充电车站。
- 每个车站至少会有一段轨道以它为起点。
- 可能会有某个轨道的起点和终点是相同的（即 $u_i=v_i$）。
- 所有轨道两两不同。也就是说，不存在这样的两个下标 $i$ 和 $j$（$0\leqslant i < j \leqslant m-1$），使得 $u_i=u_j$ 且 $v_i=v_j$。
- 对于所有 $0\leqslant i \leqslant m-1$，都有 $0\leqslant u_i,v_i \leqslant n-1$。

## 子任务

1. ($5$ 分) 对于所有 $0 \leqslant i \leqslant m-1$，都有 $v_i=u_i$ 或者 $v_i=u_i+1$。
2. ($10$ 分) $n\leqslant 15$。
3. ($11$ 分) Arezou 拥有所有车站。
4. ($11$ 分) Borzou 拥有所有车站。
5. ($12$ 分) 充电车站的数量为 $1$。
6. ($51$ 分) 无任何限制。


## 样例 #1

### 输入

```
a = [0, 1]
r = [1, 0]
u = [0, 0, 1, 1]
v = [0, 1, 0, 1]```

### 输出

```
who_wins = [1, 1]```

# 题解

## 作者：Infiltrator (赞：28)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://loj.ac/problem/3118)

------------

# Solution

非常妙的一道题。

首先题目中的判定条件“走到拥有关键点的环”是一个不好判定的条件，那么考虑将问题转化变为好判定的。

将原来的操作“保留一条边其它边全部删除”变为“选择一条边走出去”，同时，将获胜条件从“走到拥有关键点的环”变为“可以无限次经过关键点”。

如果能无限次走到环上，那么就相当于之前的走到有关键点的环上，除非后手选择一条边离开环，火车将一直在环上绕圈不停的走关键点，但是如果后手选择了一条离开环的边，那他在第一次经过那个点的时候就不应该选择走上环的边，但是他走上环是因为在那个点走上环最优，所以会产生矛盾，那么转化后的问题和转化前的问题就是等价的了。

考虑“先手可以无限次走关键点”如何判定，如果先手能走无限次关键点，那么对于所有可能走到的点，先手都能迫使后手走到关键点。

即我们求出图上先手能迫使后手走上关键点的点，如果这些点是全集，则后手在这些点必须无限次的走上关键点。

如果这些点不是关键点，那么这些点的补集，一定是后手获胜，以为后手总可以不走到关键点。

同时，先手能迫使后手走上关键点的点可能不能无限次的走上，当且仅当后手在这些点可以进入之前求过的后手必胜的点集。

那么我们发现先手可能获胜的点集又缩小了，继续在这个缩小后的的点集上搜出先手可能获胜的点集，直到满足该点集就是全集的条件，那么剩下的就是先手必胜的点集。

由于每次迭代总会使先手可能获胜的点集变小，所以最多迭代$O(n)$次，每次时间复杂度$O(n + m)$，总体最坏是$O(n ^ 2 + nm)$，可以通过本题。

------------

# Code

```cpp
#include "train.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 5000;

int vis[N + 50], res;

vector<int> edge1[N + 50], edge2[N + 50];

vector<int> Get(vector<int> a, vector<int> res, vector<int> r, int typ)
{
    int n = a.size();
    memset(vis, 0, sizeof(vis));
    vector<int> ans(N + 50), deg(N + 50);
    queue<int> q;
    for (int i = 0; i < n; i++) if (r[i] && res[i]) q.push(i), ans[i] = 1;
    for (int i = 0; i < n; i++) for (int j = 0; j < edge1[i].size(); j++) if (res[edge1[i][j]]) if (typ ^ a[i]) deg[i]++; else deg[i] = 1;
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        for (vector<int>::iterator it = edge2[u].begin(); it != edge2[u].end(); it++)
        {   
            int v = *it;
            if (!ans[v] && res[v])
            {
                deg[v]--;
                if (!deg[v]) ans[v] = 1, q.push(v);
            }
        }
    }
    return ans;
}

vector<int> who_wins(vector<int>a, vector<int>r, vector<int>u, vector<int>v)
{
    int n = a.size(), m = u.size();
    vector<int> res(N + 50);
    for (int i = 0; i < n; i++) res[i] = 1;
    for (int i = 0; i < m; i++) edge1[u[i]].push_back(v[i]), edge2[v[i]].push_back(u[i]);
    while (1)
    {
        int flag = 1;
        vector<int> fa = Get(a, res, r, 1);
        for (int i = 0; i < n; i++)
            if (!fa[i] && res[i])
            {
                flag = 0;
                break;
            }
        if (flag) return res;
        for (int i = 0; i < n; i++) fa[i] ^= 1;
        vector<int> fb = Get(a, res, fa, 0);
        for (int i = 0; i < n; i++) if (fb[i]) res[i] = 0;
    }
    return res;
}
```

---

