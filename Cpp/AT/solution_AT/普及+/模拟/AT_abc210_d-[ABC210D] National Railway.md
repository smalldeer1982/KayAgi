# [ABC210D] National Railway

## 题目描述

## 题目翻译

国王想在他 $ H $ 行 $ W $ 列的国土上建铁路  
具体地，建铁路的花费可以表示为两部分：建车站和建轨道。  
- 在 $ (i,\ j) $ 处建车站的费用表示为 $ A_{i,j} $  
- 连接 $ (i,\ j) $ 处的车站和 $ (i',\ j') $ 处车站之间铁路的花费为 $ C\ \times\ (|i-i'|\ +\ |j-j'|) $  

由于不修铁路会下台，而国王又没有太多钱，所以想知道在不考虑便利性的前提下修铁路的最小花费。

## 样例 #1

### 输入

```
3 4 2
1 7 7 9
9 6 3 7
7 8 6 4```

### 输出

```
10```

## 样例 #2

### 输入

```
3 3 1000000000
1000000 1000000 1
1000000 1000000 1000000
1 1000000 1000000```

### 输出

```
1001000001```

# 题解

## 作者：wflhx2011 (赞：5)

和官方题解思路一样，显而易见的一道动态规划。

首先，我们假设从 $(1,1)$ 开始，每次可向下或向右走一个格子，距离为 $C$。

我们考虑用一个数组 $f$ 表示已经建了一个车站而现在位于 $(i,j)$，此时有三种情况：

1. 来到 $(i,j)$ 并在此处修了一个车站。

1. 从 $(i-1,j)$ 铺了一段轨道来到 $(i,j)$。

1. 从 $(i,j-1)$ 铺了一段轨道来到 $(i,j)$。

再对这三种情况取 $\min$。

此时我们建好了第一个车站，对于第二个车站，我们设一个数组 $ans$，有两种情况：

1. 从 $(i-1,j)$ 铺了一段轨道来到 $(i,j)$，在 $(i,j)$ 建了车站。

1. 从 $(i,j-1)$ 铺了一段轨道来到 $(i,j)$，在 $(i,j)$ 建了车站。

于是对这两种取一个 $\min$。

再在所有 $ans$ 中选一个最小值。

此时我们得到的答案其实有一定局限性，只向下或向右走就只能满足第一个车站在第二个车站左上方，我们把每一行反过来再跑一遍就能求出右上方的情况。

