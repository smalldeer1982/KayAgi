# [ABC314Ex] Disk and Segments

## 题目描述

在平面直角坐标系中，有 $N$ 条线段，第 $i$ 条的端点是 $(a_i,b_i)$ 和 $(c_i,d_i)$，任意线段不共点。

你要在平面上画一个圆，使得任意一条线段都和圆周或圆内部有至少一个公共点，求满足条件的圆的最小半径，绝对或相对误差不超过 $10^{-5}$。

## 说明/提示

* $2\leq N\leq 100$
* $0\leq a_i,b_i, c_i,d_i\leq1000\ (1\leq i\leq N)$
* $(a_i,b_i)\neq(c_i,d_i)\ (1\leq i\leq N)$

## 样例 #1

### 输入

```
4
2 3 2 10
4 0 12 6
4 8 6 3
7 8 10 8```

### 输出

```
3.319048676309097923796460081961```

## 样例 #2

### 输入

```
20
0 18 4 28
2 21 8 21
3 4 10 5
3 14 10 13
5 9 10 12
6 9 10 6
6 28 10 18
12 11 15 13
12 17 12 27
13 17 20 18
13 27 19 26
16 1 16 13
16 22 19 25
17 22 20 19
18 4 23 4
18 5 23 11
22 16 22 23
23 15 30 15
23 24 30 24
24 0 24 11```

### 输出

```
12.875165712523887403637822024952```

## 样例 #3

### 输入

```
30
526 655 528 593
628 328 957 211
480 758 680 794
940 822 657 949
127 23 250 385
281 406 319 305
277 598 190 439
437 450 725 254
970 478 369 466
421 225 348 141
872 64 600 9
634 460 759 337
878 514 447 534
142 237 191 269
983 34 554 284
694 160 589 239
391 631 22 743
377 656 500 606
390 576 184 312
556 707 457 699
796 870 186 773
12 803 505 586
343 541 42 165
478 340 176 2
39 618 6 651
753 883 47 833
551 593 873 672
983 729 338 747
721 77 541 255
0 32 98 597```

### 输出

```
485.264732620930836460637042310401```

# 题解

## 作者：Purslane (赞：9)

# Solution

以为是一道计算几何的题目，直接放弃，太不牛了！

我们定义 $f(p,l)$ 表示点 $p$ 到线段 $l$ 的距离。

定义 $g(p)$ 为 $\max_{i=1}^n f(p,l_i)$，也就是在点 $p$ 处画圆和所有线段都有交的最小半径。

那么我们要求的是 $\min_{p \in \mathbb {R}^2} g(p)$。

给出一个结论：$g(p)$ 在任意一个方向上二阶偏导（没学过高数，应该是这么叫的吧？）都是非负的。注意可能不可导，本质上要求是下凸的，但是我们又不是学数学的，可以稍微不那么严谨。这样我们就可以三分套三分解决问题。

## Lemma 1

$f(p,l)$ 在线段退化成点之后在任何一个方向上二阶偏导都是非负的。

这个可以直接代数化证明。设点到这条线的距离为 $h$。那么化为证明 $h(x)=\sqrt {x^2+h^2}$ 二阶导大于等于零。显然 

$$h'(x)=\frac{x}{\sqrt{x^2+h^2}}$$

$$h''(x)=\frac{\sqrt{x^2+h^2}-\frac{x^2}{\sqrt{x^2+h^2}}}{x^2+h^2}\ge0$$

得证。

## Lemma 2

$f(p,l)$ 在线段不退化的时候再任何方向上的二阶偏导是非负的。

来张图：

