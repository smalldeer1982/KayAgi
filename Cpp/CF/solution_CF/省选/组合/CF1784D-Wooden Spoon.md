# Wooden Spoon

## 题目描述

$ 2^n $ people, numbered with distinct integers from $ 1 $ to $ 2^n $ , are playing in a single elimination tournament. The bracket of the tournament is a full binary tree of height $ n $ with $ 2^n $ leaves.

When two players meet each other in a match, a player with the smaller number always wins. The winner of the tournament is the player who wins all $ n $ their matches.

A virtual consolation prize "Wooden Spoon" is awarded to a player who satisfies the following $ n $ conditions:

- they lost their first match;
- the player who beat them lost their second match;
- the player who beat that player lost their third match;
- $ \ldots $ ;
- the player who beat the player from the previous condition lost the final match of the tournament.

It can be shown that there is always exactly one player who satisfies these conditions.

Consider all possible $ (2^n)! $ arrangements of players into the tournament bracket. For each player, find the number of these arrangements in which they will be awarded the "Wooden Spoon", and print these numbers modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the "Wooden Spoon" is always awarded to player $ 2 $ .

In the second example, there are $ 8 $ arrangements where players $ 1 $ and $ 4 $ meet each other in the first match, and in these cases, the "Wooden Spoon" is awarded to player $ 3 $ . In the remaining $ 16 $ arrangements, the "Wooden Spoon" is awarded to player $ 4 $ .

## 样例 #1

### 输入

```
1```

### 输出

```
0
2```

## 样例 #2

### 输入

```
2```

### 输出

```
0
0
8
16```

## 样例 #3

### 输入

```
3```

### 输出

```
0
0
0
1536
4224
7680
11520
15360```

# 题解

## 作者：Alex_Wei (赞：12)

设编号较大的人一定赢过编号较小的人，这与题目条件是相反且对称的。

我们发现特别奖的获奖条件是以递归形式定义的，这启发我们使用动态规划解决该问题。

先确定树的形态：顶部为根，底部为叶子，$1\sim n + 1$ 共 $n + 1$ 层，第 $i$ 层每个点的子树大小为 $2 ^ {n - i + 1}$。

自顶向下或自底向上考虑。

- 自底向上考虑时，我们需同时记录当前赢家的编号，和当前子树内获得特别奖的编号，无法接受；
- 自顶向下考虑时，每次转移都需要枚举输掉的玩家编号（在本小局中，获胜的玩家编号就是当前赢家编号），最后一步输掉的玩家刚好符合特别奖的要求，可以接受。

通过上述分析，设 $f_{i, j}$ 表示自上而下第 $i$ 层（倒数第 $i$ 轮）的赢家为 $j$ 且它输掉了之后的所有比赛的方案数。根据实际意义，$f_{1, j} = [j = 2 ^ n]$。

考虑 $f_{i, j}\to f_{i + 1, k}$（$j > k$）的贡献系数。我们不关心第 $i + 1$ 层 $j$ 子树形态，其方案数为从 $j - 2 ^ {n - i} - 1$ 个数（$1\sim j$，除了 $j$ 和第 $i + 1$ 层 $k$ 子树内 $2 ^ {n - i}$ 个数）中选出 $2 ^ {n - i} - 1$ 个数（最后有解释），和 $j$ 一起作为第 $i + 1$ 层 $j$ 的子树内所有点，乘以 $2 ^ {n - i}!$ 表示任意排列。还需要乘以 $2$ 表示第 $i + 1$ 层 $j, k$ 的位置可交换。

