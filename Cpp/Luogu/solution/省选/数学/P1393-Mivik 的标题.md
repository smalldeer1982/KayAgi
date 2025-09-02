# Mivik 的标题

## 题目背景

Mivik 现在已经写好了他的书，他现在准备给这本书起个书名去投稿。

## 题目描述

由于 Mivik 写书是乱敲键盘敲出来的，他准备对书名干同样的事情。Mivik 的键盘上有 $m$ 个不同的按键，对应着 $m$ 个不同的字符。Mivik 决定在这个键盘上**等概率**随机敲 $n$ 次敲出标题。但出于某些原因，Mivik 希望书名中要包含有一个人的名字 $S$。于是 Mivik 来问你，他随机敲出的标题有多大的概率包含有这个名字。

同样的，Mivik 并不喜欢奇形怪状的小数，所以你只需要输出这个概率对 $998244353$ 取模后的值。

## 说明/提示

### 样例解释

样例一：为方便描述，我们定义键盘上两个按键为 `a` 和 `b`。那么长度为 3 的所有字符串共有 `aaa`、`aab`、`aba`、`abb`、`baa`、`bab`、`bba`、`bbb` 这 8 个，其中包含有指定名字 `aa` 的共有 `aaa`、`aab`、`baa` 这三个，则概率为 $\frac{3}{8}$，取模后得到 623902721。

### 数据范围

对于全部数据，有 $1\le |S|\le 10^5$，$|S|\le n\le |S|+10^5$，$1\le m\le 10^8$。

Subtask 1 (5 pts)：满足 $m=1$。

Subtask 2 (20 pts)：满足 $1\le n, m\le 250$。

Subtask 3 (30 pts)：满足 $1\le n, m\le 5000$。

Subtask 3 (45 pts)：无特殊限制。

## 样例 #1

### 输入

```
3 2 2
1 1```

### 输出

```
623902721```

## 样例 #2

### 输入

```
6 3 4
1 2 3 2```

### 输出

```
480636170```

# 题解

## 作者：Mivik (赞：19)

