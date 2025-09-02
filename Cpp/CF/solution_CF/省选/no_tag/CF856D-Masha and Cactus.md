# Masha and Cactus

## 题目描述

Masha is fond of cacti. When she was a little girl, she decided to plant a tree. Now Masha wants to make a nice cactus out of her tree.

Recall that tree is a connected undirected graph that has no cycles. Cactus is a connected undirected graph such that each vertex belongs to at most one cycle.

Masha has some additional edges that she can add to a tree. For each edge she knows which vertices it would connect and the beauty of this edge. Masha can add some of these edges to the graph if the resulting graph is a cactus. Beauty of the resulting cactus is sum of beauties of all added edges.

Help Masha find out what maximum beauty of the resulting cactus she can achieve.

## 样例 #1

### 输入

```
7 3
1 1 2 2 3 3
4 5 1
6 7 1
2 3 1
```

### 输出

```
2
```

# 题解

## 作者：reyik (赞：7)

有趣的题

发现他要最终的图是一个$cactus$,即每一个点最多在一个环中，我们可以理解成对于每一条可以加的边，是一条$x$到$y$的路径，因为加了这条边就会让这条路径上的所有点处在这个环上

于是问题转化成，让多个路径覆盖这个树，每一个点最多被覆盖一次，使权值和最大

考虑$dp$,$f_i$表示$i$子树内的答案

分两种情况

情况$1:$ 不选这个点，即$f_i=f_j$之和，$j$是$i$的直接孩子。

情况$2:$ 选这个点，枚举哪一个路径，只用考虑$lca$为$i$的路径，其实就是树上挖掉这个路径让剩下的答案最大，假设路径的端点为$x$,$y$那么显然就是路径上的点的不在路径相邻点的$f_i$之和，转化一下，假设$g(i)$表示$f_j$之和$j$是$i$的孩子减去$f_i$，那么答案就是$x$到$i$的$gi$和+$y$到$i$的$gi$和+这条边的权值+$f_j$的和$j$是$i$的孩子

考虑用数据结构优化，显然他的答案就是这个点到$i$点路径上所有数的$f_j$之和减去$f_k$,$k$为当前点在路径上的儿子，这样就是一个单点修改，链查询，链查询要树剖，我们考虑转化

我们枚举完一个点，就会对所有他的子树内的点产生一定的贡献，贡献就是上面的$f_j$之和减去$f_k$,$k$为当前点在路径上的儿子，那么变成了子树加法，单点查询，我们可以用维护dfs序转化成区间加，单点查询，差分后树状数组维护即可

```cpp

#include <bits/stdc++.h>
using namespace std;
const int N=200005;
struct edge {
  int to,nxt;
}e[N<<1];
int head[N],m,n,u[N],v[N],st[N],ed[N],dfn=0,f[N],dp[N][21],val[N],t[N<<2],dep[N];
vector<int> vec[N];
int cnt=0;
void addedge(int x,int y) {
  ++cnt;
  e[cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
int lowbit(int x) {return x&(-x);}
void add(int x,int y) {
  for (;x<=n;x+=lowbit(x)) t[x]+=y;
}
int query(int x) {
  int ret=0;
  for (;x;x-=lowbit(x)) ret+=t[x];
  return ret;
}
void dfs(int x,int fa) {
  ++dfn;
  st[x]=dfn;dp[x][0]=fa;
  for (int i=head[x];~i;i=e[i].nxt) {
    int v1=e[i].to;
    if(v1==fa) continue;
    dep[v1]=dep[x]+1;
    dfs(v1,x);
  }
  ed[x]=dfn;
}
void init() {
  for (int j=1;j<=20;++j) {
    for (int i=1;i<=n;++i) dp[i][j]=dp[dp[i][j-1]][j-1];
  }
}
int lca(int x,int y) {
  if(dep[x]<dep[y]) swap(x,y);
  int delt=dep[x]-dep[y];
  for (int i=0;i<=20;++i) if(delt&(1<<i)) x=dp[x][i];
  if(x==y) return x;
  for (int i=20;i>=0;--i) {
    if(dp[x][i]!=dp[y][i]) {
      x=dp[x][i];
      y=dp[y][i];
    }
  }
  return dp[x][0];
}
void dfs1(int x,int fa) {
  int ret=0;
  for (int i=head[x];~i;i=e[i].nxt) {
    int v1=e[i].to;
    if(v1==fa) continue;
    dfs1(v1,x);
    ret+=f[v1];
  }
  f[x]=ret;
  for (int i=0;i<vec[x].size();++i) {
    int x1=u[vec[x][i]],y=v[vec[x][i]];
    f[x]=max(f[x],query(st[x1])+query(st[y])+val[vec[x][i]]+ret);
  }
  add(st[x],ret-f[x]);
  add(ed[x]+1,f[x]-ret);
  return ;
}

int main() {
  memset(head,-1,sizeof(head));
  scanf("%d%d",&n,&m);
  for (int i=2;i<=n;++i) {
    int x;
    scanf("%d",&x);
    addedge(x,i);
    addedge(i,x);
  }
  dfs(1,0);
  init();
  for (int i=1;i<=m;++i) {
    scanf("%d%d%d",&u[i],&v[i],&val[i]);
    int lc=lca(u[i],v[i]);
    vec[lc].push_back(i);
  }
  dfs1(1,0);
  printf("%d\n",f[1]);
  return 0;
}

```

---

## 作者：chenxumin1017 (赞：5)

## 闲话

省选联考第一次切题，写篇题解纪念一下。

## 思路

设 $dp_{i}$ 表示在 $i$ 的子树内的答案。

首先有一个很显然的转移，就是 $dp_{i}$ 等于他所有儿子的 $dp$ 值之和。 

然后我们可以讨论对于另外 $m$ 条边会产生怎样的转移。

以样例中 $2$ 和 $3$ 的这条边为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/8wan3o2r.png)

如图，加入这条边只会对 $1, 2, 3$ 也就是 $2$ 和 $3$ 的简单路径上的点造成影响， 由于我们的状态是 $i$ 的子树内的答案，所以对于可以加入的每条边我们在它的两个端点的最近公共祖先处进行处理。

再来看个复杂点的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wlpu1d28.png)

加入 $3, 8$ 这条边，不会影响到 $4, 6, 5, 7$ 这四个点的子树。

经过上面的手玩我们就可以找到转移了。

设这条边两个端点分别为 $u, v$，边权为 $w$，$u, v$ 的最近公共祖先为 $x$，$sum_{i}$ 表示 $i$ 的儿子结点的 $dp$ 值之和。

则 $dp_{x}$ 等于 $u$ 到 $v$ 这条路径上的所有节点 $sum$ 之和加上 $w$，再减去 $u$ 到 $v$ 这条路径上除 $x$ 以外的节点的 $dp$ 之和。

然后用重链剖分优化转移就可以做到 $O(N \log^2 N)$，但是常数很小，比大部分 $O(N \log N)$ 跑得还要快。

## 代码


