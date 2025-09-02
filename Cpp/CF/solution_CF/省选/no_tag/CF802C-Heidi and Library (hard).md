# Heidi and Library (hard)

## 题目描述

The good times at Heidi's library are over. Marmots finally got their internet connections and stopped coming to the library altogether. Not only that, but the bookstore has begun charging extortionate prices for some books. Namely, whereas in the previous versions each book could be bought for 1 CHF, now the price of book $ i $ is $ c_{i} $ CHF.

## 说明/提示

The first three sample cases are repeated, but the fourth one is new.

In the fourth test case, when buying book $ 3 $ , Heidi should discard either book $ 1 $ or $ 2 $ . Even though book $ 2 $ will be requested later than book $ 1 $ , she should keep it, because it is so expensive to buy again.

## 样例 #1

### 输入

```
4 80
1 2 2 1
1 1 1 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 1
1 2 2 1
1 1 1 1
```

### 输出

```
3```

## 样例 #3

### 输入

```
4 2
1 2 3 1
1 1 1 1
```

### 输出

```
3```

## 样例 #4

### 输入

```
7 2
1 2 3 1 1 1 2
1 10 1 0 0 0 0
```

### 输出

```
13```

# 题解

## 作者：mrsrz (赞：17)

费用流。

如果第$i$天和第$j$天都出现了同一种书，且第$i\sim j-1$天没有扔掉，则只需要花费1本的价格。如果扔掉了，则要花费2本的价格。

显然，如果在$i\sim j-1$中某一天要扔掉这本书，在第$i$天购入后直接扔掉并不会使答案变劣。

我们用费用流，很难一天一天考虑买还是不买，只能全都都先买进来。考虑一种操作，能把多余的购入花费抵消掉。

考虑第$i$天购入的一本书，如果留到了第$j$天，我们可以在第$j-1$天“卖”掉这本书，获得相应的收入。这样就相当于第$j$天没有买这本书。

建图方法如下：

对每天都有两个节点$v_i,v'_i$，表示入点和出点。

从源点向每个$v_i$连容量为1，费用为当天这种书的价格$c_{a_i}$的边，表示每本书。

从每个$v_i$向$v_{i+1}$连容量为$k-1$，费用为0的边，表示第$i$天书架最多留$k-1$本书，剩下1个位置给第$i+1$天的书。

从每个$v_i$向$v'_i$连容量为1，费用为0的边，表示当天买来就扔掉了这本书。

从$v_{i-1}$向$a_i$上一次的出现位置$j$对应的$v'_ j$连容量为1，费用为$ -c_{a_i}$的边，表示卖掉这本书。

从每个$v'_i$向汇点连容量为1，费用为0的边，表示要么扔，要么卖，最多选择一种。

如果当天没有扔，则当天的流一定会顺着书架往下流，直到卖掉。

由于费用流保证总费用最小，最终的费用就是答案。

