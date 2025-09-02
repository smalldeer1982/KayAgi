# A Random Code Problem

## 题目描述

给你一个数组 $a$ 和一个整数 $k$ ，执行下面的代码：
```cpp
long long ans = 0; //定义一个初始值为 0 的长整型变量
for(int i = 1; i <= k; i++) {
	int idx = rnd.next(0, n - 1); //生成一个介于0到n-1的随机数（含 0 和 n-1）
  								 //每个数被选中的概率是相同的
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```
您需要在执行此代码后计算变量 $ans$ 的期望。

数组 $a$ 是输入时根据特殊规则生成的。

## 说明/提示

$1\le n\le10^7$

$1\le a_0,x,y<M\le998244353$

$1\le k\le17$

## 样例 #1

### 输入

```
3 10 3 5 13 88```

### 输出

```
382842030```

## 样例 #2

### 输入

```
2 15363 270880 34698 17 2357023```

### 输出

```
319392398```

# 题解

## 作者：_sys (赞：11)

考虑对所有生成的随机数序列 $[b_1, b_2, \ldots, b_k]$ 统计答案。

不难发现每个位置独立。

我们统计每个位置产生的贡献。

设 $f_{i, j}$ 为考虑所有序列进行前 $j$ 次操作使得原数组等于 $i$ 的数的个数。

$$\begin{cases}f_{i, j+1} \leftarrow (n-1)\times f_{i, j} \\ f_{i - (i \bmod j+1), j+1} \leftarrow f_{i, j}\end{cases}$$

复杂度 $O(M k)$。

又发现，$i-(i \bmod (1 \sim k))$ 并不会改变 $\frac i{\textrm{lcm}(1 \sim k)}$。所以先把 $a$ 数组 ${} \bmod \textrm{lcm}(1\sim k)$ 即可。

复杂度 $O(k\operatorname{lcm}(1 \sim k))$。

