# Ksusha and Square

## 题目描述

Ksusha is a vigorous mathematician. She is keen on absolutely incredible mathematical riddles.

Today Ksusha came across a convex polygon of non-zero area. She is now wondering: if she chooses a pair of distinct points uniformly among all integer points (points with integer coordinates) inside or on the border of the polygon and then draws a square with two opposite vertices lying in the chosen points, what will the expectation of this square's area be?

A pair of distinct points is chosen uniformly among all pairs of distinct points, located inside or on the border of the polygon. Pairs of points $ p,q $ $ (p≠q) $ and $ q,p $ are considered the same.

Help Ksusha! Count the required expectation.

## 样例 #1

### 输入

```
3
0 0
5 5
5 0
```

### 输出

```
4.6666666667
```

## 样例 #2

### 输入

```
4
-1 3
4 5
6 2
3 -5
```

### 输出

```
8.1583333333
```

## 样例 #3

### 输入

```
3
17 136
859 937
16 641
```

### 输出

```
66811.3704155169
```

# 题解

## 作者：Rainybunny (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF293D).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~完全不会计算几何的菜鸡在线瞎搞斜率.~~
## 题意
>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在一个凸包内选择两个点, 求以两点连线为对角线的正方形的期望面积.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;实际上, 取到每一个无序点对的概率都是相等的, 我们的目标就变成了**求所有这样的正方形的面积总和**. 但显然, 我们不能枚举点对, 需要对其优化.
## 优化
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先, 对于一个对角线长度为$d$的正方形, 其面积$S=\frac{d^2}2$. 再在坐标系上考虑两点$A(x_1,y_1),B(x_2,y_2)$, 以$AB$为对角线的正方形面积:  
$$S=\frac{dist(A,B)}2=\frac{1}2[(x_1-x_2)^2+(y_1-y_2)^2]$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设凸包内整点集合$S$, 我们就需要求:  
$$Ans=\frac{1}2\sum_{A(x_1,y_1),B(x_2,y_2)\in S}(x_1-x_2)^2+(y_1-y_2)^2$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;显然, 我们可以将和式中的前后两项分别计算. 在此只考虑对前一项的求和, 设为$A$, 即:
$$A=\sum_{(x_1,x_2)}(x_1-x_2)^2$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;展开平方:
$$A=\sum_{(x_1,x_2)}x_1^2-2x_1x_2+x_2^2$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在求和意义下, 一三项是等价的, 所以:
$$A=2\sum_{(x_1,x_2)}x^2-2\sum_{(x_1,x_2)}x_1x_2$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在凸包内, 存在许多在一列上的整点, 它们的$x$是相等的, 我们可以借此优化. 对于每个$x_0$, 维护$cntx(x_0)$表示**在竖直直线$y=x_0$上的整点个数**. 于是:
$$A=2|S|\sum_xcntx(x)x^2-2(\sum_xcntx(x)x)^2$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;同理, 设$B$为后一项求和, 则应有:
$$B=2|S|\sum_ycnty(y)y^2-2(\sum_ycnty(y)y)^2$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;枚举$x$或$y$, $O(2\times10^6)$是能够接受的, 接下来我们讨论如何求$cntx$与$cnty$.
### $cnty(y)$:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;要求凸包内纵坐标为$y$的整点个数, 只需要求出左右两侧的点的横坐标即可. 考虑把一个凸包按最高点与最低点的连线分为左右两部分, 如图:  
![tmp1.png](https://i.loli.net/2019/10/25/ojOKpCDm4zsx8cE.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;依次枚举$y$, 并维护$y$值所交左侧凸包的边的上下两点, 所交右侧凸包的上下两点, 暴力解解方程, 得到交点和坐标, 在检查该点附近的整点即可. ( 注意这里不能直接上取整或者下取整, 无良$CF$会卡精度. )
### $cntx(x)$:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;同理, 按最左侧点与最右侧点将凸包分为上下两部分, 枚举$x$, 维护$x$值所交上侧凸包的边的左右两点, 所交下侧凸包的左右两点, 解方程, 检查附近的整点即可.
## 代码
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~又臭又长又慢的典范.~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不过天生励志防抄袭 ( 滑稽 ).
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>

#define Int register int

using namespace std;

struct Point {
	int x, y;
	Point () {}
	Point ( const int _x, const int _y ): x ( _x ), y ( _y ) {}
	inline void Input () { scanf ( "%d %d", &x, &y ); }
	inline void Print () { printf ( "( %d, %d )", x, y ); }
	inline Point Symmetric () { return { y, x }; }
	friend inline bool operator != ( const Point p, const Point q ) { return p.x ^ q.x || p.y ^ q.y; }
};

const int MAXN = 1e5, INF = 0x3f3f3f3f, MAXX = 1e6, EPS = 1e-7;
int n, Cntri, Cntle, Cnthi, Cntlo, Cnty[2 * MAXX + 5] = {}, Cntx[2 * MAXX + 5] = {};
Point p[MAXN + 5] = {}, Highest ( 0, -INF ), Lowest ( 0, INF ), Leftest ( INF, 0 ), Rightest ( -INF, 0 );
Point LeftP[MAXN + 5] = {}, RightP[MAXN + 5] = {}, HighP[MAXN + 5] = {}, LowP[MAXN + 5] = {};

inline bool Cmp1 ( const Point p, const Point q ) {
	return p.x < q.x;
}

inline bool Cmp2 ( const Point p, const Point q ) {
	return p.y > q.y;
}

inline bool Collinear ( const Point p, const Point q, const Point r ) {
	if ( p.x == q.x ) return p.x == r.x;
	if ( p.x == r.x ) return p.x == q.x;
	return 1LL * ( p.y - q.y ) * ( p.x - r.x ) == 1LL * ( p.y - r.y ) * ( p.x - q.x );
}

template<typename _T>
inline _T Abs ( const _T x ) { return x < 0 ? -x : x; }

template<class _T>
inline void Swap ( _T& a, _T& b ) { _T t = a; a = b, b = t; }

inline int Indx ( const int x ) { return x + MAXX; }

inline bool LeftCheck ( const Point p, Point _up, Point _dn ) {
	if ( _up.y < _dn.y ) Swap ( _up, _dn );
	if ( _up.x == _dn.x ) return p.x < _up.x;
	if ( p.x == _dn.x ) return ! ( ( _up.y - _dn.y >= 0 ) ^ ( _up.x - _dn.x >= 0 ) );
	if ( p.x == _up.x ) return ( _up.y - _dn.y >= 0 ) ^ ( _up.x - _dn.x >= 0 );
	if ( ( _up.y - _dn.y >= 0 ) ^ ( _up.x - _dn.x >= 0 ) ) {
		return 1LL * ( p.y - _dn.y ) * ( _up.x - _dn.x ) > 1LL * ( _up.y - _dn.y ) * ( p.x - _dn.x );
	} else {
		return ( ( p.y - _dn.y >= 0 ) ^ ( p.x - _dn.x >= 0 ) )
			|| 1LL * ( p.y - _dn.y ) * ( _up.x - _dn.x ) > 1LL * ( _up.y - _dn.y ) * ( p.x - _dn.x );
	}
}

inline void PrepareX () {
	for ( Int i = 1; i <= n; ++ i ) {
		if ( p[i] != Highest && p[i] != Lowest ) {
			if ( ! LeftCheck ( p[i], Highest, Lowest ) ) {
				RightP[++ Cntri] = p[i];
			} else {
				LeftP[++ Cntle] = p[i];
			}
		}
	}
	int rupper = 1, lupper = 1;
	sort ( RightP + 1, RightP + Cntri + 1, Cmp2 ), sort ( LeftP + 1, LeftP + Cntle + 1, Cmp2 );
	if ( ! Cntri || RightP[1].y ^ Highest.y ) RightP[-- rupper] = Highest;
	if ( ! Cntle || LeftP[1].y ^ Highest.y ) LeftP[-- lupper] = Highest;
	if ( RightP[Cntri].y ^ Lowest.y ) RightP[++ Cntri] = Lowest;
	if ( LeftP[Cntle].y ^ Lowest.y ) LeftP[++ Cntle] = Lowest;
	for ( Int y = Highest.y - 1; y > Lowest.y; -- y ) {
		if ( y < RightP[rupper + 1].y ) ++ rupper;
		if ( y < LeftP[lupper + 1].y ) ++ lupper;
		Point _up = LeftP[lupper], _dn = LeftP[lupper + 1];
		int lx, rx, Choice[5] = {}; double JuncX;
		if ( _up.x == _dn.x ) {
			lx = ceil ( _up.x );
		} else if ( y == _dn.y ) {
			lx = _dn.x;
		} else {
			JuncX = 1.0 * ( _up.x - _dn.x )
						* ( y - _dn.y + 1.0 * ( _up.y - _dn.y ) * _dn.x / ( _up.x - _dn.x ) ) / ( _up.y - _dn.y );
			Choice[2] = ( Choice[1] = floor ( JuncX ) - 1 ) + 1, Choice[4] = ( Choice[3] = ceil ( JuncX ) ) + 1;
			for ( Int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { Choice[i], y }, _up, _dn ) ) {
					lx = Choice[i];
					break;
				} else if ( ! LeftCheck ( { Choice[i], y }, _up, _dn ) ) {
					lx = Choice[i];
					break;
				}
			}
		}
		_up = RightP[rupper], _dn = RightP[rupper + 1];
		if ( _up.x == _dn.x ) {
			rx = floor ( _up.x );
		} else if ( y == _dn.y ) {
			rx = _dn.x;
		} else {
			JuncX = 1.0 * ( _up.x - _dn.x )
						* ( y - _dn.y + 1.0 * ( _up.y - _dn.y ) * _dn.x / ( _up.x - _dn.x ) ) / ( _up.y - _dn.y );
			Choice[2] = ( Choice[1] = ceil ( JuncX ) + 1 ) - 1, Choice[4] = ( Choice[3] = floor ( JuncX ) ) - 1;
			for ( Int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { Choice[i], y }, _up, _dn ) ) {
					rx = Choice[i];
					break;
				} else if ( LeftCheck ( { Choice[i], y }, _up, _dn ) ) {
					rx = Choice[i];
					break;
				}
			}
		}
		Cnty[Indx ( y )] = rx - lx + 1;
	}
}

