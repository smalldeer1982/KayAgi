# Perfect Matching

## 题目描述

给出一棵树，节点编号 $1$ 到 $n$，边编号 $1$ 到 $n-1$。最初，只有节点 $1$ 是活跃的。

你需要实现以下三种操作：

- $1\ v$：激活节点 $v$ 。保证与 $v$ 直接相连的点中至少有一个是活跃的。在这之后，你需要选择一些边，使得它们端点都是活跃的，并且，每个活跃的节点在这些端点中刚好出现一次。换句话说，即选出一些边，使得它们与所有活跃的点之间有完美匹配（一个活跃的点匹配一条边，一条边匹配两个活跃的点）。然后输出所有选中的边的编号和。如果不存在这样的匹配，输出 0。
- $2$：保证此询问在某一次上一种询问之后。保证此询问不超过 10 次。如果上一个询问的结果是 0，请输出 0。否则，输出上一次询问之后所选的边的具体方案，具体的说：输出选的边的条数并从小到大输出所选边的编号。注意，本次输出的编号之和应该和你上一次输出的答案一致。
- $3$：请终止您的程序。

注意你的程序需要做到在线。这意味着你必须回答上一次询问后才能读入这一次询问，注意刷新缓冲区。

## 样例 #1

### 输入

```
6
1 4
6 1
3 2
1 2
5 1
1 4
2
1 2
2
1 3
2
1 5
1 6
2
3```

### 输出

```
1
1 1
0
0
4
2 1 3
0
0
0```

# 题解

## 作者：Tyyyyyy (赞：4)

## CF1633F

### 题意简述
给定一棵 $n$ 个点的树，初始时只有 $1$ 号点被激活。

处理两种操作：

- 激活一个点 $v$，保证至少有一个与 $v$ 相邻的点已被激活。输出所有已被激活的点构成的树的任意一个完美匹配中边的编号之和。

- 输出已被激活的点构成的树的任意一个完美匹配。最多 $10$ 个这样的询问。

$1\leq n\leq 2\times 10^5$，询问次数最多为 $2n+9$。本题强制在线。

### 题目分析
首先考虑解决树不变时的问题。显然首先要选择与叶子节点直接相连的边，然后隔一条选一条，看是否合法。

如果我们设一个点的状态 $f_u=0/1$，且 $f_u=1$，当且仅当连接 $u$ 和其父节点的边被选择，那么我们对于一个叶子节点的选边就是把它到根的路径上所有的 $f_u$ 取反。

用树剖 + 线段树就可以很方便地维护这个区间取反的过程。我们还要在线段树中记录选择的边数 $cnt$。如果全局 $cnt=\frac{n}{2}$，那么就合法。

