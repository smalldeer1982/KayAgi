# [Math×Girl] 互质与整除

## 题目背景

>“还可以连接一个东西。”米尔嘉说，“$1$ 的原始 $n$ 次方根的个数是欧拉老师 $\varphi$ 函数的值。函数 $\varphi(n)$ 在 $1\le k<n$ 的范围内表示与 $n$ 互质的自然数的个数，也表示循环群的生成元的个数。”米尔嘉像是描绘 $\varphi$ 似地挥动手指，“最喜欢互质的尤里不在这里真可惜，今天你怎么没带她来？”  
>米尔嘉瞪我。

“互质？”米尔嘉看着窗外说，“我们来做道有趣的题吧！”  

## 题目描述

给定一个数 $n$，求出满足以下方程的 $x$ 的个数。
$$\varphi(x)\mid n$$

其中 $\mid$ 为整除符号，$a\mid b$ 表示 $a$ 整除 $b$。  
$\varphi(x)$ 为欧拉 $\varphi$ 函数，详见题目背景。

## 说明/提示

### 样例解释

质因数分解前 $n$ 分别为：  
$8,2024,1145141919810$

第一个例子中的 $14$ 个解是：  
$\varphi(15)=\varphi(16)=\varphi(20)=\varphi(24)=\varphi(30)=8\mid 8$  
$\varphi(5)=\varphi(8)=\varphi(10)=\varphi(12)=4\mid 8$  
$\varphi(3)=\varphi(4)=\varphi(6)=2\mid 8$  
$\varphi(1)=\varphi(2)=1\mid 8$

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $n\in[1,10^7]$ |
| $1$ | $10$ | $n\in[1,10^9]$ |
| $2$ | $20$ | $n\in[1,10^{12}]$ |
| $3$ | $20$ | $n\in[1,10^{14}]$ |
| $4$ | $20$ | $n\in[1,10^{16}]$ |
| $5$ | $20$ | - |

对于 $100\%$ 数据，保证 $T=5$，$n\in[1,10^{18}],s\ge 1$。 

## 样例 #1

### 输入

```
3
1
2 3
3
2 3
11 1
23 1
6
2 1
3 2
5 1
7 1
101 2
178187 1```

### 输出

```
14
53
53```

# 题解

## 作者：Naszt (赞：8)

# 互质与整除

# 观前提醒

原本这题是作为 D 题的，不过多元多项式优化其实优化并不大，代码却极其难写，有点故意套模板的嫌疑。

所以本题就仅仅需要其思想，时间复杂度是 $O(d_3(n)+\sigma_0(n)\log n)$ 的。  
加上 EI 的多元多项式优化可以做到 $\Theta(s\sigma_0(n)\log\sigma_0(n)+\sigma_0(n)\log n)$。  
_※ $\sigma_0(n):=\sum_{ij=n}1$，为因子个数函数。_  
_※ $d_3(n):=\sum_{ijk=n}1$，为因子的因子个数函数。_

但 $d_3(n)$ 其实跑不满，实际上期望可能是 $\frac{d_3(n)}{\log n}$ 的，而且常数相对较低。  
当然，后面也是会讲一下多元多项式优化做法的。

# 思路分析

## 先表示出答案函数 $a(n)$ 

定义 [$\psi(n)$](https://oeis.org/A014197)：方程 $\varphi(x)=n$ 的 $x$ 的解数。  
答案 [$a(n)$](https://oeis.org/A070633) 即为 $\sum_{d\mid n}\psi(d)$。

定义 $\psi(n)$ 的 Dirichlet 生成函数：
$$\tilde{\Psi}(x)=\sum_{n\ge1}\frac{\psi(n)}{n^x}$$


由于每有一个 $\varphi(x)=n$ 就对 $\psi(n)$ 产生 $1$ 的贡献，  
由此我们可以化简 $\tilde{\Psi}(x)$：

$$
\begin{aligned}
\tilde{\Psi}(x)&=\sum_{n\ge1}\frac{\psi(n)}{n^x}=\sum_{n\ge1}\frac{1}{\varphi^x(n)}\\
&=\prod_{p\in\mathcal{P}}\left(1+\sum_{i\ge1}\frac{1}{\varphi^x(p^i)}\right)\\
&=\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}+(p^2-p)^{-x}+(p^3-p^2)^{-x}+\dots)\\
&=\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}(1+p^{-x}+p^{-2x}+\dots))\\
&=\prod_{p\in\mathcal{P}}\left(1+\frac{(p-1)^{-x}}{1-p^{-x}}\right)\\
&=\zeta(x)\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}-p^{-x})\\
\end{aligned}
$$

