# Martian Food

## 题目描述

Have you ever tasted Martian food? Well, you should.

Their signature dish is served on a completely black plate with the radius of $ R $ , flat as a pancake.

First, they put a perfectly circular portion of the Golden Honduras on the plate. It has the radius of $ r $ and is located as close to the edge of the plate as possible staying entirely within the plate. I. e. Golden Honduras touches the edge of the plate from the inside. It is believed that the proximity of the portion of the Golden Honduras to the edge of a plate demonstrates the neatness and exactness of the Martians.

Then a perfectly round portion of Pink Guadeloupe is put on the plate. The Guadeloupe should not overlap with Honduras, should not go beyond the border of the plate, but should have the maximum radius. I. e. Pink Guadeloupe should touch the edge of the plate from the inside, and touch Golden Honduras from the outside. For it is the size of the Rose Guadeloupe that shows the generosity and the hospitality of the Martians.

Further, the first portion (of the same perfectly round shape) of Green Bull Terrier is put on the plate. It should come in contact with Honduras and Guadeloupe, should not go beyond the border of the plate and should have maximum radius.

Each of the following portions of the Green Bull Terrier must necessarily touch the Golden Honduras, the previous portion of the Green Bull Terrier and touch the edge of a plate, but should not go beyond the border.

To determine whether a stranger is worthy to touch the food, the Martians ask him to find the radius of the $ k $ -th portion of the Green Bull Terrier knowing the radii of a plate and a portion of the Golden Honduras. And are you worthy?

## 说明/提示

Dish from the first sample looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77E/3593da8a1385175df516219890d97f20e9f5c386.png)

Dish from the second sample looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF77E/aa3970cc488f83125f30b27363dce7ac36c7ecda.png)

## 样例 #1

### 输入

```
2
4 3 1
4 2 2
```

### 输出

```
0.9230769231
0.6666666667
```

# 题解

## 作者：bztMinamoto (赞：4)

## 题面

