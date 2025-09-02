# [ABC327E] Maximize Rating

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc327/tasks/abc327_e

高橋君は $ N $ 回コンテストに参加し、$ i $ 回目に参加したコンテストにおいてパフォーマンス $ P_i $ を獲得しました。  
高橋君はこの中から ($ 1 $ つ以上) いくつかのコンテストを選び、それらの結果から計算される高橋君のレートを最大にしたいと考えています。

コンテストをうまく選んだとき、高橋君のレートとしてあり得る最大の値を求めてください。

ただし、高橋君のレート $ R $ は、高橋君の選んだコンテストの数が $ k $ 個であり、 選んだコンテストにおけるパフォーマンスが **参加した順に** それぞれ $ (Q_1,Q_2,\ldots,Q_k) $ であるとき、

$ \displaystyle\ R=\frac{\sum_{i=1}^k\ (0.9)^{k-i}Q_i}{\sum_{i=1}^k\ (0.9)^{k-i}}-\frac{1200}{\sqrt{k}} $ によって計算されます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 5000 $
- $ 1\leq\ P_i\leq\ 5000 $
- 入力はすべて整数

### Sample Explanation 1

高橋君が $ 1 $ 回目と $ 3 $ 回目のコンテストを選んだ時、レートは、 $ \displaystyle\ R=\frac{0.9\times\ 1000+\ 1.0\times\ 1200}{0.9+1.0}-\frac{1200}{\sqrt{2}}=256.73502... $ となり、この時レートが最大となります。

### Sample Explanation 2

$ 1,2,3 $ 回目のコンテストすべてを選んだとき、レートが最大となります。

### Sample Explanation 3

レートは負になることもあります。

## 样例 #1

### 输入

```
3
1000 600 1200```

### 输出

```
256.735020470879931```

## 样例 #2

### 输入

```
3
600 1000 1200```

### 输出

```
261.423219407873376```

## 样例 #3

### 输入

```
1
100```

### 输出

```
-1100.000000000000000```

# 题解

## 作者：qqqaaazzz_qwq (赞：21)

~~赛时没切，写篇题解纪念一下。~~

考虑枚举 $k$，这样 $\left(\sum_{i=1}^k (0.9)^{k-i}\right)$ 和 $\left(\dfrac{1200}{\sqrt{k}}\right)$ 就确定下来了。现在我们的问题是，如何求出最大的 $\left(\sum_{i=1}^k (0.9)^{k-i}Q_i\right)$。

当然是伟大的DP啦！

设 $f_{x,k}$ 表示在前 $x$ 个数里选了 $k$ 个数（设这 $k$ 个数组成了 $Q$ 序列），最大的 $\left(\sum_{i=1}^k (0.9)^{k-i}Q_i\right)$ 是多少。

如何转移？

如果第 $x$ 个数没有选，那 $f_{x,k}=f_{x-1,k}$。⭐如果第 $x$ 个数选了，那么 $f_{x,k}=f_{x-1,k-1}\times0.9+a_x$。

综上，$f_{x,k}=\max(f_{x-1,k},f_{x-1,k-1}\times0.9+a_x)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[5010];
double f[5010][5010];
double sum[5010];

