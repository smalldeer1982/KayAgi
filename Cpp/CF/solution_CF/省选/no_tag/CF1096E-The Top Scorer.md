# The Top Scorer

## 题目描述

Hasan 喜欢玩游戏，最近他发现了一款名为 TopScore 的游戏。在这款类似足球的游戏中，有 $p$ 名玩家进行点球大战。得分最多的玩家获胜。如果有多人并列最高分，则这些最高分玩家中会随机等概率选出一位作为获胜者。

比赛刚刚结束，现在大家都在等待结果。但有个小问题！裁判把记分纸弄丢了！幸运的是，他们在丢失前已经算出了总得分，并且对于部分玩家，他们还记得一个得分下界。不过这些下界信息是私密的，所以 Hasan 只知道自己的下界。

根据现有信息，他知道自己的得分至少为 $r$，所有人的总得分为 $s$。

因此，比赛的最终状态可以表示为一个 $p$ 元组 $a_1, a_2, \dots, a_p$（$0 \le a_i$）——即每位玩家的得分。Hasan 是第 $1$ 号玩家，所以 $a_1 \ge r$。并且 $a_1 + a_2 + \dots + a_p = s$。如果存在某个位置 $i$，使得 $a_i$ 在两种状态下不同，则这两种状态被认为是不同的。

Hasan 并不知道具体的得分情况（他甚至不知道自己的具体得分）。因此，他认为每一种可能的最终状态出现的概率都是相等的。

请你帮助 Hasan 计算他获胜的概率。

可以证明，这个概率可以表示为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是非负整数，$Q \ne 0$，$P \le Q$。请输出 $P \cdot Q^{-1} \bmod {998244353}$。

## 说明/提示

在第一个样例中，Hasan 可能进 $3$、$4$、$5$ 或 $6$ 个球。如果他进了 $4$ 个或更多球，他就比唯一的对手进球多。如果他进了 $3$ 个球，对手也进了 $3$ 个球，这时 Hasan 有 $\frac{1}{2}$ 的概率获胜。因此，他最终获胜的概率是 $\frac{7}{8}$。

在第二个样例中，即使 Hasan 的进球下界，也意味着他比其他任何对手都多进球。因此，结果概率为 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 6 3
```

### 输出

```
124780545
```

## 样例 #2

### 输入

```
5 20 11
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10 30 10
```

### 输出

```
85932500
```

# 题解

## 作者：FreshP_0325 (赞：24)

提出一个 $O(p+s)$ 的做法。

先考虑一个比较简单的问题。如果 $r=0$，答案是多少？

答案是 $\dfrac{1}{n}$。具体证明是有很多个序列，你随机点一个位置，点到最大值的概率就是 $\dfrac{1}{n}$。每个序列都是的概率 $\dfrac{1}{n}$，那么总概率就是 $\dfrac{1}{n}$。

再回到这个问题。我们要求小明的得分大于等于 $r$，问其是最大值的概率。我们考虑上面的那个方法，发现区别在于多了要求「最大值大于等于 $r$」。

那我们考虑直接枚举大于等于 $r$ 的数的个数，有答案：

$$
\sum_{i=1}^{p} \dfrac{1}{i} \dbinom{p-1}{i-1}(-1)^{i-1}\dbinom{s-ir+p-1}{p-1} = \dfrac{1}{n} \sum_{i=1}^{p} \dbinom{p}{i}(-1)^{i-1}\dbinom{s-ir+p-1}{p-1}
$$

（这两个式子显然相等。前面那个可以很简单地考虑组合意义，后面那个是沿用上面的方法。都采用了二项式反演用钦定推出至少。）

算了还是稍微解释一下。

首先是第一个，就是钦定小明编号为 $1$ 并且得分不低于 $r$，后面还有 $i-1$ 个得分不低于 $r$，其他的在 $n$ 个里面随便乱放，最大值在这 $i$ 个里面产出；因为有的得分会超过 $r$ 也有可能作为最大值，所以要考虑容斥。

第二个是考虑上面的方法，相当于算至少有一个位置大于等于 $k$ 的方案数；那么二项式反演，钦定推至少，最后答案乘上 $\dfrac{1}{n}$。

因为算的是概率，最后乘上 $\dfrac{1}{\dbinom{s-r+p-1}{p-1}}$。

那么时间复杂度 $O(p+s)$。可以加强。

```cpp
int main() {
    int n = read(), m = read(), k = read();
    fac[0] = 1;
    for (int i = 1; i <= n + m; ++i) fac[i] = Mul(fac[i - 1], i);
    ifac[n + m] = QuickPow(fac[n + m]);
    for (int i = n + m - 1; ~i; --i) ifac[i] = Mul(ifac[i + 1], i + 1);
    int ans = 0;
    for (int i = 1; i <= n && i * k <= m; ++i) {
        int c = Mul(C(n, i), C(m - i * k + n - 1, n - 1));
        if (i & 1)
            ans = Add(ans, c);
        else
            ans = Sub(ans, c);
    }
    ans = Mul(ans, QuickPow(C(m - k + n - 1, n - 1)));
    ans = Mul(ans, QuickPow(n));
    write(ans);
    return 0;
}
```

---

## 作者：小粉兔 (赞：12)

一道经典组合数学+容斥题。

### 题意简述：

$p$ 个人，每个人有得分 $a_i$。  
总得分 $\sum a_i = s$。  
第一个人得分 $a_1 \ge r$。

得分最高的人可以获胜，如果多个人得分最高，则等概率随机其中一个人获胜。

问第一个人获胜的概率。

### 题解：

第一个人要获胜，他的得分必须是最高分。

考虑枚举第一个人的得分，假设 $a_1 = x$。

再枚举总共有几个人得分和第一个人一样（包括第一个人），假设有 $i$ 个。

那么剩下的 $p - i$ 个人的得分必须满足 $a_i < x$，$\sum a_i = s - ix$。

也就是说，$s - ix$ 个无标号小球，放进 $p - i$ 个有标号盒子中，允许空盒子，每个盒子最多放 $x - 1$ 个球。

经典的组合问题：$n$ 个小球放入 $m$ 个盒子，允许空盒子的方案数为 $\binom{n + m - 1}{m - 1}$。

加上了球数不能大于等于 $x$ 的限制，考虑容斥：

- 枚举超过限制的盒子数 $0 \le i \le m$，容斥系数是 $(-1)^i\binom{m}{i}$。

- 而 $i$ 个盒子超过了限制的答案是 $\binom{n-ix+m-i-1}{m-i-1}$。

所以答案是 $\sum\limits_{i=0}^{m}(-1)^i\binom{m}{i}\binom{n-ix+m-i-1}{m-i-1}$。

总答案是 $\sum\limits_{x=r}^{s}\sum\limits_{i=1}^{p}\binom{p}{i}\left(\sum\limits_{j=0}^{p-i}(-1)^j\binom{p-i}{j}\binom{n-ix-jx+p-i-j-1}{p-i-j-1}\right)/i$。  
当然这式子太长了，不如封装一下。

注意各种组合数无意义的情况，`continue`掉就好了。

复杂度 $O(p^2s)$。

```cpp
#include <cstdio>

