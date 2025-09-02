# [ABC399F] Range Power Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc399/tasks/abc399_f

给定正整数 $N, K$ 以及长度为 $N$ 的整数序列 $A = (A_1, A_2, \dots, A_N)$。  
请计算以下表达式的值对 $998244353$ 取模后的余数：

$$
\displaystyle \sum_{1 \leq l \leq r \leq N} \left( \sum_{l \leq i \leq r} A_i \right)^K
$$

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq K \leq 10$
- $0 \leq A_i < 998244353$
- 输入均为整数

### 样例解释 1

所求的值为 $A_1^2 + A_2^2 + A_3^2 + (A_1 + A_2)^2 + (A_2 + A_3)^2 + (A_1 + A_2 + A_3)^2 = 3^2 + 1^2 + 2^2 + 4^2 + 3^2 + 6^2 = 75$。

### 样例解释 3

注意需要对结果取 $998244353$ 的模。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 2
3 1 2```

### 输出

```
75```

## 样例 #2

### 输入

```
1 10
0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 5
91 59 85 60 57 72 12 3 27 16```

### 输出

```
428633385```

# 题解

## 作者：yuhong056 (赞：6)

# 题解：AT_abc399_f [ABC399F] Range Power Sum

本题解给出一个仅用到前缀和且时间复杂度仅为 $O(N \times K)$ 的做法。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc399_f)

## 题意

给定 $N, K$ 以及 $A$ 数组，求 $A$ 中每个连续子段和的 $K$ 次方的和，形式化的讲就是要求：

$$\sum\limits_{1 \le l \le r \le N} (\sum\limits_{l \le i \le r} A_i) ^ K$$ 

## 推柿子

首先，先把 $\sum\limits_{l \le i \le r} A_i$ 改变为 [前缀和相减](https://oi.wiki/basic/prefix-sum/) 的形式，就变成要求：

$$\sum\limits_{1 \le l \le r \le N} (Sum_r - Sum_{l - 1}) ^ K$$ 

接着，将左边的 $\sum\limits_{1 \le l \le r \le N}$ 拆成 $\sum\limits_{l = 1}^N\sum\limits_{r = l}^N$ ，变成

$$\sum\limits_{l = 1}^N\sum\limits_{r = l}^N (Sum_r - Sum_{l - 1}) ^ k$$ 

然后，套用 [二项式定理](https://oi.wiki/math/combinatorics/combination/#二项式定理) 将 $(Sum_r - Sum_{l - 1}) ^ k$ 拆分为 $\sum\limits_{i=0}^k \binom{k}{i}Sum_r^i(-Sum_{l - 1})^{k - i}$ ，可得：

$$\sum\limits_{l = 1}^N\sum\limits_{r = l}^N \sum\limits_{i=0}^k \binom{k}{i}Sum_r^i(-Sum_{l - 1})^{k - i}$$ 

观察到 $\binom{k}{i}$ 与 $l, r$ 无关，可以将 $\sum\limits_{i=0}^k \binom{k}{i}$ 提出，得：

$$\sum\limits_{i=0}^k \binom{k}{i}[\sum\limits_{l = 1}^N\sum\limits_{r = l}^N Sum_r^i(-Sum_{l - 1})^{k - i}]$$ 

如果此时将 $(-Sum_{l - 1})^{k - i}$ 提出，可得：

$$\sum\limits_{i=0}^k \binom{k}{i}\{\sum\limits_{l = 1}^N[(-Sum_{l - 1})^{k - i}\times\sum\limits_{r = l}^N Sum_r^i]\}$$

此时可以用后缀和优化掉 $\sum\limits_{r = l}^N Sum_r^i$ ，复杂度 $O(N \times K ^ 2)$ 。

重点来了。这个 $\sum\limits_{r = l}^N$ 有点棘手，它从 $l$ 开始循环，必须要后缀和维护。有没有简单一点的方法呢？

当然。当我们交换 $\sum\limits_{r = l}^N$ 和 $\sum\limits_{l = 1}^N$ 的顺序时，式子变成了：

$\sum\limits_{i=0}^K \binom{k}{i} \{\sum\limits_{r=1}^N\sum\limits_{l=1}^r[Sum_r^i(-Sum_{l - 1})^{k - i}]\}$

现在就只需要维护前缀和了。继续把 $Sum_r^i$ 提出去，得：

$\sum\limits_{i=0}^K \binom{k}{i} \{\sum\limits_{r=1}^N[Sum_r^i\ \times\sum\limits_{l=1}^r(-Sum_{l - 1})^{k - i}]\}$

$\binom{k}{i}$ 可通过预处理阶乘逆元，将时间复杂度降为 $O(1)$ 。预处理 $Sum_r^i$ 和 $(-Sum_{l - 1})^{k - i}$ 的前缀也可以将时间复杂度降为 $O(1)$ ，综合起来仅有 $O(N \times K)$ 的时间复杂度。

## code

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXK = 12, MAXN = 2e5 + 25, MOD = 998244353;

int n, k;
ll fac[MAXK];
ll finv[MAXK];
ll Sum[MAXN][MAXK];
ll ans;
int a[MAXN];

void init() {
	for(int i = 0; i <= n; i++) {	//预处理 Sum[i] 的 x 次方
		Sum[i][0] = 1;
		for(int j = 1; j <= k; j++) {
			Sum[i][j] = Sum[i][j - 1] * a[i] % MOD;
		}
	}
	fac[0] = fac[1] = finv[0] = finv[1] = 1;
	for(int i = 2; i <= k; i++) {	//预处理阶乘及逆元
		finv[i] = (MOD - MOD / i) * finv[MOD % i] % MOD;
		fac[i] = fac[i - 1] * i;
	}
	for(int i = 2; i <= k; i++) {
		finv[i] = finv[i - 1] * finv[i] % MOD;
	}
}

ll C(int n, int m) {
	return fac[n] * finv[m] % MOD * finv[n - m] % MOD;
}

int main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] = (a[i] + a[i - 1]) % MOD;
	}
	init();
	for(int i = 0; i <= k; i++) {
		ll sum = 0, Suml = 0;
		for(int r = 1; r <= n; r++) {
			ll tmp; 	//tmp = (-Sum[r]) ^ k
			if(k - i & 1)tmp = (MOD - Sum[r - 1][k - i]) % MOD;
			else tmp = Sum[r - 1][k - i];
			(Suml += tmp) %= MOD;
			(sum += Sum[r][i] * Suml % MOD) %= MOD;
		}
		(ans += sum * C(k, i) % MOD) %= MOD;
	}
	cout << (ans + MOD) % MOD;
	return 0;
}
```

这是本蒟蒻的第三篇题解，管理员大大求过！

---

## 作者：yszkddzyh (赞：4)

考虑一种 dp 的思路，令：

$$s_{i, j} = \sum _ {l = i} ^ {n} \left(\sum _ {o = i} ^ {l} a_o \right) ^ j$$

显然 $\sum _ {i = 1} ^ n s_{i, k}$ 即为答案。

考虑转移，手搓多个实例我们注意到：

$$s_{i, j} = s_{i + 1, j} + (n - i + 1)a _ i ^ j + \sum _ {l = 1} ^ {j - 1} \binom{j}{l} a _ i ^ {j - l} s _ {i + 1, l}$$

上式通过定义略微变形即可证明，读者可以自行尝试。

