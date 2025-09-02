# [COTS 2019] 疏散 Sklonište

## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T2。$\texttt{4s,0.5G}$。

## 题目描述


给定 $N$ 个点 $M$ 条边的无向连通图，边有边权。有 $K$ 个关键点 $A_1,A_2,\cdots,A_K$，**容量**为 $S_1,S_2,\cdots,S_K$。

图中的居民要疏散。也就是说，你需要构造一个序列 $B_1,B_2,\cdots,B_N$，使得：

- $\forall 1\le i\le N$，$1\le B_i\le K$；
- 对于 $1\le i\le K$，定义 $\displaystyle \mathrm{cnt}_i=\sum_{1\le j\le N} [B_j=i]$，也就是 $i$ 在 $B$ 序列中出现的次数。则 $\mathrm{cnt}_i\le S_i$。

定义序列 $B$ 的**疏散时间**为 $\displaystyle \max_{1\le i\le N} \operatorname{dist}(i,A_{B_i})$，其中 $\operatorname{dist}(u,v)$ 指图中 $u,v$ 间最短路的长度。

求出疏散时间的最小值。保证 $\sum_i S_i\ge N$。


## 说明/提示


对于 $100\%$ 的数据，保证：
- $1\le N\le 10^5$；
- $N-1\le M\le 3\times 10^5$；
- $1\le K\le 17$；
- 给定图连通，无自环；
- $1\le w,S_i\le 10^9$；
- $1\le u,v,A_i\le N$；
- $S_i$ 两两不同；
- $\sum_i S_i\ge N$。


| 子任务编号 | $N\le $ | $M\le $ | $K\le$    | 得分 |  
| :--: | :--: |:--: |  :--: | :--: | 
| $ 1 $    | $ 100 $ |   $ 500 $   |  $5$ | $30$ |
| $ 2 $    | $ 10^5 $ |  $ 3\times 10^5 $   |  $10 $ | $30$ |
| $ 3 $    | $ 10^5 $ | $ 3\times 10^5 $   |  $17$ |  $40$ |

## 样例 #1

### 输入

```
5 5 2
1 2 1
1 3 3
2 3 4
3 4 1
4 5 1
1 10
4 2```

### 输出

```
3```

## 样例 #2

### 输入

```
7 8 3
1 2 5
2 3 3
3 4 5
1 4 1
4 5 7
5 6 2
6 7 1
4 7 4
3 3
7 3
6 2```

### 输出

```
5```

# 题解

## 作者：Purslane (赞：4)

# Solution

CSP-S 2024 RP++！

非常没有趣味的缝合怪题目。

- 先预处理每个关键点到其他点的最短路。
- 二分答案，转化为二分图匹配模型。
- 左部点是原图中的点，右部点是避难所，那么对于任何一个左部点集合 $S$，都要求 $|N(S)| \ge S$，其中 $N(S)$ 表示邻域。
- 显然枚举 $S$ 是不靠谱的，我们枚举 $T=N(S)$，也就是求左部点有多少个的邻域完全包含在 $T$ 内，可以使用高维前缀和解决。

