# [SEERC 2020] AND = OR

## 题目描述

一个数组 $b$ 被称为“好的数组”当且仅当可以将 $b$ 划分为两个非空的子数组，这两个子数组中第一个子数组的 $\mathtt{OR}$ 结果与第二个子数组的 $\mathtt{AND}$ 结果相等，例如 $\{1,7,3,11\}$，将其划分为 $\{1,3\}$ 与 $\{7,11\}$，$1\ \mathtt{OR}\ 3 = 3$，$7\ \mathtt{AND}\ 11 = 3$，所以它是一个好的数组。

现在给定一个长度为 $n$ 的数组 $a$，$q$ 组询问，每次给定 $[l,r]$，问 $\{a_l, a_{l+1},\ldots,a_{r-1},a_{r}\}$ 是不是一个好的数组。

## 样例 #1

### 输入

```
5 15
0 1 1 3 2
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5```

### 输出

```
NO
NO
YES
YES
YES
NO
YES
YES
YES
NO
NO
YES
NO
NO
NO```

# 题解

## 作者：oh_my_shy (赞：6)

给出一个单 $\log$ 的离线做法。

考虑枚举 OR 和 AND 相等的那个值是什么。

直接枚举值复杂度不可承受，寻找一个和原值具有相似性质且小值域的东西。

枚举 $\operatorname{popcount}$。不断加入新元素的过程中，序列 OR $\operatorname{popc}$ 单调不降，序列 AND $\operatorname{popc}$ 单调不增。（$\operatorname{popc}$ 简写）

设 OR 和 AND 的 $\operatorname{popcount}$ 都等于 $p$，那么所有 $\operatorname{popc}(a_i)<p$ 的都应该放进 OR，$\operatorname{popc}(a_i)>p$ 的都应该被放进 AND。

$\operatorname{popc}(a_i)<p$ 的部分，相当于是 $\operatorname{popc}(a_i)=p$ 的前缀 OR（取 $p-1$ 位置）。
对每一个二进制位建一个线段树，处理出区间 $[l,r]$ 在 $p\in[0,30]$ 上的前缀 OR。判这个前缀 OR 是否是空集可以线段树顺便维护一个区间个数和，然后算个数和的前缀和。$\operatorname{popc}(a_i)>p$ 的后缀 AND 同理。

考虑 $\operatorname{popc}(a_i)=p$ 的情况。

显然多次 OR 或 AND 同一个数不会再次改变值，先关注数的种类。

若 $\operatorname{popc}(a_i)=p$ 的 $a_i$ 只有一种数，全给 OR、全给 AND、若个数 $\ge 2$ 可以两个都给，枚举三种情况。
+ 这里只需要查 $\ge 2$，可以预处理每个数向后第一个相等位置，判断位置 $\le r$。

若有两种数，对于 $a_i\ne a_j,\,\operatorname{popc}(a_i)=\operatorname{popc}(a_j)$，有 $\operatorname{popc}(a_i\,|\,a_j)>\operatorname{popc}(a_i)=p,\,\operatorname{popc}(a_i\,\&\,a_j)<\operatorname{popc}(a_i)=p$，根据前面 OR 只能放 $\operatorname{popc}<p$ 的讨论，AND 对称同理，所以两种数一定只能各自给其中一边，设两种数是 $a_i,\,a_j$，OR 和 AND 的 $\operatorname{popc}$ 一定分别是 $\ge p$ 和 $\le p$ 的，$a_i=a_j$ 时两个 $\operatorname{popc}$ 才有可能取等，这与 $a_i\ne a_j$ 矛盾。所以两种数一定不合法。

对于三种及以上，同样不会合法，所以种类要 $\le 1$。

预处理枚举到每个 $\operatorname{popcount}=p$ 时每个位置向后两个互不相同且 $\operatorname{popc}=p$ 的数，就可以判上述情况了。

复杂度 $O(n\log V+q\log V\log n)$。

考虑优化，瓶颈在于 $\log V$ 个线段树每次询问时的查询。

考虑分治，将询问离线挂在分治树上，每次处理跨过当前分治区间 $mid$ 的询问，猫树的思想，将询问 $[ql,qr]$ 拆为 $[l,mid]$ 上的后缀 $[ql,mid]$，和 $[mid+1,r]$ 上的前缀 $[mid+1,qr]$，直接扫过 $[l,mid$] 得到每个后缀的答案，贡献到询问上，$[mid+1,r]$ 同理。

