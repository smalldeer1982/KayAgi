# [ABC332E] Lucky bag

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc332/tasks/abc332_e

AtCoder 社は、[オンラインショップ](https://suzuri.jp/AtCoder/home)でグッズを販売しています。

今、$ N $ 個のグッズが社内に残っています。 ここで、$ i $ $ (1\leq\ i\leq\ N) $ 個目のグッズの重さは $ W_i $ です。

高橋君は残ったグッズをまとめて $ D $ 袋の福袋として販売する事にしました。  
高橋君は各福袋に入ったグッズの重さの合計の分散を最小にしたいと考えています。  
ここで、各福袋に入ったグッズの重さの合計がそれぞれ $ x_1,x_2,\ldots,x_D $ であるとき、  
それらの平均を $ \bar{x}=\frac{1}{D}(x_1+x_2+\cdots+x_D) $ として、 分散は $ V=\frac{1}{D}\displaystyle\sum_{i=1}^D\ (x_i-\bar{x})^2 $ として定義されます。

各福袋に入ったグッズの重さの合計の分散が最小になるようにグッズを分けた時の分散の値を求めてください。  
ただし、空の福袋が存在してもかまいません（この時福袋に入ったグッズの重さの合計は $ 0 $ として定義されます）が、  
**どのグッズも $ D $ 袋のうちちょうど $ 1 $ つの福袋に入っている** ようにするものとします。

## 说明/提示

### 制約

- $ 2\ \leq\ D\leq\ N\leq\ 15 $
- $ 1\ \leq\ W_i\leq\ 10^8 $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ つめの福袋に $ 1,3 $ 個目のグッズを、 $ 2 $ つめの福袋に $ 2,5 $ 個目のグッズを、 $ 3 $ つめの福袋に $ 4 $ 個目のグッズを入れると、 それぞれの福袋に入ったグッズの重さの合計は $ 6,8,6 $ となります。 このとき、重さの平均は $ \frac{1}{3}(6+8+6)=\frac{20}{3} $ であり、 分散は $ \frac{1}{3}\left\{\left(6-\frac{20}{3}\right)^2+\left(8-\frac{20}{3}\right)^2+\left(6-\frac{20}{3}\right)^2\ \right\}=\frac{8}{9}=0.888888\ldots $ となり、このときが最小です。 同じ重さのグッズが複数存在し得ること、 各グッズはいずれかの福袋に入っている必要があることに注意してください。

## 样例 #1

### 输入

```
5 3
3 5 3 6 3```

### 输出

```
0.888888888888889```

# 题解

## 作者：Terrible (赞：9)

## 思路

本题要将 $N$ 个物品放到 $D$ 个袋子中，每个物品有一个重量 $W_i$，放入袋子中后，每个袋子内物品总重 $x_i$，最后求这些袋子内物品总重数据 $x_i$ 的方差最小值。

方差式子可以简化：

$$V=\dfrac{1}{D}\sum\limits_{i=1}^D(x_i-\overline x)^2,$$

其中

$$\begin{aligned}&\sum\limits_{i=1}^D(x_i-\overline x)^2\\&=\sum\limits_{i=1}^D(x_i^2-2x_i\overline x+\overline x^2)\\&=\left(\sum\limits_{i=1}^Dx_i^2\right)-2\overline x\left(\sum\limits_{i=1}^Dx_i\right)+\left(\sum\limits_{i=1}^D\overline x^2\right)\\&=\left(\sum\limits_{i=1}^Dx_i^2\right)-2\overline xD\overline x+D\overline x^2\\&=\left(\sum\limits_{i=1}^Dx_i^2\right)-D\overline x^2\\&=\left(\sum\limits_{i=1}^Dx_i^2\right)-\dfrac{1}{D}\left(\sum\limits_{i=1}^Dx_i\right)^2,\end{aligned}$$

所以代回原式中

$$V=\dfrac{D\left(\sum\limits_{i=1}^Dx_i^2\right)-\left(\sum\limits_{i=1}^Dx_i\right)^2}{D^2}.$$

根据质量守恒定律，我们知道 $\sum\limits_{i=1}^Dx_i=\sum\limits_{i=1}^NW_i$，所以上式分子的右边那项是常数项，关键要求出 $\min\sum\limits_{i=1}^Dx_i^2$。

## 求解方法

（**随机化+贪心**）我们充分发挥人类智慧，按照某种顺序依次将物品加入内部重量最小的袋子里，只要我们枚举的物品随机加入顺序足够多，所有方案的最小值就很可能是 
$$\min\sum\limits_{i=1}^Dx_i^2.$$

使用 `std::shuffle` 枚举加入顺序即可：

```cpp
#include<random>
#include<vector>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;
using ll=long long;
int n,d;
long long x2(const vector<int>&w)
{
	vector<ll> ds(d);
	for(auto i:w)*min_element(ds.begin(),ds.end())+=i;
	//每次放到最小的袋子
	ll ans=0;for(auto i:ds)ans+=i*i;return ans;
	//求平方和
}
int main()
{
	cin>>n>>d;ll sum=0;
	vector<int> w(n);for(auto&i:w)cin>>i,sum+=i;
	mt19937 rnd(0xab8d5f6);
	ll minx2=9e18;
	for(int cnt=5e6;cnt--;)//卡一个 1s 左右的时间就好
	{
		shuffle(w.begin(),w.end(),rnd);//随机打乱顺序
		minx2=min(minx2,x2(w));//贪心求解，并取最小值
	}
	cout<<fixed<<setprecision(15)<<(minx2*d-sum*sum)*1.0l/d/d;
	//此处需要注意精度问题，尽量在做除法时再转化成long double
	return 0;
}
```

---

也可以通过**状态压缩动态规划**求解：

（**状态压缩动态规划**）设状态 $\mathrm{dp}_{i,S}$ 表示包含了物品集合 $S$ 的 $i$ 个袋子内重量平方和的最小值，转移方程为。

$$\mathrm{dp}_{i,S}=\min\limits_{T\subseteq S}\mathrm{dp}_{i-1,S-T}+\mathrm{dp}_{1,T},\quad i\geqslant 2.$$

集合的表示用全集中某个元素是否存在在该集合（$0$、$1$）表示，因而一个元素对应一个 bit，枚举子集的位运算方法则是初始化 `t=s`，下一个集合表示是 `t=(t-1)&s`，枚举到 `t==0` 时可以结束。`(t-1)&s` 表示如果 `t` 不为 $0$（$T$ 非空），则 `t-1` 相当于将 `t` 最小的 bit 去掉，加上所有位次比它低的 bit，由于又包含在 `s` 中，再将结果和 `s` 做与运算，从而排除掉在 `s` 之外的 bit；如果 `t` 为 $0$（$T$ 为空），假设 `t` 是带符号补码实现的整数，那么 `(t-1)&s` 结果为 `s`。

程序对应的算法时间复杂度分析：

枚举所有集合表示 `s`，以及其子集表示 `t` 的过程中，考虑到一个物品有三种情况：包含在 $S$ 和 $T$ 中；包含在 $S$ 但不包含在 $T$ 中；不包含在 $S$ 和 $T$ 中。（由于 $T\subseteq S$，所以不能只在 $T$ 中而不在 $S$ 中）由于有 $N$ 个物品，可知有 $3^N$ 种不同的方案数。

再考虑上上袋子的维数，可知对应算法**状态转移**的时间复杂度为 $\Theta(D3^N)$。

```cpp
#include<cstdio>
#include<algorithm>
long long dp[16][1<<15],w[15];
int main()
{
	int n,d;scanf("%d%d",&n,&d);long long sum=0;
	for(int i=0;i<n;i++)scanf("%lld",w+i),sum+=w[i];
	__builtin_memset(dp,0x3f,sizeof dp);
	for(int s=0;s<1<<n;s++)
	{
		dp[1][s]=0;
		for(int i=0;i<n;i++)if(s&1<<i)dp[1][s]+=w[i];
		dp[1][s]*=dp[1][s];
		//预处理 dp[1][s]，即只有一个袋子时 s 状态对应的总重平方
	}
	for(int i=2;i<=d;i++)for(int s=0;s<1<<n;s++)
	{
		int t=s;
		do{
			dp[i][s]=std::min(dp[i][s],dp[i-1][s^t]+dp[1][t]);
		}while((t=(t-1)&s)!=s);
		//for(int t=s;t;t=(t-1)&s)中 t 取遍所有非空子集
		//此处是枚举所有子集，既不是非空子集也不是真子集
		//当然，其实不必枚举所有子集
	}
	printf("%.15Lf",(dp[d][(1<<n)-1]*d-sum*sum)*1.0l/d/d);
	//此处需要注意精度问题，尽量在做除法时再转化成long double
	return 0;
}
```

---

由于枚举子集状态转移时间复杂度不低，我们有很大的把握认为，随机化卡不过不去，状压 dp 也不好受。

---

（**优化第一维递推的状态压缩动态规划**）还可以再优化一下上面的状态转移动态规划，我们发现袋子是一模一样的，而且不一定每次增加一个袋子作转移，观察上面给的 dp 转移方程：

$$\mathrm{dp}_{i,S}=\min\limits_{T\subseteq S}\mathrm{dp}_{i-1,S-T}+\mathrm{dp}_{1,T},\quad i\geqslant 2,$$

发现第一维不一定要从上一项转移而来，如果我们定义 $\mathrm{dp}_{0,S}=\begin{cases}0,&S=\varnothing\\+\infty,&S\neq\varnothing\end{cases}$，实际上有以下式子成立

$$\mathrm{dp}_{i,S}=\min\limits_{T\subseteq S}\mathrm{dp}_{i-j,S-T}+\mathrm{dp}_{j,T},\quad\forall 0\leqslant j\leqslant i,\forall S\subseteq U,$$

其中 $U$ 是全集，忽略掉第二维，将转移方程写作：

$$\mathrm{dp}_i=\mathrm{dp}_{i-j}\oplus\mathrm{dp}_j,\forall 0\leqslant j\leqslant i,$$

此处 $\oplus$ 不是异或运算，该运算就是第二维集合的转移运算：

$$\mathrm{dp}_{a+b}=\begin{pmatrix}
	\mathrm{dp}_{a+b,\varnothing}\\
	\mathrm{dp}_{a+b,\{W_1\}}\\
	\mathrm{dp}_{a+b,\{W_2\}}\\
	\vdots\\
	\mathrm{dp}_{a+b,U}
\end{pmatrix}=\begin{pmatrix}
	\min\limits_{T\subseteq\varnothing}\mathrm{dp}_{a,\varnothing-T}+\mathrm{dp}_{b,T}\\
	\min\limits_{T\subseteq\{W_1\}}\mathrm{dp}_{a,\{W_1\}-T}+\mathrm{dp}_{b,T}\\
	\min\limits_{T\subseteq\{W_2\}}\mathrm{dp}_{a,\{W_2\}-T}+\mathrm{dp}_{b,T}\\
	\vdots\\
	\min\limits_{T\subseteq U}\mathrm{dp}_{a,U-T}+\mathrm{dp}_{b,T}
\end{pmatrix}=\mathrm{dp}_a\oplus\mathrm{dp}_b.$$

容易发现这玩意满足结合律，于是我们还可以定义乘法：

$$\mathrm{dp}_a\otimes b=\underbrace{\mathrm{dp}_a\oplus\mathrm{dp}_a\oplus\cdots\oplus\mathrm{dp}_a}$$

括起来的部分共有 $b$ 个 $\mathrm{dp}_a$ 相加。

我们意识到这和倍增“快速幂”的思路不谋而合：

$$a^{19}=a^{10011_{(2)}}=a^{16}\times a^{2}\times a,$$

同样有

$$\mathrm{dp}_{19}=\mathrm{dp}_{10011_{(2)}}=\mathrm{dp}_{16}\oplus\mathrm{dp}_2\oplus\mathrm{dp}_1.$$

除此之外也可以将初始化 $\mathrm{dp}_1$ 的代码写成对应时间复杂度 $\Theta\left(2^N\right)$ 的算法，将上面的代数方法抽象成类/结构体后有了下面的代码，对应算法的时间复杂度就成了 $\Theta\left(\log D\times 3^N\right)$，即便 $D$ 本身不大，但是整体效率依然提高了一些：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
using ll=long long;
int n,d;vector<ll> w;
struct DP
{
	vector<ll> dp;
	void init_zero()//初始化为 dp_0，就是零元
	{
		dp=vector<ll>(1<<n,0x3f3f3f3f3f3f3f3f);
		dp[0]=0;
	}
	void init_one()//初始化为 dp_1，就是幺元
	{
		dp=vector<ll>(1<<n);
		for(int i=0;i<n;i++)dp[1<<i]=w[i];
		for(int s=0;s<1<<n;s++)dp[s]=dp[s^(s&-s)]+dp[s&-s];
		for(int s=0;s<1<<n;s++)dp[s]*=dp[s];
	}
	DP operator+(const DP&o)//新概念加法，也就是枚举子集转移方程
	{
		DP ans;ans.init_zero();
		for(int s=0;s<1<<n;s++)
		{
			int t=s;
			do{
				ans.dp[s]=min(ans.dp[s],dp[s^t]+o.dp[t]);
			}while((t=(t-1)&s)!=s);
		}
		return ans;
	}
};
DP doubling_mul(DP id,int b)//类似倍增“快速幂”/倍增“龟速乘”
{
	DP ans;ans.init_zero();
	for(;b;id=id+id,b>>=1)if(b&1)
	{
		ans=ans+id;
		if(b==1)break;//可以少算一次id+id
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&d);ll sum=0;
	w=vector<ll>(n);for(auto&i:w)scanf("%d",&i),sum+=i;
	DP id;id.init_one();
	DP&&ans=doubling_mul(id,d);
	//id 是 dp_1，那么 dp 结果就包含在 id⊗d 中
	printf("%.15Lf",(ans.dp[(1<<n)-1]*d-sum*sum)*1.0l/d/d);
	return 0;
}
```

---

## 作者：__ryp__ (赞：5)

谨此纪念我的第一道蓝题题解（虽然是看了其他题解后写的）

## 题意

给定一个序列 $W_0 \cdots W_{n - 1}$，以及一个整数 $D$，要求把 $W$ 的所有元素分配到 $D$ 个盒子中，求分配的方差和最小值。

## 分析

很明显是动态规划题。我们可以设 $f(i,j)$，表示将状态 $j$ 所表示的元素分配到 $i$ 个盒子中的最小方差（$\sum_k^i (x_k-\bar x)^2$）。

分析边界：

$f(0,j)$，也就是将所有元素放到同一个盒子中，就是：
$$f(i, j)=\sum\limits_k^0 (x_k-\bar x)^2=(x_k-\bar x)^2 \quad i = 0$$

对于一般情况，要将 $j$ 所表示的元素放进 $i$ 个盒子中，我们要考虑 $j$ 的每个子状态 $k$：找将 $s$ 与 $k$ 差的元素放进 $i - 1$ 个盒子中所得到的最小方差和再加上 $k$ 状态的方差，以上的最小值，也就是

$$f(i, j) = \min\limits_{k\in j}{f(i-1,j\oplus k)+(x_k-\bar x)^2}$$

因此

$$f(i,j) = \begin{cases} 
(x_j - \bar x)^2 & i = 0 \\
\min\limits_{k\in j} f(i-1,j\oplus k)+(x_k - \bar x)^2 & \text{otherwise}
\end{cases}$$

## 证明

证明是彻底理解转移方程原理的很好方式。

首先易证本问题有最优子结构：

### 最优子结构证明

问题就是求 $\frac{1}{D}\min\sum\limits_{i=0}^D(x_i-\bar x)^2$。设 $T$ 是问题的最优解，要证 $\sum\limits_{i=1}^D(T_i-\bar x)^2$ 也最小。

反证。设 $U_1,\cdots,U_{D-1}$ 是一个更优的方案，即

$$
\sum\limits_{i=1}^D(T_i-\bar x)^2 > \sum\limits_{i=1}^D(U_i -\bar x)^2
$$

那么可以有

$$
T' = \frac{1}{D}((T_1-\bar x)^2+\sum\limits_{i=1}^D(U_i-\bar x)^2)
$$

则必有 $T' < T$，与 $T$ 是本问题的最优解冲突。故不存在比 $T_1, \cdots T_{D-1}$ 更优的方案 $U$，得证。


------------

以上是证明最优子结构的常用方法，即《算法导论》中所讲的 copy-paste 法。

## 代码

代码预计算出了 $\bar x$ 与 每一种状态 $k$ 对应的 $x_k$，然后就是状压 DP。

```c++
#include <iostream>
using namespace std;

#define rep(v, s, e) for (auto v = (s); v < (e); v++)
#define square(x) ((x) * (x))
const int N = 15, M = 1 << 15;

long long *w;
long long s[M];
double f[N][M];

long long
read (void)
{
  long long res = 0;
  char c;

  while (!isdigit (c = getchar ()));
  do res = res * 10 + c - '0'; while (isdigit (c = getchar ()));
  return res;
}

int
main (void)
{
  int n, d; n = read (); d = read ();
  double xbar = 0;

  w = new long long [n];
  
  rep (i, 0, n) xbar += w[i] = read ();
  xbar /= d;

  rep (i, 0, 1 << n) rep (j, 0, n + 1)
    s[i] += w[j] * !!(i & (1 << j));

  rep (i, 0, 1 << n) f[0][i] = square (s[i] - xbar);
  rep (i, 1, d) rep (j, 0, 1 << n)
    {
      f[i][j] = f[i - 1][j] + square (xbar);
      for (int k = j; k; k = (k - 1) & j)
	f[i][j] = min (f[i][j], f[i - 1][j ^ k] + square (s[k] - xbar));
    }

  printf ("%.10lf\n", f[d - 1][(1 << n) - 1] / d);
  return 0;
}
```

## 补充最优解

以上代码 [不是最优解 （235ms）](https://www.luogu.com.cn/record/139605822)。

最优解使用的是另一种动态规划的实现方法，即自上到下的动态规划。在某些情况下这可以省去很多的计算。采用这种方法可以得到 13ms 的[最优解](https://www.luogu.com.cn/record/139174465)。



------------

upd. 2023/12/15 增加最优解

------------

证明有错误或叙述不当的请指出。感谢。


---

## 作者：emo_male_god (赞：4)

# AT_abc332_e random_shuffle解法

题意简述：把 $n$ 个数分成 $d$ 组，尽量减小每一组中所有数的和的方差（每一组可以是空的，但是每个数必须用上），这相当于一个模板题吧 ~~逃~~。

方差的定义：

$$
V = \frac{1}{D} \sum_{i = 1}^{D}(x_i - \overline{x})^{2}
$$

其中 $x_i$ 为第 $i$ 组的总和，$\overline{x} = \dfrac{1}{D}(x_1 + x_2 + x_3 + \cdot\cdot\cdot + x_D)$，也就是每组数的和的平均值。

每次我们每次用 `random_shuffle` 打乱数组，把前 $D$ 个数单独组作为 1 组放进去，然后把剩下的数，放到 **当前** 总和最小的一组，最后统计方差。

因为有随机化，所以我们用 `while ((double)clock() / CLOCKS_PER_SEC < 1.9)` 来卡时间，保证我们能更大概率随机到正解。

**注意 $ans$ 的初值设的大一点！**

代码:
```cpp
#pragma GCC optimize(2)
#include <algorithm>
#include <iostream>
#include <cstring>
#include <random>
#include <time.h>
#include <climits>

#define endl "\n"

using namespace std;

const int N = 25;

double ans = LLONG_MAX, aver;
double x[N], s[N];
int n, m;

void solve()
{
	random_shuffle(x + 1, x + 1 + n);

	for (int i = 1; i <= m; i ++ ) s[i] = x[i];

	for (int i = m + 1; i <= n; i ++ )
	{
		int p = min_element(s + 1, s + m + 1) - s; // 查找范围内最小的元素的地址
		s[p] += x[i];
	}

	double res = 0;
	for (int i = 1; i <= m; i ++ ) res += (s[i] - aver) * (s[i] - aver);
	ans = min(ans, res);
}

int main()
{
	srand(time(NULL));

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) scanf("%lf", &x[i]), aver += x[i];
	aver /= m;
	while ((double)clock() / CLOCKS_PER_SEC < 1.9) solve();
	printf("%.10lf\n", ans / m);
	return 0;
}
```

---

## 作者：chaynflow (赞：1)

这里是一篇随机化的题解，想学习正常做法的请忽略。

题意较为简单，略去。

## Solution

读完题，其实就会发现本题与 [P2503](https://www.luogu.com.cn/problem/P2503) 题意几乎一致，只是本题的 $\sigma$ 没有最后的一次开平方。

这时候，我们就可以参考那一题的题解区，感性思考一下就会发现，有一个贪心做法，如果对于一个数，我们肯定把他扔进当前总和的最小的组里来平衡各组数据。

于是我们直接使用 `random_shuffle` 来打乱序列，然后直接按上面的贪心做即可。

实践证明，在打乱次数达到 $2\times 10^6$ 左右时，即可通过本题。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
const int N = 25;
int n, m, a[N], f[N];
double ans; 
int main()
{
	#ifdef ONLINE_JUDGE
	FASTIO;
	#endif
	cin >> n >> m;
    double avg = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], avg += a[i];
    avg /= m; ans = 1e18;
    for (int counter = 1; counter <= 2e6; counter++)
    {
        random_shuffle(a + 1, a + n + 1);
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; i++)
        {
            int p = 1, minn = f[1];
            for (int j = 2; j <= m; j++)
                if (f[j] < minn) p = j, minn = f[j];
            f[p] += a[i];
        }
        double sum = 0;
        for (int i = 1; i <= m; i++) sum += (avg - f[i]) * (avg - f[i]);
        sum /= m;
        ans = min(ans, sum);
    }
    cout << fixed << setprecision(10) << ans;
	#ifndef ONLINE_JUDGE
	
	#endif
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

**首先，这是一道数据很毒瘤的题……**

我们的目标是使得每一组数字的和都尽量接近，于是把每个数加到当前和最小的组里。

但是因为加入的数字顺序不同，导致结果也会不同，于是可以随机化，进行多次贪心，每次都把数组给打乱一遍。

然后如果你按照这样写堆优化的算法，你应该是：``AC × 42`` 和 ``WA × 15``。

这好像卡不过去。（~~废话，我赛时交了二十多遍都没过~~）

赛后，打算重构一遍，先把不写堆优化的代码写出来，于是想看看不加堆优化的能过多少个点，结果竟然过了。（可能官方没卡这个？）

时间复杂度：$O(T \times n \log n)$（其中 $T$ 为你随机的次数）

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=21;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m;
ll a[N],s[N];
db ans=1e18;
void solve(){
    random_shuffle(a+1,a+n+1);
    memset(s,0,sizeof s);
    for(int i=1;i<=n;i++){
        ll t=1;
        for(int j=2;j<=m;j++)
          if(s[j]<s[t])
			t=j;
        s[t]+=a[i];
    }
    db s1=0,s2=0;
    for(int i=1;i<=m;i++)
      s1+=s[i]; 
	s1/=m;
    for(int i=1;i<=m;i++)
	  s2+=(s[i]-s1)*(s[i]-s1);
    ans=min(ans,s2/m);
}
int main(){
	n=read(),m=read();
    for(int i=1;i<=n;i++)
      a[i]=read();
    while((db)clock()/CLOCKS_PER_SEC<1.9) 
	  solve();
    printf("%.10lf",ans);
    return 0;
}
```


