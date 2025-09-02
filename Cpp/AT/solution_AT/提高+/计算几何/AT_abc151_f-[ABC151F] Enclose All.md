# [ABC151F] Enclose All

## 题目描述

给定平面上的 $N$ 个点 $(x_i, y_i)$。

请你求出能够将这 $N$ 个点全部包含在其内部或边界上的圆的最小半径。

## 说明/提示

## 限制条件

- $2 \leq N \leq 50$
- $0 \leq x_i \leq 1000$
- $0 \leq y_i \leq 1000$
- 给定的 $N$ 个点互不相同
- 输入中的所有值均为整数

## 样例解释 1

两个点可以被以 $(0.5, 0)$ 为圆心、$0.5$ 为半径的圆包含。

## 样例解释 3

如果你的输出与标准答案的绝对误差或相对误差不超过 $10^{-6}$，则视为正确。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
0 0
1 0```

### 输出

```
0.500000000000000000```

## 样例 #2

### 输入

```
3
0 0
0 1
1 0```

### 输出

```
0.707106781186497524```

## 样例 #3

### 输入

```
10
10 9
5 9
2 0
0 0
2 7
3 3
2 5
10 0
3 7
1 9```

### 输出

```
6.726812023536805158```

# 题解

## 作者：BqtMtsZDnlpsT (赞：5)

计算几何。

笔者较菜，不会随机增量法，参见 [P1742 最小圆覆盖](https://www.luogu.com.cn/problem/P1742)

$\large\text{Solution}$

首先有一个的性质：至少两个点在最小圆上。（大概就是先让一个极大的圆靠在一个点上，然后不断缩小至靠到另一个点上）。

然后我们又发现如果只有两点在圆上，那么这两点间的线段必定是直径，否则圆定然经过第三点（可以想象一下经过两个点的圆半径不断缩小直到经过第三点）。

然后直接分类讨论，讨论完后就可以判断每个点是否在圆内。

设答案半径为 $r$，圆心坐标为 $O(x,y)$，$dis(X,Y)$ 表示平面直角坐标系中点 $X,Y$ 间的距离。

- 圆上有两个点，坐标分别为 $A(x_1,y_1),B(x_2,y_2)$。

则圆心显然为这两点中点 $O(\frac{x_1+x_2}{2},\frac{y_1+y_2}{2})$。

半径为两点间距离的一半 $\frac{dis(A,B)}{2}$。

- 圆上有三个（及以上）点，坐标分别为 $A(x_1,y_1),B(x_2,y_2),C(x_3,y_3)$。

考虑到圆心到三点距离相等，所以问题转化为求到三点距离相等的点，即求三角形外心，做其中任意两组点间中垂线即可。

如下图：

![](https://z3.ax1x.com/2021/10/26/5o77Vg.png)

一个细节：如果算出来的线平行于 $y$ 轴，要进行一些特判，以避免出现未定义数。

代码有些简化，可以参考注释。

代码：

```cpp
int n;
long double x[55],y[55],ans;
#define sqr(x) ((x)*(x))
const long double eps=1e-7;
long double dis(long double x,long double y,long double u,long double v){
	return sqrt(sqr(x-u)+sqr(y-v));
}
long double fxabs(long double k){
	return k<0.0?-k:k;
}
void work(int a,int b,int c){//三点
	long double p=x[a],q=y[a],r=x[b],s=y[b],t=x[c],u=y[c];
	if(fxabs(u-s)<eps)swap(s,q),swap(p,r);//如果所算两点的纵坐标相等，则交换，避免未定义数的情况
	if(fxabs(q-s)<eps)swap(s,u),swap(t,r);
	if(fxabs(u-s)<eps)return;
	if(fxabs(q-s)<eps)return;
	long double l1k=-(r-p)/(s-q),l2k=-(t-r)/(u-s);//求中垂线的斜率，根据一直线斜率于其中垂线斜率互为负倒数
	long double dx1=(p+r)/2.0,dy1=(q+s)/2.0;
	long double dx2=(r+t)/2.0,dy2=(s+u)/2.0;//求两中垂线过的两个中点
	long double l1b=dy1-dx1*l1k,l2b=dy2-dx2*l2k;
	if(fxabs(l1k-l2k)<eps)return;//两直线平行
	long double tx=(l2b-l1b)/(l1k-l2k),ty=tx*l1k+l1b,d=dis(p,q,tx,ty);
	if(d-ans>eps)return;
	for(int i=1;i<=n;i++)//判断其余点是否在圆内
		if(dis(tx,ty,x[i],y[i])-d>eps)return;
	ans=d;
}
void work1(int a,int b){//两点
	long double p=x[a],q=y[a],r=x[b],s=y[b];
	long double tx=(p+r)/2.0,ty=(q+s)/2.0,d=dis(p,q,r,s)/2.0;
	if(d-ans>eps)return;
	for(int i=1;i<=n;i++)
		if(dis(tx,ty,x[i],y[i])-d>eps)return;
	ans=d;
}
signed main(){
	n=read();ans=1e18;
	for(int i=1;i<=n;i++)scanf("%Lf%Lf",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++){
				work(i,j,k);
			}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			work1(i,j);
	printf("%.15Lf",ans);
}
```

---

## 作者：小小小朋友 (赞：2)

### 题目描述

给定一些点，求最小的可以把所有点都覆盖个的圆的半径

### 思路

什么乱七八糟的计算几何解析几何？都不会……

但我们发现了一些有意思的事情……

- 精确到小数点后6位

- 最多只有50个点

- 坐标最大1000

于是我们想到枚举圆心坐标

当然这明显是不行的

所以我们来用**模拟退火**

这题退火可跑的飞快，因为只有50个点，枚举一遍非常快

解释见注释

### 代码
```cpp
#include<bits/stdc++.h>
#define double long double//强行提高精度
using namespace std;
struct node{
	double x,y;
}a[105];
int n;
double ansx,ansy,sy=0,sx=0;
double ans=2000,t;
double del=0.9995; //这个系数不算低，但是稳
inline double dis(node aa,node bb){
	return sqrt((aa.x-bb.x)*(aa.x-bb.x)+(aa.y-bb.y)*(aa.y-bb.y));
}//求欧几里得距离，用来看这个点里目前的圆心多远
double calc(double x,double y){
	double ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dis((node){x,y},a[i]));
	}
	return ans;
}//计算出若圆心在此处需多大半径
void SA(){//模拟退火
	double x=ansx,y=ansy;
	t=2000;//初温2000
	while(t>1e-14){//精细的降温
		double X=x+((rand()<<1)-RAND_MAX)*t;//随机得到一个x
		double Y=y+((rand()<<1)-RAND_MAX)*t;//随机得到一个y
		double now=calc(X,Y);
    	double Delta=now-ans;//查看差值
    	if(Delta<0){//接受这个新解
    		x=X,y=Y;
    		ans=now;
		}
		else if (exp(-Delta/t)*RAND_MAX>rand()) x=X,y=Y;
        //以一定概率接受这个新解
        t*=del;
	}
}
int main(){
	int cnt=0;
	srand(1000211237);//设置种子
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		sx+=a[i].x,sy+=a[i].y;
	}
	ansx=(double)sx/n,ansy=(double)sy/n;
	while((double)clock()/CLOCKS_PER_SEC<0.93) SA(),cnt++;
    	//压线多次退火
	printf("%.14Lf",ans);//输出最后答案
	return 0;
}

