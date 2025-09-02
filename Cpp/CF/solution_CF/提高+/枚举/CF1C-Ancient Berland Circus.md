# Ancient Berland Circus

## 题目描述

Nowadays all circuses in Berland have a round arena with diameter 13 meters, but in the past things were different.

In Ancient Berland arenas in circuses were shaped as a regular (equiangular) polygon, the size and the number of angles could vary from one circus to another. In each corner of the arena there was a special pillar, and the rope strung between the pillars marked the arena edges.

Recently the scientists from Berland have discovered the remains of the ancient circus arena. They found only three pillars, the others were destroyed by the time.

You are given the coordinates of these three pillars. Find out what is the smallest area that the arena could have.

## 样例 #1

### 输入

```
0.000000 0.000000
1.000000 1.000000
0.000000 1.000000
```

### 输出

```
1.00000000
```

# 题解

## 作者：Loner_Knowledge (赞：38)

这是一道计算几何题

---

题意是求包含给定三点的正多边形最小面积。


如果要求正多边形面积最小，明显正多边形的顶点都在给定三点构成的三角形外接圆上，如图



![13722](https://cdn.luogu.com.cn/upload/pic/13722.png)

已知的是三角形三点坐标，借此可以求出三角形三边长，结合海伦公式$S_{\Delta ABC}=\sqrt{p(p-a)(p-b)(p-c)}\ (p=\frac{a+b+c}{2})$可以求得三角形面积。


可以证明$S_{\Delta ABC}=\frac{ah_{a}}{2}=\frac{ab\sin C}{2}$，结合正弦定理$\frac{a}{\sin A}=\frac{b}{\sin B}=\frac{c}{\sin C}=2R$即可得出三角形外接圆半径$R=\frac{abc}{4S_{\Delta ABC}}$。


根据余弦定理分别求出三角形三边作为弦所对的圆心角的三角函数值，使用反三角函数求出圆心角的度数，由于圆心角的度数皆为正多边形中心角度数的倍数，可以通过求圆心角度数的最大公约数求出正多边形的中心角度数$t$，已知组成正多边形的三角形面积为$S_{\Delta}=\frac{R^{2}\sin t}{2}$，而这样的三角形有$\frac{2\pi}{t}$个，于是正多边形面积为$\frac{\pi R^{2}\sin t}{t}$。


```cpp
#include<cstdio>
#include<cmath>
const double Pi=acos(-1.0);        //π的值
const double EPS=1E-2;            //控制精度
struct Point {
    double x,y;
}P[3];
double len[3],a[3];        //len为边长，a为圆心角角度。
double Get(int i,int j) {    //求两点之间距离
    return sqrt((P[i].x-P[j].x)*(P[i].x-P[j].x)+(P[i].y-P[j].y)*(P[i].y-P[j].y));
}
double gcd(double a,double b) {    //double类型的最大公约数
    if(fabs(b)<EPS)
        return a;
    if(fabs(a)<EPS)
        return b;
    return gcd(b,fmod(a,b));    //fmod(a,b), double类型的取模
}
int main() {
    double t=0.0,A,r;
    for(int i=0;i<3;++i)
        scanf("%lf%lf",&P[i].x,&P[i].y);
    for(int i=0;i<3;t+=len[i],++i)
        len[i]=Get(i,(i+1)%3);
    t/=2;
    A=sqrt(t*(t-len[0])*(t-len[1])*(t-len[2]));    //求三角形面积
    r=len[0]*len[1]*len[2]/(4*A);                //求三角形外接圆半径
    for(int i=0;i<2;++i)
        a[i]=acos(1-len[i]*len[i]/(2*r*r));        //求圆心角度数
    a[2]=2*Pi-a[0]-a[1];                        //为防止误差，最后一个圆心角根据三角形三边作为弦所对的三个圆心角之和为360°求出
    t=gcd(a[0],gcd(a[1],a[2]));                    //求圆心角的最大公约数
    printf("%.6lf",(Pi*r*r*sin(t))/t);            //求正多边形面积
    return 0;
}
```

---

---

## 作者：KAMIYA_KINA (赞：11)

## 前言

这是本人第一次写计算几何的题解，可能会有一些不能理解的地方，欢迎在评论区提问。（退役前应该会回答）

请务必不要在评论区中发布与题目无关的讨论信息以影响他人的观看体验。

## 正文

### 主要思想

**计算几何** ，本题的实质可以转化为求一个以一个给定的三角形为其中三个顶点的正多边形的面积，并且使这个面积最小。

### 前置知识

高中数学必修二：正弦定理和余弦定理， `cmath` 库函数。

### 解题过程

将主要思想中的数学模型抽象出来之后，我们就只用考虑怎么处理就可以了，首先需要处理出三角形的三条边，对于三个定点而言，只要用坐标上求两点距离公式就可以了。

具体实现如下：

~~~cpp
inline db calc(const db x1,const db y1,const db x2,const db y2) {return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));}
~~~

