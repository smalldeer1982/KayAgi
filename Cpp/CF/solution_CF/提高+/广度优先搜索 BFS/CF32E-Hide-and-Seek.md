# Hide-and-Seek

## 题目描述

Victor and Peter are playing hide-and-seek. Peter has hidden, and Victor is to find him. In the room where they are playing, there is only one non-transparent wall and one double-sided mirror. Victor and Peter are points with coordinates $ (x_{v},y_{v}) $ and $ (x_{p},y_{p}) $ respectively. The wall is a segment joining points with coordinates $ (x_{w,1},y_{w,1}) $ and $ (x_{w,2},y_{w,2}) $ , the mirror — a segment joining points $ (x_{m,1},y_{m,1}) $ and $ (x_{m,2},y_{m,2}) $ .

If an obstacle has a common point with a line of vision, it's considered, that the boys can't see each other with this line of vision. If the mirror has a common point with the line of vision, it's considered, that the boys can see each other in the mirror, i.e. reflection takes place. The reflection process is governed by laws of physics — the angle of incidence is equal to the angle of reflection. The incident ray is in the same half-plane as the reflected ray, relative to the mirror. I.e. to see each other Victor and Peter should be to the same side of the line, containing the mirror (see example 1). If the line of vision is parallel to the mirror, reflection doesn't take place, and the mirror isn't regarded as an obstacle (see example 4).

Victor got interested if he can see Peter, while standing at the same spot. Help him solve this problem.

## 样例 #1

### 输入

```
-1 3
1 3
0 2 0 4
0 0 0 1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
0 0
1 1
0 1 1 0
-100 -100 -101 -101
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
0 0
1 1
0 1 1 0
-1 1 1 3
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
0 0
10 0
100 100 101 101
1 0 3 0
```

### 输出

```
YES
```

# 题解

## 作者：SDLTF_凌亭风 (赞：1)

这个题考察计算几何里的**求对称点**和**判断线段是否相交**。  
两个点能互相看到，有以下两个条件（来此初中八年级）：

1. 由于镜子**反面不反光**，那么两者一定出现在镜子的同侧；
2. 光路上不存在墙。

本题坑点如下：
- 墙是有厚度的但是镜子没有；
- 如果光线与墙或镜子共线，也无法通过。

求对称点的方法如下（向量求法）：
```cpp
temp = v + Point(-mirror.vec.y, mirror.vec.x); 
temp = crs(Segment(v, temp), mirror); 
oppo = temp + (temp - v);
```

接下来是判断是否符合条件：
```cpp
bool OK1() { // 判断是否相交
	if(cross(Segment(p, v), mirror, 0)) return false;
	if(cross(Segment(p, v), wall, 1))	return false;
	return true; 
}
bool OK2() { // 判断光线能不能走到
	int ca = sgn((p - mirror.start) ^ mirror.vec);
	int cb = sgn((v - mirror.start) ^ mirror.vec);
	if (!((ca < 0 && cb < 0) || (ca > 0 && cb > 0))) return false;
	if (!cross(Segment(p, oppo), mirror, 0)) return false;
	temp = crs(Segment(p, oppo), mirror);
	if (cross(Segment(p, temp), wall, 1))  return false;
	if (cross(Segment(temp, v), wall, 1))  return false;
	return true;
}

```

