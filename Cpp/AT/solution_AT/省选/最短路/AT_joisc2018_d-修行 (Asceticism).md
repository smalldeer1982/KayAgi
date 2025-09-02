# 修行 (Asceticism)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2018/tasks/joisc2018_d

# 题解

## 作者：DaiRuiChen007 (赞：9)

# JOISC2018D 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_d)

**题目大意**

> 给定 $n,m$，求有多少长度为 $n$ 的排列 $p_i$ 满足 $\sum_{i=1}^{n-1}[p_i>p_{i+1}]=m-1$。
>
> 数据范围：$n,m\le 10^5$。

**思路分析**

对于这类求升高的问题，经典的想法就是容斥，钦定 $k$ 个位置必须是 $p_i>p_{i+1}$，求答案。

此时把连续的 $>$ 看成一段，那么整个序列被分成了 $n-k$ 段，段内定序，大小记为 $s_1\sim s_{n-k}$，那么方案数就是 $\dfrac{n!}{\prod_{i=1}^{n-k}s_i!}$。

注意到这实际上等价于将 $n$ 个不同的球放进 $n-k$ 个不同的非空盒子里的方案数，容易证明两个组合问题之间存在双射，容斥可得此时的方案数为：
$$
\sum_{i=0}^{n-k}\binom{n-k}i(-1)^{n-k-i}\times i^n
$$
二项式反演得到：
$$
\begin{aligned}
\left\langle\begin{matrix}n\\m\end{matrix}\right\rangle
&=\sum_{k=m}^{n}\binom km(-1)^{k-m}\sum_{i=0}^{n-k}\binom{n-k}i(-1)^{n-k-i}\times i^n\\
&=\sum_{i=0}^{n-m}(-1)^{n-m-i}\times i^n\sum_{k=m}^{n-i}\binom km\binom{n-k}{i}\\
&=\sum_{i=0}^{n-m}(-1)^{n-m-i}\times i^n\times\binom{n+1}{m+i+1}
\end{aligned}
$$
其中最后一步我们用到了如下恒等式：
$$
\sum_{i=0}^n\binom ia\binom{n-i}b=\binom{n+1}{a+b+1}
$$
组合意义解释为：$n+1$ 个数里选 $a+b+1$ 个，枚举第 $a+1$ 个数的位置，前 $i$ 个数里选 $a$ 个，后 $n-i$ 个数里选 $b$ 个。

注意我们要求的答案是 $\left\langle\begin{matrix}n\\m-1\end{matrix}\right\rangle$，直接暴力计算。

 时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5,MOD=1e9+7;
