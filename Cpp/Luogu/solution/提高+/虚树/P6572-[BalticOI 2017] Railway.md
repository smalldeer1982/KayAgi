# [BalticOI 2017] Railway

## 题目背景

Bergen 基础设施建设部在一年前就有了把所有的城市用道路连起来的想法。  
可惜的是，过了一年了，这个计划烂尾了。  
所以，基础设施建设部部长就准备重启这个计划，然后把它搞得简单亿点。

## 题目描述

原定的计划是有 $n$ 个城市用 $n-1$ 个道路连起来。    
现在有 $m$ 个副部长，每个副部长都认为有一些城市是必须连起来的。  
比如说这个副部长想把 $a$ 和 $c$ 连起来，有两条道路 $a - b$ 和 $b - c$，那么副部长的要求等价过来就是选择这两条道路。  
现在要找出几条道路是至少 $k$ 个副部长选择的。  
部长就找到了您，想让您找出这几条道路。

## 说明/提示

#### 样例说明

$3$ 个副部长的要求如下：

- $1-3,2-3,3-4,4-5$
- $3-4,4-6$
- $2-3$

至少满足 $2$ 个副部长的道路为 $2$ 号和 $3$ 号。

#### 数据范围

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$n \le 10^4$，$\sum s_i \le 2 \times 10^3$。
- Subtask 2（15 pts）：$n \le 10^4$，$m \le 2 \times 10^3$。
- Subtask 3（7 pts）：每个城市最多是 $2$ 条道路的端点。
- Subtask 4（29 pts）：$k=m$，$s_i=2$。
- Subtask 5（16 pts）：$k=m$。
- Subtask 6（25 pts）：无特殊限制。

对于 $100\%$ 的数据，$2 \le s_i \le n \le 10^5$，$1 \le k \le m \le 5 \times 10^4$，$\sum s_i \le 10^5$。

#### 说明

