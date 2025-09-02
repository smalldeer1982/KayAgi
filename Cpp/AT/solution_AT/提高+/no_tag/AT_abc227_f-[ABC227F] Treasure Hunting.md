# [ABC227F] Treasure Hunting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc227/tasks/abc227_f

縦 $ H $ 行、横 $ W $ 列のマス目があります。上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と書くことにします。$ (i,j) $ には整数 $ A_{i,j} $ が書かれています。

高橋君は $ (1,1) $ を出発し、$ (H,W) $ にたどり着くまで、$ 1 $ つ右あるいは $ 1 $ つ下のマスへ移動することを繰り返します。ただし、マス目の外に出ることはできません。

この時、移動のコストを以下のように定義します。

> 通った $ H+W-1 $ 個のマスに書かれた整数のうち大きい方 $ K $ 個の和

コストとしてありうる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 30 $
- $ 1\ \leq\ K\ <\ H+W $
- $ 1\ \leq\ A_{i,j}\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

移動の方法は一通りのみであり、通ったマスに書かれた整数は大きい方から順に $ 5 $、$ 4 $、$ 3 $ となるので、$ 9(=5+4) $ を出力します。

### Sample Explanation 2

$ (1,1) $、$ (1,2) $、$ (2,2) $ の順に通った時コストが最小となります。

## 样例 #1

### 输入

```
1 3 2
3 4 5```

### 输出

```
9```

## 样例 #2

### 输入

```
2 2 1
3 2
4 3```

### 输出

```
3```

## 样例 #3

### 输入

```
3 5 3
4 7 8 6 4
6 7 3 10 2
3 8 1 10 4```

### 输出

```
21```

# 题解

## 作者：CQ_Bab (赞：3)

# 前言
宝藏 Dp 题，值得一做。
# 思路
我们首先想到的可能就是暴力去 DFS 但是时间复杂度显然过不去，所以我们有能想到从搜索优化到 Dp 但是我们显然不能存下来走的路径。所以我们转变思路，发下 $n\leq 30$ 那么我们是不是就能想到一个 $n^5$ 的 Dp 了。其实我们可以枚举出第 $k$ 大数，这里设定为 $a_{x,y}$ 然后我们可以分类讨论一下，这里我们定义 $dp_{i,j,k}$ 为从 $1,1$ 走到 $i,j$ 经过了 $k$ 个能入选最终最大值的数的最小路径。

- 如果 $a_{i,j}\geq a_{x,y}$ 那么我们由于只能从 $dp_{i-1,j}$ 和 $dp_{i,j-1}$ 转移过来所以我们就让 $dp_{i,j,k}=\min(dp_{i-1,j,k-1}+a_{i,j},dp_{i,j-1,k-1}+a_{i,j},dp_{i,j,k})$，因为这个数能入选。
- 若 $a_{i,j}\leq a_{x,y}$ 那么我们就让 $dp_{i,j,k}=\min(dp_{i-1,j,k},dp_{i,j-1,k},dp_{i,j,k})$，毕竟这个数选不上了。

注意：这里的等于可入选两种因为不会影响答案。