```cpp
#include<bits/stdc++.h>
// #pragma GCC optimize (3,"Ofast","inline")

using namespace std;
bool ST;
const int N = 1e6 + 5;
int n, m, dfn[N], top[N], sum[N], son[N], dcnt, f[N];
long long summ[N], dp[N];
struct Node{
  int u, v, w;
};
vector<Node> vis[N];
vector<int> v[N];
int read(){
  int k = 0, f = 1;
  char c = getchar();
  while(c < '0' || c > '9'){
    if(c == '-')f = -1;
    c = getchar();
  }
  while(c >= '0' && c <= '9')k = k * 10 + c - '0', c = getchar();
  return k * f;
}
void write(long long x){
	if(x > 9)write(x / 10);
	putchar((x % 10) ^ 48);
}
int lowbit(int x){
  return x & -x;
}
void modify(int x, long long y){
  for(; x <= n; x += lowbit(x))summ[x] += y;
}
long long query(int x){
  long long sum = 0;
  for(; x; x -= lowbit(x))sum += summ[x];
  return sum;
}
void dfs(int x, int fa){
  f[x] = fa;
  sum[x] = 1;
  for(int i : v[x]){
    if(i != fa){
      dfs(i, x);
      sum[x] += sum[i];
      if(sum[i] > sum[son[x]])son[x] = i;
    }
  }
}
void dfs2(int x, int fa){
  dfn[x] = ++dcnt;
  if(son[x]){
    top[son[x]] = top[x];
    dfs2(son[x], x);
  }
  for(int i : v[x]){
    if(i != fa && i != son[x]){
      top[i] = i;
      dfs2(i, x);
    }
  }
}
int LCA(int x, int y){
  while(top[x] != top[y]){
    if(dfn[x] < dfn[y])y = f[top[y]];
    else x = f[top[x]];
  }
  return (dfn[x] < dfn[y] ? x : y);
}
long long Lca(int x, int y){
  long long sum = 0;
  while(top[x] != top[y]){
    if(dfn[x] < dfn[y]){
      sum += query(dfn[y]) - query(dfn[top[y]] - 1);
      y = f[top[y]];
    }else{
      sum += query(dfn[x]) - query(dfn[top[x]] - 1);
      x = f[top[x]];
    }
  }
  sum += query(max(dfn[x], dfn[y])) - query(min(dfn[x], dfn[y]) - 1);
  return sum;
}
void DFS(int x, int fa){
  for(int i : v[x]){
    if(i != fa){
      DFS(i, x);
      dp[x] += dp[i];
    }
  }
  modify(dfn[x], dp[x]);
  for(Node i : vis[x]){
    dp[x] = max(dp[x], Lca(i.u, i.v) + i.w);
  }
  modify(dfn[x], -dp[x]);
}
bool ED;
signed main(){
  n = read(), m = read();
  for(int i = 2, x, y; i <= n; i++){
    x = read();
    v[x].push_back(i);
    v[i].push_back(x);
  }
  dfs(1, 0);
  f[1] = top[1] = 1;
  dfs2(1, 0);
  for(int i = 1, x, y, z; i <= m; i++){
    x = read(), y = read(), z = read();
    int xx = LCA(x, y);
    vis[xx].push_back({x, y, z});
  }
  DFS(1, 0);
  write(dp[1]);
  return 0;
}
```

---

## 作者：MyukiyoMekya (赞：4)

实际上就是带权版本的  HDU 4912 Paths on the tree

考虑dp

$f_u$ 表示在 $u$ 子树内能得到的最大答案

对于每条路径，我们肯定是在他的 lca 位置处理他的贡献

转移：

第一种，在这个点啥路径都不选：

$f_u=\sum f_v$，$v$ 是 $u$ 的儿子

第二种，选某一条 lca 为 $u$ 的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/4jqaiubr.png)

我们发现，选择橙色这条路径后，所有 lca经过绿色点的路径都没办法选择了，所以我们选择橙色路径的答案是所有蓝点的dp值加上橙色路径的权值。

这些蓝点其实就是路径上的点的**子节点**（注意不是子树）

那么我们有个很巧妙的方法来维护这个：

我们用维护每一个节点 $u$ 的 $-f_u+\sum f_v$

然后又因为我们是从叶子开始递归向根节点向上统计答案，所以在计算 $u$ 的dp值的时候，$u$ 向父亲节点方向的维护的节点的值一定是 0，因为当前节点的 dp 值还没弄完父节点一定不会被计算要维护的值

那么显然，我们要求的蓝点的dp值和就是**橙色路径两个端点到根节点的维护的值的和加上** $\sum f_v$（至于为什么不是到 $u$ 前面已经说过了，$u$ 的父亲方向节点的维护的值一定是 0），这个可以在上面那张图手模一下

那么我们就需要维护一个单点修改，查询点到根路径权值和

我们可以用线段树+dfs序来进行差分，区间修改直接把整棵子树（dfs序的区间）加上值就好，然后单点查询

当然也可以使用树状数组+dfs序，常数会小很多也很好写

选择一条路径的转移：

$f_u=\max \{ \text{这条路径蓝点dp值和}+\sum f_v \}$，$\sum f_v$ 在不选路径转移的时候先计算好就行了

时间复杂度 $O(n\log n)$

```cpp
// This code writed by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=200050;
struct Edge
{
	int nxt,to;
}E[MaxN<<2];
struct Quetion
{
	int u,v,w;
	int Lca;
};
struct SegmentTree
{
	#define lson (u<<1)
	#define rson (u<<1|1)
	int val[MaxN<<2],lazy[MaxN<<2];
	inline void pushup(int u)
	{
		val[u]=val[lson]+val[rson];
		return ;
	}
	inline void pushdown(int u,int l,int r)
	{
		if(lazy[u])
		{
			reg int mid=(l+r)>>1;
			lazy[lson]+=lazy[u];
			lazy[rson]+=lazy[u];
			val[lson]+=(mid-l+1)*lazy[u];
			val[rson]+=(r-mid)*lazy[u];
			lazy[u]=0;
		}
		return;
	}
	inline void modify(int u,int l,int r,int ql,int qr,int k)
	{
		if(ql<=l&&r<=qr)
		{
			val[u]+=(r-l+1)*k;
			lazy[u]+=k;
			return;
		}
		pushdown(u,l,r);
		reg int mid=(l+r)>>1;
		if(ql<=mid)
			modify(lson,l,mid,ql,qr,k);
		if(mid<qr)
			modify(rson,mid+1,r,ql,qr,k);
		pushup(u);
		return;
	}
	inline int query(int u,int l,int r,int p)
	{
		if(l==r)
			return val[u];
		pushdown(u,l,r);
		reg int mid=(l+r)>>1;
		if(p<=mid)
			return query(lson,l,mid,p);
		else
			return query(rson,mid+1,r,p);
		return -1;
	}
}tr;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int hd[MaxN],en,n,m;
int cnt;
int L[MaxN],R[MaxN];
int up[MaxN][21],dep[MaxN];
vector<Quetion> ask[MaxN];
int dp[MaxN];
inline void adde(int u,int v)
{
	++en;
	E[en]=(Edge){hd[u],v};
	hd[u]=en;
	return;
}
inline void dfs(int u,int fa)
{
	L[u]=++cnt;
	up[u][0]=fa;
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
	R[u]=cnt;
	return;
}
inline void Init_lca()
{
	for(int k=1;k<21;++k)
		for(int i=1;i<=n;++i)
			up[i][k]=up[up[i][k-1]][k-1];
	return;
}
inline int lca(int u,int v)
{
	if(dep[u]<dep[v])
		swap(u,v);
	if(u!=v)
		for(int k=20;k>=0;--k)
			if(dep[up[u][k]]>=dep[v])
				u=up[u][k];
	if(u==v)
		return u; 
	for(int k=20;k>=0;--k) 
		if(up[u][k]!=up[v][k])
			u=up[u][k],v=up[v][k];
	return up[u][0]; 
} 
inline void dfs2(int u,int fa)
{ 
	vector<int> Save;
	reg int DpSum=0;
	for(int i=hd[u];~i;i=E[i].nxt)
	{ 
		reg int v=E[i].to; 
		if(v==fa) 
			continue; 
		dfs2(v,u);
		dp[u]+=dp[v];
		DpSum+=dp[v];
	}
	for(int i=0;i<(int)ask[u].size();++i)
	{
		reg int l=ask[u][i].u;
		reg int r=ask[u][i].v;
		dp[u]=max(dp[u],ask[u][i].w+tr.query(1,1,n,L[l])+
			tr.query(1,1,n,L[r])+DpSum);
	}
	tr.modify(1,1,n,L[u],R[u],DpSum-dp[u]);
	return;
}
signed main(void)
{
	memset(hd,-1,sizeof hd);
	cin>>n>>m;
	reg int u,v;
	for(int i=2;i<=n;++i)
	{
		read(v);
		adde(i,v);
		adde(v,i);
	}
	dep[1]=1;
	dfs(1,0);
	// for(int i=1;i<=n;++i)
	// {
		// printf("Node %d %d %d\n",i,L[i],R[i]);
	// }
	Init_lca();
	reg int Lca,w;
	for(int i=1;i<=m;++i)
	{
		read(u);read(v);read(w);
		Lca=lca(u,v);
		ask[Lca].push_back((Quetion){u,v,w,Lca});
	}
	dfs2(1,0);
	cout<<dp[1]<<endl;
	return 0;
}
```



---

## 作者：Masterwei (赞：4)

膜你赛原题。讲一下赛时单 $\log$ 做法。

首先可以将加边的形式转化为链覆盖，也就是每个点最多被一条路径覆盖。

然后考虑 dp，设 $f_u$ 表示在 $u$ 的子树内，$u$ 会被链覆盖的最大权值和。$g_u$ 表示 $u$ 的子树内，$u$ 不会被链覆盖的最大权值和。

将每条路径挂在 lca 上，考虑在 lca 处计算这条路径的贡献。

首先是 $g$ 的转移。$g_u=\displaystyle \sum_{y\in son_u}\max(f_y,g_y)$。