至于下方，其实只不过是两个车站反过来，也就无所谓啦。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long h,w,c,a[1005][1005],dp[1005][1005],ans=1e18;
void solve() 
{
    memset(dp,0x3f3f3f3f,sizeof(dp));
    for(int i=1;i<=h;i++) 
        for(int j=1;j<=w;j++) 
		{
            dp[i][j]=min({a[i][j],dp[i-1][j]+c,dp[i][j-1]+c});
            ans=min({ans,dp[i-1][j]+c+a[i][j],dp[i][j-1]+c+a[i][j]});
        }
}
int main() 
{
    cin>>h>>w>>c;
    for(int i=1;i<=h;i++) 
        for(int j=1;j<=w;j++)
            cin>>a[i][j];
    solve();
    for(int i=1;i<=h;i++) 
		reverse(a[i]+1,a[i]+w+1);//这一行就是把每一行反过来，reverse是反转函数 
    solve();
    cout<<ans;
    return 0; 
}
```

---

## 作者：qw1234321 (赞：2)

这个花费会关于两个点，很烦，所以拆一下，由于有绝对值，所以我们假设 $i \gt i',j \gt j'$，DP 的时候分四个方向都 DP 一遍就行了：

$$a_{i,j} + a_{i',j'} + C \times |i - i'|\ +\ |j - j'| = (a_{i,j} + a_{i',j'} + C \times (i + j)) - (C \times (i' + j'))$$

这样每个点都有一个独立的权值 $a_{i,j} + C \times (i + j)$，将这个值计入状态中。

令 $f_{i,j}$ 表示 ${i,j}$ 点的权值，不难得：

$$f_{i,j} = min({f_{i - 1,j}, f_{i, j - 1}, a_{i, j} - C \times (i + j)})$$

进行四遍 DP 即可，每 DP 一次记得重新初始化并翻转矩阵。

[code.](/paste/6nsxqdxf)

---

## 作者：Hyc_ (赞：1)

题意显而易见，就不多说明了。

### 思路：

这题可以考虑二维前缀最大值，但是式子中的绝对值比较烦人，就把它拆成 $4$ 个部分，分类讨论。

对于左上，右上，左下，右下朝对角的四个方向，分别求一次前缀最大值。

这里以左上到右下的方向为例，其他方向见代码。
令前缀和数组为 $s1$，点权数组为 $a$，$i' \le i'$ 且 $j' \le j$，则递推式如下：

$s1_{i,j}=\max(s1_{i-1,j},s1_{i,j-1},-a_{i,j}+C \times (i+j))$

上面 $\max$ 的前两部分很好理解，而最后一部分为什么要这么做，因为：

$a_{i,j}+a_{i',j'}+C \times (\ |i-i'|+\ |j-j'|)=a_{i,j}+C \times (i+j)-(-a_{i',j'}+C \times (i',j'))$

记得开 `long long`，边界赋极小值，统计答案时注意边界。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1002,inf=0x3f3f3f3f3f3f3f3f;
ll n,m,c,a[N][N],ans=inf;
ll s1[N][N],s2[N][N],s3[N][N],s4[N][N];
int main(){
	scanf("%lld%lld%lld",&n,&m,&c);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%lld",&a[i][j]);
	for(int i=1;i<=n;++i){
		s1[i][0]=s2[i][0]=s3[i][0]=s4[i][0]=-inf;
		s1[i][m+1]=s2[i][m+1]=s3[i][m+1]=s4[i][m+1]=-inf;
	}
	for(int j=1;j<=m;++j){
		s1[0][j]=s2[0][j]=s3[0][j]=s4[0][j]=-inf;
		s1[n+1][j]=s2[n+1][j]=s3[n+1][j]=s4[n+1][j]=-inf;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			s1[i][j]=max(s1[i-1][j],s1[i][j-1]);
			s1[i][j]=max(s1[i][j],-a[i][j]+c*(i+j));
		}
	for(int i=1;i<=n;++i)
		for(int j=m;j;--j){
			s2[i][j]=max(s2[i-1][j],s2[i][j+1]);
			s2[i][j]=max(s2[i][j],-a[i][j]+c*(i+m+1-j));
		}
	for(int i=n;i;--i)
		for(int j=1;j<=m;++j){
			s3[i][j]=max(s3[i+1][j],s3[i][j-1]);
			s3[i][j]=max(s3[i][j],-a[i][j]+c*(n+1-i+j));
		}
	for(int i=n;i;--i)
		for(int j=m;j;--j){
			s4[i][j]=max(s4[i+1][j],s4[i][j+1]);
			s4[i][j]=max(s4[i][j],-a[i][j]+c*(n-1-i+m+1-j));
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			if(i>1||j>1)ans=min(ans,a[i][j]+c*(i+j)-max(s1[i][j-1],s1[i-1][j]));
			if(i>1||j<m)ans=min(ans,a[i][j]+c*(i+m+1-j)-max(s2[i-1][j],s2[i][j+1]));
			if(i<n||j>1)ans=min(ans,a[i][j]+c*(n+1-i+j)-max(s3[i+1][j],s3[i][j-1]));
			if(i<n||j<m)ans=min(ans,a[i][j]+c*(n+1-i+m+1-j)-max(s4[i+1][j],s4[i][j+1]));
		}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：AutomatiC__ (赞：1)

~~虽然出现在DP题单，但是愚只会乱搞捏。~~

考虑每个点 $A_{i, j}$ 能构成的铁路系统的最小花费，设为 $f_{i, j}$，有 $f_{i, j} = A_{i, j} + \min(A_{i',j'} + C \times (|i - i'| + |j - j'|)).$

朴素计算是 $\mathcal{O}(n^4)$ 的，瓶颈在于求出 $\min(A_{i',j'} + C \times(|i - i'| + |j - j'|))$.

精通$\operatorname{dp}$的你一定很熟悉这类形如 $\operatorname{val}(i,j)$ 的花费。考虑化简 $A_{i',j'} + C \times (|i - i'| + |j - j'|)$，按左上、右上、左下、右下四个方向分类讨论，有：

左上：$A_{i', j'} - C \times (i' + j') + C \times (i + j)$.

右上：$A_{i', j'} + C \times (j' - i') + C \times (i - j)$.

左下：$A_{i', j'} + C \times (i' - j') + C \times (j - i)$.

右下：$A_{i', j'} + C \times (i' + j') - C \times (i + j)$.

分离无关项，我们只需要二维前缀和记录四个方向上的最小值即可做到 $\mathcal{O}(n^2)$。

[代码。](https://atcoder.jp/contests/abc210/submissions/39927433)

---

## 作者：fire_hmz (赞：0)

~~这道题可以降黄了~~。
  
首先定义 $dp_{i,j}$：$dp_{i,j}$ 为当前坐标的最小花费。

于是自然就能想到 dp 方程：

$$dp_{i,j} = \min\{dp_{i-1,j}+c,dp_{i,j-1}+c,A_{i,j}\}$$

而我们要求的值便是：
$$
\min\{dp_{i-1,j}+c,dp_{i,j-1}+c\} +A_{i,j}
$$

然后提交，WA！

因为这种方法只能解决车站从左上至右下的情况，所以我们可以从不同的方向 dp 四次，这样就 AC 力。

code：
```cpp
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define int long long
#define pii pair<int, int>
#define il inline
#define p_q priority_queue
#define map unordered_map
#define rg register

