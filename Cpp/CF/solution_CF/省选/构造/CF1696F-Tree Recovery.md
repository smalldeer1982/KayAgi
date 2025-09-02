# Tree Recovery

## 题目描述

给定一棵 $n$ 个节点的树，节点编号为 $1\sim n$。

树的形态是未知的，但我们知道：
* 所有边的边权都为 $1$。
* $n-1$ 行信息：
	* 第 $i$ 行信息由 $n-i$ 个以空格隔开的 $01$ 字符串组成。
	* 定义 $d(x,y)$ 为树上 $x,y$ 两点之间的距离。我们约定字符串下标从 $1$开始。
   * 对于第 $i$ 行的 第 $j$ 个字符串 $s$，$s_k=0$ 表示 $d(i,k)\neq d(i+j,k)$，$s_k=1$ 表示 $d(i,k)=d(i+j,k)$。

## 说明/提示

对于所有测试点，$t\leqslant 200$，$n\leqslant 100$。

对于每个测试点的多组数据，至多有 $2$ 组数据的 $n>50$，至多有 $5$ 组数据的 $n>20$。

## 样例 #1

### 输入

```
5
2
00
2
10
3
001 000
000
3
001 010
000
5
00000 01001 00000 01100
00000 10000 00000
00000 11010
00000```

### 输出

```
Yes
1 2
No
Yes
1 3
2 3
No
Yes
1 2
1 4
2 3
2 5```

# 题解

## 作者：老莽莽穿一切 (赞：10)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16427416.html)

---

考场一直在想神仙构造方法，实际上连最浅显的结论都没有发现。

首先关注到数据规模不大，想到通过某种方法构造完一棵树后暴力 $\mathcal O\left(n^3\right)$ 判断是否满足要求的可行性。

这题还是比较需要思想火花的，如果想不到第一步的话根本做不下去，我们可以首先发现一个结论，就是如果确定一条边存在的话，假设这条边为 $\langle x,y\rangle$，因为这条边的存在，我们已经得知 $\operatorname{dist}(x,y)=1$，则如果存在 $a_{x,z,y}=1$，则说明 $\operatorname{dist}(y,z)=\operatorname{dist}(x,y)=1$，说明边 $\langle y,z\rangle$ 也是存在的，以此类推我们可以得知图中所有的边。

其次，我们发现满足要求的树应当是唯一的，如果存在多种构造方案，即有一条边在某种方案中存在，在另一种方案中不存在，将这条边放在它不存在的方案中将形成一个环，这个环上任意相邻的两条边 $\langle x,y\rangle,\langle y,z\rangle$ 都满足 $a_{x,z,y}=1$，则任意删去一条边都会导致存在一个不满足的条件。