实现的不好可能会被卡常。考虑代码先统计答案再进行操作。所以最后一次操作不用考虑。只用做到 $\operatorname{lcm}(1 \sim k - 1)$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int p = 998244353, Maxn = 10000005;
int n, x, y, k, M, L = 1, a[Maxn], f[Maxn], g[Maxn];
long long ans, fn[19];
int main()
{
	scanf("%d%d%d%d%d%d", &n, &a[0], &x, &y, &k, &M), fn[0] = 1;
	for (int i = 1; i < k; i++) L = L / __gcd(L, i) * i, fn[i] = fn[i - 1] * n % p;
	for (int i = 1; i < n; i++) a[i] = (1LL * a[i - 1] * x + y) % M;
	for (int i = 0; i < n; i++) f[a[i] % L]++, (ans += 1LL * (a[i] / L) * L % p * k % p * fn[k - 1]) %= p;
	for (int i = 1; i <= k; i++)
	{
		memcpy(g, f, sizeof(int[L])), memset(f, 0, sizeof(int[L]));
		for (int j = 0; j < L; j++)
		{
			if (i != k) (f[j] += g[j] * (n - 1LL) % p) %= p, (f[j - j % i] += g[j]) %= p;
			(ans += 1LL * g[j] * j % p * fn[k - i]) %= p;
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：7)

- Update on 2022.10.5：修改表述。

> [CF1626F A Random Code Problem](https://www.luogu.com.cn/problem/CF1626F)

首先，时间复杂度关于 $n$ 只能是线性，因此我们尝试在值域上做点文章。

因为我们只关心对于前 $k - 1$ 次操作，每次操作的数被减掉了多少，所以模 $P = \operatorname{lcm}(1\sim k - 1)$ 相同的数等价。也就是说，每个数 $a_i$ 的具体值不重要，我们只关心它模 $P$ 之后的值。

设 $f_{i, j}$ 表示进行 $i$ 轮后模 $P$ 等于 $j$ 的数的个数的期望值。对于 $f_{i, j}$，若 $j$ 被选择则以 $\dfrac 1 n$ 的系数转移到 $f_{i + 1, j - (j\ \bmod\ (i + 1))}$，否则以 $1 - \dfrac 1 n$ 的系数转移到 $f_{i + 1, j}$。答案即 $\dfrac{\sum f_{i, j} j} n$，再加上 $P\lfloor \frac {a_i} P \rfloor$ 这部分的贡献 $\dfrac{\sum {P\lfloor \frac {a_i} P\rfloor}} n$，最后乘以 $n ^ k$。

时间复杂度 $\mathcal{O}(n + kP)$，其中 $P = 720720$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using uint = unsigned int;
using ld = long double;
// using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(ll x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 720720;
constexpr int mod = 998244353;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int n, a, x, y, k, M, f[N];
int sum, ans, pw[20];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> a >> x >> y >> k >> M;
  for(int i = pw[0] = 1; i <= k; i++) pw[i] = 1ll * pw[i - 1] * n % mod;
  for(int i = 0; i < n; i++) {
    if(i) a = (1ll * x * a + y) % M;
    add(sum, a / N * N), f[a % N]++;
  }
  ans = 1ll * k * sum % mod * pw[k - 1] % mod;
  for(int i = 1; i <= k; i++) {
    for(int j = 0; j < N; j++) {
      int c = f[j];
      if(!c) continue;
      add(ans, 1ll * c * j % mod * pw[k - i] % mod);
      f[j] = 1ll * c * (n - 1) % mod, add(f[j - j % i], c);
    }
  }
  cout << ans << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/10/5
author: Alex_Wei
start coding at 18:27
finish debugging at 18:37
*/
```

---

## 作者：Cutest_Junior (赞：6)

## CF1626F 【A Random Code Problem】

### 题意

+ 长度为 $n$ 的数组 $a$，初值为 $0$ 的变量 $ans$，进行 $k$ 次操作；
+ 第 $i(i\in[1,k])$ 次等概率选 $a_j$，$ans\Leftarrow ans+a_j$，$a_j\Leftarrow a_j-a_j\bmod i$；
+ 求所有可能的情况下，第 $k$ 次操作后 $ans$ 的总和（即 $E_{ans}\times n^k$）；
+ $n\le10^7$，$k\le17$，$a_i<998244353$。

### 做法

记录了我的思考过程，想认真学习优化方法的可以从头阅读，想直接看正解的麻烦空降方法三。

方法一：

$k$ 很小，容易联想到 $O(2^k)$ 枚举。对于 $a_j$，枚举选中这个数的操作集合，计算产生的贡献，稍加预处理可做到复杂度 $O(nk2^k)$，可以把算贡献和枚举集合同时完成，复杂度 $O(n2^k)$，但依然无法通过。

方法二：

把 $a_j\Leftarrow a_j-a_j\bmod i$ 称为 $a_j$ 被 $i$ 修改，注意到在最后一次操作前，一个数只可能被集合 $S\subseteq[1,16]$ 内的元素按升序依次修改，不妨设 $L=\operatorname{lcm}(1,2,\dots,16)=720720$，$x=\lfloor\frac{a_j}{L}\rfloor$，$y=a_j\bmod L$，则 $a_j=xL+y$，容易发现，无论 $a_j$ 被如何修改，$xL$ 始终不变，即 $a_j$ 被修改，相当于 $y$ 被修改。

所以把 $a_j$ 拆开算贡献，$xL$ 部分不用修改，复杂度 $O(n)$。$y$ 部分值域为 $[0,L)$，开个桶，多个数同时统计，从而节约计算时间。计算方法和方法一相同，复杂度 $O(n+L2^k)$。总复杂度 $O(n+L2^k)$，又有一定优化，但依然无法通过。

方法三：

枚举过程中，如果 $a_j$ 被修改，其实就变成另一个数，可以一起计算，从而节约计算时间。比如设 $a_j=5$，被 $2$ 修改后就等于 $4$，那 $5$ 先被 $2$ 修改后，再被 $4,5,7,13$ 依次修改，和 $4$ 被 $4,5,7,13$ 依次修改，其实可以一起统计，很自然地，就联想到动态规划。

设 $dp_{i,j}$ 为第 $i$ 次操作前，$a$ 数组中 $y=j$ 的个数。特别地，$dp_{1}$ 就是方法二中的桶。考虑转移，第 $i$ 次操作有 $n-1$ 种方法不选到某个 $y$，在下一次操作前 $y$ 不变，即 $dp_{i+1,j}\Leftarrow dp_{i+1,j}+(n-1)\times dp_{i,j}$；第 $i$ 次操作有 $1$ 种方法正好选到某个 $y$，在下一次操作前 $y$ 变为 $y-y\bmod i$，即 $dp_{i+1,j-j\bmod i}\Leftarrow dp_{i+1,j-j\bmod i}+dp_{i,j}$。最后统计答案，别忘了 $xL$ 的部分。复杂度 $O(n+Lk)$，可过。

---

## 作者：Tyyyyyy (赞：4)

# CF1626F

### 题意简述
对一个给定的长度为 $n$，下标为 $0\sim n-1$ 的数列执行以下代码：

```cpp
long long ans = 0; // create a 64-bit signed variable which is initially equal to 0
for(int i = 1; i <= k; i++)
{
  int idx = rnd.next(0, n - 1); // generate a random integer between 0 and n - 1, both inclusive
                                // each integer from 0 to n - 1 has the same probability of being chosen
  ans += a[idx];
  a[idx] -= (a[idx] % i);
}
```
求 $ans$ 的期望值 $E$ 与 $n^k$ 的乘积对 $998244353$ 取模的结果。

$1\leq n\leq 10^7,1\leq k\leq 17$。

### 题目分析
因为求的是 $E\times n^k$，所以其实只要求每种情况 $ans$ 的和。

发现 $k$ 很小，尝试分析性质。因为 $a_i\gets a_i-a_i\bmod x$ 等价于 $a_i\gets x\times\lfloor\frac{a_i}{x}\rfloor$，所以，设 $X=\operatorname{lcm}(1,2,\dots,k)$，则一个数 $a_i$ 在变换的过程中不会变得小于 $X\times\lfloor\frac{a_i}{X}\rfloor$。

因此，我们可以将所有的 $a_i$ 都表示为 $X\times\lfloor\frac{a_i}{X}\rfloor+a_i\bmod X$ 的形式。则我们可以直接先把 $ans$ 加上 $\displaystyle\sum_{i=1}^n X\times\lfloor\frac{a_i}{X}\rfloor\times k\times n^{k-1}$。因为在所有情况之和中，每个数会被选 $k\times n^{k-1}$ 次，而它们又不会小于 $X\times\lfloor\frac{a_i}{X}\rfloor$，所以可以直接加上上式，然后对剩余的 $a_i\bmod X$ 作出的贡献进行讨论。下面我们的 $a_i$ 都代指 $a_i\bmod X$。

此时所有的 $a_i$ 都小于 $X$ 了。这允许我们在值域上 dp。定义 $dp_{i,j}$ 表示数 $i$ 在仅考虑前 $j$ 次操作的情况下，在所有情况中的出现次数。

对于 $dp_{i,0}$，显然 $dp_{i,0}=cnt_i$。$cnt_i$ 表示 $i$ 在原序列 $a$ 中的出现次数。

考虑怎么转移，有两种情况：

- 第 $j+1$ 次操作选到了 $i$，则 $dp_{i-(i\bmod j+1),j+1}\gets dp_{i-(i\bmod j+1),j+1}+dp_{i,j}$。

- 第 $j+1$ 次操作没有选到 $i$，则有另外的 $n-1$ 种选择。所以 $dp_{i,j+1}\gets dp_{i,j+1}+(n-1)\times dp_{i,j}$。

最后考虑怎么计算答案。因为在第 $j+1$ 次操作中，我们选择 $i$ 的情况数量是 $dp_{i,j}$，而在之后的操作中把这里的每一种情况衍生出的情况数是 $n^{k-j-1}$，所以对于 $dp_{i,j}$，它对答案的贡献是 $i\times n^{k-j-1}\times dp_{i,j}$。

所以答案即为 $\displaystyle\sum_{i=0}^{X-1}\sum_{j=0}^{k-1} i\times n^{k-j-1}\times dp_{i,j}+ans$。$ans$ 是刚刚的 $\displaystyle\sum_{i=1}^n X\times\lfloor\frac{a_i}{X}\rfloor\times k\times n^{k-1}$。

设 $SIZE=\operatorname{lcm}(1,2,\dots,17)$，则该算法的时间复杂度为 $O(k \cdot SIZE)$，对常数要求过高。我们还可以做一个小优化：只计算 $X=\operatorname{lcm}(1,2,\dots,k-1)$。因为我们并不关心最后一次操作变化之后的 $a'_i$（它对答案没有贡献）。

现在 $SIZE$ 就可以降到 $\operatorname{lcm}(1,2,\dots,16)=720720$ 了，可以接受。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,a[10000010],x,y,k,m,lcm=1,ans;
int power(int p,int q)
{
	int t=1;
	while(q)
	{
		if(q&1)t=1ll*t*p%mod;
		p=1ll*p*p%mod;
		q>>=1;
	}
	return t;
}
int dp[1000010][20];
int main()
{
	scanf("%d%d%d%d%d%d",&n,&a[1],&x,&y,&k,&m);
	for(int i=2;i<=n;i++)a[i]=(1ll*a[i-1]*x%m+y)%m;
	for(int i=1;i<k;i++)lcm=lcm/__gcd(lcm,i)*i;
	int fac=power(n,k-1);
	for(int i=1;i<=n;i++)ans=(ans+1ll*k*fac%mod*(a[i]/lcm)%mod*lcm%mod)%mod,dp[a[i]%=lcm][0]++;
	for(int j=0;j<k;j++)
	{
		for(int i=0;i<lcm;i++)
		{
			dp[i-(i%(j+1))][j+1]=(dp[i-(i%(j+1))][j+1]+dp[i][j])%mod;
			dp[i][j+1]=(dp[i][j+1]+1ll*dp[i][j]*(n-1)%mod)%mod;
		}
	}
	for(int j=0;j<k;j++)
	{
		fac=power(n,k-j-1);
		for(int i=0;i<lcm;i++)
			ans=(ans+1ll*i*dp[i][j]%mod*fac%mod)%mod;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

暴露了我不会数数的本质。

首先，我们发现问题要求的是所有的 $n^k$ 种随机情况下所有数的贡献的总和。因此我们可以去掉题目中“期望”这个概念。

每一次我们对一个数进行了 `a[idx]-=a[idx]%i;` 这种操作，我们认为我们得到了一个新的数，而剩下的数我们也认为它会变成一个新的数，只是值不变。这样经过了 $x$ 次操作，我们就有了 $n^{x+1}$ 个数，然后我们要对它们进行处理。

在第 $x$ 次操作前，已经有了 $n^x$ 个数。每个数都会产生 $n^{k-x}$ 的贡献，因为它操作之后后面的 $k-x$ 次操作可以随便选。于是我们只想知道当前所有数的和。

那么每次操作之后，当前所有数的和都会乘上 $n$，但是要减去所有模 $x$ 的余数。因此我们向关心的是模 $x$ 余 $y$ 的数有多少个，其中 $0 \le y < x$。（其实 $x \le k-1$ 就行了因为最后一次操作没人管你。）

注意到一个数模 $x(x <k)$ 的值和模 $\operatorname{lcm}(1,2,3,\dots,k-1)$ 后再模 $x$ 的值是相等的，这样其实把值域缩小在 $720720$ 之内。

因此你可以把所有数都给模上这个值之后再用动态规划统计答案即可。

NOIp 2023，RP++！

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e7+10,MAXM=720720+10,MAXK=18,MOD=998244353;
int n,a[MAXN],x,y,k,M,ans,dp[MAXK][MAXM],mzx=720720;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>a[1]>>x>>y>>k>>M;
	ffor(i,2,n) a[i]=(x*a[i-1]+y)%M;
	int sum=0; ffor(i,1,n) sum=(sum+a[i])%MOD,dp[0][a[i]%mzx]++;
	ffor(i,1,k) {
		int mul=1;
		ffor(j,1,k-i) mul=mul*n%MOD;
		ans=(ans+mul*sum)%MOD;	
		sum=sum*n%MOD;
		ffor(j,0,mzx-1) {
			dp[i][j]=(dp[i][j]+dp[i-1][j]*(n-1))%MOD;
			sum=(sum-dp[i-1][j]*(j%i))%MOD;
			dp[i][j-j%i]=(dp[i][j-j%i]+dp[i-1][j])%MOD;
		}
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：L_zaa_L (赞：2)

## 分析
因为要乘上 $n^k$，其实总和就是这么多，说明只用表示每个答案之和。

我们可以打出最简单的暴力——$O(n 2^k)$。也就是我们直接枚举每个点被那些 $k$ 影响过即可，然后稍加组合求出答案，但这个显然是不可能过得。

考虑优化这个暴力。

枚举过程中，如果 $a_i$ 被修改，其实就变成另一个数，我们可以记录一个 $dp_{i,j}$ 表示某个数 $i$ 在第 $j$ 次操作后对答案的贡献，则不难推出 $\begin{cases}dp_{i-i\bmod(j+1),j+1} = dp_{i-i\bmod(j+1),j+1}+dp_{i,j}\\dp_{i,j+1}=dp_{i,j+1}+dp_{i,j}\times(n-1)\end{cases}$。

上面的那个表示变了之后的期望，下面的表示没变的期望。

期望时间复杂度：$O(nk)$。

顺着这个思路我们可以想到 $a_i$ 只会被一些 $k$ 影响，而它影响的范围怎么说都不会超过 $a_i \bmod \operatorname{lcm}(1,2,\dots,k)$，那么我们只需要枚举 $\operatorname{lcm}(1,2,\dots k)$ 以内的东西即可，而 $k=17$ 时，$\operatorname{lcm}$ 为 $720720$， $O(n+\operatorname{lcm}\times k)$，不会超时，那么这道题就做完了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
const int Mod=998244353;
inline int quick(int a,int b){
	int S=1;
	while(b){
		if(b&1) S=S*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return S;
}
int n,m;
int a[10000005];
int dp[720725][18];
int gg[2000005];
int ans;
signed main(){
	n=read(),a[1]=read();
	int x=read(),y=read(),k=read(),M=read(); 
	int lcm=1;
    for(int i=1;i<k;i++){
        lcm=lcm*i/__gcd(lcm,i);
    }
    for(int i=2;i<=n;i++){
        a[i]=(a[i-1]*x%M+y)%M;
    }
    int s1=quick(n,k-1);
    for(int i=1;i<=n;i++){
        (ans+=lcm*(a[i]/lcm)%Mod*k%Mod*s1%Mod)%=Mod;
        a[i]-=a[i]/lcm*lcm;
        gg[a[i]]++;
    }//需要进行拆分
    for(int i=0;i<lcm;i++) dp[i][0]=gg[i];
    for(int j=0;j<k;j++){
        for(int i=0;i<lcm;i++){
            (dp[i-i%(j+1)][j+1]+=dp[i][j])%=Mod;
            (dp[i][j+1]+=(n-1)*dp[i][j]%Mod)%=Mod;//表示数i在j轮之后的期望贡献，选不选的期望值。
        }
    }
    for(int j=0;j<k;j++){
	 	int s2=quick(n,k-j-1);
        for(int i=0;i<lcm;i++)
            (ans+=dp[i][j]*i%Mod*s2%Mod)%=Mod;
        } //统计答案
    cout<<ans;
	return 0;
}
```

---

## 作者：BINYU (赞：2)

### 前置知识

1. [期望](https://www.luogu.com.cn/problem/P2911)

2. [最小公倍数](https://www.luogu.com.cn/problem/P1029)

3. [DP](https://www.luogu.com.cn/problem/P1130)

4. [组合数](https://www.luogu.com.cn/problem/P1655)

### 题意

```cpp
long long ans = 0;
for(int i = 1; i <= k; i++)
{
	int idx = rnd.next(0, n - 1);
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```
给定 $a$ 数组通项公式 ${a}_ {i} = ( {a}_ {i - 1} \cdot x + y )\; mod \; M$ 和第一项 ${a}_ {0}$ 、大小 $n$ 、操作次数 $k$ 和 模数 $M$ 、按照上面代码运行，求 $ans$ 期望 $E \cdot {n}^{k}$

### 思路

因为每次操作是**完全随机**地选一个数，所以每一次操作都有 $k$ 种可能， $n$ 次操作就有 ${n}^{k}$ 种可能，所以 $E = \sum ans \div {n} ^{k}$ ，那么 $E \cdot {n}^{k}$ 不就是 $\sum ans$ 么？也就是说，分析到这里，本题其实是一道组合数学题，而非概率论。

我们把代码最难的一行去掉，则代码为：
```cpp
long long ans = 0;
for(int i = 1; i <= k; i++)
{
	int idx = rnd.next(0, n - 1);
	ans += a[idx];
}
```
而 $\sum ans$ 则是把每一种情况都取到，也就是把随机变为循环，递归处理。分析可得 $\sum ans ={\sum}_ {i = 1}^{k}{\sum}_ {j = 0}^{n - 1}a_ {j}\cdot n^{i - 1}\cdot n^{k-i}$ ，也就是说每一次拓展后一个数出现次数，之后可拓展数，与这个数数值的积之和。那么将代码还原
```cpp
long long ans = 0;
for(int i = 1; i <= k; i++)
{
	int idx = rnd.next(0, n - 1);
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```
可知计数方式跟原来不变，则可以用动态规划来维护

转移方程：
```cpp
//dp[i][j]表示第i次拓展后数j的出现次数
dp[i + 1][j] = dp[i + 1][j] + (n - 1) * dp[i][j];//本次不选j
dp[i + 1][j - j % i] = dp[i + 1][j - j % i] + dp[i][j];//本次选j，j变为j - j % i
```
但是，$1 < M \leq 998244353$ **炸飞！**

离散化？最坏情况为 $n$ 个数每个数可以有效更新 $k - 1$ 次，所以一共可能为 $n\cdot k$ 个数， $n \cdot k \leq 17 \times {10}^{7}$ **飞的更高**

那只能在数学方法上节省空间，时间

我们可以发现 $i | j - j \bmod i$ ，所以最后的 $a$ 序列一定都是 $[1,2,3,4,...,k-2,k-1]$ 的倍数，我们设其为 $L$ ,所以无论 $j$ 怎么减，都不会影响 $\lfloor \frac{j}{L} \rfloor \times L$ 的值，我们就可以把这部分值按去掉最后一步的公式计算，余数用动态规划来维护。设此时的余数是 $b$ 序列，则 $b_ {i} \leq L \leq 720720 ,i \in [0,n)\;$ ，开的下！

### 注意事项

1. 要开 long long

2. 两个模数不能混淆

3. 为防止被卡，建议预处理

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 998244353;//答案取模
const ll Lcm = 720720;
ll n,a[10000005],x,y,k,M,dp[25][720725],ans,sum,w[15];
int main()
{
	scanf("%lld %lld %lld %lld %lld %lld",&n,&a[0],&x,&y,&k,&M);
	for(ll i = 1;i < n;i++)
		a[i] = (a[i - 1] * x % M + y) % M;
	for(ll i = 0;i < n;i++)
		sum = (sum + (a[i] - a[i] % Lcm)) % mod,dp[1][a[i] % Lcm]++;
	w[0] = 1;
	for(int i = 1;i <= k;i++)
		w[i] = w[i - 1] * n % mod;
	ans = sum * k % mod * w[k - 1] % mod;//预处理L的倍数部分
	for(ll i = 1;i <= k;i++)//DP
	{	for(ll j = 0;j < Lcm;j++)
		{
			dp[i + 1][j] = (dp[i + 1][j] + ((n - 1) * dp[i][j] % mod)) % mod;
			dp[i + 1][j - j % i] = (dp[i + 1][j - j % i] + dp[i][j]) % mod;
			ans = (ans + (dp[i][j] * w[k - i] % mod * j % mod)) % mod;
		}
	}
	printf("%lld",ans);
}

```


---

## 作者：User_Unauthorized (赞：1)

## 题意

给定长度为 $n$ 的数组 $a$ 和一个整数 $k$ ，执行下面的代码：
```cpp
long long ans = 0; //定义一个初始值为0的长整型变量
for(int i = 1; i <= k; i++) {
	int idx = rnd.next(0, n - 1); //生成一个介于0到n-1的随机数（含0和n-1）
  								 //每个数被选中的概率是相同的
	ans += a[idx];
	a[idx] -= (a[idx] % i);
}
```

求代码运行结束后 $ans$ 的期望值 $E$ 与 $n^k$ 相乘的结果，即 $E \times n^k$。

（$1 \le n \le 10^7, 1 \le k \le 17$）。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1626F.html)**

考虑计算 $ans$ 的期望值 $E$，最后使之与 $n^k$ 相乘。设 $P = \operatorname{lcm}\left(1 \sim k - 1\right)$，可以看出数组 $a$ 中的元素 $a_i$ 最多会被减去 $a_i \bmod P$。因此若将 $a_i$ 拆分为两部分：$a_i = \left\lfloor\dfrac{a_i}{P}\right\rfloor \times P + a_i \bmod P$，前半部分的贡献是不变的，为

$$k \times \dfrac{P \times \sum\limits_{i = 0}^{n - 1}\left\lfloor\dfrac{a_i}{P}\right\rfloor}{n}$$

下面着重考虑后半部分的贡献，因为值域较小，故考虑将其作为 $\texttt{DP}$ 的状态。设 $f_{i, j}$ 为在第 $i$ 次操作后模 $P$ 为 $j$ 的期望元素个数。有转移

$$\begin{aligned}
f_{i, j - \left(j \bmod i\right)} &\leftarrow \dfrac{1}{n} \times f_{i - 1, j}\\
f_{i, j} &\leftarrow \left(1 - \dfrac{1}{n}\right) \times f_{i - 1, j}
\end{aligned}$$

计算完成 $f$ 数组后即可快速计算前半部分的贡献，为

$$\sum\limits_{i = 0}^{k - 1} \dfrac{\sum\limits_j j \times  f_{i, j}}{n}$$

总复杂度 $\mathcal{O}(n + kP)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

valueType lcm(valueType a, valueType b) {
    return a / std::__gcd(a, b) * b;
}

int main() {
    valueType N, A0, X, Y, K, M;

    std::cin >> N >> A0 >> X >> Y >> K >> M;

    ValueVector source(N);

    source[0] = A0;

    for (valueType i = 1; i < N; ++i)
        source[i] = (source[i - 1] * X + Y) % M;

    valueType P = 1;

    for (valueType i = 2; i < K; ++i)
        P = lcm(P, i);

    ValueMatrix F(K, ValueVector(P, 0));

    for (auto const &iter: source)
        ++F[0][iter % P];

    valueType const InvN = pow(N, MOD - 2), reverseN = sub(1, InvN);

    for (valueType k = 1; k < K; ++k) {
        for (valueType i = 0; i < P; ++i) {
            Inc(F[k][i - i % k], mul(F[k - 1][i], InvN));
            Inc(F[k][i], mul(F[k - 1][i], reverseN));
        }
    }

    valueType ans = 0;

    for (valueType k = 0; k < K; ++k)
        for (valueType i = 0; i < P; ++i)
            Inc(ans, mul(F[k][i], i));

    for (auto const &iter: source)
        Inc(ans, mul(iter / P * P, K));

    Mul(ans, InvN);

    Mul(ans, pow(N, K));

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

**前提**

求的是 $E×n^k$，其实只要求每种情况 $ans$ 的和。

加上每一次 $idx$ 随机到的数都是 $i$，那么 $a_i$ 最终会变成 $a_i-a_i\bmod  L~(L=\text{lcm}(1,\dots,k-1))$。所以可以得知，每个 $a_i$ 最后都不会小于 $\left\lfloor\dfrac{a_i}{L}\right\rfloor \times L$。同时，因为求的是所以情况之和，所以我们可以知道每个 $a_i$ 出现的次数（或者说是概率）为 $\frac{k}{n}$。我们可以先把这个部分加到答案中，即 $\frac{k}{n} \times {P \times \sum\limits_{i = 0}^{n - 1}\left\lfloor\dfrac{a_i}{P}\right\rfloor}$，乘上 $n^k$ 即 $n^{k-1} \times {P \times \sum\limits_{i = 0}^{n - 1}\left\lfloor\dfrac{a_i}{P}\right\rfloor}$。



将每个 $a_i$ 都去掉 $\left\lfloor\dfrac{a_i}{L}\right\rfloor \times L$ 部分后，剩下的就是 $a_i\bmod L$ 了。那么我们可以计算出 $L=12,252,240$，所以现在的 $a_i$ 的值域已经减小到我们可以存下的范围了。

**dp 部分**

现在我们来考虑处理 $a_i\bmod L$ 部分的贡献了。那么我们是怎么样想到 dp 的呢？

我们考虑 $a_i$ 被修改（即变成 $a_i-a_i\bmod t$），其实就变成另一个数，可以一起计算，从而节约计算时间。比如设 $a_i=5$，被 $t=2 $ 修改后就等于 $4$，那 $5 $ 先被 $2 $ 修改后，再被一串数 $t_1\sim t_s $ 依次修改，和 $4 $ 被一串数 $t_1\sim t_s$ 依次修改是可以一起计算的。即 $5$ 可以转移到 $4$，那么这很明显就是动态规划的转移了。因此我们可以使用动态规划。

定义状态：

定义 $dp_{i,j}$ 表示数 $i$ 在前 $j$ 次操作中，在所有情况中的出现次数。

初始值：

对于 $dp_{i,0}$，显然 $dp_{i,0}=$ $i$ 在原序列 $a$ 中的出现次数。

转移：

- 第 $j+1$ 次操作选到了 $i$，那么 $i$ 就变成了 $i-(i\bmod j+1)$。$dp_{i-(i\bmod j+1),j+1}\gets dp_{i-(i\bmod j+1),j+1}+dp_{i,j}$。

- 第 $j+1$ 次操作没有选到 $i$，则有另外的 $n-1$ 种选择（记住我们的 dp 定义为前 $j$ 次后的所有情况次数之和）。$dp_{i,j+1}\gets dp_{i,j+1}+(n-1)\times dp_{i,j}$。

统计答案：

在第 $j+1 $ 次操作中，我们选择 $i $ 的情况数量是 $dp_{i,j}$​，从这种情况出发，我们可以衍生出 $n^{k-j-1}$ 种情况。对于这 $n^{k-j-1}$ 种情况，在第 $j+1$ 次操作时 $i$ 都做出一次贡献，所以对于 $dp_{i,j}$​，它对答案的贡献是 $i×n^{k-j-1}×dp_{i,j}$​。

**答案**

最后的答案就是 $n^{k-1} \times {P \times \sum\limits_{i = 0}^{n - 1}\left\lfloor\dfrac{a_i}{P}\right\rfloor}+\sum\limits_{i=0}^{L-1}\sum\limits_{j=0}^{k-1}i×n^{k-j-1}×dp_{i,j}$。

**优化**

如果按照上面的来计算，那么我们都时间复杂度就是 $O(kL)$，很悬（$2\times 10^8$ 数量级），所以我们考虑优化。我们知道，当 $k=17$ 时一定是最后一次操作，后面不会再有转移了。所以我们没有必要把 $L$ 算上 $17$，所以我们让 $L=\text{lcm}(1,\dots,16)$ 即可。

## 代码

```C++
/*
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define pii pair<int,int>

///----///
#define rd read()
inline int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
inline void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}

///----///
const int N = 1e7 + 5;
const int M = 1e6 + 5;
const int MOD = 998244353;
const double eps=1e-7;


int dp[M][20];
int n,a[N],x,y,k,m,lcm=1,ans;


int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=(res*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return res;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


signed main(){
	
	n=rd,a[1]=rd,x=rd,y=rd,k=rd,m=rd;

	//初始化
	for(int i=2;i<=n;i++)a[i]=(a[i-1]*x%m+y)%m;
	for(int i=1;i<k;i++)lcm=lcm/gcd(lcm,i)*i;

	//计算前部分，即固定的那部分
	int fac=ksm(n,k-1);
	for(int i=1;i<=n;i++){
		ans=(ans+k*fac%MOD*(a[i]/lcm)%MOD*lcm%MOD)%MOD;
		a[i]%=lcm;
		dp[a[i]][0]++;//dp初始状态设定
	}

	//计算后部分
	for(int j=0;j<k;j++){
		for(int i=0;i<lcm;i++){//dp细节很多
			dp[i-(i%(j+1))][j+1]=(dp[i-(i%(j+1))][j+1]+dp[i][j])%MOD;
			dp[i][j+1]=(dp[i][j+1]+dp[i][j]*(n-1)%MOD)%MOD;
		}
	}
	for(int j=0;j<k;j++){
		fac=ksm(n,k-j-1);
		for(int i=0;i<lcm;i++)ans=(ans+i*dp[i][j]%MOD*fac%MOD)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
```




---

## 作者：Yansuan_HCl (赞：0)

每次减去 $\bmod\ i$ 的操作只会影响 $\{x \bmod 1, x \bmod 2, \ldots, x \bmod 16\}$，而后面这个 $16$ 元组只有 $720720$ 个。

把每个 $a_i$ 拆成 $b_i=a_i \bmod 720720$ 与 $h_i = a_i - b_i$ 两部分。考虑对所有 $b_i$ 拆贡献 DP。第 $i$ 次操作中，$b_i$ 有 $1/n$ 的概率变成 $b_i - b_i \bmod i$，有 $(n-1)/n$ 的概率不变。

令 $f_i(j)$ 为第 $i$ 次操作之后某个 $b$ 是 $j$，第 $j+1 \ldots k$ 次操作期望对答案的贡献。考虑第 $i+1$ 次操作，则：

$$f_i(j)=\frac {j+f_{i+1}(j - j \bmod (i+1))} n+\frac{n-1}{n}f_{i+1}(j)$$

则每个 $b_i$ 的贡献就是 $f_0(b_i)$。

$h$ 的贡献显然能快速计算。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define IC isdigit(c)
#define GC c=getchar()
void rd(auto &x) { x = 0; char GC; bool f = 0;
	for (; !IC; GC) f |= c == '-';
	for (; IC; GC) x = x * 10 + c - 48;
	if (f) x = -x;
}
void rd(auto &x, auto &...y) { rd(x); rd(y...); }
#define U(i,l,r) for (int i(l),END##i(r); i<=END##i; ++i)
#define D(i,l,r) for (int i(l),END##i(r); i>=END##i; --i)
using ll = long long;

const int N = 10000007, M = 720720;
const ll P = 998244353;
ll qpow(ll x, ll t) { ll v = 1;
	for (; t; (x *= x) %= P, t >>= 1) if (t & 1)
		(v *= x) %= P;
	return v;
}
ll fac[N], ifac[N]; 
void getF() {
	fac[0] = ifac[0] = 1;
	U (i, 1, N - 1) fac[i] = fac[i - 1] * i % P;
	ifac[N - 1] = qpow(fac[N - 1], P - 2);
	D (i, N - 2, 1) ifac[i] = ifac[i + 1] * (i + 1) % P;
}
ll Comb(int n, int m) { return fac[n] * ifac[n - m] % P * ifac[m] % P; }

int n, k, a[N];
ll invN, coef;
void gen() {
	ll x, y, m;
	rd(n, a[0], x, y, k, m);
	U (i, 1, n - 1)
		a[i] = (a[i - 1] * x + y) % m;
	invN = qpow(n, P - 2);
	coef = k * invN % P;
}

ll f[19][M]; // 前 i 次操作后该数为 j, 不含操作 i, 对答案的贡献 
void dp() {
	D (i, k - 1, 0) {
		U (j, 0, M - 1) {
			f[i][j] += invN * (j + f[i + 1][j - j % (i + 1)]) % P;
			f[i][j] += (P + 1 - invN) * (f[i + 1][j]) % P;
			f[i][j] %= P;
		}
	}
}

int main() {
	
	getF();
	gen();
	dp();
	ll ans = 0;
	U (i, 0, n - 1) {
		ans += coef * (a[i] - a[i] % M) % P;
		ans += f[0][a[i] % M];
		ans %= P;
	}
	cout << ans * qpow(n, k) % P << endl;
}
```

注意要输出 $E\cdot n^k$ 的值。注意 `P-1` 和 `P` 都不是 $1$。

---

