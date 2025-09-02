# Traveling Graph

## 题目描述

You are given undirected weighted graph. Find the length of the shortest cycle which starts from the vertex 1 and passes throught all the edges at least once. Graph may contain multiply edges between a pair of vertices and loops (edges from the vertex to itself).

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
3 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2
1 2 3
2 3 4
```

### 输出

```
14
```

# 题解

## 作者：黎明行者 (赞：5)

【分析】

无向图欧拉回路的定理大家应该都知道了，存在欧拉回路的充要条件是不存在度数为奇数的点（以下简称奇点，非奇点称为偶点）。这道题要求一个“非欧拉回路”，也就是可以重复经过同一条边。

为了理解下面的东西，我们要先回顾一下欧拉回路定理的证明。对于一条欧拉回路，每一次“进入”一个点，一定对应着一次从这个点的“走出”。进去的时候走一条边，出来又走另外一条边，所以度数一定是偶数。

对于任意一个无向图，所有节点的度数和一定是偶数，所以奇点数一定是偶数。

考虑奇点是怎么来的：一个没有边的图，一定没有奇点。每增加一条边，这条边两端的两点的奇偶性会反转（奇点变偶点，偶点变奇点）。

如果一个图的所有**边**是联通的且没有奇点，那么答案显然就是所有边权值的和，因为答案就是欧拉回路。
如果存在奇点，那么一定是成对存在的。一个奇点连接的边当中至少有一条会被走两次，这一结论想一下欧拉回路定理的证明就不难理解了。

在有一条边走了两次的情况下，我们依旧可以把它转化成欧拉回路的问题。走了两次，就可以看作把这条边复制了一条副本出来，原件和副本各走了一遍。

这样一来，问题就转化成了：给这张图复制若干条边，使得它存在欧拉回路，同时要让复制的边的权重和尽可能小。

奇点周围的边至少要被复制一条，原来的奇点会变成偶点。被复制的那一条边的另一端的点如果原来是偶点，则变成奇点（这相当于奇点沿边移动了），如果另一个点是奇点，则两个奇点会一同变成偶点。要消除一个奇点，势必和另外一个奇点一并消除，而这一过程可以看作一个奇点沿着边走到了另外一个奇点那里。所以需要求最短路，对于这道题当然用Floyd最方便了。

然后就是暴力出奇迹。我们要让奇点成对消失，可以暴搜所有奇点配对方案。每一种方案的答案就是总边权加每一对之间的最短路长度之和。

【代码注意事项】

一定要判断边的连通性，可以在Floyd之后判断所有度数不为零的点是否可以和1连通，如果不连通则无解。

【代码】

```cpp
#include <bits/stdc++.h>

typedef long long ll;
const int N=21;
const ll INF=0x3f3f3f3fLL;
int n,m;
ll dist[N][N];
int deg[N],on[N],onp=0;
ll ans=INF,tans=0;
bool vis[N];
void init()
{
	memset(dist,0x3f,sizeof(dist));
	memset(deg,0,sizeof(deg));
	memset(vis,0,sizeof(vis));
}
bool floyd()
{
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (dist[i][j]>dist[i][k]+dist[k][j])
					dist[i][j]=dist[i][k]+dist[k][j];
	for (int i=2;i<=n;i++) if (deg[i] && dist[1][i]>=INF) return false;
	return true;
}