typedef long long LL;
const int Mod = 998244353;

inline int chk(int x) { if (x < 0) x += Mod; if (x >= Mod) x -= Mod; return x; }

inline int qPow(int b, int e)
{
	int a = 1;
	for (; e; b = (LL)b * b % Mod, e >>= 1)
		if (e & 1) a = (LL)a * b % Mod;
	return a;
}

int p, s, r, c[5105][105];

void Init()
{
	for (int i = 0; i <= 5100; ++i) c[i][0] = 1;
	for (int i = 0; i <= 5100; ++i)
		for (int j = 1; j <= i && j <= 100; ++j)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % Mod;
}

inline int Calc(int n, int m, int x)
{
	LL S = 0;
	for (int i = 0; i <= m && i * x <= n; ++i)
	{
		LL s = (LL)c[m][i] * c[n - x * i + m - 1][m - 1] % Mod;
		S += i & 1 ? -s : s;
	}
	return (S % Mod + Mod) % Mod;
}

int Sum1, Sum2;

int main()
{
	scanf("%d%d%d", &p, &s, &r);
	if (p == 1) return puts("1"), 0;
	Init();
	for (int x = r; x <= s; ++x)
	{
		if (x * p < s) continue;
		for (int i = 1; i <= p; ++i)
		{
			if (i * x > s || (p - i) * (x - 1) + i * x < s)
				continue;
			if (i == p) { Sum2 = (Sum2 + (i * x == s ? qPow(i, Mod - 2) : 0)) % Mod; continue; }
			Sum2 = (Sum2 + (LL)c[p - 1][i - 1] * Calc(s - i * x, p - i, x) % Mod * qPow(i, Mod - 2)) % Mod;
		}
	}
	Sum1 = c[s - r + p - 1][p - 1];
	printf("%lld\n", (LL)Sum2 * qPow(Sum1, Mod - 2) % Mod);
	return 0;
}
```

式子也可以写成 $p!\sum\limits_{x=r}^{s}\sum\limits_{i=1}^{p}\frac{1}{(m-i)!}\binom{n-ix-i-1}{p-i-1}\sum\limits_{j=1}^{i}\frac{(-1)^{i-j}}{(i-j)!}\cdot\frac{1}{j!\cdot j}$。（惊了，可以卷积）

复杂度可以优化到 $O(p\log p+sp)$。（为什么要写

---

## 作者：qqvq (赞：12)

#### 有错误烦请私信或者评论指出

[骗访问量](https://www.cnblogs.com/storz/p/10198953.html)，以后只要我打了的CF应该都会写题解，~~开花，关注~~

$$\text{题意：有}n\text{个人，每人有一个分数}a_i\left( a_i\geq 0 \right) ,\sum{a_i}=s$$
$$\text{假设最高分有}x\text{个，}x\text{个人中的每个人都有}\frac{1}{x}\text{的概率获胜}$$
$$\text{第1个人的得分一定在}\left[ r,s \right] \text{之内，给出}n,s,r\text{，求他的获胜概率}$$
$$\text{用隔板法，有}\left( \begin{array}{c} s-r+n-1\\ n-1\\ \end{array} \right)\text{种方案}\left( \text{有}r\text{个球已经被固定分给第1个人了} \right)$$
$$\text{求出第1个人作为最高分有多少种方案，再除以总方案数就是获胜概率（要除以同分人数）}$$
$$\text{枚举第1个人得了多少分}x\text{，以及跟他同分的人的个数}y\text{（不包括自己）}$$
$$\text{令}f\left( a,b,c \right) \text{表示}a\text{个非负整数的和是}b,\text{这}a\text{个数的上界是}c\text{的方案数}$$
$$\text{不考虑上界答案是}\left( \begin{array}{c} b+a-1\\ a-1\\ \end{array} \right) \text{（隔板法）}$$

$$g\left( i \right) \text{表示}\geq n-i\text{个不合法}\left( \leq i\text{个合法} \right) \text{的方案数，}h\left( i \right) \text{表示有}n-i\text{个不合法}\left( i\text{个合法} \right) \text{的方案数，}$$
$$g\left( x \right) =\sum_{i=0}^x{\left( \begin{array}{c} n\\ i\\ \end{array} \right) h\left( i \right)}$$
$$\text{要求}h\left( n \right) ,\text{由二项式反演}$$
$$h\left( n \right) =\sum_{i=0}^n{\left( -1 \right) ^{n-i}\left( \begin{array}{c} n\\ i\\ \end{array} \right) g\left( i \right)}$$

$$\text{对于一个}x\text{，}\sum_{y=0}^{n-1}{\left( \begin{array}{c} n-1\\ y\\ \end{array} \right) f\left( n-y-1,s-x\left( y+1 \right) ,x-1 \right)}\text{就是}x\text{作为最高分的方案数}$$

$$\text{所以答案就是}\frac{\sum_{x=r}^s{\begin{array}{c} \sum_{y=0}^{n-1}{\frac{\left( \begin{array}{c} n-1\\ y\\ \end{array} \right) f\left( n-y-1,s-x\left( y+1 \right) ,x-1 \right)}{\left( y+1 \right)}}\\ \end{array}}}{\left( \begin{array}{c} s-r+n-1\\ n-1\\ \end{array} \right)}$$


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;

int fac[10005], ifac[10005], n, s, r;

inline int Pow(int x, int y) {
  int ret = 1;
  while (y) {
    if (y & 1) ret = ret * 1ll * x % mod;
    x = x * 1ll * x % mod;
    y >>= 1;
  }
  return ret % mod;
}

inline int inv(int x) {
  return Pow(x, mod - 2);
}
inline int C(int n, int m) {
  if (m > n || m < 0) return 0;
  return fac[n] * 1ll * ifac[n - m] % mod * ifac[m] % mod;
}

inline int F(int n, int m) {//n个非负整数的和是m的方案数
  if (m < 0) return 0;
  return C(n + m - 1, n - 1);
}

inline int Mod(int x) {
  if (x >= mod) x -= mod; else if (x < 0) x += mod;
  return x;
}

inline int F1(int n, int m, int r) {  //n个非负整数的和是m 上界是r的方案数
  if (!n && !m) return 1; //此时是合法的 应该return 1;
  int ret = 0, sign = (n & 1) ? -1 : 1;
  for (int i = 0; i <= n; ++i, sign *= -1) if (m - (r + 1) * (n - i) >= 0) (ret += sign * C(n, i) % mod * F(n, m - (r + 1) * (n - i)) % mod) %= mod;
  //C(m - (r + 1) * i + n - 1, n - 1)
  return ret;
}

#undef int
int main() {
#define int long long
  fac[0] = 1;
  for (int i = 1; i <= 10000; ++i) fac[i] = fac[i - 1] * 1ll * i % mod;
  ifac[10000] = Pow(fac[10000], mod - 2);
  for (int i = 9999; i >= 0; --i) ifac[i] = ifac[i + 1] * 1ll * (i + 1) % mod;
  cin >> n >> s >> r;
  int ans = 0;
  for (int x = r; x <= s; ++x) {
    for (int y = 0; (y + 1) * x <= s && y + 1 <= n; ++y) {
      int m = n - y - 1, ss = s - (y + 1) * x;
      ans = Mod(ans + F1(m, ss, x - 1) * 1ll * C(n - 1, y) % mod * inv(y + 1) % mod);
    }
  }
  cout << ans * 1ll * inv(C(s - r + n - 1, n - 1)) % mod;
  return 0;
}
```

