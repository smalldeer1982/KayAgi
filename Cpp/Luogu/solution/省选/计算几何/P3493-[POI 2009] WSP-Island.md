# [POI 2009] WSP-Island

## 题目描述

Byteasar is the king of Byteotia, an island in The Ocean of Happiness.

The island is a convex shape, and all the towns of Byteotia are located on the shore.

One of these towns is Byteburg, the famous capital of Byteotia.

Every pair of towns is connected by a road that goes along the line segment between the towns.

Some roads that connect different pairs of towns intersect - there is a crossroad at each such intersection.

Bitratio, Byteasar's rival to the throne, had hatched a sordid plot.

While Byteasar was travelling from the capital to an adjacent town, Bitratio's people seized Byteburg.

Now Byteasar has to return to Byteburg as soon as possible in order to restore his rule.

Unfortunately, some of the roads are controlled by Bitratio's guerrilla.

Byteasar cannot risk the use of such roads, he can however cross them at the crossroads.

Needless to say, he has to travel along the roads and hence turn only at the crossroads, for otherwise the journey would take far too long.

Byteasar's loyal servants have informed him which roads are safe.

Byteasar believes your loyalty, and thus entrusts you with a task to find the shortest safe route from the town he is currently in to Byteburg.

Byteotia岛屿是一个凸多边形。城市全都在海岸上。按顺时针编号1到n。任意两个城市之间都有一条笔直的道路相连。道路相交处可以自由穿行。有一些道路被游击队控制了，不能走，但是可以经过这条道路与未被控制的道路的交点。问从城市1到n的最短距离。


## 说明/提示

spj-

## 样例 #1

### 输入

```
6 9
-12 -10
-11 6
-4 12
6 14
16 6
18 -2
3 4
1 5
2 6
2 3
4 5
3 5
1 3
3 6
1 6
```

### 输出

```
42.0000000000
```

# 题解

## 作者：nawuxika (赞：7)

##  分析

首先我们画下样例的图：