```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
题目可理解为，有若干已知点，找一个点，让此点与已知点的最大距离最小。  
如果我们要枚举的话，此点坐标可能是小数，那么，枚举数量就过于庞大了，运行时间远远超过此题时间限制。  
故我们考虑随机化算法，有模拟退火和爬山可供选择，此题较难证明，也可能无法证明答案为单峰函数，所以保险起见，我使用模拟退火算法。
## 2. 题目做法
这道题打模拟退火板子就行了，只要稍微调下参数，就能轻松过掉此题。  
我们先选定一个退火的初始坐标，作为我们搜索答案的起点，先看题目数据范围，每个点的 $x$ 和 $y$ 都大于等于  $0$ 且小于等于 $1000$，那么我们可以很轻易的看出，任何不在此数据范围内的点，一定不是答案点，因为在数据范围内一定有点优于外点。所以我们选择横纵坐标都为 $500$ 的点作为起始点。  
然后，我们的初始温度 $T$ 不能定义太大，定义为 $1000$ 就差不多了，数据范围就那么大。以温度作为随机跳点的距离，找到下一个判定点，若更优则一定替换，较劣则概率替换。  
至于降温系数，大家可以根据自己的代码慢慢调，如此便可完成此题。
## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
typedef pair<double,double> P;
int n;
double ans=INT_MAX;
P a[N];
inline double rand(double l,double r)//自写随机函数
{
	return (double)rand()/RAND_MAX*(r-l)+l;
}
inline double dis(P a1,P a2)//求两点之间距离
{
	return sqrt(pow(a1.first-a2.first,2)+pow(a1.second-a2.second,2));
}
inline double maxx(P a1)//求一点到已知点的最大距离
{
	double s=0;
	for(int i=1;i<=n;i++)
		s=max(s,dis(a1,a[i]));
	s<ans?ans=s:1;
	return s;
}
P a1,a2;
double T,dt,now,fu;
void SA()//模拟退火
{
	T=1e4;
	while(T>1e-9)
	{
		a2={rand(a1.first-T,a1.first+T),rand(a1.second-T,a1.second+T)};
		fu=maxx(a2);
		dt=now-fu;
		if(exp(dt/T)>rand(0,1))
			now=fu,a1=a2;
		T*=0.999992;
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]={read(),read()};
	a1={500,500};
	now=maxx(a1);
	SA();
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)


简单计算几何题。不知道为什么能紫？

做法很简单，即最小覆盖圆一定经过 $2$ 或 $3$ 个点，鉴于有其他题解就不再赘述。

主要讲一下解决斜率不存在的处理方法： **将初始的所有点随机旋转一定角度，这样的话斜率就可以认为是一定存在的了，而且对答案不会有影响。**可以避免一些麻烦。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps=1e-8;
const double inf=1e7;
const double Pi=3.1416;
const double alpha=5.364/9.278*Pi;
struct point {
	double x,y;
}po[55];
struct line {
	double k,b;
}q1,q2;
int n;
double rad;
double ans=inf;
inline double dis(point a,point b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double xx,yy;
inline double slope(point a,point b){
	return (a.y-b.y)/(a.x-b.x);
}
inline point cross(line a,line b){
	point r;
	r.x=(a.b-b.b)/(b.k-a.k);
	r.y=a.k*r.x+a.b;
	return r;
}
inline line make_line(point a,double slo){
	line r;
	r.k=slo;
	r.b=a.y-r.k*a.x;
	return r;
}
inline point find_mid(point a,point b){
	point t;
	t.x=(a.x+b.x)/2.00000000;
	t.y=(a.y+b.y)/2.00000000;
	return t;
}
int main(){
	scanf("%d",&n);
	double x,y;
	line l1,l2;
	point c,O;
	for(int i=1;i<=n;++i) scanf("%lf%lf",&po[i].x,&po[i].y);
	for(int i=1;i<=n;++i){
		x=po[i].x*cos(alpha)-po[i].y*sin(alpha);
		y=po[i].y*cos(alpha)+po[i].x*sin(alpha);
		po[i].x=x,po[i].y=y;
	}
	point c1,c2;
	if(n==2){
		printf("%.10f\n",sqrt(dis(po[1],po[2]))/2.000000000);
		return 0;
	}
	else {
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				for(int k=j+1;k<=n;++k){
					c1=find_mid(po[i],po[j]);
					c2=find_mid(po[i],po[k]);
					l1=make_line(c1,-1.00000000/slope(po[i],po[j]));
					l2=make_line(c2,-1.00000000/slope(po[i],po[k]));
					O=cross(l1,l2);
					int fl=1;
					rad=dis(O,po[i]);
					if(rad>inf || rad<-inf) continue;
					for(int lo=1;lo<=n;++lo) 
				    	if(dis(O,po[lo])-rad>eps) fl=0;
					if(fl) ans=min(ans,sqrt(rad));
				}
		for(int i=1;i<=n;++i){
			for(int j=i+1;j<=n;++j){
				rad=dis(find_mid(po[i],po[j]),po[i]);
				int fl=1;
				for(int k=1;k<=n;++k)
					if(dis(find_mid(po[i],po[j]),po[k])-rad>eps) fl=0;
				if(fl) ans=min(ans,sqrt(rad));
			}
		}
	}
	printf("%.10lf\n",ans);
	return 0;
}
```




