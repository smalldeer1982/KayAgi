# 「REOI-p1」打捞

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/0ukve6wl.png)

出题人：XL4453

验题人：犇犇犇犇

文案：小糯米

upd：注意，先取模再取max

## 题目描述

“别介意，我和那些家伙都是打捞者。我们在头一次追寻梦想降落到地表时，就做好丧命的准备和赴死的觉悟了。”

葛力克一行人在一次打捞中，时来运转，获得了不少的宝藏。在归途之路，言及谁的功劳最大之时，大家却起了冲突。有人说自己的宝藏是史上绝无仅有，是在鬼门关前绕了一大圈才好不容易抢到的一个；有人说自己惨淡经营，虽然没有获得那么珍贵的宝物，但数量可观，也足以与之相提并论；也有人说自己的收获二者兼有，应当综合评价云云：总之，场面一片混乱，颇有生死与共的患难之交从此决裂的危险。

于是，大家把目光投到了葛力克的身上，这让他十分为难。思索良久，他决定这样来评价大家的贡献： 

假设一共有 $n$ 名打捞者，第 $i$ 位打捞者 $a_i$ 取得的宝物数量为 $l_i$ ，而其中第 $p$ 件宝物对应的价值则为 $a_{i,p}$ ，那么在计算的时候只需要将每个序列相加求和即可。但是葛力克并不满足于现状，他现在想知道，如果是将两个人的贡献放在一起看待，那么又将如何计算呢？
一番激烈的头脑风暴后，他决定这样来计算两位打捞者 $i,j$ 之间的贡献 $g(i,j)$ ：将 $a_i$ 与$a_j$ 分别复制数遍使得两堆宝物的数量都为 $k$ ，得到两个序列 $a_i',a_j'$ ，则 $g(i,j)= \sum\limits_{p=1}^k a'_{i,p}\times a'_{j,p}$ 。

现在葛力克想知道，这个贡献值的最大值是多少。

因为贡献值可能会很大，超出了正常生物大脑的运算能力，所以我们对它进行 $998244353$ 的取余。

----------
形式化题面：给定一个整数 $n$，和 $n$ 个序列，第 $i$ 个序列 $\{a_i\}$ 长度为 $l_i$，将每个 $a_i$ 复制 $\dfrac k{l_i}$ 遍得到 $\{a'_i\}$ 使得 $\{a'_i\}$ 的长度为 $k$。

试求：$\max\limits_{i=1,j=i+1}^{i,j\leq n}\{g(i,j)\bmod 998244353\}$，其中$g(i,j)= \sum\limits_{p=1}^k a'_{i,p}\times a'_{j,p}$ 。

## 说明/提示

#### 样例解释 $#1$

$a_1'=2, 3, 4, 2, 3, 4, 2, 3, 4, 2, 3, 4$。  
$a_2'=1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4$。  
$g(1,2)=2\times1+3\times2+4\times3+2\times4+3\times1+4\times2+2\times3+3\times4+4\times1+2\times2+3\times3+4\times4=90$。

#### 样例解释 $#2$

$g(1,2)\bmod998244353=599517664$。  
$g(1,3)\bmod998244353=350889018$。  
$g(2,3)\bmod998244353=66930325$。  
$\max\limits_{1\leq i < j \leq n}\{g(i,j)\bmod998244353\}=599517664$。  

#### 数据范围

