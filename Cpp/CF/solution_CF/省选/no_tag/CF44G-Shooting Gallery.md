# Shooting Gallery

## 题目描述

Berland amusement park shooting gallery is rightly acknowledged as one of the best in the world. Every day the country's best shooters master their skills there and the many visitors compete in clay pigeon shooting to win decent prizes. And the head of the park has recently decided to make an online version of the shooting gallery. During the elaboration process it turned out that the program that imitates the process of shooting effectively, is needed. To formulate the requirements to the program, the shooting gallery was formally described. A 3D Cartesian system of coordinates was introduced, where the $ X $ axis ran across the gallery floor along the line, along which the shooters are located, the $ Y $ axis ran vertically along the gallery wall and the positive direction of the $ Z $ axis matched the shooting direction. Let's call the $ XOY $ plane a shooting plane and let's assume that all the bullets are out of the muzzles at the points of this area and fly parallel to the $ Z $ axis. Every clay pigeon can be represented as a rectangle whose sides are parallel to $ X $ and $ Y $ axes, and it has a positive $ z $ -coordinate. The distance between a clay pigeon and the shooting plane is always different for every target. The bullet hits the target if it goes through the inner area or border of the rectangle corresponding to it. When the bullet hits the target, the target falls down vertically into the crawl-space of the shooting gallery and cannot be shot at any more. The targets are tough enough, that's why a bullet can not pierce a target all the way through and if a bullet hits a target it can't fly on. In input the simulator program is given the arrangement of all the targets and also of all the shots in the order of their appearance. The program should determine which target was hit by which shot. If you haven't guessed it yet, you are the one who is to write such a program.

## 样例 #1

### 输入

```
2
1 4 1 4 1
2 5 2 6 2
4
0 0
3 3
4 5
3 5
```

### 输出

```
0
1
2
0
```

# 题解

## 作者：Leianha (赞：10)

### [博客阅读](https://www.cnblogs.com/wljss/p/13092964.html)

我们考虑用靶子来匹配射击点，可以把靶子按 $z$ 从小到大排序后，依次寻找范围内的编号最小的射击点，并将其删除，正确性显然。

考虑如何优化这个过程，实际上我们的操作分为两种:

$1.$ 在二维平面内找编号最小的点。

$2.$ 在二维平面内删除点。

可以把射击点建出 $KDtree$ ，然后维护查询和删除 ，具体实现可以看代码。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define lson tr[k].ls
#define rson tr[k].rs
using namespace std;
int n, m, root, cnt, nowk, ans;
const int N = 100010, inf = 1e8;
int fa[N], pos[N], Ans[N];
struct mb 
{
    int xl, yl, xr, yr, z, id;
    friend bool operator <(const mb &a, const mb &b)
    {return a.z < b.z;}
} B[N];
struct sj 
{
    int x, y, id;
    friend bool operator <(const sj &a, const sj &b)
    {return nowk ? a.x < b.x : a.y < b.y;}
} S[N];
struct shu 
{
    int mn, id, x, y, minx, miny, maxx, maxy, ls, rs;
} tr[N];
void pushup(int k) 
{
    tr[k].mn = tr[k].id;
    if (lson) 
    {
        tr[k].mn = min(tr[k].mn, tr[lson].mn);
        tr[k].minx = min(tr[k].minx, tr[lson].minx); tr[k].miny = min(tr[k].miny, tr[lson].miny);
        tr[k].maxx = max(tr[k].maxx, tr[lson].maxx); tr[k].maxy = max(tr[k].maxy, tr[lson].maxy);
    }
    if (rson) 
    {
        tr[k].mn = min(tr[k].mn, tr[rson].mn);
        tr[k].minx = min(tr[k].minx, tr[rson].minx); tr[k].miny = min(tr[k].miny, tr[rson].miny);
        tr[k].maxx = max(tr[k].maxx, tr[rson].maxx); tr[k].maxy = max(tr[k].maxy, tr[rson].maxy);
    }
}
void build(int FA, int &k, int l, int r, int KD) 
{
    if (l > r)return;
    int mid = (l + r) >> 1; k = ++cnt; nowk = KD;
    nth_element(S + l, S + mid, S + r + 1);
    pos[S[mid].id] = k; fa[k] = FA;
    tr[k].id = tr[k].mn = S[mid].id;
    tr[k].x = tr[k].minx = tr[k].maxx = S[mid].x;
    tr[k].y = tr[k].miny = tr[k].maxy = S[mid].y;
    build(k, lson, l, mid - 1, KD ^ 1); build(k, rson, mid + 1, r, KD ^ 1);
    pushup(k);
}
void ask(int k, int xl, int yl, int xr, int yr) 
{
    if (tr[k].maxx < xl || xr < tr[k].minx || tr[k].maxy < yl || yr < tr[k].miny)return;
    if (xl <= tr[k].minx && tr[k].maxx <= xr && yl <= tr[k].miny && tr[k].maxy <= yr) {ans = min(ans, tr[k].mn); return;}
    if (tr[k].id != inf && xl <= tr[k].x && tr[k].x <= xr && yl <= tr[k].y && tr[k].y <= yr) {ans = min(ans, tr[k].id);}
    if (lson)ask(lson, xl, yl, xr, yr);
    if (rson)ask(rson, xl, yl, xr, yr);
}
void shan(int x) 
{
    tr[x].id = inf;
    while (x) 
    {
        pushup(x);
        x = fa[x];
    }
}
int main() 
{
    cin >> n;
    for (int i = 1, xl, xr, yl, yr, z; i <= n; ++i) 
    {
        scanf("%d%d%d%d%d", &xl, &xr, &yl, &yr, &z);
        B[i] = (mb) {xl, yl, xr, yr, z, i};
    }
    cin >> m;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &S[i].x, &S[i].y), S[i].id = i;
    build(0, root, 1, m, 0);
    sort(B + 1, B + 1 + n);
    for (int i = 1; i <= n; ++i) 
    {
        ans = inf; ask(root, B[i].xl, B[i].yl, B[i].xr, B[i].yr);
        if (ans != inf) 
        {
            Ans[ans] = B[i].id;
            shan(pos[ans]);
        }
    }
    for (int i = 1; i <= m; ++i)printf("%d\n", Ans[i]);
    return 0;
}
```

---

## 作者：Jerrywang09 (赞：3)

超级大数据结构题。先将这些矩形的坐标离散化。这里注意要按行、列分别离散化，不然内存开不下。	

解决二维问题，考虑线段树套平衡树。先加入所有子弹，然后把平面按 $z$ 从小到大排序，依次匹配在平面内、编号最小的子弹。

具体来说，树套树是这么实现的：线段树在最外层维护 $x$，每个结点上都有平衡树维护 $y$ 和子弹编号。平衡树中每个结点维护子树内的子弹编号最小值。

```cpp
#include <cstdio>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=300010, inf=0x3f3f3f3f;
using namespace std;
mt19937 rnd(time(0));

