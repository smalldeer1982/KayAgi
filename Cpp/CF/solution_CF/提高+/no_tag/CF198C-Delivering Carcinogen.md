# Delivering Carcinogen

## 题目描述

Qwerty the Ranger arrived to the Diatar system with a very important task. He should deliver a special carcinogen for scientific research to planet Persephone. This is urgent, so Qwerty has to get to the planet as soon as possible. A lost day may fail negotiations as nobody is going to pay for an overdue carcinogen.

You can consider Qwerty's ship, the planet Persephone and the star Diatar points on a plane. Diatar is located in the origin of coordinate axes — at point $ (0,0) $ . Persephone goes round Diatar along a circular orbit with radius $ R $ in the counter-clockwise direction at constant linear speed $ v_{p} $ (thus, for instance, a full circle around the star takes $\frac{2\pi R}{v_p}$ of time). At the initial moment of time Persephone is located at point $ (x_{p},y_{p}) $ .

At the initial moment of time Qwerty's ship is at point $ (x,y) $ . Qwerty can move in any direction at speed of at most $ v $ ( $ v\ge v_{p} $ ). The star Diatar is hot (as all stars), so Qwerty can't get too close to it. The ship's metal sheathing melts at distance $ r $ ( $ r
\le R $ ) from the star.

Find the minimum time Qwerty needs to get the carcinogen to planet Persephone.

## 样例 #1

### 输入

```
10 0 1
-10 0 2 8
```

### 输出

```
9.584544103```

## 样例 #2

### 输入

```
50 60 10
50 60 20 40
```

### 输出

```
0.000000000```

# 题解

## 作者：Twig_K (赞：4)

两者同时运动的过程不好分析，但对于某一个确定的时间 $T_0$，我们很好判断二者是否能在 $T_0$ 相遇。先通过时间算出行星的位置 $(P_x,P_y)$，再算出飞船到达 $(P_x,P_y)$ 的时间 $t$，如果 $t\leq T_0$ 那么可以相遇。


可以判断是否合法，且答案有单调性，因此我们可以二分答案 $T_0$，再用上述方法检查 $T_0$ 是否可行。


------------------------------


然后是二分答案中 check 函数的实现。设要检查的时间为 $T_0$。


