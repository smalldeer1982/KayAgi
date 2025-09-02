# Hobbits

## 题目描述

The hobbits Frodo and Sam are carrying the One Ring to Mordor. In order not to be spotted by orcs, they decided to go through the mountains.

The mountain relief can be represented as a polyline with $ n $ points $ (x_i, y_i) $ , numbered from $ 1 $ to $ n $ ( $ x_i < x_{i + 1} $ for $ 1 \le i \le n - 1 $ ). Hobbits start their journey at the point $ (x_1, y_1) $ and should reach the point $ (x_n, y_n) $ to complete their mission.

The problem is that there is a tower with the Eye of Sauron, which watches them. The tower is located at the point $ (x_n, y_n) $ and has the height $ H $ , so the Eye is located at the point $ (x_n, y_n + H) $ . In order to complete the mission successfully, the hobbits have to wear cloaks all the time when the Sauron Eye can see them, i. e. when there is a direct line from the Eye to the hobbits which is not intersected by the relief.

The hobbits are low, so their height can be considered negligibly small, but still positive, so when a direct line from the Sauron Eye to the hobbits only touches the relief, the Eye can see them.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468G/6125df61b8e9323ee46f8b93d743d2617a04d6a9.png)The Sauron Eye can't see hobbits when they are in the left position, but can see them when they are in the right position.The hobbits do not like to wear cloaks, so they wear them only when they can be spotted by the Eye. Your task is to calculate the total distance the hobbits have to walk while wearing cloaks.

## 样例 #1

### 输入

```
6 10
10 40
20 10
25 30
30 15
50 15
65 30```

### 输出

```
70.4034587602```

## 样例 #2

### 输入

```
9 5
0 0
5 10
15 10
20 0
25 11
30 0
35 10
50 10
60 5```

### 输出

```
27.2787986124```

## 样例 #3

### 输入

```
2 10000
0 10000
400000 0```

### 输出

```
400124.9804748512```

