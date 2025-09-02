# [ABC267D] Index × A(Not Continuous ver.)

## 题目描述

有一个长度为 $N$ 整数数列 $A=(A_1,A_2,...,A_N)$ 。

现在假设有一个长度为 $M$ 的序列 $B$ ,并且 $B$ 是 $A$ 的**子序列**。请找到 $\sum_{i=1}^M i\times B_i$ 的最大值。

## 说明/提示

#### 注意事项
若序列 $S$ 是长度为 $L$ 的数列 $T$ 的**子序列**，则 $S$ 是数列 $T$ 删除任意 $i\ (i\in [0,L])$ 个元素得到的。

比如说， $(10,30)$ 是 $(10,20,30)$ 的字串，但是 $(20,10)$ 不是。


+ $1\le M\le N\le 2000$
+ $-2\times 10^5\le A_i\le 2\times 10^5$
+ 所有输入数据均为整数

#### 样例解释
对于**样例一**，当 $B=(A_1,A_4)$ 时，$\sum_{i=1}^M i\times B_i=1\times 5+2\times 8=21$ 。因为不可能达到 $22$ 或者更大的值，所以答案是 $21$ 。

## 样例 #1

### 输入

```
4 2
5 4 -1 8```

### 输出

```
21```

## 样例 #2

### 输入

```
10 4
-3 1 -4 1 -5 9 -2 6 -5 3```

### 输出

```
54```

# 题解

## 作者：Vegetableless (赞：4)

## 题目简述
给定长 $n$ 的序列，从中选取 $m$ 个数为子序列 $b$ ，求最大 $\sum_{j=1}^{m} b_{j} \times j$。

## solution

很容易发现这道题目用 dp 解决，首先我们可以设 $dp_{i,j,k}$ 为前 $i$ 个数选或不选为 $b_j$ 能得的最大值（$k$ 为 `0` 或 `1`)，选的情况下就从前一个选和不选中挑出一个最优解加上 $a_i \times j$，不选的情况就是从前面选和不选中挑出一个最优解，直接赋值。

那么，方程就是：

$$dp_{i,j,0} = \max (dp_{i-1,j,0} , dp_{i-1,j,1})$$
$$dp_{i,j,1} = \max (dp_{i-1,j-1,1} , dp_{i-1,j-1,0}) + a_i \times j$$

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e3 + 5;

int a[N] , dp[N][N][2] , m , n;

#define ioO2 std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);

signed main(){
	ioO2
	std::cin >> n >> m;
	for(int i = 1;i<=n;++i){
		std::cin >> a[i];
	}
	std::memset(dp , -0x3f , sizeof dp);
	for(int i = 0;i<=n;++i) dp[i][0][0] = dp[i][0][1] = 0;//初始化，选0个就是0
	for(int i = 1;i<=n;++i){
		for(int j = 1;j<=m;++j){
			dp[i][j][1] = max(dp[i-1][j-1][0] , dp[i-1][j-1][1]) + a[i] * j;
			dp[i][j][0] = max(dp[i-1][j][1] , dp[i-1][j][0]);
		}
	}
	std::cout << max(dp[n][m][1] , dp[n][m][0]);
	return 0;
}
```

我们可以运用背包的思想，体积看作是 $1$，价值就是 $a_i \times j$，背包容量就是 $m$，那么实际上我们就可以将它看作是 `01` 背包，我们设 $dp_{i,j}$ 为前 $i$ 个数装了 $j$ 个数到 $b$ 序列里的最大总价值，接下来要考虑两种情况，即选与不选。

选就是到上一个数还没有装上 $a_i$ 时的最优解加上 $a_i \times j$，就是：

$$dp_{i-1,j-1} + a_i \times j $$

不选就是到上一个数的最优解，即：

$$dp_{i-1,j}$$

那么只需要从中选取最优的情况即可：

$$dp_{i,j} = \max (dp_{i-1,j} , dp_{i-1,j-1} + a_i \times j)$$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e3 + 5;

int a[N] , dp[N][N] , m , n;

#define ioO2 std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);

signed main(){
	ioO2
	std::cin >> n >> m;
	for(int i = 1;i<=n;++i){
		std::cin >> a[i];
	}
	std::memset(dp , -0x3f , sizeof dp);
	for(int i = 0;i<=n;++i) dp[i][0] = 0;
	for(int i = 1;i<=n;++i){
		for(int j = 1;j<=m;++j){
			dp[i][j] = max(dp[i-1][j] , dp[i-1][j-1] + a[i] * j);
		}
	}
	std::cout << dp[n][m];
	return 0;
}
```

