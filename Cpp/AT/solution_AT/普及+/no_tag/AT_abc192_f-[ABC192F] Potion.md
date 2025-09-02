# [ABC192F] Potion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc192/tasks/abc192_f

$ N $ 種類の素材があり、素材 $ i $ には $ A_i $ の魔力があります。

魔法使いの高橋君は、この中から $ 1 $ 種類以上を選んで合成し、ポーションを作ろうとしています。

$ k $ 種類の素材を合成して出来たポーションの魔力は、合成した直後には素材の魔力の合計であり、時間が $ 1 $ 経過するごとに $ k $ 増加します。 魔力の増加は連続的ではなく離散的であることに注意してください。

高橋君が時刻 $ 0 $ に $ 1 $ 度だけ素材の合成を行うとき、魔力がちょうど $ X $ のポーションは、最速でいつ手に入りますか？

なお、制約下で魔力がちょうど $ X $ のポーションを作れることが証明されます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ A_i\ \leq\ 10^7 $
- $ 10^9\ \leq\ X\ \leq\ 10^{18} $
- 入力は全て整数

### Sample Explanation 1

素材 $ 1 $ と素材 $ 3 $ を合成して出来たポーションの魔力は、時刻 $ 0 $ で $ 3+8=11 $ であり、時間が $ 1 $ 経過するごとに $ 2 $ 増加するので、時刻 $ 4999999994 $ に $ 9999999999 $ になります。これが最速です。 素材 $ 1,2,3 $ 全てを合成して出来たポーションの魔力は、時刻 $ 3333333327 $ に $ 9999999998 $、時刻 $ 3333333328 $ に $ 10000000001 $ となり、ちょうど $ 9999999999 $ にはなりません。

## 样例 #1

### 输入

```
3 9999999999
3 6 8```

### 输出

```
4999999994```

## 样例 #2

### 输入

```
1 1000000000000000000
1```

### 输出

```
999999999999999999```

# 题解

## 作者：Light_Star_RPmax_AFO (赞：7)

思路——dp

### 前言

为了纪念长沙市一中第二次思维训练。

## 分析

选取 $s$ 个数，不难想到如果想有解，我们就需要选取的 $s$ 个数的和 $sum$，需要满足以下条件    
$$x-sum\bmod s=0$$

那么我们可以使用一个三维数组 $f_{i,j,k}$ 来进行 **dp**。

注：$i$ 枚举现在选取第几个，$j$ 枚举已经选了几个了，$k$ 枚举 **余数**。

因为我们想要开始就最大，所以我们需要找到 **每个余数** 的 $\operatorname{max}$。

状态转移方程如下