然后对于一个正多边形来说，我们可以发现，这个三角形的外接圆和这个正多边形的外接圆是相同的，这个结论可以用很多方法证明，这里给出一种充分性和必要性的证明方式。

**充分性**：  

利用反证法，假设如果对于一个三角形的外接圆而言，其中一个正多边形有这个三角形的顶点作为顶点的话，其不中有个点不在这个圆上。  

因为一个正多边形可以分解成若干个三角形，所以我们根据每一个点可以将一个正多边形分解成若干个与原三角形全等的三角形，可以很容易证明这些三角形的外心都在同一点，也就是说所有三角形的外接圆都是原三角形的外接圆，也就是说，所有的三角形的顶点都在这个圆上，很明显与所设不符，则假设不成立。  

即证明了这个正多边形的各个顶点都在这个圆上。

**必要性**：
根据证明充分性的方法，将一个正多边形分成若干个三角形，然后这些三角形中一定会有一个与原三角形全等的三角形，然后这个三角形的外接圆一定与原正多边形的外接圆相等。

然后我们可以根据高中所学的正弦定理来算出这个外接圆的半径就可以了。

具体公式如下：
$$
\frac{a}{\sin A} = \frac{b}{\sin B} = \frac{c}{\sin C} = 2R 
$$
$$
S =\frac{1}{2} ab\sin C  =\frac{1}{2}ac\sin B =\frac{1}{2}bc\sin A 
$$
由海伦公式求面积为：
$$
p=\frac{a+b+c}{2}
$$
$$
S=\sqrt{p(p-a)(p-b)(p-c)}
$$
联立解得：
$$
R = \frac{abc}{4S}
$$
紧跟着用余弦定理算出各个边所对的圆心角的度数。
$$
\cos A = \frac{R^2+R^2 -a^2}{2R^2}=1-\frac{a^2}{2R^2}
$$
$$
A = \arccos (1-\frac{a^2}{2R^2})
$$

$B,C$ 同理。

然后就可以算出三条边对应的三条弦在圆中的圆心角来计算三个弦所能得到的最小的正多边形所需要的每个边的圆心角。

设 $T$ 为这个角的度数。
$$
T = \gcd (A,B,C)
$$
最终答案就是：
$$
\frac {\pi R^2 \sin T} {T}
$$
代码如下：

~~~cpp
#include<bits/stdc++.h>
#define db double
using namespace std;
const db pi = acos(-1.0);//获得π的值
const db EPS = 1E-2;
db pos[4][2];//表示三个的位置
inline db calc(const db x1,const db y1,const db x2,const db y2) {return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));}
inline db get_s(const db a,const db b,const db c) {
    db p = (a + b + c) / 2.0;
    return sqrt( p * (p - a) * (p - b) * (p - c));
}//海伦公式求面积
db gcd(db a,db b) {
    if(fabs(b)<EPS)return a;
    if(fabs(a)<EPS)return b;
    return gcd(b,fmod(a,b)); 
}//浮点数求gcd
db a,b,c,A,B,C,S,R;
int main() {
    for(int i = 1; i <= 3; i++) cin >> pos[i][0] >> pos[i][1];
    a = calc(pos[1][0],pos[1][1],pos[2][0],pos[2][1]);
    b = calc(pos[2][0],pos[2][1],pos[3][0],pos[3][1]);
    c = calc(pos[1][0],pos[1][1],pos[3][0],pos[3][1]);//计算出三点之间的距离
    S = get_s(a,b,c);//求得面积
    R = a * b * c / (4.0 * S);//根据上式求得半径
    A = acos(1 - (a * a) / (2 * R * R));
    B = acos(1 - (b * b) / (2 * R * R));
    C = acos(1 - (c * c) / (2 * R * R));//求出三条边所对的圆心角的大小
    db T = gcd(A,gcd(B,C));//获得最终正多边形的各个小三角形的圆心角的大小
    cout << fixed << setprecision(6) << pi * R * R * sin(T) / T << endl;//最终求解
    return 0;
}
~~~

代码中的变量命名与公式几乎一致，应该不会有对比上的区别。




---

## 作者：皎月半洒花 (赞：10)

其实是一道计算几何。

我们首先考虑，对于给出的三个正多边形顶点，两两连边之后，中垂线交于正多边形所在圆心的中点——显然。那么我们可以凭此求出圆心和半径。

之后对于该多边形，我们考虑，由于其让求的正多边形需要**面积最小**，并且对于给出的三个点，由于在正多边形上的原因，所以都应该是**该正多边形相邻两个顶点在外接圆上所对的圆心角的整数倍**

