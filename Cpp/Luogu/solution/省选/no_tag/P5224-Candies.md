# Candies

## 题目背景

JerryC 有一大袋糖果，他正以 $1\ \textrm{t/ms}$ 的速度食用着这一袋糖果......

## 题目描述

JerryC 的糖果有 $N$ 箱（两两之间不同）。他一开始想挑 $M$ 箱出来，但是觉得吃起来不过瘾，所以又想要多拿一些出来。由于他比较喜欢数字 $K$，所以只要拿出来的糖的量 $x$（$x \ge M$）满足：$x \equiv M\pmod{K}$，JerryC 就会得到满足感。

求有多少种方案使得 JerryC 得到满足感。请输出方案数 $\bmod\ 1004535809$ 的结果。

## 说明/提示

样例解释：

可以拿出来：$2$ 箱 $5$ 箱 $8$ 箱，组合数算一下就是了：

$$\binom{10}{2}+\binom{10}{5}+\binom{10}{8}=342$$

数据范围：

|测试点编号|$N\le$|$K\le$|
|:-------:|:-------:|:-------:|
|$1$|$1$|$1$|
|$2-3$|$10^6$|$10$|
|$4-8$|$10^{12}$|$100$|
|$9-12$|$10^{15}$|$10^3$|
|$12-20$|$10^{18}$|$10^4$|

$0 \leq M < K$。

## 样例 #1

### 输入

```
10 2 3
```

### 输出

```
342
```

# 题解

## 作者：CYJian (赞：9)

## Candies

