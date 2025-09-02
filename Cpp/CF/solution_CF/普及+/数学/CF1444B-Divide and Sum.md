# Divide and Sum

## 题目描述

You are given an array $ a $ of length $ 2n $ . Consider a partition of array $ a $ into two subsequences $ p $ and $ q $ of length $ n $ each (each element of array $ a $ should be in exactly one subsequence: either in $ p $ or in $ q $ ).

Let's sort $ p $ in non-decreasing order, and $ q $ in non-increasing order, we can denote the sorted versions by $ x $ and $ y $ , respectively. Then the cost of a partition is defined as $ f(p, q) = \sum_{i = 1}^n |x_i - y_i| $ .

Find the sum of $ f(p, q) $ over all correct partitions of array $ a $ . Since the answer might be too big, print its remainder modulo $ 998244353 $ .

## 说明/提示

Two partitions of an array are considered different if the sets of indices of elements included in the subsequence $ p $ are different.

In the first example, there are two correct partitions of the array $ a $ :

1. $ p = [1] $ , $ q = [4] $ , then $ x = [1] $ , $ y = [4] $ , $ f(p, q) = |1 - 4| = 3 $ ;
2. $ p = [4] $ , $ q = [1] $ , then $ x = [4] $ , $ y = [1] $ , $ f(p, q) = |4 - 1| = 3 $ .

In the second example, there are six valid partitions of the array $ a $ :

1. $ p = [2, 1] $ , $ q = [2, 1] $ (elements with indices $ 1 $ and $ 2 $ in the original array are selected in the subsequence $ p $ );
2. $ p = [2, 2] $ , $ q = [1, 1] $ ;
3. $ p = [2, 1] $ , $ q = [1, 2] $ (elements with indices $ 1 $ and $ 4 $ are selected in the subsequence $ p $ );
4. $ p = [1, 2] $ , $ q = [2, 1] $ ;
5. $ p = [1, 1] $ , $ q = [2, 2] $ ;
6. $ p = [2, 1] $ , $ q = [2, 1] $ (elements with indices $ 3 $ and $ 4 $ are selected in the subsequence $ p $ ).

## 样例 #1

### 输入

```
1
1 4```

### 输出

```
6```

## 样例 #2

### 输入

```
2
2 1 2 1```

### 输出

```
12```

## 样例 #3

### 输入

```
3
2 2 2 2 2 2```

### 输出

```
0```

## 样例 #4

### 输入

```
5
13 8 35 94 9284 34 54 69 123 846```

### 输出

```
2588544```

# 题解

## 作者：tommymio (赞：10)

结论题。

每种划分的值都为前 $n$ 大的数之和减去前 $n$ 小的数之和。

证明？$\sum_{i=1}^n|p_i-q_i|=\sum_{i=1}^n\max(p_i,q_i)-\min(p_i,q_i)$，我们断言在任意一种划分中， $\forall i,\max(p_i,q_i)$ 一定是前 $n$ 大的数，$\min(p_i,q_i)$ 一定是前 $n$ 小的数。如果不是这样，则有两种情况：

- $\max(p_i,q_i)$ 是前 $n$ 大的数，$\min(p_i,q_i)$ 也是前 $n$ 大的数，这种情况会导致存在某个 $j$ ，$\max(p_j,q_j)$ 是前 $n$ 小的数，$\min(p_j,q_j)$ 也是前 $n$ 小的数。

- $\max(p_i,q_i)$ 是前 $n$ 小的数，$\min(p_i,q_i)$ 也是前 $n$ 小的数，这种情况会导致存在某个 $j$ ，$\max(p_j,q_j)$ 是前 $n$ 大的数，$\min(p_j,q_j)$ 也是前 $n$ 大的数。

而这些情况在 $p$ 不减，$q$ 不增时是不存在的。

答案就为 $(\sum_{x\in S_1} a_x-\sum_{x\in S_2} a_x)\times\binom{2n}{n}$，其中 $S_1$ 为前 $n$ 大的数构成的集合，$S_2$ 为前 $n$ 小的数构成的集合。

---

## 作者：Zenith_Yeh (赞：5)

很多同学都是通过手玩或打表找规律得到的。

规律是：结果是数列 $a$ 中的大的 $n$ 个数之和 $-$ 小的 $n$ 个数之和的 $C_{2n}^{n}$ 倍。

