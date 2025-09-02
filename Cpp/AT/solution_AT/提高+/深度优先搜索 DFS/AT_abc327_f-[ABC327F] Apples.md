# [ABC327F] Apples

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc327/tasks/abc327_f

数直線上にりんごの木が並んでおり、 $ N $ 個のりんごが木から落ちてきます。  
具体的には $ 1\leq\ i\leq\ N $ について、時刻 $ T_i $ に座標 $ X_i $ にりんごが落ちてきます。

高橋君は耐久性が $ D $ , 長さ $ W $ のカゴを持っており、**一度だけ** 次の行動を取ることができます。

> 正整数 $ S $, $ L $ を選ぶ。高橋君は時刻 $ S-0.5 $ に $ L-0.5\leq\ x\leq\ L+W-0.5 $ の範囲を覆うようにカゴを設置し、時刻 $ S+D-0.5 $ に回収する。 高橋君はカゴを設置してから回収するまでの間に、カゴが設置されていた範囲に落ちてきたりんごをすべて得ることができる。

高橋君は一度設置したカゴを動かしたり、回収したカゴを再度設置することはできません。  
高橋君が得られるりんごの数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ D\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ W\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ T_i\leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X_i\leq\ 2\times\ 10^5 $
- $ (T_i,X_i) $ はすべて異なる。
- 入力はすべて整数

### Sample Explanation 1

高橋君は $ S=3 $, $ L=2 $ を選ぶと、時刻 $ 2.5 $ から $ 6.5 $ までカゴを $ 1.5\leq\ x\leq\ 4.5 $ の範囲に設置します。このとき、 - 時刻 $ T_2=3 $ に 座標 $ X_2=4 $ に落ちてくるりんご - 時刻 $ T_3=6 $ に 座標 $ X_3=4 $ に落ちてくるりんご - 時刻 $ T_4=5 $ に 座標 $ X_4=2 $ に落ちてくるりんご - 時刻 $ T_5=4 $ に 座標 $ X_5=2 $ に落ちてくるりんご - 時刻 $ T_6=4 $ に 座標 $ X_6=3 $ に落ちてくるりんご の $ 5 $ 個のりんごを得ることができます。 どのように行動しても $ 6 $ 個以上のりんごを得ることはできないため、$ 5 $ を出力します。

## 样例 #1

### 输入

```
8 4 3
1 1
3 4
6 4
5 2
4 2
4 3
5 5
7 3```

### 输出

```
5```

# 题解

## 作者：2huk (赞：9)

# F - Apples

## Descripiton

数轴上有 $n$ 个苹果，第 $i$ 个苹果会在 $t_i$ 时刻在坐标 $x_i$ 的位置落下。

现在有一个长度为 $w$ 的篮子，耐用性为 $d$，表示这个篮子能接到在某个长度为 $d$ 的时间段内，某个长度为 $w$ 的线段内的苹果。

问最多能接到多少个苹果。

$1 \le n, d, w, t_i, x_i \le 2 \times 10^5$。

## Solution

首先双指针枚举时间段的左右端点，使得这个时间段的长度小于等于 $d$。这一步是 $\mathcal O(n)$ 的。

然后在枚举过程中线段树维护每个坐标上的苹果数量。当枚举到某个时间段时计算线段树上最大的长度为 $w$ 的区间和。

这一步显然不能 $\mathcal O(n \log n)$ 做，因此考虑重新维护线段树，用单点维护区间的信息。即第 $i$ 个位置上的值表示从 $i$ 开始，往后的长度为 $w$ 的区间之和，即区间 $[i, i + w)$ 内的苹果数量。那么查询时只需要找整颗线段树的最大值即可。

对于修改，当 $x_i$ 的位置上增加一个苹果时，线段树上 $(x_i - w, x_i]$ 都会增加 $1$。因为以这些位置开始的长度为 $w$ 的区间是包括 $x_i$ 的。同样的，当 $x_i$ 的位置上减少一个苹果时，线段树上 $(x_i - w, x_i]$ 都会减少 $1$。

因此维护一颗支持区间加，区间求最大值的线段树即可。总时间复杂度 $\mathcal O(n \log n)$。

## Code

