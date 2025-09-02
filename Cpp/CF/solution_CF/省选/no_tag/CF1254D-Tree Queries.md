# Tree Queries

## 题目描述

Hanh is a famous biologist. He loves growing trees and doing experiments on his own garden.

One day, he got a tree consisting of $ n $ vertices. Vertices are numbered from $ 1 $ to $ n $ . A tree with $ n $ vertices is an undirected connected graph with $ n-1 $ edges. Initially, Hanh sets the value of every vertex to $ 0 $ .

Now, Hanh performs $ q $ operations, each is either of the following types:

- Type $ 1 $ : Hanh selects a vertex $ v $ and an integer $ d $ . Then he chooses some vertex $ r $ uniformly at random, lists all vertices $ u $ such that the path from $ r $ to $ u $ passes through $ v $ . Hanh then increases the value of all such vertices $ u $ by $ d $ .
- Type $ 2 $ : Hanh selects a vertex $ v $ and calculates the expected value of $ v $ .

Since Hanh is good at biology but not math, he needs your help on these operations.

## 说明/提示

The image below shows the tree in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254D/8305f689c4b5cb634af4d0b9b9cf646ab39a9a7b.png)For the first query, where $ v = 1 $ and $ d = 1 $ :

- If $ r = 1 $ , the values of all vertices get increased.
- If $ r = 2 $ , the values of vertices $ 1 $ and $ 3 $ get increased.
- If $ r = 3 $ , the values of vertices $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ get increased.
- If $ r = 4 $ , the values of vertices $ 1 $ and $ 3 $ get increased.
- If $ r = 5 $ , the values of vertices $ 1 $ and $ 3 $ get increased.

Hence, the expected values of all vertices after this query are ( $ 1, 0.4, 0.8, 0.4, 0.4 $ ).

For the second query, where $ v = 2 $ and $ d = 2 $ :

- If $ r = 1 $ , the values of vertices $ 2 $ , $ 4 $ and $ 5 $ get increased.
- If $ r = 2 $ , the values of all vertices get increased.
- If $ r = 3 $ , the values of vertices $ 2 $ , $ 4 $ and $ 5 $ get increased.
- If $ r = 4 $ , the values of vertices $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ get increased.
- If $ r = 5 $ , the values of vertices $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ get increased.

Hence, the expected values of all vertices after this query are ( $ 2.2, 2.4, 2, 2, 2 $ ).

## 样例 #1

### 输入

```
5 12
1 2
1 3
2 4
2 5
1 1 1
2 1
2 2
2 3
2 4
2 5
1 2 2
2 1
2 2
2 3
2 4
2 5
```

### 输出

```
1
199648871
399297742
199648871
199648871
598946614
199648873
2
2
2
```

# 题解

## 作者：AThousandSuns (赞：7)

~~套路题怎么能没有题解呢？~~

在我的博客看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/11922292.html)

出题人的做法是 $O(n\sqrt{n\log n})$，结果这场结束后就被狂喷，一群人给出了 $O(n\sqrt{n})$ 做法，甚至 $O(n\log n)$ 都出来了……

首先发现，修改一个点时，如果把这个点看成根，其它点权期望的变化只和在根的哪个儿子的子树中有关，$\frac{n-sz[u]}{n}d$（选除了这个子树中的点都能经过 $x$）。

$O(n\sqrt{n\log n})$ 很显然，对修改的点的度数分类讨论，度数小的就是一堆子树加，度数大的就打个标记，查询的时候把大点的贡献也算上就行了。

$O(n\sqrt{n})$ 的话，把线段树/树状数组换成分块。度数小的修改复杂度总共是 $O(\text{块数}+\text{度数})$（每棵子树的区间不交）。

$O(n\log n)$ 就不用度数根号分治了。

考虑树剖（似乎很套路？），修改一个点时，只需要对重子树和外子树区间加。

