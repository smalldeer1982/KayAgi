# [POI 2005] AKC-Special Forces Manoeuvres

## 题目描述

一个秘密组织正在沙漠中举行一次军事演习。本次演习的目标是拆除隐藏在沙漠中的一个炸弹。

演习的第一部分是空降作战。每个士兵**按照一定的顺序**从悬停在沙漠上空的直升机上跳下。着陆时，每个士兵都会停在他所在的着陆点。

每个空降兵都有一个生存半径。如果炸弹与他的距离小于或等于这个生存半径的话，空降兵便会牺牲自己引爆炸弹。指挥官希望能派出尽可能少的士兵，但他希望在**最坏情况下**至少有一个士兵能够生还。

整个沙漠可以抽象为一个平面，每个士兵的着陆点可以用一个坐标 $(x,y)$ 表示，他的生存半径我们设为 $r$。所有士兵的信息按照他们跳伞时的顺序给出，即第 $i$ 个士兵跳伞时，前 $i-1$ 个士兵都已经着陆。

你的任务是：从标准输入读入所有士兵的信息，输出最少需要派出的士兵数量。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/8xbga77o.png)

最坏情况下炸弹位于 $(5,3)$，前三个士兵都会被炸死，第四个士兵会生还。

## 样例 #1

### 输入

```
5
2 2 4
7 2 3
4 3 1
5 7 1
8 7 1```

### 输出

```
4```

# 题解