[欢迎到我的博客查看](https://mivik.gitee.io/2020/solution/mivik-string-contest-title/)

## Subtask 1

输出 1 即可。

## Subtask 2

参考 Ver 1 的做法，对笔名跑 KMP，建立矩阵然后快速幂即可。

## 满分做法

为了方便描述，我们定义 $\alpha$ 类字符串为整个字符串中只出现一次名字且出现位置为字符串末尾的字符串。例如名字是 `mivik`，那么 `iammivik` 是 $\alpha$ 类字符串，而 `mivikmivik` 不是。

定义 $f_i$ 为长度为 $i$ ，字符集大小为 $m$ 的字符串中 $\alpha$ 类字符串的个数。然后定义 $F(x)$ 为 $f$ 的普通生成函数。同时定义 $g_i$ 为长度为 $i$，字符集大小为 $m$ 的字符串中完全没有出现名字的的字符串个数，并令 $G(x)$ 为它的普通生成函数。

于是我们得到一个显然的式子：
$$
G(x)\cdot mx+1=F(x)+G(x)
$$
这个式子的含义是，我们在一个还没有出现过名字的字符串后面加上一个字符（有 $m$ 种），新的字符串可能包含名字也可能不包含，于是就得到：
$$
G(x)=\frac{1-F(x)}{1-mx}\tag1
$$
然后我们定义一个关于名字（用 $S$ 表示）的多项式 $c(x)$：
$$
c(x)=\sum_{i=0}^{L-1}[\text{i is a period of S}]\cdot x^i
$$
也就是说，这个多项式的第 $i$ 项系数为 1，当且仅当名字有一个长度为 $i$ 的周期；否则这一项系数为 0。注意我们定义一个字符串总有一个长度为 0 的周期。举例来说，假如名字是 `abab`，由于这个字符串分别有长度为 0、2 的周期，那么 $c(x)=1+x^2$。

现在我们考虑在一个还没出现过名字的字符串后面加上名字，那么这个新的字符串必定包含了名字（废话）。不过这个新的字符串不一定是在末尾包含了名字，可能是刚加上一个 border 就已经包含了。形式化的，我们把这个新的字符串写成 `ABC` 的形式，其中 `A` 是原来还没出现过名字的字符串，`BC` 拼起来是名字，然后 `AB` 是一个 $\alpha$ 类字符串。举个例子，假设名字是 `abcab`，那么有一个没出现过名字的字符串 `aaaabc`，然后我们在它后面接上笔名就变成了 `aaaabcabcab`，此时 `A` 为 `aaaabc`、`B` 为 `ab`、`C` 为 `cab`，因为 `AB` 是 `aaaabcab`，末尾恰好第一次出现了名字。

我们注意到，要满足这种拆分，那么 `C` 的长度必定为名字的一个周期的长度，并且 `C` 是名字的后缀。于是我们考虑到对于每一个 `AB`（也就是 $\alpha$ 类字符串），我们把它的末尾添加上一个长度为周期长度的名字的后缀——这样我们就会得到上文提到的所有“新的字符串”。于是我们得到了下面的等式：
$$
G(x)\cdot x^L=F(x)\cdot c(x)
$$
我们把 $(1)$ 式代入进去，展开得到：
$$
\begin{aligned}
\frac{1-F(x)}{1-mx}\cdot x^L&=F(x)\cdot c(x)\\
\frac{x^L+(1-mx)\cdot c(x)}{1-mx}F(x)&=\frac{x^L}{1-mx}\\
F(x)&=\frac{x^L}{x^L+(1-mx)\cdot c(x)}
\end{aligned}
$$
于是我们就可以算出 $F(x)$ 了。考虑怎么求出答案，即包含了名字的字符串总数。我们考虑到每一个包含了这个名字字符串的字符串都必定有一个第一次出现名字的位置，也就是说一个包含名字的字符串能唯一对应到一个 $\alpha$ 类字符串。于是我们只需要对每一个 $\alpha$ 类字符串在后面任意加字符即可。假设长度为 $n$，字符集为 $m$ 的字符串中包含了名字的字符串数目是 $e_i$，其生成函数为 $E(x)$，那么我们有：
$$
\begin{aligned}
E(x)&=\sum_{i=0}F(x)\cdot (mx)^i\\
E(x)&=\frac{x^L}{(1-mx)\left(x^L+(1-mx)\cdot c(x)\right)}
\end{aligned}
$$
然后直接多项式求逆展开就好了。

题外话，上文提到的 $c(x)$ 实际使用很多，不过国内几乎没有什么资料，有个名字是字符串的 Autocorrelation Function（自相关函数），可以到 [维基百科](https://en.wikipedia.org/wiki/Autocorrelation_(words)) 看看。

[代码](https://paste.ubuntu.com/p/Psr9MTZfKp/)

运行代码需要用到的 [mivik.h](https://mivik.gitee.io/mivik.h)

---

## 作者：pomelo_nene (赞：12)

定义 $\operatorname{pre}(s,k)$ 表示 $s$ 长度为 $k$ 的前缀（显然唯一），$\operatorname{suf}(s,k)$ 表示 $s$ 长度为 $k$ 的后缀。如果一个字符串 $t$ 是 $s$ 的 Border，那么 $t=\operatorname{pre}(s,|t|)=\operatorname{suf}(s,|t|)$ 且 $t\neq s$。

首先考虑暴力怎么做。

定义 $dp_i$ 为，$[i-|s|+1,i]$ 这一段子串为 $s$，并且这是 $s$ 在标题里面第一次出现的位置。那么答案显然为 $\displaystyle \sum_{i=|s|}^n dp_i m^{n-i}$。

考虑怎么求这个 $dp_i$。首先 $[i-|s|+1,i]$ 这一段子串为 $s$ 的方案是 $m^{i-|s|}$，需要减去不合法的方案数。能够转移到 $dp_i$ 的状态主要分成两类：

1. 在 $[1,i-|s|]$ 这一段中已经出现了 $s$；   
2. 在加入一段 $s$ 的前缀之后出现了 $s$。

先考虑第一种情况。对于一个 $j \leq i-|s|$，还剩下 $i-|s|-j$ 个空位可以乱填，那么其造成的负贡献为 $dp_j m^{i-|s|-j}$。这个东西可以按顺序处理 $|s| \sim n$ 的时候顺带处理，搞成一个前缀和的形式，可以看代码。

然后是第二种情况。不难发现 $s$ 所有的 Border 都会发生转移，形似在之前已经处理了 $s$ 的一个前缀，加入一个 $s$ 的 Border 之后刚好形成 $s$。显然可以 KMP 求出所有的 Border 转移，但是 Border 数量显然是 $O(n)$ 级别的，直接转移是 $O(n^2)$ 的。

根据 Border Theory 那套理论，一个字符串的所有 Border 可以划分成 $O(\log n)$ 个等差数列。

那么一个套路是用等差数列的性质去优化算法的过程。类似于询问 $\displaystyle \sum_{i \in [l,r], i \bmod d=p} dp_i$ 一类东西。这个东西，可以通过对每个差分序列分别处理，相当于固定一个 $d$（这个在 $O(n)$ 级别）。假设现在在处理第 $i$ 个差分序列，存下所有下标值模 $d_i$ 为 $p$ 的 $dp$ 值并滚个前缀和，这样简单得到贡献范围，减去就行了；至于更新比较容易。具体细节还是得看代码……但是看懂了就很简单了。

然后求出 $dp$ 按上面的答案式子做就行了……

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<18],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
const int MOD=998244353;
inline int Add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
inline int Sub(int x,int y){return x<y?x-y+MOD:x-y;}
inline int Mul(int x,int y){return 1ll*x*y%MOD;}
int QuickPow(int x,int p)
{
	int ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=Mul(ans,base);
		base=Mul(base,base);
		p>>=1;
	}
	return ans;
}
int n,m,k;
int s[100005],nxt[100005];
struct BorderSeq{
	int l,r,d;
	BorderSeq(){}
	BorderSeq(int L,int R,int D){l=L,r=R,d=D;}
}brd[200005];
int cnt,dp[200005],sum[200005];
int pw[200005],ipw[200005];
void Kmp()
{
	int j=0;
	for(int i=2;i<=k;++i)
	{
		while(j && s[j+1]!=s[i])	j=nxt[j];
		if(s[j+1]==s[i])	++j;
		nxt[i]=j;
	}
	int now=nxt[k],d=k-nxt[k],fir=nxt[k];
	while(now)
	{
		if(d!=now-nxt[now] || !nxt[now])	brd[++cnt]=BorderSeq(now,fir,d),fir=nxt[now];
		if(!nxt[now])	break;
		d=now-nxt[now],now=nxt[now];
	}
}
vector<int> Sum[20][200005];
int pos[20][200005];
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;++i)	s[i]=read();
	Kmp();
	int invm=QuickPow(m,MOD-2);
	pw[0]=ipw[0]=1;
	for(int i=1;i<=n;++i)	pw[i]=Mul(pw[i-1],m);
	for(int i=1;i<=n;++i)	ipw[i]=Mul(ipw[i-1],invm);
	memset(pos,-1,sizeof pos);
	for(int i=k;i<=n;++i)
	{
		dp[i]=Sub(pw[i-k],sum[i-k]);
		for(int j=1;j<=cnt;++j)
		{
			int d=brd[j].d,l=brd[j].l,r=brd[j].r;
			int idx=(l+i-k)%d;
			if(!Sum[j][idx].empty())
			{
				int L=l+i-k,R=r+i-k;
				if(~pos[j][R])	dp[i]=Sub(dp[i],Sum[j][idx][pos[j][R]]);
				if(pos[j][L]>0)	dp[i]=Add(dp[i],Sum[j][idx][pos[j][L]-1]);
			}
		}
		for(int j=1;j<=cnt;++j)
		{
			int d=brd[j].d;
			int idx=i%d;
			pos[j][i]=int(Sum[j][idx].size());
			Sum[j][idx].push_back(Add(Sum[j][idx].empty()?0:Sum[j][idx].back(),dp[i]));
		}
		sum[i]=Add(Mul(sum[i-1],m),dp[i]);
	}
	int ans=0;
	for(int i=k;i<=n;++i)	ans=Add(ans,Mul(dp[i],pw[n-i]));
	write(Mul(ans,ipw[n]));
	return 0;
}
```

---

## 作者：Liveddd (赞：5)

比较有趣的字符串题目。利用 Border Theory 性质优化，或者用生成函数解决。


## 暴力解法

利用 [P3193 [HNOI2008] GT考试](https://www.luogu.com.cn/problem/P3193) 类似的方法，设计 $f(i,j)$ 表示考虑前 $i$ 位，当前已匹配 $j$ 位。转移矩阵容易通过 KMP 求出，这样是 $\mathcal O(n|S|^2)$，加上矩阵快速幂优化可以做到 $\mathcal O(|S|^3\log n)$。这样显然不够优。

我们直接记录 $f(i)$ 表示 字符串恰好在 $[i-|S|+1,i]$ 出现一次。最终答案为 $\sum_{i=|S|}^n f(i)\cdot m^{n-i}$。考虑求 $f(i)$，会出现两种情况：

1. $S$ 已经在 $[1,i-|S|]$ 中出现过。那么不合法的方案为 $\sum_{j=0}^{i-|S|}f(j)\cdot m^{i-|S|-j}$，前缀和即可。
2. 加入 $S$ 的一段前缀时出现了 $S$。那么满足该前缀是 $S$ 的一个 Border，我们利用 KMP，求出所有 Border 然后进行转移即可，不合法的方案为 $\sum_j f(i-|S|+j)$。但是因为 Border 的数量是 $\mathcal O(|S|)$ 的，所有最终总的时间复杂度为 $\mathcal O(n|S|)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=5e5+10,mod=998244353;
template<class T>
inline void read(T &x)
{
    x=0;bool f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=~x+1;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x),read(x1...);
}
int n,m,c;
int s[N];
int ne[N];
int f[N];
inline void adj(int &x){x+=x>>31&mod;}
inline int qpow(int x,int k=mod-2)
{
    int res=1;
    while(k)
    {
        if(k&1)res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        k>>=1;
    }
    return res;
}
int main()
{
    read(m,c,n);
    for(int i=1;i<=n;i++)read(s[i]);
    for(int i=2,j=0;i<=n;i++)
    {
        while(j&&s[i]!=s[j+1])j=ne[j];
        if(s[i]==s[j+1])j++;
        ne[i]=j;
    }
    for(int i=n,res=0,mul=1;i<=m;i++,mul=1ll*mul*c%mod)
    {
        adj(res=1ll*res*c%mod-f[i-n]),adj(f[i]=res+mul-mod);
        for(int j=ne[n];j;j=ne[j])adj(f[i]-=f[i-n+j]);
    }
    int ans=0;
    for(int i=m,mul=1;i>=n;i--,mul=1ll*mul*c%mod)
        adj(ans+=1ll*mul*f[i]%mod-mod);
    printf("%d\n",1ll*ans*qpow(qpow(c,m))%mod);
    return 0;
}
```

