# A Problem about Polyline

## 题目描述

There is a polyline going through points $ (0,0)–(x,x)–(2x,0)–(3x,x)–(4x,0)–...-(2kx,0)–(2kx+x,x)–... $ .

We know that the polyline passes through the point $ (a,b) $ . Find minimum positive value $ x $ such that it is true or determine that there is no such $ x $ .

## 说明/提示

You can see following graphs for sample 1 and sample 3.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/abf33c2e979ad11f626e45babf5d2a8a224a3964.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/567201d8db120e4f8136d5be265b91eca027e0d4.png)

## 样例 #1

### 输入

```
3 1
```

### 输出

```
1.000000000000
```

## 样例 #2

### 输入

```
1 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 1
```

### 输出

```
1.250000000000
```

# 题解

## 作者：81179332_ (赞：3)

容易发现，$a<b$ 时无解

分两种情况考虑：与 $x$ 轴最近的交点为 $(a-b,0)$ 和 $(a+b,0)$

设交点横坐标为 $y$，则容易发现，$x=\dfrac y{2k},k\in\mathbb{Z}$

由于我们要到达 $b$ 这个高度，则 $\dfrac y{2k}\ge b$

则 $k\le\dfrac y{2b}$，我们要使 $x$ 最小，就是要使 $k$ 最大，则 $k$ 的最大值为 $\lfloor \dfrac y{2b}\rfloor$

则 $x$ 的最小值为 $\dfrac y{2\lfloor \dfrac y{2b}\rfloor}$

取两种情况的较小值输出即可

```cpp
//timeuse:5min
int a,b;
double solve(int y)
{
	int k = y / (2 * b);
	return (double)y / (double)(2 * k);
}
int main()
{
	a = read(),b = read();
	if(a - b < 0) { puts("-1");return 0; }
	double ans = min(solve(a + b),solve(a - b));
	printf("%.10lf\n",ans);
}
```

---

## 作者：SalomeJLQ (赞：1)

### 题意

设平面上一系列点 $(0,0),(x,x),(2x,0),(3x,x),(4x,0)\dots$，前后相邻两点分别相连，形成一条折线。给定点 $(a,b)$，求出最小的 $x$ 使得折线经过点 $(a,b)$，或者给出无解。

### 题解

显然无解的情况为 $a<b$。

对于有解的情况，首先考虑上行的折线经过点的情况。等价于这么一组斜率为 $1$ 的互相平行的直线：

