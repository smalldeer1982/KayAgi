# [ABC275G] Infinite Knapsack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc275/tasks/abc275_g

$ N $ 種類の品物がそれぞれ無限個あります。 $ i $ 種類目の品物は重さが $ A_i $ 、体積が $ B_i $ 、価値が $ C_i $ です。

レベル $ X $ の高橋君は、重さの合計が $ X $ 以下かつ体積の合計が $ X $ 以下になるように品物を持つことができます。ここで、高橋君は条件を満たすならば同じ種類の品物を何個でも持つことが可能であり、また選ばない種類の品物があっても構いません。

レベル $ X $ の高橋君が持てる品物の価値の合計の最大値を $ f(X) $ とするとき、極限 $ \displaystyle\lim_{X\to\ \infty}\ \frac{f(X)}{X} $ が存在することが証明できます。この値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 10^8\leq\ A_i,B_i,C_i\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ X=300000000 $ のとき、高橋君は重さの合計が $ 300000000 $ 以下かつ体積の合計が $ 300000000 $ 以下になるように品物を持つことができます。 持ち方の一例として、高橋君は $ 1 $ 番目の品物と $ 2 $ 番目の品物を $ 1 $ 個ずつ持つことができます。このとき、品物の価値の合計は $ 100000000+100000000=200000000 $ であり、これが達成可能な価値の最大値なので、$ \dfrac{f(300000000)}{300000000}=\dfrac{2}{3} $ です。 また、この入力では極限 $ \displaystyle\lim_{X\to\ \infty}\ \dfrac{f(X)}{X} $ も $ \dfrac{2}{3} $ に一致することが証明できます。よって答えは $ 0.6666666... $ です。

## 样例 #1

### 输入

```
2
100000000 200000000 100000000
200000000 100000000 100000000```

### 输出

```
0.6666666666666667```

## 样例 #2

### 输入

```
1
500000000 300000000 123456789```

### 输出

```
0.2469135780000000```

# 题解

## 作者：EuphoricStar (赞：2)

原问题等价于：

> 给定 $a_i = \frac{A_i}{C_i}, b_i = \frac{B_i}{C_i}$，要求 $\sum\limits_{i = 1}^n x_i = 1$，$x_i$ 为**非负实数**，求 $\max(\sum\limits_{i = 1}^n a_i x_i, \sum\limits_{i = 1}^n b_i x_i)$ 的最小值。

考虑二分。设当前二分到 $mid$，check 等价于：

> 给定 $a_i = \frac{A_i}{C_i} - mid, b_i = \frac{B_i}{C_i} - mid$，要求 $\sum\limits_{i = 1}^n x_i = 1$，$x_i$ 为非负实数，问是否能使 $\sum\limits_{i = 1}^n a_i x_i \le 0 \land \sum\limits_{i = 1}^n b_i x_i \le 0$。

考虑若存在 $i$ 使得 $a_i \le 0 \land b_i \le 0$，那么就可行。

否则，我们找到 $a_i < 0, b_i \ge 0$ 且 $\frac{b_i}{-a_i}$ 最小的 $i$，$a_j \ge 0, b_j < 0$ 且 $\frac{a_j}{-b_j}$ 最小的 $j$，那么除了 $i, j$ 以外，它的 $x$ 值都等于 $0$。因为我们肯定想，选了其中一个属性 $< 0$ 的元素，对另一种元素造成的影响尽量小。

那么现在就是问是否存在一个非负实数 $x$ 满足：

- $a_i x + a_j (1 - x) \le 0$
- $b_i x + b_j (1 - x) \le 0$

这个就是一个一元一次不等式，判断下界是否小于等于上界即可。

