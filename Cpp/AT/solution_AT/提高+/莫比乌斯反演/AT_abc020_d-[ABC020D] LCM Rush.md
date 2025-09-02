# [ABC020D] LCM Rush

## 题目描述

$2$ 个正整数 $a$、$b$ 的最小公倍数 $LCM(a,\ b)$，是指既是 $a$ 的倍数又是 $b$ 的倍数的所有正整数中最小的一个。

给定两个正整数 $N$、$K$。请计算对于所有 $1$ 到 $N$ 之间的整数 $i$，$LCM(i,\ K)$ 的和，并将结果对 $1,000,000,007$ 取余。

## 说明/提示

## 部分分

由于本题作为 AtCoder Beginner Contest 的题目来说非常难，因此本题总分为 $101$ 分，并设置了部分分。

- 有 $5$ 分的测试点满足 $1 \leq N, K \leq 100$。
- 另有 $10$ 分的测试点满足 $1 \leq N \leq 10^4, 1 \leq K \leq 100$。
- 还有 $85$ 分的测试点满足 $1 \leq N \leq 10^9, 1 \leq K \leq 100$。以上共计 $100$ 分。

## 样例解释 1

$LCM(1,\ 2) + LCM(2,\ 2) + LCM(3,\ 2) + LCM(4,\ 2) = 2 + 2 + 6 + 4 = 14$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2```

### 输出

```
14```

## 样例 #2

### 输入

```
10000 100```

### 输出

```
865504986```

## 样例 #3

### 输入

```
1000000000 90```

### 输出

```
50001213```

## 样例 #4

### 输入

```
1000000000 999999900```

### 输出

```
231285006```

# 题解

## 作者：EnofTaiPeople (赞：13)

### Part1 题意
给定 $n,k$，求 $\sum\limits_{i=0}^n\operatorname{lcm}(i,k)$。

### Part2 莫反公式与最大公因数的关系

1. 定义数论函数 $f(x)$ 和 $g(x)$ 的狄利克雷卷积 $(f*g)(x)=\sum\limits_{i|x}f(i)g(\dfrac xi)$；

2. 定义莫比乌斯函数 $\mu(x)=\begin{cases}1,x=1\\0,x=p^2q,p\in P\\(-1)^k,x=\prod\limits_{i=1}^kp_i,p_i\in P,\forall i\ne j,p_i\ne p_j\end{cases}$；

3. 定义单位函数 $\epsilon(x)=[x=1]$，即只有 $x=1$ 时值为一，其余为零，于是有 $\mu*1=\epsilon$，即 $\sum\limits_{d|x}\mu(d)=\epsilon(x)$；

4. 由于狄利克雷卷积具有交换律和结合律，于是若 $f=g*1$，则 $f*\mu=g*(1*\mu)=g$，故有 $f=g*1\Leftrightarrow g=f*\mu$；

5. 于是可以考虑设 $f=g*1$，则 $f(\gcd(x,y))=\sum\limits_{d|\gcd(x,y)}g(d)=\sum\limits_{d|x,d|y}g(d)$，而由 4 得 $g=f*\mu$，故有 $f(\gcd(x,y))=\sum\limits_{d|x,d|y}(f*\mu)(d)$，有一种叫做魔力筛的东西可以在 $O(n\ln\ln n)$ 的时间复杂度内求出 $(f*\mu)(1\sim n)$。

### Part3 本题公式推导

发现我们只会处理 $\gcd$，而不会处理 $\operatorname{lcm}$，于是需要先将 $\operatorname{lcm}$ 转成 $\gcd$：

$ans=\sum\limits_{i=1}^n\dfrac{ki}{\gcd(i,k)}=k\sum\limits_{i=1}^n\dfrac i{\gcd(i,k)}$

考虑枚举 $\gcd(i,k)$：$ans=k\sum\limits_{d|k}\sum\limits_{i=1}^{\lfloor\frac n d\rfloor}[\gcd(i,\dfrac k d)=1]i$

不妨设 $f(n,m)=\sum\limits_{i=1}^n[\gcd(i,m)=1]i$，则有：

$$\begin{aligned}f(n,m)=\sum\limits_{i=1}^ni[\gcd(i,m)=1]\\=\sum\limits_{i=1}^ni\sum\limits_{d|i,d|m}\mu(d)\\=\sum\limits_{d|m}\mu(d)\sum\limits_{i=1}^{\lfloor\frac n d\rfloor}di\\=\sum\limits_{d|m}\mu(d)d\sum\limits_{i=1}^{\lfloor\frac n d\rfloor}i
\end{aligned}$$

于是，$ans=k\sum\limits_{d|k}f(\lfloor\dfrac n d\rfloor,\dfrac k d)$。

### Part4 具体实现

魔力筛可以在 $O(n\ln\ln n)$ 时间求出任意的 $f*\mu$，其实是基于埃氏筛的，具体代码如下：
```cpp
mu[1]=1;
for(x=2;x<=n;++x){
    if(vs[x])continue;
    else p[++pt]=x;
    for(y=n/x;y;--y)
        vs[x*y]=1,(mu[x*y]-=mu[y])%=M;
}
```
只要将 $f$ 函数预存在 `mu` 数组里就可以了，由于本题需要求 $\mu=\mu*\epsilon$，所以只需要预存 `mu[1]=1;` 即可。

由于可能需要求超过 $10^7$ 的 $\mu$ 函数，所以可以使用暴力分解质因数法，其实不会超时：
```cpp
#include<icecream>
using namespace std;
using ll=long long;
const int N=1e7+7,M=1e9+7;
int n=1e7+2,_n,_k,mu[N];
bitset<N>vs;
int p[2000005],pt,ans;
int mus(int x){
    if(x<=n)return mu[x];小于 1e7 暴力求
    int res=1,i;
    for(i=1;p[i]*p[i]<=x;++i)
        if(!(x%p[i])){
            x/=p[i],res=-res;
            if(!(x%p[i]))return 0;
        }
    if(x>1)res=-res;
    return res;
}
vector<int>G;
int g(int x){太懒了，开个函数求等差数列
    return ll(x+1)*x/2%M;
}
int f(int n,int m){
    int res=0;
    for(int x:G){
        if(x>m)return res;
        if(m%x)continue;
        res=(ll(x)*mus(x)%M*g(n/x)+res)%M;
    }return res;
}
int main(){
    scanf("%d%d",&_n,&_k);
    int x,y;
    mu[1]=1;
    for(x=2;x<=n;++x){
        if(vs[x])continue;
        else p[++pt]=x;
        for(y=n/x;y;--y)
            vs[x*y]=1,(mu[x*y]-=mu[y])%=M;似乎不需要取模？
    }
    for(x=1;x*x<_k;++x)直接预处理因数
        if(!(_k%x))G.push_back(x),G.push_back(_k/x);
    if(x*x==_k)G.push_back(x);
    sort(G.begin(),G.end());
    for(int x:G)ans=(ans+f(_n/x,_k/x))%M;
    ans=ll(_k)*ans%M;
    ans=(ans%M+M)%M;这个筛法会筛出负数！
    printf("%d\n",ans);
    return 0;
}
```

### Part5 一些其他分析
记 $d(x)$ 表示 $x$ 的因数个数，则本题的理想复杂度是 $d^2(k)$，而据说有 $d(k)\le k^{\frac{1.0661}{\ln\ln k}}$，当 $k=10^9$ 时，$k^{\frac{1.0661}{\ln\ln k}}=1463.2566$，可以通过。

---

## 作者：EastPorridge (赞：6)

大家好，我学了个莫比乌斯反演，不用出来浑身难受，刚好呆唯托梦给我说这题数论分块可做，所以我拿数论分块过了。

### 题目概述：

求： 

$$
\sum_{i=1}^{n} \mathrm{lcm}(i,k)
$$

### 题目分析：

进行一个式子的推，

$$
\sum_{i=1}^{n} \mathrm{lcm}(i,k)= \sum_{i=1}^{n} \frac{i \cdot k}{\gcd(i,k)}
= \sum_{d \mid k} \sum_{i=1}^{n} [\gcd(i,k)=d] \cdot \frac{i \cdot k}{d}
= k \sum_{d \mid k} \sum_{i=1}^{\left \lfloor \frac{n}{d} \right \rfloor } [\gcd(i,\frac{k}{d})=1] \cdot i 
$$

把后面那一坨拎出来做莫比乌斯反演，

$$
f(n,m)= \sum_{i=1}^{n} [\gcd(i,\frac{k}{m})=1] \cdot i 
=\sum_{i=1}^{n}i \cdot \sum_{d \mid i,d \mid \frac{k}{m}} \mu(d)
= \sum_{d \mid \frac{k}{m}} d \cdot \sum_{i=1}^{\frac{n}{d}} i \cdot \mu(d)
$$

然后就做完了，里层枚举因数，外层进行数论分块，因为我们无法把 $10^9$ 个 $\mu$ 函数全都筛出来，所以只筛一部分，如果用到再现求。

时间复杂度：稍大的 $O( \sqrt n)$，可以碾过。

### Code.

```cpp
/*
μ's Music Start!
届けて 切なさには名前をつけようか“Snow halation”!
*/
#include<bits/stdc++.h>
#define int long long
using namespace std; const int N=1e7+10,p=1e9+7,i2=500000004;
int n,k,pl,miu[N],res; bitset<N> st; vector<int> pri;
int dasuki(int x)
{
	if(x < N) return miu[x];  int t=1,yl=x;
	for(int i=2;i*i<=yl;i++)
	{
		if(x%i) continue ; pl=0; while(! (x%i)) x/=i,++pl;
		if(pl > 1) return 0; t=-t;
	}
	if(x > 1) t=-t; return t;
}
int f(int n,int m)
{
	int pl=0,t=k/m;
	for(int i=1;i*i<=t;i++)
	{
		if(t%i) continue ; pl=(pl+(i*dasuki(i))%p*(n/i)%p*(n/i+1)%p*i2%p+p)%p;
		if(i*i != t) pl=(pl+((t/i)*dasuki(t/i))%p*(n/(t/i))%p*(n/(t/i)+1)%p*i2%p+p)%p;
	}
	return pl;
}
signed main()
{
	miu[1]=1; scanf("%lld%lld",&n,&k);
	for(int i=2;i<N;i++)
	{
		if(! st[i]) pri.emplace_back(i),miu[i]=-1;
		for(auto j : pri)
		{
			if(i*j > N) break ; st[i*j]=1;
			if(! (i%j)) {miu[i*j]=0; break ;}
			miu[i*j]=-miu[i];
		}
	}
	for(int i=1;i*i<=k;i++) 
	{
		if(k%i) continue ; res=(res+f(n/i,i))%p; 
		if(i*i != k) res=(res+f(n/(k/i),k/i))%p;
	}
	res=(res*k)%p; printf("%lld",res);
	return 0;
}
```

---

## 作者：_edge_ (赞：3)

有趣的 AT 的 $2600$。

可能难度偏高？

首先我们明确要计算的是 $\sum \limits _{i=1} ^n \operatorname{lcm(i,k)}$。

转化一下变成了 $\sum \limits _{i=1} ^n \dfrac{i \times k}{\gcd(i,k)}$。

然后我们先考虑点暴力的做法。

比方说我们可以尝试枚举这个 $\gcd(i,k)$，然后计算有多少个合法的。

我们设 $g=\gcd(i,k)$。

当然，这里直接计算为 $\dfrac{n}{g}$ 会出问题，因为存在 $g$ 的倍数。

我们这里需要一个小容斥，就是 $\dfrac{n}{g}$ 减去它的倍数。

具体的，我们设 $f_x$ 表示 $n$ 里面有 $\gcd(i,k)=x$ 的个数。

然后对于一个 $f_g=\dfrac{n}{g}-\sum \limits _{i=1}^{\frac{k}{i}} f_{i \times g}$。

然后我们就可以很好的求出所有的 $f$ 数组。

但是，我们需要求的是 $\sum \limits _{i=1} ^n \dfrac{i \times k}{\gcd(i,k)}$，我们确定了 $\dfrac{k}{\gcd(i,k)}$ 之后需要求出的就是 $i$ 的总和。

个数会求了，那总和还求不出来么？

就把个数改为等差数列即可。

这样就能很好的过掉很多 subtask。

```cpp
	int kk=0;
	for (int i=m;i>=1;i--) {
		if (m%i) continue;
		g[i]=n/i;
		
		int l=i,r=n/i*i;
		g[i]=(l+r)*(n/i)/2%Mod;
		for (int j=i+i;j<=m;j+=i)
			g[i]-=g[j],g[i]%=Mod;
		int K=g[i]%Mod;
		K*=m/i;K%=Mod;
		kk+=K;
		kk%=Mod;
	}
	kk+=Mod;kk%=Mod;
	cout<<kk<<"\n";
