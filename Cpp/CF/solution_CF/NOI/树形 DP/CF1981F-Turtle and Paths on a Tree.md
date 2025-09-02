# Turtle and Paths on a Tree

## 题目描述

在这个问题中，注意 $\text{MEX}$ 的不寻常定义。

Piggy 给了 Turtle 一棵二叉树，有 $n$ 个顶点和一个序列 $a_1, a_2, \ldots, a_n$ 。这棵二叉树以顶点 $1$ 为根。

如果一组路径 $P={(x_i, y_i)}$ 在树中正好覆盖每条边一次，那么 Turtle 就认为这组路径是好的。注意，好的路径集可以多次覆盖一个顶点。

Turtle 将一组路径的值定义为 $\sum\limits_{(x,y)\in P} f(x,y)$，其中 $f(x,y)$ 表示从路径 $x$ 到 $y$ 的简单路径上所有顶点的 $\text{MEX}$ 值（包括起始顶点 $x$ 和结束顶点 $y$）。

Turtle 想知道所有好的路径集中的最小值。请帮助他计算答案！

## 样例 #1

### 输入

```
5
5
3 2 2 1 1
1 1 2 2
5
3 2 1 1 1
1 1 2 2
6
1 2 1 2 1 3
1 2 3 3 4
7
2 1 2 3 1 2 1
1 1 2 2 3 3
10
1 2 2 1 4 2 3 1 2 1
1 1 2 2 3 3 4 5 5```

### 输出

```
4
6
6
6
7```

# 题解

## 作者：EuphoricStar (赞：11)

考虑 dp。设 $f_{u, i}$ 为 $u$ 子树内延伸上去的路径，钦定这条路径不包含 $i$ 这个值，$u$ 子树内除了这条路径的路径 MEX 和的最小值。$i$ 的取值在 $[1, n + 1]$。这样我们可以直接将这条路径的 MEX 当作 $i$，因为若 MEX 不是 $i$ 那么 MEX 会更小，这个 dp 状态就不优。