后面的乘积难以化简，于是我们将其单独提出。
即为定义 $f(n)$ 的 Dirichlet 生成函数：

$$\tilde{F}(x)=\sum_{n\ge1}\frac{f(n)}{n^x}=\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}-p^{-x})$$

那么答案函数 $a(n)$ 的 Dirichlet 生成函数为：
$$\tilde{\Alpha}(x)=\zeta(x)\tilde{\Psi}(x)=\zeta^2(x)\tilde{F}(x)$$

又因为 $\zeta^2(x)$ 是 $\sigma_0(n)$ 的 Dirichlet 生成函数，  
所以答案函数：
$$a(n)=\sum_{d\mid n}f(d)\sigma_0\left(\frac{n}{d}\right)$$

## 现在考虑快速计算 $f(d)$ 

$$f(d)=[d^{-x}]\prod_{p\in\mathcal{P}}(1+(p-1)^{-x}-p^{-x})$$
  
考虑直接计算，其值域为 $\sigma_0(n)$，共做 $O(\sigma_0(n))$ 次狄利克雷卷积。  
每次狄利克雷卷积可以直接将其看做背包问题 dp，时间复杂度为其值域。

那么时间复杂度为 $O(\sigma_0^2(n))$，当然也是跑不满的。

一种很自然的想法是将其转为多项式，但这并不是多项式。

我们模仿贝尔级数的思想，定义 $x_i=p_i^{-x}$，其中 $p_i$ 为第 $i$ 小的质数。  
对任意一项因式分解就可以将其转为单项式：

$$n^{-x}=\left(\prod_{i\ge1} p_i^{t_{i,n}}\right)^{-x}=\prod_{i\ge1} x_i^{t_{i,n}}$$

于是可以把 Dirichlet 生成函数转成多元普通生成函数：

$$f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\prod_{p\in\mathcal{P}}\left(1+\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)$$

考虑 $\sigma_0(n)$ 次暴力卷积，不过其实每次只会更新指数比它高的项，  
那么每次卷积的时间复杂度达不到 $\sigma_0(n)$。

时间复杂度实际上为 $\sum_{d|n}\sigma_0(d)=d_3(n)$，换句话就是因子的因子个数。

# 代码实现

以下代码有个 $s$ 的常数，你可以通过状压等方法去掉，不过没什么必要。

## 出题人代码

