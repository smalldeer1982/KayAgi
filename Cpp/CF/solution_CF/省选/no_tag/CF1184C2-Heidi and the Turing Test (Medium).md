# Heidi and the Turing Test (Medium)

## 题目描述

【问题描述】

定义一个二维球为，以一个点为球心，离球心的曼哈顿距离小于等于半径r的所有点的集合。点(x0,y0)与点(x1,y1)曼哈顿距离为|x0-x1|+|y0-y1|。给定n个点，和r输出二维球覆盖的最多点数。

## 样例 #1

### 输入

```
5 1
1 1
1 -1
-1 1
-1 -1
2 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2
1 1
1 -1
-1 1
-1 -1
2 0
```

### 输出

```
5
```

# 题解

## 作者：EternalEpic (赞：2)

一次在校内模拟赛中做过加强版，于是乎来补题了。

首先我们可以一眼看出题目是一个裸的斜45度正方形交集最大值，可是我们并不会维护，于是我考场上就挂那了。

我们可以考虑将曼哈顿距离转换为切比雪夫距离，只要将 $p(x,y)$ 变为 $q(x - y,x + y)$ 就可以让那个斜的正方形变为正过来边长为 $2r$ 的正方形。

这是为什么呢？我们知道 $|x_1 - x_2| + |y_1 - y_2|$ 是曼哈顿距离，而 $\max(|x_1 - x_2|, |y_1 - y_2|)$ 是切比雪夫距离。我们可以用等腰直角三角形构造 $K$ 型全等配合切比雪夫距离，来解决旋转45度(设直角顶点坐标为 $(x, y)$ ，则上腰顶点坐标为 $(x - y, x + y)$ )。

于是乎，这就是一个线段树扫描线板子了。

```cpp
// Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>
#include <tr1/unordered_map>
#define lowbit(x) (x & -x)

using namespace std;

inline char gc(void) {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define gc() getchar()

template <class T> inline void read(T &x) {
	T f = 1; x = 0; static char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -f;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c & 15);
	x *= f;
}

template <class T> inline void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

template <class T> inline void writeln(T x, char c = '\n') { write(x); putchar(c); }
template <class T> inline void chkmax(T &x, const T y) { x > y ? x = x : x = y; }
template <class T> inline void chkmin(T &x, const T y) { x < y ? x = x : x = y; }

#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)

typedef long long ll;
typedef pair <int, int> pii;

const int Maxn = 3e5 + 5, Maxm = 3e6 + 5;
int n, d, cnt = 0, ans = 0, b[Maxn]; pii p[Maxn];
struct SegmentTree {
	int tmx[Maxm << 3], tag[Maxm << 3];
	inline void pushup(int pos) { tmx[pos] = max(tmx[pos << 1], tmx[pos << 1 | 1]); }
	inline void addtag(int pos, int val) { tmx[pos] += val; tag[pos] += val; }
	inline void pushdown(int pos) {
		if (tag[pos]) {
			addtag(pos << 1, tag[pos]),
			addtag(pos << 1 | 1, tag[pos]);
			tag[pos] = 0;
		}
	}
	
	inline void modify(int pos, int l, int r, int L, int R, int val) {
		if (L <= l && R >= r) return addtag(pos, val);
		int mid = l + r >> 1; pushdown(pos);
		if (L <= mid) modify(pos << 1, l, mid, L, R, val);
		if (R > mid) modify(pos << 1 | 1, mid + 1, r, L, R, val);
		pushup(pos);
	}
} T;

signed main(void) {
	read(n), read(d);
	for (int i = 1, x, y; i <= n; i++) {
		read(x), read(y);
		p[i] = Mp(x - y, x + y);
	} sort(p + 1, p + n + 1);
	
	for (int i = 1, j = 1; i <= n; i++) {
		T.modify(1, -3e6, 3e6, p[i].second - d, p[i].second + d, 1);
		while (j <= n && p[i].first - p[j].first > 2 * d) T.modify(1, -3e6, 3e6, p[j].second - d, p[j].second + d, -1), ++j;
		chkmax(ans, T.tmx[1]);
	} writeln(ans);
	return 0;
}

/**/



```


---

## 作者：LTb_ (赞：2)

