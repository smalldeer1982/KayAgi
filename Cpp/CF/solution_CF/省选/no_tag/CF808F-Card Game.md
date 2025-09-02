# Card Game

## 题目描述

集卡游戏最近十分流行。所以 Vova 决定尝试这其中的一款游戏。

Vova 的收藏中有 $n$ 张卡片。每一张卡上有三个数字，分别代表它的能量 $p_i$，魔力值 $c_i$ 和等级 $l_i$。Vova 想要创建一个总能量不小于 $k$ 的卡组，但是魔力值可能不允许他这样做 — Vova 不能把两张魔力值之和为质数的卡片放在同一个卡组里。他也不能使用（即放进卡组）一张等级高于他自己角色等级的卡片。

现在 Vova 的角色等级为 $1$。帮助 Vova 来求出他需要达到的最小角色等级来创建一套满足总能量条件的卡组。

## 样例 #1

### 输入

```
5 8
5 5 1
1 5 4
4 6 3
1 12 4
3 12 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 7
4 4 1
5 8 2
5 3 3
```

### 输出

```
2
```

# 题解

## 作者：enucai (赞：8)

## Preface

看了到了 CF 上一位老哥的提交，觉得非常神奇，**非网络流做法**，成功跑进 15ms。

## Analysis

随机。每次将还未确定的排列随机打乱，逐个检查能否与之前枚举到的物品的魔力值之和为质数，如果都**不是质数**，则贪心地把他加入选择的队列中。最后检查这样的方法是否比原来得出的答案优。

若得到更优的结果 $V$，则将魔力值 $\ge V$ 的物品全部设置为 “已确定”的，即**不会在后面选择**，因为已经得到了魔力值最小为 $V$ 的答案。这样随到正解的概率会增大。

