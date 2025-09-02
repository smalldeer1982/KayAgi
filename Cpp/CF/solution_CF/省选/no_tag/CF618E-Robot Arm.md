# Robot Arm

## 题目描述

Roger is a robot. He has an arm that is a series of $ n $ segments connected to each other. The endpoints of the $ i $ -th segment are initially located at points $ (i-1,0) $ and $ (i,0) $ . The endpoint at $ (i-1,0) $ is colored red and the endpoint at $ (i,0) $ is colored blue for all segments. Thus, the blue endpoint of the $ i $ -th segment is touching the red endpoint of the $ (i+1) $ -th segment for all valid $ i $ .

Roger can move his arm in two different ways:

1. He can choose some segment and some value. This is denoted as choosing the segment number $ i $ and picking some positive $ l $ . This change happens as follows: the red endpoint of segment number $ i $ and segments from $ 1 $ to $ i-1 $ are all fixed in place. Imagine a ray from the red endpoint to the blue endpoint. The blue endpoint and segments $ i+1 $ through $ n $ are translated $ l $ units in the direction of this ray. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/608a2bb2be5a1a38d31c7259ed31650fdc831466.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/8dcd266eaca289d2a51d6d607be6e49d38248853.png)In this picture, the red point labeled $ A $ and segments before $ A $ stay in place, while the blue point labeled $ B $ and segments after $ B $ gets translated.
2. He can choose a segment and rotate it. This is denoted as choosing the segment number $ i $ , and an angle $ a $ . The red endpoint of the $ i $ -th segment will stay fixed in place. The blue endpoint of that segment and segments $ i+1 $ to $ n $ will rotate clockwise by an angle of $ a $ degrees around the red endpoint. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/4eef0bf50f3454a86a62f402644b9a2c3d461358.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/ec84d464b2638b0a9a24702941e18140a91c9b78.png)In this picture, the red point labeled $ A $ and segments before $ A $ stay in place, while the blue point labeled $ B $ and segments after $ B $ get rotated around point $ A $ .

Roger will move his arm $ m $ times. These transformations are a bit complicated, and Roger easily loses track of where the blue endpoint of the last segment is. Help him compute the coordinates of the blue endpoint of the last segment after applying each operation. Note that these operations are cumulative, and Roger's arm may intersect itself arbitrarily during the moves.

## 说明/提示

The following pictures shows the state of the arm after each operation. The coordinates of point $ F $ are printed after applying each operation. For simplicity, we only show the blue endpoints of a segment (with the exception for the red endpoint of the first segment). For instance, the point labeled $ B $ is the blue endpoint for segment $ 1 $ and also the red endpoint for segment $ 2 $ .

Initial state:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/5dd94d4d99cfac21befb7a93befbed9aa8e53f84.png) Extend segment $ 1 $ by $ 3 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/5ab40d21a3128a7477f5fe60ed97f6335e1f7d0b.png) Rotate segment $ 3 $ by $ 90 $ degrees clockwise.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/3cc04dffc9e337d6a8b726a86dfd69075b16a531.png) Rotate segment $ 5 $ by $ 48 $ degrees clockwise.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/31b256905ebb7f9c64425dd492e0dea1a58b3d40.png) Extend segment $ 4 $ by $ 1 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618E/2ca643cd80863149bbc87b72a007522a1a3c680f.png)

## 样例 #1

### 输入

```
5 4
1 1 3
2 3 90
2 5 48
1 4 1
```

### 输出

```
8.0000000000 0.0000000000
5.0000000000 -3.0000000000
4.2568551745 -2.6691306064
4.2568551745 -3.6691306064
```

# 题解

## 作者：wsyhb (赞：5)

## 分析 + 题解

题目中有两种操作：

1. 第 $i$ 条线段延长 $l$ 个单位，其他线段长度、方向均不变；

2. 第 $i$ 至 $n$ 条线段绕第 $i$ 条线段左端点顺时针旋转 $\alpha^{\circ}$。

**第一种操作**很好维护，只需将第 $i$ 条线段的右端点及以后的点**整体平移**即可。

具体来说，设第 $i$ 条线段左端点坐标为 $(x_1,y_1)$，右端点坐标为 $(x_2,y_2)$，长度为 $d=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$，则只需将第 $i$ 条线段的右端点及以后的点的横纵坐标加上下列数值：

$$\Delta x=\frac{x_2-x_1}{d} l$$

$$\Delta y=\frac{y_2-y_1}{d} l$$

（这应该不需要证明吧，就是一个简单的相似，或者用三角函数来理解）

------------

但是**第二种操作**就没那么简单了，我们发现坐标的变化量不能简单地用一个式子表示出来。此时可以注意到，本题查询的仅仅是第 $n$ 条线段的右端点坐标，因此，我们可以考虑改变维护对象——从维护每个点到**维护每条线段**。

具体来说，我们需要**维护每条线段右端点相对于其左端点的坐标**。由于第二种操作不改变各线段的长度，它相当于每条线段对应的向量**顺时针**旋转 $\alpha^{\circ}$，给出一个坐标变换公式：

$$x'=x \cdot \cos \alpha^{\circ}+y \cdot \sin \alpha^{\circ}$$

$$y'=y \cdot \cos \alpha^{\circ}-x \cdot \sin \alpha^{\circ}$$

（其中 $(x,y)$ 是原坐标，$(x',y')$ 是旋转后坐标）

**证明**：平移线段使得其左端点与原点重合，设线段长度为 $l$，其方向为从 $x$ 轴正半轴起**逆时针**旋转 $\alpha$，则其右端点坐标为 $(l \cos \alpha,l \sin \alpha)$（记为 $(x,y)$），将其**逆时针**旋转 $\theta$，则旋转后的坐标 $(x',y')$ 如下：

$$x'=l \cos (\alpha+\theta)=l(\cos \alpha \cos \theta - \sin \alpha \sin \theta)=x \cdot \cos \theta-y \cdot \sin \theta$$

