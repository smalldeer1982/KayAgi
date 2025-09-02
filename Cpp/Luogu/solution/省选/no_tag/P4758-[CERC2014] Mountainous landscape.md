# [CERC2014] Mountainous landscape

## 题目描述

你正在穿越一个以山脉为主的风景区——在你的路径上有 $n$ 个地标（山峰和山谷）。你停下来喘口气，想知道：你现在在地平线上看到的是哪座山？

正式地说：给定一个平面上的多边形链 $P_1,P_2,\cdots,P_n$。这些点的 $x$ 坐标是严格递增的。对于这条链的每一段 $P_i P_{i+1}$，找出最小的索引 $j > i$，使得 $P_j P_{j+1}$ 上的至少一个点从 $P_i P_{i+1}$ 可见（严格位于射线 $P_i \ P^{\rightarrow}_{i+1}$ 之上）。

![0](https://cdn.luogu.com.cn/upload/pic/23379.png)

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
8
0 0
3 7
6 2
9 4
11 2
13 3
17 13
20 7
7
0 2
1 2
3 1
4 0
5 2
6 1
7 3```

### 输出

```
0 3 6 5 6 0 0
6 4 4 0 6 0```

# 题解

## 作者：JoshAlMan (赞：6)

如果给我们一个区间 $[l, r]$，我们要看这里面的点有没有可能作为答案，即 $[l, r+1]$ 区间有没有折线有部分在该线上方，这个很容易做，可以在预处理这一段的上凸包（越靠上越好，那么被完全包含在内测的凸包的确是没有用的）后 $O(\log n)$ 得出，即二分出斜率大于当前线斜率的第一个折线右端查是否在这个线上方即可（还有一些细节，如没有大于的就是第一个点）。

因此我们可以建一棵线段树，每个节点预处理一个上凸包。

对于每个点，在线段树上二分即可。时间复杂度 $O(n \log^2 n)$，空间复杂度 $O(n \log n)$。



---

## 作者：ez_lcw (赞：6)

先考虑如何确定对于某个 $i$ 的答案。

题目的要求是：对于每一个 $i=1,2,\cdots,n-1$，找一个最小的 $j$ 使得 $j>i$ 且线段 $P_jP_{j+1}$（含端点）与将射线 $P_iP_{i+1}$ 略向上平移后所得的射线相交。

这个要求可以转化为：拟一条射线 $P_iP_{i+1}$，找到最小的 $j$ 使得 $P_j$ 在这条射线上方（不含射线），那么 $P_{j-1}P_j$ 就是我们要找的答案。

![在这里插入图片描述](https://img-blog.csdnimg.cn/a3f096f88d8b4f92866845374632d665.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V6X2xjdw==,size_16,color_FFFFFF,t_70#pic_center)

原因也很简单，由于 $j$ 是最小的，所以对于任意的 $k\in [i+1,j-1]$，都有 $P_{k}$ 在这条射线下方（含射线），于是就能保证射线穿过线段 $P_{j-1}P_j$，在 $P_{j-1}P_j$ 之前不存在射线能穿过的线段。

那么现在问题就变成了：对于每一个 $i=1,2,\cdots,n-1$，找一个最小的 $j$ 使得 $j>i+1$ 且点 $P_j$ 在 $P_iP_{i+1}$ 上方（不含射线，下同）。

考虑二分，判断是否存在一个 $j\leq mid$ 满足条件，那么就需要判断点集 $\{P_{i+2},P_{i+3},\cdots,P_j\}$ 中是否存在点在射线上方。

看似我们并没有把问题简单化，甚至更加复杂化，因为貌似我们还是要枚举所有的点，甚至还加上了个二分。

但实际上我们能利用一个很好的性质：把二分的判断转化为判断点集 $\{P_{i+2},P_{i+3},\cdots,P_j\}$ 的上凸壳中是否存在点在射线上方，我们就能通过三分来 $O(\log n)$ 判断了。

而且一段区间的点的上凸壳是不会随着询问改变而改变的，而且我们可以通过线段树来维护一段区间的点的上凸壳。

于是我们可以直接在线段树上二分：假设我们当前要在区间 $[l,r]$ 寻找最小的 $j$，那我们用三分判断左儿子内有没有符合条件的 $j$，有的话就去左儿子找，否则去右儿子找。

总时间复杂度 $O(Tn\log ^2n)$。

```cpp
#include<bits/stdc++.h>

#define N 100010
#define ll long long

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^'0');
		ch=getchar();
	}
	return x*f;
}

