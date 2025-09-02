# Tourism

## 题目描述

Alex 决定进行一次全国旅游。

为简化问题，假设该国家有 $n$ 个城市和 $m$ 条双向道路连接这些城市。Alex 住在城市 $s$，最初位于该城市。为了比较不同的城市，Alex 给每个城市分配了一个分数 $w_i$，分数越高表示该城市对 Alex 越有吸引力。

Alex 认为，只有在旅行过程中不连续重复走同一条道路，他的旅行才会有趣。也就是说，如果 Alex 从城市 $u$ 来到城市 $v$，那么他可以选择下一个通过道路与 $v$ 相连的任意城市，但不能回到城市 $u$。

你的任务是帮助 Alex 规划他的旅行路线，使他所访问过的所有城市的总分数最大。注意，每个城市的分数最多只能计入一次，即使 Alex 在旅行中多次到达该城市。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 7
2 2 8 6 9
1 2
1 3
2 4
3 2
4 5
2 5
1 5
2
```

### 输出

```
27```

## 样例 #2

### 输入

```
10 12
1 7 1 9 3 3 6 30 1 10
1 2
1 3
3 5
5 7
2 3
5 4
6 9
4 6
3 7
6 8
9 4
9 10
6
```

### 输出

```
61```

# 题解

## 作者：panyf (赞：10)

缩点、拓扑排序都不需要，dfs 一遍就行了。

设 $f_i$ 表示走到 $i$ 点，并且可以往回走，最大的权值。

$g_i$ 表示走到 $i$ 点，不能往回走，最大的权值。

设当前 dfs 到点 $x$，$j$ 与 $x$ 直接相连。

用一个 bool 变量 $z_x$ 表示 $x$ 的 dfs 树子树内是否存在点在环上。

若 $j$ 已经被访问过，且 $j$ 不为 $x$ 的父亲，则 $z_x=1$ 。

若 $j$ 未被访问过，且 $z_j=1$，则 $z_x=1$。

若 $j$ 未被访问过，可以用 $j$ 的 dp 值更新 $x$ 的 dp 值，转移方程如下：

$g_x=w_x+\max(g_j-f_j)+\sum f_j$。（先走所有的环，再走一条链）

当 $z_x=1$ 时，$f_x=w_x+\sum f_j$。（走完所有的环之后回到父亲结点）

答案即为 $g_s$。

代码很短。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+3,M=4e5+3;
int he[N],to[M],ne[M];
ll w[N],f[N],g[N];
bool b[N];
void dfs(int x,int y){
	int i=he[x],j;
	ll o=0,u=0;
	bool z=0;
	for(b[x]=1;i;i=ne[i])if(i!=y){
		j=to[i];
		if(b[j])z=1;
		else{
			dfs(j,i^1);
			if(f[j]>=0)o+=f[j],z=1,u=max(u,g[j]-f[j]);
			else u=max(u,g[j]);
		}
	}
	f[x]=z?o+w[x]:-1,g[x]=o+u+w[x];
}
int main(){
	int n,m,i,j,t=1;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%lld",w+i);
	while(m--){
		scanf("%d%d",&i,&j);
		ne[++t]=he[i],to[t]=j,he[i]=t;
		ne[++t]=he[j],to[t]=i,he[j]=t;
	}
	scanf("%d",&i),dfs(i,0),printf("%lld\n",g[i]);
	return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1220E)

$\text{vp}$ 赛题，神 [$\text{zltqwq}$](https://www.luogu.com.cn/user/275273) 写了一个令人瞠目结舌的边双缩点 $\text{dp}$，但是似乎被我拓扑水过去了...

## 题目分析

考虑到一个环可以随便走，然后看起点在不在上面。如果不在上面，那么起点连接到其他环的点不能遍历，否则可以。

然后考虑剩下的路径，求最优所以选权值最大的。跑一遍拓扑，然后考虑拓扑序上 $\text{dp}$。

令 $dp_i$ 表示 $i$ 点跑到最后权值最大值，则有：

$$dp_v=\max(dp_v,dp_u+a_u)$$

然后最优的路径显然为所有 $dp_i$ 中的最大值，找出来后加上没有被拓扑的点权和即为答案。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=2e5+5;
int n,m;
int sum,ans;
int a[maxn],dp[maxn];
int cnt_edge,head[maxn],in[maxn];
struct edge{
	int to,nxt;
}e[maxn<<1];
void add(int u,int v){
	e[++cnt_edge].nxt=head[u];
	e[cnt_edge].to=v;
	head[u]=cnt_edge;
}
void topsort(int x){
	queue<int> q;
	for(register int i=1;i<=n;++i){
		if(in[i]!=1||i==x) continue;
		q.push(i);
	}
	while(!q.empty()){
		int u=q.front();q.pop();in[u]=0;
		for(register int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(in[v]==0) continue;
			dp[v]=max(dp[v],dp[u]+a[u]);
			if(v==x) continue;
			in[v]--;
			if(in[v]==1) q.push(v);
		}
	}
}
inline void init(){
	n=read();m=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	if(n==1) cout<<a[1],exit(0);
	for(register int i=1;i<=m;++i){
		int u=read(),v=read();
		add(u,v);add(v,u);
		in[u]++;in[v]++;
	}
	topsort(read());
}
signed main(){
	init();
	for(register int i=1;i<=n;++i){
		if(in[i]==0) continue;
		sum+=a[i];ans=max(ans,dp[i]);
	}
	ans+=sum;
	printf("%lld",ans);
}
```

