# Berland Beauty

## 题目描述

There are $ n $ railway stations in Berland. They are connected to each other by $ n-1 $ railway sections. The railway network is connected, i.e. can be represented as an undirected tree.

You have a map of that network, so for each railway section you know which stations it connects.

Each of the $ n-1 $ sections has some integer value of the scenery beauty. However, these values are not marked on the map and you don't know them. All these values are from $ 1 $ to $ 10^6 $ inclusive.

You asked $ m $ passengers some questions: the $ j $ -th one told you three values:

- his departure station $ a_j $ ;
- his arrival station $ b_j $ ;
- minimum scenery beauty along the path from $ a_j $ to $ b_j $ (the train is moving along the shortest path from $ a_j $ to $ b_j $ ).

You are planning to update the map and set some value $ f_i $ on each railway section — the scenery beauty. The passengers' answers should be consistent with these values.

Print any valid set of values $ f_1, f_2, \dots, f_{n-1} $ , which the passengers' answer is consistent with or report that it doesn't exist.

## 样例 #1

### 输入

```
4
1 2
3 2
3 4
2
1 2 5
1 3 3```

### 输出

```
5 3 5```

## 样例 #2

### 输入

```
6
1 2
1 6
3 1
1 5
4 1
4
6 1 3
3 4 1
6 5 2
1 2 5```

### 输出

```
5 3 1 2 1```

## 样例 #3

### 输入

```
6
1 2
1 6
3 1
1 5
4 1
4
6 1 1
3 4 3
6 5 3
1 2 4```

### 输出

```
-1```

# 题解

## 作者：ix35 (赞：4)

分析一个性质：对于一条边，设经过它的所有路径的路径最小值分别为 $W_1,\cdots,W_n$，再设这条边的权值为 $w_i$，那么有：

$$w_i\ge \max(W_1,\cdots,W_n)$$

而且，如果令 $w_i=\max(W_1,\cdots,W_n)$，不会与任何目前已知的条件矛盾。

于是我们按照最小值从小到大排序给定的路径，遇到一条路径就将这条路径上所有边的权值赋值为这条路径的最小值，这样上面的 $w_i$ 就都求完了。

最后还要检验，将每条路径带进去算一下，有不满足的就是 $-1$。

为什么这样一定对呢？会不会存在另外一种赋权方案使得答案不是 $-1$？

显然是不可能的，因为当前的 $w_i$ 已经取到了最小值，如果 $w_i$ 还要变大，那么路径最小值是不会变小的，当然依然不可能满足条件。

