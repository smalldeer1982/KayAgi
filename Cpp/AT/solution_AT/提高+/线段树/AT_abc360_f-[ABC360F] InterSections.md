# [ABC360F] InterSections

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_f

$ 1 $ から $ N $ までの番号のついた $ N $ 個の区間が与えられます。 区間 $ i $ は $ [L_i,R_i] $ です。

区間 $ [l_a,r_a] $ と区間 $ [l_b,r_b] $ は $ (l_a\ <\ l_b\ <\ r_a\ <\ r_b) $ または $ (l_b\ <\ l_a\ <\ r_b\ <\ r_a) $ を満たすとき、**交差する**といいます。

$ f(l,r) $ を $ 1\ \leq\ i\ \leq\ N $ を満たし、区間 $ [l,r] $ と区間 $ i $ が交差する $ i $ の個数と定義します。

$ 0\ \leq\ l\ <\ r\ \leq\ 10^{9} $ を満たす**整数**の組 $ (l,r) $ において、 $ f(l,r) $ の最大値を達成する $ (l,r) $ の組のうち $ l $ が最小のものを答えてください。そのような組が複数存在する場合はさらにそのうちで $ r $ が最小のものを答えてください ($ 0\ \leq\ l\ <\ r $ より、 答えるべき $ (l,r) $ の組は一意に定まります)。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{5} $
- $ 0\ \leq\ L_i\ <\ R_i\ \leq\ 10^{9} $ $ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数である

### Sample Explanation 1

$ f(l,r) $ の最大値は $ 4 $ であり、$ f(l,r)=4 $ となる $ (l,r) $ のうち $ l $ の最小値は $ 4 $ です。 $ f(l,r)=4 $ かつ $ l=4 $ を満たす $ (l,r) $ は以下の $ 5 $ 通りです。 - $ (l,r)=(4,11) $ - $ (l,r)=(4,12) $ - $ (l,r)=(4,13) $ - $ (l,r)=(4,16) $ - $ (l,r)=(4,17) $ このうち、$ r $ の最小値は $ 11 $ であるため、$ 4 $ と $ 11 $ を出力します。

## 样例 #1

### 输入

```
5
1 7
3 9
7 18
10 14
15 20```

### 输出

```
4 11```

## 样例 #2

### 输入

```
11
856977192 996441446
298251737 935869360
396653206 658841528
710569907 929136831
325371222 425309117
379628374 697340458
835681913 939343451
140179224 887672320
375607390 611397526
93530028 581033295
249611310 775998537```

### 输出

```
396653207 887672321```

# 题解

## 作者：FXT1110011010OI (赞：9)

## 分析

考虑与 $[L_i, R_i]$ 相交的 $[l, r]$ 需要满足什么条件：

1. $L_i < l < R_i < r$，可以得出 $L_i + 1 \le l \le R_i - 1, R_i + 1 \le r \le 10 ^ 9$；
2. $l < L_i < r < R_i$，可以得出 $0 \le l \le L_i - 1, L_i + 1 \le r \le R_i - 1$。

建立平面直角坐标系，$x$ 轴表示 $l$，$y$ 轴表示 $r$。可以发现，上面的情况 $1$ 转化为左下角 $(L_i + 1, R_i + 1)$，右上角 $(R_i - 1, 10 ^ 9)$ 的矩形，情况 $2$ 转化为左下角 $(0, L_i + 1)$，右上角 $(L_i - 1, R_i - 1)$ 的矩形。那么问题变为在平面直角坐标系找到一个点，使它被最多的矩形覆盖，扫描线即可。

写代码时要注意一些边界问题。

**upd 2024.07.02**

被 hack 了。hack 数据：

输入

```
3
2 10
8 10
5 8
```

输出

```
0 6
```

错误原因：没有在 $l$ 相同时比较 $r$ 的大小。

代码已修复。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
const LL N = 4e5 + 10, INF = 1e18;

struct node
{
    LL x, y, yy, op;
    
    bool operator < (const node &W) const
    {
        if (x != W.x) return x < W.x;
        return op < W.op;
    }
}seg[N];
LL lsh[N], tott;
struct Node
{
    LL l, r;
    LL mx, mxid, tag;
}tr[N << 2];

LL find(LL x) {return lower_bound(lsh + 1, lsh + 1 + tott, x) - lsh;}

PLL getmax(PLL x, PLL y)
{
    if (x.first > y.first) return x;
    else if (x.first < y.first) return y;
    else
    {
        if (x.second < y.second) return x;
        else return y;
    }
}

void pushup(LL u)
{
    if (tr[u << 1].mx > tr[u << 1 | 1].mx) tr[u].mx = tr[u << 1].mx, tr[u].mxid = tr[u << 1].mxid;
    else if (tr[u << 1].mx < tr[u << 1 | 1].mx) tr[u].mx = tr[u << 1 | 1].mx, tr[u].mxid = tr[u << 1 | 1].mxid;
    else tr[u].mx = tr[u << 1].mx, tr[u].mxid = min(tr[u << 1].mxid, tr[u << 1 | 1].mxid);
}

void pushdown(LL u)
{
    if (tr[u].tag)
    {
        tr[u << 1].mx += tr[u].tag, tr[u << 1].tag += tr[u].tag;
        tr[u << 1 | 1].mx += tr[u].tag, tr[u << 1 | 1].tag += tr[u].tag;
        tr[u].tag = 0;
    }
}

void build(LL u, LL l, LL r)
{
    tr[u] = {l, r, 0, l, 0};
    if (l == r) return;
    LL mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void modify(LL u, LL l, LL r, LL v)
{
    if (l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].mx += v, tr[u].tag += v;
        return;
    }
    pushdown(u);
    LL mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) modify(u << 1, l, r, v);
    if (r > mid) modify(u << 1 | 1, l, r, v);
    pushup(u);
}

PLL query(LL u, LL l, LL r)
{
    if (l <= tr[u].l && r >= tr[u].r) return {tr[u].mx, tr[u].mxid};
    pushdown(u);
    LL mid = tr[u].l + tr[u].r >> 1;
    if (r <= mid) return query(u << 1, l, r);
    else if (mid < l) return query(u << 1 | 1, l, r);
    else
    {
        PLL t1 = query(u << 1, l, r), t2 = query(u << 1 | 1, l, r);
        return getmax(t1, t2);
    }
}

