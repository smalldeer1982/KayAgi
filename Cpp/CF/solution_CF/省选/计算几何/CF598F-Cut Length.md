# Cut Length

## 题目描述

给定 $n$ 个点的简单多边形，再给出 $m$ 条直线。对于每条直线，求直线与多边形的公共部分的长度。

多边形的边界被视作属于多边形。

## 样例 #1

### 输入

```
4 3
0 0
1 0
1 1
0 1
0 0 1 1
0 0 0 1
0 0 1 -1
```

### 输出

```
1.41421356237309514547
1.00000000000000000000
0.00000000000000000000
```

# 题解

## 作者：He_Ren (赞：6)

首先，如果给定直线完全垂直于x轴，可以将所有点的横纵坐标交换，这样就不会出现无法写出解析式的问题了

发现直线与多边形的边重合的情况最难考虑，于是先不考虑这种情况

直线与多边形的边第奇数次相交，一定是“进入”多边形，第偶数次相交，一定是“穿出”多边形。于是可以保存直线与多边形边的交点，然后对横坐标排序，很容易得解

考虑加上直线与多边形的边重合的情况。

在把重合部分计入答案后，便可以把这段直接“略去”，然后依然可以按照上述方法得出答案

具体方法是，在直线开始重合的时候，保存上一个点相对直线的位置（上/下）；在直线结束重合的时候，保存下一个点相对直线的位置（上/下）。如果这两个位置相同，就算作“没有与边相交”；如果不同，就算作“与边相交”

在实现中，用flag表示该点是否是“进入”多边形的点，flag2表示当前是否与直线重合

结合代码更好理解

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
typedef long double db;
const int MAXN = 1e3 + 5;
const db eps = 1e-7;
using namespace std;

inline db Fabs(db x){ return x<0? -x: x;}
inline bool eq(db x,db y){ return Fabs(x-y)<=eps;}

struct Point
{
	db x,y;
}p[MAXN];
inline db dist(const Point &u,const Point &v){ return sqrt((u.x-v.x)*(u.x-v.x) + (u.y-v.y)*(u.y-v.y));}

struct Line
{
	db a,b;
	inline void calc(Point u,Point v)
	{
		a = (u.y-v.y)/(u.x-v.x),
		b = u.y - a * u.x;
	}
	inline int pos(Point u)
	{
		db y = a*u.x + b;
		if(eq(y,u.y)) return 0;
		if(y < u.y) return 1;
		return -1;
	}
	
	inline Line(Point u,Point v){ calc(u,v);}
};

struct Point_
{
	Point u;
	int id;
}q[MAXN];
int ql;
inline void push(Point u,int id){ q[++ql].u=u; q[ql].id=id;}
inline bool cmp(const Point_ &u,const Point_ &v){ return u.u.x<v.u.x;}

int n;
inline void solve(Point u,Point v)
{
	Line l(u,v);
	
	ql=0;
	for(int i=1; i<=n; ++i)
	{
		int p1=l.pos(p[i-1]), p2=l.pos(p[i]), p3=l.pos(p[i+1]);
		if(!p2)
		{
			if(p1!=p3) push(p[i], p1+p3);
		}
		else if(p2+p3==0)
		{
			if(eq(p[i].x, p[i+1].x)) push((Point){ p[i].x, l.a*p[i].x + l.b},0);
			else
			{
				Line l2(p[i],p[i+1]);
				db x = (l.b - l2.b)/(l2.a - l.a);
				push((Point){x, l.a*x + l.b},0);
			}
		}
	}
	
	sort(q+1,q+ql+1,cmp);
	db ans=0;
	int flag=0,flag2=0;
	for(int i=1; i<ql; ++i)
	{
		if(q[i].id && !flag2)
		{
			flag2=1;
			ans+=dist(q[i].u,q[i+1].u);
			if(q[i].id==q[i+1].id) flag^=1;
			continue;
		}
		
		flag2=0;
		flag^=1;
		if(flag) ans+=dist(q[i].u,q[i+1].u);
	}
	printf("%.20lf\n",(double)ans);
}

int main(void)
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
	{
		double x,y;
		scanf("%lf%lf",&x,&y);
		p[i] = (Point){x,y};
	}
	p[0]=p[n];
	p[n+1]=p[1];
	
	while(m--)
	{
		double x1,y1,x2,y2;
		scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		if(eq(x1,x2))
		{
			swap(x1,y1); swap(x2,y2);
			for(int i=0; i<=n+1; ++i) swap(p[i].x,p[i].y);
			solve((Point){x1,y1}, (Point){x2,y2});
			for(int i=0; i<=n+1; ++i) swap(p[i].x,p[i].y);
		}
		else solve((Point){x1,y1}, (Point){x2,y2});
	}
	return 0;
}

