# Another Exercise on Graphs (hard version)

## 题目描述

这是该问题的困难版本。不同版本间的区别在于此版本对 $m$ 有额外约束。只有在你解决了该问题的所有版本后，才能进行 hack。

最近，"T-generation" 的导师需要筹备一场训练赛。他们发现缺少一道题目，且整场比赛中没有图论相关的问题，于是设计了如下题目。

给定一个包含 $n$ 个顶点和 $m$ 条边的连通带权无向图，图中无自环和重边。

处理 $q$ 次形如 $(a, b, k)$ 的查询：在从顶点 $a$ 到顶点 $b$ 的所有路径中，找出路径上边权的第 $k$ 大值的最小值$^{\dagger}$。

导师们认为这个问题非常有趣，但存在一个问题：他们不知道如何解决它。请帮助他们解决这个问题，因为距离比赛开始仅剩几小时。

$^{\dagger}$ 设 $w_1 \ge w_2 \ge \ldots \ge w_{h}$ 为某条路径中所有边权按非递增顺序排列后的结果。该路径边权的第 $k$ 大值即为 $w_{k}$。


## 说明/提示

在第一组测试数据中，第一个查询的一个最优路径为 $ 1 \rightarrow 3 \rightarrow 4 $，这条路径上第二大的边权值为 $ 1 $。在第二个查询中，一个最优路径为 $ 2 \rightarrow 4 \rightarrow 3 $，该路径上最大的边权值为 $ 2 $。

