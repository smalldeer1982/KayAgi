# [POI 2006] LIS-The Postman

## 题目描述

每天早上，忙碌的邮递员需要经过城市的所有街道，完成投递邮件的任务。城市内的所有道路都是单向的，并通过一些路口连接起来。两个路口 $u,v$ 最多只有两条道路直接相连：一条 $u \to v$，一条 $v \to u$（也即不存在两条 $u \to v$ 的街道）。所有路口从 $1$ 到 $n$ 编号。

在路口 $1$，邮递员可以开始他的行程，或是结束他的行程。很长的一段时间里，邮递员可以随意选择他的路线，但最近新出的一条规定打乱了他的计划：每个邮递员得到了若干组路口序列，现在邮递员的路线必须满足如下要求：

- 路线必须从路口 $1$ 开始，在路口 $1$ 结束。
- 路线必须经过每条街道**恰好**一次。
- 规定的每个路口序列都必须在路线中**连续**出现。例如：`1 2 1` 这个序列在 `1 2 1 3` 中出现了，而在 `1 2 3 1` 中没有出现（不是连续的）。

现在邮递员找到了你，希望你能告诉他是否存在满足上述条件的路线，如果有的话，也请告诉他一条满足要求的路线。

## 说明/提示

所有数据均满足：$2 \leq n \leq 5 \times 10^4$，$1 \leq m \leq 2 \times 10^5$，$1 \leq a,b \leq n$，$a \neq b$，$0 \leq t \leq 10^4$，$2 \leq k \leq 10^5$，$\sum k \leq 10^5$。

## 样例 #1

### 输入

```
6 10
1 5
1 3
4 1
6 4
3 6
3 4
4 3
5 6
6 2
2 1
4
3 1 5 6
3 3 4 3
4 4 3 6 4
3 5 6 2```

### 输出

```
TAK
1
3
4
3
6
4
1
5
6
2
1```

# 题解

## 作者：Alex_Wei (赞：10)

