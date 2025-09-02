# Codeword

## 题目描述

The famous sculptor Cicasso is a Reberlandian spy!

These is breaking news in Berlandian papers today. And now the sculptor is hiding. This time you give the shelter to the maestro. You have a protected bunker and you provide it to your friend. You set the security system in such way that only you can open the bunker. To open it one should solve the problem which is hard for others but is simple for you.

Every day the bunker generates a codeword $ s $ . Every time someone wants to enter the bunker, integer $ n $ appears on the screen. As the answer one should enter another integer — the residue modulo $ 10^{9}+7 $ of the number of strings of length $ n $ that consist only of lowercase English letters and contain the string $ s $ as the subsequence.

The subsequence of string $ a $ is a string $ b $ that can be derived from the string $ a $ by removing some symbols from it (maybe none or all of them). In particular any string is the subsequence of itself. For example, the string "cfo" is the subsequence of the string "codeforces".

You haven't implemented the algorithm that calculates the correct answers yet and you should do that ASAP.

## 说明/提示

In the first event words of the form "a?" and "?a" are counted, where ? is an arbitrary symbol. There are $ 26 $ words of each of these types, but the word "aa" satisfies both patterns, so the answer is $ 51 $ .

## 样例 #1

### 输入

```
3
a
2 2
1 bc
2 5
```

### 输出

```
51
162626
```

# 题解

## 作者：shiroi (赞：10)

### Description

给定一个字符串 $s$ 和一个长度 $l$ ，问有多少个长度为 $l$ 的只包含小写字母的串 $t$，使得其中有一个子序列为 $s$ 。  共有 $10^5$ 次询问，保证 $\sum len_t \le 10^5$。




### Solution

首先考虑一个暴力 dp 做法。

我们首先定义题目中给定的字符串 $s$ 为模板串，需要求方案数的串 $t$ 为匹配串 。令 $f(i,j)$ 表示包含模板串 $s$ 前 $i$ 位，匹配长度 $n$ 的字符串个数。考虑到如果取了 $s$ 的一个字符放在新串的末尾，则方案数为 $f(i-1,j-1)$ ，不取则为 $f(i,j-1) \times 25$ 。转移十分显然：
$$
f(i,j)=f(i,j-1) \times 25 + f(i-1,j-1)
$$
观察上式不难看出，答案只与模板串长度 $len$ 和 $l$ 有关而和字符串内容无关。$f(i,j)$ 也可以理解为模板串长为 $i$ ，匹配串长为 $j$ 的方案数。

定义 $s$ 中的每一个字符 $s_i$ 在 $t$ 中第一次匹配到的位置为 $p_i$ ，那么 $p_i$ 为在满足了前 $i-1$ 个匹配过程之后，在匹配串中最早出现的 $s_i$ 的出现位置。

我们重新考虑上面的dp过程。如果当前考虑到的 $s_i$ 没有被填入匹配串的第 $j$ 位，最后一位可以填任意字符，则方案显然有 $f(i,j-1) \times 26$ 个。如果 $s_i$ 填入了位置 $j$ ，那么这样的数量有 ${\dbinom{j-1}{i-1} \times 25^{j-i}}$ 个。这部分相当于已知最后一位填入 $s_i$ ，需要求出模板串的前 $i-1$ 位匹配上匹配串的前 $j-1$ 位的方案数。其中选择填入 $s$ 中字符位置的方案有 $\dbinom{j-1}{i-1}$ ，没有被填入字符的部分每个位置都只有 $25$ 种可能，因为不能与后一个匹配上的字符冲突，方案有  $25^{j-i}$ 个。因此可以得到：
$$
f(i,j)=\dbinom{j-1}{i-1} \times 25^{j-i}+f(i,j-1) \times 26
$$
此时对于单个给定的 $len$ 求解复杂度为 $O(n)$ 。考虑到给定字符串 $len$ 的总和大小在 $10^5$ 级别，$len$ 的种类数量就大概在 $O(\sqrt{10^5})$ 级别。因此可以对每种长度记忆化来进行处理。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1,c=getchar();
	while(c<48) c=='-'&&(f=-1),c=getchar();
	while(c>47) x=x*10+c-'0',c=getchar();
	return x*f;
}