我们发现，方程的第一维在转移时都是 `i-1`，那么我们可以省略掉第一维，将 dp 数组改为 $dp_j$ 表示装了 $j$ 个数后的最大价值，就可以将上文的方程写为：

$$dp_j = \max(dp_{j} , dp_{j-1} + a_i \times j)$$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e3 + 5;

int a[N] , dp[N] , m , n;

#define ioO2 std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);

signed main(){
	ioO2
	std::cin >> n >> m;
	for(int i = 1;i<=n;++i){
		std::cin >> a[i];
	}
	std::memset(dp , -0x3f , sizeof dp);
	dp[0] = 0;//没有选就为0
	for(int i = 1;i<=n;++i){
		for(int j = m;j;--j){
			dp[j] = max(dp[j] , dp[j-1] + a[i] * j);
		}
	}
	std::cout << dp[m];
	return 0;
}
```

借鉴了 @[zsq20100122](https://www.luogu.com.cn/user/807774) 大佬的思路。

~~zsqtql%%%~~

---

## 作者：SuperCowHorse (赞：2)

考利使用 dp。

$f[i][j]$ 表示 $a$ 数组前 $i$ 个数，$b$ 数组前 $j$ 个数的最大值。

由于找最大值，初始值应赋成 $-\inf$。根据题面，易得：$f[i][0]=0$。

接下来有两种情况：

- 不选 $b[j]$。则 $f[i][j]=f[i-1][j]$。
- 选 $b[j]$。则 $f[i][j]=f[i-1][j-1]+j\times a[i]$。后一项的 $j\times a[i]$ 如题中叙述。

Code:
``` cpp
//chenye3
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define do double
#define re register
#define mk make_pair
#define pb push_back
using namespace std;
const int maxn=2005;
int n,m,a[maxn];
ll f[maxn][maxn];
inline void init(){//初始化
	memset(f,-0x3f,sizeof(f));
	for(int i=0;i<=n;++i)
		f[i][0]=0;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	init();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			f[i][j]=max(f[i-1][j],f[i-1][j-1]+j*a[i]);
	printf("%lld",f[n][m]);
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

[推销蒟蒻博客](https://www.luogu.com.cn/blog/807774/)

感觉现有题解写得都好麻烦啊，这题就是个裸的背包。不会背包的可以写二维 dp 或者自己百度。

每个数视为体积为 $1$，价值为 $j \times a_i$ 的物品。设 $dp_i$ 表示有 $m$ 个数的最大价值，因为体积为 $1$，那么在枚举到第 $i$ 个物品，有 $j$ 个数在子序列中时，**第 $i$ 个物品就是子序列第 $j$ 个数！！！**

贴代码：

```cpp
#include <bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define int long long//要开long long

using namespace std;
const int N=2005,INF=1e17;

int n,m,a[N],dp[N];

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)dp[i]=-INF;//可能有负数，所以初始化负无穷
	dp[0]=0;//什么都不选价值是0
	for(int i=1;i<=n;i++){//枚举每个物品
		for(int j=m;j>=1;j--){//是第几个
			dp[j]=max(dp[j],dp[j-1]+j*a[i]);//转移，体积为1
		}
	}
	cout<<dp[m]; 
	return 0;
} 
```

题外话：这个代码其实可以通过二维转移过来，具体的读者可以配合题解区其他代码自行思考。（设 $dp_{i,j}$ 表示考虑前 $i$ 个选了 $j$ 个会发现 $i$ 维其实没用）。

---

## 作者：Tsawke (赞：1)

#  [[ABC267D] Index × A(Not Continuous ver.)](https://www.luogu.com.cn/problem/AT_abc267_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC267D)

## 题面

求序列 $ A_n $ 的长度为 $ m $ 的最大权值子序列 $ B_m $，定义序列 $ B_m $ 的权值为 $ \sum_{i = 1}^m i \times B_i $。输出最大权值。

## Solution

**提供一种不同的思路**。

一种显而易见的思路就是考虑 $ i $ 是否选，则 DP 是 $ \texttt{2D0D} $ 的，这里提供一种 $ \texttt{2D1D} \rightarrow \texttt{2D0D} $ 的做法。

我们考虑一个类似 LIS 的做法，考虑令 $ dp(i, j) $ 表示长度为 $ i $ 的以 $ j $ 结尾的子序列的最大权值，转移显然为：
$$
dp(i, j) = \max_{k = 1}^{j - 1} dp(i - 1, k) + i \times A_j
$$
即考虑从之前的某一个最优子序列拼过来。

这个东西十分显然可以简单写一个前缀和优化，最终复杂度 $ O(n^2) $。

初始值即为 $ dp(0, i) = 0 $，注意初始时需要将除了 $ 0 $ 之外的所有 $ sum $ 都初始化为 $ -\infty $，否则因为负权值可能存在一些不正确的转移。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, M;
ll A[2100];
ll dp[2100][2100];
ll sum_mx[2100][2100];

int main(){
    memset(sum_mx, 0xc0, sizeof sum_mx);
    N = read(), M = read();
    for(int i = 0; i <= N; ++i)sum_mx[0][i] = 0;
    for(int i = 1; i <= N; ++i)A[i] = read();
    for(int i = 1; i <= M; ++i)
        for(int j = 1; j <= N; ++j)
            dp[i][j] = sum_mx[i - 1][j - 1] + A[j] * i,
            sum_mx[i][j] = max(sum_mx[i][j - 1], dp[i][j]);
    printf("%lld\n", sum_mx[M][N]);
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

update-2023_01_14 初稿

---

## 作者：封禁用户 (赞：1)

记 `dp[i][j]` 表示到 $A_i$ 为止选择 $j$ 个数时     $\sum_{k=1}^{j} k \times B_{k}$ 的**最大值**

转移方程：
$d p[i+1][j]=\max \left(d p[i][j], d p[i][j-1]+A_{i+1} \times j\right)$

#### 代码：
```
#include <bits/extc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
using std::cin;
using std::cout;
using std::vector;
using ll = long long;
inline void chmax(ll& x, ll y) { if (x < y) x = y; }
int main() {
    int n, m;
    cin >> n >> m;

    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    const ll INF = 1e18;
    vector dp(n+1, vector<ll>(m+1, -INF));
    dp[0][0] = 0;
    rep(i, n) {
        rep(j, m+1) {
            chmax(dp[i+1][j], dp[i][j]);
            if (j) chmax(dp[i+1][j], dp[i][j-1]+a[i]*j);
        }
    }
    cout << dp[n][m] << '\n';
    return 0;
}
```

---

## 作者：Crasole (赞：0)

## 题意

给你一个长度为 $n$ 的序列 $A$，$A_1 , A_2 , A_3 , ... ,A_n$，要从中选出一个长度为 $m$ 的子序列 $B$，$B_1 , B_2 , B_3 ,... ,B_m$，使得 $\sum_{i=1} ^ {m} B_i \times i$ 最大。

## 思路

~~刚开始没反应过来，傻傻的写了个二维 dp~~

-----

此题就是一个 01 背包，每个物品的重量是 1，价值为 $d_i \times j$。注意，物品价值并不是 $d_i \times i$。在初始化的时候，$-2 \times 10^5 \le A_i \le 2 \times 10^5$，所以要初始化成负数。

**注意：要开 long long！**

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,w[2010],d[2010],f[2010];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>d[i];
	}
	for(int i=1;i<=n;i++)
		f[i]=-1e18;//初始化成很大的负数
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--)
			f[j]=max(f[j],f[j-1]+d[i]*j);//01背包
	}	
	cout<<f[m];
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：0)

