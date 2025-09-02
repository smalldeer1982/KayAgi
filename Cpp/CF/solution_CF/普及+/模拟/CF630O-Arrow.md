# Arrow

## 题目描述

Petya has recently started working as a programmer in the IT city company that develops computer games.

Besides game mechanics implementation to create a game it is necessary to create tool programs that can be used by game designers to create game levels. Petya's first assignment is to create a tool that allows to paint different arrows on the screen.

A user of this tool will choose a point on the screen, specify a vector (the arrow direction) and vary several parameters to get the required graphical effect. In the first version of the program Petya decided to limit parameters of the arrow by the following: a point with coordinates $ (px,py) $ , a nonzero vector with coordinates $ (vx,vy) $ , positive scalars $ a,b,c,d,a&gt;c $ .

The produced arrow should have the following properties. The arrow consists of a triangle and a rectangle. The triangle is isosceles with base of length $ a $ and altitude of length $ b $ perpendicular to the base. The rectangle sides lengths are $ c $ and $ d $ . Point $ (px,py) $ is situated in the middle of the triangle base and in the middle of side of rectangle that has length $ c $ . Area of intersection of the triangle and the rectangle is zero. The direction from $ (px,py) $ point to the triangle vertex opposite to base containing the point coincides with direction of $ (vx,vy) $ vector.

Enumerate the arrow points coordinates in counter-clockwise order starting from the tip.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630O/b1373ea5c55d47b5adf32698b1a37967e1fa1cc0.png)

## 样例 #1

### 输入

```
8 8 0 2 8 3 4 5
```

### 输出

```
8.000000000000 11.000000000000
4.000000000000 8.000000000000
6.000000000000 8.000000000000
6.000000000000 3.000000000000
10.000000000000 3.000000000000
10.000000000000 8.000000000000
12.000000000000 8.000000000000
```

# 题解

## 作者：Rigel (赞：10)

## 思路

首先假设箭头方向向上。依题意，构造出符合条件的点。

由于向量规定了箭头方向，我们应旋转图形。

设 $h=\sqrt{{v_x}^2+{v_y}^2}$， $\theta=\arcsin({\dfrac{-v_x}{h}})$，则 $\sin\theta=\dfrac{-v_x}{h}$，$\cos\theta=\dfrac{v_y}{h}$。

考虑将所有点的横坐标减去 $p_x$，纵坐标减去 $p_y$。这相当于将整个图形平移，并使 $(p_x,p_y)$ 落在坐标系原点。

然后将每个点绕原点逆时针旋转 $\theta$ 的角度。设点 $(x,y)$ 旋转后的坐标为 $(X,Y)$，则：

$
\begin{cases}
X=x\cos\theta-y\sin\theta,
\\
Y=x\sin\theta+y\cos\theta.
\end{cases}
$

最后将所有点的横坐标加上 $p_x$，纵坐标加上 $p_y$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
double px,py,vx,vy,a,b,c,d,h,sin_t,cos_t;
struct node{
	double x,y;
}n[10];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f; 
}
node revolve(node ni){
	double new_x=ni.x*cos_t-ni.y*sin_t,new_y=ni.x*sin_t+ni.y*cos_t;
	return (node){new_x,new_y};
}
signed main(){
	px=read(),py=read(),vx=read(),vy=read(),a=read(),b=read(),c=read(),d=read();
	h=sqrt(vx*vx+vy*vy);
	sin_t=-vx/h,cos_t=vy/h;
	n[0]=(node){px,py+b};
	n[1]=(node){px-a/2,py};
	n[2]=(node){px-c/2,py};
	n[3]=(node){px-c/2,py-d};
	n[4]=(node){px+c/2,py-d};
	n[5]=(node){px+c/2,py};
	n[6]=(node){px+a/2,py};
	for(int i=0;i<=6;i++)n[i].x-=px,n[i].y-=py;
	for(int i=0;i<=6;i++)n[i]=revolve(n[i]);
	for(int i=0;i<=6;i++)n[i].x+=px,n[i].y+=py;
	for(int i=0;i<=6;i++)printf("%.12lf %.12lf\n",n[i].x,n[i].y);
	return 0;
}
```

---

## 作者：€€£ (赞：0)

我们发现，题意给的很明白了，这是一道模拟题；

于是我们可以按照他的要求模拟；

向量 $(x,y)$ 旋转后是 $(y,-x)$；

所以真的直接模拟就好了（

code:

```cpp
# include <stdio.h>
# include <math.h>
# include <algorithm>
# define ld double
int main()
{
	int i,j,n,m,px,py,vx,vy,vvx,vvy,b,d;
	ld cd,a,c,x,y;
	scanf("%d%d%d%d%lf%d%lf%d",&px,&py,&vx,&vy,&a,&b,&c,&d);
	cd=sqrt(vx*vx+vy*vy);
	printf("%.10lf %.10lf\n",(ld)px+(ld)b/cd*(ld)vx,(ld)py+(ld)b/cd*(ld)vy);
	a/=2;
	c/=2;
	vvx=-vx;
	vvy=-vy;
	std::swap(vx,vy);
	vx=-vx;
	printf("%.10lf %.10lf\n",(ld)px+(ld)a/cd*(ld)vx,(ld)py+(ld)a/cd*(ld)vy);
	printf("%.10lf %.10lf\n",(ld)px+(ld)c/cd*(ld)vx,(ld)py+(ld)c/cd*(ld)vy);
	printf("%.10lf %.10lf\n",(ld)px+(ld)c/cd*(ld)vx+(ld)d/cd*(ld)vvx,(ld)py+(ld)c/cd*(ld)vy+(ld)d/cd*(ld)vvy);
	vx=-vx;
	vy=-vy;
	printf("%.10lf %.10lf\n",(ld)px+(ld)c/cd*(ld)vx+(ld)d/cd*(ld)vvx,(ld)py+(ld)c/cd*(ld)vy+(ld)d/cd*(ld)vvy);
	printf("%.10lf %.10lf\n",(ld)px+(ld)c/cd*(ld)vx,(ld)py+(ld)c/cd*(ld)vy);
	printf("%.10lf %.10lf\n",(ld)px+(ld)a/cd*(ld)vx,(ld)py+(ld)a/cd*(ld)vy);
	return 0;
}
```

写在后面：

好像CF用long double会有奇奇怪怪的错误（

---