const int mod = 1e9+7;
const int MAXN = 100005;
std::vector<int> f[MAXN];
int fac[MAXN],vis[MAXN],ifac[MAXN],pw[MAXN];
int n,k,lim; char str[MAXN];

inline void init(int n)
{
	for(int i=pw[0]=fac[0]=1; i<=n; ++i)
	{
		fac[i]=1ll*fac[i-1]*i%mod;
		pw[i]=25ll*pw[i-1]%mod;
	}
	ifac[0]=ifac[1]=1;
	for(int i=2; i<=n; ++i)
		ifac[i]=1ll*(mod-mod/i)*ifac[mod%i]%mod;
	for(int i=2; i<=n; ++i)
		ifac[i]=1ll*ifac[i]*ifac[i-1]%mod;
}

inline int cat(int n,int k)
{return n<k?0:1ll*fac[n]*ifac[k]%mod*ifac[n-k]%mod;}

inline int calc(int n,int k)
{return 1ll*cat(n,k)*pw[n-k]%mod;}

inline void sol(int n)
{
	if(!vis[k])
	{
		vis[k]=1; f[k].push_back(0);
		for(int j=1; j<=lim; ++j)
			f[k].push_back((calc(j-1,k-1)+26ll*f[k][j-1]%mod)%mod);
	}
	printf("%d\n",f[k][read()]);
}

int main(int argc, char const *argv[])
{
	n=read(); init(lim=1e5);
	scanf("%s",str); k=strlen(str);
	for(int i=1; i<=n; ++i)
		(read()==1)?(scanf("%s",str),k=strlen(str)):(sol(k),1);
	return 0;
}
```



---

## 作者：绝顶我为峰 (赞：8)

遇事不决，先考虑一个暴力 dp。

记 $dp_{i,j}$ 表示前 $i$ 位最多可以匹配 $s$ 的 $j$ 个字符的方案数，转移枚举下一位填的值 $c$，然后分类讨论：

- $j<|s|$，那么只有 $c=s_{j+1}$ 的时候会转移到 $dp_{i+1,j+1}$，否则转移到 $dp_{i+1,j}$，于是有 $dp_{i+1,j+1}\leftarrow dp_{i,j},dp_{i+1,j}\leftarrow25dp_{i,j}$；

- $j=|s|$，显然填什么都不会再转移了，所以 $dp_{i+1,j}\leftarrow26dp_{i,j}$。

直接做每次询问的复杂度是 $O(n|s|)$，显然过不了。

这是一个满足一些限制的字符串计数问题。这种 dp 本质上是在设计一个自动机，可以识别字符串，有若干个起点和若干个终点，答案就是从一个起点出发走恰好（也可能是小于或大于，具体看题目要求）$n$ 步到达一个终点的路径计数。这类问题还有一个更广为人知的名字叫做 $\mathrm{dp\ of\ dp}$，也就是 dp 套 dp。

回到这一题，本质上题目要求的就是从点 $1$ 出发，走恰好 $n$ 步到达点 $m$ 的路径计数。画出这一题的自动机，大概长成下面这样（自环上的数字表示自环的数量）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wc28n02k.png)

可以发现除了点 $m$ 其他点的转移是完全相同的，所以答案只与 $s$ 完成匹配的位置有关。

有了这个结论之后计算答案，直接枚举完成匹配的位置：

$$f(m,n)=\sum\limits_{i=m}^n\dbinom{i-1}{m-1}25^{i-m}26^{n-i}=\sum\limits_{i=0}^{n-m}\dbinom{i+m-1}{m-1}25^i26^{n-m-i}$$

很遗憾，虽然这个式子长得很像二项式定理，但是这个组合数不是很优美，只能枚举 $i$ 暴力计算。

这个做法没有前途了吗？题目限制了 $\sum |s|\leq 10^5$，也就是说本质不同的 $|s|$ 的量是 $O(\sqrt V)$ 级别的。同时注意到 $f(m,n)=26f(m,n-1)+\dbinom{n+m-1}{m-1}25^{n-m}$，因此对 $1\leq i\leq n$ 和一个给定的 $m$，$f(m,i)$ 是可以在 $O(n)$ 复杂度内全部算出来的。

于是直接对 $O(\sqrt V)$ 个不同的 $|s|$ 把 $f(|s|,i)$ 全部算出来即可，时间复杂度 $O(n\sqrt V)$。

具体实现的时候是离线的，因为离线的空间复杂度是线性的而在线不是。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
const int lim=1e5,mod=1e9+7;
string s;
int n,len,ans[100001],cnt,fac[100001],inv[100001];
vector<pair<int,int> > v[100001];
inline int pw(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1)
            res=1ll*res*a%mod;
        b>>=1;
        a=1ll*a*a%mod;
    }
    return res;
}
inline int c(int x,int y)
{
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main()
{
    fac[0]=inv[0]=1;
    for(int i=1;i<=lim;++i)
        fac[i]=1ll*fac[i-1]*i%mod;
    inv[lim]=pw(fac[lim],mod-2);
    for(int i=lim-1;i;--i)
        inv[i]=1ll*inv[i+1]*(i+1)%mod;
    cin>>n>>s;
    len=s.length();
    for(int i=1;i<=n;++i)
    {
        int opt;
        cin>>opt;
        if(opt==1)
        {
            cin>>s;
            len=s.length();
        }
        else
        {
            int x;
            cin>>x;
            v[len].emplace_back(x-len,++cnt);
        }
    }
    for(int i=1;i<=lim;++i)
        if(!v[i].empty())
        {
            sort(v[i].begin(),v[i].end());
            int p=0,res=0,w=1;
            for(auto j:v[i])
            {
                for(;p<=j.first;++p)
                {
                    res=(26ll*res%mod+1ll*c(p+i-1,i-1)*w%mod)%mod;
                    w=25ll*w%mod;
                }
                ans[j.second]=res;
            }
        }
    for(int i=1;i<=cnt;++i)
        cout<<ans[i]<<'\n';
    return 0;
}
```