## Code：
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
struct edge{
	int to,nxt,cap,cost;
}e[219744];
int head[180],cnt=1,n,k,a[88],pre[88],c[88],T,tot[88];
inline void addedge(int u,int v,int flow,int cost){
	e[++cnt]=(edge){v,head[u],flow,cost};head[u]=cnt;
	e[++cnt]=(edge){u,head[v],0,-cost};head[v]=cnt;
}
std::queue<int>q;
bool spfa(int&flow,int&cost){
	static int a[180],d[180],pre_e[180],vis[180];
	memset(a,0x3f,sizeof a);
	memset(d,0x3f,sizeof a);
	memset(vis,0,sizeof a);
	memset(pre_e,0,sizeof a);
	*d=0;
	for(q.push(0);!q.empty();){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt)
		if(e[i].cap&&d[e[i].to]>d[u]+e[i].cost){
			d[e[i].to]=d[u]+e[i].cost;
			a[e[i].to]=std::min(a[u],e[i].cap);
			pre_e[e[i].to]=i;
			if(!vis[e[i].to])vis[e[i].to]=1,q.push(e[i].to);
		}
	}
	if(d[T]==0x3f3f3f3f)return 0;
	flow+=a[T];cost+=d[T]*a[T];
	for(int i=T;i;i=e[pre_e[i]^1].to){
		e[pre_e[i]].cap-=a[T];
		e[pre_e[i]^1].cap+=a[T];
	}
	return 1;
}
int main(){
	scanf("%d%d",&n,&k);
	T=n*2+1;
	for(int i=1;i<=n;++i){
		addedge(i,i+n,1,0);
		addedge(i+n,T,1,0);
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;++i)scanf("%d",&c[i]);
	for(int i=1;i<=n;++i){
		addedge(0,i,1,c[a[i]]);
		if(pre[a[i]])
		addedge(i-1,pre[a[i]]+n,1,-c[a[i]]);
		pre[a[i]]=i;
	}
	for(int i=1;i<n;++i)addedge(i,i+1,k-1,0);
	int flow=0,cost=0;
	while(spfa(flow,cost));
	printf("%d\n",cost);
	return 0;
}
```

---

## 作者：yingjingxu_NaS2O3 (赞：9)

~~模拟赛考了个加强版，然后止步于本题限制。~~

## 思路

费用流好题。

~~我们先化简为繁。~~

直接考虑同一本书前后价格可能不同的情况。不妨给书架的每个位置一个编号，从 $1$ 到 $k$。若一本书的花费能被去掉（即不用购买），说明上一本和它相同的书到这本书之间没有访问过书架的这个位置。

考虑费用流。根据上述描述，以每一本书为点，不妨建一条从该书的上一本书到与该书同类型的上一本书的边，花费就是退掉的部分，流量限制是 $1$。

由于每个点至少被 $1$ 单位的流量经过，考虑将一个点拆成实点和虚点，之前的连边也变成了实点和虚点之间的连边。

同时在相邻实点之间连边，流量限制是 $k-1$。为了方便跑流，建立超级源点 $s$ 和超级汇点 $t$，$s$ 与所有实点连边，流量限制为 $1$，花费为书的价格，$t$ 与所有虚点连边，流量限制为 $1$，花费为 $0$。

所以不妨设计如下形式的模型：

![](https://pic1.imgdb.cn/item/6818a39f58cb8da5c8ddbea0.png)

其中 $i$ 对应的虚点是 $i+n$。

## 代码

因为是赛时代码改过来的，所以可能有一点麻烦。

```cpp
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
#define __BEGIN_MULTITEST__ \
	signed T; \
	scanf("%d",&T); \
	while(T--) \
	{
#define __END_MULTITEST__ }
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
namespace Dinic
{
	int head[200005],cur[200005],dis[200005];
	bool vis[200005];
	int cnt=1,n=0,m=0;
	int bg,ed;
	struct node{int to,nxt,cost,w;} e[4000005];
	void add(int u,int v,int cost,int w)
	{
		e[++cnt].to=v;
		e[cnt].w=w;
		e[cnt].cost=cost; 
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void AddEdge(int u,int v,int cost,int w)
	{
		add(u,v,cost,w);
		add(v,u,-cost,0);
	}
	bool bfs(int s,int t)
	{
		bg=clock();
		for(int i=1;i<=n;i++)
		{
			dis[i]=1e18;
			vis[i]=0;
		}
		memcpy(cur,head,sizeof(int)*(n+1));
		queue<int> q;
		q.push(s);
		dis[s]=0;
		vis[s]=1;
		while(!q.empty())
		{
			int tmp=q.front();
			q.pop();
			vis[tmp]=0;
			for(int i=head[tmp];i;i=e[i].nxt)
				if(e[i].w>0&&dis[e[i].to]>dis[tmp]+e[i].cost)
				{
					dis[e[i].to]=dis[tmp]+e[i].cost;
					if(!vis[e[i].to])
					{
						q.push(e[i].to);
						vis[e[i].to]=1;
					}
				}
		}
		ed=clock();
		return dis[t]!=1e18;
	}
	int dfs(int u,int t,int sum,int &minc)
	{
		if(u==t)
			return sum;
		vis[u]=1;
		int ret=0;
		for(int i=cur[u];i&&sum;i=e[i].nxt)
		{
			cur[u]=i;
			if(!vis[e[i].to]&&e[i].w>0&&dis[e[i].to]==dis[u]+e[i].cost)
			{
				int k=dfs(e[i].to,t,min(sum,e[i].w),minc);
				if(!k)
					dis[e[i].to]=1e18;
				e[i].w-=k;
				e[i^1].w+=k;
				ret+=k;
				sum-=k;
				minc+=k*e[i].cost;
			}
		}
		vis[u]=0;
		return ret;
	}
	int s,t;
	int dinic(int &ans,int &minc)
	{
		while(bfs(s,t))
		{
//			printf("spfa %ld\n",ed-bg);
			bg=clock();
			ans+=dfs(s,t,1e18,minc);
			ed=clock();
//			printf("dinic %ld\n",ed-bg);
		}
		return ans;
	}
}
using namespace Dinic;
int a[100005],b[100005],c[100005],lst[100005],pre[100005];
signed main()
{
//	__BEGIN_MULTITEST__
//	freopen("latrine.in","r",stdin);
//	freopen("latrine.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%lld",&c[i]);
	for(int i=1;i<=n;i++)
		b[i]=c[a[i]];
	for(int i=1;i<=n;i++)
	{
		if(lst[a[i]])
			pre[i]=lst[a[i]];
		lst[a[i]]=i;	
	}
	s=n<<1|1;
	t=s+1;
	for(int i=1;i<=n;i++)
		AddEdge(s,i,b[i],1);
	for(int i=1;i<=n;i++)
		AddEdge(i,i+n,0,1);
	for(int i=1;i<=n;i++)
		if(pre[i])
			AddEdge(i-1,pre[i]+n,-b[i],1);
	for(int i=1;i<=n;i++)
		AddEdge(i+n,t,0,1);
	for(int i=1;i<n;i++)
		AddEdge(i,i+1,0,m-1);
	n=n*2+2;
	int ans=0,minc=0;
	dinic(ans,minc);
	printf("%lld\n",minc);
//	__END_MULTITEST__
	return 0;
}
```

---

## 作者：George1123 (赞：9)


更咖喱棒的阅读体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/14011031.html)

---

## 题面

> [CF802C Heidi and Library (hard)](https://www.luogu.com.cn/problem/CF802C)

> 有一个大小为 $k$ 的空书架。有 $n$ 天和 $n$ 种书，每天要求书架中有书 $a_i$。每天可以多次买书，买书 $i$ 的价格为 $c_i$。每天可以扔书（因为书架满了）。求满足要求的最小代价。

> 数据范围：$1\le n,k\le 80$。

---

## 路标

很明显这是一道套路烂大街的水题，但是今天蒟蒻想讲 $3$ 种巧妙的做法。

> 此题的输出方案版：[CF132E Bits of merry old England](https://www.luogu.com.cn/problem/CF132E)

$(u,v,f,c)$ 表示连一条 $u$ 到 $v$ 容量 $f$ 费用 $c$ 的边，并建它的反悔边。

---

## 题解 1

这个蒟蒻的做法，是当前最劣解。

根据时间和书种拆点 $(time,book)$。

增加一种书种叫“空”（$n$），增加一个时间为开始时（$0$）。

先 $(s,(0,n),k,0)$，流量 $x$ 流到点 $(i,j)$ 表示在第 $i$ 时间 $x$ 这个书架位置是书 $j$。

$((i,j),(i+1,x)(x\neq j),1,c_x)$，表示这个位置换书。很明显一天换一本书足矣。

$((i,j),(i+1,j),k,0)$，表示不换书。

如果 $j=a_i$，把 $(i,j)$ 拆成 $(i,j)_0$ 和 $(i,j)_1$，$((i,j)_0,t,1,0)$，$(s,(i,j)_1,1,0)$，表示要求有 $j$ 这本书。$((i,j)_0,(i,j)_1,k-1,0)$。

$((n,j),mid,k,0)$，$(mid,t,k,0)$。$mid$ 的作用是限制流量。

然后跑图，流量必定是 $n+k$ 费用是答案。

**点数 $\Theta(n^2)$，边数 $\Theta(n^3)$。**

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);~i;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;
 
//Data
const int N=80;
int n,k,a[N],c[N];
 
//Flows
const int fN=(N+1)*(N+1)+N+3;
int fn,s,t,mid,dep[fN],pre[fN],q[fN],*ta,*he;
bool vis[fN];
vector<int> e[fN],to,fw,co;
void adde(int u,int v,int w,int c){
    // cout<<u<<' '<<v<<' '<<w<<'-'<<c<<'\n';
    e[u].pb(sz(to)),to.pb(v),fw.pb(w),co.pb(+c);
    e[v].pb(sz(to)),to.pb(u),fw.pb(0),co.pb(-c);
}
bool spfa(){
    R(u,fn) dep[u]=iinf,vis[u]=false,pre[u]=-1;
    ta=he=q,dep[*ta++=pre[s]=s]=0,vis[s]=true;
    while(ta!=he){
        int u=*he++; he-q>=fn&&(he-=fn),vis[u]=false;
        for(int v:e[u])if(fw[v]&&dep[to[v]]>dep[u]+co[v])
            dep[to[v]]=dep[u]+co[v],pre[to[v]]=v,
            !vis[to[v]]&&(*ta++=to[v],ta-q>=fn&&(ta-=fn),vis[to[v]]=true);
    }
    return dep[t]^iinf;
}
pair<int,int> flow(){
    pair<int,int> res(0,0);
    while(spfa()){
        int f=iinf;
        for(int u=t;u^s;u=to[pre[u]^1]) f=min(f,fw[pre[u]]);
        for(int u=t;u^s;u=to[pre[u]^1]) fw[pre[u]]-=f,fw[pre[u]^1]+=f;
        res.x+=f,res.y+=dep[t]*f;
    }
    return res;
}
 
//Main
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>k,fn=(t=(s=(mid=(n+1)*(n+1)+n)+1)+1)+1;
    #define p(i,j) ((i)*(n+1)+(j))
    R(i,n) cin>>a[i],--a[i]; R(i,n) cin>>c[i];
    adde(mid,t,k,0),adde(s,p(0,n),k,0);
    R(i,n+1) adde(i==a[n-1]?(n+1)*(n+1)+n-1:p(n,i),mid,k,0);
    R(i,n){
        adde(p(i+1,a[i]),t,1,0),adde(s,(n+1)*(n+1)+i,1,0);
        adde(p(i+1,a[i]),(n+1)*(n+1)+i,k-1,0);
        R(j,n+1){
            int last=(i&&j==a[i-1])?(n+1)*(n+1)+i-1:p(i,j);
            adde(last,p(i+1,j),k,0);
            R(t,n) (j^t)&&(adde(last,p(i+1,t),1,c[t]),true);
        }
    }
    pair<int,int> ns(flow());
    assert(ns.x==k+n),cout<<ns.y<<'\n';
    return 0;
}
```

---

## 题解 2

神仙 `@mrsrz` 的做法，非常巧妙。

每本需要书可以在当天先买上，如果手上已经有这本书了可以把手上这本卖了。

把每天拆成 $u_0$ 和 $u_1$，$(s,u_0,1,c_{a_u})$ 表示买书，$(u_0,u_1,1,0)$ 表示供书，$(u_1,t,1,0)$ 表示提交书，$(u_0,(u+1)_0,k-1,0)$ 表示存书（$k-1$ 是因为留给下一天的书位置），$((u-1)_0,p(a_u)_1,1,-c_{a_u})$ 表示卖书（$p(x)$ 表示第 $x$ 种书上次出现位置）。

**点数 $\Theta(n)$，边数 $\Theta(n)$。**

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);~i;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=80;
int n,k,a[N],c[N],p[N];

//Flows
const int fN=(N<<1)+2;
int fn,s,t,dep[fN],pre[fN],q[fN],*ta,*he;
bool vis[fN];
vector<int> e[fN],to,fw,co;
void adde(int u,int v,int w,int c){
    // cout<<u<<' '<<v<<' '<<w<<'-'<<c<<'\n';
    e[u].pb(sz(to)),to.pb(v),fw.pb(w),co.pb(+c);
    e[v].pb(sz(to)),to.pb(u),fw.pb(0),co.pb(-c);
}
bool spfa(){
    R(u,fn) dep[u]=iinf,vis[u]=false,pre[u]=-1;
    ta=he=q,dep[*ta++=pre[s]=s]=0,vis[s]=true;
    while(ta!=he){
        int u=*he++; he-q>=fn&&(he-=fn),vis[u]=false;
        for(int v:e[u])if(fw[v]&&dep[to[v]]>dep[u]+co[v])
            dep[to[v]]=dep[u]+co[v],pre[to[v]]=v,
            !vis[to[v]]&&(*ta++=to[v],ta-q>=fn&&(ta-=fn),vis[to[v]]=true);
    }
    return dep[t]^iinf;
}
pair<int,int> flow(){
    pair<int,int> res(0,0);
    while(spfa()){
        int f=iinf;
        for(int u=t;u^s;u=to[pre[u]^1]) f=min(f,fw[pre[u]]);
        for(int u=t;u^s;u=to[pre[u]^1]) fw[pre[u]]-=f,fw[pre[u]^1]+=f;
        res.x+=f,res.y+=dep[t]*f;
    }
    return res;
}

//Main
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>k,fn=(t=(s=n<<1)+1)+1;
    R(i,n) cin>>a[i],--a[i];
    R(i,n) cin>>c[i],p[i]=-1;
    R(i,n){
        adde(i,i+n,1,0),adde(i+n,t,1,0);
        adde(s,i,1,c[a[i]]),i+1<n&&(adde(i,i+1,k-1,0),true);
        ~p[a[i]]&&(adde(i-1,p[a[i]]+n,1,-c[a[i]]),true),p[a[i]]=i;
    }
    cout<<flow().y<<'\n';
    return 0;
}
```

---

## 题解 3

根据 `@Um_nik` 和 `@Kronecker` 写的当前 `Codeforces` 上此题最优解改编，到这里看 [原版](https://codeforces.com/problemset/submission/802/27404603)。

原理是反悔贪心，用网络流来实现。

同样把点拆成 $u_0$ 和 $u_1$，$(u_0,u_1,1,-\infty)$ 表示每次增广后都必须选此边，$(s,mid,k,0)$ 限制流量，$(mid,u_0,1,c_{a_u})$ 表示买书，$(u_1,t,1,0)$ 表示交书，$(u_1,v_0,1,c_{a_v})(u<v,a_u\neq a_v)$ 表示换书，$(u_1,v_0,1,0)(u<v,a_u=a_v)$ 表示沿用书。

然后跑图，一旦某次 `spfa` 以后 $dep_t\ge 0$ 了就停止（最小费用可行流），答案是费用 $+n\cdot \infty$。

**点数 $\Theta(n)$，边数 $\Theta(n^2)$。**

这个做法有个神奇之处：可以通过不停增加 $s$ 和 $mid$ 之间的流量并增广流量 $1$，高效地求出 $k=1\sim K$ 时的答案，只不过需要把上面那句话的停止变成连一条 $(s,t,\infty,0)$ 的边。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);~i;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=80,F=3e6;
int n,k,mid,a[N],c[N],p[N];

//Flows
const int fN=(N<<1)+3;
int fn,s,t,dep[fN],pre[fN],q[fN],*ta,*he;
bool vis[fN];
vector<int> e[fN],to,fw,co;
void adde(int u,int v,int w,int c){
    // cout<<u<<' '<<v<<' '<<w<<'-'<<c<<'\n';
    e[u].pb(sz(to)),to.pb(v),fw.pb(w),co.pb(+c);
    e[v].pb(sz(to)),to.pb(u),fw.pb(0),co.pb(-c);
}
bool spfa(){
    R(u,fn) dep[u]=iinf,vis[u]=false,pre[u]=-1;
    ta=he=q,dep[*ta++=pre[s]=s]=0,vis[s]=true;
    while(ta!=he){
        int u=*he++; he-q>=fn&&(he-=fn),vis[u]=false;
        for(int v:e[u])if(fw[v]&&dep[to[v]]>dep[u]+co[v])
            dep[to[v]]=dep[u]+co[v],pre[to[v]]=v,
            !vis[to[v]]&&(*ta++=to[v],ta-q>=fn&&(ta-=fn),vis[to[v]]=true);
    }
    return dep[t]^iinf;
}
pair<int,int> flow(){
    pair<int,int> res(0,0);
    while(spfa()){
        if(dep[t]>=0) break;
        int f=iinf;
        for(int u=t;u^s;u=to[pre[u]^1]) f=min(f,fw[pre[u]]);
        for(int u=t;u^s;u=to[pre[u]^1]) fw[pre[u]]-=f,fw[pre[u]^1]+=f;
        res.x+=f,res.y+=dep[t]*f;
    }
    return res;
}

//Main
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>k,fn=(t=(s=(mid=n<<1)+1)+1)+1,adde(s,mid,k,0);
    R(i,n) cin>>a[i],--a[i]; R(i,n) cin>>c[i];
    R(i,n) adde(mid,i,1,c[a[i]]),adde(i,i+n,1,-F),adde(i+n,t,1,0);
    R(j,n)R(i,j) adde(i+n,j,1,a[i]==a[j]?0:c[a[j]]);
    cout<<flow().y+F*n<<'\n';
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：lzyqwq (赞：3)

~~和 [CF132E](https://www.luogu.com.cn/problem/CF132E) 一起水的题以及题解，会有些许雷同。~~

不同于其它的题解，使用最小费用流，$\Theta(n^2)$ 建边，这种思路还是~~喜提最劣解~~比较好想的。

# $\texttt{Description}$

把每个容量想象成格子，便是要用不超过容量放过所有的书。把格子抽象成路径，书抽象成点，就是不多于 $k$ 条不相交（一本书只能放一个格子，显然不相交）路径覆盖所有点，使得费用最小。

- 将每个点 $v$ 拆成 $v_1$ 和 $v_2$，表示到达/出发该点。

- $S$ 向每个点 $v$ 的 $v_1$ 连容量为 $1$，费用为 $c_{a_v}$ 的边，表示只有一条路径可以（因为是不相交，下同）从 $v$ 开始，且经过它需要 $c_{a_v}$ 的费用（即初始买下第 $a_v$ 本书的费用）。

- 对于任意两点 $u,v\,(u\ne v)$，如果 $a_u\ne a_v$，那么从 $u_2$ 向 $v_1$ 连容量为 $1$，费用为 $c_{a_v}$ 的边，表示有只一条路径可以从 $u$ 出发到达 $v$，并且经过它需要 $c_{a_v}$ 的费用（即当前格子原本放的是 $a_u$，改成放 $a_v$ 需要买下这本书，并丢掉 $a_u$ 再将 $a_v$ 放上去，因此费用是买 $a_v$ 的费用 $c_{a_v}$）；否则连容量为 $1$，费用为 $0$ 的边（当前格子上的书就是我要放的书，那么不用再买它， $a_v$ 这本书就已经放上去了）。

- 每个点 $v$ 的 $v_2$ 向 $T$ 连容量为 $1$，费用为 $0$ 的边，表示只有一条路径在 $v$ 处结束。

- 每个点 $v$ 的 $v_1$ 和 $v_2$ 之间连容量为 $1$，费用为 $-\inf$ 的边。容量为 $1$ 很好理解，每个点只能经过一次。那费用为什么要这样设置呢？因为题目要求是每本书都放过，所以每个点均需经过一次，然而经过一个点就是走了 $v_1\rightarrow v_2$ 这条边。所以我们将这条边的费用设置成赋无穷，保证 $S$ 到 $T$ 的最短路径肯定经过这条边使其被增广，然而其反向边的费用就是正无穷，因此肯定不在最短路上，不会被增广，即不会被返悔掉，进而满足每个点经过后不会返回经过它的这个操作，进而满足每个点都被经过一次。

因为有 $k$ 个格子，即 $k$ 条路径，所以最多增广 $k$ 次。如果发现某次增广最短路的费用大于等于 $0$ 了，就跳出。因为最小费用流是可以保证 $n$ 个点都被经过的（上面说了），然而希望在此基础上费用尽量小，如果费用小于 $0$，说明我在使答案越来越小，并最终得到最小费用；反之，若费用大于等于 $0$，说明费用增加了，与目的相反（等于 $0$ 相当于没加，那不考虑也是可以的）。此后，费用只会越来越大，那么肯定都是不需要了的。 

最终的最小代价就是 $\text{mincost}+n\times \inf$，为什么要加上后面那一项呢？因为本来经过每个点应该不付费用，然而我却为了限流付了 $-\inf$ 的费用，相当于少付了 $\inf$ 的费用，对于 $n$ 个点，每个点都少付了，那么要将 $n$ 个点少付的费用都还回来。

# $\texttt{Solution}$

~~指令集和 `SLF + LLL SPFA` 可以快不少。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//涉及inf，防祖宗
const int N = 1e5, inf = 1e10;
int n, k, a[N], c[N], d[N], h, t, q[N], T, cnt = 1, hd[N], la[N], ans;
bool iq[N];
struct edge {
    int v, w, c, nxt;
}e[N];
inline void add(int u, int v, int w, int c) {
    e[++cnt] = edge{v, w, c, hd[u]};
    hd[u] = cnt;
}
inline void bfs() {
    for (int i = 0; i <= T; ++i) {
        d[i] = inf;
        iq[i] = 0;
    }
    d[q[h = t = 1] = 0] = 0;
    while (h <= t) {
        int x = q[h++];
        iq[x] = 0;
        for (int i = hd[x]; i; i = e[i].nxt) {
            if (e[i].w && d[x] + e[i].c < d[e[i].v]) {
                d[e[la[e[i].v] = i].v] = d[x] + e[i].c;
                if (!iq[e[i].v]) {
                    iq[q[++t] = e[i].v] = 1;
                }
            }
        }
    }
}
signed main() {
    scanf("%lld%lld", &n, &k);
    T = (n << 1) + 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &c[i]);
    }
    for (int i = 1; i <= n; ++i) {
        add(0, i, 1, c[a[i]]);
        add(i, 0, 0, -c[a[i]]);
        add(i, i + n, 1, -inf);
        add(i + n, i, 0, inf);
        add(i + n, T, 1, 0);
        add(T, i + n, 0, 0);
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] == a[j]) {
                add(i + n, j, 1, 0);
                add(j, i + n, 0, 0);
            } else {
                add(i + n, j, 1, c[a[j]]);
                add(j, i + n, 0, -c[a[j]]);
            }
        }
    }
    for (int i = 1; i <= k; ++i) {
        bfs();
        if (d[T] >= 0) {
            break;
        }
        ans += d[T];
        for (int j = T; j; j = e[la[j] ^ 1].v) {
            --e[la[j]].w;
            ++e[la[j] ^ 1].w;
        }
    }
    printf("%lld\n", ans + n * inf);
}
```


