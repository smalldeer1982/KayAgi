# 「RiOI-2」likely

## 题目背景

小 E 喜欢把东西排成环状，而不是一条链。

近些天，她在学校学到了正负号。她把它们放在了环上，作为密码。

然而，她现在已然忘却了，只看到草稿纸上的一个数字。那是什么？

## 题目描述

对于一个长度为 $n$ 的仅包含 $\pm1$ 的序列 $a_0\dots a_{n-1}$，我们定义 $S(a, m) = \displaystyle \sum_{k = 0}^{n - 1} \prod_{l = 0}^{m - 1} a_{(k + l) \bmod n}$。

给定 $n, m, k$，求在 $2^n$ 个不同的序列 $a$ 里，试求出有多少不同的 $a$ 满足 $S(a, m) = k$。

答案对 $998,\!244,\!353$ 取模。

## 说明/提示

### 样例解释

对于第一组样例的第一组数据，不符合要求的只有 $a=[1,1,1,1]$，$a=[-1,-1,-1,-1]$，$a=[1,-1,1,-1]$ 和 $a=[-1,1,-1,1]$，所以答案为 $2^4-4=12$。

对于第一组样例的第二组数据，符合要求的只有 $a$ 中恰有奇数个 $-1$，所以答案为 $2^8=256$。

### 数据规模与约定

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $T \leq$ | $\sum n \leq$ | $m \leq$ |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $5$ | $1$ | $20$ | / |
| $1$ | $10$ | $5$ | $10^5$ | $2$ |
| $2$ | $10$ | $5$ | $10^5$ | $4$ |
| $3$ | $15$ | / | $7\times10^3$ | / |
| $4$ | $20$ | / | $10^5$ | / |
| $5$ | $40$ | / | / | / |

对于所有数据，保证 $2 \leq m \leq n \leq 5\times 10^6$，$0 \leq \lvert k\rvert \leq n$，$1 \leq T \leq 10$，$\sum n\leq 5\times10^6$。

## 样例 #1

### 输入

```
9
4 2 0
9 9 -9
9 3 3
20 8 -12
114 5 14
191 9 81
1036 854 104
998244 353 4
2147483 64 7```

### 输出

```
12
256
108
10000
661235724
741150826
500003636
222931421
404094315```

## 样例 #2

### 输入

```
6
8 4 0
12 4 0
16 4 0
20 4 0
24 4 0
28 4 0```

### 输出

```
176
1728
26160
368000
5413856
80212608```

## 样例 #3

### 输入

```
4
6 2 0
10 2 0
9 9 7
9 3 6```

### 输出

```
0
0
0
0```

# 题解

## 作者：Y_B_X (赞：7)