int main()
{
    LL n; scanf("%lld", &n);
    LL tot = 0;
    for (LL i = 1, l, r; i <= n; i ++ )
    {
        scanf("%lld%lld", &l, &r);
        LL x = l + 1, xx = r - 1, y = r + 1, yy = 1e9;
        if (x <= xx && y <= yy)
        {
            seg[ ++ tot] = {x, y, yy + 1, 1};
            seg[ ++ tot] = {xx + 1, y, yy + 1, -1};
            lsh[ ++ tott] = y, lsh[ ++ tott] = yy + 1;
        }
        x = 0, xx = l - 1, y = l + 1, yy = r - 1;
        if (x <= xx && y <= yy)
        {
            seg[ ++ tot] = {x, y, yy + 1, 1};
            seg[ ++ tot] = {xx + 1, y, yy + 1, -1};
            lsh[ ++ tott] = y, lsh[ ++ tott] = yy + 1;
        }
    }
    sort(seg + 1, seg + 1 + tot);
    sort(lsh + 1, lsh + 1 + tott);
    tott = unique(lsh + 1, lsh + 1 + tott) - lsh - 1;
    if (!tott)
    {
        printf("0 1\n");
        return 0;
    }
    build(1, 1, tott);
    PLL res = {-INF, 0}; LL resid = 0;
    for (LL i = 1; i <= tot; i ++ )
    {
        modify(1, find(seg[i].y), find(seg[i].yy) - 1, seg[i].op);
        PLL now = query(1, 1, tott);
        if (now.first > res.first) res = now, resid = i;
        else if (now.first == res.first && now.second < res.second && (!resid || seg[resid].x == seg[i].x)) res = now, resid = i;
    }
    printf("%lld %lld\n", seg[resid].x, lsh[res.second]);
    return 0;
}
```

---

## 作者：Engulf (赞：6)

把区间 $[l, r]$ 看作是平面直角坐标系上的点 $(l, r)$。

考虑与区间 $[l_0, r_0]$ 相交的区间 $[l, r]$ 满足的条件，依题意得

$$\left\{\begin{matrix}
0 \le l < l_0 \\
l_0 < r < r_0
\end{matrix}\right.$$

或

$$\left\{\begin{matrix}
l_0 < l < r_0 \\
r_0 < r \le 10^9
\end{matrix}\right.$$

可以看作是平面直角坐标系上的两个矩形：
- 以 $(0, l_0 + 1)$ 为左下角，$(l_0 - 1, r_0 - 1)$ 为右上角的矩形。
- 以 $(l_0 + 1, r_0 + 1)$ 为左下角，$(r_0 - 1, 10^9)$ 为右上角的矩形。

在矩形内的点所代表的区间和区间 $[l_0, r_0]$ 相交。

为了找到与区间相交最多的区间，其实就等价于在这个平面直角坐标系上找到被最多矩形覆盖的点。

如果被等量矩形覆盖，取最左下的。

而这个是经典问题，扫描线维护。

这题细节较多，给几个提醒。
- 需离散化。
- 数组空间要开够。
- $l$ 相同时，$r$ 记得取 $\min$。
- **排序的时候，假设按照 $l$ 排序，若相同，要先排 $+1$ 再 $-1$。这样把所有的 $+1$ 全部扔到线段树里面后，此时这个位置有的矩形都统计上了，然后再把在这里结束的矩形去掉（也就是 $-1$），才能保证答案正确。即使这里是一个矩形的结束，仍然有覆盖。

$O(n\log n)$。

代码写起来还是比较优美的。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e5 + 5, MAX = 1e9;

int n;

struct Segment {
    int l, r1, r2, v;
} seg[N << 4];

int add[N << 4];
int mx[N << 4], mxid[N << 4];

void pushup(int p) {
    if (mx[p << 1] >= mx[p << 1 | 1]) {
        mx[p] = mx[p << 1];
        mxid[p] = mxid[p << 1];
    } else {
        mx[p] = mx[p << 1 | 1];
        mxid[p] = mxid[p << 1 | 1];
    }
}

void pushdown(int p) {
    if (!add[p]) return;
    add[p << 1] += add[p], add[p << 1 | 1] += add[p];
    mx[p << 1] += add[p], mx[p << 1 | 1] += add[p];
    add[p] = 0;
}

void build(int p, int l, int r) {
    if (l == r) {mxid[p] = l; return;}
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void update(int p, int l, int r, int L, int R, int v) {
    if (L > R) return;
    if (L <= l && r <= R) {
        mx[p] += v;
        add[p] += v;
        return;
    }
    pushdown(p);
    int mid = l + r >> 1;
    if (L <= mid) update(p << 1, l, mid, L, R, v);
    if (mid < R) update(p << 1 | 1, mid + 1, r, L, R, v);
    pushup(p);
}

vector<int> lsh;
int getrk(int x) {return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 1, l, r, j = 0; i <= n; i++) {
        cin >> l >> r;
        lsh.emplace_back(l + 1);
        lsh.emplace_back(r - 1);
        lsh.emplace_back(r + 1);
        lsh.emplace_back(MAX);
        seg[++j] = {0, l + 1, r - 1, 1};
        seg[++j] = {l - 1, l + 1, r - 1, -1};
        seg[++j] = {l + 1, r + 1, MAX, 1};
        seg[++j] = {r - 1, r + 1, MAX, -1};
    }

    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());

    build(1, 0, lsh.size() - 1);

    sort(seg + 1, seg + 1 + 4 * n, [](const Segment &a, const Segment &b) {return a.l != b.l ? a.l < b.l : a.v > b.v;});

    int ansl = 0, ansr = 1, ans = 0;
    for (int i = 1; i <= 4 * n; i++) {
        update(1, 0, lsh.size() - 1, getrk(seg[i].r1), getrk(seg[i].r2), seg[i].v);
        if (mx[1] > ans) {
            ans = mx[1];
            ansl = seg[i].l, ansr = lsh[mxid[1]];
        } else if (mx[1] == ans && seg[i].l == ansl)
            ansr = max(1, min(ansr, lsh[mxid[1]]));
    }

    cout << ansl << " " << ansr << "\n";

    return 0;
}
```

---

## 作者：Supor__Shoep (赞：4)

~~被各种细节强力压制了 1h 的没有赛时做出来的我表示这道题除了一些细节一无是处。。~~

我先说一下我的思路，最后再放一下我这个做法可能会有的细节问题。

首先肯定需要离散化，考虑到最后答案的可能的取值，我们把 $L_i,R_i$ 本身以及它们 $±1$ 的值一并离散化。

离散化之后，设值域为 $[1,len]$，考虑枚举左端点 $l$，我们让 $r$ 从 $l+1$ 到 $len$ 依次枚举。按照题目中区间相交的定义，我们发现对于 $L_i<l$ 的 $R_i$，如果此时 $r>R_i$ 就会产生一次代价。对于 $L_i>l$ 的 $L_i$，如果此时 $r>L_i$ 就会产生一次代价，**但是如果 $r$ 枚举到了 $R_i$，这个代价就会减掉**。于是就会有一个显然的思路：

我们定义 $a_i$ 表示对于当前情况下的 $l$ 值，当 $r=i$ 时可以拥有的相交区间个数。若 $L_i>l$，则 $r\in (L_i,R_i)$ 就能产生一个代价，即这个区间段的 $a$ 要加一。若 $L_i<l$，则 $r>R_i$ 就能产生代价，即 $[R_i+1,len]$ 的 $a$ 要加一。这里可以想到用线段树维护 $a$。

为了优化时间复杂度，我们一开始就把 $(L_i,R_i)$ 的区间全部进行修改，接着从小到大枚举 $l$，对于 $L_i=l$ 的所有 $i$，我们将 $(L_i,R_i)$ 的 $a$ 减一表示删除这一段的代价。对于 $L_i=l-1$ 的所有 $i$，我们修改 $[R_i+1,len]$ 的区间。要找到这些 $i$，我们只需要使用 $len$ 个 vector 去储存就可以了。

特别要注意的是，如果出现 $R_i=l$ 的 $i$，一定要及时清理掉它对 $[R_i+1,len]$ 的贡献，这个可能容易忘记。

此时我们就可以得到以 $l$ 为左端点的所有区间的最大代价，即 $M=\max_{i\in[l+1,len]}\{a_i\}$，区间查询即可。

