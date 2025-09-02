# [ABC338F] Negative Traveling Salesman

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_f

$ N $ 頂点 $ M $ 辺の重み付き単純有向グラフがあります。 頂点には $ 1 $ から $ N $ までの番号が付けられていて、$ i $ 本目の辺は頂点 $ U_i $ から頂点 $ V_i $ に伸びる重み $ W_i $ の辺です。 ここで、重みは負の値を取ることもありますが、負閉路は存在しません。

全ての頂点を一度以上通るようなウォークが存在するかどうか判定し、存在するならば通る辺の重みの総和の最小値を求めてください。 ただし、同じ辺を複数回通る場合、その辺の重みは通った回数分加算されるものとします。

なお、「全ての頂点を一度以上通るようなウォーク」とは、頂点の列 $ v_1,v_2,\dots,v_k $ であって以下の条件を共に満たすもののことを言います。

- すべての $ i\ (1\leq\ i\leq\ k-1) $ について、頂点 $ v_i $ から頂点 $ v_{i+1} $ に伸びる辺が存在する
- すべての $ j\ (1\leq\ j\leq\ N) $ について、$ v_i=j $ を満たす $ i\ (1\leq\ i\leq\ k) $ が存在する

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 20 $
- $ 1\leq\ M\ \leq\ N(N-1) $
- $ 1\leq\ U_i,V_i\ \leq\ N $
- $ U_i\ \neq\ V_i $
- $ (U_i,V_i)\ \neq\ (U_j,V_j)\ (i\neq\ j) $
- $ -10^6\leq\ W_i\ \leq\ 10^6 $
- 与えられるグラフに負閉路は存在しない
- 入力は全て整数
 
### Sample Explanation 1

頂点 $ 2\rightarrow\ 1\rightarrow\ 2\rightarrow\ 3 $ の順に辿ると、全ての頂点を一度以上通ることができ、通る辺の重みの総和は $ (-3)+5+(-4)=-2 $ になります。 これが最小です。

### Sample Explanation 2

全ての頂点を一度以上通るようなウォークは存在しません。

## 样例 #1

### 输入

```
3 4
1 2 5
2 1 -3
2 3 -4
3 1 100```

### 输出

```
-2```

## 样例 #2

### 输入

```
3 2
1 2 0
2 1 0```

### 输出

```
No```

## 样例 #3

### 输入

```
5 9
1 2 -246288
4 5 -222742
3 1 246288
3 4 947824
5 2 -178721
4 3 -947824
5 4 756570
2 5 707902
5 1 36781```

### 输出

```
-449429```

# 题解

## 作者：Genius_Star (赞：5)

### 思路：

~~c，赛时没写 Floyd……~~

看到 $N \le 20$，一眼状压。

定义 $dp_{S,i}$ 表示当前在 $i$ 号点，点集状态为 $S$ 的最短路径，定义 $f_{i,j}$ 表示 $i$ 号点到 $j$ 号点的最短路径。（可以 Floyd 求）

则转移为：

$$dp_{S,x}=\min_{y \in T_S} \Big( [y \ne x] dp_{S-2^{y-1},y} + f_{y,x} \Big)$$

其中 $T_S$ 表示 $S$ 转化为二进制为 $1$ 的位的集合。

时间复杂度为 $O(2^N \times N^2 + N^3)$。

