# Cowslip Collections

## 题目描述

In an attempt to make peace with the Mischievious Mess Makers, Bessie and Farmer John are planning to plant some flower gardens to complement the lush, grassy fields of Bovinia. As any good horticulturist knows, each garden they plant must have the exact same arrangement of flowers. Initially, Farmer John has $ n $ different species of flowers he can plant, with $ a_{i} $ flowers of the $ i $ -th species.

On each of the next $ q $ days, Farmer John will receive a batch of flowers of a new species. On day $ j $ , he will receive $ c_{j} $ flowers of the same species, but of a different species from those Farmer John already has.

Farmer John, knowing the right balance between extravagance and minimalism, wants exactly $ k $ species of flowers to be used. Furthermore, to reduce waste, each flower of the $ k $ species Farmer John chooses must be planted in some garden. And each of the gardens must be identical; that is to say that each of the $ k $ chosen species should have an equal number of flowers in each garden. As Farmer John is a proponent of national equality, he would like to create the greatest number of gardens possible.

After receiving flowers on each of these $ q $ days, Farmer John would like to know the sum, over all possible choices of $ k $ species, of the maximum number of gardens he could create. Since this could be a large number, you should output your result modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample case, after the first day Farmer John has $ (4,6,9,8) $ of each type of flower, and $ k=3 $ .

Choosing $ (4,6,8) $ lets him make $ 2 $ gardens, each with $ (2,3,4) $ of each flower, respectively. Choosing $ (4,6,9) $ , $ (4,9,8) $ and $ (6,9,8) $ each only let him make one garden, since there is no number of gardens that each species can be evenly split into. So the sum over all choices of $ k=3 $ flowers is $ 2+1+1+1=5 $ .

After the second day, Farmer John has $ (4,6,9,8,6) $ of each flower. The sum over all choices is $ 1+2+2+1+1+2+2+3+1+1=16 $ .

In the second sample case, $ k=1 $ . With $ x $ flowers Farmer John can make $ x $ gardens. So the answers to the queries are $ 6+5+4+3+2=20 $ and $ 6+5+4+3+2+1=21 $ .

## 样例 #1

### 输入

```
3 3 2
4
6
9
8
6
```

### 输出

```
5
16
```

## 样例 #2

### 输入

```
4 1 2
6
5
4
3
2
1
```

### 输出

```
20
21
```

# 题解

## 作者：Marser (赞：7)

### 题意
给定一个长度为 $n$ 的数列 $\{a_i\}$ 和一个整数 $k$，给出 $q$ 个询问，每次向 $\{a_i\}$ 加入一个新数 $x$，并询问加入这个数之后，数列中所有大小为 $k$ 的子集的 $\gcd$ 之和。每次操作有后效性，会保留加入的数。  
$1\le n,k,q \le 10^5$，$1 \le a_i,x \le 10^6$。
### 题解
定义 $m$ 为所有加入的数和数列中原有的数的最大值。  
我们设 $f(i)$ 表示所有大小为 $k$ 的子集中，$\gcd$ 为 $i$ 的子集数量，最终答案就是 $\sum_{i=1}^m i\times f(i)$。  
考虑莫比乌斯反演，定义 $F(i)$ 为大小为 $k$ 的子集中，$\gcd$ 为 $i$ 的倍数的方案数，根据定义容易得到 $F(i)=\sum_{i|d} f(d)$。  
同时，我们记 $cnt_i$ 为数列中存在因子 $i$ 的数的个数，则 $F(i)$ 中所有子集必然是从 $cnt_i$ 个数中选择 $k$ 个数的一个方案。因此，可以得到 $F(i)=C_{cnt_i}^k$。  
通过莫比乌斯反演可以用 $F(i)$ 表示 $f(i)$，得到如下式子：

$$f(i)=\sum_{i|d} F(d)\mu(\frac{d}{i})=\sum_{i|d}\mu(\frac{d}{i})\times C_{cnt_d}^k$$

$$Ans=\sum_{i=1}^m i\times f(i)=\sum_{i=1}^m i \sum_{i|d}\mu(\frac{d}{i})\times C_{cnt_d}^k$$

