# 〈 TREEのOI 2022 Spring 〉Dimension-2 Square

## 题目背景

# 本题可能轻微卡精度，建议改用 $\tt long\ double$


正月十五夜空中。

一行人望着一棵树，一棵飘在天上的树，期待着它变成一个环。

这棵树有 $4$ 个节点。  

“它变成环了！”有人大喊。  
我顿时向天上望去……  

多么标准的正方形啊！无论哪个天文学家过来测量，它的角都是标准的 $90^{\circ}$，它的边都是完美的 $1:1:1:1$……  

只见那棵树，不，那标致而又完美的环，缓缓飞过，恰巧嵌在了那轮明月中心……

![](https://cdn.pixabay.com/photo/2016/11/29/13/14/full-moon-1869760_960_720.jpg)

## 题目描述

给定平面直角坐标系上 $4$ 个点的坐标。

你需要使用 ~~%法~~ 魔法，做一个正方形，使得这 $4$ 个点分别在正方形每条边的**直线**上。

## 说明/提示

**本题采用 $\tt SPJ$。**

如答案不唯一，输出一种即可。   
四边长度的之差 $\le 10^{-2}$ 且相邻两边夹角在 $\frac{\pi}{2}\pm10^{-2}$ 内且设给定的点为 $(p,q)$，则存在一点 $(p,q+k)\ (|k|\leq1)$ 在对应边所在直线上即可 $\tt \green {AC}$。

对于 $30\%$ 的数据，$T=1,|x_i|,|y_i|\le10^3$。

对于 $70\%$ 的数据，$1\leq T\leq 5\times 10^4,|x_i|,|y_i|\le10^6$。

对于 $100\%$ 的数据，$1\leq T\leq 5\times 10^5,|x_i|,|y_i|\le10^9$。

数据保证任意两点连成的 $6$ 直线两两之间互不垂直，且没有平行于轴的直线，任意三点不共线。保证不存在一组解的边与轴平行。保证有解。

**为了数据的精确性，您输出时至少需要保留 $8$ 位小数。**

## 样例 #1

### 输入

```
1
235 423
544 345
563 645
453 435```

### 输出

```
380.43769007 531.90429895
395.56394564 543.23089701
406.89054360 528.10464158
391.76428803 516.77804352```

# 题解

## 作者：tegethim (赞：4)

**这道题快算哭我了。**
## 凡几何题先画图
看到两个 dalao 的题解，没有看懂和代码有甚么关系，但就是看起来狠厉害的样子，但还是没看懂，我只能是讲我自己的想法了

首先，对于四个毫无关系的点，我们会确定一个正方形使得每个点都**分别**出现在这个正方形的四边所在直线上（加粗是因为一开始没看到，然后分类讨论了好久/(ㄒoㄒ)/）。

那么正方形上每个点都一定与至少一个给定点在同一直线上（其实肯定是两个点，但这样子说好像严谨那么一丢丢），也就是说我们可以画一个张这样子的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bun1tv6v.png)

也不难发现，我们其实只需要算出这四条直线的解析式，这个题基本上就宣告结束了，那么我们需要求解几个信息：

1. 四条直线的解析式

2. 每个点的位置如何用给定点的信息得到

因此我们就只需要求解这些就可以了，那么第一步就要先求解析式。