---

## 作者：_AyachiNene (赞：1)

# 思路：
这种计算题一看就可以用模拟退火，很容易想到用模拟退火枚举圆心。这时唯一的问题就是圆的半径怎么算。因为圆心到圆的边上任意一点的距离都相等，所以最小的半径一定就是圆心到最远一点的距离，这样就能覆盖全部的点。那么代码不能写出。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[114514],y[114514];
double n,ansx,ansy,ans;
double f(double nx,double ny)     //最远一点的距离 
{
    double res=0,dx,dy;
    for(int i=1;i<=n;i++)
    {
    	dx=nx-x[i];
    	dy=ny-y[i];
  		res=max(res,sqrt(dx*dx+dy*dy));
   	}
    return res;
}
void sa()  //模拟退火 
{
	double t=1145*3;
	while(t>=1e-16)
	{
		double nowx,nowy,now,del;
		nowx=(rand()*2-RAND_MAX)*t+ansx;        //随机一个点 
		nowy=(rand()*2-RAND_MAX)*t+ansy;
		now=f(nowx,nowy);
		if(now<ans) 
			ansx=nowx,ansy=nowy,ans=now;    //更新答案 
		else if(exp(-(now-ans)/t)*RAND_MAX>rand())
			ansx=nowx,ansy=nowy;
		t*=0.995;
	}
}
int main()
{
	srand(time(NULL)); 
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i],ansx+=x[i],ansy+=y[i];
	ansx/=n,ansy/=n;
	ans=f(ansx,ansy);   //初始答案 
	for(int i=1;i<=50;i++)
		sa();
	printf("%.10lf",ans);
}
```


---

## 作者：Sunrise_beforeglow (赞：0)

此题我们可以使用模拟退火来做，因为此题数据范围较小且精度要求不高。

这里简单介绍一下模拟退火，当我们使用爬山算法时，很容易陷入局部最优解出不来，于是，模拟退火应运而生。

具体的，它有一个温度函数 $t$，每次会降一点温度，我们随机出一个解，算出它的答案，若我的答案更优，那么接收。否则有 $e^{\frac{-\Delta E}{t}}$ 的概率接受答案，其中 $\Delta E$ 是我的当前答案与现在答案的差值。

不难发现，随着温度越来越低，我跳动的幅度也越来越小。

这里引用 OI-wiki 的一张图片：

![](https://oi-wiki.org/misc/images/simulated-annealing.gif)

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{int x,y,w;};
node a[1010];
int n,sx,sy;
double ansx,ansy;
double ans=1e18,t;
const double d=0.998;
double calc(double x,double y)
{
	double rt=0;
	for (int i=1;i<=n;i++) 
	{ 
		double dx=x-a[i].x,dy=y-a[i].y;
		rt=max(rt,sqrt(dx*dx+dy*dy));
	}
	return rt; 
}
void SA()
{
	double x=ansx,y=ansy;
	t=2000;
	while(t>1e-14)
	{
		double X=x+(rand()*2-RAND_MAX)*t;
		double Y=y+(rand()*2-RAND_MAX)*t;
		double now=calc(X,Y);
		double delta=now-ans;
		if(delta<0)
		{
			x=X,y=Y;
			ansx=X,ansy=Y,ans=now;
		}
		else if(exp(-delta/t)*RAND_MAX>rand())x=X,y=Y;
		t*=d;
	}
}
void solve()
{
	ansx=(double)sx/n,ansy=(double)sy/n;
    while((double)clock()/CLOCKS_PER_SEC<0.9)SA();
}
int main()
{
	srand(time(0));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		sx+=a[i].x,sy+=a[i].y;
	}
	solve();
	printf("%.18lf",calc(ansx,ansy));
	return 0;
}
```

