# Coprime Arrays

## 题目描述

#### 题意：

我们称一个大小为 $n$ 的数组 $a$ 互质，当且仅当 $gcd(a_1,a_2,\cdots,a_n)=1$，$gcd$ 是最大公约数的意思。

给定 $n,k$，对于每个 $i$ $(1\le i\le k)$，你都需要确定这样的数组的个数——长度为 $n$ 的互质数组 $a$ ，满足对每个 $j$ $(1\le j\le n)$，都有 $1\le a_j\le i$。

答案可能非常大，请对 $10^9+7$ 取模。

## 说明/提示

因为互质数组的数量比较多，我们只列出不互质的：

当 $i=1$ 时，唯一的数组就是互质的，$b_1=1$。

当 $i=2$ 时，数组 $[2,2,2]$ 不是互质的，$b_2=7$。

当 $i=3$ 时，数组 $[2,2,2],[3,3,3]$ 不是互质的，$b_3=25$。

当 $i=4$ 时，数组 $[2,2,2],[3,3,3],[2,2,4],[2,4,2],[2,4,4],[4,2,2],[4,2,4],[4,4,2],[4,4,4]$ 不是互质的，$b_4=55$。

Translated by 小粉兔

## 样例 #1

### 输入

```
3 4
```

### 输出

```
82
```

## 样例 #2

### 输入

```
2000000 8
```

### 输出

```
339310063
```

# 题解

## 作者：Elegia (赞：19)

答案输出中有异或，但是异或与数论和求和式结合是很难利用的，所以这道题可以判断，我们必须把每个 $b_i$ 都求出来。

非常套路，首先列出 $b_m$ 的原始式子

$ b_m = \sum_{a_1 = 1}^{m} \cdots \sum_{a_k = 1}^{m} \delta_1 \left( \gcd_{i = 1}^{k} a_i \right) $

套路地进行莫比乌斯变换：

$ b_m = \sum_{a_1 = 1}^{m} \cdots \sum_{a_k = 1}^{m} \sum_{d | \forall a_i} \mu(d) $

$ b_m = \sum_{d=1}^m\mu(d) \left\lfloor\frac{m}{d}\right\rfloor ^ k $

你可能认为这里要进行除法分块，但其实不是，因为这样复杂度就是 $ \sum_{d = 1}^{n} \sqrt d \log k = \mathcal O (n\sqrt n \log k) $ 了。

这样做就忽略的一个性质，那就是我们要对连续一段区间内的 $b_m$ 求值，之前的做法根本是独立的。

一个想法是因子 $d$ 会参与在 $m \ge d$ 的每一个 $b_m$ 中，但它的贡献是成段改变的，那是因为 $\mu(d)$ 取值不变，而 $\left\lfloor\frac{m}{d}\right\rfloor$ 的取整性质使 $m$ 每增加 $d$ 才会改变。

因此我们可以枚举 $d$ ，维护 $b_m$ 的差分数组 $\Delta b_m$ ，最后进行前缀和。

$d$ 在 $\Delta b_{xd} = \mu(d) \cdot (x^n - (x - 1)^n)$

把幂预处理，复杂度 $\Theta(n \log k)$ 。

每个 $d$ 影响了 $\frac n d$ 个差分位置，它们的总时间复杂度是 $\sum_{d = 1}^n \frac n d = \Theta(n \log n)$ 。

综上，我们以 $\Theta \left(n(\log n + \log k)\right)$ 时间复杂度解决的此题。

```cpp
#include <cstdio>

using namespace std;

typedef long long ll;

const int P = 1e9 + 7;

const int N = 2e6 + 10;

int n, k, pc;
int pw[N], mu[N], p[N], b[N * 2];
bool vis[N];

void sieve();
int pow(int x, int k);

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; ++i)
		pw[i] = pow(i, n);
	sieve();
	for (int x = 1; x <= k; ++x) {
		for (int i = 1; i * x <= k; ++i) {
			b[i * x] = (b[i * x] + (ll)pw[i] * (P + mu[x]) % P) % P;
			b[i * x] = (b[i * x] - (ll)pw[i - 1] * (P + mu[x] % P)) % P;
			if (b[i * x] < 0)
				b[i * x] += P;
		}
	}
	int ans = 0;
	for (int i = 1; i <= k; ++i) {
		b[i] = (b[i] + b[i - 1]) % P;
		ans = (ans + (b[i] ^ i) % P) % P;
	}
	printf("%d\n", ans);
	return 0;
}

void sieve() {
	mu[1] = 1;
	for (int x = 2; x <= k; ++x) {
		if (!vis[x]) {
			p[++pc] = x;
			mu[x] = -1;
		}
		for (int j = 1; x * p[j] <= k; ++j)
			if (x % p[j] == 0) {
				mu[x * p[j]] = 0;
				vis[x * p[j]] = true;
				break;
			} else {
				mu[x * p[j]] = -mu[x];
				vis[x * p[j]] = true;
			}
	}
}

int pow(int x, int k) {
	int ret = 1;
	while (k) {
		if (k & 1)
			ret = (ll)ret * x % P;
		x = (ll)x * x % P;
		k >>= 1;
	}
	return ret;
}
```

---

## 作者：lahlah (赞：6)


首先式子非常简单

按照套路推一推

要求的就是

对于每个$k$
$$\large f(k)=\sum\limits_{d=1}^{k}\mu(d)\lfloor\frac{k}{d}\rfloor^n$$
直接暴力对每个$k$整除分块时间复杂度是$k\sqrt{k}logn$显然不能过

注意到

$$\large \lfloor\frac{k}{d}\rfloor\ne \lfloor\frac{k-1}{d}\rfloor⇔d∣k$$
显然只会在$d$倍数那里改变

此时前者为后者$+1$

考虑对答案差分
$\large \Delta f=f(k)-f(k-1)=\sum\limits_{d=1}^{k}\mu(d)\lfloor\frac{k}{d}\rfloor^n-\sum\limits_{d=1}^{k-1}\mu(d)\lfloor\frac{k-1}{d}\rfloor^n$

$\large \Delta f=\sum\limits_{d=1}^{k}\mu(d)(\lfloor\frac{k}{d}\rfloor^n-\lfloor\frac{k-1}{d}\rfloor^n)$

考虑上面说的，$\lfloor\frac{k}{d}\rfloor^n-\lfloor\frac{k-1}{d}\rfloor^n$
不为$0$当且仅当$d|k$

所以

$\large \Delta f=\sum\limits_{d|k}^{k}\mu(d)(\lfloor\frac{k}{d}\rfloor^n-\lfloor\frac{k-1}{d}\rfloor^n)$

$g(x)=x^n$可以直接线性筛(也可以直接log算)

