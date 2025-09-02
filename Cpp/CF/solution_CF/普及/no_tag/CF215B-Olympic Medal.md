# Olympic Medal

## 题目描述

The World Programming Olympics Medal is a metal disk, consisting of two parts: the first part is a ring with outer radius of $ r_{1} $ cm, inner radius of $ r_{2} $ cm, $ (0&lt;r2&lt;r1) $ made of metal with density $ p_{1} $ g/cm $ ^{3} $ . The second part is an inner disk with radius $ r_{2} $ cm, it is made of metal with density $ p_{2} $ g/cm $ ^{3} $ . The disk is nested inside the ring.

The Olympic jury decided that $ r_{1} $ will take one of possible values of $ x_{1},x_{2},...,x_{n} $ . It is up to jury to decide which particular value $ r_{1} $ will take. Similarly, the Olympic jury decided that $ p_{1} $ will take one of possible value of $ y_{1},y_{2},...,y_{m} $ , and $ p_{2} $ will take a value from list $ z_{1},z_{2},...,z_{k} $ .

According to most ancient traditions the ratio between the outer ring mass $ m_{out} $ and the inner disk mass $ m_{in} $ must equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF215B/cd92991466e894ef37b65a9188f245d17d24ea1f.png), where $ A,B $ are constants taken from ancient books. Now, to start making medals, the jury needs to take values for $ r_{1} $ , $ p_{1} $ , $ p_{2} $ and calculate the suitable value of $ r_{2} $ .

The jury wants to choose the value that would maximize radius $ r_{2} $ . Help the jury find the sought value of $ r_{2} $ . Value $ r_{2} $ doesn't have to be an integer.

Medal has a uniform thickness throughout the area, the thickness of the inner disk is the same as the thickness of the outer ring.

## 说明/提示

In the first sample the jury should choose the following values: $ r_{1}=3 $ , $ p_{1}=2 $ , $ p_{2}=1 $ .

## 样例 #1

### 输入

```
3 1 2 3
1 2
3 3 2 1
1 2
```

### 输出

```
2.683281573000
```

## 样例 #2

### 输入

```
4 2 3 6 4
2 1 2
3 10 6 8
2 1
```

### 输出

```
2.267786838055
```

# 题解

## 作者：Alex_Wei (赞：7)

前置知识（除非你会暴力）：

- **小学**的数学基础

---

首先，我们按题目的要求列下方程，设奖牌的高度（即厚度）为 $h$，则有

$$\frac{m_{out}}{m_{in}}=\frac{A}{B}$$

$$\frac{V_{out}p_1}{V_{in}p_2}=\frac{A}{B}$$

$$\frac{S_{out}h}{S_{in}h}=\frac{Ap_2}{Bp_1}$$

$$\frac{(r_1^2-r_2^2)\pi}{r_2^2\pi}=\frac{Ap_2}{Bp_1}$$

$$\frac{r_1^2}{r_2^2}-1=\frac{Ap_2}{Bp_1}$$

$$\frac{1}{r_2^2}=\frac{\frac{Ap_2}{Bp_1}+1}{r_1^2}$$

$$r_2^2=\frac{r_1^2}{\frac{Ap_2}{Bp_1}+1}$$

因为 $A,B,p_1,p_2,r_1>0$，所以由小学的数学知识（均为正数范围内）**被除数越大，商越大** 和 **除数越小，商越大** 可知：

**当 $p_1,r_1$ 取最大值，$p_2$ 取最小值时，$r_2$ 最大**

---

然后就有了代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double n,m,k,x,r1,p1,p2=1e9,A,B;
int main()
{
	cin>>n;for(int i=1;i<=n;i++)cin>>x,r1=max(r1,x);
	cin>>m;for(int i=1;i<=m;i++)cin>>x,p1=max(p1,x);
	cin>>k;for(int i=1;i<=k;i++)cin>>x,p2=min(p2,x);
	cin>>A>>B;printf("%.9lf",sqrt(r1*r1/(A*p2/B/p1+1)));
}
```


---

## 作者：xiaomimxl (赞：0)

# 题意分析

一个大盘子中间挖去了一块,然后呢,这两个的密度还不同。

已经给你了 $r1$, $p1$, $p2$,( $r1$ 就是盘子的直径),让你去求 $r2$ (内圆的直径)。

要求是内外的比值一定要等于 $A \div B$.

# 思路分析

我们根据小学的经验有：

$r2^2=(B \times p1 \times r1^2) \div (Ap2+Bp1)$

那么我们就可以打一个暴力予以解决，但是我们会得到一个大大的 TLE

来分析一下时间复杂度，是的一个 $O(mnk)$ 的，很明显不行

我们再来分析一下公式，我们上下都干掉 $p1$ 就可以了

时间复杂度 $O(nm)$

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxx=5e3+10;
double r[maxx];
double p1[maxx];
double p2[maxx];
double a,b;
int n,m,k;

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lf",&r[i]);
	scanf("%d",&m);
	for(int i=0;i<m;i++) scanf("%lf",&p1[i]);
	scanf("%d",&k);
	for(int i=0;i<k;i++) scanf("%lf",&p2[i]);
	scanf("%lf%lf",&a,&b);
	double maxn=99999999;
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<m;j++)
		{
			maxn=min(maxn,p2[i]/p1[j]);
		}
	}
	double m=-1;
	for(int i=0;i<n;i++)
	{
		double x=sqrt(b*r[i]*r[i]/(a*maxn+b));
		if(x>m)
		{
			m=x;
		}
	}
	printf("%.12lf\n",m);
}

```


---

