# Commentator problem

## 题目描述

The Olympic Games in Bercouver are in full swing now. Here everyone has their own objectives: sportsmen compete for medals, and sport commentators compete for more convenient positions to give a running commentary. Today the main sport events take place at three round stadiums, and the commentator's objective is to choose the best point of observation, that is to say the point from where all the three stadiums can be observed. As all the sport competitions are of the same importance, the stadiums should be observed at the same angle. If the number of points meeting the conditions is more than one, the point with the maximum angle of observation is prefered.

Would you, please, help the famous Berland commentator G. Berniev to find the best point of observation. It should be noted, that the stadiums do not hide each other, the commentator can easily see one stadium through the other.

## 样例 #1

### 输入

```
0 0 10
60 0 10
30 30 10
```

### 输出

```
30.00000 0.00000
```

# 题解

## 作者：皎月半洒花 (赞：13)

一道被严重低估难度的计算几何。

喂喂凭什么CF1C是个蓝题，这个题这么麻烦是个黄题啊……

首先我们要知道本题问的是什么：

**给出三个互不相交的圆，求一个点使得到这三个圆的切线夹角相同。**

事实上，我们设这点为$T$， 三个圆心分别为$A, B,C$。而事实上，圆$A$的半径$r_A$与$dis(A,T)$的比值，就是$sin(\frac{1}{2}\angle A_1TA_2)$，其中$A_1$和$A_2$是过T的圆A的两条切线与圆的交点。

那么也就是说，我们如果有$\angle A_1TA_2 = \angle B_1TB_2= \angle C_1TC_2$，那么一定有$$\frac{r_A}{dis(A,T)} = \frac{r_B}{dis(B,T)} = \frac{r_C}{dis(C,T)}$$

稍微移一下项，就会有$$\frac{r_A}{r_B} = \frac{dis(A,T)}{dis(B,T)} $$

那么我们就可以发现，对于两个点而言，我们要找的目标点$T$满足到两个点的距离等于一个给定的比例（$r_A$和$r_B$给定）。

事实上，这样的点的轨迹是可以刻画的。我们列一个方程即可：

设比例系数为$k(k \geq 1)$, 那么：

$$\frac{\sqrt{(x_T - x_A)^2 + (y_T - y_A)^2 }}{\sqrt{(x_T - x_B)^2 + (y_T - y_B)^2 }} = k$$

$$\frac{(x_T - x_A)^2 + (y_T - y_A)^2 }{(x_T - x_B)^2 + (y_T - y_B)^2 } = k^2$$

稍微移一下项就会得到$$(k^2-1)x_T^2 + (k^2-1)y_T^2 - 2(k^2y_B - y_A)y_T - 2(k^2x_B - x_A)x_T+k^2x_B^2 - x_A^2 + k^2y_B^2 - y_A^2 = 0$$

看起来有点儿长……我们令$A = k^2-1, C = - 2(k^2x_B - x_A), D = -2(k^2y_B - y_A), E = k^2x_B^2 - x_A^2 + k^2y_B^2 - y_A^2$

那么就会变成$Ax^2 + Ay^2+ Cx + Dy+E = 0$，由于$A,C,D,E$都是常数，所以这是一个**圆的一般方程。**

我们其实也可以发现，当$k=1$时,此时为一条直线（即中垂线），换句话说**当且仅当两个圆半径相等时，点$T$的轨迹是一条直线**。其余的情况则是**一个圆**。

我们不妨先记这种**到两个圆的圆心的距离成定比例的**轨迹为两个圆的**生成曲线**。

那么之后呢，我们发现，圆$A$和圆$C$的生成曲线，与圆$A$和圆$B$的生成曲线，至多有两个交点。那么我们只需要：
* $(1)~~~$判断三组圆的生成曲线是否都相交且交于一点，不是则无解。
* $(2)~~~$对于其中两个圆的生成曲线的交点，判断是否满足条件，即是我们已经找到了符合$$\frac{r_A}{r_B} = \frac{dis(A,T)}{dis(B,T)}$$的点，我们需要判断对于圆$C$是否也满足$$\frac{r_A}{r_C} = \frac{dis(A,T)}{dis(C,T)}$$
* $(3)~~~$如果选取的生成曲线恰好有$2$个交点且两个交点$T',T''$都满足$(2)$中的条件，那么我们选$sin$值最大的（对于$\leq \frac{\pi}{2}$的角，$sin$值与角的大小成正相关）。

然后算法就结束了。中间还有好多好多好多问题，比如圆与圆的交点怎么求，直线与直线的交点怎么求，圆与直线的交点怎么求……不说了，看必修二去吧phhh

ps:我求直线与直线的交点是先转化成斜截式再求的，不是因为别的，只是因为比较熟悉并且更重要的是，我不久前写完一道用斜截式做的计算几何……于是就挪过来用了。

代码很繁琐，轻喷（含注释）：

## $\color{red}{C}\color{cyan}{o}\color{gold}{d}\color{green}{e}$