但是题目要我们求出这对 $(l,r)$。由于 $l$ 是枚举的，我们很容易得到，至于 $r$，我们考虑线段树分治，找到第一个 $a_i=M$ 的 $i$ 即可。

细节时间！！!下面是一些赛时赛后注意到的细节：

- 离散化时要注意 $±1$ 后的值必须在 $[0,10^9]$ 范围内。

- 离散化时不管有没有 $0$，必须放一个 $0$ 进去！

- 如果全局最大值初始化为 $0$，那么代表输出答案的全局变量 $l,r$，初始化必须是 $(0,1)$，因为有可能最大相交个数就是 $0$！！

- 注意数组要开多大。

代码太丑就不放了，而且大致思路就差不多是这样的，应该也不太需要代码吧。。

---

## 作者：imzfx_Square (赞：3)

### 思路:
将区间 $[l,r]$ 对应到以 $l$ 为 $x$ 轴，以 $r$ 为 $y$ 轴的平面直角坐标系的点 $(l,r)$ 上，考虑与 $[l,r]$ 相交的区间 $[L,R]$ 应满足的条件：

1. $L<l<R<r$，即 $0 \le L \le l-1$ 且 $l+1 \le R \le r-1$。

2. $l<L<r<R$，即 $l+1 \le L \le r-1$ 且 $r+1 \le R \le 10^9$。

条件 $1$ 可转化成坐标系上以 $(0,l+1)$ 为左下角，$(l-1,r-1)$ 为右上角的一个矩形。

条件 $2$ 可转化成坐标系上以 $(l+1,r+1)$ 为左下角，$(r-1,10^9)$ 为右上角的一个矩形。

于是问题就转化成了：给定若干个矩形，求一个被最多矩形包含的点，有多解输出 $x$ 最小的，若仍有多解输出 $y$ 最小的。

考虑扫描线，由 $x$ 从小到大扫保证 $x$ 最小，线段树维护区间最大值并记录区间中出现最大值的最靠左的位置 $id$，查询时更新被覆盖的最大值 $Max$ 与对应点 $(ansl,ansr)$，$Max$ 未被更新且 $ansl$ 与扫描线的 $x$ 相同时用 $id$ 更新 $ansr$ 即可。

注意离散化，还有题目要求的 $ansl<ansr$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define L (x<<1)
#define R (x<<1|1)
using namespace std;
const int N=1e5+5,MAX=1e9;
struct Stree{
	int l,r;
	int cnt,id,tag;
	int Max;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define cnt(x) tree[x].cnt
	#define id(x) tree[x].id
	#define Max(x) tree[x].Max
	#define tag(x) tree[x].tag
}tree[N<<4];
struct line{
	int l,r,x,w;
	bool operator <(const line &ln)const{
		if(x!=ln.x)return x<ln.x;
		return w>ln.w;
	}
}a[N<<2];
int n,cnt,len;
int A[N<<2];
int Max;
int ansl,ansr=1;//ansl<ansr
int Q(int x){return lower_bound(A+1,A+1+len,x)-A;}
void up(int x){
	if(Max(L)>=Max(R)){
		Max(x)=Max(L);
		id(x)=id(L);
	}else{
		Max(x)=Max(R);
		id(x)=id(R);
	}
}
void spread(int x){
	Max(L)+=tag(x);
	Max(R)+=tag(x);
	tag(L)+=tag(x);
	tag(R)+=tag(x);
	tag(x)=0; 
}
void build(int x=1,int l=1,int r=len){
	l(x)=l;
	r(x)=r;
	if(l==r){
		id(x)=l;
		return;
	}
	int mid=l+r>>1;
	build(L,l,mid);
	build(R,mid+1,r);
	up(x);
}
void update(int x,int l,int r,int k){
	if(l<=l(x)&&r(x)<=r){
		Max(x)+=k;
		tag(x)+=k;
		return;
	}
	spread(x);
	int mid=l(x)+r(x)>>1; 
	if(l<=mid)update(L,l,r,k);
	if(r>mid)update(R,l,r,k);
	up(x);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		//L<l<R<r
		//0<=L<=l-1,l+1<=R<=r-1
		if(0<=l-1&&l+1<=r-1){
			a[++cnt]=(line){l+1,r-1,0,1};
			a[++cnt]=(line){l+1,r-1,l-1,-1};
			A[++len]=l+1;
			A[++len]=r-1;
		}
		//l<L<r<R
		//l+1<=L<=r-1,r+1<=R<=10^9
		if(l+1<=r-1&&r+1<=MAX){
			a[++cnt]=(line){r+1,MAX,l+1,1};
			a[++cnt]=(line){r+1,MAX,r-1,-1};
			A[++len]=r+1;
			A[++len]=MAX;
		}
	}
	if(!len){
		cout<<"0 1";
		return 0; 
	}
	sort(a+1,a+1+cnt);
	sort(A+1,A+1+len);
	len=unique(A+1,A+1+len)-A-1;
	build();
	for(int i=1;i<=cnt;i++){
		update(1,Q(a[i].l),Q(a[i].r),a[i].w);
		if(Max(1)>Max){
			Max=Max(1);
			ansl=a[i].x;
			ansr=A[id(1)];
		}else if(Max(1)==Max&&a[i].x==ansl)//Max 未被更新且扫描线的 x 与 ansl 相等取较小的 ansr
			ansr=max(1,min(ansr,A[id(1)]));//与 1 取 max 是为了保证 ansl<ansr
	}
	cout<<ansl<<' '<<ansr;
	return 0;
}
```

---

## 作者：Starrykiller (赞：3)

将区间 $[l,r]$ 视为二维平面上的点 $(l,r)$，则区间 $[l,r]$ 会对两个矩形产生贡献：

- $L\lt l\lt R\lt r$：$\{(x,y) :x\in [0,l)\land y\in (l,r)\}$；
- $l\lt L\lt r\lt R$：$\{(x,y) :x\in (l,r)\land y\in (r,10^9]\}$。

套路地扫描线后用线段树维护即可。时间复杂度 $\Theta(N\log N)$。

[代码](https://atcoder.jp/contests/abc360/submissions/56115428)。赞美 ACL。

启示：区间与二维平面上点的互化：$[l,r]\iff (l,r)$。然后刻画区间的贡献（这通常是若干个矩形），利用数据结构维护。

---

## 作者：endswitch (赞：2)

首先考虑给定的区间 $[l_i, r_i]$ 和 一个暂定区间 $[x, y]$ 何时相交。

根据题意，有：

$$
l_i < x < r_i < y
$$

则：

$$
l_i + 1 \le x \le r_i - 1\\
r_i + 1 \le y \le V
$$

其中 $V$ 为 值域。

那么同理，可得另一种情况：

$$
x < l_i < y < r_i\\
0 \le x \le l_i - 1\\
l_i + 1 \le y \le r_i - 1
$$

将区间 $[x,y]$ 映射到平面的点 $(x, y)$ 上，发现上述相交的性质可以转为对点 $(x, y)$ 的横纵坐标的上下界约束。

把这种上下界约束抽象成矩形，题目便转化为找到被最多矩形覆盖的横纵坐标最小的点。

这是扫描线经典 trick，线段树维护即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int n, cnt, tot, num[N << 2];
struct Node {
	int x, y1, y2, val;
	Node(int xx = 0, int yy1 = 0, int yy2 = 0, int vval = 0) {
		x = xx, y1 = yy1, y2 = yy2, val = vval;
	}
} a[N << 2];
map<int, int> lsh;

namespace SGT {
	#define mid (L + R) >> 1
	#define son p, L, R
	#define lson ls(p), L, (L + R) >> 1
	#define rson rs(p), ((L + R) >> 1) + 1, R
	
	struct sgt {
		int mx, id, pls;
	} t[N << 4];
	
	inline int ls(int p) {
		return p << 1;
	}
	
	inline int rs(int p) {
		return p << 1 | 1;
	}
	
	inline void psup(int p) {
		if(t[ls(p)].mx >= t[rs(p)].mx) {
			t[p].mx = t[ls(p)].mx;
			
			t[p].id = t[ls(p)].id;
		}
		else {
			t[p].mx = t[rs(p)].mx;
			
			t[p].id = t[rs(p)].id;
		}
		
		return ;
	} // 容易写挂 
	
	inline void build(int p = 1, int L = 1, int R = tot)  {
		if(L == R) {
			t[p].id = L;
			
			return ;
		}
		
		build(lson), build(rson), psup(p); 
	}
	
	inline void work(int p, int L, int R, int k) {
		t[p].mx += k;
		t[p].pls += k;
		
		return ;
	}
	
	inline void psd(int p, int L, int R) {
		if(! t[p].pls) return ;
		
		work(lson, t[p].pls), work(rson, t[p].pls);
		
		t[p].pls = 0;
		
		return ;
	}
	
	inline void add(int l, int r, int k, int p = 1, int L = 1, int R = tot) {
		if(l <= L && R <= r) {
			work(son, k);
			
			return ;
		}
		
		psd(son);
		
		if(l <= mid) add(l, r, k, lson);
		if(r > mid) add(l, r, k, rson);
		
		psup(p);
		
		return ;
	}
	
	#undef mid
	#undef son
	#undef lson
	#undef rson 
}

using namespace SGT;

inline bool cmp(Node a, Node b) {
	if(a.x == b.x) return a.val > b.val;
	
	return a.x < b.x;
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n;
	
	num[++ tot] = 1e9;
	
	for(int i = 1 ; i <= n ; ++ i) {
		int l, r;
		
		cin >> l >> r;
		
		num[++ tot] = l + 1, num[++ tot] = r - 1, num[++ tot] = r + 1;
		
		a[++ cnt] = Node(0, l + 1, r - 1, 1);
		a[++ cnt] = Node(l - 1, l + 1, r - 1, -1);
		a[++ cnt] = Node(l + 1, r + 1, 1e9, 1);
		a[++ cnt] = Node(r - 1, r + 1, 1e9, -1);
	}
	
	sort(num + 1, num + 1 + tot);
	tot = unique(num + 1, num + 1 + tot) - num - 1;
	
	for(int i = 1 ; i <= tot ; ++ i)
		lsh[num[i]] = i;
	
	sort(a + 1, a + 1 + cnt, cmp);
	
	build();
	
	int ans = 0, posl = 0, posr = 1;
	
	for(int i = 1 ; i <= cnt ; ++ i) {
		add(lsh[a[i].y1], lsh[a[i].y2], a[i].val);
		
		if(t[1].mx > ans) {
			posl = a[i].x, posr = num[t[1].id];
			
			ans = t[1].mx;
		}
		else if(t[1].mx == ans && posl == a[i].x)
			posr = max(1ll, min(posr, num[t[1].id]));
	}
	
	cout << posl << ' ' << posr;
	
	return 0;
}
```