```cpp
#include<bits/stdc++.h>
#define il inline __attribute__((__always_inline__))

typedef unsigned int i4;
typedef unsigned long long i8;

namespace Miller_Rabin{
  const i4 Pcnt=7;
  const i8 p[Pcnt]={2,325,9375,28178,450775,9780504,1795265022};
  il i8 mul(i8 a,i8 b,i8 p){
    return __int128(a)*b%p;
  }
  il i8 pow(i8 a,i8 b,i8 p){
    i8 ans=1;
    for(;b;a=mul(a,a,p),b>>=1)if(b&1)ans=mul(ans,a,p);
    return ans;
  }
  il bool prime(i8 x){
    if(x<3||x%2==0)return x==2;
    i8 u=x-1,t=0;
    while(u%2==0) u/=2,++t;
    i8 ud[]={2,325,9375,28178,450775,9780504,1795265022};
    for(i8 a:ud){
      i8 v=pow(a,u,x);
      if(v==1||v==x-1||v==0) continue;
      for(i4 j=1;j<=t;j++){
        v=mul(v,v,x);
        if(v==x-1&&j!=t){v=1;break;}
        if(v==1) return 0;
      }
      if(v!=1) return 0;
    }
    return 1;
  }
}using Miller_Rabin::prime;

const i4 MAXS=16,MAXN=104000,MAXA=64;
const i8 P=998244353;

i8 p[MAXA];i4 T,s,a[MAXA];
struct Vec{
  char t[MAXS];
  i4 M=0;
  il Vec(){memset(t,0,sizeof(char)*MAXS);}
  il bool next(Vec&v){
    for(i4 i=0,w=1;i!=s;w*=(a[i++]+1)){
      if(t[i]==v[i]){M-=t[i]*w,t[i]=0;continue;}
      M+=w,t[i]++;return 1;
    }
    return 0;
  }
  il char&operator[](char x){return t[x];}
  il Vec operator+(Vec v){Vec x;for(char i=0;i!=s;i++)x[i]=t[i]+v[i];return x;}
  il Vec operator-(Vec v){Vec x;for(char i=0;i!=s;i++)x[i]=t[i]-v[i];return x;}
};

il i4 M(Vec v){i4 x=0;for(i4 i=0,w=1;i!=s;w*=(a[i++]+1))x+=v[i]*w;return x;}
il i8 D(Vec v){i8 x=1;for(i4 i=0;i!=s;i++)x*=(v[i]+1);return x;}
il i8 V(Vec v){i8 x=1;for(i4 i=0;i!=s;i++)x=x*powl(p[i],v[i])+.5;return x;}

il void conv(i4*f,Vec n_vd,Vec n_vp,const i4 Vd,const i4 Vp,const bool mod1,const bool mod2){
  static i4 F[MAXN];Vec i;
  if(mod1)do F[i.M+Vd]=f[i.M];while(i.next(n_vd));
  if(mod2)do F[i.M+Vp]+=P-f[i.M];while(i.next(n_vp));
  if(mod1)do f[i.M+Vd]=(f[i.M+Vd]+F[i.M+Vd])%P,F[i.M+Vd]=0;while(i.next(n_vd));
  if(mod2)do f[i.M+Vp]=(f[i.M+Vp]+F[i.M+Vp])%P,F[i.M+Vp]=0;while(i.next(n_vp));
}
il i4 slove(Vec n){
  static i4 f[MAXN];f[0]=1;i4 ans=0;
  std::map<i8,char>Pn;Vec d;
  for(i4 i=0;i!=s;i++){
    Vec d_1;i8 fact=p[i]-1;bool fg=1;
    for(auto [p_w,w]:Pn)while(fact%p_w==0)fact/=p_w,fg&=(++d_1[w]<=a[w]);
    if(fact!=1)fg=0;d[i]=1;conv(f,n-d_1,n-d,M(d_1),M(d),fg,1);d[i]=0;Pn[p[i]]=i;
  }
  do if(!Pn.count(V(d)+1)&&prime(V(d)+1))conv(f,n-d,d,d.M,0,1,0);while(d.next(n));
  do ans=(ans+D(n-d)*f[d.M])%P,f[d.M]=0;while(d.next(n));return ans;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  std::cin>>T;
  while(T--){
    std::cin>>s;Vec n;
    for(i4 i=0;i!=s;i++)std::cin>>p[i]>>a[i],n[i]=a[i];
    if(p[0]!=2){std::cout<<"2\n";continue;}
    std::cout<<slove(n)<<"\n";
  }
  return 0;
}
```

## 验题人代码

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#define ll unsigned long long
using namespace std;

ll FastMul(ll x, ll y, ll mod){return (__int128)x * y % mod;}
ll FastPow(ll a, ll b, ll mod){
  ll res = 1;
  while(b){
    if(b & 1) res = FastMul(res, a, mod);
    b >>= 1, a = FastMul(a, a, mod);
  }
  return res;
}

ll FastPowNoMod(ll a, int b){
  ll res = 1;
  while(b){
    if(b & 1) res *= a;
    b >>= 1, a *= a;
  }
  return res;
}

