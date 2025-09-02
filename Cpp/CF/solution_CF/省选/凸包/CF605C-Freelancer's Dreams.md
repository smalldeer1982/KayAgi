# Freelancer's Dreams

## 题目描述

Mikhail the Freelancer dreams of two things: to become a cool programmer and to buy a flat in Moscow. To become a cool programmer, he needs at least $ p $ experience points, and a desired flat in Moscow costs $ q $ dollars. Mikhail is determined to follow his dreams and registered at a freelance site.

He has suggestions to work on $ n $ distinct projects. Mikhail has already evaluated that the participation in the $ i $ -th project will increase his experience by $ a_{i} $ per day and bring $ b_{i} $ dollars per day. As freelance work implies flexible working hours, Mikhail is free to stop working on one project at any time and start working on another project. Doing so, he receives the respective share of experience and money. Mikhail is only trying to become a cool programmer, so he is able to work only on one project at any moment of time.

Find the real value, equal to the minimum number of days Mikhail needs to make his dream come true.

For example, suppose Mikhail is suggested to work on three projects and $ a_{1}=6 $ , $ b_{1}=2 $ , $ a_{2}=1 $ , $ b_{2}=3 $ , $ a_{3}=2 $ , $ b_{3}=6 $ . Also, $ p=20 $ and $ q=20 $ . In order to achieve his aims Mikhail has to work for $ 2.5 $ days on both first and third projects. Indeed, $ a_{1}·2.5+a_{2}·0+a_{3}·2.5=6·2.5+1·0+2·2.5=20 $ and $ b_{1}·2.5+b_{2}·0+b_{3}·2.5=2·2.5+3·0+6·2.5=20 $ .

## 说明/提示

First sample corresponds to the example in the problem statement.

## 样例 #1

### 输入

```
3 20 20
6 2
1 3
2 6
```

### 输出

```
5.000000000000000
```

## 样例 #2

### 输入

```
4 1 1
2 3
3 2
2 3
3 2
```

### 输出

```
0.400000000000000
```

# 题解

## 作者：hsfzLZH1 (赞：4)

## 题目大意

有 $n$ 份工作，完成 $1$ 个单位时间的第 $i$ 项工作会获得 $a_i$ 和 $b_i$ 两项属性值。 **工作的时间数可以不是整数** 。你需要在尽量短的时间内使 $\sum a\ge p,\sum b\ge q$ 。

$1\le n \le 10^5,1\le a_i,b_i,p,q\le 10^6$

为了防止精度问题，若你的答案为 $a$ ，而标程给出的答案为 $b$ ，你的答案会被认为是正确的当且仅当 $\frac {|a-b|} {\max\{1,b\}} \le 10^{-6}$ 。

## 解题思路

性质：最优策略中，选择的本质不同的工作数最多为 $2$ 种。

证明：

假设我们找到了一种策略，是选择编号为 $x$ 和 $y$ 的两项工作，假设我们考虑一个新的工作 $z$ 加入后是否更优。

我们将一种工作转化为一个结点，其坐标为 $(a_i,b_i)$ ，则我们的最优策略是已经选择了结点 $x$ 和 $y$ ，现加入一个结点 $z$ ，观察其是否会更优。

只选择结点 $x$ 和结点 $y$ 的贡献的方式是将结点 $x$ 和结点 $y$ 之间连接一条边，并找到这条线段上的一个结点 $(m,n)$ ，其满足 $\frac m p=\frac n q$ ，则 $\frac p m$ 即为最优时间。

如果我们要加入一个结点 $z$ ，若 $z$ 在线段 $xy$ 的上方，则折线 $xzy$ 会更优，否则仍保留 $xy$ 最优。在前面的情况中，也是把一条折线拆成若干条线段，所以在最优策略中，选择的本质不同的工作数最多 $2$ 种。

得证。

如果我们用 $O(n^2)$ 枚举所有点对，显然无法接受。

观察到之前我们找最优策略的过程实质上是求凸包的过程，我们向点集中添加点 $(0,0),(maxa,0),(0,maxb)$ ，求出凸包即可。其中 $maxa=\max\{a_i\},maxb=\max\{b_i\}$ 。