ll fac[MAXN],ifac[MAXN];
inline ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
inline ll binom(int n,int m) { return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD; }
signed main() {
	int n,m;
	scanf("%d%d",&n,&m),--m;
	for(int i=fac[0]=ifac[0]=1;i<=n+1;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	ll ans=0;
	for(int i=1;i<=n-m;++i) ans=(ans+MOD+((n-m-i)%2?-1:1)*ksm(i,n)*binom(n+1,m+i+1)%MOD)%MOD;
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：EuphoricStar (赞：4)

考虑若已求出**钦定** $k$ 个升高的排列数量 $f_k$，那么二项式反演就可以求出**恰好** $k$ 个升高的排列数量 $g_k$，即：

$$g_k = \sum\limits_{i = k}^n (-1)^{i - k} \binom{i}{k} f_i$$

考虑求 $f_i$。相当于钦定原序列构成了 $n - k$ 个上升段。相当于把 $n$ 个数分成 $n - k$ 个**互相区分**的集合，每个集合内部升序排序就是上升段。所以：

$$f_i = \begin{Bmatrix} n \\ n - i \end{Bmatrix} (n - i)!$$

直接 NTT 求一行的斯特林数可以通过 [P5825 排列计数](https://www.luogu.com.cn/problem/P5825)，但是这题的模数只能 MTT。考虑用斯特林数的通项公式展开，把 $f_i$ 代入 $g_k$：

$$\begin{aligned} g_k & = \sum\limits_{i = k}^n (-1)^{i - k} \binom{i}{k} \sum\limits_{j = 1}^{n - i} (-1)^{n - i - j} j^n \binom{n - i}{j} \\ & = \sum\limits_{j = 1}^n (-1)^{n + k + j} j^n \sum\limits_{i = k}^{n - j} \binom{i}{k} \binom{n - i}{j} \\ & = \sum\limits_{j = 1}^n (-1)^{n + k + j} j^n \binom{n + 1}{k + j + 1} \end{aligned}$$

最后一步用到了这个恒等式：$\sum\limits_i \binom{i}{a} \binom{n - i}{b} = \binom{n + 1}{a + b + 1}$。组合意义即为考虑 $n + 1$ 个物品中选 $a + b + 1$ 个，枚举第 $a + 1$ 个物品的位置，加上左边选 $a$ 个的方案数乘上右边选 $b$ 个的方案数。

直接快速幂计算 $i^n$ 就是 $O(n \log n)$ 的，也可以线性筛做到 $O(n)$。

[code](https://loj.ac/s/2009389)

---

## 作者：black_trees (赞：4)

upd: 之前求极限的地方写错了所以重写了一下。

问题可以转化为，恰好有 $k$ 个整数 $i$ 满足 $1\le i < n$ 使得 $p_i > p_{i + 1}$。

因为你每分一个段就是出现一个 $p_i > p_{i + 1}$，这个很好理解。

然后恰好是不好算的，我们转成至多，然后差分一下就行。

这个可以映射为 $n$ 个取值为 $[0, 1]$ 之间的实数的离散型随机变量。

因为我们知道，这 $n$ 个随机变量取值相等的概率是 $0$，而排列中元素取值相等的概率也是 $0$，所以这是一一对应的。

把这 $n$ 个随机变量丢到一个长度为 $1$ 的环上。

然后从 $0$ 走到 $p_1$，再从 $p_1$ 走到 $p_2$，一直走到 $p_n$。

我们记第 $i$ 次的步长为 $a_i$。

于是问题可以转化为求 $\sum a_i \le k + 1$ 的概率（这个上界取极端情况就能卡出来）。

但是这里是实数，或者说是连续的啊，我们不会算（~~其实我们可以积分~~），怎么办呢！

注意到实数的取值是无限的，所以如果我们令随机变量的取值变为 $[0, +\infty)\cap\mathbb{N}$ 也是没有问题的。

那么我们就只需要考虑整数域，也就是离散的情况，这是我们熟悉的。

我们先考虑一个 $[0, V]\cap \mathbb{N}$ 的情况，之后取个极限就行。

问题转化为求 $\sum a_i \le V(k + 1), a_i \in [0, V]\cap \mathbb{N}$ 的概率。

这是经典容斥，钦定有 $i$ 个不满足 $a_i \in [0, V]$，其它不管。

然后这里要算的就是恰好，这部分就是选 $i$ 个出来，然后插板法。

相当于是，你强制有 $i$ 个段已经有 $V$，然后这 $n$ 个段至少都要有一个，问和不大于 $V(k + 1)$ 的方案数。

正常插板法是等于，这里是不大于，所以我们新增一个段然后不够的放在里面就行了！

那么答案是：

$$
\begin{aligned}
&= \dfrac{1}{(V + 1)^n} \sum\limits_{i = 0}^{n} (-1)^i \dbinom{n}{i}\dbinom{V(k + 1) - iV - 1}{n} \\
&= \dfrac{1}{(V + 1)^n} \sum\limits_{i = 0}^{n} (-1)^i \dbinom{n}{i}\dbinom{V(k + 1 - i) - 1}{n} \\
&= \dfrac{1}{(V + 1)^n} \sum\limits_{i = 0}^{n} (-1)^i \dbinom{n}{i}\dfrac{(V(k + 1 - i) - 1)^{\underline{n}}}{n!}
\end{aligned}
$$

然后求个极限：

$$
\begin{aligned}
ans &= \lim\limits_{V \to +\infty} \dfrac{1}{(V + 1)^n} \sum\limits_{i = 0}^{n} (-1)^i \dbinom{n}{i}\dfrac{(V(k + 1 - i) - 1)^{\underline{n}}}{n!} \\
&= \dfrac{1}{n!}\sum\limits_{i = 0}^n(-1)^i\dbinom{n}{i}(k + 1 - i)^n
\end{aligned}
$$

具体细节大概是，我们知道 $\lim\limits_{V\to \infty}\dfrac{V^{\underline{n}}}{V^n} = 1$，然后我们把前面的 $\dfrac{1}{(V+1)^n}$ 扔进 $\sum$ 里，把后面那坨下降幂拆一个 $(V+1)^{\underline{n}}$ 出来凑出 $1$ 就行。

不过你注意到，第一步里面最后一个组合数的部分，上面的部分如果按照 $i \in [0, n]$ 枚举是有可能无意义的，为了优美一点，把 $n$ 偷换成 $k$，然后就得到了式子：

$$
\begin{aligned}
ans &= \dfrac{1}{n!}\sum\limits_{i = 0}^k(-1)^i\dbinom{n}{i}(k + 1 - i)^n
\end{aligned}
$$

然后就做完了，很趣味！


---

## 作者：李至擎 (赞：4)

模拟赛考到了这个，感觉太厉害啦！来写一点东西，以防自己以后看不懂了。

欧拉数：定义一个排列 $p$ 的升高为 $\sum\limits_{i=1}^{n-1}[p_i<p_{i+1}]$，那么欧拉数 $\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle$ 就代表满足升高为 $k$ 的长度为 $n$ 的排列的数量。

可能有点抽象，我们举个例子：比如 $\left\langle\begin{matrix}4\\2\end{matrix}\right\rangle=11$，因为我们可以找出 11 个满足升高为 2 的排列：$\{1,3,2,4\},\{1,4,2,3\},\{2,3,1,4\},\{2,4,1,3\},\{3,4,1,2\},\{1,2,4,3\},\{1,3,4,2\},\{2,3,4,1\},\{2,1,3,4\},\{3,1,2,4\},\{4,1,2,3\}$。

好，接下来我们将重点放在怎么求欧拉数上。因为这是一个排列，我们考虑一个从小到大插入的过程。显然新加入的数如果不在最后一定会新产生一个升高。稍微对新产生的升高与被破坏的升高分类讨论一下就可以得到一个基础的式子：

- 插入到最左边，不会产生升高，从 $\left\langle\begin{matrix}n-1\\k\end{matrix}\right\rangle$ 转移过来；

- 插入到最右边，产生一个升高，从 $\left\langle\begin{matrix}n-1\\k-1\end{matrix}\right\rangle$ 转移过来；

- 插入到一个升高中，新产生的升高与原来的抵消，从 $\left\langle\begin{matrix}n-1\\k\end{matrix}\right\rangle$ 转移过来。原来有 $k$ 个升高，所以有 $k$ 种选法；

- 不插入到一个升高中，新产生一个升高，从 $\left\langle\begin{matrix}n-1\\k-1\end{matrix}\right\rangle$ 转移过来。原来有 $k-1$ 个升高，所以有 $(n-1)-1-(k-1)=n-k-1$ 种选法；

综上所述，可以得到一个最基本的递推式：

$$\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle=(k+1)\left\langle\begin{matrix}n-1\\k\end{matrix}\right\rangle+(n-k)\left\langle\begin{matrix}n-1\\k-1\end{matrix}\right\rangle$$

这样我们就有了一个 $\mathcal{O}(n^2)$ 的 DP 求欧拉数的方法。

这个式子已经可以过掉 [P2401](https://www.luogu.com.cn/problem/P2401) 和 [UVA1485](https://www.luogu.com.cn/problem/UVA1485) 了，但是我们还需要更快的做法。

直接瞪这个式子得不到什么结论，可以手玩几个较小的例子猜一猜结论，比如 $k\le 1$。显然 $\left\langle\begin{matrix}n\\0\end{matrix}\right\rangle=1$。

算 $\left\langle\begin{matrix}n\\1\end{matrix}\right\rangle$ 可以这样：我们钦定小于号放在了第 $i$ 和 $i+1$ 个之间，剩下两边肯定都是下降排列的，只要知道了具体选什么数就可以唯一确定，这一部分方案数是 $\sum\limits_{i=1}^{n-1}\dbinom{n}{i}$。但是这样做可能会出现没有小于号的情况，也就是 $\{n,n-1,\ldots 1\}$ 并不合法，且被计算了 $n-1$ 次，需要减掉，即 $\left\langle\begin{matrix}n\\1\end{matrix}\right\rangle=\left(\sum\limits_{i=1}^{n-1}\dbinom{n}{i}\right)-(n-1)$。

注意到前面那一坨是二项式定理的样子，故 $\left\langle\begin{matrix}n\\1\end{matrix}\right\rangle=\left(\sum\limits_{i=0}^{n}\dbinom{n}{i}\right)-\dbinom{n}{0}-\dbinom{n}{n}-(n-1)=2^n-n-1$。

实际上，我们可以更大胆一些：我们直接猜 $\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle=\sum\limits_{i=0}^k(-1)^i\dbinom{n+1}{i}(k+1-i)^n$。经过试验，我们发现它应该是对的，下面尝试用归纳法证明。

回到上面那个 $\mathcal{O}(n^2)$ 的式子。假设我们已经对 $\left\langle\begin{matrix}n-1\\k\end{matrix}\right\rangle$ 和 $\left\langle\begin{matrix}n-1\\k-1\end{matrix}\right\rangle$ 证明了上述结论，可以证明 $\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle$ 也有同样的结论。

$$
\begin{aligned}
\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle&=(k+1)\left\langle\begin{matrix}n-1\\k\end{matrix}\right\rangle+(n-k)\left\langle\begin{matrix}n-1\\k-1\end{matrix}\right\rangle\\
&=\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i}(k+1)(k+1-i)^{n-1}+\sum\limits_{i=0}^{k-1}(-1)^i\dbinom{n}{i}(n-k)(k-i)^{n-1}\\
\end{aligned}
$$

发现最后一个式子的形式格格不入，考虑枚举原来的 $i+1$ 作为现在的 $i$。

$$
\begin{aligned}
\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle&=\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i}(k+1)(k+1-i)^{n-1}+\sum\limits_{i=0}^{k-1}(-1)^i\dbinom{n}{i}(n-k)(k-i)^{n-1}\\
&=\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i}(k+1)(k+1-i)^{n-1}+\sum\limits_{i=1}^k(-1)^{i-1}\dbinom{n}{i-1}(n-k)(k-i+1)^{n-1}\\
&=\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i}(k+1)(k+1-i)^{n-1}-\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i-1}(n-k)(k-i+1)^{n-1}\\
\end{aligned}
$$

