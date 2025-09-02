# Counting Is Not Fun (Hard Version)

## 题目描述

这是该问题的困难版本。与简单版本的区别在于，此版本对 $t$ 和 $n$ 的限制更大。仅当解决所有版本的问题时方可进行 hack。

小 John 现在很富有，终于买得起能容纳自己和最喜爱括号序列的大房子了。但不知为何，他得到了大量括号！沮丧之下，他用"佛掌"击穿了天花板。一个括号序列被称为平衡的，当且仅当其可以通过以下形式文法构造：

1. 空序列 $\varnothing$ 是平衡的。
2. 若括号序列 $A$ 是平衡的，则 $\mathtt{(}A\mathtt{)}$ 也是平衡的。
3. 若括号序列 $A$ 和 $B$ 是平衡的，则拼接序列 $AB$ 也是平衡的。

例如，序列 "(())()"、"()"、"(()(()))" 和空序列是平衡的，而 "(()" 和 "(()))(" 则不是。

给定一个平衡括号序列 $s$，当满足以下条件时，索引对 $(i,j)$（$i<j$）被称为好对：$s_i$ 是 '('，$s_j$ 是 ')'，且这两个括号是在构造序列 $s$ 时通过规则 2 同时添加的。例如，序列 "(())()" 有三个不同的好对：$(1,4)$、$(2,3)$ 和 $(5,6)$。可以证明，任何包含 $2n$ 个括号的平衡括号序列恰好有 $n$ 个不同的好对，且无论用何种规则顺序构造同一括号序列，得到的好对集合都相同。

Emily 将与 John 进行括号猜谜游戏。游戏规则如下：

初始时，John 有一个包含 $n$ 个不同好对的平衡括号序列 $s$，但 Emily 不知道其内容。John 告诉 Emily $n$ 的值，并要求 Emily 猜测该序列。

在 $n$ 轮中，John 每轮给出如下形式的线索：
- $l\;r$：序列 $s$ 包含好对 $(l,r)$。

John 给出的线索互不相同且互不矛盾。

在某个时刻，Emily 可以确定满足当前所有线索的平衡括号序列是唯一的。例如，假设 Emily 知道 $s$ 有 $3$ 个好对，并包含好对 $(2,5)$。在 $5$ 个有 $3$ 个好对的平衡括号序列中，只有序列 "((()))" 包含好对 $(2,5)$。因此，可以看出 Emily 并不总是需要 $n$ 轮才能猜出 $s$。

为了尽早确定 $s$ 的内容，Emily 希望知道每轮线索后符合条件的平衡括号序列数量。显然这对 Emily 来说并非易事，尤其当存在大量好对时。现在轮到你来帮助 Emily。给定所有线索，你需要在每轮前后输出答案。由于答案可能很大，请对 $998\,244\,353$ 取模。

## 说明/提示

样例中的第一个测试用例已在题目描述中解释。

第三个测试用例的解释如下：可以证明存在 $132$ 个有 $6$ 个好对的平衡括号序列。每接收一条线索后的答案如下：
1. 收到好对 $(2,3)$ 后，存在 $42$ 个符合条件的序列。
2. 收到好对 $(1,6)$ 后，存在 $5$ 个同时包含 $(2,3)$ 和 $(1,6)$ 的序列。
3. 收到好对 $(7,8)$ 后，存在 $2$ 个满足三个好对的序列，分别为 "(()())()(())" 和 "(()())()()()"。
4. 收到好对 $(9,12)$ 后，仅剩 $1$ 个满足四个好对的序列，即 "(()())()(())"。
之后的第五、第六条线索接收后答案均为 $1$，因为此时已确定唯一序列。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
2 5
1 6
3 4
4
1 6
7 8
2 3
4 5
6
2 3
1 6
7 8
9 12
10 11
4 5```

### 输出

```
5 1 1 1
14 2 2 1 1
132 42 5 2 1 1 1```

# 题解

## 作者：Register_int (赞：13)

没钦定的情况就是普通的括号序列计数，套卡特兰即可。事实上，强行先塞一对括号 $[0,2n+1]$，将每对括号 $[l_i,r_i]$ 视为树上的一个节点 $i$，将每个对括号向被被他包含的下一层括号连边，就能得到一棵树。设 $len_i=r_i-l_i+1$，则一个点 $u$ 内能自由放置的括号数量就是 $val_u=len_u-2-\sum_{v\in\text{son}(u)} len_v$。那么方案数为 $\prod_i cat_{val_i}$。

发现询问相当于在树上加点，这是困难的。不妨倒着做，转化为删一个点 $u$ 并将其所有儿子连到他的父亲 $fa_u$ 上。可以发现一次修改只会影响 $u$ 和 $fa_u$ 的 $val$，所以只要快速维护一个点的父亲是谁即可。可以使用并查集，删去 $u$ 就将 $u$ 与 $fa_u$ 合并成一个点，时间复杂度 $O(n\alpha(n))$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 6e5 + 10;
const int mod = 998244353;

int fac[MAXN], inv[MAXN], ifac[MAXN];

inline 
void init(int n) {
	inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
	*fac = *ifac = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	for (int i = 1; i <= n; i++) ifac[i] = (ll)ifac[i - 1] * inv[i] % mod;
}

inline 
int c(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod; 
}

inline int f(int n) { return (ll)fac[n] * ifac[n / 2] % mod * ifac[n / 2] % mod * inv[n / 2 + 1] % mod; }
inline int invf(int n) { return (ll)ifac[n] * fac[n / 2] % mod * fac[n / 2] % mod * (n / 2 + 1) % mod; }

int T, n, a[MAXN], t[MAXN], tp;

int fa[MAXN], val[MAXN], p[MAXN], ans[MAXN], res;

int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }

int main() {
	for (scanf("%d", &T), init(6e5); T--; ) {
		scanf("%d", &n), *val = 0, res = 1;
		for (int i = 1; i <= n * 2; i++) a[i] = 0;
		for (int i = 1, l, r; i <= n; i++) scanf("%d%d", &l, &r), a[l] = a[r] = i;
		for (int i = 1; i <= n; i++) p[i] = i;
		for (int i = 1; i <= n * 2; i++) {
			if (!a[i]) { val[t[tp]]++; continue; }
			if (t[tp] != a[i]) t[++tp] = a[i], val[a[i]] = 0;
			else fa[a[i]] = t[--tp];
		}
		for (int i = 0; i <= n; i++) res = (ll)res * f(val[i]) % mod;
		ans[n + 1] = res;
		for (int i = n; i; i--) {
			int u = find(fa[i]); p[i] = u;
			res = (ll)res * invf(val[i]) % mod * invf(val[u]) % mod;
			ans[i] = res = (ll)res * f(val[u] += val[i] + 2) % mod;
		}
		for (int i = 1; i <= n + 1; i++) printf("%d ", ans[i]); puts("");
	}
}
```

---

## 作者：KingPowers (赞：4)

来记录一下赛时做法。

约定：记 $\text{Cat}(n)=\frac{\binom{2n}{n}}{n+1}=\binom{2n}{n}-\binom{2n}{n+1}$，也就是卡特兰数的第 $n$ 项。

## Easy Version：$n\le 5000$

考虑一对限制 $(l,r)$ 实际上是在要求啥，相当于令 $s_l$ 和 $s_r$ 是一对相互匹配的左右括号，且 $[l+1,r-1]$ 这个子串也形成了一个合法的括号序列。

因为题目保证了给出的所有限制一定都合法且不会重复，如果把每对 $(l,r)$ 看成一个线段，所有的线段之间只会是不交或者包含的关系，这时候一个经典的思路就是按照线段之间的包含关系建树，也就是每个线段找包含它且长度最短的另一个线段作为它的父亲。为了方便，我们可以在最开始的时候加入线段 $[0,n+1]$。

这么做的好处是，我们发现树上每个点的贡献是独立的。具体来说，记 $len_u$ 表示树上点 $u$ 对应的线段长度，那么一个点 $u$ 的贡献就是 $\text{Cat}(\frac{len_u-2-\sum_{v\in son_u}len_v}{2})$，答案就是把每个点 $u$ 的贡献乘起来。

