# [ABC190E] Magical Ornament

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc190/tasks/abc190_e

AtCoder 王国には $ 1,\ 2,\ \dots,\ N $ の番号がついた $ N $ 種類の魔法石が流通しています。  
 高橋くんは、魔法石を一列に並べて飾りを作ろうとしています。  
 魔法石には隣り合わせにできる組とできない組があります。 隣り合わせにできる組は $ ( $魔法石 $ A_1, $ 魔法石 $ B_1),\ ( $魔法石 $ A_2, $ 魔法石 $ B_2),\ \dots,\ ( $魔法石 $ A_M, $ 魔法石 $ B_M) $ の $ M $ 組で、それ以外の組は隣り合わせることができません。(これらの組において、石の順序は不問です。)  
 魔法石 $ C_1,\ C_2,\ \dots,\ C_K $ をそれぞれ $ 1 $ 個以上含む魔法石の列を作ることができるか判定し、作れる場合はそのような列を作るのに必要な魔法石の個数の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ = N\ <\ =\ 10^5 $
- $ 0\ <\ = M\ <\ =\ 10^5 $
- $ 1\ <\ =\ A_i\ <\ B_i\ <\ =\ N $
- $ i\ ≠\ j $ ならば $ (A_i,\ B_i)\ ≠\ (A_j,\ B_j) $
- $ 1\ <\ =\ K\ <\ =\ 17 $
- $ 1\ <\ =\ C_1\ <\ C_2\ <\ \dots\ <\ C_K\ <\ =\ N $

### Sample Explanation 1

例えば、魔法石を $ [1,\ 4,\ 2,\ 4,\ 3] $ と並べると、魔法石 $ 1,\ 2,\ 3 $ を含む長さ $ 5 $ の列を作ることができます。

### Sample Explanation 3

例えば、魔法石を $ [1,\ 6,\ 7,\ 5,\ 8,\ 3,\ 9,\ 3,\ 8,\ 10,\ 2] $ と並べると、魔法石 $ 1,\ 2,\ 7,\ 9 $ を含む長さ $ 11 $ の列を作ることができます。

## 样例 #1

### 输入

```
4 3
1 4
2 4
3 4
3
1 2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
4 3
1 4
2 4
1 2
3
1 2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 10
3 9
3 8
8 10
2 10
5 8
6 8
5 7
6 7
1 6
2 4
4
1 2 7 9```

### 输出

```
11```

# 题解

## 作者：Meickol (赞：1)

经典状压 DP，我们首先处理好每个需要的点之间相互到达所需的最小步数，这显然可以用 BFS 处理。

然后设 $\large f_{i,j}$ 表示当前状态为 $j$ 且最后一次移动后停留在 $i$ 点，跑一遍状压 DP 即可。