```cpp

#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std ;
const double Eps = 1e-3 ; int i ;//以下的mark都是记录状态
struct Node{ int mark ; double xa, ya, xb, yb ; } I[5] ; // 0 = inexist, 1 = exist*1, 2 = exist*2 ;
//此处我的Node存的实际上是两个点，即一个一元二次方程的两个解。
struct Line{ int mark ; double k, b ; double x, y ; }L[12] ; //0 : // x-axis, 1: // y-axis, 2: // normal ;
struct Circle{
    int mark ; // 1 : circle ; 0 : Line ;
    double x, y, r ;
    double A, B, C, D, E ;
    Circle friend operator -(const Circle &A, const Circle &B){
        return (Circle){0, A.x - B.x, A.y - B.y, A.r - B.r, A.A - B.A, A.B - B.B, A.C - B.C, A.D - B.D, A.E - B.E} ;
    }
}C[10] ;
double ansx, ansy ; bool check ;

inline bool Comp(Node A, Node B){ return A.mark < B.mark ; }
inline double get_x(Line A, Line B){ return A.mark == 0 ? A.x : B.x ; } //which is (x = k) ;
inline double get_y(Line A, Line B){ return A.mark == 1 ? A.y : B.y ; } //which is (y = k) ;
inline bool equal(double x, double y){ return (x - y <= Eps) && (x - y >= -Eps) ; }
inline double disa(Node A, Node B){ return sqrt((A.xa - B.xa) * (A.xa - B.xa) + (A.ya - B.ya) * (A.ya - B.ya)); }//第一个点之间的距离
inline double disb(Node A, Node B){ return sqrt((A.xb - B.xb) * (A.xb - B.xb) + (A.yb - B.yb) * (A.yb - B.yb)); }//第二个点之间的距离
//呃……我承认两个dis写的很麻烦……但是好像也没什么很简单的法子
inline Node Line_inter(Line A, Line B){//斜截式直线求交点（之前写的直接copy过来的）
    if (A.mark == B.mark && (A.mark == 1 || A.mark == 0) ) return (Node){0, 0, 0, 0, 0} ;
    if ((A.mark == 1 && B.mark == 0) || (A.mark == 0 && B.mark == 1)) return (Node){1, get_x(A, B), get_y(A, B), 0, 0} ;
    if (A.mark == 1 && B.mark == 2) return (Node){1, (A.y - B.b) / B.k, A.y, 0, 0} ;
    if (A.mark == 2 && B.mark == 1) return (Node){1, (B.y - A.b) / A.k, B.y, 0, 0} ;
    if (A.mark == 2 && B.mark == 0) return (Node){1, B.x, B.x * A.k + A.b, 0, 0} ;
    if (A.mark == 0 && B.mark == 2) return (Node){1, A.x, A.x * B.k + B.b, 0, 0} ;
    return (Node){1, (A.b - B.b) / (B.k - A.k), (A.b - B.b) / (B.k - A.k) * A.k + A.b, 0, 0} ;  
}
inline Node get_inter (Circle A, Circle B){//“生成曲线”求交点
    if ((A.mark == 0 && B.mark) || (A.mark && B.mark == 0)){//一条是直线，一个是圆
        if (!A.mark) {Circle C ; C = A, A = B, B = C ;} // B is a line ;
        double a = 1 + (B.C / B.D) * (B.C / B.D), del ;
        double c = A.E - B.E * A.D / B.D + B.E * B.E /((B.D) * (B.D)) ;
        double b = (A.C - B.C * A.D / B.D + 2 * B.C * B.E /((B.D) * (B.D)) ) ; 
        if ((del = (b * b - 4 * a * c)) < -Eps) return (Node){0, 0, 0, 0, 0} ; 
        // printf("%lf %lf %lf %lf\n", a, b, c, del) ;
        double xa =  (-b + sqrt(del)) / (2 * a), xb = (-b - sqrt(del)) / (2 * a) ;
        double ya = -B.C / B.D * xa - B.E / B.D, yb = -B.C / B.D * xb - B.E / B.D ; 
        // cout << "-----------------" << xa << " " << ya << " " << xb << " " << yb << endl ;
        return (Node){2, xa, ya, xb, yb} ;//此处由于误差等原因，不容易判断是否delta=0的情况，所如果delta=0直接记录两遍，不影响结果
    }
    if (!A.mark && !B.mark){
        Line La, Lb ; //两条都是直线，那么就直接转化成斜截式求。
        if (!A.C) La = (Line){1, 0, 0, 0, - A.E / A.D} ; 
        else if (!A.D) La = (Line){0, 0, 0, -A.E / A.C, 0} ; else La = (Line){2, -A.C / A.D, -A.E / A.D, 0, 0} ;
        if (!B.C) Lb = (Line){1, 0, 0, 0, - B.E / B.D} ; 
        else if (!B.D) Lb = (Line){0, 0, 0, -B.E / B.C, 0} ; else Lb = (Line){2, -B.C / B.D, -B.E / B.D, 0, 0} ;  
        return Line_inter(La, Lb) ; 
    } 
    if (A.mark && B.mark){
        Circle C = A - B ; return get_inter(C, A) ;
        //此处需要用到一点小知识，就是两个圆的交点很难求，但是我们可以通过相减求出交线来（必修二知识点），那么就直接把这条线代会第一个if里就好。
    }
}
inline Circle make_rat(Circle A, Circle B){//rat = ratio[n.]比例；比率，用来求生成曲线的函数
    double _k2 = (A.r / B.r) * (A.r / B.r) ; Circle Ans ; double t ; 
    Ans.A = Ans.B = (_k2 - 1), Ans.C = -2 * (_k2 * B.x - A.x), Ans.D = -2 * (_k2 * B.y - A.y), 
    Ans.E = (_k2 * B.x * B.x - A.x * A.x) + (_k2 * B.y * B.y - A.y * A.y), Ans.x = Ans.y = Ans.r = 0 ; 
    if (Ans.A != 0) Ans.mark = 1, t = Ans.A, Ans.A /= t, Ans.B /= t, Ans.C /= t, Ans.D /= t, Ans.E /= t ; else Ans.mark = 0 ; return Ans ;
}
inline void make_for_Ans(){//最后的结果，判断选哪个交点
    sort(I + 1, I + 3, Comp) ;//我闲的，方便一点
    if (I[1].mark <= 1) ansx = I[1].xa, ansy = I[1].ya ;
    else {
        double A1, A11, B1, B11 ;
        I[1] = get_inter(C[4], C[5]) ;
        A1 = disa(I[1], (Node){0, C[1].x, C[1].y, 0, 0}) / C[1].r ; 
        A11 = disa(I[1], (Node){0, C[3].x, C[3].y, 0, 0}) / C[3].r ;
        B1 = disb(I[1], (Node){0, 0, 0, C[1].x, C[1].y}) / C[1].r ; 
        B11 = disb(I[1], (Node){0, 0, 0, C[3].x, C[3].y}) / C[3].r ;
        if (equal(A1, A11) && !equal(B1, B11)) ansx = I[1].xa, ansy = I[1].ya ; 
        else if (!equal(A1, A11) && equal(B1, B11)) ansx = I[1].xb, ansy = I[1].yb ;
        else if (!equal(A1, A11) && !equal(B1, B11)) check = 1 ;//如果在误差范围内都不相等就说明无解。
        else {
            double Ja = sin(1 / A1), Jb = sin(1 / B1) ;//比较角的大小，通过sin来搞
            if (Ja > Jb) ansx = I[1].xa, ansy = I[1].ya ; else ansx = I[1].xb, ansy = I[1].yb ;
        }
    }
}
int main(){
    for (i = 1 ; i <= 3 ; ++ i) cin >> C[i].x >> C[i].y >> C[i].r ;
    C[4] = make_rat(C[1], C[2]), C[5] = make_rat(C[2], C[3]), C[6] = make_rat(C[3], C[1]), 
    I[1] = get_inter(C[4], C[5]), I[2] = get_inter(C[5], C[6]), I[3] = get_inter(C[4], C[6]) ; 
    /*cout << I[1].xa << " " << I[1].xb << " " << I[1].ya << " " << I[1].yb << " " << I[1].mark << endl ;
    cout << I[2].xa << " " << I[2].xb << " " << I[2].ya << " " << I[2].yb << " " << I[2].mark << endl ;
    cout << I[3].xa << " " << I[3].xb << " " << I[3].ya << " " << I[3].yb << " " << I[3].mark << endl ;*/
    if (!I[1].mark || !I[2].mark || !I[3].mark) return putchar('\n'), 0 ; make_for_Ans() ; (!check) ? printf("%.5lf %.5lf", ansx, ansy) : 1 ; return 0 ; 
}

```
PS：
* 这道题我写了好久…大概3h？因为边做变走神+公式难推……
* 233此处向我们最可爱的数学老师lxa致以敬意qaq……前不久刚学的必修二就用上了qwq





























