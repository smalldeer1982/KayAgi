# Weights Distributing

## 题目描述

You are given an undirected unweighted graph consisting of $ n $ vertices and $ m $ edges (which represents the map of Bertown) and the array of prices $ p $ of length $ m $ . It is guaranteed that there is a path between each pair of vertices (districts).

Mike has planned a trip from the vertex (district) $ a $ to the vertex (district) $ b $ and then from the vertex (district) $ b $ to the vertex (district) $ c $ . He can visit the same district twice or more. But there is one issue: authorities of the city want to set a price for using the road so if someone goes along the road then he should pay the price corresponding to this road (he pays each time he goes along the road). The list of prices that will be used $ p $ is ready and they just want to distribute it between all roads in the town in such a way that each price from the array corresponds to exactly one road.

You are a good friend of Mike (and suddenly a mayor of Bertown) and want to help him to make his trip as cheap as possible. So, your task is to distribute prices between roads in such a way that if Mike chooses the optimal path then the price of the trip is the minimum possible. Note that you cannot rearrange prices after the start of the trip.

You have to answer $ t $ independent test cases.

## 说明/提示

One of the possible solution to the first test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1343E/45349f7bc2743dc38bc22fd8a04a573c0f1fee19.png)

One of the possible solution to the second test case of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1343E/dcd34c001e92838b1f52c04f64c0407963f9ec6e.png)

## 样例 #1

### 输入

```
2
4 3 2 3 4
1 2 3
1 2
1 3
1 4
7 9 1 5 7
2 10 4 8 5 6 7 3 3
1 2
1 3
1 4
3 2
3 5
4 2
5 6
1 7
6 7```

### 输出

```
7
12```

# 题解

## 作者：registerGen (赞：7)