```

但是我们发现这个算法还是不够优秀，继续考虑优化，我们会发现如果不是 $m$ 的约数则一点用处都没有，所以我们先把约数给搞出来之后再做上面的。

```cpp
	for (int i=1;i*i<=m;i++)
		if (m%i==0) {
			d.pb(i);
			if (m/i!=i) d.pb(m/i);
		}
	sort(d.begin(),d.end(),cmp);
	for (int i:d) {
		int l=i,r=n/i*i;
		g[i]=(l+r)*(n/i)/2%Mod;
		for (int j:d)
			if (j%i==0 && j>i) g[i]-=g[j],g[i]%=Mod;
		int K=g[i]%Mod;
		K*=m/i;K%=Mod;
		kk+=K;
		kk%=Mod;
	}
	kk%=Mod;kk+=Mod;kk%=Mod;
```

祝贺你通过了这道 $2600$ 的题。



---

## 作者：myster1ous (赞：0)

## Statement

给定 $n, k$，求 $\sum_{i=1}^n \text{lcm}(i,k)$。

## Solution

显然，这是一道莫比乌斯反演的题目，因为莫比乌斯反演就经常用来处理 $\gcd$、$\text{lcm}$ 这种的和。

莫比乌斯反演：

$$
\sum_{d | k} \mu(d) = \left\{
\begin{aligned}& 1 \quad \text{if } n = 1 \\ & 0 \quad \text{if } n \neq 0\end{aligned}
\right.
$$

其中 $\mu$ 是莫比乌斯函数：

$$
n = \prod_{i=1}^{k} p_i^{c_i}(
\forall p_i\in\textbf{P},c_i\in\textbf{N}^+,
\forall i\neq j,p_i \neq p_j)\\
\mu(n) = \left\{\begin{aligned}&0\quad&\text{if }&\max({c_i}) \geqslant 2\\&(-1)^k\quad&\text{if }&\max(c_i)=1,n\neq 1\\&1\quad&\text{if }&n=1\end{aligned}\right.
$$

我们先用 $\text{lcm}(a, b) = \frac{a \times b}{\gcd(a, b)}$ 将 $\text{lcm}$ 化为 $\gcd$：

$$
\begin{aligned}
\text{ans} & = \sum_{i = 1}^n \text{lcm}(i, k)\\
& = \sum_{i = 1}^n \frac{i \times k}{\text{gcd}(i, k)}
\end{aligned}
$$

再提出去一个 $k$，然后因为 $\gcd$ 的倒数不好算，所以直接枚举 $\gcd$ 的可能值。

$$
\begin{aligned}
\text{ans} & = \sum_{i = 1}^n \frac{i \times k}{\text{gcd}(i, k)}\\
& = k \times \sum_{i = 1}^n \frac{i}{\text{gcd}(i, k)}\\
& = k \times \sum_{i = 1}^n \sum_{g|k} \frac{i}{g} \times [\gcd(i, k) = g]
\end{aligned}
$$

注：$[\text{s}]$ 当 $\text{s}$ 成立的时候是 $1$ 否则是 $0$。

然后又因为必须是 $[\gcd(\dots)=1]$ 才能用莫比乌斯反演，因此我们考虑“提出” $g$。因为符合 $\gcd(i,k) = g$ 的时候一定有 $g|i$，因此直接 $i,k$ 同时除以 $g$ 即可。

$$
\begin{aligned}
\text{ans} & = k \times \sum_{i = 1}^n \sum_{g|k} \frac{i}{g} \times [\gcd(i, k) = g]\\
& = k \times \sum_{g|k} \sum_{i = 1}^n  \frac{i}{g} \times [\gcd(i, k) = g]\\
& = k \times \sum_{g|k} \sum_{i = 1}^n  \frac{i}{g} \times [\gcd\left(\tfrac{i}{g}, \tfrac{k}{g}\right) = 1]\\
& = k \times \sum_{g|k} \sum_{i = 1}^{\left\lfloor\tfrac{n}{g}\right\rfloor}  {i} \times [\gcd\left({i}, \tfrac{k}{g}\right) = 1]\\
\end{aligned}
$$

因为后面的 $\left\lfloor\frac{n}{g}\right\rfloor$ 和 $\frac{k}{g}$ 太麻烦了，我们考虑换元：

$$
\begin{aligned}
\text{f}(a, b) &= \sum_{i=1}^{a}i \times [\gcd(i, b) = 1]\\

\text{ans} &= k \times \sum_{g|k} \text{f}\left(\left\lfloor\tfrac{n}{g}\right\rfloor,\tfrac{k}{g}\right)
\end{aligned}
$$

然后就可以开始莫比乌斯反演了，带入公式：

$$
\begin{aligned}
\text{f}(a, b) &= \sum_{i=1}^{a}i \times [\gcd(i, b) = 1]\\
&= \sum_{i=1}^{a}\sum_{d|\gcd(i, b)}\mu(d) \times i
\end{aligned}
$$

这样虽然变得更不好算了，但是可以更换 $\sum$ 顺序：

$$
\begin{aligned}
\text{f}(a, b) &= \sum_{i=1}^{a}\sum_{d|\gcd(i, b)}\mu(d) \times i\\
&= \sum_{d|b}\sum_{i=1,d|i}^{a} \mu(d) \times i\\
&= \sum_{d|b} \mu(d) \times \sum_{i=1,d|i}^{a} i\\
&= \sum_{d|b} \mu(d) \times \sum_{i=1}^{\left\lfloor\tfrac{a}{d}\right\rfloor}i \times d\\
&= \sum_{d|b} \mu(d) \times d \times \sum_{i=1}^{\left\lfloor\tfrac{a}{d}\right\rfloor}i
\end{aligned}
$$

所以最后，我们用以下两个公式就可以算出来 $\text{ans}$ 了：

$$
\begin{aligned}
\text{f}(a, b) &= \sum_{d|b} \mu(d) \times d \times \sum_{i=1}^{\left\lfloor\tfrac{a}{d}\right\rfloor}i \\
\text{ans} &= k \times \sum_{g|k} \text{f}\left(\left\lfloor\tfrac{n}{g}\right\rfloor,\tfrac{k}{g}\right)
\end{aligned}
$$

时间复杂度：计算 $\text{f}(a, b)$ 复杂度为 $\mathcal{O}(\sqrt{b} \times \text{factors}(b))$，其中 $\text{factors}(b)$ 表示 $b$ 的因子个数。

这里 $\mathcal{O}(\sqrt b)$ 是计算 $\mu$ 的复杂度，因为 $d$ 可能超过 $10^8$ 所以不能用线性筛直接预处理 $\mu$，但是可以用线性筛筛出来质数，这样可以让计算 $\mu$ 带一个 $\mathcal{O}\left(\frac{1}{\ln(b)}\right)$ 的小常数。

计算 $\text{ans}$ 的复杂度为 $\mathcal{O}(\text{factors}(k)^2 \times \sqrt{k})$，虽然这个复杂度并不优可能过不了但是这题根本跑不满所以可以过。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long

constexpr int mod = 1000000007;

int N, K, ans;
std::vector<int> primes;
std::array<int, 10000010> fmu;
std::bitset<10000010> composite;

void sieve() {
    composite[0] = composite[1] = true;
    fmu[1] = 1;
    for (int i = 2; i <= 10000000; i++) fmu[i] = 1;
    for (int i = 2; i <= 10000000; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            fmu[i] = -1;
        }
        for (int j = 0; i * primes[j] <= 10000000; j++) {
            composite[i * primes[j]] = true;
            if (i % primes[j] == 0) { fmu[i * primes[j]] = 0; break; }
            fmu[i * primes[j]] = -fmu[i]; 
        }
    }
}

int mu(int x) {
    if (x == 1) return 1;
    int ans = 1;
    for (int i = 0; i < primes.size() && primes[i] * primes[i] <= x; i++) {
        int count = 0;
        while (x % primes[i] == 0) {
            count += 1;    
            x /= primes[i];
        } if (count > 1) return 0;
        if (count == 1) ans *= -1;
    } 
    if (x > 1) ans *= -1;
    return ans;
}

std::set<int> calcfactors(int n) {
    std::set<int> set;
    for (int i = 1; i * i <= n; i++)
        if (n % i == 0) {
            set.insert(i);
            set.insert(n / i);
        } return set;
}

int func(int n, int m) {
    // std::cout << "calculating func(" << n << ", " << m << ") = "; 
    std::set<int> a = calcfactors(m);
    int ans = 0;
    for (auto i : a) ans = ((ans + mu(i) * i % mod * ((n / i + 1) * (n / i) / 2 % mod) % mod) % mod + mod) % mod;
    // std::cout << ans << "\n";
    return ans;
}

signed main() {
    sieve();
    std::cin >> N >> K;
    std::set<int> d = calcfactors(K);
    for (auto i : d) ans = (((ans + K * func(N / i, K / i) % mod) % mod) + mod) % mod;
    std::cout << ans << std::endl;
    return 0;
}
```

