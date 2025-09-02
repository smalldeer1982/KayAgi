# [ABC232G] Modulo Shortest Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc232/tasks/abc232_g

$ N $ 頂点の有向グラフがあります。$ N $ 個の頂点はそれぞれ頂点 $ 1 $、頂点 $ 2 $、$ \ldots $、頂点 $ N $ と呼ばれます。

$ 1\ \leq\ i,\ j\ \leq\ N $ かつ $ i\ \neq\ j $ を満たす整数の組 $ (i,\ j) $ それぞれに対して、 頂点 $ i $ を始点、頂点 $ j $ を終点とする重み $ (A_i\ +\ B_j)\ \bmod\ M $ の有向辺があります。 （ただし、$ x\ \bmod\ y $ は $ x $ を $ y $ で割ったあまりを表します。）

上記のほかに辺はありません。

頂点 $ 1 $ から頂点 $ N $ への最短距離、すなわち、頂点 $ 1 $ から頂点 $ N $ へのパス上の辺の重みの総和として考えられる最小値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- $ 0\ \leq\ A_i,\ B_j\ <\ M $
- 入力はすべて整数

### Sample Explanation 1

以下では、頂点 $ i $ を始点、頂点 $ j $ を終点とする有向辺を $ i\ \rightarrow\ j $ で表します。 $ 1 $ $ \rightarrow $ $ 3 $ $ \rightarrow $ $ 2 $ $ \rightarrow $ $ 4 $ というパスを考えると、 - 辺 $ 1\ \rightarrow\ 3 $ の重みは、$ (A_1\ +\ B_3)\ \bmod\ M\ =\ (10\ +\ 4)\ \bmod\ 12\ =\ 2 $ であり、 - 辺 $ 3\ \rightarrow\ 2 $ の重みは、$ (A_3\ +\ B_2)\ \bmod\ M\ =\ (6\ +\ 7)\ \bmod\ 12\ =\ 1 $ であり、 - 辺 $ 2\ \rightarrow\ 4 $ の重みは、$ (A_2\ +\ B_4)\ \bmod\ M\ =\ (11\ +\ 1)\ \bmod\ 12\ =\ 0 $ です。 よって、このパスの辺の重みの総和は $ 2\ +\ 1\ +\ 0\ =\ 3 $ です。 これが頂点 $ 1 $ から頂点 $ N $ へのパス上の辺の重みの総和として考えられる最小値となります。

## 样例 #1

### 输入

```
4 12
10 11 6 0
8 7 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
10 1000
785 934 671 520 794 168 586 667 411 332
363 763 40 425 524 311 139 875 548 198```

### 输出

```
462```

# 题解

## 作者：Svemit (赞：11)

# Sol
发现边权对直接找最短路并没有什么好的性质，于是考虑优化建图。

由于 $a_i, b_i < m$，所以 $u, v$ 之间的边权只有可能是 $a_u + b_v$ 或 $a_u + b_v - m$。

我们希望连出去的边拥有一定规律，发现按某一维排序后连出去的边一定是一段前缀连 $a_u + b_v$，一段后缀连 $a_u + b_v - m$，于是用前后缀优化建图可以将边数降到 $O(n)$ 级别。

具体的，我们新建 $n$ 个前缀点 $pre_i$ 和 $n$ 个后缀点 $suf_i$。

对于每个 $1 < i \leq n $，连接 $pre_i$ 和 $pre_{i - 1}$，边权为 $0$。

对于每个 $1 \leq i < n$，连接 $suf_i$ 和 $suf_{i + 1}$，边权为 $0$。

对于每个 $1 \leq i \leq n$，让 $pre_i$ 和 $suf_i$ 分别向 $i$ 连一条边，边权为 $b_i$。

按 $b$ 排序后，对每个 $i$ 找到第一个点 $k$ 让 $a_i + b_k \geq m$，$i$ 向 $pre_{k - 1}$ 连一条边权为 $a_i$ 的边，向 $suf_k$ 连一条边权为 $a_i - m$ 的边。

这样连边之后原图上的任意一条路径都能在这张图上找到唯一一条与之对应的路径。

但是这样建图后会出现负权的问题，使用 SPFA 算法会让复杂度达到 $O(n ^ 2)$，不足以通过本题。

我们希望所有边都是正的，避免 $a_i - m$，那么我们考虑对于连向后缀的边，借助部分后缀点与后缀点之间的连边来算出边权，我们将 $a_i - m$ 变成 $a_i + b_k - m$。

考虑如何消除 $b_k$ 对后续的影响，可以让 $suf_k$ 连向 $suf_{k + 1}$ 的边权变成 $b_{k + 1} - b_k$，那么走到 $suf_{k + 1}$ 时边权就会变成 $a_i + b_{k + 1} - m$，再把后缀点向原图上的点连边的权值变成 $0$，容易发现这样不影响答案。

因为 $b$ 已经排序了，所以 $b_{k + 1} - b_{k}$ 全部为正，那么此时直接跑 dijkstra 即可。