![](https://cdn.luogu.com.cn/upload/image_hosting/xwftoual.png?x-oss-process=image/resize,m_lfit,h_1170,w_925)

绿色的点为 $(a,b)$，那么恰好经过该点的直线与 $x$ 轴交点为 $(a-b,0)$。

无论如何，只要是上行的折线经过，则这条线就是固定的。考虑在这条线之前有多少条平行线，设其为 $k$；因此，相邻两条线与 $x$ 轴交点之间的距离 $z$ 就为 $\frac{a-b}{k}$，而 $x=\frac{z}{2}=\frac{a-b}{2k}$。

考虑 $z$ 需要的条件。由于折线的值域是 $\left[0,x\right]$，因此要求 $\frac{a-b}{2k}\geqslant b$，即 $k\leqslant\frac{a-b}{2b}$。又须使 $z$ 最小，则 $k$ 应尽可能地大，从而 $k=\lfloor\frac{a-b}{2b}\rfloor$。因此此种情况求得：

$$
x=\frac{z}{2}=\frac{a-b}{2k}=\frac{a-b}{2\lfloor\frac{a-b}{2b}\rfloor}
$$

下行的折线经过点 $(a,b)$ 也是类似的，为 $\frac{a+b}{2\lfloor\frac{a+b}{2b}\rfloor}$。最终我们将二者对比，取较小值即可。即：

$$
\min\left(\frac{a-b}{2\lfloor\frac{a-b}{2b}\rfloor}\,,\;\frac{a+b}{2\lfloor\frac{a+b}{2b}\rfloor}\right)
$$

判掉第一个式子中分母为零的情况即可。

```cpp
ll a,b;DB x,y,A,B;
int main()
{
	a=read(),b=read(),A=a*1.0,B=b*1.0,
	y=(a+b)/(2*floor((a+b)/(2*b)));
	if(a-b<0)printf("-1\n");
	else if(a-b==0)printf("%.10lf\n",y);
	else x=(a-b)/(2*floor((a-b)/(2*b))),
		printf("%.10lf\n",min(x,y));
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1700}$
---
### 解题思路：

首先发现，当 $a>b$ 的时候一定无解，否则一定有解。

然后分两种情况讨论，即当前点在斜率等于 $1$ 的直线上还是在斜率等于 $-1$ 的直线上。

对于每一种情况，需要满足最大位置，也就是求出的 $x$，不低于目标点的纵坐标。不妨考虑与 $x$ 轴的交点在 $(a+b,0)$ 的位置的时候的情况，这也就是要求 $\dfrac{a+b}{2k}\ge b$，而且要求 $x=\dfrac{a+b}{2k}$ 最小。

$k$ 是一个整数，则最大不超过 $\left\lfloor\dfrac{a+b}{2b}\right\rfloor$，带入一下就有：$x=\dfrac{a+b}{2\left\lfloor\dfrac{a+b}{2b}\right\rfloor}$。

对于另一种情况，类似地有：$x=\dfrac{a-b}{2\left\lfloor\dfrac{a-b}{2b}\right\rfloor}$，所以最后的结果应当是：$\min(\dfrac{a-b}{2\left\lfloor\dfrac{a-b}{2b}\right\rfloor},\dfrac{a+b}{2\left\lfloor\dfrac{a+b}{2b}\right\rfloor})$

---

到这里其实已经可以结束了，算两种取最小值即可。不过其实能进一步推导出后者一定更小。

分两种情况讨论 $\dfrac{a-b}{2\left\lfloor\dfrac{a-b}{2b}\right\rfloor}$ 和 $\dfrac{a+b}{2\left\lfloor\dfrac{a+b}{2b}\right\rfloor}$ 的大小关系。在第一种情况下，设：$a=2kb+r$，其中 $r\in[0,b)$。

则原式等价于求 $[(2k-1)b+r]k$ 和 $[(2k+1)b+r](k-1)$ 的大小关系，即：$(2k^2-k)b+kr$ 和 $(2k^2-k)b+kr-b-r$ 的大小关系，结合各个数的取值，显然是左式更大一点。

当 $a=2kb+b+r$ 的时候，用类似的方法可以得出同样的结论，倒数第二步的出的式子为：$2k^2b+kr+2kb+r>2k^2b+kr+2kb$，同样是左边更大一点。

---
### 代码：

```cpp
#include<cstdio>
long long a,b;
int main(){
	scanf("%I64d%I64d",&a,&b);
	if(a<b)printf("-1");
	else printf("%.12lf",(a+b)/(2.0*((a+b)/(2*b))));
	return 0;
}
```



---

## 作者：czh___ (赞：0)

### 其实就是一道数学题

思路：
两段折线的方程分别是 $a-2kx=b$ 和 $2kx-a=b$。对于第一个式子，通过移项得到 $k=\frac{a-b}{2b}\leq\frac{a-b}{2x}$，$x=\frac{a-b}{2k}$，其中 $k$ 为整数，$x$ 为实数。用同样的方法对第二个式子求解，然后两者的 $x$ 取较小的。这样代码就很好写了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
  	scanf("%d%d",&a,&b);
  	if(a<b){
   		printf("-1");
   	 	return 0;
	}
  	printf("%.9lf",(a+b)/(2.0*((a+b)/(2*b))));
  	return 0;
}
```

拜拜！

---

## 作者：Imiya (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF578A)

为了方便，记 $t$ 为题面中的 $x$。

先考虑无解的情况。

易知， $a<b$ 时必定无解，若 $a\ge b$ 则 $t=\frac{a+b}2$ 必是一个符合条件的解，也就是只拐一次或一次不拐，其中 $a=b$ 时它是唯一解。所以当且仅当 $a<b$ 输出 $-1$。

假设 $(a,b)$ 在答案函数图像 $f(x)$ 中斜率为 $-1$ 的一段里，那么 $(a+b,0)$ 必定是 $f(x)$ 的一个最低点。设 $k$ 为 $f(x)(x\in[0,a+b])$ 的最小正周期 $(T=2t)$ 的数量。若使 $f(x)$ 符合调节，则只需满足
$$\frac{a+b}{2k}\ge b$$
$$\frac{a+b}{2b}\ge k$$
因为 $t$ 取最小值，所以 $k$ 取最大值。
$$k=\lfloor\frac{a+b}{2b}\rfloor$$
$$\therefore T=\frac{a+b}k=\frac{a+b}{\lfloor\frac{a+b}{2b}\rfloor}$$
$$t=\frac T 2=\frac{a+b}k=\frac{a+b}{2\lfloor\frac{a+b}{2b}\rfloor}$$
假设 $(a,b)$ 在答案函数图像 $f(x)$ 中斜率为 $1$ 的一段里，则与上面类似，$f(x)$ 符合条件只需满足
$$\frac{a-b}{2k}\ge b$$
$$\frac{a-b}{2b}\ge k$$
因为 $t$ 取最小值，所以 $k$ 取最大值。
$$k=\lfloor\frac{a-b}{2b}\rfloor$$
$$\therefore T=\frac{a-b}k=\frac{a-b}{\lfloor\frac{a-b}{2b}\rfloor}$$
$$t=\frac T 2=\frac{a-b}k=\frac{a-b}{2\lfloor\frac{a-b}{2b}\rfloor}$$
$$\because k\neq 0$$
$$\therefore \frac a{2b}-\frac b{2b}\ge1$$
$$\frac a{2b}\ge\frac 3 2$$
$$a\ge 3b$$
所以答案就是
$$\frac{a+b}{2\lfloor\frac{a+b}{2b}\rfloor}(a<3b),\min(\frac{a+b}{2\lfloor\frac{a+b}{2b}\rfloor},\frac{a-b}{2\lfloor\frac{a-b}{2b}\rfloor})(a\ge 3b)$$

---

## 作者：Frevotops (赞：0)

本蒟蒻提交审核的第一个题解。

## Step.0 看题

求过点 $(a,b)$ 的折线 $(0,0)-(x,x)-(2x,0)-(3x,x)-(4x,0)-...-(2kx,0)-(2kx+x,x)-...$ 的 $x$ 的最小值。
## Step.1 观察

容易发现，无论 $x$ 的取值是多少，每条线段的斜率都是不变的。第奇数条线段的斜率是 $1$，偶数条是 $-1$。

![image.png](https://s2.loli.net/2022/04/05/iab8cnUZqBLS9f5.png)

为了通俗一点，下文中将上图 $A \to B$ 这样斜率为 $1$ 的线段称为“起”，$B \to C$ 这样斜率为 $-1$ 的线段称为“落”。一个“起”和一个“落”称为一个“周期”。


## Step.2 思考

由于第奇数条和偶数条线段的斜率不同，我们不妨分类讨论，先假设该点在第奇数条线段上。

先随便取一个点 $A$。由于我们已知第奇数条线段的斜率是 $1$，我们就可以知道点 $A$ 所在的线段在哪一条直线上。设该直线交横坐标轴于 $B$。如果 $B$ 的横坐标值小于 $0$ 无解。

![image.png](https://s2.loli.net/2022/04/05/YG2aTUQIxVsh7DX.png)

看上图的数据，想象一下，在横坐标轴上 $[0,3]$ 这一段区间，折线应该是从点 $(0,0)$ 开始起、落、起……最后落到点 $(0,3)$。我们想要求出 $x$，不妨求出**这段区间经历了多少次周期**，用这段区间的长度除以周期数就是 $2x$（注意不是 $x$）。由于周期数是整数，这样就更好求了。

我们需要让 $x$ 满足什么条件呢？就是 $x$ 要大于 $A$ 点的纵坐标值（设为 $h$）。我们看一下不等式，设周期数为 $p$，$(0,0)$ 到 $B$ 点的距离为 $d$。

$\dfrac{d}{2p} =x\ge h  \ \  \ \ \therefore \dfrac{d}{h} \ge 2p$

题目让我们求最小的 $x$，那么 $p$ 要尽量大且是整数，根据上面的不等式我们已经可以求出最大的 $p$ 了。根据上图的数据解得 $p=1, x=1.5$。

![image.png](https://s2.loli.net/2022/04/05/94MJni7ROb62pT8.png)

那么，$A$ 点在奇数条线段上的情况解决了，读者可以自行推导偶数条的情况。

## Step.3 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b;
double ans1=1e18, ans2=1e18;
double work1(ll a,ll b){ // 在第奇数条
	if(a<b) return 1e18;
	a-=b;
	p*=2;
	if(p<1) return 1e18;
	ans1=a*1.0/p;
	if(ans1<b) return 1e18;
	return ans1;
}
double work2(ll a,ll b){ // 在第偶数条
	a+=b;
	ll p=a/b/2;
	p*=2;
	if(p<1) return 1e18;
	ans2=a*1.0/p;
	if(ans2<b) return 1e18;
	return ans2;
} 
int main(){
	cin>>a>>b;
	double ans=min(work1(a,b), work2(a,b));
	if(ans>=1e18) cout<<-1<<endl;
	else cout<<fixed<<setprecision(11)<<ans<<endl;
}
```

---

## 作者：Purslane (赞：0)

## Solution

欸,推式子题.

这些点都是在直线$x-y=0$上和以下的,所以$a<b$无解.

然后这个点所在线段的斜率为 $1$ 为 $-1$ , 所以线段所在直线的方程为$x+y=a+b$或$x-y=a-b$.与$x$轴交于$(a+b,0)$和$(a-b,0)$.

考虑有了交点怎么算出$x$.显然,交点的横坐标应该是$x$的偶数倍 .

不妨设交点横坐标为$p$,$x=\frac{p}{2k}$.线段峰值是$x$,所以$x \ge b$ , 解得$k$最大值是$\lfloor \frac{p}{2b} \rfloor$.$x$取最小值,则$k$取最大值带入即可.

注意$p=0$时,也就说明$a=b$,分母为$0$,应直接判为$b$.

[code](http://codeforces.com/problemset/submission/578/152716080)

---

