# [ABC227G] Divisors of Binomial Coefficient

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc227/tasks/abc227_g

二項係数 $ \displaystyle\ \binom{N}{K} $ の正の約数の個数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- $ 0\ \leq\ K\ \leq\ \min(10^6,N) $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ \displaystyle\ \binom{5}{2}=10 $ です。$ 10 $ の正の約数は $ 1,2,5,10 $ の $ 4 $ 個です。

### Sample Explanation 2

$ \displaystyle\ \binom{103}{3}=176851 $ です。$ 176851 $ の正の約数は $ 8 $ 個あります。

## 样例 #1

### 输入

```
5 2```

### 输出

```
4```

## 样例 #2

### 输入

```
103 3```

### 输出

```
8```

## 样例 #3

### 输入

```
1000000000000 1000000```

### 输出

```
110520107```

# 题解

## 作者：daniEl_lElE (赞：6)

## 思路

$\dbinom{N}{K}=\dfrac{\prod_{i=N-K+1}^Ni}{ \prod_{i=1}^Ki}$。

考虑因式分解定理，$x=p_1^{q_1}p_2^{q_2}p_3^{q_3}\dots$，则 $x$ 的因子有 $\prod (q_i+1)$ 个。

我们现在想知道的就是 $\dfrac{\prod_{i=N-K+1}^Ni}{ \prod_{i=1}^Ki}$ 的每个质因数出现的次数。考虑两段长度均为 $K$，每一段中大于 $K$ 的因数在其中最多出现一次。那么我们可以对上面和下面分别进行区间筛（$1\sim 10^6$），然后对于所有筛完不是 $1$ 的数肯定是素数（$\sqrt{N}\leq$ 的因数最多只有一种一个）。所以总复杂度是 $\Theta(10^6\ln 10^6)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
bool isp[1000005];
int now[1000005];
int cnt[1000005];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,k;
	cin>>n>>k;
	for(int i=2;i<=1000000;i++) isp[i]=1;
	for(int i=2;i<=1000000;i++) if(isp[i]) for(int j=i*2;j<=1000000;j+=i) isp[j]=0;
	for(int i=1;i<=k;i++) now[i]=i;
	for(int i=2;i<=1000000;i++){
		int fst=i;
		for(int j=fst;j<=k;j+=i){
			while(now[j]%i==0){
				now[j]/=i;
				cnt[i]--;
			}
		}
	}
	for(int i=1;i<=k;i++) now[i]=n-k+i;
	for(int i=2;i<=1000000;i++){
		int fst=((n-k)/i+1)*i;
		for(int j=fst;j<=n;j+=i){
			while(now[j+k-n]%i==0){
				now[j+k-n]/=i;
				cnt[i]++;
			}
		}
	}
	int ans=1;
	for(int i=2;i<=1000000;i++){
		ans=ans*(cnt[i]+1)%mod;
	}
	for(int i=1;i<=k;i++) if(now[i]!=1) ans=ans*2%mod;
	cout<<ans;
}
```

---

## 作者：E1_de5truct0r (赞：3)

~~一开始没看到 $k \leq 10^6$，以为是神仙题~~。

### 思路

两个式子：

1. $\dbinom{n}{k}=\dfrac{n \times (n-1) \times \dots \times (n-k+1)}{1 \times 2 \times \dots \times k}=\dfrac{\prod\limits_{i=n-k+1}^{n}i}{\prod\limits_{i=1}^{k}i}$

2. 若 $x={p_1}^{q_1} \times {p_2}^{q_2} \times \dots \times {p_n}^{q_n}$，那么 $x$ 的因数个数是 $(q_1+1)(q_2+1)\dots(q_n+1)$。

	形式化的，即若 $x=\prod_{i=1}^{n}{p_i}^{q_i}$，则 $x$ 的因数个数有 $\prod_{i=1}^{n} (q_i+1)$ 个。
    
因此我们可以求出 $n-k+1$ 到 $n$ 中的每个质数的个数，再求出 $1$ 到 $k$ 中的每个质数的个数，二者相减再相乘即可。

但是这个做法的复杂度是 $O(n \ln n)$ 的。考虑优化：

- 一个数 $x$ 中，$\gt \lceil\sqrt{x}\,\rceil$ 的质因数最多只有一个。这个是容易理解的，因为 $(\lceil\sqrt{x}\,\rceil)^2 \geq x$。所以有一个常见的 trick——我们可以把这个质数拎出来单独处理，其他的小质数可以筛出来。

	那么不难发现，本来要筛 $1 \sim n$ 的质数，现在只需要筛 $1 \sim \sqrt{n}$ 即可。这个范围还是可以接受的。
    
因此对 $1 \sim k$ 和 $n-k+1 \sim n$ 两段使用区间筛。复杂度 $O(k \ln k)$。

---

## 作者：Gaode_Sean (赞：3)

这题想到筛质数就可以，没什么难点。

$\dbinom{n}{k}=\frac{\prod\limits_{i=n-k+1}^ni}{\prod\limits_{i=1}^ki}$。

$1$. 预处理出 $1 \sim 10^6$ 中所有的质数。

$2$. 用预处理出的质数分别对上下两个长度为 $k$ 的区间进行区间筛。

$3$. 设 $cnt_i$ 表示质数 $i$ 出现的次数，扫描 $1 \sim k$ 时，每次将 $cnt_i$ 减一。扫描 $n-k+1 \sim n$ 时，每次将 $cnt_i$ 加一。 

$4$. 注意到 $n-k+1 \sim n$ 中会有一些质数是大于 $10^6$ 的，但是都只会出现一次，所以不会影响复杂度。

时间复杂度不会算。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=1e6;
const ll mod=998244353;
ll n,m,v[M+5],pr[M],cnt[M],val[M],ans=1;
void init()
{
	for(int i=2;i<=M;i++)
	{
		if(v[i]) continue;
		for(int j=i;j<=M/i;j++) v[i*j]=1;
	}
	for(int i=2;i<=M;i++) if(!v[i]) pr[++pr[0]]=ll(i);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	init();
	for(int i=1;i<=pr[0];i++)
	{
		for(ll j=1;j<=m/pr[i];j++)
		{
			ll s=pr[i]*j;
			while(s%pr[i]==0) s/=pr[i],cnt[i]--;
		}
	}
	for(ll i=n-m+1;i<=n;i++) val[i-n+m]=i;
	for(int i=1;i<=pr[0];i++)
	{
		for(ll j=(n-m+1)/pr[i];j<=n/pr[i];j++)
		{
			if(pr[i]*j<=n-m) continue;
			while(val[pr[i]*j-n+m]%pr[i]==0) val[pr[i]*j-n+m]/=pr[i],cnt[i]++;
		}
	}
	for(int i=1;i<=pr[0];i++) ans=(ans*(cnt[i]+1ll))%mod;
	for(int i=1;i<=m;i++) if(val[i]>1) ans=(ans*2ll)%mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc227_g%20[ABC227G]%20Divisors%20of%20Binomial%20Coefficient)

# 思路

首先需要知道一个事情，对于一个数 $x = \prod{p_i^{c_i}}$，它的约数个数是：

$$
\prod{(c_i + 1)}
$$

那么先将 $\binom{k}{n}$ 展开：

$$
\frac{\prod_{i = n - k + 1}^{n}i}{k!}
$$

发现一个数的约数个数只与其唯一分解后的指数有关，考虑统计每一个质数所对应的指数。

因为一个数 $x$，大于 $\sqrt{n}$ 的质因子只会有一个。证明很简单，考虑反证法，如果有两个大于 $\sqrt{n}$ 的质因子，二者相乘一定大于 $n$。

那么，我们直接筛出 $1 \sim \sqrt{n}$ 的质数。对于 $k!$ 的处理我们可以直接在筛质数的过程中处理掉，时间复杂度 $\Theta(\sqrt{n} \ln n \log n)$。

接着处理分子。考虑枚举质数，暴力将 $[n - k + 1,n]$ 的数去除掉当前枚举的质数，时间复杂度是 $\Theta(k \ln k \log n)$ 的。

然后去除掉小于 $\sqrt{n}$ 的约数，就最多剩下一个约数了。暴力加入即可。

因为值域较大，需要开 `umap` 存储。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Mul(a,b) (((a) % mod) * ((b) % mod) % mod)

using namespace std;

const int N = 1e6 + 10,mod = 998244353;
int n,k,ans = 1;
int cnt[N];
bool vis[N];
vector<int> v,p;
unordered_map<int,int> num;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void init(){
    vis[1] = true;
    for (re int i = 2;i <= 1e6;i++){
        if (!vis[i]){
            p.push_back(i);
            if (i <= k) cnt[i]--;
            for (re int j = 2;i * j <= 1e6;j++){
                vis[i * j] = true;
                int x = i * j,tot = 0;
                if (x <= k){
                    while (x % i == 0) x /= i,tot++;
                    cnt[i] -= tot;
                }
            }
        }
    }
}

signed main(){
    n = read(),k = read();
    init();
    for (re int i = 1;i <= k;i++) v.push_back(n - i + 1);
    if (v.empty()) goto End;// 特判，不然会 RE
    for (auto x:p){
        int t = n - (n / x) * x;
        for (re int i = t;i < v.size();i += x){
            int tot = 0;
            while (v[i] % x == 0) v[i] /= x,tot++;
            cnt[x] += tot;
        }
    }
    for (auto x:v){
        if (x != 1) num[x]++;
    }
    for (auto x:v){
        ans = Mul(ans,num[x] + 1); num[x] = 0;
    }
    End:;
    for (re int i = 1;i <= 1e6;i++) ans = Mul(ans,cnt[i] + 1);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

好题，场切了。

将一个数唯一分解后，一个数的因数个数为 $\prod (c_i+1)$。

那就不难想到暴力了，对于每一个 $x \in [n-k+1,n]$，分解它的时间复杂度为 $O(\sqrt x)$，所以暴力时间复杂度为 $O(k\sqrt n)$。

考虑将枚举质因数的循环提到外层，即计算每一个质数 $f_j$ 对答案的贡献。不难发现 $f_j$ 只对它的倍数有贡献，于是算出区间内第一个 $f_j$ 的倍数，然后一直累加 $f_j$ 计算贡献即可。时间复杂度为 $O(\sqrt n \ln k \log \sqrt n)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=1e6+10; 
const int Mod=998244353; 
int n,k; 
bool st[N]; 
int a[N],b[N]; 
int f[N],cnt=0; 
il void init(){ 
	for(int i=2;i<N;i++){ 
		if(!st[i]) f[++cnt]=i; 
		for(int j=1;j<=cnt&&f[j]*i<N;j++){ 
			st[f[j]*i]=true; 
			if(i%f[j]==0) break; 
		} 
	} 
} 
signed main(){ 
//	freopen("div.in","r",stdin); 
//	freopen("div.out","w",stdout); 
	init(); int ans=1; 
	n=read(),k=read(); 
	unordered_map<int,int> mp; 
	for(int i=1;i<=k;i++) a[i]=n-k+i,b[i]=i; 
	for(int j=1;j<=cnt;j++){ 
		int g=n/f[j],id=g*f[j]-(n-k); 
		while(id>=1){ 
			while(a[id]%f[j]==0) a[id]/=f[j],mp[f[j]]++; 
			id-=f[j]; 
		} 
		g=k/f[j],id=g*f[j]; 
		while(id>=1){ 
			while(b[id]%f[j]==0) b[id]/=f[j],mp[f[j]]--; 
			id-=f[j]; 
		} 
	} for(int i=1;i<=k;i++) if(a[i]>1) mp[a[i]]++; 
	for(auto u:mp) ans=ans*(u.y+1)%Mod; 
	printf("%lld\n",ans); return 0; 
} 
```

