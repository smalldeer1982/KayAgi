# [USACO3.4] 网 Electric Fences

## 题目描述

在本题中，格点是指横纵坐标皆为整数的点。

为了圈养他的牛，Farmer John 建造了一个三角形的电网。他从原点 $(0,0)$ 牵出一根通电的电线，连接格点 $(n,m)$（$0\le n<32000,0<m<32000$），再连接格点 $(p,0)$（$p>0$），最后回到原点。

牛可以在不碰到电网的情况下被放到电网内部的每一个格点上（十分瘦的牛）。如果一个格点碰到了电网，牛绝对不可以被放到该格点之上（或许 Farmer John 会有一些收获）。那么有多少头牛可以被放到农夫约翰的电网中去呢？

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.4。

## 样例 #1

### 输入

```
7 5 10```

### 输出

```
20```

# 题解

## 作者：FrenzyHydra (赞：20)

1定理：pick定理
pick定理是指一个计算点阵中顶点在格点上的多边形面积公式，该公式可以表示为2S=2a+b-2，其中a表示多边形内部的点数，b表示多边形边界上的点数，s表示多边形的面积。

------------

2定理：（0,0）到（n,m）上点的个数=gcd(n,m)+1，
定理2就是扩展欧几里得的特殊情况

楼下的老哥有代码我就不贴了（其实知道这些代码已经很容易写了）
ps.逆用pick定理时一定不能用（2s-b+2）/2，应该用s-b/2+1，不然会因为精度问题wa掉一个点

---

## 作者：Laser_Crystal (赞：13)

嗯？也算计算几何吧题目吧……

小学奥数的题目，不过这也告诉我们平时要多积累经验与公式，这样比赛可以用的上。

很多题解里都提到是pick定理了，即$S=a+\frac{b}{2}-1$，其中a表示多边形内部的点数（就是题目中要求的答案)，b表示多边形恰好落在边界上的点数，s表示多边形的面积。

易知，$a=S-b/2+1$

那么$S$和$b$改怎么计算呢？

因为有一条边就是和x轴重合的，即$(0,0)$到$(p,0)$这条边，因此三角形公式$S=\frac{pm}{2}$

b就是三角形三边上的所经过的点。$(0,0)$到$(p,0)$边上有$p+1$个点经过

然后是如何计算从$(0,0)$到$(n,m)$上的点了。

我们可以知道，过这两点的斜率是$\frac{n}{m}$，当且仅当有整数k使得$\frac{n}{m}\times k$为整数时才在一个点上。若$n$和$m$互质的时候，只有这样一个整数k，即$k=m$，但是如果当$n$与$m$不互质的时候，则有$\gcd(n,m)$个点在直线上。

然后加上点$(0,0)$，就有如下定理：

**$(0,0)$到$(n,m)$上点的个数=$\gcd(n,m)+1$**

我们可以很快的计算出$(0,0)$到$(n,m)$上点的个数，但是我们该怎么，计算出$(n,m)$到$(p,0)$上的点数呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/70u1nfuy.png)

Rt，虽然不只有一种情况，但是所有情况都可以概括为这么一个图。

可见，BC的长度是等于AB3的长度的，因为AB2是BC向x轴的负方向平移p所得的线段，AB3是AB2对于y轴的对称图形。

B2的坐标是$(n-p,m)$ ,B3的坐标就是$(|n-p|,m)$，所以这条BC边上的点数就是$\gcd(|n-p|,m)+1$

而在边上所有点的个数为： $p+1+\gcd(n,m)+1+\gcd(|n-p|,m)+1-3$
也就是$p+\gcd(n,m)+\gcd(|n-p|,m)$ ,化简过程涉及到简单的容斥。