## 解法一

尝试运用 Border Theory 对暴力进行优化。$S$ 所有的 Border 可以被划分为至多 $\mathcal O(\log n)$ 个等差数列。尝试利用这一点，对于每个等差数列分别考虑，维护每个等差数列的前缀和即可。时间复杂度为 $\mathcal O(n\log n)$，常数较小。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2e5+10,K=19,mod=998244353;
template<class T>
inline void read(T &x)
{
    x=0;bool f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=~x+1;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x),read(x1...);
}
int n,m,c;
int s[N];
int ne[N];
int tot,l[K],r[K],d[K];
int f[N],g[N][K];
inline void adj(int &x){x+=x>>31&mod;}
inline int qpow(int x,int k=mod-2)
{
    int res=1;
    while(k)
    {
        if(k&1)res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        k>>=1;
    }
    return res;
}
int main()
{
    read(m,c,n);
    for(int i=1;i<=n;i++)read(s[i]);
    for(int i=2,j=0;i<=n;i++)
    {
        while(j&&s[i]!=s[j+1])j=ne[j];
        if(s[i]==s[j+1])j++;
        ne[i]=j;
    }
    for(int i=ne[n];i;i=ne[i])
    {
        d[++tot]=i-ne[i],r[tot]=n-i;
        while(ne[i]&&i-ne[i]==d[tot])i=ne[i];
        l[tot]=n-i;
    }
    for(int i=n,res=0,mul=1;i<=m;i++,mul=1ll*mul*c%mod)
    {
        adj(res=1ll*res*c%mod-f[i-n]),adj(f[i]=res+mul-mod);
        for(int j=1;j<=tot;j++)
        {
            if(i>=l[j]+d[j])adj(f[i]+=g[i-l[j]-d[j]][j]-mod);
            adj(f[i]-=g[i-r[j]][j]);
        }
        for(int j=1;j<=tot;j++)adj(g[i][j]=g[i-d[j]][j]+f[i]-mod);
    }
    int ans=0;
    for(int i=m,mul=1;i>=n;i--,mul=1ll*mul*c%mod)
        adj(ans+=1ll*mul*f[i]%mod-mod);
    printf("%d\n",1ll*ans*qpow(qpow(c,m))%mod);
    return 0;
}
```

## 解法二

考虑第二类转移，非常的像分治 FFT，我们似乎可以直接这样求解，~~但是这样并不优美~~。所以还是利用生成函数把基本关系列出来。设 $g(i)$ 表示长度为 $i$ 的不包含名字的字符串方案数，$F(x)$ 为 $f(i)$ 的 OGF，$G(x)$ 为 $g(i)$ 的 OGF。考虑在不包含名字的字符串后，添加一个字符，那么接下来要么出现名字，要么还是不出现名字，得到关系：
$$
G(x)\cdot mx+1=F(x)+G(x)\pmod {x^n}
$$
继续考虑第二类转移，我们构造 $H(x)$ 表示 Border 长度集合构成的数列对应的 OGF。此时考虑在不包含名字的字符串后，直接添加一个名字，那么合法的字符串可以在所有 Border 所有位置结束，得到关系：
$$
G(x)\cdot x^{|S|}=F(x)H(x)\pmod{x^n}
$$
通过上面两个式子我们最终可以得到：
$$
F(x)=\frac{x^{|S|}}{x^{|S|}+(1-mx)\cdot H(x)}
$$
一次多项式求逆即可，时间复杂度为 $\mathcal O(n\log n)$。代码略。



---

## 作者：Lusterdawn (赞：5)

和官方题解略有不同的做法。

考虑计算**不包含** $S$ 的字符串数量，再用总数减去它。

考虑进行**容斥**，记 $P(x)$ 为钦定了 $x$ 个 $S$ 的出现位置，其他位置不管的合法方案数，答案即 $\sum P(x) \cdot (-1)^x$

但是上式难以直接计算，考虑来 dp 这个容斥，$f_i$ 表示考虑前 $i$ 个位置，所有方案的容斥系数之和。我们将所有出现位置有交的 $S$ 拼接起来，称这样形成的一段为一个**大段**，可以枚举前一个大段的位置转移，方程为 $f_i = \sum_{j=1}^i g_i f_{i-j} + mf_{i-1}$，其中 $g_i$ 为长度为 $i$ 的一个大段的所有方案的容斥系数之和。只需计算 $g$ 即可分治 FFT 计算上式。

考虑如何计算 $g$，设 $h_i$ 为后面已经填了一个 $S$ ，前面接着填长度为 $i$ 的字符串形成一个大段的容斥系数之和。记数列 $q$，若 $S$ 的长度为 $i$ 的前缀和后缀相同，则 $q_i=-1$，否则 $q_i=0$。$q$ 可以用 KMP 求解。

显然有 $h_i = \sum_{j=1}^i q_i h_{i-j}$，同样可以分治 FFT 计算。求得 $h$ 之后 $g_i = -h_{i - |S|}$，至此我们解决了这个问题。

---

## 作者：Purslane (赞：2)

# Solution

考虑使用容斥原理——计算出钦定了 $j$ 个位置满足**以 $j$ 开头、长度为 $|S|$ 的字符串和 $|S|$ 相同的方案数**。

如果相邻两个钦定位置 $i$ 和 $j$（$i<j$）满足 $j < i + |S|$，则要求 $S$ 有一个长度为 $|S|+i-j$ 的 Border；否则，$[i+|S|,j)$ 中间的东西就可以随便填。

接下来有很多做法：一种简单的做法是考虑相邻关键点之间的距离差，很容易写成一个多项式 $F$，要求 $1 - F + F^2 - F^3 + \cdots$，它实际上就是 $\dfrac{1}{1+F}$，可以直接多项式求逆。

还有一种做法是，设 $dp_i$ 为，最后一个关键点在 $i$，即确定了 $[1,i+|S|)$ 中的所有字符的计算结果（提前加入了容斥系数）

容易发现，$dp_j$ 向 $dp_i$ 的贡献（$j<i$）之和 $i-j$ 有关——可以直接维护半在线卷积！

如果不想用多项式，还有一些方法：显然我们只需要解决 $i-j < |S|$ 的情况。**根据 $\rm Border$ 理论，一个字符串所有 $\rm Border$ 的长度可以被划分为 $O(\log |S|)$ 个等差数列**。这样就得到了一个 $O(|S| \log |S|)$ 空间的做法：维护若干模意义下的前缀和（非常类似多重背包的优化，不赘述）。

实现了最后一种。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=998244353;
int n,m,t,tot,a[MAXN],dp[MAXN],pre[MAXN][25],kmp[MAXN];
struct SEG {int l,r,d;}sg[25];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>t;
	ffor(i,1,t) cin>>a[i];
	kmp[0]=-1,kmp[1]=0;
	ffor(i,2,t) {
		kmp[i]=kmp[i-1];
		while(kmp[i]!=-1&&a[i]!=a[kmp[i]+1]) kmp[i]=kmp[kmp[i]];
		kmp[i]++;
	}
	vector<int> v;
	int u=kmp[t];
	while(u) v.push_back(t-u),u=kmp[u];
	sort(v.begin(),v.end());
	int l=-1,r=-1,d=-1;
	for(auto id:v) {
		if(l==-1) l=r=id;
		else if(d==-1) r=id,d=r-l;
		else if(id==r+d) r+=d;
		else sg[++tot]={l,r,max(0ll,d)},l=r=id,d=-1;
	}
	sg[++tot]={l,r,max(1ll,d)};
	ffor(i,1,n-t+1) {
		dp[i]=qpow(m,i-1);
		if(i>=t) dp[i]=(dp[i]-pre[i-t][0]*qpow(m,i))%MOD;
		ffor(j,1,tot) {
			int l=sg[j].l,r=sg[j].r+sg[j].d;
			if(i>=l) dp[i]=(dp[i]-pre[i-l][j])%MOD;
			if(i>=r) dp[i]=(dp[i]+pre[i-r][j])%MOD;
		}
		ffor(j,1,tot) {
			pre[i][j]=dp[i];
			if(i>=sg[j].d) pre[i][j]=(pre[i][j]+pre[i-sg[j].d][j])%MOD;	
		}
		pre[i][0]=(pre[i-1][0]+dp[i]*qpow(m,MOD-1-i-t))%MOD;
	}
	int ans=0;
	ffor(i,1,n-t+1) ans=(ans+dp[i]*qpow(m,n-(i+t-1)))%MOD;
	ans=ans*qpow(m,MOD-1-n)%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
很早以前就看到的题，以为和 GT 考试差不多然后就被创飞了。

原本以为只能用生成函数的，后面才知道有个东西叫  border theory，算是初学第一次做题了。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
暴力的想法，可以直接上矩阵，思路直接像 GT 考试一样写，那么复杂度是 $O(|s|^3n)$ 显然爆飞了。

可以很容易发现这题的重点肯定是在 $n$ 上了，比起 GT 考试小了许多。

直接上来考虑设计 dp。

我们设 $f_i$ 表示 $[i-|s|+1,i]$ 恰好为 $s$ 且这是 $s$ 第一次出现。

那么我们知道答案是 $\sum\limits_{i=|s|}^n f_i\cdot m^{n-i}$。

接着就是计算 $f_i$ 了，不难发现，我们先固定 $[i-|s|+1,i]$，那么剩下的部分直接乱填，方案数是 $m^{n-i-|s|}$。

接着考虑来去重。

1. $s$ 在 $[1,i-|s|]$ 出现过了。

   这样的出现显然是完整和目前新造这段不重的。

   方案数也很好数，即为 $\sum\limits_{j=0}^{i-|s|}f_j\cdot m^{i-|s|-j}$。

2. $s$ 在 $[i-|s+1|,i-1]$ 出现过了。

   这样就是前面的一段拼上 $s$ 的一段前缀成了一个新的 $s$。

   那这个前缀肯定是 $s$ 的一个 border。

   找到所有的 border $j$ 进行转移就行了。

   方案数就是 $\sum\limits_{j} f_{i-|s|+j}$。

border 的数量显然是能被卡到 $O(|s|)$ 的，所以复杂度是 $O(n|s|)$。

然后我们就知道现在要做的是什么了。

转化下题意。

现在就是给一个数组末尾加，然后对于一个位置 $i$ 给定 $n$ 个定值求这些 $i$ 减去这些定值的位置之和。

这东西看着就很不可做，但是这 $n$ 个定值之间有联系。

根据 border theory，我们知道这 $n$ 个定值可以划分为 $\log n$ 个等差数列。

考虑对于每个等差数列维护，直接做前缀和就可以做到 $O(n\log |s|)$。

也就是正常的前缀和是从 $-1$ 的位置转移，等差数列用 $-k$（其中 $k$ 为公差）转移即可。
## 代码
莫名的简单。

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,V=1e6+10,M=21,INF=1e18,mod=998244353;
int n,m,k,tot,ans,nxt[N],f[N],s[N],a[M],l[M],r[M],g[N][M];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
namespace KMP
{
	inline void kmp(int s[],int n,int nxt[])
	{
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			nxt[i]=j;
		}
	}
}
using namespace KMP;
inline void solve()
{
    n=read(),m=read();k=read();for(int i=1;i<=k;i++) s[i]=read();kmp(s,k,nxt);
	for(int i=nxt[k];i;i=nxt[i])
	{
		a[++tot]=i-nxt[i];r[tot]=k-i;
		while(nxt[i]&&i-nxt[i]==a[tot]) i=nxt[i];
		l[tot]=k-i;
	}
	for(int i=k,res=0,mul=1;i<=n;i++)
	{
		f[i]=(mul-res+mod)%mod;
		for(int j=1;j<=tot;j++)
		{
			if(i>=l[j]+a[j]) f[i]=(f[i]+g[i-l[j]-a[j]][j])%mod;
			f[i]=(f[i]-g[i-r[j]][j]+mod)%mod;
		}mul=mul*m%mod;res=(res*m%mod+f[i-k+1])%mod;
		for(int j=1;j<=tot;j++) g[i][j]=(g[i-a[j]][j]+f[i])%mod;
	}for(int i=n,mul=1;i>=k;i--) ans=(ans+f[i]*mul%mod)%mod,mul=mul*m%mod;
	print(ans*ksm(ksm(m,n,mod),mod-2,mod)%mod);
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Mirasycle (赞：1)

如果按照 P3193 的 trick 来做的话是 $O(\lvert S\rvert^3\log n)$ 的。

观察到本题和那题的区别其实是 $\lvert S\rvert$ 大，但是 $n$ 小。所以考虑对于 $n$ 进行 dp 之类的。

一个串内可能多次出现 $S$，为了不统计重复，我们在其第一次出现的时候统计他。设 $f_i$ 表示 $S$ 第一次出现在以 $i$ 结尾的位置。那么后面就随便填了。

我一开始想太简单了，我觉得既然是第一次出现，我们就拿出现的方案数减去之前的 $[1,i-1]$ 之内的 $f$ 乘以一个系数之类的不就行了吗？但其实有点小问题，因为我们已经钦定了 $[i-\lvert S\rvert+1,i]$ 之内的串为 $S$，所以 $[1,i-\lvert S\rvert]$ 之内的 $f$ 是不受影响的，可以乘以一个系数减去，但是 $[i-\lvert S\rvert+1,i]$ 之内的需要有限制不是随便填的。

具体来说，必须满足在 border 处的 $f$ 才有可能造成重复贡献。因为在这些地方满足前缀和后缀是相等的，恰好可以放入。

如果暴力找 border 处的 $f$，时间复杂度是 $O(n\lvert S\rvert)$ 的。

运用 border 理论，$S$ 的所有 border 都可以被划分为 $\log$ 个等差数列，记录等差数列前缀和就可以 $O(\log \lvert S\rvert)$ 转移。

时间复杂度 $O(n\log \lvert S\rvert)$。

---

## 作者：Felix72 (赞：1)

节选自我的 [[字符串] Border 和回文前后缀的性质、维护和运用](https://www.luogu.com.cn/article/96hy0bja)。里面有这篇题解所用性质的证明，建议阅读。

> 求 $n \ (\leq 2 \times 10^5)$ 长度随机生成的字符串包含给定字符串 $s$ 的概率。

### Part A

令 $f_i$ 表示 $[i - |s| + 1, i]$ 这些字符恰好是 $s$，且前面从来没有出现 $s$ 的方案数，不难容斥做到 $O(n^2)$。

### Part B

你把代码写出来就能知道，刚刚容斥的瓶颈是枚举 $border$，但是它们构成了 $O(\log |s|)$ 个等差数列，因此记 $O(\log |s|)$ 份前缀和就能优化了。

### Part C

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 200010, mod = 998244353;
inline long long qpow(long long a, long long b)
{long long res = 1; while(b) {if(b & 1) res = res * a % mod; b >>= 1, a = a * a % mod;} return res;}
int n, k, m, s[N], nxt[N], w[N], wn; long long f[N], pw[N], pwi[N];
inline void get(int len) {if(!len) return ; w[++wn] = m - len, get(nxt[len]);}

long long p[110][N];
struct Seq {int x, d, lim;} seq[110]; int sn;
inline long long S(int id, int l, int r)
{if(r <= 0) return 0; l = max(l, 0); return (p[id][r] - p[id][l] + mod) % mod;}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> m;
	for(int i = 1; i <= m; ++i) cin >> s[i];
	pw[0] = 1; for(int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * k % mod;
	pwi[0] = 1; for(int i = 1, iv = qpow(k, mod - 2); i <= n; ++i) pwi[i] = pwi[i - 1] * iv % mod;
	for(int i = 2; i <= m; ++i)
	{
		nxt[i] = nxt[i - 1];
		while(nxt[i] && s[nxt[i] + 1] != s[i]) nxt[i] = nxt[nxt[i]];
		if(s[nxt[i] + 1] == s[i]) ++nxt[i];
	}
	get(nxt[m]);
	for(int l = 1; l <= wn; ++l)
	{
		int r = l + 1;
		if(l == wn) seq[++sn] = {w[l], 1, 0};
		else
		{
			while(r < wn && w[r + 1] - w[r] == w[r] - w[r - 1]) ++r;
			seq[++sn] = {w[l], w[l + 1] - w[l], r - l}; l = r;
		}
	}
	for(int i = m; i <= n; ++i)
	{
		f[i] = pw[i - m];
		f[i] = (f[i] - p[0][i - m] * pw[i - m] % mod + mod) % mod;
		for(int j = 1; j <= sn; ++j)
			f[i] = (f[i] - S(j, i - seq[j].x - seq[j].d * (seq[j].lim + 1), i - seq[j].x) + mod) % mod;
			
		p[0][i] = (p[0][i - 1] + f[i] * pwi[i]) % mod;
		for(int j = 1; j <= sn; ++j) p[j][i] = (p[j][max(0, i - seq[j].d)] + f[i]) % mod;
	}
	long long res = 0;
	for(int i = m; i <= n; ++i) res = (res + f[i] * pw[n - i]) % mod;
	cout << res * qpow(pwi[1], n) % mod << '\n';
	return 0;
}
/*

*/
```