于是就有了[代码](https://atcoder.jp/contests/abc399/submissions/64323532)。

这种思路是从后往前转移，从前往后是同理的。

---

## 作者：gavinliu266 (赞：4)

# 思路
我们将原式变形一下：
$$
原式=\sum_{r=1}^n \sum_{l=1}^r \left( \sum_{i=l}^r a_i \right)^k
$$

我们设 $\operatorname{dp}(x,y)= \sum \limits _{l=1}^x \left( \sum \limits_{i=l}^x a_i \right)^y$，则 $原式=\sum \limits_{r=1}^n\operatorname{dp}(r,k)$。

接着，我们只需要解决转移 $\operatorname{dp}$ 的问题即可。

我们将 $\operatorname{dp}$ 变形：
$$
\begin{aligned}
\operatorname{dp}(x,y) &=  a_x^y + \sum_{l=1}^{x-1} \left[ \left( \sum_{i=l}^{x-1} a_i \right) + a_x\right]^y \\
&= a_x^y + \sum_{l=1}^{x-1} \sum_{j=0}^y \binom{y}{j} \left( \sum_{i=l}^{x-1} a_i \right)^j a_x^{y-j} \\
&= a_x^y + \sum_{j=0}^y  \sum_{l=1}^{x-1} \binom{y}{j} \left( \sum_{i=l}^{x-1} a_i \right)^j a_x^{y-j} \\
&= a_x^y + \sum_{j=0}^y \binom{y}{j} a_x^{y-j} \sum_{l=1}^{x-1} \left( \sum_{i=l}^{x-1} a_i \right)^j \\
&= a_x^y + \sum_{j=0}^y \binom{y}{j} a_x^{y-j} \operatorname{dp}(x-1,j)
\end{aligned}
$$

于是我们得到了状态转移方程。

然后我们可以快速计算 $\operatorname{dp}$ 了，就做完了，时间复杂度：$O(nk^3)$ 或 $O(nk^2)$。

# 代码实现
可以通过预处理 $a_i^j$ 来达到 $O(nk^2)$，这里给出 $O(nk^3)$ 解法。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N = 2e5 + 5;
ll C[15][15];
ll ans;
ll dp[2][15];
int n, k;
ll a[N];
ll spow(ll a, ll b) {
    ll ret = 1;
    while(b) {
        ret = ret * a % mod;
        --b;
    }
    return ret;
}
int main() {
    C[0][0] = 1;
    for(int i = 1; i <= 12; ++i) {
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    // 组合数
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= k; ++j) {
            dp[i & 1][j] = spow(a[i], j);
            for(int l = 0; l <= j; ++l) {
                ll det = C[j][l] * dp[(i & 1) ^ 1][l] % mod * spow(a[i], j - l) % mod;
                dp[i & 1][j] += det;
            }
        }
        ans = (ans + dp[i & 1][k]) % mod;
    }
    printf("%lld\n", ans);
}
```

---

## 作者：XXh0919 (赞：3)

我来复习数论啦！

### 题意

给定一个长度为 $n$ 的序列 $A=\{a_1,a_2,a_3,...,a_n\}$ 和一个正整数 $k$，求：

$$\sum_{1\le l\le r\le n}\left(\sum_{l\le i\le r}a_i\right)^k$$

### 解法

如开头所言，这是一道数论题。看到这个式子中包含区间求和，那么不用想，直接前缀和。令 $s_i=\sum\limits_{i=1}^i a_i$，则原式就变为

$$\sum_{l=1}^{n}\sum_{r=l}^{n}(s_r-s_{l-1})^k$$

然后又看到后面这个 $(s_r-s_{l-1})^k$，这不就是二项式定理吗，拆了拆了：

$$\sum_{l=1}^{n}\sum_{r=l}^{n}\sum_{i=0}^k(-1)^{k-i}C_k^is_r^{i}s_{l-1}^{k-i}$$

注意到 $\sum\limits_{i=0}^k(-1)^{k-i}C_k^i$ 是一个定值，所以对于每一个 $i$，我们只需要考虑 $\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}s_r^{i}s_{l-1}^{k-i}$。容易发现，对于每一个 $r$，$l$ 都可以从 $1$ 取到 $r$，这样所有满足 $1\le l\le r\le n$ 的所有整数对 $(l,r)$ 都可以被不重复的取到，所以这个式子就可以变成

$$\sum_{r=1}^{n}\sum_{l=1}^{r}s_r^{i}s_{l-1}^{k-i}$$

即

$$\sum_{r=1}^{n}s_r^{i}\sum_{l=1}^{r}s_{l-1}^{k-i}$$

那么现在我们就只需要预处理出 $\sum\limits_{j=1}^ns_j^k$ 就行了。

直接放代码吧：

### Code


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 15, mod = 998244353;

int n, k;
int a[N];
int s[N];
int fac[25], inv[25], pows[N][20];

int quick_pow (int a, int b, int mod) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = (ans * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return ans;
} //快速幂求逆元

void init () {
	//预处理阶乘 
	fac[0] = 1;
	for (int i = 1; i <= k; ++ i) {
		fac[i] = fac[i - 1] * i % mod;
	}
	//预处理逆元 
	inv[k] = quick_pow (fac[k], mod - 2, mod);
	for (int i = k - 1; i >= 0; i --) {
		inv[i] = inv[i + 1] * (i + 1) % mod;
	}
	//预处理 s[i] ^ 0，s[i] ^ 1，...s[i] ^ k
	for (int i = 0; i <= n; ++ i) {
		pows[i][0] = 1ll;
		for (int j = 1; j <= k; ++ j) {
			pows[i][j] = pows[i][j - 1] * s[i] % mod;//pows[i][j] = s[i]^j
		}
	}
}

//求组合数 
int C (int n, int m) {
	if (m > n) return 0ll;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

signed main () {
	scanf ("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++ i) 
		scanf ("%lld", &a[i]), 
		s[i] = (s[i - 1] + a[i]) % mod;//前缀和 
	init ();
	int ans = 0ll;
	for (int i = 0; i <= k; ++ i) {
		int f;
		if ((k - i) & 1) f = -1;
		else f = 1;
		f = C(k, i) * f;
		f = (f + mod) % mod;
		int sl = 0, sr = 0;
		for (int j = 1; j <= n; ++ j) {
			sl = (sl + pows[j - 1][k - i]) % mod;
			sr = (sr + pows[j][i] * sl) % mod;
		}//根据二项式定理进行计算 
		ans = (ans + sr * f) % mod;
	}
	printf ("%lld\n", ans);
	return 0;
}
```

注：开 long long 哦。

---

## 作者：liaoxingrui (赞：2)

## Content

求：

$$\sum_{ l = 1 }^n \sum_{ r = l }^ n ( \sum_{ i = l }^r a_i )^K \bmod 998244353$$

## Solution

显然需要用到前缀和：

$$\sum_{ l = 1 }^n \sum_{ r = l }^ n ( sum_r - sum_{l-1} )^K$$

用二项式定理展开后可得：

$$\sum_{ k = 0 }^K \sum_{ l = 1 }^n \sum_{ r = l }^ n C^k_K \times sum_r^k \times ( -1 )^{ K - k } \times sum_{ l - 1 }^{ K - k }$$

再用前缀和（倒着跑一遍，将 $r$ 优化掉）优化后便可以过了：

$$\sum_{ k = 0 }^K \sum_{ l = 1 }^ n C^k_K \times sum_l^k \times Sum_{ l + 1 , K - k } \times ( -1 )^k$$

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=998244353;
int n,k,ans;
int a[N],sum[N];
int cnt[N][15],C[15][15];
int Pow(int a,int b){
	int cnt=a,ans=1;
	while(b){
		if(b&1)
			ans=ans*cnt%mod;
		cnt=cnt*cnt%mod;
		b>>=1; 
	}
	return ans;
}
void init(){
	C[0][0]=1;
	for(int i=1;i<=10;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=(sum[i-1]+a[i])%mod;
	}
	for(int i=n;i>=1;i--)
		for(int j=0;j<=10;j++)
			cnt[i][j]=((cnt[i+1][j]+Pow(sum[i],j))%mod+mod);
	for(int i=0;i<n;i++)
		for(int j=0;j<=k;j++)
			ans=((ans+C[k][j]*Pow(sum[i],k-j)%mod*cnt[i+1][j]*Pow(-1,j)%mod)%mod+mod)%mod;
	if(k&1)
		ans=mod-ans;
	cout<<(ans%mod+mod)%mod;
	return 0;
}
```

---

## 作者：_lqs_ (赞：2)

令 $s$ 表示前缀和数组。

则 $(\sum\limits_{l \le i \le r} a_{i})^k=(s_{r}-s_{l-1})^k$。我们考虑经典的计算以 $i$ 为结尾的答案，是这个东西：$ans_{i}=\sum\limits_{j=0}^{i-1} (s_{i}-s_{j})^k$。注意到 $k$ 很小，猜测做法是暴力展开，则有 $\sum\limits_{j=0}^{i-1} (s_{i}^k-xs_{i}^{k-1}s_{j}...)=\sum\limits_{p=0}^k (-1)^{k-p} \times mp_{p} \times qs_{i-1,k-p}s_{i}^{p}$，其中 $mp_{i}$ 表示 $k$ 次多项式下的杨辉三角系数，$qs_{i,j}$ 表示前 $i$ 项前缀和数组的 $j$ 次方的和。

那么可以 $O(k)$ 计算 $ans_{i}$ 的值，总时间复杂度 $O(nk)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define K 15
#define int long long
const int mod = 998244353;
int n,m,i,j,ans,k,a[N],s[N],qs[N][K],mp[K][K];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		b>>=1,a=a*a%mod;
	}
	return res;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	mp[0][0]=1,mp[1][0]=1,mp[1][1]=1;
	for(i=2;i<=k;i++){
		for(j=0;j<=k;j++){
			if(!j) mp[i][j]=mp[i-1][j];
			else mp[i][j]=mp[i-1][j-1]+mp[i-1][j];
		}
	}
	for(i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i],s[i]%=mod;
	qs[0][0]=1;
	for(i=1;i<=n;i++){
		for(j=0;j<=k;j++) qs[i][j]=qs[i-1][j]+qpow(s[i],j),qs[i][j]%=mod;
	}
	for(i=1;i<=n;i++){
		int c=1,x=0;
		for(j=k;j>=0;j--){
			x=c*qpow(s[i],j)*qs[i-1][k-j]%mod*mp[k][j]%mod;
			x+=mod,x%=mod;
			ans+=x,ans%=mod,c*=-1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：gesong (赞：2)

题目传送门：[[ABC399F] Range Power Sum](https://www.luogu.com.cn/problem/AT_abc399_f)。
# 思路
考虑推式子，记数组 $a$ 为题目的 $A$ 的前缀和，记 $f_{i,j}=\sum_{l=1}^i {a_l}^j$。

$$\begin{aligned}
\sum_{i=1}^n \sum_{j=i}^n (\sum_{l=i}^j A_l)^k &= \sum_{i=1}^n \sum_{j=i}^n (a_j-a_{i-1})^k \\
&=\sum_{i=1}^n \sum_{j=i}^n \sum_{l=0}^k (C_{k}^l\times {a_j}^{k-l}\times {a_{i-1}}^l \times (-1)^l) \\
&=\sum_{l=0}^k \sum_{i=1}^n \sum_{j=i}^n  (C_{k}^l\times{a_j}^{k-l}\times {a_{i-1}}^l \times (-1)^l) \\
&=\sum_{l=0}^k( C_{k}^l\times(-1)^l \times (\sum_{i=1}^n( {a_{i-1}}^l \times  \sum_{j=i}^n  {a_j}^{k-l} )))  \\
&=\sum_{l=0}^k(C_{k}^l\times (-1)^l\times  \sum_{i=1}^n( {a_{i-1}}^l  \times (f_{n,k-l}-f_{i-1,k-l}) ) )\\
\end{aligned}$$

$O(nk)$ 处理即可。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=998244353;
int a[N],f[N][20];
int w[N],c[20][20];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline int qpow(int a,int b){
	int s=1;
	while(b){
		if (b&1) s=s*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return s;
}
main(){
	c[0][0]=1;
	for (int i=1;i<=15;i++){//计算组合数
		c[i][0]=1;
		for (int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	int n=read(),k=read();
	for (int i=1;i<=n;i++) a[i]=(a[i-1]+read())%mod;
	for (int i=1;i<=n;i++) 
		for (int j=0;j<=k;j++) f[i][j]=(f[i-1][j]+qpow(a[i]%mod,j))%mod;
	for (int l=0;l<=k;l++){
		for (int i=1;i<=n;i++){
			int sum=(f[n][k-l]-f[i-1][k-l]+mod)%mod;
			w[l]=(w[l]+qpow(a[i-1],l)*sum%mod)%mod;
		}
	}
	int ans=0;
	int op=1;
	for (int l=0;l<=k;l++){ 
		ans=(ans+op*w[l]*c[k][l]%mod+mod)%mod;
		op*=-1;
	}
	cout <<ans;
    return 0;
}
//AtCoder Beginner Contest 399 RP++
//AtCoder Beginner Contest 399 RP++
//AtCoder Beginner Contest 399 RP++
//AtCoder Beginner Contest 399 RP++
//AtCoder Beginner Contest 399 RP++
```

