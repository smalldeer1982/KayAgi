# [国家集训队] Crash的数字表格 / JZPTAB

## 题目描述

今天的数学课上，Crash 小朋友学习了最小公倍数（Least Common Multiple）。对于两个正整数 $a$ 和 $b$，$\text{lcm}(a,b)$ 表示能同时被 $a$ 和 $b$ 整除的最小正整数。例如，$\text{lcm}(6, 8) = 24$。

回到家后，Crash 还在想着课上学的东西，为了研究最小公倍数，他画了一张 $ n \times m$ 的表格。每个格子里写了一个数字，其中第 $i$ 行第 $j$ 列的那个格子里写着数为 $\text{lcm}(i, j)$。

看着这个表格，Crash 想到了很多可以思考的问题。不过他最想解决的问题却是一个十分简单的问题：这个表格中所有数的和是多少。当 $n$ 和 $m$ 很大时，Crash 就束手无策了，因此他找到了聪明的你用程序帮他解决这个问题。由于最终结果可能会很大，Crash 只想知道表格里所有数的和对 $20101009$ 取模后的值。



## 说明/提示

#### 样例输入输出 1 解释

该表格为：

|$1$|$2$|$3$|$4$|$5$|
|:-:|:-:|:-:|:-:|:-:|
|$2$|$2$|$6$|$4$|$10$|
|$3$|$6$|$3$|$12$|$15$|
|$4$|$4$|$12$|$4$|$20$|

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n, m \le 10^3$。
- 对于 $70\%$ 的数据，保证 $n, m \le 10^5$。
- 对于 $100\%$ 的数据，保证 $1\le n,m \le 10^7$。

## 样例 #1

### 输入

```
4 5```

### 输出

```
122```

# 题解

## 作者：Siyuan (赞：119)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：https://www.luogu.org/problemnew/show/P1829

求解（对 $20101009$ 取模）

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^m\operatorname{lcm}(i,j)$$

数据范围：$n,m\leqslant 10^7$

---

## Solution

易知原式等价于

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^m\frac{i\cdot j}{\gcd(i,j)}$$

枚举最大公因数 $d$，显然两个数除以 $d$ 得到的数互质

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^m\sum\limits_{d|i,d|j,\gcd(\frac{i}{d},\frac{j}{d})=1}\frac{i\cdot j}{d}$$

非常经典的 $\gcd$ 式子的化法

$$\sum\limits_{d=1}^n d\cdot\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}[\gcd(i,j)=1]\cdot i\cdot j$$

后半段式子中，出现了互质数对之积的和，为了让式子更简洁就把它拿出来单独计算。于是我们记

$$\operatorname{sum}(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m [\gcd(i,j)=1]\cdot i\cdot j$$

接下来对 $\operatorname{sum}(n,m)$ 进行化简。首先枚举约数，并将 $[\gcd(i,j)=1]$ 表示为 $\varepsilon(\gcd(i,j))$

$$\sum\limits_{d=1}^n\sum\limits_{d|i}^n\sum\limits_{d|j}^m\mu(d)\cdot i\cdot j$$

设 $i=i'\cdot d$，$j=j'\cdot d$（其中 $i',j'$ 指上式中的 $i,j$ ），显然式子可以变为

$$\sum\limits_{d=1}^n\mu(d)\cdot d^2\cdot\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}i\cdot j$$

观察上式，前半段可以预处理前缀和；后半段又是一个范围内数对之和，记

$$g(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m i\cdot j=\frac{n\cdot(n+1)}{2}\times\frac{m\cdot(m+1)}{2}$$

可以 $\Theta(1)$ 求解

至此

$$\operatorname{sum}(n,m)=\sum\limits_{d=1}^n\mu(d)\cdot d^2\cdot g(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)$$

我们可以 $\lfloor\frac{n}{\lfloor\frac{n}{d}\rfloor}\rfloor$ 数论分块求解 $\operatorname{sum}(n,m)$ 函数。

在求出 $\operatorname{sum}(n,m)$ 后，回到定义 $\operatorname{sum}$ 的地方，可得原式为

$$\sum\limits_{d=1}^n d\cdot\operatorname{sum}(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)$$

可见这又是一个可以数论分块求解的式子！

本题除了推式子比较复杂、代码细节较多之外，是一道很好的莫比乌斯反演练习题！（上述过程中，默认 $n\leqslant m$）

**时间复杂度**：$\Theta(n+m)$（两次数论分块）

---

## Code

```cpp
#include <cstdio>
#include <algorithm>
using std::min;

const int N=1e7;
const int mod=20101009;
int n,m,mu[N+5],p[N/10+5],sum[N+5];
bool flg[N+5];

void init() {
    mu[1]=1;
    int tot=0,k=min(n,m);
    for(int i=2;i<=k;++i) {
        if(!flg[i]) p[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*p[j]<=k;++j) {
            flg[i*p[j]]=1;
            if(i%p[j]==0) {mu[i*p[j]]=0;break;}
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=k;++i) sum[i]=(sum[i-1]+1LL*i*i%mod*(mu[i]+mod))%mod;
}
int Sum(int x,int y) {
    return (1LL*x*(x+1)/2%mod)*(1LL*y*(y+1)/2%mod)%mod;
}
int func(int x,int y) {
    int res=0;
    for(int i=1,j;i<=min(x,y);i=j+1) {
        j=min(x/(x/i),y/(y/i));
        res=(res+1LL*(sum[j]-sum[i-1]+mod)*Sum(x/i,y/i)%mod)%mod;
    }
    return res;
}
int solve(int x,int y) {
    int res=0;
    for(int i=1,j;i<=min(x,y);i=j+1) {
        j=min(x/(x/i),y/(y/i));
        res=(res+1LL*(j-i+1)*(i+j)/2%mod*func(x/i,y/i)%mod)%mod;
    }
    return res;
}
int main() {
    scanf("%d%d",&n,&m);
    init();
    printf("%d\n",solve(n,m));
}
```

---

## 作者：pengym (赞：47)

我顺便来安利一下自己的博客[peng-ym's blog](http://www.cnblogs.com/peng-ym/)里面也有[莫比乌斯反演](http://www.cnblogs.com/peng-ym/p/8647856.html)与[整除分块](http://www.cnblogs.com/peng-ym/p/8661118.html)的介绍，不知道的可以看一看哦！
## 解题思路
- 很显然，题目所求的就是$Ans=\sum_{i=1}^{n}\sum_{j=1}^{m}lcm(i,j)$
- 我们根据$lcm(i,j)=\frac{ij}{gcd(i,j)}$这个性质把它转换成$gcd$
$$Ans=\sum_{i=1}^{n}\sum_{j=1}^{m}\frac{ij}{gcd(i,j)}$$
- 我们套路的枚举$gcd$为$d$并且顺便把它提到最前面
$$Ans=\sum_{d=1}^{min(n,m)}\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=d]\frac{ij}{d}$$
- 将$d$给提出来，当然也可以看做是换枚举项$i,j$为$di,dj$
$$Ans=\sum_{d=1}^{min(n,m)}d\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}[gcd(i,j)=1]ij$$
- 利用$\sum_{d|n}\mu(d)=[n=1]$的性质，代入
$$Ans=\sum_{d=1}^{min(n,m)}d\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}\sum_{x|gcd(i,j)}\mu(x)ij$$
- 这个枚举$gcd(i,j)$约数的式子很不爽，所以我们枚举$x$，这样$x$与$i,j$无关就可以提到前面
$$Ans=\sum_{d=1}^{min(n,m)}d\sum_{x=1}^{min(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)}\mu(x)\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}ij[x|gcd(i,j)]$$
- 我们可以将这个式子由枚举$i,j$变为枚举$xu,xv$(不用$i,j$这样子看起来没那么别扭)。因为这样我们就可以不用处理$[x|gcd(i,j)]$这个条件，因为它一定满足。
$$Ans=\sum_{d=1}^{min(n,m)}d\sum_{x=1}^{min(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)}\mu(x)\sum_{xu=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{xv=1}^{\lfloor\frac{m}{d}\rfloor}x^2uv$$
- 最后我们将$x^2$给提出来，就差不多化完了
$$Ans=\sum_{d=1}^{min(n,m)}d\sum_{x=1}^{min(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)}x^2\mu(x)(\sum_{u=1}^{\lfloor\frac{n}{dx}\rfloor}u)(\sum_{v=1}^{\lfloor\frac{m}{dx}\rfloor}v)$$
- 这个式子可以$O(n)$线性筛出$x^2\mu(x)$，最后两个式子就是等差数列求和，可以用**[整除分块](http://www.cnblogs.com/peng-ym/p/8661118.html)**优化。这道题就可以$A$了。

## Code:

```cpp
#include<bits/stdc++.h>
#define N 10010000
using namespace std;
inline void read(int &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}
const long long mod=20101009;
int n,m;
bool vis[N];
int cnt,prim[N],mu[N];
long long sum[N];
void get_mu(int maxn)
{
    mu[1]=1;
    for(int i=2;i<=maxn;i++)
    {
        if(!vis[i]){prim[++cnt]=i;mu[i]=-1;}
        for(int j=1;j<=cnt&&prim[j]*i<=maxn;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
    for(int i=1;i<=maxn;i++)(sum[i]=sum[i-1]+1ll*mu[i]*1ll*i%mod*1ll*i%mod)%=mod;
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n);read(m);
    int max_rep=0;
    get_mu(max_rep=min(n,m));
    long long ans=0;
    long long inv2=(mod+1ll)/2ll;
    long long summ=0;
    for(int d=1;d<=max_rep;d++)
    {
        int maxx=n/d,maxy=m/d,minn=min(maxx,maxy);
        summ=0ll;
        for(int l=1,r;l<=minn;l=r+1ll)
        {
            r=min(maxx/(maxx/l),maxy/(maxy/l));
            (summ+=(sum[r]-sum[l-1])%mod*(((1ll+maxx/l)%mod*1ll*(maxx/l)%mod*inv2%mod)%mod)%mod*(((1ll+maxy/l)%mod*1ll*(maxy/l)%mod*inv2%mod)%mod)%mod)%=mod;
        }
        (ans+=summ*1ll*d)%=mod;
    }
    cout<<(ans%mod+mod)%mod<<endl;
    return 0;
}
```

---

## 作者：litble (赞：44)

# 题目分析

[个人blog](http://blog.csdn.net/litble/article/details/79518721)

首先是一些莫比乌斯反演的基本套路：

设$n<m$，首先看要求的式子：

$$\sum_{i=1}^n\sum_{j=1}^m\frac{ij}{gcd(i,j)}$$

**套路1**:优先枚举gcd

$$\sum_{d=1}^nd\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)==d]$$

**套路2**:$gcd(i,j)=d $等价于 $gcd(i/d,j/d)=1$

$$\sum_{d=1}^nd\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor }\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor }[gcd(i,j)==1]$$

**套路3**:莫比乌斯函数的性质

若n不为1，则$\sum_{d|n}=1$，否则原式为0.
$$\sum_{d=1}^nd\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor }\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor }\sum_{t|gcd(i,j)}\mu(t)$$

**套路4**:优先枚举$t$(同时设$sum(n)=\sum_{i=1}^ni=\frac{n(n+1)}{2}$)

$$\sum_{d=1}^nd\sum_{t=1}^{\lfloor \frac{n}{d} \rfloor}t^2\mu(t)sum(\lfloor \frac{n}{dt} \rfloor)sum(\lfloor \frac{m}{dt} \rfloor) $$

