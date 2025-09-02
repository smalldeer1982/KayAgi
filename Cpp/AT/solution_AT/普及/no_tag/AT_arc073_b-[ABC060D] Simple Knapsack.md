# [ABC060D] Simple Knapsack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc060/tasks/arc073_b

あなたは $ N $ 個の物と、強度 $ W $ のバッグを持っています。 $ i $ 個目の物は、重さが $ w_i $ で価値が $ v_i $ です。

あなたは、物のうちいくつかを選び、バッグに入れます。 ただし、選んだ物の重さの和は $ W $ 以下でなくてはいけません。

あなたは、バッグに入れた物の価値の総和を最大化したいです。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 100 $
- $ 1\ ≦\ W\ ≦\ 10^9 $
- $ 1\ ≦\ w_i\ ≦\ 10^9 $
- すべての $ i\ =\ 2,3,...,N $ について、$ w_1\ ≦\ w_i\ ≦\ w_1\ +\ 3 $
- $ 1\ ≦\ v_i\ ≦\ 10^7 $
- $ W,\ w_i,\ v_i $ はすべて整数である

### Sample Explanation 1

$ 1,\ 3 $ 個目の物を選ぶと良いです。

### Sample Explanation 2

$ 2,\ 4 $ 個目の物を選ぶと良いです。

### Sample Explanation 3

すべての物が選べます。

### Sample Explanation 4

$ 1 $ 個も物が選べません。

## 样例 #1

### 输入

```
4 6
2 1
3 4
4 10
3 4```

### 输出

```
11```

## 样例 #2

### 输入

```
4 6
2 1
3 7
4 10
3 6```

### 输出

```
13```

## 样例 #3

### 输入

```
4 10
1 100
1 100
1 100
1 100```

### 输出

```
400```

## 样例 #4

### 输入

```
4 1
10 100
10 100
10 100
10 100```

### 输出

```
0```

# 题解

## 作者：Liynw (赞：5)

### 前言

为什么我现在才发现这道题洛谷里面有……