---

## 作者：_edge_ (赞：5)

比较好的题目。

首先看到题目，就是说如果有一个环存在，那么肯定是能走的，而且次数没有什么限制，唯一需要区别的就是走到一个死胡同里面去。

我们需要的就是去寻找这样一个最优秀的死胡同，这样我们的策略就是把其他的点都走一遍，然后直接撞进死胡同里面，可以保证这是最优的，因为走其他死胡同没有它优秀。

问题就转化成了，给定一张图，然后怎么求最长的死胡同，以及怎么判断一个点是否不在死胡同里面。

死胡同所长的样子应该是一个端点延伸上去的一条链。

因此我们先把入度为 $1$ 的点扔进去，然后再把其他入度为 $1$ 的扔进去，如果出现一个点的度不为 $1$，则它一定是有一个另外的环包含的，因为题目中已经保证连通。

所以所要寻找的即为一个端点和一个一个点拼出来的最长链，可以拓扑排序去寻找。

同时这里注意不能来回拓扑排序，所以在一个点被更新之后就标记掉它即可。

注意，这里的起点是不能作为死胡同的一部分，如果作为一部分的话就走不了了。

```cpp
#include <iostream>
#include <cstdio>
#include <queue> 
#define int long long 
using namespace std;
const int INF=2e5+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int n,m,tot,head[INF],in[INF],a[INF],vis[INF],F[INF],f[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
queue <int> q;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;tot=1;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=m;i++) {
		int x=0,y=0;cin>>x>>y;
		add_edge(x,y);add_edge(y,x);
		in[y]++;in[x]++;
	}
	if (n==1) {
		cout<<a[1]<<"\n";
		return 0;
	}
	int s=0;
	cin>>s;
	for (int i=1;i<=n;i++) {
		if (i!=s && in[i]==1) {
			q.push(i);f[i]=a[i];
		}
	}
	// 相当于你要求一条比较长的链 
	while (q.size()) {
		int x=q.front();q.pop();in[x]=0;
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_;
			if (v==s) continue;
			if (!in[v]) continue;
			f[v]=max(f[v],f[x]+a[v]);
			if (--in[v]==1) q.push(v);
		}
	}
	int res=0,sum=0;
	for (int i=1;i<=n;i++) {
		if (in[i]>0) res+=a[i];
		else sum=max(sum,f[i]);
//		cout<<in[i]<<" "<<f[i]<<" ???\n";
	}
	cout<<res+sum<<"\n";
	return 0;
}
```


---

## 作者：zsyyyy (赞：2)

## CF1220E 2200

### 题目描述

有 $n$ 个点， $m$ 条边的简单无向图。每个点有一个权值 $w_i$。一个人从 $s$ 出发，可以走一条不走回头路的路径。（也就是不能经过一条边立刻反着走，但是允许重复经过边）。求最大的权值和。

$ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le m \le 2 \cdot 10^5 $



### 思路

显然可以把图中间很多连起来的环看做是一个点（如果走到了这个点那么一定会也一定能把这个点代表的点都走一遍），然后从这个点连出去了一些树。

1. 如果 $s$ 在中间的这个点上，那么最优的一定是从这个点走到一棵树上，然后一直走到一个叶子结点不回头。