---

## 作者：SamHH0912 (赞：2)

## 题目传送门

[AtCoder](https://atcoder.jp/contests/abc399/tasks/abc399_f) | [Luogu](https://www.luogu.com.cn/problem/AT_abc399_f)

---

## 思路

**本题解中，所有 $\bm{A_i^j}$ 都指的是 $\bm{A_i}$ 的 $\bm{j}$ 次方。**

### Part I

不妨设当前计算到了 $\displaystyle\sum_{1\le l\le r\le i}\bigg(\sum_{l\le j\le r}A_j\bigg)^K$，记为 $Ans_i$。显然，我们的最终结果应该是 $Ans_N$。

我们想想怎么从 $Ans_{i-1}$ 变成 $Ans_i$。

看到了 $\sum$，于是想到区间和。对于 $1\le j\lt i$，记当前的 $S_j$ 的值为 $\displaystyle\sum_{j\le p\lt i}A_p$。

于是，我们得到了：

$$Ans_i-Ans_{i-1}=\displaystyle\sum_{1\le j\lt i}\Big(S_j+A_i\Big)^K+A_i^K$$

（最后一项 $A_i^K$ 别丢了）

### Part II

令 $S_i=0$，并通过二项式定理展开式子右边，得到（$C_K^k$ 为组合数）

$$\displaystyle\sum_{j=1}^i\sum_{k=0}^K C_K^k\times S_j^{K-k}\times A_i^k$$

提取公因式（改变求和顺序），得到

$$\displaystyle\sum_{k=0}^{K}\Bigg(C_K^k\times\bigg(\sum_{j=1}^i S_j^{K-k}\bigg)\times A_i^k\Bigg)$$

由于 $K\le 10$，所以 $C_K^k$ 直接递推求出即可，$A_i^k$ 也可以暴力求。接下来，我们只需要关注 $\displaystyle\sum_{j=1}^i S_j^k$ 即可。

### Part III

记 $Sum_{i,k}=\displaystyle\sum_{j=1}^i S_j^k$。由于我们钦定了 $S_i=0$，所以当 $k\gt 0$ 时 $Sum_{i,k}=S_1^k+S_2^k+...+S_{i-1}^k$，当 $k=0$ 时 $Sum_{i,k}=S_1^k+S_2^k+...+S_{i-1}^k\color{red}+1$（在本题中，我们需要钦定 $0^0=1$；这里的 $1$ 是 $S_i^0$）。这里需要特判（后文会说明）。

经过如此简化，我们将 $Ans_i-Ans_{i-1}$ 的结果化成了 $$\displaystyle\sum_{k=0}^{K}\bigg(C_K^k\times Sum_{i,K-k}\times A_i^k\bigg)$$。如果各 $Sum_{i,k}$ 都是现成的，我们就可以在 $\mathcal{O}(NK)$ 的整体复杂度内完成 $Ans$ 的计算。

### Part IV

现在只剩下了最后一个问题：更新 $Sum_{i,k}$。

首先，我们发现计算 $Ans_i$ 时我们只需要用到 $Sum_{i,*}$，所以我们可以把 $Sum$ 数组压成一维的。

然后，我们发现：（$S_j$ 表示 $A$ 数组下标 $[j,\bm{i)}$ 的区间和；特别地，$S_i=0$）

$$Sum_{i,j}=S_1^j+S_2^j+...+S_{i-1}^j$$

$$Sum_{i+1,j}-A_{i+1}^j=(S_1+A_i)^j+(S_2+A_i)^j+...+(S_{\color{red}i}+A_i)^j$$

是不是感到很熟悉？

没错，这个 $Sum_{i+1,j}-A_{i+1}^j$ 的形式与 $Ans_i-Ans_{i-1}$ 的结果的形式完全一致！所以，我们无需再次拆式子，就得到了其转化后的形式：

$$Sum_{i+1,j}-A_{i+1}^j=\displaystyle\sum_{k=0}^{j}\bigg(C_j^k\times Sum_{i,j-k}\times A_i^k\bigg)$$

注意到求出 $Sum_{i+1,j}$ 需要 $k\in[0,j]\cap\N$ 的所有 $Sum_{i,k}$，所以，为了方便，我们按照从 $K$ 到 $0$ 的顺序（即降序）求出各 $Sum_{i+1,j}$ 就可以了。

### Postscript

整体时间复杂度因为需要更新 $Sum_{i,j}$ 变成了 $\mathcal{O}(NK^2)$，但是实际上 $K^2$ 部分的循环次数约等于 $\frac{K^2}{2}$，而且常数极小，所以跑得飞快（赛时代码只用了 72ms 跑过用了最长时间的点）。

最后，把两个最核心的式子在这里再写一遍：

$$Ans_i=Ans_{i-1}+\displaystyle\sum_{k=0}^{K}\bigg(C_K^k\times Sum_{i,K-k}\times A_i^k\bigg)$$

$$Sum_{i+1,j}=\displaystyle\sum_{k=0}^{j}\bigg(C_j^k\times Sum_{i,j-k}\times A_i^k\bigg)$$

---

## AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long

#define mod 998244353
#define K 17
int C[K][K],Sum[K],A[K]={1};//钦定任意数0次方为1

inline void precalc(int k){//递推求组合数
	for(int i=0;i<=k;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr),cout.tie(nullptr);
	
	int n,k,ans=0;
	cin>>n>>k;
	precalc(k);//别忘预处理
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		for(int j=1;j<=k;j++) A[j]=A[j-1]*1ll*a%mod;//求a[i]的幂
		for(int j=0;j<=k;j++){//求Ans[i]-Ans[i-1]的差，记为now
			int now=C[k][j]*1ll*(Sum[k-j]+!(k-j))%mod*A[j]%mod;
			ans=(ans+now)%mod;
		}
		for(int j=k;~j;j--){//降序（从K到0更新Sum数组）
			int now=0;//原来的值不能动，一会还要用
			for(int l=0;l<=j;l++){
				int now1=C[j][l]*1ll*(Sum[j-l]+!(j-l))%mod*A[l]%mod;
				now=(now+now1)%mod;
			}
			Sum[j]=now;//赋新值
		}
	}
	cout<<ans<<'\n';//输出答案
	
	return 0;
}
```

---

$$\text{Thanks for your reading.}$$

$$-\ \bullet\ -$$

---

## 作者：Tom17 (赞：2)

这是子区间问题，由 CDQ 分治的思想，我们便可以用分治完成这题。

对于当前区间 $[L,R]$，设其子区间贡献为 $f_{L,R}$，记 $mid=\frac{L+R}{2}$，显然有：

$$
f_{L,R}=f_{L,mid}+f_{mid+1,R}+g_{L,R}
$$

其中 $g_{L,R}$ 是 $[L,R]$ 的所有跨越 $mid$ 和 $mid+1$ 的子区间的贡献。

记 $A_{L...R}=\sum_{i=L}^R A_i$。

有推导：

$$
\begin{aligned}
g_{L,R} &= \sum_{l=L}^{mid}\sum_{r=mid+1}^{R} (A_{L...R})^k\\
&=\sum_{l=L}^{mid}\sum_{r=mid+1}^{R} (A_{L...mid} + A_{mid+1...R})^k\\
&=\sum_{l=L}^{mid}\sum_{r=mid+1}^{R}\sum_{i=0}^k C_i^kA_{L...mid}^iA_{mid+1...r}^{k-i}\\
&=\sum_{i=0}^kC_i^k\sum_{l=L}^{mid}A_{L...mid}^i\sum_{r=mid+1}^{R} A_{mid+1...r}^{k-i}
\end{aligned}
$$

边界条件是 $L=R$，此时答案为 $A_L^k$。

预处理 $C_i^k$ 即可。时间复杂度 $O(nk\log n\log k)$。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=400010,mod=998244353;

int n,k,arr[N],ans,C[15][15],L[15],R[15];// L,R 表示当前次数为 i 的贡献

typedef long long LL;

int quick_pow(int a,int p)
{
    if(p==0) return 1;
    int c=quick_pow(a,p>>1);
    c=(LL)c*c%mod;
    if(p&1) c=(LL)c*a%mod;
    return c;
}

void f(int l,int r)
{
    if(l==r)
    {
        ans=(ans+quick_pow(arr[l],k))%mod;
        return ;
    }
    int mid=(l+r)>>1;
    for(int i=0;i<=k;++i) L[i]=R[i]=0;
    //处理左边
    int sum=0;
    for(int i=mid;i>=l;--i)
    {
        sum=(sum+arr[i])%mod;
        for(int j=0;j<=k;++j)
        {
            L[j]=(L[j]+quick_pow(sum,j))%mod;
        }
    }
    //处理右边
    sum=0;
    for(int i=mid+1;i<=r;++i)
    {
        sum=(sum+arr[i])%mod;
        for(int j=0;j<=k;++j)
        {
            R[j]=(R[j]+quick_pow(sum,j))%mod;
        }
    }
    //合并
    for(int j=0;j<=k;++j)
    {
        ans=(ans+(LL)C[k][j]*L[j]%mod*R[k-j]%mod)%mod;
    }
    //分治
    f(l,mid);
    f(mid+1,r);
}

int main()
{
    cin>>n>>k;
    for(int i=0;i<=k;++i) C[i][0]=1;
    for(int i=1;i<=k;++i)
    {
        for(int j=1;j<=i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
        }
    }
    for(int i=1;i<=n;++i)
    {
        cin>>arr[i];
    }
    f(1,n);
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ran_qwq (赞：1)

先把它写成前缀和相减的 $k$ 次方形式：

$$\sum\limits_{l\le r}(s_r-s_{l-1})^k$$

二项式展开：

$$\sum\limits_{l\le r}\sum\limits_{i=0}^ks_r^i(-s_{l-1})^{k-i}\binom ki$$

先预处理组合数，从小到大枚举 $r$，同时维护 $s_r^i(-s_{l-1})^{k-i}$ 的和 $t_i$，再枚举 $i$ 暴算即可。

```cpp
#define il inline
const int MOD=998244353;
il int vmod(int x) {return x>=MOD?x-MOD:x;}
il int vadd(int x,int y) {return vmod(x+y);}
il int vsub(int x,int y) {return vmod(x-y+MOD);}
il int vmul(int x,int y) {return 1ll*x*y%MOD;}
int n,k,as,sm[11],c[11][11],s[N],ps[N][11],nps[N][11];
void QwQ() {
	n=rd(),k=rd();
	for(int i=0;i<=k;i++) {
		c[i][0]=1;
		for(int j=1;j<=k;j++) c[i][j]=vadd(c[i-1][j-1],c[i-1][j]);
	}
	for(int i=1;i<=n;i++) s[i]=vadd(s[i-1],rd());
	for(int i=0;i<=n;i++) {
		ps[i][0]=nps[i][0]=1;
		for(int j=1;j<=k;j++)
			ps[i][j]=vmul(ps[i][j-1],s[i]),
			nps[i][j]=vmul(nps[i][j-1],vsub(0,s[i]));
	}
	sm[0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=k;j++) cadd(as,vmul(vmul(ps[i][j],sm[k-j]),c[k][j]));
		for(int j=0;j<=k;j++) cadd(sm[j],nps[i][j]);
	}
	wr(as,"\n");
}
```

---

## 作者：AAA404 (赞：1)

简单题，但是细节比较多，有点难调。

记 $sum_i=\sum_{k=1}^i a_k$，$s_{i,k}=\sum_{j=1}^i sum_j^k$。

那么原式化为：

$$\sum_{l=0}^{n-1}\sum_{r=l+1}^{n} (sum_r-sum_l)^k\\

=\sum_{l=0}^{n-1}\sum_{r=l+1}^{n} \sum_{x=0}^k (-1)^xC_k^xsum_l^xsum_r^{k-x}$$

交换求和号：

$$\sum_{l=0}^{n-1} \sum_{x=0}^k \sum_{r=l+1}^{n}(-1)^xC_k^xsum_l^xsum_r^{k-x}\\

=\sum_{l=0}^{n-1} \sum_{x=0}^k (-1)^xC_k^xsum_l^x(s_{n,k-x}-s_{l,k-x})$$

然后组合数和 $s$ 可以预处理，直接扫一遍计算即可。

时间复杂度：$O(nk)$。

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc399_f)

## $\mathtt{Solution}$

简单题。

观察这个式子的形式，发现它可以用二项式定理拆开。

记 $s_i=\sum\limits_{j=1}^{i}a_i$，其中 $s_0=0$，那么原式可表示为：$ \displaystyle\sum_{1\leq\ l\leq\ r\leq\ n}(s_r-s_{l-1})^k $。

由于 $k$ 不超过 $10$，那么我们可以用二项式定理展开。

$$(s_r-s_{l-1})^k=\displaystyle\ \sum_{i=0}^{k}C_k^i\ s_r^i\ s_{l-1}^{k-i}\ (-1)^i$$

由于 $C_k^i\ s_r^i\ (-1)^i$ 可以提出来，那么只需要枚举 $r$，然后前缀和优化就可以了。

赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5, MOD = 998244353;
int n, k, ans, a[MAXN], s[MAXN], fac[MAXN], inv[MAXN], sum[MAXN];
int fpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1ll)res = res * a % MOD;
		a = a * a % MOD;
		b = b >>= 1ll;
	}
	return res;
}
int C(int x, int y){
	if(x < y)return 0;
	return fac[x] * inv[y] % MOD * inv[x - y] % MOD;
}
signed main(){
	n = read(), k = read();
	for(int i = 1;i <= n;i ++)a[i] = read(), s[i] = (s[i - 1] + a[i]) % MOD;
	fac[0] = 1;
	for(int i = 1;i <= 2e5;i ++)fac[i] = fac[i - 1] * i % MOD;
	inv[200000] = fpow(fac[200000], MOD - 2);
	for(int i = 2e5 - 1;i >= 0;i --)inv[i] = inv[i + 1] * (i + 1) % MOD;
	for(int i = 0;i <= n;i ++){
		for(int j = 0;j <= k;j ++){
			ans += C(k, j) * sum[j] % MOD * fpow(-1, j) % MOD * fpow(s[i], k - j) % MOD;
			ans %= MOD;
			ans += MOD;
			ans %= MOD;
			sum[j] += fpow(s[i], j), sum[j] %= MOD;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Dream_poetry (赞：1)

### 思路：

考虑 dp。

设 $f_{x,y}$ 表示 $ \displaystyle\ \sum_{1\leq\ l\leq\ r\leq\ x}\ \Bigg(\sum_{l\leq\ i\leq\ r}\ A_i\Bigg)^y $ 的结果。

初始时 $f_{1,y}$ 等于 $(A_1)^y$。

这个东西显然可以根据二项式定理做，所以我们先预处理出 $C_n^m$，每次处理前再预处理出 $(A_x)^i$。

在根据二项式定理，我们记 $cur_x$ 表示 $f_{x-1,y}$，则显然有 $f_{x,y}=(A_x)^y+\displaystyle\ \sum_{0\leq i \leq y} C_y^i \times cur_i \times (A_x)^{y-i}$。

然后我们就做完了。

但我不理解我为什么赛时没有写二维 dp 数组。

### 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int n,k; 
int a[2000005];
int C[11][11];
int cur[1000005];
int ans;
int p[2000005];
int tmp[2000005];

signed main(){
    cin>>n>>k;
    for (int i=1;i<=n;i++){
        cin>>a[i];
    }
    for (int i=0;i<=k;i++) {
        C[i][0]=1;
        if (i){
            C[i][i]=1;
            for (int j=1;j<i;j++) {
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
            }
        }
    }
    
    cur[0]=1;
    for (int i=1;i<=k;i++) {
        cur[i]=(cur[i-1]*a[1])%mod;
    }
    
	ans=cur[k];
    
	for (int i=2;i<=n;i++) {
        p[0]=1;
        for (int j=1;j<=k;j++){
            p[j]=(p[j-1]*a[i])%mod;
        }
        
        for (int j=0;j<=k;j++) {
            tmp[j]=p[j];
            for (int t=0;t<=j;t++) {
                int w=(C[j][t]*cur[t])%mod;
                w=(w*p[j-t])%mod;
                tmp[j]=(tmp[j]+w)%mod;
            }
        }
        
        for (int j=0;j<=k;j++){
        	cur[j]=tmp[j];
		}
		ans=(ans+cur[k])%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：light_searcher (赞：1)

### 题目大意

给定 $n,k$，再给定一个长度为 $n$ 的序列 $a$，求 $\sum \limits_{l=1}^n \sum \limits_{r=l}^n (\sum \limits_{i=l}^r i)^k$。

### 做法

令 $s_i = \sum \limits_{j=1}^i a_i$，那么原问题变为 $\sum \limits_{l=1}^n \sum \limits_{r=l}^n (s_r-s_{l-1})^k$。

根据二项式定理 $(x+y)^p = \sum \limits_{i=0}^p \binom{p}{i}x^iy^{p-i}$，得

$\sum \limits_{l=1}^n \sum \limits_{r=l}^n (s_r-s_{l-1})^k = \sum\limits_{l=1}^n \sum\limits_{r=l}^n \sum \limits_{i=0}^k \binom{k}{i} s_r^i (-s_{l-1})^{k-i}$。

根据和式的性质，改变求和顺序，可得

$\sum\limits_{l=1}^n \sum\limits_{r=l}^n \sum \limits_{i=0}^k \binom{k}{i} s_r^i(-s_{l-1})^{k-i} = \sum \limits_{i=0}^k \binom{k}{i}(-1)^{k-i} \sum \limits_{l=1}^n s_{l-1}^{k-i} \sum \limits _{r=l}^n s_r^i$。

然后你会发现这个式子已经很好算了。令 $sum_{k,i}= \sum \limits _{j=1}^i s_j^k$，得

$\sum \limits_{i=0}^k \binom{k}{i}(-1)^{k-i} \sum \limits_{l=1}^n s_{l-1}^{k-i} \sum \limits _{r=l}^n s_r^i = \sum \limits_{i=0}^k \binom{k}{i}(-1)^{k-i} \sum \limits_{l=1}^n s_{l-1}^{k-i} (sum_{i,n}-sum_{i,l-1})$。

预处理 $s,sum$ 和组合数，这样时间复杂度是 $\mathcal O(nk+k^2)$。

一个细节是 $-1$ 在模意义下可以直接用 $mod-1$ 代替，就可以省去防负数取模，然并卵。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,K=15,mod=998244353;
int n,k,a[N],s[N],p[N][K],sum[K][N],C[K][K],ans;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) s[i]=(s[i-1]+a[i])%mod;
	for(int i=0;i<=n;i++){
		p[i][0]=1;
		for(int j=1;j<=k;j++)
			p[i][j]=1ll*p[i][j-1]*s[i]%mod;
	}
	sum[0][0]=1;
	for(int i=0;i<=k;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]=(sum[i][j-1]+p[j][i])%mod;
	C[0][0]=1;
	for(int i=1;i<=k;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=0;i<=k;i++){
		int S=0;
		for(int j=1;j<=n;j++)
			S=(S+1ll*p[j-1][k-i]%mod*(sum[i][n]-sum[i][j-1])%mod+mod)%mod;
		ans=(ans+1ll*C[k][i]*((k-i)%2?mod-1:1)%mod*S)%mod;
	}
	printf("%d",ans);
	return 0;
}

---

## 作者：Redshift_Shine (赞：1)

## 背景

这是我第一次在赛时独立完成分治算法的实现。

并且，截至开始写稿，AtCoder 上出现的三篇日文题解与我的解法**全部不同**。

## 题解

根据简单数学知识可得

$$
(x+y)^k=\sum_{i=0}^k x^iy^{k-i}\binom{k}{i}
$$

由此，使用分治。

令答案为 $s$，初始为 $0$。

定义对区间 $[l,r]$ 的计算如下：
1. 若 $l=r$，则令 $s\leftarrow s+p_i^k$，结束计算过程。
2. 取中点值 $m=\lfloor\frac{l+r}{2}\rfloor$。
3. 对 $0\le i\le k$，计算 $p_i=\sum_{j=l}^{m}(\sum_{t=j}^m a_j)^i,q_i=\sum_{j=m+1}^{r}(\sum_{t=m+1}^j a_j)^i$。
4. 对 $0\le i\le k$，令 $s\leftarrow s+p_iq_{k-i}\binom{k}{i}$。
5. 对区间 $[l,m]$ 和 $[m+1,r]$ 分别进行如上运算。

对区间 $[1,n]$ 进行运算后 $s$ 模 $998244353$ 意义下的值即为答案。

上述方法可行的原因是，按照上述方法进行分治后，对任意的 $1\le i\le j\le n$，**必定存在恰好一个**被进行过运算的区间 $[l,r]$，满足 $l\le i\le \lfloor\frac{l+r}{2}\rfloor<j\le r$，**或** $i=j$。而在上述的分治过程中，$p$ 和 $q$ 的实际存在意义是对满足 $l\le i\le \lfloor\frac{l+r}{2}\rfloor<j\le r$ 的所有 $i,j$ 对进行捆绑计算，加快运算速度。

因此，上述计算方法正确。

上述代码的时间复杂度为 $O(nk\log n)$。并且，由于上述的解法在实际实现时容易使得内存访问连续，若在进行模加法时进行简单优化，其运行性能可以与频繁进行一般模运算的 $O(nk^2)$ DP 解法相近。

## 代码

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5 + 10, B = 20, mod = 998244353;
int n, m, p[B], res, a[N];
inline int adm(int x, int y)
{
	return (x + y >= mod ? x + y - mod : x + y);
}
void dvin(int l, int r)
{
	static int pl[B], pr[B];
	if (l == r)
	{
		int tmp = 1;
		for (int i = 1; i <= m; i++)
			tmp = 1ll * tmp * a[l] % mod;
		res = adm(res, tmp);
		return;
	}
	memset(pl, 0, (m + 1) << 2);
	memset(pr, 0, (m + 1) << 2);
	int mid = (l + r) >> 1;
	for (int i = mid, tmp = 0; i >= l; i--)
	{
		tmp = adm(tmp, a[i]);
		for (int j = 0, tmp2 = 1; j <= m; j++)
		{
			pl[j] = adm(pl[j], tmp2);
			tmp2 = 1ll * tmp2 * tmp % mod;
		}
	}
	for (int i = mid + 1, tmp = 0; i <= r; i++)
	{
		tmp = adm(tmp, a[i]);
		for (int j = 0, tmp2 = 1; j <= m; j++)
		{
			pr[j] = adm(pr[j], tmp2);
			tmp2 = 1ll * tmp2 * tmp % mod;
		}
	}
	for (int i = 0; i <= m; i++)
	{
		res = adm(res, 1ll * pl[i] * pr[m - i] % mod * p[i] % mod);
	}
	dvin(l, mid);
	dvin(mid + 1, r);
}
void run()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	p[0] = 1;
	for (int i = 1; i <= m; i++)
	{
		for (int j = i; j; j--)
			p[j] += p[j - 1];
	}
	dvin(1, n);
	printf("%d\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：DrAlfred (赞：1)

摘要：组合数学，二项式定理，扫描线

[传送门：https://www.luogu.com.cn/problem/AT_abc399_f](https://www.luogu.com.cn/problem/AT_abc399_f)

## 题意

给定正整数 $n, k$ 和一个长度为 $n$ 的数组 $a$，求 $S = \sum_{1 \le l \le r \le n} (\sum_{l \le i \le r} a_i)^k$。

## 分析思路

当 $k = 2$ 的时候，我们可以展开二项式定理，分别统计三项的结果。但 $k$ 很大时，如果直接对后面的式子进行展开，总共就会有 $\binom{n}{k}$ 项，无法进行统计。

那我们首先对 $k$ 次方内的区间求和做一个常见的优化——前缀和优化。记 $s_i = \sum_{j = 1}^i a_i$，特别地，$s_0 = 0$。于是我们有：

$$
\begin{aligned}
S &= \sum_{1 \le l \le r \le n} (\sum_{l \le i \le r} a_i)^k \\
&= \sum_{1 \le l \le r \le n} (s_r - s_{l - 1})^k
\end{aligned}
$$

求和的是一个二项式，进行展开：

$$
\begin{aligned}
S &= \sum_{1 \le l \le r \le n} (s_r - s_{l - 1})^k \\
&= \sum_{1 \le l \le r \le n} \sum_{i = 0}^k (-1)^{k - i} \binom{k}{i} s_r^i s_{l - 1}^{k - i}
\end{aligned}
$$

这样直接求时间复杂度是 $O(n^2k)$ 的，但是我们可以更换求和顺序，并且在枚举区间的时候使用扫描线序，即在扫 $l$ 或 $r$ 中的一个时快速统计出所有的另一个端点和它组成的区间对应的所有信息。

$$
\begin{aligned}
S &= \sum_{1 \le l \le r \le n} \sum_{i = 0}^k (-1)^{k - i}  \binom{k}{i} s_r^i s_{l - 1}^{k - i} \\
&= \sum_{1 \le r \le n} \sum_{i = 0}^k (-1)^{k - i} \binom{k}{i} s_r^i  \sum_{1 \le l \le r} s_{l - 1}^{k - i}
\end{aligned}
$$

而 $\sum_{1 \le l \le r} s_{l - 1}^{k - i}$ 是可以在扫描过程中算出的。特别对于拆前缀和要注意 $l = 1$ 时，$s_{l - 1} = s_0 = 0$ 对应的贡献。

时间复杂度 $O(nk)$，可以通过。

## 代码

```cpp
// 组合数的实现：https://alfredchester.github.io/cpp-templates/src/alfred/math/comb.hpp
#include "alfred/all"
#include "alfred/debug"
using namespace std;
const int N = 200010;
Comb<m998> comb;
m998 a[N], s[N], sum[11], ans; // sum[i]: s[0]^i + s[1]^i + ... + s[r - 1]^i
inline m998 sgn(int x) {
    return x & 1 ? -1 : 1;
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    int n, k;
    optimizeIO(), cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], s[i] = s[i - 1] + a[i];
    }
    sum[0] = 1; // 特别地，0^0 = 1，否则结果会错
    for (int i = 1; i <= n; i++) {
        m998 pw = 1;
        for (int j = 0; j <= k; j++) {
            ans += sgn(k - j) * comb.binom(k, j) * pw * sum[k - j];
            pw *= s[i];
        }
        pw = 1;
        for (int j = 0; j <= k; j++) {
            sum[j] += pw, pw *= s[i];
        }
    }
    cout << ans << '\n';
    return 0;
}