$\large \Delta f$就可以类似对于每个$d$把答案贡献到它的倍数那里

$ans$一路$+\Delta f$就行了

具体实现看代码吧

code:
```cpp
#include<bits/stdc++.h>
#define N 2000050
#define mod 1000000007
#define ll long long
using namespace std;
const int lim = N - 5;
ll qpow(ll x, ll y) {
	ll ret = 1;
	for(; y; y >>= 1, x = x * x % mod) if(y & 1) ret = ret * x % mod;
	return ret;
}
int vis[N], prime[N], mu[N], sz;
void init() {//线性筛 
	mu[1] = 1;
	for(int i = 2; i <= lim; i ++) {
		if(!vis[i]) {
			prime[++ sz] = i;
			mu[i] = - 1;
		}
		for(int j = 1; j <= sz && prime[j] * i < N; j ++) {
			vis[prime[j] * i] = 1;
			if(i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = - mu[i];
		}
	}
}
int n, m;
ll pw[N], D[N];
int main() {
	init();
	scanf("%d%d", &n, &m);	
	for(int i = 1; i <= m; i ++) pw[i] = qpow(i, n);//算 g(x) = x ^ n 
	for(int i = 1; i <= m; i ++)
		for(int j = i; j <= m; j += i) {
			D[j] = (D[j] + 1ll * mu[i] * (pw[j / i] - pw[j / i - 1]) + mod) % mod;// 对于每个d，直接贡献到倍数那里 
		}		 
	ll ans = 0, s = 0;
	for(int i = 1; i <= m; i ++) {
		s = (s + D[i]) % mod;//当前的答案 
		ans = (ans + (s ^ i)) % mod;//按照题目要求的异或 
	}
	printf("%lld", ans);
	return 0;
}

```

对于这种一个个算慢的可以直接先差分，看观察式子的变化
最重要是要记得：
$$\large \lfloor\frac{k}{d}\rfloor\ne \lfloor\frac{k-1}{d}\rfloor⇔d∣k$$


---

## 作者：Delov (赞：5)

一个不用 $\mu$ 的做法。  

对于一个上界 $k$ 的计算是比较显然的，暴力做就是是枚举 $\gcd$，设其为 $g$，对于所有 $\gcd$ 为 $g$ 的倍数的数列数量就是 $(\lfloor\frac{k}{g} \rfloor)^n$，然后枚举 $g$ 的倍数容斥算出恰好为 $g$ 的方案数，但实际并不用。

我们设在当前上界 $k$ 下，$\gcd$ 为 $i$ 的方案数为 $f[i]$，可以发现，$k$ 每增 $1$，只有 $i|k$ 的位置会发生变化，而且对于一个 $f[i]$ 来讲，它实际上就是在上界为 $\lfloor\frac{k}{i}\rfloor$ 下，$\gcd$ 为 $1$ 的数列的方案数。  

可以看出，我们把问题转化成了一个更小的问题，而这题我们需要把所有的 $k$ 都求一遍，所以更小的问题的答案我们已经求得了，于是直接预处理约数然后修正变化量即可。

## code

```cpp

#include <bits/stdc++.h>
typedef long long ll;typedef unsigned long long ull; typedef double db;typedef long double ldb;
#define fre(x) freopen(#x ".in","r",stdin),freopen(#x ".out","w",stdout)
#define Rep(i,a,b) for(int i=a;i<=b;++i) 
#define Dwn(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define mair make_pair
#define fir first
#define sec second
using namespace std;

const int maxn=2e6+10,Mod=1e9+7;

int pw(int x,int p){int res=1,base=x;while(p){if(p&1)res=1LL*res*base%Mod;base=1LL*base*base%Mod;p>>=1;}return res;}
int Inv(int x){return pw(x,Mod-2);}

int n,K;
int f[maxn],p[maxn],ans;
int res[maxn];
vector<int>vec[maxn];

void solve(){
	cin>>n>>K;
	Rep(i,1,K)res[i]=pw(i,n);
	Rep(i,2,K)for(int j=1;i*j<=K;++j)vec[i*j].push_back(i);
	int sum=0;
	Rep(i,2,K){
		for(auto it : vec[i])sum=(0LL+sum-res[(i-1)/it]+res[i/it]+Mod)%Mod;
		res[i]=(res[i]-sum+Mod)%Mod;
	}
	Rep(i,1,K)ans=(ans+(res[i]^i))%Mod;
	cout<<ans<<"\n";
}

int main (){ ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);return solve(),0; }

```

---

## 作者：Lucky_Xiang (赞：3)

# 题目

[CF915G](https://www.luogu.com.cn/problem/CF915G)

# 分析

由题意，得：

$$\begin{aligned}b_k&=\sum_{a_1=1}^k\sum_{a_2=1}^k\dots\sum_{a_n=1}^k[\gcd(a_1,a_2\dots,a_n)=1]\\&=\sum_{a_1=1}^k\sum_{a_2=1}^k\dots\sum_{a_n=1}^k\sum_{d\mid\gcd(a_1,a_2\dots,a_n)}\mu(d)\\&=\sum_{d=1}^k\mu(d)\bigg\lfloor {k\over d}\bigg\rfloor^n\end{aligned}$$

但是，这时候用数论分块显然是跑不过去的。考虑用差分优化算法。

## 差分

> 引理：
> 
> $\big\lfloor {k\over d}\big\rfloor\ne\big\lfloor {k-1\over d}\big\rfloor\Longleftrightarrow d\mid k$，此时 $\big\lfloor {k\over d}\big\rfloor=\big\lfloor {k-1\over d}\big\rfloor+1$。

可以发现 $b$ 的差分中会出现上述结构。

$$\begin{aligned}\Delta b_k&=b_k-b_{k-1}\\&=\sum_{d=1}^k\mu(d)\bigg\lfloor {k\over d}\bigg\rfloor^n-\sum_{d=1}^{k-1}\mu(d)\bigg\lfloor {k-1\over d}\bigg\rfloor^n\\&=\sum_{d=1}^k\Bigg(\mu(d)\bigg\lfloor {k\over d}\bigg\rfloor^n-\mu(d)\bigg\lfloor {k-1\over d}\bigg\rfloor^n\Bigg)\\&=\sum_{d=1}^k\mu(d)\Bigg(\bigg\lfloor {k\over d}\bigg\rfloor^n-\bigg\lfloor {k-1\over d}\bigg\rfloor^n\Bigg)\\&=\sum_{d\mid k}\mu(d)\Bigg(\bigg\lfloor {k\over d}\bigg\rfloor^n-\bigg(\bigg\lfloor {k\over d}\bigg\rfloor-1\bigg)^n\Bigg)\end{aligned}$$

这样，就可以用 $O(n\log n)$ 的时间复杂度把 $\Delta b$ 序列求出来，从而推出 $b$ 序列。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mn=2000010;
const int N=2000000;
const int mod=1000000007;
LL qmi(LL a,LL b)
{
    LL s=1;
    while(b)
    {
        if(b&1)s=s*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return s;
}
int n,k;
LL d[mn],h[mn],f[mn];
int mu[mn];
int p[mn],tot;
bool st[mn];
void init()
{
    mu[1]=1;
    for(int i=2;i<=N;i++)
    {
        if(!st[i])p[++tot]=i,mu[i]=-1;
        for(int j=1;i*p[j]<=N;j++)
        {
            st[i*p[j]]=1;
            if(i%p[j]==0)
            {
                mu[i*p[j]]=0;
                break;
            }
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=k;i++)
    {
        d[i]=qmi(i,n);
        h[i]=d[i]-d[i-1];
    }
}
LL res,sum;
int main()
{
    cin>>n>>k;
    init();
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=k/i;j++)
        {
            f[i*j]+=mu[j]*h[i];
            f[i*j]%=mod;
        }
    }
    for(int i=1;i<=k;i++)
    {
        sum+=f[i];
        sum=(sum%mod+mod)%mod;
        res+=(sum^i);
        res%=mod;
    }
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：Unordered_OIer (赞：2)

# Description

你需要对于所有的 $k' \in [1,k]$，求出有多少个序列 $a_1 \sim a_n$ 满足 $\gcd\limits_{i=1}^n a_i=1$ 且 $\forall\ i \in [1,n],a_i \in [1,k']$。记 $k'$ 对应的答案为 $r[k']$，请输出 $\sum\limits_{i=1}^kr[i] \oplus i$，其中 $\oplus$ 表示异或运算。