[code](https://atcoder.jp/contests/abc232/submissions/56587545)

---

## 作者：GGapa (赞：6)

### [ABC232G] Modulo Shortest Path

https://www.luogu.com.cn/problem/AT_abc232_g

一个使用了最短路的思想但是并没有使用任何最短路的数据结构题解。

---

考虑 Dijkstra 暴力跑这个问题是怎么实现的，djk 每次会选择一个离起点集最近的点然后将其加入点集，由于题目中图是完全图，图中每个点都有可能是离起点最近的点，这启示我们用数据结构寻找全局最小值然后将其加入点集。

考虑具体怎么做，首先如果一个节点已经被加入点集，那么他的权值应当为 $\infty$，这一点是毋庸置疑的。

接着我们考虑从每一个节点出发，能够对未加入点集中的点造成什么样的影响。设当前加入点集的节点为 $u$，当前节点最短路为 $f(u)$，分两种情况讨论，若 $b_v + a_u < m$，则 $f(v) \gets \min(f(v), f(u) + a_u + b_v)$，否则 $f(v) \gets \min(f(v), f(u) + a_u + b_v - m)$，我们是可以提前将每个节点通过 $b$ 从小到大排序，这样每次操作我们可以二分出第一个 $a_u + b_v \ge m$ 的位置 $pos$，用 $f(u) + a_u - m$ 对 $[pos, n]$ 取最小值，由于后者如果存在一定比前者优，用 $f(u) + a_u$ 对全局取最小值。

现在我们已经可以使用线段树解决这个问题了，对于每个区间，分别记录最小值、最小值位置、最小的 $b$ 值，最小 $b$ 所在位置，即可维护这个问题。

由于笔者想题的时候 nt 了，所以求的是 $n \to 1$ 的最短路，核心和上述思路一样。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
using LL = long long;
using VI = vector<int>;
const int N = 2e5 + 5;
const LL INF = 1e18;

int A[N], B[N], id[N], exc[N];
int mod;

#define ls (x << 1) 
#define rs ((x << 1) | 1)
namespace SGT {   
    static const int N = (int)2e5 << 2;
    struct Node {
        int minapos, minvpos;
        LL tag, minval, mina;
    }tr[N];
    int n;
    void pushup(int x) {
        tr[x].minval = min(tr[ls].minval, tr[rs].minval);
        tr[x].mina = min(tr[ls].mina, tr[rs].mina);
        tr[x].minvpos = tr[ls].minval <= tr[rs].minval ? tr[ls].minvpos : tr[rs].minvpos;
        tr[x].minapos = tr[ls].mina <= tr[rs].mina ? tr[ls].minapos : tr[rs].minapos;
    }
    void build(int x = 1, int l = 1, int r = n) {
        tr[x].tag = INF;
        if(l == r) return tr[x].mina = A[id[l]], tr[x].minapos = l, tr[x].minval = (id[l] == n ? 0 : INF), tr[x].minvpos = l,  void();
        int mid = l + r >> 1;
        build(ls, l, mid); build(rs, mid + 1, r);
        pushup(x);
    }   
    void init(int nn) {
        n = nn; 
        build();
    }
    void apply(int x, LL v) {
        tr[x].tag = min(tr[x].tag, v);
        if(v + tr[x].mina < tr[x].minval) tr[x].minval = tr[x].mina + v, tr[x].minvpos = tr[x].minapos;
    }
    void pushdown(int x) {
        if(tr[x].tag == INF) return;
        apply(ls, tr[x].tag); apply(rs, tr[x].tag);
        tr[x].tag = INF;
    }
    void modify(int L, int R, LL v, int l = 1, int r = n, int x = 1) {
        if(L <= l && r <= R) return apply(x, v);
        int mid = l + r >> 1;
        pushdown(x);
        if(L <= mid) modify(L, R, v, l, mid, ls);
        if(mid < R) modify(L, R, v, mid + 1, r, rs);
        pushup(x);
    }
    void del(int it, int x = 1, int l = 1, int r = n) {
        if(l == r) return tr[x].minval = tr[x].mina = INF,  void();
        int mid = l + r >> 1;
        pushdown(x);
        if(it <= mid) del(it, ls, l, mid);
        else del(it, rs, mid + 1, r); 
        pushup(x);
    }
}
#undef ls
#undef rs
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n >> mod;
    rep(i, 1, n) cin >> A[i] ;
    rep(i, 1, n) cin >> B[i];
    iota(id, id + 1 + n, 0);
    sort(id + 1, id + 1 + n, [](const int x, const int y) {
        return A[x] < A[y];
    });
    rep(i, 1, n) exc[i] = id[i];
    auto find = [&](LL v) {
        int l = 1, r = n, ret = 1;
        while(l <= r) {
            int mid = l + r >> 1, i = id[mid];
            if(A[i] + v >= mod) r = mid - 1, ret = mid;
            else l = mid + 1;
        }
        return ret;
    };
    SGT::init(n);
    vector<LL> F(n + 1);
    for(int o = 1; o <= n; o++) {
        int it = SGT::tr[1].minvpos, i = id[it];
        F[it] = SGT::tr[1].minval;
        SGT::del(it);
        SGT::modify(1, n, B[i] + F[it]);
        if(B[i] + A[id[n]] >= mod) SGT::modify(find(B[i]), n, B[i] + F[it] - mod);
    }
    rep(i, 1, n) if(id[i] == 1) return cout << F[i] << '\n', 0;
    return 0;
}
```

---

## 作者：EXODUS (赞：6)

# Part 1：前言
比较套路但是也比较精妙的一个题，发这个题解的目的主要是加深一下对这个 trick 的理解，同时提出一个来自 [1789](https://www.luogu.com.cn/user/414210) 口胡的做法。

# Part 2：正文
看到边权特殊的完全图第一直觉是根据特殊性质减少边的数量到一个可以接受的范围，然后跑相关算法。注意到是一个取模的形式，因此可以想到建立一个大环，以环上的距离作为边权。

具体而言，先拉出一个大环，将点标号为 $0,1,...,m-1$，分别代表了 $0$ 到 $m-1$ 的每一个数。同时我们将原图的点重标号为 $m,m+1,...,m+n-1$。考虑将 $i$ 向 $(i+1)\bmod m$ 建边，则此时取模加法 $(x+y)\bmod m$ 的值可以表述为环上 $x,y$ 两点的距离。因此我们的原图上的一条边 $(u,v)$ 可以拆成从 $u+m-1$ 走到 $-a_u$，在从 $-a_u$ 走到 $b_v$，最后从 $b_v$ 走到 $v+m-1$。因此让 $u+m-1$ 向 $-a_u$ 连边权为 $0$ 的边，$b_u$ 向 $u+m-1$ 连边权为 $m$ 的边即可。

但这样点数是 $O(n+m)$ 的，我们无法接受，注意到真正造成贡献的点（即和原图的点有连边的点）的个数只有 $O(n)$，我们只建出这些点即可。此时点数和边数均为 $O(n)$ 级别。时间复杂度 $O(n\log n)$ 这也是官解的做法。

---

当然，作为一名 CN 的 oier，我们更应当会一些奇妙的数据结构来暴力维护这个东西，比如线段树。

我们将所有点按照 $b$ 排序。考虑到每次 dijkstra 算法的更新做一个分类讨论，即设当前对 $u$ 号节点做松弛操作，分 $a_u+b_i<m$ 和 $a_u+b_i\ge m$ 讨论。则此时相当于是对前缀和后缀分别取 $\min$，由于到 $i$ 号点的最短路可以看作 $c+b_i$，我们只需要维护 $c$ 即可，具体而言是 $(dis_u+a_u)\bmod m$，那么对于前后缀分别打 $tag$ 即可。对于线段树上的每个节点维护没有出队过的距离最小值，即可在线段树上二分找到当前距离原点距离最小的点。这样总时间复杂度是 $O(n\log n)$ 的，但是没有写过，不太清楚正确与否，感兴趣的读者可自己实现。



# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define mp make_pair
int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}
template<typename T>
void read(T &x){
	x=0;T flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flag;
}
const int N=1e6+7;
int n,mod;
int a[N],b[N];
ll dis[N];
bool vis[N];
vector<int>pnt;
vector<pair<int,int> >g[N];
int main(){
	n=read();mod=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)pnt.eb((mod-a[i])%mod),pnt.eb(b[i]);
	sort(pnt.begin(),pnt.end());
	pnt.erase(unique(pnt.begin(),pnt.end()),pnt.end());
	pnt.eb(pnt.front());
	
	
	for(int i=0;i<(int)(pnt.size())-1;i++){
		int u=i+1,v=i+2;
		if(v==(int)(pnt.size()))v=1;
		g[u].eb(mp(v,(mod+pnt[i+1]-pnt[i])%mod));
	}
	
	pnt.pop_back();
	
	for(int i=1;i<=n;i++){
		g[i+pnt.size()].eb(mp(lower_bound(pnt.begin(),pnt.end(),(mod-a[i])%mod)-pnt.begin()+1,0));
		g[lower_bound(pnt.begin(),pnt.end(),b[i])-pnt.begin()+1].eb(mp(i+pnt.size(),0));
	}
	
	auto dijkstra=[&](){
		priority_queue<pair<ll,int> >q;
		memset(dis,0x7f,sizeof(dis));dis[pnt.size()+1]=0;
		q.push(mp(-dis[pnt.size()+1],pnt.size()+1));
		while(!q.empty()){
			auto [d,u]=q.top();q.pop();
			if(vis[u])continue;
			for(auto [v,w]:g[u]){
				if(dis[v]>dis[u]+w){
					dis[v]=dis[u]+w;
					if(!vis[v])q.push(make_pair(-dis[v],v));
				}
			}
		}
	};
	
	dijkstra();
	
	printf("%lld\n",dis[n+pnt.size()]);
	
	return 0;
}
```

