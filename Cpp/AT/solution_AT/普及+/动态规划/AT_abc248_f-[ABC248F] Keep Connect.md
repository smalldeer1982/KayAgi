# [ABC248F] Keep Connect

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc248/tasks/abc248_f

$ 2 $ 以上の整数 $ N $ および素数 $ P $ が与えられます。  
 下図のような $ 2N $ 頂点 $ (3N-2) $ 辺のグラフ $ G $ を考えます。

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc248_f/6f63f253a9279fafd6370d1065746906081f4753.png)

より具体的には、頂点を順に頂点 $ 1 $, 頂点 $ 2 $, $ \ldots $, 頂点 $ 2N $、 辺を順に辺 $ 1 $, 辺 $ 2 $, $ \ldots $, 辺 $ (3N-2) $ とすると、各辺は次のように頂点を結んでいます。

- $ 1\leq\ i\leq\ N-1 $ について、辺 $ i $ は頂点 $ i $ と頂点 $ i+1 $ を結んでいる。
- $ 1\leq\ i\leq\ N-1 $ について、辺 $ (N-1+i) $ は頂点 $ N+i $ と頂点 $ N+i+1 $ を結んでいる。
- $ 1\leq\ i\leq\ N $ について、辺 $ (2N-2+i) $ は頂点 $ i $ と頂点 $ N+i $ を結んでいる。

$ i=1,2,\ldots\ ,N-1 $ について、次の問題を解いてください。

> $ G $ の $ 3N-2 $ 本の辺からちょうど $ i $ 本の辺を取り除く方法であって、辺を取り除いた後のグラフも連結であるようなものの個数を $ P $ で割ったあまりを求めよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3000 $
- $ 9\times\ 10^8\ \leq\ P\ \leq\ 10^9 $
- $ N $ は整数である。
- $ P $ は素数である。

### Sample Explanation 1

