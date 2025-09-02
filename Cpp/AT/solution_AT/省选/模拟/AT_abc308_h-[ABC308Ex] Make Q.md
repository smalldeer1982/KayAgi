# [ABC308Ex] Make Q

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_h

$ N $ 頂点 $ M $ 辺の単純無向グラフがあり、最初全ての辺は白く塗られています。 頂点には $ 1 $ から $ N $ までの番号が、辺には $ 1 $ から $ M $ までの番号がそれぞれ付けられています。 辺 $ i $ は頂点 $ A_i $ と頂点 $ B_i $ を結んでおり、この辺を黒く塗るのにかかるコストは $ C_i $ です。

$ 4 $ 本以上の辺を黒く塗ることで以下の条件を全て満たすようにすることを「Q を作る」といいます。

- 黒く塗られた辺のうちある $ 1 $ 本以外は、$ 1 $ つの単純サイクルをなす。
- 黒く塗られた辺のうち上記のサイクルに含まれない $ 1 $ 本は、そのサイクルに含まれる頂点と含まれない頂点を結ぶ。
 
Q を作ることが可能かどうか判定し、可能ならば Q を作るのに必要な最小の総コストを求めてください。

## 说明/提示

### 制約

- $ 4\leq\ N\ \leq\ 300 $
- $ 4\leq\ M\ \leq\ \frac{N(N-1)}{2} $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (A_i,B_i)\ \neq\ (A_j,B_j) $
- $ 1\ \leq\ C_i\ \leq\ 10^5 $
- 入力は全て整数
 
### Sample Explanation 1

辺 $ 2,3,4,5,6 $ を黒く塗ると、 - 辺 $ 2,4,5,6 $ が $ 1 $ つの単純サイクルをなす - 辺 $ 3 $ が頂点 $ 3 $（上記のサイクルに含まれる）と頂点 $ 1 $（上記のサイクルに含まれない）を結ぶ ため、総コスト $ 4+5+3+2+1=15 $ で Q を作ることができます。 他の方法で Q を作っても総コストは $ 15 $ 以上かかるため、答えは $ 15 $ です。

## 样例 #1

### 输入

```
5 6
1 2 6
2 3 4
1 3 5
2 4 3
4 5 2
3 5 1```

### 输出

```
15```

## 样例 #2

### 输入

```
4 4
1 2 1
2 3 1
3 4 1
1 4 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 15
2 6 48772
2 4 36426
1 6 94325
3 6 3497
2 3 60522
4 5 63982
4 6 4784
1 2 14575
5 6 68417
1 5 7775
3 4 33447
3 5 90629
1 4 47202
1 3 90081
2 5 79445```

### 输出

```
78154```

# 题解

## 作者：EuphoricStar (赞：7)

这是官方题解的 $O(n^3)$ 做法。

我们考虑枚举环上最特殊的那个点，也就是连出去一条边的点，设它为 $S$。

我们考虑使用 Dijkstra 以 $O(n^2)$ 找到包含 $S$ 的最小环。

具体地，使用 Dijkstra 建出最短路树 $T$，设点 $u$ 到 $S$ 的最短路为 $f_u$。给每个点设一个 $h_u$，若 $u = S$ 则 $h_u = S$，否则 $h_u$ 为 $S$ 的一个直接儿子，使得 $u$ 在 $h_u$ 子树内。这样，对于一条边 $(u, v, d)$，若 $h_u \ne h_v$，那么经过这条边的最小环长度为 $f_u + f_v + d$。这样不仅能找出最小环长度，还能按顺序找到环上的每一个点。

设最小环长度为 $k$，$S$ 在最小环上相邻两点为 $x, y$。然后我们考虑 $S$ 连向不在这个环上的点的边 $(S, v, d)$，对答案的贡献为 $k + d$。但是这还不够，我们还需要考虑 $S$ 连出去的边 $(S, v, d)$ 在这个环上的情况。

注意到，若 $v \ne x \land v \ne y$，这条边对最优解**一定**没有贡献。因为若我们强制钦定 $v$ 不在环上出现，求出来的最小环长 $t$ 一定 $\ge k$，最终贡献到答案中的是 $t + d$。而我们显然是可以只保留环上 $S \to v$ 的点，做到对答案的贡献 $\le t + d$（可自行画图）。

因此我们只用考虑边 $(S, x, d)$ 和边 $(S, y, d)$。删除这两条边后，再做一遍最小环即可。

注意一些最小环不存在或图不连通的处理即可。

