# [AGC041D] Problem Scores

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc041/tasks/agc041_d

コンテストで使う $ N $ 問の問題がジャッジに選ばれ、各問に配点を付ける段階になりました。

問題 $ i $ の配点 $ A_i $ は、$ 1 $ 以上 $ N $ 以下の整数でなければなりません。 また、すでに問題は難易度順に並んでおり、$ A_1\ \le\ A_2\ \le\ \ldots\ \le\ A_N $ でなければなりません (複数問の配点が同じになるのは構いませんが)。

ICPC のファンであるあなたは、解いた問題数が多い参加者ほど上位となってほしいと考えています。 この理由から、任意の $ k $ ($ 1\ \le\ k\ \le\ N-1 $) に対して、任意の $ k $ 問の配点の合計が任意の $ k+1 $ 問の配点の合計より真に小さくなるようにしたい、とあなたは考えています。

このような配点の付け方は何通りあるでしょうか？この数を与えられた素数 $ M $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ 9\ \times\ 10^8\ <\ M\ <\ 10^9 $
- $ M $ は素数である。
- 入力中のすべての値は整数である。

### Sample Explanation 1

可能な配点の付け方は $ (1,\ 1) $, $ (1,\ 2) $, $ (2,\ 2) $ です。

### Sample Explanation 2

可能な配点の付け方は $ (1,\ 1,\ 1) $, $ (1,\ 2,\ 2) $, $ (1,\ 3,\ 3) $, $ (2,\ 2,\ 2) $, $ (2,\ 2,\ 3) $, $ (2,\ 3,\ 3) $, $ (3,\ 3,\ 3) $ です。

## 样例 #1

### 输入

```
2 998244353```

### 输出

```
3```

## 样例 #2

### 输入

```
3 998244353```

### 输出

```
7```

## 样例 #3

### 输入

```
6 966666661```

### 输出

```
66```

## 样例 #4

### 输入

```
96 925309799```

### 输出

```
83779```

# 题解

## 作者：Kubic (赞：48)

这是一篇思想极度简洁的题解。

首先先考虑转化一下第三个条件。

令 $k=\lfloor\dfrac{n}{2}\rfloor$。

则我们可以发现满足条件三等价于前 $k+1$ 个数之和严格大于后 $k$ 个数。

此时再考虑如何刻画第二个条件。

初始时令 $A_i=n$，每一次选择一个前缀减去 $1$，这样所生成的序列一定不重不漏地覆盖了所有的满足条件二情况。

维护 $\Delta=$ 前 $k+1$ 个数之和 $-$ 后 $k$ 个数之和。

容易发现 $\Delta$ 初值为 $n$。

对于每一个 $i$ 容易预处理出 $w_i$ 表示对前缀 $A[1\dots i]$ 进行一次操作时 $\Delta$ 会发生什么变化。显然无论对哪个前缀操作 $\Delta$ 都会减少。

那么现在就转化为一个完全背包问题：

有 $n$ 种物品，每一种都有无限个，第 $i$ 种物品重量为 $w_i$，现在要选出一些物品使得总重不超过 $n-1$，求方案数。

容易使用 $dp$ 在 $O(n^2)$ 时间内计数。

