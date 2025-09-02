# [NordicOI 2025] 垃圾收集 / Garbage Collection

## 题目描述

北海上漂浮着 $N$ 块垃圾，编号从 $1$ 到 $N$。第 $i$ 块垃圾位于坐标 $\left(x_{i}, y_{i}\right)$，重量为 $w_{i}$。作为一项清理行动的一部分，你需要在某个矩形区域内收集所有垃圾。这个矩形区域的宽度为 $W$，高度为 $H$，但具体位置尚未确定。

你的任务是确定在最佳位置放置清理区域时，能够收集到的垃圾总重量的最大值。

译者注：「北海（North Sea）」指的是是北大西洋的一部分，不是广西壮族自治区北海市。

## 说明/提示

【样例解释】

最佳的清理区域应覆盖坐标为 $(3,1)$、$(2,1)$ 和 $(1,0)$ 的垃圾，总重量为 $10+5+5=20$。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ln6vecp.png)

【数据规模与约定】

对于所有数据，满足：

$1 \leq N \leq 10^{5},1 \leq W, H \leq 10^{9},0 \leq x_{i}, y_{i} < 10^{9}(1 \leq i \leq N),1 \leq w_{i} \leq 10^{9}(1 \leq i \leq N)$。

详细子任务附加限制及分值如下表所示：

|  子任务编号| 分值 | 特殊限制 |
| :-----------: | :-----------: |:-----------: |
| $1$ | $10$ | $N \le 400$ |
| $2$ | $12$ | $W,H,x_i,y_i \le 2000$ |
| $3$ | $15$ | $N \le 2000$ |
| $4$ | $22$ | $H=10^9$ |
| $5$ | $23$ | $W,H,x_i,y_i \le 10^5$ |
| $6$ | $18$ |无特殊限制  |

## 样例 #1

### 输入

```
5 3 2
3 1 10
2 1 5
1 0 5
0 2 10
1 3 5
```

### 输出

```
20```

# 题解

## 作者：seika27 (赞：4)

### 思路
我们考虑将垃圾按 $x$ 排序，然后维护一个集合，使这个集合中的最大的横坐标之差不大于 $W$。

这个集合的维护是简单的，从左往右扫，每次遇到一个新的垃圾就去集合末尾踢掉一些垃圾。由于每个垃圾最多只会被加进集合一次，踢出集合一次，所以复杂度十分的正确。

那么接下来考虑如何快速计算集合内的答案。

我们考虑记 $l_i$ 表示我们能选择的矩形的靠下的那条边纵坐标为 $i$ 时，能捞到的垃圾重量之和。

下一步考虑加入一个新的垃圾进入集合，会对哪些 $l_i$ 产生影响。

这个很容易就能推出来，当加入了一个纵坐标为 $y_i$ 的新垃圾，那么当你的矩形最下面一条边的纵坐标 $i$ 满足 $y_i-H+1\leq i \leq y_i$ 时，你就可以捞到这个垃圾。