那么我们就做一个`double`类型的$gcd$就好了——因为在外接圆大小一定时（三点已确定一个圆），对于正$n$边形，其面积与$n$成正相关。所以取$gcd$一定是个最好的选择。

最后的面积嘛…大概只需要余弦定理一下就好。此处借鉴的是第一篇题解里面求面积的方法——提醒一句：第三个角必须yong$2\pi$减去另外两个角得到，如果不这样误差会相当的大……尤其是乘上一堆之后，面积会很不精确$qaq$

$\color{red}{C}\color{cyan}{o}\color{gold}{d}\color{green}{e}$1

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std ;
const double Eps = 1e-4 ;
const double Pi = acos(-1.00000) ;
struct Node{
    bool mark ; // 0 = exist, 1 = inexist ;
    double x, y ;
}A, B, C, O, m1, m2, m3 ;
struct Line{
    int mark ;//0 : // x-axis, 1: // y-axis, 2: // normal ;
    double k, b ; double x, y ; // y = kx + b, x = k, y = k ;
}L[12] ; double Len[4], agl[4], R, angle ; int i ;

double get_x(Line A, Line B){ return A.mark == 0 ? A.x : B.x ; } //which is x = k ;
double get_y(Line A, Line B){ return A.mark == 1 ? A.y : B.y ; } //which is y = k ;
double dis(Node A, Node B){ return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y)) ; }
inline Node get_Mid(Node A, Node B){ return (Node){0, (A.x + B.x) / 2, (A.y + B.y) / 2 } ; }
inline Line get_verti(Node n, Line a){
    if (!a.mark) return (Line) {1, 0, 0, 0, n.y} ;
    if (a.mark == 1) return (Line) {0, 0, 0, n.x, 0} ;
    double kk = -1.0 / a.k, bb = n.y - n.x * kk ; return (Line){2, kk, bb, 0, 0 } ;
}
inline Line get_Line(Node A, Node B){
    if (A. y == B. y) return (Line){1, 0, 0, 0, B.y} ;
    if (A. x == B. x) return (Line){0, 0, 0, A.x, 0} ;
    double kk = (A.y - B.y) / (A.x - B.x), bb = A.y - A.x * kk ; return (Line){2, kk, bb, 0, 0} ;
}
inline Node get_inter(Line A, Line B){
    if (A.mark == B.mark && (A.mark == 1 || A.mark == 0) ) return (Node){1, 0, 0 } ;
    if ((A.mark == 1 && B.mark == 0) || (A.mark == 0 && B.mark == 1)) return (Node){0, get_x(A, B), get_y(A, B)} ;
    if (A.mark == 1 && B.mark == 2) return (Node){0, (A.y - B.b) / B.k, A.y} ;
    if (A.mark == 2 && B.mark == 1) return (Node){0, (B.y - A.b) / A.k, B.y} ;
    if (A.mark == 2 && B.mark == 0) return (Node){0, B.x, B.x * A.k + A.b} ;
    if (A.mark == 0 && B.mark == 2) return (Node){0, A.x, A.x * B.k + B.b} ;
    return (Node){0, (A.b - B.b) / (B.k - A.k), (A.b - B.b) / (B.k - A.k) * A.k + A.b} ;  
}
inline double gcd(double a,double b) {  if (fabs(b) < Eps) return a ; if (fabs(a) < Eps) return b ; return gcd(b, fmod(a, b)) ; }
int main(){
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y ; A.mark = B.mark = C.mark = 0 ;
    L[1] = get_Line(A, B), L[2] = get_Line(B, C), L[3] = get_Line(A, C), m1 = get_Mid(A, B), m2 = get_Mid(B, C), m3 = get_Mid(A, C) ;
    L[4] = get_verti(m1, L[1]), L[5] = get_verti(m2, L[2]), O = get_inter(L[4], L[5]), R = (dis(O, A) + dis(O, B) + dis(O, C)) / 3.0 ;
    Len[1] = dis(A, B), Len[2] = dis(B, C), Len[3] = dis(A, C) ; for (i = 1 ; i <= 3 ; ++ i) agl[i] = acos(1 - Len[i] * Len[i] / (2 * R * R) ); 
    agl[3] = 2 * Pi - agl[1] - agl[2], angle = gcd(agl[3], gcd(agl[1], agl[2])), printf("%.6lf\n", (Pi * R * R * sin(angle)) / angle) ; return 0 ;
}
```

吐槽：
* 我用的是斜截式直线方程……这就需要考虑$k$是否存在，于是我就分了好几种情况ORZ
* 这其实是我第一次写计算几何qaq感觉不是很好……一开始没考虑斜率是否是inf……导致一堆nan……qaq

---

## 作者：Limit (赞：10)

我的第一篇CF数论题解呀QAQ，这题还是考验对题目的理解和对三角函数的运用呀QAQ
```cpp
//这个正多边形可以理解为很多个等腰三角形组成的，算出每个三角形的面积和三角形个数，相乘便是总面积
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<string.h>
#include<algorithm>
using namespace std;
const double pi=3.1415926;//π
double mod(double a,double b)//小数取模
{
  return a-(int)(a/b)*b;
}
double gcd(double x,double y)//小数gcd
{
  if(y<=0.0001)return x;
  return gcd(y,mod(x,y));
}
double x,y,x2,y2,x3,y3;
int main()
{
  cin>>x>>y>>x2>>y2>>x3>>y3;
  //计算三角形三条边长
  double a=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
  double b=sqrt((x-x3)*(x-x3)+(y-y3)*(y-y3));
  double c=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
  double p=(a+b+c)/2;
  double r=(a*b*c)/(4*sqrt(p*(p-a)*(p-b)*(p-c)));//通过r=(abc)/(4s)得出外接圆半径
  //分别求出以三条边为低，外接圆半径为腰的三角形的顶角角度
  double angle1=acos(1-(a*a)/(2*r*r));
  double angle2=acos(1-(b*b)/(2*r*r));
  double angle3=2*pi-angle1-angle2;
  double angle=gcd(angle1,gcd(angle2,angle3))/pi*180;//题目所示的以正多边形边长为低接圆半径为腰的三角形的顶角角度
  double side=sqrt(2*r*r-2*r*r*cos(angle/180*pi));//求出正多边形的边长
  double P=(r*2+side)/2;
  double s=sqrt(P*(P-r)*(P-r)*(P-side))/*三角形面积*/*(360/angle)/*三角形个数*/;//计算面积
  cout<<fixed<<setprecision(6)<<s;//保留6位小数输出
  return 0;
}
```


---

## 作者：超级玛丽王子 (赞：4)

~~为什么 CF 的题面都这么磨叽 一句话了事啊~~

这题面翻译成人话就是“求一个面积最小的正多边形来涵盖给定的三个点”。经过分析，这个正多边形的**外接圆**一定就是给定的三点构成的三角形的外接圆。

海伦公式是几何里最基础的公式了，令 $p$ 为 $\triangle ABC$ 的半周长，三角形三边长分别为 $a,b,c$，那么有：

$$S_{\triangle ABC}=\sqrt{p(p-a)(p-b)(p-c)}$$

[海伦公式推导过程戳这里](https://wenku.baidu.com/view/76777692e3bd960590c69ec3d5bbfd0a7856d50b.html#)，由于不是本题解的主要内容，故此不放具体推导。

易知若三角形三边长分别为 $a,b,c$，那么 $S_{\triangle ABC}=\dfrac 1 2 ab\sin C$，推导过程如下：

$$\text{令} \triangle ABC\ a\ \text{边上的高}\ AD\  \text{为}\ h, $$
$$S_{\triangle ABC}=\dfrac 1 2ah$$
$$\because Rt_{\triangle ADC}$$
$$\therefore h=b\ \cdot\ \sin\angle C$$
$$\therefore S_{\triangle ABC}=\dfrac 1 2ab\sin C$$

又有正弦定理：
$$\dfrac a {\sin A}=\dfrac b {\sin B}=\dfrac c {\sin C}=2R$$
可得：
$$R=\dfrac{abc}{4S_{\triangle ABC}}$$
推导过程：
$$\because\dfrac{c}{\sin C}=2R$$
$$\therefore S_{\triangle ABC}=\dfrac 1 2ab\sin C=\dfrac {abc}{4R}$$
$$\therefore R=\dfrac{abc}{4S_{\triangle ABC}}$$
这样我们就可以利用余弦定理和反三角函数计算出三角形的三条弦所对的圆心角的度数。

显而易见的结论是，三条弦所对的圆心角度数的最大公约数 $\alpha$ 就是**正多边形的中心角**。

中心角指的是正多边形相邻两顶点与其中心连线的夹角。正 $n$ 边形中心角的度数是
$$\alpha=\dfrac{360\degree}{n}$$
接下来我们就能推导出正多边形的面积：
$$S=\dfrac{\pi R^2\sin \alpha}{\alpha}$$
推导过程比较复杂，需要认真消化。同时，三角函数一定要学明白。

详细代码这里就不给出了，只是给一个对 `double` 类型做 $\gcd$ 的模板函数：

```cpp
double gcd(double x, double y) {
    while (fabs(x) > eps && fabs(y) > eps) {
        if (x > y)
                x -= floor(x / y) * y;
        else
                y -= floor(y / x) * x;
    }
    return x + y;
}
```

同时也有 $\gcd_{a,b,c}=\gcd_{\gcd_{a,b},c}$

## 完结撒花~ 求赞求互关QAQ

---

## 作者：zplqwq (赞：3)

计算几何。

我终于可以做这种题了啊。


------------


首先我们断言：给定三点的正多边形面积最小当且仅当正多边形的顶点都在给定三点构成的三角形外接圆上。

题目给了三点坐标，那么可以求出三边长，之后不难想到要用海伦公式。

$$ p=\frac{1}{2}(a+b+c) $$

$$ S_{\Delta ABC}=\sqrt{p(p-a)(p-b)(p-c)} $$

接着用外接圆半径公式。

$$ R= 
4S_{\Delta
abc} $$

然后就可以求出圆心角度数，取一个最小公倍数，设为 $k$，那么最后答案是 $\frac{
\pi R^2
 sin k}{k}$ 。
 
 最后注意控制一下精度，取 `1e-2` 其他的精度会出问题。
 
 放一下主函数的代码。
 
 ```cpp
    for(int i=0;i<3;ans+=len[i],i++)
	{
		len[i]=dist(i,(i+1)%3);//dist求距离
	}
	ans/=2;
	ret=sqrt(ans*(ans-len[0])*(ans-len[1])*(ans-len[2]));
	kawaii=len[0]*len[1]*len[2]/(4*ret);
	a[0]=acos(1-len[0]*len[0]/(2*kawaii*kawaii));
	a[1]=acos(1-len[1]*len[1]/(2*kawaii*kawaii));
	a[2]=2*pi-a[0]-a[1];
	ans=gcd(a[0],gcd(a[1],a[2]));
	printf("%.6lf",(pi*kawaii*kawaii*sin(ans))/ans);
 ```
 
 
 

---

## 作者：CHUAN02162 (赞：2)

我觉得前面的大多数题解应该有问题，如果我的思路不对请指正，谢谢。  
前边题解里说之所以用$2\pi$减去两个角得到第三个角，是因为误差。但其实不是这样的。对于第13个测试点，我把图画出来量出三个角大小并计算正弦值，与程序运行结果相差无几，但是做题的时候直接算确实不行，我们用下图（测试点13）举例：  
![测试点13对应的图](https://cdn.luogu.com.cn/upload/image_hosting/crlrzmwo.png)  
在算出$∠AOB$和$∠AOC$之后，之前的题解用$2\pi-∠AOB-∠AOC$来计算$∠BOC$的值。但这样得到的并不是真正的$∠BOC$的值，而是将$C$关于$OA$对称之后得到$C'$（因为是正多边形，所以这个$C'$必然存在），得到的是$∠BOC'$的值，这个值明显比原先的$∠BOC$更大，求出来三个角的$gcd$也更大（这里我也不知道为什么，网上也搜不到相关的解释）。  
因此本题正解还是原先的写法，只不过我觉得前面的题解解释的不太对。以及最后$gcd$为什么更大的问题，麻烦哪位大佬帮忙讲一下，谢谢。


---

## 作者：封禁用户 (赞：2)

题目大意：给出三个点，求出以这三个点为定点的最小正多边形。
求最小正多边形，边数越多，面积越大，所以要是求得的多边形的边尽量的小。
由三个点组成的三角形，可以确定一个外接圆，那么正多边形的所有的定点应该都在圆上，求出三边对应的圆心角，找出圆心角的最大公约数，也就得到了多边形的最小的边数。
防止钝角的情况，边长最长的对应的圆心角 = 2*PI - 其他两个圆心角。
直接贴代码：
```
#include <cstdio>
#include <cstring>
#include <math.h>
#include <algorithm>
using namespace std ;
#define PI acos(-1)
#define eqs 0.01
double gcd(double a,double b)
{
    return a < eqs ? b : gcd(fmod(b,a),a);
}
int main()
{
    double x1 , y1 , x2 , y2 , x3 , y3 ;
    double a , b , c , p , s , r , k ;
    double A , B , C ;
    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) ;
    a = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) ;
    b = sqrt( (x2-x3)*(x2-x3) + (y2-y3)*(y2-y3) ) ;
    c = sqrt( (x1-x3)*(x1-x3) + (y1-y3)*(y1-y3) ) ;
    p = ( a + b + c ) / 2.0 ;
    s = sqrt( p * (p-a) * (p-b) * (p-c) ) ;
    r = a * b * c / ( 4 * s ) ;
    if( a > c )
    {
        k = a ; a = c ; c = k ;
    }
    if( b > c )
    {
        k = b ; b = c ; c = k ;
    }
    A = 2 * asin(a/(2*r)) ;
    B = 2 * asin(b/(2*r)) ;
    C = 2 * PI - A - B ;
    //printf("%lf %lf %lf\n", A, B, C) ;
    p = gcd(A,B);
    p = gcd(p,C) ;
    //printf("%lf %lf\n", r, p) ;
    printf("%.6lf\n", (PI*r*r*sin(p))/p ) ;
    return 0;
}
```

---

## 作者：blackzoo (赞：2)

Codeforces刷题第二天。首先，这是一道计算几何题，大致题意为：给出多边形

三个顶点，求多边形最小面积。我是这样思考的：首先，由三个点确定多边形外接

圆，再求出外接圆半径。第二步，根据余弦定理求出三个角，再求出三边对应圆心

角。第三步，根据题意：多边形边数不超过100，我们可以枚举3~100多边形的中

心角，作除法，若三条边对应圆心角皆可整除中心角，即可找到多边形的最小边长

，继而求得多边形最小面积。

### 海伦公式：![](http://latex.codecogs.com/gif.latex?%5Cinline%20%5Cdpi%7B120%7D%20S%3D%5Csqrt%7Bp%5Cleft%20%28%20p-a%20%5Cright%20%29%5Cleft%20%28%20p-b%20%5Cright%20%29%5Cleft%20%28%20p-c%20%5Cright%20%29%7D%20%5Cleft%20%28%20p%3D%5Cfrac%7Ba&plus;b&plus;c%7D%7B2%7D%20%5Cright%20%29)

### 多边形面积公式：![](http://latex.codecogs.com/gif.latex?%5Cinline%20%5Cdpi%7B120%7D%20S%3D%5Cfrac%7BnR%5E%7B2%7DsinA%7D%7B2%7D) 

最后做了一个小优化：设三角形一个内角为α,则由题意为：![](http://latex.codecogs.com/gif.latex?%5Cdpi%7B120%7D%20%5Calpha%20%5Ccdot%202%5Cdiv%20%5Cleft%20%28%202%5Ccdot%20%5Cpi%20%5Cdiv%20i%20%5Cright%20%29%3D%5Calpha%20%5Cdiv%20%5Cpi%20%5Ccdot%20i)

代码如下：

------------

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define pi 3.1415926
#define eps 1e-4
using namespace std;

struct point
{
    double x,y;
}Ti[3];

double distance(point p1,point p2)        //计算两点之间距离
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double cosine(double a,double b,double c)     //三角形余弦公式
{
    return acos((a*a+b*b-c*c)/(2*a*b));
}

double area(double a,double b,double c)     //计算三角形外接圆半径
{
    double p=(a+b+c)/2;
    double k=a*b*c/4;                      //R=abc/(4S);
    return k/sqrt(p*(p-a)*(p-b)*(p-c));    //海伦公式求三角形面积
}

bool ok(double x)     //判断x是否为整实数(注意精度）
{
    return fabs(x-(int)(x+0.05))<eps;  //加0.05避免出现0.9999类型转化为int型为0
}

int main()
{
    int i,n;
    double f[3],angle[3],quarter,r,s;
    for(i=0;i<3;i++)
        scanf("%lf %lf",&Ti[i].x,&Ti[i].y);
    f[0]=distance(Ti[0],Ti[1]);
    f[1]=distance(Ti[0],Ti[2]);
    f[2]=distance(Ti[1],Ti[2]);   //三角形三边
    angle[0]=cosine(f[1],f[2],f[0])/pi;
    angle[1]=cosine(f[0],f[2],f[1])/pi;
    angle[2]=cosine(f[0],f[1],f[2])/pi;     //三角形三个角（加优化）
    r=area(f[0],f[1],f[2]);
    for(i=3;i<=100;i++)
    {
        if(ok(angle[0]*i)&&ok(angle[1]*i)&&ok(angle[2]*i))     //枚举
        {
            n=i;             //依次去除3~100的多边形对应圆心角，若可以整除，得到多边形边数
            break;
        }
    }
    quarter=2*pi/n;
    s=n*r*r*sin(quarter)/2;       //公式
    printf("%.6lf\n",s);
    return 0;
}

```

