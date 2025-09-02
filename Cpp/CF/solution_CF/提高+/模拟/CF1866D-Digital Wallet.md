# Digital Wallet

## 题目描述

There are $ N $ arrays, each array has $ M $ positive integer elements The $ j $ -th element of the $ i $ -th array is $ A_{i,j} $ .

Initially, Chaneka's digital wallet contains $ 0 $ money. Given an integer $ K $ . Chaneka will do $ M-K+1 $ operations. In the $ p $ -th operation, Chaneka does the following procedure:

1. Choose any array. Let's say Chaneka chooses the $ x $ -th array.
2. Choose an index $ y $ in that array such that $ p \leq y \leq p+K-1 $ .
3. Add the value of $ A_{x, y} $ to the total money in the wallet.
4. Change the value of $ A_{x, y} $ into $ 0 $ .

Determine the maximum total money that can be earned!

## 说明/提示

In the first example, the following is a sequence of operations of one optimal strategy:

1. Choosing element $ A_{1, 1} $ with a value of $ 10 $ .
2. Choosing element $ A_{3, 2} $ with a value of $ 8 $ .
3. Choosing element $ A_{2, 3} $ with a value of $ 9 $ .

So the total money earned is $ 10+8+9=27 $ .

In the second example, the following is a sequence of operations of one optimal strategy:

1. Choosing element $ A_{3, 2} $ with a value of $ 8 $ .
2. Choosing element $ A_{1, 2} $ with a value of $ 9 $ .

So the total money earned is $ 8+9=17 $ .

In the third example, the following is a sequence of operations of one optimal strategy:

1. Choosing element $ A_{1, 3} $ with a value of $ 10 $ .
2. Choosing element $ A_{1, 2} $ with a value of $ 9 $ .

So the total money earned is $ 10+9=19 $ .

## 样例 #1

### 输入

```
3 3 1
10 4 2
8 1 9
4 8 2```

### 输出

```
27```

## 样例 #2

### 输入

```
3 3 2
5 9 4
1 3 1
2 8 7```

### 输出

```
17```

## 样例 #3

### 输入

```
3 4 3
5 9 10 1
1 3 1 5
2 5 7 2```

### 输出

```
19```

# 题解

## 作者：tyr_04 (赞：8)

[传送门](https://www.luogu.com.cn/problem/CF1866D)

## 题目大意

给你一个 $n \times m$ 的矩阵，让你从 $1$ 到 $k$ 列，$2$ 到 $k+1$ 列，$3$ 到 $k+2$ 列…… $m-k+1$ 到 $m$ 列中各选一个数（不可以重复选择），要你求出这些选出来的数的最大值。

## 思路

一眼动态规划，第一维枚举这是第几列，第二维枚举目前这一列中的第几个数，第三维枚举之前已选择的数的个数。

因为每一列最多可以被选择 $k$ 次，为了保证此列在可选择的范围内，每一次选数时的起点必须大于等于 $i-k+1$ 列，所以只需从 $i-k+1$ 找到 $i$ 即可，由于本蒟蒻是枚举的选择这个数前的选择数目，所以是 从 $i-k$ 到 $i-1$。

为了保证每个数只选择一次，要从后往前找，有点类似背包的思想。

状态转移方程：$dp[p+1]=\max(dp[p]+a[j][i],dp[p+1])$。

其中，$p$ 指之前已选择的数的数量，$a[j][i]$ 表示矩阵中第 $j$ 行，第 $i$ 列的数，时间复杂度为 $O(mnk)$。

# AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,dp[100005]={0},a[15][100005],o=0;
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int p=i-1;p>=max(i-k,o);p--)
			{
				dp[p+1]=max(dp[p]+a[j][i],dp[p+1]);
			}
		}
	}
	cout<<dp[m-k+1];
	return 0;
}
```

---

## 作者：CleverPenguin (赞：6)

实际上，你应当知道，CF是能跑 $10^9$ 的。\
直接考虑暴力。枚举这是第几次，这次选的是第几组，选的是第几大的，上次选的是第几组，上次选的是第几大的。\
需要注意，上次选的组一定在这次前面，否则会导致选择的混乱，有多次选择同一个结果的可能。\
时间复杂度 $O(m \times n^2 \times k^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,m,k,a[100005][15],maxx,dp[99991][11][11],ans;
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&a[j][i]);
		}
	}
	for(int i=1;i<=m;i++){
		sort(a[i]+1,a[i]+n+1,greater<int>());
	}
	for(int i=1;i<=m-k+1;i++){
		for(int j=1;j<=k;j++){
			for(int o=1;o<=n;o++){
				for(int j1=1;j1<=j+1;j1++){
					if(j1==j+1){
						dp[i][j][o]=max(dp[i][j][o],dp[i-1][j1][o-1]+a[j+i-1][o]);
					}else{
						for(int o1=1;o1<=n;o1++){
							dp[i][j][o]=max(dp[i][j][o],dp[i-1][j1][o1]+a[j+i-1][o]);
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			ans=max(ans,dp[m-k+1][i][j]);
		}
	}
	printf("%lld",ans); 
	return 0;
}
```