$$y'=l \sin (\alpha+\theta)=l(\sin \alpha \cos \theta + \cos \alpha \sin \theta)=y \cdot \cos \theta+x \cdot \sin \theta$$

而上述公式由于是**顺时针**旋转，相当于用 $-\theta$ 替换 $\theta$，因此后一项的符号变反。

------------

同时，多次旋转可以看作一次旋转，我们可以使用**线段树**维护每条线段右端点相对于其左端点的坐标，并使用 `lazy` 标记记录需要下放的旋转度数，即可进行普通的**区间修改**。

对于**第一种操作**，进行**单点修改**即可。

每次答案即为线段树根节点的值。

时间复杂度：$O(n \log n)$（实际上应该算上 `sin` `cos` 函数的复杂度）

## 代码

如果还有不清楚的就看注释吧。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const double Pi=3.1415926535897932384626433832795;
const int max_n=3e5+5;
struct Node
{
	double sx,sy,lazy;
	inline void merge(const Node &a,const Node &b)//线段树的向上合并操作 
	{
		sx=a.sx+b.sx,sy=a.sy+b.sy; 
	}
	inline void update(double ang)//旋转 ang 并更新 lazy（ang 使用弧度制） 
	{
		lazy+=ang;
		double Cos=cos(ang),Sin=sin(ang);//sin,cos 这些数学函数很慢，尽量少调用 
		double x=sx*Cos+sy*Sin,y=sy*Cos-sx*Sin;//同上述公式 
		sx=x,sy=y;
	}
}tree[max_n<<2];
inline void push_down(int p)
{
	tree[p<<1].update(tree[p].lazy);
	tree[p<<1|1].update(tree[p].lazy);
	tree[p].lazy=0;
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		tree[p].sx=1;//注意初始化 
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tree[p].merge(tree[p<<1],tree[p<<1|1]);
}
double res_x,res_y;//记录单点查询的答案 
void query(int p,int l,int r,int k)
{
	if(l==r)
	{
		res_x=tree[p].sx,res_y=tree[p].sy;
		return;
	}
	if(tree[p].lazy)
		push_down(p);
	int mid=(l+r)>>1;
	if(k<=mid)
		query(p<<1,l,mid,k);
	else
		query(p<<1|1,mid+1,r,k);
}
void modify(int p,int l,int r,int k,double dx,double dy)//平移的单点修改 
{
	tree[p].sx+=dx,tree[p].sy+=dy;
	if(l<r)
	{
		int mid=(l+r)>>1;
		if(k<=mid)
			modify(p<<1,l,mid,k,dx,dy);
		else
			modify(p<<1|1,mid+1,r,k,dx,dy);
	}
}
void rotate(int p,int l,int r,int a,int b,double ang)//旋转的区间修改 
{
	if(a<=l&&r<=b)
	{
		tree[p].update(ang);
		return;
	}
	if(tree[p].lazy)
		push_down(p);
	int mid=(l+r)>>1;
	if(a<=mid)
		rotate(p<<1,l,mid,a,b,ang);
	if(b>mid)
		rotate(p<<1|1,mid+1,r,a,b,ang);
	tree[p].merge(tree[p<<1],tree[p<<1|1]);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(x==1)
		{
			query(1,1,n,y);
			double d=sqrt(res_x*res_x+res_y*res_y);//线段长度 
			modify(1,1,n,y,z*res_x/d,z*res_y/d);
		}
		else
		{
			double ang=z*Pi/180;//角度制转弧度制 
			rotate(1,1,n,y,n,ang);
		}
		printf("%.10lf %.10lf\n",tree[1].sx,tree[1].sy);
	}
	return 0;
}
```

---

## 作者：Saliеri (赞：3)

前置芝士：

- [三角函数](https://baike.baidu.com/item/%E4%B8%89%E8%A7%92%E5%87%BD%E6%95%B0/1652457?fr=aladdin)

- [线段树](https://www.luogu.com.cn/problem/P3372)

~~不会吧不会吧，不会真的有人不会线段树切黑题吧~~

___

区间操作，nlogn 复杂度——**线段树**。

我们考虑一下需要维护什么。

### 方向1：维护每个点的真实坐标。

对于操作一，我们可以直接取出那条线段的起终点。

若相对于起点（则以起点为原点）终点的坐标为$(x,y)$，则扩展 $l$ 个单位在 $x,y$ 方向上的分量可以求出：
$$\Delta x = lx/\sqrt{x^2+y^2}$$ 
$$\Delta y = ly/\sqrt{x^2+y^2}$$

其实就是三角函数的定义。

然后区间加这个分量于所有在操作边以后的点。

对于操作二，可以将这个操作看做所有在操作边以后的点绕操作边的起点旋转$\alpha$°。

经典的技巧：绕原点旋转后的坐标可以用原先的坐标 $x,y$ 与旋转角 $\theta$ 表示。

(当然，这里的 $x,y$ 指的是点相对于操作边的起点的坐标，求出来后还要打补丁)。

在这个题中，这个式子为：

$$x' = x\cos\theta+y\sin\theta$$

$$y' = y\cos\theta-x\sin\theta$$

这是一个线性变换，所以可以用矩阵维护。

发现现在操作一无法通过打tag的方式维护，考虑把操作一写成矩阵形式。

也是个经典技巧：因为常数无法直接在2*2的矩阵中进行操作，所以往矩阵中加一维 $1$, 然后就可以啦。

因为这不是本篇题解的重头戏，所以本方法的矩阵转移，代码均略去不写（就是因为太麻烦了才用了第二种）。

### 方向2：维护每个点相对于上一个点的坐标。

其实方法一中已经暗示了这种做法。

我们需要维护的是两个分量的区间和（查询就是全局和）。

考虑操作二对维护的东西造成的影响，我们发现，操作二不仅可以看作绕操作边的起点旋转，也可以看做操作边之后的**每一条边一起旋转**。

旋转边可以直接用上面的式子。（维护的就是相对于旋转中心的坐标！）

每一条边都进行的如上的变换，那么 $\sum x$ 与 $\sum y$ 的变化是什么呢
？

我们发现，如果给出了 $\theta$，那么和的变换与单个坐标的变换是一样的！

那维护一个区间旋转 tag 就可以解决问题。

对于操作一，直接求出分量后单点改即可。

___

代码：

```cpp
#include <cmath>
#include <cstdio>
const int maxn = 3e5+5;
int n,m;
double xsum[maxn<<2],ysum[maxn<<2],tag[maxn<<2];
inline void pushup(int k){xsum[k] = xsum[k<<1] + xsum[k<<1|1],ysum[k] = ysum[k<<1] + ysum[k<<1|1];}
void build(int k,int l,int r){
	if(l == r)return xsum[k] = 1,ysum[k] = 0,void();
	int mid = l+r>>1;
	build(k<<1,l,mid),build(k<<1|1,mid+1,r);
	pushup(k);
}
void gettag(int k,double ang){
	double prex = xsum[k],prey = ysum[k];
	tag[k] += ang;
	xsum[k] = prex*std::cos(ang)+prey*std::sin(ang);
	ysum[k] = prey*std::cos(ang)-prex*std::sin(ang);
}
void pushdown(int k){
	if(std::abs(tag[k]) > 1e-10)
		gettag(k<<1,tag[k]),gettag(k<<1|1,tag[k]),tag[k] = 0;
}
void update(int k,int l,int r,int pos,double xdlt,double ydlt){
	if(l == r)return xsum[k] += xdlt,ysum[k] += ydlt,void();
	int mid = l+r>>1;
	pushdown(k);
	if(pos <= mid)update(k<<1,l,mid,pos,xdlt,ydlt);
	else update(k<<1|1,mid+1,r,pos,xdlt,ydlt);
	pushup(k);
}
void cover(int k,int l,int r,int x,int y,double ang){
	if(l>y||r<x)return ;
	if(l>=x&&r<=y)return gettag(k,ang);
	int mid = l+r>>1;
	pushdown(k);
	cover(k<<1,l,mid,x,y,ang),cover(k<<1|1,mid+1,r,x,y,ang);
	pushup(k);
}
void query(int k,int l,int r,int pos,double &x,double &y){
	if(l == r)return x = xsum[k],y = ysum[k],void();
	int mid = l+r>>1;
	pushdown(k);
	if(pos <= mid)query(k<<1,l,mid,pos,x,y);
	else query(k<<1|1,mid+1,r,pos,x,y);
}
int main(){
	scanf("%d %d",&n,&m);
	build(1,1,n);
	for(int i=1,ty,a,b;i<=m;++i){
		scanf("%d %d %d",&ty,&a,&b);
		if(ty == 1){
			double x,y;
			query(1,1,n,a,x,y);
			update(1,1,n,a,1.*b*x/std::sqrt(x*x+y*y),1.*b*y/std::sqrt(x*x+y*y));
		}
		if(ty == 2)
			cover(1,1,n,a,n,b*3.141592653589793/180);
		printf("%.8lf %.8lf\n",xsum[1],ysum[1]);
	}
	return 0;
}
```
完结撒花。

---

## 作者：_liujiaqi_ (赞：3)

## 题目

[luogu CF618E](https://www.luogu.org/problem/CF618E)

有 $n$ 条线段，第 $i$ 条线段的两端分别在 $(i - 1, 0)$ 和 $(i, 0)$

有 $m$ 次操作，分为两种操作：

$1.$ 把第 $i$ 条线段伸长 $l$，后面的线段跟着它移动。

$2.$ 把第 $i$ 条线段沿着它的起点**顺时针**旋转 $a$（角度制），后面的线段跟着它旋转。

每次操作后，输出第 $n$ 条线段终点的坐标。

---

## 做法

前置知识：计算几何（向量），线段树。

推荐一个 $dalao$ 写的非常好的计算几何初步的博客：

[计算几何初步](https://www.luogu.org/blog/wjyyy/geometry1)

---

### 直接模拟

首先，看到题目，~~作为一个什么都不会蒟蒻~~，第一反应是模拟。

维护每个线段的端点坐标，进行 $1$ 操作时，可以~~显然的~~发现，每个点的横纵坐标增加量相同，

求出这个增加量，让 $i$ 的右端点以及 $i + 1$ 至 $n$ 的左右端点都加上这个值。

伸长时，求出先线段的倾斜角 $\theta$，伸长量用 $len$ 来表示，那么

$x$ 方向的伸长量为 $len \cdot cos \; \theta$，

$y$ 方向的伸长量为 $len \cdot sin \; \theta$，

---

进行 $2$ 操作时，其实就是每个点绕 $i$ 的左端点旋转 $a$（角度制）。

如果一个线段的左端点为 $(x1, y1)$，右端点为 $(x2, y2)$，那该线段所代表的向量为 $(x2 - x1, y2 - y1)$，

旋转时，注意题目给的是角度制，计算时要转成弧度制，即乘以 $\frac{\pi}{180}$

对于向量**逆时针**旋转 $\theta$（弧度制）的公式为：

（注意题干上是**顺时针**旋转）

$x' = x \cdot cos \; \theta - y \cdot sin \; \theta$

$y' = x \cdot sin \; \theta + y \cdot cos \; \theta$

上代码：

```cpp
#include <cmath>
#include <cstdio>
int v, c;
template <class T> T read(T& x) {
    x = 0; v = 1; c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') v = -1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    return x *= v;
}
//以上是快读
const int N = 300010;
const double PI = acos(-1);
//用这种方式求PI精度损失较小
int Q, n, opt, x, val;
struct Edge {
    double x1, y1; //线段的左端点
    double x2, y2; //线段的右端点
} e[N];
void add(int x, double y) {
    double xx = e[x].x2 - e[x].x1;
    double yy = e[x].y2 - e[x].y1;
    //(xx,yy)为e[x]所表示的向量
    double len = sqrt(xx * xx + yy * yy);
    //向量的长度
    double dx = y * xx / len;
    //xx/len表示cos(theta)
    double dy = y * yy / len;
    //yy/len表示sin(theta)
    e[x].x2 += dx;
    e[x].y2 += dy;
    //dx,dy分别表示x,y方向上的伸长量
    for (register int i = x + 1; i <= n; ++i) {
        e[i].x1 += dx;
        e[i].x2 += dx;
        e[i].y1 += dy;
        e[i].y2 += dy;
        //直接暴力加上
    }
}
void rot(double x1, double y1, double& x2, double& y2, double theta) {
    //(x2,y2)绕(x1,y1)旋转theta
    //注意如果要写函数的话,x2,y2一定要加取地址符号,否则在函数外,他们的值没有改变
    double xx = x2 - x1;
    double yy = y2 - y1;
    double dx = xx * cos(theta) - yy * sin(theta);
    double dy = xx * sin(theta) + yy * cos(theta);
    x2 = x1 + dx;
    y2 = y1 + dy;
}
void rotate(int x, double theta) {
    rot(e[x].x1, e[x].y1, e[x].x2, e[x].y2, theta);
    for (register int i = x + 1; i <= n; ++i) {
        rot(e[x].x1, e[x].y1, e[i].x1, e[i].y1, theta);
        rot(e[x].x1, e[x].y1, e[i].x2, e[i].y2, theta);
        //因为旋转时,每个点的增加量都不同,所以必须分开计算
        //因为蒟蒻太懒了,所以写了函数
    }
}
int main() {
    read(n); read(Q);
    for (register int i = 1; i <= n; ++i) {
        e[i].x1 = double(i) - 1.0;
        e[i].x2 = double(i);
        //初始化坐标
    }
    for (; Q; --Q) {
        read(opt);
        read(x); read(val);
        if (opt & 1) {
            add(x, val); //伸长
        } else {
            val = 360 - val % 360;
            //因为题干上说顺时针旋转,而公式适用于逆时针旋转
	        double theta = double(val) / 180.0 * PI;
            //角度制转弧度制
            rotate(x, theta); //旋转
        }
        printf("%.10lf %.10lf\n", e[n].x2, e[n].y2);
        //输出最后一条线段的右端点
    }
    return 0;
}
```

---

### 正解

提交上去后，就会发现自己 $T$ 飞了，怎么办呢？

仔细看一下暴力程序，发现大部分时间都消耗到暴力枚举每个点进行修改，

而我们的修改区间每次都为 $i + 1$ 至 $n$，

查询时每次只询问最后一个点的坐标，

那有没有可以维护区间修改与单点查询的 $nlog(n)$ 级别数据结构呢？

有，线段树！~~（蒟蒻也只会这个了）~~

---

对于伸长，线段树基本操作，

但是线段树不好维护点的旋转，但根据上面的公式可以发现，维护线段的旋转还是很容易的。

于是我们建一棵线段树，维护每个线段所代表的向量，初始向量均为 $(1, 0)$。

伸长时直接找到所需伸长的线段，直接伸长，

---

旋转时，我们可以在维护一个倾斜角，记录旋转后的角度，

由左右儿子向上维护时，我们可以维护向量的和，

向量的和遵循三角形法则，所以我们需计算出其中一个向量在另一个向量上的增加量，

然后直接相加，具体实现看代码。

---

那答案怎么求呢？

因为每次询问最后一条线段的右端点的坐标，而我们维护的是向量的加和，

并且第一个点的左端点坐标始终为 $(0, 0)$，所以所有向量加起来就是答案。

我们直接输出下标为 $1$ 的线段树节点的横纵坐标即可。

注意代码中 $double$ 不要写成 $int$，~~蒟蒻因此调了一个小时~~

```cpp
#include <cmath>
#include <cstdio>
int v, c;
template <class T> T read(T& x) {
    x = 0; v = 1; c = getchar();
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') v = -1;
    for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
    return x *= v;
}
//依旧是快读
const int N = 600010;
const double PI = acos(-1);
int n, Q, opt, x, val;
struct Vector {
    double x, y; //向量的横纵坐标
    double theta; //倾斜角(弧度制)
    Vector() {x = y = theta = 0.0;}
    //初始化都为0
    Vector(double _x, double _y, double _sita) {
    //构造函数
        x = _x; y = _y; theta = _sita;
    }
};
int L[N << 2], R[N << 2];
Vector p[N << 1];
//注意线段树开4倍空间
#define ls (u << 1)
#define rs (u << 1 | 1)
//ls,rs分别表示u的左右儿子
void update(int u) {
    //加和向量时,我们以左儿子为基准,求出右儿子在左儿子上的增加量
    double len = sqrt(p[rs].x * p[rs].x + p[rs].y * p[rs].y);
    //右儿子的长度
    double theta = atan2(p[rs].y, p[rs].x);
    //用atan2求反正切不用考虑除数为0
    p[u].x = p[ls].x + len * cos(p[ls].theta + theta);
    p[u].y = p[ls].y + len * sin(p[ls].theta + theta);
    //详见之前的公式
    p[u].theta = p[ls].theta + p[rs].theta;
    //倾斜角直接相加
}
void build(int u, int l, int r) {
    L[u] = l; R[u] = r;
    //L,R记录该向量左右端点的标号
    if (L[u] + 1 == R[u]) {
    //如果该向量的左右端点相邻,就返回
        p[u] = Vector(1.0, 0.0, 0.0);
        //初始均为(1,0),倾斜角为0
        return; 
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid, r);
    //有可能该线段的右端点就是下一个线段的左端点,所以不能写为(mid+1,r)
    update(u);
}