2. 如果 $s$ 不在中间的这个点上，那么最优的一定是从 $s$ 走到中间的那个点上，然后走到另一棵树上不回头 或者 再走回这棵树上不回头（如果选择这种情况，注意不要重复计算从 $s$ 走到中间的那个点上的这条路径）。

3. 注意特判一下一个环都没有的情况。



### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
int n,m,val[MAXN],cnt[MAXN],u,v,ans,s,maxa,flags,tmp,fa[MAXN];
bool book[MAXN],flag,vis[MAXN],tflag,pa[MAXN];
vector<int> a[MAXN],b[MAXN];
queue<int> q;
int dfs1(int x,int f,int tt)
{
	if(x==s)  flags=v;
	if(tt&&x==s)  return val[x];
	int maxx=val[x];
	for(int i=0;i<a[x].size();i++)
	{
		if(a[x][i]==f||!book[a[x][i]])  continue;
		fa[a[x][i]]=x;
		maxx=max(maxx,dfs1(a[x][i],x,tt)+val[x]);
	}
	return maxx;
}
void dfs2(int x)
{
	pa[x]=1;
	if(x==flags)  return;
	dfs2(fa[x]);
}
int dfs3(int x,int f)
{
	int maxx=0;
	if(!pa[x])  maxx=val[x];
	for(int i=0;i<a[x].size();i++)
	{
		if(a[x][i]==f||!book[a[x][i]])  continue;
		fa[a[x][i]]=x;
		if(!pa[x])  maxx=max(maxx,dfs3(a[x][i],x)+val[x]);
		else  maxx=max(maxx,dfs3(a[x][i],x));
	}
	return maxx;
}
int dfs4(int x,int f)
{
	if(pa[x])  return 0;
	int maxx=val[x];
	for(int i=0;i<a[x].size();i++)
	{
		if(a[x][i]==f||!book[a[x][i]])  continue;
		fa[a[x][i]]=x;
		maxx=max(maxx,dfs4(a[x][i],x)+val[x]);
	}
	return maxx;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)  scanf("%lld",&val[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&u,&v);
		a[u].push_back(v);
		a[v].push_back(u);
		cnt[u]++;
		cnt[v]++;
	}
	scanf("%lld",&s);
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]==1)  q.push(i);
	}
	while(q.size())
	{
		v=q.front();
		q.pop();
		if(book[v])  continue;
		book[v]=1;
		flag=0;
		for(int i=0;i<a[v].size();i++)
		{
			cnt[a[v][i]]--;
			if(cnt[a[v][i]]==1)
			{
				flag=1;
				q.push(a[v][i]);
			}
		}
		if(!flag)
		{
			tmp=dfs1(v,0,0);
			if(flags!=v)  maxa=max(maxa,tmp);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!book[i])
		{
			tflag=1;
			ans+=val[i];
		}
	}
	dfs2(s);
	int tmps=s;
	int sum=val[s];
	while(tmps!=flags)
	{
		tmps=fa[tmps];
		sum+=val[tmps];
	}
	if(!tflag)
	{
		int tmpp=dfs4(flags,0);
		ans=max(sum+tmpp,dfs1(s,0,0));
		printf("%lld\n",ans);
		return 0;
	}
	if(book[s])  ans+=sum+max(maxa,dfs3(flags,0));
	else  ans+=maxa;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：jasonleft (赞：2)

# 缩点 + 树DP

## 题意: 
- 有一个$n(n\le 2\times 10^5)$点$m(m\le 2\times 10^5)$ 边的无重边无自环的无向图，每个点有个点权。从 1 出发，不能连续经过同一条边，问路径上点权和的最大值是多少。(抄楼上)

### 数据范围: rt

### **Tutorial:**
 如果遇到了环, 我们一定可以把它算到贡献里面(走一圈再出来), 所以可以考虑缩点....
 缩点以后得到若干树, 我们只关心包含起点的那颗, 然后就是愉快的树形dp了
 $f[cur]$代表走到cur子树还能回的贡献
 $g[cur]$代表走到cur子树回不来的贡献
目标:$g[s]$
先考虑$f$的转移, 如果子节点能回来:$f[cur]+=f[to]$
然后$g[cur] = max(g[to]) + f[cur]$走完所有可以返回的儿子再找个最大的不能返回的
...

你以为完了吗,

这样有一个问题, 如果$f[cur] < g[cur]$ - 结点cur是否要返回