以及，我写的计算几何相关模板：
```cpp
namespace LTF {
	typedef long double pos;
	constexpr auto EPS = 1e-6;
	int sgn(pos x) { if (x < -EPS) return -1; if (x > EPS) return 1; else return 0; };

	class Point {
	public:
		pos x, y;
		Point(pos _X = 0, pos _Y = 0)	  { x = _X, y = _Y; }
		Point operator+ (const Point& _v) { return Point(this->x + _v.x, this->y + _v.y); }
		Point operator- (const Point& _v) { return Point(this->x - _v.x, this->y - _v.y); }
		Point operator* (const pos&   _v) { return Point(this->x * _v,   this->y * _v);   }
		pos	  operator^ (const Point& _C) { return this->x * _C.y - this->y * _C.x;	}
	};

	class Segment {
	public:
		Point start, end, vec;
		Segment() {};
		Segment(Point _s, Point _e) { start = _s, end = _e, vec = end - start; }
	};

	Point crs(Segment A, Segment B) {
		pos S1 = (B.start - A.start) ^ A.vec;
		pos S2 = A.vec ^ B.vec;
		return B.start + (B.vec * (S1 / S2));
	}

	bool isOn(Point C, Segment T) {
		if ((C.x < min(T.start.x, T.end.x) - EPS) || (C.x > max(T.start.x, T.end.x) + EPS)) return false;
		if ((C.y < min(T.start.y, T.end.y) - EPS) || (C.y > max(T.start.y, T.end.y) + EPS)) return false;
		return true;
	}

	bool cross(Segment A, Segment B, int md) {
		if (abs(A.vec ^ B.vec) < EPS) {
			if (md == 0) return false;
			if (isOn(A.start, B) || isOn(A.end, B) || isOn(B.start, A) || isOn(B.end, A)) return true;
			return false;
		}
		Point C = crs(A, B);
		return isOn(C, A) && isOn(C, B);
	}
};
```

---

## 作者：Shunpower (赞：0)

简单计算几何题。但是为什么我又搞出来了最难写的东西。

--------

思路还是很简单的。显然我们需要按照两个人是否在镜子的两侧进行分讨。

如果两个人在镜子的异侧，那么显然不可能通过镜子反射视线来使得两个人互相看到。所以我们只需直接判断两个人的连线是否穿墙或者穿镜子就好了，有多种实现方法可以判断。需要注意一下平行线和共点比较恶心。

如果两个人在镜子的同侧，那么除了直接看以外就多了一个选项就是通过镜子。我们可以先把镜子看成一条无限长的直线，然后显然这两个点可以唯一确定一个反射点，我们只需判断入射光线和反射光线是否穿墙，以及反射点是否在镜子的线段范围内即可。

由于我们已经需要一个判断线段相交的函数，所以问题其实只剩下寻找反射点。

由于我不够聪明，所以我想不到对称点！考虑枚举反射点。

注意到，我们可以把镜子表示为一个方向向量 $\boldsymbol{d}$。考虑镜子直线上的一点 $x$，假装它是反射点，那么我们可以获得它到两个人的向量 $\boldsymbol{v}_1,\boldsymbol{v}_2$。

进一步我们可以用点积公式计算 $\cos\langle \boldsymbol{v}_1,\boldsymbol{d} \rangle$ 和 $\cos\langle \boldsymbol{v}_2,\boldsymbol{d} \rangle$，也就是可以算出目前“反射点”到两个人的“光线”和镜子的夹角。

考虑这个夹角有什么用。显然当 $x$ 是真正的反射点的时候我们一定有夹角和为 $\pi$。然后可以发现，随着 $x$ 在镜子直线上移动，夹角和总是呈现单调性（具体要看 $\boldsymbol{d}$ 的方向）。于是考虑夹角和减 $\pi$ 的绝对值，这个东西是一个单谷函数。

于是我们直接三分就能获得反射点了。

我们用镜子的一个端点和这个端点到另一端的向量表示镜子线段，这样就可以直接三分向量的倍数来确定点。

因为我们还要判掉反射点在线段上不存在，所以需要判定一下三分出来的反射点是否满足夹角和为 $\pi$，所以需要注意精度。

写得略有点恶心。