因为 $n,m$ 很小，没必要用高级算法，暴力跳 LCA 就可以了（LCA 还是倍增求了一下，感觉比暴力还方便）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=5010;
struct Q {
	int u,v,w;
}q[MAXN];
int n,m,x,y,eg,hd[MAXN],ver[2*MAXN],nx[2*MAXN],num[MAXN],w[MAXN],dep[MAXN],f[MAXN][20];
bool cmp (Q a,Q b) {return a.w<b.w;}
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	f[x][0]=fa,dep[x]=dep[fa]+1;
	for (int i=1;i<=15;i++) {f[x][i]=f[f[x][i-1]][i-1];}
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		num[ver[i]]=(i+1)/2;
		dfs(ver[i],x);
	}
	return;
}
int query_lca (int x,int y) {
	if (dep[x]<dep[y]) {swap(x,y);}
	for (int i=15;i>=0;i--) {
		if (dep[x]-(1<<i)>=dep[y]) {x=f[x][i];}
	}
	if (x==y) {return x;}
	for (int i=15;i>=0;i--) {
		if (f[x][i]!=f[y][i]) {x=f[x][i],y=f[y][i];}
	}
	return f[x][0];
}
void modify (int u,int v,int we) {
	int l=query_lca(u,v);
	while (u!=l) {
		w[num[u]]=we;
		u=f[u][0];
	}
	while (v!=l) {
		w[num[v]]=we;
		v=f[v][0];
	}
	return;
}
int query (int u,int v) {
	int l=query_lca(u,v);
	int res=1000001;
	while (u!=l) {
		res=min(res,w[num[u]]);
		u=f[u][0];
	}
	while (v!=l) {
		res=min(res,w[num[v]]);
		v=f[v][0];
	}
	return res;
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x); 
	}
	dfs(1,0);
	scanf("%d",&m);
	for (int i=1;i<=m;i++) {
		scanf("%d%d%d",&q[i].u,&q[i].v,&q[i].w);
	}
	sort(q+1,q+m+1,cmp);
	for (int i=1;i<=m;i++) {
		modify(q[i].u,q[i].v,q[i].w);
	}
	int flg=0;
	for (int i=1;i<=m;i++) {
		if (query(q[i].u,q[i].v)!=q[i].w) {flg=1;break;}
	}
	if (flg) {printf("-1\n");}
	else {
		for (int i=1;i<=n-2;i++) {
			printf("%d ",w[i]?w[i]:1);
		}
		printf("%d\n",w[n-1]?w[n-1]:1);
	}
	return 0;
}
```


---

## 作者：Awdrgysxc (赞：4)

## 【$Analysis$】
可以在$M$条路径上做max，最后检查一下就好了，注意没有赋值的就随便赋一个大于0的数

发现$N,M \leq 5000$

暴力即可

若$N,M \leq 5\times 10^5$

可以考虑倍增打标记，到最后再标记下放，复杂度$O(N\times \log N)$

## 【$Code$】暴力
```cpp
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;
const int MaxN = 3e5 + 11;
int f[MaxN];
int dep[MaxN];
int fa[MaxN];
int id[MaxN];
int U[MaxN];
int V[MaxN];
int W[MaxN];
int N, M;

vector <pair <int,int> > adj[MaxN];

void dfs(int u, int pre) {
	int si = int(adj[u].size());
	fa[u] = pre, dep[u] = dep[pre] + 1;
	for (int i = 0;i < si; ++i) {
		int v = adj[u][i].first;
		if (v == pre) continue;
		dfs(v, u), id[v] = adj[u][i].second;
	}
}

void modify(int u, int v, int w) {
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] > dep[v]) {
		f[id[u]] = max(f[id[u]], w);
		u = fa[u];
	}
	
	while (u != v) {
		f[id[u]] = max(f[id[u]], w),
		f[id[v]] = max(f[id[v]], w),
		u = fa[u],
		v = fa[v];
	}
}

