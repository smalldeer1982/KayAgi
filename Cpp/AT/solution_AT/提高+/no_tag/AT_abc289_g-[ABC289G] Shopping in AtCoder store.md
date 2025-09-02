# [ABC289G] Shopping in AtCoder store

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc289/tasks/abc289_g

高橋くんは AtCoder 商店を経営しています。 AtCoder 商店には $ N $ 人の客が訪れ、$ M $ 個の商品が売られています。 $ i $ 番目 $ (1\leq\ i\leq\ N) $ の客は購買意欲 $ B\ _\ i $ を持っています。 $ j $ 番目 $ (1\leq\ j\leq\ M) $ の商品の商品価値は $ C\ _\ j $ です。

高橋くんはそれぞれの商品に値段をつけます。 $ i $ 番目の客は、$ j $ 番目の商品の値段 $ P\ _\ j $ が次の条件を満たすような商品のみを、すべて $ 1 $ 個ずつ購入します。

- $ B\ _\ i+C\ _\ j\geq\ P\ _\ j $
 
$ j=1,2,\ldots,M $ について、高橋くんが売り上げが最大になるような値段をつけたときの $ j $ 番目の商品の売り上げを求めてください。 ただし、$ j $ 番目の商品の売り上げとは、$ P\ _\ j $ に $ j $ 番目の商品を買う人数をかけたものです。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10^5 $
- $ 1\leq\ M\leq2\times10^5 $
- $ 0\leq\ B\ _\ i\leq10^9\quad(1\leq\ i\leq\ N) $
- $ 0\leq\ C\ _\ i\leq10^9\quad(1\leq\ i\leq\ M) $
- 入力はすべて整数
 
### Sample Explanation 1

たとえば、$ 1 $ 番目の商品の値段を $ 320 $ にすると、$ 2,3,4,5 $ 番目の客が購入します。 $ 1 $ 番目の商品の売り上げは $ 1280 $ になります。 $ 1 $ 番目の商品の売り上げを $ 1280 $ より大きくすることはできないので、$ 1 $ 番目に出力すべき値は $ 1280 $ です。

### Sample Explanation 2

購買意欲が同じ $ 2 $ 人や、商品価値が同じ $ 2 $ 品があることもあります。

### Sample Explanation 4

売り上げが $ 32\operatorname{bit} $ 整数におさまらない場合があることに注意してください。

## 样例 #1

### 输入

```
5 4
100 200 300 400 500
120 370 470 80```

### 输出

```
1280 2350 2850 1140```

## 样例 #2

### 输入

```
4 4
0 2 10 2
13 13 0 4```

### 输出

```
52 52 10 18```

## 样例 #3

### 输入

```
12 15
16 592 222 983 729 338 747 61 451 815 838 281
406 319 305 519 317 590 507 946 365 5 673 478 340 176 2```

### 输出

```
6280 5466 5382 7410 5454 8120 7290 11680 5870 3670 8950 7000 5620 4608 3655```

## 样例 #4

### 输入

```
5 5
1000000000 1000000000 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
10000000000 10000000000 10000000000 10000000000 10000000000```

# 题解

## 作者：Arghariza (赞：3)

提供一个不用脑子的做法。

将顾客按照 $B_i$ 从大到小排序，显然一个商品 $i$ 取的是一个前缀顾客。

略加转换，对每个商品 $j$，考虑枚举买它的顾客人数，显然有 $h_j=\max\{i(B_i+C_j)\}$。

那么 $h_j=iC_j+iB_i$，是 $y=kx+b$ 的形式。