---

## 作者：早右昕 (赞：10)

# 模拟退火+步长控制

显然我们可以用奇奇怪怪的随机算法完成这道题；拿模拟退火来说，我们不妨从三个圆圆心所构成的三角形的重心开始，不断枚举上下左右，利用优劣函数更新最优解，直到满足精度要求；

- 关于移动解问题：从四个方向走一段距离，借用二分思想（存在更优解步长不变，否则步长变为一半），将这段距离更新到eps以下；

- 关于优劣函数：题中要求使视角相同，在(x,y)观察$\odot O$视角开阔程度可以表示为$\tan\alpha$（$\alpha$为在圆心、(x,y)以及过(x,y)的一条$\odot O$的切线的切点所构三角形中，以(x,y)作顶点的角）。我们可以使用“方差”这个概念来求得(x,y)对三个圆的$\tan\alpha$值（视角）的差异程度。

以下是代码：

```cpp
#define de(x) ((x)*(x))
double x[3],y[3],r[3],g[3];
const int dx[]= {-1,0,1,0};
const int dy[]= {0,1,0,-1};
const double eps=1e-6;

double f(double ax,double ay) {
  for(int i=0; i<3; i++) {
    g[i]=sqrt(de(x[i]-ax)+de(y[i]-ay))/r[i];
  }//求tan的值 
  double tmp=0;
  for(int i=0; i<3; i++) {//视角方差，判断视角差异
    tmp+=de(g[i]-g[(i+1)%3]);
  }
  return tmp;
}

int main() {
  double dt=1,ax=0,ay=0;
  for(int i=0; i<3; i++) {
    scanf("%lf%lf%lf",&x[i],&y[i],&r[i]);
    ax+=x[i],ay+=y[i];
  }
  ax/=3,ay/=3;
  while(dt>eps) {
    int fg=-1;
    double ths=f(ax,ay);
    for(int i=0; i<4; i++) {
      double thn=f(ax+dx[i]*dt,ay+dy[i]*dt);
      if(thn<ths) ths=thn,fg=i;
    }
    if(fg<0)dt/=2;
    else ax+=dx[fg]*dt,ay+=dy[fg]*dt;
  }
  if(f(ax,ay)<eps) printf("%.5lf %.5lf\n",ax,ay);
  return 0;
}
//感谢SIO__Five
```


---

## 作者：kczno1 (赞：5)

