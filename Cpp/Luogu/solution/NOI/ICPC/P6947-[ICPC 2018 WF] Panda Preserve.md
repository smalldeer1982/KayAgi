# [ICPC 2018 WF] Panda Preserve

## 题目描述

上个月，四川省获得资金建立大熊猫国家公园，这是一处为超过 1800 只大熊猫提供栖息地的自然保护区。公园将被多边形围栏包围。为了让研究人员追踪大熊猫，将在围栏的每个顶点放置无线接收器，每只大熊猫都将配备无线发射器。每个无线接收器将覆盖以接收器位置为中心的圆形区域，并且所有接收器的覆盖范围相同。显然，覆盖范围较小的接收器更便宜，因此你的目标是确定能够覆盖整个公园的最小可能范围。

例如，图 G.1 显示了由第一个样例输入描述的公园。注意，35 的无线范围不足以覆盖整个公园（a），而 50 的最佳范围则可以覆盖整个公园（b）。

![](https://cdn.luogu.com.cn/upload/image_hosting/n9l4fete.png)

图 G.1：样例输入 1 的示意图。

## 说明/提示

时间限制：10 秒，内存限制：1024 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
0 0
170 0
140 30
60 30
0 70
```

### 输出

```
50
```

## 样例 #2

### 输入

```
5
0 0
170 0
140 30
60 30
0 100
```

### 输出

```
51.538820320
```

## 样例 #3

### 输入

```
5
0 0
1 2
1 5
0 2
0 1
```

### 输出

```
1.581138830
```

# 题解

## 作者：xtx1092515503 (赞：3)

首先要把问题转化一下：我们不求 **能覆盖所有点的最小半径**，而求 **覆盖每个点所需最小半径的最大值**。显然这两个问题是等价的。

事实上，覆盖一个点所需最小半径，就是这个点到某个顶点的最近距离。

那么这让我们想到 Voronoi 图：关于某个点集 $\mathbb S$ 的 V 图将平面划分成若干个部分，每个部分是一个（可能面积无限的）凸壳，所有点到 $\mathbb S$ 中距离最近的点均相同。更多知识可以自行搜索。**注意本题不需要 V 图的高效构建方法**。

假如我们已经求出所有凸壳。注意任何一个 **面积有限** 的 **不一定简单的**（即，其可以有若干相离部分）**多边形** 到某一关键点的最远点必然位于边界（可能是其中某个部分的边界）上（可以调整，因为向边界移动必然不更劣），进而必然位于顶点（可能是某个部分的顶点）处（因为向左向右两个方向中必然有一个不更劣）。故只要顶点数可承受，我们就可以进行尝试了。

注意到并非凸壳中所有点都可以被选：其必须同时还是题面中给定的简单多边形内部的点。这意味着可选点集事实上是凸壳与给定多边形的交集。这必然是面积有限但不一定简单的多边形。

假如我们已经求出交集，则只需枚举交集的所有顶点，求出其到关键点的距离的最大值即可。

考虑交集的顶点可能有三种类型：凸壳中的顶点；给定多边形的顶点；凸壳中边与给定多边形中边的交点。

第一类可以枚举顶点然后用射线法判定是否在多边形内部解决。

> 射线法：自一个在简单多边形内部的顶点向外引出一条射线，其必然与该多边形的边界相交奇数次，而在外部的顶点引出的射线必然相交偶数次。

第二类不需要处理，因为多边形的顶点所需的最小半径必然是零（其自身就是集合 $\mathbb S$ 中元素）。

第三类可以枚举简单多边形的边，用一些方法（比如说，二分/三分）在凸壳上找出交点，然后尝试更新答案。

考虑分析复杂度。计算第一类顶点需要的复杂度为 $O(\text{顶点数}\times\text{射线法复杂度})$。不需计算第二类顶点。计算第三类顶点需要的复杂度是 $O(\text{简单多边形边数}\times\text{单次求交复杂度})$。

但是，只要注意到一个性质，即 V 图中 **点数和边数都是关于 $|\mathbb S|$ 线性的**，那么就可以枚举 V 图中每个顶点求射线法，再枚举 V 图中每条边和简单多边形中每条边求交点即可。这部分复杂度平方。

最后还有一个问题，就是如何求出 V 图。假如只有两个点，则考虑这两点的中垂线（垂直平分线），其左侧是到左方点更近的点集，右侧是到右方点更近的点集。对于一个点，取所有其它点求中垂线，则靠近其一侧的所有半平面的交集即为其对应的凸壳。

直接对每个点各跑一遍半平面交，复杂度平方对数。

需要注意的是，本题的瓶颈 **完全在半平面交的排序**。因此尽量优化你半平面交的比较。我一开始的写法一次比较傻傻地做了 $4$ 次 `atan2`，然后因为常数过大在 CF 上也光荣 TLE。后来预处理出 `atan2` 的结果，然后就卡过去了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
const double pi=acos(-1);
int cmp(double x){if(x>eps)return 1;if(x<-eps)return -1;return 0;}
double res;
struct Vector{
	double x,y;
	Vector(){}
	Vector(double X,double Y){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const double &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const double &v){return Vector(u.x/v,u.y/v);}
	friend double operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}
	friend double operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}
	friend bool operator ==(const Vector &u,const Vector &v){return cmp(u.x-v.x)==0&&cmp(u.y-v.y)==0;}
	double operator ~()const{return sqrt(x*x+y*y);}//the modulo of a vector
	double operator !()const{return atan2(y,x);}//the angle of a vector
	void read(){scanf("%lf%lf",&x,&y);}
	void print()const{printf("(%lf,%lf)",x,y);}
	Vector turn(){return Vector(y,-x);}
	friend bool operator<(const Vector&u,const Vector&v){
		if(cmp(u.x-v.x)==0)return cmp(u.y-v.y)==-1;
		return cmp(u.x-v.x)==-1;
	}
}p[2010],q[2010];
typedef Vector Point;
struct Line{
	Point x,y;
	Vector z;double ang;
	Line(){}
	Line(Point X,Point Y){x=X,y=Y,z=Y-X,ang=!z;}
	friend bool operator<(const Line&u,const Line&v){
		if(cmp(u.ang-v.ang))return u.ang<v.ang;
		return cmp(u.z&(v.y-u.x))==-1;
	}
	friend bool operator/(const Line&u,const Line&v){return cmp(u.z&v.z)==0;}
	friend bool operator|(const Line&u,const Line&v){return cmp(u.ang-v.ang)==0;}
	friend bool operator&(const Line&u,const Point&v){return cmp((v-u.x)&u.z)!=1;}
	friend bool operator%(const Line&u,const Point&v){return cmp((u.x-v)|(u.y-v))!=1;}
	friend Point operator&(const Line&u,const Line&v){return u.x+u.z*((v.z&(u.x-v.x))/(u.z&v.z));}
}l[2010],r[2010];
typedef Line Segment;
int n,L,R,m;
set<Point>st;
bool inside(Point P){
	if(st.find(P)!=st.end())return false;
	st.insert(P);
	static default_random_engine rnd(17680321);
	static uniform_real_distribution<double>urd(-pi,pi);
	while(true){
		double ang=urd(rnd);
		Point Q(P.x+cos(ang),P.y+sin(ang));
		Line X(P,Q);
		int num=0;
		for(int i=0;i<n;i++){
			Point A=p[i],B=p[(i+1)%n];
			Line Y(A,B);
			Point C=Y&X;
			if(C==B||C==A){num=-1;break;}
			if(!(Y%C)||(Segment(Q,C)%P&&!(P==C)))continue;
			num++;
		}
		if(num!=-1)return num&1;
	}
}
void solve(int _){
	m=0;
	for(int i=0;i<n;i++)if(i!=_){
		Point P=(p[i]+p[_])/2;
		Point Q=P+(p[_]-p[i]).turn();
		// P.print(),Q.print();puts("");
		l[m++]=Line(P,Q);
	}
	l[m++]=Line(Point(-2e4,-2e4),Point(2e4,-2e4));
	l[m++]=Line(Point(2e4,-2e4),Point(2e4,2e4));
	l[m++]=Line(Point(2e4,2e4),Point(-2e4,2e4));
	l[m++]=Line(Point(-2e4,2e4),Point(-2e4,-2e4));
	sort(l,l+m),r[L=R=0]=l[0];
	for(int i=1;;i++){
		while(i<m&&l[i]|l[i-1])i++;
		if(i==m)break;
		if(L<R&&((r[L]/r[L+1])||(r[R]/r[R-1])))return;
		while(L<R&&!(l[i]&q[R-1]))R--;
		while(L<R&&!(l[i]&q[L]))L++;
		r[++R]=l[i];if(L<R)q[R-1]=r[R]&r[R-1];
	}
	while(L<R&&!(r[L]&q[R-1]))R--;
	while(L<R&&!(r[R]&q[L]))L++;
	if(R-L<=1)return;
	q[R]=r[L]&r[R];
	// printf("%d:\n",_);
	// for(int i=L;i<=R;i++)q[i].print();puts("");
	for(int i=L;i<=R;i++)if(inside(q[i]))res=max(res,~(q[i]-p[_]));
	for(int i=L;i<=R;i++)for(int j=0;j<n;j++){
		Segment s(p[j],p[(j+1)%n]),t(q[i],q[i==R?L:i+1]);
		if(s/t)continue;
		Point P=s&t;
		if(s%P&&t%P)res=max(res,~(P-p[_]));
	}
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)p[i].read();
	for(int i=0;i<n;i++)solve(i);
	printf("%lf\n",res);
	return 0;
}
```



---

## 作者：sqrtqwq (赞：1)

前置知识：Voronoi 图

1. Voronoi 图把平面划分成 $n$ 个多边形域，每个多边形内只有一个生成元。
1. 每个多边形内的点到该生成元距离短于到其它生成元距离。
1. 多边形边界上的点到生成此边界的两个生成元的距离相等。

接下来考虑如何得到一个 Voronoi 图。

这是十分显然的，我们只需要求出一个点和其余点的中垂线半平面的交。

这个过程需要求 $n$ 次半平面交，所以时间复杂度为 $O(n^2 \log n)$。

首先一个半径 $r$ 能成为答案的条件就是对于所有的 $A \in P$，均有 $\min\{|AP_1|,|AP_2|,\cdots \cdots |AP_n|\} \le r$。

很明显，我们最终的答案就是 $\max_{A \in P}\min\{|AP_1|,|AP_2|,\cdots \cdots |AP_n|\}$。

此时我们钦定 $|AP_i| = \min\{|AP_1|,|AP_2|,\cdots \cdots |AP_n|\}$，则这样的 $A$ 的范围是关于 $P_1,P_2 \cdots \cdots P_n$ 的 Voronoi 图 $P_i$ 所在的区域中。此时我们考虑他所在的区域和 $P$ 的交集，很明显这也必定是一个多边形，我们令他为 $Q$。

所以我们只需要找到里 $P_i$ 最远并且在 $Q$ 上的点。通过直观感受，我们发现这个点是 $Q$ 的一个**顶点**。

接下来我们可以对 $Q$ 的顶点分一个类：

1. 某个 $P_i$。

2. Voronoi 图的某个多边形的顶点。

3. Voronoi 图和 $P$ 的交点。

那么此时我们直接用 $O(n^2 \log n)$ 的方法建出 Voronoi 图，然后考虑那三种点的贡献：

1. 为 $0$。

2. 对于 Voronoi 图的顶点最多有 $O(n)$ 个，所以我们只需要用 $O(n)$ 的时间判断点是否在多边形内部，然后统计答案即可。时间复杂度 $O(n)$。

3. 这样的点显然在多边形内部 (含边上)，直接更新即可。时间复杂度 $O(n)$。

最终时间复杂度为 $O(n^2 \log n)$。

---

