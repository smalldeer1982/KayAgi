# 题目信息

# [ABC251F] Two Spanning Trees

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_f

$ N $ 頂点 $ M $ 辺の無向グラフ $ G $ が与えられます。 $ G $ は**単純**（自己ループおよび多重辺を持たない）かつ**連結**です。

$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ無向辺 $ \lbrace\ u_i,\ v_i\ \rbrace $ です。

下記の $ 2 $ つの条件をともに満たすような $ G $ の $ 2 $ つの全域木 $ T_1,T_2 $ を $ 1 $ 組構成してください。（ $ T_1 $ と $ T_2 $ は異なる全域木である必要はありません。）

- $ T_1 $ は下記を満たす。
  
  > $ T_1 $ を頂点 $ 1 $ を根とする根付き木とみなしたとき、$ G $ の辺のうち $ T_1 $ に含まれないすべての辺 $ \lbrace\ u,\ v\ \rbrace $ について、$ u $ と $ v $ は $ T_1 $ において祖先と子孫の関係にある。
- $ T_2 $ は下記を満たす。
  
  > $ T_2 $ を頂点 $ 1 $ を根とする根付き木とみなしたとき、$ G $ の辺のうち $ T_2 $ に含まれない辺 $ \lbrace\ u,\ v\ \rbrace $ であって、$ u $ と $ v $ が $ T_2 $ において祖先と子孫の関係にあるようなものは存在しない。

ここで、「根付き木 $ T $ において頂点 $ u $ と頂点 $ v $ が祖先と子孫の関係にある」とは、「 $ T $ において $ u $ が $ v $ の祖先である」と「 $ T $ において $ v $ が $ u $ の祖先である」のうちどちらかが成り立つことをいいます。

本問題の制約下において上記の条件を満たす $ T_1 $ と $ T_2 $ は必ず存在することが示せます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min\lbrace\ 2\ \times\ 10^5,\ N(N-1)/2\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 入力はすべて整数
- 与えられるグラフは単純かつ連結

### Sample Explanation 1

上記の出力例において、$ T_1 $ は $ 5 $ 本の辺 $ \lbrace\ 1,\ 4\ \rbrace,\ \lbrace\ 4,\ 3\ \rbrace,\ \lbrace\ 5,\ 3\ \rbrace,\ \lbrace\ 4,\ 2\ \rbrace,\ \lbrace\ 6,\ 2\ \rbrace $ を持つ $ G $ の全域木です。この $ T_1 $ は問題文中の条件を満たします。実際、$ G $ の辺のうち $ T_1 $ に含まれない各辺に関して、 - 辺 $ \lbrace\ 5,\ 1\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 5 $ の祖先であり、 - 辺 $ \lbrace\ 1,\ 2\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 2 $ の祖先であり、 - 辺 $ \lbrace\ 1,\ 6\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 6 $ の祖先です。 また、$ T_2 $ は $ 5 $ 本の辺 $ \lbrace\ 1,\ 5\ \rbrace,\ \lbrace\ 5,\ 3\ \rbrace,\ \lbrace\ 1,\ 4\ \rbrace,\ \lbrace\ 2,\ 1\ \rbrace,\ \lbrace\ 1,\ 6\ \rbrace $ を持つ $ G $ の全域木です。この $ T_2 $ は問題文中の条件を満たします。実際、$ G $ の辺のうち $ T_2 $ に含まれない各辺に関して、 - 辺 $ \lbrace\ 4,\ 3\ \rbrace $ について、頂点 $ 4 $ と頂点 $ 3 $ は祖先と子孫の関係になく、 - 辺 $ \lbrace\ 2,\ 6\ \rbrace $ について、頂点 $ 2 $ と頂点 $ 6 $ は祖先と子孫の関係になく、 - 辺 $ \lbrace\ 4,\ 2\ \rbrace $ について、頂点 $ 4 $ と頂点 $ 2 $ は祖先と子孫の関係にありません。

### Sample Explanation 2

$ 3 $ 本の辺 $ \lbrace\ 1,\ 2\rbrace,\ \lbrace\ 1,\ 3\ \rbrace,\ \lbrace\ 1,\ 4\ \rbrace $ を持つ木 $ T $ が $ G $ の唯一の全域木です。 $ G $ の辺のうちこの木 $ T $ に含まれない辺は存在しないので、明らかに、$ T $ は $ T_1 $ の条件と $ T_2 $ の条件をともに満たします。

## 样例 #1

### 输入

```
6 8

5 1

4 3

1 4

3 5

1 2

2 6

1 6

4 2```

### 输出

```
1 4

4 3

5 3

4 2

6 2

1 5

5 3

1 4

2 1

1 6```

## 样例 #2

### 输入

```
4 3

3 1

1 2

1 4```

### 输出