看到题解都是模拟退火也是震惊的。  
一个点到一个圆的切线角度可以用距离/半径表示。    
解一下方程就可以了。  
我写了很多的特判。。
```cpp
#include<bits/stdc++.h>
using namespace std;

const double eps=1e-7;
int cmp(const double &x)
{
	return x<-eps?-1:x>eps;
}
struct circle
{
	double x,y,r;
	void re()
	{
		cin>>x>>y>>r;
	}
};
circle C1,C2,C3;
double sqr(const double &x)
{
	return x*x;
}
void get(circle C1,circle C2,double &a,double &bx,double &by,double &c)
{
	double k;
#define add(r,x,y,w) k=sqr(r)*w;a+=k;bx-=k*2*x;by-=k*2*y;c+=k*(sqr(x)+sqr(y)); 
	add(C2.r,C1.x,C1.y,1)
	add(C1.r,C2.x,C2.y,-1)
#undef add
	//bx/=a;by/=a;c/=a;
}
void jie(double a,double b,double c,double &x1,double &x2)
{
	if(!cmp(a))
	{
		x1=x2=-c/b;
		return ;
	}
	if(cmp(sqr(b)-4*a*c)<0)exit(0); 
	double s=-b/(2*a),d=sqrt(sqr(b)-4*a*c)/(2*a);
	x1=s+d;x2=s-d;
}
double dis1(double x,double y)
{
	return sqr(x-C1.x)+sqr(y-C1.y);
}

int main()
{
	freopen("1.in","r",stdin);
	C1.re();C2.re();C3.re();
	double a1=0,a2=0,bx1=0,by1=0,c1=0,bx2=0,by2=0,c2=0;
	get(C1,C2,a1,bx1,by1,c1);
	get(C1,C3,a2,bx2,by2,c2);
	double a=a2*bx1-a1*bx2,b=a2*by1-a1*by2,c=a2*c1-a1*c2;
	if(!cmp(a1))
	{
		if(!cmp(a2))
		{
			#define jie(x1,y1,x2,y2) -(c1*y2-c2*y1)/(x1*y2-x2*y1)
			//#define mu(x1,y1,x2,y2) x1*y2-x2*y1
			//	printf("%.5lf %.5lf\n",mu(bx1,by1,bx2,by2),mu(by1,bx1,by2,bx2));
				printf("%.5lf %.5lf\n",jie(bx1,by1,bx2,by2),jie(by1,bx1,by2,bx2));
			#undef jie
			//#undef mu
			return 0;
		}
		a=bx1;b=by1;c=c1;
		swap(a1,a2);swap(bx1,bx2);swap(by1,by2);swap(c1,c2);	
	}
	bool swaped=0;
	if(!cmp(b)){swaped=1;swap(a,b);swap(bx1,by1);}
	a=-a/b;c=-c/b;
	double x1,x2;
	jie( a1*(1+sqr(a)),bx1+a1*2*a*c+by1*a,a1*sqr(c)+by1*c+c1 ,x1,x2);
	double y1=a*x1+c,y2=a*x2+c; 
	if(swaped){swap(x1,y1);swap(x2,y2);}
	if(dis1(x1,y1)>dis1(x2,y2)){swap(x1,x2);swap(y1,y2);}
	printf("%.5lf %.5lf\n",x1,y1);
}

```

---

## 作者：Euler_Pursuer (赞：4)

# 题目概述

题目要求找到一个点，使得到三个圆的两切线张角相同，取最大张角的那个点输出，没有则不输出。

# 题目解析

本题解采用的方法与其他题解不同，没有从解析角度入手，而是采取的几何作图法+向量暴力法。至于模拟退火者就不多说了。

如果设这个张角为 $2\theta$，点圆心距离为 $d$，那么不难知道 $\sin \theta = \dfrac{r}{d}$。因此也就是点到三个圆的 $r,d$ 比要相同。

对于任意两个圆来说， $r,d$ 比相同代表着轨迹就是阿波罗尼斯圆，其实求这个阿波罗尼斯圆可以**不需要**搞出轨迹方程。我们可以求出两圆的四条公切线，同侧切线交点与异侧切线交点就是阿波罗尼斯圆的直径两端。当然，如果两圆半径相同，阿波罗尼斯圆就特化为了两圆心连线的中垂线，这个讨论一下即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/6n05pq3j.png)

因此，我们只需要讨论三类情况：三圆半径相同，两圆半径相同，半径两两不同。

## 三圆半径相同

这个很好做，直接求出三条中垂线，看看它们交点是否同一即可。

## 半径两两不同

这个就需要求出三个阿波罗尼斯圆，求法如上所述。然后我们求解其中两圆的交点，判断两圆交点是否位于第三个圆上。若均位于圆上，那么我们需要比较二者的 $r,d$ 之比，取大的那个即可。

## 两圆半径相同

这个我们就要找出其中一个与两圆半径不同的圆，然后对它与另外两圆求阿波罗尼斯圆。求出来之后，我们只需判断两点是否位于那俩相同半径的圆的圆心中垂线上即可。二者均可则同样比较 $r,d$ 比值即可。

# 代码主体

有两个细节要注意：因为在求解过程中可能出现 $-0.0$ 的情况，没有 spj 的话要注意处理一下。还有这里取的 eps 是 $10^{-6}$，如果取太小了会出现本来有解却变成无解的情况。

代码前面的模板就不写了，加上注释让代码更清爽。

