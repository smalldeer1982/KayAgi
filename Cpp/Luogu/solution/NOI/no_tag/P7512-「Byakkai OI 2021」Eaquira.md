# 「Byakkai OI 2021」Eaquira

## 题目描述

给定 $n$，并在数轴上截取 $[1,n]$ 的整点。

定义**极长连续黑区间段**为满足 $1 \le L \le R \le p$ 的区间段 $[L,R]$，且编号在 $[L,R]$ 内的区间都是黑色，且其不能再扩展，即编号为 $L-1$（如果存在，下同）和 $R+1$ 的区间都是白色。

首先，请您将它们划分成若干个区间 $[l_1,r_1],[l_2,r_2],\dots,[l_p,r_p]$，满足 $l_1=1,r_p = n$，且对于 $1 \le i < p$ 有 $r_i = l_{i+1}-1$；对于 $1 \le i \le p$ 满足 $l_i \le r_i$。  

其二，您需要将每个区间标记为黑色或是白色，但不允许第 $1$ 个区间和第 $p$ 个区间同时被标记为黑色。

其三，请您在每个区间内选出一个子区间，称为**绝妙子区间**。

其四，请您在每个极长连续黑区间段中各选出一个黑色区间，称为**绝妙黑区间**。

其五，在所有的极长连续黑区间段中钦定若干个称作**绝妙极长连续黑区间段**。

定义一种以上述步骤所确定的方案的权值为黑色区间的个数与绝妙极长连续黑区间段个数的和。

我本来希望您求出对于 $s = 0,1,2,\dots,n$ 得到可以使得最终权值为 $s$ 的方案数。不过我也准备了一些更低要求的挑战。详见输入格式。

答案对 $998244353$ 取模。

## 说明/提示

**样例解释**

以下用 $0$ 表示黑，$1$ 表示白。

对于第一个样例，考虑 $[1,3]$ 的 $4$ 种划分：
- $[1,1],[2,2],[3,3]$：  
  此时选出无序数对的方案数为 $1$。  
  考虑每个区间的黑白标记情况，有如下 $4$ 种方案： 
    - $001,100$：此时可以选择将唯一的极长连续黑区间段标记为绝妙与否，则权值为 $2$ 或 $3$，选择绝妙黑区间的方案数为 $2$。
    - $101$：此时可以选择将唯一的极长连续黑区间段标记为绝妙与否，则权值为 $1$ 或 $2$，选择绝妙黑区间的方案数为 $1$。
- $[1,2],[3,3]$ 或 $[1,1],[2,3]$：  
  此时选出无序数对的方案数为 $3$。  
  考虑每个区间的黑白标记情况，有如下 $2$ 种方案：
    - $01,10$：此时可以选择将唯一的极长连续黑区间段标记为绝妙与否，则权值为 $1$ 或 $2$，选择绝妙黑区间的方案数为 $1$。
- $[1,3]$：  
  此时选出无序数对的方案数为 $6$。  
  考虑每个区间的黑白标记情况，有如下 $1$ 种方案：
    - $1$：此时权值为 $0$，总方案数为 $6$，选择绝妙黑区间的方案数为 $1$。
故权值为 $0$ 的方案数为 $6 \times 1 = 6$，权值为 $1$ 的方案数为 $1 \times 1 + 2 \times 3 \times 2 \times 1 = 13$，权值为 $2$ 的方案数为 $1 \times 2 \times 2 + 1 \times 1 + 2 \times 3 \times 2 \times 1 = 17$，权值为 $3$ 的方案数为 $1 \times 2 \times 2 = 4$。

对于第二个样例，不予解释。

**数据范围**

**本题使用捆绑测试。**

具体子任务限制及分值如下表：

|子任务编号|分值|$n \le $|${\rm type} =$|时限 / s|
|:-:|:-:|:-:|:-:|:-:|
|$0$|$1$|$8$|$0$|$1$|
|$1$|$4$|$13$|$1$|$1$|
|$2$|$8$|$300$|$1$|$1$|
|$3$|$5$|$70$|$0$|$1$|
|$4$|$10$|$5 \times 10^3$|$1$|$1$|
|$5$|$8$|$300$|$0$|$1$|
|$6$|$12$|$2 \times 10^5$|$1$|$1$|
|$7$|$22$|$10^3$|$0$|$2$|
|$8$|$30$|$2 \times 10^5$|$0$|$2.5$|

