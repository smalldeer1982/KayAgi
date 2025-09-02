# 「HGOI-1」Competition

## 题目背景

$\text{HGOI}$ 举办了一场模拟赛。

为了增加选手们的积极性，$\text{HGOI}$ 的出题人根据题目难度划定了一个分数线。$\text{bh1234666}$ 会给超过这个分数线的选手发奖品。

## 题目描述

众所周知，$\text{OI}$ 赛制的比赛有很大的运气成分。选手们往往不能发挥出真实水平。所以对于参赛的 $n$ 位选手，第 $i$ 位选手会有一个达到分数线的概率 $p_i$。

在模拟赛结束后就是最激动人心颁奖环节。

组委会的委员们设置了若干种类的奖品，并且每种奖品都有对应的价值。而他们对自己设置的奖品的发放有各自的要求：

- $\text{uuku}$ 喜欢成双成对，所以对于他设置的**每种**奖品必须向**偶数个获奖选手**发放。

- $\text{rechinist}$ 喜欢跟 $\text{uuku}$ 对着干，所以对于他设置的**每种**奖品必须向**奇数个获奖选手**发放。

委员 $\text{uuku}$ 设置了 $A$ 种奖品，$a_i$ 表示他设置的第 $i$ 种奖品的价值。

委员 $\text{rechinist}$ 准备了 $B$ 种奖品，$b_i$ 表示他设置的第 $i$ 种奖品的价值。

当然**每个获奖选手**都将被发给**恰好**一份奖励。

选手们不关心每种奖品被发放了几次，但是他们关心有多少种奖品被发放了，因此选手们的积极性被定义为所有被发放的奖品的价值的乘积（每种奖品只会被乘一次）。

假如获奖人数使得委员会无法发放奖品， $\text{bh1234666}$ 会十分生气，拒绝提供资金购买奖品，使得选手积极性为 $0$ 。

现在，委员会已经知道了每个选手能达到分数线的概率 $p_i$，他们想知道选手们积极性的期望值为多少。

由于答案可能很大，所以你只需要给出对 $998244353$ 取模以后的结果。


## 说明/提示

#### 样例1解释

$0\sim n$ 人达到分数线的概率依次为$\dfrac{1}{16}$，$\dfrac{1}{4}$，$\dfrac{3}{8}$，$\dfrac{1}{4}$，$\dfrac{1}{16}$。

对于 $0$ 人达到分数线无发放方案。

对于 $1$ 人达到分数线无发放方案。

对于 $2$ 人达到分数线有如下 $2$ 种发放方案。

$4$，$5$ 价值为 $20$ 对期望贡献为 $20\times \dfrac{3}{8}\times \dfrac{1}{2}=\dfrac{15}{4}$。

$5$，$4$ 价值为 $20$ 对期望贡献为 $20\times \dfrac{3}{8}\times \dfrac{1}{2}=\dfrac{15}{4}$。

对于 $3$ 人达到分数线无发放方案。

对于 $4$ 人达到分数线有如下 $32$ 种发放方案。

对于发放 $4$，$5$ 两种奖品一共有 $8$ 种方式。

每种价值均为 $20$ 对期望总贡献为 $20\times 8\times \dfrac{1}{16}\times \dfrac{1}{32}=\dfrac{5}{16}$。

对于发放 $1$，$4$，$5$ 三种奖品一共有 $12$ 种方式。

每种价值均为 $20$ 对期望总贡献为 $20\times 12\times \dfrac{1}{16}\times \dfrac{1}{32}=\dfrac{15}{32}$。

对于发放 $2$，$4$，$5$ 三种奖品一共有 $12$ 种方式。

价值均为 $40$ 对期望贡献为 $40\times 12\times \dfrac{1}{16}\times \dfrac{1}{32}=\dfrac{15}{16}$。

则总期望 $E=\dfrac{15}{4}+\dfrac{15}{4}+\dfrac{5}{16}+\dfrac{15}{32}+\dfrac{15}{16}=\dfrac{295}{32}\equiv 779878410 (\bmod\ 998244353)$。

