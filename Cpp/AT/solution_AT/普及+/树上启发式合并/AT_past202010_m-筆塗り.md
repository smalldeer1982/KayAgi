# 筆塗り

## 题目描述

给定一棵包含 $N$ 个顶点的树，顶点编号为 $1$ 到 $N$。有 $N-1$ 条边，编号为 $1$ 到 $N-1$，第 $i$ 条边连接顶点 $a_i$ 和顶点 $b_i$，且为无向边。每条边都可以被染上颜色，颜色用 $0$ 到 $10^5$ 之间的整数表示。初始时，所有边的颜色均为 $0$。

对这棵树进行 $Q$ 次操作。第 $i$ 次操作会将顶点 $u_i$ 和顶点 $v_i$ 之间的最短路径上的所有边的颜色覆盖为 $c_i$。

请在 $Q$ 次操作后，输出每条边 $1,2,\ldots,N-1$ 的最终颜色。

## 说明/提示

### 注意

本题在 2020/11/8 18:00 JST 之前禁止讨论。如果有讨论，可能会被要求赔偿。考试结束后可以公开总分和认证等级，但请不要透露解题情况等信息。

### 约束条件

- 所有输入均为整数。
- $2 \leq N \leq 10^5$
- $1 \leq Q \leq 10^5$
- $1 \leq a_i, b_i, u_i, v_i \leq N$
- $u_i \neq v_i$
- $1 \leq c_i \leq 10^5$
- 给定的图为树。

### 样例说明 1