简短的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 5005
int n,P,ans,w[N],dp[N];
int main()
{
	scanf("%d %d",&n,&P);dp[n]=1;
	for(int i=1;i<=(n+1)/2;++i) w[i]=i;
	for(int i=1;i<=n/2;++i) w[n-i+1]=i;
	for(int i=1;i<=n;++i) for(int j=n;j>=w[i];--j)
		dp[j-w[i]]=(dp[j-w[i]]+dp[j])%P;
	for(int i=1;i<=n;++i) ans=(ans+dp[i])%P;
	printf("%d\n",ans);return 0;
}
```

---

## 作者：CYJian (赞：8)

题目中前两个限制较弱，先不考虑。

考虑第三个限制：相当于要求前 $k+1$ 个数的和一定要大于后 $k$ 个数的和。

不难发现，当 $k \leq \lfloor \frac{n+1}{2} \rfloor - 1$ 的时候这个限制都满足，那么更大就不需要考虑了。

考虑更大只会让中间出现重叠部分，减去重叠部分就是 $k = \lfloor \frac{n+1}{2} \rfloor - 1$ 的情况。

然后再考虑 $k < \lfloor \frac{n+1}{2} \rfloor - 1$ 的时候，相当于是 $k = \lfloor \frac{n+1}{2} \rfloor - 1$ 的时候两边减去几个数。考虑到左边减的一定不多于右边减的（因为 $A_i$ 是从小到大排列的）。那么如果 $k=\lfloor \frac{n+1}{2} \rfloor - 1$ 的时候合法，那么 $k < \lfloor \frac{n+1}{2} \rfloor - 1$ 的时候一定合法。

综上所述，我们只需要考虑 $k = \lfloor \frac{n+1}{2} \rfloor - 1$ 的时候的限制就行了。

为了方便，我们令：

$$S_l = A_1 + A_2 + A_3 + \ldots + A_{k} + A_{k+1}$$

$$S_r = A_{n-k+1} + A_{n-k+2} + \ldots + A_{n-1} + A_{n}$$

考虑到限制等价于：$ S_l > S_r$。

而 $A_{i} \leq A_{i+1}$，则不难发现 $1 \leq S_l - S_r \leq n$。

然后我们可以分 $n$ 的奇偶讨论了：

### 对于偶数的情况：

考虑枚举 $A_{k+2}$ 的取值。我们先假装前 $k+1$ 和后 $k$ 个数都等于 $A_{k+2}$。然后考虑调整前 $k+1$ 个数和后 $k$ 个数。

我们可以做的调整是，让前 $k+1$ 个数中一个前缀的数同时 $-1$ 和让后 $k$ 个数的一个后缀的数同时 $+1$。

然后我们设 $f[i][j]$ 表示前 $i$ 个数总共减 $j$ 的方案数，设 $g[i][j]$ 表示后 $k$ 个数中加了 $i$ 次后缀，总共加了 $j$ 的方案数。

那么我们考虑钦定 $A_{k+2} = x$，则前 $k+1$ 个数最多比后 $k$ 个数大 $x$。

则这个情况下，考虑计算方案数为：

$$ \sum_{x=1}^{n}\sum_{i=0}^{x-1} \sum_{j=0}^{x-i-1} \sum_{t=0}^{\min(j,n-i)} f[k+1][i] \times g[t][j] $$

若记 $G[i][j] = \sum_{x=0}^{i}\sum_{y=0}^{j} g[x][y]$，则方案数为：

$$ \sum_{x=1}^{n}\sum_{i=0}^{x-1} f[k+1][i] \times G[n-x][x-i-1] $$

现在考虑如何求解 $f$ 和 $g$：

对于 $f$，考虑由 $f[i][j]$ 转移：可以直接暴力枚举当前这个 $i$ 位置减多少次前缀，枚举一个 $x$ 就可以转移到 $f[i+1][j+x\times i]$。不难发现，由于第二维需要用到的只有 $[0, n)$ 以内的数，则我们可以只将 $j+x \times i$ 枚举到 $n$。那么这样的复杂度不难发现是 $O(n^2 \log n)$ 的。

考虑 $g$ 的转移。类比上面，我们还是枚举当前算到第 $i$ 个位置，但是需要枚举之前加了 $j$ 次后缀。然后再枚举加过的和为 $k$。如果我们让 $i$ 这个位置的后缀加 $1$，则会从 $g[j][k]$ 转移到 $g[j+1][k+i]$。如果直接这么枚举是 $O(n^3)$ 的。但是我们发现 $k$ 的枚举起点实际上应该是 $i \times j$。类比上面的复杂度，这个也是 $O(n^2 \log n)$ 的。

求解完 $f$ 和 $g$ 之后，这就做完了。

### 对于奇数的情况

这时候没有中间的点来枚举了，我们就考虑枚举 $A_{k+1}$ 为 $x$。式子和上面几乎一样，只是 $f[k+1][i]$ 变成了 $f[k][i]$。其他的分析是一样的。

然后这题就做完了。

---

### 一点闲话

好像有牛逼的 $O(n^2)$ 做法，可惜我不会。这个 $O(n^2 \log n)$ 的做法是赛时极限赶出来的：（`22:30` 结束）

![](https://cdn.luogu.com.cn/upload/image_hosting/5gd2c2yx.png)

（成功涨了 200+ 的分）

感谢评论区的老哥指出一个小问题，现已纠正。

---

$\rm Code$：

```cpp
const int MAXN = 5010;