询问一个点时，发现需要再统计的就是跳重链时，从一条链跳到另外一条链时链头和父亲之间的贡献（只有这时才是轻儿子）。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=300030,mod=998244353;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,q,el,head[maxn],to[maxn],nxt[maxn],b[maxn],dep[maxn],sz[maxn],son[maxn],fa[maxn],top[maxn],lft[maxn],rig[maxn],cnt,tag[maxn];
inline void add(int u,int v){
	to[++el]=v;nxt[el]=head[u];head[u]=el;
}
inline int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
	return ans;
}
inline void update(int p,int v){
	for(int i=p;i<=n;i+=i&-i) b[i]=(b[i]+v)%mod;
}
inline void update(int l,int r,int v){
	update(l,v);update(r+1,(mod-v)%mod);
}
inline int query(int p){
	int s=0;
	for(int i=p;i;i-=i&-i) s=(s+b[i])%mod;
	return s;
}
void dfs1(int u,int f){
	dep[u]=dep[fa[u]=f]+1;
	sz[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==f) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v; 
	}
}
void dfs2(int u,int topf){
	top[u]=topf;
	lft[u]=++cnt;
	if(son[u]) dfs2(son[u],topf);
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa[u] || v==son[u]) continue;
		dfs2(v,v);
	}
	rig[u]=cnt;
}
void update_tree(int u,int d){
	tag[u]=(tag[u]+d)%mod;
	if(son[u]) update(lft[son[u]],rig[son[u]],1ll*(n-sz[son[u]])*d%mod);
	if(u!=1){
		update(1,lft[u]-1,1ll*sz[u]*d%mod);
		if(rig[u]!=n) update(rig[u]+1,n,1ll*sz[u]*d%mod);
	}
}
int query_tree(int u){
	int s=(1ll*n*tag[u]+query(lft[u]))%mod;
	while(u){
		s=(s+1ll*tag[fa[top[u]]]*(n-sz[top[u]]))%mod; 
		u=fa[top[u]];
	}
	return s;
}
int main(){
	n=read();q=read();
	int inv=qpow(n,mod-2);
	FOR(i,1,n-1){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs1(1,0);dfs2(1,1);
	while(q--){
		int tp=read(),u=read();
		if(tp==1) update_tree(u,1ll*inv*read()%mod);
		else printf("%d\n",query_tree(u));
	}
}
```

---

## 作者：FZzzz (赞：6)

ATS大佬给的树剖题，看了两眼不会就翻题解。

结果……竟然没有题解？

然后自己写，结果就A了。

------------
这题出得很好。

首先考虑，对 $v$ 使用操作 $1$ ，本质上是什么呢？

为方便思考，这里把整棵树的根换为 $v$。然后发现：
- 如果 $r\not=v$，那么任何与 $r$ 不在同一子树内的节点都会加 $d$；
- 如果 $r=v$，那就是全加。

所以说，设节点 $u\not=v$ 所在的子树大小为 $size_u$，则 $u$ 被加 $d$ 的概率为 $\frac{n-size_u}{n}$。

那么我们就忽略这个分母 $n$，输出的时候再乘个逆元就可以了。

然后我们考虑如何维护。

我们发现这里只有单点查询，那我们考虑树上查分，维护每个点减去其父节点。

但是这样的话每次操作 $1$ 要维护每个子节点啊？造个菊花不就 gg 了。

这里有一个比较套路的方法：

我们树剖，然后只更重儿子。每次查询就往上跳链，然后加上链顶的贡献。

由于最多跳 $O(\log n)$ 条链，所以复杂度 $O(n\log n)$。

upd：当时太年轻，复杂度都算错了，感谢 @hs_blakck 神仙的指正，查询复杂度为 $O(\log^2n)$

code：
```cpp
#include<vector>
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
    while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=150000+5;
int n,q;
vector<int> g[maxn];
int fa[maxn],size[maxn],hson[maxn];
void dfs1(int u){
	size[u]=1;
	hson[u]=0;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs1(v);
		size[u]+=size[v];
		if(size[v]>size[hson[u]]) hson[u]=v; 
	}
}
int cnt=0,top[maxn],pos[maxn];
void dfs2(int u){
	pos[u]=++cnt;
	if(hson[u]){
		top[hson[u]]=top[u];
		dfs2(hson[u]);
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]||v==hson[u]) continue;
		top[v]=v;
		dfs2(v);
	}
}
typedef long long ll;
const ll mod=998244353;
ll c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void update(int x,ll k){
	while(x<=n){
		c[x]=(c[x]+k)%mod;
		x+=lowbit(x);
	}
}
ll query(int x){
	ll s=0;
	while(x>0){
		s=(s+c[x])%mod;
		x-=lowbit(x);
	}
	return s;
}
ll ksm(ll a,ll b){
	ll ans=1;
	while(b!=0){
		if(b%2==1) ans=ans*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ans;
}
ll invn;
ll tag[maxn];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    q=readint();
    for(int i=1;i<n;i++){
    	int u,v;
    	u=readint();
    	v=readint();
    	g[u].push_back(v);
    	g[v].push_back(u);
	}
	fa[1]=0;
	size[0]=0;
	dfs1(1);
	top[1]=1;
	dfs2(1);
	memset(c,0,sizeof(c));
	invn=ksm(n,mod-2);
	memset(tag,0,sizeof(tag));
	while(q--){
		int opt=readint();
		if(opt==1){
			int v=readint();
			ll d=readint();
			if(v!=1) update(pos[v],d*(n-size[v])%mod);
			update(1,d*size[v]%mod);
			if(hson[v]) update(pos[v]+1,d*(mod-size[hson[v]])%mod);
			tag[v]=(tag[v]+d)%mod;
		}
		else{
			int v=readint();
			ll ans=0;
			while(top[v]!=1){
				ans=(((ans+query(pos[v]))%mod+mod-query(pos[top[v]]-1))%mod+tag[fa[top[v]]]*(mod-size[top[v]])%mod)%mod;
				v=fa[top[v]];
			}
			ans=(ans+query(pos[v]))%mod;
			printf("%d\n",(int)(ans*invn%mod));
		}
	}
	return 0;
}
```


---

## 作者：xfrvq (赞：5)

[$\tt Link$](/problem/CF1254D)。

考虑分析一次修改的本质是什么：

+ 对于一次修改 $u,x$，我们删去 $u$，会出现若干联通块。
+ 对于一个大小为 $s$ 的联通块，每个点加上 $\dfrac{n-s}n$。

不妨让每个点加的值从 $\dfrac{n-s}n$ 变成 $n-s$，最后乘上一个 $n^{-1}\bmod998244353$ 即可。

我们记一个点的度数为 $d_u$。然后考虑两种算法：

+ 暴力 $\tt1$：修改时枚举 $u$ 的所有儿子 $v$，暴力按上述式子加（子树加，使用修改复杂度 $\mathcal O(k)$ 的数据结构维护），最后处理父亲（父亲所在联通块的大小应该是 $n-u$ 的字数大小）
+ 暴力 $\tt2$：查询时枚举一些点 $v$（当然 $v\ne u$），然后判断 $u$ 在 $v$ 的哪个联通块（要么 $u$ 是 $v$ 的祖先，要么找到一个 $v$ 的儿子 $w$，使得 $w$ 是 $u$ 的祖先），然后根据所在联通块计算 $v$ 对 $u$ 的贡献是多少。

哦，但是还要注意如果发生过修改 $\{u,x\}$，那么 $u$ 的答案最后要加上 $x$。

这两种算法的复杂度分别是 $\mathcal O(kd_u)$ 和 $\mathcal O(t)$，其中 $t$ 是你选择枚举的点数，$k$ 是你选择的数据结构修改的复杂度。

这并不优。于是常规手段，根号摊平。（以下的查询指计算这个点对其它点的贡献）

+ 对于 $d_u\le\sqrt n$ 的点的修改，使用暴力 $\tt1$ 中的修改。
+ 对于 $d_u\le\sqrt n$ 的点的查询，用数据结构算出任何 $d_v\le\sqrt n$ 的 $v$ 对 $u$ 的答案。
+ 对于 $d_u\gt\sqrt n$ 的点的修改，考虑跳过，直接摆烂。
+ 对于 $d_u\gt\sqrt n$ 的点的查询，枚举这些点（总个数 $t=\mathcal O(\dfrac n{\sqrt n})=\mathcal O(\sqrt n)$），然后计算贡献。

数据结构我们希望做到修改 $\mathcal O(1)$，这样才能保证最后根号的复杂度。

根号题用根号 $\tt DS$ 是极好的，我们选择采用序列分块，这个子树加单点和是常规的 $\tt dfs$ 时间戳。

在补充说说。暴力 $\tt2$ 里有一步是对于 $u,v$ 要找到一个 $w$，满足 $w$ 是 $v$ 的儿子，也是 $u$ 的祖先。这一步其实挺像 $\tt LCA$，考虑树剖解决：

我们魔改树求 $\tt LCA$，在最后一步，两个点都在一条重链的时候，深度小的那个点在重链上的儿子就是答案。

还有一种情况，就是它们中深度小的那个在重链底，这时答案是它的某个轻儿子，我们无法得知。这种情况需要在跳重链的时候，如果某一步出现 $x$ 的重链顶的父亲是 $y$，就不跳了，返回 $x$ 的重链顶就是答案。

我觉得写的可读性已经很高了。

如果 $\texttt{WA on test 6}$ 且某个结果你输出了负数，那么不妨检查哪一步没有取模，并且最后判断：如果自己的答案是负数，应该加上模数保证输出的结果不是负数。

```cpp
const int N = 1.5e5 + 5,SQ = 405;
const ll mod = 998244353;

int n,m; ll inv_n,add[N];
vector<int> G[N],big;

int B,C,st[SQ],ed[SQ],bl[N];
ll sum[SQ],cnt[N];

int dep[N],siz[N],son[N],fa[N];
int dfn[N],top[N],tot = 0;

#define Big(i) ((signed)G[i].size() > B)
#define rdfn(u) dfn[u] + siz[u] - 1
#define subt(u) dfn[u],rdfn(u)

namespace HLC{
	void dfs1(int u = 1,int ft = 0){
		dep[u] = dep[fa[u] = ft] + (siz[u] = 1);
		for(int v : G[u]) if(v != ft){
			dfs1(v,u); siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		} if(Big(u)) big.push_back(u);
	}
	
	void dfs2(int u = 1,int tp = 1){
		dfn[u] = ++tot; top[u] = tp;
		if(son[u]) dfs2(son[u],tp);
		for(int v : G[u]) if(!top[v]) dfs2(v,v);
	}
	
	int son_lca(int x,int y){
		while(top[x] != top[y]){
			if(dep[top[x]] < dep[top[y]]) swap(x,y);
			if(fa[top[x]] == y) return top[x];
			x = fa[top[x]];
		} return son[dep[x] < dep[y] ? x : y];
	}
} using namespace HLC;

namespace DS{
	void init(){
		B = sqrt(n); C = (n - 1) / B + 1;
		rep(i,1,C){
			st[i] = ed[i - 1] + 1;
			ed[i] = i == C ? n : i * B;
			rep(j,st[i],ed[i]) bl[j] = i;
		}
	}
	
	void upd(int l,int r,ll x){
		x %= mod; ++r;
		(cnt[l] += x) %= mod;
		(cnt[r] += mod - x) %= mod;
		(sum[bl[l]] += x) %= mod;
		(sum[bl[r]] += mod - x) %= mod;
	}
	
	ll qry(int p){
		ll res = 0;
		rep(i,1,bl[p] - 1) (res += sum[i]) %= mod;
		rep(i,st[bl[p]],p) (res += cnt[i]) %= mod;
		return res;
	}
} using namespace DS;