---

## 作者：End1essSummer (赞：1)



你有 $n$ 个物品，第 $i$ 种物品重量为 $w_i$，将这些物品全部分到 $D$ 个盒子中，每个盒子的重量为其中物品重量之和，求盒子重量的方差最小值，答案误差在 $10^{-6}$ 之内。

允许存在盒子没有物品，此时其重量为 $0$ 。

- $ 2\ \leq\ D\leq\ N\leq\ 15 $
- $ 1\ \leq\ W_i\leq\ 10^8 $
- 入力はすべて整数

(是不是突然觉得自己会读日文了？)

---

状压，但是考场上对着一个很呆的优化想了半天。

首先平均数是可以先求出来的，因为每个物品都要被放到袋子里。

看到 $N$ 是较小的，于是考虑对物品状压，考虑 $dp_{i,sta}$ 为现在考虑到了第 $i$ 个盒子，二进制数 $sta$ 第一位如果是一就代表第一个物品被选了，以此类推。

设选择物品的总价值为 $valsum$ 转移方程为：

$$dp_{i,nowsta} = \min(dp_{i-1,laststa} + (valsum - \bar{x})^2 , dp_{i,nowsta})$$

$valsum$ 可以预处理。

预处理时间复杂度 $O(n2^n)$ ，总时间复杂度 $O(n3^n)$ 。