# Solution

不好的 $O(k \ln k+k \log n)$ 做法，慢的取模。

$k$ 定的时候是平凡的，我们算出 $c[i]$ 表示全部 $\gcd$ 起来 $\geq i$ 的方案数，然后 $i=k \rightarrow 1$，用 $c[i]$ 减去 $i$ 的倍数的 $c[]$ 进行一个容斥就能得到 $\gcd=i$ 的序列数量了。然后 $c[1]$ 就是答案。

```
ll solve(ll n,ll k){
  for(ll i=1;i<=k;i++)c[i]=pw(k/i,n);
  for(ll i=k;i>=1;--i)
    for(ll j=i+i;j<=k;j+=i)c[i]=((c[i]-c[j])%P+P)%P;
  return c[1];
}
```

然后如果做 $k$ 次就 $O(nk)$ 了，坏！

我们可以打印一下 $k'=1 \sim k$ 的 $c[]$ 值：

```
input : 5 15

k =  1:        1 
k =  2:       31        1 
k =  3:      241        1        1 
k =  4:      991       31        1        1 
k =  5:     3091       31        1        1        1 
k =  6:     7501      241       31        1        1        1 
k =  7:    16531      241       31        1        1        1        1 
k =  8:    31711      991       31       31        1        1        1        1 
k =  9:    57781      991      241       31        1        1        1        1        1 
k = 10:    96601     3091      241       31       31        1        1        1        1        1 
k = 11:   157651     3091      241       31       31        1        1        1        1        1        1 
k = 12:   240031     7501      991      241       31       31        1        1        1        1        1        1 
k = 13:   362491     7501      991      241       31       31        1        1        1        1        1        1        1 
k = 14:   519961    16531      991      241       31       31       31        1        1        1        1        1        1        1 
k = 15:   739201    16531     3091      241      241       31       31        1        1        1        1        1        1        1        1 
```

然后我们发现，对于相邻两行的 $i=2,...,k'$ 有一些位置的 $c[]$ 不会变。对于每一列来说，这个变化是很有规律的，第 $j$ 列的 $c[]$ 每 $j$ 行变一次。

我们以行的观点来看这个规律，就是当 $k' \leftarrow k'+1$ 时，所有 $d \mid k'+1$ 的 $c[d]$ 会变。这一点其实很好理解，因为这时候 $(\left\lfloor\dfrac{k'}{d}\right\rfloor)^n$ 变了。