void Upd(int u,ll x){
	(add[u] += x) %= mod; if(Big(u)) return;
	for(int v : G[u]) if(v != fa[u])
		DS::upd(subt(v),x * (n - siz[v]));
	if(u == 1) return;
	ll y = x * siz[u]; upd(subt(1),y); upd(subt(u),-y);
}

ll Qry(int u){
	ll res = qry(dfn[u]);
	for(int v : big) if(u != v){
		if(!(dfn[v] <= dfn[u] && rdfn(u) <= rdfn(v)))
			(res += add[v] * siz[v] % mod) %= mod;
		else (res += add[v] * (n - siz[son_lca(u,v)]) % mod) %= mod;
	} res = ((inv_n * res % mod) + add[u]) % mod;
	return (res % mod + mod) % mod;
}

ll fpow(ll v,int b){
	ll res = 1;
	while(b){
		if(b & 1) (res *= v) %= mod;
		(v *= v) %= mod; b >>= 1;
	}
	return res;
}

signed main(){
	read(n,m);
	inv_n = fpow(n,mod - 2);
	rep(i,1,n - 1){
		int u,v; read(u,v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	init(); dfs1(); dfs2();
	while(m--){
		if(read() == 1){ int x = read(); Upd(x,read()); }
		else print(Qry(read()),'\n');
	}
	return 0;
}
```

---

## 作者：UnyieldingTrilobite (赞：5)

首先这个期望就很不好看，我们直接在操作时把所有 $r$ 都做一遍，查询的时候除以 $n$ 即可。

考虑如何有效地进行操作。对于每一个点 $u$，如果选取的 $r$ 对 $u$ 的权值产生了贡献，那么当且仅当 $u$ 到 $r$ 的路径经过 $v$（定义），**也就是分为了以下三类。**

1. $u=v$

挂着不管。

2. $u$ 在 $v$ 的子树外，那么 $r$ 在 $v$ 的子树内。

这部分直接把树拍扁成深度优先序然后上线段树区间加就好了。

3. $u$ 在 $v$ 的子树内。

此时 $r$ 只需要和 $u$ 不在 $v$ 的同一棵子树内就可以了。我们想模仿 $u$ 在 $v$ 的子树外那样维护，但是发现这样的话需要遍历 $v$ 的所有子树，来个菊花图就可以卡爆——于是我们想到了树剖优化。

那么继续分成两个小类： $u$ 是否在 $v$ 的重儿子对应的子树内。

如果是，直接区间加；

如果不是，那就不管了先。

查询的时候，首先统计一下这个点上挂着的值，然后线段树单点求值统计一下这个点大部分祖先放下来的贡献。

然后我们往上沿着重链跳：每次跳到链顶，此时这个点一定是其父亲（若存在）的亲儿子，也就是说正好只有这些点的父亲的贡献还没有统计到，那么看看其父亲挂了多少值，算一下就好了。

代码很好写。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1.5e5 + 9, mod = 998244353;
int n, q, invn, fa[N], sz[N], sn[N], top[N], dfn[N], ed[N], val[N];
vector<int> tr[N];
int zkw[N << 2], M = 1;
int qpow(int bs, int pw) {
  int ret = 1;
  while (pw) {
    if (pw & 1) (ret *= bs) %= mod;
    pw >>= 1, (bs *= bs) %= mod;
  }
  return ret;
}
void dfs1(int x) {
  sz[x] = 1;
  for (int& y : tr[x])
    if (y != fa[x]) {
      fa[y] = x, dfs1(y);
      sz[x] += sz[y];
      if (sz[y] > sz[sn[x]]) sn[x] = y, swap(tr[x][0], y);
    }
}
void dfs2(int x) {
  dfn[x] = ++dfn[0];
  top[x] = sn[fa[x]] == x ? top[fa[x]] : x;
  for (int y : tr[x])
    if (y != fa[x]) dfs2(y);
  ed[x] = dfn[0];
}
void update(int l, int r, int v) {
  if (l > r) return;
  for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
    if (~l & 1) zkw[l ^ 1] += v;
    if (r & 1) zkw[r ^ 1] += v;
  }
}
int query(int x) {
  int ret = 0;
  for (x += M; x; x >>= 1) ret += zkw[x];
  return ret;
}
signed main() {
  cin >> n >> q, invn = qpow(n, mod - 2);
  while (M <= n) M <<= 1;
  for (int i = 1, u, v; i < n; ++i)
    cin >> u >> v, tr[u].push_back(v), tr[v].push_back(u);
  dfs1(1), dfs2(1);
  while (q--) {
    int op, v;
    cin >> op >> v;
    if (op == 1) {
      int d;
      cin >> d;
      (val[v] += d) %= mod;
      update(1, dfn[v] - 1, sz[v] * d % mod);
      update(ed[v] + 1, n, sz[v] * d % mod);
      update(dfn[sn[v]], ed[sn[v]], (n - sz[sn[v]]) * d % mod);
    } else {
      int ret = val[v] * n + query(dfn[v]);
      while (fa[v = top[v]]) ret += (n - sz[v]) * val[fa[v]] % mod, v = fa[v];
      cout << (ret % mod * invn) % mod << endl;
    }
  }
  return 0;
}
```

Over.

---

## 作者：Lily_White (赞：5)

我们知道，对于对 $v$ 的查询，假定 $v$ 是树根，如果 $r$ 和 $u$ 在同一个子树内，则 $v$ 不在路径上，不会加 $d$；否则会加上 $d$。

也就是说，随机选择一个点，它被加上 $d$ 的概率是 $P=\dfrac{n - \operatorname{sz}(u)}n$，因此，期望值会增加 $Pd$。实际上，我们可以忽略 $n$，最后乘上逆元即可。

下面的问题就是如何高效维护上面的操作了。

路径操作可以让我们想到 HLD（树链剖分）。不过，这里的 HLD 维护的是**树上差分**。我们注意到，如果我们只更新重儿子的话

- 如果此时在重链上，那么已经直接维护好了
- 如果此时在轻链上，我们就跳到链顶。此时，加上链顶的贡献即可。

（这边可以自己画个图理解一下）

维护直接上 Fenwick Tree 就可以了。

```cpp
const int N = 200020;
int n, m;
struct Fenwick {
  int arr[N + 15];
  void modify(int x, int d) {
    for (; x <= N; x += x & (-x)) {
      arr[x] = (arr[x] + d) % mod;
    }
  }
  int query(int x) {
    LL res = 0;
    for (; x; x -= x & (-x)) {
      res = (res + arr[x]) % mod;
    }
    return res;
  }
} fenwick;
int top[N], dfn[N], dep[N], fa[N], hson[N], sz[N];
VI g[N];
void dfs1(int u) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == fa[u]) continue;
    dep[v] = dep[u] + 1;
    fa[v] = u;
    dfs1(v);
    sz[u] += sz[v];
    if (sz[v] > sz[hson[u]]) hson[u] = v;
  }
}
int in[N], out[N];
int tot;
void dfs2(int u, int t) {
  top[u] = t;
  in[u] = dfn[u] = ++tot;
  if (hson[u]) dfs2(hson[u], t);
  for (auto v : g[u])
    if (v != hson[u] && v != fa[u]) dfs2(v, v);
  out[u] = tot;
}
LL qpow(LL a, LL b = mod - 2) {
  LL ans = 1;
  for (; b; b >>= 1) {
    if (b & 1) ans = ans * a % mod;
    a = a * a % mod;
  }
  return ans % mod;
}
int lazy[N];
void solve() {
  n = qread();
  m = qread();
  rep(i, n - 1) {
    int u = qread(), v = qread();
    g[u].pb(v);
    g[v].pb(u);
  }
  fa[1] = 1;
  dep[1] = 1;
  dfs1(1);
  dfs2(1, 1);
  int invn = qpow(n);
  while (m--) {
    int op = qread();
    if (op == 1) {
      int u = qread(), d = qread();
      if (u != 1) fenwick.modify(dfn[u], d * (n - sz[u]) % mod);
      fenwick.modify(1, d * sz[u] % mod);
      if (hson[u])
        fenwick.modify(dfn[u] + 1, d * (mod - sz[hson[u]]) % mod);//对于重儿子，在 BIT 上修改。
      lazy[u] = (lazy[u] + d) % mod;//对于非重儿子，累加标记
    } else {
      int u = qread();
      LL ans = 0;
      while (top[u] != 1) {
        ans = (
                (
                  (ans + fenwick.query(dfn[u])) % mod 
                  + mod * 2 - fenwick.query(dfn[top[u]] - 1)
                ) % mod
                  + lazy[fa[top[u]]] * (mod * 2 - sz[top[u]]) % mod//加上链顶的贡献
              ) % mod;
        u = fa[top[u]];
      }
      ans = (ans + fenwick.query(dfn[u])) % mod;
      printf("%lld\n", (int)(ans * invn % mod));
    }
  }

}
signed main() {
  int T = 1;
  // T = qread();
  while (T--) solve();
  return 0;
}
```

---

## 作者：Add_Catalyst (赞：1)

# CF1254D Tree Queries 题解

------

## 知识点

树剖，树状数组，线段树，DFS 序。

------

## 分析

首先知道，题目中的期望就是骗人的，我们先不除以 $n$，等把答案统计完了之后再除以一个 $n$ 即可。

接下来考虑如何统计：

- 在更新的时候将点分种类讨论：假设现在更新操作为 `1 v d`。

  1. 对于点 $v$：

     直接加上 $nd$，因为所有的路径都一定经过它。

     直接在外面开一个数组记下来就好了，时间复杂度 $O(1)$。

  2. 对于不在 $v$ 子树内的点：

     对于这些点，每个有可能的 $r$ 都在 $v$ 的子树内，所以都要加上 $siz_vd$。

     直接 DFN 区间加即可，时间复杂度 $O(\log_2{n})$。

  3. 其余在 $v$ 子树内的点：

     对于某个点 $u$，设 $v$ 离它最近的子节点为 $x$，那么有可能的 $r$ 都在 $x$ 的子树外，所以要加上 $(n-siz_x)d$，但是我们没有办法一个个访问子节点来修改，怎么办呢？

     我们考虑只将 $v$ 重儿子 $son$ 内的子节点加上 $(n-siz_{son})d$，然后在 $v$ 上打一个标记，这个标记是等到查询的时候再按树链走上来统计。

     所以要一个 DFN 区间加，和用数组记下查询时用的标记，时间复杂度 $O(\log_2{n})$。

- 现在看到查询：`2 v`。

  那么我们需要先把区间加的部分统计出来，把数组中标记的也加上，再按树链往上走，把没加的标记加上，时间复杂度 $O(\log_2{n})$。

## 代码

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define FOR(i,a,b) for(int i(a); i<=(int)(b); ++i)
#define DOR(i,a,b) for(int i(a); i>=(int)(b); --i)
#define EDGE(g,i,x,y) for(int i(g.h[x]),y(g[i].v); ~i; y=g[i=g[i].nxt].v)
using namespace std;
constexpr int N(1.5e5+10);

struct Ecat {
#define DE(...) E(#__VA_ARGS__,__VA_ARGS__)

	template<class T>void operator ()(const char *fmt,const T x) {
		cerr<<fmt<<':'<<x<<'.'<<endl;
	}

	template<class T,class...Types>void operator ()(const char *fmt,const T x,const Types...args) {
		while(*fmt^',')cerr<<*fmt++;
		return cerr<<':'<<x<<" ,",(*this)(++fmt,args...);
	}

} E;

namespace Modular {
#define Mod 998244353
	template<class T1,class T2>constexpr auto add(const T1 a,const T2 b) {
		return a+b>=Mod?a+b-Mod:a+b;
	}

	template<class T1,class T2>constexpr auto mul(const T1 a,const T2 b) {
		return (ll)a*b%Mod;
	}

	template<class T,class...Types>constexpr auto add(const T a,const Types...args) {
		return add(a,add(args...));
	}

	template<class T,class...Types>constexpr auto mul(const T a,const Types...args) {
		return mul(a,mul(args...));
	}

	template<class T1,class T2>T1 &toadd(T1 &a,const T2 b) {
		return a=add(a,b);
	}

	template<class T1,class T2>T1 &tomul(T1 &a,const T2 b) {
		return a=mul(a,b);
	}

	template<class T0,class T,class...Types>T0 &toadd(T0 &a,const T b,const Types...args) {
		return toadd(a,b),toadd(a,args...);
	}

	template<class T0,class T,class...Types>T0 &tomul(T0 &a,const T b,const Types...args) {
		return tomul(a,b),tomul(a,args...);
	}
	
	int Pow(int a,int b=Mod-2) {
		int res(1);
		for(a%=Mod; b; b>>=1,tomul(a,a))if(b&1)tomul(res,a);
		return res;
	}

} using namespace Modular;

int n,Q,idx;
int dl[N],dr[N],fa[N],dep[N],dfn[N],siz[N],son[N],top[N],tag[N];
vector<int> g[N];
struct BIT {
#define lowbit(i) ((i)&-(i))
	int c[N];
	
	void Plus(int x,int d) {
		if(x>0)for(; x<=n; x+=lowbit(x))toadd(c[x],d);
	}
	
	void Plus(int l,int r,int d) {
		Plus(l,d),Plus(r+1,Mod-d);
	}
	
	int Sum(int x) {
		int ans(0);
		if(x>0)for(; x; x&=x-1)toadd(ans,c[x]);
		return ans;
	}
	
} bit;

void dfs0(int u) {
	dep[u]=dep[fa[u]]+1,siz[u]=1,son[u]=0;
	for(int v:g[u])if(v^fa[u])fa[v]=u,dfs0(v),siz[u]+=siz[v],son[u]=(siz[v]>siz[son[u]]?v:son[u]);
}

void dfs1(int u) {
	dfn[dl[u]=++idx]=u;
	if(son[u])top[son[u]]=top[u],dfs1(son[u]);
	for(int v:g[u])if(v!=fa[u]&&v!=son[u])dfs1(top[v]=v);
	dr[u]=idx;
}

int main() {
	cin>>n>>Q;
	FOR(i,2,n) {
		int u,v;
		cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	}
	dfs0(1),dfs1(top[1]=1);
	while(Q--) {
		int c,v,d;
		cin>>c>>v;
		if(c==1) {
			cin>>d,toadd(tag[v],d);
			if(dl[v]>1)bit.Plus(1,dl[v]-1,mul(siz[v],d));
			if(dr[v]<n)bit.Plus(dr[v]+1,n,mul(siz[v],d));
			if(son[v])bit.Plus(dl[son[v]],dr[son[v]],mul(n-siz[son[v]],d));
		} else {
			int ans(add(bit.Sum(dl[v]),mul(tag[v],n)));
			for(int u(v); fa[top[u]]; u=fa[top[u]])toadd(ans,mul(n-siz[top[u]],tag[fa[top[u]]]));
			cout<<mul(ans,Pow(n))<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Nelofus (赞：1)

比 std 少了一个 $\sqrt n$，很牛。但这个 $\mathcal O(n\log n)$ 做法不是纯套路吗？

首先期望一眼就知道是假的，所有数分母都是 $n$，最后除掉就好。

修改就变成，删掉点 $u$ 之后每个连通块大小如果是 $s$，那就加上 $(n-s)\times d$。

考虑删掉 $u$ 之后的影响，$u$ 子树以外的部分是 dfn 序的一段前后缀，直接加上 $(n-(n-siz_u))\times d=siz_u\times d$ 即可。

那 $u$ 的子树显然不能暴力维护。重剖，考虑对重子树 $w$ 里的每个数加上 $(n-siz_w)\times d$，对轻子树 $v$ 不做修改，修改挂在 $u$ 上，轻子树 $v$ 里面的节点在询问的时候暴力跳链，然后加上链顶父亲的标记的贡献即可。也就是如果当前链顶是 $c$，那就加上 $(n-siz_c)\times tag_{fa(c)}$。

两部分贡献加起来就行了。

[Code Link](https://codeforces.com/contest/1254/submission/262028838)

---

## 作者：zhylj (赞：1)

随便刷 CF 刷到这道题，然后想了个常数巨大的 $\mathcal O(n\sqrt n)$ 做法。（大概和其它题解不太一样）

---

考虑修改相当于给 $u$ 的所有相邻的点 $v$ 所在子树加 $(n - {\rm siz}_v)\cdot \dfrac dn$.（这里的 ${\rm siz}_v$ 指的是断掉 $(u,v)$ 这条边后 $v$ 所在连通块的大小）我们不妨令 $d\leftarrow \dfrac dn$.

我们先考虑假如查询全在修改之后怎么做，我们可以把对于同一个点的修改合并（$d$ 全部加起来），然后暴力给每个点打树上差分标记，再暴力给树上差分做树上前缀和，做一次的时间复杂度是 $\mathcal O(n)$ 的。

于是想到，能否想到另外一个做法，使得我们每隔 $B$ 个操作进行一次上述操作暴力应用修改，然后对于这 $B$ 个操作暴力查它们之间的影响。

注意到，我们要判断一个操作对一个询问的影响，唯一需要知道的事就是询问的点 $v$ 在修改作用于的点 $u$ 的**哪一棵子树**内。

随便拿个点做根，记 $v$ 的深度为 $d_v$，$v$ 的父亲为 ${\rm fa}_v$，则（下文的 ${\rm siz}_v$ 指的是断掉 $({\rm fa}_v, v)$ 这条边后 $v$ 所在连通块的大小）：

- 若 $u = v$，则该修改对询问贡献 $n\cdot d$.
- 若 $d_u \ge d_v $，显然 $v$ 只会在 $u$ 父亲所在子树内，该修改对询问贡献 ${\rm siz}_u\cdot d$.
- 否则，考虑跳到 $v$ 的 $d_v - d_u - 1$ 级祖先 $x$，其深度恰好与 $u$ 孩子的深度相同：
  - 此时若 ${\rm fa}_x = u$，则 $v$ 在 $x$ 所在子树内，该修改对询问贡献 $(n - {\rm siz}_x)\cdot d$.
  - 否则，$v$ 在 $u$ 父亲所在子树内，该修改对询问贡献 ${\rm siz}_u\cdot d$.

假如用倍增跳祖先的方法，时间复杂度是 $\mathcal O(\log n)$ 的，这样总的时间复杂度是 $\mathcal O\left(n\log n + qB\log n+n\dfrac qB \right)$ 的，在 $B = \sqrt{\dfrac n {\log n}}$ 时取到最小值 $\mathcal O(n\log n + n\sqrt{n\log n})$，没试过，但是感觉不是很跑的过去。~~虽然常数小就是了~~。

注意到跳 $k$ 级祖先可以使用长链剖分，对于每个点预处理出 $2^i$ 级祖先，对于每条长链，在链顶向上下预处理长链长度级祖先。对于一个询问，跳到令 $i$ 为 $k$ 二进制下的最高位，跳到 $2^i$ 级祖先所在的长链的链顶。显然这条长链长度不小于 $2^i$，更不小于剩下的 $k$（或者多跳的 $k$），直接查处理过的表即可。时间复杂度 $\mathcal O(n\log n)-\mathcal O(1)$.

这样时间复杂度就变成了 $\mathcal O\left(n\log n+qB+n\dfrac qB \right)$ 的，在 $B = \sqrt{n}$ 时取到最小值 $\mathcal O(n\log n +q\sqrt n)$，实测可过。

---

```cpp
ll QPow(ll a, ll b) {
	ll ret = 1, bas = a;
	for(; b; b >>= 1, bas = bas * bas % kMod) if(b & 1) ret = ret * bas % kMod;
	return ret;
}

int n, q;
std::vector <int> E[kN];
void Add(int u, int v) { E[u].push_back(v); E[v].push_back(u); }

int fa[kN][20], h_bit[kN], top[kN], d[kN], hvy[kN], dep[kN],
	dfn[kN], siz[kN], dfv = 0;
void Dfs(int u) {
	dfn[u] = ++dfv; siz[u] = 1;
	dep[u] = dep[fa[u][0]] + 1;
	for(auto v : E[u]) if(v != fa[u][0]) {
		fa[v][0] = u; Dfs(v);
		if(d[v] > d[hvy[u]]) hvy[u] = v;
		siz[u] += siz[v];
	}
	d[u] = d[hvy[u]] + 1;
}
void GetTop(int u, int t) {
	top[u] = t;
	if(hvy[u]) GetTop(hvy[u], t);
	for(auto v : E[u]) if(v != fa[u][0] && v != hvy[u]) {
		GetTop(v, v);
	}
}

std::vector <int> lower[kN], upper[kN];
void Init() {
	Dfs(1); GetTop(1, 1);
	for(int i = 1; i <= 18; ++i)
		for(int j = 1; j <= n; ++j)
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
	h_bit[0] = -1;
	for(int i = 1; i <= n; ++i)
		h_bit[i] = h_bit[i >> 1] + 1;
	for(int i = 1; i <= n; ++i) if(i == top[i]) {
		for(int x = i, y = i; top[x] == i; x = hvy[x], y = fa[y][0]) {
			lower[i].push_back(x);
			upper[i].push_back(y);
		}
	}
}
int FindAnc(int x, int k) {
	if(!k) return x;
	int t = top[fa[x][h_bit[k]]];
	k -= dep[x] - dep[t];
	int ret;
	if(k > 0) ret = upper[t][k];
	else ret = lower[t][-k];
	return ret;
}

struct Mod {
	int v; ll d;
} M[kN];
int cnt = 0;
ll t[kN], A[kN], dt[kN];
void Push() {
	cnt = 0;
	for(int u = 1; u <= n; ++u) if(t[u]) {
		ll d = t[u];
		for(auto v : E[u]) if(v != fa[u][0]) {
			dt[dfn[v]] = (dt[dfn[v]] + (n - siz[v]) * d) % kMod;
			dt[dfn[v] + siz[v]] = (dt[dfn[v] + siz[v]] - (n - siz[v]) * d) % kMod;
		}
		dt[1] = (dt[1] + siz[u] * d) % kMod;
		dt[dfn[u]] = (dt[dfn[u]] - siz[u] * d + n * d) % kMod;
		dt[dfn[u] + 1] = (dt[dfn[u] + 1] - n * d) % kMod;
		dt[dfn[u] + siz[u]] = (dt[dfn[u] + siz[u]] + siz[u] * d) % kMod;
	}
	for(int i = 1; i <= n; ++i)
		dt[i] = ((dt[i - 1] + dt[i]) % kMod + kMod) % kMod;
	for(int u = 1; u <= n; ++u)
		A[u] = (A[u] + dt[dfn[u]]) % kMod;
	memset(t, 0, sizeof(t));
	memset(dt, 0, sizeof(dt));
}
void Modify(int v, ll d) {
	t[v] = (t[v] + d) % kMod; 
	M[++cnt] = (Mod) { v, d };
}
ll Query(int v) {
	ll ret = A[v];
	for(int i = 1; i <= cnt; ++i) {
		int u = M[i].v; ll d = M[i].d;
		if(u == v) ret = (ret + n * d) % kMod;
		else if(dep[u] >= dep[v]) ret = (ret + siz[u] * d) % kMod;
		else {
			int x = FindAnc(v, dep[v] - dep[u] - 1);
			if(fa[x][0] != u) ret = (ret + siz[u] * d) % kMod;
			else ret = (ret + (n - siz[x]) * d) % kMod;
		}
	}
	return ret;
}

int main() { 
	ll n_inv; int B;
	rd(n, q); n_inv = QPow(n, kMod - 2);
	B = sqrt(n);
	for(int i = 1; i < n; ++i) {
		int u, v; rd(u, v);
		Add(u, v);
	}
	Init();
	for(int i = 1; i <= q; ++i)  {
		int opt, v; rd(opt, v);
		if(i / B != (i - 1) / B) Push();
		if(opt == 1) {
			ll d; rd(d);
			Modify(v, d * n_inv % kMod);
		} else printf("%lld\n", Query(v));
	}
	return 0;
}
```


---

## 作者：Saber_Master (赞：1)

[CF1254D Tree Queries](https://www.luogu.com.cn/problem/CF1254D)

先考虑指定点为根的情况.若指定点为根节点，且当前选定到的点在根节点的某个儿子$son$的子树里，那么当前节点会加上$\frac{n-siz[son]}{n}\cdot d$的权值.若当前选定到的点为根节点，那么直接加上$d$即可.

若当前点不是根节点，那对于各个儿子进行同样操作，对于不是自己子树内的点$x$，会加上$\frac{siz[x]}{n}\cdot d$的权值.

我们维护分子，最后再将结果乘上$n^{-1}$.由于每次扫描所有子树会被菊花图卡飞，所以我们考虑树剖优化.

维护差分序列，每次进行操作$1$时，我们只对重儿子进行树状数组区间修改，顺便维护一个变量$sum=\sum siz[v]\cdot d[v]$，在修改重儿子时将重复的部分消掉.对于操作$2$，注意到我们刚刚只修改了重儿子，所以当前点所在链的链顶的父节点在树状数组一定不会对当前查询点统计过贡献，所以将链顶贡献加进去即可.

$O(nlog^2n)$


核心代码

```cpp
const ll N=1.5e5+5;

ll head[N], to[N<<1], next[N<<1], tot;
inline void add(ll x, ll y){
	to[++tot]=y; next[tot]=head[x]; head[x]=tot;
} 
inline void Link(ll x, ll y){
	add(x, y); add(y, x);
}

inline ll quick_pow(ll x, ll y){
	ll res=1;
	for (; y; y>>=1){
		if (y&1) (res*=x)%=mod;
		(x*=x)%=mod;
	}
	return res;
}

inline ll inv(ll x){
	return quick_pow(x, mod-2);
}

ll n, Q, invn;

namespace bit{
	ll f[N];
	
	inline ll lowbit(ll x){
		return x&-x;
	}
	
	inline void modify(ll l, ll r, ll v){
		for (; l<=n; l+=lowbit(l)) (f[l]+=v)%=mod;
		for (++r; r<=n; r+=lowbit(r)) ((((f[r]-=v)%=mod)+=mod)%=mod);
	}
	
	inline ll ask(ll x){
		ll res=0;
		for (; x; x-=lowbit(x)) (res+=f[x])%=mod;
		return res;
	}
}

ll dfn[N], siz[N], son[N], cnt, f[N], top[N];

inline void dfs1(ll x, ll fa){
	siz[x]=1; f[x]=fa;
	for (R ll i=head[x], ver; i; i=next[i]){
		ver=to[i];
		if (ver==fa) continue;
		dfs1(ver, x);
		siz[x]+=siz[ver];
		if (siz[ver]>siz[son[x]]) son[x]=ver;
	}	
}

inline void dfs2(ll x, ll fir){
	dfn[x]=++cnt; top[x]=fir;
	if (!son[x]) return;
	dfs2(son[x], fir);
	for (R ll i=head[x], ver; i; i=next[i]){
		ver=to[i];
		if (dfn[ver]) continue;
		dfs2(ver, ver);
	}
}

ll sum, res;
ll v[N];

int main(){
	read(n); read(Q);
	for (R ll i=1, x, y; i<n; i++){
		read(x); read(y); Link(x, y);
	}
	invn=inv(n);
	dfs1(1, 0); dfs2(1, 1);
	ll op, x, d;
	while (Q--){
		read(op); read(x);
		if (op==1){
			read(d);
			(sum+=siz[x]*d)%=mod;
			(v[x]+=d)%=mod;
			if (son[x]){
				bit::modify(dfn[son[x]], dfn[son[x]]+siz[son[x]]-1, (((n-siz[son[x]])*d%mod-siz[x]*d%mod)%mod+mod)%mod);
			}
		}else {
			res=((sum-v[x]*siz[x]%mod)%mod+v[x]*n)%mod;
			(res+=bit::ask(dfn[x]))%=mod;
			while (1){
				x=top[x];
				if (x==1) break;
				(((res+=(n-siz[x]-siz[f[x]])*v[f[x]])%=mod)+=mod)%=mod;
				x=f[x];
			}
			writeln(res*invn%mod);
		}
	}
}

```


---

## 作者：Petit_Souris (赞：0)

**遇到操作和邻域相关的问题不一定要一上来就考虑对度数根号分治，或许可以试试重剖，重子树轻子树分开维护，可能会有更好的性质。**

操作可以认为是枚举根，产生贡献，最后答案除以 $n$。

对根 $r$ 和 $u$ 的位置分类讨论（以 $1$ 为根）。

- 当 $r$ 在 $u$ 子树外时，以 $r$ 为根的 $u$ 子树就是以 $1$ 为根的 $u$ 子树。

- 当 $r=u$ 时，以 $r$ 为根的 $u$ 子树就是整棵树。

- 当 $r$ 在 $u$ 的某个儿子 $v$ 的子树内时，以 $r$ 为根的 $u$ 子树就是以 $1$ 为根时 $v$ 的子树补。

因此我们可以发现一次操作，对 $u$ 子树外的部分贡献为 $\frac{sz_u}{n}$，对 $u$ 的贡献为 $1$，对于 $u$ 的某个 $v$ 的子树的贡献为 $\frac{n-sz_v}{n}$。

前两种贡献显然容易处理，dfs 序上区间加就能搞定了。但是第三种操作对于每个 $v$ 不一样，直接修改会涉及到 $deg_u$ 个值，复杂度不正确。

我们考虑重链剖分，当对 $u$ 执行操作时，我们只做重子树 $son_u$ 的操作，对于其他轻儿子的操作，先记在点 $u$ 上，等到查询的时候再处理。

重儿子可以直接一次 dfs 序区间加完成。查询时，我们每次向上跳一段重链，只会经过 $\mathcal O(\log n)$ 条轻边。对于每条轻边 $v\to u$（$v$ 是儿子），处理在 $u$ 处的标记。这个容易 $\mathcal O(1)$ 计算，因此总复杂度为 $\mathcal O(n\log n)$。

---

## 作者：Sorato_ (赞：0)

# CF1254D Tree Queries 题解

## 题目大意

给定一棵 $N$ 个节点的树，有 $Q$ 次操作，分别是如下两种：

- 给定一个点 $v$ 和一个权值 $d$，等概率地选择一个点 $r$，对每一个点 $u$，若 $v$ 在 $u$ 到 $r$ 的路径上，则$u$的权值加上$d$。
- 查询 $v$ 的权值期望，对 $998244353$ 取模。

## Solve

考虑对节点 $u$ 执行操作 1 之后，对树上所有节点的贡献。

- 对于 $u$ 自己，期望权值需要加上 $d$。
- 对于 $u$ 子树里（除去 $u$ 自己）的点，若这个点在以 $v$ 为根的子树里（$v\in son(u)$），那么只有选到的 $r$ 不在 $v$ 的子树里才对这个点有贡献，所以这个点的期望权值需要加上 $d\cdot siz(v)\over N$。
- 对于不在 $u$ 子树里的点，需要选到的 $r$ 在 $u$ 子树里，才能对这个点有贡献，期望权值需要加上 $d\cdot siz(u)\over N$。

对树建立 dfs 序，那么就可以转化为区间加，用树状数组维护。

但问题是，对 $u$ 子树里的点的贡献和那个点所在的子树有关，如果每次都遍历 $u$ 的所有儿子，可以被菊花卡到 $O(NQ\log_2N)$。所以考虑一个根号分治 / 根号重建。

将操作分为若干个大小为 $B$ 的块。记录每个块内的修改操作，把对同一个节点的修改合并。

每 $B$ 次修改，遍历这个块内的所有修改并按上面的方式执行。由于每个点的所有边至多被遍历一次，复杂度 $O(\frac Q B\cdot N\log_2N)$。

对于一次询问，它所在块前面的贡献都已经通过数据结构统计出来了，只需要遍历这个块里的所有修改就行。

比如当前询问的点是 $u$，遍历到的修改是 $(v,d)$。还是按上面所说的分类讨论计算贡献。那么我们需要快速求出 $u$ 是否在 $v$ 的子树里，若在，是在 $v$ 的哪个儿子的子树里。可以分情况讨论。

- 若 $u=v$，特判。
- 否则若 $u$ 的深度 $dep(u)\geq dep(v)$，说明 $u$ 肯定不在 $v$ 的子树里。
- 若 $dep(u)<dep(v)$，我们对 $u$ 求 $dep(v)-dep(u)-1$ 级祖先，记为 $fa$。如果 $fa$ 的父亲不是 $v$，说明 $u$ 不在 $v$ 的子树里。否则，$u$ 在 $v$ 的子树里，并且我们也已求得了它是在 $v$ 的哪个儿子的子树里。

这样，就可以计算贡献了。时间复杂度为 $O(QBK)$，其中 $K$ 为求 $k$ 级祖先的复杂度消耗。

对于求 $k$ 级祖先，方法很多。由于我们对于不同块的操作已经带了一个 $\log$，如果我们在这里还使用带 $\log$ 的算法求，如树剖和倍增，那么总复杂度是在 $B=\sqrt N$ 时取得最小值，为 $O(Q\sqrt N \log_2N)$，较慢。实测倍增写法跑了 4000ms+。

用长链剖分求 $k$ 级祖先，可以做到 $K=1$。这样总复杂度在 $B=\sqrt{N\log_2N}$ 时取得最小值 $O(Q\sqrt{N\log_2N})$，实测跑了 2000ms+。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=1.5e5+10,B=1600,MOD=998244353;
inline int qpow(ll x,int y)
{
	ll res=1;
	while(y)
	{
		if(y&1)	res=res*x%MOD;
		x=x*x%MOD;y>>=1;
	}
	return res;
}
int n,q,dfn[N],tim,inv,siz[N];
ll d[N];
int dep[N],fa[N][18],logn[N]={-1};
bool in[N];
vector<int>e[N],v;
int son[N],mx[N],l[N],r[N],top[N];
void get_son(int u)//预处理重儿子，倍增预处理 2^k 级祖先
{
	mx[u]=dep[u]=-~dep[fa[u][0]];
	for(int i=1;i<=logn[dep[u]];i=-~i)
		fa[u][i]=fa[fa[u][~-i]][~-i];
	for(int i:e[u])
		if(i!=fa[u][0])
			fa[i][0]=u,get_son(i),siz[u]+=siz[i];
	if(mx[u]>mx[son[fa[u][0]]])
		son[fa[u][0]]=u,mx[fa[u][0]]=mx[u];
}
void get_chain(int u,int L)//重儿子优先遍历
{
	r[dfn[u]=tim=-~tim]=u;
	l[tim]=L;
	top[u]=fa[u][0]&&u==son[fa[u][0]]?top[fa[u][0]]:u;
	if(son[u])	get_chain(son[u],fa[L][0]);
	for(int i:e[u])
		if(i!=son[u]&&i!=fa[u][0])	get_chain(i,i);
}
inline int ask(int u,int k)//长剖求 k 级祖先
{
	if(!k)	return u;
	u=fa[u][logn[k]];k-=(1<<logn[k]);
	k-=dep[u]-dep[top[u]];u=top[u];
	return k>0?l[dfn[u]+k]:r[dfn[u]-k];
}
ll c[N];//对 dfs 序建立树状数组维护区间加单点查
inline void add(int x,int y){for(;x<=n;x+=x&-x)(c[x]+=y+MOD)%=MOD;}
inline int ask(int x){int s=0;for(;x;x-=x&-x)(s+=c[x])%=MOD;return s;}
int op,u;
signed main()
{
	n=read();q=read();inv=qpow(n,MOD-2);
	for(int i=1,u,v;i<n;i=-~i)
		u=read(),v=read(),
		e[u].push_back(v),e[v].push_back(u);
	for(int i=1;i<=n;i=-~i)
		logn[i]=-~logn[i>>1],siz[i]=1;
	get_son(1);get_chain(1,1);
	while(q--)
	{
		op=read();u=read();
		if(op==1)
		{
			if(!in[u])	v.push_back(u),in[u]=1;
			(d[u]+=read())%=MOD;//将对于同一个点的修改合并
		}
		else
		{
			ll sum=ask(dfn[u]);//前面的块的贡献
			for(int i:v)//当前块的贡献
			{
				if(u==i)	sum+=d[i]*n%MOD;
				else if(dep[u]<=dep[i])	sum+=d[i]*siz[i];//i 子树外
				else
				{
					int x=ask(u,dep[u]-dep[i]-1);
					if(fa[x][0]==i)
						sum+=d[i]*(n-siz[x])%MOD;//i 子树内
					else	sum+=d[i]*siz[i]%MOD;//i 子树外
				}
				sum%=MOD;
			}
			printf("%lld\n",sum*inv%MOD);
		}
		if(v.size()==B)//根号重建
		{
			for(int i:v)
			{
				for(int j:e[i])
					if(j!=fa[i][0])
						add(dfn[j],d[i]*(n-siz[j])%MOD),
						add(dfn[j]+siz[j],-d[i]*(n-siz[j])%MOD);
				add(dfn[i],d[i]*n%MOD);add(-~dfn[i],-d[i]*n%MOD);
				add(1,d[i]*siz[i]%MOD);add(dfn[i],-d[i]*siz[i]%MOD);
				add(dfn[i]+siz[i],d[i]*siz[i]%MOD);
				d[i]=in[i]=0;
			}
			v.clear();
		}
	}
	return 0;
}
```

---

## 作者：Hanx16Kira (赞：0)

# Tree Queries

[Luogu CF1254D](https://www.luogu.com.cn/problem/CF1254D)

## Solution

操作很怪异，所以考虑一下每次操作会对所有点产生什么影响。先选中一个点 $v$ 作为操作点，然后枚举点 $r$。容易发现最后产生的影响只与 $v$ 作为树根时 $r$ 在 $v$ 的哪一个子树有关，那么这一次操作如果选择 $r$ 将会对 $v$ 除 $r$ 所在的子树外的所有子树产生 $\dfrac d n$ 的贡献，也就是说这一颗子树内所有可能的 $r$ 点将会对其余所有的子树产生 $\dfrac {ds}{n}$ 的贡献（其中 $s$ 为当前子树的大小）。

那么可以有两种不同思路的暴力，一种修改慢查询快，一种修改快查询慢：

- 考虑对每一个节点 $x$ 维护一个值 $val_x$ 表示当前节点的答案。那么每次修改就是暴力枚举修改节点的每一个子树，然后暴力的加到所有节点的 $v_x$ 上。
- 每次修改的时候暴力枚举所有修改过的点，然后根据修改的这个点在询问点的哪一个子树来计算答案。

注意到我们每一次的修改都与当前节点有的子树个数相关，因此对度数根号分治，设一个阈值 $S$，所有度数大于 $S$ 的节点称为关键点。显然关键点的数量是 $\mathcal O(\dfrac n S)$ 的。

对于修改操作，如果当前点是关键点，那么就只把当前点标记上；否则直接暴力枚举所有子树然后处理贡献。注意到处理贡献的时候可以看作是子树加，所以使用树状数组来维护。复杂度是 $\mathcal O(S\log n)$。

对于询问操作，先在树状数组中取出非关键点的贡献，然后再暴力枚举所有关键点并计算其贡献。时间复杂度不精细实现是 $\mathcal O(\dfrac n S\log n)$。

$S$ 取 $\sqrt n$ 时最优，总时间复杂度 $\mathcal O(q\sqrt n\log n)$，跑得挺慢，不过能过。

```cpp
int N, Q, S;
vector<int> e[_N];
bool crit[_N];
int deg[_N];
vector<int> crl;
int fa[20][_N], dep[_N], siz[_N], dfn[_N], tot;
void dfs(int x, int F) {
    fa[0][x] = F, siz[x] = 1, dfn[x] = ++tot, dep[x] = dep[F] + 1;
    For(i, 1, 18) fa[i][x] = fa[i-1][fa[i-1][x]];
    for (int v: e[x]) if (v ^ F) dfs(v, x), siz[x] += siz[v];
}
int jump(int x, int y) {
    for (int tmp = dep[x] - dep[y] - 1, i = 0; tmp; tmp >>= 1, ++i)
        if (tmp & 1) x = fa[i][x];
    return x;
}
struct Bit {
    mint val[_N];
    inline int lowbit(int x) {return x & -x;}
    void update(int x, mint v) {for (; x <= N; x += lowbit(x)) val[x] += v;}
    inline void update(int l, int r, mint v) {update(l, v), update(r + 1, -v);}
    mint ask(int x) {mint res = 0; for (; x; x -= lowbit(x)) res += val[x]; return res;}
} bit;
inline bool chk(int x, int y) {return dfn[x] >= dfn[y] && dfn[x] < dfn[y] + siz[y];}
mint inv, val[_N];
void _() {
    cin >> N >> Q;
    inv = mint(1) / N;
    For(i, 2, N) {
        int x, y; cin >> x >> y;
        e[x].epb(y), e[y].epb(x);
        ++deg[x], ++deg[y];
    }
    S = sqrt(N);
    For(i, 1, N) if (deg[i] >= S)
        crl.epb(i), crit[i] = 1;
    Debug("crit:", crl);
    dfs(1, 0);
    while (Q--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {
            mint d; cin >> d;
            if (crit[x]) val[x] += d;
            else {
                for (int v: e[x]) {
                    if (fa[0][x] == v) {
                        mint res = (N - siz[x]) * d * inv;
                        bit.update(dfn[x], dfn[x] + siz[x] - 1, res);
                    } else {
                        mint res = siz[v] * d * inv;
                        bit.update(1, N, res);
                        bit.update(dfn[v], dfn[v] + siz[v] - 1, -res);
                    }
                }
                bit.update(1, N, d * inv);
            }
        } else {
            mint base = bit.ask(dfn[x]);
            for (int c: crl) {
                if (x == c) base += val[c];
                else if (chk(x, c)) {
                    int u = jump(x, c);
                    base += val[c] * (N - siz[u]) * inv;
                } else base += val[c] * siz[c] * inv;
            }
            fmtout("{}\n", base);
        }
    }
}
```

---

## 作者：forest114514 (赞：0)

### CF1254D Tree Queries

简单期望，对于选在 $v$ 子树外的 $r$，所有的 $u\in subtree_v$ 的点均会 $+d$ ，对于选到 $v$ 子树内的 $r$，所有的 $v$ 子树外的点和 $v$ 子树内不在 $r$ 所在的 $v$ 子树的 $u$ 也会 $+d$，选到 $v$ 就所有点都 $+d$。

我们发现以 $u$ 为根来看，就是当且仅当 $r$ 所在的 $v$ 子树权值不会 $+d$（$r$ 在 $v$ 就只有 $v$ 会 $+d$）。因为每次的分母 $n$ 可以查询时乘以逆元就行了，所以我们只考虑 $n$ 个选择它们的总贡献。但如果一个个子树去改，会被菊花图卡死！~~（你猜这题为什么 2700）~~

对于子树外的点，线段树用两个区间加加上 $siz_v\times d$ 就能解决~~（但我选择树状数组）~~，对于 $v$ 子树内，我们想到了树剖，因为这样我们就有了一种方法，类似于线段树标记永久化：我们直接修改重儿子所在子树，并在在 $v$ 处打上一个永久标记 $d$，这样 $O(\log N)$ 完成了修改。

每次查询一个点的权值期望，我们先加上自己所在位置的标记 $d_u\times n$ 就沿着重链往上跳，每次加上所在链头 $top$ 的父亲的标记 $d_{fa_{top}}\times (n-siz_{top})$，借用树剖的性质可以证明，我们跳的链的条数是 $\log N$ 级别的，所以一次查询的时间复杂度为 $O(\log N)$

综上，我们就在 $O((N+Q)\log N)$ 解决了本题。（为什么官方题解是 $O(N\sqrt{N\log N})$ 的啊？）

~~（我的代码不知为何会爆long long，所以开了 int128）~~

CODE：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef __int128 LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=2e5+100;
const LL mod=998244353;
LL ksm(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
int q;
int Ti,top[N],siz[N],son[N],fa[N],dep[N],dfn[N],pos[N],low[N];
vector<int>E[N];
LL n,tag[N],inv;
void add(LL &v,LL u){
	v=(v+u>=mod)?(v+u-mod):(u+v);
}
void dfs1(int x){
	son[x]=-1,siz[x]=1;
	for(auto y:E[x]){
		if(dep[y]) continue;
		dep[y]=dep[x]+1,fa[y]=x;
		dfs1(y);
		siz[x]+=siz[y];
		if(son[x]==-1||siz[y]>siz[son[x]]) son[x]=y;
	}
}
void dfs2(int x,int tp){
	top[x]=tp,dfn[x]=++Ti,pos[Ti]=x;
	if(son[x]==-1) return ;
	dfs2(son[x],tp);
	for(auto y:E[x]){
		if(y==son[x]||y==fa[x]) continue;
		dfs2(y,y);
	}
}

struct BIT{
	LL f[N];
	BIT(){memset(f,0,sizeof f);}
	#define lowbit(x) (x&(-x))
	void update(int u,LL x){while(u<=n)add(f[u],x),u+=lowbit(u);}
	LL query(int u){LL res=0;while(u) add(res,f[u]),u-=lowbit(u);return res;}
	void upd(int l,int r,LL u){update(l,u),update(r+1,-u);}
}BIT;
void modify(int u,LL d){
	int ql=dfn[u]-1,qr=dfn[u]+siz[u];
	LL ad=1ll*siz[u]*d%mod;
	if(ql>=1) BIT.upd(1,ql,ad);
	if(qr<=n) BIT.upd(qr,n,ad);
	add(tag[u],d);
	if(son[u]!=-1)BIT.upd(dfn[son[u]],dfn[son[u]]+siz[son[u]]-1,1ll*(n-siz[son[u]])*d%mod);
}
void query(int u){
	LL res=BIT.query(dfn[u])+tag[u]*n%mod;
	int p=u;
	while(p){
		p=top[p];
		add(res,1ll*(n-siz[p])*tag[fa[p]]%mod);
		p=fa[p];
	}
	write((res*inv%mod+mod)%mod,'\n');
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,q);
	inv=ksm(n,mod-2);
	int u,v;
	repp(i,1,n){
		read(u,v);
		E[u].pb(v),E[v].pb(u);
	}
	dep[1]=1;
	dfs1(1),dfs2(1,1);
	int opt;LL d;
	tag[0]=0,fa[1]=0;
	while(q--){
		read(opt,u);
		if(opt==1){
			read(d);
			modify(u,d);
		} else query(u);
	}
	return 0;
}
```







---