在点 $u$，我们处理 $(a,b,w)$ 这条路径，有转移 $f_u=\max(g_a+g_b+cost(a,b)+w)$，其中 $cost(a,b)$ 表示 $a$ 到 $b$ 路径上与 $(a,b)$ 不交的权值之和。具体的，我们设 $h_u=g_{fa_u}-\max(f_u,g_u)$，那么 $cost(a,b)=\displaystyle \sum_{y\in path(a,b)\wedge  y\ne u}h_y$。明显我们可以在算出 $g$ 之后用树状数组维护 $h$ 数组。

求 lca 也是一只 $\log$，总共就是 $O(n\log n)$ 的。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int plen,ptop,pstk[40];
char rdc[1<<20],out[1<<20],*rS,*rT;
#define gc() (rS==rT?rT=(rS=rdc)+fread(rdc,1,1<<20,stdin),(rS==rT?EOF:*rS++):*rS++)
#define pc(x) out[plen++]=(x)
#define flush() fwrite(out,1,plen,stdout),plen=0
template<class T>inline void read(T &x){
    x=0;char ch;bool f=1;
    while(!isdigit(ch=gc()))if(ch=='-')f^=1;
    do x=(x<<1)+(x<<3)+(ch^48);while(isdigit(ch=gc()));
	if(!f)x=-x;
}
template<class T=int>inline void write(T x){
	if(plen>=1000000)flush();
	if(!x)return pc('0'),void();
	if(x<0)pc('-'),x=-x;
	for(;x;x/=10)pstk[++ptop]=x%10;
	while(ptop)pc(pstk[ptop--]+'0');
}
const int Maxn=2e5+5;
int n,m;
int head[Maxn],to[Maxn],nxt[Maxn],cnt1;
inline void add(int u,int v){
	to[++cnt1]=v;nxt[cnt1]=head[u];
	head[u]=cnt1;
}
struct edge{
	int u,v,w;
}e[Maxn];
int fa[Maxn],dep[Maxn],top[Maxn],si[Maxn],son[Maxn];
int id[Maxn],dfn[Maxn],cnt;
void dfs1(int u,int v){
	dep[u]=dep[v]+1;si[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];
		dfs1(y,u);si[u]+=si[y];
		if(si[son[u]]<si[y])son[u]=y;
	}
}
void dfs2(int u,int t){
	id[dfn[u]=++cnt]=u;
	top[u]=t;if(!son[u])return;
	dfs2(son[u],t);
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];if(y==son[u])continue;
		dfs2(y,y);
	}
}
inline int lca(int u,int v){
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}return dep[u]<dep[v]?u:v;
}
vector<edge>h[Maxn];
int f[Maxn],g[Maxn],di[Maxn];
inline int cost(int u){
	return max(f[u],g[u]);
}
int t[Maxn];
inline void change(int l,int r,int p){
	for(int x=l;x<=n;x+=x&-x)t[x]+=p;
	for(int x=r+1;x<=n;x+=x&-x)t[x]-=p;
}
inline int query(int x){
	x=dfn[x];
	int res=0;
	for(;x;x-=x&-x)res+=t[x];
	return res;
}
void dfs(int u,int v){
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];
		dfs(y,u);g[u]+=max(f[y],g[y]);
	}
	for(int i=head[u];i;i=nxt[i]){
		int y=to[i];
		di[y]=g[u]-cost(y);
		change(dfn[y],dfn[y]+si[y]-1,di[y]);
	}
	for(edge i:h[u]){
		f[u]=max(f[u],g[i.v]+g[i.u]+i.w+query(i.u)+query(i.v)-g[u]);
	}
}
signed main(){
//	freopen("peace.in","r",stdin);
//	freopen("peace.out","w",stdout);
	read(n);read(m);
	for(int i=2;i<=n;i++){
		read(fa[i]);add(fa[i],i);
	}dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=m;i++){
		read(e[i].u);read(e[i].v);read(e[i].w);
		if(dep[e[i].u]>dep[e[i].v])swap(e[i].u,e[i].v);
		h[lca(e[i].u,e[i].v)].push_back(e[i]);
	}dfs(1,0);
	write(max(f[1],g[1]));pc('\n');
	flush();
	return 0;
}
```

---

## 作者：_AyachiNene (赞：3)

线段树合并优化 dp，赛时被卡空间，拼尽全力无法战胜。
# 思路：
容易想到一个 dp 状态，设 $f_{i,j}$ 表示以 $i$ 为根的子树，编号为 $j$ 的额外边可以向上扩展。首先把每个额外边在两个端点上都挂一个，容易写出转移：

1. $f_{u,m+1}=f_{u,i}+f_{v,i}+w_i$
2. $f_{u,i}=\max(f_{u,i}+f_{v,0},f_{u,0}+f_{v,1})$

$m+1$ 用来暂存一下在这个点拼一条路径的情况，$0$ 为没有向上走的情况。容易发现有值的位置只有 $m+2$ 个，容易想到线段树合并，第二种转移可以全局加，第一种在合并时维护下最大值就行。时间和空间复杂度都是 $O(n\log n)$。

# Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(ll x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int bg;
struct node
{
	int nxt,to;
}e[200005<<1];
int head[200005],cnt_edge;
void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
int n,m;
int w[200005];
namespace Nene
{
	struct segt
	{
		int l,r;
		ll val,tag;
		segt(){val=-1e18;}
	}t[200005*41];
	#define mid ((l+r)>>1)
	int rt[200005],cnt;
	inline void push(int root,ll v){t[root].val+=v;t[root].tag+=v;}
	inline void down(int root)
	{
		if(!t[root].tag) return;
		if(t[root].l) push(t[root].l,t[root].tag);
		if(t[root].r) push(t[root].r,t[root].tag);
		t[root].tag=0;
	}
	void change(int x,ll v,int &root,int l=1,int r=m)
	{
		if(!root) root=++cnt;
		if(l==r) return t[root].val=max(t[root].val,v),void();
		down(root);
		if(x<=mid) change(x,v,t[root].l,l,mid);
		else change(x,v,t[root].r,mid+1,r);
	}
	ll u0,v0,mx;
	int merge(int x,int y,int l=1,int r=m)
	{
		if(!x||!y) return x|y;
		if(l==r)
		{
			mx=max(mx,t[x].val+t[y].val+w[l]-u0-v0);
			t[x].val=max(t[x].val,t[y].val);
			return x;
		}
		down(x);down(y);
		t[x].l=merge(t[x].l,t[y].l,l,mid);t[x].r=merge(t[x].r,t[y].r,mid+1,r);
		return x;
	}
	ll query(int x,int root,int l=1,int r=m)
	{
		if(l==r) return t[root].val;
		down(root);
		if(x<=mid) return query(x,t[root].l,l,mid);
		return query(x,t[root].r,mid+1,r);
	} 
}using namespace Nene;
ll f[200005],g[200005];
void dfs(int u,int fa)
{
	f[u]=0;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
		mx=-1e18,u0=f[u],v0=f[v];
		push(rt[u],v0);push(rt[v],u0);
		f[u]+=v0;f[v]+=u0;g[u]+=v0;g[v]+=u0;
		rt[u]=merge(rt[u],rt[v]);
		f[u]=max(f[u],f[v]);g[u]=max(g[u],g[v]);
		g[u]=max(g[u],mx);
	}
	f[u]=max(f[u],g[u]);
}
int ed;
signed main()
{
//	freopen("peace.in","r",stdin);
//	freopen("peace.out","w",stdout);
	//cout<<1.0*((&ed)-(&bg))/1024/1024*4<<endl;
	n=read(),m=read();
	for(int i=2;i<=n;i++)
	{
		int u=read();
		add_edge(u,i);
	}
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();w[i]=read();
		if(u==v)
		{
			g[u]=max(g[u],1ll*w[i]);
			continue;
		}
		change(i,0,rt[u]);change(i,0,rt[v]);
	}
	dfs(1,0);
	write(f[1]);
	//cout<<endl<<clock()/1e6<<endl;
	return 0;
}
```

---

## 作者：HYXLE (赞：2)

## CF856D Masha and Cactus