[code](https://atcoder.jp/contests/abc308/submissions/43452621)

---

## 作者：Arghariza (赞：7)

一个 $O(n^3\log n)$ 的做法。

我们考虑枚举在环上连向外部的那个点 $u$，然后再在点集 $\{1,2,\cdots u-1,u+1,\cdots n-1,n\}$ 的导出子图中跑 Floyd，枚举 $u$ 在环上相邻的两个点 $x,y$，答案就是 $d_{x,y}+w_{x,u}+w_{y,u}+\min\limits_{(u,z)\in E,z\neq x,y}w(z,u)$。

这个样做能得到一个复杂度为 $O(n^4)$ 的优秀算法。瓶颈在于对于每个 $u$ 都要跑一遍 Floyd，考虑优化。

我们发现，对于一个点 $i$，它没被算到 Floyd 里当且仅当当前枚举的是 $i$，如果我们按照枚举的顺序建一个数轴，$i$ 对 $[1,i-1]$ 和 $[i+1,n]$ 都有贡献。这启发我们**线段树分治**。

于是变成每次在点集中插入点，并动态维护全源最短路。事实上这很简单，插入一个点 $u$ 时，先求出当前点集所有点到 $u$ 的最短路，再枚举点对 $(i,j)$，用 $u$ 作为中转点对 $d_{i,j}$ 更新即可。

复杂度 $O(n^3\log n)$。

```cpp
const int N = 660;
const int inf = 1e18;
int n, m, ans = inf, w[N][N], d[N][N], f[N][3], vis[N];
vector<int> tr[N << 2];

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)
void upd(int l, int r, int s, int t, int c, int x) {
	if (s > t) return;
	if (s <= l && r <= t) return tr[x].pb(c), void();
	if (s <= mid) upd(l, mid, s, t, c, ls);
	if (t > mid) upd(mid + 1, r, s, t, c, rs);
}

void dfs(int l, int r, int x) {
	int t[N][N];
	for (int i = 1; i <= n; i++)
		memcpy(t[i], d[i], sizeof(int) * (n + 10));
	for (int k : tr[x]) {
		vis[k] = 1;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) continue;
			d[i][k] = min(d[i][k], w[i][k]);
			d[k][i] = min(d[k][i], w[k][i]);
		}
		for(int i = 1; i <= n; i++) {
			if (!vis[i]) continue;
			for (int j = 1; j <= n; j++) {
				if (!vis[j]) continue;
				d[i][k] = d[k][i] = min(d[i][k], d[i][j] + d[j][k]);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) continue;
			for (int j = i + 1; j <= n; j++) {
				if (!vis[j]) continue;
				d[i][j] = d[j][i] = min(d[i][j], d[i][k] + d[k][j]);	
			}
		}
	}
	if (l != r) dfs(l, mid, ls), dfs(mid + 1, r, rs);
	else if (f[l][2] != n + 1) {
		for (int i = 1; i <= n; i++) {
			if (i == l) continue;
			for (int j = i + 1; j <= n; j++) {
				if (j == l) continue;
				int x = i, y = j, p;
				if (w[l][x] > w[l][y]) swap(x, y);
				if (x == f[l][0] && y == f[l][1]) p = f[l][2];
				else if (x == f[l][0]) p = f[l][1];
				else p = f[l][0];
				ans = min(ans, d[i][j] + w[i][l] + w[l][j] + w[l][p]);
			} 
		}
	}
	for (int i = 1; i <= n; i++)
		memcpy(d[i], t[i], sizeof(int) * (n + 10));
	for (int k : tr[x]) vis[k] = 0;
}

signed main() {
	n = rd(), m = rd();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			d[i][j] = w[i][j] = inf;
	for (int i = 1, u, v, w; i <= m; i++) {
		u = rd(), v = rd(), w = rd();
		::w[u][v] = ::w[v][u] = w;
	}
	for (int i = 1; i <= n; i++) 
		w[i][i] = d[i][i] = 0;
	for (int i = 1; i <= n; i++) {
		f[i][0] = f[i][1] = f[i][2] = n + 1;
		w[i][n + 1] = inf;
		for (int j = 1; j <= n; j++) {
			if (j == i) continue;
			if (w[i][j] < w[i][f[i][0]]) f[i][2] = f[i][1], f[i][1] = f[i][0], f[i][0] = j;
			else if (w[i][j] < w[i][f[i][1]]) f[i][2] = f[i][1], f[i][1] = j;
			else if (w[i][j] < w[i][f[i][2]]) f[i][2] = j;
		}
	}
	for (int i = 1; i <= n; i++) 
		upd(1, n, 1, i - 1, i, 1), upd(1, n, i + 1, n, i, 1);
	dfs(1, n, 1), wr(ans < inf ? ans : -1);
	return 0;
}
```

---

## 作者：lishujia (赞：7)

先来考虑 $O(n^4)$ 的做法，枚举在环上且连接不在环上的点 $x$，然后对于 $1$ 到 $x-1$ 和 $x+1$ 到 $n$ 的点跑 Floyd，然后枚举连接 $x$ 的两个点 $i$ 和 $j$，$w$ 为 $x$ 除与 $i$ 或 $j$ 相连边的边的最小值，然后 $f_{i,j} +d_{x,i}+d_{x.j}+w$ 就是一个 $Q$ 的代价。

然后可以将 $n$ 个点分成 $\sqrt{n}$ 块，预处理出块外每个点的最短路，在处理块内的点，时间复杂度 $O(n^{3}\sqrt{n})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,m,d[N][N],f[N][N],g[N][N],s=1,t,ans=2e9;
vector< pair<int,int> >v[N];
signed main()
{
	memset(d,0x3f,sizeof(d));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		d[x][y]=d[y][x]=z,v[x].push_back({z,y}),v[y].push_back({z,x});
	}
	for(int i=1;i<=n;i++)sort(v[i].begin(),v[i].end());
	while(s<=n)
	{
		
		t=min(s+(int)sqrt(n),n);
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=d[i][j];
		for(int k=1;k<=n;k++)if(k<s||k>t)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
		for(int x=s;x<=t;x++)
		{
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=f[i][j];
			for(int k=s;k<=t;k++)if(k^x)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
			for(int i=1;i<=n;i++)
			    for(int j=i+1;j<=n;j++)
			    {
			    	int w=2e9;
			    	for(auto y:v[x])
					    if(y.second!=i&&y.second!=j)
					    {
					    	w=y.first;
					    	break;
						}
					ans=min(1ll*ans,1ll*g[i][j]+d[i][x]+d[x][j]+w);
				}
		}
		s=t+1;
	}
	printf("%d",ans>5e8?-1:ans);
	return 0;
}