复杂度 $O(Tn^2)$，其中 $T$ 为随即次数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define int long long
#define N 200000
int n,k,vis[N+10],num[110];
struct node{
	int p,c,l;
}a[110];
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	For(i,2,N) if(!vis[i]) for(int j=2*i;j<=N;j+=i) vis[j]=i;
	cin>>n>>k;
	For(i,1,n) cin>>a[i].p>>a[i].c>>a[i].l;
	int len=n,res=1e9;
	For(step,1,500){
		random_shuffle(a+1,a+len+1);
		int sz=0,mx=0,sum=0,i;
		for(i=1;i<=len&&sum<k;i++){
			int j=1; while(vis[num[j]+a[i].c]&&j<=sz) j++;
			if(j>sz) num[++sz]=a[i].c,mx=max(mx,a[i].l),sum+=a[i].p;
			if(sum>=k) res=min(res,mx);
		}
		if(i<=len){
			int tot=0;
			For(j,1,len) if(a[j].l<mx) a[++tot]=a[j];
			len=tot;
		}
	}
	if(res==1e9) cout<<"-1\n";
	else cout<<res<<"\n";
}
```

---

## 作者：RainFestival (赞：7)

我们先枚举 $x$ 为 Vova 最小要达到的等级。

现在问题转化为**等级为** $x$ **时，Vova 最大的能量和。**

首先，因为每一张卡片的能量都 $>0$ ,我们先选所有等级 $\le x$ 的卡片，然后为避免冲突，删除最小的能量和。

我们可以构造一个最小割。

以下我们用 $s$ 代表网络源点， $t$ 代表网络汇点，第 $i$ 张卡片对应点 $i$ ,并且我们只考虑等级 $\le x$ 的卡片。

我们要满足的条件是:**Vova 不能把两张魔力值之和为质数的卡片放在同一个卡组里**

#### 那么我们对于两张魔力值之和为质数的卡片所对应的两个点连一条边，流量无限， $s$ 向其中一个点连接流量为其权值的边，另一个点向 $t$ 连接流量为其权值的边。

这里解释一下，设这些边为 $s->x->y->t$。我们割掉 $s->x$ 的边，意味着不选 $x$ 卡片；割掉 $y->t$ 的边，意味着不选 $y$ 卡片；割掉 $x->y$ 的边没有意义，所以流量无限。

那对于一对冲突的卡片 $(x,y)$ ,我们是 $s->x->y->t$ 还是 $s->y->x->t$ ？

模仿“骑士共存问题”，我们考虑找到其中的**二分图关系**，即把全图（不包括 $s$ , $t$）分成两部分 $X,Y$ ，使得只有两部分之间的连边，没有某一部分中的连边。换句话说，对于 $\forall x,y,x\in X,y\in Y$ ,没有 $(x,y)$ 或者 $(y,x)$ 的边。然后我们将 $s$ 向 $X$ 中的点连边，$Y$ 中的点向 $t$ 连边。

怎么找 $X,Y$ 呢？注意到每个魔力值都是正整数，而正整数有天然二分关系：奇数为 $X$ ,偶数为 $Y$ 。以下用 $o$ 代表一个奇数, $e$ 代表一个偶数。

我们知道，$o+o=e,o+e=o,e+o=e,e+e=e$ 。

注意到**质数几乎总是奇数**，所以产生冲突的两张卡片，魔力值一定是一奇数一偶数。然后就找到了二分图关系。

但我们说**质数“几乎”总是奇数**，质数 $2$ 不是奇数，很可惜，有可能两个奇数卡片（姑且这么说）或两个偶数卡片可能会冲突。

但 $2$ 这个数非常小，如果两个正整数之和 $=2$ ,只可能是 $1+1$。

所以我们对于魔力值为 $1$ 的卡片只能取一张，当然要选取能量值最大的，在最初选择所有卡片时即可判定。

所以我们连边完成。

因为~~原则上，网络流题不能卡 dinic 与 ISAP~~ ，所以我们可以放心使用 dinic

代码如下：

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
struct graph
{
	struct edge
	{
		int to,cap,opp;
	};
	std::vector<edge> a[505];
	int n,s,t,dep[505],nxt[505],can[505];
	void add(int x,int y,int v)
	{
		int p=a[x].size(),q=a[y].size();
		a[x].push_back(edge{y,v,q});
		a[y].push_back(edge{x,0,p});
	}
	int bfs(int s,int t)
	{
		std::queue<int> q;
		for (int i=1;i<=n;i++) dep[i]=0,nxt[i]=1,can[i]=0;
		q.push(s);dep[s]=1;
		while (!q.empty())
		{
			int v=q.front();q.pop();
			for (int i=0;i<a[v].size();i++)
            {
                int u=a[v][i].to;
                if (!dep[u]&&a[v][i].cap) dep[u]=dep[v]+1,q.push(u);
			}
	    }
	    return dep[t];
	}
	int dfs(int v,int now)
	{
		if (!nxt[v]) now=0;
		if (v==t||!now) return now;
		int ss=0;
		for (int i=can[v];i<a[v].size();i++,can[v]++)
		{
			int u=a[v][i].to;
			if (dep[v]+1!=dep[u]||!a[v][i].cap) continue;
			int k=dfs(u,std::min(now,a[v][i].cap));
			if (!k) continue;
			a[v][i].cap=a[v][i].cap-k;
			a[u][a[v][i].opp].cap=a[u][a[v][i].opp].cap+k;
			ss=ss+k;now=now-k;
			if (!now){can[v]--;break;}
		}
		if (!ss) nxt[v]=0;
		return ss;
	}
	int dinic(int ss,int tt)
	{
		s=ss,t=tt;
		int ans=0;
		while (bfs(s,t)) ans=ans+dfs(s,1000000000);
		return ans;
	}
	void clear()
	{
		for (int i=1;i<=n;i++) a[i].clear();
		n=0;
	}
};
graph g;
int n,k,p[105],c[105],l[105];
int isprime(int x)
{
	if (x<2) return 0;
	for (int i=2;i*i<=x;i++) if (x%i==0) return 0;
	return 1;
}
int solve(int x)
{
	g.clear();g.n=n+2;
	int s=n+1,t=n+2;
	int y=0,ss=0;
	for (int i=1;i<=n;i++) if (l[i]<=x&&c[i]!=1&&c[i]%2==1)
	    for (int j=1;j<=n;j++) if (l[j]<=x&&c[j]!=1&&c[j]%2==0)
	        if (isprime(c[i]+c[j])) g.add(i,j,1000000000);
	//special solve 1(1+1=2,a prime)
	for (int i=1;i<=n;i++)//find 1 has maximum value
	    if (c[i]==1&&l[i]<=x) if (p[y]<p[i]) y=i;
	for (int i=1;i<=n;i++)
	    if (c[i]!=1&&l[i]<=x&&isprime(c[y]+c[i])&&c[i]%2==0) g.add(y,i,1000000000);
	for (int i=1;i<=n;i++)
	{
		if (l[i]>x||c[i]==1&&i!=y) continue;
		if (c[i]%2) g.add(s,i,p[i]);
		else g.add(i,t,p[i]);
		ss=ss+p[i];
	}
	int ans=g.dinic(s,t);
	return ss-ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) scanf("%d%d%d",&p[i],&c[i],&l[i]);
	for (int i=1;i<=100;i++) if (solve(i)>=k) return printf("%d\n",i),0;
	puts("-1");
	return 0;
}
```