- 初始时，所有边的颜色均为 $0$。
- 第 $1$ 次操作将边 $1$、$2$ 的颜色覆盖为 $10$。
- 第 $2$ 次操作将边 $1$ 的颜色覆盖为 $5$。
- 最终，边 $1,2,3$ 的颜色分别为 $5,10,0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 2
1 3
2 4
2 3 10
1 2 5```

### 输出

```
5
10
0```

## 样例 #2

### 输入

```
10 10
7 2
5 8
8 6
8 3
8 9
9 1
4 8
4 10
8 7
7 5 12773
2 6 74733
1 6 64470
7 2 41311
1 9 39776
4 8 71709
9 1 23551
4 6 29181
3 7 23742
8 4 54686```

### 输出

```
41311
12773
29181
23742
64470
23551
54686
0
23742```

# 题解

## 作者：Flanksy (赞：6)

### 并查集

目前题解区最简单，时间复杂度最优的解法！

题解区怎么都是树剖呢，没有在线查询的话，这道题就存在离线做法。

~~虽然我刚开始也是树剖过的。~~

------------

#### 思路

类似[天天爱跑步](https://www.luogu.com.cn/problem/P1600)，将树上路径 $[x,y]$ 拆成 $[x,\operatorname{lca}(x,y)]$ 和 $[y,\operatorname{lca}(x,y)]$。

从节点 $x$ 和 $y$ 出发不断跳父节点直到遇到 $\operatorname{lca}(x,y)$ 为止就可以访问这条路径，可以发现这和暴力求 $\operatorname{lca}$ 的思路相同。

**所以仅通过跳父节点能够遍历任意树上路径。由于每个节点的父节点唯一，可以使用并查集维护。**

离线所有染色操作，从最后一次操作开始模拟整个染色过程。**由于染色操作会覆盖先前节点的颜色，节点一旦被染色，就不需要再考虑时间更早的操作对它的影响。**


初始化所有节点在并查集中的父亲为自身，对于已经被染色的点，将其在并查集中的父亲设为它的父节点，通过访问节点在并查集中的父亲可以快速找到其**祖先中未被染色的深度最大的节点**，通过判断这个节点的深度和树链上深度最小的节点即 $\operatorname{lca}(x,y)$ 的深度可以判断是否继续进行染色。

最后遍历节点的颜色数组输出即可。

------------

#### 做法

题目要求边染色，通过将边的信息下放到点上来实现点边转换即可，注意由于点边转换 $\operatorname{lca}(x,y)$ 是不应被染色的。

离线所有染色操作，从最后一次操作开始染色。对于每一次染色操作，将树上路径 $[x,y]$ 拆成 $[x,\operatorname{lca}(x,y)]$ 和 $[y,\operatorname{lca}(x,y)]$ 并分别处理。

对于拆出的两条路径，它们最开始的节点是 $x$ 或 $y$，但这个节点可能已经被染色，应当从 $x$ 或 $y$ 在并查集中的父亲开始染色，称这个节点为当前节点。将当前节点染色并在并查集中将其所在的集合合并到其**父节点所在的集合**。

跳到当前节点在**并查集中的父亲**并重复操作，不断跳父亲直到跳到的节点深度小于 $\operatorname{lca}(x,y)$ 的深度为止。

最后遍历所有节点的颜色并输出。

由于是离线解法也可以使用 Tarjan 算法求 $\operatorname{lca}$，但笔者写了倍增。

总体时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Color{int x,y,c;Color(int x=0,int y=0,int c=0):x(x),y(y),c(c){}}a[100005];
int n,m,d[100005],f[100005],ex[100005],ans[100005],s[20][100005];//d:节点深度 f:并查集 s:树上父亲 
vector<pair<int,int> > v[100005];
int ask(int x){return x==f[x] ? x:f[x]=ask(f[x]);}
void dfs(int x,int las){
	d[x]=d[las]+1,s[0][x]=las;
	for(auto i:v[x]) if(i.first!=las){
		ex[i.first]=i.second;//ex:点对应的边编号 
		dfs(i.first,x);
	}
}
int lca(int x,int y){
	if(d[x]<d[y]) swap(x,y);
	for(int i=__lg(d[x]);~i;i--) if(d[s[i][x]]>=d[y]) x=s[i][x];
	if(x==y) return x;
	for(int i=__lg(d[x]);~i;i--) if(s[i][x]!=s[i][y]) x=s[i][x],y=s[i][y];
	return s[0][x];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++){
		static int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back({y,i});
		v[y].push_back({x,i});
	}
	for(int i=1;i<=m;i++){
		static int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		a[i]=Color(x,y,c);
	}
	iota(f+1,f+n+1,1),dfs(1,0);
	for(int i=1;1<<i<=n;i++)
		for(int j=1;j<=n;j++) s[i][j]=s[i-1][s[i-1][j]];
	for(int i=m;i>=1;i--){//从节点x或y开始向根节点方向染色 深度超过lim则停止 
		int lim=d[lca(a[i].x,a[i].y)]+1;//注意lca不应被染色 
		for(int j=ask(a[i].x);d[j]>=lim;j=ask(j)) ans[ex[j]]=a[i].c,f[j]=s[0][j];
		for(int j=ask(a[i].y);d[j]>=lim;j=ask(j)) ans[ex[j]]=a[i].c,f[j]=s[0][j];
	}
	for(int i=1;i<=n-1;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：_anll_ (赞：2)

# 树剖线段树+最近公共祖先

## 题目大意

给你有 $n$ 个点的树，初始状态下每条边被染成颜色 $0$。然后对每条树边进行 $q$ 次染色，从点 $u_i$ 到点 $v_i$ 的树链上的每条树边染成颜色 $c_i$颜色，问你操作完毕后每条边的颜色。

## 大体思路
读完题目，不难发现这题是在树上修改，只不过修改的**是边权而不是点权**。既然是树上修改？~~树剖，启动！~~ 考虑树剖。我们可以把边权演变成点权。众所周知每个子节点只有一个父节点，所以我们可以拿每个子节点存连接它和它的父亲的那条边的边权即可，对于每次询问，修改 $u_i$ 到 $v_i$ 的点权。

但由于我们将边权存到了点权上，所以对于 $u_i$ 和 $v_i$，他们的 LCA 一定是不会被修改的。所以我们还需要再把 LCA 改回来。

于是变成了裸的树剖线段树+最近公共祖先。复制一下板子再浅浅改一下就可以通过了。

这个做法并不难想，但时间复杂度偏高，我也是打完之后和机房神犇交流时才反应过来。但好在这题的时间复杂度有足足四秒，所以可以通过，拿来回顾板子是一个不错的选择。

## 代码展示
~~这么板的题还需要代码吗~~
```cpp
#include<iostream>
#include<map>
#define int long long
using namespace std;
struct Edge{
	int l,nxt;
}edges[200005];
struct Tr{
	int l,r,sum,laz;
}tr[800005];
int n,q,num[100005],tt,head[100005];
int son[100005],dep[100005],fas[100005],siz[100005];
int cnt,id[100005],val[100005],top[100005];
map<int,pair<int,int> >mo;
void add_edge(int f,int l){
	tt+=1;
	edges[tt]={l,head[f]};
	head[f]=tt;
}
void dfs1(int x,int fa){
	fas[x]=fa,siz[x]=1,dep[x]=dep[fa]+1;
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;
		if(l==fa) continue;
		dfs1(l,x);
		siz[x]+=siz[l];
		if(siz[son[x]]<siz[l]) son[x]=l;
	}
}
void dfs2(int x,int t){
	top[x]=t,cnt+=1,id[x]=cnt,val[cnt]=num[x];
	if(!son[x]) return;
	dfs2(son[x],t);
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;
		if(l==son[x]||l==fas[x]) continue;
		dfs2(l,l);
	}
}
void build(int p,int l,int r){
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		return;
	}
	int m=(l+r)/2;
	build(p<<1,l,m);build((p<<1)+1,m+1,r);
}
void pushdown(int p){
	if(!tr[p].laz) return;
	tr[p<<1].laz=tr[p].laz;
	tr[(p<<1)+1].laz=tr[p].laz;
	tr[p<<1].sum=tr[p].laz;
	tr[(p<<1)+1].sum=tr[p].laz;
	tr[p].laz=0;
}
int Find(int p,int l,int r){
	pushdown(p);
	if(l<=tr[p].l&&tr[p].r<=r) return tr[p].sum;
	int m=(tr[p].l+tr[p].r)/2,ok=0;
	if(l<=m) ok+=Find(p<<1,l,r);
	if(m<r) ok+=Find((p<<1)+1,l,r);
	return ok;
}
int Find_tr(int x,int y){
	int ok=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ok+=Find(1,id[top[x]],id[x]);
		x=fas[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ok+=Find(1,id[y],id[x]);
	return ok;
}
void update(int l,int r,int p,int k){
	if(l<=tr[p].l&&tr[p].r<=r){
		tr[p].laz=k;
		tr[p].sum=k;
		return;
	}
	pushdown(p);
	int m=(tr[p].l+tr[p].r)/2;
	if(l<=m) update(l,r,p<<1,k);
	if(m<r) update(l,r,(p<<1)+1,k);
	tr[p].sum=tr[p<<1].sum+tr[(p<<1)+1].sum;
}
void update_tr(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(id[top[x]],id[x],1,k);
		x=fas[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	update(id[y],id[x],1,k);
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fas[x];
	}
	if(dep[x]<dep[y]) return x;
	return y;
}
signed main(){
	int f,l;
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&f,&l);
		add_edge(f,l);
		add_edge(l,f);
		mo[i]={f,l};
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n+n);
	int a,b,c;
	while(q--){
		scanf("%lld%lld%lld",&a,&b,&c);
		int lca=LCA(a,b);
		int awa=Find_tr(lca,lca);
		update_tr(a,b,c);
		update_tr(lca,lca,awa);
		}
	for(int i=1;i<n;i++){
		f=mo[i].first,l=mo[i].second;
		if(fas[f]==l) swap(f,l);
		printf("%lld\n",Find_tr(l,l));
	}
	return 0;
}
```


---

## 作者：Bobi2014 (赞：1)

> 我爱树剖，树剖爱我！

### 前置知识

- [树链剖分](https://oi-wiki.org/graph/hld/)

### 思路

用树链剖分线段树维护每个节点的颜色，本来需要用一个 `tag` 存储颜色的懒标记，因为颜色有可能为 $0$，所以 `tag` 的初始值为 $-1$，但是这道题中不需要存储非叶子节点的颜色，线段树也不需要存储叶子节点的懒标记，所以可以两个合在一起使用，如果为叶子节点，那么颜色初始值为 $0$，否则为 $-1$，`pushdown` 时判断是否为叶子节点，如果不是再下传懒标记。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct node{
    int l,r,col;
} tri[N * 4];
struct edge{
    int u,v;
} e[N];
int n,m,dep[N],fa[N],top[N],pos[N],sz[N],cnt,son[N];
vector<int> g[N];
void build(int u,int f){ // 树链剖分 dfs1
    dep[u] = dep[f] + 1;
    fa[u] = f;
    sz[u] = 1;
    for(auto v : g[u]){
        if(v == f){
            continue;
        }
        build(v,u);
        if(sz[v] > sz[son[u]]){
            son[u] = v;
        }
        sz[u] += sz[v];
    }
}
void func(int u,int tot){ // 树链剖分 dfs2
    top[u] = tot;
    pos[u] = ++cnt;
    if(son[u] != 0){
        func(son[u],tot);
    }
    for(int v : g[u]){
        if(v == fa[u] or v == son[u]){
            continue;
        }
        func(v,v);
    }
}
void build_tri(int p,int l,int r){ // 线段树初始化
    tri[p].l = l;
    tri[p].r = r;
    tri[p].col = -1;
    if(l == r){
        tri[p].col = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build_tri(p << 1,l,mid);
    build_tri(p << 1 | 1,mid + 1,r);
}
void pushdown(int p){ // 线段树懒标记下传
    if(tri[p].l == tri[p].r or tri[p].col == -1){
        return;
    }
    tri[p << 1].col = tri[p << 1 | 1].col = tri[p].col;
    tri[p].col = -1;
}
void update(int p,int l,int r,int col){ // 线段树区间更新
    if(tri[p].l >= l and tri[p].r <= r){
        tri[p].col = col;
        return;
    }
    pushdown(p);
    int mid = (tri[p].l + tri[p].r) >> 1;
    if(l <= mid){
        update(p << 1,l,r,col);
    }
    if(r > mid){
        update(p << 1 | 1,l,r,col);
    }
}
int query(int p,int x){ // 线段树单点查询
    if(tri[p].l == tri[p].r){
        return tri[p].col;
    }
    pushdown(p);
    int mid = (tri[p].l + tri[p].r) >> 1;
    if(x <= mid){
        return query(p << 1,x);
    }else{
        return query(p << 1 | 1,x);
    }
}
void update_path(int x,int y,int k){ // 树链剖分路径更新
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]){
            swap(x,y);
        }
        update(1,pos[top[x]],pos[x],k);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]){
        swap(x,y);
    }
    update(1,pos[x] + 1,pos[y],k);
}
int query_path(int x,int y){ // 树链剖分单点查询
    if(fa[x] == y){
        return query(1,pos[x]);
    }else{
        return query(1,pos[y]);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i < n;i ++){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        e[i] = {u,v};
    }
    build(1,0);
    func(1,1);
    build_tri(1,1,n);
    while(m --){
        int x,y,col;
        cin >> x >> y >> col;
        update_path(x,y,col);
    }
    for(int i = 1;i < n;i ++){
        int x = e[i].u,y = e[i].v;
        cout << query_path(x,y) << '\n';
    }
    return 0;
}
```