using namespace std;

const int N1 = 100005;
const int N2 = 1000006;
const int mod = 998244353;



namespace first_coming {
#define IOSIZE 100000
	int precision = 3, POW[10] = {1,      10,      100,      1000,      10000,
	                              100000, 1000000, 10000000, 100000000, 1000000000
	                             };
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
// #ifdef ONLINE_JUDGE
// #define getchar()                                                         \
//     ((p1 == p2) and                                                       \
//              (p2 = (p1 = ibuf) + fread(ibuf, 1, IOSIZE, stdin), p1 == p2) \
//          ? (EOF)                                                          \
// : (*p1++))
// #define putchar(x)
//     ((p3 == obuf + IOSIZE) && (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf),
//      *p3++ = x)
// #define isdigit(ch) (ch > 47 && ch < 58)
// #define isspace(ch) (ch < 33)
// #endif
	template <typename T>
	inline T read() {
		T s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) && (ch != EOF))
			if (ch == 45)
				w = -1;
		if (ch == EOF)
			return 0;
		while (isdigit(ch))
			s = s * 10 + ch - 48, ch = getchar();
		return s * w;
	}
	template <typename T>
	inline bool read(T& s) {
		s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) && (ch != EOF))
			if (ch == 45)
				w = -1;
		if (ch == EOF)
			return 0;
		while (isdigit(ch))
			s = s * 10 + ch - 48, ch = getchar();
		return s *= w, 1;
	}
	inline bool read(char& s) {
		while (s = getchar(), isspace(s))
			;
		return 1;
	}
	inline bool read(char* s) {
		char ch;
		while (ch = getchar(), isspace(ch))
			;
		if (ch == EOF)
			return 0;
		while (!isspace(ch))
			*s++ = ch, ch = getchar();
		*s = '\000';
		return 1;
	}
	template <typename T>
	inline void print(T x) {
		if (x < 0)
			putchar(45), x = -x;
		if (x > 9)
			print(x / 10);
		putchar(x % 10 + 48);
	}
	inline void print(char x) {
		putchar(x);
	}
	inline void print(char* x) {
		while (*x)
			putchar(*x++);
	}
	inline void print(const char* x) {
		for (int i = 0; x[i]; i++)
			putchar(x[i]);
	}
	inline bool read(std::string& s) {
		s = "";
		char ch;
		while (ch = getchar(), isspace(ch))
			;
		if (ch == EOF)
			return 0;
		while (!isspace(ch))
			s += ch, ch = getchar();
		return 1;
	}
	inline void print(std::string x) {
		for (int i = 0, n = x.size(); i < n; i++)
			putchar(x[i]);
	}
	inline bool read(bool& b) {
		char ch;
		while (ch = getchar(), isspace(ch))
			;
		b = ch ^ 48;
		return 1;
	}
	inline void print(bool b) {
		putchar(b + 48);
	}
	inline bool read(double& x) {
		int a = 0, b = 0;
		char ch = getchar();
		bool f = 0;
		while (ch < 48 || ch > 57) {
			if (ch == 45)
				f = 1;
			ch = getchar();
		}
		while (47 < ch && ch < 58) {
			a = (a << 1) + (a << 3) + (ch ^ 48);
			ch = getchar();
		}
		if (ch != 46) {
			x = f ? -a : a;
			return 1;
		}
		ch = getchar();
		while (47 < ch && ch < 58) {
			b = (b << 1) + (b << 3) + (ch ^ 48), ch = getchar();
		}
		x = b;
		while (x > 1)        x /= 10;
		x /= 10;
		x = f ? -a - x : a + x;
		return 1;
	}
	inline void print(double x) {
		if (x < 0) {
			putchar(45), x = -x;
		}
		x = round((long double)x * POW[precision]) / POW[precision],
		print((long long)x), putchar(46), x -= (long long)(x);
		for (int i = 1; i <= precision; i++)
			x *= 10, putchar(x + 48), x -= (int)x;
	}
	template <typename T, typename... T1>
	inline int read(T& a, T1&... other) {
		return read(a) + read(other...);
	}
	template <typename T, typename... T1>
	inline void print(T a, T1... other) {
		print(a), print(other...);
	}
	struct Fast_IO {
		~Fast_IO() {
			fwrite(obuf, p3 - obuf, 1, stdout);
		}
	} io;
	template <typename T>
	Fast_IO& operator>>(Fast_IO& io, T& b) {
		return read(b), io;
	}
	template <typename T>
	Fast_IO& operator<<(Fast_IO& io, T b) {
		return print(b), io;
	}
}