$ N=3 $ の場合について、取り除いた後のグラフも連結となるように、ちょうど $ 1 $ 本の辺を取り除く方法は次の $ 7 $ 通りです。 !\[\](https://img.atcoder.jp/abc248/57f65600b77ee654900cff4ea6e40872.png) 取り除いた後のグラフも連結となるように、ちょうど $ 2 $ 本の辺を取り除く方法は次の $ 15 $ 通りです。 !\[\](https://img.atcoder.jp/abc248/3a7d6523a1252886e9a33204a32e45f5.png) よって、これらを $ P=998244353 $ で割ったあまりである $ 7 $, $ 15 $ をこの順に出力します。

### Sample Explanation 2

$ P $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
3 998244353```

### 输出

```
7 15```

## 样例 #2

### 输入

```
16 999999937```

### 输出

```
46 1016 14288 143044 1079816 6349672 29622112 110569766 330377828 784245480 453609503 38603306 44981526 314279703 408855776```

# 题解

## 作者：chengning0909 (赞：7)

# abc 248 F

[AT 链接](https://atcoder.jp/contests/abc248/tasks/abc248_f)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc248_f)

## 题意

给定一个大于等于 $2$ 的整数 $N$ 和一个质数 $P$， 现在有一个有 $2N$ 个点，$3N - 2$ 条边的图 $G$。

令点的编号分别为 $1, 2, \dots, 2N$，令边的编号为 $1, 2, \dots, 3N - 2$，则按照以下方式建边得到图 $G$：

- 对于 $1 \le i \le N - 1$，边 $i$ 连接点 $i$ 和 $i + 1$。

- 对于 $1 \le i \le N - 1$，边 $N + i - 1$ 连接点 $N + i$ 和 $N + i + 1$。

- 对于 $1 \le i \le N$，边 $2N + i - 2$ 连接点 $i$ 和 $N + i$。

对于 $i = 1, 2, \dots, N - 1$，请你求出有多少种删 $i$ 条边的方案，使得图 $G$ 仍然是联通的，方案数对 $P$ 取模。

$2 \le N \le 3000$

$9 \times 10 ^ 8 \le P \le 10 ^ 9$

### Sample 1

#### Input

```txt
3 998244353
```

#### Output

```txt
7 15
```

### Sample 2

#### Input

```txt
16 999999937
```

#### Output

```txt
46 1016 14288 143044 1079816 6349672 29622112 110569766 330377828 784245480 453609503 38603306 44981526 314279703 408855776
```

## 思路

首先，我们先将 Sample 1 的图 $G$ 建立出来。

也就是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/1kt7zrnu.png)

我们可以发现，这就是由很多个正方形拼成的图，每一列的两个点就是 $i$ 和 $i + N$。

-------

那么，我们先考虑一个问题，如果我们不要求删去 $i$ 条边，而是只要满足删边使得图连通，应该怎么做呢？

我们将每一列看作成一个整体，所以对于前 $i$ 列来说，没有连通的肯定是它的一段后缀，因为只有一段后缀是有可能通过后来加边而连通的。

所以，$dp_{i, 0 / 1}$ 表示前 $i$ 列是否连通的删边方案数。

那么，我们考虑转移：

如果前 $i$ 列连通，那么：

![](https://cdn.luogu.com.cn/upload/image_hosting/ehkih60y.png)

可以看出，这两种转移会使得第 $i + 1$ 列不连通，也就是从 $dp_{i, 1}$ 转移到 $dp_{i + 1, 0}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/7k3fq2sh.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6mshz5pg.png)

而这四种转移会使得第 $i + 1$ 列连通，也就是从 $dp_{i, 1}$ 转移到 $dp_{i + 1, 1}$。

我们再考虑第 $i$ 列不连通：

![](https://cdn.luogu.com.cn/upload/image_hosting/pcf5i2pq.png)

这两种转移分别会使得第 $i + 1$ 列不连通和联通，也就是从 $dp_{i, 0}$ 分别转移到 $dp_{i + 1, 0}$ 和 $dp_{i + 1, 1}$。

------

那么，要求了删去的边的数量也是一样的。

$dp_{i, j, 0 / 1}$ 表示前 $i$ 列删去 $j$ 条边是否连通的方案数。

那么转移就是：

$$2 \times dp_{i, j, 1} \rightarrow dp_{i + 1, j + 2, 0}$$

$$3 \times dp_{i, j, 1} \rightarrow dp_{i + 1, j + 1, 1}$$

$$dp_{i, j, 1} \rightarrow dp_{i + 1, j, 1}$$

$$dp_{i, j, 0} \rightarrow dp_{i + 1, j + 1, 0}$$

$$dp_{i, j, 0} \rightarrow dp_{i + 1, j, 1}$$

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3010;

int n, p;
long long dp[N][N][2];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> p;
  dp[1][0][1] = dp[1][1][0] = 1;  // 初始状态
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      dp[i + 1][j + 2][0] = (dp[i + 1][j + 2][0] + 2 * dp[i][j][1]) % p;
      dp[i + 1][j + 1][1] = (dp[i + 1][j + 1][1] + 3 * dp[i][j][1]) % p;
      dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][1]) % p;
      dp[i + 1][j + 1][0] = (dp[i + 1][j + 1][0] + dp[i][j][0]) % p;
      dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][0]) % p;
    }
  }
  for (int i = 1; i < n; i++) {
    cout << dp[n][i][1] << ' ';
  }
  return 0;
}
```

---

## 作者：yh888 (赞：2)

# [ABC248F] Keep Connect 题解

[传送门](https://www.luogu.com.cn/problem/AT_abc248_f)

## 题目大意

给定一个节点数为 $2\times n$ 的如图所示（图片来自题目）的图，求分别删掉 $1,2,3,\ldots,n-1$ 条边后该图仍能连通的方案数。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc248_f/6f63f253a9279fafd6370d1065746906081f4753.png)

## 题解

求方案数，考虑用 DP。

### 定义问题状态

$\large f_{i,j,0/1}$ 表示前 $\large i$ 列删除 $\large j$ 条边，上下两行连通或不连通的方案数。

### 状态转移方程

#### 上下两行连通

如图，前 $(i-1)$ 列上下两行连通，删一条边（红虚线），有以下三种删法。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/mifl6csg.png)

如图，前 $(i-1)$ 列上下两行连通，不删边（红边）。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/mmlfju0t.png)

如图，前 $(i-1)$ 列上下两行不连通，要保证上下两行连通，一条边都不能删（红边）。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/40se70sg.png)

即可推出：$\\$ $\Large f_{i,j,1}=f_{i-1,j-1,1}\times 3+f_{i-1,j,1}+f_{i-1,j,0}$

#### 上下两行不连通

如图，前 $(i-1)$ 列上下本身不连通，则需删一条边（红虚线）。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/gpzq0j47.png)