void modify(int u, int pos, double vLen, double vTheta) {
    if (L[u] + 1 == R[u]) {
        double len = sqrt(p[u].x * p[u].x + p[u].y * p[u].y);
        //p[u]的长度
        double theta = atan2(p[u].y, p[u].x);
        //p[u]的倾斜角
        len += vLen;
        theta += vTheta;
        //直接加上
        p[u].x = len * cos(theta);
        p[u].y = len * sin(theta);
        //维护向量的坐标
        p[u].theta = theta;
        return;
    }
    if (pos <= R[ls]) modify(ls, pos, vLen, vTheta);
    //如果我们当前要修改的线段在他左儿子的范围内,沿左儿子向下修改
    else modify(rs, pos, vLen, vTheta);
    //否则向右儿子修改
    update(u);
    //时刻更新
}
int main() {
    read(n); read(Q);
    build(1, 0, n);
    //初始化建树
    for (; Q; --Q) {
        read(opt);
        read(x); read(val);
        if (opt & 1) {
            modify(1, x, double(val), 0.0); //伸长
        } else {
            val = 360 - val % 360;
            double theta = double(val) / 180.0 * PI;
            //角度制转弧度制
            modify(1, x, 0.0, theta); //旋转
        }
        printf("%.10lf %.10lf\n", p[1].x, p[1].y);
        //p[1]所的坐标即为最后一条线段的右端点
    }
    return 0;
}
```

最后说一下，如果没有做过类似的题，一般不会往线段树方面去想，

但是即使想到了之后的，~~对于我这样的蒟蒻而言~~，代码实现也是挺麻烦的，

如果是考场上遇到这道题，~~像我这种蒟蒻~~，还是先看别的题，最后有时间再来看这题吧。

---

## 作者：peterwuyihong (赞：2)

### 看到旋转操作，考虑虚数
加长操作：如果这条边头是 $A$ ，尾是 $B$ ，加长长度$len$，则令 $t=(B-A)$ , $B$ 及以后的全加上 $\frac{t\times len}{|B-A|}$

旋转操作：如果这条边头是 $A$ ，尾是 $B$ ，则让 $B$ 及以后的所有点（记为 $P$ ），变为 $(P-A)*e^{i\alpha}+A $ 也就是 $P*e^{i\alpha}+(1-e^{i\alpha})*A$

先乘再加，用线段树维护即可，我直接拉的线段树 $2$ 板子，其实只要做区间 ~~惩罚~~ 乘法区间加法单点询问线段树即可

```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
#ifndef ONLINE_JUDGE
	#define pia getchar