---

## 作者：vicissitudes (赞：2)

我们将区间的左右端点对应到平面的坐标，发现能够与这个区间相交的区间其实就是两个矩阵 $(x+1,y+1)$ 到 $(y-1,10^9)$ 和 $(0,x+1)$ 到 $(x-1,y-1)$ 的所有点。

那么答案就是覆盖最多矩形的点。扫描线能做。

大部分题解都发现答案区间一定是**给出的区间中左右端点中加减一得到的**（可以不是同一个）。

如果这都没发现咋办 ~~（和我一样）~~。

如果你没有发现这个结论，那么你是没法离散化的，因为你根本不知道答案是否在你离散化后的所有数里。

怎么办呢，那么就写一颗**动态开点线段树**吧。

这么做稍微麻烦点的就是懒标记的下传前要先给左右儿子开点。

最后查询最大值，直接调用 $root$ 的最大值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, inf = 1e9;
struct Seg {
	int x, s, t, v;
	bool operator< (const Seg &b) const {
		if(x == b.x) return v > b.v;
		return x < b.x;
	}
}seg[N * 10];

struct node {
	int l, r;
	int val, id, lz;
}tr[N * 60];
int tot, rt;

void pushup(int u) {
	node l = tr[tr[u].l], r = tr[tr[u].r];
	tr[u].val = max(l.val, r.val);
	if(l.val < r.val) {
		tr[u].id = r.id;
	} else if(l.val > r.val) {
		tr[u].id = l.id;
 	} else {
 		tr[u].id = min(l.id, r.id);
 	}
}

void pushdown(int u) {
	if(!tr[u].lz) return ;
	node &l = tr[tr[u].l], &r = tr[tr[u].r];
	int &lz = tr[u].lz;
	l.val += lz, r.val += lz;
	l.lz += lz, r.lz += lz;
	lz = 0;
}

void add(int &u, int l, int r, int al, int ar, int v) {
	if(!u) u = ++ tot;
	if(l == r) tr[u].id = l;
	if(l >= al && r <= ar) {
		tr[u].lz += v;
		tr[u].val += v;
		if(tr[u].id == -1) tr[u].id = l;
		return ;
	}
	if(tr[u].lz) {
		if(!tr[u].l) tr[u].l = ++ tot, tr[u].id = l;
		if(!tr[u].r) tr[u].r = ++ tot, tr[u].id = r;
		pushdown(u);
	}
	
	int mid = l + r >> 1;
	if(mid >= al) add(tr[u].l, l, mid, al, ar, v);
	if(mid < ar) add(tr[u].r, mid + 1, r, al, ar, v);
	pushup(u);
}