### 题意简述

给定一个长度为 $n$ 的序列 $a$，请从中选出一个长度为 $m$ 的子序列 $b$（可不连续），使得 $\sum_{i=1}^{m}i\times b_i$ 最大。

### 题目分析

很容易发现此题满足无后效性（前面的数字当然不会影响后面答案的计算），所以此题考虑 dp 解决。

我们设 $dp_{i, j}$ 代表考虑了前 $i$ 个数，子序列长度为 $j$ 时的最大答案。显而易见地，对于 $0\le i \le n, dp_{i, 0}=0$。

我们再来思考转移方程。我们求 $dp_{i, j}$ 的值时，我们可以选择不选这个数，也可以选择把这个数放进来。不选这个数时，答案为 $dp_{i-1,j}$，选这个数时，答案为 $dp_{i-1, j-1}+a_i\times j$（不加这个数时序列 $b$ 长度为 $j-1$，加上这个数后为答案作出了 $a_i\times j$ 的贡献）。最终答案即为 $dp_{n, m}$。

注意答案可能会超出 `int` 范围，需要开 `long long`。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e3 + 5;
int n, m, a[MAXN], dp[MAXN][MAXN];
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1;i <= n;i++){
		scanf("%lld", &a[i]);
	}
	memset(dp, 128, sizeof(dp));
	for(int i = 0;i <= n;i++){ // 初始化
		dp[i][0] = 0;
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){ // 注意不能从 0 开始，否则会越界
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[i] * j); // 转移方程，上文有讲述
		}
	}
	printf("%lld", dp[n][m]);
	return 0;
}