namespace second_coming {
	int fac[N2] = {0};
	il void Cinit(int p) {
		fac[0] = 1;
		for (int i = 1; i < N2; i++) {
			fac[i] = fac[i - 1] * i % p;
		}
	}
	il int qpow(int a, int b, int p) {
		int ans = 1;
		while (b) {
			if (b & 1) {
				ans = ans * a % p;
			}
			a = a * a % p;
			b >>= 1;
		}
		return ans;
	}
	il int C(int n, int m, int p) {
		if (m > n || m < 0) {
			return 0;
		}
		return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p;
	}
	il int Lucas(int n, int m, int p) {
		if (!m)
			return 1;
		return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
	}
	il int GCD(int n, int m, int p) {
		return __gcd(n, m) % p;
	}
	il int LCM(int n, int m, int p) {
		return n * m % p * qpow(GCD(n, m, p), p - 2, p) % p;
	}
}
using namespace first_coming;
using namespace second_coming;

#define debug 0
#define endl '\n'

int _test_ = 1;
int n, m, k;
int a[1145][1145], dp[1145][1145][2], bq[1145][1145][2], dq[1145][1145][2], bp[1145][1145][2];
namespace third_coming {

	void init() {
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) cin >> a[i][j];
		}
	}

	void solve() {
		memset(dp, 0x3f, sizeof(dp));
		memset(bq, 0x3f, sizeof(bq));
		memset(bp, 0x3f, sizeof(bp));
		memset(dq, 0x3f, sizeof(dq));
		int mn = 0x3f3f3f3f3f3f3f3f;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i][j][1] = min(dp[i][j - 1][0] + k, dp[i - 1][j][0] + k) + a[i][j];
				dp[i][j][0] = min(dp[i][j - 1][0] + k, min(dp[i - 1][j][0] + k, a[i][j]));
				mn = min(mn, dp[i][j][1]);
			}
		}
		for (int i = n; i >= 1; i--) {
			for (int j = m; j >= 1; j--) {
				bq[i][j][1] = min(bq[i][j + 1][0] + k, bq[i + 1][j][0] + k) + a[i][j];
				bq[i][j][0] = min(bq[i][j + 1][0] + k, min(bq[i + 1][j][0] + k, a[i][j]));
				mn = min(mn, bq[i][j][1]);
			}
		}
		for (int i = n; i >= 1; i--) {
			for (int j = 1; j <= m; j++) {
				dq[i][j][1] = min(dq[i][j - 1][0] + k, dq[i + 1][j][0] + k) + a[i][j];
				dq[i][j][0] = min(dq[i][j - 1][0] + k, min(dq[i + 1][j][0] + k, a[i][j]));
				mn = min(mn, dq[i][j][1]);
			}
		}
		for (int i = n; i >= 1; i--) {
			for (int j = 1; j <= m; j++) {
				bp[i][j][1] = min(bp[i][j - 1][0] + k, bp[i + 1][j][0] + k) + a[i][j];
				bp[i][j][0] = min(bp[i][j - 1][0] + k, min(bp[i + 1][j][0] + k, a[i][j]));
				mn = min(mn, bq[i][j][1]);
			}
		}
		cout << mn;
	}

	void main() {
		init();
		solve();
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
#ifdef debug
//	freopen("third_coming.in", "r", stdin);
//	freopen("third_coming.out", "w", stdout);
#endif
	third_coming::main();
	return 0;
}
```

---

## 作者：Little_Cabbage (赞：0)

> 涉及知识点：动态规划

# 解题思路

因为 $W$ 和 $H$ 的范围都很大，直接枚举两个车站的位置肯定会时间超限的，所以考虑动态规划。

定义 $dp_{i, j}$ 表示所有横坐标小于等于 $i$ 且纵坐标小于等于 $j$ 的点的最小的 $a_{i', j'} + c\times (i'+j')$ 的值。

非常容易可以得到动态转移方程：

$$
dp_{i, j} = \min(dp_{i, j}, a_{i, j} + c\times (i + j))
$$

每个 $dp_{i, j}$ 的初始值为：

$$
dp_{i, j} = \min(dp_{i - 1, j}, dp_{i, j - 1}, dp_{i - 1, j - 1})
$$

答案为：

$$
res = \min(res, dp_{i, j} + a_{i, j} + c\times (i + j))
$$

我们发现如果只按照上面的方法做一次动态规划，相当于从矩阵的左上角向右下角转移了一次，并没有考虑到全部情况，还需要从矩阵的右上角向左下角转移一次，相当于把矩阵的每行调转顺序，再按上面的方法转移一次。

最后输出 $res$ 即可。

小提醒：由于当前点 $(i, j)$ 的值可能会比没有更新的 $dp_{i,j}$ 的值更优秀，所以需要先初始化 $dp_{i, j}$，然后更新 $res$，最后计算 $dp_{i, j}$。

# 代码

~~丑陋的赛时代码。~~

这里我就只放了核心部分，剩余的部分请读者自己完成。

```cpp
res = inf;
memset(dp, 0x3f, sizeof dp);
rep(i, 1, n) rep(j, 1, m) {
	dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
	if (i > 1 || j > 1) res = min(res, dp[i][j] + a[i][j] + c * (i + j));
	if (i > 1 || j > 1) dp[i][j] = min(dp[i][j], a[i][j] - c * (i + j));
	else dp[i][j] = a[i][j] - c * (i + j);
}
memset(dp, 0x3f, sizeof dp);
rep(i, 1, n) reverse(a[i] + 1, a[i] + m + 1);
rep(i, 1, n) rep(j, 1, m) {
	dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
	if (i > 1 || j > 1) res = min(res, dp[i][j] + a[i][j] + c * (i + j));
	if (i > 1 || j > 1) dp[i][j] = min(dp[i][j], a[i][j] - c * (i + j));
	else dp[i][j] = a[i][j] - c * (i + j);
}
cout << res << endl;
```

---

## 作者：wth2026 (赞：0)

# 题目大意
高桥王国可以表示为一个有 $H$ 行和 $W$ 列的网格。让 $(i, j)$ 表示从北边起第 $i$ 行和从西边起第 $j$ 列的方格。

最近，越来越多的王国公民要求修建铁路，现在国王高桥别无选择，只能修建一条铁路。  
铁路的建设将分为以下两个阶段。

- 首先，选择两个不同的方格，在每个方格上建造一个车站。在 $(i, j)$ 方格上建造车站需要花费 $A_{i,j}$ 日元。
- 然后，建造一条连接这两个车站的铁轨。当两个车站分别位于 $(i, j)$ 和 $(i', j')$ 方格时，需要花费 $C \times (|i-i'| + |j-j'|)$ 日元。 $|x|$ 表示 $x$ 的绝对值）。

高桥的首要任务是尽可能减少建设成本，而不是为市民提供更多便利。  
请列式计算该铁路的总造价。

# 题目思路
前置知识：AtCoder $1$ 秒可以跑到 $1.1\times 10^9$。

由此可得，我们使用 $O(n^3)$ 的时间复杂度通过此题。

首先，我们使用一个数组 $Mp_{i,j}$ 表示第 $i$ 行对于第 $j$ 列的最小值，可以在 $O(hw^2)$ 的时间复杂度内求出来。

然后，现枚举每一行 $i$，对于第 $j$ 行第 $k$ 列，可以通过前面求出的数组 $O(1)$ 求出最小值。此段代码的时间复杂度是 $O(h^2w)$。

最后对所有答案求一个最小值就可以了。

# [AC Code](https://atcoder.jp/contests/abc210/submissions/57238015)

---

## 作者：Swirl (赞：0)

> 涉及知识点：dp。

提供一个本质和其他题解差不多相同但转移应该更好理解一点的 dp 方式。

对于一条铁路 $(u, v)$ 到 $(x, y)$，我们只考虑 $u \le x$ 且 $v \le y$ 的情况，因为剩下的情况可以通过将矩阵旋转用同样的方法做。

我们称 $(u, v)$ 为一条线路的起点，$(x, y)$ 为终点。

首先，$(i, j)$ 位置上的点，要么是车站，要么是铁路上的线，否则就是空地。

空地不用考虑。

所以定义 $f(i, j, k)$ 为 $(i, j)$ 上点的状态，$k \in \{0, 1\}$。

因为一个起点车站和一段铁路本质上没有区别，只是起点需要额外花钱，所以可以将其归类为一类，终点车站为另一类。

- $k = 0$，起点车站的情况只需赋为 $a_{i, j}$。而铁路则需从左、上位置转移，即 $\min\{f(i - 1, j, 0), f(i, j - 1, 0)\} + c$。
- $k = 1$，与铁路类似，从左、上的 $0$ 类点转移，只不过要加上 $a_{i, j}$，即 $\min\{f(i - 1, j, 0), f(i, j - 1, 0)\} + c + a_{i, j}$。
- 最后统计答案时只需将所有的 $f(i, j, 1)$ 取最小值即可，即 $\min ^ {h} _ {i = 1}\min ^ {w} _ {j = 1} f(i, j, 1)$。

---

```cpp
namespace zqh {
	int h, w, c;
	int a[1005][1005], b[1005][1005];
	int dp[1005][1005][2];