int cnt;
int main() { 
	int n;
	cin >> n;
	for(int i = 1; i < N * 60; i ++) tr[i].id = -1;
	for(int i = 1; i <= n; i ++) {
		int x, y;
		cin >> x >> y;
		if(y + 1 <= inf) seg[++ cnt] = {x + 1, y + 1, inf, 1};
		if(y + 1 <= inf) seg[++ cnt] = {y - 1, y + 1, inf, -1};
		if(x + 1 <= y - 1) seg[++ cnt] = {0, x + 1, y - 1, 1};
		if(x + 1 <= y - 1) seg[++ cnt] = {x - 1, x + 1, y - 1, -1};
	}
	sort(seg + 1, seg + cnt + 1);
	node ans = {0};
	int x;
	for(int i = 1; i <= cnt; i ++) {
		add(rt, 0, inf, seg[i].s, seg[i].t, seg[i].v);
		node res = tr[rt];
		if(ans.val < res.val) {
			ans = res;
			x = seg[i].x;
		} 
	}
	if(!ans.val) cout << "0 1";
	else cout << x << " " << ans.id;
	return 0;
} 
```

---

## 作者：complete_binary_tree (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc360_f)

## 题目大意

给定 $N$ 个区间，第 $i$ 个区间覆盖 $[l_i,r_i]$ 的范围。

定义 $f(l,r)$ 为区间 $[l,r]$ 与这 $N$ 个区间相交的个数。求出最大的 $f(l,r)$ 使得 $l$ 最小。如有多解，输出最小的 $r$。

两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 相交指 $l_1 < l_2 < r_1 < r_2$ 或者 $l_2 < l_1 < r_2 < r_1$，也就是说包含或者只有端点重合都是不行的。

## 题解

考虑容斥。

首先我们可以求一个数组 $f$，$f(i)$ 代表第 $i$ 个点被几个区间 **完全覆盖**（不包括端点，因为端点重合不算）。

此时如果我们知道 $l$ 和 $r$，那么答案就是 $f(l) + f(r) - $ 完全覆盖 $[l,r]$ 的区间的个数。考虑如何维护后面这个区间个数。

首先我们把 $f$ 复制一份丢到线段树上，这样我们只要枚举 $l$ 然后就能在线段树上查询最大值和 $r$ 了。

然后我们考虑在线段树上减去贡献。

对于一个区间 $[l,r]$，当我们枚举的左端点（假设为 $i$）刚刚进入这个区间（$i=l$ 的时候），此时 $f(i)$ 没有受到影响（因为这段区间影响的是 $f[l+1,r-1]$），但是此时右端点选择 $(l,r)$ 已经不能受到这个区间的贡献了，所以线段树上 $(l,r)$ 区间 $-1$。

然后，枚举的 $i$ 又往右移一位（$l=i+1$ 的时候），此时 $f(i)$ 已经受到影响，也就是说当右端点选择在 $[i+1,r]$ 的时候，$f(i)$ 会多算 $1$ 的贡献，这时候我们要容斥掉，也就是在线段树上 $[i+1,r]$ 区间 $-1$。

时间复杂度 $O(n \log n)$。

还有一些细节：

- 离散化一定要加入 $0$！

- 答案是 $0$ 的话输出 `0 1`。

- 小心边界条件，`1000000001` 是不能作为答案的！

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

int l[N], r[N], tmp[N * 6], n, f[N * 6], ans = 0, ansl, ansr = 1, ___r[N * 6];
vector <int> l_r[N * 6];

struct tree { int l, r, mx, lz, pos; };
struct st {
#define ls ( x << 1 )
#define rs ( x << 1 | 1 )
	tree t[N * 24];
	void build ( int x, int l, int r ) {
		t[x].l = l, t[x].r = r;
		if ( l == r ) {
			t[x].pos = l;
			return ;
		}
		int mid = ( l + r ) >> 1;
		build ( ls, l, mid ), build ( rs, mid + 1, r );
		t[x].mx = max ( t[ls].mx, t[rs].mx );
		if ( t[rs].mx > t[ls].mx ) t[x].pos = t[rs].pos;
		else t[x].pos = t[ls].pos;
	}
	void pushdown ( int x ) {
		int lz = t[x].lz; t[x].lz = 0;
		t[ls].lz += lz, t[ls].mx += lz;
		t[rs].lz += lz, t[rs].mx += lz; 
	}
	void add ( int x, int l, int r, int y ) {
		if ( t[x].l > r || t[x].r < l ) return ;
		if ( t[x].l >= l && t[x].r <= r ) {
			t[x].mx += y, t[x].lz += y;
			return ;
		}
		pushdown ( x );
		add ( ls, l, r, y ), add ( rs, l, r, y );
		t[x].mx = max ( t[ls].mx, t[rs].mx );
		if ( t[rs].mx > t[ls].mx ) t[x].pos = t[rs].pos;
		else t[x].pos = t[ls].pos;
	}
	int query ( int x, int l, int r, int& _r ) {
		if ( t[x].l > r || t[x].r < l ) { _r = 1e9 + 7; return -1e9; }
		if ( t[x].l >= l && t[x].r <= r ) { _r = t[x].pos; return t[x].mx; }
		pushdown ( x );
		int lr, rr;
		int retl = query ( ls, l, r, lr ), retr = query ( rs, l, r, rr );
		if ( retr > retl ) _r = rr;
		else _r = lr;
		return max ( retl, retr );
	} 
} t1;

int cnt;

signed main () {
	ios::sync_with_stdio ( 0 ), cin.tie ( 0 ), cout.tie ( 0 );
	cin >> n;
	for ( int i = 1; i <= n; ++i ) cin >> l[i] >> r[i], tmp[++cnt] = l[i], tmp[++cnt] = r[i], tmp[++cnt] = l[i] + 1, tmp[++cnt] = ( l[i] == 0 ? 0 : l[i] - 1 ), tmp[++cnt] = r[i] - 1, tmp[++cnt] = ( r[i] == 1000000000 ? 1000000000 : r[i] + 1 );
	tmp[++cnt] = 0;
	sort ( tmp + 1, tmp + cnt + 1 );
	int len = unique ( tmp + 1, tmp + cnt + 1 ) - tmp - 1;
	for ( int i = 1; i <= n; ++i ) l[i] = lower_bound ( tmp + 1, tmp + len + 1, l[i] ) - tmp, r[i] = lower_bound ( tmp + 1, tmp + len + 1, r[i] ) - tmp, f[l[i] + 1] ++, f[r[i]] --, l_r[l[i]].push_back ( r[i] );
	for ( int i = 1; i <= len; ++i ) f[i] += f[i - 1];
	t1.build ( 1, 1, len );
	for ( int i = 1; i <= n; ++i ) t1.add ( 1, l[i] + 1, r[i] - 1, 1 ); 
	for ( int i = 1; i < len; ++i ) {
		for ( auto j : l_r[i] ) t1.add ( 1, i + 1, j, -1 );
		for ( auto j : l_r[i - 1] ) t1.add ( 1, i, j - 1, -1 );
		int __r;
		int _ans = f[i] + t1.query ( 1, i + 1, len, __r );
		if ( _ans > ans ) ans = _ans, ansl = tmp[i], ansr = tmp[__r];
	cout << ansl << " " << ansr << endl;
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

考虑转化为二维的平面直角坐标系，将 $(L,R)$ 看作我们的目标点。

第一种有贡献的情况：

$$l_i + 1 \le L \le r_i-1,r_i+1 \le R \le +\infty$$

此时矩形左下角为 $(l_i+1,r_i+1)$，右上角为 $(r_i-1,+\infty)$。

第二种有贡献的情况：

$$0 \le L \le l_i-1,l_i+1 \le R+1 \le r_i - 1$$

此时矩形左下角为 $(0,l_i+1)$，右上角为 $(l_i - 1,r_i - 1)$。

这样我们得到了 $2 \times n$ 个矩形，我们需要找到一个点 $(L,R)$，使得被尽可能多的矩形覆盖，于是直接扫描线即可，需要注意细节。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=2e6+10,INF=1e9;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll l,r;
	ll Max;
	ll tag;
	ll id;
}X[N<<2];
ll n,l,r,cnt,l1,l2,L,R,Max;
ll a[N],b[N],c[N],d[N],h1[N],h2[N];
vector<pair<pair<ll,ll>,ll>> E[N];
void init(){
	h1[++l1]=a[cnt];
	h1[++l1]=c[cnt];
	h1[++l1]=a[cnt]+1;
	if(a[cnt]-1>=0)
	  h1[++l1]=a[cnt]-1;
	h1[++l1]=c[cnt]+1;
	if(c[cnt]-1>=0)
	  h1[++l1]=c[cnt]-1;
	h2[++l2]=b[cnt];
	h2[++l2]=d[cnt];
	h2[++l2]=d[cnt]+1;
	if(d[cnt]-1>=0)
	  h2[++l2]=d[cnt]-1;
	h2[++l2]=b[cnt]+1;
	if(b[cnt]-1>=0)
	  h2[++l2]=b[cnt]-1;
}
void pushup(ll k){
	X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
	if(X[k].Max==X[k<<1].Max)
	  X[k].id=X[k<<1].id;
	else
	  X[k].id=X[k<<1|1].id;
}
void add(ll k,ll v){
	X[k].Max+=v;
	X[k].tag+=v;
}
void push_down(ll k){
	if(X[k].tag){
		add(k<<1,X[k].tag);
		add(k<<1|1,X[k].tag);
		X[k].tag=0;
	}
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r){
		X[k].Max=0;
		X[k].id=l;
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void update(ll k,ll l,ll r,ll v){
	if(l>r)
	  return ;
	if(X[k].l==l&&r==X[k].r){
		add(k,v);
		return ;
	}
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  update(k<<1,l,r,v);
	else if(l>mid)
	  update(k<<1|1,l,r,v);
	else{
		update(k<<1,l,mid,v);
		update(k<<1|1,mid+1,r,v);
	}
	pushup(k);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		l=read(),r=read();
		if(r-l>=2){
			++cnt;
			a[cnt]=l+1,b[cnt]=r+1;
			c[cnt]=r-1,d[cnt]=INF;
			init();
		}
		if(l>0){
			++cnt;
			a[cnt]=0,b[cnt]=l+1;
			c[cnt]=l-1,d[cnt]=r-1;
			init();
		}
	}
	sort(h1+1,h1+l1+1);
	sort(h2+1,h2+l2+1);
	l1=unique(h1+1,h1+l1+1)-(h1+1);
	l2=unique(h2+1,h2+l2+1)-(h2+1);
	while(h1[l1]>1e9)
	  l1--;
	while(h2[l2]>1e9)
	  l2--;
	if(!l1||!l2){
		puts("0 1");
		exit(0);
	}
	for(int i=1;i<=cnt;i++){
		a[i]=lower_bound(h1+1,h1+l1+1,a[i])-h1;
		c[i]=lower_bound(h1+1,h1+l1+1,c[i])-h1;
		b[i]=lower_bound(h2+1,h2+l2+1,b[i])-h2;
		d[i]=lower_bound(h2+1,h2+l2+1,d[i])-h2;
		E[a[i]].push_back({{b[i],d[i]},1});
		E[c[i]+1].push_back({{b[i],d[i]},-1});
	}
	build(1,1,l2);
	for(int i=1;i<=l1;i++){
		for(auto t:E[i])
		  update(1,t.first.first,t.first.second,t.second);
		if(Max<X[1].Max){
			Max=X[1].Max;
			L=h1[i],R=h2[X[1].id];
		}
	}
	if(!Max){
		puts("0 1");
		exit(0);		
	}
	write(L);
	putchar(' ');
	write(R);
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

有一定细节的题目，赛时没调出来，看来要加强训练。

首先考虑有意义的左端点只能是 $0$ 与给定区间左右端点加减 $1$，原因是不是这些点可以向前调整，那么此时已经确定了 $O(n)$ 个可能的 $l$。

考虑将所有 $l$ 排序后做扫描线，具体而言从小往大扫描所有 $l$，对于大于 $l$ 的 $L_i$ 满足条件的 $r$ 在 $[L_i+1,R_i-1]$ 这个区间内，于是用线段树维护这些区间加，对于小于 $l$ 的 $L_i$ 满足条件的 $r$ 在 $[R_i+1,10^9]$ 这个区间内也用线段树维护区间加，然后注意将 $R_i \leq l$ 区间区间贡献删去，由于是从小往大枚举，每个区间会先从贡献 $[L_i+1,R_i-1]$ 转变为贡献 $[R_i+1,10^9]$ 再转变为不贡献，对坐标离散化后找到当前枚举的 $l$ 是哪些区间的 $L_i$ 与 $R_i$ 即可完成对区间贡献转变的维护。

注意到查询的是第一个 $\max$ 的位置，于是线段树维护区间加区间 $\max$，查询时在线段树上二分即可。

时间复杂度 $O(n \log n)$。注意一些边界情况，不要超出 $[0,10^9]$ 这个边界。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int tr[maxn*120],tag[maxn*120];
int ls[maxn*120],rs[maxn*120],rt,tot;
int cnt;
int L[maxn],R[maxn],n;
const int top = 1e9;
void pushup(int cur){
    tr[cur]=max(tr[ls[cur]],tr[rs[cur]]);
}
void pushdown(int cur){
    if(ls[cur]==0) ls[cur]=++tot;
    tr[ls[cur]]+=tag[cur];
    tag[ls[cur]]+=tag[cur];
    if(rs[cur]==0) rs[cur]=++tot;
    tr[rs[cur]]+=tag[cur];
    tag[rs[cur]]+=tag[cur];
    tag[cur]=0;
}
void add(int cur,int lt,int rt,int l,int r,int c){
    if(l>r) return ;
    if(r<lt||rt<l) return ;
    if(l<=lt&&rt<=r){
        tag[cur]+=c;
        tr[cur]+=c;
        return ;
    }
    pushdown(cur);
    int mid=(lt+rt)>>1;
    add(ls[cur],lt,mid,l,r,c);
    add(rs[cur],mid+1,rt,l,r,c);
    pushup(cur);
}
pair<int,int> ask(int cur,int lt,int rt){
    if(lt==rt){
        return make_pair(tr[cur],lt);
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    if(tr[ls[cur]]>=tr[rs[cur]]) return ask(ls[cur],lt,mid);
    else return ask(rs[cur],mid+1,rt);
}
vector<int> Lt[maxn<<1],Rt[maxn<<1];
unordered_map<int,int> lsh;
vector<int> pos;
int maxans,minl,minr;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    minr=top;
    rt=++tot;
    cin>>n;
    lsh[0]=++cnt;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        if(L[i]-1>=0) pos.push_back(L[i]-1);
        pos.push_back(L[i]+1);
        pos.push_back(L[i]);
        pos.push_back(R[i]);
        pos.push_back(R[i]-1);
        if(R[i]+1<=top) pos.push_back(R[i]+1);
        if(lsh[L[i]]==0) lsh[L[i]]=++cnt;
        if(lsh[R[i]]==0) lsh[R[i]]=++cnt;
        Lt[lsh[L[i]]].push_back(i);
        Rt[lsh[R[i]]].push_back(i);
    }
    pos.push_back(0);
    set<int> s(pos.begin(),pos.end());
    pos.assign(s.begin(),s.end());
    for(int i=1;i<=n;i++){
        add(rt,0,top,L[i]+1,R[i]-1,1);
    }
    minr=1;
    for(int x:pos){
        for(int y:Lt[lsh[x]]){
            add(rt,0,top,L[y]+1,R[y]-1,-1);
        }
        for(int y:Rt[lsh[x]]){
            add(rt,0,top,R[y]+1,top,-1);
        }
        pair<int,int> ans=ask(rt,0,top);
        if(ans.first>maxans) maxans=ans.first,minl=x,minr=ans.second;
        for(int y:Lt[lsh[x]]){
            add(rt,0,top,R[y]+1,top,1);
        }
    }
    cout<<minl<<' '<<minr<<'\n';
    return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

唐氏题，今天看了一下题目一眼秒出来了，但是赛时没开这题/ll。

___

# Solution

考虑把一个区间 $[l,r]$ 转化为矩阵上的一个点 $(l,r)$。

对于输入的一条区间 $[l,r]$，可以转化为分别在横坐标区间为 $[0,l-1]$，纵坐标区间为 $[l+1,r-1]$ 的矩阵和横坐标区间为 $[l+1,r-1]$，纵坐标区间为 $[r+1,10^9]$ 的矩阵上加一。

扫描线即可，时间复杂度 $O(n\log n)$。

注意题目要求输出的 $l<r$，也就是说最大相交个数为 $0$ 时要输出 `0 1` 而不是 `0 0`。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
using namespace atcoder;
const int N=2e6,V=1e9;
int n,ans,T[N],tag[N];
vector<int> num;

struct line
{
	int x,l,r,w;
	bool operator <(line o)const {
		return x^o.x?x<o.x:w<o.w;
	}
};
vector<line> a;

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
void pushdown(int rt) {
	T[rt<<1]+=tag[rt],tag[rt<<1]+=tag[rt];
	T[rt<<1|1]+=tag[rt],tag[rt<<1|1]+=tag[rt];
	tag[rt]=0;
}
void change(int rt,int l,int r,int s,int t,int x) {
	if (s<=l&&r<=t) return T[rt]+=x,tag[rt]+=x,void();
	pushdown(rt); if (s<=mid) change(rt<<1,l,mid,s,t,x);
	if (mid<t) change(rt<<1|1,mid+1,r,s,t,x);
	T[rt]=max(T[rt<<1],T[rt<<1|1]);
}
int query(int rt,int l,int r) {
	if (l==r) return l; pushdown(rt);
	if (T[rt<<1]==T[rt]) return query(rt<<1,l,mid);
	else return query(rt<<1|1,mid+1,r);
}
main()
{
	n=read(),num.push_back(V);
	while (n--) {
		int l=read(),r=read();
		a.push_back({0,l+1,r-1,1});
		a.push_back({l,l+1,r-1,-1});
		a.push_back({l+1,r+1,V,1});
		a.push_back({r,r+1,V,-1});
		num.push_back(l+1),num.push_back(r-1);
		num.push_back(r+1);
	}
	sort(a.begin(),a.end() );
	sort(num.begin(),num.end() );
	num.erase(unique(num.begin(),num.end() ),num.end() );
	for (line &o:a) {
		o.l=lower_bound(num.begin(),num.end(),o.l)-num.begin()+1;
		o.r=lower_bound(num.begin(),num.end(),o.r)-num.begin()+1;
	}
	int ansl=0,ansr=1;
	for (int i=0,j=0;i<a.size();i=j) {
		while (j<a.size()&&a[i].x==a[j].x) change(1,1,num.size(),a[j].l,a[j].r,a[j].w),j++;
		if (T[1]>ans) ans=T[1],ansl=a[i].x,ansr=num[query(1,1,num.size() )-1];
	}
	printf("%lld %lld",ansl,ansr);
	return 0;
}
```