---

## 作者：AKOI自动机 (赞：1)

# 这是一道计算几何题（~~废话~~）
### 首先我们%一下笛卡尔、欧几里得、海伦、秦九韶等为此题打下坚实的知识基础的伟大数学家
这道题要用到的知识点：直线方程和直线间夹角、三角形面积公式（所有），三角形外心性质。
##### 我的方法有点不一样，但~~我懒~~代码太丑，所以就不发代码了（逃）
下面是计算思路及过程：    
- 1,利用两点间距离公式dis=$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 求出△ABC的a,b,c;
- 2，利用斜率公式K=$\frac{x_1-x_2}{y_1-y_2}$求出△ABC的三边斜率；
- 3，这是最重要，也是我方法不一样的点：tanθ=abs($\frac{k_1-k_2}{1+k_1\!k_2}$),这样就可以直接求出A,B,C了，但是！，$k_1\!k_2$≠-1才行，而当$k_1\!k_2$=-1时，夹角已经成了90°，tan90°=$\frac{k_1-k_2}{1+k_1\!k_2}$=$\frac{k_1-k_2}{0}$=±∞（可以这么理解吧），所以就需要特判一下，其实在第2步就可以判了，但第2步判有一定局限性，所以就在这一步加特判$k_1\!k_2$=-1的情况。
- 4，S△ABC=$\frac{a\!bsinC}{2}$，R=$\frac{S}{p}$,p=$\frac{a+b+c}{2}$，比正余弦定理方便得多。
- 5，根据三角形外心的性质，求出三个圆心角α、β、γ，为减小误差，γ由360°-α-β求出。
- 6，求θ=gcd(α,β,γ)=gcd(gcd(α,β),γ)，此时θ最大，对应正n边形面积最小,n=$\frac{360}{θ}$，故S_min=$\frac{πr^2sinθ}{θ}$,即可求解。
### 注：第六步gcd手写时有一个fmod函数，可求浮点数除法的余数。π=Arccos(1.0)。
这种类型的计算几何就是手算几何，只要你平面几何，解析几何知识过硬，代码都不是问题。再见！

