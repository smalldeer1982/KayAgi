# 「KrOI2021」Feux Follets 弱化版

## 题目描述

设 $\text{cyc}_\pi$ 将长为 $n$ 的排列 $\pi$ 当成置换时所能分解成的循环个数。给定两个整数 $n,k$ 和一个 $k-1$ 次多项式，求：

$$
\sum\limits_{\pi}F(\text{cyc}_{\pi})
$$

其中 $\pi$ 是长度为 $n$ 且不存在位置 $i$ 使得 $\pi_i=i$ 的排列。

## 说明/提示

### 数据范围

对于 $100\%$ 的数据，$1\leq n,k\leq 10^5$。

## 样例 #1

### 输入

```
3 2
0 1```

### 输出

```
2```

## 样例 #2

### 输入

```
6 4
11 43 27 7```

### 输出

```
53070```

## 样例 #3

### 输入

```
6 4
9 72 22 7```

### 输出

```
60990```

# 题解

## 作者：Aleph1022 (赞：13)

本文同步发表于我的博客：<https://www.alpha1022.me/articles/lg-7439.htm>。

首先把给定的多项式转成牛顿级数，即转写成
$$
F(x) = \sum\limits_{i=0}^{k-1} a_i \binom xi
$$

然后套路的拆开项，考虑计算
$$
\sum\limits_{\pi} \binom{{\rm cyc}_{\pi}}{k}
$$

让我们考虑一个错排，显然它是由非自环的循环置换为基本单位构成的，即
$$
{\rm e}^{-x-\ln(1-x)}
$$

然后考虑从中选 $k$ 个。不难发现这只需要对一个循环置换附加一个因子 $(1+y)$ 即可做到：
$$
{\rm e}^{(1+y)(-x-\ln(1-x))}
$$

首先求考虑求 $[x^n] {\rm e}^{y(-x-\ln(1-x))}$，然后使用二项式展开并卷积处理。

设 $\frac{f^2}2 = -x-\ln(1-x)$，显然其存在复合逆，设复合逆为 $g$。  
则
$$
[x^n]{\rm e}^{yf^2/2} = \frac1n[x^{n-1}] \frac{\partial{\rm e}^{yx^2/2}}{\partial x} \left(\frac xg\right)^n
$$

我们知道
$$
\frac{\partial{\rm e}^{yx^2/2}}{\partial x} = xy {\rm e}^{yx^2/2} = \sum\limits_{i\ge 0} \frac{x^{2i+1}y^{i+1}}{2^ii!}
$$

因此
$$
\frac1n[x^{n-1} y^k] \frac{\partial{\rm e}^{yx^2/2}}{\partial x} \left(\frac xg\right)^n = \frac1{n2^{k-1} (k-1)!} [x^{n-2k}] \left(\frac xg\right)^n
$$

考虑求 $g$。我们知道
$$
\frac{f^2}2 = -x-\ln(1-x)
$$

所以
$$
\frac{x^2}2 = -g-\ln(1-g)
$$

不幸的是如果我们直接对这个式子牛顿迭代，会出现一些意料之外的问题。  
所以不妨将其改写成
$$
\sqrt{-2g-2\ln(1-g)}-x=0
$$

然后对其牛顿迭代。

时间复杂度 $O(n \log^2 n)$（视 $n,k$ 同阶）。