---

## 作者：_abcd_ (赞：0)

## [[P1393] Mivik 的标题](https://www.luogu.com.cn/problem/P1393)

正难则反，我们考虑求出所有不包含 $S$ 的标题数量，然后用 $m^n$ 减去就行了。

对于这种“不包含”的问题，很自然会想到用容斥，但是“钦定 $S$ 出现了 $i$ 次”这种情况不太好直接算，因为名字可能出现相交的情况，例如在字符串 $\text{ababa}$ 中，子串 $\text{aba}$ 就出现了两次。

我们不妨将标题拆成若干个字符串来考虑。我们定义，若两个子串的出现位置相交，那么他们就在一个连续段内。例如，在字符串 $\text{ababac}$ 中，两个 $\text{aba}$ 就在同一个连续段 $\text{ababa}$ 内，而在字符串 $\text{abaaba}$ 和字符串 $\text{abacaba}$ 中则不是。

假设当前有一个连续段，那么我们可以在其后面加上一个 $S$ 的后缀来得到一个新的连续段，而且这个后缀要满足他前面那一串是 $S$ 的一个 $\text{Border}$。例如，若 $S$ 为 $\text{ababa}$ ，那么我们可以添加的后缀有 $\text{ba}$，$\text{baba}$，而不能添加后缀 $\text{a}$，$\text{aba}$。显然每个连续段都是由 $S$ 添加若干个后缀得到的，因此我们设 $H = \sum\limits_{\text{T is a border of S},T \neq S} x^{|S|-|T|}$，即所有可添加的后缀的长度，那么连续段数量的生成函数 $G = -x^{|S|} \sum\limits_{i=0}^{\inf} (-H)^i = -x^{|S|} \frac 1{1+H}$。注意，这里取负是因为我们用的是容斥，因此权值要乘上 $(-1)^i$。