---

## 作者：Union_Find (赞：1)

目前最优解，跑了 $95$ 毫秒，第二名 $186$ 毫秒。我没有卡常，一发提交的，所以如果出现了更快的不要找我。

一开始想到的是直接树链剖分。但是发现是区间推平，所以考虑有没有更优的解法。~~主要是因为我懒得写树剖。~~

区间推平最显著的性质就是取决于查询之前最后一次涉及到自己的操作。因为这题查询都在最后，所以我们考虑把操作离线下来。然后为了方便，把 $u \sim v$ 的路径拆成 $u \sim lca$ 和 $v \sim lca$ 两段。

考虑倒着做，这样子答案就是取决于第一次涉及到这条边的操作了。可以暴力从 $u$ 一个个跳到 $lca$，但是这样子就是 $O(n^2)$ 的了。~~那我们前面搞那么多干什么的。~~

注意到因为答案取决于第一次涉及到这条边的操作，所以我们可以直接跳过已经操作过的边。至于如何跳过，我们可以存一下这一段连续的已经操作过的边中深度最小的点，也就是这一些已经操作过的点的根节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/eh41ghk7.png)

存答案的时候边权转点权。如图，红色的点表示已经操作过的点，红色的边表示已经有答案的边。如果我们要修改 $13$ 到 $1$，那么就要按照以下方式。

- $13$，没有答案，进行修改。
- $13 \to 11$，发现 $11$ 已经修改，跳到根节点 $11$ 的父亲节点 $8$。
- $8$ 没有答案，进行修改。
- $13 \to 5$，发现 $5$ 已经修改，跳到根节点 $2$ 的父亲节点 $1$。
- 发现 $1$ 已经是最上面的点了，不能修改，直接退出。

这样子我们就完成了一次修改操作。然后把中间所有的点的根节点都指到最上面的点的下面那个点。

现在只需要找到最上面的那个点，可以使用并查集。

