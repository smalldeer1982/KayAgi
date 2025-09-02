# [BalticOI 2012] 移动网络 (Day1)

## 题目描述

有一条线段与若干个点，求线段上的点离最近的点最远的距离。

## 说明/提示

**【样例解释】** 

距离最远的点在两个点的中垂线与线段的交点处。

**【数据范围】**

- 对于 25% 的数据，满足 $n \leq 5000$
- 对于 50% 的数据，满足 $n \leq 10^5$
- 对于 100% 的数据，满足 $1\leq n \leq 10^6$，$1 \leq l \leq 10^9$，$-10^9 \leq x_i,y_i \leq 10^9$

**【说明】**

译自 [BalticOI 2012 Day1 T2. Mobile](http://www.boi2012.lv/data/day1/eng/mobile.pdf)

## 样例 #1

### 输入

```
2 10
0 0
11 1```

### 输出

```
5.545455```

# 题解

## 作者：Raymondzll (赞：1)

## P7249 移动网络

在后面的叙述中，圆的横坐标就是它的圆心的横坐标，左右端点就是和 $x$ 轴左边或右边的交点。

### 解题思路

点开题目，看到了“线段上的点离最近的点最远”。

典型二分，二分的就是这个求的答案（距离），因为它有单调性。

然后考虑 ```check``` 函数怎么写。**如果线段上有一个点和所有给定点的距离都大于等于 ```mid```，那么答案一定大于等于 ```mid```。**

换句话说，以每个给定点为圆心，```mid``` 为半径作圆，把线段的一部分覆盖掉，如果线段还有未被覆盖的部分，那么答案要往大了取。

一堆线段能否覆盖一条大线段，看起来要排序……真的要吗？

>给出点的坐标以横坐标为第一关键字，纵坐标为第二关键字升序排序。

好家伙，还有个条件没用！

![](https://cdn.luogu.com.cn/upload/image_hosting/dpy18zzs.png)

如图，横坐标相同时，纵坐标大的完全没用。

所以只考虑相同横坐标时纵坐标绝对值小的点。

如果全程没有空白，相安无事。

而如果有空白，横坐标大的点的圆如果能帮前面的圆填补空白，那么它的右端点一定不会比前面所有圆的右端点的最大值更小。

下面给出解释。

设这个填补了空白的圆为圆 M，圆 N 是创造空白的那个圆及其后面的圆中的一个。

因为圆 N 不能填补空白，~~所以它太逊了。~~ 所以它们的左端点没有圆 M 的左端点小。又因为圆 M 的横坐标更大，所以它的右端点一定更大。

所以用圆 M 的右端点更新最大连续覆盖的右端点一定不会更劣。

![](https://cdn.luogu.com.cn/upload/image_hosting/pd85fv0s.png)

如图，假设红色的是被填补的空白，则圆 B 的右端点比圆 A 的大。

如果有空白但不能（完全）覆盖，就不更新最大覆盖右端点，直到出现了可以完全填补空白的圆，再根据上面的解释，把最大覆盖右端点更新。

去掉了使复杂度变得垃圾的排序以后，时间复杂度降为 $O(n\times \log(\frac{10^9}{eps}))$。

如果还有不明白，最好是私聊，或者评论区。

### 代码部分

```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps=0.0003;
int n,l;
int x[1000010],y[1000010];
bool check(double mid){//1表示线段上至少有地方满足ans>mid（即未完全覆盖），0反之
	double maxx_covered_right=0;
	for(int i=1;i<=n;i++){
		double del=sqrt(mid*mid-1.0*y[i]*y[i]);//勾股定理（八年级上）
		if(x[i]-del<=maxx_covered_right&&x[i]+del>=maxx_covered_right)//垂径定理（九年级下）
		maxx_covered_right=x[i]+del;
	}
	return maxx_covered_right<l;
}
int main(){
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	double lef=0,rig=1414213562.374,mid;
	while(rig-lef>=eps){
		mid=(lef+rig)/2;
		if(check(mid))lef=mid;
		else rig=mid;
	}
	printf("%.5lf",lef);
	return 0;
}
```

### 慢！

代码中还有两处解释一下。

```rig=1414213562.374``` 这是什么鬼？

这里@_lyx1311 大佬提到了最大答案可能是 $\sqrt2\times 10^9$，详见[这里](https://www.luogu.com.cn/discuss/398181)。

```const double eps=0.0003;``` 数值有什么讲究吗？

没有，但是设置得太大会 $WA$，太小会 $TLE$（时限只有 $600ms$），所以折中取 $0.0003$。

---

## 作者：Azazеl (赞：1)

#### 2022.11.8 Update

$~~~~$ 修正了二分上界的问题，应该为 $\sqrt{5}l$ 及以上。


#### 题意
> $~~~~$ 有一条从 $(0,0)$ 到 $(0,l)$ 的线段与 $n$ 个点，找到线段上的一个点使其离平面给定的所有点最小距离最大。求这个最大距离。  
> $~~~~$ $1\leq n \leq 10^6$

#### 题意

$~~~~$ 看到最小距离最大可以想到二分。

$~~~~$ 对于某个二分的距离，则当线段能被 所有平面上的点以该距离作圆覆盖时 该距离是合法的。由圆方程可以解出一个圆心为 $(x,y)$ ，半径为 $r$ 的圆与 $x$ 轴的交点横坐标为 $\pm\sqrt{r^2-y^2}+x$ 。

$~~~~$ 按照正常思路我们就需要对区间进行排序然后 $O(n)$ 判定是否能覆盖整条线段，但这样复杂度就达到了 $\mathcal{O(n \log \dfrac{\sqrt{5}l}{\epsilon}\log n)}$ ，再考虑时限比较紧，显然需要优化。

$~~~~$ 细想发现我们还有给定的坐标横坐标、纵坐标依次递增的性质没用到。若依次考虑，当 $x$ 相同时，显然 $|y|$ 最小的那个点最可能更新覆盖区间的右端点。然后考虑横坐标不同的三个点 $p_1,p_2,p_3$ ，如果 $p_1$ 与 $p_2$ 画出的圆没有相交，但与 $p_3$ 画出的圆相交，则显然 $p_3$ 的右端点也会比 $p_2$ 的右端点更靠右，也就是 $p_3$ 更新的区间会比 $p_2$ 更优，因此不用排序也是正确的。因此我们就去掉了 $\log n$ 的复杂度。

#### 代码
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,L;
int X[1000005],Y[1000005];
bool check(double r)
{
	double x=0,From,To;
	for(int i=1;i<=n;i++)
	{
		From=-sqrt(1.0*r*r-1.0*Y[i]*Y[i])+X[i];
		To=sqrt(1.0*r*r-1.0*Y[i]*Y[i])+X[i];
		if(From<=x&&x<=To) x=To;
	}
	return x>=L;
}
int main() {
	scanf("%d %d",&n,&L);
	for(int i=1;i<=n;i++) scanf("%d %d",&X[i],&Y[i]);
	double l=0,r=2236068000,mid,Ans;
	while(r-l>0.0005)
	{
		mid=(l+r)/2;
		if(check(mid)) r=mid,Ans=mid;
		else l=mid;
	}
	printf("%.6f",Ans);
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

### 题目大意

有一条线段与若干个点，求线段上的点离最近的点最远的距离。

### 题目分析

最小值的最大值，一看就是~~模拟退火~~二分。（模拟退火只能拿 $9$ 分）。

二分最远距离。我们需要判定该答案是否合法。

一种有效的方式是，我们可以把每个点为圆心，$\mathrm{mid}$ 为半径作圆。我们可以看一下所有圆是否可以将整条线段覆盖。由于输入数据已经按照 $x$ 排序，而每个圆的半径又相同，可以按照输入顺序不断更新覆盖右端点。

如何求圆和直线的交点呢？前两天才学解析几何，我过来浅用一下。对于圆心位于 $(a, b)$ 的圆，半径为 $r$，其参数方程为 $$(x - a)^2 + (y - b)^2 = r ^ 2$$

它与 $x$ 轴的交点即当 $y = 0$ 时 $x$ 的解。将 $y = 0$ 带入方程得。

$$(x - a)^2 + b^2 = r^2$$

$$x^2 - 2ax + a^2 + b^2 - r^2 = 0$$

$$\Delta = 4a^2 - 4(a^2 + b^2 - r^2) = 4(r^2 - b^2)$$

$$x = \dfrac{2a \pm \sqrt{4(r^2 - b^2)}}{2} = a \pm \sqrt{r^2 - b^2}$$

（当然你也可以直接垂径定理）。

剩下没什么好分析的了，时间复杂度 $O(n \log \dfrac{w}{eps})$，$\max w = 10 ^ 9$。

### 代码示例

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#define x first
#define y second
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define dop(i, a, b) for (int i = (a); i > (b); i -- )

using namespace std;

using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using PDD = pair<double, double>;

const int N = (int)1e6 + 10;
const double eps = 1e-4;
PDD p[N]; int n, m;
double ans = 0;

bool check(double r) {
	double last = 0;
	rep(i, 1, n) {
		double x0 = p[i].x - sqrt(r * r - p[i].y * p[i].y), x1 = -x0 + 2 * p[i].x;
		if (x0 < last && x1 > last) last = x1;
	}
	return last >= m;
}

double binary_search(double l, double r) {
	if (fabs(r - l) < eps) return l;
	double mid = (l + r) / 2;
	if (check(mid)) return binary_search(l, mid);
	return binary_search(mid, r);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ )
		scanf("%lf%lf", &p[i].x, &p[i].y);
	
	printf("%.6lf\n", binary_search(0, 1414000000));
	return 0;
}
```

好像可以再优化，但是不想写了。

---

## 作者：qzilr (赞：0)

#### 题目描述
- 给定一条线段和若干点，在线段上找一点，使它到最近点的距离最远

#### 题目分析
一般看到这种最小值最大就可以往二分答案上猜了 ~~（虽然 Kruskal 重构树也是最小值最大）~~。

进一步分析题目容易看出答案具有单调性，对于一个满足答案的距离 $pos$，小于等于 $pos$ 的答案显然也可以，所以我们考虑二分答案。

假设当前的答案为 $ans$，题目等价于以每个点为圆心，$ans$ 为半径的圆与所给线段是否有交集。我们可以将其转化成点到线段的距离是否小于等于 $ans$，这就变成了一个基础的计算几何问题，分类讨论一下是垂直距离还是到端点的距离就行了。

点到直线垂直距离：
$$dis = \frac{\left|Ax_{0}+By_{0}+C\right|}{\sqrt{A^{2}+B^{2}}}$$
点到直线端点距离公式：
$$dis = \sqrt{(x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2}}$$

---

## 作者：lnwhl (赞：0)

## 题目大意
有一条从 $(0,0)$ 到 $(0,l)$ 的线段与 $n$ 个点，找到线段上的一个点使其离平面给定的所有点**最小距离最大**。求这个最大距离。$1\leq n \leq 10^6$
## 解法
很一眼的二分答案。

容易发现，每个站点覆盖的区域都可以抽象为一个**线段**。
> 根据勾股定理可以得知，一个点 $(x,y)$ 在覆盖半径为 $len$ 的情况下覆盖范围时从 $(x-\sqrt{len^2-y^2},0)$ 到 $(x+\sqrt{len^2-y^2},0)$

```check``` 时只需判断这些线段能否将整个大线段覆盖。

所有站点输入时已经有序，可以发现按照输入顺序贪心选择线段并不断更新右端点一定正确，这样就可以省去排序的复杂度。

总复杂度为 $O(n\log(\frac{l}{eps}))$，卡一卡就能通过此题。（但要注意精度问题，$eps$ 过大会 $TLE$，过小会 $WA$）
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,l,a[1000005],b[1000005];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool check(double len)
{
	double now=0;
	for(int i=1;i<=n;i++)
	{
		double dis=sqrt(len*len-1.0*b[i]*b[i]);
		double lft=a[i]-dis,rht=a[i]+dis;
		if(lft<=now&&now<=rht)now=rht;
	}
	return now>=l;
}
int main()
{
	n=read(),l=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=read();
	double l=0,r=1414213562.374,mid;
	while(r-l>=0.0003) 
	{
		mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.5lf",l);
	return 0;
}
```
------------
这道题其实还有一个 $O(n)$ 的算法，大体的的思路就是扫一遍，，一边扫一遍更新答案。有空补上~~~

---

## 作者：Aurora_Borealis_ (赞：0)


一眼的二分答案题。

容易发现，每个站点覆盖的区域都可以抽象为一个线段，$ check $ 时只需判断这些线段能否将整个大线段覆盖。

我们直接对所有小线段排序，然后贪心地选择。

所有站点输入时已经有序，可以发现按照输入顺序贪心一定正确，这样就可以省去排序的复杂度。


总复杂度为 $ O(n\log n) $，已经能通过此题。 

---