---

## 作者：Robin_kool (赞：0)

发现 $k$ 比较小，考虑展开 $C_n^k$。

设 $S=C_n^k=\frac{\prod_{i=n-k+1}^n i}{\prod_{i=1}^k i}$。很好理解。

对于分子分母分别计算，有一条很显然的性质：

对于正整数 $x$ 若能拆成 $\prod p_i^{q_i}$ 的性质，那么它的正因子个数为 $\prod (q_i+1)$。

考虑预先处理 $10^6$ 的质数，暴力枚举质因数即可。

```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 1e6 + 10, mod = 998244353;
bool p[M]; 
ll n, k, now[M], cnt[M], ans = 1;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	n = read(), k = read();
	memset(p, 1, sizeof p);
	for(int i = 2; i <= M - 10; ++ i){
		if(!p[i]) continue;
		for(int j = i * 2; j <= M - 10; j += i){
		    p[j] = 0;
		}
	}
	for(int i = 1; i <= k; ++ i) now[i] = i;
	for(ll i = 2; i <= M - 10; ++ i){
		if(!p[i]) continue;
		for(ll j = i; j <= k; j += i){
			while(now[j] % i == 0){
				now[j] /= i;
				-- cnt[i];
			}
		}
	}
	for(int i = 1; i <= k; ++ i) now[i] = n - k + i;
	for(ll i = 2; i <= M - 10; ++ i){
		if(!p[i]) continue;
		for(ll j = ((n - k) / i + 1) * i; j <= n; j += i){
			while(now[j + k - n] % i == 0){
				now[j + k - n] /= i;
				++ cnt[i];
			}
		}
	}
    for(int i = 2; i <= M - 10; ++ i) ans = ans * (cnt[i] + 1) % mod;
    for(int i = 1; i <= k; ++ i) if(now[i] != 1) ans = ans * 2 % mod;
    write(ans);
	return 0;
}

```