```cpp
inline db zrochk(db x)
{
    if(cmp(x,0.0)==0)
        return 0.0;
    return x;
}

int main()
{
    P<db> o[3];
    db r[3];
    rep(i,0,3)
        scanf("%lf%lf%lf", &o[i].x, &o[i].y, &r[i]);
    if(!cmp(r[0],r[1]) && !cmp(r[1],r[2])) //三圆半径相同
    {
        vector<L<db> > ext;
        P<db> lp[3], itscp[2];
        vector<L<db> > itscl;
        rep(i,0,3)
        {
            lp[i] = (o[i]+o[(i+1)%3])/2;//一定是中垂线
            itscl.pb(L<db>(lp[i], (o[i]-lp[i]).rot90()+lp[i]));//得到轨迹直线
        }
        if(parallel(itscl[0],itscl[1]) || parallel(itscl[1],itscl[2]))//直线有不交的
            return 0;
        itscp[0] = isLL(itscl[0], itscl[1]);//直线交点
        itscp[1] = isLL(itscl[0], itscl[2]);
        if(!cmp(itscp[0].x,itscp[1].x) && !cmp(itscp[0].y,itscp[1].y))//交点相同
        {
            printf("%.5lf %.5lf", zrochk(itscp[0].x), zrochk(itscp[0].y));
        }
    }
    else if(cmp(r[0],r[1]) && cmp(r[1],r[2]) && cmp(r[2],r[0])) //半径都不同
    {
        vector<L<db> > ext, ict;
        P<db> lp[3][2], oo[3];
        db rr[3];
        Polygon<db> ps, ok;//两圆交点，可行解
        rep(i,0,3)
        {
            ict = intanCC(o[i], r[i], o[(i+1)%3], r[(i+1)%3]);//同侧切线
            ext = extanCC(o[i], r[i], o[(i+1)%3], r[(i+1)%3]);//异侧切线
            lp[i][0] = isLL(ict[0], ict[1]);
            lp[i][1] = isLL(ext[0], ext[1]);
            oo[i] = (lp[i][0]+lp[i][1])/2.0;//轨迹圆圆心
            rr[i] = (lp[i][0]-lp[i][1]).abs()/2.0;//轨迹圆半径
        }
        ps = isCC(oo[0], rr[0], oo[1], rr[1]);
        if(ps.size() == 0)//没有交点则无解
            return 0;
        rep(i,0,ps.size())
            if(!cmp((ps[i]-oo[2]).abs(), rr[2]))//点在圆上满足条件
                ok.pb(ps[i]);
        if(ok.size() == 0)
            return 0;
        if(ok.size() == 1)//唯一解
            printf("%.5lf %.5lf", zrochk(ok[0].x), zrochk(ok[0].y));
        else
        {
            if(cmp(r[0]/(ok[0]-o[0]).abs(),r[0]/(ok[1]-o[0]).abs())==1)//观察角度比较
                printf("%.5lf %.5lf", zrochk(ok[0].x), zrochk(ok[0].y));
            else
                printf("%.5lf %.5lf", zrochk(ok[1].x), zrochk(ok[1].y));
        }
    }
    else //存在半径相同的
    {
        if(!cmp(r[0],r[1]))
            swap(r[0],r[2]), swap(o[0],o[2]);
        if(!cmp(r[0],r[2]))
            swap(r[0],r[1]), swap(o[0],o[1]);
        //保证第一个与其他两个不同
        //o[2].write();
        vector<L<db> > ext, ict;
        P<db> lp[2][2], oo[2];
        db rr[2];
        Polygon<db> ps, ok;//两圆交点，可行解
        rep(i,0,2)
        {
            ict = intanCC(o[0], r[0], o[i+1], r[i+1]);//必然有两轨迹是圆
            ext = extanCC(o[0], r[0], o[i+1], r[i+1]);
            lp[i][0] = isLL(ict[0], ict[1]);
            lp[i][1] = isLL(ext[0], ext[1]);
            oo[i] = (lp[i][0]+lp[i][1])/2.0;//轨迹圆圆心
            rr[i] = (lp[i][0]-lp[i][1]).abs()/2.0;//轨迹圆半径
        }
        ps = isCC(oo[0], rr[0], oo[1], rr[1]);
        if(ps.size() == 0)//没有交点则无解
            return 0;
        rep(i,0,ps.size())
        {
            if(cmp((ps[i]-o[1]).abs2(), (ps[i]-o[2]).abs2()) == 0)//判断在中垂线上
                ok.pb(ps[i]);
            //cout << (ps[i]-o[1]).abs2() << ' ' << (ps[i]-o[2]).abs2() << endl;
            //ps[i].write();
        }
        //后面判断同上
        if(ok.size() == 0)
            return 0;
        if(ok.size() == 1)
            printf("%.5lf %.5lf", zrochk(ok[0].x), zrochk(ok[0].y));
        else
        {
            if(cmp(r[0]/(ok[0]-o[0]).abs(),r[0]/(ok[1]-o[0]).abs())==1)//观察角度比较
                printf("%.5lf %.5lf", zrochk(ok[0].x), zrochk(ok[0].y));
            else
                printf("%.5lf %.5lf", zrochk(ok[1].x), zrochk(ok[1].y));
        }
    }
    return 0;
}
```



---

## 作者：Loner_Knowledge (赞：3)


---

题意是在平面上有三个没有公共部分的圆，求平面上一点使得到三个圆的切线的夹角相等。


此题可用模拟退火算法来枚举答案点，可过，然而应该不是正解。


```cpp
#include<cstdio>
#include<cmath>
const double EPS=1E-5;    //控制精度
struct Point {
    double x,y;
    double r;
}P[3];
double Get(double x,double y,const Point b) {    //求两点之间的距离
    return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
}
double Check(double x,double y) {    //估价函数
    double t[3],delta[3],ret=0.0;    //t为当前视角，delta表示误差值
    for(int i=0;i<3;++i)
        t[i]=Get(x,y,P[i])/P[i].r;
    for(int i=0;i<3;++i) {
        delta[i]=t[i]-t[(i+1)%3];
        ret+=delta[i]*delta[i];
    }
    return ret;        //返回误差的平方和
}
int main() {
    bool mark;
    double x=0.0,y=0.0;
    for(int i=0;i<3;++i) {
        scanf("%lf%lf%lf",&P[i].x,&P[i].y,&P[i].r);
        x+=P[i].x/3;
        y+=P[i].y/3;    //设置近似最优解为三个圆圆心构成的三角形重心
    }
    for(double t=1.0,delta;t>EPS;) {    //初始步长为1
        mark=0;                            //搜索标记
        delta=Check(x,y);
        if(Check(x+t,y)<delta) {    //搜索更优解
            x+=t;
            mark=1;
        }
        else if(Check(x-t,y)<delta) {
            x-=t;
            mark=1;
        }
        else if(Check(x,y+t)<delta) {
            y+=t;
            mark=1;
        }
        else if(Check(x,y-t)<delta) {
            y-=t;
            mark=1;
        }
        if(!mark)    //搜索不到调整步长
            t/=2;
    }
    if(fabs(Check(x,y))<EPS)        //检查
        printf("%.5lf %.5lf",x,y);
    return 0;
}
```