---

## 作者：bsdsdb (赞：4)

题意：$q$ 次询问，每次询问给一个字符串 $s$ 和整数 $L$，问有多少个长度为 $L$ 的字符串有子序列 $s$。$q,L,\sum|s|\le10^5,|\Sigma|=26,\mathrm{mod}=10^9+7$。

设 $n:=|s|$。假设现在匹配了前 $t$ 个字符，自己选的字符串填了 $i-1$ 个字符，那么我们可以选择第 $i$ 个字符不匹配，方案数 $x:=|\Sigma|-1$；匹配，方案数为 $1$。特别的，如果 $t=n$，那么只能不匹配，方案数为 $x+1$。假设 $s_n$ 是在第 $j$ 个字符匹配的，前面的选法为 $\binom{j-1}{n-1}$，那么：

$$
\begin{aligned}
f(n,L)=&\sum_{j=n}^L(x+1)^{L-j}\binom{j-1}{n-1}x^{j-n}\\
=&\sum_{j=n}^L\sum_{i=0}^{L-j}\binom{L-j}ix^i\binom{j-1}{n-1}x^{j-n}\\
=&\sum_{j=0}^{L-n}\sum_{i=0}^{L-j-n}\binom{L-j-n}i\binom{j+n-1}{n-1}x^{i+j}\\
=&\sum_{k=0}^{L-n}x^k\sum_{i+j=k}\binom{L-j-n}i\binom{j+n-1}j\\
=&\sum_{k=0}^{L-n}x^k\sum_{j=0}^k\binom{L-j-n}{k-j}\binom{j+n-1}j\\
\xlongequal{\text{Chu-Vandermonde}}&\sum_{k=0}^{L-n}x^k\binom Lk\\
=&(x+1)^L\bmod x^{L-n+1}
\end{aligned}
$$

那我要是不知道 Chu-Vandermonde 呢？想想怎么让 $x+1$ 的贡献没掉？想象 $s_n$ 匹配完之后，我们对后面的不存在的字符仍然有「匹配」与「不匹配」两种选择，只是匹配到第 $[n,L]$ 个字符都能为答案贡献。也就是说我们任选 $[n,L]$ 个字符匹配，每种选法中没选上的贡献一个 $x$。所以：