---

## 作者：Neil_Qian (赞：5)

## [ABC232G] Modulo Shortest Path 题解

### 题目描述

给出长度为 $n$ 的两个序列 $a$ 和 $b$，构造完全图，$u$ 到 $v$ 的连边边权为 $(a_u+b_v)\bmod m$，求单点对单点的最短路。

$n\le 2\times 10^5,m\le 10^9$。

### 解决方案

一开始的想法应该是找出边，对于点 $i$，考虑分为 $b_j<m-a_i$ 和 $b_j\ge m-a_i$ 两种。但比较复杂，还是考虑优化建图。

考虑到上一次的分类，把序列按 $b$ 升序排序，这样两类都是一个区间，而且是前后缀，于是考虑以此建图，参考以下图片：

![https://cdn.luogu.com.cn/upload/image_hosting/lmy78q0e.png](https://cdn.luogu.com.cn/upload/image_hosting/lmy78q0e.png)

注意到棕色边边权为负，直接跑肯定不行，需要进一步改进。

类似多源负权的处理方法，把最后一行的所有 $(i,i+1)$ 的边权变为 $b_{i+1}-b_i$，显然棕色边也会变，$(i,j)$ 边权变为 $a_i+b_j-m$，第三行往上到第一行的边权变为 $0$，这样就发现边权刚好抵消，$i$ 到 $v$ 会变为 $a_i+b_j-m+b_{j+1}-b_j+\dots +b_v-b_{v-1}=a_i+b_v-m$，刚好满足要求。而由于 $b$ 是递增排序的，黑色边边权仍非负。并且 $a_i+b_j\ge m$，因此棕色边边权也非负。大体如下：

![https://cdn.luogu.com.cn/upload/image_hosting/q0iucp9k.png](https://cdn.luogu.com.cn/upload/image_hosting/q0iucp9k.png)

直接上最短路就行了。点数和边数都是 $O(n)$ 的，于是时间复杂度为 $O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;using P=pair<int,int>;
const int N=6e5+2,M=6*N;mt19937 rnd(time(0));
struct Node{
	int a,b,id;
	friend bool operator <(const Node x,const Node y){return x.b<y.b;}
}p[N];int n,m,st,en,cnt,head[N],nxt[M],to[M],w[M],ans[N];
priority_queue<P,vector<P>,greater<P> > pq;bool vis[N];
inline void addedge(int x,int y,int z){
	nxt[++cnt]=head[x],head[x]=cnt,to[cnt]=y,w[cnt]=z;
}
inline bool cmp(int x,int y){return ans[x]<ans[y];}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>p[i].a,p[i].id=i;
	for(int i=1;i<=n;i++)cin>>p[i].b;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		if(p[i].id==1)st=i;
		else if(p[i].id==n)en=i;
	}
	for(int i=1;i<=n;i++){
		addedge(i+n,i,p[i].b),addedge(i+2*n,i,0);
		if(i>1)addedge(i+n,i+n-1,0);
		if(i<n)addedge(i+n*2,i+n*2+1,p[i+1].b-p[i].b);
		int pos=upper_bound(p+1,p+n+1,Node{0,m-p[i].a-1,0})-p-1;
		if(pos>=1)addedge(i,pos+n,p[i].a);
		if(pos<n)addedge(i,pos+1+n*2,p[i].a+p[pos+1].b-m);
	}
	memset(ans,0x3f,sizeof(ans)),ans[st]=0,pq.emplace(P{0,st});
	while(!pq.empty()){
		int x=pq.top().second;pq.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=nxt[i])if(ans[to[i]]>ans[x]+w[i])
			ans[to[i]]=ans[x]+w[i],pq.emplace(P{ans[to[i]],to[i]});
	}
	return cout<<ans[en]<<"\n",0;
}
```

---

## 作者：STDLRZ (赞：3)

思路来自于 @0x3b800001 的（稍改），但是我希望我能用更清晰的语言让大家理解。

这篇比较偏向萌新。~~因为作者也是萌新呀！~~

### 暴力

直接暴力建边，然后跑一遍最短路即可。

### 正解

观察一条边的边权：$u \to v$ 的边权为 $(a_u+b_v) \bmod m$。

发现有取模操作，先考虑没有取模操作的特殊情况。

即：$u \to v$ 的边权为 $(a_u+b_v)$。

我们该如何建边？我们可以枚举 $u$，一旦 $u$ 固定，那么不管你的 $v$ 是什么，$a_u$ 就已经固定了。

此时，我们可以建立一个大节点 $T$，这个节点是 $1 \sim n$ 的中转节点。

我们可以让 $u$ 节点先用 $a_u$ 的边权连向 $T$，然后让 $T$ 连向这些小节点 $v$，边权为 $b_v$。这样拆分，就不用 $\mathcal O(n^2)$ 的建图啦。

接着，再跑一遍 dijkstra，就可以结束了。

再考虑回一般情况。

我们还是一样，枚举 $u$，那么 $a_u$ 就固定了，就只剩下 $b_v$ 的事情了。

大家应该都知道，这个取模有两种情况：

- $a_u+b_v<m$：值为 $a_u+b_v$，是我们考虑的特殊情况。
- $a_u+b_v \ge m$：值为 $a_u+b_v-m$。

因为 $a_u$ 固定，如果我们将节点以 $b$ 为关键字从小到大排序，那么肯定有：前一半部分是第一种情况，后一半部分是第二种情况。

于是我们就以 $b$ 为关键字从小到大将节点排序。

此时，只使用节点 $T$ 来进行连边就不够了。我们可以来一个前后缀节点，定义：

- 对于前缀节点 $i+n$，表示的节点是 $1 \sim i$ 这个整体。
- 对于后缀节点 $i+2n$，表示的节点是 $i \sim n$ 这个整体。

模仿特殊情况的连边方式，稍微改一改。

因为对于两个前缀节点 $u+n,v+n(u<v)$，$v+n$ 节点是覆盖 $u+n$ 节点的整体的。

所以，我们可以让 $i+n \to i+n-1(i>1)$，如果大的节点行那小的节点也行，边权为 $0$；

同理，我们也可以让 $i+2n \to i+1+2n(i<n)$，边权为 $0$。

对于一个节点 $i$，设 $1 \sim ans-1$ 的节点是特殊情况，$ans \sim n$ 的节点需要在特殊情况的基础下再减去 $m$。也就是说，$1 \sim ans-1$ 的边权是 $a_u$，$ans \sim n$ 的边权是 $a_u-m$。

至于从整体节点连到单个节点，不管是 $i$ 的前缀节点 $i+n$，还是 $i$ 的后缀节点 $i+2n$，我们都令他的边权为 $b_i$。

正确性：像我们之前说的，对于两个前缀节点 $u+n,v+n(u<v)$，$v+n$ 节点是覆盖 $u+n$ 的整体的。假设我们现在需要到 $u$ 节点，于是我们可以从 $v+n$ 一直走到 $u+n$，然后再走到 $u$。所以是正确的。

总结（上图，一图胜千言）：![](https://cdn.luogu.com.cn/upload/image_hosting/8zmsigu3.png)

这个图只是举个例子，因为淡绿色的边不能污染了其他颜色的边，所以这里只举了部分连边例子。

但是我们发现：**边权可能为负！**

考虑怎么让边权变为自然数。我们发现，只有当单个节点连向后缀节点的时候，才会产生负数的边。

于是，我们考虑将 $b_i$ 也一同加入。也就是说，我们的单个节点 $i$ 连向的整体节点 $ans \sim n$ 的边权变成了 $b_{ans}+a_i-m$，此时这个边权确实非负了。但是？如果后缀节点之间节点的连边边权还是 $0$ 的话，就有问题。所以我们要调整一下这些边权。

于是，我们走一条边 $u+2n \to u+1+2n$，因为我们当前 $b$ 的贡献是 $b_{u+2n}$，现在要变成 $b_{u+1+2n}$，于是我们令这条边权为 $b_{u+1+2n}-b_{u+2n}$。

这样，我们的 $i+2n \to i$ 边的边权就不再需要考虑到 $b$ 的贡献，直接赋值为 $0$ 即可。

诶？等等？$b$ 数组是从小到大排序的？那这个边权不也是非负的嘛？

这不就完美解决了嘛？

上图（不再展示单个节点连向前缀节点的边）：![](https://cdn.luogu.com.cn/upload/image_hosting/jxhbvhi9.png)

其中，红色的边强调该边权有更改。

代码（~~应该有可读性吧~~）：

```cpp
#include<bits/stdc++.h>
#define x0 x_0
#define x1 x_1
#define y0 y_0
#define y1 y_1
#define yn y_n
#define j0 j_0
#define j1 j_1
#define k0 k_0
#define k1 k_1
#define d0 d_0
#define d1 d_1
#define LL long long
#define LD long double
#define ZPB push_back
#define ZPF push_front
#define US unsigned
using namespace std;
struct node{
	int a,b,id;
	bool operator < (const node &o)const{return (b!=o.b ? b<o.b : id<o.id);}
};
struct Enode{
	int v;
	LL w;
	bool operator < (const Enode &o)const{return w>o.w;}
};
/*
[1,n]: real_node
[n+1,2n]: qjh_node
[2n+1,3n]: hjh_node
*/
node val[200010];
int n,m,st,ed;
const LL LLmex=1e18;
LL dp[600010];
vector<Enode> G[600010];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>val[i].a,val[i].id=i;
	for(int i=1;i<=n;++i) cin>>val[i].b;
	sort(val+1,val+n+1);
	for(int i=1;i<=n;++i){
		if(val[i].id==1) st=i;
		if(val[i].id==n) ed=i;
		G[n+i].ZPB({i,val[i].b}),
		G[(n<<1)+i].ZPB({i,0});
	}
	for(int i=2;i<=n;++i) G[n+i].ZPB({n+i-1,0});
	for(int i=1;i<n;++i) G[(n<<1)+i].ZPB({(n<<1)+i+1,val[i+1].b-val[i].b});
	for(int i=1;i<=n;++i){
		int L=1,R=n,ans=n+1;
		while(L<=R){
			int mid=(L+R)>>1;
			if(val[i].a+val[mid].b>=m) R=mid-1,ans=mid;
			else L=mid+1;
		}
		if(ans>1) G[i].ZPB({n+ans-1,val[i].a});
		if(ans<=n) G[i].ZPB({(n<<1)+ans,val[i].a+val[ans].b-m});
	}
	priority_queue<Enode> q;
	for(int i=1;i<=(n<<1)+n;++i) dp[i]=LLmex;
	dp[st]=0,q.push({st,0});
	while(q.size()){
		Enode dt=q.top();
		q.pop();
		int x=dt.v;
		if(dp[x]<dt.w) continue;
		for(int i=0;i<(int)G[x].size();++i){
			int u=G[x][i].v;
			LL w=G[x][i].w;
			if(dp[u]>dp[x]+w) dp[u]=dp[x]+w,q.push({u,dp[u]});
		}
	}
	cout<<dp[ed]<<"\n";
	return 0;
}
```

---

## 作者：mlvx (赞：3)

优化建图。

考虑先把 $b$ 升序排序。

这里把排序后第 $i$ 个点的原本的编号称为 $id_i$。

则可以把 $b$ 连成一串，其中 $id_i\to id_{i+1}(i<n)$ 的边权为 $b_{i+1}-b_i$，即差分的形式。

我们把 $a,b$ 分开，建新点，$a$ 对应 $n+1\sim 2n$，$b$ 对应 $1\sim n$，由于走到一个点可以直接向外走，所以还要建 $i\to i+n(1\le i\le n)$ 的边，边权为 $0$。

由于 $a_u+b_v<2m$，故可以分成两类：

- $a_u+b_v<m$，则直接连一条边权为 $a_u+b_1$ 的 $u$ 连向 $id_1$ 的边。配合上前面建的边，对于 $1\le i\le n$，相当于建了边权为 $a_u+b_i$ 的 $u$ 连向 $i$ 的边。

- $a_u+b_v\ge m$，则找到第一个 $b_v$，使得 $a_u+b_v\ge m$，可以二分。然后连一条边权为 $a_u+b_v-m$ 的 $u$ 连向 $id_v$ 的边。配合上前面建的边，对于 $v\le i\le n$，相当于建了边权为 $a_u+b_i-m$ 的 $u$ 连向 $i$ 的边。对于满足此类却被上面连过的，则一定不优。

然后直接跑最短路即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
int c,t,n,m,a[N],dis[N<<1],vis[N<<1];vector<pair<int,int>>g[N<<1];
struct node{int x,v;}b[N];bool operator<(node a,node b){return a.v<b.v;}
struct Node{int x;ll v;};bool operator<(Node a,Node b){return a.v>b.v;}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i].v,b[i].x=i;
    sort(b+1,b+n+1);
    for(int i=2;i<=n;i++)g[b[i-1].x].push_back({b[i].x,b[i].v-b[i-1].v});
    for(int i=1;i<=n;i++){
        g[i+n].push_back({b[1].x,a[i]+b[1].v});
        int x=lower_bound(b+1,b+n+1,(node){0,m-a[i]})-b;
        if(x<=n)g[i+n].push_back({b[x].x,a[i]+b[x].v-m});
    }for(int i=1;i<=n;i++)g[i].push_back({i+n,0});
    priority_queue<Node>q;memset(dis,0x3f,sizeof dis);
    for(q.push({n+1,dis[n+1]=0});!q.empty();){
        int x=q.top().x;q.pop();
        if(vis[x])continue;vis[x]=1;
        for(auto[y,w]:g[x])if(dis[y]>dis[x]+w)q.push({y,dis[y]=dis[x]+w});
    }cout<<dis[n];
    return 0;
}
```