考虑插入一个数时，如何更新答案。观察到每次加入一个数最多使若干个 $cnt_x$ 变化 $1$，可以从这里入手。  
对于一个 $cnt_x$，它只会对所有 $i|x$ 的 $f(i)$ 中的一项产生贡献。因此，我们可以把它的贡献拆出来，就是 $\sum_{i|x} i\times \mu(\frac{x}{i})\times C_{cnt_x}^k$，每次 $cnt_x$ 加 $1$ 的时候，新增的贡献就是 $(C_{cnt_x+1}^k-C_{cnt_x}^k)\times(\sum_{i|x} i\times \mu(\frac{x}{i}))$ 。  
由于 $\mu*Id=\varphi$，容易发现后面那一大坨就是欧拉函数 $\varphi(x)$，线性筛预处理即可。  
我们把这 $n+q$ 个数顺次加入，每次维护 $cnt_x$ 和 $Ans$ 即可求解。每次更新 $cnt_x$ 复杂度为 $O(\sqrt{m})$ ，总复杂度为 $O((n+q)\sqrt{m})$。
### 代码
```cpp
#include<bits/stdc++.h>
#define reg register
typedef long long ll;
using namespace std;
const int mod=1e9+7;
const int MN=2e5+5;
const int MM=1e6+5;
int fac[MN],inv[MN];
inline ll C(int n,int m){
	if(n<m)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int phi[MM],pri[MM],F[MM],pcnt;
bool vis[MM];
int n,m,q,Ans,cnt[MM];
int main(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(reg int i=2;i<MN;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(reg int i=2;i<MN;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(reg int i=2;i<MN;i++)inv[i]=1ll*inv[i-1]*inv[i]%mod;
	phi[1]=1;
	for(reg int i=2;i<MM;i++){
		if(!vis[i])pri[++pcnt]=i,phi[i]=i-1;
		for(reg int j=1;i*pri[j]<MM&&j<=pcnt;j++){
			vis[i*pri[j]]=true;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	scanf("%d%d%d",&n,&m,&q);
	for(reg int i=1,x;i<=n;i++){
		scanf("%d",&x);
		for(reg int j=1;j*j<=x;j++){
			if(x%j)continue;cnt[j]++;Ans=(Ans+phi[j]*(C(cnt[j],m)-C(cnt[j]-1,m)))%mod;
			if(j*j!=x)cnt[x/j]++,Ans=(Ans+phi[x/j]*(C(cnt[x/j],m)-C(cnt[x/j]-1,m)))%mod;
		}
	}
	while(q--){
		static int x;scanf("%d",&x);
		for(reg int j=1;j*j<=x;j++){
			if(x%j)continue;cnt[j]++;Ans=(Ans+phi[j]*(C(cnt[j],m)-C(cnt[j]-1,m)))%mod;
			if(j*j!=x)cnt[x/j]++,Ans=(Ans+phi[x/j]*(C(cnt[x/j],m)-C(cnt[x/j]-1,m)))%mod;
		}
		printf("%d\n",(Ans+mod)%mod);
	}
	return 0;
}
```

---

## 作者：Leasier (赞：2)