---

## 作者：_Hugoi_ (赞：6)

## 题意

给定一个 $n \times m$ 的矩阵，执行 $m-k+1$ 轮，第 $i$ 轮在 $i$ 至 $i+k-1$ 列中选择一个数，每个数只能被选一次。

问选择的总和最大是多少。

数据范围：$n$，$k \leq 10$，$m \leq 10^5$。

## 思路

最优性问题，考虑用 DP。

我们发现，每次考虑时，只需考虑一个 $n$ 行 $k$ 列的矩阵，在这之间选数，所以维护这样一个矩阵来 DP。

首先转置原矩阵，方便处理。

我写的时候把数组压成一维来写，这样比较容易确定位置。

记录数组 $g[n \times i+j]$：滚动数组中到第 $i$ 行第 $j$ 列为止的选上第 $i$ 行第 $j$ 列的最大答案。

记录数组 $f[n \times i+j]$：滚动数组中到第 $i$ 行第 $j$ 列为止的最大答案。

让我们手玩一组样例。


```cpp
3 4 3

2 5 7 2

1 3 1 5

5 9 10 1
```


矩阵转置后变成：

```cpp
2 1 5

5 3 9

7 1 10

2 5 1
```

先考虑前 $k$ 列(前 $3$ 列)。

```cpp
2 1 5

5 3 9

7 1 10
```

那么数组 $g$ 就是：

```cpp
2 1 5

5 3 9

7 1 10
```

数组 $f$ 就是：

```cpp
2 2 5

5 5 9

9 9 10
```

再考虑接下来的 $3$ 列。

```cpp
5 3 9

7 1 10

2 5 1
```

这时，发现 $g$ 数组可以从 $f$ 数组转移过来。

拿第一行第二列的 $3$ 为例。

发现 $3$ 可以从 $f$ 数组中 $3$ 这一位对应的上一位转移，也就是 $f$ 数组第一列第一行，这样保证不重不漏。

那么 $g$ 数组就是：

```cpp
10 8 14

16 10 19

12 15 11
```

$f$ 数组就是：

```cpp
10 10 14

16 16 19

19 19 19
```

答案就是 $f[n \times k]$ 了。

