# [BalticOI 2016] Spiral (day1)

## 题目描述

[BalticOI 2016 Day1]螺旋


一个矩阵的大小为 $(2n+1)\times (2n+1)$，我们们通过下述方法填数：数字 $1$ 在中心，数字 $2$ 在其右，其他数字依次按照逆时针螺旋摆放。

你的任务是对于 $q$ 个询问，计算出一个给定子矩阵所有数字的和对 $(10^9+7)$ 取余的结果。比如以下 $n=2$ 的矩阵，灰色区域的数字之和为 $74$：

![](https://i.loli.net/2018/08/11/5b6e3ead24175.png)

## 说明/提示

#### Subtask 1 (12 points)

- $1 \leq n \leq 1000$

#### Subtask 2 (15 points)

- $1 \leq n \leq 10^9$

- $x_1 = x_2$ and $y_1 = y_2$

#### Subtask 3 (17 points)

- $1 \leq n \leq 10^5$

#### Subtask 4 (31 points)

- $1 \leq n \leq 10^9$

- $x_1 = y_1 = 1$

#### Subtask 5 (25 points)

- $1 \leq n \leq 10^9$

对于 $100 \%$ 数据，$1 \leq q \leq 100$，$1 \leq n \leq 10^9$，$-n \leq x_1 \leq x_2 \leq n$，$-n \leq y_1 \leq y_2 \leq n$。

## 样例 #1

### 输入

```
2 3
0 -2 1 1
-1 0 1 0
1 2 1 2
```

### 输出

```
74
9
14
```

# 题解

## 作者：Rigel (赞：36)

## 思路

数学题。

先定义象限**包括对应的坐标轴上的格点。**

对于查询的每一个矩形，分别计算此矩形在每个象限覆盖的格点的权值总和，最后减去重复计算的坐标轴格点的权值。

![](https://cdn.luogu.com.cn/upload/image_hosting/1zbcrn4u.png)

如图所示，将查询的矩形分为四个象限处理。

---

以第一象限为例。

设查询的矩形左下角为 $(a,b)$，右上角为 $(c,d)$。

设 $F(x,y)$ 表示：以 $(0,0)$ 为左下角，$(x,y)$ 为右上角的矩形所覆盖的格点的权值总和。（当 $x<0$ 或 $y<0$ 时，$F(x,y)=0$）

当第一象限内有格点被覆盖时，存在三种情况：

1. $a\leq 0$ **且** $b\leq 0$。此时坐标系原点被覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/7ez8y85n.png)

2. $a>0$ **且** $b>0$。此时坐标系原点未被覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/xs12s36w.png)

3. $a>0$ 与 $b>0$ 中只有一者成立。此时坐标系原点未被覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/6k1itxcj.png)

容易证明，第一象限对答案的贡献均为：

$F(c,d)-F(c,b-1)-F(a-1,d)+F(a-1,b-1).$

因此我们需要求出任一 $F(x,y)$ 的值。

---

设 $f(x)$ 表示：以 $(0,0)$ 为左下角，$(x,x)$ 为右上角的矩形所覆盖的格点的权值总和。

设 $W(x,y)$ 表示格点 $(x,y)$ 的权值。

设 $\begin{cases}
g_0(x)=\sum\limits_{i=0}^{x} W(0,i),\\
g_1(x)=\sum\limits_{i=0}^{x} W(-i,0),\\
g_2(x)=\sum\limits_{i=0}^{x} W(0,-i),\\
g_3(x)=\sum\limits_{i=0}^{x} W(i,0).
\end{cases}$