---

## 作者：Forg1weN (赞：2)

# **[ABC232G] Modulo Shortest Path**


你有一个 $n$ 个点的有向完全图。

每个点有两个属性 $a_i$ 和 $b_i$。$u \to v$ 的边的权值是 $(a_u+b_v) \bmod m$。

给你 $n$ , $m$ 和 $\{a_i\}$ 以及 $\{b_i\}$ , 求 $1$ 到 $n$ 的最短路。



- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- $ 0\ \leq\ A_i,\ B_j\ <\ M $

## 思路

考虑如何处理 $a_i,b_i$ 数组的条件，直接暴力建边的数量级是 $m$ 的，显然无法接受，观察到边与边直接其实是有重复部分的，考虑在模 $m$ 意义下建出 $0\dots m-1$ 标号的环，称为新图，相邻两点间连边权为 $1$ 的边，然后将原图的顶点分离出来。

若环上双向连边，则无法满足 $a_u+b_v$ 的限制，于是考虑从 $-a_u$ 出发至 $b_v$ ，于是边就成为单向边了，再将 $-a_u$ 与 $u$ 相连， $b_v$ 与 $v$ 相连即可，环与原图的边权值为 $0$。

考虑到环上并不是每一个点都是与原图有连边，相当于环上的有些点是没用的，我们只保留有用点，只需更改边权，具体而言，$u\stackrel{1}\rightarrow x \stackrel{1}\rightarrow v$ 的边，若 $x$ 与原图没有连边，则等价于 $u\stackrel{2}\rightarrow v$。