至于时间复杂度，很明显的，每个点最多操作一次，然后作为跳板一次，所以总的时间复杂度是 $O(n)$ 的。求 $LCA$ 的时间复杂度是 $O(n\log n)$ 的，可以使用 Tarjan，但没必要，我是用的是欧拉序。最后总的时间复杂度就是 $O(n\log n + n\alpha(n))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define get(x, y) (dep[x] < dep[y] ? (x) : (y))
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}//666
ll n, m, u, v, lst, tu[N], tv[N], w, lg[N], fa[N], fat[N], cnt, ans[N];
vector <ll> e[N];
il ll find(ll x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
struct Graph{
	ll dep[N], euler[N][35], et, pos[N];
	void dfs(ll u, ll fa){
		euler[++et][0] = u, pos[u] = et, dep[u] = dep[fa] + 1, fat[u] = fa;
		for (int v : e[u]) if (v != fa) dfs(v, u), euler[++et][0] = u;
	}il void init(){
		dfs(1, 1);
		for (int i = 2; i <= et; i++) lg[i] = lg[i >> 1] + 1;
		for (int j = 1; j <= 30; j++) for (int i = 1; i + (1 << (j - 1)) - 1 <= et; i++)
			euler[i][j] = get(euler[i][j - 1], euler[i + (1 << (j - 1))][j - 1]);
	}il ll lca(ll u, ll v){
		ll l = pos[u], r = pos[v];
		if (l > r) swap(l, r);
		ll p = lg[r - l + 1];
		return get(euler[l][p], euler[r - (1 << p) + 1][p]);
	}
}G;
il ll lca(ll u, ll v){return G.lca(u, v);}
struct Q{
	ll u, v, c;
}q[N];
int main(){
	n = rd(), m = rd();
	for (int i = 1; i < n; i++){
		tu[i] = u = rd(), tv[i] = v = rd();
		e[u].push_back(v), e[v].push_back(u);
	}G.init();
	for (int i = 1; i <= m; i++){
		u = rd(), v = rd(), w = rd();
		ll l = lca(u, v);
		q[++cnt] = Q{u, l, w}, q[++cnt] = Q{v, l, w};
	}for (int i = cnt; i >= 1; i--){
		u = q[i].u, v = q[i].v, lst = 0;
//		cout << u << " " << v << ":\n";
		while (G.dep[u] > G.dep[v]){
//			cout << u << '\n';
			if (ans[u]) u = find(u);
			else ans[u] = q[i].c;
			fa[u] = fat[u], lst = u, u = fat[u];
		}if (!ans[fat[lst]]) fa[lst] = lst;
	}for (int i = 1; i < n; i++)
		if (fat[tu[i]] == tv[i]) printf ("%lld\n", ans[tu[i]]);
		else printf ("%lld\n", ans[tv[i]]);
	return 0;
}
```

---

upd : 后来发现可以不使用并查集，直接存每个点的根节点，但是要多跑一边，时间复杂度就是 $O(n\log n)$ 的，跑了 $101$ 毫秒。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define get(x, y) (dep[x] < dep[y] ? (x) : (y))
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n, m, u, v, son, tu[N], tv[N], w, lg[N], rt[N], fat[N], cnt, ans[N];
vector <ll> e[N];
struct Graph{
	ll dep[N], euler[N][35], et, pos[N];
	void dfs(ll u, ll fa){
		euler[++et][0] = u, pos[u] = et, dep[u] = dep[fa] + 1, fat[u] = fa;
		for (int v : e[u]) if (v != fa) dfs(v, u), euler[++et][0] = u;
	}il void init(){
		dfs(1, 1);
		for (int i = 2; i <= et; i++) lg[i] = lg[i >> 1] + 1;
		for (int j = 1; j <= 30; j++) for (int i = 1; i + (1 << (j - 1)) - 1 <= et; i++)
			euler[i][j] = get(euler[i][j - 1], euler[i + (1 << (j - 1))][j - 1]);
	}il ll lca(ll u, ll v){
		ll l = pos[u], r = pos[v];
		if (l > r) swap(l, r);
		ll p = lg[r - l + 1];
		return get(euler[l][p], euler[r - (1 << p) + 1][p]);
	}
}G;
il ll lca(ll u, ll v){return G.lca(u, v);}
struct Q{
	ll u, v, c;
}q[N];
int main(){
	n = rd(), m = rd();
	for (int i = 1; i < n; i++){
		tu[i] = u = rd(), tv[i] = v = rd();
		e[u].push_back(v), e[v].push_back(u);
	}G.init();
	for (int i = 1; i <= m; i++){
		u = rd(), v = rd(), w = rd();
		ll l = lca(u, v);
		q[++cnt] = Q{u, l, w}, q[++cnt] = Q{v, l, w};
	}for (int i = cnt; i >= 1; i--){
		u = q[i].u, v = q[i].v, son = 0;
		while (G.dep[u] > G.dep[v]){
			if (ans[u]) u = rt[u];
			son = u, u = fat[u];
		}if (ans[fat[son]]) son = rt[fat[son]];
		u = q[i].u;
		while (G.dep[u] > G.dep[v]){
			if (ans[u]) u = rt[u];
			else ans[u] = q[i].c;
			rt[u] = son, u = fat[u];
		}
	}for (int i = 1; i < n; i++)
		if (fat[tu[i]] == tv[i]) printf ("%lld\n", ans[tu[i]]);
		else printf ("%lld\n", ans[tv[i]]);
	return 0;
}

```

---

## 作者：_qhbd_ (赞：1)

# 题意
给定一棵有 $n$ 点的树，每条边有一个颜色用 $0$ 到 $10^5$ 之间的数来表示。

最初，每条边的颜色为 $0$。对这棵树进行 $q$ 次操作，每次操作有三个数 $u,v,w$，表示将 $u$ 和 $v$ 之间的简单路径上的边的颜色染成 $w$。

问经过 $m$ 次操作后，每条边的颜色为什么。
# 思路
其实很容易可以想到树剖线段树，我们可以每次给树上 $u,v$ 这条路径上的边直接赋值 $w$，最后直接查询边的颜色就可以了，时间定然是过得去的。

但是问题来了，树剖线段树不是只能够去维护点权，但是题目却是给边赋值，不符合要求啊。

这里，可以把原来的边抽象成点，依次赋值序号，然后把这个新建的点放在原来边的两端点间，然后照常用树剖线段树维护，最后依次输出这些新点权值即可。
# 实现
```cpp
#include<iostream>
#include<vector>
#define mid (l+r>>1)
#define lm (p<<1)
#define rm (p<<1|1) 
#define N 200005
using namespace std;
vector<int> r[N]; 
struct tree{int l,r,val,lz;}tr[N<<2];
int n,q,ID,sfn,fa[N],id[N],dep[N],top[N],siz[N],son[N];
inline void build(int p,int l,int r){
	tr[p]={l,r,0,0};
	if(l==r)return;
	build(lm,l,mid);
	build(rm,mid+1,r);
}inline void uplz(int p,int lz){tr[p].val=lz;tr[p].lz=lz;}
inline void pushdown(int p){if(tr[p].lz)uplz(lm,tr[p].lz),uplz(rm,tr[p].lz),tr[p].lz=0;}
inline void modify(int p,int l,int r,int w){
	if(tr[p].l>r||tr[p].r<l)return;
	if(tr[p].l>=l&&tr[p].r<=r)return uplz(p,w);
	pushdown(p);
	modify(lm,l,r,w);modify(rm,l,r,w);
}inline int query(int p,int l,int r){
	if(tr[p].l>r||tr[p].r<l)return 0;
	if(tr[p].l>=l&&tr[p].r<=r)return tr[p].val;
	pushdown(p);
	return query(lm,l,r)+query(rm,l,r);
}inline void modifyt(int u,int v,int w){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])u^=v,v^=u,u^=v;
		modify(1,id[top[u]],id[u],w);
		u=fa[top[u]];
	}if(dep[u]>dep[v])u^=v,v^=u,u^=v;
	modify(1,id[u],id[v],w);
}inline int queryt(int u,int v){
	int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])u^=v,v^=u,u^=v;
		res+=query(1,id[top[u]],id[u]);
		u=fa[top[u]]; 
	}if(dep[u]>dep[v])u^=v,v^=u,u^=v;
	res+=query(1,id[u],id[v]);
	return res;
}inline void dfs1(int u,int faa){
	dep[u]=dep[faa]+1;siz[u]++;fa[u]=faa;
	for(auto v:r[u])if(v!=faa){
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	} 
}inline void dfs2(int u,int tp){
	top[u]=tp;id[u]=++sfn;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(auto v:r[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
}int main(){
	scanf("%d%d",&n,&q);ID=n;
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);++ID;
		r[u].emplace_back(ID);
		r[ID].emplace_back(u);
		r[v].emplace_back(ID);
		r[ID].emplace_back(v);
	}dfs1(1,1);
	dfs2(1,1);
	build(1,1,n+n);
	for(int i=1,u,v,w;i<=q;i++){
		scanf("%d%d%d",&u,&v,&w);
		modifyt(u,v,w);
	}for(int i=n+1;i<=ID;i++)printf("%d\n",queryt(i,i));
	return 0;
}
```

---

## 作者：Dr_Glitch (赞：1)

# 树链剖分+珂朵莉树
## 题干
给定一颗包含 $N$ 个点的树，树点编号分别为 $1 \sim N$。这颗树有 $N-1$ 条树边，编号分别为 $1 \sim N-1$，其中第 $i$ 条无向边连接点 $a_i$ 和点 $b_i$。现在要对每条树边进行染色，颜色用 $0 \sim 10^5$ 之间的一个整数来表示。一开始，每条边被染成颜色 $0$。

有 $Q$ 次操作，每次操作改变树上一条简单路径上所有边的颜色。问在所有操作结束之后，每条边的颜色情况。
## 分析
- 首先，对于树上简单路径的修改是很明显的树链剖分；
- 其次，维护的是这棵树的**边**而非**节点**，那么我们就需要将边转化为节点来进行操作，之后排除原来树上节点的影响；
- 然后，本题要维护的是边的颜色信息，属于区间推平类型的修改，一般情况下建议使用线段树来维护，但本题时间宽裕，因此建议使用码量更少也相对更好写的珂朵莉树；
- 最后，处理完之后统计答案信息输出即可。

## 关于珂朵莉树的补充（如果您已经会了请直接跳过）
注意：这里并不是为了讲解珂朵莉树而写，只是为了方便一些不了解珂朵莉树的读者大致了解它，以便于理解本题的解法。

简单地说，珂朵莉树是一种暴力结构而非数据结构，是基于 STL 容器中的 set 来实现的。set 在珂朵莉树中的定义如下：
```cpp
struct Node
{
	int l,r;
	mutable int val;
	Node(){}
	Node(int l,int r=0,int val=0):l(l),r(r),val(val){}
	inline bool operator <(const Node &A)const
	{
		return l<A.l;
	}
};
set<Node>s;
```
在珂朵莉树中每个节点维护的是一段**连续的颜色区间**，在 set 中每个节点按区间左端点的大小从小到大排序，表示整个序列的情况。需要注意的是，set 中每个新加入的节点都默认为 `const` 的，所以需要使用 `mutable` 来突破 `const` 的限制，进行修改。

珂朵莉树通过 set 的优秀性质，可以很方便地实现区间推平操作（详见代码部分），建议不会的读者去[起源题](https://www.luogu.com.cn/problem/CF896C)处了解。
## 代码
```cpp
#include<bits/stdc++.h>
#define init read()
using namespace std;
const int N=200005;
int n,q,tot=0,cnt=0;
int First[N],Next[N<<1],to[N<<1];
int dep[N],top[N],seg[N],father[N],rev[N],siz[N],son[N];
int ans[N>>1];
inline int read()
{
	int mmm=0,ff=1;char xx=getchar();
	while((xx<'0'||xx>'9')&&xx!='-')xx=getchar();
	if(xx=='-')ff=-1,xx=getchar();
	while(xx>='0'&&xx<='9')
	mmm=mmm*10+xx-'0',xx=getchar();
	return mmm*ff;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar('0'+x%10);
}
struct ODT //珂朵莉树
{
	struct Node
	{
		int l,r;
		mutable int val; //mutable 用来突破 const 的限制
		Node(){}
		Node(int l,int r=0,int val=0):l(l),r(r),val(val){}
		inline bool operator <(const Node &A)const //按区间左端点进行排序
		{
			return l<A.l;
		}
	};
	set<Node>s;
	inline void build()
	{
		s.insert(Node(1,cnt,0));
	}
	inline set<Node>::iterator split(int pos)
	{
		set<Node>::iterator it=s.lower_bound(Node(pos));
		if(it!=s.end()&&it->l==pos)return it;
		it--;
		if(it->r<pos)return s.end();
		int l=it->l;
		int r=it->r;
		int val=it->val;
		s.erase(it);
		s.insert(Node(l,pos-1,val));
		return s.insert(Node(pos,r,val)).first;
	}
	inline void assign(int l,int r,int c)
	{
		set<Node>::iterator itr=split(r+1),itl=split(l);
		s.erase(itl,itr);
		s.insert(Node(l,r,c));
	}
	inline void get_answer() //统计答案
	{
		for(set<Node>::iterator it=s.begin();it!=s.end();it++)
		{
			for(int i=it->l;i<=it->r;i++)
			{
				if(rev[i]>n) //排除原来节点的影响
				ans[rev[i]-n]=it->val;
			}
		}
	}
};
ODT T;
inline void Add(int u,int v)
{
	Next[++tot]=First[u];
	First[u]=tot;
	to[tot]=v;
}
inline void dfs1(int u,int fa) //树链剖分
{
	father[u]=fa;dep[u]=dep[fa]+1;
	siz[u]=1;son[u]=0;
	for(int i=First[u];i;i=Next[i])
	{
		int v=to[i];if(v==fa)continue;
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
inline void dfs2(int u,int head)
{
	seg[u]=++cnt;rev[cnt]=u;
	top[u]=head;
	if(son[u])dfs2(son[u],head);
	for(int i=First[u];i;i=Next[i])
	{
		int v=to[i];if(v==father[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
inline void update_path(int u,int v,int c) //更新路径上的颜色
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		T.assign(seg[top[u]],seg[u],c);
		u=father[top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	T.assign(seg[v],seg[u],c);
}
int main()
{
	n=init;q=init;
	for(int i=1;i<n;i++)
	{
		int x=init,y=init;
		Add(x,n+i);Add(n+i,x);
		Add(y,n+i);Add(n+i,y);
	}
	dfs1(1,0);dfs2(1,1);
	T.build();
	for(int i=1;i<=q;i++)
	{
		int x=init,y=init,c=init;
		update_path(x,y,c);
	}
	T.get_answer();
	for(int i=1;i<n;i++)write(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：1)

题意：给定一棵树，有 $q$ 次操作，每次将 $u$ 到 $v$ 的简单路径上的边染成颜色 $c$，问最后所有边的颜色。

静态区间染色是简单的，搬到树上只需要树剖即可，由于操作只有染色，我们可以不写线段树而去写 ODT，每次链上染色是 $O(\log n)$ 次序列上的染色，所以复杂度是 $O(q\log^2 n)$。注意将边映射到 dfs 序 $[2,n]$ 的点后，输出时需要转回来。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
template<typename T> inline void chkmin(T &x, const T &y) {
	(x > y) && (x = y);
}
template<typename T> inline void chkmax(T &x, const T &y) {
	(x < y) && (x = y);
}
const int N = 1e5 + 5;
int dfn[N], idx, siz[N], son[N], fa[N], dep[N], top[N], rev[N], n, q, ans[N], _u[N], _v[N];
vector<int> g[N];
struct node {
	int l, r;
	mutable int c;
	node(int _l = -1, int _r = -1, int _c = 0) {
		l = _l, r = _r, c = _c;
	}
	bool operator < (const node &o) const {
		return l < o.l;
	}
};
set<node> s;
typedef set<node>::iterator iter;
inline void dfs1(int u, int rt) {
	fa[u] = rt, siz[u] = 1, dep[u] = dep[rt] + 1;
	for (int v : g[u]) {
		if (v != rt) {
			dfs1(v, u);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]])
				son[u] = v;
		}
	}
}
inline void dfs2(int u, int rt) {
	top[u] = rt, dfn[u] = ++idx, rev[idx] = u;
	if (!son[u])
		return;
	dfs2(son[u], rt);
	for (int v : g[u]) 
		if (v != fa[u] && v != son[u])
			dfs2(v, v);
}
inline iter split(int pos) {
	iter it = s.lower_bound(node(pos));
	if (it != s.end() && it->l == pos)
		return it;
	node t(*--it);
	s.erase(it);
	return (s.insert(node(t.l, pos - 1, t.c)), s.insert(node(pos, t.r, t.c)).first);
}
inline void assign(int l, int r, int c) {
	iter itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(node(l, r, c));
}
inline void modify(int u, int v, int c) {
	while (top[u] != top[v]) {
//		cerr << u <
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		assign(dfn[top[u]], dfn[u], c);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	assign(dfn[u] + 1, dfn[v], c);
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(v), g[v].emplace_back(u);
		_u[i] = u, _v[i] = v;
	}
	dfs1(1, 0);
	dfs2(1, 1);
//	return 0;
	s.insert(node(1, n, 0));
	while (q--) {
		int u, v, c;
		cin >> u >> v >> c;
		modify(u, v, c);
	}
	for (auto [l, r, c] : s) {
		for (int i = l; i <= r; i++)
			ans[rev[i]] = c;
	}
	for (int i = 1; i < n; i++) {
		if (dep[_u[i]] > dep[_v[i]])
			cout << ans[_u[i]] << '\n';
		else
			cout << ans[_v[i]] << '\n';
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目大意

选一段路径染色，问结果。

## 题目分析

注意到对一段路径染色，所以可以树链剖分。

树链剖分的大致过程是这样的：考虑随便找一个点当做根，每次找一个重儿子加入链，其他儿子新开一个链。

其中链上的边叫做重边，不在链上的边是轻边。

考虑当前根所在的子树大小为 $n$，除了根本身是 $n=1$，又因为重儿子走了，其他每个儿子都比它大小小，这样的话，剩下每个子树大小必然减半。

由于每跳一次轻边子树大小减半，我们用 $O(\log n)$ 的链就可以表示一条路径。

我们考虑按照树剖顺序把点排起来，每个链内的点都在一块。

这样就是 $O(\log n)$ 段连续段修改，可以转化为线段树上的若干次区间推平（用珂朵莉树也可以）。

查询最后都单点查一遍就行。

时间复杂度 $O(n\log^2 n)$。

---

## 作者：Scean_Tong (赞：0)

## AT_past202010_m 筆塗り 题解

### 题意
给定一棵树和 $m$ 次操作，每次操作对 $u$ 到 $v$ 的简单路径染色。操作完后求每条边的颜色。

### 思路
树剖板子题，点权转到边权，加一个可以实现区间覆盖的线段树就完了。

如果你不会树剖，请[左转](https://www.luogu.com.cn/problem/P3384)。

如果你不会树剖点权转边权，请[右转](https://www.luogu.com.cn/problem/P3038)。

如果你不会区间覆盖线段树，请[掉头](https://www.luogu.com.cn/problem/P1253)。

代码很好写。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+7; 
int n,m,root;
struct node{
	int to,next;
	int val;
}edge[maxn];
int head[maxn],tot;
int v[maxn];
int uu[maxn],vv[maxn];
void add(int u,int v,int w){
	edge[tot]=(node){v,head[u],w};
	head[u]=tot++;
	edge[tot]=(node){u,head[v],w};
	head[v]=tot++;
}
int fa[maxn],son[maxn],siz[maxn],dep[maxn],top[maxn],w[maxn],dfn[maxn];
int tim;

void dfs1(int u,int f){
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	int maxsize=-1;
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v==f) continue;
		w[v]=edge[i].val;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>maxsize){
			maxsize=siz[v];
			son[u]=v;
		}
	}
}

void dfs2(int u,int t){
	dfn[u]=++tim;
	top[u]=t;
	w[tim]=v[u];
	if(!son[u]) return ;
	dfs2(son[u],t);
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
const int L=0,R=1,inf=1e18;
struct seg {
	int sum;
	int maxx,minn;
	int son[2];
	int addtag,covtag=inf;
}a[maxn<<2];
inline void pushup(int k){
	a[k].sum=a[a[k].son[L]].sum+a[a[k].son[R]].sum;
	a[k].maxx=max(a[a[k].son[L]].maxx,a[a[k].son[R]].maxx);
	a[k].minn=min(a[a[k].son[L]].minn,a[a[k].son[R]].minn);
}
inline void addtag(int k,int l,int r,int val){
	a[k].sum+=(r-l+1)*val;
	a[k].maxx+=val;
	a[k].minn+=val;
	a[k].addtag+=val;
}
inline void covtag(int k,int l,int r,int val){
	a[k].sum=(r-l+1)*val;
	a[k].maxx=val;
	a[k].minn=val;
	a[k].covtag=val;
	a[k].addtag=0;		
}	
int cnt=0,k;
inline void build(int &k,int l,int r){
	k=++cnt;
	if(l==r){
		a[k].sum=v[l];
		a[k].maxx=v[l];
		a[k].minn=v[l];
		a[k].covtag=inf;
		return ;
	}
	int mid=(l+r)>>1;
	build(a[k].son[L],l,mid);
	build(a[k].son[R],mid+1,r);
	pushup(k);
}
inline void pushdown1(int k,int l,int r){
	int mid=(l+r)>>1;
	if(a[k].covtag!=inf){
		covtag(a[k].son[L],l,mid,a[k].covtag);
		covtag(a[k].son[R],mid+1,r,a[k].covtag);
		a[k].covtag=inf;
	}
}
inline void pushdown2(int k,int l,int r){
	int mid=(l+r)>>1;
	if(a[k].addtag!=0){
		pushdown1(k,l,r);
		addtag(a[k].son[L],l,mid,a[k].addtag); 
		addtag(a[k].son[R],mid+1,r,a[k].addtag); 
		a[k].addtag=0;
	}
}
inline void pushdown(int k,int l,int r){
	pushdown1(k,l,r);
	pushdown2(k,l,r);
}
inline void addmodify(int k,int l,int r,int ql,int qr,int val){
	if(ql==l&&qr==r){
		addtag(k,l,r,val);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	if(qr<=mid) addmodify(a[k].son[L],l,mid,ql,qr,val);
	else if(ql>mid) addmodify(a[k].son[R],mid+1,r,ql,qr,val);
	else {
		addmodify(a[k].son[L],l,mid,ql,mid,val);
		addmodify(a[k].son[R],mid+1,r,mid+1,qr,val);
	}
	pushup(k);
} 
inline void covmodify(int k,int l,int r,int ql,int qr,int val){
	if(ql==l&&qr==r){
		covtag(k,l,r,val);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	if(qr<=mid) covmodify(a[k].son[L],l,mid,ql,qr,val);
	else if(ql>mid) covmodify(a[k].son[R],mid+1,r,ql,qr,val);
	else {
		covmodify(a[k].son[L],l,mid,ql,mid,val);
		covmodify(a[k].son[R],mid+1,r,mid+1,qr,val);
	}
	pushup(k);
} 
inline int querysum(int k,int l,int r,int ql,int qr){
	if(ql==l&&qr==r){
		return a[k].sum;
	}
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	if(qr<=mid) return querysum(a[k].son[L],l,mid,ql,qr);
	else if(ql>mid) return querysum(a[k].son[R],mid+1,r,ql,qr);
	else{
		return querysum(a[k].son[L],l,mid,ql,mid)+querysum(a[k].son[R],mid+1,r,mid+1,qr);
	}
}
inline int querymax(int k,int l,int r,int ql,int qr){
	if(ql==l&&qr==r){
		return a[k].maxx;
	}
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	int ret=-inf;
	if(qr<=mid) ret=max(ret,querymax(a[k].son[L],l,mid,ql,qr));
	else if(ql>mid) ret=max(ret,querymax(a[k].son[R],mid+1,r,ql,qr));
	else {
		ret=max(ret,querymax(a[k].son[L],l,mid,ql,mid));
		ret=max(ret,querymax(a[k].son[R],mid+1,r,mid+1,qr));
	}
	return ret;
}
inline int querymin(int k,int l,int r,int ql,int qr){
	if(ql==l&&qr==r){
		return a[k].minn;
	}
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	int ret=inf;
	if(qr<=mid) ret=min(ret,querymin(a[k].son[L],l,mid,ql,qr));
	else if(ql>mid) ret=min(ret,querymin(a[k].son[R],mid+1,r,ql,qr));
	else {
		ret=min(ret,querymin(a[k].son[L],l,mid,ql,mid));
		ret=min(ret,querymin(a[k].son[R],mid+1,r,mid+1,qr));
	}
	return ret;
}
void mlist(int u,int v,int w){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		covmodify(root,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	if(u==v)  return ;
	covmodify(root,1,n,dfn[u]+1,dfn[v],w);
}

int qlist(int x,int y){
	int ret=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ret+=querysum(root,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	if(x==y)  return ret;
	ret+=querysum(root,1,n,dfn[x]+1,dfn[y]);
	return ret;
}
signed main(){
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n-1;i++){
		int u,v,w=0;
		cin>>uu[i]>>vv[i];
		add(uu[i],vv[i],w);
	}
	dfs1(1,1);
	dfs2(1,1);
	build(root,1,n);
	while(m--){
		int u,v,w;
		cin>>u>>v>>w;
		mlist(u,v,w);
	}
	for(int i=1;i<n;i++){
		cout<<qlist(uu[i],vv[i])<<'\n';
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF375D)

# 前置知识

[线段树](https://oi-wiki.org//ds/seg/) | [树链剖分](https://oi-wiki.org/graph/hld/)

# 解法

观察到要维护树上信息，且更改的呈链状，考虑进行树链剖分。

将边权转化成点权，钦定边权给了深度更深的那个点，注意更新时不能更新 $\operatorname{LCA}$。

区间赋值和单点查询用线段树维护即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int nxt,to;
}e[200010];
int head[200010],u[200010],v[200010],c[200010],cc[200010],siz[200010],fa[200010],dep[200010],dfn[200010],son[200010],top[200010],tot=0,cnt=0;
void add(int u,int v)
{
	cnt++;
	e[cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void dfs1(int x,int father)
{
	siz[x]=1;
	fa[x]=father;
	dep[x]=dep[father]+1;
	for(int i=head[x];i!=0;i=e[i].nxt)
	{
		if(e[i].to!=father)
		{
			dfs1(e[i].to,x);
			siz[x]+=siz[e[i].to];
			son[x]=(siz[e[i].to]>siz[son[x]])?e[i].to:son[x];
		}
	}
}
void dfs2(int x,int id)
{
	top[x]=id;
	tot++;
	dfn[x]=tot;
	cc[tot]=c[x];
	if(son[x]!=0)
	{
		dfs2(son[x],id);
		for(int i=head[x];i!=0;i=e[i].nxt)
		{
			if(e[i].to!=fa[x]&&e[i].to!=son[x])
			{
				dfs2(e[i].to,e[i].to);
			}
		}
	}
}
struct SMT
{
	struct SegmentTree
	{
		int l,r,sum,lazy;
	}tree[800010];
	int lson(int x)
	{
		return x*2;
	}
	int rson(int x)
	{
		return x*2+1;
	}
	void build(int rt,int l,int r)
	{
		tree[rt].l=l;
		tree[rt].r=r;
		tree[rt].lazy=-1;
		if(l==r)
		{
			tree[rt].sum=cc[l];
			return;
		}
		int mid=(l+r)/2;
		build(lson(rt),l,mid);
		build(rson(rt),mid+1,r);
	}
	void pushdown(int rt)
	{
		if(tree[rt].lazy!=-1)
		{
			tree[lson(rt)].lazy=tree[rson(rt)].lazy=tree[rt].lazy;
			tree[lson(rt)].sum=tree[rson(rt)].sum=tree[rt].lazy;
			tree[rt].lazy=-1;
		}
	}
	void update(int rt,int x,int y,int val)
	{
		if(x<=tree[rt].l&&tree[rt].r<=y)
		{
			tree[rt].sum=tree[rt].lazy=val;
			return;
		}
		pushdown(rt);
		int mid=(tree[rt].l+tree[rt].r)/2;
		if(x<=mid)
		{
			update(lson(rt),x,y,val);
		}
		if(y>mid)
		{
			update(rson(rt),x,y,val);
		}
	}
	int query(int rt,int pos)
	{
		if(tree[rt].l==tree[rt].r)
		{
			return tree[rt].sum;
		}
		pushdown(rt);
		int mid=(tree[rt].l+tree[rt].r)/2;
		if(pos<=mid)
		{
			return query(lson(rt),pos);
		}
		else
		{
			return query(rson(rt),pos);
		}
	}
}T;
void update1(int u,int v,int val)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]])
		{
			T.update(1,dfn[top[u]],dfn[u],val);
			u=fa[top[u]];
		}
		else
		{
			T.update(1,dfn[top[v]],dfn[v],val);
			v=fa[top[v]];
		}
	}
	if(dep[u]<dep[v])
	{
		T.update(1,dfn[u]+1,dfn[v],val);
	}
	else
	{
		T.update(1,dfn[v]+1,dfn[u],val);
	}
}
int query1(int u)
{
	return T.query(1,dfn[u]);
}
int main()
{
	int n,m,x,y,z,i;
	cin>>n>>m;
	for(i=1;i<=n-1;i++)
	{
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	dfs1(1,0);
	dfs2(1,1);
	T.build(1,1,n);
	for(i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		update1(x,y,z);
	}
	for(i=1;i<=n-1;i++)
	{
		if(dep[u[i]]>dep[v[i]])
		{
			cout<<query1(u[i])<<endl;
		}
		else
		{
			cout<<query1(v[i])<<endl;
		}
	}
	return 0;
}
```

---

## 作者：RayAstRa_ (赞：0)

## 题意

给一颗 $n$ 个点的树与 $p$ 次将 $u,v$ 两点间所有边染色的操作。求操作完后每条边的颜色。（$n,q\leq 10^5$）

## 思路

树上两点间染色，典型的重链剖分问题。（不会重链剖分的看[这里](https://oi-wiki.org/graph/hld/#%E9%87%8D%E9%93%BE%E5%89%96%E5%88%86)）

和模板略有不同之处为维护的是边权而不是点权。由于树上除根外每个点都对应一条边，可以用点权代替边权。由于 $u,v$ 两点的 LCA 对应的边不会被染色，所以在操作时需要避开。

和树链剖分模板不同的细节请看注释。

## 代码

```cpp
#include<bits/stdc++.h>
#define reg int
#define ls (k<<1)
#define rs ((k<<1)+1)
#define mid ((l+r)>>1)
#define tmid ((tl[k]+tr[k])>>1)
using namespace std;
template<class T>inline void read(T &k){
	char c=0;k=0;int t=1;
	while(!isdigit(c)){
		if(c=='-')t=-1;
		c=getchar();
	}
	while(isdigit(c))k=k*10+c-48,c=getchar();
	k*=t;
}
const int N=100005;
int n,u,v,q,c,fae[N],ans[N];
struct edge{
	int to,num;	
};vector<edge>g[N];
//树链剖分预处理部分 
int son[N],siz[N],fa[N],top[N],dep[N],dfn[N],rnk[N],tim;
inline void build(int k,int f,int d,int fr){
	fa[k]=f;dep[k]=d;siz[k]++;
	fae[k]=fr;//记录一个点对应的边 
	for(reg i=0;i<g[k].size();i++){
		int to=g[k][i].to;
		if(to==f)continue;
		build(to,k,d+1,g[k][i].num);
		siz[k]+=siz[to];
		if(siz[to]>siz[son[k]])son[k]=to;
	}
}
inline void divide(int k,int f,int t){
	top[k]=t;dfn[k]=++tim;rnk[tim]=k;
	if(!son[k])return;
	divide(son[k],k,t);
	for(reg i=0;i<g[k].size();i++){
		int to=g[k][i].to;
		if(to==f||to==son[k])continue;
		divide(to,k,to);
	}
}
//线段树部分 
struct sigment_tree{
int tl[8*N],tr[8*N],col[8*N],laz[8*N];
inline void build(int k,int l,int r){
	tl[k]=l;tr[k]=r;
	if(l==r)return;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
inline void lazy(int k,int v){
	col[k]=laz[k]=v;
}
inline void pushdown(int k){
	lazy(ls,laz[k]);
	lazy(rs,laz[k]);
	laz[k]=0;
}
inline void change(int k,int l,int r,int c){
	if(l>r)return;
	if(tl[k]>=l&&tr[k]<=r){
		lazy(k,c);
		return;
	}
	if(laz[k])pushdown(k);
	if(l<=tmid)change(ls,l,r,c);
	if(r>tmid)change(rs,l,r,c);
}
inline int ask(int k,int l){//单点查询 
	if(laz[k])pushdown(k);
	if(tl[k]==l&&tr[k]==l)return col[k];
	if(l<=tmid)return ask(ls,l);
	else return ask(rs,l);
}
}st;
//染色部分 
inline void print(int u,int v,int c){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])//top[u]深度小于top[v]交换 
			swap(u,v);
		st.change(1,dfn[top[u]],dfn[u],c);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])
		swap(u,v);
	st.change(1,dfn[u]+1,dfn[v],c);//dfn[u]+1避免将LCA染色 
}
signed main(){
	read(n);read(q);
	for(reg i=1;i<n;i++){
		read(u);read(v);
		g[u].push_back((edge){v,i});
		g[v].push_back((edge){u,i});
	}
	build(1,1,1,0);
	divide(1,1,1);
	st.build(1,1,n);
	while(q--){
		read(u);read(v);read(c);
		print(u,v,c);
	}
	for(reg i=1;i<=n;i++)//将点权转化为边权 
		ans[fae[i]]=st.ask(1,dfn[i]);
	for(reg i=1;i<n;i++)
		cout<<ans[i]<<endl;
}
```

代码经过防复制处理。

Tip：线段树数组要开八倍。

---

## 作者：2022linzhiyi (赞：0)

# 解法
这是一题树链剖分的模板，甚至比模板还简单，评个绿也差
不多了，唯一不同的就是维护的信息是在边上的，解决方法
也很简单，就是把边的信息放在子节点上。最后用线段树维
护，甚至都不用 pushup。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node {
	int x,y;
};
struct Tree {
	int l,r,change,color;
}tr[N<<2];
map<int,node> maps; // 用map记录第i条边的信息
vector<int> d[N];
int n,q,fa[N],dep[N],siz[N],son[N],cnt,id[N],top[N];
void dfs1(int u,int father,int depth) {
	fa[u]=father; dep[u]=depth; siz[u]=1;
	int len=d[u].size();
	for (int i=0;i<len;i++) {
		int j=d[u][i];
		if (j == fa[u]) continue;
		dfs1(j,u,depth+1);
		if (siz[j] > siz[son[u]]) son[u]=j;
		siz[u] += siz[j];
	}
}
void dfs2(int u,int now_top) {
	id[u]= ++cnt; top[u]=now_top;
	if (!son[u]) return;
	dfs2(son[u],now_top);
	int len=d[u].size();
	for (int i=0;i<len;i++) {
		int j=d[u][i];
		if (j == fa[u] || j == son[u]) continue;
		dfs2(j,j);
	}
}
void pushdown(int u) {
	if (tr[u].change != -1) {
		tr[u<<1].color=tr[u].change;
		tr[u<<1|1].color=tr[u].change;
		tr[u<<1].change=tr[u].change;
		tr[u<<1|1].change=tr[u].change;
		tr[u].change=-1;
	}
}
void build(int u,int l,int r) {
	tr[u]={l,r,-1,0};
	if (l == r) return;
	int mid=l+r>>1;
	build(u<<1,l,mid); build(u<<1|1,mid+1,r);
}
void modify(int u,int l,int r,int c) {
	if (tr[u].l >= l && tr[u].r <= r) {
		tr[u].change=c;
		tr[u].color=c;
	} else {
		pushdown(u);
		if (tr[u<<1].r >= l) modify(u<<1,l,r,c);
		if (tr[u<<1|1].l <= r) modify(u<<1|1,l,r,c);
	}
}
void modify_path(int x,int y,int c) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x,y);
		modify(1,id[top[x]],id[x],c);
		x=fa[top[x]];
	}
	if (dep[x] < dep[y]) swap(x,y);
	modify(1,id[y]+1,id[x],c);
}
int query(int u,int x) {
	if (tr[u].l == tr[u].r) return tr[u].color;
	pushdown(u);
	if (tr[u<<1].r >= x) return query(u<<1,x);
	else return query(u<<1|1,x);
}
int main()
{
	cin >> n >> q;
	for (int i=1;i<n;i++) {
		int x,y;
		cin >> x >> y;
		d[x].push_back(y);
		d[y].push_back(x);
		maps[i]={x,y};
	}
	dfs1(1,1,1);
	dfs2(1,1);
	build(1,1,n);
	while (q --) {
		int x,y,z;
		cin >> x >> y >> z;
		modify_path(x,y,z);
	}
	for (int i=1;i<n;i++) {
		node tmp=maps[i];
		if (tmp.x == fa[tmp.y]) cout<<query(1,id[tmp.y]) << '\n';
		else cout << query(1,id[tmp.x]) << '\n';
	}
	return 0;
}