```


---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc308_h)

**题目大意**

> 定义一个 Q 子图是一个环（长度 $\ge 3$）加上一条从连接环上和环外点的边的图。
>
> 给定一张 $n$ 个点 $m$ 条边的带权无向图，求其最小权 Q 子图。
>
> 数据范围：$n\le 300,m\le n^2$。

**思路分析**

考虑枚举环外边 $u\to v$ 并删掉，然后变成求过 $u$ 的最小环，这就是[旅行者](https://www.luogu.com.cn/problem/P5304)那题的弱化版，Dijkstra 求出最短路，然后记录每个点最短路上的第一条边，取所有两端染色不同的边更新答案即可。

朴素实现 Dijkstra 是 $\mathcal O(n^2)$ 的。

但我们要枚举 $n^2$ 条边，换一个视野，先钦定一个过 $u$ 的环，那么环外边显然是剩余边中权值最小的一条，算上环上被删去的两条，这条边一定是 $u$ 的所有出边中权值前三小的边种的一条。

那么每个点只要枚举删掉三条边就行。

时间复杂度 $\mathcal O(n^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=305,inf=1e9;
int n,m,g[MAXN][MAXN],dis[MAXN],col[MAXN];
bool vis[MAXN];
int calc(int s,int d) {
	memset(dis,0x3f,sizeof(dis));
	memset(col,0,sizeof(col));
	memset(vis,0,sizeof(vis));
	dis[s]=0,vis[d]=1;
	while(true) {
		int x=0;
		for(int i=1;i<=n;++i) if(!vis[i]&&(!x||dis[i]<dis[x])) x=i;
		if(!x) break; vis[x]=true;
		for(int i=1;i<=n;++i) if(!vis[i]&&dis[x]+g[x][i]<dis[i]) {
			dis[i]=dis[x]+g[x][i],col[i]=(x==s)?i:col[x];
		}
	}
	int ans=inf; vis[d]=0;
	for(int u=1;u<=n;++u) if(u!=s&&vis[u]&&col[u]!=u) ans=min(ans,dis[u]+g[u][s]);
	for(int u=1;u<=n;++u) if(u!=s&&vis[u]) for(int v=u+1;v<=n;++v) if(v!=s&&vis[v]) {
		if(col[u]^col[v]&&g[u][v]<inf) ans=min(ans,dis[u]+g[u][v]+dis[v]);
	}
	return ans;
}
signed main() {
	scanf("%d%d",&n,&m);
	memset(g,0x3f,sizeof(g));
	for(int i=1,u,v,w;i<=m;++i) {
		scanf("%d%d%d",&u,&v,&w),g[u][v]=g[v][u]=w;
	}
	int ans=inf;
	for(int i=1;i<=n;++i) {
		vector <int> id;
		for(int j=1;j<=n;++j) if(g[i][j]<inf) id.push_back(j);
		sort(id.begin(),id.end(),[&](int x,int y){ return g[i][x]<g[i][y]; });
		if(id.size()>3) id.resize(3);
		for(int x:id) ans=min(ans,calc(i,x)+g[i][x]);
	}
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}
```