所以这道题可以$O(1)\;A$掉哦

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,m,p;
	cin>>n>>m>>p;
	long long b=__gcd(n,m)+__gcd(abs(p-n),m)+p，S=(m*p)/2;//偷了个小懒qwq
	long long a=S-b/2+1;
	cout<<a;
	return 0;
}
```
喵呜~

---

## 作者：「QQ红包」 (赞：10)

下面这段话来自百度百科

一张方格纸上，上面画着纵横两组平行线，相邻平行线之间的距离都相等，这样两组平行线的交点，就是所谓格点。如果取一个格点做原点O，如图1，取通过这个格点的横向和纵向两直线分别做横坐标轴OX和纵坐标轴OY，并取原来方格边长做单位长，建立一个坐标系。这时前面所说的格点，显然就是纵横两坐标都是整数的那些点。如图1中的O、P、Q、M、N都是格点。由于这个缘故，我们又叫格点为整点。

一个多边形的顶点如果全是格点，这多边形就叫做格点多边形。有趣的是，这种格点多边形的面积计算起来很方便，只要数一下图形边线上的点的数目及图内的点的数目，就可用公式算出。

这个公式是皮克(Pick)在1899年给出的，被称为“皮克定理”，这是一个实用而有趣的定理。

给定顶点坐标均是整点（或正方形格点）的简单多边形，皮克定理说明了其面积S和内部格点数目n、边上格点数目s的关系：

 S=n+s/2-1

(其中n表示多边形内部的点数,s表示多边形边界上的点数,S表示多边形的面积)

其中我们要求的是n，S很容易求

我们可以设直线(0，0)→(n,m)上的一点坐标为(x,x\*m/n)(x<n),且这个点为整点,求符合条件的x的个数。

代码
‘’‘cpp

/\*
ID: ylx14271

PROG: fence9

LANG: C++

\*/

```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}//最大公约数 
int s,b,i,n,m,p; 
int main() 
{
        freopen("fence9.in","r",stdin);
    freopen("fence9.out","w",stdout); 
        scanf("%d%d%d",&n,&m,&p);
        b=gcd(n,m)+gcd(abs(p-n),m)+p;//边上格点数目
    s=(p*m)/2;//面积 s=i+b/2-1
    i=s-b/2+1;
    printf("%d\n",i); 
    return 0;
}
```
’‘’

---

## 作者：一只书虫仔 (赞：6)

#### Description

> 求三角形 $(0,0),(n,m),(p,0)$ 里有多少个整点。

#### Pre Know / 前置知识

皮克定理：

$$S=k+\dfrac{s}{2}-1$$

$S$ 为多边形面积，$k$ 为内部整点个数，$s$ 为边上的整点个数。

#### Solution

在这题中我们要求皮克定理中的 $k$，所以我们可以求出 $S$ 和 $s$，然后就可以逆用皮克定理出来了：

$$k=S -\dfrac{s}{2}+1$$

$S$ 很好求吧，因为有两个点 $(0,0),(p,0)$ 在 $x$ 轴上，因此可以以这条边 $(0,0) \to (p,0)$ 为底，做 $(n,m)$ 到 $(0,0)\to (p,0)$ 的高然后求就行了，容易得到 $S$ 应该是：

$$S=\dfrac{p \times m}{2}$$

$s$ 可以拆成三角形的三条边分别看：

- $(0,0) \to (p,0)$ 上有 $p$ 个整点。
- $(n,m) \to (0,0)$ 上有 $\gcd(n,m)$ 个整点。
- $(p,0) \to (n,m)$ 上有 $\gcd(|p-n|,m)$ 个整点。

用 $\gcd$ 求整点个数就是求长方形对角线相交多少个整点那个套路问题。

所以 $s$ 也可以求出来力：

$$s=p+\gcd(n,m)+\gcd(|p-n|,m)$$

因此 $k$ 也出来力：

$$k=\dfrac{p \times m}{2}-\dfrac{p+\gcd(n,m)+\gcd(|p-n|,m)}{2}+1$$

总之，是一个考点比较全面的算几题。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int gcd(int x, int y) {
	if (x % y == 0) {
		return y;
	}
	else {
		return gcd(y, x % y);
	}
}

int main () {
	int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    int x = gcd(n, m) + gcd(abs(p - n), m) + p;
    int s = (p * m) / 2;
    int y = s - x / 2 + 1;
    printf("%d\n", y); 
	return 0;
}

// 几个月前的屑代码
```

---

## 作者：Grisses (赞：5)