---

## 作者：___QAQ__ (赞：0)

# 题意
题目里说得很清楚了，找到一个半径最小的圆以覆盖 $N$ 个点。
# 思路
精度要求很低，直接模拟退火。
# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
mt19937 myrand(time(0));
#define urd uniform_real_distribution<>

const int MAXN = 55;

int n;
double ans, ansx, ansy, x[MAXN], y[MAXN];

double dist(double x, double y, double xx, double yy){
  return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}

double calc(double nowx, double nowy){
  double cnt = 0;
  for(int i = 1; i <= n; i++){
    cnt = max(cnt, dist(nowx, nowy, x[i], y[i]));
  }
  return cnt;
}

void SA(){
  double t = 2000, d = 0.999, now = ans, nowx = ansx, nowy = ansy;
  while(t > 1e-18){
    double nxtx = nowx + urd(-10, 10)(myrand) * t, nxty = nowy + urd(-10, 10)(myrand) * t, nxt = calc(nxtx, nxty), delta = nxt - now;
    if(nxt < ans){
      ans = nxt, ansx = nxtx, ansy = nxty;
    }
    if(exp(-delta / t) > urd(0.0, 1.0)(myrand)){
      now = nxt, nowx = nxtx, nowy = nxty;
    }
    t *= d;
  }
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  ansx = 0, ansy = 0;
  for(int i = 1; i <= n; i++){
    cin >> x[i] >> y[i];
    ansx += x[i], ansy += y[i];
  }
  ansx /= n, ansy /= n;
  ans = calc(ansx, ansy);
  while((double)clock() / CLOCKS_PER_SEC < 0.99){
    SA();
  }
  cout << fixed << setprecision(18) << ans;
  return 0;
}
```

---

## 作者：___w (赞：0)

[[ABC151F] Enclose All](https://www.luogu.com.cn/problem/AT_abc151_f)

[P1742](https://www.luogu.com.cn/problem/P1742) 原题。

当然有简单的方法：首先我们要知道当 $N\ge2$ 时答案的圆只能过两个点或三个点，且注意到 $N\le50$，所以我们可以枚举外接圆是哪些点的外接圆，然后枚举判断是否在园内。

复杂度为 $O(N^4)$。

代码：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
inline ll rdll() { ll x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

const int N = 1e5+5;
const double eps = 1e-4, pi = acos(-1);

int sgn(double x) { return fabs(x) < eps ? 0 : x > 0 ? 1 : -1; }

struct point {
	double x, y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	point operator + (const point &b) const { return point(x+b.x, y+b.y); }
	point operator - (const point &b) const { return point(x-b.x, y-b.y); }
	point operator * (const double &k) const { return point(x*k, y*k); }
	point operator / (const double &k) const { return point(x/k, y/k); }
} p[N];

double dot(point a, point b) { return a.x*b.x+a.y*b.y; }
double crs(point a, point b) { return a.x*b.y-b.x*a.y; }
double len(point a) { return sqrt(a.x*a.x+a.y*a.y); }
point rotate(point p, point q, double x) { return point((p.x-q.x)*cos(x)-(p.y-q.y)*sin(x)+q.x, (p.x-q.x)*sin(x)+(p.y-q.y)*cos(x)+q.y); } //点p绕点q顺时针旋转x 
point get(point a, point b, point c, point d) {
	double x = crs(c-a, d-a), y = crs(d-b, c-b);
	return a+(b-a)*x/(x+y);
}
point circle(point a, point b, point c) {
	point x = (a+b)/2, y = (b+c)/2;
	return get(x, rotate(a, x, pi/2), y, rotate(b, y, pi/2));
}

int main() {
	int n = rd(); double r, ans = 1e9; point o;
	for (int i = 1; i <= n; ++i) p[i].x = rd(), p[i].y = rd();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k <= n; ++k) {
				o = circle(p[i], p[j], p[k]), r = len(p[i]-o);
				bool flag = 1;
				for (int u = 1; u <= n; ++u) flag &= sgn(r-len(p[u]-o)) >= 0;
				if (flag) ans = min(ans, r);
			}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			o = (p[i]+p[j])/2, r = len(p[i]-o);
			bool flag = 1;
			for (int u = 1; u <= n; ++u) flag &= sgn(r-len(p[u]-o)) >= 0;
			if (flag) ans = min(ans, r);
		}
	printf("%.12lf", ans);
	return 0;
}
```