$$\left\{\begin{matrix}
f_{i,j,k} = f_{{i-1},j,k}
 \\f_{i,j,k} = f_{{i-1},{j-1},{k+s-(a_{i-1}\bmod s)\bmod s}}+a_i & f_{{i-1},{j-1},{k+s-(a_{i-1}\bmod s)\bmod s}}\neq -1
\end{matrix}\right.
$$

最后答案统计就是

$$ans=\min(ans,x-f_{n,s,{x\bmod s}}{\div} s)$$

## AC Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll f[101][101][100], a[101];

int main()
{
	int n;
	ll x, ans;
	cin>>n>>x;
	for(int i = 0;i < n;i++)
		cin>>a[i];
	ans = x;
	for(int s = 1;s <= n;s++){//枚举选几个 。 
		memset(f,-1,sizeof(f));
		f[0][0][0] = 0;
		for(int i = 1;i <= n;i++){//枚举现在考虑的。 
			f[i][0][0] = 0;
			for(int j = 1;j <= s;j++)//枚举已经选了几个 
				for(int k = 0; k < s;k++){//枚举余数。 
					f[i][j][k] = f[i - 1][j][k];
					if(f[i - 1][j - 1][(k + s - (a[i - 1] % s)) % s] != -1)
						f[i][j][k] = max(f[i][j][k],f[i - 1][j - 1][(k + s - (a[i - 1] % s)) % s] + a[i - 1]);
				}
		}
		if(f[n][s][x%s] != -1)
			ans = min(ans,(x - f[n][s][x%s]) / s);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Louis_lxy (赞：6)

一种与众不同的 dp。

考虑暴力 dp，令 $f(i,j,k,l)$ 表示前 $l$ 个数中取 $i$ 个数的和在模 $j$ 下余 $k$ 的最大的和，然后暴力转移，此时空间 $O(n^4)$，时间 $O(n^5)$，然后发现空间可以滚掉，然后空间变成了 $O(n^3)$，然后发现时间好像不好优化。但是只要加上剪枝就可以通过这题。

剪枝一：显然只有存在 $f(i-1,j,(k-a_l)\bmod j,l-1)$ 才有可能转移。

剪枝二：容易发现 $f$ 数组在前三维相同的情况下，数据单调不减，因此只需要在更新 $f$ 的时候判断是否能更新，如果不能更新，后面的也一定不能更新。

接着证明一下 $f$ 数组在前三维相同的情况下，数据单调不减。容易发现，$f(i,j,k,l)$ 要么是 $f(i,j,k,l-1)$，要么包含 $a_l$，因此一定不小于 $f(i,j,k,l-1)$。

也可以用线段树优化，但是这样是稳定 $O(n^4\log n)$，无法通过此题。

AC 记录：https://www.luogu.com.cn/record/176263173

注：希望有神犇能证明其复杂度正确，或者给出 hack，如果有神犇会，可以发在评论区。

---

## 作者：lfxxx (赞：4)

首先考虑枚举 $k$。

然后我们发现假如最开始选出的数和为 $sum$，答案为 $ans$ 有：

$sum + ans \times k = X$。

所以 

$sum \bmod k = X \bmod k$。

又因为 $ans = \frac{X - sum}{k}$。

所以我们要尽可能最大化 $sum$。

那么问题变成从序列中选出一些数使得它们的和对某个数取模的值等于某个数的前提下最大化它们的和，那么设计状态 $dp_{i,j}$ 表示前 $i$ 个数且它们的和模 $k$ 为 $j$ 的前提下最大的和。

然后去暴力转移即可，总复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 114;
int a[maxn],n,anser=1000000000000000007; 
int X;
int dp[maxn][maxn][maxn];
void sol(int k){
	for(int i=0;i<maxn;i++){
		for(int p=0;p<maxn;p++){
			for(int j=0;j<maxn;j++) dp[i][p][j]=0;
		}
	}
	for(int i=1;i<=n;i++){
		dp[i][1][a[i]%k]=a[i];
		for(int p=1;p<=n;p++){
			for(int j=0;j<k;j++){
				if(dp[i-1][p-1][(j-(a[i]%k)+k)%k]!=0)
					dp[i][p][j]=max(dp[i-1][p][j],max(dp[i-1][p-1][(j-(a[i]%k)+k)%k]+a[i],dp[i][p][j]));
				else
					dp[i][p][j]=max(dp[i-1][p][j],dp[i][p][j]);
			}	
		}
	}
	if(dp[n][k][X%k]==0) return ;
	anser=min(anser,(X-dp[n][k][X%k])/k);
}
signed main(){
	cin>>n>>X;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++) sol(i);
	cout<<anser;
}
```


---

## 作者：tabelog_AFO (赞：1)

[ABC192F] Potion / [洛谷](https://www.luogu.com.cn/problem/AT_abc192_f) / [AtCoder](https://atcoder.jp/contests/abc192/tasks/abc192_f)

[更好的阅读体验](https://www.luogu.com.cn/blog/tabelog/solution-at-abc192-f)

#### 题目大意
$N$ 个数 $A_i$ ，要求选出若干个数（假设 $x$ 个，分别为 $A_{a1}, A_{a2}, \dots, A_{ax}$ ），使 $\sum A_{ai} \equiv X \pmod X$ 且 $\dfrac{X - \sum A_{ai}}{x}$ 最小，求出最小值。

#### 思路
枚举所有可能的 $x$ ，分别进行 DP。

设 $f_{i,j,k}$ 为前 $i$ 个数选了 $j$ 个，$\operatorname{mod} x$ 的余数为 $k$ 的 $\sum A_{ai}$ 最大值，则：
$$f_{i,j,k} = \max \{ f_{i-1,j,k}, f_{i-1,j-1,(k-a_i) \pmod x} + a_i\}$$

#### 复杂度
- 时间复杂度 $\Theta(N^4)$
- 空间复杂度 $\Theta(N^3)$

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100;
ll dp[MAXN+1][MAXN+1][MAXN]={},a[MAXN];
inline ll llmax(ll a,ll b) {return (a>b)?a:b;}
inline ll llmin(ll a,ll b) {return (a<b)?a:b;}
int main() {
    int n;ll x,ans;
    scanf("%d%lld",&n,&x);
    for (int i=0;i<n;i++) cin>>a[i];
    ans=x;
    for (int p=1;p<=n;p++) {
        // 初始化
        memset(dp,0xcf,sizeof(dp));
        dp[0][0][0]=0; // 边界条件
        for (int i=1;i<=n;i++) {
            dp[i][0][0]=0; // 边界条件
            for (int j=1;j<=p;j++)
                for (int k=0;k<p;k++)
                    dp[i][j][k]=llmax(dp[i-1][j][k],dp[i-1][j-1][(k+p-(a[i-1]%p))%p]+a[i-1]); // 状态转移
        }
        if (dp[n][p][x%p]>=0)
            ans=llmin(ans,(x-dp[n][p][x%p])/p);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Kevin_Mamba (赞：1)

### 题意

给定 $n$ 个数 $a_1,a_2,...,a_n$ 和参数 $X$。

自选一个数 $k(1\le k\le n)$，并且从这 $n$ 个数中任选 $k$ 个数 $b_1,b_2,...,b_k$。

要求 $k\mid X-\sum\limits_{i=1}^kb_i$，并且使得 $\frac{X-\sum\limits_{i=1}^kb_i}{k}$ 最小。

输出这个最小值。

### 解题思路
枚举 $k$。

对于每一个 $k$，设 $b_i=a_i \bmod k$（注意区分与题意中的 $b_i$），$c_1,c_2,...,c_k$ 为所选数的下标。

为了使 $k\mid \sum\limits_{j=1}^na_{c_j}$，条件是 $\sum\limits_{i=1}^n b_{c_i}\equiv X(\bmod\ k)$。

在满足条件的前提下，要使 $\sum\limits_{j=1}^na_{c_j}$ **最大。**

即：

$$ans=\min\limits_{k=1}^n\frac{X-\max\limits_{\sum\limits_{i=1}^n b_{c_i}\equiv X(\bmod k)}\sum\limits_{j=1}^na_{c_j}}{k}$$

其实枚举 $k$ 时只需要求**分数部分**。这时就想到了用**动态规划。**

设 $dp_{i,j}$ 表示选了 $j$ 个数，$i=\sum\limits_{u=1}^jb_{c_u} \bmod k$ 前提下的 $\sum\limits_{u=1}^j a_{c_u}$ 的最大值。其中 $c$ 为下标数组，同上。 

状态转移方程：

$$dp_{i,j}=\max \limits_{u=1}^{n}dp_{(i-b_u)\bmod k,j-1}+a_u$$

最后分数部分就为 $\dfrac{X-dp_{X\bmod k,k}}{k}$。

### 代码实现

复杂度：时间 $O(n^4)$，空间 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
#define int long long
using namespace std;

const int N=110;

int n,X,a[N],b[N],dp[N<<1][N],ans=1e18;

signed main() {
	scanf("%lld%lld",&n,&X);
	for(re int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
	}
	for(re int k=1;k<=n;k++) {
		for(re int i=1;i<=n;i++) {
			b[i]=a[i]%k;
		}
		memset(dp,0,sizeof dp);
		for(re int i=1;i<=n;i++) {
			for(re int j=(k<<1)-1;j>=b[i];j--) {
				for(re int u=k-1;~u;u--) {
					if(j-b[i]==0&&u==0||dp[j-b[i]][u]) dp[j][u+1]=max(dp[j][u+1],dp[j-b[i]][u]+a[i]);
				}
			}
			for(re int j=0;j<k;j++) {
				for(re int u=0;u<=k;u++) {
					dp[j][u]=max(dp[j][u],dp[j+k][u]);
					dp[j+k][u]=0;
				}
			}
		}
		if(dp[X%k][k]) ans=min(ans,(X-dp[X%k][k])/k);
	}
	printf("%lld\n",ans);
	return 0;
}
```







---

## 作者：ForgetOIDuck (赞：0)

### 思路：
题意可转化为 
$$
sum +ans\cdot k = x(sum=\sum_{i\in state} a_i)
$$
即
$$
sum\equiv x\pmod k 
$$
。

显然~~通过直观感受~~，我们确定 $k$ 以后就可以较快地算出关于 $sum$ 的值和合法方案。

又发现数据范围 $n\le100$，时限 $2s$，显然可以 $O(n^4)$ 卡过去。

于是我们有了第一维循环：枚举 $k(0\le k\le n)$。

然后问题就转化成求一个选择序列，使得
$$
sum\equiv x\pmod k 
$$
并且 $sum$ 最大。

发现长得有点像背包，仔细一看还真是背包，于是 dp，设 $dp_{i,j}$ 表示在前 $i$ 个物品中选，容量为 $j$ 的 $sum$ 最大值。

发现第一层循环给了个限制 $k$（即选 $k$ 个数），则再给 $dp$ 数组加一维 $l$ 表示当前已选 $l$ 个数。

dp 式子是裸背包，但是需要加一个表示能否到达的判定。

$dp_{i,j,l}=\max\{dp_{i-1,j,l},dp_{i-1,(j-a_i)\bmod k,l-1}\}$。**不能通过无法到达的点转移**。

$ans=\dfrac{x-sum}{dp_{n,x\bmod k,k}}$。

时间复杂度为 $O(n^4)$。可以卡过去。
### AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, x, a[202], dp[202][202][202], ans = 0x3f3f3f3f3f3f3f3f;
int main() {
	cin >> n >> x;
	for (ll i = 1; i <= n; i ++ ) cin >> a[i];
	for (ll k = 1; k <= n; k ++ ) {
		memset(dp, -1, sizeof dp);
		dp[0][0][0] = 0;
		for (ll i = 1; i <= n; i ++ ) for (ll j = 0; j < k; j ++ ) for (ll l = 0; l <= i; l ++ ) {
			if (dp[i - 1][j][l] != -1) dp[i][j][l] = dp[i - 1][j][l];
			if (l > 0 && dp[i - 1][((j - a[i]) % k + k) % k][l - 1] != -1) dp[i][j][l] = max(dp[i][j][l], dp[i - 1][((j - a[i]) % k + k) % k][l - 1] + a[i]);
		}
		if (dp[n][x % k][k] != -1) ans = min(ans, (x - dp[n][x % k][k]) / k);
	}
	cout << ans;
}
```

---

## 作者：crzcqh (赞：0)

**题意**

选出若干个数 $A_i$，设选出了 $k$ 个且和为 $s$，要使 $s\equiv X \pmod k$ 并且 $\frac{X-s}{k}$ 最小，求最小的 $\frac{X-s}{k}$。

**分析**

根据题意，选择的 $k$ 个物品的魔法值总和 $s$ 存在 $(X-s)\bmod k=0$ 的关系，由于不是很好正面求答案，考虑 DP。

设 $f_{k,i,j,m}$ 是选 $k$ 个物品的情况下，遍历到了第 $i$ 个物品，已经选了 $j$ 个物品，$X\bmod k=m$ 时 $s$ 的最大值。

考虑状态转移方程，一共有两种情况：

1. 不选 $A_i$，则为 $f_{k,i-1,j,m}$。
2. 选 $A_i$，则余数会为 $(k+m-(A_i\bmod k))\bmod k$，$s$ 会加上 $A_i$。

**思路**

DP 状态转移方程：

$$f_{k,i,j,m}=\max(f_{k,i-1,j,m},f_{k,i-1,j-1,(k+m-(a_i\bmod k))\bmod k}+A_i)$$

答案：

$$\min\limits_{1\le k \le n}((X-f_{k,n,k,X\bmod k})\div k)$$

**复杂度**

时间复杂度：$O(N^4)$。

空间复杂度：$O(N^4)$。

---

## 作者：Walrus (赞：0)

## ABC192F
题目本意其实是将一个子集枚举改成 DP 的形式。

### Sub 1 暴力
不难想到子集枚举，这里直接给出 Code。
```cpp
cin >> n >> m;
for(int i = 0; i < n; ++i) cin >> a[i];
for(int S = 0; S < (1 << n); ++S) {
	int sum = 0, c = 0;
	for(int i = 0; i < n; ++i) {
		if((S >> i) & 1) sum += a[i], ++c;
	}
	if(!sum) continue;
	if(!((m - sum) % c)) ans = min(ans, (m - sum) / c);
}
cout << ans;
```

### Sub 2 正解
观察到暴力里有一行代码
```cpp
if(!((m - sum) % c)) ans = min(ans, (m - sum) / c);
```

可以发现当这个子集满足条件时一定有
$$m \equiv sum \pmod c$$

同时观察数据范围 $1\leq N \leq 100$，不难想到直接枚举 $c$。

朴素 DP 定义 $dp_{i,j,k}$ 表示前 $i$ 个数已经选了 $j$ 个模 $c$ 为 $k$。

转移式子显而易见讨论选或不选，特别注意定义的是 **$k$ 是拿过之后的模数（当然可以不选）**，故式子如下：
$$dp_{i,j,k}=\max(dp_{i-1,j,k}, dp_{i-1,j-1,(k+c-a_{i}\bmod c)\bmod c}+a_{i})$$

顺带一提，如果有 $i+j \equiv k \pmod c$ 且已知 $i,k,c$，则 $j=(k+c-i\bmod c)\bmod c$。

边界值为 $dp_{i, 0, 0} =0$ 。

答案为 $\min \limits_{1\leq c \leq n} \frac{m-dp_{n,c,m\bmod c}}{c}$。

前提是 $dp_{n,c,m\bmod c}>0$。

## Code
```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for (int i = j; i <= k; ++i)
#define drep(i, j, k) for (int i = j; i >= k; --i)
#define pb push_back
#define int long long
#define fir first
#define sec second
using namespace std;

const int inf = 1e18 + 1;

inline int read();

const int N = 1e2 + 5;
int n, m, a[N], ans = inf, sum;
int dp[N][N][N];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr), cout.tie(nullptr);

    //	freopen("potion.in", "r", stdin);
    //	freopen("potion.out", "w", stdout);

    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];

    rep(len, 1, n) {
        memset(dp, 0xcf, sizeof dp);
        dp[0][0][0] = 0;
        rep(i, 1, n) {
            dp[i][0][0] = 0;
            rep(j, 1, len) {
                rep(k, 0, len - 1) dp[i][j][k] =
                    max(dp[i - 1][j][k], dp[i - 1][j - 1][(k + len - a[i] % len) % len] + a[i]);
            }
        }

        if (dp[n][len][m % len] <= 0)
            continue;

        ans = min(ans, (m - dp[n][len][m % len]) / len);
    }

    cout << ans;

    return 0;
}

inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!(c >= '0' && c <= '9')) {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
    return x * f;
}
```

时间复杂度 $O(N^4)$。

---

