# Natasha, Sasha and the Prefix Sums

## 题目描述

NaCly_Fish 最喜欢的数字是 $n$ 和 $1$；$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 最喜欢 $m$ 和 $-1$。

有一天，她们在一起写出了一个长度为 $n+m$，有 $n$ 个 $1$ 和 $m$ 个 $-1$ 的序列 $a$，定义其最大前缀和为： 
$$\large \max\{ 0,\max\limits_{1\le i\le n+m}\sum\limits_{j=1}^ia_j \}$$
换句话说，就是对于 $a$ 的前缀和的所有项和 $0$ 取 $\max$ 的值。

NaCly_Fish 想知道，对于全部可能的序列，它们的 最大前缀和 之和是多少。  
为了防止答案过大，要对 ${998244\textcolor{red}853}$ (是个质数) 取模。

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 只用 1s 就想到了做法，但是 NaCly_Fish 还不会，你能帮帮她吗？

## 说明/提示

【样例 $3$ 解释】  
可能的序列有 $6$ 种：  
$1,1,-1,-1$  
$1,-1,1,-1$  
$1,-1,-1,1$  
$-1,1,1,-1$  
$-1,1,-1,1$  
$-1,-1,1,1$  
它们的最大前缀和分别为 $2,1,1,1,0,0$，加起来答案为 $5$。

$0\le n,m \le 2000$

## 样例 #1

### 输入

```
0 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 2
```

### 输出

```
5
```

## 样例 #4

### 输入

```
2000 2000
```

### 输出

```
674532367
```

# 题解

## 作者：Sooke (赞：32)

### 题意

求所有只有 $n$ 个 $1$ 和 $m$ 个 $-1$ 的序列最大前缀和的总和。($n,\,m \leq 2000$)

---

### 解题思路

设 $f_i$ 为最大前缀和等于 $i$ 的序列数量，答案即为 $\sum\limits_{i=0}^{n}i \times f_i$ 。恰好等于 $i$ 比较难控制，不妨先求出 $g_i$ 为最大前缀和大于等于 $i$ 的序列数量，差分得到 $f_i$ 。或者粗暴一些：$\sum\limits_{i=0}^{n}i \times f_i = \sum\limits_{i=0}^n \sum\limits_{j=1}^{i} f_i = \sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}f_i = \sum\limits_{i=1}^{n} g_i$ 。