然后就可以体验 AC 的快乐了！


---

## 作者：ran_qwq (赞：1)

非常好网络流题，使我链式前向星 `id` 初值设 $0$ 虚空调试半小时。

等级的限制可以二分掉，只考虑 $l_i\le x$ 的牌。

不能选两数和为质数的限制比较奇怪，很难用其他算法刻画，只能暂且表述为两个数不能同时选，再去进一步挖掘性质。现在已经把问题转化为一般图带权最大独立集问题，很遗憾这是 NP。

尝试不考虑 $c_i=1$ 的情况。此时 $c_i+c_j\le4$，如果是质数必是奇数，即 $c_i,c_j$ 一奇一偶。

只有一奇一偶的时候才有边，建出来的图就是二分图。可以直接跑网络流，答案等于总权值减去最大流。具体建边就是把奇数放一边和源点连边权为权值的边，偶数放另一边和汇点连边权为权值的边，奇偶之间不矛盾的连边权为无穷大的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/ejhchuwz.png)

现在考虑 $c_i=1$ 的情况。显然 $c_i=1$ 的最多只能选一个，如果要选肯定贪心选 $p_i$ 最大的。

我们惊奇地发现，只保留一个 $c_i=1$ 的，$c_i+c_j$ 至少为 $3$，也没有偶质数，还是一个二分图。所以也可以跑网络流。