void solve(int x)
{
	if (x>onp) return (void)(ans=std::min(ans,tans));
	if (vis[x]) return (void)(solve(x+1));
	vis[x]=true;
	for (int i=1;i<=onp;i++) if (i!=x && !vis[i])
	{
		tans+=dist[on[x]][on[i]];
		vis[i]=true;
		solve(x+1);
		tans-=dist[on[x]][on[i]];
		vis[i]=false;
	}
	vis[x]=false;
}
int main()
{
	init();
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) dist[i][i]=0;
	ll wsum=0;
	while (m--)
	{
		int a,b; ll c; scanf("%d%d%lld",&a,&b,&c);
		if (dist[a][b]>c) dist[a][b]=dist[b][a]=c;
		deg[a]++; deg[b]++;
		wsum+=c;
	}
	for (int i=1;i<=n;i++) if (deg[i]&1) on[++onp]=i;
	if (!floyd()) return printf("-1\n"),0;
	solve(1);
	ans+=wsum;
	printf("%lld\n",ans);
	return 0;
} 
```


---

## 作者：xlqs23 (赞：4)

**题意：**

给定$n$个点$m$条边的无向图

求从1点开始经过每条边至少一次最后回到1点的最小路程

显然就是找一条路径可重复的欧拉回路

**思路：**

首先对于欧拉回路的结论是：所有点的度数都为偶数

因为所有边至少经过一次，那么可以把题意转换成加最少多少条边使得图满足以上结论

而加的边目的是为了把奇度数转成偶度数，先floyd一下得到任意点间加边的最小花费

$dp[i]$表示状态i下度数都为偶数的最小花费。

状压$dp$，把$i$状态下，所有未选择的点中挑2个奇度数的转移即可。

**Code:**
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <math.h>
using namespace std;
#define ll int
#define inf 1000000007
#define N 16
int dis[N][N], n, m;
void floyd(){
	for(ll k = 0; k < n; k++)
		for(ll i = 0; i < n; i++)
			for(ll j = 0; j < n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
	for(ll i = 0; i < n; i++)dis[i][i] = 0;
}
int du[N], ans, dp[1<<N];//dp[i] 表示加边使得i状态下的所有点都是偶度数的最小花费
ll work(){
	ll i, j, k;
	for(i = 1; i < n; i++)//如果i这个点有边连接，但点0又走不到这个点，说明和这个点相连的边是走不到的，即图不连通
		if(du[i] && dis[0][i]==inf)return -1;
 
	ll all = (1<<n)-1;
	for(i = 0; i <= all; i++)	dp[i] = inf;
	dp[0] = 0;
	for(k = 0; k <= all; k++) 
	{
		for(i = 0; i < n; i++)//找到一个奇度数的点i
			if((du[i]&1) && (k&(1<<i)))break;
		if(i==n)dp[k] = 0;
		for(i = 0; i < n; i++)// 枚举奇数度点i  
			if((du[i]&1) && !(k&(1<<i)))
				for(j = i+1; j < n; j++)// 枚举奇数度点j  
					if((du[j]&1) && !(k&(1<<j)) && dis[i][j]<inf)
						dp[k|(1<<i)|(1<<j)] = min(dp[k|(1<<i)|(1<<j)],dp[k]+dis[i][j]);
	}
	if(dp[all]>=inf)return -1;
	return ans + dp[all];
}
int main(){
	ll i, j, u, v, w;
	while(cin>>n>>m){
		for(i=0;i<n;i++)for(j=0;j<n;j++)dis[i][j] = inf;
		memset(du, 0, sizeof du);
		ans = 0;
		while(m--){
			cin>>u>>v>>w; u--; v--;
			dis[u][v] = dis[v][u] = min(dis[u][v], w);
			du[u]++; du[v]++;
			ans += w;
		}
		floyd();
		cout<<work()<<endl;
	}
	return 0;
}

```
原文链接：
[这里](https://blog.csdn.net/qq574857122/java/article/details/36180635)



---

## 作者：under_the_time (赞：1)

## 题意

> 给定一张 $n$ 个点 $m$ 条边的带权无向图，要求从 $1$ 出发，经过每条边至少一次后回到 $1$。求最小的经过的边权的和。
>
> $1\le n\le 15$，$1\le m\le 2\times 10^3$。

## 解法

如此大的 $m$ 显然不能直接进行状压，考虑把点的信息作为状态。因为每条边都至少经过了一次，所以图一定要求连通。注意到题目求的是一条可以重复经过边的欧拉回路，如果将欧拉回路重复经过的边视为重边，则原图会变成一个欧拉图，即每个节点度数都是偶数。反过来说，每个节点度数都是偶数的图，一定存在着这样一条欧拉回路。

于是我们只需要在原图上将若干边变成重边，使原图变成一张欧拉图。而边权和最小的这样的欧拉图的边权和即为所求。考虑将每个节点的度数奇偶性用一个二进制数 $S$ 表示，我们令 $f(S)$ 表示使每个节点奇偶性变为 $S$ 时所需的最小边权和。如果 $S$ 二进制第 $i$ 位上为 $1$ 表示第 $i$ 个点是偶数，反之则不是。转移时考虑枚举每一条边，将这条边进行复制，则对于边 $(u,v)$（其边权记为 $w(u,v)$），设新的状态为 $S'$（即 $u,v$ 两点奇偶性发生改变后的状态），转移方程即为
$$
f(S')\gets\min(f(S)+w(u,v),f(S'))
$$
可是这种做法无法保证 dp 的**无后效性**，即转移后的 $S'$ 有可能比 $S$ 更小。此时如果使用 Dijkstra 的方法计算，复杂度多了一个 $\log$ 就会超时。

