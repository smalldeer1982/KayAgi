# 约定（Promise）

## 题目背景

在化为废墟的城市中，大雨倾盆而降。

「魔女之夜」被击败后，圆和焰也已遍体鳞伤，因魔力不足而倒地不起。

「我们，也已经完了......」圆轻叹道。  

「那悲叹之种呢？」焰的语气中还带着一丝希望。

圆沉默不语，望着天空，只是无奈地摇了摇头。

「是吗...... 我说，我们就这样一起变成怪物，把这世界的一切都搞得一团糟吧。」焰说着，不由地啜泣起来。「把那些讨厌的事和悲伤的事，全都和没发生过一样，破坏掉、破坏掉、破坏殆尽...... 你不觉得，这样也很好吗？」

随着一声清脆的碰撞，焰感觉到魔力流入了自己的灵魂宝石内。她转头看见圆正微笑着，拿着一枚悲叹之种。

「刚才那是骗你的，」圆的笑容依旧那么甜美，「我还留着一个呢。」

焰慌忙抱住了圆的手臂，问到：「为什么，为什么要给我？」

「因为有件我做不到，但是小焰能做到的事，我想拜托你...... 小焰，你可以回到过去对吧？你说过，为了避免这样的结局，而改写过历史的吧......」

「嗯...」

圆也终于忍不住悲伤，晶莹的泪珠从她脸上滑落。「你能去救救那个还没被丘比欺骗的，笨蛋的我吗？」

**「我答应你，一定会救你的！无论重复多少次，我都会保护好你！」**

「太好了......」圆平静了下来，但下一瞬间，她的灵魂宝石中就散出了黑雾，她的表情也痛苦地扭曲了起来。「再......拜托你一件事可以吗？」

焰轻轻点头答应。

「我，不想变成魔女......」圆的声音更加虚弱，「就算有讨厌的事和悲伤的事，但我想守护的东西，在这世上还有很多。」圆艰难地抬起手臂，支撑着手中漆黑的灵魂宝石。

「小圆......」焰拔出手枪，对准了圆的灵魂宝石。在焰的痛哭声中，她扣下了扳机。


## 题目描述

澪正陪着铃一起 N 刷《魔法少女小圆》，看到全剧最催人泪下的情节之一时，家长却突然推门进来了。澪不想被发现自己在摸鱼，就迅速切换界面，假装她们在做一道计数题：


> 定义一棵有标号、有根、不区分左右儿子的二叉树的权值是：以「根节点的所有儿子节点」为根的子树的权值之和加上 $d$，特别定义只有一个节点的树权值为 $1$。求所有 $n$ 个节点的这种树权值的 $k$ 次方和，答案对 $998244353$ 取模。

