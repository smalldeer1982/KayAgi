# [PKUSC2018] PKUSC

## 题目描述

九条可怜是一个爱玩游戏的女孩子。

最近她在玩一个无双割草类的游戏，平面上有 $n$ 个敌人，每一个敌人的坐标为 $x_i,y_i$。可怜有一个技能是在平面上画一个 $m$ 个点的简单多边形，并消灭所有**严格**在多边形内部的敌人。

不难发现如果想要快速的消灭敌人的话，只要画一个足够大的简单多边形就行了。但是这样的游戏性就太差了。于是可怜打算为游戏增加一定的随机性。

可怜在平面上随便画了一个 $m$ 个点的简单多边形 $(a_i,b_i)$。接下来可怜打算按照 $[-\pi,\pi)$ 上的均匀分布随机选取数字 $\alpha$（可以理解为等概率选取），并把这个简单多边形绕原点逆时针旋转 $\alpha$ 的角度（弧度制）。

现在可怜给你了每一个点的坐标，多边形的坐标，你的任务是帮助可怜计算在随机旋转后她期望可以消灭多少个敌人。

## 说明/提示

### 样例解释

如果你对概率与期望不怎么了解，这儿给出一些 Hint:

1. 设 $P_i$ 为旋转之后恰好能消灭 $i$ 个敌人的概率，那么期望就是 $\sum_{i=1}^n iP_i$.
2. 计算 $P_i$ 的一个方法是，在所有 $[-\pi,\pi)$ 范围内的旋转角度中，旋转后恰好消灭 $i$ 个敌人的角度构成了 $t_i$ 个区间 $(l_j,r_j)$（开闭不影响），那么 $P_i=\frac{\sum_{j=1}^{t_i}(r_j-l_j)}{2\pi}$.

在这题中：能消灭 $0$ 个敌人的区间是 $[\frac{\pi}{2},\pi),[-\pi,-\frac{\pi}{2}]$，能消灭 $1$ 个敌人的区间是 $(-\frac{\pi}{2},0),(0,\frac{\pi}{2})$。于是 $P_0 = P_1=\frac{1}{2}$。所以答案为 $\frac{1}{2}=0.50000$.

### 数据范围

对于 $30\%$ 的数据，$n,m \leq 15$。

对于另外 $30\%$ 的数据，选择的简单多边形是一个凸多边形。

对于 $100\%$ 的数据，$n \leq 200, m \leq 500, |x|,|y| \leq 10^6$.

## 样例 #1

### 输入

```
4 4
0 0
1 0
-1 -1
0 1
0 0
1 0
1 1
0 1
```

### 输出

```
0.50000
```

# 题解

## 作者：command_block (赞：12)

很好的一到计算几何题目啊,怎么没人做qwq?

此外是用我的写法,这题并**不**卡精度……

## 前置芝士

- 判断一个点是否在简单多边形内

这个题要求在多边形边上也**不算**,那么先一通判定该点是否在某条边上。

然后过这个点随意做一条射线,如果与多边形有奇数个交点则在多边形内,否则在外面。

(为了避免恰好在多边形顶点处相交的情况,最好随机射线方向,或者设一个比较刁钻的值)

- 求线段与圆的交点

先求出直线与圆的交点,在判断是否在线段上即可。

具体求法:判断直线到圆心$O$的距离,如果相切或者相离则舍去。

设两个交点是$A_1,A_2$。

过圆心做直线的垂线,算出交点$M$,半径$r$和$OM$,$A_1M$组成直角三角形,那么勾股一下得到$A_1M$和$A_2M$。

在之后,把向量$\overrightarrow{MO}$的方向向量分别左转和右转$90$度,然后缩放$A_1M$倍,加上$M$,即可得到两个交点。