**注意判边界且不存在的状态就不要去转移了。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=25,M=1ll<<22;
const ll INF=1e16;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,ans=INF;
ll f[N][N],dp[M][N];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
		f[i][j]=INF;
	for(int u,v,i=1;i<=m;i++){
		u=read(),v=read();
		f[u][v]=read();
	}
	for(int k=1;k<=n;k++)
	  for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		  f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    for(int i=1;i<(1<<n);i++)
      for(int x=1;x<=n;x++)
        dp[i][x]=INF;
    for(int x=1;x<=n;x++)
      dp[1ll<<(x-1)][x]=0;
    for(int i=1;i<(1<<n);i++){
    	for(int x=1;x<=n;x++){
    		if(!(i&(1<<(x-1))))
    		  continue;
    		for(int y=1;y<=n;y++){
    			if(!(i&(1<<(y-1)))||x==y||dp[i^(1<<(x-1))][y]==INF||f[y][x]==INF)
    			  continue;
    			dp[i][x]=min(dp[i][x],dp[i^(1<<(x-1))][y]+f[y][x]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	  ans=min(ans,dp[(1ll<<n)-1][i]);
	if(ans==INF)
	  puts("No");
	else
	  write(ans);
	return 0;
}
```


---

## 作者：Shunpower (赞：2)

为啥这年头 ABC 喜欢出裸题？

注意到 $n\leqslant 20$，时限 $6$ 秒，考虑状压 dp。

$f_{i,mask}$ 表示目前在点 $i$，已经到达过的点的点集状态为 $mask$ 的最小边权。

考虑转移。容易得到：

$$
f_{j,mask|2^j}\gets f_{i,mask}+dis_{i\to j}(j\notin mask\land i\in mask) 
$$

其中 $dis_{i\to j}$ 表示 $i\to j$ 的最短路，容易用 Floyd 求得。

你先别急，还要考虑是否可能存在 $j\in mask\land i\in mask$ 导致答案更优的情况。

若现在 $mask$ 不是 $2^n-1$，即所有点没有被走完，那么很明显，即便有这样一条路径，它也要为我们走到下一个点服务。所以在 $dis$ 当中已经做了贡献。

而对于所有点都已经被走完了的情况，假设我们从终点再走到一个点导致答案更小（如图中到达“终点”之后还走了 $-w_1,-w_2$ 的边），那么我们的路径上一定构造出来了一个环，环上可能会有一些重叠部分（如下图 $-w_2$ 的边）。而对于这种形态的路径，我们考虑先跳过重叠部分，再绕环一圈，就可以把重叠部分通过 $dis$ 分开计入，这样就不存在环了（如下图直接从起点跳 $3$ 条边的操作）。

![](https://cdn.luogu.com.cn/upload/image_hosting/gc6vw7kj.png)

特别地，如果整条路径是一个完全的简单环，由于不存在负环，破掉最大的一条正权边化环为链答案显然会更优。

有了这些证明，[代码](https://atcoder.jp/contests/abc338/submissions/49732146)就是简单的状压 dp 了，这里不再赘述。

---

## 作者：Mu_leaf (赞：2)

## [思路]
第一眼发现数据范围 $N \leq 20$ 时限 6s 就可以想到状压 dp。

定义 $f_{i,j}$ 为已经拜访过了的点的状态最后一个到的点为 $j$。

那么状态转移方程就是：

$$ f_{i|(1<<(k-1),k}=\min(f_{i|(1<<(k-1),k},f_{i,j}+dis_{i,j})$$

其中 $k$ 为枚举的下一个要去的点，$j$ 为当前状态到达的最后一个点，$dis_{i,j}$ 表示点 $i$ 到点 $j$ 的最短路。

由于有负权，所以可以用我们死去的 spfa 求负权最短路来预处理 $dis_{i,j}$

然后就完了。

Code:
--------

```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1000000000000
using namespace std;
const int N=25,Mx=(1ll<<21);
int f[Mx][N];
int vis[N][N],dis[N][N],w[N];
int n,m,ans=inf;
void fh(int s){
	queue<int> q;
	q.push(s);
//	memset(vis,0,sizeof(vis));
	w[s]=1;
	dis[s][s]=0;
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=1;i<=n;++i){
			if(!w[i]&&dis[s][i]>dis[s][u]+vis[u][i]){
				dis[s][i]=dis[s][u]+vis[u][i];
				q.push(i);
			}
		}
		w[u]=0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) vis[i][j]=dis[i][j]=inf;
	}
	for(int i=1,u,v,w;i<=m;i++){
		cin >> u >> v >> w;
		vis[u][v]=w;
	}
	
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			f[i][j]=inf;
		}
	}
	for(int i=1;i<=n;i++) fh(i);
	for(int i=1;i<=n;i++) f[(1<<(i-1))][i]=0; 
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if(!((i>>(j-1))&1)) continue;
			for(int k=1;k<=n;k++){
				if(k==j) continue;
				if(((i>>(k-1))&1)) continue;
				f[i|(1<<(k-1))][k]=min(f[i][j]+dis[j][k],f[i|(1<<(k-1))][k]);
			}
		}
	}