[code](https://atcoder.jp/contests/abc275/submissions/42297637)

---

## 作者：shinkuu (赞：1)

这题的大致思路龟龟已经讲得很清楚了，我主要分享一下推导过程。

首先题目意为求一个序列 $k$，使得 $\dfrac{\sum c_ik_i}{\max(\sum a_ik_i,\sum b_ik_i)}$ 取最大值。

首先发现因为是求极限，这个 $c_i$ 太麻烦了，可以将每个 $\dfrac{a_i}{c_i}\to a_i,\dfrac{b_i}{c_i}\to b_i,1\to c_i$。则柿子变成：

$$\dfrac{\sum k_i}{\max(\sum \dfrac{a_ik_i}{c_i},\sum\dfrac{b_ik_i}{c_i})}$$

然后发现 $k_i$ 的具体值也没啥用（因为可以同时乘一个数来变化），可以强制 $\sum k_i=1$。然后柿子变成：

$$\dfrac{1}{\max(\sum \dfrac{a_ik_i}{c_i},\sum\dfrac{b_ik_i}{c_i})},(\sum k_i=1)$$

然后为了方便，先取个倒数：

$$\max(\sum \dfrac{a_ik_i}{c_i},\sum\dfrac{b_ik_i}{c_i})$$

然后就得到龟龟题解里的柿子了。

然后二分,让上面 $\max$ 中的两个都尽可能 $<0$，看取值范围是否合法。注意 corner case。具体参考 @zltqwq 的题解。

code：

```cpp
int n,m,a[N],b[N],c[N];
double A[N],B[N];
const double eps=1e-8;
bool check(double k){
	int x=0,y=0;
	rep(i,1,n){
		A[i]=1.*a[i]/c[i]-k;
		B[i]=1.*b[i]/c[i]-k;
		if(A[i]<=0&&B[i]<=0)
			return true;
		if(A[i]<0&&(!x||-B[i]/A[i]<-B[x]/A[x]))x=i;
		if(B[i]<0&&(!y||-A[i]/B[i]<-A[y]/B[y]))y=i;
	}
	if(!x||!y)return false;
	return (-A[y])/(A[y]-A[x])>=(-B[y])/(B[y]-B[x]);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	}
	double l=0,r=10;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(check(mid))
			r=mid;
		else 
			l=mid+eps;
	}
	printf("%.8lf\n",1./r);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc275_g)

**题目大意**

> 给定个 $n$ 个物品，每种无穷多个，有两维代价 $a_i,b_i$ 和收益 $c_i$，$f(x)$ 表示 $\sum a_i,\sum b_i$ 分别 $\le x$ 的情况下最大的 $\sum c_i$，求 $\lim_{x\to+\infty}\dfrac{f(x)}x$。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

先求出每种物品的“性价比”$x_i=\dfrac{a_i}{c_i},y_i=\dfrac{b_i}{c_i}$，以及每种物品的占比 $q_i$，其中 $\sum q_i=i$。

那么答案可以表示为 $\max(\sum x_ip_i,\sum y_ip_i)^{-1}$，感性理解就是想要 $1$ 的收益，$a$ 类体积为 $\sum x_ip_i$，$b$ 类体积为 $\sum y_ip_i$。

那么我们只要求 $\max(\sum x_ip_i,\sum y_ip_i)$ 的最小值，二分一个 $k$，由于 $\sum p_i=1$，因此我们只要求 $\sum (x_i-k)p_i,\sum(y_i-k)p_i\le 0$。

如果存在 $i$ 使得 $x_i,y_i\le k$ 那么取 $p_i=1$ 即可。

考虑把这些向量画在二维平面上，那么很自然的发现我们只要最靠近第三象限的两个向量（二、四象限各一个）。

具体来说就是 $x_i<k$ 且 $\dfrac{y_i-k}{k-x_i}$ 最小和 $y_i<k$ 且 $\dfrac{x_i-k}{k-y_i}$ 最小

判断这些向量过第三象限得到那个夹角是否 $\le \pi$ 即可，也可以直接解一元一次不等式组。

时间复杂度 $\mathcal O(n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ld long double
using namespace std;
const int MAXN=2e5+5;
const ld eps=1e-8;
int n;
ld a[MAXN],b[MAXN],x[MAXN],y[MAXN];
bool check(ld k) {
	int p=0,q=0;
	for(int i=1;i<=n;++i) {
		x[i]=a[i]-k,y[i]=b[i]-k;
		if(x[i]<=0&&y[i]<=0) return true;
		if(x[i]<0&&(!p||-y[i]*x[p]<-y[p]*x[i])) p=i;
		if(y[i]<0&&(!q||-x[i]*y[q]<-y[i]*x[q])) q=i;
	}
//	(x[q]-x[p])*k>=x[q], -y[q]>=k*(y[p]-y[q])
	return p&&q&&((-y[q])*(x[q]-x[p])>=x[q]*(y[p]-y[q]));
}
signed main() {
	scanf("%d",&n);
	for(int u,v,w,i=1;i<=n;++i) {
		scanf("%d%d%d",&u,&v,&w),a[i]=1.*u/w,b[i]=1.*v/w;
	}
	ld l=0,r=1e9;
	while(r-l>=eps) {
		ld mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%.12Lf",1./r);
	return 0;
}

```

---

## 作者：Ups_and_downs (赞：0)

# [ABC275G] Infinite Knapsack
### py 党写一个思路吧

$N$ 种物品，每种物品都有无限个，重量为 $A_i$，体积为 $B_i$，价值为 $C_i$。玩家能承受的最大总重量与最大总体积都是相等的喵，都是 $x$。我们简单地将玩家能拿到的最大价值记作 $f(x)$，那么我们要求的东西就是 $\lim\limits_{x\to\infty}(\frac{f(x)}{x})$。

好了，事情变得明了了。

把每种物品都视为重量为 $\dfrac{A_i}{C_i}$，体积为 $\dfrac{A_i}{B_i}$，价值为 $1$ 的物品。尝试计算 $\dfrac{1}{\lim\limits_{x\to\infty}(\tfrac{x}{f(x)})}$即可。

求原式的最大值，就相当于求新式子中分母的最小值：即每一单位价值，最少需要多少重量和体积。

所有的点 $\left(\dfrac{A_i}{C_i},\dfrac{A_i}{B_i}\right)$ 在二维平面上成散点图，并且最优解一定在这个图像的凸包上。

那么：求出凸包上的点，让相邻两点之间的组合尽可能接近 $y=x$ 这条线（重量等于体积）。设左边点的坐标为 $(l_x,l_y)$，右边的点坐标为 $(r_x,r_y)$，则有 $l_x<r_x$。

简单分个类吧：

- $l_y<r_y$。由于预先设定了 $l_x\leq r_x$，则选择左边这个点。
- $r_x<r_y$，两个点都在 $y=x$ 下面，采用靠近 $y=x$ 的右侧点。
- $l_x\geq l_y$，两个点都在 $y=x$ 上面，采用靠近 $y=x$ 的左侧点。

最后输出结果的倒数就是答案。

### 终

---

