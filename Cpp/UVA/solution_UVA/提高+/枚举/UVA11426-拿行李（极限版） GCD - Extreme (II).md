# 拿行李（极限版） GCD - Extreme (II)

## 题目描述

得定 $n$，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 4\times 10^6+1$。

## 样例 #1

### 输入

```
10
100
200000
0```

### 输出

```
67
13015
143295493160```

# 题解

## 作者：周道_Althen (赞：24)

## 7倍经验！！！[UVA11417 GCD](https://www.luogu.org/problemnew/show/UVA11417)，[UVA11424 GCD - Extreme (I)](https://www.luogu.org/problemnew/show/UVA11424)，[P1390 公约数的和](https://www.luogu.org/problemnew/show/P1390)，[P2398 GCD SUM](https://www.luogu.org/problemnew/show/P2398)，[P2568 GCD](https://www.luogu.org/problemnew/show/P2568)，[SP3871 GCDEX - GCD Extreme](https://www.luogu.org/problemnew/show/SP3871)。



------------


我们要求的式子：
$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)$$

如果你会写$for$循环，会写欧几里得算法($\ \rm gcd\ $)，你就可以过这道题了：[UVA11417 GCD](https://www.luogu.org/problemnew/show/UVA11417)

现在我们逐步化简：
$$\begin{aligned}\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)&=\sum_{j=1}^{n}\sum_{i=1}^{j-1}{\rm gcd}(i,j)\\&=\sum_{d=1}^{n}d\times \sum_{j=1}^{n}\sum_{i=1}^{j-1}\left[{\rm gcd}(i,j)=d\right]\\&=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{i=1}^{j-1}\left[{\rm gcd}(i,j)=1\right]\\&=\sum_{d=1}^{n}d\times \sum_{j=1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(j)\end{aligned}$$

(注意本题的特殊性，我们需要重新定义$\varphi(1)=0$)

嗯，就这个式子，复杂度$O(n+Tn\sqrt{n})$，你就可以过了这道题了：[UVA11424 GCD - Extreme (I)](https://www.luogu.org/problemnew/show/UVA11424)

但是这个，要用到分块操作才能过，

令$\ {\rm{sumphi}}(x)=\sum_{j=1}^{x}\varphi(j)$，$\ {\rm{sum}}(x)=\sum_{j=1}^{x}j$。

那么原式就可以化为：$\sum_{d=1}^{n}d\times {\rm{sumphi}}(\left\lfloor\frac{n}{d}\right\rfloor)$

可以发现，我们枚举了很多$\ d$，使得很多$\left\lfloor\frac{n}{d}\right\rfloor$都相等，所以我们可以把$\sum_{d=1}^{n}$，分成$\sqrt{n}\ $块，使得每一块的$\left\lfloor\frac{n}{d}\right\rfloor$都相等，这样我们可以通过结合律得到下面的式子，预处理$sumphi(x)$，$sum(x)$，来简化复杂度到$O(n+T\sqrt{n})$：

$$\sum ({\rm{sum}}[r]-{\rm{sum}}[l-1])\times {\rm{sumphi}}(\left\lfloor\frac{n}{l}\right\rfloor)$$



------------


- 扩展一、[P1390 公约数的和](https://www.luogu.org/problemnew/show/P1390)：

  这道题要求的式子是：$$\sum_{i=1}^{n}\sum_{j=1}^{n}{\rm gcd}(i,j)[i<j]$$

  其实和这道题是一样的：
  $$\sum_{i=1}^{n}\sum_{j=i+1}^{n}{\rm gcd}(i,j)$$
  一模一样的代码躺着A。



------------

 
- 扩展二、[P2398 GCD SUM](https://www.luogu.org/problemnew/show/P2398)：

  这道题要求的式子是：$$\sum_{i=1}^{n}\sum_{j=1}^{n}{\rm gcd}(i,j)$$

  其实就是：$$\left(\sum_{i=1}^{n}\sum_{j=1}^{n}{\rm gcd}(i,j)[i<j]\right)\times 2 +\sum_{i=1}^{n}i$$
  答案就应该是：
  $$\left(\sum ({\rm{sum}}[r]-{\rm{sum}}[l-1])\times {\rm{sumphi}}(\left\lfloor\frac{n}{l}\right\rfloor)\right)\times 2 +{\rm{sum}}(n)$$
  

------------
  
- 扩展三、[P2568 GCD](https://www.luogu.org/problemnew/show/P2568)：

  这道题要求的式子是：$$\sum_{i=1}^{n}\sum_{j=1}^{n}[{\rm gcd}(i,j)\tt is\ prime]$$

  其实就是：$$\left(\sum_{i=1}^{n}{\rm sumphi}(\frac {n}{i})[i\ \tt is\ prime]\right)\times 2-\sum_{i=1}^{n}[i\ \tt is\ prime]$$
  
  线性筛个素数就行了。



------------


下面贴这道题的代码:
```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
    int x=0,f=1;char ch;ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
    if(f)return x;else return -x;
}
const int N=4000010; 
bool vis[N];
long long prim[N],phi[N],sum[N],ans;
void get_phi(int n){
  phi[1]=0;
  for(int i=2;i<=n;i++){
    if(!vis[i]){phi[i]=i-1;prim[++prim[0]]=i;}
    for(int j=1;j<=prim[0]&&i*prim[j]<=n;j++){
      vis[i*prim[j]]=1;
      if(i%prim[j]==0){phi[i*prim[j]]=phi[i]*prim[j];break;}
      else phi[i*prim[j]]=phi[i]*(prim[j]-1);
    }
  }
  for(int i=1;i<=n;i++)phi[i]+=phi[i-1];
  for(int i=1;i<=n;i++)sum[i]=sum[i-1]+1ll*i;
}
int n;
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main()
{
    get_phi(4000000);
    while(scanf("%d",&n)==1&&n){
        ans=0;
      for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ans+=phi[(int)(n/l)]*(sum[r]-sum[l-1]);
      }
      printf("%lld\n",ans);
    }
    return 0;
}

```



------------


还有这道题
[SP3871 GCDEX - GCD Extreme](https://www.luogu.org/problemnew/show/SP3871)和本题一模一样，不过就是会T，估计要什么蜜汁卡常~~（我还没有过）~~

~~更新，在大巨佬[@hdxrie](https://www.luogu.org/space/show?uid=61423)的指导，我还是过了，确实是做法有点区别的~~

---

## 作者：lahlah (赞：8)

我扔：https://www.luogu.org/problemnew/show/UVA11426

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

## 作者：HPXXZYY (赞：3)

$\color{blue}{\texttt{[Problem]}}$

- 给定一个数 $n$，求：

  $$\sum\limits_{i=1}^{n} \sum\limits_{j=i+1}^{n} \gcd(i,j)$$

- $2 \leq n \leq 4 \times 10^6$，多组数据，输入以 $0$ 结束。保证答案在 `long long` 范围内。

$\color{blue}{\texttt{[Solution]}}$

记 $f_i = \sum\limits_{j=1}^{i-1} \gcd(j,i)$，则答案 $S_i=\sum\limits_{j=2}^{n} f_j$。

求出了所有的 $f_i(2 \leq i \leq N)$ 后（$N = 4 \times 10^6$），就可以用 $O(N)$ 的时间求出所有的 $S_i (2 \leq i \leq N)$。

现在，让我们考虑如何求出 $f_i(2 \leq i \leq N)$。

枚举 $d$，代表 $\gcd(j,i)=d$，假设这样的 $j$ 有 $k$ 个，则对答案的贡献为 $k \times d$。

接下来，考虑如何求出 $k$ 的值。显然，$i,j$ 一定满足 $d|i,d|j$，且 $\dfrac{i}{d},\dfrac{j}{d}$ 互质。

> 简单地证明一下：显然 $i,j$ 一定是满足 $d|i,d|j$ 的，否则 $\gcd(i,j) \neq d$。为什么 $\dfrac{i}{d},\dfrac{j}{d}$ 互质呢？
>考虑反证法。假设 $\dfrac{i}{d},\dfrac{j}{d}$ 不互质，记其最大公约数为 $g$。那么 $g$ 一定也是 $i,j$ 的因子，而且 $d \times g | i,d \times g | j$，即 $d \times g$ 也是 $i,j$ 的公约数，这与 $d$ 是 $i,j$ 的最大公约数矛盾。

有了这个定理，所以一对可行的 $(i,j)$ 一定与一对互质的数 $(\dfrac{i}{d}, \dfrac{j}{d})$ 一一对应。而因为 $\dfrac{i}{d},\dfrac{j}{d}$ 互质，所以这样的 $\dfrac{j}{d}$ 一共有 $\varphi(\dfrac{i}{d})$ 个，故这样的 $j$ 一共有 $\varphi(\dfrac{i}{d})$ 个。

所有的 $\varphi(i)(1 \leq i \leq N)$ 可以 $O(N)$ 求出，而枚举 $d$ 并计算 $f_i(2 \leq i \leq N)$ 是 $O(N\times \log N)$ 的，求出 $S_i(2 \leq i \leq N)$ 是 $O(N)$ 的，输出答案是 $O(1)$ 的。故总的时间复杂度为 $O(N \times N + T)$，其中 $T$ 是一共的数据个数。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=4e6+100;
typedef long long ll;
int n,phi[N];ll S[N],f[N];
int prime[N],g[N],tot;//线性筛 
inline void get_prime(int N){
	tot=0;phi[1]=1;//初始化 
	for(int i=2;i<=N;i++){
		if (!g[i]){//如果i是个素数 
			phi[i]=i-1;//初始化phi值 
			g[i]=prime[++tot]=i;
		}
		for(int j=1;j<=tot;j++){
			if (1ll*i*prime[j]>N) break;//剪枝 
			register int t=i*prime[j];//updata
			phi[t]=phi[i]*(prime[j]-(prime[j]<g[i]));
			g[t]=prime[j];//记录每个数的最小因子 
			if (prime[j]==g[i]) break;//算法优化 
		}
	}
}
int main(){
	get_prime(4e6);//求出phi值 
	for(int i=1;i<=(int)4e6;i++)
		for(int j=i*2;j<=(int)4e6;j+=i)
			f[j]+=1ll*i*phi[j/i];
	S[2]=f[2];//注意S[2]应特别赋值f[2] 
	for(int i=3;i<=(int)4e6;i++)
		S[i]=S[i-1]+f[i];//前缀和 
	while (~scanf("%d",&n)&&n)
		printf("%lld\n",S[n]);
	return 0;
}
```

---

## 作者：Huami360 (赞：3)

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
const int MAXN = 4000010;
long long phi[MAXN], v[MAXN], prime[MAXN], cnt;
int n;
long long ans; 
int main(){
    phi[1] = 1;
    for(int i = 2; i <= 4000002; ++i){
       if(!v[i]){
         v[i] = i;
         phi[i] = i - 1;
         prime[++cnt] = i;
       }
       for(int j = 1; j <= cnt; ++j){
          if(prime[j] > v[i] || prime[j] * i > 4000002) break;
          v[i * prime[j]] = prime[j];
          phi[i * prime[j]] = phi[i] * ((i % prime[j]) ? prime[j] - 1 : prime[j]);
       }
    }
    for(int i = 2; i <= 4000002; ++i) phi[i] += phi[i - 1];
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

## 作者：Ame__ (赞：1)

同步更新于我的博客[$My Blog$](https://www.cnblogs.com/Ame-sora/p/13304682.html)

### 前置芝士：莫比乌斯反演，欧几里得算法

同类题目:[UVA11417 GCD](https://www.luogu.com.cn/problem/UVA11417)

只要你会用for循环，你就能过的题

[P1390 公约数的和](https://www.luogu.com.cn/problem/P1390)

[SP3871 GCDEX - GCD Extreme](https://www.luogu.com.cn/problem/SP3871)

[UVA11424 GCD - Extreme (I)](https://www.luogu.com.cn/problem/UVA11424)

[P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)

纯水经验刷题数目的题，此题过后其他均可通过

正文：

$$\sum_{i=1}^{n}\sum_{j=i+1}^{n}\gcd(i,j)$$

你会发现在计算j时重复计算了i的那么我们考虑先将其看作单独的i，j，随后将重复部分减去即可

$\begin{aligned}\sum_{i = 1}^n\sum_{j = 1}^n\gcd(i, j)= \sum_{d = 1}^nd\sum_{i = 1}^n\sum_{j = 1}^n[\gcd(i, j) = d]\end{aligned}$

到了这里,我们发现对于$[gcd(i,j)=1]$我们可以根据莫比乌斯函数的定义$\begin{aligned}\sum_{d\mid n}\mu(d)\ =[n=1]\end{aligned}$来进行替换，即
$\begin{aligned}\sum_{d=1}^n\sum_{i=1}^\frac{n}{d}\sum_{j=1}^\frac{n}{d}\sum_{p\mid i,j}\mu(p)\end{aligned}$

我们可以按照套路将$p$提前$\begin{aligned}\sum_{d=1}^n\sum_{p=1}^\frac{n}{d}\mu(p)\sum_{i=1}^\frac{n}{d}[p\mid i]\sum_{j=1}^\frac{n}{d}[p\mid j]\end{aligned}$

对于后面的i，j两个和我们进行整除分块来做$\begin{aligned}\sum_{d = 1}^nd\sum_{p=1}^{\left\lfloor\frac n d\right\rfloor}\mu(p)\left\lfloor\frac n {dp}\right\rfloor\left\lfloor\frac n {dp}\right\rfloor\end{aligned}$


这里运用一个dp化Q的技巧可以变为$\begin{aligned}\sum_{Q = 1}^n\sum_{d|Q}d*\mu(\frac Q{d})\left\lfloor\frac n {Q}\right\rfloor^2\end{aligned}$

然后你会发现我们化简到的$\begin{aligned}\sum_{d|Q}d*\mu(\frac Q{d})\end{aligned}$符合$id*\mu=\varphi$的形式，所以我们可以进一步简化为$\begin{aligned}\sum_{Q = 1}^n\varphi(Q)\left\lfloor\frac n {Q}\right\rfloor^2\end{aligned}$，对于询问T次值，总下来复杂度为$O(n +T\sqrt n)$,可以通过此题，上面那个阉割版的柿子一模一样，照着用代码实现即可，此题最后还要处理一下重复情况

### 常见卷积

$σ(n)$：约数和函数，表示n的全部约数和

$\mu*id_0=\epsilon$

$\varphi*id_0=id_1$

$\mu*id_1=\varphi$

$id_0*id_1=σ$

$Code$
```.cpp
#include<bits/stdc++.h>

#define LL long long

using namespace std;

template <typename T> void read(T & t) {              
    t = 0;int f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f =- 1;ch = getchar();}
    do{t = t * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');t *= f;
}

const int kato = 4e6 + 1;

bool ispri[kato];

LL n;

LL prime[kato] , phi[kato] , sum[kato] , cnt;

inline void get_phi(){
	for(int i = 2;i <= kato;i ++){
		if(!ispri[i]){
			prime[++ cnt] = i;
			phi[i] = i - 1;
		}
		for(int j = 1;j <= cnt && (i * prime[j] <= kato);j ++){
			ispri[i * prime[j]] = 1;
			if(i % prime[j] == 0){
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else{
				phi[i * prime[j]] = phi[i] * phi[prime[j]]; 
			}
		}
	}
	for(int i = 1;i <= kato;i ++){
//		if(i<=10) cerr<<phi[i]<<"\n";
		sum[i] = sum[i - 1] + phi[i];
	}
}

inline int Ame_(){
	phi[1] = 1 , ispri[1] = 1;
	get_phi();
	while(cin >> n){
		if(!n){
			return 0;
		}
		LL ans = 0;
		for(LL l = 1 , r;l <= n;l = r + 1){
            r = n / (n / l);
			ans += (sum[r] - sum[l - 1]) * (n / l) * (n / l);
		}
		ans -= n * (n + 1) / 2;
		ans /= 2;
		printf("%lld\n" , ans);
	}
	return 0;
}

int Ame__ = Ame_();

signed main(){;}
```
### 注意
不知道为什么n不开long long被卡精度卡了半天没过，最后改了才没事，其他的就没什么注意的点了

---

## 作者：岚雪 (赞：1)

对于原题中要求的式子$\displaystyle{\sum_{i=1}^n\sum_{j=i+1}^n\text{gcd}(i,j)}$，我们对其变形，得到$\displaystyle{\sum_{i=1}^n\sum_{j=1}^{i-1}\text{gcd}(i,j)}$。

下面问题转换为求$\displaystyle{\sum_{i=1}^n\sum_{j=1}^{i-1}\text{gcd}(i,j)}$，这个问题明显好求一些。

如果强行枚举$i,j$肯定是要超时的，所以我们改变思路枚举最大公约数的值，设为$k$。

注意到当且仅当$(a,b)=1$时会有$(ak,bk)=k$，所以对于每一个$k$，设$a,b$中较大的一个数为$a$，首先$a$必须满足$ak\leq n$，即$a\leq \lfloor \dfrac{n}{k}\rfloor$。

我们固定住$a$的值，由于$b<a$，所以此时$b$有$\varphi(a)$种选择，所以对于一个固定的$a$与$k$，对答案的贡献为$\varphi(a)\times k$。

注意到这里有一种特殊情况，由于在原式中$i$与$j$是不相等的，所以当$a=1$时无解。

所以对于每一个固定的$k$，有$\displaystyle{\sum_{i=2}^{\lfloor n/k\rfloor}(\varphi(i)\times k)=k\sum_{i=2}^{\lfloor n/k\rfloor}\varphi(i)=k\sum_{i=1}^{\lfloor n/k\rfloor}\varphi(i)-k}$

由于$k$有$1$到$n$共$n$种取法，所以最终答案为$\displaystyle{\sum_{k=1}^n\left(k\sum_{i=1}^{\lfloor n/k\rfloor}\varphi(i)-k\right)}$

但同时我们也可以直接证明$\displaystyle{\sum_{k=1}^n\left(k\sum_{i=1}^{\lfloor n/k\rfloor}\varphi(i)-k\right)=\sum_{i=1}^n\sum_{j=1}^{i-1}\text{gcd}(i,j)}$，下证其正确性。

证明：

$\displaystyle{\sum_{i=1}^n\sum_{j=1}^{i-1}\text{gcd}(i,j)=\sum_{i=1}^n\sum_{j=1}^{i}\text{gcd}(i,j)-\dfrac{n(1+n)}{2}}$

$\displaystyle{=\sum_{d=1}^n\left(d\sum_{i=1}^n\sum_{j=1}^{i}\left[\gcd(i,j)=d\right]\right)-\dfrac{n(1+n)}{2}}$

注意到在这里$\gcd(i,j)=d$可以写成$\gcd(\dfrac{i}{d},\dfrac{j}{d})=1$

所以原式$\displaystyle{=\sum_{d=1}^n\left(d\sum_{i=1}^{\lfloor n/d\rfloor}\sum_{j=1}^{i}\left[\gcd(i,j)=d\right]\right)-\dfrac{n(1+n)}{2}}$

$\displaystyle{=\sum_{d=1}^n\left(d\sum_{i=1}^{\lfloor n/d\rfloor}\varphi(i)\right)-\dfrac{n(1+n)}{2}}$

$\displaystyle{=\sum_{d=1}^n\left(d\sum_{i=1}^{\lfloor n/d\rfloor}\varphi(i)-d\right)}$

证毕。

注意到$\displaystyle{k\sum_{i=1}^{\lfloor n/k\rfloor}\varphi(i)-k}$是可以先线性处理欧拉函数前缀和然后$\text O(1)$查询的，所以整个求和式可以在$\text{O}(n)$内做出来。

---

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 4000005;

ll n, cnt, vis[N], prime[N], phi[N];
int main() {
//	freopen("Uva11426.in", "r", stdin);
//	freopen("Uva11426.out", "w", stdout);
	ios::sync_with_stdio(false);
    // 预处理欧拉函数
	phi[1] = 1;
	for (int i = 2; i <= N - 5; i ++) {
		if (!vis[i]) {
			prime[++ cnt] = i;
			phi[i] = i - 1;
			vis[i] = i;
		}
		for (int j = 1; j <= cnt; j ++) {
			if (prime[j] > vis[i] || prime[j] * i > N - 5)
				break;
			vis[i * prime[j]] = prime[j];
			if (i % prime[j] != 0)
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			else
				phi[i * prime[j]] = phi[i] * prime[j];
		}
	}
	for (int i = 2; i <= N - 5; i ++)
		phi[i] += phi[i - 1];
	while (true) {
		cin >> n;
		if (n == 0)
			return 0;
		long long ans = 0;
		for (int i = 1; i <= n; ++ i)
			ans += (phi[n / i] - 1) * i;
		cout << ans << endl;
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)

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
const int MAXN = 4000000 + 6;
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

## 作者：lx_zjk (赞：0)

愉快的颓柿子 ~~基本操作不用解释了吧...~~
$$
(\sum_{x=1}^n \sum_{y=1}^m \gcd(x,y))
$$

$$
(\sum_{x=1}^n \sum_{y=1}^m \gcd(x,y))
$$


$$
(\sum_{x=1}^n \sum_{y=1}^m\sum_{p=1}^n p*[\gcd(x,y)=p])
$$

$$
(\sum_{p=1}^{n} \sum_{x=1}^{\lfloor\frac{n}{p}\rfloor}\sum_{y=1}^{\lfloor\frac{m}{p}\rfloor} p*[\gcd(x,y)=1]) - 
$$

$$
(\sum_{p=1}^{n} p*\sum_{x=1}^{\lfloor\frac{n}{p}\rfloor}\sum_{y=1}^{\lfloor\frac{m}{p}\rfloor} \sum_{d|\gcd(x,y)} \mu(d))
$$

$$
(\sum_{p=1}^n p*\sum_{d=1}^{\lfloor\frac{n}{p}\rfloor} \mu(d) \sum_{d|x}^{\lfloor\frac{n}{p}\rfloor}\sum_{d|y}^{\lfloor\frac{m}{p}\rfloor}1)
$$

$$
2(\sum_{p=1}^n p*\sum_{d=1}^{\lfloor\frac{n}{p}\rfloor}\mu(d)  \lfloor\frac{m}{dp}\rfloor\lfloor\frac{n}{dp}\rfloor) - n*m
$$

$$
\sum_{T=1}^n \sum_{d|T} d * \mu(\frac{T}{d})\lfloor\frac{m}{T}\rfloor\lfloor\frac{n}{T}\rfloor
$$

$$
\sum_{T=1}^n\lfloor\frac{m}{T}\rfloor\lfloor\frac{n}{T}\rfloor \sum_{d|T} d*\mu(\frac{T}{d})
$$


$$
\sum_{T=1}^n\lfloor\frac{m}{T}\rfloor\lfloor\frac{n}{T}\rfloor \phi(T) 
$$


---

## 作者：andyli (赞：0)

设$f(n)=\gcd(1,n)+\gcd(2,n)+\gcd(3,n)+...+\gcd(n-1,n)$,则所求答案为$S(n)=f(2)+f(3)+...+f(n)$。只需求出$f(n)$，就可以递推出所有答案：$S(n)=S(n-1)+f(n)$。因此，本题的重点在于如何计算$f(n)$。  
注意到所有$\gcd(x,n)$的值都是$n$的约数，可以按照这个约数进行分类，用$g(n,i)$表示满足$gcd(x,n)=i$且$x<n$的正整数$x$的个数，则$f(n)=sum\{i\times g(n,i)|i\text{是}n\text{的约数}\}$。注意到$\gcd(x,n)=i$的充要条件是$\gcd(x/i,n/i)=1$，因此满足条件的$x/i$有$phi(n/i)$个，说明$g(n,i)=phi(n/i)$。  
问题到这里还没有结束。如果依次计算$f(n)$，需要对每个$n$枚举它的约数$i$，速度较慢，但如果把思路逆转过来，对于每个$i$枚举它的倍数$n$（并且更新$f(n)$的值），时间复杂度将降为与素数筛法同阶。至此，问题得到了完整的解决。代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 4000000;
typedef long long LL;

int phi[maxn];
void phi_table(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        if (!phi[i])
            for (int j = i; j <= n; j += i)
            {
                if (!phi[j])
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
}
LL S[maxn + 1], f[maxn + 1];
int main()
{
    phi_table(maxn);
    for (int i = 1; i <= maxn; i++)
        for (int n = i * 2; n <= maxn; n += i)
            f[n] += i * phi[n / i];
    S[2] = f[2];
    for (int n = 3; n <= maxn; n++)
        S[n] = S[n - 1] + f[n];
    int n;
    while (~scanf("%d", &n) && n)
        printf("%lld\n", S[n]);
    return 0;
}

```

---

## 作者：decoqwq (赞：0)

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
int mu[4000010],prime[400020],cnt,vis[4000010],n,m;
void shai()
{
    mu[1]=1;
    for(int i=2;i<=4000005;i++)
    {
        if(!vis[i])
        {
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=4000005;j++)
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