```cpp
double xv,yv;
double xp,yp;
double xw1,yw1,xw2,yw2;
double xm1,ym1,xm2,ym2;
struct Point{
	double x,y;
	friend Point operator+(const Point &p,const Point &q){return {p.x+q.x,p.y+q.y};}
	friend Point operator-(const Point &p,const Point &q){return {p.x-q.x,p.y-q.y};}
	friend Point operator*(const Point &p,const double &q){return {p.x*q,p.y*q};}
	friend double operator*(const Point &p,const Point &q){return p.x*q.x+p.y*q.y;}
	friend Point operator/(const Point &p,const double &q){return {p.x/q,p.y/q};}
	friend double operator^(const Point &p,const Point &q){return p.x*q.y-p.y*q.x;}
};
struct Line{
	Point st,dir;
	double ang;
};
Line mirr,wall;
Point Intersection(Line A,Line B){
	Line AB={A.st,B.st-A.st};
	double t=(AB.dir^B.dir)/(A.dir^B.dir);
	return A.st+A.dir*t;
}
bool sign(double x){
	return x>0;
}
bool Onseg(Point x,Line L){
	double t;
	if(abs(L.dir.x)>eps) t=(x.x-L.st.x)/L.dir.x;
	else t=(x.y-L.st.y)/L.dir.y;
	Point g=L.st+L.dir*t;
	if(abs(g.x-x.x)>eps||abs(g.y-x.y)>eps) return 0;
	if(x.x>max(L.st.x+L.dir.x,L.st.x)+eps||x.x<min(L.st.x+L.dir.x,L.st.x)-eps) return 0;
	if(x.y>max(L.st.y+L.dir.y,L.st.y)+eps||x.y<min(L.st.y+L.dir.y,L.st.y)-eps) return 0;
	return 1;
}
bool Intersection_(Line A,Line B){
	A.ang=atan2(A.dir.y,A.dir.x);
	B.ang=atan2(B.dir.y,B.dir.x);
	if(abs(A.ang-B.ang)<eps||abs(abs(A.ang-B.ang)-pi)<eps){
		if(Onseg(B.st,A)||Onseg(B.st+B.dir,A)) return 1;
		else return 0;
	}
	else{
		Point x=Intersection(A,B);
		if(Onseg(x,B)&&Onseg(x,A)) return 1;
		else return 0;
	}
}
double getlen(Point x){return sqrtl(x.x*x.x+x.y*x.y);}
double Angle(Point x){
	Point l1={xv-x.x,yv-x.y};
	Point l2={xp-x.x,yp-x.y};
	return acos(l1*mirr.dir/getlen(l1)/getlen(mirr.dir))+acos(l2*mirr.dir/getlen(l2)/getlen(mirr.dir));
}
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	cin>>xv>>yv>>xp>>yp;
	cin>>xw1>>yw1>>xw2>>yw2;
	cin>>xm1>>ym1>>xm2>>ym2;
	mirr={{xm1,ym1},{xm2-xm1,ym2-ym1}};
	wall={{xw1,yw1},{xw2-xw1,yw2-yw1}};
	Line mv={{xm1,ym1},{xv-xm1,yv-ym1}},mp={{xm1,ym1},{xp-xm1,yp-ym1}};
	Line vp={{xv,yv},{xp-xv,yp-yv}};
	if(sign(mv.dir^mirr.dir)==sign(mp.dir^mirr.dir)){
		if(!Intersection_(vp,wall)&&!Intersection_(vp,mirr)) return cout<<"YES\n",0;
		double l=0,r=1;
		while(r-l>eps){
			double m1=(r-l)/3.0+l;
			double m2=(r-l)*2.0/3.0+l;
			Point t1=mirr.st+mirr.dir*m1;
			Point t2=mirr.st+mirr.dir*m2;
			if(abs(Angle(t1)-pi)<abs(Angle(t2)-pi)) r=m2;
			else l=m1;
		}
		Point t=mirr.st+mirr.dir*l;
		if(abs(Angle(t)-pi)>1e-8) return cout<<"NO\n",0;
		Line v1={t,{xv-t.x,yv-t.y}};
		Line v2={t,{xp-t.x,yp-t.y}};
		if(Intersection_(v1,wall)||Intersection_(v2,wall)) cout<<"NO\n";
		else cout<<"YES\n";
	}
	else{
		if(Intersection_(vp,wall)||Intersection_(vp,mirr)) cout<<"NO\n";
		else cout<<"YES\n";
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：SmallBlack (赞：0)

一道较为简单但是细节的计算几何题目

- **题目大意**

已知两个点 $A,B$ 和两条线段 $a,b$，$a$ 是一堵墙，$b$ 是一面镜子且只有一面有反光效果，问能不能从 $A$ 点看到 $B$ 点

- **分析**

这道题目明显没有时间或空间限制的问题，我们只需考虑做题思路即可

我们尝试一下分类讨论：

1. 线段 $AB$ 和镜子相交

	因为我们没有其他东西可以改变我们的视线方向，所以不论中间是否有墙隔着，我们的视线都到不了 $B$ 点，故这种情况一定是不行的。

0. 线段 $AB$ 不和镜子相交也不和墙相交

	我们直接从 $A$ 看向 $B$ 即可，这种情况可行。

0. 线段 $AB$ 不和镜子相交但是和墙相交

	这种情况下，运用平面镜成像的知识，我们知道：只要我们可以在镜子里看见 $B$ 点的虚像，那么就可行。
   
   我们再一次分类讨论：设 $B^{'}$ 是 $B$ 点在镜子里的虚像。
   
   I. 线段 $AB^{'}$ 和镜子不相交
   	
   	平面镜成像告诉你看不到 $B$。
   
   这时我们再设 线段 $AB^{'}$ 和镜子交点为 $O$
   
   II. $AO$ 和 $OB$ 中存在一条和墙相交
   	
   	会被挡住，自然是不行的。
   
   III. $AO$ 和 $OB$ 中任意一条都不和墙相交
   	
   	这一情况下可以。

综上，我们就实现了整道题。
   
但是为什么说这道题目细节呢？

我们开康康样例：这是样例4

```
0 0
10 0
100 100 101 101
1 0 3 0
```

可以迅速发现**镜子**和两点是**共线**的，而这个样例的答案为```YES```，所以**镜子是不计厚度**的。

but,有一个测试点是这样的：

```
0 0
3 0
1 0 2 0
-10 2 -12 2
```

这种情况下**墙**和两点是**共线**的，而这个测试点的答案为```NO```，所以**墙是计厚度的**。

所以还需要**特判一下共线的情况**。

整道题目就做完了。

最后的最后，注意你代码的进度问题

- **Codes**

轻喷码风，存在问题还请指出。

```cpp
// Problem: CF32E Hide-and-Seek
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF32E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Date:2023-02-18 13:46:44
// By:SmallBlack
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long s=0,k=1;
	char c=getchar();
	while(!isdigit(c))
	{
		k=(c=='-')?-1:1;
		c=getchar();
	}
	while(isdigit(c))
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*k;
}
#define d read()
#define ll long long
#define Maxn 10000
#define Size 10000
#define pb push_back
#define mp make_pair
#define dou double
#define Vector Point
#define Re register int
const dou eps=1e-6;
inline int dcmp(dou a){return ((a<-eps)?(-1):((a>eps)?1:0));}
inline dou Abs(dou a){return a*dcmp(a);}
struct Point
{
	dou x,y;
	Point(){x=y=0;}
	Point(dou X,dou Y){x=X,y=Y;}
	Point(int X,int Y){x=X,y=Y;}
	Point(ll X,ll Y){x=X,y=Y;}
	inline Point in(){scanf("%lf%lf",&x,&y);return *this;}
	inline void out(){printf("%.2lf %.2lf",x,y);}
	inline bool operator<(const Point &a){return (a.x==x)?(y<a.y):(x<a.x);}
};
inline dou Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
inline dou Cro(Vector a,Vector b){return a.x*b.y-b.x*a.y;}
inline dou Len(Vector a){return sqrt(Dot(a,a));}
inline dou Tan(Vector a){return atan2(a.y,a.x);};
inline dou Angle(Vector a,Vector b){return acos(Dot(a,b)/Len(a)/Len(b));}
inline Vector Normal(Vector a){return Vector(-a.y,a.x);}
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline Vector operator*(Vector a,dou b){return Vector(a.x*b,a.y*b);}
inline Vector operator/(Vector a,dou b){return Vector(a.x/b,a.y/b);}
inline bool operator==(Vector a,Vector b)
	{return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);}