![](https://cdn.luogu.com.cn/upload/pic/70778.png)

- 平分一段弧

利用垂径定理,作弦的垂线,求出垂线的方向向量,在缩放$r$倍即可恰好碰到圆周。

## 问题转化

这里每个点被覆盖到的概率是独立的,被根据期望的线性性,我们可以一个一个来算,最后再加起来。

那么问题就变成了:给出一个点和一个简单多边形,问在简单多边形随机旋转以后这个点有多少概率在多边形内。

与其让多边形转,不如让点转,那么问题又变成了:

给出一个点和一个简单多边形,问在点随机旋转以后这个点有多少概率在多边形内。

那么我们以原点为圆心,点到原点距离为半径,画一个圆,这就是那个点的运动轨迹。

这个圆弧在多边形内的长度除以2Pi就是答案。

## 解决方案

(假如这个点就是原点,那么形不成圆弧,直接判断该点是否在多边形内)

首先算出这个圆弧与多边形的所有交点。

如果没有交点,要么整个圆都在多边形外面,要么整个圆都在里面。

随意取圆上任意一点判断是否在多边形内即可。

如果有交点,就把这些交点极角排序,可以得到$O(m)$段弧,我们要一一判断这些弧在不在圆内。

如何判断?求出弧的重点,然后判断是否在多边形内即可这里的复杂度是$O(m)$。

那么这个题就做完了,总的复杂度$O(nm^2)$,有点松。

```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
#define eps 1e-7
#define MaxN 1050
using namespace std;
const double Pi=acos(-1);
int sign(double x)
{return x>eps ? 1 : (x<-eps ? -1 : 0);}
struct Point
{
  double x,y,rt;
  Point operator + (const Point &B) const
  {return (Point){x+B.x,y+B.y};}
  Point operator - (const Point &B) const
  {return (Point){x-B.x,y-B.y};}
  Point operator * (const double &B) const
  {return (Point){x*B,y*B};}
  Point operator / (const double &B) const
  {return (Point){x/B,y/B};}
  double operator ^ (const Point &B) const
  {return x*B.y-y*B.x;}
  bool operator == (const Point &B) const
  {return sign(x-B.x)==0&&sign(y-B.y)==0;}
}p[MaxN];
bool cmp(Point A,Point B)
{return sign(A.rt-B.rt)<0;}
double dis(Point A,Point B)
{return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}
struct Line
{
  Point a,b;
  double len(){return dis(a,b);}
}l[MaxN];
bool onl2(Point A,Line L)
{
  return sign((A-L.a)^(A-L.b))==0&&
         sign(A.x-min(L.a.x,L.b.x))>=0&&
         sign(A.y-min(L.a.y,L.b.y))>=0&&
         sign(A.x-max(L.a.x,L.b.x))<=0&&
         sign(A.y-max(L.a.y,L.b.y))<=0;
}
bool _onl2(Point A,Line L)
{
  return sign(A.x-min(L.a.x,L.b.x))>=0&&
         sign(A.y-min(L.a.y,L.b.y))>=0&&
         sign(A.x-max(L.a.x,L.b.x))<=0&&
         sign(A.y-max(L.a.y,L.b.y))<=0;
}
Point inter(Line L1,Line L2)
{
  double ls=(L1.b-L1.a)^(L2.a-L1.a),
         rs=(L1.b-L1.a)^(L2.b-L1.a);
  return L2.a+(L2.b-L2.a)*ls/(ls-rs);
}
double disl0(Point A,Line L)
{return fabs((L.a-A)^(L.b-A))/dis(L.a,L.b);}
int m;
//判断点是否在简单多边形内
bool in(Point A)
{
  for (int i=1;i<=m;i++)
    if (onl2(A,l[i]))return 0;
  Line L=(Line){A,(Point){A.x+0.2333,A.y+0.6666}};
  int cnt=0;
  for (int i=1;i<=m;i++){
    Point B=inter(L,l[i]);
    if (sign(B.y-A.y)>0&&_onl2(B,l[i]))cnt++;
  }return cnt&1;
}
double _r[MaxN];
int n;
void input()
{
  scanf("%d%d",&n,&m);
  double x,y;
  for (int i=1;i<=n;i++){
    scanf("%lf%lf",&x,&y);
    _r[i]=sqrt(x*x+y*y);
  }
  for (int i=1;i<=m;i++)
    scanf("%lf%lf",&l[i].a.x,&l[i].a.y);
  for (int i=1;i<m;i++)
    l[i].b=l[i+1].a;
  l[m].b=l[1].a;
}
double ans;
Point bas=(Point){0,0},t[MaxN];
//判断一段弧是否在圆内
void check(Point A,Point B,double r)
{
  Point C=(B-A)/dis(A,B);
  C=(Point){-C.y,C.x}*r;
  //注意逆时针序
  if (in(C)){
    if (A.rt>B.rt)ans+=Pi*2;
    ans+=B.rt-A.rt;
  }
}
void solve(double r)
{
  if (sign(r)==0){
    if (in(bas))ans+=Pi*2;
    return ;
  }int tot=0;
  for (int i=1;i<=m;i++){
    if (disl0(bas,l[i])-r>-1e-3)continue ;
    Point C=(l[i].a-l[i].b)/dis(l[i].a,l[i].b);
    //C: l的方向向量
    Line ML=(Line){bas,(Point){-C.y,C.x}};
    //ML: l的垂线
    Point M=inter(ML,l[i]);
    double rl=sqrt(r*r-M.x*M.x-M.y*M.y);
    //勾股(垂径)定理
    C=C*rl;
    Point P1=M+C,P2=M-C;
    //直线与圆交点计算完毕
    if (_onl2(P1,l[i]))t[++tot]=P1;
    if (_onl2(P2,l[i]))t[++tot]=P2;
  }
  //特判整个圆在多边形内/外的特殊情况
  if (tot==0){
    Point B=(Point){0,r};
    if (in(B))ans+=2*Pi;
    return ;
  }
  for (int i=1;i<=tot;i++)
    t[i].rt=atan2(t[i].x,t[i].y);
  sort(t+1,t+tot+1,cmp);
  //极角排序
  for (int i=1;i<=tot;i++)
    if (!(t[i]==t[i%tot+1]))
      check(t[i],t[i%tot+1],r);
}
int main()
{
  input();
  for (int i=1;i<=n;i++)solve(_r[i]);
  printf("%.5lf",fabs(ans/Pi/2));
  return 0;
}
```

---

## 作者：冥麟 (赞：3)

# P5467 [PKUSC2018]PKUSC

### [Link](https://www.luogu.com.cn/problem/P5467)

## 题意简述

> 平面上有 $ n $ 个点，一个 $ m $ 条边的简单多边形，不一定为正多边形。
>
> 现随机一个 $ \alpha \in [-\pi,\pi) $ ，将这个多边形绕原点逆时针旋转 $ \alpha $ 的角度，求被**严格**圈在多边形内的点的期望数量，也就是说，边界上的点不算。
>
> $ n \leq 200 , m \leq 500 $ .

## solution

容易想到：

+ 多边形绕原点旋转与其它点绕原点旋转没区别。
+ 根据期望的线性性，我们只需求出每个点被圈在多边形内的概率。

我们只需求出每个点的轨迹在多边形内部的圆弧对应的圆心角之和即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/mkqv2brn.png)

