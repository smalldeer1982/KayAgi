# [JOIST 2023] 两种货币 / Two Currencies

## 题目描述

在 JOI 王国中，有 $n$ 个城市，编号从 $1$ 到 $n$。JOI 王国有 $n−1$ 条双向道路，编号从 $1$ 到 $n−1$。第 $i$ 条道路连接城市 $a_i$ 和城市 $b_i$。

在 JOI 王国中，一些道路上放有检查站。有 $m$ 个检查站，编号从 $1$ 到 $m$。第 $j$ 个检查站位于道路 $p_j$ 上。通过该检查站需要支付 $1$ 枚金币或 $c_j$ 枚银币。

在 JOI 王国有 $q$ 名公民，编号从 $1$ 到 $q$。第 $k$ 名公民持有 $x_k$ 枚金币和 $y_k$ 枚银币，并希望从城市 $s_k$ 前往城市 $t_k$。由于金币具有较高的价值，所有公民都希望尽可能多地保留金币。

编写一个程序，给定 JOI 王国中的城市、道路、检查站和公民信息，对于每个 $k (1≤k≤q)$，判断公民 $k$ 是否能够从城市 $s_k$ 前往城市 $t_k$，并在此条件成立时计算公民 $k$ 所能保留的最多金币数。

## 说明/提示

数据范围：$2\le N\le 10^5$，$1\le M,Q\le 10^5$，$1\le A_i,B_i\le N$，$1\le P_i\le N-1$，$1\le C_j\le 10^9$，$1\le S_k,T_k\le N$，$S_k\neq T_k$，$0\le X_k\le 10^9$，$0\le Y_k\le 10^{18}$，所有数都是整数，所有城市连通。

Subtasks：
- Subtask 1（10 分）：$N,M,Q\le 2000$。
- Subtask 2（28 分）：$C_1=C_2=\cdots=C_M$。
- Subtask 3（30 分）：$A_i=i$，$B_i=i+1$。
- Subtask 4（32 分）：无特殊限制。

## 样例 #1

### 输入

```
5 4 3
1 2
1 3
2 4
2 5
2 9
2 4
3 5
4 7
3 4 2 11
5 3 4 5
2 3 1 1
```

### 输出

```
1
2
-1
```

## 样例 #2

### 输入

```
10 7 9
1 8
6 3
5 9
7 9
3 1
3 4
10 1
2 6
5 6
9 4
7 4
7 4
2 4
7 4
7 4
1 4
8 6 5 3
3 9 8 0
4 7 6 15
7 4 9 3
6 4 8 0
9 10 5 16
5 3 2 4
2 8 4 3
6 1 3 3
```

### 输出

```
3
6
6
7
7
3
1
2
2
```

## 样例 #3

### 输入

```
8 7 11
1 2
2 3
3 4
4 5
5 6
6 7
7 8
4 4
3 7
2 10
5 2
4 1
4 4
5 6
6 3 7 69
7 1 5 55
3 1 6 8
8 2 5 45
4 6 4 45
6 1 3 33
2 1 0 19
3 7 2 31
7 1 2 31
7 2 4 58
8 3 5 63
```

### 输出

```
7
5
5
5
4
2
0
2
1
4
5
```

## 样例 #4

### 输入

```
8 7 11
1 8
1 4
3 1
3 6
6 7
2 1
5 2
5 5
5 8
4 7
6 6
4 1
6 4
1 7
4 7 2 18
2 4 5 1
4 2 1 32
1 5 7 21
2 5 0 50
8 4 4 33
1 7 6 16
4 8 7 18
1 2 8 13
5 4 10 42
7 1 6 40
```

### 输出

```
1
3
1
7
0
4
5
7
8
10
6```

# 题解

## 作者：H_Kaguya (赞：5)

单纯的追求优秀的复杂度。  
如果只是想做完这道题可以忽略本文。  