而这些变化之后会是什么呢？我们发现这表里的数全是在第一列里有的答案。设第一列的值为 $ans[1] \sim ans[k]$ 实际上，我们 $k' \leftarrow k'+1$ 改变的 $c[d]$ 其实就是把它变成 $ans[\dfrac{k'}{d}]$，也很好理解，因为一开始的 $(\left\lfloor\dfrac{k'}{d}\right\rfloor)^n$ 中的 $\left\lfloor\dfrac{k'}{d}\right\rfloor$ 加了 $1$。

那么我们只需要更新这些 $d$ 位置上的 $c[d]$ 就行了。

这样做就是 $O(k \log n+k \ln k)$ 的，一开始要算一遍 $n$ 次幂。需要精细实现：

1. 把 $1 \sim k$ 的因数都预处理出来。
2. 因为取模很 **慢**，所以不必要取模的地方不要取模。
3. 能用 int 的地方就用 int，虽然我不知道全用 int 能不能过，反正我全 ll 会 T。

然后就 $3432ms$ 卡过去了。

---

## 作者：ZillionX (赞：2)

# Description

若 $\gcd(a_1,\cdots,a_n)=1$，则称数列 $a$ 是互质的。

给定 $n,k$，令 $f(j)$ 表示满足 $\forall i \in [1,n],1 \le a_i \le j$ 的互质数列的个数，试求出 $\sum\limits_{i=1}^k f(i) \oplus i$。答案对 $10^9+7$ 取模。

$n,k \le 2\times 10^6$，时限 3.5s。

# Solution

怎么全网的做法都是 $\mathcal O(n \log n)$ 的啊。这里提供一个 $\mathcal O(n \log \log n)$ 做法。目前在 CF 上是最优解 rk1。

考虑直接刻画出 $f(m)$ 的值，不难发现

$$\begin{aligned}f(m)&=\sum_{a_1 \le m, \cdots, a_n \le m} [\gcd(a_1,\cdots,a_n)=1]\\&= \sum_{d=1} ^m \mu(d) \left\lfloor\dfrac{m}{d}\right\rfloor^n\end{aligned}$$

套路地对其进行差分。众所周知，观察相邻被除数在差分时的表现，有

$$\left\lfloor\frac{n}{d}\right\rfloor \neq \left\lfloor\frac{n-1}{d}\right\rfloor \Longleftrightarrow d | n$$

且此时 $\left\lfloor\dfrac{n-1}{d}\right\rfloor = \left\lfloor\dfrac{n}{d}\right\rfloor-1$。

于是进一步有

$$\Delta f(m)=\sum_{d |m} \mu(d)S(\frac{m}{d})$$

其中 $S(x)=x^n-(x-1)^n$，使用线性筛预处理出 $id_k$ 函数后就可以快速求出。

可以发现 $\Delta f$ 是对 $\mu$ 和 $S$ 进行狄利克雷卷积得到的结果。

接下来，我们使用快速卷积性函数的套路，将积性函数 $\mu$ 分解为若干个只与质数 $p$ 有关的函数的卷积，再将这些函数分别卷到 $S$ 上去，就可以得到 $\mathcal O(\sum\limits_p\sum\limits_{k=1}^{p^k\le n} \dfrac{n}{p^k})=\mathcal O(n \log \log n)$ 的复杂度。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+5,mod=1e9+7;
int n,K,tot,p[N],mu[N],id[N],f[N],t[N];
bool vs[N];
int add(int x,int y) {
	return x+y<mod?x+y:x+y-mod;
}
int dec(int x,int y) {
	return add(x,mod-y);
}
int Qpow(int x,int y) {
	int Mul=1;
	while (y) {
		if (y&1) Mul=1ll*Mul*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return Mul;
}
void Init(int n) {
	id[1]=mu[1]=1;
	for (int i=2;i<=n;i++) {
		if (!vs[i]) {
			p[++tot]=i;
			mu[i]=-1;
			id[i]=Qpow(i,K);
		}
		for (int j=1;j<=tot && 1ll*i*p[j]<=n;j++) {
			vs[i*p[j]]=1;
			id[i*p[j]]=1ll*id[i]*id[p[j]]%mod;
			if (!(i%p[j])) {
				mu[i*p[j]]=0;
				break;
			}
			mu[i*p[j]]=-mu[i];
		}
	}
	for (int i=1;i<=n;i++) f[i]=dec(id[i],id[i-1]);
}
int main() {
	scanf("%d%d",&K,&n);
	Init(n);
	for (int i=1;i<=tot;i++) {
		for (int j=1;1ll*p[i]*j<=n;j++) t[j]=f[j];
		for (long long j=p[i];j<=n;j*=p[i])
			for (int k=1;1ll*j*k<=n;k++) {
				if (mu[j]==1) f[j*k]=add(f[j*k],t[k]);
				else if (mu[j]==-1) f[j*k]=dec(f[j*k],t[k]); 
			}
	}
	int s=0,Ans=0;
	for (int i=1;i<=n;i++) {
		s=add(s,f[i]);
		Ans=add(Ans,s^i);
	}
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：User_Unauthorized (赞：1)

## 题意

给定 $n, k$，对于所有的 $m \in \left[1, k\right]$，求长度为 $n$，值域为 $\left[1,m \right]$ 且最大公约数为 $1$ 的序列种数，对 $10^9 + 7$ 取模。

（$1 \le n,k \le 2 \times 10^6$）。

## 题解

**[cnblogs](https://www.cnblogs.com/User-Unauthorized/p/solution-CF915G.html)**

设 $f(d, m)$ 表示长度为 $n$，值域为 $\left[1,m \right]$ 且最大公约数为 $1$ 的序列种数，$g(d, m)$ 表示长度为 $n$，值域为 $\left[1,m \right]$ 且序列元素均为 $d$ 的倍数即最大公约数为 $d$ 的倍数的序列种数，那么有

$$\begin{aligned}
g(d, m) &= \sum\limits_{d \mid h} f(h, m) \\
f(d, m) &= \sum\limits_{d \mid h} \mu\left(\dfrac{h}{d}\right) g(h, m)
\end{aligned}$$

考虑计算 $g(d, m)$，发现

$$g(d, m) = \left\lfloor\dfrac{m}{d}\right\rfloor^n$$

综上，可得

$$f(1, m) = \sum\limits_{i = 1}^{m} \mu\left(i\right)\left\lfloor\dfrac{m}{i}\right\rfloor^n$$

现在我们得到了答案的计算式，但是若对于每个 $m$ 应用整除分块计算，复杂度为 $\mathcal{O}(k \sqrt{k} \log n)$，若使用线性筛预处理出幂函数，那么复杂度为 $\mathcal{O}(k \sqrt{k})$，均无法通过本题。

故考虑在 $f(1, m - 1)$ 的基础上计算 $f(1, m)$，考虑 $f(1, m)$ 较 $f(1, m - 1)$ 的差值均为 $\left\lfloor\dfrac{m}{i}\right\rfloor$ 的改变引起的，而对于每个 $i$，只有 $m$ 增大为 $i$ 的倍数时该值才会改变，故答案共会改变 $\mathcal{O}(k \ln k)$ 次。形式化的，有

$$\begin{aligned}
f(1, m)
&= f(1, m - 1) + \left(f(1, m) - f(1, m - 1)\right) \\

&= f(1, m - 1) + \left(\sum\limits_{i = 1}^{m} \mu\left(i\right)\left\lfloor\dfrac{m}{i}\right\rfloor^n - \sum\limits_{i = 1}^{m - 1} \mu\left(i\right)\left\lfloor\dfrac{m - 1}{i}\right\rfloor^n\right) \\

&= f(1, m - 1) + \sum\limits_{i = 1}^{m}\mu\left(i\right)\times\left(\left\lfloor\dfrac{m}{i}\right\rfloor^n - \left(\left\lfloor\dfrac{m}{i}\right\rfloor - 1\right)^n\right)
\end{aligned}$$

而 $\left\lfloor\dfrac{m}{i}\right\rfloor^n - \left(\left\lfloor\dfrac{m}{i}\right\rfloor - 1\right)^n$ 的取值只有 $i \mid m$ 时才不为 $0$，故上式后半部分在 $m$ 取遍 $\left[1, k\right]$ 时产生贡献的次数共为 $\mathcal{O}(k \ln k)$ 次。

对于每个数，预处理其因子，在 $m$ 增长后，对于当前 $m$ 的所有因子 $i$，$\left\lfloor\dfrac{m}{i}\right\rfloor$ 的值均会增长 $1$，将答案累加 $\mu\left(i\right)\times\left(\left\lfloor\dfrac{m}{i}\right\rfloor^n - \left(\left\lfloor\dfrac{m}{i}\right\rfloor - 1\right)^n\right)$ 即可。

使用线性筛预处理出幂函数，在 $n,k$ 同阶的情况下，总复杂度为 $\mathcal{O}(n \log n)$，可以通过本题。

但是让我们再次审视差分函数 $S(n)$，可以列出其表达式

$$S(n) = \sum\limits_{d \mid n} \mu\left(d\right) S\left(\dfrac{n}{d}\right)$$

可以若没有 $\mu$ 函数的干扰，函数 $S$ 可以通过 $\tt{Dirichlet}$ 前缀和以 $\mathcal{O}(n \log\log n)$ 的复杂度筛出，所以我们考虑 $\mu$ 函数对普通 $\tt{Dirichlet}$ 前缀和的影响。

考虑完全平方数的 $\mu$ 值为 $0$ 这一性质，可以发现对于每个质因子 $p$，其最多贡献一次，不同于普通 $\tt{Dirichlet}$ 前缀和的贡献无数次。故可以类比完全背包和 $01$ 背包的区别，将普通 $\tt{Dirichlet}$ 前缀和的第二个循环语句改为从大到小遍历，这样就可以保证每个质因子最多贡献一次。

普通 $\tt{Dirichlet}$ 前缀和：

```cpp
for (auto const &iter: P)
    for (valueType i = 1; i <= K / iter; ++i)
        Dec(F[i * iter], F[i]);
```

本次魔改 $\tt{Dirichlet}$ 前缀和：

```cpp
for (auto const &iter: P)
    for (valueType i = K / iter; i >= 1; --i)
        Dec(F[i * iter], F[i]);
```

其中 $P$ 为质数集。

这样处理的话复杂度为 $\mathcal{O}(n \log \log n)$，目前 $\tt{Codeforces}$ 最优解。

![](https://cdn.luogu.com.cn/upload/image_hosting/cj5k7xx5.png)

## Code

$\mathcal{O}(n \log n)$

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;

constexpr valueType MOD = 1e9 + 7;

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

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType N, M;
    container prime;
    bitset isPrime;
    container Mobius, Power;
    ValueMatrix Factor;

public:
    LineSieve(valueType n, valueType m) : N(n), M(m), prime(), isPrime(n + 1, true), Mobius(n + 1, 1), Factor(n + 1), Power(n + 1) {
        Mobius[1] = 1;
        Power[0] = 0;
        Power[1] = 1;

        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                prime.push_back(i);

                Mobius[i] = -1;

                Power[i] = ::pow(i, M);
            }

            for (auto const &iter: prime) {
                valueType const t = i * iter;

                if (t > N)
                    break;

                isPrime[t] = false;

                Power[t] = mul(Power[i], Power[iter]);

                if (i % iter == 0) {
                    Mobius[t] = 0;

                    break;
                } else {
                    Mobius[t] = -Mobius[i];
                }
            }

            if (Mobius[i] < 0)
                Mobius[i] += MOD;
        }

        for (valueType i = 1; i <= N; ++i)
            for (valueType j = i; j <= N; j += i)
                Factor[j].push_back(i);
    }

    valueType operator()(valueType n) const {
        return Mobius[n];
    }

    valueType pow(valueType n) const {
        return Power[n];
    }

    const ValueVector &fact(valueType n) const {
        return Factor[n];
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    LineSieve const sieve(K, N);

    ValueVector ans(K + 1, 0);

    for (valueType i = 1; i <= K; ++i) {
        ans[i] = ans[i - 1];

        for (auto const &iter: sieve.fact(i))
            Inc(ans[i], mul(sieve(iter), sub(sieve.pow(i / iter), sieve.pow(i / iter - 1))));
    }

    valueType result = 0;

    for (valueType i = 1; i <= K; ++i)
        Inc(result, ans[i] ^ i);

    std::cout << result << std::endl;
}
```

---

$\mathcal{O}(n \log \log n)$

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<bool> bitset;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
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

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType N, M;
    container prime;
    bitset isPrime;
    container Power;

public:
    LineSieve(valueType n, valueType m) : N(n), M(m), prime(), isPrime(n + 1, true), Power(n + 1) {
        prime.reserve(n / 10);
        Power[0] = 0;
        Power[1] = 1;

        for (valueType i = 2; i <= N; ++i) {
            if (isPrime[i]) {
                prime.push_back(i);

                Power[i] = ::pow(i, M);
            }

            for (auto const &iter: prime) {
                valueType const t = i * iter;

                if (t > N)
                    break;

                isPrime[t] = false;

                Power[t] = mul(Power[i], Power[iter]);

                if (i % iter == 0)
                    break;
            }
        }
    }

    valueType pow(valueType n) const {
        return Power[n];
    }

    const container &Prime() const {
        return prime;
    }
};

int main() {
    valueType N, K;

    std::cin >> N >> K;

    LineSieve const sieve(K, N);

    ValueVector const &P = sieve.Prime();

    ValueVector F(K + 1, 0);

    for (valueType i = 1; i <= K; ++i)
        F[i] = sub(sieve.pow(i), sieve.pow(i - 1));

    for (auto const &iter: P)
        for (valueType i = K / iter; i >= 1; --i)
            Dec(F[i * iter], F[i]);

    for (valueType i = 1; i <= K; ++i)
        Inc(F[i], F[i - 1]);

    valueType result = 0;

    for (valueType i = 1; i <= K; ++i)
        Inc(result, F[i] ^ i);

    std::cout << result << std::endl;
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

> 我们称一个大小为 $n$ 的数组 $a$ 互质，当且仅当 $\gcd(a_1,a_2,\cdots,a_n)=1$。
>
> 给定 $n,k$，对于每个 $i$ $(1\le i\le k)$，你都需要确定这样的数组的个数——长度为 $n$ 的互质数组 $a$ ，满足对每个 $j$ $(1\le j\le n)$，都有 $1\le a_j\le i$。

# 分析

我们设 $f(x)$ 为 $x$ 所对应的互质数组的个数。

按照题意，可以列出这样一个式子：

$$
f(x)=\sum^x_{a_1=1}\sum^x_{a_2=1}\cdots\sum^x_{a_n=1}\left[\gcd^n_{i=1}a_i=1\right]
$$

简单推一下式子：

$$
\begin{aligned}
f(x)&=\sum^x_{a_1=1}\sum^x_{a_2=1}\cdots\sum^x_{a_n=1}\left[\gcd^n_{i=1}a_i=1\right]\\
&=\sum^x_{a_1=1}\sum^x_{a_2=1}\cdots\sum^x_{a_n=1}\varepsilon\left(\gcd^n_{i=1}a_i\right)\\
\end{aligned}
$$

因为 $\mu*\mathbf{1}=\varepsilon$，即 $\varepsilon(x)=\sum_{d|x}\mu(d)$ 所以有：

$$
\begin{aligned}
f(x)&=\sum^x_{a_1=1}\sum^x_{a_2=1}\cdots\sum^x_{a_n=1}\sum_{d|\gcd^n_{i=1}a_i}\mu(d)\\
&=\sum^x_{a_1=1}\sum^x_{a_2=1}\cdots\sum^x_{a_n=1}\sum_{d|a_1,\cdots,d|a_n}\mu(d)\\
\end{aligned}
$$

变换求值顺序，枚举 $d$：

$$
\begin{aligned}
f(x)&=\sum^x_{d=1}\mu(d)\sum^{\lfloor\frac{x}{d}\rfloor}_{a_1=1}\sum^{\lfloor\frac{x}{d}\rfloor}_{a_2=1}\cdots\sum^{\lfloor\frac{x}{d}\rfloor}_{a_n=1}1\\
&=\sum^x_{d=1}\mu(d)\left\lfloor\frac{x}{d}\right\rfloor^n
\end{aligned}
$$

于是我们得到了一个 $O(k\sqrt{k}+k\log n)$ 的做法。

在 $n,k\leq2\times10^6$ 的规模下，无法通过本题。

---

有个显然的引理：

$$
d|x \Leftrightarrow \left\lfloor\frac{x}{d}\right\rfloor = \left\lfloor\frac{x-1}{d}\right\rfloor+1
$$

据此考虑差分：

$$
\begin{aligned}
\Delta f(x)&=f(x)-f(x-1)\\
&=\sum^x_{d=1}\mu(d)\left\lfloor\frac{x}{d}\right\rfloor^n-\sum^{x-1}_{d=1}\mu(d)\left\lfloor\frac{x-1}{d}\right\rfloor^n\\
&=\sum^x_{d=1}\mu(d)\left(\left\lfloor\frac{x}{d}\right\rfloor^n-\left\lfloor\frac{x-1}{d}\right\rfloor^n\right)\\
\end{aligned}
$$

根据上述引理，当且仅当 $d|x$ 时 $\left(\left\lfloor\frac{x}{d}\right\rfloor^n-\left\lfloor\frac{x-1}{d}\right\rfloor^n\right) \neq 0$，所以上式可以如下改写：

$$
\begin{aligned}
\Delta f(x)&=\sum_{d|x}\mu(d)\left(\left\lfloor\frac{x}{d}\right\rfloor^n-\left\lfloor\frac{x-1}{d}\right\rfloor^n\right)\\
\end{aligned}
$$

所以，我们可以枚举 $d$，然后将所有满足 $d|x$ 的 $\Delta f(x)$ 加上 $\mu(d)\left(\left\lfloor\frac{x}{d}\right\rfloor^n-\left\lfloor\frac{x-1}{d}\right\rfloor^n\right)$。

通过前缀和统计答案。

时间复杂度 $O(k\log n+k \log k)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 2000006
#define mod 1000000007

int mu[maxn];
bool vis[maxn];
vector<int> pri;
void init()
{
    mu[1]=1;
    for(int i=2;i<maxn;i++)
    {
        if(!vis[i]) mu[i]=-1, vis[i]=1, pri.emplace_back(i);
        for(auto p:pri)
        {
            if(p*i>=maxn) break;
            vis[p*i]=1;
            if(i%p==0) break;
            mu[i*p]=-mu[i];
        }
    }
}

int ksm(int64_t x, int l)
{
    int64_t ret=1;
    for(;l;l>>=1, x=x*x%mod)
        if(l&1) ret=ret*x%mod;
    return ret;
}

int lev[maxn], det[maxn];

int main()
{
    int n, k;
    cin>>n>>k;
    init();
    for(int i=1;i<=k;i++) 
        lev[i]=ksm(i, n);
    for(int d=1;d<=k;d++)
        for(int j=1;d*j<=k;j++)
            det[d*j]=((det[d*j]+mu[d]*(mod+(lev[j]-lev[j-1])%mod)%mod)%mod+mod)%mod;
    int ans=0, otp=0;
    for(int i=1;i<=k;i++) 
        otp=(otp+(i^(ans=(ans+det[i])%mod)))%mod;
    cout<<otp%mod;
}
```

---

## 作者：Luzhuoyuan (赞：0)

Links: [[Codeforces]](http://codeforces.com/problemset/problem/915/G) [[Luogu]](https://www.luogu.com.cn/problem/CF915G)

提供一种复杂度略劣但比较好懂的做法。

upd：修正了一些表达不明确的内容。

### 题意

给定正整数 $n,k$，对于 $1\le i\le k$ 的每个 $i$，计算满足下面条件的长为 $n$ 的序列 $a$ 个数：

- $\forall j\in [1,n],1\le a_j\le i$；
- $\gcd(a_1,a_2,\dots,a_n)=1$。

设 $i$ 的答案为 $b_i$，输出 $\displaystyle(\sum_{i=1}^k(i\oplus (b_i\bmod M)))\bmod M$ 的值，$M=10^9+7$。

- $1\le n,k\le 2\cdot 10^6$。

### 思路

首先，很容易想到计算答案的差分数组，然后统计时前缀和一下就行了。于是问题转化为：枚举 $i$，计算有多少长为 $n$ 的数列 $a$ 满足：

- $\max\{a_j\}=i$；
- $\gcd(a_1,a_2,\dots,a_n)=1$。

这个东西怎么计算呢？考虑一种比较暴力的做法。由于 $i$ 一定在序列 $a$ 中出现了，所以最终的 $\gcd$ 必然是 $i$ 的因数。所以我们对于 $i$，把 $i$ 的质因子处理出来，那么显然质因子个数不超过 $7$ 个，可以考虑状压。

设 $f_S$ 表示 $\gcd(a_1,a_2,\dots,a_n)$ 等于在集合 $S$ 中出现的质数的积（设为 $t$）的序列 $a$ 的数量，我们可以先令 $f_S$ 表示 $\gcd$ 为 $t$ 的倍数的数量，这很容易计算：$f_S=(\dfrac i t)^n-(\dfrac i t-1)^n$（即：$a_j$ 均为 $t$ 倍数的 $a$ 的种数 减去 满足前面条件但是不存在 $a_j=i$ 的种数）。之后，我们倒序枚举每个 $t$ 并枚举其因数（即枚举 $S$ 的子集），将它们的 $f$ 值减去 $f_S$，最后得到的 $f_0(t=1)$ 即为这次的答案，统计前缀和加入答案即可。

接下来是不严谨的复杂度证明（设 $n,k$ 同阶）。由于 $1\sim k$ 的 $i$ 拥有的质因子个数和为 $O(n\log\log n)$，中间状压的单次复杂度为 $O(3^{\omega(i)})$，那么总和估计也在 $O(n\log n)$ 的级别，带一点常数，状压以外的步骤的复杂度为 $O(n\log n)$。经测试，$\displaystyle\sum_{i=1}^{2\times 10^6}3^{\omega(i)}\approx 9.1\times 10^7$，时限有 $3.5\text s$，可以接受。（C++ 20 下最大用时 $921\text{ms}$，跑得不慢。）

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5,mod=1e9+7;
int n,k,p[N],pn,la[N],mi[N],ans,s,b[N],m,f[130];
inline int ksm(int x,int y){int z=1;while(y){if(y&1)z=z*x%mod;x=x*x%mod,y>>=1;}return z;}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=2;i<=k;i++){
		if(!la[i])p[++pn]=la[i]=i;
		for(int j=1;j<=pn&&p[j]*i<=k;j++){la[i*p[j]]=p[j];if(i%p[j]==0)break;}
	}
	for(int i=1;i<=k;i++)mi[i]=ksm(i,n);
	for(int x=1;x<=k;x++){
		int t=x;m=0;
		while(t>1){if(!m||la[t]!=b[m])b[++m]=la[t];t/=la[t];}
		for(int i=0;i<(1<<m);i++){t=x;for(int j=1;j<=m;j++)if(i>>(j-1)&1)t/=b[j];f[i]=(mi[t]-mi[t-1]+mod)%mod;}
		for(int i=(1<<m)-1;i;i--)for(int j=i;j;j=(j-1)&i)(f[(j-1)&i]+=mod-f[i])%=mod;
		ans=(ans+(x^(s=(s+f[0])%mod)))%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

（逃

---

## 作者：daniEl_lElE (赞：0)

异或没有什么性质，于是得求出每一个的答案。

考虑求出一个的答案，这是一个经典题，显然可以求出 Dirichlet 前缀和，将每一项变为原来的 $n$ 次方，然后差分回去。

注意到我们只需要求出 $1$ 位置的答案，于是可以不用差分，将每一项乘上 $\mu(i)$ 相加即可。

维护每个时刻的 Dirichlet 前缀和，加入一个 $i$ 相当于在 $j\mid i$ 的所有 $j$ 位置加一，于是这个位置的 $n$ 次方会改变，只需要暴力改即可。

复杂度调和级数 $O(k\ln k\log n)$，对 $n$ 次幂进行预处理可以做到 $O(k\ln k)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
vector<signed> vc[2000005];
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int prm[2000005],mu[2000005],num,prep[2000005];
bool isp[2000005];
signed main(){
	for(int i=2;i<=2000000;i++) isp[i]=1;
	mu[1]=1;
	for(int i=2;i<=2000000;i++){
		if(isp[i]) prm[++num]=i,mu[i]=-1;
		for(int j=1;j<=num&&prm[j]*i<=2000000;j++){
			isp[i*prm[j]]=0;
			if(i%prm[j]==0){
				mu[i*prm[j]]=0;
				break;
			}
			mu[i*prm[j]]=mu[i]*-1;
		}
	}
	memset(prm,0,sizeof(prm));
    int n,k,ans=0,ret=0; cin>>n>>k;
    for(int i=1;i<=k;i++) prep[i]=qp(i,n);
    for(int i=20;i<=k;i++) for(int j=i;j<=k;j+=i) vc[j].push_back(i);
    for(int i=1;i<=k;i++){
    	for(auto v:vc[i]){
    		(ans+=mod-mu[v]*prep[prm[v]]%mod)%=mod;
    		prm[v]++;
    		(ans+=mod+mu[v]*prep[prm[v]]%mod)%=mod;
		}
		for(int v=1;v<=19;v++){
		    if(i%v==0){
		        (ans+=mod-mu[v]*prep[prm[v]]%mod)%=mod;
    	    	prm[v]++;
    	    	(ans+=mod+mu[v]*prep[prm[v]]%mod)%=mod;
		    }
		}
//		cout<<ans<<" ";
		(ret+=(ans^i))%=mod;
	}
	cout<<ret;
	return 0;
}

```

---

## 作者：向日葵小班 (赞：0)

对于（正整数）序列 $a_{1\sim m}$，若 $\gcd(a_1,a_2,......,a_m)=1$，则称这个序
列是好的。

分别对于 $k\in [1,L]$，求值域为 $1\sim k$ 的好序列个数。

$m,L\le2\times10^6 $，不必考虑输出耗时。


------------

对于单个确定的 $k$，记 $F(d)$ 为 $\gcd$ 为 $d$ 的倍数的序列数目，限制显然等价
于每个元素都是 $d$ 的倍数，方案数为 ${\left\lfloor k\div d\right\rfloor}^m$。

记 $Ans[k]$ 为对于 $k$ 的答案，根据倍数差分可得

$Ans[k]=\sum\limits_{d=1}^k\mu(d)\left\lfloor k\div d\right\rfloor^m$

（使用反演动机会稍稍绕一点）

若对每个 $k$ 分别使用整除分块，复杂度为 $O(n\sqrt n)$，无法通过。

对答案数组 $Ans$ 进行差分，有

$Ans[k]-Ans[k-1]=\sum\limits_{d=1}^k\mu(d)\left\lfloor k\div d\right\rfloor^n-\sum\limits_{d=1}^{k-1}\mu(d)\left\lfloor (k-1)\div d\right\rfloor^n$

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$=\sum\limits_{d=1}^k\mu(d)(\left\lfloor k\div d\right\rfloor^n-\left\lfloor (k-1)\div d\right\rfloor^n)$

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$=\sum\limits_{d|k}\mu(d)(\left\lfloor k\div d\right\rfloor^n-((k\div d)-1)^n)$

线筛 $id_k$ 之后，记 $h(n)=n^k-(n-1)^k$，则 $\vartriangle Ans=h*\mu$（其中 $\vartriangle Ans(n)=Ans(n)-Ans(n-1)$）。

复杂度 $O(n\log n)$（甚至可做到 $O(n\log\log n)$）






---

## 作者：_Fontainebleau_ (赞：0)

### 题意

- 称一个长度为 $n$ 的数列 $a$ 是互质的，当且仅当 $\gcd\left(a_1,\ldots,a_n\right)=1$。
- 给定 $n,k$，对于每一个 $j\in[1,k]$，满足 $\forall i\in[1,n],1\le a_i\le j$ 的互质数列的个数 $b_j$。对 $10^9+7$ 取模。最后输出 $\displaystyle \sum_{i=1}^k{b_i\oplus{i}}$，再对 $10^9+7$ 取模。
- $1\le{n,k}\le2\times10^6$。


### 做法

####  update 2022.7.20

推式子部分有错，感谢 [Alex10086](https://www.luogu.com.cn/user/110484) 指正。


------------


如果您做过 [AT5310](www.luogu.com.cn/problem/AT5310) 的话，应该很快就可以得到以下结果：

$\begin{aligned}b_m&=\sum_{a_1=1}^m\sum_{a_2=1}^m\cdots\sum_{a_n=1}^m[\gcd(a_1,a_2,\ldots,a_n)=1]\\&=\sum_{a_1=1}^m\sum_{a_2=1}^m\cdots\sum_{a_n=1}^m\sum_{d\mid{\gcd(a_1,a_2,\ldots,a_n)}}\mu(d)\\&=\sum_{d=1}^{m}\mu(d)\sum_{a_1=1}^{\left\lfloor\frac{m}d\right\rfloor}\sum_{a_2=1}^{\left\lfloor\frac{m}d\right\rfloor}\cdots\sum_{a_n=1}^{\left\lfloor\frac{m}d\right\rfloor}1\\&=\sum_{d=1}^m\mu(d)\left\lfloor\frac{m}d\right\rfloor^n \end{aligned}$

如果你在这里整除分块的话，会 $\color{darkblue}\text{TLE}$。这样相当于每个查询之间都是独立的，显然我们没有用到我们求的是连续的 $b_i$ 这一条件。

怎么去做呢？观察上式中的 $d$。

虽然不能直接整除分块，但是利用整除分块的核心思想， **$\left\lfloor{\dfrac{m}d}\right\rfloor$ 是一段一段在变的**，所以我们有一个想法就是用一个差分数组 $\Delta{b_m}$ 去做差分。

对于每一个因子 $d$，它只会 $m\ge{d}$ 的 $b_m$ 产生影响，而且当且仅当 $d\mid{m}$ 时，即 $m=xd$ 时，$d$ 对 $b_m$ 的贡献才会比 $b_{m-1}$ 多 $\mu(d)\left({x^n}-{(x-1)}^n\right)$，否则不变。所以每一个 $d$ 会影响 $\dfrac{n}d$ 个位置，我们枚举所有的 $d$，就可以了。最终时间复杂度是 $O(n\log{n})$。

### 代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n,k,cnt,prime[1000006];
int p[2000006],mu[2000006],d[2000006];
bitset<2000006>used;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline void sieve(int n)
{
	mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!used[i])	prime[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=n&&1ll*i*prime[j]<=n;j++)
		{
			used[i*prime[j]]=1;
			if(i%prime[j])	mu[i*prime[j]]=-mu[i];
			else	break;
		}
	}
} 
inline int f(int x,int y)
{
	int res=1,p=x;
	while(y)
	{
		if(y&1)	res=1ll*res*p%mod;
		p=1ll*p*p%mod;y>>=1;
	}
	return res;
}
int main()
{
	n=read(),k=read();sieve(k);
	for(int i=1;i<=k;i++)	p[i]=f(i,n);
	for(int i=1;i<=k;i++)
		for(int j=i;j<=k;j+=i)
			d[j]=(d[j]+1ll*mu[i]*(p[j/i]-p[j/i-1])%mod+mod)%mod;
	int ans=0,num=0;
	for(int i=1;i<=k;i++)	num=(num+d[i])%mod,ans=(ans+(num^i))%mod;
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Yuno (赞：0)

(下文中 $m$ 代表原题面中的 $k$ )

考虑像样例解释那样，求出不互质数组的数量。

根据题意，每一个不互质数组必然有大于 $1$ 的公因子，所以可以考虑枚举质因子计算贡献。

假设当前枚举到了 $k$ 这个公因子，且当前数组里的数最大为 $i$，

那么数组里可选的数就是 $k,2k,...,dk(dk\leq m)$，容易发现 $d=\lfloor\frac {i}{k}\rfloor$

那么对答案的贡献即为 $d^n$

但是要注意去重，比如公因子为 $6$ 的时候，他已经被 $2$ 和 $3$ 算过了，要减去。

再比如 $8$，他已经被 $2$ 算过了，所以不用计算。

容易发现每个公因子的系数就是它的莫比乌斯函数值。

于是可以列出式子$b_i=i^n-\sum\limits_{k=1}^{i}\mu_k\lfloor\frac {i}{k}\rfloor^n$

这玩意显然不能直接算，考虑计算每个 $k$ 对每个 $i$ 的贡献

对于每个 $k$，枚举它的每个 $d$，代表当前可以选 $k,2k,...,dk$ 这些数

这样计算出的贡献，仅仅会被计算在 $[dk,dk+k-1]$ 这个区间

因此可以使用差分 $O(1)$ 修改

预处理幂次后，复杂度是一个调和级数，为 $O(k\ln k)$

Code:
```cpp
#include <bits/stdc++.h>

inline int read( ) {
	int x = 0;
	char c = getchar( );
	while ( !isdigit( c ) ) c = getchar( );
	while ( isdigit( c ) ) x = ( x << 3 ) + ( x << 1 ) + ( c ^ 48 ), c = getchar( );
	return x;
}
const int N = 5e6 + 7, mo = 1e9 + 7;
int n, m, b[ N ], notprime[ N ], prime[ N ], cnt, miu[ N ], cf[ N ];
void mobius( ) {
	for ( int i = 2; i <= 2000000; ++ i ) {
		if ( !notprime[ i ] ) miu[ i ] = 1, prime[ ++ cnt ] = i;
		for ( int j = 1; j <= cnt && i * prime[ j ] <= 2000000; ++ j ) {
			notprime[ i * prime[ j ] ] = -1;
			if ( i % prime[ j ] == 0 ) {
				miu[ i * prime[ j ] ] = 0;
				break;
			} else
			miu[ i * prime[ j ] ] = -miu[ i ];
		}
	}
}
inline int qp( int b, int p ) {
	int ret = 1;
	while ( p ) {
		if ( p & 1 ) ret = 1ll * ret * b % mo;
		b = 1ll * b * b % mo;
		p >>= 1;
	}
	return ret;
}
inline int reduce( int x ) { return x >= mo ? x - mo : x; }
int main( ) {
	mobius( );
	n = read( ), m = read( );
	for ( int k = 2; k <= m; ++ k ) {
		if ( miu[ k ] == 0 ) continue;
		for ( int i = k; i <= m; i += k ) {
			int val = reduce( miu[ k ] * qp( i / k, n ) + mo );
			cf[ i ] = reduce( cf[ i ] + val );
			cf[ k + i ] = reduce( cf[ k + i ] - val + mo );
		}
	}
	for ( int i = 1; i <= m; ++ i ) cf[ i ] = reduce( cf[ i - 1 ] + cf[ i ] );
	b[ 1 ] = 1;
	int ans = 0;
	for ( int i = 2; i <= m; ++ i ) {
		b[ i ] = cf[ i ];
		ans = reduce( ans + ( b[ i ] ^ i ) );
	}
	printf( "%d\n", ans );
	return 0;
}
```


---

