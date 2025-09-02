# Crypto Lights

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523E/5925bbb9bbb86a373ea1b1a63885d119a4446a59.png)To monitor cryptocurrency exchange rates trader William invented a wonderful device consisting of $ n $ lights arranged in a row. The device functions in the following way:

Initially, all lights on William's device are turned off. At the beginning of a new iteration the device randomly, with a uniform distribution, picks a light that is turned off and turns it on, telling William which cryptocurrency he should invest in. After this iteration if any $ k $ consecutive lights contain more than one turned on light, then the device finishes working.

William doesn't like uncertainty, so he wants you to calculate the expected value of the number of lights that are turned on in the device after it finishes working.

## 说明/提示

Explanation of the first sample test case:

Let's write out all possible sequences of light toggles, which will make the device complete its operation:

1. $ (1, 2) $ — $ 2 $ lights are turned on
2. $ (1, 3, 2) $ — $ 3 $ lights are turned on
3. $ (2, 1) $ — $ 2 $ lights are turned on
4. $ (2, 3) $ — $ 2 $ lights are turned on
5. $ (3, 2) $ — $ 2 $ lights are turned on
6. $ (3, 1, 2) $ — $ 3 $ lights are turned on

Then the final expected value will be equal to $ \frac{2}{6} $ + $ \frac{3}{6} $ + $ \frac{2}{6} $ + $ \frac{2}{6} $ + $ \frac{2}{6} $ + $ \frac{3}{6} $ = $ \frac{14}{6} $ = $ \frac{7}{3} $ .

Then the required output will be $ 333333338 $ , since $ 333333338 \cdot 3 \equiv 7 \pmod{10^9+7} $ .

## 样例 #1

### 输入

```
3
3 2
15 2
40 15```

### 输出

```
333333338
141946947
329622137```

# 题解

## 作者：FjswYuzu (赞：19)

考虑计算答案。采用另一篇题解的解法使用期望的定义与性质辅助考虑。那篇题解对我也很大启发帮助。

显然期望等于概率乘权值之和。定义 $p_i$ 为点亮 $i$ 颗灯结束操作的概率。那么显然有期望：

$$
E = \sum_{i=1}^{n} p_i i
$$

注意到这个 $i$，那么对 $p$ 做一个后缀和，即令 $s_i = \sum_{j=i}^n p_i$。那么有：

$$
E = \sum_{i=1}^n s_i
$$

考虑构造这样的一个互不影响的部分，并使得意义和定义能够对应 $E$ 和 $s_i$。有一个比较显然的思路是 $s_i$ 的意义是点亮 $i-1$ 颗灯还是没结束的概率。

思考到这里的原因是，我们只有保证第 $i-1$ 颗灯点亮还是无法结束，才能保证点亮 $i$ 一直到 $n$ 颗的某一颗时结束。

于是对应完成，考虑计算 $s_i$。注意到 $s_i$ 的定义是，点亮了 $i-1$ 颗灯还是无法结束的概率。

考虑采用组合定义。显然一共有 $\dbinom{n}{i-1}$ 种选法。合法的选法应该先排除距离之间的影响。我们假设已经选好了点亮的灯泡的位置，剩下的我们只需要在点亮的两颗灯泡里面插入 $k-1$ 个不亮的灯泡就行了。

这样的话一共有 $n-(k-1)\times(i-2)$ 个合法的位置，选择 $i-1$ 个，即共有 $\dbinom{n-(k-1)\times(i-2)}{i-1}$，得到：

$$
s_i = \dfrac{\dbinom{n-(k-1)\times(i-2)}{i-1}}{\dbinom{n}{i-1}}
$$