正解以后会补上...


---

---

## 作者：zhyh (赞：2)

终于跪过了orzzzzz\
我是用计算几何做的，主要用向量来表达（好像题解里很少这种？）

对于两个体育场 A, B ，如果它们的半径相等，显然观测点在点 A, B 的中垂线上。\
如果它们的半径不相等，记其半径分别为 $r_A, r_B$ ，记观测点为 P ，其距 A, B 的距离分别为 $d_A, d_B$ ，那么有：$ \frac{r_A}{d_A} = \frac{r_B}{d_B}$ ，也就是 $\frac{d_A}{d_B}$ 是一个不为 1 的常数，由高中知识可知，P 的轨迹为一个（阿波罗尼斯）圆。既然知道了这是一个圆，由对称性，直线 AB 为该圆的对称轴，又有 $\frac{d_A}{d_B}$ 已知，就能求出圆与直线 AB 的交点，进而求出这个圆了。

故我们要做的有三种情况：
1. 求直线与直线的交点（当两直线平行时无解）
2. 求直线与圆的交点（当直线与圆相离时无解）
3. 求圆与圆的交点（当**两个圆的半径和圆心距不能构成三角形**时无解）

另外由上可知，若有解，则最多有两解，选择与点 A 更近的那个就行了~

代码如下，求几何信息的细节也在里面，不过请无视掉一些奇怪的命名（写到迷乱就随便命名了qwq）。基本思路就是上面说的那样


```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const double eps = 0.000001;
struct node { double x, y; }; // 定义点
struct vect { double x, y; }; // 定义向量
struct circ { double x, y, r; }; // 定义圆
double dist(node X, node Y)
{
	double dx = X.x - Y.x, dy = X.y - Y.y;
	return sqrt(dx * dx + dy * dy);
}
double leng(vect X)
{
	return sqrt(X.x*X.x + X.y*X.y);
}
int main()
{
	double r1, r2, r3;
	node A, B, C, M, N;
	vect u, v;
	scanf("%lf%lf%lf", &A.x, &A.y, &r1);
	scanf("%lf%lf%lf", &B.x, &B.y, &r2);
	scanf("%lf%lf%lf", &C.x, &C.y, &r3);
	u = (vect) { B.x-A.x, B.y-A.y }; // 向量好啊
	v = (vect) { C.x-A.x, C.y-A.y };
	
	if (r1 == r2 && r1 == r3) { // 情况1：两直线
		if (u.x*v.y == v.x*u.y) return 0; // 两直线平行
		vect du = (vect) { -u.y, u.x }; // 求垂直向量
		vect dv = (vect) { -v.y, v.x };
		M = (node) { A.x+u.x*0.5, A.y+u.y*0.5 };
		N = (node) { A.x+v.x*0.5, A.y+v.y*0.5 };
		double t1; // t2;
		t1 = (N.x*dv.y-N.y*dv.x+dv.x*M.y-dv.y*M.x)/(du.x*dv.y-du.y*dv.x); // 解向量方程
	//	t2 = (M.x*du.y-M.y*du.x+du.x*N.y-du.y*N.x)/(dv.x*du.y-dv.y*du.x); // 重推一遍，利用对称性和上面式子对比来查错qwq
		printf("%.5f %.5f\n", M.x+du.x*t1, M.y+du.y*t1);
	}
	if (r1 == r2 && r1 != r3) { // 情况2：直线与圆
		vect _u = (vect) { -u.y, u.x };
		M = (node) { A.x+u.x*0.5, A.y+u.y*0.5 };
		node P = (node) { A.x+v.x*(r1/(r1+r3)), A.y+v.y*(r1/(r1+r3)) }; // 求圆与对称轴的交点
		node Q = (node) { C.x+v.x*(r3/(r1-r3)), C.y+v.y*(r3/(r1-r3)) }; // 求圆与对称轴的交点
		circ N = (circ) { (P.x+Q.x)*0.5, (P.y+Q.y)*0.5, dist(P, Q)*0.5 }; // 阿氏圆
		vect MN = (vect) { N.x-M.x, N.y-M.y }; // 下面是一坨向量运算
		double dMN = leng(MN), d_u = leng(_u);
		double ddu = (_u.x*MN.x+_u.y*MN.y) / d_u;
		/*
		printf("P : (%lf, %lf)\n", P.x, P.y);
		printf("Q : (%lf, %lf)\n", Q.x, Q.y);
		printf("(%lf, %lf), r = %lf\n", N.x, N.y, N.r);
		*/
		if (ddu*ddu + N.r*N.r < dMN*dMN) return 0;
		double d = sqrt(dMN*dMN-ddu*ddu);
		double dd1 = ddu - sqrt(N.r*N.r-d*d);
		double dd2 = ddu + sqrt(N.r*N.r-d*d);
		node T1 = (node) { M.x+_u.x*dd1/d_u, M.y+_u.y*dd1/d_u };
		node T2 = (node) { M.x+_u.x*dd2/d_u, M.y+_u.y*dd2/d_u };
		if (dist(T1, A) < dist(T2, A)) printf("%.5f %.5f\n", T1.x, T1.y);
		else printf("%.5f %.5f\n", T2.x, T2.y);
	}
	if (r1 != r2 && r1 == r3) { // 情况2：直线与圆，代码与上面完全对称（其实复制一下改了改...）
		vect _v = (vect) { -v.y, v.x };
		N = (node) { A.x+v.x*0.5, A.y+v.y*0.5 };
		node P = (node) { A.x+u.x*(r1/(r1+r2)), A.y+u.y*(r1/(r1+r2)) };
		node Q = (node) { B.x+u.x*(r2/(r1-r2)), B.y+u.y*(r2/(r1-r2)) };
		circ M = (circ) { (P.x+Q.x)*0.5, (P.y+Q.y)*0.5, dist(P, Q)*0.5 };
		vect NM = (vect) { M.x-N.x, M.y-N.y };
		double dNM = leng(NM), d_v = leng(_v);
		double ddv = (_v.x*NM.x+_v.y*NM.y) / d_v;
		if (ddv*ddv + M.r*M.r < dNM*dNM) return 0;
		double d = sqrt(dNM*dNM-ddv*ddv);
		double dd1 = ddv - sqrt(M.r*M.r-d*d);
		double dd2 = ddv + sqrt(M.r*M.r-d*d);
		node T1 = (node) { N.x+_v.x*dd1/d_v, N.y+_v.y*dd1/d_v };
		node T2 = (node) { N.x+_v.x*dd2/d_v, N.y+_v.y*dd2/d_v };
		if (dist(T1, A) < dist(T2, A)) printf("%.5f %.5f\n", T1.x, T1.y);
		else printf("%.5f %.5f\n", T2.x, T2.y);
	}
	if (r1 != r2 && r1 != r3) { // 情况3：两圆，求法同上
		node P, Q;
		P = (node) { A.x+u.x*(r1/(r1+r2)), A.y+u.y*(r1/(r1+r2)) };
		Q = (node) { B.x+u.x*(r2/(r1-r2)), B.y+u.y*(r2/(r1-r2)) };
		circ M = (circ) { (P.x+Q.x)*0.5, (P.y+Q.y)*0.5, dist(P, Q)*0.5 };
		P = (node) { A.x+v.x*(r1/(r1+r3)), A.y+v.y*(r1/(r1+r3)) };
		Q = (node) { C.x+v.x*(r3/(r1-r3)), C.y+v.y*(r3/(r1-r3)) };
		circ N = (circ) { (P.x+Q.x)*0.5, (P.y+Q.y)*0.5, dist(P, Q)*0.5 };
		double d = dist((node){M.x, M.y}, (node){N.x, N.y});
		//printf("d=%lf, M.r=%lf, N.r=%lf\n", d, M.r, N.r);
		if (d >= M.r + N.r) return 0; // 判断两圆是否有交点！
		if (d + M.r <= N.r) return 0;
		if (d + N.r <= M.r) return 0;
		if (abs(M.x-N.x)<eps && abs(M.y-N.y)<eps) return 0;
		double alpha = acos((d*d+M.r*M.r-N.r*N.r) / (d*M.r*2.0)); // 用了个余弦定理
		//printf("cos a = %lf\n", (d*d+M.r*M.r-N.r*N.r) / (d*M.r*2.0));
		//printf("alpha = %lf\n", alpha);
		double cosr = M.r * cos(alpha);
		double sinr = M.r * sin(alpha);
		//printf("cosr = %lf, sinr = %lf\n", cosr, sinr);
		vect MN = (vect) { N.x-M.x, N.y-M.y };
		node S = (node) { M.x+MN.x*cosr/leng(MN), M.y+MN.y*cosr/leng(MN) };
		vect _MN = (vect) { -MN.y, MN.x };
		node T1 = (node) { S.x+_MN.x*sinr/leng(_MN), S.y+_MN.y*sinr/leng(_MN) };
		node T2 = (node) { S.x-_MN.x*sinr/leng(_MN), S.y-_MN.y*sinr/leng(_MN) };
		if (dist(T1, A) < dist(T2, A)) printf("%.5f %.5f\n", T1.x, T1.y);
		else printf("%.5f %.5f\n", T2.x, T2.y);
	}
}
```

