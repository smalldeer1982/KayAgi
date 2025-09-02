# [ABC241Ex] Card Deck Score

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc241/tasks/abc241_h

$ N $ 個の整数のうちいずれか $ 1 $ つが書かれたカードが何枚かあり、 具体的には、$ A_i $ が書かれたカードが $ B_i $ 枚あります。  
次に、この $ B_1+B_2\cdots\ +B_N $ 枚の中から $ M $ 枚のカードを選ぶ方法について、 その選んだカードに書かれた $ M $ 個の整数の積をその選び方のスコアとして定めます。  
同じ整数が書かれたカードは区別できないとしたとき、$ M $ 枚の選び方としてあり得る すべての選び方についてスコアを足し合わせた値を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 16 $
- $ 1\ \leq\ M\ \leq\ 10^{18} $
- $ 1\ \leq\ A_i\ <\ 998244353 $
- $ 1\ \leq\ B_i\ \leq\ 10^{17} $
- $ i\neq\ j $ ならば $ A_i\ \neq\ A_j $
- $ M\leq\ B_1+B_2+\cdots\ B_N $
- 入力は全て整数である。

### Sample Explanation 1

$ 3 $ 枚を選ぶ方法としては次の $ 6 $ 通りが考えられます。 - $ 3 $ と書かれたカードを $ 1 $ 枚、$ 5 $ と書かれたカードを $ 2 $ 枚選ぶ。 - $ 3 $ と書かれたカードを $ 1 $ 枚、$ 5 $ と書かれたカードを $ 1 $ 枚、$ 6 $ と書かれたカードを $ 1 $ 枚選ぶ。 - $ 3 $ と書かれたカードを $ 1 $ 枚、$ 6 $ と書かれたカードを $ 2 $ 枚選ぶ。 - $ 5 $ と書かれたカードを $ 2 $ 枚、$ 6 $ と書かれたカードを $ 1 $ 枚選ぶ。 - $ 5 $ と書かれたカードを $ 1 $ 枚、$ 6 $ と書かれたカードを $ 2 $ 枚選ぶ。 - $ 6 $ と書かれたカードを $ 3 $ 枚選ぶ。 スコアは順に $ 75 $, $ 90 $, $ 108 $, $ 150 $, $ 180 $, $ 216 $ であり、これらの総和は $ 819 $ となります。

### Sample Explanation 2

「 $ 1 $ と $ 25 $ の書かれたカードを $ 1 $ 枚ずつ選ぶ」選び方と 「 $ 5 $ の書かれたカードを $ 2 $ 枚選ぶ」選び方は、いずれもスコアは $ 25 $ ですが、 カードの選び方としては異なるものとして数えられます。

### Sample Explanation 3