---

## 作者：BigJoker (赞：3)

考虑枚举环上最特殊的点 $x$，该点既在环上又与一个非环上的点相连。

那么有一个很暴力的做法，对于 $x$ 直接枚举跟它连接的所有边，然后钦定一条边为环外的边，然后对于连接的这个点直接忽略掉，最后按照套路求包含 $x$ 的最小环，如何求最小环？可以从 $x$ 开始，建立一棵最短路树，最短路树即依照通过跑最短路后建立，但如果一个点的最短路是从 $x$ 来，那么它不应该自立为一棵树，不与 $x$ 连边。

然后枚举所有点，对于所有最短路不是由 $x$ **直接**得到的，但是和 $x$ 有边的点 $v$，此时的最小环长度为 $f_v+e_{x,v}$

这是第一种情况，接着考虑第二种情况，如果两个点分别为 $u,v$，它们不属于一棵最短路树，并且有边相连，那么此时最小环长度为 $f_u+f_v+e_{u,v}$

将上述情况取最小值，即可得到答案。

但是这样的复杂度超过了 $n^4$，而 $n$ 最大可以为 $300$，无疑会超时。

考虑优化，发现瓶颈在于枚举环外的那条边，我们对于每一条边都要枚举一遍。那么真的需要所有都要枚举吗？其实不用，只需要枚举边权前 $3$ 小的即可，为什么？因为点 $x$ 至多连接 $3$ 条边，有 $2$ 条边都是环上的边：分情况讨论，如果环上与 $x$ 相连的两边都是前 $3$，那么环外的那条边是 $3$ 条中剩下的那条肯定是最好的；如果与环相连的两边有一条是前 $3$，另一条不是，那么环外的边取剩下两条中的更小的肯定最优；如果与环相连的边都不在前 $3$，那么肯定环外的边取最小的肯定最优。