---

## 作者：D2T1 (赞：0)

# 题解 [ABC020D] LCM Rush

题意：给 $n,k$，求 $\sum\limits_{i=1}^n \operatorname{lcm}(i,k)$。$1\leq n,k\leq 10^9$。

$$
\begin{aligned}
\sum_{i=1}^n \operatorname{lcm}(i,k)&=\sum_{i=1}^n \dfrac{ik}{\gcd(i,k)}\\
&=k\sum_{i=1}^n \dfrac{i}{\gcd(i,k)}
\end{aligned}
$$

枚举 $g=\gcd(i,k)$，

$$
\begin{aligned}
\sum_{i=1}^n \operatorname{lcm}(i,k)&=k\sum_{g|k}\sum_{i=1,(i,\frac kg)=1}^{\lfloor\frac ng\rfloor}i
\end{aligned}
$$

现在问题变成了，给定 $m, p$，求 $\sum\limits_{i=1,(i,p)=1}^mi$。可以容斥求解。

具体地，枚举所有 $q|p$，$q$ 每个质因子次数不大于 $1$，则

$$
\sum\limits_{i=1,(i,p)=1}^mi=\sum_q q\times \left(\sum_{i=1}^{\lfloor\frac mq\rfloor}i\right)\times val_q
$$

其中当 $q$ 的质因子个数为偶数时 $val_q=1$，否则 $val_q=-1$。（$1$ 不算质因子）