```

---

## 作者：jimmy0926 (赞：1)

## 题解：AT_abc399_f [ABC399F] Range Power Sum

### 算法思路

易得

$$
{ \begin{align}
\sum_{1 \le l \le r \le n} \left ( \sum_{i \in [l..r]} A_i \right )^K
& = \sum_{r \in [1..n] \wedge l \in [1..r]} \left ( \sum_{i \in [l..r]} A_i \right )^K \\
& = \sum_{r \in [1..n]} \sum_{l \in [1..r]} \left ( \sum_{i \in [l..r]} A_i \right )^K
\end{align} }
$$

。

令 $f(r, k) = \sum_{l \in [1..r]} \left ( \sum_{i \in [l..r]} A_i \right )^k$，则答案为 $\sum_{r \in [1..n]} f(r, K)$，有边界条件 $f(0, i) = 0$。

尝试得到状态转移方程。
$$
{ \begin{align}
f(r, k) = & = \sum_{l \in [1..r]} \left ( \sum_{i \in [l..r]} A_i \right )^k \\
& = A_r^k + \sum_{l \in [1..r)} \left ( \sum_{i \in [l..r]} A_i \right )^k \\
& = A_r^k + \sum_{l \in [1..r)} \left ( A_r + \sum_{i \in [l..r)} A_i \right )^k
\end{align} }
$$
由二项式定理，$(x + y)^n = \sum_{i = 0}^{n} {n \choose k} x^{n - i} y^i$，即
$$
{ \begin{align}
f(r, k)
& = A_r^k + \sum_{l \in [1..r)} \left ( A_r + \sum_{i \in [l..r)} A_i \right )^k \\
& = A_r^k + \sum_{l \in [1..r)} \sum_{j \in [0..k]} {k \choose j} \cdot A_r^{k - j} \cdot \left( \sum_{i \in [l..r)} A_i \right )^j \\
& = A_r^k + \sum_{j \in [0..k]} {k \choose j} \cdot A_r^{k - j} \cdot \sum_{l \in [1..r)} \left( \sum_{i \in [l..r)} A_i \right )^j \\
& = A_r^k + \sum_{j \in [0..k]} {k \choose j} \cdot A_r^{k - j} \cdot f(r - 1, j) \\
\end{align} }
$$
即状态转移方程为
$$
f(r, k) = A_r^k + \sum_{j \in [0..k]} {k \choose j} \cdot A_r^{k - j} \cdot f(r - 1, j)
$$
时间复杂度 $\Theta(NK^2)$​。

---

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
#define MOD 998244353
const int N = 2e5 + 10, K = 20;
int n, k, a[N], c[K][K], f[N][K];

int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", a + i);
	c[0][0] = 1;
	for (int i = 1; i <= k; ++i) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= k; ++j) {
			f[i][j] = qpow(a[i], j);
			for (int k = 0; k <= j; ++k)
				f[i][j] = (f[i][j] + c[j][k] * qpow(a[i], j - k) % MOD * f[i - 1][k] % MOD) % MOD;
		}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = (ans + f[i][k]) % MOD;
	printf("%lld\n", ans);
	return 0;
}
/*
AC 记录见 https://atcoder.jp/contests/abc399/submissions/64366377。
有什么问题可以评论哦，谢谢大家的支持~
*/
```