[题目传送门](https://www.luogu.com.cn/problem/CF856D)

显然题目可以转化为选择一些路径不交的链，使得这些链的权值和最大。

考虑一个较为暴力的 dp 做法。

设 $f_u$ 表示以 $u$ 为根的最小答案。

则第一种转移是 $f_u \leftarrow \sum_{son_u} f_v$。

接下来考虑枚举每一条链， 计算选择这条链的贡献。

怎么计算呢？

考虑在链的两端的 LCA 处计算其贡献。

假设我们有这样一颗树：

![](https://cdn.luogu.com.cn/upload/image_hosting/kv3woywd.png)

考虑一条从节点 $13$ 到节点 $10$ 的一条链，在节点 $20$ 处计算贡献。

先将这条链标记出来，有：

![](https://cdn.luogu.com.cn/upload/image_hosting/cdufsbhv.png)

发现当我们选择了这一条链之后，它的贡献为 $f_6$，$f_5$，$f_{11}$，$f_2$，$f_8$，$f_{14}$ 和这条链的价值的和。

所以我们可以得出：**一条链的贡献为所有这条链上的节点的直接儿子中不在这条链上的节点的节点的 dp 值之和加上这条链的贡献**。

知道这个之后就可以轻松写出 $O(nm)$ 的 dp 了。

接下来考虑优化。

记 $sum_u = \sum_{v\in son_u} f_v$。

发现可以将贡献挂在这一条链上。

具体的，定义节点 $u$ 的权值为 $sum_u-f_u$，那么可以发现，这一条链上的权值和再加上这条链的贡献即为这条链的贡献。

这个东西可以简单树剖 + 树状数组解决。

时间复杂度 $O(n\log_2^2n)$。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
#define mk(x,y) make_pair(x,y)
#define PII pair<int,int>
#define lowbit(x) (x&-x)
using namespace std;
const int N=1e6+5;
int plen,ptop,pstk[40];
char rdc[1<<20],out[1<<20],*rS,*rT;
#define gc() (rS==rT?rT=(rS=rdc)+fread(rdc,1,1<<20,stdin),(rS==rT?EOF:*rS++):*rS++)
#define pc(x) out[plen++]=(x)
#define flush() fwrite(out,1,plen,stdout),plen=0
template<class T>inline void read(T &x){
    x=0;char ch;bool f=1;
    while(!isdigit(ch=gc()))if(ch=='-')f^=1;
    do x=(x<<1)+(x<<3)+(ch^48);while(isdigit(ch=gc()));
	if(!f)x=-x;
}
template<class T=int>inline void write(T x){
	if(plen>=1000000)flush();
	if(!x)return pc('0'),void();
	if(x<0)pc('-'),x=-x;
	for(;x;x/=10)pstk[++ptop]=x%10;
	while(ptop)pc(pstk[ptop--]+'0');
}
struct edge{int u,v;}e[N<<1];
int head[N],tot;
inline void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
int n,m,x[N],y[N],w[N],dep[N],dfn[N],st[N][22],cur,curr,lg[N],siz[N];
ll f[N],ff[N],val[N];
vector<int> g[N];
namespace LCA{
	inline void dfs(int u,int fat){
		dep[u]=dep[fat]+1;siz[u]=1;
		dfn[u]=++cur;
		st[dfn[u]][0]=fat;
		for(R int i=head[u];i;i=e[i].v){
			int v=e[i].u;
			if(v==fat)continue;
			dfs(v,u);siz[u]+=siz[v];
		}
	}
	inline int getmin(int x,int y){return dep[x]<dep[y]?x:y;}
	inline void work(){
		lg[0]=-1;for(R int i=1;i<=n;i=-~i)lg[i]=lg[i>>1]+1;
		for(R int j=1;(1<<j)<=n;++j){
			for(R int i=1;i+(1<<j)-1<=n;i=-~i){
				st[i][j]=getmin(st[i][j-1],st[i+(1<<j-1)][j-1]);
			}
		}
	}
	inline int lca(int u,int v){
		if(u==v)return u;
		if(dfn[u]>dfn[v])swap(u,v);
		int k=lg[dfn[v]-dfn[u]];
		return getmin(st[dfn[u]+1][k],st[dfn[v]-(1<<k)+1][k]);
	}
}
int top[N],son[N],idx[N],fa[N];
namespace BetaCutShit{
    inline void dfs1(int u,int fat){
        siz[u]=1;dep[u]=dep[fat]+1;fa[u]=fat;int mx=0;
        for(R int i=head[u];i;i=e[i].v){
            int v=e[i].u;
            if(v==fat)continue;
            dfs1(v,u);siz[u]+=siz[v];
            if(mx<siz[v])mx=siz[v],son[u]=v;
        }
    }
    inline void dfs2(int u,int tp){
        top[u]=tp;idx[u]=++curr;
        if(!son[u])return;
        dfs2(son[u],tp);
        for(R int i=head[u];i;i=e[i].v){
            int v=e[i].u;
            if(v==fa[u]||son[u]==v)continue;
            dfs2(v,v);
        }
    }
}
ll tr[N];
inline void upd(int pos,ll x){while(pos<=n){tr[pos]+=x;pos+=lowbit(pos);}}
inline ll qry(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
inline ll qry(int l,int r){return qry(r)-qry(l-1);}
inline ll qry_chain(int ls,int rs){
	ll res=0;
	while(top[ls]!=top[rs]){
		if(dep[top[ls]]<dep[top[rs]])swap(ls,rs);
		res+=qry(idx[top[ls]],idx[ls]);
		ls=fa[top[ls]];
	}
	if(dep[ls]>dep[rs])swap(ls,rs);
	res+=qry(idx[ls],idx[rs]);
	return res;
}
inline void DP(int u,int fat){
	for(R int i=head[u];i;i=e[i].v){
		int v=e[i].u;
		if(v==fat)continue;
		DP(v,u);
		f[u]+=f[v];
	}
	ff[u]=f[u];
	f[u]+=val[u];
	upd(idx[u],ff[u]);
	ll tmp=0;
	for(int id:g[u]){
		if(x[id]==y[id])continue;
		ll tmp2=qry_chain(x[id],y[id]);
		tmp=max(tmp,tmp2+w[id]);
	}
	f[u]=max(f[u],tmp);
	upd(idx[u],-f[u]);
}
int main(){
	read(n);read(m);
	for(R int i=2;i<=n;i=-~i){int f;read(f);add(i,f);add(f,i);}
	LCA::dfs(1,0);LCA::work();BetaCutShit::dfs1(1,0);BetaCutShit::dfs2(1,1);
	for(R int i=1;i<=m;i=-~i){read(x[i]),read(y[i]),read(w[i]),g[LCA::lca(x[i],y[i])].emplace_back(i);if(x[i]==y[i]){val[x[i]]=max(val[x[i]],1ll*w[i]);}}
	DP(1,0);write(f[1]);
	flush();
	return 0;
}
```

希望这篇题解能帮助到大家！

---

## 作者：PNNNN (赞：2)

### 思路：

#### step 1.
仙人掌，也就是每一个点至多包含于一个环的图。考虑先将树建出来，将树上的边称为树边，新的被选择加入树的边称为非树边。可以发现，每一个点至多成为一条非树边的的两个端点的 $lca$。这是因为当新加入一条非树边 $(x,y)$ 时，原树 $x$ 到 $y$ 的简单路径上的所有点都会成为一个环上的点。由此自然而然的想到将非树边 $(x,y)$ 放到 $\operatorname{lca}(x,y)$ 上算贡献。

#### step 2.
考虑在树上进行 dp。设 $dp_x$ 表示以点 $x$ 为根的子树内的答案。该如何转移？
为了方便转移，不妨设 $sum_x = \sum \limits_{y \in son_x} dp_y$。

1. 若 $x$ 不作为一条新加入的非树边的两个端点的 $lca$，则 $dp_x= sum_x$。

2. 否则，枚举每一条以 $x$ 为 $lca$ 的非树边，设其为 $(u,v)$，此时树上 $u$ 到 $v$ 的简单路径上的点都会成为环上的一点，所以这些点的 $dp$  都不会为 $dp_x$ 产生贡献。因为这些点的 $dp$ 的值可能是在成为环上的点之后才取到的，会与仙人掌的定义冲突，但如果这些点之间有些点的 $dp$ 值是在该点没有成为环的时候取到的呢？见下文。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tbdo8ah5.png)

假如我们现在要加入非树边 $(5,6)$，此时的 $x$ 为 $1$，则点 $2,4,5,3,6$ 的 $dp$ 都无法为 $dp_x$ 产生贡献。考虑有哪些点可以为 $dp_1$ 产生贡献。可以发现，$7,8,9$ 会产生贡献，因为他们不在这个环上。因此，我们得知，当枚举到一条为 $(u,v)$ 的非树边时，其产生的贡献为 $u$ 到 $v$ 的路径上所有点的不在路径上子节点的 $dp$ 之和。这样就可以写出 $O(n\times m)$ 的暴力 dp 转移了。

如何优化？

设 $val_x=sum_x-dp_x$。我们惊奇的发现，路径上所有点除点 $x$ 外的 $val$ 之和再加上 $sum_x$，就为我们要求的贡献，所以 $dp_x=\sum \limits_{y \in path(u,v),y \ne x } (sum_y-dp_y)  +sum_x$。这个可以用树剖加线段树或者树状数组解决。时间复杂度 $O(n \times {\log_2^2 n} )$。此题还有树上差分的做法，这里不做讲解。回到上一个问题，若一个点的 $dp$ 值是在成为环上一点前取到的，那么根据上文，$dp_x=sum_x$，且还要减去它在路径上的子节点的 $dp$，若没有则不减，可以发现也与上文的式子符合。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,dp[200005],sum[200005];

int dep[200005],siz[200005],fa[200005],top[200005],mxs[200005],dfn[200005],mp[200005],cnt;

vector <int> to[200005];

struct line{
	int A,B,w;
};

vector <line> e[200005];

struct BIT{
	int t[200005];
	inline int lowbit(int x){return x&-x;}
	inline void updata(int x,int val){
		while(x<=n){
			t[x]+=val,x+=lowbit(x);
		}return;
	}
	inline int query(int x){
		int res=0;
		while(x>0){
			res+=t[x],x-=lowbit(x);
		}return res;
	}
	inline int get(int l,int r){
		return query(r)-query(l-1);
	}
}T;

inline void dfs1(int x,int last){
	dep[x]=dep[last]+1,fa[x]=last,siz[x]=1;
	for(int y:to[x]){
		if(y==last)continue;
		dfs1(y,x),siz[x]+=siz[y];
		if(siz[y]>siz[mxs[x]])mxs[x]=y;
	}return;
}

inline void dfs2(int x,int last){
	dfn[x]=++cnt,mp[cnt]=x,top[x]=last;
	if(!mxs[x])return;dfs2(mxs[x],last);
	for(int y:to[x]){
		if(y==fa[x]||y==mxs[x])continue;
		dfs2(y,y);
	}return;
}

inline int jump(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res+=T.get(dfn[top[x]],dfn[x]),x=fa[top[x]];
	}if(dep[x]>dep[y])swap(x,y);
	return res+T.get(dfn[x],dfn[y]);
}

inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}if(dep[x]>dep[y])swap(x,y);
	return x;
}

inline void tree_dp(int x,int last){
	for(int y:to[x]){
		if(y==last)continue;
		tree_dp(y,x),sum[x]+=dp[y];
	}dp[x]=sum[x];
	for(int i=0;i<e[x].size();i++){
		int A=e[x][i].A,B=e[x][i].B,w=e[x][i].w;
		dp[x]=max(dp[x],jump(A,B)+sum[x]+w);
	}T.updata(dfn[x],sum[x]-dp[x]);
	return;
}

inline int read(){
	register int x(0),t(0);
	static char ch=getchar();
	while(!isdigit(ch)){t|=(ch=='-'),ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return t?-x:x;
}

signed main(){
	n=read(),m=read();
	for(int i=2;i<=n;i++){
		to[read()].push_back(i);
	}dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),w=read();
		if(dep[x]<dep[y])swap(x,y);
		e[lca(x,y)].push_back({x,y,w});
	}tree_dp(1,0);
	cout<<dp[1];
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

挺好的一道题。

首先，对于在一棵树上加边的问题，我们一般可以在**每条新边两个端点的lca处记录这条边的信息**，如[这道题](http://poj.org/problem?id=3417)。

但是，在lca处记录完后如何呢？

考虑**树上dp**。

设$f_i$为$i$号节点在以它为根的子树内所能取得的最大的权值和。

考虑转移。

1）不选lca为$i$的任何一条新边。此时，有$f_i=\Sigma f_j$，$j$是$i$的儿子。

2）选择一条从$u$到$v$，权值为$w$的新边。这时，有$f_i=w+\Sigma f_j$，$j$是$u$到$v$路径上任意一个点的某个儿子，且$j$不在路径上。

换一个说法。令$g_i=\Sigma f_j$，且$j$是$i$的儿子（即$g_i$为方案一中的$f_i$）。则$f_i=w+\Sigma (g_j-f_j)$，且$j$在路径上。因为对于一个路径上的点$k$，**$f_k$必定在$k$处加上，又在$g_{father_k}$处被减去**。

但是我们不能枚举路径上每一个$k$，不然是$O(n^2)$的。

显然，树上单点修改，路径求和，可以**树剖**。

但树剖码量大，不想写，怎么办？

**树上差分**。

同往常的树上差分一样，令$sum_i$储存$i$到根节点上所有点的$(g_i-f_i)$的值的和。

则方案二的答案为$w+sum_u+sum_v+g_i$。（因为在dp到节点$i$时，$i$的所有祖先都还没有dp，则$sum_i$为$0$。）

而修改，就从单点修改变成子树修改。查询则是单点查询。

子树修改，我们有**dfs序**。

设$dfn_i$为$i$号节点的dfs序，$sz_i$为$i$号节点子树大小。

则所有dfs序在$[dfn_i,dfn_i+sz_i-1]$区间内的点$j$都应该被修改。

查询$i$的话，则查询$dfn_i$。

于是我们就可以用线段树维护了。

复杂度$O(nlog_2n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1) 
int n,m,head[200100],cnt,f[200100],g[200100],anc[200100][20],dep[200100],dfn[200100],sz[200100],tot;
struct edge{
	int to,next;
}edge[200100];
struct EDGE{
	int u,v,w;
	EDGE(int x=0,int y=0,int z=0){
		u=x,v=y,w=z;
	}
};
void ae(int u,int v){
	edge[cnt].next=head[u],edge[cnt].to=v,head[u]=cnt++;
}
vector<EDGE>v[200100];
void dfs_lca(int x){
	dfn[x]=++tot,sz[x]=1;
	for(int i=1;(1<<i)<=dep[x];i++)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=head[x];i!=-1;i=edge[i].next)dep[edge[i].to]=dep[x]+1,anc[edge[i].to][0]=x,dfs_lca(edge[i].to),sz[x]+=sz[edge[i].to];
}
int LCA(int x,int y){
	if(dep[x]>dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[x]<=dep[y]-(1<<i))y=anc[y][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(anc[x][i]!=anc[y][i])x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
struct SegTree{
	int sum,tag;
}seg[800100];
void pushup(int x){
	seg[x].sum=seg[lson].sum+seg[rson].sum;
}
void pushdown(int x,int l,int r){
	seg[lson].sum+=(mid-l+1)*seg[x].tag,seg[rson].sum+=(r-mid)*seg[x].tag;
	seg[lson].tag+=seg[x].tag,seg[rson].tag+=seg[x].tag;
	seg[x].tag=0;
}
void modify(int x,int l,int r,int L,int R,int val){
	if(l>R||r<L)return;
	if(L<=l&&r<=R){seg[x].sum+=(r-l+1)*val,seg[x].tag+=val;return;}
	pushdown(x,l,r),modify(lson,l,mid,L,R,val),modify(rson,mid+1,r,L,R,val),pushup(x);
}
int query(int x,int l,int r,int P){
	if(l>P||r<P)return 0;
	if(l==r)return seg[x].sum;
	pushdown(x,l,r);
	return query(lson,l,mid,P)+query(rson,mid+1,r,P);
}
void dfs_dp(int x){
	for(int i=head[x];i!=-1;i=edge[i].next)dfs_dp(edge[i].to),g[x]+=f[edge[i].to];
	f[x]=g[x];
	for(int i=0;i<v[x].size();i++)f[x]=max(f[x],query(1,1,n,dfn[v[x][i].u])+query(1,1,n,dfn[v[x][i].v])+v[x][i].w+g[x]);
	modify(1,1,n,dfn[x],dfn[x]+sz[x]-1,g[x]-f[x]);
}
int main(){
	scanf("%d%d",&n,&m),memset(head,-1,sizeof(head));
	for(int i=2,Fa;i<=n;i++)scanf("%d",&Fa),ae(Fa,i);
	dfs_lca(1);
	for(int i=1,x,y,z;i<=m;i++)scanf("%d%d%d",&x,&y,&z),v[LCA(x,y)].push_back(EDGE(x,y,z));
	dfs_dp(1);
//	for(int i=1;i<=n;i++)printf("(%d,%d)\n",f[i],g[i]);
	printf("%d\n",f[1]);
	return 0;
}
```


---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF856D)。

## 思路

对于每个新加的边，考虑在其 $\mathrm{LCA}$ 处处理，令 $f_u$ 表示 $u$ 子树内连成仙人掌的最大价值，枚举新加的边 $(s,t)$（满足 $\mathrm{LCA}(s,t)=u$），有两种转移：

- 不选择该边，$f_u\gets \sum_{(u,v)\in E} f_v$。
- 选择该边，贡献是 $u$ 子树内去除掉 $s\to t$ 路径剩下的子树的 $f$ 之和，这种形式不难想到容斥，记 $g_u=\sum_{(u,v)\in E}f_v$，那么这部分的贡献就是 $\sum_{u\in S}g_u-f_u$，$S$ 是 $s\to t$ 路径上的点集。

两种转移取 $\max$ 即可，可以用树剖前缀和维护，时间复杂度 $\mathcal O(n\log n)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=4e5+7;
ll f[Maxn],g[Maxn],val[Maxn],dd[Maxn];
vector<int>e[Maxn];
int son[Maxn],top[Maxn],sz[Maxn],fa[Maxn],dep[Maxn];

void dfs1(int u,int ft){
	sz[u]=1; fa[u]=ft; dep[u]=dep[ft]+1;
	for(auto v:e[u]){
		if(v==ft) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[son[u]]<sz[v]) son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp; 
	if(son[u]) dfs2(son[u],tp);
	for(auto v:e[u]){
		if(v==fa[u] or v==son[u]) continue;
		dfs2(v,v);
	}
}
int LCA(int u,int v){
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
ll work(int u,int v){
	ll ret=0;
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ret+=val[top[u]]-val[son[u]];
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	ret+=val[v]-val[son[u]];
	return ret;
}

struct node{
	int u,v,w;
};
vector<node>q[Maxn];

int n,m;
void dfs(int u){
	for(auto v:e[u]){
		if(v==fa[u]) continue;
		dfs(v);
		g[u]+=f[v];
		f[u]+=f[v];
	}
	val[u]=val[son[u]]+g[u];
	for(auto i:q[u]) f[u]=max(f[u],work(i.u,i.v)+i.w);
	
	val[u]-=f[u];
}

int main(){	
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++) scanf("%d",&fa[i]),e[fa[i]].emplace_back(i);
	dfs1(1,0);
	dfs2(1,1);
	
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		int lca=LCA(u,v);
		q[lca].emplace_back((node){u,v,w});
	}
	dfs(1);
	
	printf("%lld",f[1]);
	
}

```

---

## 作者：XenonKnight (赞：1)

[题面传送门](https://codeforces.ml/contest/856/problem/D)

> 题意：
> - 给你一棵 $n$ 个顶点的树和 $m$ 条带权值的附加边
> - 你要选择一些附加边加入原树中使其成为一个**仙人掌**（每个点最多属于 $1$ 个简单环）
> - 求你选择的附加边权值之和的最大值。
> - $n \in [3,2 \times 10^5]$，$m \in [0,2 \times 10^5]$

很容易发现，如果你选择一条端点为 $u,v$ 的附加边，那么 $u$ 到 $v$ 路径上所有点都会被包含进一个简单环。

那么题目变为：有 $m$ 条路径，你要选择其中某些路径使得每个点**最多被一条路径覆盖**。问选择的路径权值之和的最大值。

对于这一类问题，我们可以想到树形 $dp$。记 $dp_u$ 为：选择一些路径，路径上所有点都在 $u$ 的子树内，并且路径两两不相交，这些路径权值之和的最大值。

转移分两种情况：

1. $u$ 没有被覆盖，那么 $dp_u=\sum\limits_{fa_v=u}dp_v$

2. $u$ 被覆盖。那么显然它只能被 $LCA=u$ 的路径覆盖（因为根据之前的定义，路径上所有节点都必须在 $u$ 的子树内）。这种情况下就是 $u$ 的子树挖掉这条路径后剩余部分的答案+这条路径的权值。

是不是听起来有些抽象？不妨画个图理解看：

假设有如下图的树，你选择了由橙色边组成的路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/oy8h4jyi.png)

我们把这条路径上的点全部去掉看看剩余部分是个什么东西。

![](https://cdn.luogu.com.cn/upload/image_hosting/9rtve1gi.png)

~~凭直觉~~，这部分的贡献为 

$dp[4]+dp[5]+dp[6]+dp[7]+dp[10]+dp[13]+dp[16]+dp[17]+dp[19]+dp[21]+dp[24]$

发现了什么了吗？

你可能会说，项数这么多，我啥也没发现。

那我们就把删掉的点补全后看看呗。

![](https://cdn.luogu.com.cn/upload/image_hosting/vjit01el.png)

通过观察，我们发现：

- $4,5$ 是 $3$ 的儿子
- $6,7$ 是 $2$ 除了 $3$ 之外的儿子
- $10,13$ 是 $1$ 除了 $2,15$ 之外的儿子
- $16,17$ 是 $15$ 除了 $18$ 之外的儿子
- $19$ 是 $18$ 除了 $20$ 之外的儿子
- $21,24$ 是 $20$ 的儿子。

我们记 $p_1 \to p_2 \to \dots \to p_k$ 为我们选择的路径，其中 $p_j=i$，$p_0=p_{k+1}=0$，那么贡献为：

$$\sum\limits_{i=1}^j\sum\limits_{fa_v=p_i}dp_v \times [v \neq p_{i-1}]+\sum\limits_{fa_v=u}dp_v \times [v \neq p_{i-1} \operatorname{and} v \neq p_{i+1}]+\sum\limits_{i=j+1}^k\sum\limits_{fa_v=p_i}dp_v \times [v \neq p_{i+1}]+w$$

暴力显然是 $n^2$ 的，考虑对其进行优化。

记 $g_x=\sum\limits_{fa_y=x}dp_y-dp_x$，那么上式子等价于

$$\sum\limits_{i=1}^{j-1}g_{p_i}+\sum\limits_{fa_v=u}dp_v+\sum\limits_{i=j+1}^kg_{p_i}+w$$

用树链剖分随便维护一下就可以了

```cpp
/*
Contest: -
Problem: Codeforces 856D
Author: tzc_wk
Time: 2020.8.20
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define pb			push_back
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define y1			y1010101010101
#define y0			y0101010101010
typedef pair<int,int> pii;
typedef long long ll;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-') neg=-1;
		c=getchar();
	}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x*neg;
}
int n=read(),m=read();
int head[200005],to[400005],nxt[400005],ecnt=0;
inline void adde(int u,int v){
	to[++ecnt]=v;nxt[ecnt]=head[u];head[u]=ecnt;
}
int fa[200005],top[200005],dep[200005],siz[200005],wson[200005],dfn[200005],nd[200005],tim=0;
inline void dfs1(int x){
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];dep[y]=dep[x]+1;dfs1(y);siz[x]+=siz[y];
		if(siz[y]>siz[wson[x]]) wson[x]=y;
	}
}
inline void dfs2(int x,int tp){
	top[x]=tp;dfn[x]=++tim;nd[tim]=x;
	if(wson[x]) dfs2(wson[x],tp);
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];if(y!=wson[x]) dfs2(y,y);
	}
}
inline int getlca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	return y;
}
struct path{
	int u,v,w;
	path(){/*nothing*/}
	path(int _u,int _v,int _w){u=_u;v=_v;w=_w;}
}; vector<path> t[200005];
struct node{
	int l,r,val;
} s[200005<<2];
inline void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
inline void modify(int k,int ind,int val){
	if(s[k].l==s[k].r){s[k].val+=val;return;}
	int mid=(s[k].l+s[k].r)>>1;
	if(ind<=mid) modify(k<<1,ind,val);
	else modify(k<<1|1,ind,val);
	s[k].val=s[k<<1].val+s[k<<1|1].val;
}
inline int query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].val;
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
inline int calc(int u,int v){
	int sum=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		sum+=query(1,dfn[top[u]],dfn[u]);u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	sum+=query(1,dfn[v],dfn[u]);return sum;
}
int dp[200005];
inline void dfs3(int x){
	int sum=0;
	for(int i=head[x];i;i=nxt[i]){
		dfs3(to[i]);sum+=dp[to[i]];
	}
	dp[x]=sum;
	foreach(it,t[x]) dp[x]=max(dp[x],calc(it->u,it->v)+it->w+sum);
	modify(1,dfn[x],sum-dp[x]);
}
int main(){
	for(int i=2;i<=n;i++){fa[i]=read();adde(fa[i],i);}
	dfs1(1);dfs2(1,1);build(1,1,n);
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		t[getlca(u,v)].pb(path(u,v,w));
	}
	dfs3(1);printf("%d\n",dp[1]);
	return 0;
}
```

---

## 作者：RainySoul (赞：0)

在树上选择若干条不交路径，每条路径有一个收益，最大化收益和。

考虑树形 $\text{dp}$，设 $f_u$ 表示以 $u$ 为根的子树中的答案。

转移并不困难，如果 $u$ 这个点不被某条路径覆盖的话，直接从儿子转移，有 $f_u=\sum\limits_{v \in son_u}f_v$。

否则考虑所有经过 $u$ 的路径，一条路径 $(x,y,z)$ 对 $f_u$ 的贡献是这条路径上的点的其他子树的答案和加上这条路径的收益。令 $path(x,y)$ 表示 $x$ 到 $y$ 路径上的点集，则 

$$f_u\gets\sum\limits_{v\in path(x,y)}((\sum\limits_{k \in son_v}f_k-f_v)+\sum\limits_{k \in son_u}f_k+z)$$

显然你只需要维护一下 $(\sum\limits_{k \in son_v}f_k-f_v)$ 这一坨东西就可以了，由于在处理 $u$ 之前 $path(x,y)$ 上的其他点都已经被处理过了，这个东西可以简单地树剖维护。算完一个点的 $f_u$ 之后就把这个点的 $\sum\limits_{k \in son_u}f_k-f_u$ 打到线段树上。

时间复杂度 $O(n \log ^2n)$。不过后面这部分要做到 $O(n\log n)$ 似乎也并不困难。

Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,m,cnt;
int fa[N],sz[N],son[N],dfn[N],rnk[N],dep[N],top[N],f[N];
vector<int> e[N];
struct zyx{int u,v,w;};
vector<zyx> q[N];
struct SegementTree{
    int w[N<<2];
    void update(int u,int l,int r,int x,int k){
        if(l==r){
            w[u]=k;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid)update(u*2,l,mid,x,k);
        else update(u*2+1,mid+1,r,x,k);
        w[u]=w[u*2]+w[u*2+1];
    }
    int query(int u,int l,int r,int x,int y){
        if(x<=l&&r<=y){
            return w[u];
        }
        int mid=(l+r)>>1;
        int res=0;
        if(x<=mid)res+=query(u*2,l,mid,x,y);
        if(y>mid)res+=query(u*2+1,mid+1,r,x,y);
        return res;
    }
    int QUERY(int x,int y){
        int res=0;
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]])swap(x,y);
            res+=query(1,1,n,dfn[top[x]],dfn[x]);
            x=fa[top[x]];
        }
        if(dep[x]>dep[y])swap(x,y);
        res+=query(1,1,n,dfn[x],dfn[y]);
        return res;
    }
}T;
void dfs1(int now,int fz){
    fa[now]=fz;
    sz[now]=1;
    dep[now]=dep[fz]+1;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(to==fz)continue;
        dfs1(to,now);
        sz[now]+=sz[to];
        if(sz[to]>sz[son[now]])son[now]=to;
    }
}
void dfs2(int now,int topf){
    dfn[now]=++cnt;
    rnk[cnt]=now;
    top[now]=topf;
    if(!son[now])return;
    dfs2(son[now],topf);
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(to==fa[now]||to==son[now])continue;
        dfs2(to,to);
    }
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
void dfs3(int now,int fz){
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(to==fz)continue;
        dfs3(to,now);//首先先处理完它子树内的f
    }
    int sum=0;
    for(int i=0;i<(int)e[now].size();i++){
        int to=e[now][i];
        if(to==fz)continue;
        sum+=f[to];
    }
    f[now]=max(f[now],sum);
    for(int i=0;i<(int)q[now].size();i++){
        int u=q[now][i].u,v=q[now][i].v,w=q[now][i].w;
        f[now]=max(f[now],T.QUERY(u,v)+sum+w);
    }
    T.update(1,1,n,dfn[now],sum-f[now]);//拍到线段树上
}
signed main(){
    n=read(),m=read();
    for(int i=2;i<=n;i++){
        int fz=read();
        e[fz].push_back(i);
    }
    dfs1(1,0);dfs2(1,1);
    for(int i=1;i<=m;i++){//你直接把所有询问先拍到LCA上去方便转移
        int u=read(),v=read(),w=read();
        int lca=LCA(u,v);
        q[lca].push_back((zyx){u,v,w});
    }
    dfs3(1,0);
    cout<<f[1];
    return 0;
}
```

