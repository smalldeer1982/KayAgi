# [USACO14MAR] The Lazy Cow G

## 题目描述

```
  Bessie的田里有N(1<=N<=100,000)块草地，每块草地的坐标是 (xi, yi) (0<=xi,yi<=1,000,000),上面长着gi(1<=gi<=10,000)个单位的牧草。 
  Bessie可以向东南西北方向走，一次走一步（一个单位长度）。如她从（0,0）走到（3,2）需要5步。她最多可以一次走k (1<=k<=2,000,000) 步。
  现在她想找一个位置，使她从该位置出发可以得到最多单位的牧草(她可以走多次，但每次都从该位置出发)。

## 样例 #1

### 输入

```
4 3
7 8 6
3 0 0
4 6 0
1 4 2```

### 输出

```
8```

# 题解

## 作者：cccgift (赞：6)

## 看到本题没有题解，于是来发一篇。

本题的题意是在平面上找到一个点，使距离这个点的曼哈顿距离不超过$k$的牧草数最大化。

我们把曼哈顿距离不超过$k$的图像画出来，发现它长这样：

![](https://cdn.luogu.com.cn/upload/pic/61759.png)

看着特别不爽，根本不好处理。

但是，如果我们能够让它长这样：

![](https://cdn.luogu.com.cn/upload/pic/61760.png)

那么，就可以使用扫描线来维护，从而做到$O(nlogn)$了。

我们把这两个图联系一下，看过[洛谷日报#182 常用距离算法详解](https://www.luogu.org/blog/xuxing/Distance-Algorithm)的都应该发现，这不就是曼哈顿距离转切比雪夫距离吗？

于是，我们就可以把坐标$(x,y)$读入后，令它新的坐标$(X,Y)$为$(x+y,x-y)$，问题就转化成了[P1502 窗口的星星](https://www.luogu.org/problemnew/show/P1502)了。

当然，还有一些细节处理：

1、最好把新的坐标离散化，因为$x-y$可能是负数。

2、我们可以发现，转化后的正方形的边长是$2k$的，处理时要小心。

#### 3、注意！如果有高度相同的两条边，一定要先处理下边（也就是加进去的边），因为如果有这种情况，同时在这两条边上的点的答案会被记录到两条边中，但是如果先处理上边，就只会被记录到一条边中，导致答案出错！~~这样，我们会得到样例没过却有81分的好成绩。~~

Update：原来代码的读入压行了，这里把它展开。

### 代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
using namespace std;
#define res register int
//#define cccgift
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++) //fread优化
char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T>
    inline void read(T &x) //快读
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T>
    inline T max(T x,T y) {return x<y?y:x;}
    template<typename T>
    inline T min(T x,T y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,T y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,T y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::chkmax;
struct node{
    int x,y,z,k;
    bool operator <(const node &b)const {return x<b.x||(x==b.x&&k>b.k);} //先处理下边！
} a[200001];
int tot,dat[800001],ad[800001],len,b[200001],n,m,w,h,nn,t,xx,yy,k;
inline void spread(int q) {
    if(ad[q]) {
        ad[q<<1]+=ad[q],ad[q<<1|1]+=ad[q];
        dat[q<<1]+=ad[q],dat[q<<1|1]+=ad[q];
        ad[q]=0;
    }
}
void change(int q,int l1,int r1,int l,int r,int k) {
    if(r<l1||r1<l) return;
    if(l<=l1&&r1<=r) {dat[q]+=k,ad[q]+=k;return;}
    int mid=l1+r1>>1;spread(q);
    change(q<<1,l1,mid,l,r,k),change(q<<1|1,mid+1,r1,l,r,k),dat[q]=wode::max(dat[q<<1],dat[q<<1|1]);
}
int main()
{
    read(n),read(k),k<<=1;
    for(res i=1;i<=n;++i) {
    	read(a[++len].k),read(xx),read(yy);
		a[len].x=xx+yy,a[len].y=xx-yy;
		b[len]=a[len].y;
		++len,a[len].x=a[len-1].x+k,a[len].y=a[len-1].y;
		b[len]=a[len].z=a[len-1].z=a[len-1].y+k;
		a[len].k=-a[len-1].k;
	}
//	for(res i=1;i<=len;++i) printf("%d %d %d %d\n",a[i].k,a[i].x,a[i].y,a[i].z);
    sort(b+1,b+1+len),nn=unique(b+1,b+1+len)-b-1;
//	for(res i=1;i<=nn;++i) printf("%d ",b[i]);puts("");
    for(res i=1;i<=len;++i) a[i].y=lower_bound(b+1,b+1+nn,a[i].y)-b,a[i].z=lower_bound(b+1,b+1+nn,a[i].z)-b; //把坐标离散化
//	for(res i=1;i<=len;++i) printf("%d %d\n",a[i].y,a[i].z);
    sort(a+1,a+1+len);
    for(res i=1;i<=len;++i) change(1,1,nn,a[i].y,a[i].z,a[i].k),chkmax(tot,dat[1]); //最后的答案就是每一次扫描的最大值，详见窗口的星星那道题。
    printf("%d\n",tot);
    return 0;
}
```

