# [ABC291Ex] Balanced Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc291/tasks/abc291_h

$ N $ 頂点の木 $ T $ が与えられます。$ i $ 番目の辺は頂点 $ A_i $ と $ B_i $ を結んでいます。

次の条件をともに満たす $ N $ 頂点の根付き木 $ R $ を $ 1 $ つ求めてください。

- $ 1\ \leq\ x\ <\ y\ \leq\ N $ を満たす全ての整数の組 $ (x,y) $ に対し次が成り立つ
  - $ R $ における頂点 $ x,y $ の最小共通祖先が頂点 $ z $ であるとき、$ T $ において 頂点 $ x,y $ を結ぶ単純パス上に頂点 $ z $ が存在する
- $ R $ において、根以外の全ての頂点 $ v $ に対し、$ v $ を根とする部分木の頂点数の $ 2 $ 倍は、 $ v $ の親を根とする部分木の頂点数以下である
 
なお、この条件を満たす根付き木は必ず存在することが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ N $
- 入力は全て整数である
- 与えられるグラフは木である
 
### Sample Explanation 1

例えば、$ R $ における頂点 $ 1,3 $ の最小共通祖先は頂点 $ 2 $ であり、$ T $ において、頂点 $ 1,3 $ を結ぶ単純パス上に頂点 $ 2 $ が存在します。 また、例えば、$ R $ における頂点 $ 4 $ を根とする部分木の頂点数は $ 2 $ であり、その $ 2 $ 倍は、頂点 $ 2 $ を根とする部分木の頂点数 $ 4 $ 以下です。 !\[図\](https://img.atcoder.jp/abc291/7c68a1da41dbfff60a08aad4fe182376.png)

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
2 -1 4 2```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5```

### 输出

```
-1 1 1 1 1```

# 题解

## 作者：Super_Cube (赞：3)

# Solution

奇异幽默搞笑题，看得我乐开花了。

看完题目中给的两个限制条件，我寻思着第二个限制就是点分树的长相啊，然后第一个限制就是点分树的性质啊，所以要构造的 $R$ 不就是 $T$ 的点分树吗。

然后把 [P6329 【模板】点分树](https://www.luogu.com.cn/problem/P6329) 的建树部分代码复制过来稍微改改输入格式就过了。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<int>v[100005];
bool vis[100005];
int siz[100005];
int rt,all;
void dfs(int p,int dad){
	siz[p]=1;
	int w=0;
	for(const int&i:v[p])
		if(!vis[i]&&i!=dad)
			dfs(i,p),siz[p]+=siz[i],w=std::max(w,siz[i]);
	w=std::max(w,all-siz[p]);
	if((w<<1)<=all)rt=p;
}
int up[100005];
void build(int p){
	vis[p]=true;
	dfs(p,0);
	for(const int&i:v[p])
		if(!vis[i])
    		all=siz[i],dfs(i,p),
    		up[rt]=p,build(rt);
}
int n;
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;++i)
		scanf("%d%d",&x,&y),
		v[x].push_back(y),v[y].push_back(x);
	all=n;dfs(1,0);
	up[rt]=-1;build(rt);
	for(int i=1;i<=n;++i)
		printf("%d ",up[i]);
	return 0;
}
```

---

## 作者：JWRuixi (赞：1)

~~这也绝对比 G 简单~~

- 题意

给定一棵 $n$ 个点树 $T$，构造一棵有根树 $R$，是的对于任意 $1\le x<y\le n$，$R$ 上的 $\text{lca}(x,y)$ 属于 $T$ 上的 $\text{Path}(x,y)$。

且对于任意节点 $u$，$u$ 是 $R$ 上以 $u$ 为根的子树的重心。

- 分析

首先分析性质，对于节点 $u$，令 $T$ 以 $u$ 为根，其每一棵子树内的点不能在 $R$ 上被分到不同的子树。考虑最有策略就是把所有子树各自分一块。

又由于要求每个点均为子树的重心，那这就显然直接上点分树，就做完了！

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);
    }
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500);
int n, sz[maxn], mxs[maxn], rt, f[maxn], m;
vector<int> G[maxn];
bool vis[maxn];

inline void dfs (int u, int fa) {
	sz[u] = 1, mxs[u] = 0;
	for (int v : G[u]) {
		if (vis[v] || v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
		mxs[u] = max(mxs[u], sz[v]);
	}
	mxs[u] = max(mxs[u], m - sz[u]);
	if (mxs[u] < mxs[rt]) rt = u;
}

inline void slv (int u) {
	vis[u] = 1;
	dfs(u, 0);
	for (int v : G[u]) {
		if (vis[v]) continue;
		rt = 0, m = sz[v], dfs(v, u);
		f[rt] = u;
		slv(rt);
	}
}

int main() {
	n = read();
	for (int i = 1, u, v; i < n; i++) {
		u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	mxs[0] = n + 1;
	rt = 0, m = n, dfs(1, 0);
	f[rt] = -1;
	slv(rt);
	for (int i = 1; i <= n; i++) writesp(f[i]);
}
// I love WHQ!
```