inline void PrepareY () {
	for ( Int i = 1; i <= n; ++ i ) {
		if ( p[i] != Leftest && p[i] != Rightest ) {
			if ( LeftCheck ( p[i].Symmetric (), Rightest.Symmetric (), Leftest.Symmetric () ) ) {
				LowP[++ Cntlo] = p[i];
			} else {
				HighP[++ Cnthi] = p[i];
			}
		}
	}
	int uleft = 1, dleft = 1;
	sort ( HighP + 1, HighP + Cnthi + 1, Cmp1 ), sort ( LowP + 1, LowP + Cntlo + 1, Cmp1 );
	if ( ! Cnthi || HighP[1].x ^ Leftest.x ) HighP[-- uleft] = Leftest;
	if ( ! Cntlo || LowP[1].x ^ Leftest.x ) LowP[-- dleft] = Leftest;
	if ( HighP[Cnthi].x ^ Rightest.x ) HighP[++ Cnthi] = Rightest;
	if ( LowP[Cntlo].x ^ Rightest.x ) LowP[++ Cntlo] = Rightest;
	for ( Int x = Leftest.x + 1; x < Rightest.x; ++ x ) {
		if ( x > HighP[uleft + 1].x ) ++ uleft;
		if ( x > LowP[dleft + 1].x ) ++ dleft;
		Point _le = HighP[uleft], _ri = HighP[uleft + 1];
		int uy = 0, dy = 0, Choice[5] = {}; double JuncY;
		if ( _le.y == _ri.y ) {
			uy = floor ( _le.y );
		} else if ( x == _ri.x ) {
			uy = _ri.y;
		} else {
			JuncY = _le.y + 1.0 * ( _ri.y - _le.y ) / ( _ri.x - _le.x ) * ( x - _le.x );
			Choice[2] = ( Choice[1] = ceil ( JuncY ) + 1 ) - 1, Choice[4] = ( Choice[3] = floor ( JuncY ) ) - 1;
			for ( Int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { x, Choice[i] }, _le, _ri ) ) {
					uy = Choice[i];
					break;
				} else if ( LeftCheck ( Point ( x, Choice[i] ).Symmetric (), _le.Symmetric (), _ri.Symmetric () ) ) {
					uy = Choice[i];
					break;
				}
			}
		}
		_le = LowP[dleft], _ri = LowP[dleft + 1];
		if ( _le.y == _ri.y ) {
			dy = ceil ( _le.y );
		} else if ( x == _ri.x ) {
			dy = _ri.y;
		} else {
			JuncY = _le.y + 1.0 * ( _ri.y - _le.y ) / ( _ri.x - _le.x ) * ( x - _le.x );
			Choice[2] = ( Choice[1] = floor ( JuncY ) - 1 ) + 1, Choice[4] = ( Choice[3] = ceil ( JuncY ) ) + 1;
			for ( Int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { x, Choice[i] }, _le, _ri ) ) {
					dy = Choice[i];
					break;
				} else if ( ! LeftCheck ( Point ( x, Choice[i] ).Symmetric (), _le.Symmetric (), _ri.Symmetric () ) ) {
					dy = Choice[i];
					break;
				}
			}
		}
		Cntx[Indx ( x )] = uy - dy + 1;
	}
}

