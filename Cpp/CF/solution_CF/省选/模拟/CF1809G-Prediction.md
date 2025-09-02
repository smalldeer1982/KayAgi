# Prediction

## 题目描述

Consider a tournament with $ n $ participants. The rating of the $ i $ -th participant is $ a_i $ .

The tournament will be organized as follows. First of all, organizers will assign each participant an index from $ 1 $ to $ n $ . All indices will be unique. Let $ p_i $ be the participant who gets the index $ i $ .

Then, $ n-1 $ games will be held. In the first game, participants $ p_1 $ and $ p_2 $ will play. In the second game, the winner of the first game will play against $ p_3 $ . In the third game, the winner of the second game will play against $ p_4 $ , and so on — in the last game, the winner of the $ (n-2) $ -th game will play against $ p_n $ .

Monocarp wants to predict the results of all $ n-1 $ games (of course, he will do the prediction only after the indices of the participants are assigned). He knows for sure that, when two participants with ratings $ x $ and $ y $ play, and $ |x - y| > k $ , the participant with the higher rating wins. But if $ |x - y| \le k $ , any of the two participants may win.

Among all $ n! $ ways to assign the indices to participants, calculate the number of ways to do this so that Monocarp can predict the results of all $ n-1 $ games. Since the answer can be large, print it modulo $ 998244353 $ .

## 说明/提示

In the first example, a match with any pair of players can be predicted by Monocarp, so all $ 24 $ ways to assign indices should be counted.