---

## 作者：lytqwq (赞：2)

模拟退火过了，写篇题解纪念一下...

既然是模拟退火，就直接rand一个$ \Delta x$
和一个$\Delta y$，估价函数找tan的方差（我也是才知道这么找，说实话确实好了好多

```cpp
double f(double xq,double yq){
	double sum[3]={0,0,0};
	for(int i=0;i<3;i++){
		sum[i]=sqrt((x[i]-xq)*(x[i]-xq)+(y[i]-yq)*(y[i]-yq))/r[i];
	}
	double sum2=0,pj=(sum[0]+sum[1]+sum[2])/3;
	for(int i=0;i<3;i++){
		sum2+=(sum[(i+1)%3]-sum[i])*(sum[(i+1)%3]-sum[i]);
	}
	ovo2=sum[0];
	return sum2*1e5;
}
```



然后就是调参了...


![](https://cdn.luogu.com.cn/upload/image_hosting/jyadm0l6.png)

血泪...

数据2中有个峰值和答案差不多（好像一个估价1e-14，一个估价1e-11，更毒瘤的是这个数据出现了两次）就直接给估价函数的值$*1e5$了，这样应该能更好区分，降温的系数可以小一点$0.75$就挺好了，这样多几次$SA$可以找其他地方的最优解。

最后判断是不是没有的时候，要调大eps，因为如果有个答案的话，不会差太多的，有SPJ，不惧它。之前是为了区分两个解的估价大小而比较小。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
double x[3],y[3],r[3];
double dt=0.75,eps=1e-5,ans;
double x1=0,y2=0,ovo,ovo2,ci=1;
double f(double xq,double yq){
	double sum[3]={0,0,0};
	for(int i=0;i<3;i++){
		sum[i]=sqrt((x[i]-xq)*(x[i]-xq)+(y[i]-yq)*(y[i]-yq))/r[i];
	}
	double sum2=0,pj=(sum[0]+sum[1]+sum[2])/3;
	for(int i=0;i<3;i++){
		sum2+=(sum[(i+1)%3]-sum[i])*(sum[(i+1)%3]-sum[i]);
	}
	ovo2=sum[0];
	return sum2*1e5;
}
void SA(){
	double T=2000/ci,nowans=0;
	double nx1=x1,ny2=y2;
	while(T>eps){
		double qwq=((rand()*1.0/RAND_MAX)>0.5?-1:1)*rand()*T*1/RAND_MAX,qwq2=((rand()*1.0/RAND_MAX)>0.5?-1:1)*rand()*T*1/RAND_MAX;
		if(fabs(nx1+qwq)>1000||fabs(ny2+qwq2)>1000) {continue;}
		double ans2=f(qwq+nx1,qwq2+ny2);
		if(ans2<ans||(ans2-ans<eps&&ovo<ovo2)){
			ans=nowans=ans2;
			x1=nx1+qwq;
			y2=ny2+qwq2;
			nx1+=qwq,ny2+=qwq2;
		}
		else if(exp((-ans2+ans)/T)*RAND_MAX>rand()) nowans=ans2,nx1+=qwq,ny2+=qwq2;
		T*=dt;
	}
	return ;
}
void Slove(){
	ans=f(x1,y2);
	ovo=sqrt((x[0]-x1)*(x[0]-x1)+(y[0]-y2)*(y[0]-y2))/r[0];
	SA();
		SA();	SA();	SA();	SA();	SA();	SA();	SA();	SA();	SA();	SA();	SA();	SA();	SA();
	while((double)clock()/CLOCKS_PER_SEC<0.95) SA();
}
int main(){
	srand(time(NULL));
	srand(rand());
	srand(rand());
	srand(rand());
	srand(rand());
	for(int i=0;i<3;i++){
		scanf("%lf%lf%lf",&x[i],&y[i],&r[i]);
		x1+=x[i]/3;y2+=y[i]/3;
	}
	Slove();
//	printf("%lf %lf\n%lf\n",x1,y2,f(x1,y2));
	if(f(x1,y2)<eps*100)printf("%.5lf %.5lf",x1,y2);
} 
/*
0 0 10
100 100 10
200 0 20
*/
```

~~过不了的话可以再调调找找经验然后教我qwq~~

~~我才不会告诉你我好像过不了第二遍了~~


---

## 作者：_AlieZ (赞：2)

   本蒟蒻初学模拟退火，刚看到这题的时候没想到退火怎么写，于是参考了一下题解，但是发现好像和我之前看的退火不太一样，都没有初始温度，降温系数等等参数，感觉好像并没有什么随机性？（个人感觉，如有错误，欢迎各位大佬科普）于是对着之前的板子改了一下，写了一个参数齐全的版本，交了一发A了2333


```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int maxn=5;
const double eps=1e-6;
const int INF=1e9;
int n;
double r[maxn];
double minans=INF;
struct point
{
    double x,y;
    point ():x(0),y(0){}
    point (double a,double b):x(a),y(b){}
    double dis(point &b){return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));}
    point operator + (point b){return point(x+b.x,y+b.y);}
    point operator - (point b){return point(x-b.x,y-b.y);}
    point operator * (double p){return point(x*p,y*p);}
    point operator / (double p){return point(x/p,y/p);}
}p[maxn],now;
double sqr(double x)
{
    return x*x;
}
double calc(point &a)
{
    //printf("dis:%.5lf %.5lf %.5lf\n",p[1].dis(a)/r[1],p[2].dis(a)/r[2],p[3].dis(a)/r[3]);
    return (sqr(p[1].dis(a)/r[1]-p[2].dis(a)/r[2])+sqr(p[1].dis(a)/r[1]-p[3].dis(a)/r[3])+sqr(p[2].dis(a)/r[2]-p[3].dis(a)/r[3]))*1e8;
    //此处的乘1e8是关键，之前怎么改都算不出答案，而且算出来的都是跑偏了很多的，看了一下之前的代码，
    //好像估价函数的值都比较大，于是就尝试性的乘了一个1e8，然后就对了23333，也不知道是什么原理，
    //目前能想到的是是不是保证温度较高时check函数中的转移概率维持在一个较低的水平，防止解乱跳
    //如果有大佬知道其中的原理欢迎在评论区留言赐教
}
int check(double d,double T)
{
    double a=1.0*rand();
    double b=exp(-d/T)*RAND_MAX;
    //printf("pp:%.5lf %.5lf %.5lf %.5lf\n",a,b,exp(-d/T),-d/T);
    return (d<0)||(a<b);
}
void solve(point &initp,double initT,double dec,double endT)
{
    double temp=initT;
    now=initp;
    double nowans=calc(now);
    //srand((unsigned int)time(0));
    while(temp>endT)
    {
        point next(now.x+temp*(1.0*rand()*2/RAND_MAX-1),now.y+temp*(1.0*rand()/RAND_MAX*2-1));
        double ans=calc(next);
        if(check(ans-nowans,temp))
        {
            //printf("%.5lf %.5lf %.5lf %.3lf %.3lf\n",ans-nowans,ans,temp,next.x,next.y);
            nowans=ans;
            now=next;
        }
        temp*=dec;
    }
}
int main()
{
    point init;
    for(int i=1;i<=3;i++)
    {
        scanf("%lf %lf %lf",&p[i].x,&p[i].y,&r[i]);
        init=init+p[i];
    }
    init=init/3;
    for(int i=1;i<=4;i++)
        solve(init,10,0.99815,1e-14);
    if(calc(now)<eps)
        printf("%.5lf %.5lf\n",(fabs(now.x)<1e-5)?fabs(now.x):now.x,(fabs(now.y)<1e-5)?fabs(now.y):now.y);
        //有时候会出现-0.00000的情况，所以加了个三目运算符
    else
        printf("\n");
    return 0;
}
```
本人第一次写博客，格式什么的都不怎么会弄，写的也不咋样，如有不对的地方欢迎指出。

---

