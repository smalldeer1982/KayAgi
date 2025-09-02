# GCD - Extreme (I)

## 题目描述

给定   $n$，求
  $$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中   $\gcd(i,j)$ 指的是   $i$ 和   $j$ 的最大公约数。

## 说明/提示

对于   $100\%$ 的数据，  $1 < n < 2 \times 10^5+1$，最多  $2 \times 10^4$ 组数据。

## 样例 #1

### 输入

```
10
100
20000
0```

### 输出

```
67
13015
1153104356```

# 题解

## 作者：Fido_Puppy (赞：6)

## Problem

[UVA11424 GCD - Extreme (I)](https://www.luogu.com.cn/problem/UVA11424)

给定 $n$，求 $\sum_{i=1}^{i<n} \sum_{j=i+1}^{j\le n} gcd(i,j)$ 的值。

## Solution

首先，我们设：

$$f(n)=gcd(1,n)+gcd(2,n)+...+gcd(n-1,n)$$

$$s(n)=f(1)+f(2)+...+f(n)$$

显然 $s(n)$ 就是我们要求得答案。

而 $s(n)$ 得式子也很好推：

$$s(i)=s(i-1)+f(i)$$

所以我们只需要求出 $f(i)\ (1\le i \le n)$ 即可。

考虑每一个 $gcd(x,n)$ 都是 $n$ 的约数。

所以我们设 $g(i,n)$ 为对于所有的 $x\ (1\le x <n)$，$gcd(x,n)=i$ 的 $x$ 的个数。

明显，对于一个 $x$ 要满足 $gcd(x,n)=i$，则要满足 $gcd(x/i,n/i)=1$。

也就是说 $(x/i)$ 与 $(n/i)$ 互质，且 $x<n$。

所以我们可以愉快的推出：

$$g(i,n)=\varphi(n/i)$$

接着就是求 $f(i)$ 啦！

首先我们可以考虑到对于每一个 $i\ (1 \le i \le n)$，可以枚举 $i$ 的因数，可是时间复杂度会飙升到 $O(n \sqrt{n})$，显然过不了。

于是我们可以采取逆向思维，枚举因数 $i$，对于每一个 $i$，枚举比它大的倍数 $2\times i,3\times i,4\times i...$

这个做法和埃氏筛很像，时间复杂度 $O(n\ log\ log \ n)$。

## Code

~~好像挺短的。~~

```cpp
#include<iostream>
using namespace std;
const int N=4000010;
typedef long long LL;
LL phi[N],x,f[N],s[N];
void phi_table(int n) {
	for(int i=2;i<=n;i++) phi[i]=0;
	phi[1]=1;
	for(int i=2;i<=n;i++)
		if (!phi[i])
			for(int j=i;j<=n;j+=i) {
				if (!phi[j]) phi[j]=j;
				phi[j]=phi[j]/i*(i-1);
			}
}
int main() {
	phi_table(4000000);
	for(int i=1;i<=4000000;i++)
		for(int n=i*2;n<=4000000;n+=i) f[n]+=i*phi[n/i];
	s[2]=f[2];
	for(int i=3;i<=4000000;i++) s[i]=s[i-1]+f[i];
	while (cin>>x&&x) {
		cout<<s[x]<<endl;
	}
	return 0;
}
```

完结撒花！ \ ^.^ /

---

## 作者：EuphoricStar (赞：6)

设 $f(n)=\gcd(1,n)+\gcd(2,n)+\gcd(3,n)+...+\gcd(n-1,n)$，

则所求答案为 $S(n)=f(2)+f(3)+...+f(n)$。

只需求出 $f(n)$，就可以递推出所有答案：$S(n)=S(n-1)+f(n)$。

因此，本题的重点在于如何计算 $f(n)$。
****
注意到所有 $\gcd(x,n)$ 都是 $n$ 的约数，可以按照这个约数进行分类，

用 $g(n,i)$ 表示满足 $\gcd(x,n)=i$ 且 $x<n$ 的正整数 $x$ 的个数，

则 $f(n)=sum\{i \times g(n,i)\}$（$i$ 是 $n$ 的约数）。

注意到 $\gcd(x,n)=i$ 的充要条件是 $\gcd(x/i,\,n/i)=1$，

因此满足条件的 $x/i$ 有 $\varphi(n/i)$ 个，

说明 $g(n,i)=\varphi(n/i)$。
****
问题到这里还没有结束。如果依次计算 $f(n)$，需要对每个 $n$ 枚举它的约数 $i$，速度较慢。

但如果把思路逆转过来，对于每个 $i$ 枚举它的倍数 $n$（并且更新 $f(n)$ 的值），时间复杂度将降为与素数筛法同阶。

至此问题得到了完整的解决。
****
AC 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, maxn = 4000000;
ll s[4000400], f[4000400], phi[4000400];

int main()
{
    phi[1] = 1;
    for (int i = 2; i <= maxn; ++i) if (!phi[i])
        for (int j = i; j <= maxn; j += i)
        {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
    for (int i = 1; i <= maxn; ++i)
        for (int j = i * 2; j <= maxn; j += i) f[j] += i * phi[j / i];
    s[2] = f[2];
    for (int i = 3; i <= maxn; ++i) s[i] = s[i - 1] + f[i];
    while (scanf("%d", &n) == 1 && n) printf("%lld\n", s[n]);
    return 0;
}
```


---

## 作者：向noip冲刺 (赞：6)

(这个题的预处理还是比较神奇的,我没想出来..)  
显然这个题的特点是,n很小,组数却很大,我们想如何预处理.  
首先理解题目在干吗,让我们求出$\sum_{i = 1}^{n -1}\sum_{j = i + 1}^{n}GCD(i,j)$     
套路的做   
先算出   
$GCD(i,j) == x$的数量   
转而求   
$GCD(i/x,j/x) == 1$     
然后就到了预处理的阶段了
这个题的核心思想在于我们枚举每个因数对于不同n的贡献      
枚举因子
$\sum_{i=1}^{n}\sum_{i+1}^{n}GCD(i,j) == x$  的贡献         
  $phi[n/x]$
显然这样时间复杂度还是不过关的.($O(n^2)$)我们考虑什么时候因子x会加贡献,当n为x的倍数的时候就又会产生贡献.   
像这样
```cpp
for(int i = 1;i < maxN;++ i) {
		for(int j = i + i;j < maxN;j += i) {
			f[j] += i * phi[j / i];
		}
	}
```
然而我们求出的f数组是$\sum_{1}^{n - 1} GCD(i,n)$然后造一个前缀和就好了.      
CODE:
```cpp
#include <iostream>
#include <cstdio>
const int maxN = 200000 + 7;

int phi[maxN];
bool vis[maxN];
int prime[maxN];
int sum[maxN];
long long int f[maxN];

void init() {
	int num = 0;
	vis[1] = 1;
    phi[1] = 1;
    for(int i = 2;i < maxN;++ i) {
        if( !vis[i] ) {
            prime[++ num] = i;
            phi[i] = i - 1;
        }
        for(int j = 1;j <= num && prime[j] * i < maxN;++ j) {
            vis[i * prime[j]] = true;
            if(i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] =  phi[i] *( prime[j] - 1);
        }
    }   
}

int main() {
	init();
	int fuck = 1;
	for(int i = 1;i < maxN;++ i) {
		for(int j = i + i;j < maxN;j += i) {
			f[j] += i * phi[j / i];
		}
	}
	for(int i = 1;i < maxN;++ i) {
		f[i] += f[i - 1];
	}
	while(fuck) {
		int n;
		scanf("%d",&n) ;
		if(!n) break;
		std::cout << f[n] << '\n';
	} 
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：4)

### 题面

$$
\texttt{求}G(n)=\sum\limits_{i=1}^{i<n}\sum\limits_{j=i+1}^{j\leq n}\gcd(i,j)
$$

$20000$ 组数据，$n$ 范围 $200000$。

### 前置知识

$$
\varphi\texttt{，欧拉函数，欧拉筛素数}
$$

$$
\texttt{前缀和}
$$

### 思路

$$
G(n)=\sum\limits_{i=1}^{i<n}\sum\limits_{j=i+1}^{j\leq n}\gcd(i,j)
$$

$$
G(n)=\sum\limits_{j=2}^{j\leq n}\sum\limits_{i=1}^{i<j}\gcd(i,j)
$$

$$
G(n)=G(n-1)+\sum\limits_{i=1}^{i<n}\gcd(i,n)
$$

$$
preG(n)=\sum\limits_{i=1}^{i<n}\gcd(i,n)\texttt{,最后把preG做一个前缀和就是G}
$$

$$
preG(n)=\sum\limits_{k=1}^{k<n}k\times\sum\limits_{\gcd(i,n)=k}^{i<n}1
$$

$$
preG(n)=\sum\limits_{k=1}^{k<n}k\times\sum\limits_{\gcd(i,\frac{n}{k})=1}^{i<\frac{n}{k}}1
$$

$$
preG(n)=\sum\limits_{k=1}^{k<n}k\times\varphi(\frac{n}{k})
$$

倒数第三个式子有$\gcd(i,n)=k$，显然有约束：$k|n$。

所以倒过来算：$\forall i$，$\varphi(i)$对 $preG(ik)$ 有贡献 $k\times\varphi(i)$。

枚举 $k$。因为 $ik\leq n$，所以时间复杂度为调和级数 $O(nlg_n)$。

别忘了前缀和！

### $code$

```cpp
#include<stdio.h>
#define N 200001
inline void read(int&x)
{
	register char c=getchar();for(;c<'0'||'9'<c;c=getchar());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());
}
int n,primes[100000],m,phi[N];bool np[N];long long sum[N],g[N];
main()
{
	for(register int i=2;i<=N;++i)//欧拉筛求phi模板
	{
		if(!np[i])
		{
			primes[m++]=i;
			phi[i]=i-1;
		}
		for(register int j=0;j<m&&i*primes[j]<N;++j)
			if(i%primes[j])phi[i*primes[j]]=phi[i]*(primes[j]-1),np[i*primes[j]]=1;
			else{phi[i*primes[j]]=phi[i]*primes[j];np[i*primes[j]]=1;break;}
	}
	for(register int i=1;i<N;++i)for(register int k=1;k*i<N;++k)g[k*i]+=k*phi[i];//计算phi(i)对preG的贡献
	for(register int i=1;i<N;++i)g[i]+=g[i-1];//通过preG计算G
	for(;read(n),n;printf("%lld\n",g[n]));//
}
```



---

## 作者：Daidly (赞：2)

$$\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)$$

$$\frac{\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)-\frac{n(n+1)}{2}}{2}$$