## 求解析式
我们用 $k$ 来表示斜率，那每条**直线**都可以写成 $y = kx + b$ 的形式，而对于斜率 $k$ 来说，我们需要关注的就是相邻边的斜率：
$$\begin{aligned}l1: y = kx + b && l2: y = - \frac{x}{k} + b \leftrightarrow  l1 \perp l2 \end{aligned}$$
也就是说，当两直线相互垂直，则其斜率乘积为 $-1$。而正方形邻边相互垂直，因此我们就可以用 $k$ 与 $- \frac{1}{k}$ 来表示，因此对于一条 $y = kx + b$ 的直线，我们知道点 $(x_{1},y_{1})$ 在该直线上，则一定有 $y_{1} = kx_{1} +b$ 那么 b 就可以表示为 $b = y_{1} - kx_{1}$，同理可得，所在直线就是 $y = kx + y_{1} -kx_{1}$，由此可知，四条直线解析式即为：
$$\begin{aligned} l1:y &= kx + y_{1} - kx_{1} \\ l2:y &= -\frac{x}{k} + y_{2} + \frac{x_{2}}{k} \\ l3:y &= kx + y_{3} - kx_{3} \\ l4:y &= -\frac{x}{k} + y_{4} + \frac{x_{4}}{k}\end{aligned}$$
因此，可以通过“求解两直线交点坐标”的方式，将任意两个相邻解析式联立得到其交点的横坐标（因为他们的纵坐标相等），得到：
$$ \begin{aligned} 
\frac{k^{2}x_{1}-ky_{1}+ky_{4}+x_{4}}{k^{2}+1} \\ 
\frac{k^{2}x_{1}-ky_{1}+ky_{2}+x_{2}}{k^{2}+1} \\ 
\frac{k^{2}x_{3}-ky_{3}+ky_{2}+x_{2}}{k^{2}+1} \\ 
\frac{k^{2}x_{3}-ky_{3}+ky_{4}+x_{4}}{k^{2}+1} \end{aligned}$$
## 求正方形四个点的坐标
那么如果将坐标系旋转 $90°$，那么我们就可以写出 $x$ 关于 $y$ 的表达式并求出四个点的坐标了：
$$ \begin{aligned} 
S_{1}(\frac{k^{2}x_{1}-ky_{1}+ky_{4}+x_{4}}{k^{2}+1},\frac{k^{2}y_{4}-kx_{1}+kx_{4}+y_{1}}{k^{2}+1}) \\ 
S_{2}(\frac{k^{2}x_{1}-ky_{1}+ky_{2}+x_{2}}{k^{2}+1},\frac{k^{2}y_{2}-kx_{1}+kx_{2}+y_{1}}{k^{2}+1}) \\ 
S_{3}(\frac{k^{2}x_{3}-ky_{3}+ky_{2}+x_{2}}{k^{2}+1},\frac{k^{2}y_{2}-kx_{3}+kx_{2}+y_{3}}{k^{2}+1}) \\ 
S_{4}(\frac{k^{2}x_{3}-ky_{3}+ky_{4}+x_{4}}{k^{2}+1},\frac{k^{2}y_{4}-kx_{3}+kx_{4}+y_{3}}{k^{2}+1}) \end{aligned}$$
那现在的话，我们只需要求出来 $k$ 的值就万事大吉了~~~。

更简单的发现：$S_{1}$ 与 $S_{2}$ 相邻，$S_{1}$ 又与 $S_{4}$ 相邻，因此！！！

$$x_{S_{2}}-x_{S_{1}}=y_{S_{1}}-y_{S_{4}}$$
那么，（大家自己推哈），我们就得到了最终的结果：
$$\begin{aligned}k=\frac{y_{1}+x_{4}-y_{3}-x_{2}}{y_{2}+x_{1}-y_{4}-x_{3}} \end{aligned}$$
！！！！哦耶~。

好的到这就结束了，大家加上 ``long double`` 就可以安心拿满分了哦~~~~。

---

## 作者：Ginger_he (赞：3)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/16212216.html)
# 题目描述
给定平面直角坐标系上的四个点，作一个正方形使得这 $4$ 个点分别在正方形每条边所在的直线上。
# 题解
补充一下 ternary_tree 的证明，好像还挺简单的。

![](https://cdn.luogu.com.cn/upload/image_hosting/rvf1jws9.png)

过 $A$ 作 $AM\perp BS$ 交 $BS$ 于点 $M$，过 $C$ 作 $CN\perp DX$ 交 $DX$ 于点 $N$，延长 $BA$ 交 $CX$ 于点 $K$。

$\because AP\perp DX,BQ\perp DX$

$\therefore AP\parallel BQ$

又 $\because RS\parallel PQ$

$\therefore$ 四边形 $PQSR$ 为矩形

$\because\angle BKX=\angle BQX=90\degree$

$\therefore\angle CXN=\angle ABM$

又 $\because\angle CNX=\angle AMB=90\degree,CX=AB$

$\therefore\triangle CXN\cong\triangle ABM(AAS)$

$\therefore CN=AM$

$\therefore PR=QS=CN=AM=PQ=RS$

$\therefore$ 四边形 $PQSR$ 为正方形。

---

- 因为 $C$ 与 $AB$ 的相对位置，$PQRS$ 的顺序可能会调换，不过没有影响。

- 注意一下输出的顺序就好了。

---

## 作者：enucai (赞：1)

## Analysis

**解析几何**萌萌题。

设四个点分别为 $A,B,C,D$，过 $A$ 的直线的斜率为 $k$。则过 $C$ 的直线的斜率为 $k$，过 $B$ 与 过 $D$ 的直线斜率均为 $-\frac{1}{k}$。容易计算出四条直线的函数表达式与正方形四个顶点坐标，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ty1hs043.png)