---

## 作者：_zhy (赞：4)

[Link](https://www.luogu.com.cn/problem/P4876)。

~~好像没有人像我这样做~~

曼哈顿距离小于 $k$ 的点可以去。

所以很容易想到每一个点可以去的范围为一个正方形：

![](https://cdn.luogu.com.cn/upload/image_hosting/2irz29kw.png)

但很不辛，这个正方形是斜着的，我们很难处理，所以考虑将坐标系旋转一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/oxacgfyg.png)

于是这道题就变成里一道~~简单的~~扫描线的题了，和[窗口的星星](https://www.luogu.com.cn/problem/P1502)一样。

但这个时候有一个难点，那就是如何把这个正方形的每个点在新坐标系中找到。

这个时候重新看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/alcsmm98.png)

由于 $BH$ 和 $HD$ 都等于 $k$，$\angle BHC$ 又是直角，所以 $\triangle BHD$ 是等腰直。并且 $BH // x$，$DH // y$，$AB // y'$，$CD // x'$（$x, y, x', y'$ 分别是两个坐标系的坐标轴）。

所以我们就知道了新坐标系的 $x$ 和 $y$ 轴与原来坐标系的 $x$ 轴的夹角为 $45^\circ$，也就是说新坐标系的 $x$ 轴在原来坐标系中是直线 $y=-x$，新坐标系的 $y$ 轴在原来坐标系中是直线 $y=x$。

那这和求坐标有什么关系呢？

我们想一下，一个点的 $x$ 坐标的绝对值是不是此点到 $y$ 轴的距离，$y$ 坐标是到 $x$ 坐标的距离。

现在我们又知道正方形每个点的坐标以及新坐标轴在原来坐标轴的解析式，是不是距离就求得到了呢？

很显然是的，这是我们只需用到点到直线的距离公式即可：$\dfrac{|k \times m - n + b|}{\sqrt{1 + k^2}}$（$k$ 为直线解析式中 $x$ 的系数，$b$ 为直线解析式中加的那个常数，$m, n$ 就是一个点的坐标）。

所以这道题我们就可以求到正方形每个顶点与新坐标系的坐标轴的距离了，那怎么确定坐标的正负呢。

由于 $x$ 和坐标和 $y$ 坐标不同，我们分开讨论。

先看 $x$ 坐标：

![](https://cdn.luogu.com.cn/upload/image_hosting/y5iebipn.png)

由于 $y$ 轴是原来坐标系中的 $y = x$，所以只要点在这条直线右下方就相当于在新坐标系的一或四象限，就像图中的这些点一样。

那跟容易看出它们都满足 $y<x$。这时 $x$ 坐标就是 $\dfrac{|m - n|}{\sqrt{1 + 1}}$。（把 $y=x$ 带进去）。

所以如果 $y>x$ 就在二或三象限，$x$ 坐标就是 $-\dfrac{|m - n|}{\sqrt{1 + 1}}$。（把 $y=x$ 带进去，因为在二或三象限，所以取负数）。

现在看 $y$ 坐标：

![](https://cdn.luogu.com.cn/upload/image_hosting/pufsnbnj.png)

看得出来在此直线右上方 $y$ 就是正的，如图中的点。可以看出 $y > -x$时， $y$ 坐标就是 $\dfrac{|-m - n|}{\sqrt{1 + 1}}$。（把 $y=-x$ 带进去）。

同理，$y < -x$时， $y$ 坐标就是 $-\dfrac{|-m - n|}{\sqrt{1 + 1}}$。（把 $y=-x$ 带进去）。

万一在坐标轴上随便，反正都是 $0$。

坐标求到了，我们就开开心心地扫描线吧。

### code

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long

using namespace std;

const int N = 1e6 + 5;

int n, ans;
double xx[N << 1], k;
struct node {
	double l, r, h;
	int x;
	inline node() { l = r = h = 0.0, x = 0; }
	inline node(double L, double R, double H, int X) { l = L, r = R, h = H, x = X; }
	inline bool operator<(node X) const { return h != X.h ? h < X.h : x > X.x; }
} a[N << 1];
struct Segment_Tree {
	int l, r, tag, sum;
} t[N << 2];

inline int ls(int i) { return i << 1; }

inline int rs(int i) { return i << 1 | 1; }

inline void push_up(int i) { t[i].sum = max(t[ls(i)].sum, t[rs(i)].sum); }

inline void push_down(int i) {
	t[ls(i)].sum += t[i].tag, t[rs(i)].sum += t[i].tag;
	t[ls(i)].tag += t[i].tag, t[rs(i)].tag += t[i].tag;
	t[i].tag = 0;
}

inline void build(int i, int l, int r) {
	t[i].l = l, t[i].r = r;
	if (l == r)
		return ;
	int mid = l + r >> 1;
	build(ls(i), l, mid);
	build(rs(i), mid + 1, r);
}

inline void update(int i, int l, int r, int x) {
	if (l <= t[i].l && r >= t[i].r) {
		t[i].sum += x, t[i].tag += x;
		return ;
	}
	push_down(i);
	if (l <= t[ls(i)].r)
		update(ls(i), l, r, x);
	if (r >= t[rs(i)].l)
		update(rs(i), l, r, x);
	push_up(i);
}
//线段树维护扫描线。 

signed main() {
	scanf("%lld %lf", &n, &k);
	for (int i = 1, v; i <= n; i++) {
		double X, Y, nx, ny, x_1, x_2, y_1, y_3;
		scanf("%lld %lf %lf", &v, &X, &Y);
		nx = X - k, ny = Y;	//正方形点的坐标（这个是左边那个）。 
		x_1 = fabs(nx - ny) / sqrt(2) * (ny <= nx ? 1.0 : -1.0);	//按照刚才的方法求坐标。 
		y_1 = fabs(-nx - ny) / sqrt(2) * (ny >= -nx ? 1.0 : -1.0);
		nx = X, ny = Y - k; //正方形点的坐标（中间下面那个）。 
		x_2 = fabs(nx - ny) / sqrt(2) * (ny <= nx ? 1.0 : -1.0);
		nx = X + k, ny = Y;	////正方形点的坐标（这个是右边那个）。 
		y_3 = fabs(-nx - ny) / sqrt(2) * (ny >= -nx ? 1.0 : -1.0);
		//因为是正方形，所以我们只需要求2个不同的x坐标和2个不同的y坐标即可。 
		xx[i << 1] = x_1, xx[(i << 1) - 1] = x_2;	//把每个x坐标存起来。 
		a[i << 1] = node(x_1, x_2, y_1, v);	//存正方形上下两条线段。 
		a[(i << 1) - 1] = node(x_1, x_2, y_3, -v);
	}
	n <<= 1;
	sort(a + 1, a + n + 1);	 
	sort(xx + 1, xx + n + 1);
	//排序，方便处理。 
	int orz = unique(xx + 1, xx + n + 1) - xx - 1;
	//离散化，防止同一个x出现多次。 
	build(1, 1, orz);
	//建树。 
	for (int i = 1, l, r; i <= n; i++) {
		l = lower_bound(xx + 1, xx + orz + 1, a[i].l) - xx;	
		r = lower_bound(xx + 1, xx + orz + 1, a[i].r) - xx;
		//由于x是double所以离散化。 
		update(1, l, r, a[i].x);
		ans = max(ans, t[1].sum);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：lottle1212__ (赞：3)

# [The Lazy Cow G](https://www.luogu.com.cn/problem/P4876)

平面上有若干点，要求在平面上任意地选出一个位置，使得到该点曼哈顿距离不超过 $k$ 的点的数量最多。

首先题目要求的是曼哈顿距离。如果把对于一个位置曼哈顿距离不超过 $k$ 的位置都标记出来，会发现是一个正方形旋转了 $45^\circ$。而对于这个图形，正方形是容易处理的，而旋转 $45^\circ$ 不好操作，可以考虑将曼哈顿距离转换成切比雪夫距离，此处略微讲讲两距离及其转换。

曼哈顿距离：$|x_i-x_j|+|y_i-y_j|$。

切比雪夫距离：$\max\{|x_i-x_j|, |y_i-y_j|\}$。

可以发现，切比雪夫距离不超过 $k$ 的图形就是一个边与 $x$ 轴或 $y$ 轴分别平行的一个正方形。

而对于曼哈顿距离，$|x_i-x_j|+|y_i-y_j|=\max\{x_i-x_j, x_j-x_i\}+\max\{y_i-y_j, y_j-y_i\}=\max\{x_i-x_j+y_i-y_j, x_i-x_j+y_j-y_i, x_j-x_i+y_i-y_j, x_j-x_i+y_j-y_i\}=\max\{(x_i+y_i)-(x_j+y_j), (x_i-y_i)-(x_j-y_j), (x_j-y_j)-(x_i-y_i), (x_j+y_j)-(x_i+y_i)\}=\max\{|(x_i+y_i)-(x_j+y_j)|,|(x_i-y_i)-(x_j-y_j)|\}$，则令 $x'_i=x_i+y_i, y'_i=x_i-y_i$，则上式等于 $\max\{|x'_i-x'_j|, |y'_i-y'_j|\}$。这样就完成了曼哈顿距离与切比雪夫距离的转换。

实际操作时，只需要先转换坐标，再按切比雪夫距离的求法做即可。

转换后，所求变为在平面上一个 $2k\times2k$ 的矩形最多能覆盖的点数，这个用扫描线解决即可。

Code

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define fst first
#define scd second
#define db double
#define ll long long
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector <int>
#define pii pair <int, int>
#define sz(x) ((int)x.size())
#define ms(f, x) memset(f, x, sizeof(f))
#define L(i, j, k) for (int i=(j); i<=(k); ++i)
#define R(i, j, k) for (int i=(j); i>=(k); --i)
#define ACN(i, H_u) for (int i=H_u; i; i=E[i].nxt)
using namespace std;
template <typename INT> void rd(INT &res) {
	res=0; bool f=false; char ch=getchar();
	while (ch<'0'||ch>'9') f|=ch=='-', ch=getchar();
	while (ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^48), ch=getchar();
	res=(f?-res:res);
}
template <typename INT, typename...Args>
void rd(INT &x, Args &...y) { rd(x), rd(y...); }
//dfs
const int inf=0x3f3f3f3f;
const int maxn=1e5;
const int N=maxn+10;
int n, kv, d[N], dcnt;
//wmr
#define ls (p<<1)
#define rs (p<<1|1)
struct SegmentTree { int l, r; ll ma, add; } t[N<<2];
void pushdown(int p) {
	t[ls].ma+=t[p].add;
	t[rs].ma+=t[p].add;
	t[ls].add+=t[p].add;
	t[rs].add+=t[p].add;
	t[p].add=0;
}
void pushup(int p) { t[p].ma=max(t[ls].ma, t[rs].ma); }
void build(int p, int l, int r) {
	t[p]={l, r, 0, 0};
	if (l==r) return;
	int mid=l+r>>1;
	build(ls, l, mid); build(rs, mid+1, r);
}
void update(int p, int l, int r, int k) {
	if (l<=t[p].l&&t[p].r<=r) return t[p].ma+=k, t[p].add+=k, void();
	int mid=t[p].l+t[p].r>>1; pushdown(p);
	if (l<=mid) update(ls, l, r, k);
	if (mid<r) update(rs, l, r, k);
	pushup(p);
}
ll query(int p, int l, int r) {
	if (l<=t[p].l&&t[p].r<=r) return t[p].ma;
	int mid=t[p].l+t[p].r>>1; pushdown(p); ll res=0;
	if (l<=mid) res=max(res, query(ls, l, r));
	if (mid<r) res=max(res, query(rs, l, r));
	return res;
}
struct node {
	int x, y, v;
	bool operator < (const node &k) const { return x<=k.x||x==k.x&&y<k.y; }
} a[N];
//incra

//lottle
signed main() {
//	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	rd(n, kv); kv<<=1;
	L(i, 1, n) {
		int v, x, y; rd(v, x, y);
		a[i].x=x+y, a[i].y=x-y, a[i].v=v; d[i]=a[i].y;
	}
	sort(a+1, a+n+1); sort(d+1, d+n+1); dcnt=unique(d+1, d+n+1)-d-1;
	L(i, 1, n) a[i].y=lower_bound(d+1, d+dcnt+1, a[i].y)-d;
	a[n+1].x=inf; int lst=0, cur=0; ll ans=0;
	build(1, 1, dcnt);
	L(i, 1, n) if (a[i].x!=a[i+1].x) {
		while (cur<n&&a[cur+1].x-a[i].x<=kv) ++cur, update(1, lower_bound(d+1, d+dcnt+1, d[a[cur].y]-kv)-d, a[cur].y, a[cur].v);
		ans=max(ans, t[1].ma);
		L(j, lst+1, i) update(1, lower_bound(d+1, d+dcnt+1, d[a[j].y]-kv)-d, a[j].y, -a[j].v);
		lst=i;
	}
	printf("%lld\n", ans);
	return 0;
}
/*
input
4 3
7 8 6
3 0 0
4 6 0
1 4 2
output
8
*/
```

---

## 作者：_Diu_ (赞：2)

题目传送门：[P4876 \[USACO14MAR\]The Lazy Cow G](https://www.luogu.com.cn/problem/P4876)

### ~~前言：这里，我们亲切地称Bessie为某茜~~

# 正方形

我们可以知道，这里的$k$步就是某茜走的路程和

而且某茜只能走**水平或竖直方向的**

所以也就是说

每一个距离某茜的**哈曼顿距离**不超过$k$

所以我们就有了这样的一个某茜地图

![](https://cdn.luogu.com.cn/upload/image_hosting/4vv8ovkb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

某茜发现这个地图真的太丑了

~~所以她学会了歪脖子~~

于是，这个地图变成了这样

![](https://cdn.luogu.com.cn/upload/image_hosting/kgr9y638.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那我们怎么帮助某茜把她的脖子歪过来呢？

~~遇到问题，打一顿就行，实在不行打两顿~~

那就是看[某古日报](https://www.luogu.com.cn/blog/xuxing/Distance-Algorithm)

我们可以把原地图$(x,y)$的点转到歪脖后的地图$(x+y,x-y)$的点

# 扫描线

### 对，没错，接下来就是[P1502 窗口的星星](https://www.luogu.com.cn/problem/P1502)

接下来，我们的某茜就想到了扫描线

对于每一块新食物$(X,Y)$，我们可以有一个矩形$(X+k,Y+k)$，如果某茜站在这里面的任意一点，那么就能走到这一块草地

我们就可以用扫描线从左往右扫一遍

求区间最大值就可以了

# code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (o<<1)
#define rs (o<<1|1)
using namespace std;
const int N=2e5+10;
int n,t[N*4],ans,xa,ya,l,k;
struct cxk{
	int x,y1,y2,id;
	//id为负表示右，正表示左 
	bool operator<(const cxk &hs)const{
		if(x!=hs.x)return x<hs.x;
		return id>hs.id;
	}
}a[N*2],q[N*2];
struct trees{
	int mx,sum;
	//mx是最大值，也就是所求的 
	//sum是和，也就是所有 
}tree[N*8];
void pushdown(int o){
	tree[ls].mx+=tree[o].sum;
	tree[rs].mx+=tree[o].sum;
	tree[ls].sum+=tree[o].sum;
	tree[rs].sum+=tree[o].sum;
	tree[o].sum=0;
}
//每一个叶子节点[i,i]表示离散后的[i,i+1]这一条线段 
//用区间修改区间查询来维护 
void update(int o,int l,int r,int x,int y,int c){
	if(r<x||y<l)return;
	if(x<=l&&r<=y){
		tree[o].mx+=c;
		tree[o].sum+=c;
		return;
	}
	pushdown(o);
	int mid=(l+r)/2;
	update(ls,l,mid,x,y,c);
	update(rs,mid+1,r,x,y,c);
	tree[o].mx=max(tree[ls].mx,tree[rs].mx);
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&l,&xa,&ya);
		xa+=ya;
		ya=xa-ya*2;
		int xb=xa+2*k;
		int yb=ya+2*k;
		a[i*2-1]={xa,ya,yb,l};
		a[i*2]={xb,ya,yb,-l};
		t[i*2-1]=ya;
		t[i*2]=yb;
	}
	sort(a+1,a+n*2+1);
	sort(t+1,t+n*2+1);
	int low=unique(t+1,t+n*2+1)-t;
	for(int i=1;i<n*2;i++){
		int ya=lower_bound(t+1,t+low,a[i].y1)-t;
		int yb=lower_bound(t+1,t+low,a[i].y2)-t;
		update(1,1,low-1,ya-1,yb-1,a[i].id);
		ans=max(ans,tree[1].mx);
//		printf("%lld\n",tree[1].sum);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Dreamunk (赞：1)

[题目](https://www.luogu.org/problem/P4876)

题意：平面上有 $n$ 块草地，第 $i$ 块草地坐标为 $(x_i,y_i)$ ，上面有 $g_i$ 个单位的草。Bessie 可以吃到距离起始点不超过 $k$（这里是曼哈顿距离）的所有草。帮 Bessie 选定起始点使它能吃到最多的草。

看到曼哈顿距离，先转 $45$ 度。这样 Bessie 吃的就是一个平行于坐标轴的正方形里的草。

我们发现，对于一块草地，使 Bessie 能吃到它的起始点也一定在一个平行于坐标轴的正方形里，那么被这种正方形覆盖最多的位置就是选定的起始点了。

对每块草地存下这样一个正方形，然后扫描线搞就好了。

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
inline int max(int a,int b){return a>b?a:b;}
#define M (L+R>>1)
struct segment_tree{
	int mx[1<<19],lz[1<<19];
	void Down(int k){
		mx[k<<1]+=lz[k];lz[k<<1]+=lz[k];
		mx[k<<1|1]+=lz[k];lz[k<<1|1]+=lz[k];
		lz[k]=0;
	}
	void Add(int l,int r,int a,int L,int R,int k){
		if(l<=L&&R<=r){mx[k]+=a;lz[k]+=a;return;}
		Down(k);
		if(l<=M)Add(l,r,a,L,M,k<<1);
		if(r>M)Add(l,r,a,M+1,R,k<<1|1);
		mx[k]=max(mx[k<<1],mx[k<<1|1]);
	}
	int Max(){return mx[1];}
}t;
const int N=1e5+3;
struct segment{int l,r,y,f;}a[N+N];
bool Cmp(const segment&a,const segment&b){return a.y==b.y?a.f>b.f:a.y<b.y;}
int n,m,ans,x[N],y[N],value[N],tmp[N+N],k;
inline void Rotate(int&x,int&y){int tmpx=x,tmpy=y;x=tmpx+tmpy,y=tmpy-tmpx;}
signed main(){
	int l,r;
	scanf("%d%d",&n,&m);m<<=1;
	for(int i=1;i<=n;i++){
	  scanf("%d%d%d",value+i,x+i,y+i);
	  Rotate(x[i],y[i]);
	  tmp[i]=x[i],tmp[i+n]=x[i]+m;
	}
	std::sort(tmp+1,tmp+1+n+n);
	k=0;
	tmp[0]=-1;
	for(int i=1;i<=n+n;i++)
	  if(tmp[i]!=tmp[i-1])tmp[++k]=tmp[i];
	for(int i=1;i<=n;i++){
	  l=std::lower_bound(tmp+1,tmp+1+k,x[i])-tmp;
	  r=std::lower_bound(tmp+1,tmp+1+k,x[i]+m)-tmp;
	  a[i]=(segment){l,r,y[i],value[i]};
	  a[i+n]=(segment){l,r,y[i]+m,-value[i]};
	}
	std::sort(a+1,a+1+n+n,Cmp);
	for(int i=1;i<=n+n;i++){
	  t.Add(a[i].l,a[i].r,a[i].f,1,n+n,1);
	  ans=max(ans,t.Max());
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：cheng2010 (赞：0)

首先有经典结论，在曼哈顿距离下距离某个的点不超过 $k$ 的所有点 $(x,y)$ 可以变成 $(x-y,x+y)$ 从而转化为在切比雪夫距离下距离某个的点不超过 $k$，证明简单。

那转化后有什么用呢？发现原本是斜着的矩形，但是现在正过来了，于是问题友好了起来，题目转化为求带权矩形的交的最大值了。

（以下设矩形 $i$ 横坐标范围为 $xl_i\sim xr_i$，纵坐标为 $yl_i\sim yr_i$）

那怎么做？首先考虑怎么才能相交，先看横坐标，当且仅当横坐标相交，矩形才有可能相交（还有纵坐标），所以我们可以把 $xl,xr$ 当成一条条线段，先按 $xl$ 排序，用小根堆堆维护目前的所有线段的右端点（即 $xr$），每次加进来一条线段时与堆顶比较，看看是否大于堆顶，是则弹出堆顶，删除堆顶代表的线段，继续判断，否则退出，在线段树中在该线段**纵坐标**代表的范围内加上该线段的权值，这样做完了。

时间复杂度看似 $O(n \log^2 n)$ 实则 $O(n \log n)$，因为每条线段只会插入、删除一次。

```cpp
#include<bits/stdc++.h>
#define LL p<<1
#define RR p<<1|1
using namespace std;
const int N=1e5+7;
const int MAXN=4e6;
const int M=2e7+1;
int tree[M],lazy[M];
int n,k;
inline void cg(int &x,int &y)
{
	int xx=x;
	int yy=y;
	x=xx-yy;
	y=xx+yy;
	x+=2e6;
	y+=2e6;
}
int ans;
struct ID{int l,r;};
struct Node
{
	int l,r,val;
	ID x;
}a[N];
inline bool cmp(Node A,Node B)
{
	return A.l==B.l?A.r<B.r:A.l<B.l; 
}
priority_queue<pair<int,int> > q;
inline void pushdown(int p)
{
	tree[LL]+=lazy[p];
	tree[RR]+=lazy[p];
	lazy[LL]+=lazy[p];
	lazy[RR]+=lazy[p];
	lazy[p]=0;
}
inline void pushup(int p)
{
	tree[p]=max(tree[LL],tree[RR]);
}
inline void update(int p,int l,int r,int L,int R,int w)
{
	if(L<=l&&r<=R)
	{
		tree[p]+=w;
		lazy[p]+=w;
		return;
	}
	pushdown(p);
	int mid=l+r>>1;
	if(mid>=L) update(LL,l,mid,L,R,w);
	if(mid<R) update(RR,mid+1,r,L,R,w);
	pushup(p); 
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int x,y,w;
		cin>>w>>x>>y;
		int x1=x,y1=y+k,x2=x,y2=y-k,x3=x+k,y3=y,x4=x-k,y4=y;
		cg(x,y),cg(x1,y1),cg(x2,y2),cg(x3,y3),cg(x4,y4);
		a[i].l=x1;
		a[i].r=x2;
		a[i].x.l=y2;
		a[i].x.r=y1;
		a[i].val=w;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		while(1)
		{
			if(q.empty()) break;
			int v=-q.top().first;
			if(v<a[i].l)
			{
				int id=q.top().second;
				update(1,1,MAXN,a[id].x.l,a[id].x.r,-a[id].val);
				q.pop();
			}
			else break;
		}
		q.push({-a[i].r,i});
		update(1,1,MAXN,a[i].x.l,a[i].x.r,a[i].val);
		ans=max(ans,tree[1]);
	}
	cout<<ans;
}
```

---