闲话：喜欢我线段树的大常数吗？

---

## 作者：ran_qwq (赞：0)

如果树是一条链，那就是有 $m$ 个区间，你要选择一些区间，使得权值和最大。

这不经典 dp 题？$f_i$ 表示只考虑前 $i$ 个点的最大权值。

可以不选以 $i$ 为右端点的区间，$f_i\leftarrow f_{i-1}$。

也可以选一个以 $i$ 为右端点的区间，设它为 $[j,i]$，权值为 $w$。$f_i\leftarrow f_{j-1}+w$。

现在我们把它搬到树上，把一条路径挂在 $a_i$ 和 $b_i$ 的 LCA（下文称为顶点）上。

仍然可以不选以 $u$ 为顶点的路径。可看作把 $u$ 子树中 $u$ 点删掉，分裂出来的若干个连通块独立。即把所有儿子 $f$ 值加起来，$f_u\leftarrow\sum\limits_v f_v$。

还可以选以 $u$ 为顶点的路径 $i$。同样道理，可看作把 $u$ 子树中 $a_i$ 到 $b_i$ 这条路径删掉，分裂出来的若干个连通块独立。

我们假设 $a_i\ne u,b_i\ne u$，因为等于 $u$ 的情况更简单。

这条路径把 $u$ 子树分成若干部分，大概有这么几类：$a_i$ 的儿子、$b_i$ 的儿子、路径上一点的兄弟。