const int ListNum = 12, List[ListNum] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool Miller_Rabin(ll x){
  if(x == 1) return false;
  ll D = x - 1;
  while(!(D & 1)) D >>= 1;
  for(int i = 0; i < ListNum; ++i){
    if(x == List[i]) return true;
    ll k = FastPow(List[i], D, x), d = D;
    if(k != 1){
      while(d < x - 1){
        if(k == x - 1) break;
        d <<= 1, k = FastMul(k, k, x);
      }
      if(d == x - 1) return false;
    }
  }
  return true;
}

const int Mx = 103700, Nx = 16, Mod = 998244353;

ll N;
ll prime[Nx], ksm[Nx]; // power[i][j] = prime[i] ^ j
int alpha[Nx], cnt; // N = prod_{i \le cnt} prime[i] ^ alpha[i]
int sigma0, prod[Nx]; // Find position for vector bbeta[]

int F[Mx], G[Mx]; // ans = sum_{d|n} f(d) sigma0(n/d)

int bbeta[Nx], id; ll now; // Numerate divisor of n, now = prod_{i \le cnt} prime[i] ^ bbeta[i]
int gama[Nx], ids; // Numerate pres such that pre * now | n 
inline void getpos(ll x){
  id = 0;
  for(int i = 1; i <= cnt; ++i){
    int sum = 0;
    while(x % prime[i] == 0) x /= prime[i], ++sum;
    id += prod[i - 1] * sum, bbeta[i] = sum;
  }
}
inline bool pushup(){
  int pos = 1; ++id;
  while(bbeta[pos] == alpha[pos] && pos <= cnt) bbeta[pos] = 0, now /= ksm[pos], ++pos;
  return (pos == cnt + 1) ? 0 : (++bbeta[pos], now *= prime[pos], 1);
}
inline bool reduce(){
  int pos = 1;
  while(gama[pos] == 0 && pos <= cnt) gama[pos] = alpha[pos] - bbeta[pos], ids += prod[pos - 1] * gama[pos], ++pos;
  return (pos == cnt + 1) ? 0 : (--gama[pos], ids -= prod[pos - 1], 1);
}
inline bool add(){ // now = divisor(now)
  int pos = 1; ++id;
  while(bbeta[pos] == alpha[pos] && pos <= cnt) bbeta[pos] = 0, now /= (alpha[pos] + 1), ++pos;
  return (pos == cnt + 1) ? 0 : (++bbeta[pos], now += now / bbeta[pos], 1);
}

//int list[Mx];
//void print(){ cout << F[7] << endl; return;
//	for(int i = 0; i < sigma0; ++i) cout << list[i] << ' ' << F[i] << '\n';
//	cout << "===============\n";
//}