对于 $10\%$ 的数据，有 $n=2$。  
对于 $30\%$ 的数据，有 $k \leq 100$。  
对于 $60\%$ 的数据，所有 $l_i$ 两两互质，即 $\gcd(l_i,l_j)=1(1\leq i < j \leq n)$，$\gcd$ 为[最大公约数](https://oi-wiki.org/math/number-theory/gcd/)。  
对于 $100\%$ 的数据，有 $1\leq n\le 100，1\leq l_i\le 1000，1\leq k,a_{i,j}\le 10^{9}$ 且对于任意的 $i \in [1,n],l_i\mid k$。


## 样例 #1

### 输入

```
2 12
3 2 3 4
4 1 2 3 4```

### 输出

```
90```

## 样例 #2

### 输入

```
3 999999924
4 4 4 5 3
7 1 9 1 9 8 1 0
6 1 1 4 5 1 4```

### 输出

```
599517664```

# 题解

## 作者：qpdk777 (赞：17)

[点这里获得更佳的阅读体验](https://qpdk777.blog.luogu.org/post-ti-xie-p8458-reoi-p1-da-lao)

如果将所有数列都扩展到 $k$ 的长度， $1e9$ 级别的数组肯定会时间空间双爆炸。

所以这个题要利用**周期性**。

不难发现，两个数列的**最小正周期为 $lcm(l_i,l_j)$** ， 我们真正需要处理的是在这个最小正周期内的交叉积。

尽管如此，若 $l_i,l_j$ 都是质数，他们的最小正周期也可以很长很长。遍历最小正周期求交叉积依然无法AC。

通过分析那 $60\%$ 的数据我们可以发现，若 $l_i,lj$ 互质，那么，在一个最小正周期中， $a_i$ 中的每一个元素，都把 $a_j$ 中的每一个元素**乘了 $1$ 次，而且只乘了 $1$ 次**。那么我们可以利用分配律，得

$$\sum a_ia_j=\sum(a_i\sum a_j)=\sum a_i\sum a_j=sum_isum_j$$

可以在 $O(n)$ 的复杂度内解决。60pts到手！

**以此为启发，我们希望把结论推广到不互质的情况。**

若 $l_i,l_j$ 不互质，通过打表可以~~发现~~猜想：对于 $a_i$ 中的每一个元素， $a_j$ 中都有 $\frac{l_j}{gcd(l_i,l_j)}$ 项与之相乘，且每一个参与相乘的项之间的间隔为 $gcd(l_i,l_j)$。

下面给出严谨证明：
不妨设 $l_i<l_j$ ，若 $a_i$ 经过 $m$ 次复制、 $a_j$ 经过 $n$ 次复制后， $a_{i,t}$ 能与 $a_{j,k}$ 对应上，则有

$$(ml_i+t)\equiv(nl_j+k)\pmod {l_j}$$

说简单点就是：

$$(ml_i+t) \bmod l_j=k$$

我们给 $m$ 一个微小的扰动，令 $m'=m+1$ ，也就是再把 $a_i$ 向后复制一次。那么

$$
\begin{aligned}
k'&=(m'l_i+t)\bmod l_j \\
&=(ml_i+t+l_i)\bmod l_j \\
&=[(ml_i+t)\bmod l_j + l_i\bmod l_j]\bmod l_j \\
&=(k+l_i)\bmod l_j \\
\end{aligned}
$$

同理 

$$k''=(k+2l_i)\bmod l_j$$
$$k'''=(k+3l_i)\bmod l_j$$
$$......$$
$$k^{n}{'}=(k+nl_i)\bmod l_j$$

$n$ 最大可取到 $c=\frac{l_j}{gcd(l_i,l_j)}$ 次，因为这么多次之后就回到最开始的 $k$ 了。

所有的 $k$ 都在 $l_j$ 上均匀分布，因此间隔为 $gcd(l_i,l_j)$。

如果对于 $a_i$ 的每一项，都以 $gcd$ 为间隔遍历 $a_j$ 求和，时间复杂度为 $O(\frac{n^2l^2}{gcd(l_i,l_j)})$ ，会超时。

应当首先把 $a_j$ 的隔 $gcd$ 项和求出来（只需要求出前 $gcd$ 项为首的隔 $gcd$ 项和即可），然后在遍历 $a_i$ 时，直接把刚刚求好的和拿过来乘就可以了。

这样求和的循环外层是 $O(gcd)$ ，内层是 $O( \frac{l_j}{gcd(l_i,l_j)})$ ，求和总计是 $O(l)$ ，总的复杂度只有 $O(n^2l)$ ，可以AC。

AC代码：

```cpp
#include<iostream>
#include<cstdio>
#define M 998244353
using namespace std;

inline int read(){
    int x = 0, f = 1;
    char c = getchar();
    while(c<'0' || c>'9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9'){
        x = (x<<3) + (x<<1) + (c-'0');
        c = getchar();
    }
    return  x * f;
}

inline int gcd(int a, int b){
    if(b == 0) return a;
    if(a < b) swap(a, b);
    return gcd(b, a % b);
}

inline int lcm(int a, int b){
    return (int)1ll * a * b / gcd(a, b);
}

int n,k,l[200],a[200][1010];
long long ans;

long long work(int x, int y){
    int c1[1010] = {}, c2[1010] = {};
    int s[1010] = {};
    if(l[x] > l[y]) swap(x, y);
    for(int i = 1; i <= l[x]; i++){
        c1[i] = a[x][i];
    }
    for(int i = 1; i <= l[y]; i++){
        c2[i] = a[y][i];
    }
    int gc = gcd(l[x], l[y]);
    int lc = lcm(l[x], l[y]);

    long long ans = 0;
    
    for(int i = 1; i <= gc; i++){
    	long long tmp = 0;
    	for(int j = i; j <= l[y]; j+=gc){
    		tmp += c2[j];
    		tmp %= M;
		}
		s[i] = tmp;
	}

    for(int i = 1; i <= l[x]; i++){ 
    	int h = 0;
    	h = i % gc;
    	if(h == 0) h = gc;
        ans += 1ll * c1[i] * s[h] % M;
        ans %= M;
    }
    ans *= k / lc;
    ans %= M;

    return ans;
}

int main(){
    n = read(), k = read();
    for(int i = 1; i <= n; i++){
        l[i] = read();
        for(int j = 1; j <= l[i]; j++){
            a[i][j] = read();
        }
    }

    ans = -1e9;
    for(int i = 1; i <= n-1; i++){
    	for(int j = i+1; j <= n; j++)
        	ans = max(ans, work(i, j));
    }
    cout<<ans;

    return 0;
}

```


---

## 作者：bianshiyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8458)

# 题目简意
见形式化题面。

# 分析
首先不难想到复杂度为 $O(n^2\displaystyle \max_{1\le i<j\le n}\operatorname{lcm}(l_i,l_j))$ 的枚举算法，即先枚举每一对 $g(i,j)$ 然后考虑其中最大的循环节这样就不需要用 $O(k)$ 的复杂度来求解 $g(i,j)$，但是这样会超时因为最大可能到 $10^{10}$，所以我们需要改变策略。

首先在枚举每一对 $g(i,j)$ 的时候我们是没有办法通过贪心优化的，因为求最大值是在模意义下进行的，所以无法根据取模之前的结果来确定取模之后的结果是否更大，所以我们只能把希望寄托于更快的求解 $g(i,j)$ 方式上。

前面的暴力分很好获得，灵感来源于 $60$ 分的部分分上，先考虑 $(l_i,l_j)=1$ 的情况，此时可以只处理长度为 $l_i\cdot l_j$ 的部分，因为会一直循环，且有 $l_il_j\mid k$。容易发现答案就是两者和的乘积，证明可以考虑贡献计算，即考虑 $l'_i$ 中的每个数找到在 $l'_j$ 与其相乘的部分，因为 $l'_i$ 是把 $l_i$ 重复很多次，$l'_j$ 同理，所以只用讨论 $l_i$ 上的位置即可。易得出在 $l_i$ 上对于每一个位置 $x$ 都有在 $l_j$ 中位置为 $(x+kl_i-1)\bmod l_j+1$ 的位置产生贡献,其中 $k\in [0,l_j)$ 且其中两两不同，证明可参考完系的性质，也可从后文一般情况中这部分的证明进行类比。故根据容斥原理，后者取遍 $1,2\cdots l_j$ 每个数，最后根据乘法分配律可证得。

接下来考虑 $(l_i,l_j)=d(d\neq 1)$ 的情形我们可以找几组数据找下规律，易发现在 $l_i$ 对于每一个位置 $x$ 都有在 $l_j$ 中位置为 $(x+kl_i-1)\bmod l_j+1\equiv x \pmod d$ 的位置产生贡献,其中 $k\in [0,\frac{\operatorname{lcm}(l_i,l_j)}{l_i})$，说人话就是 $l_j$ 中能对 $x$ 产生贡献的位置要和 $x$ 关于模 $d$ 同余。

证明的方法与上面类似。具体来讲，需要证明对于 $\forall k\in [0,\frac{\operatorname{lcm}(l_i,l_j)}{l_i})$ 都有上式成立，且对于不同的 $k$ 所求出的位置两两不同。

后者较为好整，考虑反证法，假设 $\exists k_1\neq k_2$ 满足

$(x+k_1l_i-1)\bmod l_j+1=(x+k_2l_i-1)\bmod l_j+1$

化简一下：$k_1l_i\equiv k_2l_i\pmod {l_j}$

进一步的得到：$k_1\frac{l_i}{d}\equiv k_2\frac{l_i}{d}\pmod {\frac{l_j}{d}}$

而 $(\frac{l_i}{d},\frac{l_j}{d})=1$，两边约去 $\frac{l_j}{d}$ 之后得到 $k_1\equiv k_2\pmod {\frac{l_j}{d}}$。但 $k_1,k_2\in [0,\frac{\operatorname{lcm}(l_i,l_j)}{l_i}=\frac{l_j}{d})$，故有 $k_1=k_2$ 成立，与 $k_1\neq k_2$ 矛盾。

接下来证明前面的部分，将式子 $(x+kl_i-1)\bmod l_j+1\equiv x \pmod d$ 等价为：$(x+kl_i-1)\bmod l_j+1=md+x$

进一步的：$x+kl_i-1=md+x-1+sl_j$

即：$kl_i=md+sl_j$，也就是 $\frac{kl_i}{d}=m+s\frac{l_j}{d}$

有裴蜀定理可知对于 $\forall k$ 都有无穷多组 $m,s$ 使其成立，且可以调整 $s$ 使得 $m$ 落在 $[0,\frac{l_j}{d})$ 内，这样子可以保证解有意义，故式子得证。

所以这时候答案就是对于模 $d$ 意义下的位置作为 $l_i$ 和 $l_j$ 共同的起点，从起点开始把 $l_i$ 中相隔 $d$ 的位置进行求和，$l_j$ 中相隔 $d$ 的位置进行求和，两者乘积就是答案，这样子可以保证从起点开始 $l_i$ 和 $l_j$ 中每次遍历到的位置都关于 $d$ 同余，与刚才推倒的式子相符，时间复杂度 $O(n^2\max_{i=1}^n l_i)$。

# 代码实现
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1100;
const int mo=998244353;
int n,l[N];
ll k,a[N][N],ans;

int gcd(int x,int y)
{
	if(y==0) return x;
	return gcd(y,x%y);
}

int lcm(int x,int y)
{
	return (ll)(x*y)/gcd(x,y);
}

ll g(int x,int y)
{
	int gc=gcd(l[x],l[y]);
	int lc=lcm(l[x],l[y]);
	ll res1=0,res2=0,res=0;
	for(int i=1;i<=gc;i++)
	{
		res1=res2=0;
		for(int j=i;j<=l[x];j+=gc)
		res1=(res1+a[x][j])%mo;
		for(int j=i;j<=l[y];j+=gc)
		res2=(res2+a[y][j])%mo;
		res=(res+(ll)res1*res2%mo)%mo;
	}
	res=(ll)(k/lc)*(res)%mo;
	return res;
}

int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&l[i]);
		for(int j=1;j<=l[i];j++) scanf("%lld",&a[i][j]);
	}
	for(int i=1;i<=n;i++)
		for(int ii=i+1;ii<=n;ii++) ans=max(ans,g(i,ii));
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：JWRuixi (赞：0)

~~Chtholly 粉丝前来打卡！~~

- 题意

给定一个整数 $n$，和 $n$ 个序列，第 $i$ 个序列 $\{a_i\}$ 长度为 $l_i$，将每个 $a_i$ 复制 $\dfrac k{l_i}$ 遍得到 $\{a'_i\}$ 使得 $\{a'_i\}$ 的长度为 $k$。

试求：$\max\limits_{i=1,j=i+1}^{i,j\leq n}\{g(i,j)\bmod 998244353\}$，其中 $g(i,j)= \sum\limits_{p=1}^k a'_{i,p}\times a'_{j,p}$ 。

- 分析

首先引入一个结论，若 $\gcd(x,y)=1$，在模 $x$ 的意义下有：$\{y,2y,\dots,xy\}=\{0,1,2,\dots,x-1\}$。

在知道这个结论的基础下这道题因该就很好做了，首先显然以 $\operatorname{lcm}(l_x,l_y)$ 为一个循环节，后面的都重复。

那么如何应用顶上那个结论呢？

考虑以 $g=\gcd(l_x,l_y)$ 为一段，那段数就可以应用以上的结论，形式化的 $i\equiv j\pmod{g}$，则在一个循环节内有且仅有一个 $a_{x,i}\times a_{y,j}$ 贡献到答案，那就结束了！

时间复杂度 $O(n^2 L)$，$L$ 为 $l_i$ 的值域。

- code

```cpp
#include <bits/stdc++.h>
#define LL long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(105), maxm(1005), mod(998244353);
int n, k, a[maxn][maxm], l[maxm], s[maxm], ans;

int work (int x, int y) {
	int m = __gcd(l[x], l[y]), res = 0;
	if (l[x] > l[y]) swap(x, y);
	for (int i = 0; i < m; i++) s[i] = 0;
	for (int i = 1; i <= l[y]; i++) s[i % m] = (s[i % m] + a[y][i]) % mod;
	for (int i = 1; i <= l[x]; i++) res = (res + (LL)s[i % m] * a[x][i] % mod) % mod;
	int L = (LL)l[x] * l[y] / __gcd(l[x], l[y]);
	res = (LL)res * k / L % mod;
	return res;
}

int main () {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		l[i] = read();
		for (int j = 1; j <= l[i]; j++) a[i][j] = read();
	}
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) ans = max(ans, work(i, j));
	write(ans);
}
```

---

