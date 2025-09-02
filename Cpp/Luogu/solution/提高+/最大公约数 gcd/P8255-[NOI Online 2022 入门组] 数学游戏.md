# [NOI Online 2022 入门组] 数学游戏

## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

民间数据提供者：@一扶苏一。本题不保证民间数据强度，详见[这个帖子](https://www.luogu.com.cn/discuss/422596)。

## 题目描述

Kri 喜欢玩数字游戏。

一天，他在草稿纸上写下了 $t$ 对正整数 $(x,y)$，并对于每一对正整数计算出了 $z=x\times y\times\gcd(x,y)$。

可是调皮的 Zay 找到了 Kri 的草稿纸，并把每一组的 $y$ 都擦除了，还可能改动了一些 $z$。

现在 Kri 想请你帮忙还原每一组的 $y$，具体地，对于每一组中的 $x$ 和 $z$，你需要输出最小的正整数 $y$，使得 $z=x\times y\times\gcd(x,y)$。如果这样的 $y$ 不存在，也就是 Zay 一定改动了 $z$，那么请输出 $-1$。

注：$\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公约数，也就是最大的正整数 $d$，满足 $d$ 既是 $x$ 的约数，又是 $y$ 的约数。

## 说明/提示

**【样例 1 解释】**

$x\times y\times \gcd(x,y)=10\times 12\times\gcd(10,12)=240$。

**【数据范围】**

对于 $20\%$ 的数据，$t, x, z \le {10}^3$。

对于 $40\%$ 的数据，$t \le {10}^3$，$x \le {10}^6$，$z \le {10}^9$。

对于另 $30\%$ 的数据，$t \le {10}^4$。

对于另 $20\%$ 的数据，$x \le {10}^6$。

对于 $100\%$ 的数据，$1 \le t \le 5 \times {10}^5$，$1 \le x \le {10}^9$，$1 \le z < 2^{63}$。

## 样例 #1

### 输入

```
1
10 240```

### 输出

```
12```

## 样例 #2

### 输入

```
3
5 30
4 8
11 11```

### 输出

```
6
-1
1```

## 样例 #3

### 输入

```
见附件中的 math3.in```

### 输出

```
见附件中的 math3.out```

## 样例 #4

### 输入

```
见附件中的 math4.in```

### 输出

```
见附件中的 math4.out```

# 题解

## 作者：enucai (赞：84)

## Preface

考场上没想出来，好一道**人类智慧**题！

## Analysis1

**较简单的证明。**

若 $x\nmid z$，则一定无解。

令 $x=d\times a$，$y=d\times b$，其中 $\gcd(a,b)=1$。那么有 $\gcd(x,y)=d$。则 $z=x\times y\times \gcd(x,y)=d^3\times a\times b$。

我们知道 $x$ 与 $z$，那么可以求出 $\frac{z}{x}=d^2\times b$。由于 $\gcd(a,b)=1$，所以 $\gcd(\frac{z}{x},x^2)=\gcd(d^2\times b,d^2\times a^2)=d^2$。若 $\gcd(\frac{z}{x},x^2)$ 不是完全平方数，则无解。

将 $\gcd(\frac{z}{x},x^2)$ 开方即可得到 $d$。那么：

$$\frac{\frac{z}{x}}{\sqrt{\gcd(\frac{z}{x},x^2)}}=\frac{d^2\times b}{d}=d\times b=y$$

所以我们有：

$$y=\frac{\frac{z}{x}}{\sqrt{\gcd(\frac{z}{x},x^2)}}$$

时间复杂度 $O(T\log x)$。

## Analysis2

**更繁琐的证明。**

由于 $z=x\times y\times \gcd(x,y)$，两边同除 $x$，得：$\frac{z}{x}=y\times \gcd(x,y)$。若 $x\nmid z$，则一定无解。

根据唯一分解定理，我们对已知的 $x$、$\frac{z}{x}$ 与要求的 $y$ 分解质因数：

$$
\begin{cases}
\frac{z}{x}=p_1^{a_1}\times p_2^{a_2}\times p_3^{a_3}\times \dots \times p_k^{a_k}\\
x=p_1^{b_1}\times p_2^{b_2}\times p_3^{b_3}\times \dots \times p_k^{b_k}\\
y=p_1^{c_1}\times p_2^{c_2}\times p_3^{c_3}\times \dots \times p_k^{c_k}
\end{cases}
$$

由于 $\frac{z}{x}=y\times \gcd(x,y)$，所以对于任意 $i\in[1,k]$，有 $a_i=c_i+\min(b_i,c_i)$。

接下来分两种情况讨论：

- 当 $b_i\le c_i$ 时，$a_i=b_i+c_i$，则 $c_i=a_i-b_i$。

  该种情况满足：$b_i\le c_i\iff b_i\le a_i-b_i\iff b_i\le \frac{a_i}{2}$

- 当 $b_i>c_i$ 时，$a_i=2\times c_i$，则 $c_i=\frac{a_i}2$。

  该种情况满足：$b_i>c_i\iff b_i>\frac{a_i}{2}$。

合并一下，得到 $c_i=a_i-\min(\frac{a_i}{2},b_i)$。

两边同时乘以 $2$ 得：$2\times c_i=2\times a_i-\min(a_i,2\times b_i)$。

最后转化为人话，即：

$$y^2=\frac{(\frac{z}{x})^2}{\gcd(\frac{z}{x},x^2)}$$

两边同时开方，得：

$$y=\frac{\frac{z}{x}}{\sqrt{\gcd(\frac{z}{x},x^2)}}$$

如果 $\gcd(\frac{z}{x},x^2)$ 不是完全平方数，也是无解。

时间复杂度：$O(T\log x)$。

## Code

**Talk is cheap, show me the code.**

```cpp
// And in that light, I find deliverance.
#define int long long
void work(){
	int x,z;read(x,z);
	if(z%x!=0){puts("-1");return;}
	int tmp=__gcd(z/x,x*x);
	int sq=(int)sqrt(tmp);
	if(sq*sq!=tmp) puts("-1");
	else cout<<(z/x)/sq<<endl;
}
signed main(){
	int T;read(T);
	while(T--) work();
}
```

---

## 作者：一扶苏一 (赞：25)

## Analysis

首先显然需要把 $x$ 除过去：

$t = \frac z x = y \times \gcd(x, y)$

设 $t = \prod p_i^{c_i}$，$x = \prod p_i^{d_i}$，$y = \prod p_i^{e_i}$ 表示其唯一分解式。则 $\gcd(x, y) = \prod p_i^{\min(d_i, e_i)}$，$y \times \gcd(x, y) = \prod p_i^{e_i + \min(d_i, e_i)}$。

于是对于任意的 $p_i$，我们有：

- 若 $\min(d_i, e_i) = e_i$，则 $e_i + \min(d_i, e_i) = 2e_i = c_i \Rightarrow e_i = \frac{c_i}{2}$。因为 $e_i \leq d_i$，所以 $c_i \leq 2d_i$
- 若 $\min(d_i, e_i) = d_i$，则 $e_i + \min(d_i, e_i) = e_i + d_i = c_i \Rightarrow e_i = c_i - d_i$。因为 $e_i \gt d_i$，所以 $c_i \gt 2d_i$。

同时可以发现，$c_i \leq 2d_i \Rightarrow \frac{c_i}{2} \geq c_i - d_i$（移项一下即可）。这就是说，二者是统一的。于是 $e_i = \max(\frac {c_i} 2, c_i - d_i)$。

考虑把分母和减号消掉，于是 $2e_i + 2d_i = \max(c_i + 2d_i, 2c_i)$。

注意到两数的 lcm 就是他们对应指数的最大值，$\prod p_i^{2e_i + 2d_i} = \prod p_i^{\max(c_i + 2d_i, 2c_i)} \Rightarrow (xy)^2 = \mathrm{lcm}(t \times x^2, t^2)$

于是 $y = \frac{\sqrt{\mathrm{lcm}(t \times x^2, t^2)}}{x} = \frac{1}{x}\sqrt{\frac{t^3 x^2}{ \gcd(t \times x^2, t^2)}} = \frac{t}{\sqrt{\gcd(x^2, t)}}$。

## Code

实现上，注意到 $\gcd(x^2, t)$ 是一个 $2^{63}$ 范围内的数，直接开根号可能因为奇怪的舍入误差出现问题（虽然现在没有找到相应的数据，群友给出的方案是加上 0.5 以后再舍入，因为在这一范围内 sqrt 的误差在 $10^{-15}$ 左右，所以加上 eps 即可。

```cpp
#include <cmath>
#include <numeric>
#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int T;
  for (std::cin >> T; T; --T) {
    long long x, t;
    std::cin >> x >> t;
    if (t % x != 0) {
      std::cout << "-1\n"; continue;
    }
    t /= x;
    long long g = std::gcd(x * x, t), s = sqrt(g) + 0.5;
    if (s * s != g) {
      std::cout << "-1\n"; continue;
    }
    std::cout << t / s << '\n';
  }
}
```



---

## 作者：绝顶我为峰 (赞：19)

无内鬼，来点奇怪复杂度做法。

看到这个题有个自然的思路是对 $x$ 分解质因数，然后大力 dfs 出 $x$ 的所有因数，枚举每个因数作为 $\gcd(x,y)$ 计算是否符合条件，复杂度是 $O(T(\sqrt x+d(x)))$，已经可以得到 90 分的高分。

更进一步，考虑 $\max d(x)$ 在 $10^9$ 的范围内其实只有 $1344$，这一部分是能过的，我们的瓶颈在于每次 $O(\sqrt x)$ 的质因数分解。

借鉴 [AGC003D](https://www.luogu.com.cn/problem/AT2004) 的思路，线性筛预处理出 $\sqrt[3]x$ 范围内的质数，质因数分解的时候先把这些跑一遍，剩下的部分如果不是 $1$，就只有可能是 $p,p^2,pq(p,q\in prime)$ 中的一种。

但和上面提到的题目不同的是，AGC003D 中 $p,pq$ 可以视为同一种情况，但这个题我们毕竟是要找出每一个因数的，$p,pq$ 不能同等对待。

于是我们对剩下的部分（记为 $w$）分类讨论，首先特判掉 $p^2$，然后求 $g=\gcd(w,\frac z x)$。

如果 $g=1$，那么 $w$ 中的所有质因子都不可能成为答案，因为 $y$ 选不出来这些质因子。

如果 $g\neq 1$ 且 $g\neq w$，那么非常走运，我们直接把 $p$ 和 $q$ 分开了，按照普通做法做即可。

如果 $g=w$，再求 $g'=\gcd(w,\frac z{wx})$，如果 $g'=w$ 那么 $w$ 这部分可以刚好分到 $\gcd(x,y)$ 和 $y$ 中各一个，而我们要求最大的 $y$，直接把 $w$ 最后乘上答案即可；否则 $w$ 不能同时在 $\gcd(x,y)$ 和 $y$ 中出现，但无论出现在 $\gcd(x,y)$ 还是 $y$ 中都会导致矛盾，就只能无解了。

至此我们解决了剩余部分的贡献，剩下的质因子直接 dfs 算答案即可，时间复杂度 $O(T(\sqrt[3]x+d(x)))$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
int t,n,p[5001],cnt,tag;
long long m,ans;
bool prime[50001];
vector<pair<long long,int> > v;
inline long long read()
{
    long long x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline void sieve()
{
    prime[1]=1;
    for(int i=2;i<=1000;++i)
    {
        if(!prime[i])
            p[++cnt]=i;
        for(int j=1;j<=cnt&&i*p[j]<=1000;++j)
        {
            prime[i*p[j]]=1;
            if(i%p[j]==0)
                break;
        }
    }
}
inline long long gcd(long long x,long long y)
{
    return x%y? gcd(y,x%y):y;
}
inline void dfs(int k,long long sum)
{
    if(m%sum||(m/sum)%sum)
        return;
    if(k>=v.size())
    {
        if(gcd(n,m/sum)==sum)
            if(ans==-1)
                ans=m/sum;
            else
                ans=min(ans,m/sum);
        return;
    }
    for(int i=0;i<=v[k].second;++i)
    {
        dfs(k+1,sum);
        sum*=v[k].first;
    }
}
int main()
{
    sieve();
    t=read();
    while(t--)
    {
        n=read(),m=read();
        int tmp=n;
        if(m%n)
        {
            cout<<"-1\n";
            continue;
        }
        m/=n;
        tag=1;
        ans=-1;
        v.clear();
        for(int i=1;i<=cnt&&p[i]<=tmp;++i)
            if(tmp%p[i]==0)
            {
                v.emplace_back(p[i],0);
                while(tmp%p[i]==0)
                {
                    ++v.back().second;
                    tmp/=p[i];
                }
            }
        if(tmp^1)
            if((int)(sqrt(tmp))*(int)(sqrt(tmp))==tmp)
                v.emplace_back((int)(sqrt(tmp)),2);
            else
            {
                long long g=gcd(m,tmp);
                if(g==tmp)
                {
                    if(gcd(m,1ll*tmp*tmp)==1ll*tmp*tmp)
                    {
                        tag=tmp;
                        m/=1ll*tmp*tmp;
                    }
                    else
                    {
                        cout<<"-1\n";
                        continue;
                    }
                }
                else if(g^1)
                    v.emplace_back(g,1);
            }
        dfs(0,1);
        if(ans==-1)
            cout<<"-1\n";
        else
            cout<<ans*tag<<'\n';
    }
    return 0;
}
```

---

## 作者：囧仙 (赞：18)

卡精度给我卡吐了。

## 题解

$$z=x\times y\times \gcd(x,y)$$

按照做最大公约数常见套路，我们可以将 $z,x,y$ 进行质因数分解。具体地，我们设有这样尽量大的整数 $a,b,c$，同时有质数 $p$，满足：

$$p^a\mid z,p^b\mid x,p^c\mid y$$

那么将题设带进去，就有：

$$
\begin{aligned}
p^a&=p^b\cdot p^c\cdot p^{\min(b,c)} \cr
a&=b+c+\min(b,c)
\end{aligned}
$$

当 $b\le c$ 时，$a=2b+c$，得 $b\le c=a-2b$，得到 $b\le a/3$。  
当 $b> c$ 时，$a=b+2c$，得 $b>c=\frac{1}{2}(a-b)$，得到 $b>a/3$。

也就是当 $b\le a/3$ 时，$c=a-2b$；当 $b> a/3$ 时，$c=\frac{1}{2}(a-b)$。但是可以发现 $(a-2b)-\frac{1}{2}(a-b)=\frac{1}{2}(a-3b)$，它的分界线**同样**是 $a/3$。那么就可以推断出：

$$c=\max(a-2b,\frac{1}{2}(a-b))$$

看到指数上的 $\max$，因此可以想到**最小公倍数**。因为最小公倍数会满足这样一个性质：

$$\operatorname{lcm}(p^i,p^j)=p^{\max(i,j)}$$

因此，好像可以得到答案：

$$y=\operatorname{lcm}(z\div x^2,\sqrt{z\div x})$$

但是不对啊，最小公倍数应该是定义在整数上的，哪里可以出现有理分数甚至于无理数呢？然后就可以发现可以对 $c$ 的那个等式进行一些小小变形：

$$
\begin{aligned}
2c&=\max(2a-4b,a-b) \cr
2c+4b&=\max(2a,a+3b)
\end{aligned}
$$

这个时候就能得到：

$$
\begin{aligned}
x^4y^2=\operatorname{lcm}(z^2,z\times x^3)=\frac{z^2\times z\times x^3}{\gcd(z^2,z\times x^3)}=\frac{z^2x^3}{\gcd(z,x^3)} \cr
\end{aligned}
$$

然后就能发现：

$$y=\sqrt{\frac{z^2}{x\times \gcd(z,x^3)}}=\frac{z}{\sqrt{x\times \gcd(z,x^3\bmod z)}}$$

一些注意点：

- 因为 $x^3$ 可能爆 $\text{long long}$，所以这里利用了 $\gcd(a,b)=\gcd(a,b\bmod a)$ 的结论，同时使用龟速乘可以使得 $x^3\bmod z$ 在 $\text{long long}$ 范围内。
- 因为下面的数字开根必然要是正整数，才有可能使得存在这样的 $y$，因此根号的 $z^2$ 可以直接提出来。
- 然而无法避免 $x\times \gcd(z,x^3\bmod z)$ 照样是可以爆 $\text{long long}$ 的……因此这里直接使用 $\text{long double}$，以及 $\text{cmath}$ 库当中的 $\text{sqrtl}$ 函数，来避免这样的精度误差。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
typedef unsigned int       u32;
typedef unsigned long long u64;
u64 gcd(u64 x,u64 y){return x==0?y:gcd(y%x,x);}
u64 mul(u64 x,u64 y,u64 m){
    u64 r=0; while(y){
        if(y&1) r=(r+x)%m; y>>=1,x=(x+x)%m;
    }
    return r;
}
int main(){
    int T; scanf("%d",&T); up(1,T,TT){
        u64 x,y,z,t,u; scanf("%llu%llu",&x,&z);
        u=mul(mul(x,x,z),x,z),t=sqrtl((long double)x*gcd(z,u)+0.5),y=z/t;
        if(z!=x*y*gcd(x,y)) puts("-1");
        else printf("%llu\n",y);
    }
    return 0;
}
```


---