注意到贡献系数和 $k$ 无关，因此前缀和优化即可做到 $\mathcal{O}(2 ^ nn)$。[代码](https://codeforces.com/contest/1785/submission/192335438)。

关于贡献系数中组合数的解释：在 $1\sim p_1$ 中选 $q_1$ 个数，然后在 $1\sim p_2$ 中选 $q_2$ 个数（不能和之前选择的数重复），以此类推，选择之间无序。从限制最严格的 $p_1$ 开始依次考虑，有 $\binom {p_1} {q_1} \binom {p_2 - q_1} {q_2} \binom {p_3 - q_1 - q_2} {q_3} \cdots$。而整个 DP 过程相当于倒过来考虑这个问题，故有该看似不符合组合意义的转移系数。

---

## 作者：Leasier (赞：10)

不难发现若某个人 $i$ 获得了木质勺子，则一定存在 $1 = x_1 < x_2 < \cdots < x_n < i$，其中 $x_i$ 表示题目描述中那个递归关系的第 $i$ 层。

考虑 dp。设 $dp_{i, j}$ 表示考虑 $x_1, x_2, \cdots, x_i$，$x_i = j$ 的方案数——也即它从叶子一路赢到这里但是下一轮就输了的方案数 。

初值：$dp_{0, i} = [i = 0]$，这里 $0$ 相当于一个虚拟的最终胜者。

转移：$dp_{i, j} = 2 \times 2^{n - i}! C_{2^n - 2^{n - i} - j}^{2^{n - i} - 1} \displaystyle\sum_{k = 1}^{j - 1} dp_{i - 1, k}$，这里的 $2$ 是因为我们不关心 $j$ 所在子树，$2^{n - i}!$ 是因为我们只关心下一层的 $j$ 所在的子树内的顺序排布，$C_{2^n - 2^{n - i} - j}^{2^{n - i} - 1}$ 是因为我们要在 $(j, 2^n]$ 中选出 $2^{n - i} - 1$ 个数填充至那个子树内的其他位置。

答案：$\displaystyle\sum_{j = 1}^{i - 1} dp_{n, j}$，因为我们钦定的打败第一次就失败的 $i$ 的人 $j$ 并不固定，但我们知道其 $< i$。

前缀和优化即可。时间复杂度为 $O(n 2^n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
ll fac[1048577], inv_fac[1048577], dp[27][1048577], sum[27][1048577];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (register int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline ll comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int main(){
	int n, full;
	scanf("%d", &n);
	full = 1 << n;
	init(full);
	dp[0][0] = 1;
	for (register int i = 0; i <= full; i++){
		sum[0][i] = 1;
	}
	for (register int i = 1; i <= n; i++){
		int t = 1 << (n - i);
		for (register int j = 1; j <= full; j++){
			dp[i][j] = 2 * fac[t] % mod * sum[i - 1][j - 1] % mod * comb(full - t - j, t - 1) % mod;
			sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
		}
	}
	for (register int i = 1; i <= full; i++){
		printf("%lld\n", sum[n][i - 1]);
	}
	return 0;
}
```

---

## 作者：pengyule (赞：7)

这个 Div.2 F 比较简单，不过赛时因为必须回寝室所以最后一个多小时都没有打，也没看到这题，昨天自己想出来了。

画个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/4fgg9dby.png)

于是只需要考察满足下面那个条件的排列个数，最后乘上 $2^n$（因为我们现在钦定想要获得木勺的人 $k$ 在最左侧，而每一个它在最左侧的方案都可以同构成它在其他位置的情况）。

由于大小关系的限制，我们不难想到从小往大填数，必须后面所有集合都非空时才能填这个集合。

而我们进一步观察到，对于相邻两个集合 $\min$ 中间夹着的数值，只能填到后一个集合及其之后的集合的空位当中。

因此容易设出 $f(i,j)$ 表示已填后 $i$ 个集合，其中余下 $j$ 个空位的方案数。

转移是显然的：
- $2^{n-i-1}\cdot f(i,j)\to f(i+1,j+2^{n-i-1}-1)$（$0\le i<n$）
- $j\cdot f(i,j)\to f(i,j-1)$（$1\le i\le n$）

于是最终答案 $ans_k=2^n\times f(n,2^n-k)\times 2!\times 4!\times 8!\times \cdots \times (2^{n-1})!$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=1<<20;
int n,f[22][N+5],jc[N+5];
inline void add(int &x,int y){(x+=y)>=mod&&(x-=mod);}
int main(){
	cin>>n;
	jc[0]=1;
	for(int i=1;i<=(1<<n);i++)jc[i]=1ll*i*jc[i-1]%mod;
	f[0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=(1<<n)-(1<<n-i);j>=0;j--){
			if(i<n)add(f[i+1][j+(1<<n-i-1)-1],1ll*f[i][j]*(1<<n-i-1)%mod);
			if(j)add(f[i][j-1],1ll*j*f[i][j]%mod);
		}
	}
	int ans=1<<n;
	for(int i=1;i<=(1<<n);i++)cout<<1ll*f[n][(1<<n)-i]*jc[(1<<n)-i]%mod*ans%mod<<'\n';
}
```

---

## 作者：ningago (赞：3)

这里的编号与其他题解是反的，我认为更好一些。

不难发现每个子树的根即为每个子树的最小值。

定义子树大小为 $2^i$ 的层编号为 $i$。

自上而下考虑 DP。

$dp_{i,j}$ 表示考虑到第 $i$ 层，子树的根为 $j$ 且 $j$ 以后不会再成为根（即在上一层被打败）的方案数。

$$dp_{i,j}=\sum_{k=1}^{j-1}dp_{i+1,k}\times 2\times (2^{i-1})!\times \dbinom{2^n-j-2^{i-1}}{2^{i-1}-1}$$

含义分别为：枚举 $j$ 不在的那个儿子子树的根；$j$ 不在的那个子树的方案数；两个子树可以左右任意；$j$ 所在那个子树可以随意排列（即方案数）；在大于 $j$ 的数里选择 $2^{i-1}-1$ 个给 $j$ 所在的子树标号。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

#define mod 998244353
void plus_(int &x, int y) { x = (x + y) % mod; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b)
{
	int res = 1;
	while (b)
	{
		if (b & 1)
			mul_(res, a);
		mul_(a, a);
		b >>= 1;
	}
	return res;
}
#define N 20
#define M 1048580
int n, m;
int dp[N + 2][M];
int fac[M], invf[M];
int pre[N + 2][M];

int main()
{
	scanf("%d", &n);
	m = 1 << n;
	fac[0] = 1;
	for (int i = 1; i < m; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	invf[m - 1] = ksm(fac[m - 1], mod - 2);
	for (int i = m - 2; ~i; i--)
		invf[i] = 1ll * invf[i + 1] * (i + 1) % mod;
	auto C = [&](int n, int m) -> int
	{
		if (n < 0 || m < 0 || m > n)
			return 0;
		return 1ll * fac[n] * invf[m] % mod * invf[n - m] % mod;
	};
	dp[n + 1][0] = 1;
	for (int i = 0; i <= m; i++)
		pre[n + 1][i] = 1;
	for (int i = n; i; i--)
	{
		for (int j = 1; j <= m; j++)
		{
			pre[i][j] = dp[i][j] = 1ll * pre[i + 1][j - 1] * 2ll % mod * fac[1 << (i - 1)] % mod * C((1 << n) - j - (1 << (i - 1)), (1 << (i - 1)) - 1) % mod;
			plus_(pre[i][j], pre[i][j - 1]);
		}
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", pre[1][i - 1]);
	return 0;
}
```

---

## 作者：DerrickLo (赞：2)

考虑对于每个 $i$，他开始时在哪个叶子其实并不重要，所以我们钦定他在 $2^n$ 号点，然后将答案乘上 $2^n$ 即可。

然后考虑什么情况下 $i$ 满足条件，不难发现 $i$ 满足条件当且仅当从 $i$ 所在的点到 $1$ 的这条路径上，每个点的相邻子树中的最小值小于这个点所在子树中的最小值，也就是如果将整个序列从前到后分成长度为 $2^{n-1},2^{n-2}\ldots 2^0,2^0$ 的序列，那么这些序列的最小值就是单调递增的。

如果所有序列的最小值已经确定，考虑如何填其他数。记所有序列的最小值分别是 $a_1,a_2,\ldots a_n$，那么所有在 $(a_1,a_2)$ 之间的数只能放在第一个序列里，在 $(a_2,a_3)$ 之间的数只能放在第一个和第二个序列里，直接使用乘法原理将所有数可以放的位置乘起来即可。

  那么考虑 dp。记 $f_{i,j}$ 表示第 $i$ 个序列的最小值为 $j$ 的方案数。转移时枚举上个序列的最小值 $k$，那么在 $(k,j)$ 之间的数能填的方案数也可以算出来。对于第 $i$ 个人的答案就是 $f_{n+1,i}$ 再乘上 $(i,n]$ 这些数填的方案数再乘 $2^n$。

这里暴力转移是 $\mathcal O(n4^n)$ 的，使用前缀和优化即可做到 $\mathcal O(n2^n)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,f[25][1200005],g[25][1200005],fac[1200005],inv[1200005],mx[25],ans[1200005],p[25];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,f[1][1]=fac[0]=p[0]=1;
	for(int i=1;i<=1048576;i++)fac[i]=fac[i-1]*i%mod;
	inv[1048576]=ksm(fac[1048576],mod-2);
	for(int i=1048575;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)mx[i]=mx[i-1]+(1<<n-i),p[i]=p[i-1]*(1<<n-i),p[i]%=mod;g[1][1]=fac[mx[1]-1];
	for(int i=2;i<=n+1;i++){
		for(int j=i;j<=mx[i-1]+1;j++){
			int l=i-1,r=min(mx[i-2]+1,j-1);
			if(l<=r)f[i][j]=(g[i-1][r]-g[i-1][l-1]+mod)%mod*inv[mx[i-1]+1-j]%mod,f[i][j]%=mod;
			g[i][j]=g[i][j-1]+f[i][j]*fac[mx[i]-j]%mod,g[i][j]%=mod;
		}
	}
	for(int i=1;i<=(1<<n);i++)cout<<f[n+1][i]*fac[(1<<n)-i]%mod*p[n]%mod*(1<<n)%mod<<"\n";
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

设 $dp_{i,j}$ 为，在 $2^i$ 个人中排名为 $j$ 并且获得安慰奖的方案数。

显然 $j=1$ 时 $dp_{i,j}=0$。否则，我们要将 $2^i$ 个人划分为两个大小为 $2^{i-1}$ 的集合，使得 $j$ 和 $1$ 不在同一个集合中。枚举新排名为 $k$ 则有：

$$
dp_{i,j} = (2^{i-1})!\sum_{k=1}^{j-1} dp_{i-1,k} \dbinom{2^i-j}{2^{i-1}-k} \dbinom{j-2}{k-1}
$$

这个东西一看就可以卷积优化，所以 tag 里面有 NTT 之类的东西，但是复杂度是丑陋的 $O(n^22^n)$。感觉这种做法不用多项式科技很难继续做到 $O(n2^n)$。

发现问题的主要矛盾就在于，你的**标号是每一步独立分配的**，这就为你的计算造成了很大麻烦。

所以我们**不分配标号**，直接维护整体排名。但是这样会损失最小值信息，因此我们改为维护最小值。

发现我们相当于对集合组 $S_0$、$S_1$、$S_2$、$\cdots$、$S_{n}$ 计数，满足 $|S_i| = 2^i$，$S_i \subset S_{i+1}$，$\min(S_i+1) < \min(S_i)$，$S_0$ 是给定的。

因此设 $dp_{i,j}$ 为，确定 $\min(S_i)$ 之后（且 $\min(S_i)=j$），有多少种扩充 $S_{i+1 \cdots n}$ 的方法。

发现如果 $\min(S_{i+1})=t$ 一定，它对 $\min(S_i) = j > t$ 的贡献是一定的。可以前缀和优化。复杂度 $O(n2^n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=22,MAXM=(1<<20)+10,MOD=998244353;
int n,m,dp[MAXN][MAXM],frac[MAXM],inv[MAXM];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {return frac[d]*inv[u]%MOD*inv[d-u]%MOD;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,m=(1<<n);
	frac[0]=1; ffor(i,1,m) frac[i]=frac[i-1]*i%MOD;
	inv[m]=qpow(frac[m],MOD-2);
	roff(i,m-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	dp[n][1]=1;
	roff(i,n-1,0) {
		ffor(j,1,m-(1<<i+1)+1) dp[i][j+1]=dp[i+1][j]*C((1<<i)-1,m-j-(1<<i))%MOD;
		ffor(j,1,m-(1<<i)+1) dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
		ffor(j,m-(1<<i)+2,m) dp[i][j]=0;
	}
	int mul=qpow(2,n);
	ffor(i,0,n-1) mul=mul*frac[1<<i]%MOD;
	ffor(i,1,m) cout<<dp[0][i]*mul%MOD<<'\n';
	return 0;
}
```

注：如果你一开始就想到**利用映射计数**，那么本题将会变得异常简单。

---

## 作者：_Yonder_ (赞：0)

该题内组合数的实际意义真是神秘。

令 $f_{k,i}$ 表示倒数第 $k$ 场比赛胜者为 $i$ 且不考虑 $i$ 的子树排列的方案数。

初始值：$f_{1,1}=2$（为什么是 $2$，详见样例一）。

转移：$f_{i,j}=\displaystyle\sum^{j-1}_{k=1}f_{i-1,k}\times2^{n-i+1}!\times2\times C^{2^{n-i+1}-1}_{2^n-2^{n-i+1}-k}$。

第 $i$ 个人的方案数为 $\displaystyle\sum^{i-1}_{k=1}f_{n,k}$。

前缀和优化即可。

关于该题转移中组合数的实际意义：

假设我们要在 $a_i\sim w$ 中选 $b_i$ 个数（$a_i$ 单调递增），每次选的数不能与前面重复，则有 $\displaystyle\prod _{i\le n}C^{w-a_i+1-\sum_{j>i}b_j}_{b_i}$。

所以转移中组合数的实际含义为 $k$ 子树内点的排列数。

---

