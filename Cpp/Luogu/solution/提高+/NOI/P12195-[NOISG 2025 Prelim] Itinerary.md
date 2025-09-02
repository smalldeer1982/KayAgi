# [NOISG 2025 Prelim] Itinerary

## 题目描述

科学委员会计划访问 $n$ 个城市。这 $n$ 个城市通过恰好 $n - 1$ 条道路连接，使得可以使用这些道路在所有城市对之间移动。第 $i$ 条道路建在城市 $u[i]$ 和 $v[i]$ 之间。

每个城市都有自己的机场。为了开始旅程，委员会将从新加坡飞往其中一个城市。为了尽可能高效地利用旅程，委员会希望通过每条道路**恰好两次**（每个方向一次）来访问每个城市**至少一次**，然后从他们最终到达的城市飞回家。满足这个条件的旅程称为**巡游**。

![](https://cdn.luogu.com.cn/upload/image_hosting/glw0pqmy.png)

例如，设上图表示一个有 $n = 8$ 个城市的地图。从城市 $1$ 开始的一种可能的巡游是 $1 \to 3 \to 5 \to 3 \to 4 \to 2 \to 8 \to 2 \to 4 \to 6 \to 4 \to 7 \to 4 \to 3 \to 1$。注意这个巡游总共访问了所有城市 $2n - 1$ 次（等于 $15$），并且以起始城市（城市 $1$）结束。可以证明，对于所有可能的城市地图，所有巡游都满足这两个性质。

委员会还希望访问 $m$ 个按顺序从事件 $1$ 到事件 $m$ 发生的活动。事件 $j$ 将在城市 $s[j]$ 举行。一个城市可以举办零个、一个或多个活动，但不会有两个连续的活动在同一个城市举行，即 $s[j] = s[j + 1]$。

允许委员会访问所有活动的巡游必须按顺序访问城市 $s[1], s[2], \ldots, s[m]$，但不必连续。这样的巡游称为**行程**。形式上，设 $t[1], t[2], \ldots, t[2n - 1]$ 为某个巡游访问的城市序列。当且仅当 $s$ 是 $t$ 的一个子序列时，该巡游是一个行程。也就是说，可以通过删除 $t$ 中的零个或多个元素并保持剩下元素的顺序，得到 $s$。仍以上面的例子为例，假设 $m = 4$ 且 $s = [3, 5, 2, 7]$，那么巡游 $1 \to \textbf{3} \to \textbf{5} \to 3 \to 4 \to \textbf{2} \to 8 \to 2 \to 4 \to 6 \to 4 \to \textbf{7} \to 4 \to 3 \to 1$ 是一个行程，因为城市 $3, 5, 2, 7$ 按顺序在巡游中被访问（用粗体标记并下划线）。

委员会仍在决定从哪个城市出发，但他们同意：如果存在某个以该城市出发的行程，那么该城市就是一个好的出发选择。请帮助委员会判断对于所有城市，是否存在至少一个以该城市出发的行程。


## 说明/提示

### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $2 \leq n \leq 200\,000$
- $1 \leq m \leq 2n - 1$
- $1 \leq u[i], v[i] \leq n$ 对所有 $1 \leq i \leq n - 1$
- $1 \leq s[j] \leq n$ 对所有 $1 \leq j \leq m$
- $s[j] \neq s[j + 1]$ 对所有 $1 \leq j \leq m - 1$
- 可以通过道路在所有城市对之间移动。

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分值 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $7$ | $n \leq 1000, m = 2n - 1$ |
| $2$ | $10$ | $u[i] = 1, v[i] = i + 1$ |
| $3$ | $6$ | $n \leq 1000, u[i] = i, v[i] = i + 1$ |
| $4$ | $7$ | $u[i] = i, v[i] = i + 1$ |
| $5$ | $14$ | $n \leq 1000, m \leq 10$ |
| $6$ | $5$ | $n \leq 1000$ |
| $7$ | $19$ | $m \leq 10$ |
| $8$ | $11$ | $s[1] = s[m]$ |
| $9$ | $21$ | 无 |

### 样例 1 解释

此样例适用于子任务 $5, 6, 7, 9$。

这个样例在题目中已经作为示例说明。

存在以城市 $1, 3, 4, 6$ 和 $7$ 开始的行程。在题目中已给出一个以城市 $1$ 开始的行程。

另一方面，可以证明城市 $2, 5$ 和 $8$ 没有任何行程可以以它们为起点。

### 样例 2 解释

此样例适用于子任务 $5, 6, 7, 9$。

这个测试用例与题目示例相同，除了 $s[2]$ 和 $s[3]$ 被交换了。此时不存在任何行程。

### 样例 3 解释

此样例适用于子任务 $1, 2, 5, 6, 7, 8, 9$。

### 样例 4 解释

此样例适用于子任务 $3, 4, 5, 6, 7, 9$。

## 样例 #1

### 输入

```
8 4
1 3
2 4
3 4
4 6
5 3
2 8
7 4
3 5 2 7```

### 输出

```
1
0
1
1
0
1
1
0```

## 样例 #2

### 输入

```
8 4
1 3
2 4
3 4
4 6
5 3
2 8
7 4
3 2 5 7```

### 输出

```
0
0
0
0
0
0
0
0```

## 样例 #3

### 输入

```
4 7
1 2
1 3
1 4
2 1 2 1 2 1 2```

### 输出

```
0
0
0
0```

## 样例 #4

### 输入

```
5 2
1 2
2 3
3 4
4 5
2 4```

### 输出

```
1
1
1
1
1```

# 题解

## 作者：Mr_Az (赞：4)

# [P12195 [NOISG 2025 Prelim] Itinerary](https://www.luogu.com.cn/problem/P12195)

### Algorithm:

树链剖分。

### Solution:

赛时没切，大悲。

由于树的性质：从 $u$ 到 $v$ 的任意路径至少要经过其两点间最短路一次，加上我们遍历到的活动城市是要按顺序遍历的，所以我们可以猜测一个行程不合法的情况当且仅当**沿着行程中相邻两点的最短路遍历的时候至少一条边被遍历了大于 $2$ 次**。

这个结论显然是正确的，因为其他在这个遍历顺序中没有遍历到的边都可以进去走一遍再出来，对结果并没有影响。

于是我们要做的就是维护路径加，全局最小值，树链剖分即可。

我们首先按顺序将活动行程中相邻两点的最短路加入，至于从不同城市出发，在活动行程的最开始加入 $i$ 到 $s_1$ 的最短路判断最小值是否 $\le 2$ 即可。

赛事没切的原因是忘记树链剖分的细节了，自己的实现出现了问题。

时间复杂度：$\text{O}(n \log^2 n)$。

提供另外一个做法，发现这道题要做的就是将每一个城市作为活动行程的起点时，活动行程是否是以这个城市开头的欧拉序列的子序列。

所以可以直接换根 DP，但是笔者没有实现。

### Code:

```cpp
void read(T &x, Args &... y){read(x);read(y...);}
int n,m,ddfn;
int s[N],dfn[N],ed[N],siz[N],son[N],top[N],dep[N],fa[N];
vector<int> e[N];
void dfs(int u,int fa){
    dep[u]=dep[fa]+1;siz[u]=1;::fa[u]=fa;
    int mx=0;
    for(auto v:e[u]){
        if(v==fa) continue;
        dfs(v,u);
        if(mx<siz[v]) son[u]=v,mx=siz[v];
        siz[u]+=siz[v];
    }
    return ;
}
void dfs1(int u,int fa,int t){
    top[u]=t;dfn[u]=++ddfn;
    if(!son[u]) return ;
    dfs1(son[u],u,t);
    for(auto v:e[u]){
        if(v!=fa&&v!=son[u]) dfs1(v,u,v);
    }
    // ed[u]=ddfn;
    return ;
}
inline bool in(int x,int y){return dfn[y]<=dfn[x]&&dfn[x]<=ed[y];}
struct tree{
    int x,add;
    #define x(p) t[p].x
    #define add(p) t[p].add
}t[N*4];
#define mid (l+r>>1)
inline void update(int p){x(p)=max(x(ls),x(rs));}
inline void spread(int p){
    if(add(p)!=0){
        x(ls)+=add(p);
        x(rs)+=add(p);
        add(ls)+=add(p);add(rs)+=add(p);
        add(p)=0;
    }
    return ;
}
void addd(int p,int l,int r,int L,int R,int k){
    if(L>R) return ;
    if(L<=l&&r<=R){x(p)+=k;add(p)+=k;return ;}
    spread(p);
    if(L<=mid) addd(ls,l,mid,L,R,k);
    if(R>mid)  addd(rs,mid+1,r,L,R,k);
    update(p);
    return ;
}
int ask(int p,int l,int r,int L,int R){
    if(L>R) return 0;
    if(L<=l&&r<=R) return x(p);
    spread(p);
    int res=0;
    if(L<=mid) res=max(res,ask(ls,l,mid,L,R));
    if(R>mid)  res=max(res,ask(rs,mid+1,r,L,R));
    update(p);
    return res;
}
#undef x
#undef mid
#undef add
inline bool add(int x,int y,int k){
    bool res=1;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        addd(1,1,n,dfn[top[x]],dfn[x],k);
        if(ask(1,1,n,1,n)>=3) res=0;
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    if(x!=y){
        addd(1,1,n,dfn[x]+1,dfn[y],k);
        if(ask(1,1,n,1,n)>=3) res=0;
    }
    return res;
}
signed main(){
    int st=clock();
    read(n,m);
    for(rint i=1,u,v;i<n;i++) read(u,v),e[u].pb(v),e[v].pb(u);
    dfs(1,0);ddfn=0;
    dfs1(1,0,1);
    for(rint i=1;i<=m;i++) read(s[i]);
    for(rint i=2;i<=m;i++){
        bool f=add(s[i-1],s[i],1);
        if(!f){for(rint i=1;i<=n;i++) puts("0");return 0;}
    }
    for(rint i=1;i<=n;i++){
        if(i==s[1]) puts("1");
        else{
            bool f=add(i,s[1],1);
            puts(f?"1":"0");
            add(i,s[1],-1);
        }
    }
    return 0;
}

```

---

## 作者：Tairitempest (赞：1)

## [NOISG 2025 Prelim] Itinerary

我们要做的是判断每个城市是否能作为一条欧拉序列的起点，使活动序列是其欧拉序列的子序列。

首先，不考虑其他的结点，仅考虑行程需要经过的结点是不影响巡游的。

把任意一个城市作为树根拎起来，我们可以发现一个性质：一旦我们离开了某个子树，我们就无法再访问这个子树内的点，也就是说如果我们需要离开了某个子树后再次进入这个子树，那么就不存在一条合法序列。

进一步思考：怎么同时处理树上所有的结点？

如果一条边被经过三次及以上，那么一定不合法；因此经过的边的数量不会超过 $2N-2$。

如果一条边被经过两次，因为一棵树的某条边所连接的两个连通块一定只能通过这条边互相到达，因此一定是一次往返。

考虑如何处理一次往返：

![](https://cdn.luogu.com.cn/upload/image_hosting/c4ojuamj.png)

如图所示，这是一个往返，当我们经过一个之前经过的结点的时候，判断一下这一次移动的来源。以这条边把树分为两个连通块，那么来源结点所在连通块的任意一个结点都是不合法的，因为任意一个节点都存在一个离开后再次进入的子树。

每次计算一下 LCA 然后在路径上暴力跑就可以了。复杂度 $O(N \log N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 200010
ll n,m,a[MAXN],S[200010],MOD;
ll top[MAXN],dep[MAXN],fa[MAXN],sz[MAXN],son[MAXN];
vector<ll> e[MAXN];
void dfs1(ll p,ll f){
	dep[p]=dep[f]+1;
	fa[p]=f;
	sz[p]=1;
	for(ll i=0;i<e[p].size();i++){
		ll nxt=e[p][i];
		if(nxt==f) continue;
		dfs1(nxt,p);
		sz[p]+=sz[nxt];
		if(sz[nxt]>sz[son[p]]) son[p]=nxt;
	}
}
void dfs2(ll p,ll tp){
	top[p]=tp;
	if(!son[p]) return;
	dfs2(son[p],tp);
	for(ll i=0;i<e[p].size();i++){
		ll nxt=e[p][i];
		if(nxt==fa[p]||nxt==son[p]) continue;
		dfs2(nxt,nxt);
	}
}
ll lca(ll x,ll y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return x;
}

ll s[200010][2];
bool vis[200010];
void dfs3(ll p,ll f){
	vis[p]=true;
	for(ll i=0;i<e[p].size();i++){
		ll nxt=e[p][i];
		if(nxt==f||vis[nxt]) continue;
		dfs3(nxt,p);
	}
}
void nothing(){
	for(int i=1;i<=n;i++)
		cout<<0<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		ll x,y;
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=m;i++)
		cin>>S[i];
	for(int i=1;i<m;i++){
		ll F=lca(S[i+1],S[i]);
		ll x=S[i],y=S[i+1];
		while(x!=F){
			if(s[x][0]==1){
				nothing();
				return 0;
			}else{
				if(s[x][1]==1) dfs3(x,fa[x]);
				else s[x][0]=1;
			}
			x=fa[x];
		}
		while(y!=F){
			if(s[y][1]==1){
				nothing();
				return 0;
			}else{
				if(s[y][0]==1) dfs3(fa[y],y);
				else s[y][1]=1;
			}
			y=fa[y];
		}
	}
	for(int i=1;i<=n;i++)
		cout<<(1-vis[i])<<endl;
	return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

### 题目大意
给定一棵 $n$ 个点的树和一个点的序列 $s$，要求按顺序访问序列中的所有点，并且树上每条边要被访问**恰好** $2$ 次。问每个点是否能作为起点。
### sol
首先指定 $1$ 为树根，把所有 $s_i\to s_{i+1}(1\le i < m)$ 的路径取出，构成一个极小联通块。我们发现不管怎么走，在事件 $i$ 和 $i+1$ 发生之间，$s_i\to s_{i+1}$ 的最短路径上的边一定都会被访问至少一次，于是我们可以通过树剖计算出每条边至少要被访问几次。如果有任何一条边被访问了 $\ge 3$ 次，那么从任何一个点开始都无法成功构成一个巡游。

然后我们把选择的起点加上，也就是 $S\to s_1$ 的最短路径上所有边都会至少被访问 $1$ 次。很容易发现如果要满足每条边访问不超过 $2$ 次，那么 $S$ 只能从能被 $s_1$ 通过最少访问次数为 $0,1$ 的边遍历到的联通块中选取。

接下来我们来证明此时这个联通块中所有点都能作为起始点。

我们取出 $S\to s_1,s_1\to s_2,\dots,s_{m-1}\to s_m$ 这 $m$ 条路径所构成的联通块，则这个联通块上每条边的最少访问次数均为 $1$ 或 $2$，每个点都至少被遍历了一次。

联通块内每个点 $u$ 第一次遍历到时，都将其不在联通块内的子树全部遍历完成，容易知道这是可行的。而在联通块内，取出 $S\to s_1,s_1\to s_2,\dots,s_{m-1}\to s_m,s_m\to S$ 这 $m+1$ 条路径，容易发现这构成了一个 dfs 序。所以只需要按照这个顺序进行遍历，并在遍历到一个点时处理好其所有不在联通块内的子树即可。

所以只需要：
- 树剖计算出每条边至少要被访问几次。
- 找到能被 $s_1$ 通过最少访问次数为 $0,1$ 的边遍历到的联通块。

答案就是联通块的大小。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>G[200005];
vector<pair<int,int> >E[200005];
struct node{
	int len,w,lz;
}tr[800005];
int n,m,cnt,a[200005],b[200005];
int dis[200005],fa[200005],son[200005],siz[200005],tp[200005],idx[200005],ans[200005];
void dfs1(int u,int f){
	dis[u]=dis[f]+1;
	fa[u]=f,siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==f) continue;
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void pushup(int x){
	tr[x].w=tr[x<<1].w+tr[x<<1|1].w;
}
void Build(int x,int l,int r){
	tr[x].len=r-l+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	Build(x<<1,l,mid);
	Build(x<<1|1,mid+1,r);
	pushup(x);
}
void dfs2(int u,int top){
	idx[u]=++cnt;
	a[cnt]=b[u];
	tp[u]=top;
	if(!son[u]) return ;
	dfs2(son[u],top);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(idx[v])continue;
		dfs2(v,v);
	}
}
void pushdown(int x){
	if(!tr[x].lz) return ;
	tr[x<<1].w=(tr[x<<1].w+tr[x<<1].len*tr[x].lz);
	tr[x<<1|1].w=(tr[x<<1|1].w+tr[x<<1|1].len*tr[x].lz);
	tr[x<<1].lz=(tr[x<<1].lz+tr[x].lz);
	tr[x<<1|1].lz=(tr[x<<1|1].lz+tr[x].lz);
	tr[x].lz=0;
}
void upd(int x,int l,int r,int L,int R,int val){
	if(R<L)return;
	if(L<=l&&r<=R){
		tr[x].w+=tr[x].len*val;
		tr[x].lz+=val;
		return ;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if(L<=mid)upd(x<<1,l,mid,L,R,val);
	if(R>mid)upd(x<<1|1,mid+1,r,L,R,val);
	pushup(x);
}
void TreeAdd(int x,int y){
	while(tp[x]!=tp[y]){
		if(dis[tp[x]]<dis[tp[y]]) swap(x,y);
		upd(1,1,n,idx[tp[x]],idx[x],1);
		x=fa[tp[x]];
	}
	if(dis[x]>dis[y]) swap(x,y);
	upd(1,1,n,idx[x]+1,idx[y],1);
}
void dfs(int u,int f){
	ans[u]=1;
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i].first,w=E[u][i].second;
		if(v==f||w>1)continue;
		dfs(v,u);
	}
}
int query(int x,int l,int r,int ps){
	if(l==r)return tr[x].w;
	pushdown(x);
	int mid=(l+r)>>1,ans=0;
	if(ps<=mid)return query(x<<1,l,mid,ps);
	else return query(x<<1|1,mid+1,r,ps);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	Build(1,1,n);
	cin>>b[1];
	for(int i=2;i<=m;i++){
		cin>>b[i];
		TreeAdd(b[i-1],b[i]);
	}
	for(int i=2;i<=n;i++){
		int w=query(1,1,n,idx[i]);
		if(w>2){
			for(int i=1;i<=n;i++)cout<<"0\n";
			return 0;
		}
		E[fa[i]].push_back({i,w});
		E[i].push_back({fa[i],w});
	}
	dfs(b[1],-1);
	for(int i=1;i<=n;i++)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：SunburstFan (赞：0)

## [P12195 [NOISG 2025 Prelim] Itinerary](https://www.luogu.com.cn/problem/P12195)

### 题目大意

有一个树和一个序列，要求按照给出的顺序访问序列中的所有点，问每个点能否作为起点。

### 解题思路

如果一个方案不合法，当且仅当沿着这个方案中相邻两个点的最短路遍历的时候有一条边被遍历了大于 $2$ 边。

考虑树链剖分，将相邻两点的最短路加入，对于从城市 $i$ 出发，在活动行程的最开始加入 $i$ 到 $s_i$ 的最短路判断最小值是否 $\le 2$。

时间复杂度 $O(N\times \log ^2 N)$。

```cpp
namespace SGT{
    #define int long long
    const int N = 1e5+5;

    #define lson rt<<1,l,md
    #define rson rt<<1|1,md+1,r

    int xds[N<<4],tag[N<<4];

    void push_up(int rt){
        xds[rt]=max(xds[rt<<1],xds[rt<<1|1]);
    }

    void build(int rt,int l,int r){
        if(l==r){
            xds[rt]=a[l];
            return;
        }
        int md=(l+r)>>1;
        build(lson),build(rson);
        push_up(rt);
    }

    void push_down(int rt){
        if(tag[rt]){
            xds[rt<<1]+=tag[rt];
            xds[rt<<1|1]+=tag[rt];
            tag[rt<<1]+=tag[rt];
            tag[rt<<1|1]+=tag[rt];
            tag[rt]=0;
        }
    }

    void update(int rt,int l,int r,int L,int R,int x){
        if(L<=l&&r<=R){
            xds[rt]+=x;
            tag[rt]+=x;
            return;
        }
        push_down(rt);

        int md=(l+r)>>1;
        if(L<=md)update(lson,L,R,x);
        if(R>md)update(rson,L,R,x);
        push_up(rt);
    }

}

namespace sunburstfan{
    const int N=2e5+5;

    int n,m;
    int sz[N],dep[N],fa[N],son[N],top[N],dfn[N],rnk[N],cnt;
    vector<int> G[N];

    void dfs1(int u,int f){
        sz[u]=1,fa[u]=f,dep[u]=dep[f]+1;
        for(int v:G[u]){
            if(v==f)continue;
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]])son[u]=v;
        }
    }

    void dfs2(int u,int t){
        top[u]=t,dfn[u]=++cnt,rnk[cnt]=u;
        if(!son[u])return;
        dfs2(son[u],t);
        for(int v:G[u]){
            if(v==fa[u]||v==son[u])continue;
            dfs2(v,v);
        }
    }

    int LCA(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]])swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

    void update(int u,int v,int k){
        while(top[u]!=top[v]){
            if(dep[top[u]]<dep[top[v]])swap(u,v);
            SGT::update(1,1,n,dfn[top[u]],dfn[u],k);
            u=fa[top[u]];
        }
        if(dep[u]<dep[v])swap(u,v);
        SGT::update(1,1,n,dfn[v]+1,dfn[u],k);
    }
 
    void solve(){
        cin>>n>>m;
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        dfs1(1,0),dfs2(1,1);
        for(int i=1;i<=m;i++){
            cin>>a[i];
        }
        for(int i=1;i<m;i++){
            update(a[i],a[i+1],1);
        }
        for(int i=1;i<=n;i++){
            update(i,a[1],1);
            if(SGT::xds[1]<=2)cout<<1<<"\n";
            else cout<<0<<"\n";
            update(i,a[1],-1);
        }

        return;
    }
}
```

---