下一步我沿用了 [P1641 字符串生成](https://www.luogu.org/problem/P1641) 里的经典套路。将 $1$ 看成位移向量 $(1,\,1)$ ，$-1$ 看成位移向量 $(1,\,-1)$ ，显然所有序列一一对应了起点 $(0,\,0)$ 到终点 $(n + m,\,n - m)$ 的所有路径。

正如下图，是序列 $\{1,\,-1,\,1,\,1,\,-1,\,-1,\,-1,\,1\}$ 对应的一条路径：

![](https://i.loli.net/2019/08/22/mQzYcvd7aFPtx9D.png)

而最大前缀和大于等于 $i$ ，等价于路径要与一条 $y = i$ 的直线有交。乍一看毫无规律而无从下手，要是路径的起点和终点分别在直线的两侧，只要是合法的路径就一定与 $y = i$ 有交，直接组合数求出 $g_i = \binom{n+m}{n}$ 。

如果起点和终点在直线同侧怎么办？强行把起点移到另一边去！不妨设置新的起点 $(0,\,2i)$ ，此时我们观察它到 $(n + m,\,n - m)$ 的路径，因为在异侧，路径与 $y = i$ 一定有交。

接下来的转换将数形结合的精粹表现得淋漓尽致：我们找到路径与 $y = i$ 的第一个交点，将起点到交点这一部分的路径以 $y = i$ 为中心向下翻！这不，新的起点一时间又变到了老的起点，翻转之后的整条路径也是老的起点到终点的一条合法路径，但神奇的是，它一定与 $y = i$ 相交！

想想看，这样的翻转是不是可以把老的路径中与 $y = i$ 相交的一一对应到了新的路径？而数量也是一个组合数就能了结的。

放个图稍加体会：

![](https://i.loli.net/2019/08/22/CvVmTi5a6KXHlOS.png)

最后一步，$(0,\,2i)$ 到 $(n + m,\,n - m)$ 有多少合法路径？我们设上移了 $x$ 步，下移了 $y$ 步，列得：

$$\left\{\begin{aligned}x+y &= n + m - 0\\x-y &= n - m - 2i\end{aligned}\right.$$

故 $x = n - i,\ y = m + i$ 。$g_i = \binom{x+y}{x} = \binom{n+m}{n-i}$ 。

总结一下：

$$\left\{\begin{aligned}g_i &= \binom{n+m}{n} \quad (i \leq n - m) \\ g_i &= \binom{n+m}{n-i} \quad (i \geq n - m) \end{aligned}\right.$$

线性预处理阶乘及逆元，注意坑爹的模数，我们用 $O(n + m)$ 的复杂度完成了此题。

---

### 代码实现

惊了，现在题解不贴代码过不了审？？

```cpp
#include <bits/stdc++.h>

const int mod = 998244853;

inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int sub(int x, int y) { return x - y >= 0 ? x - y : x - y + mod; }
inline int power(int x, int y, int res = 1) {
    for (; y; y >>= 1, x = 1ll * x * x % mod) {
        if (y & 1) { res = 1ll * res * x % mod; }
    } return res;
}

const int N = 1e5 + 5;

int n, m, sx, sy, tx, ty, dx, dy, ans, f[N], fac[N], invf[N];

void initCombin(int n) {
    for (int i = fac[0] = 1; i <= n; i++) { fac[i] = 1ll * fac[i - 1] * i % mod; }
    invf[n] = power(fac[n], mod - 2);
    for (int i = n; i; i--) { invf[i - 1] = 1ll * invf[i] * i % mod; }
}

inline int binom(int n, int m) {
    if (n < m) { return 0; }
    return 1ll * fac[n] * invf[m] % mod * invf[n - m] % mod;
}

int main() {
    std::cin >> n >> m; initCombin(1e5);
    tx = n + m; ty = n - m;
    for (int i = 0; i <= n; i++) {
        sx = 0; sy = i + i;
        dx = tx - sx; dy = ty - sy;
        if (ty >= i) {
            f[i] = binom(n + m, n);
        } else {
            f[i] = binom(dx, (dx + dy) / 2);
        }
    }
    for (int i = 0; i <= n; i++) { ans = add(ans, 1ll * i * sub(f[i], f[i + 1]) % mod); }
    std::cout << ans << std::endl;
    return 0;
}
```

---

## 作者：lukelin (赞：10)

### 前言
更好的阅读体验? **[我的博客](https://www.cnblogs.com/linzhengmin/p/11391922.html)**    
本文中的排列指由n个1, m个-1构成的序列中的一种。  
题目这么长不吐槽了，但是这确实是一道好题。
### 题解
DP题话不多说，直接状态/变量/转移。
#### 状态
我们定义f表示"最大prefix sum"之和
#### 变量
f[i][j]为有i个1，j个-1的"最大prefix sum"之和
#### 转移
我们记C[i][j]为$\left(\begin{matrix}  i \\ j\end{matrix}\right)$，那么:
$$f[i][j] = \left\{\begin{matrix} f[i-1][j]+1 \times C[i+j-1][i-1] \\ f[i][j-1]+(-1)\times(C[i+j-1][j-1]-k[i][j-1])\end{matrix}\right.$$
k[i][j]表示有i个1，j个-1的最大前缀和刚好为0的排列的个数  
那么上式是如何推出的呢？  
我们固定地认为每当新加入一个数的时候将该数插入序列的最前方，这种设定仍然保证了动规涵盖所有珂能的排列。  
如果我们插入的是一个1，不管先前的序列排列如何，最大prefix sum一定会加1，由于i-1个1，j个-1对应的序列有$\left(\begin{matrix}  i+j-1 \\ i\end{matrix}\right)$种排列方法，所以当前状态增加的贡献为$\left(\begin{matrix}  i+j-1 \\ i\end{matrix}\right)$。  
如果我们插入的是一个-1，情况于上面是完全相同的，但是注意到，如果有一种排列它本身的"最大prefix sum"为0，那么我们不应当把它计入贡献(因为"最大prefix sum"最小为0)，所以要减去k[i][j]。  
组合数显然珂以通过杨辉三角递推解决。  
那么现在我们的问题就在于k[i][j]如何处理。  
我们先给出k[i][j]的递推式。  
$$k[i][j]=\left\{\begin{matrix}i=0 & k[i][j]=1 \\ j=0 & k[i][j]=0 \\ i > j & k[i][j]=0 \\ \text{其余情况} & k[i][j]=k[i-1][j]+k[i][j-1]\end{matrix}\right.$$  
这个递推式珂能有点晦涩，但是一种简单的理解方式是找出由当前状态向外转移的方程式，然后再转化为以上方程式。  
于是我们解决了此题。  
### 代码
没有卡常，见谅。  
```cpp
#include <cstdio>
#define MOD 998244853

long long f[2005][2005];
long long k[2005][2005];
long long C[4005][4005];

int main(){
    int n, m; scanf("%d %d", &n, &m);
    for (register int i = 0; i <= n; ++i)
        for (register int j = 0; j <= m; ++j){
            if (i == 0) k[i][j] = 1;
            else if (j == 0) k[i][j] = 0;
            else if (i > j) k[i][j] = 0;
            else k[i][j] = (k[i - 1][j] + k[i][j - 1]) % MOD;
        }
    C[0][0] = C[1][0] = C[1][1] = 1;
    for (register int i = 2; i <= n + m; ++i){
        C[i][0] = 1;
        for (register int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    for (register int i = 0; i <= n; ++i)
        f[i][0] = i, f[0][i] = 0;
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            f[i][j] = ((f[i - 1][j] + C[i + j - 1][i - 1]) % MOD + (f[i][j - 1] - C[i + j - 1][j - 1] + k[i][j - 1] + MOD) % MOD) % MOD;
    printf("%I64d", f[n][m]);
    return 0;
}
```

---

## 作者：Zimo_666 (赞：9)

## [CF1204E] Natasha, Sasha and the Prefix Sums

### 题意

一个长度为 $n+m$，有 $n$ 个 $1$ 和 $m$ 个 $-1$ 的序列 $a$，定义其最大前缀和为：$\large \max\{ 0,\max\limits_{1\le i\le n+m}\sum\limits_{j=1}^ia_j \}$。求算所有可能序列的最大前缀和。

### 分析

首先我们考虑一种计算总贡献的方法，首先我们有一种朴素的想法，即我们枚举状态 $s$ 时，求算 $\sum  f(s)$，但是这道题显然我们不能暴力枚举每种情况，我们考虑另外一种情况，若设某个序列的贡献为 $val$ 时，我们可以使用 $\sum cnt_{val}\times val$ 来求解。

对于这道题我们可以使用后者来求解，我们考虑前缀和区间以及题目中的定义，显然有 $val∈[\max(1,n-m),n)$。而后我们可以考虑使用类似 Catalan 数的方法进行求解，我们考虑把序列中的 $1$ 看做向右走，序列中的 $-1$ 看做向左走，则有最大前缀和为过程中坐标的最大值，则我们考虑一种 $f(k)$ 表示不向右越过 $k$ 的方案数，则有 $f(k)$ 表示最大前缀和**小于等于** $k$ 的方案数，显然我们有最大前缀和的方案数为 $f_k-f_{k-1}$。而后我们考虑单个 Catalan 序列的求解。

我们不考虑限制条件那么所有的操作方案数为 $C_{n+m}^m$。

而后我们考虑这个不越过 $k$ 的限制条件。显然有所有不合法操作都会抵达 $k+1$。那么我们把所有这一时刻后的不合法操作以 $k+1$ 为对称轴取反。则有最后我们经过一些操作，由原来的终点 $n-m$ 变为 $2(k+1)-n+m$。我们设向右走 $R$ 步且为正贡献 1，向左走 $L$ 步且为负贡献 1。则有二元一次方程组 $L+R=n+m,R-L=2(k+1)-n+m$。

那么我们解得 $L=n-k-1,R=m+k+1$。则有不合法路径数 $C_{n+m}^{m+k+1}$。

则有 $f(k)=C_{n+m}^{m}-C_{n+m}^{m+k+1}$。

我们考虑总贡献有 $Ans=\sum_{k=\max(1,n-m)}^{n}k \times (f(k)-f(k-1))$。

我们考虑使用快速幂+逆元求算组合数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int mod=998244853;
struct node{
  int inv[2000090],fac[2000090];
  int qpow(int shu,int cifang){
    int ans=1;int k=cifang;
    while(k){
      if(k&1){ans=ans*shu%mod;ans%=mod;shu=shu*shu%mod;shu%=mod;}
      else{shu=shu*shu%mod;shu%=mod;}
      k>>=1;
    }
    return ans%mod;
  }
  void init(int len){
    fac[0]=1;
    for(int i=1;i<=len;i++) fac[i]=fac[i-1]*i%mod;
    inv[len]=qpow(fac[len],mod-2);
    for(int i=len;i;i--){
      inv[i-1]=inv[i]*(i)%mod;
    }
  }
  int C(int n,int m){
    return fac[n]%mod*inv[m]%mod*inv[n-m]%mod;
  }
}lg_get;

int f(int n,int m,int k){
  int ans=lg_get.C(n+m,m)%mod-lg_get.C(n+m,m+k+1)%mod;
  ans+=mod,ans%=mod;
  return ans;
}
void solve(){
  scanf("%lld%lld",&n,&m);
  // int x=k,y=a;
  // int y=k,x=a;
  // x--,y--;
  // printf("%lld %lld\n",x,y);
  int ans=0;
  for(int kk=max(1ll,n-m);kk<=n;kk++){
  	// printf("%d\n",kk);
    int tmp=kk%mod*(f(n,m,kk)-f(n,m,kk-1))%mod;
    tmp%=mod;
    // printf("%lld\n",tmp);
    ans+=tmp;
    ans+=mod;
    ans%=mod;
  }
  printf("%lld\n",ans);
}
const int MAXN=1e6+7;
signed main(){
  lg_get.init(MAXN*2);
  // int T;
  // cin>>T;
  // while(T--) solve();
  solve();
}
```





---

## 作者：ljc20020730 (赞：5)

这里补一个$O(n+m)$的作法，对于该题，我们直接可以用组合数来求解。

设$f_i$为最大前缀和为$i$的不同序列的个数。

那么最后的答案就是$\sum\limits_{i=1}^{n}i \times f_i$

为了求出$f_i$，我们可以先求出一个$g_i$数组，

其中$g_i$表示最大前缀和大于等于$i$的不同序列个数。

那么对于任意$1 \leq i \leq n$ ，都有$f_i = g_i - g_{i-1}$

那么，如何求$g_i$，设当前放了$i$个$+1$，放了$j$个$-1$,对应在平面直角坐标系的点$(i,j)$，将一个序列看做从初始位空的$(0,0)$点走到最终状态的$(n,m)$点的一条路径。

对于最大前缀和至少为$i$的限制，就是强制这条路径必须经过直线$y = x-k$

那么，从$(0,0)$经过直线$y = x - k$再到达$(n,m)$的路径条数就是$g_k$的值。

我们可以将$(0,0)$点按照直线对称，变成$(k,-k)$，那么从$(k,-k)$走到$(n,m)$的路径条数就是所求。

这个值可以直接组合数来求，答案是$\binom{n-k+m+k}{n-k} = \binom{n+m}{n-k}$

即$g_k = \binom{n+m}{n-k}$.

请注意一个$g_i$的先决条件，就是如果无论如何当前序列如何构造，都能够使得最大前缀和大于等于$i$的情况下(即$k \leq n-m$时)，$g_i = \binom{n+m}{n}$。

吐槽一下模数我一直以为是$998244353$来着的....

$AC$代码：

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N=2e5+10,mo=998244853;
int s[N],inv[N],n,m;
int Pow(int x,int n)
{
	int ans = 1;
	while (n) {
		if (n&1) ans=ans*x%mo;
		x=x*x%mo;
		n>>=1;
	}
	return ans%mo;
}
int C(int n,int m) {
	if (m<0) return 0;
	return s[n]*inv[m]%mo*inv[n-m]%mo;
}
int g(int k) {
	if (k<=n-m) return C(n+m,n);
	else return C(n+m,n-k);
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	s[0]=1; for (int i=1;i<=n+m;i++) s[i]=s[i-1]*i%mo;
	inv[0]=1; for (int i=1;i<=n+m;i++) inv[i]=Pow(s[i],mo-2);
	int ret = 0;
	for (int i=1;i<=n;i++) 
		ret=(ret+i*(((g(i)-g(i+1)%mo+mo)%mo)%mo))%mo;
	printf("%lld\n",ret); 
	return 0;
}
```




---

## 作者：houzhiyuan (赞：5)

首先考虑将答案分解，令 $g_i$ 表示 $i\le f(a)$ 的序列 $a$ 的方案数。

那么

$$
ans=\sum_{i=1}^{n} g_i
$$

问题转化为算方案数。

将问题放到平面直角坐标系上，$1$ 就是向左上走一格，$-1$ 就是向右下走一格。

![](https://hydro.ac/file/613/QQ%E6%88%AA%E5%9B%BE20211026175050.png)

如图就是序列 $a={1,1,-1,1,1-1}$。

统计 $g_i$ 实际就是统计有多少条折线满足进过直线 $y=i$。

![](https://hydro.ac/file/613/QQ%E6%88%AA%E5%9B%BE20211026175445.png)

如图，经过红线的折线个数就是 $g_2$。

那么如何求呢？

![](https://hydro.ac/file/613/QQ%E6%88%AA%E5%9B%BE20211026175709.png)

如图，用求卡特兰数的套路，直接将第一次经过直线的点后面的部分轴对称即可。

注意特判 $n-m<i$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005,mod=998244853;
int jie[N],ni[N],ans,n,m;
int kuai(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
	return ans;
}
void work(int maxn){
	jie[0]=ni[0]=1;
	for(int i=1;i<=maxn;i++)jie[i]=1ll*jie[i-1]*i%mod;
	ni[maxn]=kuai(jie[maxn],mod-2);
	for(int i=maxn-1;i;i--)ni[i]=1ll*ni[i+1]*(i+1)%mod;
}
int C(int n,int m){return 1ll*jie[n]*ni[m]%mod*ni[n-m]%mod;}//组合数的预处理
int main(){
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	work(5000);
	if(n-m>0)ans=1ll*C(n+m,n)*(n-m)%mod;//特判情况
	for(int i=max(1,n-m+1);i<=n;i++)ans=(ans+C(n+m,n-i))%mod;//统计答案
	cout<<ans;
}
```

---

## 作者：LebronDurant (赞：3)

和[PKUSC2018]最大前缀和 基本是一道题。

f[i][j]表示i个1，j个-1组成的所有序列中最大前缀和等于i-j的有多少种

g[i][j]表示i个1，j个-1组成的所有序列中最大前缀和小于0的有多少种

转移 考虑这道题只有i>=j的f[i][j]有用，所以直接dp这些就好了，f[i+1][j]+=f[i][j],如果i>=j+1的话，f[i][j+1]+=f[i][j]

因为考虑第一个位置放1或-1的话，f[i][j]可以转移到f[i+1][j]和f[i][j+1]

同样的，只有i<j的g[i][j]有用，g[i][j]=g[i-1][j]+g[i][j-1]

考虑最后一个位置放1或-1，g[i][j]可以从g[i-1][j]和g[i][j-1]转移

最终答案是Σ(i-j) * f[i][j] * g[n-i][m-j]

对于每个前缀作为答案的话，后面的东西的最大前缀和一定要小于0，而前面要等于他本身的和，所以就是f[i][j] * g[n-i][m-j]

一定要注意！！！模数是998244853！而不是998244353！！！！！！！

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<deque>
#include<vector>
using namespace std;
typedef long long ll;
#define N 2000002
const ll p=998244853;
int n,m;
ll f[2002][2002],g[2002][2002];
int a[2002];
int main()
{
    scanf("%d%d",&n,&m);
    g[0][0]=1;
    for(int i=0;i<=m;i++)g[0][i]=1;
    f[1][0]=f[0][1]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(i-j<0)
            {
                g[i][j]=(g[i][j]+g[i-1][j])%p;
                g[i][j]=(g[i][j]+g[i][j-1])%p;
            }
        }
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(i>=j)
            {
                if(i+1>=j)f[i+1][j]=(f[i+1][j]+f[i][j])%p;
                if(i>=j+1)f[i][j+1]=(f[i][j+1]+f[i][j])%p;
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(i-j>=0&&i+j>0)ans+=1ll*(i-j)*f[i][j]%p*g[n-i][m-j]%p,ans%=p;
        }
    }
    printf("%lld\n",ans);
}
```


---

## 作者：MoyunAllgorithm (赞：2)

据说 CSP-S 前写题解会加 rp 哦。

本题的数据范围明显是为 $O(NM)$ 的做法准备的，但题解区存在大量更复杂的 $O(N+M)$ 解法，少量的 $O(NM)$ 解法缺少某些数组的推导。因此这是一篇新手友好的 $O(NM)$ 题解。

**题意**

给你 $N,M$，那存在许多个值域为 $\{1,-1\}$（注意是花括号不是区间！！）的序列，有 $N$ 个 $1$ 以及 $M$ 个 $-1$。定义一个这样的序列的权值是其前缀和数组最大的一项，若为负数则权值为 $0$，问所有这样的序列的权值和。

**分析**

序列上的统计问题自然想到 dp。

定义 $dp_{i,j}$ 表示由 $i$ 个 $1$ 和 $j$ 个 $-1$ 组成的数组的最大权值和。

以下两种情况：

- 假设有一个 $i-1$ 个 $1$ 和 $j$ 个 $-1$ 组成的数组，那在他 **前面** 添加一个 $1$ 会让其权值增加 $1$。

- 假设有一个 $i$ 个 $1$ 和 $j-1$ 个 $-1$ 组成的数组，那在他 **前面** 添加一个 $-1$ 会让其权值减少 $1$，**但其本身权值已经是 $0$ 的除外**。

可以得到转移方程。设 $zero_{i,j}$ 表示 $i$ 个 $1$ 和 $j$ 个 $-1$ 组成的权值为 $0$ 的数组的个数，则有

$dp_{i,j} \leftarrow dp_{i-1,j}+C_{i+j-1}^{i-1}+dp_{i,j-1}-C_{i+j-1}^{i}+zero_{i,j-1}$。

前两项表示第一种情况，每个数组的权值都会增加 $1$，因此需要加上数组数的贡献，也就是 $C_{i+j-1}^{i-1}$（意义：$i+j-1$ 个位置中 $i-1$ 个填 $1$）。

后三项表示第二种情况，每个权值非 $0$ 度数组数组的权值都会减少 $1$，因此需要减去数组数的贡献，也就是 $C_{i+j-1}^{i}$（意义：$i+j-1$ 个位置中 $i$ 个填 $1$），并加上本身就是 $0$ 的数组数。

对于组合数 $C$，我们可以 $O(NM)$ 递推解决。如何解决 $zero$ 数组？这一点其他题解都说的含含糊糊，事实上我们可以结合图像来解决：

一个数组权值是 $0$ 的**充分必要条件**是对于任何位置，其前面的 $-1$ 数大于等于 $1$ 的数量。我们把它放在平面直角坐标系上，横轴为 $-1$，纵轴为 $1$，则其数量等价于 $(0,0)$ 到 $(M,N)$ 的路径数（只能向上向右），且满足其不越过直线 $y=x$。

这时就容易推出 $zero$ 数组的转移方程：

- 当 $i=0$，$zero_{i,j}=1$；

- 当 $i>j$，$zero_{i,j}=0$；

- 否则，$zero_{i,j} \leftarrow zero_{i-1,j}+zero_{i,j-1}$。

可以结合图像理解。

因此可以完成本题。时间复杂度 $O(NM)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
#include <map>
#include <cstring>
#include <set>
#define LL long long
#define DB double
#define PII pair<int,int>
#define FI first
#define SE second
#define ls pos<<1
#define rs pos<<1|1
using namespace std;
const int MOD=998244853;
int dp[2005][2005],c[4005][4005],zero[2005][2005];
int N,M;
int main()
{
    scanf("%d %d",&N,&M);
    c[0][0]=1;
    for(int i=1;i<=N+M;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
    }
    zero[0][0]=1;
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=M;j++)
        {
            if(i==0) zero[i][j]=1;
            else if(i>j||j==0) zero[i][j]=0;
            else zero[i][j]=(zero[i-1][j]+zero[i][j-1])%MOD;
        }
    }
    for(int i=0;i<=N;i++) dp[i][0]=i;
    for(int i=0;i<=M;i++) dp[0][i]=0;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            dp[i][j]=((1ll*dp[i-1][j]+c[i+j-1][i-1]+dp[i][j-1]-c[i+j-1][i]+zero[i][j-1])%MOD+MOD)%MOD;
        }
    }
    printf("%d\n",dp[N][M]);
    return 0;
}
```



---

## 作者：chenxia25 (赞：1)

神仙计数题啊。（或者是我计数太烂了？）

---

首先这个最大前缀和的**值**很难融入到计数里面，很自然的想到对每个最大前缀和计数然后乘起来相加。

**最大**前缀和**恰好**等于某数比较难，套路地按差分思想计算最大前缀和小于等于某数的序列个数。但思考无果（

考虑正难则反，求至少有一个位置的前缀和大于等于该数的序列个数。由于起点从零开始，只要算至少有一个位置的前缀和等于该数的序列个数，即画成折线后穿过 $y=i$ 的个数。

首先如果 $n-m\geq i$，那么~~根据离散版的拉格朗日中值定理~~或者按照图形直观理解，知道所有序列都满足，答案就是 $\dbinom{n+m}n$。否则只需要考虑 $n-m<i$。

考虑容斥？考虑仅让第一次到达 $i$ 的位置做贡献？都思考无果，最好可以做到 FFT 优化的平方对数。下面就是很神仙的一步了！考虑转化，把至少穿过一次 $y=i$ 的折线这样一个不好数的东西转化成另一个东西。我们发现将这样的折线第一次穿过 $y=i$ 前面的部分按 $y=i$ 翻折依然连续，否则不可能连续。那么容易得到 $2i\to n-m$ 的折线和这样的折线形成双射。而这是好算的！就是 $\dbinom{n'+m'}{n'}$，其中 $n',m'$ 解个方程就可以出来。

P.S. 解方程过程：$n'-m'=n-m+2i,n'+m'=n+m$，解得 $n'=n+i,m'=m-i$。（bzd 是哪个毒瘤管理员连二元一次方程组的解法也要求放在紫题题解里/kel/kel）

---

## 作者：beacon_cwk (赞：1)

**原来的程序有问题，现已修正。**原来的程序可能会越界，在本机上其实是有问题的，但在CF上没测出来。（CF的评测机比较神奇，越界不明显或情况特殊时可能会忽略）

好像没人和我做法完全一样？那我就来写一个

首先，声明这个数组是1-indexed的，后面不再赘述。

设某种最大前缀和等于$x$，共有$num_x$个。所有的总和，可以用$\sum x \times num_x$算。但是直接用dp之类的计算每个$num_x$有些困难，换种思路。

枚举一个序列中，前缀的最大值$val$和第一次达到最大值的位置$p$（这里设为第一次，是为了方便计数，设成最后一次也可以）。尝试计算所有这样的序列的数目。这样肯定不会重复计数。

容易发现，对于所有的$1 \leq i<p$，都有$pre_i<pre_p$（这段连上$p$本身，称为“前面”）；对于所有的$p < i \leq n+m$，都有$pre_i \leq pre_p$（这段称为“后面”）。

同时，由$p$和$val$可以反推出前面和后面的$1$和$-1$的数量，前面$1$的数量为$(p+val)/2$，就设为$num1$吧（当然$num1$不是整数的情况要判掉）。剩下的可填位置数小于剩下$1$的数量的情况，**也要判掉**，不然可能会有负数下标。

总合法序列数量，就是前面的填法数$front$和后面的填法数量$back$的乘积。

$back$可能好算一些，就是“共有多少个序列长度为$(n+m-p)$，有$(m-num1)$个$1$，且每个前缀都不大于$0$”，$n^2$的dp就可以算。

至于$front$，把前面的条件变形一下。

$pre_i<pre_p$  移项得 $pre_p-pre_i>0$，这个"$pre_p-pre_i$"是什么呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/v3l2l76j.png)

也就是说，它是以$p$为结尾的一个后缀。这个后缀必须小于$0$。注意到可以翻转，后缀可以看成与前缀等价，用另一个dp就能算出来。

具体地说一下我的dp，$f_{i,j}$表示长度为$i$、有$j$个$1$的序列中，所有前缀和都**不小于**$0$的序列的数量。把这样的序列中所有数取相反数，也就是把$j$变成$i-j$，就变成了所有前缀和都不大于$0$的数量了。类似地，$g_{i,j}$表示所有非空前缀的前缀和都小于$0$的数量。

具体转移不难，看代码吧。

$k$就等于$n+m$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mit map<int,int>::iterator
#define sit set<int>::iterator
#define itrm(g,x) for(mit g=x.begin();g!=x.end();g++)
#define itrs(g,x) for(sit g=x.begin();g!=x.end();g++)
#define ltype int
#define rep(i,j,k) for(ltype(i)=(j);(i)<=(k);(i)++)
#define rap(i,j,k) for(ltype(i)=(j);(i)<(k);(i)++)
#define per(i,j,k) for(ltype(i)=(j);(i)>=(k);(i)--)
#define pii pair<int,int>
#define fi first
#define se second
#define mpr make_pair
#define pb push_back
#define fastio ios::sync_with_stdio(false)
const int inf=0x3f3f3f3f,mod=998244853;
const double pi=3.1415926535897932,eps=1e-6;
int n,m,f[4005][4005],g[4005][2005],ans,k;
#define check(i) if(i>=mod) i-=mod;
int main()
{
    scanf("%d%d",&n,&m);//新的版本n和m已经正常了
    k=n+m;
    f[0][0]=1;
    rep(i,1,k) rep(j,0,min(i,k)) if(2*j>=i){//这里必须是min(i,n+m)，后面调用f时第二维会到n以上
        if(j>0) f[i][j]=f[i-1][j-1];
        f[i][j]+=f[i-1][j];
        check(f[i][j]);
    }
    g[0][0]=1;
    rep(i,1,k) rep(j,0,min(i,n)) if(2*j>i){
        if(j>0) g[i][j]=g[i-1][j-1];
        g[i][j]+=g[i-1][j];
        check(g[i][j]);
    }
    rep(p,1,k) rep(val,1,min(p,n)){
        if((p+val)&1) continue;
        int num1=(p+val)/2;
        if(num1>n||k-p<n-num1) continue;//这里就是之前错的原因了，k-p<n-num1的话，肯定不会合法。        
        ans+=(ll)g[p][num1]*f[k-p][k-p-(n-num1)]%mod*val%mod;
        check(ans);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：求由 $n$ 个 $1$ 与 $m$ 个 $-1$ 构成的所有序列的最大前缀和的和。

核心思想：递推

解：

不妨设 $f(i,j)$ 为由 $i$ 个 $1$ 与 $j$ 个 $-1$ 构成的所有序列的最大前缀和的和。则有 $f(i,j)=f(i-1,j)+C_{i+j-1}^{i-1}$（序列最后一位是 $1$）$+f(i,j-1)-C_{i+j-1}^{i}$（序列最后一位是 $-1$）。然而注意到后一种情况中若一个序列起初最大前缀和为 $0$，在末尾添加一项 $-1$ 后仍然为 $0$，故还需加上 由 $i$ 个 $1$ 与 $j-1$ 个 $-1$ 构成的所有最大前缀和为 $0$ 的序列的个数，记为 $z(i,j)$。对于边界条件，$\forall\:0\le i\le n,m$ 由定义有 $f(i,0)=i$ 与 $f(0,i)=0$。

显然，所有最大前缀和为 $0$ 的序列都满足 $\forall\:1\le k\le i+j$，前 $k$ 项中 $-1$ 的个数不少于 $1$ 的个数。通过枚举在最后两个 $1$ 之间放置几个 $-1$，可得 $z(i,j)=\Sigma_{k=0}^{j-1+1}z(i, j-k)$（注意此处 $k$ 的含义与上文中不同）。在程序中，为优化复杂度可以采用转移前缀和的方式来优化复杂度：定义 $z'(i,j)=\Sigma_{k=i}^jz(i,k)$，则有 $z'(i,j)=z'(i,j-1)+z'(i-1,j)$。对于边界条件，$\forall\:0\le i\le m$ 有 $z(0, i)=1$。

根据以上诸式转移即可。注意模数为 $998244853$ 而非 $998244353$。

代码：
```
#include <bits/stdc++.h>
using namespace std;
const long long mod=998244853;//注意模数
long long n, m, a[2001][2001], z[2001][2001], fac[4001], inv[4001];
long long com(long long x, long long y)
{
	return fac[y]*inv[x]%mod*inv[y-x]%mod;//求组合数
}
int main()
{
	cin>>n>>m;
	fac[0]=1;
	inv[0]=1;
	inv[1]=1;
	for(int i=1; i<=4000; i++)
		fac[i]=fac[i-1]*i%mod;
	for(int i=2; i<=4000; i++)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1; i<=4000; i++)
		inv[i]=inv[i-1]*inv[i]%mod;//预处理阶乘及阶乘逆元。注意需要处理到4000
	for(int i=0; i<=m; i++)
		z[0][i]=1;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=i; j++)
			z[j][i]=(z[j][i-1]+z[j-1][i])%mod;//求z的前缀和
	for(int i=m; i>=1; i--)
		for(int j=i; j<=n; j++)
			z[j][i]=(z[j][i]-z[j][i-1]+mod)%mod;//求z
	for(int i=1; i<=n; i++)
		a[i][0]=i;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			a[i][j]=((a[i-1][j]+a[i][j-1]+com(i-1, i+j-1)-com(i, i+j-1)+z[i][j-1])%mod+mod)%mod;//求a
	cout<<a[n][m];
	return 0;
}

```

---

## 作者：hexagon (赞：0)

## CF1204E

### Description

定义一个长度为 $d$ 的序列 $a_i$，最大前缀和是：
$$
\max(\displaystyle \max_{i=1}^{d}{\sum_{j=1}^{i}{a_j}},0)
$$
给出 $n$ 和 $m$ ，求对于所有由 $n$ 个 $1$ 和 $m$ 个 $-1$ 组成的所有序列的最大前缀和之和。

答案对 $998244853$ 取模。

$1\leq n,m\leq 2000$

### Solution

**注：下文为了方便描述，$(i,j)$ 表示有 $i$ 个 $1$ , $j$ 个 $-1$ 的序列**

首先有一种很显然的 $O(n^3)$ 暴力:

设 $dp[i][j][k]$ 为序列 $(i,j)$ ，最大前缀和为 $k$ 的方案数。

转移：
$$
dp[i][j][k] \rightarrow dp[i+1][j][max(k,i+1-j)]
$$
$$
dp[i][j][k] \rightarrow dp[i][j+1][k]
$$


答案为：
$$
\sum_{i=\max(n-m,0)}^{n}{dp[n][m][i]*i}
$$

我们考虑优化这个算法：设 $dp[i][j]$ 为序列 $(i,j)$ 的前缀最大值之和，答案就是： $dp[n][m]$

考虑转移：对于$dp[i][j]$ 

+ 最后一个数是 $-1$ ，那么：
  $$
  dp[i][j] \leftarrow dp[i][j-1]
  $$
  因为在任意一个序列后加上一个 $-1$ 它的前缀最大值不会改变

+ 最后一个数是 $1$ :
  $$
  dp[i][j] \leftarrow dp[i-1][j]+x
  $$
  因为在有一些序列后加上一个 $1$ 后，它的前缀最大值会改变，所以我们要加上这部分的贡献。

那贡献具体是多少呢？

我们发现，如果加上 $1$ 后前缀最大值改变，那么最大值一定是前 $i+j$ 位的前缀和，即：
$$
\sum_{k=1}^{i+j}{a[k]}=i-j
$$
且加上 $1$ 之前的序列的最大值要小于 $i-j$ ,即小于等于 $i-j-1$ ,又考虑到序列 $(i-1,j)$ 的最大值本来就会大于等于 $i-j-1$ (这个序列的总和)

所以只有**序列 $(i-1,j)$ 中前缀最大值为i-j-1时会产生贡献，且只产生 $1$ 的贡献**。

接下来将就算这样的数的个数，有一个显然的结论：序列 $(i,j)$ 的前缀最大值为 $i-j$ 的充分必要条件是这个序列的每一个后缀都大于等于 $0$

也就是说：序列 $(i,j)$ 的前缀最大值为 $i-j$ 的个数 $=$ 序列 $(i,j)$ 的每一个后缀都大于 $0$ 的个数 $=$ 序列 $(i,j)$ 的每一个前缀都大于等于 $0$ 的个数。

这个东西可以直接 $dp$ 求：

设 $g[i][j]$ 为序列 $(i,j)$ 的每一个前缀都大于等于 $0$ 的个数，转移：
$$
g[i][j]\leftarrow g[i-1][j](i-1\geq j)
$$
$$
g[i][j]\leftarrow g[i][j-1](i\geq j-1)
$$
写起来其实很短，时间复杂度 $O(n^2)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;i++)
#define per(i,a,b) for(int i=(a),i##end=(b);i>=i##end;i--)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
const int N=2005;
const int P=998244853;
int n,m,f[N][N],g[N][N]; 
inline int read(){
	int f=1,x=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return f*x;
}
int main(){
	n=read(),m=read();
	rep(i,0,n) f[i][0]=1;
	rep(i,1,n) rep(j,1,m) if(i>=j) f[i][j]=((i-1>=j)*f[i-1][j]+(i>=j-1)*f[i][j-1])%P;
	rep(i,1,n) g[i][0]=i;
	rep(i,1,n) rep(j,1,m) g[i][j]=((g[i][j-1]+g[i-1][j])%P+f[i-1][j])%P;
	printf("%d",g[n][m]);
	return 0;
}
```







---