---

### 结语

本题解由 [这篇题解](https://atcoder.jp/contests/abc399/editorial/12582) 修改而成，附代码，~~记得抄袭~~。

完结不撒花 qwq~

---

## 作者：Chase12345 (赞：0)

洛谷的 RMJ 废了，所以我也没办法交。。。不过赛时也是成功完成了这道题。

原题：求所有子区间的 $k$ 次方的结果的和取模 $998244353$。$n \le 2 \times 10^5$。显然 $\mathcal{O(n^2)}$ 无法通过。考虑优化。但是不知道为什么 AT 给的题解是 $\mathcal{O(nk^2)}$，并不是最优的。我在赛后想了一下，是存在 $\mathcal{O(nk+k^2)}$ 的复杂度的程序的。

设
$$
S_i=\sum_{j=1}^i a_j
$$
则要求的变为：
$$
\sum_{l=1}^{n} \sum_{r=l}^{n} (S_r-S_{l-1})^k
$$
二项式定理展开之后，得到：
$$
\sum_{l=1}^{n} \sum_{r=l}^{n} \sum_{i=0}^{k} \binom{k}{i} (-1)^{k-i} S_r^i S_{l-1}^{k-i}=\sum_{i=0}^{k} \binom{k}{i} (-1)^{k-i} \sum_{l=1}^{n} S_{l-1}^{k-i} \sum_{r=l}^{n} S_r^i
$$
设
$$
s1_{k,i}=\sum_{j=i}^{n} S_j^{k}
$$
最终得出：
$$
\sum_{i=0}^{k} \binom{k}{i} (-1)^{k-i} \cdot \left(\sum_{l=1}^{n} S_{l-1}^{k-i} \cdot s1_{i,l} \right)
$$
预处理前缀和即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 998244353;
const int N = 2e5 + 5, K = 15;
long long a[N], s[N], s1[K][N], C[K][K];
 
void init() {
    C[0][0] = 1;
    for (int i = 1; i < K; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}
 
long long fpow(long long a, int b) {
    long long res = 1;
    for (; b; a = a * a % MOD, b >>= 1)
        if (b & 1)
			res = res * a % MOD;
    return res;
}
 
int main() {
    init();
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = (s[i - 1] + a[i]) % MOD;
    }
    for (int i = 0; i <= k; i++) {
        s1[i][n + 1] = 0;
        for (int j = n; j >= 1; j--)
            s1[i][j] = (fpow(s[j], i) + s1[i][j + 1]) % MOD;
    }
    long long ans = 0;
    for (int i = 0; i <= k; i++) {
        long long sum = 0;
        for (int j = 1; j <= n; j++)
            sum = (sum + fpow(s[j - 1], k - i) * s1[i][j]) % MOD;
        ans = (ans + (C[k][i] * fpow(-1, k - i) + MOD) % MOD * sum) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

记 $s_i=\displaystyle\sum_{j=1}^ia_j$，特别地，$s_0=0$。

记 $b_i=\displaystyle\sum_{j=i}^ns_j$。

使用二项式定理展开题中式子可得：

$$
\begin{aligned}
\sum_{1\le l\le r\le n}\left(\sum_{l\le i\le r}a_i\right)^k
&=\sum_{0\le l<r\le n}\left(s_r-s_l\right)^k\\
&=\sum_{0\le l<r\le n}\left(\sum_{t=0}^k\left(\dbinom t k\left(s_r^t+(-s_l)^{k-t}\right)\right)\right)\\
&=\sum_{0\le t\le k}\sum_{0\le l<n}\left(s_l^t\dbinom k t(-1)^t\left(\sum_{r=l+1}^n s_j^{k-t}\right)\right)
\end{aligned}
$$

由于 $k\le 10$，组合数可预处理。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int N=2e5+10;
int s[N][11],a[N],b[N][11],c[11],jc[11];
signed main()
{
	int n,k;
	cin>>n>>k;
	c[0]=1;
	jc[1]=1;
	for(int i=2;i<=k;i++) jc[i]=jc[i-1]*i;
	for(int i=1;i<=k;i++)
	{
		c[i]=jc[k];
		for(int j=1;j<=i;j++) c[i]/=j;
		for(int j=1;j<=k-i;j++) c[i]/=j;
	}
	for(int i=1;i<=n;i++) cin>>a[i],s[i][1]=s[i-1][1]+a[i],s[i][1]%=mod;
	for(int i=0;i<=n;i++)
	{
		s[i][0]=1;
		for(int j=2;j<=k;j++) s[i][j]=s[i][j-1]*s[i][1]%mod;
	}
	for(int i=n;~i;i--)
	{
		for(int j=0;j<=k;j++)
		b[i][j]=b[i+1][j]+s[i][j],b[i][j]%=mod;
	}
	int ans=0;
	for(int j=0;j<=k;j++)
	{
		for(int i=0;i<n;i++)
		ans=(ans+mod+s[i][j]*c[j]%mod*(j%2?-1:1)*b[i+1][k-j]%mod)%mod;
	}
	cout<<ans;
}

---

## 作者：haokee (赞：0)

访问 [Haokee Note](https://haokee-note.org/%E9%A2%98%E8%A7%A3/AtCoder/ABC399F+Range+Power+Sum) 以获得更好体验。

## 解法

首先观察到极大的 $N$ $(1\le N\le 2\times 10^5)$，这似乎让我们无从下手，但是不难发现 $K$ 极小 $(1\le K\le 10)$，这不禁让我们想到 $K$ 是一个关键的突破口。

考虑 dp。令 $dp_{i,j}$ 表示为以第 $i$ 个元素为结尾的所有区间的的和的 $k$ 次方之和，即

$$
dp_{i,j}=\sum_{k=1}^i\left(\sum_{l=k}^i a_l\right)^K
$$

每次加入一个元素 $a_i$ 时，假设之前的和为 $S$，我们可以利用二项式定理

$$
(a+b)^k=\sum\limits_{i=0}^k\binom{k}{i}a^i\cdot b^{k-i}
$$

展开 $(S+a_i)^k$，即

$$
(S+a_i)^k=\sum\limits_{m=0}^k\binom{k}{m}S^m\cdot a_i^{k-m}
$$

可以发现这个式子里面的 $\binom{k}{m}$ 和 $a_i^{k-m}$ 都是可以通过预处理提前计算得到，而 $S^m$ 就是 $dp_{(i-1,m)}$。通过这种方式，我们可以递推得到 dp 数组。最后 $\sum\limits_{i=1}^N dp_{i,k}$ 就是答案了。注意取模。

## 复杂度分析

### 时间复杂度

读入 $\mathcal O(N)$，预处理组合数 $\mathcal O(K^2)$，预处理 $a_i^k$ $\mathcal O(NK)$，dp 过程 $\mathcal O(NK^2)$，总时间复杂度 $\mathcal O(NK^2)$。本题下 $1\le N\le 2\times 10^5,1\le K\le 10$，因此运算量级大概是 $2\times 10^7$ 级别的，可以通过。如果不预处理 $a_i^k$ 的话，时间复杂度 $\mathcal O(NK^2\log_2 K)$。

### 空间复杂度

$A$ 数组存储 $\mathcal O(N)$，组合数数组 $\mathcal O(K^2)$，$a_i^k$ 数组 $\mathcal O(NK)$，dp 数组 $\mathcal O(NK)$，总空间复杂度 $\mathcal O(NK)$。如果不处理 $a_i^k$ 数组并对 dp 数组进行滚动数组优化的话空间复杂度为 $\mathcal O(N+K^2)$。

## 代码

采用滚动数组优化 dp。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const LL kMod = 998244353;

LL n, K, ans;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // 读入
  cin >> n >> K;
  vector<LL> a(n + 1);
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }

  // 预处理组合数
  vector<vector<LL>> C(K + 1, vector<LL>(K + 1));
  for (LL k = 0; k <= K; k++) {
    C[k][0] = 1;
    for (LL m = 1; m <= k; m++) {
      C[k][m] = (C[k - 1][m - 1] + C[k - 1][m]) % kMod;
    }
  }

  // 预处理 a[i]^k
  vector<vector<LL>> powA(n + 1, vector<LL>(K + 1));
  for (LL i = 1; i <= n; i++) {
    powA[i][0] = 1;
    LL x = a[i] % kMod;
    for (LL k = 1; k <= K; k++) {
      powA[i][k] = powA[i][k - 1] * x % kMod;
    }
  }

  // dp 过程及统计答案
  vector<LL> dp(K + 1);
  for (LL i = 1; i <= n; i++) {
    vector<LL> f(K + 1);
    for (LL k = 0; k <= K; k++) {
      for (LL m = 0; m <= k; m++) {
        LL trm = C[k][m] * powA[i][k - m] % kMod, prv = dp[m];
        if (m == 0) {  // 注意对零次方的特殊判断
          prv = (prv + 1) % kMod;
        }
        f[k] = (f[k] + trm * prv) % kMod;
      }
    }
    dp = f;
    ans = (ans + dp[K]) % kMod;
  }
  cout << ans << "\n";
  return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

场上写出 UB 没调出来，错失上分机会 /ll。

考虑做个前缀和，记前缀和为 $s$，原式变成 $\displaystyle \sum_{l,r}(s_r-s_{l-1})^k$。

考虑二项式定理，展开得到 $\displaystyle\sum_{l,r} \sum_{i=0}^{k}\binom k i (s_r)^{i}(-s_{l-1})^{k-i}$。$i$ 非常小，直接枚举 $i$，变成 $\displaystyle \sum_{i=0}^{k}\binom k i\sum_{l,r} (s_r)^{i}(-s_{l-1})^{k-i}$。

考虑枚举 $r$，改写为 $\displaystyle \sum_{i=0}^{k}\binom k i\sum_{r=1}^{n} (s_r)^{i} \sum_{l=1}^{r}(-s_{l-1})^{k-i}$，此时给 $(-s_{l-1})^{k-i}$ 再做个前缀和即可。

时间复杂度 $O(nk)$。注意各种潜在的下标 $<0$。

```cpp
const int N = 2e5 + 5, mod = 998244353;
int n, k, s[N], pw[N][19][2], suf[N][19], c[19][19];

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i <= k; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
    for (int i = 0; i <= n; i++) {
        if (i) cin >> s[i], (s[i] += s[i - 1]) %= mod;
        pw[i][0][0] = pw[i][0][1] = 1;
        for (int j = 1; j <= k; j++) {
            pw[i][j][0] = pw[i][j - 1][0] * s[i] % mod;
            pw[i][j][1] = (pw[i][j - 1][1] * (-s[i] + mod) % mod + mod) % mod;
        }
    }
    for (int j = 0; j <= k; j++) {
        suf[0][j] = pw[0][j][1];
        for (int i = 1; i <= n; i++) suf[i][j] = (suf[i - 1][j] + pw[i][j][1]) % mod;
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) {
        int now = 0;
        for (int r = 1; r <= n; r++) (now += pw[r][i][0] * suf[r - 1][k - i] % mod) %= mod;
        (ans += c[k][i] * now % mod) %= mod;
    } cout << (ans % mod + mod) % mod;
    return 0;
}
```

---

## 作者：SegmentTree_ (赞：0)

$k$ 的范围很小，可以考虑从前往后扫，扫到 $i$ 时维护 $i$ 前面每个位置的后缀和，问题就转化成了区间加、区间求 $k$ 次方和，可以用线段树维护。  
对于线段树的每个节点，记录它对应的区间中所有数的 $0$ 到 $k$ 次方的和及懒标记，设为 $sum$ 和 $laz$。`pushdown` 的时候，由二项式定理可以得到 $sum_n=\sum\limits_{j=0}^{n}\binom{n}{j}sum_jlaz^{n-j}$，注意等式左边的 $sum$ 是更新后的，等式右边的 $sum$ 是更新前的，需要从 $k$ 到 $0$ 更新。  
[code](https://atcoder.jp/contests/abc399/submissions/64343279)

---

## 作者：postpone (赞：0)

[二项式定理](https://zh.wikipedia.org/wiki/%E4%BA%8C%E9%A1%B9%E5%BC%8F%E5%AE%9A%E7%90%86) 的应用。

转化一下，设前缀和 $s_j$ 表示 $\sum_{i=1}^j a_i$，那么题目要我们求的就是
$$
\begin{align*}
\sum_{1\leq l\leq r\leq n}\left(\sum_{l\leq i\leq r} a_i\right)^k &= \sum_{1\leq l\leq r\leq n}\left(s_r - s_{l-1}\right)^k \\
&=\sum_{1\leq l\leq r\leq n}\sum_{m=0}^k\tbinom{k}{m}s_r^{k-m}(-s_{l-1})^{m}\\
&=\sum_{r=1}^{n}\sum_{m=0}^k \text{coef} \sum_{l=1}^r(-s_{l-1})^{m}
\end{align*}
$$

其中，$\text{coef}=(-1)^m\times\binom km\times s_r^{k-m}$；而最后 $l$ 相关的求和，是可以预处理的——将每一幂次的 $s$ 再求一个前缀和。

这道题就做出来了，复杂度 $O(nk)$。

```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // s[m][r] 表示前缀和的 m 次方
    vector s(k + 1, vector<Z>(n + 1));
    fill(s[0].begin(), s[0].end(), 1);
    for (int i = 0; i < n; i++) {
        s[1][i + 1] = s[1][i] + a[i];
    }
    for (int m = 2; m <= k; m++) {
        for (int i = 1; i <= n; i++) {
            s[m][i] = s[m - 1][i] * s[1][i];
        }
    }

    // pres[m][r] 表示前缀和的 m 次方的前缀和
    vector pres(s);
    for (int m = 0; m <= k; m++) {
        for (int i = 1; i <= n; i++) {
            pres[m][i] += pres[m][i - 1];
        }
    }

    Z ans = 0;
    for (int r = 1; r <= n; r++) {
        for (int i = 0; i <= k; i++) {
            Z coef = comb.binom(k, i);
            if (i % 2 == 1) {
                coef = -coef;
            }
            coef *= s[k - i][r];
            ans += coef * pres[i][r - 1];
        }
    }
    cout << ans << "\n";

    return 0;
}
```

[完整代码](https://atcoder.jp/contests/abc399/submissions/64342703)

---

## 作者：Tairitempest (赞：0)

## [ABC399F] Range Power Sum

对于每个区间计算必定超时。考虑利用前缀思想和二项式定理计算贡献。

考虑 $sum_{i,j}$ 表示以第 $i$ 个元素结尾的所有子区间的和的 $j$ 次方的总和。对于所有末尾位置为 $i$ 的区间，可以拆成两个部分：前面的区间数字总和 $s$ 和 $A_i$。那么，我们对于一个区间，其贡献为：

$$
(s+A_i)^k
$$

展开得：

$$
C^0_ks^k+C^1_ks^{k-1}A_i+......+C^{k-1}_ksA_i^{k-1}+C^k_kA_i^k
$$

我们维护了 $sum_{i,j}$，因此所有的 $s$ 都可以合并并使用 $sum_{i,j}$ 来计算。

因此有：

$$
sum_{i,j}=C^0_ksum_{i-1,j}^j+C^1_jsum_{i-1,j-1}A_i+......+C^{j-1}_jsum_{i-1,1}A_i^{j-1}+C^j_jA_i^j
$$

将所有的 $sum_{i,k}$ 累加即可得到答案。时间复杂度 $O(NK^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 998244353
ll n,k,a[200010][13],ans,sum[200010][13],xs[13][13];
int main(){
    cin>>n>>k;
    xs[0][0]=1;
    for(int i=1;i<=k;i++)
        for(int j=i;j>=0;j--)
            xs[i][j]=xs[i-1][j-1]+xs[i-1][j];
    for(int i=1;i<=n;i++){
        a[i][0]=1;
        cin>>a[i][1];
        for(int j=2;j<=k;j++)
            a[i][j]=(a[i][j-1]*a[i][1])%mod;
    }
    sum[0][0]=1;
    for(int i=1;i<=n;i++){
        sum[i][0]=1;
        for(int j=k;j>=0;j--)
            for(int p=j;p>=0;p--)
                sum[i][j]=(sum[i][j]+sum[i-1][p]*a[i][j-p]%mod*xs[j][p])%mod;
        ans=(ans+sum[i][k])%mod;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：coding_goat (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/CodingGoat/p/18800213)

我们看回题目所给的式子（$s_i$ 表示 $\sum_{j=1}^{i} a_j$）：

$$\sum_{l=1}^{n} \sum_{r=l}^{n} (s_r+(-s_{l-1}))^k$$

根据二项式定理：$(a+b)^k=\sum_{i=0}^{k}C_{k}^{i}a^{k-i}b^{i}$，我们可以把上面的式子换成这样：

$$\sum_{l=1}^{n}\sum_{r=l}^{n}\sum_{i=0}^{k}C_{k}^{i}{s_r}^{k-i}{(-s_{l-1})^{i}}$$

我们发现 $\sum_{i=0}^{k}C_{k}^{i}{s_r}^{k-i}{(-s_{l-1})^{i}}$ 中，$C_{k}^{i}{(-s_{l-1})^{i}}$ 并不受 $r$ 取值的影响，所以我们可以把它提出来，变成下面这个样子：

$$\sum_{l=1}^{n}\sum_{i=0}^{k}C_{k}^{i}(-s_{l-1})^i\sum_{r=l}^{n}{s_r}^{k-i}$$

最后，我们发现我们可以预处理出来 $\sum_{r=l}^{n}{s_r}^{k-i}$，那么就很好做了。时间复杂度 $O(nk\log V)$，其中 $V$ 是 $a_i$ 值域。


```cpp
#include<bits/stdc++.h>

#define int ll
#define pii pair<int,int> 
#define pll pair<long long,long long> 
#define ll long long
#define i128 __int128

#define mem(a,b) memset((a),(b),sizeof(a))
#define m0(a) memset((a),0,sizeof(a))
#define m1(a) memset(a,-1,sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
#define For(a,b,c) for(int a=(b);a<=(c);a++)
#define Rep(a,b,c) for(int a=(b);a>=(c);a--)
#define in1(a) a=read()
#define in2(a,b) a=read(), b=read()
#define in3(a,b,c) a=read(), b=read(), c=read()
#define in4(a,b,c,d) a=read(), b=read(), c=read(), d=read()
#define fst first 
#define scd second 
#define dbg puts("IAKIOI")

using namespace std;

int read() {
	int x=0,f=1; char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-'?-1:1); 
	for(;c<='9'&&c>='0';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
void write(int x) { if(x>=10) write(x/10); putchar('0'+x%10); }

const int mod = 998244353;
int qpo(int a,int b) {int res=1; a=(a%mod+mod)%mod; for(;b;b>>=1,a=(a*a)%mod) if(b&1) res=res*a%mod; return res; }
int inv(int a) {return qpo(a,mod-2); }

#define maxn 200050

int n,k,a[maxn],s[maxn];
int sum[12][maxn];
int fac[maxn],ifac[maxn];
int C(int n,int m) {//n 选 m
	return fac[n]*ifac[n-m]%mod*ifac[m]%mod;
}

void work() {
	in2(n,k);
	fac[0]=1; ifac[0]=inv(fac[0]);
	For(i,1,k) fac[i]=fac[i-1]*i,ifac[i]=inv(fac[i]);
	For(i,1,n) in1(a[i]),s[i]=(s[i-1]+a[i])%mod;
	For(i,0,k) Rep(j,n,1) sum[i][j]=(sum[i][j+1]+qpo(s[j],i))%mod;
//	For(j,0,k) For(i,1,n) cout<<sum[j][i]<<(i==n?'\n':' ');
	int ans=0;
	For(i,1,n) {
		int res=0;
		For(j,0,k) {
			res+=qpo(-s[i-1],j)%mod*C(k,j)%mod*sum[k-j][i]%mod;
			res=(res%mod+mod)%mod;
		}
		ans+=res;
		ans=(ans%mod+mod)%mod;
	}
	cout<<ans<<'\n';
}

signed main() {
//	freopen("data.in","r",stdin);
//	freopen("myans.out","w",stdout);
//	ios::sync_with_stdio(false); 
//	cin.tie(0); cout.tie(0);
	double stt=clock();
	int _=1;
//	_=read();
//	cin>>_;
	For(i,1,_) {
		work();
	}
	cerr<<"\nTotal Time is:"<<(clock()-stt)*1.0/1000<<" second(s)."<<'\n';
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc399_f 题解

## 思路

首先，$\sum\limits_{l \le i \le r} A_i$ 这个东西显然可以用前缀和 $\mathcal{O}(1)$ 做掉，记前缀和数组为 $p$，于是可以将原式转换成 $\sum\limits_{0 \le l < r \le N}(p_r-p_l)^K$，不难发现，$(p_r-p_l)^K$ 这个东西本质上就是 $(a+b)^K$，将其二项式展开即可，对于 $0 \le i \le K$ 的每一个 $i$，$a^ib^{K-i}$ 的系数是 $C_K^i$，这个前置知识点自行参考其他文献，这里不做证明和讲解。

于是，从左到右枚举每一个 $r$，对于每一个 $p_r^i(-p_l)^{K-i}$，发现 $p_l^{k-i}$ 也可以求前缀和，在统计的时候加上正负性判断即可。 

时间复杂度 $\mathcal{O}(NK^2)$，代码里求幂如果优化一下，可以做到 $\mathcal{O}(NK)$。

## 代码

```cpp
#define int long long

const int N=200005;
const int M=11;
const int mod=998244353;

int n,k;
int a[N];
int p[N];
int fac[M];
int c[M];
int s[M];

void init() {
    fac[0]=1;
    _rep(i,1,M-1) fac[i]=fac[i-1]*i;
}

int C(int a,int b) {
    return fac[a]/fac[b]/fac[a-b];
}

int ksm(int a,int b) {
    int ans=1;
    _rep(i,1,b) ans=(ans*a)%mod;
    return ans;
}

i32 main() {
    init();
    read(n),read(k);
    _rep(i,1,n) read(a[i]);
    _rep(i,1,n) p[i]=(p[i-1]+a[i])%mod;
    _rep(i,0,k) c[i]=C(k,i);
    // printf("test: "); _rep(i,0,k) writesp(c[i]); putchar(10);
    int ans=0;
    s[0]=1;
    _rep(r,1,n) {
        int i=k,j=0;
        while (i>=0) {
            int sign;
            if (i&1) sign=-1;
            else sign=1;
            ans=(ans+(s[i]*sign*c[i]%mod)*ksm(p[r],j)%mod)%mod;
            i--,j++;
        }
        _rep(i,0,k) s[i]=(s[i]+ksm(p[r],i))%mod;
    }
    ans=(ans%mod+mod)%mod;
    write(ans);
    return 0;
}
```

---

## 作者：_Passerby_ (赞：0)

来一个无脑做法。

先做个前缀和，题目转化为求：

$$
\sum_{1\leq l \leq r \leq N} {(s_r - s_{l - 1})} ^ K
$$

直接二项式定理展开，原式变为：

$$
\sum_{1\leq l \leq r \leq N} \sum_{i=0}^K {(-1)}^i {K \choose i} s_{l - 1} ^ i s_r^{K - i}
$$

变换枚举顺序，原式变为：

$$
\sum_{i=0}^K \sum_{1\leq l \leq r \leq N} {(-1)}^i  {K \choose i} s_{l - 1} ^ i s_r^{K - i}
$$

后面变换为先枚举 $l$，原式变为：

$$
\sum_{i=0}^K \sum_{1 \leq l \leq N} \sum_{l \leq r \leq N} {(-1)}^i  {K \choose i} s_{l - 1} ^ i s_r^{K - i}
$$

提取公因式，原式变为：

$$
\sum_{i=0}^K {(-1)}^i  {K \choose i} \sum_{1 \leq l \leq N} s_{l - 1} ^ i  \sum_{l \leq r \leq N}  s_r^{K - i}
$$

最内层 $\sum$ 的计算可使用后缀和优化，前面直接计算即可。

总时间复杂度 $O(N K^2)$，我写了个快速幂，时间复杂度是 $O(N K \log K)$，不过差别不大。

[代码](https://atcoder.jp/contests/abc399/submissions/64318999)。

---

