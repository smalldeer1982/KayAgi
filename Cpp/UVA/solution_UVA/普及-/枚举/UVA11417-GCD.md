# GCD

## 题目描述

给定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 501$ 。

## 样例 #1

### 输入

```
10
100
500
0```

### 输出

```
67
13015
442011```

# 题解

## 作者：Mr_QwQ (赞：11)

第一反应：看起来是反演？……完了我不会

第二反应：格式没有那么复杂，看来好像可以前缀和跑一遍$O(n)$过的……

第三反应：让我看看数据范围……等等……

（现在恶意评分都这么嚣张了吗$QAQ$）

打个暴力直接过。~~又做完了一道紫题，全身都舒服了qwq~~
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,ans;
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
int main(){
    while(1){
        scanf("%d",&n);if(!n)return 0;
        ans=0;
        for(int i=1;i<n;i++)for(int j=i+1;j<=n;j++)ans+=gcd(i,j);
        cout<<ans<<endl;
    }
    return 0;
}
```
~~我才不会告诉你我gcd打挂了两次呢QnQ~~

---

## 作者：bovine__kebi (赞：8)

所以七倍经验的题我就不多说了，直接推式子,题目让我们求：  
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\gcd(i,j)$$
**法1**：暴力枚举
直接写gcd暴力卡过去，没什么好说的  

**法2**：习惯性的加一个$\sum$:  
$$\sum\limits_{d=1}^n\sum\limits_{i=1}^n\sum\limits_{j=1}^n[\gcd(i,j)=d]$$
把d提出来：  
$$\sum\limits_{d=1}^nd\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(i,j)=1]$$
后面那一坨直接反演：  
$$\sum\limits_{d=1}^nd\sum\limits_{k=1}^{\lfloor\frac{n}{k}\rfloor}\mu(k)·\lfloor\dfrac{n}{dk}\rfloor^{2}$$
直接线性筛莫比乌斯函数+整除分块轻松水过，时间复杂度为
$O(n^{3/4})$省去了很多复杂度，可以轻松过。

**法3**：莫比乌斯反演的经典套路优化：  
令$m=dk$，带进原式,换过来得
$$\sum\limits_{m=1}^n\lfloor\dfrac{n}{m}\rfloor^{2}\sum\limits_{d|m}d·\mu(\dfrac{m}{d})$$
看起来没什么用，但是，我们仔细分析一下后面那一坨东西，因为$\mu(x)·\small\text{（这里指狄雷克雷卷积）}x=\phi(x)$（函数的特征）,后面可以直接替换掉（~~太神奇啦~~）
$$\sum\limits_{m=1}^n\lfloor\dfrac{n}{m}\rfloor^{2}\varphi(m)$$
复杂度就变成了$O(n^{1/2})$

**法4**：不会莫比乌斯反演的萌新们看过来啦：  
从新审视一下$\gcd$，我们发现对于所有的$\gcd(i,j)=1$,则有$\gcd(ik,jk)=k$，所以$gcd=k$的次数为：
$$2·\sum\limits_{i=1}^{\lfloor\frac{n}{k}\rfloor}\varphi(i)-1$$
原因是$gcd(x,y)$和$gcd(y,x)$是相等的，所以只用算到一半然后两倍，重复的部分减一，所以原来的式子可以变成： 
$$\sum\limits_{i=1}^ni·(2·\sum\limits_{j=1}^{\lfloor\frac{n}{i}\rfloor}\varphi(i)-1)$$
然后就很好做了，可以直接线性筛欧拉函数然后做前缀和，于是$O(n)$的复杂度就能做出来了

**法5**：关于法3的另一种推法,也不会用到莫比乌斯反演：
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{d|\gcd(i,j)}\varphi(d)$$
变换一下
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{d|i\;d|j}\varphi(d)$$
直接提出来
$$\sum\limits_{d=1}^n\varphi(d)\sum\limits_{i=1}^n\sum\limits_{j=1}^n[d|i][d|j]$$
分进去就成了
$$\sum\limits_{d=1}^n\varphi(d)\lfloor\dfrac{n}{d}\rfloor^{2}$$
就是法3的那个式子

我觉得就这几种做法了，代码太丑了就不放了，我只是提供思路的。

**update：**  
2020-4-30 修改了两个小bug,以及换$\phi$为$\varphi$

---

## 作者：cz666 (赞：2)

我看到好多同学都是写莫比乌斯反演的~~（写暴力其实也能因为数据水而通过此题）~~，我来交一发用欧拉函数求出 $ gcd $ 的题解 $ QwQ $ 。

由于这道题有好多的重题，所以我就只贴上A掉此题的代码~~（代码中有解释）~~，各位不要介意。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=503;
int a[maxn+1],b[maxn+1],v[maxn+1];
int sz,n,p[maxn+1],fi[maxn+1];
inline void Eular(){//用素数互质关系来寻找欧拉函数
    for(register int i=2;i<=maxn;i++){
        if(!v[i]) p[++sz]=i,fi[i]=i-1;
        for(register int j=1;j<=sz && p[j]*i<=maxn;j++){
            v[p[j]*i]=1;
            if(i%p[j]==0){fi[i*p[j]]=fi[i]*p[j];break;}
            fi[i*p[j]]=fi[i]*(p[j]-1);
        }
    }
} 
//超级像欧拉筛，不错，时间复杂度和欧拉筛的确相等，只是收集答案公式不一样而已。 
signed main(){
	v[1]=1;Eular();//预处理以1~maxn作为基数的所有欧拉函数值 
    for(register int i=1;i<=maxn;i++)
     for(register int j=i*2;j<=maxn;j+=i) a[j]+=i*fi[j/i];
    for(register int i=1;i<=maxn;i++) b[i]=b[i-1]+a[i];
    while(scanf("%lld",&n)==1 && n) printf("%lld\n", b[n]);
	//O(1)回答此题的所有问题 
    return 0;
}
```