在第二组测试数据中，第一个查询的一个最优路径为 $ 1 \rightarrow 2 \rightarrow 4 \rightarrow 5 \rightarrow 6 $，这条路径上第三大的边权值为 $ 2 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
4 4 2
1 2 2
2 4 2
1 3 4
3 4 1
1 4 2
2 3 1
6 7 3
1 2 10
2 3 3
3 4 9
4 5 2
5 6 1
2 4 10
4 6 10
1 6 3
1 6 2
2 4 1
11 17 10
1 4 5
1 3 19
1 2 10
3 2 13
4 5 1
4 6 11
3 5 9
3 6 18
2 7 17
5 8 15
5 10 8
6 9 4
7 10 20
7 8 16
8 11 3
9 11 6
10 11 14
3 11 1
3 11 3
1 11 1
1 11 4
1 11 3
8 2 2
10 4 1
3 9 2
3 9 1
6 7 3```

### 输出

```
1 2
2 9 9
11 3 11 1 3 10 8 4 11 4```

# 题解

## 作者：DerrickLo (赞：5)

### E1

先将所有边按照边权排序，考虑在询问时二分答案。

设现在二分到了第 $x$ 条边，那么我们将边权 $\le w_{x}$ 的边的边权改为 $0$，$>w_x$ 的改为 $1$，那么我们只需要判断此时 $a$ 到 $b$ 的最短路是否 $<k$ 即可。

那么考虑预处理出 $f_{i,j,k}$ 表示若边权 $\le w_i$ 的边权改为 $0$，其余边的边权是 $1$，$j$ 到 $k$ 的最短路，我们不难发现由 $f_{i-1}$ 到 $f_i$ 的变化就是将一条边的边权由 $1$ 改为 $0$，那么直接 $\mathcal O(n^2)$ 更新即可。$f_0$ 可以使用 floyd 求。时间复杂度 $\mathcal O(n^2m)$。

### E2

因为这个图的边权只有 $0/1$，所以我们考虑将边权为 $0$ 的边的两个端点缩在一起，只有在这些新点之间的边才是有用的，显然如果将一条两个端点已经是属于同一个新点的边的边权由 $1$ 改为 $0$，这个操作显然是不会改变答案的，所以只有将两个新点合并的操作才是有用的，我们不难发现这种操作只有 $n-1$ 个，所以时间复杂度降为 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,q,a,b,k,f[405][405][405],fa[405],g[405][405];
struct ee{
	int u,v,w;
	friend bool operator<(const ee&a,const ee&b){
		return a.w<b.w;
	}
}e[160005],ed[405];
int find(int x){
	return(fa[x]==x)?x:fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++)fa[i]=i;
		memset(g,0x3f,sizeof g);
		for(int i=1;i<=m;i++)cin>>e[i].u>>e[i].v>>e[i].w,g[e[i].u][e[i].v]=g[e[i].v][e[i].u]=1;
		for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
		sort(e+1,e+m+1);
		int cnt=0;
		for(int i=1;i<=n;i++)g[i][i]=0;
		for(int i=0;i<=n-1;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)f[i][j][k]=g[j][k];
		for(int i=1;i<=m;i++){
			int fx=find(e[i].u),fy=find(e[i].v);
			if(fx==fy)continue;cnt++;
			ed[cnt]=e[i],fa[fx]=fy;
			for(int x=1;x<=n;x++)for(int y=1;y<=n;y++){
				f[cnt][x][y]=min({f[cnt-1][x][y],f[cnt-1][x][e[i].u]+f[cnt-1][y][e[i].v],f[cnt-1][x][e[i].v]+f[cnt-1][y][e[i].u]});
			}
		}
		while(q--){
			cin>>a>>b>>k;
			int l=1,r=cnt,ans=0;
			while(l<=r){
				int mid=l+r>>1;
				if(f[mid][a][b]<k)ans=mid,r=mid-1;
				else l=mid+1;
			}
			cout<<ed[ans].w<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：int08 (赞：3)

## 前言
**注意：本题解可能是假算，想阅读作者破防实录请留步，想学习正解请移步其他题解。**

下分了！而下分原因非常深刻。

# Solution
### E1
首先 E1 非常简单哈，最初的想法是二分答案 $x$，然后将大于 $x$ 的边权设为 $1$，小于等于的设为 $0$，跑 `0-1bfs` 求出最短路来判定答案。

但是我们发现询问很多，每次都要重新二分，而能作为答案的权值反而少，不如直接枚举答案然后一次性处理所有询问。

由于每次处理所有询问都需要全源最短路，总复杂度是 $O(nm(n+m))$ 的，可以通过 E1。
### E2
从 E1 到 E2 思路需要绕一个弯，要意识到枚举的过程中每次只变化一条边。

不过场上有个傻逼 `0-1bfs` 调了巨久，导致发现自己要下分就慌了，根本没看出来。

没看出来咋做呢？

还是感觉得到跟最小生成树（MST）有关系，最初想法是只保留 MST 上的边来做，发现假了。

然后发现重要性质：**答案必然在 MST 上**，否则把那条非树边换成树上的一定会减小答案。

于是枚举答案次数变少，复杂度变为 $O(n^2(n+m))$，仍然过不去，会 TLE on #21。

尝试剪一些枝，发现 `0-1bfs` 太慢了，改成只有边权为 $1$ 的 `bfs` 会好很多。

于是用并查集将 $0$ 权边的端点合并起来，剩下的直接做 `bfs` 并加上一条重要剪枝：`bfs` 确定了所有点最短路之后直接清空队列然后退出。

单起点对复杂度应该没有帮助，但是我枚举所有起点，均摊说不定就更优。

这就是我考场上最后的写法了，交上去的时候还剩两分钟。

我看着它通过了 test 21，又一个一个通过后面的测试点，真是惊心动魄。

然而哪里有奇迹呢？TLE on pretest 35。

比赛结束了，下分已成定局。

题还是得过，我决定继续卡常，那就一条一条来：
1. 加 `#pragma GCC optimize("Ofast")`；
2. 没了。

就过了？啊？

然而发现这一点的时候，离比赛结束已经过去了整整 $31.5$ 小时。