signed main()
{
	cin >> n;
	for (int i=1;i<=n;i++) cin >> a[i];
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=i;j++)//赛时把j<=i写成j<=n了，交了13发都没过qaq
		{
			f[i][j] = max(f[i-1][j],f[i-1][j-1]*0.9+a[i]);
		}
	}
	double ans = -10000.0;
	for (int k=1;k<=n;k++)
	{
		sum[k] = sum[k-1]*0.9+1;
		double res = f[n][k]*1.0/sum[k]-1200.0/sqrt(k);
		ans = max(ans,res);
	}
	printf("%.10lf",ans);
	return 0;
}
```
对于 ⭐ 处的补充说明：

设原来为 $0.9\times3+7$。

若新加了一个数 $8$，

则原式变成 $0.9^2\times3+0.9\times7+8$。

$0.9^2\times3+0.9\times7+8 = 0.9\times(0.9\times3+7)+8$。

至此结束，留个赞呗！

---

## 作者：yydfj (赞：13)

这是本蒟蒻第四十四次写的题解，如有错误点请好心指出！

## 问题简述

有 $n$ 个数 $p_i$ 排成一排，你需要在其中任选 $k \in [1,n]$ 个下标 $i$ 互不相同的数，并按照原本的排列组成 $k$ 个数 $Q_i$，使得 $\displaystyle \frac{\sum_{i=1}^k\ (0.9)^{k-i}Q_i}{\sum_{i=1}^k\ (0.9)^{k-i}}-\frac{1200}{\sqrt{k}}$ 最大。

## 解法综述

从 $n$ 个数里选 $k$ 个数，且每个数只能选一次，显然是道 01 背包问题，难点应该在于如何整理上述式子。发现当 $k$ 确定的时候 $\displaystyle \sum_{i=1}^k\ (0.9)^{k-i}$ 和 $\displaystyle \frac{1200}{\sqrt{k}}$ 也是确定的，所以我们只需要求 $\displaystyle \sum_{i=1}^k\ (0.9)^{k-i}Q_i$ 的最大值即可。

然后发现即使确定了 $k$，$(0.9)^{k-i}$ 却是不好确定的，考虑将整个数组 $p_i$ 反过来，这样我们就能确定如果选了第 $i$ 个数，它的系数应该是 $(0.9)^i$。

## 代码描述

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
double p[5005],kk[5005],sum[5005],f[5005],ans=-1e9;
ll n;
int main()
{
	scanf("%lld",&n);
	for(int i=n;i>=1;i--) scanf("%lf",&p[i]);//将整个数组p[i]反过来
	kk[1]=sum[1]=1.0;
	for(int i=2;i<=n;i++) kk[i]=kk[i-1]*0.9,sum[i]=sum[i-1]+kk[i];//计算系数
	for(int i=1;i<=n;i++)
	for(int j=i;j>=1;j--) f[j]=max(f[j],f[j-1]+p[i]*kk[j]),ans=max(ans,f[j]/sum[j]-1200.0/sqrt(j));//01背包
	printf("%.15lf",ans);
	return 0;
}
```

---

## 作者：2huk (赞：6)

# E - Maximize Rating

## Description

给定一个长度为 $n$ 的序列 $\{p_n\}$，请你从中选择一个子序列 $\{q_k\}$，使得其价值最大。价值的计算如下：
$$
R=\dfrac{\sum_{i=1}^k (0.9)^{k-i}q_i}{\sum_{i=1}^k (0.9)^{k-i}}-\dfrac{1200}{\sqrt{k}}
$$
$1 \le n, p_i \le 5000$。

## Solution

设 DP 状态 $f_{i, j}$ 表示在前 $i$ 个元素中，选择 $j$ 个元素的最大价值。那么分类讨论第 $i$ 个元素是否选择：

- 若不选，则其价值为 $f_{i - 1, j}$，表示在前 $i - 1$ 个元素中选择 $j$ 个元素的最大价值。注意这种情况需要满足 $i - 1 \ge j$；