前置知识：[整体二分](https://oi-wiki.org/misc/parallel-binsearch/)。  

首先，这道题的经典做法是树上主席树，时间空间都是 $O(n \log n)$。  

但事实上这道题可以使用整体二分做到 $O(n \log n)$ 的时间复杂度和 $O(n)$ 的空间复杂度。  

整体二分的话还是常规思路，我们去枚举一个值 $mid$，即只在 $c_i \le mid$ 的时候使用银币。  
如果想要做到 $O(n \log n)$ 的复杂度，那么复杂度应该是 $T(x) = 2T(\frac{x}{2}) + O(x)$，也就是链求和的部分要做到线性。  
不能使用带 $\log$ 的数据结构维护，那么就考虑树上前缀和。  

我们需要保证每次只对有用的点做前缀和。  
所以容易想到虚树。  

具体的，我们可以把所有费用在当前二分区间内的点拿出来建虚树。  
同时，对于每个树链询问，都可以差分成 $O(1)$ 个树上前缀询问。  
把这些点也放到虚树上。  
分治的时候把点按照费用大小递归到两边即可。  

实现细节的话，首先需要把所有的点按照 DFN 序排好，分裂的时候不打乱相对顺序以避免建虚树的时候排序。  
另外，需要接一个 $O(1)$ LCA，使用单调栈建虚树。  

常数很大，仅分析理论复杂度就好了。  

---

## 作者：lyreqwq (赞：2)

建主席树，然后二分出最大的 $L$，只用银币能解决花费在 $[0, L]$ 的所有收费站。

然后看剩下的银币能解决多少收费为 $L + 1$ 的收费站。

主席树上二分不难做到 $O((n + q)\log V)$。

```cppp
# include <bits/stdc++.h>

using namespace std;

namespace lyre {
  constexpr int nmax = 100'100;
  constexpr int V = 1'000'000'000;
  constexpr int Lg = __lg(nmax) + 1;
  int n, m, q;
  vector<int> buc[nmax];
  pair<int, int> e[nmax];
  int dfn[nmax], par[nmax];
  int root[nmax];
  vector<int> G[nmax];
  pair<int, int> st[Lg][nmax];
  namespace seg {
    struct info {
      int cnt; long sum;
      constexpr info() : cnt(), sum() {}
      constexpr info(int c, long s) : cnt(c), sum(s) {}
      constexpr info operator+(info const &o) const
      { return info(cnt + o.cnt, sum + o.sum); }
      constexpr info operator-(info const &o) const
      { return info(cnt - o.cnt, sum - o.sum); }
      constexpr info operator*(int const x) const
      { return info(cnt * x, sum * x); }
    } tr[120 * nmax];
    int ch[2][120 * nmax], index = 0;
    void ins(int &u, int l, int r, int x) {
      auto pre = u; u = ++index;
      tr[u] = tr[pre] + info(1, x);
      ch[0][u] = ch[0][pre];
      ch[1][u] = ch[1][pre];
      if (l == r) return;
      auto mid = (l + r) / 2;
      if (x <= mid) ins(ch[0][u], l, mid, x);
      else ins(ch[1][u], mid + 1, r, x);
    }
    int find(int u, int v, int w, int l, int r, long k) {
      if (l == r) return l;
      auto mid = (l + r) / 2;
      auto t = tr[ch[0][u]].sum + tr[ch[0][v]].sum - 2 * tr[ch[0][w]].sum;
      if (k < t) return find(ch[0][u], ch[0][v], ch[0][w], l, mid, k);
      return find(ch[1][u], ch[1][v], ch[1][w], mid + 1, r, k - t);
    }
    info qsum(int u, int v, int w, int l, int r, int x, int y) {
      if (l == x && r == y) return tr[u] + tr[v] - tr[w] * 2;
      auto mid = (l + r) / 2;
      if (y <= mid) {
        return qsum(ch[0][u], ch[0][v], ch[0][w], l, mid, x, y);
      } else if (x > mid) {
        return qsum(ch[1][u], ch[1][v], ch[1][w], mid + 1, r, x, y);
      } else {
        return qsum(ch[0][u], ch[0][v], ch[0][w], l, mid, x, mid)
             + qsum(ch[1][u], ch[1][v], ch[1][w], mid + 1, r, mid + 1, y);
      }
    }
  }
  void search0(int x, int o) {
    static auto index = 0;
    dfn[x] = ++index, par[x] = o;
    st[0][dfn[x]] = make_pair(dfn[o], o);
    for (auto y : G[x]) {
      if (y == o) continue;
      search0(y, x);
    }
  }
  void search1(int x, int o) {
    root[x] = root[o];
    for (auto i : buc[x])
      seg::ins(root[x], 0, V, i);
    for (auto y : G[x]) {
      if (y == o) continue;
      search1(y, x);
    }
  }
  int lca(int x, int y) {
    if (x == y) return x;
    if ((x = dfn[x]) > (y = dfn[y])) swap(x, y);
    auto k = __lg(y - x++);
    return min(st[k][x], st[k][y - (1 << k) + 1]).second;
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i < n; ++i) {
      auto &[x, y] = e[i];
      cin >> x >> y;
      G[x].push_back(y);
      G[y].push_back(x);
    }
    search0(1, 0);
    for (int i = 0; i < __lg(n); ++i) {
      for (int j = 1; j + (1 << (i + 1)) - 1 <= n; ++j)
        st[i + 1][j] = min(st[i][j], st[i][j + (1 << i)]);
    }
    for (int i = 0; i < m; ++i) {
      int p, c;
      cin >> p >> c;
      auto [x, y] = e[p];
      if (par[y] == x) swap(x, y);
      buc[x].push_back(c);
    }
    search1(1, 0);
    for (int i = 0; i < q; ++i) {
      int u, v; long x, y;
      cin >> u >> v >> x >> y;
      auto w = lca(u, v);
      auto l = seg::find(root[u], root[v], root[w], 0, V, y) - 1;
      y -= seg::qsum(root[u], root[v], root[w], 0, V, 0, l).sum;
      auto r = seg::qsum(root[u], root[v], root[w], 0, V, l + 1, l + 1);
      auto t = min(r.cnt, int(y / (l + 1)));
      y -= 1l * t * (l + 1), x += t;
      x -= seg::qsum(root[u], root[v], root[w], 0, V, l + 1, V).cnt;
      cout << max(x, -1l) << '\n';
    }
  }
}

int main() { lyre::main(); }
```

---

## 作者：rubbishZZZ (赞：1)

## Two Currencies

#### 题意：

- 有一个王国，道路形成了一棵树，这些道路上有一些检查站。第 $i$ 个检查站位于第 $p_i$ 条边，通过它需要花费 $1$ 枚金币或 $c_i$ 枚银币。有 $Q$ 次询问，有个人想从 $u$ 走到 $v$，他有 $x$ 枚金币和 $y$ 枚银币，求这个人走到 $v$ 后最多剩几枚金币或报告不存在。



#### 解法：

- 我们将路径上的所有检查站的 $c$ 拿出来并排序，那么我们一定是优先选 $c$ 最小的并用银币通过，如果银币不够了再使用金币。因此是选出排序后 $c$ 尽可能长的前缀满足前缀和 $\leq y$，那么至少需要花费 $x-后缀长度$ 的金币。

  维护这个东西，可以离散化后使用主席树，那么选前缀这个过程就是一个主席树上二分，时间复杂度 $O(n\log n)$。

  上述做法时空复杂度均为 $O(n\log n)$，事实上我们可以通过整体二分得到时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$ 的做法。具体的，我们在整体二分过程中，只保留需要的节点，通过单调栈线性建立虚树，然后使用前缀和即可完成判断。



#### 代码：

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}