[传送门](http://codeforces.com/contest/77/problem/E)

这题有两种方法~~（然而两种我都想不到）~~

## 方法一

## 前置芝士

### 笛卡尔定理

我们定义一个圆的曲率为$k=\pm {1\over r}$，其中$r$是圆的半径

若在平面上有两两相切，且六个切点互不相同的四个圆，设其曲率分别为$k1,k2,k3,k4$（若该圆和其它所有圆都外切，则其曲率取正，否则曲率取负），则有

$$(k1+k2+k3+k4)^2=2(k1^2+k2^2+k3^2+k4^2)$$

类似的，若是空间中有两两相切且切点互不相同的五个球体，则有

$$(k1+k2+k3+k4+k5)^2=3(k1^2+k2^2+k3^2+k4^2+k5^2)$$

## 题解

首先那个粉色圆的直径就是$R-r$，于是我们现在知道前三个圆的半径了

上面的柿子可以看做一个关于$k4$的方程，化简一下可得

$$k4^2-2(k1+k2+k3)k4+2(k1^2+k2^2+k3^2)-(k1+k2+k3)^2=0$$

这方程一看就很不好解的样子……

想想我们初中时候学过的韦达定理，对于方程$ax^2+bx+c=0$，设它的两个解为$x_1,x_2$，则有

$$x_1+x_2=-{b\over a}$$

设$k3$代表绿圆$i$的曲率，$k2$代表黄圆的曲率，$k1$代表最大的圆的曲率，我们要求的就是与这三个圆都相切的圆的曲率……

但是这里是两个解的和的形式怎么办丫……

冷静想想，和这三个圆都相切的圆，除了绿圆$i+1$，似乎只剩下绿圆$i-1$？而$i-1$的曲率我们之前已经知道了？

那么我们就可以$O(n)$递推了，时间复杂度$O(nT)$

```cpp
//minamoto
#include<bits/stdc++.h>
#define R register
#define inline __inline__ __attribute__((always_inline))
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
int read(){
    R int res;R char ch;
    while((ch=getc())>'9'||ch<'0');
    for(res=ch-'0';(ch=getc())>='0'&&ch<='9';res=res*10+ch-'0');
    return res;
}
int n,R1,R2,R3;double r1,r2,r3,r4,r5;
int main(){
//	freopen("testdata.in","r",stdin);
	for(int T=read();T;--T){
		R1=read(),R2=read(),n=read(),R3=R1-R2;
		r1=-1.0/R1,r2=1.0/R2,r3=1.0/R3,r4=r1+r2+r3;
		fp(i,2,n)r5=r3,r3=r4,r4=(r1+r2+r3)*2-r5;
		printf("%.10lf\n",1.0/r4);
	}
	return 0;
}
```

## 方法二

## 前置芝士

### 圆的反演

![](https://i.loli.net/2019/04/14/5cb29185ec115.png)

## 题解

我们设黄圆为$A$，绿圆为$B$，大圆就叫大圆，并且以下假设$A$和大圆的交点为原点，这三个圆共同的直径为$x$轴

如果我们以原点为反演中心，那么反演之后$A$和大圆会变成两条直线。又因为反演不改变相切关系，所以$B$反演之后就在这两条直线中间。显然$B$反演之后的圆心仍在$x$轴上

如果我们还要放上别的圆（假设一直往上放），由于它与这三个圆有唯一交点，所以肯定是被卡在两条直线中间，且刚好在之前的圆上方

因为这些圆的半径相同，我们可以$O(1)$得到第$n$个圆的圆心的坐标。之后我们连接圆心和原点，这条直线和圆的两个交点分别记为$p1,p2$，把它们反演回来，对应的两个点之间的距离就是原来的第$n$个圆的半径了

```cpp
//minamoto
#include<bits/stdc++.h>
#define R register
#define inline __inline__ __attribute__((always_inline))
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
int read(){
    R int res,f=1;R char ch;
    while((ch=getc())>'9'||ch<'0')(ch=='-')&&(f=-1);
    for(res=ch-'0';(ch=getc())>='0'&&ch<='9';res=res*10+ch-'0');
    return res*f;
}
struct node{
	double x,y;
	inline node(){}
	inline node(R double xx,R double yy):x(xx),y(yy){}
	inline node operator +(const node &b)const{return node(x+b.x,y+b.y);}
	inline node operator -(const node &b)const{return node(x-b.x,y-b.y);}
	inline node operator *(const double &b)const{return node(x*b,y*b);}
	inline double norm(){return sqrt(x*x+y*y);}
}p,pp,o;
int n,r1,r2;double r,lx,rx,ir;
void get(R node o,R double k,R double b){
	double del=ir/sqrt(k*k+1);
	p=node(o.x-del,k*(o.x-del)+b),
	pp=node(o.x+del,k*(o.x+del)+b);
}
inline node inv(R node p){
	double len=1.0/p.norm();
	return p*(r*r*len*len);
}
int main(){
//	freopen("testdata.in","r",stdin);
	for(int T=read();T;--T){
		r1=read(),r2=read(),n=read(),r=r2*0.5;
		lx=r*r/(r1*2),rx=r*r/(r2*2),ir=(rx-lx)*0.5;
		o=node((lx+rx)*0.5,2*n*ir);
		get(o,o.y/o.x,0);
		printf("%.10lf\n",(inv(p)-inv(pp)).norm()*0.5);
	}
	return 0;
}
```

---

## 作者：李至擎 (赞：0)

补充一些前面的题解写的不太清楚的地方。

根据笛卡尔定理，若平面上四个半径为 $r_1,r_2,r_3,r_4$ 的圆两两相切于不同点，则：

- 若四圆两两外切，则 $(\sum\limits_{i=1}^4\dfrac{1}{r_i})^2=2\sum\limits_{i-1}^4\dfrac{1}{r_i^2}$；

- 半径为 $r_1,r_2,r_3$ 的圆内切于半径为 $r_4$ 的圆中，则 $(\dfrac{1}{r_1}+\dfrac{1}{r_2}+\dfrac{1}{r_3}-\dfrac{1}{r_4})^2=2\sum\limits_{i-1}^4\dfrac{1}{r_i^2}$；

因为题目中说了初始时的小圆切于大圆和圆盘，**且半径尽可能大**，所以小圆的半径就是 $R-r$。考虑记 $r_1=-\dfrac{1}{R}$，$r_2=\dfrac{1}{r}$，$r_3=\dfrac{1}{R-r}$。设后面加的第 $i$ 个圆的半径为 $x$，则 $r_{i+3}=\dfrac{1}{x}$，那么 $\dfrac{1}{r_{n+3}}$ 即为所求。

如果把小圆看成第 0 个圆，求 $r_i$ 可以考虑对圆盘、大圆、第 $i-4$ 个圆和第 $i-3$ 个圆应用笛卡尔定理，即 $(r_1+r_2+r_{i-1}+r_i)^2=2(r_1^2+r_2^2+r_{i-1}^2+r_i^2)$，化简即为 $r_i^2-2(r_1+r_2+r_{i-1})r_i+(2(r_1^2+r_2^2+r_{i-1}^2)-(r_1+r_2+r_{i-1})^2)=0$。

由韦达定理可知这个方程的两个解 $x_1,x_2$ 满足 $x_1+x_2=2(r_1+r_2+r_{i-1})$。注意到第 $i-5$ 个圆也和另外三个圆相切，所以 $r_{i-2}$ 也是这个方程的一个解，那么这个方程的另外一个解 $r_i=2(r_1+r_2+r_{i-1})-r_{i-2}$。

最后一个问题是 $r_4$ 怎么求。注意到如果将第一个圆沿着大圆和小圆的圆心的连线对称过去得到的圆也是这个方程的一个解，所以 $r_4=\dfrac{2(r_1+r_2+r_3)}{2}=r_1+r_2+r_3$。

递推即可，时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void()
#endif
using namespace std;
const int inf=1e18;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
double a[10015];
void solve(){
	int R=read(),r=read(),n=read();
	a[1]=-1.0/R,a[2]=1.0/r,a[3]=1.0/(R-r),a[4]=a[1]+a[2]+a[3];
	for(int i=5;i<=n+3;i++)a[i]=2*(a[1]+a[2]+a[i-1])-a[i-2];
	printf("%.8lf\n",1/a[n+3]);
}
signed main(){
	int T=read();
	while(T--){
		solve();
	} 
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 前置知识

笛卡尔定理与初中代数

## 分析

首先刚看到题的时候很明显就会往几何的方向去想，但能不能想到这个非常偏的定理是个问题。这个定理一看就可以成为这道题的背景，想到这个定理这道题就完成了一半。

笛卡尔定理：

> 若平面上四个半径为r1、r2、r3、r4的圆两两相切于不同点，则其半径满足以下结论
$$(\sum\limits_{i=1}^{4}\dfrac{1}{r_i})^2 = 2 \sum\limits_{i=1}^{4}\dfrac{1}{r_i^2}$$
> 其中，如果外切半径取正，内切半径取负

接下来，因为第一个圆得同时与 $G$ 和 $P$ 相切，所以第一个圆的圆心必须在 $G$ 和 $P$ 的圆心连线上，所以半径就是 $R - r$。

所以我们就得到了前三个圆的半径，就可以开始应用笛卡尔定理了。

假设第 $i$ 个圆的半径为 $1 / r_{i+2}$（这么写是为了让 $G$ 与 $P$ 不必单独拿出来分类讨论），$r_1 = 1 / R$，$r_2 = 1 / r$，那么有：

$$(-r_1 + r_{k-2} + r_2 + r_k) ^ 2 = 2(r_{2}^2 + r_{k-2}^2 + r_{1}^2 + r_k^2)$$

然后就开始化简了：

$$r_k^2 - 2(r_{1} + r_{k - 2} + r_{2})r_k + 2(r_{1}^2 + r_{k - 2}^2 + r_{2}^2) - (r_{1} + r_{k - 2} + r_{2})^2 = 0$$

爆算求 $\Delta$：

$$\begin{aligned}\Delta &= 4(r_{1} + r_{k - 2} + r_{2}) ^ 2 + 4(r_{1} + r_{k - 2} + r_{2})^2 - 8(r_{1}^2 + r_{k - 2}^2 + r_{2}^2)\\
&=16(r_{1}r_{k - 2} + r_{k - 2}r_{2} + r_{1}r_{2})\end{aligned}$$

解得两个解的形式就是 $\dfrac{2(r_{1}+r_{k-2}+r_{2}) \pm \sqrt{16(r_{1}r_{k - 2} + r_{k - 2}r_{2} + r_{1}r_{2})}}{2}$

看起来非常的阴间。所以不能爆算


发现两个解之和就是 $2(r_{1}+r_{k-2}+r_{2})$。

接下来是非常巧的一步：因为两个解和知道了，而已经有一个解（$r_{k - 2}$）知道了，所以另外一个解也可以知道！

所以，$r_k = 2(r_{1}+r_{k-2}+r_{2}) - r_{k-2}$

最后递推 $n - 1$ 次即可。

## 代码

```cpp
#include <bits/stdc++.h> 
#define lld long long 
using namespace std;
int n;
int R, r;
double r1, r2, r3;
int T;
int main() {
	scanf("%d", &T);
	for (; T --; ) {
		scanf("%d%d%d", &R, &r, &n);
		r1 = 1.0 / (R - r);
		r2 = -1.0 / R + 1.0 / r + 1.0 / (R - r);
		for (int i = 2; i <= n; ++ i)
			r3 = r1, r1 = r2, r2 = (-1.0 / R + 1.0 / r + r1) * 2 - r3;
		printf("%lf\n", 1.0 / r2);
	}
	return 0;
}

```

---