[题目链接](https://www.luogu.com.cn/problem/AT2556)

**正解：01 背包**

一道比较简单的创新 01 背包。

***

### 正解

如果按照背包的板子做，那么一定会 $\texttt{TLE}$ 和 $\texttt{MLE}$。那如何优化呢？

我们注意到数据范围里有一句十分特殊的话：

> 对于每个 $i=2,3,...,n$，满足 $W_1\le W_i\le W_1+3$

那么我们完全可以把每个物品的重量以 $W_1$ 为基准，转化为一个不超过 $3$ 的数。这么可以极大地优化空间复杂度。

用 $h$ 代表 $W_1$ 的真实数字。

但是这样的话，我们就无法得知我们现在装的东西到底有没有超过背包的容量，因为我们并不知道我们选了多少个东西。所以 $dp$ 数组还需要开一维代表选择物品的个数。

所以 $dp_{i,j,k}$ 代表在前 $i$ 个物品中选择 $k$ 个物品，背包容量为 $j$ 时的最大价值。

还需要注意一下循环的范围：

- $i:1\sim n$

（这个不需要解释了吧……）

- $j:0\sim 3\times i$

（因为物品的重量被处理过，当原来的 $W_i=W_1$ 时这个物品的重量为 $0$。所以最小的背包容量有可能是 $0$。物品最大的重量不超过 $3$，有 $i$ 个物品，所以最大可能容量为 $3\times i$。）

- $k:1\sim i$

（选择的物品数量不能超过总数。因为后面求答案 $ans$ 的初始值就为 $0$ 已经包括了一个都不选的情况，所以不需要考虑不选物品的情况。）

最后求答案的时候需要枚举 $dp_{n,i,j}$，注意只有 $i+j\times h\le m$ 时背包才不超限，可以更新答案。

具体见代码。

### Code

```cpp
#include<cstdio>
#define max(a,b) (a)>(b)?(a):(b) //卡常小技巧：用这个比库函数要快一些
#define ll long long
ll n,m,ans,h,w[105],v[105],dp[105][305][105];
int main(){
	scanf("%lld %lld",&n,&m);
	scanf("%lld %lld",&h,&v[1]); //h 代表 W1 的的重量
	for(int i=2;i<=n;i++){
		scanf("%lld %lld",&w[i],&v[i]);
		w[i]-=h; //以 W1 为基准转化每一件物品的重量
	}
	for(int i=1;i<=n;i++){
		for(int k=1;k<=i;k++){ //选择的物品数量不能大于总数量
			for(int j=0;j<=3*i;j++){ //3*i 为被允许的最大容量
				if(j<w[i])
					dp[i][j][k]=dp[i-1][j][k];
				else
					dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-w[i]][k-1]+v[i]);
			}
		}
	}
    //在合法的范围内寻找最大值
	for(int i=0;i<=3*n;i++){
		for(int j=0;j<=n;j++){
			if(i+j*h<=m)
				ans=max(ans,dp[n][i][j]);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zesqwq (赞：3)

# AT2556 [ARC073B] Simple Knapsac 题解

~~最优解，呵呵~~

[题目传送门](https://www.luogu.com.cn/problem/AT2556)

这道题目乍一看是一个背包 $\text{dp}$，但是数据范围不太对劲。$\text{V,W}$ 都很大，但是 $W_1\leq W_i \leq W_1 + 3$，也就是质量的种类很少。

我们便可以暴力枚举 $W_1, W_1 + 1, W_1 + 2$ 的取得个数，$W_1 + 3$ 就贪心的能取多少就取多少。枚举之后每次取最大的几个。比若说 $W_1 + 1$ 取了 $3$ 个，那么就取最大的质量为 $W_1 + 1$ 的前三个就行了。然后我们发现这一部分其实是可以使用前缀和优化的。时间复杂度 $O(n^3)$，但是跑不满，最多只有 $(\dfrac{n}{4})^3$ 的运算量，因此跑的飞快。

$\text{Code:}$

```cppp
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 110;
int v[4][N], c[4], dw;
inline bool cmp(int a, int b) { return a > b; }
void read() {
    cin >> n >> m;
    int w, x;
    scanf("%d %d", &w, &x), dw = w, v[0][++c[0]] = x;
    for (int i = 2; i <= n; i++) scanf("%d %d", &w, &x), v[w - dw][++c[w - dw]] = x;
    for (int i = 0; i <= 3; i++) {
        sort(v[i] + 1, v[i] + c[i] + 1, cmp);
        for (int j = 1; j <= c[i]; j++) v[i][j] += v[i][j - 1];
    }
}
int main() {
    read();
    int l, ans = 0;
    for (int i = 0; i <= c[0] && i * dw <= m; i++)
        for (int j = 0; j <= c[1] && (j * (dw + 1) + i * dw) <= m; j++)
            for (int k = 0; k <= c[2] && (k * (dw + 2) + j * (dw + 1) + i * dw) <= m; k++) {
                l = min(c[3], (m - (k * (dw + 2) + j * (dw + 1) + i * dw)) / (dw + 3));
                ans = max(ans, v[0][i] + v[1][j] + v[2][k] + v[3][l]);
            }
    cout << ans;
    return 0;
}
```

---

## 作者：__Hacheylight__ (赞：2)

这个题目就是翻版的背包，物品的体积大了不少，但是每个物品体积的浮动不大

如果背包都不会 ，请先AC[此题](https://www.luogu.org/problemnew/show/P1048)

考虑新的DP转移方程

根据 “每个物品体积的浮动不大” 这一条规定，可以想出方程

$dp[i][j][k]$表示前$i$个物品，选了$j$个，与$a[0]*j$共有$k$的差距

$dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k])$
$dp[i+1][j+1][k+a[i]-a[0]]=max(dp[i+1][j+1][h+a[i]-a[0]],dp[i][j][k]+b[i])$($a[i]$表示体积,$b[i]$表示价值）

答案是$\max_{j=1}^n$ $\ _{k=0}^{3*j}$ $dp[n][j][k] $

code:

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <functional>

using namespace std ;

const int eps=1e-6 ;
const int inf=0x3f3f3f3f ;

#define mp make_pair
#define pb push_back
#define first fi
#define second se
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define REP(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)

typedef unsigned long long ull ;
typedef long long ll ;

inline int read(){
	char c ;
	int f=1 ;
	while((c=getchar())<'0' || c>'9') if (c=='-') f=-1 ;
	int res=c-'0' ;
	while((c=getchar())>='0' && c<='9') res=res*10+c-'0' ;
	return res*f ;
}

const int N = 110 ; 

int n,m ;
int a[110],b[110],dp[110][110][330] ;

int main(){
	n=read();m=read();
	for (int i=1;i<=n;i++) a[i]=read(),b[i]=read() ;
	for (int i=1;i<=n;i++)
	for (int j=0;j<=i;j++)
	for (int k=0;k<=3*j;k++){
		dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k]) ;
		dp[i+1][j+1][k+a[i]-a[1]]=max(dp[i+1][j+1][k+a[i]-a[1]],dp[i][j][k]+b[i]) ;
	}
	
	int ans=0 ;
	for (int i=0;i<=n;i++)
	for (int j=0;j<=3*i;j++){
		ll W= (ll) a[1]*i+j;
		if (W<=m) ans=max(ans,dp[n+1][i][j]) ;
	}
	printf("%d",ans) ;
	return 0 ;
}


```


---

## 作者：封禁用户 (赞：2)

这是一道裸的01背包。只是重量和价值有点大。但所有的重量都不会超过a1+3，因此想到了一种新的dp。废话不多说，直接看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=111;
const int M=3*N;
int dp[N][N][M],a[N],b[N];
int main()
{
	int n,W;
	scanf("%d%d",&n,&W);
	for(int i=0;i<n;i++)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			for(int h=0;h<=3*j;h++)
			{
				dp[i+1][j][h]=max(dp[i+1][j][h],dp[i][j][h]);
				dp[i+1][j+1][h+a[i]-a[0]]=max(dp[i+1][j+1][h+a[i]-a[0]],dp[i][j][h]+b[i]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=3*i;j++)
		{
			long long curW=(long long)a[0]*i+j;
			if(curW<=W)
				ans=max(ans,dp[n][i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：shaozhehan (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT_arc073_b)

[AtCoder 链接](https://atcoder.jp/contests/abc060/tasks/arc073_b)

题目大意：

有 $N$ 个物品（$1\leq N\leq 100$），第 $i$ 个物品重 $w_i$ 千克（$1\leq w_i\leq 10^9$、$w_1\leq w_i\leq w_1+3$），有 $v_i$ 元的价值。现有一个最大容量为 $W$ 的背包，即最多装 $W$ 千克的物品。问：这个背包能装的最大价值是多少？

思路：

乍一看，这就是一道简单的 $01$ 背包，但是 $1\leq w_i\leq 10^9$ 导致我们不能用普通的 $01$ 背包解决方法来解决此题。

但是，我们看到题目中有一个特殊的数据范围：$w_1\leq w_i\leq w_1+3$。它有什么用呢？

我们可以发现，对于任意的 $2\leq i\leq N$，$w_i-w_1\leq 3$，我们可以把每一个 $w_i$ 都减掉 $w_1$，这样就不会 MLE 了。

状态表示：

$dp_{i,j,k}$ 表示在前 $i$ 个物品中选取 $k$ 个物品，且背包容量为 $j$（已经进行数值偏移）时背包中装的物品的最大价值和。

这里我们看一下 $i$、$j$、$k$ 的取值范围：

显然，$1\leq i\leq n$，$0\leq k\leq i$。因为 $w$ 数组已经偏移，所以 $w_i\leq 3$。因此，$0\leq j\leq 3i$。

状态转移方程：

考虑 $dp_{i,j,k}$ 的值。

- 如果第 $i$ 个物品不选，那么 $dp_{i,j,k}=dp_{i-1,j,k}$。
- 如果 $j\geq w_i$，那么还有一种情况：第 $i$ 个物品选了，$dp_{i,j,k}=dp_{i-1,j-w_i,k}+v_i$。

综上，我们可以推出状态转移方程：$dp_{i,j,k}=\begin{cases}dp_{i-1,j-1,k-1},&j<w_i\\\min\{dp_{i-1,j,k},dp_{i-1,j-w_i,k}+v_i\},&\text{otherwise}\end{cases}$。

答案就是所有 $i=n$ 且 $j+kw_1\leq W$ 的 $dp_{i,j,k}$ 的最大值。

此算法时间复杂度为 $\operatorname{O}(n^3)$。

坑点：

1. 全程开 ```long long```，否则会炸精度！
1. 最后求答案的时候千万不要忘记 $j+kw_1\leq W$ 的特判！
1. 记得把 $w_1$ 存储起来，以便后面数值偏移和上面提到的特判！

上代码：
```cpp
#include <iostream>
using namespace std;

long long w[101], v[101], dp[101][301][101];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    long long n, W, w_1;// 坑点 3：记得把 w[1] 存储起来
    cin >> n >> W >> w_1 >> v[1];
    for (int i = 2; i <= n; i++){
        cin >> w[i] >> v[i];
        w[i] -= w_1;// 数值偏移
    }
    for (int i = 1; i <= n; i++){
        for (int k = 1; k <= i; k++){
            for (int j = 0; j <= 3 * i; j++){
                // 状态转移方程
                if (j < w[i]){
                    dp[i][j][k] = dp[i - 1][j][k];
                } else {
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - w[i]][k - 1] + v[i]);
                }
            }
        }
    }
    // 求答案
    long long ans = -1;
    for (int j = 0; j <= 3 * n; j++){
        for (int k = 0; k <= n; k++){
            if (j + k * w_1 <= W){// 坑点 2：特判要注意
                ans = max(ans, dp[n][j][k]);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：fjy666 (赞：1)

题解怎么都这么复杂啊……我来提供一种比较无脑的解法   
总共的重量只有 $4$ 种不同的情况，而相同重量下，我们优先取价值最大的物品。  
那么我们直接暴力枚举这 $4$ 种重量的物品各取几个，然后贪心地统计答案就行了。  
实现时可以只枚举前 $3$ 种，第 $4$ 种取的数量可以贪心地设为 $\left\lfloor\dfrac{\text{left}}{w[1]+3}\right\rfloor$。   
时间复杂度：$\mathcal{O}(n^4)$

```cpp
const int kN = 105;
int n = in(), m = in();
struct Item {
	int w, v;
	bool operator < (const Item &rhs) const {
		return w != rhs.w ? w < rhs.w : v > rhs.v;
	}
} a[kN];

int main() { 
	ll res = 0;
	_rep(i,1,n) a[i].w = in(), a[i].v = in();
	sort(a + 1, a + 1 + n);
	int cnt[4] = {0};
	_rep(i,1,n) ++cnt[a[i].w - a[1].w];
	int st[4] = {n + 1, n + 1, n + 1, n + 1};
	for(int i = n; i; --i) st[a[i].w - a[1].w] = i;

	_rep(c0,0,cnt[0]) if((ll) c0 * a[1].w <= m) _rep(c1,0,cnt[1]) if((ll) c0 * a[1].w + (ll) c1 * (a[1].w + 1) <= m) 
	_rep(c2,0,cnt[2]) if((ll) c0 * a[1].w + (ll) c1 * (a[1].w + 1) + (ll) c2 * (a[1].w + 2) <= m) {
		int c3 = min(cnt[3], (m - c0 * a[1].w - c1 * (a[1].w + 1) - c2 * (a[1].w + 2)) / (a[1].w + 3));
		ll total = 0;
		_for(i,st[0],st[0] + c0) total += a[i].v;
		_for(i,st[1],st[1] + c1) total += a[i].v;
		_for(i,st[2],st[2] + c2) total += a[i].v;
		_for(i,st[3],st[3] + c3) total += a[i].v;
		chkmax(res, total);
	}
	printf("%lld\n", res);
	return 0;
}
```

---

## 作者：StarPatrick (赞：1)

这道题的描述是一道经典背包DP，但 $W$ 较大，$N$ 较小，但是如果你仔细观察会发现物品的重量都不超过 $w_1+3$，所以我们可以将重量那一维定义成 $ax+b$的形式，其中 $x$ 就是 $w_1$，$a$ 和 $b$ 是两个未知数。

再来确定 $a$ 和 $b$ 的范围， $a$ 不超过 $N$，$b$ 不超过 $N * 3$，所以我们就将 $10^9$ 的一维，转化为二维 $100 * 300$，大大节省了时间和空间。

我打的是记忆化，本质上和DP没区别，献上我丑陋的代码:
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int m, n, w[105], c[105], dp[105][105][305];
int dfs(int i, int value1, int value2)
{
	if (dp[i][value1][value2]!=-1)
	{
		return dp[i][value1][value2];
	}
	int ans1 = 0, ans2 = 0;
	if (i==n+1)
	{
		return dp[i][value1][value2]=0;
	}
	if (value1*w[1]+value2+w[i]<=m)
	{
		ans1 = dfs(i+1, value1+1, value2+(w[i]-w[1]))+c[i];
	}
	ans2 = dfs(i+1, value1, value2);
	return dp[i][value1][value2]=max(ans1, ans2);
}
int main()
{
	memset(dp, -1, sizeof(dp));
	cin>>n>>m;
	for (int p=1;p<=n;p++)
	{
		cin>>w[p]>>c[p];
	}
	cout<<dfs(1, 0, 0);
	return 0;
}
```


---

## 作者：wzt2012 (赞：1)

### 题目意思

给你 $n$ 个物品，一个容量为 $w$ 的背包，每一个物品都有它的重量和价值，让你从 $n$ 个物品中选取若干个，使得总重量不超过背包的上限，而且使得价值最大。

### 解题方法

我们发现这和 $\texttt{01}$背包 是一样的。而背包的复杂度是 $\text{O(nw)}$，这道题的数据范围不允许。

我们仔细观察后发现，物品只有 $4$ 种重量，物品的总数最多只有 $100$，所以我们可以把物品分成 $4$ 类，然后从大到小排序，枚举每一种的数量，这样就可以求出最大的价值。


---