[原题链接](https://www.luogu.com.cn/problem/P9501)

>题意：求满足 $\sum\limits_{k=0}^{n-1}\prod\limits_{j=0}^{m-1}a_{(k+j)\bmod n}=k,\forall_{i\in[0,n)}\ a_{i}=\pm 1$ 的 $a$ 的数量。  
$n,m\leq 5\times 10^6 $。

为方便考虑，以下下标均自动对 $n$ 取模，$\oplus$ 指异或，$\bigoplus $ 指异或和。 

重新设 $A_{i}\!=\!0/1$，并将限制条件改为 $\sum\limits_{k=0}^{n-1}(-1)^{\bigoplus \limits_{0\leq j<m}A_{k+j}}=k$。

首先考虑 $m=1$ 怎么做，此时 $\sum\limits_{k=0}^{n-1}(-1)^{A_i}=k$，设 $A_i=1$ 的 $i$ 的个数为 $p$，则有 $-p+n-p=k$，所以 $p=\frac{n-k}{2}$（$n-k$ 不是偶数时答案必为 $0$）。那这时答案显然为 $\binom{n}{p}$。

对于一般情况，设 $B_i=\bigoplus \limits_{0\leq j<m}A_{i+j}$，则 $B_i$ 中 $1$ 的个数有 $p=\frac{n-k}{2}$ 个，即 $\sum\limits_{0\leq i<n}B_i=p$。

考虑统计 $B$ 的个数，而 $B$ 由 $A$ 确定，那接下来要重点做的是便是：  
$1.$ 找到每个 $B$ 能对应的 $A$ 的数量。  
$2.$ 找到关系 $B_i=\bigoplus \limits_{0\leq j<m}A_{i+j}$ 中蕴含的 $B$ 的限制条件。 

### $\text{Step 1}:$ $A$ 与 $B$ 的对应关系

假设我们已经有了一个序列 $B$，考虑如何生成所有满足条件的 $A$。

由于 $A_i\oplus A_{i+m}=B_i \oplus B_{i+1}$，等号右边是确定的，所以当 $A_i$ 确定时直接可以推出 $A_{i+m},A_{i+2m}\cdots$。他们间的关系组成了一个长度为 $\frac{n}{\gcd(n,m)}$ 的环，而一共有个 $\gcd(n,m)$ 个环。

![](https://cdn.luogu.com.cn/upload/image_hosting/gtri6nh1.png)

设 $d=\gcd(n,m)$，则我们只需确定 $A_0,A_1\cdots A_{d-1}$ 就能得出全部数。

而 $B_i=\bigoplus \limits_{0\leq j<m}A_{i+j}$ 等价于 $A_i\oplus A_{i+m}=B_i \oplus B_{i+1}$ 并且 $B_0=\bigoplus \limits_{i=0}^{m-1}A_i$。接下来着重看第二个等式。

由于相差 $d$ 的倍数的下标之间的关系已经明确，**所以 $B_{0}=\bigoplus \limits_{0\leq j<m}A_{j}$ 本质上是 $B_0$ 等于 $m/d$ 个  $A_0\oplus A_1\oplus \cdots \oplus A_{d-1}$ 相异或，再异或上一个已知的数**。

![](https://cdn.luogu.com.cn/upload/image_hosting/r0qov496.png)

当 $m/d$ 是偶数时，$A_0,A_1\cdots A_{d-1}$ 分别出现偶数次，都自己跟自己异或没了，不再有对他们间的限制，方案数为 $2^d$。   
当 $m/d$ 是奇数时，$A_0\oplus A_1\oplus \cdots \oplus A_{d-1}$ 会将明确等于一个数 $0/1$。由于在所有情况下，所有数异或起来等于 $0$ 和等于 $1$ 的方案数相同（改变一个数则一一对应），方案数为 $2^{d-1}$。

所以每个 $B$ 会对应 $2^{d-[m/d\in \mathrm{odd}]}$ 个 $A$。

### $\text{Step 2}:$ $B$ 的限制条件

对于一个环，相邻两个 $A$ 间的限制条件是 $A_i\oplus A_{i+m}=B_i \oplus B_{i+1}$。但由于这是一个环，将所有这样的关系异或起来后，等号左边的 $A$ 会变成 $0$（每个数出现两次），所以 $B_{i}\oplus B_{i+1}\oplus B_{i+m}\oplus B_{i+1+m}\oplus \cdots=0$。

设 $C_i=\bigoplus \limits_{j=0}^{n/d-1}B_{i+jd}$，即一个环上所有 $B$ 的异或和，上面说的就是对所有 $i$ 都有 $ C_{i}\oplus C_{i+1}=0$，所以 $C_i=C_{i+1}$。于是所有的 $C_i$ 要么全部等于 $0$，要么全部等于 $1$。也就是说每个环上 $B$ 的和**要么全是奇数，要么全是偶数**。

![](https://cdn.luogu.com.cn/upload/image_hosting/kpdlg0a3.png)

还不止这一限制，依然重新考虑 $B_{0}=\bigoplus \limits_{i=0}^{d-1}A_i$。

根据之前的讨论，当 $m/d$ 是偶数时，$A$ 全消掉了，事实上我们能推导出 $C_{i}$ 必定是 $0$（$\text{Step 1}$ 的第二张图红字等价于 $B_0\oplus B_{2}\oplus B_{4}=0$）。($m/d$ 是奇数时肯定不会有限制，因为和 $A$ 有关。)

证明如下：

由于 $m/d$ 是偶数，$d|m/2$，所以对任意的 $i$，$i$ 和 $i+m/2$ 在同一个环内。

为构建 $A_{i}$ 与 $A_{i+m/2}$ 间的关系，设 $S_i$ 代表从 $i$ 开始，每次将下标 $+m$ 并对 $n$ 取模，直到下标为 $i+m/2$，此过程中遍历到的下标上（包括 $i$ 而**不**包括 $i+m/2$）所有 $B$ 的异或和，那么就有 $A_i\oplus A_{i+m/2}=S_{i}\oplus S_{i+1}$（不断由 $A_{i}\oplus A_{i+m}=B_{i}\oplus B_{i+1}$ 异或得来）。

所以 $B_{0}=\bigoplus \limits_{0\leq i<m/2}A_i\oplus A_{i+m/2}=\bigoplus \limits_{0\leq i<m/2}S_{i}\oplus S_{i+1}=S_{0}\oplus S_{m/2}$。

考虑一下 $S_{0}\oplus S_{m/2}$ 是什么，求 $S_0$ 过程中遍历的最后一个下标 $+m$ 就是 $m/2$，而 $S_{m/2}$ 又以 $0$ 结尾（$0\!+\!m\!=\!\frac{m}{2}\!+\!\frac{m}{2}$），所以这就是从 $0$ 开始，不断将下标 $+m$，直到回到 $0$ 的所有下表标上对应 $B$ 的异或和，注意 $0$ 出现了两次，那这就是 $C_{0}\oplus B_{0}$。

所以 $B_{0}=C_{0}\oplus B_{0}$，也就是 $C_{0}=0$，于是 $C_{0,1\cdots d-1}=0$。

### $\text{Summary}$

设 $t=n/d$，即一个环的长度。

当 $m/d$ 是偶数时，每个环上都只能有偶数个 $B$ 是 $1$，$B$ 一共要有 $p$ 个 $1$，每个 $B$ 对应 $2^d$ 个 $A$，所以答案是：

$$2^d[x^p]\left(\sum_{2|i}\binom{t}{i}x^i\right)^d=[x^p]\left((1+x)^{t}+(1-x)^{t}\right)^d$$

当 $m/d$ 是奇数时，每个环上 $B$ 的和的奇偶性相同，每个 $B$ 对应 $2^{d-1}$ 个 $A$，答案是：

$$2^{d-1}[x^p]\left(\sum_{2|i}\binom{t}{i}x^i\right)^d+\left(\sum_{2|i+1}\binom{t}{i}x^i\right)^d=[x^p]\dfrac{\left((1+x)^{t}+(1-x)^{t}\right)^d+\left((1+x)^{t}-(1-x)^{t}\right)^d}{2}$$

直接 $\text{Ln}+\text{Exp}$ 求多项式 $d$ 次幂，$O(n\log n)$ 巨大常数显然过不了。

把他们俩展开，分别有 $\begin{cases}\displaystyle \sum_{i}\binom{d}{i}\sum_{k}\binom{ti}{k}\binom{t(d-i)}{p-k}(-1)^k,m/d\in \mathrm{even}\\\displaystyle \sum_{2|i}\binom{d}{i}\sum_{k}\binom{ti}{k}\binom{t(d-i)}{p-k}(-1)^k,m/d\in \mathrm{odd}\end{cases}$，于是有了 $O(pd)$ 的做法，也不太行。

（这部分解法是参考了题解区的）但由于已经有了封闭形式，多项式的次数不超过 $n$，按着 $\text{FFT}$ 的方法，将 $n$ 补成 $2$ 的幂 $N$ 后，对于点值 $\omega_{N}^k$ 可以直接快速幂算，单次复杂度 $O(\log t+\log d=\log n)$，而需要的只有一项的系数，可以将点值直接乘上 $\text{IDFT}$ 时的贡献系数得到。

一个小优化：$998244353=1+7\times 17\times 2^{23}$，所以不一定 $N$ 硬要是 $2$ 的幂，还可以是 $7$ 或者 $17,119$ 乘上 $2$ 的某次幂。

这样复杂度是 $O(n\log n)$ 的，代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e6+10;
const int mod=998244353;
int n,m,p,a,b,ans,nn;
int fac[N],ifac[N];
#define sub(x,y) x<y?x-y+mod:x-y
inline int qpow(int x,int k){
	int res=1;
	while(k){
		if(k&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;k>>=1; 
	}
	return res;
}
void work(){
	int N1=1;while(N1<=n)N1<<=1;
	int N2=7;while(N2<=n)N2<<=1;
	int N3=17;while(N3<=n)N3<<=1;
	int N4=119;while(N4<=n)N4<<=1;
	int N=min({N1,N2,N3,N4});
	p=N-p;
	int i,w=qpow(3,(mod-1)/N),wp=qpow(w,p),v=1,vp=1,x,y;
	if((m/b)&1){
		for(i=0;i<N;++i,v=1ll*v*w%mod,vp=1ll*vp*wp%mod){
			x=qpow(1+v,a);y=qpow(mod+1-v,a);
			ans=(1ll*(qpow(x+y,b)+qpow(sub(x,y),b))*vp+ans)%mod;
		}
		ans=1ll*ans*qpow(N,mod-2)%mod;
		ans=ans&1?ans+mod>>1:ans>>1;
	}
	else {
		for(i=0;i<N;++i,v=1ll*v*w%mod,vp=1ll*vp*wp%mod){
			x=qpow(1+v,a);y=qpow(mod+1-v,a);
			ans=(1ll*qpow(x+y,b)*vp+ans)%mod;
		}
		ans=1ll*ans*qpow(N,mod-2)%mod;
	}
}
void main_(){
	cin>>n>>m>>p;ans=0;
	if((n-p)&1)return puts("0"),void();
	p=(n-p)>>1;
	b=__gcd(n,m);a=n/b;
	work();
	cout<<ans<<'\n';
}
int main(){
	int T;cin>>T;
	while(T--)main_();
} 
```

还没结束，这题实际上能 $O(n)$，且不依赖于 $\text{NTT}$ 模数。

回到答案的展开式，后面的求和都是 $\displaystyle \sum_{k}\binom{ti}{k}\binom{t(d-i)}{p-k}(-1)^k$，其中 $i\leq d$，所以 $ti\leq n$。

于是只需求出所有的 $f_i=\displaystyle \sum_{k}\binom{i}{k}\binom{n-i}{p-k}(-1)^k,0\leq i\leq n$。

这很像范德蒙德卷积，却偏偏多了一个 $(-1)^k$，像 $\mathcal{Concrete Mathematics},\mathcal{A=B}$ 等著作也没见着他的影。

但他还是能递推的，可以手搓 $\text{Zeilberger's Algorithm}$ 得到答案：

$$f_{i+1}=\dfrac{1}{n-i}\left(V f_{i}-Uf_{i-1}i\right)$$

$$U=\dfrac{2+3n+n^2-3p-2np+p^2}{(n-p)^2+3(n-p)+2}$$

$$V=\dfrac{2n+3n^2+n^3-4p-9np-4n^2p+6p^2+5mp^2-2p^3}{(n-p)^2+3(n-p)+2}$$

~~我真的不信这玩意能有组合意义。~~

推导过程过于复杂，由于篇幅限制就不再展开，有兴趣的看[这里](https://www.luogu.com.cn/paste/4tiyl3lx)。

由于 $x^2+3x+2\equiv 0\pmod {mod}$ 的解集只能是 $\{mod-1,mod-2\}$，$n-p$ 完全没有那么大，所以不用担心分母为 $0$。

代码没必要放了吧，就一个递推式的事。  
 
$\text{}$

$\text{}$

$\text{}$

$\text{}$

![](https://cdn.luogu.com.cn/upload/image_hosting/jkz98pqg.png)

最优解到底是怎么回事呢？

---

## 作者：tzc_wk (赞：7)

赛后一血来写篇题解。

默认下标从 $0$ 开始。

首先将原序列中的 $1$ 用 $0$ 代替，$-1$ 用 $1$ 代替，问题转化为，有多少个 $01$ 序列，满足恰好有 $\dfrac{n-k}{2}$ 个 $i$ 满足 $i,(i+1)\bmod n,(i+2)\bmod n,\cdots,(i+m-1)\bmod n$ 位置上 $1$ 的个数为奇数。

记 $b_i=a_i\oplus a_{(i+1)\bmod n}\oplus a_{(i+2)\bmod n}\oplus\cdots\oplus a_{(i+m-1)\bmod n}$，$c_i=a_i\oplus a_{(i+m)\bmod n}$，那么有 $b_i\oplus b_{i+1}=c_i$。但是我们并不能直接通过对 $b$ 或者 $c$ 计数来对 $a$ 计数，因为我们考虑连边 $i\to (i+m)\bmod n$，那么这样图上显然会形成 $d=\gcd(n,m)$ 个环，每个环环长为 $l=\dfrac{n}{d}$，而对于一组 $c$，存在一组 $a$ 与之对应的充要条件是 $\forall i\in[0,l-1],\oplus_{j\equiv i\pmod{d}}c_j=0$，换句话说，对于每个 $i$，$c$ 中下标模 $d$ 余 $i$ 的位置上的异或和均为 $0$，这点容易证明，这里不再赘述。

先考虑只有一个环的情况，打表发现 $\gcd(n,m)=1$ 的答案为：

- $\dbinom{n}{k}$（$m$ 为奇数）
- $2\dbinom{n}{k}$（$m,k$ 均为偶数）
- $0$（$m$ 为偶数，$k$ 为奇数）

为什么？先考虑 $m$ 为奇数的情况。我们考虑所有恰好有 $k$ 个 $1$ 的 $b$ 序列，显然它对应的 $c$ 序列满足所有数异或和为 $0$，因此只要 $a_0$ 确定了 $a$ 序列也就确定了。很显然的一件事是，假设 $a_0=0$ 时候的 $a$ 序列为 $a0$，$a_0=1$ 时候的 $a$ 序列为 $a1$，那么有 $a0_i\oplus a1_i=1$。而因为 $m$ 是奇数，所以 $\oplus_{i=0}^{m-1}a0_i,\oplus_{i=0}^{m-1}a1_i$ 中恰好有一者是 $1$，这样存在 $a_0$ 的唯一选择满足我们构造出来的 $\oplus_{i=0}^{m-1}a_i$ 等于我们选择的 $b_0$，这样方案数就是 $\dbinom{n}{k}$。

这样一来其实 $m$ 是奇数，但是 $\gcd(n,m)\ne 1$ 也很容易解决了。还是考虑对 $b$ 序列计数，因为总共有 $d$ 个环，所以相当于，确定 $b$ 序列以及 $a_0,a_1,\cdots,a_{d-1}$ 之后 $a$ 序列就确定了，而正如上文所述，$b$ 序列能够对应出至少一个 $a$ 序列的充要条件是对于每个 $i$，$c$ 中下标模 $d$ 余 $i$ 的位置上的异或和均为 $0$，用 $b$ 的语言来描述，**就是对于所有 $i$，$\bmod d=i$ 的位置上 $b_i$ 的异或和相同**。而 $a_0\sim a_{d-1}$ 的填法，根据上面 $\gcd(n,m)=1$ 情况的推论，恰好有一半是合法的，因此有 $2^{d-1}$ 种。这样用 poly 的语言描述答案就是 $2^{d-1}[x^k](\sum\limits_{i=0}^l[i\bmod 2=0]\dbinom{l}{i}x^i)^d+[x^k](\sum\limits_{i=0}^l[i\bmod 2=1]\dbinom{l}{i}x^i)^d$。至于怎么快速求我们最后再讲。

接下来考虑 $m$ 是偶数的情况，$\gcd(n,m)\ne 1$ 的情况。我们再打个表发现，如果 $\dfrac{m}{d}$ 为奇数，那么答案还是上面那个式子。这是对于每个 $\bmod d$ 的等价类，因为其统计入答案的部分个数是奇数，因此我们改变 $a_0$ 的值也就改变了 $b_0$，改变 $a_1,a_2,\cdots,a_{d-1}$ 的值同理，因此确定了 $b$ 以后，确定 $a_0\sim a_{d-1}$ 的合法方案还是 $2^{d-1}$。但是 $\dfrac{m}{d}$ 为偶数的情况就不是这样了，因为改变 $a_0$ 不会改变 $b_0$，因此这种情况下一组 $b$ 合法的条件就不再只是对于所有 $i$，$\bmod d=i$ 的位置上 $b_i$ 的异或和相同，还有个额外条件：**每个等价类中 $0$ 的个数都是奇数**（别问我为什么是这个，打表打出来的）。因此答案是 $2^{d}[x^k](\sum\limits_{i=0}^l[i\bmod 2\ne(\dfrac{n}{d})\bmod 2]\dbinom{l}{i}x^i)^d$。

现在问题变为计算 $[x^k](\sum\limits_{i=0}^l[i\bmod 2=c]\dbinom{l}{i}x^i)^d$，其中 $c\in\{0,1\}$。很显然的想法是 FFT，但是 $n\le 5\times 10^6$，DFT 直接 T 飞，但是我们发现 $c=0$ 的时候式子是 $(\dfrac{(1+x)^l+(1-x)^l}{2})^d$，$c=1$ 时候是 $(\dfrac{(1+x)^l-(1-x)^l}{2})^d$，于是你其实不用 DFT，计算 $f(\omega_n^t)$ 时候直接把它带进去快速幂即可。而 IDFT 只用求单点，因此也可以 $O(n)$。这样复杂度虽然 $O(n\log n)$，但瓶颈只有快速幂，可以通过。

```cpp
const int MAXN=5e6;
const int MOD=998244353;
const int pr=3;
const int ipr=332748118;
const int INV2=MOD+1>>1;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD)if(e&1)ret=1ll*ret*x%MOD;return ret;}
int n,m,k,d,fac[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=1)+1;i<=n;i++)ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int binom(int n,int k){
	if(k<0||n<k)return 0;
	return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;
}
int calc(int c){
	int l=n/d,LEN=1;while(LEN<=n)LEN<<=1;
	int w0=qpow(pr,(MOD-1)/LEN),iw0=qpow(ipr,1ll*(MOD-1)/LEN*k%(MOD-1)),res=0;
	for(int i=0,pw=1,ipw=1;i<LEN;i++){
		int pw1=qpow(1+pw,l),pw2=qpow(1-pw+MOD,l);
		int coef0=qpow(1ll*INV2*(pw1+pw2)%MOD,d);
		int coef1=qpow(1ll*INV2*(pw1-pw2+MOD)%MOD,d);
		if(c==0)res=(res+1ll*coef0*ipw)%MOD;
		else if(c==1)res=(res+1ll*coef1*ipw)%MOD;
		else res=(res+1ll*(coef0+coef1)*ipw)%MOD;
		pw=1ll*pw*w0%MOD;ipw=1ll*ipw*iw0%MOD;
	}return 1ll*res*qpow(LEN,MOD-2)%MOD;
}
int main(){
	init_fac(MAXN);
	int qu;scanf("%d",&qu);
	while(qu--){
		scanf("%d%d%d",&n,&m,&k);
		if((k&1)!=(n&1)){puts("0");continue;}
		k=(n-k)/2;d=__gcd(n,m);
		if((m/d)%2)printf("%d\n",1ll*calc(2)*qpow(2,d-1)%MOD);
		else printf("%d\n",1ll*calc(1-(n/d)%2)*qpow(2,d)%MOD);
	}
	return 0;
}
```



---

## 作者：Polaris_Australis_ (赞：5)

关于可爱的 Register_int 把[我在混乱中写的题解](https://www.luogu.com.cn/blog/const1e7/post-1d)直接交上来一事。

污染了大家的眼睛，深感抱歉，决定重新写一篇作为补偿。

首先定义一个无穷数组 $b_i=\prod\limits_{j=0}^{i}a_{j\bmod n}$，则 $c_k=\prod\limits_{l=0}^{m-1}a_{(k+l)\bmod n}=\dfrac{b_{t+m}}{b_t}=b_{t+m}\times b_t$，其中 $0\le k<n$，$t\equiv k\pmod n$。所求答案即为 $\sum\limits_{k=0}^{n-1}c_k$ 为一个定值的方案数，转化为有 $k$ 个 $c_k$ 为 $-1$ 的方案数。

观察一些性质：

1. 合法的 $b$ 和合法的 $a$ 一一对应。
2. $b$ 可以每隔 $\gcd(n,m)-1$ 个分为一组，即共分为 $\gcd(n,m)$ 组，各组之间的值对 $c_i$ 没有影响。
3. 若 $b_{n-1}=1$，则 $b_{n}=b_0$，$b$ 数组循环节为 $n$，否则 $b_{n}\ne b_0$，$b$ 数组的循环节为 $2n$，且 $b_i\ne b_{i+n}$。

现在只需要求有多少合法的 $b$ 数组满足求出的 $c$ 数组中有 $k$ 个 $-1$。把 $b$ 数组分成 $\gcd(n,m)$ 组分别统计，现在考虑所有满足 $i\equiv t\pmod{\gcd(n,m)}$ 的 $b_i$ 的值，设 $p_i=b_{im+t}$（$i\le 0\le \frac{n}{\gcd(n,m)}$），对于 $1\le i<\frac{n}{\gcd(n,m)}$，$1\le j<\frac{n}{\gcd(n,m)}$，$i\ne j$，易知 $p_i$ 和 $p_j$ 互相不影响。$p_{\frac{n}{\gcd(n,m)}}=b_{n\frac{m}{\gcd(n,m)}+t}$，当 $b_{n-1}=-1$ 且 $\frac{m}{\gcd(n,m)}\equiv1\pmod2$ 时 $p_{\frac{n}{\gcd(n,m)}}=-p_0$，否则 $p_{\frac{n}{\gcd(n,m)}}=p_0$。这里显然对于任意的 $0\le i<\frac{n}{\gcd(n,m)}$，$p_i\times p_{i+1}$ 都代表 $c$ 中的一个值且不重复。

假设 $\frac{m}{\gcd{n,m}}\equiv0\pmod{2}$，定义令 $p_i\ne p_{i+1}$ 表示在 $i$ 和 $i+1$ 中插一个板，板的个数就是这组中 $c$ 值中 $-1$ 的个数，插板的唯一限制是板的个数必须为偶数，所以设 $f_i$ 表示产生 $i$ 个 $-1$ 贡献的方案数，当 $i$ 为偶数时，$f_i=2\times\binom{\frac{n}{\gcd(n,m)}}{i}$，令 $F(x)=\sum\limits_{i=0}^{\frac{n}{\gcd(n,m)}}f_ix^i=(x+1)^{\frac{n}{\gcd(n,m)}}+(1-x)^\frac{n}{\gcd(n,m)}$，最终需要的是 $F^{\gcd(n,m)}(x)$，直接把原根带入求点值，$\text{IDFT}$ 的时候只需要处理一项的系数。

$\frac{m}{\gcd{n,m}}\equiv1\pmod{2}$ 的情况和上一种情况差不多，需要讨论 $b_{n-1}$ 的值，仍按照上面的分析方法分析即可。

时间复杂度 $O(n\log n)$，瓶颈在于快速幂。

---

## 作者：Register_int (赞：5)

设 $b_i=\prod\limits_{j=0}^{i}a_j$，则题意转化为 $\sum\limits_{i=0}^{n-1}b_i\times b_{(i+m)\bmod n}\times(-1)^{[i<n][i+m\ge n][b_{n-1}=-1]}=k$。且观察到每个 $b$ 对应唯一的 $a$，直接计算有多少个满足条件的 $b$ 即可。

$i$ 与 $(i+m)\bmod n$ 连边，得到 $\gcd(n,m)$ 个环。对于每个环，可以给每个点赋为 $1$ 或 $-1$ 的权值 $c$，每个环上的点从 $0$ 开始重新标号，则对于一个以 $i$ 为起始点的环（$0\le i<\gcd(n,m)$），$c_0=b_i$，$c_j=c_{j-1}\times b_{l}\times b_{(l+m)\bmod n}\times(-1)^{[i<n][i+m\ge n][b_{n-1}=-1]}$（$l=((j-1)\times m+i)\bmod n$，即第 $j-1$ 个点所对应的原序列上的点），这样赋值之后，环上相邻两项不同则会对上式贡献一个 $-1$，否则贡献一个 $1$。相当于在这个环上插若干个板，满足板的个数是偶数，板的个数即为对答案产生 $-1$ 贡献的对数。

但是会出现一个问题，就是 $c_{\frac{n}{\gcd(n,m)}-1}\times c_{0}$ 对答案产生的贡献可能是错的。考虑额外加一个点 $c_{\frac{n}{\gcd(n,m)}}$，按照和上式同样的方式转移。考虑从 $c_0$ 转移到 $c_{\frac{n}{\gcd(n,m)}}$ 的过程中，一共乘了 $\frac{m}{\gcd(n,m)}$ 个 $-1$，若这个值为奇数且 $b_{n-1}$ 为 $-1$，则 $c_{\frac{n}{\gcd(n,m)}}$ 为 $-c_0$，否则为 $c_0$，所以需要根据 $\frac{m}{\gcd(n,m)}$ 的奇偶性分类讨论。

先枚举 $b_{n-1}$ 的正负性，考虑每种插板方案也并不唯一对应一种 $c$，同时还由 $c_0$ 的值决定，所以每个环的贡献还要翻倍，但并不是所有的环的贡献都要翻倍，包含 $n-1$ 的环已经有一个值确定了，所以不需要翻倍。

思路比较乱，总结一下：

1. 枚举 $b_{n-1}$ 的正负性。
2. 算出单个环对答案的贡献，设 $f_i$ 表示贡献了 $i$ 个 $-1$ 的方案数，插板法即可，记得翻倍。
3. 背包，合并所有环的贡献。

多项式优化不做过多赘述。

by 梅川库子

---

## 作者：DaiRuiChen007 (赞：0)

# P9501 题解

[Problem Link](https://www.luogu.com.cn/problem/P9501)

**题目大意**

> 给定 $n,m,k$，求有多少 $a_0\sim a_{n-1}$ 满足：
>
> - $\forall i\in[0,n)$，满足 $a_i\in\{1,-1\}$。
> - $\sum_{i=0}^{n-1}\prod_{j=0}^{m-1} a_{(i+j)\bmod n}=k$。
>
> 数据范围：$n\le 5\times 10^6$。

**思路分析**

考虑转成 01 序列，那么就是要求 $\sum_{i=0}^{n-1}\bigoplus_{j=0}^{m-1} a_{(i+j)\bmod n}=\dfrac {n-k}2$，以下 $k$ 均指 $\dfrac {n-k}2$。

记 $b_i=\bigoplus_{j=0}^{m-1} a_{(i+j)\bmod n}$，对 $\{b_i\}$ 计数是容易的，但我们要知道 $b_i$ 到 $a_i$ 的对应关系才行。

简单观察发现 $b_i\oplus b_{i+1}=a_i\oplus a_{i+m}$，那么很自然的想法就是把所有 $i,i+m$ 连接，把 $0\sim n-1$ 分成 $d=\gcd(n,m)$ 个环 $C_0\sim C_{d-1}$。

考虑一个环上 $a_i$ 的异或和得到：
$$
\begin{aligned}
\bigoplus_{i\in C_r} a_i\oplus a_{i+m}&=\bigoplus_{i\in C_r} b_i\oplus b_{i+1}\\
\left(\bigoplus_{i\in C_r} b_i\right)\oplus\left(\bigoplus_{i\in C_{r+1}}b_i \right)&=0\\
\bigoplus_{i\in C_r} b_i&=\bigoplus_{i\in C_{r+1}}b_i
\end{aligned}
$$
因此我们要求每个环的 $b_i$ 异或和相等，且 $\sum b_i=k$，那么我们可以用生成函数的语言来描述答案：
$$
\begin{aligned}
&[x^k]\left(\sum_{i=0}^{n/d} [2\mid i]\binom nix^i\right)^d+[x^k]\left(\sum_{i=0}^{n/d} [2\nmid i]\binom nix^i\right)^d\\
=&[x^k]\left(\dfrac{(1+x)^{n/d}+(1-x)^{n/d}}2\right)^d+[x^k]\left(\dfrac{(1+x)^{n/d}-(1-x)^{n/d}}2\right)^d
\end{aligned}
$$
很显然，当我们确定了 $b_0\sim b_{n-1}$ 和 $a_0\sim a_{d-1}$ 之后，我们就能确定整个 $a_0\sim a_{n-1}$。

那么我们就要求有多少种合法的 $a_0\sim a_{d-1}$，使得 $\bigoplus_{i=0}^{m-1} a_i=b_0$。

注意到每个环中都有 $\dfrac md$ 个项对 $b_0$ 有贡献，并且对于 $a_0=0/1$ 的两种情况，每项的元素都恰好相反。

因此对于 $2\nmid \dfrac md$ 的情况，我们翻转 $a_0$ 即可翻转 $C_0$ 对 $b_0$ 的贡献，相当于一个自由元，那么总的方案数恰好是 $2^{d-1}$。

对于 $2\mid \dfrac md$ 的情况，我们需要一些推理：

显然 $d\mid \dfrac m2$，那么所有 $i,i+m/2$ 在同一个环中，我们记 $S_i$ 表示在这个环中 $[id_i,id_{i+m/2})$ 中的 $b_i$ 的异或和（$id$ 表示环中的顺序）。

那么不断运用 $a_i\oplus a_{i+m}=b_i\oplus b_{i+1}$ 直到 $i+m=m/2$，我们得到 $a_i\oplus a_{i+m/2}=S_i\oplus S_{i+1}$。

那么 $b_0=\bigoplus_{0\le i<m/2} a_i\oplus a_{i+m/2}=\bigoplus_{0\le i<m/2}  S_i\oplus S_{i+m/2}=S_0\oplus S_{m/2}$。

考虑 $S_0$ 和 $S_{m/2}$ 是什么，注意到 $S_0$ 的结束位置的下一个就是 $b_{m/2}$，而 $S_{m/2}$ 的结束位置恰好就是 $b_0$。

那么 $S_0\oplus S_{m/2}$ 恰好就是 $C_0$ 中所有 $b_i$ 的异或和再异或上 $b_0$，由于 $S_0\oplus S_{m/2}=b_0$，那么 $C_0$ 中 $b_i$ 异或和为 $0$。

那么一组 $a_0\sim a_{d-1}$ 合法当且仅当 $C_0$ 中所有 $b_i$ 异或和为 $0$，由于每个环和相等，那么所有 $C_i$ 中的异或和为 $0$。

因此答案为：
$$
\mathrm{Answer}=
\begin{cases}
2^{d-1}[x^k]\left(\dfrac{(1+x)^{n/d}+(1-x)^{n/d}}2\right)^d+\left(\dfrac{(1+x)^{n/d}-(1-x)^{n/d}}2\right)^d&2\nmid \dfrac md\\
2^{d}[x^k]\left(\dfrac{(1+x)^{n/d}+(1-x)^{n/d}}2\right)^d&2\mid \dfrac md
\end{cases}
$$
朴素的想法就是直接用 NTT 维护多项式快速幂。

但由于我们只要求多项式的某一项，因此我们可以优化 NTT 的计算过程：

- 先取 $N>n$ 满足 $N\mid P-1$。
- 然后计算 $f(\omega_{N}^0)\sim f(\omega_N^{N-1})$，由于我们的生成函数形式特殊，这里并不需要 NTT，我们直接快速幂就可以 $\mathcal O(N\log N)$ 完成。
- 最后答案的 $x^k$ 系数为 $\sum_{i=0}^{N-1} \left(\omega_N^{-k}\right)^if(\omega_N^i)$，由于我们只要一项的值，因此这里可以 $\mathcal O(N)$ 计算。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=998244353,i2=(MOD+1)/2;
ll ksm(ll a,ll b=MOD-2) {
	ll ret=1;
	for(;b;a=a*a%MOD,b=b>>1) if(b&1) ret=ret*a%MOD;
	return ret;
}
void solve() {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	if((n-k)&1) return puts("0"),void();
	int d=__gcd(n,m),N=1<<(__lg(n)+1),cy=n/d;
	k=(n-k)>>1;
	ll ans=0,w=ksm(3,(MOD-1)/N),iw=ksm((MOD+1)/3,1ll*(MOD-1)/N*k),pw=1,ipw=1;
	for(int i=0;i<N;++i) {
		ll A=ksm(1+pw,cy),B=ksm(1+MOD-pw,cy);
		ll r0=ksm((A+B)*i2%MOD,d);
		if((m/d)&1) {
			ll r1=ksm((A+MOD-B)*i2%MOD,d);
			ans=(ans+(r0+r1)*ipw)%MOD;
		} else ans=(ans+2*r0*ipw)%MOD;
		pw=pw*w%MOD,ipw=ipw*iw%MOD;
	}
	printf("%lld\n",ans*ksm(N)%MOD*ksm(2,d-1)%MOD);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：kyEEcccccc (赞：0)

> $T$ 组数据，给定 $n, m, k$，求所有 $2^n$ 个大小为 $n$ 的由 $\pm 1$ 组成的有标号环 $a_{0\dots n-1}$ 中，有多少个满足 $\sum_{i=0}^{n-1}\prod_{j=0}^{m-1}a_{(i+j)\ \bmod\ n}=k$。对 $998244353$ 取模。
>
> $1\le T\le 10, 2\le n, \sum n\le 5\times 10^6, |k|\le n, 2\le m\le n$。

显然的这就是对 $b_i = \prod_{j=0}^{m-1}a_{(i+j)\ \bmod\ n}$ 中 $-1$ 的个数进行了限制，以下重新令 $k$ 表示这个个数。于是我们关心对于一个特定的 $b$ 序列，如何判断是否存在 $a$ 序列与其对应，以及对应的 $a$ 序列有多少个。

对于任何一个 $b$，考虑它对应的 $c_i = b_ib_{i+1} = a_ia_{(i+m)\ \bmod\ n}$，显然地，下标划分成了 $g = \gcd(n,m)$ 个不同的小环。这些小环上，$c$ 的数值乘积为 $0$，也就是说相邻两个 $b$ 小环的乘积相等，也就是所有 $b$ 小环的乘积都相等，这也就是说，所有小环上要么都有奇数个 $-1$，要么都有偶数个。所有合法的 $b$ 数组必须满足这条性质。

当确定了一个满足上述条件的 $b$ 数组后，通过它对应的 $c$ 数组，我们确定了每个环上的 $a$ 的相互关系，也就是说，只要确定其中的任何一个元素，就能确定整个环。此时对应的 $a$ 数组恰好有 $2^g$ 个（它们并不都合法）。$b$ 可以由 $c$ 和 $b_0$ 唯一确定，也就是说，当前找到的满足 $c$ 限制的 $a$ 数组，如果同时满足 $b_0$ 的限制，就能唯一对应上我们正在考虑的 $b$ 数组。

对于每个环，只有将其整体反转的操作可以进行。当 $\frac{m}{g}$ 为偶数时，对任何一个环做反转都是没有用的。只有一部分（$2^{n-g}$ 个满足某种性质的）$b$ 是合法的，并且这些 $b$ 恰好对应了 $2^g$ 个合法的 $a$（每个环上 $a$ 都可以任意反转）。而当 $\frac{m}{g}$ 为奇数时，每个满足先前限制的 $b$ （$2^{n-g+1}$ 个）都恰好对应了 $2^{g-1}$ 个合法的 $a$。分别考虑两种情况的答案。

首先考虑 $\frac{m}{g}$ 为奇数。令 $t = \frac{n}{g}$，则答案为：
$$
2^{g-1}[z^k]\left(\left(\sum_{i=0}^{t}[i\equiv 0\pmod 2]\binom{t}{i}z^i\right)^g + \left(\sum_{i=0}^{t}[i\equiv 1\pmod 2]\binom{t}{i}z^i\right)^g\right)
$$
接下来考虑 $\frac{m}{g}$ 为偶数的情况。注意到每个环上 $a$ 中所有元素会被算恰好 $\frac{m}{g}$ 次，所以我们相当于额外限制所有小环上有偶数个 $-1$。所以答案即为：
$$
2^{g}[z^k]\left(\sum_{i=0}^{t}[i\equiv 0\pmod 2]\binom{t}{i}z^i\right)^g
$$
怎么求这个东西呢？注意到设 $\sum_{i=0}^t(-1)^i\binom{t}{i}z^i = (1-z)^t, \sum_{i=0}^t\binom{t}{i}z^i = (1+z)^t$。所以
$$
\begin{aligned}
F = \left(\sum_{i=0}^{t}[i\equiv 0\pmod 2]\binom{t}{i}z^i\right)^g = \frac{1}{2^g}\left((1+z)^t+(1-z)^t\right)^g\\
G = \left(\sum_{i=0}^{t}[i\equiv 1\pmod 2]\binom{t}{i}z^i\right)^g = \frac{1}{2^g}\left((1+z)^t-(1-z)^t\right)^g
\end{aligned}
$$
显然求这两个多项式的点值需要用到长度为 $\Theta(tg = n)$ 级别的 NTT，这个显然不可能过。但是由后面的封闭形式，很容易用快速幂求出单位根处的点值，大大加速求解过程。时间复杂度为 $\Theta(n\log V)$，常数很小。

---