```cpp
int n,m,tot,rs,ps,sm,vis[M];
struct NODE {int p,c,l;} a[N],b[N];
struct MF {
	int id,S,T,hd[N],cur[N],dep[N];
	struct EDGE {int to,w,ne;} e[E];
	void Add(int u,int v,int w) {e[++id]={v,w,hd[u]},hd[u]=id;}
	void add(int u,int v,int w) {Add(u,v,w),Add(v,u,0);}
	void bld() {
		ps=sm=0,id=1,S=tot+1,T=tot+2,mst(hd,0);
		for(int i=1;i<=tot;i++) if((b[i].c&1)&&b[i].c>1) for(int j=1;j<=tot;j++)
			if((~b[j].c&1)&&!vis[b[i].c+b[j].c]) add(i,j,INF);
		for(int i=1;i<=tot;i++) if(b[i].c==1&&b[i].p>b[ps].p) ps=i;
		for(int i=1;i<=tot;i++) if((~b[i].c&1)&&!vis[b[i].c+1]) add(ps,i,INF);
		for(int i=1;i<=tot;i++) if(b[i].c>1||i==ps) sm+=b[i].p,b[i].c&1?add(S,i,b[i].p):add(i,T,b[i].p);
	}
	int bfs() {
		queue<int> q; q.push(S),mst(dep,0),dep[S]=1;
		for(int u;!q.empty();) {
			u=q.front(),q.pop();
			for(int i=hd[u],v;i;i=e[i].ne) if(!dep[v=e[i].to]&&e[i].w)
				{dep[v]=dep[u]+1,q.push(v); if(v==T) return 1;}
		}
		return 0;
	}
	int dfs(int u,int sum) {
		if(u==T) return sum; int v,res=0,tmp;
		for(int &i=cur[u];i&&sum;i=e[i].ne) if(dep[v=e[i].to]==dep[u]+1||!e[i].w)
			tmp=dfs(v,min(sum,e[i].w)),sum-=tmp,res+=tmp,e[i].w-=tmp,e[i^1].w+=tmp;
		return res;
	}
	int cc() {int res=0; while(bfs()) mcp(cur,hd),res+=dfs(S,INF); return res;}
} mf;
int chk(int x) {
	tot=0; for(int i=1;i<=n;i++) if(a[i].l<=x) b[++tot]=a[i];
	mf.bld(); return sm-mf.cc()>=m;
}
void QwQ() {
	n=rd(),m=rd(),rs=n+1;
	for(int i=1;i<=n;i++) a[i]={rd(),rd(),rd()};
	for(int i=2;i<=M-10;i++) for(int j=i*2;j<=M-10;j+=i) vis[j]=1;
	for(int l=1,r=n,md;l<=r;) chk(md=l+r>>1)?r=(rs=md)-1:l=md+1;
	wr(rs>n?-1:rs,"\n");
}
```

---

## 作者：I_am_Accepted (赞：1)

~~5ab 写错 Dinic 当前弧。~~

二分答案，我们求特定等级能达到的最大能量。

发现「两两和不为素数」条件不太好搞，尝试建图。

若两个卡上魔法值之和为素数，则将两个卡之间连无向边。

我们要求这个图的最大权（权为能量值）独立集。

发现除了 $1+1=2$ 外和为素数的两数一定一奇一偶。

我们把魔法值为 $1$ 的暂且剔除，剩下一定组成**二分图**。

众所周知，二分图最大权独立集是可以用 Dinic $O(n^2m)$ 做的。

最后考虑魔法值 $1$，发现只有可能选一张，我们选能量最大的放进去跑网络流。