「这不是那个什么 [NaCly_Fish's Math Contest](https://www.luogu.com.cn/contest/53104) 的题... 吗？」铃看了看题，小声说道，「好无聊哦，不看这题。」

## 说明/提示

【样例 $1$ 解释】

$3$ 个节点的有标号有根二叉树有 $9$ 种，分别如下，其中标红的节点表示树根。
![](https://cdn.luogu.com.cn/upload/image_hosting/266knse0.png)  
由于 $k=0$，所有树权值的 $k$ 次方和就等于树的总数，故答案为 $9$。

【样例 $2$ 解释】  
接上图，图中第一行的树权值都为 $5$，第二行的树权值为 $4$，故答案为 $6\times 5^2+3\times 4^2=198$。

【数据范围】

**本题采用捆绑测试。**

Subtask1（5 pts）：$n \le 6$；  
Subtask2（9 pts）：$k=0$，$n\le 10^7$；      
Subtask3（14 pts）：$n\le 10^5$；   
Subtask4（18 pts）：$k \le 4000$，$n\le 10^7$；  
Subtask5（23 pts）：$k \le 10^5$；  
Subtask6（31 pts）：无特殊限制。

对于 $100\%$ 的数据，$2\le n,d \le 9\times 10^8$，$0\le k \le 5\times 10^6$。



## 样例 #1

### 输入

```
3 0 2```

### 输出

```
9```

## 样例 #2

### 输入

```
3 2 2```

### 输出

```
198```

## 样例 #3

### 输入

```
4 3 2```

### 输出

```
16008```

## 样例 #4

### 输入

```
6 4 2```

### 输出

```
58351320```

## 样例 #5

### 输入

```
514 250 114```

### 输出

```
354914151```

# 题解

## 作者：NaCly_Fish (赞：15)

update：修正了笔误

题目中的组合推导并不复杂，仿照有标号有根树计数的方法，设 $n!k![x^ny^k]F$ 表示所有 $n$ 个点的有标号有根二叉树权值 $k$ 次方和，可以列出方程

$$F=x\text e^y+x\text e^{dy}F + \frac{1}{2}x\text e^{dy}F^2$$

如果不能直接推出这个方程，也可以先发现树的权值只与其节点数和叶子数量有关。先计量 $n$ 个点、$m$ 个叶子的二叉树个数，经过处理也可以得到一样的结果。

对 $x$ 这一维使用拉格朗日反演，把原式先化为

$$x=\frac{F}{\text e^y+\text e^{dy}F+\text e^{dy}F^2/2}$$
得到
$$[x^ny^k]F=\frac 1n[x^{n-1}y^k]\left( \text e^y+\text e^{dy}x+\frac{\text e^{dy}x^2}{2}\right)^n$$
$$=\frac 1n[y^k]\sum_{i=0}^n \binom ni \text e^{(n-i+di)y}[x^{n-1}]\left( x+\frac{x^2}{2}\right)^i$$
这个 $\text e$ 上的指数看着很难受，设 $m(d-1)\equiv n \pmod p$，化为

$$\frac{(d-1)^k}{n}[y^k]\text e^{my}\sum_{i=0}^n \binom ni \text e^{iy}[x^{n-1}]\left( x+\frac{x^2}{2}\right)^i$$
现在设
$$g(z)=\sum_{i=0}^n \binom ni z^i[x^{n-1}] \left( x+\frac{x^2}{2}\right)^i=[x^{n-1}]\left( 1+zx+\frac{zx^2}{2}\right)^n$$
注意 $g(z)$ 是一个超几何级数，其系数满足简单的一阶整式递推：  

$$(2i-n)(2i+1-n)g_i = 2(n-i+1)(n-i)g_{i-1}$$
写为 ODE 就是

$$(4z^2-2z^3)g''+((6-4n)z+(-4+4n)z^2)g'+(n(n-1)+2n(1-n)z)g=0$$
现在我们想求 $[z^k]\text e^{mz}g(\text e^z)$，可以应用 EI 提出的一套方法。在此之前需要先知道 $G(z)=z^mg(z)$ 的 ODE。对 $G$ 求二阶导可得
$$zG'=mG+z^{m+1}g'$$
$$z^2G''=2mzG'-m(m+1)G+z^{m+2}g''$$
再把 $g''$ 用 $g',g$ 表示就可以了：
$$z^2(4-2z)G''-((-6+4n+8m)z+4(1-n-m)z^2)G'$$   
$$+(m (m + 1) (4 - 2 z) + m ((6 - 4 n) + (4 n - 4) z) + 
 n (n - 1) (2 z - 1))G =0$$
现在要求 $[z^k]G(\text e^z)$，第一步是求 $H(z)=G(z+1)\bmod z^{k+1}$ 满足的 ODE，但这又必须知道 $H(z)$ 的前两项：
$$[z^0]H=G(1)=g(1)=[x^{n-1}]\left( 1+x+\frac{x^2}{2}\right)^n$$
$$[z^1]H=H'(0)=mg'(1)+g(1)$$
这可以用 [整式递推](https://www.luogu.com.cn/problem/P6115) 算法以 $\Theta(\sqrt n \log n)$ 的时间复杂度求解（由于模数固定，也可以分块打表）。在求解过程中可以对整式递推模板微调一下，让最后答案不用再乘 $n!$。

然后就可以递推求 $H(z)$ 的系数，以得到一个多项式 $D(z)$ 使得
$$P_0(z)H(z)+P_1(z)H'(z)+P_2(z)H''(z)=D(z)$$
等式左边就是 $G$ 的 ODE 中直接把 $z$ 换为 $z+1$ 得到的，多项式平移可以暴力处理。右边多出的这个 $D(z)$ 就是因为截断了 $z^k$ 之后的项产生的扰动，它只有常数个非零项。（因此直接对着 $z^k$ 附近提取左侧系数，即可得到 $D(z)$）

最后求出 $\mathcal G(z)=H(z-1)$ 的系数，这样 $[z^k]\mathcal G(\text e^z)$ 就是答案，线性筛求幂即可。注意递推过程中 $D(z-1)$ 的系数可以直接提取（几个二项式系数的线性组合），不需要展开。

另外这里可以在 $\Theta(1)$ 的时间内求出 $\mathcal G(z)$ 最高次项，然后倒着推回去，会有不错的常数优化。不过需要注意一点：若 $n+m<k$，$H(z)$ 的 $k$ 次项为零，这里倒着推会出错，当然也没必要做前面那么复杂，直接线性筛后暴力 $\Theta(n+m)$ 计算即可。

总时间复杂度 $\mathcal O(k+\sqrt n \log n)$。std 几乎不可读，不建议直接贺（ 

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define N 262147
#define M 5000005
#define ll long long
#define reg register
#define p 998244353
using namespace std;

struct Z{
    int v;
    inline Z(const int _v=0):v(_v){}
};

inline Z operator + (const Z& lhs,const Z& rhs){ return lhs.v+rhs.v<p ? lhs.v+rhs.v : lhs.v+rhs.v-p; }
inline Z operator - (const Z& lhs,const Z& rhs){ return lhs.v<rhs.v ? lhs.v-rhs.v+p : lhs.v-rhs.v; }
inline Z operator - (const Z& x){ return x.v?p-x:0; }
inline Z operator * (const Z& lhs,const Z& rhs){ return (ll)lhs.v*rhs.v%p; }
inline Z& operator += (Z& lhs,const Z& rhs){ lhs.v = lhs.v+rhs.v<p ? lhs.v+rhs.v : lhs.v+rhs.v-p; return lhs; }
inline Z& operator -= (Z& lhs,const Z& rhs){ lhs.v = lhs.v<rhs.v ? lhs.v-rhs.v+p : lhs.v-rhs.v; return lhs; }
inline Z& operator *= (Z& lhs,const Z& rhs){ lhs.v = (ll)lhs.v*rhs.v%p; return lhs; }
inline bool operator ! (const Z& x){ return x.v==0; }

struct poly{
    Z a[8];
    int t;
    inline Z operator [] (const int& x) const{ return a[x]; }
    inline Z& operator [] (const int& x){ return a[x]; }

    inline Z eval(const int& x){
        Z res = a[t];
        for(reg int i=t-1;~i;--i) res = a[i]+res*x;
        return res;
    }
}P[8];

struct ode{
    poly b[8];
    int ord,deg;
    inline poly operator [] (const int& x) const{ return b[x]; }
    inline poly& operator [] (const int& x) { return b[x]; }

    inline void update(){
        for(int i=0;i<8;++i) b[i].t = deg;
    }
};

inline Z check1(const Z* f,const ode& G,int n){
    Z res = 0,rfac;
    for(int j=0;j<=min(n,G.deg);++j){
        rfac = 1;
        for(int i=0;i<=G.ord;++i){
            res += G[i][j]*rfac*f[n-j+i];
            rfac *= (n-j+1+i);
        }
    }
    return res;
}

inline Z power(Z a,int t){
    Z res = 1;
    while(t){
        if(t&1) res *= a;
        a *= a;
        t >>= 1;
    }
    return res;
}

Z fpw[M];
int pr[348515];
bool vis[M];

void sieve(int n,int k){
    fpw[1] = 1;
    int cnt = 0;
    for(int i=2;i<=n;++i){
        if(!vis[i]){
            vis[i] = true;
            pr[++cnt] = i;
            fpw[i] = power(i,k);
        }
        for(int j=1;j<=cnt&&i*pr[j]<=n;++j){
            fpw[i*pr[j]] = fpw[i]*fpw[pr[j]];
            vis[i*pr[j]] = true;
            if(i%pr[j]==0) break;
        }
    }
}

int ms,deg;

struct matrix{
    Z a[2][2];
    inline matrix(){ memset(a,0,sizeof(a)); }

    inline matrix operator * (const matrix& b) const{
        matrix res;
        res.a[0][0] = a[0][0]*b.a[0][0]+a[0][1]*b.a[1][0]; 
        res.a[1][0] = a[1][0]*b.a[0][0]+a[1][1]*b.a[1][0];
        res.a[0][1] = a[0][0]*b.a[0][1]+a[0][1]*b.a[1][1];
        res.a[1][1] = a[1][0]*b.a[0][1]+a[1][1]*b.a[1][1];
        return res;    
    }
}I;

inline matrix getmat(int x){
    matrix res = matrix();
    Z p0 = P[0].eval(x+ms);
    for(reg int i=0;i!=ms-1;++i) res.a[i+1][i] = p0;
    for(reg int i=0;i!=ms;++i) res.a[i][ms-1] = -P[ms-i].eval(x+ms);
    return res;
}

Z fac[N],ifac[N],rt[N],facm[N],inv[M];
int rev[N];
int siz;

inline int getlen(int n){ return 1<<(32-__builtin_clz(n)); }

void init(int n,int k){
    int lim = 1;
    while(lim<=n) lim <<= 1,++siz;
    for(reg int i=1;i!=lim;++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<(siz-1));
    Z w = power(3,(p-1)>>siz);
    inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = rt[lim>>1] = 1;
    for(int i=lim>>1|1;i!=lim;++i) rt[i] = rt[i-1]*w;
    for(int i=(lim>>1)-1;i;--i) rt[i] = rt[i<<1];
    for(int i=2;i<=n;++i) fac[i] = fac[i-1]*i;
    ifac[n] = power(fac[n],p-2);
    for(int i=n-1;i;--i) ifac[i] = ifac[i+1]*(i+1);
    for(int i=2;i<=k;++i) inv[i] = inv[p%i]*(p-p/i);
    I.a[0][0] = I.a[1][1] = 1;
}

inline void dft(Z *f,int lim){
    static unsigned long long a[N];
    reg int x,shift = siz-__builtin_ctz(lim);
    for(reg int i=0;i!=lim;++i) a[rev[i]>>shift] = f[i].v;
    for(reg int mid=1;mid!=lim;mid<<=1)
    for(reg int j=0;j!=lim;j+=(mid<<1))
    for(reg int k=0;k!=mid;++k){
        x = a[j|k|mid]*rt[mid|k].v%p;
        a[j|k|mid] = a[j|k]+p-x;
        a[j|k] += x;
    }
    for(reg int i=0;i!=lim;++i) f[i] = a[i]%p;
}

inline void idft(Z *f,int lim){
    reverse(f+1,f+lim);
    dft(f,lim);
    reg int x = p-((p-1)>>__builtin_ctz(lim));
    for(reg int i=0;i!=lim;++i) f[i] *= x;
}

inline void lagrange(const matrix* F1,int n,Z m,matrix* R1){
    static Z pre[N],suf[N],f1[N],f2[N],g[N],inv_[N],ifcm[N],mul;
    int k = n<<1|1,lim = getlen(n<<1);
    facm[0] = 1;
    for(reg int i=0;i<=n;++i){
        facm[0] *= m-n+i;
        ifcm[i] = ifac[i]*ifac[n-i];
    }
    pre[0] = suf[k+1] = 1;
    for(reg int i=1;i<=k;++i) pre[i] = pre[i-1]*(m-n+i-1);
    for(reg int i=k;i;--i) suf[i] = suf[i+1]*(m-n+i-1);
    mul = power(pre[k],p-2);
    for(reg int i=1;i<=k;++i) inv_[i] = mul*pre[i-1]*suf[i+1];
    for(reg int i=1;i<=n;++i) facm[i] = facm[i-1]*(m+i)*inv_[i];
    for(reg int i=0;i!=k;++i) g[i] = inv_[i+1];
    memset(g+k,0,(lim-k+1)<<2);
    dft(g,lim);
    for(reg int i=0;i!=ms;++i)
    for(reg int j=0;j!=ms;++j){
        for(reg int t=0;t<=n;++t) f1[t] = ifcm[t]*((n-t)&1?-F1[t].a[i][j]:F1[t].a[i][j]);
        memset(f1+n+1,0,(lim-n)<<2);
        dft(f1,lim);
        for(reg int t=0;t!=lim;++t) f1[t] *= g[t];
        idft(f1,lim);
        for(reg int t=0;t<=n;++t) R1[t].a[i][j] = f1[t+n]*facm[t];
    }
}

inline matrix ff(int d,int x){
    matrix res = getmat(x);
    for(reg int i=1;i!=d;++i) res = res*getmat(x+i);
    return res;
}

inline Z gg(int d,int x){
    Z res = P[0].eval(x);
    for(reg int i=1;i!=d;++i) res *= P[0].eval(x+i);
    return res;
}

int kk;

matrix magic(int s,int t){ 
    static Z invs = power(s,p-2);
    static matrix f[N],fd[N];
    int st[30],top = 0,x = s,d = 1,kd;
    while(x){
        st[++top] = x;
        x >>= 1;
    }
    for(reg int i=0;i<=kk;++i){
        x = i*s;
        f[i] = getmat(x);
    }
    --top;
    while(top--){
        kd = kk*d;
        lagrange(f,kd,kd+1,f+kd+1);
        f[kd<<1|1] = matrix();
        lagrange(f,kd<<1,d*invs,fd);
        for(reg int i=0;i<=(kd<<1);++i) f[i] = f[i]*fd[i];
        d <<= 1;
        if(!(st[top+1]&1)) continue;
        kd = kk*(d+1);
        for(reg int i=kk*d+1;i<=kd;++i){
            x = i*s;
            f[i] = ff(d,x);
        }
        for(reg int i=0;i<=kd;++i){
            x = i*s;
            f[i] = f[i]*getmat(x+d);
        }
        ++d;
    }
    matrix r1 = I;
    for(reg int i=0;i<=t;++i) r1 = r1*f[i];
    return r1;
}

Z P_recursive(const Z *a,int n){
    int tn = n-ms+1,s;
    s = ceil(sqrt(tn*1.0/kk))+1;
    matrix mul = magic(s,(tn-s)/s);
    Z res = 0;
    for(reg int i=(tn/s)*s;i!=tn;++i) mul = mul*getmat(i);
    for(int i=0;i!=ms;++i) res += a[i]*mul.a[i][ms-1];
    return res;
}

inline Z binom(int n,int m){
    if(n<m) return Z(0);
    return fac[n]*ifac[m]*ifac[n-m];
}

Z prepare(int k,int n){ 
    static Z a[N];
    deg = kk = 1;
    ms = 2;
    P[0][1] = 1;
    P[1][0] = p-(k+1),P[1][1] = 1;
    P[2][0] = p-(k+1),P[2][1] = inv[2];
    a[0] = 1,a[1] = k;
    P[0].t = P[1].t = P[2].t = 1;
    if(n<=1000){
        for(int i=2;i<=n;++i){
            Z res = P[1].eval(i)*a[i-1]+P[2].eval(i)*a[i-2];
            a[i] = -res*power(P[0].eval(i),p-2);
        }
        return a[n]*fac[n];
    }
    return P_recursive(a,n);
}

ode G,H;

void poly_shift(){
    for(int i=0;i<=G.ord;++i)
    for(int k=0;k<=G.deg;++k)
    for(int j=k;j<=G.deg;++j)
        H[i][k] += G[i][j]*binom(j,k);
}

int n,k,d,len,lim;
Z g[M],h[M],pre[M],suf[M];
Z ans,m,r1,r2,r3;

inline Z check2(const int& n){
    Z res = H[0][0]*h[n]+H[1][0]*h[n+1]*(n+1);
    res += H[0][1]*h[n-1]+(H[1][1]*h[n]+H[2][1]*h[n+1]*(n+1))*n;
    res += (H[1][2]*h[n-1]+H[2][2]*h[n]*n)*(n-1);
    return res+H[2][3]*h[n-1]*(n-1)*(n-2);
}

int main(){ 
    scanf("%d%d%d",&n,&k,&d);
    m = power(d-1,p-2)*n;
    init(131075,max(1000,k)+3); 
    if(n+m.v<k){
        Z pw2 = power(2,p-n);
        for(int i=0;i<=n;++i){
            g[i] = fac[n-1]*binom(n,i)*binom(i,n-i-1)*pw2;
            pw2 += pw2;
        }
        sieve(n+m.v,k);
        for(int i=0;i<=n;++i) ans += fpw[m.v+i]*g[i];
        ans *= power(d-1,k); 
        printf("%d\n",ans.v);
        return 0;
    }
    Z _n = n,tmp;
    G[0][0] = p-m*(m+1)*4+m*(6-4*_n)+_n*(1+p-_n);
    G[0][1] = m*(m+1)*2+m*(4*_n-4)+2*_n*(_n-1);
    G[1][1] = 4*_n+8*m-6,G[1][2] = 4*(1+p-_n-m);
    G[2][2] = p-4,G[2][3] = 2;
    G.ord = H.ord = 2,G.deg = H.deg = 3;
    poly_shift();
    G.update(),H.update();
    h[0] = prepare(n,n-1);
    if(k==0){
        printf("%d",h[0].v);
        return 0;
    }
    h[1] = (h[0]-prepare(n-1,n-1))*n+h[0]*m;
    Z invh0 = power(H[2][0],p-2);
    for(int i=0;i<=min(k-2,2);++i) h[i+2] = -check1(h,H,i)*invh0*inv[i+1]*inv[i+2];
    for(int i=3;i<=k-2;++i) h[i+2] = -check2(i)*invh0*inv[i+1]*inv[i+2];
    r1 = check1(h,H,k-1),r2 = check1(h,H,k),r3 = check1(h,H,k+1);
    g[k] = h[k],g[k-1] = h[k-1]-h[k]*k;
    pre[0] = suf[k+1] = 1;
    for(int j=1;j<=k;++j) pre[j] = G[0][1]+(G[1][2]+(j-2)*2)*(j-1);
    for(int j=k;j;--j) suf[j] = suf[j+1]*pre[j];
    for(int j=1;j<=k;++j) pre[j] *= pre[j-1]; 
    Z Inv = power(pre[k],p-2),c1 = r1,c2 = k*r2,c3 = inv[2]*(k+1)*k*r3,falfac = 1;
    if(Inv.v==0){
        return 1;
    }
    for(int j=k-1;j>1;--j){
        Z tmp1 = (G[0][0]+j*(G[1][1]-(j-1)*4))*g[j];
        Z tmp2 = (k-j)&1?(c1-c2+c3):(c2-c1-c3);
        g[j-1] = (tmp2*falfac-tmp1)*Inv*pre[j-1]*suf[j+1];
        c1 *= inv[k-j],c2 *= inv[k-j+1],c3 *= inv[k-j+2];
        falfac *= j;
    }
    sieve(k,k);
    for(int i=1;i<=k;++i) ans += fpw[i]*g[i];
    ans *= power(d-1,k);
    printf("%d\n",ans.v);
    return 0;   
}
```

---