$$
\begin{aligned}
f(n,L)=&\sum_{i=n}^L\binom Lix^{L-i}\\
=&\sum_{i=0}^{L-n}\binom Lix^i\\
=&(x+1)^L\bmod x^{L-n+1}
\end{aligned}
$$

注意这个 $\bmod$ 是在多项式意义下的。任意模数多项式快速幂单点求值，怎么玩？别急，题目有 $\sum|s|\le10^5$，也就是 $\sum n\le10^5$，也就是不同的 $n$ 只会有 $\Omicron(\sqrt{\sum n})$ 个。如果对于每个 $n$ 能 $\Omicron(L)$ 时间求出 $\{f(n,i)\}_{i=n}^L$ 也是可以的。所以往递推的方向想一想：

$$
\begin{aligned}
f(n,L+1)=&(x+1)^{L+1}\bmod x^{L-n+2}\\
=&\left(\left((x+1)^L\bmod x^{L-n+3}\right)\cdot(x+1)\right)\bmod x^{L-n+2}\\
=&\left(\left((x+1)^L\bmod x^{L-n+1}+x^{L-n+1}\left[x^{L-n+1}\right](x+1)^L\right)\cdot(x+1)\right)\bmod x^{L-n+2}\\
=&\left(\left(f(n,L)+\binom L{n-1}x^{L-n+1}\right)\cdot(x+1)\right)\bmod x^{L-n+2}\\
=&\left(f(n,L)+\binom L{n-1}x^{L-n+1}\right)\cdot(x+1)-\binom L{n-1}x^{L-n+2}\\
=&(x+1)f(n,L)+\binom L{n-1}x^{L-n+1}\\
=&26f(n,L)+\binom L{n-1}25^{L-n+1}\\
f(n,n)=&1
\end{aligned}
$$

或者不用多项式：

$$
\begin{aligned}
f(n,L)=&\sum_{i=0}^{L-n}\binom Lix^i\\
f(n,L+1)=&\sum_{i=0}^{L+1-n}\binom{L+1}ix^i\\
=&\sum_{i=0}^{L+1-n}\binom Lix^i+\sum_{i=1}^{L+1-n}\binom L{i-1}x^i\\
=&f(n,L)+\binom L{L+1-n}x^{L+1-n}+xf(n,L)\\
=&26f(n,L)+\binom L{n-1}25^{L-n+1}\\
\end{aligned}
$$

多项式好像更麻烦，但是这是本人做出这个题用的推导，当时觉得多项式记号简单所以推导一定简单，所以记这了（）

时间复杂度 $\Omicron(\sum n+\sqrt{\sum n}L)$。

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/k6hg6ac8)

一般可以归纳或者生成函数。例如 Chu-Vandermonde 恒等式：

$$
m,n\ge k,\sum_{i+j=k}\binom ni\binom mj=\binom{m+n}k
$$

组合意义证明显然，但是纯数学也能做。

> 考虑两边的生成函数：
> 
> $$
> R(x)\equiv\sum_k\binom{m+n}kx^k\equiv(x+1)^{n+m}\pmod{x^{\min(n,m)+1}}\\
> \begin{aligned}
> L(x)\equiv&\sum_k\sum_{i+j=k}\binom ni\binom mjx^k\\
> \equiv&\sum_k\sum_{i+j=k}\binom nix^i\binom mjx^j\\
> \equiv&\left(\sum_i\binom nix^i\right)\left(\sum_j\binom mjx^j\right)\\
> \equiv&(x+1)^n(x+1)^m\\
> \equiv&(x+1)^{n+m}\pmod{x^{\min(n,m)+1}}
> \end{aligned}
> $$

还有二项式系数递推式

$$
\binom AB=\binom{A-1}B+\binom{A-1}{B-1}
$$

> 考虑把 $B$ 做变量搞生成函数：
> 
> $$
> (x+1)^A=\sum_{B=0}^A\binom ABx^B\\
> (x+1)^{A-1}(x+1)=(x+1)\sum_{B=0}^{A-1}\binom{A-1}Bx^B
> $$
> 
> 对比两边 $B$ 次项系数即得证。