最后，答案就是对于每一个 $a_{x,y}$ 的 $dp_{n,m,k}$ 的最小值了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define il inline
int a[50][50];
int n,m,k,ans=0x3f3f3f3f3f3f3f3fll;
int dp[33][33][63];
signed main() {
	scanf("%lld%lld%lld",&n,&m,&k);
	rep(i,1,n) rep(j,1,m) scanf("%lld",&a[i][j]);
	rep(x,1,n) {
		rep(y,1,m) {
			memset(dp,0x3f,sizeof dp);
			dp[0][0][0]=dp[1][0][0]=dp[0][1][0]=false;
			rep(i,1,n) {
				rep(j,1,m) {
					if(a[i][j]>=a[x][y]) rep(t,1,k) dp[i][j][t]=min({dp[i][j][t],dp[i-1][j][t-1]+a[i][j],dp[i][j-1][t-1]+a[i][j]});
					if(a[i][j]<=a[x][y]) rep(t,0,k) dp[i][j][t]=min({dp[i][j][t],dp[i-1][j][t],dp[i][j-1][t]});
				}
			}
			ans=min(ans,dp[n][m][k]);
		}
	}
	cout<<ans<<endl;
	return false;
}
/*
2 2 1
3 2
4 3
3 5 3
4 7 8 6 4
6 7 3 10 2
3 8 1 10 4
*/
```

---

## 作者：rui_er (赞：2)

简单 DP，当时赛时没做出来，怎么回事呢。

在 DP 过程中并不好维护前 $k$ 大都是什么，没有办法把它放到状态里，因此我们枚举第 $k$ 大数的下标 $a_{x,y}$。

然后就好办了，设 $dp_{i,j,t}$ 表示从 $(1,1)$ 走到 $(i,j)$，且路径上有 $t$ 个数在前 $k$ 大中时的答案。

有两种转移：

- 当 $a_{i,j}\ge a_{x,y}$ 时，$a_{i,j}$ 可以在前 $k$ 大中，转移为 $dp_{i,j,t}=\min\{dp_{i-1,j,t-1},dp_{i,j-1,t-1}\}+a_{i,j}$。
- 当 $a_{i,j}\le a_{x,y}$ 时，$a_{i,j}$ 可以不在前 $k$ 大中，转移为 $dp_{i,j,t}=\min\{dp_{i-1,j,t},dp_{i,j-1,t}\}$。

取每一个 $a_{x,y}$ 时的 $dp_{n,m,k}$ 最小值即可。

```cpp
// Problem: F - Treasure Hunting
// Contest: AtCoder - KEYENCE Programming Contest 2021 (AtCoder Beginner Contest 227)
// URL: https://atcoder.jp/contests/abc227/tasks/abc227_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 35, inf = 0x3f3f3f3f3f3f3f3fll;