**套路5**:设$dt=T$，优先枚举$sum(\lfloor \frac{n}{T} \rfloor)sum(\lfloor \frac{m}{T} \rfloor) $(因为这一块可以数论分块根号时间内求，具体方法语言讲不清，看代码吧）

$$\sum_{T=1}^nsum(\lfloor \frac{n}{T} \rfloor)sum(\lfloor \frac{m}{T} \rfloor)T\sum_{d|T}d\mu(T)$$

套路结束。

现在我们要考虑迅速搞出$T\sum_{d|T}d\mu(T)$,那么我们设$f(T)=\sum_{d|T}d\mu(d)$

这是一个积性函数，可以线性筛。考虑莫比乌斯反演的线性筛，我们为一个数$T$加入一个新的质因子$p$，如果$T$有这个质因子的话，那么对于$T$原来的约数$d$，这个数如果有质因子$p$，加上这个$p$之后，并不会产生新的质因子。否则，$\mu(pd)=0$，所以此时$f(Tp)=f(T)$。如果$T$没有这个因子，那么其每一个约数乘上这个因子后，由于$\mu(pd)=-\mu(d)$，所以$f(Tp)=f(T)-pf(T)=(1-p)f(T)=f(p)f(T)$

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=20101009,N=10000005;
int f[N],pri[N],is[N],s[N];
int n,m,tot,ans,div2;
int qm(int x) {return x>=mod?x-mod:x;}
void init() {
    f[1]=1;
    for(int i=2;i<=n;++i) {//线性筛
        if(!is[i]) pri[++tot]=i,f[i]=qm(mod+1-i);
        for(int j=1;j<=tot&&i*pri[j]<=n;++j) {
            int k=i*pri[j]; is[k]=1;
            if(i%pri[j]) f[k]=1LL*f[i]*f[pri[j]]%mod;
            else {f[k]=f[i];break;}
        }
    }
    for(int i=1;i<=n;++i) f[i]=qm(f[i-1]+1LL*f[i]*i%mod);
    for(int i=1;i<=m;++i) s[i]=qm(s[i-1]+i);
}
int main()
{
   	scanf("%d%d",&n,&m);
   	if(n>m) swap(n,m);
   	init();
   	for(int i=1,j;i<=n;i=j+1) {//数论分块根号求解
   		j=min(n/(n/i),m/(m/i));
   		ans=qm(ans+1LL*qm(f[j]-f[i-1]+mod)*s[n/i]%mod*s[m/i]%mod);
   	}
   	printf("%d\n",ans);
    return 0;
}
```


---

## 作者：Js2xxx (赞：29)

# 分析
首先，设$n\leq m$，要求的式子是：
$$\sum_{i=1}^{n}\sum_{j=1}^{m}lcm(i, j)$$
即
$$\sum_{i=1}^{n}\sum_{j=1}^{m}\frac{i*j}{gcd(i, j)}$$
提个$gcd$出来：
$$\sum_{d=1}^{n}\sum_{i=1}^{n}\sum_{j=1}^{m}\frac{i*j}{d}[gcd(i,j)=d]$$
约掉$d$：
$$\sum_{d=1}^{n}d\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}i*j[gcd(i,j)=1]$$
由
$$\sum_{n|d}\mu(n)=[d==1]$$
得原式：
$$\sum_{d=1}^{n}d\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}i*j\sum_{a|gcd(i,j)}\mu(a)$$
合并：
$$\sum_{d=1}^{n}d\sum_{t=1}^{\lfloor\frac{n}{d}\rfloor}t^2\mu(t)*S(\lfloor\frac{n}{dt}\rfloor)*S(\lfloor\frac{m}{dt}\rfloor)$$
其中
$$S(n)=\frac{n*(n+1)}{2}$$
使$dt=T$，把他拉到前面：
$$\sum_{T=1}^{n}S(\lfloor\frac{n}{T}\rfloor)*S(\lfloor\frac{m}{T}\rfloor)*\sum_{ab=T}a*b^2\mu(b)$$
即
$$\sum_{T=1}^{n}S(\lfloor\frac{n}{T}\rfloor)*S(\lfloor\frac{m}{T}\rfloor)*T*\sum_{b|T}b*\mu(b)$$
设$f(T)=\sum_{b|T}b*\mu(b)$，易知$f(n)$为积性函数，且
$$f(p)=1-p, f(p^k)=f(p)\quad(p\in prime)$$
# 做法
线性筛出$f(n)$，预处理出$T*f(T)$的前缀和，原式用数论分块算即可。
# 代码
```cpp
#include <algorithm>
#include <iostream>

using namespace std;
constexpr long long kcz = 20101009;

int v[10000001], p[10000001], pc;
long long g[10000001];

void preproc(int n)
{
	g[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		if(!v[i]) p[++pc] = i, g[i] = (1 - i) % kcz;
		for(int j = 1; j <= pc && i * p[j] <= n; j++)
		{
			v[i * p[j]] = true;
			if(!(i % p[j]) && (g[i * p[j]] = g[i])) break;
			g[i * p[j]] = (g[i] * g[p[j]]) % kcz;
		}
	}
	for(int i = 2; i <= n; i++)
		(g[i] = g[i] * i % kcz + g[i - 1]) %= kcz;
}

inline long long s(long long k)
{
	return (k * (k + 1) / 2) % kcz;
}

int main()
{
	preproc(10000000);
	int n, m;
	long long ret = 0;
	scanf("%d%d", &n, &m);
	if(n > m) swap(n, m);
	for(int l = 1, r; l <= n; l = r + 1)
	{
		r = min(n / (n / l), m / (m / l));
		(ret += (((s(n / l) * s(m / l)) % kcz) * (g[r] - g[l - 1] + kcz) % kcz) % kcz + kcz) %= kcz;
	}
	printf("%lld\n", ret);
}
```

---

## 作者：JustinRochester (赞：21)

[题目](https://www.luogu.org/problem/P1829)

我的第一篇莫比乌斯反演题解  ~~兴奋兴奋兴奋~~

贡献一个本人自己想的思路，你从未看到过的船新思路

---

**【分析】**
---

显然，题目要求求的是 $\displaystyle Ans=\sum_{i=1}^n\sum_{j=1}^m lcm(i,j)$

根据数论知识，很显然 $lcm(i,j)={ij\over gcd(i,j)}$

$\therefore \displaystyle Ans=\sum_{i=1}^n\sum_{j=1}^m lcm(i,j)$

$\displaystyle \qquad\quad=\sum_{i=1}^n\sum_{j=1}^m{ij\over gcd(i,j)}$

$\displaystyle \qquad\quad =\sum_{k=1}^{min(n,m)}\sum_{i=1}^n\sum_{j=1}^m{ij\over k}[gcd(i,j)= k]$

考虑 $i,j$ 的贡献：

$\displaystyle \quad Ans=\sum_{k=1}^{min(n,m)}\sum_{i=1}^{\lfloor{n\over k}\rfloor}\sum_{j=1}^{\lfloor{m\over k}\rfloor}{ik\times jk\over k}[gcd(i,j)= 1]$

由 $\displaystyle \sum_{d\mid n}\boldsymbol \mu(d)=\sum_{d\mid n}\boldsymbol \mu(d)\boldsymbol I({n\over d})=(\boldsymbol \mu*\boldsymbol I)(n)=\boldsymbol \epsilon(n)=[n=1]$ 得

$\displaystyle \quad Ans=\sum_{k=1}^{min(n,m)}\sum_{i=1}^{\lfloor{n\over k}\rfloor}\sum_{j=1}^{\lfloor{m\over k}\rfloor}ijk\sum_{d\mid gcd(i,j)}\boldsymbol\mu(d)$

$\displaystyle \qquad\quad =\sum_{k=1}^{min(n,m)}\sum_{i=1}^{\lfloor{n\over k}\rfloor}\sum_{j=1}^{\lfloor{m\over k}\rfloor}ijk\sum_{d\mid i\bigwedge d\mid j}\boldsymbol\mu(d)$

调换顺序，枚举 $d$

$\displaystyle \quad Ans=\sum_{k=1}^{min(n,m)}\sum_{d=1}^{min(\lfloor{n\over k}\rfloor,\lfloor{m\over k}\rfloor)}\boldsymbol \mu(d)\sum_{i=1}^{\lfloor{n\over k}\rfloor}\sum_{j=1}^{\lfloor{m\over k}\rfloor}ijk[d\mid i\bigwedge d\mid j]$

$\displaystyle \qquad\quad =\sum_{k=1}^{min(n,m)}\sum_{d=1}^{min(\lfloor{n\over k}\rfloor,\lfloor{m\over k}\rfloor)}\boldsymbol \mu(d)\sum_{i=1}^{\lfloor{n\over k}\rfloor}\sum_{j=1}^{\lfloor{m\over k}\rfloor}ijk[d\mid i][d\mid j]$

各回各家 ~~，各找各妈~~

$\displaystyle \quad Ans=\sum_{k=1}^{min(n,m)}k\sum_{d=1}^{min(\lfloor{n\over k}\rfloor,\lfloor{m\over k}\rfloor)}\boldsymbol \mu(d)\sum_{i=1}^{\lfloor{n\over k}\rfloor}i[d\mid i]\sum_{j=1}^{\lfloor{m\over k}\rfloor}j[d\mid j]$

考虑 $i,j$ 的贡献：

$\displaystyle \quad Ans=\sum_{k=1}^{min(n,m)}k\sum_{d=1}^{min(\lfloor{n\over k}\rfloor,\lfloor{m\over k}\rfloor)}\boldsymbol \mu(d)\sum_{i=1}^{\lfloor{n\over kd}\rfloor}i\times d[1\mid i]\sum_{j=1}^{\lfloor{m\over kd}\rfloor}j\times d[1\mid j]$

$\displaystyle \qquad\quad=\sum_{k=1}^{min(n,m)}k\sum_{d=1}^{min(\lfloor{n\over k}\rfloor,\lfloor{m\over k}\rfloor)}d^2\boldsymbol \mu(d)\sum_{i=1}^{\lfloor{n\over kd}\rfloor}i\sum_{j=1}^{\lfloor{m\over kd}\rfloor}j$

大部分 dalao 就到此为止，接下来分段用整除分块求解

本人则根据套路又化简了一下：

设 $\displaystyle T=kd,Sum(n)=\sum_{i=1}^ni={i(i+1)\over 2}$

$\displaystyle \quad Ans=\sum_{k=1}^{min(n,m)}k\sum_{T=1}^{min(n,m)}[k\mid T]({T\over k})^2\boldsymbol \mu({T\over k})Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)$

调换顺序，先枚举 $T$

$\displaystyle \quad Ans=\sum_{T=1}^{min(n,m)}T^2Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)\sum_{k\mid T}{1\over k}\boldsymbol \mu({T\over k})$

~~哦吼，凉凉。这是什么鬼东西~~

---

一看题目，答案需要对一个大于 $min(n,m)$ 的质数取模

所以，${1\over k}$ 显然可以表现为逆元形式

设 $\boldsymbol {Inv}(n)=n^{-1}$

$\displaystyle \quad Ans=\sum_{T=1}^{min(n,m)}T^2Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)\sum_{k\mid T}\boldsymbol{Inv}(k)\boldsymbol \mu({T\over k})$

大家注意 $\displaystyle\sum_{k\mid T}\boldsymbol{Inv}(k)\boldsymbol \mu({T\over k})$

这玩意儿是不是很像迪利克雷卷积呢？我们可以确定 $\boldsymbol\mu(n)$ 是个积性函数，如果 $\boldsymbol{Inv}(n)$ 也是积性函数，那它就必然是卷积成一个新的积性函数了

而对 $\forall gcd(a,b)=1\Leftrightarrow \boldsymbol{Inv}(ab)=(ab)^{-1}\equiv a^{-1}\times b^{-1}=\boldsymbol{Inv}(a)\times \boldsymbol{Inv}(b)(\mod 20101009)$

所以，我们发现，在取模意义下 $\boldsymbol {Inv}(n)$ 也是积性函数

所以不妨设 $\boldsymbol f=\boldsymbol \mu*\boldsymbol {Inv}$

$\displaystyle \quad Ans=\sum_{T=1}^{min(n,m)}T^2\boldsymbol f(T)Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)$

再设 $\boldsymbol g(n)=n^2\boldsymbol f(n)$

> $\boldsymbol g(n)=\boldsymbol{id}^2(n)\boldsymbol f(n)$

所以 $\boldsymbol g(n)$ 也是积性函数，同时，式子化简完毕：

$\displaystyle \quad Ans=\sum_{T=1}^{min(n,m)}\boldsymbol g(T)Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)$

只要我们线性求出 $\boldsymbol g(T)$ 的前缀和，就可以用整除分块出来了

---

根据 $\boldsymbol g(n)$ 是积性函数，我们可以知道它一定是可以线性筛出来的

我们先考虑 $\boldsymbol f(n)$

$\displaystyle \boldsymbol f(1)=\sum_{d\mid 1}\boldsymbol \mu({1\over d})\times d^{-1}=\boldsymbol \mu(1)\times 1^{-1}=1\times 1=1$

$\displaystyle \therefore \boldsymbol g(1)=1^2\boldsymbol f(1)=1\times 1=1$

对 $\forall p\in prime$

$\displaystyle \boldsymbol f(p)=\sum_{d\mid p}\boldsymbol {Inv}(d)\boldsymbol\mu({p\over d})$

$\displaystyle \qquad\ =\boldsymbol \mu(p)\times 1^{-1}+\boldsymbol \mu(1)\times p^{-1}$

$\displaystyle \qquad\ =(-1)+p^{-1}$

$\displaystyle \qquad\ =p^{-1}-1$

$\displaystyle \qquad\ =(p^1)^{-1}-(p^0)^{-1}$

对 $\forall k>1$

$\displaystyle \boldsymbol f(p^k)=\sum_{d\mid p^k}\boldsymbol {Inv}(d)\boldsymbol\mu({p^k\over d})$

$\displaystyle\qquad\ =\sum_{t=0}^k\boldsymbol{Inv}(p^{k-t})\boldsymbol \mu(p^t)$

$\displaystyle\qquad\ =\sum_{t=0}^1\boldsymbol{Inv}(p^{k-t})\boldsymbol \mu(p^t)+\sum_{t=2}^k\boldsymbol{Inv}(p^{k-t})\boldsymbol \mu(p^t)$

$\displaystyle \qquad\ =\boldsymbol{Inv}(p^k)\boldsymbol \mu(1)+\boldsymbol{Inv}(p^{k-1})\boldsymbol \mu(p)+\sum_{t=2}^k\boldsymbol{Inv}(p^{k-t})\times 0$

$\displaystyle \qquad\ =(p^k)^{-1}-(p^{k-1})^{-1}$

$\therefore \boldsymbol f(p^k)=(p^k)^{-1}-(p^{k-1})^{-1}=(p^k)^{-1}(1-p),k\in N_+$

$\therefore \boldsymbol g(p^k)=(p^k)^2\boldsymbol f(p^k)$

$\displaystyle \qquad\quad\ \ =p^k\times p^k\times (p^k)^{-1}\times (1-p)$

$\displaystyle \qquad\quad\ \ =p^k\times (1-p)$

$\displaystyle \qquad\quad\ \ =p^k-p^{k+1}$

$\displaystyle \boldsymbol g(p^k)=p\times \boldsymbol g(p^{k-1})$

---

$\therefore$ 对 $\forall p\in prime$

$\boldsymbol g(p\times n)=\begin{cases}p\times \boldsymbol g(n),p\mid n\\\ \\\ \\(1-p)p\times \boldsymbol g(n),p\nmid n\end{cases}$

即 $\boldsymbol g(p\times n)=p\times\boldsymbol g(n)\times\begin{cases}1,p\mid n\\\ \\\ \\(1-p),p\nmid n\end{cases}$

---

这里对整除分块做一个讲解，已经掌握的 dalao 请跳过：

对于刚刚这个式子，我们希望在已知 $\boldsymbol g(n)$ 的情况下 $O(\sqrt n)$ 得出答案

$\displaystyle \quad Ans=\sum_{T=1}^{min(n,m)}\boldsymbol g(T)Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)$

这边有一个原理： 对 $\forall d\in Z_+,\lfloor{n\over d}\rfloor$ 的取值只有不超过 $2\sqrt n$ 个

>证明：对 $\forall d\leq \sqrt n,{n\over d}$ 只有不超过 $\sqrt n$ 个取值；对 $\forall d> \sqrt n,\lfloor{n\over d}\rfloor<\lfloor\sqrt n\rfloor$ ，也只有不超过 $\sqrt n$ 个取值。加起来，不超过 $2\sqrt n$ 个

整除分块的原理即从此而来：

我们先考虑单维情况，只含 $n$ 或只含 $m$：

设对 $i\in[l,r]$ 满足：

$\lfloor{n\over l-1}\rfloor\neq\lfloor{n\over l}\rfloor=\lfloor{n\over i}\rfloor=\lfloor{n\over r}\rfloor\neq \lfloor{n\over r+1}\rfloor$

则有 $r=max(i)\Leftrightarrow {n\over r}=min({n\over i})=\lfloor{n\over i}\rfloor$

$\therefore r={n\over \lfloor{n\over i}\rfloor}$

若已知 $l$ ，则 $r={n\over \lfloor{n\over l}\rfloor}$

那 $l$ 怎么知道呢？

已知第一个为 $l=1$ ，且每个 $l$ 对应且仅对应一个 $r$

所以当 $l=r+1$ 时， $l$ 一定为下个区间的最小值

既然满足如此关系，则：

$\displaystyle \quad ans=\sum_{T=l}^r\boldsymbol g(T)Sum(\lfloor{n\over T}\rfloor)Sum(\lfloor{m\over T}\rfloor)$

$\displaystyle \qquad\quad =\sum_{T=l}^r\boldsymbol g(T)Sum(\lfloor{n\over r}\rfloor)Sum(\lfloor{m\over r}\rfloor)$

$\displaystyle \qquad\quad =Sum(\lfloor{n\over r}\rfloor)Sum(\lfloor{m\over r}\rfloor)\sum_{T=l}^r\boldsymbol g(T)$

设 $\displaystyle G(n)=\sum_{i=1}^n\boldsymbol g(n)$

$\displaystyle ans=Sum(\lfloor{n\over r}\rfloor)Sum(\lfloor{m\over r}\rfloor)[G(r)-G(l-1)]$

最后只需要 $Ans=\sum ans$ 进行 $O(\sqrt n)$ 统计即可

---

对于二维情况，依葫芦画瓢：

设 $i\in[l,r],s.t.$

$\lfloor{n\over l-1}\rfloor\neq\lfloor{n\over l}\rfloor=\lfloor{n\over i}\rfloor=\lfloor{n\over r}\rfloor\neq \lfloor{n\over r+1}\rfloor$

$\lfloor{m\over l-1}\rfloor\neq\lfloor{m\over l}\rfloor=\lfloor{m\over i}\rfloor=\lfloor{m\over r}\rfloor\neq \lfloor{m\over r+1}\rfloor$

则在 $l$ 确定的情况下，为了使第一个式子得到满足，会得到 $r_1={n\over \lfloor{n\over l}\rfloor}$

为了使第二个式子得到满足会得到 $r_2={m\over \lfloor{m\over l}\rfloor}$

故为使得两式同时成立，取 $r=min(r_1,r_2)$ 即可

剩余的步骤与一维一样  ~~很简单吧~~

---

**【代码】**
---

那本蒟蒻就放 ~~我码风极丑的~~ 代码了

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define f(a,b,c,d) for(register int a=b,c=d;a<=c;a++)
#define g(a,b,c,d) for(register int a=b,c=d;a>=c;a--)
//#define LOCAL
typedef int i32;
typedef unsigned int u32;
typedef long long int i64;
typedef unsigned long long int u64;
const i32 MOD=20101009;
const i32 MAXN=1e7+10;
typedef i32 ar[MAXN];

namespace HABIT{//读入输出优化和一堆黑科技，不必管
    template<typename T> inline T Max(T a) { return a; }
    template<typename T,typename... Args> inline T Max(T a,Args... args){
        T b=Max(args...);
        return (a>b)?a:b;
    }
    template<typename T> inline T Min(T a) { return a; }
    template<typename T,typename... Args> inline T Min(T a,Args... args){
        T b=Min(args...);
        return (a<b)?a:b;
    }

    #ifdef LOCAL
        inline char gc() { return getchar(); }
    #else
        inline char gc() {
            static char s[1<<20|1]={0},*p1=s,*p2=s;
            return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++);
        }
    #endif
    inline i32 read(){
        register i32 ans=0;register char c=gc();register bool neg=0;
        while(c<48||c>57) neg^=!(c^'-'),c=gc();
        while(c>=48&&c<=57) ans=(ans<<3)+(ans<<1)+(c^48),c=gc();
        return neg?-ans:ans;
    }

    char Output_Ans[1<<20|1],*Output_Cur=Output_Ans;
    inline bool output() { Output_Cur-=fwrite(Output_Ans,1,Output_Cur-Output_Ans,stdout); }
    inline void print(char c) { (Output_Cur-Output_Ans+1>>20)&&output(),*(Output_Cur++)=c; }
    inline void print(i32 x){
        char buf[20]={0}; (Output_Cur-Output_Ans+sprintf(buf,"%d",x)>>20)&&output();
        Output_Cur+=sprintf(Output_Cur,"%d",x);
    }
}
using namespace HABIT;

i32 d_N,d_M;

ar ar_d_G,ar_d_Fc,ar_d_Prime;
inline void pre(){
    i32 *ptr_d_Prime=ar_d_Prime;
    ar_d_G[1]=1;
    f(i,2,I,d_N){
        if(!ar_d_Fc[i])
            ar_d_G[i]=(1ll-i)*(*(ptr_d_Prime++)=(ar_d_Fc[i]=i))%MOD+MOD;
            //肯定是负数，取模完直接加上
        for(register i32 *p=ar_d_Prime;p<ptr_d_Prime&&*p*i<=d_N;p++){
            ar_d_Fc[*p*i]=*p;
            ar_d_G[*p*i]=1ll*(*p)*ar_d_G[i]%MOD;
            if(*p<ar_d_Fc[i]) ar_d_G[*p*i]=(1ll-*p)*ar_d_G[*p*i]%MOD+MOD;
            //肯定是负数，取模完直接加上
            else break;
        }
        ar_d_G[i]+=ar_d_G[i-1];
        if(ar_d_G[i]>=MOD) ar_d_G[i]-=MOD;
        //前缀和
    }
}

int main(){
    d_N=read(),d_M=read();
    if(d_N>d_M) d_N^=d_M^=d_N^=d_M;
    pre();
    i32 d_Ans=0;
    for(register i32 l=1,r;l<=d_N;l=r+1){
        r=Min( d_N/(d_N/l) , d_M/(d_M/l) );
        i64 d_Tmp=ar_d_G[r]-ar_d_G[l-1];
        i32 d_A=(1ll+d_N/r)*(d_N/r)/2%MOD;
        i32 d_B=(1ll+d_M/r)*(d_M/r)/2%MOD;
        d_Tmp=d_Tmp*d_A%MOD*d_B%MOD;
        d_Ans+=d_Tmp;
        if(d_Ans<0) d_Ans+=MOD;
        else if(d_Ans>=MOD) d_Ans-=MOD;
    }
    print(d_Ans);
    output();
    return 0;
}
```

---

最后安利一下 [本蒟蒻的博客](https://www.luogu.org/blog/JustinRochester/)

---

## 作者：George1123 (赞：13)

# 题解-[国家集训队]Crash的数字表格 / JZPTAB

**[博客中阅读](https://www.cnblogs.com/Wendigo/p/12456965.html)**

**前置知识：**
> 莫比乌斯反演 [</>](https://www.cnblogs.com/Wendigo/p/12441788.html)

---

> [\[国家集训队\]Crash的数字表格 / JZPTAB](https://www.luogu.com.cn/problem/P1829)

> 单组测试数据，给定 $n,m$ ，求 
> $$\sum\limits_{i=1}^n\sum\limits_{j=1}^m\operatorname{lcm}(i,j)\bmod 20101009$$

> 数据范围：$1\le n,m\le 10^7$。

---

作为写出了最暴力的做法的蒟蒻，来推个式子。

$n\le m$，一气呵成（洛谷好像不怎么支持这种恐怖 $\LaTeX$）：

![bbbbb.png](https://i.loli.net/2020/03/10/JsBZhKzfaCT9yY1.png)

将 $x=dk$ 带入：

$$g(n,m)=\sum\limits_{x=1}^nx\cdot\frac{\lfloor\frac{n}{x}\rfloor(\lfloor\frac{n}{x}\rfloor+1)}{2}\cdot\frac{\lfloor\frac{m}{x}\rfloor(\lfloor\frac{m}{x}\rfloor+1)}{2}\sum\limits_{k|x}k\mu(k)$$

然后筛 $\mu(k)$ 时顺便计算 $h(k)=k\mu(k)$，最后狄利克雷前缀和求 $f(k)=\sum\limits_{k|x}k\mu(k)$。

别忘了膜拜 $20101009$，时间复杂度 $\Theta(N+n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define lng long long
#define lit long double
#define kk(i,n) "\n "[i<n]
const int inf=0x3f3f3f3f;
const lng Inf=1e17;

//&Mobius
const int N=1e7;
const int mod=20101009;
bitset<N+10> np;
int mu[N+10],cnt,p[N+10],f[N+10];
void Mobius(){
	f[1]=mu[1]=1;
	for(int i=2;i<=N;i++){
		if(!np[i]) p[++cnt]=i,mu[i]=-1;
		f[i]=(mu[i]*i+mod)%mod;
		for(int j=1;j<=cnt&&i*p[j]<=N;j++){
			np[i*p[j]]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;break;}
			mu[i*p[j]]=-mu[i];
		}
	}
	for(int j=1;j<=cnt;j++)
		for(int i=1;i*p[j]<=N;i++)
			(f[i*p[j]]+=f[i])%=mod; //狄利克雷前缀和
}


//&Data
int n,m,ans;
int bitfun(int x){
	lng res=1ll*x*f[x]%mod;
	(res*=1ll*(n/x+1)*(n/x)/2%mod)%=mod;
	(res*=1ll*(m/x+1)*(m/x)/2%mod)%=mod; //如上
	//这个1ll不乘要爆long long，30分。
	return (int)res;
}

//&Main
int main(){
	Mobius();
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	for(int i=1;i<=n;i++)
		(ans+=bitfun(i))%=mod;
	printf("%d\n",ans);
	return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：IceLocke (赞：9)

刚刚学了莫比乌斯反演，来写一篇题解qwq（安利一波[我的博客](https://www.icelocke.site/?p=1271)，里面也有这题的题解）。

我们已经知道了 $lcm(i, j) = \frac{ij}{\gcd(i, j)}$ ，直接进行一波莫比乌斯反演。接下来就来推一推式子：

![](https://www.icelocke.site/wp-content/uploads/2018/12/QQ20181210-231801.png)

（洛谷这边对连等式的显示好像有点问题，只能用图片啦qwq）

我们从 $(1)$ ~ $(5)$ 依次介绍一下推导过程和常见的套路：

1. 通常我们可以将求 $\sum \gcd(i, j)$ 的问题转为枚举 $\gcd(i, j)$ 统计 $[\gcd(i, j) == k]$ 的问题。于是我们将 $(0)$ 中对 $\frac{ij}{\gcd(i, j)}$ 求和转为枚举 $k$ 统计 $\frac{ij}{k}[gcd(i, j) == k]$，因为枚举 $k$ 的部分在最外层，显然 $\frac{1}{k}$ 可以放在外面， 让式子更简，这样就得到了 $(1)$。

2. 因为 $\gcd(i, j) == k$，显然有 $\gcd(\frac{i}{k}, \frac{j}{k}) == 1$ ，我们尝试枚举 $\frac{i}{k}$ 和 $\frac{j}{k}$，显然上界为 $\lfloor\frac{n}{k}\rfloor$ 和 $\lfloor \frac{m}{k} \rfloor$ 。设 $i' = \frac{i}{k}, j' = \frac{j}{k}$，由于枚举 $i', j'$的贡献少了 $k^2$ ，我们在前面乘上 $k^2$，于是有
$$\sum_{i=1}^{n}\sum_{j=1}^m ij\ [\gcd(i, j) == k] \Leftrightarrow \sum_{i'=1}^{\lfloor{\frac{n}{k}}\rfloor} \sum_{j'=1}^{\lfloor{\frac{m}{k}}\rfloor} i'j'k^2 \ [\gcd(i', j') == 1]$$
    然后为了写起来简单一点（~~其实就是懒~~），我们就干脆把 $'$ 给他去掉了，式子也就变成了 $(2)$。

3. 然后是莫比乌斯反演的简单套路
$$[\gcd(i, j) == 1] \Leftrightarrow \sum_{d\mid \gcd(i, j)} \mu(d)$$
    直接套进去就行了，我们就得到了 $(3)$。

4. 看上去对 $\mu(d)$ 的枚举中必须要整除 $\gcd(i, j)$ 是不是非常烦？我们继续将 $\sum \limits _{d\mid \gcd(i, j)} \mu(d)$ 变换位置，考虑枚举 $d$ 来实现我们的想法。因为 $d\mid\gcd(i, j)$，显然可以得到 $d$ 的上界为 $\min(\lfloor\frac{n}{k}\rfloor, \lfloor\frac{m}{k}\rfloor)$ ，同样我们也可以知道在枚举 $i, j$ 的时候要满足 $d \mid i, \ d \mid j$，因此
    $$\sum_{i=1}^{\lfloor{\frac{n}{k}}\rfloor} \sum_{j=1}^{\lfloor{\frac{m}{k}}\rfloor} ij \sum_{d\mid\gcd(i, j)} \mu(d) \Leftrightarrow \sum_{d=1}^{\min(\lfloor{\frac{n}{k}}\rfloor, \lfloor\frac{m}{k}\rfloor)} \mu(d)\ \sum_{d\mid i}^{\lfloor\frac{n}{k}\rfloor}\sum_{d\mid j}^{\lfloor\frac{m}{k}\rfloor} ij$$
    也就得到了 $(4)$。

5. 好像快结束了！我们想一下如何将后面的和式 $\sum \limits_{d\mid i}^{\lfloor\frac{n}{k}\rfloor}\sum \limits_{d\mid j}^{\lfloor\frac{m}{k}\rfloor} ij$ 变得更简单一点。跟刚刚说的第 $2$ 点类似，我们采用换元法，直接枚举 $i, j$ 来统计 $ij$ 。设 $i' = di, j' = dj$ ，显然可以得到 $i', j'$ 枚举的上界为 $\lfloor\frac{n}{kd}\rfloor, \lfloor\frac{n}{kd}\rfloor$ ，因此
    $$\sum \limits_{d\mid i}^{\lfloor\frac{n}{k}\rfloor}\sum \limits_{d\mid j}^{\lfloor\frac{m}{k}\rfloor} ij \Leftrightarrow \sum_{i'=1}^{\lfloor\frac{n}{kd}\rfloor}\sum_{j'=1}^{\lfloor\frac{m}{kd}\rfloor} i'j'$$
    接着把 $'$ 去掉，就很开心的推完了。

我们继续化简这个式子，以便程序实现。设 $f(n, m) = \sum \limits_{i=1}^n \sum \limits_{j=1}^m i j$ 。考虑一下这个式子的 $O(1)$ 求法，显然有
$$\sum_{i=1}^{n}\sum_{j=1}^{m}ij = \sum_{i=1}^{n}i\sum_{j=1}^{m}j$$
然后用一下等差数列求和公式就有
$$f(n, m) = \frac{n(n+1)}{2} \times \frac{m(m+1)}{2}$$
然后就有$$\mathbf{Orig\ Equ}= \sum_{k=1}^{\min(n, m)} k \sum_{d=1}^{\min(\lfloor{\frac{n}{k}}\rfloor, \lfloor\frac{m}{k}\rfloor)} \mu(d)\ d^2 \ f(\lfloor{\frac{n}{kd}}\rfloor, \lfloor\frac{m}{kd}\rfloor)$$
进一步化简，设 $g(n, m) = \sum \limits_{d=1}^{\min(n, m)} \mu(d)\ d^2 \ f(\lfloor{\frac{n}{d}}\rfloor, \lfloor\frac{m}{d}\rfloor)$ ，则有
$$\mathbf{Orig\ Equ} = \sum_{k=1}^{\min(n, m)} g(\lfloor\frac{n}{k}\rfloor, \lfloor\frac{m}{k}\rfloor)$$

直到这步，我们求解答案的时间复杂度还是 $O(n\log n)$，明显不符合数据规模。观察发现 $f(n, m)$ 和 $g(n, m)$ 都可以数论分块，套两遍数论分块就可以将时间复杂度优化到 $O(n)$，这样就做完啦qwq

---
**代码**
```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
#define R register
#define LL long long
#define int LL

using namespace std;

const int MAXN = 2e7 + 10, 
          MOD = 20101009;

int n, m, cnt, ans, s[MAXN], mu[MAXN], prime[MAXN];
bitset<MAXN> bits;

// 线性筛筛出 mu(d) * d^2 的前缀和
inline void prework() {
    int lim = max(n, m);
    mu[1] = 1;
    for(int i = 2; i <= lim; i++) {
        if(bits[i] == 0)
            mu[i] = -1, prime[++cnt] = i;
        for(int j = 1; j <= cnt && prime[j] * i <= lim; j++) {
            bits[i * prime[j]] = 1;
            if(i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            else mu[i * prime[j]] = -mu[i];
        }
    }
    // 筛出前缀和
    for(int i = 1; i <= lim; i++)
        s[i] = (s[i - 1] + 1ll * (mu[i] + MOD) % MOD * i % MOD * i) % MOD;
}

inline int f(int a, int b) {
    return ((1ll * a * (a + 1) / 2 % MOD) % MOD * (1ll * b * (b + 1) / 2 % MOD) % MOD) % MOD;
}

// 第一次数论分块
inline int g(int a, int b) {
    int lim = min(a, b), res = 0;
    for(int l = 1, r; l <= lim; l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        res = (res + 1ll * (s[r] - s[l - 1] + MOD) % MOD * f(a / l, b / r) % MOD) % MOD;
    }
    return res;
}

// 第二次数论分块
inline int slove(int a, int b) {
    int lim = min(a, b), res = 0;
    for(int l = 1, r; l <= lim; l = r + 1) {
        r = min(a / (a / l), b / (b / l));
        res = (res + 1ll * (r - l + 1) * (l + r) / 2 % MOD * g(a / l, b / l) % MOD + MOD) % MOD;
    }
    return res;
}

signed main() {

    scanf("%lld%lld", &n, &m);

    prework();

    printf("%lld\n", (slove(n, m) + MOD) % MOD);
}
```

---

## 作者：The_KOG (赞：8)

[原博客地址][1]

[1]:https://www.cnblogs.com/nlKOG/p/10543409.html

这道题在bzoj有多组数据,那么洛谷题解里的双重分块在bzoj就会T

那我就讲一下只有一重分块的做法

时间复杂度(大概) O($N_{max}+T\sqrt{N_i}$) 其中T为数据组数

$
\sum\limits_{i=1}^n\sum\limits_{j=1}^m\operatorname{lcm(i,j)}
$

$
=\sum\limits_{i=1}^n\sum\limits_{j=1}^m\frac{i\cdot j}{\gcd(i,j)} 
$

$
=\sum\limits_{i=1}^n
\sum\limits_{i=1}^m
\sum\limits_{d=1}^{min(n,m)}\frac{i\cdot j}d[gcd(i,j)=d]
$

$
=\sum\limits_{d=1}^{min(n,m)}
\sum\limits_{i=1}^{\lfloor\frac{n}d\rfloor}
\sum\limits_{i=1}^{\lfloor\frac{m}d\rfloor}
dij\cdot [gcd(i,j)=1]
$

$
=\sum\limits_{d=1}^{min(n,m)}
\sum\limits_{i=1}^{\lfloor\frac{n}d\rfloor}
\sum\limits_{i=1}^{\lfloor\frac{m}d\rfloor}
dij
\sum\limits_{x|gcd(i,j)}^{}\mu(x)
$

$
=\sum\limits_{d=1}^{min(n,m)}
\sum\limits_{i=1}^{\lfloor\frac{n}d\rfloor}
\sum\limits_{i=1}^{\lfloor\frac{m}d\rfloor}
dij
\sum\limits_{x|i,x|j}\mu(x)
$

然后把μ(x)和d调到前面去,i变成ix,j变成jx

$
=\sum\limits_{d=1}^{min(n,m)}d
\sum\limits_{x=1}^{min(\lfloor\frac{n}d\rfloor,\lfloor\frac{m}d\rfloor)}μ(x)
\sum\limits_{i=1}^{\lfloor\frac{n}{dx}\rfloor}ix
\sum\limits_{j=1}^{\lfloor\frac{m}{dx}\rfloor}jx
$

然后把x也调到前面去

$
=\sum\limits_{d=1}^{min(n,m)}d
\sum\limits_{x=1}^{min(\lfloor\frac{n}d\rfloor,\lfloor\frac{m}d\rfloor)}x^2μ(x)
\sum\limits_{i=1}^{\lfloor\frac{n}{dx}\rfloor}
\sum\limits_{j=1}^{\lfloor\frac{m}{dx}\rfloor}ij
$

然后等差数列

$
=\sum\limits_{d=1}^{min(n,m)}d
\sum\limits_{x=1}^{min(\lfloor\frac{n}d\rfloor,\lfloor\frac{m}d\rfloor)}x^2\mu(x)
\frac{(1+\lfloor\frac{n}{dx}\rfloor)\lfloor\frac{n}{dx}\rfloor}{2}\frac{(1+\lfloor\frac{m}{dx}\rfloor)\lfloor\frac{m}{dx}\rfloor}{2}
$

在洛谷的话推到这一步就够了


但是想要在bzoj过这道题还要接着优化

然后设T=dx,所以x=$\frac{T}{d}$

$
=\sum\limits_{T=1}^{min(n,m)}
\frac{(1+\lfloor\frac{n}{T}\rfloor)\lfloor\frac{n}{T}\rfloor}{2}\frac{(1+\lfloor\frac{m}{T}\rfloor)\lfloor\frac{m}{T}\rfloor}{2}
\sum\limits_{d|T}d\frac{T^2}{d^2}\mu(\frac{T}{d})
$

由于对称性

$
=\sum\limits_{T=1}^{min(n,m)}
\frac{(1+\lfloor\frac{n}{T}\rfloor)\lfloor\frac{n}{T}\rfloor}{2}\frac{(1+\lfloor\frac{m}{T}\rfloor)\lfloor\frac{m}{T}\rfloor}{2}
\sum\limits_{d|T}\frac{T}{d}d^2\mu({d})
$

$
=\sum\limits_{T=1}^{min(n,m)}
\frac{(1+\lfloor\frac{n}{T}\rfloor)\lfloor\frac{n}{T}\rfloor}{2}\frac{(1+\lfloor\frac{m}{T}\rfloor)\lfloor\frac{m}{T}\rfloor}{2}
\sum\limits_{d|T}Td\mu({d})
$

然后我们设

$
g(T)=\sum\limits_{d|T}Td\mu({d})
$

然后可以发现g是一个积性函数

所以有

$
g(\Pi P_i^{ai})=\Pi g(P_i^{ai})
$

$
=\Pi (T*P_i^{0}*\mu(1)+T*P_i*\mu(P_i))
$

$
=\Pi (T-T*P_i)
$

$
=\Pi (T*(1-P_i))
$

因此

$
g(p)=1-p
$

$
g(p^k)=g(p^{k-1})
$

当np互质时,有

$
g(np)=g(n)*g(p)
$

然后筛一筛就出来了

代码：
```
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define N 10000010
using namespace std;
const int mod=20101009;
int vis[N],prim[N/10],mu[N],low[N],sum[N],cnt;
void pre(int n){
	mu[1]=1;
	sum[1]=low[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])mu[i]=-1,prim[++cnt]=i,low[i]=i,sum[i]=(1-i+mod)%mod;
		for(int j=1;j<=cnt&&i*prim[j]<=n;j++){
			vis[i*prim[j]]=1;
			if(i%prim[j]==0){
				low[i*prim[j]]=low[i]*prim[j];
				if(low[i]==i)sum[i*prim[j]]=sum[i];
				else sum[i*prim[j]]=sum[i/low[i]]*sum[prim[j]*low[i]]%mod;
				break;
			}else{
				low[i*prim[j]]=prim[j];
				sum[i*prim[j]]=sum[i]*sum[prim[j]]%mod;
				mu[i*prim[j]]=-mu[i];
			}
		}
	}
	for(int T=1;T<=n;T++)sum[T]=(T*sum[T]%mod+sum[T-1])%mod;
}
int ask(int x,int y){return (x+y)*(y-x+1)/2%mod;}
int query(int n,int m){
	int re=0;
	int mx=min(n,m);
	for(int l=1,r;l<=mx;l=r+1){
		r=min(n/(n/l),m/(m/l));
		int tmp=ask(1,n/l)*ask(1,m/l)%mod;
		tmp=tmp*(sum[r]-sum[l-1]+mod)%mod;
		re=(re+tmp)%mod;
	}
	return re;
}
int t;
signed main(){
	pre(10000000);
	int n,m;
	scanf("%lld%lld",&n,&m);
	printf("%lld\n",query(n,m));
	return 0;
}
```

upd:之前letax炸了,补下锅

---

## 作者：glassy (赞：6)

### 题目大意
给定 $n,m$，令
$$\sum_{i=1}^{n}\sum_{j=1}^{m}lcm(i,j)≡x\pmod {20101009}$$

求最小的非负 $x$。

**数据范围**　$1\leqslant n,m\leqslant 10^{7}$
$$\begin{aligned}\end{aligned}$$

### 题解
开始推式子。
$$\begin{aligned}Ans&=\sum_{i=1}^{n}\sum_{j=1}^{m}\frac{i\times j}{(i,j)}\\&=\sum_{d=1}^{n}\sum_{i=1}^{n}\sum_{j=1}^{m}\frac{i\times j}{d}[(i,j)=d]\\&=\sum_{d=1}^{\min(n,m)}\sum_{i=1}^{\large\lfloor\frac nd\rfloor}\sum_{j=1}^{\large\lfloor\frac md\rfloor}\frac{d\cdot i\times d\cdot j}{d}[(i,j)=1]\\&=\sum_{d=1}^{\min(n,m)}d\sum_{i=1}^{\large\lfloor\frac nd\rfloor}\sum_{j=1}^{\large\lfloor\frac md\rfloor}ij[(i,j)=1]\\&=\sum_{d=1}^{\min(n,m)}d\times \sum_{i=1}^{\large\lfloor\frac nd\rfloor}\sum_{j=1}^{\large\lfloor\frac md\rfloor}ij\sum_{k|i,k|j}\mu(k)\\&=\sum_{d=1}^{\min(n,m)}d\times \sum_{k=1}^{\large\lfloor\frac nd\rfloor}\mu(k)\sum_{k|i}^{i\leqslant {\large\lfloor\frac nd\rfloor}}i\sum_{k|j}^{j\leqslant {\large\lfloor\frac md\rfloor}}j\\&=\sum_{d=1}^{\min(n,m)}d\times \sum_{k=1}^{\large\lfloor\frac {\min(n,m)}d\rfloor}\mu(k)\left(\sum_{k|i}^{i\leqslant {\large\lfloor\frac nd\rfloor}}i\right)\left(\sum_{k|j}^{j\leqslant {\large\lfloor\frac md\rfloor}}j\right)\\&=\sum_{d=1}^{\min(n,m)}d\times \sum_{k=1}^{\large\lfloor\frac {\min(n,m)}d\rfloor}\mu(k)\left(\sum_{i=1}^{\large\lfloor\frac n{dk}\rfloor}ik\right)\left(\sum_{j=1}^{\large\lfloor\frac m{dk}\rfloor}jk\right)\\&=\sum_{d=1}^{\min(n,m)}d\times \sum_{k=1}^{\large\lfloor\frac {\min(n,m)}d\rfloor}k^2\mu(k)\left(\frac{\left(1+\Big\lfloor\dfrac n{dk}\Big\rfloor\right)\Big\lfloor\dfrac n{dk}\Big\rfloor}2\right)\left(\frac{\left(1+\Big\lfloor\dfrac m{dk}\Big\rfloor\right)\Big\lfloor\dfrac m{dk}\Big\rfloor}2\right)\end{aligned}$$


更换枚举项，枚举 $T=kd$，易得其上界为 $n$，并且 $k|T$，则有
$$\begin{aligned}Ans&=\sum_{T=1}^{\min(n,m)}\sum_{k|T}\frac Tk\times k^2\times \mu(k)\times {\left(\frac{\left(1+\Big\lfloor\dfrac n{T}\Big\rfloor\right)\Big\lfloor\dfrac n{T}\Big\rfloor}2\right)}{\left(\frac{\left(1+\Big\lfloor\dfrac m{T}\Big\rfloor\right)\Big\lfloor\dfrac m{T}\Big\rfloor}2\right)}\\&=\sum_{T=1}^{\min(n,m)}{\left(\frac{\left(1+\Big\lfloor\dfrac n{T}\Big\rfloor\right)\Big\lfloor\dfrac n{T}\Big\rfloor}2\right)}{\left(\frac{\left(1+\Big\lfloor\dfrac m{T}\Big\rfloor\right)\Big\lfloor\dfrac m{T}\Big\rfloor}2\right)}\sum_{k|T}k^2\times \mu(k)\times \frac Tk\end{aligned}$$

这里最好不要化简后面的
$$\sum_{k|T}k^2\times \mu(k)\times \frac Tk$$

最好直接把它转换为卷积
$$\begin{aligned}Ans&=\sum_{T=1}^n{\left(\frac{\left(1+\Big\lfloor\dfrac n{T}\Big\rfloor\right)\Big\lfloor\dfrac n{T}\Big\rfloor}2\right)}{\left(\frac{\left(1+\Big\lfloor\dfrac m{T}\Big\rfloor\right)\Big\lfloor\dfrac m{T}\Big\rfloor}2\right)}\Big((id^2\cdot\mu)*id\Big)(T)\end{aligned}$$

如果我们能线性筛出前面的 $(id^2\cdot\mu)*id$ 就大功告成了。
这需要计算其三条特点：
$$\Big((id^2\cdot\mu)*id\Big)(1)=1$$

$$\Big((id^2\cdot\mu)*id\Big)(p)=p\cdot(1-p)$$

$$\Big((id^2\cdot\mu)*id\Big)(p^k)=p^k\cdot(1-p)$$

证明：由于 $p^0=1,p^1=p$，因而我们只需要证明第三条性质成立即可。
$$\begin{aligned}\Big((id^2\cdot\mu)*id\Big)(p^k)&=\sum_{d|p^k} (id^2\cdot\mu)(d)\times id\left(\frac{p^k}{d}\right)\\&=p^k\times \sum_{d|p^k} d\cdot\mu(d)\\&=p^k\times \sum_{t=0}^k p^t\cdot\mu(p^t)\\&=p^k\times \left(p^0\cdot\mu(p^0)+p^1\cdot\mu(p^1)+\sum_{t=2}^kp^t\cdot\mu(p^t)\right)\\&=p^k\times \left(1-p+\sum_{t=2}^kp^t\times0\right)\\&=p^k\cdot\left(1-p\right)\end{aligned}$$

至此，我们能够在 $T(k)=\Theta(1)$ 的时间内求出上面三种位置的函数值，因此，我们可以线性筛了。

总时间复杂度进一步降低到 $T(n)=\Theta(n+\sqrt n)$。

但这样常数有些大，会不会有风险？

考虑杜教筛。

只要求出函数 $\Big((id^2\cdot \mu)*id\Big)$ 的前缀和即可。因此考虑取 $g=id$。

**等等！**

为什么要考虑 $g=id$？为了让后续的 ~~**乱猜**~~ 更方便？如果 $g=id$ 能做到些什么的话，为什么里面那个 $id$ 不能做到？
考虑到卷积有交换律，我们可以忽略后面那个 $*id$ 而直接考虑前面的 $(id^2\cdot \mu)$，很容易发现，对于这个用点乘得到函数只需要取 $g=id^2$ 即可。
$$\begin{aligned}\bigg(\Big((id^2\cdot \mu)*id\Big)*id^2\bigg)(n)&=\bigg(\Big((id^2\cdot \mu)*id^2\Big)*id\bigg)(n)\\&=\sum_{d|n}\Big((id^2\cdot \mu)*id^2\Big)(d)\times\frac nd\\&=\sum_{d|n}\sum_{k|d}k^2\cdot \mu(k)\times\frac {d^2}{k^2}\times \frac nd\\&=n\sum_{d|n}d\sum_{k|d}\mu(k)\\&=n\sum_{d|n}d[d=1]\\&=n\\&=id(n)\end{aligned}$$

的确是个让人省心的函数。
因而有
$$\begin{aligned}n&=\bigg(\Big((id^2\cdot \mu)*id\Big)*id^2\bigg)(n)\\&=\sum_{d|n}\Big((id^2\cdot \mu)*id\Big)(d)\times \frac{n^2}{d^2}\\&=\sum_{d|n,d\not=n}\Big((id^2\cdot \mu)*id\Big)(d)\times \frac{n^2}{d^2}+\Big((id^2\cdot \mu)*id\Big)(n)\end{aligned}$$

移项，得
$$\Big((id^2\cdot \mu)*id\Big)(n)=n-\sum_{d|n,d\not=n}\Big((id^2\cdot \mu)*id\Big)(d)\times \frac{n^2}{d^2}$$
求和
$$\begin{aligned}\text{Sum}_{(id^2\cdot \mu)*id}(n)&=\sum_{i=1}^n\Big((id^2\cdot \mu)*id\Big)(i)\\&=\sum_{i=1}^ni-\sum_{i=1}^n\sum_{d|i,d\not=i}\Big((id^2\cdot \mu)*id\Big)(d)\times \frac{i^2}{d^2}\\&=\frac{(1+n)n}2-\sum_{k=2}^n\sum_{d=1}^{\large\lfloor\frac nk\rfloor}\Big((id^2\cdot \mu)*id\Big)(d)\times\frac{k^2d^2}{d^2}\\&=\frac{(1+n)n}2-\sum_{k=2}^nk^2\times \text{Sum}_{(id^2\cdot \mu)*id}(n)\left(\Big\lfloor\frac nk\Big\rfloor\right)\end{aligned}$$

递归除法分块处理即可，时间复杂度为 $T(n)=\Theta(n^{\frac 34})$
前面莫比乌斯反演的部分除法分块处理，总时间复杂度**仍然**为 $T(n)=\Theta(n^{\frac 34})$。
再把前面 $n\frac 23$ 线性筛出来，时间复杂度就降低到了 $\Theta(n^{\frac 23})$

Accepted  100
用时: 470ms
内存: 13828KB
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 406415
const long long mod=20101009;
long long inv_2=500000004;
long long inv_6=166666668;
long long low[maxn],f[maxn],pri[maxn],vis[maxn],s[maxn];
void sieve(long long n){
    memset(vis,0,sizeof vis);
    long long tot=0;
    vis[1]=low[1]=f[1]=1;
    for (long long i=2;i<=n;i++)
    {
        if(!vis[i]) low[i]=pri[++tot]=i,f[i]=(i-(i*i)%mod+mod)%mod;
        for (long long j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            vis[i*pri[j]]=1;
            if (i%pri[j]==0)
            {
                low[i*pri[j]]=low[i]*pri[j];
                if (low[i]==i)
                    f[i*pri[j]]=((((1-pri[j])*i+mod)%mod)*pri[j]+mod)%mod;
                else
                    f[i*pri[j]]=(f[i/low[i]]*f[low[i]*pri[j]]+mod)%mod;
                break;
            }
            low[i*pri[j]]=pri[j];
            f[i*pri[j]]=(f[i]*f[pri[j]])%mod;
        }
    }
    for(int i=1;i<=n;i++)
    	s[i]=(s[i-1]+f[i]+mod)%mod;
}
long long ft_1(long long a){
    long long t=a%mod;
    return ((((1+(t))*(t))%mod)*inv_2)%mod;
}
long long ft_2(long long a){
    long long t=a%mod;
    return (((t*(t+1)%mod)*(2*t+1)%mod)*inv_6)%mod;
}
map<long long,long long> Sf;
long long S(long long n){
    if(n<=maxn-10) return s[n];
    {	map<long long,long long>::iterator t=Sf.find(n);
        if(t!=Sf.end()) return t->second;	}
    long long ans=ft_1(n);
    for(long long l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        ans-=S(n/l)*(ft_2(r)-ft_2(l-1))%mod;
        ans=(ans+mod)%mod;
    } return Sf[n]=ans;
}
void main2(long long n,long long m){
    long long ans=0;
    long long len=min(n,m);
    for(long long l=1,r;l<=len;l=r+1){
        r=min(n/(n/l),m/(m/l));
        if(r>n) r=n;
        ans+=ft_1(n/l)*ft_1(m/l)%mod*(S(r)-S(l-1))%mod;
        ans=(ans+mod)%mod;
    } printf("%lld",ans); 
}
long long pow_t(long long a,long long b){
    if(b==1) return a%mod;
    long long t=pow_t(a,b/2);
    if((b&1)==0) return t*t%mod;
    return t*t%mod*a%mod;
}
int main(){
    inv_2=pow_t(2,mod-2);
    inv_6=pow_t(6,mod-2);
    sieve(maxn-10);
    long long n,m,ans=0;
    scanf("%lld%lld",&n,&m);
    main2(n,m);
    return 0;
}
```
**记得记忆化，记得记忆化，记得记忆化……别问我怎么知道的。**
~~修改一下模数和规模，本代码还可以通过其[增强版](https://www.51nod.com/Question/Index.html#!#questionId=1063&isAsc=false)。~~

PS：面对luogu的Latex公式不能换行毫无还手之力，改到自闭……

#### 附录：公式对齐方法
```latex
$$\begin{aligned}
T&=\sum_{i=1}^ni\\
&=\frac{n(1+n)}{2}\\
&=\frac 12\left(n+n^2\right)
\end{aligned}$$
```
但是luogu的公式必须写在同一行中，因此应该这么写

```latex
$$\begin{aligned}T&=\sum_{i=1}^ni\\&=\frac{n(1+n)}{2}\\&=\frac 12\left(n+n^2\right)\end{aligned}$$
```

效果：
$$\begin{aligned}T&=\sum_{i=1}^ni\\&=\frac{n(1+n)}{2}\\&=\frac 12\left(n+n^2\right)\end{aligned}$$

---

## 作者：greenty (赞：4)

## 题意

求解式子
$$ANS(n,m) = \sum_{i=1}^n\sum_{j=1}^mlcm(i,j)$$

其中$1 \leq n,m \leq 1e7$

## 分析

因为是单次询问，所需复杂度不高于O(n)

推导的思路： 

将lcm转化成gcd
$$ANS(n,m) = \sum_{i=1}^n\sum_{j=1}^m \frac{i\cdot j}{gcd(i,j)}$$
求和中有gcd, 转变求和顺序，先以相同的gcd分组，枚举gcd。

由gcd的性质可以知道$gcd(i,j)| i $ 并且$gcd(i,j)|j$
$$ANS(n,m) = \sum_{d=1}^n (\frac 1 d\sum_{d|i} \sum_{d|j} ([gcd(i,j)==d]\cdot i \cdot j))$$

观察发现$i$的取值是$d,2d,...,\lfloor\frac n d \rfloor d$，
$j$的取值是$d,2d,...,\lfloor\frac m d \rfloor d$

换元 $i = \frac i d,j = \frac j d$


$$ANS(n,m) = \sum_{d=1}^n d\sum_{i=1}^{\lfloor \frac n d \rfloor} \sum_{j=1}^{\lfloor \frac m d \rfloor}([gcd(i,j)==1]\cdot i \cdot j )$$

令 
$$S(n,m) = \sum_{i=1}^{n} \sum_{j=1}^{m}([gcd(i,j)==1]\cdot i \cdot j )$$

这里是在求解互质的数对的乘积和

则
$$ANS(n,m) = \sum_{d=1}^n( d \cdot S(\lfloor \frac n d\rfloor,\lfloor \frac m d\rfloor))$$

考虑如何求解$S(n,m)$

因为$\epsilon(n)$在n为1的时候为1，其他时候为0

$$S(n,m) = \sum_{i=1}^{n} \sum_{j=1}^{m}(\epsilon(gcd(i,j))\cdot i \cdot j )$$

因为$1 * \mu = \epsilon$

所以用$\mu$ 替代$\epsilon$

$$S(n,m) = \sum_{i=1}^{n} \sum_{j=1}^{m}(\sum _{d|gcd(i,j)}\mu(d))\cdot i \cdot j )$$

于是这里满足的关系是$d | gcd(i,j)$ 且$gcd(i,j)|i,gcd(i,j)|j$，即$d|i,d|j$

和刚刚一样的思路，转化为先枚举因子

$$S(n,m) = \sum_{d=1}^{n} \mu (d) \sum_{d|i} \sum _{d|j} i \cdot j$$

换元 $i = \frac i d,j = \frac j d$

$$S(n,m) = \sum_{d=1}^n \mu(d) d^2\sum_{i=1}^{\lfloor \frac n d \rfloor} \sum_{j=1}^{\lfloor \frac m d \rfloor}( i \cdot j )$$

令
$$g(n,m) = \sum_{i=1}^{n} \sum_{j=1}^{m}( i \cdot j )$$

这里可以用公式计算出来 

$$g(n,m) = \frac {n(n+1)} 2 \cdot \frac {m(m+1)} 2$$

而前半部分的$\mu(d) d^2$可以线性筛筛出莫比乌斯函数后，预处理前缀和求解

则
$$S(n,m) = \sum_{d=1}^n \mu(d)\cdot d^2\cdot g(\lfloor \frac n d \rfloor,\lfloor \frac m d \rfloor)$$

可以分块求解

$$ANS(n,m) = \sum_{d=1}^n( d \cdot S(\lfloor \frac n d\rfloor,\lfloor \frac m d\rfloor))$$

再次分块求解

求得最后答案

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int mod = 20101009;
typedef long long ll;

bool not_prime[10000001];
int mu[10000001];
int prime[1000001];
void mus(int n){
    mu[1] = 1;int tot=0;
    for(int i=2;i<=n;i++) {
        if(not_prime[i]==0) prime[++tot] = i,mu[i]=-1;
        for(int j=1;j<=tot&& prime[j]*i<=n;j++) {
            not_prime[prime[j]*i] = 1;
            if(i%prime[j]==0) {
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]] = -mu[i];
        }
    }

    for(int i=1;i<=n;i++) {
        mu[i] = mu[i] *1ll* i % mod * i % mod;
        mu[i] += mu[i-1];
        mu[i] %= mod;
    }
}

int sum2(int n,int m){
    int a = (n*1ll*(n+1)/2)%mod;
    int b = (m*1ll*(m+1)/2)%mod;
    return a*1ll*b%mod;
}

int sum(int n,int m) {

    if(n>m) swap(n,m);
    int res = 0;
    for(int d=1;d<=n;) {
        int en = min(n/(n/d),m/(m/d));
        int a = sum2(n/d,m/d);
        int b = (mu[en] - mu[d-1] + mod)%mod;
        res += (a*1ll*b%mod);
        res %=mod;
        d = en+1;
    }
    return res;
}
int solve(int n,int m) {
    if(n>m) swap(n,m);
    int res = 0;
    for(int d=1;d<=n;) {
        int en = min(n/(n/d),m/(m/d));
        int a = sum(n/d,m/d);

        int b = ((d+en)*1ll*(en-d+1)/2)%mod;
        res += (a*1ll*b%mod);
        res %= mod;
        d = en+1;
    }
    return res;
}


int main() {
    int n,m;
    cin>>n>>m;
    mus(n);
    cout<<solve(n,m)<<endl;
    return 0;
    int res =0;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            int g = __gcd(i,j);
            res += ((i*1ll*j / g) %mod);
            res %=mod;
        }
    }
    cout<<res<<endl;
}
```





---

## 作者：大眼仔Happy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P1829)

好吧，这题还是和 $\gcd$ 有一点不一样的。/雾

### 直接上式子吧：

$$

\begin{aligned}

&\sum_{i=1}^{n}\sum_{j=1}^{m}\operatorname{lcm}(i,j)\\

=&\sum_{i=1}^{n}\sum_{j=1}^{m}\dfrac{i\times j}{\gcd(i,j)}\\

=&\sum_{G=1}^{}\dfrac{1}{G}\sum_{i=1}^{n}\sum_{j=1}^{m}i\times j\times [G=\gcd(i,j)]\\

\end{aligned}

$$

然后对于右边那一部分，我们再给他处理一下，显然有莫反的套路：

$$

\begin{aligned}

&f(G)=\sum_{i=1}^{n}\sum_{j=1}^{m}i\times j\times [G=\gcd(i,j)]\\

&F(G)=\sum_{G|d}^{}f(d)=\sum_{i=1}^{n}\sum_{j=1}^{m}i\times j\times [G|\gcd(i,j)]=(\sum_{i=1}^{n}i\times [G|i])\times (\sum_{j=1}^{m}j\times [G|j])\\

&f(G)=\sum_{G|d}^{}\mu(\dfrac{d}{G})F(d)=\sum_{G|d}^{}\mu(\dfrac{d}{G})(\sum_{i=1}^{n}i\times [d|i])\times (\sum_{j=1}^{m}j\times [d|j])

\end{aligned}

$$

所以最后就是

$$

\begin{aligned}

&\sum_{G=1}^{}\dfrac{1}{G}\sum_{G|d}^{}\mu(\dfrac{d}{G})(\sum_{i=1}^{n}i\times [d|i])\times (\sum_{j=1}^{m}j\times [d|j])\\

\end{aligned}

$$

我们发现 $20101009\in \text{Prime}$，所以就可以求 $G^{-1}$ 了，后面两个括号里面的是等差数列，可以 $O(1)$ 求出。然后暴力是 $O(g\ln g)$，其中 $g$ 是这里的 $G$ 的枚举范围。这样的时间是可以 AC 此题的，但是好像卡我常数。

~~那如果不是质数怎么办？太菜了不会……~~

### 拓展：

如果将 $i$ 改成 $a_i$，$j$ 改成 $b_j$，其实也差不多：

$$

\begin{aligned}

\sum_{G=1}^{}\dfrac{1}{G}\sum_{G|d}^{}\mu(\dfrac{d}{G})(\sum_{i=1}^{n}a_i\times [d|a_i])\times (\sum_{j=1}^{m}b_j\times [d|b_j])

\end{aligned}

$$

后面两个括号预处理 $O(n\ln n+m\ln m)$，剩下暴力就是 $O(g\ln g)$。

---

## 作者：qwaszx (赞：1)

~~看到没有写杜教筛的十分开心.~~

$n,m\leq 1000?$

我会求$lcm$!

$n,m\leq 10000000?$

首先一定可以套上[这里](https://www.luogu.org/blog/qwaszx/ru-men-fan-yan-tao-lu#)的做法.

不过还是来推一遍(跳跃性可能略大，详细步骤请看上面的链接).以下除法均向下取整.不失一般性，设$n\leq m$，那么

$\begin{array}{lcc}\sum\limits_{i=1}^n\sum\limits_{j=1}^m lcm(i,j)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m\dfrac{ij}{\gcd(i,j)}\\=\sum\limits_{d=1}^n\frac{1}{d}\sum\limits_{i=1}^n\sum\limits_{j=1}^mij[\gcd(i,j)=d]\\=\sum\limits_{d=1}^nd\sum\limits_{i=1}^{\frac{n}{d}}\sum\limits_{j=1}^\frac{m}{d}ij[gcd(i,j)=1]\\=\sum\limits_{d=1}^nd\sum\limits_{k}\mu(k)\sum\limits_{i=1}^\frac{n}{d}\sum\limits_{j=1}^\frac{m}{d}ij[k|i][k|j]\\=\sum\limits_{d=1}^nd\sum\limits_{k=1}^\frac{n}{d}\mu(k)k^2\sum\limits_{i=1}^\frac{n}{kd}\sum\limits_{j=1}^\frac{m}{kd}ij\end{array}$

设$S(n)=\sum\limits_{i=1}^ni=\dfrac{n(n+1)}{2}$，那么可以写成

$\sum\limits_{d=1}^nd\sum\limits_{k=1}^\frac{n}{d}\mu(k)k^2S(\frac{n}{kd})S(\frac{m}{kd})$

如果我们再设一个$F(n,m)=\sum\limits_{k=1}^n\mu(k)k^2S(\frac{n}{k})S(\frac{m}{k})$，那么显然$F(n,m)$可以预处理$\mu$后在$O(\sqrt{n})$时间内数论分块算出来

原式可以写成$\sum\limits_{d=1}^ndF(\frac{n}{d},\frac{m}{d})$也可以数论分块.

总的复杂度其实是$O(\sum\limits_{i=1}^{\sqrt{n}}\sqrt{i}+\sum\limits_{i=1}^{\sqrt{n}}\sqrt{\frac{n}{i}})=O(n^\frac{3}{4})$

但是要预处理$\mu$，所以是$O(n)$的.

$n,m\leq 1000000,T$组询问，$T\leq 10000?$

回到设$F$之前的那个位置，换一个角度.

令$T=kd$，枚举$T$，那么一定有$d|T$

原式$=\sum\limits_{T=1}^nS(\frac{n}{T})S(\frac{m}{T})\sum\limits_{d|T}d\mu(\frac{T}{d})\left(\frac{T}{d}\right)^2=\sum\limits_{T=1}^nS(\frac{n}{T})S(\frac{m}{T})\sum\limits_{d|T}Td\mu(d)$

那么我们只需要预处理$\sum\limits_{d|T}Td\mu(d)$这个东西即可做到$\sqrt{n}$回答一个询问.

怎么预处理呢?显然可以直接$O(n\log n)$，但是我们还是考虑线筛.

先把$T$拿出来，然后思考$\mu$的意义.我们只需要考虑$d$无平方因子的情况.如果$n=\prod p_i$，那么$\sum\limits_{d|T}d\mu(d)=1-\sum p_i+\sum p_ip_j-\cdots$.经过一番思考我们可以发现这个式子$=\prod(1-p_i)$.(每个质因子有取和不取两种选择，并且如果取就会有一个$-1$乘上去).于是我们就可以快乐线筛了.

```cpp
void make(int n)
{
	f[1]=p[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!p[i])prime[++cnt]=i,f[i]=i*(1LL-i);
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			int x=i*prime[j];p[x]=1;
			if(i%prime[j])f[x]=f[i]*prime[j]*(1-prime[j]);
			else f[x]=f[i]*prime[j];
		}
	}
	for(int i=2;i<=n;i++)f[i]=(f[i]+f[i-1])%mod;//处理一个前缀和
}
```

现在是$O(n+T\sqrt{n})$

单组询问，$n,m\leq 10^9?$

~~我刚才看到某个神仙写完$O(n+T\sqrt{n})$忘记了需要线筛这个事实从而认为自己做到了$O(\sqrt{n})$~~

显然杜教筛了.设$f(n)=n\sum\limits_{d|n}d\mu(d)$，我们需要杜教筛出它的前缀和.

换一换形式我们得到$f(n)=\sum\limits_{d|n}d^2\mu(d)\frac{T}{d}$，即$f(n)=(id^2\cdot \mu)\ast id$.(定义$f\cdot g(n)=g(n)g(n)$)

我们来试试找一个$g$使得$f\ast g$和$g$的前缀和都可以快速计算.因为$(id^k\cdot\mu)\ast id^k=\epsilon$，所以我们取$g=id^2$，于是$f\ast g=id$

杜教筛就好啦.

卡了卡常数，现在是换新评测姬之后跑的最快的了(

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define mod 20101009
#define INF 1000000000000000000LL
#define inv2 10050505
#define inv6 16750841
using namespace std;
const int N=1e7+10;
int p[N],prime[N],cnt,mu[N],N2;
long long f[N],n,m;
struct Hash_map
{
    struct pair{long long u,v;}val[N];
    int fst[N],nxt[N],node_cnt;
    long long find(long long n)
    {
        int key=n&8388607;//秘技·手写哈希表·模数2的幂
        for(int i=fst[key];i;i=nxt[i])if(val[i].u==n)return val[i].v;
        return 1e18;
    }
    void ins(long long u,long long v)
    {
        int key=u&8388607;
        val[++node_cnt]=(pair){u,v},nxt[node_cnt]=fst[key],fst[key]=node_cnt;
    }
}mpf;
void make(int n)
{
    f[1]=p[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!p[i])prime[++cnt]=i,f[i]=i*(1LL-i);
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
        {
            int x=i*prime[j];p[x]=1;
            if(i%prime[j])f[x]=f[i]*f[prime[j]];
            else {f[x]=f[i]*prime[j],mu[x]=0;break;}
        }
    }
    for(int i=2;i<=n;i++)f[i]=(f[i]%mod+f[i-1]+mod)%mod;
}
long long S(long long n){return n*(n+1)%mod*inv2%mod;}
long long S2(long long n){return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;}
long long Sf(long long n)
{
    if(n<=N2)return f[n];
    long long x=mpf.find(n);
    if(x!=INF)return x;
    long long ans=S(n);long long lstans=1;//这里记录上一次的答案来避免重复计算.大约能快那么一点点???
    for(long long i=2,lt;i<=n;i=lt+1)
    {
        long long fn=n/i;lt=n/fn;long long tmp=S2(lt);
        ans-=(tmp-lstans)*Sf(fn)%mod;
        lstans=tmp;
    }
    ans=(ans%mod+mod)%mod;mpf.ins(n,ans);return ans;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    if(n>m)swap(n,m);N2=pow(n,0.7)+1;make(N2);
    long long ans=0;long long lstans=0;
    for(int i=1,lt;i<=n;i=lt+1)
    {
        int fn=n/i,fm=m/i;lt=min(n/fn,m/fm);
        long long tmp=Sf(lt);//同上
        ans=(ans+(tmp-lstans)*S(fn)%mod*S(fm)%mod)%mod;
        lstans=tmp;
    }
    cout<<(ans+mod)%mod<<endl;
}
```

~~真是快乐的卡常数题~~

---

## 作者：Jμdge (赞：1)

这题代码为什么这么短！（好吧数论题都短）


总之就是不断推柿子...

### $[i,j]$ 表示 $i$ 和 $j$ 的 $lcm$ 

### $(i,j)$ 表示 $i$ 和 $j$ 的 $gcd$ 

### $[\text{表达式}]$ 表示 表达式成立时取 1  ，否则为 0  

$\sum$ 的边界默认下取整，如 $\sum_{i=1}^{n/d}$ 中的 $n/d$ 默认为 $\lfloor \dfrac{n}{d} \rfloor$

并且强制 $n$ 小于 $m$ （输入大于的话 $swap$ 一下不影响答案）

然后下面的过程会推的较慢，一边初学者能看懂（woc 初学数论切国籍题...）...大佬当然是一目了然咯

$$ANS=\sum_{i=1}^n\sum_{j=1}^m[i,j]$$
$$=\sum_{i=1}^n\sum_{j=1}^m\dfrac{i\times j}{(i,j)}$$
$$=\sum_{d=1}^n \dfrac{1}{d}\sum_{d|i}^n\sum_{d|j}^m i\times j[(i,j)=1]$$
$$=\sum_{d=1}^n \dfrac{1}{d} \times d^2\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} i\times j[(i,j)=1]$$

$$=\sum_{d=1}^n d\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} i\times j [(i,j)=1]$$
>>反演一下，将表达式替换成 $μ$
$$=\sum_{d=1}^n d\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} i\times j \sum_{k|i,k|j}\mu(k)$$


$$=\sum_{d=1}^n d\sum_{k=1}^{n/d}\mu(k)\sum_{k|i}^{n/d}\sum_{k|j}^{m/d} i\times j $$


$$=\sum_{d=1}^n d\sum_{k=1}^{n/d}\mu(k)\times k^2\sum_{i=1}^{n/(kd)}\sum_{j=1}^{m/(kd)} i\times j $$
$$=\sum_{d=1}^n d\sum_{k=1}^{n/d}\mu(k)\times k^2\sum_{i=1}^{n/(kd)}\sum_{j=1}^{m/(kd)} i\times j $$

>>我们发现后面两个 $\sum$ 可以 $O(1)$ 用公式表示

$$=\sum_{d=1}^n d\sum_{k=1}^{n/d}\mu(k)\times k^2 \times \dfrac{ \lfloor \dfrac{n}{kd}\rfloor \times(\lfloor \dfrac{n}{kd}\rfloor +1)}{2} \times \dfrac{ \lfloor \dfrac{m}{kd}\rfloor \times(\lfloor \dfrac{m}{kd}\rfloor +1)}{2}  $$

>>为了让表达式清晰一点，我们令 $g(n)=\dfrac{n\times (n+1)}{2}$，然后用 g 带入原式

$$=\sum_{d=1}^n d\sum_{k=1}^{n/d}\mu(k)\times k^2 \times g(\lfloor\dfrac{n}{kd}\rfloor) \times g(\lfloor\dfrac{m}{kd}\rfloor)  $$

那么我们发现这个式子的后半部分可以单独拎出来

就是令 $f(n)= \sum_{k=1}^{n}\mu(k)\times k^2 \times g(\lfloor\dfrac{n}{k}\rfloor) \times g(\lfloor\dfrac{m}{k}\rfloor)$

这玩意儿可以数论分块解，$O(\sqrt{n})$的复杂度

求出来之后带入进原式子就是：

$$ANS=\sum_{d=1}^nd\times f(\lfloor n/d\rfloor)$$

然后发现这玩意儿还是可以数论分块解，$O(\sqrt{n})$ 的复杂度

然后随便口胡一下发现复杂度没毛病，据说总的复杂度是 $O(n+m)$ 吧，蒟蒻不会推，大佬教教我...




当然这代码里面的细节好多的说（每次做这种数论题我都是小错误频发）


所以总结一下易错点（多以本人为反面教材，大佬不喜勿喷）：

1. $ADD(a,b)$ 中的 $b$ 别忘了取模

2. 注意精度不能爆，有事没事加个 $1ll$

3. 数论分块右区间贡献减左区间贡献别就丢个左（右）区间在那儿就完事儿

4. 预处理别出锅不然得完

5. 有两个变量（$n$ 和 $m$）输入进来的， $r$ 别忘了对 $n/(n/l)$ 和 $m/(m/l)$ 取 $Min$ 而不是直接赋成 $n/(n/l)$ 

第一个总是会犯...所以写完那一行就得检查一下

第二个不怎么犯吧...感觉精度问题自己还是会特别关注的

第三个就是犯二了...（ $I'm$ 中二病患者→_→ 莫名骄傲...）

第四个板子熟的话不会有毛病吧反正我**目前**还没出过事儿


第五个可能是杜教筛或者输入只有一个 $n$  的数论题打多了...



```
//by Judge
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=20101009;
const int M=1e7+3; 
typedef int arr[M];
int n,m,cnt; arr v,p,mu;
inline void prep(int n){ v[1]=mu[1]=1;
	for(int i=2;i<=n;++i){ if(!v[i]) p[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=n;++j){ v[i*p[j]]=1;
			if(!(i%p[j])) break; mu[i*p[j]]=-mu[i];
		} mu[i]=(mu[i-1]+1ll*mu[i]*i*i%mod+mod)%mod;
	}
}
inline void ADD(int& a,int b){a+=a+b>=mod?b-mod:b;}
inline int sum1(int x){return 1ll*x*(x+1)/2%mod;}
inline int Min(int a,int b){return a<b?a:b;}
inline int calc(int n,int m){ int ans=0;
	for(int l=1,r;l<=n;l=r+1) r=Min(n/(n/l),m/(m/l)),
		ADD(ans,1ll*(mu[r]-mu[l-1]+mod)*sum1(n/l)%mod*sum1(m/l)%mod); return ans;
}
int main(){ cin>>n>>m; if(n>m) swap(n,m); prep(m); int ans=0;
	for(int l=1,r;l<=n;l=r+1) r=Min(n/(n/l),m/(m/l)),
		ADD(ans,1ll*(sum1(r)-sum1(l-1)+mod)*calc(n/l,m/l)%mod);
	return !printf("%d\n",ans); 
}
```


---

## 作者：Great_Influence (赞：1)

### 莫比乌斯反演

~~推式子推死我了~~


首先，原题要求：


$\sum\limits_{i=1}^n\sum\limits_{j=1}^m lcm(i,j)$


然后开始化式子。



$ans=\sum\limits_{i=1}^n\sum\limits_{j=1}^m \frac{ij}{\gcd(i,j)}$


$=\sum\limits_{d=1}^{\min(n,m)}d\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d} ij[\gcd(i,j)==1]$



设
$f(x,d)=\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}ij[gcd(i,j)==x]$，

$g(x,d)=\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}ij[gcd(i,j)|x]$，那么


$f(1,D)=\sum_{d=1}^{\min(n/D,m/D)}\mu(d)g(d)$


$g(x,D)=x^2\sum\limits_{i=1}^{\lfloor\frac{n/D}{x}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m/D}{x}\rfloor}ij$


所以

$ans=\sum_{D=1}^{\min(n,m)}D\sum\limits_{d=1}^{\min(n/D,m/D)}\mu(d)d^2\sum\limits_{i=1}^{\lfloor\frac{n/D}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m/D}{d}\rfloor}ij$


$=\sum\limits_{D=1}^{\min(n,m)}D\sum_{d=1}^{\min(n/D,m/D)}\mu(d)d^2\frac{(1+\lfloor\frac{n/D}{d}\rfloor)(1+\lfloor\frac{m/D}{d}\rfloor)\lfloor\frac{n/D}{d}\rfloor\lfloor\frac{m/D}{d}\rfloor}{4}$


这样直接算时间复杂度为$O(n^2)$，利用整除分块优化至$O(n\sqrt{n})$。


代码：

```cpp
#include<bits/stdc++.h>
#include<cctype>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}
static int n,m;
const int mod=20101009ll;
const int MAXN=1e7+7;
static int mu[MAXN];
static int is[MAXN],pri[MAXN],e;
void predone(int x)
{
    static int j;
    Rep(i,2,x)
    {
        if(!is[i])pri[++e]=i,mu[i]=-1;
        For(j,1,e)
        {
            if(i%pri[j]==0||i*pri[j]>x)break;
            is[i*pri[j]]=true;
            mu[i*pri[j]]=-mu[i];
        }
        if(i%pri[j]==0&&i*pri[j]<=x)
            is[i*pri[j]]=true,mu[i*pri[j]]=0;
    }
    mu[1]=1;
    Rep(i,1,x)mu[i]=(mu[i-1]+1ll*mu[i]*i*i%mod+mod)%mod;
}
void init()
{
    read(n);read(m);
    predone(min(n,m));
}
static long long ans,sum;
inline int power(int a,int b)
{
    static int sum;
    for(sum=1;b;b>>=1,a=1ll*a*a%mod)if(b&1)
        sum=1ll*sum*a%mod;
    return sum;
}
void solve()
{
    static int j,last,N,M;
    static int div4=power(4,mod-2);
    Rep(i,1,min(n,m))
    {
        sum=0ll;
        N=n/i;M=m/i;
        for(j=1;j<=min(N,M);j=last+1)
        {
            last=min(N/(N/j),M/(M/j));
            sum+=1ll*(mu[last]-mu[j-1])%mod
                *(1+N/j)%mod*(1+M/j)%mod*(N/j)%mod*(M/j)%mod*div4%mod;
            sum=(sum%mod+mod)%mod;
        }
        ans=(ans+sum*i%mod+mod)%mod;
    }
    printf("%lld\n",ans);
}
int main(void){
    file();
    init();
    solve();
    return 0;
}
```

---

## 作者：feecle6418 (赞：0)

我有一种玄学复杂度的做法。

约定：$[y]$ 当 $y$ 为真时为 $1$，否则为 $0$。

$$\sum_{i=1}^n\sum_{j=1}^m \frac{ij}{\gcd(i,j)}$$

$$=\sum_d\frac{1}{d}\sum_{i=1}^n\sum_{j=1}^mij[\gcd(i,j)=d]$$

$$=\sum_dd\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}ij[\gcd(i,j)=1]$$

$$=\sum_dd\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}ij\sum_p\mu(p)[p|i][p|j]$$

$$=\sum_dd\sum_pp^2\mu(p)\sum_{i=1}^{\lfloor\frac{n}{dp}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{dp}\rfloor}ij$$

令 $T=dp$，$f(i,j)=\sum_{x=1}^i\sum_{y=1}^jxy=\frac{x(x+1)y(y+1)}{4}$，原式

$$=\sum_TTf(\lfloor\frac{n}{T}\rfloor,\lfloor\frac{m}{T}\rfloor)\sum_{p|T}p\mu(p)$$

到这里就可以做了（后面那一坨可以筛出来）。由于单组询问，因此不用整除分块。

但是直接筛是 $O(n\log n)$ 的，会 T。加上一个优化：若 $\mu(i)=0$，则直接跳过 $i$，就能过了。但跑得很慢。

代码：

```cpp
#include<bits/stdc++.h>
#define MaxN 10000005
#define mod 20101009
using namespace std;
int miu[MaxN],prime[MaxN],vst[MaxN];
long long f[MaxN];
void Mobius(int n){
	miu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vst[i]){
			prime[++prime[0]]=i;
			miu[i]=-1;
		}
		for(int j=1;j<=prime[0]&&i*prime[j]<=n;j++){
			vst[i*prime[j]]=1;
			if(i%prime[j])miu[i*prime[j]]=-miu[i];
			else {
				miu[i*prime[j]]=0;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!miu[i])continue;
		for(int j=i;j<=n;j+=i)f[j]+=miu[i]*i;
	}
	for(int i=1;i<=n;i++)f[i]=(f[i]%mod+mod)%mod;
}
long long F(int x,int y){
	return 1ll*x*(x+1)%mod*((mod+1)/2)%mod*y%mod*(y+1)%mod*((mod+1)/2)%mod;
}
int main(){
	Mobius(10000000);
	int n,m,sum=0;
	cin>>n>>m;
	for(int i=1;i<=min(n,m);i++)sum=(sum+1ll*i*f[i]%mod*F(n/i,m/i)%mod)%mod;
	cout<<sum<<endl;
    return 0;
}
```

---

## 作者：arfa (赞：0)

有点难度的题目。

一眼看到 $\gcd(i,j)$ 就用了 $\phi$ , 结果死了。

用莫比乌斯函数套进去搞一搞先 : 

$$\begin{aligned}  & \sum\limits^n_{i=1} \sum\limits^m_{j=1} \text{lcm}(i,j) \\ = &\sum\limits^n_{i=1} \sum\limits^m_{j=1} \frac {ij}{\gcd(i,j)} \\ = & \sum\limits^{\min\{n,m\}}_{k=1} \sum\limits^n_{i=1} \sum\limits^m_{j=1} \frac{ij}{k} [\gcd(i,j)=k] \\ = & \sum\limits^{\min\{n,m\}}_{k=1} \sum\limits^{\left\lfloor \frac n k \right\rfloor}_{i=1} \sum\limits^{\left\lfloor \frac m k \right\rfloor}_{j=1} \frac{(ik)(jk)}{k} [\gcd(i,j)=1] \\ = & \sum\limits^{\min\{n,m\}}_{k=1} \sum\limits^{\left\lfloor \frac n k \right\rfloor}_{i=1} \sum\limits^{\left\lfloor \frac m k \right\rfloor}_{j=1} ijk \sum\limits_{d|\gcd(i,j)}\mu(d) \\ = & \sum\limits^{\min\{n,m\}}_{k=1} \sum\limits^{\min\{\left\lfloor \frac n k \right\rfloor,\left\lfloor \frac m k \right\rfloor\}}_{d=1}  \mu(d) \sum\limits^{\left\lfloor \frac n k \right\rfloor}_{i=1} \sum\limits^{\left\lfloor \frac m k \right\rfloor}_{j=1} ijk [d|i] [d|j] \\ = & \sum\limits^{\min\{n,m\}}_{k=1} \sum\limits^{\min\{\left\lfloor \frac n k \right\rfloor,\left\lfloor \frac m k \right\rfloor\}}_{d=1} \mu(d) \sum\limits^{\left\lfloor \frac n {kd} \right\rfloor}_{i=1} \sum\limits^{\left\lfloor \frac m {kd} \right\rfloor}_{j=1} ijkd^2  \\ = & \sum\limits^{\min\{n,m\}}_{k=1} k \sum\limits^{\min\{\left\lfloor \frac n k \right\rfloor,\left\lfloor \frac m k \right\rfloor\}}_{d=1} d^2\mu(d)  \left( \sum\limits^{\left\lfloor \frac n {kd} \right\rfloor}_{i=1} i \right)  \left( \sum\limits^{\left\lfloor \frac m {kd} \right\rfloor}_{j=1} j \right) \\ = & \sum\limits^{\min\{n,m\}}_{T=1} \left( \sum\limits^{\left\lfloor \frac n T \right\rfloor}_{i=1} i \right)  \left( \sum\limits^{\left\lfloor \frac m T \right\rfloor}_{j=1} j \right) \sum\limits_{d|T} d^2\mu(d) \frac{T}{d} \\ = & \sum\limits^{\min\{n,m\}}_{T=1} T \left( \sum\limits^{\left\lfloor \frac n T \right\rfloor}_{i=1} i \right)  \left( \sum\limits^{\left\lfloor \frac m T \right\rfloor}_{j=1} j \right) \sum\limits_{d|T} d\mu(d) \end{aligned}$$

我们发现如果 $T\sum\limits_{d|T} d\mu(d)$ 可以进行预处理的话那么这个式子就是 $O(n^{\frac{1}{2}})$ 的。

我们设 $\text F(T)=\sum\limits_{d|T} d\mu(d)$ , 是一个积性函数 : $\mu$ 是积性函数 , $\sum\limits_{d|T}=\sum\limits_{x|T,y|T,x \perp y} xy$ , 得证。

那么我们就可以知道 $\text F(Tp)=\text F(T) \times \text F(p)$ ( $p \in prime$ ) 。我们又可以知道 $\text F(p)=1+(-p)=1-p$ , 注意到这个有质数贡献的导向 , 所以可以欧拉筛。

最后记得把 $T$ 乘进去并且取前缀和。时间复杂度 $O(n+n^{\frac{1}{2}})$。

```pascal
Uses math;

Const
    total=10000000+10;
    modn=20101009;

var
    isprime:array[-1..total] of boolean;
    prime:array[-1..total] of longint;
    incea:array[-1..total] of int64;
    i,j,n,m:longint;
    ans:int64;

function Square(n:longint):longint; begin exit(n*(n+1) >> 1 mod modn); end;

procedure Incea_make(total:longint);
var i,j,k,tail:longint;
begin
   incea[1]:=1; tail:=0;
   for i:=2 to total do
   begin
        if isprime[i]=False then begin inc(tail); prime[tail]:=i; incea[i]:=1-i; end;
        for j:=1 to tail do
        begin
            if prime[j]*i>total then break;
            isprime[prime[j]*i]:=True;
            if (i mod prime[j]=0) then begin incea[prime[j]*i]:=incea[i] mod modn; break; end
            else incea[prime[j]*i]:=incea[i]*incea[prime[j]] mod modn;
        end;
   end;
   for i:=1 to total do incea[i]:=(incea[i]*i mod modn+incea[i-1]) mod modn;
end;

begin
    read(n,m); Incea_make(max(m,n)+1);
    i:=1; j:=0;
    repeat
        j:=min(n div (n div i),m div (m div i));
        inc(ans,(Square(n div i)*Square(m div i) mod modn)*(incea[j]-incea[i-1]) mod modn);
        ans:=ans mod modn; i:=j+1;
    until i>min(n,m);
    writeln((ans+modn) mod modn);
end.
```

**坑点 : 最后记得 $(ans+modn) \mod modn$ !! 不然爆负数**

---

## 作者：chihik (赞：0)

$$\sum_{i=1}^n\sum_{j=1}^mlcm(i,j)$$

$$\sum_{i=1}^n\sum_{j=1}^m\frac{i*j}{gcd(i,j)}$$

$$\sum_{d=1}^{min(n,m)}\sum_{i=1}^n\sum_{j=1}^m [gcd(i,j)=d] * \frac{i*j}{d}$$

$$\sum_{d=1}^{min(n,m)}\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor}[gcd(i,j)=1]*i*j*d$$

$$\sum_{d=1}^{min(n,m)}\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor}\sum_{k|gcd(i,j)}\mu(k)*i*j*d$$

$$\sum_{d=1}^{min(n,m)}\sum_{k=1}^{min(\lfloor \frac{n}{d} \rfloor,\lfloor \frac{m}{d} \rfloor)}\mu(k)*k^2*d\sum_{i=1}^{\lfloor \frac{n}{dk} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{dk} \rfloor}i*j$$

$$\sum_{d=1}^{min(n,m)}d\sum_{k=1}^{min(\lfloor \frac{n}{d} \rfloor,\lfloor \frac{m}{d} \rfloor)}\mu(k)*k^2*(\frac{\lfloor \frac{n}{dk} \rfloor*(\lfloor \frac{n}{dk} \rfloor+1)*\lfloor \frac{m}{dk} \rfloor*(\lfloor \frac{m}{dk} \rfloor+1)}{4})$$

内外进行两次数论分块，可以做到$\Theta(\sqrt n * \sqrt n~)=\Theta(n)$求解

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#define Mod 20101009

const int MAXN = 10000000;
int n , m , f[ MAXN + 5 ];

int k , prime[ MAXN + 5 ] , mu[ MAXN + 5 ];
bool vis[ MAXN + 5 ];
void sieve( ) {
    mu[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		if( !vis[ i ] ) {
			prime[ ++ k ] = i;
			mu[ i ] = -1;
		}
		for( int j = 1 ; j <= k && 1ll * i * prime[ j ] <= MAXN ; j ++ ) {
			vis[ i * prime[ j ] ] = 1;
			if( i % prime[ j ] == 0 ) break;
            mu[ i * prime[ j ] ] = -mu[ i ];
		}
	}
    for( int i = 1 ; i <= MAXN ; i ++ )
        f[ i ] = ( f[ i - 1 ] + 1ll * mu[ i ] % Mod * i % Mod * i % Mod ) % Mod;
}

int Quick_pow( int x , int po ) {
    int Ans = 1;
    while( po ) {
        if( po % 2 )
            Ans = 1ll * Ans * x % Mod;
        x = 1ll * x * x % Mod;
        po /= 2;
    }
    return Ans;
}
int inv( int x ) {
    return Quick_pow( x , Mod - 2 );
}

int Get( int n1 , int m1 ) {
    int d1 = min( n1 , m1 ) , Ans = 0;
    for( int l = 1 , r ; l <= d1 ; l = r + 1 ) {
        r = min( n1 / ( n1 / l ) , m1 / ( m1 / l ) );
        Ans = ( Ans + 1ll * ( f[ r ] - f[ l - 1 ] + Mod ) % Mod * ( 1ll * ( n1 / l ) * ( n1 / l + 1 ) % Mod * ( m1 / l ) % Mod * ( m1 / l + 1 ) % Mod ) % Mod * inv( 4 ) % Mod ) % Mod;
    }
    return Ans;
}
int solve( int n , int m ) {
    int Ans = 0 , d = min( n , m );
    for( int l = 1 , r ; l <= d ; l = r + 1 ) {
        r = min( n / ( n / l ) , m / ( m / l ) );
        Ans = ( Ans + 1ll * Get( n / l , m / l ) * ( l + r ) * ( r - l + 1 ) / 2 ) % Mod;
    }
    return Ans;
}

int main( ) {
    sieve( );
    scanf("%d %d",&n,&m);
    printf("%d\n",solve( n , m ));
    return 0;
}
```


---

## 作者：Sangber (赞：0)

### 题目描述
求(对 $20101009$ 取模，$n,m\le10^7$ )
$$\sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j)$$

----
### 大体思路
直接上来推式子。。。  
（因为不能用aligned所以写的不太好看。。。）
$$\sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j)$$
$$=\sum_{i=1}^n\sum_{j=1}^m\frac{i\times j}{\gcd(i,j)}$$
$$=\sum_{i=1}^n\sum_{j=1}^m\sum_{d|\gcd(i,j)}\frac{i\times j}{d}$$
$$=\sum_{d=1}^{\min(n,m)}\times d\times\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor}[\gcd(i,j)=1]\times i\times j$$
把式子后面那一大堆设为 $sum(n,m)$ ：
$$sum(n,m)=\sum_{i=1}^n\sum_{j=1}^m[\gcd(i,j)=1]\times i\times j$$
考虑化简一下 $sum$ :
$$sum(n,m) = \sum_{i=1}^n\sum_{j=1}^m[\gcd(i,j)=1]\times i\times j$$
$$=\sum_{i=1}^n\sum_{j=1}^m\sum_{d|\gcd(i,j)}\mu(d)\times i\times j$$
$$=\sum_{d=1}^{\min(n,m)}\mu(d)\times d^2\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor}i\times j$$
可以发现 $sum$ 后面那一大堆(设为 $g(n,m)$ )可以 $O(1)$ 求：
$$g(n,m)=\sum_{i=1}^n\sum_{j=1}^m i\times j$$
$$=\frac{n\times(n+1)}{2}\times \frac{m\times(m+1)}{2}$$
那么 $sum(n,m)$ 可以化为：
$$sum(n,m)=\sum_{d=1}^{\min(n,m)}\mu(d)\times d^2\times g(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)$$
这个可以数论分块 $\lfloor\frac{n}{\lfloor\frac{n}{d}\rfloor}\rfloor$ 求。  
再回到定义 $sum$ 的地方，那么：
$$Ans=\sum_{d=1}^{\min(n,m)}\times d\times sum(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)$$
好像这个还是可以数论分块 $QwQ$  
至此这道题就解决了。

----
### 细节注意事项
+ $long\ long$一定要开呀。
+ 不要写挂呀！！！

----
### 参考代码
```cpp
/*--------------------------------
  Code name: crash.cpp
  Author: The Ace Bee
  This code is made by The Ace Bee
--------------------------------*/
#include <cstdio>
#define rg register
#define int long long 
#define fileopen(x)								\
	freopen(x".in", "r", stdin);				\
	freopen(x".out", "w", stdout);
#define fileclose								\
	fclose(stdin);								\
	fclose(stdout);
const int mod = 20101009;
const int MAXN = 10000010;
inline int min(int a, int b) { return a < b ? a : b; }
inline int read() {
	int s = 0; bool f = false; char c = getchar();
	while (c < '0' || c > '9') f |= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
	return f ? -s : s;
}
int vis[MAXN], mu[MAXN];
int num, pri[MAXN], sum[MAXN];
inline void seive() {
	mu[1] = 1;
	for (rg int i = 2; i < MAXN; ++i) {
		if (!vis[i]) mu[i] = -1, pri[++num] = i;
		for (rg int j = 1; j <= num && i * pri[j] < MAXN; ++j) {
			vis[i * pri[j]] = 1;
			if (i % pri[j]) mu[i * pri[j]] = - mu[i];
			else { mu[i * pri[j]] = 0; break; }
		}
	}
	for (rg int i = 1; i < MAXN; ++i)
		sum[i] = (sum[i - 1] + 1ll * i * i % mod * (mu[i] + mod) % mod) % mod;
}
inline int g(int n, int m)
{ return 1ll * n * (n + 1) / 2 % mod * (m * (m + 1) / 2 % mod) % mod; }
inline int f(int n, int m) {
	int res = 0;
	for (rg int i = 1, j; i <= min(n, m); i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		res = (res + 1ll * (sum[j] - sum[i - 1] + mod) * g(n / i, m / i) % mod) % mod;
	}
	return res;
}
inline int solve(int n, int m) {
	int res = 0;
	for (rg int i = 1, j; i <= min(n, m); i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		res = (res + 1ll * (j - i + 1) * (i + j) / 2 % mod * f(n / i, m / i) % mod) % mod;
	}
	return res;
}
signed main() {
//	fileopen("crash");
	seive();
	int n = read(), m = read();
	printf("%lld\n", solve(n, m));
//	fileclose;
	return 0;
}

```
**完结撒花$qwq$**

---

## 作者：_ctz (赞：0)

[安利blog](https://ctz45562.github.io/2019/07/10/洛谷-P1829-国家集训队-Crash的数字表格/)

[传送门](https://www.luogu.org/problemnew/show/P1829)

小学数论知识：$lcm(i,j)=\dfrac{ij}{gcd(i,j)}$

以下规定$n<m$。

$\sum\limits_{i=1}^n\sum\limits_{j=1}^mlcm(i,j)$

$=\sum\limits_{i=1}^n\sum\limits_{j=1}^m\dfrac{ij}{gcd(i,j)}$

套路枚举$gcd$：

$=\sum\limits_{d=1}^n\sum\limits_{i=1}^n\sum\limits_{j=1}^m\dfrac{ij[gcd(i,j)=d]}{d}$

套路枚举$d$的倍数：

$=\sum\limits_{d=1}^n\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}ijd[gcd(i,j)=1]$

$=\sum\limits_{d=1}^n\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}ijd\sum\limits_{a|gcd(i,j)}\mu(a)$

$=\sum\limits_{d=1}^nd\sum\limits_{a=1}^{\lfloor\frac{n}{d}\rfloor}\mu(a)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{m}{d}\rfloor}ij[a|i][a|j]$

套路枚举$a$的倍数：

$=\sum\limits_{d=1}^nd\sum\limits_{a=1}^{\lfloor\frac{n}{d}\rfloor}\mu(a)\sum\limits_{i=1}^{\frac{\lfloor\frac{n}{d}\rfloor}{a}}ia\sum\limits_{j=1}^{\frac{\lfloor\frac{m}{d}\rfloor}{a}}ja$

$=\sum\limits_{d=1}^nd\sum\limits_{a=1}^{\lfloor\frac{n}{d}\rfloor}\mu(a)a^2\sum\limits_{i=1}^{\frac{\lfloor\frac{n}{d}\rfloor}{a}}i\sum\limits_{j=1}^{\frac{\lfloor\frac{m}{d}\rfloor}{a}}j$

设$g(n)=\sum\limits_{i=1}^ni$（就是自然数前$n$项和）,$f(n,m)=\sum\limits_{i=1}^n\mu(i)i^2g(\lfloor\dfrac{n}{i}\rfloor)g(\lfloor\dfrac{m}{i}\rfloor)$

这个$f(n,m)$显然可以预处理$\mu(i)i^2$后整除分块。

我们求的就成了$\sum\limits_{d=1}^ndf(\lfloor\dfrac{n}{d}\rfloor,\lfloor\dfrac{m}{d}\rfloor)$

又可以整除分块了。

整除分块套整除分块复杂度是$O(n^{\frac{3}{4}})$的。

然后发现了一个有趣的东西：

暴力计算$f(n,m)$是$O(n)$的。

设$F(n)$为$\lfloor\dfrac{n}{i}\rfloor(i\le n)$所有不同取值的和，它近似于在$f(n,m)$不整除分块时的整个算法复杂度。

经过计算在$F(1e7)\approx 9e7$。试着改了一下不吸氧就过了。。。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 10000001
#define inf 0x3f3f3f3f

const int mod = 20101009;

using namespace std;

inline int read(){
    int x=0,y=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return y?-x:x;
}
int mu[maxn],sum[maxn],psum[maxn],prime[maxn>>3],cnt;
bool is[maxn];
inline int f(int n,int m){
    if(n>m)swap(n,m);
    int ans=0;
    for(register int l=1,r;l<=n;l=r+1){
        r=min(n,min(n/(n/l),m/(m/l)));
        (ans+=1ll*(psum[r]-psum[l-1])*sum[n/l]%mod*sum[m/l]%mod)%=mod;
    }
    return ans;
}
int main(){
    mu[1]=is[1]=sum[1]=psum[1]=1;
    for(register int i=2;i<maxn;++i){
        if(!is[i])prime[++cnt]=i,mu[i]=-1;
        sum[i]=(sum[i-1]+i)%mod,psum[i]=(psum[i-1]+1ll*i*i*mu[i]%mod)%mod;
        for(register int j=1;j<=cnt&&i*prime[j]<maxn;++j){
            is[i*prime[j]]=1;
            if(i%prime[j]==0){mu[i*prime[j]]=0;break;}
            mu[i*prime[j]]=-mu[i];
        }
    }
    int n=read(),m=read(),ans=0;
    if(n>m)swap(n,m);
    for(register int l=1,r;l<=n;l=r+1){
        r=min(n,min(n/(n/l),m/(m/l)));
        (ans+=1ll*(sum[r]-sum[l-1])*f(n/l,m/l)%mod)%=mod;	
    }
    printf("%d\n",(ans+mod)%mod);
}
```



---

## 作者：GoldenPotato137 (赞：0)

蒟蒻博客：[戳我获得更好的阅读体验w](https://www.cnblogs.com/GoldenPotato/p/10312872.html)

---
# Solution

~~调到自闭，我好菜啊~~

**为了方便讨论，以下式子$m>=n$**

**为了方便书写，以下式子中的除号均为向下取整**

我们来颓柿子吧qwq

显然，题目让我们求：

$\large \sum_{i=1}^n\sum_{j=1}^m lcm(i,j)$

$lcm$没法玩，我们转到$gcd$形式：

$\large \sum_{i=1}^n\sum_{j=1}^m \frac{i*j}{gcd(i,j)}$

根据套路，我们去枚举$gcd$

$\large \sum_{i=1}^n\sum_{j=1}^m\sum_{d=1}^{n} \frac{i*j}{d}[gcd(i,j)=d]$

然后可以把$d$的和号移到前面去

$\large \sum_{d=1}^{n}\sum_{i=1}^n\sum_{j=1}^m \frac{i*j}{d}[gcd(i,j)=d]$

要让$gcd(i,j)=d$，$i,j$都必须要为$d$的倍数，我们可以将原来的$i*d,j*d$映射为$i,j$,有：

$\large \sum_{d=1}^{n}\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} {i*j}*d[gcd(i,j)=1]$

把$d$移到前面去

$\large \sum_{d=1}^{n}d\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} {i*j}[gcd(i,j)=1]$

然后我们可以套路地根据$[x=1]=\sum_{d|x}\mu(d)$这个柿子把$gcd(i,j)$处理掉：

$\large \sum_{d=1}^{n}d\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} {i*j}\sum_{k|gcd(i,j)}\mu(k)$

根据套路，我们把这种奇奇怪怪的和式变为枚举的形式

$\large \sum_{d=1}^{n}d\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} {i*j}\sum_{k=1}^{n/d}[k|gcd(i,j)]\mu(k)$

然后就可以把$k$往前提了

$\large \sum_{d=1}^{n}d\sum_{k=1}^{n/d}\sum_{i=1}^{n/d}\sum_{j=1}^{m/d} {i*j}*[k|gcd(i,j)]\mu(k)$

要有$k|gcd(i,j)$，$i,j$一定要为$k$的倍数

$\large \sum_{d=1}^{n}d\sum_{k=1}^{n/d}\sum_{i=1}^{\frac{n}{d*k}}\sum_{j=1}^{\frac{m}{d*k}} {i*j*k^2}*\mu(k)$

然后我们简单的移一下项方便处理：后面的$j$与$i$没有半毛钱关系，我们可以把它分离开来

$\large \sum_{d=1}^{n}d\sum_{k=1}^{n/d}*\mu(k)*k^2(\sum_{i=1}^{\frac{n}{d*k}}i)(\sum_{j=1}^{\frac{m}{d*k}} j)$

搞定，到这里为止，我们所有东西都可以求了。

对于前面的$d$的和式，我们可以发现当$n/d,m/d$不变的时候，后面的柿子计算出来的结果是一样的，因此我们可以$O(\sqrt n)$来整除分块掉前面那个和式。

后面的那个柿子我们可以再来一次整数除法来计算：最后面的两个和式都是等差数列，前面的$\mu(k)*k^2$可以前缀和直接计算。

总复杂度$O(\sqrt n * \sqrt n)=O(n)$

~~但是这题还有一个$O(\sqrt n)$的做法，蒟蒻太菜了不会，就不说了~~

---
# Code
**这题细节繁多，请注意多膜以防乘爆**

**预处理中的$i^2$会爆int，请注意**
```cpp
//Luogu  P1829 [国家集训队]Crash的数字表格 / JZPTAB
//Jan,23rd,2019
//莫比乌斯反演
#include<iostream>
#include<cstdio>
using namespace std;
long long read()
{
	long long x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=10000000+1000;
const int M=10000000;
const int poi=20101009;
int prime[N],cnt_p,mu[N];
bool noPrime[N];
void GetPrime(int n)
{
	noPrime[1]=true,mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(noPrime[i]==false)
			prime[++cnt_p]=i,mu[i]=-1;
		for(int j=1;j<=cnt_p and i*prime[j]<=n;j++)
		{
			noPrime[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=mu[i]*mu[prime[j]];
		}
	}
}
long long n,m,pre_mu[N];
long long f(int d)
{
	long long t_ans=0;
	for(long long l=1,r;l<=n/d;l=r+1)
	{
		r=min((n/d)/((n/d)/l),(m/d)/((m/d)/l));
		t_ans=(t_ans+(pre_mu[r]-pre_mu[l-1])*(((1+n/d/l)*(n/d/l)/2)%poi)%poi*(((1+m/d/l)*(m/d/l)/2)%poi))%poi;
	}
	return (t_ans%poi+poi)%poi;
}
int main()
{
	n=read(),m=read();
	if(n>m) swap(n,m);
	
	GetPrime(m);
	for(long long i=1;i<=m;i++)
		pre_mu[i]=((pre_mu[i-1]+mu[i]*i*i)%poi+poi)%poi;
	long long ans=0;
	for(long long l=1,r;l<=n;l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		ans=((ans+(l+r)*(r-l+1)/2%poi*f(l))%poi+poi)%poi;
	}
	
	printf("%lld",ans);
	return 0;
}

```








---

## 作者：hwk0518 (赞：0)

我原本不知这种题可以**多组**数据的。某**良心**出题人出了一道多组数据的类似题后，痛定思痛，学习了这道题的多组数据解法。

各位大佬的博客讲得很明白了，最后的式子是：

$\sum_{k=1 \to n}k\sum_{d=1 \to \frac{n}{k}}\mu{(d)}d^2f(\frac{n}{kd},\frac{m}{kd})$

发现当kd相等时很多次数论分块造成浪费，所以枚举$p=kd$，化为：

$\sum_{p=1 \to n}p*f(\frac{n}{p},\frac{m}{p})\sum_{d|p}\mu{(d)}d$

=$\sum_{p=1 \to n}f(\frac{n}{p},\frac{m}{p})\sum_{d|p}\mu{(d)}d*p$

发现$g(p)=\sum_{d|p}\mu{(d)}d$是积性函数，所以线筛求出，再乘以p。求个前缀和就可以分块了~

复杂度：$O(n+T\sqrt{n})$，其中T是询问次数。

这里有个问题，使用欧拉筛求积性函数，$i \space mod \space prime[j]=0$时如何求g的值呢？设$i=a_1^{x_1}*a_2^{x_2}*...*a_n^{x_n}$，不妨令$fac[i]=a_1^{x_1}$，$fac[i]$很容易筛出。$i \space mod \space prime[j]=0$时分情况讨论，若$fac[i*prime[j]]=i*prime[j]$，则$\mu{(i)}=0$，$fac[i*prime[j]]=fac[i]$;反之，除去$i*prime[j]$中的$fac$，即可化为两个互素数的乘积。

~~$T=1$不是随便过吗？~~

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=1e7+5;
const int M=1e7;
const int mod=20101009;

int T,n,m,prime[N],tot;
int mju[N],s[N],f[N],fac[N];
bool used[N];

namespace MATHEMATICS
{
	int add(int x,int y)
	{
		int ret=x+y;
		if(ret>=mod) ret-=mod;
		return ret;
	}
	int mi(int x,int y)
	{
		int ret=x-y;
		if(ret<0) ret+=mod;
		return ret;
	}
	
	void inc(int &x,int y)
	{
		x+=y;
		if(x>=mod) x-=mod;
	}
	void dec(int &x,int y)
	{
		x-=y;
		if(x<0) x+=y;
	}
	
	int mul(int x,int y)
	{
		return 1LL*x*y%mod;
	}
}
using namespace MATHEMATICS;

void prework()
{
	int i,j;
	fac[1]=mju[1]=used[1]=f[1]=1;
	for(i=2;i<=M;++i)
	{
		if(!used[i])
		{
			mju[i]=mi(0,1);
			f[i]=mi(1,i);
			fac[i]=i;
			prime[++tot]=i;
		}
		for(j=1;j<=tot&&i*prime[j]<=M;++j)
		{
			used[i*prime[j]]=1;
			if(i%prime[j])
			{
				f[i*prime[j]]=mul(f[i],f[prime[j]]);
				fac[i*prime[j]]=prime[j];
				mju[i*prime[j]]=mul(mju[i],mju[prime[j]]);
			}
			else
			{
				fac[i*prime[j]]=fac[i]*fac[prime[j]];
				mju[i*prime[j]]=0;
				if(fac[i*prime[j]]==i*prime[j])
					f[i*prime[j]]=f[i];
				else
					f[i*prime[j]]=mul(f[i*prime[j]/fac[i*prime[j]]],f[fac[i*prime[j]]]);
				break;
			}
		}
	}
	for(i=1;i<=M;++i) f[i]=mul(f[i],i);
	for(i=1;i<=M;++i) s[i]=add(s[i-1],f[i]);
}

int _sum(int x)
{
	return (1LL*x*(x+1)>>1)%mod;
}
int func(int x,int y)
{
	return mul(_sum(x),_sum(y));
}

void work()
{
	int l,r,ans=0;
	scanf("%d%d",&n,&m);
	if(n>m) swap(n,m);
	for(l=1;l<=n;++l)
	{
		r=min(n/(n/l),m/(m/l));
		inc(ans,mul(func(n/l,m/l),mi(s[r],s[l-1])));
		l=r;
	}
	printf("%d\n",ans);
}

int main()
{
	prework();work();
	return 0;
}

```

---

## 作者：Sym_Je (赞：0)

# P1829 [国家集训队]Crash的数字表格 / JZPTAB     

## 题目大意    
求 $\sum_{i=1}^{n}\sum_{j=1}^{m}lcm(i,j)$     

## 题解    
还是推柿子啊    
首先为了方便我们设 $n<m$
$$\sum_{i=1}^{n}\sum_{j=1}^{m}lcm(i,j)$$      
$$\sum_{i=1}^{n}\sum_{j=1}^{m} (\frac{i × j}{gcd(i,j)})$$     
$$\sum_{d=1}^{d=n}\sum_{i=1}^{n}\sum_{j=1}^{m} (\frac{i × j}{[gcd(i,j)==d]×d})$$    
$$\sum_{d=1}^{d=n}~d~\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor} (\frac{i × j}{[gcd(i,j)==1]})$$      
$$\sum_{d=1}^{d=n}~d~\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor} (\frac{i × j}{[gcd(i,j)==1]})$$   
因为我们 $[gcd(i,j)==1]$ 是可以翻到上面的，不影响 。   
所以    
$$\sum_{d=1}^{d=n}~d~\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor} ({i × j} ×{[gcd(i,j)==1]})$$     

$$\sum_{d=1}^{d=n}~d~\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor} ({i × j} ×\sum_{k|i,k|j}\mu(k))$$     
$$\sum_{d=1}^{d=n}~d~\sum_{k=1}^{\lfloor \frac{n}{d} \rfloor}\mu(k)×k^2×\sum_{i=1}^{\lfloor \frac{n}{dk} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{dk} \rfloor} ({i × j} )$$   

对于前面一部分我们显然可以数论分块，对于后面呢一块我们也是可以数论分块的 。   
最后我们分块套分块  。   
复杂度 $O(n)$  

* $\frak{Code}$   

```cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=20101009;
const ll maxn=1e7+10;
ll np[maxn],pr[maxn],num,mu[maxn],S[maxn];
ll n,m;
void init() {
	mu[1]=1;
	for(ll i=2;i<maxn;++i) {
		if(!np[i]) pr[++num]=i,mu[i]=-1;
		for(ll j=1;j<=num;++j) {
			if(i*pr[j]>=maxn) break ;
			np[i*pr[j]]=1;
			if(i%pr[j]==0) {
				mu[i*pr[j]]=0;
				break ;
			}
			mu[i*pr[j]]=-mu[i];
		}
	}
	for(ll i=1;i<maxn;++i) {
		S[i]=(S[i-1]+(mu[i]*i+mod)%mod*i%mod)%mod;
	}
}

ll get(ll n,ll m) {
	return (n*(n+1)/2)%mod*(m*(m+1)/2%mod)%mod;
}

ll so(ll x,ll y) {
	ll ans=0;
	for(ll l=1,r;l<=x;l=r+1) {
		r=min(x/(x/l),y/(y/l));
		ans=(ans+(S[r]-S[l-1]+mod)%mod*get(x/l,y/l)%mod)%mod;
	}
	return ans;
}

ll wo() 
{
	ll ans=0;
	for(ll l=1,r;l<=n;l=r+1) {
		r=min((n/(n/l)),m/(m/l));
		ans=(ans+(l+r)*(r-l+1)/2%mod*(so(n/l,m/l))%mod)%mod;
	}
	return ans;
}

int main() 
{
	init();
	scanf("%lld%lld",&n,&m);
	if(n>m) swap(n,m);
	cout<<wo()<<"\n";
	return 0;
}


```

---

