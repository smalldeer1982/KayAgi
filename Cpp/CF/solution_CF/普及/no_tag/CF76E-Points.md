# Points

## 题目描述

You are given $ N $ points on a plane. Write a program which will find the sum of squares of distances between all pairs of points.

## 样例 #1

### 输入

```
4
1 1
-1 -1
1 -1
-1 1
```

### 输出

```
32
```

# 题解

## 作者：Wenoide (赞：5)

给出 $n$ 个点，求这 $n$ 个点两两距离的平方和。即：

$$\sum_{i=1}^n\sum_{j=1}^{i-1}[(x_i-x_j)^2+(y_i-y_j)^2]$$

暴力求解的时间复杂度为 $O(n^2)$。显然会超时。

取 $\sum_{i=1}^n\sum_{j=1}^{i-1}(x_i-x_j)^2$ 这一部分，将括号展开并整理。可以得到：

$$\sum_{i=1}^n\sum_{j=1}^{i-1}(x_i^2+x_j^2)-2\sum_{i=1}^n\sum_{j=1}^{i-1}x_ix_j$$

------------

如何计算 $\sum_{i=1}^n\sum_{j=1}^{i-1}(x_i^2+x_j^2)$？

假设有一个数 $x_k$:

当 $k=i$ 时，$x_k^2$ 作为 $x_i^2$ 被计算了 $i-1$ 次；

当 $i\in(k,n]$ 时，$x_k^2$ 作为 $x_j^2$ 被计算了 $n-i$ 次。

那么 $x_k$ 对答案的贡献应为 $(n-1)\times x_k^2$。

枚举 $i\in[1,n]$，统计贡献 。可以在 $O(n)$ 的时间复杂度内完成这一部分的计算。

------------


如何计算 $\sum_{i=1}^n\sum_{j=1}^{i-1}x_ix_j$？

提取公因数 $x_i$：

$$\sum_{i=1}^n(x_i\times\sum_{j=1}^{i-1}x_j)$$

其中，$\sum_{j=1}^{i-1}$ 可以由 $\sum_{j=1}^{i-2}$ 推得。

枚举 $i\in[1,n]$，统计贡献，并记录 $\sum_{j=1}^{i}x_j$。可以在 $O(n)$ 的时间复杂度内完成这一部分的计算。

------------

$\sum_{i=1}^n\sum_{j=1}^{i-1}(y_i-y_j)^2$ 同理。

总时间复杂度为 $O(n)$。

参考代码：

```
//注意数据范围。
#include<cstdio>
int main(){
	long long ans=0;
	long long sx=0,sy=0;
	//sx,sy用于记录累加和。
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		ans+=(n-1LL)*(x*x+y*y)-((x*sx+y*sy)<<1);
		sx+=x,sy+=y;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：伟大的王夫子 (赞：2)

题目给出我们$n$个点，让我们求这几个点的平方和

设这几个点的坐标为$(x_i, y_i)$

则$ans = \sum_{i=1} ^ n \sum_{j = 1} ^ {i - 1} (x_i - x_j)^2 +(y_i - y_j)^2$

暴力$O(n^2)$超时

先拿$\sum_{i=1} ^ n \sum_{j = 1} ^ {i - 1} (x_i - x_j)^2$来说

$\text{原式}=\sum_{i=1} ^ n \sum_{j = 1} ^ {i - 1} {{x_i}^2+{x_j}^2} - 2\sum_{i=1} ^ n \sum_{j = 1} ^ {i - 1}x_ix_j$

令$A = \sum_{i=1} ^ n \sum_{j = 1} ^ {i - 1} {{x_i}^2+{x_j}^2}, B = 2\sum_{i=1} ^ n \sum_{j = 1} ^ {i - 1}x_ix_j$

$\forall k \in [1, n]$当$k = i$时${x_k}^2$被算了$k - 1$次

当$k \in [i +1, n]$时${x_k}^2$被算了$n-k$次

所以$\forall k \in [1, n]$ ${x_k}^2$的贡献为$n-1$

所以$A=(n-1)\sum_{i=1}^n {x_i}^2$

而$B = 2\sum_{i=1}^n x_i\sum_{j = 1}^{i-1} {x_j}$

令$sx_i=\sum_{j=1}^i {x_i}$

$B = 2{\sum_{i=1}^n x_i \times sx_{i - 1}} $

对于$y$同理

以上所有操作都可$O(n)$求出

故时间复杂度为$O(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
ll n, x[100010], y[100010], sx[100010], sy[100010], ansx, ansy;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
	for (register int i = 1; i <= n; ++i) 
		sx[i] = sx[i - 1] + x[i], sy[i] = sy[i - 1] + y[i];
	for (register int i = 1; i <= n; ++i) {
		ansx += (n - 1) * x[i] * x[i];
		ansy += (n - 1) * y[i] * y[i];
		ansx -= 2 * x[i] * sx[i - 1];
		ansy -= 2 * y[i] * sy[i - 1];
	}
	printf("%lld", ansx + ansy);	
}
```
一定开long long！


