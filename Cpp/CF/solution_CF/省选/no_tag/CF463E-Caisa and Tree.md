# Caisa and Tree

## 题目描述

给出 $n$ 个点，以 $1$ 为根的树，点 $u$ 有点权 $a_u$，$q$ 次操作，每次操作为以下两种中的一种：

- `1 u`：查询点 $u$ 的一个最近祖先 $v$，使得 $\gcd(a_u,a_v)>1$，没有则输出 $-1$。

- `2 u d`：修改 $a_u$ 为 $d$。

其中，$2$ 操作次数不超过 $50$ 次。

$1\le n,m\le 10^5,1\le a_u\le 2\times10^6$

## 样例 #1

### 输入

```
4 6
10 8 4 3
1 2
2 3
3 4
1 1
1 2
1 3
1 4
2 1 9
1 4
```

### 输出

```
-1
1
2
-1
1
```

# 题解

## 作者：lzyqwq (赞：5)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17681318.html)**

树链剖分真可爱。

[**题目传送门**](https://www.luogu.com.cn/problem/CF463E "**题目传送门**")

> - 给出 $n$ 个点以 $1$ 为根的树，点 $u$ 有点权 $a_u$。$m$ 次操作，两种类型：
>
>     - $1\texttt{ }u$，查询点 $u$ 的一个**最近**祖先 $v$，满足 $\gcd(a_u,a_v)>1$，没有输出 $-1$。
>
>     - $2\texttt{ }u\texttt{ }d$，将 $a_u\leftarrow d$。
>
> - $n,m\le 10^5$，$a_u\le 2\times 10^6$。

「保证 $2$ 操作的数量不超过 $50$」的限制和 $10$ 秒的时限太不牛了。让我们去掉这个限制并将时限改为 $2$ 秒，再考虑怎么做。

看到单点修改和路径查询，容易想到树链剖分。考虑到 $\gcd(a_u,a_v)>1$ 本质上是 $a_u,a_v$ 有着共同的质因数，所以要先用欧拉筛筛出 $2\times 10^6$ 内的质数。然后可以枚举这个质因数，分别查询有该质因数的最近祖先，再从其中选出最近的即可。

由于根到某个点路径的 $dfn$ 序是递增的，考虑通过求最大的 $dfn$ 序来找到最近祖先。具体地，对每种质数维护一个 `set`，里面有序存放点权有该质因数的点的 $dfn$ 序。查询某种质因数时，在跳链的过程中通过 `lower_bound` 和 `upper_bound` 二分找到不超过当前点 $u$ 的最大 $dfn$ 序（如果 $u$ 为初始点则是严格小于，因为自己不能选），若该值 $\ge dfn_{top_u}$，说明该值对应的点在当前重链上，直接返回即可。

对于修改操作，相当于在 $a_u$ 的质因数的 `set` 中删除 $dfn_u$，在 $y$ 的质因数的 `set` 中插入 $dfn_u$。

乍一看分解质因数很暴力，但是我们可以在欧拉筛的时候处理每个数 $i$ 的最小质因数 $pre_i$，分解质因数的时候，设当前数为 $x$，则分解一个 $pre_{x}$ 出来，再令 $x\leftarrow \dfrac{x}{pre_{x}}$。由于质数 $\ge 2$，因此除以 $pre_x$ 的操作**至多进行 $\log x$ 次**，意味着我们完成了在 $\mathcal{O}(\log x)$ 的时间复杂度内分解质因数。而且，$2\times 10^6$ 内的数**本质不同的质因数个数不超过 $7$**，考虑 $2\times 3\times 5\times 7\times 11\times 13\times 17\times 19=9699690$，而我们对于同一个质因数只需要进行一次跳链查询/修改 `set`，因此单次操作跳链查询/修改 `set` 次数是常数级别。

设值域为 $V$，最终的时间复杂度为 $\mathcal{O}(m\log^2 n)$，空间复杂度为 $\mathcal{O}(|V|)$。

[**评测记录**](https://codeforces.com/contest/463/submission/222000856 "**评测记录**")

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,V=2e6+5;
int n,m,a[N],pr[V],tot,cnt,pre[V],siz[N],fa[N],hvy[N],top[N],dfn[N],id[N];
bool notp[V],vis[V];
vector<int>g[N];
set<int>s[V];
template<typename T>void read(T&x){
    x=0;T f=1;char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+c-48;
    x*=f;
}
template<typename T>void write(T x){
    if(x>9)write(x/10);
    putchar(x%10+48);
}
template<typename T>void print(T x,char ed='\n'){
    if(x<0)putchar('-'),x=-x;
    write(x),putchar(ed);
}
void reVis(int val){
    for(int tmp=val;tmp!=1;tmp/=pre[tmp])vis[pre[tmp]]=0;
}
void dfs1(int u){
    ++siz[u];
    for(int v:g[u]){
        if(v==fa[u])continue;
        fa[v]=u,dfs1(v),siz[u]+=siz[v];
    }
}
void dfs2(int u){
    for(int v:g[u]){
        if(v==fa[u])continue;
        if((siz[v]<<1)>siz[u])top[hvy[u]=v]=top[u];
        else top[v]=v;
        dfs2(v);
    }
}
void dfs3(int u){
    id[dfn[u]=++tot]=u;
    for(int tmp=a[u];tmp!=1;tmp/=pre[tmp]){
        if(!vis[pre[tmp]])vis[pre[tmp]]=1,s[pre[tmp]].insert(tot);
    }
    reVis(a[u]);
    if(hvy[u])dfs3(hvy[u]);
    for(int v:g[u]){
        if(v==fa[u]||v==hvy[u])continue;
        dfs3(v);
    }
}
int query(int x,int fac){
    int u=x;
    while(u){
        auto it=(u==x?s[fac].lower_bound(dfn[u]):s[fac].upper_bound(dfn[u]));
        if(it!=s[fac].begin()){
            --it;
            if(*it>=dfn[top[u]])return*it;
        }
        u=fa[top[u]];
    }
    return-1;
}
signed main(){
    for(int i=2;i<V;++i){
        if(!notp[i])pr[++cnt]=pre[i]=i;
        for(int j=1;i*pr[j]<V;++j){
            notp[i*pr[j]]=1,pre[i*pr[j]]=pr[j];
            if(!(i%pr[j]))break;
        }
    }
    read(n),read(m);
    for(int i=1;i<=n;++i)read(a[i]);
    for(int i=1,u,v;i<n;++i){
        read(u),read(v);
        g[u].emplace_back(v),g[v].emplace_back(u);
    }
    dfs1(1),dfs2(top[1]=1),dfs3(1);
    for(int i=1,op,x,y;i<=m;++i){
        read(op),read(x);
        if(op==1){
            int ret=-1;
            for(int tmp=a[x];tmp!=1;tmp/=pre[tmp]){
                if(!vis[pre[tmp]])vis[pre[tmp]]=1,ret=max(ret,query(x,pre[tmp]));
            }
            print(ret==-1?-1:id[ret]);
            reVis(a[x]);
        }else{
            read(y);
            for(int tmp=a[x];tmp!=1;tmp/=pre[tmp]){
                if(!vis[pre[tmp]])vis[pre[tmp]]=1,s[pre[tmp]].erase(dfn[x]);
            }
            reVis(a[x]);
            a[x]=y;
            for(int tmp=y;tmp!=1;tmp/=pre[tmp]){
                if(!vis[pre[tmp]])vis[pre[tmp]]=1,s[pre[tmp]].insert(dfn[x]);
            }
            reVis(y);
        }
    }
    return 0;
}
```

---

## 作者：_edge_ (赞：1)

~~暴力出奇迹。~~

我们看到这个操作非常的难搞呀，想 $\log n$ 级别来维护显然是不太可能。

但是我们又看到，`保证 2 操作的数量不超过 50。`，以及 10s 的时限，尝试用暴力来出奇迹。

但是这个暴力要写的足够优美，首先，先遍历一下整棵树，遍历到一个点，把它质因数分解了，统计答案，因为 $\gcd>1$ 必定有两个数是有公共的质因子的，然后扔到一个质数的桶里面去，记得把桶给清空了。

如果有操作 $2$，就只把那个点给清空了，其他点不变，这样能有一个非常强的剪枝效果。

我们来分析一下这个复杂度，对于开始的分解质因数，我们只能 $O(\sqrt n)$ 来分解，但是，可以把质数先筛出来再分解，这样分解效率更高一些。

对于后来，每次只需要遍历这棵树 $O(n)$，并且实际上我们只需要分解一个数，所以是一次就只有 $O(\sqrt n)$ 的。

同时，一个数的质因子个数是非常非常少的，比 $\log$ 还要少，所以 $5 \times 10^6$ 是完全不用担心的，毕竟时限还开这么大呀。

最后几个坑点注意一下，一定要清空！，以及询问的答案是深度最大而不是点的大小。

目前我的做法在 lg 是最优解。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
const int INF=1e5+5;
const int INFN=2e6+5;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int n,m,head[INF],tot,a[INF],dep[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ;
}
bool prime[INFN];
vector <int> Prime,D[INF],L[INF],LL[INF];
int p[INFN],aa[INF],pp[INFN],bb[INF];
void solve(int x) {
	int xx=a[x];
	for (int i=0;Prime[i]*Prime[i]<=xx;i++) {
		if (xx%Prime[i]==0) D[x].pb(Prime[i]),L[x].pb(0),LL[x].pb(0);
		while (xx%Prime[i]==0) xx/=Prime[i];
	}
	if (xx>1) D[x].pb(xx),L[x].pb(0),LL[x].pb(0);
	return ;
} 
void DFS(int x,int fa) {
	dep[x]=dep[fa]+1;
	if (D[x].size()==0) solve(x);
	int len=D[x].size();aa[x]=0;
	for (int i=0;i<len;i++) {
		if (aa[x]<p[D[x][i]]) aa[x]=p[D[x][i]],bb[x]=pp[D[x][i]];
		L[x][i]=p[D[x][i]];LL[x][i]=pp[D[x][i]];
		if (p[D[x][i]]<dep[x]) p[D[x][i]]=dep[x],pp[D[x][i]]=x;
		
	}
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x);
	}
	for (int i=0;i<len;i++)
		p[D[x][i]]=L[x][i],pp[D[x][i]]=LL[x][i];
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=2;i<=2e6;i++) {
		if (!prime[i]) Prime.pb(i);
		int len=Prime.size(); 
		for (int j=0;j<len && Prime[j]*i<=2e6;j++) {
			prime[Prime[j]*i]=1;
			if (!(i%Prime[j])) break;
		}
	}
	
	for (int i=1;i<n;i++) {
		int x=0,y=0;cin>>x>>y;
		add_edge(x,y);add_edge(y,x);
	}
	DFS(1,0);
	
	for (int i=1;i<=m;i++) {
		int op=0,x=0;cin>>op>>x;
		if (op==1) cout<<(bb[x]?bb[x]:-1)<<"\n";
		else {
//			memset(p,0,sizeof p);
//			memset(pp,0,sizeof pp);
			int y=0;cin>>y;
			a[x]=y;D[x].clear();L[x].clear();
			DFS(1,0);
		}
	}
	return 0;
}
```


---

## 作者：AladV (赞：1)

## 题意分析
稍微需要注意的是他让你输出的是节点编号 $u_i$，不是 $i$ 。

## 做法分析
我们考虑对于询问 v 我们要做什么。即，我们要找在 $1-v$ 路径上与 v 不互质的最深的点，不互质这个条件更苛刻一些。我们想一想怎么处理，既然要不互质，那么显然只要任意一个数与 v 有任意一个公因数就行，于是我们预处理出 $a_i$ 的所有质因数，存在一个叫做 p 的 vector 里边。完了之后呢我们就可以开始 dfs 了。在 $dfs$ 的过程中，我们维护一个 set，类型是 pair, 实际意义的话 $set_i$ 表示包含因子 i 的数字最深出现在那里，什么深度，是哪个点。

在 dfs 的时候，我们先有一个循环 $i\in [0,p[u].size]$，即枚举当前数字 u 的每一个因数，然后如果 $set_{p_{u,i}}$ 不为空，即，在当前递归搜索的子树中，在 u 的前面，至少有一个数与 v 共同拥有 $p_{u,i}$ 这个因子，那么显然我们就可以把 $ans_u$ 更新为这个数字。在**更新完之后**，我们把 $p_{u,i}$ 放进 set 里边，所以不会出现 $ans_u=u$ 的情况。

值得注意的是，在递归查找完之后，我们需要把 $set$ 里边的元素删除掉，因为我们要回到我们的父节点，也就是我们要进入一个新的子树进行工作了，如果不删除的话会影响正确性。细节详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
vector<int> p[N];
set<pair<int,int> > s[N*30];
pair<int,int> ans[N];
int n,q,dep[N],a[N];
int tot,head[N],ver[N<<1],nxt[N<<1];
int read()
{
    int x=0,f=1;
    char c=getchar();
    while (c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
void Get_Prime(int val,int u)
{
    p[u].clear();
    for(int i=2;i*i<=val;i++)
    {
        if(val%i) continue;
        p[u].push_back(i);
        while(val%i==0) val/=i;
    }
    if(val!=1) p[u].push_back(val);
}
void add(int x,int y)
{
    tot++;
    ver[tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void DFS(int u,int fa)
{
    ans[u]=make_pair(-1,-1);
    dep[u]=dep[fa]+1;
    for(int i=0;i<p[u].size();i++)
    {
        int prime=p[u][i];
        if(s[prime].size()) ans[u]=max(ans[u],*s[prime].rbegin());
        s[prime].insert(make_pair(dep[u],u));
    }

    for(int i=head[u];i;i=nxt[i])
    {
        int v=ver[i];
        if(v==fa) continue;
        DFS(v,u);
    }

    for(int i=0;i<p[u].size();i++) s[p[u][i]].erase(make_pair(dep[u],u));
}
int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) Get_Prime(a[i],i);
    for(int i=1;i<n;i++)
    {
        int x=read(),y=read();
        add(x,y);
        add(y,x);
    }
    DFS(1,0);
    while(q--)
    {
        int opt=read();
        if(opt==1) 
        {
            int x=read();
            cout<<ans[x].second<<endl;
        }
        else
        {
            int x=read(),y=read();
            Get_Prime(y,x);
            DFS(1,0);
        }
    }
    return 0;
}
```


---

## 作者：small_john (赞：0)

## 前言

一眼秒了这道题，目前还是最优解，所以写篇题解纪念一下。

## 思路

考虑没有修改的时候怎么做。

不难发现，两个数的最大公因数大于一的充要条件为这两个数有相同的质因数，而一个数 $x$ 的质因数个数一定小于 $\log x$，所以想到预处理所有点的答案。直接暴力分解质因数然后开个桶记录一下即可（可以使用 vector 实现）。时间复杂度 $O(n\sqrt V+n\log V)$，其中 $V$ 指值域。

注意到，最多修改 $50$ 次，而每次只需要重新计算修改位置的质因数和修改位置的子树的答案即可。

时间复杂度 $O((n+T)\sqrt V+Tn\log n)$，其中 $T$ 指修改次数，$V$ 指值域。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5,M = 2e6+5;
int n,m,a[N],f[N],ans[N],dep[N],pt[N],cnt;
vector<int> g[N],p[N],v[M];
inline void calc(int u)
{
	p[u].clear();
	int x = a[u];
	for(int i = 2;i*i<=x;i++)
		if(x%i==0)
		{
			p[u].push_back(i);
			while(x%i==0) x/=i;
		}
	if(x>1) p[u].push_back(x);
}
void dfs(int u,int fa)
{
	f[u] = fa,ans[u] = -1,dep[u] = dep[fa]+1;
	for(auto i:p[u])
	{
		if(v[i].size()&&(ans[u]==-1||dep[v[i].back()]>dep[ans[u]])) ans[u] = v[i].back();
		v[i].push_back(u);
	}
	for(auto v:g[u])
	{
		if(v==fa) continue;
		dfs(v,u);
	}
	for(auto i:p[u]) v[i].pop_back();
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		cin>>a[i],calc(i);
	for(int i = 1,u,v;i<n;i++)
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs(1,0);
	while(m--)
	{
		int op,x,y;
		cin>>op>>x;
		if(op==1) cout<<ans[x]<<'\n';
		else
		{
			cin>>y;
			cnt = 0;
			int u = f[x];
			while(u) pt[++cnt] = u,u = f[u];
			for(int i = cnt;i;i--)
			{
				u = pt[i];
				for(auto i:p[u]) v[i].push_back(u);
			}
			a[x] = y,calc(x);
			dfs(x,f[x]);
			for(int i = cnt;i;i--)
			{
				u = pt[i];
				for(auto i:p[u]) v[i].clear();
			}
		}
	}
	return 0;
}
```

---

## 作者：teylnol_evteyl (赞：0)

一个 $O(n\log^2n)$ 的线段树做法。

首先，由于修改操作数量不多，让修改操作把整个过程分成几段，在每一段中分别预处理和查询，这样这道题就被转换成了一个静态问题。

由于最大公约数不等于 $1$，所以两个数一定有相同的质因数。先将点权分解质因数，这里用线性筛预处理每个数最小的质因子和出去所有最小质因子后的数，可以 $O(\log n)$ 地分解质因数。对于每个点，它可以成为它子树中与它有相同质因数的点的满足要求的点。对每个质数分别讨论，先将所有的值设为 $-1$，再从深度较浅的点到深度较深的点枚举，将这些点的子树对应的 dfs 区间的值设为这个节点的编号，这样最后每个位置表示能覆盖到这个位置的区间对应节点深度最大的编号，也就是这个位置的 dfs 序对应节点的儿子的答案。然后枚举包含这个质因子的查询的节点获得答案。这个过程可以用线段树维护。总的时间复杂度是 $O(n\log^2n)$，带个 $50$ 的常数。

注意，这个问题要求答案的**深度**取最大值，而不是编号取最大值。

```cpp
#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

const int N = 1e5 + 5, M = 2e6 + 5;

int n, m, a[N];
int la[N], ne[N * 2], en[N * 2], idx;
int Fa[N], dep[N], in[N], out[N], dfst;
int prime[M], cnt;
int pre[M], pi[M];
vector<int> p[M];
vector<pair<int, int> > q[M];
int qid, res[N];
struct node{
	int a, b;
	int v;
}t[N * 4];
int mp, md;
int TT;

void pushdown(int u)
{
	if(t[u].a != t[u].b && t[u].v != -2)
	{
		t[u << 1].v = t[u << 1 | 1].v = t[u].v;
		t[u].v = -2;
	}
}
void build(int u, int a, int b)
{
	t[u].a = a, t[u].b = b;
	if(t[u].a == t[u].b) t[u].v = -1;
	else
	{
		int mid = a + b >> 1;
		build(u << 1, a, mid), build(u << 1 | 1, mid + 1, b);
		t[u].v = -2;
	}
}
void modify(int u, int x, int y, int d)
{
	if(x <= t[u].a && t[u].b <= y)
	{
		t[u].v = d;
		return ;
	}
	pushdown(u);
	int ls = u << 1, rs = ls | 1;
	if(t[ls].b >= x) modify(ls, x, y, d);
	if(t[rs].a <= y) modify(rs, x, y, d);
}
int query(int u, int x)
{
	if(t[u].a == t[u].b) return t[u].v;
	pushdown(u);
	int ls = u << 1, rs = ls | 1;
	if(t[ls].b >= x) return query(ls, x);
	return query(rs, x);
}

void add(int a, int b)
{
	ne[ ++ idx] = la[a];
	la[a] = idx;
	en[idx] = b;
}
void dfs(int u, int fa)
{
	Fa[u] = fa;
	dep[u] = dep[fa] + 1;
	in[u] = ++ dfst;
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(v != fa) dfs(v, u);
	}
	out[u] = dfst;
}

void get_prime()
{
	for(int i = 2; i < M; i ++ )
	{
		if(!pre[i])
		{
			prime[ ++ cnt] = i;
			pre[i] = 1, pi[i] = cnt;
		}
		for(int j = 1; j <= cnt && i * prime[j] < M; j ++ )
		{
			int t = i * prime[j];
			pi[t] = j;
			if(i % prime[j] == 0)
			{
				pre[t] = pre[i];
				break;
			}
			pre[t] = i;
		}
	}
}

bool cmp(int a, int b)
{
	return dep[a] < dep[b];
}
void build()
{
	for(int i = 1; i <= n; i ++ )
	{
		int t = a[i];
		while(t > 1) p[pi[t]].push_back(i), t = pre[t];
	}
}
void solve()
{
	for(int i = 1; i <= qid; i ++ ) res[i] = -1;
	for(int i = 1; i <= cnt; i ++ )
	{
		if(q[i].size())
		{
			modify(1, 1, n, -1);
			if(p[i].size()) sort(p[i].begin(), p[i].end(), cmp);
			for(auto j : p[i]) modify(1, in[j], out[j], j);
			for(auto j : q[i])
				if(j.x)
					res[j.y] = max(res[j.y], query(1, in[j.x]), cmp);
			q[i].clear();
		}
		p[i].clear();
	}
	for(int i = 1; i <= qid; i ++ ) printf("%d\n", res[i]);
	qid = 0;
}

int main()
{
	get_prime();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	build();
	for(int i = 1; i < n; i ++ )
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	dfs(1, 0);
	build(1, 1, n);
	for(int i = 1; i <= m; i ++ )
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int u;
			scanf("%d", &u);
			qid ++ ;
			if(qid == 1) TT = u;
			int t = a[u];
			while(t > 1) q[pi[t]].push_back({Fa[u], qid}), t = pre[t];
		}
		else
		{
			solve();
			scanf("%d%d", &mp, &md);
			a[mp] = md;
			build();
		}
	}
	if(qid) solve();
	return 0;
}

```

---

