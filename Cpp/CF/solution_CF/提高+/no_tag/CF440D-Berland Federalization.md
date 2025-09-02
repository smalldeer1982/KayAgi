# Berland Federalization

## 题目描述

最近，Berland 面临着越来越重的联邦化的要求。许多支持者建议将国家分成几个独立的州。此外，她们还要求有一个州恰好包含 k 个城市。

现在，Berland 有 n 个城市，有一些城市间通过双向道路连接，共有 n−1 条道路，组成树形结构。

政府害怕分离后，连接不同州的道路会惹麻烦，所以她们提出了如下要求：
	
    每一个州是一个连通块，即每个州内部是互相连通的。
    存在一个州，它恰好包含 k 个城市。
    连接不同州的道路数量尽可能小。

你的任务就是想出一个方案，使得满足上述要求的同时，让连接不同州的道路数量达到最小值。

## 样例 #1

### 输入

```
5 2
1 2
2 3
3 4
4 5
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
5 3
1 2
1 3
1 4
1 5
```

### 输出

```
2
3 4
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
0

```

# 题解

## 作者：HyperSQ (赞：3)

树形DP，

$f_{u,i}$ 表示以 $u$ 为根，取出 $i$ 个节点子树的最少删边次数。

有 
$$f_{u,i}=\min\{f_{u,i-k}+f_{v,k}\}$$

过程类似分组背包。特别地，当 $k=0$ 时 $f_{u,i}$ 强制加 $1$。

但题目要输出方案怎么办呢？可以用 $g_{u,i}$ 记录一下  $f_{u,i}$ 的后继状态，转移时从 $g_{u,i-k}$ 复制。后继状态中显然当 $i=0$ 时 $u$ 要被删去。

复制后继状态看似给复杂度加了一维，但由于复制时间只与该点的子节点数决定，而子节点数是均摊的，所以不会超时。

注意，当根节点不为 $1$ 时 ans++。

Code:
```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
using namespace std;

const int maxn=405;
int n,k;
int id[maxn][maxn];
vector<pii> g[maxn][maxn];

struct node{
	int v,nxt;
}edge[maxn*2];int head[maxn],cntE;


void add(int u,int v){
	edge[++cntE]=(node){v,head[u]};
	head[u]=cntE;
}

int sz[maxn],fa[maxn];
int f[maxn][maxn];

void cpy(int u,int j,int t){
	g[u][j].clear();
	for(int i=0;i<g[u][t].size();i++){
		g[u][j].pb(g[u][t][i]);
	}
}

void init(int u,int p){
	sz[u]=1;
	fa[u]=p;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==p) continue;
		init(v,u);
		sz[u]+=sz[v];
	}
}

void dfs(int u,int p){
	f[u][1]=f[u][sz[u]]=0;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==p) continue;
		dfs(v,u);
		for(int j=sz[u];j>=0;j--){
			for(int k=0;k<=min(sz[v],j);k++){
				if(!k){
					f[u][j]++;
					g[u][j].pb(mp(v,0));
				}
				else
				if(f[u][j-k]+f[v][k]<f[u][j]){
					f[u][j]=f[u][j-k]+f[v][k];
					cpy(u,j,j-k);
					g[u][j].pb(mp(v,k));
				}
			}
		}
	}
}

void get_ans(int u,int w){
	for(int i=0;i<g[u][w].size();i++){
		if(g[u][w][i].second==0){
			if(g[u][w][i].first!=1) printf("%d ",id[u][g[u][w][i].first]);
		}else get_ans(g[u][w][i].first,g[u][w][i].second);
	}
}

int main(){
	scanf("%d%d",&n,&k);
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n-1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		id[u][v]=id[v][u]=i;
		add(u,v);add(v,u);
	}
	init(1,1);
	dfs(1,1);
	int ans=f[1][k],rt=1;
	for(int u=2;u<=n;u++){
		if(k>sz[u]) continue;
		if(f[u][k]+1<ans){
			ans=f[u][k]+1;
			rt=u;
		}
	}
	printf("%d\n",ans);
	if(rt!=1){
		printf("%d ",id[fa[rt]][rt]);
	}
	if(k!=sz[rt])
	get_ans(rt,k);
}
```

---

## 作者：yqr123YQR (赞：0)

### 分析
为了方便考虑，我们钦定根必定在那个大小为 $k$ 的块里，每次枚举根单独算。又各条边断开后相当于从全树的 $n$ 个点中删去一些子树，故可将子树大小设做权值，代价为 $1$，选了的点不可为祖孙关系，问选出点的权值和恰好为 $n-k$ 时的最小代价。

这个很明显是树上背包，单次 $O(n^2)$，跑 $n$ 边也才 $O(n^3)$。问题来到了方案的记录。我们可以记 `pre[i][j][k]` 表示在 $i$ 子树内，删去子树大小和为 $j$ 时，$i$ 的第 $k$ 个儿子的子树内分担了多少。看似 $n^3$，实际因为每个点只会被作为儿子统计一遍，故 $(i,k)$ 总共只有 $n-1$ 对，单次共计 $O(n^2)$。

### 代码
```cpp
//...
typedef long long ll;
typedef unsigned long long ull;
constexpr int maxn = 405;
std::vector<int> g[maxn];
int n, k, sz[maxn], f[maxn][maxn], son[maxn], pre[maxn][maxn][maxn], idx[maxn][maxn];
void dfs(int k, int pre)
{
	sz[k] = 1;
	int &son = ::son[k] = 0;
	f[k][0] = 0;
	for(int i : g[k]) if(i != pre)
	{
		dfs(i, k);
		++son;
		for(int p = sz[k]; p >= 0; p--)
			for(int j = sz[i]; j >= 0; j--)
			{
				int val = f[k][p] + f[i][j];
				if(f[k][p + j] > val) f[k][p + j] = val, ::pre[k][p + j][son] = j;
			}
		sz[k] += sz[i];
	}
	f[k][sz[k]] = 1;
	if(sz[k] == ::k) puts("1"), printf("%d\n", idx[k][pre]), exit(0);//直接取该子树即可
}
void print(int now, int sum, int idx, int pre)
{
	if(!sum) return;
	if(sum == sz[now]) return printf("%d ", ::idx[pre][now]), void();
	int cnt = 0;
	std::reverse(g[now].begin(), g[now].end());
	for(int i : g[now]) if(i != pre)
	{
		print(i, ::pre[now][sum][idx], son[i], now);
		sum -= ::pre[now][sum][idx--];
	}
}
int main()
{
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	read(n, k);
	for(int i = 1, u, v; i < n; i++) read(u, v),
		g[u].push_back(v), g[v].push_back(u), idx[u][v] = idx[v][u] = i;
	if(k == n) return puts("0"), 0;//直接满足条件
	int step = n, rt;
	for(int i = 1; i <= n; i++)//枚举根
	{
		memset(f, 0x3f, sizeof f);
		for(int j = 1; j <= n; j++)
			for(int k = 0; k <= sz[j]; k++)
				for(int p = 0; p <= son[j]; p++)
					pre[j][k][p] = 0;
		dfs(i, -1);
		if(step > f[i][n - k]) step = f[i][n - k], rt = i;
	}
	memset(f, 0x3f, sizeof f);
	for(int j = 1; j <= n; j++)
		for(int k = 0; k <= sz[j]; k++)
			for(int p = 0; p <= son[j]; p++)
				pre[j][k][p] = 0;
	dfs(rt, -1);
	printf("%d\n", step);
	print(rt, n - k, son[rt], -1);
	return 0;
}
```

---