#else
	#define pia nc
#endif
char nc(){
  	static char buf[1<<25],*p=buf,*q=buf;
  	if(p==q&&(q=(p=buf)+fread(buf,1,1<<25,stdin),p==q))return EOF;
  	return *p++;
}
template<class T>void rd(T&x){
	short f=1;x=0;
	char ch=pia();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=pia();
	}while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=pia();
	}x*=f;
}
template<class T>void wr(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)wr(x/10);
	putchar(x%10+48);
}

#define maxn 300010
int n,m;
int x,y,z;
struct Cp{
	double a,b;
	Cp(double aa=0,double bb=0):a(aa),b(bb){}
	Cp operator+(Cp x)const{return Cp(a+x.a,b+x.b);}
	Cp operator-(Cp x)const{return Cp(a-x.a,b-x.b);}
	Cp operator*(Cp x)const{return Cp(a*x.a-b*x.b,a*x.b+x.a*b);}
	Cp operator*(int x)const{return Cp(a*x,b*x);}
	double len(){return sqrt(a*a+b*b);}
	void print(){
		printf("%.12lf %.12lf\n",a,b);
	}
};
Cp e(int a){
	double r=a*3.14159265358979323846/180;
	return Cp(cos(r),-sin(r));
}
struct{
	int l,r;
	Cp sum,mul,add;
}tree[maxn<<2];
void pushup(int x){
	tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
}
void pushdown(int x){
	if(tree[x].mul.a!=1||tree[x].mul.b){
		tree[x<<1].add=tree[x<<1].add*tree[x].mul;
		tree[x<<1|1].add=tree[x<<1|1].add*tree[x].mul;
		tree[x<<1].sum=tree[x<<1].sum*tree[x].mul;
		tree[x<<1|1].sum=tree[x<<1|1].sum*tree[x].mul;
		tree[x<<1].mul=tree[x<<1].mul*tree[x].mul;
		tree[x<<1|1].mul=tree[x<<1|1].mul*tree[x].mul;
		tree[x].mul=Cp(1,0);
	}
	if(tree[x].add.a||tree[x].add.b){
		tree[x<<1].add=tree[x<<1].add+tree[x].add;
		tree[x<<1|1].add=tree[x<<1|1].add+tree[x].add;
		tree[x<<1].sum=tree[x<<1].sum+tree[x].add*(tree[x<<1].r-tree[x<<1].l+1);
		tree[x<<1|1].sum=tree[x<<1|1].sum+tree[x].add*(tree[x<<1|1].r-tree[x<<1|1].l+1);
		tree[x].add=Cp(0,0);
	}
}
void build(int x,int l,int r){
	tree[x].l=l,tree[x].r=r;
	tree[x].mul=Cp(1,0);
	if(l==r){
		tree[x].sum=Cp(l-1,0);
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	pushup(x);
}
void add(int x,int l,int r,Cp k){
	if(tree[x].l>=l&&tree[x].r<=r){
		tree[x].add=tree[x].add+k;
		tree[x].sum=tree[x].sum+Cp(tree[x].r-tree[x].l+1)*k;
		return;
	}
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	if(l<=mid)add(x<<1,l,r,k);
	if(r>mid)add(x<<1|1,l,r,k);
	pushup(x);
}
void mul(int x,int l,int r,Cp k){
	if(tree[x].l>=l&&tree[x].r<=r){
		tree[x].add=tree[x].add*k;
		tree[x].mul=tree[x].mul*k;
		tree[x].sum=tree[x].sum*k;
		return;
	}
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	if(l<=mid)mul(x<<1,l,r,k);
	if(r>mid)mul(x<<1|1,l,r,k);
	pushup(x);
}
Cp get(int x,int pos){
	if(tree[x].l==tree[x].r)return tree[x].sum;
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	if(pos<=mid)return get(x<<1,pos);
	else return get(x<<1|1,pos);
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	rd(n),rd(m);
	build(1,1,n+1);
	while(m--){
		rd(z),rd(x),rd(y);
		Cp A=get(1,x),B=get(1,x+1);
		if(z==1){
			Cp t=B-A;
			double ll=t.len();
			t=Cp(y*t.a/ll,y*t.b/ll);
			add(1,x+1,n+1,t);
		}else{
			Cp E=e(y);
			mul(1,x+1,n+1,E);
			add(1,x+1,n+1,(Cp(1,0)-E)*A);
		}
		Cp g=get(1,n+1);
		g.print();
	}

#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}

```


---

## 作者：cike_bilibili (赞：0)

典题，不就是区间加区间 sin/cos 和？

首先我们将坐标的横纵坐标分开考虑，不妨设第 $i$ 根机械臂与水平面夹角为 $\alpha_i$，长度为 $len_i$，$ans_x,ans_y$ 为最后的横、纵坐标，有式子：

$$ans_x = \sum_{i=1}^n len_i \cos \alpha_i$$

$$ans_y = \sum_{i=1}^n len_i \sin \alpha_i$$

我们要做的两种修改操作，一种是单点改 $len_i$，一种是区间加 $\alpha$，就是带权的 P6327 了。

---

这里再简单阐述一下如何维护这一坨东西。

建出线段树，分别维护第 $i$ 个节点上的 $s_i,c_i$，分别表示 $\sum_{j=l_i}^{r_i} len_j \sin \alpha_j$ 和 $\sum_{j=l_i}^{r_i} len_j \cos \alpha_j$，则区间加 $\alpha$ 操作，我们用和差角公式维护，有：

$$\sum_{j=l_i}^{r_i} len_j \sin (\alpha_j + \theta) =\cos \theta \sum_{j=l_i}^{r_i} len_j \sin \alpha_j + \sin \theta \sum_{j=l_i}^{r_i} len_j \cos \alpha_j$$

$$\sum_{j=l_i}^{r_i} len_j \cos (\alpha_j + \theta) =\cos \theta \sum_{j=l_i}^{r_i} len_j \cos \alpha_j - \sin \theta \sum_{j=l_i}^{r_i} len_j \sin \alpha_j$$

也就是：

$$s'_i=s_i \cos \theta +c_i \sin \theta$$

$$c'_i=c_i \cos \theta - s_i \sin \theta$$

简单维护就行了。

单点改 $len_i$ 暴力改。

---

## 作者：Svemit (赞：0)

# Sol:

考虑维护每个位置的向量。

对于操作一，直接按比例算出新的偏移量即可。

对于操作二，由于向量的旋转是线性变换，所以后面一整段绕某个点旋转一个角度，相当于每个向量都旋转这个角度再相加，并且具有结合律。

线段树维护向量即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 3e5 + 5;
const db Pi = acos(-1);

int n, m;

struct Vector {
	db x, y;
	
	void rotate(db a) {
		db xx, yy;
		xx = x * cos(a) + y * sin(a);
		yy = y * cos(a) - x * sin(a);
		x = xx, y = yy;
	}
	
	void get_longer(db len) {
		db cur = sqrt(x * x + y * y);
		x *= (len + cur) / cur;
		y *= (len + cur) / cur;
	}
};

Vector operator +(const Vector &lhs, const Vector &rhs) {
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

struct SegT {
	int l, r;
	Vector val;
	db tag;
	
	void apply(db v) {
		tag += v;
		val.rotate(v);
	}
	
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define val(x) tr[x].val
	#define tag(x) tr[x].tag
} tr[N * 4];

void pushdown(int x) {
	tr[x * 2].apply(tag(x)), tr[x * 2 + 1].apply(tag(x));
	tag(x) = 0.0;
}

void build(int l, int r, int x) {
	tr[x] = {l, r};
	if (l == r) {
		val(x) = {1.0, 0.0};
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid, x * 2), build(mid + 1, r, x * 2 + 1);
	val(x) = val(x * 2) + val(x * 2 + 1);
}

void update_len(int p, int x, db v) {
	if (l(x) == r(x)) {
		val(x).get_longer(v);
		return;
	}
	pushdown(x);
	int mid = (l(x) + r(x)) / 2;
	if (p <= mid) {
		update_len(p, x * 2, v);
	} else {
		update_len(p, x * 2 + 1, v);
	}
	val(x) = val(x * 2) + val(x * 2 + 1);
}

void update_rotate(int l, int r, int x, db v) {
	if (l <= l(x) && r(x) <= r) {
		tr[x].apply(v);
		return;
	}
	pushdown(x);
	int mid = (l(x) + r(x)) / 2;
	if (l <= mid) {
		update_rotate(l, r, x * 2, v);
	}
	if (r > mid) {
		update_rotate(l, r, x * 2 + 1, v);
	}
	val(x) = val(x * 2) + val(x * 2 + 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> n >> m;
	build(1, n, 1);
	
	while (m --) {
		int op, x;
		db y;
		cin >> op >> x >> y;
		if (op == 1) {
			update_len(x, 1, y);
		} else {
			y = y * Pi / 180.0;
			update_rotate(x, n, 1, y);
		}
		cout << fixed << setprecision(10) << val(1).x << ' ' << val(1).y << "\n";
	}
	
	return 0;
}
```

---

## 作者：Resurgammm (赞：0)

> 给定 $n$ 条线段，首尾相接，初始第 $i$ 条线段的起点和终点坐标为 $(i-1,0)$ 和 $(i,0)$，有 $m$ 个操作：

> $1:$ 使第 $i$ 条线段延长 $l$ 单位长度。

> $2:$ 使第 $i$ 条线段以起点为中心顺时针旋转 $\alpha^{\circ}$。

> 两种操作都要保证剩下的线段与之相对位置不变。

> 求每次操作后第 $n$ 条线段的终点坐标。

考虑用线段树维护每条线段所对应的 **向量**（即终点和起点的相对位置）。

由于向量可以平移，那么就先将所有线段的起点平移到原点，设平移后终点坐标为 $(x,y)$。

对于操作 $1$，由相似，有：

$$\begin{cases}\frac{l}{\sqrt{x^2+y^2}}=\frac{\Delta x}{x} \\ \frac{l}{\sqrt{x^2+y^2}}=\frac{\Delta y}{y}\end{cases}\Rightarrow \begin{cases}\Delta x=\frac{lx}{\sqrt{x^2+y^2}} \\ \Delta y=\frac{ly}{\sqrt{x^2+y^2}}\end{cases}$$

所以直接将第 $i$ 条线段的向量分别加上 $\Delta x,\Delta y$ 即可，直接在线段树上单点修改。

对于操作 $2$，先将给出的角度制转化为弧度制，设第 $i$ 条线段原来相对于坐标轴的角度为 $\theta$，由三角恒等变换，有：

$$\begin{cases}x'=\sqrt{x^2+y^2}\cos(\theta-\alpha) \\ y'=\sqrt{x^2+y^2}\sin(\theta-\alpha)\end{cases}\Rightarrow \begin{cases}x'=x\cos\alpha+y\sin\alpha \\ y'=y\cos\alpha-x\sin\alpha\end{cases}$$

在线段树上打一个旋转角的 $\text{lazy tag}$，对于第 $i\sim n$ 条线段区间修改即可。

由于向量可以平移，那么将每次操作后得到的线段重新收尾相接相对位置不变，且最后一条线段终点坐标为所有向量相加。

每次答案即为线段树根节点的值。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	#define fill(a,b,c,d) memset(a,b,sizeof(c)*(d+1))
	#define debug puts("debug")
	#define breakpoint exit(0)
	#define out(x) cout<<#x<<" : "<<x<<"\n"
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x,char ch='\n'){
		static int sta[35]; int top=0;
		if(x<0) putchar('-'),x=-x;
		do{sta[++top]=x%10,x/=10;}while(x);
		while(top) putchar(sta[top--]+48); putchar(ch);
	}
}
using namespace IO;
namespace CL{ 