ll n, m, k, a[N][N], dp[N][N][2*N], ans = inf;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	rep(i, 1, n) rep(j, 1, m) scanf("%lld", &a[i][j]);
	rep(x, 1, n) {
		rep(y, 1, m) {
			memset(dp, 0x3f, sizeof(dp));
			dp[0][1][0] = 0;
			rep(i, 1, n) {
				rep(j, 1, m) {
					if(a[i][j] >= a[x][y]) {
						rep(t, 1, k) {
							chkmin(dp[i][j][t], dp[i-1][j][t-1] + a[i][j]);
							chkmin(dp[i][j][t], dp[i][j-1][t-1] + a[i][j]);
						}
					}
					if(a[i][j] <= a[x][y]) {
						rep(t, 0, k) {
							chkmin(dp[i][j][t], dp[i-1][j][t]);
							chkmin(dp[i][j][t], dp[i][j-1][t]);
						}
					}
				}
			}
			chkmin(ans, dp[n][m][k]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：_Kenma_ (赞：1)

## 前言

值得一做的 DP 题。

## 思路分析

首先看到题，第一反应是直接 [多人背包](https://www.luogu.com.cn/problem/P1858)。

但是其实假的很彻底。

主要有两个问题：

- 我们只维护了前 $k$ 大权值中，字典序最小的方案，而不是前 $k$ 大方案中，和最小的方案；

- 难以解决算重的问题。

所以这个思路被恋恋不舍地放弃了。

注意到 $n \le 30$，考虑通过在外层枚举确定某些信息。

比如，枚举第 $k$ 大看起来能极大方便我们的决策。

设 $f_{i,j,l}$ 表示从 $(1,1)$ 走到 $(i,j)$，有前 $k$ 大中 $l$ 个数。

设枚举的第 $k$ 大值为 $tar$，转移是自然的：

当 $a_{i,j} \le tar$ 时：

$$f_{i,j,l}=\min(f_{i-1,j,l},f_{i,j-1,l})$$

当 $a_{i,j} \ge tar$ 时：

$$f_{i,j,l}=\min(f_{i-1,j,l-1}+a_{i,j},f_{i,j-1,l-1}+a_{i,j})$$

注意当 $a_{i,j}=tar$ 时，我们可以把它选进前 $k$ 大，也可以不选。

做完了，总体复杂度 $O(n^5)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans,a[35][35],f[35][35][65];
int dp(int tar){
	memset(f,0x3f,sizeof(f));
	f[1][0][0]=f[0][1][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int l=0;l<=k;l++){
				if(a[i][j]<=tar){
					f[i][j][l]=min({f[i][j][l],f[i-1][j][l],f[i][j-1][l]});
				}
				if(a[i][j]>=tar){
					if(l) f[i][j][l]=min({f[i][j][l],f[i-1][j][l-1]+a[i][j],f[i][j-1][l-1]+a[i][j]});
				}
			}
		}
	}
	return f[n][m][k];
}
signed main(){
	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	ans=1e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans=min(ans,dp(a[i][j]));
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：dengchengyu (赞：1)

##  [abc227_f Treasure Hunting](https://www.luogu.com.cn/problem/AT_abc227_f)

首先想到二分第 $K$ 大 $mid$，然后设 $f_{i,j,k}$ 表示走到 $(i,j)$ 选了 $k$ 个大于等于 $mid$ 的数。

然而观察第二个样例发现并没有单调性：

```txt
input:
2 2 1
3 2
4 3
output:
3
```

于是考虑枚举第 $K$ 大 $x$，然后还是一样的状态。

如果 $x$ 是正确路径的第 $K$ 大，但路径上大于等于 $x$ 的数多于 $K$ 个怎么办呢。

发现可以让等于 $x$ 的数选或不选即可，最后只统计 $f_{n,m,K}$。

计算时间复杂度，注意 $f_{i,j,k}$ 中 $k$ 是 $O(n)$ 的，于是做一次 DP 是 $O(n^3)$，枚举第 $K$ 大为 $O(n^2)$，于是总复杂度为 $O(n^5)$，刚好能通过。

AC 代码：

```cpp
const int N=32;
int a[N][N];
int n,m,K;
ll f[N][N][N+N];
ll ans=9e18;
signed main(){
	read(n,m,K);
	fo(i,1,n)fo(j,1,m)read(a[i][j]);
	fo(_,1,n)fo(__,1,m){
		memset(f,0x3f,sizeof f);
		int t=a[_][__];
		if(a[1][1]<t)f[1][1][0]=0;
		else f[1][1][1]=a[1][1];
		fo(i,1,n)fo(j,1,m){
			if(i==1&&j==1)continue;
			if(a[i][j]<=t)f[i][j][0]=min(f[i-1][j][0],f[i][j-1][0]);
			fo(k,1,K){
				if(a[i][j]==t){
					f[i][j][k]=min(min(f[i-1][j][k],f[i][j-1][k]),min(f[i-1][j][k-1],f[i][j-1][k-1])+a[i][j]);
				}
				else if(a[i][j]>t){
					f[i][j][k]=min(f[i-1][j][k-1],f[i][j-1][k-1])+a[i][j];
				}
				else f[i][j][k]=min(f[i-1][j][k],f[i][j-1][k]);
			}
		}
		ans=min(ans,f[n][m][K]);
	}
	write(ans);
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ABC227F] Treasure Hunting](https://www.luogu.com.cn/problem/AT_abc227_f)

有点厉害。

看到 $n,m\le 30$，以为是 Meet in middle，没想到是 $\mathcal O(n^5)$ 的 DP。

考虑枚举路径上第 $k$ 大的数，设这个数为 $a_{x,y}$。

设 $dp_{i,j,k}$ 为从 $(1,1)$ 到 $(i,j)$ 的路径上有 $k$ 个能成为总路径上前 $k$ 大的点的点权之和。

若 $a_{i,j}\ge a_{x,y}$，则 $a_{i,j}$ 一定在答案里，$dp_{i,j,k}=\min(dp_{i-1,j,k-1},dp_{i,j-1,k-1})+a_{i,j}$。

若 $a_{i,j}\le a_{x,y}$，则 $a_{i,j}$ 不会入选最终答案，$dp_{i,j,k}=\min(dp_{i-1,j,k},dp_{i,j-1})+a_{i,j,k}$。

由于 $a_{i,j}=a_{x,y}$ 既有可能入选也有可能不入选，所以都要考虑。

最终答案即为所有情况中的 $dp_{n,m,k}$ 的最小值。

时间复杂度 $\mathcal O(n^5)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 33, M = 63;
int n, m, K;
int a[N][N];
LL dp[N][N][M], ans = 1e18;
inline void chmin (LL &x, LL y) {
    x = x < y ? x : y;
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> m >> K;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    for (int x = 1; x <= n; ++x)
        for (int y = 1; y <= m; ++y) {
            memset (dp, 0x3f, sizeof (dp));
            dp[1][0][0] = dp[0][1][0] = 0;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j)
                    for (int k = 0; k <= K; ++k) {
                        if (a[i][j] >= a[x][y] && k) chmin (dp[i][j][k], min (dp[i - 1][j][k - 1], dp[i][j - 1][k - 1]) + a[i][j]);
                        if (a[i][j] <= a[x][y]) chmin (dp[i][j][k], min (dp[i - 1][j][k], dp[i][j - 1][k]));
                    }
            chmin (ans, dp[n][m][K]);
        }
    cout << ans;
    return 0;
}
```

---

## 作者：LEWISAK (赞：1)

设一条路径上的权值从大到小依次为 $w_1,w_2,\cdots,w_p$，其中 $p=n+m-1$，那么它的答案是

$$
\sum_{i=1}^{k} w_i
$$

若 $w_i = \max(0,w_i-w_k)$，那么答案为 

$$\sum w_i+k\times w_k$$

$\\$

可以考虑暴力枚举权值 $x$ 并令 $w_i = \max(0,w_i-x)$，然后 DP，将其值增加 $k\times x$ 并更新答案，这样一定会考虑到最优答案。如何证明不会枚举到不合法的情况？

若 $x\lt w_k$，那么 
$$\begin{aligned}
  \sum_{i=1}^p\max(0,w_i-x)+kx &= \sum_{i=1}^kw_i+\sum_{i=k+1}^p\max(0,w_i-x) \\
                 &\ge \sum_{i=1}^kw_i
\end{aligned}$$

若 $x\gt w_k$，那么
$$\begin{aligned}
  \sum_{i=1}^p\max(0,w_i-x)+kx &= \sum_{i=1}^k\max(0,w_i-x)+kx \\
                 &\ge \sum_{i=1}^kw_i
\end{aligned}$$


若 $x=w_k$，原式答案就是 $0$。根本不更新路线。

综上所述，这种方法是正确的。

时间复杂度为 $\mathcal O(n^2m^2)$。代码在 gxyzoj 上跑了 138ms，降维打击！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int w[35][35];
long long dp[35][35];
inline int solve(int x){
	memset(dp,0x3f,sizeof(dp));
	dp[1][0]=dp[0][1]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i][j]=min(dp[i-1][j],dp[i][j-1]);
			if(w[i][j]>=x){
				dp[i][j]+=w[i][j]-x;
			}
		}
	}
	return dp[n][m]+k*x;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>w[i][j];
		}
	}
	long long ans=LONG_LONG_MAX;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans=min(ans,solve(w[i][j]));
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