## code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=20,M=1e5+10;
int a[M*N],f[105],g[105],n,m,k;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[n*j+i];
		}
	}
	for(int i=1;i<=m-k+1;i++){
		for(int j=1;j<=n*k;j++){
			g[j]=f[min(j+n-1,n*k)]+a[j+n*i];
		}
		for(int j=1;j<=n*k;j++){
			f[j]=g[j];
		}
		for(int j=2;j<=n*k;j++){
			f[j]=max(f[j],f[j-1]);
		}
	}
	cout<<f[n*k];
	return 0;
}
```


---

## 作者：wth2026 (赞：3)

# 题目大意
翻译已经说得很清楚了，不再赘述。
# 题目思路
先是一眼贪心，结果把自己调到了脑瘫也没贪出来。

其实正解是动态规划。

先定义数组 $f_{i,j,k}$ 表示当前选到了第 $i$ 次，这是第 $j$ 列，选第 $k$ 大的值。

于是就有动态转移方程：
$$
f_{i,j,0}=\max(f_{i,j,0},f_{i,j-1,0})\\
f_{i,j,1}=f_{i,j,0}+a_{i+j-K,1}\\
f_{i+1,j-1,k+1}=\max(f_{i+1,j-1,k+1},f_{i,j,k}+a_{i +j-K,k+1}\\
f_{i+1,j,0}=\max(f_{i+1,j,0},f_{i,j,k})
$$
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1 ++)
char *p1, *p2, buf[1 << 20 + 5];

inline int read() {
	int x = 0, f = 1;
	char c = gc();
	
	while (!isdigit(c)) {
		if (c == '-') {
			f = -1;
			break;
		}
		
		c = gc();
	}
	
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = gc();
	}
	
	return x * f;
}

inline void print(int k) {
	if (k < 0) {
		putchar('-');
		k = -k;
	}
	
	if (k > 9) {
		print(k / 10);
	}
	
	putchar(48 + k % 10);
}

bool cmp(int a, int b) {
	return a > b;
}

const int N = 10, M = 1e5;
int n, m, k, f[M + 5][N + 5][N + 5], a[M + 5][N + 5], b[N + 5][M + 5];

void init() {
}

signed main() {
	init();
	n = read();
	m = read();
	k = read();

	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			b[i][j] = read();
		}
	}

	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			a[j][i] = b[i][j];
		}
	}

	for (int i = 1; i <= m; ++ i) {
		sort(a[i] + 1, a[i] + n + 1, cmp);
	}

	for (int i = k; i <= m + 1; ++ i) {
		for (int j = 1; j <= k; ++ j) {
			f[i][j][0] = max(f[i][j][0], f[i][j - 1][0]);
			f[i][j][1] = f[i][j][0] + a[i + j - k][1];

			for (int _ = 1; _ <= n; ++ _) {
				if (j > 1 && _ < n) {
					f[i + 1][j - 1][_ + 1] = max(f[i + 1][j - 1][_ + 1], f[i][j][_] + a[i + j - k][_ + 1]);
				}

				f[i + 1][j][0] = max(f[i + 1][j][0], f[i][j][_]);
			}
		}
	}

	print(f[m + 1][k][0]);
	return 0;
}
```

---

## 作者：SamHJD (赞：3)

## [Digitle Wallet](https://www.luogu.com.cn/problem/CF1866D)

### 题意

给定 $n\times m$ 的矩阵，对于每一个 $i\in[1,m-k+1]$，你可以选一个 $a_{x,y}$ 满足 $x\in[1,n],y\in[i,i+k-1]$。

求选择数的和的最大值。

---

### 解法

对矩阵元素编号如下，使其变为一维：

```
1 4 7 ...
2 5 8 ...
3 6 9 ...
```

设 $f_{i,j}$ 为第 $i$ 次选择 $a_{(i-1)*n+j}$ 的最大值，即选择可选区间内的第 $j$ 个数。

枚举第 $i-1$ 次选择的数转移。由于同一列选择的顺序无影响，并且一定可以从左往右选，于是规定第 $i-1$ 次选择的数 $a_x$，第 $i$ 次选择的数 $a_y$ ，需保证 $x<y$。

$f_i$ 只从 $f_{i-1}$ 转移，可以压掉这一维。时间复杂度 $O(nmk)$。

---

### [代码](https://www.luogu.com.cn/paste/pqm6mt6w)



---

## 作者：Linge_Zzzz (赞：1)