---

## 作者：Insouciant21 (赞：2)

首先了解距离公式 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$

于是这个问题就变成了求这个式子

$$
\sum_{i=1}^n\sum_{j=i+1}^n(x_i-x_j)^2+(y_i-y_j)^2
$$

当 $n=3$ 时，整理式子得
$$
2\times\sum_{i=1}^3(x_i^2+y_i^2)-2\times(\sum_{i=1}^2x_i\times\sum_{j=i+1}^3x_j+\sum_{i=1}^2y_i\times\sum_{j=i+1}^3y_j)
$$

可发现式子可变为
$$
(n-1)\times\sum_{i=1}^n(x_i^2+y_i^2)-2\times(\sum_{i=1}^{n-1}x_i\times\sum_{j=i+1}^nx_j+\sum_{i=1}^{n-1}y_i\times\sum_{j=i+1}^ny_j)
$$

代码为
``` cpp
#include <iostream>

using namespace std;

struct Point
{
	long long x, y;
};

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	Point a[n + 1];
	long long ans = 0;
	long long sumx = 0, sumy = 0;
	long long mul = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].x >> a[i].y;
		ans += a[i].x * a[i].x * (n - 1) + a[i].y * a[i].y * (n - 1); // 式子的前半部分计算
		sumx += a[i].x;
		sumy += a[i].y; // 计算所有x和y的和
	}
	sumx -= a[1].x, sumy -= a[1].y;
	for (int i = 1; i < n; i++) // 后半部分计算 
	{
		mul += 2 * a[i].x * sumx + 2 * a[i].y * sumy;
		sumx -= a[i + 1].x, sumy -= a[i + 1].y; // 算一个去掉最前面的值
	}
	cout << ans - mul << endl;
	return 0;
}
```

---

## 作者：NOILinux_Ubuntu (赞：2)

这道题**很水**的

真的是普及难度,如果真的不会的话那我就现场推一下吧

(由于是平方和，所以推导时我们先只看x)

设有3个点

sum=(x1-x2)^2+(x1-x3)^2+(x2-x3)^2=x1^2-2x1x2+x2^2+...(完全平方展开)

=2*(x1^2+x2^2+x3^2)-2*(x1*x2+(x1+x2)*x3)

若有4个点，则sum=3*(x1^2+x2^2+x3^2+x4^2)-2*(x1*x2+(x1+x2)*x3+(x1+x2+x3)*x4)

发现当我们每加入一个点x时，可以通过直接求ans1+=x^2以及ans2-=s*x(s为前面点x的和)