所以边的数量级是 $n$ 相关的，跑一般图论算法可以通过，时间复杂度 $O(n\log n)$。

## code
提供一份借鉴了网上代码的可读代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
const int maxn=1e6+10;
int n,m,num;
int a[maxn],b[maxn];
int tmp[maxn],dis[maxn],vis[maxn];
int hd[maxn],num_edge;
struct EDGE {
	int nt,u,v,w;
}edge[maxn*2];
void addedge(int u,int v,int w) {
	edge[++num_edge]=(EDGE){hd[u],u,v,w};
	hd[u]=num_edge;
}
void dij(int x) {
	priority_queue< pi >Q;
	memset(dis,0x3f,sizeof(dis));
	dis[x]=0;
	Q.push({-dis[x],x});
	while(!Q.empty()) {
		int u=Q.top().second;
		Q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=hd[u];i;i=edge[i].nt) {
			int v=edge[i].v;
			int w=edge[i].w;
			if(dis[v]>dis[u]+w) {
				dis[v]=dis[u]+w;
				Q.push({-dis[v],v});
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		a[i]=( m-a[i]+m )%m;
		tmp[++num]=( a[i]%m+m )%m;
	}
	for(int i=1;i<=n;i++) {
		scanf("%d",&b[i]);
		tmp[++num]=b[i]%m; 
	}
	sort(tmp+1,tmp+1+num);
	num=unique(tmp+1,tmp+1+num)-tmp-1;
	for(int i=1;i<=n;i++) {
		a[i]=lower_bound(tmp+1,tmp+1+num,a[i])-tmp;
		b[i]=lower_bound(tmp+1,tmp+1+num,b[i])-tmp;
		addedge(i+num,a[i],0);
		addedge(b[i],i+num,0);
	}
	for(int i=1;i<num;i++) 
		addedge(i,i+1,tmp[i+1]-tmp[i]);
	addedge(num,1, ( tmp[1]-tmp[num]+m )%m);
	dij(num+1);
	printf("%d",dis[n+num]);
	return 0;
}
```

---

## 作者：zhou2414 (赞：1)

~~一道毒瘤题~~。
# 思路
题目中要求建完全图，~~一身反骨的~~我们肯定不能建完全图，考虑优化建图。

这题难就难在优化建图。每条边的权值与两端的端点都有关系，且每条边有 $a,b$ 两个属性。

套路地想到可以将一个点拆成两个点来做，令编号 $1$ 到 $n$ 的点的权值为对应的 $a$，$n+1$ 到 $n+n$ 的点权为对应的 $b$，在对应的两个点之间连一条从 $b$ 到 $a$ 的权值为 $0$ 的边即可。以下称前者为 $a$ 点，后者为 $b$ 点。

我们希望将边的数量降至 $O(n)$ 级别，就肯定不能暴力建边。可以考虑**差分建边**（自己取的名字），即利用差分思想建边。先将各个节点按照 $b$ 值排序，然后从小到大建边。每个从 $u$ 到 $v$ 的边的权值为 $b_v-b_u$，然后只要让每个 $a$ 点连接一条到 $n+1$ 的权值为 $a_i+b_{n+1}$ 有向边即可。

容易证明这样建边的正确性，希望读者能自己完成证明。

此时已经完成了这道题的百分之八十，还有一个取模没有完成。

观察数据范围：
> $0\leq A_i,b_j<M$

发现在这样的数据范围下，一条边最多也不会大于等于 $2M$，所以完全可以将取模转换为减法，对于大于 $M$ 的边，只要减上 $M$ 即可。

有了前面的基础，这一步应该不太难想。由于前面已经将 $b$ 点排序，那么可以对于每个 $a$ 点（设为点 $i$），**二分**出第一个使得 $a_i+b_j\geq M$ 的 $b$ 点 $j$，此时对于每个后面的 $b$ 点，都需要减 $M$，所以可以连一条 $i$ 到 $j$ 的权值为 $a_i+b_j-M$ 的有向边。不用担心影响前面的，因为 $b$ 点之间的边为从小到大的有向边。也不用担心与第一个 $b$ 点连接的边会影响后面的，因为显然更劣。

注意如果点 $j$ 不存在或者点 $j$ 为第一个 $b$ 点，那么只要建一条边即可。

容易发现这样建边都是非负的，所以建完图跑个 Dijkstra 就行。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define ld long double
#define dd double
inline ll read() {
	ll x = 0, f = 1;
	char ch;
	while (((ch = getchar()) < 48 || ch > 57)&&ch!=EOF)if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
char __sta[1009], __len;
inline void write(ll x,ll bo) {
	if (x < 0)putchar('-'), x = -x;
	do __sta[++__len] = x % 10 + 48, x /= 10;
	while (x);
	while (__len)putchar(__sta[__len--]);
	if(bo==3)return;
	putchar(bo ? '\n' : ' ');
}
const ll N=2e6+9,INF=1e17;
ll n,m;
struct B{
	ll id,a,b;
}node[N];
struct LIAN{
	ll to,ne,w;
}lian[N*3];
ll h[N*2],licnt;
ll jian[N];
ll dis[N*3];
bool bo[N*3];
struct NODE{
	ll id,dis;
	bool operator<(const NODE b)const{
		return dis>b.dis;
	}
};
inline bool cmp(B a,B b){
	return a.b<b.b;
}
inline void add(ll u,ll v,ll w){
	lian[++licnt].to=v;
	lian[licnt].ne=h[u];
	lian[licnt].w=w;
	h[u]=licnt;
}
inline void er(){
	node[n+1].b=INF;
	for(int i=1;i<=n;i++){
		ll l=1,r=n+1,mid;
		while(l<r){
			mid=(l+r)/2;
			if(node[i].a+node[mid].b>=m){
				r=mid;
			}else{
				l=mid+1;
			}
		}
		if(l==n+1){
			add(node[i].id,node[1].id+n,node[i].a+node[1].b);
		}else{
			if(l==1){
				add(node[i].id,node[1].id+n,node[i].a+node[1].b-m);
			}else{
				add(node[i].id,node[1].id+n,node[i].a+node[1].b);
				add(node[i].id,node[l].id+n,node[i].a+node[l].b-m);
			}
		}
	}
}
inline void dj(){
	for(int i=0;i<=n*3;i++){
		dis[i]=INF;
	}
	dis[1]=0;
	priority_queue<NODE>q;
	q.push({1,0});
	while(!q.empty()){
		ll now=q.top().id;
		q.pop();
		if(bo[now])continue;
		bo[now]=1;
		for(int j=h[now];j;j=lian[j].ne){
			ll to=lian[j].to;
			if(dis[to]>dis[now]+lian[j].w){
				dis[to]=dis[now]+lian[j].w;
				q.push({to,dis[to]});
			}
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		node[i].a=read(),node[i].id=i;
	}
	for(int i=1;i<=n;i++){
		node[i].b=read();
	}
	sort(node+1,node+n+1,cmp);
//	for(int i=1;i<=n;i++){
//		if(node[i].id==1)st=i;
//		if(node[i].id==n)en=i;
//	}
	for(int i=1;i<n;i++){
		add(node[i].id+n,node[i+1].id+n,node[i+1].b-node[i].b);
		add(node[i].id+n,node[i].id,0);
	}
	add(node[n].id+n,node[n].id,0);
	er();
	dj();
	write(dis[n],1);
//	for(int i=1;i<=n+n;i++){
//		for(int j=h[i];j;j=lian[j].ne){
//			cout<<i<<' '<<lian[j].to<<' '<<lian[j].w<<endl;
//		}
//	}
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：1)

好题。优化建图的思路十分多样。我介绍一个比较容易理解的。

首先，观察题目中的边权，发现其可以拆分：把所有点按照 $b$ 从大到小排序，给定一个 $a$，其向 $b$ 的一个前缀连权值为 $a+b-m$ 的边，向 $b$ 剩下的后缀连权值为 $a+b$ 的边。

只会向前后缀连边是一个极好的性质！于是我们考虑前后缀优化建图。

对于从 $u$ 到 $v$ 边权为 $a+b$ 的边，因为 $a,b$ 非负，考虑建立虚点 $x_u,x_v$，连边 $(u,x_u,a_u),(x_v,v,b_v)$。相邻的 $x$ 连边 $(x_i,x_{i+1},0)$。

对于从 $u$ 到 $v$ 边权为 $a+b-m$ 的边，刚才的方法就行不通了，会产生负权边。观察到 $b$ 是从大到小排序的，因此向前缀连边所经过的 $b$ 是从小到大的，$b_{i-1}-b_i\ge 0$。考虑建立虚点 $y_u,y_v$，连边 $(u,y_u,a_u+b_u-m),(y_v,v,0)$。由于这个差是可累加的，相邻的 $y$ 连边 $(y_i,y_{i-1},b_{i-1}-b_i)$。

然后跑一遍 Dijsktra 即可。

```cpp
// Title:  Modulo Shortest Path
// Source: ABC232G
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=600010; ll inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
char buf[1<<23], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int n, m, nn, a[N]; bool vis[N]; ll d[N];
struct node
{
    int x, i;
    bool operator <(node t) {return x>t.x;}
} b[N];
vector<pair<int, int>> g[N];
void add(int u, int v, int w)
{
    g[u].push_back({v, w});
}
priority_queue<pair<ll, int>> q;
void dij(int s)
{
    rep(i, 1, nn) d[i]=inf;
    d[s]=0; q.push({0, s});
    while(q.size())
    {
        int u=q.top().second; q.pop();
        if(vis[u]) continue; vis[u]=1;
        for(auto [v,w]:g[u]) if(d[u]+w<d[v])
            d[v]=d[u]+w, q.push({-d[v], v});
    }
}

int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin); ios::sync_with_stdio(0);
#endif
    n=read(), m=read(); nn=n+n+n;
    rep(i, 1, n) a[i]=read();
    rep(i, 1, n) b[i].x=read(), b[i].i=i;
    sort(b+1, b+n+1);
    rep(i, 1, n)
    {
        if(i>1) add(n+i, n+i-1, b[i-1].x-b[i].x);
        if(i<n) add(n+n+i, n+n+i+1, 0);
    }
    rep(i, 1, n)
    {
        add(n+i, b[i].i, 0);
        add(n+n+i, b[i].i, b[i].x);
    }
    rep(k, 1, n)
    {
        int u=b[k].i;
        int l=1, r=n, res=0;
        while(l<=r)
        {
            int mid=l+r>>1;
            if(a[u]+b[mid].x>=m) res=mid, l=mid+1; else r=mid-1;
        }
        if(res>0) add(u, n+res, a[u]+b[res].x-m);
        if(res<n) add(u, n+n+res+1, a[u]);
    }
    dij(1);
    printf("%lld", d[n]);

    return 0;
}
```

---

## 作者：pioneer2000 (赞：1)

### 分析：

题目要求我们输出节点 $1$ 到节点 $n$ 的最短路，考虑暴力建图，时间复杂度是 $O(n^2)$ 的，显然会超时。

我们可以考虑去后缀建图。具体的做法是向将 $b$ 数组升序排序，将整个区间建立一条长为 $n$ 的虚链。这条虚链从前往后连单向边，每个虚链上的点向真正的点连边。将 $i$ 向 $i+1$ 两边，边权类似差分，这样就可以表示 $x$ 节点到 $y$ 节点的边权了（后面会讲）。

首先对 $(x_u+b_v)\bmod m$ 进行分类讨论：
- 若 $(x_u+b_v)<m$，那么可以将 $i+n$ 号节点连向前面的 $1$ 号节点，此时边权即为 $a_i+b_1$，那么也可以类似的求出每个点的权值为 $a_i+b_i$，边权是正确的。
- 若 $(x_u+b_v)\ge m$，那么同样可以将 $i+n$ 号节点连向前面的 $u$ 号节点（利用二分求得第一个 $(a_i+b_v)\ge m$ 的点），此时边权即为 $a_i+b_u-m$，那么也可以类似的求出每个点的权值为 $a_i+b_i-m$，边权依旧正确。

所以在此之后，我们只需要将前后缀建图时的节点与其对应的节点建一条边权为 $0$ 的单项边即可。
（千万不要建双向边，不然直接寄了）。

那么此时我们已经完成了建图，最后再用 dijkstra 跑一遍就行了，我们最多会建 $4n$ 条边，时间复杂度在 $O(n \log n)$ 解决此题。

最后是喜闻乐见的代码啦（过于抽象，勿喷）。

### code：

```cpp
#include<bits/stdc++.h>
#define INF 1e18
#define ll long long
#define int long long
using namespace std;
const int N=2e5+5;
ll n,m,a[N],dis[N<<1],c,t,vis[N<<1];
struct node{
	ll val,id;
}b[N];
struct Node{
	ll val,id;
};
bool operator<(Node x,Node y){
	return x.val>y.val;
}
vector<pair<ll,ll> > g[N<<1];
bool operator<(node x,node y){
	return x.val<y.val;
}
main(){
    freopen("graph.in","r",stdin),freopen("graph.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>c>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=(n<<1);i++){
    		g[i].clear();
    		vis[i]=0;
    		dis[i]=INF;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i].val;
			b[i].id=i;
		}
		sort(b+1,b+n+1);
		for(int i=2;i<=n;i++){
			g[b[i-1].id].push_back({b[i].id,b[i].val-b[i-1].val}); 
		}
		for(int i=1;i<=n;i++){
			g[i+n].push_back({b[1].id,a[i]+b[1].val});
			ll x=lower_bound(b+1,b+n+1,(node){m-a[i],0})-b;
			if(x<=n) g[i+n].push_back({b[x].id,a[i]+b[x].val-m});
		}
		for(int i=1;i<=n;i++){
			g[i].push_back({i+n,0});
		}
		priority_queue<Node> qp;
		dis[n+1]=0;
		qp.push({0,n+1});
		while(!qp.empty()){
			Node tot=qp.top();
			qp.pop();
			if(vis[tot.id]) continue;
			vis[tot.id]=1;
			for(auto i:g[tot.id]){
				if(dis[i.first]>dis[tot.id]+i.second){
					dis[i.first]=dis[tot.id]+i.second;
					qp.push({dis[i.first],i.first});
				}
			}
		}
		cout<<dis[n]<<endl;
	}
	return 0;
}