---

## 作者：aiyougege (赞：1)

### $$\text{Cf1c\ Ancient Berland Circus}$$
#### Solution
　　4:17日:一开始看到这道题还是很有想法的: 找出任意两个点连线的垂直平分线, 多边形的中心就存在在这条线上, 找到中心后根据两个柱子到中心的角度$\alpha$, 多边形相邻两顶点到中心的角度$\beta$, 满足$\beta|\alpha$.

 　　4:27日: 做了这道题, 利用的就是上面这个思路.然后写了好长时间, 码力好弱, 加上自己非常零碎的一点计算几何和解析几何的知识, 最终还是写完了, 然后写了很多函数, 其实根本用不到这么多.具体的介绍一下各个函数的作用吧.

　　这道题细节有点多.所以我是分布写的, 每写完一个函数就用数据检查, 因此花在调试上的精力反而不多.

- gcd(), 求两个浮点数的最小公约数
- Point::***用x,y两个值表示一个点(矢量)***
	- input(), 输入点的坐标
	- print(), 打印点的坐标(x,y)
	- operator+(Point), 矢量的加法
	- operator-(Point), 矢量的减法
	- operator*(int), 矢量的放大与缩小
	- operator*(Point), 矢量的数量积(点乘)
- Line::***用两个点(Point)表示一条直线/线段/矢量***
	- print(), 同Point
	- Length(), 矢量的模长
