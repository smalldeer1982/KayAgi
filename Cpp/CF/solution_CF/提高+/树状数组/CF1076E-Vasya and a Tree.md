# Vasya and a Tree

## 题目描述

Vasya 有一棵包含 $n$ 个结点的树，根结点为 $1$。初始时，每个结点上的值都是 $0$。

设 $d(i, j)$ 表示结点 $i$ 和结点 $j$ 之间的距离，即从 $i$ 到 $j$ 的最短路径上的边数。我们定义结点 $x$ 的 $k$-子树为满足以下两个条件的所有结点 $y$ 的集合：

- $x$ 是 $y$ 的祖先（每个结点都是自己的祖先）；
- $d(x, y) \le k$。

Vasya 需要你处理 $m$ 个操作。第 $i$ 个操作为三元组 $v_i$、$d_i$ 和 $x_i$。对于每个操作，Vasya 会将 $x_i$ 加到 $v_i$ 的 $d_i$-子树中的每个结点上。

请你在所有操作结束后，输出树上每个结点的最终值。

## 说明/提示

在第一个样例中，初始时各结点的值为 $0, 0, 0, 0, 0$。第一次操作后，结点的值变为 $1, 1, 1, 0, 0$。第二次操作后，结点的值变为 $1, 11, 1, 0, 0$。第三次操作后，结点的值变为 $1, 11, 1, 100, 0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
3
1 1 1
2 0 10
4 10 100
```

### 输出

```
1 11 1 100 0 
```

## 样例 #2

### 输入

```
5
2 3
2 1
5 4
3 4
5
2 0 4
3 10 1
1 2 3
2 3 10
1 1 7
```

### 输出

```
10 24 14 11 11 
```

# 题解

## 作者：VenusM1nT (赞：11)

好多用 BIT 的啊……其实直接差分就行了吧……  
记录每个点的操作，然后从 1 开始遍历，遍历时记录前缀和 $\text{sum}$，对于 $u$ 上的操作 $(d,v)$，先使 $\text{sum}+v$，然后在深度为 $\text{dep} _u+d+1$ 这一层打上标记，遍历到这层时对应处理，最后回溯时把标记去掉即可。  
感觉难度虚高？
```cpp
#include<bits/stdc++.h>
#define MAXN 300005
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Node
{
	int dep,val;
};
int cnt,fst[MAXN],to[MAXN<<1],nxt[MAXN<<1];
int n,q,dep[MAXN],val[MAXN],ans[MAXN];
vector <Node> vec[MAXN];
inl void AddEdge(reg int u,reg int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs(reg int u,reg int pre,reg int sum)
{
	sum+=val[dep[u]];
	for(reg int i=0;i<(int)vec[u].size();i++)
	{
		sum+=vec[u][i].val;
		if(dep[u]+vec[u][i].dep+1<=n) val[dep[u]+vec[u][i].dep+1]-=vec[u][i].val;
	}
	ans[u]=sum;
	for(reg int i=fst[u];i;i=nxt[i])
	{
		reg int v=to[i];
		if(v==pre) continue;
		dep[v]=dep[u]+1;
		Dfs(v,u,sum);
	}
	for(reg int i=0;i<(int)vec[u].size();i++)
	{
		if(dep[u]+vec[u][i].dep+1<=n) val[dep[u]+vec[u][i].dep+1]+=vec[u][i].val;
	}
}
signed main()
{
	scanf("%lld",&n);
	for(reg int i=1;i<n;i++)
	{
		reg int x,y;
		scanf("%lld %lld",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	scanf("%lld",&q);
	for(reg int i=1;i<=q;i++)
	{
		reg int x,y,z;
		scanf("%lld %lld %lld",&x,&y,&z);
		vec[x].push_back((Node){y,z});
	}
	dep[1]=1;
	Dfs(1,0,0);
	for(reg int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：优秀的渣渣禹 (赞：5)

CF1076E Vasya and a Tree

可以把操作离线，每次开始遍历到一个节点，把以它为根的操作加上，结束时把这个点的操作删去。

因为是$dfs$，所以一个点对同一深度的贡献是一定的，可以用树状数组区间加减，求前缀和。

但是因为是$dfs$，完全可以把前缀和传入，就不需要树状数组了。

```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#define LL long long
const int inf = 1e9 + 9;
const int N = 6e5 + 5;
using namespace std;
inline int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
int head[N],to[N],nxt[N],cnt;
void add(int x,int y) {
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
}
int n,m;
struct node {
	int d,x;
	inline node() {}
	inline node(int __d, int __x) :d(__d), x(__x){}
};
vector<node> s[N];
LL c[N],ans[N];
void dfs(int u,int fa,int dep,LL sum) {
	for(auto it = s[u].begin();it != s[u].end();it++) {
		c[dep] += it->x;
		if(dep + it->d + 1 <= n) c[dep + it->d + 1] -= it->x;
	}
	sum += c[dep],ans[u] = sum;
	for(int i = head[u];i;i = nxt[i]) {
		int v = to[i];
		if(v != fa) dfs(v,u,dep + 1,sum);
	}
	for(auto it = s[u].begin();it != s[u].end();it++) {
		c[dep] -= it -> x;
		if(dep + it -> d + 1 <= n) c[dep + it -> d + 1] += it -> x;
	}
}
int main() {
	n = read();
	for(int i = 1;i < n;i++) {
		int x = read(),y = read();
		add(x,y),add(y,x);
	}
	m = read();
	for(int i = 1;i <= m;i++) {
		int v = read(),d = read(),x = read();
		s[v].push_back(node(d,x));
	}
	dfs(1,0,0,0);
	for(int i = 1;i <= n;i++) printf("%lld ", ans[i]);
	return 0;
}
```



---

## 作者：MikukuOvO (赞：3)

考虑将修改离线到树的每一个点上，由于修改具有只与深度有关的性质，我们考虑$dfs$整棵树，维护一个以深度为下标的支持单点加区间查询的数据结构即可，类似线段树分治来加入和撤销。

复杂度$nlogn$

```cpp
const int N=3e5+5;

int n,m,cnt;
int head[N];
ll t[N],ans[N];
struct edge
{
    int to,nxt;
};
edge e[N<<1];
struct node
{
    int d,v;
};
vc<node>s[N];

int lowbit(int x)
{
    return x&-x;
}
void add(int x,int y)
{
    e[++cnt].to=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
void link(int x,int y)
{
    add(x,y),add(y,x);
}
void modify(int x,int z)
{
    while(x<=n) t[x]+=z,x+=lowbit(x);
}
ll query(int x)
{
    ll res=0;
    while(x) res+=t[x],x-=lowbit(x);
    return res;
}
void dfs(int x,int fa,int dep)
{
    for(auto i:s[x]) modify(min(n,i.d+dep),i.v);
    ans[x]=query(n)-query(dep-1);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,x,dep+1);
    }
    for(auto i:s[x]) modify(min(n,i.d+dep),-i.v);
}
int main()
{
    fio();
    gi(n);
    for(int i=1,x,y;i<=n-1;++i) gi(x,y),link(x,y);
    gi(m);
    for(int i=1,v,d,x;i<=m;++i)
    {
        gi(v,d,x);
        s[v].pub({d,x});
    }
    dfs(1,0,1);
    for(int i=1;i<=n;++i) print(ans[i]),pc(' ');
    end();
}
```

---

## 作者：alecli (赞：3)


简要题意就是给定多个操作，每次操作将**与 $u$ 距离小于等于 $k$ 且在 $u$ 子树内的点**点权值加 $x$ ，输出最终各个点的权值。

看这题的时候我先想的是树剖，发现树剖并不好处理两点的距离限制

第二种想法是 $bfs$ 序，想想可能不好处理

于是当时这题成功地没有做出来，我过于菜

考完看了看别人的代码...发现自己智障了...

考虑单独的一个节点 $u$，它的操作影响的都是**在它子树内的与 $u$ 深度差小于等于 $k$** 的节点，那么我们只要维护**当前深度操作总和**就行了（树状数组或线段树），但有一个问题，由于 $u$ 点的操作只影响 $u$ 的子树，其他节点怎么办 ? 我们可以先将所有操作离线，再总体按 $dfs$ 实现：
1. 进入该点
2. 实现该点的所有操作
3. 递归它的子树
4. 撤销操作

这样 $u$ 的操作就不会影响到其他子树上的点了，还有一个好处，我们并不需要修改深度 $dep(u)$~$dep(u)+k$ 而只需修改 $dep(k)$ 最后查询的时候查 $sum(dep(u)$~$sum(max))$就好，因为当查询到这个点时，只有 $u$ 的祖先节点的操作实现了，那么对于任意的 $u$ 的儿子节点，如果它的值有修改，说明这个修改操作是来自 $u$ 的祖先节点的，所以 $u$ 肯定也会被修改  

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x * f;
}
const ll N = 300030;
struct node{
    ll nxt, to;
}edge[N << 1];
ll head[N], num;
void build(ll from, ll to){
    edge[++num].nxt = head[from];
    edge[num].to = to;
    head[from] = num;
}
ll c[N], n, m;
ll lowbit(ll x){ return x & -x; }
void add(ll pos, ll v){
    for(ll i=pos; i<=n; i+=lowbit(i)) c[i] += v;
}
ll query(ll pos){
    ll ans = 0;
    for(ll i=pos; i; i-=lowbit(i)) ans += c[i];
    return ans;
}
vector<ll> val[N], D[N];
ll ans[N];
void dfs(ll u, ll f, ll d){
    for(ll i=0; i<D[u].size(); i++){
        add(min(n, D[u][i] + d), val[u][i]);
    }
    ans[u] = query(n) - query(d - 1);
    for(ll i=head[u]; i; i=edge[i].nxt){
        ll v = edge[i].to;
        if(v == f) continue;
        dfs(v, u, d + 1);
    }
    for(ll i=0; i<D[u].size(); i++){
        add(min(n, D[u][i] + d), -val[u][i]);
    }
}
int main(){
    n = read();
    for(ll i=1; i<=n-1; i++){
        ll u = read(), v = read();
        build(u, v); build(v, u);
    }
    m = read();
    for(ll i=1; i<=m; i++){
        ll u = read(), d = read(), v = read();
        D[u].push_back(d);
        val[u].push_back(v);
    }
    dfs(1, 0, 1);
    for(ll i=1; i<=n; i++){
        cout << ans[i] << " ";
    }
    return 0;
}

```





---

## 作者：lnwhl (赞：1)

离线+树上差分。

## Solution
暴力修改肯定是不行的，但我们可以注意到是统一询问，所以可以离线处理一下，把修改都挂到树上。

从 $1$ 开始 dfs，用一个 $\operatorname{sum}$ 记录前缀和，也就是当前点的答案。对于 $v$ 的每个操作 $(d,x)$，可以差分，把 $\operatorname{sum}$ 加上 $x$，然后在 $\operatorname{dep}_{u}+d+1$ 这一层打一个标记，遍历到的时候减去 $x$，回溯时把标记去掉。然后就可以解决本题了，记得开 $\texttt{long long}$。
## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3e5+5;
struct rec{int dep,val;};
vector<rec>r[maxn];
struct node{int to,nxt;}e[maxn<<1];
int n,q,head[maxn],cnt,dep[maxn];
ll val[maxn],ans[maxn];
void add_edge(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa,ll sum)
{
	sum+=val[dep[u]];
	for(int i=0;i<r[u].size();i++)
	{
		sum+=r[u][i].val;
		if(dep[u]+r[u][i].dep<n)
			val[dep[u]+r[u][i].dep+1]-=r[u][i].val;
	}
	ans[u]=sum;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u,sum);
	}
	for(int i=0;i<r[u].size();i++)
		if(dep[u]+r[u][i].dep<n)
			val[dep[u]+r[u][i].dep+1]+=r[u][i].val;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		add_edge(x,y);add_edge(y,x);
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int v,d,x;scanf("%d%d%d",&v,&d,&x);
		r[v].push_back((rec){d,x});
	}
	dep[1]=1;dfs(1,0,0);
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Stinger (赞：1)

如果只是把 $u$ 的 k-son 全部加上 $x$ 就很好做。

大概思路是维护一些`vector`，第 $i$ 个`vector`按照`dfs`序的 $\text{In}$ 值装下所有深度为 $i$ 的节点。然后设 $dep_i$ 为 $i$ 的深度，所有 $u$ 的 k-son 都在第 $dep_u+k$ 个`vector`中，且 $\text{In}$ 值都在 $[\text{In}_u,\text{Out}_u]$ 中。所以二分查找一下确定 $u$ 的 k-son 在`vector`中对应的区间，那么把 k-son 加 $x$ 就变成了区间加 $x$，由于没有修改只有最后输出单点查询，所以我是直接用的差分树状数组，但这里是我nt了，直接差分完全可以。

那如果把 0-son,1-son...k-son 全部加呢？只需要再差分一遍（树上差分）就行了。最后问题变为把 $u$ 点权加上 $x$，$u$ 的 k+1-son 减去 $x$。最后统计答案统计树上前缀和就可以了（$u$ 的所有祖先（包括自己）的点权总和）。

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define int long long

int c[300005], In[300005], Out[300005], idx[300005], n, cnt;
int s[300005], dep[300005], p[300005];
std::vector<int> G[300005], vec[300005], vec2[300005];
void update(int l, int r, int d) {
	for (int i = l; i <= n; i += (i & ~i + 1)) c[i] += d;
	for (int i = r + 1; i <= n; i += (i & ~i + 1)) c[i] -= d;
}
int query(int x) {
	int sum = 0;
	for (int i = x; i; i -= (i & ~i + 1)) sum += c[i];
	return sum;
}
void dfs(int u, int fa) {
	vec[dep[u] = dep[fa] + 1].push_back(In[u] = ++ cnt);
	vec2[dep[u]].push_back(u);
	for (int v : G[u]) if (v != fa) dfs(v, u);
	Out[u] = cnt;
}
void DFS(int u, int fa) {
	s[u] += query(p[u]);
	for (int v : G[u])
		if (v != fa) s[v] += s[u], DFS(v, u);
}

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i < n; ++ i) {
		int u, v;
		scanf("%lld%lld", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1, -1);
	idx[0] = 1;
	for (int i = 1; vec[i].size(); ++ i) {
		idx[i] = idx[i - 1] + vec[i - 1].size();
		for (int j = 0; j < vec[i].size(); ++ j)
			p[vec2[i][j]] = idx[i] + j;
	}
	int m;
	scanf("%lld", &m);
	for (int i = 1; i <= m; ++ i) {
		int x, d, u, k;
		scanf("%lld%lld%lld", &u, &d, &x);
		s[u] += x, k = dep[u] + d + 1;
		if (n < k || !vec[k].size()) continue;
		int st = std::lower_bound(vec[k].begin(), vec[k].end(), In[u]) - vec[k].begin();
		int ed = std::upper_bound(vec[k].begin(), vec[k].end(), Out[u]) - vec[k].begin() - 1;
		update(idx[k] + st, idx[k] + ed, -x);
	}
	DFS(1, -1);
	for (int i = 1; i <= n; ++ i) printf("%lld ", s[i]);
	return 0;
}
```

---

## 作者：shao0320 (赞：1)

#### CF1076E Vasya and a Tree

~~老年人选手没看到统一询问瞎想了20分钟怎么办？？？~~

由于统一询问，因此其实操作处理的顺序无关紧要，考虑通过$dfs$将其转化到链上。

对于我们当前搜索的这一条链，那么每个节点的操作可以看成是一个区间上的修改，我们只需要对于这一个点求和即可，然后再处理当前点的操作，之后递归处理即可。可以用线段树简单维护。

因为我们的操作只在当前子树生效，因此递归回来的时候要退掉这部分贡献，再来一遍修改把贡献改成负数即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define lowbit(x) x&-x 
#define pb push_back
#define N 300005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
struct node
{
	int v,d,x;
}a[N];
int cmp(node a,node b)
{
	return a.v<b.v;
}
int n,q,ans[N],ll[N],rr[N];
struct Segment_Tree
{
	int ll[N<<2],rr[N<<2],v[N<<2],tag[N<<2];
	void build(int l,int r,int k)
	{
		ll[k]=l;rr[k]=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,k*2);build(mid+1,r,k*2+1);
	}
	void pushdown(int k)
	{
		tag[k*2]+=tag[k];
		v[k*2]+=(rr[k*2]-ll[k*2]+1)*tag[k];
		tag[k*2+1]+=tag[k];
		v[k*2+1]+=(rr[k*2+1]-ll[k*2+1]+1)*tag[k];
		tag[k]=0;
	}
	int query(int l,int r,int k,int x)
	{
		if(l==r)return v[k];
		int mid=(l+r)>>1;pushdown(k);
		if(x<=mid)return query(l,mid,k*2,x);
		else return query(mid+1,r,k*2+1,x);
	}
	void modify(int l,int r,int k,int x,int y,int val)
	{
		if(l>=x&&r<=y){v[k]+=val*(r-l+1);tag[k]+=val;return;}
		int mid=(l+r)>>1;pushdown(k);
		if(x<=mid)modify(l,mid,k*2,x,y,val);
		if(y>mid)modify(mid+1,r,k*2+1,x,y,val);
		v[k]=v[k*2]+v[k*2+1];
	}
}T;
vector<int>G[N];
void dfs(int x,int fa,int dep)
{
	for(int i=ll[x];i<=rr[x];i++)T.modify(1,n,1,dep,dep+a[i].d,a[i].x);
	ans[x]=T.query(1,n,1,dep);int siz=G[x].size();
	for(int i=0;i<siz;i++)if(G[x][i]!=fa)dfs(G[x][i],x,dep+1);
	for(int i=ll[x];i<=rr[x];i++)T.modify(1,n,1,dep,dep+a[i].d,-a[i].x);
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		G[x].pb(y);G[y].pb(x); 
	}
	q=read();
	for(int i=1;i<=q;i++)
	{
		a[i].v=read();
		a[i].d=read();
		a[i].x=read();
	}
	sort(a+1,a+1+q,cmp);
	for(int i=1;i<=q;i++)if(a[i].v!=a[i-1].v)ll[a[i].v]=i,rr[a[i-1].v]=i-1;
	rr[a[q].v]=q;
//	for(int i=1;i<=q;i++)
//	{
//		cout<<a[i].v<<" "<<a[i].d<<" "<<a[i].x<<endl;
//	}
//	puts("!!!!!!!!!!");
//	for(int i=1;i<=n;i++)printf("%d %d\n",ll[i],rr[i]);
	dfs(1,0,1);for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	return 0;
}
```



---

## 作者：GJX_Algorithm (赞：0)

# CF1076E 题解
## 解题思路
- 按照树的深度进行查分。

- 为了保证一个子树的查分不会影响到另一子树，需要在回溯时把查分取消。

- 注意要优化时间，输入时把每个结点的操作用动态数组存起来，搜索时一次全操作完。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
int n, m, x, y, v, d, ans[N], c[N];
struct node
{
    int D, K;
};
vector<node> vt[N];
vector<int> nbr[N];
void dfs(int cur, int fa, int dep, int val)
{
    for (int i = 0; i < vt[cur].size(); i++)
    {
        int k = vt[cur][i].K, d = vt[cur][i].D;
        c[dep] += k;
        c[min(n + 1, dep + d + 1)] -= k; 
    }
    val += c[dep];
    ans[cur] = val;
    for (int i = 0; i < nbr[cur].size(); i++)
    {
        int nxt = nbr[cur][i];
        if (nxt != fa)
        {
            dfs(nxt, cur, dep + 1, val);
        }
    }
    for (int i = 0; i < vt[cur].size(); i++)
    {
        int k = vt[cur][i].K, d = vt[cur][i].D;
        c[dep] -= k;
        c[min(n + 1, dep + d + 1)] += k;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        nbr[x].push_back(y);
        nbr[y].push_back(x);
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> v >> d >> x;
        vt[v].push_back({d, x});
    }
    dfs(1, 0, 1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    return 0;
}
```

---

## 作者：xyzqwq (赞：0)

## 题意

每次给一个点的 $k$ 级子树加上一个数（$k$ 级子树指的是这个点的子树上所有到它的距离不超过 $k$ 的点）

## 题目分析

很板的树上差分。将所有修改离线后，对于每个点 $u$ 处理出对该层的贡献：对于 $u$ 所在的层 $\text{dep} \space u$ 和 $\text{dep} \space u+k$ 间所有为 $u$ 的子树上的点加上一个数，转化成差分即为给 $\text{dep} \space u$ 和 $\text{dep} \space u+k+1$ 层打上标记。当然，回溯的时候需要把这个标记消掉，否则就会重复贡献。递归时记录前缀和即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
vector<int>e[N];
int val[N],Ans[N];
int n,dfn[N],dep[N],tot=0;
struct Node{
	int val,dep;
};
vector<Node>v[N];
void dfs(int x,int fa,int sum){
	sum+=val[dep[x]];
	for(auto it:v[x]){
		sum+=it.val;
		if(dep[x]+it.dep+1<=n) val[dep[x]+it.dep+1]-=it.val;
	}
	Ans[x]=sum;
	for(auto it:e[x]){
		if(it==fa) continue;
		dep[it]=dep[x]+1; 
		dfs(it,x,sum);
	}
	for(auto it:v[x]){
		if(dep[x]+it.dep+1<=n) val[dep[x]+it.dep+1]+=it.val;
	}
}
int s[N],m;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%lld%lld",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u); 
	}
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		int u,d,x;
		scanf("%lld%lld%lld",&u,&d,&x);
		v[u].push_back({x,d});
	}
	dep[1]=1;
	dfs(1,0,0);
	for(int i=1;i<=n;i++) printf("%lld ",Ans[i]);
	return 0;
}
```

---

## 作者：wfc284 (赞：0)

看到子树处理，就有了用 DFS 序乱搞的想法。  
算出 DFS 序的同时顺便算出每一层中每一个结点的时间戳，用 `vector` 记录。  
对于每一个修改操作 $u, k, val$，第一步用 DFS 序上的差分记录一下 $u$ 的子树的修改情况。第二步去掉 $u$ 的所有 $k$ 级后代（这玩意可以用 DFS 序上的二分搞）的子树。  
对于第二步，不能直接暴力修改，要不然复杂度不对。于是再考虑一个差分数组记录第 $dep_u+k$ 层中，哪一些是要被斩掉子树的。最后一起统计即可。  
时间复杂度全在二分上了，$O(n \log n)$。

### Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
#define int long long
using namespace std;
const int N = 3e5+2;

int n, m;
vector<int> g[N];

int dep[N]. dfn[N], num, size[N], rev[N];
vector<int> x[N];
void DFS(int u, int fa) {
	dfn[u] = ++num, rev[num] = u;
	dep[u] = dep[fa] + 1, x[dep[u]].push_back(num);
	size[u] = 1;
	for(re auto v : g[u]) {
		if(v == fa) continue;
		DFS(v, u);
		size[u] += size[v];
	}
}

int diff[N];

vector<int> s[N];
int ans[N];

signed main() {
	cin >> n;
	for(re int i = 1, u, v; i < n; ++i) {
		scanf("%lld%lld", &u, &v);
		g[u].push_back(v), g[v].push_back(u);
	}
	DFS(1, 0);
	for(re int i = 1; i <= n; ++i) s[i].resize(x[i].size() + 1, 0);
	
	cin >> m;
	for(re int i = 1, u, k, val, l, r, curl, curr; i <= m; ++i) {
		scanf("%lld%lld%lld", &u, &k, &val);
		l = dfn[u], r = dfn[u] + size[u] - 1;
		diff[l] += val, diff[r+1] -= val;
		
		int d = min(dep[u] + k, n+1);	//要取min，不然会炸
		if(x[d].empty()) continue;
		curl = lower_bound(x[d].begin(), x[d].end(), l) - x[d].begin();
		curr = upper_bound(x[d].begin(), x[d].end(), r)- x[d].begin() - 1;
		s[d][curl] -= val, s[d][curr+1] += val;	//乱搞
	}
	
	for(re int i = 1; i <= n; ++i)
		for(re int j = 0; j < x[i].size(); ++j) {
			if(j) s[i][j] += s[i][j-1]; 
			int u = rev[x[i][j]];
			int l = dfn[u] + 1, r = dfn[u] + size[u] - 1;
			diff[l] += s[i][j], diff[r+1] -= s[i][j];
		}
	for(re int i = 1; i <= n; ++i) {
		diff[i] += diff[i-1];
		ans[rev[i]] = diff[i];
	}
	for(re int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：0)

提供一个$K\ D\  Tree$

设p的dfs序为$dfn[p]$，其子树内最大的dfs序叫$end[p]$

一次修改就是把满足

$$dfn[p] \leq dfn[q] \leq end[p] \wedge dep[p] \leq dep[q] \leq dep[q]+k$$

的q的点权加

由于是矩形加 所以需要打标记

观察数据范围$n \leq 300000$

然后一波计算$n\sqrt n \leq 164316767$

然后观察到时限$2s$

理论上是能过的，但是考虑到kd树的常数…

所以我们不妨进行标记永久化

最后遍历整棵树，把跟到节点路径的标记和累下来，就实现了标记永久化

不会kdtree的来[这里](https://www.luogu.org/blog/van/qian-tan-pian-xu-wen-ti-yu-k-d-tree)学
```cpp
#include<cstdio>
#include<algorithm>
using std::nth_element;
template<class type>inline const type min(const type &a,const type &b)
{
	return a<b?a:b;
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
typedef long long ll;
const int N=3e5+10,K=2,inf=2147483647;
ll ans[N];
int n,m,head[N],edc,next[N<<1],to[N<<1],dfn[N],end[N],dep[N],dot[N];
inline const void link(int u,int v)
{
	next[++edc]=head[u];to[head[u]=edc]=v;
	next[++edc]=head[v];to[head[v]=edc]=u;
}
inline const void dfs(int p,int fa)
{
	dot[dfn[p]=++*dfn]=p;
	for (int son,i=head[p];i;i=next[i])
		if ((son=to[i])^fa)
			dep[son]=dep[p]+1,
			dfs(son,p);
	end[p]=*dfn;
}
int f;
struct point
{
	int d[K];ll w;
	inline point(){}
	inline point(const int &x,const int &y,const int &w=0):w(w){d[0]=x;d[1]=y;}
	inline const bool operator<(const point &p)const
	{
		return d[f]<p.d[f];
	}
}a[N];
template<const int k,const int maxn>class KD_Tree
{
	private:
		struct tree
		{
			ll add;
			tree *son[2];
			point range,mn,mx;
			inline const void pushup()
			{
				for (int i=0;i<k;i++)
					mn.d[i]=min(range.d[i],min(son[0]->mn.d[i],son[1]->mn.d[i])),
					mx.d[i]=max(range.d[i],max(son[0]->mx.d[i],son[1]->mx.d[i]));
			}
			inline const bool out(const point &lower,const point &upper)
			{
				for (int i=0;i<k;i++)
					if (mn.d[i]>upper.d[i]||mx.d[i]<lower.d[i])
						return 1;
				return 0;
			}
			inline const bool in(const point &lower,const point &upper)
			{
				for (int i=0;i<k;i++)
					if (!(mn.d[i]>=lower.d[i]&&mx.d[i]<=upper.d[i]))
						return 0;
				return 1;
			}
			inline const bool at(const point &lower,const point &upper)
			{
				for (int i=0;i<k;i++)
					if (!(range.d[i]>=lower.d[i]&&range.d[i]<=upper.d[i]))
						return 0;
				return 1;
			}
		}*root,memory_pool[maxn],*null,*tail;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			null->son[0]=null->son[1]=null;
			for (int i=0;i<k;i++)null->mn.d[i]=inf,null->mx.d[i]=-inf;
		}
		inline tree *spawn(const point &x)
		{
			tree *p=tail++;
			p->range=p->mn=p->mx=x;
			p->son[0]=p->son[1]=null;
			return p;
		}
		inline tree *build(int l,int r,int d)
		{
			if (l>r)return null;
			const int mid=l+r>>1;f=d;
			nth_element(a+l,a+mid,a+r+1);
			tree *p=spawn(a[mid]);
			if (l==r)return p;
			p->son[0]=build(l,mid-1,(d+1)%k);
			p->son[1]=build(mid+1,r,(d+1)%k);
			p->pushup();
			return p;
		}
		inline const void add(tree *p,const point &x,const point &y,const int &w)
		{
			if (p==null)return;
			if (p->out(x,y))return;
			if (p->in(x,y))return p->add+=w,void();
			if (p->at(x,y))p->range.w+=w;
			add(p->son[0],x,y,w);add(p->son[1],x,y,w);
		}
		inline const void check(tree *p,ll add)
		{
			if (p==null)return;
			ans[dot[p->range.d[0]]]=p->range.w+(add+=p->add);
			check(p->son[0],add);check(p->son[1],add);
		}
	public:
		inline const void build()
		{
			init();root=build(1,n,0);
		}
		inline const void add(int x1,int y1,int x2,int y2,int w)
		{
			add(root,point(x1,y1),point(x2,y2),w);
		}
		inline const void check()
		{
			check(root,0);
		}
};
KD_Tree<K,N>kdt;
int main()
{
	read(n);
	for (int u,v,i=1;i<n;i++)read(u),read(v),link(u,v);
	dfs(1,0);
	for (int i=1;i<=n;i++)a[i]=point(dfn[i],dep[i]);
	kdt.build();
	read(m);
	for (int u,k,w;m--;)
		read(u),read(k),read(w),
		kdt.add(dfn[u],-inf,end[u],k+dep[u],w);
	kdt.check();
	for (int i=1;i<=n;i++)printf("%lld ",ans[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：Owen_codeisking (赞：0)

好题！

好吧，我把我最初的思路到正解都说一下好了。

首先，我想到了带修主席树 + $BIT$，但是我把这个想法否决掉了。这是 $O(n\log^2 n)$ 的解法，而且好像是错误的。

上个星期做了一些 $K-D\ Tree$ 的题目，我想将这道题目的加法转化成一个矩形的整体加减。我们以 $x$ 轴为 $dfs$ 序，$y$ 轴为深度，我们将矩形 $x$ 轴 $[st_x,ed_x]$，$y$ 轴 $[dep_x,min(dep_x+d,maxdep)]$ 同时加一个 $k$。然后最后查询 $n$ 个点 $(st_x,dep_x)$ 的值，用 $K-D\ Tree$ 维护，最坏复杂度 $O(n\sqrt{n})$

注意到这不是 $Ynoi$，并不卡常，而且是最后查询，所以我们需要另辟蹊径。

二维数点问题在 $x$ 轴和 $y$ 轴都极大的时候怎么办呢？不能用二维线段树，我们可以跑一遍扫描线！

将矩形差分一下，在 $st_x$ 的时候，区间 $[dep_x,min(dep_x+d,maxdep)]$ 加上 $k$，在 $ed_x+1$ 的时候减掉就好了，一遍扫描一遍记录 $ans$

那么发现我们需要维护一个区间修改+单点查询的数据结构，很容易想到树状数组+差分或者线段树。

这道题就做完了，时间复杂度 $O(n\log n)$

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int maxn=300000+10;
int n,m,c[maxn],ans[maxn],maxdep,dep[maxn],st[maxn],ed[maxn],mp[maxn],tim;
int head[maxn],to[maxn<<1],nxt[maxn<<1],tot;

struct Query{
    int l,r,k;
};
vector<Query> in[maxn],out[maxn];

inline void add(int x,int y){
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void update(int x,int y){
    for(;x<=maxdep;x+=lowbit(x)) c[x]+=y;
}
int sum(int x){
    int ans=0;
    for(;x;x-=lowbit(x)) ans+=c[x];
    return ans;
}

void dfs(int x,int f){
    st[x]=++tim;
    mp[tim]=x;
    dep[x]=dep[f]+1;
    maxdep=max(maxdep,dep[x]);
    for(int i=head[x],y;i;i=nxt[i]){
        y=to[i];
        if(y==f) continue;
        dfs(y,x);
    }
    ed[x]=tim;
}

signed main()
{
    scanf("%I64d",&n);
    int x,y;
    for(int i=1;i<n;i++){
        scanf("%I64d%I64d",&x,&y);
        add(x,y);add(y,x);
    }
    dfs(1,0);
    scanf("%I64d",&m);
    int l,r,k;
    for(int i=1;i<=m;i++){
        scanf("%I64d%I64d%I64d",&l,&r,&k);
        in[st[l]].push_back((Query){dep[l],min(dep[l]+r,maxdep),k});
        out[ed[l]+1].push_back((Query){dep[l],min(dep[l]+r,maxdep),k});
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<in[i].size();j++)
            update(in[i][j].l,in[i][j].k),update(in[i][j].r+1,-in[i][j].k);
        for(int j=0;j<out[i].size();j++)
            update(out[i][j].l,-out[i][j].k),update(out[i][j].r+1,out[i][j].k);
        ans[mp[i]]=sum(dep[mp[i]]);
    }
    for(int i=1;i<=n;i++)
        printf("%I64d ",ans[i]);
    printf("\n");
    return 0;
}
```

---