如何解决这个问题？

可以求出圆与多边形的所有交点，极角排序后求解。

这里给出另一种码量小、速度较快的方法。

对于一条边，我们考虑求出这个圆有多少角度在自己“内部”，分讨一波。

1. 被圆完全包含的边。这样的边没啥用，不做贡献。

2. 将圆完全“包含”的边。

   这种情况下所求即为线段两端点的极角差。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/dqjo61jb.png)

   顺带一提图中的 $ h $ 如何求： $ h = \dfrac{2S_{\Delta AOB}}{AB} = \dfrac{| \vec{OA} \times \vec{OB} |}{AB} $ .

3. 所在直线与圆相交的边。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/zdmarooh.png)

   我们要求的就是 $ \angle{AOC} + \angle{BOD} $ .

   注意到 $ \angle{AOC} = \angle{OCD} - \angle{OAB} = \arcsin\dfrac{h}{r} - \arccos\dfrac{\vec{AO} \cdot \vec{AB}}{AO \times AB} $ .

   这不就很舒服了～

还有一件事，我们给边按输入顺序定个向，起点极角小于终点极角的边的贡献为正，否则为负，这个画个图手模一下就很好理解。

最后再来特判一下与原点重合的点，需要判断其是否在多边形外或多边形的边界上。

边界不用多说，我们可以用射线法判断点是否在多边形内，具体地，从该点向 $ x $ 轴正方向引一条射线，如果它与多边形的交点个数为奇数，则可得该点在多边形内部。

只需要强制一条边纵坐标较大的端点严格在交点上方就可以应对一些刁钻的情况。

