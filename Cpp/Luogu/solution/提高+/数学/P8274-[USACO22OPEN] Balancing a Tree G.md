# [USACO22OPEN] Balancing a Tree G

## 题目背景

感谢 @tiger2005 配置 SPJ。

## 题目描述

Farmer John 对不同奶牛品种的进化进行了广泛的研究。所得到的结果形成一棵 $N$（$2\le N\le 10^5$）个结点的有根树，编号为 $1\ldots N$，每个结点对应一个奶牛品种。对于每一个 $i\in [2,N]$，结点 $i$ 的父结点是结点 $p_i$（$1\le p_i< i$），意味着品种 $i$ 是由品种 $p_i$ 进化而来的。称结点 $j$ 为结点 $i$ 的祖先，如果 $j=p_i$ 或者 $j$ 是 $p_i$ 的祖先。

树中的结点 $i$ 所关联的品种具有整数 $s_i$ 数量的斑点。定义树的「不平衡度」为所有结点对 $(i,j)$ 中 $|s_i-s_j|$ 的最大值，其中 $j$ 是 $i$ 的祖先。

Farmer John 不知道每个品种的 $s_i$ 的确切数值，但他知道这些值的下界和上界。你的任务是为每个结点分配一个整数值 $s_i \in [l_i,r_i]$（$0\le l_i\le r_i\le 10^9$），以最小化树的不平衡度。

## 说明/提示

【样例解释 1】

对于第一个子测试用例，最小不平衡度为 $3$。一种达到不平衡度 $3$ 的方式是令 $[s_1,s_2,s_3]=[4,1,7]$。

【样例解释 2】

这个测试用例除了 $B$ 的值之外与第一个测试用例完全相同。另一种达到不平衡度 $3$ 的方式是令 $[s_1,s_2,s_3]=[3,1,6]$。

【数据范围】

- 测试点 3-4 对于所有的 $i$ 满足 $l_i=r_i$。
- 测试点 5-6 对于所有的 $i$ 满足 $p_i=i-1$。
- 测试点 7-16 没有额外限制。

在每一部分子任务中，前一半的测试点满足 $B=0$，后一半测试点满足 $B=1$。


## 样例 #1

### 输入

```
3 0
3
1 1
0 100
1 1
6 7
5
1 2 3 4
6 6
1 6
1 6
1 6
5 5
3
1 1
0 10
0 1
9 10```

### 输出

```
3
1
4
```

## 样例 #2

### 输入

```
3 1
3
1 1
0 100
1 1
6 7
5
1 2 3 4
6 6
1 6
1 6
1 6
5 5
3
1 1
0 10
0 1
9 10```

### 输出

```
3
3 1 6
1
6 5 5 5 5
4
5 1 9```

# 题解

## 作者：yaoxi (赞：6)