求出凸包后，我们扫描凸包上的每一条边，如果凸包边上的一条线段与直线 $(0,0)+k(p,q)$ 有交点，那么这个点即是工作时间为 $1$ 时的最优点。设这个点的坐标为 $(m,n)$ ，则 $\frac p m$ 即为所求答案。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
const int maxn=100010;
int n,st[maxn],tot;
double p,q,maxa,maxb,ans;
struct Vector
{
    double a,b,polar_angle;
    bool operator<(Vector x){return polar_angle<x.polar_angle;}
    Vector operator+(Vector x){return{a+x.a,b+x.b,0.0};}
    Vector operator-(Vector x){return{a-x.a,b-x.b,0.0};}
    Vector operator*(double x){return{a*x,b*x,0.0};}
}s[maxn],intersection;
double cross(Vector x,Vector y){return x.a*y.b-x.b*y.a;}
int main()
{
    scanf("%d%lf%lf",&n,&p,&q);
    for(int i=1;i<=n;i++)scanf("%lf%lf",&s[i].a,&s[i].b),maxa=max(maxa,s[i].a),maxb=max(maxb,s[i].b);
    s[++n]={0,maxb,0.0};s[++n]={maxa,0,0.0};s[++n]={0,0,0.0};
    swap(s[1],s[n]);
    for(int i=2;i<=n;i++)s[i].polar_angle=atan2(s[i].b,s[i].a);
    sort(s+2,s+n+1);
    for(int i=1;i<=n;i++)
    {
        while(tot>=2&&cross(s[st[tot]]-s[st[tot-1]],s[i]-s[st[tot]])<=0)tot--;
        st[++tot]=i;
    }
    //(s[st[tot]])+k(s[st[tot+1]]-s[st[tot]])
    //(0,0)+k(p,q)
    for(int i=2;i<tot;i++)
    {
        if(cross(s[st[i+1]]-s[st[i]],{p,q})==0.0)continue;
        double t=cross({p,q},s[st[i]])/cross(s[st[i+1]]-s[st[i]],{p,q});
        intersection=s[st[i]]+(s[st[i+1]]-s[st[i]])*t;
        if(intersection.a>=min(s[st[i]].a,s[st[i+1]].a)&&intersection.a<=max(s[st[i]].a,s[st[i+1]].a))ans=p/intersection.a;
    }
    printf("%.15lf\n",ans); 
    return 0;
} 
```

---

## 作者：wishapig (赞：4)

很明显这是一个线性规划，考虑它的对偶：

原始问题：
$$
\min:\sum_{j=1}^nx_j
$$

$$
\begin{aligned}
\operatorname{s.t.}\ 
&\sum_{j=1}^na_jx_j\ge p\\
&\sum_{j=1}^nb_jx_j\ge q\\
&x_j\ge 0\ \ (1\le j\le n)
\end{aligned}
$$

其对偶：
$$
\max:py_1+qy_2
$$

$$
\begin{aligned}
\operatorname{s.t.}\ 
&a_jy_1+b_jy_2\le1\ \ (1\le j\le n)\\
&y_i\ge 0\ \ (i=1,2)
\end{aligned}
$$

在确定 $y_1$ 之后，很明显 $y_2$ 一定会取 $\min_j\left\{\dfrac{1-a_jy_1}{b_j}\right\}$，在此情况下，$f(y_1)=py_1+qy_2$ 是上凸的，因此可以三分求出最大值。

具体来说，$y_1$ 的范围有两个限制，即 $y_1,y_2$ 均要非负，那么解出 $0\le y_1\le \min_j\left\{\dfrac{1}{a_j}\right\}$。

三分的时候，二分一个 `mid`，比较 $f(mid)$ 与 $f(mid+\epsilon)$ 的大小关系，若前者大则 `r=mid`，否则 `l=mid`。

这里 $\epsilon$ 可以取 $10^{-12}$ 左右。

```c++
#include<bits/stdc++.h>
using namespace std;
long double p,q,l,r=1e9,a[100005],b[100005]; int n;
char buf[1<<22],*S=buf;
#define gc() (*S++)
int read(){       
	char ch=gc(); int num=0;
	while (!isdigit(ch)) ch=gc();
	while (isdigit(ch)) num=num*10+ch-'0',ch=gc();
	return num;
}
inline long double query(long double x){
	long double y=1e9;
	for (int i=1; i<=n; i++) y=min(y,(1-a[i]*x)/b[i]);
	return x*p+y*q;
}
int main(){
	fread(buf,1,1<<22,stdin);
	n=read(),p=read(),q=read();
	for (int i=1; i<=n; i++) a[i]=read(),b[i]=read(),r=min(r,1.0/a[i]);
	for (int i=1; i<=50; i++){
		long double mid=(l+r)/2;
		if (query(mid)<query(mid+(1e-12))) l=mid;
		else r=mid;
	}
	printf("%.15lf\n",(double)query(l));
}
```



---

## 作者：TOBapNw (赞：1)

怎么全是高级的计算几何啊？

首先，最多选 2 个工作。

反证，假设现在选取了若干工作，一定可以找到一组工作 $x,y$，使得它们可以通过按比例分配时间超过任意其它工作，然后把其它工作删去后只剩 2 个了。

对时间二分答案（显然一段可行一段不可行）。

现在二分答案了 $T$，那么对于合法的一组 $x,y$，假设在 $x$ 的时间为 $t$，需要满足：

$$
\begin{cases}
a_x t + a_y (T-t)\ge p\\
b_x t + b_y (T-t)\ge q
\end{cases}
$$

为了避免分类讨论，钦定 $Ta_x\ge p,Ta_y< p$，$Tb_y\ge q,Tb_x< q$。

意思是“只用 $x$ 能满足 $a$ 达到 $p$，但不能满足 $b$ 达到 $q$，而只用 $y$ 与只用 $x$ 相反”。

而除此之外只需特判使用一个就能成功的特殊情况。

把上述不等式以 $t$ 为变量解得：

$$
\frac{p-a_yT}{a_x-a_y}\le t\le \frac{q-b_y T}{b_x-b_y}
$$

为了让 $t$ 有解，要满足：

$$
\begin{cases}
\displaystyle\frac{p-a_yT}{a_x-a_y}\le  \frac{q-b_y T}{b_x-b_y} \\
\displaystyle 0\le  \frac{q-b_y T}{b_x-b_y} \le T
\end{cases}
$$

上式解得：$a_yb_xT-a_yq-b_xp\le a_x b_y T-a_x q-b_y p$。

简单配方可得：$\displaystyle\frac{Ta_y-p}{Tb_y-q}\ge\frac{Ta_x-p}{Tb_x-q}$。

而下式解得的已经被钦定了。

于是只要对 $\{i|Ta_i< p,i\in[1,n]\}$ 求出 $\frac{Ta_i-p}{Tb_i-q}$ 的最大值，并对剩余 $i$ 判断即可。

```cpp
#include<bits/stdc++.h>
#define For(i_,l_,r_)for(int i_=(l_),g_=(r_);i_<=g_;i_++)
#define Rep(i_,l_,r_)for(int i_=(l_),g_=(r_);i_>=g_;i_--)
using namespace std;
#define db double
int n,p,q;
struct N{
    int a,b;
    inline bool operator<(const N&U)const{
        return a<U.a;
    }
}a[300005];
const db eps=1e-8;
inline bool check(const db T){
    int u=n+1;db mx=-1e12;
    For(i,1,n){
        if(a[i].a*T>=p){u=i;break;}
        if(a[i].b*T>=q){
            mx=max(mx,(a[i].a*T-p)/(a[i].b*T-q));
        }
    }
    For(i,u,n){
        if(a[i].b*T>=q)return 1;
        if((a[i].a*T-p)/(a[i].b*T-q)<mx+eps)return 1;
    }
    return 0;
}
signed main(){
    cin>>n>>p>>q;
    For(i,1,n)cin>>a[i].a>>a[i].b;
    sort(a+1,a+1+n);
    db l=0.0,r=1e6;
    while(r-l>eps){
        const db mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid;
    }
    printf("%.7lf\n",r);
    return 0;
}
```

---

## 作者：yzx72424 (赞：1)

思路参考 2018_08_03  dwjshift老师基础省选讲课

凸包+向量。

题意：有n份工作，第i份工作做1个单位时间获得ai经验和bi钱，现在要凑齐p点经验和q钱，至少要工作多久，工作的时间可以为小数

相当于有向量i Σi,1-n  (ai,bi)，平均每单位时间的收益就是这 些向量的线性组合。把这n个向量画出来，再添上(0,y(max))和(x(max),0)、(0,0)三个点,求出凸包后，连接原点和(p,q)求出与凸包的交点即可

程序比较丑，勿喷.

```
#include <bits/stdc++.h>
using namespace std;
int a[100010], b[100010];
int n, p, q;
double f(double x){
    double y = 1;
    for(int i=0;i<n;i++)y=min(y,((double)1- x*b[i])/a[i]);
    return y*p + x*q;
}