于是再 :
$g[cur] = max(g[cur], f[cur] - f[to] + g[to]);$


```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
#define _rep(n, a, b) for (ll n = (a); n <= (b); ++n)
#define _rev(n, a, b) for (ll n = (a); n >= (b); --n)
#define _for(n, a, b) for (ll n = (a); n < (b); ++n)
#define _rof(n, a, b) for (ll n = (a); n > (b); --n)
#define oo 0x3f3f3f3f3f3f
#define ll long long
#define db double
#define eps 1e-8
#define bin(x) cout << bitset<10>(x) << endl;
#define what_is(x) cerr << #x << " is " << x << endl
#define met(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()
#define pii pair<ll, ll>
const ll mod = 1e9 + 7;
const ll maxn = 4e5 + 5;
struct node
{
	ll nxt, to;
} way[maxn];
ll cnt, head[maxn], dfn[maxn], tim, low[maxn], val[maxn], st[maxn], top, node_num, bel[maxn], w[maxn], sz[maxn];
void addedge(ll from, ll to)
{
	way[++cnt].to = to;
	way[cnt].nxt = head[from];
	head[from] = cnt;
}
ll n, m;
struct edge {
	ll from, to;
	edge(ll _from = 0, ll _to = 0):from(_from), to(_to){}
	bool operator <(const edge& a) {
		return from == a.from ? to < a.to : from < a.from;
	}
	bool operator ==(const edge& a) {
		return from == a.from && to == a.to;
	}
};
vector<ll> G[maxn];
vector<edge> tmp;
void tarjan(ll cur, ll fa)
{ 
	dfn[cur] = low[cur] = ++tim;
	st[++top] = cur;
	for (ll i = head[cur]; i; i = way[i].nxt)
	{
		ll to = way[i].to;
		if (to == fa)
			continue;
		if (!dfn[to])
		{
			tarjan(to, cur);
			low[cur] = min(low[cur], low[to]);
		}
		else if (!bel[to])
			low[cur] = min(low[cur], dfn[to]);
	}
	if (dfn[cur] != low[cur])return;
	node_num++;
	while (st[top] != cur) bel[st[top--]] = node_num;
	bel[st[top--]] = node_num;
}
void build() {
	_rep(i, 1, n) {
		val[bel[i]] += w[i];
		sz[bel[i]]++;
	}

	_rep(i, 1, n) {
		for (ll j = head[i]; j; j = way[j].nxt) {
			ll to = way[j].to;
			if (bel[i] == bel[to])continue;
			tmp.push_back(edge(bel[i], bel[to]));
		}
	}
	sort(all(tmp));
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	for (auto i : tmp) {
		G[i.from].push_back(i.to);
	}
}
ll f[maxn], g[maxn];
bool ret[maxn];
void dfs(ll cur, ll fa) {
	f[cur] = val[cur];
	if (sz[cur] > 1)ret[cur] = 1;
	ll mx = 0;
	for (auto to : G[cur]) {
		if (to == fa)continue;
		dfs(to, cur);
		if (ret[to])f[cur] += f[to], ret[cur] = 1;
		else mx = max(mx, g[to]);
	}
	g[cur] = f[cur] + mx;
	for (auto to : G[cur]) {
		if (to != fa && ret[to])
			g[cur] = max(g[cur], f[cur] - f[to] + g[to]);
	}
}
signed main()
{

	cin >> n >> m;
	_rep(i, 1, n)cin >> w[i];
	_rep(i, 1, m)
	{
		ll u, v;
		cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
	}
	ll s;
	cin >> s;
	_rep(i, 1, n) if (!dfn[i]) tarjan(i, 0);
	build();//缩点系列
	dfs(bel[s], 0);
	cout << g[bel[s]] << endl;

	
	
}

```

---

## 作者：Llf0703 (赞：2)