---

## 作者：2020kanade (赞：0)

前情提要：脑抽风场上倒开，结束才调完。

题目：ABC360F

首先考虑可能被选择的点，至少每两个区间端点（不论左右）中间如果有合法的空位，至少要塞一个点过去，且这个点为了保证最优性质直接放在左侧端点的右边一个单位。此外，如果没有 $0$，务必塞一个进去，作用显然。注意塞点的时候如果是直接往区间端点右边一个单位塞点，判一下右边界。

把这最多 $3n+2$ 个点离散化去重，之后考虑如何统计某个区间与多少个区间相交。

显然，对于区间 $[l,r]$，我们可以预处理所有区间覆盖的位置（每个区间按覆盖 $[l+1,r-1]$），用覆盖 $l$ 的区间数加上覆盖 $r$ 的区间数，显然会包含一些不合法情况，我的做法比较麻烦，这里细说一下：

显然，不合法区间 $[L,R]$ 满足 $L\le l \lt r \le R$，根据式子前半段，对于固定的左端点 $l$，我们此时要处理所有左端点等于 $l$ 的区间造成的重复情况；对于式子的后半段，我们需要处理的情况比较复杂，下面详细展开：

第一类是右端点 $=r$ 的区间，此时因 $r=R$ 区间 $[L,R]$ 不能在右端点上产生贡献，但其会贡献左端点在 $[L+1,R-1]$ 内的区间一次，需要减去；

