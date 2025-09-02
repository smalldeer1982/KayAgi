# [NOI Online 2021 提高组] 愤怒的小 N

## 题目描述

极度愤怒的小 N 通关了一款游戏来泄愤。

这款游戏共有 $n$ 关，分别为第 $0$ 关、第 $1$ 关、第 $2$ 关、$\cdots$、第 $n-1$ 关。这些关卡中有一些是普通关卡，另一些则是奖励关卡。

这款游戏中普通关卡与奖励关卡的分布比较特殊。如果用字符 $\texttt{a}$ 表示普通关卡，用字符 $\texttt{b}$ 表示奖励关卡，那么第 $0$ 关、第 $1$ 关、第 $2$ 关、$\cdots$、第 $n-1$ 关依次排列形成的字符串是一个无穷字符串 $s$ 的前缀，且 $s$ 可以按照如下方式构造：

1. 初始时 $s$ 为包含单个字符 $\texttt{a}$ 的字符串。

2. 将 $s$ 的每个字符 $\texttt{a}$ 替换成字符 $\texttt{b}$，每个字符 $\texttt{b}$ 替换成字符 $\texttt{a}$ 得到字符串 $t$，然后将 $t$ 拼接到 $s$ 后。
3. 不断执行2. 得到的字符串就是最终的 $s$。

可以发现 $s=\texttt{abbabaabbaababba}\cdots$，所以这款游戏的第 $0$ 关是普通关卡，第 $1$ 关
是奖励关卡，第 $2$ 关是奖励关卡，第 $3$ 关是普通关卡，以此类推。

通过游戏的第 $i$ 关可以得到 $f(i)$ 分，其中 $f(x)=a_0+a_1x+a_2x^2+\cdots+a_{k-1}x^{k-1}$ 
是一个固定的 $k-1$ 次多项式。

小 N 通关时一气之下通过了所有奖励关卡而忽略了所有普通关卡，然后就把游戏卸载了。现在回想起来，他想要知道他在卸载游戏前的总得分对 $10^9+7$ 取模后的结果。

## 说明/提示

对于所有测试点：$0\le \log_2n<5\times 10^5$，$1\le k\le 500$，$0\le a_i < 10^9 + 7$，$a_{k-1}\ne 0。$

| 测试点编号 | $\log_2n\le$ | $k\le$ |
|:-:|:-:|:-:|
| $1\sim2$ | $10$ |$500$ |
| $3\sim4$ | $20$ | $500$ |
| $5\sim8$ | $100$ | $500$ |
| $9\sim10$ | $500$ | $500$ |
| $11\sim12$ | $5\times 10^5$ | $1$ |
| $13\sim16$ | $5\times 10^5$ | $100$ |
| $17\sim20$ | $5\times 10^5$ | $500$ |