$(x+1)^n$ 的展开可以用 Maclaurin 级数来证，不用组合意义：

> 设 $f(x)=(x+y)^n$，那么根据 Maclaurin 级数
>
> $$
> f(x)=\sum_{i=0}^{\infty}\frac{\frac{\mathrm d^i}{\mathrm dx^i}(0)}{i!}x^i\\
> f^{(i)}(x)=n^{\underline i}(x+y)^{n-i}\\
> f^{(i)}(0)=n^{\underline i}y^{n-i}\\
> \frac{f^{(i)}(0)}{i!}=\begin{aligned}\begin{cases}0,\quad&i>n\\\binom niy^{n-i},\quad&\text{otherwise.}\end{cases}\end{aligned}\\
> f(x)=\sum_{i=0}^n\binom nix^iy^{y-i}
> $$
>
> 

下证上面用到的广义 Chu-Vandermonde 恒等式的一个推广（？）：

$$
\forall X,Y,r:\sum_{i=0}^r\binom{X+i}i\binom{Y-i}{r-i}=\binom{X+Y+1}r
$$

> 考虑归纳。$r=0$ 显然成立。考虑 $r+1$：
> 
> $$
> \begin{aligned}
> &\sum_{i=0}^{r+1}\binom{X+i}i\binom{Y-i}{r+1-i}\\
> =&\sum_{i=0}^{r+1}\binom{X+i}i\left(\binom{Y-i-1}{r-i}+\binom{Y-i-1}{r+1-i}\right)\\
> =&\sum_{i=0}^{r+1}\binom{X+i}i\binom{Y-1-i}{r-i}+\sum_{i=0}^r\binom{X+i}i\binom{Y-1-i}{r+1-i}\\
> =&\binom{X+Y}r+\binom{X+Y}{r+1}\\
> =&\binom{X+Y+1}{r+1}
> \end{aligned}
> $$
> 
> 证毕。

---

## 作者：Lates (赞：3)

第一眼观察到这个数据范围很奇怪，猜想这玩意可能跟根号有关。

先考虑按照第一个匹配上的位置分类？也就是说，两两匹配位置之间不能填第二个匹配字符。方案数为 $25$。

注意到可以枚举一个最后一个匹配位置。因为从此的每个位置方案数为 $26$。

答案可以写作 $\sum\limits_{i=n}^{L} \binom{i}{n}25^{i-n}26^{L-i}$。 

$n$ 为给出子序列的长度。

然后仔细想想上面那个事情。$\sum n\le 10^5$。假设操作中给出了 $T$ 个子序列。

当 $T\le \sqrt{10^5}$，那么对于每个串暴力求出每个 $L$ 的答案是一个根号的复杂度。

当 $T > \sqrt{10^5}$， 那么 $n\le \sqrt{10^5}$，那么对于每个 $n$ 记忆化一下每个 $L$ 的答案就行。

复杂度是一个根号。



---

## 作者：YLWang (赞：3)

好题不火系列

首先我们 ob 出一个结论就是最终答案与当前是哪些字符无关。

这玩意很好理解，你对字符集建立一个双射就行。

然后考虑暴力 dp。定义 $m$ 为副串 $t$ 长度，$n$ 为主串 $s$ 长度。

设 $f_{i,\ j}$：当前 $s$ 填了前 $i$ 位，里面最长的一个子序列到了 $t$ 第 $j$ 位的方案数。

那么有 $f_{i,\ j} =25\cdot f_{i-1,\ j} + f_{i-1,\ j-1}$。第一个是放一个不等于 $t$ 第 $j$ 位的，第二个是放一个等于 $t$ 第 $j$ 位的。

然后你发现这玩意在 $j = m$ 的时候不成立。得把那个 $25$ 改成 $26$ 。

然后你眉头一皱发现这个玩意十分玄妙。

这好像是可以直接拆开进行组合数的。

考虑 $f_{n,\ m}$ 的组合意义。

找到 $s_1 - s_n$ 中任意 $m$ 个位置作为 $t_1 - t_m$。

两个字符中间不能有相同于这右边的字符的字符。

再枚举一手最后一个数的位置，因为后边要 * 26。