一个半径为 $r$ 的圆中所有点都对这个圆心有 $1$ 的贡献；同样地，一个点对以这个点为圆心，半径为 $r$ 的圆中所有的圆心都有 $1$ 的贡献。

考虑曼哈顿距离转切比雪夫距离，这样之后一个半径为 $r$ 的“圆”就变成了一个边长 $2r+1$ 的正方形。

把点按横坐标升序排序，枚举圆心的横坐标，对纵坐标建线段树即可动态维护这时答案的最大值。

```c++
// 2020.09.29
// Code by LTb
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define fi first
#define se second
inline int read(){
    int x=0,f=1;
    char ch;
    while(ch<'0'||ch>'9')  {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

const int MAXN=300005;
const int MAX=2e6+5000;
int n,rad;
int ans=1;
pair<int,int> a[MAXN];

struct Segment_Tree{
	const int INF=0x3f3f3f3f;
	struct node{
		int l,r;
		int add,mx;
	}st[MAX*8];
	
	void build(int p,int l,int r){
		st[p].l=l;st[p].r=r;
		if (l==r){
			return;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		st[p].mx=max(st[p<<1].mx,st[p<<1|1].mx);
	}

	void spread(int p){
		st[p<<1].add+=st[p].add;
		st[p<<1|1].add+=st[p].add;
		st[p<<1].mx+=st[p].add;
		st[p<<1|1].mx+=st[p].add;
		st[p].add=0;
	}

	void change(int p,int l,int r,int c){
		if (l<=st[p].l&&st[p].r<=r){
			st[p].add+=c;
			st[p].mx+=c;
			return;
		}
		spread(p);
		int mid=st[p].l+st[p].r>>1;
		if (l<=mid) change(p<<1,l,r,c);
		if (r>mid) change(p<<1|1,l,r,c);
		st[p].mx=max(st[p<<1].mx,st[p<<1|1].mx);
	}

	int query_max(int p,int l,int r){
		if (l<=st[p].l && st[p].r<=r)
			return st[p].mx;
		spread(p);
		int mid=st[p].l+st[p].r>>1,ans=-INF;
		if (l<=mid) ans=query_max(p<<1,l,r);
		if (r>mid) ans=max(ans,query_max(p<<1|1,l,r));
		return ans;
	}
}seg;

signed main()

{
	n=read();rad=read();
	int mx=0;
	for (int i=1;i<=n;i++){
		int x=read(),y=read();
		int tmp=x;
		a[i].fi=x+y+MAX;
		a[i].se=x-y+MAX;
		mx=max(mx,a[i].fi);
	}

	sort(a+1,a+1+n);

	seg.build(1,1,MAX*2);
	int l=1,r=1;

	for (int i=a[1].fi;i<=mx;i++){
		while (r<=n && a[r].fi<=i+rad){
			seg.change(1,a[r].se-rad,a[r].se+rad,1);
			r++;
		}
		while (l<=n && a[l].fi<i-rad){
			seg.change(1,a[l].se-rad,a[l].se+rad,-1);
			l++;
		}

		ans=max(ans,seg.query_max(1,1,MAX*2));
	}

	cout<<ans<<endl;
	return 0;
}
```

小声bb：值域开到 $10^9$ 的话其实也可做。

考虑对于一个横坐标为 $x$ 的点，它对线段树做的修改只有可能在 $x-r,x+r+1$ 这两个地方发生。于是我们只需要枚举这些点，原方法中“枚举圆心横坐标”这一操作的复杂度降至 $2n$。线段树加上动态开点，总复杂度即可优化到 $\mathcal{O(n \log W)}$，其中 $\mathcal{W}$ 为值域。

---

## 作者：Sudohry (赞：1)

前置知识：曼哈顿距离转切比雪夫距离[（不会做这个）](https://www.luogu.com.cn/problem/P3964)、[扫描线](https://www.luogu.com.cn/problem/P5490)。

发现题目中所述的斜正方形不好维护，考虑做坐标变换转化为切比雪夫距离的正方形，即 $(x,y)\rightarrow (x+y,x-y)$ 。

然后转化为矩形覆盖问题，即求若干个矩形下权值最大的点。

离线下来扫描横坐标，在线段树上对对应纵坐标区间操作即可。

时间复杂度 $O(n\log n)$ 。

[Code](https://www.luogu.com.cn/paste/eddnxdl8)

---