感谢 [s_r_f](https://www.luogu.com.cn/user/52518) 提供数据。

## 样例 #1

### 输入

```
1000
3
3 2 1```

### 输出

```
110
```

## 样例 #2

### 输入

```
11111100101
4
2 0 2 1```

### 输出

```
143901603
```

## 样例 #3

### 输入

```
1001011001101001
16
1 0 0 1 0 1 1 0 0 1 1 0 1 0 0 1```

### 输出

```
184740992
```

# 题解

## 作者：周子衡 (赞：41)

首先分析题目中关于奖励关卡的叙述，容易发现：

**性质 0** 第 $i$ 关是奖励关卡当且仅当 $i$ 的二进制表示包含奇数个 $1$。

可以通过对 $i$ 在二进制下的位数进行归纳证明，此处略去。也就是说，我们要计算的值为

$$
\sum_{0\leq i < n,i\in C_1}f(i)
$$

其中 $C_1$ 是全体二进制表示中有奇数个 $1$ 的自然数的集合。由于有限制 $i < n$，为了去掉这个限制，考虑枚举 $i$ 和 $n$ 在二进制位上首次不一样的地方——这样，更低位的选择便是自由的。不妨设 $n$ 在二进制下有 $s$ 位，且 $n=(n_sn_{s-1}\cdots n_1)_2$（其中 $n_s$ 是最高位）。令 $T_i$ 表示将 $n$ 的后 $i$ 位变成 $0$ 所得的数（即 $T_i=(n_s\cdots n_{i+1}00\cdots 0)_2$。那么答案便是

$$
\sum_{1\leq i\leq s,n_i=1}\sum_{0\leq j<2^{i-1},T_i+j\in C_1}f(T_i+j)
$$

显见这里的 $T_i$ 对每个 $i$ 是固定且容易计算的，且 $T_i+j$ 有奇数个 $1$ 当且仅当 $T_i$ 和 $j$ 在在二进制中有相同奇偶性个数的 $1$。问题的关键在于对多项式的求和。按二项式定理展开：

$$
f(T+j)=\sum_{p=0}^{k-1}a_p\binom{k-1}{p}T^pj^{k-1-p}
$$

$T=T_i$ 是确定的，我们要做的是快速的求出符合条件的 $j$ 的 $0\sim (k-1)$ 次幂和。观察到这里是对所有 $i-1$ 位二进制数中的恰好一半求次幂和，联想到一个广为人知的结论：

**定理 1** 设 $k$ 是正整数，那么

$$
\sum_{0\leq i < 2^k,i\in C_1}i^p=\sum_{0\leq i < 2^k,i\in C_0}i^p
$$

对所有的非负整数 $0\leq p < k$ 成立，其中 $C_0,C_1$ 分别是二进制下 $1$ 个数为偶数、奇数的自然数集合。

（知道这个定理的读者可以跳过证明）

为了证明这个定理，我们先证明如下结论：

**引理 2** 设 $x_1,...,x_k;y_1,...,y_k$ 是实数，$p$ 是自然数，若对任意自然数 $f\leq p$ 都有

$$
\sum_{i=1}^kx_i^f=\sum_{i=1}^ky_i^f
$$

那么对任意的实数 $z$，有

$$
\sum_{i=1}^k(z+x_i)^f=\sum_{i=1}^k(z+y_i)^f
$$

**证明** 左右对减，观察到 $z^i$ 项的系数为 $\binom{p}{p-i}(\sum_{j=1}^kx_j^{p-i}-y_j^{p-i})$，由已知条件显然该式为 $0$。故左式等于右式。

**定理 1 的证明** 考虑归纳法。$k=1$ 时显然。$k>1$ 时，对于任意 $p < k-1$，由归纳假设知

$$
\sum_{0\leq i < 2^{k-1},i\in C_1}i^p=\sum_{0\leq i < 2^{k-1},i\in C_0}i^p
$$

那么由引理可得

$$
\sum_{0\leq i < 2^{k-1},i\in C_1}(2^k+i)^p=\sum_{0\leq i < 2^{k-1},i\in C_0}(2^k+i)^p
$$

对任意 $x\in [2^{k-1},2^k)$，$x$ 的二进制中 $1$ 的个数奇偶性恰和 $x-2^{k-1}$ 的奇偶性相反。因而我们得知

$$
\sum_{0\leq i < 2^k,i\in C_1}i^p=\sum_{0\leq i < 2^{k-1},i\in C_1}i^p+\sum_{0\leq i < 2^{k-1},i\in C_0}(2^k+i)^p
$$

对另一侧也有相同的结论。再由上面的式子就得知：对于 $p < k-1$，上式是成立的。我们关键来讨论 $p=k-1$ 的情况。这里我们特别留心 $i^{k-1}$ 次项的系数（因为除了这一项外前面的次幂和都是相等的）。展开得

$$
\sum_{0\leq i < 2^k,i\in C_1}i^{k-1}=\sum_{0\leq i < 2^{k-1},i\in C_1}i^{k-1}+\sum_{0\leq i < 2^{k-1},i\in C_0}(2^k+i)^{k-1}
$$

$$
=\sum_{0\leq i < 2^{k-1},i\in C_1}i^{k-1}+\sum_{0\leq i < 2^{k-1},i\in C_0}(i^{k-1}+\sum_{j=0}^{k-2}\binom{k-1}{j}i^j2^{k(k-1-j)}
$$

$$
=\sum_{i=0}^{2^{k-1}}i^{k-1}+\sum_{0\leq i < 2^{k-1},i\in C_0}\sum_{j=0}^{k-2}\binom{k-1}{j}i^j2^{k(k-1-j)}
$$

后面那一堆东西是什么并不重要——由于 $i$ 的次幂不超过 $k-2$ 次，因此归纳假设已经保证了左右是相等的。而前面的 $k-1$ 次项神奇地合并了！定理证毕。

-------------------------

回到原题。由上面的定理进一步可以知道：当 $k > p$ 时，

$$
\sum_{0\leq i < 2^{k},i\in C_1}i^p=\sum_{0\leq i < 2^{k},i\in C_0}i^p=\dfrac{1}{2}\sum_{i=0}^{2^k-1}i^p
$$

$$
\sum_{0\leq i < 2^{k},i\in C_1}(T+i)^p=\sum_{0\leq i < 2^{k},i\in C_0}(T+i)^p=\dfrac{1}{2}\sum_{i=0}^{2^k-1}(T+i)^p
$$

那么当 $k-1 < i-1$ 时，要求的

$$
\sum_{0\leq j<2^{i-1},T_i+j\in C_1}f(T_i+j)=\dfrac{1}{2}\sum_{0\leq j<2^{i-1}}f(T_i+j)
$$

令 $S(x)=\sum_{i=0}^{x}f(i)$。显见这是关于 $x$ 的不超过 $k$ 次的多项式且当 $k$ 小于模数时在模意义下有等价性。我们可以用拉格朗日插值的方法，在求出 $S(0),...,S(k)$ 后推出各项系数。这样在预处理系数后便可以 $O(k)$ 代入上式进行计算了！算上枚举 $i$ 的复杂度，这一部分的总时间复杂度为 $O(sk)$。

我们还剩下 $k\geq i$ 的情况没有处理。由于这样的 $i$ 只有 $k$ 个，我们考虑暴力处理出 $G_z(i,p)=\sum_{0\leq j < 2^i,j\in C_z}j^p$。运用二项式定理可以在 $O(k^3)$ 的时间复杂度内完成转移。之后暴力代入计算即可。这一部分总时间复杂度为 $O(k^3)$。综上，我们在 $O(sk+k^3)$ 的时间复杂度内解决了本题。

---

## 作者：ZigZagKmp (赞：24)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14586444.html)。

## 题意简述
数列 $\{b_n\}$ 构造如下：（即 `Thue-Morse` 数列，[OEIS A010060](http://oeis.org/A010060)）
- $b_0=0$
- $\forall i\in [2^n,2^{n+1}),b_i=1-b_{i-2^n}$

输入 $n$ 和一个次数为 $m-1$ 次的多项式 $f(x)=\sum\limits_{i=0}^{m-1}a_ix^i$ ，求 $\sum\limits_{i=0}^{n-1}b_if(i)$ ，答案对 $10^9+7$ 取模。

$0\le \log_2 n\le 5\cdot 10^5\ ,\ 1\le m\le 500\ ,\ 0\le a_i< 10^9+7\ ,\ a_{m-1}\neq 0$ 。

## 算法分析

我们首先尝试找到 $\{b_n\}$ 的通项，方便我们下面的求解。

由构造过程，不难发现，我们在 $x$ 的最高位前添上一个 $1$ （设为 $y$ ），则 $b_{y}=b_{x}\mathrm{xor}1$ ，这个过程中最明显的变化就是二进制中 $1$ 的个数 $+1$ ，因此我们有如下结论：

$$b_{n}=\mathrm{popcount}(n) \pmod 2$$

$\mathrm{popcount}(n)$ 即为 $n$ 的二进制表示下有多少个 $1$ 。

但这个$\pmod 2$  并不好处理，我们转化成乘积，即：

$$b_{n}=\frac{1}{2}\left(1-(-1)^{\mathrm{popcount}(n)}\right)$$

因此答案如下：

$$ans=\frac{1}{2}\sum_{i=0}^{n-1}\left(1-(-1)^{\mathrm{popcount}(i)}\right)f(i)$$

稍作化简：

$$ans=\frac{1}{2}\sum_{i=0}^{n-1}f(i)-\frac{1}{2}\sum_{i=0}^{n-1}(-1)^{\mathrm{popcount}(i)}f(i)$$

由于 $f(x)$ 是一个 $m-1$ 次多项式，因此可以归纳证明 $f(x)$ 的前缀和是一个 $m$ 次多项式，用拉格朗日插值即可求出，时间复杂度 $O(m^2)$ 。

现在我们只看后面一部分，即：

$$\sum_{i=0}^{n-1}(-1)^{\mathrm{popcount}(i)}f(i)$$

把 $f(i)$ 展开，交换求和顺序：

$$\sum_{k=0}^{m-1}a_k\sum_{i=0}^{n-1}(-1)^{\mathrm{popcount}(i)}i^k$$

我们只要能求出 $\sum\limits_{i=0}^{n-1}(-1)^{\mathrm{popcount}(i)}i^k$，即可 $\mathcal{O}(m)$ 计算。

考虑类似于 `数位dp` 的做法，**把 $[0,n)$ 这个区间拆解为若干个形如 $[x,x+2^t)(x>2^t)$ 的区间**，这样我们**所有的区间长度都是 $2$ 的整次幂**，方便我们计算。

举个例子，$n=\left(10101101\right)_2$，我们拆解为如下几个区间：
- $\left[\left(00000000\right)_2,\left(10000000\right)_2\right)$
- $\left[\left(10000000\right)_2,\left(10100000\right)_2\right)$
- $\left[\left(10100000\right)_2,\left(10101000\right)_2\right)$
- $\left[\left(10101000\right)_2,\left(10101100\right)_2\right)$
- $\left[\left(10101100\right)_2,\left(10101101\right)_2\right)$

接下来我们的工作就是要计算 $\sum\limits_{i=x}^{x+2^t-1}(-1)^{\mathrm{popcount}(i)}i^k$，不妨记此为 $f(x,t,k)$，则：

$$f(x,t,k)=\sum_{i=0}^{2^t-1}(-1)^{\mathrm{popcount}(i+x)}(i+x)^k$$

我们划分区间的优势现在就体现出来了，因为 $x>2^t$ ，所以 $\mathrm{lowbit}(x)>\mathrm{highbit}(2^t)$ ，因此 $\mathrm{popcount}$ 我们可以独立计算，即：

$$f(x,t,k)=(-1)^{\mathrm{popcount}(x)}\sum_{i=0}^{2^t-1}(-1)^{\mathrm{popcount}(i)}(i+x)^k$$

后面的 $(i+x)^k$ 用二项式定理展开，即：

$$f(x,t,k)=(-1)^{\mathrm{popcount}(x)}\sum_{i=0}^{2^t-1}(-1)^{\mathrm{popcount}(i)}\sum_{j=0}^k\dbinom{k}{j}i^jx^{k-j}$$

继续交换求和顺序，并独立出 $x$ ，即：

$$f(x,t,k)=(-1)^{\mathrm{popcount}(x)}\sum_{j=0}^k\dbinom{k}{j}x^{k-j}\sum_{i=0}^{2^t-1}(-1)^{\mathrm{popcount}(i)}i^j$$

**子问题出现了**，即：

$$f(x,t,k)=(-1)^{\mathrm{popcount}(x)}\sum_{j=0}^k\dbinom{k}{j}x^{k-j}f(0,t,j)$$

但 $f(0,t,j)$ 并不能由我们上面的式子计算出，考虑 $[0,2^t)=[0,2^{t-1})\cup[2^{t-1},2^t)$，而这种区间的划分仍然满足上面的条件（$x>2^t$），因此：

$$f(0,t,k)=f(0,t-1,k)+f(2^{t-1},t-1,k)$$

综上，我们可以在 $\mathcal{O}(m)$ 的时间复杂度实现 $f(x,t,k)$ 的转移，后面两维状态数是 $\mathcal{O}(m^2)$ 的，总共有 $\mathcal{O}(\log_2 n+m)$个可能的$x$，因此因此总复杂度为 $\mathcal{O}((\log_2n+m)m^2)$ 的，可以通过 $60\%$ 的数据。

~~通过打表~~，发现 $f(x,t,k)$ 在 $x>2^k$ 或者 $t>k$ 时都是 $0$ 。这个也是可以归纳证明的，（但我不会证），此处略去。

因此所有 $>m$ 的 $x$ 都没有用，因此实际上只有 $\mathcal{O}(m)$ 个可能的不同的 $x$ ，复杂度为 $\mathcal{O}(\log_2n+m^3)$ ，可以通过。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define ull unsigned long long
#define db double
#define ldb long double
#define mod 1000000007
#define eps 1e-9
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int ksm(int b,int p=mod-2,int Mod=mod){int ret=1;while(p){if(p&1)ret=1ll*ret*b%Mod;b=1ll*b*b%Mod;p>>=1;}return ret;}

int iv2=((mod+1)/2);
int n,m;
char ss[maxn];
int a[maxn];
struct Larg{//拉格朗日插值求前缀和
	int calc_f(int x){
		int ret=0;
		for(int i=m-1;i>=0;--i){
			ret=(1ll*ret*x+a[i])%mod;
		}
		return ret;
	}
	int frac[505],frinv[505],xi[505],yi[505],syi[505],N;
	int pv[505],sf[505];
	void prepr(){
		N=m+1;
		frac[0]=1;for(int i=1;i<=N;++i)frac[i]=1ll*frac[i-1]*i%mod;
		frinv[N]=ksm(frac[N]);for(int i=N;i;--i)frinv[i-1]=1ll*frinv[i]*i%mod;
		yi[0]=calc_f(0);
		for(int i=1;i<=N;++i){
			xi[i]=i;yi[i]=(yi[i-1]+calc_f(i))%mod;
			int prv=frinv[i-1],suf=frinv[N-i];
			if((i^N)&1)suf=(mod-suf);
			syi[i]=1ll*yi[i]*prv%mod*suf%mod;
		}
	}
	int calc_sf(int x){
		x%=mod;
		pv[0]=sf[N+1]=1;
		for(int i=1;i<=N;++i)pv[i]=1ll*pv[i-1]*(x-xi[i])%mod;
		for(int i=N;i;--i)sf[i]=1ll*sf[i+1]*(x-xi[i])%mod;
		int ret=0;
		for(int i=1;i<=N;++i){
			ret=(ret+1ll*syi[i]*pv[i-1]%mod*sf[i+1]%mod)%mod;
		}
		return (ret+mod)%mod;
	}
}La;

int ans1,ans2;
int C[505][505];
int p2[maxn];
void prep(){
	for(int i=0;i<=m;++i){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;++j){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	p2[0]=1;
	for(int i=1;i<=n;++i)p2[i]=2ll*p2[i-1]%mod;
}
int ff[505][505];

int calc(int tn,int k){//计算 f(0,tn,k)
	if(tn>k)return 0;
	if(tn==0)return k==0;
	if(ff[tn][k]!=-1)return ff[tn][k];
	int ret=calc(tn-1,k);
	int X=p2[tn-1];
	int px=1;
	for(int j=k;j>=0;--j,px=1ll*px*X%mod){
		ret=(ret+mod-1ll*C[k][j]*px%mod*calc(tn-1,j)%mod)%mod;
	}
	return ff[tn][k]=ret;
}

void solve(){
	int tnm=0,tppc=0;
	for(int i=0;i<n;++i){
		int cnm=(2ll*tnm+ss[i]-'0')%mod,cppc=(tppc^(ss[i]-'0'));
		if(n-i-1<=m){//无用的x直接剪枝减掉
			if(ss[i]=='1'){//划分区间
				int X=1ll*tnm*p2[n-i]%mod;
				for(int k=0;k<m;++k){
					int sm=0;
					int px=1;
					for(int j=k;j>=0;--j,px=1ll*px*X%mod){
						sm=(sm+1ll*C[k][j]*px%mod*calc(n-i-1,j)%mod)%mod;
					}
					if(tppc)sm=(mod-sm);
					ans2=(ans2+1ll*a[k]*sm%mod)%mod;
				}
			}	
		}
		
		tnm=cnm,tppc=cppc;
	}
}

signed main(){
	#ifndef local
		file("angry");
	#endif
	memset(ff,-1,sizeof(ff));
	scanf("%s",ss);n=strlen(ss);
	read(m);
	for(int i=0;i<m;++i)read(a[i]);
	La.prepr();prep();
	int nm=0;
	for(int i=0;i<n;++i)nm=(2ll*nm+ss[i]-'0')%mod;
	nm=(nm+mod-1)%mod;
	ans1=La.calc_sf(nm);
	solve();
	int ans=(ans1+mod-ans2)%mod;
	ans=1ll*ans*iv2%mod;
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：feecle6418 (赞：18)

考场上这题做了 2h，直接没时间写 T3 了，，，，，，，，

先考虑一个 $O(nk^2)$ 的无脑 dp：设 $f_{i,j,0/1}$ 表示 $0\sim 2^i-1$ 编号的位置中，所有 a/b 位置的编号的 $j$ 次方和。

则有

$$f_{i,j,k}=f_{i-1,j,k}+\sum_{l\le j} \binom jl f_{i-1,l,1-k}2^{(i-1)(j-l)}$$

直接转移，复杂度 $O(nk^2)$。

算答案时分成 $O(n)$ 个小段，每段形如

![](https://cdn.luogu.com.cn/upload/image_hosting/risfjbq4.png)

也就是把 $n$ 的二进制里面的每一个 `1` 按照次数从大到小排列，对每个 `1` 管辖的一段算答案。这一部分也可以直接二项式定理拆开，利用之前算的 $f$ 做到 $O(nk^2)$。

> **定理** 若 $i>j$ 则 $f_{i,j,0}=f_{i,j,1}=\dfrac{\sum_{k=0}^{2^i-1}k^j}{2}$。

对 $i$ 归纳可证，这里略去，考场上可以用找规律等各种方式得到。

由此，对于之前算答案时拆分出来的，长度大于 $2^k$ 的段，都可以插值算。（注意到整个多项式的前缀和也是多项式，可以一起插值，然后每段不用分别插，也可以直接插整个前缀）插值只有 $O(k)\sim O(k^2)$ 的复杂度。

然后对小于等于 $2^k$ 的段暴力 dp 然后算，这部分复杂度 $O(k^3)$。

总复杂度 $O(n+k^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int n,K,a[505],f[505][505][2],C[505][505]={1},pw[505]={1},ans=0;
char s[500005];
int Power(int x,int y){
	int r=1;
	while(y){
		if(y&1)r=1ll*r*x%mod;
		y>>=1,x=1ll*x*x%mod;
	}
	return r;
}
int Interpolation(int n,int K,vector<int> x,vector<int> y){
	int ans=0;
	for(int i=0;i<n;i++){
		int fz=y[i],fm=1;
		for(int j=0;j<n;j++){
			if(i==j)continue;
			fz=1ll*fz*((K-x[j]+mod)%mod)%mod,fm=1ll*fm*((x[i]-x[j]+mod)%mod)%mod;
		}
		ans=(ans+1ll*fz*Power(fm,mod-2)%mod)%mod;
	}
	return ans;
}
int main(){
	scanf("%s%d",s,&K),n=strlen(s);
	for(int i=0;i<K;i++)scanf("%d",&a[i]);
	vector<int> x,y;
	for(int i=0,ts=0;i<=505;i++){
		x.push_back(i),y.push_back(ts);
		int sum=0;
		for(int j=K-1;j>=0;j--)sum=(1ll*sum*i+a[j])%mod;
		ts=(ts+sum)%mod;
	}
	for(int i=1;i<=K;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	f[0][0][0]=1;
	for(int i=1,t=1;i<=K;i++,t=2*t%mod){
		for(int j=1;j<K;j++)pw[j]=1ll*pw[j-1]*t%mod;
		for(int j=0;j<K;j++){
			unsigned long long w0=0,w1=0;
			for(int k=0;k<=j;k++){
				int t=1ll*pw[j-k]*C[j][k]%mod;
				w1+=1ll*f[i-1][k][0]*t;
				w0+=1ll*f[i-1][k][1]*t;
				if((k&15)==0)w0%=mod,w1%=mod;
			}
			f[i][j][0]=(f[i-1][j][0]+w0)%mod,f[i][j][1]=(f[i-1][j][1]+w1)%mod;
		}
	}
	for(int i=n-1,ss=0,cur=0;i>=0;i--){
		if(s[n-i-1]!='1')continue;
		if(i>K){
			ss=(ss+Power(2,i))%mod,cur^=1;
			continue;
		}
		for(int j=1;j<K;j++)pw[j]=1ll*pw[j-1]*ss%mod;
		for(int j=0;j<K;j++){
			unsigned long long sum=0;
			for(int k=0;k<=j;k++){
				sum+=1ll*f[i][k][cur^1]*C[j][k]%mod*pw[j-k];
				if((k&15)==0)sum%=mod;
			}
			ans=(ans+1ll*sum%mod*a[j])%mod;
		}
		ss=(ss+Power(2,i))%mod,cur^=1;
	}
	//还剩下K+1~n-1的贡献，这部分直接插值求f(k)前缀和 
	int ss=0;
	for(int i=n-1;i>K;i--)if(s[n-i-1]=='1')ss=(ss+Power(2,i))%mod;
	cout<<(ans+1ll*(mod+1)/2*Interpolation(x.size(),ss,x,y))%mod;
}
```

---

## 作者：dengyaotriangle (赞：17)

官方题解对结论的证明不直观，来看看怎么拿生成函数直观证明！

首先考虑如何表示一个集合 $S$ 里面所有数的 $0\sim k$ 次方和。

考虑 $F_S(x)=\sum\limits_{u\in S}\mathrm{e}^{ux}$，我们发现 $k![x^k]F_S(x)$ 即为 $k$ 次方和。

原因就是 $k![x^k]F_S(x)=k![x^k]\sum\limits_{n\geq 0}\sum\limits_{u\in S}\frac{(ux)^n}{n!}=\sum\limits_{u\in S} u^k$

（至于为什么是 EGF 而不是 OGF，你会发现写成 OGF 的话，下面的转移无法表示）

考虑令 $P_n(x)$ 代表长度为 $2^n$ 的串中 a 构成的集合的 $F_S(x)$，$Q_n(x)$ 为长度为 $n$ 的串中 b 构成的集合的 $F_S(x)$

试图找到 $P_n(x),Q_n(x)$ 到 $P_{n+1}(x),Q_{n+1}(x)$ 的递推方式。考虑枚举长度 $2^{n+1}$ 的串的每个元素的最低位：

由于二进制中有偶数个 1 的是 a，奇数个 1 的是b，所以：

- 若第 $i$ 个数是偶数，而 $i/2$ 是 a，那么 $i$ 是 a，否则 $i$ 是 b。  
- 若第 $i$ 个数是奇数，而 $(i-1)/2$ 是 a，那么 $i$ 是 b，否则 $i$ 是 a。

所以我们只需要处理一个集合同时 $\times 2$ 和 $+c$ 之后 $F_S(x)$ 的变化，易得

$$F_{2S}(x)=\sum\limits_{u\in S}\mathrm{e}^{2ux}=F_S(2x)$$
$$F_{S+c}(x)=\sum\limits_{u\in S}\mathrm{e}^{(u+c)x}=F_S(x)\mathrm{e}^{cx}$$

所以递推方程可以写成：

$$P_{n+1}(x)=P_n(2x)+Q_n(2x)\mathrm{e}^x$$
$$Q_{n+1}(x)=Q_n(2x)+P_n(2x)\mathrm{e}^x$$

我们发现 $P_n(x)+Q_n(x)$ 是好求的，就是自然数幂和的生成函数。那么我们试图求 $P_n(x)-Q_n(x)$。

将递推式相减，得

$$P_{n+1}(x)-Q_{n+1}(x)=(P_n(2x)-Q_n(2x))(1-\mathrm{e}^x)$$

发现我们只关心 $P,Q$ 的前 $k$ 项，$x\mid (1-\mathrm{e}^x)$，而生成函数被 $2x$ 复合并不改变其中 $x^i$ 因子，所以每次就会多出一个 $x$ 因子，所以我们知道 $P_{k+1}(x)-Q_{k+1}(x)\equiv 0 \pmod{x^{k+1}}$

这说明（$\bmod\ x^{k+1}$ 意义下，下同），对于 $n>k,P_{n}(x)=Q_{n}(x)$，所以我们其实只需要求前 $k$ 个 $P,Q$ 就够了。

而若求长度不是 $2^n$ 的答案，考虑形如数位 dp 的东西。每次确定了高位，求低 $w$ 位任意取的和。不妨设高位里有偶数个1，那么整个数的奇偶性和去掉高位的数的奇偶性相同，所以设确定的高位部分是 $c$，那么答案就是 $Q_{w}(x)\mathrm{e}^{cx}$，我们总的答案就是所有区间的 $Q_{w}(x)\mathrm{e}^{cx}$ 之和。


那么对于计算过程，对于 $w\leq k$，使用暴力计算得的 $P,Q$ 暴力卷积，复杂度 $O(k^3)$ ，如果使用 任意模数ntt 可以做到 $O(k^2\log k)$。

回顾自然数幂和生成函数，
$$P_n(x)+Q_n(x)=\sum_{i=0}^{2^n-1}\sum_{j\geq 0}\frac{(xi)^j}{j!}=\sum_{i=0}^{2^n-1}\mathrm{e}^{xi}=\frac{\mathrm{e}^{2^nx}-1}{\mathrm{e}^{x}-1}$$

对于 $w>k$， $P_w(x)=Q_w(x)=\frac{\mathrm{e}^{2^nx}-1}{2(\mathrm{e}^{x}-1)}$，那么考虑其与 $\mathrm{e}^{cx}$ 卷积后，展开得

$$\frac12\sum_{i=c}^{2^w+c-1}\mathrm{e}^{ix}$$

所有 $w>k$ 考虑到的区间其实是一个前缀，那么它们答案的总和就是


$$\frac12\sum_{i=0}^{R-1}\mathrm{e}^{ix}=\frac{\mathrm{e}^{Rx}-1}{2(\mathrm{e}^{x}-1)}$$

其中 $R$ 为最右边的一个 $w>k$ 的项的右端点。

可以使用 $O(k^2)$ 的多项式求逆一发得到。

所以总复杂度 $O(\log n+k^3)$ （或 $O(\log n+k^2\log k)$ ）

```cpp
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxn=500005;
const int maxk=505;
const int mdn=1000000007;
const int inv2=(mdn+1)/2;

inline int qpw(int bse,int ex){int ans=1;while(ex){if(ex&1)ans=ans*(long long)bse%mdn;ex>>=1;bse=bse*(long long)bse%mdn;}return ans;}

char s[maxn];
int a[maxk];
int n;
int p[maxk][2][maxk];
int ifac[maxk],fac[maxk];
int pw2[maxk];
int cp[maxk];
int i0[maxk],iv[maxk];
int main(){
    fac[0]=1;for(int i=1;i<maxk;i++)fac[i]=fac[i-1]*(long long)i%mdn;
    ifac[maxk-1]=qpw(fac[maxk-1],mdn-2);
    for(int i=maxk-1;i>0;i--)ifac[i-1]=ifac[i]*(long long)i%mdn;
    pw2[0]=1;for(int i=1;i<maxk;i++)pw2[i]=pw2[i-1]*2%mdn;
    cin>>s>>n;
    for(int i=0;i<=n;i++)cin>>a[i];
    p[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int t=0;t<2;t++){
            for(int j=0;j<=n;j++){
                p[i][t][j]=p[i-1][t][j]*(long long)pw2[j]%mdn;
                for(int k=0;k<=j;k++){
                    p[i][t][j]=(p[i][t][j]+p[i-1][!t][k]*(long long)pw2[k]%mdn*ifac[j-k])%mdn;
                }
            }
        }
    }
    int sz=strlen(s);
    int r=0,cur=0;bool ct=1;
    int ans=0;
    for(int i=0;i<sz;i++){
        cur=cur*2%mdn;
        r=r*2%mdn;
        if(s[i]=='1'){
            int rc=(cur+1)%mdn;
            int w=sz-i-1;
            if(w<=n){
                int l=cur*(long long)pw2[w]%mdn;
                cp[0]=1;for(int i=1;i<=n;i++)cp[i]=cp[i-1]*(long long)l%mdn;
                for(int j=0;j<=n;j++){
                    int cur=0;
                    for(int k=0;k<=j;k++){
                        cur=(cur+p[w][ct][k]*(long long)ifac[j-k]%mdn*cp[j-k])%mdn;
                    }
                    ans=(ans+a[j]*(long long)fac[j]%mdn*cur)%mdn;
                }
            }else{
                r=rc;
            }
            cur=rc;
            ct^=1;
        }
    }
    for(int i=0;i<=n;i++)i0[i]=ifac[i+1];
    iv[0]=i0[0];
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++)iv[i]=(iv[i]+iv[j]*(long long)i0[i-j])%mdn;
        iv[i]=(mdn-iv[i])%mdn;
    }
    cp[0]=1;for(int i=1;i<=n;i++)cp[i]=cp[i-1]*(long long)r%mdn;
    for(int i=0;i<=n;i++){
        int cur=0;
        for(int j=0;j<=i;j++){
            cur=(cur+iv[j]*(long long)ifac[i-j+1]%mdn*cp[i-j+1])%mdn;
        }
        ans=(ans+a[i]*(long long)fac[i]%mdn*cur%mdn*inv2)%mdn;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：云浅知处 (赞：17)

orz

场上推了一半不会了qwq，还是太菜啦/dk

由于云浅太菜了，所以写的可能会通俗一点qwq（

------------

### Description

有一个可爱的数列 $\{A_n\}$，满足：   

> $A_0=0$               
> $A_{n}=1-A_{n-2^{m}}$，其中 $m$ 是使得 $2^{m}\le n$ 的最大的正整数。

再给你一个可爱的 $k-1$ 次多项式 $f(x)=\sum_{i=0}^{k-1}a_ix^{i}$。

给定 $n$，求 $\sum_{i=0}^{n-1}A_i\cdot f(i)$。

------------

### Solution

第一步肯定要处理 $\{A_n\}$ ，毕竟这个数列太神奇了，不搞一下都没法做>\_<

首先看一下数列 $\{A_n\}$ 到底是什么东西。

仔细观察这个递推式：$A_{n}=1-A_{n-2^{m}}$。

我们发现，如果把 $n$ 的二进制表达写出来，那么减去这个 $2^m$ ，就相当于**把 $n$ 最高位上的那个 $1$ 去掉！**

毕竟，$2^{m}$ 在二进制下总是一个 $1$ 后面跟一长串 $0$，而且这还是使得 $2^{m}\le n$ 的最大的正整数嘛，那就只能是最高位和 $n$ 一样都是 $1$，然后后面全是 $0$ qwq。

于是 $A_{n-2^{m}}$ 到 $A_n$ 就相当于在前头加了个 $1$，那就相当于把 $A_n$ 的二进制表达中奇偶性翻转。

再结合 $A_0=0$，就有：

$$
A_n=\text{Popcount}(n)\bmod2
$$

其中 $\text{Popcount}(n)$ 表示 $n$ 的二进制表达中的 $1$ 个数。方便起见，下面统一简记为 $\text{P}(n)$。

但是这个 $\bmod 2$ 让我们很难受啊>\_<

用一个常见的技巧，把 $\bmod 2$ 搞掉：

$$

A_n=\text{P}(n)\bmod2=\dfrac{1-(-1)^{\text{P}(n)}}{2}
$$

于是那我们就成功搞掉了 $A_n$，把它变得更可爱啦（๑ \`▽´๑)

------------

回到要求出来的这个式子。

把我们之前推出来的 $A_n$ 带进去化简一通：

$$
\begin{aligned}
\sum_{i=0}^{n-1}A_i\cdot f(i)&=\sum_{i=0}^{n-1}\left(\dfrac{1-(-1)^{\text{P}(i)}}{2}\cdot f(i)\right)\\
&=\dfrac{1}{2}\left(\sum_{i=0}^{n-1}\left(f(i)-(-1)^{\text{P}(i)}\cdot f(i)\right)\right)\\
&=\dfrac{1}{2}\left(\sum_{i=0}^{n-1}f(i)-\sum_{i=0}^{n-1}(-1)^{\text{P}(i)}\cdot f(i)\right)
\end{aligned}
$$

诶，前面就是一个 $f(x)$ 的前缀和嘛！

那就可以直接拉格朗日插值，$O(k^2)$ 求出前缀和的表达式，然后带进去算出这部分qwq。

现在主要看后面这部分：

$$
\sum_{i=0}^{n-1}(-1)^{\text{P}(i)}\cdot f(i)
$$

貌似这种形式没法继续推。把 $f(i)$ 展开试试：

$$
\sum_{i=0}^{n-1}(-1)^{\text{P}(i)} \sum_{r=0}^{k-1}a_{r}i^{r}
$$

交换一下求和顺序（其实就是提取公因式）：

$$
\sum_{r=0}^{k-1}a_r\sum_{i=0}^{n-1}(-1)^{\text{P}(i)}i^{r}
$$

诶，前面的这个系数 $a_r$ 是很好算的嘛qwq！

那我们现在要求的就是：

$$
\sum_{i=0}^{n-1}(-1)^{\text{P}(i)}i^{r}
$$

然后，我当时就推到这里，推不下去啦>\_<

------------

现在我们写出 $n$ 的二进制表示，是一长串 $1$ 和 $0$。

然后我们从后往前，一个一个地把 $n$ 二进制表示中的 $1$ 去掉，去掉之后的数和去掉之前的数构成了一个区间。

这样就把 $[0,n)$ 划分成了很多个区间，并且每个区间的长度都是 $2$ 的正整数次幂。

比如随便写一个 $n=114=(1110010)_2$，那么就把 $[0,n)$ 划分成了：

- $[(1110000)_2,(1110010)_2)$，即 $[112,114)$
- $[(1100000)_2,(1110000)_2)$，即 $[96,112)$
- $[(1000000)_2,(1100000)_2)$，即 $[64,96)$
- $[0,(1000000)_2)$，即 $[0,64)$

当然你也可以拿 $514=(1000000010)_2$ 验证一下qwq。

（其实就是 $114=2^6+2^5+2^4+2$，$514=2^9+2$ 嘛qwq）

那么我们考虑一段长度为 $2^t$ 的区间 $[u,u+2^t)$ 中的和：

$$
\sum_{i=u}^{u+2^t-1}(-1)^{\text{P}(i)}i^{r}
$$

把求和换成从 $0$ 开始：

$$
\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i+u)}(i+u)^{r}
$$

显而易见的一点是，要么 $u=0$，要么 $u$ 的最低位上的 $1$ 要比 $2^t$ 的最高位上的 $1$ 靠前，即 $\text{lowbit}(u)>\text{highbit}(2^t)$。

毕竟，我们每一次区间的转换其实就相当于在 $u$ 的后面的一堆 $0$ 上选一位变成 $1$ 嘛qwq。

比如前面的例子 $n=114=(1110010)_2$，这里的 $u$ 和 $t$ 就依次是：

$$\begin{aligned}u&&0000000 &&1000000&&1100000&&1110000&&1110010\\2^t&&1000000&&100000&&10000&&10&&/\end{aligned}$$

既然 $u$ 的最低位上的 $1$ 都比 $2^t$ 的最高位上的 $1$ 靠前，那它肯定比 $i$ 的最高位上的 $1$ 靠前。也就是说，$u+i$ 的二进制表示中，*不会发生进位！*

那么 $u+i$ 的二进制表示中的 $1$ 的个数就是 $u$ 和 $i$ 各自的二进制表示中 $1$ 的个数之和，即：$\text{P}(u+i)=\text{P}(u)+\text{P}(i)$。

那么就可以提出来一个 $(-1)^{\text{P}(u)}$，把式子变成：

$$
(-1)^{\text{P}(u)}\cdot\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i)}(i+u)^{r}
$$

再用二项式定理展开 $(i+u)^r$，得到：

$$
(-1)^{\text{P}(u)}\cdot\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i)}\sum_{j=0}^{r}C_{r}^ju^{r-j}i^{j}
$$

再交换求和顺序：

$$
(-1)^{\text{P}(u)}\cdot\sum_{j=0}^{r}C_r^ju^{r-j}\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i)}i^j
$$

仔细观察这个式子的后半部分qwq！

$$
\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i)}i^j
$$

嘛......这个东西，好像在前面见过？

------------

如果我们记

$$
\text{Sum}(u,t,r)=\sum_{i=u}^{u+2^t-1}(-1)^{\text{P}(i)}i^{r}=\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i+u)}(i+u)^{r}
$$

诶，刚才那个式子的后半部分

$$
\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i)}i^j
$$

不就是 $\text{Sum}(0,t,j)$ 嘛qwq！

也就是说，如果我们知道了对于所有 $0\le j\le r$ 的 $\text{Sum}(0,t,j)$ 的值，那么就可以在 $O(r)$ 的时间内算出 $\text{Sum}(u,t,r)$。

至于 $\text{Sum}(0,t,j)$ 的值，那直接变形一下：

$$
\begin{aligned}
\text{Sum}(0,t,j)&=\sum_{i=0}^{2^t-1}(-1)^{\text{P}(i)}i^j\\
&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}i^j+\sum_{i=2^{t-1}}^{2^t-1}(-1)^{\text{P}(i)}i^j\\
&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}i^j+\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i+2^{t-1})}(i+2^{t-1})^j\\
&=\text{Sum}(0,t-1,j)+\text{Sum}(2^{t-1},t-1,j)\\
\end{aligned}
$$

那么我们发现，类似于动态规划，可以用 $\text{Sum}(0,t-1,j)$ 和 $\text{Sum}(2^{t-1},t-1,j)$ 来推出 $\text{Sum}(0,t,j)$。

直接硬算的话，由于总共有 $O(k+\log_2n)$ 个不同的 $x$，而两重的递推又是 $O(k^2)$ 的，所以总复杂度为 $O(k^3+k^2\log_2n)$，可以获得 $60pts$。

------------

回到刚才的那个式子，另一方面，它也可以变成：

$$
\begin{aligned}
&\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}i^j+\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i+2^{t-1})}(i+2^{t-1})^j\\
=&\text{Sum}(0,t-1,j)+(-1)^{\text{P}(2^{t-1})}\cdot \sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}(i+2^{t-1})^j\\
=&\text{Sum}(0,t-1,j)-\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}(i+2^{t-1})^j\\
\end{aligned}
$$

推到这里之后发现有一个和之前形式几乎一模一样的：

$$
\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}(i+2^{t-1})^j
$$

类似之前的操作，用二项式定理展开并交换求和顺序，就得到：

$$
\begin{aligned}
\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}(i+2^{t-1})^j&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}\sum_{s=0}^{j}C_{j}^s\left(2^{t-1}\right)^{j-s}i^{s}\\
&=\sum_{s=0}^{j}C_j^s\left(2^{t-1}\right)^{j-s}\sum_{i=0}^{2^{t-1}-1}(-1)^{\text{P}(i)}i^s\\
&=\sum_{s=0}^jC_j^s\left(2^{t-1}\right)^{j-s}\text{Sum}(0,t-1,s)
\end{aligned}
$$

于是就得到另一个递推式：

$$
\text{Sum}(0,t,j)=\text{Sum}(0,t-1,j)-\sum_{s=0}^jC_j^s\left(2^{t-1}\right)^{j-s}\text{Sum}(0,t-1,s)
$$

利用这个递推式，可以发现一个结论：若 $2^{t}>2^j$ 即 $t>j$ 时，总有：

$$
\text{Sum}(0,t,j)=0
$$

$t=0$ 时显然成立。

若 $t=x$ 时，对于 $j<t$，均有 $
\text{Sum}(0,x,j)=0$。

则当 $t=x+1$ 时，对于任意的 $j<x+1$ 即 $j\le x$：

若 $j<x$，则由归纳：

$$
\text{Sum}(0,x,j)=0
$$
$$
\sum_{s=0}^jC_j^s\left(2^{x}\right)^{j-s}\text{Sum}(0,x,s)=0
$$

那么

$$
\text{Sum}(0,x+1,j)=\text{Sum}(0,x,j)-\sum_{s=0}^jC_j^s\left(2^{x}\right)^{j-s}\text{Sum}(0,x,s)=0
$$

若 $j=x$，则：

$$
\begin{aligned}
\text{Sum}(0,x+1,j)&=\text{Sum}(0,x,j)-\sum_{s=0}^jC_j^s\left(2^{x}\right)^{j-s}\text{Sum}(0,x,s)\\
&=\text{Sum}(0,x,j)-\text{Sum}(0,x,j)=0
\end{aligned}
$$

于是命题对 $t=x+1$ 仍然成立。

因此，若 $t>j$，则 $\text{Sum}(0,t,j)=0$。

类似地，我们也可以证明：对于 $\text{Sum}(x,t,j)$，若 $x>2^j$，则同样也有 $\text{Sum}(x,t,j)=0$。

------------

由上面两个结论，可以发现：实际上真正「有用」的 $x$ 只有 $O(k)$ 个。毕竟，如果 $x$ 太大了，那这个小可爱就是 $0$ 嘛QAQ。

那我们就可以在 $O(k^3)$ 的时间内计算后面的东西，再加上前面的东西，总复杂度 $O(\log_2n+k^3)$。足以通过本题。

---

## 作者：CraZYali (赞：15)

~~考场被自己演了。~~

提供一个偏多项式一点的做法。

# 首先考虑一个暴力

对于一个长度为 $2^i$ 的串，我们记 $A_i(x),B_i(x)$ 分别表示这个串下标从 $x$ 开始（整个串左边已经有 $x$ 个字符），这个串中 $a$ 和 $b$ 的位置的 $f(i)$ 之和。显然有 $A_0(x)=f(x),B_0(x)=0$ 。

那么有转移：
$$
\begin{aligned}
A_i(x)&=A_{i-1}(x)+B_{i-1}(x+2^{i-1})\\
B_i(x)&=B_{i-1}(x)+A_{i-1}(x+2^{i-1})
\end{aligned}
$$
暴力计算出所有 $A,B$ 的复杂度为：$O(nk^2)$ 。

从高位到低位模拟“填写”出原串来计算答案的复杂度为： $O(nk)$ 。

# 优化

观察到转移式的形式很像，考虑上下相减：
$$
\begin{aligned}
D_i(x)&=A_i(x)-B_i(x)\\
&=\left(A_{i-1}(x)+B_{i-1}(x+2^{i-1})\right)-\left(B_{i-1}(x)+A_{i-1}(x+2^{i-1})\right)\\
&=(A_{i-1}-B_{i-1})(x)-(A_{i-1}-B_{i-1})(x+2^{i-1})\\
&=D_{i-1}(x)-D_{i-1}(x+2^{i-1})
\end{aligned}
$$
注意到这样每次最高次项都会被消成 $0$ ，所以当 $i$ 充分大的时候 $D_i(x)$ 就会被消成 $0$ 。

那么暴力计算出所有非 $0$ 的 $D_i(x)$ 的复杂度为 $O(k^3)$ 。

接下来考虑暴力，我们实际上是要对所有的`1`位 $j$ 求 $A_i(j)$ 或者 $B_i(j)$ 并求和。

又有：
$$
\begin{aligned}
A_i(x)+B_i(x)&=\sum_{j=0}^{2^i-1}f(x+j)\\
A_i(x)&=\frac{A_i(x)+B_i(x)+D_i(x)}2\\
B_i(x)&=\frac{A_i(x)+B_i(x)-D_i(x)}2
\end{aligned}
$$
$D_i(j)$ 的部分可以暴力计算，所以其实是要算 $f(x)$ 的若干段连续的点值。

而这若干段连续的点值本身也是连续的。所以最后要算就是 $\sum_{i=0}^{N-1}f(x+i)$ 。

把 $\sum_i f(x+i)$ 展开，会变成一个自然数幂和的形式，拉格朗日插值即可。

总复杂度为 $O(k^3+n)$ 。

顺便放上（修改后的）考场代码：

```cpp
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cassert>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10, maxk = 500 + 15, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;

i64 power_pow(i64 base, i64 b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int n;
char N[maxn];
int k;

#define poly vector <int>
inline int deg(const poly &f) {return (int)f.size() - 1;}
poly operator + (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, deg(g)) f[i] = (f[i] + g[i]) % MOD;
	return f;
}
inline void output(const poly &f)
{
	REP(i, 0, deg(f)) printf("%d%c", f[i], i == end_i ? '\n' : ' ' );
}
int fac[maxk], invs[maxk], Invs[maxk];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}
poly shift(poly f, int a) // return f(x + a)
{
	int n = deg(f);
	static int bin[maxk];
	bin[0] = 1;REP(i, 1, n) bin[i] = 1ll * bin[i - 1] * a % MOD * invs[i] % MOD;

	REP(i, 0, n) f[i] = 1ll * f[i] * fac[i] % MOD;
	poly g(n + 1, 0);
	REP(j, 0, n)
	{
		i64 res = 0;
		REP(i, j, n)
			(res += 1ll * f[i] * bin[i - j]) %= MOD;
		g[j] = res * Invs[j] % MOD;
	}
	return g;
}
poly operator - (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, deg(g)) f[i] = (f[i] + MOD - g[i]) % MOD;
	while (f.size() && !f.back()) f.pop_back();
	return f;
}

inline i64 calc(poly f, i64 x) // return f(x)
{
	i64 res = 0;
	DEP(i, deg(f), 0) res = (res * x + f[i]) % MOD;
	return res;
}

poly fk;
poly d[maxn];
int bin2[maxn];

namespace ziranshumi
{
	int k;
	int y0[maxk], st[maxk];
	void init(int K)
	{
		k = K;
		REP(i, 0, k + 1)
		{
			i64 res = 0, ij = 1;
			REP(j, 0, k)
			{
				(res += ij * fk[j]) %= MOD;
				(ij *= i) %= MOD;
			}
			y0[i] = (res + (i ? y0[i - 1] : 0)) % MOD;
		}
		REP(i, 0, k + 1) st[i] = 1ll * Invs[i] * Invs[k + 1 - i] % MOD * y0[i] % MOD;
	}
	int bs[maxk], iv[maxk];
	inline i64 query(i64 n)
	{
		if (n <= k + 1) return y0[n];
		//return Sum[ i ^ k , {i, 0, n} ]
		//0 ^ 0 = 1
		i64 ans = 0;

		bs[0] = n;REP(i, 1, k + 1) bs[i] = bs[i - 1] * (n - i) % MOD;
		i64 W = bs[k + 1];
		iv[k + 1] = inv(bs[k + 1]);
		DEP(i, k, 0) iv[i] = (n - (i + 1)) * iv[i + 1] % MOD;

		DEP(i, k + 1, 0) iv[i] = 1ll * iv[i] * (i ? bs[i - 1] : 1ll) % MOD;

		REP(i, 0, k + 1)
		{
			i64 res = 1ll * iv[i] * st[i];
			//	REP(j, 1, i) res = res * invs[j] % MOD;
			//	REP(j, 1, k + 1 - i) res = res * invs[j] % MOD;

			if ((k - i + 1) & 1) res = -res;
			ans += res;ans %= MOD;
		}

		//		ans = 0;
		//		REP(i, 0, n) ans += power_pow(i, k);
		return ans % MOD * W % MOD;
	}
}

int main()
{
#ifdef CraZYali
	freopen("angry.in", "r", stdin);
	freopen("angry.out", "w", stdout);
#endif
	scanf("%s\n", N); n = strlen(N);
	scanf("%d", &k);init(k + 5);k--;
	fk.resize(k + 1);
	REP(i, 0, k) scanf("%d", &fk[i]);

	bin2[0] = 1;REP(i, 1, n) bin2[i] = bin2[i - 1] * 2 % MOD;
	reverse(N, N + n);

	d[0] = fk;
	REP(i, 1, n - 1)
		d[i] = d[i - 1] - shift(d[i - 1], bin2[i - 1]);
	//d[i] = fa[i] - fb[i]

	int flg = 0, ard = 0;i64 ans = 0;
	ard = 0;int lstr = -1;
	DEP(i, n - 1, 0) if (N[i] == '1')
	{
		lstr = ard + bin2[i] - 1;

		//		REP(j, 0, (1 << i) - 1) tot += calc(fk, j + ard);
		//		tot %= MOD;
		ans += ((flg & 1) ? 1 : -1) * calc(d[i], ard) ;

		(ard += bin2[i]) %= MOD;
		flg ^= 1;
	}

	if (lstr != -1)
	{
		ziranshumi :: init(k);
		ans += ziranshumi :: query(lstr);
	}

	cout << (ans % MOD + MOD) % MOD * inv2 % MOD << endl;
	return 0;
}
```





---

## 作者：hsfzLZH1 (赞：9)

另一种推式子方法。

### 题目大意

给定 $n$ 和 $k-1$ 次多项式 $F(x)=\sum_{i=0}^{k-1}a_ix^i$ ，求 $\sum_{i=0}^{n-1} F(i)[popcnt(i)~mod~2=1]$ 的值，答案取模 $10^9+7$。

$n\le 2^{500000},1\le k\le 500,0\le a_i<10^9+7$

### 解题思路

令 $m=n-1$ 。

令 $p_i=(-1)^{popcnt(i)}$ ，则 $Ans=\dfrac 1 2(\sum_{i=0}^m F(i)+\sum_{i=0}^m p_iF(i))$ 。

左侧式子可以拉格朗日插值或斯特林数 $O(k^2)$ 解决。考虑如何计算右侧式子。

考虑将 $2i$ 和 $2i+1$ 进行配对。这两个数二进制中 $1$ 的个数的奇偶性相反，即 $p_{2i}=-p_{2i+1}$ ，且 $p_{i}=p_{2i}$ 。那么有

$\sum_{i=0}^m p_iF(i)=\sum_{i=0}^{\frac m 2} p_i(F(2i)-F(2i+1))-p_{m+1}F(m+1)[m\text{为偶数}]$

发现一个奇妙的性质， $F_1(x)=F(2x)-F(2x+1)$ 的次数正好是 $k-2$ ！将 $F_1(x)$ 作为新的 $F(x)$ ，就可以带入式子继续递归下去，而不超过 $k$ 次，这个多项式就会变成 $0$ 。

根据二项式定理展开，我们可以预处理 $2$ 的次幂，阶乘和阶乘逆元，在 $O(k^3)$ 的时间复杂度内算出所有这些多项式。而每次 $m$ 也就是 $n-1$ 舍弃最末若干位的值，在 $m$ 为偶数时，将一个值代入多项式计算并累加进答案即可。

需要特别注意， $\log_2 n\le k$ 时，需要在前面补 $0$ 至 $k$ 位，不然会出现问题。

时间复杂度 $O(n+k^3)$ 。可以用多项式科技优化新的多项式的计算，使时间复杂度达到 $O(n+k^2\log n)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=500010;
const int mod=1000000007;
#define int long long
char n[maxn];
int ksm(int a,int k)
{
	int x=a,ret=1;
	while(k)
	{
		if(k&1)ret=ret*x%mod;
		x=x*x%mod;k>>=1;
	}
	return ret;
}
int l,k,a[maxn],b[maxn],pww[maxn],frac[maxn],invf[maxn],val[maxn],pre[maxn],x[maxn],y[maxn],ans;
int F(int x){int ret=0,nww=1;for(int i=0;i<k;i++)ret=(ret+a[i]*nww)%mod,nww=nww*x%mod;return ret;}
int C(int n,int m){return frac[n]*invf[m]%mod*invf[n-m]%mod;}
signed main()
{
	scanf("%s%lld",n+1,&k);l=strlen(n+1);
	if(l<=k+1){for(int i=l;i>=1;i--)n[k+1-l+i]=n[i];for(int i=k+1-l;i>=0;i--)n[i]='0';l=k+1;}
	//printf("%s\n",n+1);
	for(int i=l;i>=1;i--)if(n[i]=='0')n[i]='1';else{n[i]='0';break;}
	for(int i=0;i<k;i++)scanf("%lld",a+i);
	for(int i=1;i<=l;i++)val[i]=(val[i-1]*2+n[i]-'0')%mod,pre[i]=pre[i-1]+n[i]-'0';
	pww[0]=frac[0]=invf[0]=1;
	for(int i=1;i<=k;i++)pww[i]=pww[i-1]*2%mod,frac[i]=frac[i-1]*i%mod,invf[i]=ksm(frac[i],mod-2);
	for(int i=0;i<=k+1;i++)
	{
		x[i]=i;
		if(i)y[i]=(y[i-1]+F(i))%mod;
		else y[i]=F(i);
	}
	if(val[l]<=k+1)ans=y[val[l]];
	else
	{
		for(int i=0;i<=k+1;i++)
		{
			int prod=y[i],divi=1;
			for(int j=0;j<=k+1;j++)if(i!=j)prod=prod*(val[l]-x[j]+mod)%mod,divi=divi*(x[i]-x[j]+mod)%mod;
			ans=(ans+prod*ksm(divi,mod-2)%mod)%mod;
		}
	}
	//printf("%lld\n",ans);
	for(int i=k-1,j=l;i>=0&&j>=1;i--,j--)
	{
		if(n[j]=='0')
		{
			if(pre[j]&1)ans=(ans+F(val[j]+1))%mod;
			else ans=(ans+mod-F(val[j]+1))%mod;
		}
		for(int t=0;t<=k;t++)b[t]=0;
		for(int k=0;k<=i;k++)for(int t=0;t<k;t++)
		{
			b[t]=(b[t]+mod-a[k]*pww[t]%mod*C(k,t)%mod)%mod;
		}
		for(int t=0;t<=k;t++)a[t]=b[t];
		//for(int t=0;t<=k;t++)printf("%d ",a[t]);printf("\n");
	}
	printf("%lld\n",ans*ksm(2,mod-2)%mod);
	return 0;
}
```

---

## 作者：zzw4257 (赞：4)

> 初始有 $S_1=\mathrm{a}$
> 
> 定义 $S^R$ 为 $S$ 中的字符翻转的结果( $a,b$ 互换)
>
> $S_{i}=S_{i-1}+S^R_{i-1}$
>
> 再定义一个 $K$ 次多项式 $f(x)$
> 
> 求 $\displaystyle \sum_{i=0}^{n-1}[S_{\infty,i}=\mathrm{b}]f(i)$

~~现在格式应该没问题了吧~~

考察 $n$ 的特殊给出方式我们可以感受到按照二进制拆分成若干个 $2^k$ 的区间，每个区间其实是前缀/前缀的$R$,下面为了方便表述设       $g(x,i,j)=x^i\cdot\left([S_{\infty,x}=b]\bigoplus j\right)$

具体的，我们设 $\displaystyle f_{i,j,c}=\sum_{k=0}^{2^i-1}g(k,j,c)$

意思是 $S_{\infty}$ 中 $[0,2^i)$ 前缀/前缀反串( $c$ 表示)中 $x^j$ 次项的和

考虑预处理所有的 $f$

注意到 $[0,2^i)$ 到 $[0,2^{i+1})$ 增量的部分其实是把前一半取反，再平移，注意到平移是在底数的，自然地想到二项式定理展开

$$
\begin{aligned}
&\sum_{P(i)}(p_i+\Delta)^k\\=&\sum_{P(i)}\sum_{j=0}^kp_i^j\Delta^{k-j}\binom{k}{j}
\\=&\sum_{j=0}^k\Delta^{k-j}\binom{k}{j}\sum_{P(i)}p_i^j
\end{aligned}
$$


放到本题中即 $f_{i,j,c}=f_{i-1,j,c}+\sum\limits_{k=0}^j \binom{j}{k}\left(2^i\right)^{j-k}f_{i-1,j,c\bigoplus1}$ ，初值有 $f_{0,0,1}=1 $

再提及一下推答案

设 $n$ 中第 $k$ 高位的 `1` 是 $2^i$ ， $(k,\log_2 n]$ 高位的值是 $\Delta$ ,此位的贡献是 $\sum\limits_{j=0}^K\sum\limits_{k=0}^j\binom{j}{k}\left(\Delta\right)^{j-k}f_{i,j,[k~\mathrm{is~odd}]\bigoplus1}$

解释一下其实我们提取出这一位为 $1$ 表示的长度为 $2^i$ 的段,其本质是 $[0,2^i)$ 的前缀(有正反之分由 $[k~\mathrm{is~odd}]\bigoplus1$ 确定)再平移$\Delta$

好的然后现在你已经可以在 $\mathcal{O(nk^2)}$ 的时间内预处理+算答案了

这里是$60$分的写法

```cpp
inline void Solve1(void){
	int i,j,k,sum,v,now=0,dlt=0;
	f[0][0]=1;
	for(i=1;i<=n;++i){
		for(v=pw[i-1],*Pw=j=1;j<K;++j)Pw[j]=1ll*v*Pw[j-1]%mod;
		for(j=0;j<K;++j){
			f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
			for(k=0;k<=j;++k)f[i][j]=(f[i][j]+1ll*g[i-1][k]*C[j][k]%mod*Pw[j-k])%mod,
			g[i][j]=(g[i][j]+1ll*f[i-1][k]*C[j][k]%mod*Pw[j-k])%mod;
		}
	}
	for(i=n-1;~i;--i)if(str[n-i-1]=='1'){
		now^=1;
		for(*Pw=j=1;j<K;++j)Pw[j]=1ll*dlt*Pw[j-1]%mod;
		for(j=0;j<K;++j){
			for(sum=0,k=0;k<=j;++k)sum=(sum+1ll*(now&1?g[i][k]:f[i][k])*C[j][k]%mod*Pw[j-k])%mod;
			ans=(ans+1ll*sum*a[j])%mod;
		}Add(dlt,pw[i]); 
	}
	printf("%d\n",ans);
}
```

紧接着分析(~~打表~~)一下可以得出

> Lemma
> 
> $\forall i>j,f_{i,j,0}-f_{i,j,1}=0$

证明在NOI OL官方题解已经有详细证明，基于 $i=j$ 向 $i=j+1$ 的转移作为归纳法基底即可简单证明

考虑这个引理的意思是对于 $i>K$ 的部分，有其任意次项的贡献无论正串反串答案均为 $\frac{\sum\limits_{j=0}^{2^i}f(j)}{2}$ 易发现这东西是自然数幂和的前缀和，是一个 $K+1$ 次多项式直接插即可

更具体的当 $K>n$ 时设 $n$ 有 $C$ 位

对 $[0,K-1]$ 位暴力算预处理和算答案均为 $\mathcal{O(k^3)}$ ,  $[K,C]$ 位取出其二进制权和$v$,总贡献为 $\frac{\sum\limits_{j=0}^{v}f(j)}{2}$ ，这个东西 $O(K^2)$ 暴力算前几项再插值即可

下面的代码民间数据过了，应该是对的吧

```cpp
#include<bits/stdc++.h>
#define N 1000001
#define M 506
#define mod 1000000007
using namespace std;
char str[N];
int n,K,a[M],C[M][M],pw[N],Pw[M],f[M][M],g[M][M],ans,suf[M],pre[M],F[M],inv[M];
inline void Add(int&x,int y){x=(x+y>=mod)?x+y-mod:x+y;}
inline int Mod(int x){return x>=mod?x-mod:x;}
inline int Lag(int *f,int m,int n){
	int i,pre,ans=0;suf[m+1]=1;
	for(inv[1]=*inv=1,i=2;i<=m;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	for(i=1;i<=m;++i)inv[i]=1ll*inv[i-1]*inv[i]%mod;
	for(i=m;~i;--i)suf[i]=1ll*suf[i+1]*Mod(n-i+mod)%mod;
	for(pre=i=1;i<=m;pre=1ll*pre*Mod(n-i+mod)%mod,++i)ans=(ans+(((m-i)&1)?mod-1ll:1ll)*pre%mod*suf[i+1]%mod*inv[i-1]%mod*inv[m-i]%mod*f[i]%mod+mod)%mod;
	return ans;
}
inline void Solve1(void){
	int i,j,k,sum,v,now=0,dlt=0;
	f[0][0]=1;
	for(i=1;i<=n;++i){
		for(v=pw[i-1],*Pw=j=1;j<K;++j)Pw[j]=1ll*v*Pw[j-1]%mod;
		for(j=0;j<K;++j){
			f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
			for(k=0;k<=j;++k)f[i][j]=(f[i][j]+1ll*g[i-1][k]*C[j][k]%mod*Pw[j-k])%mod,
			g[i][j]=(g[i][j]+1ll*f[i-1][k]*C[j][k]%mod*Pw[j-k])%mod;
		}
	}
	for(i=n-1;~i;--i)if(str[n-i-1]=='1'){
		now^=1;
		for(*Pw=j=1;j<K;++j)Pw[j]=1ll*dlt*Pw[j-1]%mod;
		for(j=0;j<K;++j){
			for(sum=0,k=0;k<=j;++k)sum=(sum+1ll*(now&1?g[i][k]:f[i][k])*C[j][k]%mod*Pw[j-k])%mod;
			ans=(ans+1ll*sum*a[j])%mod;
		}Add(dlt,pw[i]); 
	}
	printf("%d\n",ans);
}
inline void Solve2(void){
	int i,j,k,sum,res,v,now=0,dlt=0; 
	f[0][0]=1;
	for(i=1;i<=K;++i){
		for(v=pw[i-1],*Pw=j=1;j<K;++j)Pw[j]=1ll*v*Pw[j-1]%mod;
		for(j=0;j<K;++j){
			f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
			for(k=0;k<=j;++k)f[i][j]=(f[i][j]+1ll*g[i-1][k]*C[j][k]%mod*Pw[j-k])%mod,
			g[i][j]=(g[i][j]+1ll*f[i-1][k]*C[j][k]%mod*Pw[j-k])%mod;
		}
	}
	for(i=n-1;~i;--i)if(str[n-i-1]=='1'){
		now^=1;if(i>K){dlt=(dlt+pw[i])%mod;continue;}
		for(*Pw=j=1;j<K;++j)Pw[j]=1ll*dlt*Pw[j-1]%mod;
		for(j=0;j<K;++j){
			for(sum=0,k=0;k<=j;++k)sum=(sum+1ll*(now&1?g[i][k]:f[i][k])*C[j][k]%mod*Pw[j-k])%mod;
			ans=(ans+1ll*sum*a[j])%mod;
		}Add(dlt,pw[i]); 
	}
	for(res=0,i=1;i<=K+5;++i){
		for(sum=0,j=K-1;~j;--j)sum=(1ll*sum*(i-1)+a[j])%mod;
		Add(res,sum);F[i]=res;
	}
	for(dlt=0,i=n-1;i>K;--i)if(str[n-i-1]=='1')Add(dlt,pw[i]); 
	printf("%lld\n",(ans+500000004ll*Lag(F,K+5,dlt))%mod);
}
int main(void){
	freopen("angry.in","r",stdin);
	freopen("angry.out","w",stdout);
	int i,j;scanf("%s%d",str,&K),n=strlen(str);
	for(i=0;i<K;++i)scanf("%d",a+i);
	for(C[0][0]=i=1;i<=K;++i)
		for(C[i][0]=j=1;j<=i;++j)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	for(*pw=i=1;i<=n;++i)Add(pw[i]=pw[i-1],pw[i-1]);
	if(n<=500)return Solve1(),0;
	Solve2();
	return 0;
}
```

---

## 作者：Chinese_zjc_ (赞：4)

其实这题的奖励关构造方式与正解是有一定联系的.

开始时 $s_0=0$ ,随后复制并翻转,恰好使字符串上的 $popcount$ 的奇偶性反转.

或者更详细地,对于 $s_i$ 有下列转移:
$$
s_i=
\begin{cases}
1-s_{i-highbit(i)} & i>0\\
0                  & i=0\\
\end{cases}
$$
因此 $s_i=popcount(i)\bmod 2$ .

显然有一种暴力的方式就是枚举每个 $s_i=1$ 的 $f(i)$ 求和.

**下面我们令 $N$ 为二进制数 $n$ 转十进制后的值, $n_i$ 表示二进制数 $n$ 从低到高的第 $i$ 位的值( $0$ 或 $1$ ), $n$ 表示二进制数 $n$ 的长度(即看作字符串时的长度), $C_i=\{x\in \text{N}|popcount(x)\bmod2=i\}$ .**
$$
ans=\sum_{i=0,i\in C_1}^{N-1}f(i)
$$
这个的时间复杂度是$O(Nk)$的.

推推式子,让这个表达式不要包含$i\in C_1$这种不好一起计算的东西.

考虑拆成两个式子:
$$
\begin{aligned}
ans&=\sum_{i=0,i\in C_1}^{N-1}f(i)\\
&=\frac{1}{2}\sum_{i=0}^{N-1}f(i)-\frac{1}{2}\sum_{i=0}^{N-1}(-1)^{popcount(i)}f(i)
\end{aligned}
$$
左边这个东西可以利用待定系数法,使用拉格朗日插值或高斯消元法求出 $f(i)$ 的前缀和的多项式,在代入求值.可以证明其前缀和的多项式是不超过 $k+1$ 次的.

现在就只需要求出右边这块:
$$
\begin{aligned}
\sum_{i=0}^{N-1}(-1)^{popcount(i)}f(i)
&=\sum_{i=0}^{k-1}a_i\sum_{j=0}^{N-1}(-1)^{popcount(j)}j^i &(\text{展开多项式并提取公因式})\\
&=\sum_{i=0}^{k-1}a_i\sum_{j=0,n_j=1}^{n-1}(-1)^{popcount(T)}\sum_{l=0}^{2^j-1}(-1)^{popcount(l)}(T+l)^i &(T=\sum_{l=j+1,n_l=1}^{n-1}2^l)\\
&=\sum_{i=0}^{k-1}a_i\sum_{j=0,n_j=1}^{n-1}(-1)^{popcount(T)}\sum_{l=0}^i{i\choose l}T^l\sum_{p=0}^{2^j-1}(-1)^{popcount(p)}p^{i-l} &(\text{利用二项式定理展开}(T+p)^i)\\
\end{aligned}
$$
发现 $\sum_{p=0}^{2^j-1}(-1)^{popcount(p)}p^{i-l}$ 的值仅与 $i-l$ 和 $j$ 有关,考虑预处理出它们的值.

令 $sum(i,j)=\sum_{l=0}^{2^i-1}(-1)^{popcount(l)}l^j$ ,则有:
$$
\begin{aligned}
sum(i,j)
&=\sum_{l=0}^{2^i-1}(-1)^{popcount(l)}l^j\\
&=\sum_{l=0}^{2^{i-1}-1}(-1)^{popcount(l)}l^j-\sum_{l=0}^{2^{i-1}-1}(-1)^{popcount(l)}(2^{i-1}+l)^j &(\text{拆成两半计算})\\
&=sum(i-1,j)-\sum_{l=0}^{2^{i-1}-1}(-1)^{popcount(l)}(2^{i-1}+l)^j &(\text{左边的可以直接替换})\\
&=sum(i-1,j)-\sum_{l=0}^{j}{j\choose l}2^{(i-1)l}\sum_{p=0}^{2^{i-1}-1}(-1)^{popcount(p)}p^{j-l} &(\text{利用二项式定理展开})\\
&=sum(i-1,j)-\sum_{l=0}^{j}{j\choose l}2^{(i-1)l}sum(i-1,j-l) &(\text{右边的也可以替换了})\\
\end{aligned}
$$
然后就可以做到 $O(nk^2)$ 求出正确答案.

考虑删去冗余的计算.

其实 $sum(i,j)$ 在 $i>j$ 时是为 $0$ 的,可以使用数学归纳法证明:

~~然而我并不是很懂数学归纳法…~~

- 当 $i=0$ 时,不存在自然数 $j<i$ ,结论显然成立.

- 当 $i>0$ 时,我们分类讨论 $j<i-1$ 与 $j=i-1$ 的情况.

  - 当 $j<i-1$ 时, $sum(i-1,j)$ 与 $sum(i-1,j-l)$ 都为 $0$ ,因此 $sum(i-1,j)$ 亦为 $0$ .

  - 当 $j=i-1$ 时,
    $$
    \begin{aligned}
    sum(i,j)&=sum(i-1,j)-\sum_{l=0}^j{j\choose l}2^{(i-1)l}sum(i-1,j-l)\\
    &=sum(i-1,j)-sum(i-1,j)-\sum_{l=1}^j{j\choose l}2^{(i-1)l}sum(i-1,j-l)\\
    &=-\sum_{l=1}^j{j\choose l}2^{(i-1)l}sum(i-1,j-l)\\
    &=0
    \end{aligned}
    $$
    

因此命题得证.
$$
\begin{aligned}
\sum_{i=0}^{N-1}(-1)^{popcount(i)}f(i)
&=\sum_{i=0}^{k-1}a_i\sum_{j=0,n_j=1}^{n-1}(-1)^{popcount(T)}\sum_{l=0}^i{i\choose l}T^l\sum_{p=0}^{2^j-1}(-1)^{popcount(p)}p^{i-l}\\
&=\sum_{i=0}^{k-1}a_i\sum_{j=0,n_j=1}^{n-1}(-1)^{popcount(T)}\sum_{l=0}^i{i\choose l}T^lsum(j,i-l)\\
&=\sum_{i=0}^{k-1}a_i\sum_{j=0,n_j=1}^{\min(k,n)-1}(-1)^{popcount(T)}\sum_{l=0}^i{i\choose l}T^lsum(j,i-l)\\
\end{aligned}
$$
这样就可以在 $O(k^3)$ 的时间处理出后面部分,再合并前面的算法即可通过此题.

---

## 作者：破壁人五号 (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P7468)

## 题意
定义串 $A_0=\texttt{a}$，$A_i=A_{i-1}+\overline{A_{i-1}}$（其中上划线代表 a b 互换），考虑串 $A_\infty[0..n-1]$。给定 $k-1$ 次多项式 $f$，求 $\sum_{i=0}^{n-1}[A_\infty[i]=\texttt{b}]f(i)$。$n\leq 2^{500000}$，$k\leq 500$。

## 题解
我们首先考虑 $O(k^2\log n)$ 的做法：我们维护多项式 $F_{i,\texttt{a}/\texttt{b}}(x)$ 代表把字符串 $A_i$ 平移到 $x$ 处后，$\texttt{a}/\texttt{b}$ 的贡献。$F_{0,\texttt{a}}=f,F_{0,\texttt{b}}=0$。

我们有 $F_{i,\texttt{a}}(x)=F_{i-1,\texttt{a}}(x)+F_{i-1,\texttt{b}}(x+2^{i-1})$（$F_{i,\texttt{b}}$ 同理），处理系数平移需要 $O(k^2)$（二项式定理展开），一共要递推到 $F_{\log n,\texttt{a}/\texttt{b}}$。

如果你在调试时输出了多项式，你可能会发现在 $i\geq k$ 时，$F_{i,\texttt{a}}=F_{i,\texttt{b}}$。证明可以参见[官方题解](http://www.noi.cn/xw/2021-03-27/724334.shtml)。（考试时我输出了调试信息，但是没发现结论，一个悲伤的故事）

知道这个结论后，我们可以只处理到 $F_{k-1,\texttt{a}/\texttt{b}}$，剩下的部分借助自然数幂和计算。复杂度 $O(k^3+\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int getint(){
    int ans=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c)){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans;
}
const int K=503,N=500010,mod=1e9+7;
int f[2][K],g[2][K];
int c[K][K];
char s[N];int n;

int p2[N];
int p[N],q[N];

int sp[N];
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*1ll*x%mod;
        x=x*1ll*x%mod;
        y>>=1;
    }
    return ans;
}
int main(){
    freopen("angry.in","r",stdin);
    freopen("angry.out","w",stdout);
    scanf("%s",s+1);
    n=strlen(s+1);
    int k=getint();
    if(n<k){
        for(int i=n;i;i--)s[k-n+i]=s[i];
        for(int i=1;i<=k-n;i++)s[i]='0';
        n=k;
    }
    for(int i=0;i<k;i++)f[0][i]=getint();
    for(int i=c[0][0]=1;i<=k;i++)
        for(int j=c[i][0]=1;j<=k;j++)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    p2[0]=1;for(int i=1;i<=n;i++)p2[i]=p2[i-1]<<1,p2[i]>=mod&&(p2[i]-=mod);
    for(int i=1;i<=n;i++){
        q[n-i]=q[n-i+1]^(s[i]-'0');
        p[n-i]=(p[n-i+1]+(s[i]-'0')*p2[n-i])%mod;
    }

    int ans=0;

    int m=p[0];
    // cerr<<"> "<<m<<endl;
    sp[0]=m;
    for(int i=1;i<k;i++){
        sp[i]=qpow(m,i+1);
        for(int j=0;j<i;j++)
            sp[i]=(sp[i]-c[i+1][j]*1ll*sp[j]%mod+mod)%mod;
        sp[i]=sp[i]*1ll*qpow(i+1,mod-2)%mod;
        // cerr<<"> "<<sp[i]<<endl;
    }
    for(int i=0;i<k;i++)ans=(ans+f[0][i]*1ll*sp[i])%mod;

    for(int i=0;i<k;i++){
        // for(int i=0;i<k;i++)cerr<<">"<<f[0][i];cerr<<endl;
        // for(int i=0;i<k;i++)cerr<<">"<<f[1][i];cerr<<endl;cerr<<endl;
        int q=::q[i],p=::p[i+1];
        if(s[n-i]-'0'){
            int v=0;
            for(int j=0;j<k;j++)
                v=(v*1ll*p+f[q][k-j-1])%mod;
            ans=(ans+v)%mod;
            v=0;
            for(int j=0;j<k;j++)
                v=(v*1ll*p+f[q^1][k-j-1])%mod;
            ans=(ans+mod-v)%mod;
        }

        memcpy(g,f,sizeof(g));
        int e=p2[i];
        for(int j=0;j<k;j++){
            int pe=1;
            for(int l=j;l>=0;l--,pe=pe*1ll*e%mod){
                int t=pe*1ll*c[j][l]%mod;
                g[1][l]=(g[1][l]+f[0][j]*1ll*t)%mod;
                g[0][l]=(g[0][l]+f[1][j]*1ll*t)%mod;
            }
        }
        memcpy(f,g,sizeof(f));
    }

    ans=(mod+1ll)/2*ans%mod;

    cout<<ans;
}

```


---

## 作者：TempestMiku (赞：1)

#  [愤怒的小 N](https://www.luogu.com.cn/problem/P7468)
## 前置知识

- 拉格朗日差值

- 二项式定理


## 题目描述

极度愤怒的小 N 通关了一款游戏来泄愤。

这款游戏共有 $n$ 关，分别为第 $0$ 关、第 $1$ 关、第 $2$ 关、$\cdots$、第 $n-1$ 关。这些关卡中有一些是普通关卡，另一些则是奖励关卡。

这款游戏中普通关卡与奖励关卡的分布比较特殊。如果用字符 $\texttt{a}$ 表示普通关卡，用字符 $\texttt{b}$ 表示奖励关卡，那么第 $0$ 关、第 $1$ 关、第 $2$ 关、$\cdots$、第 $n-1$ 关依次排列形成的字符串是一个无穷字符串 $s$ 的前缀，且 $s$ 可以按照如下方式构造：

1. 初始时 $s$ 为包含单个字符 $\texttt{a}$ 的字符串。

2. 将 $s$ 的每个字符 $\texttt{a}$ 替换成字符 $\texttt{b}$，每个字符 $\texttt{b}$ 替换成字符 $\texttt{a}$ 得到字符串 $t$，然后将 $t$ 拼接到 $s$ 后。
3. 不断执行2. 得到的字符串就是最终的 $s$。

可以发现 $s=\texttt{abbabaabbaababba}\cdots$，所以这款游戏的第 $0$ 关是普通关卡，第 $1$ 关
是奖励关卡，第 $2$ 关是奖励关卡，第 $3$ 关是普通关卡，以此类推。

通过游戏的第 $i$ 关可以得到 $f(i)$ 分，其中 $f(x)=a_0+a_1x+a_2x^2+\cdots+a_{k-1}x^{k-1}$ 
是一个固定的 $k-1$ 次多项式。

小 N 通关时一气之下通过了所有奖励关卡而忽略了所有普通关卡，然后就把游戏卸载了。现在回想起来，他想要知道他在卸载游戏前的总得分对 $10^9+7$ 取模后的结果。

## 题意转化

首先观察 $s$ 字符串的性质。$s$ 中的每一位 $\text{b}$ 都由上次对应状态的 $a$ 转来，因为只有 $\text{b}$ 会产生贡献，不妨设 $\text{b}$ 为 $1$，设 $\text{a}$ 为 $\text{0}$。

$$s_i=\begin{cases}
0 & i=0\\
1-s_{i-2^m} & i>1 & \text{（其中 } 2^m \text{ 为离 } i \text{ 最近的值，即 highbit。）}
\end{cases}$$

暴力找 $s_i$ 一定会超时，那么我们可以观察它的性质。

每次 $s_i$ 相当于在原来的 $s_{i-2^m}$ 的基础上在前面加了一个 $1$，所以这个数的奇偶性会改变。

再根据 $s_0=0$ ~~和打表~~，我们到:

$$s_i=\operatorname{popcount}(i)\bmod 2$$


这里有个 $\bmod 2$，看的好丑，化简一下：

$$\begin{aligned}
s_i &=\operatorname{popcount}(i)\bmod 2\\
    &= \frac{1}{2}\times(1-(-1)^{\operatorname{popcount}(i)})
\end{aligned}$$

记 $f(x)=a_0+a_1x+a_2x^2+\cdots+a_{k-1}x^{k-1}=\sum_{i=0}^{k-1}a_i\times x^i$

所以最终答案为：

$$\begin{aligned}
ans &=\sum_{i=0}^{n-1}f(i)\times s_i\\
    &=\sum_{i=0}^{n-1}f(i)\times(\operatorname{popcount}(i)\bmod2)\\
    &=\frac{1}{2}\sum_{i=0}^{n-1}f(i)\times (1-(-1)^{\operatorname{popcount}(i)})
\end{aligned}$$

我们把这个式子展开得到：

$$\begin{aligned}
ans &=\frac{1}{2}\sum_{i=0}^{n-1}f(i)\times (1-(-1)^{\operatorname{popcount}(i)})\\
    &=\frac{1}{2}\sum_{i=0}^{n-1}f(i) - \frac{1}{2}\sum_{i=0}^{n-1}f(i)\times (-1)^{\operatorname{popcount}(i)}\\
    &=\frac{1}{2}(\sum_{i=0}^{n-1}f(i) - \sum_{i=0}^{n-1}f(i)\times (-1)^{\operatorname{popcount}(i)})\\
\end{aligned}$$

因此我们将式子化为了两部分。先看第一部分。

$$\sum_{i=0}^{n-1}f(i)$$

其中 $f(i)$ 为 $k-1$ 次多项式，那么显然 $\sum_{i=0}^{n-1}f(i)$ 为 $k$ 次多项式。

- 证明：我们对 $\sum_{i=0}^{n-1}f(i)$ 作差分，得到每一项为 $f(i)$，而 $f(i)$ 为 $k-1$ 次多项式，根据**差分后的多项式的次数为原多项式的次数减一**可得 $\sum_{i=0}^{n-1}f(i)$ 为 $k$ 次多项式。

记 $F(x)=\sum_{i=0}^{x-1}f(i)$

那么我们可以预处理横坐标为 $0\sim k+1$ 的前缀和，根据**拉格朗日插值**得出 $F(x)$。

- 拉格朗日插值定理

$$\operatorname{f}(x)=\sum_{i=1}^{n}y_i\prod_{j\ne i}\frac{x-x_i}{x_i-x_j}$$

- 拉格朗日插值定理在横坐标连续的时候的公式

$$f(x)=\sum\limits_{i=1}^{n+1}y_i\cdot\frac{\prod\limits_{j=1}^{n+1}(x-j)}{(x-i)\cdot(-1)^{n+1-i}\cdot(i-1)!\cdot(n+1-i)!}
$$

然后再看第二部分的贡献。

$$\sum_{i=0}^{n-1}f(i)\times (-1)^{\operatorname{popcount}(i)}$$

好像没法化简了？

那么只能把 $f(i)$ 展开。

$$\sum_{i=0}^{n-1}(-1)^{\operatorname{popcount}(i)}\times \sum_{r=0}^{k-1}a_i\times i^r$$

交换一下求和的顺序，可得：

$$\sum_{r=0}^{k-1}a_r\sum_{i=0}^{n-1}(-1)^{\operatorname{popcount}(i)} i^r $$

现在前面的系数 $\sum_{r=0}^{k-1}a_r$ 很好求，考虑后面一项要怎么求。

$$ \sum_{i=0}^{n-1}(-1)^{\operatorname{popcount}(i)} i^r $$

我们考虑把 $n$ 拆成二进制，对于每个 $1$ 考虑。

假设有二进制数 $10001010$，那么它的答案就是 $10000000+1000+10$ 三部分的贡献。


现在，考虑一段区间 $[ x,x+2^t)$ 我们要求它的贡献。

可得：

$$ \sum_{i=x}^{x+2^t-1}(-1)^{\operatorname{popcount}(i)} i^r $$

我们用 $\operatorname{sum}(x,t,k)$ 来表示它。

把他化简成从 $0$ 开始的形式：

$$ \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i+x)} (i+x)^{r} $$

根据

$$(-1)^{a+b}=(-1)^a\times(-1)^b$$

$$(-1)^{\operatorname{popcount}(a+b)}=(-1)^{\operatorname{popcount}(a)}\times(-1)^{\operatorname{popcount}(b)}$$

可得

$$ (-1)^{\operatorname{popcount}(x)} \cdot \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} (i+u)^{r} $$

设 

$$\operatorname{sum}(x,t,k)=(-1)^{\operatorname{popcount}(x)} \cdot \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} (i+x)^{k} $$

嗯？后面怎么有 $(i+x)^{k}$，二项式定理展开一下得到：$\sum_{j=0}^{k}C_{k}^{j}x^{k-j}i^{j}$，即：

$$\operatorname{sum}(x,t,k)=(-1)^{\operatorname{popcount}(x)} \cdot \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} \sum_{j=0}^{k}C_{k}^{j}x^{k-j}i^{j} $$

继续交换求和顺序，得到：

$$\operatorname{sum}(x,t,k)=(-1)^{\operatorname{popcount}(x)}\cdot  \sum_{j=0}^{k}C_{k}^{j}x^{k-j} \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)}\cdot i^{j} $$

化简后半部分 $\sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)}\cdot i^{j}$ ，发现这一项是 $\operatorname{sum}(0,t,j)$

即：

$$\operatorname{sum}(x,t,k)=(-1)^{\operatorname{popcount}(x)} \cdot \sum_{j=0}^{k}C_{k}^{j}x^{k-j} \times \operatorname{sum}(0,t,j)$$


怎么计算 $\operatorname{sum}(0,t,j)$ 呢？

$$\begin{aligned}

\operatorname{sum}(0,t,j)&=(-1)^{\operatorname{popcount}(0)} \cdot \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} i^{j}\\

&=\sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} i^{j}\\

&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} i^{j} + \sum_{i=2^{t-1}}^{2^{t}-1}(-1)^{\operatorname{popcount}(i)} i^{j} \\


&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} i^{j} + \sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i+2^t-1)} (i+2^{t-1})^{j} \\

&=\operatorname{sum}(0,t-1,j)+\operatorname{sum}(2^t-1,t-1,j)

\end{aligned}$$
这时候我们发现 $\operatorname{sum}$ 可以递推实现，但是让我们换一种推式子方法。 
$$\begin{aligned}

\operatorname{sum}(0,t,j)&=(-1)^{\operatorname{popcount}(0)} \cdot \sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} i^{j}\\

&=\sum_{i=0}^{2^t-1}(-1)^{\operatorname{popcount}(i)} i^{j}\\

&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} i^{j} + \sum_{i=2^{t-1}}^{2^{t}-1}(-1)^{\operatorname{popcount}(i)} i^{j} \\


&=\sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} i^{j} + \sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i+2^t-1)} (i+2^{t-1})^{j} \\

&=\operatorname{sum}(0,t-1,j)+\sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i+2^t-1)} (i+2^{t-1})^{j}
\\

&=\operatorname{sum}(0,t-1,j)+(-1)^{\operatorname{popcount}(2^t-1)}\cdot \sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} (i+2^{t-1})^{j}
\\

&=\operatorname{sum}(0,t-1,j)+ \sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} (i+2^{t-1})^{j}
\\

&=\operatorname{sum}(0,t-1,j)+ \sum_{i=0}^{2^{t-1}-1}(-1)^{\operatorname{popcount}(i)} (i+2^{t-1})^{j}
\\

&\text{类似上面，二项式定理展开再交换顺序}\\

&=\operatorname{sum}(0,t-1,j)+ \sum_{i=0}^{j}
C_j^s(2^{t-1})^{j-s}\operatorname{sum}(0,t-1,s)
\\

\end{aligned}$$

---

让我们回顾一下！

$$\begin{aligned}
ans &=\frac{1}{2}\sum_{i=0}^{n-1}f(i)\times (1-(-1)^{\operatorname{popcount}(i)})\\

    &=\frac{1}{2}\sum_{i=0}^{n-1}f(i) - \frac{1}{2}\sum_{i=0}^{n-1}f(i)\times (-1)^{\operatorname{popcount}(i)}\\

\end{aligned}$$

---

$$ans1=\sum_{i=0}^{n-1}f(i) \text{（用拉插实现）}$$

---

$$\begin{aligned}

ans2&=\sum_{i=0}^{n-1}f(i)\times (-1)^{\operatorname{popcount}(i)}\\

ans2&=\sum \operatorname{sum}(x,t,k)

\end{aligned}$$

---

$$ans=\frac{1}{2}(ans1-ans2)$$

## 代码实现：

```cpp
#include<bits/stdc++.h>
typedef int Int;
#define int long long
using namespace std;
namespace Testify{
    int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    void WritE(int x){
        if(x<0) putchar('-'),x=-x;
        if(x>9) WritE(x/10);
        putchar(x%10+48);
    }
    void write(int x){
        WritE(x);
        puts("");
    }
    void Write(int x){
        WritE(x);
        putchar(' ');
    }
}
using namespace Testify;
const int K=505;
const int N=1e6+5;
const int mod=1e9+7;
int iv2=((mod+1)/2);
char ch[N];
inline int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=res*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int C[505][505],n,m,a[N],ans1,ans2,p2[N];
inline void pre(){
    for(register int i=0;i<=m;i++){
        C[i][0]=C[i][i]=1;
        for(register int j=1;j<i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    p2[0]=1;
    for(register int i=1;i<=n;i++){
        p2[i]=2*p2[i-1]%mod;
    }
}
inline int niyuan(int x){
    return qpow(x,mod-2)%mod;
}
struct lar{
    int f(int x){
        int res=0;
        for(register int i=m-1;i>=0;i--){
            res=(res*x+a[i])%mod;
        }
        return res;
    }
    int fac[K],facinv[K],xi[K],yi[K],syi[K],nn;
    int pv[K],sf[K];
    inline void prepr(){
        nn=m+1;
        fac[0]=facinv[0]=1;
        for(register int i=1;i<=nn;i++){
            fac[i]=fac[i-1]*i%mod;
            facinv[i]=facinv[i-1]*qpow(i,mod-2)%mod;
        }
        yi[0]=f(0);
        for(register int i=1;i<=nn;i++){
            xi[i]=i;
            yi[i]=(yi[i-1]+f(i))%mod;
            int pree=facinv[i-1],suf=facinv[nn-i];
            if((nn-i)&1){
                suf=(mod-suf);
            }
            syi[i]=yi[i]*pree%mod*suf%mod; 
        }
    }
    inline int F(int x){
        x%=mod;
        if(x<=nn){
            return yi[x];
        }
        pv[0]=sf[nn+1]=1;
        for(register int i=1;i<=nn;i++){
            pv[i]=pv[i-1]*(x-xi[i])%mod;
        }
        for(register int i=nn;i;i--){
            sf[i]=sf[i+1]*(x-xi[i])%mod;
        }
        int res=0;
        for(register int i=1;i<=nn;i++){
            res=(res+(syi[i]*pv[i-1]%mod*sf[i+1]%mod))%mod;
        }
        return res%mod;
    }
}La;
int memory[505][505];
inline int sum(int t,int k){//计算sum(0,t,k)
    if(t>k) return 0;
    if(!t) return k==0;
    if(memory[t][k]!=-1){
        return memory[t][k];
    }
    int res=sum(t-1,k);
    int X=p2[t-1];
    int px=1;
    for(register int j=k;j>=0;j--,px=px*X%mod){
        res=(res+mod-C[k][j]*px%mod*sum(t-1,j)%mod)%mod;
    }
    memory[t][k]=res;
    return res;
}
inline void solve(){
    int tnm=0,tt=0;
    for(register int i=0;i<n;i++){
        int op=(2*tnm+ch[i]-'0')%mod;
        int cc=(tt^(ch[i]-'0'));
        if(n-i-1<=m){
            if(ch[i]=='1'){//划分区间
                int X=tnm*p2[n-i]%mod;
                for(register int k=0;k<m;k++){
                    int sm=0;
                    int px=1;
                    for(register int j=k;j>=0;j--,px=px*X%mod){
                        sm=(sm+C[k][j]*px%mod*sum(n-i-1,j)%mod)%mod;
                    }
                    if(tt) sm=(mod-sm);
                    ans2=(ans2+a[k]*sm%mod)%mod;
                }
            }
        }
        tnm=op,tt=cc;
    }
}
signed main(void){
    // freopen("angry.in","r",stdin);
    // freopen("angry.out","w",stdout);
    memset(memory,-1,sizeof(memory));
    scanf("%s",(ch));
    n=strlen(ch);
    m=read();
    for(register int i=0;i<m;i++){
        a[i]=read();
    }
    La.prepr();
    pre();
    int nm=0;
    for(register int i=0;i<n;i++){
        nm=(2*nm+ch[i]-'0')%mod;
    }
    nm=(nm+mod-1)%mod;
    ans1=La.F(nm);
    solve();
    int ans=(ans1+mod-ans2)%mod;
    ans=ans*iv2%mod;
    write(ans);
    return 0;
}
/*
1000
3
3 2 1

*/
```



---

## 作者：luogubot (赞：0)

给定 $N$ 和 $m-1$ 次多项式 $f(x)$，求 $\sum_{i=0}^{N-1}[{\rm popcount}(i)\equiv 1\pmod 2]f(i)$。

答案对 $10^9+7$ 取模。

$\log_N=n<5\times 10^5$，$1\leq m\leq 500$。

部分分：$O(nm^2)$。

多项式次数很少，显然可以对拆成对 $0\sim m-1$ 次幂的求和再乘对应系数。

设计一个 dp：$f_{i,j,0/1}$ 表示 $[0,2^i)$ 内，popcount 是偶数/奇数的数的 $j$ 次幂和。转移用二项式定理：$f_{i,j,k}=f_{i-1,j,k}+\sum_{l=0}^j \binom{j}{l}f_{i-1,l,k{\rm xor} 1}\times (2^{i-1})^{j-l}$（$(x+2^{i-1})^j$ 的展开），初始只需要 $i=0,1$ 的值。计算答案时考虑从高位到低位计算，如果当前位是 $1$，先处理这一位是 $0$ 的后面的所有情况，再往后处理这一位是 $1$ 的情况；否则忽略。这个也是二项式定理可以做的。$O(nm^2)$。

成为机器人，观察到当 $i>j$ 时，$dp_{i,j,0}=dp_{i,j,1}=\frac{\sum_{x=0}^{2^i-1}x^j}{2}$。证明是简单的，只需要注意到对于至少 $1$ 位的二进制数，其 popcount 是奇数/偶数的数量是相等的，那么我们把 $x$ 二进制拆分，$x^j$ 就相当于是一车二进制数加起来再 $j$ 次幂，直接枚举 $j$ 个位算对应的 $x$ 的方案数：这 $j$ 个位的并一定属于 $x$，假设并集大小是 $k$，当 $k<i$ 时，外面有至少 $1$ 位，所以对 $dp_{i,j,0}$ 和 $dp_{i,j,1}$ 的贡献是一样的；当 $j<i$ 时，$k\leq j<i$，所有贡献都一样，那么 $dp_{i,j,0}=dp_{i,j,1}$ 就显然了，而且其和是 $\sum_{x=0}^{2^i-1}x^j$。

同理，我们可以一并处理结算有至少 $m$ 个自由位的 $i$ 的贡献，发现如果 dp 值统一，高位结算的就是 $0\sim S-1$ 的 $j$ 次幂和相关的式子，其中 $S$ 是 $N$ 去掉低 $m$ 位后的值，可以插出 $f(n)=\sum_{i=0}^{n-1}\sum_{j=0}^{m-1}a_j\times i^j$，这是一个 $O(m)$ 次的多项式（自然数幂和的前缀和的叠加），这部分的贡献就是 $\frac{f(S)}{2}$。

---

