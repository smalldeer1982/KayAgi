# [ABC360E] Random Swaps of Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_e

$ N\ -\ 1 $ 個の白いボールと $ 1 $ 個の黒いボールがあります。これらの $ N $ 個のボールが横一列に並んでおり、はじめ黒いボールが最も左にあります。

高橋くんは、これから以下の操作をちょうど $ K $ 回行います。

- $ 1 $ 以上 $ N $ 以下の整数を一様ランダムに選ぶ試行を $ 2 $ 回行う。選んだ整数をそれぞれ $ a,\ b $ とする。さらに、 $ a\ \neq\ b $ であれば左から $ a $ 番目のボールと $ b $ 番目のボールを交換する。
 
$ K $ 回の操作のあと黒いボールがある位置を左から $ x $ 番目とします。$ x $ の期待値を $ \text{mod}\ 998244353 $ で求めてください。

   期待値 $ \text{mod}\ 998244353 $ とは  求める期待値は必ず有理数になることが証明できます。 また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます。 よって、$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ &amp;lt\ 998244353 $ を満たす整数 $ R $ が一意に定まります。 この $ R $ を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 998244352 $
- $ 1\ \leq\ K\ \leq\ 10^5 $
 
### Sample Explanation 1

$ 1 $ 回の操作が終わった後、黒いボールが左から $ 1 $ 番目にある確率、 $ 2 $ 番目にある確率はそれぞれ $ \displaystyle\ \frac{1}{2} $ です。よって期待値は $ \displaystyle\ \frac{3}{2} $ です。

## 样例 #1

### 输入

```
2 1```

### 输出

```
499122178```

## 样例 #2

### 输入

```
3 2```

### 输出

```
554580198```

## 样例 #3

### 输入

```
4 4```

### 输出

```
592707587```

# 题解

## 作者：CarroT1212 (赞：38)

提供一种应该不太一样且码量骤减的人类智慧做法，目前卡长后是 AT 最短解。

------------

设每次选到的两个数为 $a,b$，黑球目前在 $x$。

+ 如果 $a\neq x$ 且 $b\neq x$，那么这轮操作就跟 $x$ 没有关系，$x$ 原地不动，概率为 $\frac{(n-1)^2}{n^2}$。
+ 如果 $a=b=x$，那么 $x$ 同样保持不动，概率为 $\frac{1}{n^2}$。
+ 如果 $a=x$ 或 $b=x$，那么 $x$ 等概率地换到除它以外的任何一个位置，每一位概率都为 $\frac{2}{n^2}$。

这时我们动用人类智慧：注意到前两种操作结果相同，于是你从第一种操作里随便拿一种情况分给第二种，使第二种操作的概率变成 $\frac{2}{n^2}$，这样后面两种操作就可以合并起来了。变成，每次操作：

+ $x$ 以 $\frac{(n-1)^2-1}{n^2}$ 的概率不受影响。
+ $x$ 以 $\frac{2n}{n^2}$ 的概率随机分配到 $[1,n]$ 中任意一个位置，每个位置概率都为 $\frac{2}{n^2}$。

也就是说，只要 $x$ 在这个定义下“受到影响”过一次，那么它的位置就会完全随机，不管受到几次影响都一样。这样 $x$ 的期望值就为 $\frac{n+1}{2}$。否则一次都没受影响就是 $x=1$。

即答案为 $(\frac{(n-1)^2-1}{n^2})^k+[1-(\frac{(n-1)^2-1}{n^2})^k]\cdot\frac{n+1}{2}$。

------------

```cpp
ll qp(ll x,ll y=P-2) { return y?(y&1?x:1)*qp(x*x%P,y>>1)%P:1; }
ll n,k,p;
void mian() {
	scanf("%lld%lld",&n,&k);
	p=qp(((n-1)*(n-1)+P-1)%P*qp(n*n%P)%P,k);
	cout<<(p+(1+P-p)*((n+1)*qp(2)%P))%P;
}
```

~~感觉自己赛时能想到真是太厉害了。~~

---

## 作者：ma_niu_bi (赞：19)

### [ABC360E] Random Swaps of Balls  题解

### 题意

有 $N - 1$ 个白球和一个黑球。这些 $N$ 球排列成一排，黑球最初位于最左边的位置。

高桥正好要执行下面的操作 $K$ 次。

- 在 $1$ 和 $N$ 之间均匀随机地选择一个整数，包括两次。设 $a$ 和 $b$ 为所选整数。如果是 $a \neq b$，从左边开始交换 $a$ -th 和 $b$ -th 两个球。

经过 $K$ 次操作后，让黑球位于左边第 $x$ 个位置。求 $x$ 的期望值，对 $998244353$ 取模。

### 思路

记 $k$ 次操作后黑球在最左边的概率为 $f$，则黑球在其他点的概率均为 $\frac{1-f}{n-1}$。

