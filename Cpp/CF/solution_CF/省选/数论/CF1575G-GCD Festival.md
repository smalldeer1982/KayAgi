# GCD Festival

## 题目描述

Mr. Chanek has an array $ a $ of $ n $ integers. The prettiness value of $ a $ is denoted as:

 $ $$$\sum_{i=1}^{n} {\sum_{j=1}^{n} {\gcd(a_i, a_j) \cdot \gcd(i, j)}} $ $ </p><p>where  $ \\gcd(x, y) $  denotes the greatest common divisor (GCD) of integers  $ x $  and  $ y $ .</p><p>In other words, the prettiness value of an array  $ a $  is the total sum of  $ \\gcd(a\_i, a\_j) \\cdot \\gcd(i, j) $  for all pairs  $ (i, j) $ .</p><p>Help Mr. Chanek find the prettiness value of  $ a $ , and output the result modulo  $ 10^9 + 7$$$!

## 样例 #1

### 输入

```
5
3 6 2 1 4```

### 输出

```
77```

# 题解

## 作者：1saunoya (赞：4)

/kk 老年人做个 2200 都觉得很开心了属于是


$\sum \sum \gcd(i, j) \times \gcd (a_i, a_j)$


$\gcd(i,j) = \sum_{d|\gcd(i,j)}\varphi(d)$


$\sum_{d} \varphi(d) \sum_{i|d} \sum_{j|d} \gcd(a_i,a_j)$

然后关键在 $\sum_{i|d} \sum_{j|d} \gcd(a_i,a_j)$ 上。

令 $b = [a_{kd}], k \in Z$。

这样的话，要做的就是 $\gcd(b_i, b_j)$。

$k = \sum_{d|k} \varphi(d)$。

然后我们只需要做一个高维前缀和（或者普通的 $n \ln n$ 搞一下）。

就可以算出来 $c_i = \sum_{i|j} cnt_{j}$。

所求的 $\gcd = ik$ 的个数的对数刚好是 $c_i^2 $，然后乘上系数 $\varphi(d)$ 就可以了。


```cpp

#include <bits/stdc++.h>
using namespace std;
const int B = 400;
const int P = 1e9 + 7;
int main() {
 ios::sync_with_stdio(false);
 cin.tie(nullptr);
 int n;
 cin >> n;
 vector<int> a(n + 1, 0);
 for (int i = 1; i <= n; i++) {
  cin >> a[i];
 }
 vector<int> phi(100000 + 1, 0);
 iota(phi.begin(), phi.end(), 0);
 for (int i = 2; i <= 100000; i++) {
  if (phi[i] == i) {
   for (int j = i; j <= 100000; j += i) {
    phi[j] = phi[j] / i * (i - 1);
   }
  }
 }
 vector<int> primes;
 for (int i = 2; i <= 100000; i++) {
  if (phi[i] == i - 1) {
   primes.push_back(i);
  }
 }
 vector<int> cnt(100000 + 1, 0);
 int ans = 0;
 for (int d = 1; d <= n; d++) {
  int cur = 0;
  if (d < B) {
   for (int i = 1; i <= 100000; i++) {
    cnt[i] = 0;
   }
   for (int i = d; i <= n; i += d) {
    cnt[a[i]]++;
   }
   for (auto p : primes) {
    for (int j = 100000 / p; j >= 1; j--) {
     cnt[j] += cnt[j * p];
     if (cnt[j] >= P) {
      cnt[j] -= P;
     }
    }
   }
   for (int i = 1; i <= 100000; i++) {
    cur += (long long) cnt[i] * cnt[i] % P * phi[i] % P;
    if (cur >= P) {
     cur -= P;
    }
   }
  } else {
   for (int i = d; i <= n; i += d) {
    for (int j = d; j <= n; j += d) {
     cur += __gcd(a[i], a[j]);
     if (cur >= P) {
      cur -= P;
     }
    }
   }
  }
  ans += (long long) cur * phi[d] % P;
  if (ans >= P) {
   ans -= P;
  }
 }
 cout << ans << "\n";
 return 0;
}

```