$ 998244353 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
3 3
3 1
5 2
6 3```

### 输出

```
819```

## 样例 #2

### 输入

```
3 2
1 1
5 2
25 1```

### 输出

```
180```

## 样例 #3

### 输入

```
10 232657150901347497
139547946 28316250877914575
682142538 78223540024979445
110643588 74859962623690081
173455495 60713016476190629
271056265 85335723211047202
801329567 48049062628894325
864844366 54979173822804784
338794337 69587449430302156
737638908 15812229161735902
462149872 49993004923078537```

### 输出

```
39761306```

# 题解

## 作者：Register_int (赞：9)

看到拆分 DNA 又动了，于是大力生成函数，得到答案：

$$
\begin{aligned}
&[x^m]\prod^n_{i=1}\sum^{B_i}_j(a_ix)^j\\
=&[x^m]\prod^n_{i=1}\dfrac{1-(a_ix)^{b_i+1}}{1-a_ix}\\
=&[x^m]\prod^n_{i=1}(1-(a_ix)^{b_i+1})\times\left(\prod^n_{i=1}\dfrac1{1-a_ix}\right)
\end{aligned}
$$

由于 $n$ 非常小，所以前半部分直接暴力算就行了。考虑后半段怎么算，稍微部分分式展开一下：

$$
\begin{aligned}
\prod^n_{i=1}\dfrac1{1-a_ix}&=\sum^n_{i=1}\dfrac{t_i}{1-a_ix}\\
\sum^n_{i=1}\dfrac{t_i}{1-a_ix}\prod^n_{j=1}(1-a_jx)&=1\\
\sum^n_{i=1}t_i\prod^n_{j=1,j\not=i}(1-a_jx)&=1\\
\end{aligned}
$$

这里要运用 $x$ 的任意性，让前面的和式在 $i\not=k$ 时都为 $0$。容易想到设 $x=\dfrac{a_j}{a_k}$，则有：

$$
\begin{aligned}
t_k\prod^n_{j=1,j\not=k}(1-\dfrac{a_j}{a_k})&=1\\
t_i&=\left(\prod^n_{j=1,j\not=k}(1-\dfrac{a_j}{a_k})\right)^{-1}\\
\end{aligned}
$$

$t_i$ 即可 $O(n^2)$ 算出。再根据 $\dfrac1{1-ax}=\sum_ia^ix^i$，即可 $O(n)$ 单点计算分母部分的系数。再根据分子部分大力乘出来也顶多只有 $2^n$ 个项系数不为 $0$，所以可以 $O(n2^n)$ 大力硬乘乘出系数，总时间复杂度为 $O(n^2+n2^n)$，完结撒花。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1 << 16;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

int n; ll a[16], b[16], c[16], m;

ll f[MAXN], p[MAXN], t[16], x, ans;

int main() {
	scanf("%d%lld", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d%lld", &a[i], &b[i]), c[i] = mod - qpow(a[i], ++b[i]);
	for (int s = 0; s < 1 << n; s++) {
		f[s] = 1, p[s] = 0;
		for (int i = 0; i < n; i++) if (s >> i & 1) f[s] = f[s] * c[i] % mod, p[s] += b[i];
	}
	for (int i = 0; i < n; i++) {
		x = qpow(a[i], mod - 2), t[i] = 1;
		for (int j = 0; j < n; j++) if (i != j) t[i] = t[i] * (mod + 1 - a[j] * x % mod) % mod;
		t[i] = qpow(t[i], mod - 2);
	}
	for (int s = 0; s < 1 << n; s++) {
		if (p[s] > m) continue;
		for (int i = 0; i < n; i++) ans = (ans + f[s] * t[i] % mod * qpow(a[i], m - p[s]) % mod) % mod;
	}
	printf("%lld", ans);
}
```

---

## 作者：Re_Star (赞：6)