![](https://cdn.luogu.com.cn/upload/image_hosting/51s9bztn.png)

对着上图稍微解释下，假设红色线段是 $u$，蓝色线段是它的儿子，对于被儿子的线段覆盖掉的位置的贡献我们直接在儿子处计算，这样对于 $u$ 来说限制就只剩下了绿色的没有被儿子覆盖的部分要形成合法括号序列，减 $2$ 是为了去掉端点 $l,r$。

对于 Easy Version，我们每次加入一个线段时可以暴力重构树的结构，直接扫一遍之前的线段找到它的父亲，再把父亲原来儿子里被新线段包含的改为新线段的儿子，这样每次重构是 $O(n)$ 的，然后直接 dfs 计算上面的式子即可，这样就做到了 $O(n^2)$。

代码里省略了 modint 类。


```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define fi first
#define se second
using namespace std;
const int N = 1e6 + 5, mod = 998244353, inf = 1e9;
using pii = pair<int, int>;
int n, m, tot; pii p[N];
mint ans, fac[N], ifac[N], cat[N];
vector<int> e[N];
mint C(int n, int m){
	if(n < m || m < 0) return 0;
	return fac[n] * ifac[m] * ifac[n - m];
}
void init(int n){
	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i;
	ifac[n] = qpow(fac[n], mod - 2);
	Rof(i, n, 1) ifac[i - 1] = ifac[i] * i;
	For(i, 0, n) cat[i] = C(2 * i, i) / (i + 1);
}
void dfs(int now){
	int len = p[now].se - p[now].fi - 1;
	for(int to : e[now]){
		dfs(to);
		len -= p[to].se - p[to].fi + 1;
	}
	ans *= cat[len / 2];
}
void add(int id){
	int pos = 0, mn = inf;
	For(i, 1, tot) if(i != id){
		if(p[i].se < p[id].se || p[i].fi > p[id].se) continue;
		int len = p[i].se - p[i].fi + 1;
		if(len < mn) mn = len, pos = i;
	}
	vector<int> son;
	for(int to : e[pos]){
		if(p[to].fi >= p[id].fi && p[to].se <= p[id].se)
			son.push_back(to);
	}
	for(int x : son){
		e[pos].erase(find(e[pos].begin(), e[pos].end(), x));
		e[id].push_back(x);
	}
	e[pos].push_back(id);
}
void calc(){
	ans = 1; dfs(1);
	cout << ans << ' ';
}
void Solve(){
	cin >> m; n = m << 1; tot = 0;
	p[++tot] = {0, n + 1}; calc();
	For(i, 1, m){
		int l, r; cin >> l >> r;
		p[++tot] = {l, r}; add(tot); calc();
	}
	cout << '\n';
	For(i, 1, tot) e[i].clear();
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	init(600005);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

## Hard Version：$n\le 3\times10^5$

考虑延续上面的思路，此时的数据范围要求我们支持添加线段并动态维护树上每个点的贡献。赛时并没有想到可以直接离线，所以编了一个在线的做法。

尝试重新刻画每个线段没被儿子覆盖的长度。我们设 $mx_i$ 表示所有覆盖 $i$ 的线段里最大的左端点在哪个位置，特别地要判掉 $i$ 本身是某个线段的左右端点的情况。那么对于一个线段 $[l,r]$ 来说，前面要计算的长度其实就是满足 $mx_i=l$ 的 $i$ 的个数，贡献就变成了 $\text{Cat}(\frac{\sum_{i=1}^n[mx_i=l]}{2})$，答案就是对每个线段的 $l$ 计算这个式子乘起来。

想想这个是不是好维护的。最开始的时候相当于是 $\forall i,mx_i=0$，加入一个线段 $[l,r]$ 的时候相当于是 $\forall i\in[l+1,r-1],mx_i\leftarrow\max(mx_i,l)$，也就是一个 check max 的操作，同时去掉 $l,r$ 两个端点的贡献，然后需要算出这个过程中答案的增量。

考虑使用吉司机线段树，因为吉司机线段树特别的修改方式，在做 check max 的时候我们只会把区间内若干个相同的数进行修改，额外维护一个区间内最小值的个数 $cnt$，直接开桶对每个 $l$ 存 $mx_i=l$ 的位置个数，这样递归修改的时候只会改变桶的两个位置且变化量都是 $cnt$，答案的变化容易计算。至于去掉 $l,r$ 的贡献可以直接做个单点修改 $+\infty$，是容易的。

提前预处理卡特兰数的逆元，因为这里的吉司机线段树并没有区间加，所以上面的操作均摊下来单次是 $O(\log n)$ 的，最后的复杂度是优秀的 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define fi first
#define se second
using namespace std;
const int N = 1e6 + 5, mod = 998244353, inf = 1e9;
using pii = pair<int, int>;
int n, m, tot; pii p[N];
mint ans, fac[N], ifac[N], cat[N], icat[N];
vector<int> e[N];
mint C(int n, int m){
	if(n < m || m < 0) return 0;
	return fac[n] * ifac[m] * ifac[n - m];
}
void init(int n){
	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i;
	ifac[n] = qpow(fac[n], mod - 2);
	Rof(i, n, 1) ifac[i - 1] = ifac[i] * i;
	For(i, 1, n) cat[i] = C(2 * i, i) / (i + 1), icat[i] = qpow(cat[i], mod - 2);
}
int cur[N];
inline void ins(int p, int v = 1){if(p == inf) return; cur[p] += v;}
inline void era(int p, int v = 1){if(p == inf) return; cur[p] -= v;}
mint F(int l){
	if(l == inf || !cur[l]) return 1;
	if(cur[l] & 1) return 1;
	return cat[cur[l] / 2];
}
mint G(int l){
	if(l == inf || !cur[l]) return 1;
	if(cur[l] & 1) return 1;
	return icat[cur[l] / 2];
}
struct node{
	int mn, smn, cnt;
	friend node operator+(const node &a, const node &b){
		node c; c.mn = min(a.mn, b.mn);
		if(a.mn == b.mn) c.smn = min(a.smn, b.smn);
		else if(a.mn > b.mn) c.smn = max(a.smn, b.mn);
		else c.smn = max(a.mn, b.smn);
		c.cnt = (a.mn == c.mn) * a.cnt + (b.mn == c.mn) * b.cnt;
		return c;
	}
};
struct segtree{
	node t[N << 2];
	#define ls now << 1
	#define rs now << 1 | 1
	inline void pushup(int now){t[now] = t[ls] + t[rs];}
	inline void addtag(int now, int w){t[now].mn = max(t[now].mn, w);}
	inline void pushdown(int now){addtag(ls, t[now].mn); addtag(rs, t[now].mn);}
	void build(int l, int r, int now){
		if(l == r) return t[now] = {0, inf, 1}, void();
		int mid = (l + r) >> 1;
		build(l, mid, ls); build(mid + 1, r, rs);
		pushup(now);
	}
	void update(int p, int v, int l, int r, int now){
		if(l == r){
			ans *= G(t[now].mn); ans *= G(v); int lst = t[now].mn;
			era(t[now].mn); t[now].mn = v; ins(t[now].mn);
			ans *= F(lst); ans *= F(v);
			return;
		}
		int mid = (l + r) >> 1; pushdown(now);
		if(p <= mid) update(p, v, l, mid, ls);
		else update(p, v, mid + 1, r, rs);
		pushup(now);
	}
	void modify(int x, int y, int v, int l, int r, int now){
		if(t[now].mn >= v) return;
		if(x <= l && r <= y && t[now].smn > v){
			ans *= G(t[now].mn); ans *= G(v); int lst = t[now].mn;
			era(t[now].mn, t[now].cnt); t[now].mn = v; ins(t[now].mn, t[now].cnt);
			ans *= F(lst); ans *= F(v);
			return;
		} 
		int mid = (l + r) >> 1; pushdown(now);
		if(x <= mid) modify(x, y, v, l, mid, ls);
		if(y > mid) modify(x, y, v, mid + 1, r, rs);
		pushup(now);
	}
}sgt;
void add(int l, int r){
	if(l < r) sgt.modify(l + 1, r - 1, l, 1, n, 1);
	sgt.update(l, inf, 1, n, 1); sgt.update(r, inf, 1, n, 1);
}
void Solve(){
	cin >> m; n = m << 1; tot = 0;
	ans = cat[m]; cout << ans << ' ';
	For(i, 1, n) cur[i] = 0;
	cur[0] = n; sgt.build(1, n, 1);
	For(i, 1, m){
		int l, r; cin >> l >> r;
		add(l, r); cout << ans << ' ';
	}
	cout << '\n';
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	init(600005);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：Shunpower (赞：3)

提供一个疑似是本题最简单的做法，并且我们爆标了。practical 的复杂度是 $\mathcal O(n\alpha(n))$，使用[线性树上并查集](https://ljt12138.blog.uoj.ac/blog/4874)我们可以做到线性。

感谢 @[StayAlone](/user/409236) 提供的细节帮助，感谢 @[AfterFullStop](/user/555065) 指出本做法可以做到线性。

------------------

回顾 F1 的做法：

我们对已知的匹配括号建立括号串分治树。具体来说，树上每个节点都是一对匹配括号 $(u,R_u)$，我们按照它们的包含和不交关系建立成树。

有了树结构，答案是容易表示的。我们维护每个节点下没有被儿子匹配管辖的空位的长度 $l_u$，即 $l_u=R_u-u-1-(\sum\limits_{v\in \operatorname{son}(u)} R_v-v+1)$。它产生的贡献就是这一长度的合法括号串的数量，也就是一个卡特兰数 $C_{\frac{l_u}{2}}$。

答案把所有节点的贡献乘起来就好。

延续 F1 的做法。我们尝试维护分治树，考虑每次加入一个节点产生的影响。因为加入节点需要操作子树，这不太方便，我们考虑时光倒流。

时光倒流之后，每次我们只需删除一个节点，把它的儿子挂到它的父亲上。贡献上会产生的影响只有删去它的 $l$ 的贡献，再改变它父亲的 $l$ 的贡献，结构上也只会影响此处的父亲关系。

我们直接用逆元撤销掉原来的贡献，再把新的贡献加上去，同时维护 $l$。

考虑剩下的问题是我们还需要也仅需要维护分治树上的父亲关系，需要支持删除一个节点。类似可并堆的处理办法，考虑我们没必要真实删除这个节点，把它重定向到它的父亲即可。用一个并查集就可以简单维护好。

实现上，因为分治树上所有节点的端点都互不相同，所以我们可以从端点映射节点规避 `map`；卡特兰数及其逆元可以用线性阶乘逆元、线性逆元 $\mathcal O(1)$ 得到。于是时间复杂度瓶颈是并查集。

树上并查集直接写可以做到 $\mathcal O(n\alpha(n))$，使用[线性树上并查集](https://ljt12138.blog.uoj.ac/blog/4874)就可以把整个东西打成线性。

下面是一个懒得写按秩合并所以带 $\log$ 的代码：

```cpp
int tc;
int n;
ll fac[N],ifac[N],inv[N];
ll qpow(ll b,int p){
    if(!p) return 1;
    ll d=qpow(b,p>>1);
    if(p&1) return d*d%mod*b%mod;
    else return d*d%mod;
}
void init(int n=1.2e6){
    fac[0]=1;
    fr1(i,1,n) fac[i]=fac[i-1]*i%mod;
    ifac[n]=qpow(fac[n],mod-2);
    fr2(i,n-1,0) ifac[i]=ifac[i+1]*(i+1)%mod;
    fr1(i,1,n) inv[i]=ifac[i]*fac[i-1]%mod;
}
ll Ca(int n){
    return fac[n]*ifac[n>>1]%mod*ifac[n>>1]%mod*inv[(n>>1)+1]%mod;
}
ll iCa(int n){
    return ifac[n]*fac[n>>1]%mod*fac[n>>1]%mod*((n>>1)+1)%mod;
}
int mat[N];
vector <int> op;
vector <int> res;
int fa[N],dirf[N];
int len[N];
int node[N];
int tot;
int find(int x){
    if(fa[x]!=x) fa[x]=find(fa[x]);
    return fa[x];
}
void divide(int f,int l,int r){
    tot++;
    node[l]=tot;
    len[tot]=0,dirf[tot]=f,fa[tot]=tot;
    int cnt=0;
    fr1(i,l+1,r-1){
        divide(node[l],i,mat[i]);
        i=mat[i];
    }
}
void solve(){
    tot=0;
    op.clear(),res.clear();
    cin>>n;
    fr1(i,1,(n<<1)) mat[i]=0;
    fr1(i,1,n){
        int u,v;
        cin>>u>>v;
        mat[u]=v;
        op.pb(u);
    }
    divide(0,0,(n<<1)+1);
    ll ans=1;
    fr2(i,n-1,0){
        res.pb(ans);
        int id=op[i];
        int u=node[id];
        int f=find(dirf[u]);
        (ans*=iCa(len[u]))%=mod;
        (ans*=iCa(len[f]))%=mod;
        len[f]+=len[u]+2;
        (ans*=Ca(len[f]))%=mod;
        fa[u]=f;
    }
    res.pb(ans);
    while(!res.empty()){
        cout<<res.back()<<" ";
        res.pop_back();
    }
    cout<<'\n';
}
```

---

## 作者：Dovish (赞：2)

~~没搞懂为啥官解要写平衡树啊。~~
## 前情提要
首先你得会 F1 做法。

记 $C_k$ 是卡特兰数的第 $k$ 项。

我们不妨称一对匹配的括号 $l,r$ 为一条覆盖 $[l,r]$ 的线段。

我们根据当前线段的覆盖关系，建立一颗树。对于每个节点，其答案是 $C_{\frac{l_u}2}$。（$l_u$ 是 $u$ 覆盖的**开**区间中有多少个位置没有被其任意一个儿子覆盖）显然不同节点之间的答案互不影响，所以最后将每个节点的贡献乘起来就得到了答案。
## 正文
现在，我们的问题就是要动态维护这个过程。

此时，我们的问题有两个：

一是找到这个要插入的线段的父亲节点。

二是重新计算贡献。（显然只需要重新计算这个线段以及其父亲节点的贡献。）

对于第一个问题，我们可以建立一颗线段树，每次插入一个线段的时候在线段树的 $l$ 位置插入 $r$。

那么其父节点就是所有小于 $l$ 的位置上第一个权值大于 $r$ 的线段。可以线段树上二分直接做。

对于第二个问题，我们可以不用显式地建出整颗树。注意“没有被 $u$ 的任意一个儿子覆盖”等价于“总的被覆盖的次数等于 $u$ 的祖先的个数”。而 $u$ 的祖先的个数一定是这个区间中被覆盖的次数的最小值。

于是问题就转化成了区间加，区间求最小值个数。

同样可以写一颗线段树解决。

复杂度 $O(n\log n)$。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
#define lc (u<<1)
#define rc (u<<1|1)
#define pii pair<int,int>
#define pdd pair<double,double>
#define mp make_pair
#define pb push_back
#define fst first
#define sed second
using namespace std;
const int N=3e5+10,M=1e6+10,inf=1e18,mod=998244353;
const double eps=1e-6;
struct modint{
	int val;
	static int norm(const int& x){return x<0?x+mod:x;}
	modint inv()const{
		int a=val,b=mod,u=1,v=0,t;
		while (b>0)t=a/b,swap(a-=t*b,b),swap(u-=t*v,v);
		return modint(u);
	}
	modint():val(0){}
	modint(const int& m):val(norm(m)){}
	modint(const long long& m):val(norm(m % mod)){}
	modint operator-()const{return modint(norm(-val));}
	bool operator==(const modint&o){return val==o.val;}
	bool operator<(const modint&o){return val<o.val;}
	modint&operator+=(const modint&o){return val=(1ll*val+o.val)%mod,*this;}
	modint&operator-=(const modint&o){return val=norm(1ll*val-o.val),*this;}
	modint&operator*=(const modint&o){return val=static_cast<int>(1ll*val*o.val%mod),*this;}
	modint operator-(const modint&o)const{return modint(*this)-=o;}
	modint operator+(const modint&o)const{return modint(*this)+=o;}
	modint operator*(const modint&o)const{return modint(*this)*=o;}
	friend std::ostream&operator<<(std::ostream& os, const modint&a){return os<<a.val;}
	friend std::istream&operator>>(std::istream& is,modint&a){ll v;return is>>v,a.val=norm(v%mod),is;}
};
bool MS;
modint fac[N<<1],inv[N<<1];
modint ans,c[N];
struct sx
{
	int l,r;
	bool operator<(const sx&b)const
	{
		return l<b.l;
	}
}line[N];
int L[N],R[N],n;
int rev[N<<1],sz[N];
namespace SGT
{
	int tre[N<<4];
	void pushup(int u)
	{
		tre[u]=max(tre[lc],tre[rc]);
	}
	void add(int u,int l,int r,int x,int k)
	{
		if(l==r)
		{
			tre[u]=k;
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)add(lc,l,mid,x,k);
		else add(rc,mid+1,r,x,k);
		pushup(u);
	}
	pii erfen(int u,int l,int r,int k)
	{
		if(l==r)
		return mp(l,tre[u]);
		int mid=(l+r)/2;
		if(tre[rc]>k)return erfen(rc,mid+1,r,k);
		else return erfen(lc,l,mid,k);
	}
	pii getans(int u,int l,int r,int x,int k)
	{
		if(l==r)
		return mp(l,tre[u]);
		int mid=(l+r)/2;
		if(x<=mid)return getans(lc,l,mid,x,k);
		else
		{
			pii g=getans(rc,mid+1,r,x,k);
			if(g.sed>k||tre[lc]<=k)return g;
			else return erfen(lc,l,mid,k);
		}
	}
}using namespace SGT;
namespace SGT2
{
	struct sx
	{
		pii g;
		int add;
	}tre[N<<4];
	void pushup(int u)
	{
		tre[u].g.fst=min(tre[lc].g.fst,tre[rc].g.fst);
		tre[u].g.sed=0;
		if(tre[u].g.fst==tre[lc].g.fst)tre[u].g.sed+=tre[lc].g.sed;
		if(tre[u].g.fst==tre[rc].g.fst)tre[u].g.sed+=tre[rc].g.sed;
	}
	void update(int u,int k)
	{
		tre[u].add+=k;
		tre[u].g.fst+=k;
	}
	void pushdown(int u)
	{
		if(tre[u].add)
		{
			update(lc,tre[u].add);
			update(rc,tre[u].add);
			tre[u].add=0;
		}
	}
	void build(int u,int l,int r)
	{
		tre[u].add=0;
		if(l==r)
		{
			tre[u].g=mp(0,1);
			return;
		}
		pushdown(u);
		int mid=l+r>>1;
		build(lc,l,mid);
		build(rc,mid+1,r);
		pushup(u);
	}
	void add(int u,int l,int r,int x,int y,int k)
	{
		if(x<=l&&r<=y)
		{
			update(u,k);
			return;
		}
		pushdown(u);
		int mid=l+r>>1;
		if(x<=mid)add(lc,l,mid,x,y,k);
		if(y>mid)add(rc,mid+1,r,x,y,k);
		pushup(u);
	}
	pii query(int u,int l,int r,int x,int y)
	{
		if(x>y)return mp(0,0);
		if(x<=l&&r<=y)
		return tre[u].g;
		pushdown(u);
		int mid=l+r>>1;
		if(x<=mid&&y>mid)
		{
			pii a=query(lc,l,mid,x,y);
			pii b=query(rc,mid+1,r,x,y);
			if(a.fst==b.fst)return mp(a.fst,a.sed+b.sed);
			else return min(a,b);
		}
		if(x<=mid)return query(lc,l,mid,x,y);
		if(y>mid)return query(rc,mid+1,r,x,y);
	}
}
void init()
{
	rep(i,0,n+1)sz[i]=rev[i]=0;
	rep(i,1,(n<<4)+10)tre[i]=0;
	SGT2::build(1,0,2*n+1);
}
void solve()
{
	cin>>n;
	init();
	ans=c[n];
	cout<<ans<<' ';
	add(1,0,2*n+1,0,2*n+1);
	rev[0]=n+1;L[n+1]=0,R[n+1]=2*n+1;
	sz[n+1]=2*n;
	rep(i,1,n)
	{
		cin>>L[i]>>R[i];
		rev[L[i]]=i;
		sz[i]=R[i]-L[i]-1;
		add(1,0,2*n+1,L[i],R[i]);
		int fa=rev[getans(1,0,2*n+1,L[i],R[i]).fst];
		ans*=c[sz[fa]/2].inv();
		SGT2::add(1,0,2*n+1,L[i],R[i],1);
        sz[fa]=SGT2::query(1,0,2*n+1,L[fa],R[fa]).sed-2;
		sz[i]=SGT2::query(1,0,2*n+1,L[i],R[i]).sed-2;
		ans*=c[sz[fa]/2];
		ans*=c[sz[i]/2];
		cout<<ans<<" ";
	}cout<<'\n';
}
bool MT;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	fac[0]=inv[0]=1;
	rep(i,1,(N<<1)-1)fac[i]=fac[i-1]*i;
	inv[(N<<1)-1]=fac[(N<<1)-1].inv();
	per(i,(N<<1)-2,1)inv[i]=inv[i+1]*(i+1);
	
	c[0]=1;
	rep(i,1,N-1)
	c[i]=fac[i<<1]*inv[i]*inv[i]-fac[i<<1]*inv[i-1]*inv[i+1];
	
	int T=1;
	cin>>T;
	while(T--)
	solve();
	cerr<<"Memory:"<<(&MS-&MT)/1048576.0<<"MB Time:"<<clock()/1000.0<<"s\n";
}
```

---

## 作者：toolazy (赞：1)

来个诡异做法（idea by @[liaoz123](https://www.luogu.com.cn/user/914961) thx

考虑先建括号树，怎么建之后说。

那么，对于括号树上的每一个节点，它对答案的贡献就是 $H_m$，其中 $H$ 为卡特兰数，$2m$ 为这个节点对应括号内部自由的字符数量。

具体的，由于限制形如括号配对，因此每一个括号的贡献是独立乘算的。对于一个包含了其它括号的括号，它可以自由决策的字符就是那些被自己包含且没有被其它子括号包含的字符。

只要能把优秀地维护括号树，那么计算 $m$ 就是简单的，更新答案也是简单的。

现在的问题在于如何动态改树，这里就直接大力 DS 了吧（（（

具体的，由于匹配括号非包则无交，因此每次增加一对括号，其本质就是增加一个节点，并夺取原树某节点的一段连续儿子。

考虑直接 FHQ 维护儿子，直接切两刀就行了，所以非常好 $O(n\lg n)$。

---

## 作者：Kingna (赞：1)

## [CF2063F1+F2 Counting Is Not Fun](https://www.luogu.com.cn/problem/CF2063F1)

### 题目大意

现在有一个隐藏的长度恰好为 $2n$ 的『合法括号串』$s$。依次有 $n$ 条信息，每条信息给出 $l,r$ 表示 $s_l=\texttt{(},s_r=\texttt{)}$ 且 $s_l,s_r$ 是可以直接匹配的。回答 $n+1$ 个问题：

- 第一个问题回答没有给定任何信息时 $s$ 的所有可能情况。
- 第 $i+1$ 个问题回答给定前 $i$ 条信息时 $s$ 的所有可能情况。

答案对 $998244353$ 取模。

### 题目思路

先将 $H_n$ 记为 $n$ 对括号组成的合法的括号序列个数，是 Catalan 数。如果对于每一个括号，如果它中间未被里面括号包含的空位置个数为 $k$，那么这 $k$ 个位置则是一个合法的括号串，方案数为 $H_k$。答案就是 $H_k$ 的乘积。用栈来模拟，如果遇到了右括号，那么弹出栈顶直到遇到了左括号。弹出栈的元素数量就是这对括号未被里面括号包含的空位置个数。

F1 只需要将这些操作模拟一遍，复杂度 $O(n^2)$。F2 则需要用数据结构来维护。

---


考虑加入一对括号后，将本来的 $H_x$ 分裂成 $H_y$ 和 $H_{x-y-1}$。这样做并不好做，考虑倒着操作。

最开始先将所有括号加入，再依次将括号对删除。假设其父亲节点对应的空位置为 $x$ 个，自己对应的空位置为 $y$ 个，则合并之后答案会将 $H_x$ 和 $H_y$ 除掉，再乘上新的 $H_{x+y+1}$。同时，父亲节点的空位置个数累计上 $y$。因为是倒着操作，则最开始每个括号对所对应的父亲括号对已经完全确定了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 6e5 + 5, mod = 998244353;

int T, n, fac[N], invfac[N], ans[N], a[N], fa[N], val[N];

int qpow(int a, int k, int p) {
	int res = 1;
	while (k) {
		if (k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}

void init() {
	fac[0] = 1;
	_for(i, 1, N - 5) fac[i] = fac[i - 1] * i % mod;
	invfac[N - 5] = qpow(fac[N - 5], mod - 2, mod);
	_pfor(i, N - 6, 0) invfac[i] = invfac[i + 1] * (i + 1) % mod; 
}

int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * invfac[n - m] % mod * invfac[m] % mod;
}

int calc(int x) {
	x /= 2;
	return (C(2 * x, x) - C(2 * x, x + 1) + mod) % mod;
}

int p[N];

int find(int x) {
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}


signed main() {
	cin >> T; init(); 
	while (T--) {
		cin >> n;
		_for(i, 0, n) p[i] = i, val[i] = 0;
		_for(i, 1, n) {
			int l, r;
			cin >> l >> r;
			a[l] = a[r] = i;
		}
		stack<int> stk; stk.push(0); 
		_for(i, 1, 2 * n) {
			if (a[i] != stk.top()) stk.push(a[i]);
			else stk.pop(), fa[a[i]] = stk.top(); // 处理父亲括号
		}
		int res = 1;
		_for(i, 0, n) res = res * calc(val[i]) % mod;
		ans[n + 1] = res; 
		_pfor(i, n, 1) {
			int t = find(fa[i]); p[i] = t;
			res = res * qpow(calc(val[i]), mod - 2, mod) % mod * qpow(calc(val[t]), mod - 2, mod) % mod;
			val[t] += val[i] + 2;
			res = res * calc(val[t]) % mod;
			ans[i] = res;
		}
		_for(i, 1, n + 1) cout << ans[i] << ' ';
		puts("");
	}
}
```

---

## 作者：D0000 (赞：1)

### 题意

有一个长度为 $2n$ 的括号序列，依次告诉你 $n$ 对匹配的括号，需要在每次告诉你之前和之后回答随便填没告诉你的位置，能构成多少个合法的括号序列。

### 解法

#### F1
首先 $n$ 对括号组成的合法的括号序列是 Catalan 数，这里记作 $H_n$。

可以假设外面套了一个括号把整个串包起来。

对于每个括号，如果它中间未被里面的括号串包含（直接包含）的空位置个数为 $k$，则这 $k$ 个位置需要成为一个合法的括号串，有 $H_k$ 种。而答案应当是 $H_k$ 的乘积。

比如对于括号序列 `((..)...(....(....)..).)` 最大的括号直接包含 $4$ 个空位置，其他几个括号直接包含 $2,6,4$ 个空位置，因此总共有 $H_2H_1H_3H_2$ 种方案。

证明也很简单，一对匹配的括号中的括号需要满足左括号数等于右括号数，且任意前缀左括号数不应当小于右括号数，这与括号串没有本质区别。

Catalan 数能够预处理。新加入的括号只会改变最小的一个包含它的括号对答案的贡献。只需要每次加括号时改变最小的一个包含它的括号的 $k$ 值，以及通过枚举所有它包含的位置来计算这个新括号对的 $k$ 值。能够 $O(n^2)$ 解决。这样，可以通过 F1。
#### F2
注意到时间复杂度的瓶颈是枚举一个括号包含的位置有没有其他括号。

用线段树可以找最小的包含一个括号的括号对。对于每个 $l,r$ 括号对，在 $l$ 处插入 $r$，用 MAX 线段树，每次查询的就是 $[0,l]$ 中最后一个大于 $r$ 的位置。

同样可以用线段树找区间中已经被更小的括号对包含的位置。对于每个位置，最小的一个包含它的括号对右边的一个是 $r$，则在 $r$ 处加 $1$。这样查询 $[l,r]$ 的和即可，因为给定的括号对是合法的。如果查询的值是 $s$。那么在线段树 $r$ 位置加上 $r-l-1-s$ 即完成了对线段树的维护。

时间复杂度 $O(n\log n)$。

### 代码
```cpp

#include<cstdio>
#include<utility>
#include<algorithm>
int n,sgt[4000005],tag[4000005],ans,l,r;
int ak[4000005],mod=998244353,inv[4000005],q[4000005],qv[4000005];
int stt[4000005];
void aa(int x,int v,int l=0,int r=2*n+1,int o=1){
    stt[o]+=v;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(x<=mid)aa(x,v,l,mid,o*2);
    else aa(x,v,mid+1,r,o*2+1);
}
int qq(int ll,int rr,int l=0,int r=2*n+1,int o=1){
    if(ll<=l&&rr>=r)return stt[o];
    int mid=(l+r)>>1;
    if(ll<=mid&&rr>mid)return qq(ll,rr,l,mid,o*2)+qq(ll,rr,mid+1,r,o*2+1);
    if(ll<=mid)return qq(ll,rr,l,mid,o*2);
    return qq(ll,rr,mid+1,r,o*2+1);
}
void build(int l=0,int r=2*n+1,int o=1){
    sgt[o]=tag[o]=0;stt[o]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(l,mid,o*2);
    build(mid+1,r,o*2+1);
}
void add(int ll,int rr,int l=0,int r=2*n+1,int o=1){
    if(rr>sgt[o])sgt[o]=rr,tag[o]=ll;
    if(l==r)return void();
    int mid=(l+r)>>1;
    if(ll<=mid)add(ll,rr,l,mid,o*2);
    else add(ll,rr,mid+1,r,o*2+1);
}
std::pair<int,int>qu(int ll,int rr,int vv,int l=0,int r=2*n+1,int o=1){
	if(sgt[o]<vv)return {-1e9,-1e9};
    if(l==r)return {tag[o],sgt[o]};
    int mid=(l+r)>>1;
    if(ll<=l&&rr>=r){
        if(sgt[o*2+1]>vv)return qu(ll,rr,vv,mid+1,r,o*2+1);
        return qu(ll,rr,vv,l,mid,o*2);
    }
    if(ll<=mid&&rr>mid)return std::max(qu(ll,rr,vv,l,mid,o*2),qu(ll,rr,vv,mid+1,r,o*2+1));
    if(ll<=mid)return qu(ll,rr,vv,l,mid,o*2);
    return qu(ll,rr,vv,mid+1,r,o*2+1);
}
int lto[2000005];
void Main(){
    scanf("%d",&n);ans=q[n],ak[0]=2*n;build();add(0,2*n+1);
    
    printf("%d ",ans);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l,&r);
        std::pair<int,int> x=qu(0,l,r);
		int su=qq(l,r);add(l,r);lto[l]=i;int xx=lto[x.first];
        ak[i]=r-l-1-su;ans=1ll*ans*(q[ak[i]/2])%mod;aa(r,ak[i]+2);aa(x.second,-ak[i]-2);
        ans=1ll*ans*qv[ak[xx]/2]%mod;ak[xx]-=ak[i]+2;ans=1ll*ans*q[ak[xx]/2]%mod;
        printf("%d ",ans);
    }
    puts("");
}
int mul(int a,int x){
    if(!x)return 1;
    int t=mul(a,x/2);
    if(x%2)return 1ll*t*t%mod*a%mod;
    return 1ll*t*t%mod;
}
int main(){
    inv[0]=q[0]=qv[0]=inv[1]=1;
    for(int i=1;i<=5e5;i++)inv[i+1]=mul(i+1,mod-2),q[i]=1ll*q[i-1]*(2*i)%mod*(2*i-1)%mod*inv[i]%mod*inv[i+1]%mod,qv[i]=mul(q[i],mod-2);
    int t;
    scanf("%d",&t);
    while(t--)Main();
}

```

---

## 作者：沉石鱼惊旋 (赞：1)

# F1 题解链接

<https://www.luogu.com.cn/article/1t5fdtp8>

# 题目翻译

我们称可以用以下操作生成的括号串为一个『合法括号串』：

1. 空串。
2. 如果串 $A$ 是『合法括号串』，那么 $\texttt{(}A\texttt{)}$ 也是一个『合法括号串』。
3. 如果串 $A$ 和串 $B$ 都是『合法括号串』，那么 $AB$ 也是一个『合法括号串』。

现在有一个隐藏的长度恰好为 $2n$ 的『合法括号串』$s$。依次有 $n$ 条信息，每条信息给出 $l,r$ 表示 $s_l=\texttt{(},s_r=\texttt{)}$ 且 $s_l,s_r$ 是通过操作 2 被**同时**添加的一对括号。

回答 $n+1$ 个问题：

- 第一个问题回答没有给定任何信息时 $s$ 的所有可能情况。
- 第 $i+1$ 个问题回答给定前 $i$ 条信息时 $s$ 的所有可能情况。

答案对 $998244353$ 取模。

**本题为 Hard Version。**

多测。

$1\leq t\leq 10^4$，$2\leq n,\sum n\leq 3\times 10^5$，$1\leq l_i\lt r_i\leq 2n$。

# 题目思路

关于前置的做法相关请先阅读 F1 题解。本文着重讲对 F1 的暴力做法的数据结构优化。

F1 的瓶颈在于我们暴力的做了后缀加法和查询父亲括号。

我们把这个事情重新描述一遍。我们需要做的是：

> 维护序列 $a$ 和标记序列 $f$，支持以下操作：
>
> 1. 给定 $x$，对 $[x,n]$ 做 $+1$ 或 $-1$。
> 1. 给定 $x$，求点 $x$ 的值。
> 1. 给定 $x,rk$。求最大的 $y$ 满足 $y<x$ 且点 $y$ 的值为 $rk-1$ 且 $f_y=1$。
> 1. 给定 $x$，$f_x\gets 0$。
> 1. 给定 $x$，$f_x\gets 1$。

这个东西看上去很复杂，我们直接考虑分块。设块长为 $B$。

操作 1 和操作 2 的分块属于是大炮打蚊子了。操作 1 散块暴力操作 $a_i\gets a_i+1$ 或 $a_i\gets a_i-1$ 之后重构这一块，整块打标记。操作 2 就是查询这一个位置的值即 $a_i+tag_{bel_i}$。

操作 3 我们需要知道某一块中是否存在值恰好为 $x$ 的数。如果有的话我们直接在这一块中找答案。我们对每一块维护一个长度为 $\mathcal O(n)$ 的桶表示这一块的这个值出现了几次。但是空间 $\mathcal O(n^2/B)$ 爆炸，不难发现这一块之间极差只有 $\mathcal O(B)$。我们记录每个元素与这一块第一个值的差的桶即可。重构一个块以及操作 3 的查找分别是 $\mathcal O(B)$ 和 $\mathcal O(n/B)$ 的。

操作 4 和操作 5 我们直接 $\mathcal O(1)$ 的修改这个块的桶的某个位置即可。

这样子我们就得到了一份 $\mathcal O(n\sqrt n)$ 的代码。但是这里 $n$ 自带 $2$ 倍常数，删除一堆括号的时候还有约 $3$ 次的根号复杂度的查询 / 修改，很遗憾 TLE 了。

但是我坚信分块是有前途的，于是我卡了一晚上的常。

发现一个惊人的事情：**我们的 $f$ 只会修改左括号位置上的值**。只有后缀加法的操作可能会从右括号开始。

但是，这一点也不影响。我们直接对左括号离散化，右括号找自己后面下一个左括号的位置，从这里开始修改。

这样子的 $\mathcal O(n\sqrt n)$ 的复杂度就是可行的了。

# 代码链接

[CF submission 302499400](https://codeforces.com/contest/2063/submission/302499400)

只加了离散化左括号，没有其他卡常。

---

## 作者：ChrysanthBlossom (赞：1)

感觉比官解可能简单不少吧（主要是感觉官解好长，各种操作奇奇怪怪的，再加上超过翻译限制了完全看不下去），虽然应该很多人都是这样。

首先根据 F1，可以把树建出来，这样方案数的计算方式为设第 $i$ 个点子树内未被安排好的位置的数量为 $siz_i$（我们认为未被添加的点的 $siz$ 为 $0$），则最终答案一定为 $\prod^{n}_{i=1}C_{\frac{siz_i}{2}}$，这里 $C_i$ 在 $i \neq 0$ 时为卡特兰数，在 $i = 0$ 时为 $1$。

那么考虑新添加一个 $u$ pair 会对已经添加的点的 $siz$ 产生怎样的贡献。可以发现此时只会对此时的 $u$ 外层的第一个 pair（记为 $v$）的 siz 产生影响，而这个对应到树上恰好就是 $u$ 的最近已被访问过的祖先。这个用树剖可以单次 $O(\log^2n)$。把 $siz_v$ 对应着更新一下即可。但更好的方法是先处理出每个点添加的时间，然后在 dfs 的时候把 dep 放到线段树上，最后相当于是求 dep 最大的时间小于等于某个值的祖先，直接线段树二分即可。

那么对于未被添加进来的祖先呢？显然此刻是没有贡献的（因为其 $siz$ 为 $0$），但当未来添加他们的时候他们的 $siz$ 就不再是树上那个 $siz$ 直接拿过来了。考虑直接拿个数据结构维护出来每个点的 $siz$，若是已有的点就是它真正的 $siz$，若不是已有的点就是它未来添加进来的时候的那个初始的 $siz$。显然只有 $u \to v$ 上的祖先会受影响（因为 $u$ 上边的祖先已经在取 $u$ 的时候摘除了），影响即是减掉一个 $siz_u$，这个当然也可以树剖维护，但用树状数组会更方便。

最后时间复杂度 $O(n \log n+n \log V)$，$\log V$ 是求逆元的，搞掉很容易。[submission](https://codeforces.com/contest/2063/submission/302530731)

---

## 作者：xyvsvg (赞：0)

不难注意到，在一个平衡序列中新增一个好队并不影响合法性，即每个同深度的好队是独立的，于是把序列建成括号数处理。

不妨倒序考虑答案，则我们不断删除限制，在树上的体现为不断删去一个点并将他的儿子合并到父亲。对于无限制的区间，使用卡特兰数处理答案。

可以使用并查集维护区间合并关系，复杂度为 $O(n\log n)$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,N=2e6+10;
int fac[N+10],inv[N+10],finv[N+10];
inline int Cat(int n)
{
    n>>=1;
    return 1LL*inv[n+1]*fac[n*2]%mod*finv[n]%mod*finv[n]%mod;
}
inline int iCat(int n)
{
    n>>=1;
    return (n+1LL)*finv[n*2]%mod*fac[n]%mod*fac[n]%mod;
}
struct Dsu
{
    int n;
    vector<int>fa;
    Dsu(int n_)
    {
        n=n_;
        fa.resize(n+10);
        iota(fa.begin(),fa.end(),0);
    }
    int fr(int x)
    {
        while(x!=fa[x])
            x=fa[x]=fa[fa[x]];
        return x;
    }
    void unite(int x,int y)
    {
        fa[fr(x)]=fr(y);
    }
};
void solve()
{
    int n;
    cin>>n;
    vector<int>a(n*2+10);
    vector<int>rg(n+10);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        cin>>x>>y;
        a[x]=a[y]=i;
    }
    vector<int>fa(n+10);
    {
        stack<int>sta;
        vector<bool>vis(n*2+10);
        for(int i=0;i<=n*2+1;++i)
        {
            if(vis[a[i]])
                while(sta.top()!=a[i])
                    fa[sta.top()]=a[i],sta.pop();
            else
                sta.push(a[i]),vis[a[i]]=1;
        }
    }
    int res=1;
    vector<int>ans;
    Dsu dsu(n);
    for(int i=n;~i;--i)
    {
        int d=dsu.fr(i),f=dsu.fr(fa[d]);
        ans.push_back(res);
        res=1LL*res*iCat(rg[d])%mod*iCat(rg[f])%mod;
        res=1LL*res*Cat(rg[f]+=rg[d]+2)%mod;
        dsu.unite(d,f);
    }
    reverse(ans.begin(),ans.end());
    for(int x:ans)
        cout<<x<<' ';
    cout<<endl;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fac[0]=inv[1]=finv[0]=1;
    for(int i=2;i<=N;++i)
        inv[i]=1LL*(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1;i<=N;++i)
        fac[i]=1LL*fac[i-1]*i%mod,
        finv[i]=1LL*finv[i-1]*inv[i]%mod;
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

## 作者：ax_by_c (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/axbyc/articles/18732221)

题意：有一个长度为 $2n$ 的空括号序列，每次加入一对括号，求一开始和每次加入后补全空的部分使得整个括号序列合法且每次加入的括号恰好匹配的方案数，对 $998244353$ 取模，Easy Version $2\le n,\sum n\le5000$，Hard Version $2\le n,\sum n\le3\times 10^5$。

## 卡特兰数

先复习一下卡特兰数。

有一个网格图，你一开始在 $(0,0)$，要走到 $(2n,0)$。设你在 $(x,y)$，那么你下一步可以走到 $(x+1,y-1)$ 和 $(x+1,y+1)$，并且你不能走到直线 $y=0$ 的下方，求方案数 $C_n$。

考虑用 $\binom{2n}{n}$ 减去不符合限制的方案数。如果一个方案不合法，那么一定有一个时刻满足 $y=-1$。将路径中从 $(0,0)$ 走到这个位置的部分关于 $y=-1$ 对称，那么就能得到一条从 $(0,-2)$ 走到 $(2n,0)$ 的路径。

注意到对于任意一条从 $(0,-2)$ 走到 $(2n,0)$ 的路径，也一定有一个时刻满足 $y=-1$。同样将路径中从 $(0,-2)$ 走到这个位置的部分关于 $y=-1$ 对称，那么就能得到一条从 $(0,0)$ 走到 $(2n,0)$ 的不符合限制的路径。也就是说从 $(0,0)$ 走到 $(2n,0)$ 的不合法路径与从 $(0,-2)$ 走到 $(2n,0)$ 的路径一一对应。

于是有关键结论：不合法方案数等于从 $(0,-2)$ 走到 $(2n,0)$ 的方案数。而从 $(0,-2)$ 走到 $(2n,0)$ 的方案数即为 $\binom{2n}{n+1}$，因此 $C_n=\binom{2n}{n}-\binom{2n}{n+1}$。

## F1

为了方便直接在最外面加上一层括号。

加入括号相当于将里面和外面分成两部分，将内部括号包含部分忽略后内部方案数即为卡特兰数。

可以先建出括号结构树，然后每次暴力即可，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int mod=998244353;
const int N=1e4+5;
int ksm(int a,int b,int p){
	a=a%p;
	int r=1;
	while(b){
		if(b&1)r=(ll)r*a%p;
		a=(ll)a*a%p;
		b>>=1;
	}
	return r%p;
}
int fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(ll)fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	for(int i=n;i>=1;i--)inv[i-1]=(ll)inv[i]*i%mod;
}
int C(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return (ll)fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int CC(int n){
	return (C(n,n/2)-C(n,n/2+1)+mod)%mod;
}
int n,l[N],r[N],mch[N];
vector<int>g[N];
bool mk[N];
void bld(int l,int r){
	int pos=l+1;
	while(pos<r){
		g[l].push_back(pos);
		bld(pos,mch[pos]);
		pos=mch[pos]+1;
	}
}
pii cal(int l,int r){
	pii res={1,0};
	for(auto v:g[l]){
		pii tmp=cal(v,mch[v]);
		res.first=(ll)res.first*tmp.first%mod;
		res.second+=tmp.second;
	}
	if(mk[l])res.first=(ll)res.first*CC(r-l-1-res.second)%mod,res.second=r-l+1;
	return res;
}
void slv(){
	scanf("%d",&n);
	Init(n*2);
	mch[0]=n*2+1,mch[n*2+1]=0;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&l[i],&r[i]);
		mch[l[i]]=r[i],mch[r[i]]=l[i];
	}
	for(int i=0;i<=n*2+1;i++)g[i].clear(),mk[i]=0;
	bld(0,n*2+1);
	mk[0]=1;
	printf("%d ",cal(0,n*2+1).first);
	for(int i=1;i<=n;i++){
		mk[l[i]]=1;
		printf("%d ",cal(0,n*2+1).first);
	}
	putchar('\n');
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

## F2

加入括号看着就很难做，考虑时光倒流一下变成删除括号，那么只有删除前的实际父亲（忽略删除括号后括号结构树上的父亲）处出现变化，使用并查集维护一下实际父亲即可。

懒得精细实现了，是 $O(n\log n)$ 的，可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int mod=998244353;
const int N=6e5+5;
int ksm(int a,int b,int p){
	a=a%p;
	int r=1;
	while(b){
		if(b&1)r=(ll)r*a%p;
		a=(ll)a*a%p;
		b>>=1;
	}
	return r%p;
}
int fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(ll)fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	for(int i=n;i>=1;i--)inv[i-1]=(ll)inv[i]*i%mod;
}
int C(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return (ll)fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int CC(int n){
	return (C(n,n/2)-C(n,n/2+1)+mod)%mod;
}
int n,l[N],r[N],mch[N],fa_[N],fa[N],len[N],res[N],ans,pr[N];
vector<int>g[N];
void bld(int l,int r){
	int pos=l+1;
	while(pos<r){
		g[l].push_back(pos);
		fa_[pos]=l;
		bld(pos,mch[pos]);
		pos=mch[pos]+1;
	}
	len[l]=r-l-1;
}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void rm(int l,int r){
	ans=(ll)ans*ksm(res[l],mod-2,mod)%mod;
	fa[l]=fa_[l];
	ans=(ll)ans*ksm(res[find(l)],mod-2,mod)%mod;
	len[find(l)]-=r-l+1-len[l];
	res[find(l)]=CC(mch[find(l)]-find(l)-1-len[find(l)]);
	ans=(ll)ans*res[find(l)]%mod;
}
void slv(){
	scanf("%d",&n);
	Init(n*2);
	mch[0]=n*2+1,mch[n*2+1]=0;
	for(int i=1;i<=n;i++){
		scanf("%d %d",&l[i],&r[i]);
		mch[l[i]]=r[i],mch[r[i]]=l[i];
	}
	for(int i=0;i<=n*2+1;i++)g[i].clear(),fa_[i]=0,fa[i]=i,len[i]=0,res[i]=1;
	bld(0,n*2+1);
	ans=1;
	for(int i=n;i>=1;i--){
		pr[i]=ans;
		rm(l[i],r[i]);
	}
	pr[0]=ans;
	for(int i=0;i<=n;i++)printf("%d ",pr[i]);
	putchar('\n');
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

CF 100 红题祭。

考虑加上一对括号实际上是把包在他外面的那一对括号内部的段分成中间和两边的两个连续段。现在只需要知道两个东西：一是包含他的括号是谁，二是两段的长度是多少。

维护一个线段树表示一个点被括号包的次数，那么修改相当于区间加。设一次操作的时候 $[l,r]$ 端点的值是 $k$，那么第一个操作相当于找到 $l$ 左边最后一个小于 $k$ 的数和 $r$ 右边第一个小于 $k$ 的数。这个是很好做的。第二问相当于找一个区间有多少个 $k$，注意到 $k$ 是区间最小值，而区间最小值出现次数是很好维护的。

你写完了代码，然后发现过不去。这是因为比如我两次操作分别操作了 $[1,6]$ 和 $[7,12]$，那么我就分辨不出这两个操作了。解决方法也很简单，只要在保证最小值性质的情况下让每次增加的值不同即可。于是我采用了第 $i$ 次操作区间加 $i$ 的方法。

别忘了 F1 改成 F2 的时候阶乘数组也要扩大。

---

## 作者：int08 (赞：0)

## 前言
启发式分裂，超劣复杂度，大家都喜欢。
# Solution
### F1 Solution
首先初始答案是卡特兰数。

考虑添加的第一对括号，题目中的条件等价于强制这两个括号匹配的方案数。

发现：这等价于两个括号中间匹配且去除这两个括号之间的一切之后剩下的部分匹配，于是此时两部分（中间，两边）就变成了两个独立的问题，对于接下来的括号，我们只需要找到它属于哪一个部分，并继续分裂这个部分，答案便是每个部分的乘积。

每次暴力处理这个分裂即可做到 $O(n^2)$ 的复杂度。
### F2 Solution

每次暴力分裂还是太劣了，考虑启发式分裂：每次只将小的部分分裂出去，大的留在原地，但是如何知道哪部分小呢？考虑每一个部分用一个集合维护：内部装着该部分所有点，分裂时查询 $l,r$ 的排名作差即可知道中间有多少元素，也就知道该怎么分裂了。

由于需要支持动态插入删除求排名和前驱后继，考虑使用平衡树，最终复杂度 $O(n\log^2n)$，证明同启发式合并，使用 `pb_ds` 可以大幅简化代码。

不卡常，大家都很高兴。
## AC Code


```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define N 616414
#define mod 998244353
using namespace std;
using namespace __gnu_pbds;
int n,T,i,l,r,C[N],a[N],ans,x;
int qp(int x,int y)
{
	int ans=1;
	while(y) y&1?ans=1ll*ans*x%mod:0,y>>=1,x=1ll*x*x%mod;
	return ans;
}
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> t[N];
int main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>T;
	C[0]=1;
	for(i=1;i<N;i++) C[i]=1ll*C[i-1]*(4*i-2)%mod*qp(i+1,mod-2)%mod;
	while(T--)
	{
		cin>>n;ans=C[n];
		cout<<C[n]<<" ";
		for(i=1;i<=n+1;i++) t[i].clear();
		for(i=1;i<=2*n;i++) t[1].insert(i),a[i]=1;
		for(i=1;i<=n;i++)
		{
			cin>>l>>r;int c=a[l];ans=1ll*ans*qp(C[t[c].size()/2],mod-2)%mod;
			int pl=t[c].order_of_key(l)+1,pr=t[c].order_of_key(r)+1;
			#define upd x=*it,it++,a[x]=i+1,t[c].erase(x),t[i+1].insert(x)
			if((pr-pl-1)*2<=t[c].size()-2)
			{
				auto it=t[c].upper_bound(l);
				while(*it!=r) upd;
			}
			else
			{
				auto it=t[c].begin();
				while(*it!=l) upd;
				it=t[c].upper_bound(r);
				while(it!=t[c].end()) upd;
			}
			t[c].erase(l),t[c].erase(r);
			ans=1ll*ans*C[t[c].size()/2]%mod*C[t[i+1].size()/2]%mod;
			cout<<ans<<" ";
		}
		cout<<endl;
	}
}
```

---

## 作者：gyyyyx (赞：0)

注意到没有限制的时候就是卡特兰数。

现在加一条限制 $(l,r)$。

那么 $(l,r)$ 中的括号必然是一个合法括号串，而如果把 $[l,r]$ 中的所有括号全部删去，剩下的括号顺次拼接也一定是合法括号串。

我们称一条限制 $(l,r)$ 的长度为 $r-l+1$。

那么我们很容易得到对于一个限制 $(l,r)$，设被这个限制包含的已经加入的限制集合为 $S$。

我们称在 $S$ 中且不被 $S$ 中的限制包含的限制为限制 $(l,r)$ 的最长独立子限制。

设限制 $(l,r)$ 的最长独立子限制的长度之和为 $len$。

则该限制对答案的贡献是 $C[\frac{r-l-1-len}{2}]$。

其中 $C[i]$ 是卡特兰数的第 $i$ 项。

我们在一开始就加入限制 $(0,2n+1)$，并将所有限制的贡献乘起来就是答案。

比如现在有限制 $(1,6)$ 和 $(2,3)$ 和 $(7,8)$，我们一开始先加入限制 $(0,13)$，那么答案就是 $C[\frac{12-6-2}{2}]\times C[\frac{4-2}{2}]\times C[\frac{0}{2}]\times C[\frac{0}{2}]=C[2]\times C[1]\times C[0]\times C[0]=2$。

对于 Easy Version，我们直接每加一条限制就 $O(n)$ 算答案就行了。

对于 Hard Version，考虑每加入一条限制就在原答案基础上修改得到新答案。

我们称包含一条限制 $(l,r)$ 且长度最小的已经加入的限制为限制 $(l,r)$ 的最短祖先限制，包含一条限制 $(l,r)$ 且长度最小的限制为限制 $(l,r)$ 的父限制。

显然我们加入一条限制会影响到最短祖先限制的贡献，同时会加入当前限制的贡献。

那我们其实只需要找到当前限制的最长独立子限制的长度和即可。

然而我们直接在每次加入限制之后寻找最长独立子限制并不好维护。

考虑动态维护所有限制（包括未加入的限制）的最长独立子限制的长度和（注意未加入的限制的最长独立子限制是已加入的限制的子集）。

考虑把所有限制和其父限制连边，那么会得到一棵树。

我们先把所有点点权设为该点对应限制的长度除以 $2$ 减 $1$，也就是 $\frac{r-l+1}{2}-1=\frac{r-l-1}{2}$。

那我们加入一条限制之后会影响到的限制为该限制的父限制到其最短祖先限制的链上的所有限制。

具体的，设该限制的长度为 $len$，其最长独立子限制的长度和为 $d$，那么链上所有点的点权都要减去 $\frac{len-d}{2}$。

那这就变成了树上链加法的问题，可以用 dfs 序加差分加树状数组解决。

然后找最短祖先限制可以用线段树解决。

建树的话可以用一个栈维护当前链，类似于笛卡尔树，当然线段树带 $\log$ 建树也不是不行。

时间复杂度 $O(n\log n)$。

感觉还是复杂了，应该有更优秀的做法的。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mod 998244353
#define N 300005
using namespace std;
LL fpow(LL a,LL b){
	if(!b) return 1;
	LL t(fpow(a,b>>1));
	if(b&1) return t*t%mod*a%mod;
	return t*t%mod;
}
int _,n,len[N];LL c[N],invc[N];
bool can[N<<1];array <int,2> a[N<<1];
stack <array <int,2> > id;
struct Edge{
	int nxt,to;
	Edge(int a=0,int b=0):nxt(a),to(b){}
} e[N<<1];
int head[N],cnt;
inline void AddEdge(int x,int y){
	e[++cnt]=Edge(head[x],y);head[x]=cnt;
}
int idx,dfn[N],siz[N],fa[N],dep[N];
void DFS(int u,int d=1){
	dfn[u]=++idx;siz[u]=1;dep[u]=d;
	for(int i(head[u]);i;i=e[i].nxt){
		int v(e[i].to);DFS(v,d+1);
		siz[u]+=siz[v];fa[v]=u;
	}
}
int p[N];
inline int lowbit(int x){return x&-x;}
inline void Add(int x,int v){
	while(x<=idx){
		p[x]+=v;
		x+=lowbit(x);
	}
}
inline int Sum(int x){
	int sum(0);
	while(x){
		sum+=p[x];
		x-=lowbit(x);
	}
	return sum;
}
int flg[N<<2];
void Update(int k,int l,int r,int s,int t,int v){
	if(s<=l&&r<=t){
		if(dep[v]>dep[flg[k]]) flg[k]=v;
		return;
	}
	int ls(k<<1),rs(k<<1|1),mid(l+r>>1);
	if(s<=mid) Update(ls,l,mid,s,t,v);
	if(t>mid) Update(rs,mid+1,r,s,t,v);
}
int Query(int k,int l,int r,int x){
	if(l==r) return flg[k];
	int ls(k<<1),rs(k<<1|1),mid(l+r>>1),tmp;
	if(x<=mid) tmp=Query(ls,l,mid,x);
	else tmp=Query(rs,mid+1,r,x);
	return dep[flg[k]]>dep[tmp]?flg[k]:tmp;
}
int main(){
	c[0]=invc[0]=1;for(int i(1);i<N;++i)
		invc[i]=fpow(c[i]=c[i-1]*(4*i-2)%mod*fpow(i+1,mod-2)%mod,mod-2);
	scanf("%d",&_);
	while(_--){
		scanf("%d",&n);
		for(int i(1);i<=n;++i){
			int l,r;scanf("%d%d",&l,&r);
			can[l]=1;can[r]=0;a[l]={r,i};
			len[i]=(r-l-1>>1);
		}
		fill(head+1,head+n+2,0);cnt=0;
		while(!id.empty()) id.pop();
		id.push({(n<<1)+1,n+1});
		for(int i(1);i<=(n<<1);++i)
			if(can[i]){
				while(i>id.top()[0]) id.pop();
				AddEdge(id.top()[1],a[i][1]);
				id.push(a[i]);
			}
		idx=0;DFS(n+1);fill(p+1,p+idx+1,0);
		memset(flg,0,sizeof(flg));
		Add(1,n);Update(1,1,idx,1,idx,n+1);
		LL ret(c[n]);printf("%lld ",ret);
		for(int t(1);t<=n;++t){
			int f(Query(1,1,idx,dfn[t]));
			Update(1,1,idx,dfn[t],dfn[t]+siz[t]-1,t);
			int k(Sum(dfn[f]+siz[f]-1)-Sum(dfn[f]-1));
			Add(dfn[t],len[t]);Add(dfn[fa[t]],-len[t]);
			int d(Sum(dfn[t]+siz[t]-1)-Sum(dfn[t]-1)+1);
			Add(dfn[fa[t]],-d);if(f^n+1) Add(dfn[fa[f]],d);
			ret=ret*c[d-1]%mod*invc[k]%mod*c[k-d]%mod;
			printf("%lld ",ret);
		} puts("");
	}
	return 0;
}
```

---