```


---

## 作者：xtx1092515503 (赞：2)

卡精度屑题，特别是26、27那两个hack的点，本地都跑过去了却被CF评测姬卡掉了，后来发现是精度开 $10^{-8}$ 太小了会把相同的东西看成不同的，$10^{-6}$ 才刚刚好卡过……

思想非常simple。我们回忆一下所谓的“射线法”（用来判断一个点是否在多边形内的那个算法），然后将其魔改一下，就变成了求出该直线与此多边形的所有交点，然后处在相邻两个交点间的线段便是其处于多边形内的部分。

因为 $n$ 只有 $1000$，我们完全可以枚举每一条线段来找到它与直线的交点。很明显这些交点都在该直线上，那么我们把它们按照从直线的一段到另一端的顺序排序，然后就是找出第一个交点和第二个交点间的线段，第三个和第四个间的线段……

这是理论上的算法。真正实现起来会发现有很多要处理的：

1. 关于重合的边的问题。

明显，如果边与直线重合，该边是一定要计入的；于是我们单独开一个数组维护所有这样的边，然后将这样的边与上文所述线段求一个并即可。

2. 关于直线何时与边有交的问题

当直线与边不交在一些奇奇怪怪的位置之前，这实际上是很simple的；但是的确会出现奇奇怪怪的位置，比如说直线与一个角相交（这时需要判断直线是穿过了角进入了多边形（这时就贡献了一个交点），还是只是擦过去并没有真正进去），或是直线与边重合（这时还是上文所述两种情况，进去或是没进去）。这玩意需要好好讨论一下，如果不想讨论也可以直接看代码，里面有注释。

在处理这情形2的时候，最好把所有 $180^{\circ}$ 的角都删掉，不然可能会增加讨论量。

最终时间复杂度 $O(nm\log n)$，因为区间并是 $O(n\log n)$ 的。

代码（最后附有三组我绞尽脑汁构造出来卡掉我自己的数据，如果实在不知道什么错也可以拿去玩玩）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double
const double eps=1e-6;
int cmp(double x){
	if(x>eps)return 1;
	if(x<-eps)return -1;
	return 0;
}
struct Vector{
	double x,y;
	Vector(){}
	Vector(double X,double Y){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const double &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const double &v){return Vector(u.x/v,u.y/v);}
	friend double operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}//cross times
	friend double operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}//point times
	double operator ~()const{return sqrt(x*x+y*y);}//the modulo of a vector
	double operator !()const{return atan2(y,x);}//the angle of a vector
	friend bool operator <(const Vector &u,const Vector &v){return cmp(u.x-v.x)?u.x<v.x:u.y<v.y;}
	friend bool operator ==(const Vector &u,const Vector &v){return !cmp(u.x-v.x)&&!cmp(u.y-v.y);}
	void read(){scanf("%Lf%Lf",&x,&y);}
	void print()const{printf("(%Lf,%Lf)",x,y);}
}p[1010];
Vector read(){Vector x;x.read();return x;}
typedef Vector Point;
struct Line{
	Point x,y;
	Vector z;
	Line(){}
	Line(Point X,Point Y){x=X,y=Y,z=Y-X;}
	void print()const{x.print(),y.print();}
	friend Point operator &(const Line &u,const Line &v){return u.x+u.z*((v.z&(u.x-v.x))/(u.z&v.z));}
	friend int operator &(const Line &u,const Point &v){return cmp((v-u.x)&(v-u.y));}//point v is on which side of line u
};
typedef Line Segment;
int n,m;
vector<Segment>u;
vector<Point>v,w;
vector<int>b;
bool on[1010];
double calc(Line l){
	u.clear(),v.clear(),memset(on,false,sizeof(on));
	for(int i=0;i<n;i++){
		if(!cmp((p[i]-p[(i+1)%n])&l.z)){//two lines parallel
			if(cmp(l.z&(p[i]-l.x)))continue;
			u.emplace_back(p[i],p[(i+1)%n]);//two lines coincide
			Segment tmp(p[i],p[(i+1)%n]);if((tmp&p[(i+n-1)%n])!=(tmp&p[(i+2)%n]))v.push_back(p[i]);
			//the line crossed the border at the coincided edge
			continue;
		}
		Point x=Line(p[i],p[(i+1)%n])&l;//if not parallel, this is the intersection point
		if(x==p[i]){on[i]=true;continue;}
		if(x==p[(i+1)%n]){on[(i+1)%n]=true;continue;}//if intersection point is concide with one endpoint of the segment,consider it specially
		if(cmp((x-p[i])|(x-p[(i+1)%n]))==1)continue;//intersection is not on the segment
		v.push_back(x);
	}
	for(int i=0;i<n;i++){//this loop only consider points exactly on the line
		if(!on[i])continue;
		if(on[(i+n-1)%n]||on[(i+1)%n])continue;//if this point is endpoint of a coinciding edge, do not bother as we've considered it previously
		Point x=(l.x==p[i]?l.y:l.x);//find one point on the line which do not coincide with the current point
		Segment A(p[(i+n-1)%n],p[i]);bool a=((A&x)!=(A&p[(i+1)%n]));
		Segment B(p[(i+1)%n],p[i]);bool b=((B&x)!=(B&p[(i+n-1)%n]));
		if(a==b)v.push_back(p[i]);//cross the border.
	}
	sort(v.begin(),v.end()),w=v;
	for(auto i:u)w.push_back(i.x),w.push_back(i.y);
	sort(w.begin(),w.end());
	b.assign(w.size(),0);
	for(int i=0;i<v.size();i+=2){
		int l=lower_bound(w.begin(),w.end(),v[i])-w.begin();
		int r=lower_bound(w.begin(),w.end(),v[i+1])-w.begin();
		b[l]++,b[r]--;
	}
	for(int i=0;i<u.size();i++){
		int l=lower_bound(w.begin(),w.end(),u[i].x)-w.begin();
		int r=lower_bound(w.begin(),w.end(),u[i].y)-w.begin();
		if(l>r)swap(l,r);
		b[l]++,b[r]--;
	}
	for(int i=1;i<b.size();i++)b[i]+=b[i-1];
	double ret=0;
	for(int i=0;i+1<b.size();i++)if(b[i])ret+=~(w[i+1]-w[i]);
	return ret;
}
int N;
int main(){
	scanf("%d%d",&N,&m);
	for(int i=0;i<N;i++){
		p[n].read();
		if(n>=2&&cmp((p[n]-p[n-1])&(p[n]-p[n-2]))==0)n--,p[n]=p[n+1];//eliminating those 180-degree angles.
		n++;
	}
	if(n>=3&&cmp((p[0]-p[n-1])&(p[0]-p[n-2]))==0)n--;
	if(n>=3&&cmp((p[1]-p[0])&(p[1]-p[n-1]))==0){for(int i=0;i+1<n;i++)p[i]=p[i+1];n--;}
	while(m--)printf("%.10Lf\n",calc(Line(read(),read())));
	return 0;
}
/*
12 5
-1 0
-2 1
-1 2
0 1
1 2
2 1
1 0
2 -1
1 -2
0 -1
-1 -2
-2 -1
-2 -1 -1 0
-2.01 -1 -1.01 0
-1.99 -1 -0.99 0
-1 0 1 0
1 2 2 1

8 4
0 0
0 1
0 2
1 2
2 2
2 1
1 1
1 0
1 0 1 1
0 1 1 1
0 0 1 1
1 0 2 1

6 3
0 0
0 1
0 2
1 1
2 0
1 0
0 0 1 1
2 0 0 2
2 0 0 1
*/
```