int mod;

inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline void Add(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }

int f[MAXN][MAXN];
int g[MAXN][MAXN];
int S[MAXN * 2];

int main() {
	int n = ri; mod = ri;
	int N = (n + 1) / 2;

	f[0][0] = 1;
	for(int i = 1; i <= N; i++)
		for(int j = 0; j <= n; j++)
			for(int k = j; k <= n; k += i)
				Add(f[i][k], f[i - 1][j]);

	g[0][0] = 1;
	for(int i = N - 1; i >= 1; i--) {
		for(int j = 0; j <= n; j++) {
			if(i * j >= n) break;
			for(int k = i * j; i + k <= n; k++)
				if(i + k <= n)
					Add(g[j + 1][k + i], g[j][k]);
		}
	}

	for(int i = 0; i <= n; i++)
		for(int j = 1; j <= n; j++)
			Add(g[i][j], g[i][j - 1]);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= n; j++)
			Add(g[i][j], g[i - 1][j]);

	int n1 = N, n2 = N - 1;
	int res = 0;
	if(!(n & 1)) {
		for(int x = 1; x <= n; x++)
			for(int i = 0; i < x; i++)
				res = (res + 1LL * f[n1][i] * g[n - x][x - i - 1]) % mod;
	} else {
		for(int x = 1; x <= n; x++)
			for(int i = 0; i < x; i++)
				res = (res + 1LL * f[n2][i] * g[n - x][x - i - 1]) % mod;
	}
	printf("%d\n", res);
	return 0;
}
```

---

## 作者：star_field (赞：2)

## 题意简述

有一个长度为 $N$ 的数列，满足：

1. 这个数列是不降的。
2. 这个数列中的数都不大于 $N$。
3. 令 $k=\left \lfloor \frac{n}{2} \right \rfloor$，前 $k+1$ 个数的和严格大于后 $k$ 个数的和（因为条件 1）。

输出有多少这样的方案，答案对 $M$ 取模。

## 做题思路

我们可以设 $D= {\textstyle \sum_{i=1}^{k+1}}i -{\textstyle \sum_{i=N-k}^{k}}i$（就是前 $k+1$ 个数与后 $k$ 个数的差），然后把 $A_1 ,\cdots, A_N$ 都初始化为 $N$（此时数列合法且 $D=N$）。然后现在我们要做的事情就是把 $A_i$ 减去一个数使数列合法的同时满足 $D>0$。这时你会发现这题其实就是一个变了形的**完全背包**！我们可以进行无限次操作 （就是 $A_i-1$），然后统计方案数就可以了。这样的做法是 $O(N^2)$ 的，而 $N\le5000$，完全可过。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,k,mod,x[N],f[N],ans;
int main(){
	cin>>n>>mod;
	f[n]=1;
	for(int i=1;i<=(n+1)/2;i++) 
		x[i]=i;
	for(int i=1;i<=n/2;i++) 
		x[n-i+1]=i;
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=n;j>=x[i];j--)
			f[j-x[i]]=(f[j-x[i]]+f[j])%mod;
	for(int i=1;i<=n;i++)
		ans=(ans+f[i])%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：jockbutt (赞：2)

这道题好像缺一个$O(n^2)$的代码，我来补一个。

##### FBI WARMING 本题解没有复杂到我都看不懂的公式，但是代码经过暴力压行，可能会引起不适

### 一.30分の解法

dfs+打表能得30分

极致压行30分code

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=4010;
ll n,modd=1e9+7;
inline ll read(){ll x=0,f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;}
ll ans=0,a[maxn];
int check(){ll s1=0,s2=0;if(n&1){for(ll i=1;i<=n/2+1;i++){s1+=a[i];}for(ll i=n/2+2;i<=n;i++)s2+=a[i];return s1>s2;}
else{for(ll i=1;i<=n/2;i++){s1+=a[i];}for(ll i=n/2+2;i<=n;i++)s2+=a[i];return s1>s2;}}
void dfs(ll u,ll v)
{
	if(u==n){ans+=check();return;}
	if(v>=a[1]+a[2]&&u>3)	return;
	if(a[u]+a[u-1]+a[u-2]>=a[1]+a[2]+a[3]+a[4]&&u>6)	return;
	for(ll i=v;i<=n;i++){a[u+1]=i;dfs(u+1,i);}
}
ll dabiao[110]={0,1,3,7,16,33,66,123,225,392,674,1117,1831,2922,4618,7144,10961,16534,24755,36551,53607,77715,111983,
				159778,226713,318981,446526,620481,858189,1179302,1613590,2195151,2974398,4009580,5384987,7198707};
int main(){n=read();modd=read();cout<<dabiao[n]%modd;return 0;} 
```