#### 数据范围

本题采用**捆绑测试**，共有 $6$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \textbf{特殊限制} \cr\hline
1 & 5 & n \le 5 \text{且} A \text{，}B \le 5 \cr\hline
2 & 10 & n \le 500 \text{且} A+B \le 500 \cr\hline
3 & 15 & n \le 2000 \text{且} A+B\le 2000  \cr\hline
4 & 20 & n\text{，}A\text{，}B \le 5000  \cr\hline
5 & 20 & n \le 2\times 10^5 \text{，} A \text{，} B \le 10^5\cr\hline
6 & 30 &  \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \le A$，$B \le 2 \times 10^5$，$1 \le n \le 4 \times 10^5$，$1 \le a_i$，$b_i$，$p_i \le 998244352$。

## 样例 #1

### 输入

```
4 2 2
499122177 499122177 499122177 499122177
1 2 
4 5```

### 输出

```
779878410```

# 题解

## 作者：NaCly_Fish (赞：6)

场上就一个人 AC，怎么回事呢？

样例给的做法提示很明显，就是 有 $k$ 个选手过线概率 乘以 给 $k$ 个选手分配的期望价值 再求和。

有 $k$ 个人过线的概率很简单，就是 $[x^k]\prod_i((1-p_i)+p_ix)$，分治乘即可。

然后需要计算给 $k$ 个选手分配的价值总和。对于这种经典模型，对每种奖品建立 EGF，然后都乘起来，也就是：

$$k![x^k]\prod_{i=1}^A(1+a_i(\cosh x-1))\times \prod_{i=1}^B(b_i \sinh x)$$
后一部分很简单，前一部分有个暴力做法：做换元 $u=\text e^x$，然后直接分治乘，最后就是求 $F(\text e^x)$ 的系数。

$$k![x^k]F(\text e^x)=\sum_{i=-A}^Af_i i^k$$
$$=[x^k]\sum_{k=0}^\infty x^k\sum_{i=-A}^Af_i i^k =[x^k]\sum_{i=-A}^A\frac{f_i}{1-ix}$$
可以直接维护分子和分母分治求和。

最后把总和变为期望就是除一个方案数，令 $a_i,b_i$ 都为 $1$ 就是答案。

参考代码（没太注意实现细节，跑得比较慢）：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 1048579
#define p 998244353
#define ll long long
using namespace std;

inline void read(int &x){
	x = 0;
	char c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9'){
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
}

void print(int x){
	if(x>9) print(x/10);
	putchar(x%10+'0');	
}

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

inline int add(const int& x,const int& y){ return x+y>=p?x+y-p:x+y; }
inline int dec(const int& x,const int& y){ return x<y?x-y+p:x-y; }

int rt[N],rev[N],fac[N],ifac[N],inv[N];
int siz;