---

## 作者：λᴉʍ (赞：8)

概率就是可行方案除以总方案

先枚举第一个人获胜时的分数$x$，和与这个人分数相等的人$i$（这个人也算分数相等）

接下来的问题就是有$p-i$个人，总分为$s-xi$，而且分数都$<x$，求方案数

也就是$s-xi$个球放进$p-i$个容量为$x-1$的篮子

先解决这个问题：$n$个球放进$m$个容量为$lim$的篮子的方案数

可以直接容斥，枚举超过容量的篮子数，超过了的篮子直接减掉，隔板法算答案

所以这个问题的方案数为$\sum_{i=0}^{m}(-1)^iC_{m}^{i}C_{n-i\cdot lim+m-1}^{m-1}$

所以原问题也做完了

整理一下，$solve(n,m,lim)=\sum_{i=0}^{m}(-1)^iC_{m}^{i}C_{n-i\cdot lim+m-1}^{m-1}$

$ans=\sum_{x=r}^{s}\sum_{i=1}^p solve(s-xi,p-i,x-1) C_{p-1}^{i-1} \cdot i^{-1}$

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
#define mod 998244353
typedef long long ll;
il int gi(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
il int pow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret=1ll*ret*x%mod;
        x=1ll*x*x%mod;y>>=1;
    }
    return ret;
}
int CC[5110][5110];
il int C(int n,int m){
    if(n<m||n<0||m<0)return 0;
    return CC[n][m];
}
il int solve(int n,int m,int lim){
    if(n==0)return 1;
    if(n<0)return 0;
    int ans=0;
    for(int i=0;i<=m;++i)ans=(ans+1ll*((i&1)?998244352:1)*C(m,i)%mod*C(n-lim*i+m-1,m-1))%mod;
    return ans;
}
int inv[101];
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    CC[0][0]=1;
    for(int i=1;i<=5109;++i){
        CC[i][0]=1;
        for(int j=1;j<=i;++j)CC[i][j]=(CC[i-1][j]+CC[i-1][j-1])%mod;
    }
    int p=gi(),s=gi(),r=gi();
    int ans=0;
    inv[1]=1;for(int i=2;i<=p;++i)inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
    for(int x=r;x<=s;++x)
        for(int i=1;i<=p;++i){
            if((p-i)*(x-1)+i*x<s)continue;
            ans=(ans+1ll*C(p-1,i-1)*solve(s-i*x,p-i,x)%mod*inv[i])%mod;
        }
    printf("%d\n",1ll*ans*pow(C(s-r+p-1,p-1),mod-2)%mod);
    return 0;
}
```

---

## 作者：zcxxnqwq (赞：7)

Mn Zn 昨天考试遇见了组合数容斥求选数方案问题，但发现没有题解详细讲了这个过程，所以来发一篇对萌新比较友好的题解 qwq。

这道题的思路其它题解都讲得差不多了，枚举最高分 $m$ 及得到最高分的人数 $k$，若设 $f(n,m,s)$ 表示在 $[0,m]$ 之间选 $n$ 个数，使其和为 $s$ 的方案数，则答案为 $ans=\sum\limits_{m=r}^s \sum\limits_{k=1}^n \dfrac{\dbinom{n-1}{k-1}\times f(n-k,m-1,s-k\times m)}{k}$，问题就变为了怎么求 $f(n,m,s)$。

如果是在 $[0,+\infty)$ 里选数，那就是经典的插板法，先把 $s$ 加上 $n$，强制 $n$ 个数先选一个 $1$，方案数就是 $\dbinom{s+n-1}{n-1}$，那么对于加上 $[0,m]$ 的限制的情况，考虑枚举不符合限制的数的个数进行容斥：

假设当前枚举到 $k$，即有至少 $k$ 个数（以下称为第一类数） $\in[m+1,+\infty)$，至多 $n-k$ 个数（以下称为第二类数）$\in[0,m]$，先将第一类数整体减去 $m+1$，得到 $s=s-k\times(m+1)$，再将所有数整体加 $1$，得到 $s=s-k\times(m+1)+n$。那么当前问题变为有 $k$ 个数 $\in[1,+\infty)$，$n-k$ 个数 $\in[1,m+1]$，和为 $s-k\times(m+1)+n$ 的方案数。由于是至少 $k$ 个不满足限制，那么就又可以插板法，为 $\dbinom{s-k\times(m+1)+n-1}{n-1}$。

考虑上 $n$ 个数里选 $k$ 个数的不同方案，即可得到 $f(n,m,s)=\sum\limits_{k=0}^n (-1)^k \dbinom{n}{k}\times \dbinom{s-k\times(m+1)+n-1}{n-1}$。

对于本题，用 $ans$ 除以总方案数 $\dbinom{s-r+n-1}{n-1}$，就可以在 $O(n^2s)$ 的复杂度里求出本题答案了。组合数里出现负数的状态都不成立，可以提前判掉。

代码就很简单了 qwq。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i=(s);i<=(e);++i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=105,M=10005,mod=998244353,qaq=1e4;
int jc[M],inv[M];
int n,s,r;
inline int ksm(int x,int y){
    int res=1;
    for(;y;y>>=1){
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
    }
    return res;
}
inline int C(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return 1ll*jc[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void add(int &x,int y){x+=y;if(x>=mod) x-=mod;if(x<0) x+=mod;}
inline int f(int n,int r,int s){
    if(!n&&!s) return 1;
    int ans=0;
    ff(k,0,n){
        int op=(k&1)?-1:1,tmp=s-k*(r+1)+n-1;
        if(tmp<n-1) break;
        add(ans,1ll*op*C(n,k)*C(tmp,n-1)%mod);
    }
    return ans;
}
signed main(){
    n=read(),s=read(),r=read();
    jc[0]=1;
    ff(i,1,qaq) jc[i]=1ll*jc[i-1]*i%mod;
    inv[qaq]=ksm(jc[qaq],mod-2);
    for(int i=qaq-1;i>=0;--i) inv[i]=inv[i+1]*(i+1ll)%mod;
    int ans=0;
    ff(rr,r,s) ff(k,1,n){
        if(k*rr>s) break;
        add(ans,1ll*f(n-k,rr-1,s-k*rr)*C(n-1,k-1)%mod*ksm(k,mod-2)%mod);
    }
    int tot=C(s-r+n-1,n-1);
    printf("%lld\n",1ll*ans*ksm(tot,mod-2)%mod);
}
```