	const int maxn=3e5+5;
	const double pi=acos(-1);

	int n,m;
	namespace SegmentTree{
		#define lson p<<1
		#define rson p<<1|1
		struct node{
			double sumx,sumy,tag;
			node(){}
			node(double _sumx,double _sumy,double _tag){
				sumx=_sumx,sumy=_sumy,tag=_tag;
			}
		}t[maxn<<2];
		inline void pushup(int p){
			t[p].sumx=t[lson].sumx+t[rson].sumx;
			t[p].sumy=t[lson].sumy+t[rson].sumy;
		}
		inline void pushtag(int p,double k){
			double sumx=t[p].sumx,sumy=t[p].sumy;
			t[p].sumx=sumx*cos(k)+sumy*sin(k);
			t[p].sumy=sumy*cos(k)-sumx*sin(k);
			t[p].tag+=k;
		}
		inline void pushdown(int p){
			if(t[p].tag){
				pushtag(lson,t[p].tag),pushtag(rson,t[p].tag);
				t[p].tag=0;
			}
		}
		void build(int p,int l,int r){
			if(l==r) return t[p]=node(1,0,0),void();
			int mid=(l+r)>>1;
			build(lson,l,mid),build(rson,mid+1,r);
			pushup(p);
		}
		void modify(int p,int l,int r,int pos,double x,double y){
			if(l==r) return t[p].sumx+=x,t[p].sumy+=y,void();
			int mid=(l+r)>>1;
			pushdown(p);
			if(pos<=mid) modify(lson,l,mid,pos,x,y);
			else modify(rson,mid+1,r,pos,x,y);
			pushup(p);
		}
		void update(int p,int l,int r,int tl,int tr,double k){
			if(tl<=l && r<=tr) return pushtag(p,k),void();
			int mid=(l+r)>>1;
			pushdown(p);
			if(tl<=mid) update(lson,l,mid,tl,tr,k);
			if(tr>mid) update(rson,mid+1,r,tl,tr,k);
			pushup(p);
		}
		node query(int p,int l,int r,int pos){
			if(l==r) return t[p];
			int mid=(l+r)>>1;
			pushdown(p);
			if(pos<=mid) return query(lson,l,mid,pos);
			else return query(rson,mid+1,r,pos);
		}
	}using namespace SegmentTree;