inline void Work () {
	scanf ( "%d", &n );
	for ( Int i = 1; i <= n; ++ i ) {
		p[i].Input ();
		if ( p[i].y > Highest.y ) {
			Cnty[Indx ( p[i].y )] = 1;
			Highest = p[i];
		} else if ( p[i].y == Highest.y ) {
			Cnty[Indx ( p[i].y )] = Abs ( p[i].x - Highest.x ) + 1;
		}
		if ( p[i].y < Lowest.y ) {
			Cnty[Indx ( p[i].y )] = 1;
			Lowest = p[i];
		} else if ( p[i].y == Lowest.y ) {
			Cnty[Indx ( p[i].y )] = Abs ( p[i].x - Lowest.x ) + 1;
		}
		if ( p[i].x < Leftest.x ) {
			Cntx[Indx ( p[i].x )] = 1;
			Leftest = p[i];
		} else if ( p[i].x == Leftest.x ) {
			Cntx[Indx ( p[i].x )] = Abs ( p[i].y - Leftest.y ) + 1;
		}
		if ( p[i].x > Rightest.x ) {
			Cntx[Indx ( p[i].x )] = 1;
			Rightest = p[i];
		} else if ( p[i].x == Rightest.x ) {
			Cntx[Indx ( p[i].x )] = Abs ( p[i].y - Rightest.y ) + 1;
		}
	}
	PrepareX ();
	PrepareY ();
	double ResX = 0.0, ResY = 0.0, PointCnt = 0.0;
	double Sqrx = 0.0, Sumx = 0.0;
	for ( Int x = Leftest.x; x <= Rightest.x; ++ x ) {
		PointCnt += Cntx[Indx ( x )];
	}
	for ( Int x = Leftest.x; x <= Rightest.x; ++ x ) {
		Sqrx += 0.5 * Cntx[Indx ( x )] * x * x;
		Sumx += 0.5 * Cntx[Indx ( x )] * x;
	}
	ResX = Sqrx * PointCnt - Sumx * Sumx * 2.0;
	double Sqry = 0.0, Sumy = 0.0;
	for ( Int y = Highest.y; y >= Lowest.y; -- y ) {
		Sqry += 0.5 * Cnty[Indx ( y )] * y * y;
		Sumy += 0.5 * Cnty[Indx ( y )] * y;
	}
	ResY = Sqry * PointCnt - Sumy * Sumy * 2.0;
	printf ( "%.10lf\n", ( ResX + ResY ) / PointCnt / ( PointCnt - 1.0 ) * 2.0 );
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：jr_inf (赞：0)

设对角线长度期望为 $l$，则正方形面积期望为 $\frac{l^2}{2}$，所以我们要计算所有线段长度的平方之和。

猛拆贡献。对于确定的两点，有：
$$
\begin{aligned}
l^2&=(x_0-x_1)^2+(y_0-y_1)^2\\
&=x_0^2-2x_0x_1+x_1^2+y_0^2-2y_0y_1+y_1^2\\
&=x_0^2+y_0^2+x_1^2+y_1^2-2x_0x_1-2y_0y_1\\
\end{aligned}
$$
由于 $|x_i|,|y_i|\leqslant10^6$ 且图形为凸多边形，所以 $\forall |i|\leqslant 10^6$ 我们都可以 $O(1)$ 计算出有多少个点的横坐标为 $i$（纵坐标同理），上式便可快速计算。具体实现见代码及注释。


code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define mst(x,y) memset(x,y,sizeof(x))
using namespace std;
const int N=2e6+10,dlt=1e6,M=1e5+10;
int n,st,mid,l[N],r[N],cnt;
__int128 ans,s,s1;
struct node{int x,y;}a[M],b[M];
void work()
{
	mid=1,cnt=s=s1=st=0;
	mst(l,127);
	mst(r,128);
	for(int i=0;i<n;i++)if(b[i].x<b[st].x)st=i;//从横坐标最小的点开始遍历
	for(int i=st;;i=(i+1)%n)
	{
		a[++cnt]=b[i];
		if(i==(st-1+n)%n)break;
	}
	if((a[1].x==a[n].x)||(long long)(a[1].y-a[2].y)*(a[1].x-a[n].x)<=(long long)(a[1].y-a[n].y)*(a[1].x-a[2].x))reverse(a+2,a+1+n);//保证首先遍历上凸壳
	for(int i=1;i<=n;i++)if(a[i].x>a[mid].x)mid=i;
	for(int i=1;i<mid;i++)//上凸壳
	{
		int j=i+1;
		if(j==n+1)j=1;
		if(a[i].x==a[j].x)continue;
		// 使用点斜式计算
		// k_l=(a[i].y-a[j].y)/(a[i].x-a[j].x)
		// f(x)=k(x-a[i].x)+a[i].y
		for(int k=min(a[i].x,a[j].x);k<=max(a[i].x,a[j].x);k++)
		{
			int x=floor((double)(a[i].y-a[j].y)*(k-a[i].x)/(a[i].x-a[j].x))+a[i].y;
			r[k+dlt]=max(r[k+dlt],x);//由于是凸多边形，所有可取的点都在一个区间内
		}
	}
	for(int i=mid;i<=n;i++)//下凸壳
	{
		int j=i+1;
		if(j==n+1)j=1;
		if(a[i].x==a[j].x)continue;
		for(int k=min(a[i].x,a[j].x);k<=max(a[i].x,a[j].x);k++)
		{
			int x=ceil((double)(a[i].y-a[j].y)*(k-a[i].x)/(a[i].x-a[j].x))+a[i].y;
			l[k+dlt]=min(l[k+dlt],x);
		}
	}
	for(int i=0;i<N;i++)
	{
		if(r[i]==-2139062144)continue;
		__int128 x=r[i]-l[i]+1;
		ans+=(-2)*s*(i-dlt)*x;
		s+=(i-dlt)*x;
		s1+=x;
	}
	for(int i=0;i<N;i++)
	{
		if(r[i]==-2139062144)continue;
		__int128 x=r[i]-l[i]+1;
		ans+=(s1-x)*x*(i-dlt)*(i-dlt);
	}
}
signed main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d%d",&b[i].x,&b[i].y);
	work();
	for(int i=0;i<n;i++)swap(b[i].x,b[i].y);//同理计算纵坐标的贡献
	work();
	printf("%.8lf",(double)ans/(s1*(s1-1)));
}
```

---