### 二.正解

首先，前两个限制条件根本不需要考虑，第三个条件需要转化一下。

第三个条件的充分必要条件：
1.当$n$是奇数时，设$n=2k+1$，有$A_i+A_2+A_3+.....+Ak+1>Ak+2+...+A_n$

2.当$n$是偶数时，设$n=2k$，有$A_i+A_2+A_3+.....+A_k>Ak+2+...+A_n$

Why？因为对于$i<j$，必有$A_i<A_j$，然后用贪心的思想，就可以证明这个~~简单的小结论。~~

然后，以$A_1$为基准建立差分数组$V_i$，把$A_1$给看做常数，上面那$1$、$2$两式的左右两边的个数相等。

枚举$A_1$，设它为$x$，经过~~枚举~~得出，在差分数列$V_i$上加上$1$时右边的式子会分别增加$1,2,3....k-1,k,k-1,k-2....3,2,1$

你看看，这东西和什么很像呢？

# 背包！！！

x为价值，$V_i$为选的物品。

code：

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=5010;
ll n,modd,v[maxn],dp[maxn][maxn],ans;
inline ll read(){ll x=0,f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;}
int main(){
	n=read(),modd=read();
	v[2]=1,dp[1][n]=1;
	for(ll i=3,j=n;i<=j;i++,j--)	v[i]=v[j]=v[i-1]+1;//V赋初值
	for(ll i=2;i<=n;i++)
		for(ll j=n;j>=0;j--)
		{
			dp[i][j]=(dp[i][j]+dp[i-1][j])%modd;
			if(j>0)	dp[i][max(0ll,j-v[i])]=(dp[i][max(0ll,j-v[i])]+dp[i][j])%modd;//背包转移
		}
	for(ll i=1;i<=n;i++)	ans=(ans+i*dp[n][i])%modd;
	printf("%lld",ans);
	return 0;
   cout<<"I AK IOI"<<endl;
}
```

真的很短，核心代码才五行。


---

## 作者：AuCloud (赞：1)

前两个限制比较简单，着重看第三个。

考虑极限情况，$k=\lfloor\frac{n}{2}\rfloor$ 的时候，显然极限是 $k$ 个取到后 $k$ 个，而 $k+1$ 个取到前面，意思就是前 $k+1$ 个数的和严格大于后面 $k$ 个数。

显然这个条件的 $k$ 越大越不容易满足。因此当这个极限被满足时，更小的  $k$ 一定满足条件。

考虑如何不重不漏地计算所有可能的情况：

首先先让所有数都 $=n$ ，此时一定合法。设 $C$ 为前 $k+1$ 项的和与后 $k$ 项的和的差值，不难发现一开始 $C=n$ 。

我们让操作 $P_x$ 表示将长度为 $x$ 的前缀位置上的值 $-1$ 。显然这可以很好地包括所有情况，并且以此做出的所有情况都合法。

所以我们的问题就转化成了：有 $n$ 种操作，每个操作可以做无数遍，共有多少种操作方式可以使得序列满足 $C>0$ 。

观察每种操作，显然无论怎么操作， $C$ 都会变小，且每次变小的数量为当前操作的前缀的长度减它占后缀的长度。

于是这个模型就可以抽象为一个背包，物品（操作）的重量为 $1\sim k$ ，背包容量（C）为 $k-1$ （ $C$ 严格大于 $0$ ）

记录方案数，最后累加就行。

奇怪的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[5001], dp[5001];
int main()
{
	int n, p;
	cin >> n >> p;
	int k = n & 1 ? (n >> 1) + 1 : (n >> 1);
	for(int i = 1; i <= k; i++)
	{
		a[i] = i;
	}
	for(int i = 1; i <= (n >> 1); i++)
	{
		a[n - i + 1] = i;
	}
	dp[n] = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = n; j >= a[i]; j--)
		{
			dp[j - a[i]] = (dp[j - a[i]] + dp[j]) % p;
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = (ans + dp[i]) % p;
	cout << ans;
	return 0;
}


```