- Lineo::***用直线的一般式表示一条直线***
	- Convert(Line), 将两点式的直线转化为一般式
- angle(Line), 一条直线的斜率(直线与x轴的夹角的tan值)
- MidPoint(Line), 线段的中点
- MidPlumd(Line), 一条直线的垂直平分线
- InterPoint(Line,Line), 两直线的交点
- CenterPoint(Point,Point,Point), 三个点形成的多边形的几何中心
- TanLine(Point a,Point b,Point c), a与b形成直线与b与c形成直线的夹角的余切值.
- Angle(Point a,Point b,Point c), a与b形成直线与b与c形成直线的夹角.

#### Code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define Phi 3.141592653589793
#define eps 1E-2
using namespace std;

double gcd(double a,double b){
    if(fabs(b)<eps)return a;
    if(fabs(a)<eps)return b;
    return gcd(b,fmod(a,b));
}

struct Point{
	double x,y;
	void input(){cin>>x>>y;}
	void print(){cout<<x<<' '<<y<<'\n';}
	Point operator+(const Point &a)const{
		return (Point){x+a.x,y+a.y};
	}
	Point operator-(const Point &a)const{
		return (Point){x-a.x,y-a.y};
	}
	Point operator*(const double& a)const{
		return (Point){x*a,y*a};
	}
	double operator*(const Point &a)const{
		return x*a.x+y*a.y;
	}
};
typedef Point Vector;
struct Line{
	Point a,b;
	void print(){a.print();b.print();}
	double Length(){
		Vector c=b-a;
		return sqrt(c.x*c.x+c.y*c.y);
	}
};
struct Lineo{
	double a,b,c;
	void Convert(Line s){
		a=s.b.y-s.a.y,b=s.a.x-s.b.x,c=-a*s.a.x-b*s.a.y;
	}
};