//	cout << f[(1<<n)-1][3] << "\n"; 
	for(int i=1;i<=n;i++){
		ans=min(ans,f[(1<<n)-1][i]);
	}
	if(ans>1e9)puts("No");
	else cout << ans;
	return 0 ;
}




```


---

## 作者：donaldqian (赞：2)

## 题意简述
有一个 $N$ 个点 $M$ 条边的 __有向图__，第 $i$ 条边从 $U_i$ 连向 $V_i$，边权为 $W_i$。

边权可能为负，但 __不会有负环__。

判断是否有一条路径经过每个节点 __至少__ 一次，如果存在，最小化经过边权总和。

如果一条边被经过几次，边权也会被累加几次。

$2 \le N \le 20$。

## 思路
从数据范围入手，显然考虑状压。[什么是状压？](https://oi-wiki.org/dp/state/)

设 $dp_{st,\ pl}$ 表示当前访问状态为 $st$，位置为 $pl$ 的最小边权和。

那么，转移方程即为 $dp_{st\ |\ 2^{to},\ to} = \displaystyle\min_{to = 1} ^ n (dp_{st,\ pl}\ +\ dis_{pl,\ to})$。

其中 $dis_{pl,\ to}$ 指从 $pl$ 到 $to$ 的最短路长，用 Floyd 算法即可解决。

时间复杂度 $\mathcal O(n^3+2^nn^2)$。

## Code
```cpp
// 下标从零开始记位运算更方便
memset (dp, 0x3f, sizeof dp);
memset (dis, 0x3f, sizeof dis);
for (int i = 0; i < n; i++) dis[i][i] = 0;
for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
for (int i = 1, u, v, w; i <= m; i++)
{
	scanf("%lld%lld%lld", &u, &v, &w);
	dis[u - 1][v - 1] = w;
}

// Floyd
for (int k = 0; k < n; k++)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dis[i][j] = min (dis[i][j], dis[i][k] + dis[k][j]);
		}
	}
}

for (int st = 1; st < (1 << n); st++)
{
	for (int pl = 0; pl < n; pl++) if (st >> pl & 1) // 如果 st 中甚至没有访问 pl 当然不合法
	{
		for (int to = 0; to < n; to++)
		{
			dp[st | (1 << to)][to] = min (dp[st | (1 << to)][to], dp[st][pl] + dis[pl][to]);
		}
	}
}
ans = (int)1e18;
for (int pl = 0; pl < n; pl++) ans = min (ans, dp[(1 << n) - 1][pl]);
if (ans == (int)1e18 || ans == dp[(1 << N) - 1][N - 1]) puts ("No");
else printf("%lld", ans);
```

---

## 作者：xiaofu15191 (赞：1)

审题。给你一张简单有向图，可能有**负权边**，但保证**无负环**，需要你将图上每一个点都遍历到一次，**允许走重复的边或点**，求最小边权和。注意边权每走一次都会被加入答案。

一开始想到的好像是分层图之类的思路？不过很快就放弃了。

看到了 $2 \leq n \leq 20$。$O(n!)$ 的爆搜肯定行不通。考虑 $O(2^n \times n^2)$ 的状压 DP。

预处理出点与点之间的最短路，然后直接状压即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const long long INF=1145141919810;
long long n,m,dis[30][30],f[2000000][30];
int main()
{
	memset(dis,0x3f,sizeof(dis));
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=m;i++)
	{
		long long from,to,v;
		scanf("%lld%lld%lld",&from,&to,&v);
		dis[from][to]=v;
	}
	for(long long k=1;k<=n;k++)
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	memset(f,0x3f,sizeof(f));
	for(long long i=1;i<=n;i++) f[1<<(i-1)][i]=0;
	for(long long i=0;i<(1<<n);i++)
		for(long long j=1;j<=n;j++)
			if(i&(1<<(j-1)))
				for(long long k=1;k<=n;k++)
					if(!(i&(1<<(k-1))))
						f[i|(1<<(k-1))][k]=min(f[i|(1<<(k-1))][k],f[i][j]+dis[j][k]);
	long long ans=INF;
	for(long long i=1;i<=n;i++)
		ans=min(ans,f[(1<<n)-1][i]);
	if(ans==INF) printf("no\n");
	else printf("%lld\n",ans);
}
```

