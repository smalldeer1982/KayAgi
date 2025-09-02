# Mobile Phone Network

## 题目描述

你正在管理一个移动电话网络，并希望为连接网络提供有竞争力的价格。

该网络有 $n$ 个节点。

你的竞争对手已经为部分节点之间提供了一些连接，并设定了固定的价格。这些连接是双向的。最初有 $m$ 条由竞争对手提供的连接。第 $i$ 条连接连接节点 $fa_i$ 和 $fb_i$，费用为 $fw_i$。

你有一份包含 $k$ 条你想要提供的连接的列表。保证这 $k$ 条连接不会形成环。第 $j$ 条连接将连接节点 $ga_j$ 和 $gb_j$。这些连接同样是双向的。这些连接的费用尚未决定。

你可以为这些连接设置任意整数价格。每条连接的价格可以独立设置。设置好价格后，客户会选择 $n-1$ 条连接，使得所有节点连通且总费用最小。如果有多种选择方式，客户会选择其中包含你最多连接数的方案。

你希望设置价格，使得客户选择你所有的 $k$ 条连接，并且你这些连接的价格之和最大。

请输出你能获得的最大利润。如果利润无上界，请输出 $-1$。

## 说明/提示

在第一个样例中，最优做法是将连接 $1-3$ 的费用设为 $3$，连接 $1-2$ 的费用设为 $3$，连接 $3-4$ 的费用设为 $8$。此时，最便宜的连通网络费用为 $14$，且客户会选择包含你所有连接的方案。

在第二个样例中，只要你的第一条连接费用不超过 $30$，客户无论如何都会选择你的两条连接，因此你可以让第二条连接的费用任意大，所以利润无上界。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3 6
1 2
3 4
1 3
2 3 3
3 1 4
1 2 4
4 2 8
4 3 8
4 1 10
```

### 输出

```
14
```

## 样例 #2

### 输入

```
3 2 1
1 2
2 3
1 2 30
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 3 3
1 2
1 3
1 4
4 1 1000000000
4 2 1000000000
4 3 1000000000
```

### 输出

```
3000000000
```

# 题解

## 作者：Mobius127 (赞：9)

~~恶臭树链剖分毁我青春耗我钱财不讲武德。~~

### 题目大意

给出 $k$ 条边权未定的边，以及 $m$ 条边权已定的边，让你求这样一个东西：

1. 有一颗最小生成树包含这 $k$ 条边；

1. 这 $k$ 条边的权值和最大。

最后输出 $k$ 条边的权值和。

既然要求 $k$ 条边都在最小生成树内，那我们不妨先把这 k 条边加入一棵树内。

然后我们对 $m$ 条边按边权排序，从小到大把能加入生成树内的边都加进去。（其实就是补完这颗生成树）

然后我们考虑剩下没加的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/o1iotapi.png)

如上图，红色二边是 $k$ 条边中的两条，蓝色是已加入的边，而黑边则是，未加入的一条黑边。

考虑这条边会对边 $AC$ 和 $AB$ 造成什么影响。

因为我们优先按边权从小到大排了一遍，所以只要红边中的最大值 $\le$ $f_{w_i}$ ，那么蓝边就必定可以加入最小生成树中。

那么每一条黑边其实就变成了对路径的限制。

即 $f_{a_i}$ 到 $f_{b_i}$ 的路径上的边的权值不得超过 $f_{w_i}$ ，这是一个在树上进行区间覆盖的模板，可以用树剖~~轻松~~解决。

还有亿些小问题：

1. 初始的红边要设成一个最大值，这样就易于进行判断是否有解；

1. 蓝边的权值设为 $0$ ，这样就不会影响到最大值的更新。

以上。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define N 500005
using namespace std;
const int INF=1e9+1;
int n, m, k, ans[N];
struct Edge{
	int to, nxt, w;
}d[N*2];
int tot, h[N];
void add(int x, int y, int w){
	d[++tot].to=y, d[tot].nxt=h[x];
	d[tot].w=w, h[x]=tot;
}
struct Tree_chain_partition{
	int val[N], son[N], sum[N], dep[N], fa[N];
	int top[N], toseg[N], back[N], cnt;
	void debug(){
		for(int i=1; i<=n; i++) 
			printf("%d: %d %d %d %d %d %d %d %d\n", i, val[i], son[i], sum[i], dep[i], fa[i], top[i], toseg[i], back[i]);
		for(int i=1; i<=n; i++)
			printf("--%d %d\n", mx[i], tag[i]);
	}
	void dfs_1(int pos, int f){
		sum[pos]=1, dep[pos]=dep[f]+1, fa[pos]=f;
		for(int i=h[pos]; i; i=d[i].nxt){
			int to=d[i].to;
			if(to==f) continue;
			val[to]=d[i].w;
			dfs_1(to, pos);
			sum[pos]+=sum[to];
			if(sum[son[pos]]<sum[to]) son[pos]=to; 
		}
	}
	void dfs_2(int pos, int root){
		toseg[pos]=++cnt, top[pos]=root;
		back[cnt]=pos;
		if(son[pos]) dfs_2(son[pos], root);
		for(int i=h[pos]; i; i=d[i].nxt){
			int to=d[i].to;
			if(top[to]) continue;
			dfs_2(to, to);
		}
	}
	#define ls k<<1
	#define rs k<<1|1
	#define mid (l+r>>1)
	int mx[N*4], tag[N*4];
	void pushup(int k){mx[k]=max(mx[ls], mx[rs]);}
	void upd(int k, int w){mx[k]=w, tag[k]=w;}
	void pushdown(int k){
		if(!tag[k]) return ;
		if(mx[ls]>=tag[k]) upd(ls, tag[k]);
		if(mx[rs]>=tag[k]) upd(rs, tag[k]);
		tag[k]=0;
		return ;
	}
	void build(int k, int l, int r){
		if(l==r){mx[k]=val[back[l&r]];return ;}
		build(ls, l, mid);build(rs, mid+1, r);
		pushup(k);
	}
	void add(int k, int l, int r, int x, int y, int w){
		if(w>mx[k]) return ;
		if(x<=l&&r<=y) return upd(k, w);pushdown(k);
		if(x<=mid) add(ls, l, mid, x, y, w);
		if(mid<y) add(rs, mid+1, r, x, y, w);
		return pushup(k);
	}
	int LCA(int a, int b){
		while(top[a]!=top[b]){
			if(dep[top[a]]<dep[top[b]]) swap(a, b);
			a=fa[top[a]];
		}
		if(dep[a]>dep[b]) return b;
		return a;
	}
	void change(int a, int b, int w){
		while(top[a]!=top[b]){
			if(dep[top[a]]<dep[top[b]]) swap(a, b);
			add(1, 1, n, toseg[top[a]], toseg[a], w);
			a=fa[top[a]];
		}
		if(a==b) return;
		if(dep[a]<dep[b]) swap(a, b);
		add(1, 1, n, toseg[b]+1, toseg[a], w);
	}
	void putall(int k, int l, int r){
		if(l==r){
			ans[back[l&r]]=mx[k];
			return ;
		}pushdown(k);
		putall(ls, l, mid);putall(rs, mid+1, r);
	}
}TCP;
struct F{
	int a, b, w;
	bool in;
	bool operator < (const F &A) const{
		return w<A.w;
	}
}f[N], g[N];
int fs[N];
int find(int x){
	if(x==fs[x]) return x;
	return fs[x]=find(fs[x]);
}
long long ret=0;
int main(){
	scanf("%d%d%d", &n, &k, &m);
	for(int i=1; i<=n; i++) fs[i]=i;
	for(int i=1; i<=k; i++){
		scanf("%d%d", &g[i].a, &g[i].b);
		add(g[i].a, g[i].b, INF), add(g[i].b, g[i].a, INF);
		fs[find(g[i].a)]=find(g[i].b);
	}
	for(int i=1; i<=m; i++)
		scanf("%d%d%d", &f[i].a, &f[i].b, &f[i].w), f[i].in=false;
	sort(f+1, f+m+1);
	for(int i=1; i<=m; i++){
		int fa=find(f[i].a), fb=find(f[i].b);
		if(fa==fb) continue;
		f[i].in=true;
		fs[fa]=fb;
		add(f[i].a, f[i].b, 0);
		add(f[i].b, f[i].a, 0);
	}
	TCP.dfs_1(1, 0);
	TCP.dfs_2(1, 1);TCP.top[1]=TCP.fa[1]=1;
	TCP.build(1, 1, n);
	for(int i=1; i<=m; i++)
		if(!f[i].in){
			int lca=TCP.LCA(f[i].a, f[i].b);
			TCP.change(f[i].a, lca, f[i].w);
			TCP.change(f[i].b, lca, f[i].w);
		}
	TCP.putall(1, 1, n);
	for(int i=1; i<=n; i++){
		if(ans[i]==INF) return printf("-1")*0;
		ret+=(long long)ans[i];
	}
	printf("%lld\n", ret);
	return 0;
}
```