```cpp
/*
    name: LCM Rush
    id:   AT_abc020_d
    date: 2023/01/25
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll P = 1e9 + 7;
int n, k, top;
ll ans = 0;

int calc(int p){
	int sum = 1;
	for(int i = 2; i * i <= p; ++ i){
		if(p % i == 0){
			++ sum;
			p /= i;
		}
		if(p % i == 0){
			return 0;	
		}
	}
	if(p != 1){
		++ sum;
	}
	return (sum&1) ? 1 : -1;
}

#define adall(k) ((ll)(k) * ((k)+1) / 2)

ll solve(int g){
	int p = k / g, m = n / g;
	ll cur = 0;
	for(int q = 1; q * q <= p; ++ q){
		if(p % q == 0){
			cur += calc(q) * q * adall((int)m/q);
			int r = p/q;
			if(r != q){
				cur += calc(r) * r * adall((int)m/r);
			}
		}
	}
	return cur % P;
}

int main(){
	scanf("%d%d", &n, &k);
	for(int g = 1; g * g <= k; ++ g){
		if(k % g != 0){
			continue;
		}
		ans += solve(g);
		if(g * g != k){
			ans += solve(k / g);
		}
		ans %= P;
	}
	printf("%lld\n", ans * k % P);
	return 0;
}
```