int Solve(){
  if(prime[1] != 2) return 2;
  prod[0] = N = 1;
  for(int i = 1; i <= cnt; ++i){
    prod[i] = prod[i - 1] * (alpha[i] + 1);
//		power[i][0] = 1;
    ksm[i] = FastPowNoMod(prime[i], alpha[i]);
//		for(int j = 1; j <= alpha[i]; ++j) power[i][j] = power[i][j - 1] * prime[i];
    N *= ksm[i];
  }
  sigma0 = prod[cnt];
  F[0] = 2, F[1] = -1;
  for(int i = 2; i < sigma0; ++i) F[i] = 0;
//	for(int i = 1; i <= cnt; ++i) bbeta[i] = 0;
//	now = 1, id = 0;
//	do list[id] = now; while(pushup());
//	print();
  for(int i = 2; i <= cnt; ++i){
    for(int j = 0; j < sigma0; ++j) G[j] = F[j];
    int idp = prod[i - 1];
    for(int j = 1; j <= cnt; ++j) gama[j] = alpha[j] - (i == j), bbeta[j] = (i == j);
    ids = sigma0 - 1 - idp;
    do F[ids + idp] = (F[ids + idp] - F[ids]) % Mod; while(reduce());
//		cout << "prime " << prime[i] << " mod " << N % (prime[i] - 1) << endl;
//		print();
    if(N % (prime[i] - 1) == 0){
      getpos(prime[i] - 1);
      for(int j = 1; j <= cnt; ++j) gama[j] = alpha[j] - bbeta[j];
      ids = sigma0 - 1 - id;
//			cout << "yesmod " << ids << ' ' << id << endl;
      do F[ids + id] = (F[ids + id] + G[ids]) % Mod; while(reduce());
    }
//		cout << "prime " << prime[i] << " don " << idp << endl;
//		print();
  }
  
  for(int i = 1; i <= cnt; ++i) bbeta[i] = 0; id = 0; now = 1;
  while(pushup()) if(N % (now + 1) != 0 && Miller_Rabin(now + 1)){
    for(int i = 1; i <= cnt; ++i) gama[i] = alpha[i] - bbeta[i];
    ids = sigma0 - 1 - id;
    do F[ids + id] = (F[ids + id] + F[ids]) % Mod; while(reduce());
//		cout << "divisor " << now << endl;
//		print();
  }
//	print();
  for(int i = 1; i <= cnt; ++i) bbeta[i] = 0; id = 0; now = 1;
  ll ans = 0;
  do ans += 1ll * now * F[sigma0 - 1 - id]; while(add());
  ans %= Mod;
  return ans < 0 ? ans + Mod : ans;
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T; cin >> T;
  while(T--){
    cin >> cnt;
    for(int i = 1; i <= cnt; ++i) cin >> prime[i] >> alpha[i];
    cout << Solve() << endl;
  }
  return 0;
}
```

# 多元多项式优化方法

观察多元普通生成函数：

$$f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\prod_{p\in\mathcal{P}}\left(1+\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)$$

仿照 [P4389 付公主的背包](https://www.luogu.com.cn/problem/P4389) 优化 0/1 背包：
$$f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{p\in\mathcal{P}}\ln\left(1+\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)\right)$$

对其展开成形式幂级数：
$$
\begin{aligned}
f(d)&=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{p\in\mathcal{P}}\sum_{k\ge1}\frac{(-1)^{k+1}}{k} \left(\prod_{i\ge1} x_i^{t_{i,p-1}}-\prod_{i\ge1} x_i^{t_{i,p}}\right)^k\right)\\
&=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{p\in\mathcal{P}}\sum_{\substack{j,k\ge0\\[3pt]j+k\ne0}}\frac{(-1)^{j+1}}{j+k}\binom{j+k}{j}\left(\prod_{i\ge1} x_i^{t_{i,p-1}}\right)^j\left(\prod_{i\ge1} x_i^{t_{i,p}}\right)^k\right)
\end{aligned}
$$

但是这样会有一个小问题：  
当 $p=2$ 时要计算 $ln(2-x_1)$  
但是很可惜，不能按上方一般的形式展开，所以我们可以将其单独提出：
$$
f(d)=\left[\prod_{i\ge1} x_i^{t_{i,d}}\right]\exp\left(\sum_{\substack{p\in\mathcal{P}\\[3pt]p\ne2}}\sum_{\substack{j,k\ge0\\[3pt]j+k\ne0}}\frac{(-1)^{j+1}}{j+k}\binom{j+k}{j}\left(\prod_{i\ge1} x_i^{t_{i,p-1}}\right)^j\left(\prod_{i\ge1} x_i^{t_{i,p}}\right)^k\right)(2-x_1)
$$

由于对于所有的 $d\mid n$，都有 $t_{i,d}<t_{i,n}$  
且已经给出了 $n$ 的标准质因子分解形式 $n=\prod_{i=1}^s p_i^{\alpha_i}$。  

所以我们仅需计算 $s$ 维，每一维都分别的次数都分别低于 $\alpha_i$ 的多项式的 exp。

这里如果暴力递推计算 exp 仍然是 $d_3(n)$ 的时间复杂度。

## 多元多项式

接下来最后一步就是多元多项式 exp 了，  
我这里主要是复读 [> EI 大神的 blog <](https://www.luogu.com/article/wje8kchr) 和有关 Uoj#596 的 blog，  
在此之前我们先浅谈一下多元多项式。

这里约定多元多项式为 $s$ 维，每一维都分别的次数都分别 $\le\alpha_i$ 的多项式。  
那么它的值域 $N=\prod_{i=1}^s(\alpha_i+1)=\sigma_0(n)$

### 多元多项式 DFT/IDFT

多元多项式 DFT 相当于按顺序依次对其每一维 DFT。  
多元多项式 IDFT 相当于反向按顺序的依次对其每一维 IDFT。

那么为什么多元多项式 DFT 就是依次对其每一维 DFT 呢？  
因为做 DFT 相当于把系数表示法转为了点值表示法，  
所以依次对其每一维带入单位根即可计算点值。

由于多元多项式 DFT 是线性算法。  
有「求逆原理」：$(A_1A_2\dots A_s)^{-1}=A_s^{-1}A_{s-1}^{-1}\dots A_1^{-1}$  
这样就得到了多元函数的 IDFT 算法。

### 多元多项式乘法

我们计算卷积 $F(x_1,x_2,\dots,x_s)\cdot G(x_1,x_2,\dots,x_s)$，  
可以发现卷积后的值域为 $\prod_{i=1}^s(2\alpha_i+1)=O(2^sN)$

然而实际上大多数情况下我们仅需计算 $\bmod(x_1^{\alpha_1},x_2^{\alpha_2},\dots,x_s^{\alpha_s})$ 意义下的值。  
若 $s$ 较大，值域将会急剧膨胀，这被称为维度爆炸。  
而 EI 以一种构造性的算法解决了这个问题：

显然，高维多项式是要避免的。  
于是我们将下标 $\vec{i}=(i_1,i_2,\dots,i_s)$ 编码为一个 $(\alpha_1+1,\alpha_2+1,...,\alpha_s+1)$ 进制数。  
即令 $\lvert\vec{i}\rvert=\sum\limits_{t=1}^si_t\prod_{n=1}^{t-1}(\alpha_n-1)=i_1+i_2*(\alpha_1+1)+...+i_s*(\alpha_1+1)*(\alpha_2+1)*...*(\alpha_{s-1}+1)$。  
这样就把多维映射到了一维上，下标 $\vec{i}$ 和编码 $\lvert\vec{i}\rvert$ 是一一对应的。  
而且可以发现大多数时候有 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$。    
所以多元多项式可以被这样的一元多项式来代替：
$$F(x_1,x_2,\dots,x_s)=\sum_{\substack{\vec{i}=(i_1,\dots,i_s)\\i_1\le \alpha_1,\dots,i_s\le \alpha_s}}^{}f_{\vec{i}}x_1^{i_1}\dots x_s^{i_s}\textcolor{red}\to F(x)=\sum_{i=0}^{N-1}f_ix^i$$

其中 $f_{\vec{i}}=f_{\lvert\vec{i}\rvert}$。

只有 $\vec{i}+\vec{j}$ 超过了模意义的范围时 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$ 才不成立，  
所以我们要将超出范围（产生进位）的贡献去除（我们要计算模意义下的卷积）。  
考虑占位函数 $\chi(n)$，使得 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$ 成立当且仅当 $\chi(i)+\chi(j)=\chi(i+j)$。  
这样，我们计算二元幂级数 $\sum_i f_ix^iy^{\chi(i)}$ 的卷积，然后利用第二维去除无用贡献即可。

接下来就是 EI 的一个精妙构造了：

由于 $[i_t+j_t\le \alpha_t]=\left\lfloor\frac{i+j}{\prod_{n=1}^{t-1}(\alpha_n+1)}\right\rfloor-\left\lfloor\frac{i}{\prod_{n=1}^{t-1}(\alpha_n+1)}\right\rfloor-\left\lfloor\frac{j}{\prod_{n=1}^{t-1}(\alpha_n+1)}\right\rfloor\in\{0,1\}$

令 $\chi(i)=\sum\limits_{t=1}^{s-1}\left\lfloor \frac{i}{\prod_{n=1}^{t}(\alpha_n+1)}\right\rfloor=\left\lfloor \frac{i}{(\alpha_1+1)}\right\rfloor+...+\left\lfloor \frac{i}{(\alpha_1+1)(\alpha_2+1)...(\alpha_{s-1}+1)}\right\rfloor$

这个占位函数是极好的，因为 $\chi(i+j)-\chi(i)-\chi(j)\in[0,s)$。  
所以 $\lvert\vec{i}+\vec{j}\rvert=\lvert\vec{i}\rvert+\lvert\vec{j}\rvert$ 成立当且仅当 $\chi(i)+\chi(j)\equiv\chi(i+j)\pmod{s}$。  

我们令 $1\equiv y^s$，相当于模 $y^s-1$ 的循环卷积。  
这样，值域也被这么压缩到了 $sN$。

### 多元多项式全家桶

多元多项式的其他运算可以直接套一元多项式的模板。

对其求导可以考虑一个特殊的微分算子 $\mathfrak{D}=x\frac{d}{dx}$，  
这里的 $x$ 是压缩成一维时的变量。  

可以发现它满足常见的导数性质，  
这样就解决了多项式 ln 和牛顿迭代。

## 时间复杂度

时间复杂度分为：  
1. 判 $\sigma_0(n)$ 次质数（所有的 $d+1$）：$\Theta(\sigma_0(n)\log n)$
2. 计算 exp 之前的级数：$O(\sigma_0(n))$
3. 多元多项式 exp：$\Theta(s\sigma_0(n)\log\sigma_0(n))$

第 $2$ 处的时间复杂度证明（不严谨）：  
若所有质因子减 $1$ 都还是因子：$O(s\log^2(n))$  
若所有因子加 $1$ 都是质数（除去上方情况）：$A309891(n)+\sigma_0(n)$  
当 $\sigma_0(n)$ 较大时这里的时间复杂度就为 $O(\sigma_0(n))$  
~~较小时就没必要考虑时间复杂度了~~  

第 $3$ 处的时间复杂度以及实现方法，对于卷积部分：  
做 $s$ 个长为 $2N$ 的 DFT，  
然后在 $y$ 维暴力进行卷积，相当于进行了 DFT+IDFT。  
再做 $s$ 个长为 $2N$ 的 IDFT，  
卷积顺序正确性可以看上方的证明。  
复杂度为 $\Theta(sN\log N)+\Theta(s^2N)=\Theta(sN\log N)=\Theta(s\sigma_0(n)\log\sigma_0(n))$。  
而牛顿迭代并不会增加时间复杂度。

总时间复杂度为：
$$\Theta(s\sigma_0(n)\log\sigma_0(n)+\sigma_0(n)\log n)$$

## 暴力 exp 版本代码

是 $\Theta(sd_3(n)+\sigma_0(n)\log n)$ 的，过不了这题。

```cpp
#include<bits/stdc++.h>
namespace Miller_Rabin{
  const int Pcnt=7;
  const int64_t p[Pcnt]={2,325,9375,28178,450775,9780504,1795265022};
  int64_t mul(int64_t a,int64_t b,int64_t p){
    return __int128(a)*b%p;
  }
  int64_t pow(int64_t a,int64_t b,int64_t p){
    int64_t ans=1;
    for(;b;a=mul(a,a,p),b>>=1)if(b&1)ans=mul(ans,a,p);
    return ans;
  }
  bool prime(int64_t x){
    if(x<3||x%2==0)return x==2;
    int64_t u=x-1,t=0;
    while(u%2==0) u/=2,++t;
    int64_t ud[]={2,325,9375,28178,450775,9780504,1795265022};
    for(int64_t a:ud){
      int64_t v=pow(a,u,x);
      if(v==1||v==x-1||v==0) continue;
      for(int j=1;j<=t;j++){
        v=mul(v,v,x);
        if(v==x-1&&j!=t){v=1;break;}
        if(v==1) return 0;
      }
      if(v!=1) return 0;
    }
    return 1;
  }
}using Miller_Rabin::prime;