考虑 dp 的所有转移（转移解释部分来自 [AFewSuns](https://www.luogu.com.cn/user/224336)）：

1. $u$ 是叶子，则有：

$$
f_{u,i}=\begin{cases}
0, & i \neq a_u \\
+\infty, & i=a_u
\end{cases}
$$

2. $u$ 只有一个儿子，不妨设儿子为 $x$。令 $\text{minx}=\min\limits_{i\neq a_u}{f_{x,i}+i}$，则有：

$$
f_{u,i}=\begin{cases}
\min(f_{x,i},\text{minx}), & i \neq a_u \\
+\infty, & i=a_u
\end{cases}
$$

3. $u$ 有两个儿子，不妨设两个儿子为 $x,y$。令 $\text{minx}=\min\limits_{i\neq a_u}{f_{x,i}+i},\text{miny}=\min\limits_{i\neq a_u}{f_{y,i}+i}$，则有四种转移方式：

- 延续 $x$ 子树中的路径，即 $\forall i\neq a_u,f_{u,i}=\min(f_{u,i},f_{x,i}+\text{miny})$
- 延续 $y$ 子树中的路径，即 $\forall i\neq a_u,f_{u,i}=\min(f_{u,i},f_{y,i}+\text{minx})$
- 新建一个路径，并将两个子树中的路径拼接起来，即 $\forall i\neq a_u,f_{u,i}=\min(f_{u,i},\min\limits_{j \neq a_u}{(f_{x,j}+f_{y,j}+j)})$
- 新建一个路径，并且不拼接两个子树中的路径，即 $\forall i\neq a_u,f_{u,i}=\min(f_{u,i},\text{minx} + \text{miny})$

令 $k=\min(\min\limits_{i \neq a_u}{(f_{x,i}+f_{y,i}+i),\text{minx} + \text{miny}})$，则可以将转移写成如下形式：
$$
f_{u,i}=\begin{cases}
\min(f_{x,i}+\text{miny},f_{y,i}+\text{minx},k), & i \neq a_u \\
+\infty, & i=a_u
\end{cases}
$$

这样时间复杂度是 $O(n^2)$ 的。

事实上可以证明我们只需要考虑不超过 $O(\frac{n}{\ln n})$ 的 MEX（在 $n = 25000$ 时只需要考虑不超过 $3863$ 的 MEX），因此 dp 第二维只用枚举到 $O(\frac{n}{\ln n})$（或 $3863$）。

并且我们有一个能达到 $O(\frac{n}{\ln n})$ 的 MEX 的一条链的构造，就是从 $1$ 开始枚举 $i$，把 $i$ 的因数倒序列举出来，比如 $[1, 2, 1, 3, 1, 4, 2, 1, 5, 1]$。

时间复杂度：每个测试用例 $O(\frac{n^2}{\ln n})$。

关于 MEX 上界的证明：

只考虑链的情况。对于一个固定的 $x$，形如 $[a, \ldots, b, x, c, \ldots, d, x, e, \ldots, f, x, g, \ldots, h]$ 的序列，可以把它分成这样的段：

$$
[a, \ldots, b], [b, x, c], [c, \ldots, d], [d, x, e], [e, \ldots, f], [f, x, g], [g, \ldots, h]
$$
其中不含 $x$ 的段的 $\text{MEX} \le x$，含 $x$ 的段的 $\text{MEX} \le 4$。

设答案为 $t$，那么 $t$ 满足：（其中 $c_i$ 为 $i$ 的出现次数）

$$
\min\limits_{i \ge 1} (c_i + 1) i + 4 c_i \ge t
$$
放缩，得：
$$
\min\limits_{i \ge 1} (c_i + 1) (i + 4) \ge t
$$


进一步地，形如 $[b, x, c]$ 的段，若 $x \ge 4$，那么上面的 $4c_i$ 可以变成 $3c_i$（因为 $x$ 不可能为 $1, 2, 3$），所以得：

$$
\min(\min\limits_{i = 1}^3 (c_i + 1)(i + 4), \min\limits_{i \ge 4}(c_i + 1)(i + 3)) \ge t
$$
那么：

$$
c_i \ge \begin{cases} \left\lceil\frac{t}{i + 4}\right\rceil - 1 & 1 \le i \le 3 \\ \left\lceil\frac{t}{i + 3}\right\rceil - 1 & i \ge 4 \end{cases}
$$
也就是说我们需要 $O(\frac{t}{i})$ 个 $i$，那么 $n = O(t \ln t)$，所以 $t = O(\frac{n}{\ln n})$。

我们还有：

$$
n = \sum\limits_{i \ge 1} c_i \ge \sum\limits_{i = 1}^3 (\left\lceil\frac{t}{i + 4}\right\rceil - 1) + \sum\limits_{i \ge 4} (\left\lceil\frac{t}{i + 3}\right\rceil - 1)
$$
$n$ 固定时可以二分出最大的满足上面条件的 $t$，得到 $n = 25000$ 时 $t = 3863$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))
 
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;
 
const int maxn = 25050;
const int inf = 0x3f3f3f3f;
 
int n, m, a[maxn], f[maxn][4000];
vector<int> G[maxn];
 
void dfs(int u) {
	if (G[u].empty()) {
		for (int i = 1; i <= m; ++i) {
			f[u][i] = (i == a[u] ? inf : 0);
		}
		return;
	}
	if ((int)G[u].size() == 1) {
		int x = G[u][0];
		dfs(x);
		int mn = inf;
		for (int i = 1; i <= m; ++i) {
			if (i != a[u]) {
				mn = min(mn, f[x][i] + i);
			}
		}
		if (u == 1) {
			printf("%d\n", mn);
			return;
		}
		for (int i = 1; i <= m; ++i) {
			f[u][i] = (i == a[u] ? inf : min(f[x][i], mn));
		}
		return;
	}
	int x = G[u][0], y = G[u][1], mnx = inf, mny = inf, k = inf;
	dfs(x);
	dfs(y);
	for (int i = 1; i <= m; ++i) {
		if (i != a[u]) {
			mnx = min(mnx, f[x][i] + i);
			mny = min(mny, f[y][i] + i);
			k = min(k, f[x][i] + f[y][i] + i);
		}
	}
	k = min(k, mnx + mny);
	if (u == 1) {
		printf("%d\n", k);
		return;
	}
	for (int i = 1; i <= m; ++i) {
		f[u][i] = (i == a[u] ? inf : min({f[x][i] + mny, f[y][i] + mnx, k}));
	}
}
 
