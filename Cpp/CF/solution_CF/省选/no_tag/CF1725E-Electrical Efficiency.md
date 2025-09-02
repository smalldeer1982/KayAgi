# Electrical Efficiency

## 题目描述

In the country of Dengkleknesia, there are $ N $ factories numbered from $ 1 $ to $ N $ . Factory $ i $ has an electrical coefficient of $ A_i $ . There are also $ N-1 $ power lines with the $ j $ -th power line connecting factory $ U_j $ and factory $ V_j $ . It can be guaranteed that each factory in Dengkleknesia is connected to all other factories in Dengkleknesia through one or more power lines. In other words, the collection of factories forms a tree. Each pair of different factories in Dengkleknesia can use one or more existing power lines to transfer electricity to each other. However, each power line needs to be turned on first so that electricity can pass through it.

Define $ f(x, y, z) $ as the minimum number of power lines that need to be turned on so that factory $ x $ can make electrical transfers to factory $ y $ and factory $ z $ . Also define $ g(x, y, z) $ as the number of distinct prime factors of $ \text{GCD}(A_x, A_y, A_z) $ .

To measure the electrical efficiency, you must find the sum of $ f(x, y, z) \times g(x, y, z) $ for all combinations of $ (x, y, z) $ such that $ 1 \leq x < y < z \leq N $ . Because the answer can be very large, you just need to output the answer modulo $ 998\,244\,353 $ .

Note: $ \text{GCD}(k_1, k_2, k_3) $ is the greatest common divisor of $ k_1 $ , $ k_2 $ , and $ k_3 $ , which is the biggest integer that simultaneously divides $ k_1 $ , $ k_2 $ , and $ k_3 $ .

## 说明/提示

In the first example, the only $ (x, y, z) $ possible is $ (1, 2, 3) $ . Because $ \text{GCD}(A_1, A_2, A_3) = \text{GCD}(1, 2, 3) = 1 $ has $ 0 $ distinct prime factors, therefore $ f(x, y, z) \times g(x, y, z) = 2 \times 0 = 0 $ .

In the second example, all triples $ (x, y, z) $ that satisfy the condition are as follows:

- $ (1, 2, 3) \rightarrow f(1, 2, 3) \times g(1, 2, 3) = 2 \times 1 = 2 $
- $ (1, 2, 4) \rightarrow f(1, 2, 4) \times g(1, 2, 4) = 2 \times 1 = 2 $
- $ (1, 3, 4) \rightarrow f(1, 3, 4) \times g(1, 3, 4) = 3 \times 2 = 6 $
- $ (2, 3, 4) \rightarrow f(2, 3, 4) \times g(2, 3, 4) = 2 \times 1 = 2 $

So the electrical efficiency is $ 2 + 2 + 6 + 2 = 12 $ .

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3```

### 输出

```
0```

## 样例 #2

### 输入

```
4
6 14 6 6
1 2
2 3
2 4```

### 输出

```
12```

# 题解

## 作者：WangManhe (赞：10)

> 这题正解是虚树，本解法卡常，仅适合不会虚树的。(例如本人)

注意：下文中根节点深度定义为 1

# 第一步: 转化问题

我们把 $ g(x,y,z) $ 拆开，考虑每个质数是哪些点的因子。

包含这个质数的点构成一个点集，我们只需求这个点集 S 的 $ \sum\limits_{x,y,z\in S } f(x,y,z) $。

# 第二步: 对于已知点集 S 的 $ \sum\limits_{x,y,z\in S } f(x,y,z) $

首先考虑三个点构成的最小连通块的边数。

这可以简单计算出： 

$$ \dfrac{\operatorname{dist}(u,v)+\operatorname{dist}(v,w)+\operatorname{dist}(u,w)}{2} $$

通过式子可以算出，点集内每两个点的距离恰好被计算 $ \frac{|S|-2}{2} $ 次。

通过某种方法计算 $\sum\limits_{x,y\in S } \operatorname{dist}(x,y) $ ，乘上 $ \frac{|S|-2}{2} $ 获得答案。

# 第三步: "某种方法"

我们需要求： 

$$ \sum\limits_{x,y\in S } \operatorname{dist}(x,y) $$ 

使用树上差分： 

$$ \operatorname{dist}(x,y) = \operatorname{depth}(x) + \operatorname{depth}(y) - 2 \operatorname{depth}(\operatorname{lca}(u,v))$$

带回求和得到

$$ \begin{aligned}
    \sum\limits_{x,y\in S } \operatorname{dist}(x,y) 
    = \sum\limits_{x,y\in S } \operatorname{depth}(x) + \operatorname{depth}(y) - 2 \operatorname{depth}(\operatorname{lca}(u,v))\\
\end{aligned}
$$

我们依次加入点，通过记录前面的点的深度和以及前面的点的个数，可以简单处理这个式子的前两块。

对于包含 LCA 的深度的部分，我们通过数据结构可以处理。

加入一个点的时候，给这个点到根节点的所有点点权加上一，查询一个点的时候，查询这个点到根节点的点权和，这就是这个点与之前所有点的 LCA 的深度和。

为什么呢？

考虑 LCA 的深度在树上的实际意义，就是两点到根的路径的重合点数，然后就好理解了。

# 代码

本题卡常，代码中使用了树状数组而不是线段树。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353;
const int MxN=200000;
int n,Answer,result,TotalDepth,Count;
int head[MxN+5],nxt[2*MxN+5],to[2*MxN+5],tot;
int siz[MxN+5],depth[MxN+6],son[MxN+5],top[MxN+5],father[MxN+5];
int L[MxN+5],R[MxN+5],rnk[MxN+5],tim;
int value[MxN+5];
vector<int>Ver[MxN+5];
int Pow(int A,int B){
    int res=1;
    while(B){
        if(B&1){
            res=res*A%MOD;
        }
        A=A*A%MOD;
        B>>=1;
    }
    return res;
}
void AddEdge(int u,int v){
    to[++tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
}
void DFS1(int p,int fa){
    siz[p]=1;
    father[p]=fa;
    depth[p]=depth[fa]+1;
    for(int i=head[p];i;i=nxt[i]){
        if(to[i]!=fa){
            DFS1(to[i],p);
            siz[p]+=siz[to[i]];
            if(siz[to[i]]>siz[son[p]]){
                son[p]=to[i];
            }
        }
    }
}
void DFS2(int p,int fa,int tp){
    L[p]=++tim;
    rnk[tim]=p;
    top[p]=tp;
    if(son[p]){
        DFS2(son[p],p,tp);
    }
    for(int i=head[p];i;i=nxt[i]){
        if(to[i]!=fa&&to[i]!=son[p]){
            DFS2(to[i],p,to[i]);
        }
    }
    R[p]=tim;
}
struct BIT{
    int T[MxN+5],TT[MxN+5];
    void Modify(int l,int r,int c){
        for(int i=l;i<=n;i+=i&-i){T[i]+=c;TT[i]+=c*l;}
        for(int i=(r+1);i<=n;i+=i&-i){T[i]-=c;TT[i]-=c*(r+1);}
    }
    int Query(int l,int r){
        int res=0;
        for(int i=r;i;i-=i&-i){res+=(r+1)*T[i];res-=TT[i];}
        for(int i=l-1;i;i-=i&-i){res-=(l)*T[i];res+=TT[i];}
        return res;
    }
}bit;
void Insert(int u){
    int res=TotalDepth+Count*depth[u],v=u;
    while(v){
        res=(res-2*bit.Query(L[top[v]],L[v])%MOD+MOD)%MOD;
        bit.Modify(L[top[v]],L[v],1);
        v=father[top[v]];
    }
    TotalDepth=(TotalDepth+depth[u])%MOD;
    Count=(Count+1)%MOD;
    result=(result+res)%MOD;
}
void Delete(int u){
    int v=u;
    while(v){
        bit.Modify(L[top[v]],L[v],-1);
        v=father[top[v]];
    }
}
void Calculate(int num){
    result=0;TotalDepth=0;Count=0;
    for(auto i:Ver[num]){
        Insert(i);
    }
    Answer=(Answer+result*(Count-2)%MOD*Pow(2,MOD-2)%MOD)%MOD;
    for(auto i:Ver[num]){
        Delete(i);
    }
}
signed main(){
    int u,v;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&value[i]);
        int t=value[i];
        for(int j=2;j*j<=t;j++){
            if(t%j==0){
                Ver[j].push_back(i);
                while(t%j==0){
                    t/=j;
                }
            }
        }
        if(t>1){
            Ver[t].push_back(i);
        }
    }
    for(int i=1;i<n;i++){
        scanf("%lld%lld",&u,&v);
        AddEdge(u,v);
        AddEdge(v,u);
    }
    DFS1(1,0);
    DFS2(1,0,1);
    for(int i=2;i<=MxN;i++){
        Calculate(i);
    }
    printf("%lld\n",Answer);
}
```