**翻译自 [BOI 2017 D1](https://boi.cses.fi/files/boi2017_day1.pdf) T2 Railway。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

应扶咕咕的要求已经删减 $1 \sim 5$ 子任务中的部分数据，保留了 $6$ 子任务中的极限数据。

## 样例 #1

### 输入

```
6 3 2
1 3
2 3
3 4
6 4
4 5
4 1 3 2 5
2 6 3
2 3 2```

### 输出

```
2
2 3```

# 题解

## 作者：slzs (赞：11)

## 思路
对于每一个副部长，我们把被他选择的点按dfs序从小到大排序，依次使相临两点最短路径上的边的权值+1。最后判断有哪些边的权值不小与2*k即可。

#### 举个例子
如图：若副部长选择的点为4,5,7。(可以发现本来只算一次的边，恰好算了2次)


![](https://cdn.luogu.com.cn/upload/image_hosting/12l4w9ng.png)


从4到5，从5到7，从7到4。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
using namespace std;
const int N=401000;
int n,m,k,num,tot=0,dotot=0,tp=0;
int lst[N],dfn[N],sum[N],laz[N],ls[N],rs[N],q[N],u[N],v[N];
int id[N],dep[N],top[N],son[N],siz[N],fa[N];
struct A
{
	int fir,nex,go,type;
}a[N];
inline bool cmp(int E,int F)
{
	return dfn[E]<dfn[F];
}
void add(int x,int y)
{
	a[++tot].nex=a[x].fir;
	a[x].fir=tot;
	a[tot].go=y;
}
inline int read()
{
	int x=0,minus=0;char ch;
	while (!isdigit(ch=getchar())) minus|=(ch=='-');
	while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return minus?-x:x;
}
void dfs1(int x,int f)
{
	dfn[x]=++dotot;//dfs序
	fa[x]=f;
	dep[x]=dep[f]+1;
	siz[x]=1;
	for (register int i=a[x].fir;i;i=a[i].nex)
	{
		int y=a[i].go;
		if (y==f) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if (siz[son[x]]<siz[y]) son[x]=y;
	}
}
void dfs2(int x,int topf)
{
	id[x]=++dotot;//线段树用的
	top[x]=topf;
	if (!son[x]) return ;
	dfs2(son[x],topf);
	for (register int i=a[x].fir;i;i=a[i].nex)
	{
		int y=a[i].go;
		if (y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
void build(int k,int l,int r)
{
	ls[k]=l,rs[k]=r;
	if (l==r) return ;
	int mid=(l+r)>>1;
	build(k<<1,l,mid),build(k<<1|1,mid+1,r);
}
void down(int k)
{
	if (laz[k]==0) return ;
	laz[k<<1]+=laz[k];
	laz[k<<1|1]+=laz[k];
	sum[k<<1]+=(rs[k<<1]-ls[k<<1]+1)*laz[k];
	sum[k<<1|1]+=(rs[k<<1|1]-ls[k<<1|1]+1)*laz[k];
	laz[k]=0;
}
void change(int k,int x,int y)
{
	if (ls[k]>=x&&rs[k]<=y)
	{
		sum[k]+=rs[k]-ls[k]+1;
		laz[k]++;
		return ;
	}
	down(k);
	if (x<=rs[k<<1]) change(k<<1,x,y);
	if (y>=ls[k<<1|1]) change(k<<1|1,x,y);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline int cheak(int k,int x)
{
	if (ls[k]==rs[k]) return sum[k];
	down(k);
	if (x<=rs[k<<1]) return cheak(k<<1,x);
	else return cheak(k<<1|1,x);
}
void chain(int x,int y)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if (x==y) return ;
	if (dep[x]>dep[y]) swap(x,y);
	change(1,id[son[x]],id[y]);
}
signed main()
{
	n=read(),m=read(),k=read();
	for (register int i=1,x,y;i<n;++i)
	x=read(),y=read(),add(x,y),add(y,x),u[i]=x,v[i]=y;
	tot=0,dfs1(1,0),dotot=0,dfs2(1,1),build(1,1,n);//预处理
	while (m--)
	{
		num=read();
		for (register int i=1;i<=num;++i) lst[i]=read();
		sort(lst+1,lst+1+num,cmp);//按dfs序排序
		for (register int i=1;i<num;++i) chain(lst[i],lst[i+1]);
		chain(lst[1],lst[num]);//依次使相临两点最短路径上的边的权值+1
	}
	for (register int i=1;i<n;++i)
	{
		if (dep[u[i]]<dep[v[i]]) swap(u[i],v[i]);//树剖把边权存到儿子那了
		if (cheak(1,id[u[i]])>=2*k) q[++tp]=i;
	}
	printf("%d\n",tp);
	for (register int i=1;i<=tp;++i) printf("%d ",q[i]);//输出答案
	return 0;
}
```




---

## 作者：一扶苏一 (赞：9)

## 【虚树，树上差分】P6572 [BOI 2017] Railway

### Analysis

对于每一个副部长，我们可以把被他选择的所有边都加上 $1$，最后 check 有哪些边的权值不小于 $k$ 即可。

对于 $s_i = 2$ 的子任务，我们可以轻松找出两个节点之间的那条链。问题被转化为链加以及最终统计，可以使用树上差分解决。为了统计边权，将边权下放成点权即可。

对于一般情况，我们没法不重复的快速给所有被选择的边都 $+1$。考虑建出虚树，注意到虚树的边对应到原图上就是所有被选择的边。我们把虚树上一条边 $(u, v)$，其中 $u$ 是父节点，对应到原图上 $v$ 到 $u$ （但是不包括 $u$）的这条链上。那么对这些链进行链加即可。时间复杂度 $O(n \log n)$，这里认为 $n, m, \sum s$ 同阶。

### Code

```cpp
namespace Fusu {

const int maxt = 19;
const int maxn = 100005;

int n, m, t, vistime;
int dfn[maxn], fa[maxn], depth[maxn], l2[maxn], a[maxn], id[maxn], g[maxn], w[maxn], anc[maxt][maxn];
std::vector<int> p, q, e[maxn], ans;
std::vector<std::pair<int, int> > ee[maxn];

void dfs(const int u);
void vt();
void dfs2(const int u);

void Main() {
  qr(n); qr(m); qr(t);
  for (int u, v, i = 1; i < n; ++i) {
    qr(u); qr(v);
    ee[u].push_back({v, i});
    ee[v].push_back({u, i});
  }
  for (int i = 0, v = 1 << i; v <= n; v = 1 << ++i) l2[v] = i;
  for (int i = 3; i <= n; ++i) if (l2[i] == 0) l2[i] = l2[i - 1];
  dfs(1);
  for (int s, x; m; --m) {
    qr(s);
    p.clear();
    q.clear();
    while (s--) {
      qr(x);
      p.push_back(x);
    }
    vt();
  }
  dfs2(1);
  for (int i = 1; i <= n; ++i) if (w[i] >= t) ans.push_back(id[i]);
  std::sort(ans.begin(), ans.end());
  qw(ans.size(), '\n');
  for (auto u : ans) {
    qw(u, ' ');
  }
  putchar('\n');
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) std::swap(u, v);
  for (int delta = depth[u] - depth[v]; delta; delta -= 1 << l2[delta]) {
    u = anc[l2[delta]][u];
  }
  if (u == v) return u;
  for (int i = l2[depth[u]]; ~i; --i) if (anc[i][u] != anc[i][v]) {
    u = anc[i][u];
    v = anc[i][v];
  }
  return anc[0][u];
}

int top;
int stk[maxn];
void vt() {
  std::sort(p.begin(), p.end(), [](const int x, const int y) { return dfn[x] < dfn[y]; });
  stk[top = 1] = 0;
  int x, y, z;
  for (auto u : p) {
    x = stk[top];
    if ((z = lca(x, u)) != x) {
      while (dfn[y = stk[top - 1]] > dfn[z]) {
        g[x] = y; q.push_back(x); x = stk[--top];
      }
      if (y != z) {
        g[x] = z; q.push_back(x);
        stk[top] = z;
      } else if (top != 1) {
        g[x] = y;
        q.push_back(x);
        --top;
      }
    }
    stk[++top] = u;
  }
  while (top != 1) {
    int x = stk[top], y = stk[--top];
    g[x] = y;
    q.push_back(x);
  }
  for (auto u : q) if (g[u]) {
    ++w[u];
    --w[g[u]];
  }
}

void dfs(const int u) {
  dfn[u] = ++vistime;
  depth[u] = depth[fa[u]] + 1;
  for (int i = 0, v = anc[i][anc[i][u] = fa[u]]; v; v = anc[i][v]) anc[++i][u] = v;
  for (auto v : ee[u]) if (dfn[v.first] == 0) {
    fa[v.first] = u;
    id[v.first] = v.second;
    e[u].push_back(v.first);
    dfs(v.first);
  }
}

void dfs2(const int u) {
  for (auto v : e[u]) {
    dfs2(v);
    w[u] += w[v];
  }
}

} // namespace Fusu
```

---

## 作者：一铭君一 (赞：5)

# P6572 BalticOI 2017 Railway 题解

## 题意简述

题面并不复杂。总的来说，要求你维护一棵树的所有边，每次给定 $m$ 个结点，要求你选择最少的边，使得这 $m$ 个点联通。把所选边的边权 +1 ，最后询问有多少条边的边权大于等于 $k$。

## 思路历程

无论做什么题，手玩样例总是一个好习惯。

![](https://cdn.luogu.com.cn/upload/image_hosting/pjw2zgq8.png)

这个题的样例是这样的，1 号的要求为红色，2 号的为蓝色，3 号的为绿色，很明显 连接 2 3 的边和连接 3 4 的边符合要求。

直接选边不好操作，一个比较容易想到的操作就是先把两个点路径上的边权 +1 （连接起来）。然后再连接第三个、第四个...

但是这样显然不对，如果用这个思路去满足 1 号的要求的话，你会发现连接 2 3 的那条边被重复选择了一次。

太糟糕了！整理一下心情，思考一下为什么会出错：

看到如果 1 号的要求是连接 1、3、5 这 3 个点，我们的算法就不会出错，为什么？因为 1、3、5 这 3 个点在同一条链上（暂且叫做“主链”），而我们按照顺序访问一个链上的所有目标结点，可以做到不重不漏的覆盖掉整个链。

2 号结点不在 1、3、5 这 3 个结点组成的链上，所以我们走到 3 的时候必须要“转弯”去访问 2 号结点。访问完了之后还要再“回到”主链上，这就导致我们从主链到 2 号结点上的路径（暂且叫做“支链”）被重复计算了。

分析到这里，我们可以得知，只要不是主链上的点，其到主链的路径上所有的边一定会被计算两次。

有没有什么办法避免重复计算呢？我不知道，但是既然所有支链路径都被计算两次，那么我们为什么不让主链“随个大流”，也把它计算两次呢？

用这个思路重新手玩一下样例，发现正好每条边都被计算了两次，这样我们计算答案的时候就应该统计那些边权大于等于 $2k$ 的边。

等等！你以为这就完了？如果 1 号的要求是连接 1、4、3、2、5 呢？发现如果按顺序处理的话，连接 3 4 的这条边算了 4 次！

这种情况是因为我们没有按顺序访问主链，而是先访问了深度较深的 4 ，然后回过头来去访问深度较浅的 3 ，这样也会导致重复覆盖。

我们可以根据 dfs 序对这些点排序，这样就可以保证我们按照顺序，不重不漏的访问完整个主链，从而保证算法正确。

剩下的东西很简单了：快速修改树上一条路径上的边权，这个树链剖分可以做到。

## $\text{Talk is cheap,show you the code.}$

树链剖分本来是维护点权的，如果让他维护边权的话，一个常用的操作是把边权下放到他的儿子结点，当作点权计算。

这里我用了另一个在 LCT 中常用的方法：把边建成一个带权的点，这样直接跑树链剖分就行。（但是带了 2 倍的时空常数）

```cpp
//前面都是些快读啥的，为了简洁就省略了（其实是因为太长被打回来了）
const int maxn=400005;

int n,m,k,tot;

std::vector<int>v[maxn];

int heavy[maxn],fa[maxn],id[maxn],cnt,dep[maxn],size[maxn],top[maxn];

struct segment_tree{
  int l,r,value,tag;
  segment_tree *ls,*rs;
};
struct segment_tree *root;

inline bool in_range(segment_tree *node,const int L,const int R){
  return L<=node->l && node->r<=R;
}

inline bool outof_range(segment_tree *node,const int L,const int R){
  return node->r<L || R<node->l;
}

inline void update(segment_tree *node){
  node->value=node->ls->value+node->rs->value;
}

inline void make_tag(segment_tree *node,const int w){
  node->value=node->value+(node->r-node->l+1)*w;
  node->tag+=w;
}

inline void push_down(segment_tree *node){
  if(node->tag){
    make_tag(node->ls,node->tag);
    make_tag(node->rs,node->tag);
    node->tag=0;
  }
}

segment_tree* Build(const int L,const int R){
  segment_tree *u=new segment_tree;
  u->l=L,u->r=R;
  u->tag=u->value=0;
  if(L==R){
    u->ls=u->rs=NULL;
  }else{
    int Mid=(R+L)>>1;
    u->ls=Build(L,Mid);
    u->rs=Build(Mid+1,R);
    update(u);
  }
  return u;
}

int query(segment_tree *node,const int L,const int R){
  if(in_range(node,L,R)) return node->value;
  if(outof_range(node,L,R)) return 0;
  push_down(node);
  return query(node->ls,L,R)+query(node->rs,L,R);
}

void modify(segment_tree *node,const int L,const int R){
  if(in_range(node,L,R)) make_tag(node,1);
  else if(!outof_range(node,L,R)){
    push_down(node);
    modify(node->ls,L,R);
    modify(node->rs,L,R);
    update(node);
  }
}

void path_modify(int x,int y){
  while(top[x]!=top[y]){
    if(dep[top[x]]<dep[top[y]]) swap(x,y);
    modify(root,id[top[x]],id[x]);
    x=fa[top[x]];
  }
  if(dep[x]>dep[y]) swap(x,y);
  modify(root,id[x],id[y]);
}

void dfs1(const int x,const int f){
  fa[x]=f;
  dep[x]=dep[f]+1;
  size[x]=1;
  int M=-1;
  for(int i=0;i<v[x].size();++i){
    int y=v[x][i];
    if(y==f) continue;
    dfs1(y,x);
    size[x]+=size[y];
    if(size[y]>M)
      M=size[y],heavy[x]=y;
  }
}

void dfs2(const int x,const int topf){
  id[x]=++cnt;
  top[x]=topf;
  if(!heavy[x]) return;
  dfs2(heavy[x],topf);
  for(int i=0;i<v[x].size();++i){
    int y=v[x][i];
    if(y==heavy[x] || y==fa[x]) continue;
    dfs2(y,y);
  }
}//上面那一堆都是树链剖分

std::pair<int,int>order[maxn];//pair的特性：以第一维为第一关键字
int out[maxn];

signed main(){
//	freopen("P6572_7.in","r",stdin);
  read(n),read(m),read(k);
  for(int i=1,a,b;i<n;++i){
    read(a),read(b);
		tot++;
    v[a].push_back(n+tot);
    v[n+tot].push_back(a);//把边拆成点，分配一个编号
    v[n+tot].push_back(b);
    v[b].push_back(n+tot);  
  }
  dfs1(1,0);
	dfs2(1,1); 
  root=Build(1,cnt);
  while(m--){
    int s;
    read(s);
    for(int i=1;i<=s;++i){
      read(order[i].second);
      order[i].first=id[order[i].second];
    }
    std::sort(order+1,order+s+1);//排好序再路径修改
    for(int i=2;i<=s;++i)
      path_modify(order[i-1].second,order[i].second);
    path_modify(order[1].second,order[s].second);
  }//直接路径修改
  int ans=0;
  for(int i=1;i<=tot;++i){
    if(query(root,id[n+i],id[n+i])>=k*2) 
      ans++,out[ans]=i;//查询每一条边的边权
  }
  write(ans),putchar('\n');
  for(int i=1;i<=ans;++i)//输出答案
    write(out[i]),putchar(' ');
  return 0;
}
```

---

## 作者：Tweetuzki (赞：3)

> 给出一棵 $n$ 个节点的树。有 $m$ 次染色操作，每次操作给出一些点，把覆盖他们的最小连通块内的边染上颜色。求被染色次数不小于 $k$ 的边数。
> 
> $n \le 10 ^ 5$，$m \le 5 \times 10 ^ 4$，$k \le m$。

先以 $1$ 为根，把这棵树变成有根树。

对于一个点 $u$，考虑它向父亲连的边 $e$ 会被什么样的操作染色。

这条边要被一个方案的连通块包含，必须要满足边的两边都有方案内的点。也就是说，这个方案在 $u$ 子树内有点，$u$ 子树外也有点。

换句话说，就是这个方案在 $u$ 子树内有点，且不是所有点都在 $u$ 子树内。

形式化地说，就是设这个方案 $x$ 在 $u$ 子树内出现次数为 $c_x$，那么这个方案会对 $u$ 到父亲的边 $e$ 染色当且仅当 $0 \lt c_x \lt s_x$，其中 $s_x$ 是第 $x$ 个方案的点数。

接下来只要计算每个点子树内有多少个点满足这个不等式就能得到答案。启发式合并维护。

时间复杂度 $\mathcal{O}((n + m) \log m)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

const int MaxN = 100000, MaxM = 50000;

struct graph_t {
  int cnte;
  int head[MaxN + 5], to[MaxN * 2 + 5], next[MaxN * 2 + 5];

  graph_t() {
    cnte = 1;
    memset(head, 0, sizeof head);
    memset(to, 0, sizeof to);
    memset(next, 0, sizeof next);
  }

  inline void addEdge(int u, int v) {
    cnte++;
    to[cnte] = v;
    next[cnte] = head[u];
    head[u] = cnte;
  }
};

int N, M, Q, K;
int S[MaxM + 5];
graph_t Gr;
std::vector< std::pair<int, int> > Vec;
std::vector<int> Ans;

int Fa[MaxN + 5], Sum[MaxN + 5], Wson[MaxN + 5];
int Id[MaxN + 5], Dfc, Left[MaxN + 5], Right[MaxN + 5];

void init() {
  scanf("%d %d %d", &N, &M, &K);
  for (int i = 1; i < N; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    Gr.addEdge(u, v);
    Gr.addEdge(v, u);
  }
  for (int i = 1; i <= M; ++i) {
    scanf("%d", &S[i]);
    for (int j = 1; j <= S[i]; ++j) {
      int x;
      scanf("%d", &x);
      Sum[x]++;
      Vec.push_back(std::make_pair(x, i));
    }
  }
  Q = (int) Vec.size();
}

void dfs1(int u) {
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Fa[u]) continue;
    Fa[v] = u;
    dfs1(v);
    Sum[u] += Sum[v];
    if (Wson[u] == 0 || Sum[v] > Sum[Wson[u]]) Wson[u] = v;
  }
}

void dfs2(int u) {
  Id[u] = ++Dfc;
  if (Wson[u] != 0) dfs2(Wson[u]);
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Fa[u] || v == Wson[u]) continue;
    dfs2(v);
  }
}

inline bool cmp(std::pair<int, int> x, std::pair<int, int> y) { return Id[x.first] < Id[y.first]; }

void dfs3(int u) {
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Fa[u]) continue;
    dfs3(v);
    Left[u] = std::min(Left[u], Left[v]);
    Right[u] = std::max(Right[u], Right[v]);
  }
}

int Buc[MaxM + 5], Num;

inline void ins(int x) {
  Buc[x]++;
  if (Buc[x] == 1) Num++;
  if (Buc[x] == S[x]) Num--;
}

inline void del(int x) {
  Buc[x]--;
  if (Buc[x] == 0) Num--;
  if (Buc[x] == S[x] - 1) Num++;
}

void dfs4(int u, int tof) {
  int weightsontof = 0;
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Fa[u]) continue;
    if (v == Wson[u]) {
      weightsontof = (i >> 1);
      continue;
    }
    dfs4(v, i >> 1);
    for (int j = Left[v]; j <= Right[v]; ++j) del(Vec[j].second);
  }
  if (Wson[u] != 0) dfs4(Wson[u], weightsontof);
  for (int i = Left[u]; i < std::min(Right[u] + 1, Left[Wson[u]]); ++i) ins(Vec[i].second);
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Fa[u] || v == Wson[u]) continue;
    for (int j = Left[v]; j <= Right[v]; ++j) ins(Vec[j].second);
  }
  if (Num >= K) Ans.push_back(tof);
}

void solve() {
  dfs1(1);
  dfs2(1);
  std::sort(Vec.begin(), Vec.end(), cmp);
  for (int i = 0; i <= N; ++i) Left[i] = Q, Right[i] = -1;
  for (int i = 0; i < Q; ++i) {
    std::pair<int, int> p = Vec[i];
    Left[p.first] = std::min(Left[p.first], i);
    Right[p.first] = std::max(Right[p.first], i);
  }
  dfs3(1);
  dfs4(1, 0);
  printf("%d\n", (int) Ans.size());
  std::sort(Ans.begin(), Ans.end());
  for (int i = 0; i < (int) Ans.size(); ++i)
    printf("%d%c", Ans[i], " \n"[i == (int) Ans.size() - 1]);
}

int main() {
  init();
  solve();
  return 0;
}
```

---

## 作者：Pain_Of_Regret (赞：1)

## 题目大意

给定一棵树，同时有 $m$ 个人，每个人在树上选定一些点，并让他们联通。求在 $k$ 个及以上的人的方案中都要联通的边。

## 思路

这是一道树上统计类题目，我们考虑使用树上差分。但是树上差分在这道题目中只能做两个点的情况，那我们怎么优化呢？

因为这里面的一堆点是靠线段连接起来的，我们在这些点里的连接方式里进行一点研究。例如我下面图中的这棵树，我们要将 $3,4,7$ 这三个点连通。

![](https://pic.imgdb.cn/item/62b964861d64b07066e52930.png)

然后我们依次用树上差分连接 $(4,7),(7,3),(3,4)$ 得到以下这样。

![](https://pic.imgdb.cn/item/62b965651d64b07066e6d32b.png)

我们惊奇的发现所有要用的边都被加了两次！观察一下我们可以发现将这些点按照 dfs 序排序，两两相连，并将最小和最大相连，这样所有的边都会被覆盖两次。而我们在找一些其他的点，都可以验证这一个性质。

那我们就可以通过进行树上差分来解决这个问题了。

## 代码实现

在写代码之前，我们再考虑一个问题：如何处理边权？我们可以将边权转移到它的儿子节点那里去，那么除了根节点之外，其他所有的点都对应唯一的一条边，在输出的时候再按照边的编号进行排序就可以了。

```c++
#include <bits/stdc++.h>
using namespace std;
template <typename T>
T read()
{
    char c = getchar();
    int neg = 1;
    T sum = 0;
    while (!isdigit(c))
    {
        if (c == '-')
            neg = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        sum = (sum << 3) + (sum << 1) + (c ^ 48);
        c = getchar();
    }
    return sum * neg;
}
#define Read read<int>
int n, m, k;
vector<pair<int, int>> g[100010];
vector<int> id[100010];
int f[100010][32], dfsxu[100010], dep[100010];
int cnt, diff[100010], toe[100010];
void dfs(int cur, int fa)
{
    dfsxu[cur] = ++cnt;
    f[cur][0] = fa;
    dep[cur] = dep[fa] + 1;
    for (int i = 1; (1 << i) <= dep[cur]; i++)
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    for (int i = 0; i < g[cur].size(); i++)
    {
        int to = g[cur][i].second;
        if (to == fa)
            continue;
        dfs(to, cur);
        toe[to] = g[cur][i].first;
    }
}
int lca(int x, int y)
{
    if (dep[x] > dep[y])
        swap(x, y);
    for (int i = 30; i >= 0; i--)
    {
        if (dep[f[y][i]] >= dep[x])
            y = f[y][i];
    }
    if (x == y)
        return x;
    for (int i = 30; i >= 0; i--)
    {
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
bool cmp(int x, int y)
{
    return dfsxu[x] < dfsxu[y];
}
bool cmp2(int x, int y)
{
    return toe[x] < toe[y];
}
void Calcans(int cur, int fa)
{
    for (int i = 0; i < g[cur].size(); i++)
    {
        int to = g[cur][i].second;
        if (to == fa)
            continue;
        Calcans(to, cur);
        diff[cur] += diff[to];
    }
}
int main()
{
#ifdef LOCAL
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    n = Read();
    m = Read();
    k = Read();
    for (int i = 1; i < n; i++)
    {
        int x = Read(), y = Read();
        g[x].push_back(make_pair(i, y));
        g[y].push_back(make_pair(i, x));
    }
    dfs(1, 0);
    vector<int> vec;
    for (int i = 1; i <= m; i++)
    {
        int x = Read();
        vec.clear();
        for (int j = 1; j <= x; j++)
            vec.push_back(Read());
        sort(vec.begin(), vec.end(), cmp);
        for (int j = 0; j < x - 1; j++)
        {
            int xx = vec[j], y = vec[j + 1], l = lca(xx, y);
            diff[xx] += 1;
            diff[y] += 1;
            diff[l] -= 2;
        }
        int xx = vec[vec.size() - 1], y = vec[0], l = lca(xx, y);
        diff[xx] += 1;
        diff[y] += 1;
        diff[l] -= 2;
    }
    Calcans(1, 0);
    vec.clear();
    for (int i = 2; i <= n; i++)
    {
        if (diff[i] >= 2 * k)
            vec.push_back(i);
    }
    printf("%d\n", vec.size());
    sort(vec.begin(), vec.end(), cmp2);
    for (auto i : vec)
        printf("%d ", toe[i]);
    return 0;
}
```


---

## 作者：qwqszxc45rtnhy678ikj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6572)

P6572 这题应该不难想到，可以先建树，再将每个副局长选定的城市  lca，通过 dfs 差分做出来~~

假设副局长选定了 $k$ 个城市，我们就循环遍历这些城市，当  $i<k$ ，应该取编号为 $i$ 和 $i+1$ 的来 lca，如果 $i=k$ ，就取编号为 $k$ 和 $1$ 的来求，每个城市求了两次，最后差分是判定是否大于等于 $k/2$ 就是了。

这个算法看似没问题，但有漏洞——有可能在一个副局长选定的城市做差可以看作，它加了几条边，求了两次，后来其他两个城市做差，又加了其中一条一次，加起来就求了四次了……怎么解决呢？很简单，只要再把选定的 $k$ 个通过 dfs 序排一下就可以了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, k, t1, t2, fa[100010][30], sx[100010], dep[100010], tsx, sk, tk[100010], a[100010], gh[100010], ans;
struct node{
	long long ph, bh;
};
vector<node> p[100010];
void js(long long h, long long g) {//建树
	fa[h][0] = g;//父亲节点
	dep[h] = dep[g] + 1;//深度
	sx[h] = ++tsx;//dfs 序
	for(int i = 1; i <= 20; i++) fa[h][i] = fa[fa[h][i - 1]][i - 1];//这是倍增，lca 会用到 
	for(int i = 0; i < p[h].size(); i++)
		if(p[h][i].ph != g)
			js(p[h][i].ph, h);
}
bool cmp(long long x, long long y) {
	return sx[x] < sx[y];
}
long long lca(long long x, long long y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; i--)
		if(dep[fa[x][i]] >= dep[y])
			x = fa[x][i];
	if(x == y) return x;//如果已经等于就直接返回
	for(int i = 20; i >= 0; i--)
		if(fa[x][i] != fa[y][i]) {//不等于就跳
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];//最后返回它们的父亲节点
}
void dfs(long long h, long long g) {
	for(int i = 0; i < p[h].size(); i++)
		if(p[h][i].ph != g){
			dfs(p[h][i].ph, h);
			if(a[p[h][i].ph] >= k * 2) {//如果大于 k*2 ，这就是要求的边之一
				ans++;
				gh[p[h][i].bh] = 1;
			}
			a[h] += a[p[h][i].ph];
		}
}
int main() {
	cin >> n >> m >> k;
	for(int i = 1; i < n; i++) {
		cin >> t1 >> t2;
		p[t1].push_back({t2, i});
		p[t2].push_back({t1, i});
	}
	js(1, 0);
	for(int i = 1; i <= m; i++) {
		cin >> sk;
		for(int i = 1; i <= sk; i++) cin >> tk[i];
		sort(tk + 1, tk + sk + 1, cmp);//按照 dfs 序排序
		for(int i = 1; i <= sk; i++) {
			long long fu = lca(tk[i], tk[i % sk + 1]);
			a[tk[i]]++;
			a[tk[i % sk + 1]]++;
			a[fu] -= 2;//因为是求边而不是点，所以这里的做差应该是 -2
		}
	}
	dfs(1, 0);
	cout << ans << endl;
	for(int i = 1; i < n; i++)
		if(gh[i])
			cout << i << " ";
	return 0;
}
```


---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/P6572)

设某个副部长要连的点集为 $h$，要求这个副部长所选的边。

我们会发现，如果将 $h$ 中所有元素按 $\text{dfs}$ 序排列，然后依次相连，并且第一个元素和最后一个元素相连，就会形成一个环。

而环上的边就是副部长要选的，并且都会被重复计算两次。

为什么按 $\text{dfs}$ 序排序？因为按这样的话，如果到某个 $h_i$ 之前的所有点都在同一条链上，而 $h_{i+1}$ 在另一条链上，那 $h_i$ 一定是一条链的结尾，$h_{i+1}$ 一定是另一条链的开头。

那么所有链就会头尾相连，必定形成一个每条边都重复两次的环。

然后用树上差分和倍增维护一下就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,K,s,u,v,h[N],d[N];
int head[N],nxt[N<<1],to[N<<1],cnt;
inline void add(int x,int y){
    to[++cnt]=y;
    nxt[cnt]=head[x];
    head[x]=cnt;
}
int fa[N][21],dep[N],id[N],tot;
void dfs(int k){
    for(int i(1);i<=20;++i)
        fa[k][i]=fa[fa[k][i-1]][i-1];
    id[k]=++tot;
    for(int i(head[k]);i;i=nxt[i])
        if(!id[to[i]]){
            fa[to[i]][0]=k;
            dep[to[i]]=dep[k]+1;
            dfs(to[i]);
        }
}
inline int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i(20);~i;--i){
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
        if(x==y) return x;
    }
    for(int i(20);~i;--i)
        if(fa[x][i]^fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    return fa[x][0];
}
inline bool cmp(const int&a,const int&b){
    return id[a]<id[b];
}
vector <int> vec;
void CCF(int k,int f){
    for(int i(head[k]);i;i=nxt[i])
        if(to[i]^f){
            CCF(to[i],k);
            d[k]+=d[to[i]];
            if(d[to[i]]>=2*K) vec.push_back(i+1>>1);
        }
}
int main(){
    scanf("%d%d%d",&n,&m,&K);
    for(int i(1);i<n;++i){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dep[1]=1;dfs(1);
    for(int i(1);i<=m;++i){
        scanf("%d",&s);
        for(int j(1);j<=s;++j) scanf("%d",&h[j]);
        sort(h+1,h+1+s,cmp);
        for(int j(1);j<s;++j){
            ++d[h[j]];
            ++d[h[j+1]];
            d[LCA(h[j],h[j+1])]-=2;
        }	
        ++d[h[1]];
        ++d[h[s]];
        d[LCA(h[1],h[s])]-=2;
    }
    CCF(1,0);printf("%d\n",vec.size());sort(vec.begin(),vec.end());
    for(int i(0);i<vec.size();++i) printf("%d ",vec[i]);puts("");
    return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：0)

### 题意

> 给定一棵 $n$ 个点的树。有 $m$ 个人，每个人给出一些点，标记恰好连通这些点的边。问有多少边是至少 $k$ 个人标记的，并输出这些点。

> $n\le 10^5,k\le m\le 5\times 10^4$。

### 题解

对于每个人，分别建出[虚树](https://oi-wiki.org/graph/virtual-tree/)，然后相当于对所有虚树上的边 $(u,v)$，把原树上 $(u,v)$ 之间的路径中所有边添加一层标记。

然后扫一遍所有边统计标记次数即可。对于离线的路径加法可以使用树上差分。

复杂度 $O(n\log n)$，如果使用 $O(1)$ 求 LCA可以做到 $O(n)$。

### 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
vector<int> edge[100005];
int ex[100005],ey[100005];
int dep[100005],fa[100005][20];
int st[100005],tp;
int dfn[100005],cnt;
int a[100005];
int val[100005];
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
void dfs(int x,int f){
	dfn[x]=++cnt;
	fa[x][0]=f;dep[x]=dep[f]+1;
	for(int y:edge[x])if(y!=f)dfs(y,x);
}
int LCA(int x,int y){
	int k=16;
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y]){
		if(dep[fa[x][k]]>=dep[y])x=fa[x][k];
		k--;
	}
	if(x==y)return x;
	k=16;
	while(k>=0){
		if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
		k--;
	}
	return fa[x][0];
}
void addedge(int x,int y){
	val[x]++,val[y]--;
}
void dfs1(int x,int f){
	for(int y:edge[x])if(y!=f){
		dfs1(y,x);
		val[x]+=val[y];
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
		ex[i]=x,ey[i]=y;
	}
	dfs(1,0);
	for(int i=1;i<n;i++)if(dep[ex[i]]>dep[ey[i]])swap(ex[i],ey[i]);
	// 让 ey 表示深度较大的端点，方便统计
	for(int j=1;j<=16;j++)for(int i=1;i<=n;i++)fa[i][j]=fa[fa[i][j-1]][j-1];
	while(m--){
		int s;scanf("%d",&s);
		for(int i=1;i<=s;i++)scanf("%d",&a[i]);
		sort(a+1,a+s+1,cmp);
		st[tp=1]=a[1];for(int i=2;i<=s;i++)st[1]=LCA(st[1],a[i]);
		for(int i=(a[1]==st[1]?2:1);i<=s;i++){
			int lca=LCA(a[i],st[tp]);
			if(lca==st[tp]){
				if(a[i]!=st[tp])st[++tp]=a[i];
			}else{
				while(tp>1&&dep[st[tp-1]]>dep[lca])addedge(st[tp],st[tp-1]),tp--;
				addedge(st[tp],lca);tp--;
				if(lca!=st[tp])st[++tp]=lca;
				if(a[i]!=st[tp])st[++tp]=a[i];
			}
		}
		while(tp>1)addedge(st[tp],st[tp-1]),tp--;
	}
	dfs1(1,0);
	int ans=0;
	for(int i=2;i<=n;i++)if(val[i]>=k)ans++;
	printf("%d\n",ans);
	for(int i=1;i<n;i++)if(val[ey[i]]>=k)printf("%d ",i);puts("");
	return 0;
}
```

---

## 作者：Dita (赞：0)

[题面](https://www.luogu.com.cn/problem/P6572)

**solution**

大部分题解都用的虚树，可是本~~蒟蒻~~ 不会用虚树，只好用差分水过去了。

**subtask4:**  

$s_i = 2$ 

最基础的树的差分。

每个部长所选的两个点之间的边在树上构成一条路径，对每条路径上的边都 $+1$，最后找出经过次数大于等于 $k$ 的边就好了。

路径修改用差分即可。

[code](https://www.luogu.com.cn/paste/d54c5nqz)

$s_i > 2$ 

还是考虑用上面的方法。

与上面不同的是这里要想把一个部长所选的点都连起来，所需要的边不再是一条路径了，考虑怎么对这些边进行修改。

来看样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/y7dvncz6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于一号部长的点：1 3 2 5 

目的：对红色的边都 +1。

一个神奇的操作：

**先对所有点按照 dfs 序进行排序，然后把每相邻两个点的路径上的边 +1，第一个和最后一个点的路径上的边也要 +1**

模一下样例：

按照 $dfs$ 序排好序就是 1 3 5 2

对 $1\sim3$ 路径 $+1$，$3\sim 5$ 路径 $+1$，$5\sim2$ 路径 $+1$，$2 \sim 1$ 路径 $+1$。

加完之后会发现每条红色的边都被加了两次。

每个部长都操作完之后，把每条边除以 $2$，然后找大于等于 $k$ 的边就好了。

**code**

```c++
/*
work by:Ariel_
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>
#define ll long long
#define rg register
using namespace std;
const int MAXN = 1e5 + 5;
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, m, k, a[MAXN], vis[MAXN], ans, dfn[MAXN], tot, cnt;
struct Question{
   int x, id;
   bool operator < (const Question &rhs)const{
       return id < rhs.id; 
   } 
}q[MAXN];
struct edge{int v, nxt, val, id;}e[MAXN << 1];
int E = 1, head[MAXN];
void add_edge(int u, int v, int id) {
   e[++E] = (edge) {v, head[u], 0, id};
   head[u] = E;
}
namespace LCA{
   int dep[MAXN], son[MAXN], top[MAXN], siz[MAXN], fa[MAXN];
   void dfs(int x, int f) {
   	  dep[x] = dep[f] + 1, siz[x] = 1, fa[x] = f, dfn[x] = ++tot;
   	  for (int i = head[x]; i; i = e[i].nxt) {
   	  	    int v = e[i].v;
   	  	    if (v == f) continue;
   	  	    dfs(v, x);
   	  	    siz[x] += siz[v];
   	  	    if (siz[son[x]] < siz[v]) son[x] = v;
		}
   }
   void dfs2(int x, int tp) {
   	  top[x] = tp;
   	  if(son[x]) dfs2(son[x], tp);
   	  for (int i = head[x]; i; i = e[i].nxt) {
   	       int v = e[i].v;
		   if (v == son[x] || v == fa[x]) continue;
		   dfs2(v, v);	 
	   }
   }
   int lca(int x, int y) {
   	  while (top[x] != top[y]) {
   	      if (dep[top[x]] < dep[top[y]]) swap(x, y);
   	      x = fa[top[x]];
	   }
	   if (dep[x] > dep[y]) swap(x, y);
	   return x;
   }
}
using namespace LCA;
void work(int u) {
   for (int i = head[u]; i; i = e[i].nxt) {
   	    int v = e[i].v;
   	    if (v == fa[u]) continue;
		work(v); 
   	    e[i].val += a[v], e[i ^ 1].val += a[v];
   	    a[u] += a[v];
   }
}
int main(){
   memset(e, 0, sizeof e);
   n = read(), m = read(), k = read();
   for (int i = 1, u, v; i < n; i++) {
   	  u = read(), v = read();
   	  add_edge(u, v, i), add_edge(v, u, i);
   }
   dfs(1, 0), dfs2(1, 1);
   for (int i = 1; i <= m; i++) {
   	  int s = read();cnt = 0;
	  for(int j = 1; j <= s; j++) q[++cnt].x = read();
	  for (int j = 1; j <= cnt; j++) q[j].id = dfn[q[j].x];
	  sort(q + 1, q + cnt + 1);
	  int last = q[1].x;
      for (int j = 2; j <= cnt; j++) {
   	     a[last]++, a[q[j].x]++;
   	     a[lca(last, q[j].x)] -= 2;
   	     last = q[j].x;
       }
      a[q[cnt].x]++, a[q[1].x]++;
      a[lca(q[cnt].x, q[1].x)] -= 2;
   }
   work(1);
   for (int i = 1; i <= E; i++) {
   	   if((e[i].val / 2) >= k) vis[e[i].id] = 1;	
   }
   for (int i = 1; i < n; i++)if (vis[i]) ans++; 
   cout<<ans<<"\n";
   for (int i = 1; i < n; i++) if(vis[i]) printf("%d ",  i);
   puts("");
   return 0;
}
```



---

## 作者：lytqwq (赞：0)

考虑只有一个副部长，我们可以从 lca 开始向下 dfs ，把所有经过的边的次数 +1 ，直到子树里没有需要被相连 。


多个副部长的话，上面的方法复杂度太高，我们建虚树，更新边的次数我们用树上差分，最后统计一遍就完事了 。

线性复杂度，随便过 。

AC情况 ：[https://www.luogu.com.cn/record/48258894](https://www.luogu.com.cn/record/48258894)

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int n,m,k;
int Head[N],Next[N<<1],V[N<<1],cnt;
void add(int u,int v){V[cnt]=v;Next[cnt]=Head[u];Head[u]=cnt++;}
int h[N],S;
int ou[N<<1],top2,dfn[N],depth[N];
void dfs(int u,int fa){
	depth[u]=depth[fa]+1;ou[++top2]=u;dfn[u]=top2;
	for(int i=Head[u];i!=-1;i=Next[i])if(V[i]!=fa)dfs(V[i],u),ou[++top2]=u;
}
int st[N][20],Log[N];
int calc(int x,int y){return depth[ou[x]]>depth[ou[y]]?y:x;}
void ST(){
	Log[0]=-1;
	for(int i=1;i<=top2;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=top2;i++)st[i][0]=i;
	for(int j=1;(1<<j)<=top2;j++)for(int i=1;i+(1<<j)-1<=top2;i++)st[i][j]=calc(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int LCA(int x,int y){
	int fx=dfn[x],fy=dfn[y];
	if(fx>fy)swap(fx,fy);
	int k=Log[fy-fx+1];
	return ou[calc(st[fx][k],st[fy-(1<<k)+1][k])];
}
struct VirtualTree{
	int Head[N],Next[N<<1],V[N<<1],cnt;
	void add(int u,int v){V[cnt]=v;Next[cnt]=Head[u];Head[u]=cnt++;}
}g;
bool cmp(int x,int y){return dfn[x]<dfn[y];}
int sta[N],top,h1;
void build(){
	h1=0;sort(h+1,h+S+1,cmp);
	sta[top=1]=1,g.cnt=0,g.Head[1]=-1;
	for(int i=1,l;i<=S;i++){
		if(h[i]!=1){
			l=LCA(sta[top],h[i]);
			if(l==1&&sta[top]!=1)h1=1;
			if(l!=sta[top]){
				while(dfn[sta[top-1]]>dfn[l])g.add(sta[top-1],sta[top]),top--;
				if(dfn[l]>dfn[sta[top-1]])g.Head[l]=-1,g.add(l,sta[top]),sta[top]=l;
				else g.add(l,sta[top--]);
			}
			g.Head[h[i]]=-1;sta[++top]=h[i];
		}
		else h1=1;
	}
	for(int i=1;i<top;i++)g.add(sta[i],sta[i+1]);
}
int sum[N];
void doit(int u,int fa){
	int kk=0;
	for(int i=g.Head[u];i!=-1;i=g.Next[i]){
		if(g.V[i]!=fa){
			doit(g.V[i],u);
			kk++;
		}
	}
	sum[u]+=1-kk;
}
int ans[N],topans;
void dfs2(int u,int fa){
	for(int i=Head[u];i!=-1;i=Next[i]){
		if(V[i]!=fa){
			dfs2(V[i],u);
			if(sum[V[i]]>=k)ans[++topans]=i/2+1;
			sum[u]+=sum[V[i]];
		}
	}
}
int main(){
	memset(Head,-1,sizeof(Head));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n-1;i++){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs(1,0);ST();
	for(int o=1;o<=m;o++){
		scanf("%d",&S);
		for(int i=1;i<=S;i++)scanf("%d",&h[i]);
		build();
		if(h1)doit(1,0);
		else for(int i=g.Head[1];i!=-1;i=g.Next[i])sum[g.V[i]]--,doit(g.V[i],1);
	}
	dfs2(1,0);
	printf("%d\n",topans);
	sort(ans+1,ans+topans+1);
	for(int i=1;i<=topans;i++)printf("%d ",ans[i]);
	printf("\n");
}
```


---

## 作者：fanypcd (赞：0)

### 题意：

给定一棵树，有 $m$ 次操作，每次选取一些点，并将树上连接这些点的边标记一次。

求操作完后标记次数不少于 $k$ 的边有哪些。

### 分析：

回顾一下虚树的构建过程：舍弃无用的部分，将根、所有点、两两点的 lca 加入虚树。

发现这道题中选点后需要标记的边是原树中保留必要信息（节点的父子关系）的部分，也就是虚树中的**部分**边。

为什么是**部分**呢，因为根节点（通常是 1 号节点）是默认加入虚树的，但有可能并不会需要标记其他节点到 1 的边。

需要统计其他节点到 1 的边的情况当且仅当 1 号节点是某两个节点的 lca。

如果 1 号节点本来就被选中，或者它在虚树上至少有 2 个儿子（即它作为了某两点的 lca 被选中），那么需要标记 1 号到儿子之间的路径。

除此之外，还需要标记其它所有点之间的路径，（边的标记值下放到点）树上差分即可。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
template <class T> inline void read(T &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + (ch - 48);
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define inf 0x3f3f3f3f
#define N 100005
struct Graph
{
	int first[N], Next[N << 1], to[N << 1], tot = 1;
	inline void add(int x, int y)
	{
//		printf("!%d -> %d\n!", x, y);
		Next[++tot] = first[x];
		first[x] = tot;
		to[tot] = y;
		return;
	}
};
Graph Ori, Vir;
int dfn[N], sign, dep[N], fa[N][21];
void dfs(int u, int pre)
{
	dfn[u] = ++sign;
	for(int i = Ori.first[u]; i; i = Ori.Next[i])
	{
		int v = Ori.to[i];
		if(v == pre)
		{
			continue;
		}
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		dfs(v, u);
	}
	return;
}
int n, m, K;
inline void init()
{
	dep[1] = 1;
	dfs(1, 0);
	for(int j = 1; j <= 20; j++)
	{
		for(int i = 1; i <= n; i++)
		{
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
		}
	}
	return;
}
int lca(int x, int y)
{
	if(dep[x] > dep[y])
	{
		swap(x, y);
	}
	for(int i = 20; i >= 0; i--)
	{
		if(dep[fa[y][i]] >= dep[x])
		{
			y = fa[y][i];
		}
	}
	if(x == y)
	{
		return x;
	}
	for(int i = 20; i >= 0; i--)
	{
		if(fa[x][i] != fa[y][i])
		{
			x = fa[x][i], y = fa[y][i];
		}
	}
	return fa[x][0];
}
int st[N], top;
int a[N];
void build(int siz)
{
	st[top = 1] = 1;
	for(int i = 1; i <= siz; i++)
	{
		int now = a[i], lc = lca(st[top], a[i]);
		while(1)
		{
			if(dep[lc] < dep[st[top - 1]])
			{
				Vir.add(st[top - 1], st[top]);
				top--;
			}
			else if(dep[lc] < dep[st[top]])
			{
				Vir.add(lc, st[top]);
				top--;
			}
			else
			{
				break;
			}
		}
		if(st[top] != lc)
		{
			st[++top] = lc;
		}
		if(st[top] != now)
		{
			st[++top] = now;
		}
	}
	while(--top)
	{
		Vir.add(st[top], st[top + 1]);
	}
	return;
}
int ans[N];
int flag;
void solve(int u)
{
	for(int i = Vir.first[u]; i; i = Vir.Next[i])
	{
		int v = Vir.to[i];
		solve(v);
		if(u != 1 || (u == 1 && flag))
		{
			ans[v]++, ans[u]--;
		}
	}
	Vir.first[u] = 0;
	return;
}
int prt[N], cnt;
void calc(int u, int pre)
{
	for(int i = Ori.first[u]; i; i = Ori.Next[i])
	{
		int v = Ori.to[i];
		if(v == pre)
		{
			continue;
		}
		calc(v, u);
		if(ans[v] >= K)
		{
			prt[++cnt] = i >> 1;
		}
		ans[u] += ans[v];
	}
	return;
}
bool cmp(const int &a, const int &b)
{
	return dfn[a] < dfn[b];
}
signed main()
{
	read(n), read(m), read(K);
	int u, v;
	for(int i = 1; i < n; i++)
	{
		read(u), read(v);
		Ori.add(u, v), Ori.add(v, u);
	}
	init();
	int siz;
	while(m--)
	{
		read(siz);
		for(int i = 1; i <= siz; i++)
		{
			read(a[i]);
		}
		sort(a + 1, a + siz + 1, cmp);
		build(siz);
		flag = (a[1] == 1) || Vir.Next[Vir.first[1]];
		solve(1);
	}
	calc(1, 0);
	sort(prt + 1, prt + cnt + 1);
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i++)
	{
		printf("%d ", prt[i]);
	}
	return 0;
}
```

---

