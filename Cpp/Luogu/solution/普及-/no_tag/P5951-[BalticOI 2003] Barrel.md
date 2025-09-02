# [BalticOI 2003] Barrel

## 题目背景

大水池子。


## 题目描述

给定一个水池的底面积 $S$ 和高 $H$。

现在其中有体积为 $V$ 的水量，放入 $n$ 个立方体，给出每个立方体的棱长和密度，请你求出水池中水池的高度。

注：此处我们忽视空气的任何作用力， 认为正方体之间互不接触且不会在水中旋转， 且认为水的密度为 $1$。

## 说明/提示

对于 $100\%$ 的数据，$1\le S,H,V\le10000$，$1\le n\le 1000$。

## 样例 #1

### 输入

```
100 10 500
1
1 0.5```

### 输出

```
5.0050000```

# 题解

## 作者：_Haoomff_ (赞：6)

物理 $+$ 数学题。
## - 物理部分
根据[浮力](https://baike.baidu.com/item/%E6%B5%AE%E5%8A%9B/1535715?fr=aladdin)可以发现一个坑点：密度小的物体会浮在水面上，所以我们在做的时候要根据密度来判断物体是否完全浸入水中。
## - 数学部分
学过 $6$ 年级的同学都知道求长方体、正方体、圆柱的体积计算公式：
$$V=Sh$$
根据上面这个公式可以求出逆定理：
$$S=\frac{V}{h}$$
$$h=\frac{V}{S}$$
在这里，我们需要用到第二个逆定理：根据输入的 $S$ 和 $V$，我们可以求出水的高度是多少，也就是 $\frac{V}{S}$。

然后，就是根据密度判断物体是否完全浸入水中，算出浸入水中部分的体积，用沉入水中部分的体积除以底面积得到沉入水中的部分使得水面上升了多少。

最后把每次算出的上升的高度累加起来并加上原始水的高度即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int s,h,v,n;
double ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>s>>h>>v>>n;
	ans=1.0*v/s;//原始水面高度 
	for(;n--;){
		double lc,md;
		cin>>lc>>md;
		if(md>=1)ans+=lc*lc*lc/s;//完全浸入水中 
		else ans+=lc*lc*lc*md/s;//不完全浸入水中 
		if(ans>=h){//有溢出的水 
			cout<<h;//因为已经有溢出的水，所以无论如何都是满的，直接输出水池的高 
			return 0;
		}
	}
	printf("%.7lf",ans);
	return 0;
}
```


---

## 作者：no2lxs (赞：1)

## Part 1

初中生都熟悉这题，这是[浮力](https://baike.baidu.com/item/%E6%B5%AE%E5%8A%9B/1535715?fr=aladdin)中的基本运算;


但是这里有一个坑点，就是密度比水小的物体会浮在水面上，导致物体不能完全浸入，所以我们在算的时候应该判定是否全部浸入。

本题运算基本公式:
浸入体积等于重力除以密度乘重力的比例系数。

## Part 2 

 _**Code**_ 
 ```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>//sort函数库 