const int N=100005;
int n,m,Q,dep[N],fa[N][20],lsh[N],top,rt[N];
pii edg[N];
vector<int>add[N],e[N];
void dfs(int u,int fat){
	dep[u]=dep[fat]+1,fa[u][0]=fat;
	rep(i,1,16)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:e[u])if(v^fat)dfs(v,u);
}
struct SGT{
	int sum[N<<6],sz[N<<6],ls[N<<6],rs[N<<6],tot;
	void pushup(int u){sum[u]=sum[ls[u]]+sum[rs[u]],sz[u]=sz[ls[u]]+sz[rs[u]];}
	void upd(int l,int r,int p,int&u,int v){
		u=++tot;ls[u]=ls[v],sz[u]=sz[v],rs[u]=rs[v],sum[u]=sum[v];
		if(l==r)return sum[u]+=lsh[p],sz[u]++,void();
		int mid=(l+r)>>1;
		if(mid>=p)upd(l,mid,p,ls[u],ls[v]);
		else upd(mid+1,r,p,rs[u],rs[v]);
		pushup(u);
	}
	int query(int l,int r,int k,int a,int b,int c,int d){
		if(l==r){
			if(k/lsh[l]>sz[a]+sz[b]-sz[c]-sz[d])return 0;
			return sz[a]+sz[b]-sz[c]-sz[d]-k/lsh[l];
		}
		int mid=(l+r)>>1;
		int tmp=sum[ls[a]]+sum[ls[b]]-sum[ls[c]]-sum[ls[d]];
		if(tmp<=k)return query(mid+1,r,k-tmp,rs[a],rs[b],rs[c],rs[d]);
		return sz[rs[a]]+sz[rs[b]]-sz[rs[c]]-sz[rs[d]]+query(l,mid,k,ls[a],ls[b],ls[c],ls[d]);
	}
}sgt;
void dfs2(int u,int fat){
	rt[u]=rt[fat];
	for(int x:add[u])sgt.upd(1,top,lower_bound(lsh+1,lsh+top+1,x)-lsh,rt[u],rt[u]);
	for(int v:e[u])if(v^fat)dfs2(v,u);
}
int LCA(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	per(i,16,0)if(dep[fa[u][i]]>=dep[v])u=fa[u][i];
	if(u==v)return u;
	per(i,16,0)if(fa[u][i]^fa[v][i])u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

bool Med;
signed main() {
//	fprintf(stderr,"%.3LfMb\n",(&Mbe-&Med)/1024./1024.);
	n=read(),m=read(),Q=read();
	rep(i,1,n-1){
		int u=read(),v=read();
		e[u].eb(v),e[v].eb(u);
		edg[i]=MP(u,v);
	}
	dfs(1,0);
	rep(i,1,m){
		int x=read(),u=edg[x].fi,v=edg[x].se,c=read();
		if(dep[u]<dep[v])swap(u,v);
		add[u].eb(c),lsh[++top]=c;
	}
	sort(lsh+1,lsh+top+1);
	top=unique(lsh+1,lsh+top+1)-lsh-1;
	dfs2(1,0);
	rep(i,1,Q){
		int u=read(),v=read(),x=read(),y=read(),lca=LCA(u,v);
		int k=sgt.query(1,top,y,rt[u],rt[v],rt[lca],rt[lca]);
		if(k>x)printf("-1\n");
		else printf("%lld\n",x-k);
	}
	return 0;
}
```

---

## 作者：xxseven (赞：0)

树上主席树练手题。

对于单次询问，可以取出路径上所有的检查点，贪心地选取 $c_j$ 更小的点付银币，剩下的检查点付金币。

拓展到多次询问，我们想要快速地获得一条路径上检查站形成的桶。

仿照序列上获得区间桶信息的方法，我们建出主席树，每个节点上的版本维护**其到根的链**上的信息。这样，我们只需使用树上差分，用 $u,v,\operatorname{LCA}(u,v)$ 版本的树相加减即可得到路径信息。

$n,m,q$ 同阶，时空复杂度均为 $O(n \log n)$。

如果想要再做一道练手，可以尝试 [P2633 Count on a tree](https://www.luogu.com.cn/problem/P2633)。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6;
typedef long long i64;
int n,m,q;
vector<pair<int,int> > f[N];
vector<int> g[N];

struct node{
	int l,r,num;
	i64 sum;
}t[N<<6];
int rt[N],idx;
#define mid (L+R>>1)
void upd(int &pos,int pre,int L,int R,int x){
	pos=++idx; t[pos]=t[pre]; 
	t[pos].sum+=x; t[pos].num++;
	if(L==R) return;
	if(x<=mid) upd(t[pos].l,t[pre].l,L,mid,x);
	else upd(t[pos].r,t[pre].r,mid+1,R,x);
}
int qry(int pos,int pos2,int pos3,int L,int R,i64 k){
	if(L==R) return t[pos].num+t[pos2].num-t[pos3].num*2-(k/L);
	i64 now=t[t[pos].l].sum+t[t[pos2].l].sum-t[t[pos3].l].sum*2;
	int num=t[t[pos].r].num+t[t[pos2].r].num-t[t[pos3].r].num*2;
	if(now<=k) return qry(t[pos].r,t[pos2].r,t[pos3].r,mid+1,R,k-now);
	return qry(t[pos].l,t[pos2].l,t[pos3].l,L,mid,k)+num;
}

int dep[N],top[N],siz[N],son[N],fa[N];
void dfs(int x,int y){
	dep[x]=dep[y]+1; fa[x]=y; siz[x]=1;
	for(auto e:f[x]){
		int u=e.first,id=e.second;
		if(u==y) continue;
		rt[u]=rt[x]; 
		for(int v:g[id]) upd(rt[u],rt[u],1,1e9,v);
		dfs(u,x); siz[x]+=siz[u];
		if(siz[u]>siz[son[x]]) son[x]=u;
	}
}
void dfs2(int x,int y){
	top[x]=y;
	if(son[x]) dfs2(son[x],y);
	for(auto e:f[x]){
		int u=e.first;
		if(!top[u]) dfs2(u,u);
	}
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>q;
	for(int x,y,i=1;i<n;++i) {
		cin>>x>>y;
		f[x].push_back({y,i});
		f[y].push_back({x,i});
	}
	for(int x,y,i=1;i<=m;++i) {
		cin>>x>>y;
		g[x].push_back(y);
	}
	dfs(1,0); dfs2(1,1);
	for(i64 s,t,x,y,i=1;i<=q;++i) {
		cin>>s>>t>>x>>y;
		int l=lca(s,t);
		cout<<max(-1ll,x-max(0,qry(rt[s],rt[t],rt[l],1,1e9,y)))<<'\n';
	}
	return 0;
}


```

希望这篇题解能够帮到你！

---

## 作者：shenxinge (赞：0)

一个比较套路的做法。

考虑贪心，你肯定只会取路径上银币从小到大排序后的一段前缀，所以直接主席树维护根到 $u$ 的所有检查点的银币的桶，然后树上差分得到 $u$ 和 $v$ 路径上的桶，主席树上二分查找最多能支付的银币个数，然后只需要考虑金币数量是否够用即可。

时间复杂度 $O(n \log{n})$，空间复杂度 $O(n \log{n})$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std; constexpr int maxn(1e5+10),maxv(1e9);
int n,m,q,f[maxn]; vector<pair<int,int> > vec[maxn]; vector<int> cost[maxn];
int dep[maxn],sz[maxn],son[maxn],rt[maxn],segcnt,top[maxn],fa[maxn];
struct tree_node{ int ls,rs,cnt,sum; }tr[maxn<<5];
#define ls(x) tr[x].ls
#define rs(x) tr[x].rs
#define cnt(x) tr[x].cnt
#define sum(x) tr[x].sum
#define lson(x) l,mid,ls(x)
#define rson(x) mid+1,r,rs(x)
inline void push_up(int rt){
	cnt(rt)=cnt(ls(rt))+cnt(rs(rt)),
	sum(rt)=sum(ls(rt))+sum(rs(rt));
}
inline int new_node(int x){
	int rt=++segcnt; tr[rt]=tr[x]; return rt;
}
inline void insert(int p,int l,int r,int &rt){
	rt=new_node(rt); if(l==r) return cnt(rt)++,sum(rt)+=l,void();
	int mid=(l+r)>>1; if(p<=mid) insert(p,lson(rt)); else insert(p,rson(rt));
	push_up(rt);
}
inline int query(int k,int y,int z,int l,int r,int rt){
	int lcnt=cnt(ls(rt))+cnt(ls(y))-2*cnt(ls(z)),
		lsum=sum(ls(rt))+sum(ls(y))-2*sum(ls(z)),
		mid=(l+r)>>1;
	if(l==r) return min(k/l,cnt(rt)+cnt(y)-2*cnt(z));
	if(lsum<=k) return lcnt+query(k-lsum,rs(y),rs(z),rson(rt));
	else return query(k,ls(y),ls(z),lson(rt));
}
#define root(x) 1,maxv,rt[x]
inline void dfs(int u,int fa){ dep[u]=dep[fa]+1,::fa[u]=fa,sz[u]=1;
	for(auto E:vec[u]){ int v,id; tie(v,id)=E; if(v==fa) continue;
		rt[v]=rt[u],f[v]=f[u]; for(int x:cost[id]) insert(x,root(v)),f[v]++;
		dfs(v,u); sz[u]+=sz[v]; if(sz[son[u]]<sz[v]) son[u]=v;
	}
}
inline void get_top(int u,int top){ ::top[u]=top; if(son[u]) get_top(son[u],top);
	for(auto E:vec[u]){ int v,id; tie(v,id)=E; if(v==son[u]||v==fa[u]) continue;
		get_top(v,v);
	}
}
inline int LCA(int u,int v){
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	} if(dep[u]>dep[v]) swap(u,v);
	return u;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin >> n >> m >> q;
	for(int i=1,u,v;i<n;i++)
		cin >> u >> v,
		vec[u].emplace_back(v,i),
		vec[v].emplace_back(u,i);
	for(int i=1,p,c;i<=m;i++)
		cin >> p >> c,cost[p].push_back(c);
	dfs(1,0),get_top(1,1);
	for(int i=1,u,v,lca,x,y;i<=q;i++){
		cin >> u >> v >> x >> y,lca=LCA(u,v);
		int ack=f[u]+f[v]-2*f[lca]-query(y,rt[v],rt[lca],root(u));
		if(x<ack) cout << "-1\n"; else cout << x-ack << '\n';
	}
	return 0;
}
```


---

## 作者：__stick (赞：0)

## 题意
给出一棵树，边上有检查点，通过检查点需要一个金币和若干银币，多次询问带着一些金币和银币从 $u\to v$ 最多能剩下多少金币，不能到达输出 $-1$。
## 思路
大概是主席树的模板，因为没有人写题解于是就来了。

首先明显的贪心是按银币数量从小到大支付，这样能保证最多，这里可以二分解决。

我们对每个节点到根节点的路径维护主席树，每个节点从父亲继承，然后树上差分出来当前询问路径的情况，然后树上二分出来最多能用银币支付的数量。

复杂度 $O(n\log n)$。

不会树上主席树的可以 P2633 Count on a tree。

这道题大概可以整体二分，就是对检查点按照银币数量排序，每次看路径中在当前区间中小于 $mid$ 的检查点总和是否合法，这样使用两个树状数组维护一下就能得到答案，复杂度 $O(n\log^2n)$。

## code
```cpp
const int MAXN=2e5+10;
vector<pii> e[MAXN];
struct node
{
    int l,r;
    int cnt;ll w;
}t[MAXN*30];
#define ls t[p].l
#define rs t[p].r
int tt;
void update(int& p,int l,int r,int qq,int w)
{
    t[++tt]=t[p];p=tt;t[p].cnt++,t[p].w+=w;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(qq<=mid)update(ls,l,mid,qq,w);
    else update(rs,mid+1,r,qq,w);
}
vi d;
ll ask(int u,int v,int p,int l,int r,ll sum)
{
    if(l==r)return min<ll>(sum/d[l-1],t[u].cnt+t[v].cnt-t[p].cnt*2);
    int mid=(l+r)>>1;
    ll lsum=t[t[u].l].w+t[t[v].l].w-t[t[p].l].w*2;
    if(lsum<=sum)return ask(t[u].r,t[v].r,rs,mid+1,r,sum-lsum)+t[t[u].l].cnt+t[t[v].l].cnt-t[t[p].l].cnt*2;
    else return ask(t[u].l,t[v].l,t[p].l,l,mid,sum);
}
vi pos[MAXN];
int c[MAXN],rt[MAXN],N;
const int K=17;
int F[K+1][MAXN],dep[MAXN];
inline int LCA(int u,int v)
{
    if(dep[u]<dep[v])swap(u,v);
    for(int i=K;~i;i--)if(dep[F[i][u]]>=dep[v])u=F[i][u];
    if(u==v)return u;
    for(int i=K;~i;i--)if(F[i][u]!=F[i][v])u=F[i][u],v=F[i][v];
    return F[0][u];
}
void dfs(int u,int fa)
{
    F[0][u]=fa;dep[u]=dep[fa]+1;
    for(auto&[v,w]:e[u])if(v!=fa)
    {
        rt[v]=rt[u];
        for(auto&x:pos[w])update(rt[v],1,N,lower_bound(all(d),x)-d.begin()+1,x);
        dfs(v,u);
    }
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,m,q;cin>>n>>m>>q;
    for(int i=1,u,v;i<n;i++)cin>>u>>v,e[u].emplace_back(v,i),e[v].emplace_back(u,i);
    for(int i=1,x;i<=m;i++)cin>>x>>c[i],pos[x].push_back(c[i]);
    d=vi(c+1,c+m+1);sort(all(d)),d.erase(unique(all(d)),d.end());
    N=d.size();
    dfs(1,0);
    for(int i=1;i<=K;i++)
        for(int j=1;j<=n;j++)
            F[i][j]=F[i-1][F[i-1][j]];
    while(q--)
    {
        int u,v;ll x,y;cin>>u>>v>>x>>y;
        int l=LCA(u,v);int t1=rt[u],t2=rt[v],t3=rt[l];
        ll w=ask(t1,t2,t3,1,N,y);
        cout<<max(-1ll,x+w-(t[t1].cnt+t[t2].cnt-t[t3].cnt*2))<<'\n';
    }
	return 0;
} 
```


---

