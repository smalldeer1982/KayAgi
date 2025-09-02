# Crossword Expert

## 题目描述

今天 Adilbek 要参加概率论考试。不幸的是，当 Adilbek 到达大学时，已经有很多学生排队等着参加同样的考试了。Adilbek 估计他需要在到达后等待 $T$ 秒才能开始考试。

幸运的是，Adilbek 可以不用复习那些无聊的定理和公式来打发时间。他的智能手机上有一个应用，里面有 $n$ 个日本填字游戏可以解答。Adilbek 决定按照应用中给出的顺序，依次解答所有填字游戏，不跳过任何一个。对于每个填字游戏，给定一个数字 $t_i$，表示一个普通填字游戏专家解答该题所需的时间（单位为秒）。

Adilbek 是一位真正的填字游戏专家，但有时候他在解题时运气不佳。因此，他解第 $i$ 个填字游戏所需的时间要么是 $t_i$ 秒，要么是 $t_i+1$ 秒，概率各为 $\frac{1}{2}$（即他有 $\frac{1}{2}$ 的概率正好用 $t_i$ 秒解完，有 $\frac{1}{2}$ 的概率需要多花一秒）。所有这些事件都是独立的。

在 $T$ 秒过去后（或者如果他在 $T$ 秒之前解完了最后一个填字游戏），Adilbek 会关闭应用（如果他恰好在第 $T$ 秒完成某个填字游戏，则该题算作解答完成；否则当前题目不算解答完成）。他觉得计算 $E$ ——他能完全解答的填字游戏的期望数量——是一个有趣的概率论问题。你能帮他计算这个期望值吗？

回忆一下，离散型随机变量的期望值是所有可能取值的概率加权平均——在本题中，解答填字游戏数量的期望值可以表示为 $E = \sum\limits_{i=0}^{n} i p_i$，其中 $p_i$ 是 Adilbek 恰好解答了 $i$ 个填字游戏的概率。

我们可以将 $E$ 表示为最简分数 $\frac{P}{Q}$，其中 $Q > 0$。请输出 $P \cdot Q^{-1} \bmod (10^9 + 7)$。

## 说明/提示

第一个样例的答案为 $\frac{14}{8}$。