1. 线速度为 $v_p$，得出角速度 $w_p=\frac{v_p}{R}$，则逆时针方向旋转的角度 $\theta=w_p t_0$。将点 $(x_p,y_p)$ 绕原点逆时针旋转 $\theta$ 得到点 $(P_x,P_y)$。
[（向量逆时针旋转）](https://www.luogu.com.cn/article/izmdofx0)


2. 求出飞船到 $(P_x,P_y)$ 的时间。


	- 情况一：飞船可以走直线到达目标点。此时线段 $a$ 和圆 $C$ 不交或相切。如图，$t=\frac{|AB|}{v}$。

    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/8yyqed8e.png)

    
    - 情况二：线段 $a$ 和圆 $C$ 有相交，如果直接走的话会与原点靠太近，飞船需要沿着圆 C 走一段圆弧。如图，若弧 $PQ$ 的长度为 $l$，$P,Q$ 为切点，则 $t=\frac{AP+l+BQ}{v}$。


    ![](https://cdn.luogu.com.cn/upload/image_hosting/llfojfzi.png)


3. 判断是否满足 $t\leq T_0$ 即可。


------------


代码写得很丑且很长。


```cpp
#include<bits/stdc++.h>
#define push_back emplace_back
#define For(i,il,ir) for(register int i=il;i<=ir;++i)
#define Forr(i,ir,il) for(register int i=ir;i>=il;--i)
using namespace std;
const double eps=1e-8;
const double PI=acos(-1.0);
int sgn(double x){
    if(fabs(x)<eps) return 0;
    return (x<0)?-1:1;
}

struct Point{
    double x,y;
    void readP(){ scanf("%lf%lf",&x,&y); }
    Point(double x=0.0,double y=0.0):x(x),y(y){}
};
typedef Point Vector;
Vector operator + (Vector A,Vector B){ return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A,Vector B){ return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A,double p){ return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A,double p){ return Vector(A.x/p,A.y/p); }

double Dot(Vector A,Vector B){ return A.x*B.x+A.y*B.y; }
double Cross(Vector A,Vector B){ return A.x*B.y-A.y*B.x; }
double Length(Vector A){ return sqrt(Dot(A,A)); }
double Angle(Vector A,Vector B){ return acos(Dot(A,B)/Length(A)/Length(B)); }
bool OnSeg(Point P,Point A,Point B){ return sgn(Cross(A-P,B-P))==0&&sgn(Dot(A-P,B-P))<0; }//判断是否在线段（不含端点）上 
Vector Rotate(Vector A,double rad){ return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad)); }//向量逆时针旋转 

struct Circle{
    Point O;double r;
};
int getIntersec(Circle C,Point A,Point B,vector<Point>& sol)//求直线和圆的交点 
{
    double a=(B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y);
    double b=2*(B.x-A.x)*(A.x-C.O.x)+2*(B.y-A.y)*(A.y-C.O.y);
    double c=(A.x-C.O.x)*(A.x-C.O.x)+(A.y-C.O.y)*(A.y-C.O.y)-C.r*C.r;
    double delta=b*b-4*a*c;
	if(sgn(delta)<0) return 0;
    if(sgn(delta)==0){ double t=-b/(2*a); sol.emplace_back(A+(B-A)*t); return 1; }
    double t1=(-b-sqrt(delta))/(2*a);
    double t2=(-b+sqrt(delta))/(2*a);
    sol.emplace_back(A+(B-A)*t1);
    sol.emplace_back(A+(B-A)*t2);
    return 2;
}
int getTan(Point P,Circle C,vector<Point>& v)//求过点 P 的与圆 C 相切的切点 
{
    Vector u=P-C.O;
    double d=Length(u);
    if(sgn(d-C.r)<0) return 0;
    if(sgn(d-C.r)==0){ v.emplace_back(P); return 1; }
    double ang=acos(C.r/d);
    Point P1=(Rotate(u,ang))/d*C.r+C.O;
    Point P2=(Rotate(u,-ang))/d*C.r+C.O;
    v.emplace_back(P1),v.emplace_back(P2);
    return 2;
}

Circle C; 
Point Pl,Sh;//planet;ship 
double vp,vs,minr;

bool check(double t)
{
	Point nowP=Rotate(Pl,t*vp);//求此时的行星的坐标 

	//判断线段是否与圆有交点 
	vector<Point> tmp;
	int num=getIntersec(C,Sh,nowP,tmp),fl=0;
	if(num==2) for(int i=0;i<num&&fl==0;++i) if(OnSeg(tmp[i],Sh,nowP)) fl=1;

	if(!fl){ //情况一
		double t2=Length(Sh-nowP)/vs;
		return sgn(t2-t)<=0;
	}else{ //情况二
		vector<Point> ve1,ve2;
		int num1=getTan(nowP,C,ve1);
		int num2=getTan(Sh,C,ve2);
		double t2=1e18;
		For(i,0,num1-1)//这里暴力枚举了，但事实上有对称性 
			For(j,0,num2-1)
			{
				Point P1=ve1[i],P2=ve2[j];
				double tt=Length(P1-nowP)/vs+Length(P2-Sh)/vs;
				double lenr=fabs(Angle(P1-C.O,P2-C.O))*C.r; 
				t2=min(t2,tt+lenr/vs);
				if(sgn(t2-t)<=0) return 1;
			}
		return sgn(t2-t)<=0;
	}
}
signed main()
{
	Pl.readP(),scanf("%lf",&vp),vp=vp/Length(Pl);
	Sh.readP(),scanf("%lf%lf",&vs,&minr);
	C={(Point){0,0},minr};
	
	double L=0,R=1e18;
	while(sgn(R-L)>0){
		double mid=(L+R)/2.0;
		if(check(mid)) R=mid;
		else L=mid;
	}
	printf("%.7lf\n",L);
	return 0;
}
```

---