inline Point turn_P0(Point a,dou eta)
{
	dou x=a.x*cos(eta)+a.y*sin(eta);
	dou y=a.y*cos(eta)-a.x*sin(eta);
	return Point(x,y);
}
inline Point turn_P(Point a,Point b,dou eta)
{
	Point p=a-b;
	dou x=p.x*cos(eta)+p.y*sin(eta);
	dou y=p.y*cos(eta)-p.x*sin(eta);
	return Point(x+b.x,y+b.y);
}
struct Line
{
	Point A,B;
	dou k;
	Line(){A=B=Point(0,0),k=1;}
	Line(Point a,Point b):A(a),B(b),k(Tan(b-a)){}
	inline bool isOn(Point p){return dcmp(Cro(p-A,p-B))==0;}
	inline bool operator==(const Line &l)
	{
		dou x=k-l.k;
		while(x<0) x+=acos(-1);
		while(x>=acos(-1)) x-=acos(-1);
		if(dcmp(x)) return 0;
		return isOn(l.A);
	}
	inline Point FootPoint(Point p)
	{
		Vector x=p-A,y=p-B,z=B-A;
		dou len1=Dot(x,z)/Len(z),len2=-1.00*Dot(y,z)/Len(z);
		return A+z*(len1/(len1+len2));
	}
	inline Point Symmetry(Point p){return p+(FootPoint(p)-p)*2;}
	inline Point operator*(const Line &l)
	{
		if(*this==l) return A;
		Vector x=B-A,y=l.B-l.A,z=A-l.A;
		return A+x*(Cro(y,z)/Cro(x,y));
	}
};
struct Segment
{
	Point A,B;
	Segment(Point a=Point(0,0),Point b=Point(0,0)):A(a),B(b){}
	inline Line toLine(){return Line(A,B);}
	inline bool isOn(Point p)
	{
		dou X1=min(A.x,B.x),X2=max(A.x,B.x);
		dou Y1=min(A.y,B.y),Y2=max(A.y,B.y);
		return toLine().isOn(p)&&(X1<=p.x)&&(p.x<=X2)&&(Y1<=p.y)&&(p.y<=Y2);
	}
	inline bool isCrossing_L(Line l){return isOn(l*Line(A,B));}
	inline bool isCrossing_S(Segment S)
	{
		if(toLine()==S.toLine()&&(S.isOn(A)||S.isOn(B)||isOn(S.A)||isOn(S.B)))
			return 1;
		else if(toLine()==S.toLine()) return 0;
		Point O=(toLine()*S.toLine());
		return isOn(O)&&S.isOn(O);
	}
};
int main()
{
	Point A,B;
	A.in(),B.in();
	Segment S(A,B);
	A.in(),B.in();
	Segment W(A,B);
	A.in(),B.in();
	Segment M(A,B);
	if(M.toLine()==S.toLine())
	{
		if(S.isCrossing_S(W)) puts("NO");
		else puts("YES");
		return 0;
	}else if(S.isCrossing_S(M)) return 0&puts("NO");
	if(!S.isCrossing_S(W)&&!S.isCrossing_S(M))	return 0&puts("YES");
	Point B1=M.toLine().Symmetry(S.B);
	if(!M.isCrossing_S(Segment(S.A,B1))) return 0&puts("NO");
	Point O=M.toLine()*Line(S.A,B1);
	Segment S1(S.A,O),S2(O,S.B);
	if(!S1.isCrossing_S(W)&&!S2.isCrossing_S(W)) return 0&puts("YES");
	else puts("NO");
}
```

---