相信大佬都做过[这道题](https://www.luogu.org/problemnew/show/P3746)，Candies这道题是我在学长讲完那一道数据比较弱的题目yy出来的优化做法。(如果是任意模数就需要MTT了。。)

### 15分做法

枚举。。不多BB..

### 15分做法（看起来强一点的做法）

还是上面那一道题的做法吧。。

我们可以设状态$f[i][j]$表示从$i$箱糖中选择箱数为$\% k \equiv j$的方案数，然后考虑加入一箱会有什么影响：

显然是加入的这一箱可以选，也可以不选。所以我们有转移：

$$f[i][j] = f[i-1][j] + f[i-1][(j-1+k)\%k]$$

然后就可以拿到$15$分的高分。。

### 40分做法

发现$k$还是比较小，考虑矩阵快速幂。

然后就可以构造出一个$k \ast k$的矩阵，然后就可以$O(k^3logN)$做了。。

### 60分做法(优化1)

这个时候$k$变大了，考虑优化。

发现构造的矩阵是一个循环矩阵(此题中为下一行为上一行向右转1得到)

然后就可以考虑每一次做矩阵乘法只需要用第一行乘就行了。因为其他行的答案都可以用旋转得到。

这样复杂度就是$O(k^2 \ast logN)$

### 60分做法(优化2)

考虑合并$x$箱的答案$f[x]$和$y$箱的答案$f[y]$

发现可以有一个暴力转移：

$f[x+y][(i + j) \% k] = \sum f[x][i] \ast f[y][j]$

简单的乘法原理应该没有问题吧。。

然后就发现可以倍增，这样就预处理出每一个二进制位的$f[x]$，然后根据$N$的二进制位合并答案就好了。

复杂度$O(k^2 \ast logN)$

### 100分做法

发现上面的优化2是一个卷积的形式，所以可以$NTT$优化。只不过卷积乘出来超出k的部分需要把多的部分弄进$k$的范围内。简单来说，就是$f[i](i>k)$就要加到$f[i\%k]$里面。

发现题目非常友好~~没有要写MTT~~，给出的模数的原根就是$3$.

复杂度$O(k \ast logk \ast logN)$

代码太丑了，就不放了。。

---

## 作者：Weng_Weijie (赞：8)

由于

$(1+x)^n=\displaystyle\sum_{i=0}^n\binom nix^i$

此时若将指数模 $k$ 相同的放在一起就是答案了

这其实就是循环卷积

于是题目求的就是 $(1+x)^n\bmod(x^k-1)$

多项式快速幂+FFT即可

复杂度 $O(k\log k\log n)$

当 $k$ 为 $2$ 的幂或者有其他特殊性质时可以 $O(k\log k)$

```cpp
#include <iostream>
#include <algorithm>

const int mod = 1004535809;
const int N = 32768;
using LL = long long;
int wn[N], w[N], rev[N], lim, s, f[N], tmp[N];
int pow(int x, int y, int ans = 1) {
    for (; y; y >>= 1, x = (LL) x * x % mod)
        if (y & 1) ans = (LL) ans * x % mod;
    return ans;
}
void reduce(int &x) {
    x += x >> 31 & mod;
}
void fftinit(int len) {
    wn[0] = lim = 1, s = -1; while (lim < len) lim <<= 1, ++s;
    for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const int g = pow(3, (mod - 1) / lim);
    for (int i = 1; i < lim; ++i) wn[i] = (LL) wn[i - 1] * g % mod;
}
void fft(int *A, int typ) {
    for (int i = 0; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; ++k) {
                const int x = A[k + j], y = (LL) A[k + j + i] * w[k] % mod;
                reduce(A[k + j] += y - mod), reduce(A[k + j + i] = x - y);
            }
    }
    if (!typ) {
        const int il = pow(lim, mod - 2);
        for (int i = 0; i < lim; ++i) A[i] = (LL) A[i] * il % mod;
        std::reverse(A + 1, A + lim);
    }
}
LL n;
int m, k;
void poly_pow(LL n) {
    if (n == 1) { f[0] = 1, f[1 % k]++; return; }
    poly_pow(n >> 1);
    fft(f, 1);
    for (int i = 0; i < lim; ++i) f[i] = (LL) f[i] * f[i] % mod;
    fft(f, 0);
    for (int i = k + k - 2; i >= k; --i)
        reduce(f[i - k] += f[i] - mod), f[i] = 0;
    if (n & 1) {
        for (int i = 0; i < k; ++i) tmp[i] = f[i];
        for (int i = 0; i < k; ++i) reduce(tmp[(i + 1) % k] += f[i] - mod);
        for (int i = 0; i < k; ++i) f[i] = tmp[i];
    }
}
int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    std::cin >> n >> m >> k, fftinit(k + k - 1);
    poly_pow(n);
    std::cout << f[m] << std::endl;
    return 0;
}

```

---

## 作者：NaCly_Fish (赞：4)

看一下题我们就会发现，题目让我们求这个东西：  
$$\large \sum\limits_{i=0}^{n/k}\binom{n}{m+ki}$$  
好像有点不好算呢qwq  

根据二项式定理，我们知道：  
$$\large (x+1)^n=\sum\limits_{i=0}^n\binom{n}{i}x^i$$  
于是我们就把这个多项式的$m,m+k,m+2k...$次项系数都加起来，就是答案啦！  

于是你高高兴兴地把多项式快速幂的板子复制过来，发现$n$的范围：  
$$\large n\le10^{18}$$  
多项式不可能这么长，咋办啊qaq  

这个时候就需要用到**循环卷积**。  
在我们每次做多项式乘法时，对于$x$次项的系数，把它加到$x\text{ mod }k$次项上，然后把这一项设为$0$即可。  
其它地方都是板子，直接写一个倍增快速幂就可以通过此题啦qwq  

```cpp
// luogu-judger-enable-o2
#include<cstdio> 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define ll long long
#define N 400007
#define reg register
#define p 1004535809
using namespace std;

struct poly{
    int a[N];
    int t;
};

int rev[N];
int inv;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

inline void NTT(poly &f,int type,int lim){
    for(reg int i=1;i<=lim;++i){
        if(i>=rev[i]) continue;
        swap(f.a[i],f.a[rev[i]]);
    }
    reg int w,r,x,y,rt;
    for(reg int mid=1;mid<lim;mid<<=1){
        r = mid<<1;
        rt = power(3,(p-1)/r);
        if(type==-1) rt = power(rt,p-2);
        for(reg int j=0;j<lim;j+=r){
            w = 1;
            for(reg int k=0;k<mid;++k){
                x = f.a[j+k];
                y = (ll)w*f.a[j+k+mid]%p;
                f.a[j+k] = (x+y)%p;
                f.a[j+k+mid] = (x-y+p)%p;
                w = (ll)w*rt%p;
            }
        }
    }
}

ll n;
int m,k,lim,l;
poly F;

poly power(poly f,ll n){
    poly g,h;
    g.t = f.t;
    memset(g.a,0,sizeof(g.a));
    g.a[0] = 1;
    while(n){
        if(n&1){
            h = f;
            NTT(h,1,lim),NTT(g,1,lim);
            for(reg int i=0;i<=lim;++i)
                g.a[i] = (ll)g.a[i]*h.a[i]%p;
            NTT(g,-1,lim);
            for(reg int i=0;i<=lim;++i)
                g.a[i] = (ll)g.a[i]*inv%p;
            for(reg int i=k;i<=lim;++i){
                g.a[i%k] = (g.a[i%k]+g.a[i])%p;    
                g.a[i] = 0;
            }
        } 
        n >>= 1;
        if(!n) break;
        NTT(f,1,lim);
        for(reg int i=0;i<=lim;++i)
            f.a[i] = (ll)f.a[i]*f.a[i]%p;
        NTT(f,-1,lim);
        for(reg int i=0;i<=lim;++i)
            f.a[i] = (ll)f.a[i]*inv%p;
        for(reg int i=k;i<=lim;++i){
            f.a[i%k] = (f.a[i%k]+f.a[i])%p;
            f.a[i] = 0;
        }    
    }
    return g;
}

signed main(){ 
    scanf("%lld%d%d",&n,&m,&k);
    lim = 1,l = -1;
    while(lim<=(k<<1)){
        lim <<= 1;
        ++l;
    }
    inv = power(lim,p-2);
    for(reg int i=1;i<=lim;++i) 
        rev[i] = (rev[i>>1]>>1)|((i&1)<<l);
    F.t = lim;
    F.a[0] = F.a[1] = 1;    
    F = power(F,n);
    printf("%d",F.a[m]);
    return 0;
}
```

---