---

## 作者：A_Pikachu (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1096E)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf1096e-the-top-scorer)）

$\Large\mathscr{P}\mathit{art}\,\,1\;\;\text{基本思路}$

概率等于合法方案数除以总方案数。不妨令小明为一号选手。

先算总方案数。由于包括一号在内所有选手的得分和为 $s$，而一号得分至少为 $r$，其余选手得分至少为 $0$，那么总方案数就是 $\dbinom{s-r+p-1}{p-1}$，即把多出的分数分成 $p$ 份。

既然题目特地提醒同分时的概率要平分，设有 $y$ 个获得最高分 $x$ 的选手，则还要满足剩下 $p-y$ 个选手的得分总和为 $s-xy$ 且每个选手不超过 $x-1$ 分的条件。

注意到容易算得没有得分上限时总方案数为 $\dbinom{s-xy+p-y-1}{p-y-1}$，考虑此时不满足限制的方案数。设至少有 $i$ 位选手超过限制，即至少 $i$ 个人都得到了至少 $x$ 分，方案数为 $\dbinom{s-xy-ix+p-y-1}{p-y-1}$。又因为这个定义是逐层包含关系的，所以可以使用容斥计算总合法方案数，容斥系数为 $(-1)^{i}\dbinom{p-y}{i}$，可得算式 $\displaystyle\sum_{i=0}^{p-y} (-1)^{i}\dbinom{p-y}{i}\dbinom{s-xy-ix+p-y-1}{p-y-1}$。