计算即可。注意特判 $i=0$ 的时候 $s_i$ 为 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL fac[100005],ifac[100005];
LL QuickPow(LL x,LL p)
{
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=(ans*base)%MOD;
		base=(base*base)%MOD;
		p>>=1;
	}
	return ans;
}
LL C(LL n,LL m){if(n<m)	return 0;return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
int main(){
	fac[0]=1;
	for(LL i=1;i<=100000;++i)	fac[i]=fac[i-1]*i%MOD;
	ifac[100000]=QuickPow(fac[100000],MOD-2);
	for(LL i=99999;~i;--i)	ifac[i]=ifac[i+1]*(i+1)%MOD;
	LL T;
	scanf("%lld",&T);
	while(T-->0)
	{
		LL n,k;
		scanf("%lld %lld",&n,&k);
		LL ans=1;
		for(LL i=1;i<n;++i)	(ans+=C(n-(i-1)*(k-1),i)*QuickPow(C(n,i),MOD-2))%=MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：walk_alone (赞：9)

写在前面：感谢 SyadouHayami 对我的一些指导与帮助。本题解主要是对 SyadouHayami 题解的一些补充与说明。

首先构造一个概率 $p_i$：最终点亮了 $i$ 盏灯后流程结束的概率。这样便于我们去计算最后的期望：

$$E=\sum_{i=1}^{n} ip_i $$

但是这个概率并不好计算：因为 $p_i$ 并没有与灯的组合联系起来，并且很难找到递推式，因而我们考虑改造一下这个式子。

构造 $\displaystyle s_i=\sum_{j=i}^{n} p_j$， 这样$\displaystyle E=\sum_{i=1}^{n} s_i$。此处为数学上的变形，可以使用后缀和去理解。

考虑 $s_i$ 的实际意义：合法放置 $i-1$ 盏灯的概率。由定义，$s_i$ 为从 $i$ 到 $n$ 的 $p_j$ 概率和，它代表了所有的放置了大于等于 $i$ 盏灯的概率。但是它不一定放置了符合要求的 $i$ 盏灯——我们只能保证它成功执行了第 $i-1$ 步，而不能保证第 $i$ 步被成功执行，因而它代表了成功执行 $i-1$ 步的概率，也就是成功放置了 $i-1$ 盏灯的概率。后面任意步（如第 $j$ 步，满足 $j \geq i$）失败了无法继续都可以在 $s_i$ 中找到对应的概率—— $p_{j-1}$。

这样这个概率就简化成为了单个、无需转移的状态并且是一个古典概型。

考虑这个古典概型。显然所有的方案总数为 $\dbinom {n}{i-1}$—— $n$ 个灯里选取 $i-1$ 个灯亮。再考虑合法的方案总数。此处有三个理解：

1. 考虑先将状态转化成合法的再计算方案数。我们先把 $i-1$ 盏亮的灯放在一起，然后向点亮的灯中间的 $i-2$ 个空隙每个插入 $k-1$ 盏不亮的灯。这样就有 $(i-2)(k-1)+(i-1)$ 盏已经被安排好的亮与不亮的灯，而且这个方案一定合法。接下来，把剩余的 $j=n-[(i-2)(k-1)+(i-1)]$ 盏不亮的灯插入到 $i-1$ 盏亮的灯构成的 $i$ 个空隙中。问题抽象化为 $j$ 个相同的球放入 $i$ 个不同的箱子中，每个箱子允许空放，问方案总数。这是一个隔板法的经典题：先预支 $i+1$ 个球，用作每个箱子的打底；再用正常的隔板法求出每个箱子至少一个球的方案总数，再将每个箱子预支的 $1$ 个球收回。因而方案总数为 $\dbinom {i+j-1}{i-1}=\dbinom {n-(i-2)(k-1)}{i-1}$。

2. （SyadouHayami 题解的做法，只是大概理解）考虑放完灯之后空位分布。为了保证方案合法，可以放亮的灯的地方并不是 $n$，而是 $n-(i-2)(k-1)$——要保证相距至少为 $k-1$。因而最后的方案数就是在这些合法放灯的位置随机选取 $i-1$ 个—— $\dbinom {n-(i-2)(k-1)}{i-1}$。

3. 地道的插板法：同方法 1 一样将 $i-1$ 个亮着的灯摆在一起。问题转化为剩余不亮的 $n-(i-1)$ 盏灯插入到亮着的 $i-1$ 盏灯构成的 $i$ 个空隙中，即 $n-(i-1)$ 个相同的球放入 $i$ 个不同的箱子中，但是对于首尾两个箱子，可以空放；中间的 $i-2$ 个箱子，必须放置 $k-1$ 个球。提前满足要求——对于首尾两个箱子，各预支一个球用于满足要求；中间的 $i-2$ 个箱子，提前各放置 $k-2$ 个球，使得每个箱子至少都有 $1$ 个球，这样才符合插板法的要求。因而总球数变为 $n-(k-2)(i-2)+2$，使用插板法可得方案总数为 $\dbinom {n-(i-2)(k-1)}{i-1}$。

因而 $\displaystyle s_i=\frac{\dbinom {n-(i-2)(k-1)}{i-1}}{\dbinom {n}{i-1}}$。然后就可以使用逆元求解，代码可以见 SyadouHayami 的题解。

---

## 作者：OMG_wc (赞：5)

题意： 

给定  $n,m$，由 $1\sim n$ 构成的排列一共有 $n!$ 个，每一个排列存在一个有效值 $k$ 定义为：

前 $k-1$ 个数中，任意两个数的差的绝对值 $\ge m$ ，第 $k$ 个数会和之前某个数的差的绝对值 $<m$ 。

求任意选一个排列有效值的期望，也就是 $\frac{\sum k}{n!}$ 。



显然可以对每个有效值 $i$，求出相应的概率为 $P_i$ ，那么最终答案就是 $\sum\limits_{i=1}^nP_ii$ 。不过 $P_i$ 有点不太好算，因为第 $i$ 步终止的方案数很难算。

稍微变形一下，$\sum\limits_{i=1}^nP_ii=\sum\limits_{i=1}^n\sum\limits_{j=i}^n P_i=\sum\limits_{i=1}^n S_i$  ，改成计算后缀概率和 $S_i$ 。

仔细想想，$S_i$ 就是相当于是到了第 $i-1$ 步还活着的概率，这样就不用计算终止步的概率了。

要计算 $S_i$， 先考虑在 $n$ 个位置上选 $i-1$ 个位置，满足相邻所选的位置之间至少有 $m-1$ 个空，再乘以每次选这些位置的概率，

即 $\frac{i-1}{n}\times\frac{i-2}{n-1}\times\frac{i-3}{n-2}\times\cdots\times\frac{1}{n-i+2}$ 。

$i-1$ 个位置，除了头尾以外，中间两两之间有 $m-1$ 个空是不能选的，把这样位置去掉（理解成最后再填回去），还剩下 $n-(m-1)(i-2)$ 个位置，所以方案数为 $C_{n-(m-1)(i-2)}^{i-1}$。

于是最后答案为 $\sum\limits_{i=1}^n \frac{C_{n-(m-1)(i-2)}^{i-1}}{C_{n,i-1}}$ 。





---

## 作者：chroneZ (赞：4)

记点亮 $i$ 盏灯后停止的概率为 $p_i$，则答案可表示为 $E = \sum \limits_{i = 1} ^ n p_ii$，问题在于 $p_i$ 不便于计算。

这里有一个 trick 是，记 $s_j = \sum\limits_{i = j} ^ n p_i$，则 $E = \sum \limits_{i = 1} ^ n s_i$。$s_i$ 的实际意义是，点亮 $i - 1$ 盏灯后仍未停止的概率。首先钦定 $i - 1$ 盏灯，然后在 $i - 2$ 个空隙中各插入 $k - 1$ 盏灯保证合法，剩下的灯运用隔板法任意分配，得到合法方案数为 $\binom{n - (i - 2)(k - 1)}{i - 1}$。由于插入是有序的，还应乘上一个 $(i - 1)!$。因此 $s_i = \dfrac{\binom{n - (i - 2)(k - 1)}{i - 1}(i-1)!}{\binom{n}{i - 1}(i-1)!}$。

可能有细心的读者注意到，总方案数显然不应该是 $\binom{n}{i - 1}$ 啊，因为可能在点亮 $i - 1$ 盏灯之前就停止了。其实这是一个关于概率问题的一个典型认知误解（据说这题能被评到 \*2600 也是因为这一点），详细可参考[这篇讨论](https://www.luogu.com.cn/discuss/557595)。一定要注意，**决策与决策间并不是等概率的**！换言之，记当前被点亮的灯集为 $S$（此处认为 $S$ 是有序集，即 $S_1$ 表示第一个被点亮的灯，以此类推），并记 $i = |S|$，则在不考虑是否合法的情况下，点亮这个灯集的概率是 $\dfrac{1}{n ^ {\underline{i}}}$，而当我们考虑点亮另一个更大的灯集时，做出这个决策的概率本身就会更小。这意味着我们不能仅看方案数来进行计算，而是应该对方案数配上一个权值后再进行计算。就以 $s_i = \dfrac{\binom{n - (i - 2)(k - 1)}{i - 1}(i-1)!}{\binom{n}{i - 1}(i-1)!}$ 为例，分子部分是以 $\dfrac{1}{n ^ {\underline{i - 1}}}$ 为单位的，而如果分母部分中体现的方案在点亮 $i - 1$ 盏灯前就停止了，它的单位将不同于分子部分。为了统一单位，我们考虑强制将分母部分的单位统一为 $\dfrac{1}{n ^ {\underline{i - 1}}}$，这样做就等价于，若在点亮某盏灯后本应停止，但强制插入完 $i - 1$ 个后再停止，因此便能解释为什么分母部分是 $\binom{n}{i - 1}(i-1)!$ 了。

当然还有另一种更简明的想法，点亮一个有序灯集的概率为 $\dfrac{1}{n ^ {\underline{i}}}$，那么我们直接枚举合法的有序灯集，并乘上这个概率 $\dfrac{1}{n ^ {\underline{i}}}$，同样可以得到 $s_i = \binom{n - (i - 2)(k - 1)}{i - 1}(i-1)! \times \dfrac{1}{n ^ {\underline {i - 1}}} = \dfrac{\binom{n - (i - 2)(k - 1)}{i - 1}}{\binom{n}{i - 1}}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 2e5 + 10, mod = 1e9 + 7;

inline i64 ksm(i64 a, i64 b){
	i64 r = 1;
	while(b){
		if(b & 1) r = r * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return r;
}

inline i64 inv(i64 x) {return ksm(x, mod - 2);}

i64 fact[N], ifact[N];

inline i64 binom(i64 n, i64 m) {return fact[n] * ifact[m] % mod * ifact[n - m] % mod;}

int main(){
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	
	fact[0] = ifact[0] = 1;
	for(int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % mod;
	ifact[N - 1] = inv(fact[N - 1]);
	for(int i = N - 2; i > 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % mod;

	int T; cin >> T;
	while(T--){
		int n, k; cin >> n >> k;
		i64 ans = 0;
		for(int i = 1; i <= n; i++){
			if(n - (i - 2) * (k - 1) < i - 1) break;
			ans += binom(n - (i - 2) * (k - 1), i - 1) * inv(binom(n, i - 1)) % mod;
			ans %= mod;
		}
		cout << ans << "\n";
	}
}
```

---

## 作者：RyexAwl (赞：2)

本博客 [一些杂题](https://www.luogu.com.cn/blog/maxsama/sth-problem) 内收录的第一道题就是 $\text{CLJ}$ 课件内期望和概率的转化的一个例子。

（[[杂题]HDU4624 Endless Spin 期望与概率 问题转化 容斥 DP](https://www.luogu.com.cn/blog/maxsama/HDU4624-sol)）

~~世 界 线 收 束~~

---

在这里回忆一下具体过程：

令 $p_i$ 为恰好第 $i$ 次放完停止的概率。

$$
E=\sum_{i=1}^np_i\times i=\sum_{i=1}^np_i\sum_{1\le j\le i} 1=\sum_{i=1}^n\sum_{1\le j\le i}p_i =\sum_{i=1}^n \sum_{j=i}^n p_j
$$

令

$$
P[i]=\sum_{j=i+1}^n p_j
$$

那么

$$
E=\sum_{i=0}^{n-1} P[i]
$$

考虑 $P[i]$ 的组合意义：概率的不交并。

因此直接转化成补集，就等价于 $i$ 次操作后合法的概率。

具体地：考虑一下 $P[i]$ 的组合意义。

那其实就是恰好选 $i+1$ 个后不合法，恰好选 $i+2$ 个后不合法...的概率的和。

并且任意两个事件是不交的，因此代表的一定是一个不交并。

那么其组合意义即：选 $i$ 个后仍然合法的概率。

（如果选 $i$ 个仍然合法，那么不合法时恰好选的个数一定严格大于 $i$）


$n$ 个球中染色 $i$ 个，两两距离大于 $k$ 的方案数是个经典问题，因此很容易得出：

$$
P[i]=\binom{n-(i-1)\times (k-1)}{i}\times \frac{i!(n-i)!}{n!}
$$


```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl
#define int long long

namespace wxy{

const int mod = 1e9 + 7,N = 3e5 + 15;

int fac[N],invfac[N];

inline int C(int n,int m){return n<m?0:fac[n]*invfac[m]%mod*invfac[n-m]%mod;}

inline void init(){
    fac[0]=invfac[0]=invfac[1]=1;
    for(int i=1;i<=100005;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=2;i<=100005;i++)invfac[i]=(mod-mod/i)*invfac[mod%i]%mod;
    for(int i=2;i<=100005;i++)invfac[i]=invfac[i-1]*invfac[i]%mod;
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    int t; gin >> t; init();
    while(t--){
        int n,k; gin >> n >> k;
        int ans = 1;
        rep(i,1,n-1)
            if (n-(i-1)*(k-1)>=0) ans = (ans + C(n-(i-1)*(k-1),i)*invfac[n]%mod*fac[n-i]%mod*fac[i]%mod) % mod;
        prt << ans << edl;
    }
}

}signed main(){wxy::main(); return 0;}


```





---

## 作者：Purslane (赞：0)

# Solution

对于每个 $i$，如何求出时刻 $i$ 还没结束的概率？

为了方便用古典概型解释，就算过程停止了我们也假装他还在继续操作。

时刻 $i$ 还没有结束，相当于 $i$ 盏灯距离都大于等于 $k-1$。所以不妨将这 $k-1$ 个数先删去，总的概率为：

$$
\dfrac{\binom{n-(i-1)(k-1)}{i}}{\binom{n}{i}}
$$

因此答案就是 $1 + \sum_{1 \le i \le n} \dfrac{\binom{n-(i-1)(k-1)}{i}}{\binom{n}{i}}$。

暴力算即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MOD=1e9+7;
int T,n,k,frac[MAXN],inv[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {return frac[d]*inv[u]%MOD*inv[d-u]%MOD;	}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	frac[0]=1;
	ffor(i,1,100000) frac[i]=frac[i-1]*i%MOD;
	inv[100000]=qpow(frac[100000],MOD-2);
	roff(i,99999,0) inv[i]=inv[i+1]*(i+1)%MOD;
	cin>>T;
	while(T--) {
		cin>>n>>k;
		int ans=1;
		ffor(i,1,n) {
			if(n-(i-1)*(k-1)<i) break ;
			ans=(ans+C(i,n-(i-1)*(k-1))*qpow(C(i,n),MOD-2)%MOD)%MOD;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：To_our_starry_sea (赞：0)

## Part1 分析
本题实际上并没有用到特别复杂的数学知识与推导，而更多的要求有比较强的分析题目能力与运用常见数学模型的能力。这也是本篇题解想要说明的。

首先，我们需要注意本题并不是一个古典概型，也就是说概率是建立在决策过程中的，从而导致每种情况的概率**不同**，从[这条讨论](https://www.luogu.com.cn/discuss/557595)可以很好的看出这一点。

接着，我们可以思考一个更简单的问题，如果已知序列长 $n$，点亮了 $m$ 盏灯且操作**还未**结束。我们可以发现，因为不存在长度为 $k$ 的连续段使得点亮的灯数量大于一个，那么我们可以利用插板法，在 $n$ 个位置中插入 $(k - 1) \times (m - 1)$ 个位置作为不亮的灯泡，也就是说，剩下了 $n - (k - 1) \times (m - 1)$ 个合法的位置，选其中 $m$ 个点亮，也就是说贡献为 $\dbinom{n-(k-1)\times(m - 1)}{m}$。

现在，我们回到题目，显然可以设期望的表达式为 $E = \sum_{i = 1}^n p_i \times i$。其中 $p_i$ 表示经过 $i$ 次操作**恰好**结束的概率。然而我们发现，这样定义的 $p_i$ 难以计算。类似 @pomelo_nene 的做法，我们可以设 $ans_i = \sum_{j = i} ^ n p_i$，则 $E = \sum_{i = 1}^n ans_i$。我们可以发现，此时 $ans_i$ 的意义即可对应为点亮了 $i - 1$ 盏灯且还未结束的概率，容易发现，此时其满足古典概型，也就是上文所述的弱化的问题。可以得到：

$$
ans_i = \frac{\dbinom{n-(k-1)\times(i - 2)}{i - 1}}{\dbinom{n}{i - 1}}
$$

综上所述，问题得以求解。

## Part2 代码实现

值得注意的是，当 $i = 1$ 时需要特判 $ans_1 = 1$，同时建议在求解组合数的函数内部特判 $\dbinom{n}{m}$ 而 $n < m$ 的情况，避免错误。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 100005;
const ll MOD = 1e9 + 7;
int T, n, k;
ll ni[MAXN], jc[MAXN];
inline ll qmi(int a, int b) {
	ll ans = 1, res = a;
	while (b) {
		if (b & 1) ans = ans * res % MOD;
		res = res * res % MOD;
		b >>= 1;
	}
	return ans;
}
inline ll C(int n, int m) {
	if (n < m) return 0;
	else return jc[n] * ni[m] % MOD * ni[n - m] % MOD;
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
    ni[0] = ni[1] = jc[0] = jc[1] = 1;
    for (ll i = 2; i <= 100000; i++) ni[i] = (MOD - MOD / i) * ni[MOD % i] % MOD, jc[i] = jc[i - 1] * i % MOD;
    for (int i = 2; i <= 100000; i++) ni[i] = ni[i] * ni[i - 1] % MOD;
    T = read();
    while (T--) {
    	n = read(), k = read();
    	ll ans = 1;
    	for (int i = 2; i <= n; i++) {
            if (n - (k - 1) * (i - 2) < i - 1) break;
            ans = (ans + C(n - (k - 1) * (i - 2), i - 1) * qmi(C(n, i - 1), MOD - 2) % MOD) % MOD;
        }
    	printf("%lld\n", ans);
	}
    return 0;
}
```

---

## 作者：syysongyuyang (赞：0)

拆贡献，根据期望的定义，则 $Ans=\sum\limits_{i=1}^n p_i i$，其中 $p_i$ 表示点亮 $i$ 盏灯且合法的概率。

转化为求点亮 $i$ 盏灯的状态的贡献，贡献为 $p_i \times i$。考虑对 $p_i$ 求后缀和得到 $s_i$，则 $Ans= \sum\limits_{i=1}^n s_i$。

考虑 $s_i$ 的实际意义。可以得到 $f_i$ 表示 $p_i$ 的前缀和，容易发现 $f_i$ 表示点亮 $\leq i$ 盏灯且合法的概率。则 $s_{i} = (\sum\limits_{j=1}^n p_j) - f_{i-1}$。可以发现其表示 $\forall j \in [1,i-1]$，都不会取得合法状态。所以 $s_i$ 表示取了 $i-1$ 个后仍然非法的概率。

考虑怎样求出合法的 $s_i$。总方案数为 $\binom {n} {i-1}$，考虑先构造一组状态，使得 $i-1$ 盏灯亮，并且两两之间隔了 $k-1$ 盏灯。考虑将剩下 $n-(i-2)\times (k-1) -i+1$ 盏灯插入 $i-1$ 盏灯的空隙以及两侧中，注意到灯相同盒不同，则为经典的可空插板法，答案为 $\binom {n-(i-2)\times(k-1) - i+1+i-1} {i-1} = \binom {n-(i-2)\times(k-1)} {i-1}$，统计答案即可。时间复杂度 $\Theta(n \log p)$。

代码：

```
#include<bits/stdc++.h>
#define int long long
#define PII pair <int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+5;
const int mod=1e9+7;
int T,n,k;
int fac[N],ifac[N];
inline int read(){
    int s=0,f=1;char ch=getchar();
    while (!isdigit(ch)) {if (ch=='-') {f=-1;} ch=getchar();}
    while (isdigit(ch)) {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();}
    return s*f;
}
inline int ksm(int a,int b)
{
    int res=1;
    while (b)
    {
        if (b&1) res=res*a%mod;
        a=a*a%mod;b>>=1;
    }
    return res;
}
inline int binom(int n,int m)
{
    if (n<m) return 0;
    if (n<0 || m<0) return 0;
    if (n==0 || m==0) return 1;
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline void solve()
{
    int ans=0;
    n=read(),k=read();
    for (int i=2;i<=n;i++)
    {
        int res=binom(n-(i-2)*(k-1),i-1);
        res=res*ksm(binom(n,i-1),mod-2)%mod;
        ans=(ans+res)%mod;
    }
    printf("%lld\n",(ans+1)%mod);
}
signed main()
{
    // freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
    T=read();fac[0]=ifac[0]=1;
    for (int i=1;i<=N-5;i++) fac[i]=fac[i-1]*i%mod;
    ifac[N-5]=ksm(fac[N-5],mod-2)%mod;
    for (int i=N-6;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
    while (T--) solve();
    return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：0)

### Solve

设 $f_i$ 表示点亮 $i$ 盏灯然后立即结束的概率，那么期望答案应该等于 $\sum_{i\in [1,n]}i\cdot f_i$。

定义 $g_i=\sum_{j\in [i,n]}f_j$，那么答案也可以表示为 $\sum_{i\in [1,n]}g_i$。

$g_i$ 只是我们强行定义的，我们需要为 $g_i$ 寻找一个形象化的解释。容易想到 $g_i$ 表示可以点亮 $i-1$ 盏灯还没有结束的概率。

有

$$
g_i=\dfrac{\dbinom{n-(i-1)-(i-2)(k-2)+2-1}{i-1}}{\dbinom{n}{i-1}}=\dfrac{\dbinom{n-(k-1)(i-2)}{i-1}}{\dbinom{n}{i-1}}
$$

即先放出来在 $i-1$ 个，再在 $i-1$ 个的空隙中插入不放的，每个空至少插入 $k-1$ 个，两边的空可以不放。经典的插板法。

---