---

## 作者：Unordered_OIer (赞：0)

# Description

求 $\begin{pmatrix}N\\K\end{pmatrix}$ 的正约数个数，其中 $N \leq 10^{12},K \leq 10^6$。

# Solution

小清新数学题 qwq。看到 $N$ 与 $K$ 范围不同，容易想到以 $K$ 作为突破口。

首先统计一个数的正约数个数，我们只需要分解一下，$x=p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_k^{\alpha_k}$，那么其正约数个数即为 $(\alpha_1+1)(\alpha_2+1)\cdots(\alpha_k+1)$。

我们先看：

$$\begin{pmatrix}N\\K\end{pmatrix}=\dfrac{N^{\underline{K}}}{K!}$$

$N^{\underline K}$ 即 $\prod\limits_{i=N-K+1}^Ni$。

对于一个素因子 $p$ 的 $\alpha=$ 在 $\begin{pmatrix}N\\K\end{pmatrix}$ 中的个数 $=$ 在 $N^{\underline{K}}$ 中的个数 $-$ 在 ${K!}$ 中的个数。只需要统计 $[N-K+1,N]$ 与 $[1,K]$ 中 $p^w$ 的倍数的个数即可，$w \geq 1$，$w \in \mathbb Z^+$。对于区间 $[l,r]$，算 $\sum w \times c(w)$ 就是这个区间对应的结果。