# 题解

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF1468G Hobbits](https://www.luogu.com.cn/problem/CF1468G)

## 解题思路

某个点能被光源照到，当且仅当从光源 $L$ 到该点之间没有被遮挡，即不存在其他点的斜率小于该点。因此，我们可以从后往前推，维护斜率最小的点 $a_k$。

特别地，最后一个线段一定能够被照到，因此可以直接计算，并将 $k \gets n-1$。

接下来对于每条线段 $a_ia_{i+1}$ 分类讨论：

1. 如果线段 $a_iL$ 的斜率大于 $a_kL$，说明该线段的左端点不能被光源照到，整个线段都无法被照到。
2. 求出线段 $a_ia_{i+1}$ 与线段 $a_kL$ 的交点 $P$，交点 $P$ 上方的线段 $a_iP$ 可以被光源照到。
3. 特别地，如果线段 $a_iL$ 的斜率等于线段 $a_{i+1}L$ 的斜率，表示该线段与光线重叠，整个线段都会被光源照到。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const double eps=1e-10;
const int N=200005;
int sgn(double x){return (x>eps)-(x<-eps);}
struct Point
{
	double x,y;
}a[N];
double Dis(Point A,Point B){return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
double Slope(Point A,Point B){return (A.y-B.y)/(A.x-B.x);}
Point Cross(Point A,Point B,Point C,Point D)
{
	double a1=A.y-B.y,b1=B.x-A.x,c1=A.x*B.y-B.x*A.y;
	double a2=C.y-D.y,b2=D.x-C.x,c2=C.x*D.y-D.x*C.y;
	return {(b1*c2-b2*c1)/(a1*b2-a2*b1),(a2*c1-a1*c2)/(a1*b2-a2*b1)};
}
int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	return x*f;
}
int main()
{
	int n,h;
	cin>>n>>h;
	for(int i=1;i<=n;i++)
	{
		a[i].x=read();
		a[i].y=read();
	}
	Point L={a[n].x,a[n].y+h};
	int k=n-1;
	double ans=Dis(a[n-1],a[n]);
	for(int i=n-2;i>=1;i--)
	{
		if(sgn(Slope(a[i],L)-Slope(a[k],L))>0)continue;
		ans+=Dis(a[i],sgn(Slope(a[i],L)-Slope(a[i+1],L))==0?a[i+1]:Cross(a[i],a[i+1],a[k],L));
		k=i;
	}
	cout<<fixed<<setprecision(10)<<ans<<'\n';
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

这道题非常的水，可能是很多人看到计算几何就弃了所以 AC 比 A 少吧。

每一次，我们只用找到最高的点，也就是说，在 $i$ 之后与眼睛构成斜率最小的点与当前线相交求交点。

这里是暴力解直线交点的做法，可以看一下具体实现。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
const int Mxdt=100000;	//单次大小
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline char pc(char ch,bool bj){
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return (bj||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
inline int read(){
	re int t=0;re char v=gc();
	while(v<'0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
inline double dis(re double a,re double b,re double c,re double d){
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}
struct point{double x,y;}p[200002],eye,h;
double ans;
inline double slope(re point x,re point y){
	return (y.y-x.y)/(y.x-x.x);
}
inline point cross(re point a,re point b,re point c,re point d){
	if(b.x==h.x)return b;
	double k2=(d.y-c.y)/(d.x-c.x),k1=(b.y-a.y)/(b.x-a.x),b1=a.y-a.x*k1,b2=c.y-c.x*k2;
	point s;
	s.x=(b2-b1)/(k1-k2);
	return (point){s.x,s.x*k1+b1};
}
int n,m,stk[200002],tp;
int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i)p[i].x=read(),p[i].y=read();
	eye.x=p[n].x,eye.y=p[n].y+m,h=p[n];
	for(re int i=n-1;i;--i){
		if(slope(p[i],eye)<=slope(h,eye)){
			point x=cross(p[i],p[i+1],h,eye);
			ans+=dis(p[i].x,p[i].y,x.x,x.y);
			h=p[i];
		}
	}
	printf("%.9lf",ans);
}

```


---

## 作者：shinkuu (赞：0)

如果我没犯那些神必错误还是很轻松的……

考虑 $(x_n,y_n+H)$ 和 $(x_i,y_i)$ 所连成的直线，折线在这些直线中的某条的下面，则一定不会被看到。这些直线中限制最强的一定是斜率最小的，所以记录后缀斜率最小的直线记作 $f_i$。

然后有些线段是一定不行的 $(k<k_{f_i})$。否则就可以做一个直线之间求交点的操作寻找线段上会被看到和不会之间的分界线，再计算一下长度即可。

一定要想清楚是哪条直线和哪条啊……

使用分数类，不用担心精度。但是这题本来就不卡，我也不知道我脑子是怎么了一开始写了一个甚至会被卡精度的做法。

code：

```cpp
int n;
#define lll __int128
struct frac{
	lll a,b;
	frac(lll _a=0,lll _b=1):a(_a),b(_b){if(b<0)a*=-1,b*=-1;}
	il bool operator<(const frac &rhs)const{return (lll)a*rhs.b<(lll)rhs.a*b;}
	il bool operator>(const frac &rhs)const{return rhs<(*this);}
	il bool operator==(const frac &rhs)const{return (lll)a*rhs.b==(lll)rhs.a*b;}
	il frac operator+(const frac &rhs)const{return frac(a*rhs.b+rhs.a*b,b*rhs.b);}
	il frac operator-(const frac &rhs)const{return (*this)+frac(-rhs.a,rhs.b);}
	il frac operator*(const frac &rhs)const{return frac(a*rhs.a,b*rhs.b);}
	il frac operator/(const frac &rhs)const{return (*this)*frac(rhs.b,rhs.a);}
	il long double Val(){return (long double)a/b;}
}m,a[N],b[N],f[N],g[N];
il frac slope(frac x1,frac y1,frac x2,frac y2){return (y2-y1)/(x2-x1);}
il double slope(double x1,double y1,double x2,double y2){return (y2-y1)/(x2-x1);}
void Yorushika(){
	int _m;scanf("%d%d",&n,&_m),m.a=_m;
	rep(i,1,n){
		ll x,y;scanf("%lld%lld",&x,&y);
		a[i].a=x,b[i].a=y;
	}
	f[n]=frac(1ll*inf*inf,1),m=m+b[n],g[n]=frac()-f[n];
	drep(i,n-1,1){
		frac x=slope(a[i],b[i],a[n],m);
		if(x<f[i+1])f[i]=x,g[i]=b[i]-x*a[i];
		else f[i]=f[i+1],g[i]=g[i+1];
	}
	long double ans=0;
	rep(i,1,n-1){
		if(slope(a[i],b[i],a[n],m)>f[i+1])continue;
		frac k=slope(a[i],b[i],a[i+1],b[i+1]),t=b[i]-k*a[i],nx;
		if(k==f[i+1]||i==n-1)nx=a[i+1];
		else nx=(g[i+1]-t)/(k-f[i+1]);
		nx=max(min(nx,a[i+1]),a[i]);
		frac len=nx-a[i];
		long double x=len.Val(),y=k.Val();
		ans+=sqrtl(x*x+x*x*y*y);
	}
	printf("%.8Lf\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：ChuTian (赞：0)

# 题意：
在二维平面上面有$n$个点$(x_1,y_1),(x_2,y_2),\cdots,(x_n,y_n)$，相邻的点连一段线段，组成一个折线。有一个眼睛在点$(x_n,y_n+H)$上，求从这点能够看到不被遮挡的线段总长度为多少。
# 思路：
我们可以看到，如果一条线段或者它的一部分不能够被看到，那么它一定会被后面的某些线段所影响，也就是后面的更高的点会遮挡住前面的线段。那么，我们可以发现，如果判断一条线段会不会被遮挡，我们需要关注这条线段的后面最高的点。所以我们只要从后往前遍历，判断线段和迭代最高点就可以了。

那么我们接下来就需要判断一条线段是否能够被看见了。我们设眼睛在的点为  $E$，最高点为 $M$。我们可以考虑一点 $P$ ，如果 $P$ 在 $\overrightarrow{EM}$ 的右边（顺时针方向），那么他就可以被看到，反正，它就会被遮挡。那么对于线段 $(P_i,P_{i+1})$ ，我们判断 $P_i$ 和 $P_{i+1}$ 和 $\overrightarrow{EM}$ 的关系。

1、 $P_i$ 和 $P_{i+1}$ 都可以被看到，那么长度加上 $dis(P_i,P_{i+1})$。

2、 $P_i$ 被看见， $P_{i+1}$ 不被看见，那么我们求出 $EM$ 和 $P_iP_{i+1}$ 的交点 $Q$ ，长度加上 $dis(P_i,Q)$。

3、 $P_i$ 和 $P_{i+1}$ 都不被看见，就不用加上这段的距离。

为什么不用考虑 $P_i$ 不被看见， $P_{i+1}$ 被看见的情况？因为如果不可能出现这种情况。如果 $P_i$ 在 $\overrightarrow{EM}$ 的左边， $P_{i+1}$ 在 $\overrightarrow{EM}$ 的右边，那么 $\overrightarrow{EM}\times\overrightarrow{EP_{i+1}}\le 0$ ,那么在前一步枚举 $i+1$ 的时候，$M$就会被迭代掉。

最后就是需要迭代最高点，注意的是。最高点**并不是** $y_{max}$ 的点。我们设从 $x$ 轴的正方向顺时针到 $\overrightarrow{EP}$ 的角度为 $\alpha$,$\alpha_{max}$ 的点是最高点。也就是我们判断一个点 $P$ 如果在 $\overrightarrow{EM}$ 的右边（顺时针方向），那么就将 $P$ 替换最高点 $M$。

总结就是：从后向前遍历，判断线段端点 $P_i$ 和 $P_{i+1}$ 与 $\overrightarrow{EM}$ 的关系，计算距离。迭代最高点 $M$。
# 代码：

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define cl(x,y) memset(x,y,sizeof(x))
#define ct cerr<<"Time elapsed:"<<1.0*clock()/CLOCKS_PER_SEC<<"s.\n";
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
#define INF 1e18
const int N=1e6+10;
const int mod=1e9+7;
const double inf=1e18;
const double eps=1e-8;
const double pi=acos(-1);
using namespace std;
int n,top;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0) return -1;
    else return 1;
}
struct point
{
    double x,y;
    point(){}
    point(double xx,double yy){x=xx;y=yy;}
    point operator +(point b){return point(x+b.x,y+b.y);}
    point operator -(point b){return point(x-b.x,y-b.y);}
    double operator ^(point b){return x*b.y-y*b.x;}//叉乘 
    double operator *(point b){return x*b.x+y*b.y;}//点乘 
    point operator *(double b){return point(x*b,y*b);}//数乘   
    void read(){scanf("%lf%lf",&x,&y);}
}p[N];
struct line
{
    point s,e,l;
    line(){}
    line(point ss,point ee){s = ss;e = ee;l=e-s;}
    double gettan(){return atan2(e.y-s.y,e.x-s.x);}
};
double dis(point a,point b)
{
	return sqrt((a-b)*(a-b));
}
point getcross(line l1,line l2)
{
	double s1=((l2.s-l1.s)^(l2.e-l1.s));
	double s2=((l2.e-l1.e)^(l2.s-l1.e));
	if(s1+s2==0)//平行 
		return point{inf,inf};
	return l1.s+l1.l*(s1/(s1+s2));
}
int main()
{
	int i;
	double h;
	scanf("%d%lf",&n,&h);
	for(i=1;i<=n;i++)
		p[i].read();		
	double sum=0;
	point mx=p[n],eye={p[n].x,p[n].y+h};
	for(i=n-1;i>=1;i--)
	{
		point ju=mx-eye,p1=p[i]-eye,p2=p[i+1]-eye;
		int f1=((ju^p1)<=0),f2=((ju^p2)<=0);
		if(f1 && f2)
			sum+=dis(p[i],p[i+1]);			
		else if(f1 && !f2)
		{
			point g=getcross(line{eye,mx},line{p[i],p[i+1]});
			sum+=dis(g,p[i]);
		}
		if(f1)
			mx=p[i];
	}
	printf("%.9lf\n",sum);
	return 0;
}
```



---

