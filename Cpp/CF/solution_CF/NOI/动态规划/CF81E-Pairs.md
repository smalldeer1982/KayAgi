# Pairs

## 题目描述

有 $n$ 个人，每个人都有自己最好的朋友，**但不保证 a 的最好朋友是 b 时，b 的最好朋友是 a**。

现在要把他们和自己最好的朋友两两分组，因为不一定全部人都能被分在一起，所以求在组数最多的情况下，男女组最多。

## 样例 #1

### 输入

```
5
5 2
3 2
5 1
2 1
4 2
```

### 输出

```
2 2
5 3
4 2
```

## 样例 #2

### 输入

```
6
5 2
3 2
5 1
2 1
4 2
3 1
```

### 输出

```
3 1
4 2
5 1
3 6
```

## 样例 #3

### 输入

```
8
2 2
3 2
5 1
3 1
6 1
5 1
8 2
7 1
```

### 输出

```
4 1
5 6
3 4
2 1
7 8
```

# 题解

## 作者：Saka_Noa (赞：7)

思路来源于 codeforces
#### 简要题意： 
给定 $n$ 个点 $n$ 条边的有向图，求最大匹配，在此基础上让异色匹配最大。  
#### 分析:     
通过观察， $n$ 个点 $n$ 条边，所以必定是基环树森林。且一个点只有一个出度，所以肯定是内向树。（简要证明：
因为出度为 $1$，而一条链上的点方向相同。所以我们只考虑环与环外点的连边。
假定不是内向树，环有必有上一点向外连出边，但是这个点已经在环上了，所以它的出度必定大于 $1$，与已知条件矛盾）于是我们可以通过内向树来找到环上的点，再在反图（即外向树）上跑树形 DP。  
令 $G(i,j) = \sum_{k\in Son_i, k\ne j} \max \left (f_{k,1} , f_{k,0} \right)$  
$$f_{i,0} = \sum_{j\in Son_i} \max \left (f_{j,1} , f_{j,0} \right)$$ 
$$f_{i , 1} =  \max \left( G(i,j) +f_{j,0} + val(i,j) \right) , j\in Son_i$$
因为这是一个环，假定 $u,v,w$ 是环上的三个点，我们可以通过断开 $(u,v)$ 这条边进行一次 DP，因为会漏掉 $(u,v)$ 这条边的答案，所以然后再断开 $(v,w)$ 这条边进行一次 DP。

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(i,a,b) for(int i = a;i <= b;i++)
#define pb push_back
struct node{int x , y;
    bool operator <(node b) {return x == b.x ? y < b.y : x < b.x;} 
    node operator +(node b) const {node ans; ans.x = x + b.x;ans.y = y + b.y;return ans;}
    node operator -(node b) const {node ans; ans.x = x - b.x;ans.y = y - b.y;return ans;}
};
const int N = 1e5 + 5;
int n, in[N] , g[N] , rt , s[N] , v[N];
node f[N][2] , ans;
vector<int> c[N];
vector<node> p , q;
void calc(int u) {
    f[u][1] = f[u][0] = node{0,0}, g[u] = 0, v[u] = 1;
    for(auto P : c[u]) {
        if(P == rt) continue;
        calc(P);
        f[u][0] = f[u][0] + f[P][1];
        node t = f[P][0] - f[P][1] + node{1 ,s[u] ^ s[P]};
        if(f[u][1] < t) f[u][1] = t , g[u] = P;
    }
    f[u][1] = f[u][1] + f[u][0];
}
void get(int u , int i) {
    for(auto P : c[u])  { 
        if(P == rt) continue;
        if(!i || g[u] != P) get(P , 1); else p.pb(node{u,P}) , get(P , 0);
    }
}
void solve(int u) {
    for(;!v[u];u = in[u]) v[u] = 1; // 找环上的点
    node r = node{0,0};
    fo(i,1,2) {
        rt = u; // 断边
        calc(u);
        if(r < f[u][1]) r = f[u][1] , p.clear() , get(u,1);
        u = in[u]; // 换边
    }
    for(auto P : p) q.pb(P);
    ans = ans + r;
}
int main() {
    scanf("%d" , &n);
    fo(i,1,n) scanf("%d %d",in + i , s + i) , s[i]--,c[in[i]].pb(i);
    fo(i,1,n) if(!v[i]) solve(i);
    printf("%d %d\n" , ans.x , ans.y);
    for(auto P:q) printf("%d %d\n" , P.x , P.y);
    return 0;
}
```


---

## 作者：绝顶我为峰 (赞：6)

喜欢线性题开 $10^5$ 是吧。那就别怪我 $O(n\sqrt n)$ 过去了。

题意是求基环树森林最大匹配，同时最大化异色匹配数量。

匹配当然可以考虑一下网络流，如果是树的话就很简单，直接给树黑白染色建二分图就能求出最大匹配。求出最大异色匹配数量也是简单的，方法是把最大流换成费用流，匹配边如果是同色的边权是 $1$，否则边权是 $0$，然后跑最小费用最大流，最大异色匹配数量就是流量减去费用。

现在基环树怎么办？其实是类似的，我们直接找一棵生成树，然后枚举唯一的非树边是否选择，分别跑一遍最小费用最大流即可。

基环树森林直接对每个联通块做基环树的做法即可。

虽然是费用流，但是由于最短路只有 $0$ 和 $1$ 两种，直接跑的复杂度依然是 $O(n\sqrt n)$，刚好能卡着时限过。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
int n,m,s,t,tot=1,cnt,bin[100005],id[100005],node[100005],dep[100005],h[100005],cur[100005],ans,cost,ans1,ans2,col[100005],a[100005];
bool vis[100005];
vector<int> v[100005],g[100005];
pair<int,int> w[100005];
vector<pair<int,int> > res;
struct edge
{
    int nxt,to,weight,val;
}e[100005<<2];
inline int read()
{
    int x;
    cin>>x;
    return x;
}
inline int anc(int k)
{
    if(!bin[k])
        return k;
    return bin[k]=anc(bin[k]);
}
inline void link(int x,int y)
{
    pair<int,int> val={x,y};
    x=anc(x);
    y=anc(y);
    if(x^y)
    {
        g[val.first].emplace_back(val.second);
        g[val.second].emplace_back(val.first);
        bin[y]=x;
        if(w[y].first)
            w[x]=w[y];
    }
    else
        w[x]=val;
}
inline void add(int x,int y,int w,int val)
{
    e[++tot]={h[x],y,w,val};
    h[x]=tot;
}
inline void clear()
{
    for(int i=0;i<=t;++i)
        h[i]=dep[i]=cur[i]=vis[i]=0;
    tot=1;
    s=t=cnt=ans=cost=0;
}
inline bool SPFA()
{
    for(int i=0;i<=t;++i)
    {
        dep[i]=0x3f3f3f3f;
        cur[i]=h[i];
        vis[i]=0;
    }
    queue<int> q;
    q.emplace(s);
    dep[s]=0;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        vis[k]=0;
        for(int i=h[k];i;i=e[i].nxt)
            if(e[i].weight&&dep[e[i].to]>dep[k]+e[i].val)
            {
                dep[e[i].to]=dep[k]+e[i].val;
                if(!vis[e[i].to])
                {
                    vis[e[i].to]=1;
                    q.emplace(e[i].to);
                }
            }
    }
    return dep[t]^dep[0];
}
inline int dfs(int k,int f)
{
    if(k==t)
    {
        ans+=f;
        return f;
    }
    vis[k]=1;
    int r=0,used=0;
    for(int i=cur[k];i;i=e[i].nxt)
    {
        cur[k]=i;
        if((!vis[e[i].to]||e[i].to==t)&&e[i].weight&&dep[e[i].to]==dep[k]+e[i].val)
            if((r=dfs(e[i].to,min(e[i].weight,f-used))))
            {
                cost+=e[i].val*r;
                e[i].weight-=r;
                e[i^1].weight+=r;
                used+=r;
                if(f==used)
                    break;
            }
    }
    return used;
}
inline void dinic()
{
    while(SPFA())
    {
        vis[t]=1;
        while(vis[t])
        {
            for(int i=0;i<=t;++i)
                vis[i]=0;
            dfs(s,1<<30);
        }
    }
}
inline void solve(int root)
{
    clear();
    for(int i:v[root])
        node[id[i]=++cnt]=i;
    s=cnt+1;
    t=s+1;
    for(int i=1;i<=cnt;++i)
        if(col[node[i]])
        {
            add(s,i,1,0);
            add(i,s,0,0);
            for(int j:g[node[i]])
            {
                int val=a[node[i]]==a[j];
                add(i,id[j],1,val);
                add(id[j],i,0,-val);
            }
        }
        else
        {
            add(i,t,1,0);
            add(t,i,0,0);
        }
    dinic();
    vector<pair<int,int> > tmp;
    pair<int,int> w1={ans,ans-cost};
    for(int k=1;k<=cnt;++k)
        if(col[node[k]])
            for(int i=h[k];i;i=e[i].nxt)
                if(!e[i].weight&&e[i].to>=1&&e[i].to<=cnt)
                {
                    tmp.emplace_back(node[k],node[e[i].to]);
                    break;
                }
    clear();
    ans=1;
    cost=a[w[root].first]==a[w[root].second];
    for(int i:v[root])
        if(i!=w[root].first&&i!=w[root].second)
            node[id[i]=++cnt]=i;
    s=cnt+1;
    t=s+1;
    for(int i=1;i<=cnt;++i)
        if(col[node[i]])
        {
            add(s,i,1,0);
            add(i,s,0,0);
            for(int j:g[node[i]])
                if(j!=w[root].first&&j!=w[root].second)
                {
                    int val=a[node[i]]==a[j];
                    add(i,id[j],1,val);
                    add(id[j],i,0,-val);
                }
        }
        else
        {
            add(i,t,1,0);
            add(t,i,0,0);
        }
    dinic();
    pair<int,int> w2={ans,ans-cost};
    if(w1<w2)
    {
        tmp.clear();
        tmp.emplace_back(w[root]);
        for(int k=1;k<=cnt;++k)
        if(col[node[k]])
            for(int i=h[k];i;i=e[i].nxt)
                if(!e[i].weight&&e[i].to>=1&&e[i].to<=cnt)
                {
                    tmp.emplace_back(node[k],node[e[i].to]);
                    break;
                }
    }
    pair<int,int> maxn=max(w1,w2);
    ans1+=maxn.first;
    ans2+=maxn.second;
    for(auto i:tmp)
        res.emplace_back(i);
}
inline void predfs(int k,int f,int tag)
{
    col[k]=tag;
    for(int i:g[k])
    {
        if(i==f)
            continue;
        predfs(i,k,tag^1);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    n=read();
    for(int i=1;i<=n;++i)
    {
        int f=read();
        a[i]=read();
        link(i,f);
    }
    for(int i=1;i<=n;++i)
        v[anc(i)].emplace_back(i);
    for(int i=1;i<=n;++i)
        if(anc(i)==i)
        {
            predfs(i,0,0);
            solve(i);
        }
    cout<<ans1<<" "<<ans2<<'\n';
    for(auto i:res)
        cout<<i.first<<" "<<i.second<<'\n';
    cout.flush();
    return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：5)

[传送门](https://codeforces.ml/contest/81/problem/E)

发现自己的解法带个 $\log$，是最慢的555

化简题意：给定 $n$ 点 $n$ 边的无向图（不保证连通），求其最大匹配，在此基础上最大化两端点颜色不同的匹配边数，并输出一个解。

首先 $n$ 点 $n-1$ 边的话就是森林最大匹配，树形DP做法很容易想到：设 $f(x)$ 是以 $x$ 为根的子树的答案，$son(x)$ 是 $x$ 的儿子集合，$g(x)=\sum_{y\in son(x)}f(y)$，即 $x$ 子树不能使用 $x$ 的答案。那么 $f$ 的转移式为：

$$f(x)=\max\{g(x),\max\{g(x)-f(y)+1+g(y)\,\mid\,y\in son(x)\}\,\}$$

单独拿出来就是个 1500* 的 2C，然而它是一个奇怪比赛（大概等于Div1）的E，不可能这么简单。考虑到，$n$ 点 $n$ 边其实就是基环树森林+普通森林，也就是说我们需要将树上解法拓展到基环树上。

基环树和树的区别：有环。所以许多关于基环树的套路都是关于这个环的（要么删环上一边，要么把环挂着的树算出来变成环形问题）。考虑删掉环上一边 $(u,v)$，那么对于新的树 $t$，我们可以用树形DP求解。但是可能还存在最优答案都包括 $(u,v)$ 的情况，此时我们不能删去 $(u,v)$. 但是注意到，**题目求的是匹配**，也就是说如果选了 $(u,v)$，那么 $u$ 和其它点的连边都不会使用。又因为 $u$ 是环上一点，所以一定还存在另一条在环上的边 $(u,w)$，找到这两条边，可以保证，删去 $(u,v)$ 所得到的 $t1$ 和删去 $(u,w)$ 所得到的 $t2$ 两棵树中必有一颗树的答案是原基环树的答案。

所以大致解法是：找到一个连通块，找环（即找$u,v,w$），比较删 $(u,v)$ 和删 $(u,w)$ 的答案，确定删去的边，重新做 DP 记录方案。最后输出。

另外，本题中答案有两个属性：数量和不同颜色数量，建议使用 pair，内置比较符重载写起来比较方便，同时建议重载一下 pair 的加减法便于 DP 使用。

到这里你发现了这个做法是 $O(n)$ 的为什么我会说我的解法带个 $\log$ .（本质上这个做法的复杂度真的是线性没问题的）因为删边加边非常麻烦所以我用了 set 去维护可达性，写起来比较方便，代价就是变成了最慢解555.

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10,MAXM=2e5+10;
int n,u,v,color[MAXN],vis[MAXN],fa[MAXN],depth[MAXN];
int pre[MAXN];
pi f[MAXN],g[MAXN],ans;
set<int>e[MAXN];
vector<pi>sol;
pi operator+(const pi& p1,const pi& p2){return mp(p1.fr+p2.fr,p1.se+p2.se);}
pi operator-(const pi& p1,const pi& p2){return mp(p1.fr-p2.fr,p1.se-p2.se);}
struct Dsu{
	int fa[MAXN];
	pi info[MAXN];
	void Init(){
		rep(i,1,n)fa[i]=i;
	}
	int Find(int x){
		if(fa[x]==x)return x;
		return fa[x]=Find(fa[x]);
	}
	void Merge(int x,int y){
		if(!info[Find(y)].fr)info[Find(y)]=info[Find(x)];
		fa[Find(x)]=Find(y);
	}
}dsu;
void predfs(int u){
	vis[u]=1;
	depth[u]=depth[fa[u]]+1;
	for(sit it=e[u].begin();it!=e[u].end();it++){
		if(vis[*it])continue;
		fa[*it]=u;predfs(*it);
	}
}
void clr(int u,int fa){
	f[u]=g[u]=mp(0,0);pre[u]=0;
	for(sit it=e[u].begin();it!=e[u].end();it++){
		if(fa==*it)continue;
		clr(*it,u);
	}
}
void dfs(int u,int fa){
	for(sit it=e[u].begin();it!=e[u].end();it++){
		if(fa==*it)continue;
		dfs(*it,u);
		g[u]=g[u]+f[*it];
	}
	f[u]=g[u];
	for(sit it=e[u].begin();it!=e[u].end();it++){
		if(fa==*it)continue;
		if(g[u]-f[*it]+g[*it]+mp(1,color[u]!=color[*it]) > f[u]){
			pre[u]=*it;
			f[u]=g[u]-f[*it]+g[*it]+mp(1,color[u]!=color[*it]);
		}
	}
}
pi dp(int u){
	clr(u,u); //清空信息	
	dfs(u,u);
	return f[u];
}
void solve(int u,int fa){
	if(pre[u]){
		sol.pb(mp(u,pre[u]));
		for(sit it=e[pre[u]].begin();it!=e[pre[u]].end();it++){
			if(*it == pre[u] || *it==u)continue;
			solve(*it,pre[u]); 
		}
	}
	for(sit it=e[u].begin();it!=e[u].end();it++){
		if(*it==pre[u] || *it==fa)continue;
		solve(*it,u);
	}
}
int main(){
	cin>>n;
	dsu.Init();
	rep(u,1,n){
		cin>>v>>color[u];
		if(dsu.Find(u)!=dsu.Find(v)){
			dsu.Merge(u,v);
			e[u].is(v),e[v].is(u);
		}else{
			dsu.info[dsu.Find(u)]=mp(u,v); //(u,v)是环上一边 
		}
	}
	rep(i,1,n){
		if(vis[i])continue;
		//新的连通块
		vis[i]=1;predfs(i);
		pi p=dsu.info[dsu.Find(i)],ret=mp(0,0),tmp=mp(0,0);
		int u,v,w;
		if(depth[p.fr]>depth[p.se])u=p.fr,v=fa[p.fr],w=p.se;
		else u=p.se,v=fa[p.se],w=p.fr;
		//1.删(u,v)连(u,w)
		e[u].erase(v),e[v].erase(u);
		e[u].is(w),e[w].is(u);
		ret=dp(i);
		//2.删(u,w)连(u,v) 
		e[u].erase(w),e[w].erase(u);
		e[u].is(v),e[v].is(u);
		tmp=dp(i); 
		ans=ans+Max(ret,tmp);
		if(tmp<ret){
			e[u].erase(v),e[v].erase(u);
			e[u].is(w),e[w].is(u);
		}
		dp(i);
		solve(i,i);
	}
	printf("%d %d\n",ans.fr,ans.se);
	int sz=sol.size();
	rep(i,0,sz-1){
		printf("%d %d\n",sol[i].fr,sol[i].se);
	}
	return 0;
}
```