void init(int n){
	int w,lim = 1;
	while(lim<=n) lim <<= 1,++siz;
	for(int i=1;i!=lim;++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<(siz-1));
	w = power(3,(p-1)>>siz);
	inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = rt[lim>>1] = 1;
	for(int i=(lim>>1)+1;i!=lim;++i) rt[i] = (ll)rt[i-1]*w%p;
	for(int i=(lim>>1)-1;i;--i) rt[i] = rt[i<<1];	
    for(int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
    for(int i=2;i<=n;++i) inv[i] = (ll)fac[i-1]*ifac[i]%p;
}

inline void dft(int *f,int n){
    static unsigned long long a[N];
    int x,shift = siz-__builtin_ctz(n);
    for(int i=0;i!=n;++i) a[rev[i]>>shift] = f[i];
    for(int mid=1;mid!=n;mid<<=1)
    for(int j=0;j!=n;j+=(mid<<1))
    for(int k=0;k!=mid;++k){
        x = a[j|k|mid]*rt[mid|k]%p;
        a[j|k|mid] = a[j|k]+p-x;
        a[j|k] += x;
    }
    for(int i=0;i!=n;++i) f[i] = a[i]%p;
}

inline void idft(int *f,int n){
    reverse(f+1,f+n);
    dft(f,n);
    int x = p-((p-1)>>__builtin_ctz(n));
    for(int i=0;i!=n;++i) f[i] = (ll)f[i]*x%p;
}

inline int getlen(int n){ return 1<<(32-__builtin_clz(n)); }

inline void inverse(const int *f,int n,int *r){
    static int g[N],h[N],st[30];
    memset(g,0,getlen(n<<1)<<2);
    int lim = 1,top = 0;
    while(n){
        st[++top] = n;
        n >>= 1;
    }
    g[0] = 1;
    while(top--){
        n = st[top+1];
        while(lim<=(n<<1)) lim <<= 1;
        memcpy(h,f,(n+1)<<2);
        memset(h+n+1,0,(lim-n)<<2);
        dft(g,lim),dft(h,lim);
        for(int i=0;i!=lim;++i) g[i] = g[i]*(2-(ll)g[i]*h[i]%p+p)%p;
        idft(g,lim);
        memset(g+n+1,0,(lim-n)<<2);
    }
    memcpy(r,g,(n+1)<<2);
}

int n,A,B;
int pr[N],a[N],C[N];

void product(int l,int r,int *R){
    if(l==r){
        R[0] = p+1-pr[l],R[1] = pr[l];
        return;
    }
    int lim = getlen(r-l+1),mid = (l+r)>>1;
    int fl = mid-l+1,gl = r-mid;
    int f[lim+2],g[lim+2];
    product(l,mid,f),product(mid+1,r,g);
    memset(f+fl+1,0,(lim-fl)<<2);
    memset(g+gl+1,0,(lim-gl)<<2);
    dft(f,lim),dft(g,lim);
    for(int i=0;i!=lim;++i) R[i] = (ll)f[i]*g[i]%p;
    idft(R,lim);
}

void prod2(int l,int r,int *R){
    if(l==r){
        R[0] = R[2] = a[l],R[1] = ((p+1-a[l])<<1)%p;
        return;
    }
    int lim = getlen((r-l+1)<<1),mid = (l+r)>>1;
    int fl = (mid-l+1)<<1,gl = (r-mid)<<1;
    int f[lim+2],g[lim+2];
    prod2(l,mid,f),prod2(mid+1,r,g);
    memset(f+fl+1,0,(lim-fl)<<2);
    memset(g+gl+1,0,(lim-gl)<<2);
    dft(f,lim),dft(g,lim);
    for(int i=0;i!=lim;++i) R[i] = (ll)f[i]*g[i]%p;
    idft(R,lim);
}

void solve(int l,int r,const int *sc,int *fz,int *fm){ // 多项式复合 F(e^x)
    if(l==r){
        fz[0] = sc[l+A],fm[0] = 1,fm[1] = (p-l)%p;
        return;
    }
    int lim = getlen(r-l+1),mid = (l+r)>>1;
    int fl = mid-l+1,gl = r-mid;
    int lfz[lim+2],lfm[lim+2],rfz[lim+2],rfm[lim+2];
    solve(l,mid,sc,lfz,lfm),solve(mid+1,r,sc,rfz,rfm);
    memset(lfz+fl,0,(lim-fl+1)<<2),memset(lfm+fl+1,0,(lim-fl)<<2);
    memset(rfz+gl,0,(lim-gl+1)<<2),memset(rfm+gl+1,0,(lim-gl)<<2);
    dft(lfz,lim),dft(lfm,lim),dft(rfz,lim),dft(rfm,lim);
    for(int i=0;i!=lim;++i){
        fz[i] = ((ll)lfz[i]*rfm[i]+(ll)lfm[i]*rfz[i])%p;
        fm[i] = (ll)lfm[i]*rfm[i]%p;
    }
    idft(fz,lim),idft(fm,lim);
}

inline void deriv(const int *f,int n,int *R){
    for(int i=1;i!=n;++i) R[i-1] = (ll)i*f[i]%p;
    R[n-1] = 0;
}

inline void integ(const int *f,int n,int *R){
    for(int i=n-1;i;--i) R[i] = (ll)f[i-1]*inv[i]%p;
    R[0] = 0;
}

inline void log(const int *f,int n,int *r){
    static int g[N],h[N];
    inverse(f,n,g);
    deriv(f,n+1,h);
    int lim = getlen(n<<1);
    memset(g+n+1,0,(lim-n)<<2);
    memset(h+n+1,0,(lim-n)<<2);
    dft(g,lim),dft(h,lim);
    for(int i=0;i!=lim;++i) g[i] = (ll)g[i]*h[i]%p;
    idft(g,lim);
    integ(g,n+1,r);
}

inline void exp(const int *a,int n,int *R){
    int m = n+1;
    n = 1;
    while(n<m) n <<= 1;
    static int der[N],b[N],c[N],dfta[N],dftb[N],dftb2[N],dftc[N];
    for(int i=0;i!=n;++i) b[i] = c[i] = dfta[i] = dftb[i] = dftb2[i] = dftc[i] = 0;
    dftb2[0] = b[0] = c[0] = 1;
    dft(dftb2,2);
    deriv(a,n,der);
    for(int d=1;d!=n;d<<=1){
        memcpy(dftc,c,d<<2);
        dft(dftc,d<<1);
        for(int i=0;i!=d;++i) dftb[i] = (ll)dftb2[i<<1]*dftc[i<<1]%p;
        idft(dftb,d);
        dftb[0] = dec(dftb[0],1);
        for(int i=0;i!=d;++i) dftb[d+i] = dftb[i];
        memset(dftb,0,d<<2);
        dft(dftb,d<<1);
        memcpy(dfta,der,(d-1)<<2);
        dfta[d-1] = 0;
        dft(dfta,d<<1);
        for(int i=0;i!=(d<<1);++i) dfta[i] = (ll)dfta[i]*dftb[i]%p;
        idft(dfta,d<<1);
        deriv(b,d,dftb);
        dft(dftb,d);
        for(int i=0;i!=d;++i) dftb[i] = (ll)dftb[i]*dftc[i<<1]%p;
        idft(dftb,d);
        for(int i=0;i!=d-1;++i) dftb[d+i] = dec(dftb[i],der[i]);
        memset(dftb,0,(d-1)<<2);
        for(int i=d-1;i!=(d<<1);++i) dftb[i] = dec(dftb[i],add(der[i],dfta[i]));
        integ(dftb,d<<1,dftb);
        dft(dftb,d<<1);
        for(int i=0;i!=(d<<1);++i) dftb[i] = (ll)dftb[i]*dftb2[i]%p;
        idft(dftb,d<<1);
        for(int i=d;i!=(d<<1);++i) b[i] = p-dftb[i];
        if((d<<1)==n) continue;
        memcpy(dftb2,b,d<<3);
        dft(dftb2,d<<2);
        for(int i=0;i!=(d<<1);++i) dftb[i] = (ll)dftb2[i<<1]*dftc[i]%p;
        idft(dftb,d<<1);
        memset(dftb,0,d<<2);
        dft(dftb,d<<1);
        for(int i=0;i!=(d<<1);++i) dftb[i] = (ll)dftb[i]*dftc[i]%p;
        idft(dftb,d<<1);
        for(int i=d;i!=(d<<1);++i) c[i] = p-dftb[i];
    }
    memcpy(R,b,m<<2);
}

int f[N],g[N],fz[N],fm[N],suf[N];
int pw,ans;

int main(){
	read(n),read(A),read(B);
    if(n<B){
        puts("0");
        return 0;
    }
    init(800000);
    for(int i=1;i<=n;++i) read(pr[i]);
    for(int i=1;i<=A;++i) read(a[i]);
    product(1,n,C),prod2(1,A,f);
    solve(-A,A,f,fz,fm); 
    for(int i=n+1;i<=(A<<1);++i) fz[i] = fm[i] = 0;
    inverse(fm,n,fm);
    int lim = getlen(n<<1);
    dft(fz,lim),dft(fm,lim);
    for(int i=0;i!=lim;++i) fz[i] = (ll)fz[i]*fm[i]%p;
    idft(fz,lim);
    memset(fz+n+1,0,(lim-n)<<2),memset(f,0,lim<<2);
    for(int i=0;i<=n;++i) fz[i] = (ll)fz[i]*ifac[i]%p;
    int tn = max((n-B)>>1,4);
    for(int i=0;i<=tn;++i) f[i] = ifac[i<<1|1];
    log(f,tn,f);
    for(int i=0;i<=tn;++i) f[i] = (ll)f[i]*B%p;
    exp(f,tn,f);
    for(int i=tn;i;--i) f[i<<1] = f[i],f[i] = 0;
    for(int i=n;i>=B;--i) f[i] = f[i-B];
    memset(f,0,B<<2),memset(f+n+1,0,(lim-n)<<2);
    for(int i=0;(i<<1)<=n;++i) g[i] = ifac[i<<1];
    log(g,n>>1,g);
    for(int i=0;(i<<1)<=n;++i) g[i] = (ll)g[i]*A%p;
    exp(g,n>>1,g);
    for(int i=(n>>1);i;--i) g[i<<1] = g[i],g[i] = 0;
    dft(fz,lim),dft(f,lim),dft(g,lim);
    for(int i=0;i!=lim;++i){
        fz[i] = (ll)fz[i]*f[i]%p;
        g[i] = (ll)g[i]*f[i]%p;
    }
    idft(fz,lim),idft(g,lim);
    suf[n+1] = 1;
    for(int i=n;i;--i) suf[i] = (ll)suf[i+1]*(g[i]==0?1:g[i])%p;
    int pre = power(suf[1],p-2);
    for(int i=1;i<=n;++i){
        ans = (ans+(ll)fz[i]*C[i]%p*pre%p*suf[i+1])%p;
        pre = (ll)pre*(g[i]==0?1:g[i])%p;
    }
    for(int i=1;i<=B;++i){
        read(pw);
        ans = (ll)ans*pw%p;
    }
    ans = (ll)ans*power(2,p-A-1)%p;
    print(ans);
	return 0;
}
```

---

## 作者：uuku (赞：4)

根据题意，积极性的期望就是每种方案的积极性 $\times$ 这种方案的概率。

形式化的，我们记 $P_k$ 表示最终有 $k$ 个人达到分数线的概率，$F_k$ 表示给 $k$ 个人发奖品的方案数，$val_k$ 表示给 $k$ 个人发奖品所有方案的积极性之和。

那么对于一种发给 $k$ 个人奖品的方案其概率为 $\dfrac{P_k}{F_k}$。

则最终期望 $E=\sum\limits_{k=0}^n \dfrac{P_k\times val_k}{F_k}$。

下面考虑分别求出 $P_k$，$F_k$，$val_k$。

$P_k$：

显然可以 $O(n^2)$ 进行 $\tt{DP}$。记 $f_{i,j}$ 表示前 $i$ 个人中有 $j$ 个人达到分数线的概率。那么有 $f_{0,0}=1$，$f_{i,j}=f_{i-1,j}\times (1-p_i)+f_{i-1,j-1}\times p_i$。

但这个复杂度显然不能接受。套路性的，我们考虑答案的生成函数 $\sum\limits_{k=0}^n P_kx^k$。而每个人的生成函数即为 $1-p_i+p_ix$。

则 $\sum\limits_{k=0}^n P_kx^k = \prod\limits_{i=1}^n (1-p_i+p_ix)$。

普通分治乘法就可以解决这个问题。

$F_k$：

有 $O((A+B)n^2)$ 的 $\tt{DP}$，记 $f_{i,j}$ 表示用前 $i$ 个 奖品发给 $j$ 个人的方案数。

枚举第 $i$ 个奖品用了多少个和发给多少人。

对于 $\text{A}$ 类奖品有转移 $f_{i,j}=\sum\limits_{k\text{为偶数}}^j f_{i-1,j-k}\times \binom{j}{k}$。

对于 $\text{B}$ 类奖品有转移 $f_{i,j}=\sum\limits_{k\text{为奇数}}^j f_{i-1,j-k}\times \binom{j}{k}$。

不难发现转移过程类似卷积，但不完全一样。套路的将组合数写成阶乘的形式。

即对于 $\text{A}$ 类奖品有转移 $f_{i,j}=\sum\limits_{k\text{为偶数}}^j f_{i-1,j-k}\times \dfrac{j!}{k!\times (j-k)!}=j!\times \sum\limits_{k\text{为偶数}}^j \dfrac{f_{i-1,j-k}}{(j-k)!}\times \dfrac{1}{k!}$。

不考虑 $j!$ 这个式子就可以用 $\tt{NTT}$ 优化了。

对于 $\text{B}$ 类奖品也是一样的。复杂度 $O((A+B)n\log n)$。

不难发现每次卷的多项式都是一样的。

对于 $\text{A}$ 类，每个奖品的生成函数均为 $1+\dfrac{x^2}{2!}+\dfrac{x^4}{4!}\cdots$。

即最终的结果即为 $(1+\dfrac{x^2}{2!}+\dfrac{x^4}{4!}\cdots)^A$。

[多项式快速幂](https://www.luogu.com.cn/problem/P5245)  即可。

对于 $\text{B}$ 类，每个奖品的生成函数为 $\dfrac{x}{1!}+\dfrac{x^3}{3!}\cdots$。

而 $(\dfrac{x}{1!}+\dfrac{x^3}{3!}\cdots)^B$ 由于常数项不为 $1$，有两种处理方式：

1. 转化为 $x^B(\dfrac{1}{1!}+\dfrac{x^2}{3!}\cdots)^B$ 直接快速幂即可。

2. [多项式幂函数（加强版）](https://www.luogu.com.cn/problem/P5273)。

最后再将 $\text{A}$，$\text{B}$ 两类的方案数卷起来乘上 $k!$ 就可以得到 $F_k$。

复杂度 $O(n\log n)$。

$val_k$：

$\tt{DP}$ 做法及优化和求方案数一样，只需多乘一个价值。

对于 $\text{B}$ 类，每种奖品价值的生成函数为 $b_i(\dfrac{x}{1!}+\dfrac{x^3}{3!}\cdots)$。

则 $\text{B}$ 类的方案价值生成函数即为 $(\dfrac{x}{1!}+\dfrac{x^3}{3!}\cdots)^B \prod\limits_{i=1}^B b_i$。

将之前求过的方案数乘上 $\prod\limits_{i=1}^B b_i$ 即可。

对于 $\text{A}$ 类，每种奖品价值的生成函数为 $1+\dfrac{a_i}{2!}x^2+\dfrac{a_i}{4!}x^4\cdots$。

这个东西显然不能用快速幂做。考虑其指数型生成函数 $\tt{EGF}$。

由 $e^x=\sum\limits_{k=0}^{\infty} \dfrac{x^k}{k!}$，$e^{-x}=\sum\limits_{k=0}^{\infty} (-1)^k\dfrac{x^k}{k!}$。

则 $1+\dfrac{x^2}{2!}+\dfrac{x^4}{4!}\cdots=\dfrac{e^x+e^{-x}}{2}$。

$1+\dfrac{a_i}{2!}x^2+\dfrac{a_i}{4!}x^4\cdots=a_i(\dfrac{e^x+e^{-x}}{2}-1)+1$。

$\prod\limits_{i=1}^A (1+\dfrac{a_i}{2!}x^2+\dfrac{a_i}{4!}x^4\cdots)=\prod\limits_{i=1}^A (a_i(\dfrac{e^x+e^{-x}}{2}-1)+1)$。

考虑将上述式子展开后，再将 $e^{kx}$ 泰勒展开回普通型生成函数。

为了方便处理，先将 $e^{-x}$ 提出来。

$\prod\limits_{i=1}^A (a_i(\dfrac{e^x+e^{-x}}{2}-1)+1)=e^{-Ax}\prod\limits_{i=1}^A(\dfrac{a_i}{2}e^{2x}+(1-a_i)e^x+\dfrac{a_i}{2})$。

将 $e^x$ 看成 $x$。用分治乘法将其展开。得到一个形如 $\sum\limits_{i=0}^{2A} c_ie^{i-A}$ 的多项式。

接下来就是将 $e^{kx}$ 泰勒展开。

即对于每个 $k\in[1,n]$，求出 $\sum\limits_{i=0}^{2A}c_i(i-A)^k$。

当 $c_i=1$ 时，就是直接求自然数幂和（可参考[calc加强版](https://www.luogu.com.cn/problem/P5850)或[[THUPC2017] 小 L 的计算题](https://www.luogu.com.cn/problem/P7431)）。

对于任意情况：

同样考虑最终答案的生成函数 $G(x)=\sum\limits_{k=0}^{\infty}x^k\sum\limits_{i=0}^{2A}c_i(i-A)^k$。

因为 $\sum\limits_{k=0}^{\infty}a^kx^k=\dfrac{1}{1-ax}$。

所以 $G(x)=\sum\limits_{i=0}^{2A}\dfrac{c_i}{1-(i-A)x}$。

直接通分：

$$G(x)=\dfrac{\sum\limits_{i=0}^{2A}c_i\prod\limits_{j=0,j\ne i}^{2A}(1-(j-A)x)}{\prod\limits_{i=0}^{2A}{(1-(i-A)x)}}$$

同样考虑用分治求解上述式子。

我们记 $A(l,r)=\sum\limits_{i=l}^{r}c_i\prod\limits_{j=l,j\ne i}^r(1-(j-A)x)$，$B(l,r)=\prod\limits_{i=l}^{r}{(1-(i-A)x)}$。

不难发现 $A(l,r)=A(l,mid)\times B(mid+1,r)+A(mid+1,r)\times B(l,mid)$，$B(l,r)=B(l,mid)\times B(mid+1,r)$。

直接分治即可。复杂度 $O(n\log^2n)$。

而之前求方案数同样可以考虑用上述分治方法完成。并且由于多项式快速幂的大常数，两者的效率差不多。

综上最终的复杂度为 $O(n\log^2n)$。

示例代码：
```cpp
namespace work_A
{
	#define mid ((l+r)>>1)
	poly tA,tB;
	inline poly solve(int l,int r)
	{
		if(l==r)return r=1ll*inv[2]*a[l]%mod,(poly{r,sub(1-a[l]),r});
		return Get_Mul(solve(l,mid),solve(mid+1,r),-1);
	}
	Poly tp;
	Poly work(Poly L,Poly R)
	{
		int lim=1,p=0,Lb=L.b.size(),Rb=R.b.size();
		for(;lim<Lb+Rb;lim<<=1,p++);
		L.resize(lim),R.resize(lim);
		DFT(L.a),DFT(L.b),DFT(R.a),DFT(R.b);
		for(int i=0;i!=lim;++i)L.a[i]=(1ll*L.a[i]*R.b[i]+1ll*R.a[i]*L.b[i])%mod;
		dot(L.b,R.b),IDFT(L.a),IDFT(L.b);
		L.resize(min(Lb+Rb-1,n+1));
		return L;
	}
	Poly solve2(int l,int r)
	{
		if(l==r)return (Poly){{tA[l]},{1,sub(-tB[l])}};
		return work(solve2(l,mid),solve2(mid+1,r));
	}
	inline Poly main()
	{
		tA=solve(1,A);   //分治求((a_ie^2x+a_i)/2+(1-a_i)e^x) 
		tB.resize(tA.size());
		for(int i=0;i<(int)tA.size();i++)tB[i]=i-A;
		if((int)tA.size()<n)tA.resize(n),tB.resize(n);
		//分治展开 e^kx 
		tp=solve2(0,tA.size()-1);
		tp.b=Get_Inv(tp.b,tp.b.size());
		tp.a=Get_Mul(tp.a,tp.b,n+1);
		for(int i=0;i<=n;i++)tp.a[i]=1ll*tp.a[i]*ifac[i]%mod;
		//ksm求A的方案数 
		tp.b.resize(n+1);
		for(int i=0;i<=n;i++)(i&1)?tp.b[i]=0:tp.b[i]=ifac[i];
		tp.b=Get_Ksm(tp.b,n+1,A);
		return tp;
	}
}
namespace work_B
{
	Poly tp;
	inline Poly main()
	{
		//ksm求B的方案数和价值 
		tp.resize(n+1);
		for(int i=0;i<=n;i+=2)tp.b[i]=ifac[i+1];
		tp.b=Get_Ksm(tp.b,n+1,B);
		for(int i=n;i-B>=0;i--)tp.b[i]=tp.b[i-B];
		for(int i=0;i<B;i++)tp.b[i]=0;
		int mul=1;
		for(int i=1;i<=B;i++)mul=1ll*mul*b[i]%mod;
		for(int i=B;i<=n;i+=2)tp.a[i]=1ll*tp.b[i]*mul%mod;
		return tp;
	}
}
namespace work_P
{
	poly solve(int l,int r)
	{
		if(l==r)return poly{sub(1-p[l]),p[l]};
		return Get_Mul(solve(l,(l+r)>>1),solve(((l+r)>>1)+1,r));
	}
	inline poly main(){return solve(1,n);}//分治求 P 
}
inline poly merge(Poly a,Poly b)//合并A，B 
{	
	a.a=Get_Mul(a.a,b.a,n+1);
	a.b=Get_Mul(a.b,b.b,n+1);
	for(int i=B;i<=n;i+=2)a.a[i]=1ll*a.a[i]*ksm(a.b[i],mod-2)%mod;
	return a.a;
}
int main()
{
	n=read(),A=read(),B=read();
	a.resize(A+1),b.resize(B+1),p.resize(n+1);
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=A;i++)a[i]=read();
	for(int i=1;i<=B;i++)b[i]=read();
	init(N>>1);
	AB=merge(work_A::main(),work_B::main());
	P=work_P::main();
	for(int i=B;i<=n;i+=2)ans=(ans+1ll*AB[i]*P[i])%mod;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：IdnadRev (赞：0)

场上被自己演了没过，其实还是挺简单的。

拆成计算期望过线人数和每个过线人数对应的期望价值，前者无非是一个分治乘。

后者分奇、偶两种奖品，即计算：

$$\prod(1+a_i(\frac{e^x+e^{-x}}{2}-1))\prod b_i(\frac{e^x-e^{-x}}{2})$$

后半边很容易考虑，前半部分先变一下形：

$$e^{-Ax}\prod(\frac{a_ie^{2x}}{2}+(1-a_i)e^x+\frac{a_i}{2})$$

换元，令 $x$ 为 $e^x$，那么就是一个分治乘，但是我们要还原系数。

即对于所有 $k$，求出：

$$\sum_i f_ii^k$$

根据 [P7431 [THUPC2017] 小 L 的计算题](https://www.luogu.com.cn/problem/P7431) 的技巧，我们即求：

$$\sum_kx^k\sum_i f_ii^k=\sum_if_i\sum_k(ix)^k=\sum_i\frac{f_i}{1-ix}$$

这个东西直接分治通分就好了，复杂度 $O(n\log^2 n)$。

---

