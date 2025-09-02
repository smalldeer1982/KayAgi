# Chemistry Lab

## 题目描述

Monocarp is planning on opening a chemistry lab. During the first month, he's going to distribute solutions of a certain acid.

First, he will sign some contracts with a local chemistry factory. Each contract provides Monocarp with an unlimited supply of some solution of the same acid. The factory provides $ n $ contract options, numbered from $ 1 $ to $ n $ . The $ i $ -th solution has a concentration of $ x_i\% $ , the contract costs $ w_i $ burles, and Monocarp will be able to sell it for $ c_i $ burles per liter.

Monocarp is expecting $ k $ customers during the first month. Each customer will buy a liter of a $ y\% $ -solution, where $ y $ is a real number chosen uniformly at random from $ 0 $ to $ 100 $ independently for each customer. More formally, the probability of number $ y $ being less than or equal to some $ t $ is $ P(y \le t) = \frac{t}{100} $ .

Monocarp can mix the solution that he signed the contracts with the factory for, at any ratio. More formally, if he has contracts for $ m $ solutions with concentrations $ x_1, x_2, \dots, x_m $ , then, for these solutions, he picks their volumes $ a_1, a_2, \dots, a_m $ so that $ \sum \limits_{i=1}^{m} a_i = 1 $ (exactly $ 1 $ since each customer wants exactly one liter of a certain solution).

The concentration of the resulting solution is $ \sum \limits_{i=1}^{m} x_i \cdot a_i $ . The price of the resulting solution is $ \sum \limits_{i=1}^{m} c_i \cdot a_i $ .

If Monocarp can obtain a solution of concentration $ y\% $ , then he will do it while maximizing its price (the cost for the customer). Otherwise, the customer leaves without buying anything, and the price is considered equal to $ 0 $ .

Monocarp wants to sign some contracts with a factory (possibly, none or all of them) so that the expected profit is maximized — the expected total price of the sold solutions for all $ k $ customers minus the total cost of signing the contracts from the factory.

Print the maximum expected profit Monocarp can achieve.

## 样例 #1

### 输入

```
2 10
0 10 20
100 15 20```

### 输出

```
175.000000000000000```

## 样例 #2

### 输入

```
2 10
0 100 20
100 150 20```

### 输出

```
0.000000000000000```

## 样例 #3

### 输入

```
6 15
79 5 35
30 13 132
37 3 52
24 2 60
76 18 14
71 17 7```

### 输出

```
680.125000000000000```

## 样例 #4

### 输入

```
10 15
46 11 11
4 12 170
69 2 130
2 8 72
82 7 117
100 5 154
38 9 146
97 1 132
0 12 82
53 1 144```

### 输出

```
2379.400000000000000```

# 题解

## 作者：Alex_Wei (赞：4)

挺趣味的一道题，让我对线性组合产生了新的理解。

考虑两种试剂 $i, j$ 以及对应体积 $a_i, a_j$，则浓度为 $a_ix_i + a_jx_j$，价格为 $a_ic_i + a_jc_j$。不妨 $x_i \geq x_j$，设给定浓度 $x\in [x_i, x_j]$，得方程组 $\begin{cases} a_i + a_j = 1 \\ a_ix_i + a_jx_j = x \end{cases}$，解得 $\begin{cases} a_i = \frac {x - x_j} {x_i - x_j} \\ a_j = \frac {x_i - x} {x_i - x_j} \end{cases}$。再乘上价格作为系数，可以发现价格是关于浓度的线性函数，且当浓度为 $x_i$ 时，价格为 $c_i$，当浓度为 $x_j$ 时，价格为 $c_j$。

将每种试剂 $(x_i, c_i)$ 视为平面上的点 $P_i$，则 $i, j$ 组合出的试剂落在线段 $P_iP_j$ 上，而浓度为 $x$ 时的价格即横坐标为 $x$ 时对应纵坐标 $c$ 的值。期望值即 $c$ 在 $[x_j, x_i]$ 上的积分，即线段和横坐标围成的梯形面积 $g(j, i) = \frac {(c_i + c_j)(x_i - x_j)} 2$。

进一步地，当存在多种试剂时， 它们组合出的试剂在这些试剂对应的点的凸包上，而我们只关心上凸包的积分。这是一个经典结论，但我不太会证：**若干个点的权重之和为 $1$ 的线性组合形成的区域为这些点的凸包**。2022 杭电多校第四场 08 也用到了这个结论。

将所有试剂按 $x$ 从小到大排序，设 $f_i$ 表示选择第 $i$ 种试剂时，在前 $1\sim i$ 种试剂中的答案，则有转移 $f_i = -w_i + \max(0, \max_{j = 1} ^ {i - 1} f_j + g(j, i))$。转移下凸一定是不优的，对答案没有影响。

时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1765/submission/185246598)。

---

## 作者：lsj2009 (赞：2)

### Solution

很厉害的题目。很好奇这个题咋评 2200 的，感觉完全有 2700 啊！

先考虑只有两个试剂的情况：我们考虑把 $(x_i,c_i)$ 当做一个点丢到平面上，你们只有两个试剂的情况下，如果两个实际都选，显然就是连接两个点得到一条直线 $y=\frac{c_1-c_2}{x_1-x_2}\cdot x+c_1-\frac{c_1-c_2}{x_1-x_2}\cdot x_1$，则期望即为：

