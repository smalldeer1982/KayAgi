# Maximum Monogonosity

## 题目描述

有两个长度为 $n$ 的序列 $a$，$b$。其中区间 $[l,r]$，$(1 \le l \le r \le n)$ 的价值是 $|b_l-a_r|+|b_r-a_l|$。

区间 $[l_1,r_1]$ $(1 \le l_1 \le r_1 \le n)$ 和区间 $[l_2,r_2]$ $(1 \le l_2 \le r_2 \le n)$ 不相交，是指 $r_1 < l_2$ 满足或 $r_2 < l_1$ 满足。

区间 $[l,r]$ $(1 \le l \le r \le n)$ 的长度被定义为 $r-l+1$。

给定 $a,b$，求若干个**互不相交的，总长度为 $k$ 的** $[l,r]$ 的价值总和的最大值。

## 说明/提示

- $1 \le t \le 1000$。
- $1 \le k \le n \le 3000$。
- $\forall i \in ([1,n] \cap \mathbb N ), -10^9 \le a_i, b_i \le 10^9 $。

## 样例 #1

### 输入

```
5
4 4
1 1 1 1
1 1 1 1
3 2
1 3 2
5 2 3
5 1
1 2 3 4 5
1 2 3 4 5
7 2
1 3 7 6 4 7 2
1 5 3 2 7 4 5
4 2
17 3 5 8
16 2 5 9```

### 输出

```
0
10
0
16
28```

# 题解

## 作者：Register_int (赞：8)

赛时没切，D 没清空 fst。下大分。

首先考虑朴素的 dp。设 $dp_{i,j}$ 表示前 $i$ 个填了 $j$ 个单位长度的最大价值，显然有转移：

$$dp_{i,j}=\max(dp_{i-1,j},\max^j_{k=1}dp_{i-k,j-k}+|a_i-b_{i-k+1}|+|b_i-a_{i-k+1}|)$$

直接转移是 $O(nk^2)$ 的，无法接受。考虑到绝对值有性质 $|x|\ge x$，可以将绝对值拆成四个正负号：

$$
\begin{aligned}
\max^j_{k=1}dp_{i-k,j-k}+a_i-b_{i-k+1}+b_i-a_{i-k+1}\\
\max^j_{k=1}dp_{i-k,j-k}+b_{i-k+1}-a_i+b_i-a_{i-k+1}\\
\max^j_{k=1}dp_{i-k,j-k}+a_i-b_{i-k+1}+a_{i-k+1}-b_i\\
\max^j_{k=1}dp_{i-k,j-k}+b_{i-k+1}-a_i+a_{i-k+1}-b_i\\
\end{aligned}
$$

稍微整理一下：

$$
\begin{aligned}
(\max^j_{k=1}dp_{i-k,j-k}-a_{i-k+1}-b_{i-k+1})+a_i+b_i\\
(\max^j_{k=1}dp_{i-k,j-k}-a_{i-k+1}+b_{i-k+1})-a_i+b_i\\
(\max^j_{k=1}dp_{i-k,j-k}+a_{i-k+1}-b_{i-k+1})+a_i-b_i\\
(\max^j_{k=1}dp_{i-k,j-k}+a_{i-k+1}+b_{i-k+1})-a_i-b_i\\
\end{aligned}
$$

定义 $f_{x,0\sim 3}$ 表示当前转移到的位置满足 $i-j=x$ 时，上面四种情况分别的最大值，直接转移即可。时间复杂度 $O(nk)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e3 + 10;

int t, n, m; ll a[MAXN], b[MAXN];