---

## 作者：WhisperingWillow (赞：1)

看数据范围直接考虑状压。

先用全源最短路 $n^3$ 求出两点最短距离 $dis$。

设立状态 $dp_{S,i}$ 表示走过了点集 $S$，现在走到了 $i$，枚举转移的点 $j$ 暴力转移即可。

时间复杂度 $\mathcal O(n^3+2^n\cdot n)$。


```
	n=read(),m=read();
	memset(dis,0x3f,sizeof dis);
	f(i,0,n-1) dis[i][i]=0;
	f(i,1,m){
		int u=read()-1,v=read()-1;
		//dis[u][v];
		dis[u][v]=read();
	}
	--n;
	f(k,0,n){
		f(i,0,n){
			f(j,0,n){
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
			}
		}
	}
	memset(dp,0x3f,sizeof dp); 
	f(i,0,n) dp[1<<i][i]=0;
	f(i,1,(1<<(n+1))-1){
		f(j,0,n){
			if((~i)&(1<<j)) continue;
			if(dp[i][j]>=1e10) continue;
			f(k,0,n){
				if(i&(1<<k)) continue;
				if(dis[j][k]>=1e10) continue; 
				toMin(dp[i|(1<<k)][k],dp[i][j]+dis[j][k]);
			}	
    //        return 0;
		}
	}
//    return 0;
	int ans=1e18; 
	f(i,0,n) toMin(ans,dp[(1<<n+1)-1][i]); 
    if(ans<=1e15)writed(ans);
    else puts("No");
```

---

## 作者：WilliamFranklin (赞：1)

### 主要思路

这道题一眼看上去就感觉是道动态规划，然后看了一眼范围 $0 \le N \le 20$，那铁定状压了。

考虑设 $f_{i, j}$，若 $i$ 在二进制下，第 $k$ 位为 $1$，则代表 $k$ 这个点被访问过，那么，$f_{i, j}$ 就表示在遍历状态为 $i$ 时，最后一个访问的点为 $j$ 的最小代价。

关于转移部分具体看下代码（都能做到第六题了，应该会状压吧）。