void solve() {
	scanf("%d", &n);
	m = min(n + 1, 3863);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		vector<int>().swap(G[i]);
	}
	for (int i = 2, p; i <= n; ++i) {
		scanf("%d", &p);
		G[p].pb(i);
	}
	dfs(1);
}
 
int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：AFewSuns (赞：10)

为了避免与 [zltqwq 的题解](https://www.luogu.com.cn/article/jjjbo756) 高度重合，这里仅作补充，基本的 dp 转移式请参照 [zltqwq 的题解](https://www.luogu.com.cn/article/jjjbo756)。

考虑使用线段树合并维护 dp 值。$u$ 有不超过 $1$ 个儿子的转移是很好维护的，只需要考虑有两个儿子的情况。

回顾一下有两个儿子的转移。不妨设 $u$ 的两个儿子为 $x,y$。令 $minx=\min\limits_{i\neq a_u}{(f_{x,i}+i)},miny=\min\limits_{i\neq a_u}{(f_{y,i}+i)}$，$k=\min(\min\limits_{i \neq a_u}{(f_{x,i}+f_{y,i}+i),minx+miny})$，则有如下转移：
$$
f_{u,i}=\begin{cases}
\min(f_{x,i}+miny,f_{y,i}+minx,k), & i \neq a_u \\
+\infty, & i=a_u
\end{cases}
$$

首先用线段树维护 $f_{u,i}+i$ 的最小值，那么 $minx$ 和 $miny$ 都可以求出来。$f_{u,a_u}$ 的值可以通过单点修改设成 $+\infty$。

先不考虑如何求解 $k$，那么在最后只需要将所有 $f_{x,i}$ 加上 $miny$，$f_{y,i}$ 加上 $minx$，使用线段树合并，然后将所有 $f_{u,i}$ 与 $k$ 取 $\min$ 即可。

而求解 $k$ 即求解 $\min\limits_{i \neq a_u}{(f_{x,i}+f_{y,i}+i)}$，也可以使用类似线段树合并的方法，在一棵线段树递归到叶子节点的时候快速计算即可，需要额外维护 $f_{u,i}$ 的最小值。总时间复杂度 $\mathcal O(n\log n)$。

虽然区间加和区间取 $\min$ 操作需要 pushdown（当然有办法变成标记永久化），不过我们只需要在线段树合并的时候给只有一个儿子的点补成两个儿子，即所有点要么是叶子，要么有两个儿子，就可以保证时间复杂度和正确性。

区间取 $\min$ 操作实际上不需要吉司机线段树，因为只需要维护 $f_{u,i}$ 和 $f_{u,i}+i$ 的最小值。

---

题外话：

其实一开始我只得到了一个 set + 启发式合并的 $\mathcal O(n\log^2n)$ 做法，其关键在于观察到对于所有不在 $u$ 子树中的 $i$，$f_{u,i}$ 的值是容易维护的。

后来在 [\_LHF\_](https://www.luogu.com.cn/user/99506) 的帮助下，意识到无脑线段树合并即可，这里向他表示感谢。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using namespace my_std;
#define LC tree[x].lc
#define RC tree[x].rc
ll t,n,a[25025],ch[25025][2],ans=inf;
ll rt[25025],tot=0;
struct node{
	ll minn1,minn2,lz,lzmin,lc,rc;
	il void addtag(ll v,ll vmin,ll l){
		minn1=min(minn1+v,vmin);
		minn2=min(minn2+v,vmin+l);
		lz+=v;
		lzmin=min(lzmin+v,vmin);
	}
}tree[1000010];
il void pushup(ll x){
	tree[x].minn1=min(tree[LC].minn1,tree[RC].minn1);
	tree[x].minn2=min(tree[LC].minn2,tree[RC].minn2);
}
il ll newnode(){
	tree[++tot]=(node){(ll)inf,(ll)inf,0,(ll)inf,0,0};
	return tot;
}
il void pushdown(ll x,ll l,ll r){
	if(!LC) LC=newnode();
	if(!RC) RC=newnode();
	ll mid=(l+r)>>1;
	tree[LC].addtag(tree[x].lz,tree[x].lzmin,l);
	tree[RC].addtag(tree[x].lz,tree[x].lzmin,mid+1);
	tree[x].lz=0;
	tree[x].lzmin=inf;
}
void upd(ll &x,ll l,ll r,ll pos){
	if(!x) x=newnode();
	if(l==r){
		tree[x].minn1=tree[x].minn2=inf;
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(x,l,r);
	if(pos<=mid) upd(LC,l,mid,pos);
	else upd(RC,mid+1,r,pos);
	pushup(x);
}
void add(ll &x,ll l,ll r,ll ql,ll qr,ll v){
	if(!x) x=newnode();
	if(ql<=l&&r<=qr){
		tree[x].addtag(v,(ll)inf,l);
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(x,l,r);
	if(ql<=mid) add(LC,l,mid,ql,qr,v);
	if(mid<qr) add(RC,mid+1,r,ql,qr,v);
	pushup(x);
}
void mdf(ll &x,ll l,ll r,ll ql,ll qr,ll v){
	if(!x) x=newnode();
	if(ql<=l&&r<=qr){
		tree[x].addtag(0,v,l);
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(x,l,r);
	if(ql<=mid) mdf(LC,l,mid,ql,qr,v);
	if(mid<qr) mdf(RC,mid+1,r,ql,qr,v);
	pushup(x);
}
ll merge(ll x,ll y,ll l,ll r){
	if(!LC&&!RC){
		tree[y].addtag(0,tree[x].minn1,l);
		return y;
	}
	if(!tree[y].lc&&!tree[y].rc){
		tree[x].addtag(0,tree[y].minn1,l);
		return x;
	}
	ll mid=(l+r)>>1;
	pushdown(x,l,r);
	pushdown(y,l,r);
	LC=merge(LC,tree[y].lc,l,mid);
	RC=merge(RC,tree[y].rc,mid+1,r);
	pushup(x);
	return x;
}
ll query(ll x,ll y,ll l,ll r){
	if(!LC&&!RC) return tree[x].minn1+tree[y].minn2;
	if(!tree[y].lc&&!tree[y].rc) return tree[y].minn1+tree[x].minn2;
	ll mid=(l+r)>>1,res=inf;
	pushdown(x,l,r);
	pushdown(y,l,r);
	res=min(res,query(LC,tree[y].lc,l,mid));
	res=min(res,query(RC,tree[y].rc,mid+1,r));
	return res;
}
void dfs(ll u){
	if(!ch[u][0]){
		mdf(rt[u],1,n+1,1,n+1,0);
		if(a[u]<=(n+1)) upd(rt[u],1,n+1,a[u]);
		if(u==1) ans=0;
	}
	else if(!ch[u][1]){
		dfs(ch[u][0]);
		rt[u]=rt[ch[u][0]];
		if(a[u]<=(n+1)) upd(rt[u],1,n+1,a[u]);
		ll minn=tree[rt[u]].minn2;
		mdf(rt[u],1,n+1,1,n+1,minn);
		if(a[u]<=(n+1)) upd(rt[u],1,n+1,a[u]);
		if(u==1) ans=minn;
	}
	else{
		ll x=ch[u][0],y=ch[u][1];
		dfs(x);
		dfs(y);
		if(a[u]<=(n+1)){
			upd(rt[x],1,n+1,a[u]);
			upd(rt[y],1,n+1,a[u]);
		}
		ll minx=tree[rt[x]].minn2,miny=tree[rt[y]].minn2,k=min(query(rt[x],rt[y],1,n+1),minx+miny);
		add(rt[x],1,n+1,1,n+1,miny);
		add(rt[y],1,n+1,1,n+1,minx);
		rt[u]=merge(rt[x],rt[y],1,n+1);
		mdf(rt[u],1,n+1,1,n+1,k);
		if(a[u]<=(n+1)) upd(rt[u],1,n+1,a[u]);
		if(u==1) ans=k;
	}
}
il void clr(){
	fr(i,1,n) ch[i][0]=ch[i][1]=rt[i]=0;
	tot=0;
	ans=inf;
}
int main(){
	t=read();
	while(t--){
		n=read();
		fr(i,1,n) a[i]=read();
		fr(i,2,n){
			ll x=read();
			if(!ch[x][0]) ch[x][0]=i;
			else ch[x][1]=i;
		}
		dfs(1);
		writeln(ans);
		clr();
	}
} 
```

---

## 作者：Inui_Sana (赞：3)

[推荐](https://littleyinhee.github.io/post/cf1981f/)

### Sol 1

首先有个一定需要的 $O(n^2)$ dp：设 $dp_{u,i}$ 表示当前在 $u$ 点，钦定选的链上点权一定不包含 $i$，此时的最小代价。转移是非常简单的，只要看当前链是否在这里断开即可。而且 $\operatorname{mex}$ 性质是很好的，如果此时转移的 $i$ 并不是 $\operatorname{mex}$，也一定不会成为最优解，而是真正的 $\operatorname{mex}$ 会成为最优解。于是这么做是正确的。

然后会观察出一个问题：我们很多时候并不会取到很大的 $\operatorname{mex}$。然而，我们 dp 的第二维就是和这个上界相关。而根据证明（参考 cf 上的 edtorial），这个上界是 $O(\dfrac{n}{\ln n})$ 的！我们也可以通过一个构造证明：`12131421516321`，即把每个数和它的因数降序列出。感性理解一下发现很有道理。你考虑分成 $n$ 组。对于每个数 $x$，你都会希望每 $x$ 长度就有一个 $x$，否则消耗了这么多的长度会亏。~~并且通过提交证明这是对的。~~

于是就限制第二维枚举到大概 $4000$，就可以 $O(\dfrac{n^2}{\ln n})$ 解决了。

code：

```cpp
bool Mbe;
int n,m,c[N],dp[N][M],ls[N],rs[N];
void dfs(int u){
    if(!u){
        return;
    }
    dfs(ls[u]),dfs(rs[u]);
    if(!ls[u]&&!rs[u]){
        rep(i,1,m){
            if(i!=c[u]){
                dp[u][i]=0;
            }
        }
        if(u==1){
            puts("0");
        }
        return;
    }
    if(!rs[u]){
        int mn=inf;
        rep(i,1,m){
            if(i!=c[u]){
                dp[u][i]=dp[ls[u]][i];
                mn=min(mn,dp[u][i]+i);
            }
        }
        rep(i,1,m){
            if(i!=c[u]){
                dp[u][i]=min(dp[u][i],mn);
            }
        }
        if(u==1){
            printf("%d\n",mn);
        }
        return;
    }
    int x=inf,y=inf,mn=inf;
    rep(i,1,m){
        if(i!=c[u]){
            x=min(x,dp[ls[u]][i]+i);
            y=min(y,dp[rs[u]][i]+i);
        }
    }
    rep(i,1,m){
        if(i==c[u]){
            continue;
        }
        mn=min(mn,dp[ls[u]][i]+dp[rs[u]][i]+i);
        dp[u][i]=min({dp[u][i],dp[ls[u]][i]+y,dp[rs[u]][i]+x});
    }
    rep(i,1,m){
        if(i!=c[u]){
            dp[u][i]=min(dp[u][i],mn);
        }
    }
    if(u==1){
        printf("%d\n",min(mn,x+y));
    }
}
void Yorushika(){
    scanf("%d",&n),m=min(n+1,4000);
    rep(i,1,n){
        scanf("%d",&c[i]);
        rep(j,1,m){
            dp[i][j]=inf;
        }
        ls[i]=rs[i]=0;
    }
    rep(i,2,n){
        int u;scanf("%d",&u);
        if(ls[u]){
            rs[u]=i;
        }else{
            ls[u]=i;
        }
    }
    dfs(1);
}
bool Med;
signed main(){
	cerr<<(&Mbe-&Med)/1048576.0;
    int t=1;
        scanf("%d",&t);
    while(t--)
        Yorushika();
}
```

### Sol 2

先有 $O(n^2)$ dp，然后观察到一个性质：对于所有没在以 $u$ 为根的子树内出现过的点权 $x$，$dp_{u,x}$ 都是相等的！原因显然。而且我们 dp 的转移是非常好维护的，于是可以使用线段树合并或启发式合并解决。时间复杂度 $O(n\log n)$ 或 $O(n\log^2 n)$。

可以参考 [AFewSuns 的代码](https://codeforces.com/contest/1981/submission/263520936)。

---

## 作者：Link_Cut_Y (赞：2)

首先有朴素的 dp：$f_{u, i}$ 表示以 $u$ 为根的子树已经 finish 了，经过 $u$ 往上走的路径 MEX 为 $i$。$i$ 的取值是 $[1, n + 1] \bigcap \mathbb{Z}$，因为一共只有 $n$ 个点。

转移的时候分情况，看看子树往上走的路径是在 $u$ 断开还是继续向上延伸。如果有两个儿子还要考虑是否需要将两个向上走的链在 $u$ 这里 merge 起来。

这个朴素 dp 是 $O(n ^ 2)$ 的。但是根据直觉 MEX 不会很大。因此转移时第二维只转移到 $5000$。由于 CF 的神机，很轻松的就跑过了。

----------

为什么只需要转移到 $5000$ 呢？我提交之后参考了一下官方的题解。证明思路大概是这样的（下面只证明链的情况）：假设权值 $i$ 出现了 $s_i$ 次。对于一个序列，将每个 $i$ 与其左右划分为一段，剩下的部分同样成段。这样一共能分出 $2s_i + 1$ 段。

其中含有 $i$ 的段 MEX $\le i$（因为 $i$ 一定不在序列中），含有 $i$ 的段 MEX $\le 4$（因为段长为 $3$）。

设 MEX 上界为 $t$，则有 $\min\{(s_i + 1)i + 4s_i\} \ge t$。又 $\min\{(s_i + 1)i + 4s_i\} < \min\{(s_i + 1)i + 4(s_i + 1)\}$，可以放缩一下，解得 $s_i \le \left \lfloor \dfrac{t}{i +4} \right \rfloor - 1$。

由于 $\sum s_i = n$，根据调和级数可以得到 $n = O(t \ln t)$，也就是说 $t$ 实际上是 $O(\dfrac{n}{\ln n})$ 级别的。题解说 $t = 3863$。

```cpp

const int N = 25010;
const int INF = 2e9;
int f[N][5010], a[N], p[N], n, lim; 
vector<int> E[N];
void dfs(int u) {
	if (!E[u].size()) { // u is leaf.
		rep(i, 1, lim) f[u][i] = i == a[u] ? INF : 0;
	} else if (E[u].size() & 1) { // u has only one son.
		int x = E[u][0], mn = INF; dfs(x);
		rep(i, 1, lim) if (i ^ a[u]) mn = min(mn, f[x][i] + i); // split at u, and inherit from x.
		rep(i, 1, lim) f[u][i] = (i ^ a[u]) ? min(f[x][i], mn) : INF;
		if (u == 1) printf("%lld\n", mn);
	} else {
		int x = E[u][0], y = E[u][1], mn0 = INF, mn1 = INF, mn = INF; dfs(x), dfs(y);
		rep(i, 1, lim) if (i ^ a[u]) mn0 = min(mn0, f[x][i] + i); // x split at u, and y go upward.
		rep(i, 1, lim) if (i ^ a[u]) mn1 = min(mn1, f[y][i] + i); // y split at u, and x go upward.
		rep(i, 1, lim) if (i ^ a[u]) mn = min(mn, f[x][i] + f[y][i] + i); // merge at u.
		rep(i, 1, lim) f[u][i] = (i ^ a[u]) ? min({f[x][i] + mn1, f[y][i] + mn0, mn, mn0 + mn1}) : INF;
		if (u == 1) printf("%lld\n", min(mn0 + mn1, mn));
	}
}
signed main() {
	read(T);
	while (T -- ) {
		read(n);
		rep(i, 1, n) E[i].clear();
		rep(i, 1, n) read(a[i]);
		rep(i, 2, n) read(p[i]);
		rep(i, 2, n) E[p[i]].push_back(i);
		lim = min(n + 1, 5000ll); dfs(1);
	} return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1981F)

**题目大意**

> 给定 $n$ 个点的二叉树，点带权，将树上的边分成若干条路径，最小化每条路径上点权 $\mathrm{MEX}$ 的和。
>
> 数据范围：$n\le 2.5\times 10^4$.

**思路分析**

先刻画 $\mathrm{MEX}$，很显然可以改成：钦定一个数 $x$ 不为路径上任何一个点的点权，代价为 $x$。

那么 $\mathrm{MEX}$ 就是最小的 $x$，求最小答案能保证正确性。

于是可以 dp，设 $f_{u,i}$ 表示 $u$ 子树，钦定过 $u\to fa_u$ 的链 $\mathrm{MEX}=i$。

转移的时候尝试把左右子树的链闭合起来，或者把两条链在 $u$ 处连接，再新建一条向上。

时间复杂度 $\mathcal O(n^2)$。

但是我们观察到答案中不会存在 $\mathrm{MEX}$ 太大的链，否则可以分割成总权值和更小的子段。

对于一条 $\mathrm{MEX}=v$ 的链，观察其中的元素 $x$ 的出现，把链写成 $C_0,x,C_1,x,\dots,x,C_k$。

可以把链划分成 $C_0,C_1,\dots ,C_k$，以及每个 $x$ 加上其左右的元素。

此时 $C_i$ 的权值 $\le x$，包含 $x$ 的链取值 $\le 4$，那么 $v\le (k+1)x+4k$，因此 $k$ 至少是 $\dfrac vx$ 级别的。

因此权值为 $v$ 的链无法分割，其长度至少为 $v\log v$ 级别，由于链长 $\le n$，故 $v$ 大约是 $\dfrac n{\log n}$。

可以证明 $n\le 25000$ 时 $v\le 4000$。

时间复杂度 $\mathcal O\left(\dfrac{n^2}{\log n}\right)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=25005,B=4000,inf=1e9;
int n,f[MAXN][B+5],a[MAXN];
vector <int> G[MAXN];
void dfs(int u) {
	if(G[u].empty()) {
		for(int i=1;i<=B;++i) f[u][i]=(i==a[u]?inf:0);
		return ;
	}
	if(G[u].size()==1) {
		int mn=inf,v=G[u][0];
		dfs(v);
		for(int i=1;i<=B;++i) if(i!=a[u]) mn=min(mn,f[v][i]+i);
		for(int i=1;i<=B;++i) f[u][i]=(i==a[u]?inf:min(f[v][i],mn));
		if(u==1) cout<<mn<<"\n";
		return ;
	}
	int x=G[u][0],y=G[u][1];
	dfs(x),dfs(y);
	int mn=inf,mnx=inf,mny=inf;
	for(int i=1;i<=B;++i) if(i!=a[u]) mn=min(mn,f[x][i]+f[y][i]+i),mnx=min(mnx,f[x][i]+i),mny=min(mny,f[y][i]+i);
	for(int i=1;i<=B;++i) f[u][i]=(i==a[u]?inf:min({f[x][i]+mny,f[y][i]+mnx,mn}));
	if(u==1) cout<<min(mn,mnx+mny)<<"\n";
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],G[i].clear(),fill(f[i]+1,f[i]+B+1,inf);
	for(int i=2,fz;i<=n;++i) cin>>fz,G[fz].push_back(i);
	dfs(1);
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

