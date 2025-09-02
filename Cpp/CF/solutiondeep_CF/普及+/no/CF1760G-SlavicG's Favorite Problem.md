# 题目信息

# SlavicG's Favorite Problem

## 题目描述

You are given a weighted tree with $ n $ vertices. Recall that a tree is a connected graph without any cycles. A weighted tree is a tree in which each edge has a certain weight. The tree is undirected, it doesn't have a root.

Since trees bore you, you decided to challenge yourself and play a game on the given tree.

In a move, you can travel from a node to one of its neighbors (another node it has a direct edge with).

You start with a variable $ x $ which is initially equal to $ 0 $ . When you pass through edge $ i $ , $ x $ changes its value to $ x ~\mathsf{XOR}~ w_i $ (where $ w_i $ is the weight of the $ i $ -th edge).

Your task is to go from vertex $ a $ to vertex $ b $ , but you are allowed to enter node $ b $ if and only if after traveling to it, the value of $ x $ will become $ 0 $ . In other words, you can travel to node $ b $ only by using an edge $ i $ such that $ x ~\mathsf{XOR}~ w_i = 0 $ . Once you enter node $ b $ the game ends and you win.

Additionally, you can teleport at most once at any point in time to any vertex except vertex $ b $ . You can teleport from any vertex, even from $ a $ .

Answer with "YES" if you can reach vertex $ b $ from $ a $ , and "NO" otherwise.

Note that $ \mathsf{XOR} $ represents the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 说明/提示

For the first test case, we can travel from node $ 1 $ to node $ 3 $ , $ x $ changing from $ 0 $ to $ 1 $ , then we travel from node $ 3 $ to node $ 2 $ , $ x $ becoming equal to $ 3 $ . Now, we can teleport to node $ 3 $ and travel from node $ 3 $ to node $ 4 $ , reaching node $ b $ , since $ x $ became equal to $ 0 $ in the end, so we should answer "YES".

For the second test case, we have no moves, since we can't teleport to node $ b $ and the only move we have is to travel to node $ 2 $ which is impossible since $ x $ wouldn't be equal to $ 0 $ when reaching it, so we should answer "NO".

## 样例 #1

### 输入

```
3
5 1 4
1 3 1
2 3 2
4 3 3
3 5 1
2 1 2
1 2 2
6 2 3
1 2 1
2 3 1
3 4 1
4 5 3
5 6 5```

### 输出

```
YES
NO
YES```

# AI分析结果

### 题目翻译
#### SlavicG最喜欢的问题

#### 题目描述
给定一棵包含 $n$ 个顶点的带权树。回忆一下，树是一种没有任何环的连通图。带权树是指树中的每条边都有一定权重的树。这棵树是无向的，没有根节点。

由于树让你感到厌烦，你决定挑战自己，在给定的树上玩一个游戏。

在每一步中，你可以从一个节点移动到它的一个相邻节点（即与它有直接边相连的另一个节点）。

你从一个初始值为 $0$ 的变量 $x$ 开始。当你经过第 $i$ 条边时，$x$ 的值变为 $x ~\mathsf{XOR}~ w_i$（其中 $w_i$ 是第 $i$ 条边的权重）。

你的任务是从顶点 $a$ 移动到顶点 $b$，但只有当移动到顶点 $b$ 后 $x$ 的值变为 $0$ 时，你才被允许进入顶点 $b$。换句话说，只有当使用的边 $i$ 满足 $x ~\mathsf{XOR}~ w_i = 0$ 时，你才能移动到顶点 $b$。一旦你进入顶点 $b$，游戏结束，你获胜。

此外，你最多可以在任意时刻传送一次到除顶点 $b$ 以外的任意顶点。你可以从任意顶点传送，甚至可以从 $a$ 传送。

如果可以从 $a$ 到达顶点 $b$，则回答 “YES”，否则回答 “NO”。

注意，$\mathsf{XOR}$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

#### 说明/提示
对于第一个测试用例，我们可以从节点 $1$ 移动到节点 $3$，$x$ 的值从 $0$ 变为 $1$，然后从节点 $3$ 移动到节点 $2$，$x$ 的值变为 $3$。现在，我们可以传送到节点 $3$，然后从节点 $3$ 移动到节点 $4$，到达节点 $b$，因为最后 $x$ 的值变为 $0$，所以我们应该回答 “YES”。

对于第二个测试用例，我们没有可行的移动，因为我们不能传送到节点 $b$，并且唯一的移动是移动到节点 $2$，但这是不可能的，因为到达节点 $2$ 时 $x$ 的值不会等于 $0$，所以我们应该回答 “NO”。