然后现在这道题是不断加点，因为新加的点肯定是叶子，所以我们上面的做法可以直接做这道题。至于输出方案，因为不超过 $10$ 次询问所以直接暴力 dfs 就可以了。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,tot,h[N];
struct edge
{
	int v,w,nxt;
}e[N<<1];
void add(int u,int v,int w)
{
	e[++tot]=(edge){v,w,h[u]};
	h[u]=tot;
}
int fa[N],siz[N],dep[N],wson[N];
void prework(int u)
{
	siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u])continue;
		fa[v]=u,dep[v]=dep[u]+1;
		prework(v),siz[u]+=siz[v];
		if(siz[wson[u]]<siz[v])wson[u]=v;
	}
}
int dfn[N],id[N],idx,top[N],a[N];
void dfs(int u,int t)
{
	top[u]=t,id[dfn[u]=++idx]=u;
	if(wson[u])dfs(wson[u],t);
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==wson[u])a[v]=e[i].w; 
		if(v==fa[u]||v==wson[u])continue;
		dfs(v,v),a[v]=e[i].w;
	}
}
struct SegmentTree
{
	ll sum[N<<2],s[N<<2];
	int cnt[N<<2],tag[N<<2];
	void pushup(int p){s[p]=s[p<<1]+s[p<<1|1],cnt[p]=cnt[p<<1]+cnt[p<<1|1];}
	void adtag(int p,int l,int r)
	{
		tag[p]^=1,cnt[p]=(r-l+1)-cnt[p],s[p]=sum[p]-s[p];
	}
	void pushdown(int p,int l,int r)
	{
		if(!tag[p])return;
		int mid=(l+r)>>1;
		adtag(p<<1,l,mid),adtag(p<<1|1,mid+1,r);
		tag[p]=0;
	}
	void build(int p,int l,int r)
	{
		if(l==r){cnt[p]=(l==1),sum[p]=a[id[l]];return;}
		int mid=(l+r)>>1;
		build(p<<1,l,mid),build(p<<1|1,mid+1,r);
		pushup(p),sum[p]=sum[p<<1]+sum[p<<1|1];
	}
	void upd(int p,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R){adtag(p,l,r);return;}
		pushdown(p,l,r);
		int mid=(l+r)>>1;
		if(L<=mid)upd(p<<1,l,mid,L,R);
		if(R>mid)upd(p<<1|1,mid+1,r,L,R);
		pushup(p);
	}
}segt;
bool act[N],chs[N];
int acnt;
vector<int>way; 
void getans(int u)
{
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u]||!act[v])continue;
		getans(v);
		if(!chs[v])chs[u]=1,way.push_back(e[i].w);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),add(x,y,i),add(y,x,i);
	prework(1),dfs(1,1),segt.build(1,1,n),act[1]=1,acnt=1;
	int op,u;ll ans=0;
	while(1)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d",&u);
			act[u]=1,acnt++;
			while(u)
			{
				segt.upd(1,1,n,dfn[top[u]],dfn[u]);
				u=fa[top[u]];
			}
			if(segt.cnt[1]*2==acnt)ans=segt.s[1];
			else ans=0;
			printf("%lld\n",ans),fflush(stdout);
		}
		else if(op==2)
		{
			if(ans)
			{
				way.resize(0),memset(chs,0,sizeof(chs));
				getans(1),sort(way.begin(),way.end());
				printf("%d ",(int)way.size()),fflush(stdout);
				for(int x:way)printf("%d ",x),fflush(stdout);
				puts(""),fflush(stdout);
			}
			else puts("0"),fflush(stdout);
		}
		else break;
	}
	return 0;
}
```

---

## 作者：cirnovsky (赞：4)

 首先所有的 activated nodes 组合成了一棵以 $1$ 为根的有根树。询问即求由 activated nodes 组成的树的最大匹配。对于树上最大匹配有一个贪心策略：自底向上匹配当前点和其父亲，删除这两个点，直至只剩一个点或空树。若为空树，则树存在完美匹配。
 
> **Claim：** 对于树 $\textbf{T}=(\textbf{V},\textbf{E})$，若存在完美匹配，当且仅当 $\displaystyle\left(\sum_{u\in\textbf{V}}[|\text{subtree}(u)|\bmod2=1]\right)=\left(\sum_{u\in\textbf{V}}[|\text{subtree}(u)|\bmod2=0]\right)$

> **Proof：** 两个简单的观察即可证明：（1）每个子树大小为偶数的结点有且仅有一个子树大小为奇数的后继；（2）每个子树大小为奇数的结点的父亲子树大小为偶数。
>
> 所以偶数奇数两两对应，以上论断的充分性得证。其必要性的正确性比较平凡，故略。

然后我们需要支持的操作就只有加入一个叶子结点，反转一条无拐点的链上结点的标记。整棵树的形态是固定的，HLD 维护即可。具体方案的询问次数不超过 10 次，朴素 $O(n)$ 寻找即可。

然而翻转链部分暴力也能过而且和线段树没啥本质区别……

```cpp
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
#define cmin(x, y) x = std::min(x, y)
#define cmax(x, y) x = std::max(x, y)
#define fors(i, l, r, ...) for(int i = (l), REP##i = (r), ##__VA_ARGS__; i <= REP##i; ++i)
#define dfors(i, r, l, ...) for(int i = (r), REP##i = (l), ##__VA_ARGS__; i >= REP##i; --i)
int n, up[200100], all, on[200100], cnt, sz[200100], son[200100], top[200100], fa[200100], dfn[200100];
// params: @up[i]: identity of edge (i, fa[i]); @on[i]: is rev[i] activated; @all: amout of nodes activated;
//      @cnt: amout of odd nodes
std::vector<std::pair<int, int>> adj[200100];
std::set<int> S;
long long ans;
namespace hld {
    int tt;
    void dfs_sz(const int x, const int fa) {
        sz[x] = 1, ::fa[x] = fa;
        for(const auto [y, id] : adj[x]) if(y != fa) {
            dfs_sz(y, x);
            if(sz[y] > sz[son[x]]) son[x] = y;
        }
    }
    void dfs_hld(const int x, const int tp) {
        top[x] = tp, dfn[x] = ++tt;
        if(son[x]) dfs_hld(son[x], tp);
        for(const auto [y, id] : adj[x]) {
            if(y == fa[x]) up[dfn[x]] = id;
            if(y != fa[x] && y != son[x]) dfs_hld(y, y);
        }
    }
    void init() { dfs_sz(1, 0), dfs_hld(1, 1); }
}
signed main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    fors(i, 1, n-1, x, y) {
        std::cin >> x >> y;
        adj[x].emplace_back(y, i);
        adj[y].emplace_back(x, i);
    }
    on[1] = all = cnt = 1, hld::init();
    for(int op, x; "eternal love"; std::cout << "\n") {
        if(std::cin >> op, S.clear(); op == 1) {
            for(std::cin >> x, all++; x; x = fa[top[x]])
                fors(i, dfn[top[x]], dfn[x]) cnt += (on[i]?-1:1),ans += (on[i]?-1:1)*up[i],on[i] ^= 1;
            std::cout << ((all == cnt*2)?ans:0);
        } else if(op == 2) {
            if(all != cnt*2) std::cout << "0";
            else {
                fors(i, 2, n) if(on[i]) S.emplace(up[i]);
                std::cout << cnt;
                for(const int x : S) std::cout << " " << x;
            }
        } else break;
    }
    return 0;
}
```

---

