# Constellation

## 题目描述

Cat Noku has obtained a map of the night sky. On this map, he found a constellation with $ n $ stars numbered from $ 1 $ to $ n $ . For each $ i $ , the $ i $ -th star is located at coordinates $ (x_{i},y_{i}) $ . No two stars are located at the same position.

In the evening Noku is going to take a look at the night sky. He would like to find three distinct stars and form a triangle. The triangle must have positive area. In addition, all other stars must lie strictly outside of this triangle. He is having trouble finding the answer and would like your help. Your job is to find the indices of three stars that would form a triangle that satisfies all the conditions.

It is guaranteed that there is no line such that all stars lie on that line. It can be proven that if the previous condition is satisfied, there exists a solution to this problem.

## 说明/提示

In the first sample, we can print the three indices in any order.

In the second sample, we have the following picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF618C/221daa860cc5914a84b65151dd3afba0407aed90.png)Note that the triangle formed by starts $ 1 $ , $ 4 $ and $ 3 $ doesn't satisfy the conditions stated in the problem, as point $ 5 $ is not strictly outside of this triangle (it lies on it's border).

## 样例 #1

### 输入

```
3
0 1
1 0
1 1
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
5
0 0
0 2
2 0
2 2
1 1
```

### 输出

```
1 3 5
```

# 题解

## 作者：封禁用户 (赞：5)

## 题解：CF618C Constellation

### 解题思路

虽然标签和其余题解说这是一道**构造**题，但是经过实践，我发现这道题可以用**贪心**解决，而且常数复杂度优秀。

因为所有点不都在一条直线上，所以每个点**必有至少一个合法三角形**，由此，我们可以先固定第一个点为我们选取的一个点。

因为固定了一个点的三角形如果内部仍然有点，那么连接到内部的点一定会使三角形面积变小，所以我们只需挑选让三角形最小的另外两个端点。

所以，我们可以先挑出离 $1$ 号点最近的点（后面称之为 $2$ 号点），然后再对剩余所有点进行排序，排序的依据是：离 $1$ 号点的距离和离 $2$ 号点的距离中的最小值更小的优先。

最后，我们要使用**斜率**知识，保持这三个点不在一条直线上（$1$ 号点与 $2$ 号点的斜率和 $2$ 号点与 $3$ 号点的斜率不相等）

我们在输出时并不是输出这几个点的编号，而是输出这几个点在输入时的位置。

**注意：算斜率时要使用交叉相乘，而不要直接除，容易发生 division by $0$ 错误，导致 $\text{RE}$。**

### 附：

交叉相乘后斜率的算法：

如果 $(x_2-x_1)\times(y_3-y_2)$ 与 $(x_3-x_2)\times(y_2-y_1)$ 相等，那么 $x_1,x_2,x_3$ 在同一条直线上。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p
{
	long long x , y , z , q;
}a[100005];
long long n;
bool cmp(p l , p r)
{
	return l.z < r.z;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i].x >> a[i].y;
		a[i].z = (a[i].x - a[1].x) * (a[i].x - a[1].x) + (a[i].y - a[1].y) * (a[i].y - a[1].y);
		a[i].q = i;
	}
	sort(a + 1 , a + n + 1 , cmp);
	for(int i = 1 ; i <= n ; i++)
	{
		a[i].z = min((a[i].x - a[1].x) * (a[i].x - a[1].x) + (a[i].y - a[1].y) * (a[i].y - a[1].y) , (a[i].x - a[2].x) * (a[i].x - a[2].x) + (a[i].y - a[2].y) * (a[i].y - a[2].y));
	}
	sort(a + 1 , a + n + 1 , cmp);
	for(int i = 3 ; i <= n ; i++)
	{
		if((a[2].x - a[1].x) * (a[i].y - a[2].y) != (a[i].x - a[2].x) * (a[2].y - a[1].y))
		{
			cout << a[1].q << ' ' << a[2].q << ' ' << a[i].q;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：1)

萌萌构造题。

# Algorithm 1

考虑调整地构造。

先考虑已经选出了一个三角形，我们要判断其是否合法。

考虑对于剩下的每一个点：若其在三角形中，我们随便选择一个顶点被当前这个点替换，这样就有一个新的三角形合法，而且其符合前面的任意一个点不在其中。

# Algorithm 2

考虑逐步选择地构造。

假定能够定下一个点。

先考虑选出两个点构成一条线段，使得剩下所有点都不在这条线段上。

那很明显就是选离这个点最近的一个点。

再考虑如何选择第三个点。

类似地，我们选择离这个线段最近的一个点即可。

从这组构造下，我们发现，选择的第一个点是什么是无关紧要的。


Algorithm 2 代码：
```cpp
il db F(pdd a,pdd b){return sd hypot(a.x-b.x,a.y-b.y);}
il db G(pdd a,pdd b,pdd c){return .5*sd abs(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y));}
void Solve()
{
	rd(n);
	for(int i=1;i<=n;++i) rd(a[i].x,a[i].y);
	int x=2,y=-1;
	for(int i=3;i<=n;++i) F(a[1],a[i])<F(a[1],a[x])&&(x=i);
	db m=1e27;
	for(int i=2;i<=n;++i) if(i^x)
	{
		db S=G(a[1],a[x],a[i]);
		if(S>1e-10&&S<m) m=S,y=i;
	}
	wrt(1,' ',x,' ',y);
	return;

```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/618/submission/208897889)

---

## 作者：recollect_i (赞：1)

## 题意描述

给定 $n$ 个点（$n\leq10^5$），找到三个点满足这三个点不在同一直线上且三个点构成的三角形中不包含其他点，保证所有点不会在同一直线上。

## 题目分析

首先必然每一个点都可以作为一组解中的点。

不妨其中一个点编号为 $1$。找一个点作为第二个点，为了使没有点在这条边上，这个点与 $1$ 号点的距离要是最短的。

接下来找第三个点，只需使这个点与前两个点构成的三角形面积最小就行了。

## 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5 + 5;
const double esp = 1e-8;
 
int n;
double x[N], y[N];
 
double dis(double ax, double ay, double bx, double by)
{
	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
 
double area(double ax, double ay, double bx, double by, double cx, double cy)
{
	double tx1 = bx - ax, ty1 = by - ay, tx2 = cx - ax, ty2 = cy - ay;
	return fabs(tx1 * ty2 - tx2 * ty1) / 2;
}
 
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++ ) scanf("%lf%lf", &x[i], &y[i]);
	
	int t = 2;
	double dt = dis(x[1], y[1], x[2], y[2]);
	for(int i = 3; i <= n; i ++ )
	{
		double d = dis(x[1], y[1], x[i], y[i]);
		if(d < dt)
		{
			dt = d;
			t = i;
		}
	}
	double ma = 1e20;
	int rt;
	for(int i = 2; i <= n; i ++ )
		if(i != t)
		{
			double xx = area(x[1], y[1], x[t], y[t], x[i], y[i]);
			if(xx > esp && xx <= ma)
			{
				rt = i;
				ma = xx;
			}
		}
	printf("%d %d %d\n", 1, t, rt);
	return 0;
}
```

---