typedef std::complex<double> C;
typedef int32_t i32;
typedef int64_t i64;

const double PI2=6.2831853071795864769l;
const i32 MAXS=16,MAXN=104000,MAXA=64;
const i64 P=998244353;

i64 T,s,p[MAXA],a[MAXA];
i64 nCr[MAXA<<1][MAXA],Inv[MAXA<<1];
struct Vec{
  i32 t[MAXS];
  Vec(){memset(t,0,sizeof(i32)*MAXS);}
  bool next(Vec v,i32 w=-1){for(i32 i=0;i!=s;i++){if(i==w||t[i]==v[i]){t[i]=0;continue;}t[i]++;return 1;}return 0;}
  i32&operator[](i32 x){return t[x];}
  bool operator+=(Vec v){for(i32 i=0;i!=s;i++)if((t[i]+=v[i])>a[i])return 0;return 1;}
  Vec operator-(Vec v){Vec x;for(i32 i=0;i!=s;i++)x[i]=t[i]-v[i];return x;}
};
i64 fpow(i64 a,i64 n=P-2){i64 x=1;for(;n;(a*=a)%=P,n>>=1)if(n&1)(x*=a)%=P;return x;}

i64 M(Vec v){i64 x=0;for(i64 i=0,w=1;i!=s;w*=(a[i++]+1))x+=v[i]*w;return x;}
i64 D(Vec v){i64 x=1;for(i64 i=0;i!=s;i++)x*=(v[i]+1);return x;}
i64 S(Vec v){i64 x=0;for(i64 i=0;i!=s;i++)x+=v[i];return x;}
i64 V(Vec v){i64 x=1;for(i64 i=0;i!=s;i++)x=x*powl(p[i],v[i])+.5;return x;}