```cpp
//最后ans1*=n-1,ans2*=2，两者相加即可
//至于为什么这一段要打在代码块里，我不会告诉你"*="死活打不出的
#include<iostream>
#include<cstdIO>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define itn long long
#define ri register itn
#define For(i,a,b) for(ri i=(a);i<=(b);++i)
itn n;
itn read(){
 char ch=getchar();
 itn x=0,f=1;
   while(ch<'0'||ch>'9'){
    if(ch=='-')f=-1;
    ch=getchar();
   }
   while(ch>='0'&&ch<='9'){
    x=(x<<3)+(x<<1)+(ch^48);
    ch=getchar();
   }
  return x*f;
}
int main(){
  n=read();
  itn x,y;
  itn ans1=0,ans2=0,last1=0,last2=0;
  For(i,1,n){
   x=read(),y=read();
   ans1+=x*x+y*y;ans2-=last1*x+last2*y;
   last1+=x,last2+=y;
  }
  ans1*=n-1;
  ans2*=2;
  printf("%lld\n",ans1+ans2);
 return 0;
}
```

---

## 作者：scp020 (赞：1)

### 题目大意

给出 $n$ 个点的坐标 $x$ 和 $y$，让你求出各个点的距离的平方和。

### 解法

两点距离公式：$\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

本题是一道数学题，第一反应是枚举 $\sum\limits_{i=1}^n \sum\limits_{j=i+1}^n (x_1-x_2)^2+(y_1-y_2)^2$，时间复杂度为 $O(n^2)$（跑不满），会超时，所以我们要对原式进行化简。

化简得 $(n-1) \times \sum\limits_{i=1}^n (x_i^2 + y_i^2)-2 \times (\sum\limits_{i=1}^{n-1}x_i \times \sum\limits_{j=i+1}^n x_j + \sum\limits_{i=1}^{n-1}y_i \times \sum\limits_{j=i+1}^n y_j)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans1,sum1,sum2,ans2;
struct node
{
	int x,y;
	node()
	{
		x=0,y=0;
	}
	void init1()
	{
		ans1+=(long long)(x*x*(n-1))+(long long)(y*y*(n-1));
		sum1+=x,sum2+=y;
	}
	void init2(int xx,int yy)
	{
		ans2+=2*x*sum1+2*y*sum2,sum1-=xx,sum2-=yy;
	}
};
node a[100010];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y,a[i].init1();
	sum1-=a[1].x,sum2-=a[1].y;
	for(int i=1;i<n;i++) a[i].init2(a[i+1].x,a[i+1].y);
	cout<<ans1-ans2;
	return 0;
}
```


---

## 作者：Buried_Dream (赞：1)

可以把题目转换成求：

$$\sum_{i = 1}^{n} \sum_{j = i + 1} ^{n} [(x_i - x_j)^2 + (y_i - y_j)^2]$$


继续化简:

$$\begin{aligned} 

&=\sum_{i = 1}^{n} \sum_{j = i + 1} ^{n} (x_i - x_j)^2 + \sum_{i = 1}^{n} \sum_{j = i + 1} ^{n}  (y_i - y_j)^2

\\

&= \sum_{i = 1}^n \sum_{j = i + 1}^{n}(x_i^2-2x_ix_j+x_j^2)+\sum_{i = 1}^n \sum_{j = i + 1}^{n}(y_i^2-2y_iy_j+y_j^2)

\\

&= \sum_{i=1}^n \sum_{j=i+1}^n(x_i^2+y_i^2)+\sum_{i=1}^n \sum_{j=i+1}^n (x_j^2 + y_j^2)-2\sum_{i=1}^n\sum_{j=i+1}^n (x_ix_j + y_iy_j)

\\

&= \sum_{i=1}^{n} [(n-i)\times (x_i^2 + y_i^2)] + \sum_{i =1}^n[(i -1)\times (x_i^2 + y_i^2) ] - 2\sum_{i=1}^{n}(x_i\sum_{j=i+1}^n x_j + y_i\sum_{j=i+1}^n y_j)

\\

&=\sum_{i=1}^n[(n- 1) \times (x_i^2 + y_i^2)]- 2\sum_{i=1}^{n}(x_i\sum_{j=i+1}^n x_j + y_i\sum_{j=i+1}^n y_j)\end{aligned}$$

每一项都可以 $\mathcal{O}(n)$ 的处理出来，总时间复杂度是 $\mathcal{O}(n)$。


```cpp
ll x[N], y[N], hzx[N], hzy[N];
ll ans = 0;