---

## 作者：qczrz6v4nhp6u (赞：0)

### Solution

对于第三个条件，$\sum_{x\in S}A_x$ 要尽可能大，$\sum_{x\in T}A_x$ 要尽可能小，所以 $S$ 直接取后缀，$T$ 直接取前缀。

然后发现 $k>\lfloor\frac{n-1}{2}\rfloor$ 的限制都是没用的：把中间的重叠部分各自减掉就变成了 $k\le \lfloor\frac{n-1}{2}\rfloor$ 的限制。

现在我们先把最左边的数填好，然后每一次操作分别在左边和右边加一个数，这个过程中任何时候左边总和减右边总和都要大于 $0$。发现左边的一定小于等于右边的，所以 $k=\lfloor\frac{n-1}{2}\rfloor$ 的限制是最严格的，只需要考虑这一个限制即可。下文均认为 $k=\lfloor\frac{n-1}{2}\rfloor$。

那么现在我们要做的是这样一个事情：计数不降序列 $A$ 的个数，满足 $\sum_{i=1}^{k+1}A_i-\sum_{i=1}^{k}A_{n-i+1}>0$。

计数的是不降序列且限制与序列的和相关，于是你想到了 [P7519 [省选联考 2021 A/B 卷] 滚榜](https://www.luogu.com.cn/problem/P7519)：计数原序列的差分序列，将不降的限制转化为非负的限制。

继续考虑每一个位置的差分数组会贡献多少次。记 $B_i=A_i-A_{i-1}$，$C_i$ 表示 $B_i$ 贡献的次数。那么若 $n\equiv 1\pmod 2$，则 $C=\{1,0,-1,-2,\cdots,-k+1,-k,-k+1,\cdots,-2,-1\}$；否则 $C=\{1,0,-1,-2,\cdots,-k+1,-k,-k,-k+1,\cdots,-2,-1\}$。即 $n$ 为偶数时会在中间多出一个 $C_i=-k$ 的位置。

现在的问题就是这样：计数非负序列 $B$ 的个数，满足：

- $\sum_{i=1}^nB_i\le n$；
- $\sum_{i=1}^nB_iC_i>0$。

直接做是 $O(n^3)$ 的，考虑继续优化。

重新刻画填数的过程：最开始 $B_1=n,B_i=0(2\le i\le n+1)$，一次操作即选取 $2\le i\le n+1$，将 $B_1\gets B_1-1,B_i\gets B_i+1$。

发现此时我们可以丢掉第一条限制了。此时问题就是一个完全背包，时间复杂度 $O(n^2)$，可以通过。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=5005;
int n,m,mod,f[N];
inline int add(int x,int y){return (x+=y)>=mod&&(x-=mod),x;}
inline int Add(int &x,int y){return x=add(x,y);}
inline int sub(int x,int y){return (x-=y)<0&&(x+=mod),x;}
inline int Sub(int &x,int y){return x=sub(x,y);}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>mod;m=(n-1)>>1;
	f[n]=1;
	for(int i=2;i<=n+1;i++){
		int w=-(i<=m+2?i-2:n-i+1)-1;
		for(int k=n+w;k>=0;k--)
			Add(f[k],f[k-w]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		Add(ans,f[i]);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：zhiyin123 (赞：0)

因为 $A_i$ 是从小到大排序的，观察第 3 个限制，对于任意集合大小 $k$，我们只需要满足 $\displaystyle \sum_{i = n - k + 1} ^ n A_i < \sum_{i = 1} ^ k A_i$ 即可。

设命题 $p_k$ 表示 $\displaystyle \sum_{i = n - k + 1} ^ n A_i < \sum_{i = 1} ^ {k + 1} A_i$，那么，我们需要满足的就是 $p_1\land p_2\land \cdots\land p_{n - 1}$。

但是又可以发现，$p_1,p_2,\dots,p_{n - 1}$ 中 $p_{\lfloor\frac{n}{2}\rfloor + 1}$ 不弱于其他的，即 $\forall j\in\{1,2,\dots,n-1\}$，有 $p_{\lfloor\frac{n}{2}\rfloor + 1}\Rightarrow p_j$。这还是因为 $A_i$ 是从小到大排序的。

所以，限制 3 就变成了 $\displaystyle p_{\lfloor\frac{n}{2}\rfloor + 1} : \sum_{i = n - (\lfloor\frac{n}{2}\rfloor + 1) + 1} ^ n A_i < \sum_{i = 1} ^ {\lfloor\frac{n}{2}\rfloor + 1} A_i$。

为了方便，我们设 $\displaystyle D = \sum_{i = 1} ^ {\lfloor\frac{n}{2}\rfloor + 1} A_i - \sum_{i = n - (\lfloor\frac{n}{2}\rfloor + 1) + 1} ^ n A_i$，所以限制 3 就是 $D > 0$。

考虑限制 1 要求 $A_i$ 有序，我们一般有以下 2 种办法处理这个限制：

1. 直接在 dp 之类的东西中增加状态，考虑到 $A_i$ 时记录 $A_{i - 1}$ 的值。
2. 不直接对 $A_i$ 进行 dp，而是它的**差分数组**。

办法 1 不太合适，因为增加的状态会使时间复杂度难以优化到 $O(n^2)$。

办法 2 也不合适，因为 $A_i$ 有值域限制 $[1,n]$，而**差分**难以直接限制其值域。

怎么办呢？我们感受到，$A_i$ 越大，越**容易**满足限制 3。特别的，暂且**删掉**限制 2，如果 $n>1$ 且 $\exists A_i,A_i\leq 0$，那么一定**不满足**限制 3。

所以，我们就有一种方法，**改进一下办法 2**，让限制 3“强于”限制 2。

首先，我们令所有 $A_i\leftarrow n$，容易算出此时 $D = n$，然后进行若干次**前缀减**，在操作的过程中，$D$ 只可能减少，而我们要在过程中保证 $D$ 始终大于 $0$。这样做就自然而然地可以满足限制 1 和限制 2 了！

对于这种方法，我们可以把它概括为背包问题。总共有 $n$ 个物品，其中第 $i$ 个物品为"将 $A_1,A_2,\dots,A_i$ 都减 $1$"，而这个物品的价格为"这次操作让 $D$ 改变的变化量"，每个物品都可以选**无数次**，但是价格之和不能超过 $n$。

这个背包的复杂度就是 $O(n^2)$ 的。

# code


```cpp
#include<iostream>
using std::cin; using std::cout; using std::endl;
using ll=long long;
constexpr int MAXN=5000;
int N=0; ll M=0;
ll mo(ll x){return x>=M?x-M:x;}
void n_add(ll &x,ll y){x=mo(x+y); return ;}
ll f[MAXN+5]={};
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>M;
	f[N]=1;
	int mid=(N>>1)+1;
	for(int i=1;i<=N;i++){
		int w;
		if(N&1){w=(i<=mid?i:mid-(i-mid));}
		else{if(i<mid) w=i; else if(mid==i) w=mid-1; else w=mid-1-(i-mid);}
		for(int j=N-w;j>=1;j--) n_add(f[j],f[j+w]);
	}
	ll ans=0;
	for(int i=1;i<=N;i++) n_add(ans,f[i]);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：aoeiuv (赞：0)

题目的限制等价于取长度为 $k+1$ 的前缀，分数和大于长度为 $k$ 的后缀。考虑如何计数，这里有个小技巧，可以把计数转为：先将所有数赋值为 $n$，再进行若干次前缀 $-1$ 的操作。这样既满足了递增的要求，也满足了计数的不重不漏！

接下来考虑一次操作会对 $k+1$ 前缀和 $k$ 后缀产生什么影响？分开考虑太麻烦了，我们可以维护两者之差 $\Delta$，初始时 $\Delta = n$。

设数组中间位置 $mid = \left\lceil\dfrac{n}{2}\right\rceil$，操作的前缀位置为 $[1,p]$。假如 $p\le mid$，那么 $\Delta \leftarrow \Delta - p$。$p>mid$，$\Delta \leftarrow \Delta - (n - p + 1)$。

最后 $\Delta$ 每种不同的取值的方案数之和，便是 $A$ 数组构造的方案数了。怎么计算这个东西？发现这个问题变成了一个完全背包的模型：背包容量是 $[1,n-1]$，也就是 $\Delta$。物品 $w_i$ 的大小就是操作对 $\Delta$ 的影响，因为操作次数无限制，所以等价于物品有无限个。这就转换成完全背包了！直接做即可，时间复杂度 $\mathcal{O}(n^2)$，因为背包大小和物品数量都是 $\mathcal{O}(n)$ 的。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;

int n,m,f[N],w[N];

int main(){
    cin >> n >> m;
    int k = n / 2;
    for (int i = 1;i <= k;i++) w[i] = i;
    for (int i = k + 1;i <= n;i++) w[i] = n - i + 1;
    f[n] = 1;
    for (int i = 1;i <= n;i++)
        for (int j = n;j >= w[i];j--)
            (f[j - w[i]] += f[j]) %= m;
    int ans = 0;
    for (int i = 1;i <= n;i++)
        (ans += f[i]) %= m;
    cout << ans;
    return 0;
}
```

---

## 作者：bluewindde (赞：0)

在分值不降的条件下，要使任意一个大小为 $k$ 的子集 $S$ 内题目的分值之和少于任意一个大小为 $k + 1$ 的子集 $T$ 内题目的分值之和，容易发现只需要取 $S$ 为后 $k$ 道题目，$T$ 为前 $k + 1$ 道题目时满足限制即可。

换而言之，只需要对满足 $a$ 的每一段长为 $k + 1$ 的前缀的和大于对应的长为 $k$ 的后缀的和的方案计数。

为了方便，可以把分值不降的限制转化为：初始令所有 $a_i = n$，每次选择一个前缀并整体减一，但必须保证所有 $a_i$ 为正整数。

朴素地，设 $dp_{i, a, b}$ 表示已经处理完前缀 $i$，前缀和为 $a$，后缀和为 $b$ 的方案数。

套路地，设差分变量：$j = a - b$，为了合法，令 $j > 0$。$dp_{i, j}$ 表示已经处理完前缀 $i$，前缀和减后缀和为 $j$ 的方案数。

容易描述每次选择前缀并整体减一后 $j$ 的变化。问题就转化为一个完全背包问题：有 $n$ 种物品，每种物品有无限个，物品的体积确定，问总体积小于 $n$ 的条件下可以选择的最多的物品数量。

再套路地压缩第一维，跑完全背包即可。时间复杂度 $O(n^2)$。

参考代码如下。（需要指出代码中的背包是反过来跑的）

```cpp
#include <iostream>

#define int long long

using namespace std;

int n, mod;
int w[5005];
int dp[5005];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("AGC041D.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> mod;
    for (int i = 1; i <= (n + 1) / 2; ++i)
        w[i] = i;
    for (int i = n; i > n / 2; --i)
        w[i] = n - i + 1;
    dp[n] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = n; j >= w[i]; --j)
            dp[j - w[i]] = (dp[j - w[i]] + dp[j]) % mod;
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += dp[i];
    cout << ans % mod << endl;
    return 0;
}
```

---

## 作者：OrezTsim (赞：0)

非常好 DP 题。

首先钦定 $A$ 满足条件一。

那么如何满足条件二？可以想到，令初始所有 $A_i=1$，按 $i$ 从小到大依次对后缀 $[i,n]$ 进行 $+1$ 操作。设对 $i$ 执行了 $D_i$ 次后缀加，那么这部分满足 $\sum\limits_{i=1}^nD_i<n$ 即可。

除此之外，要使得 $\sum\limits_{x \in S}A_x-\sum\limits_{x \in T}A_x$ 最大，就要满足：

- $S$ 取 $A$ 中最大的 $k$ 个数，也就是 $A_{n-k+1},A_{n-k+2},\cdots,A_{n-1},A_n$。
- $T$ 取 $A$ 中最小的 $k+1$ 个数，也就是 $A_1,A_2,\cdots,A_k,A_{k+1}$。

此处显然有 $k=\left\lfloor\dfrac{n}{2}\right\rfloor$ 最蓟县，满足这一点那么第三条也搞完了。

记 $V=\sum\limits_{x \in S}A_x-\sum\limits_{x \in T}A_x$。

对 $i$ 执行一次后缀加，对 $V$ 产生的贡献也是容易计算的。

根据定义，$V<0$，发现有点难搞，因为初始 $V=1$，而且如果在 $i=1$ 执行后缀加，$V$ 甚至还会变大！

所以对称一下，令初始所有 $A_i=n$，像上面那样执行前缀减，题目就彻底转化为完全背包了。

也就是给定 $n$ 个数 $w_i$，每个 $w_i$ 可以选择无限次，要求满足 $\sum w<n$ 的方案数。

其中 $w_i$ 表示对 $i$ 执行一次前缀减对 $V$ 产生的贡献，$f$ 的下标表示 $-V$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e3+10; int n,P,w[N],f[N];
auto md(int &x,int y) { ((x+=y)>=P)&&(x-=P); }

auto main() -> signed {
    cin>>n>>P,f[n]=1;
    iota(w+1,w+(n+1>>1)+1,1);
    for(int i=1;i<=(n>>1);++i) w[n-i+1]=i;
    for(int i=1;i<=n;++i)
        for(int j=n;j>=w[i];--j)
            md(f[j-w[i]],f[j]);
    return cout<<accumulate(f+1,f+1+n,0ll)%P,0;
}
```

---