发现这是一个十分简单的区间修改，搞个线段树，发现这个纵坐标有点大，搞个离散化。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,w,h;
const int N=1e5+5;
struct point
{
	int x,y,w;
	int ly,hy;
}a[N];
int b[N<<1];
int tot;
inline bool operator<(point a,point b)
{
	return a.x^b.x?a.x<b.x:a.y^b.y?a.y<b.y:a.w<b.w;
}
struct sgt
{
	int lar[N<<2],add[N<<2];
#define lx (x<<1)
#define rx (x<<1|1)
#define mid (L+R>>1)
	inline void up(int x)
	{
		lar[x]=max(lar[lx],lar[rx]);
		return;
	}
	inline void tag(int x,int L,int R)
	{
		if(add[x])
		{
			lar[lx]+=add[x];
			lar[rx]+=add[x];
			add[lx]+=add[x];
			add[rx]+=add[x];
			add[x]=0;
		}
		return;
	}
	void update(int x,int L,int R,int l,int r,int v)
	{
		if(l<=L&&R<=r){lar[x]+=v,add[x]+=v;return;}
		tag(x,L,R);
		if(l<=mid)update(lx,L,mid,l,r,v);
		if(r>mid)update(rx,mid+1,R,l,r,v);
		up(x);
		return;
	}
}subaru;
int ans;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>w>>h;
	for(int i=1;i<=n;++i)cin>>a[i].x>>a[i].y>>a[i].w,b[++tot]=a[i].y,b[++tot]=a[i].y-h+1;
	sort(a+1,a+1+n);
	sort(b+1,b+1+tot);
	tot=unique(b+1,b+1+tot)-b-1;
	for(int i=1;i<=n;++i)a[i].ly=lower_bound(b+1,b+1+tot,a[i].y-h+1)-b,a[i].hy=lower_bound(b+1,b+1+tot,a[i].y)-b;
	for(int i=1,j=1;i<=n;++i)
	{
		subaru.update(1,1,n,a[i].ly,a[i].hy,a[i].w);
		while(a[j].x+w-1<a[i].x)subaru.update(1,1,n,a[j].ly,a[j].hy,-a[j].w),++j;
		ans=max(ans,subaru.lar[1]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Masterwei (赞：4)

题目意思：给定 $n$ 个坐标轴上的点，点有权值，可以选择一个长为 $h$，高为 $w$ 的矩阵，求矩阵内的点的权值的最大值。

考虑扫描线，将点按 $x$ 坐标排序，使得当前维护的点 $x$ 的差值不超过 $h$。我们设 $f_i$ 表示在所有维护的点中，$0\le i-y\le w$ 的权值之和，最大的 $f_i$ 就是答案。

考虑维护 $f$，发现每个点对于 $f$ 都是一个区间加的操作，所以拿线段树维护即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e5+5,V=1e9;
int n,h,w;
struct node{
	int x,y,w;
}a[Maxn];
int root,cnt;
struct Tree{
	int ls,rs,data,tag;
}t[Maxn*100];
void change(int&x,int l,int r,int L,int R,int p){
	if(!x)x=++cnt;
	R=min(R,V);
	if(L<=l&&r<=R){t[x].data+=p;t[x].tag+=p;return;}
	int mid=l+r>>1;
	if(mid>=L)change(t[x].ls,l,mid,L,R,p);
	if(mid<R)change(t[x].rs,mid+1,r,L,R,p);
	t[x].data=max(t[t[x].ls].data,t[t[x].rs].data)+t[x].tag;
}
signed main(){
	n=read();h=read();w=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),read()};
	sort(a+1,a+1+n,[&](node i,node j){return i.x<j.x;});
	int p=1,ans=0;
	for(int i=1;i<=n;i++){
		while(p<i&&a[i].x-a[p].x+1>h)change(root,0,V,a[p].y,a[p].y+w-1,-a[p].w),++p;
		change(root,0,V,a[i].y,a[i].y+w-1,a[i].w);
		ans=max(ans,t[root].data);
	}printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：wangyanjing (赞：3)

其他的题解都是双指针，这里给出一个**扫描线**的做法。
# Description
由于题意中的矩形的长宽固定，故只要固定矩形的右下方的端点，即可确定一个矩形。  
**我们可以用矩形的右下端点来代表一个矩形。**  
![](https://cdn.luogu.com.cn/upload/image_hosting/23af9zeq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
以上图片的红点为右下端点。  
我们定义一个矩形的右下端点为 $P$ 点。

现在我们考虑一个点 $A$ 可以对那些 $P$ 点产生贡献。  
很显然，在以 $A$ 为左上端点，长为 $W$，宽为 $H$ 的矩形内的所有 $P$ 点，都可以吃到 $A$ 的贡献。如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/jk1a1dgc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们可以确定坐标，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3kboanay.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

现在问题转化为：  
给你 $n$ 个矩形，每个矩形有一个权值，一个点的权值为所有覆盖这个点的矩形的权值之和，求所有点权值的最大值。

# Solution

我们可以使用**扫描线**解决。

先储存，并离散化矩形的端点。

```cpp
struct Rectangle{
	int x1,y1,x2,y2,val;
}a[N];

int lenX = 0,lenY = 0;
for(int i = 1;i<=n;++i){
  int x1,y1,val;
  std::scanf("%d %d %d",&x1,&y1,&val);
  int x2 = x1+W-1,y2 = y1-H+1;
  a[i] = (Rectangle){x1,y1,x2,y2,val};
  tmpX[++lenX] = x1,tmpX[++lenX] = x2;
  tmpY[++lenY] = y1,tmpY[++lenY] = y2;
} 
std::sort(tmpX+1,tmpX+lenX+1);
std::sort(tmpY+1,tmpY+lenY+1);
lenX = std::unique(tmpX+1,tmpX+lenX+1)-tmpX-1;
lenY = std::unique(tmpY+1,tmpY+lenY+1)-tmpY-1;
for(int i = 1;i<=n;++i){
  a[i].x1 = std::lower_bound(tmpX+1,tmpX+lenX+1,a[i].x1)-tmpX;
  a[i].x2 = std::lower_bound(tmpX+1,tmpX+lenX+1,a[i].x2)-tmpX;
  a[i].y1 = std::lower_bound(tmpY+1,tmpY+lenY+1,a[i].y1)-tmpY;
  a[i].y2 = std::lower_bound(tmpY+1,tmpY+lenY+1,a[i].y2)-tmpY;
}
```
我们考虑怎样添加一个矩形。

### 暴力：

```cpp
for(int i = x1;i<=x2;++i)
	Plus(y2,y1,val);//[y2,y1]区间加 
```
### 考虑差分：

```cpp
Plus(y2,y1,val)//i = x1
Plus(y2,y1,-val)//i = x2+1
```
现在添加一个矩形只需两次区间加操作，用线段树即可。

再用一个邻接表存储每个 $x$ 点的操作即可。

### 完整代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#define ll long long
const int N = 1e5+5;
inline ll max(ll a,ll b){return a>b?a:b;}
struct Segment_Tree{
	struct Tree{
		int lson,rson;
		ll Max,Add; 
		inline void Fun_Add(ll val){
			Max += val,
			Add += val;
		}
	}tree[N<<2];
	int root,total;
	inline void build(int &rt,int l,int r){
		rt = ++total;
		if(l == r) return ;
		int mid = l+r>>1;
		build(tree[rt].lson,l,mid);
		build(tree[rt].rson,mid+1,r); 
	}
	inline void push_up(int rt){
		tree[rt].Max = max(tree[tree[rt].lson].Max,tree[tree[rt].rson].Max);
	}
	inline void push_down(int rt){
		if(tree[rt].Add)
			tree[tree[rt].lson].Fun_Add(tree[rt].Add),
			tree[tree[rt].rson].Fun_Add(tree[rt].Add),
			tree[rt].Add = 0;
	}
	inline void Plus(int rt,int treeL,int treeR,int askL,int askR,ll val){
		if(askL <= treeL && treeR <= askR)
			return tree[rt].Fun_Add(val);
		push_down(rt);
		int mid = treeL+treeR>>1;
		if(askL<=mid) Plus(tree[rt].lson,treeL,mid,askL,askR,val);
		if(askR>mid) Plus(tree[rt].rson,mid+1,treeR,askL,askR,val);
		push_up(rt);
	}
}T;
struct Rectangle{
	int x1,y1,x2,y2,val;
}a[N];
struct Node{
	int l,r,val;
};
std::vector<Node> Key[N<<1];
int tmpX[N<<1],tmpY[N<<1];
int main(){
	int n,W,H;
	std::scanf("%d %d %d",&n,&W,&H);
	int lenX = 0,lenY = 0;
	for(int i = 1;i<=n;++i){
		int x1,y1,val;
		std::scanf("%d %d %d",&x1,&y1,&val);
		int x2 = x1+W-1,y2 = y1-H+1;
		a[i] = (Rectangle){x1,y1,x2,y2,val};
		tmpX[++lenX] = x1,tmpX[++lenX] = x2;
		tmpY[++lenY] = y1,tmpY[++lenY] = y2;
	} 
	std::sort(tmpX+1,tmpX+lenX+1);
	std::sort(tmpY+1,tmpY+lenY+1);
	lenX = std::unique(tmpX+1,tmpX+lenX+1)-tmpX-1;
	lenY = std::unique(tmpY+1,tmpY+lenY+1)-tmpY-1;
	for(int i = 1;i<=n;++i){
		a[i].x1 = std::lower_bound(tmpX+1,tmpX+lenX+1,a[i].x1)-tmpX;
		a[i].x2 = std::lower_bound(tmpX+1,tmpX+lenX+1,a[i].x2)-tmpX;
		a[i].y1 = std::lower_bound(tmpY+1,tmpY+lenY+1,a[i].y1)-tmpY;
		a[i].y2 = std::lower_bound(tmpY+1,tmpY+lenY+1,a[i].y2)-tmpY;
	}
	for(int i = 1;i<=n;++i){
		int l = a[i].y2,r = a[i].y1;
		Key[a[i].x1].push_back({l,r,a[i].val});
		Key[a[i].x2+1].push_back({l,r,-a[i].val});
	}
	T.build(T.root,1,lenY);
	ll ans = 0;
	for(int i = 1;i<=lenX;++i){
		for(Node v : Key[i]) T.Plus(T.root,1,lenY,v.l,v.r,v.val);
		ans = max(ans,T.tree[T.root].Max);
	}
	std::printf("%lld",ans);
	return 0;
}


```

时间复杂度：$O(n \log n)$。

PS：真不知道题目的双指针标签是干嘛的。

---

## 作者：Istruggle (赞：1)

可以发现，如果只考虑长度为 $W$ 是很简单的，只需要使用双指针维护，如果当前垃圾的横坐标与所维护的左端点垃圾的横坐标差值大于 $W$ 则弹出左端点，直到符合条件为止，也就是说我们可以使用很优的时间复杂度来遍历所有长度为 $W$ 的区间，接下来只需要考虑如何快速求出每个长度合法的区间的答案即可。如果直接扫描难以解决，所以我们换个思路，用 $t_y$ 表示当这个矩形下面的边的纵坐标为 $y$ 时的答案。最终答案即为 $t_i$ 的最大值，我们考虑当加入或者删除一个点时对 $t_i$ 的影响，显然加入点 $i$ 时对于区间 $[y_i-h+1,y_i]$ 的 $t$ 值会增加 $w_i$，删除时则减少，这就是一个区间修改，线段树维护即可，由于值域较大，需要离散化。

#### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,w,h,t[N<<2],b[N],tag[N],cnt;
struct tub{int x,y,w;}a[N];
void push_up(int p){t[p]=max(t[p<<1],t[p<<1|1]);}
void addtag(int p,int d){
	t[p]+=d;
	tag[p]+=d;
}
void push_down(int p){
	if(tag[p]){
		addtag(p<<1,tag[p]);
		addtag(p<<1|1,tag[p]);
		tag[p]=0;
	}
}
void update(int p,int l,int r,int L,int R,int d){
	if(L<=l&&R>=r){
		addtag(p,d);
		return;
	}
	int mid=(l+r)>>1;
	push_down(p);
	if(L<=mid) update(p<<1,l,mid,L,R,d);
	if(R>mid) update(p<<1|1,mid+1,r,L,R,d);
	push_up(p);
}
bool cmp(tub x,tub y){return x.x<y.x;}
signed main(){
	scanf("%lld%lld%lld",&n,&w,&h);
	for(int i = 1;i<=n;i++){
		scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].w);
		b[++cnt]=a[i].y; b[++cnt]=a[i].y-h+1;
	}
	sort(a+1,a+1+n,cmp); sort(b+1,b+1+cnt);
	int m = unique(b+1,b+1+cnt)-b-1; int j=1,ans=0;
	for(int i = 1;i<=n;i++){
		int ly=lower_bound(b+1,b+1+m,a[i].y-h+1)-b;
		int ry=lower_bound(b+1,b+1+m,a[i].y)-b; 
		update(1,1,2e5,ly,ry,a[i].w);
		while(a[j].x+w-1<a[i].x){
			ly=lower_bound(b+1,b+1+m,a[j].y-h+1)-b;
			ry=lower_bound(b+1,b+1+m,a[j].y)-b;
			update(1,1,2e5,ly,ry,-a[j].w);
			j++;
		}
		ans=max(ans,t[1]);
	}
	printf("%lld",ans);
}
```

---

## 作者：JoyLosingK (赞：1)

首先将所有点按 $x$ 的大小排序，然后对 $x$ 进行双指针，当区间的左右端点距离大于 $W$ 时对左端点进行收缩。

这时考虑 $y$ 的问题。明显，对于一个 $y$，它能产生的贡献可以分为左边和右边。实际上，我们只需维护其中一边即可，这里选择左边来维护。那么一个 $y$ 的贡献区域为 $[y-H+1,y]$。

然后问题就转成实现了一个区间加，询问最大值的操作，使用线段树即可。

具体实现请看代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
#define rll register ll
#define lb(i) (i&(-i))
const ll N = 3e5 + 5;
ll n, w, h, lsh[N << 2], tot, ans;
struct note {
	ll x, y, z, ly;
} a[N];
inline bool cmp(note a, note b) {
	return a.x < b.x;
}
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * f;
}
struct tree {
	ll l, r, mx, tg;
#define l(z) t[z].l
#define r(z) t[z].r
#define mx(z) t[z].mx
#define tg(z) t[z].tg
} t[N << 2];
inline void build(ll k, ll l, ll r) {
	l(k) = l, r(k) = r;
	if (l == r) return;
	ll mid = l + r >> 1;
	build(k << 1, l, mid),
	build(k << 1 | 1, mid + 1, r);
}
inline void pushdown(ll k) {
	if (!tg(k)) return;
	mx(k << 1) += tg(k), mx(k << 1 | 1) += tg(k),
	tg(k << 1) += tg(k), tg(k << 1 | 1) += tg(k);
	return (void)(tg(k) = 0);
}
inline void Add(ll k, ll x, ll y, ll v) {
	if (x <= l(k) && r(k) <= y) return (void)(tg(k) += v, mx(k) += v);
	if (r(k) < x || y < l(k)) return;
	pushdown(k);
	Add(k << 1, x, y, v), Add(k << 1 | 1, x, y, v);
	mx(k) = max(mx(k << 1), mx(k << 1 | 1));
}
int main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	n = read(), w = read(), h = read();
	for (ll i = 1; i <= n; i++)
		a[i].x = read(), a[i].y = read(), a[i].z = read(),
		lsh[++tot] = a[i].y, lsh[++tot] = a[i].y - h + 1;
	sort(a + 1, a + n + 1, cmp), sort(lsh + 1, lsh + tot + 1);
	tot = unique(lsh + 1, lsh + tot + 1) - lsh - 1, build(1, 1, 300000);
	for (ll i = 1; i <= n; i++)
		a[i].ly = lower_bound(lsh + 1, lsh + tot + 1, a[i].y - h + 1) - lsh,
		a[i].y = lower_bound(lsh + 1, lsh + tot + 1, a[i].y) - lsh;
	for (ll l = 1, r = 1; r <= n; r++) {
		Add(1, a[r].ly, a[r].y, a[r].z);
		while (a[l].x + w - 1 < a[r].x) Add(1, a[l].ly, a[l].y, -a[l].z), l++;
		ans = max(ans, mx(1));
	}
	cout << ans;
	return 0;
}
```

无耻地求个赞。

---

## 作者：WuMin4 (赞：1)

## [[NordicOI 2025] 垃圾收集 / Garbage Collection](https://www.luogu.com.cn/problem/P12119)

## 思路

观察到 $W$ 的限制容易通过双指针进行维护。

具体来说，我们枚举矩形的右端点，并找到左端点的最小值。接下来考虑如何快速找到一段区间的最大和。

假设矩形下边的纵坐标为 $Y$，满足 $W$ 限制的所有垃圾的坐标为 $(x_i,y_i)$，重量为 $w_i$。

因为我们已经限制了 $W$，所以只会有满足 $Y\le y_i\le Y+H-1$ 的垃圾才会产生贡献。我们反向考虑，对于一个垃圾 $(x_i,y_i)$，只有当矩形下边的纵坐标 $Y$ 在 $y_i-H+1\le Y\le y_i$ 时才能让它产生贡献。

于是我们可以将这段区间整体加上 $w_i$。此时收集到的垃圾总重量的最大值即为单点最大值。可以通过将 $y_i$ 与 $y_i-H+1$ 离散化后通过线段树维护。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,w,h,c[1200005],lz[1200005],Ans;
struct node{
	int x,y,yl,yr,c;
}a[100005];
vector<int> lsh;
void push_up(int u){
	c[u]=max(c[u*2],c[u*2+1]);
}
void lz_tag(int u,int v){
	c[u]+=v,lz[u]+=v;
}
void push_down(int u){
	if(lz[u]!=0){
		lz_tag(u*2,lz[u]);
		lz_tag(u*2+1,lz[u]);
		lz[u]=0;
	}
}
void add(int u,int l,int r,int x,int y,int v){
	if(x<=l&&r<=y){
		lz_tag(u,v);
		return;
	}
	int mid=(l+r)/2;
	push_down(u);
	if(x<=mid) add(u*2,l,mid,x,y,v);
	if(mid<y) add(u*2+1,mid+1,r,x,y,v);
	push_up(u);
}
int qu(int u,int l,int r,int x,int y){
	if(x<=l&&r<=y) return c[u];
	int mid=(l+r)/2,mx=0;
	push_down(u);
	if(x<=mid) mx=max(mx,qu(u*2,l,mid,x,y));
	if(mid<y) mx=max(mx,qu(u*2+1,mid+1,r,x,y));
	return mx;
}
bool cmp(node x,node y){return x.x<y.x;}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>w>>h;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].c;
		a[i].yl=a[i].y-h+1,a[i].yr=a[i].y;
		lsh.push_back(a[i].yl);
		lsh.push_back(a[i].yr);
	}
	sort(lsh.begin(),lsh.end());
	int len=unique(lsh.begin(),lsh.end())-lsh.begin();
	for(int i=1;i<=n;i++){
		a[i].yl=lower_bound(lsh.begin(),lsh.begin()+len,a[i].yl)-lsh.begin()+1;
		a[i].yr=lower_bound(lsh.begin(),lsh.begin()+len,a[i].yr)-lsh.begin()+1;
	}
	sort(a+1,a+1+n,cmp);
	for(int l=1,i=1;i<=n;i++){
		while(a[i].x-a[l].x>=w)
			add(1,1,300000,a[l].yl,a[l].yr,-a[l].c),l++;
		add(1,1,300000,a[i].yl,a[i].yr,a[i].c);
		Ans=max(Ans,qu(1,1,300000,1,300000));
	}
	cout<<Ans;
	return 0;
}
```