---

## 作者：JK_LOVER (赞：5)

## 题意
给你 $m_1$ 条白边，$m_2$ 条黑边，要求构造一颗最小生成树，要求包含所有白边，求最大可能的白边之和。[qwq](https://www.luogu.com.cn/blog/xzc/solution-cf1023f)
## 分析
如果我们用已知的黑边建一颗最小生成树，那么在加入白边时，树的结构可能会变化（ $LCT$ 等动态树可能可以做），所以我们考虑一开始就把白边的权值作为 $0$ 确定一颗最终的最小生成树。

- 那么考虑白边的最大值。当且仅当一条不在 $MST$ 中的边的两个端点的路径中边的权值大于它的权值时是可以替换的。

- 那么如何维护一颗树上的路径，树链剖分， $LCT$ 。都是不错的选择。这样时间复杂度为 $O(n\log^2n /n \log n)$ 。

- 然而这道题只给了 $256M$ 的空间所以，要有极强的卡空间能力才过得了，可见另一篇题解。而我很可惜没有卡过。

- 考虑优化空间。我们发现对于每一条白边其实我们最多也只会覆盖一次。所以可以用并查集来维护这个过程，不仅优化了空间，也优化了时间，为 $O(n\alpha(n))$。

## 代码

空间过不了的树剖，大家可以参照一下，可能是我实现有点问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 501000;
int n,k,m1,m2;
struct dsu_edge{int x,y,w;}dsu_e[N<<1];
int dsu_fa[N],mst_e[N],mst_top;
bool dsu_cmp(dsu_edge a,dsu_edge b)
{
	return a.w < b.w;
}
int dsu_find(int x)
{
	return x==dsu_fa[x]?x:dsu_fa[x]=dsu_find(dsu_fa[x]);
}
void solve_dsu()
{
	for(int i = 1;i <= m1+m2;i++)
	{
		int a = dsu_e[i].x,b = dsu_e[i].y;
		a = dsu_find(a);
		b = dsu_find(b);
		if(a == b) continue;
		mst_e[i] = 1;
		dsu_fa[a] = b;
	}
}
struct segment_tree{
	int down,up;
}t[N<<1];
vector<int> G[N<<1],W[N<<1];
int top[N],son[N],si[N],d[N],id[N],f[N],map_e[N],seg_val[N],val_node[N],cnt_id = 0;
void build(int x,int l,int r)
{
//	cout<<"l:: "<<l<<" "<<" r:: "<<r<<endl;
	if(l==r) {
		if(l==1) return;
//		cout<<"segval   "<<seg_val[l]<<endl;
		t[x].up = (seg_val[l] == 0);
		t[x].down = 0;
		return;
	}
	int mid = l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x].up = t[x<<1|1].up + t[x<<1].up;
//	cout<<"t[x].up:: "<<t[x].up<<endl;
}
void dfs_dep(int x,int fa,int dep)
{
	d[x] = dep;f[x] = fa;si[x] = 1;
	//cout<<"x:: "<<x<<" fa:: "<<fa<<endl;
	for(int i = 0;i < G[x].size();i++)
	{
		int y = G[x].at(i);
		if(y == fa) continue;
		val_node[y] = W[x].at(i);
		dfs_dep(y,x,dep+1);
		si[x] += si[y];
		if(si[y] > si[son[x]])
		{
			son[x] = y;
		}
	}
}
void dfs_top(int x,int fa,int Top)
{
	//cout<<"x:: "<<x<<"  Top:: "<<Top<<endl;
	id[x] = ++cnt_id;seg_val[cnt_id] = val_node[x];top[x] = Top;
	if(son[x]) dfs_top(son[x],x,Top);
	for(int i = 0;i < G[x].size();i++)
	{
		int y = G[x].at(i);
		if(y == son[x] || y == fa) continue;
		dfs_top(y,x,y);
	}
}
void solve_mst()
{
	for(int i = 1;i <= m1+m2;i++)
	{
		if(mst_e[i])
		{
			//cout<<"mst_e[i]:: "<<i<<endl;
			dsu_edge a = dsu_e[i];
			G[a.x].push_back(a.y);
			G[a.y].push_back(a.x);
			W[a.x].push_back(a.w);
			W[a.y].push_back(a.w);
		}
	}
	dfs_dep(1,0,1);
	dfs_top(1,0,1);
	build(1,1,n);
}
void update(int x)
{
	if(t[x].down)
	{
		t[x<<1|1].down = t[x<<1].down = 1;
		t[x<<1|1].up = t[x<<1].up = 0;
		t[x].down = 0;
	}
	return;
}
void change(int x,int L,int R,int l,int r)
{
	if(r < L || l > R) return;
	if(L <= l && r <= R) {
		t[x].up = 0;
		t[x].down = 1;
		return;
	}
	update(x);
	int mid = l+r>>1;
	change(x<<1,L,R,l,mid);
	change(x<<1|1,L,R,mid+1,r); 
	t[x].up = t[x<<1].up + t[x<<1|1].up;
}
int ask(int x,int L,int R,int l,int r)
{
	if(r < L || l > R) return 0;
	if(L <= l && r <= R) return t[x].up;
	update(x);
	int mid = l+r>>1;
	return ask(x<<1,L,R,l,mid)+ask(x<<1|1,L,R,mid+1,r); 	
}
int work_edge(dsu_edge a)
{
	int x = a.x,y = a.y;
	int res = 0;
	while(top[x] != top[y])
	{
//		cout<<"X:: "<<x<<"  "<<"Y::" <<y<<endl;
		if(d[top[x]] < d[top[y]]) swap(x,y);
		res += ask(1,id[top[x]],id[x],1,n);
		change(1,id[top[x]],id[x],1,n);
		x = f[top[x]];
	}
	if(d[x] > d[y]) swap(x,y);
	res += ask(1,id[x]+1,id[y],1,n);
	change(1,id[x]+1,id[y],1,n);
//	cout<<"res:: "<<res<<endl;
	return res;
}
void solve_ans()
{
	long long ans = 0;
	for(int i = m1+1;i <= m1+m2;i++)
	{
		if(mst_e[i]) continue;
		ans += 1LL*dsu_e[i].w * work_edge(dsu_e[i]);
	}
//	cout<<"ask "<<ask(1,1,n,2,n)<<endl;
	if(ask(1,1,n,2,n) > 0) printf("-1\n");
	else printf("%lld\n",ans);
}
signed main()
{
	n = read();m1 = read();m2 = read();
	for(int i = 1;i <= n;i++) dsu_fa[i] = i;
	for(int i = 1;i <= m1;i++) 
	{
		dsu_e[i].x = read();
		dsu_e[i].y = read();
		dsu_e[i].w = 0;
	}
	for(int i = m1+1;i <= m1+m2;i++)
	{
		dsu_e[i].x = read();
		dsu_e[i].y = read();
		dsu_e[i].w = read();
	}
	sort(dsu_e+1,dsu_e+m1+m2+1,dsu_cmp);
	solve_dsu();
	solve_mst();
	solve_ans();
	return 0;
}
```


可以通过的并查集代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 1110000;
int n,k,m1,m2;
struct dsu_edge{int x,y,w;}dsu_e[N];
int dsu_fa[N],mst_e[N],mst_top;
bool dsu_cmp(dsu_edge a,dsu_edge b)
{
	return a.w < b.w;
}
int dsu_find(int x)
{
	return x==dsu_fa[x]?x:dsu_fa[x]=dsu_find(dsu_fa[x]);
}
void solve_dsu()
{
	for(int i = 1;i <= m1+m2;i++)
	{
		int a = dsu_e[i].x,b = dsu_e[i].y;
		a = dsu_find(a);
		b = dsu_find(b);
		if(a == b) continue;
		mst_e[i] = 1;
		dsu_fa[a] = b;
	}
}
//vector<int> G[N],W[N];
struct MLE{
	int to,nxt,w;
}e[N];
int fuck = 0,head[N];
void add(int x,int y,int w)
{
	e[++fuck].to = y;
	e[fuck].nxt = head[x];
	e[fuck].w = w;
	head[x] = fuck;
}
void solve_mst()
{
	for(int i = 1;i <= m1+m2;i++)
	{
		if(mst_e[i])
		{
			//cout<<"mst_e[i]:: "<<i<<endl;
			dsu_edge a = dsu_e[i];
			add(a.x,a.y,a.w);
			add(a.y,a.x,a.w);
//			G[a.x].push_back(a.y);
//			G[a.y].push_back(a.x);
//			W[a.x].push_back(a.w);
//			W[a.y].push_back(a.w);
		}
	}
}
int f[N],d[N],cost[N];
void dfs(int x,int fa,int dep)
{
	f[x] = fa;d[x] = dep;
	for(int i = head[x];i;i = e[i].nxt)
	{
		int y = e[i].to;
		if(y == fa)continue;
		cost[y] = e[i].w;
		dfs(y,x,dep+1);
	}
}
signed main()
{
	n = read();m1 = read();m2 = read();
	for(int i = 1;i <= n;i++) dsu_fa[i] = i;
	for(int i = 1;i <= m1;i++) 
	{
		dsu_e[i].x = read();
		dsu_e[i].y = read();
		dsu_e[i].w = 0;
	}
	for(int i = m1+1;i <= m1+m2;i++)
	{
		dsu_e[i].x = read();
		dsu_e[i].y = read();
		dsu_e[i].w = read();
	}
	sort(dsu_e+1,dsu_e+m1+m2+1,dsu_cmp);
	solve_dsu();
	solve_mst();
	dfs(1,0,1);
	long long num = 0,ans = 0;
	for(int i = 1;i <= n;i++) dsu_fa[i] = i;
	for(int i = m1+1;i <= m1+m2;i++)
	{
		if(mst_e[i]) continue;
		int a = dsu_find(dsu_e[i].x),b = dsu_find(dsu_e[i].y),c = dsu_e[i].w;
		while(a != b)
		{
			if(d[a]<d[b]) swap(a,b);
			if(cost[a] <= 0) ans += c,num++;
			//cout<<c<<endl;
			int fa = dsu_find(f[a]);
			dsu_fa[a] = fa;
			a = dsu_find(a); 
		}
	}
	if(num < m1) ans=-1;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：wcyQwQ (赞：4)

典题。因为 $k$ 条边都要在最终的生成树里面，所以我们不妨直接把它们放进一棵树里，然后对剩下的边用 kruscal 的方式补全，不难发现在这棵树里面的边不会对答案造成影响，而对于剩下的边 $(u, v, w)$，生成树上 $u \rightarrow v$ 路径上的边的边权一定要小于等于 $w$，于是树剖区间覆盖即可。

时间复杂度 $O(n\log^2 n)$。[Code](https://codeforces.com/contest/1023/submission/209240873)

---

## 作者：Endt (赞：3)

# Mobile Phone Network-题解

### 题意

给定 $k$ 条边权不定的边与 $m$ 边权确定的边，让 $k$ 条边在最小生成树中并最大化 $k$ 条边。

### 解法

既然要让 $k$ 条边在最小生成树内，那先将这些边加入这棵树，再用 Kruskal 让 $m$ 条边补全生成树。对于剩下的非树边，令端点为 $x$ 和 $y$ 边权为 $w$，根据最小生成树的性质，生成树上 $x$ 到 $y$ 的路径边权都不能超过 $w$，否则其中的一条边应由这条非树边代替。

问题转化为给多条树上路径与值 $w$，使得每条路径上所有边的权值不超过 $w$。树剖显然可以解决，但时空均劣，容易被卡掉。

可以让 $w$ 递增，那么每条边最多会更新最小值一次，用并查集维护已经更新的部分，时间复杂度可降到近似 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Pub  public
#define  rand  Rand
std::mt19937 rand(time(0));

using std::min;using std::max;
using std::swap;
const Int INF=1000000000000000;

int n,k,m;
std::map<std::pair<int,int>,bool> h;

int RD(){
    int x=0;char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c<='9'&&c>='0')x=(x<<3)+(x<<1)+c-'0',c=getchar();
    return x;
}
class Node{
Pub:std::vector<int> s;int fa;
    int dp;
}a[500005];

Int t[2000005];


void dfs(int x){
    if(h.find({x,a[x].fa})==h.end()&&h.find({a[x].fa,x})==h.end())t[x]=0;
    a[x].dp=a[a[x].fa].dp+1;
    for(int i:a[x].s){
        if(i==a[x].fa)continue;
        a[i].fa=x;
        dfs(i);
    }
}

class Edge{
Pub:int x,y;
    Int z;
    bool f;
}e[500005];
int fa[500005];
int fin(int x){
    if(fa[x]!=x)fa[x]=fin(fa[x]);
    return fa[x];
}
int FA[500005];
int FIN(int x){
    if(FA[x]!=x)FA[x]=FIN(FA[x]);
    return FA[x];
}
int main(){
    scanf("%d%d%d",&n,&k,&m);
    for(int i=1;i<=n;++i)fa[i]=FA[i]=i;
    for(int i=1,x,y;i<=k;++i){
        x=RD(),y=RD();
        fa[fin(x)]=fin(y);
        a[x].s.emplace_back(y);
        a[y].s.emplace_back(x);
        h[{x,y}]=1;
    }
    for(int i=1;i<=m;++i)e[i].x=RD(),e[i].y=RD(),e[i].z=RD();
    for(int i=1;i<=m;++i){
        if(fin(e[i].x)!=fin(e[i].y)){
            fa[fin(e[i].x)]=fin(e[i].y);
            a[e[i].x].s.emplace_back(e[i].y);
            a[e[i].y].s.emplace_back(e[i].x);
            e[i].f=1;
        }
    }
    std::fill(t,t+2000005,INF);
    
    dfs(1);
    for(int i=1;i<=m;++i){
        if(e[i].f==0){
            int x=e[i].x,y=e[i].y;
            while(x!=y){
                x=FIN(x),y=FIN(y);
                if(x==y)break;
                if(a[x].dp<a[y].dp)swap(x,y);
                t[x]=min(t[x],e[i].z);
                FA[x]=FIN(a[x].fa);
            }
        }
    }
    Int ans=0;
    for(int i=1;i<=n;++i)ans=min(INF,t[i]+ans);
    if(ans==INF)printf("-1");
    else printf("%lld",ans);
    
    return 0;
}
```

