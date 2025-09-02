# Area of Two Circles' Intersection

## 题目描述

You are given two circles. Find the area of their intersection.

## 样例 #1

### 输入

```
0 0 4
6 0 4
```

### 输出

```
7.25298806364175601379
```

## 样例 #2

### 输入

```
0 0 5
11 0 5
```

### 输出

```
0.00000000000000000000
```

# 题解

## 作者：TianTian2008 (赞：7)

这道题是纯粹的数学题，需要对解析几何、三角学有一定基础。

定义一些变量以表述方便，第一个圆的圆心为 $(x_1,y_1)$，半径为 $r_1$，第二个圆的圆心为 $(x_2,y_2)$，半径为 $r_2$，两圆圆心的距离为 $dis=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

两圆的位置关系会出现不同的情况，不同情况的面积交集也不同，因此需要分类讨论。

1、两圆外离

![CF600D-1](https://cdn.luogu.com.cn/upload/image_hosting/w4ct0swc.png)

此情况的充要条件是 $dis\geqslant r_1+r_2$。

显然，此情况交的面积为 $0$。

2、两圆内容

![CF600D-2](https://cdn.luogu.com.cn/upload/image_hosting/4iu38yre.png)

此情况的充要条件是 $dis\leqslant |r_1-r_2|$。

显然，此情况交的面积为 $\min(r_1,r_2)^2\pi$。

3、两圆相交

![CF600D-3](https://cdn.luogu.com.cn/upload/image_hosting/g8r260fv.png)

除前两种情况外剩余一种情况。

显然，此情况交的面积可以被看作两个弓形的面积和。

![CF600D-4](https://cdn.luogu.com.cn/upload/image_hosting/jxh5trcn.png)

而每个弓形又可以看作一个扇形和一个三角形的面积差。

![CF600D-5](https://cdn.luogu.com.cn/upload/image_hosting/lu65ehfc.png)

因此只需计算出该扇形的圆心角 $\theta$ 即可。

考虑该三角形

![CF600D-6](https://cdn.luogu.com.cn/upload/image_hosting/lwx6k1so.png)

三边长为 $r_1,r_2,dis$，根据余弦定理，有 $r_2^2=r_1^2+dis^2-2r_1dis\cos(\frac 12\theta)$，稍加变形得出 $\theta=2\arccos\frac{r_1^2+dis^2-r_2^2}{2r_1dis}$。

由此得出扇形的面积 $S_1=\frac \theta2r_1^2$（此处的 $\theta$ 为弧度）。

三角形的面积可以被分解成两个全等的直角三角形。

![CF600D7](https://cdn.luogu.com.cn/upload/image_hosting/yyxf51vh.png)

每个直角三角形的底为 $r_1\cos(\frac 12\theta)$，高为 $r_1\sin(\frac 12\theta)$，由此得出三角形的面积 $S_2=2\times\frac 12r_1\cos(\frac 12\theta)r_1\sin(\frac 12\theta)=r_1^2\cos(\frac 12\theta)\sin(\frac 12\theta)$。

$\because \sin(\alpha+\beta)=\sin(\alpha)\cos(\beta)+\cos(\alpha)\sin(\beta)$

$\therefore \sin(\theta)=2\sin(\frac 12\theta)\cos(\frac 12\theta)$

$\therefore \sin(\frac 12\theta)\cos(\frac 12\theta)=\frac 12\sin(\theta)$

$\therefore S_2=\frac 12r_1^2\sin(\theta)$

弓形的面积为 $S_1-S_2$。同理可得出另一弓形的面积。

到此，得出了此题的思路。

```
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>
using namespace std;
typedef long double ld;
ld xa,ya,ra,xb,yb,rb,pi,ans;
inline ld sq(ld x){return x*x;}
int main()
{
	pi=acos(-1);
	cin>>xa>>ya>>ra>>xb>>yb>>rb;
	ld dis=sqrt(sq(xa-xb)+sq(ya-yb));
	if(dis>=ra+rb) ans=0;
	else if(dis<=fabs(ra-rb)) ans=sq(min(ra,rb))*pi;
	else
	{
		ld aa=acos((sq(ra)+sq(dis)-sq(rb))/2/ra/dis)*2,ab=acos((sq(rb)+sq(dis)-sq(ra))/2/rb/dis)*2;//计算出两个圆心角
		ans=aa/2*sq(ra)-sq(ra)/2*sin(aa)+ab/2*sq(rb)-sq(rb)/2*sin(ab);
	}
	cout<<fixed<<setprecision(20)<<ans;
	return 0;
}
```


---

## 作者：UKBwyx (赞：3)

这里给出一个用**自适应辛普森法**的题解。  
但是这里不会讲自适应辛普森法，而是当做前置知识。  
主要讲的是这题的处理方法。

这题要求我们求两个圆的面积交，一看就是很能自适应辛普森积分的题。

辛普森法的关键是要**求出积分的函数 $f(x)$**。

首先我们可以求出两个圆分别在这一点的取值（即相交的长度）。

但是这还不够，我们需要的是两个圆的相交部分。

首先不难发现一个圆与直线的相交部分应该长这个样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/10esg8v0.png)
蓝色的是相交部分，由于圆是凸的，所以相交部分（与直线的）应该是一条线段。

那实际上在求出和两个圆相交的两条线段后，我们要求的就是两条线段的交。

也就是以下四种。

相交或包含：

![](https://cdn.luogu.com.cn/upload/image_hosting/9vbdzxm9.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/ptmqe5xr.png)

直接拿右端点较小的一个减左端点较大的一个就行了。

不交或不存在：

![](https://cdn.luogu.com.cn/upload/image_hosting/3mig00wh.png)

直接返回 $0$ 就可以了。

于是要积分的函数 $f(x)$ 就可以求出来了。

我们不妨去积分的范围为从 两个圆的较右的左端 到 较左的右端（因为如果只有一个的话一定没有交）。

但是要用自适应辛普森积分还是有个问题，就是如果没有值就直接返回了但是实际上交得很偏。

于是我们把它转化成两个圆心的 $x$ 坐标都等于 $0$ 的圆就行了（这样是一定没有空白的）。

这里贴上代码。
```
#include<bits/stdc++.h>
#define pii pair<long long,long long>
#define mp make_pair
#define pb push_back
using namespace std;
__float128 lim1=1e-6;//精度
__float128 ans=0;
__float128 lim=1;
struct circle {
	__float128 x,y,r;//这里不能用 double 存
	void rd() {
		long long t1,t2,t3;
		cin>>t1>>t2>>t3;
		x=t1;
		y=t2;
		r=t3;
	}
};
circle a,b;
__float128 f1(__float128 x) {
	__float128 qwq1=a.r*a.r-(a.x-x)*(a.x-x),qwq2=b.r*b.r-(b.x-x)*(b.x-x);
	__float128 dis1=0,dis2=0;
	if(qwq1>0)dis1=sqrtl(qwq1);
	else return 0;
	if(qwq2>0)dis2=sqrtl(qwq2);
	else return 0;
	__float128 l1=a.y-dis1,r1=a.y+dis1,l2=b.y-dis2,r2=b.y+dis2;//相交的左右端点
	if(l2<l1)swap(l1,l2),swap(r1,r2);//为了方便判断是否相交
	if(r1>=l2) {
		return r1+r2-l2-max(r2,r1);
	}
	return 0;
}
inline __float128 cnt(__float128 l,__float128 r) {//辛普森法
	__float128 mid=(l+r)*0.5;
	return (r-l)*(f1(l)+4*f1(mid)+f1(r))/6;
}
void f(__float128 l,__float128 r,int dep,__float128 v1) {//自适应
	__float128 mid=(r+l)*0.5;
	__float128 l1=cnt(l,mid),r1=cnt(mid,r);
	__float128 del=r1+l1-v1;
	if(dep>=10&&(-lim1<del&&del<lim1||-lim*(ans+v1)<del
	             &&del<lim*(ans+v1))) {//相对精度不超过1e-6也行，不加这个跑800ms,加了跑70ms
		ans+=l1+r1;
		return;
	} else {
		f(l,mid,dep+1,l1);
		f(mid,r,dep+1,r1);
	}
}
int main() {
	a.rd();
	b.rd();
	__float128 dis=sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	a.x=0;
	a.y=0;
	b.y=0;
	b.x=dis;//旋转（其实还把第一个圆的圆心转成了（0,0））
	if((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)>=(a.r+b.r)*(a.r+b.r)) {//防止 l>r
		cout<<0;
		return 0;
	}
	f(max(a.x-a.r,b.x-b.r),min(a.x+a.r,b.x+b.r),0,cnt(max(a.x-a.r,b.x-b.r),min(a.x+a.r,b.x+b.r)));
	printf("%.12f",(double)ans);
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：2)

## CF600D Area of Two Circles' Intersection
纯数学题。
### Solution
记 $D=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

讨论：
- 两圆外离（切），如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/9b6pmkiy.png)

此时易得 $S=0$。

此情况的充要条件是 $r_1+r_2 \le D$。
- 两圆内含（切），如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/8wubzdg3.png)

此时 $S=\min(r_1,r_2)^2\pi$。

此情况的充要条件是 $|r_1-r_2| \ge D$。
- 最复杂的情况，两圆相交，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/qkbtvd9z.png)
此时 $S$ 就等于红色部分（两个弓形）面积。图中 $OA=r_1,O'A=r_2,OO'=D$。

显然，两个弓形的求法是相同的。

因此我们就 $\triangle OAB$ 包含的弓形进行计算：

可以看出弓形的面积等于 $\angle AOB$ 对应的扇形面积减去三角形 $OAB$ 的面积。记 $\angle AOB$ 为 $\theta$，则有：
$$S_弓=\cfrac{\theta}{2\pi} \cdot r_1^2-\cfrac{1}{2}\cdot r_1^2 \sin \theta=\cfrac{1}{2}\ r_1^2(\theta-\sin \theta)$$

所以只要求出 $\theta$，此题就可以解决。

记另一个圆心为 $O'$，则根据余弦定理得：

$$r_2^2=r_1^2+OO'^2-2\ r_1 \cdot OO'\cos \cfrac{\theta}{2}$$

整理、变换得：
$$\theta=2 \arccos \cfrac{r_1^2-r_2^2+D^2}{2\ r_1 D}$$

至此，分析完成。

### [AC](https://codeforces.com/contest/600/submission/302582497) Code
```cpp
#include<iostream>
#include<cmath>
using namespace std;
long double PI = acos(-1.0),D,x1,x2,y1,y2,r1,r2,theta1,theta2,res;
int main(){
	scanf("%Lf%Lf%Lf%Lf%Lf%Lf",&x1,&y1,&r1,&x2,&y2,&r2);
	D=sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
	if( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) >= r1*r1 + r2*r2 + 2 * r1 * r2 ) res = 0 ;
	else if( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= (r1-r2)*(r1-r2) ) res = min(r1,r2)*min(r1,r2) * PI ;
	else{
		theta1 = acos( ( r1*r1 - r2*r2 + (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) / ( 2 * r1 * D ) ) * 2 , theta2 = acos( ( r2*r2 - r1*r1 + (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ) / ( 2 * r2 * D ) ) * 2 ;
		res= (r1*r1) * ( theta1 - sin(theta1) ) / 2  + (r2*r2) * ( theta2 - sin(theta2) ) / 2 ;
	}
	printf("%.25Lf\n",res);
	return 0;
}
```
**注意：一定要开 `long double`！**

---

## 作者：zhicheng (赞：1)

### 题意简述

给出两个圆的圆心和半径，求两个圆的面积交。

### 思路

首先通过两圆半径和圆心的距离判断两圆是相离，包含还是相交。相离面积交为 $0$，包含答案即为较小的圆的面积。当包含时相当于求两个弓形的面积。（见下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/ux4qj18a.png)

由正弦定理有：

$$
\begin{aligned}

S_{\text{弓}ACD}&=S_{\text{扇}ACD}-S_{\Delta ACD}\\
&=\pi r_1^2\times\dfrac{\angle CAD}{2\pi}-\dfrac{1}{2}r_1^2\sin\angle CAD\\
\end{aligned}
$$

其中：

$$
\angle CAD=2\angle CAB
$$

由余弦定理：

$$
\angle CAB=\arccos\left(\dfrac{r_1^2+dis^2-r_2^2}{2r_1\times dis}\right)
$$

$S_{\text{弓}B CD}$ 同理。然后就完了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long double pi=3.14159265358979323846264338;
int main(){
	long double a,b,c,d,r1,r2,dis,deg,ans;
	scanf("%Lf%Lf%Lf%Lf%Lf%Lf",&a,&b,&r1,&c,&d,&r2);
	dis=sqrt((a-c)*(a-c)+(b-d)*(b-d));
	if(r1+r2<=dis){
		printf("0");//相离
		return 0;
	}
	if(fabs(r1-r2)>=dis){
		printf("%.7Lf",min(r1,r2)*min(r1,r2)*pi);//包含
		return 0;
	}
	deg=2*acos((r1*r1+dis*dis-r2*r2)/(2*r1*dis));//弓形
	ans=r1*r1*(deg/2-sin(deg)/2);
	deg=2*acos((r2*r2+dis*dis-r1*r1)/(2*r2*dis));
	ans+=r2*r2*(deg/2-sin(deg)/2);
	printf("%.7Lf",ans);
}
```

---

## 作者：Eltaos_xingyu (赞：1)

## 题目描述

分别给出两个圆的圆心坐标和半径，求两个圆相交部分的面积。

## 分析

前置知识：余弦定理，正弦定理，反三角函数。

我当时还以为这是多圆相交的题，于是直接把这道题放到了自适应辛普森的题单里，今天一做，啊？这不是一道裸的数学题吗？

分 $3$ 种情况：

### 两圆外离

![](https://cdn.luogu.com.cn/upload/image_hosting/yr7tqe5o.png)

运用小学知识，我们可以知道两圆外离的条件是 $dis \geq r_1+r_2$，其中 $dis$ 指两圆心的距离。

可以很明显发现此时两圆相交面积一定是 $0$ 的。

### 两圆内含

![](https://cdn.luogu.com.cn/upload/image_hosting/z5pg11qx.png)

~~（好吓人）~~

再次运用小学知识，我们可以知道两圆内含的条件是 $dis \leq \lvert r_1-r_2\rvert$。

也可以很明显的发现此时两圆的相交面积就是小圆的面积，即 $S=\min(r_1,r_2)^2\pi$。

### 两圆相交

![](https://cdn.luogu.com.cn/upload/image_hosting/6oi7d6rb.png)

~~（这个图如果截小了我自己都看不清）~~

...不是那么容易出答案对吧？

我们运用初中的知识，把这个不规则图形化为求两个弓形的面积：

![](https://cdn.luogu.com.cn/upload/image_hosting/iwlat02i.png)

下面有两个思路：

方法一：

先用余弦定理和反三角函数算出两圆心角一半的度数，然后用正弦定理算筝形的面积，最后用两个扇形的面积减去筝形的面积即可（如图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/2vmou551.png)

~~（蓝加红等于紫）~~

蓝色与紫色面积之和乘 $2$ 即为筝形面积，用两个扇形面积减掉即可。

......

然后你会发现用这个方法 WA 掉了（至少我是这样）。原因似乎是有些数据非常坑，算出圆心角极小，这个时候用这种方法的时候误差极大，所以不能过掉这道题。

方法二：

直接是初中常用求弓形面积方法：扇形面积减去三角形面积。当然，求圆心角的步骤和方法一是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/roejood1.png)

扇形面积减蓝紫部分即可，仍然需要用到正弦定理，记得要算两遍！

然后因为这种方法相对于方法一来讲角度误差会小一点，使得如果半径或两圆距离极大的时候，角度的误差仍控制在正常范围内。

超短但巨丑的 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	long double x_1,x_2,y_1,y_2,r1,r2;
	cin>>x_1>>y_1>>r1>>x_2>>y_2>>r2;
	long double dis=sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2));
	if(dis>=r1+r2)cout<<"0.00000000000000000000";
	else if(dis<=abs(r1-r2))cout<<fixed<<setprecision(6)<<min(r1,r2)*min(r1,r2)*acos(-1);
	else{
		long double alpha1=acos((r2*r2+dis*dis-r1*r1)/(2*r2*dis))*2;
		long double alpha2=acos((r1*r1+dis*dis-r2*r2)/(2*r1*dis))*2;
		long double S=r2*r2*sin(alpha1)/2+r1*r1*sin(alpha2)/2;
		long double S1=alpha1*r2*r2/2,S2=alpha2*r1*r1/2;
		cout<<fixed<<setprecision(6)<<S1+S2-S; 
	}
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：0)

# [CF600D](https://codeforces.com/contest/600/problem/D)

Upd on 2023/11/02：修复一些小 bug。

## 题意

给出两个圆的圆心 $(x_1,y_1),(x_2,y_2)$ 及半径 $r_1,r_2$，求两圆相交部分面积。

数据范围：$|x_i|,|y_i|,|r_i|\le10^9$。

## 题解

计算几何板子。但是这里还是推一下吧~~其实是我不会计几~~。**本题解全文使用弧度制。**

前置知识：中学几何知识，三角函数，弧度制，~~C++ 语言~~。

![](https://cdn.luogu.com.cn/upload/image_hosting/etivlu36.png)

首先计算出两圆圆心距离 $d=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}$。

- 如果 $d\ge r_1+r_2$，则两圆外离（或外切），答案直接就是 $0$。

- 如果 $d\le|r_1-r_2|$，则两圆内含（或内切），答案为 $\pi\min(r_1,r_2)^2$。

- 否则两圆相交。

考虑计算出交点弦一侧（弓形）的面积，如图紫色部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/d3ff4eqx.png)

根据初高中的数学知识有（其中 $\alpha$ 是圆心角，用弧度表示）：

$$S_{\text{弓}}=S_{\text{扇}}-S_{\triangle},$$

$$S_{\text{扇}}=\dfrac\alpha{2\pi}\cdot\pi r_1^2=\dfrac\alpha2 r_1^2,$$

$$S_{\triangle}=\dfrac12r_1\cdot r_1\cdot\sin\alpha=\dfrac12r_1^2\sin\alpha.$$

所以只需求出 $\alpha$ 即可。

注意下图中的阴影三角形：

![](https://cdn.luogu.com.cn/upload/image_hosting/vf9sthbg.png)

根据余弦定理，有：

$$r_2^2=r_1^2+d^2-2\cdot r_1\cdot d\cos\frac{\alpha}2,$$

即

$$\alpha=2\arccos\frac{r_1^2+d^2-r_2^2}{2\cdot r_1\cdot d}.$$

求出来 $\alpha$ 啦。所以这部分的面积就能算了。

$$S_{\text{弓}}=\frac12r_1^2(\alpha-\sin\alpha)$$

同理，另一边的弓形面积也可计算。

于是这个面积就求完了。

时间复杂度 $\Theta(1)$。

## Code

对着式子敲就行了。不放了。

**本题需要开 $\texttt{long double}$**，不然会被卡精度。这里放个对比：[$\texttt{long double}$](https://codeforces.com/contest/600/submission/230644132)，[$\texttt{double}$](https://codeforces.com/contest/600/submission/230645016)。

---

## 作者：XL4453 (赞：0)

~~初三蒟蒻什么都不会爪巴了。~~

------------
### 题目分析：

先给个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/t17ruqsv.png)

首先已知两个圆心的坐标，分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$，那么可以求出两点间的距离：$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

还知道圆心到圆上任意一点的距离分别为：$r_1$ 和 $r_2$，也就是 $OA=OB=r_1$，$O'A=O'B=r_2$。

根据余弦定理，有：$\overline{O'A}^2=\overline{OA}^2+\overline{O'O}^2-2\times\overline{OA}\times\overline{O'O}\cos\angle AOO'$

变形，立刻有：$\cos\angle AOO'=\dfrac{\overline{OA}^2+\overline{O'O}^2-\overline{O'A}^2}{2\times\overline{OA}\times\overline{O'O}}$

根据 $\angle AOO'=arccos(cos(\angle AOO'))$ 得出 $\angle AOO'$ 的度数，然后乘以二得到 $\angle AOB$ 的度数，然后用扇形面积公式 $\dfrac{\angle AOO' \times r_1^2}{2}$求出整个扇形面积。

再利用求得角度的一半算出 $\sin \angle AOO'$，然后乘以 $r_1$，得到 $\overline {AC}$ 的长度，乘以 $2$ 得到 $\overline {AB}$ 的长度。

求出三角形面积，用扇形面积减去三角形面积，得出右半部分的面积。

最后对于左半边再求一次，就能得到面积了。

------------
顺便提供一组检验程序对错的数据：
输入：

	0 0 6
	5 0 3

输出（大致）：

	18.574316314768083
这组数据中有小圆圆心在大圆中间，如果程序中没有用三角函数求，而是用了海伦公式或在求正弦时用了 $\sin^2 a+cos^2 a=1$ 来求却没有考虑到三角函数正负，则会报错。

这是由于上述两种方法没有考虑到三角形的面积可以是“负”的，也就是应当是扇形面积加上三角形面积求出一半的面积。

------------
### 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long double xa,xb,ya,yb,ra,rb,dis,S1,S2,S3,cos_1,cos_2;
int xa_,xb_,ya_,yb_,ra_,rb_;
long double calc_cos(long double a,long double b,long double c){//利用余弦定理算cos 
	return (a*a+b*b-c*c)/(2*a*b);
}
long double work_deg(long double cosx){//根据cos算角度 
	return acos(cosx);
}
long double work_half(long double r,long double deg){//算一半的面积 
	long double sinx=sin(deg);
	return r*r*(deg-sin(deg))/2;
}
long double work(){//提供参数 
	long double cosx=calc_cos(ra,dis,rb);
	long double deg=work_deg(cosx)*2;
	return work_half(ra,deg);
}
void calc(){
	S1=work();
	swap(xa,xb);swap(ya,yb);swap(ra,rb);//交换一下再求，这样就不用动参数了 
	S2=work();
	S3=S1+S2;
	printf("%.20lf",(double)S3);
}
int main(){
	scanf("%d%d%d%d%d%d",&xa_,&ya_,&ra_,&xb_,&yb_,&rb_);
	xa=xa_;xb=xb_;ya=ya_;yb=yb_;ra=ra_;rb=rb_;
	dis=sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
	if(ra+rb<=dis)printf("0.00000000000000000000");
	else
	if(abs(ra-rb)>=dis)printf("%.20lf",min((double)ra,(double)rb)*min((double)ra,(double)rb)*atan2(0,-1));
	else
	calc();
	return 0;
}
```


---

## 作者：cold_cold (赞：0)

 [安利一波博客](https://www.cnblogs.com/cold-cold/p/10082426.html)

两个圆的关系，可分为三种情况，相离，相交，包含

1.相离或边缘重合，输出0即可

2.包含的话输出小圆的面积即可

3.相交的话

![](https://img2018.cnblogs.com/blog/1539484/201812/1539484-20181207132903783-474794836.png)


如上图，总面积等于SACC1=S扇形DCC1A-SΔDCC1A

所以我们用余弦定理求出∠D即可求出总面积

计算时要用long double

实现如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const ld pai=atan2(0,-1);
ld suan(ld a,ld c,ld b)
{
    ld jiao=acos((a*a+b*b-c*c)/a/b/2)*2;
    return a*a*(jiao-sin(jiao))/2;
}
int main()
{
//    freopen("input","r",stdin);
//    freopen("output","w",stdout);
    ld x1,y1,x2,y2,r1,r2,dis;
    x1=read(),y1=read(),r1=read();
    x2=read(),y2=read(),r2=read();
    if(r1>r2) swap(x1,x2),swap(y1,y2),swap(r1,r2);
    dis=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if(r1+r2<=dis) printf("0.00000000000000000000");
    else if(r1+dis<=r2) printf("%.20lf",(double)(r1*r1*pai));
    else printf("%.20lf",(double)(suan(r1,r2,dis)+suan(r2,r1,dis)));
    return 0;
}
```

---