[记录](https://www.luogu.com.cn/record/213040547)

---

## 作者：Asedwai (赞：1)

## 思路
  首先，要使答案最优，必然要保证选择的矩形某个边界上存在垃圾。我们钦定选择矩形的右边界上存在垃圾，枚举这个垃圾 $i$。按 $x$ 坐标排序后我们容易使用双指针对于每个 $i$ 找出最大的区间 $[j,i]$ 使得 $x_i-x_j+1\le W$，于是削去了矩形宽度的限制，将问题变为一维的。最后对于每个区间的最大答案求最大值即可。  

  对于这个区间记 $y$ 维坐标上 $v_i$ 表示 $y=i$ 时的垃圾总数。则每个区间的最大贡献应为 $\displaystyle  \max_{j=0}^{10^9} \sum_{k=j}^{j+H-1} a_k$。考虑如何快速计算。记 $\displaystyle  c_j=\sum_{k=j}^{j+H-1} a_k$，不难发现每个 $a_k$ 对 $c$ 的贡献是 $[k-H+1,k]$ 这段区间。因此在双指针过程中每新加入一个垃圾 $i$ 就将$[y_i-H+1,y_i]$ 这段区间增加 $w_i$，离散化后使用线段树快速维护；每踢出一个垃圾就将其贡献减去。则这段垃圾的最大贡献为线段树的全局最大值。总时间复杂度 $O(n\log n)$。  

## 代码
实现略微不同，仅供参考。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define LOCAL
#ifdef LOCAL
#define debug(format, args...) fprintf(stderr,\
"[\tLOG](Func:%s(), Line:%d): "   \
, __FUNCTION__, __LINE__);       \
fprintf(stderr, format"\r\n", ##args)
#else
#define debug(format, args...)  do {} while (0)
#endif
//#define endl "\n"
#define LL long long
#define fer(i, a, b, args...) for(int i = (a), ##args; i <= (b); i ++)
#define fel(i, a, b, args...) for(int i = (a), ##args; i >= (b); i --)
const int N = 2e5 + 10; 
int n, W, H; 
struct node {
	int x, y, v; 
} a[N]; 
struct tree_Segment {
	struct Tree_node {
		int l, r; 
		LL mx, lz; 
	} s[N * 4]; 
#define Ls(i) (i << 1)
#define Rs(i) ((i << 1) | 1)
	inline void push_up(int i) {
		s[i].mx = max(s[Ls(i)].mx, s[Rs(i)].mx); 
	}
	inline void a_lazy(int i, LL lz) {
		s[i].mx += lz; 
		s[i].lz += lz; 
	}
	inline void push_down(int i) {
		if(s[i].lz) {
			a_lazy(Ls(i), s[i].lz); 
			a_lazy(Rs(i), s[i].lz); 
			s[i].lz = 0; 
		}
	}
	inline void build(int i, int l, int r) {
		s[i].l = l, s[i].r = r; 
		s[i].lz = 0; 
		if(l == r) {
			s[i].mx = 0; 
			return ; 
		}
		int mid = l + r >> 1; 
		build(Ls(i), l, mid); 
		build(Rs(i), mid + 1, r); 
		push_up(i); 
	}
	inline void add(int i, int l, int r, LL v) {
		if(s[i].l >= l && s[i].r <= r) {
			a_lazy(i, v); 
			return ; 
		}
		push_down(i); 
		if(s[Ls(i)].r >= l) add(Ls(i), l, r, v); 
		if(s[Rs(i)].l <= r) add(Rs(i), l, r, v); 
		push_up(i); 
	}
#undef Ls
#undef Rs
} s; 
int t[N], tot; 
int get(int y) {
	return lower_bound(t + 1, t + tot + 1, y) - t; 
}
signed main() { 
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr); 
	cin >> n >> W >> H; 
	fer(i, 1, n) {
		cin >> a[i].x >> a[i].y >> a[i].v; 
		t[++ tot] = a[i].y; 
		t[++ tot] = a[i].y - H + 1; 
	}
	sort(t + 1, t + tot + 1); 
	tot = unique(t + 1, t + tot + 1) - t - 1; 
	sort(a + 1, a + n + 1, [](node a, node b) { return a.x < b.x; }); 
	s.build(1, 1, 2 * n); 
	LL ans = 0; 
	fer(i, 1, n, j = 1) {
		s.add(1, get(a[i].y - H + 1), get(a[i].y), a[i].v); 
		while(j <= i && a[i].x - a[j].x >= W) {
			s.add(1, get(a[j].y - H + 1), get(a[j].y), -a[j].v); 
			j ++; 
		}
		ans = max(ans, s.s[1].mx); 
	}
	cout << ans << endl; 
	return 0; 
}
```

---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[P12119 [NordicOI 2025] 垃圾收集 / Garbage Collection](https://www.luogu.com.cn/problem/P12119)

双倍经验：[P1502 窗口的星星](https://www.luogu.com.cn/problem/P1502)

### 题目分析

考虑场地放在哪里时一块垃圾会被抓住，若场地的左下角在横坐标 $[x_i-W+1,x_i]$，纵坐标 $[y_i-H+1,y_i]$ 这块矩形区域内，则第 $i$ 块垃圾的 $w_i$ 可以贡献上。

因此把 $n$ 块垃圾的可贡献范围整成矩形，看单点最大贡献值即可。然后就是扫描线了。

扫描线流程：

- 先把矩形坐标离散化。

- 把每个矩形拆成一条加边和一条减边，按纵坐标排序。

- 线段树维护整个区间最大值。

- 将当前高度的所有边加入线段树，形如区间加减。

- 取所有最大值的最大值为答案。

### 代码实现

不开 `long long` 见祖宗。

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=200005;
int n,w,h,x[N],tot;
struct line{
    int l,r,y,p;
}a[N];
bool cmp(line a,line b){
    if(a.y==b.y)return a.p>b.p;
    return a.y<b.y;
}
int s[N<<2],L[N<<2],R[N<<2],lzy[N<<2];
void build(int u,int l,int r){
    L[u]=x[l],R[u]=x[r];
    s[u]=lzy[u]=0;
    if(l<r)build(u<<1,l,(l+r>>1)),build(u<<1|1,(l+r>>1)+1,r);
}
void pushdown(int u){
    int k=lzy[u];
    lzy[u<<1]+=k,lzy[u<<1|1]+=k;
    s[u<<1]+=k,s[u<<1|1]+=k;
    lzy[u]=0;
}
void update(int u,int l,int r,int p){
    if(l<=L[u]&&R[u]<=r){
        lzy[u]+=p;
        s[u]+=p;
    }
    else if(l<=R[u]&&L[u]<=r){
        pushdown(u);
        update(u<<1,l,r,p),update(u<<1|1,l,r,p);
        s[u]=max(s[u<<1],s[u<<1|1]);
    }
}
int solve(){
    n<<=1;
    for(int i=1,x1,x2,y1,y2,l;i<=n;i+=2){
        cin>>x2>>y2>>l;
        x1=x2-w+1,y1=y2-h+1;
        a[i].l=x1,a[i].r=x2,a[i].y=y1,a[i].p=l;
        a[i+1].l=x1,a[i+1].r=x2,a[i+1].y=y2,a[i+1].p=-l;
        x[i]=x1,x[i+1]=x2;
    }
    sort(a+1,a+1+n,cmp);
    sort(x+1,x+1+n);
    tot=unique(x+1,x+1+n)-x-1;
    build(1,1,tot);
    int ans=0;
    for(int i=1;i<=n;i++){
        update(1,a[i].l,a[i].r,a[i].p);
        ans=max(ans,s[1]);
    }
    return ans;
}
signed main(){
    cin>>n>>w>>h;
    cout<<solve()<<'\n';
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/229223167)。

---