先求：

$$\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)$$

枚举 $\gcd$：

$$\sum_{d=1}^n\sum_{i=1}^n\sum_{j=1}^nd[\gcd(i,j)=d]$$

用 $di,dj$ 替换 $i,j$：

$$\sum_{d=1}^n\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}d[\gcd(i,j)=1]$$

将 $d$ 提前：

$$\sum_{d=1}^nd\left(\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(i,j)=1]\right)$$

将 $[\gcd(i,j)=1]$ 替换乘元函数 $\varepsilon(\gcd(i,j))$：

$$\sum_{d=1}^nd\left(\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}\varepsilon(\gcd(i,j))\right)$$

由于 $\varepsilon* 1=\mu$ 得：

$$\sum_{d=1}^nd\left(\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{k|i,k|j}\mu(k)\right)$$

枚举 $k$，对于每个 $k$ 统计计算次数：

$$\sum_{d=1}^nd\left(\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}\lfloor\frac{n}{dk}\rfloor^2\mu(k)\right)$$

设 $T=dk$，枚举 $T$，则 $d|T$：

$$\sum_{T=1}^n\sum_{d|T}^{n}d\lfloor\frac{n}{T}\rfloor^2\mu(\frac{T}{d})$$

交换顺序：

$$\sum_{T=1}^n\lfloor\frac{n}{T}\rfloor^2\left(\sum_{d|T}^{n}\mu(\frac{T}{d})d\right)$$