上代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
namespace code{
	#define R register
	const int maxn=500;const double e=1e-10,pi=acos(-1);
	inline int read(){
		int a=0,b=1;char s=getchar();
		while(s<48||s>57){if(s=='-'){b=-1;}s=getchar();}
		while(s>=48&&s<=57)a=(a<<1)+(a<<3)+s-48,s=getchar();
		return a*b;
	}
	int n,m;
	struct node{
		double x,y;
		double operator * (const node &a)const{return x*a.x+y*a.y;}
		double operator ^ (const node &a)const{return x*a.y-y*a.x;}
		double dis(){return sqrt(x*x+y*y);}
		node operator - (const node &a)const{return (node){x-a.x,y-a.y};}
	}a[maxn+5],b[maxn+5];
	inline void input(){
		n=read(),m=read();
		for(R int i=1;i<=n;i=-~i)a[i]=(node){1.0*read(),1.0*read()};
		for(R int i=1;i<=m;i=-~i)b[i]=(node){1.0*read(),1.0*read()};
		b[m+1]=b[1];
	}
	inline bool check(node a,node b){
		if(a.y-b.y<-e)swap(a,b);
		return a.y>e&&b.y<e&&(b^a)>e;
	}
	inline bool check(){
		for(R int i=1;i<=m;i=-~i)
			if((b[i]^b[i+1])<e&&(b[i]^b[i+1])>-e&&b[i]*b[i+1]<e)return false;//判断点是否在边界上
		int num=0;
		for(R int i=1;i<=m;i=-~i)num^=check(b[i],b[i+1]);//求与多边形的交点个数的奇偶性
		return num&1;
	}
	inline double calc(node a,node b,double r){
		if(max(a.dis(),b.dis())-r<-e)return 0;
		double h=fabs((a^b)/(a-b).dis()),alpha=acos(a*b/(a.dis()*b.dis()));//注意h要取abs,alpha为两端点的极角差
		double opt=(a^b)>e?1:-1;
		if(h-r>-e)return alpha*opt;
		double beta=asin(h/r),gamma=acos((a*(a-b))/(a.dis()*(a-b).dis()));
		double theta=acos((b*(b-a))/((b-a).dis()*b.dis()));
		return opt*min(alpha,((beta-gamma>e?beta-gamma:0)+(beta-theta>e?beta-theta:0)));
	}
	inline void solve(){
		double ans=0;
		for(R int i=1;i<=n;i=-~i)if(a[i].dis()<e)ans+=check()*2.0*pi;
		for(R int i=1;i<=m;i=-~i)
			if((b[i]-b[i+1]).dis()>e&&((b[i]^b[i+1])<-e||(b[i]^b[i+1])>e)){
				for(R int j=1;j<=n;j=-~j)
					if(a[j].dis()>e)ans+=calc(b[i],b[i+1],a[j].dis());
			}
		ans/=2.0*pi;printf("%.5lf\n",ans);
	}
	inline void main(){input(),solve();}
}
int main(){return code::main(),0;}
```



---

## 作者：Betrayer_of_love (赞：1)

### 题解：

---

考虑求每个点的贡献

等价于一个以 $OA$ 长为半径的圆心为原点的圆在多边形内的弧对应的角度 $/ 2π$ 。
 
求弧度可以利用三角剖分。

在原点的点要特判，采用射线法就可以了。


## code:

---


```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define db double
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
const db eps=1e-6,Pi=acos(-1.);
const int N=1005;
int sign(db x){return ((x>eps)-(x<-eps));}
struct P{
    db x,y;
    P(db x=0,db y=0):x(x),y(y){}
    P operator+(P o){
		return P(x+o.x,y+o.y);
		}
    P operator-(P o){
		return P(x-o.x,y-o.y);
	}
    P operator *(db o){
		return P(x*o,y*o);
	}
    P rev(){
		return P(-x,-y);
	}
    db operator *(P o){
		return x*o.x+y*o.y;
		}
    db operator ^(P o){
		return x*o.y-y*o.x;}
    db mo(){return sqrt(x*x+y*y);
	}
    db thi(P o){
		return acos(((*this)*o)/(mo()*o.mo()));
		}
}s[N],p[N];
db calc(P a,P b,db R){
    db ras=0;
    db f=sign(a^b);
    if(sign(max(a.mo(),b.mo())-R)==-1) return 0;
    db thi=a.thi(b);
    db h=fabs((a^b)/(a-b).mo());
    if(sign(h-R)>-1) return thi*f;
    db a0=asin(h/R),a1=a.rev().thi(b-a),a2=b.rev().thi(a-b);
    if(sign(a0-a1)==1) ras+=a0-a1;
    if(sign(a0-a2)==1) ras+=a0-a2;
    return min(ras,thi)*f;
}
int chk(P x,P y){
    if(!sign(x.y)) return sign(x.x)==1;
    if(!sign(y.y)) return 0;
    if(x.y>y.y) swap(x,y);
    if(sign(x.y*y.y)==1) return 0;
    P xxx=x+(y-x)*(x.y/(y.y-x.y));
    return sign(xxx.x)==1;
}
int main(){
    reg int i,j,n,m;
    db ans=0;
    n=read(),m=read();
    for(i=1;i<=n;++i) p[i].x=read(),p[i].y=read();
    for(i=1;i<=m;++i) s[i].x=read(),s[i].y=read();
    s[m+1]=s[1];
    for(i=1;i<=m;++i){
        if(!sign(s[i]^s[i+1])) continue;
        for(j=1;j<=n;++j){
            if(!sign(p[j].mo())) continue;
            ans+=calc(s[i],s[i+1],p[j].mo());
        }
    }
    for(i=1;i<=n;++i){
        if(sign(p[i].mo())) continue;
        int flag=1,cnt=0;
        for(j=1;j<=m;++j){
            if(sign(s[j]^s[j+1])) cnt+=chk(s[j],s[j+1]);
            else if(sign(s[j]*s[j+1])<1){flag=0;break;}
        }
        if(flag&&cnt%2==1) ans+=Pi*2.;
    }
    ans/=(Pi*2.);
    return 0*printf("%.5lf\n",ans);
}
```

**完结撒花，谢谢观看！！！**

---