赛后 50 分钟的代码：[Submission #47279637 - HHKB Programming Contest 2023(AtCoder Beginner Contest 327)](https://atcoder.jp/contests/abc327/submissions/47279637)

---

## 作者：未来姚班zyl (赞：4)

## 题目大意

在二维平面内有 $n$ 个点 $(T_i,X_i)$，求一个长（与横轴平行的边）为 $D$，宽（与纵轴平行的边）为 $W$ 的矩形能包含的最多的点数。

## 题目分析

~~又来水 abc 题解了~~。

这种二维问题显然要想办法消掉一维，最典的方法就是扫描线。我们扫描横坐标，则需要支持在 $O(\log n)$ 的时间内查询长度为 $W$ 的区间的和的最大值，不好用数据结构维护。考虑加一个点 $X_i$ 对那些区间有影响，显然是左端点在 $[X_i-W+1,X_i]$ 的区间。这样就只需区间修改与查询单点最大值，线段树维护之，复杂度 $O(n\log n)$。

出题人这题面让人稍微有点点难受，不如把值域开到 $2\times 10^9$ 有技术含量，而值域只有 $2\times 10^5$，那就很容易写了！

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5;
using namespace std;
int n=read(),d=read(),w=read();
struct node{
	int t,x;
}a[N];
struct seg{
	int w,laz;
}xd[N<<2];
int tot;
void ins(int x,int k){
	xd[x].w+=k,xd[x].laz+=k;
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k){

	if(OK)return ins(x,k),void();
	ins(L,xd[x].laz),ins(R,xd[x].laz),xd[x].laz=0;
	if(Ll<=mid&&Rr>=l)modify(lc,Ll,Rr,k);
	if(Ll<=r&&Rr>mid)modify(rc,Ll,Rr,k);
	xd[x].w=max(xd[L].w,xd[R].w);
}
inline bool cmp(node a,node b){
	return a.t<b.t;
}
signed main(){
	rep(i,1,n)a[i].t=read(),a[i].x=read();
	int m=N;
	int ans=0;
	sort(a+1,a+n+1,cmp);
	int Ll=1;
	rep(i,1,n){
		modify(1,1,m,max(1,a[i].x-w+1),a[i].x,1);
		while(Ll<=n&&a[Ll].t<a[i].t-d+1){
			modify(1,1,m,max(1,a[Ll].x-w+1),a[Ll].x,-1);Ll++;
		}
		ans=max(ans,xd[1].w);
	}
	cout <<ans;
	return 0;
}
```


---

## 作者：incra (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc327_f)
### 题解
读完题目，不难想到把题目简化为一下问题：

在一个 $(x,y)$ 平面，求一个长宽分别为 $d,w$ 的长方形中最多能框住几个点。

如果从两个维度进行双指针，时间复杂度为 $O(n^2)$ 超时。考虑优化。

仔细想想，再把问题转化一下：给定 $n$ 条竖的线段，每条线段的起始位置分别是 $(t,x)$ 和 $(t+d-1,x)$，求水平直线在哪里时会与这 $n$ 条线段的交点数量最大值。

纵坐标可以直接从上到下一次枚举，考虑一下横坐标要实现的操作：

1. 单点修改，每一个点加入和退出对一个点答案的影响。
2. 区间查询，查询一个宽为 $w$ 的线段能覆盖几个点。

注意这里一个点表示一个框内纵坐标的维度上给他压掉，也就是说把所有纵坐标的点的数量压到一个横线上。

仔细看看发现很像线段树，但貌似不好维护。

所以，又把要维护的东西转化一下：

1. 区间修改，每一个点加入和退出对答案中**哪些线段的答案有贡献**。
2. 区间查询，查询一个宽为 $w$ 的线段能覆盖几个点。

好像感觉复杂化了，但是其实变简单了，因为上面第 $1$ 条把对一个点的影响变为了区间的影响，使查询简单化了，仔细来说就是把维护的东西从一个点，**变成以这个点为区间左端点的答案了**。

于是，这题就做完了。

其实第二条直接查询所有的区间的最大值即可（不懂可以看代码）。

考试的时候最后一步没想到，废。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <map>
#include <set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 400010;	//	t+d >= 200000
int n,d,w;
vector <PII> g[N];
struct node {
	int l,r;
	int val;
	int add;
}tr[4 * N];
void push_up (int u) {
	tr[u].val = max (tr[u << 1].val,tr[u << 1 | 1].val);
}
void opt_add (int u,int d) {
	tr[u].val += d;
	tr[u].add += d;
}
void push_down (int u) {
	if (tr[u].add) {
		opt_add (u << 1,tr[u].add),opt_add (u << 1 | 1,tr[u].add);
		tr[u].add = 0;
	}
}
void build (int u,int l,int r) {
	tr[u] = {l,r,0,0};
	if (l == r) return ;
	int mid = l + r >> 1;
	build (u << 1,l,mid),build (u << 1 | 1,mid + 1,r);
}
void modify (int u,int l,int r,int d) {
	if (l <= tr[u].l && tr[u].r <= r) {
		opt_add (u,d);
		return ;
	}
	push_down (u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify (u << 1,l,r,d);
	if (r >= mid + 1) modify (u << 1 | 1,l,r,d);
	push_up (u);
}
int main () {
	cin >> n >> d >> w;
	for (int i = 1;i <= n;i++) {
		int t,x;
		cin >> t >> x;
		g[t].push_back ({x,1}),g[t + d].push_back ({x,-1});
	}
	build (1,0,N - 1);
	int ans = 0;
	for (int i = 1;i < N;i++) {
		for (auto [x,d] : g[i]) modify (1,max (x - w + 1,0),x,d);
		ans = max (ans,tr[1].val);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 前言

赛时切出 F 题，好高兴！

## 思路

首先可以想到把苹果按掉落时间排序，枚举一个苹果为最后接的一颗，双指针维护目前可以接到的有那些苹果（假设有 $k$ 个）。

现在问题就变成了给你 $k$ 个苹果的坐标以及篮子的长度 $w$，求最多能接多少个。如果我们记 $f_i$ 表示篮子以 $i$ 为右端点的个数，那对于一个坐标为 $x_j$ 的苹果 $j$，就会对 $f_{(x_j-w+1)\sim x_j}$ 有 $1$ 的贡献，最后的答案就是 $\displaystyle \max_{i=1}^{V} f_i$，其中 $V$ 表示值域。

不难发现，上述的过程可以用线段树维护，即区间加和查询最大值。这道题就做完了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> inline void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x<=9) return putchar(x+48),void();
    write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    puts("");
}
const int N = 2e5+5,V = 2e5;
int n,d,w;
struct node{
	int t,x;
	inline void init(){read(t),read(x);}
	friend inline bool operator < (node x,node y)
	{
		return x.t<y.t;
	}
}a[N];
#define ls (k*2)
#define rs (k*2+1)
struct Tree{
	int tag,mx;
}t[N<<2];
inline void down(int k)
{
	if(!t[k].tag) return;
	t[ls].mx+=t[k].tag,t[ls].tag+=t[k].tag;
	t[rs].mx+=t[k].tag,t[rs].tag+=t[k].tag;
	t[k].tag = 0;
}
void change(int k,int l,int r,int x,int y,int v)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return t[k].mx+=v,t[k].tag+=v,void();
	down(k);
	int mid = (l+r)/2;
	change(ls,l,mid,x,y,v),change(rs,mid+1,r,x,y,v);
	t[k].mx = max(t[ls].mx,t[rs].mx);
}
inline void modify(int i,int v){change(1,1,V,max(1,a[i].x-w+1),a[i].x,v);}
int ans;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(d),read(w);
	for(int i = 1;i<=n;i++)
		a[i].init();
	sort(a+1,a+n+1);//按时间排序
	int l = 1;
	for(int i = 1;i<=n;i++)
	{
		modify(i,1);//将当前苹果加入
		while(a[i].t-a[l].t>=d) modify(l,-1),l++;//将超过时间的苹果删掉
		ans = max(ans,t[1].mx);//直接取所有区间的最大值，即 1 号节点的值
	}
	write(ans);
	return 0;
}
```

---

## 作者：Otue (赞：1)

## 题目大意：

苹果坐标 $(T_i,X_i)$，一个宽为 $H$，高为 $W$ 的矩形最多框柱多少个苹果。且边框不算苹果。

## 题目做法

设某个苹果的坐标为 $(x,y)$，那么矩形右上角出现在 $(x\sim x+H-1,y\sim y+W-1)$ 这个范围内才能框柱苹果。

那么每个苹果都可以使用如上方法，去扩展成一个矩形，并把这个矩形权值加上 $1$。

最后等价于求：求在哪个坐标上权值的总和最大。

扫描线可轻松维护。

```c++
#include <bits/stdc++.h>
using namespace std;


const int N = 2e6 + 5;
int n, W, H;
vector<int> ys;

struct stu {
	int x, l, r;
	int k;
}ed[N * 2];

struct edge {
	int l, r, lazy, maxn;
}tree[N * 8];

int find(int x) {
	return lower_bound(ys.begin(), ys.end(), x) - ys.begin();
}

void push_up(int p) {
	tree[p].maxn = max(tree[p * 2].maxn, tree[p * 2 + 1].maxn);
}

void build(int p, int l, int r) {
	tree[p].l = l, tree[p].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid + 1, r);
}

void push_down(int p) {
	if (tree[p].lazy != 0) {
		tree[p * 2].lazy += tree[p].lazy;
		tree[p * 2 + 1].lazy += tree[p].lazy;
		tree[p * 2].maxn += tree[p].lazy;
		tree[p * 2 + 1].maxn += tree[p].lazy;
		tree[p].lazy = 0;
	}
}

void modify(int p, int l, int r, int k) {
	if (l <= tree[p].l && tree[p].r <= r) {
		tree[p].maxn += k; tree[p].lazy += k;
		return;
	} 
	push_down(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (l <= mid) modify(p * 2, l, r, k);
	if (r > mid) modify(p * 2 + 1, l, r, k);
	push_up(p);
}

int main() {
	ys.push_back(-2e9);
	cin >> n >> W >> H; 
	for (int i = 1, j = 0; i <= n; i++) {
		int x, y, val;
		cin >> x >> y;
		j++; ed[j] = {x, y, y + H - 1, 1}; 
		j++; ed[j] = {x + W - 1, y, y + H - 1, -1};
		ys.push_back(y), ys.push_back(y + H - 1);
	} 
	auto cmp = [&] (stu x, stu y) {
		if (x.x == y.x) return x.k > y.k;
		return x.x < y.x;
	};
	sort(ed + 1, ed + 2 * n + 1, cmp);
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	build(1, 1, ys.size());
	int res = 0;
	for (int i = 1; i <= 2 * n; i++) {
		modify(1, find(ed[i].l), find(ed[i].r), ed[i].k);
		res = max(res, tree[1].maxn);
	}
	cout << res << endl;
}
```

---

## 作者：bmatrix (赞：1)

[题面](https://www.luogu.com.cn/problem/AT_abc327_f)。

[加强版（窗口的星星）](https://www.luogu.com.cn/problem/P1502)。

> 平面内有 $n$ 个点 $(x_i,y_i)$，找到一个 $d\times w$ 的矩形，使得矩形内的点数最大，边框上的点不算矩形内。
>
> $1\le n,x_i,y_i,d,w\le2\times10^5$

为什么窗口的星星题解区几乎都是转化为矩形面积交啊？这里提供另一种解法。

首先将点按 $x$ 坐标排序，然后进行尺取，使选中的点的 $x$ 坐标之差 $<d$，即移动一个长为 $d$ 的线段。

这一步消除了 $x$ 坐标的影响，只考虑选中的点的 $y$ 坐标，问题转化为维护一个序列 $\{a\}$，支持单点修改，查询所有长为 $w$ 的子区间的元素和的最大值。

由于 $w$ 是定值，所以考虑构造数列 $\{b_i=\sum_{j=i}^{j+w-1}a_i\}$。单点修改转化为 $\{b\}$ 的区间修改，具体地，将 $a_i$ 加上 $v$ 转化为了将 $b_{i-w+1}$ 到 $b_i$ 都加上 $v$；询问转化为求 $\{b\}$ 的最大值。

线段树可以实现这个功能，时间复杂度 $O(n\log V)$，其中 $V$ 为值域。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
// #define int ll
#define gmin(x, y) (x = min(x, y))
#define gmax(x, y) (x = max(x, y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
template<class T = int> const T& read() {
    static T x; cin >> x; return x;
}
constexpr int N = 2e5 + 5;
int n, d, w;
pii a[N];
struct node {
    int mx, tag;
} nd[N * 4];
#define ls (p << 1)
#define rs (p << 1 | 1)
void upd(int p, int x) {
    nd[p].mx += x, nd[p].tag += x;
}
void pushdown(int p) {
    if(nd[p].tag) {
        upd(ls, nd[p].tag);
        upd(rs, nd[p].tag);
        nd[p].tag = 0;
    }
}
void pushup(int p) {
    nd[p].mx = max(nd[ls].mx, nd[rs].mx);
}
void add(int p, int l, int r, int ql, int qr, int v) {
    if(ql <= l && r <= qr) return upd(p, v);
    pushdown(p);
    int mid = (l + r) / 2;
    if(ql <= mid) add(ls, l, mid, ql, qr, v);
    if(qr > mid) add(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> n >> d >> w;
    rep(i, 1, n) cin >> a[i].F >> a[i].S;
    sort(a + 1, a + n + 1);
    // rep(i, 1, n) cerr << a[i].F << ' ' << a[i].S << endl;
    // cerr << endl;
    int j = 1, ans = 0;
    rep(i, 1, n) {
        add(1, 1, 200000 - w + 1, max(1, a[i].S - w + 1), min(200000 - w + 1, a[i].S), 1);
        while(j <= n && a[i].F - a[j].F + 1 > d) {
            add(1, 1, 200000 - w + 1, max(1, a[j].S - w + 1), min(200000 - w + 1, a[j].S), -1);
            ++j;
        }
        // cerr << j << ' ' << nd[1].mx << endl;
        gmax(ans, nd[1].mx);
    }
    cout << ans << endl;
    return 0;
}
```

窗口的星星那题只需要加一个动态开点就好了。

---

## 作者：NBest (赞：0)


二维变一维想到扫描线，而这里有限制 $x,t$ 的范围求最大值，我们不妨按照套路静一动一，排序后双指针枚举 $x$，然后把符合范围要求的加入贡献，而贡献的计算就是算每个苹果能对哪些时间范围早成贡献，可以用线段树区间加维护，最后求全局最大值即可，这题甚至不需要离散化，复杂度 $O(n\log n)$。
### Code
```cpp
PII a[N+5];
int n,d,w,tr[(N<<2)+5],lazy[(N<<2)+5],ans;
inline void add(int root,int v){tr[root]+=v,lazy[root]+=v;}
void update(int root,int l,int r,int x,int y,int v){
    if(x<=l&&r<=y)return add(root,v),void();
    add(root<<1,lazy[root]),add(root<<1|1,lazy[root]),lazy[root]=0;
    int mid=l+r>>1;
    if(mid>=x)update(root<<1,l,mid,x,y,v);
    if(mid<y)update(root<<1|1,mid+1,r,x,y,v);
    tr[root]=max(tr[root<<1],tr[root<<1|1]);
}
int main(){
    n=read(),d=read(),w=read();
    for(int i=1;i<=n;i++)a[i].first=read(),a[i].second=read();
    sort(a+1,a+1+n);
    for(int i=1,l=0;i<=n;i++){
        while(l<n&&a[l+1].first-a[i].first<d)
            l++,update(1,1,N,max(a[l].second-w+1,1),a[l].second,1);
        ans=max(ans,tr[1]);
        update(1,1,N,max(a[i].second-w+1,1),a[i].second,-1);
    }
    cout<<ans;
}
```

---

## 作者：West_2_31_1 (赞：0)

## 题目大意 

在平面上有 $N$ 个点，现在高橋君用一个 $D \times W$ 的矩形来框住这些点，问最多框住多少个。

## 解题思路

首先，我们先用双指针简化问题。

枚举 $T_i$ 相等的点，双指针 $j$ 跳满足 $T_j < T_i+D$ 的点，区间内的点加入点集。

问题转化为维护一个点集内的子集 $\{X_1,X_2,\dots,X_k\}$ 满足 $\max X_i - \min X_i \leq W$，求子集大小的最值。

显然，每一个加入的 $X_i$ 都对一些区间有贡献。

进一步发现区间的起点是一段连续的自然数。

建一棵线段树，第 $i$ 个叶子节点表示一段区间 $[i,i+w)$ 的答案。

每次加入一个点就是区间 $+1$，删一个点就是 $-1$。

查全局最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
	char Is[(1<<21)+10],Os[(1<<21)+10];
	int Ipt,Opt;
	char gc(){
		if(Ipt==1<<21)Ipt=0;
		if(!Ipt){Is[fread(Is,1,1<<21,stdin)]=0;}
		return Is[Ipt++];
	}
	void flush(){fwrite(Os,1,Opt,stdout);Opt=0;}
	void pc(char x){
		if(Opt==1<<21)flush();
		Os[Opt++]=x;
	}
	int read(){
		int x=0;char ch=gc();while(ch<'0'||ch>'9')ch=gc();while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=gc();return x;
	}
}
using namespace IO;
struct P{
	int x,y;
}p[200001];
bool cmp(P x,P y){
	return x.x==y.x?x.y<y.y:x.x<y.x;
}
int lazy[800001];
int tree[800001];
void pushdown(int x){
	lazy[x*2]+=lazy[x];
	tree[x*2]+=lazy[x]; 
	lazy[x*2+1]+=lazy[x];
	tree[x*2+1]+=lazy[x];
	lazy[x]=0;
}
void add(int x,int l,int r,int L,int R,int z){
	if(l==L&&r==R){
		lazy[x]+=z;
		tree[x]+=z;
		return;
	}
	pushdown(x);
	int mid=l+r>>1;
	if(R<=mid){
		add(x*2,l,mid,L,R,z);
	}else if(L>mid){
		add(x*2+1,mid+1,r,L,R,z);
	}else{
		add(x*2,l,mid,L,mid,z);
		add(x*2+1,mid+1,r,mid+1,R,z);
	}
	tree[x]=max(tree[x*2],tree[x*2+1]);
} 

int main(){
	int n,d,w;
	n=read(),d=read(),w=read();
	for(int i=1;i<=n;++i){
		p[i].x=read();
		p[i].y=read();
	}
	sort(p+1,p+1+n,cmp);
	int j=0;
	int ans=0;
	for(int i=1;i<=n;++i){
		while(j<n&&p[i].x+d>p[j+1].x){
			++j;
			add(1,1,200000,max(p[j].y-w+1,1),p[j].y,1);
		}
		ans=max(tree[1],ans);
		add(1,1,200000,max(p[i].y-w+1,1),p[i].y,-1);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

没打补一下题。

# 正文

第一眼看出两维同时尺取，但是这样显然寄透。

不妨考虑一个经典问题：一个平面上有若干点，求用一个矩形覆盖最大点数。可以发现本题也可转换成这个问题，这是很容易想到的。

~~如果你关注日报的话会发现会有一篇浅谈扫描线~~，而这个问题恰好是经典的扫描线问题。

我们考虑当前这个矩形能覆盖几个点，但是很显然这不太好做。

于是我们可以考虑每个点能被几个矩形覆盖。这样就很好做了：拿扫描线暴力维护一维，另外一维采用数据结构维护当前扫描线上的每个坐标上的点被几个矩形覆盖。

具体来说我们考虑对于每一个苹果 $(t, x)$ 都建立一个入点 $(t, x)$ 和出点 $(t, x + D - 1)$，一个 $+1$ 一个 $-1$。

关于另一维的限制，可以考虑排序尺取，也可以考虑区间修改。这里使用区间修改；尺取版的也很好想，只需去维护左右端点时间差小于 $D$ 即可。

这题的妙处还是在于如何把苹果的位置转化成能接住它的所有篮子的左上端点。

另：这题若值域变大，需要动态开点线段树。

# 代码

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll N, D, W, cnt, ans; 

struct Point {
	ll x, y, val;
} arr[400005];

bool operator <(Point a, Point b)
{
	return (a.x != b.x) ? (a.x < b.x) : (a.val > b.val);
}

#define lson ((p << 1) | 0)
#define rson ((p << 1) | 1)

struct SegmentTree {
	ll max, lazytag_add;
} tree[800005];

void pushdown(ll p)
{
	tree[lson].max += tree[p].lazytag_add;
	tree[rson].max += tree[p].lazytag_add;
	tree[lson].lazytag_add += tree[p].lazytag_add; 	
	tree[rson].lazytag_add += tree[p].lazytag_add;
	tree[p].lazytag_add = 0;
}

void merge(ll p)
{
	tree[p].max = max(tree[lson].max, tree[rson].max);
} 

ll query_max(ll l, ll r, ll lll, ll rrr, ll p)
{
	if(lll <= l && rrr >= r)
		return tree[p].max;
	
	if(tree[p].lazytag_add) pushdown(p);
	ll mid = (l + r) >> 1, res = 0;	
	if(lll <= mid + 0) res = max(res, query_max(l, mid, lll, rrr, lson));
	if(rrr >= mid + 1) res = max(res, query_max(mid + 1, r, lll, rrr, rson));
	merge(p);
	return res;
}

void modify_add(ll l, ll r, ll lll, ll rrr, ll val, ll p)
{
	if(lll <= l && rrr >= r)
	{
		tree[p].lazytag_add += val;
		tree[p].max += val;
		return;
	}
	
	if(tree[p].lazytag_add) pushdown(p);
	ll mid = (l + r) >> 1, res = 0;	
	if(lll <= mid + 0) modify_add(l, mid, lll, rrr, val, lson);
	if(rrr >= mid + 1) modify_add(mid + 1, r, lll, rrr, val, rson);
	merge(p);
}

signed main()
{
	cin >> N >> D >> W;
	for(ll i = 1; i <= N; ++ i) { ll t, x; cin >> t >> x; arr[++ cnt] = (Point) {t, x, 1}; arr[++ cnt] = (Point) {t + D - 1, x, -1}; }
	sort(arr + 1, arr + cnt + 1);
	for(ll i = 1; i <= cnt; ++ i)
	{
		ll l = arr[i].y, r = min(200000ll, arr[i].y + W - 1ll);
		modify_add(1, 200000, l, r, arr[i].val, 1);
		ans = max(ans, query_max(1, 200000, 1, 200000, 1));
	}
	
	cout << ans << endl;
	return 0;
}

```

# 后言

还是要感谢[这篇文章](https://www.luogu.com.cn/blog/478585/qian-tan-sao-miao-xian)。

---

## 作者：DengDuck (赞：0)

这题你把时间变成一个维度，放在一个坐标系上，那就是：

> 要求你在一个 $10^5\times 10^5$ 找到一个包含点最多的 $d\times w$ 个矩形。

什么二维前缀和啊，滑动窗口啊肯定都会寄，考虑技巧，用数据结构维护一维。

容易想到只对时间滑动窗口，那么你需要维护的就是一维的区间定长，你用线段树维护一个点作为区间左端点的区间和即可，每次删除一个时间的贡献，加入一个时间的贡献。

那你修改时考虑有哪些区间包含我就行，修改就是区间加，查询是全局最值，比较好写。

然后直接做就行了，没啥难度，$\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
const LL M=2e5;
struct node
{
	LL l,r,mx,lz;
}t[N*20];
LL n,d,w,x,y,ans;
vector<LL>v[N];
void build(LL rt,LL l,LL r)
{
	t[rt]={l,r,0,0};
	if(l==r)return;
	LL mid=(l+r)/2;
	build(rt*2,l,mid),build(rt*2+1,mid+1,r);
}
void down(LL rt)
{
	LL l=rt*2,r=rt*2+1,k=t[rt].lz;
	t[l].mx+=k,t[l].lz+=k;
	t[r].mx+=k,t[r].lz+=k;
	t[rt].lz=0;
}
void upd(LL rt,LL l,LL r,LL x)
{
	if(t[rt].r<l||r<t[rt].l)return;
	if(l<=t[rt].l&&t[rt].r<=r)
	{
		t[rt].lz+=x;
		t[rt].mx+=x;
		return;
	}
	down(rt);
	upd(rt*2,l,r,x),upd(rt*2+1,l,r,x);
	t[rt].mx=max(t[rt*2].mx,t[rt*2+1].mx);
}
void add(LL x,LL k)
{
	for(LL i:v[x])
	{
		LL t=max(1ll,i-w+1);
		upd(1,t,i,k);
	}
}
int main()
{
	cin>>n>>d>>w;
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
	}
	build(1,1,M);
	for(int i=1;i<=d-1;i++)
	{
		add(i,1);
	}
	for(int i=1;i+d-1<=M;i++)
	{
		add(i+d-1,1);
		ans=max(ans,t[1].mx);
		add(i,-1);
	}
	cout<<ans<<endl;
}
```

---

## 作者：BYR_KKK (赞：0)

[Here](https://www.luogu.com.cn/problem/AT_abc327_f)

## 题意

有 $n$ 个苹果，第 $i$ 个会在第 $t_i$ 时刻落在 $x_i$ 处。高桥可以选择时间 $T$ ，位置 $X$ ，使得获得在时间段 $[T,T+D)$ 落在 $[X,X+w)$ 区域内的所有苹果。求最大化苹果的数量。

## 思路

发现可以按时间对苹果排序后双指针扫一遍，这样可以 $O(n-w)$ 地维护每一个时间段。

接着考虑我们如何考虑在某个时间苹果数量的变化。这种区间类的题，容易想到线段树 ~~（所以我赛时妄图用二维线段树过掉这道题）~~。用线段树记录现在每个区间有多少苹果。但是这样统计最大值明显不方便。于是我们用线段树表示从某点开始长度为 $w$ 的区间有多少苹果。

苹果的变化直接区间加减即可，找答案时直接找区间最大值即可。

## code

```cpp

#include<bits/stdc++.h>
#define int long long
#define pii std::pair<int,int>
#define fi first
#define se second

const int maxn=3e5+10;

pii a[maxn];

std::vector<int>t[maxn];

struct node{
	int l,r,lz,max;
}s[maxn<<2];

void push_up(int p){
	s[p].max=std::max(s[p*2].max,s[p*2+1].max);
	return ;
} 

void build(int p,int l,int r){
	s[p].l=l,s[p].r=r;
	if(l==r) {
		s[p].max=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	push_up(p);
	return ;
}

void push_down(int p){
	if(s[p].lz){
		int ls=p*2,rs=ls+1;
		s[ls].lz+=s[p].lz,s[rs].lz+=s[p].lz;
		s[ls].max+=s[p].lz,s[rs].max+=s[p].lz;
		s[p].lz=0;	
	}
	return ;
}

void upd(int p,int L,int R,int k){//支持区间加 
	int l=s[p].l,r=s[p].r;
	if(l>=L&&r<=R){
		s[p].max+=k;
		s[p].lz+=k;
		return ;
	}
	push_down(p);
	int mid=(l+r)>>1;
	if(mid>=L) upd(p*2,L,R,k);
	if(R>mid) upd(p*2+1,L,R,k);
	push_up(p);
	return ;
}

int query(int p,int L,int R) {
	int l=s[p].l,r=s[p].r;
	if(l>=L&&r<=R) return s[p].max;
	push_down(p);
	int mid=(l+r)>>1;
	int ans=-0x3f3f3f3f;
	if(mid>=L) ans=std::max(ans,query(p*2,L,R));
	if(R>mid) ans=std::max(ans,query(p*2+1,L,R));
	return ans;
}

signed main(){
	int n,d,w;
	std::cin>>n>>d>>w;
	int max=-1;
	for(int i=1;i<=n;i++){
		std::cin>>a[i].fi>>a[i].se;
		max=std::max(a[i].fi,max);
	}
	std::sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) t[a[i].fi].push_back(i);
	build(1,1,max);
	int z=1;
	int ti=1;//end:ti+d-1
	for(int i=1;i<ti+d;i++){
		while(z<=n&&a[z].fi==i){
			int wh=a[z].se;
			upd(1,std::max(1ll,wh-w+1),wh,1);
			z++;
		}
	}
	int ans=query(1,1,max);	
	int en=ti+d-1;
	while(z<=n){
		for(int i=0;i<t[ti].size();i++){
			int x=t[ti][i];
			upd(1,std::max(1ll,a[x].se-w+1),a[x].se,-1);
		} 
		ti++,en++;
		while(z<=n&&a[z].fi==en){
			upd(1,std::max(1ll,a[z].se-w+1),a[z].se,1);
			z++;
		}
		ans=std::max(ans,query(1,1,max));
	}
	std::cout<<ans;
	return 0;
} 

```

---

## 作者：joyslog (赞：0)

我们对题意做一个转化，每个苹果的位置和时间可以映射为平面直角坐标系中的一个关键点 $(T_i,X_i)$。选择一对 $S,L$，相当于框定一个坐标系中的矩形，左下角为 $(S,L)$，右上角为 $(S+D-1,L+W-1)$，然后计算矩形中有多少个苹果。

那么这个问题就比较经典了，我们可以用扫描线的思想解决。首先可以发现，矩形的左边界上存在关键点的情况中，必定包括最优情况。那么对于一个点 $i$，它在横轴上能影响的范围为 $[T_i,T_i+D-1]$。所以我们从左到右扫横坐标，碰到 $T_i$ 时我们往区间 $[X_i, X_i+W-1]$ 上加一，碰到 $T_i+D$ 时往 $[X_i, X_i+W-1]$ 上减一。那么在点 $i$ 有影响的范围内，包含的最多的点数就是这时的全局最大值。

用线段树维护即可。时间复杂度 $\mathcal{O}(n\log V)$，其中 $V$ 为值域。

赛时 [Record](https://atcoder.jp/contests/abc327/submissions/47272757)。注意细节，排序时若横坐标相同，要把减一排在加一前面。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {...}
inline void write(ll x) {...}

const int MAX_N = 4e5 + 10;
int n, D, W, ans, cnt;
struct node {
    int x, y, f;
    node(int _x = 0, int _y = 0, int _f = 0) :
        x(_x), y(_y), f(_f) { } 
    bool operator < (const node &t) const { return x == t.x ? f < t.f : x < t.x; }
} a[MAX_N << 1];

struct tnode {
    int val, tag;
    tnode() { val = tag = 0; }
} d[MAX_N << 4];
inline int lc(int p) { return (p << 1); }
inline int rc(int p) { return (p << 1) | 1; }
inline int mid(int s, int t) { return (s + t) >> 1; }
inline void pd(int p) {
    if(d[p].tag != 0) {
        d[lc(p)].val += d[p].tag, d[rc(p)].val += d[p].tag;
        d[lc(p)].tag += d[p].tag, d[rc(p)].tag += d[p].tag;
        d[p].tag = 0;
    }
}
void update(int s, int t, int p, int l, int r, int f) {
    if(l <= s && t <= r) {
        d[p].val += f;
        d[p].tag += f;
        return;
    }
    pd(p);
    int m = mid(s, t);
    if(l <= m)  update(s, m, lc(p), l, r, f);
    if(r > m)   update(m + 1, t, rc(p), l, r, f);
    d[p].val = max(d[lc(p)].val, d[rc(p)].val);
}


int main() {
    n = read(), D = read() - 1, W = read() - 1;
    for(int i = 1; i <= n; i++) {
        int t = read(), x = read();
        a[++cnt] = node(t, x, 1);
        a[++cnt] = node(t + D + 1, x, -1);
    }
    sort(a + 1, a + cnt + 1);
    ans = 1;
    for(int i = 1; i <= cnt; i++) {
        update(1, MAX_N, 1, a[i].y, a[i].y + W, a[i].f);
        ans = max(ans, d[1].val);
    }
    write(ans), putchar('\n');
    return 0;
}
```

---

## 作者：escapist404 (赞：0)

有 $n$ 个苹果将要掉落在数轴上，具体地，第 $i$ 个苹果，将要在第 $t_i$ 秒掉落在坐标 $x_i$ 上。

高桥君有一个长度为 $w$ 的篮子，他可以把篮子放在数轴上 $d$ 秒**恰好一次**。

具体地，假设第 $s$ 秒高桥君在坐标 $l$ 放下篮子，这样他能够捡起所有掉落时刻在 $[s, s + d)$、坐标在 $[l, l + w)$ 的苹果。

请求出他最多能捡到多少苹果。

---

一道很像 [P1502](https://www.luogu.com.cn/problem/P1502) 的题目。

将苹果全部拍到 时间 - 坐标 坐标系中，则我们要求：在一个长度为 $d$、宽度在 $w$ 的矩形内，能框住多少苹果。

考虑一个转化：一个苹果 $(t, x)$ 能被框住，当且仅当：矩形的左下角两个坐标分别在 $[t - d + 1, t + 1)$ 和 $[x - w + 1, x + 1)$ 之间。

这样就变成扫描线板子了。答案就是每个时刻的最大值。

一个细节：要先处理 $-1$ 的操作，再处理 $1$ 的操作。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

template <typename Value, typename Lazy>
class LazySegmentTree {
    int n;
    std::vector<Value> value;
    std::vector<Lazy> lazy;
    inline int lhs(const int id) { return (id << 1) + 1; }
    inline int rhs(const int id) { return (id << 1) + 2; }
    void push_down(const int id) {
        value[lhs(id)] += lazy[id], value[rhs(id)] += lazy[id];
        lazy[lhs(id)] += lazy[id], lazy[rhs(id)] += lazy[id];
        lazy[id] = Lazy();
    }
    void push_up(const int id) { value[id] = value[lhs(id)] + value[rhs(id)]; }
    void set(int id, int l, int r, int _l, int _r, Lazy _k) {
        if (_l <= l && r <= _r) return value[id] += _k, lazy[id] += _k, void();
        push_down(id);
        if (_l < ((l + r) >> 1)) set(lhs(id), l, (l + r) >> 1, _l, _r, _k);
        if (_r > ((l + r) >> 1)) set(rhs(id), (l + r) >> 1, r, _l, _r, _k);
        push_up(id);
    }
    Value get(int id, int l, int r, int _l, int _r) {
        if (_l <= l && r <= _r) return value[id];
        push_down(id);
        if (_l >= ((l + r) >> 1)) return get(rhs(id), (l + r) >> 1, r, _l, _r);
        if (_r <= ((l + r) >> 1)) return get(lhs(id), l, (l + r) >> 1, _l, _r);
        return get(lhs(id), l, (l + r) >> 1, _l, _r) +
               get(rhs(id), (l + r) >> 1, r, _l, _r);
    }
    template <typename P>
    int first(int id, int l, int r, int _l, int _r, P pred) {
        if (l + 1 == r) {
            if (pred(value[id]))
                return l;
            else
                return -1;
        }
        push_down(id);
        if (pred(value[lhs(id)]))
            return first(lhs(id), l, (l + r) >> 1, _l, _r, pred);
        else
            return first(rhs(id), (l + r) >> 1, r, _l, _r, pred);
    }
    template <typename P>
    int last(int id, int l, int r, int _l, int _r, P pred) {
        if (l + 1 == r) {
            if (pred(value[id]))
                return l;
            else
                return -1;
        }
        push_down(id);
        if (pred(value[rhs(id)]))
            return last(lhs(id), (l + r) >> 1, r, _l, _r, pred);
        else
            return last(lhs(id), l, (l + r) >> 1, _l, _r, pred);
    }
    void init(int id, int l, int r) {
        lazy[id] = Lazy();
        if (l + 1 == r) {
            value[id] = Value();
        } else {
            init(lhs(id), l, (l + r) >> 1), init(rhs(id), (l + r) >> 1, r);
            push_up(id);
        }
    }

   public:
    void set(int l, int r, Lazy k) { set(0, 0, n, l, r, k); }
    void set(int p, Lazy k) { set(p, p + 1, k); }
    void set(Lazy k) { value[0] += k, lazy[0] += k; }
    Value get(int l, int r) { return get(0, 0, n, l, r); }
    Value get(int p) { return get(p, p + 1); }
    Value get() { return value[0]; }
    template <typename P>
    int first(int l, int r, P pred) {
        return first(0, 0, n, l, r, pred);
    }
    template <typename P>
    int first(P pred) {
        return first(0, n, pred);
    }
    template <typename P>
    int last(int l, int r, P pred) {
        return last(0, 0, n, l, r, pred);
    }
    template <typename P>
    int last(P pred) {
        return last(0, n, pred);
    }
    LazySegmentTree(int n) : n(n), value(n << 2), lazy(n << 2) {
        init(0, 0, n);
    }
};

using i64 = long long;

struct Lazy {
	i64 fix;
	Lazy(i64 fix = 0) : fix(fix) {}
	void operator+= (Lazy x) {
		fix += x.fix;
	}
};

struct Value {
	i64 cur;
	Value(i64 cur = 0) : cur(cur) {}
	void operator+= (Lazy x) {
		cur += x.fix;
	}
	void operator+= (Value x) {
		cur = std::max(cur, x.cur);
	}
};

Value operator+ (Value x, Value y) {
	return Value(std::max(x.cur, y.cur));
}

int main() {
	int n, d, w;
	std::cin >> n >> d >> w;
	std::vector<std::pair<int, int>> a(n);
	for (auto& [t, x] : a) std::cin >> t >> x;

	LazySegmentTree<Value, Lazy> T(200'001);
	std::vector<std::tuple<int, int, int, int>> process;
	for (auto [t, x] : a) {
		process.emplace_back(x - w, x, t - d, 1);
		process.emplace_back(x - w, x, t, -1);
	}

	std::sort(process.begin(), process.end(), [](std::tuple<int, int, int, int> x, std::tuple<int, int, int, int> y) {
		if (std::get<2>(x) == std::get<2>(y)) return std::get<3>(x) < std::get<3>(y);
		return std::get<2>(x) < std::get<2>(y);
	});

	i64 answer = 0;
	for (auto [l, r, x, d] : process) {
		T.set(l, r, Lazy(d));
		answer = std::max(answer, T.get().cur);
	}

	std::cout << answer << '\n';
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

简单转化一下：

在一个平面内有若干点，求一个 $d\times w$ 的矩形最多能框住多少点。

考虑枚举位置区间。

接下来转换为求一个时间区间上长度为 $d$ 的最大子段和。

怎么处理这个东西呢？我们把一个点看作可以框住它的矩形，即 $w$ 条在 $y$ 轴上的长度为 $d$ 的线段。

那么直接上扫描线就好了。把所有点按 $x$ 从小到大排序，把每个点的出现、消失位置的线段用把它 $+1,-1$ 表示。每次求全局 $\max$ 就是当前 $x$ 轴上的所有矩形的答案。

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
struct Tree{
	struct node{
		int maxn,lazy;
		node(){
			maxn=lazy=0;
		}
		void tag(int val){
			maxn+=val;
			lazy+=val;
		}
	}tr[MAXN<<2];
	node pushup(node a,node b){
		a.maxn=max(a.maxn,b.maxn);
		a.lazy=0;
		return a;
	}
	void pushdown(int root){
		if(tr[root].lazy){
			tr[root<<1].tag(tr[root].lazy);
			tr[root<<1|1].tag(tr[root].lazy);
			tr[root].lazy=0;
		}
	}
	void update(int root,int l,int r,int ql,int qr,int val){
		if(ql<=l&&qr>=r){
			tr[root].tag(val);
			return;
		}
		pushdown(root);
		int mid=(l+r)>>1;
		if(ql<=mid) update(root<<1,l,mid,ql,qr,val);
		if(qr>mid) update(root<<1|1,mid+1,r,ql,qr,val);
		tr[root]=pushup(tr[root<<1],tr[root<<1|1]);
	}
}tree;
struct point{
	int x,y,val;
}p[MAXN<<1];
int n,d,w,cnt,ans;
signed main(){
	cin>>n>>d>>w;
	d--,w--;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		p[++cnt]=(point){x,y,1};
		p[++cnt]=(point){x+d,y,-1};
	}
	sort(p+1,p+cnt+1,[](point a,point b){
		if(a.x!=b.x) return a.x<b.x;
		return a.val>b.val;
	});
	for(int i=1;i<=cnt;i++){
		int l=p[i].y,r=min(200000,p[i].y+w);
		tree.update(1,1,200000,l,r,p[i].val);
		ans=max(ans,tree.tr[1].maxn);
	}
	cout<<ans;
}
```

---

## 作者：SegTree (赞：0)

我们将苹果当作一个点 $(t_i,x_i)$。现在问题等价于有一个长为 $d-1$，宽为 $w-1$ 的矩形最多框住几个点。（$-1$ 是因为边界框不到）。

我们考虑将问题转化，它对矩形左上角在 $t_i-d+1\le x\le t_i,x_i-w+1\le y\le x_i$ 会造成 $1$ 的贡献。

考虑把贡献在 $t_i-d+1$ 的时候加入，在 $t_i+1$ 时删除，每次对区间 $[x_i-w+1,x_i]$ 加一或减一，查询全局 $\max$ 即可。

[Record](https://atcoder.jp/contests/abc327/submissions/47248989)。

---