第二个样例的答案为 $\frac{17}{8}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 5
2 2 2
```

### 输出

```
750000007
```

## 样例 #2

### 输入

```
3 5
2 1 2
```

### 输出

```
125000003
```

# 题解

## 作者：Sooke (赞：14)

### 题意

有一个序列，现给序列中每个数等概率加一或不加，求满足前缀和 $\leq T$ 最大下标的期望。

### 解题思路

题目中给你了一个式子（$p_i$ 表示最大下标为 $i$ 的概率）：

$$E = \sum_{i=0}^{n} ip_i$$

最大下标恰好为 $i$ 不好求，这引导着我们进行如下变换：

$$E = \sum_{i=0}^{n} P_i$$

此时 $P_i$ 表示最大下标**大于等于** $i$ 的概率，不难发现两式是等价的。

为什么 $P_i$ 就好求了呢？因为只需要序列前 $i$ 个数之和 $\leq T$ ，其他数随便怎么变，依旧在这个概率的范畴中。

设这 $i$ 个数全部不加时的和为 $S_i$ ，显然加的值不超过 $T - S_i$ 。

很自然地，可以列出以下式子：

$$P_i = (\dfrac{1}{2})^{i}\sum_{j=0}^{T-S_i} \binom{i}{j}$$

后面那部分写成 $S(n,\,m) = \sum\limits_{i=0}^{m} \binom{n}{i}$ 的形式，就是 $S(i,\,T - S_i)$ 。我们的目的，就是对每个 $i$ 都求出这样的一个**组合数前缀和**，看上去是不可能的任务。

实际上，有个 $O(n \sqrt{n})$ 的万能做法，但复杂度过大在此不赘述。考虑随着 $i$ 的增加，$T - S_i$ 是下降的。

$$\begin{cases}S(n + 1,\,m) = \sum\limits_{i=0}^{m} \binom{n+1}{m} = \sum\limits_{i=0}^{m} \binom{n}{m} + \binom{n}{m-1} = S(n,\,m) + S(n,\,m - 1) = 2S(n,\,m) - \binom{n}{m} \\S(n,\,m - 1) = S(n,\,m) - \binom{n}{m} \end{cases}$$

于是预处理求组合数必需品，我们便可以通过上面的转移线性完成本题了！

$T - S_i$ 可能极其大，怎么办？注意到 $\binom{n}{m}$ 在 $n < m$ 时等于 $0$ ，$T - S_i$ 不过纸老虎，$\min$ 上 $n$ 就万事大吉。

---

## 作者：K_256 (赞：6)

考虑用期望的定义计算

现在的问题是如何计算 $p_i$，设 $s_i$ 为前缀和，$k$ 表示在 $i$ 前（包括 $i$）有多少道题目多用了一秒，则 $p_i$ 为 $s_i + k \leq T$ 且 $s_i + t_{i + 1} + k > T$ 的概率，对于 $t_{i + 1}$，概率为 

$$\frac1{2^{i + 1}} \sum_{k = l}^r \binom i k $$

其中 $l = \max \{0,T - s_i - t_{i + 1} \}$，$r = \min \{i - 1,T - s_i \}$

对于 $t_{i + 1} + 1$ 的情况同理

对于每个 $i$，可以发现只有当 $s_i+i+t_{i + 1} > T$ 时才会进行计算，且一次计算消耗 $\min \{t_{i +1},n \}$ 的时间，设 $pos$ 是第一个满足条件的位置，则计算 $pos$ 时复杂度 $O(n)$, 由于 $T - s_{pos + 1} \leq n$，后面的计算复杂度也为 $O(n)$，总复杂度为 $O(n)$

```cpp
#include<cstdio>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const int MAXN = 200010;

ll fac[MAXN], finv[MAXN], pow2[MAXN], t[MAXN];

inline ll Max(ll a, ll b){return a > b ? a : b;}

inline ll Min(ll a, ll b){return a < b ? a : b;}

