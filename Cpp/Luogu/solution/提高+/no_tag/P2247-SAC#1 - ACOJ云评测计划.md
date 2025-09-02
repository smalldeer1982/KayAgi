# SAC#1 - ACOJ云评测计划

## 题目背景

本题由世界上最蒟蒻最辣鸡最撒比的 SOL 提供。

寂月城网站是完美信息教室的官网。地址：http://191.101.11.174/mgzd 。

## 题目描述

ACOJ 的服务器简直是差到了一个令人发指的地步。于是 SAC 的出题人，也就是傻逼 SOL，不得不强制要求每一个通过下载 ACOJ 软件包而搭建的分站，都为主站启动云端评测服务。

云评测服务是由网络来连接的。这样的网络连接是双向的；但是由于地理位置等因素的限制，并不是任意两台服务器都可以直接相连。ACOJ 主站已经得到了可以直连的服务器的表，其中包含 $n$ 个分站（包括主站）以及它们的 $m$ 条连接情况，可以根据这个来分配各个分站的任务。

有一些分站的服主是 SOL 的脑残粉。他们会无条件地将他们的服务器提供给 SOL。这些 ACOJ 分站称作“好站”。但是还有一些分站的服主是 SOL 黑。他们虽然拿到了 ACOJ 的服务端，但是并不愿意为 SOL 提供资源，于是利用黑科技关掉了云服务。也就是说，虽然主站仍然认为这些站点存在，但是它们不会起到任何作用——既不能传递通信，也不能进行评测。它们称作“坏站”。

经过千辛万苦的调查，SOL 确定了 ACOJ 云评测系统中有最多 $k$ 个坏站存在，而且这 $k$ 个坏站似乎会使得 ACOJ 的云网络不再联通！大危机！

但是 SOL 太弱智了，并不能确定是哪 $k$ 个。于是他请你来帮他找出任意一组可能会使得网络不再联通的 $k$ 个站点，以便加强防范。


## 说明/提示

对于 $20\%$ 的数据，$n \le 15$；

对于另外 $20\%$ 的数据，$n \le 100$，$k=1$；

对于另外 $20\%$ 的数据，$n \le 100$，$k=2$；

对于 $100\%$ 的数据，$3 \le  n\le 500$，$k \le 3$，$2\le n - k$，云网络不存在自环和重边。

## 样例 #1

### 输入

```
4 4 2
1 2
2 3
3 4
4 1```

### 输出

```
1 3```

## 样例 #2

### 输入

```
4 6 2
1 2
2 3
3 4
4 1
1 3
2 4 ```

### 输出

```
How oversuspicious you are, SOL!```

## 样例 #3

### 输入

```
4 0 2```

### 输出

```
Poor SOL!```

# 题解

## 作者：U•ェ•*U (赞：0)

这玩意，咋一篇题解都没有啊。。。那我写一篇。

## 思路
通过分析，发现此题是 $\texttt{NP}$ 问题（$
\texttt{Non-deterministic Polynomial Problem}$，非确定性多项式问题）。

> 所有非确定性问题都只能通过验证猜测来求解。

然后我们~~盲猜~~又知道，和图有关的题目一定要看数据范围，看看数据范围，$k \le 3$！说明我们可以暴力枚举每一种 $k$。

暴力枚举？其实就是这样：
```cpp
if (k == 1) {
  //xxx
} else if (k == 2) {
  //xxx
} else {
  //xxx
}
```

然后不难想到使用 $\texttt{Tarjan}$ 算法，过程如下：
1. 判断图的初始连通性。
2. $\texttt{Tarjan}$ 求割点
3. 如果初始状态下图不连通，直接输出 `Poor SOL!`。

对于每种不同的 $k$ 的值：
- $k=1$：输出一个割点。
- $k=2$：输出两个使得去掉它们后图中会存在割点的节点。
- $k=3$：输出三个使得去掉它们后图中会存在割点的节点。

## 代码

~~你还想要代码？~~