答案就是 $ans=\sum\limits_{i=m}^{n}C_{i-1}^{m-1}26^{n-i}25^{i-m}$。

最后发现不同的 $m$ 只有 $\sqrt{100000}$ 种。记忆化即可。

其实 dp 的过程也就是这么一个过程。

这个题还是很妙的。




---

## 作者：ywy_c_asm (赞：2)

首先我们可以想到一个暴力的dp，$dp[i][j]$为已经构造出了答案串的前i个字符，这之前包含的一个最长的为模板串的前缀的子序列是j，我们枚举i这个位置填啥，那显然只能填一种字符才能使匹配的最长前缀扩展一格，其他25种都是没用的，所以$dp[i][j]=dp[i-1][j-1]+25dp[i-1][j]$。

哦，所以，这个答案和这个串本身并没有任何关系，这只与串长$len$有关。

然后值得注意的是他保证了输入的$\sum len<=10^5$，当时做普通字符串题做多了的我并没有注意这个，其实没了这个这题就做不了了……这说明，**$len$的种类是$O(\sqrt {10^5})$级别的**，这个的最极端的情况就是给的是$1,2,3,\cdots,\sqrt {10^5}$，然后我们就可以考虑记忆化一下，对每种$len$都对$n=1$~$10^5$求一遍答案。

求答案的话，我们现在有的这个dp是$O(n^2)$的，需要考虑优化一下，但是可以考虑我们用这个dp如何搞出答案——我们枚举这个模板串在答案串里作为子序列的第一次出现的结尾的位置，后面的就可以任取，即$\sum_{i=len}^n26^{n-i}dp[i-1][len-1]$，换句话说我们要干的事就是保证i-1这个答案串的前缀里必须有一个模板串的$len-1$前缀的子序列，并且不能出现模板串的子序列，然后让i位置放模板串的最后一个字符，这样的话有一个看起来很不对的想法就是枚举出现在前i-1个字符里面的这个长为$len-1$的子序列，然后钦定他就是模板串的$len-1$前缀，但是这样剩下的就不能任意填了，可能会造成同一种方案重复计数，比如我们的模板串是abbab，我想让abba出现在答案串的前缀里，那么显然abbba就包含了两个abba的子序列，会被统计两遍。所以我们不妨这样，**让每个串在他第一次出现的子序列处被统计仅一次**，我们先$C_{i-1}^{len-1}$枚举这个子序列的位置，然后我要钦定他是第一个出现的这个子序列，可以考虑怎么才能不是第一个出现的，就比如上面这个例子，abb?a是第一个出现的，a?bba不是第一个出现的，因为在第一个b和他的前驱a之间还有一个b，会把这个b替换掉，所以我们可以考虑这剩下的$i-len$个位置，他们后面都肯定有第一个是子序列里面的位置，那么这个位置就不能是那个子序列的位置的字符，所以有且仅有25种选择，所以——

$ans=\sum_{i=len}^nC_{i-1}^{len-1}25^{i-len}26^{n-i}$

（说了这么多，式子还是非常简单的……

