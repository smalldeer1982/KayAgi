# [ABC262D] I Hate Non-integer Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc262/tasks/abc262_d

項数が $ N $ の正整数列 $ A=(a_1,\ldots,a_N) $ が与えられます。  
 $ A $ の項を $ 1 $ 個以上選ぶ方法は $ 2^N-1 $ 通りありますが、そのうち選んだ項の平均値が整数であるものが何通りかを $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ A $ の項を選ぶ方法それぞれに対する平均値は以下のようになります。 - $ a_1 $ のみを選んだ場合、平均値は $ \frac{a_1}{1}=\frac{2}{1}\ =\ 2 $ であり、整数である。 - $ a_2 $ のみを選んだ場合、平均値は $ \frac{a_2}{1}=\frac{6}{1}\ =\ 6 $ であり、整数である。 - $ a_3 $ のみを選んだ場合、平均値は $ \frac{a_3}{1}=\frac{2}{1}\ =\ 2 $ であり、整数である。 - $ a_1 $ と $ a_2 $ を選んだ場合、平均値は $ \frac{a_1+a_2}{2}=\frac{2+6}{2}\ =\ 4 $ であり、整数である。 - $ a_1 $ と $ a_3 $ を選んだ場合、平均値は $ \frac{a_1+a_3}{2}=\frac{2+2}{2}\ =\ 2 $ であり、整数である。 - $ a_2 $ と $ a_3 $ を選んだ場合、平均値は $ \frac{a_2+a_3}{2}=\frac{6+2}{2}\ =\ 4 $ であり、整数である。 - $ a_1 $ と $ a_2 $ と $ a_3 $ を選んだ場合、平均値は $ \frac{a_1+a_2+a_3}{3}=\frac{2+6+2}{3}\ =\ \frac{10}{3} $ であり、整数ではない。 以上より、$ 6 $ 通りの選び方が条件を満たします。

### Sample Explanation 2

どのように $ A $ の項を $ 1 $ 個以上選んでも平均値が $ 5 $ になります。

## 样例 #1

### 输入

```
3
2 6 2```

### 输出

```
6```

## 样例 #2

### 输入

```
5
5 5 5 5 5```

### 输出

```
31```

# 题解

## 作者：Hell0_W0rld (赞：9)

# [abc262](https://atcoder.jp/contests/abc262/tasks/abc262_d) Solution
~~考场上想到思路写挂的菜鸡【汗颜】~~
## 题目大意
给定一个长度为 $N$ 序列 $A$，从中选若干个数，有几种选法使得选出的数平均数是整数？

答案对 $998244353$ 取模，$1\leq N\leq 100,\ A_i\leq10^9$。
## 朴素解法
暴力枚举每个数选还是不选，复杂度 $\Theta(2^N)$，显然无法通过。
## 题目分析以及正解
我们可以枚举所有的选数个数 $i$。

+ 当 $i=1$ 时，有 $N$ 种方法。
+ 当 $i=2$ 时，选出的数一定是 $2$ 的倍数。
+ 当 $i=3$ 时，选出的数一定是 $3$ 的倍数。
+ …………
+ 当 $i=N$ 时，选出的数一定是 $N$ 的倍数。

于是乎，我们考虑 dp。

$f[i][j][k][l]$：从前 $j$ 个数中选择 $k$ 个，总和 $\bmod\ i$ 余 $l$。

我们发现，$100^4$ 空间会爆炸！而且我们发现，$f[i][][][]$ 和 $f[i+1][][][]$ 填写无关！于是我们覆盖式填写，把 $[i]$ 维度省略，大不了每一次清空。

我们发现，**用已知的 $f$ 去更新未知的 $f$，要更轻松。**~~作者太蒻了，忘记是 push 还是 pull 了。~~

可以发现，如果我们枚举 $j,k,l$，
+ 如果 $j$ 号不选，用 $f[j][k][l]$ 更新 $f[j+1][k][l]$。
+ 如果 $j$ 号选，用 $f[j][k][l]$ 更新 $f[j+1][k+1][(l+a_j)\bmod i]$

最后统计答案：

因为 $i$ 是选数个数，对于每一次的 $i$ 循环，答案显然是 $f[N][i][0]$。