枚举 $x$，$y$，先从剩下 $p-1$ 个人中选 $y-1$ 个最高分，再平分概率，可得答案为 $\displaystyle\sum_{x=r}^{s}\sum_{y=1}^{p}\dbinom{p-1}{y-1}\frac{1}{y}\sum_{i=0}^{p-y} (-1)^{i}\dbinom{p-y}{i}\dbinom{s-xy-ix+p-y-1}{p-y-1}$。预处理组合数（或阶乘），然后直接计算即可。

$\Large\mathscr{P}\mathit{art}\,\,2\;\;\text{Code}$

```cpp
#include <cstdio>
const int P=105,S=5005,MOD=998244353;
int p,s,r,ans,inv[P],c[S+P][S];
void pre(){
	c[0][0]=c[1][0]=inv[1]=1;
	for(int i=1; i<=s+p; i++,c[i][0]=1) for(int j=1; j<=i&&j<=p; j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	for(int i=2; i<=p; i++) inv[i]=(-1LL*inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
}
int cal(int n,int m,int x){
	if(!n) return 1;
	int res=0,xs=1;
	for(int i=0; i<=m&&i*x<=n; i++,xs*=-1) res=(res+1LL*xs*c[m][i]%MOD*c[n-i*x+m-1][m-1]%MOD+MOD)%MOD;
	return res;
}
int qpow(int x,int p=MOD-2){
	register int y=1;
	while(p){
		if(p&1) y=1LL*x*y%MOD;
		x=1LL*x*x%MOD;
		p>>=1;
	}
	return y;
}
int main(){
	scanf("%d%d%d",&p,&s,&r); pre();
	for(int x=r; x<=s; x++) for(int y=1; y<=p&&x*y<=s; y++) if((p-y)*(x-1)+x*y>=s)ans=(ans+1LL*c[p-1][y-1]*inv[y]%MOD*cal(s-x*y,p-y,x)%MOD)%MOD;
	ans=1LL*ans*qpow(c[s-r+p-1][p-1])%MOD;
	printf("%d\n",ans);
	return 0;
}
```

时间复杂度 $\Theta(p^2s)$。

---

## 作者：LJC00118 (赞：1)

$ n $ 为人数，总分为 $ s $，自己的下限 $ r $ , $ c $ 为组合数，枚举有多少个人跟自己得分相同，自己的得分 $ j $，对答案的贡献是 $ C[n - 1][i - 1] * \frac{1}{i} * calc(n - i, s - i * j, j) $

$ calc( n, s, big ) $ 表示有 $ n $ 个人，总分为 $ s $，每个人的得分都 $ < big $ 的方案数，这个可以通过容斥求出

总方案数可以用隔板法求出是 $ C[s - r + n - 1][n - 1] $，乘上这个的逆元即可