为什么呢？

我们来证一下：

设数列 $a$ 非降序排序后，前 $n$ 个数分别为 $\{u_1,u_2,u_3,\cdot\cdot\cdot,u_n\}$，后 $n$ 个数分别为 $\{v_1,v_2,v_3,\cdot\cdot\cdot,v_n\}$，那我们设 $i$ 为前 $n$
 个数被分配到数列 $p$ 中的个数。

$PS:u_1≤u_2≤u_3≤\cdot\cdot\cdot≤u_n≤v_1≤v_2≤v_3≤\cdot\cdot\cdot≤v_n$
 
因为 $p$ 为非递减且 $q$ 为非递增，所以 $p=\{\underbrace{u,u,u,\cdot\cdot\cdot,u}_{i\text{ 个}}\,,\underbrace{v,v,v,\cdot\cdot\cdot,v}_{n-i\text{ 个}}\},q=\{\underbrace{v,v,v,\cdot\cdot\cdot,v}_{i\text{ 个}}\,,\underbrace{u,u,u,\cdot\cdot\cdot,u}_{n-i\text{ 个}}\}$。

所以 $\sum_{i=1}^{n}|p_i-q_i|=\sum_{i=1}^{n}|u_i-v_i|=\sum_{i=1}^{n}(v_i-u_i)$。

由于 $\sum_{i=1}^{n}(v_i-u_i)$ 为确定的，所以只要求有多少个 $f(p,q)$ 即可，不难发现为 $C_{2n}^{n}$ 个。

所以答案为数列 $a$ 中的大的 $n$ 个数之和 $-$ 小的 $n$ 个数之和的 $C_{2n}^{n}$ 倍。

