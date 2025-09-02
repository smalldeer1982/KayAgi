# Shelter

## 题目背景

![Shelter](https://cdn.luogu.com.cn/upload/image_hosting/dng2ysqs.png)

> It's a long way forward, so trust in me
>
> I'll give them shelter, like you've done for me
>
> And I know, I'm not alone
>
> You'll be watching over us, until you're gone

## 题目描述

在太空里的时间，Rin 除了在虚拟世界里自由创作，每天还会进行一个有趣的小游戏。

最初来到太空时，她的父亲留给她了一个由英文小写字母组成的非空的字符串 $s$，其长度为 $n$。每天，Rin 都会找到一个最大的整数 $i$（$0\le i<|s|$）使得字符串的长度为 $i$ 的前缀与其长度为 $i$ 的后缀相同（注意 $i$ 可能为 $0$），并将这个 前缀 / 后缀 追加在整个字符串的最后面形成新的字符串。例如，当字符串为 `mivikismivik` 时，最大的 $i=5$（字符串长为 $5$ 的前缀后缀皆为 `mivik`），于是 Rin 将 `mivik` 追加在字符串后面形成新字符串 `mivikismivikmivik`。

在太空中度过 $K$ 天后，这个字符串已经变得很长，Rin 突然很好奇这个字符串的长度现在是多少，你能帮帮她吗？由于答案可能很大，你只需要告诉她答案对 $998244353$ 取模的结果即可。

## 说明/提示

### 样例解释

样例一：操作一次后得到字符串 `abcdabcabc`，长度为 $10$。

样例二：操作一次后得到字符串 `ioioiioi`，再操作一次得到 `ioioiioiioi`，长度为 $11$。

### 数据范围

对于全部数据，有 $1\le n\le 2\cdot 10^6$，$1\le K\le 10^{18}$。

Subtask 1 (15 pts)：保证 $s$ 只由一种字母构成。

Subtask 2 (20 pts)：保证 $s$ 有长度不为 $|s|$ 的整周期（即长度是 $|s|$ 的约数的周期）。

Subtask 3 (65 pts)：无特殊限制。


## 样例 #1

### 输入

```
7 1
abcdabc```

### 输出

```
10```

## 样例 #2

### 输入

```
5 2
ioioi```

### 输出

```
11```

## 样例 #3

### 输入

```
8 50
idolidol```

### 输出

```
263923940```

# 题解

## 作者：Mivik (赞：7)


如果没有 border，答案是 $n$。

如果有整周期，则答案是 $|p|+2^K(n-|p|)$，其中 $p$ 是最小整周期。

如果 border 大于 $\dfrac n2$，即周期小于 $\dfrac n2$。令 $s=p^k\cdot pre_t(p)$，其中 $p$ 是最小周期，$pre_t(p)$ 是 $p$ 的长为 $t$ 的前缀（$0<t<|p|$）。实际上这样的字符串进行一次操作之后的最长 border 仍为 $n-p$，证明如下：

假设进行一次操作后的字符串有一个长度小于 $n$ 的周期 $q$，首先我们知道 $p\nmid q$，因为如果 $q$ 是 $p$ 的倍数的话就间接指出 $p^\infty=pre_t(p)\cdot p^\infty$，则 $t$ 是 $p$ 的整周期，$p$ 就不是原串的最小周期了。于是我们知道 $q>\dfrac n2$，因为 $p\nmid q$，如果 $q\le \dfrac n2$，则会必然会有一个小于 $p$ 的周期（弱周期引理）。不难发现由于 $|p|\le\dfrac n2$，于是 $k>1$，那么根据周期的定义，我们知道 $q=suf_{n-|q|}(s)\cdot pre_{2|q|-n}(p^\infty)$（把 $q$ 重复两次和串匹配），于是我们得知 $(|q|\bmod|p|)$ 和 $(|p|-(|q|\bmod|p|))$ 同为 $p$ 的周期，进而通过周期引理我们知道 $p$ 必然有一个长为 $g=(|q|\bmod|p|,|p|)$ 的周期，而由于 $g<|p|$ 且 $g\mid(|p|)$，我们知道 $g$ 是 $p$ 的一个整周期，则 $g$ 也是原串的一个周期且长度小于 $p$，形成矛盾。于是我们得证。

这样的话，一个周期小于 $\dfrac n2$ 的字符串经过一次操作之后 border 仍为 $n-p$，那么此时的最短周期就为 $n+(n-p)-(n-p)=n>\dfrac{n+(n-p)}2$。于是我们现在只需要讨论周期大于 $\dfrac n2$ 的情况。

对于这种情况，即 $k=1$，我们有一个结论。令 $B$ 为 $s$ 的最长 border，$l$ 为 $B$ 的最小整周期，令 $B=l^j$，然后找到最大的 $i$ 使得 $pre_{i|l|}(s)=l^i$。首先 $i|l|<n+|l|$，因为反之的话，首先我们知道 $|l|\nmid n$（$s$ 有一个整周期的情况我们已经在题解最开始讨论过了），于是我们知道 $i|l|-n\ge |l|$，不妨令 $n\equiv q\pmod{|l|}$，则 $suf_{|l|-q}(l)$ 既是 $l$ 的周期也是 $l$ 的 border，于是 $l$ 会有一个更小的整周期，形成矛盾。

有个结论：我们进行第 $b$ 次操作后的最长 border 长度为 $\min\{2^bj,i\}|l|$。考虑归纳证明。$b=0$ 时显然，我们考虑 $b>0$。在进行这一操作前的字符串，假令其长度为 $n$，我们知道最长 border 长度是 $\min\{2^{b-1}j,i\}|l|$ 的，那么显然进行这一操作后的字符串会有一个长为 $\min\{2^bj,i\}|l|$ 的 border，我们只需要证明不存在一个比其更长的 border。

- $i\ge2^bj$：则如果存在 $|\text{border}|>2^bj|l|$，则存在 $|\text{周期}|<n+2^{b-1}j|l|-2^bj|l|=n-2^{b-1}j|l|$，而我们知道进行操作前的字符串 $\text{周期}=n-2^{b-1}j|l|$，形成矛盾。
- $i<2^bj$：我们考虑把这个 border 和 $s$ 的前缀进行匹配。
  - $|\text{border}|=l^k$：这意味着 $l^k=l^i\cdot s_{[i|l|,k|l|]}$。由于 $k>i$，这显然不可能，因为这意味着 $pre_{(i+1)|l|}(s)=l^i$，则我们的 $i$ 是应该更大的，产生矛盾。
  - $|\text{border}|\ne l^k$：假令 $|\text{border}|\equiv q\pmod l$，$|\text{border}|=d$，则我们得到 $l^i\cdot s_{[i|l|,d]}=suf_q(l)\cdot l^{\left\lfloor\dfrac d{|l|}\right\rfloor}$。由于 $\dfrac{d}{|l|}\ge i$，我们知道 $l=suf_q(l)\cdot pre_{|l|-q}(l)$，即 $q$ 既是 $l$ 的周期也是 $l$ 的 border，则 $l$ 有一个更小的整周期，产生矛盾。

于是我们只需要找到 $i,j$ 后直接模拟即可，时间复杂度 $O(n+\log K)$（$s$ 有整周期时的快速幂）。

[mivik.h](https://mivik.gitee.io/mivik.h) / [代码](https://paste.ubuntu.com/p/zVMmrcjRFy/)


---

## 作者：xh39 (赞：3)

前置算法:①kmp求next。②快速幂。

本题解观察规律得出的结论较多,有些未证明。

需分两部分考虑。一部分是subtask1,2,另一部分是subtask3。
## subtask1
发现每次都会增加 $(|s|-1)$ 个字符。可以列出递推式$f[i]=f[i-1]\times 2-1$。其中  $f[i]$ 表示第 $i$ 天的长度。

而 $f[i-1]$ 又可以由 $f[i-2]$ 递推，所以$f[i]=(f[i-2]\times 2-1)\times 2-1=4 \times f[i-2]-3$。

又可以得$f[i]=8\times f[i-3]-7$。

观察规律，$f[i]=2^{j}\times f[i-j]-(2^{j}-1)$。

所以$f[k]=2^{k}\times f[k-k]-(2^{k}-1)=2^{k}\times n-2^{k}+1$。然后用快速幕优化即可。

```cpp
#include<iostream>
using namespace std;
#define mod 998244353
long long cf(long long a,long long b){
	long long sum=1;
	while(b>1){
		if(b&1){
			sum=sum*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return a*sum%mod;
}
int main(){
	long long n,k,ykb;
	cin>>n>>k;
	ykb=cf(2,k);
	cout<<(n*ykb-ykb+1+mod)%mod;
	return 0;
}
```
## subtask1+subtask2
找出循环节即可。然后就和subtask1一样了。

枚举循环节长度只需要枚举 $n$ 的因数就可以了，这样可以做到$O(n\times\pi(n))$，$\pi(n)$为因数个数。理论上最坏$O(n\sqrt n)$，事实上$\pi(n)$远远达不到$\sqrt n$。所以可以过。

```cpp
#include<iostream>
using namespace std;
#define mod 998244353
long long cf(long long a,long long b){
	long long sum=1;
	while(b>1){
		if(b&1){
			sum=sum*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return a*sum%mod;
}
string s;
long long n;
bool check(int len){
	int i;
	for(i=0;i<n;i++){
		if(s[i]!=s[i%len]){ //判断。对于所有i,j满足s[i*len+j]=s[i]。所以可以这样写。
			return false;
		}
	}
	return true;
}
int main(){
	long long k,ykb,i;
	cin>>n>>k>>s;
	for(i=1;i<n&&((n%i)||!check(i));i++){ //多个循环节找最短。所以是从小到大枚举。
	}
	ykb=cf(2,k);
	cout<<(n/i*ykb-ykb+1+mod)*i%mod; //i是循环节长度,n/i就是循环节的个数。最后还要乘上长度i。
	return 0;
}
```
## subtask3
需要观察规律。

对于样例```ioioi```，每次都会添加一个```ioi```。那是不是每次添加的串都一样呢?

有一个反例```aaaaaba```，模拟一下可以发现，第 $1$ 次添加 $1$ 个```a```，第 $2$ 次添加 $2$ 个```a```，第 $3$ 次添加 $4$ 个```a```，之后都添加5个a。

似乎是按照 $1,2,4,8,...,2^{i},...,a,a,a,...$ 这样的规律。($a$ 为一个常数)

那就一直枚举，直到添加到出现两次添加的字符串长度一样。可以做到 $O(n\times log_{2}(n))$，可能tle(没试过)。就算卡过去了也要追求更好的算法。

所以观察$a$到底为何值。

```abababacab```

设原串的前后缀相等串为$same$。

会发现添加$4$次后所以添加的串都是```abababa```。通过上面两组例子。最后添加的字符串就是**从左到右一直循环匹配 $same$ 能匹配多少。**

比如对于第二个例子，在串中从左到右一直匹配```ab```，可以匹配$3$整串和额外一个字符```a```。

思路可以见代码，下面一行可能有些复杂。

所以总体首先用 kmp 找到 $same$ 串。然后一直循环匹配，能匹配多少字符。然后新建变量 $add$，表示这次添加多少，初始为 $n$，每次乘 $2$，直到超过 $|same|$。不断累计 $add$ 的和。累计过程中不断将 $m$ 减 $1$。最后的值就是 $m\times a+sum\{add\}+n$。

```cpp
#include<iostream>
using namespace std;
#define mod 998244353
long long cf(long long a,long long b){
	long long sum=1;
	while(b>1){
		if(b&1){
			sum=sum*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return a*sum%mod;
}
string s;
long long n;
bool check(int len){
	int i;
	for(i=0;i<n;i++){
		if(s[i]!=s[i%len]){
			return false;
		}
	}
	return true;
}
int Next[5000005];
int main(){
	long long m,ykb,i,j=-1,asdf,sum=0,qwer;
	cin>>n>>m>>s;
	if(n==1){ //特判n=1,直接输出1。
		cout<<1;
		return 0;
	}
	for(i=1;i<n&&((n%i)||!check(i));i++){
	}
	if(i<n){ //若循环节长度小于n,说明是subtask1或subtask2。
		ykb=cf(2,m);
		cout<<(n/i*ykb-ykb+1+mod)*i%mod;
		return 0;
	}
	Next[0]=-1;
	for(i=1;i<n;i++){
		while(j>=0&&s[i]!=s[j+1]){
			j=Next[j];
		}
		if(s[j+1]==s[i]){
			j++;
		}
		Next[i]=j;
	}
	ykb=Next[n-1]+1; //循环节长度。
	if(!ykb){ //特判,不然会出现除数为0然后挂掉。
		cout<<n;
		return 0;
	}
	for(i=0;i<n&&s[i]==s[i%ykb];i++){
	}
	qwer=i; //qwer就是a
	asdf=i/ykb; //循环节个数。
	sum=n;
	for(i=ykb;i<qwer&&m;i<<=1){
		sum+=i;
		m--;
	}
	cout<<(sum%mod+qwer*(m%mod)%mod)%mod;
	return 0;
}
```

---

## 作者：Engulf (赞：2)

很妙的题。

分类讨论一下。

第一种情况，若 $s$ 存在最小整周期，则每进行一次操作，$s$ 的 border 便翻一倍，举个例子（括号内为 border，红色为新增部分）：

$$\texttt{abcabcabc}(6)$$
$$\texttt{abcabcabc\color{red}abcabc\color{black}}(12)$$

如果要证明一下，就记最小整周期字符串是 $t$，$s = \underbrace{t+t+\cdots + t}_{m 个}$，加号表示连接，border 是 $(m-1)|t|$，$|t|$ 是字符串 $t$ 的长度。那么操作一次后字符串变为 $s = \underbrace{t+t+\cdots + t}_{2m -1 个}$，border 是 $(2m-2)|t| = 2 \cdot (m-1)|t|$，得证。

形式化地记 $\pi$ 为 $s$ 的 border，那么第 $i$ 次操作要添加 $\pi^{i-1}$ 个字符，这是公比为 $2$ 的等比数列，直接套求和公式，$a_n = \dfrac{a_1(1-q^n)}{1 - q}$，那么答案为 $n + \dfrac{1-2^k}{1-2} = n+2^k-1$。

第二种情况，$s$ 不存在最小整周期，border 会增大 $O(\log n)$ 次停止，之后一直恒为一个数，这个证明有点复杂，可以参考一下[出题人的证明](https://www.luogu.com.cn/article/wvmppdu5)，我这篇题解的目的是提供一个详细的实现步骤。

知道了这个，我们思考一下 border 如何会增长。举个例子：

$$\texttt{abababcab}(2)$$
$$\texttt{abababcab\color{red}ab}(4)$$
$$\texttt{abababcabab\color{red}abab}(6)$$
$$\texttt{abababcabababab\color{red}ababab}(6)$$

发现了一些规律？如果 border 增长，$s$ 一定是形如这样，记 $T$ 是 $s$ 的 border，$X$ 是任意字符串。

$$s = \underbrace{TT\cdots T}_{若干个 T}XT$$

同样的，每操作一次，border 就会翻一倍，似乎最终 border 就恒为 $2^{\left\lfloor\log_2c\right\rfloor}|T|$ 了。

这是不对的，反例是 $\texttt{aaabaa}$，最终 border 是 $3$。

若 $X$ 的前缀是 $T$ 的一个最小整周期，这个 border 会再变大一点，不是翻倍。

这个咋求呢？设 $Y$ 是初始状态下 $s$ 的 border 的最小整周期。如果 $Y$ 不存在，border 不会变大了。否则就往后判断 $X$ 的前缀有多少个 $Y$。记那若干个 $T$ 中和 $X$ 的前缀中一共有 $c$ 个 $Y$，最终的 border 就是 $c|Y|$。

最后看看怎么实现这些步骤。
- 求 border 用 kmp。另外这题多次运用周期 $p$ 和 border $\pi$ 的关系 $p + \pi = |s|$，若 $|s| \bmod (|s| - \pi)=0$，那么 $p = |s| - \pi$ 就是 $s$ 的最小整周期，证明去网上找吧，不是重点。
- 往后找连续相等字符串，即快速判断两区间字符串是否相等，使用字符串哈希解决。

时间复杂度 $O(n + \log k)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using ull = unsigned long long;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e6 + 5;
const int mod = 998244353;
const int base = 233;

int n; ll k;

char str[N];

ull hs[N], pw[N];
ull query(int l, int r) {return hs[r] - hs[l - 1] * pw[r - l + 1];}

int ne[N];

int qpow(int a, ll b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> str + 1;

    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        hs[i] = hs[i - 1] * base + str[i];
        pw[i] = pw[i - 1] * base;
    }

    for (int i = 2, j = 0; i <= n; i++) {
        while (j && str[j + 1] != str[i]) j = ne[j];
        if (str[j + 1] == str[i]) j++;
        ne[i] = j;
    }

    int period = n - ne[n];
    int ans = n;
    if (n % period == 0) {
        ans = (ans + 1ll * ne[n] * (qpow(2, k) - 1) + mod) % mod;
    } else if (ne[n]) {
        int cnt = 1;
        for (int i = ne[n] + 1; i + ne[n] - 1 <= n; i += ne[n])
            if (query(i, i + ne[n] - 1) == query(1, ne[n]))
                cnt++;
            else break;

        int add = 1;
        while (k && add <= cnt) {
            ans = (ans + 1ll * ne[n] * add) % mod;
            add <<= 1;
            k--;
        }

        int len = 1ll * cnt * ne[n] % mod;

        if (ne[ne[n]] && ne[n] % (ne[n] - ne[ne[n]]) == 0) {
            int cyc = ne[n] - ne[ne[n]];
            int t = 1;
            for (int i = cyc + 1; i + cyc - 1 <= n; i += cyc)
                if (query(i, i + cyc - 1) == query(1, cyc))
                    t++;
                else break;

            len = 1ll * t * cyc % mod;
        }

        ans = (ans + 1ll * k % mod * len) % mod;
    }
    cout << ans << "\n";

    return 0;
}
```

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P7525)

神仙结论题。

发现部分分有很强的引导性。

首先全是一个字符的情况，最大 border 显然是 $n-1$（$n$ 为当前字符串长度），然后就可以设 $s_i$ 表示操作 $i$ 次的长度，递推得到 $s_i=2s_{i-1}-1$，其中 $s_0=n$。从而有 $s_k=2^ks_0-(2^k-1)$，直接快速幂即可。

然后考虑最小正周期小于 $n$ 的情况，显然这个串是循环的，不妨设这个最小正周期为 $t$。

然后这个字符串就可以看成由 $t$ 个最小循环节拼成的串，每次把 $t-1$ 个循环节接到串后面，每个循环节长度为 $\dfrac{n}{t}$，把这样的串看成一个字符，所以递推同上，有 $s_k=2^ks_0-(2^k \times \dfrac{n}{t}-\dfrac{n}{t})$
，瓶颈在找最小循环节上，显然最小循环节是 $n$ 的因数，于是枚举所有 $n$ 的因数，对于每个循环节暴力 $O(n)$ 判断即可，由于因数个数很少，并且有找到合法循环节就退出，失配就立刻退出等等剪枝，跑得飞快，可以直接过掉。

然后考虑没有小于 $n$ 的循环节怎么做。首先没有 border 答案显然是 $n$。

显然可以 KMP 预处理出当前能最长匹配的前后缀长度。

发现每次只会在后缀上加一段，所以后缀会越来越大，而前缀不变。

如果前缀是后缀的子串，那么显然加 $k$ 次前缀的长度即可，直接做。

如果后缀是前缀的子串，设后缀长度为 $m$，显然第 $i$ 次操作会在末尾加上 $2^{i-1} \times m$，直到后缀不再是前缀子串为止，然后就回到上一段的情况了，直接做剩下的部分即可。

---

## 作者：TZMydl (赞：1)

本题的字符串可以分为两种情况来处理：

1. 有长度不为 $ \left\vert s \right\vert $ 的整周期：

设 $ t $ 是 $ s $ 的最小循环节，长度为 $ l $ ，这样， $ s $ 就是由 $ \dfrac{n}{l} $ 个 $ t $ 连接而成的字符串。

那么，第一天后，$ s $ 就会变成由 $ \dfrac{n}{l} + \dfrac{n}{l} -1 $ 个 $ t $ 连接而成的字符串。

以此类推，第 $ k $ 天后， $ s $ 就会变成由 $ \dfrac{n}{l} \times 2^k -2^k +1  $ 个 $ t $ 连接而成的字符串。

具体证明可以用数学归纳法，不在这里赘述。

这样，第 $ k $ 天后，$ s $ 的长度就会变为 $ (\dfrac{n}{l} \times 2^k -2^k +1) \times l = n \times 2^k -l \times 2^k + l $ ，然后我们就解决了第一种情况。

2. 没有长度不为 $ \left\vert s \right\vert $ 的整周期：

这种情况的重点在于这样一类字符串：

比如 $ \texttt {xxxxxyx} $ ，我们来模拟一下前四天的操作：

第一天： $ \texttt{xxxxxyxx} $ 。

第二天： $ \texttt{xxxxxyxxxx} $ 。

第三天： $ \texttt{xxxxxyxxxxxxxx} $ 。

第四天： $ \texttt{xxxxxyxxxxxxxxxxxxx} $ 。

我们发现，对于这样的字符串，前若干天最长相同前后缀也是在不断变长的。

我们就可以去找 $ s $ 中最长相同前后缀的最小循环节（若没有，它本身就作为一个循环节），然后看从 $ s_{next[n] + 1} $ 开始还可以再多扩展几段这样的循环节，然后模拟前若干天的操作，直到无法再扩展为止。容易看出，操作后最长相同前后缀变长的天数是 $ O(\log(n)) $ 级别的。

这样之后，若操作尚未结束，因为后面每天的操作都一样了，就是直接把扩展到的最长前缀往后加， $ O(1) $ 计算即可。

这道题的程序就可以写出来了：kmp预处理（这里的 $ next[i] $ 指的是从第 $ 1 $ 位到第 $ i $ 位的前缀字符串的最长相同前后缀），分情况处理即可。

code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long ll;
typedef unsigned long long ull; 
const int mod=998244353,N=2000005,base=19260817;
int n,next[N];
ll k;
char s[N];
ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		b>>=1;
		a=a*a%mod;	
	}
	return res;
}
int main(){
	scanf("%d%lld%s",&n,&k,s+1);
	for(int i=2,j=0;i<=n;++i){
		while(j&&s[i]!=s[j+1])j=next[j];
		j+=(s[i]==s[j+1]);
		next[i]=j;
	}
	if(n%(n-next[n])==0){
		ll l=n-next[n],t=qpow(2,k);
		printf("%lld\n",(n*t%mod-l*t%mod+l+mod)%mod);
	}
	else{
		int l=next[next[n]],sz,pos=next[n],t,ti=0;
		if(next[n]%(next[n]-l)==0)
			sz=next[n]-l;
		else sz=next[n];
		t=next[n]/sz;
		ull h=0;
		for(int i=1;i<=sz;++i)
			h=h*base+s[i]-'a'+1;
		for(int i=pos+1;i+sz-1<=n;i+=sz){
			ull nw=0;
			for(int j=i;j<=i+sz-1;j++)
				nw=nw*base+s[j]-'a'+1;
			if(nw==h)ti++;
			else break; 
		}
		ll ans=n,len=(ti+t)*sz;
		while(k&&t<=ti){
			k--;
			ans=(ans+t*sz)%mod;
			ti-=t;
			t+=t;
		}
		if(k&&ti){
			k--;
			ans=(ans+t*sz)%mod;	
		}
		printf("%lld\n",(ans+(k%mod*len)%mod)%mod);
	}
	return 0;
}
```

代码细节如果有不太清楚的可以私信或评论区问我，我会尽量解答的qaq。

---