```cpp
#include <bits/stdc++.h>
#define CIOS ios::sync_with_stdio(false);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> ";
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename T>
inline void read(T &f) {
	f = 0; T fu = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') fu = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
	f *= fu;
}

template <typename T>
void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + 48);
	else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
	print(x); putchar(t);
}

const int N = 5005, md = 998244353;

inline int mul(int x, int y) { return (ll)x * y % md; }

inline int add(int x, int y) {
	x += y;
	if(x >= md) x -= md;
	return x;
}

inline int sub(int x, int y) {
	x -= y;
	if(x < 0) x += md;
	return x;
}

inline int fpow(int x, int y) {
	int ans = 1;
	while(y) {
		if(y & 1) ans = mul(ans, x);
		y >>= 1; x = mul(x, x);
	}
	return ans;
}

int C[N + 105][105], inv[N];
int n, s, r, ans;

int calc(int n, int s, int big) {
	if(n == 0) return s == 0;
	int ans = 0;
	for(register int i = 0, opt = 1; i <= n && i * big <= s; i++, opt = md - opt)
		ans = add(ans, mul(opt, mul(C[s - i * big + n - 1][n - 1], C[n][i])));
	return ans;
}

int main() {
	read(n); read(s); read(r);
	for(register int i = 0; i <= s + n; i++) {
		C[i][0] = 1;
		for(register int j = 1; j <= i && j <= n; j++)
			C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
	}
	for(register int i = 1; i <= n; i++) inv[i] = fpow(i, md - 2);
	for(register int i = 1; i <= n; i++) {
		for(register int j = r; j <= s; j++) {
			if(s - i * j < 0) break;
			ans = add(ans, mul(mul(C[n - 1][i - 1], calc(n - i, s - i * j, j)), inv[i])); 
		}
	}
	print(mul(ans, fpow(C[s - r + n - 1][n - 1], md - 2)), '\n');
	return 0;
}

// Rotate Flower Round.
```

---

## 作者：zztqwq (赞：0)

推式子题，过了之后神清气爽。

首先把概率转化为合法情况除以总情况，那这题就变成了一道计数题。

先考虑 dp。发现朴素的 dp 是 $\mathcal O(ps^3)$ 的，前缀和优化一下大概是 $\mathcal O(ps^2)$ 的，但这个 2e9 的东西显然过不了。

那就直接算！

枚举自己的分数 $i$，然后枚和自己得分一样的人的个数 $j$，这种情况对于答案的贡献是 $\frac 1jF(i,j)$，$F(i,j)$ 表示合法情况的个数。

$F(i,j)$ 大概没有办法用组合数直接算，考虑把它容斥出来。

设 $f(k)$ 表示至少 $k$ 个人得分大于等于 $i$ 的情况数量，那么根据插板法不难得出：

$$
f(k)=\binom{s-i-ij-ik+p-2-j}{p-2-j}
$$

$F(i,j)$ 就是：

$$
\begin{aligned}F(i,j)&=\sum_{k=0}^{p-1-j}(-1)^kf(k)\binom{p-1-j}{k}\\&=\sum_{k=0}^{p-1-j}(-1)^k\binom{s-i-ij-ik+p-2-j}{p-2-j}\binom{p-1-j}{k}\end{aligned}
$$

可以 $\mathcal O(p)$ 算出，总复杂度 $\mathcal O(p^2s)$，这题就做完啦。

代码（头文件省略）：