时间复杂度 $\Theta(N^4)$，实际计算量 $\approx \frac{N^4}{4}$，可以通过。
## Talk is cheap,show my code.
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define rep(i,l,r) for(register ll i=(l);i<=(r);i++)
#define PLL pair<ll,ll>
#define PLD pair<ld,ld>
#define FI first
#define SC second
#define MP make_pair
using namespace std;
const ll INF=9223372036854775807;
const ld ERR=1e-12;
void File(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
void IOS(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
}//缺省源
const ll N=109,MOD=998244353;
ll n,a[N],f[N][N][N],ans;
int main(){
	IOS();
	cin>>n;
	rep(i,1,n)cin>>a[i];
	rep(i,1,n){
		memset(f,0,sizeof(f));
		f[1][0][0]=1;
		rep(j,1,n)rep(k,0,i)rep(l,0,i-1){
			f[j+1][k][l]+=f[j][k][l];
			f[j+1][k][l]%=MOD;
			if(k!=i)f[j+1][k+1][(l+a[j])%i]+=f[j][k][l],f[j+1][k+1][(l+a[j])%i]%=MOD;
		}
		ans=(ans+f[n+1][i][0])%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：LionBlaze (赞：2)

I Hate Non-integer Number.

---

如果你把子序列看成了子串那么恭喜你和我一样。如果真的是子串那么这题前缀和秒了。

> 本文通篇省略取模，因为不重要且太简单。所有运算均在模意义下进行。

首先显然答案的紧的上界是 $2^N$，最优秀（指没有任何冗余枚举）的暴力也不能通过。考虑 DP。

根据直觉可得设 $f_{i,j,k,l}$ 表示考虑前 $i$ 个元素，选取 $j$ 个，模 $k$ 余 $l$ 的方案数（空间问题？不存在的，内存限制 $1.00\mathrm{GB}$，实在担心也可以滚动数组省略 $i$）。显然需要满足条件 $0 \le j \le i\le N,0 \le l < k \le N$（原则上 $i=j=0$ 不可以，但是为了方便转移这里表示不考虑任何元素，而 $k>N$ 实际上有意义但是用不上）。

则此题答案为 $\displaystyle \sum_{j=1}^N f_{N,j,j,0}$，也就是长度为 $j$ 的和模 $j$ 余 $0$ 的方案数之和。长度不能为 $0$。

考虑如何进行状态转移。第 $i$ 个元素可以选或者不选，若选则会让和 $+a_i$ 且长度 $+1$，不选则不变。

故 $f_{i,j,k,l}=f_{i-1,j-1,k,l-a_i}+f_{i-1,j,k,l}$。如果 $j=0$ 则没有加号左边的那一坨。

边界条件是 $f_{0,0,k,0}=1$。

那么我们就可以愉快地解决这题啦！如果你用滚动数组（下面的代码就是用的）那么注意 $j,l$ 需要降序枚举。

代码：

```cpp
#include <cstdio>

using namespace std;

int f[105][105][105];

int main()
{
	int n;
	scanf("%d", &n);
	for (int k = 1; k <= n; k++)
	{
		for (int l = 0; l < k; l++)
		{
			f[0][k][0] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		for (int j = i; j >= 1; j--)
		{
			for (int k = 1; k <= n; k++)
			{
				for (int l = k - 1; l >= 0; l--)
				{
					f[j][k][l] = (f[j][k][l] + f[j-1][k][((l - a) % k + k) % k]) % 998244353;
					// printf("f[%d][%d][%d][%d] = %d （考虑前 %d 个，选取 %d 个，模 %d 余 %d）\n", i, j, k, l, f[j][k][l], i, j, k, l);
				}
			}
		}
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum = (sum + f[i][i][0]) % 998244353;
	}
	printf("%d\n", sum);
	return 0;
}
```

[submission](https://atcoder.jp/contests/abc262/submissions/65825183)。

---

## 作者：_qingshu_ (赞：2)

# 题意：

给定一个长度为 $N$ 数列，求从中选出若干个数平均数为整数有多少种选法，答案对于 $998244353$ 取模。

# 思路：

求方案数那么考虑 DP。

我们定义 $f_{i,j,k}$，其中 $i$ 表示在前 $i$ 个数中选取 $j$ 个数，最后的余数是 $k$。

我们需要有四层循环：
- 总共选取了 $i$ 个数。（需要清空 dp 数组）

- 考虑到了前 $j$ 个数。

- 到现在选取了 $k$ 个数。

- 最后的余数是 $d$。

有了这个定义，那么动态转移方程就很好推了：

- 如果不选当前这个数。

$$dp_{(j+1),k,d}=dp_{(j+1),k,d}+dp_{j,k,d}$$

- 如果选择了当前这个数。

$$dp_{(j+1),(k+1),((d+a_j)\%i)}=dp_{(j+1),(k+1),((d+a_j)\%i)}+dp_{j,k,d}$$

最后统计答案的时候加上 $dp_{(n+1),i,0}$，之所以第一维是 $n+1$，是因为我们转移方程是一个递推式，所以到 $n$ 的答案实际上记录的位置会在下一位。

---

## 作者：Tsawke (赞：2)

# [[ABC262D] I Hate Non-integer Number](https://www.luogu.com.cn/problem/AT_abc262_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC262D)

## 题面

已知一个长度为 $N$ 的数列 $a_1,a_2,\cdots a_N$，从数列中选出至少一个数，使选出的数平均数为整数，求有多少种这样的方案。

## Solution

经典DP，考虑设状态 $ dp(i, j, p, k) $，表示考虑前 $ i $ 个数里选 $ j $ 个的和模 $ p $ 余 $ k $。

转移显然，即：
$$
dp(i, j, p, k) \rightarrow dp(i + 1, j, p, k)
$$

$$
dp(i, j, p, k) \rightarrow dp(i + 1, j + 1, p, (k + a_{i + 1}) \bmod{p})
$$

最终答案即为 $ \sum_{i = 1}^n dp(N, i, i, 0) $。

然后需要注意转移过程中存在 $ j = 0 $，但答案不可以 $ j = 0 $，原因显然。

初始值即为 $ dp(1, 0, i, 0) = 1, dp(1, 1, i, a_1 \bmod{i}) = 1 $。

发现空间无法支持，故可以将 $ i $ 维滚动掉。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

int N;
ll a[110];
ll dp[2][110][110][110];
ll ans(0);

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)a[i] = read();
    for(int i = 1; i <= N; ++i)dp[1][0][i][0] = 1, dp[1][1][i][a[1] % i] = 1;
    for(int i = 1; i < N; ++i){
        for(int j = 0; j <= 100; ++j)for(int p = 0; p <= 100; ++p)for(int k = 0; k <= 100; ++k)dp[!(i & 1)][j][p][k] = 0;
        for(int j = 0; j <= i; ++j)
            for(int p = 1; p <= N; ++p)
                for(int k = 0; k < p; ++k)
                    (dp[!(i & 1)][j][p][k] += dp[i & 1][j][p][k]) %= MOD,
                    (dp[!(i & 1)][j + 1][p][(k + a[i + 1]) % p] += dp[i & 1][j][p][k]) %= MOD;
    }
    for(int i = 1; i <= N; ++i)(ans += dp[N & 1][i][i][0]) %= MOD;
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_07 初稿

---

## 作者：luwanning (赞：1)

# 题目思路
考虑 DP。

状态：$f[i][j][k][l]$ 表示考虑了前 $i$ 个数，$n$ 个数中要取 $j$ 个数，现在已经取了 $k$ 个数，这 $k$ 个数的和 $\operatorname{mod}j$ 余 $l$。

转移分两种情况。

- 不取第 $i+1$ 个数，$f[i+1][j][k][l]=f[i][j][k][l]$。
- 取第 $i+1$ 个数，$f[i+1][j][k+1][(l+a[i+1])\operatorname{mod}j]=f[i][j][k][l]$。

最后统计答案，因为要整除，所以答案是 $max_{1\le {i}\le{n}}(f[n][i][i][0])$。

时间复杂度为 $\Theta(n^4)$，但实际运行会比这快，可以通过。

好了，上代码：
```
#include <cstdio>

using namespace std;

const int N = 102, p = 998244353;
int n, a[N], f[N][N][N][N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		f[0][i][0][0] = 1;//初始化
	for (int i = 0; i < n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 0; k <= j; k++)
				for (int l = 0; l < j; l++) {
					f[i + 1][j][k][l] += f[i][j][k][l];
					f[i + 1][j][k][l] %= p;//注意每次更新完都要模p!不然爆int
					f[i + 1][j][k + 1][(l + a[i + 1]) % j] += f[i][j][k][l];
					f[i + 1][j][k + 1][(l + a[i + 1]) % j] %= p;
				}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += f[n][i][i][0], ans %= p;//统计答案
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题还是有一点难度的，我们首先可以发现这是一个 Dp，然后我们一眼就能想到一个定义状态的方式为 $f_{i,j,k,l}$ 为前 $i$ 个数选 $j$ 个其总和模 $k$ 等于 $l$ 的方案数。我们这样定义的原因是因为既然平均数为整数，所以肯定有 $sum\bmod l=0$ 这里的 $sum$ 为总和，$l$ 为个数。我们转移时可以将第一维压掉，然后枚举一个 $j,k,l$ 因为 $k$ 可以固定所以就很好转移了，方程为 $f_{i,j,k,l}=f_{i,j,k,l}+f_{i-1,j,k,l}+f_{i-1,j-1,k,(l+k\times 10^9-a_i)\bmod k}$ 这里之所以要乘 $10^9$ 是因为我们在加上以后还要模上 $k$ 所以为了减之后不为负数先要加过原数，就是能够使 $(l+k\times 10^9-a_i)\equiv (l-a_i)\bmod k$。

答案就是 $f_{n,i,i,0}$ 的和。

# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
const int N=101;
int f[2][N][N][N],n,a[N];//从前i个中选了j个总和模k=l 
const int mod=998244353;
fire main() {
	cin>>n;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) {
		rep(k,1,n) f[0][0][k][0]=1;
		rep(j,1,i) {
			rep(k,1,n) {
				rep(l,0,k-1) {
					f[1][j][k][l]+=(f[0][j][k][l]+f[0][j-1][k][(l+k*1000000000-a[i])%k])%mod;
				}
			}
		}
		rep(j,1,i) {
			rep(k,1,n) {
				rep(l,0,k-1) {
					f[0][j][k][l]=f[1][j][k][l];
					f[1][j][k][l]=false;
				}
			}
		}
	}
	int res=0;
	rep(j,1,n) (res+=f[0][j][j][0])%=mod;
	print(res);
	return false;
}
```

---

## 作者：Demons_Killer (赞：1)

# 思路：
考虑动态规划。

$f_{i,j,k}$ 表示前 $i$ 个数中选 $j$ 个数余数为 $k$ 的情况数。通过对不同状态的枚举，将第 $i$ 个状态与前面的状态加起来，依次递推，每次刷新一下对应状态所得的余数，可求出最后的答案为不同的 $j$ 加起来，也就是取不同数量的状态给加起来。

由思路可得不选状态转移方程为 $f_{i,j,k}=f_{i+1,j,k}$，选的状态转移方程为 $f_{i,j,k}=f_{i+1,j+1,(k+a_{j})\mod k}$。
# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define rep(i,l,r) for(register ll i=(l);i<=(r);i++)
#define PLL pair<ll,ll>
#define PLD pair<ld,ld>
#define FI first
#define SC second
#define MP make_pair
using namespace std;
const ll INF=9223372036854775807;
const ld ERR=1e-12;
const ll N=109,MOD=998244353;
ll n,a[N],f[N][N][N],ans;
int main(){
	cin>>n;
	rep(i,1,n)cin>>a[i];
	rep(i,1,n){
		memset(f,0,sizeof(f));
		f[1][0][0]=1;
		rep(j,1,n)rep(k,0,i)rep(l,0,i-1){
			f[j+1][k][l]+=f[j][k][l];
			f[j+1][k][l]%=MOD;
			if(k!=i)f[j+1][k+1][(l+a[j])%i]+=f[j][k][l],f[j+1][k+1][(l+a[j])%i]%=MOD;
		}
		ans=(ans+f[n+1][i][0])%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：yuhong056 (赞：0)

# 题解：AT_abc262_d [ABC262D] I Hate Non-integer Number
本题解提供一个空间较小，代码也很简短的做法。
## 思路
要让选出的数平均数为整数，那么明显选出的数之和要能被选出的数的个数整除。

那么，我们就可以直接枚举选出多少个数，看有多少种方式满足要求即可。

而数可以选与不选，很明显就是一个 01 背包。

因此这道题可以使用 01 背包 dp。
## dp 状态
很明显，$dp_{i, j, k}$ 就是前 $i$ 个数选出 $j$ 个最终和对选出的数的个数取模后为 $k$ 的方案数。
## dp 转移
两种情况：
1. 第 $i$ 个数选，$dp_{i - 1, j - 1, k - a_i} \to dp_{i, j, k}$。
2. 第 $i$ 个数不选，$dp_{i - 1, j, k} \to dp_{i, j, k}$。

此时，空间复杂度为 $O(n^3)$，足以通过此题。

但是，我们发现，$dp_i$ 这一维仅依赖于 $dp_{i - 1}$，因此可以滚动数组或降维优化。
## Code
```cpp
#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353, MAXN = 105;

int a[MAXN];
int dp[MAXN][MAXN];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	int ans = 0;
	for(int k = 1; k <= n; k++) {
		for(int j = 0; j <= k; j++) { // 清空 dp 数组
			for(int s = 0; s < k; s++) {
				dp[j][s] = 0;
			}
		}
		dp[0][0] = 1; // 初始化
		for(int i = 1; i <= n; i++) {
			for(int j = k; j > 0; j--) {
				for(int s = 0; s < k; s++) {
					int ls = (s - a[i] % k + k) % k; // 计算出不选 a[i] 的和模 k 的值
					dp[j][s] = (dp[j][s] + dp[j - 1][ls]) % MOD; // 做 dp 转移，这里使用了降维优化
				}
			}
		}
		ans = (ans + dp[k][0]) % MOD;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Phoenix114514 (赞：0)

## AT_abc262_d [ABC262D] I Hate Non-integer Number
一道较有思维难度的 dp。
### 思路
记 $dp_{i,j,k}$ 为前 $i$ 个数中选 $j$ 个数的和对  $j$ 取模后的结果是 $k$。为什么要记余数呢？因为记和的活会爆空间，记余数后的答案也显而易见（见下）。状态转移方程如下：
- 初始化 $dp_{0,0,0}=1$
- 若选 $j$，则 $dp_{i+1,j,k}=(dp_{i+1,j,k}+dp_{i,j,k})\bmod 998244353 $
- 若不选，则 $dp_{i+1,j+1,(k+a_{i+1})\bmod i}=(dp_{i+1,j+1,(k+a_{i+1})\bmod i}+dp_{i,j,k})\bmod 998244353$

最后的答案就是
$$
\sum_{i=1}^n (dp_{n,i,0}\bmod 998244353)
$$
~~Latex不太美观，勿喷！~~
### CODE

```cpp
#include<bits/stdc++.h>
#include<bits/stl_algo.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
#define ull unsigned long long
#define ui unsigned int
const int mod=998244353;
int n,a[105],dp[105][105][105];
int ans;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for (int i=1;i<=n;i++)cin>>a[i];
    auto begin_=chrono::high_resolution_clock::now();//计时器而已，不要管
    for (int i=1;i<=n;i++){
        memset(dp,0,sizeof(dp));
        dp[0][0][0]=1;
        for (int j=0;j<n;j++){
            for (int k=0;k<=min(i,j);k++){
                for (int l=0;l<i;l++){
                    dp[j+1][k][l]+=dp[j][k][l];
                    dp[j+1][k][l]%=mod;
					if (k!=i)dp[j+1][k+1][(l+a[j+1])%i]+=dp[j][k][l];
					dp[j+1][k+1][(l+a[j+1])%i]%=mod;
                }
            }
        }
        ans+=dp[n][i][0];
        ans%=mod;
    }
    cout<<ans%mod<<endl;
    auto end_=chrono::high_resolution_clock::now();
    cerr<<chrono::duration_cast<chrono::milliseconds>(end_-begin_).count()<<"ms"<<endl;
    return 0;
}
```

---