- 若选，则其基础价值为 $val \gets f_{i - 1, j - 1}$，表示在前 $i - 1$ 个元素中选择 $j - 1$ 个元素的最大价值。然后考虑如何计算真正的答案：

  - 首先将上一次计算的 $- \dfrac {1200}{\sqrt{j-1}}$ 的贡献去掉，即 $val \gets val + \dfrac {1200}{\sqrt{j-1}}$；

  - 然后将上一次计算的 $\dfrac1{\sum_{k=1}^{j-1} (0.9)^{j-k-1}}$ 去掉，即 $val \gets val \times \sum_{k=1}^{j-1} (0.9)^{j-k-1}$；

  - 然后需要将 $\sum_{k=1}^{j - 1} (0.9)^{j-k-1}q_k$ 的值修改为 $\sum_{k=1}^{j} (0.9)^{j-k}q_k$：
    $$
    \begin{aligned} \sum_{k=1}^{j} (0.9)^{j-k}q_k &= \sum_{k=1}^{j - 1} (0.9)^{j-k}q_k + (0.9)^{j-j}q_i\\&= \sum_{k=1}^{j - 1} (0.9)^{j-k}q_k + q_i \\ &= 0.9 \sum_{k=1}^{j - 1} (0.9)^{j-k-1}q_k + q_i \\ &= 0.9\times val + q_i\end{aligned}
    $$
    

    即 $val \gets 0.9 \times val + q_i$；

  - 然后在加上 $\dfrac1{\sum_{k=1}^{j} (0.9)^{j-k}}$ 的贡献加上，即 $val \gets \dfrac{val}{\sum_{k=1}^{j} (0.9)^{j-k}}$；

  - 最后加上 $-\dfrac{1200}{\sqrt{j}}$ 的贡献，即 $val \gets val - \dfrac{1200}{\sqrt{j}}$。

然后在两种情况中取较大值即可，即 $f_{i, j} \gets \max(f_{i -  1, j}, val)$。

其中计算 $\sum_{k=1}^{j} (0.9)^{j-k}$ 时可以预处理。令 $x_j = \sum_{k=1}^{j} (0.9)^{j-k}$，有递推式：
$$
\begin{aligned} x_j &= \sum_{k=1}^{j} (0.9)^{j-k} \\ &= \sum_{k=1}^{j-1}(0.9)^{j-k} + (0.9)^{j-j} \\&= 0.9\sum_{k=1}^{j-1}(0.9)^{j-k-1} + 1 \\&=0.9 \times x_{j-1} + 1 \end{aligned}
$$
然后根据上述模拟即可。答案显然为 $\max_{i=1}^n(f_{n, i})$。总时间复杂度 $\mathcal O(n^2)$。

## Code