```cpp
const int N=2e5+10,mod=998244353;
int qpow(int a,int n)
{
	int ans=1;
	while(n){
		if(n&1)ans=1ll*a*ans%mod;
		a=1ll*a*a%mod;
		n>>=1;
	}
	return ans;
}
int fac[N],ifac[N];
int binom(int n,int m)
{
	if(n<0||m<0||n<m)return 0;
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int main()
{
	fac[0]=1;for(int i=1;i<=2e5;i++)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[200000]=qpow(fac[200000],mod-2);
	for(int i=2e5-1;i>=0;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	int p=read(),s=read(),r=read();
	if(p==1)return puts("1"),0;
	//p 选手，s 总和，得分>=r
	int tot=binom(s-r+p-1,p-1),ans=0;
	for(int i=r;i<=s;i++)
	{
		for(int j=0;j<=p-1;j++)//j个人的得分=i
		{
			int sum=0;
			if(j==p-1)
			{
				if(p*i==s)
					sum=1;
			}
			else
			{
				for(int k=0;k<=p-1-j;k++)
				{
					if(k&1)
						sum-=1ll*binom(p-1-j,k)*binom(s-i-i*j-i*k+p-2-j,p-2-j)%mod;
					else
						sum+=1ll*binom(p-1-j,k)*binom(s-i-i*j-i*k+p-2-j,p-2-j)%mod;
					sum=(sum%mod+mod)%mod;
				}
			}
			sum=1ll*sum*binom(p-1,j)%mod;
			sum=1ll*sum*qpow(j+1,mod-2)%mod;
			// printf("i=%d, j=%d, sum=%d\n",i,j,sum);
			ans+=sum,ans%=mod;
		}
	}
	// printf("ans=%d\n",ans);
	// printf("tot=%d\n",tot);
	ans=1ll*ans*qpow(tot,mod-2)%mod;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：RainFestival (赞：0)

感谢 @realskc

$A=$ 第一个 $\ge k$ 的方案总数。

$B=$ 第一个 $\ge k$ 的并且第一个赢的方案总数。

$C=$ 有 $\ge k$ 的人方案总数。

$D=$ 没有 $\ge k$ 的人方案总数。

$S=$ 没有任何限制的方案总数。

考虑 $C$ 的某一种方案 $p$。

假设 $p$ 有 $x$ 个最大值，则 $p$ 的所有循环移位总共会对 $B$ 贡献 $x$ 次，对 $C$ 贡献 $nx$ 次。

所以 $B=\frac{C}{n}$。

所以答案就是 $\frac{B}{A}=\frac{C}{nA}$。

然后 $C=S-D$，所以答案就是 $\frac{S-D}{nA}$。

$S$ 插板一下，$A$ 插板一下。

$D$ 的 $\rm OGF$ 是 $(\sum\limits_{0}^{k-1}x^i)^n$

然后这个东西就是 $(\frac{1-x^k}{1-x})^n$

然后分子分母算一下就好了。

$\mathcal O(n+\log mod)$ 

```
#include<cstdio>
#include<algorithm>
#include<assert.h>
#define mod 998244353
int n,m,k;
long long fac[10000005],inv[10000005],s=0,ss=0;
long long fp(long long x,int y){return (y&1?x:1ll)*(y>>1?fp(x*x%mod,y>>1):1ll)%mod;}
void pre(int n)
{
	fac[0]=inv[0]=1;
	for (int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	inv[n]=fp(fac[n],mod-2);
	for (int i=n-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
long long c(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	if (k==0) return printf("%lld\n",fp(n,mod-2)),0;
	if (n==1) return puts("1"),0;
	pre(2*std::max(n,m));
	long long s=c(m+n-1-k,n-1),ps=c(m+n-1,n-1);
	long long ss=0;
	for (int i=0;i<=n;i++)
	{
		long long nd=m-i*k;
		if (nd<0) break;
		long long ans=c(n,i)*c(n+nd-1,nd);
		if (i&1) ss=(ss-ans+mod)%mod;
		else ss=(ss+ans)%mod;
	}
	ss=(ps-ss+mod)%mod;
	printf("%lld\n",ss*fp(s,mod-2)%mod*fp(n,mod-2)%mod);
	return 0;
}
```

注意：由于版权问题，本博客不予显示。

---

## 作者：Azazеl (赞：0)

### CF1096E The Top Scorer



#### 题意

>  $~~~~$ 给出数列 $p$ 个人各自的 $a_i$ 表示得分, $\sum a_i=s$ ，求在第一个数 $\geqslant r$ 的情况下，它是最大值的概率。若有其他数与它的值相同，最大值会认为是等概率选择了其中的一个.（即若不包括它在内有 $k$ 个最大值，则概率 $/k$ ）

---

#### 题解

$~~~~$ ~~不会吧不会吧，这题CF上只有2500~~。受到专题训练影响直接想 $\texttt{DP}$ ，然后发现时空都会爆，状态具体怎么定义出来都成问题。  

$~~~~$ 否决了概率 $\texttt{DP}$,那现在我们只能直接计算概率了。  

$~~~~$ 总的方案数很好求，是：  
$$
\begin{pmatrix}
s-r+n-1\\
n-1
\end{pmatrix}
$$
$~~~~$ **解释**： 上式可以用插板法可以推出，相当于把 $s-r$ 分（第一个人必须有 $r$）分配给 $p$ 个人。但注意分数可以是 $0$ ，所以每个人插板后会有新空隙。 

$~~~~$ 所以我们来求合法的方案数。

$~~~~$ 枚举有 $i$ 人（包括 $1$ 自己在内）同最高分 $x$ 。那我们有 $\begin{pmatrix}p-1\\i-1\end{pmatrix}$ （ $1$ 必定要被选）种选人方案。  

$~~~~$ 接下来是求另一个子问题： $p-i$ 人分 $s-ix$ 分，每人可以分到 $[0,x-1]$ 分的方案数。  

$~~~~$ 为方便，下文令:$n=s-ix,m=p-i$.

$~~~~$ 方案数无法直接正面求到，那我们是否可以考虑反面求呢？  

$~~~~$ 考虑优先给 $m$ 个人都安排上 $x$ 分，那这样就可以求出 $m$ 个人都不满足条件的方案数。以此类推算出$[0,m-1]$ 时的方案数$\dots\dots$了吗？ 

$~~~~$ 并不是的，我们发现在求 $m-1$ 人不合法时，是包括 $m$ 人合法的情况的，也就是说我们每次求出来的应该是：**至少** $k$ 个人不合法的方案数。  

$~~~~$ 等等，提到了至少？那我们就自然而然想到容斥了。  

$~~~~$ 考虑当**至少**有 $k\in[0,m]$ 人不合法时的方案数：

- 有容斥系数：$(-1)^k\times\begin{pmatrix}m\\k\end{pmatrix}$ ;
- 综合之前的策略，有答案：$\begin{pmatrix}n-kx+m-k-1\\k\end{pmatrix}$ .

$~~~~$ 因此这个子问题的答案是：  
$$
\sum_{k=0}^{m} (-1)^k\times \begin{pmatrix}m\\k\end{pmatrix}\times \begin{pmatrix}n-kx+m-k-1\\k\end{pmatrix}
$$
$~~~~$ 综上，总的答案就是：  
$$
\sum_{x=r}^{s}\sum_{i=1}^{p} \begin{pmatrix}p-1\\i-1\end{pmatrix}\times (\sum_{k=0}^{m} (-1)^k\times \begin{pmatrix}m\\k\end{pmatrix}\times \begin{pmatrix}n-kx+m-k-1\\k\end{pmatrix})
$$
$~~~~$ 但这只是算到了合法方案数，而当 $i$ 人同分时，概率会变为原式的 $\dfrac{1}{i}$ ，因此在求答案时要在上式每次 $\times \dfrac{1}{i}$ .

$~~~~$ 此外还要注意当 $i=p$ 时需要特判 $ix=s$ 是否成立，否的话答案为 $0$ ，否则答案为 $1$ (记得这是方案数，最后还是要 $\times \dfrac{1}{i}$) 

$~~~~$ 最后除以总方案数就是概率了。  

$~~~~$ 另外算一下 $(n-kx+m-k-1)_{max}$ 就会发现组合数底数要递推到 $5099$ 而不是 $5000$.

---

#### 代码

(~~由于改组合数范围的时候修改借鉴了神兔的代码，所以可能会有亿点点像~~)

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
const ll MOD=998244353;
ll C[5105][5105];//C[i][j]:j选i
ll p,s,r;
inline ll qpow(ll a,ll b)
{
	ll ret=1;
	while(b)
	{
		if(b&1) ret=ret*a%MOD;
		b>>=1;
		a=a*a%MOD;
	}
	return ret;
}
ll calc(ll n,ll m,ll x)//子问题求解
{
	ll ret=0;
	for(ll k=0;k<=m&&x*k<=n;k++)
	{
		ll tmp=C[k][m]*C[m-1][n+m-1-k*x]%MOD;
		ret+=(k&1)?-tmp:tmp;
	}
	return ((ret%MOD)+MOD)%MOD;
}
int main() {
	C[0][0]=1;
	for(ll i=1;i<=5100;i++) 
	{
		C[i][i]=C[0][i]=1;
		for(ll j=1;j<=i;j++) C[j][i]=(C[j-1][i-1]+C[j][i-1])%MOD;	
	}
	ll ans=0;
	scanf("%lld %lld %lld",&p,&s,&r);
	for(ll x=r;x<=s;x++)
	{
		for(ll i=1;i<=p;i++)
		{
			if(i==p) (ans+=(i*x==s?qpow(i,MOD-2):0))%=MOD;//特判 i=p
			else (ans+=(C[i-1][p-1]*calc(s-i*x,p-i,x)%MOD*qpow(i,MOD-2)%MOD))%=MOD;
		}
	}
	printf("%lld",ans*qpow(C[p-1][s-r+p-1],MOD-2)%MOD);
	return 0;
} 
```

---

## 作者：瞬闪影 (赞：0)

https://www.cnblogs.com/2017SSY/p/10207411.html

厚颜无耻的丢一个转向自己博客的链接2333
=￣ω￣=

其实再整也就是搬运了233
设 g(s,p,m)=（在一场总分和s，玩家数p的游戏中，没有人得分超过m的合法状态数）

这东西dp起来蛮简单（的吧？），但是你会发现他的复杂度有点难以接受。。。但这至少给我们一个启示？

遇到获胜等设计随机状态中涉及最大值的问题，可以试着转化成一些“不超过”问题的组合
我们试着用数学方法解决这个问题吧

 ![](https://img2018.cnblogs.com/blog/1271158/201901/1271158-20190102102941360-1327953650.png)

这个 这个公式出自隔板法和容斥原理，请允许我解释一下

首先看容斥，简单来说就是想计算 所有情况-至少一个人超过m+至少两个人超过m-至少三个人超过m……

然后看隔板法，如何计算有i个人超过m呢？先选出i个人C(p,i)，给每个人先分配m+1个，就变成了箱子内剩余数可以为零的经典隔板问题

这个式子在有预处理的帮助下的代价是O(p)的

有了g之后呢，答案f貌似就很好计算了，搬个公式大家自己体会吧~

![](https://img2018.cnblogs.com/blog/1271158/201901/1271158-20190102104539864-1132229735.png)


总复杂度：O(s*p2)

```cpp
#include<cstdio>
#define ll long long
#define mod 998244353
using namespace std;
ll ksm(ll x,ll t){ll ans=1;for(;t;t>>=1,x=(x*x)%mod)if(t&1)ans=(ans*x)%mod;return ans;}
int p,s,r;
ll fac[6005],invf[6005];
void pre(){
	fac[0]=1;
	for(int i=1;i<=p+s;i++)fac[i]=(fac[i-1]*i)%mod;
	invf[p+s]=ksm(fac[p+s],mod-2);
	for(int i=p+s-1;i>=0;i--)invf[i]=(invf[i+1]*(i+1))%mod;
}
ll C(ll n,ll m){
	if(n<0||m<0||m>n)return 0;
	return ((fac[n]*invf[n-m])%mod*invf[m])%mod;
}
ll ans;
ll g(ll s,ll p,ll m){
	if(p==0&&s==0)return 1;
	ll tot=0;
	for(int i=0,t=1;i<=p;i++){
		tot+=t*(C(p,i)*C(s+p-1-i*(m+1),p-1)%mod);
		tot=(tot+mod)%mod;
		t*=-1;
	}
	return tot;
}
int main(){
	scanf("%d%d%d",&p,&s,&r);
	pre();
	for(int t=r;t<=s;t++)
	for(int q=1;q<=p;q++){
		ans+=((C(p-1,q-1)*ksm(q,mod-2)%mod)*g(s-q*t,p-q,t-1))%mod;
		ans%=mod;
	}
	ans*=ksm(C(s+p-1-r,p-1),mod-2);
	ans%=mod;
	printf("%lld",ans);
	return 0;
}
```

---