```cpp
//We'll be counting stars.
//#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int ll
#define V 200000
#define N 110
#define M 2610
const int inf=1e15;
int n,p[N],c[N],L[N];
bool vis[V+1];
vector<int> pr;
void init(){
	For(i,2,V){
		if(!vis[i]){
			pr.pb(i);
		}
		for(int j:pr){
			if(i*j>V) break;
			vis[i*j]=1;
			if(i%j==0) break;
		}
	}
}
struct edge{
	int nxt,to,flow;
}e[2*M];
int head[N],cur[N],tot,dis[N];
pair<int,int> q[N];//p c
int lim,S,T;
void adde(int x,int y,int z){
	e[++tot]=(edge){head[x],y,z};head[x]=tot;
	e[++tot]=(edge){head[y],x,0};head[y]=tot;
}
queue<int> Q;
bool bfs(){
	fill(dis+1,dis+T+1,0);
	dis[S]=1;
	Q.push(S);
	int x;
	while(!Q.empty()){
		x=Q.front();
		Q.pop();
		cur[x]=head[x];
		for(int i=head[x],to;i;i=e[i].nxt){
			to=e[i].to;
			if(!e[i].flow || dis[to]) continue;
			dis[to]=dis[x]+1;
			Q.push(to);
		}
	}
//	For(i,1,T) cout<<dis[i]<<" "; cout<<endl;
	return dis[T];
}
int dfs(int x,int flow){
	if(x==T) return flow;
	int res=0;
	for(int &i=cur[x],to,tmp;i;i=e[i].nxt){
		to=e[i].to;
		if(dis[to]!=dis[x]+1 || !e[i].flow) continue;
		tmp=dfs(to,min(flow,e[i].flow));
		e[i].flow-=tmp;
		e[i^1].flow+=tmp;
		res+=tmp;
		flow-=tmp;
		if(!flow) break;
	}
	return res;
}
int work(int val,bool one){
	lim=0;
	For(i,1,n) if(L[i]<=val && c[i]!=1 && (!one || vis[c[i]+1])) q[++lim]=mkp(p[i],c[i]);
	S=lim+1;T=lim+2;
	fill(head+1,head+T+1,0);
	tot=1;
//	For(i,1,lim) cout<<q[i].fir<<"%"<<q[i].sec<<endl;
	For(i,1,lim) For(j,i+1,lim) if(!vis[q[i].sec+q[j].sec]){
//		cout<<i<<"^"<<j<<endl;
		if(q[i].sec&1) adde(i,j,inf);
		else adde(j,i,inf);
	}
	For(i,1,lim)
		if(q[i].sec&1) adde(S,i,q[i].fir);
		else adde(i,T,q[i].fir);
	int res=0;
	For(i,1,lim) res+=q[i].fir;
	while(bfs()) res-=dfs(S,inf);
//	cout<<val<<"~"<<one<<":"<<res<<endl;
	return res;
} 
int32_t main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	init();
	int k,l=1,r=0,mid,res=-1;
	cin>>n>>k;
	For(i,1,n) cin>>p[i]>>c[i]>>L[i];
	For(i,1,n) ckmx(r,L[i]);
	int p1;
	while(l<=r){
		mid=(l+r)>>1;
		p1=0;
		For(i,1,n) if(c[i]==1 && L[i]<=mid) ckmx(p1,p[i]);
		if(work(mid,0)>=k || (p1 && work(mid,1)>=k-p1)){
			res=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	cout<<res<<endl;
return 0;}
```

---

## 作者：RockyYue (赞：0)

#### CF808F: 最小割处理选取限制关系

$n$ 个物品，每个物品有属性 $l_i,c_i,p_i$，要求从中取若干物品构成集合 $\{S\}$，满足 $\sum_{i\in S} p_i\ge k$ 且 $\forall i,j\in S,c_i+c_j$ 非质数，求 $\max_{i\in S}\{l_i\}$ 最小值。

$n,l_i\le 100$，$1\le c_i,p_i\le 10^5$。

#### Sol

限制过多，简化之，从 $l$ 开始：二分 $l$ 最大值 $maxl$，后续只考虑 $l_i\le maxl$，计算满足 $c$ 条件下 $p$ 之和最大值。

选取类问题，想强制选/不选的关系建图是否是 $k$ 部图。如本题中以物品为点，$c_i+c_j$ 为质数则连边 $(i,j)$，若按 $c_i$ 奇偶性分为两组，除了 $c_i=c_j=1$ 的情况不会有同组连边，这种情况可以只留下 $p$ 更大的物品，二分图关系成立。

考虑最小割，将损失体现在边权上，这里即为未选取点的 $p$。用每条 $S$ 到 $T$ 的路径表示一组限制，想使选取合法则每条路径上至少删掉一条边，符合最小割模型，这样的好处是，每条路径形式相同。则 $S$ 向 $c_i$ 为奇点连边，边权为 $p_i$，$c_i$ 为偶点则向 $T$ 连边。

$\sum p$ 最大值则为所有 $p$ 之和减去上图最小割，一次二分完成。

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF808F)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/09/01/CF808F%20Card%20Game/)

## 前言

感觉是打过的一场模拟赛里面的一道题的弱化版，比较轻松地做了出来。

### 前置芝士

网络流

## 分析

不难发现答案具有单调性，所以我们可以二分最终的等级 $x$，现在问题就转化成了等级为 $x$ 时获得的最大能量。