但是我们要注意：一个点可以经过好多次，那么这就可能出现一直更新的情况，但是题目中说了，没有负环，所以为了转移彻底，只用每一次都重复执行 $n$ 次转移过程即可，具体看下代码。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 22, M = (1 << N);
long long f[M][N];
int n, m;
vector<pair<int, long long> > G[N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	For(i, 1, m) {
		int a, b, c;
		cin >> a >> b >> c;
		G[a].push_back(mp(b, c));
	}
	int tot = 0;
	for (int i = 1; i <= n; i++) tot += (1 << i);
	for (int i = 0; i <= tot; i++) for (int j = 1; j <= n; j++) f[i][j] = 1e18;
		For(i, 1, n) f[1 << i][i] = 0;
	for (int i = 1; i <= tot; i++) {
		if (i & 1) continue;
		for (int l = 1; l <= n; l++)
		for (int j = 1; j <= n; j++) {
			if (((1 << j) & i)) {
				for (auto k : G[j]) {
					f[i | (1 << k.x)][k.x] = min(f[i | (1 << k.x)][k.x], f[i][j] + k.y);
				}
			}
		}
	}
	long long minn = 1e18;
	for (int i = 1; i <= n; i++) {
		minn = min(minn, f[tot][i]);
	}
	if (minn >= 1e10) cout << "No";
	else cout << minn;
	return 0;
} 
```

### 谢谢观看

---

## 作者：harmis_yz (赞：1)

## 分析

考虑状压。

定义状态函数 $f_{i,j}$ 表示在经过点的情况为 $i$ 且最后停在点 $j$ 的最小花费。那有：$f_{i,j}=\min\{f_{i',k}+w_{k \to j}|k\to j\}$。然后就过不了样例一。根据样例一，可以发现 $f_{3,2}=f_{2,2}+w_{2\to 1}+w_{1 \to 2}$。也就是说我们在原本已经走完了状态 $i$ 之后，可能在里面走还会有更优的。其实这个你跑 $n$ 遍转移，在原有的转移方程上再加上一个与 $f_{i,k}$ 的取最小值就行了。很牛，能冲过去。

复杂度 $O(n^32^{n})$。

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

const int N=1e5+10,M=1<<20|1,K=25;
int n,m,k;
int f[M][K];
int vis[K][N],dis[K][N];

il void solve(){
	memset(dis,0x3f,sizeof(dis)),
	memset(vis,0,sizeof(vis)),
	memset(f,0x3f,sizeof(f));
	n=read(),m=read();
	for(re int i=1,a,b,c;i<=m;++i)
		a=read(),b=read(),c=read(),
		vis[a][b]=1,dis[a][b]=c;
	for(re int i=1;i<=n;++i) f[(1<<(i-1))][i]=0,f[0][i]=0;
	for(re int i=1;i<(1<<n);++i){
		for(int ks=1;ks<=n;++ks)
		for(re int a=n;a>=1;--a){
			if(!((i>>(a-1))&1)) continue;
			for(re int b=n;b>=1;--b){
				if(!((i>>(b-1))&1)) continue;
				if(!vis[b][a]) continue;
				int lst=i-(1<<(a-1));
				f[i][a]=min(f[i][a],f[lst][b]+dis[b][a]);
				f[i][a]=min(f[i][a],f[i][b]+dis[b][a]);
			}
		}		
	}
	int Min=1e18;
	for(re int i=1;i<=n;++i) Min=min(Min,f[(1<<n)-1][i]);
	if(Min>1e9) printf("No\n");
	else printf("%lld\n",Min);
	return ;      
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：MrPython (赞：0)

~~ABC 没题出了吗……全是大典~~

1. 用邻接矩阵存下图
2. 跑一遍 floyd 求出任意两点间的距离
3. 同 [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)。

---
吐槽结束，还是具体说说状压怎么做吧。
设计状态：$F(i,j)$ 表示当前在 $j$ 点，状态为 $i$ 时代价的最小值。其中状态用二进制压位，第 $p$ 个二进制位为 $1$ 表示已经访问过 $p$ 点，为 $0$ 表示没有访问过。

假设当前想要求 $F(i,j)$。我们可以枚举 $k$ 点，从该点走到这里。但是 $k$ 有限制条件：
- $j\neq k$，不能从当前点走到当前点；
- $i$ 的第 $k$ 个比特位为 $1$，必须之前走过第 $k$ 个点才能从那走过来。

满足条件即可列出转移方程：$F(i,j)=\mathop{\min}_{\text{满足上述条件的所有} k} F(i \text{去除第} j \text{位},k)+d(k,j)$

代码如下：
```
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;
    cin>>n>>m;
    vector<vector<int>> dst(n,vector<int>(n,numeric_limits<int>::max()/2));
    while (m--){
        size_t u,v;int w;
        cin>>u>>v>>w;--u,--v;
        dst[u][v]=w;
    }
    for (size_t k=0;k<n;++k) for (size_t i=0;i<n;++i) for (size_t j=0;j<n;++j)
        dst[i][j]=min(dst[i][j],dst[i][k]+dst[k][j]);
    vector<vector<int>> dp(1<<n,vector<int>(n,numeric_limits<int>::max()/2));
    for (size_t i=0;i<n;++i) dp[1<<i][i]=0;
    for (size_t i=0;i<(1<<n);++i) if (__builtin_popcount(i)>1)
        for (size_t j=0;j<n;++j) if ((i|(1<<j))==i)
            for (size_t k=0;k<n;++k) if (k!=j&&(i&(1<<k)))
                dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+dst[k][j]);
    int ans=numeric_limits<int>::max();
    for (size_t i=0;i<n;++i) ans=min(ans,dp[(1<<n)-1][i]);
    if (ans>=numeric_limits<int>::max()/8) cout<<"No"; else cout<<ans;
    return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc338_f)