代码：
```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define add(a,b) (a + b >= mod ? a + b - mod : a + b)
#define dec(a,b) (a < b ? a - b + mod : a - b)
#define ls (p << 1)
#define rs (ls | 1)
using namespace std;
const int N = 1e5;
const int mod = 998244353;
int n,k,m;
inline int fpow(int a,int b)
{
    int ret = 1;
    for(;b;b >>= 1)
        (b & 1) && (ret = (long long)ret * a % mod),a = (long long)a * a % mod;
    return ret;
}
namespace Poly
{
    const int LG = 17;
    const int N = 1 << LG + 1;
    const int G = 3;
    int lg2[N + 5];
    int rev[N + 5],fac[N + 5],ifac[N + 5],inv[N + 5];
    int rt[N + 5];
    inline void init()
    {
        for(register int i = 2;i <= N;++i)
            lg2[i] = lg2[i >> 1] + 1;
        rt[0] = 1,rt[1 << LG] = fpow(G,(mod - 1) >> LG + 2);
        for(register int i = LG;i;--i)
            rt[1 << i - 1] = (long long)rt[1 << i] * rt[1 << i] % mod;
        for(register int i = 1;i < N;++i)
            rt[i] = (long long)rt[i & i - 1] * rt[i & -i] % mod;
        fac[0] = 1;
        for(register int i = 1;i <= N;++i)
            fac[i] = (long long)fac[i - 1] * i % mod;
        ifac[N] = fpow(fac[N],mod - 2);
        for(register int i = N;i;--i)
            ifac[i - 1] = (long long)ifac[i] * i % mod;
        for(register int i = 1;i <= N;++i)
            inv[i] = (long long)ifac[i] * fac[i - 1] % mod;
    }
    struct poly
    {
        vector<int> a;
        inline poly(int x = 0)
        {
            x && (a.push_back(x),1);
        }
        inline poly(const vector<int> &o)
        {
            a = o,shrink();
        }
        inline poly(const poly &o)
        {
            a = o.a,shrink();
        }
        inline void shrink()
        {
            for(;!a.empty() && !a.back();a.pop_back());
        }
        inline int size() const
        {
            return a.size();
        }
        inline void resize(int x)
        {
            a.resize(x);
        }
        inline int operator[](int x) const
        {
            if(x < 0 || x >= size())
                return 0;
            return a[x];
        }
        inline void clear()
        {
            vector<int>().swap(a);
        }
        inline poly rever() const
        {
            return poly(vector<int>(a.rbegin(),a.rend()));
        }
		inline void dif()
		{
			int n = size();
            for(register int i = 0,len = n >> 1;len;++i,len >>= 1)
                for(register int j = 0,*w = rt;j < n;j += len << 1,++w)
                    for(register int k = j,R;k < j + len;++k)
                        R = (long long)*w * a[k + len] % mod,
                        a[k + len] = dec(a[k],R),
                        a[k] = add(a[k],R);
		}
        inline void dit()
        {
			int n = size();
            for(register int i = 0,len = 1;len < n;++i,len <<= 1)
                for(register int j = 0,*w = rt;j < n;j += len << 1,++w)
                    for(register int k = j,R;k < j + len;++k)
                        R = add(a[k],a[k + len]),
                        a[k + len] = (long long)(a[k] - a[k + len] + mod) * *w % mod,
                        a[k] = R;
            reverse(a.begin() + 1,a.end());
            for(register int i = 0;i < n;++i)
                a[i] = (long long)a[i] * inv[n] % mod;
		}
        inline void ntt(int type = 1)
        {
            type == 1 ? dif() : dit();
        }
        friend inline poly operator+(const poly &a,const poly &b)
        {
            vector<int> ret(max(a.size(),b.size()));
            for(register int i = 0;i < ret.size();++i)
                ret[i] = add(a[i],b[i]);
            return poly(ret);
        }
        friend inline poly operator-(const poly &a,const poly &b)
        {
            vector<int> ret(max(a.size(),b.size()));
            for(register int i = 0;i < ret.size();++i)
                ret[i] = dec(a[i],b[i]);
            return poly(ret);
        }
        friend inline poly operator*(poly a,poly b)
        {
            if(a.a.empty() || b.a.empty())
                return poly();
            if(a.size() < 40 || b.size() < 40)
            {
                if(a.size() > b.size())
                    swap(a,b);
                poly ret;
                ret.resize(a.size() + b.size() - 1);
                for(register int i = 0;i < ret.size();++i)
                    for(register int j = 0;j <= i && j < a.size();++j)
                        ret.a[i] = (ret[i] + (long long)a[j] * b[i - j]) % mod;
                ret.shrink();
                return ret;
            }
            int lim = 1,tot = a.size() + b.size() - 1;
            for(;lim < tot;lim <<= 1);
            a.resize(lim),b.resize(lim);
            a.ntt(),b.ntt();
            for(register int i = 0;i < lim;++i)
                a.a[i] = (long long)a[i] * b[i] % mod;
            a.ntt(-1),a.shrink();
            return a;
        }
        poly &operator+=(const poly &o)
        {
            resize(max(size(),o.size()));
            for(register int i = 0;i < o.size();++i)
                a[i] = add(a[i],o[i]);
            return *this;
        }
        poly &operator-=(const poly &o)
        {
            resize(max(size(),o.size()));
            for(register int i = 0;i < o.size();++i)
                a[i] = dec(a[i],o[i]);
            return *this;
        }
        poly &operator*=(poly o)
        {
            return (*this) = (*this) * o;
        }
        poly deriv() const
        {
            if(a.empty())
                return poly();
            vector<int> ret(size() - 1);
            for(register int i = 0;i < size() - 1;++i)
                ret[i] = (long long)(i + 1) * a[i + 1] % mod;
            return poly(ret);
        }
        poly integ() const
        {
            if(a.empty())
                return poly();
            vector<int> ret(size() + 1);
            for(register int i = 0;i < size();++i)
                ret[i + 1] = (long long)a[i] * inv[i + 1] % mod;
            return poly(ret);
        }
        inline poly modxn(int n) const
        {
            if(a.empty())
                return poly();
            n = min(n,size());
            return poly(vector<int>(a.begin(),a.begin() + n));
        }
        inline poly inver(int m) const
        {
            poly ret(fpow(a[0],mod - 2)),f,g;
            for(register int k = 1;k < m;)
            {
                k <<= 1,f.resize(k),g.resize(k);
                for(register int i = 0;i < k;++i)
                    f.a[i] = (*this)[i],g.a[i] = ret[i];
                f.ntt(),g.ntt();
                for(register int i = 0;i < k;++i)
                    f.a[i] = (long long)f[i] * g[i] % mod;
                f.ntt(-1);
                for(register int i = 0;i < (k >> 1);++i)
                    f.a[i] = 0;
                f.ntt();
                for(register int i = 0;i < k;++i)
                    f.a[i] = (long long)f[i] * g[i] % mod;
                f.ntt(-1);
                ret.resize(k);
                for(register int i = (k >> 1);i < k;++i)
                    ret.a[i] = dec(0,f[i]);
            }
            return ret.modxn(m);
        }
        inline pair<poly,poly> div(poly o) const
        {
            if(size() < o.size())
                return make_pair(poly(),*this);
            poly f,g;
            f = (rever().modxn(size() - o.size() + 1) * o.rever().inver(size() - o.size() + 1)).modxn(size() - o.size() + 1).rever();
            g = (modxn(o.size() - 1) - o.modxn(o.size() - 1) * f.modxn(o.size() - 1)).modxn(o.size() - 1);
            return make_pair(f,g);
        }
        inline poly log(int m) const
        {
            return (deriv() * inver(m)).integ().modxn(m);
        }
        inline poly exp(int m) const
        {
            poly ret(1),iv,it,d = deriv(),itd,itd0,t1;
            if(m < 70)
            {
                ret.resize(m);
                for(register int i = 1;i < m;++i)
                {
                    for(register int j = 1;j <= i;++j)
                        ret.a[i] = (ret[i] + (long long)j * operator[](j) % mod * ret[i - j]) % mod;
                    ret.a[i] = (long long)ret[i] * inv[i] % mod;
                }
                return ret;
            }
            for(register int k = 1;k < m;)
            {
                k <<= 1;
                it.resize(k >> 1);
                for(register int i = 0;i < (k >> 1);++i)
                    it.a[i] = ret[i];
                itd = it.deriv(),itd.resize(k >> 1);
                iv = ret.inver(k >> 1),iv.resize(k >> 1);
                it.ntt(),itd.ntt(),iv.ntt();
                for(register int i = 0;i < (k >> 1);++i)
                    it.a[i] = (long long)it[i] * iv[i] % mod,
                    itd.a[i] = (long long)itd[i] * iv[i] % mod;
                it.ntt(-1),itd.ntt(-1),it.a[0] = dec(it[0],1);
                for(register int i = 0;i < k - 1;++i)
                    itd.a[i % (k >> 1)] = dec(itd[i % (k >> 1)],d[i]);
                itd0.resize((k >> 1) - 1);
                for(register int i = 0;i < (k >> 1) - 1;++i)
                    itd0.a[i] = d[i];
                itd0 = (itd0 * it).modxn((k >> 1) - 1);
                t1.resize(k - 1);
                for(register int i = (k >> 1) - 1;i < k - 1;++i)
                    t1.a[i] = itd[(i + (k >> 1)) % (k >> 1)];
                for(register int i = k >> 1;i < k - 1;++i)
                    t1.a[i] = dec(t1[i],itd0[i - (k >> 1)]);
                t1 = t1.integ();
                for(register int i = 0;i < (k >> 1);++i)
                    t1.a[i] = t1[i + (k >> 1)];
                for(register int i = (k >> 1);i < k;++i)
                    t1.a[i] = 0;
                t1.resize(k >> 1),t1 = (t1 * ret).modxn(k >> 1),t1.resize(k);
                for(register int i = (k >> 1);i < k;++i)
                    t1.a[i] = t1[i - (k >> 1)];
                for(register int i = 0;i < (k >> 1);++i)
                    t1.a[i] = 0;
                ret -= t1;
            }
            return ret.modxn(m);
        }
        inline poly sqrt(int m) const
        {
            poly ret(1),f,g;
            for(register int k = 1;k < m;)
            {
                k <<= 1;
                f = ret,f.resize(k >> 1);
                f.ntt();
                for(register int i = 0;i < (k >> 1);++i)
                    f.a[i] = (long long)f[i] * f[i] % mod;
                f.ntt(-1);
                for(register int i = 0;i < k;++i)
                    f.a[i % (k >> 1)] = dec(f[i % (k >> 1)],(*this)[i]);
                g = (2 * ret).inver(k >> 1),f = (f * g).modxn(k >> 1),f.resize(k);
                for(register int i = (k >> 1);i < k;++i)
                    f.a[i] = f[i - (k >> 1)];
                for(register int i = 0;i < (k >> 1);++i)
                    f.a[i] = 0;
                ret -= f;
            }
            return ret.modxn(m);
        }
        inline poly pow(int m,int k1,int k2 = -1) const
        {
            if(a.empty())
                return poly();
            if(k2 == -1)
                k2 = k1;
            int t = 0;
            for(;t < size() && !a[t];++t);
            if((long long)t * k1 >= m)
                return poly();
            poly ret;
            ret.resize(m);
            int u = fpow(a[t],mod - 2),v = fpow(a[t],k2);
            for(register int i = 0;i < m - t * k1;++i)
                ret.a[i] = (long long)operator[](i + t) * u % mod;
            ret = ret.log(m - t * k1);
            for(register int i = 0;i < ret.size();++i)
                ret.a[i] = (long long)ret[i] * k1 % mod;
            ret = ret.exp(m - t * k1),t *= k1,ret.resize(m);
            for(register int i = m - 1;i >= t;--i)
                ret.a[i] = (long long)ret[i - t] * v % mod;
            for(register int i = 0;i < t;++i)
                ret.a[i] = 0;
            return ret;
        }
    };
}
using Poly::init;
using Poly::poly;
inline int C(int n,int m)
{
    return n < m ? 0 : (long long)Poly::fac[n] * Poly::ifac[m] % mod * Poly::ifac[n - m] % mod;
}
poly f,seg[(N << 2) + 5],g;
poly t1,t2;
inline poly comp_xplusa(const poly &f,int a)
{
    int n = f.size();
    poly t1,t2,ret;
    t1.resize(n),t2.resize(n);
    for(register int i = 0,pw = 1;i < n;++i,pw = (long long)pw * a % mod)
        t1.a[n - 1 - i] = (long long)Poly::fac[i] * f[i] % mod,
        t2.a[i] = (long long)Poly::ifac[i] * pw % mod;
    t1 *= t2;
    ret.resize(n);
    for(register int i = 0;i < n;++i)
        ret.a[i] = (long long)Poly::ifac[i] * t1[n - 1 - i] % mod;
    return ret;
}
void build(int n,int p)
{
    if(n == 1)
    {
        seg[p].resize(2),seg[p].a[1] = 1;
        return ;
    }
    int mid = n + 1 >> 1;
    build(mid,ls),build(n - mid,rs);
    seg[p] = seg[ls] * comp_xplusa(seg[rs],dec(0,mid));
}
poly solve(const poly &f,int n,int p)
{
    if(n == 1)
        return f;
    int mid = n + 1 >> 1;
    poly ret;
    ret.resize(n);
    pair<poly,poly> res = f.div(seg[ls]);
    poly t1 = solve(res.second,mid,ls);
    poly t2 = solve(comp_xplusa(res.first,mid),n - mid,rs);
    for(register int i = 0;i < mid;++i)
        ret.a[i] = t1[i];
    for(register int i = mid;i < n;++i)
        ret.a[i] = t2[i - mid];
    return ret;
}
inline poly calc(int m)
{
    poly ret,t,t1,t2,t3;
    ret.resize(2),ret.a[1] = 1;
    for(register int k = 2;k < m;)
    {
        k <<= 1;
        t = 0 - 2 * ret - 2 * (1 - ret).log(k + 1),t.resize(k + 1);
        for(register int i = 0;i < k - 1;++i)
            t.a[i] = t[i + 2];
        t.resize(k - 1),t = t.sqrt(k - 1),t.resize(k);
        for(register int i = k - 1;i;--i)
            t.a[i] = t[i - 1];
        t.a[0] = 0,t1 = t,t1.resize(k),t1.a[1] = dec(t1[1],1);
        for(register int i = 0;i < (k >> 1);++i)
            t1.a[i] = t1[i + (k >> 1)];
        for(register int i = (k >> 1);i < k;++i)
            t1.a[i] = 0;
        t2 = ((1 - ret) * t).modxn((k >> 1) + 1),t2.resize((k >> 1) + 1);
        for(register int i = 0;i < (k >> 1);++i)
            t2.a[i] = t2[i + 1];
        t3.resize(k >> 1);
        for(register int i = 0;i < (k >> 1);++i)
            t3.a[i] = ret[i + 1];
        t2.resize(k >> 1),t2 = (t2.inver(k >> 1) * t3).modxn(k >> 1);
        t1 = (t1 * t2.inver(k >> 1)).modxn(k >> 1),t1.resize(k);
        for(register int i = (k >> 1);i < k;++i)
            t1.a[i] = t1[i - (k >> 1)];
        for(register int i = 0;i < (k >> 1);++i)
            t1.a[i] = 0;
        ret -= t1;
    }
    return ret.modxn(m);
}
int ans;
int main()
{
    init();
    scanf("%d%d",&n,&k),f.resize(k);
    for(register int i = 0;i < k;++i)
        scanf("%d",&f.a[i]);
    build(k,1),f = solve(f,k,1);
    for(register int i = 0;i < k;++i)
        f.a[i] = (long long)f[i] * Poly::fac[i] % mod;
    g = calc(n + 1),g.resize(n + 1);
    for(register int i = 0;i < n;++i)
        g.a[i] = g[i + 1];
    g.resize(n),g = g.pow(n,mod - n,mod - n - 1);
    m = (n >> 1) + 1,t1.resize(m),t2.resize(m);
    for(register int i = 0,pw = 2;i < m;++i,pw = (long long)pw * Poly::inv[2] % mod)
        i && (t1.a[m - i - 1] = (long long)Poly::fac[n - 1] * pw % mod * i % mod * g[n - 2 * i] % mod),
        t2.a[i] = Poly::ifac[i];
    t1 = t1 * t2;
    for(register int i = 0;i < min(k,m);++i)
        ans = (ans + (long long)f[i] * Poly::ifac[i] % mod * t1[m - 1 - i]) % mod;
    printf("%d\n",ans);
}
```