然后我们想到把两张不满足要求的卡牌连边，那么我们要求的就是图中的最大独立集，这玩意在一般图中是 NPC 的，所以我们考虑一些特殊性质，观察到，质数除了 $2$ 都是奇数，所以我们如果把 $2$ 的情况排除掉就能得到一个二分图 (按奇偶分左右)，然后又观察到 $2 = 1 + 1$，所以 $1$ 只能选一张，贪心地选能量最大的即可，建完图后跑 dinic 即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10, M = 110, INF = 1 << 30;
int h[N], e[N], ne[N], f[N], idx;
int d[N], cur[N];
int v[N], primes[N], cnt;
int s, t;
struct node
{
    int p, c, l;
} a[M];
int n, k;

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void add(int a, int b, int c)
{
    e[idx] = b;
    f[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

inline void init()
{
    for (int i = 2; i <= 200000; i++)
    {
        if (!v[i]) primes[++cnt] = i;
        for (int j = 1; j <= cnt && primes[j] <= 200000 / i; j++)   
        {
            v[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

inline bool bfs()
{
    memset(d, -1, sizeof d);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    cur[s] = h[s];
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = h[u]; ~i; i = ne[i])
        {
            int v = e[i];
            if (d[v] == -1 && f[i])
            {
                d[v] = d[u] + 1;
                cur[v] = h[v];
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

inline int find(int u, int lim)
{
    if (u == t) return lim;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < lim; i = ne[i])
    {
        cur[u] = i;
        int v = e[i];
        if (d[v] == d[u] + 1 && f[i])
        {
            int t = find(v, min(f[i], lim - flow));
            if (!t) d[v] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

inline int dinic()
{
    int res = 0, flow;
    while (bfs()) while (flow = find(s, INF)) res += flow;
    return res;
}

inline bool check(int x)
{
    memset(h, -1, sizeof h);
    idx = 0;
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].l > x) continue;
        if (!(a[i].c & 1)) add(s, i, a[i].p), add(i, s, 0), tot += a[i].p;
        else if (a[i].c != 1) add(i, t, a[i].p), add(t, i, 0), tot += a[i].p;
    }
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++)
        {
            if (a[i].l > x || a[j].l > x || a[i].c & 1 || !(a[j].c & 1) || v[a[i].c + a[j].c] || a[i].c == 1 || a[j].c == 1) continue;
            add(i, j, INF);
            add(j, i, 0);
        }
    int mx = 0, p = 0;
    for (int i = 1; i <= n; i++)
        if (a[i].l <= x && a[i].c == 1 && a[i].p > mx)
            mx = a[i].p, p = i;
    if (p)
    {
        tot += mx;
        add(p, t, mx);
        add(t, p, 0);
        for (int i = 1; i <= n; i++)
            if (!(a[i].c & 1) && !v[a[i].c + 1])
                add(i, p, INF), add(p, i, 0);
    }
    int res = dinic();
    return tot - res >= k;
}

int main()
{
    init();
    n = read(), k = read();
    for (int i = 1; i <= n; i++)
        a[i].p = read(), a[i].c = read(), a[i].l = read();
    int l = 1, r = n;
    s = 0, t = n + 1;
    bool flag = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, flag = true;
        else l = mid + 1;
    }
    printf("%d\n", flag ? l : -1);
    return 0;
}
```



---

## 作者：5ab_juruo (赞：0)

首先发现和为质数这东西没有什么很好的维护方法，又看到 $n$ 这么小，考虑直接算。

先二分等级 $l$，把问题转化成某些卡牌不能同时选，求能选的卡牌权值和最大值。这东西类似于最大独立集，而这东西在一般图上是不太可做的。

注意到 $2$ 以上的质数都是奇数，而奇数只有可能是偶数和奇数的和。所以将卡牌按奇偶分。有一个特例是 $1$，但 $1$ 只会选 $1$ 张，然后就正常考虑好了。

考虑如下构造：建立超级原点 $S$ 和超级汇点 $T$，$S$ 向所有偶数连流量为其 $p_i$ 的边，所有奇数向 $T$ 连流量为其 $p_i$ 的边，而在不能同时选的偶数和质数间连流量为无穷大的边。这样，求出来的最小割一定能使剩下的 $p_i$ 和最大，且两两不冲突。

Dinic 当前弧写挂了，删掉就过了，跑得飞快，写题解的时候最优解第二。

```cpp
/* name: CF808F
 * author: 5ab
 * created at: 22-07-08 20:31
 */
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const int max_n = 100, max_nd = max_n + 2, max_m = max_n * max_n + max_n + max_n, max_c = 200000, INF = 0x3f3f3f3f;

struct nd
{
	int p, c, l, id;
};
nd a[max_n];
bool isp[max_c+1];
int hd[max_nd], des[max_m<<1], val[max_m<<1], nxt[max_m<<1], cur[max_nd], dis[max_nd], e_cnt, n, k;

void add(int s, int t, int v)
{
	des[e_cnt] = t, val[e_cnt] = v;
	nxt[e_cnt] = hd[s], hd[s] = e_cnt++;
	
	des[e_cnt] = s, val[e_cnt] = 0;
	nxt[e_cnt] = hd[t], hd[t] = e_cnt++;
}

inline int my_min(int a, int b) { return (a < b)? a:b; }
int dfs(int id, int curf)
{
	if (id == n + 1)
		return curf;
	
	int ret = 0, tmp;
	
	for (int p = cur[id]; p != -1; p = nxt[p])
		if (val[p] && dis[des[p]] == dis[id] + 1)
		{
			tmp = dfs(des[p], my_min(val[p], curf));
			val[p] -= tmp, val[p^1] += tmp, ret += tmp, curf -= tmp;
			if (!curf)
				return ret;
		}
	return ret;
}

queue<int> q;
bool bfs()
{
	memset(dis, 0x3f, sizeof dis);
	q.push(n), dis[n] = 0;
	
	int cd;
	while (!q.empty())
	{
		cd = q.front();
		q.pop();
		
		for (int p = hd[cd]; p != -1; p = nxt[p])
			if (val[p] > 0 && dis[des[p]] > dis[cd] + 1)
			{
				dis[des[p]] = dis[cd] + 1;
				q.push(des[p]);
			}
	}
	
	return dis[n+1] < INF;
}

bool check(int lim)
{
	e_cnt = 0;
	memset(hd, -1, sizeof hd);
	
	int mxc = 0, mxp = -1, psm = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i].l > lim)
			break;
		if (a[i].c == 1)
		{
			if (a[i].p > mxc)
			{
				mxc = a[i].p;
				mxp = i;
			}
		}
		else
		{
			psm += a[i].p;
			if (a[i].c & 1)
				add(n, i, a[i].p);
			else
				add(i, n + 1, a[i].p);
			
			for (int j = 0; j < i; j++)
				if (a[j].c > 1 && !isp[a[j].c+a[i].c])
				{
					if (a[i].c & 1)
						add(i, j, INF);
					else
						add(j, i, INF);
				}
		}
	}
	if (mxp != -1)
	{
		add(n, mxp, mxc);
		for (int i = 0; i < n; i++)
			if (a[i].c > 1 && !isp[a[i].c+1])
				add(mxp, i, INF);
	}
	
	for (int i = 0; i < n + 2; i++)
		cur[i] = hd[i];
	
	int ans = 0;
	while (bfs())
		ans += dfs(n, INF);
	
	return psm + mxc - ans >= k;
}

signed main()
{
	isp[0] = isp[1] = true;
	for (int i = 2; i <= max_c; i++) if (!isp[i])
		for (int j = i + i; j <= max_c; j += i)
			isp[j] = true;
	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> a[i].p >> a[i].c >> a[i].l, a[i].id = i;
	sort(a, a + n, [](const nd& a, const nd& b) {
		return (a.l == b.l) ? (a.id < b.id) : (a.l < b.l);
	});
	
	int lb = 1, ub = n + 1, mid, ans = -1;
	
	while (lb < ub)
	{
		mid = (lb + ub) >> 1;
		if (check(mid))
			ans = mid, ub = mid;
		else
			lb = mid + 1;
	}
	cout << ans << endl;
	
	return 0;
}
```

---