---

## 作者：hgzxwzf (赞：1)

如果答案大于 $0$，那么给的直线一定和多边形的边有交点，可以用向量的叉积正负判断点在直线的左侧还是右侧，如果线段上两个点在直线的不同侧，那么就说明他们相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/9xqimomd.png)

因为 $\overrightarrow{AQ'}\times\overrightarrow{AP}=2S_{\triangle{APQ}},\overrightarrow{AQ'}\times\overrightarrow{AB}=2S_{\triangle{ABQ'}}$，且 $\triangle_{APQ'}$ 和 $\triangle{ABQ'}$ 共底，

所以 $P$ 到 $AQ'$ 的距离比 $B$ 到 $AQ'$ 的距离等于 $\frac{\overrightarrow{AQ'}\times\overrightarrow{AP}}{\overrightarrow{AQ'}\times\overrightarrow{AB}}$，因为 $AQ'\parallel PQ$，所以 $A$ 到 $AQ'$ 的距离等于 $P$ 到 $AQ'$ 的距离。

又由相似可知，$\frac{|AC|}{|AB|}=\frac{\overrightarrow{AQ'}\times\overrightarrow{AP}}{\overrightarrow{AQ'}\times\overrightarrow{AB}}$，将这个值记为 $PQ$ 的贡献。

用小根堆把有贡献的边存下来，用 pair 记录边，$first$ 表示贡献，$second$ 表示相对位置（即 $r_{i+1}-r_i$，如果 $i$ 在直线左边，$r_i=-1$，如果在右边 $r_i=1$，如果在上面 $r_i=0$）。

记录 $sum$ 表示 $second$ 的前缀和，如果 $sum\not=0$，就说明当前段在多边形内。

如下图，$|AC|=first_i$，$|AD|=first_{i+1}$，所以 $CD$ 的贡献为 $first_{i+1}-first_{i}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/uasuz2jm.png)

最后把总贡献乘上 $|AB|$ 就是答案。

---