	void init() {
		cin >> h >> w >> c;
		rep (i, 1, h) {
			rep (j, 1, w) {
				cin >> a[i][j];
			}
		}
	}
	
	int work() {
		memset(dp, 0x3f, sizeof(dp));
		int ans = 0x3f3f3f3f3f3f3f3f;
		rep (i, 1, h) {
			rep (j, 1, w) {
				dp[i][j][1] = min(dp[i][j - 1][0], dp[i - 1][j][0]) + a[i][j] + c;
				dp[i][j][0] = min(min(dp[i][j - 1][0], dp[i - 1][j][0]) + c, a[i][j]);
				ans = min(ans, dp[i][j][1]);
			}
		}
		return ans;
	}
	
	void xz() {
		rep (i, 1, h) {
			rep (j, 1, w) {
				b[j][h - i + 1] = a[i][j];
			}
		}
		swap(h, w);
		rep (i, 1, h) rep (j, 1, w) a[i][j] = b[i][j];
	}

	void solve() {
		int ans = 0x3f3f3f3f3f3f3f3f;
		ans = min(ans, work());
		xz();
		ans = min(ans, work());
		xz();
		ans = min(ans, work());
		xz();
		ans = min(ans, work());
		cout << ans;
	}

	void main() {
		init();
		solve();
	}
}  // namespace zqh
```

本做法由 second_coming 提出（但没解释清楚），笔者改进了一下。

---

## 作者：YuYuanPQ (赞：0)

没有场切是因为 dp 太差了。

考虑动态规划。

设 $dp_{i,j}$ 表示现在在点 $(i,j)$，已经建了 $1$ 个车站或者要在点 $(i,j)$ 建车站的最小花费。

从左上角 dp 到右下角。

$dp_{i,j}$ 有 $3$ 种转移方式：

- 在当前点 $(i,j)$ 修车站。

- 从上面的点 $(i-1,j)$ 连接一段铁路到 $(i,j)$。

- 从左边的点 $(i,j-1)$ 连接一段铁路到 $(i,j)$。

对这 $3$ 种情况取 $\min$。

此时考虑建第 $2$ 个车站。

有 $2$ 种转移方式：

- 从上面的点 $(i-1,j)$ 连接一段铁路到 $(i,j)$，并在 $(i,j)$ 建了车站。

- 从左边的点 $(i,j-1)$ 连接一段铁路到 $(i,j)$，并在 $(i,j)$ 建了车站。

$ans$ 对这 $2$ 种情况取 $\min$。

状态转移方程：

$$
dp_{i,j}=\min(\min(dp_{i-1,j},dp_{i,j-1}),a_{i,j}-C\times(i+j))
$$

参考了 @wflhx2011 reverse 函数的使用。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 1e18
#define MAXN 1010
using namespace std;
ll h,w,C;
ll a[MAXN][MAXN];
ll dp[MAXN][MAXN],ans;
ll my_min(ll x,ll y){return x<y?x:y;}
void DP()
{
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            dp[i][j]=my_min(my_min(dp[i-1][j],dp[i][j-1]),a[i][j]-C*(i+j));
            ans=my_min(ans,a[i][j]+C*(i+j)+my_min(dp[i-1][j],dp[i][j-1]));
        }
    }
    return;
}
int main()
{
    ans=INF;
    scanf("%lld%lld%lld",&h,&w,&C);
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++) scanf("%lld",&a[i][j]);
    DP();
    for(int i=1;i<=h;i++) 
		reverse(a[i]+1,a[i]+w+1);
    DP();
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：BigJoker (赞：0)

线性 DP

设 $f_{i,j}$ 表示从 $(1,1)\rightarrow (i,j)$ 的路径上，已经确定了一个车站，从这个确定的车站走到 $(i,j)$ 的最小代价。

那么 $f_{i,j}\gets \min{\large\{}a_{i,j},c+\min\{f_{i-1,j},f_{i,j-1}\}{\large\}}$

那么答案怎么算呢？设 $g_{i,j}$ 表示第二个车站修在 $(i,j)$ 上的最小代价。

那么 $g_{i,j}\gets a_{i,j}+c+\min\{f_{i-1,j},f_{i,j-1}\}$

最后的答案就是 $g$ 中的最小值。

不过仍然有一些问题，上述的解法仅仅只是考虑了第一个车站在第二个车站左上的情况，并没有考虑右上的情况，不过这类情况也很好处理，反着跑一遍 $f$ 就可以了。

---