对于所有数据，$1 \le n \le 2 \times 10^5$，${\rm type} \in \{0,1\}$。

## 样例 #1

### 输入

```
3 0```

### 输出

```
6 13 17 4```

## 样例 #2

### 输入

```
5 1```

### 输出

```
1035```

# 题解

## 作者：Aleph1022 (赞：8)

本文是 「Byakkai OI 2021」Eaquira 一题的官方题解。  
本文同步发表于我的博客 <https://www.alpha1022.me/articles/byakkai-oi-2021-eaquira.htm>。  
关于 Byakkai OI 的更多情报可以在[这里](https://www.luogu.com.cn/blog/your-alpha1022/byakkai-oi)找到。

---

不难看出一个多项式复合的模型：先计算区间之间的黑白关系，再以每个区间为单位复合。

考虑内层一个区间的 GF：
$$
F(x) = \sum\limits_{i\ge 1} \binom{i+1}2 x^i = \frac x{(1-x)^3}
$$

对于外层，容易知道所有方案都形如「白黑黑……黑白黑黑……黑白黑黑……黑（白）」（除了首黑尾白，但是根据对称性容易得到这种方案数）。因此可以考虑以形如「白黑黑……黑」的基础单位构造序列来刻画。  
令一个极长连续黑区间段的 GF 为（用 $w$ 元记录权值）
$$
G(x) = \sum\limits_{i\ge 1} i x^i w^i (1+w) = \frac{xw(1+w)}{(1-xw)^2}
$$

则答案应当形如
$$
\frac{2+F}{1-F(G \circ F)}
$$

由于我们需要求得的仅是 $x^n$ 项系数，因此可以考虑拉格朗日反演。  
注意到 $F$ 具有简单的封闭形式，从而容易牛顿迭代求出 $F$ 的复合逆。  
然后令
$$
W = \frac{2+x}{1-xG}
$$

则答案为
$$
[x^n]\frac{2+F}{1-FG} = \frac1n [x^{n-1}]W'(x)\left(\frac x{F^{-1}(x)}\right)^n
$$

注意 $-1$ 是函数幂。

然后考虑 $W'$：
$$
\begin{aligned}
W'
&= \left(\frac{2+x}{1-\frac{x^2w+x^2w^2}{(1-xw)^2}}\right)' \\
&= \left(\frac{2-4xw+2x^2w^2+x-2x^2w+x^3w^2}{1-2xw-x^2w}\right)' \\
&= \frac{1+4xw^2+x^2w+3x^2w^2-4x^2w^3-4x^3w^3-x^4w^3}{(1-2xw-x^2w)^2}
\end{aligned}
$$

我们需要提取上式的 $w^s$ 项系数。  
设 $p(s) = x^s(x+2)^s$。  
则有
$$
\begin{aligned}
[w^s]W'
&= [w^s] (1+4xw^2+x^2w+3x^2w^2-4x^2w^3-4x^3w^3-x^4w^3)\sum\limits_{i\ge 0}(i+1)x^i(x+2)^iw^i \\
&= (s+1)p(s)+4(s-1)xp(s-2)+sx^2p(s-1)+3(s-1)x^2p(s-2) \\
&- 4(s-2)x^2p(s-3)-4(s-2)x^3p(s-3)-(s-2)x^4p(s-3)
\end{aligned}
$$

令 $V = \left(\frac x{F^{-1}}\right)^n$，则问题变为计算 $5$ 个
$$
[x^r] \frac{V(x)}{1-tx(x+2)}
$$

令 $P(x)=x(x+2)$，$Q(x)=V(P^{-1}(x))$，$U(x) = \frac{Q(x)}{1-tx}$，则根据扩展拉格朗日反演有
$$
[x^r] \frac{V(x)}{1-tx(1+x)} = \frac1r[x^{r-1}]U'(x)\left(\frac x{P^{-1}(x)}\right)^r
$$

$P(x)$ 的复合逆非常好求，就是
$$
\sqrt{1+x}-1
$$

可以随手广义二项式定理展开一下，不嫌麻烦的也可以写个多项式开方。  
（但是如果你不会展开的话底下就做不了了）

继续考虑
$$
\begin{aligned}
U'
&= \left(\frac{Q(x)}{1-tx}\right)' \\
&= \frac{Q'(x)(1-tx)+Q(x)(1-tx)'}{(1-tx)^2} \\
&= \frac{Q'(x)+t(Q(x)-xQ'(x))}{(1-tx)^2}
\end{aligned}
$$