```

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
直接连边显然是 $O(n^2)$ 的，所以要优化建图。

我们考虑将 $b$ 数组升序排序。

考虑用前缀的方式连边，具体来说就是 $i$ 向 ${i+1}$ 连边，其边权就是 $b_{i+1}-b_{i}$，那么从 $x$ 号节点出发到 $y$ 节点所经过的边权就是 $b_y-b_x$。

那么这样就可以考虑将每个原图点拆分为两个点，一个点就是刚才前缀处理的点，那么另一个点就可以用于表示 $a_i$ 的贡献了。

考虑对 $(a_u+b_v) \bmod m$ 分类讨论：
- $a_u+b_v<m$，那么此时新建 $n$ 个点，将每个 $i+n$ 编号的点连向刚才前缀处理后的 $1$ 号节点，其边权为 $a_i+b_1$，那么此时从新建的点出发即可正确计算此情况的边权，到达每个点的权值即是 $a_u+b_v$。
- $a_u+b_v\ge m$，那么仍使用刚才的方法，对于每个 $i+n$ 编号的点，用二分在 $b$ 数组中找到第一个满足条件的 $b_v$，并向其连一条边权为 $a_i+b_v-m$ 的边，那么此时边权仍是正确的，因为 $a_u+b_v < 2m$，所以到达每个点的权值即是 $a_u+b_v-m$。

此时还有一个问题，因为我们将同一个节点分裂了，所以他们之间是可以无代价到达的，所以将前缀处理的点与其对应的节点连一条边权为 $0$ 的边即可。

我们来分析一下正确性，首先边权计算已经分析过，保证计算无误。对于答案的贡献来说，每个点都是可以互达的，也没有问题。对于可以通过边权为 $a_i+b_v-m$ 到达的点来说，虽然也有 $a_i+b_v$ 的边可以到达，但一定更劣，所以也正确。

最后来看一下边数是 $O(n)$ 的，跑个最短路就可以了，所以就可以 $O(n \log n)$ 解决这道题了。
### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define N 200005
using namespace std; 
int c,T;
int n,m;
vector<pair<int,int>> g[N<<1];
ll dis[N<<1];
struct node{
	int id;
	ll w;
}a[N],b[N];
bool vis[N<<1];
priority_queue<node> q;
bool operator <(node x,node y){
	return x.w>y.w;
}
bool operator <(node x,int y){
	return x.w<y;
}
void dij(int s){
	for(int i=1;i<=(n<<1);i++){
		dis[i]=1e15;
		vis[i]=0;
	}
	dis[s]=0;
	q.push({s,0});
	while(!q.empty()){
		node x=q.top();
		q.pop();
		if(vis[x.id]) continue;
		vis[x.id]=1;
		for(auto i:g[x.id]){
			if(dis[i.first]>dis[x.id]+i.second){
				//cout<<x.id<<"->"<<i.first<<' '<<i.second<<'\n';
				dis[i.first]=dis[x.id]+i.second;
				q.push({i.first,dis[i.first]});
			}
		}
	}
} 
bool cmp(node x,node y){
	return x.w<y.w;
}
int s,t;
int main(){
	cin.tie(),cout.tie(),ios::sync_with_stdio(0);
	T=1;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i].w;
			a[i].id=i;
		}
		for(int i=1;i<=n;i++){
			cin>>b[i].w;
			b[i].id=i;
		}
		sort(b+1,b+n+1,cmp);
		t=n;
		for(int i=1;i<n;i++){
			g[i].push_back({i+1,b[i+1].w-b[i].w});
			if(b[i].id==n) t=i;
		}
		for(int i=1;i<=n;i++){
			g[i+n].push_back({1,a[i].w+b[1].w});
			int id=lower_bound(b+1,b+n+1,m-a[i].w)-b;
			if(id<=n){
				g[i+n].push_back({id,a[i].w+b[id].w-m});
			}
			if(a[i].id==1) s=i+n;
		}
		for(int i=1;i<=n;i++){
			g[i].push_back({b[i].id+n,0});
		}
		dij(s);
		cout<<dis[t]<<'\n';
		for(int i=1;i<=(n<<1);i++){
			g[i].clear();
		}
	} 
	return 0;
}
```