	inline int main(){
		n=read(),m=read();
		build(1,1,n);
		while(m--){
			int op=read(),a=read(),b=read();
			if(op==1){
				node now=query(1,1,n,a);
				double len=sqrt(now.sumx*now.sumx+now.sumy*now.sumy);
				modify(1,1,n,a,now.sumx*1.0*b/len,now.sumy*1.0*b/len);
			}
			if(op==2) update(1,1,n,a,n,1.0*b*pi/180.0);
			printf("%.10lf %.10lf\n",t[1].sumx,t[1].sumy);
		}
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：ShuYuMo (赞：0)

~~这个题是线段树模板题吧~~

可以考虑把问题形式化一下：
 - 求从原点出发，沿着每一条手臂移动，移动到最后一个点的坐标。
 - 支持修改

向量是可以用来描述一种移动的，这就和题目中要求做的对应起来了。

把每一条手臂看成一个向量，那么最后要求的就是这些向量的和。

那么对手臂的修改就可以转化为对手臂对应向量做修改。

考虑两种修改：

 - 对于伸长操作，显然就是把对应向量伸长，这个很简单
 - 对于旋转操作，不难发现其实是把这个向量及其后面的所有向量都旋转相同的一个角度。
 
众所周知，可以用矩阵来描述对向量的旋转操作，而且矩阵满足结合律和分配律，这样就可以线段树维护了。

所以可以考虑线段树每个结点维护向量和，lazy 标记（对向量的修改）就可以使用矩阵表示。

考虑旋转一个向量的矩阵，若旋转 $\alpha$ 度，可以构造为：
$$
\begin{bmatrix}
\cos\alpha &-\sin\alpha\\
\sin\alpha &\cos\alpha
\end{bmatrix}
$$

推法可以参考[这里](https://oi-wiki.org/math/vector/#_24) 其实可以考虑把向量放到复平面里面，然后这个式子就很显然了，个人感觉比三角恒等变换的推法要优美。

线段树维护向量和即可。

好像有很多人懒标记是旋转角度，其实如果操作只有旋转的话，都是可以的，我只是觉得这样想起来更自然。如果维护旋转角度，每次下放标记都要三角函数算一算，会比维护矩阵慢很多，写出来也没有卡常数…~~然后就最优解了~~。 /CY

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

#define db double 

const db PI = acos(-1.);

namespace SegmentTree{
	int n;
	const int _ = 2e6 + 100; 
	db squ(db x) { return x * x; }
	struct Vector{
		db x, y; 
		Vector(){} 
		Vector(db a, db b) { x = a; y = b; }
		db Length() { return sqrt(squ(x) + squ(y)); }
		void pull(db len) {
			db tmp = this->Length();
			x *= (len + tmp) / tmp;
			y *= (len + tmp) / tmp;
		}
	};
	Vector operator + (const Vector & A, const Vector & B) { return Vector(A.x + B.x, A.y + B.y); }
	/**
	 | a b |
	 | c d |
	*/
	struct Matrix{
		db a, b, c, d;
		Matrix() { a = d = 1; c = b = 0; }
		Matrix(db $1, db $2, db $3, db $4) {
			a = $1; b = $2;
			c = $3; d = $4;
		}
		Matrix(db alpha){ // 逆时针 alpha 度。
			db $1 = cos(alpha), $2 = sin(alpha);
			a = $1; b = -$2;
			c = $2; d = $1;
		}
	};
	#define EPS (1e-9)
	inline int sign(db x) { return x < -EPS ? -1 : (x > EPS); }
	inline int cmp(db x, db y) { return sign(x - y); }
	inline bool operator == (const Matrix & A, const Matrix & B) { return cmp(A.a, B.a) == 0 && cmp(A.b, B.b) == 0 && cmp(A.c, B.c) == 0 && cmp(A.d, B.d) == 0; }
	Matrix operator * (const Matrix & A, const Matrix & B) {
		Matrix ret;
		ret.a = A.a * B.a + A.b * B.c;
		ret.b = A.a * B.b + A.b * B.d;
		ret.c = A.c * B.a + A.d * B.c;
		ret.d = A.c * B.b + A.d * B.d;
		return ret;
	}
	Vector operator * (const Matrix & A, const Vector & B) { return Vector(A.a * B.x + A.b * B.y, A.c * B.x + A.d * B.y); }
	Vector v[_]; Matrix tag[_];
	#define ls(o) (o << 1)	
	#define rs(o) ((o << 1) | 1)
	#define maintain(o) (v[o] = v[ls(o)] + v[rs(o)])
	void tar(int o, Matrix V){
		tag[o] = V * tag[o];
		v[o]   = V * v[o];
	}
	void push(int o) {
		if(tag[o] == tag[0]) return ;
		tar(ls(o), tag[o]);
		tar(rs(o), tag[o]);
		tag[o] = tag[0];
	}
	void build(int o, int L, int R) {
		if(L == R) return v[o] = Vector(1, 0), void();
		int mid = (L + R) >> 1;
		build(ls(o), L, mid); build(rs(o), mid + 1, R);
		maintain(o);
	}
	void build(int __) { n = __; return build(1, 1, n); }
	void update_pull(int o, int nowl, int nowr, int p, db L){
		if(nowl == nowr) return v[o].pull(L), void();
		int mid = (nowl + nowr) >> 1; push(o); 
		if(p <= mid) update_pull(ls(o), nowl, mid, p, L);
		if(p  > mid) update_pull(rs(o), mid + 1, nowr, p, L);
		maintain(o);
	}
	void update_pull(int p, db L) { return update_pull(1, 1, n, p, L); }
	void update_rotate(int o, int nowl, int nowr, int L, int R, Matrix x) {
		if(L <= nowl && nowr <= R) return tar(o, x);
		int mid = (nowl + nowr) >> 1; push(o);
		if(L <= mid) update_rotate(ls(o), nowl, mid, L, R, x);
		if(R  > mid) update_rotate(rs(o), mid + 1, nowr, L, R, x);
		maintain(o);
	}
	void update_rotate(int p, db alpha){
		alpha = 360 - alpha; alpha = (alpha / 180.) * PI;
		update_rotate(1, 1, n, p, n, Matrix(alpha));
	}
	Vector query() { push(1); return v[1]; }
}
using SegmentTree::update_pull;
using SegmentTree::update_rotate;
using SegmentTree::query;
using SegmentTree::build;
using SegmentTree::Vector;
int n, m;
int main(){
	scanf("%d%d", &n, &m);
	build(n);
	while(m--){
		int opt, x; scanf("%d%d", &opt, &x);
		if(opt == 1){
			db L; scanf("%lf", &L);
			update_pull(x, L);
		} else {
			db alpha; scanf("%lf", &alpha);
			update_rotate(x, alpha);
		}
		Vector ret = query();
		printf("%.5lf %.5lf\n", ret.x, ret.y);
	}
	return 0;
}
```

---