In the second example, suitable ways are $ [1, 3, 2] $ , $ [2, 3, 1] $ , $ [3, 1, 2 $ \] and $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
4 3
7 12 17 21```

### 输出

```
24```

## 样例 #2

### 输入

```
3 7
4 9 28```

### 输出

```
4```

## 样例 #3

### 输入

```
4 1
1 2 3 4```

### 输出

```
0```

## 样例 #4

### 输入

```
4 1
1 2 2 4```

### 输出

```
12```

## 样例 #5

### 输入

```
16 30
8 12 15 27 39 44 49 50 51 53 58 58 59 67 68 100```

### 输出

```
527461297```

# 题解

## 作者：Alex_Wei (赞：6)

[CF1809G Prediction](https://www.luogu.com.cn/problem/CF1809G)

考虑符合要求的 $a$ 的排列 $b$，两个选手比赛时评级较高的选手胜出。因此，题目中的条件等价于：对任意 $2\leq i\leq n$，$|b_i - \max_{j < i} b_j| > k$。

因为 $a_n$ 和 $a_{n - 1}$ 一定会比赛，所以当 $a_{n - 1} + k \geq a_n$ 时，无解，答案为 $0$。

设 $l_i$ 表示最大的 $j$ 使得 $a_j + k < a_i$，$r_i$ 表示最小的 $j$ 使得 $a_i + k < a_j$。

考虑钦定前缀最大值的位置 $q_1, q_2, \cdots, q_c$ 计算对应排列方案数。对于 $a_{q_i}$，位置大于 $l_{q_i}$ 的 $a$ 必须放在 $a_{q_{i + 1}}$ 之后。从限制强到限制弱依次插入每个元素。

- 对于 $q_c$，将 $l_{q_c} + 1\sim n$ 不含 $q_c$ 的所有位置放在 $q_c$ 之后，方案数为 $(n - l_{q_c} - 1) !$。
- 从 $c - 1$ 到 $1$ 枚举 $i$，注意到 $q_i \leq l_{q_{i + 1}}$（否则不合法），所以相当于将 $l_{q_i} + 1\sim l_{q_{i + 1}}$ 不含 $q_i$ 的所有位置 $S$ 放在 $q_{i + 1}$ 之后，此时 $l_{q_{i + 1}} + 1\sim n$ 不含 $q_i$ 的所有位置已经在 $q_{i + 1}$ 之后。因此，考虑每个位置插在哪个元素后面，方案数为 $n - l_{q_{i + 1}}\sim n - l_{q_i} - 2$ 的积。
- 最后将 $1\sim l_{q_1}$ 放在 $q_1$ 之后，方案数为 $n - l_{q_1}\sim n - 1$ 的积。
- 整理，得方案数 $(n - 1)! \prod_{i = 1} ^ {c - 1} (n - l_{q_i} - 1) ^ {-1}$。

设 $f_i$ 表示 $q_1 = i$ 的方案数之和，从后往前转移，前缀和优化即可。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1809/submission/199356704)。

---

## 作者：空气树 (赞：4)

小清新计数题。

分析合法序列的构成，可以发现其是由若干段序列组成，每段第一个元素的值大于其余元素最大值加 $k$。并且相邻两段的第一个元素 $u,v$，满足 $u+k<v$（$u$ 在 $v$ 前）。

那么这就直接考虑从大到小 DP。设 $f_i$ 表示考虑从 $n$ 到 $i$ 形成合法序列的方案数。可以预先 $O(n)$ 处理出 $L_i$ 和 $R_i$，表示最左和最右的满足与 $a_i$ 差的绝对值不大于 $k$ 的位置。

那么转移分为两种。一种是 $i$ 插入到之前段的某个位置；一种是 $i$ 成为一段段头。

如果直接考虑第一种情况，会比较难处理。那么可以先考虑第二种情况的影响。发现就是 $L_i$ 到 $i-1$ 的元素，会少 $1$ 个位置可以插。因为由于段头与段头差的约束，使得一个元素不可以插的段只有上一段，且该段只有一个元素。这样可以算得比原来 $i$ 不单独成段的贡献多了个 $\frac{1}{n-L_i}$的系数。（原先，对于 $x$（$L_i\le x\le i$），有 $n-x$ 个位置可以插，$i$ 单独成段后，变成 $n-x-1$ 个位置可插，且 $i$ 只有一种插法了）。

这样，就可以对 $f$ 稍微做个调整。变为带系数的值。第一种情况就直接将 $f_{i+1}$ 贡献给 $f_i$ 即可。第二种情况则变为将 $\frac{1}{n-L_i}f_{R_i+1}$ 贡献给 $f_i$。最后再整体乘上 $(n-1)!$ 即可。

上面的调整实际可以理解为选择 DP（指系数上）和前缀和思想。


---

## 作者：Leasier (赞：4)

Update on 2023.9.29：感谢 [wublabdubdub_s](https://www.luogu.com.cn/user/358781)。

首先考虑转化题目条件，可得：

- 求有多少个长为 $n$ 的排列 $p$，满足 $\forall 2 \leq i \leq n$，有 $|\displaystyle\max_{j = 1}^{i - 1} a_{p_j} - a_{p_i}| > k$。

注意到我们在新填入一个元素时只关心已填元素的 $\max$，然后我们就有一个 $O(2^n n)$ 的状压 dp 做法了，但显然不能通过。

接下来进行一些观察，可以发现：

- 在任意一个合法的 $p$ 中，删除 $a_{p_i}$ 最小的 $p_i$，新的 $p'$ 仍然合法。

证明是显然的。

于是可以考虑从大到小填所有元素，考虑 dp，设 $dp_i$ 表示填完 $(i, n]$ 的方案数。

初值：$dp_n = 1$。

转移：考虑 $a_i$ 填在哪里，具体而言分为两类：

- 不填在当前的第一个位置：此时不影响后面元素的前缀 $\max$，则 $dp_{i - 1} \leftarrow dp_{i - 1} + dp_i (n - i)$。
- 填在当前的第一个位置：设 $lst_i$ 表示最大的 $j$ 使得 $a_i - a_j > k$（这里钦定 $a_0 = -\infty$），则此时 $(lst_i, i)$ 都不能出现在 $i$ 之后，则这 $i - lst_i - 1$ 个数需要填入第二个位置之共 $n - lst_i - 2$ 个可选位置，则 $dp_{lst_i} \leftarrow dp_{lst_i} + dp_i A_{n - lst_i - 2}^{i - lst_i - 1}$。

答案：$dp_0$。

双指针求出 $lst_i$ 即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
int a[1000007], lst[1000007];
ll fac[1000007], inv_fac[1000007], dp[1000007];

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
	for (int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline ll arrange(int n, int m){
	if (m == 0) return 1;
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[n - m] % mod;
}

int main(){
	int n = read(), k = read();
	init(n);
	for (int i = 1; i <= n; i++){
		a[i] = read();
	}
	for (int i = 1; i <= n; i++){
		lst[i] = lst[i - 1];
		while (a[i] - a[lst[i] + 1] > k) lst[i]++;
	}
	dp[n] = 1;
	for (int i = n; i >= 1; i--){
		dp[i - 1] = (dp[i - 1] + dp[i] * (n - i) % mod) % mod;
		dp[lst[i]] = (dp[lst[i]] + dp[i] * arrange(n - lst[i] - 2, i - lst[i] - 1) % mod) % mod;
	}
	printf("%lld", dp[0]);
	return 0;
}
```

---

## 作者：NATO (赞：3)

伟大的原题。