赛时 46 分钟切的：[Submission #47251198 - HHKB Programming Contest 2023(AtCoder Beginner Contest 327)](https://atcoder.jp/contests/abc327/submissions/47251198)。

---

## 作者：PikachuQAQ (赞：2)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc327_e)

高桥君参加了 $n$ 场比赛，第 $i$ 场比赛的表现是 $P_i$ 分。

高桥君要选择至少一场比赛来计算等级分，设选择的第 $i$ 场比赛的表现是 $Q_i$ ，总共选择了 $k$ 场比赛来计算，那么最终的等级分为 $\begin{aligned}\frac{\sum_{i=1}^k(0.9)^{k-i}Q_i}{\sum_{i=1}^k(0.9)^{k-i}}-\frac{1200}{\sqrt{k}}\end{aligned}$ 。

请你设计一个程序来计算最终的等级分的最大值是多少，你的输出与标准答案的相对或绝对误差小于 $10^{-6}$ 即被视为正确。

翻译来自 UID912241。

## Solution

我们发现答案和 $k$ 和 $R=\sum_{i=1}^k(0.9)^{k-i}Q_i$ 有关，假设我们先不考虑 $k$，发现对于 $P_i$，$d$ 呈线性关系。

定义 $R$ 值为 $0.9x+P_i$。

所以我们可以考虑枚举 $k$，DP 找到 $R_{\max}$。

既然是道 DP，考虑走三步。

首先考虑状态。

显然有令 $f_{i,j}$ 为打了前 $i$ 场比赛，选择 $j$ 个比赛时的最大值。

然后考虑边界状态。

当只打一场比赛时，只能选一个比赛，贡献为 $P_1$。也就是 $f_{1,1}=P_1$。

当只选一场比赛时，贡献为 $\max(f_{i-1,j},P_i)$。

最后考虑转移。

分两种情况：

- 当选择了不少于一场比赛并且选择的比赛少于可选择的总比赛数量，有两个可能的最大值：打了前 $i-1$ 场，但是同样也选了 $j$ 场的贡献；要求不能选第 $i$ 场比赛的最大值的 $R$ 值，也就是打了前 $i-1$ 场，选了 $j-1$ 场的贡献的 $R$ 值。

- 当我们选择所有 $Q_i$ 时，最大贡献为前 $i-1$ 场，选了 $j-1$ 场的贡献的 $R$ 值。

至此，情况讨论完毕。

当然有另外一种 DP 方法，其他的题解讲的很清楚了，这里不做赘述。

## Code

```cpp
// 2023/11/4 PikachuQAQ

#include <iostream>
#include <cmath>

using namespace std;

const int kMaxN = 5007;
const double DINF = 1e100, A = 1200;

int n, a[kMaxN];
double f[kMaxN], res, ans = -DINF;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.fixed, cout.precision(18), cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * 0.9 + a[i];
        for (int j = i; j; j--) {
            f[j] = max(f[j], f[j - 1] * 0.9 + a[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        res *= 0.9, res++;
        ans = max(ans, f[i] / res - A / sqrt(i));
    }
    cout << ans;

    return 0;
}
```

---

## 作者：uid_647775 (赞：1)

动态规划。  
设 $F_{i,j}$ 为只考虑前 $i$ 个比赛且参加 $j$ 个比赛时，$\sum_{i=1}^j (0.9)^{k-i}Q_i$（$(Q_1, Q_2, \ldots, Q_k)$ 为参加的 $n$ 个比赛的成绩按时间顺序排序）（就是算评分式子的左上角部分）的最大值。  
很容易可以发现：
$$F_{i,j}=max(F_{i-1,j},F[i-1][j-1]\times 0.9+P[i])$$
那么最终评分的最大值为：
$$\max_{1 \le k \le n}(\frac{F_{n,k}}{\sum_{i=1}^k (0.9)^{k-i}}-\frac{1200}{\sqrt{k}})$$

---

## 作者：incra (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc327_e)
### 题解
发现 $k$ 和式子左上角那玩意和答案有关，故考虑维护这俩东西。

设 $f_{i,j}$ 表示前 $i$ 个比赛中，选择 $j$ 场，**且一定选择 $i$**，且得出的结果为左上角那玩意的最大值。

显然 $f_{i,j}=f_{k,j-1}(k<i)$，然后时间复杂度 $O(n^3)$，前缀和优化一下，就变成了 $O(n^2)$ 了。

不懂的看代码吧。
### 代码
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <map>
#include <set>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 5010;
double pre[N];
int n;
int p[N];
double f[N][N],g[N][N];
double tmp[N];
double get_rating (double s,int k) {
	return s / pre[k - 1] - 1200 / sqrt (k);
}
int main () {
	cin >> n;
	pre[0] = 1;
	for (int i = 1;i <= n;i++) pre[i] = pre[i - 1] * 0.9 + 1;
	for (int i = 1;i <= n;i++) cin >> p[i];
	tmp[1] = f[1][1] = p[1],g[1][1] = p[1] - 1200;
	double ans = g[1][1];
	for (int i = 2;i <= n;i++) {
		for (int j = i;j >= 1;j--) {
			double r = get_rating (tmp[j - 1] * 0.9 + p[i],j);
			g[i][j] = r,f[i][j] = tmp[j - 1] * 0.9 + p[i];
			tmp[j] = max (tmp[j],f[i][j]);
			ans = max (ans,g[i][j]);
		}
	}
	printf ("%.6lf",ans);
	return 0;
}
```

---

## 作者：naroanah (赞：0)

一眼 $O(n^2)$ dp，首先注意到 $\displaystyle R=\frac{\sum_{i=1}^k (0.9)^{k-i}Q_i}{\sum_{i=1}^k (0.9)^{k-i}}-\frac{1200}{\sqrt{k}}$ 中，$\sum_{i=1}^k (0.9)^{k-i}$ 和 $-\frac{1200}{\sqrt{k}}$ 只和 $k$ 有关，所以先不管，考虑对每一个 $k$ 求出 $\sum_{i=1}^k (0.9)^{k-i}Q_i$ 的最大值即可。

考虑设 $f_{i, j}$ 表示考虑到第 $i$ 场比赛， 已经选了 $j$ 场的最大值。发现 $(0.9)^{k - i}$ 很烦，不好处理，注意到最后的和是一个 $k$ 次多项式的形式，可以用秦九韶算法转化，转移方程即为：

$$f_{i, j} = max(f_{i - 1,j}, f_{i - 1, j - 1} \times 0.9 + p_i)$$

最后对每个 $k$ 计算答案，取最大值即可，同时注意精度问题，尽量开 `long double`。

```cpp
#include<bits/stdc++.h>
#define pc putchar
#define gc getchar
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define EG (int)(N << 1)
using namespace std;
constexpr int N = 5000 + 10, inf = 0x3f3f3f3f, INF = 0x7f7f7f7f;
constexpr double eps = 1e-9;
int n; 
long double p[N], f[N][N], o[N];
signed main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i];
    o[0] = 1;
    for(int i = 1; i <= n; i++) o[i] = o[i - 1] * 0.9;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            f[i][j] = max(f[i - 1][j], (f[i - 1][j - 1] * 0.9 + p[i]));
        }
    }
    long double ans = -1e18, t = 0;
    for(int i = 1; i <= n; i++) {
        t += o[i - 1];
        long double now = f[n][i] / t - ((long double)1200.00 / sqrtl((long double)i));
        ans = max(ans, now);
    }
    cout << fixed << setprecision(15) << ans << "\n";
    return 0;
}
```



---

## 作者：SegTree (赞：0)

不难想到状态 $dp_{i,j}$ 表示前 $i$ 场选 $j$ 场的最大 Rating。

但是注意到有 $\sum_{i=1}^k(0.9)^{k-i}$ 和 $\dfrac{1200}{\sqrt{k}}$ 会使得我们不好转移。

注意到这两个式子是只和 $k$ 有关的函数，所以我们修改状态为 $dp_{i,j}$ 表示前 $i$ 场选 $j$ 场的 $\sum_{i=1}^k(0.9)^{k-i}Q_i$ 最大值。最后，求出 $\max_{i=1}^n \dfrac{dp_{n,i}}{\sum_{j=1}^i (0.9)^{i-j}}-\dfrac{1200}{\sqrt{i}}$ 即可。

转移：$dp_{i,j}=\max(dp_{i-1,j},0.9dp_{i-1,j-1}+Q_i)$ 分别表示不选第 $i$ 场和选第 $i$ 场的答案。

[Record](https://atcoder.jp/contests/abc327/submissions/47238131)。

---

## 作者：FReQuenter (赞：0)

考虑 dp。

令 $f_{i,j}$ 表示后 $i$ 场比赛中选择了 $j$ 场比赛的 $\max\{\sum^{k}_{i=1}(0.9)^{k-i}Q_i\}$。

为什么倒着来呢？显然越大的 perf 放在后面收益更高，每一场比赛都变一下 $k-i$ 不好处理。

转移：

$$f_{i,j}=\max(f_{i-1,j},f_{i-1,j-1}+(0.9)^{j-1}\times P_i)$$

其中的两项分别对应不参加和参加第 $i$ 场比赛。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[5005];
double f[5005][5005],base[5005],sum[5005];
signed main(){
	cin>>n;
	base[0]=1;
	sum[0]=1;
	for(int i=1;i<=n;i++) base[i]=base[i-1]*0.9,sum[i]+=sum[i-1]+base[i];
	for(int i=1;i<=n;i++) cin>>p[i];
	reverse(p+1,p+n+1);
	for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) f[i][j]=-1e18;
	for(int i=1;i<=n;i++) f[i][1]=max(f[i-1][1],1.0*p[i]);
	for(int i=2;i<=n;i++){
		for(int j=2;j<=i;j++){
			f[i][j]=max(f[i-1][j],f[i-1][j-1]+base[j-1]*p[i]);
		}
	}
	double ans=-1e18;
	for(int i=1;i<=n;i++) ans=max(ans,f[n][i]/sum[i-1]-1200.0/sqrt(i));
	cout<<fixed<<setprecision(10)<<ans;
}

---