如图，前 $(i-1)$ 列上下两行连通，要使其不连通需删两条边（红虚线），两种删法如下。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/rnhy5qr9.png)

即可推出：$\\$ $\Large f_{i,j,0}=f_{i-1,j-1,0}+f_{i-1,j-2,1}\times 2$

### 初始化与边界状态

初始化：

$\large f_{i,j,k}=0$。

边界状态：

$\large f_{1,1,0}=f_{1,0,1}=1$。

$\large f_{i,0,1}=1$。

### 计算顺序和答案

计算顺序：

$\large i:2\to n$，$\large j:1\to i$。

答案：

$\large f_{n,i,1}(1\le i\le n)$。

### 时间复杂度

$O(n^2)$，轻松 AC。

### Code

```cpp
#include<bits/stdc++.h>
#define N 3005
#define int long long
using namespace std;
int n, mod, f[N][N][2];
signed main() {
	cin >> n >> mod;
	f[1][1][0] = f[1][0][1] = 1;		//初始化
	for (int i = 1; i <= n; i++)
		f[i][0][1] = 1;			//初始化
	for (int i = 2; i <= n; i++)		//递推
		for (int j = 1; j <= i; j++) {
			f[i][j][1] = (f[i - 1][j - 1][1] * 3 + f[i - 1][j][1] + f[i - 1][j][0]) % mod;
			f[i][j][0] = (f[i - 1][j - 1][0] + f[i - 1][j - 2][1] * 2) % mod;
		}
	for (int i = 1; i < n; i++)
		cout << f[n][i][1] << " ";
	return 0;
}
```

---

## 作者：Tsawke (赞：2)

#  [[ABC248F] Keep Connect](https://www.luogu.com.cn/problem/AT_abc248_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC248F)

## 题面

给定 $ n, p $，存在如图的 $ 2 \times n $ 的网格图，显然初始共有 $ 2n $ 个顶点和 $ 3n - 2 $ 条边，分别求删除 $ i \in [1, n - 1] $ 条边后仍使图连通的删边方案数，对 $ p $ 取模。

## Solution

这种题 DP 很显然，考虑设状态 $ dp(i, j, 0/1) $ 表示考虑前 $ i $ 列，删除了 $ j $ 条边，第 $ i $ 列上下两点之间是否连边，然后对不同情况无脑进行分类讨论即可。

具体地，对于 $ dp(i, j, 0) $，如下图，此时 $ i $ 位置两个点竖直方向并未连边，则为了保证连通性，那么 $ i $ 到 $ i + 1 $ 的水平的两个边必须连上，而 $ i + 1 $ 的竖直的边（即虚线边）是否连结均合法，则有如下转移：
$$
\begin{aligned}
	&dp(i, j, 0) \longrightarrow dp(i + 1, j + 1, 0) \\
    &dp(i, j, 0) \longrightarrow dp(i + 1, j, 1)
\end{aligned}
$$