李超树维护即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace vbzIO {
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define pc putchar
	#define ps puts
	#define pi pair<int, int>
	#define tu3 tuple<int, int, int>
	#define tu4 tuple<int, int, int, int>
	#define mp make_pair
	#define mt make_tuple
	#define fi first
	#define se second
	#define pb push_back
	#define ins insert
	#define era erase
	inline int read () {
		char ch = gh();
		int x = 0;
		bool t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? ~(x - 1) : x;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using vbzIO::read;
using vbzIO::write;

const int maxn = 2e5 + 200;
const int w = 1e9;
struct lct { int lc, rc, id; } tr[maxn << 2];
int n, m, rt, tot, a[maxn], b[maxn];
pi p[maxn];

#define ls tr[x].lc
#define rs tr[x].rc
#define mid ((l + r) >> 1)
int cmp(int x, int y) { return x == y ? 0 : (x > y ? 1 : -1); }
int gety(int id, int x) { return p[id].fi * x + p[id].se; }
void push(int l, int r, int s, int &x) {
    if (!x) x = ++tot;
    int &t = tr[x].id;
    if (cmp(gety(s, mid), gety(t, mid)) == 1) swap(s, t);
    int fl = cmp(gety(s, l), gety(t, l)), fr = cmp(gety(s, r), gety(t, r));
    if (fl == 1 || (!fl && s < t)) push(l, mid, s, ls);
    if (fr == 1 || (!fr && s < t)) push(mid + 1, r, s, rs);
}

int qry(int l, int r, int p, int x) {
    if (!x) return 0;
    if (l == r) return gety(tr[x].id, p);
    int res = gety(tr[x].id, p);
    if (p <= mid) return max(res, qry(l, mid, p, ls));
    else return max(res, qry(mid + 1, r, p, rs));
}

signed main() {
	n = read(), m = read(), p[0] = mp(0, -w * w);
    for (int i = 1; i <= n; i++) a[i] = read();
    sort(a + 1, a + n + 1, greater<int> ());
    for (int i = 1; i <= m; i++) b[i] = read();
    for (int i = 1; i <= n; i++) {
        p[i] = mp(i, i * a[i]);
        push(0, w, i, rt);
    }
    for (int i = 1; i <= m; i++) 
        write(qry(0, w, b[i], rt)), pc(' ');
	return 0;
}
```

---

## 作者：JWRuixi (赞：3)

~~VP 上大分，但我没打，哭~~

- 题意

有 $n$ 个顾客，$m$ 个物品，每个顾客有一个倾向性 $B$，每个物品有一个价值 $C$。第 $i$ 个顾客会买第 $j$ 个物品当且仅当 $P_j\le B_i+C_j$，$P$ 为售价。对于每个物品求大化 $P_j\sum [P_j\le B_i+C_j]$。

- 分析

考虑将顾客按倾向性从大到小排序，那么会买一个物品的顾客显然是一个前缀，若要宁顾客 $i$ 买物品 $j$，则最大收益为 $i(B_i+C_j)$，问题转化成对于每个 $j$，求：
$$\max\limits_{i=1}^n\{i(B_i+C_j)\}$$
也就是：
$$\max\limits_{i=1}^n\{iB_i-i(-C_j))\}$$
看到这一步做法就已经呼之欲出了，这显示一个斜率优化的形式，设 $y_i=iB_i,x_i=i,k_j=-C_j$，那显然可以构造出来一个斜率单调递减的凸包，求其切线的截距，再将 $C$ 从大到小排序即可。

时间复杂度 $\mathcal O(n\log n)$，瓶颈在排序。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define int long long
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read () {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void write(long long x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
}

using IO::read;
using IO::write;

const int maxn(2e5 + 7);
int n, m, b[maxn], c[maxn], stk[maxn], top, ans[maxn];

struct pNode {
    int x, y;
    inline pNode operator - (const pNode &rhs) const {
        return {x - rhs.x, y - rhs.y};
    }
    inline int operator * (const pNode &rhs) const {
        return x * rhs.y - y * rhs.x;
    }
} p[maxn], q[maxn];

inline double slp (int i, int j) {
    return double(p[i].y - p[j].y) / (p[i].x - p[j].x);
}

signed main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    sort(b + 1, b + n + 1, [] (const int &x, const int &y) -> bool { return x > y; });
    for (int i = 1; i <= n; i++) p[i].x = i, p[i].y = b[i] * i;
    for (int i = 1; i <= m; i++) c[i] = read(), q[i].x = i, q[i].y = -c[i];
    for (int i = 1; i <= n; i++) {
        while (top > 1 && (p[stk[top - 1]] - p[stk[top]]) * (p[stk[top]] - p[i]) > 0) --top;
        stk[++top] = i;
    }
    sort(q + 1, q + m + 1, [] (const pNode &u, const pNode &v) -> bool { return u.y > v.y; });
    for (int i = 1, j = 1; i <= m; i++) {
        for (; j < top && slp(stk[j], stk[j + 1]) > q[i].y; j++);
        ans[q[i].x] = p[stk[j]].y - p[stk[j]].x * q[i].y;
    }
    for (int i = 1; i <= m; i++) write(ans[i]), putchar(' ');
}
// I love WHQ!
```

---

## 作者：EnofTaiPeople (赞：3)

### Part1 题意简述

$n$ 个客人，每个人有期望值 $B_i$，$m$ 件商品，有权值 $C_i$，你需要**分别**给每一件商品定一个价格 $P_i$，如果客人 $x$ 满足 $B_x+C_i\ge P_i$，他就会买这件商品，最大化每件商品的销售额，即买的人数与价值之积，$n,m\le2\times10^5$。

### Part2 问题转化

将客人按 $B_i$ 从大到小排序，若一个客人会买，那么期望值比他大（比他靠前）的都会购买，考虑一件商品 $y$，恰好让第 $x$ 位客人购买，那么销售额就为（不考虑 $x$ 后面与 $x$ 期望值相等的人，因为他们更优，会算到）$w(x,y)=x(B_x+C_y)$。

### Part3 解决问题

以上是一个一次函数，你已经可以用 Li-Chao Tree 解决了，不过我觉得推出四边形不等式用分治更好写一些，所以：

将商品按 $C_i$ 从小到大排序，对于任意的 $a<b,c<d$，都有 $w(a,c)+w(b,d)-w(a,d)-w(b,c)$

$=a(B_a+C_c)+b(B_b+C_d)-a(B_a+C_d)-b(B_b+C_c)$

$=(a-b)(C_c-C_d)\ge 0$

即 $w(a,c)+w(b,d)\ge w(a,d)+w(b,c)$，相交优于包含，满足四边形不等式，具有决策单调性，然后分治解决。

时间复杂度 $O((n+m)\log(n+m))$，空间 $O(n+m)$：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
using ll=long long;
int T,n,m,c[N],b[N],p[N];
ll ans[N];
ll W(int l,int r){
    return ll(b[l]+c[p[r]])*l;
}
void solve(int l,int r,int L,int R){
    if(l>r||L>R)return;
    int md=L+R>>1,i,nl=l;ll mx=W(l,md),nw;
    for(i=r;i>l;--i)if((nw=W(i,md))>mx)mx=nw,nl=i;
    ans[p[md]]=mx;
    if(L<md)solve(l,nl,L,md-1);
    if(md<R)solve(nl,r,md+1,R);
}
int main(){
    ios::sync_with_stdio(false);
    int i,x,y,l,r;
    cin>>m>>n;
    for(i=1;i<=m;++i)cin>>b[i];
    for(i=1;i<=n;++i)cin>>c[i],p[i]=i;
    sort(b+1,b+m+1,greater<int>());
    sort(p+1,p+n+1,[&](int x,int y){return c[x]<c[y];});
    solve(1,m,1,n);
    for(i=1;i<=n;++i)printf("%lld%c",ans[i]," \n"[i==n]);
    return 0;
}
```

---

## 作者：CmsMartin (赞：2)

[更好的阅读体验](http://cmsblog.top/archives/abc289gshoppinginatcoderstore)

## 题目描述

[题目传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc289_g)

## 思路

先将 $B$ 和 $C$ 从小到大排序。显然的，每一个 $P_i$ 都可以表示为 $B_j + C_i$。称 $B_j$ 为 $C_i$ 的最优决策。

然后还可以发现答案具有单调性，如果 $B_j$ 是 $C_i$ 的最优决策，那么 $B_k(B_k < B_j)$ 不可能是 $C_{l} < C_i$ 的最优决策。

于是我们可以进行分治。

具体的，就是可以在分治的子任务中来选择最排完序中间的一个客人作为购买的最后一个人，然后枚举商品计算贡献，最后递归进去就好了。

具体看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 10;

ll Ans[MAXN], B[MAXN];
pair<ll, int> C[MAXN];
int N, M;

void solve(int l1, int r1, int l2, int r2) {
	if (l1 > r1) return;
	int mid = l1 + r1 >> 1;
	ll ans = 0, pos = 0;
	for (int i = r2; i >= l2; i--) {
		if ((B[i] + C[mid].first) * (N - i + 1) > ans) {
			ans = (B[i] + C[mid].first) * (N - i + 1);
			pos = i;
		}
	}
	Ans[C[mid].second] = ans;
	solve(l1, mid - 1, pos, r2);
	solve(mid + 1, r1, l2, pos);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= N; i++) cin >> B[i];
	for (int i = 1; i <= M; i++) {
		cin >> C[i].first;
		C[i].second = i;
	}
	sort(B + 1, B + 1 + N);
	sort(C + 1, C + 1 + M);
	solve(1, M, 1, N);
	for (int i = 1; i <= M; i++) cout << Ans[i] << " ";
	return 0;
} 
```

---

## 作者：_Imaginary_ (赞：2)

AT 好久没出模板题了，动态开点李超树万岁。

## Problem

给定 $B_1\dots B_n$，有 $m$ 次询问，每次询问 $C$，要求回答 $\max (k\times P)$，其中 $P$ 是自己选定的，$k$ 是满足 $B_i+C\ge P$ 的 $i$ 的个数。

## Solution

显然，$B_i$ 越大，越容易满足。

显然，$P$ 最终一定会取某一个 $B_i+C$。

因此，我们可以把 $B_i$ 从大到小排序。

这时，如果选择了 $B_k$（这里先不考虑 $B_i$ 有相同的情况，其实如果这样的话一定是选更靠后的 $B_i$ 更优），就恰好对应 $k\times (B_k+C)$，即 $kC+kB_k$。

看到了吗？每一个 $B_k$ 对应一条直线 $y=kx+kB_k$，查询 $C$ 就是所有直线在这个位置的最大值。

最后套一个动态开点李超树模板就完事了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=0x3f3f3f3f3f3f3f3f;
const int N=200005;
struct lcs{
	int ls,rs;
	ll k,b;
	lcs(){}
	lcs(ll K,ll B){ls=rs=0,k=K,b=B;}
}t[N<<2];
int tot=1;
void add(int x,ll l,ll r,ll k,ll b)
{
	if(x==0) return;
	ll tk=t[x].k,tb=t[x].b;
	ll mid=(l+r)>>1;
	if(l*k+b>=l*tk+tb && r*k+b>=r*tk+tb)
	{
		t[x].k=k; t[x].b=b;
		return;
	}
	else if(l*k+b<l*tk+tb && r*k+b<r*tk+tb) return;
	else
	{
		if(!t[x].ls) t[x].ls=++tot,t[tot]=lcs(tk,tb);
		else add(t[x].ls,l,mid,tk,tb);
		if(!t[x].rs) t[x].rs=++tot,t[tot]=lcs(tk,tb);
		else add(t[x].rs,mid+1,r,tk,tb);
		t[x].k=k,t[x].b=b;
	} 
}
ll query(int x,ll l,ll r,ll g)
{
	if(x==0) return -inf;
	ll mid=(l+r)>>1;
	ll ret=g*t[x].k+t[x].b;
	if(g<=mid) ret=max(ret,query(t[x].ls,l,mid,g));
	else ret=max(ret,query(t[x].rs,mid+1,r,g));
	return ret;
}
int n,m;
ll b[N],c[N];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	sort(b+1,b+n+1,greater<ll>());
	for(int i=1;i<=n;i++) add(1,-1,1e9,1ll*i,1ll*i*b[i]);
	for(int i=1;i<=m;i++) 
	{
		scanf("%lld",&c[i]);
		printf("%lld ",query(1,-1,1e9,c[i]));
	}
	return 0;
}

```

---

## 作者：Filberte (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_abc289_g)
## 思路
把 $b$ 数组从大到小排序，对于一个固定的价格 $p$，有以下 $3$ 个显然的性质：

- $b$ 相同的顾客，要么全买要么全不买
- 愿意购买它的顾客肯定是一个前缀
- 若当前的价值为 $c$，$p$ 必然为 $c + b_i$。

所以对于第 $x$ 个物品，其答案为 $\max\limits_{i\in[1,n]} i\cdot(b_i + c_x) = c_xi+ib_i$。这玩意用李超线段树维护一下就好了。注意 $y$ 值相同的时候要 $x$ 较大的那一个。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2e5 + 100, Mx = 1e9;
const int maxn = 6e6 + 100;
int n, m, rt;
int a[N];
ll k[N], b[N];
int lc[maxn], rc[maxn], id[maxn], idx;
ll f(int u, int x){return k[u] * x + b[u];}
void Add(int &u, int l, int r, int p){
    if(!u) u = ++idx;
    int Mid = (l + r) >> 1;
    if(f(p, Mid) > f(id[u], Mid) || f(p, Mid) == f(id[u], Mid) && p > id[u]) swap(id[u], p);
    if(!p) return ;
    if(f(p, l) > f(id[u], l) || f(p, l) == f(id[u], l) && p > id[u]) Add(lc[u], l, Mid, p);
    if(f(p, r) > f(id[u], r) || f(p, r) == f(id[u], r) && p > id[u]) Add(rc[u], Mid + 1, r, p);
}
ll qry(int u, int l, int r, int x){
    if(l == r) return f(id[u], x);
    ll res = f(id[u], x);
    int Mid = (l + r) >> 1;
    if(x <= Mid && lc[u]) res = max(res, qry(lc[u], l, Mid, x));
    if(x > Mid && rc[u]) res = max(res, qry(rc[u], Mid + 1, r, x));
    return res;
}
int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    sort(a + 1, a + 1 + n, greater<int> ());
    k[0] = 0, b[0] = -1e18;
    for(int i = 1;i <= n;i++){
        k[i] = i, b[i] = 1ll *  i * a[i];
        Add(rt, 0, Mx, i);
    }
    for(int i = 1;i <= m;i++){
        int x;cin >> x;
        cout << qry(rt, 0, Mx, x) << " ";
    }
    return 0;
}
```

---

## 作者：ran_qwq (赞：1)

对于每个 $j$，$P_j$ 只能是某个 $B_i+C_j$。否则 $P_i$ 可以取到更大且买的人数不变。

将 $B$ 从小到大排序。问题转化为对于每个 $j$，找一个 $i$，使得 $i\sim N$ 的顾客都买它，最大化 $(B_i+C_j)(N-i+1)$ 的值，时间复杂度 $O(N^2)$。

如果再将 $C$ 从小到大排序，容易看出满足决策单调性，证明：

> 当价值增加 $1$ 时，决策点取到 $i$ 会对答案产生 $N-i+1$ 的贡献。$i$ 越靠近 $N$，贡献越小。
>
> 则设当前价格为 $x$，决策点为 $y$。价格加到 $x+1$ 时 $y+1\sim N$ 加的贡献严格小于 $y$ 加的贡献，所以 $y+1\sim N$ 更加不优。证毕。

考虑分治。设当前分治区间为 $[l,r]$，当前商品为 $x=\lfloor\dfrac{l+r}2\rfloor$，当前决策点区间为 $[L,R]$，找到的决策点为 $y$。则根据决策单调性，往左分治时决策点只需要在 $[y,R]$ 中找，往右分治时决策点只需要在 $[L,y]$ 中找。

时间复杂度 $O(n\log n)$。

```cpp
int n,m,a[N]; pii b[N]; ll ans[N];
void sol(int l,int r,int L,int R) {
	int mid=l+r>>1,p; ll mx=0,tmp; for(int i=R;i>=L;i--) if(mx<(tmp=1ll*(n-i+1)*(a[i]+b[mid].fir))) mx=tmp,p=i;
	ans[b[mid].sec]=mx; if(l<mid) sol(l,mid-1,p,R); if(mid<r) sol(mid+1,r,L,p);
}
void QwQ() {
	n=rd(),m=rd(); for(int i=1;i<=n;i++) a[i]=rd(); for(int i=1;i<=m;i++) b[i]={rd(),i};
	sort(a+1,a+1+n),sort(b+1,b+1+m),sol(1,m,1,n); for(int i=1;i<=m;i++) wrll(ans[i]," ");
}
```

---

## 作者：CrTsIr400 (赞：1)

# [ABC289G-Shopping in AtCoder store](https://atcoder.jp/contests/abc289/tasks/abc289_g)

题意：有 $n$ 位顾客，有 $m$ 种商品，初始价值为 $c_i$，顾客 $i$ 选择第 $j$ 种商品当且仅当 $b_i+c_j\ge p_j$。其中 $b,c$ 已给定，求给每种商品定价 $p$ 使得销售额最大化。

思路：可以按照 $b$ 从大到小排序，对于每个商品 $i$ 枚举购买它的人数 $j$，那么答案就是 $j(b_j+c_i)$。

比赛时被坑了一会是因为这个答案并不满足单调性，所以考虑另外的思路。

拆开这个价值，原式就是 $j\cdot c_i+j\cdot b_j$，这个时候假设 $j$ 是可以已知的数据，而把 $c_i$ 设成 $x$ 即未知的数据，那么式子就转化成了 $K_jx+B_j$ 的形式（令 $K_j=j,B_j=j\cdot b_j$）。

对于一个给定的 $c_i$ 我们需要求得对于所有一次函数的最大值，这个可以使用半平面交维护一个下凸壳。

下凸壳的维护，只需要维护一个斜率递增的直线集合即可，对于一条斜率更大的直线我们可以按照单调性判掉交点在其右边的所有线段。

可以去做这个题目，[P3194 [HNOI2008]水平可见直线](https://www.luogu.com.cn/problem/P3194)。

对于本题只需要先算出凸壳上相邻两条直线的交点，然后按照交点集二分这个 $c_i$ 对应的是第几条线段即可。

时间复杂度 $O(n\log n+m\log n)$。

```cpp
const I N=2e5+10;
I b[N],n,m,q[N],t;
LL k[N];
double jdx(I i,I j){
	return -1.0*(k[i]-k[j])/(i-j);
}double lb[N];
int main(){
	in(n,m);
	for(I i=1;i<=n;++i)in(b[i]);
	sort(b+1,b+n+1,greater<I>());
	for(I i=1;i<=n;++i){
		k[i]=1ll*b[i]*i;
		while(t>1&&jdx(q[t-1],i)<=jdx(q[t-1],q[t]))--t;
		q[++t]=i;
	}for(I i=2;i<=t;++i){
		lb[i]=jdx(q[i-1],q[i]);
	}lb[t+1]=inf;
	for(I i=1,c,id;i<=m;++i){
		in(c);
		id=upper_bound(lb+1,lb+t+2,c)-lb-1;
		printf("%lld ",1ll*(c+b[q[id]])*q[id]);
	}
	return 0;
}
```



---

## 作者：Mikefeng (赞：1)

# [ABC289G] Shopping in AtCoder store

## 题目翻译

有 $n$ 个人买 $m$ 件商品，如果 $P_j\le B_i+C_j$ 则第 $i$ 个人会买第 $j$ 件商品，问每个商品的最大总利润分别是多少。

$1\le n,m\le2\times10^5$

## 做法

如果只有一个商品，那很简单，按照 $B_i$ 排序，每次枚举有 $k$ 个人买的利润是多少，取 $n$ 次的最大值。

但是由于有 $m$ 个物品，这样做时间复杂度是 $O(nm)$ 的。

我们考虑 ：

$$ans_i=\max_{j=1}^n f_j+j\times C_i$$

相当于对一个数组进行全局加等差数列和求全局最大值。

可以维护一个上凸包，与 $y=C_i x$ 相切的点就是 $ans_i$ 取到最大值的点。

又发现随着 $C_i$ 增大，切点的位置是单调变化的，由此可以 $O(n)$ 求解。

时间复杂度 $O(n\log n)$，瓶颈在于将 $B_i$ 和 $C_i$ 排序。

## 代码

```cpp
inline ll read(){
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const ll N=2e5+5;
ll n,m,maxn;
vector<ll> v;
vector<pii> g;
ll a[N],b[N],ans[N];
ll f[N],s[N],t;
inline ll get_val(ll val,ll id){
//	cout<<id<<" "<<val<<endl;
	return f[n-id+1]+id*val;
}
inline void get_ans(){
	ll cnt=0;
	F(i,1,m) g.emplace_back(b[i],i);
	sort(g.begin(),g.end());
	F(i,0,(ll)v.size()-1){
		while(cnt<m&&i!=(ll)v.size()-1&&get_val(g[cnt].fi,v[i])>get_val(g[cnt].fi,v[i+1])){
			ans[g[cnt].se]=get_val(g[cnt].fi,v[i]);
			cnt++;
		}
	}
	while(cnt<m){
		ans[g[cnt].se]=get_val(g[cnt].fi,v[(ll)v.size()-1]);
		cnt++;
	}
}
int main(){
	n=read();m=read();
	F(i,1,n) a[i]=read();
	F(i,1,m) b[i]=read();
	F(i,1,n) v.push_back(a[i]);
	sort(v.begin(),v.end());
	F(i,0,n-1) f[i+1]=(n-i)*v[i];
//	F(i,1,n) cout<<f[i]<<" ";
//	puts("");
	v.clear();
	F(i,1,n){
		while(t>1&&(f[s[t]]-f[s[t-1]])*(i-s[t-1])<(f[i]-f[s[t-1]])*(s[t]-s[t-1])) t--;
		s[++t]=i;
	}
//	UF(i,t,1) cout<<n-s[i]+1<<" ";
//	puts("");
	UF(i,t,1) v.push_back(n-s[i]+1);
	get_ans();
	F(i,1,m) printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

先将 $b_i$ 从小到大排序。

最终定的价格必定刚好能让某人买得起，设这个人为 $i$，价钱定为 $a_i+c$。

收益为 $(a_i+c)\times(n-i+1)$，即 $(n+1)\times c+(-i\times c+(n-i+1)\times a_i)$，看成 $k=-i$ 和 $b=(n-i+1)\times a_i$ 的一次函数，用李超线段树动态开点维护。

（二）

AC 代码。

```cpp
//2025-01-03 20:58:07
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
#define int long long
using namespace std;
bool MBE;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
const int mxn=2e5+10,mx=1e9;
int a[mxn],p,n,m,k[mxn],b[mxn],t[mxn<<2],ls[mxn<<2],rs[mxn<<2],cnt,rt;
int w(int o,int x){
	if(!o)return -1e9;
	return k[o]*x+b[o];
}
void update(int &o,int l,int r,int x){
	if(!o)o=++cnt;
	if(w(x,l)>w(t[o],l)&&w(x,r)>w(t[o],r)){
		t[o]=x;
		return;
	}
	if(w(x,l)<=w(t[o],l)&&w(x,r)<=w(t[o],r)){
		return;
	}
	int mid=(l+r)>>1;
	if(k[t[o]]<k[x]){
		if(w(x,mid)>w(t[o],mid))update(ls[o],l,mid,t[o]),t[o]=x;
		else update(rs[o],mid+1,r,x);
	}
	else{
		if(w(x,mid)>w(t[o],mid))update(rs[o],mid+1,r,t[o]),t[o]=x;
		else update(ls[o],l,mid,x);
	}
}
int query(int o,int l,int r,int x){
	if(!o)return -1e9;
	if(l==r)return w(t[o],x);
	int mid=(l+r)>>1;
	if(x<=mid)return max(w(t[o],x),query(ls[o],l,mid,x));
	else return max(w(t[o],x),query(rs[o],mid+1,r,x));
}
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=read(),m=read();
    for(int i=1;i<=n;i++){
    	a[i]=read();
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
    	b[i]=(n+1-i)*a[i];
    	k[i]=-i;
    	update(rt,0,mx,i);
    }
    for(int i=1;i<=m;i++){
    	p=read();
    	printf("%lld ",query(rt,0,mx,p)+p*n+p);
    }
    bool MED;
    cerr<<(&MED-&MBE)/1048576.0<<" MB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：_xixi (赞：0)

首先可以把 $B_i$ 从大到小排序，再把 $C_i$ 从小到大排序，设 $f_i$ 为第 $i$ 件物品的最大销售额。

显然 $f_i = \max \lbrace(c_i+b_j) \times j \rbrace$，这个可以用 $\Theta(n^2)$ 求出，考虑优化。

$f_i = \max \lbrace (c_i+b_j) \times j \rbrace = \max \lbrace c_i \times j+b_j \times j \rbrace$ 。 $c_i \times j$ 为定值。

设 $w(a,b) = a \times b$。显然 $w(a,b + 1)+w(a+1,b) < w(a,b)+w(a+1,b+1)$，$f_i = c_i \times j+ \max \lbrace w(b_j,j) \rbrace$，有决策单调性。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
using namespace std;

const int maxn = 2e5 + 5;
int n, m, b[maxn], ans[maxn];
struct node{
    int id, x;
}c[maxn];

void solve(int l, int r, int L, int R){
    if(l > r) return;
    int mid = l + r >> 1, x = 0, p = 0;
    for(int i = L; i <= R; i++) if(i * (c[mid].x + b[i]) >= x) p = i, x =  i * (c[mid].x + b[i]);
    ans[c[mid].id] = (c[mid].x + b[p]) * p;
    solve(l, mid - 1, L, p);solve(mid + 1, r, p, R);
}

signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> b[i];
    sort(b + 1, b + n + 1, [](int x, int y){return x > y;});
    for(int i = 1; i <= m; i++) cin >> c[i].x, c[i].id = i;
    sort(c + 1, c + m + 1, [](node x, node y){return x.x < y.x;});
    solve(1, m, 1, n);
    for(int i = 1; i <= m; i++) cout << ans[i] << " ";

    return 0;
}
```

---