---

## 作者：Mikefeng (赞：0)

# [ABC020D] LCM Rush

#### update 2023.2.22 使用alignedat环境

## 题面翻译

- 记两个正整数 $a,b$ 的最小公倍数为 $\operatorname{lcm}(a,b)$。给出两个正整数 $N(1\le N\le 10^9)$ 和 $K(1\le K\le 100)$。对于所有整数 $i(1\le i\le N)$，累加 $\operatorname{lcm}(i,K)$ 的值，并求出这个值。由于结果可能很大，你只需要输出答案模 $10^9+7$ 的余数。
- 输入仅包含两个整数 $N$ 和 $K$。输出即为题中所求。

## 做法

$\begin{alignedat}{3}\sum_{i=1}^n\operatorname{lcm}(i,k)
&=\sum_{i=1}^n\frac{i\times k}{\gcd(i,k)}
\\&=k\times\sum_{d|k}\frac{1}{d}\sum_{i=1}^n[\gcd(i,k)=d]i
\\&=k\times\sum_{d|k}\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(i,\frac{k}{d})=1]i
\end{alignedat}$

后面一部分提出来得：

$\begin{alignedat}{2}\sum_{i=1}^n[\gcd(i,m)=1]i
&=\sum_{i=1}^ni\sum_d[d|i][d|m]\mu(d)
\\&=\sum_{d|m}\mu(d)dS(\lfloor\frac{n}{d}\rfloor)
\end{alignedat}$

