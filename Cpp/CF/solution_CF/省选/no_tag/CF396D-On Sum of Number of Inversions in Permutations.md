# On Sum of Number of Inversions in Permutations

## 题目描述

You are given a permutation $ p $ . Calculate the total number of inversions in all permutations that lexicographically do not exceed the given one.

As this number can be very large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Permutation $ p $ of length $ n $ is the sequence that consists of $ n $ distinct integers, each of them is from $ 1 $ to $ n $ .

An inversion of permutation $ p_{1},p_{2},...,p_{n} $ is a pair of indexes $ (i,j) $ , such that $ i&lt;j $ and $ p_{i}&gt;p_{j} $ .

Permutation $ a $ do not exceed permutation $ b $ lexicographically, if either $ a=b $ or there exists such number $ i $ , for which the following logical condition fulfills: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396D/c9f676c4e9d24faf34cdefe9d1d94cdf3a30d1e0.png) AND $ (a_{i}&lt;b_{i}) $ .

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 1 3
```

### 输出

```
2
```

# 题解

## 作者：Inui_Sana (赞：2)

看到计算逆序对数量，毫无疑问是要分开算贡献的，但是怎么算是个问题。

先不考虑怎么算，先考虑怎么处理字典序小于 $p$ 这个条件方便。设一个字典序小于 $p$ 的排列为 $p'$，发现可以用和数位 dp 类似的方式，看最前面多少位是顶到上界的，再根据第一位没顶满的 $p_i'$ 的取值算贡献。

设当前枚举第一个位没顶满的是第 $i$ 位，此时发现已经可以将序列分成不同的几部分算贡献了：

- 第 $i$ 位与后面的数产生的贡献。

此时如果 $p_i'$ 在还没有确定的数中排名是 $x$，则排名 $<x$ 的数，一共 $x-1$ 个，一定都会出现在后面 $[i+1,n]$ 内，产生贡献。对于 $x$，产生的贡献即为 $(x-1)\times(n-i)!$。所以设原序列 $p_i$ 在还没确定的数中排名 $k$，这一部分贡献就是 $\sum_{j<k} (j-1)\times(n-i)!=\dfrac{(k-1)\times(k-2)}{2}\times(n-i)!$。

- 第 $i$ 位后面的数间产生的贡献。

此时可以将后面的数当成 $[1,n-i]$ 的一个排列来算。贡献是简单的，每两个数都有 $\dfrac{1}{2}$ 的情况为正序对，否则为逆序对。再乘上 $p_i'$ 的取值方案 $k-1$ 种，最后就有 $(k-1)\times\dfrac{(n-i)\times(n-i-1)}{2}\times\dfrac{(n-i)!}{2}$ 的贡献。

除此之外，当第 $i$ 位顶满时，也是有贡献的，设后面的数能组成 $<p$ 的排列数为 $c$ 个，则贡献为 $(k-1)\times c$。$c$ 需要用康托展开的方式求。需要 BIT 或者 SGT 维护。

code：

```cpp
int n,m,a[N],f[N],fac[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
struct BIT{
	int tr[N];
	#define lb(x) (x&(-x))
	il void upd(int x,int y){while(x<=n)tr[x]+=y,x+=lb(x);}
	il int qry(int x){int ret=0;while(x)ret+=tr[x],x-=lb(x);return ret;}
}T;
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	fac[0]=1;
	rep(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
	drep(i,n,1){
		f[i]=1ll*T.qry(a[i])*fac[n-i]%mod;
		T.upd(a[i],1);
		f[i]=Mod(f[i],f[i+1]);
	}
	const int iv=(mod+1)/2;
	int ans=0;
	rep(i,1,n){
		int p=T.qry(a[i]);
		ans=Mod(ans,(1ll*(p-2)*(p-1)/2)%mod*fac[n-i]%mod);
		ans=Mod(ans,(1ll*(n-i)*(n-i-1)/2)%mod*(p-1)%mod*fac[n-i]%mod*iv%mod);
		ans=Mod(ans,1ll*(p-1)*(f[i+1]+1)%mod);
		T.upd(a[i],-1);
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：DengDuck (赞：1)

枚举第一个比原排列小的位置，这个我想到了。然后对于每个位置单独算贡献，这个也想到了。

但是咋算贡献我确实脑子没捋顺，所以 Orz @yinhee，顺便整理一下思路。

首先为了满足字典序的约束，我们不难想到枚举枚举第一个比原排列小的位置。

接下来考虑计算这时候的贡献：

## 我和后面的产生的贡献

我们选定自己的数值，假如这个数值在 $[i,n]$ 中的后缀中的排名是 $x$，那么后面的排名在 $[1,x-1]$ 的数字回合我们有 $x-1$ 的贡献，总共是有 $\dfrac 1 2 (x-1)(x-2)$。

其中 $x$ 显然可以 BIT 求。

考虑后面的数字可以随便排，所以我们还要乘上一个 $(n-i)!$

## 后面彼此之间的贡献

考虑我可以在 $[1,x-1]$ 中选择一个数字（$x$ 的定义同上），然后剩下的数字可以随便排，那问题就是：对于所有的 $1\sim n$ 排列，逆序对的数量是多少？

考虑一个逆序对会在一半的排列中出现，所以计数一下应该是 $\frac 1 4 n(n-1)n!$。

注意不要真的带入 $n$，实际要带入 $n-i$。

## 所有对前面的贡献

$[1,n]$ 对 $[1,i-1]$ 的贡献，咋算呢？

区间对区间是困难的，但是 $[1,n]$ 尚且未知所以不能动，所以我们只能考虑枚举到 $t\in[1,i-1]$ 计算这一部分贡献了。

那我们现在就知道，$[1,t]$ 是和原来一样的，也就是我知道后面有多少个数字比我小。

所以我们直接考虑合法排列的数量，也就是后面有多少个排列可以做到字典序不超过 $P$，那我们可以康托展开地计数就行。

代码和 @yinhee 差不多，还不是因为自己不会实现/kk。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1e6+5;
const LL Mod=1e9+7;
const LL I2=(Mod+1)/2;
int n,P[N];
LL Ans,Fac[N],F[N];
struct BIT
{
	LL t[N];
	inline int LB(int x){return x&-x;}
	inline void Upd(int x,LL k){for(int i=x;i<=n;i+=LB(i))t[i]+=k;}
	inline LL Qry(int x){LL Ans=0;for(int i=x;i;i-=LB(i))Ans+=t[i];return Ans;}
}T;
inline void Add(LL &x,LL y){(x+=y)%=Mod;}
int main()
{
	scanf("%d",&n);
	Fac[0]=1;
	for(int i=1;i<=n;i++)Fac[i]=Fac[i-1]*i%Mod;
	for(int i=1;i<=n;i++)scanf("%d",&P[i]);
	for(int i=n;i>=1;i--)
	{
		F[i]=(T.Qry(P[i])*Fac[n-i]%Mod+F[i+1])%Mod;
		T.Upd(P[i],1);
	}
	for(int i=1;i<=n;i++)
	{
		LL K=T.Qry(P[i]);
		Add(Ans,(K-1)*(K-2)%Mod*I2%Mod*Fac[n-i]%Mod);
		Add(Ans,(K-1)*(n-i)%Mod*(n-i-1)%Mod*I2%Mod*Fac[n-i]%Mod*I2%Mod);
		Add(Ans,(K-1)*(F[i+1]+1)%Mod);
		T.Upd(P[i],-1);
	}
	printf("%lld\n",Ans);
}
```

---

## 作者：Kazdale (赞：1)

做法：DP + 权值 BIT

- ## 分析

	我们设 $F_i$ 表示前 $i-1$ 位均与原序列相同时所有字典序小于等于原排列的排列中第 $i$ 位到第 $n$ 位间的逆序对数量之和，那么易得最后的答案为 $F_1$。
    
    那么转移时一共要统计四类逆序对：
    
    - 当第 $i$ 位上的数小于 $p_i$ 时第 $i+1$ 位到第 $n$ 位间的逆序对
    	
        首先设第 $i$ 位到第 $n$ 位间小于 $p_i$ 的数的数量为 $rlz$（后文中所有的 $rlz$ 的定义均与此处相同）。
        
        然后因为第 $i$ 位的数小于 $p_i$ 了，所有后面几位所有的排列都合法，所以这类逆序对的数量等于后面几位的全排列中逆序对的数量 $\times rlz$。
        
        设 $f_i$ 为长度为 $i$ 的全排列中的逆序对数量和。
        
        那么从 $f_{i-1}$ 转移，首先要统计已有的 $i-1$ 个数中的逆序对数量，为 $f_{i-1}$，又因为 $i$ 可以插入这个排列中的 $i$ 个位置构成新的排列，所以数量为 $i \times f_{i-1}$。
        
        然后统计 $i$ 与剩下的数形成的逆序对数量，因为除 $i$ 以外的所有数都小于 $i$，所以只要有数出现在 $i$ 的后面就会产生 $1$ 的贡献，那么当 $i$ 后面有 $j$ 个数时，就会产生 $j \times (i-1)!$ 的贡献，因为 $j \in [0,i-1]$，所以数量为 $\sum_{j=1}^{i-1} j \times (i-1)!$（由于 $j=0$ 时对答案的贡献为 $0$，故不计算）。
        
        所以 $f_i=i \times f_{i-1}+\sum_{j=1}^{i-1} j \times (i-1)!$。
        
        那么这一类逆序对的数量为 $f_{n-i} \times rlz$。
	
	- 当第 $i$ 位上的数等于 $p_i$ 时第 $i+1$ 位到第 $n$ 位间的逆序对
    	
        发现这一类逆序对的数量与为前 $i$ 位与原序列相同时，第 $i+1$ 位到第 $n$ 为间的逆序对数量，即 $F_{i+1}$ 相同。
        
        那么这一类逆序对的数量为 $F_{i+1}$。
	
    - 当第 $i$ 位上的数小于 $p_i$ 时其中一个数为第 $i$ 位上的数的逆序对
    	
        问题可以看做从后面的数中选一个放在 $i$ 的位置上，统计后面的排列中小于这个数的数的数量和，那么设后面的数中有 $j$ 个数小于我现在放的这个数，那么此时数量为 $j \times (n-i)!$，因为排列中各个数不一样，所以不会出现 $j$ 相同的情况而且每个 $j$ 都会被取到，又因为 $j \in [0,rlz-1]$，所以数量为 $\sum_{j=1}^{rlz-1} j \times (n-i)!$（由于 $j=0$ 时对答案的贡献为 $0$，故不计算） 
        
	- 当第 $i$ 位上的数等于 $p_i$ 时其中一个数为第 $i$ 位上的数的逆序对
    	
        那么不难发现，对于单个排列有 $rlz$ 个数小于 $p_i$ 且在第 $i$ 位后面，即单个排列中会有 $rlz$ 个逆序对，那么只要求出这种情况下排列的总数就好了。
        
        设 $hf_i$ 为前 $i-1$ 位均与原序列相同时字典序小于等于原排列的排列的数量。
        
        那么从 $hf_{i+1}$ 转移，分两种情况，第一种是第 $i$ 位上的数为 $p_i$，这时的排列数为 $hf_{i+1}$，第二种是第 $i$ 位上的数小于 $p_i$，首先第 $i$ 位到第 $n$ 位间有 $rlz$ 个数小于 $p_i$，而且由于第 $i$ 位上的数已经小于 $p_i$ 了，所以后面可以直接取全排列。
        
        所以 $hf_i=hf_{i+1}+rlz \times (n-i)!$。
        
        那么这一类逆序对的数量为 $rlz \times hf_{i+1}$。
		
    	接下来思考如何求 $rlz$，不难想到可以开一个权值BIT，处理完一位后加一个 $p_i$（因为 $p_i$ 必然不会小于 $p_i$，所以先加后加对当前位的 $rlz$ 计算没有影响，这里选择后加），然后查询时直接查询到 $p_i-1$ 的前缀和即可。
    
    	最后的总转移式为 $F_i=f_{n-i} \times rlz+F_{i+1}+\sum_{j=1}^{rlz-1} j \times (n-i)!+rlz \times hf_{i+1}$。
    
    	如果将前缀和以及阶乘预处理，那么转移就是 $\mathcal{O(1)}$ 的，此时的总时间复杂度就是 $\mathcal{O(n \log n)}$ 的，可以通过本题。

- ## 代码

```
#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN(1000007);
constexpr int mod(1000000007);
int a[MAXN], p[MAXN], fct[MAXN], sp[MAXN], xx[MAXN], f[MAXN], F[MAXN], hf[MAXN], sum[MAXN];
int n;
struct BIT{
	inline int lowbit(int x) { return x & -x; }
	inline void update(int x, int val) { for (int i(x); i <= n; i += lowbit(i))  sum[i] += val; }
	inline int query(int x) { int res(0);  for (int i(x); i; i -= lowbit(i))  res += sum[i];  return res; }
}Luka;
inline void read(int &temp) { cin >> temp; }
signed main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n);
	fct[0] = hf[n] = hf[n + 1] = 1;
	for (int i(1); i <= n; ++i)  read(a[i]);
	for (int i(1); i <= n; ++i)  p[i] = (p[i - 1] + i) % mod;
	for (int i(1); i <= n; ++i)  fct[i] = fct[i - 1] * i % mod;
	for (int i(1); i <= n; ++i)  f[i] = (i * f[i - 1] % mod + p[i - 1] * fct[i - 1] % mod) % mod;
	Luka.update(a[n], 1);
	for (int i(n - 1), len(2); i; --i, ++len) {
		int res(0);
		int rlz = Luka.query(a[i] - 1);
		hf[i] = (hf[i + 1] + rlz * fct[len - 1] % mod) % mod;
		res = (res + f[len - 1] * rlz % mod) % mod;
		res = (res + F[i + 1]) % mod;
		res = (res + p[rlz - 1] * fct[len - 1] % mod) % mod;
		res = (res + rlz * hf[i + 1] % mod) % mod;
		F[i] = res;
		Luka.update(a[i], 1);
	}
	cout << F[1] << endl;
	return 0;
}
```

---

## 作者：VainSylphid (赞：1)

给你一个 $1$ 到 $n$ 的排列 $p$，计算字典序不超过 $p$ 的所有排列里逆序对的总个数，对 $10^9+7$ 取模。

由于是字典序小于 $p$ 的排列，我们不妨枚举 $1$ 到 $n$ 的每一个位置，计算满足前 $i-1$ 个位置和 $p$ 相同、第 $i$ 个位置比 $p_i$ 小的排列中的逆序对数，不难发现这样做覆盖了所有**小于** $p$ 的排列。

在计算之前，我们需要预处理一些信息。设 $g(i)$ 表示前 $i-1$ 个数中比 $p_i$ 小的值的个数，$d(i)$ 表示后 $n-i$ 个数中比 $p_i$ 小的值的个数。我们可以用树状数组计算 $g(i)$ 的值，则 $d(i)=p_i-g(i)-1$。

接下来我们对于满足前 $i-1$ 个位置和 $p$ 相同、第 $i$ 个位置比 $p_i$ 小的排列分类讨论：

1.后 $n-i$ 个数内部的逆序对数。首先第 $i$ 个位置有 $d(i)$ 种取值，后面 $n-i$ 个数的实际内容是不重要的，可以看成$1$ 到 $n-i$ 的全排列的逆序对个数总和。设 $f(x)$ 表示 $1$ 到 $x$ 的全排列的所有逆序对个数之和，我们从 $x$ 个位置里任选两个位置，并从 $1$ 到 $x$ 任选两个数，大的放前面，小的放后面，剩下 $x-2$ 个位置随便排，就能得到所有这样的逆序对，因此 $f(x)=\tbinom{x}{2} \times \tbinom{x}{2} \times (x-2)!$。那么后 $n-i$ 个数内部的逆序对数就等于 $d(i) \times f(n-i)$。

2.第 $i$ 个数对后 $n-i$ 个数的逆序对数。第 $i$ 个位置可以放第 $i+1$ 到 $n$ 个位置中小于 $p_i$ 的数，对于每个这样的数 $p_j$ 又有第 $i+1$ 到 $n$ 个位置中小于 $p_j$ 的数与之构成逆序对，再乘上后 $n-i$ 个数的全排列，所以它就等于 $(n-i)! \times \frac{d(i) \times (d(i)-1)}{2}$。

3.前 $i-1$ 个数内部的逆序对。

4.前 $i-1$ 个数对后面的 $n-i+1$ 个数的逆序对。

我们可以将3、4两部分一起计算，对于每一个 $j$ 满足 $1 \leq j < i$都有 $d(j)$ 个数在它后面并且比它小，再乘上第 $i$ 个数的方案数和后 $n-i$ 个数的全排列。这两部分的答案就是 $d(i) \times (n-i)! \times \sum_{j=1}^{i-1}{d(j)}$。

我们对于每一个 $1\leq i \leq n$ 计算上面四部分的答案并求和，同时用树状数组维护 $g(i)$。但是我们没有计算排列 $p$ 本身的逆序对数，因此答案还要加上 $\sum_{i=1}^{n}{g(i)}$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll mod = 1000000007;
ll n,a[1000005],fac[1000005],dv[1000005],sum,ans;
struct tree{
	ll s[1000005],sz;
    void update(ll k,ll v)
	{
		while(k <= sz)
		    s[k] += v,k += (k & (-k));
	}
    ll getsum(int k)
	{
	    ll res = 0;
	    while(k)
	        res += s[k],k -= (k & (-k));
		return res;
	}
}b;
ll ksm(ll a,ll b,ll p)
{
	ll ret = 1;a %= p;
	while(b)
	{
		if(b & 1)
		    ret = ret * a % p;
		a = a * a % p,b >>= 1;
	}
	return ret;
}
void init()
{
	fac[0] = dv[0] = 1;
	for(ll i = 1;i <= 1000001;i++)
	    fac[i] = fac[i - 1] * i % mod;
	dv[1000001] = ksm(fac[1000001],mod - 2,mod);
	for(ll i = 1000000;i > 0;i--)
	    dv[i] = dv[i + 1] * (i + 1) % mod;
}
ll C(ll a,ll b)
{
	if(a < b)
	    return 0;
	return fac[a] * dv[b] % mod * dv[a - b] % mod;
}
int main()
{
	init(),scanf("%lld",&n),b.sz = n;
	for(ll i = 1;i <= n;i++)
	    scanf("%lld",&a[i]);
	for(ll i = 1;i <= n;i++)
	{
		int num = b.getsum(a[i]);
		ans = (ans + C(n - i,2) * C(n - i,2) % mod * fac[n - i - 2] % mod * (a[i] - num - 1) % mod) % mod;
		ans = (ans + (a[i] - num - 1) * (a[i] - num - 2) / 2 % mod * fac[n - i] % mod) % mod;
		ans = (ans + sum * fac[n - i] % mod * (a[i] - num - 1) % mod) % mod;
		ans = (ans + (a[i] - num - 1)) % mod;
		b.update(a[i],1),sum = (sum + (a[i] - num - 1)) % mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