# 前言

都是状态数 $O(n^2m)$ 的 DP，我发个 $O(nm)$ 的。

# 题解

首先不难注意到如下事实：

> 我们称“第 $i$ 列的矩形”为，以第 $i$ 列开头的矩形。
> 
> 我们只考虑前 $i$ 列以内的数，假设前 $i$ 列选了 $j$ 个数（$j\leq i$）。
>
> 那么一定有 $j$ 个矩形选了数。
>
> 可以证明，存在一种方式，使得恰好第 $1$ 到 $j$ 列的矩形选了数，第 $j+1$ 到第 $i$ 列的矩形不选数。

考虑数学归纳法，读者自证不难。

我们先对每一列的数降序排序，计算其以列为单位的前缀和，第 $i$ 列前 $j$ 大数的和记为 $a_{i,j}$。

可以设计以下 DP：

设 $f_{i,j}$ 表示在前 $i$ 列中选数，能覆盖到第 $i+1$ 列的空闲矩形一共有 $j$ 个。

转移时枚举第 $i+1$ 列矩形选了 $l$ 个数，则有：

$$ f_{i+1,j+1-l}\leftarrow f_{i,j}+a_{i+1,l} $$

注意上式只对 $i\leq m-k$ 成立，因为从 $i=m-k+1$ 列开始，第 $i+1$ 列没有新的矩形，所以对于 $i>m-k$，有：

$$ f_{i+1,j-l}\leftarrow f_{i,j}+a_{i+1,l} $$

直接 DP，时间复杂度 $O(n^2m)$，空间复杂度如果采用滚动数组可以优化到 $O(n)$，以下代码为了方便阅读没有采用滚动数组。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=20,M=1e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n,m,k;
int a[M][N];
int f[M][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[j][i];
	for(int i=1;i<=m;i++)sort(a[i]+1,a[i]+1+n,greater<int>());
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			a[i][j]+=a[i][j-1];
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<=m-k;i++)
		for(int j=0;j<k;j++)
			for(int l=0;l<=j+1;l++)
				f[i+1][j+1-l]=max(f[i+1][j+1-l],f[i][j]+a[i+1][l]);
	for(int i=m-k+1;i<m;i++)
		for(int j=0;j<=m-i;j++)
			for(int l=0;l<=j;l++)
				f[i+1][j-l]=max(f[i+1][j-l],f[i][j]+a[i+1][l]);
	cout<<f[m][0]<<endl;
	return 0;
}
```

---

## 作者：Chillturtle (赞：1)

# 题意
有一个 $n$ 行 $m$ 列的矩阵，需要你进行 $m-k+1$ 轮循环，在 $i$ 到 $i+k-1$ 列中，选出一个数，使得选出的数和最大。数据范围为 $n,k \le 10$，$m \le 1 \times 10^5$。

# 思路
看一眼数据范围，先猜一猜，应该是一个 $O(nmk)$ 的 DP。然后开始分析。首先我们可以想一想，贪心？不对，如果用贪心去找到每一列的最大值，再来依次相加，显然是不可以的，因为一列可能被选到很多次。那我们不妨换个角度来想，我们不去计算每次应选哪个数，而是去记录这一列的数会被多少次循环框住，以此来计算最优解。

具体转移见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/xqo9hme5.png)

分析:

- 以列为单位，每次都会框到几列，而每次向后转移时，又会有一列退出现有的框框，如图：$\red{\text 红色}$ 变成 $\color{#FFDD00} {黄色}$，那么阴影的那一列就被现有的框框退出来啦，同理 $\color{#FFDD00} {黄色}$ 和 $\blue{\text 蓝色}$ 也是这样。

-  我们用一个 $p$ 记录，当前已选的个数。如果一个数被框到了很多次，那我们就没有必要在框到它的第一次就选它，我们可以把这个机会留到后面，为后面的大数铺路，所以每一次的决策就不是单纯的用类似贪心想法的当前最优决策。

经过以上分析我们就可以得到一个 DP 的转移方程：

$$dp_{p+1} = \max(dp_{p}+a_{j,i},dp_{p+1})$$

其中，$p$ 表示已选数的数量，$i$ 表示第几列，$j$表示第几行，数组 $a$ 即为输入矩阵。

特别注意，因为每个数只能选一次，所以枚举 $p$ 是需要从后往前遍历。

# AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int abab=0;
int n,m,k;
int a[12][N];
int dp[N];
signed main(){
	memset(dp,0,sizeof(dp));
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
//	dp[1]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			for(int p=i-1;p>=max(i-k,abab);p--){
				dp[p+1]=max(dp[p]+a[j][i],dp[p+1]);
			}
		}
	}
	cout<<dp[m-k+1];
return 0;
}
```