int n, m, res[N], rt[N<<2], bx[N], nx, by[N], ny;
struct rect
{
	int i, x1, x2, y1, y2, z;
} a[N];
struct point
{
	int i, x, y;
} p[N];
namespace fhq
{
	struct node
	{
		int x; unsigned y; pii a; int l, r;
	} t[N<<5]; int tot;
	int New(pii a)
	{
		return t[++tot]={a.S, rnd(), a}, tot;
	}
	void up(int p)
	{
		t[p].x=t[p].a.S;
		if(t[p].l) t[p].x=min(t[p].x, t[t[p].l].x);
		if(t[p].r) t[p].x=min(t[p].x, t[t[p].r].x);
	}
	void split(int p, pii a, int &x, int &y)
	{
		if(!p) return x=y=0, void();
		if(t[p].a<=a) split(t[p].r, a, t[x=p].r, y);
		else split(t[p].l, a, x, t[y=p].l);
		up(p);
	}
	int merge(int x, int y)
	{
		if(!x || !y) return x|y;
		if(t[x].y<t[y].y) return t[x].r=merge(t[x].r, y), up(x), x;
		return t[y].l=merge(x, t[y].l), up(y), y;
	}
	void insert(int &p, pii a)
	{
		int x, y; split(p, a, x, y);
		p=merge(merge(x, New(a)), y);
	}
	void remove(int &p, pii a)
	{
		int x, y, z; split(p, a, x, z); split(x, pii{a.F, a.S-1}, x, y);
		p=merge(x, z); 
	}
	int query(int p, int l, int r)
	{
		if(!p) return inf;
		int x, y, z; split(p, pii{r, inf}, x, z); split(x, pii{l, 0}, x, y);
		int res=y?t[y].x:inf;
		return merge(merge(x, y), z), res;
	}
}
void modify(int o, int i, int x, int y, int p=1, int l=1, int r=nx)
{
	if(o) fhq::insert(rt[p], pii{y, i});
	else  fhq::remove(rt[p], pii{y, i});
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) modify(o, i, x, y, p<<1, l, mid);
	else modify(o, i, x, y, p<<1|1, mid+1, r);
}
int query(int L, int R, int y1, int y2, int p=1, int l=1, int r=nx)
{
	if(L<=l && r<=R) return fhq::query(rt[p], y1, y2);
	int mid=l+r>>1;
	if(R<=mid) return query(L, R, y1, y2, p<<1, l, mid);
	if(L>mid) return query(L, R, y1, y2, p<<1|1, mid+1, r);
	return min(query(L, R, y1, y2, p<<1, l, mid), query(L, R, y1, y2, p<<1|1, mid+1, r));
}