---

## 作者：decoqwq (赞：1)

莫比乌斯反演

这道题就是让你求$\sum_{d=1}^n\sum_{i=1}^{n}\sum_{j=1}^n(gcd(i,j)=d)$减去$\sum_{i=1}^ni$之后再除以$2$

把式子改为$\sum_{d=1}^n\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}(gcd(i,j)=1) $，求和的时候我们乘上$d$即可

然后就是莫比乌斯反演基本套路，后面那一截$\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}(gcd(i,j)=1)$就相当于$\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}\mu(k)\lfloor\frac{n}{id}\rfloor\lfloor\frac{n}{jd}\rfloor$

然后枚举$n$，后面整除分块，时间复杂度大概是$O(n\sqrt n)$？

我们先一次筛完$\mu$的前缀和，每次就可以$O(\sqrt n)$回答啦qwq
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mu[2010],prime[420],cnt,vis[2010],n,m;
void shai()
{
    mu[1]=1;
    for(int i=2;i<=505;i++)
    {
        if(!vis[i])
        {
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=505;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)
            {
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
        mu[i]+=mu[i-1];
    }
}
signed main()
{
    
    shai();
    while(cin>>n,n!=0)
    {
        m=n;
        long long ans=0;
        for(int i=1;i<=m;i++)
        {
            n=m;
            n/=i;
            for(int j=1;j<=n;j++)
            {
                int l=(n/(n/j));
                ans+=i*(mu[l]-mu[j-1])*(n/j)*(n/j);
                j=l;
            } 
        }
        ans-=(m*(m+1)/2);
        ans/=2;
        cout<<ans<<endl;
    }
}
```

---

## 作者：Huami360 (赞：1)

~~四倍经验~~

~~UVA11417 P2568 P2398 UVA11426~~



------------

~~反演是不可能反演的这辈子不可能反演的~~

我们枚举所有gcd $k$，求所有$gcd=k$的数对，记作$f(k)$，那么$ans=\sum_{i=1}^{n}(f(i)-1)*i$。为什么减1呢，观察题目，发现$j=i+1$，所以自己与自己的数对是不算的。

$f(k)$怎么求？

若$a,b$互质，则$gcd(ak,bk)=k$。

我们枚举$a,b$中较大的那个，记作$i$，那么另一个数就有$φ(i)$种可能，~~显然，~~$1≤i≤n/k$，所以$f(k)=\sum_{i=1}^{n/k}φ(i)$，用前缀和就行了。

时间复杂度$O(n)$

```cpp
#include <cstdio>
const int MAXN = 100010;
long long phi[MAXN], v[MAXN], prime[MAXN], cnt;
int n;
long long ans; 
int main(){
    phi[1] = 1;
    for(int i = 2; i <= 502; ++i){
       if(!v[i]){
         v[i] = i;
         phi[i] = i - 1;
         prime[++cnt] = i;
       }
       for(int j = 1; j <= cnt; ++j){
          if(prime[j] > v[i] || prime[j] * i > 502) break;
          v[i * prime[j]] = prime[j];
          phi[i * prime[j]] = phi[i] * ((i % prime[j]) ? prime[j] - 1 : prime[j]);
       }
    }
    for(int i = 2; i <= 502; ++i) phi[i] += phi[i - 1];
    while(233){
      scanf("%d", &n);
      if(!n) return 0;
      ans = 0;
      for(int i = 1; i <= n; ++i) ans += (phi[n / i] - 1) * i;
      printf("%lld\n", ans);
    }
    return 0;
}

```

---

## 作者：封禁用户 (赞：0)

## 背景
发现双倍经验，看了下题目，印象中可以用莫比乌斯水过，发现真的可以用诶，开心qwq。

关于莫比乌斯反演[点我点我](http://www.cinema000.xyz/1082.ruby)

三倍经验：[UVa11417](https://www.luogu.org/problemnew/show/UVA11417)，[UVa11426](https://www.luogu.org/problemnew/show/UVA11426)，[Luogu1390](https://www.luogu.org/problemnew/show/P1390)
## 分析
本题就是求
$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}\gcd(i,j)$$
然后我们可以先求有重复元素的，然后减去重复的好了，这样方便套反演。
枚举最大公约数$d$然后转化成可以分块的形式（准确的说应该是分块思想，公共乘积优化），
$$\begin{aligned}\sum_{i = 1}^n\sum_{j = 1}^m\gcd(i, j)& = \sum_{d = 1}^nd\sum_{i = 1}^n\sum_{j = 1}^m[\gcd(i, j) = d]\\& = \sum_{d = 1}^nd\sum_{x=1}^{\left\lfloor\frac n d\right\rfloor}\mu(x)\left\lfloor\frac n {dx}\right\rfloor\left\lfloor\frac m {dx}\right\rfloor\end{aligned}$$
套分块$O((\sqrt(n)^2)=O(n)$，当然计算过程中溢出了，懒得优化什么的了，直接上了$int128$，应用$double$或高精吧。
```cpp
#include<cstdio>
#include<algorithm>
using std::fill;using std::swap;
typedef unsigned long long int64;
typedef __int128 int128;
const int MAXN = 1000 + 6;
int primes[MAXN],mu[MAXN],sum[MAXN],num;
bool isPrime[MAXN];
inline int min(int a,int b){return a < b ? a : b;}
void sieve(){
	fill(isPrime,isPrime + MAXN,true);
	num = 0,mu[1] = 1;
	for(int i = 2;i < MAXN;++i){
		if(isPrime[i]) primes[num++] = i,mu[i] = -1;
		static int d;
		for(int j = 0;j < num && (d = i * primes[j]) < MAXN;++j){
			isPrime[d] = false;
			if(i % primes[j] == 0){
				mu[d] = 0;break;
			}else mu[d] = -mu[i];
		}
	}
	sum[0] = 0;
	for(int i = 1;i < MAXN;i++) sum[i] = sum[i - 1] + mu[i];
}

int64 f(int n,int m,int d){
	if(n > m) swap(n,m);
	int64 ans = 0;
	n /= d,m /= d;
	for(int i = 1,last = 1;i <= n;i = last + 1){
		last = min(n / (n / i),m / (m / i));
		ans += (int128)((sum[last] - sum[i - 1]) * (int128)(n / i) * (int128)(m / i));
	}
	return ans;
}

int main(){
	sieve();
	int64 n,ans;
	while(scanf("%llu",&n) == 1 && n){
		ans = 0;
		for(int d = 1;d <= n;d++) ans += d * f(n,n,d);
		printf("%llu\n",(ans - n * (n + 1) / 2) / 2);
	}
	
	return 0;
}
```

---