bool query(int u, int v, int w) {
	int res = 2e9;
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] > dep[v]) {
		res = min(f[id[u]], res);
		if (res < w) return false;
		u = fa[u];
	}
	
	while (u != v) {
		res = min(f[id[u]], res),
		res = min(f[id[v]], res);
		if (res < w) return false;
		u = fa[u],
		v = fa[v];
	}
	return w == res;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	
	cin >> N;
	for (int i = 1;i < N; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(make_pair(v, i)),
		adj[v].push_back(make_pair(u, i));
	}
	dfs(1, 0);
	
	cin >> M;
	for (int i = 1;i <= M; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		modify(u, v, w);
		U[i] = u, V[i] = v, W[i] = w;
	}
	
	bool ok = 1;
	for (int i = 1;i <= M; ++i) {
		ok &= query(U[i], V[i], W[i]);
		if (!ok) break;
	}
	
	if (!ok) puts("-1");
	else 
		for (int i = 1;i < N; ++i)
			cout << (f[i] == 0 ? 1 : f[i]) << ' ';
	
	return 0;
}
```

---

## 作者：Karry5307 (赞：3)

### 题意

给定一棵 $n$ 个点的数。告诉你 $m$ 个信息，每个信息形如 $u_i$ 到 $v_i$ 的路径上最小边权是 $w_i$，你需要给出一组对边赋权的方案使得满足以上信息，或者说明无解。

$\texttt{Data Range:}1\leq n,m\leq 5\times 10^3$

### 题解

暴力都能过，或者是树链剖分板子。

考虑将询问按照边权从小到大排序，对于每一次询问直接覆盖经过的边的边权。

然后将没有被所有询问考虑到的边设成最大值，接着一个一个检查一遍就好了。

时间复杂度 $O(n^2)$，由于数据过水，可以通过。

注意到我们的过程就是链的覆盖，这个可以使用树链剖分在 $O(n\log^2n)$ 的时间复杂度内通过此题。

所以……就没了？

是的。如果你是 TLE/WA on 148 话请注意数组是否开小了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=5e3+51;
struct Edge{
	ll to,prev;
};
struct Query{
	ll x,y,k;
	inline bool operator <(const Query &rhs)const
	{
		return this->k<rhs.k;
	}
};
Edge ed[MAXN<<1];
Query qry[MAXN];
ll nc,tot,from,to,qcnt,x,y,z,hasSol,r;
ll last[MAXN],res[MAXN<<1];
vector<ll>s,ss;
vector<ll>bs[MAXN];
inline ll read()
{
    register ll num=0;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num;
} 
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
inline void dfs(ll x,ll y,ll fa)
{
	if(x==y)
	{
		ss=s,hasSol=1;
		return;
	}
	for(register int i=last[x];i;i=ed[i].prev)
	{
		if(ed[i].to!=fa)
		{
			s.push_back(i),dfs(ed[i].to,y,x),s.pop_back();
		}
	}
}
int main()
{
	nc=read(),memset(res,0x3f,sizeof(res));
	for(register int i=0;i<nc-1;i++)
	{
		from=read(),to=read();
		addEdge(from,to),addEdge(to,from);
	}
	qcnt=read();
	for(register int i=0;i<qcnt;i++)
	{
		qry[i].x=read(),qry[i].y=read(),qry[i].k=read();
	}
	sort(qry,qry+qcnt);
	for(register int i=0;i<qcnt;i++)
	{
		s.clear(),hasSol=0,dfs(qry[i].x,qry[i].y,0);
		bs[i]=ss;
		for(register int p=0;p<ss.size();p++)
		{
			ll j=ss[p];
			res[j]=res[((j+1)^1)-1]=qry[i].k;
		}
	}
	for(register int i=0;i<qcnt;i++)
	{
		r=0x3f3f3f3f,ss=bs[i];
		for(register int p=0;p<ss.size();p++)
		{
			ll j=ss[p];
			r=min(r,res[j]);
		}
		if(r!=qry[i].k)
		{
			puts("-1");
			return 0;
		}
	}
	for(register int i=1;i<=nc*2-2;i+=2)
	{
		cout<<(res[i]!=1061109567?res[i]:1000000)<<" ";
	} 
}
```

---

## 作者：封禁用户 (赞：1)

这题似乎是许多题的弱化版。

对于一个人的批话，那么是不是只要满足这条路径上的边的边权都是 $w$。

那么对于所有人的呢？按 $w$ 从小到大排，这不就是赤裸裸的覆盖问题？

然后无解就是检查一下每条路径最小值是不是 $w$。没被覆盖到也要边权为 $1$。

随便拿个数据结构来做。比如树剖。或者 $O(nm)$ 暴力。

---

## 作者：Zimo_666 (赞：1)

## CF1296F

### 题意

给你一颗大小为 $n$ 的无根树，树边的边权尚未确定。现在你从 $m$ 个人中得知在 $(u,v)$ 这条路径(最短路径)上的最小边权为 $w$。请你构造一种方案满足这 $m$ 个人的条件，如果不存在，请输出 $-1$。

### 分析