int main()
{
#ifdef Jerrywang
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d", &n);
	rep(i, 1, n)
	{
		int x1, x2, y1, y2, z; scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &z);
		a[i]={i, x1, x2, y1, y2, z};
		bx[++nx]=x1, bx[++nx]=x2, by[++ny]=y1, by[++ny]=y2;
	}
	scanf("%d", &m);
	rep(i, 1, m)
	{
		int x, y; scanf("%d%d", &x, &y);
		p[i]={i, x, y};
		bx[++nx]=x, by[++ny]=y;
	}
	sort(bx+1, bx+nx+1); nx=unique(bx+1, bx+nx+1)-bx-1;
	sort(by+1, by+ny+1); ny=unique(by+1, by+ny+1)-by-1;
	rep(i, 1, n)
	{
		a[i].x1=lower_bound(bx+1, bx+nx+1, a[i].x1)-bx;
		a[i].x2=lower_bound(bx+1, bx+nx+1, a[i].x2)-bx;
		a[i].y1=lower_bound(by+1, by+ny+1, a[i].y1)-by;
		a[i].y2=lower_bound(by+1, by+ny+1, a[i].y2)-by;
	}
	rep(i, 1, m)
	{
		p[i].x=lower_bound(bx+1, bx+nx+1, p[i].x)-bx;
		p[i].y=lower_bound(by+1, by+ny+1, p[i].y)-by;
		modify(1, i, p[i].x, p[i].y);
	}
	sort(a+1, a+n+1, [](rect a, rect b){return a.z<b.z;});
	rep(i, 1, n)
	{
		int j=query(a[i].x1, a[i].x2, a[i].y1, a[i].y2);
		if(j<inf) res[j]=a[i].i, modify(0, j, p[j].x, p[j].y);
	}
	rep(i, 1, m) printf("%d\n", res[i]);
	
	return 0;
}
```

---

## 作者：Reunite (赞：1)

## 一
---

考虑一步转化题意，把一次射击会击穿哪一块平面等价为一块平面最早被哪一次射击击穿。

显然我们可以把平面按照 $z$ 升序排序，这样高的平面不影响低的平面，无后效性。现在扫描平面序列，考虑一块平面，我们要找到满足：$xl \le x\le xr,yl\le y \le yr$ 且时间编号最小的一个点，然后将其删去。

暴力做是 $O(n^2)$ 的，很劣，二维平面矩形查询，考虑 KD-Tree。

具体地，我们把所有射击点建成一棵 KD-Tree，每次查询二维平面内标号最小的点，然后再给这个点的标号加上一个 $\inf$，即可模拟删除。KD-Tree 的深度是严格 $\log_2n$ 的，因此再记录一个父数组，向上 $pushup$ 即可。

---
## 二
---

复杂度瓶颈在于二维查询，由 KD-Tree 复杂度分析，为 $O(n^{1.5})$，空间线性。

当然这玩意也可以二维平面分块，或者是硬上树套树，但那玩意常数太大。我目前还没想到任何单 $\log$ 做法，如果有人会请私信。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,m,rt;
int g[100005];
struct node{int x1,x2,y1,y2,z,id;};
node a[100005];
int x[100005];
int y[100005];
int d[100005];
int fa[100005];
int lc[100005];
int rc[100005];
int mn1[100005];
int mx1[100005];
int mn2[100005];
int mx2[100005];
int mn[100005];
int pos[100005];
int ans[100005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int build(int l,int r,int dep){
	if(l>r) return 0;
	int mid=(l+r)>>1;
	nth_element(g+l,g+mid,g+1+r,[dep](int a,int b){return dep?x[a]<x[b]:y[a]<y[b];});
	int u=g[mid];
	mn1[u]=mx1[u]=x[u];
	mn2[u]=mx2[u]=y[u];
	mn[u]=d[u],pos[u]=u;
	lc[u]=build(l,mid-1,dep^1);
	rc[u]=build(mid+1,r,dep^1);
	if(lc[u]){
		fa[lc[u]]=u;
		mn1[u]=min(mn1[u],mn1[lc[u]]);
		mx1[u]=max(mx1[u],mx1[lc[u]]);
		mn2[u]=min(mn2[u],mn2[lc[u]]);
		mx2[u]=max(mx2[u],mx2[lc[u]]);
		mn[u]=min(mn[u],mn[lc[u]]);
		if(mn[u]==mn[lc[u]]) pos[u]=pos[lc[u]];
	}
	if(rc[u]){
		fa[rc[u]]=u;
		mn1[u]=min(mn1[u],mn1[rc[u]]);
		mx1[u]=max(mx1[u],mx1[rc[u]]);
		mn2[u]=min(mn2[u],mn2[rc[u]]);
		mx2[u]=max(mx2[u],mx2[rc[u]]);
		mn[u]=min(mn[u],mn[rc[u]]);
		if(mn[u]==mn[rc[u]]) pos[u]=pos[rc[u]];
	}
	return u;
}

inline void pushup(int u){
	mn[u]=d[u];
	pos[u]=u;
	if(lc[u]){
		mn[u]=min(mn[u],mn[lc[u]]);
		if(mn[u]==mn[lc[u]]) pos[u]=pos[lc[u]];
	}
	if(rc[u]){
		mn[u]=min(mn[u],mn[rc[u]]);
		if(mn[u]==mn[rc[u]]) pos[u]=pos[rc[u]];
	}
	return ;
}

inline int query(int u,int l,int r,int L,int R){
	if(!u) return 0;
	if(mx1[u]<l||mn1[u]>r||mx2[u]<L||mn2[u]>R) return 0;
	if(l<=mn1[u]&&mx1[u]<=r&&L<=mn2[u]&&mx2[u]<=R) return pos[u];
	int xx=0;
	if(l<=x[u]&&x[u]<=r&&L<=y[u]&&y[u]<=R) xx=u;
	int x1=query(lc[u],l,r,L,R);
	int x2=query(rc[u],l,r,L,R);
	int dd=min({d[xx],d[x1],d[x2]});
	if(dd==d[xx]) return xx;
	if(dd==d[x1]) return x1;
	if(dd==d[x2]) return x2;
	return 0;
}

inline void updata(int u){
	if(!u) return ;
	d[u]+=1e9;
	while(u){
		pushup(u);
		u=fa[u];
	}
	return ;
}

int main(){
	in(n);
	for(int i=1;i<=n;i++)
		in(a[i].x1),in(a[i].x2),in(a[i].y1),in(a[i].y2),in(a[i].z),a[i].id=i;
	sort(a+1,a+1+n,[](node p,node q){return p.z<q.z;});
	in(m);
	for(int i=1;i<=m;i++)
		in(x[i]),in(y[i]),d[i]=g[i]=i;
	d[0]=1e9;
	rt=build(1,m,0);
	for(int i=1;i<=n;i++){
		int x=query(rt,a[i].x1,a[i].x2,a[i].y1,a[i].y2);
		if(d[x]<=m){
			ans[x]=a[i].id;
			updata(x);
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);

	return 0;
}
```

---

## 作者：Arghariza (赞：1)

$O(n\log^2 n)$ 做法，但是喜提最劣解。

考虑求出每个平面，哪次射击射到了它。我们按照高度从小到大枚举平面，然后依次匹配射击的时间。不难发现这个平面对应的射击时间为 平面范围内尚未被其他平面匹配的射击的发生时间 的最小值。

于是我们相当于在做矩阵求 $\min$ 之后单点修改（去掉被匹配掉的射击）。注意到这个过程是自带强制在线的。

KDT 是好做的，但我不会。

另一个经典的做法是二维线段树（线段树套线段树），时间复杂度 $O(n\log^2 n)$，但空间也是 $O(n\log^2 n)$ 的，寄。

于是我们把内层的线段树换成平衡树，空间就变成 $O(n\log n)$ 的啦。