[可能更好的阅读体验](https://registergen.github.io/post/solution-cf1343e/)

[顺便安利我的水题选做系列](https://registergen.github.io/tag/xSY20OkOx//)

CF div3E 的图论题就是清新~

先考虑只有两个点 $a,b$ 的情况。

# Solution

显然有一种贪心策略：先把所有点的权值设为 $1$，用 BFS 求出 $a\leftrightarrow b$ 的最短路 $k$，让最小的 $k$ 个 $w_i$ 填入 $a\leftrightarrow b$ 间的路径即可。

再考虑有 $3$ 个点 $a,b,c$ 的情况。

上面的贪心策略已经失效，因为 $a\leftrightarrow b$ 与 $b\leftrightarrow c$ 的最短路径可能有重合的部分。

不过类比两个点的做法，再考虑处理重合的办法，可以得到以下解法：

枚举一个点 $i$（可以为 $a,b,c$），我们选择的路线为 $a\to i\to b\to i\to c$（即 $b\leftrightarrow i$ 是重合的部分），那么答案为

$$
\min\{\operatorname{price}(a,i)+2\operatorname{price}(b,i)+\operatorname{price}(c,i)\}
$$

其中 $\operatorname{price}(x,y)$ 为安排好边权后 $x,y$ 间的最短路。

分析到这里，我们就可以愉快的贪心啦！

枚举 $i\in [1,n]$，先把边权最小的边放在 $b\leftrightarrow i$ 间的路径上，然后把 $a\leftrightarrow i$ 和 $c\leftrightarrow i$ 间路径安排上边权尽量小的边即可。

另外，由于本题多测而且数据范围是 $1\le T\le 10^4$，$2\le n\le 2\times 10^5$，所以一次不要 `memset` 太多数组。给每个函数前加上一句 `__attribute__ ((always_inline))` 也是一个不错的选择（当然正式比赛时千万别用）。

# Code

```cpp
// #pragma GCC optimize(3,"Ofast","inline")

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

typedef long long ll;

const int N=2e5;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
const int inf=0x3f3f3f3f;

struct Edge{int to,nxt;}e[N*2+10];int head[N+10],tote;
__attribute__ ((always_inline))
inline void addEdge(int u,int v){e[++tote].to=v;e[tote].nxt=head[u];head[u]=tote;}

int n,m,a,b,c;
ll w[N+10],s[N+10];
int dis[N+10],disA[N+10],disB[N+10],disC[N+10];
bool vis[N+10];

__attribute__ ((always_inline))
inline void BFS(int start,int opt)
{
	memset(dis,0x3f,sizeof(dis));
	dis[start]=0;
	memset(vis,0,sizeof(vis));
	std::queue<int> q;
	q.push(start);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
//		if(vis[u])continue;
//		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(dis[v]==inf)
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
//	for(int i=1;i<=n;i++)
//		printf("%lld ",dis[i]);
//	puts("");
	if(opt==1)for(int i=1;i<=n;i++)disA[i]=dis[i];
	if(opt==2)for(int i=1;i<=n;i++)disB[i]=dis[i];
	if(opt==3)for(int i=1;i<=n;i++)disC[i]=dis[i];
}

__attribute__ ((always_inline))
inline void solve()
{
	memset(head,0,sizeof(head));
	tote=0;
//	memset(disA,0x3f,sizeof(disA));
//	memset(disB,0x3f,sizeof(disB));
//	memset(disC,0x3f,sizeof(disC));
	memset(s,0,sizeof(s));
	scanf("%d%d%d%d%d",&n,&m,&a,&b,&c);
	for(int i=1;i<=m;i++)
		scanf("%lld",w+i);
	std::sort(w+1,w+m+1);
	for(int i=1;i<=m;i++)
		s[i]=s[i-1]+w[i]; // 边权排序后的前缀和
	for(int u,v,i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		addEdge(u,v);addEdge(v,u);
	}
	BFS(a,1);
	BFS(b,2);
	BFS(c,3);
	ll ans=INF;
	for(int i=1;i<=n;i++)
	{
//		puts("!");
		int A=disA[i],B=disB[i],C=disC[i];
//		printf("%lld %lld %lld\n",A,B,C);
		if(A+B+C<=m) // 防止越界
			ans=std::min(ans,s[A+B+C]+s[B]);
	}
	printf("%lld\n",ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：JK_LOVER (赞：7)

## 题意：
在无向图上，有 $a,b,c$ 三个点，要让 $a$ 到 $b$ 再到 $c$ 的路径最小，边权在可重集合 $W$ 中选取。 
## 分析
因为是无向图，那么 $a$ 到 $b$ 的最小路径长度等于 $b$ 到 $a$ 的路径长度。所以如果没有重复路径 $a$ 到 $b$ 再到 $c$ 的路径长度应该贪心的选择前 $k$ 个。但如果有重复路径，我们应该让重复路径更小(这个贪心很显然，因为我们要最小化总路径长度)。这里我们用图例说明。
![](https://cdn.luogu.com.cn/upload/image_hosting/jicmw9q6.png)

看出 $5$ 到 $3$ 到 $2$ 的这条路径过了两次，那我们就应该最小化这一条路径，也可以看出 $2$ 到 $6$ 和 $2$ 到 $7$ 是没有重复点的。我们再简化路径，所有的图的最小路径都是：从 $A$ 到 $D$ （重复点），再从 $D$ 到 $B$ ， 然后 $B$ 到 $D$ ，最后从 $D$ 到 $C$。所以总长度为: 
$$
sum=dist[B] * 2 +dist[C] + dist[A]
$$
而我们不可能做 $n$ 次 $BFS$ 所以考虑优化。再从无向图的性质：两点路径等价可简化式子：
$$
sum = dist_{A-D}+dist_{B-D} * 2  + dist_{C-D}
$$
到这里，我们就只需要三次 $BFS$ 就可以了。然后 ${B-D}$ 路径选前 $dist_{B-D}$ 个就可以，然后 ${D-A}$ 和 ${D-C}$ 依次向后选择就行。那我们只需枚举 $D$ 就可以了。总的复杂度应为 $O(Tn)$ 。但可能常数挺大的。
## 代码

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
#define N 200100
struct edge{int next,to;}e[N<<1];
int head[N],w[N],sum[N],n,m,A,B,C,disA[N],disC[N],disB[N],dis[N],cnt=-1;
void add(int x,int y)
{
	e[++cnt].next = head[x];
	e[cnt].to = y;
	head[x] = cnt;
}
void solve(int s,int t)
{
	queue<int> q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;q.push(s);
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for(int i = head[x];~i;i=e[i].next)
		{
			int y = e[i].to;
			if(dis[y]==0x3f3f3f3f3f3f3f3f)
			{
				dis[y] = dis[x]+1;
				q.push(y);
			}
		}
	}
	if(t == 1) 
	for(int i = 1;i <= n;i++)disA[i]=dis[i];
	if(t == 2) 
	for(int i = 1;i <= n;i++)disB[i]=dis[i];
	if(t == 3) 
	for(int i = 1;i <= n;i++)disC[i]=dis[i];
}
signed main()
{
	int T=read();
	while(T--)
	{
		memset(head,-1,sizeof(head));
		memset(w,0,sizeof(w));
		cnt=-1;
		n=read();m=read();A=read();B=read();C=read();
		for(int i = 1;i <= m;i++)
		{
			w[i]=read();
		}
		sort(w+1,w+m+1);
		for(int i = 1;i <= m;i++) sum[i]=sum[i-1]+w[i];
		for(int i = 1;i <= m;i++)
		{
			int a=read(),b=read();
			add(a,b);
			add(b,a);
		}
		solve(A,1);
		solve(B,2);
		solve(C,3);
		int ans=0x3f3f3f3f3f3f3f3f;
		for(int i = 1;i <= n;i++)
		{
			int a=disA[i],b=disB[i],c=disC[i];
			if(a+b+c<=m)
			{
				ans=min(sum[a+b+c]+sum[b],ans);
			}
			
		}
		printf("%lld\n",ans);
		for(int i = 1;i <= n;i++)
		disA[i]=disB[i]=disC[i]=0x3f3f3f3f3f3f3f3f;
	}
	return 0;
}
```


---

## 作者：KellyFrog (赞：4)

第一场 CF 的题~~为啥我这题都不会做啊~~。

题意（这鬼翻译居然是我写的）：

给每条边安排一个边权，最小化 $a$ 到 $b$ 和 $b$ 到 $c$ 的最短路长度和。

我们将 $a\rightarrow b$ 拆分为 $a\rightarrow p\rightarrow b$，同理 $c\rightarrow b$ 拆为 $c\rightarrow p\rightarrow b$，意思是 $a,c$ 两点在 $p$ 汇合之后走到 $b$，**之前都没有汇合**。

那么此时的答案就是 $2\cdot dis(b\rightarrow p)+dis(a\rightarrow p)+dis(c\rightarrow p)$，于是我们先以边权为 1，跑 $a,b,c$ 分别为源点的最短路，之后枚举 $p$ 点就行了（把尽量小的权值安排给 $b\rightarrow p$）。

但这样你发现过不了第一个样例，因为会有 $dis(a\rightarrow p)+dis(b\rightarrow p)+dis(c\rightarrow p) > m$，边权安排不过来，根据抽屉原理，一定会有一条边被经过两次，和上面“没有汇合”就矛盾了，于是我们舍去这种情况。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;
const int M = 2e5 + 5;
const ll INF = 1e18;

ll wgt[M], sum[M];
vector<int> adj[N];
int disa[N], disb[N], disc[N];
int n, m, a, b, c;

void Bfs(int s, int dis[]) {
	for(int i = 1; i <= n; i++) {
		dis[i] = -1;
	}
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : adj[u]) {
			if(dis[v] == -1) {
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
}

void Solve() {
	scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);
	
	for(int i = 1; i <= n; i++) {
		adj[i].clear();
	}
	
	for(int i = 1; i <= m; i++) {
		scanf("%lld", &wgt[i]);
	}
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	sort(wgt + 1, wgt + 1 + m);
	for(int i = 1; i <= m; i++) {
		sum[i] = sum[i - 1] + wgt[i];
	}
	
	Bfs(a, disa), Bfs(b, disb), Bfs(c, disc);
	
	ll ans = INF;
	
	for(int i = 1; i <= n; i++) {
		if(disa[i] + disb[i] + disc[i] > m) {
			continue;
		}
		ans = min(ans, sum[disa[i] + disb[i] + disc[i]] + sum[disb[i]]);
	}
	
	printf("%lld\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		Solve();
	}
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：3)

先考虑只有两个点的情况，不难发现我们肯定会走边数最少的路径（反正权值是你填的，每次在填最小的权值的情况下边最少肯定最优）。

但是拓展到三个点时就出了一些问题：有些边可能会被重复经过，这样的话边数最少的贪心不一定成立（可能有些边经过不止一次）。但是又发现这个贪心并没有完全假，因为每一条边最多经过两次，否则一定不优。

我们考虑什么时候边会经过两次，肯定是路径形如 $a\to x\to b\to x\to c$，即我们一定能找到一个中转点 $x$ 使得 $x$ 到 $b$ 的边被经过了两次（$x$ 亦有可能与 $b$）重合。

直观理解就是被走过两次的边一定连成了一条以 $b$ 为其中一个端点的路径。

综上，我们跑 $3$ 遍 BFS 预处理最短路，然后枚举中间点，并将中转点到 $b$ 的路径上填上最小的值，并将答案类算两遍，剩下的边填上较小的值。

时间 $O(n+m\log m)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rs now<<1|1
#define ls now<<1

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define int long long
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=3e5+10;
int n,m,a,b,c,dis[3][N],w[N],vis[N],T;
vector < int > v[N];
queue < int > Q;

void dijkstra(int st,int *dis){
	for(int i=1;i<=n;++i) vis[i]=0,dis[i]=1e9;
	dis[st]=0;Q.push(st);vis[st]=1;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int y:v[x]) if(!vis[y]){dis[y]=dis[x]+1;Q.push(y);vis[y]=1;}
	}
}

signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m>>a>>b>>c;int ans=1e18;
		for(int i=1;i<=m;++i) cin>>w[i];sort(w+1,w+1+m);for(int i=1;i<=m;++i) w[i]+=w[i-1];
		for(int i=1,x,y;i<=m;++i){cin>>x>>y;v[x].emplace_back(y);v[y].emplace_back(x);}
		dijkstra(a,dis[0]);dijkstra(b,dis[1]);dijkstra(c,dis[2]);
		for(int i=1;i<=n;++i){
			int x=dis[0][i],y=dis[1][i],z=dis[2][i];
			if(x+y+z<=m) ans=min(ans,w[x+y+z]+w[y]);
		}
		for(int i=1;i<=n;++i) v[i].clear();
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：3)

在此约定 $ x $ 和 $ y $ 之间的最短路为 $ dis_{x,y} $ 。

------------

给你一张图和一些边权，你可以随意地安排边权，使得边与权一一对应。

求 $ dis_{a,b} + dis_{b,c} $ 的最小值。

注意是双向边。

------------

边是双向的，问题成了求 $ dis_{b,a} + dis_{b,c} $ 的最小值。

如果2条最短路有大于 $ 2 $ 段重合了，可以一直做一下操作：

1. 选择 $ 2 $ 段重合段中间夹着的两条路径的经过边最少的一段。