对于两条边 $(u,v),(v,z)$，当它们同时发生复制时，$u$ 和 $z$ 将改变奇偶性而 $v$ 却不会。而 $v$ 的选择作用相同，欲使 $u,z$ 奇偶性发生改变，最优的方案显然是选择 $w(u,v)+w(v,z)$ 最小的 $v$。进一步推广得到：对于任意两个点 $u,v$​，最优方案就是复制整条最短路径上经过的边。

于是做法就出来了：对于每个状态，我们找到其中的两个度数仍为奇数的点，复制它们的最短路使它们变成偶数。这样一来目标状态的偶数度数的点就会更多，满足无后效性。最后答案取全是偶数的情况即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 17;
#define ll long long
ll g[maxn][maxn], f[1 << (maxn - 2)], ans;
int d[maxn], n, m;
const ll inf = 2e18;
int main() {
    scanf("%d%d",&n,&m);
    for (int i = 0;i < n;i ++) 
        for (int j = 0;j < n;j ++)
            g[i][j] = (i == j ? 0 : inf);
    for (int i = 1,u,v,w;i <= m;i ++) {
        scanf("%d%d%d",&u,&v,&w), u --, v --;
        // 每条边都需要经过，于是先把最基本的边权和算出来
        // 重边中取最小的
        ans += w, g[u][v] = g[v][u] = min(g[u][v],1ll * w);
        d[u] ++, d[v] ++;
    }
    // Floyd
    for (int k = 0;k < n;k ++)
        for (int i = 0;i < n;i ++)
            for (int j = 0;j < n;j ++)
                g[i][j] = min(g[i][j],g[i][k] + g[k][j]);
    d[0] &= 1; 
    // 判无解
    for (int i = 1;i < n;i ++) {
        // 即如果该点周围有边，但出发点 0 到不了，就为无解。
        if (g[0][i] >= inf && d[i]) return puts("-1"), 0;
        d[i] &= 1; // 这里 &= 1 是因为我们只关心度数的奇偶性
    }
    int beg = 0, end = (1 << n) - 1;
    for (int i = 0;i < n;i ++)
        beg |= ((d[i] ^ 1) << i);
    // 起点状态与终点状态
    for (int i = 0;i <= end;i ++) 
        f[i] = inf;
    f[beg] = 0;
    for (int S = beg;S < (1 << n);S ++) {
        if ((beg | S) != S) continue; // 如果出现了“想让其变为奇数，但它已是偶数”的情况直接跳过
        for (int i = 0;i < n;i ++)
            if (!(S & (1 << i)) && d[i]) // 枚举一个“想让其变为奇数，它也的确是奇数”的两个点
                for (int j = 0;j < n;j ++)
                    if (i != j && !(S & (1 << j)) && d[j]) { // 注意两个点不能相同
                        int T = (S | (1 << i) | (1 << j));
                        f[T] = min(f[T],f[S] + g[i][j]);
                    }
    }
    if (f[end] >= inf) puts("-1");
    else printf("%lld",ans + f[end]);
    return 0;
}
```

---

## 作者：CyberPrisoner (赞：1)

解决本题的一个重要知识：**欧拉路径**。

在这里简单介绍一下欧拉路径，我们定义一个点连接它的边的数量为它的度，定义度数为奇数的点为奇点，度数为偶数的点为偶点。对于一个无向图 $G$，奇点个数为 $2$ 时为**欧拉路**，从任意奇点出发可以遍历所有边，最后走到另一个奇点；奇点的个数为 $0$ 时为**欧拉回路**,此时从任意一个点出发可以遍历所有的点，最后回到出发点，所有的边都只经过一遍，其余情况都无法一遍走完所有边。

那么对于本题，我们要从 $1$ 出发最后回到 $1$ ,如果此时的图构成了欧拉回路，那么直接把所有边的权值加起来即可。如果不是欧拉回路，我们需要重复经过一些边才能回到出发点，其实把重复经过的边算到原图上，就相当于把原图变成了欧拉回路。再回到欧拉回路的定义，这就相当于我们要把度数为奇数的点的度数变成偶数。

具体要怎样实现呢？我们很容易发现，每连一条边可以让两个点的度数 $+1$,那么我们每次选两个奇点，把它们之间最短的路径再走一遍，最后把所有奇点都考虑到。对于选取的方案，我们发现本题的数据范围非常小，可以考虑状态压缩。令当前已经选取的奇点集合为 $S$,有 
$$dp_{S \cup \{j,k\}}=\min _{j,k\notin S }(dp_S+dis_{jk})$$
最后的 $dp_S$ 就是回到 $1$ 所需要重复经过的边的总长度。

 _code_ 
 ```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,inf=1e9;
