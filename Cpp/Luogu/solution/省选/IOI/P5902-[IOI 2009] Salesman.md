# [IOI 2009] Salesman

## 题目背景

IOI2009 D2T4

## 题目描述

旅行商已经发现，最佳的陆上旅行计划是一个难以解决的计算问题，所以他将他的生意转移到多瑙河的线性世界。他有一条很快的船，可以在很短的时间内把他从沿河的任何地方送到任何地方，但不幸的是，这条船耗油量很大。旅行商向上游（靠近河流源头的方向）移动每一米的成本为 $U$ 美元，向下游（远离河流源头的方向）移动每一米的成本为 $D$ 美元。

沿河有 $N$ 个展销会，旅行商想参加。每场展销会只举行一天。对于每个展销会 $X$，旅行商知道它的日期 $T_X$（他买船后的天数为第 $0$ 天），集市的位置 $L_X$ 和他在这场集市上能获得的盈利 $M_X$。位置表示集市到河流源头的距离，以米为单位。他必须在位置为 $S$ 的家 **开始和结束** 他的旅程。

帮助旅行商选择参加哪些展销会（如果有的话）以及按什么顺序，这样他可以在旅行结束时最大化他的利润。旅行商的总利润是指他在参加集市时获得的美元减去他在河上下游旅行所花费的美元的总和。

请记住，如果展销会 $A$ 的举办时间早于展销会 $B$，则旅行商只能按此顺序去展销会（即，他不能先去展销会 $B$，然后再去展销会 $A$）。但是，如果两个集市在同一天举行，旅行商可以按任何顺序参观。旅行商一天去多少个集市是没有限制的，但他不能在同一个集市盈利两次。他可以经过他已经参观过的集市而一无所获。

**任务**：编写一个程序，给定所有展销会的日期，位置和旅行商的盈利额，以及旅行商的家的位置和他移动的代价，求出他在旅行结束时的最大利润。

## 说明/提示

### 样例解释

在一个最优方案中，旅行商参加了编号为 $1$ 和 $3$ 的展销会（位置分别为 $80$ 和 $75$）。事件序列以及对应的利润如下：

- 旅行商从家出发，向上游移动 $20$ 米，花费 $100$ 美元。目前利润：$-100$。
- 旅行商参加展销会 $1$ 并赚取 $100$ 美元。目前利润：$0$。
- 旅行商向上游移动 $5$ 米，花费 $25$ 美元。目前利润 $-25$。
- 旅行商参加展销会 $3$ 并赚取 $150$ 美元。目前利润：$125$。
- 旅行商向下游移动 $25$ 米，回到自己的家，花费 $75$ 美元。最终利润：$50$。

### 数据范围与约定

- 对于 $60\%$ 的数据，没有两个展销会在同一天举行。
- 对于 $40\%$ 的数据，输入的所有数不超过 $5000$。
- 同时满足上述两个条件的数据有 $15\%$，至少满足上述一个条件的数据有 $85\%$。
- 对于 $100\%$ 的数据，$1 \le N, T_k \le 5\times 10^5$，$1 \le D \le U \le 10$，$1 \le S, L_k \le 5 \times 10^5 +1$，$1 \le M_k \le 4000$。

## 样例 #1

### 输入

```
4 5 3 100
2 80 100
20 125 130
10 75 150
5 120 110
```

### 输出

```
50
```

# 题解

## 作者：Alex_Wei (赞：5)

- Update on 2023.4.25：修改一处错误。