---

## 作者：周子衡 (赞：4)

运用莫比乌斯反演的一些技巧（或者说欧拉函数的知识），我们知道

$$
x=\sum_{d|x}\varphi(d)
$$

故原式

$=\sum_{i=1}^n\sum_{j=1}^n\gcd(a_i,a_j)\sum_{d|\gcd (i,j)}\varphi(d)$

$=\sum_d \varphi(d) \sum_{d|i}\sum_{d|j}\gcd(a_i,a_j)$

下面的复杂度分析中我们记 $M=\max \{a_1,...,a_n\}$。

记 $F(d)=\sum_{d|i}\sum_{d|j}\gcd(a_i,a_j)$。首先我们知道，满足 $d|i$ 的 $i$ 不超过 $\dfrac{n}{d}$，如果我们暴力枚举 $i,j$ 来计算 $\gcd(a_i,a_j)$，总时间复杂度为 $O(\dfrac{n^2}{d^2}\log M)$。这个复杂度在 $d$ 比较大是优秀的，但 $d$ 小时很劣，我们需要另外的做法。

再套用开头的公式，我们知道 $F(d)=\sum_x \varphi(x)\sum_{d|i,x|a_i}\sum_{d|i,x|a_j}1$。如果我们能算出对每个 $x$，满足 $d|i,x|a_i$ 的 $i$ 的个数 $c_{d,x}$，那么 $F(d)=\sum_{i=1}^M\varphi(i)c_{d,i}^2$。而计算 $c$ 可以在筛出所有素数后，做高维前缀和（可以参见洛谷上狄利克雷前缀和模板题），做到 $O(M\log \log M)$ 的复杂度。

我们取一个阈值 $T$，对 $T > d$ 用前一个算法，$T \leq d$ 用后一个算法。那么后一部分复杂度 $O(TM\log \log M)$，而前一部分计算 $\gcd$ 次数 $\leq n^2\sum_{i=T+1}^n\dfrac{1}{i^2}\leq n^2\int_{T}^n\dfrac{1}{x^2}\mathrm{d}x=n^2(\dfrac{1}{T}-\dfrac{1}{n})<\dfrac{n^2}{T}$，总复杂度 $O(\dfrac{n^2}{T}\log M)$。假定 $n,M$ 同阶，可以做到 $O(n^{1.5}(\log n\log \log n)^{0.5})$ 的复杂度（虽然这个分析更多是理论意义上的，实际上和 $O(n^{1.5}\log n)$ 做法应该无太大区别）。

```cpp
#include<cstdio>
#include<cstring>
 
using namespace std;
const long long MOD=1e9+7;
int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}
 
int gcd(int x,int y){return y?gcd(y,x%y):x;}
 
long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}
 
 
const int B=400;
 
bool prm[200000];int prm_lst[200000],pcnt;long long phi[200000];
 
void init_mu(int n)
{
	for(int i=2;i<=n;i++)prm[i]=1;phi[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(prm[i])prm_lst[++pcnt]=i,phi[i]=i-1;
		for(int j=1;j<=pcnt&&prm_lst[j]*i<=n;j++)
		{
			prm[prm_lst[j]*i]=0;
			if(i%prm_lst[j]==0){phi[i*prm_lst[j]]=phi[i]*prm_lst[j];break;;}
			phi[i*prm_lst[j]]=phi[i]*(prm_lst[j]-1);
		}
	}
}
 
int a[200000];
long long cnt[200000];
 
int main()
{
	init_mu(100000);//for(int i=1;i<=10;i++)printf("%d\n",phi[i]);
	int n=0;scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	long long ans=0;
	for(int d=1;d<=n;d++)
	{
		long long cur=0;
		if(d<=B)
		{
			memset(cnt,0,sizeof(cnt));
			for(int j=1;j*d<=n;j++)cnt[a[j*d]]++;
			for(int i=1;i<=pcnt;i++)
			{
				for(int j=100000/prm_lst[i];j>=1;j--)cnt[j]=add(cnt[j],cnt[j*prm_lst[i]]);
			}
			for(int i=1;i<=100000;i++)cur=add(cur,cnt[i]*cnt[i]%MOD*phi[i]%MOD);
		}
		else
		{
			for(int j=1;j*d<=n;j++)for(int k=1;k*d<=n;k++)cur=add(cur,gcd(a[j*d],a[k*d]));
		}
		//printf("%lld\n",cur);
		ans=add(ans,cur*phi[d]%MOD);
	}
	printf("%lld",ans);
}
```