![](https://cdn.luogu.com.cn/upload/image_hosting/oixi8vax.png)

此时分三种情况讨论：

1. 当 $x=y$ 时，$F(x,y)=f(x)=f(y)$。

2. 当 $x>y$ 时，观察所求区域，将其分成两部分求解：

![](https://cdn.luogu.com.cn/upload/image_hosting/87n2fy7s.png)

深色部分即 $f(y)$。对于浅色部分，观察到 $11+28=g_3(x)-g_3(y)$。可以证明，在浅色部分中，每一列均为公差为 $1$ 的等差数列。因此我们可以推出浅色部分的贡献为：

$\dfrac{1}{2}[g_3(x)-g_3(y)+g_3(x)-g_3(y)+y(x-y)](y+1).$

即 $\dfrac{1}{2}[2g_3(x)-2g_3(y)+y(x-y)](y+1).$

此时 $F(x,y)=f(y)+\dfrac{1}{2}[2g_3(x)-2g_3(y)+y(x-y)](y+1)$。

3. 当 $x<y$ 时，同理，在浅色区域中，每一行均为公差为 $1$ 的等差数列。

![](https://cdn.luogu.com.cn/upload/image_hosting/q3ehm6ov.png)

此时 $F(x,y)=f(x)+\dfrac{1}{2}[2g_0(y)-2g_0(x)-x(y-x)](x+1)$。

---

对于第二、三、四象限，我们只需**旋转坐标系**，将所求象限转化至第一象限进行求解即可（在代码实现中体现为变换矩形对应顶点的坐标）。这样可以保证需要计算的横纵坐标均为自然数。

每个象限的 $F(x,y)$ 与 $f(x)$ 是不同的，计算中所需的 $g$ 函数也是不同的。

对于第一象限的 $F(x,y)$，计算 $x$ 轴上的格点总值用 $g_3$，计算 $y$ 轴上的格点总值用 $g_0$。

同理，第二象限用 $g_0$ 与 $g_1$，第三象限用 $g_1$ 与 $g_2$，第四象限用 $g_2$ 与 $g_3$。

接下来需要推导每个象限的 $f(x)$，以及所有的 $g$ 函数。

---

下面给出 $g$ 函数的推导。

以推导 $g_3$ 为例。观察到，$W(0,0)$ 至 $W(x,0)$ 所对应的数列为 $1,2,11,28,53\cdots$。可以证明 $W(x,0)$ 是 $x$ 的二次函数。经计算，得出 $W(x,0)=4x^2-3x+1$。

$\therefore g_3(x)=\sum\limits_{i=0}^{x} W(i,0)=\sum\limits_{i=0}^{x}(4i^2-3i+1)=\dfrac{2x(x+1)(2x+1)}{3}-\dfrac{3x(x+1)}{2}+x+1.$

同理，我们有：

$\begin{cases}
g_0(x)=\dfrac{2x(x+1)(2x+1)}{3}-\dfrac{x(x+1)}{2}+x+1,\\
\\
g_1(x)=\dfrac{2x(x+1)(2x+1)}{3}+\dfrac{x(x+1)}{2}+x+1,\\
\\
g_2(x)=\dfrac{2x(x+1)(2x+1)}{3}+\dfrac{3x(x+1)}{2}+x+1.
\end{cases}$

---

下面给出 $f(x)$ 的推导。

以第一象限为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/ur58avdb.png)

如图所示，将原图分层。定义 $(0,0)$ 为第 $0$ 层。

观察到，第 $x$ 层的权值总和为 $W(x,x)\cdot(2x+1)=(4x^2-2x+1)(2x+1)=8x^3+1$。

$\therefore f(x)=\sum\limits_{i=0}^{x}(8i^3+1)=2x^2(x+1)^2+x+1.$

同理，在第二象限的计算中：

$f(x)=2x^2(x+1)^2+\dfrac{2x(x+1)(2x+1)}{3}+x(x+1)+x+1.$

在第三象限的计算中：

$f(x)=2x^2(x+1)^2+\dfrac{4x(x+1)(2x+1)}{3}+2x(x+1)+x+1.$

第四象限较为特殊。

![](https://cdn.luogu.com.cn/upload/image_hosting/1xn53a5q.png)

如图，将每一层分成红色和蓝色两部分。

在第 $x$ 层中，红色区域的权值总和为 $\dfrac{1}{2}(x+1)(W(0,-x)+W(0,-x)+x)$，蓝色区域的权值总和为 $\dfrac{1}{2}x(W(x,0)+W(x,0)-(x-1))$。

将 $\begin{cases}
W(0,-x)=4x^2+3x+1,\\
W(x,0)=4x^2-3x+1.
\end{cases}$ 代入并化简，得第 $x$ 层的权值总和为 $8x^3+4x^2+6x+1$。

$\begin{aligned}
\therefore f(x)&=\sum\limits_{i=0}^{x}(8i^3+4i^2+6i+1)\\
&=2x^2(x+1)^2+\dfrac{2x(x+1)(2x+1)}{3}+3x(x+1)+x+1.
\end{aligned}$

至此完成所有象限中 $f(x)$ 的推导。

---

最终，对每一个被覆盖的象限进行计算，并减去重复计算的部分。

设查询的矩形左下角为 $(a,b)$，右上角为 $(c,d)$。

1. 当原点被覆盖（即查询的矩形覆盖了 $4$ 个象限）时，坐标轴（除原点）上被覆盖的格点被统计了 $2$ 次，原点被统计了 $4$ 次。此时 $ans$ 应减去 $g_3(c)+g_0(d)+g_1(-a)+g_2(-b)-1$。

2. 当原点未被覆盖且有坐标轴被覆盖（即查询的矩形覆盖了 $2$ 个象限）时，坐标轴上的格点被统计了 $2$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/0zx7dr98.png)

以此情况为例。此时 $ans$ 应减去 $g_3(c)-g_3(a-1)$。

其他情况同理，减去重叠部分即可。

3. 当原点未被覆盖且无坐标轴被覆盖（即查询的矩形仅覆盖 $1$ 个象限）时，无重复计算的部分。

**至此完成全部推导。**

## 代码

取模用 `modint`。对于除法，算出除数的逆元。

```cpp
#include<bits/stdc++.h>
#define int long long
#define TT 1000000007
#define _0 (modint){0}
#define _1 (modint){1}
#define _2 (modint){2}
#define _3 (modint){3}
#define _4 (modint){4}
#define d2 (modint){500000004}
#define d3 (modint){333333336}
#define M(x) (modint){x}
using namespace std;
int n,q,vis[4];
struct node{
	int x,y;
}a[4];
struct modint{
	int v;
	modint operator+(const modint &b)const{return (modint){(v+b.v)%TT};}
	modint operator-(const modint &b)const{return (modint){((v-b.v)%TT+TT)%TT};}
	modint operator*(const modint &b)const{return (modint){(v*b.v)%TT};}
}ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f; 
}
modint f(int op,modint x){
	if(op==3)return _2*x*x*(x+_1)*(x+_1)+x+_1;
	if(op==0)return _2*x*x*(x+_1)*(x+_1)+_2*x*(x+_1)*(_2*x+_1)*d3+x*(x+_1)+x+_1;
	if(op==1)return _2*x*x*(x+_1)*(x+_1)+_4*x*(x+_1)*(_2*x+_1)*d3+_2*x*(x+_1)+x+_1;
	if(op==2)return _2*x*x*(x+_1)*(x+_1)+_2*x*(x+_1)*(_2*x+_1)*d3+_3*x*(x+_1)+x+_1;
}
modint g(int op,modint x){
	if(op==3)return _2*x*(x+_1)*(_2*x+_1)*d3-_3*x*(x+_1)*d2+x+_1;
	if(op==0)return _2*x*(x+_1)*(_2*x+_1)*d3-x*(x+_1)*d2+x+_1;
	if(op==1)return _2*x*(x+_1)*(_2*x+_1)*d3+x*(x+_1)*d2+x+_1;
	if(op==2)return _2*x*(x+_1)*(_2*x+_1)*d3+_3*x*(x+_1)*d2+x+_1;
}
modint F(int op,modint x,modint y){
	if(x.v<0||y.v<0)return _0;
	if(x.v==y.v)return f(op,x);
	if(x.v>y.v)return f(op,y)+(_2*g(op,x)-_2*g(op,y)+(x-y)*y)*(y+_1)*d2;
	return f(op,x)+(_2*g((op+1)%4,y)-_2*g((op+1)%4,x)-(y-x)*x)*(x+_1)*d2;
}
void calc(int op){
	int sx=0,sy=0,ex=0,ey=0;
	if(op==3)sx=a[1].x,sy=a[1].y,ex=a[3].x,ey=a[3].y;
	if(op==0)sx=a[2].y,sy=-a[2].x,ex=a[0].y,ey=-a[0].x;
	if(op==1)sx=-a[3].x,sy=-a[3].y,ex=-a[1].x,ey=-a[1].y;
	if(op==2)sx=-a[0].y,sy=a[0].x,ex=-a[2].y,ey=a[2].x;
	ans=ans+F(op,M(ex),M(ey))-F(op,M(ex),M(sy-1))-F(op,M(sx-1),M(ey))+F(op,M(sx-1),M(sy-1));
}
signed main(){
	n=read(),q=read();
	while(q--){
		ans=_0;
		for(int i=0;i<=3;i++)vis[i]=0;
		a[1].x=read(),a[1].y=read(),a[3].x=read(),a[3].y=read();
		a[0].x=a[1].x,a[0].y=a[3].y,a[2].x=a[3].x,a[2].y=a[1].y;
		if(a[0].x<=0&&a[0].y>=0)calc(0),vis[0]=1;
		if(a[1].x<=0&&a[1].y<=0)calc(1),vis[1]=1;
		if(a[2].x>=0&&a[2].y<=0)calc(2),vis[2]=1;
		if(a[3].x>=0&&a[3].y>=0)calc(3),vis[3]=1;
        if(vis[0]&&vis[1]&&vis[2]&&vis[3])ans=ans-(g(3,M(a[3].x))+g(0,M(a[3].y))+g(1,M(-a[1].x))+g(2,M(-a[1].y))-_1);
        else{
            if(vis[3]&&vis[0])ans=ans-(g(0,M(a[3].y))-g(0,M(a[1].y-1)));
            if(vis[0]&&vis[1])ans=ans-(g(1,M(-a[1].x))-g(1,M(-a[3].x-1)));
            if(vis[1]&&vis[2])ans=ans-(g(2,M(-a[1].y))-g(2,M(-a[3].y-1)));
            if(vis[2]&&vis[3])ans=ans-(g(3,M(a[3].x))-g(3,M(a[1].x-1)));
        }
		printf("%lld\n",ans.v);
	}
	return 0;
}
```

单次询问为 $\mathcal{O}(1)$，故时间复杂度为 $\mathcal{O}(q)$。

---

