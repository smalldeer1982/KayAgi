# Multipliers

## 题目描述

Ayrat has number $ n $ , represented as it's prime factorization $ p_{i} $ of size $ m $ , i.e. $ n=p_{1}·p_{2}·...·p_{m} $ . Ayrat got secret information that that the product of all divisors of $ n $ taken modulo $ 10^{9}+7 $ is the password to the secret data base. Now he wants to calculate this value.

## 说明/提示

In the first sample $ n=2·3=6 $ . The divisors of $ 6 $ are $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ , their product is equal to $ 1·2·3·6=36 $ .

In the second sample $ 2·3·2=12 $ . The divisors of $ 12 $ are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 6 $ and $ 12 $ . $ 1·2·3·4·6·12=1728 $ .

## 样例 #1

### 输入

```
2
2 3
```

### 输出

```
36
```

## 样例 #2

### 输入

```
3
2 3 2
```

### 输出

```
1728
```

# 题解

## 作者：waauto (赞：4)

简化题意：

$$
\prod_{i|n}^{n}i \pmod {10^9+7}
$$

假设$a|n$，则有$\frac{n}{a}|n$
，他们的乘积就是$n$。

也就是说，我们假设$n$有$k$个因数，答案就是：
$$
n^{\frac{k}{2}} \pmod{10^9+7}
$$

由于$10^9+7$是质数根据费马小定理：

$$
n^{10^9+6} \equiv 1 \pmod{10^9+7}
$$

那么答案就是：

$$
n^{\frac{k}{2}\%10^9+6} \pmod{10^9+7}
$$

假设$n$的标准质因分解是：

$$
n=p_1^{a_1}p_2^{a_2}....p_n^{a_n}
$$

那么因子数量就是：

$$
sum=\prod_{i=1}^{n}(a_i+1)
$$
这个很好理解，对于每个质数都有$a+1$种取方法，乘起来即可。

那么答案就出现了，注意特判$n$是完全平方数的情况即可。

可以选择模数扩大两倍防止除以二的时候炸。

~~使用桶排序优化至O(n)~~