$$S(n)=\frac{n\times(n+1)}{2}$$

考虑不用暴力求太多次莫比乌斯函数，时间复杂度为 $O(d(k)^2)$。

## 代码

```cpp

const ll N=5e6+5;
const ll p=1e9+7;
ll n,k,cnt,ans;
bool vis[N];
ll mu[N],prime[N];
inline void init(ll n){
	mu[1]=1;
	F(i,2,n){
		if(!vis[i]){
			mu[i]=-1;
			prime[++cnt]=i;
		}
		for(ll j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]]=-mu[i];
		}
	}
}
vector<int> v;
inline ll get_mu(ll n){
	if(n<=5e6) return mu[n];
	ll res=0;
	for(ll i=1;prime[i]*prime[i]<=n;i++){
		if(n%prime[i]==0){
			res++;
			ll num=0;
			while(n%prime[i]==0) n/=prime[i],num++;
			if(num>1) return 0;
		}
	}
	if(n>1) res++;
	return res&1?-1:1;
}
inline ll S(ll x){
	return x*(x+1)/2%p;
}
inline ll get_ans(ll n,ll m){
	ll res=0;
	for(ll i:v){
		if(i>m) break;
		if(m%i) continue;
		res=(res+get_mu(i)*i%p*S(n/i)%p)%p;
	}
	return res;
}
int main(){
	n=read();k=read();
	init(5e6);
	for(ll i=1;i*i<=k;i++){
		if(k%i==0){
			v.push_back(i);
			if(i*i!=k) v.push_back(k/i);
		}
	}
	sort(v.begin(),v.end());
	for(ll i:v) ans=(ans+get_ans(n/i,k/i))%p;
	ans=(ans+p)%p;
	printf("%lld\n",k*ans%p);
	return 0;
}

```