`Update On 2024-08-13`：代码参考了[这篇文章](https://blog.csdn.net/loi_imcy/article/details/53147029)。

一开始得了 $90$ 分，找了半天，你猜怎么着？`Poor SOL` 写成 `Pool SOL` 了。。。（告诉我们复制的实用性）

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 60010; // 最大顶点数量
int n, m, k; // 节点数, 边数, 参数k
int cnt_edge, head[MAXN], nxt[MAXN], to[MAXN]; // 与链式前向星相关的变量
int dfn[MAXN], mm[MAXN], cnt; //Tarjan算法相关变量
bool del[MAXN], flag[MAXN], vis[MAXN]; // 标记割点, 忽略节点, 是否访问过

void add_edge(int u, int v) {
	to[++cnt_edge] = v; // 当前边指向v
	nxt[cnt_edge] = head[u]; // 存储下一条边的ID
	head[u] = cnt_edge; // 更新头结点的起始边ID
}

int tarjan(int u, int fa) {
	int new_cnt = 0; // 记录子节点数
	dfn[u] = mm[u] = ++cnt; // 初始化dfn和mm为当前计数器值
	for (int i = head[u]; i; i = nxt[i]) { // 遍历u的所有边
		int v = to[i]; // 当前边指向的邻节点
		if (!dfn[v] && !flag[v]) { // 如果v是未访问的节点且未被忽略
			new_cnt++;// 子节点数+1
			mm[v] = tarjan(v, u); // 递归求解
			mm[u] = min(mm[u], mm[v]); // 更新mm值
			if (mm[v] >= dfn[u]) // 判断是否为割点
				del[u] = true;
		} else if (v != fa && dfn[v] < mm[u] && !flag[v])
			mm[u] = dfn[v]; // 更新mm值
	}
	if (fa == 0 && new_cnt == 1) del[u] = false; // 根节点特殊处理
	return mm[u];
}

void dfs(int u) {
	vis[u] = true; // 标记节点已访问
	for (int i = head[u]; i; i = nxt[i]) { // 遍历u的所有边
		if (!flag[to[i]] && !vis[to[i]]) //如果目标节点未被忽略且未被访问
			dfs(to[i]); // 递归访问
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v; // 输入边信息
		add_edge(u, v); // 双向边
		add_edge(v, u);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) // 检查图是否连通
		if (!vis[i]) dfs(i), ans++;
	if (ans > 1) return cout << "Poor SOL!" << endl, 0; // 如果不连通

	if (k == 1) { // 查找单个割点
		tarjan(1, 0);
		for (int i = 1; i <= n; i++) {
			if (del[i])
				return cout << i << endl, 0; // 输出割点
		}
	}
	if (k == 2) { // 查找两个节点（变成割点）
		for (int i = 1; i <= n; i++) {
			cnt = 0; //重置计数器和数组
			memset(dfn, 0, sizeof(dfn));
			memset(mm, 0, sizeof(mm));
			memset(del, 0, sizeof(del));
			flag[i] = true; // 暂时忽略节点i
			for (int j = 1; j <= n; j++) {
				if (!flag[j]) {
					tarjan(j, 0);
					break;
				}
			}
			flag[i] = false; // 恢复标记
			for (int j = 1; j <= n; j++) {
				if (j != i && del[j])
					return cout << i << " " << j << endl, 0; // 输出结果
			}
		}
	}
	if (k == 3) { // 查找三个节点（变成割点）
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				cnt = 0;
				memset(dfn, 0, sizeof(dfn));
				memset(mm, 0, sizeof(mm));
				memset(del, false, sizeof(del));
				flag[i] = true, flag[j] = true; // 暂时忽略节点i和j
				for (int k = 1; k <= n; k++) {
					if (!flag[k]) {
						tarjan(k, 0);
						break;
					}
				}
				flag[i] = false, flag[j] = false; // 恢复标记
				for (int k = 1; k <= n; k++) {
					if (k != i && k != j && del[k])return cout << i << " " << j << " " << k << endl, 0; // 输出结果
				}
			}
		}
	}
	cout << "How oversuspicious you are, SOL!" << endl; // 无解时输出
	return 0;
}
```

---