$$\int_{x=x_1}^{x_2} y\mathrm{d}x =\frac{(x_2-x_1)(c_1+c_2)}{2}$$

也就是两点连成的直线与 $x$ 轴和 $x=x_1$ 与 $x=x_2$ 四条直线围成面积。

而对于多个点的情况，也就是选择 $(x_{p_1},c_{p_1}),(x_{p_2},c_{p_2}),\cdots,(x_{p_m},c_{p_m})$ 时，他们通过线性组合得到的点集，也就是

$$\{(\sum\limits_{i=1}^m v_i\cdot x_{p_i},\sum\limits_{i=1}^m v_i\cdot c_{p_i})\mid \sum\limits_{i=1}^m v_i=1\}$$

恰好为这 $m$ 个点所构成的凸包。

那么也就是说，我们要选取若干个点，使得他们围成的凸包面积减去 $\sum w_i$ 值最大。由于要维护一个凸包，看起来我们只能直接 $\Theta(n^3)$ 去 dp（因为要记录上一个斜率），但是我们观察到，我们直接计算 $n$ 个点围成的面积，如果说某个面积不是一个凸包，则必然不优，见下图：

![](https://z1.ax1x.com/2023/11/14/piYn8Zn.png)

也就是我直接连接第一和第三个点（红线），不仅比连接第一、第二和第二、第三个点（黑线）多了一块面积，而且少付出了 $w_2$ 的代价。

所以我们直接 $\Theta(n^2)$ 枚举相邻两个点 dp 即可。具体的，我们将所有点按 $x$ 排序，考虑设 $f_i$ 为对于前 $i$ 个点且强制选第 $i$ 个点的最优代价，得：

$$f_i=\max\limits_{j=1}^{i-1} \frac{(c_i+c_j)(x_i-x_j)}{200}\cdot k-a_i$$

其中除以 $200$ 中得除以 $2$ 是因为计算梯形面积，除以 $100$ 是因为题目询问得是百分比，乘上 $k$ 是因为有 $k$ 名客户。

然后就做完了，复杂度 $\Theta(n^2)$。 

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=5e3+5;
struct node {
	int x,w,c;
	bool operator < (const node &tmp) const {
		return x<tmp.x;
	}
}; node a[N];
ld f[N];
int n,k;
ld calc(int j,int i) {
	return 1.0*(a[i].c+a[j].c)*(a[i].x-a[j].x)/200.0*k;
}
signed main() {
	scanf("%d%d",&n,&k);
	rep(i,1,n)
		scanf("%d%d%d",&a[i].x,&a[i].w,&a[i].c);
	sort(a+1,a+n+1);
	ld ans=0.0;
	rep(i,1,n) {
		rep(j,1,i-1) 
			chkmax(f[i],f[j]+calc(j,i));
		f[i]-=a[i].w;
		chkmax(ans,f[i]);
	}
	printf("%.9Lf\n",ans);
    return 0;
}
```

---

## 作者：ZnPdCo (赞：0)

Duel 不会了。

首先考虑恰好选两个的时候 $(x_1,c_1),(x_2,c_2)$，设两个分别取了 $(a_1,a_2)$，希望浓度为 $x$，解一个方程：

$$
\begin{cases}
a_1+a_2=1 \\
x_1a_1+x_2a_2=x
\end{cases}
$$

那么发现当 $x=x_1$ 时 $a_1=1,a_2=0$，代价为 $c_1$，当 $x=x_2$ 时 $a_1=0,a_2=1$，代价为 $c_2$。

其实发现代价就是连接 $(x_1,c_1)$ 和 $(x_2,c_2)$ 两个点的一个一次函数。

那么期望值就是这个这个一次函数，与 $x=x_1$ 和 $x=x_2$ 两条直线和 $x$ 轴围成的梯形积起来，也就是：

$$
\dfrac{(c_1+c_2)(x_1-x_2)}{2}
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/w0tw7f5a.png)

考虑更多点时，代价就是这些点围成的凸包，那么期望值也是这个凸包与两端垂直于 $x$ 轴的直线与 $x$ 轴围成的图形的面积了。

![](https://cdn.luogu.com.cn/upload/image_hosting/34rnbh39.png)

那么我们可以用 $O(n^3)$ 维护这个凸包。考虑瓶颈是什么，就是我们要记录上一条线的斜率。但是实际上我们发现当有下面这种非凸包的情况时，一定不优（面积不比凸包大）：

![](https://cdn.luogu.com.cn/upload/image_hosting/4xn4tlx8.png)

所以不需要记录上一条线的斜率，dp 最优时就是凸包。

所以有：

$$
f_i=-w_i+f_j+g(j,i)
$$

其中 $g(j,i)$ 是 $j$ 到 $i$ 围成的面积。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 5010
#define db long double
using namespace std;
int n, k;
db f[N], ans;
struct node {
    int x, w, c;
} a[N];
signed main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i].x >> a[i].w >> a[i].c;
    }
    sort(a + 1, a + n + 1, [](node a, node b) {
        return a.x < b.x;
    });
    for(int i = 1; i <= n; i ++) {
        f[i] = -a[i].w;
        for(int j = 1; j < i; j ++) {
            f[i] = max(f[i], - a[i].w + f[j] + 1.0 * (a[i].x - a[j].x) * (a[i].c + a[j].c) / 200 * k);
        }
        ans = max(ans, f[i]);
    }
    cout << fixed << setprecision(10) << ans << endl;
}
```

---