再令 $R(x) = \left(\frac x{P^{-1}(x)}\right)^r$。  
则
$$
\begin{aligned}
[x^{r-1}t^c]U'(x)R(x)
&= [x^{r-1}t^c]\left(\frac{Q'(x)+t(Q(x)-xQ'(x))}{(1-tx)^2}\right) R(x) \\
&= [x^{r-1}t^c]\left(Q'(x)\sum\limits_{i\ge 0} (i+1)t^ix^i + (Q(x)-xQ'(x))\sum\limits_{i\ge 0}(i+1)t^{i+1}x^i\right) R(x) \\
&= (c+1) [x^{r-c-1}] Q'(x)R(x) + c [x^{r-c}] (Q(x)-xQ'(x))R(x)
\end{aligned}
$$

问题又变为求 $Q(x)$。  
考虑求 $V(\sqrt{1+x}-1)$。  
可以首先求 $V'(x) = V(x-1)$（记住这个 $'$ 不是求导），然后计算 $V'(\sqrt{1+x})$。  
这部分可以参考 CF923E。

考虑对系数的奇偶性进行讨论。  
对于偶数部分的系数，单独提取出来并复合 $\sqrt x$（这个时候就相当于把次数除以二）就变成了复合 $1+x$，也比较简单。  
对于奇数部分的系数，首先考虑一下 $(1+x)^{i+1/2}$：
$$
\begin{aligned}
(1+x)^{i+1/2}
&= \sum\limits_{j\ge 0} \binom{i+\frac12}j x^j \\
&= \sum\limits_{j\ge 0} x^j \frac{(2i+1)\cdot(2i-1)\cdots(2i-2j+3)}{j!2^j} \\
&= \sum\limits_{j\ge0} x^j \frac{(2i+1)!!}{j! 2^j (2i-2j+1)!!}
\end{aligned}
$$