Code:

```cpp
#include<iostream>
using namespace std;
#define int long long
#define double long double
double dp[20][(1<<15)],x[20],sum[(1<<15)];
double avex;
int n,d,nowsta,laststa,choice,nownums,cnt;
signed main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>x[i];
        avex+=x[i];
    }avex=(avex/(double)d);
    for(int i=0;i<=d;i++){
        for(int j=1;j<(1<<n);j++){
            dp[i][j]=1e18;
        }
    }for(int nowsta=1;nowsta<(1<<n);nowsta++){
        choice=(nowsta),nownums=0,cnt=0;
        while(choice!=0){
            cnt++;
            if((choice&1)==1){
                nownums+=x[cnt];
            }choice>>=1;
        }sum[nowsta]=nownums;
    }dp[0][0]=0;
    for(int i=1;i<=d;i++){
        dp[i][0]=i*avex*avex;
        for(nowsta=1;nowsta<(1<<n);nowsta++){
            for(laststa=nowsta;true;laststa=((laststa-1)&nowsta)){
                choice=(nowsta-laststa),nownums=sum[choice];
                dp[i][nowsta]=min(dp[i-1][laststa]+(nownums-avex)*(nownums-avex),dp[i][nowsta]);
                if(laststa==0) break;
            }
        }
    }dp[d][(1<<n)-1]/=d;
    printf("%.10Lf",dp[d][(1<<n)-1]);
}
```