double angle(Line a){
	Lineo s;s.Convert(a);
	return s.a/s.b;
}
Point MidPoint(Line l){
	Point ans;ans=l.a+l.b,ans=ans*0.5;
	return ans;
}

Line MidPlumd(Line l){
	Point mid=MidPoint(l);
	Vector delta=l.b-l.a;
	Point z=(Point){mid.x+delta.y,mid.y-delta.x};
	return (Line){mid,z};
}

Point InterPoint(Line a,Line b){
	Lineo l1,l2;l1.Convert(a),l2.Convert(b);
	return (Point){(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b),(l2.a*l1.c-l1.a*l2.c)/(l1.a*l2.b-l2.a*l1.b)};
}

Point CenterPoint(Point a,Point b,Point c){
	Line l1=(Line){a,b};Line l2=(Line){b,c};
	Line l3=MidPlumd(l1),l4=MidPlumd(l2);
	return InterPoint(l3,l4);
}

double TanLine(Point a,Point b,Point c){
	Line l1=(Line){a,b},l2=(Line){b,c};
	double a1=angle(l1),a2=angle(l2);
	return abs((a1-a2)/(1+a1*a2));
}


double Angle(Point a,Point b,Point c){
	double as=TanLine(a,b,c);
	as=atan(as);Vector aa=a-b,bb=c-b;
	if(aa*bb<0)as=3.1415926-as;
	return as;
}