后续：尼古最优解第一！

---

## 作者：AlicX (赞：1)

考场降智题。

## Solution

发现前 $k$ 个元素不好确定，所以考虑找一个标准来维护他们。定义 $a_{x,y}$ 为最终序列中第 $K$ 大的元素，然后定义状态 $f_{i,j,k}$ 表示从 $(1,1)$ 走到 $(i,j)$ 途中选定了 $k$ 个元素。因为我们钦定了 $a_{x,y}$ 为第 $k$ 大的元素，所以对于每一个 $a_{i,j}$，分为两种情况：要么是在序列中的，要么不在。当 $a_{x,y} \leq a_{i,j}$ 时，$f_{i,j,k}=\min(f_{i-1,j,k-1},f_{i,j-1,k-1})+a_{i,j}$，当 $a_{x,y} \geq a_{i,j}$ 时，$f_{i,j,k}=\min(f_{i-1,j,k},f_{i,j-1,k})$。

------------

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=35,INF=1e18+7; 
int n,m,K; 
int a[N][N];
int f[N][N][N<<1];   
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar(); 
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); } 
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); } 
	return x*f;
} 
signed main(){ 
	n=read(),m=read(),K=read(); int ans=INF;  
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=read(); 
	for(int x=1;x<=n;x++){ 
		for(int y=1;y<=m;y++){
			memset(f,0x3f,sizeof f);
			f[0][1][0]=f[1][0][0]=0; 
			for(int i=1;i<=n;i++){ 
				for(int j=1;j<=m;j++){ 
					if(a[i][j]<=a[x][y]) f[i][j][0]=min({f[i][j][0],f[i-1][j][0],f[i][j-1][0]}); 
					for(int k=1;k<=K;k++){ 
						if(a[i][j]>=a[x][y]) f[i][j][k]=min({f[i][j][k],f[i-1][j][k-1]+a[i][j],f[i][j-1][k-1]+a[i][j]}); 
						if(a[i][j]<=a[x][y]) f[i][j][k]=min({f[i][j][k],f[i-1][j][k],f[i][j-1][k]}); 
					} 
				} 
			} ans=min(ans,f[n][m][K]); 
		} 
	} printf("%lld\n",ans); 
	return 0; 
} /*
1 3 2
3 4 5

2 2 1
3 2
4 3

3 5 3 
4 7 8 6 4
6 7 3 10 2
3 8 1 10 4 

*/ 
```

---

## 作者：_ZSR_ (赞：1)

### [[ABC227F] Treasure Hunting](https://www.luogu.com.cn/problem/AT_abc227_f)

我们不太可能去动态维护前 $k$ 大的数分别是什么，因此考虑枚举第 $k$ 大的数 $a_{x,y}$。

令 $dp_{i,j,k}$ 表示当前位于 $(i,j)$，经过的路径中有 $k$ 个点权值大于等于 $a_{x,y}$。当 $a_{i,j} \geq a_{x,y}$ 时，$dp_{i,j,k}= \min (dp_{i-1,j,k-1},dp_{i,j-1,,k-1})+a_{i,j}$。当 $a_{i,j} \leq a_{x,y}$ 时，$dp_{i,j,k}= \min (dp_{i-1,j,k},dp_{i,j-1,k})$。会发现，这里的转移条件都写了等于的情况，是因为等于的时候既可以把 $a_{i,j}$ 看成是排在 $a_{x,y}$ 前面的数，也可以看成是排在 $a_{x,y}$ 后面的数。答案就是对于每个 $a_{x,y}$ 的 $dp_{n,m,k}$ 的最小值。

code 
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=40;
int n,m,k,ans=1e18;
int a[N][N];
int dp[N][N][N<<1];
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for (int i=1;i<=n;++i)
	{
		for (int j=1;j<=m;++j)
		{
			scanf("%lld",&a[i][j]);
		}
	}
	for (int x=1;x<=n;++x)
	{
		for (int y=1;y<=m;++y)
		{
			memset(dp,0x3f,sizeof dp);
			dp[0][0][0]=dp[1][0][0]=dp[0][1][0]=0;
			for (int i=1;i<=n;++i)
			{
				for (int j=1;j<=m;++j)
				{
					if (a[i][j]<=a[x][y]) dp[i][j][0]=min(dp[i-1][j][0],dp[i][j-1][0]);
					for (int p=1;p<=k;++p)
					{
						if (a[i][j]>=a[x][y]) dp[i][j][p]=min({dp[i][j][p],dp[i-1][j][p-1]+a[i][j],dp[i][j-1][p-1]+a[i][j]});
						if (a[i][j]<=a[x][y]) dp[i][j][p]=min({dp[i][j][p],dp[i-1][j][p],dp[i][j-1][p]});
					}
				}
			}
			ans=min(ans,dp[n][m][k]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：registerGen (赞：1)

显然这个题是 dp。

但是我们发现，前 $K$ 大这个玩意是很难用 dp 处理的，于是我们考虑枚举所有 $a_{x,y}$，并令 $a_{x,y}$ 为 第 $K$ 大的数。

那么我们可以设 $f_{i,j,k}$ 为走到 $(i,j)$，且恰有 $k$ 个数大于等于 $a_{x,y}$，那么此时的答案即为 $f_{n,m,K}$。

转移方程：

$$
f_{i,j,k}=
\begin{cases}
\min(f_{i,j-1,k-1}+f_{i-1,j,k-1})+a_{i,j},&a_{i,j}\gt a_{x,y}\\
\min(f_{i,j-1,k},f_{i-1,j,k},f_{i,j-1,k-1}+a_{i,j},f_{i-1,j,k-1}+a_{i,j}),&a_{i,j}=a_{x,y}\\
\min(f_{i,j-1,k},f_{i-1,j,k}),&a_{i,j}\lt a_{x,y}
\end{cases}
$$

（对于第二种情况，$a_{i,j}$ 可以在前 $K$ 大里，也可以不在，两种情况都要考虑）

最终答案即为所有 $x,y$ 对应的 $f_{n,m,K}$ 的最小值。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int N = 30;

int n, m, p, a[N + 10][N + 10];
ll f[N + 10][N + 10][N * 2 + 10];

int main() {
  scanf("%d%d%d", &n, &m, &p);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", a[i] + j);
  ll ans = 0x3f3f3f3f3f3f3f3f;
  for (int x = 1; x <= n; x++)
    for (int y = 1; y <= m; y++) {
      int now = a[x][y];
      memset(f, 0x3f, sizeof(f));
      f[0][0][0] = f[0][1][0] = f[1][0][0] = 0;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
          if (a[i][j] < now) f[i][j][0] = min(f[i][j - 1][0], f[i - 1][j][0]);
          for (int k = 0; k <= p; k++) {
            if (a[i][j] > now) f[i][j][k] = min(f[i][j - 1][k - 1], f[i - 1][j][k - 1]) + a[i][j];
            else if (a[i][j] == now)
              f[i][j][k] = min({f[i][j - 1][k], f[i - 1][j][k], f[i][j - 1][k - 1] + a[i][j], f[i - 1][j][k - 1] + a[i][j]});
            else f[i][j][k] = min(f[i][j - 1][k], f[i - 1][j][k]);
          }
        }
      ans = min(ans, f[n][m][p]);
    }
  printf("%lld\n", ans);
  return 0;
}
```