---

## 作者：qwaszx (赞：6)

![](https://ae01.alicdn.com/kf/Uc9663df5788f49c4a0e51723f78afa77D.jpg)

该做法可以求出所有系数，以下是对上面两句话的翻译(

长度非 $1$ 的循环排列的 EGF 为 $\sum_{i\geq 2}\frac{1}{i}x^i=-\ln(1-x)-x$，于是我们要求的就是

$$
\sum_{i\geq 0}\frac{(-\ln(1-x)-x)^i}{i!}\sum_{j}c_ji^j
$$

为了简化后续的计算，我们先用 $\Theta(k\log^2 k)$ 的时间把多项式转为牛顿级数，这样我们要求的就大概是

$$
\sum_{i\geq 0}\frac{(-\ln(1-x)-x)^i}{i!}\sum_{j\geq 0}c_j\binom{i}{j}=\sum_j c_j[y^j]e^{(1+y)(-\ln(1-x)-x)}
$$

首先翻译上面一句话，考虑其转置的计算，也就是

$$
\sum_j c_j[x^j]e^{(1+y)(-\ln(1-x)-x)}
$$

注意这时 BGF 有很好的性质. 设 $F=e^{(1+y)(-\ln(1-x)-x)}$，则有

$$
\frac{\partial F}{\partial x}=F(1+y)(\frac{1}{1-x}-1)
$$

现在我们可以来翻译下面一句话，令 $F_i(y)=[x^i]F$，那么有递推式

$$
iF_i=(i-1)F_{i-1}+(1+y)F_{i-2}
$$

这样我们可以分治计算. 对于区间 $[l,r]$，我们算出

$$
\sum_{i=l}^rc_iF_i(y)
$$

关于 $F_{l-1}$ 和 $F_{l-2}$ 的表示. 显然这两个系数多项式次数都是 $\Theta(r-l)$ 的. 我们只需要再对每个区间算出 $F_{r},F_{r-1}$ 关于 $F_{l-1},F_{l-2}$ 的表示就可以合并区间.

最后把这个过程转置即可.

放出主要部分代码

```
void solve(int rot,int lt,int rt)
{
	if(lt==rt)
	{
		a[rot][1][0]=Poly(1);a[rot][1][1]=Poly(0);
		if(lt==0){a[rot][0][0]=Poly(1),a[rot][0][1]=Poly(0);}
		else if(lt==1){a[rot][0][0]=a[rot][0][1]=Poly(0);}
		else
		{
			a[rot][0][0]=Poly(Z(lt-1)*inv[lt]);a[rot][0][1]=Poly(inv[lt],inv[lt]);
		}
		return;
	}
	int mid=(lt+rt)>>1;
	solve(rot<<1,lt,mid),solve(rot<<1|1,mid+1,rt);
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				a[rot][i][j]+=a[rot<<1|1][i][k]*a[rot<<1][k][j];
}
void solve2(const Poly u[2],int rot,int lt,int rt)
{
	if(lt==rt)
	{
		if(lt==0)ans[lt]=u[0][0];
		else if(lt==1)ans[lt]=0;
		else ans[lt]=(u[0][0]*Z(lt-1)+u[1][0]+u[1][1])*inv[lt];
		return;
	}
	int mid=(lt+rt)>>1;
	Poly v[2];v[0]=u[0],v[1]=u[1];v[0].resize((mid-lt+1)/2+1),v[1].resize((mid-lt+1)/2+1);
	solve2(v,rot<<1,lt,mid);
	
	v[0]=mulT(u[0],a[rot<<1][0][0])+mulT(u[1],a[rot<<1][0][1]);
	v[1]=mulT(u[0],a[rot<<1][1][0])+mulT(u[1],a[rot<<1][1][1]);
	solve2(v,rot<<1|1,mid+1,rt);
}
```

---

## 作者：Lyrella (赞：2)

# 前言

本文同步发表于[我的博客](https://www.cnblogs.com/Lyrella/p/18880723)。

题意在此不进行简述。

数据范围：$1\le n,k\le10^5$。求一项。

貌似需要用到科技。然后去网上搜做法，看到的基本都是拉格朗日反演。~~然后因为笔者数学太差了没学太懂，于是就只能口胡了。~~ 然后笔者就去学习了拉反并写了一篇[博客](https://www.cnblogs.com/Lyrella/p/18868925)，如果不会建议先去看一下。

好了废话不多说，正片开始。

# 题解

上面（弱化版题解）的思路太麻烦，我们其实可以直接枚举 $\text{cyc}_\pi$，然后每个地方乘上系数即可。所以我们现在需要快速求 $[x^n]e^{y(-\ln(1-x)-x)}$。

现在我们需要处理的函数非常复杂，我们尝试将它拆解，然后用拉格朗日反演得到系数的关系。

因为指数太复杂所以设 ${G^2(x)\over2}=-\ln(1-x)-x$，复合逆为 $H(x)$。然后我们就可以进行拓展拉格朗日反演：
$$
[x^n]e^{G^2(x)y\over2}={1\over n}[x^{n-1}]xye^{x^2y\over2}\left(x\over H(x)\right)^n
$$
我们把 $e^{x^2y\over2}$ 写成多项式的形式得到：
$$
{1\over n}[x^{n-1}y^m]xye^{x^2y\over2}\left(x\over H(x)\right)^n={1\over n2^{m-1}(m-1)!}[x^{n-2m}]\left(x\over H(x)\right)^n
$$
现在我们只用求出 $H(x)$ 就大功告成。那么如何求呢？考虑到 $H(x)$ 是 $G(x)$ 的复合逆，所以有
$$
{x^2\over2}=-\ln(1-H(x))-H(x)
$$
把它整理可得：
$$
2H(x)+2\ln(1-H(x))+x^2=0
$$
这个就牛顿迭代即可，写出式子：
$$
H(x)=H(x)-{2H(x)+2\ln(1-H(x))+x^2\over2-2(1-H(x))^{-1}}
$$
这里还有一个问题，就是分母的常数项为零，所以我们需要在最开始约分约掉一个 $x$。最后时间复杂度 $O(n\log^2n)$。

---