**上菜:**
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
#define mod 998244353
using namespace std;
int n,a[150000*2+5],f[150000*2+5],inv[150000*2+5],ans;
int ksm(int x,int y)//由于要用到逆元求组合数，所以要快速幂
{	int res=1;
	while(y)
	{	if(y&1)res=x*res%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main()
{	cin>>n;
	for(register int i=1;i<=2*n;++i)cin>>a[i];
	sort(a+1,a+n+n+1);//排序
	f[0]=1;
	for(register int i=1;i<=2*n;++i)//求逆元
	{	f[i]=f[i-1]*i%mod;
		inv[i]=ksm(f[i],mod-2);
	}
	for(register int i=2*n;i>=1;--i)//计算答案
	{	if(i<=n)ans=(ans+mod-f[2*n]*inv[n]%mod*inv[n]%mod*a[i]%mod)%mod;//若为小的n个数，则减
		else ans=(ans+f[2*n]*inv[n]%mod*inv[n]%mod*a[i]%mod)%mod;//若为大的n个数，则加
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：白鲟 (赞：3)

## 前言
纪念 CF 第一次打 Div.1，第一次 FST，以及第一次掉 Rating……

## 题意简述
将一个长为 $2n$ 的序列 $a$ 分为长为 $n$ 的两部分 $p,q$，并将这两部分分别以降序和升序排列，问所有划分方式的 $\sum_{i=1}^{n}|p_i-q_i|$ 之和。

## 题目分析
考虑分析每个 $a_i$ 作为正负的次数。

从特殊情况着手，自然地想到将原序列升序排序，取前 $n$ 个作为 $p$，后 $n$ 个作为 $q$。容易得知此时前 $n$ 个贡献均为负，后 $n$ 个均为正。

接下来拓展到一般情况。事实上一般情况可看作前一种情况的 $p,q$ 间若干元素的交换。由于 $p$ 中任意元素不小于 $q$ 中任意元素，且序列总有序，交换后的元素都将聚集在序列的尾端，。因此，$p$ 中交换到 $q$ 中的元素贡献继续为正；同样地，$q$ 中交换到 $p$ 中的元素贡献继续为负。

这时我们发现，较小的 $n$ 个 $a_i$ 贡献恒为负，较大的 $n$ 个 恒为正。符合条件的分法为从 $2n$ 个数中无序地选出 $n$ 个作为序列 $p$，总共有 $\dbinom{2n}{n}$ 种。将 $a_i$ 升序排序后，答案就等于 $\dbinom{2n}{n}(\sum_{i=1}^{n}-a_i+\sum_{i=n+1}^{2n}a_i)$。

组合数的计算只需要对 $n!$ 整体求一次逆元。时间复杂度为 $\operatorname{O}(n\log n)$，瓶颈在排序。

## 代码
需要注意的是 $a_i$ 的最大值大于模数，因此读入时应对其取模。否则减法操作将为负数。

我就是因为这个 FST 掉了！！！

```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=3e5,mod=998244353;
int n,ans,factorial=1,t=1,a[maxn+1];
int power(int base,int exponent)
{
	int res=1;
	while(exponent)
	{
		if(exponent&1)
			res=(long long)res*base%mod;
		base=(long long)base*base%mod;
		exponent>>=1;
	}
	return res%mod;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=(n<<1);++i)
		scanf("%d",&a[i]);
	sort(a+1,a+(n<<1)+1);
	for(int i=n+1;i<=(n<<1);++i)
		factorial=(long long)factorial*i%mod;
	for(int i=1;i<=n;++i)
		t=(long long)t*i%mod;
	factorial=(long long)factorial*power(t,mod-2)%mod;
	for(int i=1;i<=n;++i)
		ans=(ans+(long long)factorial*(mod-a[i]%mod)%mod)%mod;
	for(int i=n+1;i<=(n<<1);++i)
		ans=(ans+(long long)factorial*a[i]%mod)%mod;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：2)

- [原题链接](https://www.luogu.com.cn/problem/CF1444B)

------------

怎么都是用的结论，来个拆贡献。

枚举数 $x$ 分别考虑其作为减数与被减数的贡献。

思考 $x$ 在排序后序列的位置：

$$p:\dots \dots x \dots \dots$$


$$q:\dots \dots y \dots \dots$$

不难发现在该示例中，若 $x$ 作为减数，它必须不小于它它前面所有数，且不小于 $y$ 及其以后所有数。而这显然是为定值 $n$。

故我们可知，$x$ 作为减数与被减数是互斥的两种状态。考虑分类，分别计算。

以 $x$ 在 $p$ 中作为被减数为例，我们考虑算计数系数。这里给出两种理解：

#### 一

考虑将除 $x$ 外的 $2n-1$ 个数分成两部分的方案，不能发现这与 $x$ 作为被减数的方案形成双射。故系数为 $2n-1 \choose n-1$。

#### 二

上面那种思路比较跳跃。考虑一步一步推式子。

枚举 $x$ 在 $p$ 序列中的位置 $i$，令 $x$ 为全局第 $c$ 小数。则有

$$Ans=\sum_{i=1}^{n}{c-1 \choose i-1}{2n-c \choose n-i}$$

不能发现上式可以用范德蒙德卷积化简，算出来也为 $2n-1 \choose n-1$。

算出系数后模拟即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e5+10,mod=998244353;
int n,m,ans,v[N],inv[N],fct[N],finv[N];
inline void init()
{
	fct[0]=inv[0]=finv[0]=fct[1]=inv[1]=finv[1]=1;
	for(int i=2;i<N;i++)
	{
		fct[i]=1ll*fct[i-1]*i%mod;
		inv[i]=(mod-1ll*mod/i*inv[mod%i]%mod)%mod;
		finv[i]=1ll*finv[i-1]*inv[i]%mod;
	}
}
inline int C(int x,int y){return 1ll*fct[x]*finv[y]%mod*finv[x-y]%mod;}
int main()
{
	init();
	scanf("%d",&n);m=n<<1;
	for(int i=1;i<=m;i++) scanf("%d",&v[i]);
	sort(v+1,v+m+1);
	for(int i=1;i<=m;i++)
		if(i<=n) ans=(ans+mod-2ll*v[i]*C(m-1,n-1)%mod)%mod;
		else ans=(ans+2ll*v[i]*C(m-1,n-1)%mod)%mod;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：KSToki (赞：2)

结论题：无论 $p,q$ 怎样 $f(p,q)$ 的结果都是一样的，都为较大 $n$ 个数的和减较小 $n$ 个数的和。

证明：为了方便，我们设较大 $n$ 个数构成的集合为 $A$，较小 $n$ 个数构成的集合为 $B$，原命题等价于对于任意一个 $i$，$x_i$ 和 $y_i$ 分别属于 $A$ 和 $B$。用反证法，假设存在 $x_i$ 和 $y_i$ 同属于 $A$ 或 $B$，那么必将存在 $x_j$ 和 $y_j$ 同属于另一个集合，则必然有 $(x_i-x_j)(y_i-y_j)\ge 0$，即 $x_i$ 和 $y_i$ 同大于或小于 $x_j$ 和 $y_j$，不符题意。

不同的选择 $p,q$ 的方法一共有 $C_{2n}^{n}$ 种，所以要用逆元，时间复杂度 $O(n log n)$ 可以通过。当然可以把分母乘起来最后再逆元~~但是我懒~~，该时间复杂度 $O(n+log n)$。

代码，记得强转：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[300001],ans;
const int Mod=998244353;
int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
			res=(ll)res*x%Mod;
		x=(ll)x*x%Mod;
		y>>=1;
	}
	return res;
}
int main()
{
    cin>>n;
    for(register int i=1;i<=2*n;++i)
    	cin>>a[i];
    sort(a+1,a+2*n+1);
    for(register int i=1;i<=n;++i)
    	ans=(ans+a[i+n]-a[i])%Mod;
    for(register int i=1;i<=n;++i)
    	ans=(ll)ans*(n+i)%Mod*ksm(i,Mod-2)%Mod;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：275307894a (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/CF1444B)

考虑一个最朴素的暴力:枚举两个数，再用组合数算答案。

考虑算贡献。先排好序。

一个数有两个贡献，加的贡献和减的贡献。

可以枚举每一个数，钦定这个数一定是降序排序的，结果乘二，然后枚举在这个数之前选几个。

代码大概长这样:

```cpp
sort(a+1,a+2*n+1);
for(int i=1;i<=2*n;i++){
	for(int j=1;j<=min(i,n);j++){
		if(i-j-1<=n-j-1) ans-=a[i]*c(j,i)*c(n-j-1,n-i);
		else ans+=a[i]*c(j,i)*c(n-j-1,n-i);
	}
}
```

观察判断是加贡献还是减贡献的判断:$i-j-1\leq n-j-1$

化简一下得到$i\leq n$

即对于每个数，它只可能有一种贡献，而是否有贡献取决于它排好序后在前半边还是后半边。

那么我们要求得式子就是$\sum\limits_{i=n+1}^{2\times n}{\sum\limits_{j=1}^{n-i}{C^{i}_{j}\times C^{2\times n-i}_{n-j-1}\times a_{i}}}-\sum\limits_{i=1}^{n}{\sum\limits_{j=1}^{i-1}{C^{i}_{j}\times C^{2\times n-i}_{n-j-1}\times a_i}}$

然后发现后面这一堆东西很难从数论的角度上优化。

考虑整体一起算，那么就是在除了这个剩下$2\times n-1$中取$n-1$个，即$C^{2\times n-1}_{n-1}$

那么答案就是$(\sum\limits_{i=1}^{n}{a_{n+i}-a_{i}})\times C^{2\times n-1}_{n-1}$

这个东西随便算就好了。

别忘了$\times2$

代码实现:

```cpp
#include<cstdio>
#include<algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
#define mod 998244353
using namespace std;
int n,m,k,x,y,z;
long long ans,a[400039],po[300039],pr[300039],f[300039],now,s[300039],sf[300039],head;
int main(){
	register int i,j;
	scanf("%d",&n);
	for(i=1;i<=2*n;i++)scanf("%lld",&a[i]);
	po[0]=1;
	for(i=1;i<=2*n;i++) po[i]=po[i-1]*2%mod;
	sort(a+1,a+2*n+1);
	for(i=1;i<=2*n;i++){
		if(i>n) ans=(a[i]+ans)%mod;
		else ans=(ans-a[i]+mod)%mod;
	}
	for(i=2; i<=300000; i++) {
		if(!f[i]) s[++head]=i,pr[i]=i;
		for(j=1; j<=head&&i*s[j]<=300000; j++) {
			f[i*s[j]]=1;pr[i*s[j]]=s[j];
			if(i%s[j]==0) break;
		}
	}
	for(i=1;i<=2*n-1;i++){
		now=i;
		while(now!=1) sf[pr[now]]++,now/=pr[now];
	} 
	for(i=1;i<=n-1;i++){
		now=i;
		while(now!=1) sf[pr[now]]--,now/=pr[now];
	}
	for(i=1;i<=n;i++){
		now=i;
		while(now!=1) sf[pr[now]]--,now/=pr[now];
	}
	for(i=1;i<=2*n;i++){
		while(sf[i]) ans=ans*i%mod,sf[i]--;
	}
	printf("%lld\n",ans*2%mod);
}
```







---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题其实很诈骗，很多人看到这道题就想到了动态规划，但其实不然。

我们不妨假设第一个选择的集合是前 $n$ 大的数字组成的，第二个集合是后 $n$ 大的数字组成的。因为前一个集合要保持单调不降，后一个集合要保持单调不增，那么如果两个集合中的数字交换顺序的话那么因为第二个数组中的数都比第一个数组的数要大，那一定都在后面，而第一个数组的数都比第二个数组的数字要小，那么也就在后面，这样一一对应取绝对值的话和就是原来的第二数组总和减去第一数组总和，这样我们直接用这个数去乘交换的总方案即可（代码中有提到）。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int a[300005];
int ksm(int x,int y){
	int ret=1;
	while(y){
		if(y%2==1) {
			ret*=x;ret%=mod;
		}
		x*=x,x%=mod,y/=2;
	}
	return ret;
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n*2;i++) cin>>a[i];
	sort(a+1,a+1+n*2);
	int sumn=0,sumnh=0;
	for(int i=1;i<=2*n;i++){
		if(i<=n) sumn+=a[i],sumn%=mod;
		else sumnh+=a[i],sumnh%=mod;
	}
	int pw=1,po=1;
	for(int i=1;i<=n*2;i++){
		pw=(pw*i)%mod;
		if(i<=n) po=(po*i)%mod;
	}
//	cout<<sumnh<<" "<<sumn<<" ";
	cout<<(sumnh+mod-sumn)%mod*pw%mod*ksm(po,mod-2)%mod*ksm(po,mod-2)%mod;//2*n个数字中选n个数的贡献，组合数即可
	return 0;
}
```

---

## 作者：七色丶人偶使 (赞：1)

upd:2020.11.2 感谢 @panyf 指出我算错时间复杂度。

-----

一个水题，但是考场上愣是想了一个小时，最后忘了加模数再取模导致我fst。

考虑 $\mid x_i - y_i \mid$ 的意义，就是 $\max(x_i, y_i) - \min(x_i, y_i)$ 那么就是说对于每个位置，取两个排列中的最大值减去最小值。

这样的排列一共会有 $C_{2n}^n$ 个。

这里先给出一个结论，**排序后**，后半部分永远会被取成最大值，前半部分永远会被取成最小值。

（以下内容均以**排序后的原数组**为准）

上述结论是由其排列排列顺序决定的，考虑后半部分的数如果放到 $p$ 中，那么一定在最后几个。如果放到 $q$ 中，一定在前几个，那么我们可以知道原序列的一半恰好等于 $p, q$ 的长度，那么其实这些元素是不会相互之间取最大最小值的。

所以答案即为**排序后的数组** $\displaystyle \Big( \sum_{i=n+1}^{2\cdot n} a_i - \sum_{i=1}^n a_i \Big) \cdot C_{2n}^n$。

我比较菜，写的线性求逆元+阶乘。

时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;
const ll MAXN = 1e6+10, MOD = 998244353;

ll N, M, fac[MAXN], val[MAXN], inv[MAXN], ans;

int main() {
    scanf("%lld", &N);
    inv[1] = inv[0] = fac[1] = fac[0] = 1;
    for (ll i = 2; i <= N<<1; i++) fac[i] = fac[i-1] * i % MOD, inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (ll i = 1; i <= N<<1; i++) inv[i] = inv[i-1] * inv[i] % MOD;
    for (ll i = 1; i <= N<<1; i++)
        scanf("%lld", val+i);
    ll tem = fac[N<<1] * inv[N] % MOD * inv[N] % MOD;
    sort(val+1, val+(N<<1)+1);
    for (ll i = 1; i <= N; i++)
        ans = (ans - tem * val[i] % MOD) % MOD;
    for (ll i = N + 1, k = N << 1; i <= k; i++)
        ans = (ans + tem * val[i] % MOD) % MOD;
    printf("%lld\n", (ans + MOD) % MOD);
    return 0;
}
```


---

## 作者：2huk (赞：0)

> - 给一个长度为 $2n$ 的数列 $a$，将 $a$ 中的数分为两串长度为 $n$ 的数列 $p$ 和 $q$。将 $p$ 升序排序，$q$ 降序排序。定义权值为 $\sum_{i=1}^n |p_i - q_i|$。求所有划分的权值和。
> - $n \le 1.5 \times 10^5$。

首先每种划分的方案都是一定的，为 $\sum_{v \in S_1} v - \sum_{v \in S_2} v$。其中 $S_1$ 表示 $a$ 的前 $n$ 大的数构成的集合，$S_2$ 表示 $a$ 的前 $n$ 小的数构成的集合。

那么答案为 $\dbinom {2n}n \cdot \sum_{v \in S_1} v - \sum_{v \in S_2} v$。

首先 $\sum |p_i - q_i| = \sum (\max (p_i,q_i) - \min(p_i, q_i))$，而且可以证明 $\max (p_i,q_i) \in S_1$ 以及 $\min(p_i, q_i) \in S_2$。

考虑反证：

- 如果 $\max (p_i,q_i), \min(p_i, q_i) \in S_1$，那么一定存在某个 $j$ 使得 $\max (p_j, q_j), \min(p_j, q_j) \in S_2$。那么此时 $i < j$ 或 $i > j$ 都不能满足「$p$ 升序排序，$q$ 降序排序」这个条件。
- 如果 $\max (p_i,q_i), \min(p_i, q_i) \in S_2$，那么一定存在某个 $j$ 使得 $\max (p_j, q_j), \min(p_j, q_j) \in S_1$。那么此时 $i < j$ 或 $i > j$ 都不能满足「$p$ 升序排序，$q$ 降序排序」这个条件。

```cpp
int fpm(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = (ll)res * a % P;
		b >>= 1, a = (ll)a * a % P;
	}
	return res;
}

int C(int a, int b) {
	int res = 1;
	for (int i = 1; i <= b; ++ i ) res = (ll)res * fpm(i, P - 2) % P;
	for (int i = a - b + 1; i <= a; ++ i ) res = (ll)res * i % P;
	return res;
}

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n * 2; ++ i ) fin >> a[i];
	sort(a + 1, a + n * 2 + 1);
	int res = 0;
	for (int i = 1; i <= n; ++ i ) (res += a[i + n] - a[i]) %= P;
	fout << (ll)res * C(2 * n, n) % P << '\n';
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[CF1444B Divide and Sum](https://www.luogu.com.cn/problem/CF1444B)。

## 题意

给一个长度为 $2n$ 的数列 $a$，将 $a$ 中的数分为两串长度为 $n$ 的数列 $p$ 和 $q$。

我们按非递减的顺序对数列 $p$ 排序，而数列 $q$ 按非递增的顺序排序。然后我们定义 $f(p,q)=\sum_{i=1}^{n}|p_i-q_i|$。

求对于所有的 $p,q$ 的 $f(p,q)$ 的值之和。答案对 $998244353$ 取模。

## 思路

遇到这种关于数列划分的数数题，可以考虑拆开贡献。

对于一个数 $x$，它可以在 $p$ 和 $q$ 两个数列中。我们先讨论在 $p$ 中的情况。假设排序后 $x$ 在 $p$ 中的位置是 $i$。

1. 若 $p_i<q_i$，则 $x$ 贡献为负。此时 $p_{[i+1,n]}$ 和 $q_{[1,i]}$ 一定不小于 $x$，即至少 $n$ 个数不小于 $x$；

1. 若 $p_i \geq q_i$，则 $x$ 贡献为正。此时 $p_{[1,i-1]}$ 和 $q_{[i,n]}$ 一定不大于 $x$，即至少 $n$ 个数不大于 $x$。

注意到上面的“不小于”“不大于”，虽然不是严格大于或小于，但是相同的数同时出现在两种情况就能抵消，所以可以将原数组排序，前 $n$ 小的算负的贡献，前 $n$ 大的算正的贡献。

但是每个数的贡献肯定不是 $+x$ 或 $-x$ 啊，所以我们要算出它的系数。

上面我们已经排除了相同情况的干扰，所以直接当成数组中的元素互不相同。此时，无论其他的 $2n-1$ 个数怎么排，$x$ 贡献的正负性永远不会改变。所以总方案为 $\binom{2n-1}{n-1}$。

但是这是 $x$ 在 $p$ 中的系数，实际上还要考虑在 $q$ 中的情况，乘二就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300001],jc[300001],ni[300001],ans;
int qpow(int x,int b){
	if(!b)return 1;
	int res=qpow(x,b>>1);
	return b&1?1ll*res*res%998244353*x%998244353:1ll*res*res%998244353;
}
int main(){
	jc[0]=ni[0]=1,scanf("%d",&n);
	for(int i=1;i<300001;++i)jc[i]=1ll*i*jc[i-1]%998244353;
	ni[300000]=qpow(jc[300000],998244351);
	for(int i=299999;i;--i)ni[i]=1ll*ni[i+1]*(i+1)%998244353;
	for(int i=1;i<=n<<1;++i)scanf("%d",a+i);
	sort(a+1,a+n+n+1);
	for(int i=1;i<=n;++i)ans=(ans+a[i+n]-a[i])%998244353;
	return 0&printf("%d",1ll*ans*jc[n<<1]%998244353*ni[n]%998244353*ni[n]%998244353);
}
```

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1444B)

## 分析

猜不出结论怎么办，那就直接推吧。

绝对值符号很丑，考虑拿掉，假如前 $k$ 个数都有 $q_i \ge p_i,i \in [1,k]$，取最大的 $k$，那么就有：

$$\sum_{i=1}^{n}|q_i-p_i|=\sum_{i=1}^{k}(q_i-p_i)+\sum_{k+1}^{n}(p_i-q_i)$$

$$=\sum_{i=1}^{n}p_i-\sum_{i=1}^{n}q_i+2\sum_{i=1}^{k}q_i-2\sum_{i=1}^{k}p_i$$

因为 $p,q$ 可以交换，那么 $\sum \limits_{i=1}^{n} p_i-\sum \limits_{i=1}^{n}q_i$ 这一项是可以抵消的。

考虑求 $\sum \limits_{i=1}^{k} q_i$。我们枚举 $k$，显然 $q_{1}\sim q_k$ 只能在前 $n$ 大的数里面选，剩下的 $n-k$ 个数则在前 $n$ 小的数里面选，这样一定有 $q_i \ge p_i,i \in [1,k]$。

现在我们需要知道在前 $n$ 大的数里面选 $k$ 的数的所有方案的 $q_i$ 之和，那么只需要知道每个数出现的次数即可，显然每个数出现的次数都是 $\dfrac{k\times \binom{n}{k}}{n}$。

求 $\sum \limits_{i=1}^{k} p_i$ 同理。时间复杂度是 $O(n\log n)$ 的，瓶颈在排序。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3e5 + 10, mod = 998244353;
int n, a[N];
int fac[N], inv[N], finv[N];

inline void init(int n) {
	fac[0] = inv[0] = finv[0] = 1;
	fac[1] = inv[1] = finv[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = (ll)fac[i - 1] * i % mod;
		inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
		finv[i] = (ll)finv[i - 1] * inv[i] % mod;
	}
}

int C(int n, int m) {
	return (ll)fac[n] * finv[m] % mod * finv[n - m] % mod;
}

int main() {
	scanf("%d", &n);
	init(n);
	for (int i = 1; i <= n << 1; i++) scanf("%d", &a[i]);
	sort(a + 1, a + 2 * n + 1);
	ll sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; i++) sum1 += a[i];
	for (int i = 1; i <= n; i++) sum2 += a[i + n];
	ll ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i++) {
		int t = (ll)C(n, i) * i % mod * inv[n] % mod;
		ans1 = (ans1 + sum1 % mod * t % mod * 2 % mod * C(n, n - i) % mod) % mod;
		ans2 = (ans2 + sum2 % mod * t % mod * 2 % mod * C(n, n - i) % mod) % mod;
	}
	printf("%lld", (ans2 - ans1 + mod) % mod);
	return 0;
}
```


---