这里，上一步可以把最后一个式子改为从 0 开始枚举是因为在 $i=0$ 时 $\dbinom{n}{i-1}=0$。

把式子们的公因式提出来：

$$
\begin{aligned}
\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle&=\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i}(k+1)(k+1-i)^{n-1}-\sum\limits_{i=0}^k(-1)^i\dbinom{n}{i-1}(n-k)(k-i+1)^{n-1}\\
&=\sum\limits_{i=0}^k(-1)^i(k+1-i)^{n-1}\left[\dbinom{n}{i}(k+1)-\dbinom{n}{i-1}(n-k)\right]\\
\end{aligned}
$$

进行一个式子的拆：

$$
\begin{aligned}
\left\langle\begin{matrix}n\\k\end{matrix}\right\rangle&=\sum\limits_{i=0}^k(-1)^i(k+1-i)^{n-1}\left[\dbinom{n}{i}(k+1)-\dbinom{n}{i-1}(n-k)\right]\\
&=\sum\limits_{i=0}^k(-1)^i(k+1-i)^{n-1}\left[\dbinom{n}{i}(k-i+1)+\dbinom{n}{i}i-\dbinom{n}{i-1}(n-k)\right]\\
&=\sum\limits_{i=0}^k(-1)^i(k+1-i)^{n-1}\left[\dbinom{n}{i}(k-i+1)+\dfrac{n-i+1}{i}\times\dbinom{n}{i-1}i-\dbinom{n}{i-1}(n-k)\right]\\
&=\sum\limits_{i=0}^k(-1)^i(k+1-i)^{n-1}\left[\dbinom{n}{i}(k-i+1)+\dbinom{n}{i-1}(k-i+1)\right]\\
&=\sum\limits_{i=0}^k(-1)^i(k+1-i)^n\dbinom{n+1}{i}\\
\end{aligned}
$$