Point a,b,c;
Point root;
double lon;

int main(){
	a.input(),b.input(),c.input();
	root=CenterPoint(a,b,c);
	double a1=Angle(a,root,c),a2=Angle(a,root,b),a3;
	a3=2*Phi-a1-a2;
	double ans=gcd(a1,gcd(a2,a3));
	ans=2*Phi/ans;
	Line bian=(Line){a,root};
	lon=bian.Length();
	printf("%.7f",ans*cos(Phi/ans)*sin(Phi/ans)*lon*lon);
	return 0;
}
```

---

## 作者：hgoicjl (赞：0)

### [blog](https://www.luogu.org/blog/cmine/)内食用更佳
---
### 算法:
~~高中的~~ 解析几何(解三角形) & 枚举

---
~~以下内容并没有图片，请自行脑补~~

### 前置芝士：

<math.h>头文件中有许多有用的函数 ~~(废话)~~

包括 acos(),对一个给定cos值返回$[0,\pi]$内的弧度角

```cpp
double Pi=acos(-1);//一个精度不高的pi
```
以及fmod()可以对浮点数取模

```
double a,b;
b=fmod(b,a);//b对a取模
```

### 数学推论:

我们可以把给定三角形用它的三条边表示,比如$\{A,B,C\}$

每条边对应的角是它相对应的小写字母

根据余弦定理

$\cos(a)=\frac{-a^2+b^2+c^2}{2bc}$

所以有给定三角形的角的cos集合

$\{\cos(a)=\frac{-a^2+b^2+c^2}{2bc},\cos(b)=\frac{a^2-b^2+c^2}{2ac},\cos(c)=\frac{a^2+b^2-c^2}{2ab}\}$

通过$acos()$函数

我们可以得到角的集合

$\{a,b,c\}$

我们设这个三角形的外接圆的圆心是点$R$,半径是$r$

显然有两个结论

$∠ARB=2c,∠ARC=2b,∠BRC=2a$

$r=\frac{A}{\sin(a)}=\frac{A}{1-\cos(a)^2}$

我们可以枚举这个覆盖这个三角形的正多边形

显然在$r$确定的情况下，正多边形的边数越小，它的面积就越小

我们假设得到的正多边形的边数是$s$

考虑每个顶点与这个正多边形重心连线所得到一堆全等的三角形

对于任意的三角形有面积公式

$S=AB\sin(c)$

所以我们可以得到每个小三角形的面积

$S=r^2\sin(\frac{\pi}{s})$ 

所以最后的正大多边形的面积为

$r^2n\sin(\frac{\pi}{s})$

---

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-3;
#define PI acos(-1)
int main()
{
	double x1,y1,x2,y2,x3,y3;
	cin>>x1>>y1>>x2>>y2>>x3>>y3;
	double A=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)),B=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)),C=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
	double cosA=(C*C+B*B-A*A)/(2*B*C),cosB=(C*C+A*A-B*B)/(2*A*C),cosC=(A*A+B*B-C*C)/(2*A*B);
	double r=A/sqrt(1-cosA*cosA)/2.0;
	double degreeARC=2*acos(cosB)/PI*180,degreeARB=2*acos(cosC)/PI*180,degreeBRC=2*acos(cosA)/PI*180;
	int side;
	for(int i=3;i<=100;i++)
	{
		double deg=360/(i*1.0);
		double moda=fmod(degreeARC,deg),modb=fmod(degreeBRC,deg),modc=fmod(degreeARB,deg);
		if(moda>3)
			moda-=deg;
		else if(moda<-3)
			moda+=deg;
		if(modb>3)
			modb-=deg;
		else if(modb<-3)
			modb+=deg;
		if(modc>3)
			modc-=deg;
		else if(modc<-3)
			modc+=deg;
		if(abs(moda)<=eps&&abs(modb)<=eps&&abs(modc)<=eps)
		{
			side=i;
			break;
		}
	}
	printf("%.6lf\n",0.5*sin(2*acos(-1)/side)*side*r*r);
	return 0;
}
```

---

#### 后话
这种方法的浮点误差极大，最大可为0.003，还好CF判的是相对误差

---

