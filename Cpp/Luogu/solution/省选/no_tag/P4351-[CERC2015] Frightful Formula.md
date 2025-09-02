# [CERC2015] Frightful Formula

## 题目描述

定义一个矩阵 $F$，其中第一行和第一列是给定的，计算矩阵方法如下：

矩阵的第一列是序列  $l$：

 $F[k,1]=$  $l _ k$

矩阵的第一行是序列  $t$：

 $F[1,k]=$  $t _ k$

其他元素使用给定的递归公式进行计算：

$F[i,j]=a \times F[i,j-1]+b \times F[i-1,j]+c$。

现在要求找求出 $F[n,n]$ 模 $10^6+3$ 的值。

## 样例 #1

### 输入

```
3 0 0 0 
0 0 2 
0 3 0```

### 输出

```
0```

## 样例 #2

### 输入

```
4 3 5 2 
7 1 4 3 
7 4 4 8```

### 输出

```
41817```

# 题解

## 作者：岸芷汀兰 (赞：10)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/P4351)

[codeforces原题](https://codeforces.com/gym/101480)

# 二、思路：

一道数学题。

先不管公式中的常数项 $c$，首先考虑第一行和第一列的贡献。

对于位于 $(i,1)$ 的数 $x$，它的贡献为：$\dbinom{2n - i-2}{n-i}\times a^{n-1}b^{n-i}x$。

对于位于 $(1,j)$ 的数 $x$，它的贡献为：$\dbinom{2n-j-2}{n-j}\times a^{n-j}b^{n-1}x$。

再来考虑常数项 $c$ 的影响。我们可以发现，加入在位置 $(i,j)$ 上加了一个常数 $c$，那么这个 $c$ 最终就会“演变成”$\dbinom{2n-i-j}{n-i}a^{n-j}b^{n-i}c$。这种演变的思路也可以参见[这道题](https://www.cnblogs.com/little-aztl/p/14880260.html)。

关于为什么是这样的，我们可以这么考虑：假设一个人从 $(i,j)$ 要走到 $(n,n)$，每向右走都要乘 $a$，向下走都要乘 $b$，那么乘 $a$ 的次数和乘 $b$ 的次数都是确定的。而又因为一共有 $\dbinom{2n-i-j}{n-i}$ 种走法，所以最终的总贡献就是上面那个式子啦！

又因为 $\forall 2\leq i,j\leq n$，$(i,j)$ 都要加上常数 $c$。所以它们的总贡献为 $c\sum\limits_{i=2}^n\sum\limits_{j=2}^n\dbinom{2n-i-j}{n-i}b^{n-i}a^{n-j}$。

考虑这个式子怎么进行化简。设 $k=2n-i-j$，更改枚举顺序，有：
$$
\begin{aligned}
\text{Original Formula} &= c\sum\limits_{k=0}^{2n-4}\left(\sum\limits_{i=\max\{0,k-n+2\}}^{\min\{k,n-2\}}\dbinom{k}{i}b^{i}a^{k-i} \right)
\end{aligned}
$$
将和式分为两部分。

第一部分：

$$
\begin{aligned}
\text{The First Part} &= c\sum\limits_{k=0}^{n-2}\sum\limits_{i=0}^k\dbinom{k}{i} b^i a^{k-i}\\
&= c\sum\limits_{k=0}^{n-2}(a+b)^k
\end{aligned}
$$

第二部分：
$$
\begin{aligned}
\text{The Second Part}&=c\sum\limits_{k=n-1}^{2n-4}\left(\sum\limits_{i=k-(n-2)}^{n-2} \dbinom{k}{i}b^i a^{k-i} \right)\\
&=c\sum\limits_{k=n-1}^{2n-4}f_k
\end{aligned}
$$
其中 $f_k=\sum\limits_{i=k-(n-2)}^{n-2} \dbinom{k}{i}b^i a^{k-i} $。则根据组合数的递推公式，可以得到
$$
f_k=(a+b)f_{k-1}-\dbinom{k-1}{k-n+1}b^{k-n+1}a^{n-1}-\dbinom{k-1}{n-2}b^{n-1}a^{k-n+1}
$$
总时间复杂度：$O(n)$。

# 三、代码：

```cpp
#include <iostream> // 目前是洛谷rk1
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
#define FILEIN(s) freopen(s, "r", stdin)
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int MAXN = 200005, MOD = 1000003;

int n, a, c, b;
long long factor[MAXN << 1], facinv[MAXN << 1], ans;
long long powa[MAXN], powb[MAXN], f[MAXN << 1];

inline long long power(long long a, long long b) {
    long long res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
    }
    return res;
}

inline void prework(void) {
    factor[0] = 1;
    for (int i = 1; i <= 2 * n; ++ i) factor[i] = factor[i - 1] * i % MOD;
    facinv[2 * n] = power(factor[2 * n], MOD - 2);
    for (int i = 2 * n - 1; i >= 0; -- i) facinv[i] = facinv[i + 1] * (i + 1) % MOD;
    powa[0] = 1; powb[0] = 1;
    for (int i = 1; i <= n; ++ i)
        powa[i] = powa[i - 1] * a % MOD,
        powb[i] = powb[i - 1] * b % MOD;
}

inline long long C(int n, int m) {
    if (n < m) return 0;
    return factor[n] * facinv[m] % MOD * facinv[n - m] % MOD;
}

inline long long get_f(int k) {
    long long res = 0;
    for (int i = k - (n - 2); i <= n - 2; ++ i)
        (res += C(k, i) * powb[i] % MOD * powa[k - i] % MOD) %= MOD;
    return res;
}

int main() {
    n = read(); a = read(); b = read(); c = read();
    prework();

    for (int i = 1; i <= n; ++ i) {
        long long x = read();
        if (i == 1) continue;
        long long tmp = C(2 * n - i - 2, n - i) * powa[n - 1] % MOD * powb[n - i] % MOD * x;
        (ans += tmp) %= MOD;
    }

    for (int j = 1; j <= n; ++ j) {
        long long x = read();
        if (j == 1) continue;
        long long tmp = C(2 * n - j - 2, n - j) * powa[n - j] % MOD * powb[n - 1] % MOD * x;
        (ans += tmp) %= MOD;
    }

    {
        long long tmp = 1;
        for (int k = 0; k <= n - 2; ++ k) {
            if (k != 0) tmp = tmp * (a + b) % MOD;
            (ans += c * tmp % MOD) %= MOD;
        }
    }

    f[n - 1] = get_f(n - 1);
    for (int k = n - 1; k <= 2 * n - 4; ++ k) {
        if (k != n - 1) {
            f[k] = (a + b) * f[k - 1] % MOD
                   - C(k - 1, k - n + 1) * powb[k - n + 1] % MOD * powa[n - 1] % MOD
                   - C(k - 1, n - 2) * powb[n - 1] % MOD * powa[k - n + 1] % MOD;
            f[k] %= MOD;
            if (f[k] < 0) f[k] += MOD;
        }
        (ans += c * f[k] % MOD) %= MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：foreverlasting (赞：4)

[同步发表在我的博客里哦](https://foreverlasting1202.github.io/)

就是一道推式子。

首先考虑$F[i,1]$和$F[1,i]$的贡献，这个很好求。考虑这个点到$F[n,n]$每次坐标加一走过去的方案数，显然是$C(n+n-i-2,n-i)$，在这基础上将$a$和$b$考虑进去就可以了。

然后是考虑$c$的贡献，这个式子有点长。稍微组合数推一下，大概长成这样$c\sum_{i=2}^n \sum_{j=2}^n (2\ast n-i-j)!\ast \frac {a^{n-j}}{(n-j)!}\ast \frac {b^{n-i}}{(n-i)!}$。

这里显然可以NTT，但模数很丑，要任意模数。所以正解肯定有更好的方法。

我们考虑斜对角线的贡献。我们发现每条相邻斜线之间的贡献都是有递推关系的。显然在主斜对角线之前的任意斜线的总贡献为其上一斜线的总贡献$\ast (a+b)$。同时经过主斜对角线后贡献显然会算多，于是每次减掉多余的贡献就可以了。

显然最小的斜线贡献为$1$。

code:
```cpp
//2019.2.26 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int kcz=1000003;
const int N=4e5+10;
namespace MAIN{
    inline int mul(const res &x,const res &y){
        return 1LL*x*y%kcz;
    }
    inline int qpow(res x,res y){
        res ret=1;
        while(y){
            if(y&1)ret=mul(ret,x);
            y>>=1,x=mul(x,x);
        }
        return ret;
    }
    inline void add(res &x,const res &y){
        x+=y,x>=kcz?x-=kcz:1,x<0?x+=kcz:1;
    }
    inline int Add(const res &x,const res &y){
        return x+y>=kcz?x+y-kcz:(x+y<0?x+y+kcz:x+y);
    }
    int n,a,b,c;
    int fac[N],inv[N];
    inline void pre(){
        fac[0]=fac[1]=inv[0]=inv[1]=1;
        for(res i=2;i<=2*n;i++)fac[i]=mul(fac[i-1],i),inv[i]=mul(inv[kcz%i],kcz-kcz/i);
        for(res i=2;i<=2*n;i++)inv[i]=mul(inv[i-1],inv[i]);
    }
    inline int C(const res &x,const res &y){
        return x<y?0:mul(fac[x],mul(inv[y],inv[x-y]));
    }
    int ans;
    int pwa[N],pwb[N];
    inline void MAIN(){
        n=read(),a=read(),b=read(),c=read(),pre();
        pwa[0]=pwb[0]=1;
        for(res i=1;i<=n;i++)pwa[i]=mul(pwa[i-1],a),pwb[i]=mul(pwb[i-1],b);
        for(res i=1;i<=n;i++)add(ans,mul(read(),i>1?mul(C(2*n-i-2,n-i),mul(pwa[n-1],pwb[n-i])):0));
        for(res i=1;i<=n;i++)add(ans,mul(read(),i>1?mul(C(2*n-i-2,n-i),mul(pwa[n-i],pwb[n-1])):0));
        res now=1,ab=Add(a,b);
        for(res i=1;i<=n-2;i++)now=mul(now,ab),add(ans,mul(now,c));
        for(res i=1;i<=n-2;i++){
            res v1=mul(C(n+i-3,i-1),mul(pwa[i-1],pwb[n-2])),v2=mul(C(n+i-3,i-1),mul(pwa[n-2],pwb[i-1]));
            now=Add(mul(Add(now,-Add(v1,v2)),ab),Add(mul(v1,a),mul(v2,b))),add(ans,mul(now,c));
        }
        printf("%d\n",Add(ans,c));
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```
以上代码轻松跑了LG和bzoj的rnk1.

---

## 作者：Aleph1022 (赞：3)

试着用生成函数导了一下递推式，不过在这里表现不出什么很大的优势（

首先自然考虑每个 $l_k,t_k$ 的贡献。不难发现分别是 $(k,2),(2,k)$ 走到 $(n,n)$ 的路径数，因此分别是
$$
l_k \binom{2n-k-2}{n-2} a^{n-1} b^{n-k},\quad t_k \binom{2n-k-2}{n-2} a^{n-k} b^{n-1}
$$

当然，$(1,1)$ 是没有贡献的。

接下来考虑 $c$，显然其等价于在每个 $(x,y)$ $(x,y\ge 2)$ 处赋予一个 $c$ 的权值，则其贡献为
$$
c \binom{2n-x-y}{n-x} a^{n-x} b^{n-y}
$$

略微换元，也就是需要计算
$$
\sum\limits_{i=0}^{n-2} \sum\limits_{j=0}^{n-2} \binom{i+j}i a^i b^j
$$

令 $k=n-2$，设
$$
A(x) = \sum\limits_{i=0}^k a^i \frac{x^i}{i!},\quad B(x) = \sum\limits_{i=0}^k b^i \frac{x^i}{i!},\quad F(x) = A(x)B(x)
$$

那么所求即 $\sum\limits_{i=0}^{2k} i! [x^i] F(x)$。

我们先来考虑 $A,B$ 的 ODE。这是很经典的：
$$
A'=aA-a^{k+1}\frac{x^k}{k!},\quad B'=bB-b^{k+1}\frac{x^k}{k!}
$$

然后
$$
\begin{aligned}
F'
&= (AB)' \\
&= AB' + A'B \\
&= A\left(bB-b^{k+1}\frac{x^k}{k!}\right) + B\left(aA-a^{k+1}\frac{x^k}{k!}\right) \\
&= (a+b)F - (Ab^{k+1} + Ba^{k+1}) \frac{x^k}{k!}
\end{aligned}
$$

令 $f_i = i! [x^i] F(x)$，对上式提取系数
$$
f_{i+1} = (a+b)f_i - \binom ik (b^{k+1} a^{i-k}+a^{k+1} b^{i-k})
$$

即可递推。

---

## 作者：Fading (赞：3)

两位学长 tql，这个棋盘游走 dp 转组合贡献的经典题还是很妙的~

我来一个具体一点的...

$$f_{i,j}=Af_{i,j-1}+Bf_{i-1,j}+C$$

考虑贡献。

对于一个点$(1,x)(1\leq x\leq n)$。

它对答案$(n,n)$的贡献为什么？

首先他的转移一定从$(2,x)$开始。那么$(2,x)$到$(n,n)$的路径数是什么？

是

$$C_{n-2+n-x}^{n-2}=C_{2n-x-2}^{n-2}$$

它乘了多少次$A?$

是$n-x$次。

乘了多少次$B?$

是$n-1$次。

所以$(1,x)$对答案的贡献是

$$t_1C_{2n-x-2}^{n-2}A^{n-x}B^{n-1}$$

同理$(x,1)$对答案的贡献是

$$l_1C_{2n-x-2}^{n-2}A^{n-1}B^{n-x}$$

注意$(1,1)$的贡献为$0$。

不急，还有$C$的贡献呢。

对于一个点$(x,y)(2\leq x,y\leq n)$，他到$(n,n)$的路径条数是$C_{2n-x-y}^{n-x}$

同理，贡献就是$C_{2n-x-y}^{n-x}A^{n-y}B^{n-x}$

我们对于$(1,x),(x,1)(1\leq x\leq n)$的贡献，直接乘上本身算入$F_{n,n}$。

对于$(x,y)(2\leq x,y\leq n)$，我们要把贡献乘上$C$。

前面这个可以$O(n)$算，后面这个怎么办？

原式$=$

$$C\sum_{i=2}^n\sum_{j=2}^nC_{2n-i-j}^{n-i}A^{n-j}B^{n-i}$$

$$=C\sum_{i=2}^n\sum_{j=2}^n\frac {(2n-i-j)!}{(n-i)!(n-j)!}A^{n-j}B^{n-i}$$

$$=C\sum_{i=2}^n\sum_{j=2}^n(2n-i-j)!\frac {B^{n-i}A^{n-j}}{(n-i)!(n-j)!}$$

枚举$i+j$，设为$d$

$$=C\sum_{d=4}^{2n}(2n-d)!\sum_{i=2}^n\sum_{j=2}^n[i+j==d]\frac {B^{n-i}A^{n-j}}{(n-i)!(n-j)!}$$

看到后面的卷积形式了吧。

设

$$f_i=\frac {B^{n-i}}{(n-i)!},g_i=\frac {A^{n-i}}{(n-i)!}$$

特别地，

$f_0=f_1=g_0=g_1=0$

那么设$h=f \times g$，原式等于：

$$=C\sum_{d=4}^{2n}(2n-d)!h(d)$$

最后把贡献加起来即可，不要忘记用$MTT\sim$

时间复杂度$O(n\log_2n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 1000003
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
double pi=acos(-1);
ll f[1500002],h[1500002],g[1500002],n,m,a,b,c,xx,yy,r[1500002],inv[1200001],fac[1200001];
struct Complex{
    double x,y;
    Complex(double xx=0,double yy=0)
    {x=xx,y=yy;}
}X[1500002],A[1500002],B[1500002],C[1500002],D[1500002],w[1500002];
inline Complex operator + (const Complex &a,const Complex &b){
    return Complex(a.x+b.x,a.y+b.y);
}
inline Complex operator - (const Complex &a,const Complex &b){
    return Complex(a.x-b.x,a.y-b.y);
}
inline Complex operator * (const Complex &a,const Complex &b){
    return Complex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
inline void swap(Complex &a,Complex &b){
    Complex t=a;a=b;b=t;
}
inline void FFT(Complex f[],int id,int lim){
    for (int i=0;i<lim;i++){
        if (i>r[i]) swap(f[r[i]],f[i]);
    }
    for (int len=1;len<lim;len<<=1){
    	Complex gen(cos(pi/len),id*sin(pi/len));
        for (int i=0;i<lim;i+=len<<1){
            Complex *f1=f+i,*f2=f1+len;
            for (int j=0;j<len;j++){
            	Complex WW=w[lim/len*j];
            	if (id==-1) WW.y=-WW.y;
                Complex x=f1[j],y=f2[j]*WW;
                f1[j]=x+y;f2[j]=x-y;
            }
        }
    }
    if (id==1) return;
    for (int i=0;i<lim;i++) f[i].x=fabs(f[i].x/lim+0.5);
}
const ll sqq=32768;
int lim,len;
inline void MTT(ll *a,ll *b,ll *c,ll n,ll m){
    lim=1,len=0;
    while (lim<=(n+m)) lim<<=1,len++;
    for (int i=0;i<lim;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    for (int i=0;i<lim;i++){
        A[i].x=A[i].y=B[i].x=B[i].y=C[i].x=C[i].y=D[i].x=D[i].y=0;
    }
    for (int len=1;len<lim;len<<=1){
    	for (int j=0;j<len;j++){
    		w[lim/len*j]=(Complex){cos(j*pi/len),sin(j*pi/len)};
        }
    }
    for (int i=0;i<n;i++) A[i].x=a[i]/sqq,B[i].x=a[i]%sqq;
    for (int i=0;i<m;i++) C[i].x=b[i]/sqq,D[i].x=b[i]%sqq;
    FFT(A,1,lim);FFT(B,1,lim);FFT(C,1,lim);FFT(D,1,lim);
    Complex tmp1,tmp2;
    for (int i=0;i<lim;i++){
    	tmp1=A[i]*C[i];tmp2=D[i]*B[i];
        B[i]=B[i]*C[i]+A[i]*D[i];A[i]=tmp1;D[i]=tmp2;
    }
    FFT(A,-1,lim);FFT(B,-1,lim);FFT(D,-1,lim);
    for (int i=0;i<lim;i++){
    	c[i]=(c[i]+(ll)(A[i].x)*sqq%ljc*sqq%ljc)%ljc;
    	c[i]=(c[i]+(ll)(B[i].x)*sqq%ljc)%ljc;
    	c[i]=(c[i]+(ll)(D[i].x))%ljc;
    }
}
ll L[1000002],miA[1000002],miB[1000002],T[1000002];
inline ll getC(ll n,ll m){
    return fac[n]*inv[m]%ljc*inv[n-m]%ljc;
}
signed main(){
    n=read(),a=read(),b=read(),c=read();
    for (int i=1;i<=n;i++) L[i]=read();
    for (int i=1;i<=n;i++) T[i]=read();
    fac[0]=inv[0]=inv[1]=miA[0]=miB[0]=1;
    for (ll i=1;i<=2*n;i++) miA[i]=miA[i-1]*a%ljc,miB[i]=miB[i-1]*b%ljc,fac[i]=fac[i-1]*i%ljc;
    for (ll i=2;i<=2*n;i++) inv[i]=(ljc-(ljc/i)*inv[ljc%i]%ljc)%ljc;
    for (ll i=1;i<=2*n;i++) inv[i]=inv[i-1]*inv[i]%ljc;
    ll ans=0;
    for (int i=2;i<=n;i++) ans=(ans+T[i]*getC(2*n-i-2,n-2)%ljc*miA[n-i]%ljc*miB[n-1]%ljc)%ljc;
    for (int i=2;i<=n;i++) ans=(ans+L[i]*getC(2*n-i-2,n-2)%ljc*miA[n-1]%ljc*miB[n-i]%ljc)%ljc;
    for (int i=2;i<=n;i++) f[i]=miB[n-i]*inv[n-i]%ljc;
    for (int i=2;i<=n;i++) g[i]=miA[n-i]*inv[n-i]%ljc;
    MTT(f,g,h,n+1,n+1);
    for (int i=4;i<=2*n;i++) ans=(ans+fac[2*n-i]*h[i]%ljc*c%ljc)%ljc;
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Iscream2001 (赞：3)

这题第一个题解。。

一道推式子的好题。。。

首先要发现给出的第一行和第一列只是吓唬你的。。。

对于第一行和第一列，我们可以分别对每个元素算它对答案的贡献。

一个元素对答案的贡献就是：这个点到终点的路径数 * 元素的值 * A和B的影响

然后考虑C的贡献，思路和上面几乎一样，但是每个点都有一个C，推完式子会发现是一个卷积形式，然后上任意模数NTT就可以了

代码什么的还是不发了。。。
这里就给个思路。。。

---

## 作者：lgswdn_SA (赞：2)

思路和楼下 srz 的差不多，但是加了一点自己思考中的细节补充（

答案可以有以下三个部分组成：第一行对答案做的贡献；第一列对答案做的贡献；$c$ 对答案做的贡献。考虑第一行 $(1,k)$ 对答案做的贡献，组合意义为从 $(1,k)$ 走到 $(n,n)$，向右走贡献为 $a$，向下走贡献为 $b$ 贡献总和。由于 $(1,k)$ 只能走到 $(2,k)$，所以实际上真正可以开始自由走的出发点是 $(2,k)$。所以 $(1,k)$ 的贡献为：
$$
\binom{2n-2-k}{n-2}a^{n-k}b^{n-1}f_{1,k}
$$
同理，$(k,1)$ 的贡献为：
$$
\binom{2n-2-k}{n-2}a^{n-1}b^{n-k}f_{k,1}
$$
考虑能不能消掉 $c$ 的贡献。找到一个 $x=\frac{c}{1-a-b}$ 满足 $x=ax+bx+c$，可以转化成 $f_{i,j}-c=a(f_{i,j-1}-x)+b(f_{i-1,j}-x)$。设 $g=f-x$，则我们可以直接求出 $g_{n,n}$ 即可。

不过如果没有 $x$，即 $a+b\equiv 1$ 呢？我们带入。$f_{i,j}=a\cdot f_{i,j-1}+(1-a)\cdot f_{i-1,j}+c$。我们希望求出一个 $y$，满足：
$$
f_{i,j}-y_{i,j}=a\cdot (f_{i,j-1}-y_{i,j-1})+(1-a)\cdot (f_{i-1,j}-y_{i,j-1})
$$
即
$$
c-y_{i,j}=-a\cdot y_{i,j-1}+a\cdot y_{i,j-1}-y_{i,j-1}
$$
为了消去 $a$，我们需要 $y_{i,j-1}=y_{i-1,j}$。那么 $y$ 应该是一个关于 $(i+j)$ 的式子（因为两个东西的下标和相等）。设 $y=k(i+j)$。解方程可以得到 $k=c$。于是，我们有 $g_{i,j}=f_{i,j}-c(i+j)$。我们求出 $g_{n,n}$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=4e5+9,mod=1e6+3;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,a,b,c,l[N],t[N],pwa[N],pwb[N],fac[N],inv[N],ifac[N];
void pre(int n) {
	inv[0]=inv[1]=fac[0]=ifac[0]=pwa[0]=pwb[0]=1;
	rep(i,1,n) fac[i]=fac[i-1]*i%mod;
	rep(i,2,n) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	rep(i,1,n) ifac[i]=ifac[i-1]*inv[i]%mod;
	rep(i,1,n) pwa[i]=pwa[i-1]*a%mod;
	rep(i,1,n) pwb[i]=pwb[i-1]*b%mod;
}
int C(int x,int y) {
	if(x<0||y<0||x<y) return 0;
	else return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
int ksm(int x,int y,int ret=1) {
	while(y) {
		if(y%2) ret=ret*x%mod;
		x=x*x%mod, y>>=1;
	}
	return ret;
}

signed main() {
	n=read(), a=read(), b=read(), c=read();
	rep(i,1,n) l[i]=read();
	rep(i,1,n) t[i]=read();
	pre(2*n);
	if((a+b)%mod!=1) {
		int x=c*ksm((1+mod+mod-a-b)%mod,mod-2)%mod,ans=0;
		rep(i,2,n) ans=(ans+C(2*n-2-i,n-2)*pwa[n-i]*pwb[n-1]%mod*(t[i]-x))%mod;
		rep(i,2,n) ans=(ans+C(2*n-2-i,n-2)*pwa[n-1]*pwb[n-i]%mod*(l[i]-x))%mod;
		ans=(ans+x+mod)%mod;
		printf("%lld\n",ans);
	} else {
		int ans=0;
		rep(i,2,n) {
			int x=c*(1+i)%mod;
			ans=(ans+C(2*n-2-i,n-2)*pwa[n-i]*pwb[n-1]%mod*(t[i]-x))%mod;
			ans=(ans+C(2*n-2-i,n-2)*pwa[n-1]*pwb[n-i]%mod*(l[i]-x))%mod;
		}
		ans=(ans+2*c*n+mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：LastKismet (赞：0)

# Sol
我们考虑拆贡献，把贡献拆到每个点上。

首先 $(1,1)$ 点是没有贡献的。

常数 $c$ 略为复杂，我们先暂时忽略 $c$ 的影响，只考虑 $a,b$。

我们只对边界点进行分析即可（不考虑 $c$ 时非边界点无额外贡献），这里以左边界为例：

令当前点为 $(x,1)$，那么当前点产生贡献的路径其实就是 $(x,2)$ 到 $(n,n)$ 的路径。在一条路径上，会产生 $a^{n-1}b^{n-x}$ 的贡献，因为其必然右移 $n-1$ 次且必然下移 $n-x$ 次。路径的数量为 $\binom{2n-x-2}{n-2}$。你可以这么理解：共移动 $2n-x-2$ 次，在其中选 $n-2$ 次执行右移操作。不要忘了其初始贡献 $l_x$。

因此左边界点的贡献为：
$$
\sum_{i=2}^n l_i\binom{2n-i-2}{n-2}a^{n-1}b^{n-i}
$$

同理，上边界点的贡献为：
$$
\sum_{i=2}^n t_i\binom{2n-i-2}{n-2}a^{n-i}b^{n-1}
$$

接下来考虑 $c$，我们将 $c$ 的贡献拆分到各个非边界点上计算。通过类似的路径预算贡献思路，我们可以写出贡献：
$$
\sum_{i=2}^n\sum_{j=2}^nc\binom{2n-i-j}{n-i}a^{n-j}b^{n-i}
$$
值得注意的是，此处 $i,j$ 视具体实现而定，这里将 $j$ 视作横坐标的枚举，否则应互换 $a,b$ 的指数。

拆式子得：
$$
\begin{align*}
&\sum_{i=2}^n\sum_{j=2}^nc\frac{(2n-i-j)!}{(n-i)!(n-j)!}a^{n-j}b^{n-i}\\
=&\sum_{i=2}^n\sum_{j=2}^nc(2n-i-j)!\frac{b^{n-i}}{(n-i)!}\cdot\frac{a^{n-j}}{(n-j)!}
\end{align*}
$$

发现贡献中存在 $i+j$ 部分与 $i,j$ 独立部分，我们可以考虑将其转化为卷积形式：
$$
\sum_{x=4}^n\sum_{i=2}^n\sum_{j=2}^n\left[i+j=x\right]c(2n-x)!\frac{b^{n-i}}{(n-i)!}\cdot\frac{a^{n-j}}{(n-j)!}
$$

对 $\frac{b^{n-i}}{(n-i)!}$ 和 $\frac{a^{n-j}}{(n-j)!}$ 卷积即可。此处模数并不满足特殊性质，故使用 MTT。

这样我们就统计出了 $c$ 的贡献，将我们计算出的所有贡献相加即为答案。

# Code
```cpp
namespace MTT{
    int P=1e6+3;
    struct clx{
        flt x,y;
        clx(flt a=0,flt b=0){x=a,y=b;}
        inline clx operator+=(const clx &b){return x+=b.x,y+=b.y,*this;}
        friend inline clx operator+(clx a,clx b){return a+=b;}
        inline clx operator-=(const clx &b){return x-=b.x,y-=b.y,*this;}
        friend inline clx operator-(clx a,clx b){return a-=b;}
        inline clx operator*=(const clx &b){return *this=clx(x*b.x-y*b.y,x*b.y+y*b.x);}
        friend inline clx operator*(clx a,clx b){return a*=b;}
        inline clx operator!(){return clx(x,-y);}
    };
    typedef vec<ll> poly;
    typedef vec<clx> Poly;
    const flt Pi=acos(-1);
    vec<int> Rt;
    inline void fft(int lim,Poly &a,int type){
        repl(i,0,lim)if(i<Rt[i])swap(a[i],a[Rt[i]]);
        for(int mid=1;mid<lim;mid<<=1){
            clx w1(cos(Pi/mid),type*sin(Pi/mid));
            for(int j=0;j<lim;j+=(mid<<1)){
                clx w(1,0);
                repl(k,0,mid){
                    clx x=a[j+k],y=w*a[j+mid+k];
                    a[j+k]=x+y;
                    a[j+mid+k]=x-y;
                    w=w*w1;
                }
            }
        }
    }
    inline void operator*=(poly &x,poly y){
        int n=x.size(),m=y.size(),M=ceil(sqrt(P));
        int lim=1,l=0,len=n+m-1;
        while(lim<len)lim<<=1,l++;
        Rt.resize(lim);
        repl(i,0,lim)Rt[i]=(Rt[i>>1]>>1)|((i&1)<<(l-1));
        Poly p(lim),q(lim),s(lim),t(lim);
        x.resize(lim),y.resize(lim);
        repl(i,0,lim)p[i]=clx(x[i]/M,x[i]%M),q[i]=clx(y[i]/M,y[i]%M);
        fft(lim,p,1);fft(lim,q,1);
        repl(i,0,lim){
            clx ka=(p[i]+!p[i?lim-i:i])*clx(0.5,0);
            clx ba=(p[i]-!p[i?lim-i:i])*clx(0,-0.5);
            clx kb=(q[i]+!q[i?lim-i:i])*clx(0.5,0);
            clx bb=(q[i]-!q[i?lim-i:i])*clx(0,-0.5);
            s[i]=ka*kb+ka*bb*clx(0,1);
            t[i]=ba*kb+ba*bb*clx(0,1);
        }
        fft(lim,s,-1);fft(lim,t,-1);
        repl(i,0,lim){
            ll a=(ll)(s[i].x/lim+0.5)%P;
            ll b=(ll)(s[i].y/lim+0.5)%P;
            ll c=(ll)(t[i].x/lim+0.5)%P;
            ll d=(ll)(t[i].y/lim+0.5)%P;
            x[i]=a*M*M%P+(b+c)*M%P+d,x[i]%=P;
        }
        x.resize(len);
        for(auto &i:x)i=(i+P)%P;
    }
    inline void operator+=(poly &a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]+b[i],a[i]%=P;
    }
    inline void operator-=(poly &a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]-b[i]+P,a[i]%=P;
    }
    poly operator*(poly a,poly b){return a*=b,a;}
    poly operator+(poly a,poly b){return a+=b,a;}
    poly operator-(poly a,poly b){return a-=b,a;}
}using namespace MTT;

int n;
mint ans;
mint a,b,c,l[N],t[N];
mint jc[N<<1],iv[N<<1];
mint ma[N],mb[N];
#define C(n,m) (jc[n]*iv[m]*iv[(n)-(m)])

inline void Main(){
	read(n,a,b,c);
	rep(i,1,n)read(l[i]);
	rep(i,1,n)read(t[i]);
	jc[0]=1;
	rep(i,1,n<<1)jc[i]=jc[i-1]*i;
	iv[n<<1]=1/jc[n<<1];
	per(i,n<<1,1)iv[i-1]=iv[i]*i;
	ma[0]=mb[0]=1;
	rep(i,1,n)ma[i]=ma[i-1]*a,mb[i]=mb[i-1]*b;
	rep(i,2,n)ans+=l[i]*C(n-2+n-i,n-2)*ma[n-1]*mb[n-i];
	rep(i,2,n)ans+=t[i]*C(n-2+n-i,n-2)*ma[n-i]*mb[n-1];
	poly f(n+1),g(n+1);
	rep(i,2,n)f[i]=(mb[n-i]*iv[n-i]).x,g[i]=(ma[n-i]*iv[n-i]).x;
	f*=g;
	rep(i,4,n<<1)ans+=c*jc[2*n-i]*f[i];
	put(ans);
}
```

---

## 作者：0x3F (赞：0)

令 $n \gets n-2$，则答案为：

$$
[x^ny^n]\frac{{\color{red}{b\sum_{i=0}^{n}t_{i+2}x^i}}+{\color{green}{a\sum_{i=0}^{n}l_{i+2}y^i}}+{\color{blue}{\frac{c}{(1-x)(1-y)}}}}{1-ax-by}
$$

其中红色部分为：

$$
\begin{aligned}
&[x^ny^n]{\color{red}{\frac{b\sum_{i=0}^{n}t_{i+2}x^i}{1-ax-by}}}
\\
&=\sum_{i=0}^{n}t_{i+2}[x^{n-i}y^n]\frac{b}{1-ax-by}
\\
&=\sum_{i=0}^{n}t_{i+2}a^{n-i}b^{n+1}\binom{2n-i}{n}
\end{aligned}
$$

绿色部分为：

$$
\begin{aligned}
&[x^ny^n]{\color{green}{\frac{a\sum_{i=0}^{n}l_{i+2}y^i}{1-ax-by}}}
\\
&=\sum_{i=0}^{n}l_{i+2}[x^ny^{n-i}]\frac{a}{1-ax-by}
\\
&=\sum_{i=0}^{n}l_{i+2}a^{n+1}b^{n-i}\binom{2n-i}{n}
\end{aligned}
$$

蓝色部分为：

$$
[x^ny^n]{\color{blue}{\frac{c}{(1-x)(1-y)(1-ax-by)}}}
$$

当 $a+b\ne1$ 时，我们有：

$$
\begin{aligned}
&[x^ny^n]\frac{c}{(1-x)(1-y)(1-ax-by)}
\\
&=\frac{c}{a+b-1}[x^ny^n]\left(\frac{b}{(1-x)(1-ax-by)}+\frac{a}{(1-y)(1-ax-by)}-\frac{1}{(1-x)(1-y)}\right)
\\
&=\frac{c}{a+b-1}\left(\sum_{i=0}^{n}[x^{n-i}y^n]\frac{b}{1-ax-by}+\sum_{i=0}^{n}[x^ny^{n-i}]\frac{a}{1-ax-by}-1\right)
\\
&=\frac{c}{a+b-1}\left(\sum_{i=0}^{n}a^{n-i}b^{n+1}\binom{2n-i}{n}+\sum_{i=0}^{n}a^{n+1}b^{n-i}\binom{2n-i}{n}-1\right)
\end{aligned}
$$

当 $a+b=1$ 时，我们有：

$$
\begin{aligned}
&[x^ny^n]\frac{c}{(1-x)(1-y)(1-ax-by)}
\\
&=c[x^ny^n]\left(\frac{b}{(1-x)(1-ax-by)^2}+\frac{a}{(1-y)(1-ax-by)^2}\right)
\\
&=c\left(\sum_{i=0}^{n}[x^{n-i}y^{n}]\frac{b}{(1-ax-by)^2}+\sum_{i=0}^{n}[x^ny^{n-i}]\frac{a}{(1-ax-by)^2}\right)
\\
&=c\left(\sum_{i=0}^{n}(2n-i+1)a^{n-i}b^{n+1}\binom{2n-i}{n}+\sum_{i=0}^{n}(2n-i+1)a^{n+1}b^{n-i}\binom{2n-i}{n}\right)
\end{aligned}
$$

综上所述，答案为：

$$
\sum_{i=0}^{n}t_{i+2}a^{n-i}b^{n+1}\binom{2n-i}{n}+\sum_{i=0}^{n}l_{i+2}a^{n+1}b^{n-i}\binom{2n-i}{n}
\\
+[a+b=1]c\!\!\left(\sum_{i=0}^{n}(2n-i+1)a^{n-i}b^{n+1}\binom{2n-i}{n}+\sum_{i=0}^{n}(2n-i+1)a^{n+1}b^{n-i}\binom{2n-i}{n}\right)
\\
+[a+b\ne1]\frac{c}{a+b-1}\left(\sum_{i=0}^{n}a^{n-i}b^{n+1}\binom{2n-i}{n}+\sum_{i=0}^{n}a^{n+1}b^{n-i}\binom{2n-i}{n}-1\right)
$$

时间复杂度为 $\mathcal{O}(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e5 + 10;
const int __ = 4e5 + 10;
const int mod = 1e6 + 3;
inline int qpow(int a, int b) {
    int s = 1;
    while (b) {
        if (b & 1) {
            s = (long long) s * a % mod;
        }
        a = (long long) a * a % mod;
        (b >>= 1);
    }
    return s;
}
int n, a, b, c, ans, tmp, l[_], t[_], f[__], g[__];
inline void init(int n) {
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = (long long) f[i-1] * i % mod;
    }
    g[n] = qpow(f[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        g[i] = (long long) g[i+1] * (i + 1) % mod;
    }
}
inline int binom(int n, int m) {
    return (long long) f[n] * g[m] % mod * g[n-m] % mod;
}
int main() {
    init(400000);
    cin >> n >> a >> b >> c;
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }
    n -= 2;
    tmp = qpow(b, n + 1);
    for (int i = n; i >= 0; i--) {
        ans = (ans + (long long) t[i+2] * tmp % mod * binom(2 * n - i, n)) % mod;
        if (i) {
            tmp = (long long) tmp * a % mod;
        }
    }
    tmp = qpow(a, n + 1);
    for (int i = n; i >= 0; i--) {
        ans = (ans + (long long) l[i+2] * tmp % mod * binom(2 * n - i, n)) % mod;
        if (i) {
            tmp = (long long) tmp * b % mod;
        }
    }
    if ((a + b) % mod == 1) {
        tmp = (long long) c * qpow(b, n + 1) % mod;
        for (int i = n; i >= 0; i--) {
            ans = (ans + (long long) (2 * n - i + 1) * tmp % mod * binom(2 * n - i, n)) % mod;
            if (i) {
                tmp = (long long) tmp * a % mod;
            }
        }
        tmp = (long long) c * qpow(a, n + 1) % mod;
        for (int i = n; i >= 0; i--) {
            ans = (ans + (long long) (2 * n - i + 1) * tmp % mod * binom(2 * n - i, n)) % mod;
            if (i) {
                tmp = (long long) tmp * b % mod;
            }
        }
    } else {
        tmp = (long long) c * qpow(((a + b - 1) % mod + mod) % mod, mod - 2) % mod * qpow(b, n + 1) % mod;
        for (int i = n; i >= 0; i--) {
            ans = (ans + (long long) tmp * binom(2 * n - i, n)) % mod;
            if (i) {
                tmp = (long long) tmp * a % mod;
            }
        }
        tmp = (long long) c * qpow(((a + b - 1) % mod + mod) % mod, mod - 2) % mod * qpow(a, n + 1) % mod;
        for (int i = n; i >= 0; i--) {
            ans = (ans + (long long) tmp * binom(2 * n - i, n)) % mod;
            if (i) {
                tmp = (long long) tmp * b % mod;
            }
        }
        ans = (ans + mod - (long long) c * qpow(((a + b - 1) % mod + mod) % mod, mod - 2) % mod) % mod;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)


有点意思的计数题。

发现递推式实际上是算带权的走到当前点的方案数。

首先考虑 $a,b$ 的贡献，以 $(1,i)$ 为例，它相当于是 $(2,i)\rightarrow (n,n)$，因此贡献为 $\dbinom{n-2+n-i}{n-2}\times a^{n-i}\times b^{n-1}\times val(1,i)$。

然后再考虑 $c$ 的贡献。再 $(i,j)$ 处加入一个 $c$，会加上 $\dbinom{2n-i-j}{n-i}a^{n-j}b^{n-i}c$ 的贡献。

直接做是 $O(n^2)$ 的，不难想到考虑一条一条对角线去枚举，式子长这样：

$$
\sum_{k=0}^{n-2}\left(\sum_{i=0}^{k}\binom k i a^{k-i}b^i\right)+\\
\sum_{k=n-1}^{2n-4}\left(\sum_{i=k-n+2}^{n-2}\binom k i a^{k-i}b^i \right)
$$

前面的一坨可以使用二项式定理来化简，后面那一坨可以使用增量法计算：

$$
\begin{aligned}
f(k)&=\sum_{i=k-n+2}^{n-2}\binom k i a^{k-i}b^i\\
&=\sum_{i=k-n+2}^{n-2}\binom{k-1} i a^{k-i}b^i+\sum_{i=k-n+2}^{n-2}\binom{k-1}{i-1} a^{k-i}b^i\\
&=af_{k-1}-\binom{k-1}{k-n+1}b^{k-n+1}a^{n-1}+bf_{k-1}-\binom{k-1}{n-2}b^{n-1}a^{k-n+1}
\end{aligned}
$$

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000003; 
const int N = 400000; 

inline int poww(int a, int b) {
    int r = 1;
    for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P;  
    return r; 
}

int n, a, b, c, pa[400005], pb[400005]; 
int l[200005], t[200005]; 
int fac[400005], ifac[400005]; 
int f[400005]; 

inline int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0; 
    return 1ll * fac[n] * ifac[m] * ifac[n - m] % P; 
}

int calf(int k) {
    int res = 0; 
    for (int i = k - n + 2; i <= n - 2; ++i)
        res = (res + 1ll * C(k, i) * pa[k - i] * pb[i]) % P; 
    return res; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> a >> b >> c; 

    for (int i = fac[0] = pa[0] = pb[0] = 1; i <= N; ++i) fac[i] = 1ll * fac[i - 1] * i % P, pa[i] = 1ll * pa[i - 1] * a % P, pb[i] = 1ll * pb[i - 1] * b % P; 
    ifac[N] = poww(fac[N], P - 2); 
    for (int i = N - 1; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; 

    int ans = 0; 
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; 
        if (i == 1) continue; 
        ans = (ans + 1ll * C(n - 2 + n - i, n - 2) * pa[n - 1] * pb[n - i] % P * x) % P; 
    }
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; 
        if (i == 1) continue; 
        ans = (ans + 1ll * C(n - 2 + n - i, n - 2) * pa[n - i] * pb[n - 1] % P * x) % P; 
    }
    for (int k = 0, B = 1; k <= n - 2; ++k) {
        ans = (ans + 1ll * c * B) % P; 
        B = 1ll * B * (a + b) % P; 
    }
    for (int k = n - 1; k <= n * 2 - 4; ++k) {
        if (k == n - 1) f[k] = calf(k); 
        else {
            f[k] = (1ll * a * f[k - 1] - 1ll * C(k - 1, k - n + 1) * pb[k - n + 1] * pa[n - 1] + 1ll * b * f[k - 1] - 1ll * C(k - 1, n - 2) * pb[n - 1] * pa[k - n + 1]) % P; 
        }
        ans = (ans + 1ll * c * f[k]) % P; 
    }
    cout << (ans + P) % P << "\n"; 
    return 0; 
}
```

---

## 作者：木xx木大 (赞：0)

[P4351 [CERC2015]Frightful Formula](https://www.luogu.com.cn/problem/P4351)


这个式子有点像格路径计数的 dp 式子。$c$ 的贡献的组合意义即为从每个 $(i,j)$ $(i,j\in[2,n])$ 走到 $(n,n)$，只能向下向右走，向右走一步路径权值 $\times a$，向下走一步路径权值 $\times b$ ，求所有路径的权值和 $\times c$ 的结果。即
$$
c\sum_{i=0}^{n-2}\sum_{j=0}^{n-2}{i+j\choose i}a^ib^j
$$
不用考虑 $c$ 时，式子前半部分的组合意义即为，从 $(i,2)$ 或 $(2,i)$ 走到 $(n,n)$，路径初始权值为 $f(i,1)$ 或 $f(1,i)$ ，只能向下向右走，向右走一步路径权值 $\times a$，向下走一步路径权值 $\times b$ ，求所有路径的权值和。即
$$
\sum_{i=2}^n{2n-i-2\choose n-2}a^{n-1}b^{n-i}f(i,1)+\sum_{i=2}^n{2n-i-2\choose n-2}a^{n-i}b^{n-1}f(1,i)
$$
这部分可以 $O(n)$ 算，所以只需要继续化简上面的式子。设
$$
\begin{aligned}

s_i&=\sum_{j=0}^{n-2}{i+j\choose j}b^j\\
s_{i+1}&=\sum_{j=0}^{n-2}{i+j+1\choose j}b^j\\&=\sum_{j=0}^{n-2}\left({i+j\choose j}+[j>0]{i+j\choose j-1}\right)b^j\\
&=s_i+b\sum_{j=0}^{n-2}{i+j+1\choose j}b^j-{i+n-1\choose n-2}b^{n-1}\\
&=s_i+bs_{i+1}-{i+n-1\choose n-2}b^{n-1}\\
&s_{i+1}=\begin{cases}\dfrac{{i+n-1\choose n-2}b^{n-1}-s_i}{b-1}\quad(b\ne 1)\\{i+n\choose n-2}\quad(b=1)\end{cases}\\

\end{aligned}
$$

先 $O(n)$ 递推出 $s$，上式即为 $\sum_{i=0}^{n-2}a^is_i$。总复杂度 $O(n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FGF
{
	int n,A,B,c;
	const int N=2e6+5,mo=1e6+3;
	int fac[N],inv[N],ifac[N],a[N],b[N],s[N],ans;
	long long C(int x,int y){if(x<0||y<0||x<y)return 0;return 1ll*fac[x]*ifac[y]%mo*ifac[x-y]%mo;}
	int qpow(int x,int y)
	{
		int s=1;
		while(y)
		{
			if(y&1)s=1ll*s*x%mo;
			x=1ll*x*x%mo;
			y>>=1;
		}
		return s;
	}
	void work()
	{
		scanf("%d%d%d%d",&n,&A,&B,&c);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		fac[0]=inv[1]=ifac[0]=ifac[1]=1;
		for(int i=2;i<=2*n;i++)
			inv[i]=1ll*inv[mo%i]*(mo-mo/i)%mo;
		for(int i=1;i<=2*n;i++)
			fac[i]=1ll*fac[i-1]*i%mo,ifac[i]=1ll*ifac[i-1]*inv[i]%mo;
		for(int i=0,x=1;i<=n-2;i++,x=1ll*x*B%mo)
			s[0]=(s[0]+x)%mo;
		if(B==1)
			for(int i=1;i<=n-2;i++)
				s[i]=C(n+i-1,n-2);
		else
			for(int i=1,x=qpow(B-1,mo-2),y=qpow(B,n-1);i<=n-2;i++)
				s[i]=1ll*x*(C(i+n-2,n-2)*y%mo-s[i-1]+mo)%mo;
		for(int i=0,x=1;i<=n-2;i++,x=1ll*x*A%mo)
			ans=(ans+1ll*x*s[i]%mo)%mo;
		ans=1ll*ans*c%mo;
		for(int i=n,x=1,y=1,aa=qpow(A,n-1),bb=qpow(B,n-1);i>=2;i--,x=1ll*x*A%mo,y=1ll*y*B%mo)
			ans=(ans+C(2*n-i-2,n-2)*aa%mo*y%mo*a[i]%mo+C(2*n-i-2,n-2)*bb%mo*x%mo*b[i]%mo)%mo;
		printf("%d\n",ans);
	}
}
int main()
{
	FGF::work();
	return 0;
}

---

## 作者：mrsrz (赞：0)

~~被强行灌输了一些高级的数学知识，不过还是可以用简单的方法理解~~

首先考虑 $c=0$ 时的做法。$f_{i,j}=a\cdot f_{i,j-1}+b\cdot f_{i-1,j}$。

考虑式子的组合意义，这是一个经典的格路计数问题，其中向右走贡献乘 $a$，向下走贡献乘 $b$。则从 $(1,1)$ 到 $(m,n)$ 的贡献就是 $\binom{n+m-2}{n-1}\cdot a^{n-1}b^{m-1}$。

由于第一行第一列的初始贡献不同，因此对于每个起点都要计算。时间复杂度 $O(n)$。

---

现在考虑 $c\neq 0$ 的做法。我们希望找到一个办法来消掉常数项 $c$。

考虑找到一个 $x$ 满足 $x=ax+bx+c$，这样就可以得到 $f_{i,j}-x=a\cdot (f_{i,j-1}-x)+b\cdot (f_{i-1,j}-x)$。令 $g_{i,j}=f_{i,j}-x$，将 $g_{n,n}$ 用 $c=0$ 时的做法求出，再加上 $x$ 即可。

容易解得 $x=\frac{c}{1-a-b}$。

---

上面的做法当 $a+b\not\equiv 1\pmod{10^6+3}$ 时是正确的，否则就无法找到这样的 $x$。

~~虽然好像并没有这样的数据但还是要考虑的~~

现在的式子为 $f_{i,j}=a\cdot f_{i,j-1}+(1-a)\cdot f_{i-1,j}+c$。

我们还是想要消掉这个常数 $c$。

注意此时右边两项的系数和为 $1$，且下标和相等，因此我们考虑一个与 $(i+j)$ 有关的函数，为了方便记为 $h_{i,j}$。

令 $h_{i,j}=k(i+j)$，则 $k(i+j)=k(i+j-1)+c$。

解得 $k=c$，即 $h_{i,j}=c(i+j)$。

可以得到 $(f_{i,j}-h_{i,j})=a\cdot(f_{i,j-1}-h_{i,j-1})+(1-a)\cdot(f_{i-1,j}-h_{i-1,j})$。

令 $g_{i,j}=f_{i,j}-h_{i,j}$，将 $g_{n,n}$ 用 $c=0$ 时的做法求出，再加上 $2n\cdot c$ 就是答案。

时间复杂度 $O(n)$。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=4e5+5,md=1e6+3;
int n,R[N],C[N],a,b,c,A[N],B[N],fac[N],iv[N];
inline int pow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=(LL)a*a%md)if(b&1)res=(LL)res*a%md;
	return res;
}
inline int binom(int n,int m){return(LL)fac[n]*iv[m]%md*iv[n-m]%md;}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>a>>b>>c;
	for(int i=*A=*B=*fac=1;i<=2*n;++i)A[i]=(LL)A[i-1]*a%md,B[i]=(LL)B[i-1]*b%md,fac[i]=(LL)fac[i-1]*i%md;
	iv[n]=pow(fac[n],md-2);
	for(int i=n-1;~i;--i)iv[i]=(i+1LL)*iv[i+1]%md;
	for(int i=1;i<=n;++i)cin>>R[i];
	for(int i=1;i<=n;++i)cin>>C[i];
	if((a+b)%md==1){
		int ans=0;
		for(int i=2;i<=n;++i)
		ans=(ans+((LL)A[n-1]*B[n-i]%md*(R[i]-c*(i+1LL)%md+md)+(LL)B[n-1]*A[n-i]%md*(C[i]-c*(i+1LL)%md+md))%md*binom(2*n-i-2,n-2))%md;
		cout<<(ans+2LL*c*n)%md<<'\n';
	}else{
		int x=c*(LL)pow(2*md+1-a-b,md-2)%md,ans=0;
		for(int i=2;i<=n;++i)
		ans=(ans+((LL)A[n-1]*B[n-i]%md*(R[i]-x+md)+(LL)B[n-1]*A[n-i]%md*(C[i]-x+md))%md*binom(2*n-i-2,n-2))%md;
		cout<<(ans+x)%md<<'\n';
	}
	return 0;
}
```

---

## 作者：Prean (赞：0)

很久以前我的某个朋友给过我一道题：

给定 $f_i,a,b,c,h$，定义 $A$ 满足：
$$A_{i,j}=[i\ne 0]\times(([j=0]f_i)+([j\ne 0]a\times A_{i-1,j}+b\times A_{i,j-1}+c))$$
请求出 $\sum_{i=1}^{n}\sum_{j=1}^{m}A_{i,j}h^{(i-1)m+j}$ 的值。

当时应该是口胡了一个，把 $A$ 的每一列看做一个生成函数，容易发现转移是一个卷积，最终答案能够写成 $F(x)G^n(x)$ 的形式。

随便写写就可以 $m\log m\log n$ 了。

这道题简直是上述的究极弱化版，只需要求单项。

所以先考虑一个 $l,t$ 对答案的贡献，容易发现是：
$$\sum_{i=1}^{n}\binom{(n-2)+n-i}{n-i}(l_ib^{n-i}a^{n-1}+t_ia^{n-i}b^{n-1})$$
这个随便算算就 $O(n)$ 了，别的地方相当于：
$$\sum_{i=1}^{n-1}\sum_{j=1}^{n-1}\binom{(n-i-1)+(n-j-1)}{n-i-1}a^{n-i-1}b^{n-j-1}$$
$$\sum_{i=0}^{n-2}\sum_{j=0}^{n-2}\binom{i+j}{i}a^ib^i$$
$$\sum_{i=0}^{n}\binom{i+k}{i}b^i$$
不难发现这是一个萌萌卷积，令 $A(x)=\sum_{i=0}^{n-2}\frac{a^ix^i}{i!},B(x)=\sum_{i=0}^{n-2}\frac{b^ix^i}{i!}$，答案就是 $\sum_{i=0}^{2n-4}[\frac{x^i}{i!}]A(x)B(x)$
接下来考虑如何 $O(n)$。
枚举一个 $i$，设：
$$F_k=\sum_{i=0}^{n}\binom{i+k}{i}b^i$$
答案就是 $\sum_{i=0}^{n}F_ia^i$。

接下来裂开组合数递推：
$$\sum_{i=0}^{n}\binom{i+(k-1)}{i}b^i+\binom{(i-1)+k}{i-1}b^i$$
$$\sum_{i=0}^{n}\binom{i+(k-1)}{i}b^i+b\sum_{i=0}^{n-1}\binom{i+k}{i}b^i$$
$$F_k=F_{k-1}+b(F_k-\binom{n+k}{n}b^n)$$
$$F_k=\frac{F_{k-1}-\binom{n+k}{n}b^{n+1}}{1-b}$$
特殊情况，如果 $b=1$，那么有 $F_k=\binom{n+k+1}{n}$。
```cpp
#include<cstdio>
#include<cctype>
const int M=4e5+5,mod=1e6+3;
int n,a,b,c,ans,x[M],y[M],F[M],fac[M],ifac[M],G[1000][1000];
inline int read(){int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;}
inline int pow(int a,int b=mod-2){int ans(1);for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;}
inline int C(const int&n,const int&m){return 1ll*ifac[m]*ifac[n-m]%mod*fac[n]%mod;}
inline void calc(const int&n){
	if(b==1){for(int i=0;i<=n;++i)F[i]=C(n+i+1,n);return;}
	const int&x=pow(mod+1-b),&y=mod-pow(b,n+1);F[0]=1ll*(y+1)*x%mod;
	for(int i=1;i<=n;++i)F[i]=(F[i-1]+1ll*C(n+i,n)*y)%mod*x%mod;
}
signed main(){
	n=read()-1;a=read();b=read();c=read();for(int i=0;i<=n;++i)x[i]=read();for(int i=0;i<=n;++i)y[i]=read();
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;for(int i=2;i<=n*2;++i)ifac[i]=1ll*(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=2;i<=n*2;++i)fac[i]=1ll*fac[i-1]*i%mod,ifac[i]=1ll*ifac[i-1]*ifac[i]%mod;
	if(c){calc(n-1);for(int i=n-1;i>=0;--i)ans=(1ll*ans*a+F[i])%mod;ans=1ll*ans*c%mod;}
	for(int q(pow(a,n)),p(pow(b,n)),i=n;i>=1;--i){
		ans=(ans+1ll*C(n-1+n-i,n-i)*(1ll*x[i]*q+1ll*y[i]*p))%mod;q=1ll*q*b%mod;p=1ll*p*a%mod;
	}
	printf("%d\n",ans);
}
```

---

