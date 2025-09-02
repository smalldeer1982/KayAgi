# Amr and Pins

## 题目描述

Amr loves Geometry. One day he came up with a very interesting problem.

Amr has a circle of radius $ r $ and center in point $ (x,y) $ . He wants the circle center to be in new position $ (x',y') $ .

In one step Amr can put a pin to the border of the circle in a certain point, then rotate the circle around that pin by any angle and finally remove the pin.

Help Amr to achieve his goal in minimum number of steps.

## 说明/提示

In the first sample test the optimal way is to put a pin at point $ (0,2) $ and rotate the circle by $ 180 $ degrees counter-clockwise (or clockwise, no matter).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507B/a26ac87b2d0412fb38dc1bc7b7b71315dcd60080.png)

## 样例 #1

### 输入

```
2 0 0 0 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 1 1 4 4
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 5 6 5 6
```

### 输出

```
0
```

# 题解

## 作者：张心博harry (赞：7)

### CF507B Amr and Pins 题解

[题目传送门](https://www.luogu.com.cn/problem/CF507B)

------------

### 大体思路：



#### 第一步：

如何求移动次数？

我们为了步伐更大，我们每次将定点定在圆周上。

如图，从 $A$ 至 $B$ 点，点 $C$ 是定点（借用大佬 @CharlesZiy 的图）

![image.png](https://s2.loli.net/2022/08/19/vm7FHpIn1Z2eNcX.png)

那么，结果显而易见，答案就是点 $A$ 和点 $B$ 的距离除以 $r\times2$ 的积并向上取证。

因为圆每次最圆移动 $r\times2$ 个坐标，两点之间直线最近，只需令圆沿两点之间的直线走，在终点进入圆内时，微调一次就好了。因为要微调，所以我们需要向上取整。

那么，现在问题又来了，怎么求两点之间的距离呢？

#### 第三步：

这里需要用到[勾股定理](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E5%AE%9A%E7%90%86/91499?fr=kg_general)。

如下图，圆心是 $A(x,y)$，终点是 $B(x',y')$。

![image.png](https://s2.loli.net/2022/08/19/QlaOvgUoz7yXeFJ.png)

由勾股定理可知，$a^2+b^2=c^2$，边 $a$ 显然是 $y'-y$，边 $b$ 显然是 $x'-x$,那么边 $c$ 便是 $\sqrt{(y'-y)^2+(x'-x)^2}$。

#### 总结：

我们把刚刚说的那么多总结起来，那么答案就是：

$ans=\lceil\sqrt{(y'-y)^2+(x'-x)^2}\div(r\times2)\rceil$


-------------

### 代码：

```
//这里为了便于理解，我把上面的算式分开来写。
#include<iostream>
#include<cmath>
using namespace std;
long long pf(long long x){ //求平方。
	return x*x;
}
int main(){
	long long r,x,y,x1,y1;
	cin>>r;
	long long zj=2*r;
	cin>>x>>y>>x1>>y1;
	double wy=0;
	wy=pf(y1-y)+pf(x1-x);//如果相减是负数也不用管，一平方就变正数了
	wy=sqrt(wy); //wy 是两点间距离的平方，所以还要再求一次根。
	wy=wy/(2*r);
	long long ans=ceil(wy); //ceil 向上取整。
	cout<<ans<<endl;
	return 0;
}
```

---------------

$END$

---

## 作者：CharlesZiy (赞：3)

### 写在前面

期末考试回来随机一道题，然后开屏雷击（~~指题号~~）。

这题是真简单 细节是真的多。本题解主要面向写题时由于一些细节而卡住的同学们。

### 思路

我们要考虑一个问题：如果要使移动步数最小，那么我们应该怎么移动？

显然，在下图情况下能使步长最长，相应的步数就最小，此时步长为圆的直径。

[![jTl2TA.png](https://s1.ax1x.com/2022/07/19/jTl2TA.png)](https://imgtu.com/i/jTl2TA)

$$\tiny\text{令圆半径为 }r$$

如果在若干次如上图的移动之后，圆心距离目标点的距离小于圆的直径，那么我们显然只需要再进行一次移动进行微调即可。具体地，在代码中体现为使用 `ceil` 进行上取整。

那我们如何计算两个点之间的距离呢？根据勾股定理变形式 $c=\sqrt{a^2+b^2}$ 可得，若两点坐标为 $(x_1, y_1)$ 和 $(x_2, y_2)$，这两点间距离为：

$\begin{aligned}d&=\sqrt{(|x_1-x_2|)^2+(|y_1-y_2|)^2}\\&=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\end{aligned}$

那么，结合上面的推导，我们可以推出最终的答案为 $\left\lceil\dfrac{d}{2r}\right\rceil$。

知道这些，让我们开始动笔吧。

### 代码实现 & 调试

关注数据范围，极端情况存在 $4\times10^{10}$ 的运算，肯定会爆 `int`，考虑使用 `long long`。

需要注意的是，在 C++ 中加法符号和乘法符号同级，默认从左向右运算。所以在利用上面的公式计算距离的时候要注意添加括号，不然有可能会出现对负数开平方的情况。

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

long long r, x, y, xx, yy, leap;

double dis(long long x, long long y, long long xx, long long yy)
{
	return sqrt(((x - xx) * (x - xx)) + ((y - yy) * (y - yy)));
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin >> r >> x >> y >> xx >> yy;
	
	leap = 2 * r;
	
	if (x != xx || y != yy) cout << ceil(dis(x, y, xx, yy) / leap) << endl;
	else cout << 0 << endl;
}
```

然后本题就算结束了。如果感觉写的好的话能点个赞吗QwQ。

---

## 作者：a_123_a (赞：1)

### 我们需要知道的
在笛卡尔坐标系，利用欧几里得距离公式对于 $ (x,y) $，$ (x_1,y_1)$ 这两个点的距离 $d = \sqrt{(x-x_1)^2+(y-y_1)^2}$


### 思路

根据题意我们知道，一个圆的圆心至多可以移动 $ 2R $ 个单位长度。可以推出旋转的次数最小就是圆心移动的距离最小，所以我们可以利用欧几里得距离公式得出圆心需要移动的最小距离。用最小距离 $ d $ 来除以 $ 2R $ 向上取整就是本题的答案了。
```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define intl long long
intl r,x,y,x1,y1;
double d;
int main(){
	cin>>r>>x>>y>>x1>>y1;
	d=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
	cout<<ceil(d/(2*r));
	return 0;
}
```

---

## 作者：_ayaka_ (赞：1)

### 思路
首先我们可以选择圆内任何一个点转动任意角度，那么每一次旋转后圆心可到达的点就是以当前圆为圆心，以 $2r$ 为半径所画出的圆中所覆盖的所有位置。

那我们只需要朝着目标点的方向保持最大移动的距离 $2r$ 一直转到距离小于等于 $2r$，再转一次就可以了。

假设圆心 $(x,y)$ 距离目标点 $(x',y')$ 的距离为 $d$，那么我们的答案便就是这个：

$$ ans=\lceil \frac{d}{2r} \rceil  $$

现在我们的目标就是求出 $d$ 了。我们可以使用欧几里得距离公式，它的作用就是求出坐标系上的两点之间的距离。这个公式是这样的：

$$d=\sqrt{(x-x')^2+(y-y')^2}$$

然后我们就解决了此题！

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int r,x,y,X,Y;
double d;
signed main(){
	cin>>r>>x>>y>>X>>Y;
	d=sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
	cout<<ceil(d/r/2);
	return 0;
}

```

---

## 作者：Igallta (赞：1)

前置芝士：勾股定理（欧几里得距离公式）。

通过说明我们不难发现每次最大可以移动 $2r$ 的距离。

也就是说我们只需要求出距离，然后：$\lceil len \div 2r\rceil$ 不就行了吗？

距离怎么求：使用勾股定理就可以了。式子：$\sqrt{(x-x')^2+(y-y')^2}$。

```cpp
#include <bits/stdc++.h>
#define LL k<<1
#define RR k<<1|1
#define int long long
using namespace std;
double r,x,y,xx,yy;
signed main() {
	cin>>r>>x>>y>>xx>>yy;
	double len=sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
	cout<<ceil(len/(r*2));
	return 0;
}
```

---

## 作者：hhh_778899 (赞：1)

## 思路

- 我们先用两点间距离公式 $d=\sqrt{{(x-x')}^2+{(y-y')}^2}$ ，可以求出点 $(x,y)$ 到点 $(x',y')$ 的距离。

- 由于每次圆心移动的最大距离为圆的直径，即 $2r$ ，可以求出移动次数 ( 注意向上取整 ) ：

$$ans=\left\lceil\dfrac{d}{2r}\right\rceil$$

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	long long r,x_1,y_1,x_2,y_2;//本题有乘法运算，只能开long long
	cin>>r>>x_1>>y_1>>x_2>>y_2;
	double d=(x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2);
	cout<<ceil(sqrt(d)/(2*r));//使用ceil函数向上取整
	return 0;
}
```


---

## 作者：Fearliciz (赞：1)

~~这道题原本以为是一道毒瘤数学题，仔细想想才发现其实很水。~~

思路：

先用距离公式求两点的距离。

两点之间距离公式：$\sqrt{(x1 - x2)^2+(y1 - y2)^2}$

接下来，求这个距离要几个直径（因为每转一次，圆心最多移动一个直径）。

最后，如果还有多余距离，答案取 $\texttt{ceil}$。

所以代码也很简洁：

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

double cul(long long x1, long long y1, long long x2, long long y2) {
	return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))); //距离公式
}

int main() {
	long long r, x1, y1, x2, y2;
	cin >> r >> x1 >> y1 >> x2 >> y2;
	long long d = 2 * r;
	if (x1 == x2 && y1 == y2)
		cout << 0;
	else
		cout << ceil(cul(x1, y1, x2, y2) / d);
	return 0;
}
```


---

## 作者：CSP_Sept (赞：1)

### Description

给定一个半径为 $r$ 的圆，圆心在 $(x,y)$ 处。每次可以把圆固定在圆内的某点选择任意度数，使圆心移动到 $(x',y')$ 处。求最小旋转次数。

### Solution

首先不难发现，这个点必须得选在圆上，且得旋转 $180\degree$。

如下图，此时移动距离为 $2\cdot r$。

![rL1SmD.png](https://s3.ax1x.com/2020/12/30/rL1SmD.png)

而 $(x,y)$ 到 $(x',y')$ 的距离 $d$ 直接用勾股定理就可以求出。所以答案为

$$
\left\lceil\dfrac{d}{2r}\right\rceil
$$

### Code

[Link](https://codeforces.com/contest/507/submission/102735545)

---

## 作者：CaoSheng_zzz (赞：0)

### 前置知识
在笛卡尔坐标系，利用欧几里得距离公式对于 $ (x_1,y_1) $ 与 $ (x_2,y_2) $ 这两个点的距离为 $ \sqrt{({x_1-x_2})^2+(y_1-y_2)^2} $。
### 思路
根据题意我们可以推出旋转的次数最小就是圆心移动的距离最小，所以我们可以根据上面的公式得出移动的最小圆心移动的最小距离。用最小距离来除以 $ D $ 也就是 $ 2R $ 向上取整就是本题的答案，因为圆心移动的最长距离就是直径。

---

## 作者：National_Studying (赞：0)

### 前置芝士
欧几里得距离：$d=\sqrt{{(x_1-x_2)}^2+{(y_1-y_2)}^2}$。半径：$r$，直径：$d$。

### 思路
圆上任意一点，进行旋转，这个点距离开始的圆心是一条 $r$，而距离新的圆心还是一条相同的 $r$，所以总距离等于两条 $r$，即一条 $d$。

#### 况一
两个点在同一线上，即 $x = x^{'}$ 或 $y = y^{'}$，距离为坐标差。
#### 况二
两点不在同一线上，用欧几里得距离求出。

- 综上：$ans=\lceil\sqrt{{(x_1-x_2)}^2+{(y_1-y_2)}^2} \div d\rceil$。

注：全局开 double。

Code：
```
#include <bits/stdc++.h>
typedef int intt;
#define int double

using namespace std;
int r, x, y, xx, yy;
intt main() {
	ios::sync_with_stdio(0);
	cout.tie(0), cin.tie(0);

	cin >> r >> x >> y >> xx >> yy;
	int pos = sqrt((xx - x) * (xx - x) + (yy - y) * (yy - y));
//	cout << pos << "&&&&&\n";
	cout << ceil(pos / (r * 2));
	return 0;
}
```

---

## 作者：_iridescent (赞：0)

### 思路

根据题面下方说明里面的那张图，我们不难发现：圆心每次可移动的最长距离就是 $2r$。具体可以详见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jnnvpaor.png)

知道了这一点后，这道题就变得简单了很多，我们只需要计算出两点之间的直线距离就可以了。

那么，如何求平面直角坐标系内任意两点的距离呢？答案当然是使用欧几里得距离公式了。

若设两点的坐标分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$，则两点之间距离 $d$ 与其的关系如下：

$$ d=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2} $$

所以可以得到：

$$res=\lceil \frac{d}{2r} \rceil$$

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int r,x,y,xx,yy;
signed main(){
	cin>>r>>x>>y>>xx>>yy;
	double l=sqrt((xx-x)*(xx-x)+(yy-y)*(yy-y));
	cout<<ceil(l/(r*2))<<endl;
	return 0;
} 
```

---

## 作者：KevinHu0402 (赞：0)

这道题本质上就是一道数学题，只需要按照题目要求一句一句写就行了。

首先，大家应该都知道两点间距离公式吧，我们要先将移动前和移动后的两点间距离算出来，这里我存到了变量 dis 中。（注意：这道题数据都要用 **double** 存储）

然后，一步步增加步数，判断此时圆能否到达目标位置，如果到达则退出循环，输出结果。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    double r,x,y,x1,y1;
    cin >> r >> x >> y >> x1 >> y1;//圆半径，圆坐标，移动后坐标 
    double dis = (x - x1) * (x - x1) + (y - y1) * (y - y1);//两点间距离公式 
    dis = sqrt(dis);
    double i = 0;
    while((i * r) < dis / 2)
	i++;
    cout << i << endl;
    return 0;
}
```

~~求管理员通过！！~~

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF507B)
# 思路
对于起始的圆和终点的圆，只有两种情况：

- 两圆相交，圆的距离小于等于直径。那么任选一点，旋转一次即可完成。
- 两圆相离，圆的距离大于直径。每次翻转可以拉近一个直径的距离。

设两圆的距离为 $x$，两点坐标为 $(a1,b1)$ 和 $(a2,b2)$，则 $x= \sqrt{(a1-a2)^2+(b1-b2)^2}$。

即要旋转的次数为 $\lceil x\div (r \times 2) \rceil$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long r,a1,a2,b1,b2;//注意long long
double x;
signed main(){
    cin>>r>>a1>>b1>>a2>>b2;
    x=sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));
    cout<<ceil(x/(r*2)); 
    return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你一个初始位置在 $x_1,y_1$，半径为 $r$ 的圆，请问，每次选取圆上的一点并围绕其旋转任意度数，最少需要多少次才能转到终点 $x_2,y_2$？

# 解法分析

其实特别简单，就是一个障眼法。

假想有一个起始的圆和一个在终点的圆，那么每一次分两种情况：

1. 暂时还没有交点。
2. 已经有了至少一个交点。

对于第一个情况，两圆是相离的，即 $D>R\times2$，这时转一次一定无法重合，那么我们在两圆圆心的连线与当前圆的交点处翻转半圈，就可以将他们的距离缩短 $R\times2$。

对于第二个情况，即 $D\leq R\times2$，在它们的任意一个交点旋转适当角度就可以使得圆心重合，即达成目标。

综上，我们得到移动的步数为 $\lceil D\div(R\times2)\rceil$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int r,a,b,c,d;
	cin>>r>>a>>b>>c>>d;
	double dis=sqrt((a-c)*1ll*(a-c)+(b-d)*1ll*(b-d));
	cout<<ceil(dis/(r*2))<<endl;
	return 0;
} 
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
一道数学题。
## 分析。
首先，我们要知道这个题的本质含义。

我们要在**圆内**找一点，使原先的圆心移动到新的一点上，所以我们要缩短这两个点的距离，并且使旋转次数最少。所以我们在最开始，即圆心与要求的目标之间的距离等于或大于圆的直径，我们就可以在**圆上**找到一个点进行旋转，从而使旋转次数尽可能小，在最后小于直径时，进行微调即可。

关于为什么与直径作比较，我们可以这样理解：在圆上找到一点后，进行旋转，这个旋转中心点距离开始的圆心是一条半径，而距离新的圆心还是一条半径，所以总距离就是两条半径，即一条直径。

那么，我们可以先求出圆心与目标点的距离，然后除以直径。如果不能整除，那说明最后在圆内有一点，通过一次旋转后即可到达目标点，故需要向上取整。

圆心与目标点的距离可以通过二维中的欧几里得距离求解。欧几里得距离公式可以通过勾股定理得证。

综上所述，公式为：  
$ans = \left\lceil \sqrt{\left(x'- x\right)^2 + \left(y' - y\right)^2} \div \left(r \times 2 \right)\right\rceil$。

代码如下：仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
ll r,x,y,xx,yy,d;
double js(ll a,ll b,ll c,ll d){
	return sqrt(((a-c)*(a-c))+((b-d)*(b-d)));
}
int main(){
	cin>>r>>x>>y>>xx>>yy;
	d=2*r;
	if(x==xx&&y==yy) cout<<"0\n";
	else cout<<ceil(js(x,y,xx,yy)/d)<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