---

## 作者：FreeTimeLove (赞：3)

## 一、题意

给定一个 $n$ 个点、$m$ 条边的无向带权图，令额外给定 $k$ 条边，求保证这 $k$ 条边能**同时**存在于此图的**其中**一棵最小生成树（MST）中的情况下**边权和的最大值**。如果存在一条边的权可以设为无穷大，输出 $-1$。

## 二、思路

好题。

最显然的想法是我们先建出原图的 MST ，然后依次查询 $k$ 条边两点在 MST 上的路径上的最大值 $\max$，然后将这条边设为 $\max$，并将原边权赋值为 $0$。

但是这样是**错误**的，因为两点之间的最大边可能恰恰是之前新增的边，这样不能保证割掉的是最大边；但若割新边，则不符合题意，也不易处理。

转换角度，我们先保证这 $k$ 条边一定在 MST 中，在求 MST 时钦定这 $k$ 条边为 $0$，构建出 MST；然后树链剖分，初始化新边的权为 $+\infty$，用**不在** MST 中的边对 MST 中的边权进行约束，即此边两点在 MST 的路径上的边权都应**不大于**此边边权。区间取 $\min$ 即可。

最后我们可以查询每个节点的值，如果有 $+\infty$ 就输出 $-1$，否则输出和。