---

## 作者：Phartial (赞：1)

先推一推式子：

$$
\begin{aligned}
  V
  &=\frac{1}{D}\sum_{i=1}^D(x_i-\overline{x})^2\\
  &=\frac{1}{D}\sum_{i=1}^Dx_i^2-2\overline{x}x_i+\overline{x}^2\\
  &=\frac{1}{D}\left(\sum_{i=1}^Dx_i^2\right)-2\overline{x}\frac{1}{D}\left(\sum_{i=1}^Dx_i\right)+\overline{x}^2\\
  &=\frac{1}{D}\left(\sum_{i=1}^Dx_i^2\right)-2\overline{x}^2+\overline{x}^2\\
  &=\frac{1}{D}\left(\sum_{i=1}^Dx_i^2\right)-\overline{x}^2\\
\end{aligned}
$$

于是你只需要最小化 $\displaystyle\sum_{i=1}^Dx_i^2$。

考虑状压 dp，设 $f_{i,S}$ 表示现在已经分出了 $i$ 组，且集合 $S$ 内的数已经被选走了时的最小的  $\displaystyle\sum_{j=1}^ix_j^2$。有转移方程：

$$
f_{i,S}=\min_{T\subseteq S}\left\{f_{i-1,T}+\left(\sum_{j\in S\setminus T}W_j\right)^2\right\}
$$