ll dp[MAXN][MAXN], f[MAXN][4];

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d%d", &n, &m), memset(f, 0x80, sizeof f);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m && j <= i; j++) {
				dp[i][j] = dp[i - 1][j];
				f[i - j][0] = max(f[i - j][0], dp[i - 1][j - 1] - b[i] - a[i]);
				f[i - j][1] = max(f[i - j][1], dp[i - 1][j - 1] + b[i] - a[i]);
				f[i - j][2] = max(f[i - j][2], dp[i - 1][j - 1] - b[i] + a[i]);
				f[i - j][3] = max(f[i - j][3], dp[i - 1][j - 1] + b[i] + a[i]);
				dp[i][j] = max(dp[i][j], f[i - j][0] + a[i] + b[i]);
				dp[i][j] = max(dp[i][j], f[i - j][1] - a[i] + b[i]);
				dp[i][j] = max(dp[i][j], f[i - j][2] + a[i] - b[i]);
				dp[i][j] = max(dp[i][j], f[i - j][3] - a[i] - b[i]);
			}
		}
		printf("%lld\n", dp[n][m]);
	}
}
```

---

## 作者：Hisaishi_Kanade (赞：5)

这种题在场上没做出来我还是挺飞舞的。

设 $\omega(i,j)=|b_i-a_j|+|b_j-a_i|$，首先显然的 dp 是 $f(i,j)$ 表示 前 $i$ 个数，已经有 $j$ 长度的最大价值。

转移则是简单的，$f(i,j)=\max(f(i-1,j),\max\{f(i-x,j-x)+\omega(i-x+1,i)\})$。即将 $[i-x+1,i]$ 这个长为 $x$ 的纳入；或者目前不选 $i$。

这个东西 $i,j,x$ 的枚举时 $n\times k\times k$ 的，没法通过，考虑优化。

我们发现，如果要选 $i$，则转移过来的 $f(i^\prime,j^\prime)$ 其 $i^\prime-j^\prime=i-j$。那么，我们尝试将 $i-j$ 相同的的归为一类。

但是我们发现还有个绝对值不太好搞，我们将 $\omega(i,j)$ 拆开：

$$
f(i,j)=\max\left\{
\begin{aligned}
b_i-a_i+f(i-x,j-x)-a_{i-x+1}+b_{i-x+1}\\
b_i+a_i+f(i-x,j-x)-a_{i-x+1}-b_{i-x+1}\\
-a_i-b_i+f(i-x,j-x)+a_{i-x+1}+b_{i-x+1}\\
-b_i+a_i+f(i-x,j-x)+a_{i-x+1}-b_{i-x+1}\\
\end{aligned}
\right.
$$

我们将只和 $i$ 有关的 $a_i,b_i$ 不看，发现似乎只需要维护对于 $i-j=m$ 的最大 $f(i,j)$ 加上一些玩意。为什么这样就可以得到正确的结果呢？我们只要证明两个点，第一不会枚举到不存在的更优解，第二一定能枚举到合法的最优解。

对于第一条，由于 $|x|\ge x$，绝对值拆开后，必然拆不出比原来更大的结果，所以成立。

对于第二条，绝对值所有取值情况都枚举过了，而且最开始枚举了一个不取的情况，所以是成立的。

那么代码比较显然了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(i=l; i<=r; ++i)
const int N=3005, K=3005;
using ll=long long;
vector<ll> mxa, mxb, mxc, mxd;
/*
- + a - +
+ + b - -
- - c + +
+ - d + -
*/
long long f[N][K], a[N], b[N];
int n, k, i, j, t;
long long ret;
const ll inf=-(1ll<<50);
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ret=0;
		scanf("%d %d", &n, &k);
		rep(i, 1, n) scanf("%lld", a+i); a[n+1]=0;
		rep(i, 1, n) scanf("%lld", b+i); b[n+1]=0;
		vector<ll>(n+5, inf).swap(mxa);	vector<ll>(n+5, inf).swap(mxb);
		vector<ll>(n+5, inf).swap(mxc);	vector<ll>(n+5, inf).swap(mxd);
		rep(i, 0, n) rep(j, 0, n) f[i][j]=inf;
		f[0][0]=0; mxa[0]=-a[1]+b[1]; mxb[0]=a[1]+b[1]; mxc[0]=-a[1]-b[1]; mxd[0]=a[1]-b[1];
		rep(i, 1, n)
		{
			rep(j, 0, k)
			{
				if(j>i) break;
				f[i][j]=max(f[i][j], f[i-1][j]);
				f[i][j]=max(f[i][j], -a[i]+b[i]+mxa[i-j]);// printf("%d %d\n",mxa[i-j],f[i][j]);
				f[i][j]=max(f[i][j], -a[i]-b[i]+mxb[i-j]);// printf("%d\n",f[i][j]);
				f[i][j]=max(f[i][j], +a[i]+b[i]+mxc[i-j]);// printf("%d\n",f[i][j]);
				f[i][j]=max(f[i][j], +a[i]-b[i]+mxd[i-j]);// printf("%d\n",f[i][j]);
				if(i!=n)
				{
					mxa[i-j]=max(mxa[i-j], f[i][j]-a[i+1]+b[i+1]);
					mxb[i-j]=max(mxb[i-j], f[i][j]+a[i+1]+b[i+1]);
					mxc[i-j]=max(mxc[i-j], f[i][j]-a[i+1]-b[i+1]);
					mxd[i-j]=max(mxd[i-j], f[i][j]+a[i+1]-b[i+1]);
				}
				ret=max(ret, f[i][j]);
			}
		}
		printf("%lld\n", ret);
	}
}
```