目前的最优解。
![](https://cdn.luogu.com.cn/upload/image_hosting/hc8w55gk.png)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int p[200005];
const int mod=1e9+7,phi=2*(mod-1);
inline int qpow(int a,int b,int p){
    int res=1;
    while(b){
        if(b&1)res=1ll*res*a%p;
        a=1ll*a*a%p;
        b>>=1;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,ans=1,tot=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        p[num]++;
        if(p[num]%2)tot++;
        else tot--;
        ans=ans*num%mod;
    }
    int sums=1;
    for(int i=1;i<=200000;i++){
        sums=sums*(p[i]+1)%phi;
    }
    sums=sums/2;
    int g=1;
   // cout<<tot<<endl;
    if(tot==0){
        for(int i=1;i<=200000;i++){
            g=g*qpow(i,p[i]/2,mod)%mod;
        }
    }
    cout<<g*qpow(ans,sums,mod)%mod;
    return 0;
}
```


---

## 作者：Warriors_Cat (赞：4)

一道数论好题，特别是后面的分类讨论。

### $Solution:$

首先，由于代数式基本定理，我们可以把这个数分解质因数并求出它的因数个数：

$$A = \prod_{i=1}^m p_i^{\alpha_i}$$

$$d(A) = \prod_{i=1}^m(\alpha_i + 1)$$

然后我们对每一个 $p_i$ 来计算它的贡献。

对于每一个 $p_i$，有可能有 $1$ 个，$2$ 个，一直到 $\alpha_i$ 个，所以先会有：

$$p_i \times {p_i}^2\times {p_i}^3\times ...\times {p_i}^{\alpha_i}=p_i^{\frac{\alpha_i\times(\alpha_i+1)}{2}}$$

然而还剩下其它的质因数可选可不选，很显然选择的方案为 $\frac{d(A)}{(\alpha_i+1)}$。

于是一个 $p_i$ 对于答案来说就要乘上：

$$p_i^{\frac{\alpha_i\times(\alpha_i+1)}{2}}\times p_i^{\frac{d(A)}{(\alpha_i+1)}}$$

$$\text{即}\ p_i^{\frac{\alpha_id(A)}{2}}$$

于是答案就呼之欲出了：

$$Ans = \prod_{i=1}^{m}p_i^{\frac{\alpha_id(A)}{2}}$$

但这里有一个 $\frac{1}{2}$，不好边取模边除，所以我们进行分类讨论：

$1. d(A)\equiv0(\!\!\!\!\mod\ 2)$，那么直接重算 $\frac{d(A)}{2}$ 即可。

$2. d(A)\equiv1(\!\!\!\!\mod\ 2)$，那么所有的 $\alpha_i$ 都是偶数，所以直接全部除以 $2$ 即可。

然后这道题就没了……

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define int long long
#define fi first
#define se second
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int mod = 1000000007;
inline int fpow(int n, int p){
	n %= mod; int ans = 1, base = n;
	while(p){
		if(p & 1) ans = ans * base % mod;
		base = base * base % mod;
		p >>= 1;
	}
	return ans;
}
int n, vis[200010], cj = 1, ans = 1;
vector <pair <int, int> > mp;
bool flag = 1;
signed main(){
	n = read();
	for(int i = 1; i <= n; ++i) vis[read()]++;
	for(int i = 1; i <= 200000; ++i) cj = cj * (vis[i] + 1) % (mod - 1);
	for(int i = 1; i <= 200000; ++i) if(vis[i]) mp.push_back(make_pair(vis[i], i));
	for(int i = 0; i < mp.size(); ++i){
		if(mp[i].fi & 1){
			flag = 0;
			break;
		}
	}
	if(flag){//情况 2
		for(int i = 0; i < mp.size(); ++i) mp[i].fi >>= 1;
		for(int i = 0; i < mp.size(); ++i) ans = ans * fpow(mp[i].se, cj * mp[i].fi % (mod - 1)) % mod;
	}
	else{//情况 1
		cj = 1; bool FI = 1;
		for(int i = 0; i < mp.size(); ++i){
			if(mp[i].fi & 1 && FI){
				FI = 0;
				cj = cj * (mp[i].fi + 1) / 2 % (mod - 1);
			}
			else cj = cj * (mp[i].fi + 1) % (mod - 1);
		}
		for(int i = 0; i < mp.size(); ++i) ans = ans * fpow(mp[i].se, cj * mp[i].fi % (mod - 1)) % mod;
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：LJ07 (赞：2)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF615D)

## 思路简述

~~由于题号打错而找到的一道水紫。~~

显然地，我们可以考虑每个质因子对答案的贡献。

不妨规定

1. 数 $Num$ 可以表示成 $Num=\prod p_i^{e_i}$。

2. $d(x)$ 表示 $x$ 的因子个数

那么显然答案就是 $\prod p_i^{t_i}$。

其中 $t_i=\frac{e^i\times (e^i-1)}{2}\times d(\dfrac{Num}{p_i^{e_i}})$

直接快速幂计算显然会 TLE，那么我们考虑减小指数的大小。

由欧拉定理，$t_i=\frac{e^i\times (e^i-1)}{2}\times d(\dfrac{n}{p_i^{e_i}}) \mod (P-1)$

$d(Num)$ 由因子个数定理是容易的：$d(Num)=\prod e_i+1$。

那么 $d(\dfrac{Num}{p_i^{e_i}})=\frac {d(Num)}{e_i+1}$。

由于模的是一个合数，不好逆元，前缀积优化即可。

## 丑陋の代码

[click here](https://www.luogu.com.cn/paste/r362stts)

---

## 作者：GKxx (赞：2)

在讨论里看到了这道题，于是就来做一下，顺便发个题解。

首先，直接把所有数乘起来再枚举约数肯定是不行的，但是我们可以换一个角度想：对于原数$N$，它的所有约数都有一个特点。

本题的输入也提示了我们：将$N$质因子分解得到

$N=\prod_{i=1}^k p_i^{\alpha_i}$

那么$N$的所有约数$d$一定可以表示为

$d=\prod_{i=1}^k p_i^{\beta_i}, 0\leq \beta_i\leq\alpha_i$

现在要求所有的$d$的乘积$ans$，不难发现，$ans$也可以用这些质因子来表示：

$ans=\prod_{i=1}^k p_i^{c_i}$

现在问题在于$c_i$是什么，以及如何快速求出$c_i$

对于每个$p_i$，我们考虑：$N$有多少个约数含有$1$个$p_i$？有多少个约数含有$2$个$p_i$？有多少个约数含有$3$个$p_i$？......

$N$有多少个约数含有$t$个$p_i$？（$1\leq t\leq\alpha_i$）首先可以发现，对于所有的$t$，这个问题的答案都是一样的，它就相当于在问$N'=\prod_{j=1}^k p_i^{\alpha_i}[j\neq i]$，$N'$有多少个约数？显然答案是

$\prod_{j=1}^k(\alpha_j +1)[j\neq i]$，也即 $\frac{\prod_{j=1}^k(\alpha_j +1)}{\alpha_i+1}$

所以我们就可以回答第一个问题：$c_i=\frac{\prod_{j=1}^k(\alpha_j +1)}{\alpha_i+1}*(1+2+...+\alpha_i)$

$=\frac{\prod_{j=1}^k(\alpha_j +1)}{\alpha_i+1}*\frac{(\alpha_i+1)\alpha_i}{2}$

$=\frac{1}{2}\alpha_i\prod_{j=1}^k(\alpha_j +1)$

那么$ans=\prod_{i=1}^k p_i^{\frac{1}{2}\alpha_i\prod_{j=1}^k(\alpha_j +1)}$

考虑如何快速计算这个式子。

首先我觉得这个$\frac{1}{2}$有点讨厌，因为这涉及到除法运算，但是显然这个指数一定是整数。因为如果所有的$\alpha_i$都是偶数，就可以将它们与$2$约分；而只要有一个$\alpha_i$是奇数，就可以将$\alpha_i+1$与$2$约分。

基于这个想法，我们可以分这两种情况改写这个式子。记$prod_1=\prod_{j=1}^k(\alpha_j +1), prod_2=\frac{1}{2}\prod_{j=1}^k(\alpha_j +1)$
- 当所有$\alpha_i$都是偶数的时候，$ans=(\prod_{i=1}^k p_i^{\frac{1}{2}\alpha_i})^{prod_1}$
- 当有一个$\alpha_{pos}$是奇数的时候，$ans=(\prod_{i=1}^k p_i^{\alpha_i})^{prod_2}$

现在问题来了：无论是$prod_1$还是$prod_2$都可能会非常大，如何降指数？

#### 降指数神器：扩展欧拉定理

对于$\forall a,b,p$都有$a^b \mod p =a^{b \mod \varphi(p)+\varphi(p)} \mod p$

证明这里略去，请自行百度。

本题$p=10^9+7$是质数，故$\varphi(p)=10^9+6$。

利用扩展欧拉定理我们就可以求$prod_1$和$prod_2$了。（求$prod_2$的时候，我是先找到一个奇数$\alpha_{pos}$，然后拿它$+1$去和$2$约分）

剩下的事情就只要快速幂即可。

分析一下时间复杂度：显然应该是$O(k\log_2{\alpha_i})$，其中$k$是不同的$p_i$的个数，注意到此题$n$与$p_i$同阶，由于$n$以内的质数只有大约$n/(\ln n)$个，所以$k\leq n/(\ln n)$。而$\alpha_i$不会超过$n$，所以复杂度是$O(\frac{n\log_2 n}{\ln n})=O(n\log_2 e)=O(n)$。

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define dwn(I, A, B) for (int I = (A); I >= (B); --I)
#define erp(I, X) for (int I = head[X]; I; I = next[I])

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t); read(args...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> void writeln(T x) {
    write(x);
    puts("");
}
template <typename T> inline bool chkMin(T& x, const T& y) { return y < x ? (x = y, true) : false; }
template <typename T> inline bool chkMax(T& x, const T& y) { return x < y ? (x = y, true) : false; }

typedef long long LL;
const int maxn = 2e5 + 207;
const LL mod = 1e9 + 7, phi = 1e9 + 6;
LL p[maxn], a[maxn], n, k;
LL buk[maxn];

inline LL mul(LL x, LL k, LL mod) {
    return (x % mod) * (k % mod) % mod;
}
inline LL quickPow(LL x, LL k, LL mod) {
    LL s = 1;
    for (; k; x = mul(x, x, mod), k >>= 1)
        if (k & 1) s = mul(s, x, mod);
    return s;
}

int main() {
    read(n);
    LL mv = 0;
    rep(i, 1, n) {
        LL x; read(x);
        ++buk[x];
        chkMax(mv, x);
    }
    rep(i, 1, mv) if (buk[i]) {
        p[++k] = i;
        a[k] = buk[i];
    }
    bool alleven = 1;
    rep(i, 1, k) if (a[i] & 1) { alleven = 0; break; }
    if (alleven) {
        LL prod = 1;
        rep(i, 1, k) prod = prod * (a[i] + 1) % phi;
        prod += phi;
        LL ans = 1;
        rep(i, 1, k) ans = mul(ans, quickPow(p[i], a[i] / 2, mod), mod);
        ans = quickPow(ans, prod, mod);
        writeln(ans);
    } else {
        LL prod = 1;
        int pos;
        rep(i, 1, k) if (a[i] & 1) { pos = i; break; }
        rep(i, 1, k) {
            if (i != pos) prod = prod * (a[i] + 1) % phi;
            else prod = prod * ((a[i] + 1) / 2) % phi;
        }
        prod += phi;
        LL ans = 1;
        rep(i, 1, k) ans = mul(ans, quickPow(p[i], a[i], mod), mod);
        ans = quickPow(ans, prod, mod);
        writeln(ans);
    }
    return 0;
}
```

---

## 作者：DarkMoon_Dragon (赞：2)

# 题意:给你一个数，输出其所有因数的乘积。
## $Solution$: 对于每个因子单独计算其贡献
+ 运用唯一分解定理将给定数$n$分解为$x_1^{a_1}*x_2^{a_2}*x_3^{a_3}*\cdots x_n^{a_n}$
+ 对于每个因子单独讨论其贡献(这里不能用二进制算集合讨论),乘法原理,对于$x_1$ ,其余每个指数的选择为$a_n+1$贡献$x_1^{(a_2+1)*(a_3+1)*\dots *(a_n+1)}$ 
+ 然后讨论$x_1$的指数,分配率可得$x_1$的系数和为$\sum _{i=1}^{n}{a_i}$ 即为$(1+a_n)*n/2$ 
+ 令 $M=(a_1+1)*(a_2+1)*...*(a_n+1)$,那么$x_1$贡献为$x_1^{M*a_1/2}$
+ 然后处理"指数爆炸"~~(此处应卷舌)~~,应注意的是
$a^b\%p\neq a^{(b\%p)}\%p$

### 法一:考虑费马小定理($p$是质数就直接用了)(快速幂就别想了)
$$
  a^{\phi(p)}\equiv 1(mod~p)
$$
+ 所以$x^{p-1}\equiv 1(mod~p)$ 
+ 化简$x^{M*a/2}$,指数可以写成(模数分解)$M*a/2=k*(p-1)+y$
+ 原式等于$x^{k*(p-1)}*x_1^{y}\%p=x_1^{y}\%p$
+ 得到$a^b\%p=a^{(b\%(p-1))}\%p$
+ 因为同余,前面的乘法就变成了1(费马小就是这么用的),*那么说明指数可以模p-1=1e9+6*
+ 需要注意的是这里$/2$可能不整除,所以前面预处理时$M$是模数扩大两倍保证预留$2$因子

#### 也可以运用指数循环节证明
+ 指数循环节通式为 
$$
  a^{b}\equiv a^{b\%\phi(p)+\phi(p)}(mod~p),b\geq \phi(p)
$$
+ $p$为指数时,$\phi(p)=p-1$,带入利用费马小定理化简$x^{p-1}\equiv 1(mod~p)$ 也可以得到$a^b\%p=a^{(b\%(p-1))}\%p$

               
### 法二:预处理前缀后缀省去$/2$

法一代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define rr register int
using namespace std;
typedef long long ll;
inline ll read(){
    char i=getchar();
    ll dp=1,res=0;
    while(i<'0'||i>'9'){if(i=='-')dp=-1;i=getchar();}
    while(i>='0'&&i<='9'){res=res*10+i-'0';i=getchar();}
    return res*dp; 
}
const ll mod=1000000007;
ll quickpow(ll tmp,ll b,ll mod){
	ll res=1;
	tmp%=mod;//乘法可模 
	b=b%(mod-1);
	while(b){
		if(b&1) res=(res*tmp)%mod;
		tmp=(tmp*tmp)%mod;
		b>>=1;
	}
	return res;
}
const int N=2e5+50;
ll n,cnt;
ll x[N],tmp[N],a[N];
//a[i] 指数个数 
int main(){
	n=read();
	int cnt=0;
	for(rr i=1;i<=n;++i) tmp[i]=read();
	sort(tmp+1,tmp+n+1);
	for(rr i=1;i<=n;++i){
		if(i==1||tmp[i]!=tmp[i-1]){
			x[++cnt]=tmp[i];
			a[cnt]=1;
		}else a[cnt]++;
	}
	ll M=1,ans=1;
	for(rr i=1;i<=cnt;++i) M=(M*(a[i]+1))%(2*mod-2);
	for(rr i=1;i<=cnt;++i){
		ans=ans*quickpow(x[i],M*a[i]/2%(2*mod-2),mod)%mod;
	}
	printf("%lld\n",ans%mod);
}
```

---

## 作者：Vct14 (赞：1)

duel 到这题了，模数问题卡我十几发。/fn/fn

题意：输入 $n$ 个质数 $a_i$，输出 $m=\prod\limits_{i=1}^np_i$ 所有因数的乘积。

设 $s$ 为 $m$ 不同素因子个数，$t$ 为 $m$ 因子个数。

由 $x\times\dfrac{m}{x}=m$，答案即为 $m^{\frac{t}{2}}$。~~由小奥可知~~，设 $sum_i$ 为从小到大第 $i$ 个素因子 $p_i$ 出现的次数，$t=\sum\limits_{i=1}^s(sum_i+1)$。

我们求出 $m^{\lfloor\frac{t}{2}\rfloor}$，如果 $m$ 为完全平方数（即 $sum_i$ 均为偶数），那么答案乘上 $\sqrt{m}=\prod\limits_{i=1}^s p_i^{\frac{sum_i}{2}}$。

我们知道 $t$ 可能会巨大无比，那么如何求出 $m^{\lfloor\frac{t}{2}\rfloor}\bmod 10^9+7$ 呢？这里给大家介绍[扩展欧拉定理](https://zhuanlan.zhihu.com/p/131536831)：

$$a^b\equiv a^{b\bmod \varphi(m)+\varphi(m)}\pmod m$$

由 $10^9+7$ 为素数，由费马小定理有 $\varphi(10^9+7)=10^9+6$。则 $m^{\lfloor\frac{t}{2}\rfloor}\bmod 10^9+7=m^{\lfloor\frac{t}{2}\rfloor\bmod (2\times(10^9+6))}=m^{\lfloor\frac{t\bmod (2\times(10^9+6))}{2}\rfloor}$。这样就不会爆 `long long` 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long

const int N=2e5+2;
const int mod=1e9+7;
const int mmod=2*mod-2;
const int MAX=2e5;
int sum[N];

int qpow(int a,int b){
	int bs=a,ans=1;
	while(b){
		if(b%2) ans=ans*bs%mod;
		bs=bs*bs%mod;b>>=1;
	}
	return ans;
}

signed main(){
	int n;cin>>n;int m=1;
	for(int i=1; i<=n; i++){
		int p;cin>>p;
		m=m*p%mod;sum[p]++;
	}
	int t=1;bool odd=0;
	for(int i=1; i<=MAX; i++){
		if(sum[i]){
			t=t*(sum[i]+1)%mmod;
			if(sum[i]%2) odd=1;
		}
	}
	int ans=qpow(m,t/2);if(!odd) for(int i=1; i<=MAX; i++) if(sum[i]) ans=ans*qpow(i,sum[i]/2)%mod;
    cout<<ans%mod;
	return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：1)

# CF615D题解

### 题意

以给定质因子的形式给定一个数 $n$，并给出具体的质因子，求：

$$\prod_{d\mid n}d$$

### Solution

我们唯一分解 $n$，使得 $n=\prod p_i^{\alpha_i}$，我们考虑对于每一个素数 $p_i$，它在质因子中可能以 $p_i^k(0\le k\le \alpha_i)$ 的形式出现，即一共 $\frac{\alpha_i\times(\alpha_i+1)}{2}$ 次。并且对于每个幂 $k$，都会在别的质因子取任何值的时候出现，即对于一个 $p_i^k$，它会出现 $\frac{\prod_j(\alpha_j+1)}{\alpha_i+1}$ 次，因此它的贡献就是

$$p_i^{\frac{\prod_j(\alpha_j+1)}{\alpha_i+1}\times\frac{\alpha_i\times(\alpha_i+1)}{2}}=p_i^{\frac{\alpha_i\prod(\alpha_i+1)}{2}}$$

这个东西就计算 $\prod(\alpha_i+1)$，然后每次乘 $\alpha_i$ 放在 $p_i$ 的指数上。

记 $s=\prod(\alpha_i+1)$，于是现在的答案就是

$$\prod p_i^{\frac{s\times \alpha_i}{2}}$$

但是 $s\times \alpha_i$ 可能会非常大，而且它在指数上，因此我们用拓展欧拉公式对指数进行降幂。

因为 $\alpha_i$ 与 $\alpha_i+1$ 都在乘积中，因此除以二一定为整数。但对于模数的情况下，我们并不能保证是整数，因此我们还需要进行判断。

- 对于 $\alpha_i+1$ 有偶数的情况，再求乘积的时候就将某个 $\alpha_i+1$ 除以二，后面直接乘 $\alpha_i$ 就行。

- 对于 $\alpha_i+1$ 全部为奇数，即 $\alpha_i$ 全部为偶数，直接在最后计算的时候将 $\alpha_i$ 除以二再乘进去就可以了。

具体的看代码吧。

### CODE

``` cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<set>
#include<vector>
#include<map>

using namespace std;

const int N = 2e5 + 10;
const int M = 2e5 + 10;
#define endl '\n'
#define int long long
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n,m,phi=MOD-1;
int t[N],cnt,sum=1;
bool flag=false;

int ksm(int x,int k){
	int ans=1;
	while(k){
		if(k&1)	ans=ans*x%MOD;
		x=x*x%MOD; k>>=1; 
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;++i)	cin>>x, t[x]++, m=max(m,x);
	for(int i=1;i<=m;++i){
		if((t[i]+1)%2==0&&!flag)	sum=sum*(t[i]+1)/2%phi, flag=true;
		else	sum=sum*(t[i]+1)%phi;
	}
	int ans=1;
	for(int i=1;i<=m;++i){
		if(t[i]==0)	continue;
		int y;
		if(flag)	y=sum*t[i]%phi;
		else	y=sum*t[i]/2%phi;
		ans=ans*ksm(i,y+phi)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：AzureHair (赞：1)

**本题为 MLEOI 的 T2，在赛场上因挂了 70 分被罚玩 3 小时原神，故来写一篇题解纪念一下。**

简明题干：求一个数的所有因数的乘积。

对于这道题，只要是一个没有学过 OI 的人都能在 5s 内切了，但是我并没有想到两个因数相乘等于原数这个性质（说白了就是我菜）。

所以这边我提供一种奇怪的思路。

本题给定了他的质因数分解，所以考虑每个质因子的出现次数，我们设第 $i$ 个质因子是 $b_i$,他在质因数分解中出现了 $a_i$ 次，那我们容易想到，总共有 
$\prod\limits_{i=1}^{cnt}(a_i+1)$ 个因数，现在我们考虑在这些因数中出现了多少次某个质因子，首先先计算除要求的第 $i$ 个质因子外的其余质因子的出现情况，即 $\prod\limits_{j=1}^{cnt}(a_j+1)(j\ne i)$，再计算该质因子的出现次数，容易发现，是个等差数列求和，利用等差数列求和公式，我们可以得到，第  $i$ 个质因子的出现次数为 $\frac{a_i(a_i+1)}{2}\times\prod\limits_{j=1}^{cnt}(a_j+1)(j\ne i)$ 这样问题就迎刃而解了，只需要算出 $\prod\limits_{i=1}^{cnt}b_i^{\frac{a_i(a_i+1)}{2}\times\prod\limits_{j=1}^{cnt}(a_j+1)(j\ne i)}$ 最后写一个前缀和优化一下即可，是不是非常的简单，所以下面放代码，有一些需要注意的小细节。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int mod=1e9+7;
int m,a[200010],b[200010],s1[200010],s2[200010],cnt=0,ans=1;
map<int,int> mp;
int ksm(int x,int y)
{
	int tmp=1;
	while(y)
	{
		if(y&1)
		{
			tmp=tmp*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return tmp%mod;
}
signed main()
{
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int x;
		cin>>x;
		if(mp[x])
		{
			a[mp[x]]++;
		}
		else
		{
			mp[x]=++cnt;
			a[mp[x]]=2;//这里我提前将个数的+1记录下来了，所以后面的a[i]*(a[i]+1)/2自然就变成a[i]*(a[i]-1)/2了
			b[mp[x]]=x;
		}
	}
	s1[0]=1;s2[cnt+1]=1;
	for(int i=1;i<=cnt;i++)
	{
		s1[i]=s1[i-1]*a[i]%(mod-1);//注意这里一定要取模mod-1啊啊啊啊，我在这里挂了70pts，被罚玩三小时原神
	}
	for(int i=cnt;i>=1;i--)
	{
		s2[i]=s2[i+1]*a[i]%(mod-1);
	}
	for(int i=1;i<=cnt;i++)
	{
		int tmp=((a[i]*(a[i]-1)/2)%(mod-1))*(s1[i-1]*s2[i+1]%(mod-1))%(mod-1);//这里要小心爆long long，如果等差数列求和完不取模会比long long上限高一点点，导致WA on#54
		//cout<<tmp<<endl;
		ans=ans*ksm(b[i],tmp)%mod;
	}
	cout<<ans%mod<<endl;
	return 0;
}
```
祝早日 AC。

---

## 作者：johnsmith0x3f (赞：1)

## 0x00 Outline

- 给定一个数 $n$ 的质因子分解，求其所有因数的乘积。

## 0x01

- 其他题解已经介绍了计算 $\text{ans}$ 的公式的推导过程，这里提供一种码量更小的思路。

- 考虑逐个加入每种质因子产生的贡献。

- 设 $n = \displaystyle\prod_{i=1}^m p_i^{\alpha_i}$ 为 $n$ 的质因子分解，且现在要加入第 $i$ 个质因子的贡献，特别地，令 $p_0 = 1, \alpha_0 = 0$。

- 则之前的因数个数为 $N = \displaystyle\prod_{k=0}^{i-1} (\alpha_k+1)$，设其中第 $j$ 个因数为 $a_j$，则所有因数的乘积 $P = \displaystyle\prod_{k=1}^N a_k$。

- 加入 $p_i^{\alpha_i}$ 的贡献后，对于某一个因数 $a_j$，对应地会产生 $\alpha_i$ 个新的因数 $a_j p_i, a_jp_i^2, \ldots, a_jp_i^{\alpha_i}$，则 $a_j$ 的贡献由 $a_j$ 变为 $a_j^{\alpha_i+1} \cdot p_i^{\frac {\alpha_i(\alpha_i+1)} 2}$。

- 则所有因数的乘积 $P$ 变为 $P' = \displaystyle\prod_{k=1}^N (a_k^{\alpha_i+1} \cdot p_i^{\frac {\alpha_i(\alpha_i+1)} 2}) = P^{\alpha_i+1} \cdot p_i^{\frac {N \alpha_i(\alpha_i+1)} 2}$。

---

## 作者：_edge_ (赞：1)

前置知识：欧拉函数。

先令 $num_i$ 表示 $i$ 这个质数出现多少次。

我们可以发现它这个东西可以每一个质因子单独算贡献，然后你就不停地推柿子，大概能推出：

$tot=num_{p1+1} \times num_{p2+1} \times \cdots \times num_{pm+1}$。

令 $k$ 为质数个数。

$ans= \prod \limits _{i=1}^{k} pi^{tot \times num_{pi} \times (num_{pi}+1) /2 /num_{pi}}$。

大概想法就是，忽略当前枚举的质数，那么就是 $tot/num_{pi}$，然后我们发现当前枚举的质数，有可能是二次幂，三次幂或者更高次幂，这是一个等差数列的形式。

然后将其化简，可以得到：

$ans= \prod \limits _{i=1}^{k} pi^{tot \times (num_{pi}+1) /2}$。

然后我们发现仅仅是 $tot$ 数量就是 $10^{10^5}$ 还不止，按照现在的计算水平，~~这个高精度可以搞一下~~，或许还要用到 FFT 之类的，，，

然后我们看到有取模，但是可惜的是不能对指数取模，然后我们就想到欧拉函数。

$a^{b \bmod \phi(n)} \equiv a^b \pmod n$。

~~这个证明的话就百度把。~~

然后我们发现 $\phi(10^9+7)=10^9+6$，因为它是一个质数。

然后，然后我们很愉快的将它带入，却发现：

$tot \times (num_{pi}+1) /2$，

有一个 $/2$ ！！！！！！！

然后我就想了很多办法，乘法逆元的话 $10^9+6$ 并非是一个质数，exgcd 的话 $10^9+6$ 和 $2$ 不互质。

然后我以为就这样没了，但是又看了看前面的东西。

$tot \times (num_{pi}+1)$，欸？$tot$ 里面是不是有一个 $num_{pi}$，它和 $(num_{pi}+1)$ 正好是连续的正整数，然后根据抽屉原理，两个肯定有一个被 $2$ 整除，然后暴力除就完事了。

处理的时候注意点细节。

代码：

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int INF=1e6+5;
const int Mod=1e9+7;
int n,p[INF],num[INF];
int ksm(int x,int y) {
        // cout<<x<<" "<<y<<"\n";
        int ans=1,ba=x%Mod;
        while (y) {
                if (y&1) (ans*=ba)%=Mod;
                (ba*=ba)%=Mod;
                y>>=1;
        }
        // cout<<ans<<"\n";
        return ans;
}
int Mod2;
signed main()
{
        ios::sync_with_stdio(false);
        cin>>n;
        for (int i=1; i<=n; i++)
                cin>>p[i],num[p[i]]++;
        Mod2=Mod-1;
        // int k=Mod;
        // for (int i=2; i*i<=k; i++) {
        //         if (k%i==0) Mod2/=i,Mod2*=(i-1);
        //         while (k%i==0) k/=i;
        // }
        // cout<<Mod2<<"\n";
        int tot=1,fl=1;
        for (int i=1; i<=1e6; i++) {
                if ((num[i]+1)%2==0 && fl) tot=(tot*(num[i]+1)/2)%Mod2,fl=0;
                else tot=(tot*(num[i]+1))%Mod2;
        }
        int ans=1;
        for (int i=1; i<=1e6; i++) {
                if (num[i]==0) continue;
                if (fl) num[i]/=2;
                int kk=ksm(i,tot*num[i]%Mod2)%Mod;
                // cout<<(tot*ksm(num[i]+1,Mod2-2)-1+Mod2)*num[i]%Mod2*(num[i]+1)%Mod2*ksm(2,Mod2-2)%Mod2<<"\n";
                (ans*=kk)%=Mod;
        }
        cout<<ans%Mod<<"\n";
        return 0;
}

```

如有问题还请指出。

---

## 作者：liugh_ (赞：0)

提供一个思路和实现都非常简洁的做法，题解区截至此文似乎未曾有该做法。

先进行唯一分解得 $n=\prod_{i=1}^{k} p_i^{\alpha_i}$，记 $s=\prod_{i=1}^{k} (\alpha_i+1)$，考虑分别计算每个质因子对答案的贡献，显然有
$$
ans=\prod_{i=1}^{k}\prod_{j=0}^{\alpha_i} p_i^{js/(\alpha_i+1)}
$$
指数太大怎么办？注意不能对 $p=10^9+7$ 取模。考虑扩展欧拉定理
$$
a^b\equiv a^{b\bmod \varphi(p)+\varphi(p)} \pmod p
$$
至于 $s/(\alpha_i+1)$，可以直接上逆元，也可以从小到大枚举 $p_i$ 时维护前后缀指数积。

时间复杂度 $\Theta((n+V)\log p)$。

```cpp
[&](){
	static constexpr int p=1e9+7,phip=p-1;
	static constexpr auto fpw=[&](int a,int b,int res=1){for(;b;b>>=1,a=1ll*a*a%p)if(b&1)res=1ll*res*a%p;return res;};
	int n,ans=1;cin>>n;vec<int> cnt(2e5+10),pre(2e5+10),suf(2e5+10);
	for(int i=pre[0]=suf[(int)2e5+1]=1,x;i<=n;i++)cin>>x,cnt[x]++;
	for(int i=1;i<=2e5;i++)pre[i]=1ll*pre[i-1]*(cnt[i]+1)%phip;
	for(int i=2e5;i>=1;i--)suf[i]=1ll*suf[i+1]*(cnt[i]+1)%phip;
	for(int i=1;i<=2e5;i++)
		for(int j=1,cur=1;j<=cnt[i];j++)
			ans=1ll*ans*fpw(cur=1ll*cur*i%p,1ll*pre[i-1]*suf[i+1]%phip+phip)%p;
	cout<<ans;
}();
```

---

## 作者：01bit (赞：0)

设 $n=\prod_{i} p_i^{r_i}\quad(\forall\lambda,\mu\in[1,m],p_\lambda\ne p_\mu)$ 。
则答案为：
$$\begin{aligned}
ans&=\prod_{i}p_i^{\sum_{j=0}^{r_i}j\prod_{j\ne i}(r_j+1)}\\
&=\prod_{i}p_i^{\frac{r_i(r_i+1)}{2}\prod_{j\ne i}(r_j+1)}\\
&=\prod_{i}p_i^{\frac{r_i}{2}\prod_{j}(r_j+1)}
\end{aligned}$$
直接计算即可，注意要处理好有关 $\frac{1}{2}$ 的问题。

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
void read(ll &x) {
    char c = getchar();
    ll v = 0, f = 1;
    while (c < '0' || '9' < c) {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        v = (v << 1) + (v << 3) + (c ^ 48);
        c = getchar();
    }
    x = v * f;
}
const ll mod = 1e9 + 7, mxp = 2 * mod - 2;
ll qpow(ll x, ll y) {
    ll z = 1;
    while (y) {
        if (y & 1)
            z = z * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return z;
}
const ll M = 2e5 + 5;
ll m, p[M], r[M];
bool div2 = false;
ll exp = 1, ans = 1;
int main() {
    read(m);
    for (ll i = 1; i <= m; i++) {
        read(p[i]);
        r[p[i]]++;
    }
    sort(p + 1, p + m + 1);
    m = unique(p + 1, p + m + 1) - (p + 1);
    for (ll i = 1; i <= m; i++)
        exp = exp * (r[p[i]] + 1) % mxp;
    for (ll i = 1; i <= m; i++)
        ans = ans * qpow(p[i], exp * r[p[i]] / 2) % mod;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：EgLund (赞：0)

给一个 $\mathcal O(n \sqrt n \log n)$ 的做法。

首先式子很好推：对于每一个质因子，答案为这个质因子从 $0$ 到它的出现次数次方的和，乘以将这个质因数除干净之后的数的因数个数。

考虑求出对于每个质因数的答案。

首先第一项 $\prod \limits _{i=0} ^{\alpha _i} p^i$，其中 $\alpha _i$ 表示质因数 $p$ 的出现次数。

考虑合并指数，为 $\frac {\alpha _i (\alpha _i -1)}{2} \bmod 10^9 + 6$，可以 $O(1)$ 不除法的计算。

重点在第二项，算出除干净一个质因数之后的因数个数。

我们当然可以 $\mathcal O(n^2)$ 的暴力求解，但是会 T 掉。

我们要找到一个不是 $\mathcal O(n)$ 量级的，而且影响答案的数据。

考虑一个质因数的出现次数，发现这是 $\mathcal O(\sqrt n)$ 量级的。而且，答案本质上就是只和出现次数有关。

好了，我们对于每一个出现次数预处理，用 `u_map` 查询它的答案。

复杂度严格 $\mathcal (n \sqrt n \log n)$。$\log$ 来自快速幂。

---

## 作者：Yansuan_HCl (赞：0)

发个不用分类讨论的做法。~~抢了一个[次优解](https://www.luogu.com.cn/paste/ml9jdkn4)。~~

把每个因数写成 $\prod p_i^{e_i}$ 的形式。考虑每个 $p_i$ 对最终乘积的贡献。

首先，$p_i$ 的指数可以选择 $[0, e_i]$。其次，别的因数一共有 $\prod_{j\neq i}(e_j+1)$ 种选法。因此，$p_i$ 的贡献为：

$$\left( p_i^{e_i \times (e_i+1) / 2} \right)^{\prod_{j\neq i}(e_j+1)}$$

右上角的部分，可以前缀积处理，并利用扩展欧拉定理对 $P-1$ 取膜。

```cpp
const ll P = 1000000007;
ll qpow(ll x, ll t) { ll v = 1; while (t) { if (t & 1) (v *= x) %= P; (x *= x) %= P; t >>= 1; } return v; }

const int N = 200005;
int m, k;
map<int, int> mp;
ll p[N], e[N], sumE[N], pref[N], suf[N];

int main() {
    rd(m);
    U (i, 1, m) {
        int x; rd(x);
        ++mp[x];
    }
    for (auto &pr : mp)
        p[++k] = pr.first, e[k] = pr.second;
    
    ll ans = 1;
    pref[0] = suf[k + 1] = 1;
    U (i, 1, k)
        sumE[i] = qpow(p[i], e[i] * (e[i] + 1) / 2 % (P - 1));
    U (i, 1, k)
        pref[i] = (pref[i - 1] * (e[i] + 1)) % (P - 1);
    D (i, k, 1)
        suf[i] = (suf[i + 1] * (e[i] + 1)) % (P - 1);
    
    U (i, 1, k) 
        (ans *= qpow(sumE[i], pref[i - 1] * suf[i + 1] % (P - 1))) %= P;

    printf("%lld", ans);
}
```

---