（这里区间取 $\min$ 用普通线段树即可，但查询每个节点常数较大，被卡常了。因此我用吉司机线段树区间取 $\min$、维护区间和）

### AC code

```cpp
//written_by_FTL
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#define ll long long
#define LD long double
#define i7 __int128
#define re return
using namespace std;
const int N=5e5+5;
int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,m,k,u,v,bk[N<<1];
ll sum,INF=0x3f3f3f3f,a[N];
int nd[N],tt=1;
struct xxs{
	int u,v,w;
	bool operator <(const xxs x)const{
		re w<x.w;
	}
}g[N<<1];
struct edge{
	int v;ll w;int nxt;
}e[N<<1];
void add(int u,int v,int w){
	e[++tt]={v,w,nd[u]};
	nd[u]=tt;
}
namespace kru{
	int f[N];
	int gtf(int x){
		if(f[x]==x)re x;
		re f[x]=gtf(f[x]);
	}
	void sol(){
		sort(g+1,g+k+m+1);
		for(int i=1;i<=n;i++)f[i]=i;
		int tot=0;
		for(int i=1;i<=k+m;i++){
			u=gtf(g[i].u),v=gtf(g[i].v);
			if(u==v)continue;
			f[u]=v,sum+=g[i].w,bk[i]=1;
			add(g[i].u,g[i].v,g[i].w?g[i].w:INF),add(g[i].v,g[i].u,g[i].w?g[i].w:INF);
			if(++tot==n-1)break;
		}
	}
}
int f[N],siz[N],d[N],sn[N];
int dfn[N],rk[N],tp[N],num;
namespace SGT{//吉司机线段树
	#define vl v<<1
	#define vr v<<1|1
	#define t d[v]
	#define tl d[vl]
	#define tr d[vr]
	#define z lz[v]
	#define zl lz[vl]
	#define zr lz[vr]
	#define mid ((l+r)>>1)
	struct data{
		int l,r;int mx,x,c;ll s;
	}d[N<<2];
	void pu(int v){
		t.s=tl.s+tr.s;
		if(tl.mx>tr.mx)t.mx=tl.mx,t.c=tl.c,t.x=tl.x>tr.mx?tl.x:tr.mx;
		else{
			if(tl.mx<tr.mx)t.mx=tr.mx,t.c=tr.c,t.x=tl.mx>tr.x?tl.mx:tr.x;
			else t.mx=tl.mx,t.c=tl.c+tr.c,t.x=tl.x>tr.x?tl.x:tr.x;
		}
	}
	void chg(int v,int k){
		if(t.mx<=k)re;
		t.s-=(ll)t.c*(t.mx-k);
		t.mx=k;
	}
	void pd(int v){
		chg(vl,t.mx),chg(vr,t.mx);
	}
	void bd(int l,int r,int v){
		t.l=l,t.r=r,t.x=0;
		if(l==r){
			t.s=t.mx=a[rk[l]],t.c=1;
			re;
		}
		bd(l,mid,vl),bd(mid+1,r,vr);
		pu(v);
	} 
	ll qry(int l,int r,int v){
		if(t.l>=l&&t.r<=r)re t.s;
		pd(v);
		re (tl.r>=l?qry(l,r,vl):0)+(tr.l<=r?qry(l,r,vr):0);
	}
	void ud(int l,int r,int v,int k){
		if(t.mx<=k)re;
		if(t.l>=l&&t.r<=r&&t.x<k){chg(v,k);re;}
		pd(v);
		if(tl.r>=l)ud(l,r,vl,k);
		if(tr.l<=r)ud(l,r,vr,k);
		pu(v);
	}
	#undef  t
	#undef  mid
}
namespace HCS{//树链剖分
	void dfs1(int u,int fa){
		f[u]=fa,siz[u]=1;
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==f[u])continue;
			d[v]=d[u]+1,dfs1(v,u),siz[u]+=siz[v];
			if(siz[v]>siz[sn[u]])sn[u]=v;
		}
	}
	void dfs2(int u,int t){
		dfn[u]=++num,rk[num]=u,tp[u]=t;
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==sn[u]){dfs2(v,t),a[v]=e[i].w;break;}
		}
		for(int i=nd[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==f[u]||v==sn[u])continue;
			dfs2(v,v),a[v]=e[i].w;
		}
	}
	void ud(int u,int v,int w){
		while(tp[u]!=tp[v]){
			if(d[tp[u]]<d[tp[v]])swap(u,v);
			SGT::ud(dfn[tp[u]],dfn[u],1,w),u=f[tp[u]];
		}
		if(d[u]>d[v])swap(u,v);
		if(u!=v)SGT::ud(dfn[u]+1,dfn[v],1,w);
	}
}
int main(){
	n=rd(),k=rd(),m=rd();
	for(int i=1;i<=k;i++){
		u=rd(),v=rd();
		g[i]={u,v,0};
	}
	for(int i=1;i<=m;i++){
		u=rd(),v=rd();
		g[i+k]={u,v,rd()};
	}
	kru::sol();//MST
	HCS::dfs1(1,0),HCS::dfs2(1,1),SGT::bd(1,n,1);
	for(int i=k+1;i<=k+(m);i++){
		if(bk[i])continue;
		HCS::ud(g[i].u,g[i].v,g[i].w);
	}
	ll ans=SGT::d[1].s,x=SGT::d[1].mx;
	printf("%lld\n",(x==INF)?-1:ans-sum);
	re 0;
}
```