因为若黑球不在最左边，在其他点的概率都相同。

求出 $f$ 即可求出答案。

设 $f_i$ 表示第 $i$ 次操作后黑球在最左边的概率。

记 $p$ 为黑球从最左边跑到其他点的概率。

记 $q$ 为黑球从其他点回到最左边的概率。
$$
p=2\times \frac{1}{n}\times\frac{n-1}{n}=\frac{2n-2}{n^2}
$$

$$
q=2\times \frac{1}{n} \times \frac{1}{n}=\frac{2}{n^2}
$$

注意每次操作所选的 $a$ 和 $b$ 顺序没有影响，概率需要乘二。

状态转移：
$$
f_i=(1-p)f_{i-1}+q(1-f_{i-1})
$$
即保持在最左边的概率加上从其他点回到最左边的概率。

时间复杂度 $O(k)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
const int mod = 998244353;
int qpow(int a, int x) {
    int ret = 1;
    for (; x; x >>= 1, a = a * a % mod)
        if (x & 1) ret = ret * a % mod;
    return ret;
}
int inv(int x) {return qpow(x, mod - 2);}
int n, k, p, q, e, ans, dp[N];
signed main() {
    cin >> n >> k;
    p = 2 * (n - 1) % mod * inv(n * n % mod) % mod; 
    q = 2 * inv(n * n % mod) % mod;
    dp[0] = 1;
    for (int i = 1; i <= k; i ++)
        dp[i] = (1 - p + mod) % mod * dp[i - 1] % mod + q % mod * (1 - dp[i - 1]) % mod,
        dp[i] += mod, dp[i] %= mod;
    ans += dp[k];
    e = (1 - dp[k] + mod) % mod * inv(n - 1) % mod;
    e *= (n - 1) % mod * (n + 2) % mod * inv(2) % mod;
    e %= mod;
    ans += e, ans %= mod;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：linjunye (赞：5)

![](bilibili:BV1QF89eqEWn)

普通 DP：
```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,k,ans;
int dp[100010][3];
int fm,sum;
int ksm(int a,int b){
	int z=1;
	while(b){
		if(b&1)z=z*a%mod;
		a=a*a%mod;
		b>>=1; 
	}
	return z;
}
int inv(int x){
	x%=mod;
	return ksm(x,mod-2);
}
int sub(int a,int b){
	return ((a-b)%mod+mod)%mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	int num=(ksm(n-1,2)+1)%mod;
	dp[0][1]=1;
	sum=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=2;j++){
			dp[i][j]=(2*sum%mod+dp[i-1][j]*sub(num,2)%mod);
			dp[i][j]=dp[i][j]*inv(n*n)%mod%mod;
		}
	cout<<(dp[k][1]+dp[k][2]*(2+n)%mod*(n-1)%mod*inv(2)%mod)%mod;
	return 0;
}
//dp[i][j]:第i次，黑球在第j个地方的概率 
```
[提交结果](https://atcoder.jp/contests/abc360/submissions/55113482)。

加了矩阵快速幂：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,k,x,num;
int ksm(int a,int b){
	int z=1;
	while(b){
		if(b&1)z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
int sub(int a,int b){
	return ((a-b)%mod+mod)%mod;
}
int inv(int x){
	x%=mod;
	return ksm(x,mod-2);
}
struct martix{
	int a[5][5];
	void init(){
		memset(a,0,sizeof(a));
		return;
	}
};
martix A,B,ans; 
void init(int S){
	A.init();
	B.init();
	A.a[1][1]=x*inv(n*n)%mod;
	A.a[1][2]=inv(n*n)%mod;
	A.a[2][2]=1;
	B.a[1][1]=S;
	B.a[2][1]=2;
	return;
}
martix mul(martix a,martix b){//a*b
	martix c;
	c.init();
	for(int k=1;k<=2;k++)
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%mod)%mod;
	return c;
}
martix unit(martix a){
	for(int i=1;i<=2;i++)
		a.a[i][i]=1;
	return a;
}
martix ksm(martix a,int b){
	martix z;
	z.init();
	z=unit(z);
	while(b){
		if(b&1)z=mul(z,a);
		a=mul(a,a);
		b>>=1;
	}
	return z;
}
int cal(int S){
	init(S);
	ans=mul(ksm(A,k),B);
	return ans.a[1][1]%mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	num=(ksm(n-1,2)+1)%mod;
	x=sub(num,2);
	cout<<(cal(1)+cal(0)*(2+n)%mod*(n-1)%mod*inv(2)%mod)%mod;
	return 0;
}
```
[提交结果](https://atcoder.jp/contests/abc360/submissions/55114978)。

---

## 作者：xiezheyuan (赞：4)

## 简要题意

> E - Random Swaps of Balls
>
> 有 $n$ 个球，其中 $n-1$ 球为白球，剩下一个球为黑球。初始时黑球为第 $1$ 个球。
>
> 你可以进行 $k$ 次操作，每次操作等概率随机选择两个整数 $i,j\in[1, n]$，然后交换第 $i$ 个和第 $j$ 个球。
>
> 求最终黑球位置期望，对 $P=998244353$ 取模。
>
> $1\leq N<P,1\leq k\leq 10^5$

## 思路

设 $f_i$ 表示第 $i$ 个操作后的答案，则有：

$$
f_i=\begin{cases}
1&i=0\\
\frac{(n-1)(n-1)+1}{n^2}\cdot f_{i-1}+\frac{1}{n^2}\cdot \left(\frac{1}{2}n(n+1)-f_{i-1}\right)\cdot 2&\text{otherwise}
\end{cases}
$$

为什么呢？

- 对于第一部分 $\frac{(n-1)(n-1)+1}{n^2}$ 表示有 $(n-1)(n-1)$ 种情况没有选择黑球位置，还有 $1$ 种情况 $i,j$ 均是黑球位置，这些情况不会改变答案。
- 对于第二部分，则是选择了黑球位置。所有位置和显然可以用等差数列求和公式。但是需要注意可能选择黑球原有的位置，需要减去这一部分的贡献。然后选择的 $i,j$ 有序，所以要乘上 $2$。

时间复杂度 $O(k+\log n)$。

## 代码

注意别溢出了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n, k, ans = 1;

int M(int x){
    return (x % mod + mod) % mod;
}

int fastpow(int a, int b){
    int ans = 1;
    while(b){
        if(b&1) ans = M(ans * a);
        a = M(a * a);
        b >>= 1;
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k;
    int all = M(M(n * (n + 1)) * fastpow(2, mod - 2));
    int cb = fastpow(M(n * n), mod - 2);
    int nocb = M(M((n - 1) * (n - 1) + 1) * cb);
    for(int i=1;i<=k;i++) ans = M(M(nocb * ans) + M(cb * M((all - ans) * 2)));
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Pentiment (赞：4)

设 $f_i$ 为第 $i$ 次操作后黑球位置的期望。一共有 $n^2$ 种选数的方式，其中有 $(n-1)^2+1$ 种方式不会对黑球的位置产生影响，剩下 $2n-2$ 种方式，黑球落在除原位置外的所有位置的概率相同，有：
$$
f_i=\dfrac{f_{i-1}[(n-1)^2+1]+\frac{\sum_{j=1}^nj-f_{i-1}}{n-1}\cdot(2n-2)}{n^2}
$$
化简一下好看点。
$$
f_i=\dfrac{f_{i-1}(n^2-2n)+n(n+1)}{n^2}
$$

---

## 作者：__Cby___ (赞：3)

## 思路
很容易知道 $2\le x\le n$ 的情况下概率是相同的。   
我们先考虑 $2\le x\le n$ 的情况，设 $dp_i$ 表示经过 $i$ 次操作后黑球的位置在 $x$ 的概率。分两种情况，第一种情况是上一次操作时小球在 $x$ 位置的，这个时候只要不动小球就没问题，若 $a=b=x$ 的时候也是没问题的。概率为：   
$$\begin{aligned}&dp_{i-1}\times \big((\frac{n-1}{n}\times\frac{n-1}{n})+(\frac{1}{n}\times\frac{1}{n}) \big)\\ &=dp_{i-1}\times(\frac{n^2-2n+2}{n^2})\\ &=dp_{i-1}\times(1-\frac{2n-2}{n^2})\end{aligned}$$
另一种情况是上一次小球不在 $x$ 位置，其概率显然为：
$$\begin{aligned}&(1-dp_{i-1})\times2\times\frac{1}{n}\times\frac{1}{n}\\&=(1-dp_{i-1})\times\frac{2}{n^2}\end{aligned}$$  
直接递推即可。    
对于 $x=1$ 时，我们让 $dp_0=1$ 表示不操作时在 $x$ 位置的概率为 $1$ 即可。预处理 $\frac{1}{n}$ 在模 $998244353$ 意义下的逆元。总复杂度为 $O(k+\log n)$。   
## 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
__int128 dp[100025];
__int128 fp(__int128 a,__int128 b){
	__int128 ans=1;
	a%=998244353;
	while(b){
		if(b&1){
			ans*=a;
			ans%=998244353;
		}
	    a*=a;
		a%=998244353;
		b>>=1;
	}
	return ans;
}
int main() {
	long long int n,k;
	cin>>n>>k;
	__int128 cn=fp(n,998244351);
	__int128 lzh=1-((2*n-2)*fp(n*n,998244351)%998244353)+998244353;
	lzh+=998244353;
	lzh%=998244353;
	__int128 xlw=2*cn*cn%998244353;
	__int128 u;
	for(int i=1;i<=k;i++){
		dp[i]+=dp[i-1]*lzh%998244353+((1-dp[i-1])*xlw)%998244353;
		dp[i]%=998244353;
	}
	u=dp[k];
	for(int i=1;i<=k;i++)dp[i]=0;
	dp[0]=1;
	for(int i=1;i<=k;i++){
		dp[i]=dp[i-1]*lzh%998244353+((1-dp[i-1])*xlw)%998244353;
		dp[i]%=998244353;
	}
	cout<<(long long int)((dp[k]+u*((2+n)*(n-1)/2)%998244353)%998244353+998244353)%998244353<<endl;
	return 0;
}
```

---

## 作者：sgl654321 (赞：1)

## 题目大意
- 有 $n$ 个球，其中第一个球是黑球，其他是白球。
- $k$ 次操作，每次选择任意两个数 $(i,j)$，把第 $i$ 个球和第 $j$ 个球进行交换。
- 问 $k$ 次操作之后黑球的位置期望值。

## 解题思路
设黑球原来的位置处在 $x$。那么，如果它的位置受到了变化，变成了一个不是 $x$ 的数 $y$，那么你选的 $(i,j)$ 要么是 $(x,y)$ 要么是 $(y,x)$。

所以，从 $x$ 变成任意一个 $y\not=x$ 的概率都是 $\dfrac{2}{n^2}$。如果仍然待在 $x$ 位置的概率就是 $1-\dfrac{2(n-1)}{n^2}=\dfrac{n^2-2n+2}{n^2}$。

因此，根据期望的定义式，操作一次后，它的位置期望值就变成了：

$$E(x)=\dfrac{n^2-2n+2}{n^2}\times x+\dfrac{2}{n^2}\times(\dfrac{n\times(n+1)}{2}-x)$$

化简：

$$E(x)=\dfrac{n-2}{n}+\dfrac{n+1}{n}\times x$$

那么现在有 $k$ 次操作，第一次操作显然 $x = 1$。但是第二次操作和以后的操作，黑球在不同位置上的概率各不相同，期望值变得非常难算。不少题解并没有解释**为什么在算第二次的期望值时，可以令 $x$ 等于第一次算出的期望值，代入原式计算。**

下面给出简要证明：

令 $P(i)$ 为一次操作后处在 $i$ 这个位置的概率。有：

$$E_2(x)=\sum_{i=1}^nP(i)E(x)=\sum_{i=1}^nP(i)\times (\dfrac{n-2}{n}+\dfrac{n+1}{n}\times i)$$

由于 $E(x)$ 是关于 $x$ 的一个一次函数，因此可以进一步把 $P(i)$ 乘进去。

$$E_2(x)=\dfrac{n-2}{n}+\dfrac{n+1}{n}\times \sum_{i=1}^niP(i)$$

而 $\sum_{i=1}^niP(i)=E(1)$。

因此有

$$E_2(x)=E(E(1))$$

这个都得出来了，那下面这些就不用说了吧……

$$E_3(x)=E(E(E(1))),E_4(x)=E(E(E(E(1))))$$

因此我们直接把他一次一次递归进去带入就可以了。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll qpow(ll x, ll y){
	ll ret = 1;
	while(y){
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	} 
	return ret;
}
ll n, k, ans, num, iv, x;
int main(){
	cin >> n >> k; 
	iv = qpow(n * n % mod, mod - 2);
	
	ans = 1;
	for(int i = 1; i <= k; i++){
		num = n * (n + 1) / 2 - ans;
		num = (num % mod + mod) % mod;
		num = num * 2 % mod * iv % mod;
		
		x = n * n - 2 * n + 2; x = x % mod;
		x = x * iv % mod;
		x = x * ans % mod;
		
		ans = (num + x) % mod;
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：aeiouaoeiu (赞：0)

考虑当前的期望为 $f$，我们要把它转移到下一次操作的期望 $f'$。

分两类贡献。

- 黑球没有动。概率为 $p_0=\frac{n^2-2n}{n^2}$。贡献为 $fp_0$。

- 黑球动了。动到一个特定点的概率为 $p_1=\frac{2}{n^2}$。令 $s=\sum_{i=1}^{n} i$。贡献需要稍微拼凑一下，先把黑球没有动视为动了，这部分是 $sp_1$，然后再删去没有动的情况，这部分是 $fp_1$，故贡献为 $sp_1-fp_1$。

于是 $f'\leftarrow fp_0+sp_1-fp_1$，递推即可，时间复杂度 $\mathcal{O}(k)$。

值得注意的是 $fp_0+sp_1-fp_1=f(p_0-p_1)+sp_1$，可以通过矩阵快速幂、等比数列等优化至对数级别复杂度。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
#define mkt make_tuple
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=500007,ee=1000000000000000007ll,p=998244353;
ll n,k,inv,co,ro,s,f,g;
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
signed main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	//ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	inv=qpow(n*n%p,p-2),ro=2*inv%p,co=(n*n-2*(n-1))%p*inv%p,s=n*(n+1)%p*qpow(2,p-2)%p;
	f=(co+ro*((s-1+p)%p)%p)%p;
	for(int i=2;i<=k;i++) f=(f*co%p+(ro*s%p-f*ro%p+p)%p)%p;
	cout<<f<<"\n";
	return 0;
}
```

---

## 作者：FXT1110011010OI (赞：0)

## 分析

先考虑一次操作后黑球的位置变化：

1. $a, b$ 均不是黑球，黑球位置不变，概率为 $\frac{(n - 1) ^ 2}{n ^ 2} = \frac{n ^ 2 - 2n + 1}{n ^ 2}$；
2. $a, b$ 均是黑球，黑球位置不变，概率为 $\frac{1}{n ^ 2}$；
3. $a, b$ 中有且仅有一个黑球，黑球位置变化，概率为 $\frac{2n - 2}{n ^ 2}$，显然，黑球会等概率变到其他位置，变到每个位置的概率都为 $\frac{2}{n ^ 2}$。

再考虑多次操作后黑球的位置变化，可以 DP：设 $f_{i, j}$ 表示经过 $i$ 次操作，黑球在 $j$ 的概率。转移比较显然：$f_{i, j} = \sum \limits_{k = 1}^n f_{i - 1, k} \times g_{k, j}$，其中 $g_{k, j}$ 表示黑球一次操作后从位置 $k$ 变到位置 $j$ 的概率，可以通过上面的分讨求出来。初始状态就是 $f_{0, 1} = 1$，表示黑球一开始在位置 $1$。但是，这样的复杂度是 $O(n ^ 2k)$，显然爆炸。

我们发现除了 $g_{i, i}$ 外，其他的 $g_{i, j}$ 是相同的，可以提取公因数，优化掉一个 $k$，复杂度变为 $O(nk)$，还是过不去。

注意到因为黑球一开始在位置 $1$，所以第 $2 \sim n$ 个位置本质是相同的，即 $f_{i, 2 \sim n}$ 是相同的，于是我们优化掉了一个 $n$，复杂度变为 $O(k)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL mod = 998244353;

LL qmi(LL a, LL b)
{
    LL res = 1;
    while (b)
    {
        if (b & 1) res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res;
}

int main()
{
    LL n, k; scanf("%lld%lld", &n, &k);
    LL g1 = 1, g2 = 0, inv = qmi(n * n % mod, mod - 2);
    for (LL i = 1; i <= k; i ++ )
    {
        LL gg1 = g1, gg2 = g2;
        g1 = ((n - 1) * gg2 % mod * 2 % mod * inv + gg1 * ((n * n % mod - n * 2 % mod + 2) % mod + mod) % mod * inv % mod) % mod;
        g2 = ((gg1 + (n - 2) * gg2 % mod) % mod * 2 % mod * inv % mod + gg2 * ((n * n % mod - n * 2 % mod + 2) % mod + mod) % mod * inv % mod) % mod;
    }
    LL res = (g1 + (n + 2) * (n - 1) / 2 % mod * g2 % mod) % mod;
    printf("%lld\n", res);
    return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution
设 $f_i$ 表示进行完 $i$ 此操作后黑球位置的期望，则 $f_{0}=1$，答案即为 $f_K$。

考虑怎么进行转移。设当前是第 $i$ 此操作，随机到了 $a,b$，现在黑球的位置在 $x$。对于一次操作，有以下几种情况：
+ $a,b\neq x$，这种情况的概率为 $(\frac{N-1}{N})^2$，贡献即为 $(\frac{N-1}{N})^2f_{i-1}$。

+ $a,b$ 中有 $x$。首先抽到 $x$ 的概率为 $\frac{1}{N}$，另一个数随机到 $j$ 的概率也为 $\frac{1}{N}$，贡献为 $\frac{i}{N}$。所以这部分的总贡献为 $2 \sum_{i=1}^N \frac{i}{N}$。
\
但是这样还有一个问题，就是 $a=b=x$ 时的贡献被我们计算了两次，而这个 $x$ 又是不确定的，所以难以消去贡献。
\
回归期望的定义，考虑 $f_{i-1}=\sum_{i=1}^N i P(x=i)$，那么我们可以枚举这个 $x$，则需要减去的值就是 $ \frac{1}{N^2}\sum_{i=1}^N i P(x=i)$，乘上 $\frac{1}{N^2}$ 是求出抽到这个位置的概率。而这个式子恰好可以化为 $\frac{1}{N^2}f_{i-1}$。

综上，我们得到

$$f_i=(\frac{N-1}{N})^2f_{i-1}+2\sum_{i=1}^N \frac{i}{N^2}-f_{i-1}$$

也就是

$$f_i=\frac{-2N+1}{N^2}f_{i-1}+\frac{2\sum_{i=1}^Ni}{N^2}$$

提前预处理出 $N^2$ 的逆元和后面式子的值，直接计算即可。

时间复杂度 $\mathcal{O}(K+\log N)$。

### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
const int MOD=998244353;
ll f[maxn];
ll power(ll a,ll b,ll p){
	a%=p;
	ll ans=1;
	for(;b;b>>=1){
		if(b&1) ans=(ans*a)%p;
		a=(a*a)%p;
	}
	return ans;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	ll inv=power(1ll*n*n,MOD-2,MOD);
	ll val=(1ll*n*(n+1))%MOD;
	val=(val*power(2,MOD-2,MOD))%MOD;
	val=(val*inv)%MOD;
	f[0]=1;
	for(int i=1;i<=k;i++){
		ll w=(1ll*(n-1)*(n-1))%MOD;
		w=(w*inv)%MOD;
		f[i]=((f[i-1]*w)%MOD+2*val)%MOD;
		f[i]=(f[i]-(f[i-1]*inv)%MOD+MOD)%MOD;
	}
	printf("%lld",f[k]);
	return 0;
}
```

---

## 作者：zrl123456 (赞：0)

[[ABC360E] Random Swaps of Balls](https://www.luogu.com.cn/problem/AT_abc360_e)   

题目考查：期望，逆元。    
题目简述：  
给你一个数 $n$，有 $n-1$ 个白球和 $1$ 个黑球，黑球一开始在最左侧。有 $k$ 次操作，每次操作**等概率随机地**从区间 $[1,n]$ 选出两个数 $a,b$，交换处于从左往右数第 $a$ 个球和第 $b$ 个球，求最后黑球所在位置的期望值对 $998244353$ 取模的结果。   
数据范围：
- $1\le n<998244353$
- $1\le k\le 10^5$
------------
很容易发现除了黑球在第一个位置外，黑球在其他位置上的概率是相同的。   
那么我们设第 $i$ 次操作后黑球在第一个位置上的概率（当然要对 $998244353$ 取模，下同）为 $f_i$，在其他位置上的概率为 $g_i$。  

注：  
$\displaystyle(\frac{a}{b}+\frac{c}{d})\bmod p$ 和 $\displaystyle(\frac{a}{b}\bmod p+\frac{c}{d}\bmod p)\bmod p$ 是相同的，下面给出证明：  
$$\begin{aligned}(\frac{a}{b}+\frac{c}{d})\bmod p&=\frac{ad+bc}{bd}\bmod p\\&=(ad+bc)(bd)^{-1}\bmod p\end{aligned}$$
根据费马小定理（$a^p\equiv a\pmod p$，$p\in \text{prime}$），得：  
$$\begin{aligned}(\frac{a}{b}+\frac{c}{d})\bmod p&=(ad+bc)(bd)^{-1}\bmod p\\&=(ad+bc)(bd)^{p-2}\bmod p\end{aligned}$$
而：  
$$\begin{aligned}(\frac{a}{b}\bmod p+\frac{c}{d}\bmod p)\bmod p&=(ab^{-1}+cd^{-1})\bmod p\\&=(ab^{p-2}+cd^{p-2})\bmod p\end{aligned}$$
我们将 $(ad+bc)(bd)^{p-2}$ 转化：  
$$\begin{aligned}(ad+bc)(bd)^{p-2}&=ad(bd)^{p-2}+bc(bd)^{p-2}\\&=ab^{p-2}d^{p-1}+cd^{p-2}b^{p-1}\\&=ab^{p-2}+cd^{p-2}\end{aligned}$$
证毕。  
减法，乘法同理。  

接下来对 $f_i$ 考虑转移方程，想要将黑球移到其他地方，有 $(1,2),(1,3),\dots,(1,n-1),(1,n)$ 和 $(2,1),(3,1),\dots,(n-1,1),(n,1)$ 这些 $2(n-1)$ 种方法，那么黑球留在原地就有 $n^2-2(n-1)$ 种方法，得转移方程：  
$$f_i=((n^2-2(n-1))f_{i-1}+2(n-1)g_{i-1})\bmod 998244353$$
然后对 $g_i$ 考虑转移方程，想要将黑球移到最左边，只有 $2$ 种方法。那么留在除了最左边的其他地方有 $n^2-2$ 种方法，得转移方程：
$$g_i=((n^2-2)g_{i-1}+2f_{i-1})\bmod 998244353$$
最后答案就是：  
$$ans=(f_k+(n(n+1)-1)g_k)\bmod 998244353$$

总体复杂度为 $\Theta(k)$。  
代码：  
```cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define int long long
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define rep(i,x,y) for(reg int i=x;i<=(y);++i) 
#define per(i,x,y) for(reg int i=x;i>=(y);--i)
#define rpr(i,x,y,z) for(reg int i=x;i<=(y);i+=z)
#define epe(i,x,y,z) for(reg int i=x;i>=(y);i-=z)
#define endl '\n'
#define INF 1e16
#define pb push_back
#define fi first
#define se second
#define lcm(x,y) x/__gcd(x,y)*y
#define ull unsigned long long
#define prr make_pair
#define pii pair<int,int> 
#define gt(s) getline(cin,s)
#define at(x,y) for(reg auto x:y)
#define ff fflush(stdout)
#define mt(x,y) memset(x,y,sizeof(x))
#define idg isdigit
#define fp(s) string ssss=s;freopen((ssss+".in").c_str(),"r",stdin);freopen((ssss+".out").c_str(),"w",stdout);
using namespace std;
const int N=1e5+5,MOD=998244353;
int f[N],g[N];
inl int ksm(int a,int b){
	reg int num=a%MOD,ans=1;
	while(b){
		if(b&1) (ans*=num)%=MOD;
		(num*=num)%=MOD;
		b>>=1; 
	}
	return ans;
}
inl int inv(int a,int b){
	return a*ksm(b,MOD-2)%MOD;
}
signed main(){
	fst;
	reg int n,k,p,q,r,s;
	cin>>n>>k;
	p=inv((n-1<<1)%MOD,n*n%MOD);
	q=inv(2,n*n%MOD);
	r=inv((n*n-(n-1<<1))%MOD,n*n%MOD);
	s=inv((n*n-2)%MOD,n*n%MOD);
	f[0]=1;
	g[0]=0;
	rep(i,1,k){
		f[i]=(f[i-1]*r%MOD+g[i-1]*p%MOD)%MOD;
		g[i]=(g[i-1]*s%MOD+f[i-1]*q%MOD)%MOD;
	}
	cout<<(f[k]+((n*(n+1)>>1)-1)%MOD*g[k]%MOD)%MOD;
	return 0;
} 
```

---

## 作者：wly09 (赞：0)

简单手玩就能发现 $2\sim N$ 的概率是一样的。

设第 $i$ 轮第一个位置的概率为 $a_i$，其余位置概率均为 $b_i$。

考虑转移。

对于一个位置 $p$，随机选择两次，共 $N^2$ 个选法：

+ 有 $(N-1)^2$ 个不会选到 $p$；
+ 有 $1$ 个选两次 $p$；
+ 仅选一次 $p$，另一次选到 $q$，对于每个 $q$ 各有 $2$ 个选法。

总之，有 $\dfrac{(N-1)^2+1}{N^2}$ 的概率不会移动，移动到其他每个位置的概率均为 $\dfrac{2}{N^2}$。

容易验证 $\dfrac{(N-1)^2+1}{N^2}+(N-1)\times\dfrac{2}{N^2}=1$。

先考虑 $a_{i+1}$：

+ 对于第一个位置，不移动的概率为 $\dfrac{(N-1)^2+1}{N^2}$，因此有 $\dfrac{(N-1)^2+1}{N^2}\times a$ 的贡献。
+ 对于剩下 $(N-1)$ 个位置，每个位置有 $\dfrac{2}{N^2}$ 的概率转移到第一个位置，共有 $(N-1)\times \dfrac{2}{N^2}\times b$ 的贡献。

故 $a_{i+1}=\dfrac{(N-1)^2+1}{N^2}+(N-1)\times \dfrac{2}{N^2}\times b$。

再考虑 $b_{i+1}$，不妨取 $p\ne 1$ 考虑：

+ 对于第一个位置，有 $\dfrac{2}{N^2}$ 的概率转移到 $p$，贡献 $\dfrac{2}{N^2}\times a$。
+ 对于位置 $p$，有 $\dfrac{(N-1)^2+1}{N^2}$ 的概率不移动，贡献 $\dfrac{(N-1)^2+1}{N^2}\times b$。
+ 对于剩下 $(N-2)$ 个位置，各有 $\dfrac{2}{N^2}$ 的概率转移到 $p$，贡献 $(N-2)\times \dfrac{2}{N^2}\times b$。

容易验证，对于其他任意 $q>1$，情况与 $p$ 确实是等同的。

因此 $b_{i+1}=\dfrac{2}{N^2}\times a+\dfrac{(N-1)^2+1}{N^2}\times b+(N-2)\times \dfrac{2}{N^2}\times b$。

初始 $a_0=1,b_0=0$，$O(K)$ 递推即可。

[AC 记录](https://atcoder.jp/contests/abc360/submissions/55087357)

> 有人不会期望吗？对于这种离散型的，可以简单理解成各个取值按出现概率的加权平均。

*题外话：若将 $N,K$ 开大，容易发现 $N$ 直接取模（不能为零）即可，$K$ 可以矩阵快速幂处理，开到 $10^{10000}$ 问题不大。*

*难度大概绿，或者下位蓝。*

---

## 作者：__Floze3__ (赞：0)

## 思路简介

不难想到，除了第 $1$ 个位置，在进行 $k$ 次操作后黑球到每个位置的概率是均等的。因此，我们只需要维护两个值：黑球在第 $1$ 个位置的概率和在其他位置的概率。

我们考虑从上一次操作进行完之后递推。令上一次操作完后在第一次的概率为 $a$，在其他位置的概率为 $b$。我们考虑如何得出在这一次操作完后的两种概率，记为 $a'$ 和 $b'$。

首先是在第一个位置的概率，有两种转移方式：

1. 从其他位置转移而来，对于每个除 $1$ 以外的位置，在 $n ^ 2$ 种可能的数字中都有 $2$ 种方式转移。
2. 在 $1$ 这个位置保持不变，在所有的 $n^2$ 种可能性中，除了从其他位置转到 $1$ 号位置，其余的可能都是保持不变，有 $n ^ 2 - 2 \times (n - 1)$ 种方式。

然后是在其他位置的概率，有三种转移方式：

1. 从第 $1$ 个位置转移而来，在 $n ^ 2$ 种可能性中有 $2$ 种组合能做到这一点。
2. 从除了第 $1$ 个位置和当前位置转移而来，对于剩下的 $n - 2$ 个位置，每个位置有 $2$ 种组合来转移。
3. 在当前位置保持不变，有 $n ^ 2 - 2 \times(n - 2) - 2$ 种组合可以做到这一点。

因此，我们可以得出：

$$
a' = (n - 1) \times b \times \frac{2}{n ^ 2} + a \times \frac{n ^ 2 - 2 \times n + 2}{n ^ 2} \\
b' = a \times \frac{2}{n ^ 2} + (n - 2) \times b \times \frac{2}{n ^ 2} + b \times \frac{n ^ 2 - 2 \times n + 2}{n ^ 2} = a \times \frac{2}{n ^ 2} + b \times \frac{n ^ 2 - 2}{n ^ 2}
$$

直接 $O(k)$ 递推即可。

## 代码

[赛时提交记录](https://atcoder.jp/contests/abc360/submissions/55088189)

---

## 作者：lfxxx (赞：0)

注意到第 $2$ 个位置到第 $n$ 个位置本质上没区别。

不妨设计状态 $dp_{i,0/1}$ 表示 $i$ 次操作后在位置 $1$ 的概率与在其他位置上的概率。

转移的时候考虑到 $1$ 与 $1$ 交换，第 $2$ 个位置到第 $n$ 个位置内部交换，$1$ 与第 $2$ 个位置到第 $n$ 个位置中没有球的交换，以及与有球的交换几种情况即可，具体转移见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int n,k;
const int maxn = 1e5+114;
int dp[maxn][2];
int sum;
signed main(){
    cin>>n>>k;
    sum=n*n%mod;
    int op1=qpow(sum,mod-2);//(1,1) 发生交换
    int op2=(2*n-2)%mod*qpow(sum,mod-2)%mod;//(1,k) k 不等于 1 发生交换
    int op3=(n-1)*(n-1)%mod*qpow(sum,mod-2)%mod;//(k,k) k 不等于 1 发生交换
    int op4=2*qpow(sum,mod-2)%mod;//1 与 [2,n] 中有球的发生交换
    int op5=(op2+mod-op4)%mod;//1 与 [2,n] 中没球的发生交换
    dp[0][0]=1;
    dp[0][1]=0;
    for(int i=1;i<=k;i++){
        dp[i][0]=(dp[i-1][1]*op4%mod+dp[i-1][0]*((op1+op3)%mod)%mod)%mod;
        dp[i][1]=(dp[i-1][0]*op2%mod+dp[i-1][1]*((op1+op5+op3)%mod)%mod)%mod;
    }
    //cout<<dp[k][0]*4%mod<<' '<<dp[k][1]*5%mod<<'\n';
    //cout<<dp[k][1]*9%mod<<'\n';;
    cout<<(dp[k][0]+dp[k][1]*((n+2)%mod)%mod*qpow(2,mod-2)%mod)%mod<<'\n';
    return 0;
}

```

另外由于转移时只与 $dp_{i-1,0/1}$ 有关所以我们实际上可以在 $O(\log k)$ 的时间复杂度下回答一组 $k$。

---