int d[40][40];//d表示两点的距离 
int deg[35],f[1<<21];//deg表示点的度数，f为重复经过的边 
int n,m,cnt,ans,tot,a[40];//a为奇点的集合 
void floyed(){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=j&&i!=k&&j!=k){
					d[i][j]=min(d[i][k]+d[k][j],d[i][j]);
				}
			}
		}
	}
} 
int cc(int num){
	int res=0;
	while(num){
		num>>=1;
		res++;
	}
	return res;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			d[i][j]=inf;
		}
	}
	for(int i=1,x,y,w;i<=m;i++){
		cin>>x>>y>>w;
		if(x!=y){
			d[x][y]=min(d[x][y],w);//重边只考虑最小的 
			d[y][x]=d[x][y];
		}
		deg[x]++,deg[y]++;
		ans+=w;
	}
	floyed();//n^3处理每两个点的距离
	for(int i=2;i<=n;i++){
		if(deg[i]&&d[1][i]==inf){//非连通图且那个点连的有边 
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		if(deg[i]&1)a[++tot]=i;
	}
	f[0]=0,cnt=(1<<tot)-1;
	for(int i=1;i<=cnt;i++){
		f[i]=inf;
		if(cc(i)&1)continue;//奇点的个数一定为偶数 
		for(int j=1;j<=tot;j++){
			if((i&1<<(j-1))==0)continue;
			for(int k=j+1;k<=tot;k++){
				if((i&1<<(k-1))==0)continue;
				int s=i^(1<<(j-1))^(1<<(k-1));
				f[i]=min(f[s]+d[a[j]][a[k]],f[i]);
			}
		}
	}
	cout<<ans+f[cnt];//end 
	return 0;
}
```


---

## 作者：王熙文 (赞：1)

我感觉这道题的证明比较有趣，但是其他题解都没写，因此我写一篇。

## 思路

以下称度数为偶数的点为偶点，否则为奇点。

首先，如果这个图中有一条欧拉回路，则答案一定为所有边权的总和。存在欧拉回路当且仅当所有点都是偶点且图连通。如果图不连通则答案一定是无解，可以直接判断掉。现在考虑图连通的情况。

考虑把重复走的边想象成添加的边，那么现在可以把问题转化成：需要填多少条边，使得添加的边权最小且没有奇点。

想将一个奇点变成偶点就得在它周围添加一条边，而如果这条边的另外一个点之前是偶点，现在就变成了奇点，需要继续添加。直到遇到了添加的边的另外一个点也是奇点才能结束。因此消除奇点的过程本质是在两个奇点之间添加一条路径。

这样就可以想到一个算法：暴力匹配奇点并消除，代价为两个奇点之间的最短路的长度。

但是这个算法是对的吗？可以发现，如果两对奇点的最短路上有重复的边，则这条边被添加了两遍，和没添加一样（因此添加两遍奇偶性不变），代价会算多。

但是，如果出现了这种情况，可以换一种匹配，使得路径之间没有重复的边。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/09vsql25.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

因此我们猜想，上面这个算法是对的。想要证明这个算法的正确性，只需要证明，任意有重复边的最短路匹配方式和任意不按最短路连边的方式都劣于无重复边的最短路匹配方式。

对于有重复边的最短路匹配方式，如上图，可以换一条路，并把新增的路径换成它们之间的最短路（上图中把 $1,2$ 和 $3,4$ 之间的路径换成最短路），这样一定更优。对于不按最短路连边的方式，可以把一对不是最短路的换成最短路，这样也一定更优。

因为每一次换路会使答案更优，所以这样的换路是有限的，不会死循环。最终上面两种方式一定会变成无重复边的最短路匹配方式。因此计算所有无重复边的最短路匹配方式的代价最小值即可。

而且，因为有重复边的匹配方式劣于无重复边的，所以统计的时候并不需要判断是否有重复边，直接取最小值即可。

那最开始提到的算法怎么实现呢？在这道题中，暴力搜索或状压 dp 都可以通过，对于更大的数据应该可以使用二分图最大权匹配。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int dis[20][20];
int in[20];
int tot=0,odd[20];
int dp[1<<15];
int main()
{
	memset(dis,0x3f,sizeof(dis));
	cin>>n>>m;
	int sum=0;
	for(int i=1; i<=m; ++i)
	{
		int u,v,w; cin>>u>>v>>w;
		sum+=w;
		dis[u][v]=dis[v][u]=min(dis[u][v],w);
		++in[u],++in[v];
	}
	for(int k=1; k<=n; ++k)
	{
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=n; ++j)
			{
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(int i=1; i<=n; ++i)
	{
		if(in[i]!=0 && dis[1][i]>=1e9) return cout<<-1,0;
	}
	for(int i=1; i<=n; ++i)
	{
		if(in[i]%2==1) odd[++tot]=i;
	}
	for(int i=1; i<(1<<tot); ++i)
	{
		if(__builtin_popcount(i)%2==1) continue;
		dp[i]=1e9;
		for(int j=1; j<=tot; ++j)
		{
			if((i>>j-1&1)==0) continue;
			for(int k=j+1; k<=tot; ++k)
			{
				if((i>>k-1&1)==0) continue;
				dp[i]=min(dp[i],dp[i^(1<<j-1)^(1<<k-1)]+dis[odd[j]][odd[k]]);
			}
		}
	}
	cout<<sum+dp[(1<<tot)-1];
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

# Solution
发现 $n$ 最大只有 $15$，但是 $m$ 却很大，考虑如何将问题转换到 $n$ 上面。

根据欧拉回路可以知道，我们这道题要处理的其实就是度数为奇数的点，然后进行**连边**。

考虑连边的边权，其实就是当前 $2$ 个度数为奇数的点（假设为 $x, y$）连上一条权值为 $G_{x, y}$ 的边（$G_{x, y}$ 为 $2$ 点的最短距离）。

那么答案的构成就是由**输入**所有的边权的和加上度数为奇数的点两两配对的最小值。

为了方便我们将所有的点编号少一。

定义 $s$ 的第 $i$ 位二进制上如果是 $1$ 则代表 $i$ 的度数是奇数。

问题就转换成了在 $1$ 中互相匹配变成 $0$，使得 $s$ 变成 $0$。

直接搜索即可，但是发现会超时。

定义 $f_s$ 表示 $s$ 到 $0$ 最小需要变换成功的权值。

然后记忆化即可。
# code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1e1 + 6;
int n, m, u, v, w, G[N][N], deg[N], s, f[1 << N], sum, dist[N][N];
int dfs (int s) {
	if (!s) return 0;
	if (f[s] >= 0) return f[s];
	f[s] = 1e18;
	for (int i = 0; i < n; i ++)
		if (s >> i & 1) {
			for (int j = i + 1; j < n; j ++)
				if (s >> j & 1) {
					int k = dfs (s - (1 << i) - (1 << j)) + G[i][j];
					if (f[s] > k) f[s] = k;
				}
		}
	return f[s];
}
signed main () {
	*cin.tie (nullptr) << fixed << setprecision (20);
	cout.tie (nullptr) -> ios_base :: sync_with_stdio (false);
	
//	while (cin >> n && n) {
		cin >> n >> m, sum = 0, memset (f, -1, sizeof f), memset (deg, 0, sizeof deg), memset (G, 0x3f, sizeof G);
		memset (G, 0x3f, sizeof G), memset (dist, 0, sizeof dist);
		for (int i = 0; i < n; i ++) G[i][i] = 0;
		for (int i = 1; i <= m; i ++) {
			cin >> u >> v >> w, u --, v --;
			G[u][v] = G[v][u] = min (G[u][v], w), deg[u] ++, deg[v] ++;
			dist[u][v] += w, dist[v][u] += w;
		}
		for (int i = 0; i < n; i ++)
			for (int j = 0; j < n; j ++)
				sum += dist[i][j];
		sum /= 2;
		s = 0;
		for (int k = 0; k < n; k ++)
			for (int i = 0; i < n; i ++)
				for (int j = 0; j < n; j ++)
					G[i][j] = min (G[i][j], G[i][k] + G[k][j]);
		for (int i = 0; i < n; i ++)
			if (deg[i] % 2)
				s |= 1 << i;
		cout << sum + dfs (s) << '\n';
//	}
	return 0;
}
```

---

