# 题目信息

# [ABC266F] Well-defined Path Queries on a Namori

## 题目描述

给定一张有 $N$ 个点、$N$ 条边的简单连通无向图和 $Q$ 次询问，对于每次询问，给定 $x_i,y_i$，表示两点的编号，请你回答第 $x_i$ 个点和第 $y_i$ 个点之间是否**有且仅有**一条简单路径。

+ 什么是简单路径？

如果路径上的各顶点均不重复，则称这样的路径为简单路径。

## 说明/提示

对于 $30\%$ 的数据，$N \le 100$，$Q \le \frac{N(N-1)}{2}$；

对于 $100\%$ 的数据，$3 \le N \le 2 \times 10^5$，$1 \le u_i<v_i \le N$，$1 \le Q \le 2 \times 10^5$，$1 \le x_i < y_i \le N$，保证图没有重边或自环，且给定询问均不重复。

翻译 by @CarroT1212

## 样例 #1

### 输入

```
5
1 2
2 3
1 3
1 4
2 5
3
1 2
1 4
1 5```

### 输出

```
No
Yes
No```

## 样例 #2

### 输入

```
10
3 5
5 7
4 8
2 9
1 2
7 9
1 6
4 10
2 5
2 10
10
1 8
6 9
8 10
6 8
3 10
3 9
1 10
5 8
1 10
7 8```

### 输出

```
Yes
No
Yes
Yes
No
No
Yes
No
Yes
No```

# AI分析结果

### 题目重写
给定一张有 $N$ 个点、$N$ 条边的简单连通无向图和 $Q$ 次询问，对于每次询问，给定 $x_i,y_i$，表示两点的编号，请你回答第 $x_i$ 个点和第 $y_i$ 个点之间是否**有且仅有**一条简单路径。

+ 什么是简单路径？

如果路径上的各顶点均不重复，则称这样的路径为简单路径。

### 算法分类
图论

### 题解分析与结论
本题的核心是判断基环树中两点之间是否存在唯一的简单路径。基环树是一种特殊的图，它由一棵树加上一条边形成，且只有一个环。题解的主要思路是通过找到环，并判断两点是否在环的同一子树内。如果两点在同一子树内，则它们之间的路径唯一；否则，路径不唯一。

### 高星题解推荐

#### 题解1：igAC (4星)
**关键亮点**：
- 通过DFS找到环，并标记环上的点。
- 使用DFS遍历每棵子树，记录每个点的祖先。
- 判断两点是否在同一子树内，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
void dfs1(int x,int f){
	if(vis[x]){
		gettag(x);
		return;
	}
	vis[x]=true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		fa[y]=x;
		dfs1(y,x);
	}
}
void dfs2(int x,int f){
	if(!cir[x]) fa[x]=fa[f];
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f || cir[y]) continue;
		dfs2(y,x);
	}
}
```
**个人心得**：
- 通过DFS找到环并标记环上的点，再通过DFS遍历子树，记录每个点的祖先，最终判断两点是否在同一子树内。

#### 题解2：yinhy09 (4星)
**关键亮点**：
- 使用DFS找到环，并标记环上的点。
- 通过DFS遍历每棵子树，记录每个点的祖先。
- 判断两点是否在同一子树内，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
void dfs(ll u,ll f){
	if(found==1)return;
	fa[u]=f;
	for(int i=h[u];i;i=e[i].next){
		if(found==1)return;
		ll v=e[i].v;
		if(v==f)continue;
		if(fa[v]){
			while(u!=v){
				in.set(u);
				u=fa[u];
			}
			in.set(v);
			found=1;
			return;
		}
		else dfs(v,u);
	}
}
```
**个人心得**：
- 通过DFS找到环并标记环上的点，再通过DFS遍历子树，记录每个点的祖先，最终判断两点是否在同一子树内。

#### 题解3：Nicrobot (4星)
**关键亮点**：
- 通过DFS找到环，并标记环上的点。
- 使用DFS遍历每棵子树，记录每个点的祖先。
- 判断两点是否在同一子树内，时间复杂度为 $O(n)$。

**核心代码**：
```cpp
void dfs(ll u,ll f){
	if(found==1)return;
	fa[u]=f;
	for(int i=h[u];i;i=e[i].next){
		if(found==1)return;
		ll v=e[i].v;
		if(v==f)continue;
		if(fa[v]){
			while(u!=v){
				in.set(u);
				u=fa[u];
			}
			in.set(v);
			found=1;
			return;
		}
		else dfs(v,u);
	}
}
```
**个人心得**：
- 通过DFS找到环并标记环上的点，再通过DFS遍历子树，记录每个点的祖先，最终判断两点是否在同一子树内。

### 最优关键思路或技巧
- **找到环**：通过DFS找到基环树中的环，并标记环上的点。
- **子树遍历**：通过DFS遍历每棵子树，记录每个点的祖先。
- **判断路径唯一性**：如果两点在同一子树内，则它们之间的路径唯一；否则，路径不唯一。

### 可拓展之处
- 类似的问题可以扩展到其他类型的图，如多环图或更复杂的图结构。
- 可以进一步优化算法，减少时间复杂度或空间复杂度。

### 推荐题目
1. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P2863 [USACO06JAN]The Cow Prom S](https://www.luogu.com.cn/problem/P2863)

---
处理用时：37.59秒