### $\text{The End.}$

---

## 作者：cyhzz (赞：3)

1.考虑令k条无权边权值为0，建出最小生成树。

2.将最小生成树中的无权边权值设为INF，有权边权值设为0，将最小生成树树链剖分

3.然后对于每一条没有包含在最小生成树中的带权边(u,v,d)，我们需要让最小生成树上(u,v)这条路径上的所有边权值对d取min

4.答案就是最小生成树的权值和
```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int MAXN=1110000;
const int INF=1e15;
int n,m,k;
int ans[MAXN];
int f[MAXN],X[MAXN],Y[MAXN],D[MAXN],book[MAXN];
int tot,front[MAXN],to[MAXN],nxt[MAXN],di[MAXN];
int fa[MAXN],dep[MAXN],siz[MAXN],son[MAXN],top[MAXN],w[MAXN],totw,b[MAXN];
int data[MAXN],maxn[MAXN*4],flag[MAXN*4];
void init(int u,int v,int d)
{
	to[++tot]=v;
	nxt[tot]=front[u];
	di[tot]=d;
	front[u]=tot;
}
int find(int x)
{
	if(f[x]!=x)f[x]=find(f[x]);
	return f[x];
}
void dfs(int u,int father)
{
	fa[u]=father;
	dep[u]=dep[father]+1;
	siz[u]=1;
	for(int i=front[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa[u])continue;
		data[v]=di[i];
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}
}
void dfs(int u)
{
	if(son[u])
	{
		w[son[u]]=++totw;
		top[son[u]]=top[u];
		b[totw]=son[u];
		dfs(son[u]);
	}
	for(int i=front[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa[u]||v==son[u])continue;
		w[v]=++totw;
		top[v]=v;
		b[totw]=v;
		dfs(v);
	}
}
void build(int root,int l,int r)
{
	if(l==r)
	{
		maxn[root]=data[b[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	maxn[root]=max(maxn[root*2],maxn[root*2+1]);
}
void pushdown(int root)
{
	if(flag[root]<=maxn[root*2])
		maxn[root*2]=flag[root],flag[root*2]=flag[root];
	if(flag[root]<=maxn[root*2+1])
		maxn[root*2+1]=flag[root],flag[root*2+1]=flag[root];
	flag[root]=0;
}
void chg(int root,int l,int r,int xl,int xr,int d)
{
	if(d>maxn[root])return;
	if(l==xl&&r==xr)
	{
		maxn[root]=d;
		flag[root]=d;
		return;
	}
	if(flag[root])pushdown(root);
	int mid=(l+r)>>1;
	if(xr<=mid)chg(root*2,l,mid,xl,xr,d);
	else
		if(xl>mid)chg(root*2+1,mid+1,r,xl,xr,d);
		else	
		{
			chg(root*2,l,mid,xl,mid,d);
			chg(root*2+1,mid+1,r,mid+1,xr,d);
		}
	maxn[root]=max(maxn[root*2],maxn[root*2+1]);
}
void change(int u,int v,int d)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		chg(1,1,n,w[top[u]],w[u],d);
		u=fa[top[u]];
	}
	if(u==v)return;
	if(dep[u]<dep[v])swap(u,v);
	chg(1,1,n,w[v]+1,w[u],d);
}
int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])return v;
	return u;
}
void check(int root,int l,int r)
{
	if(l==r)
	{
		ans[b[l]]=maxn[root];
		return;
	}
	if(flag[root])pushdown(root);
	int mid=(l+r)>>1;
	check(root*2,l,mid);
	check(root*2+1,mid+1,r);
}
signed main()
{
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	scanf("%I64d%I64d%I64d",&n,&k,&m);
	for(int i=1;i<=n;i++)f[i]=i;
	int cnt=0;
	for(int i=1,x,y;i<=k;i++)
	{
		scanf("%I64d%I64d",&x,&y);
		if(find(x)!=find(y))
		{
			f[find(x)]=find(y);
			init(x,y,INF);
			init(y,x,INF);
			cnt++;
		}
	}
	int ans2=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld",&X[i],&Y[i],&D[i]);
		if(find(X[i])!=find(Y[i]))
		{
			f[find(X[i])]=find(Y[i]);
			init(X[i],Y[i],0);
			init(Y[i],X[i],0);
			cnt++;
			book[i]=1;
		}
	}
	dfs(1,0);
	w[1]=++totw;
	top[1]=1;
	b[totw]=1;
	dfs(1);
	build(1,1,n);
	for(int i=1;i<=m;i++)
		if(!book[i])
		{
			int tmp=lca(X[i],Y[i]);
			change(X[i],tmp,D[i]);
			change(Y[i],tmp,D[i]);
		}
	check(1,1,n);
	for(int i=1;i<=n;i++)
	{
		if(ans[i]==INF)
		{
			printf("-1");
			return 0;
		}
		ans[i]+=ans[i-1];
	}
	printf("%I64d",ans[n]-ans2);
	return 0;
}

```