[题面](https://www.luogu.com.cn/problem/AT_abc241_h) 

[更好的阅读体验](https://www.cnblogs.com/Re-Star/p/18677283)

题面：有一些卡牌，每张卡牌上有一个数字，具体的，有 $b_i$ 张卡牌上的数字为 $a_i$。

求出拿走其中 $m$ 张卡牌的贡献之和。贡献为这些卡牌的乘积。对于本质相同的卡牌组合，只算一次。

- $n\leq 16,m\leq 10^{18},b_i\leq 10^{17},1\leq a_i<mod$ 

$sol$ ：

首先对于每种卡牌构造生成函数：

$$
\sum\limits_{j=0}^{b_i} a_i^jx^j=\frac{1-a_i^{b_i+1}x^{b_i+1}}{1-a_ix}
$$

最终答案的就是：

$$
\begin{aligned}
[x^m]\prod\limits_{i=1}^n \frac{1-a_i^{b_i+1}x^{b_i+1}}{1-a_ix}\\
=[x^m]\frac{\prod\limits_{i=1}^n1-a_i^{b_i+1}x^{b_i+1}}{\prod\limits_{i=1}^n1-a_ix}
\end{aligned}
$$

这里因为 $n$ 很小，只有 $16$ 所以可以$2^n$暴力把分子部分展开。假设展开有 $w$ 项，第 $i$ 项为 $c_ix^{d_i}$，则累加每一项的贡献得到的答案就是：

$$
\begin{aligned}
\sum\limits_{i=1}^wc_i\times[x^{n-d_i}]\frac{1}{\prod\limits_{i=1}^n1-a_ix}
\end{aligned}
$$

 现在问题变成了 $2^n$ 次询问分母某一位的值。处理分母可以考虑待定系数，如果可以写成求和的形式就好做多了，于是我们令：

$$
\begin{aligned}
\prod\limits_{i=1}^n\frac1{1-a_ix}=\sum\limits_{i=1}^n \frac{p_i}{1-a_ix}\\
\sum\limits_{i=1}^n \frac{p_i}{1-a_ix}\prod\limits_{j=1}^n 1-a_jx=1\\
\sum\limits_{i=1}^n p_i\prod\limits_{j=1,j\ne i}^n 1-a_jx=1\\
\end{aligned}
$$

一般来说生成函数中的 $x$ 是没有实际意义的，但是这里我们可以考虑把它当作一个普通的函数，而普通函数有一个优势，可以代值求待定系数。所以我们代入 $x=\frac1{a_k}$ 那么当 $j=k$  时，式子中 $1-a_jx=0$，也就是说只有 $i=k$ 这一项被保留了下来：

$$
\begin{aligned}
p_i\prod\limits_{j=1,j\ne i}^n 1-\frac{a_j}{a_i}=1\\
p_i=\frac1{\prod\limits_{j=1,j\ne i}^n 1-\frac{a_j}{a_i}}
\end{aligned}
$$

于是我们可以求出每一项的待定系数，现在再看一下分母的形式就非常好求了：

$$
\begin{aligned}
[x^k]\sum\limits_{i=1}^n \frac{p_i}{1-a_ix}\\
=\sum\limits_{i=1}^n[x^k]\frac{p_i}{1-a_ix}\\
=\sum\limits_{i=1}^np_i\times a_i^k
\end{aligned}
$$

至此，我们得到了一个单次 $O(n)$ 查询某一位的做法。

最终复杂度：$O(n2^n\log m)$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,N=1e6+5;
inline ll rd()
{
    char c;ll f=1;
    while(!isdigit(c=getchar()))if(c=='-')f=-1;
    ll x=c-'0';
    while(isdigit(c=getchar()))x=x*10+(c^48);
    return x*f;
}
ll qp(ll x,ll y)
{
    ll res=1;
    while(y)
    {
        if(y&1)res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
ll n,m,a[20],in,b[20],x[20],p[20],nx[N],P[N],w=1;
int main()
{
    n=rd(),m=rd();
    for(int i=1;i<=n;i++)
        a[i]=rd(),b[i]=rd(),x[i]=-qp(a[i],b[i]+1);
    nx[w]=1,P[w]=0;
    for(int i=1;i<=n;i++)
    {
        int t=w;
        for(int j=1;j<=t;j++)
        {
            nx[++w]=nx[j]*x[i]%mod;
            P[w]=P[j]+b[i]+1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        p[i]=1,in=qp(a[i],mod-2);
        for(int j=1;j<=n;j++) if(i!=j)
            p[i]=p[i]*qp(1-in*a[j]%mod+mod,mod-2)%mod;
    }
    ll ans=0;
    for(int i=1;i<=w;i++)
    {
        if(P[i]>m) continue;
        ll now=m-P[i];
        ll res=0;
        for(int j=1;j<=n;j++)
            (res+=(p[j]*qp(a[j],now)%mod))%=mod;
        (ans+=(nx[i]*res%mod))%=mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：5)

Update 2023.05.12 通过代码挂错了，现已修改。

容斥是平凡的，每种排均选小于等于 $b_i$ 张显然不好算，不如钦定某些排强制大于 $b_i$。

接下来就是算把 $x$ 分成 $\sum_{i=1}^nx_i$ 式子 $\prod_{i=1}^na_i^{x_i}$ 之和。

不会生成函数，考虑先朴素 $dp_{i,j}$ 表示目前考虑了 $1\sim i$ 的 $x_i$，其和为 $j$ 的权值和。不难发现转移可以考虑在 $x_k$ 上加一满足 $k\ge i$。

不难发现转移容易写成矩阵形式。复杂度 $O(2^nn^3\log m)$ 大约为 $1.7\times10^{10}$。稍微卡常，对矩阵快速幂部分进行简单预处理，增加访问连续，避免过多取模即可通过。（实际上是 $\frac{1}{12}$ 的常数）

[通过代码。](https://atcoder.jp/contests/abc241/submissions/39472506)

---

## 作者：Masterwei (赞：5)

非常有价值的一道题。

发现这道题我们直接 `dp` 的话不好优化，所以我们考虑容斥，钦定一些位置至少选择 $b_i+1$ 个，然后就可以算出随便选的答案，拿进去容斥即可。不会这一步的可以去看看 [CF451E](https://www.luogu.com.cn/problem/CF451E)。

那么现在我们就只用求出随便选的方案数就可以了。

设 $f_{i,j}$ 表示选了 $i$ 张卡牌，用的是前 $j$ 种，且结尾必须是 $j$ 的贡献是多少，考虑转移：$f_{i,j}=\sum_{k=0}^{k\le j}f_{i-1,k}\times a_j$。但是还是过不了，考虑用矩乘优化，预处理一些东西可以将时间复杂度变为 $O(2^n\times n^2\log m)$。不用卡常即可通过。

[代码](https://atcoder.jp/contests/abc241/submissions/60798361)。

---

## 作者：EuphoricStar (赞：4)

答案即为：

$$\sum\limits_c \prod\limits_{i = 1}^n [c_i \le b_i] a_i^{c_i}$$

考虑生成函数，设 $F_i(x) = \sum\limits_{j = 0}^{b_i} (a_i x)^j$。那么答案即为 $[x^m] \prod\limits_{i = 1}^n F_i(x)$。

考虑 $F_i(x) = \sum\limits_{j = 0}^{b_i} (a_i x)^j = \frac{1 - (a_i x)^{b_i + 1}}{1 - a_i x}$。分子可以 $O(2^n)$ 枚举乘了哪一项，这样可以知道分母需要贡献 $x$ 的多少次方。我们重点关注分母。设现在要求分母的 $x^q$ 次项。

有一个常见套路是设 $\sum\limits_{i = 1}^n \frac{f_i}{1 - a_i x} = \frac{1}{\prod\limits_{i = 1}^n (1 - a_i x)}$。因为 $\sum\limits_{i = 1}^n \frac{f_i}{1 - a_i x} = \frac{\sum\limits_{i = 1}^n f_i \prod\limits_{j \ne i} (1 - a_j x)}{\prod\limits_{i = 1}^n (1 - a_i x)}$ 所以可以列出 $n$ 个关于 $f_i$ 的方程，可以高斯消元求解。

那么 $[x^q] \frac{1}{\prod\limits_{i = 1}^n (1 - a_i x)} = [x^q] \sum\limits_{i = 1}^n \frac{f_i}{1 - a_i x} = \sum\limits_{i = 1}^n f_i ([x^q] \sum\limits_{j \ge 0} (a_i x)^j) = \sum\limits_{i = 1}^n f_i a_i^q$。

总时间复杂度 $O(n (2^n \log m + n^2))$。

[code](https://atcoder.jp/contests/abc241/submissions/53262485)

---

## 作者：TernaryTree (赞：4)

设第 $i$ 类卡牌选了 $c_i$ 个。答案为

$$\sum_{c_1+c_2+\dots +c_n=m}\prod_{i=1}^n a_i^{c_i}$$

令 $F_i(x)=\sum\limits_{j=0}^{b_i}a_i^jx^j=\dfrac{(a_ix)^{b_i+1}-1}{a_ix-1}$，则答案为

$$[x^m]\prod_{i=1}^n F_i(x)=[x^m]\prod_{i=1}^n\dfrac{(a_ix)^{b_i+1}-1}{a_ix-1}$$

令 $G(x)=\prod\limits_{i=1}^n\left((a_ix)^{b_i+1}-1\right)$，$H(x)=\prod\limits_{i=1}^n\dfrac{1}{a_ix-1}$。$G(x)$ 可以 $2^n$ 暴力计算，$H(x)$ 考虑展开成求和。不妨设 $H(x)=\sum\limits_{i=1}^n t_i\cdot\dfrac{1}{a_ix-1}$，则

$$\sum_{i=1}^n t_i\cdot \prod_{j\neq i}(a_jx-1)=1$$

取 $x\in\left\{\dfrac{1}{a_i}\mid 1\le i\le n\right\}$，不妨设 $x=\dfrac1{a_k}$，则容易发现当 $i\neq k$ 时 $j$ 可以取到 $k$，$a_k\cdot \dfrac1{a_k}-1=0$，此时右边式子为 $0$；所以此时可化为 $t_k\prod\limits_{j\neq k}(a_jx-1)=1$，即 $t_k=\dfrac1{\prod\limits_{j\neq k}\left(\dfrac{a_j}{a_k}-1\right)}$。

算出 $t_i$ 再带回去，有

$$
\begin{aligned}
H(x)&=\sum_{i=1}^nt_i\cdot\dfrac{1}{a_ix-1} \\
&= -\sum_{i=1}^nt_i\cdot\dfrac{1}{1-a_ix} \\
&= -\sum_{i=1}^nt_i\sum_{j=0}^{\infin}a_i^jx^j \\
&= -\sum_{j=0}^{\infin}x^j\sum_{i=1}^nt_ia_i^j \\
\end{aligned}
$$

所以 $[x^k]H(x)=-\sum\limits_{i=1}^nt_ia_i^k$。又

$$ans=[x^m]\prod_{i=1}^n F_i(x)=\sum_{i=0}^m [x^i]G(x)\cdot [x^{m-i}]H(x)$$

而 $G(x)$ 只有不超过 $2^n$ 项，$H(x)$ 单项系数可以 $\Theta(n)$ 算出，暴力卷起来即可。[Code](https://www.luogu.com.cn/paste/f3j98vly)。

---

## 作者：analysis (赞：4)

容易想到一个平凡的 DP：设 $f_{i,j}$ 为仅考虑前 $i$ 个选出 $j$ 个的答案。

于是有：

$$
f_{i,j} = \sum_{k=0}^{b_{i-1}}f_{i-1,j-k}
$$

转移方程很简单，容易想到使用生成函数或矩阵一类的东西维护他。

这里设：

$$
F_i = \sum_{j=0}^{\infty}f_{i,j}x^j
$$

易得转移多项式：

$$
T_i = \sum_{k=0}^{b_i}a_i^kx^k = \frac{1 - (a_ix)^{b_i+1}}{1 - a_ix}\\
F_i = F_{i-1}T_i
$$

于是：

$$
F_n = \prod_{i=1}^{n}T_i = \prod_{i=1}^{n}\frac{1 - (a_ix)^{b_i+1}}{1 - a_ix}
$$

上面部分可以使用暴力乘法，因为 $n$ 很小，$2^n$ 可以接受。

下半部分可以考虑待定系数：

$$
\prod_{i=1}^{n}\frac{1}{1 - a_ix} = \sum_{i=1}
^{n}\frac{t_i}{1 - a_ix}
$$

于是：

$$
\sum_{i=1}^nt_i\prod_{j=1}^{n}[i \neq j](1-a_jx)=1
$$

带入 $x = \frac{1}{a_k}$：

$$
t_k\prod_{j=1}^{n}[k \neq j](1-\frac{a_j}{a_k}) = 1
$$

$$
t_i = \frac{1}{\prod_{j=1}^{n}[k \neq j](1-\frac{a_j}{a_k})}
$$

$O(n^2)$ 即可求得所有 $t$。

时间复杂度 $O(n^2+n2^n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
int fpow(int a,int b=mod-2)
{
    int r=1;
    while(b)
    {
        if(b&1)r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r;
}
int n,m,a[20],b[20],bs[20],t[20];
int lk[(1<<17)],pw[(1<<17)],cnt=1;
signed main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i],bs[i] = mod - fpow(a[i],(b[i]+1)%(mod-1));
    lk[cnt]=1,pw[cnt]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=cnt;j>=1;j--)
        {
            cnt++;
            lk[cnt] = lk[j] * bs[i] % mod;
            pw[cnt] = pw[j] + b[i] + 1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        t[i] = 1;int v = fpow(a[i]);
        for(int j=1;j<=n;j++)
        {
            if(i == j)continue;
            t[i] = t[i] * (1 - v * a[j] % mod + mod) % mod;
        }
        t[i] = fpow(t[i]);
    }
    int ans =0;
    for(int i=1;i<=cnt;i++)
    {
        if(pw[i] > m)continue;
        int nd = m - pw[i];
        nd %= mod-1;
        int v=0;
        for(int j=1;j<=n;j++)
        {
            v = (v + t[j] * fpow(a[j],nd) % mod) % mod;
        }
        ans = (ans + lk[i] * v % mod) % mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Reunite (赞：3)

## 一
---

记每种球选了 $c_i$ 个，则答案为：

$$\sum_{\sum c_i=m \wedge c_i\le b_i}\prod_{i} a_i^{c_i}$$

直接列出 dp 转移，设 $f_{i,j}$ 表示前 $i$ 种，选了 $j$ 个的权值和，有 
$$f_{i,j}=\sum_{k=0}^{\min(j,b_i)} f_{i-1,j-k}a_i^k$$

这个 $\min$ 在这里十分难搞，没什么好办法优化，所以尝试用容斥把限制干掉。设我们钦定有若干一定超过 $b_i$，剩下的无限制，其被钦定的种类的二进制压缩状态为 $s$，则答案为：
$$\sum_{s}(-1)^{|s|}val(m-\sum_{i \in s} (b_i+1))$$

$val(m)$ 表示无限制地选择 $m$ 个球的权值和，则 dp 可改写为：$f_{i,j}=f_{i-1,j}+f_{i-1,j-1}a_i$ 直接上矩阵优化就好了。

---
## 二
---

然后就被卡常了，可以预处理了转移矩阵的 $2$ 的幂次方，减少一倍常数，发现初始矩阵其实就是一个行向量，使用向量乘矩阵就行，这样复杂度会少一个 $n$。

时间复杂度 $O(n^22^n\log m)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int unsigned long long
#define mod 998244353
using namespace std;

int n,m;
int a[20],b[20];
struct node{int a[20][20];};
node A,B,mi[65];

node operator * (node A,node B){
	node C;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			C.a[i][j]=0;
			for(int k=1;k<=n;k++)
				C.a[i][j]+=A.a[i][k]*B.a[k][j];
			(C.a[i][j])%=mod;
		}
	}
	return C;
}

node operator / (node A,node B){
	node C;
	for(int j=1;j<=n;j++){
		C.a[1][j]=0;
		for(int k=1;k<=n;k++)
			C.a[1][j]+=A.a[1][k]*B.a[k][j];
		(C.a[1][j])%=mod;
	}
	return C;
}

inline int calc(int x,int k){
	k%=(mod-1);
	int tmp=1;
	while(k){
		if(k&1) tmp=tmp*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return tmp;
}

inline int solve(int M){
	node C=A;
	for(int i=0;i<=60;i++)
		if(M&(1ll<<i)) C=C/mi[i];
	int s=0;
	for(int i=1;i<=n;i++) (s+=C.a[1][i])%=mod;
	return s;
}

signed main(){
	scanf("%llu%llu",&n,&m);
	for(int i=1;i<=n;i++) scanf("%llu%llu",&a[i],&b[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++) B.a[j][i]=a[i];
	A.a[1][1]=1;
	mi[0]=B;
	for(int i=1;i<=60;i++) mi[i]=mi[i-1]*mi[i-1];
	int ans=0;
	for(int s=0;s<(1llu<<n);s++){
		int ct=0,M=m,S=1,ok=0;
		for(int i=1;i<=n;i++){
			if(!(s&(1<<(i-1)))) continue;
			ct++;
			if(M>=b[i]+1) M-=b[i]+1;
			else{ok=1;break;}
			S=S*calc(a[i],b[i]+1)%mod;
		}
		if(ok) continue;
		if(M>0) S=S*solve(M)%mod;
		if(ct&1) S=(mod-S)%mod;
		(ans+=S)%=mod;
	}
	printf("%llu\n",ans);

	return 0;
}
```

---

## 作者：Graphcity (赞：3)

为啥全是生成函数？？？

考虑容斥，钦定集合 $S$ 内的数字 $>b$。枚举 $S$，先把 $S$ 内部的每个元素先选 $b+1$ 个，这样处理完后每个元素都是平等的了。设当前剩余的 $m$ 为 $m'$。

接下来要做的事，就是给每个元素分配它被选择的次数 $x_i$，总贡献就是 $\prod_{i=1}^n a_i^{x_i}$。考虑 DP，设 $f_{i,j}$ 表示考虑到二进制从低往高第 $i$ 位，上一位进位进了 $j$ 过来的贡献。

转移考虑枚举这一位选择了几个元素。可以预处理 $val_{i,j}$ 表示第 $i$ 位选择了 $j$ 个元素的总贡献。

总时间复杂度 $O(2^nn^2\log m)$，可以用前缀和优化到 $O(2^nn\log m)$，但是跑的很快没必要。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=65536,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,lim,a[Maxn+5]; ll m,b[Maxn+5];
int f[65][25],val[65][25];

inline int Work(int p)
{
    ll sum=0; int all=1; For(i,0,n-1) if(p&(1<<i))
        sum+=b[i]+1,all=1ll*all*Pow(a[i],(b[i]+1)%(Mod-1))%Mod;
    if(sum>m) return 0; sum=m-sum;
    memset(f,0,sizeof(f)),f[0][0]=all;
    For(i,0,62) For(j,0,20) if(f[i][j]) For(t,0,n)
    {
        int res=1ll*f[i][j]*val[i][t]%Mod;
        if(((j+t)&1)!=((sum>>i)&1)) continue;
        (f[i+1][(j+t)/2]+=res)%=Mod;
    } return f[63][0];
}

signed main()
{
    cin>>n>>m; lim=(1<<n)-1;
    For(i,0,n-1) cin>>a[i]>>b[i];
    For(i,0,lim)
    {
        int res=1,c=__builtin_popcount(i);
        For(j,0,n-1) if(i&(1<<j)) res=1ll*res*a[j]%Mod;
        For(j,0,62) val[j][c]=(val[j][c]+res)%Mod,res=1ll*res*res%Mod;
    }
    int ans=0; For(i,0,lim)
        ans=(ans+1ll*Work(i)*(__builtin_popcount(i)&1?Mod-1:1))%Mod;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：1)

先把 $b_i$ 这个限制扔掉试试看。生成函数大家都会吧！答案即为 $\displaystyle [x^m]\prod_{i=1}^n\dfrac{1}{1-a_ix}$。

不容易想到的，考虑待定系数法。我们使得 $\displaystyle \prod_{i=1}^n \dfrac{1}{1-a_ix}=\sum_{i=1}^n \dfrac{c_i}{1-a_ix}$。

这个式子可以变成 $\displaystyle \sum_{i=1}^n c_i\prod_{j\neq i}(1-a_jx)=1$。基本的技巧是代入 $\dfrac{1}{a_1},\dfrac{1}{a_2},\dots,\dfrac{1}{a_n}$。
则有 $\displaystyle c_i\prod_{j\neq i}(1-\dfrac{a_j}{a_i})=1$。有点像拉格朗日插值。

至此我们可以在 $O(n^2)$ 的时间内解决 $c_i$ 的问题。接下来答案即为 $\displaystyle \sum_{i=1}^nc_ia_i^m$。

剩下的部分都不难了。考虑硬币购物式的容斥，则枚举一个集合 $S$ 超过限制，这是容易计算的。

时间复杂度 $O(n^2+n2^n\log p)$。

---

## 作者：云浅知处 (赞：0)

考虑随便选的时候（即没有 $B_i$ 这个约束）答案是啥，发现是
$$
[x^M]\prod_{i=1}^N(1+A_ix+A_i^2x^2+\cdots)=[x^M]\prod_{i=1}^N\dfrac{1}{1-A_ix}
$$
这东西......总之可以暴力算出 $F(x)=\prod(1-A_ix)$，然后求逆。

我不会多项式科技怎么办！只会暴力写求逆递推式然后矩阵快速幂 $O(N^3\log M)$ 啊，自闭了。

考虑拆一手，待定系数
$$
\begin{aligned}\prod_{i=1}^N\dfrac{1}{1-A_ix}&=\sum_{i=1}^N\dfrac{c_i}{1-A_ix}\\1&=\sum_{i=1}^Nc_i\prod_{j\neq i}(1-A_jx)\end{aligned}
$$
依次取 $x=A_1^{-1},A_2^{-1},\cdots,A_N^{-1}$，我们就可以得到
$$
c_i\prod_{j\neq i}(1-A_jA_i^{-1})=1\qquad(1\le i\le N)
$$
这样就可以 $O(N^2)$ 时间内解出 $c_i$ 的值。接下来就有
$$
[x^M]\prod_{i=1}^N\dfrac{1}{1-A_ix}=\sum_{i=1}^Nc_iA_i^M
$$
然后考虑容斥，钦定 $S$ 以内爆限制，发现只需要把 $M$ 减去 $\sum_{i\in S}B_i$ 然后乘上 $\prod_{i\in S}A_i^{B_i}$ 就行了。

总的时间复杂度为 $O(2^N\times N\log P)$。

>实际上你可以发现容斥干的事情无非是把原答案的多项式
>$$
[x^M]\prod_{i=1}^N\dfrac{1-A_i^{B_i+1}x^{B_i+1}}{1-A_ix}
$$
>的分子展开了而已！和生成函数做法没啥区别的！！

<https://atcoder.jp/contests/abc241/submissions/41307325>

---