#### 样例 #1
##### 输入
```
3
5 1 4
1 3 1
2 3 2
4 3 3
3 5 1
2 1 2
1 2 2
6 2 3
1 2 1
2 3 1
3 4 1
4 5 3
5 6 5
```
##### 输出
```
YES
NO
YES
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解的核心思路都是基于深度优先搜索（DFS）来解决问题。由于可以传送一次，最终的路径可以看作是一条从 $a$ 出发的简单路径和一条以 $b$ 结束的简单路径拼接而成，且这两条路径的边权异或和相等时，就能满足到达 $b$ 时异或和为 $0$ 的条件。

各题解的主要步骤为：
1. 预处理从 $a$ 出发的所有简单路径的边权异或和，使用 `set` 或 `map` 记录。
2. 从 $b$ 出发进行 DFS，检查是否存在某个异或和与之前记录的相等。

### 评分较高的题解
- **作者：Phartial (赞：5)，4星**
    - **关键亮点**：思路清晰，代码简洁，使用 `set` 存储从 $a$ 出发的异或和，时间复杂度为 $O(n\log n)$。
- **作者：_Remake_ (赞：3)，4星**
    - **关键亮点**：使用邻接表存储图结构，代码逻辑清晰，通过 `map` 记录从 $a$ 出发的异或和，易于理解。
- **作者：hjqhs (赞：2)，4星**
    - **关键亮点**：代码结构清晰，通过两个 DFS 函数分别处理从 $a$ 和 $b$ 出发的情况，逻辑明确。

### 关键代码及核心思想
#### 作者：Phartial
```cpp
bool D(int x, int f, int v) {
  if (x == b) {
    return !v;
  }
  m.insert(v);
  for (Pii &i : e[x]) {
    if (i.first != f) {
      if (D(i.first, x, v ^ i.second)) {
        return 1;
      }
    }
  }
  return 0;
}
bool C(int x, int f, int v) {
  if (x != b && m.find(v) != m.end()) {
    return 1;
  }
  for (Pii &i : e[x]) {
    if (i.first != f) {
      if (C(i.first, x, v ^ i.second)) {
        return 1;
      }
    }
  }
  return 0;
}
```
**核心思想**：`D` 函数从 $a$ 出发进行 DFS，将所有简单路径的异或和存入 `set` 中；`C` 函数从 $b$ 出发进行 DFS，检查是否存在某个异或和在 `set` 中。

#### 作者：_Remake_
```cpp
void dfs1(int u,int fa,int Xor)
{
	for(int r=head[u];r;r=E[r].ne)
	{
		int v=E[r].v;
		if(v==fa||v==b)
		{
			continue;
		}
		M[Xor^E[r].w]=1;
		dfs1(v,u,Xor^E[r].w);
	}
}
void dfs2(int u,int fa,int Xor)
{
	for(int r=head[u];r;r=E[r].ne)
	{
		int v=E[r].v;
		if(v==fa)
		{
			continue;
		}
		if(M[Xor^E[r].w]!=0)
		{
			exist=1;
		}
		dfs2(v,u,Xor^E[r].w);
	}
}
```
**核心思想**：`dfs1` 函数从 $a$ 出发进行 DFS，使用 `map` 记录所有简单路径的异或和；`dfs2` 函数从 $b$ 出发进行 DFS，检查是否存在某个异或和在 `map` 中。

#### 作者：hjqhs
```cpp
void dfs (int u, int fa, int k, int t) {
	if (!t && u == b) return;
	if (!t) vis[k] = 1;
	else ans |= (u != b && vis[k]);
	
	for (node i : g[u]) {
		if (i.to != fa) {
			dfs (i.to, u, k ^ i.w, t);
		}
	}
}
```
**核心思想**：通过参数 `t` 区分是从 $a$ 还是 $b$ 出发的 DFS。当 `t` 为 $0$ 时，从 $a$ 出发，将异或和存入 `map` 中；当 `t` 为 $1$ 时，从 $b$ 出发，检查是否存在某个异或和在 `map` 中。

### 可拓展之处
同类型题目可能会在树的基础上增加更多的限制条件，如边权的范围、传送次数的限制等。类似的算法套路可以应用在其他图论问题中，如判断是否存在满足特定条件的路径等。

### 洛谷相关题目推荐
1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
2. [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)
3. [P2607 [ZJOI2008] 骑士](https://www.luogu.com.cn/problem/P2607)

### 个人心得摘录与总结
- **作者：zhujiangyuan**：气人啊，没打过 CF 不知道不能用 `unordered_map`，调了我 $1$ 个小时，还好看了讨论区。
**总结**：在不同的竞赛环境中，可能会对某些标准库的使用有限制，需要注意，遇到问题可以查看讨论区获取帮助。

---
处理用时：75.32秒