---

## 作者：王江睿 (赞：1)

环优化建图
-

建 $ 2n $ 个点，点权为 $ m - a_i, b_i $。

将 $ 2n $ 个点按点权排序连成环。环上相邻两点的边权为其点权之差。（尾→首之差须加 $ m $ 以为正数）

再将 $ i $ 相同的二对应点自 $ b $ 侧向 $ a $ 侧连边。

可以证明该图和原图等价（讨论 $ b_i - m $ 和 $ a_i $ 的在环上的前后关系，即 $ a_i + b_i $ 和 $ m $ 的大小关系）。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
enum{_n=400007,_m=600007};
struct node{
	bool operator<(node A) const
	{return d>A.d;}
	mutable int u; int d; };
priority_queue<node>q;
struct {int u,v,w,N;}E[_m];
int hed[_n],cnt;
int dis[_n];
void add(int u,int v,int w){
	E[++cnt]={u,v,w,hed[u]};
	hed[u]=cnt; }
int a[_n],l[_n];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;++i) cin>>a[i],a[i]=m-a[i];
	for(int i=0;i<n;++i) cin>>a[n+i];
	for(int i=0;i<n;++i) add(n+i,i,0);
	n*=2; iota(l,l+n,0);
	stable_sort(l,l+n,[](int i,int j){return a[i]<a[j];});
	for(int i=0;i<n;++i)
		add(l[i],l[(i+1)%n],(a[l[(i+1)%n]]-a[l[i]]+m)%m);
	memset(dis,-1,4*n);
	q.push({0,0});
	while(!q.empty()){
		auto[u,d]=q.top();
		q.pop();
		if(!~dis[u]){
		  dis[u]=d;
		  for(int i=hed[u],v;v=E[i].v,i;i=E[i].N)
			q.push({v,d+E[i].w});
		}
	}
	cout<<dis[n-1]<<'\n';
}
```

---

## 作者：loser_seele (赞：1)

首先考虑暴力做法：暴力建边，然后直接跑 Dijkstra，但是边数是 $ N^2 $ 级别，难以通过。

我们考虑拆边的做法：

首先对于点 $ i $，连 $ i $ 到 $ -a_i \bmod m $ 的边，连 $ b_i $ 到 $ i $ 的长度为 $ 0 $ 的边。

然后对于 $ [0,m) $ 之间的所有 $ i $ 连向 $ i+1 $，代价为 $ 1 $，因为是模意义下连边所以 $ m $ 相当于 $ 0 $。则原图的路径显然都可以拆分成新图上的一条路径。

具体构造如下：原图中任意边 $ s \rightarrow t $ 可以拆分为 $ s \rightarrow -a_s \bmod m \rightarrow (-a_s+1) \bmod m \rightarrow ... \rightarrow b_t \rightarrow t $。这个是显然的，因为经过的总路径长度仍然为 $ a_s+b_t $。

但是拆完边之后点数为 $ n+m $，难以接受。

注意到新图中一条路径上的边都可以被合并，实际上这张图等价于建完第一种边之后，对于每个点，将边连向距离其最近的点，这个可以二分实现。

最后建出来的图每个点最多有 $ 3 $ 条边连接，所以点和边的数量级都是 $ n $，可以直接跑 Dijkstra，总时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> node;
int const N=600010;
int n,m,a[N],b[N],d[N],vis[N];
vector<int>v;
vector<node>e[N];
priority_queue<node,vector<node>,greater<node> >q;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i],v.push_back(a[i]=(m-a[i])%m);
	for(int i=1;i<=n;i++)
		cin>>b[i],v.push_back(b[i]);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	int p=v.size();
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1,
		b[i]=lower_bound(v.begin(),v.end(),b[i])-v.begin()+1,
		e[i+p].push_back({a[i],0}),e[b[i]].push_back({i+p,0});
	for(int i=1;i<p;i++)
		e[i].push_back({i+1,v[i]-v[i-1]});
	e[p].push_back({1,(v[0]-v[p-1]+m)%m});
	memset(d,0x3f,sizeof d);
	q.push({d[p+1]=0,p+1});
	while(!q.empty())
    {
		int x=q.top().second;
        q.pop();
		if(vis[x])
		continue;
		vis[x]=1;
		for(auto i:e[x])
        {
			int y=i.first,w=i.second+d[x];
			if(!vis[y]&&d[y]>w)
				q.push({d[y]=w,y});
		}
	}
	cout<<d[p+n];
}
```