> *[P3443 [POI2006]LIS-The Postman](https://www.luogu.com.cn/problem/P3443)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

每条路径片段的限制形如在片段中出现的相邻两条边必须先后走，因为**一条边有向边仅出现一次**。

所有限制形成一条边先后走的关系的链（有点像 CSP2019 T4 树上的数），将这条链缩成从起点到终点的一条边，然后跑欧拉回路即可，最后输出这条边时要再展开成链，因此要记录每条链上的结点顺序。

若限制关系出现环或分叉则无解，这可以通过并查集或链表维护。时间复杂度线性对数或线性。

```cpp
const int N = 5e5 + 5;
int n, m, q, node, cur[N], fa[N];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
int u[N], v[N], in[N], deg[N];
int vis[N], vert, top, stc[N];
vpii e[N], E[N];
vint G[N], pa[N];
gp_hash_table <ll, int> mp, buc;
ll hsh(int a, int b) {return 1ll * a * N + b;}

void dfs(int id) {
	if(!vis[id]) vert++, vis[id] = 1;
	for(int &i = cur[id]; i < E[id].size(); ) {
		pii it = E[id][i++]; dfs(it.fi);
		if(it.se > n) stc[++top] = it.se;
	} stc[++top] = id;
}

bool Med;
int main(){
	cin >> n >> m, node = m;
	for(int i = 1; i <= m; i++) {
		u[i] = read(), e[u[i]].pb(v[i] = read(), i);
		mp[hsh(u[i], v[i])] = fa[i] = i;
	} q = read();
	for(int i = 1; i <= q; i++) {
		static int p[N]; int k = read();
		for(int j = 1; j <= k; j++) p[j] = read();
		for(int j = 1; j + 1 < k; j++) {
			int u = mp[hsh(p[j], p[j + 1])], v = mp[hsh(p[j + 1], p[j + 2])];
			if(!u || !v) puts("NIE"), exit(0);
			if(buc.find(hsh(u, v)) != buc.end()) continue;
			if(G[u].size() || deg[v] || find(u) == find(v)) puts("NIE"), exit(0);
			buc[hsh(u, v)] = 1, G[u].pb(v), deg[v]++, fa[fa[u]] = fa[v];
		}
	} for(int i = 1; i <= m; i++)
		if(G[i].size() && !deg[i]) {
			int cur = u[i], p = i, x = ++node;
			while(1) {
				cur = v[p];
				if(!G[p].size()) break;
				else pa[x].pb(v[p]), p = G[p][0];
			} E[u[i]].pb(cur, x);
		}
	for(int i = 1; i <= n; i++) for(pii it : e[i])
		if(!G[it.se].size() && !deg[it.se]) E[i].pb(it);
	for(int i = 1; i <= n; i++) for(pii it : E[i]) in[it.fi]++;
	for(int i = 1; i <= n; i++)
		if(E[i].size() != in[i]) puts("NIE"), exit(0);
		else if(!E[i].size()) vert++;
	dfs(1);
	if(vert != n) puts("NIE"), exit(0);
	puts("TAK");
	while(top) {
		if(stc[top] > n) for(int it : pa[stc[top]]) cout << it << "\n";
		else cout << stc[top] << "\n"; top--;
	} return  0;
}
```

---

## 作者：conti123 (赞：7)

### 题意
求一条以 $1$ 为起点的欧拉回路，使得给定路口序列在路线及求出的欧拉回路序列中出现。

### 分析
1. 首先，肯定是要存在欧拉路径的。而有向图中存在欧拉路径须满足以下条件：图去掉孤立点后联通和每个点的入度等于出度。
2. 注意到**规定的每个路口序列都必须在路线中连续出现**，及如果我们存在路线，我们不能改变走这些规定的序列的顺序。那么相当于这些边是被限制死的了，不能改变，所以可以将它们**合并为一条边**。（因合并而多出来的孤立点不影响欧拉回路）

那么在我们就来考虑怎么将边合成了，如果直接按照每条序列合并的话，会发现可能存在几条序列刚好有公共部分从而卡掉我们的程序。

所以我们先给每条边编上一个编号，在维护指向这条边的上一条边和这条边指向的下一条边，及前驱和后继。

从而我们很容易发现：

1. 一条边不能有多个后继。
2. 几条边的指向关系不能组成一个环。
3. 若求出一条不存在的边，那么就不行。

而维护起来也是很容易的，用 map 存边的编号，开个数组记录后继，再用循环不断合并边。

最后还有一个小技巧，及我们如果合并了边，在最后输出时还有点儿麻烦，所以=我们可以加几个数组，让程序在求欧拉回路时如果碰到了指定序列（合并后）中的边，就只能遍历完序列的边，这样输出也方便。

最终本题就解完了。

~~就不上代码了~~。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define GG printf("NIE"),exit(0)
const int M=5e5+1;
using namespace std;
vector<int>E[M];
map<int,int>g[M];
int x,y,n,m,t,k,H[M],deg[M],To[M],del[M],Ne[M],Now,Nex,S[M],Sid;
void read(int &P)
{
	int x=0;
	char c=getchar();
	while(c>'9'&&c<'0')
		c=getchar();
	while(c<='9'&&c>='0')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	P=x;
}
void dfs(int u,int from)
{
	if(from)
		dfs(To[from],Ne[from]);
	else
		for(int i=H[u];i<E[u].size();i++)
		{
			int id=E[u][i];
			H[u]++;
			if(del[id])
				continue;
			del[id]=1;
			dfs(To[id],Ne[id]);
		}
	S[++Sid]=u;
}
signed main()
{
	read(n),read(m);
	for(int i=1;i<=m;i++)
	{
		read(x),read(y);
		E[x].push_back(i);
		To[i]=y,g[x][y]=i,deg[x]++,deg[y]--;
	}
	for(int i=1;i<=n;i++)
		if(deg[i])
			GG;
	read(t);
	while(t--)
	{
		read(k),read(Now),read(Nex);
		k--,k--;
		int Last=g[Now][Nex];
		if(!Last)
			GG;
		for(int i=1;i<=k;i++)
		{
			read(x);
			int id=g[Nex][x];
			if(!id)
				GG;
			if(Ne[Last]&&Ne[Last]!=id)
				GG;
			Ne[Last]=id;
			del[id]=1;
			Now=Nex,Nex=x;Last=id;
		}
	}
	dfs(1,0);
	if(Sid!=m+1)
		GG;
	printf("TAK\n");
	while(Sid)
		printf("%lld\n",S[Sid--]);
	return 0;
}
```

一些更正：

确实是没考虑到**限制成环**的情况，还是讨论区大佬多。

所以我们对于代码加入一个小细节，使得他不重复走某条边即可。

具体地，我们开一个数组 $used[i]$ 表示第 $i$ 条边是否被遍历过，然后判断即可。

更正后的代码如下：
```cpp
void dfs(int u,int from)
{
	if(from){
		if(used[from])
			GG;
		used[from]=1;
	}
	if(from)
		dfs(To[from],Ne[from]);
	else
		for(int i=H[u];i<E[u].size();i++)
		{
			int id=E[u][i];
			H[u]++;
			if(del[id])
				continue;
			del[id]=1;
			dfs(To[id],Ne[id]);
		}
	S[++Sid]=u;
}
```

---

## 作者：船酱魔王 (赞：3)

## 题意回顾

$ n $ 点 $ m $ 边有向图欧拉路径构造，要求包含给定的 $ t $ 个总长度为 $ K $ 的特征子段，无重边。

$ 2 \le n \le 5 \times 10^4 $，$ 1 \le m \le 2 \times 10^5 $，$ 0 \le t \le 10^4 $，$ 0 \le K \le 10^5 $。

## 分析

$ t=0 $ 问题是简单的，考虑如何处理特征子段。

因为无重边，因此每条边都是唯一的，特征子段每相邻两个点查询边表可以得到一个边特征子段，建立一张以边为点的图，将子段上相邻的边连接。

此时，因为边的唯一性，这张图必须由若干条互不相交的链构成。

我们取出每条链，将链头点对应原图上边的起点连向链尾点对应原图上边的终点，意味着我们省略掉这条链中间的步骤；对于每个这张图上的孤点，即原图中的自由边，我们直接保留在原图上；受到限制的非自由边全部删除。

可以理解为，我们把必须连续经过的边压缩了，此时我们在新图上跑欧拉回路算法即可。

注意最后需要解压缩这些被压缩的边。

## 实现细节

* 特征子段中，如果出现图上根本没有的边，无解。
* 互不相交的链这个特征，注意判断相交链和出现环的情况。
* 建新图时注意特判掉一条边下一条边必须为两条不同的边的情况。
* 原图中，可能没有欧拉回路。
* 为了方便解压缩时的操作，在压缩边的时候，可以开一个边表来记录这条压缩后的边对应一列点，可能压缩后出现重边，此时可以把边表变成压缩边对点列编号的映射，开一个数组用类似链式前向星的思想指向这个点列之前被覆盖掉的这条压缩边对应的上一个点列。
* 最后要特判解压缩失败的情况，即存在点列未被解压缩。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <stack>
#define jsx pair<int, int>
using namespace std;
const int N = 2e5 + 5;
int n, m, q;
int ui[N], vi[N];
map<jsx, int> mp, gt;
vector<int> vec, git[N];
int nxt[N], tyu[N], fub[N], vis[N], yuc[N], boc[N], wfs[N], cur[N];
stack<int> pat;
int prepare(int u, int ls) {
	if(vis[u]) {
		vis[0] = -1;
		return -1;
	}
	vis[u] = 1;
	git[ls].push_back(u);
	if(!nxt[u]) return u;
	return prepare(nxt[u], ls);
}
vector<int> g[N];
void dfs(int u) {
	for(int i = cur[u]; i < g[u].size(); i = cur[u]) {
		cur[u] = i + 1;
		dfs(g[u][i]);
	}
	pat.push(u);
}
vector<int> ans; 
int main() {
	scanf("%d%d", &n, &m);
	int u, v;
	for(int i = 1; i <= m; i++) scanf("%d%d", &u, &v), ui[i] = u, vi[i] = v, mp[(jsx){u, v}] = i;
	scanf("%d", &q);
	bool ok = true;
	for(int qi = 1; qi <= q; qi++) {
		int l;
		scanf("%d", &l);
		vec.clear();
		for(int i = 1; i <= l; i++) scanf("%d", &u), vec.push_back(u);
		for(int i = 1; i < l; i++) {
			tyu[i] = mp[(jsx){vec[i - 1], vec[i]}];
			if(!tyu[i]) ok = false;
		}
		for(int i = 1; i + 1 < l; i++) {
			if(nxt[tyu[i]] != tyu[i + 1] && nxt[tyu[i]]) ok = false;
			else nxt[tyu[i]] = tyu[i + 1];
		}
	}
	if(!ok) {
		puts("NIE");
		return 0;
	}
	for(int i = 1; i <= m; i++) {
		fub[nxt[i]]++;
	}
	int tcp = 1;
	for(int i = 1; i <= m; i++) {
		if(!fub[i] && nxt[i]) {
			int t = prepare(i, i);
			if(t == -1) {
				ok = false;
				break;
			} 
			int ed = vi[t];
			int st = ui[i];
			if(gt.find((jsx){st, ed}) != gt.end()) wfs[i] = gt[(jsx){st, ed}];
			gt[(jsx){st, ed}] = i;
			g[st].push_back(ed), boc[ed]++, tcp++;
		}
		if(!fub[i] && !nxt[i]) g[ui[i]].push_back(vi[i]), boc[vi[i]]++, tcp++;
		if(vis[0] < 0) {
			ok = false;
			break;
		}
	}
	for(int i = 1; i <= n; i++) {
		if(boc[i] != g[i].size()) ok = false;
	}
	if(!ok) {
		puts("NIE");
		return 0;
	}
	dfs(1);
	while(!pat.empty()) {
		int u = pat.top();
		pat.pop();
		tcp--;
		if(ans.size() == 0) {
			ans.push_back(u);
			continue;
		}
		int v = ans.back();
		if(gt.find((jsx){v, u}) != gt.end()) {
			int t = gt[(jsx){v, u}];
			if(wfs[t]) gt[(jsx){v, u}] = wfs[t];
			else gt.erase((jsx){v, u});
			for(int i = 0; i < git[t].size(); i++) {
				ans.push_back(vi[git[t][i]]);
			}
		} else {
			ans.push_back(u);
		}
	}
	if(tcp || gt.size() > 0 || ans.size() != m + 1) {
		puts("NIE");
		return 0;
	}
	puts("TAK");
	for(int i = 0; i < ans.size(); i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