复杂度 $O((nk+k2^k) \log V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MAXM=(1<<17)+10;
int n,m,k,vis[MAXN],pre[MAXM],a[20],s[20],dis[20][MAXN],sum[MAXM];
vector<pair<int,int>> G[MAXN];
struct Node {int u,dis;};
bool operator <(Node A,Node B) {return A.dis>B.dis;}
vector<int> calc(int s) {
	memset(vis,0,sizeof(vis));	
	priority_queue<Node> q;
	vector<int> ans;
	ffor(i,0,n) ans.push_back(0x3f3f3f3f3f3f3f3f);
	ans[s]=0,q.push({s,0});
	while(!q.empty()) {
		int u=q.top().u;
		q.pop();
		for(auto pr:G[u]) {
			int v=pr.first,w=pr.second;
			if(ans[u]+w<ans[v]) {
				ans[v]=ans[u]+w,q.push({v,ans[v]});
			}
		}
	}
	return ans;
}
int bel[MAXN];
int check(int w) {
	memset(bel,0,sizeof(bel)),memset(pre,0,sizeof(pre));
	ffor(i,1,k) ffor(j,1,n) if(dis[i][j]<=w) bel[j]|=(1<<i-1);
	ffor(i,1,n) pre[bel[i]]++;
	ffor(i,1,k) ffor(j,0,(1<<k)-1) if(j&(1<<(i-1))) pre[j]+=pre[j-(1<<i-1)];
	ffor(i,0,(1<<k)-1) if(pre[i]>sum[i]) return 0;
	return 1;
}
int bfind(int l,int r) {
	int ans=-1;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	ffor(i,1,m) {int u,v,w;cin>>u>>v>>w,G[u].push_back({v,w}),G[v].push_back({u,w});}
	ffor(i,1,k) cin>>a[i]>>s[i];
	ffor(i,1,(1<<k)-1) {ffor(j,1,k) if(i&(1<<j-1)) sum[i]+=s[j];}
	ffor(i,1,k) {
		auto vc=calc(a[i]);
		ffor(j,1,n) dis[i][j]=vc[j];
	}
	cout<<bfind(0,100000000000000);
	return 0;
}
```

---

## 作者：Reunite (赞：3)

无聊缝合题。

显然二分转化为判定，容易做 $k$ 遍 dij 求出每个点能合法地到达哪些点，显然原图可以是一个二分图的形式，问题转化为判定是否有完美匹配。

显然流是没有前途的，但是这个一脸就是很可以上 Hall 定理的样子。不是很好枚举经典形式中左边的点集并计算邻域，但是我们右边的点压缩一下只有 $k$ 个啊，正难则反，考虑枚举右边点集，那这个点集可以称为哪些左边点集的邻域呢？显然我们只需要关注点数最多的那个，也就是连边完全包含在 $S$ 内的，高维前缀和扫一遍就做完了。复杂度 $O(k(n\log (n+m)+2^k))$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define int long long
using namespace std;

int n,m,k;
int a[18];
int lim[18];
int f[200005];
int h[200005];
bool vis[300005];
int dis[18][300005];
vector <pair <int,int>> g[300005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void dij(int S,int dis[]){
	for(int i=1;i<=n;i++) dis[i]=1e18,vis[i]=0;
	dis[S]=0;
	priority_queue <pair <int,int>> q;
	q.push({0,S});
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto tmp:g[u]){
			int v=tmp.first,w=tmp.second;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({-dis[v],v});
			}
		}
	}
	return ;
}

inline bool check(int mid){
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		int x=0;
		for(int j=1;j<=k;j++)
			if(dis[j][i]<=mid) x|=1<<(j-1);
		if(!x) return 0;
		f[x]++;
	}
	for(int j=0;j<k;j++)
		for(int i=0;i<(1<<k);i++)
			if(i&(1<<j)) f[i]+=f[i^(1<<j)];
	for(int s=1;s<(1<<k);s++) if(h[s]<f[s]) return 0;
	return 1;
}

signed main(){
	in(n),in(m),in(k);
	for(int i=1;i<=m;i++){
		int u,v,w;
		in(u),in(v),in(w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	for(int i=1;i<=k;i++) in(a[i]),in(lim[i]);
	for(int i=1;i<=k;i++) dij(a[i],dis[i]);
	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=k;i++) vis[a[i]]=1;
	for(int s=1;s<(1<<k);s++){
		int ss=0;
		for(int i=1;i<=k;i++) if(s&(1<<(i-1))) ss+=lim[i];
		h[s]=ss;
	}
	int l=0,r=1e14,mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

一个社区有 $n$ 个地点，地点间有 $m$ 条双向道路，道路有长度（边权），每个居民的速度都是一个长度单位每时刻。

其中有 $k$ 个地点为营地（关键点），第 $i$ 个营地为 $A_i$，可以容纳至多 $S_i$ 个地点的居民。

假设现在发生自然灾害，需要所有地点的居民到营地避难，你需要求出假如所有居民同时行动，至少要多少时刻？

$1\leq n\leq 10^5,n-1\leq m\leq 3\times 10^5,1\leq k\leq 17$。

## 思路

我们先二分答案 $B$，转成判定性问题。

不难想到一个二分图建模的方法，对于每一个关键点 $A_i$，拆成 $S_i$ 个点 $A_{i1},A_{i2},\cdots,A_{iS_i}$，表示第 $A_i$ 个营地分成 $S_i$ 个小部分，每个小部分可以容纳一个人。

然后对于一个关键点 $A_i$ 和一个非关键点 $j$，对于任意的 $k$，若 $\mathrm{dis}(A_i,j)\leq B$，连边 $(j,A_{ik})$。则 $B$ 合法的充要条件为这张二分图存在非关键点集到已拆点的关键点集的完美匹配。

完美匹配似乎不好处理？我们可以考虑 Hall 定理：

> Hall 婚配定理：对于一个二分图，设其左部点集为 $V_1$，右部点集为 $V_2$，且 $|V_1|\leq |V_2|$，令 $N(S)$ 表示一个点集 $S$ 的邻域（即 $S$ 中每个点的邻域点集之并）。则该二分图存在 $V_1$ 到 $V_2$ 的完美匹配（即，$V_1$ 中没有点不在匹配中）的充要条件为对于任意的 $S\subseteq V_1$，均有 $|S|\leq |N(S)|$。

如何应用 Hall 定理？枚举 $S$ 是不可行的，枚举 $N(S)$ 看上去是不可行的，实际上是可行的，因为任何一个 $S$ 的邻域虽然点可能很多，但都是包含了一些关键点拆成的所有点，可以枚举这个关键点集。

我们枚举关键点集 $T$，现在的问题就变成了最大的点集 $S$ 使得 $N(S)=T$。可以考虑高维前缀和的方法。处理出每个点的邻域状压，然后就是一个高维前缀和模板啦（如果你不会这玩意，可以看成一个状压 dp）！

至于 $\mathrm{dis}$ 信息，以每个关键点为起点跑 $k$ 遍 dijkstra 求最短路就好了。

时间复杂度 $O((nk+k2^k)\log B+nk\log n)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5, M = 19, M_ = (1 << 17) + 5;
int n, m, k;
vector<pair<int,int> > g[N];
struct zak{
    int a, s;
} key[M];
int dis[N][M];
bool vis[N];
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;

void dijkstra(int id){
    fill(vis + 1, vis + n + 1, 0);
    for(int i=1;i<=n;i++) dis[i][id] = 1e18;
    dis[key[id].a][id] = 0;
    q.emplace(0, key[id].a);
    while(!q.empty()){
        int u = q.top().second; q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(auto [v, w] : g[u]){
            if(dis[v][id] > dis[u][id] + w){
                dis[v][id] = dis[u][id] + w;
                q.emplace(dis[v][id], v);
            }
        }
    }
}

int f[M_];

bool check(int B){
    for(int i=0;i<(1 << k);i++) f[i] = 0;
    for(int i=1;i<=n;i++){
        int tag = 0;
        for(int j=1;j<=k;j++){
            if(dis[i][j] <= B) tag |= (1 << (j - 1));
        }
        f[tag]++;
    }
    for(int i=1;i<=k;i++){
        for(int j=0;j<(1 << k);j++){
            if(j & (1 << (i - 1))) f[j] += f[j ^ (1 << (i - 1))];
        }
    }
    for(int i=0;i<(1 << k);i++){
        int val = 0;
        for(int j=1;j<=k;j++){
            if(i & (1 << (j - 1))) val += key[j].s;
        }
        if(f[i] > val) return false;
    }
    return true;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m >> k;
    for(int i=1,u,v,w;i<=m;i++){
        cin >> u >> v >> w;
        g[u].emplace_back(v, w); g[v].emplace_back(u, w);
    }
    for(int i=1;i<=k;i++){
        cin >> key[i].a >> key[i].s;
        dijkstra(i);
    }
    int L = 0, R = 1e18;
    while(L < R){
        int mid = (L + R) >> 1;
        if(check(mid)) R = mid;
        else L = mid + 1;
    }
    cout << L << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：gdf_yhm (赞：2)

[P11225](https://www.luogu.com.cn/problem/P11225)

基本同 [arc106e](https://www.luogu.com.cn/problem/AT_arc106_e)。

[my blog](https://yhddd123.github.io/post/p11225-ti-jie/)

### 思路

预处理 $k$ 个关键点的单源最短路。二分答案，就知道点 $u$ 能去哪些关键点。可以网络流，连边 $(S,u,1)$，$(a_i,T,val_i)$，如果 $dis_{i,u}\le x$ 连边 $(u,a_i,1)$，检查最大流是否为 $n$。

用 Hall 定理判定，对于二分图 $G(V1,V2,E)(\lvert V1\rvert\le \lvert V2\rvert)$，$V1$ 存在完美匹配的充要条件为 $\forall X\subseteq V1,\lvert X\rvert\le\lvert N(X)\rvert$，其中 $N(X)$ 是与 $X$ 中点有边的点集。

状压 $k$ 个关键点，枚举 $N(X)$ 对应的子集为 $s$ ，$X$ 是所有使得 $\forall dis_{i,u}\le x,i\in s$ 的 $u$，高维前缀和计算。

### code

```cpp
int n,m,k;
int a[17],val[17];
int head[maxn],tot;
struct edge{
	int nxt,to,w;
}e[maxn*6];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[17][maxn];
bool vis[maxn];
priority_queue<pii> q;
int sum[1<<17],dp[1<<17];
bool check(int x){
	for(int s=1;s<(1<<k);s++){
		sum[s]=sum[s^(s&(-s))]+val[__builtin_ctz(s&(-s))];
	}
	for(int s=0;s<(1<<k);s++)dp[s]=0;
	for(int i=1;i<=n;i++){
		int s=0;
		for(int j=0;j<k;j++)if(dis[j][i]<=x)s|=1<<j;
		dp[s]++;
	}
	for(int i=0;i<k;i++){
		for(int s=0;s<(1<<k);s++){
			if(s&(1<<i))dp[s]+=dp[s^(1<<i)];
		}
	}
	for(int s=0;s<(1<<k);s++)if(dp[s]>sum[s])return 0;
	return 1;
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	for(int i=0;i<k;i++)a[i]=read(),val[i]=read();
	for(int i=0;i<k;i++){
		mems(dis[i],0x3f),mems(vis,0);
		dis[i][a[i]]=0,q.push({0,a[i]});
		while(!q.empty()){
			int u=q.top().se;q.pop();
			if(vis[u])continue;vis[u]=1;
			for(int ii=head[u];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				if(dis[i][v]>dis[i][u]+e[ii].w){
					dis[i][v]=dis[i][u]+e[ii].w;
					q.push({-dis[i][v],v});
				}
			}
		}
		// for(int j=1;j<=n;j++)cout<<dis[i][j]<<" ";cout<<"\n";
	}
	int l=0,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%lld\n",res);
}
```

---

## 作者：XZhuRen (赞：0)

这个题最难的貌似是高维前缀和板子……

这个问题要求的是最大值最小，考虑二分。

先跑最短路。

二分答案，按照限制建出二分图，左边是图上的每一个点，右边是关键点，**左部点每一个点匹配一个**，右部点每一个点最多匹配 $S_{i}$ 个。

根据 Hall 定理，我们将每一个右部点视为拆成 $S_{i}$ 个等价的点，则考虑对于左部点判断完美匹配（因为我们没有要求右部点完美匹配）。

考虑这张图并没有什么优美性质，只能从右部点入手，代入 Hall 定理公式：

$X\le N(X)$

这是一个并集形式，代表确定 $N(X)$ 时，我们的 $X$ 就是相邻点都在 $N(X)$ 集合里的所有点的集合。

所以对于每一个点求出来相邻点集合记为 $base_{i}$，放到高维前缀和里边就可以对每一个 $N(X)$ 求答案了。

二分即判断是否有 $X>N(X)$。

Code:


```cpp
bool check(ll1 lim){
	memset(f,0,sizeof(f));
	for(int u=1;u<=n;u++){
		base[u]=0;
		for(int i=1;i<=K;i++)
			if(dis[i][u]<=lim)base[u]^=(1<<(i-1));
		f[base[u]]++;
	}//处理出每一个base
	for(int k=0;k<K;k++){
    	for(int s=0;s<SK;s++){
        	if((s>>k)&1)f[s]+=f[s^(1<<k)];
    	}
    }//高维前缀和
    ll1 sm;
    for(int s=0;s<SK;s++){//判断是否有N(S)<S
    	sm=0;
    	for(int i=1;i<=K;i++){
    		if((s>>(i-1))&1)sm+=S[i];
    	}
  		if(sm<f[s])return 0;
    }
	return 1;
}
```

---