---

## 作者：大眼仔Happy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1575G)

### 题目挺难，先给出几道简单一点的：

[$\begin{aligned}\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(i,j)\end{aligned}$](https://www.luogu.com.cn/problem/P2398) 和 [$\begin{aligned}\sum_{i=1}^{n}\sum_{j=1}^{n}\operatorname{lcm}(a_i,a_j)\end{aligned}$](https://www.luogu.com.cn/problem/P3911) 两道题。另外，后者有个[双倍经验](https://www.luogu.com.cn/problem/AT_agc038_c)，[三倍经验](https://www.luogu.com.cn/problem/P1829)。

实际上，由于 $\operatorname{lcm}$ 和 $\gcd$ 处理起来差不多（后者甚至更简单），所以这两道简单版本的题结合一下就是我们这道题的做法了。~~（所以为什么不应该是黑题……）~~

先给出两个莫反很经典的套路：

$$[n=1]=\sum_{d|n}^{}\mu(d)\qquad\qquad\qquad\qquad\qquad n=\sum_{d|n}^{}\varphi(d)$$

首先是 $\begin{aligned}\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(i,j)\end{aligned}$ 的两种解法：

$$\begin{aligned}

&\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(i,j)&\qquad\qquad\qquad\qquad\qquad&\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(i,j)\\

=&\sum_{G=1}^{n}\sum_{i=1}^{n}\sum_{j=1}^{n}[\gcd(i,j)=G]\times G&=&\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d|i,d|j}^{}\varphi(d)\\

=&\sum_{G=1}^{n}G\sum_{i=1}^{\lfloor\frac{n}{G}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{G}\rfloor}[\gcd(i,j)=1]&=&\sum_{d=1}^{n}\varphi(d)\lfloor\frac{n}{d}\rfloor^2\\

=&\sum_{G=1}^{n}G\sum_{i=1}^{\lfloor\frac{n}{G}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{G}\rfloor}\sum_{d|i,d|j}^{}\mu(d)\\


=&\sum_{G=1}^{n}G\sum_{d=1}^{\lfloor\frac{n}{G}\rfloor}
\mu(d)\lfloor\frac{n}{dG}\rfloor^2
\end{aligned}$$

显然第二种做法更加简单一点，事实证明，如果要刻意构造出 $[n=1]$ 的式子，是会更加复杂一点。

然后是这个（设 $A=\max_{i=1}^{n} a_i$）:

$$\begin{aligned}

&\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(a_i,a_j)\\

=&\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d|a_i,d|a_j}^{}\varphi(d)\\

=&\sum_{d=1}^{A}\sum_{i=1}^{n}[d|a_i]\sum_{j=1}^{n}[d|a_j]\\

=&\sum_{d=1}^{A}(\sum_{i=1}^{n}[d|a_i])^2

\end{aligned}$$

开一个桶记录每个 $a_i$ 的值，那么对于每一个 $d$，后面那个东西都可以用 $O(\dfrac{n}{d})$ 来完成，时间复杂度为 $\begin{aligned}\sum_{d=1}^{n}O(\dfrac{n}{d})=O(n\ln n)\end{aligned}$，所以暴力直接完事了。

## 接下来，本题正解部分：

首先我们考虑推一下式子：

$$\begin{aligned}

&\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(a_i,a_j)\gcd(i,j)\\