#include<cstdlib>
#include<cstring>
#include<bits/stdc++.h>
#include<map>
#define gets(S) fgets(S,sizeof(S),stdin)
#pragma optimize GCC(2)
using namespace std;
int s,h,v,n;
double len,rou;
int main()
{
	cin>>s>>h>>v>>n;
	double hf=1.0*v/s;//1.0是为了转换为浮点数
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&len,&rou);
		if(rou>=1)//判断是否浸入
		{
			hf+=(len*len*len)/s;
		}
		else
		{
			hf+=(len*len*len*rou)/s;
		} 
		if(hf>=h)//如果超出范围则直接输出
		{
			printf("%d",h);
			return 0;
		}
	}
	printf("%.7f",hf);
		return 0;
} 
```


---

## 作者：panyanppyy (赞：1)

写题解是因为另一篇有误。
## Problem
有个水缸，里面东西都不会碰撞，放入 $n$ 个立方体，给出每个立方体的棱长 $l_i$ 和密度 $\rho_i$，求最后缸中水的**高度**。
## Solution
显然，这是一道初中物理题。

对物体分类讨论：

1. $\rho_i\ge1$ 时，物体沉入水底，水面高度增加 $\dfrac{l_i^3}{s}$。

2. $\rho_i<1$ 时，物体浮起，设物体排开水的体积为 $V_\texttt排$。

	$\because F_\texttt浮=\rho_\texttt水\cdot g\cdot V_\texttt{排}$

	又 $\because F_\texttt{浮}=G=l_i^3\cdot\rho_i\cdot g$

	$\therefore V_\texttt{排}=\dfrac{l_i^3\cdot\rho_i}{\rho_\texttt{水}}$

	$\therefore$ 水面上升 $\dfrac{V_\texttt{排}}{s}$

**小剪枝**：当高度超过 $h$ 时可以直接输出高度 $h$。（另一篇题解写成了体积）

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
double ans,l,p;
int n,s,h,v;
int main(){
	scanf("%d%d%d%d",&s,&h,&v,&n),ans=1.*v/s;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&l,&p);
		if(p>=1)ans+=l*l*l/s;
		else ans+=l*l*l*p/s;
		if(ans>=h)return printf("%d",h),0;
	}
	printf("%.7f",ans);
	return 0;
}
```

---

## 作者：wishapig (赞：1)

远古BOI系列。。。

初中物理题（大雾）

设当前方块棱长为$a$，密度为$\rho_a$

- 当$\rho_a\ge1$时，整个方块都沉到水里去了，这个方块占用了$a^3$的体积，所以液面会上升$\dfrac{a^3}{S}$

- 当$\rho_a<1$时，方块是浮在水面上的，根据受力平衡的知识（设方块体积为$V_a$，排开水的体积为$V_a'$）：

$$
\begin{aligned}
F_{\uparrow}&=G_a \cr
\rho_{water}gV'_a&=\rho_a gV_a \cr
gV'_a&=\rho_a ga^3 \cr
V'_a&=\rho_a a^3
\end{aligned}
$$