然后代入系数
$$
\begin{aligned}
\sum\limits_{i\ge 0} v'_{2i+1} (1+x)^{i+1/2}
&= \sum\limits_{i\ge 0} v'_{2i+1} \sum\limits_{j\ge 0} x^j \frac{(2i+1)!!}{j! 2^j (2i-2j+1)!!} \\
&= \sum\limits_{j\ge 0} \frac{x^j}{j! 2^j} \sum\limits_{i\ge 0} \frac{v'_{2i+1}(2i+1)!!}{(2i-2j+1)!!}
\end{aligned}
$$

可以卷积解决。

复杂度 $O(n \log n)$。  
std 最慢点大概是 1.25s。

---

另外，这份题解是我一段时间前写的。实际上应用另类拉格朗日反演的幂级数形式可以减少一点点细节的讨论（并没有减小多少）。

代码：
```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>
#define add(a,b) (a + b >= mod ? a + b - mod : a + b)
#define dec(a,b) (a < b ? a - b + mod : a - b)
using namespace std;
const int N = 2e5;
const int mod = 998244353;
int n,m,type;
int wfac_[4 * N + 5],*wfac = wfac_ + 2 * N;
int iwfac_[4 * N + 5],*iwfac = iwfac_ + 2 * N;
int ans[N + 5];
inline int fpow(int a,int b)
{
    int ret = 1;
    for(;b;b >>= 1)
        (b & 1) && (ret = (long long)ret * a % mod),a = (long long)a * a % mod;
    return ret;
}
namespace Poly
{
    const int LG = 19;
    const int N = 1 << LG + 1;
    const int G = 31;
    int lg2[N + 5];
    int rev[N + 5],fac[N + 5],ifac[N + 5],inv[N + 5];
    int rt[N + 5];
    inline void init()
    {
        for(register int i = 2;i <= N;++i)
            lg2[i] = lg2[i >> 1] + 1;
        rt[0] = 1,rt[1 << LG] = fpow(31,1 << 21 - LG);
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
poly f,v,v1,p,q,r;
inline poly solve(int m)
{
    poly ret,t,t2,t3;
    for(register int k = 1;k < m;)
    {
        k <<= 1,t.resize(k << 1),t2.resize(k << 1),t3.resize(k << 1);
        for(register int i = 0;i < (k << 1);++i)
            t.a[i] = dec(0,ret[i]);
        t.a[0] = add(t[0],1);
        t.ntt();
        for(register int i = 0;i < (k << 1);++i)
            t2.a[i] = (long long)t[i] * t[i] % mod;
        t2.ntt(-1);
        for(register int i = k;i < (k << 1);++i)
            t2.a[i] = 0;
        t3 = t2,t3.ntt();
        for(register int i = 0;i < (k << 1);++i)
            t3.a[i] = (long long)t3[i] * t[i] % mod;
        t3.ntt(-1),t2.resize(k),t3.resize(k);
        for(register int i = k - 1;i;--i)
            t2.a[i] = t2[i - 1],t3.a[i] = t3[i - 1];
        t2.a[0] = t3.a[0] = 0;
        for(register int i = 0;i < k;++i)
            t2.a[i] = 3LL * t2[i] % mod,
            t3.a[i] = dec(t3[i],ret[i]);
        t2.a[0] = add(t2[0],1);
        t2 = t2.inver(k >> 1),t2.resize(k);
        for(register int i = 0;i < (k >> 1);++i)
            t3.a[i] = t3[i + (k >> 1)];
        for(register int i = (k >> 1);i < k;++i)
            t2.a[i] = t3.a[i] = 0;
        t2.ntt(),t3.ntt();
        for(register int i = 0;i < k;++i)
            t3.a[i] = (long long)t3[i] * t2[i] % mod;
        t3.ntt(-1);
        ret.resize(k);
        for(register int i = (k >> 1);i < k;++i)
            ret.a[i] = t3[i - (k >> 1)];
    }
    return ret.modxn(m);
}
poly t1,t2;
int cur[N + 5];
inline void calc(int n)
{
    memset(cur,0,sizeof cur);
    if(n == 0)
        cur[0] = v[0];
    if(n <= 0)
        return ;
    poly q1 = q.deriv().modxn(n),q2 = q.modxn(n);
    for(register int i = 0;i < n;++i)
        q2.a[i] = dec(q2[i],q1[i - 1]);
    q1 *= r.modxn(n),q2 *= r.modxn(n);
    for(register int i = 0;i <= n;++i)
        cur[i] = ((long long)(i + 1) * q1[n - i - 1] + (long long)i * q2[n - i]) % mod * Poly::inv[n] % mod;
}
int sum;
int main()
{
    init();
    scanf("%d%d",&n,&type);
    if(type == 1)
    {
        f.resize(n + 1);
        for(register int i = 1;i <= n;++i)
            f.a[i] = C(i + 1,2);
        t2 = 1 - f,t2 = (t2 * t2).modxn(n + 1);
        t2 = (f * t2.inver(n + 1)).modxn(n + 1),t2 *= 2;
        f = ((2 + f) * (1 - f * t2).inver(n + 1)).modxn(n + 1);
        printf("%d\n",f[n]);
        return 0;
    }
    f = solve(n + 1),f.resize(n + 1);
    for(register int i = 0;i < n;++i)
        f.a[i] = f[i + 1];
    f.resize(n),v = f.pow(n,mod - n,mod - n - 1);
    p.resize(n + 1);
    for(register int i = 1,pw = mod - Poly::inv[4];i <= n;++i,pw = (long long)pw * (mod - Poly::inv[4]) % mod)
        p.a[i] = (long long)(mod - 2) * pw % mod * Poly::inv[i] % mod * C(2 * i - 2,i - 1) % mod;
    for(register int i = 0;i < n;++i)
        p.a[i] = p[i + 1];
    p.resize(n);
    t1.resize(n),t2.resize(n);
    for(register int i = 0;i < n;++i)
        t1.a[n - 1 - i] = (long long)Poly::fac[i] * v[i] % mod,
        t2.a[i] = (long long)(i & 1 ? mod - 1 : 1) * Poly::ifac[i] % mod;
    t1 *= t2;
    v1.resize(n);
    for(register int i = 0;i < n;++i)
        v1.a[i] = (long long)t1[n - 1 - i] * Poly::ifac[i] % mod;
    q.resize(n);
    t1.resize(n),t2.resize(n);
    for(register int i = 0;i < n;++i)
        t1.a[n - 1 - i] = (long long)Poly::fac[i] * v1[i << 1] % mod,
        t2.a[i] = Poly::ifac[i];
    t1 *= t2;
    for(register int i = 0;i < n;++i)
        q.a[i] = (long long)t1[n - 1 - i] * Poly::ifac[i] % mod;
    m = n + 1 >> 1;
    t1.resize(m),t2.resize(n + m - 1);
    wfac[1] = iwfac[1] = wfac[-1] = iwfac[-1] = 1;
    for(register int i = 3;i <= 2 * n;i += 2)
        wfac[i] = (long long)wfac[i - 2] * i % mod,
        iwfac[i] = (long long)iwfac[i - 2] * Poly::inv[i] % mod;
    for(register int i = -1;i - 2 >= -2 * n;i -= 2)
        wfac[i - 2] = (long long)wfac[i] * (mod - 1) % mod * Poly::inv[-i] % mod,
        iwfac[i - 2] = (long long)iwfac[i] * (i + mod) % mod;
    for(register int i = 0;i < m;++i)
        t1.a[i] = (long long)v1[(i << 1) | 1] * wfac[(i << 1) | 1] % mod;
    for(register int i = 0;i < n + m - 1;++i)
        t2.a[i] = iwfac[2 * ((n + m - 2 - i) - n + 1) + 1];
    t1 *= t2;
    for(register int i = 0,pw = 1;i < n;++i,pw = (long long)pw * Poly::inv[2] % mod)
        q.a[i] = (q[i] + (long long)t1[m + i - 1] * Poly::ifac[i] % mod * pw) % mod;
    r = p.pow(n,(mod - n + 1) % mod,mod - n),calc(n - 1);
    for(register int i = 0;i <= n;++i)
        ans[i] = (long long)(i + 1) * cur[i] % mod;
    r = (r * p).modxn(n),calc(n - 2);
    for(register int i = 2;i <= n;++i)
        ans[i] = (ans[i] + 4LL * (i - 1) % mod * cur[i - 2]) % mod;
    r = (r * p).modxn(n),calc(n - 3);
    for(register int i = 1;i <= n;++i)
        ans[i] = (ans[i] + (long long)i * cur[i - 1]) % mod;
    for(register int i = 2;i <= n;++i)
        ans[i] = (ans[i] + 3LL * (i - 1) % mod * cur[i - 2]) % mod;
    for(register int i = 3;i <= n;++i)
        ans[i] = (ans[i] - 4LL * (i - 2) % mod * cur[i - 3] % mod + mod) % mod;
    r = (r * p).modxn(n),calc(n - 4);
    for(register int i = 3;i <= n;++i)
        ans[i] = (ans[i] - 4LL * (i - 2) % mod * cur[i - 3] % mod + mod) % mod;
    r = (r * p).modxn(n),calc(n - 5);
    for(register int i = 3;i <= n;++i)
        ans[i] = (ans[i] - (long long)(i - 2) * cur[i - 3] % mod + mod) % mod;
    for(register int i = 0;i <= n;++i)
        ans[i] = (long long)ans[i] * Poly::inv[n] % mod;
    if(!type)
        for(register int i = 0;i <= n;++i)
            printf("%d%c",ans[i]," \n"[i == n]);
    else
    {
        for(register int i = 0;i <= n;++i)
            sum = add(sum,ans[i]);
        printf("%d\n",sum);
    }
}
```

---

## 作者：jijidawang (赞：4)

快进到生成函数：
$$[x^n]\dfrac{2+F(x)}{1-G(F(x),w)}\text{ where }F(x)=\dfrac x{(1-x)^3},\,G(x,w)=\dfrac{xw(1+w)}{(1-xw)^2}$$
可以发现相当于要计算有理分式的点值，调用 Bostan-Mori 算法即可。由于分子分母关于 $x$ 的次数始终为 $O(1)$，而 $w$ 的次数每次倍增。故时间复杂度为 $O(n\log n)$。

实现细节：对于 $x$ 这一元可以平方计算多项式乘法，对于 $w$ 再使用 NTT 优化。如果被卡常了可以考虑递归到足够小的 $n$ 时暴力求逆算点值。

---

