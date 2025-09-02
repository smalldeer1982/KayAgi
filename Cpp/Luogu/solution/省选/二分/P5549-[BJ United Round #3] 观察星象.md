# [BJ United Round #3] 观察星象

## 题目描述

EI 在用望远镜观察星星，星空中共有  $n$ 个星星，每个星星观察起来有一个二维直角坐标 $(x,y)$。  

他的望远镜如果定位在 $(x_0,y_0)$ 处，可以看到所有 $(x_0-x)^2 + (y_0-y)^2 \le r^2$ 的星星。  

望远镜的大小 $r$ 是可以调整的，EI 想知道如果他要至少看到 $m$ 个星星，至少需要把 $r$ 设置到多大？

## 说明/提示

| 子任务编号 | $n$ | $m$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 50$ | $\leq n$ | $10$ |
| $2$ | $\leq 200$ | $\leq n$ | $15$ |
| $3$ | $\leq 700$ | $\leq n$ | $15$ |
| $4$ | $\leq 2000$ | $= n$ | $20$ |
| $5$ | $\leq 2000$ | $\leq n$ | $40$ |


对于 $100\%$ 的数据，保证：  
$2 \le m \le n  \le 2000$  
$|x|,|y| \le 10^4$

By：EntropyIncreaser

## 样例 #1

### 输入

```
4 3
0 0
1 1
2 3
3 3```

### 输出

```
1.41421356```

# 题解

## 作者：Elegia (赞：4)


#### 算法一

显然所选的圆上要么有两个点要么有至少三个。因此分别枚举，枚举两个点作为圆的直径，此外枚举三个点之后可以确定唯一一个外接圆。

时间复杂度 $\Theta(n^4)$，预计得分 $10\%$。

#### 算法二

$m=n$ 的情况就是经典的最小圆覆盖问题。

首先将点的顺序打乱，考虑维护前 $k$ 个点的最小圆。可以证明前 $k+1$ 个点的最小覆盖圆由前 $k$ 个点最小覆盖圆上的关键点和第 $k+1$ 个点，新的最小覆盖圆的关键点一定在这些点之间。因此只有常数种情况，每种通过 $\Theta(n)$ 的 check 即可。第 $k$ 个点不在前 $k-1$ 个点的最小覆盖圆内的概率显然是 $O(\frac1k)$，因此第 $k$ 个点消耗的期望复杂度是 $\Theta(k) \cdot O(\frac1k) = \Theta(1)$。

期望时间复杂度 $\Theta(n)$，预计得分 $20\%$。

#### 算法三

我们考虑二分答案。那么接下来枚举哪个点在圆上，其它每个点我们可以计算出它对于当前圆在哪个夹角区间内，进行一遍前缀和即可查找出是否存在一个夹角使得该圆包含 $m$ 个点。

时间复杂度 $\Theta(n^2\log n \log \frac{x}{\epsilon})$，预计得分 $60\%$。

#### 算法四

我们对算法三进行进一步的观察。事实上我们可以看成这样一个问题，对于第 $i$ 个点，客观上存在一个 $r_i$ 即最小的圆的半径使得圆内有 $m$ 个点（我们认为无解即 $+\infty$），我们在二分的过程中，总共会预计调用 $\Theta(n\log \frac{x}{\epsilon})$ 次检查。这实际上是有所浪费的，在同样的检查次数内，实际上我们还可以算出每个 $i$ 对应的 $r_i$，换句话说我们多获取了不必要的信息，因为我们只关心最小值。

接下来就是有趣的地方了：我们先将序列随机打乱，并把当前最小值设为 $a = +\infty$。接下来我们将点一个个考虑，我们实际上可以一次检查出当前点的答案是否可以 $< a$。如果并不小于，我们就可以略过它，否则对该点的答案进行二分。这样显然是进行 $n + L\log \frac{x}{\epsilon}$ 次检查，其中 $L$ 是 $r_i$ 序列的单调栈长度。

显然最坏情况是 $r$ 互不相同时，单调栈长度的期望最长，这等价于一个排列的期望长度。而这一期望长度等于 $H_n = \sum_{k=1}^n \frac 1k = \Theta(\log n)$。

因此本算法的期望复杂度为 $\Theta( (n + \log n \log \frac{x}{\epsilon}) n\log n)$，预计得分 $100\%$。


---

## 作者：hellowin (赞：2)

### 前置知识

最小圆覆盖中，最小圆覆盖的所有点中的最远点对的距离一定大于此圆的半径。

这题如果取$n=m$则变成最小圆覆盖问题，半径上界$maxdist$为最远点对的距离，

所以我们二分上界取$dist_{max}$即可。

### 题解

可以想到的是二分半径，然后极角排序，找出是否有一个夹角包含使得这个圆包含m个点。

具体做法：考虑以点集 $X$ 中的每个点为圆心，做半径为 $r$ 的圆。如果一个覆盖区域被 $k$ 个圆覆盖，那么以这个区域内的任意一点做半径为 $r$ 的圆，必定能覆盖 $X$ 中的 $k$ 个点。所以我们只需要统计每个区域被多少个圆给覆盖。我们以此考虑每个圆心，与这个圆心相关的每个区域的覆盖次数，和对应的弧的覆盖次数是一致的，所以我们转而统计弧的覆盖次数。

前缀和做一下就好了。

时间复杂度$O(n^2\log n\log \frac{dist_{max}}{exp})$

然鹅只有60

我们考虑对每个点作圆，显然存在一个最小的圆使得圆内有$m$个点。

然后考虑当前答案是不是<ans，如果这个答案不够优秀，那么我们没必要去算他。

如果这个答案更加优秀，我们选择对他做60分的这个二分，求出答案。

时间复杂度$O(n\log^2 n \log \frac{dist_{max}}{exp}+n^2\log n)$

目前$rk1$（开$O2$）

```cpp
#include <bits/stdc++.h>
#define Mn 2005
using namespace std;
const double eps = 1e-8;
const double pi = acos(-1.0);
#define sqr(x) ((x) * (x))
double Fmax(double a,double b) {
	return a > b ? a : b;
}
double RF;
int n,k;
struct point {
	double x,y;
	void read() {
		scanf("%lf%lf",&x,&y);
	}
	void print() {
		printf("%lf%lf\n",x,y);
	}
	double friend dis(const point &a,const point &b) {
		return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
	}
} p[Mn + 5];
double dist(int a,int b) {
	return sqrt((double)(sqr(p[a].x - p[b].x) + sqr(p[a].y - p[b].y)));
}
struct alpha {
	double v;
	int flag;
	bool friend operator < (const alpha &a,const alpha &b) {
		return a.v < b.v;
	}
} alp[Mn * Mn + 5];
int judge(int i,double r) {
	int num = 0;
	for(int j=0; j<n; ++j) {
		if(i==j)continue;
		double dis=dist(i,j);
		if(dis-2.0*r>eps)continue;
		double angle=atan2(p[j].y-p[i].y,p[j].x-p[i].x);
		(angle<0)&&(angle+=2*pi);
		double p=acos(dis/2.0/r);
		alp[++num]=alpha {angle-p+2*pi,1};
		alp[++num]=alpha {angle+p+2*pi,-1};
	}
	sort(alp + 1,alp + num + 1);
	int res = 0,maxx = 0;
	for (int j = 1; j <= num; j++) res += alp[j].flag,maxx = max(maxx,res);
	return maxx + 1; 
}
int main() {
	double Mdist = 0;
	scanf("%d%d",&n,&k);
	for(int i = 0; i < n; i++)
		p[i].read();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j)
				Mdist = Fmax(Mdist,dis(p[i],p[j]));
//  cout<<Mdist<<endl;
	random_shuffle(p,p + n);
	double ans = 1000000000.000;
	for (int i = 0; i < n; i++) {
		if (judge(i,ans) >= k) {
			double L = 0;
			double R = Mdist;//二分上界取最远距离
			while (fabs(R - L) > eps) {
				double mid = (L + R) / 2;
				//cout<<RF<<endl;
				if (judge(i,mid) >= k)
					R = mid - eps,ans = mid;
				else
					L = mid + eps;
			}
		}
	}//二分
	printf("%.8lf\n",ans);//精度
	return 0;
}
```



---