---

## 作者：喵仔牛奶 (赞：1)

## Solution

- 首先，题目给定 $k$ 条边肯定要选，接下来考虑对手的 $m$ 条边中那些会被选。那么可以构造生成树，把 $k$ 条边先在生成树上连起来，然后用剩下 $m$ 条边按权值从小到大补全该生成树，这样使用的 $m$ 条边权值是最小的。
- 对于没有被选中的边，我们需要选择保证自己的 $k$ 条边比它们优。对于一条没有选择的连接 $(u,v)$ 的边，它不会被选中仅当生成树 $u\to v$ 路径上任意一条边的权值都不大于它。原因很显然，因为如果有比它大的，直接把比它大的那条边删掉换成它就更优了。
- 我们初始把 $k$ 条边价格都设为 $\infty$，对于没有选择的 $(u,v)$ 权值为 $w$ 的边，生成树 $u\to v$ 上每条边的权值都对 $w$ 取 $\min$。这样才能保证每条边都 $\leq w$。
- 把没有选择的边权值从大到小排序，这样取 $\min$ 就成了覆盖，问题就变成了维护数据结构来支持树上链覆盖。可以使用树链剖分把问题放到序列上，然后使用颜色段均摊或线段树维护皆可。
- 最后将 $k$ 条边的权值相加即为答案，不要忘记判断无解。

一些细节：

- 颜色段均摊常数过大，无法通过。测评记录：<https://codeforces.com/contest/1023/submission/199081289>
- 由于只有最后的单点查询，线段树可以只维护区间修改的 `tag`，注意最后没有 `tag` 的即为 $\infty$，输出无解即可。

时间复杂度 $\mathcal{O}(m\log^2n)$。

## $\mathcal{}Code$