```
1 2

1 3

1 4

1 4

1 3

1 2```

# AI分析结果

### 题目翻译
# [ABC251F] 两棵生成树

## 题目描述

给定一个包含 $N$ 个顶点和 $M$ 条边的无向图 $G$。$G$ 是**简单**的（没有自环和多重边）且**连通**的。

对于 $i = 1, 2, \ldots, M$，第 $i$ 条边是连接顶点 $u_i$ 和顶点 $v_i$ 的无向边 $\{u_i, v_i\}$。

请构造两棵生成树 $T_1$ 和 $T_2$，满足以下条件：

- $T_1$ 满足：将 $T_1$ 视为以顶点 $1$ 为根的根树时，$G$ 中所有不在 $T_1$ 中的边 $\{u, v\}$ 都满足 $u$ 和 $v$ 在 $T_1$ 中是祖先与后代的关系。
- $T_2$ 满足：将 $T_2$ 视为以顶点 $1$ 为根的根树时，$G$ 中所有不在 $T_2$ 中的边 $\{u, v\}$ 都不满足 $u$ 和 $v$ 在 $T_2$ 中是祖先与后代的关系。

### 说明/提示

#### 样例解释
样例1中，$T_1$ 和 $T_2$ 分别满足题目要求，具体边集见输出。

### 题解分析与结论

#### 综合分析
本题要求构造两棵生成树，分别满足不同的边关系条件。通过分析，可以发现：
- $T_1$ 可以通过深度优先搜索（DFS）生成，因为DFS生成的树中，非树边都是返祖边，满足祖先与后代的关系。
- $T_2$ 可以通过广度优先搜索（BFS）生成，因为BFS生成的树中，非树边连接的点不在同一层，不满足祖先与后代的关系。

#### 最优思路
- **DFS生成树**：DFS遍历时，非树边都是返祖边，满足$T_1$的条件。
- **BFS生成树**：BFS遍历时，非树边连接的点不在同一层，满足$T_2$的条件。

### 精选题解

#### 题解1：Nahida_Buer (4星)
**关键亮点**：
- 通过DFS和BFS分别生成$T_1$和$T_2$，思路清晰。
- 提供了DFS和BFS的代码实现，代码简洁易读。

**核心代码**：
```cpp
void dfs(int u){
	for(int v:h[u]){
		if(pd[(v<<1)-1])continue;
		pd[(v<<1)-1]=1;
		printf("%d %d\n",u,v);
		dfs(v);
	}
}
void bfs(){
	queue<int>q;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:h[u]){
			if(pd[v<<1])continue;
			pd[v<<1]=1;
			printf("%d %d\n",u,v);
			q.push(v);
		}
	}
}
```

#### 题解2：Pengzt (4星)
**关键亮点**：
- 通过Tarjan算法和BFS生成树，思路明确。
- 提供了DFS和BFS的代码实现，代码简洁。

**核心代码**：
```cpp
void dfs(ll u){
	for (int i = 0; i < e[u].size(); i++){
		ll v = e[u][i];
		if (vis[v]) continue;
		cout << u << " " << v << "\n";
		vis[v] = 1;
		dfs(v);
	}
}
il void bfs(ll s){
	q.push(s);vis[s] = 1;
	while (q.size()){
		ll u = q.front();q.pop();
		for (int i = 0; i < e[u].size(); i++){
			ll v = e[u][i];
			if (vis[v]) continue;
			cout << u << " " << v << "\n";
			vis[v] = 1;
			q.push(v);
		}
	}
}
```

#### 题解3：MMXIandCCXXII (4星)
**关键亮点**：
- 通过DFS和BFS分别生成$T_1$和$T_2$，思路清晰。
- 提供了DFS和BFS的代码实现，代码简洁。

**核心代码**：
```cpp
void dfs(int u){
	vis[u] = true;
	for (int i = 0; i < v[u].size(); i++){
		int j = v[u][i];
		if (vis[j]) continue;
		cout << u << " " << j << endl;
		dfs (j);
	}
}
void bfs(){
	q.push (1);
	vis[1] = true;
	while (q.size()){
		int x = q.front();
		q.pop();
		for (int i = 0; i < v[x].size(); i++){
			int j = v[x][i];
			if (vis[j]) continue;
			vis[j] = true;
			cout << x << " " << j << endl;
			q.push (j);
		}
	}
}
```

### 扩展思路
- 类似问题：生成树的其他变种，如最小生成树、最大生成树等。
- 可以进一步优化DFS和BFS的实现，减少空间复杂度。

### 推荐题目
1. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
2. [P3371 【模板】单源最短路径](https://www.luogu.com.cn/problem/P3371)
3. [P3388 【模板】割点](https://www.luogu.com.cn/problem/P3388)

---
处理用时：48.94秒