---

## 作者：Feyn (赞：0)

先推式子。

$$\begin{aligned}
\text{ans}=&\sum\limits_{i=1}^m\text{lcm}(i,k)\\
=&\sum\limits_{i=1}^m\dfrac{ik}{\gcd(i,k)}\\
=&\sum\limits_{g=1}^{\min(m,k)}\sum\limits_{i=1}^m\dfrac{ik}{g}[\gcd=g]\\
=&k\sum\limits_{g|k}\sum\limits_{i=1}^{\lfloor\frac{m}{d}\rfloor}i\varepsilon(\text{gcd}^{'})
\end{aligned}$$

把后面那一堆拎出来反演可以得到：

$$\sum\limits_{i=1}^{\lfloor\frac{m}{d}\rfloor}i\varepsilon(\text{gcd}')=\sum\limits_{i=1}^{\lfloor\frac{m}{d}\rfloor}i\sum\limits_{t|\text{gcd}'}\mu(t)=\sum\limits_{t|k}t\mu(t)\sum\limits_{i=1}^{\lfloor\frac{m}{dt}\rfloor}i$$

然后可以快速求得。问题在于如何知道 $\mu(t)$ 的值，只需要先求大概 $10^7$ 的 $\mu$，然后大于这个值的 $t$ 可以想到不会太多，所以暴力去算就可以了。一个需要注意的地方就是考虑到 $\gcd'$ 的实际含义是 $\gcd(\frac{i}{g},\frac{k}{g})$，所以显然有 $\gcd'\le \frac{k}{g}$，需要特殊处理一下。令 $d(k)$ 表示 $k$ 的因数个数，那么复杂度是 $O(d(k)^2)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=5000010;
const int mod=1e9+7;
using namespace std;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,k;

int p[N>>2],cnt,mu[N];
bool vis[N];
void init(){
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(vis[i]==false)p[++cnt]=i,mu[i]=-1;
		for(int j=1;i*p[j]<N;j++){
			vis[i*p[j]]=true;if(i%p[j]==0)break;
			mu[i*p[j]]=-mu[i];
		}
	}
}
map<int,int>reM;
inline int work(int val){
	if(val<N)return mu[val];
	if(reM.count(val))return reM[val];
	for(int i=1;p[i]*p[i]<=val;i++){
		if(val%p[i])continue;val/=p[i];
		if(val%p[i]==0)return 0;
		else return -work(val);
	}
	return -1;
}
inline int ff(int wh){return wh*(wh+1)/2%mod;}

int num,c[100],d[100],a[N>>2],top;
void dfs(int wh,int val){
	if(wh>num)return a[++top]=val,void();
	for(int i=0;i<=d[wh];i++)dfs(wh+1,val),val*=c[wh];
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(k);init();int kk=k,ans=0;
	for(int i=1;p[i]*p[i]<=k;i++){
		if(k%p[i])continue;
		c[++num]=p[i];
		while(k%p[i]==0)k/=p[i],++d[num];
	}
	if(k>1)c[++num]=k,d[num]=1;dfs(1,1);
	sort(a+1,a+top+1);
	for(int i=1;i<=top;i++){
		for(int j=1;j<=top;j++){
			int g=a[i],t=a[j];
			if(kk%(g*t))continue;
			ans+=t*work(t)*ff(m/(g*t));ans%=mod;
		}
	}
	ans*=kk;printf("%lld\n",(ans%mod+mod)%mod);
	
	return 0;
}
```

---

## 作者：S00021 (赞：0)

题意：给定 $n,k$ ，求 $\sum_{i=1}^n \text{lcm}(i,k)$，$n,k\le 10^9$。

因为 $\LaTeX$ 较多所以就丢洛谷上了。

非常套路的题，然而我有非常奇怪的做法...老年退役选手哭了。

原式可以变为 ：
	
  $$\sum_{i=1}^n \dfrac{ik}{\gcd(i,k)}$$
   
接着枚举 $\gcd$ 变为：

  $$\sum_{d=1}^n [d|k] \sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} ik [\gcd(i,\frac{k}{d})=1]$$
   
令 
  $$\text{sum}(t,d)=\sum_{i=1}^{t} i [\gcd(i,\frac{k}{d})=1]$$
    
考虑利用 $\epsilon(n) = \sum_{i|n} \mu(i)$，进行莫比乌斯反演：

  $$\text{sum}(t,d)=\sum_{i=1}^{t} i \sum_{u|i,u|\frac{k}{d}} \mu(u)$$
   
枚举 $u$：

  $$\text{sum}(t,d)=\sum_{u|\frac{k}{d}} \mu(u) \sum_{i=1}^{\lfloor \frac{t}{u} \rfloor} i$$
   
所以原式和上式均可在 $O(d(k))$ 的复杂度内求得，总复杂度 $O(d(k)^2)$，其中 $d(k)$ 为 $k$ 的因数个数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define pb push_back
#define N 200005
#define fi first
#define se second
#define M 1000000007
using namespace std;
int n,k; map<int,int>miu,vis;
int getmiu(int x){
	if(x==1) return 1; 
	if(vis[x]) return miu[x]; 
	vis[x]=1; int ret=x,an=1;
	for(int i=2;i*i<=x;i++){
		int cn=0; while(ret%i==0) ret/=i,++cn;
		if(!cn) continue;
		if(cn>1) return miu[x]=0;
		an*=-1;
	}if(ret>1) an*=-1;
	return miu[x]=an;
}int o(int x){return (x*(x+1)/2)%M;}
int sur(int T,int p){return p*getmiu(p)%M*o(T/p)%M;}
int sum(int T,int p){
	int ret=0;
	for(int u=1;u*u<=p;u++){
		if(p%u) continue;
		ret=(ret+sur(T,u))%M;
		if(u!=p/u) ret=(ret+sur(T,p/u))%M;
	}return k*ret%M;
}signed main(){
	scanf("%lld%lld",&n,&k); int ans=0;
	for(int d=1;d*d<=k;d++){
		if(k%d) continue;
		ans=(ans+sum(n/d,k/d))%M;
		if(d!=k/d) ans=(ans+sum(n/(k/d),d))%M;
	}printf("%lld\n",(ans+M)%M);
	return 0;
}
```

---