## AC Code
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
#define N 404
#define Q 508032
int cn,T,n,m,i,q,u[N*N],v[N*N],w[N*N],a[Q],b[Q],k[Q],ans[Q],dis[N][N];
vector<int> e[N];
set<int> s;
queue<int> qu;
void bfs(int s)
{
	memset(dis[s],0,sizeof dis[s]);
	dis[s][s]=1;
	int cnt=1;
	qu.push(s);
	while(!qu.empty())
	{
		int u=qu.front();qu.pop();
		for(auto x:e[u]) if(!dis[s][x])
		{
			dis[s][x]=dis[s][u]+1,qu.push(x);
			if(++cnt==cn)
			{
				while(!qu.empty()) qu.pop();
				return;
			}
		}
	}
}
int fa[N];
vector<pair<int,pair<int,int> > > ed;
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>q;
		for(i=1;i<=m;i++)
		{
			cin>>u[i]>>v[i]>>w[i],ed.push_back({w[i],{u[i],v[i]}});
		}
		sort(ed.begin(),ed.end());
		for(i=1;i<=n;i++) fa[i]=i;
		for(auto x:ed)
		{
			int u=x.second.first,v=x.second.second,w=x.first;
			if(find(u)==find(v)) continue;
			fa[find(u)]=find(v);
			s.insert(-w);
		}
		for(i=1;i<=q;i++) cin>>a[i]>>b[i]>>k[i];
		for(auto x:s)
		{
			x=-x;
			for(i=1;i<=n;i++) fa[i]=i;
			for(i=1;i<=m;i++) if(w[i]<=x) fa[find(v[i])]=find(u[i]);
			for(i=1;i<=m;i++) if(w[i]>x&&find(u[i])!=find(v[i])) e[find(u[i])].push_back(find(v[i])),e[find(v[i])].push_back(find(u[i]));
			cn=0;
			for(i=1;i<=n;i++) if(find(i)==i) cn++;
			for(i=1;i<=n;i++) bfs(i);
			for(i=1;i<=q;i++) if(dis[find(a[i])][find(b[i])]<=k[i]) ans[i]=x;
			for(i=1;i<=n;i++) e[i].clear();
		}
		for(i=1;i<=q;i++) cout<<ans[i]<<" ";
		cout<<endl;
		ed.clear();s.clear();
	}
	return 0;
 }
```
## 后记
**The End.**

---

## 作者：luanyanjia (赞：3)

感觉和 [[NOI2018] 归程](https://www.luogu.com.cn/problem/P4768) 有点像（？

考虑对每个询问二分答案，设二分到的答案是 $x$，要判断路径上的 $k$ 大值是否能不大于 $x$，只需先将价值不大于 $x$ 的所有边的边权设为 $0$，其他边设为 $1$，跑一遍 $a$ 到 $b$ 的最短路，看最短路长度是否不大于 $k$ 即可。因为 $x$ 的排名只和价值比它大的边的数量有关系，比它小的边可以随便走。

现在我们只需预处理出任意时刻任意两点间的最短路即可。将所有边按边权从小到大加入，显然如果一条边连接的两点已经被边权为 $0$ 的边联通了，这条边加入就没什么意义了。每加入一条边就用类似 Floyd 的方法松弛一遍。总时间复杂度 $O(n^3 + q\log n)$。

```cpp

#include<bits/stdc++.h>
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	int ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=3e5+5,D=405,INF=1e9+7;
int T,n,m,q;
int dis[D][D][D],cnt,w[D];
struct node{int x,y,z;}e[N];
inline void Solve(){
	rd(n,m,q);cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)dis[0][i][j]=INF;
	for(int i=1;i<=n;i++)dis[0][i][i]=0;
	for(int i=1;i<=m;i++){
		rd(e[i].x,e[i].y,e[i].z);
		dis[0][e[i].x][e[i].y]=dis[0][e[i].y][e[i].x]=1;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[0][i][j]=std::min(dis[0][i][k]+dis[0][k][j],dis[0][i][j]);
			}
		}
	}
	std::sort(e+1,e+m+1,[](node a,node b){return a.z<b.z;});
	for(int i=1;i<=m;i++){
		if(dis[cnt][e[i].x][e[i].y]==0)continue;
		++cnt;w[cnt]=e[i].z;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)dis[cnt][j][k]=dis[cnt-1][j][k];
		dis[cnt][e[i].x][e[i].y]=0;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				dis[cnt][j][k]=std::min(dis[cnt][j][k],dis[cnt][j][e[i].x]+dis[cnt][e[i].y][k]);
				dis[cnt][j][k]=std::min(dis[cnt][j][k],dis[cnt][j][e[i].y]+dis[cnt][e[i].x][k]);
			}
		}
	}
	while(q--){
		int a,b,k;rd(a,b,k);
		int L=1,R=cnt;
		while(L<=R){
			int mid=(L+R)>>1;
			if(dis[mid][a][b]<=k-1)R=mid-1;
			else L=mid+1;
		}
		printf("%d\n",w[L]);
	}
}
signed main(){
	rd(T);
	while(T--)Solve();
	return 0;
}