具体实现可看代码，代码不难理解，就不多解释了。

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
typedef long long LL;
const int N=1e5+5,M=N*2,S=18,INF=0x3f3f3f3f;
int n,m,cnt;
int e[M],ne[M],h[N],idx;
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
LL f[S][1<<S];
int c[S];
LL dist[N],dis[S][N];
bool st[N];
void bfs(int u){
	memset(dist,INF,sizeof dist);
	memset(st,0,sizeof st);
	st[u]=1;
	dist[u]=0;
	queue<int> q;
	q.push(u);
	while(!q.empty()){
		auto t=q.front();
		q.pop();
		for(int i=h[t];~i;i=ne[i]){
			int j=e[i];
			if(st[j]) continue;
			dist[j]=dist[t]+1;
			q.push(j);
			st[j]=1;
		}
	}
}
void solve(){
	memset(h,-1,sizeof h);
	cin>>n>>m;
	rep(i,1,m){
		int a,b;
		cin>>a>>b;
		add(a,b),add(b,a);
	}
	cin>>cnt;
	memset(dis,INF,sizeof dis);
	rep(i,1,cnt) cin>>c[i];
	rep(i,1,cnt){
		bfs(c[i]);
		rep(j,1,cnt) dis[i][j]=dist[c[j]];
	}
	LL maxj=(1<<cnt)-1;
	memset(f,INF,sizeof f);
	rep(i,1,cnt) f[i][1<<(i-1)]=1;
	rep(j,0,maxj){
		rep(i,1,cnt){
			if(!(j>>(i-1)&1)) continue;
			rep(k,1,cnt){
				if(!(j>>(k-1)&1)) continue;
				if(i==k) continue;
				f[i][j]=min(f[i][j],f[k][j-(1<<(i-1))]+dis[k][i]);
			}
		}
	}
	LL ans=INF;
	rep(i,1,cnt) ans=min(ans,f[i][maxj]);
	if(ans==INF) cout<<"-1";
	else cout<<ans;
}
```

---

## 作者：Union_Find (赞：1)

题目很好理解，这是一道经典的状压 dp。

设 $f_{i,s}$ 表示当前是 $c_i$ 号石头，并且当前状态是 $s$。$s$ 用二进制表示是否包含石头。第 $i$ 为是 $1$ 表示已经包含了 $c_i$ 号石头。那么我们就可以得到。

`f[j][s | (1 << (i - 1))] = min(f[i][s] + dis[i][j])`

$dis_{i,j}$ 表示第 $c_i$ 号石头连接到 $c_j$ 号石头需要几块石头。因为 $k \le 17$，所以 $dis_{i,j}$ 可以先用 `bfs` 预处理。

总体来说比较板。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, m, u, v, k, c[25], dis[25][N], vis[N], f[25][(1 << 20) + 5], ans = 1e18;
ll head[N], nxt[N << 1], to[N << 1], en;
il void add(ll u, ll v){nxt[++en] = head[u], head[u] = en, to[en] = v;}
il void bfs(ll s){
	queue <ll> q;
	memset (vis, 0, sizeof vis);
	memset (dis[s], 0x3f, sizeof dis[s]);
	q.push(c[s]), dis[s][c[s]] = 0, vis[c[s]] = 1;
	while (q.size()){
		ll u = q.front();
		q.pop();
		for (int i = head[u]; i; i = nxt[i]){
			ll v = to[i];
			if (vis[v]) continue;
			vis[v] = 1;
			q.push(v);
			dis[s][v] = min(dis[s][v], dis[s][u] + 1);
		}
	}
}
il bool inn(ll x, ll s){return (s & (1 << (x - 1)));}
int main(){
	n = rd(), m = rd();
	for (int i = 1; i <= m; i++){
		u = rd(), v = rd();
		add(u, v), add(v , u);
	}
	k = rd();
	for (int i = 1; i <= k; i++) c[i] = rd();
	for (int s = 1; s <= k; s++) bfs(s);
	//for (int s = 1; s <= k; s++, puts("")) for (int t = 1; t <= n; t++) printf ("%lld ", dis[s][t]);
	memset (f, 0x3f, sizeof f);
	for (int i = 1; i <= k; i++) f[i][(1 << (i - 1))] = 0;
	for (int s = 0; s < (1 << k); s++){
		for (int i = 1; i <= k; i++){
			if (!inn(i, s)) continue;
			for (int j = 1; j <= k; j++){	
				if (inn(j, s)) continue;
				f[j][s | (1 << (j - 1))] = min(f[j][s | (1 << (j - 1))], f[i][s] + dis[i][c[j]]);
			}
		}
	}
	for (int i = 1; i <= k; i++) ans = min(ans, f[i][(1 << k) - 1]);
	if (ans == 1e18) puts("-1");
	else printf ("%lld", ans + 1);
	return 0;
}

```

---

## 作者：CQ_Bob (赞：1)

## 分析

考虑状压。