> [P5902 [IOI2009] Salesman](https://www.luogu.com.cn/problem/P5902)

首先假设没有展览会在同一天。将展览会按 $T$ 从小到大排序，设 $f_i$ 表示参加第 $i$ 个展览会的最大收益，则有转移
$$
f_i = \max_{1 \leq j < i} f_j - \mathrm{trans}(j, i)
$$
其中若 $L_j \leq L_i$，则 $\mathrm{trans}(j, i) = D(L_i - L_j)$，否则等于 $U(L_j - L_i)$。分离贡献系数的 $i, j$，用两棵线段树维护即可。树状数组也可以维护，因为查询前后缀，且查询和修改都是取 $\max$。

对于在同一天的展览会，如果参加其中任何一个，则旅行商肯定是从某个位置较大的展览会走到某个位置较小的展览会，或者反过来，并参加其中所有展览会。将同一天的展览会按位置从小到大排序，分开做从前往后转移与从后往前转移即可。

注意考虑从家出发带来的影响。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool Mbe;
constexpr int N = 5e5 + 5;
constexpr int inf = 2e9 + 7;

int n, U, D, S;
struct exhi {
  int T, L, M;
  bool operator < (const exhi &z) const {
    if(T != z.T) return T < z.T;
    return L < z.L;
  }
} c[N];

struct SegTree {
  int val[N << 2];
  void build(int l, int r, int x) {
    val[x] = -inf;
    if(l == r) return;
    int m = l + r >> 1;
    build(l, m, x << 1), build(m + 1, r, x << 1 | 1);
  }
  void modify(int l, int r, int p, int x, int v) {
    val[x] = max(val[x], v);
    if(l == r) return;
    int m = l + r >> 1;
    if(p <= m) modify(l, m, p, x << 1, v);
    else modify(m + 1, r, p, x << 1 | 1, v);
  }
  int query(int l, int r, int ql, int qr, int x) {
    if(ql <= l && r <= qr) return val[x];
    int m = l + r >> 1, ans = -inf;
    if(ql <= m) ans = max(ans, query(l, m, ql, qr, x << 1));
    if(m < qr) ans = max(ans, query(m + 1, r, ql, qr, x << 1 | 1));
    return ans;
  }
} fl, fr;
int query(int p) {
  int res = fl.query(1, N, 1, p, 1) - D * p;
  return max(res, fr.query(1, N, p, N, 1) + U * p);
}
void update(int p, int v) {
  fl.modify(1, N, p, 1, v + D * p);
  fr.modify(1, N, p, 1, v - U * p);
}


bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> U >> D >> S;
  for(int i = 1; i <= n; i++) cin >> c[i].T >> c[i].L >> c[i].M;
  sort(c + 1, c + n + 1);
  fl.build(1, N, 1), fl.modify(1, N, S, 1, D * S);
  fr.build(1, N, 1), fr.modify(1, N, S, 1, -U * S);
  for(int l = 1; l <= n; l++) {
    int r = l;
    while(r < n && c[r + 1].T == c[l].T) r++;
    static int f[N], g[N];
    for(int p = l; p <= r; p++) {
      g[p] = f[p] = query(c[p].L) + c[p].M;
    }
    for(int p = l + 1; p <= r; p++) {
      f[p] = max(f[p], f[p - 1] + c[p].M - D * (c[p].L - c[p - 1].L));
    }
    for(int p = r - 1; p >= l; p--) {
      g[p] = max(g[p], g[p + 1] + c[p].M - U * (c[p + 1].L - c[p].L));
    }
    for(int p = l; p <= r; p++) {
      update(c[p].L, max(f[p], g[p]));
    }
    l = r;
  }
  cout << query(S) << "\n";
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：legendgod (赞：4)

[P5902 [IOI2009]salesman](https://www.luogu.com.cn/problem/P5902)

**题目描述：** 还是看原题吧，感觉挺清楚的。

主要是从这题学到的是 $Dp$ 只要保留有价值的东西，有些东西可以省去就需要省去。

对于我来说首先看到题目，会想到通过时间轴进行 $Dp$。但是经过具体的推导发现只能到 $O(n^3)$。

然后需要考虑换一个方向进行 $Dp$，不妨考虑设考虑了前 $i$ 个集会，当前的终止点在第 $i$ 个位置，一开始排序一下。

然后如果不考虑同一天的情况，转移本质上就是就是枚举之前从哪天进行转移的。

$$f(i) = \max_{j = 0} ^ i \{f(j) - (L_i - L_j) \times U\} + w_i$$

还有一种就是向下走的，我们就拿上面的柿子进行优化。

考虑将其拆开，发现 $f(i) = \max_{j  =0} ^ i \{f(j) + L_j \times U\} + w_i - L_i \times U$。

我们使用树状数组维护一下 $\max$ 里面的值，然后另外一种也是同理。

---

之后我们考虑一下同一天的情况，显然如果说经过迂回到达一个位置，肯定不如直接从下到上或者从上到下到达。我们不妨设 $lft(i)$ 表示起点在 $i$ 的左边，终点为 $i$ 的最大收益。

我们一开始赋值的时候，直接让 $lft(i)$ 变成从之前到 $i$ 的最大收益即可。

那么转移的时候因为从下到上，所以直接从 $i - 1$ 进行之前的转移即可。

```cpp
#include <bits/stdc++.h>
/*
* @ legendgod
* 纵使前路是无底深渊，下去了也是前程万里
*/
using namespace std;

//#define Fread
//#define Getmod

#ifdef Fread
char buf[1 << 21], *iS, *iT;
#define gc() (iS == iT ? (iT = (iS = buf) + fread (buf, 1, 1 << 21, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
	for(; '0' <= c && c <= '9';c = getchar()) x = (x * 10) + (c ^ 48);
	x *= f;
}

#ifdef Getmod
const int mod  = 1e9 + 7;
template <int mod>
struct typemod {
    int z;
    typemod(int a = 0) : z(a) {}
    inline int inc(int a,int b) const {return a += b - mod, a + ((a >> 31) & mod);}
    inline int dec(int a,int b) const {return a -= b, a + ((a >> 31) & mod);}
    inline int mul(int a,int b) const {return 1ll * a * b % mod;}
    typemod<mod> operator + (const typemod<mod> &x) const {return typemod(inc(z, x.z));}
    typemod<mod> operator - (const typemod<mod> &x) const {return typemod(dec(z, x.z));}
    typemod<mod> operator * (const typemod<mod> &x) const {return typemod(mul(z, x.z));}
    typemod<mod>& operator += (const typemod<mod> &x) {*this = *this + x; return *this;}
    typemod<mod>& operator -= (const typemod<mod> &x) {*this = *this - x; return *this;}
    typemod<mod>& operator *= (const typemod<mod> &x) {*this = *this * x; return *this;}
    int operator == (const typemod<mod> &x) const {return x.z == z;}
    int operator != (const typemod<mod> &x) const {return x.z != z;}
};
typedef typemod<mod> Tm;
#endif

template <typename T,typename... Args> inline void r1(T& t, Args&... args) {
    r1(t);  r1(args...);
}

#define int long long
const int maxn = 5e5 + 5;
const int maxm = maxn << 1;
const int N = 5e5;
struct Segment {
    int t[maxn];
    Segment(void) {memset(t, -0x3f, sizeof(t));}
    inline int lowbit(int x) {
        return x & (-x);
    }
    void add(int p,int c) {
        for(; p <= N; p += lowbit(p)) t[p] = max(t[p], c);
    }
    int ask(int p) {
        int res(-1e17);
        for(; p; p -= lowbit(p)) res = max(t[p], res);
        return res;
    }
}T1;
struct Segment1 {
    int t[maxn];
    Segment1(void) {memset(t, -0x3f, sizeof(t));}
    inline int lowbit(int x) {
        return x & -x;
    }
    void add(int p,int c) {
        for(; p; p -= lowbit(p)) t[p] = max(t[p], c);
    }
    int ask(int p) {
        int res(-1e7);
        for(; p <= N; p += lowbit(p)) res = max(res, t[p]);
        return res;
    }
}T2;

/*
T1 <
T2 >
*/

int n, U, D, S;
struct Node {
    int t, l, w;
    int operator < (const Node &z) const {
        return t == z.t ? l < z.l : t < z.t;
    }
}a[maxn];

int f[maxn];
int lft[maxn], rig[maxn];

void Solve(int l,int r) {
    for(int i = l; i <= r; ++ i) {
        rig[i] = lft[i] = max(
            T1.ask(a[i].l) - a[i].l * U,
            T2.ask(a[i].l) + a[i].l * D
        ) + a[i].w;
    }
    for(int i = l + 1; i <= r; ++ i) lft[i] = max(lft[i], lft[i - 1] - (a[i].l - a[i - 1].l) * U + a[i].w);
    for(int i = r - 1; i >= l; -- i) rig[i] = max(rig[i], rig[i + 1] - (a[i + 1].l - a[i].l) * D + a[i].w);
    for(int i = l; i <= r ;++ i) {
        f[i] = max(lft[i], rig[i]);
        T1.add(a[i].l, f[i] + a[i].l * U);
        T2.add(a[i].l, f[i] - a[i].l * D);
    }
}

signed main() {
//    freopen("S.in", "r", stdin);
//    freopen("S.out", "w", stdout);
    memset(f, -0x3f, sizeof(f));
    int i, j;
    r1(n, U, D, S);
    for(i = 1; i <= n; ++ i) {
        r1(a[i].t, a[i].l, a[i].w);
    }
    a[0].t = 0, a[0].l = a[n + 1].l = S, a[n + 1].t = 1e9;
    ++ n;
    sort(a + 1, a + n + 1);
    T1.add(S, S * U), T2.add(S, - S * D);
    for(i = 1; i <= n; ++ i) {
        if(a[i].t == a[i + 1].t) {
            int now = i;
            while(a[now].t == a[now + 1].t) ++ now;
            Solve(i, now);
            i = now;
            continue;
        }
        f[i] = max(T1.ask(a[i].l) - a[i].l * U, T2.ask(a[i].l) + a[i].l * D) + a[i].w;
        T1.add(a[i].l, f[i] + a[i].l * U);
        T2.add(a[i].l, f[i] - a[i].l * D);
    }
    printf("%lld\n", f[n]);
	return 0;
}

```


---

## 作者：弦巻こころ (赞：3)

设$f$数组为当前第$i$个集市能获得的最大利润

首先朴素的 $n^2$dp还是比较好想的

$f[i]=max(f[j]-c(j,i)+w[i])(j<i)$


假设没有在同一天的情况,如何优化$dp$式子.

我们可以将有关i的常数先分离出来再观察满足那种条件的j是最优值

若$a[i].l>a[j].l$

$f[i]=max(f[j]-(a[i].l-a[j].l)*  d+w[i])$
将有关$i$的常数分离,发现如果 $f[j]+a[j].l* d$最大,那么这个$j$一定是对于$i$的最优值.

将$f[j]+a[j].l* d$扔到树状数组上维护就好,$a[i].l<a[j].l$时同理

但如果有集市在同一天的话,先后顺序会不好处理

我们发现,如果同一天的多场集市,我们一定会按l从小到大走或从大往小走,我们一定不会来回绕路来增加费用.

所以对于同一天,单独再处理一遍就行了

方程为

$tl[i]=max(tl[i],tl[i-1]+ (a[i].l-a[i-1].l)*d+w[i]$

$tr[i]=max(tr[i],tr[i+1]+(a[i+1].l-a[i].l)*u+w[i]$

最后$f[i]=max(tl[i],tr[i])$,在树状数组上更新即可

代码有点压行

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=514514;
#define ll long long
ll tl[N],tr[N],tr1[N],tr2[N],f[N],u,d,s;
int n;
struct ask{int t;ll l,w;}a[N];
int lb(int x){return x&(-x);}
void add1(int x,ll p){while(x<N)tr1[x]=max(p,tr1[x]),x+=lb(x);return;}
ll ask1(int x){ll k=-1e17;while(x)k=max(tr1[x],k),x-=lb(x);return k;}//前缀最大值
void add2(int x,ll p){while(x)tr2[x]=max(p,tr2[x]),x-=lb(x);return;}
ll ask2(int x){ll k=-1e17;while(x<N)k=max(tr2[x],k),x+=lb(x);return k;}//后缀最大值
bool cmp(ask a,ask b){return a.t==b.t?a.l<b.l:a.t<b.t;}
void solve(int l,int r){
	for(int i=l;i<=r;i++)tl[i]=tr[i]=max(ask1(a[i].l)-a[i].l*d,ask2(a[i].l)+a[i].l*u)+a[i].w;
	for(int i=l+1;i<=r;i++)tl[i]=max(tl[i],tl[i-1]-(a[i].l-a[i-1].l)*d+a[i].w);//从l比他小的转移.
	for(int i=r-1;i>=l;i--)tr[i]=max(tr[i],tr[i+1]-(a[i+1].l-a[i].l)*u+a[i].w);//从l比他大的转移.
	for(int i=l;i<=r;i++){f[i]=max(tl[i],tr[i]);
		add1(a[i].l,f[i]+a[i].l*d);add2(a[i].l,f[i]-a[i].l*u);//扔到树状数组里
	}
}
int main(){memset(tr1,-123,sizeof(tr1));memset(tr2,-123,sizeof(tr2));
	memset(f,-123,sizeof(f));scanf("%d%lld%lld%lld",&n,&u,&d,&s);
	for(int i=1;i<=n;i++)scanf("%d%lld%lld",&a[i].t,&a[i].l,&a[i].w);
	a[n+1].t=1919810;a[0].l=a[n+1].l=s;f[0]=0;
	sort(a+1,a+n+1,cmp);add1(s,s*d);add2(s,-s*u);
	for(int i=1;i<=n+1;i++){
		if(a[i].t==a[i+1].t){int l=i;
			while(a[i].t==a[i+1].t)i++;
			solve(l,i);continue;
		}f[i]=max(ask1(a[i].l)-a[i].l*d,ask2(a[i].l)+a[i].l*u)+a[i].w;
		add1(a[i].l,f[i]+a[i].l*d),add2(a[i].l,f[i]-a[i].l*u);扔到树状数组里
	}printf("%lld\n",f[n+1]);
}

---

## 作者：wangjiajian (赞：1)

### 解题思路

看到最优方案，可以拆分为不同子问题，并且按时间顺序选择展厅（同一天除外）便不会对后续选择造成影响，考虑动态规划。

**先考虑没有同一天展厅的情况：**

设 $f_i$ 表示选到第 $i$ 个展厅的最大利润，$d_{j, i}$ 表示从展厅 $j$ 移动到展厅 $i$ 的旅行成本。将展厅按时间排序，得到转移方程：

$f_i = \max \left\{ f_j + m_i - d_{j,i} \right\}$，${j \in [0,i)}$

已知：
 - 当 $l_j <= l_i$ 时，$d_{j,i} = (l_i - l_j) \times u$。
 - 当 $l_j > l_i$ 时，$d_{j, i} = (l_j - l_i) \times d$。

将此代入转移方程，并将与 $j$ 无关的项提到 $\max()$ 之外，得到：

 - 当 $l_j <= l_i$ 时，$f_i = \max \left\{f_j + l_j \times u \right\} + m_i - l_i \times u$。
 - 当 $l_j > l_i$ 时，$f_i = \max(f_j - l_j \times d) + m_i + l_i \times d$。

此时可以使用两个树状数组分别维护 $f_j + l_j \times u$ 和 $f_j - l_j \times d$ 的最大值，因为需要知道 $l_j$ 和 $l_i$ 的相对位置关系，所以将位置 $l$ 作为下标。

对于前者，像平常的树状数组一样，用 $tree1_{pos}$ 维护 $1$ 到 $pos$ 的最大值；对于后者，与前者相反，用 $tree2_{pos}$ 维护 $pos$ 到 $mx$（最远展销会的位置）的最大值。

**考虑有同一天的情况：**

可以将所有同一天的展销会一起处理。已知这些展销会的取法一定不会走回头路（这样成本会更大），但是不知道应该从哪一个展销会开始。

所以先分别处理每一个展销会（不考虑其他同一天的展销会），得到从其开始的利润（即代码中第一遍遍历得到的 $f1_i$ 和 $f2_i$ 的初始值）。再分别（按位置）从小到大和从大到小遍历同一天的这些展销会，考虑从上一个展销会转移过来能否更优。

设从小到大转移时，展销会 $i$ 的最大利润为 $f1_i$，则 $f1_i = \max \left\{f1_{i-1} + dis_{i-1, i} , f1_i \right\}$，$f2$ 反之。最终的 $f_i = \max \left\{ f1_i, f2_i \right\}$，并用以更新树状数组。

这样，从（同一天的）这些展销会中任意一个展销会开始和任意一个展销会结束，并不走回头路地选取，所有的情况都被考虑到了。

**补充细节：** 最后应当回到 $s$ 的位置，所以需要在转移的最后补上一个位置为 $s$ 的项。

### AC 代码

```cpp
#include <bits/stdc++.h>
#define N (int)(5e5+3)
#define ll long long
using namespace std;

int n, u, d, s, mx;
ll tree1[N], tree2[N], f[N], f1[N], f2[N];
struct node {
	int t, l, m;
} a[N];

inline bool cmp(node i, node j) {
	if(i.t != j.t)
		return i.t < j.t;
	return i.l < j.l;
}

inline int lowbit(int i) {
	return (i & (-i));
}

void modify1(int pos, ll num) {
	for(int i=pos; i<=mx; i+=lowbit(i))
		tree1[i] = max(tree1[i], num);
}

ll query1(int pos) {
	ll ret = f[0];
	for(int i=pos; i>=1; i-=lowbit(i))
		ret = max(ret, tree1[i]);
	return ret;
}

void modify2(int pos, ll num) {
	for(int i=pos; i>=1; i-=lowbit(i))
		tree2[i] = max(tree2[i], num);
}

ll query2(int pos) {
	ll ret = f[0];
	for(int i=pos; i<=mx; i+=lowbit(i))
		ret = max(ret, tree2[i]);
	return ret;
}

inline void insert(int pos, ll num1, ll num2) {	// 分别插入两棵树状数组 
	modify1(pos, num1), modify2(pos, num2);
}

inline void init() {
	mx = max(mx, s);  // 更新树状数组最大位置 
	memset(f, 0xc0, sizeof(ll)*(n+2));
	memset(f1, 0xc0, sizeof(ll)*(n+2));
	memset(f2, 0xc0, sizeof(ll)*(n+2));
	memset(tree1, 0xc0, sizeof(ll)*(mx+2));
	memset(tree2, 0xc0, sizeof(ll)*(mx+2));
	a[n+1] = node{INT_MAX, s, 0};	// 最后应当回到 s 的位置 
	insert(s, (ll)s * u, -(ll)s * d);	// 从 s 点出发，插入树状数组 
}

int main() {
	scanf("%d%d%d%d", &n, &u, &d, &s);
	for(int i=1; i<=n; i++) {
		scanf("%d%d%d", &a[i].t, &a[i].l, &a[i].m);
		mx = max(mx, a[i].l);
	}
	init();
	sort(a+1, a+1+n, cmp);
	for(int i=1, j; i<=n+1; i++) {
		for(j=i; a[j+1].t==a[i].t && j+1<=n; j++);
		if(j != i) {  // 处理同一天的展厅 
			for(int k=i; k<=j; k++) 
				f1[k] = f2[k] = max(query1(a[k].l) + a[k].m - (ll)a[k].l * u, query2(a[k].l) + a[k].m + (ll)a[k].l * d);
		    for(int k=i+1; k<=j; k++)
				f1[k] = max(f1[k], f1[k-1] - (ll)(a[k].l-a[k-1].l) * u + a[k].m);
		    for(int k=j-1; k>=i; k--)
				f2[k] = max(f2[k], f2[k+1] - (ll)(a[k+1].l-a[k].l) * d + a[k].m);
		    for(int k=i; k<=j; k++) {
		        f[k] = max(f1[k], f2[k]);
		        insert(a[k].l, f[k] + (ll)a[k].l * u, f[k] - (ll)a[k].l * d);
		    }
			i = j;
			continue;
		}
		f[i] = max(query1(a[i].l) + a[i].m - (ll)a[i].l * u, query2(a[i].l) + a[i].m + (ll)a[i].l * d);
		insert(a[i].l, f[i] + (ll)a[i].l * u, f[i] - (ll)a[i].l * d);
	}
	printf("%lld\n", f[n+1]);
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)

一道 DP + 数据结构优化 + 贪心的题，层层递进。

### DP

我们先来考虑展销会时间两两不同的情况，这时候它们之间形成了一个拓扑关系，我们必然先 DP 时间靠前的，再 DP 时间靠后的。

我们将展销会按照时间排序，得到 DP 方程：

特别地，为了方便转移，我们定义：

$dp_0 = 0,l_0 = s,w_0 = 0,t_0 = 0$。

$l_{n+1} = s,w_{n+1} = 0,t_{n+1} = \infty$。

状态转移方程：

$dp_i = \max\{dp_j + \operatorname{Dis}(l_i,l_j)\} + w_i$，其中 $j < i$。

### 数据结构优化

我们根据 $\operatorname{Dis}(l_i,l_j)$，展开以上状态转移方程：

$dp_i = \max\{dp_j + l_j \times D - l_i \times D\}$

$dp_i = \max\{dp_j - l_j \times U + l_i \times U\}$

其中 $j<i$。

发现，可以用树状数组维护 $dp_i + l_i \times D$ 和 $dp_i - l_i \times U$ 的最大值。

到此，我们已经有了 $51$ 分。

### 贪心

问题的关键在于有一些展销会的时间会相同，无法形成拓扑顺序，所以我们要做的就是给它们定序。

可以直观地发现，如果我们跳跃地参加这些展销会，会多走更多的距离。

所以对于这些展销会，可以贪心地发现最优解一定是顺流而上或者逆流而下地参加这些展销会。

所以对于时间相同的展销会，只要正着转移一遍，倒着转移一遍即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 500010
ll dp[N],dpU[N],dpD[N],U,D;
int n,s;
struct B1
{
	ll mx[N];
	B1()
	{
		memset(mx,0x80,sizeof(mx));
	}
	inline void update(int x,ll y)
	{
		while(x <= 5e5+5)
		{
			mx[x] = max(mx[x],y);
			x += x & -x;
		}
	}
	inline ll query(int x)
	{
		ll ret = -1e18;
		while(x)
		{
			ret = max(ret,mx[x]);
			x -= x & -x;
		}
		return ret;
	}
}tr1;
struct B2
{
	ll mx[N];
	B2()
	{
		memset(mx,0x80,sizeof(mx));
	}
	inline void update(int x,ll y)
	{
		while(x)
		{
			mx[x] = max(mx[x],y);
			x -= x & -x;
		}
	}
	inline ll query(int x)
	{
		ll ret = -1e18;
		while(x <= 5e5+5)
		{
			ret = max(ret,mx[x]);
			x += x & -x;
		}
		return ret;
	}
}tr2;
struct node
{
	int t,p;
	ll w;
	inline bool friend operator<(const node &X,const node &Y)
	{
		if(X.t != Y.t) return X.t < Y.t;
		return X.p < Y.p; 
	}
}a[N];
inline void update(int i)
{
	tr1.update(a[i].p,dp[i] + D * a[i].p);
	tr2.update(a[i].p,dp[i] - U * a[i].p);		
}
inline void solve(int l,int r)
{
	F(i,l,r) dpD[i] = dpU[i] = max(tr1.query(a[i].p) - D * a[i].p,tr2.query(a[i].p) + U * a[i].p)+a[i].w;
	F(i,l+1,r) dpD[i] = max(dpD[i],dpD[i-1] - D * (a[i].p-a[i-1].p) + a[i].w);
	D(i,r-1,l) dpU[i] = max(dpU[i],dpU[i+1] - U * (a[i+1].p-a[i].p) + a[i].w);
	F(i,l,r)
	{   
		dp[i] = max(dpD[i],dpU[i]);
		update(i);
	}
}
int main()
{
	read(n),read(U),read(D),read(s);
	F(i,0,n+1) dp[i] = dpU[i] = dpD[i] = -1e18;
	dp[0] = 0;
	F(i,1,n) read(a[i].t),read(a[i].p),read(a[i].w);
	a[0] = (node){0,s,0},a[n+1] = (node){(int)1e9,s,0},a[n+2] = (node){0,0,0};
	update(0);
	sort(&a[1],&a[n+1]);
	int l = 1;
	F(i,1,n+1)
		if(a[i].t != a[i+1].t)
			solve(l,i),l = i+1;
	write(dp[n+1]);
	return 0;
}
```



---

## 作者：RedLycoris (赞：1)

考虑dp。

---

令 $dp_i$ 表示走到底 $i$ 个集市时的最大收益。

---

1.最朴素的dp

循环 $i$，枚举 $j$ 进行转移。

复杂度：$O(n^2)$

---

2.分离常项

假设现在是 $i$，要从 $j$ 转移

1.$place_j<place_i$

```dp[i]=max(dp[j]+U*(place[i]-place[j]))+val[i]```

有

$dp_j+U*(place_i-place_j)=dp_j-U*place_j+U*place_i$

所以

```dp[i]=max(dp[j]-U*place[j])+val[i]+U*place[i]```

用线段树/树状数组维护即可。

2.$j>i$

同理。

时间复杂度:$O(nlogn)$

---

3.日期相同的情况

贪心可得一定是从一个点直着走到另一个点，中间不会回头。

这里单独弄一个dp。

$dpl_i , dpr_i$ 表示以$i$为结束点，进过集市的开始点在 $i$ 的左边/右边的最大收益。

预处理出不考虑相同日期时每一个点的dp值，然后从左往右、从右往左贪心的递推即可。类似最大子段和。

---

Code:

```
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define mp make_pair
#define ri register int
#define ld long double
using namespace std;
const int mxn=1e6+6;
int dp[mxn];
vector<int>g[mxn];
int n,S,D,U;
struct market{
	int date,money,place;
}a[mxn];
inline bool operator <(market a,market b){
	if(a.date!=b.date)return a.date<b.date; 
	return a.place<b.place;
}
struct bit1{  //左边（前缀）
	int val[mxn];
	inline void init(){memset(val,-63,sizeof(val));}
	inline void upd(int x,int d){for(++x;x<mxn;x+=x&-x)val[x]=max(val[x],d);}
	inline int ask(int x){
		ri rt=-2147483647;
		for(++x;x;x-=x&-x)rt=max(rt,val[x]);
		return rt;
	}
}Left;
struct bit2{  //右边（后缀）
	int val[mxn];
	inline void init(){memset(val,-63,sizeof(val));}
	inline void upd(int x,int d){for(++x;x;x-=x&-x)val[x]=max(val[x],d);}
	inline int ask(int x){
		ri rt=-2147483647;
		for(++x;x<mxn;x+=x&-x)rt=max(rt,val[x]);
		return rt;
	}
}Right;
int tmpl[mxn],tmpr[mxn];
inline void cmax(int&x,int y){if(x<y)x=y;}
inline void Same(int L,int R){ //日期相同的情况
	for(ri i=L;i<=R;++i)tmpl[i]=tmpr[i]=max(Left.ask(a[i].place)-a[i].place*D,Right.ask(a[i].place)+a[i].place*U)+a[i].money;
	for(ri i=L+1;i<=R;++i)cmax(tmpl[i],tmpl[i-1]-(a[i].place-a[i-1].place)*D+a[i].money);
	for(ri i=R-1;i>=L;--i)cmax(tmpr[i],tmpr[i+1]-(a[i+1].place-a[i].place)*U+a[i].money);
	for(ri i=L;i<=R;++i){
		dp[i]=max(tmpl[i],tmpr[i]);
		Left.upd(a[i].place,dp[i]+a[i].place*D);
		Right.upd(a[i].place,dp[i]-a[i].place*U);
	}
}
inline void solve(){
	Left.init();Right.init();
	memset(dp,-63,sizeof(dp));
	scanf("%d%d%d%d",&n,&U,&D,&S);
	for(ri i=1;i<=n;++i)scanf("%d%d%d",&a[i].date,&a[i].place,&a[i].money);
	sort(a+1,a+n+1);
	a[n+1].place=S;a[0].place=S;a[n+1].date=a[n].date+1;++n;
	dp[0]=0;
	Left.upd(S,S*D);
	Right.upd(S,-S*U);
	for(ri i=1;i<=n;++i){
		if(a[i+1].date==a[i].date and i<=n){
			ri j=i+1;
			for(;j<=n and a[j].date==a[i].date;++j);
			Same(i,j-1);
			i=j-1;
			continue;
		}
		dp[i]=max(Left.ask(a[i].place)-a[i].place*D,Right.ask(a[i].place)+a[i].place*U)+a[i].money;
		Left.upd(a[i].place,dp[i]+a[i].place*D);
		Right.upd(a[i].place,dp[i]-a[i].place*U);
	}
	printf("%d\n",dp[n]);
}
int main(){
	ios_base::sync_with_stdio(false);
	int T=1;//cin>>T;
	for(;T--;)solve();
}
```

---

## 作者：Nygglatho (赞：0)

令 $dp_{t,i}$ 表示时间为 $t$，此时在 $i$ 结束的最大利润，$m_{t,i}$ 表示时间 $t$ 时 $l$ 点展销会的盈利，若不存在展销会则 $m_{t,i}$ 为 $0$。显然最后答案为 $\max(\max\{dp_{T_{\max},i}+D\times (S-i)\mid i<S\},\max\{dp_{T_{\max},i}+U\times (i-S)\mid i\ge S\})$。

先考虑没有两个展销会在同一天举行的情况。

转移分在上游和在下游转移，即：

- $dp_{t,0}=\begin{cases}U\times (S-i)& i<S\\D\times (i-S)& i\ge S\end{cases}$

- $\forall i>0,dp_{t,i}=\max(dp_{t-1,i},\max\{dp_{t-1,j}+D\times (i-j)\mid j<i\},\max\{dp_{t-1,j}+U\times (j-i)\mid j> i\})$。

然后考虑存在的情况。

显然一天内肯定是只朝一个方向走是最优的。

那么考虑分从上游到下游转移和从下游到上游转移。

令 $f_{t,i}$ 表示钦定上游到下游转移，$g_{t,i}$ 表示钦定从下游到上游转移，时间为 $t$，此时在 $i$ 结束的最大利润，有：

- $f_{t,i}=\max(dp_{t-1,i},\max\{f_{t,j}+D\times (i-j)\mid j<i\},\max\{dp_{t-1,j}+U\times (j-i)\mid j> i\})$。

- $g_{t,i}=\max(dp_{t-1,i},\max\{dp_{t-1,j}+D\times (i-j)\mid j<i\},\max\{g_{t,j}+U\times (j-i)\mid j>i\})$。

- $dp_{t,i}=\max(f_{t,i},g_{t,i})$。

这样是 $O((L_{\max})^2\times T_{\max})$ 的，考虑优化。

首先显然 $dp_t$ 是只和 $dp_{t-1}$ 有关的，因此可以滚动数组把 $t$ 这一维删掉。然后就可以用四个线段树分别维护 $\max\{f_{j}+D\times (i-j)\},\max\{dp_{j}+U\times (j-i)\},\max\{dp_{j}+D\times (i-j)\},\max\{g_{j}+U\times (j-i)\}$，因为 $D\times (i-j),U\times (j-i)$ 的相对大小是不改变的，每次只需要整体修改这个，查询合法部分的 $\max$，加入 $f_j$ 和 $g_j$。最后再更新 $dp_j$，这样就把复杂度降到了 $O(L_{\max}\log (L_{\max})\times T_{\max})$。

然后可以发现对于 $j$ 只需要在存在展销会的这几天更新 $dp_j$。否则更新 $dp_j$ 时假如从 $k$ 转移到 $j$，显然转移时直接找 $dp_k$ 转移一定比找 $dp_j$ 转移不劣，统计答案时同理。

那么只需要在线段树里存下 $dp_j$ 的值，然后令 $f_j,g_j\gets dp_j$，如果这一天 $j$ 存在展销会，那么就更新 $f_j,g_j,dp_j$，同时更新线段树里的值。复杂度 $O(n\log L_{\max})$。常数略大。

```cpp
struct Info {
    int l; ll m;
} ;

vector <Info> v[N];
int n, s;
ll u, d;
constexpr int w = 500005;
ll dp1[N], dp2[N], dp[N], tmp[N];
struct Sgt {
    ll d[N << 2], b[N << 2];
    void Pd (int l, int r, int p) {
        int m = (l + r) >> 1;
        d[p << 1] += b[p], d[p << 1 | 1] += b[p], b[p << 1] += b[p], b[p << 1 | 1] += b[p], b[p] = 0LL;
    }
    void Add (int l, int r, int s, int t, int p, ll v) {
        if (l <= s && t <= r) {
            d[p] += v;
            b[p] += v;
            return ;
        }
        int m = (s + t) >> 1;
        Pd (s, t, p);
        if (l <= m) Add (l, r, s, m, p << 1, v);
        if (m < r) Add (l, r, m + 1, t, p << 1 | 1, v);
        d[p] = max (d[p << 1], d[p << 1 | 1]);
    }
    ll Qry (int l, int r, int s, int t, int p) {
        if (l <= s && t <= r) return d[p];
        int m = (s + t) >> 1;
        Pd (s, t, p);
        ll res = -inf;
        if (l <= m) res = Qry (l, r, s, m, p << 1);
        if (m < r) res = max (res, Qry (l, r, m + 1, t, p << 1 | 1));
        return res;
    }
    void Update (int x, ll v) {
        ll tmp = Qry (x, x, 0, w, 1);
        Add (x, x, 0, w, 1, v - tmp);
    }
} st1, st2; // 这里开的线段树重复使用，所以只开了两颗
int main () {
    // OPEN
    IOS
    cin >> n >> u >> d >> s;
    F (i, 1, n) {
        int t, l, m;
        cin >> t >> l >> m;
        v[t].push_back ({l, m});
    }
    int ls = s;
    F (i, 0, w) {
        if (i < s) dp[i] = - u * (s - i);
        else dp[i] = - d * (i - s);
        dp1[i] = dp2[i] = -inf;
    }
    F (i, 0, w) st1.Add (i, i, 0, w, 1, - d * (ls - i) + dp[i]);
    F (i, 0, w) st2.Add (i, i, 0, w, 1, - u * (i - ls) + dp[i]);
    F (t, 1, 500000) {
        sort (v[t].begin (), v[t].end (), [] (Info x, Info y) {return x.l < y.l; });
        for (auto [l, m] : v[t]) tmp[l] = dp[l];
        for (auto [l, m] : v[t]) {
            st1.Add (0, w, 0, w, 1, d * (ls - l));
            st2.Add (0, w, 0, w, 1, u * (l - ls));
            ls = l;
            ll tmp1 = dp1[l];
            dp1[l] = max (st1.Qry (0, l - 1, 0, w, 1), st2.Qry (l + 1, w, 0, w, 1)) + m;
            st1.Update (l, max (dp1[l], tmp1));
            st2.Update (l, max (dp1[l], tmp1));
        }
        for (auto [l, m] : v[t]) st1.Update (l, tmp[l] - d * (ls - l)), st2.Update (l, tmp[l] - u * (l - ls));
        sort (v[t].begin (), v[t].end (), [] (Info x, Info y) {return x.l > y.l; });
        for (auto [l, m] : v[t]) {
            st1.Add (0, w, 0, w, 1, d * (ls - l));
            st2.Add (0, w, 0, w, 1, u * (l - ls));
            ls = l;
            ll tmp1 = dp2[l];
            dp2[l] = max (st1.Qry (0, l - 1, 0, w, 1), st2.Qry (l + 1, w, 0, w, 1)) + m;
            st1.Update (l, max (dp2[l], tmp1));
            st2.Update (l, max (dp2[l], tmp1));
        }
        for (auto [l, m] : v[t]) dp[l] = max (dp[l], max (dp1[l], dp2[l]));
        for (auto [l, m] : v[t]) st1.Update (l, dp[l] - d * (ls - l)), st2.Update (l, dp[l] - u * (l - ls));
        for (auto [l, m] : v[t]) dp1[l] = dp2[l] = -inf;
    }
    ll ans = 0LL;
    F (i, 1, 500000) {
        if (i < s) ans = max (ans, dp[i] - d * (s - i));
        else ans = max (ans, dp[i] - u * (i - s));
    }
    cout << ans << '\n';
}
```

---

## 作者：无名之雾 (赞：0)

本题被无量出题人搬到了省选模拟 T1，场上怒写 $2.5$ 小时导致后面没时间打萌萌 T2，$100+25+25$ 遗憾离场。写题解纪念之。

## solution

阅读题面不难发现当保证多个展销不会在同一天举办时，这道题目就变成了一个非常经典的 SGT 优化 dp。也就是 [AT_abc353_g](https://www.luogu.com.cn/problem/AT_abc353_g)。


我们考虑一个比较好写出来的 $n^2$ dp。

我们设 $f_i$ 表示参加第 $i$ 个展销会会获得的最大收益。方程就很好写出来了：

$$f_i=\max \{ f_j-cost_{j,i} \}$$

其中 $cost_{i,j}$ 表示从 $i$ 到 $j$ 多要花费的价值。

显然这个式子拆开后直接求前后缀 $\max$ 即可。

随便 SGT/BIT 维护一下就可以了。

现在我们来考虑存在多个展销会在同一天的情况。

一个显然的结论就是我们选择参加的展销会必定是连续的一段区间，所以我必定最多只走连续的一趟顺流路线和逆流路线。

因为我们可以发现，如果我参加的展销会 $i$ 和展销会 $j$，满足 $L_i<L_j$，那么对于所有 $L_i<L_k<L_j$ 的展销会 $k$ 也必然参加。

令 $f_i$ 表示参加展销会 $i$ 且 $i$ 之前本日不参加展销会的最大获利，$f_{U_i}$ 表示对于与 $i$ 同一天内的展销会只考虑逆流参加时的最大获利，$f_{D_i}$ 表示对于与 $i$ 同一天内的展销会只考虑顺流参加时的最大获利。

对于 $f_{U_i}$ 有转移：

$$f_{U_i} = \max {f_i , f_{i+1} + cost_{i+1,i}}$$

对于 $f_{D_i}$ 有转移：

$$f_i = \max {f_i , f_{i-1} + cost_{i-1,i}}$$

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1; 
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void out(int x){
    if(x==0){putchar('0');return;}
	int len=0,k1=x,c[10005];
	if(k1<0)k1=-k1,putchar('-');
	while(k1)c[len++]=k1%10+'0',k1/=10;
	while(len--)putchar(c[len]);
}
const int N=5e5+5,INF=-INT_MAX;
struct node{
    int day,x,w;
    bool operator <(const node &b)const{
    	if(day==b.day)return x<b.x;
    	else return day<b.day;
    }
}a[N];
int f[N],tmp[N],tmp2[N];    
int MXu,MXd,n,u,d,s,maxn;
struct SGT{
	struct tr{
	    int maxu,maxd;
	}t[N<<2];
	int ls(int p){return p<<1;}
	int rs(int p){return p<<1|1;}
	void pushup(int p){
	    t[p].maxd=max(t[ls(p)].maxd,t[rs(p)].maxd);
	    t[p].maxu=max(t[ls(p)].maxu,t[rs(p)].maxu);
	}
	void build(int l,int r,int p){
	    if(l==r){t[p].maxd=t[p].maxu=INF;return;}
	    int mid=(l+r)>>1;
	    build(l,mid,ls(p));build(mid+1,r,rs(p));
	    pushup(p);
	}
	void update(int pp,int l,int r,int p){
	    if(l==r){
	        t[p].maxd=f[pp]+a[pp].x*d;    
			t[p].maxu=f[pp]-a[pp].x*u;
	        return;
	    }
	    int mid=(l+r)>>1;
	    if(a[pp].x<=mid)update(pp,l,mid,ls(p));
	    else update(pp,mid+1,r,rs(p));
	    pushup(p);
	}
	void query(int L,int R,int l,int r,int p){
	    if(L<=l&&r<=R){
	        MXd=max(t[p].maxd,MXd);
			MXu=max(t[p].maxu,MXu);
	        return;
	    }
	    int mid=(l+r)>>1;
	    if(L<=mid)query(L,R,l,mid,ls(p));
	    if(R>mid)query(L,R,mid+1,r,rs(p));
	}	
}sgt;
signed main(){
	// freopen("salesman.in","r",stdin);
	// freopen("salesman.out","w",stdout);
    n=read(),u=read(),d=read(),s=read();
    a[1]={0,s,0};n++;
    for(int i=2;i<=n;i++){
    	a[i]={read(),read(),read()};
        maxn=max(maxn,a[i].x);
    }
    sort(a+1,a+n+1);n++;
    a[n]={a[n-1].day+1,s,0};
    maxn=max(maxn,s);
    sgt.build(1,maxn,1);    
    sgt.update(1,1,maxn,1);
    for(int i=2,j;i<=n;i=j+1){
        for(j=i;a[j].day==a[i].day;j++){
            f[j]=INF;
            MXu=INF;sgt.query(a[j].x,maxn,1,maxn,1);
            f[j]=max(f[j],MXu+a[j].x*u);
            MXd=INF;sgt.query(1,a[j].x,1,maxn,1);
            f[j]=max(f[j],MXd-a[j].x*d);
            f[j]+=a[j].w;
        }
		j--;tmp[i]=f[i];tmp2[j]=f[j];
        for(int k=i+1;k<=j;k++){
        	tmp[k]=max(f[k],tmp[k-1]-(a[k].x-a[k-1].x)*d+a[k].w);
		}
        for(int k=j-1;k>=i;k--){
        	tmp2[k]=max(f[k],tmp2[k+1]-(a[k+1].x-a[k].x)*u+a[k].w);
		}
        for(int k=i;k<=j;k++){
            f[k]=max(f[k],max(tmp[k],tmp2[k]));
            sgt.update(k,1,maxn,1);
        }
    }
    cout<<f[n];
    return 0;
}
```

---