```

---

## 作者：wfc284 (赞：2)

对于这种问题，我们有一个（很典？）的套路。
直接做貌似不可做，故要尝试去【判定】一条边是否是答案。

判断一条边 $(u, v, w)$ 是否是第 $k$ 大的，只需要把图上所有大于 $w$ 的边权值重设为 $1$，小于等于 $w$ 的边权值重设为 $0$，看看 $u$ 到 $v$ 的最短路是不是等于 $k-1$，是则就是答案。

感性理解：我们要找的是所有路径中，最小的第 $k$ 大，重构图之后的最短路就是包含【当前判定的边】的路径（显然），这条路径如果长度为 $k-1$，那么只有 $k-1$ 条边小于 $w$，那么等价于 $w$ 是第 $k$ 大。

那我们就很好搞了。  
我们首先算出重构图中边全是 $1$ 时的全源最短路，再从小到大枚举所有边，依次从【重构图】中把每条边改为 $0$，用 Floyd 松弛一遍，就得到了每一【时刻】的全源最短路。
判定的时候二分一下，即可每个询问 $O(\log m)$ 的时间回答。

E1 的话，在预处理最短路的时候直接 $O(mn^2)$ 做就行。E2，发现在松弛某条边的时候，如果两端点的 dis 已经等于 $0$，就 skip 掉。这样做相当于每次将两个点【合并为一个点】，所以只会松弛 $n-1$ 轮，总时间复杂度 $O(n^3+q\log n)$。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
#define multi_cases 1

namespace Traveller {
	const int N = 402, M = 1.6e5+2;
	
	int n, m, q, g[N][N];
	struct edge {
		int u, v, w;
		edge() { }
		edge(int u, int v, int w) : u(u), v(v), w(w) { }
	} e[M];
	
	int f[N][N][N], a[M];
	
	void main() {
		cin >> n >> m >> q;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) g[i][j] = 0;
		for(int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			g[u][v] = g[v][u] = w;
			e[i] = edge(u, v, w);
		}
		
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				f[0][i][j] = g[i][j] ? 1 : i == j ? 0 : inf;
		
		for(int k = 1; k <= n; ++k)
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					f[0][i][j] = min(f[0][i][j], f[0][i][k] + f[0][k][j]);
		
		sort(e+1, e+m+1, [] (edge x, edge y) { return x.w < y.w; });
		int tot = 0;
		for(int k = 1; k <= m; ++k) {
			int u = e[k].u, v = e[k].v, w = e[k].w;
			if(f[tot][u][v] == 0) continue;
			a[++tot] = w;
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j) f[tot][i][j] = f[tot-1][i][j];
			f[tot][u][v] = f[tot][v][u] = 0;
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
					f[tot][i][j] = min(f[tot][i][j], min(f[tot-1][i][u] + f[tot-1][v][j], f[tot-1][i][v] + f[tot-1][u][j]));
		}
		
		for(int i = 1, u, v, k; i <= q; ++i) {
			scanf("%d%d%d", &u, &v, &k);
			int L = 1, R = tot;
			while(L < R) {
				int mid = L + R >> 1;
				if(f[mid][u][v] < k) R = mid;
				else L = mid + 1;
			}
			printf("%d ", a[L]);
		}
		puts("");
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：yvbf (赞：2)

![](bilibili:BV1dkruY8ETZ?t=2152)

---

## 作者：littlebug (赞：1)

## Solution

前置知识：[E1](https://www.luogu.com.cn/article/bh1i2jii)，这篇题解继续沿用 E1 中的一些定义之类的东西。

E2 与 E1 相比，就是又多了一步神奇的剪枝，从而把复杂度中的 $m$ 变成了 $n$。考虑到每次删边不一定是有用的，因为如果删边前 $u \leadsto v$ 的最短路已经为 $0$，那么再删边不会对答案造成任何影响，所以可以只在 $u \leadsto v$ 的最短路 $> 0$ 的时候删边。关于复杂度，可以这么考虑，把每次删边看作把 $u,v$ 两个点合并，那么因为图中只有 $n$ 个点，所以总共删边次数为 $n-1$，那么总复杂度为 $O(n^3)$。

不过数组开小硬控我 1h，无敌了。

## Code

```cpp
int n,m,q;
struct edge{int u,v,w;} e[MAXN*MAXN];
int f[MAXN][MAXN][MAXN],w[MAXN],cnt;