我们显然可以先把边权按照从小到大排序，而后构造一种最优方案即把这条路径上的所有边都赋值为 $w$。这样我们可以使得每条路径上的最小值都尽可能满足题面的要求。而后我们检验是否合法。使用 LCA 维护即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+7;
struct node{int u,v,w;}a[N];
int f[N][50];
int head[N],to[N],nxt[N];
int fat[N];
int dis[N],dep[N];
int cnt;
int n,m;
int num[N];
int w[N];
void add(int u,int v){
	cnt++;to[cnt]=v;nxt[cnt]=head[u];head[u]=cnt;
}
int xx;
void dfs(int x,int fa){
	++xx;
	if (xx > 1e6) exit(0);
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==fa) continue;
        num[y]=(i+1)/2;
		dep[y]=dep[x]+1;fat[y]=x;dfs(y,x);
	}
}
void init(){
	for(int i=1;i<=n;i++) f[i][0]=fat[i];
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
}
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    if (dep[x] != dep[y]) {
        for (int i = 20; i >= 0; i--)
            if (dep[f[x][i]] > dep[y])
                x = f[x][i];
        x = f[x][0];
    }
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
void modify(int u,int v,int val){
    int _lca=lca(u,v);
    while(u!=_lca) w[num[u]]=val,u=f[u][0];
    while(v!=_lca) w[num[v]]=val,v=f[v][0];
}
int query(int u,int v){
    int _lca=lca(u,v);
    int res=0x3f3f3f3f;
    while(u!=_lca) res=min(res,w[num[u]]),u=f[u][0];
    while(v!=_lca) res=min(res,w[num[v]]),v=f[v][0];
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    dfs(1,0);
    init();
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].w);
    }
    sort(a+1,a+1+m,[](const node a,const node b){return a.w<b.w;});
    // for(int i=1;i<=m;i++) printf("%d\n",a[i].w);
     // for(int i=1;i<=n;i++) printf("%d\n",num[i]);
    for(int i=1;i<=m;i++) modify(a[i].u,a[i].v,a[i].w);
    bool flag=0;
    for(int i=1;i<=m;i++){
    	// printf("%d ",query(a[i].u,a[i].v));
        if(query(a[i].u,a[i].v)!=a[i].w){flag=1;break;}
    }
    if(flag) printf("-1\n");
    else{
        for(int i=1;i<=n-1;i++){
            printf("%d ",w[i]?w[i]:1);
        }
        // printf("%d\n",w[n-1]?w[n-1]:1);
    }
    return 0;
}
```

---

## 作者：TankYu (赞：0)

问题即对边权 $W$，其受形如 $W \ge w$ 这样的限制。

即有 $W \ge w_{\max}$，不妨基于这一点，直接令 $W = w_{\max}$，此时若非法，则不可能有合法解。

这便令人想到将限制按 $w$ 排序，然后覆盖，最后扫一遍看合不合法。

这个题 $n$ 很小，可以考虑写个暴力覆盖而不用重剖。

然后其实遍历路径有一个比较优美的写法：

```cpp
if (dfn[u] < dfn[v])
{
    swap(u, v);
}
while (dfn[u] > dfn[v])
{
    W[u] = w;
    u = fa[u];
}
while (u != v)
{
    if (u == v)
    {
        break;
    }
    W[v] = w;
    v = fa[v];
}
```

原理就是对于 $u,v$（保证 $dfn_u > dfn_v$）两个点的最近公共祖先，其儿子中子树包含 $v$ 的一定早于包含 $u$ 的被遍历，也就是包含 $v$ 的子树中任何一个点的 $dfn$ 都比包含 $u$ 的小。

这样第一个循环结束时，$u$ 就是最近公共祖先。

[code](https://codeforces.com/contest/1296/submission/305080403)

值得关注的是，**本题边权取值要在 $[1,10^6]$ 中**。

---

## 作者：kimi0705 (赞：0)

首先，贪心得把每一个人得要求按照 $w$ 从小到大排序，以免小的被大的给覆盖了。

然后就把 $u,v$ 上的路径给覆盖成 $w$ 就行了。

考虑如何求 $u,v$ 路径。

- 求 $l=\operatorname{lca}(u,v)$。
- 不断让 $u$ 成为自己的父亲，并标记边，直到 $u=l$。
- 不断让 $v$ 成为自己的父亲，并标记边，直到 $u=l$。

注意其他要标记为 $[1,10^6]$ 范围的整数。

---