那么标题的数量的生成函数就是 $F = \sum\limits_{i=0}^{\inf} (G+mx)^i = \frac 1{1-mx-G}$，也就是在当前标题后面添加一个单个字符，或者一个连续段。最后的答案就是 $\frac {m^n - f_n}{m^n}$。

### 附上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
#define int ll
#define N 262144
#define mod 998244353
#define maxn 100005
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
int ksm(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ret;
}
void dq(int &x)
{
    if(x>=mod)x-=mod;
    if(x<0)x+=mod;
}
void swap(int& x,int& y)
{
    x^=y^=x^=y;
}
namespace polynomial
{
    int gn[N<<1],gi[N<<1],rev[N<<1],iv[N+1];
    void poly_init()
    {
        for(int i=1;i<=N;i<<=1)
        {
            gn[i]=ksm(3,(mod-1)/i);
            gi[i]=ksm(gn[i],i-1);
        }
        gn[0]=gi[0]=1;
        for(int i=1;i<N<<1;i++)
        {
            int j=1<<__lg(i);
            gn[i]=gn[i-1]*gn[j]%mod;
            gi[i]=gi[i-1]*gi[j]%mod;
        }
        for(int i=2;i<=N;i<<=1)
        {
            for(int j=i;j<i<<1;j++)
            {
                rev[j]=rev[j-i>>1|i]>>1;
                if(j&1)
                    rev[j]|=i>>1;
            }
        }
        iv[0]=iv[1]=1;
        for(int i=2;i<=N;i++)
            iv[i]=(mod-mod/i)*iv[mod%i]%mod;
    }
    int getn(int n)
    {
        if(n==1)
            return 1;
        return 1<<__lg(n-1)+1;
    }
    struct Poly
    {
        int a[N];
        int& operator [] (int x)
        {
            return a[x];
        }
        void print(int n,int l=0)
        {
            for(int i=l;i<l+n;i++)
                printf("%lld ",a[i]);
            pn;
        }
        void cpy(Poly& t,int n,int l=0)
        {
            for(int i=l;i<l+n;i++)
                a[i]=t[i];
        }
        void clr(int n,int l=0)
        {
            for(int i=l;i<l+n;i++)
                a[i]=0;
        }
        void NTT(int n,int ty=1)
        {
            for(int i=0,*t=rev+n;i<n;i++,t++)
            {
                if(*t<i)
                    swap(a[i],a[*t]);
            }
            for(int i=1;i<n;i<<=1)
            {
                for(int j=0;j<n;j+=i<<1)
                {
                    int *x=(ty==1?gn:gi)+(i<<1)-1;
                    for(int k=j;k<j+i;k++,x++)
                    {
                        int l=a[k],r=*x*a[k+i]%mod;
                        a[k]=l+r,a[k+i]=l-r;
                        a[k]=a[k]>=mod?a[k]-mod:a[k];
                        a[k+i]=a[k+i]<0?a[k+i]+mod:a[k+i];
                    }
                }
            }
            if(ty==-1)
            {
                for(int i=0;i<n;i++)
                    a[i]=a[i]*iv[n]%mod;
            }
        }
        void mul(Poly& F,Poly& G,int n)
        {
            n=getn(n);
            F.NTT(n);
            G.NTT(n);
            for(int i=0;i<n;i++)
                a[i]=F[i]*G[i]%mod;
            NTT(n,-1);
        }
        void bni(Poly& t,int n)
        {
            if(n==1)
            {
                a[0]=ksm(t[0],mod-2);
                return;
            }
            clr(n>>1,n>>1);
            static Poly tni1,tni2;
            tni1.cpy(*this,n);
            tni2.cpy(t,n);
            tni1.mul(tni1,tni2,n);
            tni1.clr(n>>1);
            tni2.cpy(*this,n);
            tni1.mul(tni1,tni2,n);
            for(int i=n>>1;i<n;i++)
                dq(a[i]=-tni1[i]);
        }
        void ni(int n)
        {
            static Poly tni0;
            n=getn(n);
            tni0.cpy(*this,n);
            for(int i=1;i<=n;i<<=1)
                bni(tni0,i);
        }
        void dao(int n)
        {
            for(int i=1;i<n;i++)
                a[i-1]=i*a[i]%mod;
            a[n-1]=0;
        }
        void jf(int n)
        {
            for(int i=n-1;i;i--)
                a[i]=a[i-1]*iv[i]%mod;
            a[0]=0;
        }
        void ln(int n)
        {
            static Poly tln;
            n=getn(n);
            tln.cpy(*this,n<<1);
            tln.dao(n);
            ni(n);
            mul(*this,tln,n<<1);
            jf(n);
        }
        void exp(int n)
        {
            n=getn(n);
            static Poly texp0;
            texp0.cpy(*this,n);
            a[0]=1;
            a[1]=0;
            for(int len=2;len<=n;len<<=1)
            {
                static Poly texp1,texp2,texp3;
                texp1.bni(*this,len>>1);
                texp1.bni(*this,len);
                texp2.cpy(texp1,len);
                texp3.cpy(*this,len);
                texp3.dao(len);
                texp3.clr(len,len);
                texp2.clr(len,len);
                texp2.mul(texp2,texp3,len<<1);
                texp2.jf(len);
                dq(texp2[0]=1-texp2[0]);
                for(int i=1;i<len;i++)
                    dq(texp2[i]=texp0[i]-texp2[i]);
                clr(len,len);
                mul(*this,texp2,len<<1);
                clr(len,len);
                texp1.clr(len,len);
            }
        }
        void mi(int n,int m)
        {
            n=getn(n);
            ln(n);
            for(int i=0;i<n;i++)
                (a[i]*=m)%=mod;
            exp(n);
        }
    };
}
using namespace polynomial;
int n,k,m;
int a[maxn],nex[maxn];
Poly F;
signed main()
{
    poly_init();
    n=re(),k=re(),m=re();
    for(int i=1;i<=m;i++)
        a[i]=re();
    for(int i=2,j=0;i<=m;i++)
    {
        while(j&&a[j+1]!=a[i])
            j=nex[j];
        if(a[j+1]==a[i])
            j++;
        nex[i]=j;
    }
    for(int i=m;i;i=nex[i])
        F[m-i]=1;
    F.ni(n+1);
    for(int i=n;i>=m;i--)
        F[i]=F[i-m];
    F.clr(m);
    F[0]=1;
    dq(F[1]-=k);
    F.ni(n+1);
    int ans=(ksm(k,n)-F[n])*ksm(k,n*(mod-2))%mod;
    dq(ans);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Union_of_Britain (赞：0)

这题很像歌唱王国阿。

于是先转计数，统计 $a_i$ 为 $i$ 位置作为第一个出现的名字的结束的方案数。如此可保证不重不漏。因此我们希望求出 $F=\sum a_ix^i$。

类似地，设 $G=\sum b_ix^i$，$b_i$ 为 $i$ 位置结束还未出现名字的方案数。

我们可以得出两个关系。

$$1+mxG=F+G$$

意义为还没出现添加一个字符后名字可能会第一次出现，也可能不出现。

$$x^{|S|}G=F\sum _{s[1:i]=s[|s|-i+1:|s|]}x^{|s|-i}$$

意义为没出现的强行加上一个名字序列可能会在任意 border 位置结束（当然也可能在最后才结束）。

综上，设

$$H(x)=\sum _{s[1:i]=s[|s|-i+1:|s|]}x^{|s|-i}$$

有

$$F=\frac{x^{|s|}}{(H-mxH+x^{|s|})}$$

KMP 求出 $H$ 后求逆即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=6e5+5,mod=998244353,G=3;
int lim,L,r[maxn],iG;
int qp(int a,int b){
	if(b==0)return 1;
	int T=qp(a,b>>1);T=T*T%mod;
	if(b&1)return T*a%mod;
	return T;
}
void ntt(int a[],int tp){
	for(int i=0;i<lim;i++)if(r[i]>i)swap(a[i],a[r[i]]);
	for(int mid=1;mid<lim;mid<<=1){
		int wn=qp(tp==1?G:iG,(mod-1)/(mid<<1));
		for(int j=0;j<lim;j+=(mid<<1)){
			int W=1;
			for(int k=0;k<mid;k++,W=W*wn%mod){
				int x=a[j+k],y=a[j+k+mid]*W%mod;
				a[j+k]=(x+y)%mod,a[j+k+mid]=(x-y+mod)%mod;
			}
		}
	}
	int I=qp(lim,mod-2);
	if(tp==-1)for(int i=0;i<lim;i++)a[i]=a[i]*I%mod;
}
void qsy(int x){
	lim=1,L=0;
	while(lim<(x<<1))lim<<=1,L++;
	for(int i=1;i<lim;i++)r[i]=(r[i>>1]>>1)|((i&1)<<L-1);
}
int c[maxn];
void Inv(int a[],int b[],int len){
	if(len==1){
		b[0]=qp(a[0],mod-2);
		return ;
	}
	Inv(a,b,(len+1)>>1);
	qsy(len);
	memset(c,0,sizeof(c));
	for(int i=0;i<len;i++)c[i]=a[i];
	ntt(c,1);ntt(b,1);
	for(int i=0;i<lim;i++)b[i]=(2-b[i]*c[i]%mod+mod)%mod*b[i]%mod;
	ntt(b,-1);
	for(int i=len;i<lim;i++)b[i]=0;
}
int n,m,k,P[maxn],C[maxn],T[maxn],A[maxn],s[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	iG=qp(G,mod-2);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)cin>>s[i];
	P[1]=0;int j=0;
	for(int i=2;i<=k;i++){
		while(j&&s[j+1]!=s[i])j=P[j];
		if(s[j+1]==s[i])++j;
		P[i]=j;
	}
	int now=k;
	while(now){
		C[k-now]=1;
		now=P[now];
	}
	T[0]=C[0];
	for(int i=1;i<=k;i++)T[i]=(C[i]-m*C[i-1]%mod+mod)%mod;
	(T[k]+=1)%=mod;
	Inv(T,A,n);int ans=0;
	for(int i=0;i<=n-k;i++)(ans+=qp(m,n-(k+i))*A[i]%mod)%=mod;
	ans=ans*qp(qp(m,n),mod-2)%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