所以液面会上升$\dfrac{V_a'}{S}=\dfrac{\rho_a a^3}{S}$

其实就是液面上升$\dfrac{\min(\rho_a,1) a^3}{S}$

还有一个细节就是水是会溢出来的

```c++
#include<bits/stdc++.h>
using namespace std;
double s,h,v,d,rou,a;
int x,y,z,n;
int main(){
	scanf("%d%d%d",&x,&y,&z); s=x,h=y,v=z;
	scanf("%d",&n); d=v/s;
	for (int i=1; i<=n; i++){
		scanf("%lf%lf",&a,&rou);
		rou=min(rou,1.0);
		d+=a*a*a*rou/s;
		if (d>=h){ printf("%.10lf\n",v); return 0; }
	}
	printf("%.10lf\n",d);
	return 0;
}
```

---

## 作者：ZYH_juruo (赞：0)

# 题目传送门
[P5951 [BOI2003] Barrel](https://www.luogu.com.cn/problem/P5951)
# 题目大意
在一个给出底面积为 $S$，高为 $H$，装有体积为 $V$ 的水池中，放入放入 $n$ 个立方体，给出每个立方体的棱长和密度，求出现在水池的高度。
# 题目分析
这是一道物理题，~~我默认读者都会初二的浮力~~。但还是讲一下吧。

当物体密度小于水的密度时，物体漂浮，上浮的高度就为它的质量除以容器底面积。
当物体密度大于水的密度时，物体沉底，上浮的高度就是体积除以容器底面积。

浮力讲完了，再讲讲体积，质量。质量等于密度乘体积，体积等于棱长的三次方。

还有一个要注意的点是，当水的高度超过容器高度时，要特判，直接输入容器高度即可。
# ACCODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,h,v;
double ans,l,p;
int main(){
	cin>>s>>h>>v>>n;
	ans=1.0*v/s;
	for(int i=1;i<=n;i++){
		cin>>l>>p;
		if(p<1)ans+=l*l*l*p/s;
		else ans+=l*l*l/s;
	}
	if(ans>=h)
	    printf("%d",h);
	else
		printf("%.7f",ans);
	return 0;
}
```
**完结撒花！！！**

---

## 作者：xibaohe (赞：0)

# 题目大意
有一个大水池，往里面放一些立方体，求放入立方体后的水面高度。

# 题目思路
将情况进行分类讨论，分为以下几种情况：

- 物体不浮起

- 物体浮起

- 有水溢出

# 分类讨论
1. 当物体不浮起时，加上其密度即可。

2. 当物体浮起时，加上其入水体积。

3. 当有水溢出时，直接结束循环。

# 知识储备

- 当物体密度小于液体密度时，物体漂浮。

- 当物体密度等于液体密度时，物体悬浮。（这种情况基乎全部题解都表述错误或没说清楚。）

- 当物体密度大于液体密度时，物体沉底。

# 满分代码
加上了详细的代码注释。
```cpp
#include<iostream>
using namespace std;

int S,H,V;//S,H,V,n意思如题目
int n;
double a,ruo;//a为棱长,ruo是密度在课本中读音的谐音

int main()
{
	cin>>S>>H>>V;
	cin>>n;
	double h=1.0*V/S;//计算初始情况
	while(n--)
	{
		cin>>a>>ruo;
		double v=a*a*a;//v用来表示物体体积
		if(ruo>1)//沉底
		{
		    h+=v/S;
		}
		if(ruo==1)//悬浮
		{
		    h+=v/S;
		}
		if(ruo<1)//沉底
		{
		    h+=v*ruo/S;
		}
		if(h>=H)//溢水
		{
			cout<<H<<endl;//输出
			break;//结束循环
		}
	}
	printf("%.7lf",h);
	return 0;
}
```


---

## 作者：zhczcg314 (赞：0)

# P5951题解

### [题目传送门](https://www.luogu.com.cn/problem/P5951)

这道题无非就是初二下物理浮力一章的基础题，拿到计算机上就更好做了。

我们需要考虑的就是：

第一点：物体的浮沉条件，物体密度与液体密度的关系（`p` 代表排开的液体，`w` 代表物体）

- 在物体密度小于液体密度时，物体会漂浮，这样一来 $V_p = \dfrac{\rho_w}{\rho_p}\times V_w$。
- 在物体密度等于液体密度时，物体会悬浮，这样一来 $V_p = V_w$。
- 在物体密度大于液体密度时，物体会沉底，这样一来也是 $V_p = V_w$。

第二点：液面升高的高度怎么算

- $h = \dfrac{V_p}{S}$。

代码如下：

```cpp
//P5951(请忽略丑陋的rou)
#include <iostream>
#include <iomanip>

using namespace std;

int S, H, V, n;
double a, rou;

int main(){
    cin >> S >> H >> V;
    double now_h = V * 1.0 / S;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a >> rou;
        //如果物体密度小于液体密度，v排 = rou物 / rou液 * v物
        if(rou < 1) now_h += a * a * a * rou / S;
        //如果物体密度大于等于液体密度，v排 = v物
        else now_h += a * a * a / S;
    }
    cout << fixed << setprecision(7) << now_h << endl;
    return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

如果你上过初二科学课的话，你一定会知道：物体排开水的体积 $\times$ 水的密度 $=$ 物体的质量。

- 物体密度比水大时，排开水的体积等于物体体积。

- 物体密度比水小时，排开水的体积等于物体质量 $\div$ 水的密度。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int s,h,v,n;
double hnow,a,b;
int main(){
	scanf("%d%d%d",&s,&h,&v);
	double hnow=v*1.0/s;
	scanf("%d",&n);
	while(n--){
		scanf("%lf%lf",&a,&b);
		if(b>=1)hnow+=a*a*a/s;
		else hnow+=a*a*a*b/s;
	}
	printf("%.7lf",min(h*1.0,hnow));
	return 0;
}
```

---