il void floyd()
{
    rep(i,0,n+1) rep(j,0,n+1) f[0][i][j]=inf;
    rep(i,1,n) f[0][i][i]=0;
    rep(i,1,m) f[0][e[i].u][e[i].v]=f[0][e[i].v][e[i].u]=1;
    rep(k,1,n) rep(i,1,n) rep(j,1,n) f[0][i][j]=min(f[0][i][j],f[0][i][k]+f[0][k][j]);
}

il void add(int k)
{
	w[++cnt]=e[k].w;
    rep(i,1,n) rep(j,1,n) f[cnt][i][j]=min({f[cnt-1][i][j],f[cnt-1][i][e[k].u]+f[cnt-1][e[k].v][j],f[cnt-1][i][e[k].v]+f[cnt-1][e[k].u][j]});
}

il void solve(int __Ti)
{
    cnt=0;
    
    read(n,m,q);
    rep(i,1,m) read(e[i].u,e[i].v,e[i].w);
    sort(e+1,e+m+1,[](const auto a,const auto b){return a.w<b.w;});

    floyd();
    rep(k,1,m) f[cnt][e[k].u][e[k].v] && (add(k),1);
    
    int u,v,k,l,r,mid;
    while(q--)
    {
        read(u,v,k);

        l=1,r=cnt,mid=0x66CCFF;
        while(l<r)
        {
            mid=l+r>>1;
            f[mid][u][v]<k ? (r=mid) : (l=mid+1);
        }
        write(w[r],' ');
    }

    fast_io::pc('\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：Wuming_Shi (赞：1)

# CF2057E2

## 题意
给定一个 $n$ 个点 $m$ 条边的无向图，边有边权。共 $q$ 次询问，每次询问给定 $a,b,k$，求 $a$ 到 $b$ 的所有路径中，第 $k$ 大的权值最小是多少。

$n\le400,m\le \frac{n\cdot(n-1)}{2},q\le3\cdot10^5$

## 思路
建议先阅读一下[E1题解](https://www.luogu.com.cn/article/vp0g3kdb)。

我们发现，在 E1 和 E2 只有 $m$ 的范围发生变化。我们考虑使用整体二分将 $m$ 优化到 $\log m$。

设当前二分到的答案区间为 $[l,r]$，$mid=(l+r)/2$。我们可以将 $[l,mid]$ 内的边全部加入，然后类似于 E1，对询问求一下连通块距离，小了放左边，大了放右边。然后撤销这些加边，递归左边，再加上这些边，递归右边，最后再撤销加的边。

如何实现撤销边？答案是暴力。由于 $n$ 很小，我们可以在进入这个函数时开两个数组，分别存当前的 $dis$ （即最短路）数组以及 $fa$ （即并查集）数组，赋值时暴力 `memcpy` 即可。撤销时也是直接 `memcpy` 到原数组。这样单次复杂度 $O(n^2)$。总时间复杂度即为 $O(n^2\log m+q\log m)$，可以通过。

## Code
代码并不难写。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510, MAXQ = 3e5 + 10;
int n, m, q;
struct Edge {
    int u, v, w;
}edge[MAXN * MAXN];
struct Que {
    int a, b, k, id;
}que[MAXQ];
int fa[MAXN];
int dis[MAXN][MAXN];
int ans[MAXQ];

int getf(int pos) {return fa[pos] == pos ? pos : fa[pos] = getf(fa[pos]);}
inline void merge(int a, int b) {
    a = getf(a); b = getf(b);
    if (a == b) return;
    fa[a] = b;
    for (int i = 1; i <= n; i++) {
        dis[b][i] = dis[i][b] = min(dis[a][i], dis[b][i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dis[i][b] + dis[b][j] < dis[i][j]) {
                dis[i][j] = dis[j][i] = dis[i][b] + dis[b][j];
            }
        }
    }
}

void solve(int l, int r, int ql, int qr) {
    if (ql > qr) return;
    if (l == r) {
        for (int i = ql; i <= qr; i++) {
            ans[que[i].id] = edge[l].w;
        }
        return;
    }
    int mid = l + r >> 1;
    int od[MAXN][MAXN], of[MAXN];
    memcpy(od, dis, sizeof(od));
    memcpy(of, fa, sizeof(of));
    for (int i = l; i <= mid; i++) {
        merge(edge[i].u, edge[i].v);
    }
    vector<Que> v1, v2;
    for (int i = ql; i <= qr; i++) {
        int a = getf(que[i].a);
        int b = getf(que[i].b);
        if (dis[a][b] < que[i].k) {
            v1.push_back(que[i]);
        }
        else {
            v2.push_back(que[i]);
        }
    }
    
    for (int i = 0; i < v1.size(); i++) que[i + ql] = v1[i];
    for (int i = 0; i < v2.size(); i++) que[i + ql + v1.size()] = v2[i];
    
    memcpy(dis, od, sizeof(dis));
    memcpy(fa, of, sizeof(fa));
    solve(l, mid, ql, ql + v1.size() - 1);
    for (int i = l; i <= mid; i++) {
        merge(edge[i].u, edge[i].v);
    }
    solve(mid + 1, r, ql + v1.size(), qr);
    memcpy(dis, od, sizeof(dis));
    memcpy(fa, of, sizeof(fa));
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = 0x3f3f3f3f;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = {u, v, w};
        dis[u][v] = dis[v][u] = 1;
    }

    sort(edge + 1, edge + m + 1, [&](Edge a, Edge b) {
        return a.w < b.w;
    });

    for (int i = 1; i <= q; i++) {
        cin >> que[i].a >> que[i].b >> que[i].k;
        que[i].id = i;
    }

    for (int i = 1; i <= n; i++) {
        dis[i][i] = 0;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++) fa[i] = i;

    solve(1, m, 1, q);

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

void init() {
    for (int i = 1; i <= q; i++) {
        ans[i] = 0;
    }
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
    int t; cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
        init();
    }

    return 0;
}
```

---

## 作者：juruo_zhanshen (赞：0)

[戳我进入CF提交](https://codeforces.com/problemset/problem/2057/E2)

给定一张 $n$ 个点 $m$ 条边的无向带权连通图。

$q$ 次询问：$a_i \to b_i$ 的所有路径中，「路径中边权第 $k_i$ 大值」的最小值。

这里可以考虑二分答案。

首先，我们把所有大于 $mid$ 的边都改为 $1$，反之则为 $0$。所以，$check(mid)$ 就是 $a\rightarrow b$ 的最短路径（其中，$check(mid)$ 表示 $a\rightarrow b$ 中，$mid$ 是第几大的。）

我们可以考虑使用邻接矩阵存图，如果两个结点之间有边，则边权为 $1$，否则为 $\infty$。

接下来，把边权升序排序后，对于每一条边，如果该边连接的两个结点是否已经合并（距离为 $0$），此时 `continue` ；否则合并两个点（把连接它们的边改为 $0$）。

我们可以初始化一张表 $f_{erased,u,v}$ 表示删除前 $erased$ 小的后，$u$ 到 $v$ 的距离，可以使用 floyd 求解。这里，合并后，更新 $i$ 到 $j$ 的距离，如果当前这一轮 $u$ 与 $v$ 和合并，那么需要分类讨论：
$$
f_{erased,i,j}=
\min\begin{cases}
{f_{erased-1,i,j}}\\
{f_{erased-1,i,u}+f_{erased-1,v,j}}\\
{f_{erased-1,i,v}+f_{erased-1,u,j}}\\
\end{cases}
$$

实际上，并不是合并 $u$ 和 $v$ 就能保证 $i\to j$ 最短，可能会绕路。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef long long ll;
const int N = 400 + 5;
const int M = N * N / 2;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

struct Edge
{
    int u, v, w;
}e[M];
int g[N][N];
int f[N][N][N];
int n, m, q;
int ans[N];

int main ( int argc, char *argv[] )
{ 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--){
        cin >> n >> m >> q;
        memset(g, 0, sizeof g);
        for (int i = 1, u, v, w; i <= m; i++){
            cin >> u >> v >> w;
            g[u][v] = g[v][u] = w;
            e[i] = Edge{u, v, w};
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[0][i][j] = g[i][j] ? 1 : i == j ? 0 : INF;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    f[0][i][j] = min(f[0][i][j], f[0][i][k] + f[0][k][j]);
        sort(e + 1, e + m + 1, [](Edge x, Edge y){ return x.w < y.w; });

        int erased = 0;
        for (int k = 1; k <= m; k++){
            int u = e[k].u, v = e[k].v, w = e[k].w;
            if (f[erased][u][v] == 0)
                continue;
            ans[++erased] = w;

            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    f[erased][i][j] = f[erased - 1][i][j];
            f[erased][u][v] = f[erased][v][u] = 0;
            
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    f[erased][i][j] = min(f[erased][i][j], min(f[erased - 1][i][u] + f[erased - 1][v][j], f[erased - 1][i][v] + f[erased - 1][u][j]));
        }

        for (int i = 1, a, b, k; i <= q; i++){
            cin >> a >> b >> k;
            int l = 1, r = erased;
            while (l < r){
                int mid = l + (r - l >> 1);
                if (f[mid][a][b] < k) r = mid;
                else
                    l = mid + 1;
            }
            cout << ans[l] << " ";
        }
        cout << endl;
    }
    return 0;
}				/* ----------  end of function main  ---------- */
```

---

## 作者：ax_by_c (赞：0)

## E1

考虑枚举答案，将小于 $val$ 的边权看作 0，否则看作 1，那么只要 $dis(u,v)<k$ 就说明 $ans<val$。

一开始先跑一次 floyd，然后按照边权从小到大枚举，每次使用枚举边的端点去松弛即可。

时间复杂度 $O(n^3+mn^2+mq)$。

## E2

发现如果不是 MST 上的边，那么松弛到它的时候两端已经出现长度为零的路径了，所以不需要松弛。

所以只需松弛 MST 上的边，时间复杂度 $O(n^3+nq)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,l,r) for(int i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int inf=1e9;
const int N=405;
const int Q=3e5+5;
int n,m,q;
struct E{
	int u,v,w;
};
bool cmp(E x,E y){
	return x.w<y.w;
}
vector<E>es;
int f[N][N];
int x[Q],y[Q],kk[Q],ans[Q];
struct DSU{
	int fa[N];
	void Init(int n){
		rep(i,1,n)fa[i]=i;
	}
	int find(int x){
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	bool meg(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y)return 0;
		fa[x]=y;
		return 1;
	}
}dsu;
void slv(){
	scanf("%d %d %d",&n,&m,&q);
	dsu.Init(n);
	rep(i,1,n)rep(j,1,n)f[i][j]=inf;
	rep(i,1,n)f[i][i]=0;
	es.clr();
	rep(i,1,m){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		es.push_back({u,v,w});
		if(u!=v){
			f[u][v]=1;
			f[v][u]=1;
		}
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	sort(es.begin(),es.end(),cmp);
	rep(i,1,q){
		scanf("%d %d %d",&x[i],&y[i],&kk[i]);
		ans[i]=inf;
	}
	int lst=-inf;
	for(auto it:es){
		if(!dsu.meg(it.u,it.v))continue;
		rep(i,1,q)if(f[x[i]][y[i]]<kk[i])ans[i]=min(ans[i],lst);
		lst=it.w;
		rep(i,1,n)rep(j,1,n)f[i][j]=min({f[i][j],f[i][it.u]+f[it.v][j],f[i][it.v]+f[it.u][j]});
	}
	rep(i,1,q)printf("%d ",min(ans[i],lst));
	putchar('\n');
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：0)

阅读本文前请先阅读 [E1](https://www.luogu.com.cn/article/5q7pwzgz)。

本文以“开放边 $u$，$v$”形容“将一条连结 $u$，$v$ 的边边权设为 $0$”。

发现 E1 复杂度瓶颈在枚举每条边。

考虑过滤一些无用的情况。可以发现，开放边 $u$，$v$ 对答案无影响，当且仅当此时 $u$，$v$ 间最短路为 $0$。显然此时这条边不能对答案造成贡献。

可以考虑用一个并查集维护边权为 $0$ 的边构成的连通块。
我们每开放一条边 $u$，$v$，就将他加入这个并查集中，并判断，如果它们本来就在同一连通块中，意味着此时 $u$，$v$ 间最短路为 $0$。就不执行暴力更新 $f$ 的操作。否则将两个连通块合并，并暴力更新 $f$。

考虑复杂度为什么是对的。显然暴力更新 $f$ 的操作次数就是执行合并连通块的次数。对于一个 $n$ 个点的图，合并 $n-1$ 次即可让其连通。连通后每两点间最短路都为 $0$，我们不会进行操作。因此暴力更新 $f$ 的操作只会执行 $n-1$ 次。复杂度 $O(n^3+q\log n)$，可过。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define fir first
#define sec second
#define pb emplace_back
#define mod 1000000007
#define put putchar
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
const int JYAAKIOI=1e18,N=4e2+86,M=N*N/2+86;
struct node{
	int u,v,w;
}a[M];
int T,n,m,q,f[N][N][N],s,fa[N],now,mp[M];
il bool cmp(node x,node y){
	return x.w<y.w;
}
il int fd(int x){return fa[x]==x?x:fa[x]=fd(fa[x]);}
il bool mge(int x,int y){
	int fax=fd(x),fay=fd(y);
	if(fax==fay)return 0;
	fa[fax]=fay;
	return 1;
}
signed main(){
	//freopen("csnm.in","r",stdin);
	//freopen("csnm.out","w",stdout);
	T=rd();
	while(T--){
		n=rd();m=rd();q=rd();
		for(int i=1;i<=m;++i)a[i].u=rd(),a[i].v=rd(),a[i].w=rd();
		sort(a+1,a+1+m,cmp);
		for(int i=0;i<=n;++i)fa[i]=i;
		for(int i=0;i<=n;++i){
			for(int j=1;j<=n;++j){
				for(int k=1;k<=n;++k){
					f[i][j][k]=JYAAKIOI;
				}
			}
		}
		for(int i=0;i<=n;++i)f[0][i][i]=0;
		for(int i=1;i<=m;++i)f[0][a[i].u][a[i].v]=f[0][a[i].v][a[i].u]=1;
		for(int k=1;k<=n;++k){
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					f[0][i][j]=min(f[0][i][j],f[0][i][k]+f[0][k][j]);
				}
			}
		}
		now=0;
		for(int k=1;k<=m;++k){
			int u=a[k].u,v=a[k].v;
			if(mge(u,v)){
				mp[++now]=a[k].w;
				for(int i=1;i<=n;++i){
					for(int j=1;j<=n;++j){
						f[now][i][j]=min(f[now-1][i][j],min(f[now-1][i][u]+f[now-1][v][j],f[now-1][i][v]+f[now-1][u][j]));
					}
				}
			}
		}
		while(q--){
			int u=rd(),v=rd(),k=rd();
			int l=0,r=now,res=-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(f[mid][u][v]<k){
					r=mid-1;
					res=mid;
				}
				else l=mid+1;
			}
			wr(mp[res]),put(' ');
		}
		put('\n');
	}
    return 0;
}
```

---