由于 $\mu* I=\phi$：

$$\sum_{T=1}^n\lfloor\frac{n}{T}\rfloor^2\phi(T)$$

线性筛 $\phi$，整除分块，复杂度：$O(n+t\sqrt{n})$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=1e6+5;
int n,m,prime[MAXN],phi[MAXN],sum[MAXN],num,ans;
bool isprime[MAXN];

void getphi(int maxn){
	phi[1]=1;
	for(int i=2;i<=maxn;++i){
		if(!isprime[i]){
			prime[++num]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=num&&i*prime[j]<=maxn;++j){
			isprime[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
	for(int i=1;i<=maxn;++i){
		sum[i]=sum[i-1]+phi[i];
	}
}

signed main(){
	getphi(1e6);
	while(1){
		n=read();
		if(!n)break;
		ans=0;
		for(int l=1,r;l<=n;l=r+1){
			r=n/(n/l);
			ans+=(sum[r]-sum[l-1])*(n/l)*(n/l);
		}
		ans-=n*(n+1)>>1;
		ans>>=1;
		print(ans),puts("");
	}
	return 0;
}
```

---

## 作者：云浅知处 (赞：2)

我们考虑递推地预处理答案。记 

$$
f(n)=\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)
$$

那么有

$$
f(n)-f(n-1)=\sum_{i=1}^{n-1}\gcd(i,n)
$$

记

$$
g(n)=\sum_{i=1}^{n}\gcd(i,n)
$$

枚举 $\gcd$

$$
\sum_{d|n}d\cdot\sum_{i=1}^n[\gcd(i,n)=d]
$$

注意到 $\gcd(i,n)=d\iff\gcd(i/d,n/d)=1,d|i,d|n$，因此上式即

$$
\sum_{d|n}d\cdot\sum_{d|i}[\gcd(i/d,n/d)=1]
$$

即

$$
\sum_{d|n}d\cdot\sum_{i=1}^{n/d}[\gcd(i,n/d)=1]
$$

注意到 $\sum\limits_{i=1}^{n/d}[\gcd(i,n/d)=1]=\varphi(n/d)$，因此上式化为

$$
\sum_{d|n}d\cdot\varphi(n/d)
$$

注意到这个东西就是 $\varphi * \text{Id}$，因此这也是一个积性函数，可以线性筛。

所以我们就做到了 $O(n)$ 的预处理。每次询问 $O(1)$ 输出即可。

时间复杂度为 $O(n+T)$。

不过 $n$ 只有 $4\times 10^6$，而且严格 $O(n)$ 的线性筛我写挂了没调出来，所以我并没有写严格 $O(n)$ 的线性筛（

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>

#define int long long
const int MN=4e6+6;

using namespace std;

int pri[MN],phi[MN],ans[MN],g[MN],f[MN],pi[MN];
bool vis[MN];

int ksm(int y,int z){
    int ans=1;
    for(int i=z;i;i>>=1,y=y*y)if(i&1)ans=ans*y;
    return ans;
}

int cnt=0;
void Pre(){
    vis[1]=1,phi[1]=1,g[1]=1;
    for(int i=2;i<MN;i++){
        if(!vis[i])pri[++cnt]=i,phi[i]=i-1,g[i]=2*i-1;
        for(int j=1;j<=cnt;j++){
            int id=i*pri[j];
            if(id>=MN)break;
            vis[id]=1;
            if(i%pri[j]==0){
                pi[id]=i;
                phi[id]=phi[i]*pri[j];
                int x=i,num=0;
                while(x%pri[j]==0)x/=pri[j],num++;
                g[id]=g[i]*pri[j]+ksm(pri[j],num)*(pri[j]-1)*g[x];
                break;
            }
            phi[id]=phi[i]*(pri[j]-1);
            g[id]=g[i]*g[pri[j]];
        }
    }
}

void init(){
    ans[1]=0;
    for(int i=2;i<MN;i++)ans[i]=ans[i-1]+g[i]-i;
}

signed main(void){

    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    Pre();
    init();

    int n;cin>>n;
    while(n!=0){
        cout<<ans[n]<<'\n';
        cin>>n;
    }

    return 0;
}
```

---

## 作者：zhimao (赞：2)

为啥大家都不莫反 ， 虽然我的方法挺慢 。

于是我们先推式子 ：
$$\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(i,j)$$
$$=\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d=1}^{\min(i,j)}d \,[\gcd(i,j)=1]$$
$$=\sum_{d=1}^{n}d\sum_{i=1}^{i\times d\le n}\sum_{j=1}^{j\times d\le n}[\gcd(i,j)=1]$$
$$=\sum_{d=1}^{n}d\sum_{i=1}^{i\times d\le n}\sum_{j=1}^{j\times d\le n}\sum_{k|\gcd(i,j)}\mu(k)$$
$$=\sum_{d=1}^{n}d\sum_{k=1}^{k\times d\le n}\mu(k)\sum_{i=1}^{i\times d\times k\le n}\sum_{j=1}^{j\times d\times k\le n}1$$
$$=\sum_{d=1}^{n}d\sum_{k=1}^{k\times d\le n}\mu(k) \left\lfloor\dfrac{n}{k\times d}\right\rfloor^2$$

此时筛出 $\mu$ 函数 ， 枚举 $d$ ， 对后面进行整除分块 ， 则可做到 $O(Tn\sqrt{n})$ 。 但它太慢了~~却可以跑过UVA11424 GCD - Extreme (II)~~ ， 我们考虑优化 。

记 $m=\left\lfloor\dfrac{n}{d}\right\rfloor$ ， 则有
$$\sum_{d=1}^{n}d\sum_{k=1}^{k\times d\le n}\mu(k) \left\lfloor\dfrac{n}{k\times d}\right\rfloor^2$$
$$=\sum_{d=1}^{n}d\sum_{k=1}^{m}\mu(k) \left\lfloor\dfrac{m}{k}\right\rfloor^2$$

我们发现：后面部分在 $m$ 已知的情况下与 $d$ 无关 。因此我们可以预处理出来 ， 记 $f(x)=\sum\limits_{k=1}^{x}\mu(k) \left\lfloor\dfrac{x}{k}\right\rfloor^2$ ， 则
$$\sum_{d=1}^{n}d\sum_{k=1}^{m}\mu(k) \left\lfloor\dfrac{m}{k}\right\rfloor^2$$
$$=\sum_{d=1}^{n}d\times f(m)$$

又可以整除分块 ， 则时间复杂度降为 $O((T+n)\sqrt{n})$
 。 不过由于整除分块的常数特别大 ， 这样子我还是过不去~~大常数选手~~ ， 于是我们可以采用一种方法优化常数：把除法次数减小 ， 即把 $\left\lfloor\dfrac{n}{i}\right\rfloor$ 放进数组里 ， 以便之后直接调用 ， 具体实现可以看我代码 。
 
 这样子我们就 AC 了 。
 
 ```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,ans,p,miu[10000005],bo[10000005],pri[10000005],f[10000000],cnt,srn,v[1000];
void xxs(int n)
{
	miu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!bo[i])
		{
			bo[i]=0;
			pri[++q]=i;
			miu[i]=-1;
		}
		for(int j=1;j<=q&&pri[j]*i<=n;j++)
		{
			bo[i*pri[j]]=1;
			if(i%pri[j]==0) break;
			miu[i*pri[j]]=-miu[i];
		}
	}
	for(int i=1;i<=n;i++) miu[i]=miu[i-1]+miu[i];
}
signed main()
{
	xxs(200001);
	for(int i=1;i<=200001;++i)
	{
		int srn=sqrt(i),cnt=(srn<<1)-(srn*(srn+1)>i);
		for(int j=1;j<=srn;++j) v[j]=j,v[cnt-j+1]=i/j;/、预处理除法
		for(int k=1,j=cnt;k<=cnt;++k,--j) f[i]+=v[k]*v[k]*(miu[v[j]]-miu[v[j-1]]);
	}
    do
    {
		scanf("%lld",&n);
		if(n==0) return 0;
		ans=0;
		for(int l=1,r;l<=n;l=r+1)
		{
			r=n/(n/l);
			ans=ans+(f[n/l]-1)*(l+r)*(r-l+1)/2;
		}//太鸽了 ， 这里不预处理了
		printf("%lld\n",ans/2);
    }
	while(1);
}
```


---

## 作者：lahlah (赞：2)

### [听说在blog体验更佳哦](https://blog.csdn.net/qq_38944163/article/details/83756739)


先别急着打莫比乌斯反演，这题有更简单的做法，可以先设

$f(n) = gcd(1, n) + gcd(2, n) + gcd(3, n) + ... + gcd(n-1, n)$

答案

$S(n) = f(2) + f(3) + ... + f(n)$

我们首先考虑如何求$f(n)$

我们可以先把$gcd(x, n)$的值分类，我们发现$gcd(x, n)$肯定是n的约数，再设$g(n, x)$表示$gcd(x, n) = i$的小于$n$的正整数的个数，

显然

$f(n) =$
$\sum _{i|n} i * g(n, i)$

可以注意到$[gcd(x, n) = i]$       $  -> $            $[gcd(x/i, n/i)== 1]$, 和 $n / i $互质的数的个数即为$\phi(n/i)$个，然后这题就切掉了
```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int prime[N], phi[N], vis[N], sz;
void get_phi(){
	vis[1] = 1;
	for(int i = 2; i < N; i ++){
		if(!vis[i]){
			prime[++ sz] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= sz && prime[j] * i < N; j ++){
			vis[prime[j] * i] = 1;
			if(i % prime[j] == 0){
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
}//-------------------------------------------以上部分为线性筛质数和欧拉函数
long long n, f[N], s[N];
int main(){
	get_phi();
	for(int i = 1; i < N; i ++)
		for(int j = i * 2; j < N; j += i)
			f[j] += i * phi[j / i]; 
//-------------------------------------------------即算每个数i对i的倍数的贡献
	for(int i = 1; i < N; i ++) s[i] = s[i-1] + f[i];
//-------------------------------------------------s[i]即为答案
	while(scanf("%lld", &n) == 1 && n){
		printf("%lld\n", s[n]);//O(1)输出
	}	
	return 0;
}
```

好题啊……

GCD - Extreme  GCD - Extreme (I) GCD - Extreme (II) 可以用同一份代码A掉

---

## 作者：Dzhao (赞：1)

题意：给你 $T$ 组询问，每组询问包含一个 $n$，请你回答 $\sum_{i=1}^n {\sum_{j=i+1}^n \gcd(i,j)}$。

题解：对于只询问一次，我们可以这样做

$\sum_{i=1}^n {\sum_{j=i+1}^n \gcd(i,j)}$

$=\sum_{k=1}^n k\times{\sum_{i=1}^n {\sum_{j=i+1}^n [\gcd(i,j)=k]}}$

$=\sum_{k=1}^n k\times{\sum_{i=1}^n {\sum_{j=i+1}^n [\gcd(i/k,j/k)=1](k|i,k|j)}}$

$=\sum_{k=1}^n k\times{\sum_{i=1}^{\lfloor n/k\rfloor} {\sum_{j=i+1}^{\lfloor n/k\rfloor} [\gcd(i,j)=1]}}$

$=\sum_{k=1}^n k\times{\sum_{i=1}^{\lfloor n/k\rfloor} \varphi(i)}$

我们令 $\operatorname{g(n)}=\sum_{i=1}^n \varphi(i)$

则原式 $=\sum_{k=1}^n k\times \operatorname{g}(\lfloor n/k \rfloor)$

这样对于每个询问回答的时间复杂度是 $O(n)$ 的，所以总复杂度为 $O(Tn)$，显然是超时的，所以我们得找方法优化。

我们发现许多 $\lfloor n/k \rfloor$ 是相同的，所以我们可以使用**整除分块**，将每一段的答案直接统计，设 $[l,r]$ 的$\lfloor n/l \rfloor$ 相同，所以，$r=\lfloor n/\lfloor n/l \rfloor \rfloor$。每一段答案就为 $(l+r)\times(r-l+1)/2\times \operatorname{g}(\lfloor n/l \rfloor)$，时间复杂度 $O(T\sqrt n)$。

$\mathcal{View\ Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int phi[N],n,v[N],prm[N],m;long long sum[N],ans; 

int main()
{
	v[0]=v[1]=1;
	for(int i=1;i<=200000;i++) //O(n)筛出每个数的 phi 值 
	{
		if(!v[i]) v[i]=i,prm[++m]=i,phi[i]=i-1;
		for(int j=1;j<=m;j++)
		{
			if(prm[j]>v[i] || prm[j]>200000/i) break;
			v[i*prm[j]]=prm[j];
			phi[i*prm[j]]=phi[i]*(i%prm[j]?prm[j]-1:prm[j]);
		}
	} 
	for(int i=1;i<=200000;i++) sum[i]=sum[i-1]+phi[i]; //预处理 phi 的值的前缀和 
	while(scanf("%d",&n),n)
	{
		int l,r;ans=0;
		for(l=1;l<=n;l=r+1) //整除分块 
			r=n/(n/l),ans+=1ll*(l+r)*(r-l+1)/2*sum[n/l]; 
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：demon_yao (赞：1)

### 前置芝士
$\varphi$,欧拉筛素数

### 思路
发现答案是求$ans=\sum\limits_{i=1}^{i<N}\sum\limits_{j=i+1}^{j<=N}GCD(i,j)$我们可以容易地想到，求前缀和可以节省大量时间，设答案数组为$sum[]$,那么我们就可以得住递推公式为$sum[n]=sum[n-1]+\sum\limits_{i=1}^{i<n}GCD(i,n)$；

在此同时我们设前缀和数组为$pre[]$,我们可以用这个公式算出前缀和$pre[n]=\sum\limits_{k=1}^{k<N}k*\varphi(\dfrac{n}{k})$ (为什么是这样，自己想一想就知到了)。

在算完$pre[]$后，我们把$pre[]$做一个前缀这就可以得到$sum[]$;这样我们就把这道题目做完了qwq！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+6;
int n;bool vis[N];
long long ans[N],pri[N],phi[N],cnt=0;
void calc(int n){
	phi[1]=0;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			phi[i]=i-1;pri[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*pri[j]<=n;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){int  tmp=i*pri[j];
				phi[tmp]=phi[i]*pri[j];
				break;
			}
			else {int  tmp=i*pri[j];
				phi[tmp]=phi[i]*(pri[j]-1);
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j*i<=n;j++){
			ans[j*i]+=j*phi[i];
		}
	for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
}
int main(){
	calc(2000001);
	while(cin>>n&&n!=0){printf("%lld\n",ans[n]);}
	return 0;
}

```


---

## 作者：翼德天尊 (赞：0)

## 题目大意

给定 $n$，求

$$\sum_{i=1}^n\sum_{j=i+1}^n\gcd(i,j)$$

## 解法讨论

首先看第二个循环很不顺眼，我想让他变成一个前缀和的形式，所以原式等价于

$$\sum_{i=1}^n\sum_{j=1}^{i-1}\gcd(i,j)$$

然后由于我们看到了 $\gcd$，很自然地就会联想到 $\varphi$ 函数。

------------

**注解：**$\varphi(n)$ 是一个积性函数，表示 $n$ 以内所有与 $n$ 互质的数的个数。可以通过线性筛在 $O(n)$ 时间内求出 $n$ 以内所有 $\varphi$ 的值。

------------

所以我们将原式变成含有条件判别式的形式：

$$\sum_{d=1}^nd\times\sum_{i=1}^n\sum_{j=1}^{i-1}[\gcd(i,j)=d]$$

将条件判别式内的条件变成等于 $1$：

$$\sum_{d=1}^nd\times\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{j=1}^{i-1}[\gcd(i,j)=1]$$

由于【互质】的定义就是当 $x$ 和 $y$ 互质时，$\gcd(x,y)=1$，所以我们发现后一个循环的值刚好就是 $\varphi(i)$，故我们可以将原式化为

$$\sum_{d=1}^nd\times \sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(i)$$

于是我们 $O(n)$ 预处理出所有 $\varphi(i)$ 的值，然后处理出 $n$ 以内所有关于 $\varphi$ 的前缀和，然后用整除分块处理每次询问的答案即可。

## 本题代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 4000000
ll n,zhi[N+5],ztot,phi[N+5];
bool izhi[N+5]; 
int read(){
	int w=0,f=1;
	char ch=getchar();
	while (ch>'9'||ch<'0'){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}
void init(){//线性筛求phi的前缀和
	izhi[1]=1;
	for (int i=2;i<=N;i++){
		if (!izhi[i]) zhi[++ztot]=i,phi[i]=i-1;
		for (int j=1;j<=ztot,i*zhi[j]<=N;j++){
			izhi[i*zhi[j]]=1;
			if (i%zhi[j]==0){
				phi[i*zhi[j]]=phi[i]*zhi[j];
				break;
			} 
			phi[i*zhi[j]]=phi[i]*phi[zhi[j]];
		}
	} 
	for (int i=1;i<=N;i++) phi[i]+=phi[i-1];
}
ll solve(int x){
	ll ans=0;
	for (ll l=1,r;l<=n;l=r+1){//整除分块
		r=x/(x/l);
		ans+=(r+l)*(r-l+1)/2*phi[x/l]; 
	}
	return ans;
}
int main(){
	init();
	while ((n=read())!=0){
		printf("%lld\n",solve(n));
	}
	return 0;
}
```


---

## 作者：Wuyanru (赞：0)

求：$ {\large\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n\gcd\left(i,j\right)} $

其实也就是 $ {\large\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd\left(i,j\right)} $

------------

### 首先考虑单次询问

首先枚举 $ i $ 与 $ j $ 两个数字再计算肯定是会超时的，我们不妨换个角度，来枚举 $ \gcd\left(i,j\right) $,再计算满足要求的 $ i $ 与 $ j $ 的个数。

不妨设 $ \gcd\left(i,j\right)=d $,

则 $ i=ad $,$ j=bd $,且 $ a $ 与 $ b $ 互质。

$ \because i<j $,

$ \therefore a<b $。

此时，如果确认 $ b $ 的值，则 $ a $ 的可选的数量就是小于 $ b $ 且与 $ b $ 互质的所有数，这不就是 $ \varphi\left(b\right) $ 吗？

$ \because ad=i<bd=j\le n $,

$ \therefore a<b\le{\large\left\lfloor\frac{n}{d}\right\rfloor} $。

$ \therefore ans_n={\large\sum\limits_{d=1}^n\sum\limits_{b=2}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi\left(b\right)\times d}={\large\sum\limits_{d=1}^n\sum\limits_{b=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi\left(b\right)\times d-\sum\limits_{i=1}^ni} $

其中 $ \varphi\left(b\right) $ 可以前缀和处理。

所以到这里，我们就解决了单组询问的问题。

[双倍经验](https://www.luogu.com.cn/problem/P1390)。

------------

### 然后考虑多组询问

在单组询问下，上述方法时间复杂度是可以接受的，但是本题是多组数据，时间复杂度瞬间炸裂。考虑提前预处理答案，再进行 $ \Theta\left(1\right) $ 回答。

不难发现 $ \forall i\in\left[1,n\right) j\in\left(i,n\right] $,都有 $ \gcd\left(i,j\right)\ge1 $。也就是说对于 $ n $ 的增加,$ ans_n $ 也会增加,$ ans_n $是 **单调递增的**。

不妨利用差分思想，求出每个 $ ans_i-ans_{i-1} $ 的值。

仔细观察上面得到的公式。

$$ ans_n={\large\sum\limits_{d=1}^n\sum\limits_{b=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi\left(b\right)\times d-\sum\limits_{i=1}^ni} $$

显然, $ \forall p>n $,$ \left\lfloor\frac{n}{p}\right\rfloor=0 $,也就是说有：

$$ ans_n={\large\sum\limits_{d=1}^\infty\sum\limits_{b=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi\left(b\right)\times d-\sum\limits_{i=1}^ni} $$

则：
$$ ans_i-ans_{i-1}={\large\sum\limits_{d=1}^\infty\sum\limits_{b=1}^{\left\lfloor\frac{i}{d}\right\rfloor}\varphi\left(b\right)\times d-\sum\limits_{d=1}^\infty\sum\limits_{b=1}^{\left\lfloor\frac{i-1}{d}\right\rfloor}\varphi\left(b\right)\times d-i} $$

$$ ={\large\sum\limits_{d=1}^\infty d\times\left(\sum\limits_{b=1}^{\left\lfloor\frac{i}{d}\right\rfloor}\varphi\left(b\right)-\sum\limits_{b=1}^{\left\lfloor\frac{i-1}{d}\right\rfloor}\varphi\left(b\right)\right)-i} $$

$$ ={\large\sum\limits_{d=1}^\infty \left(d\times\left[d\mid i\right]\times\varphi\left(\frac{i}{d}\right)\right)-i} $$

枚举 $ d $ 的值，再枚举倍数即可。

AC 代码：

```
#include<cstdio>
using namespace std;
long long ans[500001];
int mem[500001];
int num[500001];
int pr[500001];
int n=500000;
int main()
{
	for(int i=2;i<=n;i++)
	{
		if(mem[i]==0)
			pr[++pr[0]]=i;
		for(int j=1;j<=pr[0]&&i*pr[j]<=n;j++)
		{
			mem[i*pr[j]]=pr[j];
			if(i%pr[j]==0)
				break;
		}
	}
	for(int i=1;i<=n;i++)
		num[i]=i,ans[i]=-i;
	for(int i=1;i<=pr[0];i++)
		for(int j=1;pr[i]*j<=n;j++)
			num[pr[i]*j]=num[pr[i]*j]/pr[i]*(pr[i]-1);
	for(int d=1;d<=n;d++)
		for(int i=1;i*d<=n;i++)//枚举倍数
			ans[i*d]+=d*num[i];
	for(int i=2;i<=n;i++)
		ans[i]+=ans[i-1];
	scanf("%d",&n);
	while(n)
	{
		printf("%lld\n",ans[n]);
		scanf("%d",&n);
	}
	return 0;
}
```

感谢观看：

---

## 作者：_Scaley (赞：0)

## 题目介绍

有多组数据，每组数据给定一个整数 $N$，求

$$\sum^N_{i = 1} \sum^N_{j = i + 1}{\gcd(i, j)}$$

其中 $\gcd(i, j)$ 是整数 $i$ 和 $j$ 的最大公约数。

当 $N = 0$ 时结束程序。

**数据范围**

$n \in [1, ~2 \times 10^5 + 1]$

## 题目分析

先来了解一下前置芝士~~

**积性函数**

定义函数 $f$，

若 $i$ 和 $j$ 互质，且满足 $f(i \cdot j) = f(i) \cdot f(j)$，

则称函数 $f$ 为积性函数。

**欧拉函数**

以 $\phi$ 来表示，其中 $\phi(n)$ 的意思是：

$1 \to n$ 中的所有整数中有多少数和 $n$ 互质。

其中 $i$ 和 $j$ 互质是指 $\gcd(i, j) = 1$ 。

求法为：

$$\phi(n) = n \cdot (1 - \frac{1}{p_1})(1 - \frac{1}{p_2}) \cdots (1 - \frac{1}{p_k})$$

其中 $p_i$ 为 $n$ 的所有质因子。

已知欧拉函数是积性函数。

因此求 $n$ 的 $\phi$ 值时：

* 若 $n$ 是质数

$n$ 在 $1 \to n$ 中只能和 $n$ 不互质，

因此 $\phi$ 值为 $n - 1$ 。

* 若 $n$ 是合数

设 $t$ 是 $n$ 的倍数。

1. 若 $n$ 是一个质数的倍数

那么该数的倍数 $t$ 也是这个质数的倍数，由此可得出 $t$ 的 $\phi$ 值为 $n$ 的 $\phi$ 值与该质数的积。

2. 若 $n$ 不是一个质数的倍数

那么由积性函数的性质可知，$t$ 的 $\phi$ 值为 $n$ 的 $\phi$ 值与该质数的 $\phi$ 值的积

**线性筛**

线性筛可以用来筛质数、欧拉函数等等。

放代码来解释一下：

```cpp
void Shai(int n) {\\ 筛到整数 n
	Phi[1] = 1;\\ 定义数组 Phi 为欧拉函数值，1 的 Phi 值为 1
	for (int i = 2; i <= n; ++i) {
		if (!NotPrime[i]) { // 用 NotPrime 数组存储该数是否被访问过，若被访问过则是合数，没被访问过则是质数
			PrimeList[++cnt] = i;// 存下质数
			Phi[i] = i - 1; // 看上文
		}
		for (int j = 1, t; j <= cnt; ++j) {
			t = i * PrimeList[j];
			if (t > n) break;
			NotPrime[t] = true;// 标记
			if (!(i % PrimeList[j])) {
				Phi[t] = Phi[i] * PrimeList[j];
				break;// 线性筛的优化
			}
			else Phi[t] = Phi[i] * Phi[PrimeList[j]];
		}
	}
	for (int i = 1; i <= n; ++i) Phi[i] += Phi[i - 1];// 求所有 Phi 值的前缀和，便于下面的分块
}
``` 
---------------------

接下来就是愉快的推公式时间了~~

先算

$$\sum^N_{i = 1} \sum^N_{j = 1}{\gcd(i, j)}$$

可用 $id$ 函数来转化为

$$\sum^N_{i = 1} \sum^N_{j = 1}{id[\gcd(i, j)]}$$

接下来用等式 $\phi \ast I = id$ 可化为

$$\sum^N_{i = 1} \sum^N_{j = 1}\sum_{d \mid gcd(i,j)}{\phi(d) \ast I(\frac{N}{d})}$$

由 $I(n) = 1$ 可得

$$\sum^N_{i = 1} \sum^N_{j = 1}\sum_{d \mid gcd(i,j)}{\phi(d)}$$

把第三个 $\sum$ 提前，由于 $d$ 是 $i$ 和 $j$ 的最大公约数的因子，所以可以先枚举 $d$，再用 $i$ 和 $j$ 分别枚举原本公式 $i$ 和 $j$ 枚举过的次数

$$\sum^N_{d = 1} \sum^{\lfloor \frac{N}{d} \rfloor}_{i = 1}\sum^{\lfloor \frac{N}{d} \rfloor}_{j = 1}{\phi(d)}$$

我们可以看到 $i$ 和 $j$ 与后面的表达式没有关系，因此可以删去，就变成了

$$\sum^N_{d = 1} {\lfloor \frac{N}{d} \rfloor \lfloor \frac{N}{d} \rfloor{\phi(d)}}$$

公式到现在差不多化简完了，现在只需考虑怎么从

$$\sum^N_{i = 1} \sum^N_{j = 1}{\gcd(i, j)}$$

来推到

$$\sum^N_{i = 1} \sum^N_{j = i + 1}{\gcd(i, j)}$$

我们可以把枚举 $i = 1$ 和 $j = 1$ 看作是一个 $N \times N$ 的矩阵，

由此可知枚举  $i = 1$ 和 $j = i + 1$ 看做是这个矩阵的一半（不算对角线），

所以通过容斥原理可以把原式推成：

$$\sum^N_{i = 1} \sum^N_{j = i + 1}{\gcd(i, j)} = \frac{\sum^N_{i = 1} \sum^N_{j = 1}{\gcd(i, j)} - \frac{n \cdot (n + 1)}{2}}{2}$$

好啦，式子推完了，是时候进行愉快的代码时间啦~~

## 代码实现

```cpp
#include <bits/stdc++.h>
#define MAXN 1000010
#define int long long
using namespace std;
//---------------定义结构体---------------

//----------------定义变量----------------
int Phi[MAXN], NotPrime[MAXN], PrimeList[MAXN];
int cnt = 0;
//----------------定义函数----------------
inline int read() {
	int f = 0, x = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void Shai(int n) {// 线性筛，上文有讲解
	Phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!NotPrime[i]) {
			PrimeList[++cnt] = i;
			Phi[i] = i - 1;
		}
		for (int j = 1, t; j <= cnt; ++j) {
			t = i * PrimeList[j];
			if (t > n) break;
			NotPrime[t] = true;
			if (!(i % PrimeList[j])) {
				Phi[t] = Phi[i] * PrimeList[j];
				break;
			}
			else Phi[t] = Phi[i] * Phi[PrimeList[j]];
		}
	}
	for (int i = 1; i <= n; ++i) Phi[i] += Phi[i - 1];
}
//-----------------主函数-----------------
signed main() {
	int n, ans = 0;
	Shai(200010); // 多组数据，提前筛好
	while (1) {
		n = read();
		ans = 0;// 多测不清空，WA下两行泪
		if (n == 0) return 0;
		for (int i = 1, a, j; i <= n; i = j + 1) {
			a = n / i;
			j = n / a;// 分块优化
			ans += a * a * (Phi[j] - Phi[i - 1]);
		}
		ans = (ans - n * (n + 1) / 2) / 2;// 上面推出来的公式
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Suzt_ilymtics (赞：0)

[->更好的阅读体验](https://www.cnblogs.com/Silymtics/p/14730184.html)

## Description

> 求
> $$\sum_{i = 1}^{n} \sum_{j = i + 1}^{n} \gcd(i, j)$$


## Solution

莫反练习题。

我们知道 $id(n) = n$ ，所以原式化为：

$$\sum_{i = 1}^{n} \sum_{j = i + 1}^{n} id(\gcd(i,j))$$

又因为 $id = \varphi \ast I $， 那么：

$$
\begin{aligned}
id(n) 
& = \sum_{d \mid n} \varphi(d) \times I(\frac{n}{d}) \\
& = \sum_{d \mid n} \varphi(d)

\end{aligned}
$$

所以上式化为：

$$ \sum_{i = 1}^{n} \sum_{j = i + 1}^{n} \sum_{d \mid \gcd(i,j)} \varphi (d)$$

把 $d$ 提到前面去，$i,j$ 改为枚举 $d$ 的倍数。

$$ \sum_{d = 1}^{n} \sum_{i = 1}^{\left \lfloor \frac{n}{d} \right \rfloor} \sum_{j = i + 1}^{\left \lfloor \frac{n}{d} \right \rfloor}  \varphi (d)$$

后面的变量与后面两个 $\sum$ 中的变量无关，可以直接化掉。不同于其他大佬的做法，我们先把这两个 $\sum$ 拿出来，并设 $x = {\left \lfloor \frac{n}{d} \right \rfloor}$ 。两个 $\sum$ 变成：

$$\sum_{i = 1}^{x} \sum_{j = i + 1}^{x} 1 = \frac{x (x-1)}{2}$$

所以不用在减去重复的并除以 $2$，直接代回去可得：

$$\sum_{d = 1}^{n} \frac{x(x-1)}{2} \varphi(d)$$

枚举 $d$ 即可，复杂度 $O(n)$。

考虑到有多组数据，只是 $O(n)$ 的枚举还是会 T 掉，所以使用整除分块优化。

不会的话可以看一下这位大佬的博客 -> [整除分块](https://www.cnblogs.com/peng-ym/p/8661118.html)

整除分块的复杂度为 $O(\sqrt{n})$，总复杂度为 $O(T\sqrt{n})$，其中 $T$ 表示有 $T$ 组数据。

剩下的看代码吧。

## Code

```cpp
/*
Work by: Suzt_ilymics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 1e6+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

LL prim[MAXN], phi[MAXN], Cnt = 0, sum[MAXN];
bool vis[MAXN];

void Init(int limit) {
    phi[1] = 1, sum[1] = 1;
    for(int i = 2; i <= limit; ++i) { // 利用线性筛预处理欧拉函数
        if(!vis[i]) phi[i] = i - 1, prim[++ Cnt] = i;
        for(int j = 1; j <= Cnt && i * prim[j] <= limit; ++j) {
            vis[i * prim[j]] = true;
            if(i % prim[j] == 0) { phi[i * prim[j]] = phi[i] * prim[j]; break; }
            else phi[i * prim[j]] = phi[i] * phi[prim[j]];
        }
        sum[i] = sum[i - 1] + phi[i];
    }
}

int main()
{
    Init(200010);
    while(true) { // 多组询问
        int n = read();
        if(!n) return 0;
        LL ans = 0;
        for(int l = 1, r; l <= n; l = r + 1) { // 整除分块
            r = n / (n / l);
            LL x = n / l;
            ans += x * (x - 1) / 2 * (sum[r] - sum[l - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}


```

---