int main() {
    scanf("%d%d%d",&n,&p,&q);
    int maxx=0;
    for(int i=0;i<n;i++){scanf("%d%d",&a[i],&b[i]);maxx=max(maxx,b[i]);}
    double l=0,r=(double)1/maxx;
    int t=10000;
	while(t--){
        double l2=(2*l+r)/3,r2=(2*r+l)/3;
        if(f(l2)<=f(r2)){l=l2;continue;}r=r2;
    }
    printf("%.10f\n",f((l+r)*0.5));
    return 0;
}
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
又是要求精度较高，那么显然对于一般的算法可以不考虑了。本题的主要思路为凸包。
## 分析。
我们可以看到，对于每一个单位时间的工作，我们都可以看做是一个向量。那么我们设一个单位的工作内容为一个向量，并将其命名为 $\left(a,b\right)$。那么我们接下来考虑这个向量的所处范围即可。显然题目中有约束条件 $q$ 和 $p$ 所以我们考虑满足这个的区间。那么这个工作的向量可以满足条件的区域就是 $\{\left(p,q\right)\mid p\leq a,q\leq b\}$ 的地方。显然我们考虑建造一个平面直角坐标系，并将这个区域投影到这个坐标系中。那么在这个平面直角坐标系中，这就是一个边平行于坐标轴的矩形。