![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://tsawke.com/Images/Blog/2022_11_19_1.png)

对于 $ dp(i, j, 1) $，如下图，三条边都不能直接确定，所以需要继续讨论，具体地，可以讨论 $ i + 1 $ 的竖直边是否连结，简单想一下就有如下 $ 4 $ 个转移，此处不多赘述，直接看方程吧。
$$
\begin{aligned}
	&dp(i, j, 1) \times 2 \longrightarrow dp(i + 1, j + 1, 1) \\
	&dp(i, j, 1) \longrightarrow dp(i + 1, j, 1) \\
    &dp(i, j, 1) \times 2 \longrightarrow dp(i + 1, j + 2, 0) \\
    &dp(i, j, 1) \longrightarrow dp(i + 1, j + 1, 1)
\end{aligned}
$$
同时注意 $ \times 2 $ 是因为要枚举上下的两个水平边删掉其中一个。

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://tsawke.com/Images/Blog/2022_11_19_1.png)

边界可以是 $ dp(1, 0, 1) = dp(1, 1, 0) = 1 $，对应删边数 $ d $ 的答案即为 $ dp(n, d, 1) $。

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

template< typename T = int >
inline T read(void);

int N; int MOD;
int dp[3100][3100][2];

int main(){
    N = read(), MOD = read();
    dp[1][0][1] = dp[1][1][0] = 1;
    for(int i = 1; i <= N - 1; ++i)
        for(int j = 0; j <= N - 1; ++j)
            dp[i + 1][j + 1][0] = ((ll)dp[i + 1][j + 1][0] + dp[i][j][0]) % MOD,
            dp[i + 1][j][1] = ((ll)dp[i + 1][j][1] + dp[i][j][0]) % MOD,
            dp[i + 1][j + 1][1] = ((ll)dp[i + 1][j + 1][1] + dp[i][j][1] * 2ll) % MOD,
            dp[i + 1][j][1] = ((ll)dp[i + 1][j][1] + dp[i][j][1]) % MOD,
            dp[i + 1][j + 2][0] = ((ll)dp[i + 1][j + 2][0] + dp[i][j][1] * 2ll) % MOD,
            dp[i + 1][j + 1][1] = ((ll)dp[i + 1][j + 1][1] + dp[i][j][1]) % MOD;
    for(int i = 1; i <= N - 1; ++i)printf("%d%c", dp[N][i][1], i == N - 1 ? '\n' : ' ');
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

update-2022_11_21 初稿

---

## 作者：Grow2011 (赞：0)

# 题目分析

题意很清楚了吧，这里就不再赘述了。

这题的 DP 很显然，我们设计 DP 状态 $dp_{i,j,0}$，表示考虑前 $i$ 列，删 $j$ 条边后连通的情况数， $dp_{i,j,1}$，表示考虑前 $i$ 列，删 $j$ 条边后不连通的情况数。

那么我们容易得到以下转移方程：

$$dp_{i+1,j,1} = dp_{i+1,j,1}+dp_{i,j,0}+dp_{i,j,1}$$

$$dp_{i+1,j+1,0} = dp_{i+1,j+1,0}+dp_{i,j,0}$$

$$dp_{i+1,j+1,1} = dp_{i+1,j+1,1}+dp_{i,j,1}\times 3$$

$$dp_{i+1,j+2,0} = dp_{i+1,j+2,0}+dp_{i,j,1}\times 2$$

根据转移方程用扩散法转移即可。

初始化应该都会吧……

**注意：要开 long long，记得取模。**

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,dp[3005][9005][2];
signed main(){
	cin >> n >> p;
	dp[1][0][1] = dp[1][1][0] = 1;//初始化 
	for(int i = 1;i<=n;i++){
		for(int j = 0;j<=n-1;j++){
			dp[i+1][j][1] = (dp[i+1][j][1]+dp[i][j][0]+dp[i][j][1])%p;
			dp[i+1][j+1][0] = (dp[i+1][j+1][0]+dp[i][j][0])%p;
			dp[i+1][j+1][1] = (dp[i+1][j+1][1]+dp[i][j][1]*3)%p;
			dp[i+1][j+2][0] = (dp[i+1][j+2][0]+dp[i][j][1]*2)%p;
			//DP转移 
		}
	}
	for(int i = 1;i<n;i++)cout << dp[n][i][1] << " ";//输出答案。 
	return 0;
}
```

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

给定一个 $2\times n$ 的网格图，那么此网格图有 $2\times n$ 个点，以及 $3\times n-2$ 条边（竖着 $n$ 条，横着 $2\times n-2$ 条）

你想在上面删掉一些边，使得余下来的图依然联通。

即，问对于 $i=1,2,\dots,n-1$，删掉 $i$ 条边后依然联通的方案数。

答案对于一个给定的质数 $p$ 取模。

# Sol

考虑 dp。

设 $f_{i,j,0}$ 表示从 $1$ 到 $i$ 列，共删去 $j$ 条边，第 $i$ 列不连通的数量，$f_{i,j,1}$ 表示从 $1$ 到 $i$ 列，共删去 $j$ 条边，第 $i$ 列连通的数量。

那么易得有转移方程：

$f_{i+1,j,1}=f_{i,j,0}\times 1+f_{i,j,1}\times 1$

$f_{i+1,j+1,0}=f_{i,j,0}\times 1$

$f_{i+1,j+1,1}=f_{i,j,1}\times 3$

$f_{i+1,j+2,0}=f_{i,j,1}\times 2$

时间复杂度 $O(n^2)$，可过。

# Code

注意：十年 OI 一场空，不开 long long 见祖宗！

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[3005][9005][2],n,p;
signed main(){
    cin>>n>>p;f[1][0][1]=f[1][1][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=3*i-2;j++){
            f[i+1][j][1]=(f[i+1][j][1]+f[i][j][0]+f[i][j][1])%p;
            f[i+1][j+1][0]=(f[i+1][j+1][0]+f[i][j][0])%p;
            f[i+1][j+1][1]=(f[i+1][j+1][1]+f[i][j][1]*3)%p;
            f[i+1][j+2][0]=(f[i+1][j+2][0]+f[i][j][1]*2)%p;
        }
    }
    for(int i=1;i<n;i++) cout<<f[n][i][1]<<' ';
}
```

---

## 作者：joe_zxq (赞：0)

# Part 0 - 前言闲话

学校训练做到的题，一道不错的计数 dp。

# Part 1 - 算法思路

## 1-1 dp 状态的定义

由数据范围可知，dp 的时间复杂度应为 $O(N^2)$。

于是定义 $dp_{i,j,k}$，其中 $k \in \{0,1\}$，表示到了第 $i$ 列，删了 $j$ 条边，$k$ 是前 $i$ 列是否连通的方案数。

## 1-2 dp 的转移

dp 转移的情况数量较多，注意不要遗漏。

若前 $i$ 列不连通，有以下几种转移:

$$
dp_{i,j,0} \to dp_{i+1,j,1}
\\
dp_{i,j,0} \to dp_{i+1,j+1,0}
$$

若前 $i$ 列连通，有以下几种转移:

$$
dp_{i,j,1} \to dp_{i+1,j,1}
\\
dp_{i,j,1} \times 2 \to dp_{i+1,j+2,0}
\\
dp_{i,j,1} \times 3 \to dp_{i+1,j+1,1}
$$

## 1-3 dp 的边界

dp 的边界显然为 $dp_{1,0,1} = dp_{1,1,0} = 1$。

删去 $i$ 条边的方案数就是 $dp_{n,i,1}$。

# Part 2 - 代码实现

注意取模！

```cpp
// Problem: 
//     [ABC248F] Keep Connect
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc248_f
// Memory Limit: 1 GB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define ll long long

void ts() {
	puts("The code is running!");
}

ll read() {
    char c;
    bool isf = 0;
    while (!isdigit(c = getchar())) isf = (c == '-');
    ll res = (c ^ 48);
    while (isdigit(c = getchar())) res = (res << 3) + (res << 1) + (c ^ 48);
    return isf ? -res : res;
}

void write(ll x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar('0' + x % 10);
}

void openf(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

ll tc = 1, n, p, dp[3005][3005][2];

void add(ll& x, ll y) {
	x += y;
	x %= p;
}

void init() {
	dp[1][0][1] = dp[1][1][0] = 1;
}

void solve() {
	init();
	n = read();
	p = read();
	for (ll i = 1; i <= n; i++) {
		for (ll j = 0; j < n; j++) {
			add(dp[i + 1][j + 2][0], dp[i][j][1] * 2);
			add(dp[i + 1][j + 1][1], dp[i][j][1] * 3);
			add(dp[i + 1][j][1], dp[i][j][1]);
			add(dp[i + 1][j + 1][0], dp[i][j][0]);
			add(dp[i + 1][j][1], dp[i][j][0]);
		}
	}
	for (ll i = 1; i < n; i++) {
		write(dp[n][i][1]);
		putchar(' ');
	}
}

int main() {
	
    // openf("data");

    // tc = read();
    
    while (tc--) {
    	solve();
    }

    return 0;
}

/*
Things to check:

1. When testing multiple sets of data, remember to clear the array.

2. When clearing, pay attention to clearing the area, starting from 0 or 1. If time permits, use memset.

3. Delete the debugged code.

4. Do you need to enable file input/output.

5. Use faster input and output methods.

6. Pay attention to time complexity and space complexity, and control constants.

7. Think twice before acting.

8. Talk is cheap, show me the code.

9. The most important one, zxq's brain.
*/

/*
                                                                                              
_|_|_|_|_|  _|      _|    _|_|          _|      _|        _|_|      _|      _|_|    _|  _|    
      _|      _|  _|    _|    _|          _|  _|        _|    _|  _|  _|  _|    _|  _|  _|    
    _|          _|      _|  _|_|            _|              _|    _|  _|      _|    _|_|_|_|  
  _|          _|  _|    _|    _|          _|  _|          _|      _|  _|    _|          _|    
_|_|_|_|_|  _|      _|    _|_|  _|      _|      _|      _|_|_|_|    _|    _|_|_|_|      _|    
                                                                                              
                                                                 
*/
```

---