定义状态函数 $f_{i,j}$ 表示在得到 $C$ 出现过的状态为 $i$ 且排列末尾为 $j$ 时的最小代价。则有转移方程：$f_{i,j}=\min\{f_{i',k}+dis_{k,j}\}$，保证 $i'$ 表示集合属于 $i$。$dis_{i,j}$ 跑最短路就行了，通过枚举 $C_i$ 为起点可以做到 $O(kn\log n) $ 的复杂度求。再注意一下空间问题即可。

复杂度 $O(kn\log n+2^kk^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=1e5+10,M=1<<17|1,K=18;
int n,m,k;
int ne[N<<1],e[N<<1],h[N],idx;
int c[N];
int f[M][K];
int vis[K][N],dis[K][N];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dij(int s,int id){
	priority_queue<PII,vector<PII>,greater<PII>> qu;
	qu.push({0,s}),dis[id][s]=0;
	while(!qu.empty()){
		PII now=qu.top();qu.pop();
		if(vis[id][now.y]) continue;
		vis[id][now.y]=1;
		for(re int i=h[now.y];i;i=ne[i]){
			int j=e[i];if(dis[id][j]>dis[id][now.y]+1){
				dis[id][j]=dis[id][now.y]+1,qu.push({dis[id][j],j});
			}
		}
	}
	return ;
}
il void solve(){
	memset(dis,0x3f,sizeof(dis)),
	memset(vis,0,sizeof(vis)),
	memset(f,0x3f,sizeof(f));
	n=read(),m=read();
	for(re int i=1,a,b;i<=m;++i)
		a=read(),b=read(),
		add(a,b),add(b,a);
	k=read();
	for(re int i=1;i<=k;++i)
		c[i]=read(),dij(c[i],i);
	for(re int i=1;i<=k;++i) f[0][i]=0;
	for(re int i=1;i<(1<<k);++i){
		for(re int a=1;a<=k;++a){
			if(!((i>>(a-1))&1)) continue;
			for(re int b=1;b<=k;++b){
				if(!((i>>(b-1))&1)) continue;
				int lst=i-(1<<(a-1));
				f[i][a]=min(f[i][a],f[lst][b]+dis[b][c[a]]);
			}
		}
	}
	int Min=1e18;
	for(re int i=1;i<=k;++i) Min=min(Min,f[(1<<k)-1][i]);
	if(Min>1e9) printf("-1\n");
	else printf("%lld\n",Min+1);
	return ;      
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：DerrickLo (赞：1)

可以想到一个状压 dp。

设 $dp_{S,i}$ 表示当前集合 $S$ 中的元素都已出现，而且最后的一个数是 $i$ 的最小值，那么很容易地可以得到

$$dp_{S,i}=\min_{j\in S,i\neq j}dp_{S\backslash i,j}+dis_{i,j}$$

其中 $dis_{i,j}$ 表示 $c_i$ 到 $c_j$ 的最短路，预处理就是 $dp_{\{i\},i}=1$。

就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,u,v,k,c[50],dis[50][200005],vis[200005],dp[1000005][25],ans=1e18;
vector<int> ve[200005];
queue<int>qu; 
void dijkstra(int s,int p){
	qu.push(s); 
	memset(dis[p],0x3f,sizeof dis[p]);
	dis[p][s]=0;
	while(!qu.empty()){
		int ft=qu.front();qu.pop();
		for(int v:ve[ft]){
			if(dis[p][v]>=1e18){
				dis[p][v]=dis[p][ft]+1;
				qu.push(v); 
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>u>>v,ve[u].emplace_back(v),ve[v].emplace_back(u);
	cin>>k;
	for(int i=1;i<=k;i++)cin>>c[i];
	for(int i=1;i<=k;i++)dijkstra(c[i],i);
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=k;i++)dp[1<<(i-1)][i]=1;
	for(int i=1;i<(1<<k);i++){
		for(int j=1;j<=k;j++)if(i&(1<<(j-1)))for(int l=1;l<=k;l++)if(j!=l)if(i&(1<<(l-1))){
			dp[i][j]=min(dp[i][j],dp[i-(1<<(j-1))][l]+dis[l][c[j]]);
		}
	}
	for(int i=1;i<=k;i++)ans=min(ans,dp[(1<<k)-1][i]);
	if(ans>=1e18)cout<<-1;
	else cout<<ans;
	return 0;
}
```

---

## 作者：tanshunyu0913 (赞：0)

# 思路
对于每两块石头，如果要求出同时放置它们最小需要多少块石头，可以把每一对可以相邻的石头建一条双向边，再跑最短路就行了。

然后我们发现这题变成了最短 Hamilton 路径，即不重不漏地经过每一个 $C_i$，求最短路。可以用状压 DP 解决。

复杂度 $O\left(K^2 \cdot 2^K \right)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,K=18,inf=1e18;
int n,m,k;
vector<int> e[N];
int d[N],ans=inf,c[N];
int dis[K][K];
int f[1<<17][K];//f[s][i]表示以i结尾，状态为s的最短路 
bool vis[N];
int bfs(int st,int ed){
	queue<int> q;
	memset(d,0x3f,sizeof d);
	memset(vis,0,sizeof vis);
	d[st]=0;q.push(st);
	while(q.size()){
		int u=q.front();q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto v:e[u])
			if(d[v]>d[u]+1){
				d[v]=d[u]+1;
				q.push(v); 
				if(v==ed)return d[v];
			}
	}
	return inf;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	cin>>k;
	for(int i=1;i<=k;i++)
		cin>>c[i];
	memset(dis,0x3f,sizeof dis);
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=k;i++)	
		for(int j=i+1;j<=k;j++)
			dis[i][j]=dis[j][i]=bfs(c[i],c[j]);
	for(int i=1;i<=k;i++)f[1<<(i-1)][i]=1;
	for(int s=0;s<(1<<k);s++)
		for(int i=0;i<k;i++)
			if((s>>i)&1)
				for(int j=0;j<k;j++)
					if(i!=j&&(s>>j)&1){
						f[s][i+1]=min(f[s][i+1],f[s^(1<<i)][j+1]+dis[i+1][j+1]);
					}
	for(int i=1;i<=k;i++)ans=min(ans,f[(1<<k)-1][i]);
	if(ans==inf)puts("-1");
	else cout<<ans;
	return 0;
}

---

## 作者：MMXIandCCXXII (赞：0)

$\Large {\text{Solution}}$

看样例想到每次从一个必须经过的点走到另一个必须经过的点，通过某种方式获取路径长度，就在觉得不可行时发现 $k\le17$，于是就可以从每个必经之点跑 dijkstra ~~（明明可以 BFS 的）~~，还是因为 $k$ 的大小，我们就可以用状压来求走过每一个点的最短路径了。总时间复杂度 $\Omicron(k\times n\log m+2^k\times k^2)$。如果用 BFS 就是 $\Omicron(k\times (n+m) + 2^k\times k^2)$。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair <int, int>
#define CCFIS return
using namespace std;

signed main();
vector <int> v[100010];
int d[20][100010], c[20];
bool vis[100010];
int f[200010][20];

void dijkstra(int id, int st)
{
	d[id][st] = 0;
	memset (vis, false, sizeof vis);
	priority_queue <pii, vector <pii>, greater <pii> > q;
	q.push ({d[id][st], st});
	while (q.size ())
	{
		int u = q.top ().second;
		q.pop ();
		if (vis[u]) continue;
		vis[u] = true;
		for (int j : v[u])
		{
			if (d[id][j] > d[id][u] + 1)
			{
				d[id][j] = d[id][u] + 1;
				q.push ({d[id][j], j});
			}
		}
	}
}

signed main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		v[a].push_back (b);
		v[b].push_back (a);
	}
	int k;
	cin >> k;
	memset (d, 0x3f, sizeof d);
	for (int i = 0; i < k; i++)
	{
		cin >> c[i];
		dijkstra (i, c[i]);
//		for (int j = 1; j <= n; j++)
//			cout << d[i][j] << " ";
//		cout << endl;
	}
//	for (int i = 0; i <= k; i++)
//	{
//		for (int j = 1; j <= n; j++)
//			cout << d[i][j] << " ";
//		cout << endl;
//	}
	memset (f, 0x3f, sizeof f);
	for (int i = 0; i < k; i++)
		f[1 << i][i] = 1;
	for (int i = 1; i < (1 << k); i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (((i >> j) & 1) == 0) continue;
			for (int l = 0; l < k; l++)
			{
				if (j == l || ((i >> l) & 1) == 0) continue;
//				cout << l << " " << c[j] << " " << endl;
				f[i][j] = min (f[i][j], f[i - (1 << j)][l] + d[l][c[j]]);
//				cout << f[i - (1 << j)][l] << " " << d[l][c[j]] << endl;
			}
//			printf ("f[%lld][%lld] = %lld\n", i, j, f[i][j]);
		}
	}
	int ans = 1e18;
	for (int i = 0; i < k; i++)
		ans = min (ans, f[(1 << k) - 1][i]);
	if (ans != 1e18) cout << ans << endl;
	else cout << -1 << endl;
	CCFIS 0;
}
```

---

## 作者：Kketchup (赞：0)

### [[ABC190E] Magical Ornament](https://atcoder.jp/contests/abc190/tasks/abc190_e)

- 状压 DP

**Sol:** 观察到 $k$ 很小，所以直接状压：$f_{S,i}$ 表示已经表示出的集合为 $S$，序列末尾为 $i$ 的最小答案。

$$f_{S,i}=\min_{j\in S,i\not= j}f_{S\backslash i,j}+dis_{i,j}$$

其中 $dis_{i,j}$ 是关键，表示从点 $i$ 到 $j$ 的最小步数，直接 bfs 预处理即可。

**Trick:** 将 $i,j$ 可以相邻转化成 $i$ 向 $j$ 连边，这样将两个点的最短路就是同时存在的最小代价。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=2e5+10;
int n,m,k;
vector<int> e[N];
ll f[1000000][20],ans=1e18,dis[20][N];
int c[20];
queue<int> q;
void dij(int s,int i){
    q.push(s);
    memset(dis[i],0x3f,sizeof(dis[i]));
    dis[i][s]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int v:e[u]){
            if(dis[i][v]>=1e18){
                dis[i][v]=dis[i][u]+1;
                q.push(v);
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1,x,y;i<=m;++i){
        cin>>x>>y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    cin>>k;
    for(int i=1;i<=k;++i){
        cin>>c[i];
        dij(c[i],i);
    }
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=k;++i) f[(1<<(i-1))][i]=1;
    for(int i=1;i<(1<<k);++i){
        for(int j=1;j<=k;++j){
            if(i&(1<<(j-1))){
                for(int l=1;l<=k;++l){
                    if(j==l) continue;
                    if(i&(1<<(l-1))){
                        f[i][j]=min(f[i][j],f[i-(1<<(j-1))][l]+dis[l][c[j]]);
                    }
                }
            }
        }
    }
    for(int i=1;i<=k;++i) ans=min(ans,f[(1<<k)-1][i]);
    if(ans>=1e18) cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}

```

---

## 作者：cosf (赞：0)

## [AT_abc190_e](https://www.luogu.com.cn/problem/AT_abc190_e)

首先，看看数据范围。$k \le 17$ 这种东西显然用状压 dp 是很合适的。

具体怎么压呢？我们可以令 $dp_{S, i}$ 表示经过过的点集为 $S$，最后一个为 $i$。有 $dp_{S, i} = \min_{j \in S, j \not= i} dp_{(S - i), j} + d_{i, j}$，其中 $d_{i, j}$ 为 $c_i$ 与 $c_j$ 的距离。

注意，此处仅仅记录 $C$ 中的点，其他的**无意义**。

那么，我们在 dp 前仅仅需要记录两点之间的距离 $d_{i, j}$。跑 $K$ 遍 bfs 即可。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 100005
#define MAXK 18
#define MAXS 132020

// using ll = long long;
#define int long long

using pii = pair<int, int>;

vector<int> e[MAXN];

int dis[MAXN];

int n;

void bfs(int p)
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        dis[i] = 0x3ffff3fff3ff;
    }
    dis[p] = 0;
    q.push(p);
    while (!q.empty())
    {
    	int c = q.front();
	   	q.pop();
        for (int u : e[c])
        {
            if (dis[u] > n)
            {
            	dis[u] = dis[c] + 1;
                q.push(u);
            }
        }
    }
}

int d[MAXK][MAXK];

int c[MAXK];

int dp[MAXS][MAXK];

signed main()
{
    cin >> n;
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    int k;
    cin >> k;
    if (k == 1)
    {
    	cout << 1 << endl;
    	return 0;
	}
    for (int i = 1; i <= k; i++)
    {
        cin >> c[i];
    }
    for (int i = 1; i <= k; i++)
    {
        bfs(c[i]);
        for (int j = 1; j <= k; j++)
        {
            d[i][j] = dis[c[j]];
//            cout << d[i][j] << ' ';
        }
//        cout << endl;
    }
    memset(dp, 0x1f, sizeof(dp));
    for (int i = 1; i <= k; i++)
    {
    	dp[1 << (i - 1)][i] = 1;
	}
    for (int s = 1; s < (1 << k); s++)
    {
    	if (__builtin_popcount(s) == 1)
    	{
    		continue;
		}
        for (int i = 1; i <= k; i++)
        {
            if (!(s & (1 << (i - 1))))
            {
                continue;
            }
            for (int j = 1; j <= k; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (!(s & (1 << (j - 1))))
                {
                    continue;
                }
                dp[s][j] = min(dp[s][j], dp[s ^ (1 << (j - 1))][i] + d[i][j]);
            }
        }
    }
    int res = 0x3ffff3fff3ff;
    for (int i = 1; i <= k; i++)
    {
        res = min(res, dp[(1 << k) - 1][i]);
    }
    if (res >= 0x3ffff3fff3ff) // 判 -1
    {
        cout << -1 << endl;
    }
    else
    {
        cout << res << endl;
    }
    return 0;
}

```


---

## 作者：Jia_ye (赞：0)

因为写位运算不熟练，而且想按秩转移的时候总是头疼，所以写了题解记录一下。

- AtCoder 王国流通着 $N$ 种魔法石，编号为 $1,2,\dots,N$。高桥想要把魔法石排成一列做成装饰品。
- 有的魔法石能够相邻放在一起，有的魔法石却不行。有 $M$ 组魔法石是可以相邻的，分别是 $ ( $魔法石 $ A_1, $ 魔法石 $ B_1),\ ( $魔法石 $ A_2, $ 魔法石 $ B_2),\ \dots,\ ( $魔法石 $ A_M, $ 魔法石 $ B_M) $。除此之外的任何两个魔法石都不能相邻摆放。（可以相邻的魔法石摆放前后顺序不限。）
- 请判断是否存在这样一种排列方式，使得其中包含 $ C_1,C_2,\dots,C_K $ 中的每一种魔法石。如果存在，求形成这样一个序列所需的最小宝石数量。如果不存在的话，输出 `-1`。
- $1\le N,M\le 10^5$；$1\le K\le 17$。

（这个翻译也可以考虑采纳XD）

注意到合法序列的每一个石头前后的石头都是必须满足和自己能相邻的，所以这道题能转化为一道图论题。在可以每个可以相邻的 $A_i$ 和 $B_i$ 建立一条长度为 $1$ 的边，于是问题就转化为寻找一个遍历 $C_1$ 到 $C_K$ 每一个点的最短路。此外如果 这些点中有点不与图连通，那就没有合法路径。

注意到 $1\le K\le 17$ 的小范围，可以把 $C_i$ 是否为在路径上的路径情况表示成二进制数 $S$。考虑状态压缩的动态规划。定义 $f_{i,S}$ 为 以 $C_i$ 结尾的、拥有 $C_1$ 到 $C_K$ 中的点的集合为 $S$ 的最短路径。于是答案为所有 $i$ 中最短的路径长度再加 $1$，即 $\min\limits_{i=1,2,\dots,N}\{f_{i,2^K-1}\}+1$，注意加 $1$ 是因为要求的是序列长度，路径长度只是两点间隔数。

考虑转移。如果 $j$ 在集合 $S$ 中，那么 $C_j$ 就可以作为序列中的一个数。于是对于每一个集合 $S$ 中的 $j$，都可以转移到 $i$。即
$$f_{i,S}=\min_{j\in S}\{f_{j,S-\{j\}}+dis_{i,C_j}\}$$
按秩转移的话就得倒过来想。如果与 $i$ 相邻的点 $j$ 不在目前的集合中，那么就可以转移到 $j$。从点 $i$ 开始 DFS，因为我们以 $i$ 为结尾定义的 $f$ 嘛，所以可以理解为往前转移，直到搜到 $S=2^K-1$ 停止并回溯。

$dis_{i,j}$ 数组仅用于记录 $C_i$ 到 点 $j$ 的距离，用朴素的 BFS 预处理就行。

[评测记录](https://atcoder.jp/contests/abc190/submissions/37418596) $\mathtt{275ms/98204KB/1250B}$
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int inf=1e9;
const int maxn=1e5+9;
const int maxk=20;

vector<int> G[maxn];
void add(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
}

int c[maxk];
int n,m,k;
int dis[maxk][maxn];

void bfs(int p)
{
	for(int i=1;i<=n;i++)
		dis[p][i]=inf;
	
	queue<int> q;
	dis[p][c[p]]=0;
	q.push(c[p]);
	
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(auto v:G[u])
		{
			if(dis[p][v]==inf)
			{
				dis[p][v]=dis[p][u]+1;
				q.push(v);
			}
		}
	}
}

int f[maxk][(1<<maxk)];
int dp(int i,int s)
{
	if(s==(1<<k)-1)
		return 0;
	
	if(f[i][s]!=-1)
		return f[i][s];
	
	f[i][s]=inf;
	for(int j=0;j<k;j++)
	{
		if(s&(1<<j))
			continue;
		f[i][s]=min(f[i][s],dp(j,s|(1<<j))+dis[j][c[i]]);
	}
	return f[i][s];
}

int main()
{
	memset(f,-1,sizeof(f));
	
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y; cin>>x>>y;
		add(x,y);
	}
	
	cin>>k;
	for(int i=0;i<k;i++)
		cin>>c[i];
	for(int i=0;i<k;i++)
		bfs(i);
	
	for(int i=0;i<k;i++)
		if(dis[i][c[0]]==inf)
			return cout<<-1<<endl,0;
	
	int ans=inf;
	for(int i=0;i<k;i++)
		ans=min(ans,dp(i,1<<i)+1);
	cout<<ans<<endl;
	
	return 0;
}
```
```


---

## 作者：loser_seele (赞：0)

部分内容参考自官方题解。

首先这个问题可以转化为最短哈密尔顿路板子题，也就是旅行商，不过限制了不需要经过所有点。

用类似的思路，观察到 $ K \leq 17 $，考虑状压。

首先设状态 $ dp_{S,i} $ 表示一条包含 $ S $ 中全部元素且在 $ i $ 结束的最短路径，则设给定的集合为 $ C $，答案即为所有 $ dp_{C,i} $ 中的最小值加一，这个是显然的。然后根据一个套路的方法转移：

$ dp_{\{i\},i}=0,dp_{S,i}=\min \{dp_{S-\{i\},j}+dis_{i,j}\} $，其中 $ dis_{i,j} $ 表示 $ i,j $ 两点间的距离，用一个朴素的 bfs 预处理任意两点间距离即可。

于是转移的时间复杂度为 $ \mathcal{O}(2^K \times K^2) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int INF=1e9;
const int maxn=2e6+10;
vector<int>cost;
vector<int>g[maxn];
vector<int>C;
int N, M,K;
vector<int> bfs(int s)
{
    cost.resize(N+1);
    for(int i=0;i<=N;i++)
    cost[i]=INF;
    cost[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(auto y : g[x]) 
        if(cost[y]>cost[x] + 1) 
        cost[y]=cost[x] + 1,q.push(y);
    }
    for(int i = 0; i < K; i++) 
    cost[i] = cost[C[i]];
    cost.resize(K);
    return cost;
}
int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        A--; 
        B--;
        g[A].push_back(B);
        g[B].push_back(A);
    }
    cin >> K;
    for(int i=1;i<=K;i++)
    {
        int c;
        cin >> c;
        c--;
        C.push_back(c);
    }
    vector<vector<int>> cost(K);
    for(int i = 0; i < K; i++) 
    cost[i] = bfs(C[i]);
    vector dp(1 << K, vector(K, INF));
    for(int i = 0; i < K; i++) 
    dp[1 << i][i] = 1;
    for(int sub = 1; sub < (1 << K); sub++) 
    for(int i = 0; i < K; i++) 
    if(sub & 1 << i)
    {
        int bit2 = sub ^ 1 << i;
        for(int j = 0; j < K; j++) 
        if(bit2 & 1 << j) 
        dp[sub][i]=min(dp[sub][i],dp[bit2][j] + cost[i][j]);
    }
    sort(dp.back().begin(),dp.back().end());
    int ans=dp.back()[0];
    if(ans==INF)
    cout<<-1;
    else
    cout<<ans;
}
```


---

## 作者：huyangmu (赞：0)

若当前要放进序列的是 $c_{i}$，序列里的最后一个数是 $c_{j}$，则需要放进 $dis_{c_{i},c_{j}}$ 本书，$dis_{c_{i},c_{j}}$ 表示至少要放几本书才能让 $c_{i}$ 与 $c_{j}$ 连通，考虑把相邻的关系看作边，建一张图，以每个 $c_{i}$ 为起点跑单源最短路，因为 $k \le 17$，所以复杂度是对的。

但是选书的顺序是不固定的，又因为 $k \le 17$，所以考虑状压，设 $dp_{i,j}$ 表示当前选第 $i$ 个，并且选书的状态为 $j$ 时最少放的书本数量。这个状压是比较版的，转移方程长这样。

```cpp
dp[i][j] = min(dp[i][j], dp[l][j-(1 << (i - 1))] + dis[c[i]][l])
```

建议多使用位运算，因为我就是不会用位运算在几个点上卡了好久。

### AC Code

```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e5 + 5;
const int K = (1 << 17) + 5;
const int M = 22;
int n, m, k, x, y, c[M], dis[N][M], dp[M][K], ans = LONG_LONG_MAX;
bool vis[N];
struct Node{
	int v, w;
	bool operator < (const Node &a) const{
		return w > a.w;
	}
};
vector<Node> G[N];
map<int, int> mp;
void dijkstra (int x, int mid){
	for (int i = 1; i <= 100000; ++i){
		vis[i] = 0;
		dis[i][mid] = 0x3f3f3f3f3f3f3f3f;
	}
	dis[x][mid] = 0;
	priority_queue<Node> q;
	q.push(Node{x, 0});
	while (!q.empty()){
		int tmp = q.top().v;
		q.pop();
		if (vis[tmp]) continue;
		vis[tmp] = 1;
		for (int i = 0; i < G[tmp].size(); ++i){
			int x = G[tmp][i].v, y = G[tmp][i].w;
			if (dis[x][mid] > dis[tmp][mid] + y){
				dis[x][mid] = dis[tmp][mid] + y;
				q.push(Node{x, dis[x][mid]});
			}
		}
	}
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i){
		cin >> x >> y;
		G[x].push_back(Node{y, 1});
		G[y].push_back(Node{x, 1});
	}
	cin >> k;
	for (int i = 1; i <= k; ++i){
		cin >> c[i];
		dijkstra(c[i], i);
	}
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 1; i <= k; ++i) dp[i][(1 << (i - 1))] = 1;
	for (int j = 1; j <= (1 << k) - 1; ++j){
		for (int i = 1; i <= k; ++i){
			for (int l = 1; l <= k; ++l){
				if (l == i || (!((1 << l - 1) & j)) || (!((1 << i - 1) & j))) continue;
				dp[i][j] = min(dp[i][j], dp[l][j-(1 << (i - 1))] + dis[c[i]][l]);
			}
		}
	}
	for (int i = 1; i <= k; ++i) ans = min(ans, dp[i][(1 << k) - 1]);
	cout << ((ans > 1e18) ? -1 : ans) << '\n';
	return 0;
}

---

