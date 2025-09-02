# 「EZEC-9」Meltel

## 题目背景

> 貴方だけは許せない。  
> 『唯独你不可原谅。』  
> 貴方だけは私の全てを許してくれた。  
> 『唯独你宽恕了我的一切。』  
> 貴方だけは私の全てを奪い尽くし食い尽くし  
> 『唯独你覆灭了我的世界，』  
> 焼き尽くして全てを無駄にした。  
> 『焚烧殆尽，山陷地裂。』

## 题目描述

给定正整数 $n$，请对 $s=0,1, \dots, n$，计数满足存在恰好 $s$ 棵二叉树的 $n$ 个结点的由有标号有根树组成的有标号森林的个数。  
对 $998244353$ 取模。

定义二叉树为每个结点只有不超过 $2$ 个儿子的有标号有根树。  
定义两片森林不同，当且仅当存在两个结点的父亲不同（根结点视为没有父亲）。

## 说明/提示

【样例 $1$ 说明】

$3$ 个点只可能出现二叉树，因此 $s=0$ 的方案数为 $0$。  
$3$ 个点的有标号有根二叉树有 $9$ 种，因此 $s=1$ 的方案数为 $9$。  
$2$ 个点的有标号有根二叉树有 $2$ 种，因此 $s=2$ 的方案数为 $3 \times 2 = 6$。  
单个结点也算有标号有根二叉树，因此 $s=3$ 的方案数为 $1$。

【数据规模与约定】

**本题采用捆绑测试。**

-  Subtask 1（5 points）：$n\le 5$。
-  Subtask 2（5 points）：$n \le 10$。
-  Subtask 3（30 points）：$n\le 10^3$。
-  Subtask 4（30 points）：$n\le 8\times 10^3$。
-  Subtask 5（30 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 2 \times 10^5$。


## 样例 #1

### 输入

```
3```

### 输出

```
0 9 6 1```

## 样例 #2

### 输入

```
4```

### 输出

```
4 60 48 12 1```

## 样例 #3

### 输入

```
5```

### 输出

```
85 560 480 150 20 1```

# 题解

## 作者：NaCly_Fish (赞：13)

update：修复了一些 typo。

出题人迟迟没发题解，那我来水一篇。
****
先考虑「有根有标号二叉树」数量的 EGF，设为 $f(x)$；那么我们知道 $f(x)$ 应满足方程：
$$f(x)=x\left(1+f(x)+\frac{f(x)^2}{2}\right)$$


设「有标号有根树」数量的 EGF 为 $g(x)$，那么答案就应该是：
$$a_s=\left[ \frac{x^n}{n!}\right]\left( \frac{f(x)^s}{s!}\times\text e^{g(x)-f(x)}\right)$$
这个也容易理解，要求二叉树恰好有 $s$ 个，剩下的点是非二叉树组成的森林，两种再拼接起来就是答案。

~~众所周知，alpha1022 喜欢出拉格朗日反演题~~。那么我们如何用拉格朗日反演呢？根据 EI 的指导，可以将其化为扩展拉格朗日反演的形式。


设 $\text e^{g(x)-f(x)}=A(x)$，$f(x)$ 的复合逆为 $h(x)$，以及 $P_s(x)=x^sA(h(x))$，答案就可以写为

