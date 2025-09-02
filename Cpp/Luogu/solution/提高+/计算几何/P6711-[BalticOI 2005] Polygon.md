# [BalticOI 2005] Polygon

## 题目描述

给定一个凸包的每条边的长度，求这个凸包。

## 说明/提示

#### 样例说明

对于样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/7bbhlpom.png)

#### 数据规模与约定

对于 $100\%$ 的数据，$3 \le  N \le 1000$，$1 \le a_i \le 10^4$。

**本题使用 Special Judge。**

感谢 spj 作者 @[tiger2005](https://www.luogu.com.cn/user/60864)。

#### 说明

翻译自 [BalticOI 2005 Day2 C Polygon](https://boi.cses.fi/files/boi2005_day2.pdf)。

## 样例 #1

### 输入

```
4
7
4
5
4 ```

### 输出

```
0.5 2.5
7.5 2.5
4.5 6.5
0.5 6.5 ```

# 题解

## 作者：Terrible (赞：7)

**注**：凸包就是凸多边形。

### 构造思路

找一个圆，在圆上逆时针取 $n$ 个点，使得相邻两个点距离等于给定边长，输出这 $n$ 个点坐标。

![印象图](https://s3.bmp.ovh/imgs/2023/07/22/df6442c72add3805.gif)

$\small\text{（印象图）}$

### 理论论述

_不想吃烤 mian() 包夹绿鸟可以不买，不想看证明可以跳过喵。_ [知乎上相关问题推荐](https://www.zhihu.com/question/35402071)

**定义** $\quad$ 如果一个多边形没有任何一个内角是优角（介于 $180^\circ$ 到 $360^\circ$ 的角），那么这个多边形是**凸多边形**。

**定义'** $\quad$ 一个多边形的每条边所在直线将平面划成两部分，如果多边形其它边均在其一侧，那么这个多边形是**凸多边形**。

**引理 1** $\quad$ 圆上找 $n$ 个点（$n\geqslant 3$）按逆时针序顺次相连 $n$ 次得到的图形是凸 $n$ 边形。

[证明 1]：圆上找任意三点从其一点开始按逆时针顺序连线两次后得到的夹角都严格小于 $180^\circ$，圆上找 $n$ 个点顺次相连 $n$ 次得到 $n$ 边形，它的 $n$ 个内角都严格小于 $180^\circ$，都不为平角或优角，故得到凸 $n$ 边形。

[证明 2]：圆上任意一个弦将圆分成两部分，$n$ 次相连得到的 $n$ 边形的边都是圆的弦，由于按照逆时针序顺次相连，所有顶点均在每个边上或其一侧，否则顶点相连顺序不满足逆时针序，进而可知对于每一条边其它边均在其一侧，因而得到的图形是凸 $n$ 边形。

**引理 2** $\quad$ 给定一个多边形，能够通过不改变这个多边形边长的形变使得其顶点共圆。

[证明 1]：归纳法：

1. 任意三角形都存在外接圆，[证明链接](https://zhuanlan.zhihu.com/p/83103092)；

2. 假设 $n$ 边形的情况成立（$n\geqslant 3$），取定任意一个 $n$ 边形 $P$，能够找到通过上述形变后顶点共圆的 $n$ 边形 $P'$，取定 $P'$ 上任一顶点记为 $A$，使 $P'$ 在 $A$ 处裂开，裂开后分别记裂口处两单侧端点为 $A_1,A_2$，将剩下的 $n-1$ 个顶点和 $A_1,A_2$ 两点固定到 $P'$ 对应的圆上，并扩张对应的圆，裂口两侧距离 $|A_1A_2|$ 随着 $R$ 的增加而连续增大，且易知 $0<|A_1A_2|<\boxed{\small{n\text{条边长总和}}}$，如果将 $|A_1A_2|$ 视作一条新的边，则它和其他 $n$ 条边一起构成一个顶点共圆的 $n+1$ 边形 $P''$，再由 $P$ 的任意性和 $|A_1A_2|$ 长度的任意性，可得构造出的 $P''$ 包含了 $n+1$ 边形的所有情况。

![证明附图](https://s3.bmp.ovh/imgs/2023/07/25/47758797fbb5deb0.gif)

$\small\text{（证明附图）}$

由数学归纳定理，对于任意多边形，都可以使其通过不改变边长的形变使得其顶点共圆。

[证明 2]：下面的**具体构造方法**中定理部分。

### 具体构造方法

首先**无解的条件**是这些边连一个多边形都构造不出来，最长的边比其他边加起来还长，总有一段接不上，或者它们至多构成一来一回的两端。即 `max>=sum-max`。

除此之外，其他情况就都存在解啦。因为能组成多边形就能贴到圆上，能贴到圆上的就是凸多边形。

那么我们的当务之急是找到这个圆，不妨把圆心放到坐标系圆点，求半径 $R$ 即可。我们可以先试试随便给一个 $R_0$，看看这个 $R_0$ 是不是我们要的，它是大了还是小了，进而二分答案来确定。

考虑各个镶嵌到圆上的多边形顶点可以用一个角度 $\alpha_i$ 来表示，因为确定了 $R$ 和 $\alpha_i$ 就确定了对应顶点位置 $(R\cos\alpha_i,R\sin\alpha_i),i=1,2,\cdots,n$，同时也方便逆时针输出点坐标。

![示意图](https://s3.bmp.ovh/imgs/2023/07/22/95fb693aeb741b29.png)

$\small\text{（示意图）}$

考虑如何得到 $\alpha_i$：我们现在知道边长，因而至多知道两个相邻角之差，这个相邻角的差怎么求呢？

![半弦—半角公式](https://s3.bmp.ovh/imgs/2023/07/22/f11c714e462b36d4.png)

$\small\text{（半弦—半角公式）}$

从上图可以得出半弦—半角转化公式：$R\sin\dfrac{\alpha}{2}=\dfrac{a}{2}$，容易反解出 $\alpha=2\arcsin\left(\dfrac{a}{2R}\right)$，但是有一个前提，就是弦的圆心角小于等于 $180^\circ$——因为 $\arcsin$ 只能解出来锐角或直角（$\leqslant 90^\circ$），这意味着我们需要分情况讨论。好在这里至多会出现一个平角或优角，聪明的你应该明白为什么至多只有一个吧！

![三种情况](https://s3.bmp.ovh/imgs/2023/07/22/f4e1dbd4df4d31f6.png)

$\small\text{（三种情况）}$

前两种情况可以统一处理，后一种情况需分开。

**定理** $\quad$ 设给定多边形边长依次为 $a_1,a_2,\cdots,a_n$，且 $a_{max}=\max\limits_{i=1}^n(a_i)$，能构成前两种情况的充要条件是 $\sum\limits_{i=1}^n2\arcsin\left(\dfrac{a_i}{a_{max}}\right)\geqslant 2\pi$，否则必然能构成第三种情况。

[直观理解]：

情况 2：直接意味着找到了 $R$。

![情况 1](https://s3.bmp.ovh/imgs/2023/07/25/75e20c22c19649e3.gif)

$\small\text{（情况 1）}$

情况 1：如果 $R$ 大了，就合不住口了；如果 $R$ 小了，就有交叉点了。

![情况 3](https://s3.bmp.ovh/imgs/2023/07/25/3d3824a663cade9d.gif)

$\small\text{（情况 3）}$

情况 3：如果 $R$ 小了，反而合不住口；如果 $R$ 大了，就有交叉点了。

[证明]：

充分性：

1. 当等号成立时，构成第二种情况。即以最长边为直径，各边对应的圆心角加和为 $2\pi$，正好绕圆一圈；
2. 当小于号成立时构成第一种情况。设 $f(R)=\sum\limits_{i=1}^n2\arcsin\left(\dfrac{a_i}{2R}\right),R\in\left[\dfrac{a_{max}}{2},+\infty\right)$，则 $R$ 取最小值时有 $f\left(\dfrac{a_{max}}{2}\right)>2\pi$，易知诸 $\arcsin\left(\dfrac{a_i}{2R}\right)$ 连续单调递减，因而整体连续单调递减，且 $\lim\limits_{R\to+\infty}\arcsin\left(\dfrac{a_i}{2R}\right)=0$，取 $R_0$ 使得诸 $2\arcsin\left(\dfrac{a_i}{2R_0}\right)<\dfrac{2\pi}{n}$，从而 $f(R_0)<2\pi$，根据[中值定理](https://baike.baidu.com/item/%E4%B8%AD%E5%80%BC%E5%AE%9A%E7%90%86/7167076)，必然存在一点 $R_\xi\in\left[\dfrac{a_{max}}{2},R_0\right]$，使得 $f(R_\xi)=2\pi$，从而各边绕圆整整一圈；

必要性：

3. 如果上述 $f\left(\dfrac{a_{max}}{2}\right)<2\pi$，根据单调递减性，不存在 $R_\xi$ 使得 $f(R_\xi)=2\pi$，不能绕圆一整圈；

下证 $\sum\limits_{i=1}^n2\arcsin\left(\dfrac{a_i}{a_{max}}\right)<2\pi$ 时必然能构成第三种情况：

4. 设 $g(R)=f(R)-2\arcsin\left(\dfrac{a_{max}}{2R}\right)+2\pi-2\arcsin\left(\dfrac{a_{max}}{2R}\right)$，即

$$g(R)=f(R)+2\pi-4\arcsin\left(\dfrac{a_{max}}{2R}\right),R\in\left[\dfrac{a_{max}}{2},+\infty\right)$$

$g(R)$ 表示最长边对应的相邻角之差取优角时的相邻角之差的总和，一个 $[0,\pi]$ 范围内的角 $\alpha$ 对应的优角为 $2\pi-\alpha$（也可不加 $2\pi$，和 $0$ 比较，将优角理解成负角）。反证优角对应的边一定是最长边：如果不是最长边，那么最长边一定比优角对应的边还接近圆心，从而顶点构造不满足逆时针序。不妨设 $a_n=a_{max}$，此时有 $a_i<a_n(i\neq n)$。

值得一提的是 $g(R)$ 在定义域内不具有单调性，但是这不妨碍我们二分，理由如下：

设辅助函数 $p(x)=\dfrac{x}{\sqrt{1-x^2}},q(x)=\dfrac{1}{x^2\left(\dfrac{1}{x^2}-1\right)^\frac{3}{2}}$。

对 $g(R)$ 求导得 $g'(R)=-\dfrac{2}{R}\left[\sum\limits_{i=1}^{n-1}p\left(\dfrac{a_i}{2R}\right)-p\left(\dfrac{a_n}{2R}\right)\right]$，

设 $\begin{cases}h_1(R)=\sum\limits_{i=1}^{n-1}p\left(\dfrac{a_i}{2R}\right)\\h_2(R)=p\left(\dfrac{a_n}{2R}\right)\end{cases}$，则 $\begin{cases}h_1'(R)=-\dfrac{1}{x}\sum\limits_{i=1}^{n-1}q\left(\dfrac{a_i}{2R}\right)\\h_2'(R)=-\dfrac{1}{x}q\left(\dfrac{a_n}{2R}\right)\end{cases}$，

记 $h(R)=\dfrac{h_1(R)}{h_2(R)}$，则 

$$\begin{aligned}
	h'(R)&=\dfrac{h_1'(R)h_2(R)-h_1(R)h_2'(R)}{h_2^2(R)}\\
	&=-\dfrac{1}{x}\dfrac{\sum\limits_{i=1}^{n-1}\left[q\left(\dfrac{a_i}{2R}\right)p\left(\dfrac{a_n}{2R}\right)-p\left(\dfrac{a_i}{2R}\right)q\left(\dfrac{a_n}{2R}\right)\right]}{h_2^2(R)}
\end{aligned}$$

两者辅助函数之比 $r(x)=\dfrac{q(x)}{p(x)}=\dfrac{1}{1-x^2}$ 在 $[0,1)$ 上单调递增，

由 $a_i<a_n$ 得 $r\left(\dfrac{a_i}{2R}\right)<r\left(\dfrac{a_n}{2R}\right)(i\neq n)$，即 $\dfrac{q\left(\dfrac{a_i}{2R}\right)}{p\left(\dfrac{a_i}{2R}\right)}<\dfrac{q\left(\dfrac{a_n}{2R}\right)}{p\left(\dfrac{a_n}{2R}\right)}$，从而 $h'(R)>0$，于是 $h(R)$ 是单增函数。$h(R)$ 的极限点：

$$\begin{aligned}
\lim\limits_{R\to\frac{a_n}{2}^+}h(R)&=\dfrac{C}{+\infty}=0,\;C\;\text{是正的常数}\\
p(R)&\sim R(R\to0)\\
\lim\limits_{R\to+\infty}h(R)&=\lim\limits_{R\to+\infty}\dfrac{\sum\limits_{i=1}^{n-1}\dfrac{a_i}{2R}}{\dfrac{a_n}{2R}}=\dfrac{\sum\limits_{i=1}^{n-1}a_i}{a_n}>1\end{aligned}$$

总结得出下表：

|$R$|$\text{极限点}\;\dfrac{a_n}{2}$|$\left(\dfrac{a_n}{2},R_1\right]$|$R_1$|$[R_1,+\infty)$| $\text{无穷极限点}\;+\infty$|
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
|$h(R)$|$0$|$\nearrow$|$1$|$\nearrow$|$\dfrac{\sum\limits_{i=1}^{n-1}a_i}{a_n}$|

![h(R) 总体样貌](https://s3.bmp.ovh/imgs/2023/07/25/025083848b48d820.png)

$\small{\text{（}h(R)\; \text{总体样貌）}}$

根据 $h(R)=\dfrac{h_1(R)}{h_2(R)},g'(R)=-\dfrac{2}{R}\left[h_1(R)-h_2(R)\right]$ 可知，

$0<h(R)<1$ 时，$g(R)$ 单调递增，此时 $R\in\left(\dfrac{a_n}{2},R_1\right]$；

$h(R)>1$ 时，$g(R)$ 单调递减，此时 $R\in\left[R_1,+\infty\right)$。

$g(R)$ 的极限点：$\lim\limits_{R\to+\infty}g(R)=2\pi$，设最高点是 $R_1$，易知 $g(R_1)>2\pi$，$g(R)$ 在 $\left[\dfrac{a_n}{2},R_1\right]$ 连续单调递增，根据[中值定理](https://baike.baidu.com/item/%E4%B8%AD%E5%80%BC%E5%AE%9A%E7%90%86/7167076)，存在一点 $R_\xi\in\left[\dfrac{a_n}{2},R_1\right]$ 使得 $g(R_\xi)=2\pi$，此时各边能正好绕圆一圈。

总结得出下表：

|$R$|$\dfrac{a_n}{2}$|$\left[\dfrac{a_n}{2},R_\xi\right]$|$R_\xi$|$\left[R_\xi,R_1\right]$|$R_1$|$[R_1,+\infty)$|$\text{无穷极限点}\;+\infty$|
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
|$g(R)$|$<2\pi$|$\nearrow$|$2\pi$|$\nearrow$|最高点|$\searrow$|$2\pi$|

![g(R) 总体样貌](https://s3.bmp.ovh/imgs/2023/07/25/77bcae6d2cb87818.png)

$\small{\text{（}g(R)\; \text{总体样貌）}}$

给定示性函数 $I(R)=[g(R)<2\pi]$，如果表达式为真，其值是 $1$；如果表达式为假，其值是 $0$。$I(R)$ 前半段是 $1$，后半段是 $0$，断点是 $R_\xi$，可以二分求解。

### 构造流程：

1. 判断是否能构成多边形，若 `max>=sum-max` 则输出 `NO SOLUTION` 并结束程序；

2. 不妨令 $a_n=a_{max}$（题目没有要求边长的顺序，可以直接排序或将最长边交换到最后。即便要求了边长的顺序，也可对边长序列进行一次轮换，将最长边调到最后）。

3. 判断构成的多边形是否通过圆心。若 $\sum\limits_{i=1}^n2\arcsin\left(\dfrac{a_i}{a_n}\right)\geqslant2\pi$，二分枚举单调递减函数

$$f(R)=\sum\limits_{i=1}^n2\arcsin\left(\dfrac{a_i}{2R}\right),R\in\left[\dfrac{a_n}{2},+\infty\right),$$

找到 $f(R_\xi)=2\pi$ 的解；

否则二分枚举单调不增示性函数 $I(R)=[g(R)<2\pi]$ 找到断点 $R=R_\xi$。其中

$$g(R)=\sum\limits_{i=1}^{n-1}2\arcsin\left(\dfrac{a_i}{2R}\right)+2\pi-2\arcsin\left(\dfrac{a_n}{2R}\right),R\in\left[\dfrac{a_n}{2},+\infty\right);$$

4. 令 $\alpha_i=\sum\limits_{j=1}^i2\arcsin\left(\dfrac{a_i}{2R}\right),i=1,2,\cdots,n$，若 $\sum\limits_{i=1}^n2\arcsin\left(\dfrac{a_i}{a_n}\right)<2\pi$，则覆盖定义 $\alpha_n=\alpha_{n-1}+2\pi-2\arcsin\left(\dfrac{a_n}{2R}\right)$；

5. 输出 $(R\cos\alpha_i,R\sin\alpha_i),i=1,2,\cdots,n$。

### 代码：

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
const double pi=acos(-1);
int a[1001],n;double alpha[1001];
double f(double R)
{
	for(int i=1;i<=n;i++)alpha[i]=alpha[i-1]+2*asin(a[i]/(2*R));
	return alpha[n];
}
int main()
{
	int sum=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i),sum+=a[i];
	std::sort(a+1,a+1+n);//题目对边长出现的顺序无要求
	//可以只将最大边放到最后，std::swap(a[n],*std::max_element(a+1,a+1+n));
	if(a[n]>=sum-a[n])return puts("NO SOLUTION"),0;//无解
	double l=a[n]/2.0,r=1e7,R;//半径至少等于半倍最长边，注意是 2.0
	if(f(a[n]/2.0)>=2*pi)//以最长边为直径是否能绕圆至少一圈
		while((r-l)/r>1e-10)
		{
			R=(l+r)/2;
			if(f(R)>2*pi)l=R;else r=R;
		}
	else
		while((r-l)/r>1e-10)
		{
			R=(l+r)/2;//多边形不过圆心，将最长边对应的圆周角换成对应优角
			f(R),alpha[n]=alpha[n-1]+2*pi-2*asin(a[n]/(2*R));
			if(alpha[n]<2*pi)l=R;else r=R;
		}
	for(int i=1;i<=n;i++)//有一个边的误差很大，取决于 R 的精度
		printf("%.10lf %.10lf\n",R*cos(alpha[i]),R*sin(alpha[i]));
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

# [Portal](https://www.luogu.com.cn/problem/P6711)

首先先说一下```NO SOLUTION```的充分必要条件：给出的边的长度中，最长的那一条的长度 $\geq$ 剩余所有边的长度之和。这是很显然的，因为三角形中两边之和必大于第三边，而任意多边形总可以形变成为一个三角形。

现在我们在判断无解后，就要尝试构造一组解。这里是我的构造方法：

1. 将所有边按照长度从大到小排序，并记 $dis_i$ 为排序后的结果，$sum_i$ 为排序后的**后缀和**。

2. 我们分别令 $P_0=(x_0,y_0),\dots,P_n=(x_{n-1},y_{n-1})$ 表示凸包上的点。并令第一个点为 $(0,0)$，第二个点为 $(dis_1,0)$。

3. 接下来，尝试将第 $2\sim(n-1)$ 条边加入凸包。当加入第 $i$ 条边时，它一定处于以 $P_{i-1}$ 为圆心，$dis_i$ 为半径的圆上。我们把这条边看作该圆上的一个向量，则该向量的倾角一定满足如下限制：

其倾角必严格大于 $\vec{v}=(x_{i-1}-x_{i-2},y_{i-1}-y_{i-2})$ 的倾角，并小于 $\vec{u}=(-x_{i-1},-y_{i-1})$ 的倾角。

具体可以看下图为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/4d2pcfig.png)

我的构造方式是希望 $P_i$ 到原点的距离尽量趋近于 $sum_{i+1}+\Delta$，其中 $\Delta$ 是一极小量，是为了使凸包上所有的边不共线。在正常使用中，我们取 $\Delta=10^{-6}\times(n-i-2)$。

那么如何让这一距离尽量趋近于上述值呢？二分向量倾角即可。注意到上图中注明了“不含边界”，故左右边界都加上一个 $\epsilon$，我取了 $10^{-10}$。

直接按照上述算法即可通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
const double eps=1e-10;
const double rem=1e-6;
int n;
double dis[1010],sum[1010];
double x[1010],y[1010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf",&dis[i]);
	sort(dis+1,dis+n+1),reverse(dis+1,dis+n+1);
	for(int i=n;i;i--)sum[i]=dis[i]+sum[i+1];
	if(sum[2]<=dis[1]){puts("NO SOLUTION");return 0;}
	x[0]=y[0]=0,x[1]=dis[1],y[1]=0;
	for(int i=2;i<n;i++){
		double l=atan2(y[i-1]-y[i-2],x[i-1]-x[i-2])+eps,r=atan2(-y[i-1],-x[i-1])-eps;
		if(r<l)r+=2*pi;
//		printf("%lf %lf\n",l,r);
		while(r-l>eps){
			double mid=(l+r)/2;
			double nx=x[i-1]+cos(mid)*dis[i],ny=y[i-1]+sin(mid)*dis[i];
//			printf("%lf:%lf,%lf\n",mid,sqrt(nx*nx+ny*ny),(sum[i+1]+rem*(n-i-1)));
			if(sqrt(nx*nx+ny*ny)>=(sum[i+1]+rem*(n-i-2)))l=mid;
			else r=mid;
		}
		x[i]=x[i-1]+cos(l)*dis[i],y[i]=y[i-1]+sin(l)*dis[i];
	}
	for(int i=0;i<n;i++)printf("%.14lf %.14lf\n",x[i],y[i]);
//	for(int i=1;i<n;i++)printf("%.14lf\n",sqrt((x[i]-x[i-1])*(x[i]-x[i-1])+(y[i]-y[i-1])*(y[i]-y[i-1])));printf("%.14lf\n",sqrt(x[n-1]*x[n-1]+y[n-1]*y[n-1]));
	return 0;
}
```


---

## 作者：白鲟 (赞：1)

归纳易证，任何能构成凸多边形的边长都可以构成三角形。题目要求直接转化为将原序列分为三段，要求拼接每段内的和可以形成一个三角形。

贪心地，要求第一段的和尽量靠近但不达到总和的一半，之后枚举第二段的位置即可判定答案。若不存在第一段要求的分界点，只能是第一个数即大于一半，这时显然无解；若不存在第二段要求的分界点，同理，只能是第二段内存在不小于总和一半的数。

注意题意疑似要求不能所有点共线。

```cpp
#include <cmath>
#include <cstdio>
const int maxn = 1000;
int n, pos1, pos2, a[maxn + 1], sum[maxn + 1];
struct Vector {
    double x, y;
    Vector operator*(double t) const {
        return {x * t, y * t};
    }
};
inline double get_cosine(double x, double y, double z) {
    return (x * x + y * y - z * z) / (2 * x * y);
}
Vector get_direction(double x, double y, double z) {
    double cos = get_cosine(x, y, z);
    return {cos, sqrt(1 - cos * cos)};
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i < n; ++i) {
        if (sum[i] * 2 < sum[n] && sum[i + 1] * 2 >= sum[n]) {
            pos1 = i;
            break;
        }
    }
    if (!pos1) {
        puts("NO SOLUTION");
        return 0;
    }
    for (int i = pos1 + 1; i < n; ++i) {
        if (sum[i] * 2 > sum[n] && (sum[i] - sum[pos1]) * 2 < sum[n]) {
            pos2 = i;
            break;
        }
    }
    if (!pos2) {
        puts("NO SOLUTION");
        return 0;
    }
    puts("0 0");
    for (int i = 1; i <= pos1; ++i) {
        printf("%d %d\n", sum[i], 0);
    }
    auto t1 = get_direction(sum[pos1], sum[pos2] - sum[pos1], sum[n] - sum[pos2]);
    for (int i = pos1 + 1; i <= pos2; ++i) {
        auto t = t1 * (sum[i] - sum[pos1]);
        printf("%lf %lf\n", sum[pos1] - t.x, t.y);
    }
    auto t2 = get_direction(sum[pos1], sum[n] - sum[pos2], sum[pos2] - sum[pos1]);
    for (int i = pos2 + 1; i < n; ++i) {
        auto t = t2 * (sum[n] - sum[i]);
        printf("%lf %lf\n", t.x, t.y);
    }
    return 0;
}
```

---