---

## 作者：lfxxx (赞：0)

因为多测题对拍时没有造大小不同的数据导致没有在模拟赛场上场切，不过不妨碍这个题并不困难。

考虑先建立一个中转点 $u$，然后连边 $i \to u,a_u,u \to i,b_u$ 即可处理 $a_u + b_v < m$ 的情况。

把所有点按照 $b$ 从大到小排序，然后对于一个 $a$ 二分出最大前缀满足 $a+b \geq m$，然后向这个前缀点连边 $a+b-m$，前缀 $pre_i$ 向前缀 $pre_{i-1}$ 连一条 $b_{pre_{i-1}} - b_{pre_i}$ 的边。这样通过连向前缀的边表示实际边权，前缀之间的边表示实际边权差的方式就避免了负边权出现。

时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn  = 4e5+114;
int p[maxn],a[maxn],b[maxn],n,m;
int vis[maxn];
priority_queue< pair<int,int> > q;
bool cmp(int x,int y){
    return b[x]>b[y];
}
//n+1 2*n 前缀优化建图
//2*n+1 中转站
int dis[maxn];
vector< pair<int,int> > E[maxn];
void work(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        p[i]=i;
    }
    for(int i=1;i<=n;i++) cin>>b[i];
    sort(p+1,p+n+1,cmp);
    while(q.size()>0) q.pop();
    for(int i=1;i<=2*n+1;i++) E[i].clear(),dis[i]=1e15,vis[i]=0;
    for(int i=1;i<=n;i++){
        E[i].push_back(make_pair(2*n+1,a[i]));
        E[2*n+1].push_back(make_pair(i,b[i]));
    }
    for(int i=n+2;i<=2*n;i++){
        E[i].push_back(make_pair(i-1,b[p[i-n-1]]-b[p[i-n]]));
    }
    for(int i=n+1;i<=2*n;i++) E[i].push_back(make_pair(p[i-n],0));
    for(int i=1;i<=n;i++){
        if(a[i]+b[p[1]]>=m){
            int l=1,r=n+1;
            while(l+1<r){
                int mid=(l+r)>>1;
                if(a[i]+b[p[mid]]>=m) l=mid;
                else r=mid;
            }
            E[i].push_back(make_pair(l+n,a[i]+b[p[l]]-m));
        }
    }
    dis[1]=0;
    q.push(make_pair(-dis[1],1));
    while(q.size()>0){
        int u=q.top().second;
        q.pop();
        if(vis[u]==1) continue;
        vis[u]=1;
        for(pair<int,int> nxt:E[u]){
            int v=nxt.first,w=nxt.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push(make_pair(-dis[v],v));
            }
        }
    }
    cout<<dis[n]<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    work();
    return 0;
}
/*
0 5
4 12
10 11 6 0
8 7 4 1
4 12
10 11 6 0
8 7 4 1
4 12
10 11 6 0
8 7 4 1
4 12
10 11 6 0
8 7 4 1
4 12
10 11 6 0
8 7 4 1
*/
```

---