---

## 作者：SamHJD (赞：4)

## [CF1859E Maximum Monogonosity](https://www.luogu.com.cn/problem/CF1859E)

### Part 1：暴力

设 $dp_{i,j}$ 为考虑 $1\dots i$，选的区间长度和为 $j$ 的价值和最大值，记 $w_{l,r}$ 为 $l\dots r$ 区间的价值。转移很显然：

$$dp_{i,j}=\max(dp_{i-1,j},\max\limits_{k=1}^{j} dp_{i-k,j-k}+w_{i-k,i})$$

需要循环枚举 $i,j,k$，复杂度 $O(nk^2)$，显然不行。

### Part 2：正解

将绝对值进行处理，我们会得到以下四种可能的情况：

$$|b_l-a_r|+|b_r-a_l|=\begin{cases}b_l-a_r+b_r-a_l\\b_l-a_r+a_l-b_r\\a_r-b_l+b_r-a_l\\a_r-b_l+a_l-b_r\end{cases}=\begin{cases}b_l-a_l+b_r-a_r\\b_l+a_l-b_r-a_r\\-b_l-a_l+b_r+a_r\\-b_l+a_l-b_r+a_r\end{cases}$$

我们将 $a_l,b_l$ 的计算与 $a_r,b_r$ 的计算分开，则转移式为：

$$dp_{i,j}=\max(dp_{i-1,j},\left[\max\limits_{k=1}^{j}dp_{i-k,j-k}\pm a_{i-k}\pm b_{i-k}\right]\pm a_i\pm b_i)$$

注意到方括号内的下标均为 $i-k,j-k$，我们不妨用 $f_{d,0/1/2/3}$ 表示当前 $i-j=d$，$a_l,b_l$ 的正负为第 $0/1/2/3$ 种情况，方括号内的表达式的最大值，设 $v1_{0/1/2/3},v2_{0/1/2/3}$ 为 $a_l,b_l$ 在第 $0/1/2/3$ 中情况时的正负。则转移式为：

$$f_{d,l}=\max(dp_{i-1,j-1}+v1_l\times a_i+v2_l\times b_i)$$

那么我们便可以用 $f_{i-j,0/1/2/3}$ 转移 $dp_{i,j}$ 了，转移式为：

$$dp_{i,j}=\max(f_{i-j,l}+v1_l\times a_i+v2_l\times b_i)$$

注意先计算 $f_{i-j,l}$，再计算 $dp_{i,j}$。

### 代码