~~一句话题解：同 [CF1437F](https://www.luogu.com.cn/problem/CF1437F)，改一下一个数前面可以放的数的定义就好了。~~

### 思路：

容易转化题意为 $\forall i,|a_{p_i}-\max\limits_{j=1}^{i-1}a_{p_j}|>k$ （显然，第 $i$ 个人必然是和前面最大战力打，所以只要前面的最大战力和第 $i$ 个人满足条件就可以了）。

那么考虑先将战力从小到大排序，下文位置均指排序后的位置。

无解的情况显然是最大战力与次大战力差不超过 $k$，否则最大战力放最前面，必然有解。

我们考虑对于一个数 $a_i$，显然只有所有 $<a_i-k$ 的数可以放在它前面，排序后即是一前缀。

那么设 $dp_i$ 表示放了 $a_i$ 和 $<a_i-k$ 的所有数的合法方案数，设最大的满足 $<a_i-k$ 的数位置为 $k$，易得转移如下：

$dp_i=\sum\limits_{j=1}^{k}dp_j\times A_{n-j-1}^{k-j}$

意义即枚举 $a_i$ 放在哪个数后面，再将剩余数随意安排到剩余位置（因为有 $a_i$ 的存在，剩余数放哪里都必然是合法的）。求和即为当前合法方案数。

然鹅单个转移 $O(n)$，总复杂度 $O(n^2)$，考虑优化。

考虑拆开排列数：

$dp_i=\frac{\sum\limits_{j=1}^{k}dp_j\times(n-j-1)!}{(n-k-1)!}$

发现上面的乘法只和 $j$ 有关，而 $k$ 因 $i$ 而定，前缀和预处理上面，乘上下面的逆元即可优化至 $O(n)$。

#### 参考代码：

```cpp
// LUOGU_RID: 150829143
#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
using namespace std;
ll mul(ll x)
{
	return (x>=MOD?x-MOD:x);
}
ll n,k;
ll dp[1000005];
ll a[1000005],sum[1000005];
ll inv[1000005],f[1000005];
ll pre[1000005];
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	f[0]=1;
	for(ll i=1;i<=n;++i)cin>>a[i],f[i]=f[i-1]*i%MOD;
	inv[n]=qpow(f[n],MOD-2);
	for(ll i=n-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%MOD;
	sort(a+1,a+1+n);
	if(a[n-1]+k>=a[n])
	{
		cout<<0;return 0;
	}
	for(ll i=1;i<=n;++i)sum[i]=lower_bound(a+1,a+i,a[i]-k)-a;
	dp[0]=1;pre[0]=f[n-1];
	for(ll i=1;i<=n;++i)
	{
		dp[i]=pre[sum[i]-1]*inv[n-sum[i]]%MOD;
		pre[i]=(pre[i-1]+dp[i]*f[n-sum[i]-1]%MOD)%MOD;
	}
	cout<<dp[n];
}
```

---

## 作者：daniEl_lElE (赞：0)

不难发现比赛一定是设初始胜者为 $t$，$t$ 吊打一些人后（即 $a_x<a_t-k$）被某个人吊打（即 $a_t<a_x-k$），然后依次类推。

设 $p_i$ 表示第一个大于等于 $a_i-k$ 的位置。

考虑 $dp_i$ 表示目前胜者为 $i$ 的方案数。

考虑 $p_i\sim i-1$ 中的人，显然这些人应该放在 $i$ 之后。注意到我们已经确定了 $p_i$ 个人的相对位置（即，前 $p_{i-1}$ 个人和 $i$），于是 $i\to j$ 的转移就是 $dp_i\times\binom{n-p_i-1}{p_j-p_i-1}\times(p_i-p_j-1)!\to dp_j$。化简可以得到 $dp_i\times\frac{(n-p_i-1)!}{(n-p_j)!}\to dp_j$。维护 $dp_i\times(n-p_i-1)!$ 的前缀和，设为 $pre_i$，则 $dp_i=pre_{p_i-1}\times\frac{1}{(n-p_j)!}$。

总复杂度 $O(n\log n)$ 或 $O(n)$（如果你愿意使用双指针求 $p_i$ 的话）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define s(i,j) ((i-1)*m+j)
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
const int mod=998244353;
int a[1000005],p[1000005],fac[1000005],inv[1000005];
int dp[1000005],pre[1000005];
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
void init(){
	fac[0]=1; for(int i=1;i<=1000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[1000000]=qp(fac[1000000],mod-2); for(int i=999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	init();
	int n,k; cin>>n>>k; for(int i=1;i<=n;i++) cin>>a[i];
	if(a[n]-a[n-1]<=k){
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++) p[i]=lower_bound(a+1,a+n+1,a[i]-k)-a;
	dp[0]=1,pre[0]=fac[n-1];
	for(int i=1;i<=n;i++){
		(dp[i]+=pre[p[i]-1]*inv[n-p[i]])%=mod;
		pre[i]=(pre[i-1]+dp[i]*fac[n-p[i]-1])%mod;
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

有趣的题目。

注意到在合法状态下，第 $i$ 轮的擂主一定是 $a_{p_1}$，$a_{p_2}$，$\dots$，$a_{p_i}$ 中最大的那个对应的 $p$。

因此题目要求：$|a_{p_j}- \max_{i=1}^{j-1} a_{p_i}| > k$。

考虑一个数，他前面的数要么全部 $< a_i - k$，要么存在 $> a_i + k$ 的项。我们不妨考虑前者，因为这样就相当于钦定了前缀 $\rm max$。

于是设只考虑 $< a_i - k$ 的项和 $a_i$，让他们填好了 $n$ 个位置中的部分的方案数为 $dp_i$。

假设有 $t_i$ 个数满足 $< a_i-k$。如果在 $j$ 处转移（$j \le t_i$）那么应当在 $dp_j$ 的基础上略加修改。（我们实际上在枚举 $i$ 的上一个擂主是谁。）

怎么修改呢？一方面，$a_i$ 只能放在当前第一个空位上。略加分析知道，第一个空位不能放任何其他的数。另一方面，而且如果所有被枚举到的数都采取“放在第一个空位上”的策略，这个位置必定满足上一个擂主是 $j$。

考虑 $j$ 时只放了 $1+t_j$ 个数，那么为了达成目标还要再放 $t_i-1-t_j$ 个数，而最开始有 $n-t_j-2$ 个空位，因此要乘上 $\dfrac{(n-t_j-2)!}{(n-t_i-1)!}$。

即 $dp_i = \dfrac{(n-1)!}{(n-t_i-1)!} + \sum_{j=1}^{t_i} dp_j \dfrac{(n-t_j-2)!}{(n-t_i-1)!}$。使用前缀和优化即可。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=998244353;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int n,k,dp[MAXN],frac[MAXN],inv[MAXN],pre[MAXN],a[MAXN],len[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k; frac[0]=1; ffor(i,1,n) frac[i]=frac[i-1]*i%MOD; inv[n]=qpow(frac[n],MOD-2); roff(i,n-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,1,n) cin>>a[i];
	if(a[n]-a[n-1]<=k) return cout<<0,0;
	ffor(i,1,n) len[i]=lower_bound(a+1,a+n+1,a[i]-k)-a-1;
	pre[0]=frac[n-1],dp[0]=1;
	ffor(i,1,n) dp[i]=pre[len[i]]*inv[n-len[i]-1]%MOD,pre[i]=(pre[i-1]+dp[i]*frac[n-len[i]-2])%MOD;	
	cout<<dp[n];
	return 0;
}
```

---

## 作者：ningago (赞：0)

题目要求任意一次比赛都有唯一胜者，也就是说 $\forall i,\ |a_{p_i}-\max_{j\leq i} a_{p_j} |>K$。

考虑从小到大依次加入 $p_i$ 的过程。

对于每一个点 $i$，存在 $L_i,R_i$ 表示当前的 $\max_{j\leq i} a_{p_j}$ 的取值为 $a_i$ 时，下一步不能取区间 $x\in [L_i,R_i]$ 内的 $a_x$（$L_i\leq i\leq R_i$）。不难用双指针算法求出 $L_i,R_i$。

一个简单的性质：如果 $R_i<j$，那么一定有 $i<L_j$。

定义**关键点**为插入 $p_i$ 后，改变 $\max$ 的 $p_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/2af157l5.png)

假设图中 $x,y$ 是第一、二个关键点。那么有性质：

- 插入 $x/y$ 后，绿色/蓝色部分就会成为非关键点。这些点可以在之后任意选取。蓝色部分的具体长度为 $L_y-L_x-1$，绿色部分为 $L_x-1(L_0=0)$。
- 下一个关键点 $z$ 必须 $>R_y$。
- 插入 $y$ 后，剩下的没有确定的长度为 $n-L_y$。$x$ 同理。
  - 插入 $n$ 这个关键点后，必须所有点都被确定了，所以**有解的一个必要条件为 $n-L_n=0$**。

于是可以设计 DP，令 $f_i$ 表示若 $i$ 为关键点，且考虑了 $[1,i]$ 的关键点，的方案数。转移：

$$f_i\gets [0\leq j<L_i]\cdot f_j\cdot (L_i-L_j-1)!\cdot \dbinom{(n-L_i)+(L_i-L_j-1)}{n-L_i}$$

把组合数拆开为阶乘后，发现 $i,j$ 是独立的。所以前缀和优化即可。复杂度 $O(n)$。

```cpp
#define N 2000010
int fac[N], invf[N]; int C(int n, int m) { return 1ll * fac[n] * invf[m] % mod * invf[n - m] % mod; }
int n, K;
int a[N], L[N];
int dp[N], pre[N];

void solve()
{
	n = read(), K = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	L[n + 1] = n + 1;
	for(int i = n; i >= 1; i--)
	{
		L[i] = std::min(L[i + 1], i);
		for(; L[i] > 1 && a[i] - a[L[i] - 1] <= K; L[i]--);
	}
	if(L[n] != n) { print(0, '\n'); return; }
	// dp[0] = 1;
	// for(int i = 1; i <= n; i++) 
	// {
	// 	for(int j = 0; j < L[i]; j++)
	// 	{
	// 		int t = L[i] - L[j] - 1, oth = n - L[i];
	// 		plus_(dp[i], 1ll * dp[j] * fac[t] % mod * C(oth + t, t) % mod);
	// 	}
	// }
	// print(dp[n], '\n');
	dp[0] = 1; pre[0] = fac[n - 1];
	for(int i = 1; i <= n; i++)
	{
		dp[i] = 1ll * pre[L[i] - 1] * invf[n - L[i]] % mod;
		pre[i] = sm(pre[i - 1] + 1ll * dp[i] * fac[n - L[i] - 1] % mod);
	}
	print(dp[n], '\n');
}
```

---

## 作者：Skeleton_Huo (赞：0)

一个比较抽象的方法。

首先我们观察一下解的形式：一定是一个大，若干小，一个大若干小，这样的形式。形象的说，我们可以认为有若干个“擂主”，然后他们后面会跟着若干“败者”，然后再被下一个擂主打下去。

因此，我们可以根据该性质 DP，即考虑选出一个子序列作为擂主，然后将败者插入擂主之间。

倒着 DP 比较方便：设 $f_i$ 为以选手 $i$ 为第一个擂主，且与第二个擂主间没有败者，且所有可选择的败者都被选择的方案数。

方程可能要自己推一下理解理解。

$$
f_i = \sum_{j:a_j - a_i > k}{f_j \binom{x+y}{y}y!}
$$
记 $c_i$ 为能力值大于等于 $a_i - k$ 的人数，那么 $x = c_j - 1$，$y = c_i - c_j - 1$。

这个通过化简可以得到：
$$
f_i = (c_i - 2)!\sum_{j:a_j - a_i > k}{\frac{f_j}{(c_j-1)!}}
$$

此时可以用前缀和来优化 DP。

可能太抽象了，画张图（图中黑色为擂主，其他颜色为败者）：
![](https://img1.imgtp.com/2023/09/30/ffnunGey.png)

我们希望在转移的时候，可以随意的在 $j$ 位置往后，插入大小在 $[a_i - k, a_j - k)$ 的数。所以相当于是分了个层。固定了每个阶段能填的数。

最后统计的只需枚举每个人作为第一个擂主，然后将小于 $a_i - k$ 的败者补进来，再求和即可。

### AC Code
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 10, P = 998244353;

int n, k, a[N];
int fac[N], ifac[N], c[N], f[N];

int inv(int a)
{
    int x = P - 2, res = 1;
    for (; x; x >>= 1) {
        if (x & 1)
            res = res * a % P;
        a = a * a % P;
    }
    return res;
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
    cin >> n >> k;

    // j 指向第一个 >= a[i] - k 的数
    for (int i = 1, j = 1; i <= n; i++) {
        cin >> a[i];
        while (j <= n && a[j] < a[i] - k)
            j++;
        c[i] = n - j + 1;
    }

    if (a[n] - a[n - 1] <= k) {
        cout << "0\n";
        return 0;
    }

    fac[0] = 1;
    ifac[0] = inv(fac[0]);
    for (int i = 1; i <= n + 5; i++) {
        fac[i] = fac[i - 1] * i % P;
        ifac[i] = inv(fac[i]);
    }

    // j 指向第一个 <= a[i] + k 的点
    int sum = 0;
    f[n] = 1;
    for (int i = n - 1, j = n; i >= 1; i--) {
        while (j > i && a[j] > a[i] + k) {
            sum = (sum + f[j] * ifac[c[j] - 1] % P) % P;
            j--;
        }
        f[i] = fac[c[i] - 2] * sum % P;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += f[i] * fac[n - 1] % P * ifac[c[i] - 1] % P;
        ans %= P;
    }

    cout << ans << "\n";

    return 0;
}

```

---