# 总结

使用了很顺畅的思路流程，不是正解而且卡常，但是好理解才是重要的。 :D

---

## 作者：fanypcd (赞：5)

### 简要题意：

树上 $n$ 个点，每个点有点权 $a_i$。对于一个三元组 $(x,y,z)$ 满足 $1 \leq x < y < z \leq n$，定义 $f(x,y,z)$ 为树上连通这三个点的连通块边数，$g(x,y,z)$ 为 $\gcd(a_x,a_y,a_z)$ 所含的不同质因子个数，求 $\sum f(x,y,z)\times g(x,y,z)$。

---

显然可以单独对每个质因子考虑贡献，即原答案等价于 $\sum \limits_{d \in \mathbb{P}} \sum f(x,y,z) [d \mid \gcd(a_x,a_y,a_z)]$。

然后发现 $f(x,y,z)=\frac{dis(x,y)+dis(y,z)+dis(x,z)}{2}$，可以自己举几种情况试试。

所以 $\sum f(x,y,z)={(n-2)\over 2}\sum dis(x,y)$。

考虑枚举质数 $p$，把所有 $p \mid a_i$ 的点拎出来建虚树，然后一次 dfs 算出任意两点间的距离之和（注意只计算关键点的贡献，对于保持树的形态加入的点不算）。

每个点会被它点权的不同质因子拉入虚树，复杂度大约为 $O(n \omega{\small(}n{\small)}\log n)$，但是远远跑不满（树剖 lca），已经足以通过此题。有兴趣也可以用 $O(1)$ lca 做到更优的理论复杂度。