![样例](https://cdn.luogu.com.cn/upload/image_hosting/y2lf64fs.png)

可以非常明显地看出最优路径是 $A \rightarrow G \rightarrow H \rightarrow F$。也就是说最优路径就是沿着剩下的 **最内侧** 的边行走。

~~其实作为一个 $\text{OI}$ 选手猜出结论就可以了。~~

## 证明

使用数学归纳法证明，归纳命题为：最内侧路径上的点数等于 $n$(不包括 $2$ 个端点) 时，最内侧路径是最短路径。

① 当 $n=0$ 即最内侧路径为一条线段时，命题成立。（两点间线段距离最短）

② 令当 $n = k$ 时命题成立，当 $n=k+1$ 时，取出最内侧路径和任意一条外侧路径，如下图所示：

![证明图](https://cdn.luogu.com.cn/upload/image_hosting/f0rakpm7.png)

延长内侧路径第一条边将外侧路径分为两段，则有：
$$
AE+EF+FG+GH+HD \ge AI+IG+GH+HD = AB+BI+IG+GH+HD
$$
由于 $B \rightarrow I \rightarrow G \rightarrow G \rightarrow D$ 相对于 $B \rightarrow  C \rightarrow D$ 为一个外侧路径且内侧路径除端点点数为 $k$，所以有：
$$
BI+IG+GH+HD \ge BC+CD
$$
综上，有：
$$
AE+EF+FG+GH+HD \ge AB+BC+CD
$$
则当 $n=k+1$ 时命题成立。

综合① ② 可知命题成立。结论成立。

可以看出最短路径其实可以跑一个半平面交得出，就样例而言，所求折线 $A \rightarrow G \rightarrow H \rightarrow F$ 即可视为四边形 $AGHF$ 的周长减去 $AF$。而 $AGHF$ 即可视为是 $\vec{AB},\vec{AD},\vec{BD},\vec{BE},\vec{DF},\vec{EF}$ 的右侧半平面的交集。

## 算法

朴素算法就是将所有剩下的边直接暴力跑一次半平面交，复杂度 $O((n^2-m)\log(n^2-m))$，由于 $n \le 10^5$，显然这种做法是需要优化的，可以发现对于每一个点，以它为起点的向量中只有最向内偏的向量是有效的，同时我们发现 $m \le 10^6$，那么我们可以考虑利用链式前向星存储所有不合法的边，然后对于每一个边，从后向前遍历找出最内侧的合法边。最后跑一遍半平面交，算个长度。完结散花。

### $\text{AC CODE}$

```c++
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<set>
#include<bitset>
#include<map>
#include<algorithm>
#include<ctime>
#include<queue>
#include<stack>
#include<random>
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define il inline
using namespace std;
template<typename T>
il void read(T &x)
{
    x=0;int f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48); ch=getchar();}
    x*=f;
}
template<typename T>
il void write(T x)
{
    if(x<0) {putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=1e5+10,maxm=1e6+10;
const double eps=1e-12;//注意本题卡精度
int n,m,cnt,tot,top,head[maxn],h=1,t;
double ans;
bool vis[maxn],flag;
struct Edge{
    int to,next;
}edge[maxm<<1];
il void add(int u,int v)
{
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    head[u]=cnt;
}
struct point{
    double x,y;
    friend il point operator + (point a,point b) {return (point){a.x+b.x,a.y+b.y};}
    friend il point operator - (point a,point b) {return (point){a.x-b.x,a.y-b.y};}
    friend il point operator * (point a,double t) {return (point){t*a.x,t*a.y};}
}p[maxn],a[maxn];
il double d(point a,point b) {return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
il double dot(point a,point b) {return a.x*b.x+a.y*b.y;}
il double csp(point a,point b) {return a.x*b.y-b.x*a.y;}
il int sign(double x) {return fabs(x)<=eps?0:(x>0?1:-1);}
struct line{
    point p,v;
    double ang;
    friend il bool operator < (line a,line b)
    {return sign(a.ang-b.ang)==0?csp(a.v-a.p,b.v-a.p)>0:sign(a.ang-b.ang)<0;}
    il void getang() {ang=atan2(v.y-p.y,v.x-p.x);}
}l[maxn],q[maxn];
il point inter(line a,line b)
{
    point p1=a.p,p2=b.p,v1=a.v,v2=b.v,u=p2-p1;
    v1=v1-p1;v2=v2-p2;
    return p2+v2*(csp(u,v1)/csp(v1,v2));
}
il bool judge(line a,line b,line c)
{
    point p=inter(a,b);
    return sign(csp(c.v-c.p,p-c.p))<=0;
}
int main()
{
    read(n);read(m);
    for(int i=1;i<=n;++i) scanf("%lf%lf",&p[n-i+1].x,&p[n-i+1].y);//个人习惯是逆时针存图
    for(int i=1;i<=m;++i)
    {
        int u,v;read(u);read(v);
        if((u==1 and v==n) or (u==n and v==1)) flag=false;
        u=n-u+1;v=n-v+1;add(u,v);add(v,u);
    }
    if(flag) {cout<<d(p[1],p[n]); return 0;}//注意特判
    for(int i=1;i<n;++i)
    {
        for(int j=head[i];j;j=edge[j].next)
        {
            int v=edge[j].to;
            vis[v]=1;//处理出不合法的边
        }
        for(int j=n;j>i;--j)
        {
            if(!vis[j])
            {
                l[++tot].p=p[i];l[tot].v=p[j];
                l[tot].getang();break;
            }
        }
        for(int j=head[i];j;j=edge[j].next) vis[edge[j].to]=0;
    }
    l[++tot].p=p[n]; l[tot].v=p[1]; l[tot].getang();
    sort(l+1,l+tot+1);
    cnt=0;
    for(int i=1;i<=tot;++i)
    {
        if(i==1 or l[i].ang-l[i-1].ang>0) ++cnt;
        l[cnt]=l[i];
    }
    q[++t]=l[1];
    for(int i=2;i<=cnt;++i)
    {
        while(t>h and judge(q[t-1],q[t],l[i])) --t;
        while(t>h and judge(q[h],q[h+1],l[i])) ++h;
        q[++t]=l[i];
    }
    while(t>h and judge(q[t-1],q[t],q[h])) --t;
    while(t>h and judge(q[h],q[h+1],q[t])) ++h;
    tot=0;
    q[t+1]=q[h];
    for(int i=h;i<=t;++i) a[++tot]=inter(q[i],q[i+1]);
    a[tot+1]=a[1];
    for(int i=1;i<=tot;++i) ans+=d(a[i],a[i+1]);
    ans-=d(p[1],p[n]);
    printf("%.10lf",ans);
    return 0;
}
```


---

## 作者：Piwry (赞：7)

## 解析

这题如果作一下图应该就很好理解。

以题目样例为输入，其图像是：

![凸包](https://cdn.luogu.com.cn/upload/image_hosting/blgoholf.png)

其中黑色的线段为剩下的道路，红色的线段为答案路径。

可以发现，我们只需沿着 “最内侧的” 道路走即可最优；而又可以发现求这个东西的逻辑和半平面交很相似，于是题目就被转化为了一个半平面交问题。

~~（这严谨证明我不会qaq（逃）~~

不过一共 $n^2$ 条道路还是有点大。我们考虑**每个点**向编号比它大的点连的道路，发现向编号尽可能大的点连的道路一定是最 “向内侧” 的。于是道路的数量就缩减到了 $n$ 级别。

对于每条道路，我们将其转化为左侧（交）包含起点终点的有向直线，即从编号大的点连向编号小的点（根据凸包单调性）。

为了方便处理，我们再添加一条由起点连向终点的有向直线：这样最后求出的交就一定是一个凸包，我们求周长并减去这条边就可求得答案了。

不过要注意由于这条边的加入，对于起点到终点有道路的情况如果不特判就会出 bug（试图求平行线的交点）。

另外虽然题目保证有解，无解情况下我们实际上会求出一个无穷大的交，这时只需围一个边界并检查答案是否出现边界直线即可。

## CODE

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using std::sort;
using std::pair;
typedef pair<int, int> pad;

/*------------------------------Computational geometry------------------------------*/

const double pi =acos(-1), eps =1e-6;

struct vect{
	double x, y;
	vect(){}
	vect(double xx, double yy):x(xx), y(yy){}
	vect operator + (vect v){ return vect(x+v.x, y+v.y); }
	vect operator - (vect v){ return vect(x-v.x, y-v.y); }
	vect operator * (double mu){ return vect(mu*x, mu*y); }
	double operator / (vect v){ return x*v.y-y*v.x; }/*叉积*/
};

struct line{
	vect u, v;
	double angle;
	line(){}
	line(vect uu, vect vv):u(uu), v(vv){ angle =atan2(vv.y-uu.y, vv.x-uu.x); }
};

inline short gtr(double a, double b){ return (a-b > eps); }

inline bool eq(double a, double b){ return (a-b < eps && a-b > -eps); }

inline bool onright(line f, vect w){ return (gtr((w-f.u)/(f.v-f.u), 0)); }

vect getIntersection(line f, line g){
	double w =((g.u-f.u)/(f.u-f.v))/((f.u-f.v)/(g.u-g.v));
	return g.u+(g.u-g.v)*w;
}

int cmp(line A, line B){
	if(eq(A.angle, B.angle)) return onright(B, A.u);/*有向直线最左的在最后面，会被保留*/
	else return (gtr(B.angle, A.angle));
}

inline pad getHPI(line ls[], int totl, line hull[]){
	sort(ls, ls+totl, cmp);
	int l =0, r =0;
	for(int i =0; i < totl; ++i){
		while(i < totl-1 && eq(ls[i].angle, ls[i+1].angle)) ++i;
		while(r-l > 1 && onright(ls[i], getIntersection(hull[r-1], hull[r-2]))) --r;
		if(r > 0 && eq(ls[i].angle-hull[r-1].angle, pi)) return pad(0, 0);/*判方向相反的平行*/
		hull[r++] =ls[i];
	}
	while(r-l > 1){
        if(onright(hull[r-1], getIntersection(hull[l], hull[l+1]))) ++l;
        else if(onright(hull[l], getIntersection(hull[r-1], hull[r-2]))) --r;
        else break;
    }
	if(r-l < 3) return pad(0, 0);/*其实这行不会用到qwq*/
	else return pad(l, r);
}

inline double dist(vect x, vect y){ return sqrt((y.x-x.x)*(y.x-x.x)+(y.y-x.y)*(y.y-x.y)); }

inline double getPerimeter(line hull[], int toth, vect res[]){
	hull[toth++] =hull[0];
	for(int i =0; i < toth-1; ++i) res[i] =getIntersection(hull[i], hull[i+1]);
	/*偷懒直接用 toth 了*/
	res[toth-1] =res[0];
	double ret =0;
	for(int i =0; i < toth-1; ++i) ret +=dist(res[i], res[i+1]);
	return ret;
}

/*------------------------------Main------------------------------*/

const int MAXN =1e5+50, MAXM =1e6+50;

line ls[MAXN], hull[MAXN];
vect point[MAXN], res[MAXN];
pad ban[MAXM];
int ban2[MAXN];

int cmp2(pad a, pad b){ return a.first < b.first; }

inline int read(){
	int x =0; bool f =0; char c =getchar();
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read(), m =read();
	for(int i =0; i < n; ++i) point[i].x =read(), point[i].y =read();
	bool flg =1;
	for(int i =0; i < m; ++i){
		int a =read()-1, b =read()-1;
		if(a > b) a ^=b ^=a ^=b;
		if(a == 0 && b == n-1) flg =0;
		ban[i] =pad(a, b);
	}
	/*这种情况不判会出 bug*/
	if(flg) return printf("%lf", dist(point[0], point[n-1])) && 0;
	sort(ban, ban+m, cmp2);
	int totl =0;
	for(int i =0, p =0; i < n-1; ++i){
		memset(ban2, 0, sizeof(ban2));
		while(p < m && ban[p].first == i) ban2[ban[p].second] =1, ++p;
		int j =n-1;
		while(j > i && ban2[j]) --j;
		if(j == i) continue;
		ls[totl++] =line(point[j], point[i]);
	}
	ls[totl++] =line(point[0], point[n-1]);
	pad h =getHPI(ls, totl, hull);
	/*题目数据貌似保证有路；如果无路的话最后会求出无穷交*/
	printf("%.10lf", getPerimeter(hull+h.first, h.second-h.first, res)-dist(point[0], point[n-1]));
}
```

---

## 作者：Drind (赞：0)

### 题目解析

这题要我们求一个类似最短路的东西。我们发现一条路径应该是一个类似上凸壳的东西，所以最短的上凸壳就是从下面往上看，看到的那条上凸壳，也就是最靠下的那条（可以用类似松弛的思想感性理解一下）

所以我们可以用半平面交来计算这个上凸壳，记得加上一条从终点到起点的边让它变得封闭。

问题来了，这样会有 $n^2$ 条边，非常恐怖。所以我们要寻找一些没用的边删掉。容易发现，同样起点，指向更靠近 1 号点的边更不优，所以我们每个点出的边中只需要找到最远的一条边加进半平面交里即可，用 vector 维护，注意初始化即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const long double eps=1e-7;

struct point{
	long double x,y;
	friend point operator +(point a,point b){
		return {a.x+b.x,a.y+b.y};
	} 
	friend point operator -(point a,point b){
		return {a.x-b.x,a.y-b.y};
	}
	friend point operator *(point a,long double b){
		return {a.x*b,a.y*b};
	}
	friend point operator /(point a,long double b){
		return {a.x/b,a.y/b};
	}
};

struct edge{
	point s,t;
	long double ang;
};

inline long double dis(point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

inline long double cross(point a,point b){
	return a.x*b.y-a.y*b.x;
}
inline long double cross(point a,point b,point c){
	return cross(b-a,c-a);
}

inline long double dot(point a,point b){
	return a.x*b.x+a.y*b.y;
}

point getnode(edge a,edge b){//点向法计算线段交点，注意开 long double
	point va=a.s-a.t;
	point vb=b.s-b.t;
	long double S1=cross(a.s-b.s,vb);
	long double S2=cross(vb,va);
	return va*S1/S2+a.s;
}

bool check(edge a,edge b,edge c){
	point tmp=getnode(b,c);
	return cross(tmp,a.s,a.t)>=0;
}

point a[N],ins[N];
edge q[N];
edge e[N]; int cnt;
vector<int>be[N];
int vis[N];

void fake_main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		be[u].push_back(v);
		be[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		for(auto j:be[i]){
			vis[j]=1;
		}
		for(int j=n;j>i;j--){//找到最远的边
			if(!vis[j]){
				e[++cnt].s=a[i]; e[cnt].t=a[j];
				e[cnt].ang=atan2(a[j].y-a[i].y,a[j].x-a[i].x);
				break;
			}
		}
		for(auto j:be[i]){
			vis[j]=0;
		}
	}
	e[++cnt].s=a[n]; e[cnt].t=a[1]; e[cnt].ang=atan2(a[1].y-a[n].y,a[1].x-a[n].x);
	sort(e+1,e+cnt+1,[](edge a,edge b){//按照极坐标排序
		if(fabs(a.ang-b.ang)<=eps) return cross(a.s,b.s,b.t)<0;
		return a.ang<b.ang;
	});
	int tot=1;
	for(int i=2;i<=cnt;i++){
		if(fabs(e[i].ang-e[i-1].ang)>eps) e[++tot]=e[i];
	}
	int hd=2,bk=1;
	q[1]=e[1]; q[2]=e[2];
	for(int i=3;i<=tot;i++){//双端队列维护半平面交
		while(bk<hd&&check(e[i],q[hd],q[hd-1])) hd--;
		while(bk<hd&&check(e[i],q[bk],q[bk+1])) bk++;
		q[++hd]=e[i];
	}
	while(bk<hd&&check(q[bk],q[hd-1],q[hd])) hd--;
	while(bk<hd&&check(q[hd],q[bk],q[bk+1])) bk++;
	for(int i=bk;i<hd;i++){//找出每个交点
		ins[i-bk+1]=getnode(q[i],q[i+1]);
	}
	if(hd-bk>1) ins[hd-bk+1]=getnode(q[hd],q[bk]); long double ans=0;
	for(int i=1;i<=hd-bk+1;i++){//求边长
		ans+=dis(ins[i],ins[i%(hd-bk+1)+1]);
	}
	ans-=dis(a[1],a[n]);
	cout<<fixed<<setprecision(6)<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	fake_main();
}
```

---

## 作者：Toothless03 (赞：0)

~~来水一篇题解~~

![](https://cdn.luogu.com.cn/upload/image_hosting/6vz6e1ic.png)

显然路径 $A_1\to A\to B\to A_6$ 最短，可以想到最优路径就是沿着“最内侧”的边走，我们可以使用三角形两边之和大于第三边进行浅浅的证明~~我就不证了（逃~~。

而我们可以使用半平面交求解“最内侧”多边形，所以很容易想到链接 $A_1A_6$ ，这样就形成了一个封闭图形。但是 $O(n^2)$ 条边略微有辣么亿点点大，所以我们又发现了对于每个点，“最内侧”的边，一定是与其相连，另一端编号最大的边，所以当加边的时候可以先排一下序。答案就是交平面的周长减去 $A_1A_n$ 。

贴上代码
```cpp
namespace geometry {
	double pi = acos(-1);
	struct point {
		double x, y;
		point(double _x = 0, double _y = 0)
			: x(_x), y(_y) {}
		inline void read() {
			cin >> x >> y;
		}
		inline friend double dist(point a, point b) {
			double sq1 = (a.x - b.x), sq2(a.y - b.y);
			return sqrt(sqr(sq1) + sqr(sq2));
		}
		inline friend bool operator==(point a, point b) {
			return a.x == b.x && a.y == b.y;
		}
		inline friend bool operator!=(point a, point b) {
			return a.x != b.x || a.y != b.y;
		}
		inline friend point operator-(point a, point b) {
			return point(a.x - b.x, a.y - b.y);
		}
		inline friend point operator+(point a, point b) {
			return point(a.x + b.x, a.y + b.y);
		}
		inline friend double cross(point a, point b) {
			return a.x * b.y - a.y * b.x;
		}
		inline friend double dot(point a, point b) {
			return a.x * b.x + a.y * b.y;
		}
		inline friend point operator*(point a, double b) {
			return point(a.x * b, a.y * b);
		}
	};
	using line = pair<point, point>;
	double dist_sqr(point a, point b) {
		return sqr(a.x - b.x) + sqr(a.y - b.y);
	}
	inline double len(point p, point l, point r) {
		point x1 = l - p, x2 = r - p;
		return cross(x1, x2) / dist(l, r);
	}
	double c(double x) {
		if (x > 1)
			return 1;
		if (x < -1)
			return -1;
		return x;
	}
	inline double angle(point a, point b, point rt = point()) {
		return acos(c(dot(a - rt, rt - b) / dist(a, rt) / dist(b, rt)));
	}
	inline double check(point a1, point a2, point b1, point b2) {
		return (a2.x - a1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a2.y - a1.y);
	}
	vector<point> convex_hull(vector<point> p) {
		point g = p[0];
		for (int i = 1; i < p.size(); i++) {
			if (p[i].y < g.y || (p[i].y == g.y && p[i].x < g.x))
				g = p[i];
		}
		sort(p.begin(), p.end(), [&](point a, point b)->bool {
			double sum = cross(a - g, b - g);
			if (sum > 0)
				return true;
			if (sum < 0)
				return false;
			return dist(a, g) < dist(b, g);
			});
		vector<point> res(p.size());
		int cnt = -1;
		res[++cnt] = p[0];
		for (int i = 1; i < p.size(); i++) {
			while (cnt > 0 && check(res[cnt - 1], res[cnt], res[cnt], p[i]) <= 0)
				cnt--;
			res[++cnt] = p[i];
		}
		res.resize(cnt + 1);
		return res;
	}
	double diameter(vector<point> p) {
		int sz = p.size();
		if (sz < 3)
			return dist_sqr(p[0], p[(1) % sz]);
		int j = 2;
		double res = 0;
		p.push_back(p[0]);
		for (int i = 0; i < sz; i++) {
			while (cross(p[i + 1] - p[i], p[(j + 1) % sz] - p[i]) > cross(p[i + 1] - p[i], p[j] - p[i]))
				j = (j + 1) % sz;
			res = max(res, dist_sqr(p[i], p[j]));
		}
		return res;
	}
	point itsect(line a, line b) {
		return a.first + a.second * (cross(b.second, a.first - b.first) / cross(a.second, b.second));
	}
	bool right(line a, point b) {
		return cross(a.second, b - a.first) < EPS;
	}
	vector<point> plane(vector<line> v) {
		sort(v.begin(), v.end(), [&](line a, line b)->bool {
			return atan2(a.second.y, a.second.x) < atan2(b.second.y, b.second.x);
			});
		int l = 0, r = 0;
		vector<point> t(v.size());
		vector<line> q(v.size());
		q[0] = v[0];
		for (int i = 1; i < v.size(); i++) {
			while (l < r && right(v[i], t[r]))
				r--;
			while (l < r && right(v[i], t[l + 1]))
				l++;
			q[++r] = v[i];
			if (abs(cross(q[r].second, q[r - 1].second)) < EPS) {
				if (right(q[r], q[r - 1].first) && dot(q[r].second, q[r - 1].second) < EPS)
					return vector<point>();
				r--;
				if (!right(q[r], v[i].first))
					q[r] = v[i];
			}
			if (l < r)
				t[r] = itsect(q[r], q[r - 1]);
		}
		while (l < r && right(q[l], t[r]))
			r--;
		if (r - l <= 1)
			return vector<point>();
		t[l] = itsect(q[l], q[r]);
		return vector<point>(t.begin() + l, t.begin() + r + 1);
	}
	double area(vector<point> p) {
		if (p.size() <= 2)
			return 0;
		double res = 0;
		for (int i = 0; i < p.size() - 1; i++)
			res += cross(p[i], p[i + 1]);
		res += cross(p.back(), p[0]);
		return res / 2;
	}
	double circumference(vector<point> p) {
		if (p.size() < 2)
			return 0;
		if (p.size() == 2)
			return dist(p[0], p[1]);
		double res = 0;
		for (int i = 0; i < p.size() - 1; i++)
			res += dist(p[i], p[i + 1]);
		res += dist(p.back(), p[0]);
		return res;
	}
	double area(point p1, point p2, point p3) {
		return abs(cross(p1 - p3, p2 - p3)) / 2;
	}
}
using namespace geometry;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m; cin >> n >> m;
	vector<point> p(n);
	for (int i = 0; i < n; i++)
		p[i].read();
	vector<line> l;
	vector<vector<int>> dn(n);
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		--x, --y;
		if (x < y)
			swap(x, y);
		dn[x].push_back(y);
	}
	for (int i = 0; i < n; i++)
		sort(dn[i].begin(), dn[i].end());
	for (int i = 0; i < n; i++) {
		int j = 0, k = 0;
		for (j; j < i && k < dn[i].size(); j++, k++)
			if (dn[i][k] != j)
				break;
		if (j != i)
			l.push_back({ p[i], p[j] - p[i] });
	}
	l.push_back({ p.front(), p.back() - p.front() });
	vector<point> pla = plane(l);
	double ans = circumference(pla) - dist(p.front(), p.back());
	printf("%.5llf\n", ans);
	return 0;
}
```

---