由于 $E_1E_2E_3E_4$ 是正方形，因此 $xE_2-xE_1=yE_1-yE_4$。化简得到一个一元一次方程。计算出 $k$ 再回代坐标即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/x5pfv57s.png)

## Code

```cpp
#include<iostream>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
#define db long double
db x1,x2,x3,x4,y1,y2,y3,y4;
void work(){
	scanf("%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
	db k=(y1-x2-y3+x4)/(x1+y2-x3-y4);
	printf("%.8Lf %.8Lf\n",(k*k*x1-k*y1+k*y4+x4)/(k*k+1),(k*k*y4-k*x1+k*x4+y1)/(k*k+1));
	printf("%.8Lf %.8Lf\n",(k*k*x1-k*y1+k*y2+x2)/(k*k+1),(k*k*y2-k*x1+k*x2+y1)/(k*k+1));
	printf("%.8Lf %.8Lf\n",(k*k*x3-k*y3+k*y2+x2)/(k*k+1),(k*k*y2-k*x3+k*x2+y3)/(k*k+1));
	printf("%.8Lf %.8Lf\n",(k*k*x3-k*y3+k*y4+x4)/(k*k+1),(k*k*y4-k*x3+k*x4+y3)/(k*k+1));
}
signed main(){
	int T;cin>>T;
	while(T--) work();
}
```

---

## 作者：TernaryTree (赞：0)

## 前言

pcq 出的一道构造 + 计算几何。很长一段时间内我都理解错了题意，理解成是线段上，后来 pcq 给了思路以后才真正明白。不得不说，金钩爷就是金钩爷。

这题的背景一开始是 lhx 写的，后来我修改了一点，把其他题的背景都补上了。连起来是一篇科幻小说，很 lj 我自己都不爱看下去的那种。

## 题目大意


给定平面直角坐标系上 $4$ 个点的坐标。

你要构造一个正方形，使得这 $4$ 个点分别在正方形每条边所在的**直线**上。

## 思路分析


连 $AB$，

做 $CX$ 垂直于 $AB$ 且 $CX=AB$。

连~~滴叉~~ $DX$，

做 $A,B$ 到 $DX$ 垂线 $AP,BQ$  ($P,Q$ 在 $DX$ 上）。

做 $CR//PQ$ 交 $AP,BQ$ 于 $R,S$。

则 $PQRS$ 即为所求。


需要用到比较强的计算几何基础。


## 完整代码

```cpp
#include <bits/stdc++.h>
#define double long double

using namespace std;

inline double DoubleRead()
{
    long long s = 0, w = 1, k = 0, n = 0, m = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while((ch >= '0' && ch <= '9') || ch == '.')
    { 
        if (ch == '.')
            n = 1;
        else if (n == 0)
            s = s * 10 + ch - '0';
           else k = k * 10 + ch - '0', m++;
        ch = getchar();
    }
    return (pow(0.1, m) * k + s) * w;
}

inline int IntRead() 
{
    char ch = getchar();
    int s = 0, w = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0',
        ch = getchar();
    }
    return s * w;
}



int main(){
	int T = IntRead();
	while(T--){
    	double x1,x2,y1,y2,z1,z2,l1,l2;
    	y1 = DoubleRead();
    	y2 = DoubleRead();
    	z1 = DoubleRead();
    	z2 = DoubleRead();
    	l1 = DoubleRead();
    	l2 = DoubleRead();
    	x1 = DoubleRead();
    	x2 = DoubleRead();
   		double m1=x1+y2-l2,m2=x2+l1-y1;
    	double k1=(z2-m2)/(z1-m1),k2=-1./k1;
    	double b1=x2-x1*k1,b2=y2-y1*k2,b3=z2-z1*k1,b4=l2-l1*k2;
    	double A1=-(b4-b1)/(k2-k1),A2=k1*A1+b1;
    	double B1=-(b2-b1)/(k2-k1),B2=k1*B1+b1;
    	double C1=-(b2-b3)/(k2-k1),C2=k1*C1+b3;
    	double D1=-(b4-b3)/(k2-k1),D2=k1*D1+b3;
    	printf("%.8Lf %.8Lf\n%.8Lf %.8Lf\n%.8Lf %.8Lf\n%.8Lf %.8Lf\n",B1,B2,C1,C2,D1,D2,A1,A2);
	}
    return 0;
}

```



---