```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T> inline void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while(!isdigit(ch)) {
		f |= ch == '-';
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? - x : x; return;
}
#define inf 0x3f3f3f3f
#define fir first
#define sec second
#define ll long long
#define N 200005
int n;
struct Graph1 {
	int first[N], Next[N << 1], to[N << 1], tot;
	inline void add(int x, int y) {
//		printf("link:%d -> %d\n", x, y);
		Next[++tot] = first[x];
		first[x] = tot;
		to[tot] = y;
		return;
	}
} Ori, Vir;
int dep[N], fa[N], siz[N], hson[N];
void getdep(int u) {
	siz[u] = 1; for(int i = Ori.first[u]; i; i = Ori.Next[i]) {
		int v = Ori.to[i]; if(v != fa[u]) {
			dep[v] = dep[u] + 1; fa[v] = u;
			getdep(v); siz[u] += siz[v];
			if(siz[v] > siz[hson[u]])
				hson[u] = v;
		}
	}
	return;
}
int top[N], dfn[N], sign;
void gettop(int u, int fr) {
	top[u] = fr; dfn[u] = ++sign;
	if(hson[u]) gettop(hson[u], fr);
	for(int i = Ori.first[u]; i; i = Ori.Next[i]) {
		int v = Ori.to[i]; if(v != fa[u] && v != hson[u]) {
			gettop(v, v);
		}
	}
	return;
}
inline int lca(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] > dep[top[y]]) swap(x, y);
		y = fa[top[y]];
	}
	if(dep[x] > dep[y]) swap(x, y); return x;
}
vector<int> ndval[N];
bool flag[N], real_nd[N];
int a[N], vsz;
bool cmp(int x, int y) {
	return dfn[x] < dfn[y];
}
int st[N], tp;
inline void VT_build() {
	Vir.tot = 0;
	sort(a + 1, a + vsz + 1, cmp);
	st[tp = 1] = a[1];
	for(int i = 2; i <= vsz; i++) {
		int lc = lca(st[tp], a[i]);
		while(1) {
			if(dep[lc] >= dep[st[tp - 1]]) {
				if(lc != st[tp]) {
					Vir.add(lc, st[tp]);
					if(lc != st[tp - 1]) {
						st[tp] = lc;
					}
					else tp--;
				}
				break;
			}
			else {
				Vir.add(st[tp - 1], st[tp]);
				tp--;
			}
		}
		st[++tp] = a[i];
	}
	while(--tp) {
		Vir.add(st[tp], st[tp + 1]);
	}
	return;
}
const int mod = 998244353;
int ans = 0, tmp;
inline void addmod(int &x, int y) {
	x += y; if(x >= mod) x -= mod; return;
}
void dfs(int u) {
	siz[u] = real_nd[u];
	for(int i = Vir.first[u]; i; i = Vir.Next[i]) {
		int v = Vir.to[i]; dfs(v); siz[u] += siz[v];
		addmod(tmp, 1ll * (dep[v] - dep[u]) * siz[v] % mod * (vsz - siz[v]) % mod);
	}
	Vir.first[u] = 0; return;
}
const int inv = 499122177;
signed main() {
	read(n); int x, y, mx = 0;
	for(int i = 1; i <= n; i++) {
		read(x); ndval[x].emplace_back(i);
		mx = max(mx, x);
	}
	for(int i = 2; i <= mx; i++) {
		if(!flag[i]) {
			for(int j = 2 * i; j <= mx; j += i) {
				flag[j] = 1;
			}
		}
	}
	for(int i = 1; i < n; i++) {
		read(x), read(y); Ori.add(x, y), Ori.add(y, x);
	}
	getdep(dep[1] = 1); gettop(1, 1);
	for(int pv = 2; pv <= mx; pv++) {
		if(!flag[pv]) {
			vsz = 0;
			for(int mulpv = pv; mulpv <= mx; mulpv += pv) {
				for(auto und : ndval[mulpv]) {
					a[++vsz] = und;
				}
			}
			VT_build();
			for(int i = 1; i <= vsz; i++) real_nd[a[i]] = 1;
			tmp = 0; if(vsz) dfs(st[1]);
			addmod(ans, 1ll * tmp * (vsz - 2) % mod * inv % mod);
			for(int i = 1; i <= vsz; i++) real_nd[a[i]] = 0;
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Luciylove (赞：2)

考虑对于质因子建虚树。

根据虚树相关理论：

$f(x, y, z)$ 就是这三个点的虚树边权和，考虑到在三个数的情况下，怎么轮换搜索序顺序都是对的，所以有：

$$f(x, y, z) = \frac{d(x, y) + d(y, z) + d(x, z)}{2}$$

其中 $d(x, y)$ 表示距离。

考虑对于 $(x, y)$ 观察其贡献了多少次。固定 $(x, y)$ 则对于所有的 $n - 2$ 个 $z$ 都会产生贡献。所以贡献是 $\frac{(n - 2)d(x, y)}{2}$。

然后答案式子就是一个系数乘上虚树上距离和即：

$$\frac{(n - 2)\sum d(x, y)}{2}$$

后者可以考虑关键点对经过一条边的贡献是多少次计算，树形 DP 即可。

时间复杂度 $O(n\log n \omega(n))$ 瓶颈在于排序建虚树。
代码实现采用了二次排序建虚树。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)

using namespace std;
typedef long long ll;

const int _ = 4e5 + 5, mod = 998244353;
const int V = 2e5 + 100;

int power (int x, int y) {
	int ret = 1;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) ret = 1ll * ret * x % mod;
	return ret;
}
void add (int & x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
int mul (int x, int y) { return 1ll * x * y % mod; }


int n, dfc, a[_];
int tn, pr[_]; bool isp[_];
int dep[_], dfn[_], anc[_][21];
int tot, vir[_], sz[_];
vector <int> e[_];
vector <int> nd[_];
ll ans, ret;

void dfs (int x, int fa) {
	anc[x][0] = fa, dfn[x] = ++ dfc, dep[x] = dep[fa] + 1;
	rep(i, 1, 20) anc[x][i] = anc[anc[x][i - 1]][i - 1];
	for (int y : e[x]) if (y ^ fa) dfs(y, x);
}

int LCA (int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int d = dep[x] - dep[y];
	rep(i, 0, 20) if (d & (1 << i)) x = anc[x][i];
	if (x == y) return x;
	per(i, 20, 0) if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i]; 
	return anc[x][0];
}
namespace virTree {
	bool isq[_];
	int vit[_];
	vector <int> vt[_];
	bool cmp (int x, int y) { return dfn[x] < dfn[y]; }
	void build () {
		rep(i, 1, tot) isq[vir[i]] = 1;
		int len = 0;
		sort(vir + 1, vir + 1 + tot, cmp);
		rep(i, 1, tot - 1) {
			vit[++ len] = vir[i];
			vit[++ len] = LCA(vir[i], vir[i + 1]);
		} vit[++ len] = vir[tot], vit[++ len] = 1;
		sort(vit + 1, vit + 1 + len, cmp),
		len = unique(vit + 1, vit + 1 + len) - (vit + 1);
		rep(i, 1, len - 1) {
			int lc = LCA(vit[i], vit[i + 1]);
			vt[lc].push_back(vit[i + 1]);
		}
	}
	void dfs2 (int x, int fa) {
		sz[x] = isq[x];
		for (int y : vt[x]) {
			if (y == fa) continue;
		    dfs2(y, x);
			sz[x] += sz[y], 
			(ans += 1ll * (tot - sz[y]) * sz[y] % mod * (dep[y] - dep[x]) % mod) %= mod;
		}
		isq[x] = 0;
		vt[x].clear();
	}
} ;
int main() {
	/*
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
	黛拉可玛莉·岗德森布莱德，一亿年一遇美少女。
	*/
	cin >> n;
	rep(i, 1, n) scanf("%d", & a[i]), nd[a[i]].push_back(i);
	rep(i, 1, n - 1) {
		int x, y;
		scanf("%d%d", & x, & y);
		e[x].push_back(y), e[y].push_back(x);
	}
	dfs(1, 0);
	rep(i, 2, V) {
		if (!isp[i]) pr[++ tn] = i;
		for (int j = 1; i * pr[j] <= V && j <= tn; j ++) {
			isp[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
	rep(i, 1, tn) {
		ans = tot = 0;
		int x = pr[i];
		for (int y = x; y <= V; y += x) 
			for (int p : nd[y]) vir[++ tot] = p;
		if (tot <= 2) continue ;
		virTree::build();
		virTree::dfs2(1, 0);
		ans = ans * (tot - 2) % mod * ((mod + 1) / 2) % mod;
		(ret += ans) %= mod;
	}
	cout << ret;
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：2)

# CF1725E Electrical Efficiency 题解

观察 $g$ 的形式很特殊，按照套路先拆 $\gcd(a_x,a_y,a_z)$ 的质因子个数。

**直接枚举**质因子，即原式就变成了 $\sum_{d\in prime} \sum f(x,y,z)[d\mid\gcd(a_x,a_y,a_z)]=\sum_{d\in prime}\sum f(x,y,z)[d\mid a_x][d\mid a_y][d\mid a_z]$。

根据 $d$，对于所有 $d\mid a_i$ 的点作为**关键点**构建**虚树**。可以证明一个数的质因子个数**不会**超过 $7$ 个，所以这里的时间复杂度是 $O(n\log n)$ 级别的。

具体程序实现就弄个筛法，计算每个数的最大质因子，然后使用**链式前向星**存储编号即可。

接下来问题转化成了 $\sum f(x,y,z)$。根据虚树的理论，把 $x,y,z$ 作为关键点构建虚树，结论就是 $f(x,y,z)=\dfrac{1}{2}(d(x,y)+d(y,z)+d(x,z))$ 。（其中 $d(x,y)$ 为 $x,y$ 之间的距离）

如何计算这个值呢？考虑**间接计算**。统计每条边的贡献。

对于一条边 $(x,y)$，它作为 $f(x,y,z)$ 对答案做贡献的时候，合法的 $z$ 有 $(n-y)$ 个，即这条边贡献了 $(n-y)$ 次；

它作为 $f(x,z,y)$ 对答案做贡献的时候，合法的 $z$ 有 $(y-x-1)$ 个，即这条边贡献了 $(y-x-1)$ 次；

它作为 $f(z,x,y)$ 对答案做贡献的时候，合法的 $z$ 有 $(x-1)$ 个，即这条边贡献了 $(x-1)$ 次；

于是这条边就对答案贡献了 $(n-2)$ **次**，答案就是 $\dfrac{(n-2)}{2}\sum d(x,y)$。这个式子的后半部分可以直接树形 DP 求得。

不会后半部分的可以做[这个题](https://www.luogu.com.cn/problem/P2986)。但是注意这里的**子树大小**是子树中**关键点**的个数。

总时间复杂度 $O(n\omega(n)\log_2n)$，速度飞快，稳稳通过 $n\le 2\times 10^5$ 的数据。

---

代码实现这里采用了树剖求 LCA，二次排序法建虚树，链式前向星存储原树、虚树和质因子对应的节点编号。

（为什么不用 `vector` 呢？因为前两周我做过[性能测试](https://www.luogu.com.cn/blog/SmallTualatin/speedtest-graph)，结果是 `vector` 的存图效率**远远不如**前向星）。

下面会对关键部分（容易写错的地方）做一些注释。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i=(a);i<=(b);++i)
using namespace std;typedef int I;typedef void V;
const I N=2e5+10,mod=998244353;
struct graph{
	I*ey,*nx,hd[N],*ez,ec=0;
	graph(I m){if(m)ey=new int[m],ez=new int[m],nx=new int[m];ec=0;}//使用指针进行分配动态内存
	V conn(I x,I y,I z=0){ey[++ec]=y;nx[ec]=hd[x];hd[x]=ec;ez[ec]=z;}//普通的连边
	V dest(){delete ey;delete nx;delete ez;ec=0;}//清除整张图，即为删除所有边，但是这里没有清空 hd
}G(N<<1),VT(N<<1),D(N*7);
#define go(T,x) for(I _i=(T).hd[(x)],y,z;y=(T).ey[_i],z=(T).ez[_i],_i;_i=(T).nx[_i])
//使用宏定义简化代码 go(T,x) 表示在 T 图中 x 开始的一条单向链进行遍历，y 为出边节点，z 为出边长度
I mip[N],pr[N],a[N<<1],n,pl,m;
//注意：这里的 n 被复用了。原来 n 是输入的点的个数，建立虚树的时候我们定为关键点的个数。
//这里的 pr 也被复用了，因为筛出质数之后我们就不需要质数数组了，可以直接覆写
//这里的 a 也被复用了，原来是编号对应的数值，现在是虚树的节点编号
//m 为当前虚树节点个数
bool np[N];
V ext(I x,I y){pl=0;
	for(;x^1;x/=mip[x])pr[++pl]=mip[x];//整理出 x 所有最小的质因子。
	sort(pr+1,pr+pl+1);pl=unique(pr+1,pr+pl+1)-pr-1;//这里排序去重处理一下
	fo(i,1,pl)D.conn(pr[i],y);}//对于质因子存储相对应的编号 y
I d[N],dfn[N],tp[N],s[N],fa[N],clk,hs[N];
V dfs1(I x,I fa=0){s[x]=1;d[x]=d[fa]+1;::fa[x]=fa;dfn[x]=++clk;
	go(G,x)if(y!=fa)dfs1(y,x),s[x]+=s[y],hs[x]=(s[y]>s[hs[x]]?y:hs[x]);}
V dfs2(I x,I tp=1){::tp[x]=tp;if(hs[x])dfs2(hs[x],tp);
	go(G,x)if(y!=fa[x]&&y!=hs[x])dfs2(y,y);}
I lca(I x,I y){while(tp[x]^tp[y]){if(d[tp[x]]<d[tp[y]])swap(x,y);
	x=fa[tp[x]];}return d[x]<d[y]?x:y;}
//这上面几行都是树链剖分的普通代码，注意 s 在上面的计算中，是 s 子树内部点的个数
//在虚树的计算中被复用，成为子树内部关键点的个数
bool cmp(I x,I y){return dfn[x]<dfn[y];}
//按照 dfn 序关键字比较
bool is[N];//is[x] 表示 x 是不是关键点
V bvt(){m=n;
	sort(a+1,a+n+1,cmp);
	fo(i,(is[a[1]]=1,2),n)is[a[i]]=1,a[++m]=lca(a[i-1],a[i]);
	sort(a+1,a+m+1,cmp);m=unique(a+1,a+m+1)-a-1;
	VT=(m<<1);fo(i,1,m)VT.hd[a[i]]=0;I lc=1;
	fo(i,2,m)lc=lca(a[i-1],a[i]),VT.conn(lc,a[i],d[a[i]]-d[lc]);}//普通的二次排序虚树构建。记得清空虚树的 hd 数组。
I dfs(I x){long long ans=0;s[x]=is[x];//求答案
	go(VT,x)ans+=dfs(y),s[x]+=s[y],ans+=(1ll*z*s[y])%mod*(n-s[y])%mod;//求每条边的贡献，注意这里是 n 而不是 m
	return ans%mod;}//这里把所有子树答案加起来后再取模可以省一点点时间
I qans(){
	I ans=1ll*dfs(a[1])*(n-2)%mod;//注意要乘上 n-2
	fo(i,1,m)is[a[i]]=0;VT.dest();//拆除虚树
	return ans;}
I main(){
	scanf("%d",&n);fo(i,1,n)scanf("%d",a+i);
	fo(i,2,2e5){if(!np[i])pr[++pl]=i,mip[i]=i;
		for(I j=1;j<=pl&&1ll*pr[j]*i<=2e5;++j){
			mip[i*pr[j]]=pr[j];np[i*pr[j]]=1;
			if(i%pr[j]==0)break;}}//筛法，记 mip[x] 为 x 最小的质因子
	fo(i,1,n)ext(a[i],i);
	fo(i,2,n){I x,y;scanf("%d%d",&x,&y);G.conn(x,y);G.conn(y,x);}//连边。这种东西就不需要单独换行了。
	dfs1(1);dfs2(1);//树剖的两个基本操作
	I ans=0;
	fo(i,2,2e5)if(!np[i]){n=0;
		go(D,i)a[++n]=y;if(!n)continue;//这里如果没有关键点就不要建虚树了，有可能会有内存错误
		bvt();ans+=1ll*(mod+1)/2*qans()%mod;//注意末尾还要乘上 1/2
		ans%=mod;}
	printf("%d\n",ans);
	return 0;
}

```