void Init(){
  for(i32 i=1;i!=MAXA<<1;i++)Inv[i]=fpow(i);
  for(i32 i=0,j=1;i!=MAXA<<1;i++)
    for(nCr[i][0]=1,j=1;j<=i&&j!=MAXA;j++)
      nCr[i][j]=(nCr[i-1][j-1]+nCr[i-1][j])%P;
}
void exp(int*f,Vec n){
  static int g[MAXN];Vec d,i;g[0]=1,d.next(n);
  do{do g[M(d)]=(g[M(d)]+S(i)*f[M(i)]%P*g[M(d-i)])%P;
    while(i.next(d));g[M(d)]=g[M(d)]*fpow(S(d))%P;
  }while(d.next(n));
  do f[M(d)]=g[M(d)],g[M(d)]=0;while(d.next(n));
}
int slove(Vec n){
  static int f[MAXN];
  std::map<i64,i32> Pn;Pn[2]=0;
  for(int i=1;i!=s;i++){
    Vec d_1,t;i64 fact=p[i]-1,j=0,k=0;
    for(auto [p_w,w]:Pn)
      while(fact%p_w==0)d_1[w]++,fact/=p_w;
    if(fact!=1)d_1[0]=MAXA;
    do{do f[M(t)]=(f[M(t)]+(j&1?1ll:P-1)*Inv[j+k]%P*nCr[j+k][j])%P;
      while((t[i]=++k)<=a[i]);t[i]=k=0;++j;
    }while(t+=d_1);Pn[p[i]]=i;
  }
  Vec d;d.next(n);do{
    if(Pn.count(V(d)+1)||!prime(V(d)+1))continue;
    Vec t;int j=1;
    for(;t+=d;j++)f[M(t)]=(f[M(t)]+(j&1?1ll:P-1)*Inv[j])%P;
  }while(d.next(n));
  exp(f,n);i64 ans=0;
  do ans=(ans+D(n-d)*(2ll*f[M(d)]+(M(d)%(a[0]+1)?P-f[M(d)-1]:0)))%P;
  while(d.next(n));memset(f,0,sizeof(i32)*D(n));return ans;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  Init();std::cin>>T;
  while(T--){
    std::cin>>s;Vec n;
    for(int i=0;i!=s;i++)std::cin>>p[i]>>a[i],n[i]=a[i];
    if(p[0]!=2){std::cout<<"2\n";continue;}
    std::cout<<slove(n)<<"\n";
  }
  return 0;
}
```

# 后话

我其实还有几个小疑问：  

本题中 $\alpha_i$ 都很小，是否有更快的方法进行卷积？  
总时间复杂度能不能做到 $\Theta(\sigma_0(n)\log n)$？

本题中的几个数论函数如何快速求前缀和？各种筛法似乎都不可用。

不过这就在我的能力之外了，欢迎各位大佬解决。

---