[更好的阅读体验](https://llf0703.com/p/cf-1220.html#etourism)

## 题意

有一个 $n(n\le 2\times 10^5)$ 点 $m(m\le 2\times 10^5)$ 边的无重边无自环的无向图，每个点有个点权。从 $1$ 出发，不能连续经过同一条边，问路径上点权和的最大值是多少。

## 题解

环上每一个点都可以遍历一遍，连接环之间的点也是；如果起点不在这些点上，那么这条边到环上的所有点也能被遍历，但起点到末梢的路径上则不能（到末梢再回来就会连续经过末端的边）。

剩下的与环相连的路径只能选择一条，可以拓扑排序DP，用 $f[i]$ 表示末梢到 $i$ 点权值和的最大值，所有环上的点中取 $f[i]$ 的最大值即是最优的路径。

答案即为所有没被拓扑的点的点权和 $+ \max(f[i])$ 。

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

inline ll read()
{
    char ch=getchar(); ll f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

const ll N=200005;
struct Edge {
    ll next,to;
} edge[N<<1];
queue <ll> q;
ll cnt,head[N],n,m,a,b,st,s[N],deg[N],f[N];

inline void add(ll u,ll v)
{
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}

signed main()
{
    n=read(); m=read();
    for (ll i=1;i<=n;i++) s[i]=read();
    for (ll i=1;i<=m;i++)
    {
        a=read(); b=read();
        add(a,b); add(b,a);
        deg[a]++; deg[b]++;
    }
    st=read();
    if (n==1) return !printf("%lld",s[1]);
    for (ll i=1;i<=n;i++)
    {
        if (i==st || deg[i]!=1) continue;
        q.emplace(i);
    }
    while (!q.empty()) //拓扑排序
    {
        ll x=q.front(); q.pop();
        deg[x]=0;
        for (ll i=head[x];i;i=edge[i].next)
        {
            ll y=edge[i].to;
            if (!deg[y]) continue;
            f[y]=max(f[y],f[x]+s[x]);
            if (y==st) continue; //遇到起点则不继续
            deg[y]--;
            if (deg[y]==1) q.emplace(y);
        }
    }
    ll ans=0,maxf=0;
    for (ll i=1;i<=n;i++)
    {
        if (!deg[i]) continue;
        ans+=s[i];
        maxf=max(maxf,f[i]);
    }
    return !printf("%lld",ans+maxf);
}
```

---

## 作者：Suuon_Kanderu (赞：1)

考虑处在同一个边双连通分量里的点，显然我们可以将他们都经过（任意两点间有两条路径）。所以缩点后变成一棵树，可以 dp。

设 $f_u$ 表示走第 u 个节点还能回头的最大答案，$g_u$ 为不再回头的最大答案。  
我们发现，只要子树中有一个大小大于等于 3 的边双连通分量，那么进入了这颗子树后就还能回来，否则无论如何也回不来了。因为要保证不走进死胡同，所以 $f_u=\sum f_v$，其中 $v$ 要能走回头路（子树中有一个大小大于等于 3 的边双连通分量）。

然后考虑 $g_u$。首先我们肯定先将所有回头路走完，在 $f_u$ 的基础上更新 $g_u$，然后我们选择一个 $v$，如果说 $v$ 有走回头路的能力，那 $g_u=\max(g_u,g_v-f_v+f_u)$，因为 $f_u$ 中已经将 $f_v$ 统计过，要减去。否则 $g_u=\max(g_u,f_u+g_v)$。

显然 $g_u$ 不劣于 $f_u$，答案取 $g$ 即可。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 100;
typedef long long ll;
int head[N] , nex[N] , edge[N] , cnt = 1;
void add(int x , int y) {
	nex[++cnt] = head[x];
	head[x] = cnt;
	edge[cnt] = y;
}
bool vis[N] , bian[N];
int low[N] , dfn[N] , now = 0;
ll sum[N] , scc[N] , ee;
void tarjan(int u , int fa) {
	low[u] = dfn[u] = ++now;
	for(int i = head[u]; i ; i = nex[i]) {
		int v = edge[i];
		if(v == fa)continue;
		if(!dfn[v]) {
			tarjan(v , u);
			low[u] = min(low[u] , low[v]);
			if(low[v] > dfn[u])bian[i] = bian[i ^ 1] = true;
		}else {
			low[u] = min(low[u] , dfn[v]);
		}
	}
}
map<pair<int , int> , bool>t;
int n , m , w[N] , siz[N];
void dfs(int u) {
	scc[u] = ee;siz[ee]++;
	sum[ee] += w[u];
	for(int i = head[u]; i ; i = nex[i]) {
		int v = edge[i];
		if(bian[i] || scc[v])continue;
		dfs(v);
	}
}
vector<int>a[N];
ll f[N] , g[N];
bool can[N];//走了这条路是否能回来 
int u[N] , v[N];
void dfs2(int fa , int u) {
	f[u] = sum[u];
	if(siz[u] >= 3)can[u] = true;
	
	ll maxx = 0;
	for(auto v : a[u]) {
		if(v == fa)continue;
		dfs2(u , v);
		if(can[v])f[u] += f[v] , can[u] = true , maxx = max(maxx , g[v] - f[v]);
		else maxx = max(maxx , g[v]);
	}
	g[u] = max(maxx + f[u] , f[u]);
//	cout << u << ' ' << can[u]<< ' ' << f[u] << ' ' << g[u]<< endl;
} 
int main() {
	scanf("%d%d" , &n , &m);
	for(int i = 1; i <= n; i++)
		scanf("%d" , &w[i]);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d" , &u[i] , &v[i]);
		add(u[i] , v[i]);add(v[i] , u[i]);
	}
	for(int i = 1; i <= n; i++) {
		if(!dfn[i])tarjan(i , 0);
	}
	for(int i = 1; i <= n; i++) {
		if(!scc[i]) {
			++ee;
			dfs(i);
		}
	}
	for(int i = 1; i <= m; i++) {
		if(scc[u[i]] != scc[v[i]] && t.find(make_pair(scc[u[i]] , scc[v[i]])) == t.end()) {
			t[make_pair(scc[u[i]] , scc[v[i]])] = true;
			t[make_pair(scc[v[i]] , scc[u[i]])] = true;
			a[scc[u[i]]].push_back(scc[v[i]]);
			a[scc[v[i]]].push_back(scc[u[i]]);
		}
	}
	int s;scanf("%d" , &s);
	dfs2(0 , scc[s]);
	cout << g[scc[s]]  << endl;
	return 0;
}
```


---

## 作者：KokiNiwa (赞：1)

[题目链接](http://codeforces.com/contest/1220/problem/E)

可能是个好题，但更多的，是个写起来费劲的题。

## 题目叙述

有一个 无重边无自环的无向图，每个点有个点权。从一个指定点出发，不能连续经过同一条边，问路径上点权和的最大值是多少。

## 题解

### Solution 1

开始我理解题的意思是一条边只能走一遍。如果这样理解，那么就可以缩点双，一个割边走进去就走不出来了，所以就是从起点走一条最长链。

但是按照正确的理解，应该是不能立刻重复走同一条边。那么走到一个点双（大小大于1的）那么就可以走回那一条割边。所以就树型```dp```，设$f_{i}$表示从$i$开始走不回来的最大价值，$g_i$表示从$i$开始走回来的最大价值，转移即可。

### Solution 2

考虑到最佳走法是从起点绕完所有的环回来然后再走一个最长链。所以考虑找出所有不是叶子节点的然后把所有在环上的权值加起来，再找距离叶子节点到环的最长链。整个过程可以通过拓扑排序实现。

## 知识点

+ 看这种不能重复走一条边类似的东西可以考虑缩边双（因为割边一去不复返

## 代码
注意：
+ 这里放置一个我并没有解决的问题，就是[这份提交记录](http://codeforces.com/contest/1220/submission/71074113)为啥过不了qwq。
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
template <const int maxNode, const int maxEdge> struct Graph {
	int head[maxNode], to[maxEdge], nxt[maxEdge], Elen;
	Graph() : Elen(0) { memset(head, -1, sizeof(head)); }
	void AddEdge(int from, int _to) {
		to[++Elen] = _to;
		nxt[Elen] = head[from];
		head[from] = Elen;
	}
};
template <const int maxNode> struct dsu {
	int fa[maxNode];
	void Init(int nbNode) {
		for (int node = 1; node <= nbNode; ++node) fa[node] = node;
	}
	int Get(int now) { return (fa[now] == now) ? now : (fa[now] = Get(fa[now])); }
	void Merge(int un, int vn) {
		un = Get(un), vn = Get(vn);
		if (un == vn) return ;
		fa[un] = vn;
	}
};
const int maxNode = 2e5 + 5, maxEdge = 2e5 + 5;
dsu<maxNode> set;
Graph<maxNode, maxEdge << 1> graph;
Graph<maxNode, maxNode << 1> tree;
int nbNode, nbEdge, startNode, dfstime, val[maxNode], dfn[maxNode], low[maxNode], size[maxNode];
ll go[maxNode], back[maxNode], sum[maxNode];
bool cut[maxEdge << 1], canBack[maxNode];
void Dfs(int now, int from) {
	low[now] = dfn[now] = ++dfstime;
	for (int pt = graph.head[now]; ~pt; pt = graph.nxt[pt]) {
		int to = graph.to[pt];
		if (to == from) continue ;
		
		if (dfn[to])
			low[now] = min(low[now], dfn[to]);
		else {
			Dfs(to, now);
			low[now] = min(low[now], low[to]);
		}
		if (low[to] > dfn[now]) cut[pt] = 1;
		else set.Merge(to, now);
	}
}
void Dp(int now, int from) {
	if (size[now] >= 2)
		canBack[now] = 1;
	for (int pt = tree.head[now]; ~pt; pt = tree.nxt[pt]) {
		int to = tree.to[pt];
		if (to != from) {
			Dp(to, now);
			canBack[now] |= canBack[to];
			back[now] += back[to];
		}
	}
	for (int pt = tree.head[now]; ~pt; pt = tree.nxt[pt]) {
		int to = tree.to[pt];
		if (to != from)
			go[now] = max(go[now], back[now] - back[to] + go[to]);
	}
	go[now] += sum[now];
	if (canBack[now])
		back[now] += sum[now];
}
int main() {
	scanf("%d%d", &nbNode, &nbEdge);
	for (int node = 1; node <= nbNode; ++node)
		scanf("%d", &val[node]);
	set.Init(nbNode);
	for (int edge = 1; edge <= nbEdge; ++edge) {
		int node1, node2;
		scanf("%d%d", &node1, &node2);
		graph.AddEdge(node1, node2);
		graph.AddEdge(node2, node1);
	}
	scanf("%d", &startNode);
	Dfs(1, 0);
	for (int node = 1; node <= nbNode; ++node) {
		sum[set.Get(node)] += val[node];
		size[set.Get(node)] += 1; 
		for (int pt = graph.head[node]; ~pt; pt = graph.nxt[pt]) {
			if (!cut[pt]) continue ;
			tree.AddEdge(set.Get(node), set.Get(graph.to[pt]));
			tree.AddEdge(set.Get(graph.to[pt]), set.Get(node));
		}
	}
	int root = set.Get(startNode);
	Dp(root, 0);
	printf("%lld\n", max(go[root], back[root]));
	return 0;
}
```

---

## 作者：ollo (赞：0)

## 题目大意

有一张 $n$ 个点 $m$ 条边的无向图 ($m, n\le 2\times 10^5$) ，从一个起点出发，不能连续经过同一条边，问最大的点权和是多少。

## 题解

环上每一个点都可以遍历一遍，连接环之间的点也是；如果起点不在这些点上，那么从起点到环上的所有点也能被遍历，但起点到其他连接环上则不能（如果去了回来必须连续经过同一条边）。

剩下的与环相连的路径只能选择一条点权总和最大的，考虑拓扑序上DP，用  $f[i]$ 表示末梢到 $i$ 点权值和的最大值，所有环上的点中取 $f[i]$ 的最大值即是最优的路径。至于拓扑序，跑一边拓扑排序即可。

答案即为起点到环经过的点+环上的点的点权和 + $\max(f[i])$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10;

struct S{
	int to, nxt;
}a[N];
int head[N], tot;

void add(int u, int v){
	a[++tot].nxt = head[u];
	a[tot].to = v;
	head[u] = tot;
}

int n, m, in[N];
int s[N], f[N];

void topo(){
	queue<int> q;
	int qd;
	cin >> qd;
	if(n == 1){
		cout << s[1];
		return ;
	}
	for(int i = 1; i <= n; i++){
		if(i == qd || in[i] != 1) continue;
		q.push(i);
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		in[x] = 0;
		for(int i = head[x]; i; i = a[i].nxt){
			int v = a[i].to;
			if(!in[v]) continue;
			f[v] = max(f[x] + s[x], f[v]);
			if(v == qd) continue;
			in[v]--;
			if(in[v] == 1){
				q.push(v);
			}
		}
	}
	int ans = 0, num = 0;
	for(int i = 1; i <= n; i++){
		if(!in[i]) continue;
		num += s[i];
		ans = max(ans, f[i]);
	}
	cout << ans + num;
}

signed main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> s[i];
	}
	for(int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
		in[u]++;
		in[v]++;
	}
	topo();
	return 0;
}
```

---