[题面](https://www.luogu.com.cn/problem/P2735)

如果做本题时，你知道 **皮克定理**，那么会非常轻松，如果不知道，现在就会知道了。

## 皮克定理：

皮克定理是用来计算点阵中顶点在格点上的多边形面积的，公式表示为 $S=a+\dfrac{b}{2}-1$，其中 $a$ 表示多边形内部的点数，$b$ 表示多边形落在格点边界上的点数，$S$ 表示多边形的面积。

皮克定理的适用条件又：

- 格点。

- 多边形的每一个顶点都在格点上。

$S$ 的话可以用海伦公式求，$b$ 就等于 $p+1+\gcd(n,m)+1+\gcd(|n-p|,m)+1-3$。也就等于：
$$p+\gcd(n,m)+\gcd(|n-p|,m)$$

![](https://cdn.luogu.com.cn/upload/image_hosting/7mpnas09.png)

$p+1$ 是 BC 边上的格点数，$\gcd(n,m)+1$ 是 AC 边上的格点数（看经过了几个最小矩形），$\gcd(|n-p|,m)+1$ 是 AB 边上的格点数（同理）。最后，因为三个顶点被多算了一次，减掉 3。

最后三角形内的格点数 $a$ 就是 $S-\dfrac{b}{2}+1$ 了。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,p,B;//B是边上的格点数
  double P,a,b,S;//P是半周长，S是面积
  double len(int x1,int y1,int x2,int y2){return sqrt(1.0*(x1-x2)*(x1-x2)+1.0*(y1-y2)*(y1-y2));}//求距离
  int main()
  {
      scanf("%d%d%d",&n,&m,&p);
      a=len(0,0,n,m);
      b=len(p,0,n,m);
      P=(a+b+p)/2.0;
      S=sqrt(P*(P-a)*(P-b)*(P-p));//海伦公式
      B=p+__gcd(n,m)+__gcd(abs(n-p),m);//上面讲过
      printf("%d",int(S+1-B/2.0+0.5));//反推a
      return 0;
  }
```

---

## 作者：Manjusaka丶梦寒 (赞：4)

定理什么的最讨厌了，匹克定理？不会，也不想学。

![那样例来看](https://cdn.luogu.com.cn/upload/pic/37383.png)

粉色的为电网，将图中的电网我们将他构造一个矩形，然后蓝色和绿色的的补齐。

那么我们的答案就是：矩阵中的点数- 蓝色三角形中的点数- 绿色三角形中的点数。

然后我们单独拿出一个三角形来考虑。

![](https://cdn.luogu.com.cn/upload/pic/37382.png)

从箭头(箭头呢？右上角那个点)开始向左考虑，

我们将这个三角形一点一点的扩大，看每次能覆盖几个点。

![](https://cdn.luogu.com.cn/upload/pic/37381.png)

随着h不断变大那么，不断有点被覆盖，那么不断加入的点的个数就是$$ \lfloor \frac{b}{a} \times x \rfloor +1 $$。

我们对每个三角形进行处理，然而不要忘记电网的下边缘哦。

最后你会发现有几个点重复处理了(电网下边缘的端点)，所以再+2就好了。

开不开long long 无所谓
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define LL unsigned long long
#define inf 2147483647
LL n,m,p,ans;
LL calc(double a,double b)
{
    if(a==0)return b+1;
    if(b==0)return a+1;
    LL sum=0;
    double h=b/a;
    for(LL i=0;i<=a;i++)
    {
        sum+=(LL)(h*double(i)+1);
    }
    return sum;
}
int main()
{
    cin>>n>>m>>p;
    ans=(max(n,p)+1)*(m+1);
//    cout<<ans<<"\n";
//    cout<<calc(n,m)<<" "<<calc(max(n,p)-min(n,p),m);
    ans-=calc(n,m);
    ans-=calc(max(n,p)-min(n,p),m);
    ans-=p;
    cout<<ans+2;
} 
```
最后[打波广告](https://www.cnblogs.com/rmy020718/p/9776916.html)。

---

## 作者：jiuguaiwf (赞：3)

这题17年7月写的了，最近写计算几何题，按难度排序，才猛然想起我曾做过她QwQ

题解区并没有不用皮克公式的O(logn)(gcd的复杂度)模拟，那我就来发下。

首先，一条连接(0,0)和(n,m)的直线我们可以拿gcd来计算线上的整点。而任意一个三角形都可以被分为一个或多个直角三角形。

### 两个直角三角形凑成一个矩形（点数直接n*m）

#### 小细节：两个直角三角形拼成矩形时，要先减去那条对角线（gcd）上的点再除以二才是一个三角形的点。(当然，n和m也要减去)。

#### 还有，如果是钝角三角形，那把他按直角三角形来算，最后再扣掉空白的三角形（查分思想）。

#### 犹记得当年这道毒瘤题困扰了我好久，~~用我的写法就是现在也要调好久细节啊，真的很毒瘤！~~，不过还是写出来了，大家努力想，努力写吧！ ~~不然就像我现在一样年迈弱小又无助~~

那时的码风挺鬼畜的说~

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iostream>

using namespace std;

int n,m,k,l,num,ans,q,p,ans1,ans2;



int GCD(int a,int b)
{
	if (a%b==0) return b;
	else
	{
		return GCD(b,a%b);
	}
}

int main()
{
	//freopen("fence9.in","r",stdin);
	//freopen("fence9.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	if  (n>p)//分三种情况啊，直角锐角钝角自有不同写法
	{
    num=(n+1)*(m+1);
	q=GCD(n,m);
	q=1+q;
	num=num-q;
	num=num/2;
	ans1=num;

    num=(n-p+1)*(m+1);
	q=GCD(n-p,m);
	q=1+q;
	num=num-q;
	num=num/2+q;
	ans2=num;
	ans=ans1-ans2-p+2;//鬼畜的细节
	printf("%d",ans);

	}
	if (n==p)
	{
      num=(n+1)*(m+1);
	  q=GCD(n,m);
	  q=1+q;
	  num=num-q;//直角三角形最好写啦！
	  num=num/2;
	  ans1=num-n-m+1;
	  printf("%d",ans1);

	}
	
	if (n<p)
	{
      num=(n+1)*(m+1);
      q=GCD(n,m);
      q=1+q;
      num=num-q;
      num=num/2;
      ans1=num-(n+1);

      num=(p-n+1)*(m+1);
      q=GCD(p-n,m);
      q=1+q;
      num=num-q;
      num=num/2;
      ans2=num-(p-n+1);
      ans=ans1+ans2-m+3;
      printf("%d",ans);
    }
	//while(1);
	return 0;
}

```
#### NOI2019 Bless All

---

## 作者：Law_Aias (赞：3)

##  一道校内模拟赛遇见的题
>> ** 不会正解就真的很麻烦的 _数学题_ **

### 有一种东西叫 **皮克定理** 
> **发现的千古神犇**：
>> 姓名：George Alexander Pick（~~所以叫**皮克定理**呀~~

>> 国籍：奥地利（~~蛤！竟然不是匈牙利。。。**逃**。。。~~

> **皮克定理是干蛤的**

>> 　　就是在一张网格纸上（对，就是网格纸，~~**关于SPFA，他，死了**~~），上面画着纵横两组平行线，相邻平行线之间的距离都相等，这样两组平行线的交点，就是所谓格点。如果取一个格点做原点O，取通过这个格点的横向和纵向两直线分别做X轴和Y轴，并取原来方格边长做单位长，建立一个坐标系。这时前面所说的格点，显然就是纵横两坐标都是整数的那些点。由于这个缘故，我们又叫格点为整点。

>> 　　一个多边形的顶点如果全是格点，这多边形就叫做格点多边形。有趣的是，这种格点多边形的面积计算起来很方便，只要数一下图形边线上的点的数目及图内的点的数目，就可用公式算出。

> **公式是啥？**
>> **公式**：2S = 2a + b - 2
 
>> 其中a表示多边形内部的点数，b表示多边形边界上的点数，S表示多边形的面积。

## ~~证明，不存在的。。。（光速逃离。。。~~

## 题解：
> 这题显然求的是a，2S可用m*p来求，b则用gcd来。

> 所以，反向套公式就完事了。。。

### CODE：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long

using namespace std;

inline ll gcd(ll x,ll y) {
	return x % y == 0 ? y : gcd(y,x % y);
}
ll n,m,p;

int main() {
	//freopen("fence.in","r",stdin);
	//freopen("fence.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&p);
	ll s = p * m / 2;
	ll cnt = (gcd(n,m) + gcd(abs(n - p),m) + p) / 2;
	ll ans = s - cnt + 1;
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Augen_stern (赞：3)

## Part 1：前置芝士

#### 1，Pick定理

   Pick 定理是指一个计算点阵中顶点在格点上的多边形面积公式，该公式可以表示为 $ S=a+b÷2-1 $，其中 a 表示多边形内部的点数，b 表示多边形落在格点边界上的点数，S 表示多边形的面积。
                                       
                                         ----百度百科
   
#### 2，扩展欧几里得

   在两整点 $ A ( x1,y1 ) $ 和 $ B ( x2,y2 ) $ 的线段中经过整点的个数为 $ gcd(| x1-x2 |,| y1-y2 |)+1 $。
   
   Tips: 
   
   1，整点是指横纵坐标均为整数的点；
   
   2，$ gcd(x,y) $ 是指 x 和 y 的最大公因数。
       
## Part 2：分析求解

铺垫了这么多，是时候进入正题。

看了看题目，“ 计算几何 ”映入脑海；

题目的大致意思就是在直角坐标系是有三个点，求其中的整点个数。

![如图](https://cdn.luogu.com.cn/upload/image_hosting/ida4w6iu.png)

所以 套上前置芝士的 Pick 就可以得到计算答案为

```cpp
int ans=m*p/2-(p+1+gcd(n,m)+1+gcd(abs(n-p),m)+1-3)/2+1
```

再加上最大公因数的辗转相除

```cpp
int gcd(int m,int n) {
	int r;
	while(n!=0) {
		r=m%n;
		m=n;
		n=r;
	}
	return m;
}
```

## Part 3：CODE

然后就可以轻松 AC 了

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int n,m,p;
int gcd(int m,int n) {
	int r;
	while(n!=0) {
		r=m%n;
		m=n;
		n=r;
	}
	return m;//辗转相除求最大公因数
}
int main() {
	scanf("%d%d%d",&n,&m,&p);
	printf("%d",m*p/2-(p+1+gcd(n,m)+1+gcd(abs(n-p),m)+1-3)/2+1);//Pick定理
	return 0;
}
```
自己动手，丰衣足食！



---

## 作者：voruala (赞：2)

### 题目概述

求三角形顶点为$(0,0)$、$(n,m)$和$(p,0)$的三角形内有多少整数点.

### 思路解析

![](https://cdn.luogu.com.cn/upload/image_hosting/zk8o7t6w.png)

分别对于每一行统计点的个数. 

对于第$i$行，计算在左边那条线上的坐标$(l,i)$：
$$
\begin{aligned}
\frac{l}{i}&=\frac{n}{m}
\\
l&=\frac{n\cdot i}{m}
\end{aligned}
$$
计算右边那条线上的坐标$(r,i)$：
$$
\begin{aligned}
\frac{r-p}{i-0}&=\frac{n-p}{m-0}
\\
r-p&=\frac{i\cdot (n-p)}{m}
\\
r&=p+\frac{i\cdot (n-p)}{m}
\end{aligned}
$$

那么最后答案应该大概是$\lfloor r \rfloor-\lceil l\rceil$.

```c++
double n,m,p;
cin>>n>>m>>p;
//line left (0,0)to(n,m)
//line right (p,0)to(n,m)
for(i=1;i<m;i++)
	l[i]=double(i)*n/m,
	r[i]=p+double(i)*(n-p)/m,
	ans+=dn(r[i])-up(l[i])+1;
cout<<ans<<endl;
```

$Ps.$需要格外注意$up$（向上取整）和$dn$（向下取整）函数

```c++
int up(double x)
{//无论在不在三角形的边上 都要往右一格
	return int(x)+1;
}
int dn(double x)
{//在三角形的边上不能取 往左一格
	if(x==int(x))
		return x-1;
	else//不在就直接找左边的点就可以
		return int(x);
 } 
```

### 完整代码

```C++
/*
ID: 
TASK: fence9
LANG: C++       
*/
#include</*头文件*/>
using namespace std;
const int N=32000+10;
double l[N];//虽然可以不用数组 但是我这么交了 
double r[N];//就懒得改了 
int ans=0;
int up(double x)
{//无论在不在三角形的边上 都要往右一格
	return int(x)+1;
}
int dn(double x)
{//在三角形的边上不能取 往左一格
	if(x==int(x))
		return x-1;
	else//不在就直接找左边的点就可以
		return int(x);
 } 
int main()
{
//	freopen("fence9.in","r",stdin);
//	freopen("fence9.out","w",stdout);
	int i,j;
	double n,m,p;
	cin>>n>>m>>p;
	//line left (0,0)to(n,m)
	//line right (p,0)to(n,m)
	for(i=1;i<m;i++)
		l[i]=double(i)*n/m,
		r[i]=p+double(i)*(n-p)/m,
		ans+=dn(r[i])-up(l[i])+1;
	cout<<ans<<endl;
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```

大佬轻喷$awa$如果有帮到你 给我个赞吧...嘿嘿 谢谢啦

---

## 作者：zplqwq (赞：2)

# USACO3.4 题解

一道非常不错的计算几何题qwq

## Part 1 前置芝士

这道题看很多人说可以暴力或者用计算几何，其实根本没有那个必要。

这道题其实就考了一个比较偏僻的芝士：**皮克定理**

根据百度百科：皮克定理是指一个计算点阵中顶点在格点上的多边形面积公式，该公式可以表示为$S=a+b÷2$$－1$，其中$a$表示多边形(内部的点数，$b$表示多边形落在格点边界上的点数，$S$表示多边形的面积。

感觉是不是有点懵？能理解。

解释一下：其实就只用数出不碰边界的，和在图形的边界的点就好了qwq。

那么问题来了：我们在这道题里面怎么使用皮克定理呢？

我们可以设直线(0，0)→(a,b)上的一点坐标为(x,x*a/b)(x<a),且这个点为整点,求符合条件的x的个数。

因此说白了就是正方向不停套公式就好了。

## PART 2 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,m,p;

const int N=10000010;

int a[N];


int main()
{
	cin>>n>>m>>p;//输入
	int ans=__gcd(n,m)+__gcd(abs(p-n),m)+p;//我就是懒容易禁赛别学我
    int sum=(p*m)/2;
    int ret=sum-ans/2+1;//公式
	cout<<ret<<endl; //输出
    return 0;
}

```





---

## 作者：QianhanOfficial (赞：2)

蒟蒻数学很差，于是只能想到通过斜率处理。  
发现各位题解都是使用了皮克定理等高端操作，于是本蒟蒻就来点相对暴力但是有效的方法。  
我的思路是处理出三角形两条斜边的斜率，然后分两种情况讨论：  

1. p>n 也就是两条边斜率一正一负。  
2. p<=n 也就是两条边斜率相同或者直角三角形。  

这样，我们可以得到两个一次函数 y = k1·x 和 y = k2·x 。然后我们枚举自变量x(x为自然数)，得出y的函数值并且下取整，这样得到的y就是每一条直线下面的格点数。  
但是对于在直线上的格点，我们不需要，所以如果是第一种情况下的在直线上的格点，我们就把y减一即可得到正确答案。最后把两条直线所得的答案相加即可。  
处理三角形顶点的时候加上m-1即可 注意n=0时不能加。  
对于第二种情况，y=k1·x上的格点需要减去 而另一条则不需要 因为我们得出答案是通过第一条答案减去第二条，减去的格点可以在第二条直线上。  
这样我们就用O(n)的复杂度解决了问题，最后提示一下精度问题，判断格点是否在直线上就看y原值-y整数部分是否为0即可，但是强制类型转换可能有偏差，所以使用<=0.00000001解决。  
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int n, m, p, sum, shit = 1;
double k1, k2, t, tmp = -1.0;
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	if(n == 0) k1 = 0.0, k2 = (double) m / (n - p);//防止除数为0，下同 如果n==0那么k1不会被计算到 同理n==p时k2也不会被计算 
	else if(n == p) k1 = (double) m / n, k2 = 0.0; 
	else k1 = (double) m / n, k2 = (double) m / (n - p);
	if(p > n)//第一种情况
	{
		for(int i = 1; i < n; ++i)//第一条直线
		{
			t = (double) k1 * i;
			if((double)(t - (int)t) <= 0.00000001) t -= 1.0;
			sum += (int) t;
		}
		if(n) sum += m - 1;//顶点
		for(int i = n + 1; i < p; ++i)//第二条
		{
			t = (double) k2 * (i - p);
			if((double)(t - (int)t) <= 0.00000001) t -= 1.0;
			sum += (int)t;
		}
	}
	else//第二种情况
	{
		for(int i = 1; i < n; ++i)//第一条
		{
			t = (double) k1 * i;
			if((double)(t - (int)t) <= 0.000000001) t -= 1.0;
			sum += (int) t;
		}
		for(int i = p + 1; i < n; ++i)//第二条
		{
			t = (double) k2 * (i - p);
			sum -= (int) t;//减去格点数
		}
	}
	printf("%d", sum);//输出答案。
	return 0;
}
```

---

## 作者：Celebrate (赞：1)

这一道题用皮克定理解就好了，虽然说我没有能力手推，但是在网上搜一下皮克定理就会了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int x,int y)//gcd 
{
	if(y==0) return x;
	else	 return gcd(y,x%y);
}
int main()
{
	int n,m,p,s,b,i;
	scanf("%d%d%d",&n,&m,&p);
    b=gcd(n,m)+gcd(abs(p-n),m)+p; //边上格点数目
	s=p*m/2;i=s-b/2+1;//面积 s=i+b/2-1
	printf("%d\n",i);
	return 0;
}
```

---

## 作者：Bzy_temp (赞：1)

/\*
看大家都在玩数学方法，那我就来个暴力吧，也挺短，O(m+|p-m|)还比较快
\*/
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//流操作命名空间
//特殊的除法//如果整除就减一
int dv(int a,int b){
    if(a%b==0)a-=1;
    return a/b>0?a/b:0;
}
//主函数
int main(){
    int a,b,c;cin>>b>>c>>a;int sum=0;//输入赋值
    for(int i=0;i<=b-1;i++)sum+=dv(i*c,b);if(b==0)sum=-c+1;//cout<<sum;//从1到m判断其下的点//特判b=0
    if(a<b)for(int i=a;i<=b-1;i++)sum-=c*(i-a)/(b-a);//如果a<b则减去另一条线下的点
    else for(int i=b+1;i<=a;i++)sum+=dv((c-c*(i-a)),(a-b));//如果a>=b则加上另一条线上的点
    cout<<sum;//输出
}
```

---

## 作者：zhzh2001 (赞：1)

# 整体思路

一开始并没有想到那个定理，尽管数学课都有。

我想到的方法是求出直线解析式，因为是三角形，且一边平行于x轴，分三种情况讨论。

1.p=n，此时为直角三角形，计算出x=[1,p)中整点的个数；

2.p>n，此时为锐角三角形，样例也是，把三角形分成两个直角三角形即可；

3.p<n，此时为钝角三角形，分成一个直角三角形和一个钝角三角形计算。


# 细节

至于如何计算整点个数，需要一个函数lw(x)，当x不为整数时等于floor(x)，否则等于x-1。

但是直接实现会有浮点误差，必须手写floor，代码中为fl(x)。


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
inline int fl(double x)
{
    int ans=floor(x);
    if(fabs(ans-x)>1-eps)
        ans++;
    return ans;
}
inline int lw(double x)
{
    int ans=fl(x);
    if(fabs(ans-x)<eps)
        ans--;
    return ans;
}
int main()
{
    int n,m,p;
    cin>>n>>m>>p;
    double k1=(double)m/n;
    int ans=0;
    if(p==n)
        for(int x=1;x<p;x++)
            ans+=lw(k1*x);
    else
    {
        double k2=(double)m/(n-p),b=-k2*p;
        if(p>n)
        {
            for(int x=1;x<=n;x++)
                ans+=lw(k1*x);
            for(int x=n+1;x<p;x++)
                ans+=lw(k2*x+b);
        }
        else
        {
            for(int x=1;x<=p;x++)
                ans+=lw(k1*x);
            for(int x=p+1;x<n;x++)
                ans+=lw(k1*x)-fl(k2*x+b);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Mine_King (赞：0)

这题需要用到皮克定理，皮克定理是说，对于一个所有顶点都在格点上的多边形，它的面积 $S=a+\frac{b}{2}-1$，其中 $a$ 表示这个多边形内部的格点数，而 $b$ 表示这个多边形边上的格点数。  
那么我们这题要求的是 $a$，转化一下上面的公式可以得到：$a=S-\frac{b}{2}+1$，于是问题转化成了如何求 $S$ 和 $b$。

先看图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/1yu8csj0.png)  
这里 $A$ 点为 $(0,0)$，$B$ 点为 $(n,m)$，$C$ 点为 $(p,0)$。

我们知道，三角形的面积 $S=\frac{1}{2}ah$，即底乘高。  
在上图中，如果选线段 $b$ 为低，那么高就是线段 $h$。所以 $a=p,h=m$，所以 $S=\frac{1}{2}pm$。  
而公式中的 $b$，可以分段求解。

在线段 $b$ 上的格点数为 $p+1$。  

有一个结论，就是对于一条两个端点的坐标分别为 $(x_1,y_1),(x_2,y_2)$ 的线段，在线段上的整点个数为 $\gcd(|x_2-x_1|,|y_2-y_1|)+1$。  
那么对应到途中，线段 $c$ 的整点个数为 $\gcd(n,m)+1$，线段 $a$ 上的整点个数为 $\gcd(|n-p|,m)+1$。

所以上面公式中的 $b=p+1+\gcd(n,m)+1+\gcd(|n-p|,m)+1-3=p+\gcd(n,m)+\gcd(|n-p|,m)$。这里需要 $-3$ 是因为三个顶点被算了两次，所以要减掉。

**Code：**

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,p,S,l;
int abs(int x){return x<0?-x:x;}
int gcd(int _a,int _b){return _b==0?_a:gcd(_b,_a%_b);}
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	S=m*p/2;
	l=gcd(n,m)+gcd(abs(n-p),m)+p;
	printf("%d\n",S-l/2+1);
	return 0;
}
```



---

## 作者：Tiffany_Tendering (赞：0)

1. 根据扩展欧几里得得知  两点之间的距离即为横纵坐标差（绝对值）的gcd
2. 匹克定理 在网格点中三角形的面积：
    2S = 2a + b - 2
    
    S为面积 a为图形内的点数 b为边上的点数
    
    我们只要根据这个定理逆用，推出以上式子的a即可
    


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,p ;

int gcd(int x,int y) {
	if(!y) return x;
	else return gcd(y , x % y) ;
}

int main() {
	scanf("%d%d%d",&n,&m,&p) ;
	int b = gcd(n , m) + 1 + gcd(abs(n - p) , m) + 1 + p + 1 - 3 ;
	int s = p * m / 2 ;
	int ans = s - b / 2 + 1 ;
	printf("%d",ans) ;	
	return 0;
}
```

---

## 作者：vinvor (赞：0)

可以算是一道数学题吧。如果知道皮克定理就行了。皮克定理说明了其面积S和内部格点数目a、边上格点数目b的关系：S=a+b/2-1。根据三角形面积公式求出S。如果知道了b，那么三角形内部格点数目a也就求出来了。可以证明，一条直线((0，0)，(n，m))上的格点数等于n与m的最大公约数+1。即b=gcd(n，m)+1.gcd(n,m)为n与m的最大公约数。代入皮克公式，即可求出a的值。下附代码：

```cpp
#include<iostream>
using namespace std;
int gcd(int x,int y)
{
    if (x>y) swap(x,y);
    if (x==0) return y;
    return gcd(y%x,x);
}
int main()
{
    int n,m,p,b=0,s;
    cin>>n>>m>>p;
    s=(m*p)/2;
    b+=gcd(n,m);
    if (n!=p) b+=gcd(abs(n-p),m);
    else b+=m;
    b+=p;
    cout<<s+1-(b/2)<<endl;
    return 0;
}
```

---

## 作者：zk1431043937 (赞：0)

代码巨短瞬间AC。

用皮克定理，对于格点多边形有2S=2a+b-2，其中S为多边形面积，a为图形内部格点，b为图形边上的格点。

这题显然求的是a，2S可用m\*p来求，b则用gcd来。

因为有一个点是(0,0)，所以(0,0)到(n,m)的点数（不包括原点）为gcd(n,m)，同理，(n,m)到(p,0)的点数为gcd(abs(n-p),m)（这里不包括(n,m)），然后加上(0,0)到(p,0)的p个点（不包括(p,0)），于是刚好无遗漏无重复地计算出b。

再用逆公式a=(2S-b+2)/2即可求解。

代码见下：

```cpp
program p2735;
  var n,m,p,a,b,s:longint;
function gcd(x,y:longint):longint;
  var r:longint;
begin
  r:=x mod y;
  x:=y;
  y:=r;
  if y=0 then exit(x) else exit(gcd(x,y));
end;
begin
  readln(n,m,p);
  s:=m*p;
  b:=gcd(n,m)+gcd(abs(p-n),m)+p;
  a:=(s-b+2) div 2;
  writeln(a);
end.
```

---