直接做即可，时间复杂度 $\mathcal{O}(D3^N)$。

特别要注意的是你输出答案时应当**只在最后**进行一次 `long double` 下的除法，之前的运算都应在整数下进行，否则精度误差能直接给你爆了。

```cpp
#include <iomanip>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 15;

int n, d, w[kN];
LL f[kN + 1][1 << kN], s[1 << kN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> d;
  for (int i = 0; i < n; ++i) {
    cin >> w[i];
    for (int j = 0; j < (1 << n); ++j) {
      if (j >> i & 1) {
        s[j] += w[i];
      }
    }
  }
  for (int i = 0; i < (1 << n); ++i) {
    s[i] *= s[i];
  }
  for (int i = 1; i < (1 << n); ++i) {
    f[0][i] = 3e18;
  }
  for (int i = 1; i <= d; ++i) {
    for (int j = 0; j < (1 << n); ++j) {
      f[i][j] = s[j];
      for (int k = j; k; k = j & k - 1) {
        f[i][j] = min(f[i][j], f[i - 1][k] + s[j ^ k]);
      }
    }
  }
  cout << fixed << setprecision(15) << 1.0L * (f[d][(1 << n) - 1] * d - s[(1 << n) - 1]) / (d * d);
  return 0;
}
```

---

## 作者：sgl654321 (赞：0)