```cpp
// Problem: Shooting Gallery
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF44G
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define pb pop_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

mt19937 rnd(time(0));
const int inf = 0x3f3f3f3f;
const int N = 1e5 + 100;
const int M = 3e5 + 300;
const int B = 20;

int n, m, cx, cy;
int tx[M], ty[M], ans[N];

struct P { 
	int id, xl, xr, yl, yr, z; 
	P () { }
	P (int _id, int _xl, int _xr, int _yl, int _yr, int _z) :
		id(_id), xl(_xl), xr(_xr), yl(_yl), yr(_yr), z(_z) { }
} a[N];

struct Q {
	int x, y;
	Q () { }
	Q (int _x, int _y) : x(_x), y(_y) { }
} q[N];

struct Seap { // Seg + Treap
	int tot, rt[M << 2];
	struct node { 
		int lc, rc, id, mn; pi vl;
		node () { }
		node (pi _v, int _i) :
			lc(0), rc(0), vl(_v), id(_i), mn(_v.se) { }
	} tr[N * B];
	Seap () : tot(0) { }
	#define ls(x) tr[x].lc
	#define rs(x) tr[x].rc
	int mk(pi v) { return tr[++tot] = node(v, rnd()), tot; }
	void pup(int x) {
		tr[x].mn = tr[x].vl.se;
		if (ls(x)) tr[x].mn = min(tr[x].mn, tr[ls(x)].mn);
		if (rs(x)) tr[x].mn = min(tr[x].mn, tr[rs(x)].mn);
	}
	void spl(int p, pi k, int &x, int &y) {
		if (!p) return x = y = 0, void();
		if (tr[p].vl <= k) x = p, spl(rs(x), k, rs(x), y);
		else y = p, spl(ls(y), k, x, ls(y));
		pup(p);
	}
	int mrg(int x, int y) {
		if (!x || !y) return x | y;
		if (tr[x].id < tr[y].id) return rs(x) = mrg(rs(x), y), pup(x), x;
		else return ls(y) = mrg(x, ls(y)), pup(y), y;
	}
	void ins(int &p, pi v) {
		int x, y;
		spl(p, v, x, y);
		p = mrg(mrg(x, mk(v)), y);
	}
	void del(int &p, pi v) {
		int x, y, z;
		spl(p, mp(v.fi, v.se - 1), x, z), spl(z, v, y, z);
		p = mrg(x, z);
	}
	int que(int p, int l, int r) {
		if (!p) return inf;
		int x, y, z;
		spl(p, mp(r, m + 1), x, z), spl(x, mp(l, 0), x, y);
		int res = y ? tr[y].mn : inf;
		p = mrg(mrg(x, y), z);
		return res;
	}
	#undef ls
	#undef rs
	#define ls x << 1
	#define rs x << 1 | 1
	void upd(int l, int r, int op, int id, int x) {
		if (op) ins(rt[x], mp(q[id].y, id));
		else del(rt[x], mp(q[id].y, id));
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (q[id].x <= mid) upd(l, mid, op, id, ls);
		else upd(mid + 1, r, op, id, rs);
	}
	int qry(int l, int r, int lx, int rx, int ly, int ry, int x) {
		if (lx <= l && r <= rx) return que(rt[x], ly, ry);
		int mid = (l + r) >> 1;
		if (lx > mid) return qry(mid + 1, r, lx, rx, ly, ry, rs);
		if (rx <= mid) return qry(l, mid, lx, rx, ly, ry, ls);
		return min(qry(l, mid, lx, rx, ly, ry, ls), qry(mid + 1, r, lx, rx, ly, ry, rs));
	}
} T;

void solve() {
	cin >> n;
	for (int i = 1, xl, xr, yl, yr, z; i <= n; i++) {
		cin >> xl >> xr >> yl >> yr >> z, a[i] = P(i, xl, xr, yl, yr, z);
		tx[++cx] = xl, tx[++cx] = xr, ty[++cy] = yl, ty[++cy] = yr;
	}
	cin >> m;
	for (int i = 1, x, y; i <= m; i++) 
		cin >> x >> y, q[i] = Q(x, y), tx[++cx] = x, ty[++cy] = y;
	sort(a + 1, a + n + 1, [](P &x, P &y) { return x.z < y.z; });
	sort(tx + 1, tx + cx + 1), cx = unique(tx + 1, tx + cx + 1) - tx - 1;
	sort(ty + 1, ty + cy + 1), cy = unique(ty + 1, ty + cy + 1) - ty - 1;
	for (int i = 1; i <= m; i++) {
		auto &[x, y] = q[i];
		x = lower_bound(tx + 1, tx + cx + 1, x) - tx;
		y = lower_bound(ty + 1, ty + cy + 1, y) - ty;
		T.upd(1, cx, 1, i, 1);
	}
	for (int i = 1; i <= n; i++) {
		auto &[id, xl, xr, yl, yr, z] = a[i];
		xl = lower_bound(tx + 1, tx + cx + 1, xl) - tx;
		xr = lower_bound(tx + 1, tx + cx + 1, xr) - tx;
		yl = lower_bound(ty + 1, ty + cy + 1, yl) - ty;
		yr = lower_bound(ty + 1, ty + cy + 1, yr) - ty;
		int tar = T.qry(1, cx, xl, xr, yl, yr, 1);
		if (tar == inf) continue;
		ans[tar] = id, T.upd(1, cx, 0, tar, 1);
	}
	for (int i = 1; i <= m; i++)
		cout << ans[i] << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：MuYC (赞：1)

萌新刚学 `KD-T`，写了114514年后终于过了这道题。

#### 本题解法

如果考虑用 $m$ 个给定的平面的点去查询能被它删除的矩形显然不优秀（大概三只 $log$ 可以做？）

于是我们考虑转化为用每一个平面来对应 $m$ 个点，因为反正每个点只能被算一次而且每个平面也只能被算一次，所以考虑这样转化。

把 $m$ 个点每个点表示为 $(x,y,t)$ $(t$ 表示这个点被给出的时间，也就是第几次询问$)$

对于给出的 $m$ 个询问点建立 `KD-T`。你需要支持删除某一个点以及维护矩形内的最值。

然后我们把每一个给出的矩形先按照高度从小到大排序，然后依次扫过去，每次把一个矩形覆盖到的询问点中 $t$ 最小的那个，也就是意味着它是第一个把当前矩形删掉的询问点。

并且因为我们的矩形按照高度排序过了，那么就可以知道这个矩阵一定是那个 $t$ 最小的询问点对应的答案，于是我们把 $ans[t]$ 赋值为当前矩形的编号，然后把 $t$ 最小的那个询问点在 `KD-T` 上删除。

删除一个点有一个技巧就是先记录每一个平面上的询问点在 `KD-T` 上对应的编号，然后我们就不用递归去找这个被删除的点了，就直接从下往上更新就完事了。删除也不用真正的删去，将其 $t$ 赋为 $INF$ 这样它就无法对接下来的操作做出贡献了。它怎么也不会成为最小 $t$ 了。

这道题并不需要重构！因为 `KD-T` 的树高是 $\log n$ 级别的，所以删除的时间复杂度为: $O(\log{n})$。结合 `KD-T` 分割平面的性质，矩形查询的复杂度为： $O(\sqrt{m})$ 的。

空间复杂度: $O(n)$，时间复杂度: $O(n \sqrt{m})$

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
const int MAXN = 2e5 + 50, B = 317, INF = 998244353;
int n, m, Ans[MAXN], rt, cnt = 0;
int DY[MAXN], Cl = 0;
struct Point {
    int x, y, id;
} P[MAXN];
struct Ques {
    int X1, Y1, X2, Y2, id, h;
} Q[MAXN];
struct Tree {
    int X, Y, Min, ls, rs, dat, fa;
    int mx[2], my[2];
    void clean() {
        X = Y = ls = rs = mx[1] = my[1] = fa = 0;
        mx[0] = my[0] = dat = Min = INF; 
    }
} T[MAXN];
int MIN(int a, int b) { return a < b ? a : b; }
bool cmp3(Point a, Point b) { return a.y < b.y; }
bool cmp2(Point a, Point b) { return a.x < b.x; }
bool cmp(Ques a, Ques b) { return a.h < b.h; }
void update(int cur) {
    T[cur].Min = MIN(T[T[cur].rs].Min, T[T[cur].ls].Min);
    T[cur].Min = MIN(T[cur].Min, T[cur].dat);
    T[cur].mx[0] = MIN(MIN(T[T[cur].rs].mx[0], T[T[cur].ls].mx[0]), T[cur].mx[0]);
    T[cur].my[0] = MIN(MIN(T[T[cur].rs].my[0], T[T[cur].ls].my[0]), T[cur].my[0]);
    T[cur].mx[1] = max(max(T[T[cur].rs].mx[1], T[T[cur].ls].mx[1]), T[cur].mx[1]);
    T[cur].my[1] = max(max(T[T[cur].rs].my[1], T[T[cur].ls].my[1]), T[cur].my[1]);
}
void build(int &cur, int L, int R, int D, int fa) {
    if(L > R) return ;
    if(!cur) cur = ++ cnt;
    int mid = (L + R) >> 1;
    T[cur].fa = fa;
    if(L == R) {
        int x = P[L].x, y = P[L].y;
        T[cur].mx[0] = T[cur].mx[1] = T[cur].X = x;
        T[cur].my[0] = T[cur].my[1] = T[cur].Y = y;
        T[cur].dat = T[cur].Min = P[L].id; 
        DY[P[L].id] = cur;
        return ;
    }
    if(D == 0) nth_element(P + L, P + mid, P + 1 + R, cmp2);
    else nth_element(P + L, P + mid, P + 1 + R, cmp3);
    T[cur].dat = P[mid].id, T[cur].X = P[mid].x, T[cur].Y = P[mid].y;
    T[cur].mx[0] = T[cur].mx[1] = T[cur].X;
    T[cur].my[0] = T[cur].my[1] = T[cur].Y;
    DY[P[mid].id] = cur;
    build(T[cur].ls, L, mid - 1, D ^ 1, cur);
    build(T[cur].rs, mid + 1, R, D ^ 1, cur); 
    update(cur); return ;
}
bool out(int x, int X1, int Y1, int X2, int Y2) { return (T[x].mx[0] > X2 || T[x].mx[1] < X1 || T[x].my[0] > Y2 || T[x].my[1] < Y1); }
bool in(int x, int X1, int Y1, int X2, int Y2) { return (T[x].mx[0] >= X1 && T[x].mx[1] <= X2 && T[x].my[0] >= Y1 && T[x].my[1] <= Y2); }
int query(int now, int X1, int Y1, int X2, int Y2) {
    int Min = INF;
    if(T[now].X >= X1 && T[now].Y >= Y1 && T[now].X <= X2 && T[now].Y <= Y2) Min = T[now].dat;
    if(out(now, X1, Y1, X2, Y2) || !now) return Min;
    if(in(now, X1, Y1, X2, Y2)) return min(T[now].Min, T[now].dat);
    if(T[now].ls) Min = MIN(Min, query(T[now].ls, X1, Y1, X2, Y2));
    if(T[now].rs) Min = MIN(Min, query(T[now].rs, X1, Y1, X2, Y2));
    return Min;
}
void Go(int x, int t) {
    if(! x) return ;
    if(T[x].dat == t) T[x].dat = INF; 
    update(x); Go(T[x].fa, t);
    return ;
}

int main() {
    n = read(); T[0].clean();
    for(int i = 1 ; i <= n ; i ++) Ans[i] = -1;
    for(int i = 1 ; i <= n ; i ++) {
        Q[i].X1 = read(), Q[i].X2 = read();
        Q[i].Y1 = read(), Q[i].Y2 = read();
        Q[i].h = read(), Q[i].id = i;
    } rt = 0;
    m = read();
    sort(Q + 1, Q + 1 + n, cmp);
    for(int i = 1 ; i <= m ; i ++) {
        P[i].x = read(), P[i].y = read();
        P[i].id = i;
    }
    build(rt, 1, m, 0, 0);
    for(int i = 1 ; i <= n; i ++) {
        int t = query(rt, Q[i].X1, Q[i].Y1, Q[i].X2, Q[i].Y2);
        if(t == 998244353 || !t) continue;
        Ans[t] = Q[i].id, Go(DY[t], t);
    }
    for(int i = 1 ; i <= m ; i ++) printf("%d\n", max(Ans[i], 0));
    return 0;
} // ZHY AK IOI gives me the power
```