上述过程在 $p \leq 10^6$ 的时候是好做的，因为 $p$ 可以直接算出，但是 $N-K+1 \leq p \leq N$ 的 $p$ 就不能直接这么做。

考虑到，这一部分的 $p$ 最多在 $[N-K+1,N]$ 中仅出现 $1$ 次，且 $[N-K+1,N]$ 中的合数的最小素因子一定不会 $>10^6$，因为两个乘起来就爆 $10^{12}$ 了。因此我们可以用 $[1,10^6]$ 内的素数筛出 $[N-K+1,N]$ 中的素数，然后筛出多少个（比如 $a$ 个）就在原来的基础上 $\times 2^a$ 就行了。

复杂度 $O(N \ln N)$。

```cpp
const ll N=1e6+5;
ll pr[N],c[N],cnt;
bool vst[N];
void xxs(ll n){
  for(ll i=2;i<=n;i++){
    if(!vst[i])pr[++cnt]=i;
    for(ll j=1;j<=cnt&&i*pr[j]<=n;j++){
      vst[i*pr[j]]=1;
      if(i%pr[j]==0)break;
    }
  }
}
const ll P=998244353;
ll n,K;
ll count(ll l,ll r,ll x){
  ll fir=(l/x+(l%x!=0))*x;
  ll sec=(r/x)*x;
  return (sec-fir)/x+1;
}
ll rem[N];
int main(){
  xxs(1e6);
  n=read(),K=read();
  for(ll i=1;i<=cnt;i++){
    ll cur=pr[i];
    while(cur<=n)c[i]+=count(n-K+1,n,cur)-count(1,K,cur),c[i]%=P,cur*=pr[i];
  }
  ll ans=1;
  for(ll i=1;i<=cnt;i++)ans=(ans*(c[i]+1))%P;
  for(ll i=1;i<=K;i++)rem[i]=i+n-K;
  for(ll i=1;i<=cnt;i++){
    ll fir=((n-K+1)/pr[i]+((n-K+1)%pr[i]!=0))*pr[i];
    for(ll j=fir;j<=n;j+=pr[i])
      while(rem[j-n+K]%pr[i]==0)rem[j-n+K]/=pr[i];
  }
  for(ll i=1;i<=K;i++)if(rem[i]!=1)ans=(ans*2)%P;
  cout<<ans<<'\n';
  return 0;
}
```

---