那么我们现在就是要找到一条在最终答案中存在的边，因为数据规模不大，所以我们可以直接暴力枚举一条以 $1$ 为端点的边，因为总有一条端点为 $1$ 的边是被包含到答案里的，所以直接枚举构造，最后判断答案是否满足要求，时间复杂度 $\mathcal O\left(n^4\right)$，实际上因为跑不满所以很快，[**代码**](https://codeforces.com/contest/1696/submission/162387377)实现不难。

---

## 作者：Felix72 (赞：2)

先思考一下构造方案难在哪里。思考后我们知道，这题的难点在于只知道等量关系而不知道点对之间距离的具体数值，导致我们的构造无从下手。反之，只要知道少量数值，就能通过这些关系推理出更多数值。

再思考一下我们想要什么数值。最终的答案是一棵树，我们就需要知道所有的边。正好，只要知道一条边，我们便可以 BFS 推出所有边。因此可以假设一条边 $(x, y)$ 存在，再推理出剩余的边，最后检验是否合法即可。复杂度是枚举的 $O(n^2)$ 乘检验的 $O(n^3)$，会超时。

但是我们只需要枚举到一条合法边就可以结束了，因此枚举 $(1, x)$，复杂度 $O(n^4)$，可以通过。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int T, n; bool mp[N][N][N];

struct edge {int x, y;}; int dis[N][N]; bool vis[N];
queue < edge > q; int edge_num;
inline void bfs(edge st)
{
	q.push(st); edge_num = 0;
	for(int i = 1; i <= n; ++i) vis[i] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			dis[i][j] = ((i == j) ? 0 : 1e9);
	vis[st.x] = vis[st.y] = true;
	while(!q.empty())
	{
		edge li = q.front(); q.pop(); ++edge_num;
		dis[li.x][li.y] = dis[li.y][li.x] = 1;
		for(int i = 1; i <= n; ++i)
		{
			if(vis[i]) continue;
			if(mp[li.x][li.y][i])
			{
				vis[i] = true;
				q.push({li.y, i});
			}
			else if(mp[li.y][li.x][i])
			{
				vis[i] = true;
				q.push({li.x, i});
			}
		}
	}
}
inline bool check()
{
	if(edge_num < n - 1) return false;
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			for(int k = 1; k <= n; ++k)
				if((dis[i][j] == dis[j][k]) != mp[i][j][k])
					return false;
	return true;
}

inline void sol()
{
	cin >> n;
	for(int i = 1; i <= n; ++i)
	{
		char c;
		for(int j = 1; j <= n; ++j)
			mp[i][j][i] = true;
		for(int j = i + 1; j <= n; ++j)
			for(int k = 1; k <= n; ++k)
				cin >> c, mp[i][k][j] = mp[j][k][i] = c - '0';
	}
	for(int i = 2; i <= n; ++i)
	{
		bfs({1, i});
		if(check())
		{
			cout << "Yes" << '\n';
			for(int j = 1; j <= n; ++j)
				for(int k = j + 1; k <= n; ++k)
					if(dis[j][k] == 1)
						cout << j << " " << k << '\n';
			return ;
		}
	}
	cout << "No" << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--) sol();
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

~~这 $O(n^3)$ 暴虐 $O(n^4)$ 标算。~~

这里拜谢 @[monstersqwq](https://www.luogu.com.cn/user/191868)。

我们预判断浅显的错误：$d(i,i)=d(i,j(\ne i))$。

其次，预处理出对于每一个 $x$ 作为根，哪些点的深度（以下记为 $dep$）相同，这里用并查集做到 $O(n^3)$，当然并查集时也可能判无解，记最后每个点为根的并查集为「等深度并查集」。

接下来是主体。

最外层循环，我们枚举 $x\in[2,n]$，表示我们钦定了存在 $(1,x)$ 这条边，接下来的任务就是 $O(n^2)$ 以内的时间构造并判断是否可行。

* * *

**结论：** 钦定了一条边存在后整棵树只有一种形态（或无解）。

**证明：** 我们从已知的边推向未知的边。设 $(x,y)$ 有边，且 $d(x,y)=d(x,z(\ne y))$，则 $(x,z)$ 有边。这样不断拓展，树就唯一。

* * * 

类似上述的证明，我们可以 $O(n^2)$ 求出树的形态。

我们枚举钦定根 $rt\in[1,n]$，然后 $O(n)$ 求出每个点的 $dep$，接下来我们只要用预处理好的等深度并查集 $O(n)$ 判断合法即可。

[已经尽力改美观但是还是很屑的代码](https://codeforces.com/contest/1696/submission/163991829)

---

## 作者：Nelofus (赞：1)

首先给出的所有限制都是三元的 $\operatorname{dis}(i, k)=\operatorname{dis}(j, k)$，这看起来就没有什么很好的处理方式，我们把这看作是对路径 $(i,k)$ 和 $(j,k)$ 的限制，对所有**无序二元组** $(u, v)$ 建一个点 $t_{(u,v)}$，对每个等于的限制连一条边 $t_{(i,k)}\sim t_{(j,k)}$，那么形成的图中，任意两个在同一个连通块中的路径长度相等，任意两个不在同一连通块中的路径长度不同。

用并查集可以简单找到每个连通块中的元素，接下来的问题是，我们知道了路径的长度等价关系，如何构造出一个树符合所有限制？我们尝试枚举一些东西来简化问题，首先枚举一个路径集合，表示这个路径集合是所有长度 $=1$ 的路径集合。

等等，这不就做完了吗？$=1$ 的路径不就是一条边吗，那么这个边集必须恰好是一棵树，再验证这棵树是否符合每个限制 $\operatorname{dis}(i,k)=\operatorname{dis}(j,k)$ 或 $\operatorname{dis}(i,k)\neq \operatorname{dis}(j,k)$ 即可。

时间复杂度 $\mathcal O(n^4+n^3\alpha(n))$

```cpp
/*
 * Copyright© 2024 Heratino & Nelofus. All rights reserved.
 * author: Heratino & Nelofus
 * Problem: 
 * Tag: 
 * Memory Limit: 
 * Time Limit: 
 * Source: 
 */

// Narcissus & どうか安寧な記憶を

#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 110;
bool eq[N][N][N];
int edgenum[N][N];

int tot;
std::pair<int, int> rev[N * N];
struct DSU {
	int fa[N * N], siz[N * N];

	inline void init(int x) {
		for (int i = 1; i <= x; i++)
			fa[i] = i, siz[i] = 1;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	inline bool merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy)
			return false;
		if (siz[fx] > siz[fy])
			std::swap(fx, fy);
		fa[fx] = fy;
		siz[fy] += siz[fx];
		return true;
	}
} SET1, ST;

std::vector<std::pair<int, int>> edges[N * N];
int dis[N][N];
std::vector<int> G[N];

void dfs(int u, int fa, int rt) {
	for (const int &v : G[u]) {
		if (v == fa)
			continue;
		dis[rt][v] = dis[rt][u] + 1;
		dfs(v, u, rt);
	}
}

bool IS_TEST3 = false;

void solve() {
	int n;
	std::cin >> n;

	tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				eq[i][j][k] = 0;

	tot = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			edgenum[j][i] = edgenum[i][j] = ++tot;
			rev[tot] = std::make_pair(i, j);
		}

	SET1.init(tot);
	for (int i = 1; i <= tot; i++)
		edges[i].clear();

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n - i; j++) {
			int p = i, q = i + j;
			std::string s;
			std::cin >> s;

			for (int k = 1; k <= n; k++)
				if (s[k - 1] == '1')
					eq[p][q][k] = eq[q][p][k] = true;
				else
					eq[p][q][k] = eq[q][p][k] = false;
		}
	}

	for (int i = 1; i <= n; i++)
		for (int k = 1; k <= n; k++)
			eq[i][i][k] = true;

	for (int i = 1; i <= n; i++)
		SET1.merge(edgenum[1][1], edgenum[i][i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++) {
				if (eq[i][j][k])
					SET1.merge(edgenum[i][k], edgenum[j][k]);
			}

	for (int i = 1; i <= tot; i++) {
		edges[SET1.find(i)].push_back(rev[i]);
	}

	for (int i = 1; i <= tot; i++) {
		if (edges[i].size() == n - 1) {
			ST.init(n);
			bool flag = true;
			for (const auto &[u, v] : edges[i]) {
				if (!ST.merge(u, v)) {
					flag = false;
					break;
				}
			}

			// 检查其他边是否限制合法
			if (flag) {
				for (int u = 1; u <= n; u++)
					G[u].clear();
				for (const auto &[u, v] : edges[i]) {
					G[u].push_back(v);
					G[v].push_back(u);
				}
				for (int u = 1; u <= n; u++) {
					dis[u][u] = 0;
					dfs(u, 0, u);
				}
				for (int i = 1; i <= n; i++)
					for (int j = 1; j <= n; j++)
						for (int k = 1; k <= n; k++)
							if (eq[i][j][k] && dis[i][k] != dis[j][k]) {
								flag = false;
								break;
							} else if (!eq[i][j][k] && dis[i][k] == dis[j][k]) {
								flag = false;
								break;
							}
			}

			if (flag) {
				std::cout << "Yes" << '\n';
				for (const auto &[u, v] : edges[i]) {
					std::cout << u << ' ' << v << '\n';
				}
				return ;
			}
		}
	}
	std::cout << "No" << '\n';
}

/* 无法忘却的记忆与苍蓝之梦 */
int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T;
	std::cin >> T;
	for (int i = 1; i <= T; i++) {
		solve();
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

要相信 `*2600` 是唐题。

刚开始想了很多神秘做法，但是限制太多太杂。对于这么多的限制，我们想的是“必要条件缩小答案范围”，然后在有能力枚举的情况下判断是否合法。

考虑钦定一个点 $u$ 与 $1$ 相连。那么 $1$ 所有直接相连的边就确定了：他们和 $u$ 到 $1$ 的距离相同。然后这样 DFS，每个点通过它的父亲确定儿子。

这样一轮复杂度是 $O(n^2)$ 建树，$O(n^3)$ 暴力 check（应该可以进一步优化，但是摆摆摆），总体复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int T,n,dis[MAXN][MAXN],vis[MAXN],flag=1;
vector<int> G[MAXN];
string flg[MAXN][MAXN];
void dfs(int u,int f) {
	vis[u]=1;
	if(f) ffor(v,1,n) if(v!=f&&flg[v][f][u]=='1') G[u].push_back(v);
	for(auto v:G[u]) {
		if(vis[v]) flag=0;
		else dfs(v,u);	
	}
	if(f) G[u].push_back(f);
	return ;
}
void get_dis(int u,int f,int anc) {
	if(f) dis[u][anc]=dis[f][anc]+1;
	for(auto v:G[u]) if(v!=f) get_dis(v,u,anc);
	return ;
}
int check(int u) {
	flag=1;
	ffor(i,1,n) G[i].clear(),vis[i]=0;
	ffor(i,2,n) if(i==u||flg[u][i][1]=='1') G[1].push_back(i);
	dfs(1,0);
	ffor(i,1,n) if(!vis[i]) return 0;
	if(!flag) return 0;
	ffor(i,1,n) get_dis(i,0,i);
	ffor(i,1,n) ffor(j,i+1,n) ffor(u,1,n) if(flg[i][j][u]-'0'!=(dis[i][u]==dis[j][u])) return 0;
	return 1;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) ffor(j,i+1,n) cin>>flg[i][j],flg[i][j]="&"+flg[i][j],flg[j][i]=flg[i][j];
		int flg=0;
		ffor(i,1,n) if(check(i)) {flg=1;break;}
		if(flg) {
			cout<<"Yes\n";
			ffor(u,1,n) for(auto v:G[u]) if(v>u) cout<<u<<' '<<v<<'\n';	
		}
		else cout<<"No\n";
	}
	return 0;
}
```

---