---

## 作者：C20203030 (赞：1)

## 一、题目
[点此看题](https://www.luogu.com.cn/problem/CF44G)

**翻译：**

有$n$个靶子，第$i$个靶子在距离射击点$z$的地方，给出靶子的定位，有$m$个射击，按顺序进行，每个射击如果击中靶子会将其击倒，问每个射击会击中哪个靶子，输出靶子的编号（输入顺序）

**数据范围**

$n,m\leq 100000$，$x,y,z\leq10^7$
## 二、解法
我们把射击建$\text{k-d}$树，靶子看作询问，我们先把靶子按$z$排序，然后查询靶子的区域内的顺序最小的射击，这就是$\text{k-d}$树的基操查询了。然后需要删除这个射击，我们找到每个射击在$\text{k-d}$树上的点，把权值改成$inf$，然后一路向祖先方向更新即可。

时间复杂度就是正常$\text{k-d}$树的复杂度，贴个代码$qwq$。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int M = 100005;
const double al = 0.7;
const int inf = 1e9;
int read()
{
    int x=0,flag=1;char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int n,m,k,opt,rt,cnt,ans[M],pos[M],fa[M];
int mi[M][2],mx[M][2],Min[M],ls[M],rs[M];
struct node
{
    int x[2],val;
}a[M],v[M];
struct data
{
    int x1,y1,x2,y2,v,id;
    bool operator < (const data &b) const
    {
        return v<b.v;
    }
}b[M];
void up(int x)
{
    for(int i=0;i<2;i++)
        mi[x][i]=mx[x][i]=v[x].x[i];
    if(ls[x])
        for(int i=0;i<2;i++)
        {
            mx[x][i]=max(mx[x][i],mx[ls[x]][i]);
            mi[x][i]=min(mi[x][i],mi[ls[x]][i]);
        }
    if(rs[x])
        for(int i=0;i<2;i++)
        {
            mx[x][i]=max(mx[x][i],mx[rs[x]][i]);
            mi[x][i]=min(mi[x][i],mi[rs[x]][i]);
        }
    Min[x]=v[x].val;
    if(ls[x]) Min[x]=min(Min[x],Min[ls[x]]);
    if(rs[x]) Min[x]=min(Min[x],Min[rs[x]]);
}
int cmp(node a,node b)
{
    return a.x[opt]<b.x[opt];
}
void build(int &x,int l,int r,int wd)
{
    if(l>r) return ;
    x=++cnt;
    int mid=(l+r)>>1;
    opt=wd;
    nth_element(a+l,a+mid,a+r+1,cmp);
    v[x]=a[mid];pos[v[x].val]=x;
    build(ls[x],l,mid-1,wd^1);
    build(rs[x],mid+1,r,wd^1);
    fa[ls[x]]=fa[rs[x]]=x;
    up(x);
}
int in(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    return x1<=x3 && x4<=x2 && y1<=y3 && y4<=y2;
}
int out(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
    return x1>x4 || x2<x3 || y1>y4 || y2<y3;
}
int ask(int x,int x1,int y1,int x2,int y2)
{
    if(!x) return inf;
    if(in(x1,y1,x2,y2,mi[x][0],mi[x][1],mx[x][0],mx[x][1]))
        return Min[x];
    if(out(x1,y1,x2,y2,mi[x][0],mi[x][1],mx[x][0],mx[x][1]))
        return inf;
    int r=inf;
    if(in(x1,y1,x2,y2,v[x].x[0],v[x].x[1],v[x].x[0],v[x].x[1]))
        r=v[x].val;
    r=min(r,ask(ls[x],x1,y1,x2,y2));
    r=min(r,ask(rs[x],x1,y1,x2,y2));
    return r;
}
void del(int x)
{
    v[x].val=inf;
    while(x)
    {
        up(x);
        x=fa[x];
    }
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        int x=read(),y=read(),c=read(),d=read(),z=read();
        b[i]=data{x,c,y,d,z,i};
    }
    sort(b+1,b+1+n);
    m=read();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        a[i]=node{x,y,i};
    }
    build(rt,1,m,0);
    for(int i=1;i<=n;i++)
    {
        int t=ask(rt,b[i].x1,b[i].y1,b[i].x2,b[i].y2);
        if(t==inf) continue;
        int x=pos[t];
        ans[t]=b[i].id;
        del(x);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
}

```



---

## 作者：OtterZ (赞：0)

# 题意
给定 $n$ 个水平平面，平面有高度 $z$，不存在两个高度相同的平面，每次删掉包含点 $(x,y)$，且高度最小的平面，问删除的平面编号。
# 解法
由于题目涉及二维平面问题，考虑使用 `2d-tree` 处理，但 `2d-tree` 适合查询平面包含的点，而不是包含点的平面。考虑到 $z$ 较小的平面会被优先删除，于是我们充分发扬人类智慧，用 `2d-tree` 存操作点（即删除操作给定的点），将平面按 $z$ 升序排序处理，处理时找到平面包含的最先操作的操作点，将此点对应操作删除的平面记录为此平面，并删掉此操作点。

我们对所有操作点建 `2d-tree`，删除操作点时删点会比较麻烦，其实打 `tag` 即可。

这样做时间复杂度 $\operatorname{O}(n\sqrt n)$。

~~没错，就是这么简单。~~
# 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100009,M = 100009;
struct tar{
	int xmn,xmx,ymx,ymn,z,id;
	bool operator<(const tar &b)const{
		return z < b.z;
	} 
}t[N];
int sid[M];
struct kdtree{
	int x,y,xmn = 0x3f3f3f3f,ymn = 0x3f3f3f3f,xmx = -1,ymx = -1,t = 0x3f3f3f3f,mid;
	int lc,rc;
	bool dt;
}nd[M];
bool cmp1(kdtree tx,kdtree ty){
	return tx.x < ty.x;
}
bool cmp2(kdtree tx,kdtree ty){
	return tx.y < ty.y;
}
int build(int l,int r,int k){
	if(l > r)
		return 0;
	if(l == r){
		nd[l].xmn = nd[l].x;
		nd[l].ymn = nd[l].y;
		nd[l].xmx = nd[l].x;
		nd[l].ymx = nd[l].y;
		nd[l].mid = l;
		return l;
	}
	int u = (l + r) >> 1;
	nth_element(nd + l,nd + u,nd + r + 1,k == 0 ? cmp1 : cmp2);
	//printf(" %d %d\n",l,r); 
	nd[u].lc = build(l,u - 1,k ^ 1);
	nd[u].rc = build(u + 1,r,k ^ 1);
	//printf("%d %d\n",nd[u].x,nd[u].y);
	nd[u].xmn = min(nd[u].x,min(nd[nd[u].lc].xmn,nd[nd[u].rc].xmn));
	nd[u].ymn = min(nd[u].y,min(nd[nd[u].lc].ymn,nd[nd[u].rc].ymn));
	nd[u].xmx = max(nd[u].x,max(nd[nd[u].lc].xmx,nd[nd[u].rc].xmx));
	nd[u].ymx = max(nd[u].y,max(nd[nd[u].lc].ymx,nd[nd[u].rc].ymx));
	nd[u].mid = u;
	if(nd[nd[u].mid].t > nd[nd[nd[u].lc].mid].t)
		nd[u].mid = nd[nd[u].lc].mid;
	if(nd[nd[u].mid].t > nd[nd[nd[u].rc].mid].t)
		nd[u].mid = nd[nd[u].rc].mid;
	//printf("%d %d %d %d\n",nd[u].xmn,nd[u].ymn,nd[u].xmx,nd[u].ymx);
	return u;
}
void kill(int k,int px,int py,int pt){
	if(nd[k].xmn > px || nd[k].xmx < px || nd[k].ymn > py || nd[k].ymx < py)
		return;
	if(nd[k].x == px && nd[k].y == py && nd[k].t == pt){
		nd[k].dt = true;
		nd[k].x = 0x3f3f3f3f,nd[k].y = 0x3f3f3f3f,nd[k].t = 0x3f3f3f3f;
		nd[k].xmn = min(nd[k].dt ? 0x3f3f3f3f : nd[k].x,min(nd[nd[k].lc].xmn,nd[nd[k].rc].xmn));
		nd[k].ymn = min(nd[k].dt ? 0x3f3f3f3f : nd[k].y,min(nd[nd[k].lc].ymn,nd[nd[k].rc].ymn));
		nd[k].xmx = max(nd[k].dt ? -1 : nd[k].x,max(nd[nd[k].lc].xmx,nd[nd[k].rc].xmx));
		nd[k].ymx = max(nd[k].dt ? -1 : nd[k].y,max(nd[nd[k].lc].ymx,nd[nd[k].rc].ymx));
		nd[k].mid = 0;
		if(nd[nd[k].mid].t > nd[nd[nd[k].lc].mid].t)
			nd[k].mid = nd[nd[k].lc].mid;
		if(nd[nd[k].mid].t > nd[nd[nd[k].rc].mid].t)
			nd[k].mid = nd[nd[k].rc].mid;
		return;
	}
	kill(nd[k].lc,px,py,pt);
	kill(nd[k].rc,px,py,pt);
	nd[k].xmn = min(nd[k].dt ? 0x3f3f3f3f : nd[k].x,min(nd[nd[k].lc].xmn,nd[nd[k].rc].xmn));
	nd[k].ymn = min(nd[k].dt ? 0x3f3f3f3f : nd[k].y,min(nd[nd[k].lc].ymn,nd[nd[k].rc].ymn));
	nd[k].xmx = max(nd[k].dt ? 0 : nd[k].x,max(nd[nd[k].lc].xmx,nd[nd[k].rc].xmx));
	nd[k].ymx = max(nd[k].dt ? 0 : nd[k].y,max(nd[nd[k].lc].ymx,nd[nd[k].rc].ymx));
	nd[k].mid = k;
	if(nd[nd[k].mid].t > nd[nd[nd[k].lc].mid].t)
		nd[k].mid = nd[nd[k].lc].mid;
	if(nd[nd[k].mid].t > nd[nd[nd[k].rc].mid].t)
		nd[k].mid = nd[nd[k].rc].mid;
	return;
}
int kid;
void fnd(int k,int qs){
	//printf("%d %d %d %d %d %d %d %d\n",t[qs].xmn,t[qs].ymn,t[qs].xmx,t[qs].ymx,nd[k].xmn,nd[k].ymn,nd[k].xmx,nd[k].ymx);
	if(t[qs].xmn > nd[k].xmx || t[qs].xmx < nd[k].xmn || t[qs].ymn > nd[k].ymx || t[qs].ymx < nd[k].ymn || nd[k].mid == 0)
		return;
	if(t[qs].xmx >= nd[k].xmx && t[qs].xmn <= nd[k].xmn && t[qs].ymx >= nd[k].ymx && t[qs].ymn <= nd[k].ymn){
		if(nd[kid].t > nd[nd[k].mid].t)
			kid = nd[k].mid;
		return;
	}
	else if(t[qs].xmx >= nd[k].x && t[qs].xmn <= nd[k].x && t[qs].ymx >= nd[k].y && t[qs].ymn <= nd[k].y){
		if(nd[kid].t > nd[k].t)
			kid = k;
	}
	fnd(nd[k].lc,qs);
	fnd(nd[k].rc,qs);
}
int n,m;
int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++){
		scanf("%d %d %d %d %d",&t[i].xmn,&t[i].xmx,&t[i].ymn,&t[i].ymx,&t[i].z);
		t[i].id = i;
	}
	sort(t + 1,t + n + 1);
	scanf("%d",&m);
	for(int i = 1; i <= m; i ++){
		scanf("%d %d",&nd[i].x,&nd[i].y);
		nd[i].t = i;
	}
	int rt = build(1,m,0);
	for(int i = 1; i <= n; i ++){
		kid = 0;
		fnd(rt,i);
		//printf("%d\n",nd[kid].t);
		if(kid != 0){
			sid[nd[kid].t] = t[i].id;
			kill(rt,nd[kid].x,nd[kid].y,nd[kid].t);
		}
	}
	for(int i = 1; i <= m; i ++)
		printf("%d\n",sid[i]);
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

有人不会写 K-D Tree。

-----

考虑让靶子找子弹。

把所有子弹建立出 K-D Tree，在上面搜索。

按 $z$ 从小到大加入平面，将能覆盖的最小的子弹删去即可。

在 K-D Tree 上记录父节点，删点的时候暴力往上跳。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,INF=1e9;
int n,m,ans[MAXN],fa[MAXN],rev[MAXN];
struct Node {
	int x,y,id,lson,rson,flg;
	int xmn,xmx,ymn,ymx,idmn;
}t[MAXN];
int xl[MAXN],xr[MAXN],yl[MAXN],yr[MAXN],z[MAXN];
vector<pair<int,int>> pl;
void push_up(int u) {
	fa[t[u].lson]=fa[t[u].rson]=u;
	if(t[u].flg) t[u].xmn=INF,t[u].xmx=-INF,t[u].ymn=INF,t[u].ymx=-INF,t[u].idmn=m+1;
	else t[u].xmn=t[u].xmx=t[u].x,t[u].ymn=t[u].ymx=t[u].y,t[u].idmn=t[u].id;
	if(t[u].lson) t[u].xmn=min(t[u].xmn,t[t[u].lson].xmn),t[u].xmx=max(t[u].xmx,t[t[u].lson].xmx),t[u].ymn=min(t[u].ymn,t[t[u].lson].ymn),t[u].ymx=max(t[u].ymx,t[t[u].lson].ymx),t[u].idmn=min(t[u].idmn,t[t[u].lson].idmn);
	if(t[u].rson) t[u].xmn=min(t[u].xmn,t[t[u].rson].xmn),t[u].xmx=max(t[u].xmx,t[t[u].rson].xmx),t[u].ymn=min(t[u].ymn,t[t[u].rson].ymn),t[u].ymx=max(t[u].ymx,t[t[u].rson].ymx),t[u].idmn=min(t[u].idmn,t[t[u].rson].idmn);
	return ;
}
int build(int l,int r,int op) {
	if(l>r) return 0;
	if(l==r) return t[l].xmn=t[l].xmx=t[l].x,t[l].ymn=t[l].ymx=t[l].y,t[l].idmn=t[l].id,l;
	int mid=l+r>>1;
	if(op==0) nth_element(t+l,t+mid,t+r+1,[](Node A,Node B) {return A.x<B.x;});
	else nth_element(t+l,t+mid,t+r+1,[](Node A,Node B) {return A.y<B.y;});
	t[mid].lson=build(l,mid-1,op^1),t[mid].rson=build(mid+1,r,op^1);
	return push_up(mid),mid;
}
int query(int u,int xl,int xr,int yl,int yr) {
	if(!u) return m+1;
	if(xr<t[u].xmn||xl>t[u].xmx||yr<t[u].ymn||yl>t[u].ymx) return m+1;
	if(xl<=t[u].xmn&&t[u].xmx<=xr&&yl<=t[u].ymn&&t[u].ymx<=yr) return t[u].idmn;
	int ans=m+1;
	if(!t[u].flg&&xl<=t[u].x&&t[u].x<=xr&&yl<=t[u].y&&t[u].y<=yr) ans=t[u].id;
	ans=min(ans,query(t[u].lson,xl,xr,yl,yr)),ans=min(ans,query(t[u].rson,xl,xr,yl,yr));
	return ans;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>xl[i]>>xr[i]>>yl[i]>>yr[i]>>z[i],pl.push_back({z[i],i});
	sort(pl.begin(),pl.end());
	cin>>m;
	ffor(i,1,m) cin>>t[i].x>>t[i].y,t[i].id=i;
	int rt=build(1,m,0);
	ffor(i,1,m) rev[t[i].id]=i;
	for(auto pr:pl) {
		int id=pr.second,cs=query(rt,xl[id],xr[id],yl[id],yr[id]);
		if(cs==m+1) continue ;
		ans[cs]=id,cs=rev[cs],t[cs].flg=1;
		while(cs) push_up(cs),cs=fa[cs];
	}
	ffor(i,1,m) cout<<ans[i]<<'\n';
	return 0;
}
```

---