完结撒花！


---

## 作者：ltdj (赞：3)

## 题解

这是一个只需要 $n+2$ 个点的简单做法

### 如何想到

首先，容易想到的是：如果不能卖出再买入，对于一个颜色 $x$，我们在第一次出现买入，最后一次卖出。![image-20220217102809162](https://blogpicp.oss-cn-guangzhou.aliyuncs.com/ltdblogimg/image-20220217102809162.png)

上图，数轴上每个点表示一天，每天的书都可以直接流向下一天，容量为 $k$，费用为 $0$，表示放在书架。

问题是，如何考虑卖出后再买入的操作呢？

仔细想，对于相邻两个 $x$ 之间的一段(如上图红色部分),这本书要么一直在书架，要么一直不在（如果前部分在后半部分不在还不如直接在上一个 $x$  那里卖掉）。如果不在书架的话，就不会占用书架的容量，但是在下一个 $x$ 就一定要重新买。所以我们可以直接用一条额外的边连接相邻的两个 $x$,费用为 $c_x$,容量为 $1$。 

### 为什么是对的

这样做是对的吗？我们发现：如果这样做不是错的话那它一定是对的（。我们考虑到错的情况有两种：一个流流过了它不该流的边或者不该流入的汇点。

1.我们称相邻两个 $x$ 之间的边为购买边，理想状态下 $x$ 只会走 $x$ 的购买边，但实际上它可能走到 $y$ 的购买边，由于购买边流量为1，此时 $y$ 一定走的是书架边，那这种情况等价于 $y$ 走购买边而 $x$ 走书架边。所以，**一条流只要从 $x$ 第一次出现的点流入最后出现的点，那么中途无论经过什么边都是合法的**

2.假如 $x$ 流入了 $y$ 的汇点呢？事实上由于第一点，下面两种情况可以看成等价的

![image-20220217112218812](https://blogpicp.oss-cn-guangzhou.aliyuncs.com/ltdblogimg/image-20220217112218812.png)![image-20220217112332544](https://blogpicp.oss-cn-guangzhou.aliyuncs.com/ltdblogimg/image-20220217112332544.png)

而且它情况实际上都可以转化成上述情况的。



## 实现

有一个小细节，如果你完全按照上述建图，会有一个问题: 如果一个点刚买就卖了，他是不会走书架边的，但实际上它当天需要占用一个书架位置。那我们换一种思路，我们认为这本书是前一天下班的时候买的，把入边连到上一天即可。

```cpp
int main()
{
	memset(head,-1,sizeof(head)); num_edge=-1;
    N=read(), K=read();
    for(int i=1; i<=N; i++) A[i]=read();
    for(int i=1; i<=N; i++) C[i]=read();
    s=N+1, t=N+2;

    for(int i=1; i<N; i++) addEdge(i, i+1, K, 0);
    for(int i=1; i<=N; i++){
        if(!VIS[A[i]]) {
            if(i == 1) addEdge(N+1, i, 1, C[A[i]]);
            else addEdge(N+1, i-1, 1, C[A[i]]);
        }else{
            addEdge(VIS[A[i]], i-1, 1, C[A[i]]);
        }
        VIS[A[i]] = i;
    }
    for(int i=1; i<=N; i++) if(VIS[i]) addEdge(VIS[i], N+2, 1, 0);
	MCMF();
	printf("%d\n", mincost);
	return 0;
}
```

---

## 作者：QuantAsk (赞：3)

# 正题
题目链接:[https://www.luogu.com.cn/problem/CF802C](https://www.luogu.com.cn/problem/CF802C)


获取更好体验:[https://www.cnblogs.com/QuantAsk/p/15879351.html](https://www.cnblogs.com/QuantAsk/p/15879351.html)

-------

## 题目大意
你有一个可以放 $k$ 本书的书架，第 $i$ 天要求书架上有第 $a_i$ 种书，购买第 $i$ 种书的价格为 $c_i$ 。

求满足 $n$ 天要求的最小花费。

$1\leq n,k\leq 80,1\leq c_i\leq 10^6$

------

## 解题思路
我们注意到每一天的限制是不能超过 $k$ 本书延续到下一天。而书的保留我们可以考虑视为将一本书从这一天延续到下一次需要这本书的时候免费拿一本新的。

好那么现在相当于我们可以通过霸占一些区间来减少花费，但是一个格子最多被区间包含 $k$ 次。

这和[[NOI2008] 志愿者招募](https://www.luogu.com.cn/problem/P3980)很像，考虑使用费用流来做本题。

首先我们要固定总流量为 $n$ ，然后考虑怎么建图。这里将一个点拆为三部分记为 $p(x,1/2/3)$ 
1. 获取点，用来流过今天需要的书。
2. 储存点，表示流过的这本书已经使用完了。
3. 商店点，流过多余的流量，购买书时从这个点流过。

然后要实现以下功能
- 要求满足每天的条件：我们让 $p(x,1)\rightarrow p(x,2)$ ，流量为 $1$ ，费用为 $-\infty$ ,表示每天的条件必须满足。
- 延续这本书到下一个同样需求的点$y$：$p(x,2)\rightarrow p(y,1)$，流量为 $1$ ，费用为 $0$ ，表示这本书用完之后可以留给后面的用。
- 购买一本书： $p(x,3)\rightarrow p(x,1)$ ，流量为 $1$ ，费用为 $c_{a_x}$ 。
- 丢弃一本书： $p(x,2)\rightarrow p(x+1,3)$ ，流量为 $1$ ，费用为 $0$ 。因为这本书今天已经借出了所以需要占用空间，明天才能丢掉。
- 限制存有书的数量不超过 $k$ ：考虑到我们相当于总共有 $n$ 点流量，在 $1/2$ 类点之间的流量都相当于目前存在书柜里的，所以商店的书至少需要为 $n-k$ 本。那么我们让 $p(x,3)\rightarrow p(x+1,3)$ 流量为 $n-k$ ，费用为 $-\infty$ ，这样这些流量就必须流过了，然后再建立一条 $p(x,3)\rightarrow p(x+1,3)$ 流量为 $\infty$ ，费用为 $0$ 的给多余的流过就好了。

费用为 $-\infty$ 的我们设为一个很大的值，最后将答案把这些值加回去就好了。

就可以通过本题了

------

## code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
const ll N=1e4+10,inf=1e9;
struct node{
	ll to,next,w,c;
}a[N<<1];
ll n,k,tot,ans,op[N],c[N],las[N];
ll s,t,ls[N],f[N],pre[N],mf[N];
bool v[N];queue<ll> q;
void addl(ll x,ll y,ll w,ll c){
	a[++tot].to=y;a[tot].next=ls[x];ls[x]=tot;a[tot].w=w;a[tot].c=c;
	a[++tot].to=x;a[tot].next=ls[y];ls[y]=tot;a[tot].w=0;a[tot].c=-c;
	return;
}
bool SPFA(){
	memset(f,0x3f,sizeof(f));pre[t]=0;
	f[s]=0;q.push(s);v[s]=1;mf[s]=inf;
	while(!q.empty()){
		ll x=q.front();q.pop();v[x]=0;
		for(ll i=ls[x];i;i=a[i].next){
			ll y=a[i].to;
			if(a[i].w&&f[x]+a[i].c<f[y]){
				f[y]=f[x]+a[i].c;pre[y]=i;
				mf[y]=min(mf[x],a[i].w);
				if(!v[y])v[y]=1,q.push(y);
			}
		}
	}
	return pre[t];
}
ll update(){
	ll x=t;
	while(x!=s){
		a[pre[x]].w-=mf[t];
		a[pre[x]^1].w+=mf[t];
		x=a[pre[x]^1].to;
	}
	return mf[t]*f[t];
}
signed main()
{
	scanf("%lld%lld",&n,&k);tot=1;
	for(ll i=1;i<=n;i++)scanf("%lld",&op[i]);
	for(ll i=1;i<=n;i++)scanf("%lld",&c[i]);
	ll w=0;s=3*n+2;t=s+1;
	addl(s,2*n+1,n,0);
	for(ll i=1;i<=n;i++){
		if(las[op[i]])
			addl(las[op[i]]+n,i,1,0);
		else w=min(w+1,k);
		addl(i+2*n,i,1,c[op[i]]);
		addl(i,i+n,1,-inf);ans+=inf;
		addl(i+n,i+2*n+1,1,0);
		las[op[i]]=i;
		if(n>w){
			addl(i+2*n,i+2*n+1,n-w,-inf);
			ans+=(n-w)*inf;
		}
		addl(i+2*n,i+2*n+1,inf,0);
	}
	addl(3*n+1,t,n,0);
	int k=0;
	while(SPFA())ans+=update();
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Huami360 (赞：2)

[题目链接](https://www.luogu.org/problemnew/show/CF802C)

感觉跟餐巾计划问题有点像。费用流。

决定每天买不买不太好搞，不如先把所有东西都买进来，再卖掉不必要的。

拆点，每个点拆成$x,y$。

源点向每个点的$x$连费用为当天的价格，流量为1的边。

每个点的$y$向汇点连费用为0，流量为1的边。

每个点$x$向$y$连流量为1，费用为0的边。

此时流出的已经等于流入的了，也就是说最大流一定为$n$。

现在考虑加入费用限制。

每天的$x$向下一天的$x$连流量为$k-1$，费用为0的边，表示可以不扔，留到明天，但明天的书还需要一个位置，所以是$k-1$。

每天的前一天向上一个$a_i$出现的位置的$y$连一条费用为$-c_{a_i}$，流量为1的边，表示在已经有这本书的情况下，可以卖掉这本书。

此时求出最小费用即为答案。
```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#define INF 2147483647
using namespace std;
const int MAXN = 210;
const int MAXM = 200010;
queue <int> q; 
int s, t, now, n;
struct Edge{
    int from, next, to, rest, cost;
}e[MAXM];
int head[MAXN], num = 1, dis[MAXN], vis[MAXN], Flow[MAXN], pre[MAXN];
inline void Add(int from, int to, int flow, int cost){
    e[++num] = (Edge){ from, head[from], to, flow, cost }; head[from] = num;
    e[++num] = (Edge){ to, head[to], from, 0, -cost }; head[to] = num;
}
int RoadsExist(){
    q.push(s);
    memset(dis, 127, sizeof dis);
    dis[s] = 0; Flow[s] = INF; pre[t] = 0;
    while(!q.empty()){
      now = q.front(); q.pop(); vis[now] = 0;
      for(int i = head[now]; i; i = e[i].next)
         if(e[i].rest && dis[e[i].to] > dis[now] + e[i].cost){
           dis[e[i].to] = dis[now] + e[i].cost;
           pre[e[i].to] = i;
           Flow[e[i].to] = min(Flow[now], e[i].rest);
           if(!vis[e[i].to]){
             vis[e[i].to] = 1;
             q.push(e[i].to);
           }
         }
    }
    return pre[t];
}
int k, maxflow, mincost, sum;
int a[MAXN], c[MAXN], last[MAXN];
int main(){
    scanf("%d%d", &n, &k); s = 199; t = 200;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    for(int i = 1; i <= n; ++i){
       Add(s, i, 1, c[a[i]]);
       if(i != 1) Add(i - 1, i, k - 1, 0);
       Add(i, i + n, 1, 0);
       if(last[a[i]]) Add(i - 1, last[a[i]] + n, 1, -c[a[i]]);
       Add(i + n, t, 1, 0);
       last[a[i]] = i;
    }
    while(RoadsExist()){
      mincost += Flow[t] * dis[t];
      for(int i = t; i != s; i = e[pre[i]].from){
         e[pre[i]].rest -= Flow[t];
         e[pre[i] ^ 1].rest += Flow[t];
      }
    }
    printf("%d\n", mincost);
    return 0;
}

```

---

## 作者：liangbowen (赞：1)

(CF132E 是 CF802C 的范围加强+输出方案 Ver.)

平方点数都想了好久。。然后不会线性点数做法。感觉是网络流的套路掌握得不熟练啊。

---

下面先是一个垃圾做法。

发现很难维护每个时刻哪些书被存储了，所以直接让 flow 来帮我们记录。记 $id(i,j)$ 为第 $i$ 天的第 $j$ 本书的存储状态，令一个点流过了等价于被选。我们采用费用流，考察每个限制

+ 书架容量为 $k$：只需要在最后限制，因为流量守恒所以如果你前面爆了那么后面肯定也会爆。另一个问题是，如果 $k$ 很大那可能会流很多废边来加最大流，但是费用肯定就错了：所以找到出现过的元素数 $cnt$，建边 $(T^{\prime},T,\min(k,cnt),0)$。
+ 每天强制 $a_i$ 选：在点间加入限制即可，对于 $(id(i-1,j),id(i,j))$ 的边，若 $j=a_i$ 则强制流过，可以令费用为 $-\infty^{\prime}$，最后在答案加上 $n\times\infty^{\prime}$ 即可；否则 $j\ne a_i$ 时令费用为 $0$。
+ 丢书买书操作：令 $id(i,0)$ 表示空位，可以 $(id(i,j),id(i,0),1,0)$，$(id(i,0),id(i,j),1,c_i)$。

跑 MCMF，复杂度 $O(\operatorname{Flow}(n^2,n^2))$。[傻逼做法过不了加强版](https://codeforces.com/contest/132/submission/326223006)，但是至少能[通过本题](https://codeforces.com/contest/802/submission/326219030)。

线性做法见 <https://www.luogu.com.cn/article/e2ej74o9>

---

## 作者：JiaY19 (赞：1)

一道三倍经验的题目。

[一倍](https://www.luogu.com.cn/problem/CF802A)，[二倍](https://www.luogu.com.cn/problem/CF802C)，[三倍](https://www.luogu.com.cn/problem/CF132E)。

至于[这个](https://www.luogu.com.cn/problem/CF802B)长得很相似，但网络流复杂度过不去。

#### 思路

考虑~~烂大街的~~费用流。

可以发现很难单独决定每天买不买，所以可以先把所有东西都买进来，再卖掉不必要的，抵消花费。

首先进行拆点 $i$ 与 $i'$ 之间连一条费用为 $0$ ，流量为 $1$ 的边。

从原点 $s$ ，连一条费用为 $c_{a_{i}}$ ，流量为 $1$ 的边。

再从每个 $i+1$ 向 $i$ 连一条流量为 $k - 1$ ，费用为 $0$ 的边。

从 $i-1$ 向 $a_i$ 上一次的出现位置 $j$ 对应的      $j'$ 连一条流量 $1$ ，费用为 $-c_{i}$ 的边。

最后从每个 $i'$ 向汇点 $t$ 连一条流量为 $1$ ，费用为 $0$ 的边。

代码实现直接套费用流板子就可以了。

#### Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 0x3f3f3f3f;
int n , k , tot , s , t , maxf , ans , head[5010] , d[5010] , in[5010] , pre[5010] , v[5010] , a[100] , c[100] , re[100];
struct E
{
	int to , nex , fei, liu;
}e[150100];

int read()
{
	long long X = 0 , w = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
		w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		X = X * 10 + c - '0' , c = getchar();
	return X * w;
}

void add(int x , int y , int z , int u)
{
	e[++tot].to = y , e[tot].liu = z , e[tot].fei = u , e[tot].nex = head[x] , head[x] = tot;
	e[++tot].to = x , e[tot].liu = 0 , e[tot].fei = -u , e[tot].nex = head[y] , head[y] = tot;
}

bool spfa()
{
	queue<int> q;
	memset(d , inf , sizeof(d));
	memset(v , 0 , sizeof(v));
	q.push(s); d[s] = 0; v[s] = 1;
	in[s] = 1 << 30;
	while(!q.empty()) 
	{
		int x = q.front(); v[x] = 0; q.pop();
		for(int i = head[x];i;i = e[i].nex)
		{
			if(!e[i].liu) continue;
			int y = e[i].to;
			if(d[y] > d[x] + e[i].fei)
			{
				d[y] = d[x] + e[i].fei;
				in[y] = min(in[x] , e[i].liu);
				pre[y] = i;
				if(!v[y]) v[y] = 1 , q.push(y);	
			} 
		}
	}
	if(d[t] == 4557430888798830399) return 0;
	return 1;
}

void update()
{
	while(spfa())
	{
		int x = t;
		maxf += in[t];
		ans += d[t] * in[t];
		int i;
		while(x != s)
		{
			i = pre[x];
			e[i].liu -= in[t];
			e[i ^ 1].liu += in[t];
			x = e[i ^ 1].to;
		} 
	}
}

signed main()
{
	n = read() , k = read() , s = 0 , t = 2 * n + 1;
	tot = 1;
	for(int i = 1;i <= n;++i) add(i , i + n , 1 , 0) , add(i + n , t , 1 , 0) , a[i] = read();
	for(int i = 1;i <= n;++i) c[i] = read();
	for(int i = 1;i <= n;++i)
	{
		add(s , i , 1 , c[a[i]]);
		if(re[a[i]]) add(i - 1 , re[a[i]] + n , 1 , -c[a[i]]);
		re[a[i]] = i;
	}
	for(int i = 1;i < n;++i) add(i , i + 1 , k - 1 , 0);
	update();
	cout << ans;
	return 0;
}
```


---

## 作者：liyixin0514 (赞：1)

# [CF802C Heidi and Library (hard)](https://www.luogu.com.cn/problem/CF802C)

> 模拟退火爆切流题

## 题意

有一个容量为 $m$ 的书架，有 $n$ 种书，每种书有一个价格 $c_i$，有 $n$ 次操作，每次操作给出一种书 $x$，如果你的书架上面没有这种书，你就必须花费 $c_x$ 的价格买下它，否则就不用买。要求任意时刻书架上不超过 $m$ 本书。为最小花费。

## 思路

最初的方案是每买一本书就马上扔掉，花费 $\sum c_{a_i}$。然后问题转化成保留一些书，最大化价值。

考虑 $i$ 不需要买的情况，当且仅当前一个和它颜色相同的书没有被扔掉，设前一个颜色相同的是 $la_{a_i}$，那么在时间 $[la_{a_i},i)$ 中，第 $la_{a_i}$ 本书会一直在书架上面。

因此问题就是有 $O(n)$ 个区间，最大化选择的区间价值，使得每个时间被覆盖的次数不超过 $m-1$（不是 $m$，因为每个时间你需要一个空的位置来买书以及马上扔掉）。

这个非常的网络流，但是我不会建模。。。

## 模拟退火

于是可以模拟退火。给所有区间钦定一个选择顺序，然后按顺序贪心地选择，如果能选就直接选上。（一次贪心可以使用线段树优化，$O(n \log n)$）显然这个贪心是错误的，所以每次退火随机交换两个顺序，卡个时间一直做退火。

CF 上面可以过。

### code

```cpp
// sa yyds!
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace plastic {
	constexpr int N=85;
	int n,a[N],c[N],m;
	ll ans;
	struct edge {
		int l,r,w;
	};
	vector<edge> vec;
	int la[N];
	bool del[N];
	int s;

	constexpr double time_limit=0.95,T=10,delta=0.99,eps=1e-15;
	mt19937 rd(random_device{}());
	ll mx;
	struct seg {
		int tr[N<<2],tag[N<<2];
		void clear() { memset(tr,0,sizeof(tr)), memset(tag,0,sizeof(tag)); }
		void maketag(int u,int t) {
			tr[u]+=t,tag[u]+=t;
		}
		void pushup(int u) { tr[u]=max(tr[u<<1],tr[u<<1|1]); }
		void pushdown(int u) { 
			if(tag[u]) maketag(u<<1,tag[u]),maketag(u<<1|1,tag[u]), tag[u]=0;
		}
		void insert(int u,int l,int r,int L,int R) {
			if(l>=L&&r<=R) return maketag(u,1), void(0);
			int mid=(l+r)>>1;
			pushdown(u);
			if(L<=mid) insert(u<<1,l,mid,L,R);
			if(mid+1<=R) insert(u<<1|1,mid+1,r,L,R);
			pushup(u);
		}
		int query(int u,int l,int r,int L,int R) {
			if(l>=L&&r<=R) return tr[u];
			int mid=(l+r)>>1;
			pushdown(u);
			int s=0;
			if(L<=mid) s=query(u<<1,l,mid,L,R);
			if(mid+1<=R) s=max(s,query(u<<1|1,mid+1,r,L,R));
			pushup(u);
			return s;
		}
	}Tr;
	ll calc() {
		ll sum=0;
		Tr.clear();
		for(auto u : vec) {
			if(u.l+1<=u.r-1) {
				if(Tr.query(1,1,n,u.l+1,u.r-1)<=m-2) sum+=u.w, Tr.insert(1,1,n,u.l+1,u.r-1);
			} else sum+=u.w;
		}
		return sum;
	}
	void sa() {
		double t=T;
		while(t>eps) {
			int x=rd()%s,y=rd()%s;
			swap(vec[x],vec[y]);
			ll now=calc();
			if(now > mx) mx=now;
			else if(1.0*(mx-now)*T>rand()/RAND_MAX) swap(vec[x],vec[y]);
			t*=delta;
		}
	}

	void main() {
		clock_t st=clock();
		srand(time(0));
		sf("%d%d",&n,&m);
		rep(i,1,n) sf("%d",&a[i]);
		rep(i,1,n) sf("%d",&c[i]);
		rep(i,1,n) {
			ans+=c[a[i]];
			if(la[a[i]]) vec.push_back({la[a[i]],i,c[a[i]]});
			la[a[i]]=i;
		}
		s=vec.size();
		while(clock()-st<time_limit*CLOCKS_PER_SEC) sa();
		pf("%lld\n",ans-mx);
	}
}
int main() {
	plastic :: main();
}
```

## 网络流

来自 [https://www.luogu.com.cn/discuss/995933](https://www.luogu.com.cn/discuss/995933) 提供的做法。

建 $n$ 个点，$i$ 向 $i+1$ 连容量为 $m-1$，费用为 $0$ 的边，代表你不选择区间的时候没有费用。每个区间 $[l,r,v]$ 从 $l$ 往 $r$ 连一条容量为 $1$，费用为 $v$ 的边，代表使用一个容量可以获得 $v$ 的费用。然后跑一个最大费用最大流，其实流量一定是 $m-1$。我们可爱的 SPFA 是可以跑负权图的，把边权取负然后跑最小费用最大流就好了。时间复杂度是 $O(nmf)$ 即 $O(n^2m)$ 的。

### code

注意对于上一个书和这一个书的情况会出现负权自环边，这种边判掉，直接必选就可以了。

唉，过了，跑的飞快。

好写的。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace plastic {
	constexpr int N=85;
	int n,a[N],c[N],m;
	struct edge {
		int to,f,ne,c;
	}e[N<<8];
    int cnt=1,head[N];
    void addedge(int u,int v,int f,int w) {
        e[++cnt]={v,f,head[u],w}, head[u]=cnt;
        e[++cnt]={u,0,head[v],-w}, head[v]=cnt;
    }
	int la[N];
    ll cost;

    constexpr ll inf=0x3f3f3f3f3f3f3f3f;
    ll dis[N];
    int cur[N];
    bool vi[N];
    bool spfa() {
        queue<int> q;
        memset(dis,0x3f,sizeof(dis));
        memcpy(cur,head,sizeof(cur));
        vi[1]=1;
        q.push(1);
        dis[1]=0;
        while(!q.empty()) {
            int u=q.front();
            q.pop();
            vi[u]=0;
            for(int i=head[u];i;i=e[i].ne) {
                int v=e[i].to,c=e[i].c;
                if(e[i].f && dis[u]+c<dis[v]) {
                    dis[v]=dis[u]+c;
                    if(!vi[v]) vi[v]=1, q.push(v);
                }
            }
        }
        return dis[n]!=inf;
    }
    int dinic(int u,int flow) {
        if(u==n) return flow;
        vi[u]=1;
        int sum=0;
        for(int &i=cur[u];i&&flow;i=e[i].ne) {
            int v=e[i].to,c=e[i].c,f=e[i].f;
            if(!vi[v] && f && dis[u]+c==dis[v]) {
                int x=dinic(v,min(flow,f));
                if(x) flow-=x, sum+=x, e[i].f-=x, e[i^1].f+=x, cost+=c*x;
                else dis[v]=-1;
            }
        }
        vi[u]=0;
        return sum;
    }
    void mcmf() {
        while(spfa()) dinic(1,m-1);
    }

	void main() {
		sf("%d%d",&n,&m);
		rep(i,1,n) sf("%d",&a[i]);
		rep(i,1,n) sf("%d",&c[i]);
        rep(i,1,n-1) addedge(i,i+1,m-1,0);
		rep(i,1,n) {
			cost+=c[a[i]];
			if(la[a[i]]) {
                if(la[a[i]]==i-1) cost-=c[a[i]]; 
                else addedge(la[a[i]],i-1,1,-c[a[i]]);
            }
			la[a[i]]=i;
		}
        mcmf();
        pf("%lld\n",cost);
	}
}
int main() {
	plastic :: main();
}
```

---

## 作者：喵仔牛奶 (赞：0)

非常神仙的思路。

# Solution

把丢弃书，看成找一个图书馆，以 $c_x$ 的代价存放书，下一次用这本书时取回。

也就是说，每种书只有一本，在第一次用时流入，最后一次用完时流出。

我们不区分书，把一种书看作一个流量，因为我们可以得知当前要用的书、根据图书馆里的流量得知寄存的书，剩下在书架上的书是可以确定的。

一个注意点：$i$ 时取回书或从源点收到书要流到 $i-1$，因为这样才能受到容量不超过 $k$ 的限制。

复杂度 $\mathcal{O}(n^3)$。

# Code

```cpp
int n, k, rs, s, t, a[N], c[N], hd[N];
int main() {
	cin >> n >> k, s = n + 1, t = s + 1;
	REP(i, 1, n) cin >> a[i];
	REP(i, 1, n) cin >> c[i];
	REP(i, 1, n) {
		if (!hd[a[i]]) flow.add(s, max(i - 1, 1), 1, 0), rs += c[a[i]];
		else flow.add(hd[a[i]], i - 1, 1, c[a[i]]);
		if (i > 1) flow.add(i - 1, i, k, 0);
		hd[a[i]] = i;
	}
	REP(i, 1, n)
		if (hd[a[i]] == i) flow.add(i, t, 1, 0);
	cout << rs + flow.solve(s, t).se << '\n';
	return 0;
}
```

---

## 作者：int_R (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF802C)

第一道自己独立切掉的黑题，还是应该记录一下。

题目很好理解，相比同场比赛的前两道题（easy,medium），这道题最大的区别是每本书的**价格并不相同**，因此不是很好考虑贪心。~~因为看起来有点奇怪，~~ 所以想到了网络流（**最小费用最大流**）。

首先我们用网络流的常见套路拆出 $n$ 天，对于每天有 $n+1$ 个点，通过前 $1\sim n$ 个点的流量分别表示每种书在第 $i$ 天有几本，由于书架并不一定要装满，所以我们用通过第 $n+1$ 个点的流量表示书架**剩余的容量**。这样我们只需要保证通过每天的 $n+1$ 个点的**流量和**为 $k$ 就可以保证任何时候书架中的书都不超过 $k$ 本。

我们用 $(i,j)$ 表示第 $i$ 天的第 $j$ 个点，我们从源点向 $(0,n+1)$ 连一条容量为 $k$，费用为 $0$ 的边，这样我们就可以保证每天的流量和为 $k$。

然后我们思考如何表示在某天开始时买入某种书，某种书某天结束时是扔掉还是保留。

对于 $\forall i\in[1,n],j\in[1,n+1]$，从 $(i-1,n+1)$ 向 $(i+1,j)$ 连一条容量为 $INF$ ，费用为 $a_j$ 的边，表示在第 $i$ 天一开始的时候买入了若干这种书。

对于 $\forall i\in[1,n],j\in[1,n]$，从 $(i,j)$ 向 $(i,n+1)$ 连一条容量为 $INF$，费用为 $0$ 的边，表示这些书选择丢弃。

对于 $\forall i\in[1,n-1],j\in[1,n]$，从 $(i,j)$ 向 $(i+1,j)$ 连一条容量为 $INF$ ，费用为 $0$ 的边，表示将这些书选择保留到下一天；

接下来我们才要处理真正的问题，就是那 $n$ 个请求，如何限制第 $i$ 天时书架里有第 $c_i$ 本书，我们可以通过**最大流**来限制。

对于 $\forall i\in[1,n]$，从 $(i,c_i)$ 向汇点连一条容量为 $1$，费用为 $0$ 的边。这样我们可以保证每天都可以满足请求。

但是这时迎来了一个新的问题，第 $c_i$ 本书相当于被丢弃了，并没有被置回，这时下一天的流量和就变成了 $k-1$。

所以对于 $\forall i\in[1,n]$，从源点向 $(i,n+1)$ 容量为 $1$，费用为 $0$ 的边，来保证每一天除去从源点流向第 $n+1$ 个点和从 $c_i$ 流出到汇点的流之外，流量和是 $k$。

同时对于 $\forall i\in[1,n-1]$，从 $(i,n+1)$ 向 $(i+1,c_i)$ 连一条容量为 $1$，费用为 $0$ 的边，表示如果并没有选择丢弃，我们还可以用 $0$ 元重新让它置回书架。为什么这里不能直接从源点向 $(i+1,c_i)$ 连边，因为如果那样的话，这本书就不能选择**丢弃**了。

最后在这个网络上跑最小费用最大流的费用和就是完成 $n$ 个请求的最少价钱。

其实上述一些范围**不需要**取的这么精确，多一条边或许无所谓，但是为了严谨还是都写出来了。

```cpp
int main()
{
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>n>>k;s=n*(n+1)+1,t=s+1;
	for(register int i=1;i<=n;++i) cin>>C[i];
	for(register int i=1;i<=n;++i) cin>>a[i];
	add(s,0,k,0),add(0,s,0,0);//s to (0,n+1) 
	for(register int i=1;i<=n;++i)
	{
        //(i,c[i]) to t
		add((i-1)*(n+1)+C[i],t,1,0);
		add(t,(i-1)*(n+1)+C[i],0,0);
        //s to (i,n+1)
		add(s,i*(n+1),1,0);
        add(i*(n+1),s,0,0);
        for(register int j=1;j<=n+1;++j)
        {
            //(i-1,n+1) to (i,j)
			add((i-1)*(n+1),(i-1)*(n+1)+j,INF,a[j]);
			add((i-1)*(n+1)+j,(i-1)*(n+1),0,-a[j]);
        }
        for(register int j=1;j<=n;++j)
        {
            //(i,j) to (i,n+1)
			add((i-1)*(n+1)+j,i*(n+1),INF,0);
			add(i*(n+1),(i-1)*(n+1)+j,0,0);
        }
        if(i==n) break;
        //(i,n+1) to (i+1,c[i])
		add(i*(n+1),i*(n+1)+C[i],1,0);
		add(i*(n+1)+C[i],i*(n+1),0,0);
        for(register int j=1;j<=n;++j)
		{
            //(i,j) to (i+1,j)
			add((i-1)*(n+1)+j,i*(n+1)+j,INF,0);
			add(i*(n+1)+j,(i-1)*(n+1)+j,0,0);
		}
	}
	while(SPFA()) cost+=dis[t]*dfs(s,INF);
	cout<<cost<<'\n';return 0;
}
```

---

## 作者：_Sein (赞：0)

[题目链接](https://codeforces.com/contest/802/problem/C)

在 CF 逛代码区的时发现了不同的建图方法，写一下吧。

首先我们买一本书丢一本书。

如果我们要选择两个同色相邻的书(天) $l,r$，如果它们不相邻，意味着我们要覆盖 $[l+1,r-1]$ 区间一次，意味着这些天书架要多承担一本书(本来每天就要承担一本)。

于是转化成 [最长k可重区间集问题](https://www.luogu.com.cn/problem/P3358)  , 不一样是，如果我们采用 “点” 的流量会有一点问题，也就是我们需要把闭区间变成开区间，这时候就会有问题。 举个最简单的例子:

$[l,r-1],[r,z]$  区间无交，转化为开区间有交，对应的图就会出现相应的问题，会判断这两个区间有交。

那不妨换另一种方法建图，以初始边，即 $i\rightarrow i+1$ 的初始流量的残余容量来作为第 $i$ 天还剩下多少空位。这种建图对于处理闭区间可以兼容上述情况。

于是我们得到一种较为简单的建图方法，即可通过此题。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
 
using namespace std;
 
const int N = 10005;
 
struct edge { int y, c, w, next; } a[N << 1]; int len, last[N];
 
void ins(int x, int y, int c, int w) { 
	a[++len] = (edge) { y, c, w, last[x] }; last[x] = len;
	a[++len] = (edge) { x, 0, -w, last[y] }; last[y] = len;
}
 
int q[N << 2], d[N], f[N], S, T, prv[N], ans, sta[N], top; bool v[N];
 
bool spfa() {
	memset(d, 0xcf, sizeof d); memset(f, 0, sizeof f);
	d[S] = 0; f[S] = 0x3f3f3f3f; int l = 1, r = 0; v[q[++r] = S] = 1;
	for (int x = q[l]; l <= r; x = q[++l]) {
		v[x] = 0; for (int k = last[x], y; k; k = a[k].next) {
			if (d[y = a[k].y] < d[x] + a[k].w && a[k].c) {
				d[y] = d[x] + a[k].w; f[y] = min(f[x], a[k].c);
				if (!v[y]) v[q[++r] = y] = 1; prv[y] = k;
			}
		}
	}
	return f[T] > 0;			
}	
 
void upd() {
	ans -= f[T] * d[T]; int k = prv[T];
	while (k) {
		a[k].c -= f[T]; 
		a[k ^ 1].c += f[T];
		k = prv[a[k ^ 1].y];
	}
}
 
int A[N], C[N], lst[N];
 
int main() {
	len = 1; memset(last, 0, sizeof last); memset(lst, 0, sizeof lst);
	int n, m; scanf("%d%d", &n, &m); ans = 0;
	for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", &C[i]); 
	for (int i = 1; i <= n; ++i) ans += C[A[i]];
	
	S = 0; T = n + 1; --m;
	for (int i = 0; i < T; ++i) ins(i, i + 1, m, 0);
	for (int i = 1; i <= n; ++i) {
		if (!lst[A[i]]) lst[A[i]] = i;
		else {
			if (lst[A[i]] == i - 1) ans -= C[A[i]]; 
			else ins(lst[A[i]] + 1, i, 1, C[A[i]]);
			lst[A[i]] = i;
		}
	}
	
	while (spfa()) upd();
	printf("%d\n", ans);
	return 0;
}
```





---