---

## 作者：WangBng (赞：4)

难度转 AT $\color{orange}{2683}$。

首先这个有向图的关系是假的，可以看作无向图。

然后会发现这是一个基环树森林，先考虑一棵树怎么做。

定义 $f_x$ 为 $x$ 这棵子树的最大匹配对数，$g_x$ 为最大男女组组数，$G_x$ 为一个集合，包含 $x$ 的所有儿子，$P_x=\sum\limits_{y\in G_x}f_y$，$Q_x=\sum\limits_{y\in G_x}g_y$，则：

枚举 $x$ 和谁配对，假设和 $y$ 配对，则：（下面用 `pair` 表示）

$\{f_x,g_x\}=\max(\{f_x,g_x\},\{P_y+P_x-f_y,Q_y+Q_x-g_y\})$

或者是不配对，则转移式为：

$\{f_x,g_x\}=\max(\{f_x,g_x\},\{P_x,Q_x\})$

然后枚举环上任意一点的匹配情况（是和两个旁边的环点匹配，还是和其子树内的点匹配？），断边形成树进行树形 dp 即可。

---

## 作者：CmsMartin (赞：3)

[$\mathcal{Link}$](http://www.cmsblog.top/archives/cf81epairs)

## 题目描述

给定一颗黑白内向基环树，你要对其进行匹配，让匹配数最多的同时最大化异色匹配。并且给出一种方案。

$1 \le n \le 10^5$。

## 思路

### 暴力

考虑流。对于一颗普通的树，进行黑白染色变成二分图，跑网络流即可得到最大匹配。如果是异色匹配费用流即可。对于这道题，不妨直接断开环上的任意一条边 $u \to v$，钦定这条边必须选择或者不选流两次即可。时间复杂度 $\mathcal{O}(n\sqrt n)$。理论可过，而且有人过了，但是卡常。

### 正解

考虑 dp。对于环上的一条路径 $u \to v \to w$。最多产生一个匹配。所以我们可以先断开 $u \to v$ dp 一次，再断开 $v \to w$ dp 一次。两次 dp 答案取 max 即可。这个 dp 是朴素的，设 $f_{u,0/1}$ 表示 $u$ 子树内，$u$ 是（$1$）否（$0$）可以进行匹配的答案。平凡的转移：
$$
f_{u,0} = \sum_{v \in \operatorname{son}(u)}f_{v,1}
$$
$$
f_{u,1} = \max\{f_{u,0},\max_{v \in \operatorname{son}(u)}\{(\sum_{k \in\operatorname{son}(v),k \neq v}f_{k,1}) + f_{v,0}+\texttt{是否异色}\}\}
$$
然后记一下转移去找匹配就行了。时间复杂度 $\mathcal{O}(n)$。



---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给出 $n$ 个点 $n$ 条边的无向图，保证每个点度数至少为 $1$，同时每个点有一个颜色（$1$ 或 $2$）。现在请你将他们两两分组，满足每组的两个点有边直接相连。在匹配组数最多的前提下，最大化组内颜色不同的组数。

## 题目分析

显然该图是一个基环树森林。

由匹配和最大化的条件，不难想到费用流，可是这不是一个二分图，无法直接建图。瓶颈在于奇环的出现。但是这题是基环树，每个联通块最多只有一个奇环。所以我们干脆对于每个联通块，直接枚举环上一个边选或不选，剩下的图就一定是个树，显然是个二分图，跑费用流即可。

建模十分简单，由于边的容量都为 $1$，使用 zkw 费用流会超时，而使用 Dinic 算法可以达到 $O(m\sqrt n )$。只要有较为优秀的代码常数即可卡过此题。

注意清空时不能 memset，否则复杂度会退化到 $O(n^2)$。使用栈记录每次处理到的点即可。

（这里借用了峰哥的费用流，%%%）。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e5+5,M=2e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e8+7,bas=131;
const ui base=13331;
using namespace std;
int m,n,cst,s,t,h[N],now[N],nxt[M],to[M],d[N],cnt=1,pre[N],c[M],w[M],dis[N],ans;
bool vis[N];
int stac[N],tp;
void add(int a,int b,int C,int cost){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=C,c[cnt]=cost;
	to[++cnt]=a,nxt[cnt]=h[b],h[b]=cnt,w[cnt]=0,c[cnt]=-cost;
}
int dep[N];
inline bool spfa(){
	rep(i,0,tp){
    	int x=stac[i];
        dep[x]=0x3f3f3f3f,now[x]=h[x],vis[x]=0;
    }
    dep[t]=0x3f3f3f3f,now[t]=h[t],vis[t]=0;
    dep[t+1]=dep[t];
    queue<int>q;
    q.push(s);
    dep[s]=0;
    while(!q.empty())
    {
        int k=q.front();
        q.pop();vis[k]=0;
        e(k)if(w[i]&&dep[y]>dep[k]+c[i]){
            dep[y]=dep[k]+c[i];
            if(!vis[y])vis[y]=1,q.push(y);
        }
    }
    return dep[t]^dep[t+1];
}
inline int dfs(int k,int f){
    if(k==t)return f;
	
    vis[k]=1;
    int r=0,used=0;
    for(int i=now[k];i;i=nxt[i])
    {
    	int y=to[i];
        now[k]=i;
        if((!vis[y]||y==t)&&w[i]&&dep[y]==dep[k]+c[i])if((r=dfs(y,min(w[i],f-used)))){
        	cst+=c[i]*r,w[i]-=r,w[i^1]+=r,used+=r;
            if(f==used)break;
        }
    }
    return used;
}
inline void dinic(){
    while(spfa()){
        vis[t]=1;
        while(vis[t]){
            rep(i,0,tp)vis[stac[i]]=0;
            vis[t]=0;
            ans+=dfs(s,1<<30);
        }
    }
}
struct node{
	int x,y;
}e[N];
int id[N],Id;
vector<Pi >p[N],out;
int col[N];
vector<int>P,Ed;
inline void Dfs(int x,int fr){
	P.pb(x);
	E(x){
		int v=y.first,d=y.second;
		if(!col[v])col[v]=3-col[x],Ed.pb(d),Dfs(v,d);
		else if(d^fr)Id=d;
	}
}
int ans1,ans2,tot;
vector<Pi >nw;
inline void solve(int xx){
	P.clear(),Ed.clear(),nw.clear();
	col[xx]=1;
	Dfs(xx,0);
	int a1,a2;
	ans=cst=0,cnt=1;
	for(auto x:P)stac[++tp]=x,col[x]==1?add(s,x,1,0):add(x,t,1,0);
	for(auto i:Ed){
		int Cs=id[e[i].x]==id[e[i].y];
		col[e[i].x]==1?add(e[i].x,e[i].y,1,Cs):add(e[i].y,e[i].x,1,Cs);
	}
	dinic();
	for(auto x:P)if(col[x]==1)e(x)if(y>0&&!w[i])nw.pb({x,y});
	a1=ans,a2=ans-cst;
	cnt=1;
	h[t]=0;rep(i,0,tp)h[stac[i]]=0;
	int A=e[Id].x,B=e[Id].y;
	ans=1,cst=id[A]==id[B];
	for(auto x:P)col[x]==1?add(s,x,1,0):add(x,t,1,0);
	for(auto i:Ed){
		if(e[i].x==A||e[i].y==A||e[i].x==B||e[i].y==B)continue;
		int Cs=id[e[i].x]==id[e[i].y];
		col[e[i].x]==1?add(e[i].x,e[i].y,1,Cs):add(e[i].y,e[i].x,1,Cs);
	}
	dinic();
	if(ans>a1||(ans==a1&&ans-cst>a2)){
		a1=ans,a2=ans-cst;
		out.pb({A,B});
		for(auto x:P)if(col[x]==1)e(x)if(y>0&&!w[i])out.pb({x,y});
	}else for(auto i:nw)out.pb(i);
	while(tp)h[stac[tp--]]=0;
	h[0]=h[t]=0;
	cnt=1;
	ans1+=a1,ans2+=a2;
}
int main(){
	n=read(),s=0,t=n+1;
	rep(i,1,n)e[i].x=i,e[i].y=read(),id[i]=read(),p[e[i].x].pb({e[i].y,i}),p[e[i].y].pb({e[i].x,i});
	rep(i,1,n)if(!col[i])solve(i);
	pf(ans1),putchar(' '),pf(ans2),putchar('\n');
	for(auto i:out)pf(i.first),putchar(' '),pf(i.second),putchar('\n');
	return 0;
}
```


---