---

还可以更快吗？答案是肯定的。

内容参考了 [这篇博客](https://return20071007.blog.uoj.ac/blog/8573)，感谢作者。

我们之前对于虚树的构建，使用了**二次排序法**，瓶颈在于 排序 + LCA。

那么使用基数排序就可以把排序的瓶颈消除。但是还有 LCA 一只 `log` 的瓶颈。

---

如何做到 $O(1)$ 强制**在线** LCA？

对于 $(x,y)$，有一个结论，假设 $dfn_x<dfn_y$。那么它们 LCA 一定是 $dfn$ 序处于 $[dfn_x+1,dfn_y]$ 这段区间之内**深度最小**的点的**父亲节点**。

证明如下：首先可以确定的是这一个流程**不会跳出**它们 LCA 的子树，而子树内非 $(x,y)$ 路径上的节点没有影响。

如果 $x$ 是 $y$ 的祖先，那么这段区间深度最小的点就是 $x$ 的某个儿子节点。

否则，它们的 LCA 一定在 $x$ 和 $y$ 的上方，而整个 DFS 流程就会先遍历 $x$ 再遍历 $y$。

而 $x$ 和 $y$ 又不在 LCA 的同一个子树内部，所以遍历完 LCA 有 $x$ 的子树之后才会遍历进有 $y$ 的子树。

此时这个流程中 LCA 的**子节点**中，子树中包含 $y$ 的**这个子节点**，就是**深度最小**的节点（之一）。

所以，LCA 就是 $[dfn_x+1,dfn_y]$ 中深度最小的节点。

然后使用一下 RMQ 维护即可。

至此我们成功地把时间复杂度优化成了 $O(n\log n+n\omega(n))$，瓶颈在于 RMQ。

```cpp
#pragma GCC optimize(3,"Ofast","inline")//CF 开 O3
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i=(a);i<=(b);++i)
#define fd(i,a,b) for(I i=(a);i>=(b);--i)
using namespace std;typedef int I;typedef void V;
const I N=2e5+10,mod=998244353;
struct graph{
	I*ey,*nx,hd[N],*ez,ec=0;
	graph(I m){if(m)ey=new int[m],ez=new int[m],nx=new int[m];ec=0;}
	V conn(I x,I y,I z=0){ey[++ec]=y;nx[ec]=hd[x];hd[x]=ec;ez[ec]=z;}
	V dest(){delete ey;delete nx;delete ez;ec=0;}
}G(N<<1),VT(N<<1),D(N*7);
#define go(T,x) for(I _i=(T).hd[(x)],y,z;y=(T).ey[_i],z=(T).ez[_i],_i;_i=(T).nx[_i])
I mip[N],pr[N],a[N<<1],n,pl,m;
bool np[N];
V ext(I x,I y){pl=0;
	for(;x^1;x/=mip[x])pr[++pl]=mip[x];
	sort(pr+1,pr+pl+1);pl=unique(pr+1,pr+pl+1)-pr-1;
	fo(i,1,pl)D.conn(pr[i],y);}
I d[N],dfn[N],s[N],clk,hs[N],f[19][N],LG[N],fa[N];
I pmx(I a,I b){return d[a]<d[b]?a:b;}
I rmq(I l,I r){I k=LG[r-l+1];
	return pmx(f[k][l],f[k][r-(1<<k)+1]);}
V dfs1(I x,I fa=0){d[x]=d[fa]+1;::fa[x]=fa;f[0][dfn[x]=++clk]=x;
	go(G,x)if(y!=fa)dfs1(y,x);}
I lca(I x,I y){if(dfn[x]>dfn[y])swap(x,y);
	return x==y?x:fa[rmq(dfn[x]+1,dfn[y])];}//O(1) LCA
bool is[N];
I b[N<<1];
V Rsort(I*a,I n){
	if(n<=1e3)sort(a+1,a+n+1,[=](I a,I b){return dfn[a]<dfn[b];});
    //如果 1e3 的时候还不如 sort 更快
	static I c[256]={};
	fo(t,0,2){
		fo(i,1,n)++c[(dfn[a[i]]>>(t<<3))&255];
		fo(i,1,255)c[i]+=c[i-1];
		fd(i,n,1)b[c[(dfn[a[i]]>>(t<<3))&255]--]=a[i];
		fd(i,n,1)a[i]=b[i];
		fd(i,255,0)c[i]=0;}}
V bvt(){m=n;Rsort(a,n);
	fo(i,(is[a[1]]=1,2),n)is[a[i]]=1,a[++m]=lca(a[i-1],a[i]);
	Rsort(a,m);m=unique(a+1,a+m+1)-a-1;
	VT=(m<<1);fo(i,1,m)VT.hd[a[i]]=0;I lc=1;
	fo(i,2,m)lc=lca(a[i-1],a[i]),VT.conn(lc,a[i],d[a[i]]-d[lc]);}
I dfs(I x){long long ans=0;s[x]=is[x];
	go(VT,x)ans+=dfs(y),s[x]+=s[y];
	go(VT,x)ans+=(1ll*z*s[y])%mod*(n-s[y])%mod;
	return ans%mod;}
I qans(){
	I ans=1ll*dfs(a[1])*(n-2)%mod;
	fo(i,1,m)is[a[i]]=0;VT.dest();
	return ans;}
I main(){LG[0]=-1;
	scanf("%d",&n);fo(i,1,n)scanf("%d",a+i),LG[i]=LG[i>>1]+1;
	fo(i,2,2e5){if(!np[i])pr[++pl]=i,mip[i]=i;
		for(I j=1;j<=pl&&1ll*pr[j]*i<=2e5;++j){
			mip[i*pr[j]]=pr[j];np[i*pr[j]]=1;
			if(i%pr[j]==0)break;}}
	fo(i,1,n)ext(a[i],i);
	fo(i,2,n){I x,y;scanf("%d%d",&x,&y);G.conn(x,y);G.conn(y,x);}
	dfs1(1);
	fo(k,1,18)for(I i=1;i-1+(1<<k)<=n;++i)f[k][i]=pmx(f[k-1][i],f[k-1][i+(1<<(k-1))]);//预处理 RMQ
	I ans=0;
	fo(i,2,2e5)if(!np[i]){n=0;
		go(D,i)a[++n]=y;if(!n)continue;
		bvt();ans+=1ll*(mod+1)/2*qans()%mod;
		ans%=mod;}
	printf("%d\n",ans);
	return 0;
}

```

----

还能不能更快？答案是肯定的。可以使用 $O(n)-O(1)$ RMQ 算法来进一步提升效率。

希望大家能够不断追求更快的本题算法！

---

## 作者：创世游戏科技 (赞：1)

# Electrical Efficiency

## 题目大意

树上 $n$ 个点，每个点有权值 $a_i$ ，求出所有质因子相同的任意三个点联通块边数距离之和。

## 思路解析

因为每个质因子无论出现多少次，我们都把它们看做一次，所以我们认为它们对答案的**贡献是独立**的。

那么我们现在仅考虑一种质因子。

因为它是联通块，$x,y,z$ 可以任意交换，所以三点之间的边的数量就是任意两点边数之和再除以二。

$$f(x,y,z)=\frac{d(x,y)+d(x,z)+d(y,z)}{2}$$

我们现在需要考虑一条边对于 $f(x,y,z)$ 的贡献，因为一个联通块至少三个点，所以**不能是这两个端点之一**。

它所包含的点可以是除了端点之外的任意一个合法的点，共有 $k-2$ 种选择。$k$ 是**包含同种质因子的点**的个数。

这些联通块每个都会包含这条边，边 $(x,y)$ 对每个的贡献是 $\frac{d(x,y)}{2}$，所以我们这条边对答案的贡献是  $\frac{(k-2)d(x,y)}{2}$。

所以这种质因子对答案贡献是 $\frac{(k-2)}{2}\sum{d(x,y)}$。

我们需要求出每个点两两之间的距离，这个可以通过树形 DP 实现。

假设我们已经求出了一个点子树内**包含同种质因子的点**有 $p$ 个，那么这条边的贡献对两两之间距离和的贡献就是 $p(k-p)$，原因是子树内每个**包含同种质因子的点**必须经过这条边才能到子树外的点。容易证明这样做是不重不漏。

这时候我们发现如果质因子太大的话可以最多需要遍历 $n$ 遍树，但是如果用虚树维护，一个点就最多被访问 $n\log{n}$ 次。

可以证明一个数的质因子不超过 $\log{n}$ 个，所以最多被访问 $n\log{n}$ 遍。

就可以使用虚树维护每种质因子。

但这种方法比较复杂，考虑一种比较简单的树上启发式合并的简单做法。

每次我们把小的子节点向大的节点合并，如果发现根节点较小就交换，这样保证了最多合并 $n\log{n}$ 次。

我们记录每个子节点的质因数，和这个质因子一共出现的次数，那么它的系数就是 $\frac{k-2}{2}$。

我们合并时每次减掉旧的贡献，加上新的贡献即可。

注意一个节点的初始贡献是只包含这个点的情况。

精细化实现复杂度为 $O(n\log{n})$。可以通过。

## 参考实现


```
#include<bits/extc++.h>
using namespace __gnu_pbds;
#define int long long
using namespace std;
const int MAXN=3e5+10;
const int mod=998244353;
gp_hash_table<int,int>mp[MAXN];
int n,colcnt[MAXN],res[MAXN],ans=0,inv;
vector<int>col[MAXN];
struct node{
    int nxt,to;
}e[MAXN*4];
int head[MAXN],tot=0;
void add(int x,int y){
    e[++tot].nxt=head[x];
    e[tot].to=y;
    head[x]=tot;
}
int qpow(int base,int ret){
    int ans=1;
    while(ret){
        if(ret&1)ans=ans*base%mod;
        base=base*base%mod;
        ret/=2;
    }
    return ans;
}
void dfs(int x,int fa){
    for(int i=head[x];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa)continue;
        dfs(v,x);
        if(mp[x].size()<mp[v].size()){
            swap(mp[x],mp[v]);swap(res[x],res[v]);
        }
        for(auto i:mp[v]){
            res[x]-=(colcnt[i.first]-2)*mp[x][i.first]%mod*(colcnt[i.first]-mp[x][i.first])%mod*inv%mod;
            res[x]=(res[x]+mod)%mod;
            mp[x][i.first]+=i.second;
            res[x]+=(colcnt[i.first]-2)*mp[x][i.first]%mod*(colcnt[i.first]-mp[x][i.first])%mod*inv%mod;
            res[x]=(res[x]+mod)%mod;
        }
    }
    ans+=res[x];
    ans%=mod;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n;inv=qpow(2,mod-2);
    for(int k=1;k<=n;k++){
        int x;cin>>x;
        for(int i=2;i<=sqrt(x);i++){
            if(x%i==0){
                col[k].emplace_back(i);
                colcnt[i]++;
            }
            while(x%i==0)x/=i;
        }
        if(x!=1)col[k].emplace_back(x),colcnt[x]++;
    }
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;add(x,y);add(y,x);
    }
    for(int i=1;i<=n;i++){
        for(auto j:col[i]){
            mp[i][j]++;
            res[i]+=(colcnt[j]-2)*(colcnt[j]-1)%mod*inv%mod;
            res[i]%=mod;
        }
    }
    dfs(1,0);
    cout<<ans%mod;
    return 0;
}

```

---

## 作者：_YangZJ_ (赞：1)

一个跟大家不同的拆贡献做法，不需要用虚树。复杂度也是 $O(n\omega(V)\log n)$ 的。

路径长度和我们一般可以把贡献拆到每一条边来计算。本题我们也这么来考虑，考虑每一条边，记删去这条边后形成的两个连通块分别为 $S, T$。首先这条边在路径并上说明 $S$ 集合中有 $1$ 或 $2$ 个端点，我们枚举在 $S$ 集合中的端点数量，再来考虑 $\omega(\gcd)$ 的贡献。先只考虑 $1$ 个端点的，$2$ 个的是同理。枚举 $g=\gcd $ ：
$$
\sum_{g=1}^V\omega(g)\sum_{i\in S;j,k\in T}[\gcd(a_i,a_j,a_k)=g]
$$

$$
=\sum_{g=1}^V\omega(g)\sum_{i\in S;j,k\in T}[\gcd(\frac{a_i}{g},\frac{a_j}{g},\frac{a_k}{g})=1]
$$

记后面那个 $\gcd=G$，套用莫比乌斯反演的式子：
$$
=\sum_{g=1}^V\omega(g)\sum_{i\in S;j,k\in T}\sum_{d|G}([dg|a_i]\cdot [dg|a_j]\cdot [dg|a_k])
$$

$$
=\sum_{g=1}^V\omega(g)\sum_{d=1}^V\mu(d)\sum_{i\in S}[dg|a_i]\frac{\sum\limits_{j\in T}[dg|a_j](\sum\limits_{j\in T}[dg|a_j]-1)}{2}
$$

枚举 $gd$ ：
$$
=\sum_{x=1}^V f(x)\cdot C_S(x)\frac{C_T(x)(C_T(x) -1)}{2}
$$
其中 $C_S(x)$ 表示 $S$ 集合中有多少点权是 $x$ 的倍数，$C_T$ 同理；$f=\omega*\mu$，$f$ 可以直接预处理出来。

考虑暴力维护上面这个式子，假设 $S$ 集合为当前子树，那么只需要维护出一个子树内元素的桶即可，这一步可以用 $\text{dsu}$ 启发式合并来处理，每次加入一个点被更改的位置是其所有的约数，因此加入一个点的复杂度是 $O(d(a_i))$。

那么现在总复杂度就是 $O(nd(V)\log n)$。

写完后发现了一个有意思的事实，考虑我们那个 $f$ 函数，写完之后发现：
$$
f(x)=[x\in prime]
$$
也就是只有在质数处点值为 $1$，否则为 $0$，因此对于一个 $a_i$ 其 $f$ 非 $0$ 的约数只有 $\omega(a_i)$ 个，因此总复杂度是 $O(n\omega(V)\log n)$。

[submission](https://codeforces.com/contest/1725/submission/228650457)。

---

## 作者：良心WA题人 (赞：1)

一种题解里好像还没有的暴力做法。

考虑每一种质因子，对于包含该质因子的所有点中选出三个点的 $f(x,y,z)$ 的和就是原题的数。

对于计算 $f(x,y,z)$，我们把贡献拆到每条边上，令含当前质因子数个数为 $m$，子树内含当前质因子数个数为 $k$，则贡献为 $k\times\dfrac{(m-k)\times (m-k-1)}{2}+\dfrac{k\times(k-1)}{2}\times(m-k)$。

可是质因子个数太多了，我们考虑根号分治。对于 $\le \sqrt{V}$ 的质数，每一种都暴力做上面的计数即可。

而对于 $>\sqrt{V}$ 的质数，每个数都只会有一个，所以考虑再次按照出现个数根号分治。对于出现次数 $>B$ 的质数，同样进行暴力跑。出现次数 $\le B$ 的质数，$n^2$ 枚举每一对点对，令两点距离为 $g(x,y)$，因为 $f(x,y,z)=\dfrac{g(x,y)+g(x,z)+g(y,z)}{2}$，所以每一对 $x,y$ 的贡献为 $\dfrac{g(x,y)\times (m-2)}{2}$。

时间复杂度 $O((\sqrt{V}+\dfrac{n}{B}+B\times\log n)\times n)$，可以用 $O(1)$ lca 去掉 $\log$。不过因为常数很小，所以带 $\log$ 也完全足矣通过此题。块长都没调，直接用的 $B=400$ 就最慢点 2390ms 过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4,P=998244353;
vector<int>g[NN],p[NN];
int a[NN],cnt[NN][604],all[604],primes[604],m,ans,up[NN][24],d[NN];
int lca(int u,int v)
{
	if(d[u]<d[v])
		swap(u,v);
	int res=0;
	for(int i=20;~i;i--)
		if(d[up[u][i]]>=d[v])
		{
			res+=1<<i;
			u=up[u][i];
		}
	if(u==v)
		return res;
	for(int i=20;~i;i--)
		if(up[u][i]!=up[v][i])
		{
			res+=1<<i+1;
			u=up[u][i],v=up[v][i];
		}
	return res+2;
}
void before_lca(int u,int fa)
{
	up[u][0]=fa;
	d[u]=d[fa]+1;
	for(int i=1;i<=20;i++)
		up[u][i]=up[up[u][i-1]][i-1];
	for(auto v:g[u])
	{
		if(v==fa)
			continue;
		before_lca(v,u);
	}
}
void dfs(int u,int fa)
{
	for(int i=1;i<=m;i++)
		if(!(a[u]%primes[i]))
		{
			cnt[u][i]++;
			while(!(a[u]%primes[i]))
				a[u]/=primes[i];
		}
	for(auto v:g[u])
	{
		if(v==fa)
			continue;
		dfs(v,u);
		for(int i=1;i<=m;i++)
		{
			ans=(ans+1ll*(all[i]-cnt[v][i])*(all[i]-cnt[v][i]-1)/2%P*cnt[v][i]%P+1ll*cnt[v][i]*(cnt[v][i]-1)/2%P*(all[i]-cnt[v][i])%P)%P;
			cnt[u][i]+=cnt[v][i];
		}
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=2;i<=500;i++)
	{
		bool flag=true;
		for(int j=2;1ll*j*j<=i;j++)
			if(!(i%j))
				flag=false;
		if(flag)
			primes[++m]=i;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		int x=a[i];
		for(int j=1;j<=m;j++)
			if(!(x%primes[j]))
			{
				all[j]++;
				while(!(x%primes[j]))
					x/=primes[j];
			}
		if(x>1)
			p[x].push_back(i);
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	before_lca(1,0);
	for(int i=501;i<NN;i++)
		if(p[i].size()>=400)
		{
			primes[++m]=i;
			all[m]=p[i].size();
		}
		else
			for(int j=0;j<p[i].size();j++)
				for(int k=j+1;k<p[i].size();k++)
					ans=(ans+1ll*lca(p[i][j],p[i][k])*(p[i].size()-2)%P*((P+1)/2)%P)%P;
	dfs(1,0);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

### 思路

观察到 $f(x,y,z)=\frac{dis(x,y)+dis(y,z)+dis(x,z)}{2}$

所以答案为

$$\frac{\sum_{x<y<z} (dis(x,y)+dis(y,z)+dis(x,z)) \sum_{j\in Prime} [j\mid A_x][j\mid A_y][j\mid A_z]}{2}$$

由于每个数的质因子个数不超过 $6$ 个，用线性筛求出每个数的最小质因子，然后枚举每一个质因子，建立虚树。

枚举树上每一条边，求出边两边的点的数量为 $cnt1$ 和 $cnt2$，则这条边贡献为 $\frac{w\times cnt \times cnt2 \times (cnt+cnt2 - 2)}{2}$，复杂度为 $O(n\max\{\omega\}\log n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int, int>

using namespace std;

const int N = 2e5 + 10, mod = 998244353;
int h[N], e[N << 2], ne[N << 2], idx;
vector<int> g[N];
int vis[N], d[N], a[N], p[N][22], dep[N], L[N], R[N], tot;
vector<int> P; 

void addedge(int x, int y) {
	e[idx] = y, ne[idx] = h[x], h[x] = idx ++ ;
} 

void init(int m) {
	for (int i = 2; i <= m; i ++ ) {
		if (!vis[i]) {
			P.pb(i);
			d[i] = P.size() - 1;
		}
		for (int j = 0; i * P[j] <= m; j ++ ) {
			vis[i * P[j]] = 1;
			d[i * P[j]] = j;
			if (i % P[j] == 0) {
				break;
			}
		}
	}
}

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	L[u] = ++ tot;
	p[u][0] = fa;
	for (int j = 1; j < 20; j ++ ) p[u][j] = p[p[u][j - 1]][j - 1];
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j == fa) continue;
		dfs(j, u);
	}
	R[u] = tot;
}

int lca(int x, int y) {
	if (dep[x] > dep[y]) swap(x, y);
	for (int i = 19; i >= 0; i -- )
		if (dep[p[y][i]] >= dep[x])
			y = p[y][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; i -- )
		if (p[x][i] ^ p[y][i])
			x = p[x][i], y = p[y][i];
	return p[x][0];
}

int main() {
	init(200000);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	memset(h, -1, sizeof h);
	for (int i = 1; i < n; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y), addedge(y, x);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i ++ ) {
		int b = a[i];
		while (b > 1) {
			int id = d[b], t = P[id];
			while (b % t == 0) b /= t;
			g[id].pb(i);
		}
	}
	int ans = 0;
	for (int i = 0; i < P.size(); i ++ ) {
		if (g[i].size() < 3) continue;
		sort(g[i].begin(), g[i].end(), [](int x, int y) {
			return L[x] < L[y];
		});
		int len = g[i].size();
		for (int j = 1; j < len; j ++ )
			g[i].push_back(lca(g[i][j], g[i][j - 1]));
		sort(g[i].begin(), g[i].end(), [](int x, int y) {
			return L[x] < L[y];
		});
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
		vector<pii> H;
		for (int j = g[i].size() - 1; j >= 1; j -- ) {
			int cnt = (a[g[i][j]] % P[i] == 0);
			while (H.size() && H.back().first <= R[g[i][j]]) {
				cnt += H.back().second;
				H.pop_back();
			}
			H.pb({R[g[i][j]], cnt});
			ans = (ans + 1ll * cnt * (len - cnt) % mod * (dep[g[i][j]] - dep[lca(g[i][j], g[i][j - 1])]) % mod * (len - 2) % mod) % mod;
		}
	}
	printf("%d\n", 1ll * ans * (mod + 1) / 2 % mod);
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

观察式子来分析一下答案。

$g(x,y,z)$ 是求质数个数，就可以把每一个质数拿出来建一颗虚树。

$f(x,y,z)=\frac{dis(x,y)+dis(x,z)+dis(y,z)}{2}=\frac{n-2}{2}\sum\limits_{x<y}dis(x,y)$。

求两两点之间的距离，可以计算在虚树上每一条边的代价。

思路简单，代码不难写。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=2e5;
const int mod=998244353;
const int inv2=(mod+1)/2;
int n,a[N],prime[N],id[N],tot=0,x,y;
int b[N],c[N],ans=0,res=0,len=0,cnt=0,num[N];
int dfn[N],son[N],dep[N],top[N],siz[N],fat[N],idx=0;
bool vis[N],flag[N];
vector<int>pr[N],p[N],g[N];
void dfs1(int u,int fa){
	siz[u]=1;fat[u]=fa;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int topx){
	top[u]=topx;
	dfn[u]=++idx;
	if(!son[u])return;
	dfs2(son[u],topx);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fat[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
void add(int u,int v){
	g[u].push_back(v);
	g[v].push_back(u);
	num[u]=num[v]=0;
}
void dfs(int u,int fa){
	num[u]=flag[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dfs(v,u);
		num[u]+=num[v];
		res=(res+(1ll*(cnt-num[v])*num[v]%mod)*(dep[v]-dep[u])%mod)%mod;
	}
	flag[u]=0;
	g[u].clear();
}
signed main(){
	for(int i=2;i<=inf;i++){
		if(!vis[i]){
			prime[++tot]=i;
			id[i]=tot;
			pr[i].push_back(i);
			for(int j=i*2;j<=inf;j+=i){
				pr[j].push_back(i);
				vis[j]=1;
			}
		}
	}
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		for(int j=0;j<pr[a[i]].size();j++){
			p[id[pr[a[i]][j]]].push_back(i);
		}
	}
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&x,&y);
		add(x,y);
	}
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;i++)g[i].clear();
	for(int i=1;i<=tot;i++){
		if(p[i].size()<3)continue;
		cnt=0,len=0;
		for(int j=0;j<p[i].size();j++)b[++cnt]=p[i][j];
		for(int j=1;j<=cnt;j++)flag[b[j]]=1;
		sort(b+1,b+1+cnt,cmp);
		c[++len]=1;
		for(int j=1;j<cnt;j++){
			c[++len]=b[j];
			c[++len]=lca(b[j],b[j+1]);
		}
		c[++len]=b[cnt];
		sort(c+1,c+1+len,cmp);
		len=unique(c+1,c+1+len)-c-1;
		for(int j=1;j<len;j++){
			add(lca(c[j],c[j+1]),c[j+1]);
		}
		res=0;
		dfs(1,0);
		res=1ll*(1ll*res*(cnt-2)%mod)*inv2%mod;
		ans=(ans+res)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：happybob (赞：0)

一眼题。

注意到值域不大且每个数的质因数个数不大，直接枚举所有质数，对所有这个质数的倍数的那些点建虚树，对每条边算子树内和子树外的贡献即可。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 2e5 + 5;
constexpr ll MOD = 998244353ll;

int n, idx;
ll ans;
array<int, N> a, dfn,dep,sum;
array<vector<int>, N> G;
array<vector<pair<int,int>>,N> NG;
array<vector<int>, N> ve, pos;
array<array<int,20>,N> faf;

array<bool, N> vis,vta;
vector<int> primes;

int nc;
void Init()
{
	for(int i=2;i<N;i++)
	{
		if(!vis[i]) primes.emplace_back(i);
		for(auto&j:primes)
		{
			if(1ll*i*j>=N) break;
			vis[i*j]=1;
			if(i%j==0) break;
		}
	}
}

void dfs(int u, int fa)
{
	dfn[u] = ++idx;
	for (auto &j : G[u])
	{
		if (j == fa) continue;
		dfs(j, u);
	}
}

void dfs2(int u,int fa)
{
	faf[u][0]=fa;
	for(int j=1;j<20;j++) faf[u][j]=faf[faf[u][j-1]][j-1];
	dep[u]=dep[fa]+1;
	for(auto&j:G[u])
	{
		if(j==fa) continue;
		dfs2(j, u);
	}
}

inline int LCA(int u,int v)
{
	if(u==v) return u;
	if(dep[u]<dep[v]) swap(u,v);
	int c=0,k=dep[u]-dep[v];
	while(k)
	{
		if(k&1) u=faf[u][c];
		k>>=1;
		c++; 
	}
	if(u==v) return u;
	for(int i=19;i>=0;i--)
	{
		if(faf[u][i]^faf[v][i]) u=faf[u][i],v=faf[v][i];
	}
	return faf[u][0];
}

inline int getdis(int u,int v)
{
	return dep[u]+dep[v]-2*dep[LCA(u,v)];
}

struct Edge
{
	int u,v,w;
	Edge()=default;
	Edge(int u,int v,int w):u(u),v(v),w(w){}
};

void dfs3(int u)
{
	sum[u]=vta[u];
	for(auto&j:NG[u])
	{
		dfs3(j.first);
		sum[u]+=sum[j.first];
		int L=nc-sum[j.first],R=sum[j.first];
		if(L&&R)
		{
			ans=ans+1ll*L*(L-1)/2%MOD*R%MOD*j.second%MOD;
			ans=ans+1ll*R*(R-1)/2%MOD*L%MOD*j.second%MOD;
			ans%=MOD;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	Init();
	for (int i = 1; i < N; i++)
	{
		if(vis[i]) continue;
 		for (int j = i; j < N; j += i) ve[j].emplace_back(i);
	}
	cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		for (auto &j : ve[a[i]]) pos[j].emplace_back(i);
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v), G[v].emplace_back(u);
	}
	dfs(1, 0);
	dfs2(1, 0);
	for (int i = 2; i < N; i++)
	{
		if (vis[i]) continue;
		vector<int> vt(pos[i]);
		if(vt.size()<=2) continue;
		nc=vt.size();
		for(auto&j:vt) vta[j]=1;
		vt.emplace_back(1);
		sort(vt.begin(),vt.end(),[&](const int& x,const int&y){return dfn[x]<dfn[y];});
		vector<Edge> eg;
		int rsz=vt.size();
		for(int j=0;j+1<rsz;j++)
		{
			vt.emplace_back(LCA(vt[j],vt[j+1]));
		}
		sort(vt.begin(),vt.end(),[&](const int& x,const int&y){return dfn[x]<dfn[y];});
		vt.erase(unique(vt.begin(),vt.end()),vt.end());
		rsz=vt.size();
		for(int j=0;j+1<rsz;j++)
		{
			int L=LCA(vt[j],vt[j+1]);
			eg.emplace_back(L,vt[j+1],getdis(L,vt[j+1]));
			NG[L].emplace_back(vt[j+1],getdis(L,vt[j+1]));
			sum[L]=0,sum[vt[j+1]]=0;
		}
		dfs3(1);
		for(auto&j:vt) vta[j]=0;
		for(auto&x:eg) NG[x.u].clear(),NG[x.u].shrink_to_fit(),sum[x.u]=sum[x.v]=0;
		//cout<<"!!!: "<<i<<" "<<ans<<"\n";
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：gyyyyx (赞：0)

可以当成是[这题](https://www.luogu.com.cn/problem/AT_abc359_g)的加强版

观察到 $f$ 和 $g$ 函数一个图论有关，一个和数论有关，可见这俩函数八竿子打不着。

这里有两种处理思路：

1. 注意到 $f$ 函数与树边相关，考虑对于每一条边计算贡献

2. 注意到对于一个质数 $p$，若 $p\mid a_x,p\mid a_y,p\mid a_z$，则 $p\mid \gcd(a_x,a_y,a_z)$，考虑对于每一个质数计算贡献

如果是第一种思路可以用点分治来做，由于本人用的不是这个方法，就不赘述了。

对于第二种思路，对于一个质数，我们将所有点权能被此质数整除的点设为一组，**一个点可以同时存在于多个组内**。

显然一个组内任意选三个点都能对答案产生 $f(x,y,z)$ 的贡献。

易证这样每组的点的个数之和是 $O(n\omega(V))$。

这样问题转化为了：对于一棵树，给出多组询问，每组询问给出点集 $V$，求 $\sum\limits_{x,y,z\in V,x<y<z} f(x,y,z)$ 的值，**点集大小之和为 $O(n\omega(V))$ 级别**。

想到虚树。

对于每组点建虚树，考虑每一条边的贡献。

对于一条边 $(u,v)$，其能对答案产生的贡献为虚树上两两间路径包含此边的**有序**三元组的个数**乘以这条边的长度**。

乘以长度是由于虚树上的边相当于原树上的多条边，而**这些边都能对答案产生相同的贡献**。

不妨假定一个根节点并假设 $u$ 为 $v$ 的父亲。

我们称属于给定点集的点为关键点，令 $sum$ 为 $v$ 节点子树内关键点的数量，$tot$ 为点集大小。

则三元组个数为为 $sum(sum-1)(tot-sum)/2+sum(tot-sum)(tot-sum-1)/2$（选一个子树内的点和两个子树外的点，或选两个子树内的点和一个子树外的点）。

整理可得：$sum(tot-sum)(tot-2)/2$。

这里使用本人更熟悉的单调栈建虚树，倍增求 LCA。

由于懒我直接写了质因数分解来分组，如果您不懒惰可以选择线性筛，保证分组的时间复杂度为 $O(n\log n)$。

时间复杂度 $O(n\omega(V)\log n)$，如果用 RMQ $O(1)$ 求 LCA 可以优化到 $O(n\log n+n\omega(V))$。

最后不要忘记开 `long long` 和清空虚树。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mod 998244353
#define N 200005
using namespace std;
int n;bool yp[N];
vector <int> bl[N],p;
struct Edge{
	int nxt,to;
	Edge(int a=0,int b=0):nxt(a),to(b){}
} e[N<<1];
int head[N],cnt;
int dep[N],fa[N][20],dfn[N],cur;
int st[N],top,tot;
queue <int> Q;
bool vis[N];
LL ans;
inline void AddEdge(int x,int y){
	e[++cnt]=Edge(head[x],y);head[x]=cnt;
}
void DFS(int u,int f){
	dep[u]=dep[fa[u][0]=f]+1;dfn[u]=++cur;
	for(int i(1);fa[u][i-1];++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i(head[u]);i;i=e[i].nxt){
		int v(e[i].to);
		if(v^f) DFS(v,u);
	}
}
inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i(18);~i;--i)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y) return x;
	for(int i(18);~i;--i)
		if(fa[x][i]^fa[y][i])
			x=fa[x][i],
			y=fa[y][i];
	return fa[x][0];
}
inline bool cmp(int a,int b){return dfn[a]<dfn[b];}
inline void Push(int x){st[++top]=x;Q.push(x);}
LL DFS2(int u,LL dis){
	LL sum(vis[u]);
	for(int i(head[u]);i;i=e[i].nxt)
		sum+=DFS2(e[i].to,dep[e[i].to]-dep[u]);
	(ans+=sum*(tot-sum)%mod*(tot-2)%mod*dis%mod)%=mod;
	return sum;
}
int main(){
	scanf("%d",&n);
	for(int i(1);i<=n;++i){
		int val;scanf("%d",&val);
		for(int j(2);j*j<=val;++j)
			if(!(val%j)){
				bl[j].push_back(i);
				if(!yp[j]) yp[j]=1,p.push_back(j);
				while(!(val%j)) val/=j;
			}
		if(val^1){
			bl[val].push_back(i);
			if(!yp[val]) yp[val]=1,p.push_back(val);
		}
	}
	for(int i(1);i<n;++i){
		int u,v;scanf("%d%d",&u,&v);
		AddEdge(u,v);AddEdge(v,u);
	}
	DFS(1,0);
	fill(head+1,head+1+n,0);cnt=0;
	for(int t(0);t<p.size();++t){
		int c(p[t]);
		if(bl[c].size()<3) continue;
		sort(bl[c].begin(),bl[c].end(),cmp);Push(1);
		for(int i(bl[c][0]==1);i<bl[c].size();++i){
			int x(bl[c][i]),lca(LCA(st[top],x));
			if(lca^st[top]){
				while(top>1&&dfn[lca]<dfn[st[top-1]])
					AddEdge(st[top-1],st[top]),--top;
				AddEdge(lca,st[top]);--top;
				if(lca^st[top]) Push(lca);
			}
			Push(x);vis[x]=1;
		}
		while(--top) AddEdge(st[top],st[top+1]);
		tot=bl[c].size();DFS2(1,0);
		for(int i(0);i<bl[c].size();++i) vis[bl[c][i]]=0;
		while(!Q.empty()) head[Q.front()]=0,Q.pop();cnt=0;
	}
	printf("%lld\n",(ans*499122177%mod+mod)%mod);
	return 0;
}
```

---