### 题解
状压 DP 水题，考虑状压 DP（雾。

设建好的图有向边 $\lang i,j\rang$ 的边权为 $g_{i,j}$，不存在时，$g_{i,j}=+\infty$。

令 $f_{i,s}$，表示经过了以 $s$ 为已经经过的节点集合，且目前来到了节点 $i$。

不难写出转移方程 $f_{i,s}=\displaystyle\min_{j\in s}\{f_{j,s-\{i\}},f_{j,s}\}$。

但是，上面的方程复杂度是 $O(n^32^n)$，在 AT 的评测机和 6s 的时限下，会 TLE 两个点。

于是，考虑卡常。

根据一个无负环的图中最短路径不超过节点数 $-1$，所以我们可以把上述转移方程的维护次数改为 $popcount(s)$，还有集合中的点可以预处理，至此，这题就可以卡过了。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 30,M = 1 << 21;
const LL INF = 0x3f3f3f3f3f3f3f3f;
int n,m;
int cnt[M];
vector <int> v[M];
LL g[N][N];
LL f[N][M];
int main () {
    cin >> n >> m;
    for (int i = 0;i < 1 << n;i++) {
    	for (int j = 1;j <= n;j++) {
    		if (i >> j - 1 & 1) {
    			cnt[i]++;
    			v[i].pb (j);
			}
		}
	}
    memset (g,0x3f,sizeof (g));
    while (m--) {
    	int a,b,w;
    	cin >> a >> b >> w;
    	tomin (g[a][b],w);
	}
    memset (f,0x3f,sizeof (f));
    for (int i = 1;i <= n;i++) f[i][1 << i - 1] = 0;
    for (int k = 0;k < 1 << n;k++) {
        for (int i : v[k]) {
  			for (int j : v[k]) tomin (f[i][k],f[j][k - (1 << i - 1)] + g[j][i]);
        }
    	for (int _ = 1;_ <= cnt[k];_++) {
	        for (int i : v[k]) {
	            for (int j : v[k]) tomin (f[i][k],f[j][k] + g[j][i]);
	        }
	    }
    }
    LL ans = INF;
    for (int i = 1;i <= n;i++) tomin (ans,f[i][(1 << n) - 1]);
    if (ans > INF / 2) puts ("No");
    else cout << ans << endl;
    return 0;
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
$n \le 20$ 个点，$m$ 条边简单带权有向图，无负环，求最短的经过所有点至少一次的路径长度。


## Sol
状压dp。

先 Floyd 求出全源最短路，令 $f[S][i]$ 表示已经经过了 集合 $S$ 中的点，到达点 $i$ 的最短路，有转移方程：

$$f[S \cup j][j]=\min(f[S \cup j][j],f[S][i]+d[i][j])$$

答案在全集中取 $\min$ 即可。

然后就是一些细节问题，比如无解情况答案应该是 `inf`，但因为负边权比 `inf` 小。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 22
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const double eps=1e-6;
ll d[N][N];
ll f[(1<<N)][N];
ll n,m;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    memset(d,0x3f,sizeof(d));
    memset(f,0x3f,sizeof(f));
    ll inf=d[0][0];
    for(int i=0;i<n;i++)d[i][i]=f[(1<<i)][i]=0;
    for(int i=1;i<=m;i++){
        ll x,y,z;
        cin>>x>>y>>z;
        x--,y--;
        d[x][y]=z;
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                d[i][j]=min(d[i][k]+d[k][j],d[i][j]);
            }
        }
    }
    ll res=inf;
    for(int s=1;s<(1<<n);s++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                f[s|(1<<j)][j]=min(f[s][i]+d[i][j],f[s|(1<<j)][j]);
                if((s|(1<<j))==((1<<n)-1))res=min(res,f[s|(1<<j)][j]);
            }
        }
    }
    if(res*2>inf){//注意这里，因为有负边权,无解情况可能走着走着就比inf小了。
        cout<<"No\n";
    }else cout<<res<<endl;
    return 0;
}
```

---