前置芝士：[莫比乌斯反演](https://oi-wiki.org/math/number-theory/mobius/)

对倍数形式的莫比乌斯反演还是不熟 /kk

设 $f(i)$ 表示 $\gcd$ 为 $i$ 时的答案，$g(i)$ 表示 $\gcd$ 为 $j$ 的倍数时的答案，则 $g(i) = \displaystyle\sum_{i \mid d}^N f(d)$。由莫比乌斯反演可得：$f(i) = \displaystyle\sum_{i \mid d}^N \mu(\frac{i}{d}) g(d)$。

答案 $= \displaystyle\sum_{i = 1}^N i f(i)$

$ = \displaystyle\sum_{i = 1}^N i \displaystyle\sum_{i \mid d}^N \mu(\frac{i}{d}) g(d)$

$ = \displaystyle\sum_{d = 1}^N g(d) \displaystyle\sum_{i \mid d} i \mu(\frac{i}{d})$

$ = \displaystyle\sum_{d = 1}^N \mu(d) g(d)$

设 $cnt_i$ 表示当前 $a$ 中为 $i$ 的倍数的数的个数，则显然 $g(i) = C_{cnt_i}^k$，于是在预处理每个数的因数后枚举因数并更新答案即可。时间复杂度为 $O(N \log N + \sum \tau(a_i) + \sum \tau(c_i))$。

代码：
```cpp
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;

const int N = 1e6, M = 2e5 + 7, mod = 1e9 + 7;
int prime[N + 7], phi[N + 7], cnt[N + 7];
ll fac[M], inv_fac[M];
bool p[N + 7];
vector<int> v[N + 7];

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
	int cnt = 0;
	for (register int i = 1; i <= N; i++){
		for (register int j = i; j <= N; j += i){
			v[j].push_back(i);
		}
	}
	p[0] = p[1] = true;
	phi[1] = 1;
	for (register int i = 2; i <= N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= N; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				phi[t] = phi[i] * prime[j];
				break;
			}
			phi[t] = phi[i] * (prime[j] - 1);
		}
	}
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (register int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline ll comb(int n, int m, int mod){
	if (n < m) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

inline ll insert(int x, int k){
	int size = v[x].size();
	ll ans = 0;
	for (register int i = 0; i < size; i++){
		ll t = comb(cnt[v[x][i]], k, mod);
		cnt[v[x][i]]++;
		ans += phi[v[x][i]] * (comb(cnt[v[x][i]], k, mod) - t) % mod;
		if (ans < 0){
			ans += mod;
		} else if (ans >= mod){
			ans -= mod;
		}
	}
	return ans;
}

int main(){
	int n, k, q;
	ll ans = 0;
	scanf("%d %d %d", &n, &k, &q);
	init(n + q);
	for (register int i = 1; i <= n; i++){
		int a;
		scanf("%d", &a);
		ans = (ans + insert(a, k)) % mod;
	}
	for (register int i = 1; i <= q; i++){
		int c;
		scanf("%d", &c);
		ans = (ans + insert(c, k)) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：zhimao (赞：1)

一种不用欧拉函数的做法。

根据莫反套路，设 $f(x)$ 为 $\gcd$ 为 $x$ 的 $k$ 个数的组数， $F(x)$ 为 $\gcd$ 为 $x$ 的倍数 $k$ 个数的组数，则有所求答案为 $ans=\sum\limits_{i=1}^ni\times f(x),F(i)=\sum\limits_{i|d}f(d),F(i)=\tbinom{g(i)}{k}$ ，其中 $g(i)$  表示加入的数中为 $i$ 的倍数的数的个数。

则 
$$f(i)=\sum\limits_{i|d}\mu(\tfrac{d}{i})F(d)$$
$$ans=\sum\limits_{i=1}^n\sum\limits_{i|d}\mu(\tfrac{d}{i})F(d)$$

我们改变求和顺序，枚举 $F$

$$ans=\sum\limits_{i=1}^nF(i)\sum\limits_{d|i}d\times\mu(\tfrac{i}{d})$$

后面的系数只与 $i$ 有关，可以 $O(m\ln m)$ 预处理。每次加入一个数只会改变 $O(\sqrt n)$ 项 $F(i)$ 。则复杂度为 $O(q\sqrt m)$ 。

总时间复杂度为 $O(q\sqrt m+m\ln m)$ ，$m$ 为值域。

代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n,m,q,q1,miu[1000005],mu[1000005],pri[1000005],g[1000005],fac[1000005],inv[1000005],f[1000005],ans;
bool bo[1000005];
void xxs(int n)
{
    miu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!bo[i])
        {
            bo[i]=0;
            pri[++q1]=i;
            miu[i]=-1;
        }
        for(int j=1;j<=q1&&pri[j]*i<=n;j++)
        {
            bo[i*pri[j]]=1;
            if(i%pri[j]==0) break;
            miu[i*pri[j]]=-miu[i];
        }
    }
    for(int i=1;i<=n;i++)
    	if(miu[i]) for(int j=1;j*i<=n;j++) mu[i*j]=(mu[i*j]+j*miu[i]+mod)%mod;
}
int kp(int a,int b)
{
	int c=1;
	while(b)
	{
		if(b&1) c=1ll*c*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return c;
}
int c(int x,int y)
{
	if(x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
void ad(int x)
{
	++g[x];
	if(g[x]<m) return;
	ans-=f[x];
	ans=(ans+mod)%mod;
	f[x]=1ll*c(g[x],m)*mu[x]%mod;
	ans+=f[x];
	ans%=mod;
}
void add(int x)
{
	for(int i=1;i*i<=x;i++)
		if(x%i==0)
		{
			ad(i);
			if(i*i!=x) ad(x/i);
		}
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	xxs(1000005);
	fac[0]=1;
	for(int i=1;i<=200005;i++) fac[i]=1ll*i*fac[i-1]%mod;
	inv[200005]=kp(fac[200005],mod-2);
	for(int i=200005;i;i--) inv[i-1]=1ll*i*inv[i]%mod;
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add(x);
	}
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		add(x);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：le0n (赞：1)

### **题意**  
给定一个有 $n$ 个元素的数列 $\{a_i\}$ 和一个正整数 $k$，有 $q$ 次询问，每次向数列中加入一个数 $b$（有后效性），并询问添加完之后任意 $k$ 个元素的 $\gcd$ 之和。  
$1\leq n,k,q\leq 10^5, 1\leq a_i, b\leq 10^6$

### **题解**  
我们考虑欧拉反演:
$$n=\sum_{d|n}\varphi(d)$$
于是就有:
$$\gcd_{i=1}^{m}t_i=\sum_{\forall 1\leq i\leq m, d|t_i} \varphi(d)$$
设 $b$ 是 $a$ 的一个大小为 $k$ 的子集，则题目中所求即为
$$\sum_b \gcd_{i=1}^k b_i = \sum_b \sum_{\forall 1\leq i\leq k, d|b_i} \varphi(i)$$
我们设 $cnt_i$ 表示目前 $i$ 是数列 $\{a_i\}$ 中多少个数的因子，容易得出上式中 $i$ 的贡献为:
$$\tbinom{cnt_i}{k}\times \varphi(i)$$
于是我们只需预处理出 $\varphi(i)$和阶乘，然后顺序加入这 $n+q$ 个数并维护 $cnt_i$ 即可。具体来说，我们考虑加入的数 $b$ 的 $O(\sqrt{b})$ 个因子，对于每个因子 $d$，我们将答案加上 $(\tbinom{cnt_i}{k}-\tbinom{cnt_i-1}{k})\varphi(i)$，即 $\tbinom{cnt_i-1}{k-1}\varphi(i)$。  

总复杂度 $\Theta(w)-\Theta((n+q)\sqrt{w})$，其中 $w$ 为值域。

### **代码**
```cpp
#include <cstdio>
#define mod 1000000007
#define maxn 1000000

using namespace std;

int phi[maxn + 5];
int prime[maxn + 5];
bool ntp[maxn + 5];
int k;
int cnt[maxn + 5], ans = 0;
int fac[maxn + 5], inv[maxn + 5];
int qpow(int x, int y)
{
	int ans = 1;
	while(y)
	{
		if(y & 1)
			ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1; 
	}
	return ans;
}
void sieve()
{
	int i, j, cnt = 0;
	phi[1] = 1;
	for(i = 2; i <= maxn; i++)
	{
		if(!ntp[i])
		{
			phi[i] = i - 1;
			prime[++cnt] = i;
		}
		for(j = 1; j <= cnt && prime[j] * i <= maxn; j++)
		{
			ntp[i * prime[j]] = true;
			if(!(i % prime[j]))
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}
int C(int x, int y)
{
	return ((x < y) || (x < 0) || (y < 0)) ? 0 : (1ll * fac[x] * inv[y] % mod * inv[x - y] % mod);
}
void work(int x)
{
	int i;
	for(i = 1; i * i <= x; i++)
		if(!(x % i))
		{
			++cnt[i];
			if(cnt[i] >= k)
				ans = (ans + 1ll * phi[i] * C(cnt[i] - 1, k - 1) % mod) % mod;
			if(1ll * i * i != x)
			{
				++cnt[x / i];
				if(cnt[x / i] >= k)
					ans = (ans + 1ll * phi[x / i] * C(cnt[x / i] - 1, k - 1) % mod) % mod;
			}
		}
}

int main()
{
	int n, m, i, a;
	sieve();
	fac[0] = 1;
	for(i = 1; i <= maxn; i++)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[maxn] = qpow(fac[maxn], mod - 2);
	for(i = maxn; i >= 1; i--)
		inv[i - 1] = 1ll * inv[i] * i % mod;
	scanf("%d%d%d", &n, &k, &m);
	for(i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		work(a);
	}
	for(i = 1; i <= m; i++)
	{
		scanf("%d", &a);
		work(a);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

令 $f(i)$ 为在 $S$ 中选择 $k$ 个数，$\gcd$ 值为 $i$ 的方案数。

$g(i)$ 为 $\gcd| i$ 的方案数。

则 $g(i)=\sum \limits_{i|j}f(j)$。

由莫比乌斯反演可得 $f(i)=\sum \limits_{i|j} g(j)\mu(\frac{j}{i})$。

那么 $ans=\sum \limits_{i=1}^{V} if(i)$

$=\sum \limits_{i=1}^{V}i\sum \limits_{i|j}g(j)\mu(\frac{j}{i})$

$=\sum \limits_{j=1}^Vg(j)\sum \limits_{i|j}i\mu(\frac{j}{i})$

$=\sum \limits_{j=1}^Vg(j)\varphi(j)$。

而若整除 $j$ 的数有 $cnt_j$ 个，则 $g(j)=\binom{cnt_j}{k}$。

因此答案为 $\sum \limits_{j=1}^V \binom{cnt_j}{k}\varphi(j)$。

在每次修改时枚举因数修改每一个因数 $j$ 的 $\binom{cnt_j}{k}\varphi(j)$ 即可。


```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int mod=1e9+7;
const int maxv=1e6;

int Mod(int x){
	if(x<0){
		if(x<=-mod){
			x%=mod;
		}
		if(x==0){
			return x;
		}
		return x+mod;
	}
	if(x>=mod){
		x%=mod;
	}
	return x;
}

int phi[maxv+5];
int frac[maxv+5];
int inv[maxv+5];
int cnt[maxv+5];
bool notprime[maxv+5];
vector<int> primes;
int ans=0;
int k;

int binom(int n,int m){
	if(n<m){
		return 0;
	}
	return Mod(frac[n]*Mod(inv[m]*inv[n-m]));
}

int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=Mod(ans*a);
		}
		a=Mod(a*a);
		b>>=1;
	}
	return ans;
}

void init(){
	frac[0]=1;
	for(int i=1;i<=maxv;i++){
		frac[i]=Mod(frac[i-1]*i);
	}
	inv[maxv]=ksm(frac[maxv],mod-2);
	for(int i=maxv-1;i>=0;i--){
		inv[i]=Mod(inv[i+1]*(i+1));
	}
	phi[1]=1;
	for(int i=2;i<=maxv;i++){
		if(!notprime[i]){
			phi[i]=i-1;
			primes.push_back(i);
		}
		for(auto j:primes){
			if(i*j>maxv){
				break;
			}
			notprime[i*j]=1;
			if(i%j==0){
				phi[i*j]=Mod(phi[i]*j);
				break;
			}
			else{
				phi[i*j]=Mod(phi[i]*(j-1));
			}
		}
	}
}

void ins(int x){
	cnt[x]++;
	ans=Mod(ans-Mod(phi[x]*binom(cnt[x]-1,k)));
	ans=Mod(ans+Mod(phi[x]*binom(cnt[x],k)));
}

void insert(int x){
	for(int i=1;i*i<=x;i++){
		if(x%i==0){
			ins(i);
			if(i*i!=x){
				ins(x/i);
			}
		}
	}
}

signed main(){
	int now=1;
	for(int i=1;i<=12;i++){
		now=now*i/__gcd(now,i);
	}
	init();
	int n,q;
	cin>>n>>k>>q;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		insert(x);
	}
	while(q--){
		int x;
		cin>>x;
		insert(x);
		cout<<ans<<"\n";
	}
}
```

---

## 作者：Tachibana_Kimika (赞：0)

我们可以枚举 gcd，然后对于每个不同的 gcd，求有多少个集合满足条件。但是我们发现多少个集合其实并不好算，但是我们可以算出来有多少个集合的 gcd 是当前 gcd 的倍数，设这个为 $f(x)$ 吧，那么我们只需要统计出 $x$ 的倍数有多少个，然后排列组合即可，为 $\tbinom{cnt_x}{k}$。

然后我们要算有多少个集合的 gcd 正好为 $x$，设这个是 $g(x)$，那么我们可以考虑容斥了。首先我们先加上一个 $f(x)$，为了把两倍 $x$，三倍 $x$ 等等的任意倍 $x$ 为 gcd 的集合去掉，我们减去 $f(p_i)$，其中 $p$ 为质数集合。然后我们又多算了任意两个质数乘起来，所以我们还要加上 $\sum_{i\in p}\sum_{j\in p}f(ij)[i\neq j]$ ，然后还要减去三个质数乘起来，以此类推。

有没有发现我们只计算了每个质因子次数为 $1$ 的 $x$？有没有感觉到一丝熟悉？没错，这个式子的容斥系数就是 $\mu$ 函数。

我们可以得到 $g(x)=\sum_{i|x}f(i)\mu(\frac{x}{i})$，拆掉 $f(x)$，统计答案就是：

$$\sum_{i=1}^ni\sum_{j|i}\tbinom{cnt_j}{k}\mu(\frac{x}{j})$$

考虑 $cnt_j$ 带来的贡献，因为 $j$ 为 $i$ 的倍数，所以枚举 $j$ 的因子即可。贡献为：

$$\sum_{i|j}\tbinom{cnt_j}{k}i\mu(\frac{x}{j})$$

把组合数提出来，因为 $cnt_j$ 每次只会增加 $1$，所以只需要计算变动 $1$ 的情况。

$$(\tbinom{cnt_j+1}{k}-\tbinom{cnt_j}{k})\sum_{i|j}i\mu(\frac{x}{j})$$

不难发现右部是一个狄利克雷卷积的形式，因为 $\mu* id=\phi$，所以可以把右部看成一个欧拉函数，欧拉函数可以线性筛预处理，组合数也可以预处理阶乘，每次插入新数字的时候枚举 $\sqrt V$ 个因子即可，总复杂度 $V+n\sqrt V$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int p=1e9+7;

int qpow(int a,int index){
	int ans=1;
	while(index){
		if(index&1) ans=ans*a%p;
		a=a*a%p; index>>=1;
	}
	return ans;
}

int fac[N],ifac[N]; 
void init(int n){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%p;
	ifac[n]=qpow(fac[n],p-2);
	for(int i=n-1;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%p;
}

int C(int n,int m){
	if(n<m||n<0||m<0) return 0;
	return fac[n]*ifac[n-m]%p*ifac[m]%p;
}

int pri[N],res;
bitset<N>vis;
int phi[N];

void sieve(int n){
	phi[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pri[++res]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=res&&i*pri[j]<=n;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}else{
				phi[i*pri[j]]=phi[i]*phi[pri[j]];
			}
		}
	}
}

int cnt[N],ans,k;

void insert(int x){
	for(int i=1;i*i<=x;i++){
		if(x%i==0){
			ans=(ans+phi[i]*(C(cnt[i]+1,k)-C(cnt[i],k)+p)%p)%p; cnt[i]++;
			if(i*i==x) continue;
			ans=(ans+phi[x/i]*(C(cnt[x/i]+1,k)-C(cnt[x/i],k)+p)%p)%p; cnt[x/i]++;
		}
	}
}

inline void fake_main(){
	int n,q; cin>>n>>k>>q;
	for(int i=1;i<=n;i++){
		int tmp; cin>>tmp;
		insert(tmp);
	}
	for(int i=1;i<=q;i++){
		int tmp; cin>>tmp;
		insert(tmp); cout<<ans<<"\n";
	} 
}

signed main(){
	init(N-10); sieve(N-10);
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：Inui_Sana (赞：0)

其实不会反演也可以做。

首先显然要考虑给你每个数个数，怎么计数。最简单的方法是从大枚举到小，设 $c_i$ 为 $i$ 的个数，$f_i$ 为 $\gcd=i$ 的 $k$ 元组出现了多少次，则 $f_i=\binom{c_i}{k}-\sum_j f_{ij}$，就是 $\gcd$ 为 $i$ 或 $i$ 的倍数减去 $\gcd$ 为 $i$ 的倍数的。

这样单次是 $O(V\ln V)$ 的。考虑怎么高效地处理修改。每次只有 $d(b_j)$ 个 $c_i,f_i$ 被修改，所以可以预处理每个数的所有因数然后暴力修改。

但是一个 $c_i$ 修改完后也会影响所有 $j\mid i$ 的 $c_j$，怎么办呢？

打表发现 $10^6$ 以内，对于一个 $x$，他的所有因数的因数之和大概在 $8000$ 到 $9000$ 之间。结合本题时间限制可以通过。具体实现是计算完 $f_x$ 的增加量后，以此修改所有 $y|x$ 的 $f_y$ 的增加量。

code：

```cpp
int n,m,k=1e6,q,c[N],d[N],f[N],fac[N],ifac[N];
vector<int> g[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
il int binom(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
void Yorushika(){
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,n){
		int x;scanf("%d",&x);
		c[x]++;
	}
	fac[0]=1;
	rep(i,1,k)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[k]=qpow(fac[k],mod-2);
	drep(i,k-1,0)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	rep(i,1,k){
		for(int j=i+i;j<=k;j+=i)c[i]+=c[j],g[j].eb(i);
	}
	int ans=0;
	drep(i,k,1){
		f[i]=binom(c[i],m);
		for(int j=i+i;j<=k;j+=i)f[i]=Mod(f[i],mod-f[j]);
		ans=Mod(ans,1ll*f[i]*i%mod);
	}
	while(q--){
		int x;scanf("%d",&x);
		for(int i:g[x])d[i]=0;
		d[x]=Mod(binom(c[x]+1,m),mod-binom(c[x],m)),c[x]++,ans=Mod(ans,1ll*x*d[x]%mod);
		for(int i:g[x])d[i]=Mod(d[i],mod-d[x]);
		drep(i,(int)g[x].size()-1,0){
			int y=g[x][i];
			d[y]=Mod(d[y],Mod(binom(c[y]+1,m),mod-binom(c[y],m))),c[y]++,ans=Mod(ans,1ll*y*d[y]%mod);
			for(int j:g[y])d[j]=Mod(d[j],mod-d[y]);
		}
		printf("%d\n",ans);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：一只绝帆 (赞：0)

~~欧拉反演就是好，就是好来就是好。~~

首先把题意转化成将两个序列拼在一起，求出每个前缀的答案。

你发现每个前缀的答案是基于上一个前缀的，我们只需要处理每次新加一个数的答案即可。

也就是，我们要维护一个集合，支持插数，查询一个数和里面每个 $k-1$ 元组的 $\gcd$ 之和。

运用伟大的欧拉反演：

$$\begin{aligned}&\varphi*I=Id\\\to &n=\sum_{x|n}\varphi(x)\end{aligned}$$

所以可以将 $\gcd$ 摊到每个因数上，只要两个数有共同的因数，那么就对答案贡献 $\varphi(x)$，出现了多次的因数维护一个出现次数乘上即可。

Code：
```cpp
// Problem: CF645F Cowslip Collections
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF645F
// Memory Limit: 500 MB
// Time Limit: 8000 ms

#include<bits/stdc++.h>
#define pb emplace_back
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
using namespace std;typedef long long ll;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int p=1e9+7,N=1e6+5;
int n,k,q,is[N],pr[N],pnt,phi[N],d[N];vector<int> v[N];ll ans,fac[N],inv[N];
void init(int n) {
	fac[0]=1;F(i,1,n) fac[i]=fac[i-1]*i%p;
	inv[0]=inv[1]=1;F(i,2,n) inv[i]=(p-p/i)*inv[p%i]%p;
	F(i,2,n) inv[i]=inv[i]*inv[i-1]%p;
	phi[1]=1;F(i,2,n) {
		if(!is[i]) pr[++pnt]=i,phi[i]=i-1;
		F(j,1,pnt) if(i*pr[j]<=n) {
			is[i*pr[j]]=1;
			if(i%pr[j]==0) {phi[i*pr[j]]=phi[i]*pr[j];break;}
			else phi[i*pr[j]]=phi[i]*phi[pr[j]];
		} else break;
	} F(i,1,n) F(j,1,n) if(i*j<=n) v[i*j].pb(i); else break;
}
ll C(ll n,ll m) {if(n<m) return 0;return fac[n]*inv[m]%p*inv[n-m]%p;}
ll ins(int x) {
	ll res=0;for(int i:v[x]) res=(res+phi[i]*C(d[i],k-1)%p)%p;
	for(int i:v[x]) d[i]++;return res;
}
int main() {
	n=read();k=read();q=read();init(1e6);
	F(i,1,n) ans=(ans+ins(read()))%p;
	F(i,1,q) {
		ans=(ans+ins(read()))%p;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