---

## 作者：sunkuangzheng (赞：1)

我们先忽略第一条限制，只考虑第二条限制。

> $\forall u \in [1,n],2siz_u \le siz_{fa_u}$。

很自然想到树的重心，我们知道一棵树重心为根时，最大的子树的 $siz_v \le \dfrac{1}{2}siz_u$。类似点分治的，找到重心后断开，会分出若干子树，找子树重心是子问题，可以递归处理。

我们可以通过上面的方式，把重心之间连边，得到一棵新树。如果你这么写并直接提交，会发现已经 AC 了。现在我们来证明它满足第一条限制。

> $\forall x,y \in [1,n]$，$x,y$ 在新树上的 LCA 在原树 $x,y$ 的路径上。

证明其实比较简单：$x,y$ 在新树上的 LCA 一定是它们第一次被分开的那个重心，那么 $x,y$ 在原树上的路径就一定经过这个重心，否则就不会被分开了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int n,vis[N],u,v,siz[N],mx[N],rt,fa[N]; vector<int> g[N];
void dfs1(int u,int f){
	siz[u] = 1,mx[u] = 0;
	for(int v : g[u]) if(!vis[v] && v != f) dfs1(v,u),siz[u] += siz[v],mx[u] = max(mx[u],siz[v]);
}void getrt(int u,int f,int tot){
	mx[u] = max(mx[u],tot - siz[u]);
	if(mx[u] < mx[rt]) rt = u;
	for(int v : g[u]) if(!vis[v] && v != f) getrt(v,u,tot);
}void dfs2(int u){
	vis[u] = 1;
	for(int v : g[u]) if(!vis[v]) rt = 0,dfs1(v,0),getrt(v,0,siz[v]),fa[rt] = u,dfs2(rt);
}int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> n; mx[0] = 1e9;
	for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
	dfs1(1,0),getrt(1,0,n),fa[rt] = -1,dfs2(rt);
	for(int i = 1;i <= n;i ++) cout << fa[i] << " ";
}
```

PS：我 AC 以后看别的题解，才知道我口胡的这东西就是点分树（

---

## 作者：cancan123456 (赞：0)

看到重构一棵树，看到 LCA 在路径上，想到点分树（不要问我怎么想，问就是做过类似题）。

考虑如何证明要求：

1. $x,y$ 的 LCA $z$ 在点分树的 $x$ 到 $y$ 的路径上：考虑某层的连通块，设重心为 $u$，那么该连通块被分成了若干子树。如果 $x$ 到 $y$ 的路径上包含了 $u$，那么显然其一定被分在的不同的子树中，则其路径一定包含 $u$，否则，它们一定在同一子树中，其路径一定不包含 $u$，证毕。
2. 子树大小 $\times2$ 小于等于父节点：发现父节点一定是某个连通块的重心，联想重心的性质即可证明。

> 重心的性质：以树的重心为根时，所有子树的大小都 $\times2$ 小于等于整棵树的大小。  
> 证明考虑反证法，考虑重心的定义：所有子树中最大的子树节点数，这个值最小的点就是这棵树的重心，如果其有一个子树大小大于整棵树大小 $n$ 除以 $2$，那么重心应当是该子树的根，这是显然的。

---