---

## 作者：Register_int (赞：1)

不妨为选数的位置钦定一个顺序。可以发现不同行间无影响，不同列间从左往右取肯定不劣，所以可以设计 $dp_{i,j}$ 表示第 $i$ 次选了位置为 $j$ 的数的方案，时间复杂度 $O(m^2n)$。考虑到实际上转移的有效位置只有 $n\times k$ 的部分，转移时滚掉即可，时间复杂度 $O(nmk)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e6 + 10;
const int MAXM = 1e2 + 10;

int n, m, k, a[MAXN]; ll dp[MAXM], x;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) scanf("%d", &a[(j - 1) * n + i]);
	}
	for (int i = 1; i <= m - k + 1; i++) {
		x = 0;
		for (int j = 1; j <= n * k; j++) dp[j] = x = max(x, dp[min(j + n - 1, n * k)] + a[(i - 1) * n + j]);
	}
	printf("%lld", dp[n * k]);
}
```

---

## 作者：lyhqwq (赞：0)

# Solution
因为框是从左向右滑动，所以从左往右取一定不劣。

将二维数组变成一维，令 $f_{i,j}$ 表示第 $i$ 次取数，最后一次取数的位置在 $j$ 之前的最大价值。有 $f_{i,j}=f_{i-1,j-1}+a_j$，答案为 $f_{m-k+1,n\times k}$。

由于框的大小只有 $100$ 所以 $j$ 只需要维护 $100$ 个数即可，再把第一维滚掉，$O(nmk)$，可过。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1000005;
int n,m,k;
int a[N];
LL f[105];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[(j-1)*n+i]);
    for(int i=1;i<=m-k+1;i++){
        LL premax=0;
        for(int j=1;j<=n*k;j++){
            premax=max(premax,f[min(j+n-1,n*k)]+a[(i-1)*n+j]);
            f[j]=premax;
        }
    }
    printf("%lld\n",f[n*k]);
    return 0;
}

```

---

## 作者：huazai676 (赞：0)

[link](https://codeforces.com/problemset/problem/1866/D)

题意：给定一个 $n \times m (n \leq 10,m \leq 10^5)$ 的数表，你有一个 $n \times k(k \leq 10)$ 的框，框从左到右滑动 $m-k$ 次，你需要每次在框中选一个数（不能重复），总共选 $m-k+1$ 个，使总和最大。

这类 dp 题需要为 dp 过程确定一个顺序，发现同一列中选的数越大越好，于是可以钦定从左到右一列一列的选数，同时这样也不会出现覆盖不到最优解的情况。

于是可以设状态 $f_{x,y,z}$ 为框右端滑倒第 $x$ 列，选数选到了第 $y$ 列，且第 $y$ 列选了 $z$ 个的和最大值。枚举下一次选哪列进行转移（详见代码）。

由于最后选的列只可能有 $k$ 列，于是可以修改状态 $f_{x,y,z}$ 为选到第 $x-k+y$ 列的最大值，从 $O(nm^2)$ 优化为 $O(nmk)$。

[code](https://codeforces.com/contest/1866/submission/228359555)

---