$$\frac{s!}{n!}a_s=[x^n]P_s(f(x))$$
直接使用拉格朗日反演就有
$$\frac{s!}{n!}a_s=\frac 1n[x^{n-1}]P'_s(x)\left(\frac{x}{h(x)} \right)^n$$
$$=\frac 1n[x^{n-1}]\left( sx^{s-1}A(h(x))+x^s A(h(x))'\right)\left(\frac{x}{h(x)} \right)^n$$
$$=\frac 1n[x^{n-s}](s A(h(x))+xA(h(x))')\left(\frac{x}{h(x)} \right)^n$$
那一大坨式子可以分成两部分，分别计算后提取系数即可。

现在再考虑如何求 $A(h(x))$，将原式展开，就有：
$$A(h(x))=\text e^{g(h(x))-x}$$
只要求出 $g(h(x))$，问题就解决了。注意到 $f(x)$ 是个代数幂级数，其复合逆也很容易求，是这样一个有理分式：
$$x=h(x)\left(1+x+\frac{x^2}{2}\right)$$
代入有标号有根树的方程中：
$$g(h(x))=h(x)\text e^{g(h(x))}$$
牛顿迭代求解即可，时间复杂度 $\Theta(n \log n)$。

补个代码，为了可读性没做什么优化：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 524292
#define ll long long
#define reg register
#define p 998244353
using namespace std;

inline int add(const int& x,const int& y){ return x+y>=p?x+y-p:x+y; }
inline int dec(const int& x,const int& y){ return x<y?x-y+p:x-y; }

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int siz;
int rev[N],rt[N],inv[N],fac[N],ifac[N];

void init(int n){
    int lim = 1;
    while(lim<=n) lim <<= 1,++siz;
    for(reg int i=0;i!=lim;++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<(siz-1));
    int w = power(3,(p-1)>>siz);
    inv[1] = rt[lim>>1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for(reg int i=(lim>>1)+1;i!=lim;++i) rt[i] = (ll)rt[i-1]*w%p;
    for(reg int i=(lim>>1)-1;i;--i) rt[i] = rt[i<<1];
    for(reg int i=2;i<=n;++i) inv[i] = (ll)(p-p/i)*inv[p%i]%p;
    for(int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
}

inline void dft(int *f,int n){
    static unsigned long long a[N];
    reg int x,shift = siz-__builtin_ctz(n);
    for(reg int i=0;i!=n;++i) a[rev[i]>>shift] = f[i];
    for(reg int mid=1;mid!=n;mid<<=1)
    for(reg int j=0;j!=n;j+=(mid<<1))
    for(reg int k=0;k!=mid;++k){
        x = a[j|k|mid]*rt[mid|k]%p;
        a[j|k|mid] = a[j|k]+p-x;
        a[j|k] += x;
    }
    for(reg int i=0;i!=n;++i) f[i] = a[i]%p;
}

inline void idft(int *f,int n){
    reverse(f+1,f+n);
    dft(f,n);
    int x = p-((p-1)>>__builtin_ctz(n));
    for(reg int i=0;i!=n;++i) f[i] = (ll)f[i]*x%p;
}

inline int getlen(int n){
    return 1<<(32-__builtin_clz(n));
}

inline void inverse(const int *f,int n,int *r){
    static int g[N],h[N],st[30];
    memset(g,0,getlen(n<<1)<<2);
    int lim = 1,top = 0;
    while(n){
        st[++top] = n;
        n >>= 1;
    }
    g[0] = f[0]==1?1:p-1;
    while(top--){
        n = st[top+1];
        while(lim<=(n<<1)) lim <<= 1;
        memcpy(h,f,(n+1)<<2);
        memset(h+n+1,0,(lim-n)<<2);
        dft(g,lim),dft(h,lim);
        for(reg int i=0;i!=lim;++i) g[i] = g[i]*(2-(ll)g[i]*h[i]%p+p)%p;
        idft(g,lim);
        memset(g+n+1,0,(lim-n)<<2);
    }
    memcpy(r,g,(n+1)<<2);
}

inline void log(const int *f,int n,int *r){
    static int g[N],h[N];
    inverse(f,n,g);
    for(reg int i=0;i!=n;++i) h[i] = (ll)f[i+1]*(i+1)%p;
    h[n] = 0;
    int lim = getlen(n<<1);
    memset(g+n+1,0,(lim-n)<<2);
    memset(h+n+1,0,(lim-n)<<2);
    dft(g,lim),dft(h,lim);
    for(reg int i=0;i!=lim;++i) g[i] = (ll)g[i]*h[i]%p;
    idft(g,lim);
    for(reg int i=1;i<=n;++i) r[i] = (ll)g[i-1]*inv[i]%p;
    r[0] = 0;
}

inline void exp(const int *f,int n,int *r){
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
        memcpy(h,g,(n+1)<<2);
        memset(h+n+1,0,(lim-n)<<2);
        log(g,n,g);
        for(reg int i=0;i<=n;++i) g[i] = dec(f[i],g[i]);
        g[0] = add(g[0],1);
        dft(g,lim),dft(h,lim);
        for(reg int i=0;i!=lim;++i) g[i] = (ll)g[i]*h[i]%p;
        idft(g,lim);
        memset(g+n+1,0,(lim-n)<<2);
    }
    memcpy(r,g,(n+1)<<2);
}

inline void iterate(const int *h,int n,int *r){
    static int f[N],g[N],_h[N],fz[N],st[30];
    memset(f,0,getlen(n<<1)<<2);
    int lim = 1,top = 0;
    while(n){
        st[++top] = n;
        n >>= 1;
    }
    f[0] = 1;
    while(top--){
        n = st[top+1];
        while(lim<=(n<<1)) lim <<= 1;
        exp(f,n,g);
        memcpy(_h,h,(n+1)<<2);
        memset(_h+n+1,0,(lim-n)<<2),memset(g+n+1,0,(lim-n)<<2);
        dft(g,lim),dft(_h,lim);
        for(int i=0;i!=lim;++i) g[i] = (ll)g[i]*_h[i]%p;
        idft(g,lim);
        memset(g+n+1,0,(lim-n)<<2);
        for(int i=0;i<=n;++i) fz[i] = dec(g[i],f[i]);
        g[0] = p-1;
        inverse(g,n,g);
        memset(fz+n+1,0,(lim-n)<<2);
        dft(fz,lim),dft(g,lim);
        for(int i=0;i!=lim;++i) g[i] = (ll)g[i]*fz[i]%p;
        idft(g,lim);
        for(int i=0;i<=n;++i) f[i] = dec(f[i],g[i]);
    }
    memcpy(r,f,(n+1)<<2);
}

int n,lim;
int A[N],h[N],hpw[N],dA[N],f[N];
const int inv2 = 499122177;

int main(){
    scanf("%d",&n);
    init(n<<1);
    h[0] = 0,hpw[0] = h[1] = 1;
    for(int i=2;i<=n;++i){ // 递推算 h(x)
        h[i] = (h[i-1]+(ll)inv2*h[i-2])%p;
        h[i] = h[i]==0?0:p-h[i];
    }
    hpw[1] = n; // (x/h(x))^n
    for(int i=1;i<n;++i) hpw[i+1] = (((ll)n*(hpw[i]+hpw[i-1])%p-(ll)inv2*(i-1)%p*hpw[i-1]-(ll)i*hpw[i])%p+p)*inv[i+1]%p;
    iterate(h,n,A);
    A[1]--;
    exp(A,n,A);
    lim = getlen(n<<1);
    for(int i=0;i<=n;++i) dA[i] = (ll)A[i]*i%p;
    dft(hpw,lim),dft(A,lim),dft(dA,lim);
    for(int i=0;i!=lim;++i){
        A[i] = (ll)A[i]*hpw[i]%p;
        dA[i] = (ll)dA[i]*hpw[i]%p;
    }
    idft(A,lim),idft(dA,lim);
    for(int s=0;s<=n;++s){
        int ans = ((ll)s*A[n-s]+dA[n-s])%p*fac[n-1]%p*ifac[s]%p;
        printf("%d ",ans);
    }
    return 0;   
}
```

---