=&\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(a_i,a_j)\sum_{G|i,G|j}{}\varphi(G)\\

=&\sum_{G=1}^{n}\varphi(G)\sum_{i=1}^{\lfloor\frac{n}{G}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{G}\rfloor}\gcd(a_{i\times G},a_{j\times G})\\

=&\sum_{G=1}^{n}\varphi(G)\sum_{d=1}^{A}(\sum_{i=1}^{\lfloor\frac{n}{G}\rfloor}[d|a_{i\times G}])^2

\end{aligned}$$

然后我们发现，好像不能继续推式子了，所以就直接从代码处优化一下吧。

可以发现，我们枚举 $d$ 的时候，可以只需要枚举所有选定的 $a_{i\times G}$ 的因数即可。

所以最后的时间复杂度为 $\begin{aligned}\sum_{i=1}^{n}O(\dfrac{n}{d}\times \max \operatorname{d}(a_i))=O(n\ln n\times \max \operatorname{d}(a_i))\end{aligned}$，其中经过计算得到 $\max \operatorname{d}(a_i)=128$。

[那么如何更快的预处理每一个 $a_i$ 的因数？点看这里。](https://www.luogu.com.cn/discuss/681057)

代码如下（在 CF 上 AC 了，但是你谷 RMJ 炸掉了）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
const ll mod=1e9+7;
ll n,mx,A,a[N],tot;
bool vis[N];
ll p[N],phi[N],num[N],ans,res;
vector<ll>d[N],id[N];
void InitPhi()
{
	phi[1]=1;
	mx=max(n,A);
	for(int i=2;i<=mx;i++)
	{
		if(!vis[i])p[++tot]=i,phi[i]=i-1;
		for(int j=1;i*p[j]<=mx;j++)
		{
			vis[i*p[j]]=1;
			if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}//预处理phi 
void InitD()
{
	for(int i=1;i<=n;i++)id[a[i]].push_back(i);
	for(ll i=1;i<=A;i++)
	{
		for(ll j=i;j<=A;j+=i)
		{
			for(int k=0;k<id[j].size();k++)d[id[j][k]].push_back(i);
		}
	}
}//预处理每一个数的所有因数 
void solve(int x)
{
	for(int i=0;i<d[x].size();i++)
	{
		ll D=d[x][i];//D是i的约数 
		res=(res+(num[D]*2ll+1)*phi[D])%mod;
		num[D]++;
	}
}
void del(int x)
{
	for(int i=0;i<d[x].size();i++)
	{
		ll D=d[x][i];
		num[D]--;
	}
}
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),A=max(A,a[i]);
	InitPhi();InitD();
	for(int G=1;G<=n;G++)
	{
		res=0;
		for(int i=G;i<=n;i+=G)solve(i);
		for(int i=G;i<=n;i+=G)del(i);
		ans=(ans+res*phi[G])%mod;
	}
	printf("%lld",ans);
	return 0;
}
```

[话说网上找到了一个调和级数的证明，可以看看。](https://mp.weixin.qq.com/s?__biz=MzU5OTQ2NzIzNw==&mid=2247487070&idx=1&sn=a89f0afff78c659608bec57c05ad2dcd&chksm=feb53bd4c9c2b2c219afa9980562d1a7faf48d24e6d07b92687eb968d14d284bdd549d4770d4&scene=27)

总结一下就是：

$$\sum_{i=1}^{n}\dfrac{1}{i}\le 1+\int_{1}^{n}\dfrac{1}{x}\,dx=1+[\ln |x|]_{1}^{n}=1+\ln n$$

---

## 作者：syzf2222 (赞：2)

诈骗题属于是。

$\sum\limits_{i}\sum\limits_{j} \gcd(i,j)\gcd(a_i,a_j)=\sum\limits_{d} \varphi(d)\sum\limits_{i}\sum\limits_{j} \gcd(a_{di},a_{dj})$

$=\sum\limits_{d} \varphi(d)\sum\limits_{t} \varphi(t) (\sum\limits_{i}[t|a_{id}])^2$

至此，还想优化，发现十分困难。

仔细观察，发现枚举 $d$ ，枚举 $id$，复杂度为 $n\ln n$，后面枚举因子，复杂度 $d(n)$，发现只有两个亿，稳过。

码风丑陋，恕不奉上。

---

## 作者：bluewindde (赞：1)

upd 2024-09-02：LaTeX 炸了，已修。

考虑欧拉反演

$$\sum\limits_{d \mid n} \varphi(d) = n$$

则原式可以化为

$$
\begin{aligned}
&\sum\limits_{i = 1}^n \sum\limits_{j = 1}^n \gcd(a_i, a_j) \cdot \gcd(i, j) \\
= &\sum\limits_{i = 1}^n \sum\limits_{j = 1}^n \gcd(a_i, a_j) \sum\limits_{d \mid \gcd(i, j)} \varphi(d) \\
= &\sum\limits_{d = 1}^n \varphi(d) \sum\limits_{i = 1}^{\lfloor \frac n d \rfloor} \sum\limits_{j = 1}^{\lfloor \frac n d \rfloor} \gcd(a_{id}, a_{jd}) \\
= &\sum\limits_{d = 1}^n \varphi(d) \sum\limits_{i = 1}^{\lfloor \frac n d \rfloor} \sum\limits_{j = 1}^{\lfloor \frac n d \rfloor} \sum\limits_{k \mid \gcd(a_{id}, a_{jd})} \varphi(k) \\
= &\sum\limits_{d = 1}^n \varphi(d) \sum\limits_{k = 1}^{\max\{ a \}} \varphi(k) \left( \sum\limits_{i = 1}^{\lfloor \frac n d \rfloor} [k \mid a_{id}] \right)^2 \\
\end{aligned}
$$

线性筛 $\varphi$，预处理 $a_{id}$ 的所有因数 $k$。枚举 $d$ 和 $i$，再枚举 $id$ 的所有因数 $k$ 计算答案。

时间复杂度 $O(w + w \sqrt w + n \ln n \sqrt w)$，其中 $w$ 是值域大小。可以通过。

```cpp
#pragma GCC optimize("Ofast")

#include <iostream>
#include <map>
#include <vector>

#define int long long

using namespace std;

const int lim = 1e5;
const int mod = 1e9 + 7;

bool vis[lim + 5];
int pr[lim + 5], tail;
int phi[lim + 5];

int n;
int a[100005];
int cnt[100005];
vector<int> factor[100005];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1575G.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    phi[1] = 1;
    for (int i = 2; i <= lim; ++i) {
        if (!vis[i]) {
            pr[++tail] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tail && i * pr[j] <= lim; ++j) {
            vis[i * pr[j]] = 1;
            if (i % pr[j] == 0) {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            }
            phi[i * pr[j]] = phi[i] * phi[pr[j]];
        }
    }
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    for (int i = 1; i <= mx; ++i)
        for (int j = 1; j * j <= i; ++j)
            if (i % j == 0) {
                factor[i].push_back(j);
                if (j * j != i)
                    factor[i].push_back(i / j);
            }
    int ans = 0;
    for (int d = 1; d <= n; ++d) {
        for (int i = d; i <= n; i += d)
            for (auto fac : factor[a[i]])
                ++cnt[fac];
        for (int i = d; i <= n; i += d)
            for (auto fac : factor[a[i]])
                if (cnt[fac]) {
                    ans = (ans + phi[d] * phi[fac] % mod * cnt[fac] % mod * cnt[fac] % mod) % mod;
                    cnt[fac] = 0;
                }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

前置知识：狄利克雷前缀和。

给定数列 $a_i$ ，求数列 $b_i=\sum_{j|i}a_j$ 。

代码 ：
 
 ```cpp
const int N=100005;
int n,a[N],b[N];
scanf("%d",&n);
for(int i=1;i<=n;++i) scanf("%d",&a[i]),b[i]=a[i];
for(int j=1;j<=cnt;++j) 
	for(int k=1;k*p[j]<=n;++k)
		b[k*p[j]]+=b[k];
for(int i=1;i<=n;++i) printf("%d ",b[i]);
```
类似 FMT 。

变式：

给定数列 $a_i$ ，求数列 $b_i=\sum_{i|j}a_j$ 。

代码：

 ```cpp

const int N=100005;
int n,a[N],b[N];
scanf("%d",&n);
for(int i=1;i<=n;++i) scanf("%d",&a[i]),b[i]=a[i];
for(int j=1;j<=cnt;++j) 
	for(int k=n/p[j];k>=1;--k)
    	b[k]+=b[k*p[j]];
for(int i=1;i<=n;++i) printf("%d ",b[i]);
```
应用 ：CF1575G

题意 ：给定数列 $a_i$ ，求 $\sum_{i=1}^n\sum_{j=1}^n \gcd(i,j)\cdot \gcd(a_i,a_j)$ 。

数据范围： $n,a_i\in [1,10^5]$ 。

关于 $\phi(x)$ （欧拉函数）的性质：

对于正整数 $x$ ，有 $x=\sum_{i|x}\phi(i)$ ，证明略。

对原式进行变形。

$\sum_{i=1}^n\sum_{j=1}^n \gcd(i,j)\cdot \gcd(a_i,a_j)$

$=\sum_{i=1}^n\sum_{j=1}^n \sum_{x|i}\sum_{x|j}\phi(x)\cdot \gcd(a_i,a_j)$

$=\sum \phi(x)\sum_{i=1}^{n/x}\sum_{j=1}^{n/x}\gcd(a_{ix},a_{jx})$

考虑类根号分治。

注意到当 $x$ 比较大的时候，我们直接枚举 $i,j$ 计算，单次时间复杂度 $O(n^2 \log n/x^2)$ 。

当 $x$ 比较小的时候就不能强行枚举了。这时，取出我们需要考虑的数字。这些数字应该是 $a_x,a_{2x}\dots a_{(n/x)x}$ 。记 $b_i=a_{ix},m=(n/x)$ ，显然数列 $b_i$ 有 $m$ 项。

那么我们需要求的就是： $\sum_{i=1}^m \sum_{j=1}^m \gcd(b_i,b_j)$ 。

继续变形 ：

$\sum_{i=1}^m \sum_{j=1}^m \gcd(b_i,b_j)$ 

$=\sum_{i=1}^m \sum_{j=1}^m \sum_{x|b_i}\sum_{x|b_j} \phi(x)$

$=\sum_{x=1}^{N}\phi(x)\cdot (\sum_{i=1}^{n}[x|b_i])^2$

那么，我们就把用之前取出的数字做 Dirichlet 前缀和就好了。用的是变式的形式。

复杂度分析：

记阈值为 $B$ ，大于 $B$ 时我们用方法 $1$ ，否则用方法 $2$ 。

方法 $1$ 的总耗时 

$T_1=\sum_{x=B}^n n^2\log n/x^2=n^2\log n\sum_{x=B}^n 1/x^2$ 

$=n^2\log n(1/B-1/n)=n^2\log n/B$ 。

方法 $2$ 的总耗时

$T_2=n\log n \log n$ 。

令 $T_1=T_2$ ，则 $B=\sqrt{n\log n/\log \log n}$

再令 $n=10^5$ ，可得 $B=651.92$ 。

后者常数过大，理论上 $B$ 应该更小些？不过实测 $B$ 从 $400$ 一直升到 $700$ 的过程中用时单调递减，这就很奇怪了。

本篇博客参考了 @周子衡 的题解，在此特别感谢。

---

## 作者：User_Authorized (赞：0)

## 题意
给定一个长度为 $n$ 的正整数数列 $a$，求

$$\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n} \gcd\left(a_i, a_j\right) \times \gcd\left(i, j\right)$$

（$1 \le n,a_i  \le 10^5$）。

## 题解
根据欧拉函数的性质，可以得出

$$n = \sum\limits_{d \mid n} \varphi(d)$$

该式也被称作欧拉反演。

下面开始化简算式

$$\begin{aligned}
& \sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n} \gcd\left(a_i, a_j\right) \times \gcd\left(i, j\right) \\