```

---

## 作者：DaiRuiChen007 (赞：0)

# ABC267D 题解

## 思路分析

考虑 dp，设 $dp_{i,j}$ 表示前 $i$ 个数里选择 $j$ 个时的最大价值（不一定选 $a_i$），状态转移方程如下：
$$
dp_{i,j}=
\begin{cases}
0&i=0,j=0\\
-\infty&i=0,j\neq0\\
\max(dp_{i-1,j},dp_{i-1,j-1}+a_i\times j)&\text{otherwise}
\end{cases}
$$
时间复杂度 $\Theta(nm)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2001;
int a[MAXN],dp[MAXN][MAXN];
signed main() {
	memset(dp,-0x3f,sizeof(dp));
	int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	dp[0][0]=0;
	for(int i=1;i<=n;++i) {
		dp[i][0]=0;
		for(int j=1;j<=m;++j) {
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+a[i]*j);
		}
	}
	printf("%lld\n",dp[n][m]);
	return 0;
}
```


---

## 作者：Jerrywang09 (赞：0)

[D - Index × A(Not Continuous ver.)](https://atcoder.jp/contests/abc267/tasks/abc267_d)

给你序列 $a$，从中抽出长度为 $m$ 的子序列 $b$，使得 $b$ 的每个元素与下标的乘积之和最大。也就是
$$
\sum^{m}_{i=1} b_i\times i
$$
最大。

考虑 DP。设 $f(i,j)$ 表示前 $i$ 个数中选中 $j$ 个数的最优方案。转移时枚举当前填的是 $b$ 中的第几个数，从 $f(i-1,j)$ （不选 $i$）和 $f(i-1,j-1)$ （选 $i$ 并更新答案）两种情况中转移。初始化全为负无穷，表示不可能。如果 $j$ 为 $0$，则结果为 $0$。

```cpp
// D - Index × A(Not Continuous ver.)
#include <bits/stdc++.h>
#define int long long
#define SIZE 2001
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
using namespace std;

int n, m;
int f[SIZE][SIZE];
int a[SIZE];

signed main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>a[i];
	memset(f, -0x3f, sizeof(f));
	f[1][0]=0;
	f[1][1]=a[1];
	for(int i=2; i<=n; i++)
	{
		f[i][0]=0;
		for(int j=1; j<=m; j++)
		{
			f[i][j]=max(f[i-1][j], f[i-1][j-1]+a[i]*j);
		}
	}
	cout<<f[n][m];

    return 0;
}
```

---