2. 舍弃另一段。

如下：

![bad](https://cdn.luogu.com.cn/upload/image_hosting/qnh96st8.png)

修改成：

![good](https://cdn.luogu.com.cn/upload/image_hosting/paprbai3.png)

使用的边变少了至少 $ \left \lceil \frac{ \text{夹着的两条路径边数} }{2} \right \rceil $ 。

而增加的重合路径是至多 $ \left \lfloor \frac{ \text{夹着的两条路径边数} }{2} \right \rfloor $ ，比较一下发现这样一定更优。

问题变成了 $ dis_{b,a} + dis_{b,c} $ 的最小值，且两条路径只会有1段交。

把 $ dis_{b,b} $ 这段空的路也算一段交，也可以通过上述理论合并。

问题变成了求一个点 $ d $ ，使得 $ 2dis_{b,d} + dis_{d,a} + dis_{d,c} $ 最小（ $ b $ 可以和 $ d $ 重合）。

只需要宽度优先搜索一遍，再枚举哪个点是 $ d $ ，优先把权值小的边给重复路径即可。

根据 $ d $ 计算答案可以通过前缀和优化成 $ O(1) $ 。

------------

时间复杂度即 $ O(n) $ ，非常正确。

------------

代码如下 （~~非常的短~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
vector<int>q[202020];
int vis[202020][3],dis[202020][3];
long long v[606060];
queue<int>b;
void bfs(int x,int p){//把bfs封装成函数调用，p表示这次的距离存在那个dis数组里面。
	b.push(x);
	vis[x][p]=1;
	static int s,l;
	while(b.size()){
		s=b.front();
		b.pop();
		for(register int i=0;i<q[s].size();++i){
			l=q[s][i];
			if(!vis[l][p]){
				dis[l][p]=dis[s][p]+1;
				vis[l][p]=1;
				b.push(l);
			}
		}
	}
}
void doing(){
	static int a,b,c;
	cin>>n>>m>>a>>b>>c;
	for(register int i=1;i<=n;++i){
        q[i].clear();
		for(register int j=0;j<3;++j)vis[i][j]=dis[i][j]=0;
	}
	for(register int i=1;i<=m;++i)scanf("%lld",&v[i]);
	for(register int i=m+1;i<=m*3;++i)v[i]=1000000000;//防止边太多了。
	sort(v+1,v+m+1);
	for(register int i=1;i<=m*3;++i)v[i]+=v[i-1];//前缀和优化。
	for(register int i=1;i<=m;++i){
		scanf("%d %d",&s,&l);
		q[s].push_back(l);
		q[l].push_back(s);
	}
	bfs(a,0);
	bfs(b,1);
	bfs(c,2);
	static long long ans;
	ans=v[m*3];
	//优先重合段的答案计算。
	for(register int i=1;i<=n;++i)ans=min(ans,v[dis[i][0]+dis[i][1]+dis[i][2]]+v[dis[i][1]]);
	printf("%lld\n",ans);
}
int main(){
	int t;
	cin>>t;
	while(t--)doing();
	return 0;
} 
```

---

## 作者：Pengzt (赞：0)

# CF1343E Weights Distributing

###### Problem

给出一个有 $n$ 个点，$m$ 条边的无向图和一个长为 $m$ 的权值序列 $w$。

你可以随意安排边权（每条边权对应 $w$ 中的一个数，不可以重复）。

求 $a$ 到 $b$ 的最短路与 $b$ 到 $c$ 的最短路的和的最小值。

$2 \le n,m \le 2 \cdot 10^5$。

###### Sol

发现最后这两条路径的交一定可以是一段路径。所以枚举 $a \leadsto b$ 和 $b \leadsto c$ 的交 $b \leadsto i$。然后这一段重复经过的边的权都放比较小的。对 $w$ 排序之后做前缀和，然后分别以 $a, b, c$ 为源点跑最短路即可，然后这里只需要知道边的数量，所以可以直接 01BFS 做到 $\mathcal{O}(n + m)$。

###### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
#define ll long long
#define vi vector<int>
#define pb emplace_back
#define sz(a) ((int) a.size())
#define pii pair<int, int>
#define fi first
#define se second
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, A, B, C;
int a[200005];
ll s[200005];
vi e[200005];
int dis[3][200005];
void Dijkstra(int s, int *dis) {
    queue<int> que;
    memset(dis, 0x3f, (n + 1) * sizeof (int));
    que.emplace(s);
    dis[s] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : e[u])
            if (dis[v] == inf)
                dis[v] = dis[u] + 1, que.emplace(v);
    }
}
void Solve() {
    scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
    L(i, 1, m) scanf("%d", &a[i]);
    sort(a + 1, a + m + 1);
    L(i, 1, m) s[i] = a[i] + s[i - 1];
    L(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].pb(v), e[v].pb(u);
    }
    Dijkstra(A, dis[0]);
    Dijkstra(B, dis[1]);
    Dijkstra(C, dis[2]);
    ll ans = INF;
    L(i, 1, n) {
        ll c0 = dis[0][i];
        ll c1 = dis[1][i];
        ll c2 = dis[2][i];
        if (c0 + c1 + c2 > m) continue;
        ans = min(ans, s[c0 + c1 + c2] + s[c1]);
    }
    printf("%lld\n", ans);
    L(i, 1, n) e[i].clear();
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        Solve();
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1343E)

***2100**，独立完成。

~~难度虚高了吧。~~

做法是你考虑答案的构成，肯定是以 $b$ 为基准点，然后我们找到某一条 $b$ 到 $c$ 的路径，记路径上的点序列为 $p$。

然后 $b$ 到 $a$ 的路径怎么找呢？容易发现就是在某个 $p_i$ 延伸出去的一条到 $a$ 的最短路径。

这就是答案的形态，不可能出现说，从 $b$ 出发绕了一个环到 $p_i$ 再延伸到 $a$ 的这种情况。

因为在这种情况下选的边尽可能少是优的。

考虑完答案的形态，接下来的就比较容易了。

枚举我们刚刚的中转点 $p_i$，因为选的边尽可能越少越好，所以，我们找到 $p_i$ 分别到 $a,b,c$ 最少经过几个边，然后计算答案即可。

计算就是 $p_i$ 到 $b$ 的边数算两次，然后加上 $p_i$ 到 $a,c$ 即可。按着这个顺序从小到大安排边就好了。

可能从 $p_i$ 到 $a,b,c$ 的路径之间可能会有重复覆盖的答案，这时候说明 $p_i$ 不是中转点，统计出来的答案偏大，对答案不造成影响。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
int ans=LLONG_MAX,A[N],s[N],dis[N],dis1[N],dis2[N],n,m,a,b,c;
bool vis[N];
vector<int> g[N];
void BFS(int st,int Dis[]){
	queue<int> q;
	for(int i=1;i<=n;i++)	vis[i]=false,Dis[i]=1e16;
	Dis[st]=0,q.push(st),vis[st]=1;
	while(!q.empty()){
		int now=q.front(); q.pop();
		for(int i=0;i<g[now].size();i++){
			int v=g[now][i];
			if(vis[v]==true)	continue;
			Dis[v]=Dis[now]+1,vis[v]=true,q.push(v);
		}
	}
} 
signed main(){
	int t;
	cin>>t;
	while(t--){
		ans=LLONG_MAX;
		cin>>n>>m>>a>>b>>c;
		for(int i=1;i<=m;i++)	cin>>A[i]; 
		sort(A+1,A+m+1);
		for(int i=1;i<=m;i++)	s[i]=s[i-1]+A[i];
		for(int i=1,u,v;i<=m;i++)	cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
		BFS(a,dis),BFS(b,dis1),BFS(c,dis2);
		
		
		for(int i=m+1;i<=4*m;i++)	s[i]=1e16;
		
		for(int i=1;i<=n;i++){
			ans=min(ans,s[dis1[i]]*2+s[dis1[i]+dis2[i]+dis[i]]-s[dis1[i]]);
	//		if(i==2)	cout<<ans<<endl;
		}
		for(int i=1;i<=n;i++)	g[i].clear();
		cout<<ans<<endl;
	}
	return 0;
} 
/*
4 3 2 3 4
1 2 3
1 2
1 3
1 4
*/
```

---

## 作者：Arghariza (赞：0)

首先因为图是无向的，所以 $a$ 到 $b$ 的最短路等于 $b$ 到 $a$ 的最短路，即求 $b$ 分别到 $a,c$ 的最短路和的最小值。

如果只有两个点的话，考虑求出所有边权为 $1$ 时两个点的最短路径（这条路径经过的边是**最少**的），只要把边权从小到大排序，尽可能将小的权值放到两个点最短路径上即可，正确性显然。

那有 $a,b,c$ 三个点的情况呢？其实这是同理的。三个点上述情况不正确，是因为 $b$ 到 $a$ 的最短路径和 $b$ 到 $c$ 的最短路径可能有重合的部分，而这些部分可能会被计算 $2$ 次。

所以我们可以枚举 $i$，表示离 $b$ 最远的，$b$ 到 $a$ 和 $b$ 到 $c$ 最短路径的重叠部分的点。题目即求 $dis_{b,i}\times 2+dis_{i,a}+dis_{i,c}$ 的最小值。

于是我们可以尽量把小的边优先安排到 $b$ 到 $i$ 的路径上，然后再尽量把小的边安排在 $i$ 到 $a,c$ 的路径上。

然后我们考虑如何求出 $i$ 到 $a,b,c$ 经过边**最少**的路径。可以使用 $3$ 次 bfs 解决。

代码很好写，记录如下。

[$\color{lightgreen}\mathtt{code}$](https://codeforces.com/contest/1343/submission/164246854)

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/120026599)

一道思维题。

首先我们可以发现实际上我们如果能够在 $a \to b \to c$ 上的路径上将总和排的尽量小那么一定是最优的。

于是我们可以考虑求出 $a \to b$ 的最短路以及 $b \to c$ 的最短路然后其和的结果就是总的最短路，将小的丢到这些路径上面就好了

……吗？

实际上还没有，因为上述做法并没有考虑到 $a \to b$ 和 $b \to c$ 两条路径重合的情况，如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/69b713109550428aa8a97eabec5d0369.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUGxvemlh,size_12,color_FFFFFF,t_70,g_se,x_16)

此时你会发现实际上 $b \to t$ 这条路径会被统计两次，但是按照上述做法这两次统计实际上是不同的结果。

所以实际上我们需要在 $b \to t$ 这条路径上排上最小的几个权值，然后剩下的就可以从小到大排啦~

考虑到这个 $t$ 是不定的，所以我们需要 $O(n)$ 枚举。

总复杂度 $O(Tn)$。

Code：[GitHub CodeBase-of-Plozia CF1343E Weights Distributing.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF1343E%20Weights%20Distributing.cpp)

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1343E Weights Distributing
	Date:2021/8/30
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::priority_queue;

typedef long long LL;
const int MAXN = 2e5 + 5;
int t, n, m, Head[MAXN], cnt_Edge = 1, dis[4][MAXN], Start, Middle, End, p[MAXN];
LL ans = 0, sum[MAXN];
bool book[4][MAXN];
struct node { int to, val, Next; } Edge[MAXN << 1];
struct pri
{
	int u, Num;
	bool operator <(const pri &fir)const
	{
		return Num > fir.Num;
	}
};

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, int z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void Dijkstra()
{
	priority_queue <pri> q1, q2, q3;
	q1.push((pri){Start, 0}), q2.push((pri){Middle, 0}), q3.push((pri){End, 0});
	while (!q1.empty())
	{
		pri x = q1.top(); q1.pop();
		if (book[1][x.u]) continue ; book[1][x.u] = 1;
		for (int i = Head[x.u]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (book[1][u]) continue ;
			if (dis[1][u] > dis[1][x.u] + Edge[i].val)
			{
				dis[1][u] = dis[1][x.u] + Edge[i].val;
				q1.push((pri){u, dis[1][u]});
			}
		}
	}
	while (!q2.empty())
	{
		pri x = q2.top(); q2.pop();
		if (book[2][x.u]) continue ; book[2][x.u] = 1;
		for (int i = Head[x.u]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (book[2][u]) continue ;
			if (dis[2][u] > dis[2][x.u] + Edge[i].val)
			{
				dis[2][u] = dis[2][x.u] + Edge[i].val;
				q2.push((pri){u, dis[2][u]});
			}
		}
	}
	while (!q3.empty())
	{
		pri x = q3.top(); q3.pop();
		if (book[3][x.u]) continue ; book[3][x.u] = 1;
		for (int i = Head[x.u]; i; i = Edge[i].Next)
		{
			int u = Edge[i].to;
			if (book[3][u]) continue ;
			if (dis[3][u] > dis[3][x.u] + Edge[i].val)
			{
				dis[3][u] = dis[3][x.u] + Edge[i].val;
				q3.push((pri){u, dis[3][u]});
			}
		}
	}
}

int main()
{
	t = Read(); memset(dis, 0x7f, sizeof(dis));
	while (t--)
	{
		n = Read(), m = Read(), Start = Read(), Middle = Read(), End = Read();
		for (int i = 1; i <= n; ++i) Head[i] = book[1][i] = book[2][i] = book[3][i] = 0; cnt_Edge = 1;
		for (int i = 1; i <= n; ++i) dis[1][i] = dis[2][i] = dis[3][i] = 0x7f7f7f7f; ans = 0x7f7f7f7f7f7f7f7f;
		dis[1][Start] = dis[2][Middle] = dis[3][End] = 0;
		for (int i = 1; i <= m; ++i) p[i] = Read(); sum[0] = 0;
		std::sort(p + 1, p + m + 1);
		for (int i = 1; i <= m; ++i) sum[i] = (LL)p[i] + sum[i - 1];
		for (int i = 1; i <= m; ++i)
		{
			int x = Read(), y = Read();
			add_Edge(x, y, 1); add_Edge(y, x, 1);
		}
		Dijkstra();
		for (int i = 1; i <= n; ++i)
			if (dis[1][i] + dis[3][i] + dis[2][i] <= m) ans = Min(ans, sum[dis[1][i] + dis[3][i] + dis[2][i]] + sum[dis[2][i]]);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：F_Mu (赞：0)


**题意**

多组样例

给定$n,m,a,b,c$，给定一个长度为$m$的数组$p[]$，给定$m$条边，构成一个$n$个点$m$条边的无向图，$Mike$想要从$a$走到$b$，再从$b$走到$c$，你可以在他从$a$出发前将$p[]$中的值分配到$m$条边上，问$Mike$最少走多少路程

**分析**

我们先将所有边的权值赋为$1$，意为两点间的最小边数为多少

如果$a$到$b$和$b$到$c$的最短路不重合，那就直接将两条路上的边从小到大赋值即可，问题在于有重合的部分路径

发现$\sum n\leq 2\cdot 10^5$，我们可以枚举重合的点$i$，让$Mike$走路径$a->i->b->i->c$，然后求得边数，其中$i->b$的路径为$p[]$中最小的几个元素，因为要走两遍，$i->a$和$i->c$的的路径为剩下元素中最小的元素

由于为无向图，$i$到三点距离即为三点到$i$距离，为表述方便，皆用$i$到三点表述

枚举$i$肯定不能以$i$为起点求最短路，否则时间复杂度太高，则可以以三点求最短路，然后枚举$i$

先计算$i->a$的边数，以$a$为起点，使用$Dijkstra$算法，再计算$i->b$的边数，以$b$为起点，使用$Dijkstra$算法，再计算$i->c$的边数，以$c$为起点，使用$Dijkstra$算法，其中不同的距离设为$disa[],disb[],disc[]$

因为是求路径权值和，可直接排序后计算前缀和$sum[]$

设$i->a$的路径为$disai$，$i->$的b路径为$disbi$，$i->c$的路径为$disci$，则答案为$sum[disai + disbi + disci] + sum[disbi]$的最小值(三边总的前缀和加上$i->b$的二次计算)

由于$i$到三点的路径不可能有重叠（否则取重叠点可使得答案更小），因此三条路径和小于$m$，正好使得$disai + disbi + disci$不会超出$sum[]$的范围

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
const int maxn = (ll) 2e5 + 5;
const int mod = (ll) 1e9 + 7;
const int inf = 0x3f3f3f3f;
int T = 1;

struct edge {
    int v, next, w;
} e[maxn << 1];

struct node {
    int dis, u;

    bool operator<(const node &b) const {
        return dis > b.dis;
    }
};

int cnt;
int head[maxn];
int disa[maxn];
int disb[maxn];
int disc[maxn];
bool vis[maxn];

void addedge(int u, int v, int w) {
    e[++cnt].next = head[u];
    e[cnt].v = v;
    e[cnt].w = w;
    head[u] = cnt;
    e[++cnt].next = head[v];
    e[cnt].v = u;
    e[cnt].w = w;
    head[v] = cnt;
}

int n, m, s;

void dijkstra_a() {
    priority_queue<node> q;
    disa[s] = 0;
    node st;
    st.dis = 0;
    st.u = s;
    q.push(st);
    while (!q.empty()) {
        node u = q.top();
        q.pop();
        if (vis[u.u])
            continue;
        vis[u.u] = true;
        for (int i = head[u.u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (disa[v] > disa[u.u] + e[i].w) {
                disa[v] = disa[u.u] + e[i].w;
                node w;
                w.dis = disa[v];
                w.u = v;
                q.push(w);
            }
        }
    }
}

void dijkstra_b() {
    priority_queue<node> q;
    disb[s] = 0;
    node st;
    st.dis = 0;
    st.u = s;
    q.push(st);
    while (!q.empty()) {
        node u = q.top();
        q.pop();
        if (vis[u.u])
            continue;
        vis[u.u] = true;
        for (int i = head[u.u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (disb[v] > disb[u.u] + e[i].w) {
                disb[v] = disb[u.u] + e[i].w;
                node w;
                w.dis = disb[v];
                w.u = v;
                q.push(w);
            }
        }
    }
}

void dijkstra_c() {
    priority_queue<node> q;
    disc[s] = 0;
    node st;
    st.dis = 0;
    st.u = s;
    q.push(st);
    while (!q.empty()) {
        node u = q.top();
        q.pop();
        if (vis[u.u])
            continue;
        vis[u.u] = true;
        for (int i = head[u.u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (disc[v] > disc[u.u] + e[i].w) {
                disc[v] = disc[u.u] + e[i].w;
                node w;
                w.dis = disc[v];
                w.u = v;
                q.push(w);
            }
        }
    }
}

int num[maxn], sum[maxn];

void solve() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    int a, b, c;
    cin >> n >> m >> a >> b >> c;
    for (int i = 1; i <= m; ++i)
        cin >> num[i];
    sort(num + 1, num + 1 + m);
    for (int i = 1; i <= m; ++i)
        sum[i] = sum[i - 1] + num[i];
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        addedge(u, v, 1);
    }
    s = a;
    for (int i = 1; i <= n; ++i) {
        disa[i] = disb[i] = disc[i] = inf;
        vis[i] = false;
    }
    dijkstra_a();
    s = b;
    for (int i = 1; i <= n; ++i)
        vis[i] = false;
    dijkstra_b();
    s = c;
    for (int i = 1; i <= n; ++i)
        vis[i] = false;
    dijkstra_c();
    int ans = LLONG_MAX;
    for (int i = 1; i <= n; ++i) {
        int disai = disa[i];
        int disbi = disb[i];
        int disci = disc[i];
        if (disai + disbi + disci > m)
            continue;
        int now = sum[disai + disbi + disci] + sum[disbi];
        ans = min(ans, now);
    }
    cout << ans << '\n';
}


signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