考虑从单位时间上入手。构造两个向量 $\left(a_1,b_1\right)$ 和 $\left(a_2,b_2\right)$ 可以通过线性组合构造出的向量的区域。有一个显然且必要的公式是：
$$\theta\times\left(a_1,b_i\right)+\left(1-\theta\right)\times\left(a_2,b_2\right)$$
这个公式是求两点间线段的一个方程。这个公式的成立代表着这条两点之间的线段，是所构造出的向量区域的边界，因此两个向量加上这条向量的边界所构成的三角形就是答案。

那么我们就可以拓展到多个向量的情况。那么我们惊奇地发现，如果我们将每一个点和向量建出来，将会出现答案区域就是原点加上这些向量点所构成的凸包。这一点不了解的可以从几何画板上画一下。如图是一个不是很标准的例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/yuyjho1d.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

能构造出的向量的区域是这个凸包，又因为向量能满足的条件的区域是一个矩形，因此我们分别求出 $x$ 和 $y$ 坐标上的向量的点坐标的最大值，加上构造的这两个最大值分别于 $y$ 轴与 $x$ 轴交点的两个点构造凸包，此时便是我们便构造出了一个单位时间内的满足条件的区域了。这个在 $t\leq1$ 的情况下构造的凸包我们就称呼为单位凸包吧。

那么我们现在就可以直接考虑所有情况了。如果我们考虑整个比单位时间大的区域，那么就相当于将这个上面单位的凸包进行扩大或缩小。显然这个相似比就是面前我们考虑的时间。那么我们找到最短的时间的问题就转变成了另一个问题：求一个最短时间使得凸包正好包含点 $\left(p,q\right)$。那么有一个很经典的做法就是将这个扩大或缩小的凸包和这个单位凸包近似地看做关于原点位似，直接连接原点和 $\left(p,q\right)$。那么一定存在一个点与单位凸包相交，所以根据相似的基本定理和位似的基本性质，答案就是原点到 $\left(p,q\right)$ 的距离比上，原点到上面那个交点的距离。这个就可以套上连线然后求交点的模板题了。

时间复杂度为 $O\left(n\log n\right)$。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
const double eps=1e-7;
int n;
int sum,st[100005];
double P,Q;
double maxx,maxy,ans;
struct node{
	double x,y;
}point[100005];
double operator * (node a,node b){
    return a.x*b.y-b.x*a.y;
}
node operator + (node a,node b){
    node kkk={a.x+b.x,a.y+b.y};
	return kkk;
}
node operator - (node a,node b){
    node kkk={a.x-b.x,a.y-b.y};
	return kkk;
}
node operator * (node a,double b){
	node kkk={a.x*b,a.y*b};
	return kkk;
}
double dis(node a,node b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool cmp(node a,node b){
	if(abs((a-point[1])*(b-point[1]))<eps){
		return dis(point[1],a)<dis(point[1],b);
	}
	return (a-point[1])*(b-point[1])>0;
}
node add(node a,node b,node c,node d){
	node xx=a-c;
	double yy=(d*xx)/(b*d);
	return a+(b*yy);
}
int main(){
	cin>>n>>P>>Q;
	node co={P,Q};
	for(int i=1;i<=n;i++){
		cin>>point[i].x>>point[i].y;
		maxx=max(maxx,point[i].x);
		maxy=max(maxy,point[i].y);
	}
	point[++n].x=0.0;
	point[n].y=0.0;
	swap(point[1],point[n]);
	point[++n].x=0.0;
	point[n].y=maxy;
	point[++n].x=maxx;
	point[n].y=0.0;
	sort(point+2,point+n+1,cmp);
	for(int i=1;i<=n;i++){
		while(sum>1&&(point[st[sum]]-point[st[sum-1]])*(point[i]-point[st[sum]])<eps){
			sum--;
		}
		st[++sum]=i;
	}
	for(int i=2;i<sum;i++){
		node give=add(point[1],co,point[st[i]],point[st[i+1]]-point[st[i]]);
		double xa=point[st[i]].x;
		double ya=point[st[i]].y;
		double xb=point[st[i+1]].x;
		double yb=point[st[i+1]].y;
		if(xa>xb){
		    swap(xa,xb);
		}
		if(ya>yb){
		    swap(ya,yb);
		}
		if(give.x>=xa-eps&&give.x<=xb+eps&&give.y>=ya-eps&&give.y<=yb+eps){
			ans=sqrt(dis(point[1],co)/dis(point[1],give));
			break;
		}
	}
	printf("%.15lf\n",ans);
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