struct Point
{
	int x,y;
	Point(){};
	Point(int xx,int yy){x=xx,y=yy;}
}p[N],sta[N],s,t;

Point operator - (Point a,Point b){return Point(a.x-b.x,a.y-b.y);}
ll cross(Point a,Point b){return 1ll*a.x*b.y-1ll*b.x*a.y;}

int n;
int top;

vector<Point>v[N<<2];

void insert(Point u)
{
	while(top>1&&cross(sta[top]-sta[top-1],u-sta[top-1])>=0) top--;
	sta[++top]=u;
}

void merge(int k)
{
	top=0;
	int lc=k<<1,rc=k<<1|1;
	int l=0,r=0;
	while(l<v[lc].size()&&r<v[rc].size())
	{
		if(v[lc][l].x<v[rc][r].x) insert(v[lc][l]),l++;
		else insert(v[rc][r]),r++;
	}
	while(l<v[lc].size()) insert(v[lc][l]),l++;
	while(r<v[rc].size()) insert(v[rc][r]),r++;
	for(int i=1;i<=top;i++) v[k].push_back(sta[i]);
}

void build(int k,int l,int r)
{
	v[k].clear();
	if(l==r)
	{
		v[k].push_back(p[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	merge(k);
}

bool check(int k)
{
	int l=0,r=v[k].size()-1,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(!mid||cross(t-s,v[k][mid-1]-s)<cross(t-s,v[k][mid]-s)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return cross(t-s,v[k][ans]-s)>0;
}

int query(int k,int l,int r,int x)
{
	if(x<=l)
	{
		if(!check(k)) return 0;
		if(l==r) return l-1;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
	{
		int tmp=query(k<<1,l,mid,x);
		if(tmp) return tmp;
	}
	return query(k<<1|1,mid+1,r,x);
}

int main()
{
	int T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			p[i].x=read(),p[i].y=read();
		build(1,1,n);
		for(int i=1;i<n-1;i++)
		{
			s=p[i],t=p[i+1];
			printf("%d ",query(1,1,n,i+2));
		}
		puts("0");
	}
	return 0;
}
```



---

## 作者：Arghariza (赞：4)

这是一个跑不过双 $\log$ 的单 $\log$ 做法。

考虑双 $\log$ 做法是怎么做的。令 $a_i(1\le i\le n)$ 为给定的 $x$ 坐标递增的点序列，开一棵线段树维护区间上凸壳，第 $i$ 次查询相当于在 $[i+2,n]$ 区间组成的点的上凸壳中，找到一个在经过 $a_i,a_{i+1}$ 两点的直线上的点 $a_j$，那么线段 $a_{j-1},a_j$ 就是答案。

这个过程显然可以 $O(n\log n)$ 预处理之后，线段树上二分实现。复杂度 $O(n\log^2 n)$，因为每次查询都要二分斜率所以是双 $\log$ 的。

有一个避免二分的做法。考虑对 $i=1,2,\cdots, n-2$ 的询问直线 $a_i,a_{i+1}$ 离线下来并按照斜率从大到小排序。那么每次在线段树节点中查询的斜率是单调递增的，于是记录一个 $p_x$ 表示当前斜率下查询 $x$ 的切点位置即可。

由于线段树节点凸壳点数是 $O(n\log n)$ 的，所以 $p_x$ 的总移动次数是 $O(n\log n)$ 的，所以复杂度是 $O(n\log n)$ 的。但是实测跑得没有二分快，可能是因为 $p_x$ 的移动次数卡得比较满。

```cpp
// Problem: P4758 [CERC2014] Mountainous landscape
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4758
// Memory Limit: 125 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define ll long long
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    // #if ONLINE_JUDGE
    // #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    // #else
    #define gh() getchar()
    // #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 1e5 + 100;

int n, pos[N << 2], id[N], ans[N];
vector<int> tr[N << 2];

struct node {
	int x, y;
	node () { }
	node (int _x, int _y) : x(_x), y(_y) { }
	node operator - (const node &rhs) const { return node(x - rhs.x, y - rhs.y); }
	ll operator * (const node &rhs) const { return 1ll * x * rhs.y - 1ll * y * rhs.x; }
} a[N];

#define ls x << 1
#define rs x << 1 | 1
#define mid ((l + r) >> 1)

void init(int l, int r, int x) {
	for (int i = l; i <= r; i++) {
		int sz = tr[x].size();
		while (sz > 1 && (a[i] - a[tr[x][sz - 1]]) * (a[tr[x][sz - 1]] - a[tr[x][sz - 2]]) < 0) tr[x].pop_back(), sz--;
		tr[x].pb(i);
	}
}

bool calc(int k, int x) {
	while (pos[x] < tr[x].size() - 1 && (a[k + 1] - a[k]) * (a[tr[x][pos[x]]] - a[k]) < (a[k + 1] - a[k]) * (a[tr[x][pos[x] + 1]] - a[k])) pos[x]++;
	return (a[k + 1] - a[k]) * (a[tr[x][pos[x]]] - a[k]) > 0;
}

void build(int l, int r, int x) {
	tr[x].clear(), init(l, r, x), pos[x] = 0;
	if (l == r) return;
	build(l, mid, ls), build(mid + 1, r, rs);
}

int qry(int l, int r, int p, int k, int x) {
	if (p <= l) {
		if (!calc(k, x)) return 0;
		if (l == r) return l;
	}
	if (p <= mid) {
		int res = qry(l, mid, p, k, ls);
		if (res) return res;
	}
	return qry(mid + 1, r, p, k, rs);
}

void solve() {
	n = rd();  
	for (int i = 1, x, y; i <= n; i++) 
		x = rd(), y = rd(), a[i] = node(x, y);
	build(1, n, 1);
	for (int i = 1; i <= n - 2; i++) id[i] = i;
	sort(id + 1, id + n - 1, [] (int &x, int &y) { return (a[x + 1] - a[x]) * (a[y + 1] - a[y]) < 0; });
	for (int i = 1; i <= n - 2; i++) {
		int p = qry(1, n, id[i] + 2, id[i], 1);
		ans[id[i]] = (!p) ? 0 : (p - 1);
	}
	for (int i = 1; i <= n - 2; i++)
		wr(ans[i]), pc(' ');
	wr(0), pc('\n');
}

signed main() {
	int T = rd();
	while (T--) solve();
    return 0;
}
```

---

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P4758)。

## 思路

发现 $n\le 10^5$，容易想到分块，对原序列分块，对于求解一个点 $i$ 的答案，遍历后面的点 $j$，散块暴力叉积判断，现在问题是如何求解整块的答案。

事实上我们并不需要求解整块的答案，我们只需判断这个整块是否存在一个点使得该点 $j$ 在射线 $P_iP_{i+1}$ 上，如果存在，就暴力遍历该块，然后退出。不妨对整块建上凸壳，没在凸壳上的点一定没有在凸壳上的点优，每次在整块中二分斜率找出最后一个斜率小于等于 $P_iP_{i+1}$ 斜率的线，判断其右端点是否在射线 $P_iP_{i+1}$ 上方，如果这个点都不在上方的话，那么后面的点更不可能在上方了。

时间复杂度 $\mathcal O(n\sqrt{n\log n})$，由于每个块是互不影响的，这种性质不难想到把分块换成线段树，时间复杂度 $\mathcal O(n\log^2 n)$。

下面是分块代码：


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+7,B=350;
int T,n;
int L[B],R[B],bl,pos[Maxn];

struct point{
	int x,y;
	point(int x=0,int y=0):x(x),y(y){}
	inline point operator -(const point a){return point(x-a.x,y-a.y);} 
	inline ll operator *(const point a){return 1ll*x*a.y-1ll*y*a.x;};
}a[Maxn],vec[B][B]; 
inline ll multi(point p1,point p2,point p0){return (p1-p0)*(p2-p0);}

point stk[Maxn];
inline void solve(int ql,int qr,int bel){
    int top=0;
    for(int i=ql;i<=qr;i++) pos[i]=bel;
    for(int i=ql;i<=qr;i++){
        while(top>1 and 1ll*(stk[top].y-stk[top-1].y)*(a[i].x-stk[top].x)<=
                        1ll*(a[i].y-stk[top].y)*(stk[top].x-stk[top-1].x)) top--;
        stk[++top]=a[i];
    }
    for(int i=1;i<=top;i++) vec[bel][i]=stk[i]; vec[bel][0].x=top;
}

inline bool check(int i,int p){
    int l=2,r=vec[i][0].x,ret=1;
    while(l<=r){
        int mid=l+r>>1;
        if(1ll*(vec[i][mid].y-vec[i][mid-1].y)*(a[p+1].x-a[p].x)>=
           1ll*(a[p+1].y-a[p].y)*(vec[i][mid].x-vec[i][mid-1].x)) l=mid+1,ret=mid;
           else r=mid-1;
    }
    return multi(a[p+1],vec[i][ret],a[p])>0;
}
inline int doit(int l,int r,int p){
    for(int i=l;i<=r;i++) if(multi(a[p+1],a[i],a[p])>0) return i-1;
    return 0;
}
inline int work(int ql,int qr,int p){
    int wl=pos[ql],wr=pos[qr];
    if(wl==wr) return doit(ql,qr,p);
    if(doit(ql,R[wl],p)) return doit(ql,R[wl],p);
    for(int i=wl+1;i<wr;i++) if(check(i,p)) return doit(L[i],R[i],p);
    return doit(L[wr],qr,p);
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n); bl=sqrt(n);
        for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
        for(int i=1;i<=bl;i++) L[i]=R[i-1]+1,R[i]=i*bl;
        if(R[bl]<=n) R[++bl]=n,L[bl]=R[bl-1]+1;
        for(int i=1;i<=bl;i++) solve(L[i],R[i],i);

        for(int i=1;i<n-1;i++) printf("%d ",work(i+2,n,i));
        puts("0");
    }

    return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

考试原题，耶！

一个询问本质上是找点 $P_{j}$ 满足它在射线 $P_{i-1}P_{i}$ 上方，这个问题我们是可以二分的。

具体而言：二分一个区间 $[i+2,n]$ 时判断是否有点在其上方。考虑检查，我们发现可以维护区间内的上凸包，然后二分斜率来找到斜率第一个大于当前射线的折线是否在其上方。

外层二分加上内层二分是 $O(\log^3 n)$ 的，需要优化。很常见的思路就是把外层二分改成线段树二分，然后优化至 $O(n \log^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
struct Point{
	int x,y;
	Point operator-(const Point &tlh)const{
		return (Point){x-tlh.x,y-tlh.y};
	}
}a[N],s[N],b[N],st,ed;
int t,n,top,len;
bool cmp(Point x,Point y){
	return x.x<y.x;
}
vector <Point> c[N<<2];
int calc(Point x,Point y){
	return x.x*y.y-y.x*x.y;//交乘 
}
void insert(Point x){
	while(top>1&&calc(s[top]-s[top-1],x-s[top-1])>=0)top--;//可以取等? 
	s[++top]=x;
}
void updata(int x){
	len=top=0;
	for(int i = 0;i < c[x<<1].size();i++)b[++len]=c[x<<1][i];
	for(int i = 0;i < c[x<<1|1].size();i++)b[++len]=c[x<<1|1][i];
	sort(b+1,b+1+len,cmp);
	for(int i = 1;i <= len;i++)insert(b[i]);
	for(int i = 1;i <= top;i++)c[x].push_back(s[i]);
}
void build(int x,int l,int r){
	c[x].clear();
	if(l==r){
		c[x].push_back(a[l]);
		return;
	}int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);updata(x);
}

bool check(int x)
{
	int l = 0,r = c[x].size()-1,ans=-1;Point tlh=ed-st;
	while(l<=r){
		int mid=(l+r)>>1;
		if(!mid||calc(tlh,c[x][mid-1]-st)<calc(tlh,c[x][mid]-st)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return calc(tlh,c[x][ans]-st)>0;
}
int query(int x,int l,int r,int s){
	if(s<=l&&!check(x))return 0;
	if(l==r)return l-1;
	int mid=(l+r)>>1;
	if(s<=mid){
		int ans=query(x<<1,l,mid,s);
		if(ans)return ans;
	}
	return query(x<<1|1,mid+1,r,s);
}
void work(){
	cin >> n;
	for(int i = 1;i <= n;i++)cin >> a[i].x >> a[i].y;
	build(1,1,n);
	for(int i = 1;i < n-1;i++){
		st=a[i],ed=a[i+1];
		cout << query(1,1,n,i+2) << " ";
	}cout << 0 << "\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> t;
	while(t--)work();	
	return 0;
}
 
  

```

但是，这个题 $n$ 开到 $10^6$ 我们就毫无办法了吗？是假的，请看 VCR。

```
有一个避免二分的做法。考虑对 i=1,2,⋯,n−2 的询问直线 ai,ai+1 离线下来并按照斜率从大到小排序。那么每次在线段树节点中查询的斜率是单调递增的，于是记录一个 px 表示当前斜率下查询 x 的切点位置即可。
```

摘自[这篇题解](https://www.luogu.com.cn/article/exnp29yr)。意思就是说我们在满足询问斜率单调后，在查询时答案下标时单调递增的，所以记录切点位置即可做到均摊 $O(n \log n)$。

挺好的这个做法。

---

## 作者：littlez_meow (赞：0)

小清新计算几何。

[题目指路](https://www.luogu.com.cn/problem/P4758)。

### 题意

给定一个 $n$ 个点组成的折线 $P_1P_2\cdots P_n$，满足 $P_i$ 横坐标严格递增。对于所有 $i\in[1,n-1]$，求出最小的 $j>i$，满足线段 $P_jP_{j+1}$ 在射线 $P_iP_{i+1}$ 上方（不包括射线），不存在则为 $0$。

### 思路

发现线段 $P_jP_{j+1}$ 存在一点严格在射线 $P_iP_{i+1}$ 上方很不好处理。我们需要转化。

如果只是判断一个点那很好做。假设我们找到最小的 $j$ 使得 $P_j$ 严格在其上方，能否说明 $P_{j-1}P_j$ 是最靠左的在其上方的线段呢？

答案是可以。假设还存在更靠左的线段，那么它一定与射线 $P_iP_{i+1}$ 相交，且有一个端点在其上方。这与 $j$ 的最小性矛盾。

问题转化为在每个点集 $\{P_{i+2},P_{i+3},\cdots,P_n\}$ 找到最左边的严格在射线 $P_iP_{i+1}$ 上方的点。

考虑线段树上二分转化为判定性问题。发现如果存在一个点严格在射线 $P_iP_{i+1}$ 上方，那么一定有一个满足条件的点在点集的上凸壳上。这可以凸壳上二分求叉积最值实现。

而每次查询的凸壳又是确定的，可以事先预处理。

时间复杂度 $O(n\log^2n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define lc now<<1,l,(l+r)>>1
#define rc now<<1|1,((l+r)>>1)+1,r
using namespace std;
const int MAXN=1e5+1;
int n;
struct vec{
	int x,y;
	vec(const int&xx=0,const int&yy=0):x(xx),y(yy){}
	vec operator+(const vec&t){
		vec res(x+t.x,y+t.y);
		return res;
	}
	vec operator-(const vec&t){
		vec res(x-t.x,y-t.y);
		return res;
	}
	ll operator*(const vec&t){
		return x*1ll*t.y-y*1ll*t.x;
	}
};
vec p[MAXN];
inline bool cross(int x,int y,int z){
	vec xx(p[y]-p[x]),yy(p[z]-p[x]);
	return yy*xx<0;
}
vector<int>conv[MAXN<<2];
inline void solve(int now,int l,int r){
	int cnt=1,stk[MAXN];
	stk[cnt]=l;
	stk[++cnt]=l+1;
	F(i,l+2,r){
		while(cnt>1&&cross(stk[cnt-1],stk[cnt],i)) --cnt;
		stk[++cnt]=i;
	}
	conv[now].resize(cnt+1);
	F(i,1,cnt) conv[now][i]=stk[i];
	return;
}
void build(int now,int l,int r){
	if(l==r){
		conv[now].resize(2);
		conv[now][1]=l;
		return;
	}
	build(lc);
	build(rc);
	solve(now,l,r);
	return;
}
vec bg,ed;
inline bool check(int now){
	int l=1,r=conv[now].size()-1;
	int res(l);
	while(l<=r){
		int mid((l+r)>>1);
		ll qwq=(p[conv[now][mid]]-bg)*(ed-bg);
		if(qwq<0) return 1;
		if(mid==1||(p[conv[now][mid-1]]-bg)*(ed-bg)>qwq) l=mid+1,res=mid;
		else r=mid-1;
	}
	return (p[conv[now][res]]-bg)*(ed-bg)<0;
}
int query(int now,int l,int r,int pos){
	if(pos<=l){
		if(!check(now)) return 0;
		if(l==r) return l-1;
	}
	if(pos<=((l+r)>>1)){
		int res=query(lc,pos);
		if(res) return res;
	}
	return query(rc,pos);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T; 
	for(cin>>T;T;--T){
		cin>>n;
		F(i,1,n) cin>>p[i].x>>p[i].y;
		build(1,1,n);
		F(i,1,n-2){
			bg=p[i],ed=p[i+1];
			cout<<query(1,1,n,i+2)<<" ";
		}
		cout<<"0\n";
	}
	return 0;
} 
```

---