前两者是容易的，随便分讨一下。

令 $g_u$ 为 $u$ 儿子的 $f$ 和，可以单点加，路径查 $g$ 的和，用树剖可做到双 log。

但我们有更优的解法。我们要查的是 $u$ 到某个点的 $g$ 和。考虑直接维护根到某个点 $w$ 的 $g$ 和，记作 $h_w$。

类似换根 dp 的思路，如果根从 $v$ 挪到 $u$，会使子树内的 $h$ 值增加 $g_v$，线段树区间加即可。

时间复杂度单 log，代码有点细节。

```cpp
int n,m,id,nm,hd[N],fa[N],d[N],sz[N],sn[N],tp[N],dfn[N],a[N],b[N],c[N]; ll f[N],sf[N]; vi t[N];
struct EDGE {int to,ne;} e[N];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id;}
void dfs1(int u,int f) {
	fa[u]=f,d[u]=d[f]+1,sz[u]=1;
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=f)
		dfs1(v,u),sz[u]+=sz[v],sz[v]>sz[sn[u]]&&(sn[u]=v);
}
void dfs2(int u,int f) {
	tp[u]=f,dfn[u]=++nm;
	if(sn[u]) dfs2(sn[u],f);
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa[u]&&v!=sn[u]) dfs2(v,v);
}
int lca(int u,int v) {
	for(;tp[u]!=tp[v];) {
		if(d[tp[u]]<d[tp[v]]) swap(u,v);
		u=fa[tp[u]];
	}
	return d[u]<d[v]?u:v;
}
struct SGT {
	#define ls (id<<1)
	#define rs (id<<1|1)
	#define mid (l+r>>1)
	#define all 1,1,n
	#define Ls ls,l,mid
	#define Rs rs,mid+1,r
	ll vl[N*4],tg[N*4];
	il void pu(int id) {vl[id]=vl[ls]+vl[rs];}
	il void ad(int id,ll k) {vl[id]+=k,tg[id]+=k;}
	il void pd(int id) {ad(ls,tg[id]),ad(rs,tg[id]),tg[id]=0;}
	void upd(int id,int l,int r,int L,int R,ll k) {
		if(L<=l&&r<=R) return ad(id,k);
		pd(id),L<=mid?upd(Ls,L,R,k):void(),R>mid?upd(Rs,L,R,k):void(),pu(id);
	}
	ll qry(int id,int l,int r,int x) {
		if(l==r) return vl[id];
		pd(id); return x<=mid?qry(Ls,x):qry(Rs,x);
	}
} sgt;
void dfs3(int u,int fa) {
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa) dfs3(v,u),f[u]+=f[v],sf[u]+=f[v];
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa)
		sgt.upd(all,dfn[v],dfn[v]+sz[v]-1,sf[u]-f[v]),sgt.upd(all,dfn[v],dfn[v],sf[v]);
	for(int i:t[u])
		if(a[i]==u&&b[i]==u) cmaxll(f[u],sf[u]+c[i]);
		else if(a[i]==u) cmaxll(f[u],sgt.qry(all,dfn[b[i]])+c[i]);
		else if(b[i]==u) cmaxll(f[u],sgt.qry(all,dfn[a[i]])+c[i]);
		else cmaxll(f[u],sgt.qry(all,dfn[a[i]])+sgt.qry(all,dfn[b[i]])-sf[u]+c[i]);
}
void QwQ() {
	n=rd(),m=rd();
	for(int i=2;i<=n;i++) add(rd(),i);
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=m;i++) a[i]=rd(),b[i]=rd(),c[i]=rd(),t[lca(a[i],b[i])].pb(i);
	dfs3(1,0),wrll(f[1],"\n");
}
```