signed main() 	
{
	int n = read();	
	for(int i = 1; i <= n; i++) x[i] = read(), y[i] = read();
	for(int i = n; i >= 1; i--) hzx[i] = hzx[i + 1] + x[i], hzy[i] = hzy[i + 1] + y[i];
	for(int i = 1; i <= n; i++) ans +=  (n - 1) * ((x[i] * x[i]) + (y[i] * y[i]));
	for(int i = 1; i <= n; i++) ans -=  2 * ((x[i] * hzx[i + 1]) + (y[i] * hzy[i + 1]));
	printf("%lld\n", ans);
	return (0 - 0);
}
```

---

## 作者：zsyyyy (赞：1)

# CF76E 1700 数学

## 题意

有 $n$ 个点，求这 $n$ 个点的距离的平方和。

**输入：**

第一行：$n$（$0≤n≤100000$）

接下来 $n$ 行：每行两个数 $x$，$y$，表示该点坐标（$-10000≤x$，$y≤10000$）。

**输出：**

所有点的距离的平方和。


## 思路

前置知识：若两个点 $(x_{1},y_{1})$ 和 $(x_{2},y_{2})$，它们的距离是 $\sqrt{(x_{1}-x_{2})^2+(y_{1}-y_{2})^2}$

假设有 $3$ 个点，坐标为 $(x_{1},y_{1})$， $(x_{2},y_{2})$， $(x_{3},y_{3})$

它们的距离的平方和是：

$(x_{1}-x_{2})^2+(y_{1}-y_{2})^2+(x_{1}-x_{3})^2+(y_{1}-y_{3})^2+(x_{2}-x_{3})^2+(y_{2}-y_{3})^2$

$=x_{1}^2+x_{2}^2-2x_{1}x_{2}+y_{1}^2+y_{2}^2-2y_{1}y_{2}+x_{1}^2+x_{3}^2-2x_{1}x_{3}+y_{1}^2+y_{3}^2-2y_{1}y_{3}+x_{2}^2+x_{3}^2-2x_{2}x_{3}+y_{2}^2+y_{3}^2-2y_{2}y_{3}$

$=2(x_{1}^2+x_{2}^2+x_{3}^2)+2(y_{1}^2+x_{2}^2+x_{3}^2)-2(x_{1}x_{2}+x_{1}x_{3}+x_{2}x_{3}+y_{1}y_{2}+y_{1}y_{3}+y_{2}y_{3})$

由此可知有 $n$ 个点时，设所有横坐标的平方和为 $x2$，所有纵坐标的平方和为 $y2$，所有任意两个横和纵坐标的积的和为 $sum$，距离的平方和就是$(x2+y2)(n-1)-sum(n-1)$。


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=100005;
int n,x[MAXN],y[MAXN],x2,y2,xsum,ysum,ans,sum;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)  scanf("%lld%lld",&x[i],&y[i]);
	for(int i=1;i<=n;i++)  x2+=(x[i]*x[i]);
	for(int i=1;i<=n;i++)  y2+=(y[i]*y[i]);
	for(int i=1;i<=n;i++)  xsum+=x[i];
	for(int i=1;i<=n;i++)  ysum+=y[i];
	ans=(x2+y2)*(n-1);
	for(int i=1;i<=n;i++)  ans-=x[i]*(xsum-x[i])+y[i]*(ysum-y[i]);
	printf("%lld",ans);
	return 0;
}
```


---