---

## 作者：AKPC (赞：0)

集训练习题，个人认为难度不高，但是质量较高的 dp 题。

刚看到这题，由题面、数据范围和~~人类智慧~~可以看出这是一道 dp 题。

dp 题的第一步是设状态。想了大概只有五分钟，我的第一个做法是这样的：

- $dp_{i,j,k,mn}$ 表示到达 $(i,j)$ 的前 $k$ 大，第 $k$ 大是 $mn$ 的价值之和最小值。

显而易见地，可以想到转移方程式：

- $a_{i,j}>mn$ 时，$dp_{i,j,k,mn}=\min\{dp_{i-1,j,k-1,mn}+a_{i,j},dp_{i,j-1,k-1,mn}+a_{i,j}\}$。
- $a_{i,j}<mn$ 时，$dp_{i,j,k,mn}=\min\{dp_{i-1,j,k,mn},dp_{i,j-1,k,mn}\}$。
- $a_{i,j}=mn$ 时，因为有的 $mn$ 可能会被算入 $k$ 大总和，多余的可能会排除，因此对上述四种取 $\min$。

我的思考到此为止了（不过四维的数组应该也能过吧）。

后面找了当时已经通过这道题的同学讨论了这个题，他说，这道题可以对状态优化掉一维。因为 $i,j,k$ 在转移过程中都可以被改变，$mn$ 却没有，而 $mn$ 的值最多只有 $H\times W$ 种，故可以预先枚举这个 $mn$。