综上，可以简单说明只需要枚举前 $3$ 条边，这样可以下降一个 $n$ 的复杂度，此题时限很大，完全可以通过。

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef pair<int,int>PII;
const int N=3e2+5;
const int inf=0x3f3f3f3f;
int n,m,fir;
int g[N][N],f[N],pre[N],vis[N];
int ans=inf;
PII rk[N];
struct node{
	int x,val;
	bool operator<(const node&P)const{
		return val>P.val;
	}
};
priority_queue<node>q;
il int get(int x){
	return pre[x]=(pre[x]==x?x:get(pre[x]));
}
il int mir(int x){
	int res=inf;
	for(re int i=1;i<=n;i++) f[i]=inf,vis[i]=0,pre[i]=i;
	f[x]=0,q.push((node){x,0});
	while(!q.empty()){
		int t=q.top().x;
		q.pop();
		if(vis[t]) continue;
		vis[t]=1;
		for(re int i=1;i<=n;i++){
			if(i==fir || g[t][i]==inf) continue;
			if(f[i]>f[t]+g[t][i]){
				f[i]=f[t]+g[t][i],q.push((node){i,f[i]});
				if(t!=x) pre[i]=t;
			}
		}
	}
	for(re int i=1;i<=n;i++) if(pre[i]!=i && g[x][i]!=inf && i!=fir) res=min(res,f[i]+g[i][x]);
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++){
			if(i==x || j==x || i==fir || j==fir || g[i][j]==inf || get(i)==get(j)) continue;
			res=min(res,f[i]+f[j]+g[i][j]);
		}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++) g[i][j]=inf;
	for(re int i=1,u,v,w;i<=m;i++){
		cin>>u>>v>>w;
		g[u][v]=g[v][u]=w;
	}
	for(re int i=1;i<=n;i++){
		for(re int j=1;j<=n;j++) rk[j]=PII(g[i][j],j);
		sort(rk+1,rk+1+n);
		for(re int j=1;j<=3;j++) fir=rk[j].second,ans=min(ans,rk[j].first+mir(i));
	}
	cout<<(ans==inf?-1:ans);
	return 0;
}
```

---

## 作者：rzh01014 (赞：0)

# [abc308_Ex](https://www.luogu.com.cn/problem/AT_abc308_h)
### 题目描述
有一个由 $N$ 个点，$M$ 条边组成的简单无向图。从中选出至少四条边，使得形成一个环与一条跟环相连的边，问选出的边最小代价是多少。
### 做法
看到这道题，很容易想到暴力，即枚举一条边，求出该边一端所在的最小环，在所有答案中取最小值。但由于暴力的时间复杂度为 $O(n^4\log n)$，对于此题来说不能接受，故需要优化。     
仔细思考题目，能发现在合法答案中必有一个点是被三条边连接的。进一步思考，能发现多出来的边必是该点所在的最小三条边之一。因此对于该题只需对于某个点，枚举其最小三条边，在其他的边中建最短路树跑最小环即可。  
时间复杂度 $O(n^3\log n)$。
### code
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e2+5,inf=1e18;
int n,m,k,ve[N][N],fa[N];
string a;
int find(int x){
	if(fa[x]==x) return fa[x];
	return fa[x]=find(fa[x]);
}
int noww[N],dis[N];
bool vis[N];
pair<int,int> rk[N];
int getans(int u,int d){
	for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0,fa[i]=i;//初始化
	priority_queue<pair<int,int>>q;
	dis[u]=0,q.push({0,u});
	while(!q.empty()){//dijkstra建立最短路树求最小环
		int v=q.top().second;
		q.pop();
		if(vis[v]) continue;
		vis[v]=1;
		for(int i=1;i<=n;i++){
			if(i!=d&&ve[v][i]&&dis[i]>dis[v]+ve[v][i]){//不包含d点
				dis[i]=dis[v]+ve[v][i];
				q.push({-dis[i],i});
				if(v!=u) fa[i]=v;//连边，不为根节点
			}
		}
	}
	int anss=inf;
	for(int i=1;i<=n;i++){//跟原点相连的环
		if(i!=d&&fa[i]!=i&&ve[u][i]!=0) anss=min(anss,dis[i]+ve[u][i]);//无d点
	}
	for(int i=1;i<=n;i++){//其它情况即不跟原点相连
		for(int j=i+1;j<=n;j++){
			if(i!=d&&j!=d&&i!=u&&j!=u&&ve[i][j]!=0&&find(i)!=find(j)) anss=min(anss,dis[i]+dis[j]+ve[i][j]);
		}
	}
	return anss;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++){//记录边
		cin>>u>>v>>w;
		ve[u][v]=ve[v][u]=w;
	}
	int ans=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){//记录下来跟i点相连的边
			if(ve[i][j]==0) rk[j]={inf,j};
			else rk[j]={ve[i][j],j};
		}
		sort(rk+1,rk+1+n);//排序
		for(int j=1;j<=3;j++) ans=min(ans,rk[j].first+getans(i,rk[j].second));//进行dijkstra，跑最小环，以i点建最短路树，其中rk[j].second()这个点不能被包含在最短路树中
	}
	if(ans==inf){
		cout<<-1;return 0;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：MatrixGroup (赞：0)

## 题意

给定一个 $N$ 个点的无向简单图。定义一个 $\textbf{Q}$ 是一个基环树子图，其中恰有一个点不在环上，权值是其边权和。求最小的 $\textbf{Q}$ 的权值，或报告不存在。$4\le N\le 300$。

## 题解

考虑枚举三度点 $v$。将 $v$ 拆成一个源 $s$ 一个汇 $t$，求最短路再加上 $v$ 的权最小相邻边（不能是与 $s,t$ 相邻的那两条边 $s-p,t-q$），再钦定不能选 $v-p,v-q$ 跑两遍就行。唯一可能出现的问题是出现了一个环上的两个点连了边。但这显然是不优的，所以正确。复杂度 $O(N^3)$，瓶颈是最短路。

……但是这样有个问题，直接 $s-x-t$ 并不对应一个环，而是一条边跑了两遍。因此我们要钦定 $p\neq q$。怎么钦定？我们枚举 $p,q$ 的二进制第 $i$ 位不相同，从第 $i$ 位为 $0$ 的开始跑，为 $1$ 的接受即可。复杂度 $O(N^3\log N)$。

[代码实现](https://atcoder.jp/contests/abc308/submissions/43177436)

---