## 题目大意
给定一个长度为 $n$ 的集合 $a$，把他分成 $d$ 个互不相交的子集，对每个子集的元素求和，问如何分组使得这 $d$ 个子集的方差最小。

## 解题思路
首先显然对于每个元素，把他放到当前元素之和最小的一个子集里面，答案不会变得更劣。

我们可以运用随机化算法，执行尽可能多次 `random_shuffle`，打乱这个序列。打乱之后，顺次放入每一个元素，放到当前元素之和最小的一个子集里面。

最后求出这个方差，然后取最小值。通过数据可以发现，加上卡时可以通过该题。

注意，我们要把答案最初设为一个极大值，这个极大值应当有值域的平方这个级别。

## 参考代码
[这里自取](https://www.luogu.com.cn/paste/rjeq1ixf)。


---

## 作者：Unnamed114514 (赞：0)

[整场题解](https://www.luogu.com.cn/blog/556362/abc-332-post)

题意：$n$ 个物品，每个权值 $w_i$。放到 $d$ 个福袋，每个福袋可以为空，但是每个物品都必须放到一个福袋里面，即福袋的 $SUM$ 等于这个福袋里物品的 $w$ 之和。求 $SUM$ 最小方差。

略微有点难度的题目。首先 $D\times d^2=n(\sum SUM^2)-(\sum SUM)^2$，后面为定值，问题转化为 $\sum SUM^2$ 的最小值。

发现 $N$ 比较小，所以容易想到状压，定义 $dp_{i,j}$ 表示 $i$ 个福袋，状态为 $j$ 的时候最小方差。注意直接枚举后继状态的时间复杂度是 $O(D\times2^N\times2^N)=O(D2^{2N})$，但是其实很多都不会继续遍历，枚举子集即可。

关于时间复杂度：$O(D\times\sum C_{n}^i2^{n-i})=O(D\times3^N)$。

---

## 作者：FreedomKing (赞：0)

个人认为算是比较好的随机乱搞题。

听大佬说正解是状压 DP 然而我~~不会~~感觉不如随机贪心乱搞。

双倍经验：[P2503 [HAOI2006] 均分数据](https://www.luogu.com.cn/problem/P2503)，唯一区别好像能不能有空组。

### 思路

有一个看一眼就觉得非常假的贪心，即每次都把数加入到当前和最小的那一组里。但是由于这道题的数据范围甚至比 P2503 还小，所以直接考虑进行多次随机化每次都跑一遍贪心最后确定正确率较高的近似解。

剩下的见注释。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5;
const int mod=1e9+7,mmod=1e7+7,Lmod=998244353;
int a[N],f[N],n,m,t,k;
vector<int>e[N];
bool vis[N];
double ans=1e18;
inline int qread(){
#define qr qread()
	int x=0,c=getchar(),t=1;
	while(c<'0'||c>'9'){
		t^=(c=='-');
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return (t?x:-x);
}
inline int qpow(int x,int p,int mod){
	mod=(mod?mod:LONG_LONG_MAX);
	x=(p?x:1);
	x%=mod;
	int t=1;
	while(p>1){
		if(p&1) t=(t*x)%mod;
		x=(x*x)%mod;
		p>>=1;
	}
	return (t*x)%mod;
}
inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qwe(_) qw(_),putchar('\n')
	if(x<0) x=-x,putchar('-');
	if(x>9) qwrite(x/10);
	putchar(x%10+'0');
}
void SA(){
	random_shuffle(a+1,a+n+1);//随机化
	for(int i=1;i<=m;i++) f[i]=0;//初始化
	for(int i=1;i<=n;i++){
		int cnt=1;
		for(int j=1;j<=m;j++) if(f[j]<f[cnt]) cnt=j;//求和最小的那组
		f[cnt]+=a[i];
	}
	double ave=0,sum=0;
	for(int i=1;i<=m;i++) ave+=f[i];//加和
	ave/=m;//求平均值
	for(int i=1;i<=m;i++) sum+=(f[i]-ave)*(f[i]-ave);//加和
	sum/=m;//求方差
	ans=min(ans,sum);//更新答案
	return;
}
signed main(){
	n=qr;m=qr;
	for(int i=1;i<=n;i++) a[i]=qr;
	while((double)clock()/CLOCKS_PER_SEC<1.9) SA();//卡时
	printf("%.10lf",ans);
	return 0;
}
```

虽然写的时候函数名字用的是退火，但个人认为这种做法没有多项式选择，仅仅能算是随机贪心。

---

## 作者：1234567890sjx (赞：0)

水题，但是没想出来随机化。~~但是因为是新号所以还是上大分~~

首先考虑一个错误的贪心。

从左往右枚举每一个价值，然后再从中找出当前价值最小的包裹，把当前的价值放到当前价值最小的包裹里去。但是这个显然是不对的。

所以考虑随机化！每一次随机出一个价值排列，然后跑贪心，取最小值。实测这样可以过。

然后这个题就做完了。

---

## 作者：OldDriverTree (赞：0)

本文讲解随机化做法。

双倍经验：[P2503](https://www.luogu.com.cn/problem/P2503)。

# Solution

可以想出一个显然错误的贪心：

每次把序列中当前位置的物品放入当前总重量最小的盒子中。

由于位置发生变化正确答案不会改变正确答案，考虑随机化：

每次打乱序列跑贪心，跑的次数较多正确率就会比较高，答案取个最小值即可。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=15;
int n,m,a[N],s[N];
double ans=1e18;

void SA()
{
	random_shuffle(a,a+n);
	memset(s,0,sizeof s);
	for (int i=0;i<n;i++) {
		int pos=0;
		for (int j=1;j<m;j++)
			if (s[j]<s[pos]) pos=j;
		s[pos]+=a[i];
	}
	double ave=0,sum=0;
	for (int i=0;i<m;i++) ave+=s[i]; ave/=m;
	for (int i=0;i<m;i++) sum+=(s[i]-ave)*(s[i]-ave);
	ans=min(ans,sum/m);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d",a+i);
	while ( (double)clock()/CLOCKS_PER_SEC<1.9) SA();
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

# [题目](https://www.luogu.com.cn/problem/AT_abc332_e)

## 思路：

用状压 dp 处理，$dp_{ij}$ 表示 $i$ 集合分成 $j$ 个幸运袋的重量，枚举集合，算 $dp_{ij}$。

## 实现方法：

首先算出平均值 $ava$，枚举集合，算出每个集合的重量，再枚举它的子集，拆分成两部分，更新答案。

## AC Code：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int n, d;
double w[20];
double sum[20];
double ans = 2000000.0, ava;
double dp[(1 << 15) + 1000][16];
int main() {
	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; i ++) scanf("%lf", &w[i]);
	for (int i = 0; i < n; i ++) ava += w[i];
	ava /= double(d);
	for (int i = 0; i < (1 << n); i ++) {
		double weight_of_i = 0.0;
		for (int j = 0; j < n; j ++) {
			if (i & (1 << j)) weight_of_i += w[j];
		}
		dp[i][1] = (weight_of_i - ava) * (weight_of_i - ava); // 初始化
		for (int j = 2; j <= d; j ++) {
			dp[i][j] = dp[i][j - 1] + dp[0][1];
			for (int tmp = i; tmp > 0; tmp = (tmp - 1) & i) {
				dp[i][j] = min(dp[i][j], dp[i - tmp][j - 1] + dp[tmp][1]);
			}
		}
	}
	printf("%.10f", dp[(1 << n) - 1][d] / double(d));
	return 0;
}
```

---