第二类是右端点 $\lt r$ 的区间，此时因 $[L,R]$ 在右端点上产生 $1$ 的贡献，条件为 $L\le l$，也需要减去。

不难发现这两类减去的部分有重合，这是正常的，虽然都是两部分都产生贡献，但与容斥原理相比，这一部分是根本不应产生贡献而不是在交集中多贡献一次，都需要减去，减两次就是对的。

考虑如何获得答案：将第一类和第二类贡献消除分别挂到 $l+1$ 和 $l$ 上，然后枚举左端点进行扫描线，用线段树维护一个基于区间 $\min$ 的特殊结合信息，显然其也支持区间加减操作，结合修改进行后缀查询即可。最终将所有左端点得到的答案扔到一起取最优即可。

注意：对于所有区间都是 $[0,10^9]$ 等情况，上述算法无法选择一个相交区间数不为零的区间，此时算法正确性没有保证，具体的表现为答案返回值 $[l,r]$ 中有 $l\ge r$ 或答案的相交数为零，此时手动输出 $[0,1]$ 即可（感谢 [@cwjfighting](https://www.luogu.com.cn/user/138481) 提出 hack）。

时间复杂度 $\Theta(n\log n)$，写的巨唐无比。

RMJ 说可以单调队列线性，回头补一下。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
struct info
{
	ll val;int pos;
	info():val(0),pos(0) {}
	info(int pos):val(0),pos(pos) {}
	info(int pos,ll v):val(v),pos(pos) {}
};
struct tag
{
	ll v;
	tag():v(0) {}
	tag(ll v):v(v) {}
	bool kara() {return v==0;}
};
info operator +(const info& a,const info &b)
{
	if(a.val>b.val) return a;
	else if(a.val<b.val) return b;
	else
	{
		if(a.pos<b.pos) return a;
		else return b;
	}
}
tag operator +(const tag& a,const tag &b)
{
	return tag(a.v+b.v);
}
info operator +(const info& a,const tag &b)
{
	info r=a;r.val+=b.v;
	return r;
}
struct xds
{
	int rt,ct;
	int ls[N*2],rs[N*2];info v[N*2];tag tg[N*2];
	void down(int x)
	{
		if(!tg[x].kara())
		{
			tg[ls[x]]=tg[ls[x]]+tg[x],v[ls[x]]=v[ls[x]]+tg[x];
			tg[rs[x]]=tg[rs[x]]+tg[x],v[rs[x]]=v[rs[x]]+tg[x];
			tg[x]=tag(0ll);
		}
	}
	void up(int x)
	{
		v[x]=v[ls[x]]+v[rs[x]];
	}
	void cst(int &x,int l,int r)
	{
		x=++ct;if(l==r) return v[x]=info(l),void();
		int mid=(l+r)>>1;
		cst(ls[x],l,mid);cst(rs[x],mid+1,r);up(x);
	}
	void change(int x,int l,int r,int ql,int qr,tag _)
	{
		if(ql<=l&&r<=qr)
		{
			v[x]=v[x]+_,tg[x]=tg[x]+_;
			return;
		}
		down(x);int mid=(l+r)>>1;
		if(ql<=mid) change(ls[x],l,mid,ql,qr,_);
		if(mid+1<=qr) change(rs[x],mid+1,r,ql,qr,_);
		up(x);
	}
	info ask(int x,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr) return v[x];
		down(x);int mid=(l+r)>>1;info _=info(ct);
		if(ql<=mid) _=_+ask(ls[x],l,mid,ql,qr);
		if(mid+1<=qr) _=_+ask(rs[x],mid+1,r,ql,qr);
		return _;
	}
};
xds sgt;
map<int,bool> exist;
int poses[N*2],drc[N*2],dl1,dla;map<int,int> _drc,drci;
int _r;vector<int> seq[N];pair<int,int> sqs[N*2];
ll api[N*2];
struct anser
{
	int l,r;ll ans;
	bool operator <(const anser& a) const
	{
		if(ans<a.ans) return 1;
		else if(ans>a.ans) return 0;
		else
		{
			if(l>a.l) return 1;
			else if(l<a.l) return 0;
			else
			{
				return r>a.r;
			} 
		}
	}
};
set<anser> ans;
void solve()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int x,y;cin>>x>>y;
		exist[x]=exist[y]=1;
		poses[++dl1]=x,poses[++dl1]=y;
		sqs[i]={x,y};
	}
	sort(poses+1,poses+dl1+1);dl1=unique(poses+1,poses+dl1+1)-poses-1;
	if(!exist[0]) exist[0]=1,drc[++dla]=0,_drc[0]=dla,drci[dla]=0;
	for(int i=1;i<=dl1;++i)
	{
		drc[++dla]=poses[i],_drc[poses[i]]=dla,drci[dla]=poses[i];
		if(poses[i]+1<=1e9&&(!exist[poses[i]+1]))  drc[++dla]=poses[i]+1,_drc[poses[i]+1]=dla,drci[dla]=poses[i]+1;
	}
	//for(int i=1;i<=dla;++i) cout<<drc[i]<<' ';cout<<endl; 
	/*for(int i=1;i<=n;++i)
	{
		int x=sqs[i].first,y=sqs[i].second;
		x=_drc[x],y=_drc[y];
		cout<<x<<' '<<y<<endl;
	}*/
	sgt.cst(sgt.rt,1,dla);
	for(int i=1;i<=n;++i)
	{
		int x=sqs[i].first,y=sqs[i].second;
		x=_drc[x],y=_drc[y];
		seq[x+1].push_back(y);
		seq[x].push_back(y-1);
		if(x+1<=y-1) sgt.change(1,1,dla,x+1,y-1,tag(1ll));
	}
	for(int i=1;i<=dla;++i)
	{
		info x=sgt.ask(1,1,dla,i,i);
		api[i]=x.val;
		//cout<<i<<' '<<x.pos<<' '<<x.val<<endl;
	}
	for(int i=1;i<dla;++i)
	{
		int pl=drci[i];
		for(auto x:seq[i])
		{
			//cout<<"change:"<<i<<' '<<x<<endl;
			if(i<=x) sgt.change(1,1,dla,i,x,tag(-1ll));
		}
		info xans=sgt.ask(1,1,dla,i+1,dla);
		//cout<<i<<' '<<xans.pos<<' '<<xans.val+api[i]<<endl;
		ans.insert(anser{pl,drci[xans.pos],xans.val+api[i]});
	}
	auto it=ans.end();*--it;
	auto x=*it;
	if(x.l>x.r||x.ans==0) x.l=0,x.r=1;
	cout<<x.l<<' '<<x.r<<endl;
}
int main()
{
 	t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

无脑做法，加个特判就能过了。

考虑对于线段 $i$，你的 $lp,rp$ 什么时候会让 $i$ 有贡献。显然在 $lp<l_i<rp<r_i$ 或者 $l_i<lp<r_i<rp$ 时有 $1$ 的贡献。

将 $l$ 看成横坐标，$r$ 看成纵坐标，我们发现上述两种情况中对应 $(lp,rp)$ 的可行点成为了两个 **不交** 的矩形。

于是无脑套扫描线维护最大覆盖数即可。因为不交所以不用考虑重复给贡献的情况。

寻找端点可以线段树二分找第一个等于某个数的位置。

因为懒写的是动态开点，记得空间开大一点，然后 `pushdown` 的时候没有儿子记得新建子节点。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef long double db;
typedef pair<int,int> pii;
const int N=4e5,Inf=1e9;
const db eps=1e-8,pi=acos(-1.0);

int n,pn=0,al=0,ar=0,ans=0;
int pid=0,rt,sx[N*20+5],ls[N*20+5],rs[N*20+5],tg[N*20+5];
struct Node{
	int px,pl,pr,pf;
	Il bool operator <(const Node &stmp)const{return px<stmp.px;}
}pp[N+5];

Il void pown(int p){
	if(!tg[p])return;
	if(!ls[p])ls[p]=++pid;sx[ls[p]]+=tg[p];tg[ls[p]]+=tg[p];
	if(!rs[p])rs[p]=++pid;sx[rs[p]]+=tg[p];tg[rs[p]]+=tg[p];
	tg[p]=0;
	return;
}

Il void add(int ql,int qr,int l,int r,int &p,int K){
	if(ql>qr)return;
	if(!p)p=++pid;
	if(ql<=l&&r<=qr){sx[p]+=K;tg[p]+=K;return;}
	int mid=(l+r)>>1;pown(p);
	if(ql<=mid)add(ql,qr,l,mid,ls[p],K);
	if(qr>mid)add(ql,qr,mid+1,r,rs[p],K);
	sx[p]=max(sx[ls[p]],sx[rs[p]]);
	return;
}

Il int find(int l,int r,int p){
	if(l==r)return l;
	int mid=(l+r)>>1;pown(p);
	if(sx[ls[p]]==sx[p])return find(l,mid,ls[p]);
	return find(mid+1,r,rs[p]);
}

Il int qps(int ps,int l,int r,int p){
	if(!p||l==r)return sx[p];
	pown(p);int mid=(l+r)>>1;
	if(ps<=mid)return qps(ps,l,mid,ls[p]);
	return qps(ps,mid+1,r,rs[p]);
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(Ri i=1;i<=n;i++){
		int il,ir;cin>>il>>ir;if(ir-il<=1)continue;
		pp[++pn]={il+1,ir+1,Inf,1};
		pp[++pn]={ir,ir+1,Inf,-1};
		pp[++pn]={0,il+1,ir-1,1};
		pp[++pn]={il,il+1,ir-1,-1};
	}
	sort(pp+1,pp+pn+1);
	for(Ri i=1;i<=pn;i++){
		for(Ri j=i;i<=pn&&pp[i].px==pp[j].px;i++)add(pp[i].pl,pp[i].pr,0,Inf,rt,pp[i].pf);
		i--;int mx=sx[rt];if(mx<=ans)continue;
		ans=mx,al=pp[i].px,ar=find(0,Inf,rt);
	}
	cout<<al<<' '<<ar+(al==ar);//感谢讨论区提供特判。
	return 0;
}
```

---