然后我们变形一下：$26^n\sum_{i=len}^nC_{i-1}^{len-1}\frac{25^{i-len}}{26^{i}}$，然后我们对每种$len$，$O(n)$推一下后面那个式子就好啦~这个是$O(n\sqrt n)$的。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p 1000000007
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	void print(int num) {
	    if (num >= 10)
	        print(num / 10);
	    putchar(num % 10 + '0');
	}
	int dp[450][100001];
	inline int sget() {
	    int n = 1;
	    char c;
	    while ((c = getchar()) || 23333)
	        if (c >= 'a' && c <= 'z')
	            break;
	    while ((c = getchar()) || 23333) {
	        if (c >= 'a' && c <= 'z')
	            n++;
	        else
	            return (n);
	    }
	}
	int id[100001];
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	ll dk[100001], inv[100001], jc[100001], jcny[100001], dk1[100001];
	inline ll cnm(int n, int m) {
	    ll cjr = jc[n];
	    cjr *= jcny[m];
	    cjr %= p;
	    cjr *= jcny[n - m];
	    return (cjr % p);
	}
	void ywymain() {
	    int m = get();
	    int n = sget();
	    dk[0] = inv[0] = jc[0] = dk1[0] = 1;
	    ll ni = mi(26, p - 2);
	    for (register int i = 1; i <= 100000; i++) {
	        jc[i] = (jc[i - 1] * i) % p;
	        dk[i] = (dk[i - 1] * 26) % p;
	        dk1[i] = (dk1[i - 1] * 25) % p;
	        inv[i] = (inv[i - 1] * ni) % p;
	    }
	    jcny[100000] = mi(jc[100000], p - 2);
	    for (register int i = 99999; i >= 0; i--) jcny[i] = (jcny[i + 1] * (i + 1)) % p;
	    int gn = 2;
	    id[n] = 1;
	    for (register int i = n; i <= 100000; i++) {
	        ll cjr = cnm(i - 1, n - 1);
	        cjr *= dk1[i - n];
	        cjr %= p;
	        cjr *= inv[i];
	        dp[1][i] = (dp[1][i - 1] + cjr) % p;
	    }
	    while (m) {
	        m--;
	        int op = get();
	        if (op == 1) {
	            n = sget();
	            if (!id[n]) {
	                id[n] = gn;
	                gn++;
	                for (register int i = n; i <= 100000; i++) {
	                    ll cjr = cnm(i - 1, n - 1);
	                    cjr *= dk1[i - n];
	                    cjr %= p;
	                    cjr *= inv[i];
	                    dp[gn - 1][i] = (dp[gn - 1][i - 1] + cjr) % p;
	                }
	            }
	        } else {
	            int ln = get();
	            print((dp[id[n]][ln] * dk[ln]) % p);
	            putchar('\n');
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：Tsukimaru (赞：0)

提供一个比较套路的做法。

***为了方便，我们设 $O(n) = O(\sum |S|) = O(q)$。***

设 $m = |S|$。

首先可以写出 $O(n|S|)$ 的 DP，然后就会发现答案和 $S$ 具体的值无关，只和 $|S|$ 有关。

那么我们令 $S = \texttt{aaa} \ldots \texttt{a}$，然后枚举字符串内 $\texttt{a}$ 的个数 $i$，可以得到一个简单的枚举式。

$$
\begin{aligned}
	& \sum_{i = m}^n \mathrm{C}^i_n 25^{n - i} \\
	=&26^n - \sum_{i = 0}^{m - 1} \mathrm{C}^i_n 25^{n - i} \\
\end{aligned}
$$

利用第二行的式子我们可以在 $O(m)$ 时间内完成一个询问。

考虑分块分治：若 $m \leq \sqrt n$，那么我们直接暴力 $O(m) = O(\sqrt n)$ 计算。

否则，这样的 $m$ 最多只有 $O(\sqrt n)$ 个。考虑能否 $O(n)$ 预处理出 $1 \ldots n$ 的答案。后面这个求和长得非常套路，所以我们直接套路递推即可。

$$
\begin{aligned}
	S(n) &= 25^n\sum_{i = 0}^{m - 1} \mathrm{C}^i_n 25^{-i} \\
	&= 25^n\sum_{i = 0}^{m - 1} (\mathrm{C}^{i - 1}_{n - 1} + \mathrm{C}^i_{n - 1}) 25^{-i} \\
	&= 25^n\sum_{i = 0}^{m - 1} \mathrm{C}^{i - 1}_{n - 1} 25^{-i} + 25^n \sum_{i = 0}^{m - 1}\mathrm{C}^i_{n - 1} 25^{-i}  \\
	&= 25^{n - 1}\sum_{i = 0}^{m - 2} \mathrm{C}^i_{n - 1} 25^{-i} + 25^n \sum_{i = 0}^{m - 1}\mathrm{C}^i_{n - 1} 25^{-i}  \\
	&= 26S(n - 1) + \mathrm{C}^{m - 1}_{n - 1}25^{n - m} \\
\end{aligned}
$$

就可以 $O(n)$ 计算了。

时间复杂度：$O(n \sqrt n)$。

---

当然，也可以注意到不同的 $m$ 最多只有 $O(\sqrt n)$ 个，所以对每个 $m$ 都直接 $O(n)$ 递推也可以。

---