---

## 作者：zdd6310 (赞：0)

# [Masha and Cactus](https://www.luogu.com.cn/problem/CF856D)

求树上不交路径权值之和的最大值。

考虑 $dp$。定义 $f_u$ 表示以 $u$ 为根的子树中，选择若干路径的权值和最大值。

把一条路径 $(u,v,w)$ 置于 $\operatorname{lca}(u,v)$ 处统计。

转移比较迷惑，就是路径下面挂着的每一个点的 $f$ 之和。

比如：

![](https://img.picui.cn/free/2025/02/24/67bc17ac2c4a3.bmp) 

在子树 $1$ 中，如果选了路径 $(8,11)$，那么现在的答案就是 $f_7+f_6+f_{10}+f_{13}+f_{12}+f_{4}+w$。

如何快速计算？

记录 $g_u=(\sum\limits_{v\in son(u)}f_v)-f_u$。若没有计算到就设置为 $0$。

则路径 $(x,y)$ 的贡献为 $w+\sum\limits_{p\in(u,v)}g_p$。

可以分类考虑：

- 若在路径下，比如节点 7。此时你会在父亲的 $g$ 中被计算。
- 若在路径中，且不是 $u$，比如节点 5。值在当前节点被减去，在父亲节点被加上。
- 若为 $u$，则不被统计。

发现恰好就是我们需要的部分。

每一次计算完之后，把 $f_u$ 添加到 $fa$ 和 $u$ 中即可。

需要路径查询，单点修改，树剖和 BIT 即可。复杂度 $O(n\log^2 n)$。

其实也可以对 $g$ 树上差分，变成单点查询，子树修改。只需要 BIT，复杂度 $O(n\log n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
int n,m,head[MAXN],tot;
struct node{int nxt,to;}e[MAXN<<1];
inline void add(int u,int v){
	e[++tot]=node{head[u],v};
	head[u]=tot;
}
int siz[MAXN],fa[MAXN],dep[MAXN],son[MAXN];
void dfs(int u,int fa1){
	siz[u]=1,fa[u]=fa1,dep[u]=dep[fa1]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa1)continue;
		dfs(v,u),siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
int dfn[MAXN],dfncnt,rid[MAXN],top[MAXN];
void dfs2(int u,int fa1,int tp){
	dfn[u]=++dfncnt,rid[dfncnt]=u;top[u]=tp;
	if(son[u])dfs2(son[u],u,tp);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa1||v==son[u])continue;
		dfs2(v,u,v);
	}
}
inline int __lca(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]<dep[top[b]])swap(a,b);
		a=fa[top[a]];
	}
	return dep[a]<dep[b]?a:b;
}
#define lb(x) (x&-x)
struct BIT{
	ll tr[MAXN];
	inline void upd(int x,ll k){while(x<=n){tr[x]+=k;x+=lb(x);}}
	inline ll qry(int x){ll cnt=0;while(x){cnt+=tr[x];x-=lb(x);}return cnt;}
	inline ll qry(int l,int r){return qry(r)-qry(l-1);}
}T;
inline ll query(int u,int v){
	ll ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		ans+=T.qry(dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dfn[u]>dfn[v])swap(u,v);
	ans+=T.qry(dfn[u],dfn[v]);
	return ans;
}
ll dp[MAXN];
struct qry{int x,y,w;};
vector<qry>vec[MAXN];
void dfs3(int u,int fa1){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa1)continue;
		dfs3(v,u);dp[u]+=dp[v];
	}
	for(auto [x,y,w]:vec[u]){
		dp[u]=max(dp[u],query(x,y)+w);
	}
	T.upd(dfn[u],-dp[u]);
	if(fa[u])T.upd(dfn[fa[u]],dp[u]);
}
namespace Read{...}
signed main(){
    read(n,m);
    for(int i=2,fa;i<=n;i++){
        read(fa);add(i,fa),add(fa,i);
    }
	dfs(1,0),dfs2(1,0,1);
	for(int i=1,u,v,w;i<=m;i++){
        read(u,v,w);
		vec[__lca(u,v)].push_back(qry{u,v,w});
	}
	dfs3(1,0);
    write(dp[1],'\n');
}
```

---

## 作者：Purslane (赞：0)

# Solution

简单题。

设 $dp_u$ 表示只考虑两端点都在 $u$ 子树内的线段，获得的最大的价值。

两种情况：

1. $u$ 没有被任何一条线段覆盖。因此，答案是 $\sum_{v \in son_u} dp_v$；
2. $u$ 被某一条线段覆盖了。

假设这条线段是 $l \to u \to r$，那么其他线段不能经过这条路径上的所有点。

我们只能考虑下图子树内的结构：（根节点可能会带上很多子树，但先不管）

![](https://s21.ax1x.com/2024/06/13/pkdkWnO.png)

考虑把权值扔到节点上。对于红色子树的贡献，我们记录 $u$ 所有兄弟的 $dp$ 之和；蓝色子树的贡献，记录 $u$ 所有儿子的 $dp$ 之和即可。这样变成：树上单点修改，链查询。复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,tot,tr[MAXN],dep[MAXN],fa[MAXN][21],sze[MAXN],val[MAXN],dfn[MAXN],dp[MAXN];
vector<pair<pair<int,int>,int>> upd[MAXN];
vector<int> G[MAXN];
void dfs1(int u,int f) {
	dep[u]=dep[f]+1,dfn[u]=++tot,sze[u]=1;
	ffor(i,1,20) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(auto v:G[u]) dfs1(v,u),sze[u]+=sze[v];
	return ;	
}
int lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);
	int dt=dep[u]-dep[v],id=0;
	while(dt) {
		if(dt&1) u=fa[u][id];
		dt>>=1,id++;
	}
	if(u==v) return u;
	roff(i,20,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}
int jump(int u,int v) {
	ffor(i,0,20) if(v&(1<<i)) u=fa[u][i];
	return u;	
}
void update(int pos,int v) {
	while(pos<=n) tr[pos]+=v,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	int ans=0;
	while(pos) ans+=tr[pos],pos-=pos&-pos;
	return ans;	
}
void dfs2(int u,int f) {
	int sum=0;
	for(auto v:G[u]) dfs2(v,u),sum+=dp[v];
	for(auto pr:upd[u]) {
		int l=pr.first.first,r=pr.first.second,v=pr.second;	
		int tval=query(dfn[l])+query(dfn[r]);
		if(l!=u) tval+=val[l],l=jump(l,dep[l]-dep[u]-1);
		if(r!=u) tval+=val[r],r=jump(r,dep[r]-dep[u]-1);
		tval+=sum+v;
		if(l!=u) tval-=dp[l];
		if(r!=u) tval-=dp[r];
		dp[u]=max(dp[u],tval);
	}
	dp[u]=max(dp[u],sum),val[u]=sum;
	for(auto v:G[u]) update(dfn[v],sum-dp[v]),update(dfn[v]+sze[v],dp[v]-sum);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,2,n) cin>>fa[i][0],G[fa[i][0]].push_back(i);
	dfs1(1,0);
	ffor(i,1,m) {
		int l,r,w;
		cin>>l>>r>>w;
		if(dep[l]<dep[r]) swap(l,r);
		upd[lca(l,r)].push_back({{l,r},w});			
	}
	dfs2(1,0);
	cout<<dp[1];
	return 0;
}
```

---

