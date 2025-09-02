# Cactus Not Enough

## 题目描述

There was no problem about a cactus at the NERC 2020 online round. That's a bad mistake, so judges decided to fix it. You shall not pass to the World Finals 2021 without solving a problem about a cactus!

A cactus is a connected undirected graph in which every edge lies on at most one simple cycle. Intuitively, a cactus is a generalization of a tree where some cycles are allowed. Multiedges (multiple edges between a pair of vertices) and loops (edges that connect a vertex to itself) are not allowed in a cactus.

Cher has got a cactus. She calls cactus strong if it is impossible to add an edge to it in such a way that it still remains a cactus. But Cher thinks her cactus is not strong enough. She wants to add the smallest possible number of edges to it to make it strong, i. e. to create a new cactus with the same vertices, so that the original cactus is a subgraph of the new one, and it is impossible to add another edge to it so that the graph remains a cactus. Cher hired you to do this job for her. So... it's on you!

## 样例 #1

### 输入

```
6 1
7 1 2 5 6 2 3 4
3 1
4 1 2 3 1
5 2
3 1 3 5
3 1 2 4
7 2
6 1 2 3 4 5 3
3 6 5 7
0 0```

### 输出

```
1
1 4
0
1
5 4
2
1 3
6 7```

# 题解

## 作者：qiuzx (赞：1)

## 题意

定义一个仙人掌是强的，当且仅当任意加入一条边之后这张图都不再是仙人掌。现在给定一个仙人掌，求至少加入多少条边后这张图变成一个强的仙人掌并输出方案。注意这里仙人掌不能有重边与自环。$n\le 10^5$。

## 思路

由于是仙人掌，因此我们先建出圆方树，在圆方树上考虑应该如何处理。首先需要知道什么样的仙人掌是强的。考虑加入一条边会对圆方树造成什么样的影响。我们发现若加入 $(x,y)$ 这条边，如果一个代表点双的点出现在了 $x\to y$ 在圆方树的路径上，这意味着任意一条仙人掌上 $x\to y$ 的路径都至少会经过该点双的两个点，从而一定不合法。但有一种例外情况，就是如果一个点双仅有两个点，那么这么加边不会导致这个点双变得不合法。

这样我们能够得出一个仙人掌是强的，当且仅当不存在两个点 $x,y$，使得圆方树中 $x\to y$ 的路径经过的所有点双大小都为 $2$，且 $x\to y$ 经过至少两个点双。前一个条件很好理解，后一个条件是为什么呢？因为如果 $x\to y$ 只经过一个点双，且这个点双大小为 $2$，那么本质上我们加入了一条重边，这是不合法的。

有了这个条件，考虑原问题怎么做。发现所有大小 $\ge 3$ 的点双都没有用了，因为反正我们也不能加一条跨越这个的边，而且这个点的存在与否与不会影响最终的合法性，所以可以将这些点全部删掉，形成若干个连通块。此时每个连通块都只有大小为 $2$ 的点双，也就是这些连通块形成了一棵树。而在这棵树上加一条边 $(x,y)$，可以看作覆盖了 $x\to y$ 的路径。那么一条边只能被覆盖一次，同时需要满足不存在两条首尾相连的边都没有被覆盖。容易验证满足这两个条件的一种覆盖方式就能对应一种合法连边方式。所以我们将问题转化为在树上选择尽可能少的链，要求满足每个点至多有一条邻边不在选择的链上。

这样就可以想到一个树形 dp，记 $f_{x,0/1}$ 表示 $x$ 的子树中是否存在一条边没有被选择的答案。转移时将所有儿子取出，先考虑所有儿子边都选取的情况。此时一定是两两配对会最优，因为向上的边至多只有一条，若为了这一条边舍弃了一组配对，那么也不会使答案变得更好。于是贡献容易计算。对于有一条边空着的情况，枚举这是哪一条边，计算与全选的贡献之差转移即可。由于还需要输出方案，所以再记录一下转移路径即可。复杂度线性。

---