消去一维之后，状态转移方程除了少了一维几乎无改变。最终答案即为 $dp_{n,m,k}$。对于初始状态，因为要求 $\min$ 值，故全部设为 $\inf$。不过，$dp_{0,1,0},dp_{1,0,0}$ 需要设为 $0$，这是显然的。

[code](/paste/e0huk2hb)。

---

## 作者：WaterSun (赞：0)

# 思路

首先，我们枚举出第 $k$ 大的数 $x$。

那么，我们可以定义 $dp_{i,j,p}$ 表示从 $(1,1)$ 走到 $(n,m)$ 选出 $p$ 的点作为答案的一部分的最优答案。

由此，可得出状态转移方程（注意，$x$ 既可以选，也可以不选）：

$$
dp_{i,j,p} = \left\{\begin{matrix}
\min(dp_{i - 1,j,p},dp_{i,j - 1,p}) & (a_{i,j} \leq x)\\
\min(dp_{i - 1,j,p - 1},dp_{i,j - 1,p - 1}) + a_{i,j} & (a_{i,j} \geq x)
\end{matrix}\right.
$$

最终的答案就是 $\min(dp_{n,m,k})$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 55,M = 110,inf = 0x3f3f3f3f3f3f3f3f;
int n,m,k,ans = inf;
int arr[N][N];
int dp[N][N][M];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	n = read();
	m = read();
	k = read();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= m;j++) arr[i][j] = read();
	}
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= m;j++){
			memset(dp,inf,sizeof(dp));
			dp[0][1][0] = dp[1][0][0] = dp[0][0][0] = 0;
			for (re int x = 1;x <= n;x++){
				for (re int y = 1;y <= m;y++){
					if (arr[x][y] <= arr[i][j]) dp[x][y][0] = min({dp[x][y][0],dp[x - 1][y][0],dp[x][y - 1][0]});
					for (re int p = 1;p <= k;p++){
						if (arr[x][y] <= arr[i][j]) dp[x][y][p] = min({dp[x][y][p],dp[x - 1][y][p],dp[x][y - 1][p]});
						if (arr[x][y] >= arr[i][j]) dp[x][y][p] = min({dp[x][y][p],dp[x - 1][y][p - 1] + arr[x][y],dp[x][y - 1][p - 1] + arr[x][y]});
					}
				}
			}
			ans = min(ans,dp[n][m][k]);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