---

## 作者：Slient_QwQ (赞：0)

大家好，我是一个不会计算几何的萌新，我喜欢随机化算法，所以我用 SA 水过去了。

## Mean Meaning

题目说的很简洁了。。

## Solution

这里先讲一下什么是模拟退火。

>退火：将金属加热到一定温度，保持足够时间，然后以适宜速度冷却（通常是缓慢冷却，有时是控制冷却）的一种金属热处理工艺。——摘自百度

模拟退火就是像退火的过程一样，慢慢去寻找答案。

我们有一个初始温度 $T$ 和降温系数 $delta$，然后不断降温到某个温度 $d$，这时停止降温。

在降温过程中，我们有若干个答案，如果这个答案比当前答案更优就选择，否则以多项式概率接受。

这里给出这个过程：

```cpp
E = now - ans;

if (E < 0)ansx = X, ansy = Y, ans = now;
else if (exp(-E / T) * RAND_MAX > rand())ansx = X, ansy = Y;
```

大家可以先做板子[吊打XXX](https://www.luogu.com.cn/problem/P1337)，再来做这题，发现就是跟板子差不多。

[Code](https://atcoder.jp/contests/abc151/submissions/52024461)

---

## 作者：xxxxxzy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc151_f)

从 [P1742最小圆覆盖](https://www.luogu.com.cn/problem/P1742#submit) 过来，这道题对于精度的要求较低，所以可以用模拟退火做。

退火只需要维护圆心的坐标即可，接下来的就是模拟退火板子，就不多说。

该说的都在代码里了。


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define delta 0.971
int n,f;
long double dx[100005],dy[100005],ansx,ansy,ans=1e15,tmp;
long double d(double x,double y,double x2,double y2){//两点距离的平方
	return (x-x2)*(x-x2)+(y-y2)*(y-y2);
}
void ask(double x,double y){//询问当以(x,y) 为圆心时半径的值
	tmp=-1;
	for(int i=0;i<n;i++){
		long double j=d(x,y,dx[i],dy[i]);
		j=sqrt(j);
		if(j>tmp) tmp=j,f=i;
	}
}
void begin(){//模拟退火
	long double t=30000;
	while(t>1e-18){//其实不需要这么高的精度
		ask(ansx,ansy);
		ans=min(ans,tmp);
		ansx+=(dx[f]-ansx)*t/tmp,ansy+=(dy[f]-ansy)*t/tmp;
		t*=delta;
	}
}
signed main(){
    srand(1e9+7);
	cin>>n;
	double sum1=0,sum2=0;
	for(int i=0;i<n;i++) scanf("%Lf%Lf",&dx[i],&dy[i]),sum1+=dx[i],sum2+=dy[i];
	ansx=sum1/n,ansy=sum2/n;//取平均值确定初始状态
	ask(ansx,ansy);
	ans=tmp;
	while((double)clock()/CLOCKS_PER_SEC<0.5) begin();
	printf("%.11Lf",ans);
} 
```

---

## 作者：木棉絮123 (赞：0)

## 题意简述：
给定 $n$ 个点（$n\le 50$），求最小覆盖园的半径。
## 简要思路:
正解是[随机增量法](https://oi.wiki/geometry/random-incremental/)，但发现 $n$ 的范围较小（$n\le50$），可用[模拟退火](https://oi.wiki/misc/simulated-annealing/)。每次退火在原有“圆心”的基础上随机移动一个距离，求解其与给定点的距离最大值。

不难发现，当这个最大值最小时，这个“圆心”会很接近真实的圆心，输出答案即可。
## 代码片段：
为了代码简洁，已省略无关片段。
```cpp
namespace sa
{
	int n;
	ld ans=1e5,s;
	point p[MAX],o0;
	//点类，存储给定点和一开始的圆心
	void init(){
		s=rand_double(0,3.14159);
		cin>>n;
		ld x=0,y=0;
		fo(i,1,n){
			p[i]=point(2);
			p[i].spin_2(s);
			//读入一个点，并且随机旋转 s
			x+=p[i].pos[0],y+=p[i].pos[1];
		}
		x/=n;y/=n;
		o0=point(x,y);
		//计算一开始的圆心
	}
	ld get(point o)//计算 传入的圆心和给定点距离的 最大值{
		ld dis=0;
		fo(i,1,n) dis=max(dis,o*p[i]);//o*p[i] -> o与p[i]的欧拉距离
		ans=min(ans,dis);//trick 1:答案在check函数更新，避免取到较劣解
		return dis;
	}
	void sim_anel(){
		ld t = 2500,r,minr;
		//定义温度，半径和退火时搜到的最小半径
		constexpr ld delta = 0.9996,eps=1e-17;
		//定义退火系数，最小温度，并计算初始的半径
		r=minr=get(o0);
		while (t > eps){
			point o1=point(o0.pos[0]+t*rand_double(-100,100)
           			 ,o0.pos[1]+t*rand_double(-100,100));
			r=get(o1);
			//得到新点，计算新点的半径，判断是否更新
			ld dt = r - minr;
			//如果 新点的半径 更小，更新最小半径并将旧点设置为新点
			if (dt < 0) {
				minr = r;
				o0=o1;
			} else if (exp(1.0 * -dt / t)*1000.0 > rand_int(1, 1000) ) {
			//否则以一定概率将旧点设置为新点
				o0=o1;
			}
			t *= delta;
		}
		
	}
	void main() {
		init();
		while(clock()/CLOCKS_PER_SEC < 0.65){
			//trick 2:卡时，增大答案为正解的可能性
			sim_anel();
		}
		printf("%.18Lf",ans);
	}
}
```

---

## 作者：Zak_chen (赞：0)

原题链接：[[ABC151F] Enclose All](https://www.luogu.com.cn/problem/AT_abc151_f)

这道题可以看做是 [P1742 最小圆覆盖](https://www.luogu.com.cn/problem/P1742)的弱化版，因为 $n\le50$ 数据范围极小。

既然那道题退火过不了，那就用退火写这道题：

### 模拟退火：

这道题就是让求一个最小的圆半径（位置），使得包含所有的点。

1. 我们先给圆的坐标定义一个初值，就是所有的点的坐标的平均值。
2. 然后我们计算出以该点为圆心，包住所有点的最小半径（即距离该点最远的点的距离）
3. 然后我们就可以开心的退火了。

### 细节：
1. 这道题求的是最小的半径，所以 Metropolis 准则要用大于号

```c
else if(exp(-delta/T) * RAND_MAX > rand())
{
	ansx = nwx; ansy = nwy;
}
```

2. 由于本题 $N$ 较小，则可以用

```c
while(clock()/CLOCKS_PER_SEC < 0.65)
```

3. 耐心调参，然后就过啦

### Code:

```c
#include<bits/stdc++.h>
#define N 55
#define eps 1e-15
#define down 0.9996
using namespace std;
int n;
double x[N],y[N];
double ansx,ansy,ansr;
double calc(double X,double Y)
{
	double ret=0.0;
	for(int i=1;i<=n;i++)
	{
		double dx = X-x[i], dy =Y-y[i];
		double dis = sqrt(dx*dx+dy*dy);
		ret = max(ret , dis);
	}
	return ret;
}
void SA()
{
	double T = 2500;
	while(T>eps)
	{
		double nwx = ansx + (rand()*2-RAND_MAX)*T;
		double nwy = ansy + (rand()*2-RAND_MAX)*T;
		double nwr = calc(nwx,nwy);
		double delta = nwr - ansr;
		if(delta < 0)
		{
			ansx = nwx; ansy=nwy; ansr=nwr;
		}
		else if(exp(-delta/T) * RAND_MAX > rand())
		{
			ansx = nwx; ansy = nwy;
		}
		T*=down;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);
		ansx += x[i]; ansy += y[i];
	}
	ansx /= n; ansy /= n;
	ansr = calc(ansx,ansy);
	while(clock()/CLOCKS_PER_SEC < 0.65)
	{
		SA();
	}
	printf("%.18lf",ansr);
	return 0;
}
```


---