至此，原结论得证。

（说点闲话：感觉这样推导十分自然，并不需要过多的变形。）

回到这个题：有 $k$ 个位置满足 $p_{i-1}>p_i$ 等价于有 $n-1-k$ 个位置满足 $p_{i-1}<p_i$。这就是欧拉数的定义了。

知道这个结论以后，我们就可以利用快速幂 $\mathcal{O}(n\log n)$ 单点求欧拉数，这道题也就迎刃而解了。

当然，由于幂函数是完全积性函数，且指数固定为 $n$。在模数为质数时，我们可以线性预处理组合数和幂函数，时间复杂度 $\mathcal{O}(\frac{n}{\ln n}\log n+n)=\mathcal{O}(n)$。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18,mod=1e9+7,SIZ=1e5+2;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int qpow(int b,int p){
	int res=1;
	for(;p;p>>=1,b=b*b%mod)if(p&1)res=res*b%mod;
	return res;
}
int jc[100005],iv[100005],ij[100005]; 
int C(int n,int m){
	if(n<0||m<0||n-m<0)return 0;
	return jc[n]*ij[m]%mod*ij[n-m]%mod;
}
int tot,p[100005],np[100005],f[100005];
signed main(){
	int n=read(),m=read();m=n-m;f[1]=1;
	jc[0]=1;for(int i=1;i<=SIZ;i++)jc[i]=jc[i-1]*i%mod;
	iv[1]=1;for(int i=2;i<=SIZ;i++)iv[i]=mod-(mod/i)*iv[mod%i]%mod;
	ij[0]=1;for(int i=1;i<=SIZ;i++)ij[i]=ij[i-1]*iv[i]%mod;
	for(int i=2;i<=SIZ;i++){
		if(!np[i])p[++tot]=i,f[i]=qpow(i,n);
		for(int j=1;j<=tot&&i*p[j]<=SIZ;j++){
			np[i*p[j]]=1;f[i*p[j]]=f[i]*f[p[j]]%mod;
			if(i%p[j]==0)break;
		}
	}
	int res=0;
	for(int i=0;i<=m;i++)res=(res+C(n+1,i)*f[m+1-i]%mod*((i&1)?-1:1)+mod)%mod;
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：MatrixGroup (赞：2)

## 题意

给定 $n,m+1$，求出欧拉数 $\left<\begin{matrix}n\\m\end{matrix}\right>$。

## 题解

$$
\begin{array}{llr}
\left<\begin{matrix}n\\m\end{matrix}\right>&=\displaystyle\sum_{\sum a=n,a\ge 1}\dbinom{n}{a}\dbinom{n-|a|}{n-m-1}(-1)^{|a|-m-1}&\text{(*)}\\
&=\displaystyle \sum_{k=1}^n\dbinom{n-k}{n-m-1}(-1)^{k-m-1}\sum_{\sum a=n,a\ge1,|a|=k}\dbinom{n}{a}\\
&=n!\displaystyle \sum_{k=1}^n\dbinom{n-k}{n-m-1}(-1)^{k-m-1}[x^n](e^x-1)^k\\
&=\displaystyle \sum_{k=1}^n\dbinom{n-k}{n-m-1}(-1)^{k-m-1}\sum_{i=0}^k\dbinom{k}{i}(-1)^{k-i}[x^n]e^{ix}\\
&=n!\displaystyle \sum_{k=1}^n\dbinom{n-k}{n-m-1}\sum_{i=0}^k\dbinom{k}{i}(-1)^{m-1-i}\dfrac{i^n}{n!}\\
&=\displaystyle \sum_{i=0}^n(-1)^{m-1-i}i^n\sum_{k=0}^n\dbinom{n-k}{n-m-1}\dbinom{k}{i}\\
&=\displaystyle\sum_{i=0}^n(-1)^{m-1-i}i^n\dbinom{n+1}{n-m+i}&\text{(**)}
\end{array}
$$

$\text{(*) }$ 容斥（二项式反演），考虑把数列分割成 $m+1$ 个上升子段的方案数之和，也有可能更少。

$\text{(**)}$ 考虑组合意义。$n+1$ 个格子里放 $n-m+i$ 个球，上式枚举了第 $n-m$ 个球的位置。

---

## 作者：Purslane (赞：0)

# Solution

直接上二项式反演。钦定有 $j$ 个位置满足 $p_{i} > p_{i+1}$。

这样会被分为若干连续段（通过钦定的大于关系连接），则只需要将数填到连续段内，就会自动排好序。

钦定 $j$ 个连续段之后的方案数就是：

$$
\sum_{i_1+i_2+ \cdots + i_j = n,i \ge 1} \dfrac{n!}{i_1!i_2!\cdots i_j!}
$$

这个东西就是 $n![x^n](e^x-1)^j$，即 $\sum_{i=0}^j e^{ix}\dbinom{j}{i}(-1)^{j-i}$。

而显然 $[x^n]e^{ix} = \dfrac{i^n}{n!}$，得到

$$
\sum_{j=k}^{n}(-1)^{j-k} \dbinom{j}{k}\sum_{i=0}^{n-j} \dbinom{n-j}{i}(-1)^{n-j-i} i^n
$$

看 $i$，发现其系数为 $(-1)^{n+i+k} \sum_j \dbinom{n-j}{i}\dbinom{j}{k}$，后者求和显然就是 $\dbinom{n+1}{i+k+1}$。

代码略。

---

## 作者：OldDriverTree (赞：0)

# Solution

我们先把 $k$ 减 $1$，方便处理。

然后同时限制小于和大于显然是不好做的，因此考虑容斥。

我们枚举 $S$，并钦定 $S$ 中的所有元素 $x$ 都有 $p_{x-1}>p_x$，那么剩下的方案数是好求的：我们先令每个连续段（同一连续段的大小关系确定）的长度为 $a_1,a_2,\dots,a_{n-\vert S\vert}$，那么此时排列的方案数就为 $\dfrac{n!}{\prod\limits_{i=1}^{n-\vert S\vert} a_i!}$，我们令这个东西为 $f(S)$，那么总方案数就为 $\sum\limits_{\vert S\vert\ge k}(-1)^{\vert S\vert-k}\binom{\vert S\vert}k f(S)$（乘 $\binom{\vert S\vert}k$ 是因为这道题相当于要对所有 $S(\vert S\vert=k)$ 求出限制恰好为 $S$ 的答案之和）。

然后我们可以注意到对于所有大小相等的 $S$（令 $x\vert S\vert$），$f(S)$ 之和就相当于将 $n$ 个有标号的球放进 $n-x$ 个有标号的盒子中，且要求所有盒子非空，这个东西可以考虑容斥，钦定一些空的盒子，方案数就为 $\sum\limits_{i=0}^{n-x}(-1)^i\binom{n-x}i(n-x-i)^n$。

那么总方案数就为：
$$
\begin{aligned}
&\sum_{i=k}^n(-1)^{i-k}\binom ik\sum_{j=0}^{n-i}(-1)^j\binom{n-i}j(n-i-j)^n\\
=&\sum_{i=k}^n\binom ik\sum_{j=0}^{n-i}(-1)^{n-k-j}\binom{n-i}jj^n\\
=&\sum_{j=0}^{n-m}(-1)^{n-k-j}j^n\sum_{i=0}^{n-j}\binom ik\binom{n-i}j\\
=&\sum_{j=0}^{n-m}(-1)^{n-k-j}j^n\binom{n+1}{k+j+1}\\
\end{aligned}
$$

用线性筛求 $i^n$ 可以做到总时间复杂度 $O(n)$。

然后可以发现这个东西是一个卷积的形式，于是你就会 [P5825 排列计数](https://www.luogu.com.cn/problem/P5825) 了。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
//using mint=modint998244353;
const int N=1e5+2,mod=1e9+7;
vector<int> prime; bool st[N];
int n,m,ans,fact[N],ifact[N],f[N];

struct custom_hash
{
	static uint64_t splitmix64(uint64_t x) {
		x+=0x9e3779b97f4a7c15;
		x=(x^(x>>30) )*0xbf58476d1ce4e5b9;
		x=(x^(x>>27) )*0x94d049bb133111eb;
		return x^(x>>31);
	}
	size_t operator() (uint64_t x) const {
		static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x+FIXED_RANDOM);
	}
};
int read() {
	int x=0; bool _=true; char c=0;
	while (!isdigit(c) ) _&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=x*10+(c&15),c=getchar();
	return _?x:-x;
}
int power(int a,int b)
{
	int res=1;
	while (b) {
		if (b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
int C(int n,int m) {
	return fact[n]*ifact[m]%mod*ifact[n-m]%mod;
}
void init()
{
	for (int i=2;i<=n;i++)
	{
		if (!st[i]) prime.push_back(i),f[i]=power(i,n);
		for (int j=0;prime[j]<=n/i;j++) {
			st[i*prime[j] ]=true;
			f[i*prime[j] ]=f[i]*f[prime[j] ]%mod;
			if (!(i%prime[j]) ) break;
		}
	}
}
main()
{
	n=read(),m=read()-1,fact[0]=ifact[0]=ifact[1]=f[1]=1;
	init(); for (int i=1;i<=n+1;i++) fact[i]=fact[i-1]*i%mod;
	for (int i=2;i<=n+1;i++) ifact[i]=ifact[mod%i]*(mod-mod/i)%mod;
	for (int i=1;i<=n+1;i++) ifact[i]=ifact[i-1]*ifact[i]%mod;
	for (int i=0;i<=n-m;i++) {
		int res=f[i]*C(n+1,m+i+1)%mod;
		if ( (n-m-i)&1) ans=(ans-res+mod)%mod;
		else ans=(ans+res)%mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：roger_yrj (赞：0)

## AT_joisc2018_d 修行

### 题意

求有多少个长为 $N$ 排列 $P$ 满足：

$$N-K=\sum\limits_i[P_i<P_{i+1}]$$

$1\le K\le N\le 1e5$

### 题解

我们可以先求至少有 $N-j$ 个位置合法。我们把连续的 $[P_i<P_{i+1}]$ 这相当于把 $N$ 个数放进不同的 $j$ 段里，容斥可得答案为：

$$\sum\limits_{i=1}^j\dbinom{j}{i}(-1)^{j-i}i^n$$

通过二项式反演求出恰好有 $N-K$ 个位置合法的答案：

$$ANS=\sum\limits_{j=1}^{K}\dbinom{N-j}{N-K}(-1)^{K-j}\sum\limits_{i=1}^j\dbinom{j}{i}(-1)^{j-i}i^n$$

交换求和顺序：

$$=\sum\limits_{i=1}^K\sum\limits_{j=i}^{K}\dbinom{N-j}{N-K}\dbinom{j}{i}(-1)^{K-j}(-1)^{j-i}i^n$$

$$=\sum\limits_{i=1}^K(-1)^{K-i}i^n\sum\limits_{j=i}^{K}\dbinom{N-j}{N-K}\dbinom{j}{i}$$

$$=\sum\limits_{i=1}^K(-1)^{K-i}i^n\dbinom{N+1}{N-K+i+1}$$

其中 $\sum\limits_{i=0}^{N}\dbinom{i}{a}\dbinom{N-i}{b}=\dbinom{N+1}{a+b+1}$ 可以理解为枚举 $N+1$ 选 $a+b+1$ 中第 $a+1$ 个数的位置。

### 代码

```cpp
int main(){
	cin>>n>>k;
	fac[0]=1;
	for(int i=1;i<=n+1;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=k;i++)ans=(ans+qpow(-1,k-i)*qpow(i,n)%mod*C(n+1,n-k+i+1)%mod+mod)%mod;
	cout<<ans<<"\n";
}
```

---

## 作者：Arghariza (赞：0)

令 $k\gets k-1$，那么相当于 $n$ 阶排列有 $k$ 个上升的方案数，即为欧拉数 $\left\langle\begin{matrix}n \\ k\end{matrix} \right\rangle$。

考虑容斥，将 恰好有 $k$ 的上升 容斥为 钦定有 $k$ 个上升 的方案数，前者为 $f_k$ 后者为 $g_k$，那么对于每个 $j\ge i$，$f_j$ 对 $g_i$ 有 $\dbinom{j}{i}$ 的贡献次数。

于是：

$$g_i=\sum\limits_{j\ge i}\dbinom{j}{i}f_j$$

即：

$$f_i=\sum\limits_{j\ge i}\dbinom{j}{i}(-1)^{j-i}g_j$$

考虑 $g_i$ 的意义，即将 $n$ 个互不相同的数划分成 $n-i$ 个互不相同的非空集合的方案数。每个集合为由我们钦定的连续的上升构成的连通块，连通块内部固定从小到大排序。

对每个非空集合列出 EGF：

$$\frac{x}{1!}+\frac{x^2}{2!}+\cdots +\frac{x^{n}}{n!}=e^x-1$$

乘起来就是方案数的 EGF：

$$n![x^n](e^x-1)^{n-i}$$

于是：

$$\begin{aligned}f_k&=\sum\limits_{i=k}^{n-1}\dbinom{i}{k}(-1)^{i-k}n![x^n](e^x-1)^{n-i}\\&=\sum\limits_{i=k}^{n-1}\dbinom{i}{k}(-1)^{i-k}n!\sum\limits_{j=0}^{n-i}\dbinom{n-i}{j}e^{jx}(-1)^{n-i-j}\\&=\sum\limits_{i=k}^{n-1}\dbinom{i}{j}\sum\limits_{j=1}^{n-i}\dbinom{n-i}{j}j^n(-1)^{n-j-k}\\&=\sum\limits_{j=1}^{n-k}j^n(-1)^{n-j-k}\sum\limits_{i=k}^{n-j}\dbinom{i}{k}\dbinom{n-i}{j}\end{aligned}$$

根据[范德蒙德卷积推论](https://www.luogu.com.cn/blog/i-am-zhiyangfan/er-xiang-shi-ji-shuo)：

$$\sum\limits_{-q\le k\le l}\dbinom{l-k}{m}\dbinom{q+k}{n}=\dbinom{l+q+1}{m+n+1}$$

所以：

$$\begin{aligned}f_k&=\sum\limits_{j=1}^{n-k}j^n(-1)^{n-j-k}\dbinom{n+1}{j+k+1}\end{aligned}$$

注意到 $p_i\gets n-p_i+1$ 后上升数变为原本的下降数，即 $f_k=f_{n-1-k}$：

$$\begin{aligned}f_k&=\sum\limits_{j=1}^{k+1}j^n(-1)^{n-j-(n-1-k)}\dbinom{n+1}{j+(n-1-k)+1}\\&=\sum\limits_{j=1}^{k+1}j^n(-1)^{k-j+1}\dbinom{n+1}{n+j-k}\\&=\sum\limits_{j=1}^{k+1}j^n(-1)^{k-j+1}\dbinom{n+1}{k-j+1}\\&=\sum\limits_{j=0}^k(j+1)^n(-1)^{k-j}\dbinom{n+1}{k-j}\end{aligned}$$

然后就随便做了，复杂度 $O(n\log n)$ 或 $O(n)$。

---