代码中将 $f,dp$ 的转移压缩了一下，当然如果你看懂了上面的四种情况转移可以尝试用自己的顺序写转移。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+10;
int T,n,k;
int f[N][5],dp[N][N],a[N],b[N];
int v1[]={0,-1,1,-1,1};
int v2[]={0,-1,-1,1,1};
void solve(){
	scanf("%lld%lld",&n,&k);
	memset(f,0x80,sizeof(f));
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=min(k,i);++j){
			dp[i][j]=dp[i-1][j];
			for(int l=1;l<=4;++l) f[i-j][l]=max(f[i-j][l],dp[i-1][j-1]+v1[l]*b[i]+v2[l]*a[i]);
			for(int l=4;l>=1;--l) dp[i][j]=max(dp[i][j],f[i-j][5-l]+v1[l]*a[i]+v2[l]*b[i]);
		}
	}
	printf("%lld\n",dp[n][k]);
}
signed main(){
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```





---

## 作者：Penguin_Master (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1859E)

这种题有 $2500$？感觉很抽象。

## 思路

考虑 $|a-b|=\max(a-b,b-a)$。

那么 $|b_l-a_r|+|b_r-a_l|=\max(b_l-a_r,a_r-b_l)+\max(b_r-a_l,a_l-b_r)$。

然后把 $\max$ 拆开来，变成四种情况。

然后写出 $\rm dp$ 的转移式子，大概是这样：

```cpp
for (int k=1;k<=i;++k)
    for (int j=max(1ll,i-k+1);j<=i;++j)
        dp[i][k]=max(dp[i][k],dp[j-1][k-(i-j+1)]+a[i]+b[i]-a[j]-b[j]),
        dp[i][k]=max(dp[i][k],dp[j-1][k-(i-j+1)]+a[i]-b[i]+a[j]-b[j]),
        dp[i][k]=max(dp[i][k],dp[j-1][k-(i-j+1)]-a[i]+b[i]-a[j]+b[j]),
        dp[i][k]=max(dp[i][k],dp[j-1][k-(i-j+1)]-a[i]-b[i]+a[j]+b[j]);
```

发现 $dp_{i,j}$ 能转移到的点是一条斜线。

对于每条斜线，四种情况分别维护 $\max$ 即可。

时间复杂度 $\mathcal O(nk)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
int const N=3e3+10;
int const M=1e5+10;
int const B=1e4;
int a[N],b[N],dp[N][N],mp1[M],mp2[M],mp3[M],mp4[M];
void solve(){
	int n,k;cin>>n>>k;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=n;++i) cin>>b[i];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j) dp[i][j]=-1e18;
	dp[0][0]=0;
	for (int i=-n;i<=n;++i) mp1[i+B]=mp2[i+B]=mp3[i+B]=mp4[i+B]=-1e18;
	mp1[0+B]=-a[1]-b[1],mp2[0+B]=a[1]-b[1];
	mp3[0+B]=-a[1]+b[1],mp4[0+B]=a[1]+b[1];
	for (int i=1;i<=n;++i){
		for (int j=0;j<=n;++j) dp[i][j]=dp[i-1][j];
		for (int k=0;k<=i;++k)
			dp[i][k]=max(dp[i][k],mp1[k-i+B]+a[i]+b[i]),
			dp[i][k]=max(dp[i][k],mp2[k-i+B]+a[i]-b[i]),
			dp[i][k]=max(dp[i][k],mp3[k-i+B]-a[i]+b[i]),
			dp[i][k]=max(dp[i][k],mp4[k-i+B]-a[i]-b[i]);
		for (int k=0;k<=i;++k)
			mp1[k-i+B]=max(mp1[k-i+B],dp[i][k]-a[i+1]-b[i+1]),
			mp2[k-i+B]=max(mp2[k-i+B],dp[i][k]+a[i+1]-b[i+1]),
			mp3[k-i+B]=max(mp3[k-i+B],dp[i][k]-a[i+1]+b[i+1]),
			mp4[k-i+B]=max(mp4[k-i+B],dp[i][k]+a[i+1]+b[i+1]);
	}
	cout<<dp[n][k]<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	cin>>t;
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

定义 $f(l,r)$ 为 $|a_l-b_r|+|b_l-a_r|$。那么可以写成常规的 DP：

设 $dp_{i,j}$ 为前 $i$ 个数，选了长度和为 $j$ 的若干个不相交的区间，产生的最大值。转移为 $dp_{i,j} = \max \{dp_{i-1,j},\max_{len=1} \{dp_{i-len,j-len}+f(i-len+1,i)\}\}$。

如果 $f(l,r)$ 就是 $a_l-b_r+b_l-a_r$，我们发现转移的第二项都满足第一维减第二维是 $i-j$，因此可以用前缀和优化（记录 $dp_{x,x-t}+a_{x+1}+b_{x+1}$ 的最大值，查询的时候再减去 $a_i+b_i$ 即可）。

不过很遗憾，这个绝对值不能拆开。但是我们求的是**最大值**，而绝对值有一个天然的性质：$|x|=\max \{x,-x\}$！因此我们可以改写 $f(l,r)$：

$$f(l,r)=\max\{(a_l+b_l)-(a_r+b_r),(a_l-b_l)+(a_r-b_r),(b_l-a_l)+(b_r-a_r),(b_r+a_r)-(b_l+a_l)\}$$

于是直接分四类记录并取最大值即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,INF=0x3f3f3f3f3f3f3f3f;
int T,n,k,a[MAXN],b[MAXN],dp[MAXN][MAXN],mx[MAXN][5];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>k;
		ffor(i,1,n) cin>>a[i];
		ffor(i,1,n) cin>>b[i];
		ffor(i,0,n) ffor(j,0,n) dp[i][j]=-INF;
		ffor(i,0,n) mx[i][0]=mx[i][1]=mx[i][2]=mx[i][3]=-INF;
		dp[0][0]=0,mx[0][0]=a[1]+b[1],mx[0][1]=a[1]-b[1],mx[0][2]=b[1]-a[1],mx[0][3]=-b[1]-a[1];
		ffor(i,1,n) {
			dp[i][0]=0;
			mx[i][0]=max(mx[i][0],dp[i][0]+a[i+1]+b[i+1]);
			mx[i][1]=max(mx[i][1],dp[i][0]+a[i+1]-b[i+1]);
			mx[i][2]=max(mx[i][2],dp[i][0]+b[i+1]-a[i+1]);
			mx[i][3]=max(mx[i][3],dp[i][0]-a[i+1]-b[i+1]);
			ffor(j,1,i) {
				dp[i][j]=max(dp[i][j],dp[i-1][j]);
				dp[i][j]=max(dp[i][j],mx[i-j][0]-(a[i]+b[i]));
				dp[i][j]=max(dp[i][j],mx[i-j][1]+(a[i]-b[i]));
				dp[i][j]=max(dp[i][j],mx[i-j][2]+(b[i]-a[i]));
				dp[i][j]=max(dp[i][j],mx[i-j][3]+(b[i]+a[i]));
				mx[i-j][0]=max(mx[i-j][0],dp[i][j]+a[i+1]+b[i+1]);
				mx[i-j][1]=max(mx[i-j][1],dp[i][j]+a[i+1]-b[i+1]);
				mx[i-j][2]=max(mx[i-j][2],dp[i][j]+b[i+1]-a[i+1]);
				mx[i-j][3]=max(mx[i-j][3],dp[i][j]-a[i+1]-b[i+1]);
			}
		}
		cout<<dp[n][k]<<'\n';
	}
	return 0;
}
```

有一道类似的题目：[link](https://ac.nowcoder.com/acm/contest/59717/E) 供练习。

---

## 作者：Diana773 (赞：1)

# 问题描述
给定长度为 $n$（$n\leq 3000$）的两个数字序列 $a,b$；现在要在 $[1,n]$ 这个区间内取一些互不相交的、端点为整数的线段，使这些线段一共恰好包含 $k$（$k\leq n$）个整数点。

每条线段 $[l,r]$（$1\leq l \leq r \leq n$）的权值定义为 $\lvert b_l-a_r \rvert + \lvert b_r-a_l \rvert$；现在需要找出使线段权值和最大的方案，输出权值和最大值。

# 问题分析

- 容易想到 $O(n^3)$ 的 DP；定义 $dp[i][j]$ 为在区间 $[1,i]$ 取了总长度为 $j$ 的线段的最大权值，状态转移方程为：

  $dp[i][j]=\max_{k=1}^j(dp[i-1][j],dp[i-k][j-k]+f[i-k+1][i])$；
  
  其中 $f[x][y]$ 代表线段 $[x,y]$ 的权值。

- 如果想着斜率优化、四边形不等式之类的方法去优化上面的 DP 大概率做不出来。

- 观察到每条线段定义权值的绝对值可以去掉，拆分为四种情况：
  
  $(b_l+a_l)+(-a_r-b_r)$
  
  $(b_l-a_l)+(-a_r+b_r)$
  
  $(-b_l+a_l)+(+a_r-b_r)$
  
  $(-b_l-a_l)+(+a_r+b_r)$

- 错误的去除绝对值方法只会让答案减少，不会影响最终的正确答案。通过这种拆分，**每条线段的左右端点可以单独产生权值**，可以根据左右端点产生权值进行转移。

- 注意到绝对值去除方法只要确定了 $b_l,a_l$ 的正负号，就能确定具体的拆分方法。可以用一对数 $(x,y)$ 表示这种去除方法，$x,y$ 用 $\pm 1$ 表示正负号。

- $dp[i][x][y][j]$ 在前 $[1,i]$ 区间时，选择了若干线段和一条新线段的左端点；**如果**新线段右端点确定为 $i$ 时，所有线段总长度就为 $j$；新线段计算权值绝对值去除方法为 $(x,y)$ 状态时的最大权值。
  
  **注意这个最大权值不包含“如果的”新线段右端点的权值**。


- $ans[i][j]$ 代表在前 $[1,i]$ 区间时，线段长度和为 $j$ 时的最大权值。


- $dp[i][x][y][j]=\max(dp[i-1][x][y][j-1],ans[i-1][j-1]+xb_i+ya_i)$
  
  由之前的结果转移或者将新线段左端点设为 $i$。

- $ans[i][j]=\max_{x,y}(ans[i-1][j],dp[i][x][y][j]-xa_i-yb_i)$

  由之前的结果转移或者将新线段右端点设为 $i$，在新线段的四种绝对值去除方法选一个最大的。

- $ans[0][0]=0$，而 $dp,ans$ 数组其他初始值设为**负无穷大**，否则会使不可能出现的线段取法影响答案。

- 答案是 $ans[n][k]$；时间复杂度 $O(n^2)$。

- $dp,ans$ 数组都可以用滚动数组或改变枚举顺序优化掉第一维，但本题不卡空间，所以可以不优化。

# 参考代码

```
//和题解相比优化了 ans 数组的第一维。

#include<iostream>
#include<cstdio>

using namespace std;
 
int t;
int n,k;
long long a[3010];
long long b[3010];
long long dp[3010][2][2][3010];
long long ans[3010];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	for (int qqw=1; qqw<=t; qqw++)
	{
		cin>>n>>k;
		for (int i=1; i<=n; i++)
		  cin>>a[i];
		for (int i=1; i<=n; i++)
		  cin>>b[i];
		
		for (int i=0; i<=n; i++)
		  ans[i]=-1e18;
		for (int i=0; i<=n; i++)
		  for (int j=0; j<=k; j++)
		    dp[i][0][0][j]=dp[i][0][1][j]=dp[i][1][0][j]=dp[i][1][1][j]=-1e18;
        ans[0]=0;

		for (int i=1; i<=n; i++)
		{
			for (int x=0; x<2; x++)
			  for (int y=0; y<2; y++)
			    for (int l=1; l<=k; l++)
			      dp[i][x][y][l]=max(dp[i-1][x][y][l-1],ans[l-1]+(x?-1:1)*b[i]+(y?1:-1)*a[i]);
            
		    for (int x=0; x<2; x++)
		      for (int y=0; y<2; y++)
		        for (int l=1; l<=k; l++)
		        	ans[l]=max(ans[l],dp[i][x][y][l]+(x?1:-1)*a[i]+(y?-1:1)*b[i]);
		}
		cout<<ans[k]<<'\n';
		
	}
	
	return 0;
}

```

---

## 作者：yukari1735 (赞：0)

容易想到朴素 dp，$f_{n,k}(k\leq n)$ 表示考虑前 $n$ 位区间长度和为 $k$ 时的答案，有转移 $f_{n,k}=\max_{l\leq k}\{f_{n-l,k-l}+|b_n-a_{n-l+1}|+|b_{n-l+1}-a_n|\}$ 可以做到 $O(nk^2)$，过不了。

注意到一个事实：$|x-y|=\max\{x-y,y-x\}$。因此 $|x-y|+|z-w|$ 可以变成四种没有绝对值的式子取 $\max$。我们随便拎出来一种看看，这时转移是 $f_{n,k}=\max_{l\leq k}\{f_{n-l,k-l}-a_{n-l+1}+b_{n-l+1}\}+b_n-a_n$，贡献独立出来了，容易优化到 $O(1)$ 转移。具体地，对每个 $c$ 维护一个 $t_c=\max_{n-k=c}\{f_{n,k}-a_{n+1}+b_{n+1}\}$，实际上就是发现矩阵上能转移到 $(i,j)$ 上的点都在 $y-x=j-i$ 这条斜线上，我们维护的就是每条斜线上的最大值。四个情况下的 $t_c$ 取 $\max$ 就能得到答案了。

时间复杂度 $O(nk)$。

```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 225;
typedef long long ll;
const ll Inf = 1e14 + 225;

int a[ N ] , b[ N ];
ll w[ N ][ 4 ] , f[ N ][ N ];

int n , k;

void Solve(){
	scanf( "%d%d" , & n , & k );
	for( int i = 1 ; i <= n ; i ++ ) scanf( "%d" , & a[ i ] );
	for( int i = 1 ; i <= n ; i ++ ) scanf( "%d" , & b[ i ] );
	ll ans = 0;
	w[ 0 ][ 0 ] = b[ 1 ] - a[ 1 ];
	w[ 0 ][ 1 ] = - b[ 1 ] - a[ 1 ];
	w[ 0 ][ 2 ] = b[ 1 ] + a[ 1 ];
	w[ 0 ][ 3 ] = - b[ 1 ] + a[ 1 ];
	for( int i = 1 ; i <= n ; i ++ ) w[ i ][ 0 ] = w[ i ][ 1 ] = w[ i ][ 2 ] = w[ i ][ 3 ] = -Inf;
	
	for( int i = 1 ; i <= n ; i ++ ){
		for( int j = 0 ; j <= min( k , i ) ; j ++ ){
			ll t0 = w[ i - j ][ 0 ] + b[ i ] - a[ i ];
			ll t1 = w[ i - j ][ 1 ] + b[ i ] + a[ i ];
			ll t2 = w[ i - j ][ 2 ] - b[ i ] - a[ i ];
			ll t3 = w[ i - j ][ 3 ] - b[ i ] + a[ i ];
			f[ i ][ j ] = max( max( t0 , t1 ) , max( t2 , t3 ) );
			f[ i ][ j ] = max( f[ i ][ j ] , f[ i - 1 ][ j ] );
			if( j == k ) ans = max( ans , f[ i ][ j ] );
			w[ i - j ][ 0 ] = max( w[ i - j ][ 0 ] , f[ i ][ j ] + b[ i + 1 ] - a[ i + 1 ] );
			w[ i - j ][ 1 ] = max( w[ i - j ][ 1 ] , f[ i ][ j ] - b[ i + 1 ] - a[ i + 1 ] );
			w[ i - j ][ 2 ] = max( w[ i - j ][ 2 ] , f[ i ][ j ] + b[ i + 1 ] + a[ i + 1 ] );
			w[ i - j ][ 3 ] = max( w[ i - j ][ 3 ] , f[ i ][ j ] - b[ i + 1 ] + a[ i + 1 ] );
		}
	}
	printf( "%lld\n" , ans );
}

int main(){
	int T;
	scanf( "%d" , & T );
	while( T -- ) Solve();
	return 0;
}

```


---

## 作者：WilliamFranklin (赞：0)

### 主要思路

在此，我们设 $g(l, r)$ 等于 $|b_l - a_r| + |b_r - a_l|$。

首先考虑暴力做法：

我们设 $f_{i, j}$ 为前 $i$ 个数中所选总长度为 $j$ 的最大值。

转移方程如下（很简单，不再讲解）：

$$f_{i, j} = \max(f_{i - 1, j}, f_{i - x, j - x} + g(i - x + 1, i))$$

下面我们考虑优化：

我们发现：

$$
g(l,r)=\max\left\{ \begin{aligned} b_l - a_r + b_r - a_l\\ b_l - a_r - b_r + a_l\\ -b_l + a_r + b_r - a_l\\ -b_l + a_r - b_r + a_l\\ \end{aligned} \right.
$$

然后我们可以把 $f$ 看成一张表，注意到我们在对角线上会重新计算(也就是说我们会在所有 $i - j$ 的值相同的状态上重新计算)。

那么转移就很显然了，详看代码。

### AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

const int N = 3005;

long long f[N][N];
long long mn1[N];
long long mx1[N];
long long mn2[N];
long long mx2[N];
int n, k; 
long long a[N], b[N];

int main() {
	int t;
	cin >> t;
	while (t--) {
		scanf("%d%d", &n, &k);
		
		for (int i = 0; i <= n; i++) {
			mn1[i] = mn2[i] = 1e18;
			mx1[i] = mx2[i] = -1e18;
			for (int j = 0; j <= k; j++) {
				f[i][j] = 0;
			}
		}
		
		for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
		for (int i = 0; i < n; i++) scanf("%lld", &b[i]);
		
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= min(i, k); j++) {
				if (i != 0) f[i][j] = f[i - 1][j];
				int l = i - j;
				if (i != 0) {
					f[i][j] = max(f[i][j], b[i - 1] + a[i - 1] - mn1[l]);
					f[i][j] = max(f[i][j], -b[i - 1] - a[i - 1] + mx1[l]);
					f[i][j] = max(f[i][j], a[i - 1] - b[i - 1] - mn2[l]);
					f[i][j] = max(f[i][j], b[i - 1] - a[i - 1] + mx2[l]);
				}
				if (i != n) {
					mn1[l] = min(mn1[l], b[i] + a[i] - f[i][j]);
					mx1[l] = max(mx1[l], b[i] + a[i] + f[i][j]);
					mn2[l] = min(mn2[l], b[i] - a[i] - f[i][j]);
					mx2[l] = max(mx2[l], b[i] - a[i] + f[i][j]);
				}
			}
		}
		
		printf("%lld\n", f[n][k]);
	}
	
	return 0;
} 
```

~~妈的，不这么严谨的初始化就给我 T 是吧~~

### 谢谢观看！

---

## 作者：masonpop (赞：0)

比较巧妙的 dp 优化。

首先 $O(nk^2)$ 的 dp 是显然的：设 $f_{i,j}$ 表示考虑到第 $i$ 项，总长度为 $j$ 的总长度。枚举最后一个数选不选，以及如果选择的话区间的长度，有：

$f_{i,j}=\max\{f_{i-1,j},f_{i-t,j-t}+F(i-t+1,i)\},t\in[1,j]$。

其中 $F(i,j)$ 表示区间 $[i,j]$ 的权值。

考虑优化。注意到这个 dp 的过程已经最简了，要想优化只能从 $F(i,j)$ 的本质入手。

注意到关键性质：**$\text{abs}(x)=\max\{x,-x\}$**。

因此，$F(i,j)=\text{abs}(a_i-b_j)+\text{abs}(a_j-b_i)$ 即为以下四项的最大值：$(b_i+b_j)-(a_i+a_j)$，$(b_i-b_j)+(a_i-a_j)$，$(b_j-b_i)+(a_j-a_i)$，$(a_i+a_j)-(b_i+b_j)$。

又注意到，$f_{i-t,j-t}$ 实际上表示两维的差值为 $i-j$ 的 dp 值集合。因此，可以考虑分别维护 $f_{i,j}+(b_{i+1}-a_{i+1})$，$f_{i,j}+(b_{i+1}+a_{i+1})$，$f_{i,j}-(b_{i+1}+a_{i+1})$，$f_{i,j}+(a_{i+1}-b_{i+1})$ 这四项的最大值。储存在 $g_x,h_x,t_x,r_x$ 中，其中 $x=i-j$。然后每次转移就可以调用这里面的值实现 $O(1)$ 转移了，具体细节见代码。

时间复杂度降为 $O(nk)$。建议写转移式时先在纸上打好草稿再对照着写，不然容易弄混。[代码](https://codeforces.com/contest/1859/submission/218739957)。

---

## 作者：CuCl4Loliko (赞：0)


### Preface

诈骗题。

### Problem

给你两个长度为 $n$ 的数组，定义一个区间的贡献为 $|b_l-a_r|+|b_r-a_l|$，求长度为 $k$ 的不相交区间的最大贡献。

### Solution

首先可以设计一个暴力的 DP。

设 $f_{i,j}$ 表示考虑了前 $i$ 个位置，共选了长度 $j$ 的区间，可以得到一个暴力转移方程：

$$f_{i,j}=max(f_{i-1,j},f_{l-1,j-(i-l+2)}+|b_l-a_i|+|b_i-a_l|)$$

这是一个 2D1D 的动态规划，复杂度为 $O(nk^2)$，复杂度过高，考虑优化。

注意到绝对值的性质，$|a-b|=max(a-b,b-a)$，所以上面的式子可以化为：

$$f_{i,j}=max(f_{i-1,j},f_{l-1,j-(i-l+2)}+max(b_l-a_r+b_r-a_l,-b_l+a_r+b_r-a_l,b_l-a_r-b_r+a_l,-b_l+a_r-b_r+a_l))$$

把内层的 $max$ 提出来式子化为了四种情况，每种情况都是这样子的式子：

$$max(f_{l-1,j-(i-l+2)} \pm b_l \pm a_l \pm a_i \pm b_i)$$

$a_i$ 和 $b_i$ 是固定的，对最大值没有影响，写到外面。

$$max(f_{l-1,j-(i-l+2)} \pm b_l \pm a_l )\pm a_i \pm b_i$$

维护四种情况的 $f_{l-1,j-(i-l+2)} \pm b_l \pm a_l$ 的最大值，转移时 $O(1)$ 转移，注意要对每种 $i-j$ 来分开维护，因为每次转移 $i$ 和 $j$ 的增量是一样的。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e3+5,INF=1e18;
int f[maxn][maxn];
int ma[maxn][5];
int a[maxn],b[maxn];

signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=k;j++)
				f[i][j]=0;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		for(int i=0;i<=n;i++)
			ma[i][1]=ma[i][2]=ma[i][3]=ma[i][4]=-INF;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=min(k,i);j++)
			{
				f[i][j]=f[i-1][j];
				f[i][j]=max(f[i][j],ma[i-j+1][1]-a[i]+b[i]);
				f[i][j]=max(f[i][j],ma[i-j+1][2]+a[i]+b[i]);
				f[i][j]=max(f[i][j],ma[i-j+1][3]-a[i]-b[i]);
				f[i][j]=max(f[i][j],ma[i-j+1][4]+a[i]-b[i]);
				ma[i-j][1]=max(ma[i-j][1],f[i-1][j]+b[i]-a[i]);
				ma[i-j][2]=max(ma[i-j][2],f[i-1][j]-b[i]-a[i]);
				ma[i-j][3]=max(ma[i-j][3],f[i-1][j]+b[i]+a[i]);
				ma[i-j][4]=max(ma[i-j][4],f[i-1][j]-b[i]+a[i]);
			}
		cout<<f[n][k]<<endl;
	}
	return 0;
}

```

---