## 作者：agicy (赞：6)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-p3428)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117793228)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14873274.html)；
- [简书](https://www.jianshu.com/p/a29e0510e321)。

## 题目

题目链接：[洛谷 P3428](https://www.luogu.com.cn/problem/P3428)、[官网](https://szkopul.edu.pl/problemset/problem/Cyqv1x7xJRdcwj24GKoOZyl3/site/?key=statement)。

### 题意简述

给定 $n$ 个圆 $(x_i,y_i,r_i)$，每个圆对应一个点集 $S_i=\left\{(x,y)\mid (x-x_i)^2+(y-y_i)^2\leq r_i^2\right\}$。

求一个最小的 $i$ 满足 $\cap_{j=1}^i S_j=\varnothing$；如果无解输出 `NIE`。

## 题解

### 简单又自然的随机化

我们考虑枚举 $i$，然后判定 $S_{1\sim i}$ 的交集是否为空。

如何判定呢？我们想到一个简单的方法，我们随机一些在圆的边界上的点，只需要判定这些点是否存至少在一个点在所有圆内即可。

这种方法简单又自然，但是随机化算法正确率不高，这远远不够。

### 研究几何性质

如果做计算几何题而抛弃几何性质，所得到的做法往往是劣解。

继续沿着上面的思路，我们同样考虑枚举 $i$，然后判定 $S_{1\sim i}$ 的交集是否为空。

不同的是，我们定义一个交集中横坐标最大的点为代表点（代表点只会有一个，这是因为圆是凸集，凸集的交集还是凸集）。

我们发现，如果一些圆的交集非空，那么其代表点一定满足：它是所有圆两两交集的代表中横坐标最小的那个。

证明十分显然，考虑交集的意义即可。

### 最后的结论

综上所述，对于一个 $i$，我们只需要求出 $1\sim i-1$ 与 $i$ 的代表点即可，如果所有代表点中横坐标最小的那一个在所有的圆内，那么其合法，否则不合法，换言之，答案为 $i$。

我们考虑证明这个结论：

- 若没有交集，则这个点必然不合法，符合我们的预期；
- 若有交集，则我们需要证明这个点是交集的代表点。
	- 假设其不是交集的代表点，则交集的代表点可能在其左右；
    - 左边：不可能，若交集存在，则代表点的横坐标 $\geq$ 当前点横坐标。
    - 右边：不可能，考虑当前点在 $S_a\cap S_b$ 中得到，那么所有 $x\geq$ 当前点横坐标的点均被交集抛弃，因此代表点的横坐标 $\leq$ 当前点横坐标。
    - 由夹逼过程可知结论正确。

这个算法的时间复杂度为 $\Theta(n^2)$。

### 参考程序

下面我们来解决两圆求交的问题。

下面介绍一下两种方法：余弦定理和相似三角形。

#### 余弦定理

用余弦定理求解需要用到三角函数，常数大，精度差。

我们考虑下图：

[![2WRtN4.png](https://z3.ax1x.com/2021/06/11/2WRtN4.png)](https://imgtu.com/i/2WRtN4)

对 $\triangle{ACB}$ 运用余弦定理，得到 $r_a^2+d^2-2dr_a\cos\alpha=r_b^2$，进而求出 $\alpha=\arccos\left(\frac{r_a^2+d^2-r_b2}{2dr_a}\right)$。

然后我们再求出基准角 $\beta$，显然 $\beta=\texttt{atan2}(y_b-y_a,x_b-x_a)$。

因此，我们得到了 $C,D$ 两点的对 $A$ 的极角为 $\beta+\alpha$，$\beta-\alpha$。

对于极角为 $\theta$，极径为 $r_a$ 的点，我们得出其对应点的坐标为 $(r_a\cos\theta,r_a\sin\theta)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const double eps=1e-6;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline double sqr(reg double x){
	return x*x;
}

const int MAXN=2e3+5;

struct Vector{
	double x,y;
	inline Vector(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
	inline Vector operator*(const double a)const{
		return Vector(x*a,y*a);
	}
};

inline double dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline double cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

inline double getDis2(const Point& a,const Point& b){
	return dot(a-b,a-b);
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(getDis2(a,b));
}

inline bool isEmpty(const Point& a){
	return a.x!=a.x||a.y!=a.y;
}

struct Circle{
	Point o;
	double r;
	inline bool contain(const Point& x)const{
		return sgn(sqr(r)-getDis2(x,o))>=0;
	}
	inline Point getRig(void)const{
		return o+Vector(r,0);
	}
};

inline bool isCon(const Circle& a,const Circle& b){
	return sgn(sqr(a.r-b.r)-getDis2(a.o,b.o))>=0;
}

inline bool isSep(const Circle& a,const Circle& b){
	return sgn(getDis2(a.o,b.o)-sqr(a.r+b.r))>0;
}

inline Point getPot(const Circle &a,const Circle &b){
	if(isCon(a,b))
		if(sgn(b.getRig().x-a.getRig().x)>0)
			return a.getRig();
		else
			return b.getRig();
	else if(isSep(a,b))
		return Point(nan(""),nan(""));
	else{
		if(a.contain(b.getRig()))
			return b.getRig();
		else if(b.contain(a.getRig()))
			return a.getRig();
		else{
			reg double d=getDis(a.o,b.o);
			reg double ang=acos(((sqr(a.r)+sqr(d))-sqr(b.r))/(2*a.r*d));
			reg double delta=atan2(b.o.y-a.o.y,b.o.x-a.o.x);
			reg double ang1=delta+ang,ang2=delta-ang;
			Point p1=a.o+Vector(cos(ang1)*a.r,sin(ang1)*a.r);
			Point p2=a.o+Vector(cos(ang2)*a.r,sin(ang2)*a.r);
			Point res;
			if(sgn(p2.x-p1.x)>0)
				res=p2;
			else
				res=p1;
			return res;
		}
	}
}

int n;
Circle a[MAXN];

int main(void){
	scanf("%d",&n);
	Point lef(0,0);
	for(reg int i=1;i<=n;++i){
		static int x,y,r;
		scanf("%d%d%d",&x,&y,&r);
		a[i].o=Point(x,y),a[i].r=r;
		if(i==2)
			lef=getPot(a[1],a[2]);
		else if(i>2){
			for(reg int j=1;j<i&&!isEmpty(lef);++j){
				Point tmp=getPot(a[i],a[j]);
				if(isEmpty(tmp)||tmp.x<=lef.x)
					lef=tmp;
			}
			for(reg int j=1;j<=i&&!isEmpty(lef);++j)
				if(!a[j].contain(lef))
					lef=Point(nan(""),nan(""));
		}
		if(isEmpty(lef)){
			printf("%d\n",i);
			return 0;
		}
	}
	puts("NIE");
	return 0;
}
```

#### 相似三角形

[![2WRN4J.png](https://z3.ax1x.com/2021/06/11/2WRN4J.png)](https://imgtu.com/i/2WRN4J)

如上图，我们设 $a=|AG|$，$b=|BG|$，$h=|CG|$。

那么我们有：

$$\begin{cases}r_a^2=a^2+h^2\\r_b^2=b^2+h^2\\a+b=d\end{cases}$$

那么我们有：

$$a=\frac{r_a^2+d^2-r_b^2}{2d}$$

然后考虑 $\triangle AIB\sim\triangle CHG$，我们有：

$$(y_b-y_a)h=d(y_c-y_g)$$

我们可由此解出坐标，其他同理可算出。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const double eps=1e-6;

inline int sgn(reg double x){
	if(fabs(x)<eps)
		return 0;
	else
		return x<0?-1:1;
}

inline double sqr(reg double x){
	return x*x;
}

const int MAXN=2e3+5;

struct Vector{
	double x,y;
	inline Vector(reg double x=0,reg double y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
	inline Vector operator*(const double a)const{
		return Vector(x*a,y*a);
	}
};

inline double dot(const Vector& a,const Vector& b){
	return a.x*b.x+a.y*b.y;
}

inline double cross(const Vector& a,const Vector& b){
	return a.x*b.y-a.y*b.x;
}

typedef Vector Point;

inline double getDis2(const Point& a,const Point& b){
	return dot(a-b,a-b);
}

inline double getDis(const Point& a,const Point& b){
	return sqrt(getDis2(a,b));
}

inline bool isEmpty(const Point& a){
	return isnan(a.x)||isnan(a.y);
}

struct Circle{
	Point o;
	double r;
	inline bool contain(const Point& x)const{
		return sgn(sqr(r)-getDis2(x,o))>=0;
	}
	inline Point getRig(void)const{
		return o+Vector(r,0);
	}
};

inline bool isCon(const Circle& a,const Circle& b){
	return sgn(sqr(a.r-b.r)-getDis2(a.o,b.o))>=0;
}

inline bool isSep(const Circle& a,const Circle& b){
	return sgn(getDis2(a.o,b.o)-sqr(a.r+b.r))>0;
}

inline Point getPot(const Circle &a,const Circle &b){
	if(isCon(a,b))
		if(sgn(b.getRig().x-a.getRig().x)>0)
			return a.getRig();
		else
			return b.getRig();
	else if(isSep(a,b))
		return Point(nan(""),nan(""));
	else{
		if(a.contain(b.getRig()))
			return b.getRig();
		else if(b.contain(a.getRig()))
			return a.getRig();
		else{
			reg double d=getDis(a.o,b.o);
			reg double val=(sqr(a.r)+sqr(d)-sqr(b.r))/(2*d);
			reg double h=sqrt(sqr(a.r)-sqr(val));
			Point bas=a.o+(b.o-a.o)*(val/d);
			Vector tmp=Vector(b.o.y-a.o.y,a.o.x-b.o.x)*(h/d);
			Point p1=bas-tmp,p2=bas+tmp;
			if(sgn(p2.x-p1.x)>0)
				return p2;
			else
				return p1;
		}
	}
}

int n;
Circle a[MAXN];

int main(void){
	scanf("%d",&n);
	Point lef(0,0);
	for(reg int i=1;i<=n;++i){
		static int x,y,r;
		scanf("%d%d%d",&x,&y,&r);
		a[i].o=Point(x,y),a[i].r=r;
		if(i==2)
			lef=getPot(a[1],a[2]);
		else if(i>2){
			for(reg int j=1;j<i&&!isEmpty(lef);++j){
				Point tmp=getPot(a[i],a[j]);
				if(isEmpty(tmp)||tmp.x<=lef.x)
					lef=tmp;
			}
			for(reg int j=1;j<=i&&!isEmpty(lef);++j)
				if(!a[j].contain(lef))
					lef=Point(nan(""),nan(""));
		}
		if(isEmpty(lef)){
			printf("%d\n",i);
			return 0;
		}
	}
	puts("NIE");
	return 0;
}
```


---

## 作者：Piwry (赞：2)

这题可能有很多种奇奇怪怪的做法X

这里主要是介绍下 std 的做法，相比其它做法应该会简单和好写许多

（波兰语真难读）

[参考](https://oi.edu.pl/static/attachment/20110811/oi12.pdf) - P149

## 解析

首先题意可以转化为，按给出的顺序添加圆（士兵），维护它们的交集，当交集首次为空时输出已添加的圆的数量（不含最后添加的那个圆）

设已添加的圆 $K_1, K_2, \cdots K_n$，即我们要维护交集 $S=K_1\cap K_2 \cap \cdots \cap K_n$

考虑维护当前交集最右（$\text{x}$ 坐标最大）的那个点，设其为 $X$

不难发现，当 $S$ 不为空时，$X$ 有如下性质：

> $\text{引理 1.}$ $X$ 一定存在且唯一

> $\text{引理 2.}$ $X$ 一定为某两个圆的交集 $K_i\cap K_j$ 的最右点（可以有 $i=j$）

$\text{1.}$ 的其中一种证明方式为，先证明交集是凸的，再根据圆的性质讨论即可。具体讨论此处略过

$\text{2.}$ 的证明也是很显然的。首先 $X$ 不可能不在任何圆的边缘上，否则我们只需单纯地增大 $X$ 的 $\text{x}$ 坐标就能得到一个更右边的点。如果 $X$ 在某个圆 $K_i$ 的边缘上，这意味着：

- $X$ 为 $K_i$ 的最右点
- 存在另一个圆 $K_j$，使得 $X$ 为交集 $K_i\cap K_j$ 的最右点

的至少其中之一满足。不然的话一定存在某个圆 $K_k$，只要我们沿 $K_k$ 的边缘增大 $X$ 的 $\text{x}$ 坐标就能得到矛盾。注意到这两个条件和 $\text{\text{2.}}$ 是等价的，于是由此导出了 $\text{2.}$ 的证明

设集合 $P$ 由所有可能的两个圆的交 $K_i\cap K_j$ 的最右点构成。接着还能注意到：

> $\text{引理 3.}$ $X$ 一定为 $P$ 中 $\text{x}$ 坐标最小的那个点

证明只需考虑圆的性质、交集的基本性质以及 $1.$ 即可

由此问题就已经转化成，检查一个特定的点——集合 $P$ 最左边的点——是否在当前的所有圆中（$S$ 是否为空）。$P$ 比 $S$ 更容易描述和计算；要做到这点，我们只需在每添加一个圆时简单地 $O(n)$ 维护集合 $P$（求两个圆的交的最右点是可以 $O(1)$ 做到的，但具体此处略过）与检查 $P$ 最左边的点是否合法。算法总的复杂度是 $O(n^2)$ 的

## 代码

```cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#define nan 0.0/0
#define double long double
using std::vector;
using std::max;

const double eps =1e-14;

struct point{
	double x, y;
	
	point(){}
	point(const double &_x, const double &_y)
		:x(_x), y(_y){}
	
	inline bool Null() const{
		return (x != x || y != y);
	}
};
struct circle{
	point O;
	double r;
	
	circle(){}
	circle(const double &_x, const double &_y, const double &_r)
		:O(point(_x, _y)), r(_r){}
};

const point Null(nan, nan);

bool inCircle(const point &x, const circle &K){
//	return (sqrt((x.x-K.O.x)*(x.x-K.O.x)+(x.y-K.O.y)*(x.y-K.O.y)) < K.r);
	return ((x.x-K.O.x)*(x.x-K.O.x)+(x.y-K.O.y)*(x.y-K.O.y) <= K.r*K.r+1e-7);
}

// 返回两个圆交集的 x 坐标最大点 //
point prawyPunkt(const circle &K1, const circle &K2){
	if((K1.O.x-K2.O.x)*(K1.O.x-K2.O.x)+(K1.O.y-K2.O.y)*(K1.O.y-K2.O.y) < (K1.r-K2.r)*(K1.r-K2.r)+eps){ // 包含的情况 //
		if((K1.O.x+K1.r <= K2.O.x+K2.r+eps && K1.O.x-K1.r >= K2.O.x-K2.r-eps) && (K1.O.y+K1.r <= K2.O.y+K2.r+eps && K1.O.y-K1.r >= K2.O.y-K2.r-eps))
			return point(K1.O.x+K1.r, K1.O.y);
		else if((K2.O.x+K2.r <= K1.O.x+K1.r+eps && K2.O.x-K2.r >= K1.O.x-K1.r-eps) && (K2.O.y+K2.r <= K1.O.y+K1.r+eps && K2.O.y-K2.r >= K1.O.y-K1.r-eps))
			return point(K2.O.x+K2.r, K2.O.y);
	}
	else{ // 求两圆交点；下面的式子事实上都是用 matlab 推的，所以别试着搞懂 ( //
		double a1 =K1.O.x, b1 =K1.O.y, R1 =K1.r, a2 =K2.O.x, b2 =K2.O.y, R2 =K2.r;
	
		double R1R1 =R1*R1;
		double a1a1 =a1*a1;
		double b1b1 =b1*b1;
	
		double a2a2 =a2*a2;
		double b2b2 =b2*b2;
		double R2R2 =R2*R2;
	
		double subs1 = a1a1 - 2 * a1*a2 + a2a2 + b1b1 - 2 * b1*b2 + b2b2;
		double subs2 = -R1R1 * a1 + R1R1 * a2 + R2R2 * a1 - R2R2 * a2 + a1a1*a1 - a1a1 * a2 - a1*a2a2 + a1*b1b1 - 2 * a1*b1*b2 + a1*b2b2 + a2a2*a2 + a2*b1b1 - 2 * a2*b1*b2 + a2*b2b2;
		double subs3 = -R1R1 * b1 + R1R1 * b2 + R2R2 * b1 - R2R2 * b2 + a1a1*b1 + a1a1 * b2 - 2 * a1*a2*b1 - 2 * a1*a2*b2 + a2a2 * b1 + a2a2 * b2 + b1b1*b1 - b1b1 * b2 - b1*b2b2 + b2b2*b2;
		double sigma = sqrt((R1R1 + 2 * R1*R2 + R2R2 - a1a1 + 2 * a1*a2 - a2a2 - b1b1 + 2 * b1*b2 - b2b2)*(-R1R1 + 2 * R1*R2 - R2R2 + subs1));
		
		if(abs(subs1) > eps){
			point P1, P2;
			P1.x = (subs2 - sigma*b1 + sigma*b2) / (2 * subs1);
			P2.x = (subs2 + sigma*b1 - sigma*b2) / (2 * subs1);
		
			P1.y = (subs3 + sigma*a1 - sigma*a2) / (2 * subs1);
			P2.y = (subs3 - sigma*a1 + sigma*a2) / (2 * subs1);
			
			point P =((P1.x > P2.x) ? P1 : P2);
			
			// 若不为交点，则为其中一个圆的最右点 //
			const point Q1 =point(K1.O.x+K1.r, K1.O.y);
			if(inCircle(Q1, K2) && Q1.x > P.x-eps)
				P =Q1;
			const point Q2 =point(K2.O.x+K2.r, K2.O.y);
			if(inCircle(Q2, K1) && Q2.x > P.x-eps)
				P =Q2;
			
			return P;
		}
		else
			return Null;
	}
}

int main(){
	int n;
	scanf("%d", &n);
	vector<circle> arr(n);
	point x(0, 0);
	for(int i =0; i < n; ++i){
		int _x, _y, _r;
		scanf("%d%d%d", &_x, &_y, &_r);
		arr[i] =circle(_x, _y, _r);
		
		if(i == 1)
			x =prawyPunkt(arr[0], arr[1]);
		else if(i > 1){
			for(int j =0; j < i && !x.Null(); ++j){
				const point y =prawyPunkt(arr[i], arr[j]);
				if(y.Null() || y.x < x.x+eps)
					x =y;
			}
			for(int j =0; j <= i && !x.Null(); ++j)
				if(!inCircle(x, arr[j]))
					x =Null;
		}
		if(x.Null())
			return printf("%d", i+1) && 0;
	}
	puts("NIE");
}
```

---