[或许会更好的阅读体验](https://yaoxi-std.github.io/2022/03/27/sol-p8274/)

### 题面

[题目链接](https://www.luogu.com.cn/problem/P8274)

### 解法

~~同届的巨佬们已经都通关了 USACO，只有我还在做 Gold 组的蓝题~~

可以发现确定了 $s_1$ 的值以后就知道了其他的所有 $s$，构造方法如下：

$$
s_i = 
\begin{cases}
r_i ,& r_i < s_1 \\
s_1 ,& l_i \le s_1 \le r_i \\
l_i ,& s_1 < l_i \\
\end{cases}
$$

让所有 $s_i$ 都尽量靠近 $s_1$ 显然使得 $Ans$ 最小。

而此时的 $Ans$ 也很容易一遍 $dfs$ 进行 $O(n)$ 的计算，但是复杂度 $n \times (r_1 - l_1)$。

思考 $s_1$ 对答案的贡献，显然就是 $\max(0, \max(l_i) - s_1, s_1 - \min(r_i))$，可以预处理出 $l_i$ 和 $r_i$ 的最大值 $O(1)$ 计算。

但是这不是最终的答案，有可能有 $v$ 的祖先 $u$ 使得 $r_u < s_1 < l_v$（反之同理，即 $r_v < s_1 < l_u$）。而此时，由于要让所有 $s_i$ 靠近 $s_1$，则 $s_u$ 的取值一定为 $r_u$，$s_v$ 的取值一定为 $l_v$，对答案的贡献就成了 $l_v - r_u$。

而如果 $s_u$ 和 $s_v$ 在 $s_1$ 的同侧，那么 $|s_u - s_v|$ 的贡献就一定小于 $s_1$ 对答案的贡献，这部分可以不用考虑。于是得出重要结论：**非根节点和其非根节点的祖先对答案的贡献是固定的**。

因此，不难想到可以一遍 $dfs$ 就处理出 $max(l_v - r_u)$，在枚举 $s_1$ 的时候可以 $O(1)$ 加入贡献。于是复杂度变为 $O(r_1 - l_1)$。虽然还是无法通过，但是有了不少的优化空间。

由于一部分答案的贡献是固定的，所以我们只考虑另一部分 $\max(0, \max(l_i) - s_1, s_1 - \min(r_i))$。那么显然 $s_1 = \frac{\max(l_i) - \min(r_i)}{2}$ 是最优的。

于是这题就结束了，时间复杂度 $O(n)$，为一遍 $dfs$ 的复杂度。

### AC代码

```cpp
/**
 * @file:           T3.cpp
 * @author:         yaoxi-std
 * @url:            
*/
// #pragma GCC optimize ("O2")
// #pragma GCC optimize ("Ofast", "inline", "-ffast-math")
// #pragma GCC target ("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
#define resetIO(x) \
    freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout)
#define debug(fmt, ...) \
    fprintf(stderr, "[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
template <class _Tp>
inline _Tp& read(_Tp& x) {
    bool sign = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) sign |= (ch == '-');
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar((x % 10) ^ 48);
}
bool m_be;
using ll = long long;
const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m, tp, fa[MAXN], lp[MAXN], rp[MAXN], ans[MAXN];
vector<int> g[MAXN];
inline void chkmin(int& x, int y) { (x > y) && (x = y); }
inline void chkmax(int& x, int y) { (x < y) && (x = y); }
int dfs(int u, int mxl, int mnr) {
    int ret = max({0, lp[u] - mnr, mxl - rp[u]});
    chkmax(mxl, lp[u]), chkmin(mnr, rp[u]);
    for (auto v : g[u]) chkmax(ret, dfs(v, mxl, mnr));
    return ret;
}
bool m_ed;
signed main() {
    // debug("Mem %.5lfMB.", fabs(&m_ed - &m_be) / 1048576);
    int cas; read(cas), read(tp);
    while (cas--) {
        read(n), m = 0;
        for (int i = 1; i <= n; ++i) g[i].clear();
        for (int i = 2; i <= n; ++i) read(fa[i]), g[fa[i]].push_back(i);
        for (int i = 1; i <= n; ++i) read(lp[i]), read(rp[i]);
        int mxl = 0, mnr = INF;
        for (int i = 1; i <= n; ++i)
            chkmax(mxl, lp[i]), chkmin(mnr, rp[i]);
        int mn = dfs(1, 0, INF), ansp = 0, answ = INF;
        for (int i = (mxl + mnr) / 2; i <= (mxl + mnr + 1) / 2; ++i) {
            int curw = mn;
            if (i < mxl) chkmax(curw, mxl - i);
            if (i > mnr) chkmax(curw, i - mnr);
            if (curw < answ) answ = curw, ansp = i;
        }
        write(answ), putchar('\n');
        if (tp) {
            for (int i = 1; i <= n; ++i) {
                if (lp[i] <= ansp && ansp <= rp[i])
                    ans[i] = ansp;
                else if (ansp < lp[i])
                    ans[i] = lp[i];
                else if (rp[i] < ansp)
                    ans[i] = rp[i];
                write(ans[i]), putchar(" \n"[i == n]);
            }
        }
    }
    return 0;
}
```

---

## 作者：_LPF_ (赞：4)

[Balancing a Tree G](https://www.luogu.com.cn/problem/P8274)

> 每个点有权值范围，要求你钦定每个点的权值。
>
> 满足，全局的 $(i,j)$（其中 $i$ 是 $j$ 的祖先）的 $|a_i-a_j|$ 的最大值最小。

官方题解的做法很妙妙，再看这个解法感觉暴力多了。

先一手二分答案，设为 $\lim$。

然后想一个 naive 的贪心，考虑直接自底向上推，每次向上限制范围 $|l-\lim,r+\lim|$，每次求交，后再向上推。

但是，有可能当前值是由某一次的 $l-\lim$ 扩展来的，此时再次 $-\lim$ 扩展就出现了值域被错误的扩大的问题。

考虑这种情况出现的原因，是因为某个祖先和子孙的值域相差超过 $\lim$。

目的很明确，可以直接先从上往下收缩一次，把值域控制在较小的差中，再从下往上收缩一次即可。

输出方案也是类似的，在可选范围内任意钦定即可。

实现起来有一些细节。

```cpp
const int N = 1e5 + 10;
const int inf = 1e9;
int n, opt, lv[N], rv[N];
int cnt, head[N];
struct Edge {int nxt, v;} e[N];

void clear() {
	cnt = 0;
	rep(i, 1, n) head[i] = 0;
}

bool flag;
int lc[N], rc[N], lim;

void dfs1(int u, int L, int R) {
	if(L > R) {flag = false; return;}
	if(L > rc[u] || R < lc[u]) {flag = false; return;}
	lc[u] = max(L, lc[u]);
	rc[u] = min(R, rc[u]);
	Ede(i, u) {
		int v = e[i].v;
		dfs1(v, max(lc[u] - lim, L), min(rc[u] + lim, R));
		if(! flag) return;
	}
}

bool res[N];

void dfs2(int u) {
	int lt = 0;
	int rt = inf;
	Ede(i, u) {
		int v = e[i].v;
		dfs2(v);
		if(! flag) return;
		int ln = lc[v];
		int rn = rc[v];
		if(ln > rt || rn < lt) {flag = false; return;}
		lt = max(lt, ln);
		rt = min(rt, rn);
	}
	if(lt > rt) {flag = false; return;}
	lc[u] = max(lc[u] - lim, lt);
	rc[u] = min(rc[u] + lim, rt);
	if(lc[u] > rc[u]) {flag = false; return;}
}

int ans[N];

void dfs3(int u, int L, int R) {
	ans[u] = max(lc[u], L);
	int nxtl = max(L, ans[u] - lim);
	int nxtr = min(R, ans[u] + lim);
	Ede(i, u)
		dfs3(e[i].v, nxtl, nxtr);
}

bool check(int lim_) {
	lim = lim_, flag = true;
	rep(i, 1, n) lc[i] = lv[i], rc[i] = rv[i];
	dfs1(1, 0, inf);
	if(! flag) return false;
	dfs2(1);
	return flag;
}

void work() {
	n = read(), clear();
	rep(v, 2, n) {
		int u = read();
		e[++ cnt] = (Edge) {head[u], v}, head[u] = cnt;
	}
	rep(i, 1, n) lv[i] = read(), rv[i] = read();

	int l = 0, r = inf;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid; else l = mid + 1;
	}
	printf("%d\n", l);

	if(opt) {
		check(l); assert(flag);
		rep(i, 1, n)
			lc[i] = max(lc[i], lv[i]), 
			rc[i] = min(rc[i], rv[i]);

		ans[1] = lc[1];
		dfs3(1, ans[1] - lim, ans[1] + lim);
		rep(i, 1, n) printf("%d ", ans[i]);
		puts("");
	}
}

int main() {int t = read(); opt = read(); while(t --) work(); return 0;}
```

---

## 作者：Little09 (赞：4)

神仙题。

我们探究一下 $ans$ 的下界。当然有个前提 $ans\ge 0$。

- **如果节点 $x$ 是 $y$ 的祖先，那么显然 $ans\ge l_x-r_y$，$ans\ge l_y-r_x$。**

如果是链就已经做完了，$ans$ 的下界是能取到的，让每个点都在 $[r_{min},l_{max}]$ 就行了。

但是树的答案是错的。仔细想想，同一个点不能有多种取值，因此没有祖先关系的点之间也有限制：

- **对于任意 $x,y$，满足 $ans\ge \frac{l_x-r_y}{2}$。考虑 $x\to 1\to y$ 的路径就行了，当 $1$ 的取值在 $l_x$ 和 $r_y$ 的正中间取到等号。**

这个时候看起来 $ans$ 比较正确了，交一下 $B=0$ 发现它过了。因此 $ans$ 的下界我们找到了，只要能构造方案可以说明 $ans$ 是最小值了。

官方题解给出的构造方案：令 $mid=\lfloor\dfrac{r_{min}+l_{max}}{2}\rfloor$，那么每个点的答案 $s_i=\max(\min(mid,r_i),l_i)$，直白的说就是如果 $mid$ 在 $[l_i,r_i]$ 内就取 $mid$，否则取接近 $mid$ 的端点。

证明这个方案的合法性。考虑每一对存在祖先关系的点对 $(x,y)$：

- 若 $s_x\le mid,s_y\le mid$，那么 $|s_x-s_y|\le mid-r_{min}\le \lceil\dfrac{l_{max}-r_{min}}{2}\rceil\le ans$。
- 若 $s_x\ge mid,s_y\ge mid$，同理。
- 若 $s_x\le mid,s_y\ge mid$，说明 $s_x=r_x,s_y=l_y$，所以 $|s_x-s_y|=l_y-r_x\le ans$。

所以这个构造的方案是正确的。因此我们找到了 $ans$ 的最小值。

代码难度远低于思维难度。

```cpp
void work()
{
	n=read();
	for (int i=2;i<=n;i++) fa[i]=read();
	int minr=inf,maxl=0,ans=0;
	for (int i=1;i<=n;i++)
	{
		L[i]=read(),R[i]=read();
		minr=min(R[i],minr);
		maxl=max(L[i],maxl);
		if (fa[i]!=0)
		{
			a[i][0]=max(a[fa[i]][0],L[i]);
			a[i][1]=min(a[fa[i]][1],R[i]);
		}
		else
		{
			a[i][0]=L[i],a[i][1]=R[i];
		}
		ans=max(ans,a[i][0]-a[i][1]);
	}
	ans=max(ans,(maxl-minr+1)/2);
	printf("%d\n",ans);
	if (B==0) return;
	if (maxl<=minr)
	{
		for (int i=1;i<=n;i++) printf("%d ",maxl);
		return;
	}
	int mid=(maxl+minr)/2;
	for (int i=1;i<=n;i++) printf("%d ",max(min(mid,R[i]),L[i]));
	cout << endl;
}
```


---

## 作者：Eibon (赞：2)

考虑当你确定 $s_{1}$ 的时候，你就会确定其他节点的取值，它们一定会尽可能的接近 $s_{1}$ 的值。

$s_{1}$ 最后对答案的贡献即为 $\max(\max(l_{i})-s_{1},s_{1}-\min(r_{i}))$。

考虑到其他节点也有可能对答案造成贡献，即 $l_{u}-r_{v}$ 或者 $l_{v}-r_{u}$。这个可以一遍算出。

考虑计算 $s_{1}$ 的贡献。

设最终答案为 $x$，$mx=\max(l_{i})-s_{1}$，$mn=s_{1}-\min(r_{i}))$。

则 $x \ge mx-s_{1}$，$x \ge s_{1}-mn$。

加起来，解得 $x \ge \dfrac{mx-mn}{2}$。

至此，我们将最小贡献算完了。

考虑构造方案。

感知一下，设 $mid=\lfloor\dfrac{mn+mx}{2}\rfloor$。我们让一个点的值尽可能接近 $mid$。

那么一个点的取值只有三种，$l_{i}$，$r_{i}$ 和 $mid$。

那么 $\left|mid-l_{i}\right|$，$\left|mid-r_{i}\right|$ 和 $\left|l-r\right|$ 这些值都是合法的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
const int mod=1e9+7;
const int inf=0x3f3f3f3f3f3f3f3f;
int T=1,n,B,ans,mx,mn;
int fa[maxn],l[maxn],r[maxn],a[maxn][2];
void solve()
{
    scanf("%lld",&n);
	mx=0,mn=inf;ans=0;
    for(int i=2;i<=n;i++){
		scanf("%lld",&fa[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&l[i],&r[i]);
		mn=min(r[i],mn);mx=max(mx,l[i]);
		a[i][0]=l[i],a[i][1]=r[i];
		if(fa[i]){
			a[i][0]=max(a[fa[i]][0],a[i][0]);
			a[i][1]=min(a[fa[i]][1],a[i][1]);
		}
		ans=max(ans,a[i][0]-a[i][1]);
	}
	ans=max(ans,(mx-mn+1)/2);
	printf("%lld\n",ans);
	if(!B){
		return;
	}
	int mid=(mx+mn)/2;
	for(int i=1;i<=n;i++){
		printf("%lld ",max(min(mid,r[i]),l[i]));
	}
	puts("");
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%lld%lld",&T,&B);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Elma_ (赞：1)

一个不需要脑子的做法。

首先二分这个不平衡度 $m$。考虑自底向上求出每个点 $u$ 的取值范围 $[p_u,q_u]$，使得当 $s_u \in [p_u,q_u]$ 时，$u$ 子树内存在一种不平衡度 $\leq m$ 的方案。

注意到，当我们计算 $u$ 的取值范围时，其子树内所有点 $v$ 的取值范围都已经算出来了，而对于 $s_v \in [p_v,q_v]$，存在 $s_v$ 使得 $|s_u - s_v| \leq m$ 的充要条件是 $s_u \in [p_v - m, q_v + m]$。也就是说子树内每个点 $v$ 对应一个对 $s_u$ 的限制，把这些限制求交，得到的结果再和 $[l_u,r_u]$ 求交就是 $[p_u,q_u]$。维护子树内所有限制的交 $[c_u,d_u]$ 即可。

构造也是容易的，考虑自顶向下填，确定 $s_v$ 的值时 $v$ 的所有祖先 $s_u$ 的值都已经确定了，每个 $u$ 对应一个对 $s_v$ 的限制。把这些限制求交，得到的结果再和 $[p_v,q_v]$ 求交就能得到当前情况下 $s_v$ 的取值范围 $[p_v',q_v']$，在里面随便钦定一个就行了。维护所有祖先限制的交 $[c'_u,d'_u]$ 即可。时间复杂度 $\mathcal{O}(n \log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> pi;
const int N = 1e5 + 5;
int n, B, a[N], l[N], r[N], p[N], q[N], c[N], d[N], m;
vector <int> e[N];
int min(int x, int y) {
    return x < y ? x : y;
}
pi in(int a, int b, int c, int d) {
    if (a > c) {
        swap(a, c), swap(b, d);
    }
    if (b >= d) {
        return make_pair(c, d);
    } else if (b >= c) {
        return make_pair(c, b);
    } else {
        return make_pair(-1, -1);
    }
}
void dfs(int u, int ff) {
    p[u] = l[u];
    q[u] = r[u];
    for (auto v : e[u]) {
        if (v == ff) {
            continue;
        }
        dfs(v, u);
        tie(p[u], q[u]) = in(p[u], q[u], c[v], d[v]);
    }
    c[u] = max(p[u] - m, 0);
    d[u] = min(q[u] + m, 1e9);
    for (auto v : e[u]) {
        if (v == ff) {
            continue;
        }
        tie(c[u], d[u]) = in(c[u], d[u], c[v], d[v]);
    }
}
void fill(int u, int ff) {
    if (u == 1) {
        a[u] = p[u];
        c[u] = max(a[u] - m, 0);
        d[u] = min(a[u] + m, 1e9);
    }
    for (auto v : e[u]) {
        if (v == ff) {
            continue;
        }
        int L, R;
        tie(L, R) = in(c[u], d[u], p[v], q[v]);
        a[v] = L;
        tie(c[v], d[v]) = in(max(L - m, 0), min(L + m, 1e9), c[u], d[u]);
        fill(v, u);
    }
}
bool chk(int m) {
    dfs(1, 0);
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        if (p[i] == -1) {
            ok = false;
        }
    }
    return ok;
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        e[i].clear();
    }
    for (int i = 2, f; i <= n; i++) {
        cin >> f;
        e[f].push_back(i);
        e[i].push_back(f);
    }
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    int L = 0, R = 1e9, mi = 1e9;
    while (L <= R) {
        m = (L + R) / 2;
        if (chk(m) == true) {
            R = m - 1, mi = m;
        } else {
            L = m + 1;
        }
    }
    cout << mi << "\n";
    if (B == 1) {
        m = mi, dfs(1, 0);
        fill(1, 0);
        for (int i = 1; i <= n; i++) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }
}
int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    cin >> t >> B;
    while (t--) {
        solve();
    }
    return 0;
}
```


---