![图](https://s1.ax1x.com/2023/08/12/pPurEwT.png)

在 $1$ 区域，$f(p,l)=f(p,A)$，二阶偏导正的。

在 $2$ 区域，$f(p,l)$ 实际上是直接做垂线，这是个一次函数，二阶偏导是零。

在 $3$ 区域，$f(p,l)=f(p,B)$，二阶偏导正的。

注意线段 $AB$ 可能和我们找的线有交，这样有个地方不可导，但是好像不怎么影响问题。

得证。

## Lemma 3

$g(p)$ 二阶偏导非负。

我们转化为两个问题：有两个二阶偏导非负的函数 $h_1(p)$ 和 $h_2(p)$，让他们求 $\max$ 变成 $h(p)$。

这时候回到下凸的定义：$\forall x_1,x_2 \in R,f(x_1)+f(x_2) \ge2f(\frac{x_1+x_2}{2})$。（可能还是没有那么严谨）

显然，$h_1(x_1)+h_1(x_2) \ge 2h_1(\frac{x_1+x_2}{2})$，$h_2(x_1)+h_2(x_2) \ge 2h_2(\frac{x_1+x_2}{2})$。那么 $\max \{h_1(x_1)+h_2(x_1)\}+ \max\{h_1(x_2)+h_2(x_2)\} \ge h_1(x_1)+h_1(x_2) \ge 2h_1(\frac{x_1+x_2}{2})$。另一个同理。
因此 $\max \{h_1(x_1)+h_2(x_1)\}+ \max\{h_1(x_2)+h_2(x_2)\} \ge \max\{2h_1(\frac{x_1+x_2}{2}),2h_2(\frac{x_1+x_2}{2}) \}$。也就是 $h(x_1)+h(x_2) \ge 2h(\frac{x_1+x_2}{2})$。

得证。

那么我们把 $g$ 当做一个一个函数打擂台即可。

综上，我们证明了 $g$ 函数在任何方向上都是下凸的。可以愉快地使用三分啦！

代码：
```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
const double eps=1e-9;
int n; long double a[MAXN],b[MAXN],c[MAXN],d[MAXN];
long double dis(long double x,long double y,long double X,long double Y) {
	return sqrt((x-X)*(x-X)+(y-Y)*(y-Y));	
}
long double dist(long double x,long double X,long double y,long double Y,long double px,long double py) {
	if(abs(x-X)<=eps) { // 这是一条竖线 
		if(py>=min(y,Y)&&py<=max(y,Y)) return abs(px-x);
		return min(dis(x,y,px,py),dis(X,Y,px,py)); 
	}
	if(abs(y-Y)<=eps) { //这是一条横线
		if(px>=min(x,X)&&px<=max(x,X)) return abs(py-y);
		return min(dis(x,y,px,py),dis(X,Y,px,py));	
	}
	long double k=(Y-y)/(X-x),b=y-k*x;
	long double K=-1/k,B=py-K*px;
	//kx+b=Kx+B
	long double posx=(B-b)/(k-K),posy=k*posx+b;
	if(posx>=min(x,X)&&posx<=max(x,X)) return dis(posx,posy,px,py);
	return min(dis(x,y,px,py),dis(X,Y,px,py));
}
long double solve(long double x,long double y) {
	long double res=0;
	ffor(i,1,n) res=max(res,dist(a[i],c[i],b[i],d[i],x,y));
	return res;	
}
long double calc(long double x) {
	long double l=-30000,r=30000;
	while(r-l>=eps) {
		long double A=l+(r-l)/3,B=l+2*(r-l)/3;
		if(solve(x,A)<=solve(x,B)) r=B;
		else l=A;	
	}
	return solve(x,l);
}
long double gans(void) {
	long double l=-30000,r=30000;
	while(r-l>=eps) {
		long double A=l+(r-l)/3,B=l+2*(r-l)/3;
		if(calc(A)<=calc(B)) r=B;
		else l=A;	
	}
	return calc(l);
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i]>>b[i]>>c[i]>>d[i];
	cout<<fixed<<setprecision(10)<<gans();
	return 0;
}
```

有一点需要注意的，实数三分，你不能向整数三分一样来个 $mid \pm \text{eps}$，因为这样两个函数差值可能很小很小，容易把正解误删掉。因此可以安稳地找两个三等分点。

---

## 作者：zifanoi (赞：5)

题目太水了，用小号发。

题意就是找到距离 $n$ 条线段的最大值最小的一个点，由于 $n\le 100$，精度只有 $10^{-5}$，可以模拟退火。

跟 [P1337](https://www.luogu.com.cn/problem/P1337) 非常相似，改改即可通过。

点的 $x,y$ 坐标值都在 $-1000$ 到 $1000$ 之间，初始温度可以写 $1000$，降温系数 $0.99995$，终止温度 $10^{-7}$。

代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
inline double Rand(){
	return (double)rand()/RAND_MAX;
}
struct node{
	double x,y;
	void in(){scanf("%lf%lf",&x,&y);}
}a[103],b[103];
node operator-(node x,node y){return {x.x-y.x,x.y-y.y};}
double len(node x){return sqrt(x.x*x.x+x.y*x.y);}
int dcmp(double x){return fabs(x)<1e-10?0:x<0?-1:1;}
double dot(node x,node y){return x.x*y.x+x.y*y.y;}
double cross(node x,node y){return x.x*y.y-x.y*y.x;}
double distoseg(node p,node a,node b){
	node x=b-a,y=p-a,z=p-b;
	if(dcmp(dot(x,y))<0)return len(y);
	if(dcmp(dot(x,z))>0)return len(z);
	return fabs(cross(x,y)/len(x));
}
int n;
double t,mn,sx,sy;
double get(double x,double y){
	double ans=0;
	rep(i,1,n)ans=max(ans,distoseg({x,y},a[i],b[i]));
	if(ans<mn)mn=ans,sx=x,sy=y;
	return ans;
}
signed main(){
	srand((unsigned long long)new char);
	scanf("%d",&n);
	rep(i,1,n){
		a[i].in(),b[i].in();
		sx+=(a[i].x+b[i].x)/2.0,sy+=(a[i].y+b[i].y)/2.0;
	}
	sx/=n,sy/=n,mn=get(sx,sy);
	t=1e3;
	double nx=sx,ny=sy;
	while(t>0.0000001){
		double x=nx+t*(Rand()*2-1),y=ny+t*(Rand()*2-1);
		if(exp((get(nx,ny)-get(x,y))/t)>Rand())nx=x,ny=y;
		t*=0.99995;
	}
	rep(i,1,100000){
		double x=sx+t*(Rand()*2-1),y=sy+t*(Rand()*2-1);
		get(x,y);
	}
	printf("%.8lf",mn);
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

### 传送
[AT_abc314_h](https://www.luogu.com.cn/problem/AT_abc314_h)

### 题目
你要在平面上画一个圆，使得任意一条线段都和圆周或圆内部有至少一个公共点，求满足条件的圆的最小半径，绝对或相对误差不超过 $10^{-5}$。

### 题意
很容易想到，本题实际上就是求点到 $n$ 条线段的最短距离的最大值的最小值。

### 思路
本题求最小值，并且对于精度的要求不高，可以想到模拟退火。

令符合题意的点为 $P(x,y)$，考虑对 $x,y$ 退火。\
退火就不细讲了，主要讲讲求点到线段的最短距离。

令该点为 $A$，线段的两端点分别为 $B,C$。

连接 $AB,AC$。\
过点 $A$ 作 $AG\perp BC\text{所在直线}$。

- 若 $G$ 在 $BC$ 上，最短距离为 $AG$（垂线段最短）。
- 若 $G$ 不在 $BC$ 上，最短距离为 $\min(AB,AC)$。

思考如何判定。

首先，若 $G$ 不在 $BC$ 上，那么 $\triangle ABC$ 为钝角三角形，且 $\angle ABC$ 或 $\angle ACB$ 为钝角。

又令 $\triangle ABC$ 中最长边为 $c$，其余两边分别为 $a,b$。

可知：\
若 $c^2>a^2+b^2$，则 $\triangle ABC$ 为钝角三角形。

先判是否为钝角三角形，再判 $\angle ABC$ 或 $\angle ACB$ 是否为钝角（直接判 $c\neq BC$ 是否成立）。

若判定结果为 $G$ 在 $BC$ 上。

先用海伦公式求出 $\triangle ABC$ 的面积，再计算 $AG$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=107;
const double st=1777,ed=1e-14,down=0.997;
int n;
double sx=0,sy=0,nx,ny,x,y,ans,now;

struct line{
	double a,b,c,d;
}l[N];

double ds(double x,double y,double _x,double _y){
	return sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));
}

double s(double a,double b,double c){
	double p=(a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

double com(double x,double y,int id){
	double S1,S2,S3;
	S1=ds(x,y,::l[id].a,::l[id].b);
	S2=ds(x,y,::l[id].c,::l[id].d);
	S3=ds(::l[id].a,::l[id].b,::l[id].c,::l[id].d);
	vector<double> S;
	S.push_back(S1),S.push_back(S2),S.push_back(S3);
	sort(S.begin(),S.end());
	S1=S[0],S2=S[1],S3=S[2];
	if(S1*S1+S2*S2<S3*S3&&S3!=ds(::l[id].a,::l[id].b,::l[id].c,::l[id].d))
		return min<double>(ds(x,y,::l[id].a,::l[id].b),ds(x,y,::l[id].c,::l[id].d));
	return s(S1,S2,S3)*2/ds(::l[id].a,::l[id].b,::l[id].c,::l[id].d);
}

double get(double x,double y){
	double res=-1e9;
	for(int i=1;i<=n;++i)
		res=max<double>(res,com(x,y,i));
	return res;
}

void SA(){
	double t=st;
	x=sx,y=sy;
	while(t>ed){
		nx=x+(rand()*2-RAND_MAX)*t,ny=y+(rand()*2-RAND_MAX)*t;
		now=get(nx,ny);
		if(now<ans)
			ans=now,sx=x=nx,sy=y=ny;
		else if(exp(-abs(now-ans)/t)>double(rand())/RAND_MAX)
			x=nx,y=ny;
		t*=down;
	}
}

signed main(){
	int c=clock();
    srand(time(NULL));
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>l[i].a>>l[i].b>>l[i].c>>l[i].d,
		sx+=l[i].a+l[i].c,sy+=l[i].b+l[i].d;
	sx/=n*2,sy/=n*2;
    ans=get(sx,sy);
    while(clock()-c<1.85*CLOCKS_PER_SEC)
	    SA();
	printf("%.31lf",ans);
	return 0;
}

```

---

## 作者：zgy_123 (赞：3)

[原题](https://www.luogu.com.cn/problem/AT_abc314_h)

题意：求一个半径最小的圆，使每条线段都与圆有交点或相切。

首先看到精度 $10^{-5}$ 和 $1\le n \le 150$ 果断想到退火。

接下来的问题主要是如何计算一个点 $P_1(x_0,y_0)$ 到另一条线段 $l$ 的距离。

设 $l$ 端点分别为 $P_2(x_2,y_2)$ 和 $P_3(x_3.y_3)$，然后明显分为两种情况：

1. 过 $(x_0,y_0)$ 向 $l$ 做高，垂足在 $l$ 上；  
2. 垂足不在 $l$ 上。 

然后就是分别处理。

首先如果是第一种，明显可以求垂足坐标。令垂足为 $H$，步骤如下：

求出 $P_2P_3$ 所在直线斜率：$k_0=\frac{y_2-y_3}{x_2-x_3}$；

求出其所在直线表达式：$y=k_0x+y_2-k_0x_2$；

然后显然 $P_1H$ 所在直线斜率为 $k_1=-\frac{1}{k_0}$，表达式为 $y=k_1x+y_1-k_1x_1$；

求两直线交点，这里令两个方程分别为 $y=ax+b$ 和 $y=cx+d$，则有：

$$H(\frac{b-d}{a-c},\frac{bc-ad}{a-c})$$

所以就求出来了。

如果是第二种，很明显返回到两端点的距离最小值。

即 $\min P_1P_2,P_1P_3$，随后带入距离公式算就行。

到此距离函数就好了。

然后就可以进入主体部分了。退火本身不细说，直接放完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct poi{
	double x,y;
}a[205],ans;
int n;
double mn=2e9;
double rd(int l,int r){return 1.0*rand()/RAND_MAX*(r-l)+l;}
#define d(a,b,c,d) (sqrt((c-a)*(c-a)+(b-d)*(b-d)))
#define mn_dis min(d(x_1,y_1,x_2,y_2),d(x_1,y_1,x_3,y_3))
double dis(poi p1,poi p2,poi p3){
	double x_1=p1.x,x_2=p2.x,x_3=p3.x,y_1=p1.y,y_2=p2.y,y_3=p3.y;
	if(x_2==x_3){
		if(y_1>=min(y_2,y_3)&&y_1<=max(y_2,y_3)) return fabs(x_1-x_2);
		else return mn_dis;
	}
	else if(y_2==y_3){
		if(x_1>=min(x_2,x_3)&&x_1<=max(x_2,x_3)) return fabs(y_1-y_2);
		else return mn_dis;
	}
	double k_0=(y_2-y_3)/(x_2-x_3),k_1=-1/k_0;
	double x=(y_2-y_1-k_0*x_2+k_1*x_1)/(k_1-k_0);
	double y=(y_2*k_1+x_2-k_0*y_1-x_1)/(k_1-k_0);
	if(x>=min(x_2,x_3)&&x<=max(x_2,x_3)) return d(x,y,x_1,y_1);
	else return mn_dis;
}
double calc(poi p){
	double tot=-2e9;
	for(int i=1;i<=n;i++) tot=max(tot,dis(p,a[i*2-1],a[i*2]));
	if(tot<mn) mn=tot,ans=p;
	return tot;
}
void SA(){
	for(double T=100;T>1e-9;T*=0.998){
		poi rd_p={ans.x+rd(-1,1)*T,ans.y+rd(-1,1)*T};
		double del=calc(rd_p)-calc(ans);
		if(exp(-del/T)>rd(0,1)) ans=rd_p;
	}
}
int main(){
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n*2;i++) scanf("%lf%lf",&a[i].x,&a[i].y);
	ans={0,0},mn=calc(ans);
	while(1.0*clock()/CLOCKS_PER_SEC<0.8) SA();
	printf("%.30lf",mn);
	return 0;
}
```

---

闲话：

- 话说这题为什么紫。
- 祝大家 2024 省选 RP++！！！

---

## 作者：Aisaka_Taiga (赞：3)

模拟退火的题解。

题目的难点在于如何计算点到所有线段的距离。

我们可以通过求线段的直线解析式，然后计算与其垂直的直线的斜率，将随机出来的点带入求得直线解析式，然后求两直线交点，判断是否在线段上进行分讨即可，但是我可能写挂了，所以改成用的向量。

![](https://cdn.luogu.com.cn/upload/image_hosting/rlc0hgxi.png)

我们看到有三种情况，我们可以分别来讨论。

当为图 (a) 的情况时，我们可以用叉积来计算，我们都知道叉积的几何意义是以两个向量为边的平行四边形的面积，设向量 $\overrightarrow{AB} (x1,y1),\overrightarrow{AP} (x2,y2))$ 则我们要求的 $PC$ 为:

$$
\frac{(\overrightarrow{AB}\cdot \overrightarrow{AP}) }{|\overrightarrow{AB} |}=\frac{x1\times y2 - x2 \times x1}{|\overrightarrow{AB} |}
$$

当为图 (b) 的情况时，我们要的就是 $|\overrightarrow{BP} |$。

当为图 (c) 的情况时，我们要的就是 $|\overrightarrow{AP} |$。

然后我们利用点乘来判断上述三种情况。

若为 (b) 的情况，$\overrightarrow{BP} $ 在 $\overrightarrow{AB} $ 上的投影向量与 $\overrightarrow{AB} $ 同向；若为 (c) 的情况，$\overrightarrow{AP} $ 在 $\overrightarrow{AB} $ 上的投影向量与 $\overrightarrow{AB} $ 异向。

设 $\overrightarrow{AB}(x1,y1),\overrightarrow{AP}(x2,y2),\overrightarrow{BP}(x3,y3) $。

所以得出结论：


$$
d = 
\left\{\begin{matrix} 
  |\overrightarrow{AP} | & x1 \times x2 + y1 \times y2 < 0\\  
  |\overrightarrow{BP} | & x1 \times x3 + y1 \times y3 > 0\\
  |\overrightarrow{AC} | & others
\end{matrix}\right. 
$$

然后我们就有了一个快速的求以当前点为圆心符合要求的圆半径最小是多少了。

后面就是正常的退火流程了，然后就是痛苦的调参，建议目标温度调小一点，降温系数尽量接近 $1$ 一点，这样能保证精度。

code:

```cpp

#include <bits/stdc++.h>

#define int long long
#define DB double
#define N 10010

using namespace std;

int n;
DB ax, ay, ans;
 
struct sb
{
	DB x, y;
	inline DB len(){return sqrt(x * x + y * y);}
} a[N], b[N];
 
inline sb operator + (const sb &a, const sb &b){return (sb){a.x + b.x, a.y + b.y};}
inline sb operator - (const sb &a, const sb &b){return (sb){a.x - b.x, a.y - b.y};}
inline DB dot(sb a, sb b){return a.x * b.x + a.y * b.y;}
inline DB cross(sb a, sb b){return a.x * b.y - a.y * b.x;}
 
inline DB dis(sb p, sb a, sb b)
{
	sb x = p - a, y = p - b, z = b - a;//向量AP，BP，AB，终点坐标减起点坐标
	if(dot(x, z) < 0) return x.len();//AP在AB的投影向量与AB方向相反，AP向量的模
	else if (dot(y, z) > 0) return y.len();//BP在AB的投影向量与AB方向相同，BP向量的模
	else return fabs(cross(x, z)) / z.len();//利用叉积计算距离
}
 
inline DB calc(DB x, DB y)
{
	DB ans = -1e18;
	for (int i = 1; i <= n; ++i)
		ans = max(ans, dis((sb){x, y}, a[i], b[i]));
	return ans;
}
 
inline void SA()
{
    DB T = 1e3;
    while(T > 1e-13)
    {
		DB tx = ax + (DB)(2 * rand() - RAND_MAX) / RAND_MAX * T;
		DB ty = ay + (DB)(2 * rand() - RAND_MAX) / RAND_MAX * T;
		DB res = calc(tx, ty);
		if(res < ans) ans = res, ax = tx, ay = ty;
		else if(exp((ans - res) / T) * RAND_MAX > rand()) ax = tx, ay = ty;
        T *= 0.9996;
	}
    return ;
}
 
signed main()
{
	srand(time(0));
	cin >> n;
	for(int i = 1; i <= n; i ++)
    {
		cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
		ax += (a[i].x + b[i].x) / 2;
		ay += (a[i].y + b[i].y) / 2;
	}
	ax /= n, ay /= n;
	ans = calc(ax, ay);
	while((DB)clock() / CLOCKS_PER_SEC < 1.5) SA();
	printf("%.10lf\n", ans);
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc314/submissions/44849279)。



---

## 作者：wrkwrkwrk (赞：0)

模拟退火好题。

由于本题精度不高，只有 $10^{-5}$，可以用模拟退火来解决。

具体的，把模拟退火求最小圆覆盖的代码中选择距离当前点最远的点，变成选择距离当前点最远的线段上最近的点即可。

由于有几何模版的存在，故代码比较长，下面给出主要代码，其中 `Line` 表示线段，`NearestPointToLineSegDis` 表示点到线段的距离长度，`NearestPointToLineSeg` 表示点到线段最近的点。完整代码可以看[这里](https://atcoder.jp/contests/abc314/submissions/44580387)。

```cpp
Line lls[105];
int main(){
	srand(time(0));
	int n;
	cin>>n;
	int lx=1000,rx=-1,ly=1000,ry=-1;
	for(int i=1;i<=n;i++){
		cin>>lls[i].e.x>>lls[i].e.y>>lls[i].s.x>>lls[i].s.y;
		lx=min<int>(lx,lls[i].e.x);
		lx=min<int>(lx,lls[i].s.x);
		ly=min<int>(lx,lls[i].e.y);
		ly=min<int>(lx,lls[i].s.y);
		rx=max<int>(lx,lls[i].e.x);
		rx=max<int>(lx,lls[i].s.x);
		ry=max<int>(lx,lls[i].e.y);
		ry=max<int>(lx,lls[i].s.y);//区间范围
	}
	double ans=1e9;
	int d=10;//模拟退火次数
	for(int i=1;i<=d;i++){
		double sx=rand()%(rx-lx+1)+lx,sy=rand()%(ry-ly+1)+ly;
		Point w;
		w.x=sx;w.y=sy;
		double T=100;
		while(T>=1e-7){
			double dis=0;
			Point pp;
			for(int i=1;i<=n;i++){
				if(NearestPointToLineSegDis(w,lls[i])>dis){
					dis=NearestPointToLineSegDis(w,lls[i]);
					pp=NearestPointToLineSeg(w,lls[i]);
				}
			}
			w.x+=(pp.x-w.x)/dis*T;
			w.y+=(pp.y-w.y)/dis*T;
			ans=min(ans,dis);
			T*=0.98;
		}
	}
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