inline ll fpow(ll a, ll b){
	ll res = 1;
	while (b){
		if (b & 1)
			res = res * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return res;
}

void Init(int maxn){
	fac[0] = pow2[0] = 1;
	for (int i = 1; i <= maxn; ++i){
		fac[i] = fac[i - 1] * i % mod;
		pow2[i] = pow2[i - 1] * 500000004 % mod;
	}
	finv[maxn] = fpow(fac[maxn], mod - 2);
	for (int i = maxn - 1; i >= 0; --i)
		finv[i] = finv[i + 1] * (i + 1) % mod;
}

inline ll C(ll n, ll m){
	return fac[n] * finv[n - m] % mod * finv[m] % mod;
}

int main(){
	ll N, T, ti, sum = 0, ans = 0;
	Init(200001);
	scanf("%lld %lld", &N, &T);
	for (int i = 1; i <= N; ++i)
		scanf("%lld", &t[i]);
	t[++N] = T + 1;//对边界处理 
	for (int i = 1, l, r; i <= N && sum <= T; ++i){
		if (sum + i + t[i] > T){
			//ti的情况 
			l = Max(0, T - sum - t[i] + 1);
			r = Min(i - 1, T - sum);
			for (int j = l; j <= r; ++j)
				ans = (ans + pow2[i] * C(i - 1, j) % mod * (i - 1) % mod) % mod;
			//ti+1的情况 
			l = Max(0, T - sum - t[i]);
			r = Min(i - 1, T - sum);
			for (int j = l; j <= r; ++j)
				ans = (ans + pow2[i] * C(i - 1, j) % mod * (i - 1) % mod) % mod;
		}
		sum += t[i];
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：tommymio (赞：5)

很好的期望入门题。

求出只做出前 $i$ 道题的概率 $P(X=i)$ 不是很好做。考虑换一种做法，求出做出了不少于 $i$ 道题的概率 $P(X\geq i)$，就可以用期望的定义公式 $E(X)=\sum_i P(X=i)\times W_i=\sum_i(P(X\geq i)-P(X\geq i+1))\times i$ 得出答案。

为什么要这样转化呢？因为我们发现，做出前 $i$ 道题，一定能够尝试做之后的题。也就是说，做之后的题是在做完前 $i$ 道题的基础之上的，所以我们只需要求出做完前 $i$ 道题，剩余时间不为负的概率即可。自然有：

$$
P(X\geq i)=(\frac{1}{2})^i\sum_{j=0}^{m}\binom{i}{j}
$$

其中 $m=min(T-\sum\limits_{k=1}^i t_k,i)$。

直接做是 $O(nm)$ 的，$m$ 与 $n$ 基本同阶所以是 $O(n^2)$ 的。

不妨观察一下 $m$ 的变化。我们发现在 $T-\sum\limits_{k=1}^i t_k>i$ 的时候，$m$ 的值都会取 $i$，这样 $m$ 就是单调递增的。随着 $\sum\limits_{k=1}^i t_k$ 逐渐增大，$m$ 在某一个时刻开始取 $T-\sum\limits_{k=1}^i t_k$，由于 $\sum\limits_{k=1}^i t_k$ 一直都是单调递减的，所以 $m$ 也开始单调递减。总体来说 $m$ 的变化呈现两个阶段，图像是一个单峰函数。这使我们考虑一个类似 $\text{two-pointer}$ 的东西。

具体来说，从小到大枚举 $i$，维护一个指针 $\text{cur}$，记录 $\sum\limits_{k=0}^{cur} \binom{i}{k}$ 的值。根据每个 $i$ 对应的 $m$ 放缩 $\text{cur}$ 即可。**由于上述提到的 $m$ 是一个单峰函数，所以时间复杂度稳定 $O(n)$。**

记 $f(n,m)=\sum_{i=0}^m\binom{n}{i}$，则从 $f(n,cur)$ 转移到 $f(n+1,cur)$ 的柿子为 $f(n+1,m)=\sum_{i=0}^{m}\binom{n+1}{i}=\sum\binom{n}{i}+\binom{n}{i-1}=2f(n,m)-\binom{n}{m}$。根据这个柿子在 $i$ 与 $i+1$ 之间转移即可。

我代码里写了快速幂，所以总时间复杂度是 $O(n \log n)$ 的，但事实上可以通过线性求逆元 $+$ 光速幂达到 $O(n)$ 的总时间复杂度。

```cpp
#include<cstdio>
typedef long long ll;
const ll mod=1e9+7;
ll f[200005],fac[200005],inv[200005],a[200005];
inline ll read() {
	ll x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
} 
inline ll min(const ll &x,const ll &y) {return x<y? x:y;}
inline ll binom(int n,int m) {return fac[n]*inv[m]%mod*inv[n-m]%mod;}
inline ll pow(ll x,ll p) {ll res=1;for(;p;p>>=1) {if(p&1) res=res*x%mod; x=x*x%mod;} return res;}
int main() {
	int n=read(),inv2=pow(2,mod-2); ll T=read(),ans=0; fac[0]=inv[0]=1ll;
	for(register int i=1;i<=n;++i) inv[i]=pow(fac[i]=fac[i-1]*1ll*i%mod,mod-2);
	for(register int i=1;i<=n;++i) a[i]=a[i-1]+read(); f[0]=1;
	int cur=0;ll sum=1;
	for(register int i=1;i<=n;++i) {
		if(a[i]>T) break;
		ll lim=min(T-a[i],i);
		sum=(sum+sum-binom(i-1,cur))%mod;
		while(cur<lim) {sum=(sum+binom(i,cur+1))%mod;++cur;}
		while(cur>lim) {sum=(sum-binom(i,cur))%mod;--cur;}
		f[i]=sum*pow(inv2,i)%mod;
	}
	for(register int i=0;i<=n;++i) ans=(ans+(f[i]-f[i+1])*i%mod)%mod;
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
}
```

---

## 作者：UperFicial (赞：4)

> [**CF1194F 解题报告**](https://www.luogu.com.cn/problem/CF1194F)。

$\Theta(n)$ 做法，目前最优解。

设 $p_i$ 表示做到第 $i$ 道题的概率，根据期望的线性性可以得到 $E=\sum_{i=0}^nip_i$。恰好做到第 $i$ 道题的条件是不好求的，我们可以求做 $\ge i$ 道题的概率 $p_i$，那么 $E=\sum_{i=0}^np_i$。原因是，考虑假设能做至少 $i$ 道题，那么肯定会有前缀和 $s_i\le T$，后面的数随便怎么变换是不用管的。

现在求 $p_i$，枚举前面有多少道题加了 $1$ 秒，这个显然是有上限 $T-s_i$ 的，所有可能的序列数为 $2^i$，其中有 $\sum_{k=0}^{T-s_i}\binom{i}{k}$ 种序列是合法的，那么很显然有：

$$p_i=2^{-i}\sum_{k=0}^{T-s_i}\binom{i}{k}$$

问题化为组合数求和，不要看 $T$ 很大，实际上 $k$ 是需要满足不大于 $i$ 的，也就是 $T-s_i$ 是 $O(n)$ 级别。

我们设 $S(n,m)$ 表示 $\sum_{i=0}^m\binom{n}{i}$，它的组合意义为，有 $n$ 个物品，选择不超过 $m$ 个物品的方案数。考虑 $S(n,m)$ 的递推式，$n$ 这个物品如果不选，那么方案数为前 $(n-1)$ 个物品选不超过 $m$ 个的方案数，如果选，那么就是前 $(n-1)$ 个物品选不超过 $(m-1)$ 个的方案数，则 $S(n,m)=S(n-1,m)+S(n-1,m-1)$。

这个式子有什么用呢？考虑它的两种变形：

$$S(n,m-1)=S(n,m)-\binom{n}{m}$$

$$S(n+1,m)=2S(n,m)-\binom{n}{m}$$

第一个式子考虑组合意义，我们把恰好选择 $m$ 个物品的方案数扣掉，也就是不超过 $(m-1)$ 个物品的方案数。第二个式子代数推倒，把 $S(n+1,m)$ 化成 $S(n,m)+S(n,m-1)$，然后把 $S(n,m-1)$ 转成第一个式子就可以得到结果了。

这样我们就有两条等式 $S(n,m)\to S(n,m-1)$ 的，和 $S(n,m)\to S(n+1,m)$ 的，注意随着 $i$ 上升 $T-s_i$ 是不断减小的，这个就可以用双指针做到 $\Theta(n)$ 了。

```cpp
int main()
{
    n=read(),scanf("%lld",&T);
    rep(i,1,n) t[i]=read();
    init_();
   	rep(i,1,n)
   	{
   		sum+=t[i];
   		int mm=(int)Min(T-sum,(ll)i);
   		if(mm<0) break;
   		ans=sub(add(ans,ans),C(i-1,m));
   		if(m<mm) rep(j,m+1,mm) ans=add(ans,C(i,j));
   		else if(m>mm) rev(j,m-1,mm) ans=sub(ans,C(i,j+1));
   		p[i]=mul(fac2[i],ans); 
   		m=mm;
   		E=add(E,p[i]);
   	}
   	printf("%d\n",E); 
    return 0;
}
```


---

## 作者：caidzh (赞：3)

翻译有点锅，应加上：所有题按给定顺序完成

根据题意，我们是要求这样一个东西：

$$\sum_{k=1}^nkA_k$$

其中$A_k$为在$T$秒内做出$k$道题的概率

对于这种“正好做出$k$道题的描述”，一个简单的想法就是将“$=$”转化成“$\ge$”，即“在$T$秒内做出大于等于$k$道题的概率”，我们定义其为$P_k$

可以发现对于原式，可以通过这样的类似后缀和的形式转化成下面这个式子：

$$\sum_{i=1}^nP_i$$

其中$P_i=\frac{1}{2^i}\times \sum_{k=0}^{T-S_i}C_{i}^k$，此式中$S_n=\sum_{i=1}^nt_i$

怎么理解？因为是做出大于等于$k$道题的概率，其中包含$k$，因为题按顺序做，所以做前面的时候不能影响后面的，所以我们不能对后面的题进行时间$+1$的操作，能进行操作的只有前面$i$道题，能操作的题的个数也有限制，即$T-S_i$个，于是乘上组合数即可

接下来我们考虑怎么求$P_i$，一个简单的想法是暴力求组合数前缀和，但是$n\le 2e5$，所以会超时

我们考虑题目的特殊性质，由于$T-S_i$不增，所以这启示我们不用计算重复部分

可是我们发现组合数$C_n^m$中的$n$始终在变化，并没有重复的部分供我们继续做

我们进一步考虑$C_n^m$与$C_{n+1}^m$的关系

我们定义$\sum_{i=0}^m C_n^i=f(n,m)$作为状态，利用组合数之间的关系来进行状态转移

前面提到了，$m$不增，所以我们考虑：$f(n,m)$与$f(n,m-1)$之间的关系

我们拆开$\sum$后可以发现：$f(n,m)-C_n^m=f(n,m-1)$

然后我们考虑$n$，计算过程中，我们首先让$n$单调上升，然后我们来考虑：$f(n+1,m)$与$f(n,m)$之间的关系

$$f(n+1,m)=\sum_{i=0}^mC_{n+1}^i$$

根据组合恒等式：$C_{n}^m=C_{n-1}^m+C_{n-1}^{m-1}$

$$f(n+1,m)=\sum_{i=0}^mC_{n}^i+\sum_{i=0}^mC_{n}^{i-1}=\sum_{i=0}^mC_{n}^{i}+\sum_{i=0}^{m-1}C_n^i$$

上式等于：

$$f(n+1,m)=f(n,m)+f(n,m-1)$$

我们通过前面那个式子，可以得到：

$$f(n+1,m)=f(n,m)+f(n,m)-C_{n}^m=2f(n,m)-C_{n}^m$$

这时我们可以发现状态转移已经充分，可以进行全部的状态转移了

具体实现的时候，我先算出了$f(0,n)=1$，然后再进行一步步的线性状态转移，复杂度瓶颈在于提前预处理逆元，复杂度为$O(nlogn)$
```
#include<bits/stdc++.h>
#define int LL
#define LL long long
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=200010,mod=1e9+7;int n,T,a[maxn],inv[maxn],fac[maxn],inv2[maxn],pow2[maxn],ans;
int Getinv(int x,int y){int ans=1;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
int C(int n,int m){if(m>n)return 0;else return fac[n]*inv[m]%mod*inv[n-m]%mod;}int nowm,val;
signed main()
{
	n=read();T=read();
	fac[0]=1;inv[0]=1;pow2[0]=1;inv2[0]=1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]+=a[i-1];
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=n;i++)inv[i]=Getinv(fac[i],mod-2);
	for(int i=1;i<=n;i++)pow2[i]=pow2[i-1]*2%mod,inv2[i]=Getinv(pow2[i],mod-2);//计算f(0,n) 
	nowm=n;val=1;
	for(int i=1;i<=n;i++){
		int s=min(n,T-a[i]);//计算f(i,s)
		if(s<0)continue;val=((2*val-C(i-1,nowm))%mod+mod)%mod;//f(i-1,nowm)->f(i,nowm)
		while(nowm>s){val=((val-C(i,nowm))%mod+mod)%mod;nowm--;}//f(i,nowm)->f(i,nowm-1)
		ans=(ans+val*inv2[i]%mod)%mod;
	}printf("%lld",ans%mod);return 0;
}
```


---

## 作者：TernaryTree (赞：1)

记 $a_i$ 前缀和为 $s_i$。记变量“做出题目数目”为 $x$。则 

$$
\begin{aligned}
&P(x\ge i) \\
= &2^{-i}\sum_{j=0}^{T-s_i}\dbinom{i}{j}
\end{aligned}
$$

并且 $P(x=i)=P(x\ge i)-P(x\ge i+1)$。

后面是个组合数前缀和。无脑上莫队。$m$ 的转移是简单的。$n$ 的转移有：

$$\sum_{i=0}^m \dbinom ni=\sum_{i=0}^m \dbinom {n-1}{i-1}+\sum_{i=0}^m \dbinom {n-1}{i}=2\sum_{i=0}^m \dbinom {n-1}{i}-\dbinom{n-1}m$$

即可做到 $\Theta(1)$ 转移。总复杂度 $\Theta(n\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;
const bool multidata = 0;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int n, k;
int a[maxn];
int b[maxn];

int power(int a, int b, int p = mod) {
	int t = 1; a %= p;
	while (b) {
		if (b & 1) t = t * a % p;
		a = a * a % p, b >>= 1;
	}
	return t;
}

int fac[maxn], ifac[maxn], pw[maxn];

void init() {
	pw[0] = 1; rep(i, 1, maxn - 1) pw[i] = pw[i - 1] * 2 % mod;
	fac[0] = 1; rep(i, 1, maxn - 1) fac[i] = fac[i - 1] * i % mod;
	ifac[maxn - 1] = power(fac[maxn - 1], mod - 2); per(i, maxn - 2, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

int C(int n, int m) {
	if (n < 0 || n < m || m < 0) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int m, s, res;
pii q[maxn];

void fake_main() {
	init();
	n = read(), k = read();
	rep(i, 1, n) a[i] = a[i - 1] + read();
	rep(i, 0, n) {
		if (k < a[i]) continue;
		q[++m] = {i, min(i, k - a[i])};
	}
	s = max(1.0, n / max(1.0, sqrt(m)));
	sort(q + 1, q + 1 + m, [] (pii x, pii y) {
		return x.fs / s == y.fs / s ? x.sc < y.sc : x.fs < y.fs;
	});
	int N = 0, M = 0, ans = 1;
	rep(i, 1, m) {
		while (N < q[i].fs) ans = (ans * 2 % mod - C(N, M) + mod) % mod, ++N;
		while (M > q[i].sc) ans = (ans - C(N, M) + mod) % mod, --M;
		while (N > q[i].fs) --N, ans = (ans + C(N, M)) % mod * inv2 % mod;
		while (M < q[i].sc) ++M, ans = (ans + C(N, M) + mod) % mod;
		b[q[i].fs] = ans * pw[n - q[i].fs] % mod;
	}
	rep(i, 0, n) b[i] = (b[i] - b[i + 1] + mod) % mod, res = (res + b[i] * i % mod) % mod;
	write(res * power(pw[n], mod - 2) % mod), pc('\n');
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
```

---

## 作者：cosf (赞：1)

比较水的紫题。

我们可以把所有题分为三类：

- 一定能过的题。
- 不一定能过的题。
- 一定过不了的题。

第一、三种可以比较简单地算出。

这里令 $s_i = \sum_{j=1}^it_j$。那么第一种相当于 $s_i + i \le T$，第三种相当于 $s_i \gt T$。

对于第二种，它的要求就是，前面 $i$ 道题至多有 $T - s_i$ 道要多花时间。这个概率就是：

$$
\frac{\binom{i}{1} + \binom{i}{2} + \dots + \binom{i}{T - s_i}}{2^i}
$$

方便表示，令 $F_{i, j}$ 表示 $\sum_{k=1}^j\binom{i}{k}$。可以发现，这个东西可以 $O(1)$ 进行类似莫队的转移（AtCoder 有这个原题，忘记题号了）：

$$
\begin{cases}
F_{i + 1, j} = 2F_{i, j} - \binom{i}{j}\\
F_{i, j - 1} = F_{i, j} - \binom{i}{j}
\end{cases}
$$

于是，我们可以方便地从 $F_{i, T - s_i}$ 转移到 $F_{i + 1, T - s_{i + 1}}$。

## 代码

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005
#define MOD 1000000007ll

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}


ll fac[MAXN], inf[MAXN];


ll C(int n, int m)
{
    return fac[n] * inf[m] % MOD * inf[n - m] % MOD;
}

int n;

ll t;

int main()
{
    cin >> n >> t;
    ll s = 0, v;
    ll res = 0;
    int r = n + 1;
    ll cur = 0;
    fac[0] = 1;
    inf[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fac[i] = i * fac[i - 1] % MOD;
        inf[i] = pow(fac[i], MOD - 2, MOD);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> v;
        s += v;
        if (s + i <= t)
        {
            res++;
            continue;
        }
        else if (s > t)
        {
            break;
        }
        if (r > i)
        {
            r = i;
            cur = pow(2, i, MOD);
        }
        else
        {
            cur = (MOD + 2 * cur - C(i - 1, r)) % MOD;
        }
        while (r > t - s)
        {
            cur = (MOD + cur - C(i, r)) % MOD;
            r--;
        }
        res += (cur * pow(2, i * (MOD - 2) % (MOD - 1), MOD) % MOD) % MOD;
        res %= MOD;
    }
    cout << res << endl;
}
```

---

## 作者：lfxxx (赞：0)

不妨枚举题目数 $i$，问题转化为恰好做了 $i$ 道题的概率，这个不好做，差分一下变成做了至少做了 $i$ 道题的贡献，那么你只用考虑前 $i$ 道题，不妨枚举一下有 $j$ 道题多花了时间，概率就是 $\frac{1}{2^i} \sum_{j=0}^{\min(i,T - \sum_{k=1}^i t_k)} {i \choose j}$。现在问题的瓶颈是多个组合数前缀和。

注意到一个组合数前缀和的复杂度完全可以接受，求解多个前缀和考虑能不能在相邻的式子间做递推。

注意到对于相邻的两个式子对应位置的组合数上标差为 $1$，而我们有 $\sum_{j=0}^{L} {{i+1} \choose j} = \sum_{j=0}^{L} {{i} \choose j} + \sum_{j=0}^{L} {i \choose j-1} = 2 \times (\sum_{j=0}^{L} {i \choose j}) - {i \choose L}$，因此上标差的处理是轻松的，对于下标差，我们发现相邻式子间差的组合数数量是 $|\sum \min(i,T - \sum_{k=1}^i t_k) - \sum \min(i+1,T - \sum_{k=1}^{i+1} t_k)|$，注意到 $f(x) = \min(x,T - \sum_{k=1}^x t_k)$ 是一个值域为 $O(n)$ 的单峰函数，因此相邻式子间差的组合数数量之和是 $O(n)$ 的，暴力将其加入即可做到 $O(n \log mod)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int mod = 1e9+7;
int fac[maxn],inv[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int n,pre[maxn];
int dp[maxn];//第 T 秒时至少做了 i 道题的概率
int ans,T;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    fac[0]=inv[0]=1;
    for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    cin>>n>>T;
    for(int i=1;i<=n;i++) cin>>pre[i],pre[i]+=pre[i-1];
    dp[0]=1;
    int lstup=0,lstdw=0,lstv=1;
    for(int i=1;i<=n;i++){
        if(pre[i]>T) break;
        lstv=(2*lstv%mod+mod-C(lstup,lstdw))%mod;
        lstup++;
        while(lstdw>min(i,T-pre[i])) lstv=(lstv+mod-C(lstup,lstdw))%mod,lstdw--;
        while(lstdw<min(i,T-pre[i])) lstdw++,lstv=(lstv+C(lstup,lstdw))%mod;
        dp[i]=qpow(qpow(2,i),mod-2)*lstv%mod;
    }
    for(int i=1;i<=n;i++) ans=(ans+i*(dp[i]+mod-dp[i+1])%mod)%mod;
    cout<<ans<<'\n';
    return 0;
}
```

---