时间复杂度 $O(n\log n+ q\log V)$。

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, f, t) for (int i(f); i <= t; ++i)
#define re(i, t) for (int i(1); i <= t; ++i)
#define per(i, t, f) for (int i(t); i >= f; --i)
#define pe(i, t) for (int i(t); i >= 1; --i)
typedef pair<int, int> pii;
#define pb push_back
#define mkp make_pair
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define fi first
#define se second
const int N = 1e5 + 5;
int n, Q, a[N], pc[N];
int ini[N];
int A[31], B[31], Ac[31], Bc[31], C[31];
using Pos = tuple<int, int>;
Pos P[31][N];
int nxt[N];
map<int, int> buc;
pii qry[N];
vector<int> t[N * 4];
void putqry(int rt, int l, int r, int ql, int qr, int id)
{
    if (l == r)
    {
        t[rt].pb(id);
        return;
    }
    int mid = (l + r) / 2;
    if (qr <= mid)
    {
        putqry(ls(rt), l, mid, ql, qr, id);
        return;
    }
    if (ql > mid)
    {
        putqry(rs(rt), mid + 1, r, ql, qr, id);
        return;
    }
    t[rt].pb(id);
}
struct Dat
{
    int Or, And, cnt;
} Res[31][N];
int tmp[31];
vector<int> vec[N];
void work(int rt, int l, int r)
{
    if (l == r)
    {
        for (int id : t[rt])
        {
            Res[pc[l]][id].Or |= a[l];
            Res[pc[l]][id].And &= a[l];
            Res[pc[l]][id].cnt++;
        }
        return;
    }
    int mid = (l + r) / 2;

    for (int id : t[rt])
        vec[qry[id].fi].pb(id), vec[qry[id].se].pb(id);
    rep(i, 0, 30) tmp[i] = 0;
    rep(i, mid + 1, r)
    {
        tmp[pc[i]] |= a[i];
        for (int id : vec[i])
            rep(p, 0, 30) Res[p][id].Or |= tmp[p];
    }
    rep(i, 0, 30) tmp[i] = 0;
    per(i, mid, l)
    {
        tmp[pc[i]] |= a[i];
        for (int id : vec[i])
            rep(p, 0, 30) Res[p][id].Or |= tmp[p];
    }
    rep(i, 0, 30) tmp[i] = (1 << 30) - 1;
    rep(i, mid + 1, r)
    {
        tmp[pc[i]] &= a[i];
        for (int id : vec[i])
            rep(p, 0, 30) Res[p][id].And &= tmp[p];
    }
    rep(i, 0, 30) tmp[i] = (1 << 30) - 1;
    per(i, mid, l)
    {
        tmp[pc[i]] &= a[i];
        for (int id : vec[i])
            rep(p, 0, 30) Res[p][id].And &= tmp[p];
    }
    rep(i, 0, 30) tmp[i] = 0;
    rep(i, mid + 1, r)
    {
        tmp[pc[i]]++;
        for (int id : vec[i])
            rep(p, 0, 30) Res[p][id].cnt += tmp[p];
    }
    rep(i, 0, 30) tmp[i] = 0;
    per(i, mid, l)
    {
        tmp[pc[i]]++;
        for (int id : vec[i])
            rep(p, 0, 30) Res[p][id].cnt += tmp[p];
    }
    for (int id : t[rt])
        vec[qry[id].fi].clear(), vec[qry[id].se].clear();

    work(ls(rt), l, mid);
    work(rs(rt), mid + 1, r);
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> Q;
    re(i, n) cin >> a[i];
    pe(i, n)
    {
        nxt[i] = buc[a[i]];
        if (nxt[i] == 0)
            nxt[i] = n + 1;
        buc[a[i]] = i;
    }
    re(i, n) pc[i] = __builtin_popcount(a[i]);
    rep(p, 0, 30)
    {
        re(i, n)
        {
            if (pc[i] == p)
                ini[i] = a[i];
            else
                ini[i] = -1;
        }
        Pos now = make_tuple(n + 1, n + 1);
        pe(i, n)
        {
            if (ini[i] != -1)
            {
                int u = 0, v = 0;
                tie(u, v) = now;
                if (u == n + 1)
                    u = i;
                else if (v == n + 1)
                {
                    if (a[u] == a[i])
                        u = i;
                    else
                        v = u, u = i;
                }
                else
                {
                    if (a[u] == a[i])
                        u = i;
                    else if (a[v] == a[i])
                        v = u, u = i;
                    else
                        v = u, u = i;
                }
                now = tie(u, v);
            }
            P[p][i] = now;
        }
    }
    re(i, Q)
    {
        int l = 0, r = 0;
        cin >> l >> r;
        qry[i] = mkp(l, r);
        putqry(1, 1, n, l, r, i);
    }
    rep(p, 0, 30) re(i, Q)
    {
        Res[p][i].Or = 0;
        Res[p][i].And = (1 << 30) - 1;
        Res[p][i].cnt = 0;
    }
    work(1, 1, n);
    re(qid, Q)
    {
        int l = 0, r = 0;
        tie(l, r) = qry[qid];
        if (l == r)
        {
            cout << "NO\n";
            continue;
        }
        rep(p, 0, 30)
        {
            Dat tt = Res[p][qid];
            A[p] = tt.Or, B[p] = tt.And;
            Ac[p] = Bc[p] = C[p] = tt.cnt;
        }
        rep(p, 1, 30) A[p] |= A[p - 1], Ac[p] += Ac[p - 1];
        per(p, 29, 0) B[p] &= B[p + 1], Bc[p] += Bc[p + 1];
        int Ans = 0;
        rep(p, 0, 30)
        {
            int As = 0, Bs = (1 << 30) - 1, tA = 0, tB = 0;
            if (p > 0)
                As = A[p - 1], tA = (Ac[p - 1] > 0);
            if (p < 30)
                Bs = B[p + 1], tB = (Bc[p + 1] > 0);
            int Cnt = 0;
            int u = 0, v = 0;
            tie(u, v) = P[p][l];
            Cnt = (u <= r) + (v <= r);
            u = min(u, r);
            v = min(v, r);
            if (Cnt == 0)
            {
                if (As == Bs && tA && tB)
                {
                    Ans = 1;
                    break;
                }
            }
            if (Cnt == 1)
            {
                int ok = (((As | a[u]) == Bs && tB) | (As == (Bs & a[u]) && tA));
                if (nxt[u] <= r)
                    ok |= ((As | a[u]) == (Bs & a[u]));
                if (ok)
                {
                    Ans = 1;
                    break;
                }
            }
        }
        if (Ans)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：_maojun_ (赞：5)

一个比较劣的做法。

---

一个显然的判定方法是把区间所有数排序，判断是否存在一个断点，使得前面的 OR 等于后面的 AND。

如果提出区间的 trie，暴力递归全树，记录前缀 OR 和后缀 AND，可以做到单次 $O(V)$。注意到前缀 OR 和后缀 AND 只有 $O(\log V)$ 种，在合法的时候往下递归，查询复杂度就是单次 $O(\log^2V)$。

但是需要用到子树 AND 和 OR，不可差分，要是可持久化 trie 的话可能需要 $\log^3$。考虑查询已经 $q\log^2V$ 了，修改可以乱来，只要信息是处理好的支持快速查询即可。

所以直接猫树分治，复杂度 $O(n\log n\log V+q\log^2V)$。

---

有一些判集合非空的细节，代码实现得比较抽象。

这份代码的复杂度可能需要这样证明：递归的时候始终会 $t\in[\operatorname{AND},\operatorname{OR}]$，如果 AND $\ne$ OR，由于段数不超过 $\log V$，这些递归不会超过 $\log^2V$，否则，只会单路递归，还是 $\log^2V$。

```cpp
const int N=1e5+5,K=29;
int n,q,a[N],ql[N],qr[N],qq[N],as[N];

const int S=N*(K+3);
int idx,rt[N],tr[S][2],Ad[S],Or[S],ct[S];
void ins(int&p,int d,int x){
	int q=++idx;tr[q][0]=tr[p][0];tr[q][1]=tr[p][1];
	Ad[q]=Ad[p]&x;Or[q]=Or[p]|x;ct[q]=ct[p]+1;p=q;
	if(!~d)return;ins(tr[p][x>>d&1],d-1,x);
}
bool qry(int p,int q,int d,int AD,int OR,int t,bool ox,bool oy){
	if((AD&OR)!=OR)return 0;
	if(!p&&!q)return ox&&oy&&OR==AD;
	if(!~d)return ct[p]+ct[q]>=2||(ox&&AD==t)||(oy&&OR==t);
	if(OR>>d&1)return qry(tr[p][1],tr[q][1],d-1,AD,OR|Or[tr[p][0]]|Or[tr[q][0]],t|1<<d,ox,oy||ct[p]||ct[q]);
	if(~AD>>d&1)return qry(tr[p][0],tr[q][0],d-1,AD&Ad[tr[p][1]]&Ad[tr[q][1]],OR,t,ox||ct[p]||ct[q],oy);
	return qry(tr[p][1],tr[q][1],d-1,AD,OR|Or[tr[p][0]]|Or[tr[q][0]],t|1<<d,ox,oy||ct[p]||ct[q])||
		qry(tr[p][0],tr[q][0],d-1,AD&Ad[tr[p][1]]&Ad[tr[q][1]],OR,t,ox||ct[p]||ct[q],oy);
}
void dvd(int l,int r,int L,int R){
	if(l==r||L>R)return;
	int md=l+r>>1;idx=0;
	for(int i=md;i>=l;i--)ins(rt[i]=i==md?0:rt[i+1],K,a[i]);
	for(int i=md+1;i<=r;i++)ins(rt[i]=i==md+1?0:rt[i-1],K,a[i]);
	int X=stable_partition(qq+L,qq+R+1,[&](int x){return ql[x]<=md&&md<qr[x];})-qq;
	for_each(qq+L,qq+X,[&](int x){as[x]=qry(rt[ql[x]],rt[qr[x]],K,Ad[0],Or[0],0,0,0);});
	int Y=stable_partition(qq+X,qq+R+1,[&](int x){return qr[x]<=md;})-qq;
	dvd(l,md,X,Y-1);dvd(md+1,r,Y,R);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=q;i++){scanf("%d%d",&ql[i],&qr[i]);qq[i]=i;}
	Ad[0]=-1;Or[0]=0;dvd(1,n,1,q);
	for(int i=1;i<=q;i++)puts(as[i]?"YES":"NO");
	return 0;
}
```

---

## 作者：Arghariza (赞：3)

这种题放联考 T2 还是过于超前了。

我们先考虑单次询问。

把 $a$ 从小到大排序后，如果存在方案，假设 $\mathtt{AND=OR}=x$，那么一定是 $<x$ 的全部取 $\mathtt{OR}$，$>x$ 的全部取 $\mathtt{AND}$，$=x$ 的随便放即可。于是只需要求出前缀 $\mathtt{OR}$ 和后缀 $\mathtt{AND}$ 的值。

然而这个东西大概是拓展不到区间询问的。我们考虑另一种排序方式：按照 $\text{popcount}$ 排序。

由于取 $\mathtt{OR}$ 后 $\text{popcount}$ 单调不减，取 $\mathtt{AND}$ 后 $\text{popcount}$ 单调不增，所以假设最后 $\text{popcount}(\mathtt{AND})=\text{popcount}(\mathtt{OR})=x$，那么 $\text{popcount}(a_i)<x$ 的 $a_i$ 应全部取 $\mathtt{OR}$，$\text{popcount}(a_i)>x$ 的 $a_i$ 应全部取 $\mathtt{AND}$。

对于 $\text{popcount}(a_i)=x$ 的情况，这些 $a_i$ 必须全部相等。如果存在不相等的 $a_i$，首先它们不能一起被分到同一个集合里面；其次如果它们分属于不同的集合，相当于在 $a\neq b$ 中选出一个 $a$ 的子集和 $b$ 的超集相等，这显然不可能。

于是我们每次询问从小到大枚举 $x$，求出 $\text{popcount}<x$ 的数的 $\mathtt{OR}$ 和 $\text{popcount}>x$ 的数的 $\mathtt{AND}$，然后分类讨论一下 $=x$ 的数应该取哪边即可。

使用二区间合并可以做到 $O((n+q)\log w)$。

```cpp
// Problem: P10743 [SEERC2020] AND = OR
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10743
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 1e5 + 5;
const int S = (1 << 30) - 1;
const int L = 32;
const int B = 30;

struct Q {
	int l, r, i;
	Q () { }
	Q (int _l, int _r, int _i) : l(_l), r(_r), i(_i) { }
};

vector<Q> q;

int n, m;
int a[N], c[N], ans[N], vs[N];
int to[L], ta[L], tc[L], ro[L], ra[L], rc[L];
int lo[N][L], la[N][L], lc[N][L];
int po[L], sa[L], pc[L], sc[L];

void mems(int *x, int y) {
	F (i, 0, B) x[i] = y;
}

void memc(int *x, int *y) {
	F (i, 0, B) x[i] = y[i];
}

void conq(int l, int r, vector<Q> qs) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	vector<Q> ql, qr, qn;
	for (Q p : qs) {
		int L = p.l, R = p.r;
		if (L > mid) {
			qr.eb(p);
		} else if (R <= mid) {
			ql.eb(p);
		} else {
			qn.eb(p);
			vs[L] = 1;
		}
	}
	mems(to, 0);
	mems(ta, S);
	mems(tc, 0);
	R (i, mid, l) {
		to[c[i]] |= a[i];
		ta[c[i]] &= a[i];
		tc[c[i]]++;
		if (vs[i]) {
			memc(lo[i], to);
			memc(la[i], ta);
			memc(lc[i], tc);
			vs[i] = 0;
		}
	}
	sort(qn.begin(), qn.end(), [](Q &x, Q &y) {
		return x.r < y.r;
	});
	int j = mid + 1;
	mems(ro, 0);
	mems(ra, S);
	mems(rc, 0);
	for (Q p : qn) {
		int L = p.l, R = p.r, i = p.i;
		while (j <= R) {
			ro[c[j]] |= a[j];
			ra[c[j]] &= a[j];
			rc[c[j]]++;
			j++;
		}
		po[0] = (lo[L][0] | ro[0]);
		sa[B] = (la[L][B] & ra[B]);
		pc[0] = lc[L][0] + rc[0];
		sc[B] = lc[L][B] + rc[B];
		F (o, 1, B) {
			po[o] = po[o - 1] | (lo[L][o] | ro[o]);
			pc[o] = pc[o - 1] + lc[L][o] + rc[o];
		}
		R (o, B - 1, 0) {
			sa[o] = sa[o + 1] & (la[L][o] & ra[o]);
			sc[o] = sc[o + 1] + lc[L][o	] + rc[o];
		}
		F (o, 0, B - 1) {
			if (!pc[o] || !sc[o + 1]) {
				continue;
			}
			if (po[o] == sa[o + 1]) {
				ans[i] = 1;
				break;
			}
		}
		if (ans[i]) {
			continue;
		}
		F (o, 0, B) {
			if (lc[L][o] + rc[o] < 2 || (lo[L][o] | ro[o]) != (la[L][o] & ra[o])) {
				continue;
			}
			int w = (lo[L][o] | ro[o]);
			if (((!o ? w : (po[o - 1] | w))) == ((o == B ? w : (sa[o + 1] & w)))) {
				ans[i] = 2;
				break;
			}
		}
	}
	conq(l, mid, ql);
	conq(mid + 1, r, qr);
}

void solve() {
	cin >> n >> m;
	F (i, 1, n) {
		cin >> a[i];
		c[i] = __builtin_popcount(a[i]);
	}
	F (i, 1, m) {
		int l, r;
		cin >> l >> r;
		q.eb(Q(l, r, i));
	}
	conq(1, n, q);
	F (i, 1, m) {
		if (ans[i]) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}

bool Med;
int main() {
	FIO("bit");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：Rainsleep (赞：2)

非常巧妙的一个题。我们首先考虑单组询问该怎么做。

首先需要注意到一个结论，即设答案为 $x$，那么对于 $\forall y < x$，$y$ 都应该放在与组；同样的，对于 $\forall y > x$，$y$ 都应该放在与组。

进一步的，我们观察在 $\text{popcount}$ 上也有同样的性质，即对于 $\forall y, \text{popcount(y)} < \text{popcount(x)}$，$y$ 应该被放到或组，反之同理。

而对于 $\text{popcount(y) = \text{popcount(x)}}$ 的 $y$，有结论：所有的 $y$ 相等。

>证明非常的巧妙，设或集合为 $A$，与集合为 $B$，$\text{popcount(x)} = k$。
>
>当只有一个数时显然成立，现在考虑大于一个数的情况。
>
>从这些数中拿出两个，分别设为 $a, b$，并分别放入 $A, B$ 中，设 $A, B$ 内的数经运算后的值分别为 $v1, v2$。
>
>显然有 $\text{popcount}(v1) \ge k, \text{popcount}(v2) \le k$，又因为两个集合的答案相等，所以 $\text{popcount}(v1) = \text{popcount}(v2) = k$。
>
>考虑按位与或的本质，是把二进制下的位置分别取并和交，因为两者都恰好有 $k$ 位，所以 $v1 = a, v2 = b$，那么进一步就有 $a = b$。
>
>大于 $2$ 个数字都可以用类似的证明。

考虑答案怎么维护，考虑枚举答案的 $\text{popcount} = k$，依次 check 每个区间是否合法，维护 $\text{popcount} < k$ 的 $A$ 集合值和 $\text{popcount} > k$ 的 $B$ 集合值，可以用线段树和前缀和在 $\log^2$ 内完成。

细节上对于 $\text{popcount} = k$ 的数，要分别对数量为 $1, 2, \ge 2$ 分别讨论。

```cpp
// ubsan: undefined
// accoders
// 如果命运对你缄默, 那就活给他看。
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
// #define int LL
const int maxn = 100010;
const int INF = (1 << 30) - 1;
int n, q, w[maxn], pc[maxn];
namespace sgt {
  struct Node { int o, a, c, v; };
  struct sgt {
    Node t[maxn << 2];
    inline Node mg(Node ls, Node rs) {
      return {ls.o | rs.o, ls.a & rs.a, ls.c + rs.c, 
        (ls.v == -1 || rs.v == -1) ? max(ls.v, rs.v) : ((ls.v ^ rs.v) ? INF + 1 : rs.v)
      }; 
    }
    inline void build(int u, int l, int r, int c) {
      if(l == r) {
        if(pc[r] == c) t[u] = {w[r], w[r], 1, w[r]};
        else t[u] = {0, INF, 0, -1};
        return ;
      }
      int mid = l + r >> 1;
      build(u << 1, l, mid, c);
      build(u << 1 | 1, mid + 1, r, c);
      t[u] = mg(t[u << 1], t[u << 1 | 1]);
    }
    inline Node Q(int u, int l, int r, int ql, int qr) {
      if(ql <= l && r <= qr) return t[u];
      int mid = l + r >> 1;
      if(qr <= mid) return Q(u << 1, l, mid, ql, qr);
      if(ql > mid) return Q(u << 1 | 1, mid + 1, r, ql, qr);
      return mg(Q(u << 1, l, mid, ql, qr), Q(u << 1 | 1, mid + 1, r, ql, qr));
    }
  } t[31];
} using namespace sgt; 
int a[31], o[31];
inline bool check(int l, int r) {
  for(int i = 0; i < 31; ++ i) {
    Node e = t[i].Q(1, 1, n, l, r);
    a[i] = e.a, o[i] = e.o;
  }
  for(int i = 1; i < 31; ++ i) o[i] |= o[i - 1];
  for(int i = 29; ~i; -- i) a[i] &= a[i + 1];
  int co = 0, ca = r - l + 1;
  for(int k = 0; k < 31; ++ k) {
    Node e = t[k].Q(1, 1, n, l, r);
    ca -= e.c;
    int vo = (!k) ? 0 : o[k - 1], va = (k == 30 ? INF : a[k + 1]);
    if(e.v ^ (INF + 1)) {
      int cnt = e.c;
      if((cnt == 0) && (ca && co && (vo == va))) return 1;
      if((cnt == 1) && ((((vo | e.v) == va) && ca) || ((vo == (e.v & va)) && co))) return 1;
      if((cnt >= 2) && ((vo | e.v) == (va & e.v))) return 1; 
    }
    co += e.c;
  }
  return 0;
}
signed main() {
//   freopen("peace.in", "r", stdin);
//   freopen("peace.out", "w", stdout);
  ios :: sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> q;
  for(int i = 1; i <= n; ++ i) {
    cin >> w[i];
    pc[i] = __builtin_popcount(w[i]);
  }
  for(int i = 0; i < 31; ++ i) t[i].build(1, 1, n, i);
  for(int l, r, i = 1; q --; ) {
    cin >> l >> r;
    cout << (check(l, r) ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

---

## 作者：sunkuangzheng (赞：2)

$\textbf{P10743}$

> - 定义一个序列是好的，当且仅当可以把每个元素划分至 $A,B$ 中的某一个集合，使得 $\operatorname{AND}_{x \in A} = \operatorname{OR}_{x \in B}$ 且 $A,B$ 均非空。
> - 给定序列 $a$，$q$ 次询问 $a[l_i,r_i]$ 是否是好的。
> - $1 \le n,q \le 10^5,0 \le a_i < 2^{30}$。

考虑每一个二进制位，如果 $\operatorname{AND} = \operatorname{OR} = 0$ 则要求 $B$ 集合包含所有该位是 $0$ 的元素，否则要求 $A$ 集合包含所有该位是 $1$ 的元素。

将所有元素排序后，从高到低考虑每一个二进制位带来的限制。不难发现，一个合法的划分总满足 $B$ 集合是一段前缀，$A$ 集合是一段后缀。

注意到序列的前后缀 $\operatorname{AND},\operatorname{OR}$ 都只有 $\mathcal O(\log V)$ 个，因此每次询问我们只需要找到这些区间然后暴力判断判断值相等的区间是否有交集。寻找区间时，我们对每个二进制上是 $0,1$ 的分别开一个 st 表，想要从当前的前缀 $\operatorname{OR}$ 推到下一个时，只需要当前前缀 $\operatorname{OR}$ 没有的位上 $1$ 的 st 表里找最小值即可。

时间复杂度 $\mathcal O(n \log V \log n + q\log^2 V)$。

实现时注意对相同元素的处理。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 11.07.2024 08:09:44
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5,oi = 0,ai = (1ll << 31) - 1;
using namespace std;
int T,n,tot,q,a[N],b[N],l,r,rt[N],vl[N],tm_[N]; 
struct tr{int l,r,o,a;}t[N*40];
using pi = pair<int,int>; vector<pi> c;
template <class S,S (*op)(S,S)> struct rmq{
    private:
        vector<vector<S>> st; int n,lg;
    public:
        rmq() : rmq(0){}
        rmq(int _n){
            n = _n,lg = __lg(n),st.resize(lg + 1,vector<S>(n + 1));
        }void init(vector<S> a){
            for(int i = 1;i <= n;i ++) st[0][i] = a[i];
            for(int j = 1;j <= lg;j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
                st[j][i] = op(st[j-1][i],st[j-1][i+(1<<j-1)]);
        }void init(S *a){
            vector<S> tmp(n + 1);
            for(int i = 1;i <= n;i ++) tmp[i] = a[i];
            init(tmp);
        }S qry(int l,int r){
            int k = __lg(r - l + 1);
            return op(st[k][l],st[k][r-(1<<k)+1]);
        }
}; 
using rn = rmq<int,[](int x,int y){return min(x,y);}>;
using rx = rmq<int,[](int x,int y){return max(x,y);}>;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) cin >> a[i],c.emplace_back(a[i],i);
    sort(c.begin(),c.end());
    t[0].o = oi,t[0].a = ai;
    for(int i = 1;i <= n;i ++) b[i] = lower_bound(c.begin(),c.end(),pi{a[i],i}) - c.begin() + 1,
        vl[b[i]] = a[i];
    rn mn(n),Mn[32];
    rx mx(n),Mx[32];
    mn.init(b),mx.init(b);
    for(int i = 0;i <= 30;i ++){
        Mn[i] = rn(n),Mx[i] = rx(n);
        for(int j = 1;j <= n;j ++) tm_[j] = (a[j] >> i & 1 ? b[j] : ai);
        Mn[i].init(tm_);
        for(int j = 1;j <= n;j ++) tm_[j] = (a[j] >> i & 1 ? oi : b[j]);
        Mx[i].init(tm_);
    }while(q --){
        cin >> l >> r;
        int ql = mn.qry(l,r),qr = mx.qry(l,r); 
        map<int,vector<pi>> mp;
        int la = vl[ql],lt = ql;
        for(int i = 1;i <= 30;i ++){
            int mn = qr + 1;
            for(int j = 0;j <= 30;j ++) if(!((la >> j) & 1)) mn = min(mn,Mn[j].qry(l,r));
            mp[la].emplace_back(lt,mn),lt = mn,la |= vl[lt];
            if(lt == qr + 1) break;
        }la = vl[qr],lt = qr + 1;
        for(int i = 1;i <= 30;i ++){
            int mn = ql - 1;
            for(int j = 0;j <= 30;j ++) if((la >> j & 1)) mn = max(mn,Mx[j].qry(l,r));
            mp[la].emplace_back(mn + 1,lt),lt = mn + 1,la &= vl[lt - 1];
            if(lt == ql) break;
        }int fg = 0;
        for(auto [x,y] : mp)
            if(y.size() == 2){
                auto [l1,r1] = y[0]; auto [l2,r2] = y[1];
                if(max(l1 + 1,l2) < min(r1 + 1,r2)){fg = 1,cout << "YES\n"; break;}
            }
        if(!fg) cout << "NO\n";
    }
}
```

---

## 作者：AbsMatt (赞：1)

### [题目传送器](https://www.luogu.com.cn/problem/P10743)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/P10743-solution/)

## 前言

赛时想出的做法，结果过了一周才过，非常难写，常数还大，本文其实可以认为是做法的补充，只用到了一个性质。

## 做法

先分析一些性质。

1. 对于询问的区间 $[l,r]$，将区间排序后，显然结果是一个前缀 $a_1,a_2\dots a_k$ 的或和等于后缀 $a_{k+1},a_{k+2}\dots a_n$ 的与和，因为或和的最小值为 $a_k$，与和的最大值为 $a_{k+1}$，$a_k\le a_{k+1}$，所以两个部分一定可以不交，即形成一个前缀和后缀。
2. 设与和 $=$ 或和 $=x$。按位考虑，若 $x$ 的第 $i$ 位为 $0$，则分界点 $k$ 满足 $[l,k]$ 的第 $i$ 位都是 $0$，且 $[k+1,r]$ 中至少有一个 $0$。若 $x$ 的第 $i$ 位为 $1$，则 $k$ 满足 $[k+1,r]$ 的第 $i$ 位都是 $1$，$[l,k]$ 至少有一个 $1$。

第二条性质本质上就是说明，若第 $i$ 位为 $0$，设第 $i$ 位的一个极长前缀 $[1,L]$ 满足 2，则 $k\in[1,L]$，若第 $i$ 位为 $1$，设第 $i$ 位的一个极长后缀 $[R+1,n]$ 满足 2，则 $k\in[R+1,n]$。

具体实现就是建一棵主席树，在主席树上二分得到满足以上要求的极长前缀和后缀，则最终的分界点 $k$ 必然满足在每一位都在 $[1,L_i]$ 或 $[R_i+1,n]$ 区间中，即若满足 $\exist k,k\in[1,L_i]\cup[R_i+1,n]$，则答案为 ``YES``，否则为 ``NO``。本质上就是对每个区间求交集。

分析时间复杂度，对每一位做主席树上二分为 $\mathcal{O}((q+n)\times \log_2V\times \log_2n)$，求交集可以将每个区间先取反，再求并集是否为全集即可 $\mathcal{O}(q\times \log_2V\times \log_2\log_2V)$。

具体实现时，可以将询问离线，对每个位先求出 $q$ 个询问的极长前后缀，最后求交集，这样可以将空间复杂度将为 $\mathcal{O}(n\times\log_2n)$，时间常数减小，再添加一些小剪枝就通过了。

[Code](https://www.luogu.com.cn/paste/nt5wlfg1)

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10743)。

## 思路

不妨假设区间 $[l,r]$ 存在一种划分使得 $\mathrm{OR}_{i\in S_1} a_i=\mathrm{AND}_{i\in S_2}a_i=x$，令 $k=\mathrm{popcount}(x)$，那么很显然区间内 $\mathrm{popcount}$ 小于 $k$ 的数都在 $S_1$（或集合）里，大于 $k$ 的数都在 $S_2$（与集合）里，等于 $k$ 的可以随便分配。

不妨对于每个 $k$，用线段树维护区间中 $\mathrm{popcount}$ 恰好为 $k$ 的数的按位或和按位与，在询问中枚举每个 $k$，并求出对应的或集合和与集合，判断是否相等即可，注意区间内 $\mathrm{popcount}$ 恰好为 $k$ 的数只有一种。

时间复杂度 $\mathcal O (q\log n\log V)$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+7;
int n,Q;
int a[Maxn],b[Maxn];
int q0[32],q1[32],c0[32],c1[32],s0[32],s1[32],t[32];

struct TREE{
    int l,r;
    int vA,vO,c;
}tree[31][Maxn<<2];

inline int OR(int x,int y){
    if(x==-1 or y==-1) return x+y+1;
    return x|y;
}
inline int AND(int x,int y){
    if(x==-1 or y==-1) return x+y+1;
    return x&y;
}
inline void pushup(int wh,int node){
    tree[wh][node].vA=AND(tree[wh][node<<1].vA,tree[wh][node<<1|1].vA);
    tree[wh][node].vO=OR(tree[wh][node<<1].vO,tree[wh][node<<1|1].vO);
    tree[wh][node].c=tree[wh][node<<1].c+tree[wh][node<<1|1].c;
}
void buildtree(int wh,int node,int l,int r){
    tree[wh][node].l=l,tree[wh][node].r=r;
    if(l==r){
        tree[wh][node].vA=tree[wh][node].vO=b[l];
        tree[wh][node].c=(b[l]>=0);
        return ;
    }
    int mid=l+r>>1;
    buildtree(wh,node<<1,l,mid);
    buildtree(wh,node<<1|1,mid+1,r);
    pushup(wh,node);
}
TREE query(int wh,int node,int l,int r){
    if(tree[wh][node].l>=l and tree[wh][node].r<=r) return tree[wh][node];
    int mid=tree[wh][node].l+tree[wh][node].r>>1,ret0=-1,ret1=-1,ret2=0;
    if(l<=mid){
        TREE s=query(wh,node<<1,l,r);
        ret0=OR(ret0,s.vO),ret1=AND(ret1,s.vA),ret2+=s.c;
    }
    if(r>mid){
        TREE s=query(wh,node<<1|1,l,r);
        ret0=OR(ret0,s.vO),ret1=AND(ret1,s.vA),ret2+=s.c;
    }
    return (TREE){0,0,ret1,ret0,ret2};
}

int main(){
    scanf("%d%d",&n,&Q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<=30;i++){
        for(int j=1;j<=n;j++){
            if(__builtin_popcount(a[j])==i) b[j]=a[j];
            else b[j]=-1;
        }
        buildtree(i,1,1,n);
    }
    while(Q--){
        int l,r;
        scanf("%d%d",&l,&r);
        for(int i=0;i<=30;i++){
            TREE s=query(i,1,l,r);
            q0[i]=s0[i]=s.vO,q1[i]=s1[i]=s.vA,c0[i]=s.c,c1[i]=s.c,t[i]=s.c;
        }

        bool tag=0;
       
        for(int i=1;i<=30;i++) q0[i]=OR(q0[i],q0[i-1]),c0[i]+=c0[i-1];
        for(int i=29;~i;i--) q1[i]=AND(q1[i],q1[i+1]),c1[i]+=c1[i+1];


        for(int i=0;i<=30;i++){
            if(c0[i] and c1[i+1] and q0[i]==q1[i+1]) tag=1;
            if(q0[i]==q1[i] and t[i]>=2 and s0[i]==s1[i]) tag=1;
        } 
            
        if(tag) puts("YES");
        else puts("NO");
    }

    return 0;
}

```

---

## 作者：CYZZ (赞：1)

## [P10743](https://www.luogu.com.cn/problem/P10743)

赛时想到的聪明做法。

设 $A$ 为题面中相等的值，$B=card(A)$，$card(x)$ 表示 $x$ 二进制表示下 $1$ 的个数。

考虑枚举 $B$。

不难发现 $card(a_i)<B$ 的一定放进 $S_1$，$card(a_i)>B$ 的放进 $S_2$。

需要决策 $card(a_i)=B$。

不难发现，如果这类数中有两个不同的 $a_i$，那么一定无解。

于是所有满足这个条件的数相同，设有 $cnt$ 个。

1. $cnt=0$。直接判断。
2. $cnt=1$。枚举这个数丢进哪一边。
3. $cnt\ge2$。两边都分配一个。

注意需要满足**两边的集合都非空**。

线段树维护区间 $card(a_i)$ 小于/等于/大于 $x$ 的 与/或 和。

时间复杂度 $O(q\log^2n)$。

也可以使用 ST 表做到查询单 $\log$，但是空间会炸。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define ppc __builtin_popcount
int n,q,a[N],msk;
namespace SGT
{
	int pre[N<<2][31];
	void buildpre(int p,int l,int r)
	{
		if(l==r)
		{
			for(int i=ppc(a[l]);i<=30;i++)
				pre[p][i]=a[l];
			return ;
		}
		int mid=(l+r)>>1;
		buildpre(p<<1,l,mid);
		buildpre(p<<1|1,mid+1,r);
		for(int i=0;i<=30;i++)
			pre[p][i]=pre[p<<1][i]|pre[p<<1|1][i];
	}
	int querypre(int p,int l,int r,int x,int y,int id)
	{
		if(x<=l&&y>=r) return pre[p][id];
		int mid=(l+r)>>1,ret=0;
		if(x<=mid) ret|=querypre(p<<1,l,mid,x,y,id);
		if(y>mid) ret|=querypre(p<<1|1,mid+1,r,x,y,id);
		return ret;
	}
	int suf[N<<2][31];
	void buildsuf(int p,int l,int r)
	{
		if(l==r)
		{
			for(int i=0;i<=30;i++)
				suf[p][i]=ppc(a[l])>=i?a[l]:msk;
			return ;
		}
		int mid=(l+r)>>1;
		buildsuf(p<<1,l,mid);
		buildsuf(p<<1|1,mid+1,r);
		for(int i=0;i<=30;i++)
			suf[p][i]=suf[p<<1][i]&suf[p<<1|1][i];
	}
	int querysuf(int p,int l,int r,int x,int y,int id)
	{
		if(x<=l&&y>=r) return suf[p][id];
		int mid=(l+r)>>1,ret=msk;
		if(x<=mid) ret&=querysuf(p<<1,l,mid,x,y,id);
		if(y>mid) ret&=querysuf(p<<1|1,mid+1,r,x,y,id);
		return ret;
	}
	int tr[N<<2][31];
	void buildtr(int p,int l,int r)
	{
		if(l==r)
		{
			for(int i=0;i<=30;i++)
				tr[p][i]=i==ppc(a[l])?a[l]:msk;
			return ;
		}
		int mid=(l+r)>>1;
		buildtr(p<<1,l,mid);
		buildtr(p<<1|1,mid+1,r);
		for(int i=0;i<=30;i++)
			tr[p][i]=tr[p<<1][i]&tr[p<<1|1][i];
	}
	int querytr(int p,int l,int r,int x,int y,int id)
	{
		if(x<=l&&y>=r) return tr[p][id];
		int mid=(l+r)>>1,ret=msk;
		if(x<=mid) ret&=querytr(p<<1,l,mid,x,y,id);
		if(y>mid) ret&=querytr(p<<1|1,mid+1,r,x,y,id);
		return ret;
	}
}using namespace SGT;
int psum[31][N];
int ssum[31][N];
int sum[31][N];
inline int queryp(int x,int l,int r){return psum[x][r]-psum[x][l-1];}
inline int querys(int x,int l,int r){return ssum[x][r]-ssum[x][l-1];}
inline int query(int x,int l,int r){return sum[x][r]-sum[x][l-1];}
int main()
{
	scanf("%d%d",&n,&q);
	msk=(1<<30)-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		for(int j=0;j<=30;j++)
		{
			psum[j][i]=psum[j][i-1]+(ppc(a[i])<=j);
			ssum[j][i]=ssum[j][i-1]+(ppc(a[i])>=j);
			sum[j][i]=sum[j][i-1]+(ppc(a[i])==j);
		}
	}
	buildpre(1,1,n);
	buildsuf(1,1,n);
	buildtr(1,1,n);
	while(q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int flag=0;
		for(int i=0;i<=30;i++)
		{
			int s1=i?querypre(1,1,n,l,r,i-1):0;
			int s2=i<30?querysuf(1,1,n,l,r,i+1):msk;
			int s3=querytr(1,1,n,l,r,i);
			int cnt1=i?queryp(i-1,l,r):0;
			int cnt2=i<30?querys(i+1,l,r):0;
			int cnt3=query(i,l,r);
			if(!cnt3)
			{
				if(s1==s2&&cnt1&&cnt2)
					{flag=1;break;}
			}
			else if(cnt3==1)
			{
				if((s1==s3&&((s2&s3)==s3)&&cnt1&&(cnt2+cnt3))||
					(s2==s3&&((s1|s3)==s3)&&cnt2&&(cnt1+cnt3)))
					{flag=2;break;}
			}
			else if(ppc(s3)==i)
			{
				if((s1|s3)==s3&&(s2&s3)==s3)
					{flag=3;break;}
			}
		}
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
}
```

---

## 作者：qnqfff (赞：1)

### 思路

容易发现一个结论，设最后两个值都等于 $p$，则对于一个数 $a$,若 $\text{popcount}(a)<\text{popcount}(p)$，则 $a$ 一定会分到 OR 那组，若 $\text{popcount}(a)>\text{popcount}(p)$，则 $a$ 一定会分到 AND 那组。

证明比较显然，因为 OR 的 $\text{popcount}$ 单调不降，且 AND 的 $\text{popcount}$ 单调不升。

于是考虑枚举 $\text{popcount}(p)$ 设为 $t$，使用ST表求出当前区间 $\text{popcount}$ 等于 $x$ 的所有数的 OR 和 AND，在做一遍前缀 OR 和后缀 AND 就能求出 $\text{popcount}(a)<t$ 的所有 $a$ 的 OR，和 $\text{popcount}(a)>t$ 的所有 $a$ 的 AND，那么现在只剩下 $\text{popcount}=t$ 的数了，容易发现这些数必须相等，所以把这些数分组的方案只有三种，全部判断一遍即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,a[100010],OR[31][21][100010],AND[31][21][100010],pre[31],suf[31],cnt[100010][31],lst[100010][31],pcnt[31],scnt[31];
signed main(){
    n=read();m=read();for(int i=0;i<=30;i++) for(int j=1;j<=n;j++) AND[i][0][j]=(1ll<<30)-1;
    for(int i=1;i<=n;i++){
        a[i]=read();memcpy(cnt[i],cnt[i-1],sizeof(cnt[i]));memcpy(lst[i],lst[i-1],sizeof(lst[i]));cnt[i][__builtin_popcount(a[i])]++;lst[i][__builtin_popcount(a[i])]=a[i];
        OR[__builtin_popcount(a[i])][0][i]=AND[__builtin_popcount(a[i])][0][i]=a[i];
    }for(int k=0;k<=30;k++) for(int j=1;j<=20;j++) for(int i=1;i+(1<<j)-1<=n;i++) OR[k][j][i]=OR[k][j-1][i]|OR[k][j-1][i+(1<<j-1)],AND[k][j][i]=AND[k][j-1][i]&AND[k][j-1][i+(1<<j-1)];
    auto qOR=[&](int i,int l,int r){int k=__lg(r-l+1);return OR[i][k][l]|OR[i][k][r-(1<<k)+1];};
    auto qAND=[&](int i,int l,int r){int k=__lg(r-l+1);return AND[i][k][l]&AND[i][k][r-(1<<k)+1];};
    while(m--){
        int l=read(),r=read();
        for(int i=1;i<=30;i++){pre[i]=pre[i-1]|qOR(i-1,l,r);pcnt[i]=pcnt[i-1]+cnt[r][i-1]-cnt[l-1][i-1];}
        suf[30]=(1ll<<30)-1;for(int i=29;~i;i--){suf[i]=suf[i+1]&qAND(i+1,l,r);scnt[i]=scnt[i+1]+cnt[r][i+1]-cnt[l-1][i+1];}
        bool flg=0;for(int i=0;i<=30;i++){
            if(cnt[r][i]-cnt[l-1][i]&&(lst[r][i]^qOR(i,l,r)||lst[r][i]^qAND(i,l,r))) continue;
            flg|=((pre[i]|qOR(i,l,r))==suf[i]&&pcnt[i]+cnt[r][i]-cnt[l-1][i]&&scnt[i])||((pre[i]==(suf[i]&qAND(i,l,r))&&pcnt[i]&&scnt[i]+cnt[r][i]-cnt[l-1][i]));
            if(cnt[r][i]-cnt[l-1][i]>1) flg|=((pre[i]|lst[r][i])==(suf[i]&lst[r][i]));
        }cout<<(flg?"YES\n":"NO\n");
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

观察一下性质，什么时候才是好的数组，我们枚举一个 $k$，若其是合法的，当且仅当：

- 对于所有 $x = a_i \subseteq k$，其 $\operatorname{OR}$ 等于 $k$。

- 对于其他的 $y = a_i$，都要满足 $k \subset a_i$，其 $\operatorname{AND}$ 等于 $k$。

容易发现，满足第一个条件的 $a_i$ 是一定小于满足第二个条件的 $a_i$，所以可以将整个数组排序，若存在一个断点使得前缀 $\operatorname{OR}$ 等于后缀 $\operatorname{AND}$，那么就是好的。

考虑区间询问怎么做？感觉很难拓展啊。但是注意到不仅会满足 $x < y$，且会满足 $\operatorname{popcount}(x) < \operatorname{popcount}(y)$。

考虑若 $\operatorname{popcount}(\operatorname{OR}) = \operatorname{popcount}(\operatorname{AND}) = k$，那么 $\operatorname{popcount}(a_i) < k$ 的必须全选到 $\operatorname{OR}$ 集合，$\operatorname{popcount}(a_i) > k$ 的必须全部选到 $\operatorname{AND}$ 集合，且所有 $\operatorname{popcount}(a_i) = k$ 的 $a_i$ 必须全部相同。

故我们使用线段树维护区间每个 $\operatorname{popcount}$ 的元素是否全部相同，且维护 $\operatorname{popcount}(a_i) < x$ 与 $\operatorname{popcount}(a_i) > x$ 的 $\operatorname{OR}$ 与 $\operatorname{AND}$ 即可。

询问时依次枚举 $k$ 判断即可，时间复杂度为 $O(N \log N \log W)$。

还有很多小细节，例如还需要维护目前左边右边是否有数；对当前 $k$ 的数量为 $0, 1, > 1$ 要进行特判，具体看代码吧。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e5 + 10, M = 31, INF = (1 << 30) - 1;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct St{
	pair<int, int> data[M];
	int OR[M], AND[M];
};
struct Node{
	int l, r;
	St infor;
}X[N << 2];
int n, q, l, r;
int a[N], h[N];
inline pair<int, int> merge(pair<int, int> x, pair<int, int> y){
	if(x.fi == -2 || y.fi == -2) return {-2, 0};
	if(x.fi == -1) return y;
	if(y.fi == -1) return x;
	if(x.fi == y.fi) return {x.fi, x.se + y.se};
	return {-2, 0};
}
inline int ORmerge(int x, int y){
	if(x == -1) return y;
	if(y == -1) return x;
	return x | y;
}
inline int ANDmerge(int x, int y){
	if(x == -1) return y;
	if(y == -1) return x;
	return x & y;
}
inline St merge(St X, St Y){
	St ans;
	for(int i = 0; i < M; ++i){
		ans.data[i] = merge(X.data[i], Y.data[i]);
		ans.OR[i] = ORmerge(X.OR[i], Y.OR[i]);
		ans.AND[i] = ANDmerge(X.AND[i], Y.AND[i]);
	}
	return ans;
}
inline void pushup(int k){
	X[k].infor = merge(X[k << 1].infor, X[k << 1 | 1].infor);
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		for(int i = 0; i < M; ++i){
			X[k].infor.data[i] = {-1, 0};
			if(i >= h[l])
			  X[k].infor.OR[i] = a[l];
			else
			  X[k].infor.OR[i] = -1;
			if(i <= h[l])
			  X[k].infor.AND[i] = a[l];
			else
			  X[k].infor.AND[i] = -1;
		}
		X[k].infor.data[h[l]] = {a[l], 1};
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline St ask(int k, int l, int r){
	if(X[k].l == l && r == X[k].r)
	  return X[k].infor;
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  return ask(k << 1, l, r);
	else if(l > mid)
	  return ask(k << 1 | 1, l, r);
	else
	  return merge(ask(k << 1, l, mid), ask(k << 1 | 1, mid + 1, r)); 
}
bool End;
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		h[i] = popcnt(a[i]);
	}
	build(1, 1, n);
	while(q--){
		bool flag = 0;
		l = read(), r = read();
		auto now = ask(1, l, r);
		for(int i = 0; i < M; ++i){
			if(now.data[i].fi == -2)
			  continue;
			int L, R;
			if(!i) L = -1;
			else L = now.OR[i - 1];
			if(i == M - 1) R = -1;
			else R = now.AND[i + 1];
//			cerr << L << ' ' << R << '\n';
			if(now.data[i].fi == -1){
				if(L == R && L != -1 && R != -1){
					flag = 1;
					break;
				}
				continue;
			}
			if(now.data[i].se == 1){
				if((ORmerge(L, now.data[i].fi) == R && R != -1) || (L != -1 && L == ANDmerge(R, now.data[i].fi))){
					flag = 1;
					break;
				}
				continue;
			}
			if(ORmerge(L, now.data[i].fi) == ANDmerge(R, now.data[i].fi) && ANDmerge(R, now.data[i].fi) !=-1){
				flag = 1;
				break;
			}
		}
		puts(flag ? "YES" : "NO");
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：WRuperD (赞：0)

[本文同步发表于我的博客之中。](http://wruperd.github.io/post/2024-11-08-solution-p10743/)

提供一种好写的 $O(n \log n \log V)$ 的做法。

先考虑如何对于给定的 $l,r$ 在 $O(n\log n)$ 的复杂度单次求解。不难发现，我们每一次一定是取值域上连续的一段前缀的 $\operatorname{OR}$ 和连续的一段后缀的  $\operatorname{AND}$。排序之后就行了。

类似于 P8421 的做法，不难注意到前缀 $\operatorname{OR}$ 和后缀 $\operatorname{AND}$ 的变化量是 $\log V$ 的。所以我们只需要拎出那些有用的值即可。具体的，我们可以考虑使用 $\log V$ 个 $st$ 表维护区间最大的二进制下第 $i$ 位为 0 的数值和它的位置/区间最小的二进制下第 $i$ 位为 1 的数值和它的位置。不难发现对于一个值它最多只会有两个被加入可能有贡献的数组。所以可能有贡献的数就还是 $\log V$ 级别的。通过预处理可以知道区间内是否有 $\geq 2$ 个那个值。

最后我们直接对着可能的值做暴力。

总的复杂度就是 $O(n \log n \log V + q \log V \log V)$。实践证明瓶颈在前半部分。

[至此我们在原数据范围下通过。](https://qoj.ac/submission/724933)

---

## 作者：Rain_chr (赞：0)

考场上给了很重要的一档部分分：$n,q\le 10^5,a_i<2^{10}$，本来是想拿到这一个包的分数的，没想到想着想着直接就会了。

考虑枚举 $x$ 去判定能否分成两个集合使得第一个集合的与和第二个集合的或均为 $x$。显然所有小于 $x$ 的数字必须放在第二个集合，所有大于 $x$ 的数字必须放在第一个集合，不然的话一定不成立。对于等于 $x$ 的数，你再判断一下放在哪个集合，如果有两个 $x$ 就每个集合各放一个，然后看看或和与是否分别等于 $x$。

然后你考虑这个东西是什么，就是把值域劈成前缀和后缀，你在找能否有一个断点使得前缀或等于后缀与。根据经典结论，前缀或和后缀与都只会有 $O(\log V)$ 种，所以你把他们暴力求出来之后直接判断一下就好了。

问题来了，怎么求出一个区间内前缀或和后缀与？我们只讨论前者，因为后者基本是类似的。首先上线段树，得到在两个子区间内的前缀或以及使前缀或变化的位置，合并的时候把这些变化的位置归并了，再删除不会影响前缀或的位置即可。

总复杂度 $O(q\log n\log V+q\log^2 V)$，挺好写的。

---