树链剖分，[1.76s](https://www.luogu.com.cn/record/105880084)。

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
	char buf[1 << 23], *p1 = buf, *p2 = buf;
#define getchar() \
	(p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
	inline int read() {
	    register int sr = 0;
	    register char ch = getchar(), last;
	    while (ch < '0' || ch > '9') last = ch, ch = getchar();
	    while (ch >= '0' && ch <= '9') sr = (sr << 1) + (sr << 3) + (ch ^ 48), ch = getchar();
	    return last == '-' ? -sr : sr;
	}
}
namespace Milkcat {
	using namespace FastIO;
	typedef long long LL;
	const int N = 1e6 + 5, inf = INT_MAX;
	struct edge {
		int u, v, w;
		bool operator < (const edge& x) const {
			return w < x.w;
		}
	} e[N], qwq[N];
	int n, m, k, f[N], a[N];
	vector<edge> t;
	LL ans;
	int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
	void merge(int u, int v) {
		int fu = find(u), fv = find(v);
		if (fu != fv) f[fv] = fu;
	}
	struct SegmentTree {
	    LL tag[N << 1];
	    inline int ls(int p) { return p << 1; }
	    inline int rs(int p) { return p << 1 | 1; }
	    void push_down(int p, int l, int r) {
	        if (tag[p]) tag[ls(p)] = tag[p], tag[rs(p)] = tag[p], tag[p] = 0;
	    }
	    void modify(int p, int l, int r, int nl, int nr, LL k) {
	        if (nl <= l && r <= nr) { tag[p] = k; return; }
	        push_down(p, l, r);
	        int mid = (l + r) >> 1;
	        if (nl <= mid) modify(ls(p), l, mid, nl, nr, k);
	        if (nr > mid) modify(rs(p), mid + 1, r, nl, nr, k);
	    }
	    LL query(int p, int l, int r, int t) {
	        if (l == r) return tag[p];
	        push_down(p, l, r);
	        int mid = (l + r) >> 1;
	        if (t <= mid) return query(ls(p), l, mid, t);
	        if (t > mid) return query(rs(p), mid + 1, r, t);
	    }
	} Sgt;
	struct TreeDecom {
		struct edge {
			int next, to;
		} e[N << 1];
		int tot, cnt, head[N], depth[N], fa[N], siz[N], son[N], top[N], id[N];
		void Add(int u, int v) {
			e[++ cnt].to = v;
			e[cnt].next = head[u];
			head[u] = cnt;
		}
		void add(int u, int v) {
			Add(u, v), Add(v, u);
		}
		void dfs1(int u, int fat) {
			fa[u] = fat, siz[u] = 1, depth[u] = depth[fa[u]] + 1;
			for (int i = head[u]; i; i = e[i].next) {
				int v = e[i].to;
				if (v == fa[u]) continue;
				dfs1(v, u), siz[u] += siz[v];
				if (!son[u] || siz[v] > siz[son[u]])
					son[u] = v;
			}
		}
		void dfs2(int u, int topf) {
			top[u] = topf, id[u] = ++ tot;
			if (son[u]) dfs2(son[u], topf);
			for (int i = head[u]; i; i = e[i].next) {
				int v = e[i].to;
				if (v == fa[u] || v == son[u]) continue;
				dfs2(v, v);
			}
		}
		void updRange(int u, int v, int k) {
			while (top[u] != top[v]) {
				if (depth[top[u]] < depth[top[v]]) swap(u, v);
				Sgt.modify(1, 1, n, id[top[u]], id[u], k), u = fa[top[u]];
			}
			if (depth[u] > depth[v]) swap(u, v);
			if (id[u] < id[v]) Sgt.modify(1, 1, n, id[u] + 1, id[v], k);
		}
	} T;
	int main() {
		n = read(), k = read(), m = read();
		for (int i = 1; i <= n; i ++) f[i] = i;
		for (int i = 1; i <= k; i ++) {
			qwq[i].u = read(), qwq[i].v = read();
			merge(qwq[i].u, qwq[i].v), T.add(qwq[i].u, qwq[i].v);
		}
		for (int i = 1; i <= m; i ++) e[i].u = read(), e[i].v = read(), e[i].w = read();
		sort(e + 1, e + 1 + m);
		for (int i = 1; i <= m; i ++) {
			int fu = find(e[i].u), fv = find(e[i].v);
			if (fu != fv) merge(e[i].u, e[i].v), T.add(e[i].u, e[i].v);
			else t.push_back(e[i]);
		}
		T.dfs1(1, 0), T.dfs2(1, 1);
		reverse(t.begin(), t.end());
		for (edge pwp : t) T.updRange(pwp.u, pwp.v, pwp.w);
		for (int i = 1; i <= k; i ++) {
			if (T.depth[qwq[i].u] < T.depth[qwq[i].v]) swap(qwq[i].u, qwq[i].v);
			int res = Sgt.query(1, 1, n, T.id[qwq[i].u]);
			if (!res) puts("-1"), exit(0);
			ans += res;
		}
		printf("%lld\n", ans);
		return 0;
	}
}
int main() {
	return Milkcat::main();
}

```


---

## 作者：Reunite (赞：0)

这题一看就很最小生成树的意思，因为 $k$ 条边必须在里面，直接钦定加入。剩下来一些有限制的边，按照边权从小到大的顺序依次尝试加入，如果能加，则说明一定在最小生成树上，否则一定不在。

现在我们有一些限制边，他们没能加入到最小生成树上，说明他们 $\ge$ 树链上所有边的边权。我们只需倒序用折线边做树链覆盖即可，因为每条边最多被覆盖一次，复杂度后面可以做到线性。瓶颈在排序。

---

## 作者：User_Authorized (赞：0)

## 题意
给出 $n$ 个点，$k$ 条未钦定边权的边和 $m$ 条已钦定边权的边，要求为这 $k$ 条未指定边权的边分配权值使其均在图的最小生成树中且最大化这 $k$ 条边的边权之和。

（$1 \le n,k,m \le 5 \times 10^5$）。

## 题解
**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1023F.html)**

首先满足要求这 $k$ 条边均在最小生成树中，考虑将这 $k$ 条边的权值置为极小值后建立最小生成树。然后考虑最大化边权之和。

此时需要考虑的是非树边对树边边权的限制，若有一条非树边 $\left(a, b\right)$，边权为 $w$，那么可以得出在最小生成树上的路径 $a \rightarrow b$ 上的边边权均要满足不大于 $w$，否则其将被非树边 $\left(a, b\right)$ 替代。

发现这一过程为树链取最小值，使用树链剖分即可。如果存在未指定边权的边在处理完所有限制后没有限制到，输出 $-1$ 即可。在 $n,m,k$ 同阶的情况下总复杂度为 $\mathcal{O}(n \log^2 n)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MAX = INT_MAX >> 1;

class DSU {
private:
    valueType N;

    std::vector<int> father, size;

public:
    explicit DSU(valueType n) : N(n), father(N, 0), size(N, 0) {
        std::iota(father.begin(), father.end(), 0);

        std::fill(size.begin(), size.end(), 1);
    }

    void resize(valueType n) {
        N = n;

        father.resize(N, 0);
        size.resize(N);

        std::iota(father.begin(), father.end(), 0);

        std::fill(size.begin(), size.end(), 1);
    }

    int find(int x) {
        return father[x] == x ? x : father[x] = find(father[x]);
    }

    void unite(int x, int y) {
        x = find(x), y = find(y);

        if (x == y) return;

        if (size[x] < size[y]) std::swap(x, y);

        father[y] = x;
        size[x] += size[y];
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    valueType count(valueType n) {
        return size[find(n)];
    }
};

class Tree {
public:
    typedef ValueVector container;

private:
    valueType N;

    container data;

    void push(valueType id) {
        if (data[id] != MAX) {
            data[id << 1] = std::min(data[id << 1], data[id]);
            data[id << 1 | 1] = std::min(data[id << 1 | 1], data[id]);
            data[id] = MAX;
        }
    }

public:
    explicit Tree(valueType n) : N(n), data((N << 2) + 10, MAX) {}

    void resize(valueType n) {
        N = n;

        data.resize((N << 2) + 10, MAX);
    }

    void update(valueType l, valueType r, valueType key) {
        if (l > r)
            return;

        update(1, 1, N, l, r, key);
    }

    container ans() {
        container result(N + 1, MAX);

        query(1, 1, N, result);

        return result;
    }

private:
    void update(valueType id, valueType nodeL, valueType nodeR, valueType queryL, valueType queryR, valueType key) {
        if (queryL <= nodeL && nodeR <= queryR) {
            data[id] = std::min(data[id], key);

            return;
        }

        valueType const mid = (nodeL + nodeR) >> 1;

        push(id);

        if (queryL <= mid)
            update(id << 1, nodeL, mid, queryL, queryR, key);

        if (queryR > mid)
            update(id << 1 | 1, mid + 1, nodeR, queryL, queryR, key);
    }

    void query(valueType id, valueType l, valueType r, container &result) {
        if (l == r) {
            result[l] = data[id];

            return;
        }

        valueType const mid = (l + r) >> 1;

        push(id);

        query(id << 1, l, mid, result);
        query(id << 1 | 1, mid + 1, r, result);
    }
};

struct Edge {
    valueType from, to, weight;

    bool tag;

    Edge(valueType from, valueType to, valueType weight, bool tag) : from(from), to(to), weight(weight), tag(tag) {}

    bool operator<(Edge const &obj) const {
        return weight < obj.weight;
    }
};

typedef std::vector<Edge> EdgeVector;

valueType N, K, M;
ValueVector dfn, father, depth, size, son, top;
ValueMatrix G;
Tree tree(N + 1);

void dfs(valueType x, valueType from) {
    father[x] = from;
    depth[x] = depth[from] + 1;
    size[x] = 1;

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        dfs(iter, x);

        size[x] += size[iter];

        if (son[x] == 0 || size[iter] > size[son[x]])
            son[x] = iter;
    }
}

valueType dfsCount = 0;

void build(valueType x, valueType from, valueType TOP) {
    dfn[x] = ++dfsCount;
    top[x] = TOP;

    if (son[x] == 0)
        return;

    build(son[x], x, TOP);

    for (auto const &iter: G[x]) {
        if (iter == from || iter == son[x])
            continue;

        build(iter, x, iter);
    }
}

void modify(valueType x, valueType y, valueType key) {
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]])
            std::swap(x, y);

        tree.update(dfn[top[x]], dfn[x], key);

        x = father[top[x]];
    }

    if (depth[x] > depth[y])
        std::swap(x, y);

    tree.update(dfn[x] + 1, dfn[y], key);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

//#ifndef LOCAL_STDIO
//    freopen("trade.in", "r", stdin);
//    freopen("trade.out", "w", stdout);
//#endif

    std::cin >> N >> K >> M;

    G.resize(N + 1);
    dfn.resize(N + 1);
    father.resize(N + 1);
    depth.resize(N + 1);
    size.resize(N + 1);
    son.resize(N + 1);
    top.resize(N + 1);
    tree.resize(N + 1);

    EdgeVector edge;

    edge.reserve(K + M);

    for (valueType i = 0; i < K; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        edge.emplace_back(u, v, 0, true);
    }

    for (valueType i = 0; i < M; ++i) {
        valueType u, v, w;

        std::cin >> u >> v >> w;

        edge.emplace_back(u, v, w, false);
    }

    std::sort(edge.begin() + K, edge.end());

    EdgeVector treeEdge, remainEdge;

    treeEdge.reserve(N);
    remainEdge.reserve(K + M);

    DSU dsu(N + 1);

    for (auto const &iter: edge) {
        if (dsu.connected(iter.from, iter.to)) {
            remainEdge.push_back(iter);
        } else {
            dsu.unite(iter.from, iter.to);
            treeEdge.push_back(iter);

            G[iter.from].emplace_back(iter.to);
            G[iter.to].emplace_back(iter.from);
        }
    }

    ValueVector root;

    for (valueType i = 1; i <= N; ++i) {
        if (dfn[i] == 0) {
            dfs(i, 0);
            build(i, 0, i);
            root.push_back(i);
        }
    }

    for (auto const &iter: root)
        tree.update(dfn[iter], dfn[iter], 0);

    for (auto &iter: treeEdge) {
        if (!iter.tag) {
            if (depth[iter.from] > depth[iter.to])
                std::swap(iter.from, iter.to);

            tree.update(dfn[iter.to], dfn[iter.to], 0);
        }
    }

    for (auto const &iter: remainEdge) {
        modify(iter.from, iter.to, iter.weight);
    }

    auto const &result = tree.ans();

    long long ans = 0;
    
    for (valueType i = 1; i <= N; ++i) {
        if (result[dfn[i]] == MAX) {
            std::cout << -1 << std::endl;

            std::exit(0);
        }

        ans += result[dfn[i]];
    }

    std::cout << ans << std::endl;

    std::exit(0);
}
```

---