=& \sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n} \gcd\left(a_i, a_j\right) \times \sum\limits_{d \mid \gcd\left(i, j\right)} \varphi(d) \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n} \gcd\left(a_i, a_j\right) \left[d \mid \gcd\left(i, j\right)\right] \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{i = 1}^{n} \left[d \mid i\right]\sum\limits_{j = 1}^{n} \left[d \mid j\right]\gcd\left(a_i, a_j\right) \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{i = 1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j = 1}^{\lfloor\frac{n}{d}\rfloor} \gcd\left(a_{id}, a_{jd}\right) \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{i = 1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j = 1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{t \mid \gcd\left(a_{id}, a_{jd}\right)} \varphi(t) \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{t} \varphi(t) \sum\limits_{i = 1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j = 1}^{\lfloor\frac{n}{d}\rfloor}\left[t \mid \gcd\left(a_{id}, a_{jd}\right)\right] \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{t} \varphi(t) \sum\limits_{i = 1}^{\lfloor\frac{n}{d}\rfloor}\left[t \mid a_{id}\right]\sum\limits_{j = 1}^{\lfloor\frac{n}{d}\rfloor}\left[t \mid a_{jd}\right] \\

=& \sum\limits_{d = 1}^{n} \varphi(d) \sum\limits_{t} \varphi(t) \left(\sum\limits_{i = 1}^{\lfloor\frac{n}{d}\rfloor}\left[t \mid a_{id}\right]\right)^2 \\
\end{aligned}$$

我们先枚举 $d$ 和 $id$，复杂度为 $\mathcal{O}(n \ln n)$。如果我们在枚举 $t$ 时可以保证只枚举 $a_{id}$ 的因子，那么总复杂度为 $\mathcal{O}(n \ln n \max\limits_{i = 1}^{n} d(a_i))$，其中 $d(n) = \sum\limits_{i \mid n} 1$ 即 $n$ 的约数个数，可以通过本题。

## Code
```cpp
//Codeforces - 1575G
#include <bits/stdc++.h>

typedef long long valueType;
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
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % MOD;
}

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType size;
    bitset isPrime;
    container primeList, phi;
    ValueMatrix fact;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true), phi(_size_ + 1), fact(_size_ + 1) {
        phi[1] = 1;

        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                phi[i] = i - 1;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
                    phi[t] = phi[i] * iter;

                    break;
                } else {
                    phi[t] = phi[i] * (iter - 1);
                }
            }
        }

        for (valueType i = 1; i <= size; ++i) {
            for (valueType j = i; j <= size; j += i) {
                fact[j].push_back(i);
            }
        }
    }

    const container &Prime() const {
        return primeList;
    }

    valueType Phi(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return phi[x];
    }

    const container &Factor(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return fact[x];
    }
};

constexpr valueType V = 1e5 + 5;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    LineSieve const sieve(V);

    valueType N;

    std::cin >> N;

    ValueVector source(N + 1, 0);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> source[i];

    valueType ans = 0;
    ValueVector count(V, 0);

    for (valueType d = 1; d <= N; ++d) {
        for (valueType i = d; i <= N; i += d)
            for (auto const &iter: sieve.Factor(source[i]))
                ++count[iter];

        valueType sum = 0;

        for (valueType i = d; i <= N; i += d) {
            for (auto const &iter: sieve.Factor(source[i])) {
                if (count[iter] > 0) {
                    Inc(sum, mul(mul(count[iter], count[iter]), sieve.Phi(iter)));

                    count[iter] = 0;
                }
            }
        }

        Inc(ans, mul(sum, sieve.Phi(d)));
    }

    std::cout << ans << std::endl;


    return 0;
}
```

---