```


---

## 作者：AlicX (赞：0)

## Solution 

这是一道模板题，观察到数据范围 $n \leq 10^5$ 且题目要求我们修改边权，可以得出这是一道用树链剖分维护的题目。唯一转换的地方就是修改边时，需要将每一条边的值都存在它的儿子上方便更新，又因为此题最终求的是叶子节点，所以我们不用向上传信息。具体细节看代码。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second
#define il inline 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1e5+10; 
int n,m; 
int mp[N];
int siz[N]; 
int a[N],b[N]; 
int h[N],idx=0; 
int id[N],cnt=0; 
int f[N],dep[N]; 
int son[N],top[N];   
struct Edge{
	int to,ne; 
}e[N<<1]; 
struct Node{
	int l,r; 
	int w,add; 
}tr[N<<2]; 
il void add(int u,int v){
	e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il void dfs1(int u,int fa){
	int Max=0; 
	f[u]=fa,siz[u]=1,dep[u]=dep[fa]+1; 
	for(int i=h[u];i!=-1;i=e[i].ne){
		int to=e[i].to; 
		if(to==fa) continue; 
		dfs1(to,u); siz[u]+=siz[to]; 
		if(siz[to]>Max) Max=siz[to],son[u]=to;
	}  
} 
il void dfs2(int u,int fa,int Top){
	top[u]=Top; 
	id[u]=++cnt; mp[cnt]=u; 
	if(!son[u]) return ; 
	dfs2(son[u],u,Top); 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa||to==son[u]) continue ;
		dfs2(to,u,to); 
	} 
} 
il void pushdown(int u){ 
	if(!tr[u].add) return ; 
	tr[u<<1].w=tr[u].add,tr[u<<1|1].w=tr[u].add; 
	tr[u<<1].add=tr[u].add,tr[u<<1|1].add=tr[u].add,tr[u].add=0; 
} 
il void build(int u,int l,int r){ 
	tr[u]={l,r}; 
	if(l==r) return ; 
	int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
} 
il void modify(int u,int l,int r,int w){ 
	if(l<=tr[u].l&&tr[u].r<=r){ 
		tr[u].w=w; tr[u].add=w; 
		return ; 
	} pushdown(u); 
	int mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) modify(u<<1,l,r,w); 
	if(r>mid) modify(u<<1|1,l,r,w); 
} 
il int query(int u,int x){ 
	if(tr[u].l==tr[u].r) return tr[u].w; 
	pushdown(u); int mid=tr[u].l+tr[u].r>>1; 
	if(x<=mid) return query(u<<1,x); return query(u<<1|1,x); 
} 
il void modify_section(int x,int y,int w){ 
	while(top[x]!=top[y]){ 
		if(dep[top[x]]<dep[top[y]]) swap(x,y); 
		modify(1,id[top[x]],id[x],w); 
		x=f[top[x]]; 
	} if(dep[x]<dep[y]) swap(x,y); 
	modify(1,id[y]+1,id[x],w); 
} 
signed main(){ 
	memset(h,-1,sizeof h); 
	cin>>n>>m; 
	for(int i=1;i<n;i++){ 
		cin>>a[i]>>b[i]; 
		add(a[i],b[i]),add(b[i],a[i]); 
	} dfs1(1,0),dfs2(1,0,1); build(1,1,n); 
	while(m--){ 
		int x,y,w; 
		cin>>x>>y>>w; 
		modify_section(x,y,w); 
	} for(int i=1;i<n;i++){ 
		int u=a[i],v=b[i]; 
		if(dep[u]<dep[v]) swap(u,v);
		cout<<query(1,id[u])<<endl; 
	} return 0; 
} 

```


---

