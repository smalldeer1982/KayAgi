# [AGC038E] Gachapon

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_e

すぬけくんはある乱数生成器を手に入れました。 この乱数生成器は、$ 0 $ 以上 $ N-1 $ 以下の整数を生成します。 それぞれの整数を生成する確率は、整数列 $ A_0,A_1,\cdots,A_{N-1} $ によって表され、 整数 $ i $ ($ 0\ \leq\ i\ \leq\ N-1 $) が生成される確率は $ A_i\ /\ S $ です。 ただしここで $ S\ =\ \sum_{i=0}^{N-1}\ A_i $ とします。 また、乱数生成は毎回独立に行われます。

すぬけくんはこれから、次の条件が満たされるまで、乱数生成を繰り返します。

- すべての $ i $ ($ 0\ \leq\ i\ \leq\ N-1 $) について、今までに乱数生成器が $ i $ を生成した回数が $ B_i $ 回以上である。

すぬけくんが操作を行う回数の期待値を求めてください。 ただし、期待値は mod $ 998244353 $ で出力してください。 より正確には、期待値が既約分数 $ P/Q $ で表されるとき、 $ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ <\ 998244353 $ を満たす整数 $ R $ が一意に定まるので、その $ R $ を出力してください。

なお、操作の回数の期待値が有理数として存在し、 さらに mod $ 998244353 $ での整数表現が定義できることが問題の制約から証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ A_i $
- $ \sum_{i=0}^{N-1}\ A_i\ \leq\ 400 $
- $ 1\ \leq\ B_i $
- $ \sum_{i=0}^{N-1}\ B_i\ \leq\ 400 $
- 入力される値はすべて整数である。

### Sample Explanation 1

すぬけくんが操作を行う回数の期待値は $ 3 $ です。

### Sample Explanation 2

すぬけくんが操作を行う回数の期待値は $ 132929/7200 $ です。

## 样例 #1

### 输入

```
2
1 1
1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 3
2 2
3 1```

### 输出

```
971485877```

## 样例 #3

### 输入

```
15
29 3
78 69
19 15
82 14
9 120
14 51
3 7
6 14
28 4
13 12
1 5
32 30
49 24
35 23
2 9```

### 输出

```
371626143```

# 题解

## 作者：Soulist (赞：42)

$\min-\max$ 容斥的题好少啊?...好难找...如果有看到这篇题解的善良人麻烦发一下 CF 上有没有对应的题吧/kel

题目是经典模型(求每个数都至少出现...), 但是每个数是有一个出现次数的要求 $B_i$

~~好久没写题解了，过来水一发~~

----

容易发现要求的值其实就是集合内最晚成为合法的元素的值, 考虑 $\min-\max$ 容斥, 有:

$$E(\max(S))=\sum_{T\subseteq S, T\ne \varnothing}E(\min(T))\times (-1)^{|T|+1}$$

现在考虑对于给定的一组 $T$ 集, 我们如何计算其相应的期望.

我们需要计算的实际上是存在一个元素属于 $T$ 集被选至上界的期望.

实际上集合之外的元素对于答案都没有贡献, 我们考虑去除这些元素的贡献, 只需要考虑期望多少次操作会选到集合内的元素即可, 不妨令 $W=\sum A_i$, 则选到集合内的元素的期望需要的次数为 $\frac{W}{\sum_{i\in T}A_i}$ 令其为 $P$

现在我们只需要关注集合内部的元素了, 对于这类问题(多少次才选中元素)的期望的操作次数, 有一个十分常见的转换是我们可以把他视为**每一轮均没有一个元素被选中(这里是被选中 $B_i$ 次)的概率之和**. ( 这里需要包括 $0$ 轮操作, 或者直接说答案需要 $+1$ )

于是不妨假设选到集合内有 $k$ 轮, 那么对应的操作次数应该为 $k\times P$, 所以单独一轮的贡献为 $P$, 所以其贡献为 $P\times E(\textbf{合法})$, 这里的合法即没一个元素被选中的概率( emm 简单说就是由于系数之前有一个 $k\times P$ 的贡献, 所以单独拆轮次来考虑贡献的时候应该为 $P\times$ 本轮没被选的概率).

等价于我们需要分配一组 $c_{1},c_{2}\sim c_{|T|}$, 且有 $c_i<B_i$, 且 $\sum c = k$, 考虑其对应的概率, 显然可以视为混合组合数乘以对应概率, 所以可以得到为:

$$\prod_{i\in T} (\frac{A_i}{\sum_{i\in T} A_i})^{c_i} \times \frac{k!}{c_1!c_2!...c_{|T|}!}$$

容易发现可以把每一位的贡献提取出来, 于是我们所求等价于(方便期间令 $w(T)=\sum_{i\in T} A_i$):

$$k!\prod_{i\in T}\frac{A_i^{c_i}}{w(T)^{c_i} c_i!}$$

现在将期望选入集合内的需要次数也写入答案, 于是我们可以把一个方案 $T$ 的答案写为 $(r=\sum_{i\in T} (B_i-1)~)$:

$$\sum_{k=0}^{r} P\times k!\prod_{i\in T,c_1+...c_{|T|=k}} \frac{A_i^{c_i}}{w(T)^{c_i}c_i!}$$

所以总答案即:


$$\sum_{T\subseteq S, T\ne \varnothing } (-1)^{|T|+1}\bigg(\sum_{k=0}^{r} P\times k!\times w(T)^{-k}\prod_{i\in T,c_1+...c_{|T|=k}} \frac{A_i^{c_i}}{c_i!}\bigg)$$

考虑如何设计一个 dp 来统计答案, 事实上, 我们只需要关注 $w(T)$ 以及 $k$ 就能够知道答案了, 或者说在考虑通过 dp 转移维护系数贡献和的时候, 只有某个数的 $-k$ 次幂这种形式的东西非常难维护, 所以将其放入状态即可. 

于是我们只需要令 $f_{i,j,k}$ 表示考虑到了前 $i$ 个数, 所选的 $c_i$ 之和为 $k$, 选择的 $\sum_{i\in T} A_i=j$ 的贡献和即可. 转移的时候注意如果将一个数选入集合那么容斥系数， 那么一定会强制增大 $(-1)$ 倍， 如果没有将当前数选入集合， 那么答案不变。

于是转移直接：

$$f_{i,j,k}=f_{i-1,j,k}-\sum_{l=0}^{\min(B_i-1,l)}f_{i-1,j-l,k-A_i}\times \frac{A_i^l}{l!}$$

然后就喜提一个 $O(n^4)$ 的做法（方便起见认为 $n$，$\sum A$，$\sum B$ 平级）

真的吗？

我们发现事实上我们的 $l$ 的枚举总量其实是 $O(\sum B)$ 的，所以实际上复杂度是 $O(n^3)$ 的，然后本题就可以愉快的通过惹。

值得一提的就是初始化是 $dp_{0,0,0}=-1$ 这是因为空集对应的容斥系数是 $(-1)^1=-1$ /lb

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 998244353 ; 
const int N = 400 + 5 ; 
int n, A[N], a[N][N], B[N], SA, SB, inv[N], fac[N], dp[N][N][N] ;
int fpow( int x, int k ) {
    int ans = 1, base = x ; 
    while( k ) {
        if( k & 1 ) ans = 1ll * ans * base % P ; 
        base = 1ll * base * base % P, k >>= 1 ; 
    } return ans % P ; 
}
int Dec( int x, int y ) {
    return ( x - y + P ) % P ; 
} 
signed main() 
{
    n = gi() ; 
    rep( i, 1, n ) A[i] = gi(), B[i] = gi() ; 
    rep( i, 1, n ) SA += A[i], SB += B[i] ; 
    fac[0] = inv[0] = 1 ; 
    rep( i, 1, SB ) fac[i] = fac[i - 1] * i % P, inv[i] = fpow( fac[i], P - 2 ) ;
    rep( i, 1, n ) rep( j, 0, SB ) a[i][j] = ( j == 0 ) ? 1 : a[i][j - 1] * A[i] % P ;
    dp[0][0][0] = -1 ; 
    rep( i, 1, n ) rep( j, 0, SA ) rep( k, 0, SB ) {
        dp[i][j][k] = dp[i - 1][j][k] ; 
        for( re int l = 0; l < B[i]; ++ l ) if( A[i] <= j && l <= k ) 
        dp[i][j][k] = Dec( dp[i][j][k], 1ll * dp[i - 1][j - A[i]][k - l] * a[i][l] % P * inv[l] % P ) ;
    }
    int Ans = 0 ;
    rep( j, 0, SA ) rep( k, 0, SB ) 
    Ans = ( Ans + SA * fpow( fpow( j, P - 2 ), k + 1 ) % P * dp[n][j][k] % P * fac[k] % P ) % P ;
    cout << Ans << endl ; 
	return 0 ; 
}
```

---

## 作者：tzc_wk (赞：17)

[Atcoder 题面传送门](https://atcoder.jp/contests/agc038/tasks/agc038_e) & [洛谷题面传送门](https://www.luogu.com.cn/problem/AT5202)

我竟然能独立做出 Ag 的 AGC E，incredible！更新了 Atcoder 做题难度上限（

首先按照套路 Min-Max 容斥，$ans=\sum\limits_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\times E(\min(T))$，考虑怎样求这个式子的值。首先我们需要搞清楚 $E(\min(T))$，假设 $T$ 中包含下标为 $x_1,x_2,\cdots,x_m$ 这 $m$ 个元素，那么 $E(\min(T))$ 的实际意义就是期望最少选多少个数就能找到一个 $x_i$ 的出现次数达到了其上界 $b_{x_i}$，首先有可能我们抽到的数不在 $T$ 当中，这里有一个小套路，我们记 $e$ 为期望多少次才能抽到一个 $T$ 中的数，那么显然 $e=\dfrac{\sum a_i}{\sum\limits_{x\in T}a_x}$，这样相当于我们将原来每一步的贡献 $1$ 变成了 $e$，因此我们只需将答案乘个 $e$ 就可以得到最终的 $E(\min(T))$。这样一来我们就不用考虑不在 $T$ 中的数的影响了，不过我们发现这东西是不太好直接求的，故我们不妨换个角度，我们假设到达最终状态时元素 $x_i$ 被选择的 $c_i$ 次，那么不难发现对于任意一个由初始状态 $0,0,\cdots,0$ 到达最终状态的取数方式，它中间总要经过 $\sum c_i$ 个满足 $c_i<b_{x_i}$ 的状态，因此我们可以在每个中间状态中累加一次贡献，而对于一个满足 $\forall i,c_i<b_{x_i}$ 的 $c_1,c_2,\cdots,c_m$，只要它到达了这个状态，它就肯定会被统计入答案中，因此我们要求的实际上是所有满足满足 $\forall i,c_i<b_{x_i}$ 的 $c_1,c_2,\cdots,c_m$，到达 $c_1,c_2,\cdots,c_m$ 的概率。而显然对于固定的 $c_1,c_2,\cdots,c_m$，到达 $c_1,c_2,\cdots,c_m$ 的概率可用总方案数除以到达 $c_1,c_2,\cdots,c_m$ 的方案数计算，即 $\dfrac{(\sum c_i)!}{\prod c_i!}\times\prod(\dfrac{a_i}{\sum\limits_{x\in S}a_x})^{c_i}$，第一项为多重组合数，即将 $i$ 个 $c_i$ 填入一排 $c_1+c_2+\cdots+c_m$ 个数的方案数，第二项表示生成 $c_i$ 个 $i$ 的方案数，生成一个 $i$ 的概率为 $\dfrac{a_i}{\sum\limits_{x\in S}a_x}$，生成 $c_i$ 个 $i$ 的概率就是 $(\dfrac{a_i}{\sum\limits_{x\in S}a_x})^{c_i}$，很好理解。

因此我们有：

$$E(\min(T))=\dfrac{\sum a_i}{\sum\limits_{x\in T}a_x}\sum\limits_{c_i\lt b_{x_i}}\dfrac{(\sum c_i)!}{\prod c_i!}\times\prod(\dfrac{a_i}{\sum\limits_{x\in S}a_x})^{c_i}$$

将其带入答案计算式可得

$$\begin{aligned}ans&=\sum\limits_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\times\dfrac{\sum a_i}{\sum\limits_{x\in T}a_x}\sum\limits_{c_i\lt b_{x_i}}\dfrac{(\sum c_i)!}{\prod c_i!}\times\prod(\dfrac{a_i}{\sum\limits_{x\in S}a_x})^{c_i}\\&=\sum\limits_{\varnothing\ne T\subseteq S}(-1)^{|T|-1}\times\dfrac{\sum a_i}{\sum\limits_{x\in T}a_x}\sum\limits_{c_i\lt b_{x_i}}\dfrac{(\sum c_i)!}{\prod c_i!}\times\prod a_i^{c_i}\times(\dfrac{1}{\sum\limits_{x\in T}a_x})^{\sum c_i}\end{aligned}$$

注意到 $\sum a_i$ 是定值，$\sum\limits_{x\in T}a_x,\sum c_i$ 都不会超过 $400$，因此考虑 $dp$，可以将其放入背包的状态中，设 $dp_{i,j,k}$ 表示所有 $T\subseteq\{1,2,3,\cdots,i\}$，$\sum\limits_{x\in T}a_x=j$，$\sum c_i=k$ 的 $(-1)^{|T|-1}\prod\dfrac{1}{c_i!}a_i^{c_i}$ 的和，转移就分 $i\in T$ 和 $i\notin T$ 转移即可，若 $i\notin T$ 则 $dp_{i,j,k}\leftarrow dp_{i-1,j,k}$，否则我们枚举 $c_i<b_i$，那么 $dp_{i,j,k}\leftarrow -dp_{i-1,j,k}\times\dfrac{1}{c_i!}a_i^{c_i}$，二者相加即可，初始值 $dp_{0,0,0}=-1$（因为空集的 $(-1)^{|T|+1}=-1$），求答案就枚举 $\sum\limits_{x\in T}a_x=j,\sum c_i=k$，然后用 $dp_{n,j,k}\times(\sum a_i)\times\dfrac{1}{j^{k+1}}\times k!$ 更新答案即可，第一维可以优化到，时间复杂度 $\sum a_i(\sum b_i)^2$，空间复杂度 $\sum a_i\sum b_i$，可以通过此题。

```cpp
const int MAXN=400;
const int MOD=998244353;
int n,a[MAXN+5],b[MAXN+5],sa,sb,dp[MAXN+5][MAXN+5];
int inv[MAXN+5],ifac[MAXN+5],fac[MAXN+5];
void init_fac(int n){
	for(int i=(inv[0]=inv[1]=ifac[0]=fac[0]=1)+1;i<=n;i++) inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) ifac[i]=1ll*ifac[i-1]*inv[i]%MOD,fac[i]=1ll*fac[i-1]*i%MOD;
}
int main(){
	scanf("%d",&n);init_fac(MAXN);dp[0][0]=MOD-1;
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]),sa+=a[i],sb+=b[i];
	for(int i=1;i<=n;i++){
		for(int j=sa;j>=a[i];j--) for(int k=sb;~k;k--)
			for(int l=0,pw=1;l<=min(k,b[i]-1);l++,pw=1ll*pw*a[i]%MOD){
				dp[j][k]=(dp[j][k]-1ll*dp[j-a[i]][k-l]*pw%MOD*ifac[l]%MOD+MOD)%MOD;
			}
	} int ans=0;
	for(int i=1;i<=sa;i++) for(int j=0,pw=1;j<=sb;j++,pw=1ll*pw*inv[i]%MOD){
		ans=(ans+1ll*dp[i][j]*pw%MOD*inv[i]%MOD*sa%MOD*fac[j]%MOD)%MOD;
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：x义x (赞：14)

[题目链接](https://atcoder.jp/contests/agc038/tasks/agc038_e)，[题目翻译](https://www.luogu.com.cn/problem/AT5202)

这题不仅不需要 min-max 容斥，而且也不需要阿贝尔变换和洛必达法则……

考虑

$$\begin{aligned}P(X\le n)&=n![x^n]\prod_{i=0}^{N-1}\sum_{j=B_i}\dfrac{(\dfrac{A_i}{S}x)^j}{j!}\\&=n![x^n]\prod_{i}\left(e^{\frac{A_i}{S}x}-\sum_{j=0}^{B_i-1}\dfrac{(\dfrac{A_i}{S}x)^j}{j!}\right)\end{aligned}$$

可以观察到它应该有这样的形式

$$n![x^n]\sum_{i=0}^SP_i(x)e^{\frac{i}{S}x}$$

显然 $P$ 是可以大力 DP 得出的。

答案应该是

$$\begin{aligned}\sum_{n=0}^{\infty}P(X>n)&=\sum_{n=0}^{\infty}1-n![x^n]\sum_{i=0}^SP_i(x)e^{\frac{i}{S}x}\\&=-\sum_{n=0}^{\infty}n![x^n]\sum_{i=0}^{S-1}P_i(x)e^{\frac{i}{S}x}\end{aligned}$$

是时候拆掉 $[x^n]$ 了。设 $P_{i,j}=[x^j]P_i(x),T=\sum B$。

$$-\sum_{n=0}^{\infty}n!\sum_{i=0}^{S-1}\sum_{j=0}^TP_{i,j}\dfrac{i^{n-j}}{S^{n-j}(n-j)!}$$

$$\boxed{-\sum_{i=0}^{S-1}\sum_{j=0}^TP_{i,j}\left(\dfrac{i}{S}\right)^{-j}\sum_{n=0}^{\infty}\left(\dfrac{i}{S}\right)^n\dfrac{n!}{(n-j)!}}$$

设后面那个东西是 $j!F_j(\dfrac{i}{S})$，也就是说

$$\begin{aligned}F_j(x)&=\sum_{i=0}^{\infty}{i\choose j}x^i\\&={0\choose j}+\sum_{i=1}^{\infty}\left({i-1\choose j}+{i-1\choose j-1}\right)x^i\\&=xF_j(x)+xF_{j-1}(x)\end{aligned}$$

$$\boxed{F_j(x)=\dfrac{x}{1-x}F_{j-1}(x)}$$

显然有 $F_0(x)=\dfrac{1}{1-x}$，递推即可。

注意特判 $x=0$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int p=998244353;
int qpow(int a,int k){
	int ans=1;
	while(k){
		if(k&1) ans=1LL*ans*a%p;
		a=1LL*a*a%p;
		k>>=1;
	}
	return ans;
}

int N;
int fac[405],ifac[405],inv[405];
int A[405],S,iS,B[405],T; 

int P[405][405];int G[405];

int main(){
	fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
	for(int i=2;i<=400;i++)
		inv[i]=1LL*(p-p/i)*inv[p%i]%p,
		fac[i]=1LL*fac[i-1]*i%p,
		ifac[i]=1LL*ifac[i-1]*inv[i]%p;
	scanf("%d",&N);
	for(int i=0;i<N;i++) scanf("%d%d",&A[i],&B[i]),S+=A[i],T+=B[i]-1;
	iS=qpow(S,p-2);
	
	P[0][0]=1;int tS=0,tT=0;
	for(int i=0;i<N;i++){
		for(int j=0,mul=1;j<=B[i]-1;j++) G[j]=1LL*mul*ifac[j]%p,mul=1LL*mul*A[i]%p*iS%p;
		tS+=A[i];tT+=B[i]-1;
		for(int j=tS;j>=0;j--){
			for(int k=tT;k>=0;k--){
				int tmp=0;
				for(int kk=0;kk<=B[i]-1&&kk<=k;kk++)
					tmp=(tmp+1LL*G[kk]*P[j][k-kk]%p)%p;
				P[j][k]=(p-tmp)%p;
			}
			if(j>=A[i]) for(int k=0;k<=tT;k++) P[j][k]=(P[j][k]+P[j-A[i]][k])%p;
		}
	}
	int ans=0;
	for(int i=0;i<S;i++){
		int x=1LL*i*iS%p,ix=qpow(x,p-2);
		int F=qpow(1-x+p,p-2),FF=F;
		for(int j=0;j<=T;j++){
			ans=(ans+1LL*P[i][j]*fac[j]%p*F%p)%p;
			F=1LL*F*FF%p;
		}
	}
	printf("%d\n",(p-ans)%p);
}
```

---

## 作者：_sys (赞：10)

有一个随机数生成器，生成 $[0,n-1]$ 之间的整数，其中生成 $i$ 的概率为 $\frac{A_i}{S}$，其中，$S=\sum A_i$。

这个随机数生成器不断生成随机数，当 $\forall i\in[0,n-1]$，$i$ 至少出现了 $B_i$ 次时，停止生成，否则继续生成。

求期望生成随机数的次数，输出答案对 $998244353$ 取模的结果。

$A_i,B_i\geq 1$，$\sum A_i,\sum B_i,n\leq 400$。

来一篇不需要容斥的直接推式子做法。

设 $F_u(x)$ 表示 $u$ 生成了不少于 $B_u$ 次的概率型指数生成函数。即

$$F_u(x)=\sum_{i=B_u}^{+\infty} (\frac{A_u}S)^i\frac{x^i}{i!}=e^{\frac{A_i}Sx}-\sum_{i=0}^{B_i-1}\frac{(\frac{A_i}Sx)^i}{i!}$$

则生成 $i$ 次已经结束（可能在更早的时间结束）的概率为

$$[x^i]\prod F_u(x)$$

所以答案为

$$\sum_{i=0}^{+\infty}1-i![x^i]\prod F_u(x)$$

设

$$\prod F_u(x)=\sum_{i=0}^Se^{\frac iSx}g_i(x)$$

其中 $g_i(x)$ 是不超过 $\sum B_i$ 次多项式。所以可以直接使用类似于背包的算法考虑 $F_u(x)$ 是选择 $e^{\frac{A_i}Sx}$ 还是 $\sum_{i=0}^{B_i-1}\frac{(\frac{A_i}Sx)^i}{i!}$，暴力多项式运算即可。

算出所有 $g_i(x)$ 后，可得答案为

$$\sum_{i=0}^{+\infty}1-i![x^i]\sum_de^{\frac dSx}g_d(x)$$

交换求和顺序得

$$\sum_{i=0}^{+\infty}1-\sum_{d=0}^Si![x^i](e^{\frac dSx}g_d(x))=-\sum_{i=0}^{+\infty}\sum_{d=0}^{S-1}i![x^i](e^{\frac dSx}g_d(x))$$

因为 $g_S(x)=1$。

多一维枚举

$$-\sum_{i=0}^{+\infty}\sum_{d=0}^{S-1}i![x^i](e^{\frac dSx}g_d(x))=-\sum_{i=0}^{+\infty}\sum_{d=0}^{S-1}i!\sum_{k=0}^S\left([x^k]g_d(x)\times[x^{i-k}]e^{\frac dSx}\right)$$

将 $e^x$ 泰勒展开得

$$-\sum_{i=0}^{+\infty}\sum_{d=0}^{S-1}i!\sum_{k=0}^S\left([x^k]g_d(x)\frac{(\frac dS)^{i-k}}{(i-k)!}\right)=-\sum_{i=0}^{+\infty}\sum_{d=0}^{S-1}\sum_{k=0}^S\left([x^k]g_d(x)(\frac dS)^{i-k}i^{\underline k}\right)$$

设 $c=\frac dS$，更换求和顺序得

$$-\sum_{d=0}^{S-1}\sum_{k=0}^S\left([x^k]g_d(x)c^{-k}\sum_{i=0}^{+\infty}c^ii^{\underline k}\right)$$

如果我们能够对于每个 $k$ 求出 $\sum_{i=0}^{+\infty} c^ii^{\underline k}$，问题也就解决了。

#### 分部求和法（阿贝尔变换）

$$\sum_{k=m}^nf_k(g_{k+1}-g_{k})=f_{n+1}g_{n+1}-f_mg_m-\sum_{k=m}^ng_{k+1}(f_{k+1}-f_{k})$$

或是更为规整的形式：

$$\sum_{i=m+1}^n(b_i-b_{i-1})a_i+(a_i-a_{i-1})b_{i-1}=a_nb_n-a_mb_m$$

正确性显然。

设 $L_t(n)=\sum_{i=0}^nc^ii^{\underline t}$，$L_t=\lim_{n\to+\infty}L_t(n)$。

差分一下得

$L_t(n)=\frac{1-c^{n+1}}{1-c}(n+1)^{\underline t}-\sum_{i=0}^n\frac{1-c^{i+1}}{1-c}((i+1)^{\underline t}-i^{\underline t})$

使用分部求和法

$$L_t(n)=\frac{1-c^{n+1}}{1-c}(n+1)^{\underline t}-\frac{(n+1)^{\underline t}}{1-c}+\frac c{1-c}\sum_{i=0}^nc^iti^{\underline {t-1}}$$

此时开始求极限，根据简单的推导（比如洛必达法则），前两项极限为 $0$。

$$L_t=\frac c{1-c}t\sum_{i=0}^{+\infty}c^ii^{\underline {t-1}}=\frac c{1-c}tL_{t-1}$$

直接递推即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 405, p = 998244353;
int S;
long long fac[Maxn], finv[Maxn];
long long fast_pow(long long x, long long y)
{
	long long ans = 1, now = x;
	while (y)
	{
		if (y & 1) ans = ans * now % p;
		now = now * now % p;
		y >>= 1;
	}
	return ans;
}
void init(void)
{
	fac[0] = 1;
	for (int i = 1; i <= 400; i++)
		fac[i] = fac[i - 1] * i % p;
	finv[400] = fast_pow(fac[400], p - 2);
	for (int i = 399; i >= 0; i--)
		finv[i] = finv[i + 1] * (i + 1) % p;
}
void multi(long long x[], long long y[], long long ans[], int len)
{
	for (int i = 0; i <= S; i++)
		for (int j = 0; i + j <= S && j < len; j++)
			(ans[i + j] += p - x[i] * y[j] % p) %= p;
}
void add(long long x[], long long ans[])
{
	for (int i = 0; i <= S; i++)
		(ans[i] += x[i]) %= p;
}
int n, a[Maxn], b[Maxn];
long long ans, invS, f[Maxn][Maxn], g[Maxn][Maxn], tmp[Maxn];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i], &b[i]), S += a[i];
	init();
	invS = fast_pow(S, p - 2);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		memcpy(g, f, sizeof(g));
		memset(f, 0, sizeof(f));
		tmp[0] = 1;
		for (int j = 1; j < b[i]; j++)
			tmp[j] = tmp[j - 1] * a[i] % p * invS % p;
		for (int j = 1; j < b[i]; j++)
			tmp[j] = tmp[j] * finv[j] % p;
		for (int j = 0; j <= S - a[i]; j++)
		{
			multi(g[j], tmp, f[j], b[i]);
			add(g[j], f[j + a[i]]);
		}
	}
	for (int d = 0; d < S; d++)
	{
		long long c = d * invS % p, L = 1 * fast_pow(1 - c + p, p - 2);
		(ans += L * f[d][0]) %= p;
		for (int i = 1; i <= S; i++)
		{
			L = fast_pow(1 - c + p, p - 2) % p * i % p * L % p;
			(ans += L * f[d][i]) %= p;
		}
	}
	printf("%lld", (p - ans) % p);
	return 0;
}
```


---

## 作者：myee (赞：8)

### 前言

这里有个不用 min-max 反演的**爆标**做法。

其复杂度可以做到 $O(n^2\log n)$。（认为 $n\sim\sum A\sim\sum B$）

可以先去了解一下 [【ZJOI2019】开关](https://uoj.ac/problem/469) 的 GF 做法再来阅读此题解。

---
### 一个记号

为了避免歧义，先声明一下一个看上去有点古怪的记号。

设

$$f=\sum_kf_kz^k$$

则定义

$$\Xi f=\sum_kk!f_kz^k$$

直观看来就是给每个系数乘上了一个阶乘。

因此，这就是一个**从 EGF 转为 OGF 的记号**。

不难验证其对加法、数乘有线性。

---
### 初步思路

设 $P_i=\dfrac{A_i}S$。

考虑暴力枚举最后一步是什么数。

那么，除了当前数 $i$ 外，别的数 $j$ 都已经出现了至少 $B_j$ 次，而自己先前已经出现了恰 $B_i-1$ 次。

因此，考虑 EGF 组合意义，设：

$$f_i=\sum_{k\ge B_i}{P_i^kz^k\over k!}=e^{P_iz}-\sum_{k<B_i}{P_i^kz^k\over k!}$$

$$g_i={P_i^{B_i}z^{B_i-1}\over(B_i-1)!}$$

$$h=\sum_ig_i\sum_{j\neq i}f_j$$

则答案即

$$\sum_kk[{z^k\over k!}]h$$

或者改写成

$$(\Xi h)'(1)$$

（其实 $\Xi h$ 此处可以认为是转成了 PGF，然后这个柿子的正确性就不言而喻了）

---
容易发现 $h$ 即分式 $\sum\dfrac gf$ 的分子。

容易发现 $h$ 把乘法展开后每项均形如

$$C_{ab}z^ae^{\frac{bz}S}$$

**升一维！**

换元，设 $u=e^{\frac zS}$，则即

$$C_{ab}z^au^b$$

因此我们可以暴力模拟加入一个分式通分的过程，把 $h$ 的计算使用一个**二维背包**的 dp 在 $O(n^3)$（应该？）的时间内完成。


---
### 造福调试

以下是样例二的 $h$，可供调试使用。

$$-{{\left(u^3-2\right)\,z^3+\left(-u^5+9\,u^3+4\,u^2-24\right)\,z^2+ \left(-48\,u^4+48\,u^3+36\,u^2+120\,u-156\right)\,z-216\,u^3+216\,u^ 2+216\,u-216}\over{432}}$$

---
### 进一步推导

考虑怎么计算

$$(\Xi z^ae^{\frac{bz}S})'(1)$$

为了方便，以下解出

$$(\Xi z^ae^{bz})'(1)$$

的柿子，然后最后再把 $b$ 代为 $\frac bS$ 即可。

先摆结论：

$$\Xi z^ae^{bz}={a!z^a\over(1-bz)^{a+1}}$$

证明？

可以直接把系数展开；当然，也有更简洁（？）的推导，见文末。

然后就很简单了。

$$(\Xi z^ae^{bz})'=\bigg({a!z^a\over(1-bz)^{a+1}}\bigg)'={a!z^{a-1}(a+bz)\over(1-bz)^{a+2}}$$

$$(\Xi z^ae^{bz})'(1)={a!(a+b)\over(1-b)^{a+2}}$$

---
### 好了？

好，我们现在已经得到了一个 $O(n^3)$（应该？）的做法了。

但是这样还不够，我们可以来的**更给力**一点啊！

考虑瓶颈在分式基求和上。

回想是一维多项式时，我们可以在 $O(n\log^2n)$ 的时间内用分治卷积解决。

现在是二维多项式的分式基，我们依旧考虑分治卷积，只是单次乘法改用**二维 FFT**。

这样，我们就做到了 $O(n^2\log n)$ 的优秀复杂度！

于是，我们就**爆标**了。

---
### Laplace 变换

文末，我们给出 $\Xi z^ae^{bz}$ 的另一种推导方法。

大家都知道

$$a!=\int_0^{+\infty}t^ae^{-t}\operatorname dt$$

吧？

~~不知道也没有关系，现在不就知道了。~~

定义 Laplace 变换

$${\mathcal L}f(z)=\int_0^{+\infty}f(zt)e^{-t}\operatorname dt$$

容易验证有 $\Xi f={\mathcal L}f$。

于是 $f=z^ae^{bz}$ 时，

$${\mathcal L}f(z)=\int_0^{+\infty}f(zt)e^{-t}\operatorname dt\\=\int_0^{+\infty}(zt)^ae^{bzt}e^{-t}\operatorname dt\\=z^a\int_0^{+\infty}t^ae^{-t(1-bz)}\operatorname dt\\={z^a\over(1-bz)^{a+1}}\int_0^{+\infty}(t(1-bz))^ae^{-t(1-bz)}\operatorname d(t(1-bz))\\={a!z^a\over(1-bz)^{a+1}}$$

于是就得到

$$\Xi z^ae^{bz}={a!z^a\over(1-bz)^{a+1}}$$

这是一个令人满意的收尾。


---

## 作者：小粉兔 (赞：8)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC038E.html](https://www.cnblogs.com/PinkRabbit/p/AGC038E.html)。

### 题意简述

有 $N$ 个物品，给定 $A_0 \sim A_{N - 1}$ 和 $B_0 \sim B_{N - 1}$。

每一个单位时间你会获得一个物品，第 $i$ 个物品有 $\dfrac{A_i}{\sum_{j = 0}^{N - 1} A_j}$ 的概率获得。

计算第一次对于每个 $i$ 都有第 $i$ 个物品获得至少 $B_i$ 个的期望时间。

- $\displaystyle \sum_{i = 0}^{N - 1} A_i \le 400$
- $\displaystyle \sum_{i = 0}^{N - 1} B_i \le 400$。

### 题解

令 $\displaystyle \Sigma A = \sum_{i = 0}^{N - 1} A_i$ 以及 $\displaystyle \Sigma B = \sum_{i = 0}^{N - 1} (B_i - 1)$。

使用 Min-Max 容斥，转化为对于每个 $\{0, 1, \ldots , N - 1\}$ 的非空子集计算第一次子集中的任意一个物品获得至少 $B_i$ 个的期望时间，如果集合大小为奇数，则对答案贡献 $1$ 倍，否则贡献 $-1$ 倍。

也就是满足子集中的所有物品获得的数量都少于 $B_i$ 个的时间，加上 $1$。

如果我们把开始的没有任何物品的状态也算作一个时刻，那么 $+1$ 就省了。

现在考虑对于一个非空子集 $S \subseteq \{0, 1, \ldots , N - 1\}$ 计算子集中的所有物品获得的数量都少于 $B_i$ 个的时间（包括初始时刻）。

这也就是对于每一种物品获得的状态，计算这种状态在所有可能情况下出现的期望次数（包括初始时刻），再求和。

我们枚举每一种状态，用 $x$ 表示，其中 $x_i$ 表示 $i$ 获得的个数（$i \in S$），必须保证 $0 \le x_i < B_i$。

接下来需要计算这种状态在所有可能情况下出现的期望次数。

注意到一旦第一次变成了这种状态，只要再次获得 $S$ 中的物品，状态就会改变。

令 $P$ 为一次获得 $S$ 中的物品的概率，也就是 $\dfrac{\sum_{i \in S} A_i}{\Sigma A}$。可以发现一旦第一次变成这种状态之后，状态会期望持续 $1 / P$ 个时刻（包括第一次的时刻）。对于固定的 $S$，$P$ 都是不变的，所以只要求出每一种状态出现的概率再最后乘以 $1 / P$ 就行了。

考虑计算每一种状态出现的概率，这时就不需要考虑 $S$ 以外的物品的影响了，它们不会影响出现概率。

那么一种状态的概率就是存在一个获得 $S$ 中物品的前缀满足 $i$ 恰好出现了 $x_i$ 次。

令 $\displaystyle X = \sum_{i \in S} x_i$ 以及 $\displaystyle C = \sum_{i \in S} A_i$，则概率就是 $\displaystyle X! \prod_{i \in S} {\left( \frac{A_i}{C} \right)}^{x_i} \frac{1}{(x_i)!}$，这些阶乘来自于多重组合数。

利用乘法分配律，以 $X$ 为 DP 的状态进行转移，我们就可以对于所有可能的状态求出这个概率的和，转移其实类似于指数型生成函数的卷积。

而如果需要对所有的 $S$ 求和，也是类似的，需要注意处理一下容斥系数。然而对于不同的 $S$，$C$ 是不固定的，不过我们可以直接把 $C$ 提出来，也就是 $\displaystyle \frac{X!}{C^X} \prod_{i \in S} \frac{A_i^{x_i}}{(x_i)!}$，然后 DP 的时候记录 $X, C$ 两维状态即可。

这样依次加入 $N$ 个物品，每次加入的时间复杂度为 $\mathcal O (B_i X C)$ 进行暴力转移。

时间复杂度为 $\mathcal O({(\Sigma B)}^2 \Sigma A)$，[评测链接](https://atcoder.jp/contests/agc038/submissions/12873708)。

---

## 作者：littlez_meow (赞：5)

难得的 $\mathbf{\min-\max}$ 容斥题。

[题目指路](https://atcoder.jp/contests/agc038/tasks/agc038_e)。

### 题意

有一随机数生成器，每次生成 $[0,n-1]$ 的整数，生成 $i$ 的概率为 $\dfrac {a_i} A$，其中 $A=\sum\limits_{i=0}^{n-1}a_i$。当所有 $i\in[0,n-1]$ 都生成了至少 $b_i$ 次时，停止生成。求期望生成次数。

### 思路

题面里的所有都出现多少次很不好解决，考虑 $\min-\max$ 容斥，我们有下式：

**【$\mathbf{\min-\max}$ 容斥】** $E(\max S)=\sum\limits_{T\subseteq S}(-1)^{|T|-1}E(\min T)$。

则答案变成：

$$\sum\limits_{T\subseteq\{0,1,\cdots,n-1\}}(-1)^{|T|-1}E(T)$$

其中 $E(T)$ 表示 $T$ 中至少有一个元素 $i$ 生成不小于 $b_i$ 次的期望次数。但这还是不好算，还要再推一推。记 $t$ 为结束时间，把期望拆成概率，得到：

$$P(t=1)+2P(t=2)+3P(t=3)+\cdots$$

加法交换律一下：

$$(P(t=1)+P(t=2)+\cdots)+(P(t=2)+\cdots)+\cdots$$

整理：

$$P(t\ge1)+P(t\ge2)+\cdots$$

该式的实际意义为，第 $0$ 轮所有元素 $i$ 选到次数小于 $b_i$ 的概率，加第 $1$ 轮的概率，加第 $2$ 轮，一直加下去。

但是这个仅仅是在集合内选的期望。我们还要考虑随机生成到集合外。也就是说，上面这个式子还要再乘以随机生成到集合内的期望次数，即概率的倒数，才是 $E(T)$。设 $A=\sum\limits_{i=0}^{n-1}a_i,B=\sum\limits_{i=0}^{n-1}b_i$，则系数为 $\dfrac A{\sum\limits_{i\in T} a_i}$。

接下来计算第 $0$ 轮所有元素 $i$ 选到次数小于 $b_i$ 的概率，加第 $1$ 轮的概率，加第 $2$ 轮，一直加下去的值。我们考虑计算第 $k$ 轮的贡献。枚举每个数的出现次数 $c_0,c_1\cdots c_{n-1}$，满足 $\sum\limits_{i\in T} c_i=k,c_i<b_i$，则方案数为多重组合数，概率是生成每个数的概率乘在一起，贡献为二者相乘。即：

$$\left(\dfrac{k!}{\prod\limits_{i\in T}c_i!}\right)\left(\prod\limits_{i\in T}(\dfrac{a_i}{\sum\limits_{j\in T} a_j})^{c_i}\right)$$

整理得：

$$\dfrac{k!}{(\sum\limits_{j\in T} a_j)^k}\prod\limits_{i\in T}\dfrac{a_i^{c_i}}{c_i!}$$

最终答案为：

$$A\sum\limits_{T\subseteq\{0,1,\cdots,n-1\}}(-1)^{|T|-1}\sum\limits_{k}\dfrac{k!}{(\sum\limits_{i\in T} a_i)^{k+1}}\prod\limits_{i\in T}\dfrac{a_i^{c_i}}{c_i!}$$

设 $dp(i,j,k)$ 表示考虑到第 $i$ 个，所选的 $a_i$ 的和为 $j$，$c_i$ 的和为 $k$ 的贡献，做一遍带容斥系数的背包就好了。

具体地，转移为：

$$dp(i,j,k)=dp(i-1,j,k)-\sum\limits_{t=0}^{\min\{b_i-1,k\}}dp(i-1,j-a_i,k-t)\dfrac{a_i^t}{t!}$$

由于带容斥系数，初值 $dp(-1,0,0)=-1$，其余为 $0$。

最后答案为 $A\sum\limits_{j=0}^A\sum\limits_{k=0}^B\dfrac{dp(n,j,k)}{j^{k+1}}k!$

时间复杂度 $O(nAB)$，代码把下标平移到了 $1\sim n$。

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
using namespace std;
const int MOD=998244353,MAXN=401;
int n,a[MAXN],b[MAXN],A,B;
int fact[MAXN],invf[MAXN],inv[MAXN];
int po[MAXN][MAXN+10];
int dp[2][MAXN][MAXN];
inline ll qpow(ll base,int expo){
	ll res(1);
	while(expo){
		(expo&1)&&(res=res*base%MOD);
		base=base*base%MOD,expo>>=1;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	fact[0]=fact[1]=invf[0]=invf[1]=inv[1]=1;
	F(i,2,400) inv[i]=MOD-MOD/i*1ll*inv[MOD%i]%MOD,fact[i]=fact[i-1]*1ll*i%MOD,invf[i]=invf[i-1]*1ll*inv[i]%MOD;
	F(i,1,400){
		po[i][0]=1;
		F(j,1,410) po[i][j]=po[i][j-1]*1ll*i%MOD;
	}
	cin>>n;
	F(i,1,n) cin>>a[i]>>b[i],A+=a[i],B+=b[i];
	dp[0][0][0]=MOD-1;
	F(i,1,n){
		int now(i&1),pre(now^1);
		F(j,0,A) F(k,0,B){
			int&qwq(dp[now][j][k]);
			qwq=dp[pre][j][k];
			if(j<a[i]) continue;
			F(t,0,min(b[i]-1,k)) qwq=(qwq-dp[pre][j-a[i]][k-t]*1ll*po[a[i]][t]%MOD*invf[t])%MOD+MOD;
		}
	}
	int ans(0);
	F(i,0,A) F(j,0,B) ans=(ans+dp[n&1][i][j]*qpow(inv[i],j+1)%MOD*fact[j])%MOD;
	cout<<(ans+MOD)*1ll*A%MOD;
	return 0;
} 
```

---

## 作者：justin_cao (赞：4)

可以发现，题目要求的实际上就是最大的取到$B_i$个数的期望时间，考虑min_max容斥：
$$E(max(S))=\sum_{T\in S}(-1)^{|T|+1}E(min(T))$$
那么问题就转化为了求每个集合中取到$B_i$个数的最小期望时间。

先考虑假设我们已经知道了这个集合，应该怎么求。

假设我们已经知道的集合是$T=\{x_1,x_2,\dots x_m\}$。

考虑暴力枚举：
$$E=(-1)^{m+1}\times \frac{S}{\sum A[x_i]}\times\sum_{c_i=0}^{B[x_i]-1}\frac{(\sum c_i)!}{\prod c_i!}\times\prod(\frac{A[x_i]}{\sum A[x_i]})^{c_i}$$
其中$(-1)^{m+1}$是容斥系数，而$\frac{S}{\sum A[x_i]}$是期望选多少个数才会选到这个集合里一次。

那么这样就可以算出来了。

但是我们不可能枚举所有的集合，于是考虑在转移的过程中（加入一个数），哪些量会改变。

可以发现会改变的量是$\sum A[x_i]$与$\sum c_i$。

于是可以考虑设$f[i][j][k]$表示前$i$个数，$\sum A[x_i]=j,\sum c_i=k$的时候，式子里与这两个量无关的值的和。

再转化一下式子，可以发现，这个值实际上就是：
$$(-1)^{m+1}\sum_{c_i=0}^{B[x_i]-1}\frac{A[x_i]^{c_i}}{\prod c_i!}$$
转移的时候枚举一下当前这个数选多少个即可。

dp完了之后，答案就可以直接带进去求了：
$$ans=\sum_{i=1}^{S}\sum_{j=0}^{sum_B}f[n][i][j]\times\frac{S}{i}\times \frac{j!}{i^j}=\sum_{i=1}^{S}\sum_{j=0}^{sum_B}f[n][i][j]\times \frac{S\times j!}{i^{j+1}}$$
这样就做完了。

复杂度$O((\sum B_i)^2\times S)$。

code:
```cpp
#include<bits/stdc++.h>
#define maxn 405
#define mod 998244353
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,sa,sb;
int a[maxn],b[maxn];
int f[maxn][maxn][maxn];
int fac[maxn],inv[maxn];
int quick_pow(int x,int p)
{
    int an=1,po=x;
    while(p)
    {
        if(p&1)  an=1ll*an*po%mod;
        po=1ll*po*po%mod;
        p>>=1;
    }
    return an;
}
void add(int &x,int y)
{
    x=(x+y>=mod)?(x+y-mod):x+y;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)  a[i]=read(),b[i]=read(),sa+=a[i],sb+=b[i];
    fac[0]=1;for(int i=1;i<=400;i++)  fac[i]=1ll*fac[i-1]*i%mod;
    inv[400]=quick_pow(fac[400],mod-2);
    for(int i=399;i>=0;i--)  inv[i]=1ll*inv[i+1]*(i+1)%mod;
    f[0][0][0]=mod-1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=sa;j++)
        {
            for(int k=0;k<=sb;k++)
            {
                if(!f[i-1][j][k])  continue;
                add(f[i][j][k],f[i-1][j][k]);
                int x=1;
                for(int l=0;l<b[i];l++,x=1ll*x*a[i]%mod) add(f[i][j+a[i]][k+l],mod-1ll*x*inv[l]%mod*f[i-1][j][k]%mod);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=sa;i++)
    {
        int y=quick_pow(i,mod-2);
        int x=1ll*sa*y%mod;
        for(int j=0;j<=sb;j++,x=1ll*x*y%mod)  add(ans,1ll*x*fac[j]%mod*f[n][i][j]%mod);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

切了很开心。一看就要 $\rm Min-Max$ 容斥。具体的，设每个点到达 $B_i$ 的时刻是 $t_i$，则停时为 $\max_{1 \le i \le n} t_i$。显然转化为：$\sum_{S \subseteq \{1,2,\cdots,n\}} (-1)^{|S|-1} \min_{i \in S} t_i$。

所以考虑计算 $E(\min_{i \in S} t_i)$。

我们先计算出 $E'(\min_{i \in S} t_i)$ 表示，如果只保留在 $S$ 中的物品、出现满足限制的物品需要的期望操作次数。

而设 $p_0 = \sum_{i \notin S} p_i$，即实际上每次操作有 $p_0$ 的概率选到不在 $S$ 中的物品。

感性理解一下，别的事情发生的次数应该是原本次数的 $\dfrac{p_0}{1-p_0}$ 倍。（严谨证明也不难的。如果一件事情发生的概率为 $p$，则期望 $\dfrac{1}{p}$ 次会发生一次。把 $E'$ 中的每种操作隔离开，不难发现之间的影响是线性的，可以直接利用线性性组合起来。）

而自然数变量的期望可以使用贡献法拆开：

$$
E(X) = \sum_{i=1} P(i \le X)
$$

所以转化为计算 $P(x \le \min_{i \in S} t_i-1)$。（求和之后还要加一。这里的概率指的仍然是只考虑 $S$ 中的元素的概率）

减一之后就相当于，$S$ 中每个物品可以选 $0$ 到 $b_i-1$ 个，选出 $x$ 个的概率（由于有顺序，所以还要用多重组合数，也就是一些阶乘乘来乘去。这一部分不是很重要，略过。）

于是就是简单的背包问题了。设 $dp_{i,j,k}$ 为，选择了前 $i$ 的一个子集为 $S$，$\sum_S A = j$，$\sum_S B = k$，你计算的贡献的总和（事实上，不同人的实现也不太相同，但是这种方法的 $dp$ 式子应该没啥区别）

直接转移即可。复杂度为：

1. 每一轮你会对 $k$ 做 $O(B)$ 的增量，所以增量的总次数为 $O(\sum B)$。
2. 每增量一次，都需要 $O(\sum A \sum B)$ 次遍历。

所以复杂度是 $O((\sum B)^2(\sum A))$。

我自己在做题的时候，发现**认知哪些过程是随机的，哪些变量在容斥的过程中已经无关了**这件事情非常重要。

这是代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=400+10,MOD=998244353;
int n,ans,frac[MAXN],inv[MAXN],a[MAXN],b[MAXN],dp[MAXN][MAXN][MAXN],sa,sb,pw[MAXN];
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
	frac[0]=1; ffor(i,1,400) frac[i]=frac[i-1]*i%MOD;
	inv[400]=qpow(frac[400],MOD-2); roff(i,399,0) inv[i]=inv[i+1]*(i+1)%MOD;
	
	cin>>n;
	ffor(i,1,n) cin>>a[i]>>b[i];
	dp[0][0][0]=-1;
	ffor(i,1,n) {
		pw[0]=1;
		ffor(j,1,b[i]-1) pw[j]=pw[j-1]*a[i]%MOD;
		ffor(oa,0,sa+a[i]) ffor(ob,0,sb+b[i]) {
			dp[i][oa][ob]=dp[i-1][oa][ob];
			if(oa>=a[i]) ffor(j,0,min(b[i]-1,ob)) dp[i][oa][ob]=(dp[i][oa][ob]-dp[i-1][oa-a[i]][ob-j]*inv[j]%MOD*pw[j])%MOD;
		}
		sa+=a[i],sb+=b[i];
	}
	pw[0]=1; ffor(i,1,sb) pw[i]=pw[i-1]*sa%MOD;
	ffor(i,0,sb) pw[i]=qpow(pw[i],MOD-2);
	ffor(i,0,sa) ffor(j,0,sb) {
		int mul=sa*qpow(i,MOD-2)%MOD;
		ans=(ans+dp[n][i][j]*mul%MOD*frac[j]%MOD*qpow(qpow(i,j),MOD-2))%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：yshpdyt (赞：3)

## 题意
一个随机数生成器，生成 $[1,n]$ 之间的整数，其中生成 $i$ 的概率为 $\frac{A_i}{\sum A_i}$。

当 $\forall i\in[1,n]$，$i$ 至少出现了 $B_i$ 次时，停止生成，否则继续生成。

求期望生成随机数的次数，输出答案对 $998244353$ 取模的结果。

$a_i,b_i\geq 1$，$\sum a_i,\sum b_i,n\leq 400$。
## Sol
$\text{min-max}$ 容斥，考虑如下式子：

$$ E(\max U)=\sum\limits_{S\subseteq U}(-1)^{|S|+1}E(\min S) $$

$E(\min S)$ 表示 $S$ 集合内至少有一个元素生成规定次数的期望时间，求出这个即可求出答案。

令 $ A=\sum\limits_{i=1}^n a_i,A_S=\sum\limits_{i\in S}a_i$，选到 $S$ 集合内的元素的期望次数是 $\frac{A}{A_S}$，于是我们可以认为每 $\frac{A}{A_S}$ 次让 $S$ 集合内的某个元素增加，现在只需要考虑集合内的元素即可。

$E(\min S)$ 不好算，考虑拆成概率，设 $P(X=i)$ 表示进行了 $i$ 次集合内操作后，**恰好有一个位置刚好达到目标**的概率：
 
$$ E(\min S)=\frac{A}{A_S}\sum\limits_{i=1}^{\infty} iP(X=i)=\frac{A}{A_S}\sum\limits_{i=1}^{\infty}\sum\limits_{j=i}^{\infty} P(X=j)=\frac{A}{A_S}\sum\limits_{i=1}^{\infty} P(X\ge i)$$

考虑 $P(X\ge i)$ 的实际意义：至少 $i$ 次集合内操作后，恰好有一个位置刚好达到目标的概率，等价于 **$i-1$ 次集合内操作时没有一个位置实现目标的概率**。

设 $x_i$  满足 $i\in S,x_i\in[0,b_i)$，表示当前目标加了几次，则有 $X=\sum\limits_{i\in S}x_i$，我们需要计算的就是 $X$ 次集合内操作后，$i$ 位置上为 $\{x_i\}$ 的概率，设其为 $P(x_i)$。

$$ P(x_i)=\prod_{i\in S}\left(\frac{a_i}{A_S}\right)^{x_i} \frac{X!}{x_i}$$

实际意义：选到 $x_i$ 次 $i$ 位置，并对其进行多重集的排序。

于是我们可以得到：

$$ E(\min S)=\frac{A}{A_S}X!\sum\limits_{i\in S,x_i\in[0,b_i)} \prod\limits_{i\in S}\left(\frac{a_i}{A_S}\right)^{x_i}\frac{1}{x_i!}$$


于是有：
$$\begin{align*}
 E(\max U)&=\sum\limits_{S\subseteq U} \frac{A}{A_S} (-1)^{|S|+1}X!\sum\limits_{i\in S,x_i\in[0,b_i)} \prod\limits_{i\in S}\left(\frac{a_i}{A_S}\right)^{x_i}\frac{1}{x_i!}\\
&=A\sum\limits_{S\subseteq U} (-1)^{|S|+1}\frac{X!}{(A_S)^{X+1}} \sum\limits_{i\in S,x_i\in[0,b_i)} \prod\limits_{i\in S}\frac{a_i^{x_i}}{x_i!}\\
&=A\sum\limits_{S\subseteq U} (-1)\frac{X!}{(A_S)^{X+1}} \sum\limits_{i\in S,x_i\in[0,b_i)}\prod\limits_{i\in S}(-1)\times \frac{a_i^{x_i}}{x_i!}
\end{align*}$$

考虑计算右边那坨东西，设 $f[i][j][k]$ 表示考虑由前 $i$ 个元素，当前集合的 $A_S=j,X=k$ 的对答案贡献和。

初始化 $f[0][0][0]=1$。


如果 $i$ 不选：
$$ f[i+1][j+a_{i+1}][k+d]=f[i+1][j+a_{i+1}][k+d]+f[i][j][k]$$
如果 $i$ 选，需要满足 $d< b_{i+1}$：
$$ f[i+1][j+a_{i+1}][k+d]=f[i+1][j+a_{i+1}][k+d]-(a_{i+1} )^d\times\frac{1}{d!}\times f[i][j][k]$$

答案为:
$$ E(\max U)=A\sum\limits_{i=1}^A \sum\limits_{j=1}^B (-1)\frac{j!}{i^{j+1}}f[n][i][j]$$

时间复杂度 $O(nAB)$。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 405
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6;
ll n,a[N],b[N];

ll f[N][N][N];
namespace math_permutation{
    ll fpow(ll x,ll y){
        ll res=1;
        while(y){
            if(y&1)res=res*x%mod;
            y>>=1,x=x*x%mod;
        }
        return res;
    }
    ll fac[N],ifac[N],inv[N];
    void work(ll r){
        fac[0]=inv[1]=1;
        for(int i=1;i<=r;i++)fac[i]=fac[i-1]*i%mod;
        ifac[r]=fpow(fac[r],mod-2);
        for(int i=r;i>0;i--){
            ifac[i-1]=ifac[i]*i%mod;
            inv[i]=fac[i-1]*ifac[i]%mod;
        }
    }
    ll C(ll n,ll m){
        if(n<0||n<m)return 0;
        return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
    }
    void add(ll &x,ll y){
        x%=mod,y%=mod;
        x=(x+y+mod)%mod;
    }
}using namespace math_permutation;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n;
    work(400);
    f[0][0][0]=1;
    ll A=0,B=0;
    for(int i=0,a,b;i<n;i++){
        cin>>a>>b;
        for(int j=0;j<=A;j++){
            for(int k=0;k<=B;k++){
                if(f[i][j][k]==0)continue;
                add(f[i+1][j][k],f[i][j][k]);
                for(int d=0;d<b;d++){
                    add(f[i+1][j+a][k+d],-1*ifac[d]*fpow(a,d)%mod*f[i][j][k]%mod);
                }
            }
        }
        A+=a,B+=b;
    }
    ll res=0;
    for(int i=0;i<=A;i++){
        for(int j=0;j<=B;j++){
            ll p=fpow(i,j+1);
            add(res,-fac[j]*fpow(p,mod-2)%mod*f[n][i][j]%mod);
        }
    }
    res=res*A%mod;
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：zifanwang (赞：3)

比较基础的一道题。很容易想到 Min-Max 容斥：

$$E(\max(S))=\sum_{T\sube S}(-1)^{|T|-1}\times E(\min(T))$$

然后发现 $E(\min(T))=\sum_{k\ge 0}P(\min(T)\ge k)$。考虑 dp，记 $f_{i,j,k}$ 表示从前 $i$ 个数中选出 $T$，$\sum_{i\in T}A_i=j,\sum_{i\in T}c_i=k$ 且每个数都还没被选过 $B_i$ 次，到达这个状态的概率（$c_i$ 表示第 $i$ 个数选了多少次）。发现每次选出一个数的概率不好直接求得，可以先乘上对应的 $A$ 值最后再除以一个东西。

转移时直接枚举当前数 $i$ 选了 $x$ 个，$f_{i-1,j-a_i,k-x}$ 乘上系数 ${k\choose x}\times A_i^x$ 求和即可。

最后再考虑一个状态 $f_{n,i,j}$ 对答案的贡献是什么。发现每次都有 $\frac{S-i}S$ 的概率选中集合外的一个数，所以对于每一步的贡献还要加上 $\frac{S-i}i$。那么每一步的贡献就是 $\frac S i$，所以最终答案就是 $\sum S\times i^{j+1}\times f_{n,i,j}$。时间复杂度 $\mathcal O(\sum A_i(\sum B_i)^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define md 998244353
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int n,s1,s2,a[403],b[403],c[403][403];
ll ans,p[403][403],dp[403][403][403];
ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
signed main(){
	cin>>n;
	rep(i,1,n)cin>>a[i]>>b[i];
	c[0][0]=1;
	rep(i,1,400){
		p[i][0]=c[i][0]=1;
		rep(j,1,401){
			p[i][j]=p[i][j-1]*i%md;
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%md;
		}
	}
	dp[0][0][0]=-1;
	rep(i,1,n){
		s1+=a[i],s2+=b[i]-1;
		rep(j,0,s1){
			rep(k,0,s2){
				dp[i][j][k]=dp[i-1][j][k];
				if(j>=a[i])rep(x,0,min(k,b[i]-1)){
					dp[i][j][k]=(dp[i][j][k]-dp[i-1][j-a[i]][k-x]*p[a[i]][x]%md*c[k][x])%md;
				} 
			}
		}
	}
	rep(i,1,s1)rep(j,0,s2){
		ans=(ans+s1*dp[n][i][j]%md*power(p[i][j+1],md-2))%md;
	}
	cout<<(ans+md)%md;
	return 0;
}
```

---

## 作者：xht (赞：3)

## Gachapon

### 题意

- 有一个随机数生成器，每次可以有 $\frac {a_i}{\sum_{i=0}^{n-1}a_i}$ 的概率生成 $i$。
- 求对于每个 $i$，都有 $i$ 被生成了至少 $b_i$ 次的期望时间。
- $n, \sum_{i=0}^{n-1} a_i, \sum_{i=0}^{n-1} b_i\le 400$，答案对 $998244353$ 取模。

### 题解

设 $\max(S)$ 表示 $S$ 中的元素被生成到规定次数的最大时间，即所有元素都被生成到规定次数的期望时间，则
$$
ans = E(\max(U))
$$
其中 $U$ 是全集，$E$ 表示期望。

根据 Min-Max 容斥，设 $\min(S)$ 表示 $S$ 中的元素被生成到规定次数的最小时间，即至少一个元素被生成到规定次数的期望时间，有
$$
ans = \sum_{S \subseteq U} (-1)^{|S|+1} E(\min(S))
$$
考虑如何计算 $E(\min(S))$，有
$$
E(\min(S)) = \sum_{i \in S, 0 \le x_i < b_i} P(x_i)E(x_i)
$$
其中 $P(x_i)$ 表示状态 $x_i$ 的出现概率，$E(x_i)$ 表示状态 $x_i$ 的期望持续时间。

显然当 $S$ 相同时 $E(x_i)$ 都一样
$$
E(x_i) = \frac A{A_S}
$$
为了方便，不妨认为 $a,b$ 的下标从 $1$ 开始，于是其中的 $A = \sum_{i=1}^{n} a_i$，$A_S = \sum_{i \in S} a_i$。

考虑如何求 $P(x_i)$，即要求 $i \in S$ 的 $i$ 恰好出现 $x_i$ 次的概率，此时不再需要考虑 $U - S$ 中的元素。

设 $X = \sum_{i \in S}x_i$，此时为有标号概率（设 $i,j \in S$，先 $i$ 后 $j$ 和先 $j$ 后 $i$ 是两种情况），因此考虑 EGF，对于 $i$ 的 EGF 为
$$
f_i(x) = \sum_{n \ge 0} \left(\frac {a_i}{A_S}\right)^n \frac{x^n}{n!}
$$
所以
$$
P(x_i) = X! \prod_{i \in S} \left(\frac {a_i}{A_S}\right)^{x_i}\frac 1{x_i!}
$$
整理一下，我们要算的就是这个玩意儿
$$
\begin{aligned}
ans &= E(\max(U)) \\\\
&= \sum_{S \subseteq U} (-1)^{|S|+1} E(\min(S)) \\\\
&= \sum_{S \subseteq U} (-1)^{|S|+1} \left(\sum_{i \in S, 0 \le x_i < b_i} P(x_i)E(x_i)\right) \\\\
&= \sum_{S \subseteq U} (-1)^{|S|+1} \frac A{A_S}\sum_{i \in S, 0 \le x_i < b_i} P(x_i) \\\\
&= \sum_{S \subseteq U} (-1)^{|S|+1} \frac A{A_S}\sum_{i \in S, 0 \le x_i < b_i} X! \prod_{i \in S} \left(\frac {a_i}{A_S}\right)^{x_i}\frac 1{x_i!} \\\\
&= A\sum_{S \subseteq U} \sum_{i \in S, 0 \le x_i < b_i}(-1)^{|S|+1} \frac {X!}{A_S^{X+1}} \prod_{i \in S} \frac {a_i^{x_i}}{x_i!} \\\\
\end{aligned}
$$
考虑一下 $\sum_{S \subseteq U} \sum_{i \in S, 0 \le x_i < b_i}$ 本质上枚举了啥。

其实就是对于每个 $i$，都可以选或者不选，如果选还要考虑选多少个。

于是显然 DP，状态中需要记录 $A_S$ 和 $X$ 的值，因此设 $f_{i,j,k}$ 表示考虑了前 $i$ 个数，$A_S = j$，$X = k$ 的贡献之和。

初始状态为 $f_{0,0,0} = -1$。

转移为
$$
f_{i+1,j,k} \leftarrow f_{i,j,k} \\\\
f_{i+1,j+a_{i+1},k+l} \leftarrow -(\frac{a_{i+1}^{l}}{l!}f_{i,j,k})(l < b_{i+1})
$$
目标为
$$
ans = A\sum_{j=1}^{A}\sum_{k=0}^B \frac{k!}{j^{k+1}}f_{n,j,k}
$$
其中 $B = \sum_{i=1}^{n}b_i$。

注意到转移类似一个背包，因此倒序枚举 $j$ 可以省掉 $i$ 这一维。

总时间复杂度 $\mathcal O(AB^2)$。

### 代码

```cpp
const int N = 407;
int n, a, b, A, B;
modint f[N][N], ans;

int main() {
	init(400);
	rd(n);
	f[0][0] = P - 1;
	for (int i = 0; i < n; i++) {
		rd(a, b);
		for (int j = A; ~j; j--)
			for (int k = B; ~k; k--)
				if (f[j][k].x) {
					modint o = 1;
					for (int l = 0; l < b; l++, o *= a)
						f[j+a][k+l] -= o * vp[l] * f[j][k];
				}
		A += a, B += b;
	}
	for (int j = 1; j <= A; j++) {
		modint o = v[j];
		for (int k = 0; k <= B; k++, o *= v[j])
			if (f[j][k].x)
				ans += p[k] * o * f[j][k];
	}
	print(ans * A);
	return 0;
}
```

---

## 作者：lhm_ (赞：3)

发现题目所求即为最晚达到出现次数的整数的期望次数，考虑 $\text{min-max}$ 容斥，将其转化为最早达到出现次数的整数的期望次数：
$$
\large E(\max(S) )=\sum_{T\subseteq S}(-1)^{|T|+1}E(\min(T))
$$
设集合 $T=\{ x_1,x_2,\dots,x_m \}$，考虑如何计算该集合的贡献，因为期望的线性性，所以直接求和所有未达到出现次数的状态的期望次数即可，得：
$$
\large\begin{aligned}

&(-1)^{|T|+1}E(\min(T)) \\

=&(-1)^{m+1}\sum_{i \geqslant 0} \left( \frac{s-\sum a_{x_i}}{s} \right)^i\sum_{0 \leqslant c_i < b_{x_i}} \frac{(\sum c_i)!}{\prod(c_i!)}\prod\left( \frac{a_{x_i}}{\sum a_{x_i}} \right)^{c_i} \\

=&(-1)^{m+1}\frac{s}{\sum a_{x_i}}\sum_{0 \leqslant c_i < b_{x_i}} \frac{(\sum c_i)!}{\prod(c_i!)}\prod\left( \frac{a_{x_i}}{\sum a_{x_i}} \right)^{c_i} \\

\end{aligned}
$$
第一项为容斥系数，第二项为随机到该集合元素的期望次数，第三项是可重集排列，因为整数的出现顺序需要考虑，第四项为集合内每个整数随机到的概率。

发现式子主要和 $\sum a_{x_i},\sum c_i$ 有关，可以考虑 $DP$ 来进行计算。设 $f_{i,j,k}$ 为考虑了前 $i$ 个数，$\sum a_{x_i}$ 为 $j$，$\sum c_i$ 为 $k$ 的所有集合按上面式子去掉与 $\sum a_{x_i},\sum c_i$ 有关的项的乘积之和。

转移为考虑是否加入第 $i$ 个数，加入就考虑第 $i$ 个数和其出现次数对式子的贡献。最后枚举 $\sum a_{x_i},\sum c_i$ 即可计算答案。

```cpp
#include<bits/stdc++.h>
#define maxn 410
#define all 400
#define p 998244353
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,s1,s2;
ll ans;
int a[maxn],b[maxn];
ll f[maxn][maxn][maxn],inv[maxn];
void init()
{
    inv[0]=inv[1]=1;
    for(int i=2;i<=all;++i) inv[i]=(p-p/i)*inv[p%i]%p;
}
int main()
{
    init(),read(n);
    for(int i=1;i<=n;++i)
        read(a[i]),read(b[i]),s1+=a[i],s2+=b[i];
    f[0][0][0]=p-1;
    for(int i=1;i<=n;++i)
    {
        ll v=1;
        for(int j=0;j<=s1;++j)
            for(int k=0;k<=s2;++k)
                f[i][j][k]=f[i-1][j][k];
        for(int t=0;t<b[i];++t,v=v*a[i]%p*inv[t]%p)
            for(int j=a[i];j<=s1;++j)
                for(int k=t;k<=s2;++k)
                    f[i][j][k]=(f[i][j][k]-f[i-1][j-a[i]][k-t]*v%p+p)%p;
    }
    for(int j=1;j<=s1;++j)
    {
        ll v=1;
        for(int k=0;k<=s2;++k,v=v*k%p*inv[j]%p)
            ans=(ans+f[n][j][k]*s1%p*inv[j]%p*v%p)%p;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：lalaouye (赞：2)

感觉这题是套路堆砌，但是还是很有价值的，尤其是对于我这种不太会计数的人来说。

首先考虑 min-max 容斥，我也只能想到这了，我难以想象这是能做的，因为涉及到子集，但是它真的能做。我们可以先利用 min-max 容斥再推式子优化成类似背包什么的的形式。

那么这题我们相当于要求 $\sum_T (-1)^{|T|-1}E(\min(T))$。现在考虑计算 $E(\min(T))$。首先对于一个集合我们需要让操作保证在集合内，然而我们期望需要 $\frac S {\sum_{i\in T} A_i}$ 步才能够操作到 $T$ 之内的数，设其为 $E_0$。那么现在我们只需要对集合内算期望的操作次数即可。我们发现这是 $\sum_k kP_0(k)$ 的形式，$P_0(k)$ 表示 $k$ 轮恰好结束的概率。拆开 $k$ 推推性质就不难发现我们可以转化为 $\sum_{k=0} P_1(k)$，$P_1(k)$ 则表示为 $k$ 轮后仍未结束的概率，那么最后只需要算 $\sum_{k=0}E_0P_1(k)$ 即可。

我们发现 $P_1(k)$ 其实不难算，我们可以写出他的式子：

$$P_1(k)=\sum_{\sum c_i=k}\prod_i(\frac {A_i}{\sum_{i\in T} A_i})^{c_i}\times\frac{k!}{\prod_i c_i!}$$

式子是好理解的，相当于枚举每个数被取了多少次，乘上概率再确定顺序。然后不难发现每个数的贡献几乎独立，把式子放到原式上我们发现这个东西很好 dp，考虑设 $f(i,j,k)$ 表示考虑完前 $i$ 个数，总共取了 $j$ 次，$\sum_{i\in T}A_i$ 为 $k$ 的总贡献，然后最后把 $f(n,j,k)$ 乘上 $j!(\frac{1}{k})^{j+1}S$ 即可。

代码：


```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define rep(i, l, r) for (int i (l); i <= r; ++ i)
#define rrp(i, l, r) for (int i (r); i >= l; -- i)
#define eb emplace_back
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
#define pii pair <int, int>
#define inf 1000000000
#define ls (p << 1)
#define rs (ls | 1)
constexpr int N = 400 + 5, M = 1e5 + 5, P = 998244353;
typedef long long ll;
typedef unsigned long long ull;
inline __int128_t rd () {
  __int128_t x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret (1);
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int n;
int A[N], B[N];
int f[N][N];
int fac[N], ifac[N];
int pw[N][N];
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd ();
  fac[0] = 1;
  rep (i, 1, N - 1) fac[i] = fac[i - 1] * i % P;
  ifac[N - 1] = qpow (fac[N - 1], P - 2);
  rrp (i, 1, N - 1) ifac[i - 1] = ifac[i] * i % P;
  int S (0);
  rep (i, 1, n) A[i] = rd (), B[i] = rd (), S += A[i]; S %= P;
  rep (i, 1, n) {
    pw[i][0] = 1;
    rep (j, 1, 400) pw[i][j] = pw[i][j - 1] * A[i] % P;
  }
  f[0][0] = P - 1;
  rep (i, 1, n) {
    rrp (j, 0, 400) {
      rrp (k, A[i], 400) {
        rrp (l, 0, min (j, B[i] - 1)) {
          (f[j][k] += (P - f[j - l][k - A[i]]) * pw[i][l] % P * ifac[l]) %= P;
        }
      }
    }
  }
  int ans (0);
  rep (j, 0, 400) rep (k, 0, 400) (ans += f[j][k] * fac[j] % P * qpow (k, (j + 1) * (P - 2)) % P * S) %= P;
  cout << ans;
} 
```

---

## 作者：yyyyxh (赞：2)

好像我的切入点比较奇怪？根本想不到最大众的 $\min-\max$ 容斥做法，那么讲讲 PGF + 直接容斥做法吧！

题意：不断按照一个给定的分布的生成一个随机数 $x$，然后让对应的计数器 $C_x$ 加一，问期望生成多少个随机数时第一次满足所有的 $C_i\geq B_i$。

首先我们设概率生成函数 $F$ 表示进行 $i$ 轮操作后所有计数器 $C_i$ 都满足 $C_i\geq B_i$ 的概率。注意不是第一次满足的概率。

这个概率生成函数似乎比较难有一个封闭形式，因为满足 $C_i\geq B_i$ 的 $C_i$ 是无限的无法枚举。

那么考虑一个套路：直接上普通容斥！接下来我们用一个由 $\geq,<,-$ 字符串来表示 $C_i$ 与 $B_i$ 之间的关系是大于等于/小于/没有限制。

我们发现，题目中要求的 $F$ 就是 $F_{\geq \geq \geq \dots \geq}$，而我们后面会看到好求的 $F$ 都是只有 $<$ 和 $-$ 的形式。考虑逐个将 $F$ 容斥成后者的形式，我们就可以发现 容斥系数正好就是 $<$ 号的个数。

于是我们转而去考虑这样一个问题：强制计数器的若干个位置小于一个给定值，那么它的 PGF 是什么。$<B_i$ 的位置是有限的，设这些位置组成的集合是 $S$，所以我们暴力枚举这些位置的 $C_i$，然后用一个多重组合数计算它们拼成一个长度为 $\sum_{i\in S} C_i$ 的序列的方案数，也就是 $\frac{(\sum_{i\in S} C_i)!}{\prod_{i\in S} C_i!}$。

记 $a=\sum_{i\in S} C_i$，我们再考虑怎么算 PGF。设生成一个 $\in S$ 的随机数的概率是 $p$，我们枚举 $\notin S$ 的数的出现次数 $t$，然后把这些数插入到刚才钦定的序列，有:

$$
\begin{aligned}
F_S&=\sum_{\text{enumerate } C_i<B_i} \frac{a!}{\prod_{i\in S} C_i!} \prod_{i\in S} (\frac{A_i}{\sum_i A_i})^{C_i}\sum_{t\geq 0} {a+t \choose a} (1-p)^t x^{t+a}\\
&=\sum_{\text{enumerate } C_i<B_i} \frac{a!}{\prod_{i\in S} C_i!}\prod_{i\in S} (\frac{A_i}{\sum_i A_i})^{C_i}\frac{x^a}{[1-(1-p)x]^{a+1}}
\end{aligned}
$$

那么 $F=\sum_S (-1)^{|S|}F_S$。现在，如果只是单纯算下不只是第一次出现的期望，那么直接算 $F'(1)$ 就可以了。然后考虑如何处理“第一次”这个条件：我们直接差分，乘上 $(1-x)$ 就可以了！因为 $[x^i]F$ 也可以看成是第一次满足的时间 $\leq i$ 的概率。

于是我们要求的就是 $\frac{x^a(1-x)}{[1-(1-p)x]^{a+1}}$ 的导数在 $x=1$ 处的取值，用商的求导法则计算得到是 $-p^{-a-1}$([Wolfram](https://www.wolframalpha.com/input?i2d=true&i=derivative+of+Divide%5BPower%5Bx%2Ca%5D%5C%2840%291-x%5C%2841%29%2CPower%5B1-%5C%2840%291-p%5C%2841%29x%2Ca%2B1%5D%5D+with+respect+to+x+where+x%3D1))。

于是我们把 $A_i,C_i$ 当作体积直接背包出 $p,a$，中途乘上一些相关贡献，由于 $\sum B_i$ 不大，复杂度 $O(\sum A_i (\sum B_i)^2)$。

```cpp
#include <cstdio>
using namespace std;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=(x<<1)+(x<<3)+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=403,P=998244353;
typedef long long ll;
int n,sum,num,iv;
int f[N][N],a[N],b[N];
int qp(int a,int b=P-2){
	int res=1;
	while(b){
		if(b&1) res=(ll)res*a%P;
		a=(ll)a*a%P;b>>=1;
	}
	return res;
}
int fac[N],fiv[N];
void init(int lim){
	fac[0]=1;
	for(int i=1;i<=lim;++i) fac[i]=(ll)fac[i-1]*i%P;
	fiv[lim]=qp(fac[lim]);
	for(int i=lim;~i;--i) fiv[i-1]=(ll)fiv[i]*i%P;
}
void dec(int &x,int v){if((x-=v)<0) x+=P;}
int main(){
	n=read();f[0][0]=P-1;init(400);
	for(int x=1;x<=n;++x) a[x]=read(),b[x]=read(),iv+=a[x];
	iv=qp(iv);
	for(int x=1;x<=n;++x){
		int p=(ll)a[x]*iv%P;
		for(int i=sum;~i;--i)
			for(int j=num;~j;--j){
				int pw=1;
				if(!f[i][j]) continue;
				for(int t=0;t<b[x];++t){
					dec(f[i+a[x]][j+t],(ll)fiv[t]*pw%P*f[i][j]%P);
					pw=(ll)pw*p%P;
				}
			}
		num+=b[x]-1;
		sum+=a[x];
	}
	int res=0;
	for(int i=0;i<=sum;++i){
		int p=(ll)i*iv%P;
		for(int j=0;j<=num;++j)
			res=(res+(ll)f[i][j]*qp(p,P-2-j)%P*fac[j]%P)%P;
	}
	printf("%d\n",res);
	return 0;
}
```

跟其它的做法殊途同归了。

---

## 作者：Kevin090228 (赞：2)

容易想到 $\min-\max$ 容斥：计算对于每个 $\{1,2,\cdots,n\}$ 的子集 $S$，$S$ 中第一次存在达到限定次数的数的期望轮数。

令 $P(S)=\sum\limits_{x\in S}A_x$。对于一个固定的 $S$，容易计算它的答案为 $(-1)^{|S|}\frac{P(\{1,2,\cdots,n\})}{P(S)}\sum\limits_{\{a_i\},0\leq a_i<B_i}(\sum a_i)!\prod\limits_{x\in S}(\frac{A_x}{P(S)})^{a_x}\frac{1}{a_x!}$。

这个式子显然可以使用动态规划解决，状态中需要记录当前考虑到前 $i$ 个数，$P(S)=j$，所有 $a_x$ 的和为 $k$ 的贡献总和。转移时暴力枚举 $a_i$ 即可。

时间复杂度 $O((\sum A_i)(\sum B_i)^2)$。

---

## 作者：UKE_Automation (赞：1)

### AGC038E Gachapon

[$\text{Link}$](https://atcoder.jp/contests/agc038/tasks/agc038_E)

首先我们假设最后每个数第一次达到 $B_i$ 的时间是 $t_i$，那么我们要求的就是 $E(\max t_i)$。看到这个就不难想到 Min-Max 容斥，我们有：
$$
E(\max t_i)=\sum_{T\subseteq \{1,2,\cdots,n\}}(-1)^{|T|-1}E(\min(T))
$$
现在考虑如何求 $E(\min(T))$。首先第一步，我们发现所有在 $T$ 之外的元素对 $T$ 的求解应该没有太多影响，所以我们希望把这一部分的贡献刨掉。我们知道，对于一个概率为 $P$ 的事件，完成他的期望步数是 $\dfrac{1}{P}$。所以假如我们只考虑 $T$ 之内每个元素的概率，算出 $E$ 之后乘上一个 $\dfrac{1}{P}$ 应该就是正确答案。$P$ 也是好算的，令 $A=\sum a_i$，$P$ 就是 $\dfrac{\sum_{i\in T} a_i}{A}$。

然后考虑怎么计算 $T$ 之内的期望。这里需要一步经典的转化。我们把期望写成定义的形式，然后变形可得：
$$
\begin{aligned}
&E(\min(T))=\sum i\times P(\min(T)=i)\\
\Rightarrow &E(min(T))=\sum P(\min(T)\ge i)
\end{aligned}
$$
也就是我们要对每个 $i$，求出在第 $i$ 轮还没有任何元素达到 $B_i$ 的概率之和。我们枚举每个元素被选取的个数 $c_i$，令 $k=\sum c_i$，则我们的概率就是多重组合数乘上概率，为：
$$
\frac{k!}{\prod c_i!}\times \prod\left(\frac{a_i}{\sum\limits_{j\in T} a_j}\right)^{c_i}
$$
所以整理得答案是：
$$
\sum_{T\subseteq\{1,2,\cdots,n\}}(-1)^{|T|-1}\times A\sum\frac{k!}{(\sum\limits_{i\in T} a_i)^{k+1}}\prod \dfrac{a_i^{c_i}}{c_i!}
$$
这个时候我们就可以直接 dp 了，令 $dp(i,j,k)$ 表示考虑前 $i$ 个数，$\sum a_i=j$，$\sum c_i=k$ 的方案数。转移的时候带上容斥系数，我们有：
$$
dp(i,j,k)=dp(i-1,j,k)-\sum dp(i-1,j-a_i,k-l)\times \frac{a_i^{l}}{l!}
$$
要注意初值有转移系数，应该是 $dp(0,0,0)=-1$。最后答案就是 $A\times \sum \dfrac{dp(n,i,j)\times j!}{i^{j+1}}$。直接转移的话复杂度好像是 $O(n^4)$ 的，但是实则不然，因为我们 $l$ 的枚举上界不超过 $B_i$，所以这个枚举量上界不超过 $\sum B=400$。所以复杂度应该是 $O(n^3)$ 级别的，可以通过。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 400 + 5;
const int Inf = 2e9;
const int Mod = 998244353;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b, int P = Mod) {int res = 1; for(; b; a = 1ll * a * a % P, b >>= 1) if(b & 1) res = 1ll * res * a % P; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, a[Maxn], b[Maxn];
int f[Maxn][Maxn][Maxn];
int fac[Maxn], inv[Maxn];

void init(int N) {
	fac[0] = 1; for(int i = 1; i <= N; i++) fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[N] = Inv(fac[N]); for(int i = N; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % Mod;
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n);
	int sa = 0, sb = 0;
	for(int i = 1; i <= n; i++) read(a[i]), read(b[i]), sa += a[i], sb += b[i];
	init(400);
	f[0][0][0] = Mod - 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= sa; j++) {
			for(int k = 0; k <= sb; k++) {
				f[i][j][k] = f[i - 1][j][k];
				if(j >= a[i]) {
					for(int l = 0; l <= min(b[i] - 1, k); l++) sub(f[i][j][k], 1ll * f[i - 1][j - a[i]][k - l] * qpow(a[i], l) % Mod * inv[l] % Mod);
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= sa; i++) {
		for(int j = 0; j <= sb; j++) {
			pls(ans, 1ll * f[n][i][j] * qpow(Inv(i), j + 1) % Mod * fac[j] % Mod);
		}
	}
	ans = 1ll * ans * sa % Mod;
	write(ans);
    Usd();
	return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

# Solution

令 $t_x$ 为 $x$ 出现 $B_x$ 次的时间，则我们要求 $E(\max\limits_{x=1}^n t_x)$。考虑 min-max 容斥：$E(\max\limits_{x=1}^n t_x)=\sum\limits_{S\neq\empty}(-1)^{\vert S\vert-1}E(\min\limits_{x\in S} t_x)$。

然后考虑如何求 $E(\min\limits_{x=1}^n t_x)$，首先这个东西的概率我们可以转化为每个时间（注意这里包括时间 $0$）所有 $x$ 出现次数都小于 $b_x$ 的概率之和，枚举每个 $x$ 的出现次数 $c_x$：
$$
\begin{aligned}
&E(\min\limits_{x=1}^n t_x)\\
=&\sum_{\forall x\in [1,n]0\le c_x<b_x}\binom{\sum\limits_{x=1}^n c_x}{c_1,c_2,\dots,c_n}\prod_{x=1}^n{\left(\dfrac{a_x}{\sum_{i=1}^n a_i}\right)}^{c_x}\\
=&\sum_{\forall x\in [1,n]0\le c_x<b_x}\dfrac{(\sum_{x=1}^n c_x)!}{(\sum_{x=1}^n a_x)^{\sum_{i=1}^n c_i}}\prod_{x=1}^n\dfrac{{a_x}^{c_x}}{c_x!}\\
\end{aligned}
$$

对于任意一个集合 $S$，求 $E(\min\limits_{x\in S} a_x)$ 和上面类似，只需要把限制都改为 $x\in S$，外面再乘上一个 $\dfrac{\sum_{x=1}^n a_x}{\sum_{x\in S} a_x}$（这个就是每次选到 $S$ 集合中元素的期望次数）。

然后由于值域比较小，所以我们可以考虑 DP，设 $f_{x,y,z}$ 表示考虑 $[1,x]$ 中的元素，当前选出的 $\sum\limits_{i\in S} a_i=y,\sum\limits_{i\in S} c_i=z$ 的答案（注意不选的容斥系数为 $-1$，所以 $f_{0,0,0}=-1$），转移就是 $f_{x,y,z}=f_{x-1,y,z}-\sum\limits_{i=0}^{b_i-1} f_{x-1,y-a_x,k-i}\times \dfrac{{a_x}^i}{i!}$。

最终答案就为 $\sum\limits_{x=1}\sum\limits_{y=0} f_{n,x,y}\times\dfrac{y!}{x^y}$。

总时间复杂度是 $O((\sum\limits_{x=1}^n a_x)(\sum\limits_{x=1}^n b_x)^2)$。
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
const int N=401,mod=998244353;
int fact[N],ifact[N],inv[N];
int n,sum,ans,a[N],b[N];
int f[N][N][N];

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
void add(int &x,int y) { (x+=y)>=mod&&(x-=mod); }
void sub(int &x,int y) { (x-=y)<0&&(x+=mod); }
main()
{
	n=read(),f[0][0][0]=mod-1,fact[0]=ifact[0]=inv[1]=1;
	for (int i=1;i<=n;i++) a[i]=read(),b[i]=read(),sum+=a[i];
	for (int i=1;i<N;i++) fact[i]=fact[i-1]*i%mod;
	for (int i=2;i<N;i++) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	for (int i=1;i<N;i++) ifact[i]=ifact[i-1]*inv[i]%mod;
	for (int i=1;i<=n;i++)
		for (int j=0;j<N;j++)
			for (int k=0;k<N;k++)
				if (f[i-1][j][k]) {
					add(f[i][j][k],f[i-1][j][k]);
					for (int l=0,mul=1;l<b[i];l++,mul=mul*a[i]%mod)
					sub(f[i][j+a[i] ][k+l],f[i-1][j][k]*mul%mod*ifact[l]%mod);
				}
	for (int i=1;i<N;i++)
		for (int j=0,mul=sum*inv[i]%mod;j<N;j++,mul=mul*inv[i]%mod)
			if (f[n][i][j]) add(ans,f[n][i][j]*fact[j]%mod*mul%mod);

	printf("%lld",ans);
	return 0;
}
```

---

## 作者：strlen_s_ (赞：1)

没有用 min-max 容斥，用的是一种非常暴力的思路……

 设 $SA=\sum A_i,SB=\sum B_i,P_i=\frac{A_i}{SA}$。

考虑我们枚举最后被填上的是 $i$，那么考虑你填数的序列，设你其它的数 $j$ 填了 $c_j(c_j\ge B_j)$ 个，那么答案是:

$$(B_i+\sum_{j\neq i}c_j)P_i^{B_i}\binom{B_i-1+\sum_{j\neq i}c_j}{c_1,\cdots B_i-1,\cdots c_n}\prod_{j\neq i}P_j^{c_j}$$

发现存在一个组合数，考虑其指数型生成函数，我们发现其答案可以表示为如下形式：

设:

$$G_i=e^{P_ix}-\sum_{j=0}^{B_i-1}\frac{P_i^jx^j}{j!},F=\prod_{i=1}^n G_i，H=\sum_{i=1}^n\frac{F}{G_i}\frac{P_i^{B_i}x^{B_i-1}}{(B_i-1)!}$$

则:

$$ans=\sum_{i=0}^{+\infin}(i+1)![x^i]H$$

我们考虑如何求出 $H$，我们发现，$H$ 一定是形如:

$$\sum_{i=0}^{SA-1}e^{\frac{i}{SA}}T_i$$

其中 $T_i$ 为一最高次数为 $SB-1$ 的多项式。

只要我们求出了每个 $T_i$ 的具体值，我们就可以计算答案了。

直接做是 $O(n^5)$ 的。我们发现我们不关系计算过程中每次计算后 $T_i$ 的各项系数是多少，只关心最终是什么。那么我们可以进行一次拉格朗日插值，最终再对每个 $T_i$ 还原多项式。

那么 $G_i=e^{P_ix}-C_i$，其中 $C_i$ 为一常数。

设 $y=e^x$，则可以每次先 $O(n^2)$ 的算出 $F$。

然后再每次枚举 $i$，然后就相当于把 $F$ 除以一个 $y^{P_i}-C_i$，这是容易 $O(n)$ 求解的。

然后再把 $F$ 的每一项系数对应加和到 $T_i$ 对应的点值上，再将 $F$ 还原。最后还原 $T_i$ 即可。

于是复杂度为 $O(SA(SB)^2)$。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=405,mod=998244353,M=400;
int n;
int A[N],B[N],sa;
ll dp[N][N],g[N],res[N],ans;
ll fr[N],inv[N],iv[N],ia,v1[N],v2[N];
ll ksm(ll a,int b){
  ll res=1;
  while(b){
    if(b&1)res=res*a%mod;
    a=a*a%mod,b>>=1;
  }
  return res;
}
ll C(int x,int y){return fr[x]*inv[y]%mod*inv[x-y]%mod;}
void ins(ll x,int p){for(int i=M;i>=0;i--)g[i]=(g[i]*x+(i-p>=0?g[i-p]:0))%mod;}
void del(ll x,int p){for(int i=0;i<=M;i++)g[i]=(g[i]-(i-p>=0?g[i-p]:0)+mod)*x%mod;}
signed main(){
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  fr[0]=1;for(int i=1;i<=M;i++)fr[i]=fr[i-1]*i%mod;
  inv[M]=ksm(fr[M],mod-2);for(int i=M-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
  iv[1]=1;for(int i=2;i<=M;i++)iv[i]=iv[mod%i]*(mod-mod/i)%mod;
  cin>>n;for(int i=1;i<=n;i++)cin>>A[i]>>B[i],B[i]--,sa+=A[i];
  ia=ksm(sa,mod-2);
  for(int x=1;x<=M;x++){
    memset(g,0,sizeof(g));g[0]=1;
    for(int i=1;i<=n;i++){
      ll ra=1,rx=1;v1[i]=0;
      for(int j=0;j<=B[i];j++)v1[i]=(v1[i]+ra*rx%mod*inv[j])%mod,ra=ra*A[i]%mod*ia%mod,rx=rx*x%mod;
      v2[i]=ra*rx%mod*iv[x]%mod*inv[B[i]]%mod;
      ins(mod-v1[i],A[i]);
    }
    for(int i=1;i<=n;i++){
      del(ksm(mod-v1[i],mod-2),A[i]);
      for(int j=0;j<=M;j++)dp[j][x]=(dp[j][x]+g[j]*v2[i])%mod;
      ins(mod-v1[i],A[i]);
    }
  }
  for(int i=0;i<=sa;i++){
    memset(g,0,sizeof(g));memset(res,0,sizeof(res));
    g[0]=1;
    for(int j=1;j<=M;j++)ins(mod-j,1);
    for(int j=1;j<=M;j++){
      del(mod-iv[j],1);
      ll sm=dp[i][j];
      for(int k=1;k<=M;k++){
        if(k==j)continue;
        sm=sm*(k<j?iv[j-k]:mod-iv[k-j])%mod;
      }
      for(int k=0;k<=M;k++)res[k]=(res[k]+g[k]*sm)%mod;
      ins(mod-j,1);
    }
    ll ip=ia*i%mod,ic=ksm(mod+1-ip,mod-2),ra=ic;
    for(int j=0;j<=M;j++){
      ans=(ans+fr[j]*res[j]%mod*ra)%mod;
      ra=ra*ic%mod;
      ans=(ans+fr[j]*res[j]%mod*(j+ip)%mod*ra)%mod;
    }
  }
  cout<<ans<<'\n';
  return 0;
}
```

---

## 作者：Anoshag_Ruwan (赞：1)

min-max 反演+生成函数：看到全部元素满足状态这个限制立即反应要求 $E(\max(S))$ ,而期望时间往往 $\max$ 是比 $\min$ 难求的，直接考虑 min-max 反演。$E(\max(S))=\sum\limits_{T \subseteq S}E(\min(T))(-1)^{|T|+1}$

考虑怎么求所有集合的 $\min$，令 $s1=\sum\limits_{i \in T}a_i$，由 $E(XY)=E(X)E(Y)$ 和几何分布，可以只管在集合内随机生成的期望，最后再将答案 $\times \frac{s1}{\sum S}$ 即可。根据整数概率公式 $E(X)=\sum\limits_{i \geq 1}P(X \geq i)$，我们要算的就是前 $k$ 次没有使任一元素生成 $B_i$ 次的概率对 $k$ 累加求和。令 $f_i(x)$ 表示 $a_i$ 未满足条件的概率生成函数（PGF），这里使用指数型生成函数（EGF），即 $f_i(x)=\sum\limits_{k<B_i}(\frac{a_i}{s1})^k\frac{x^k}{i!}$，期望就是 $\sum\limits_{k \geq 0}k![x^k]\prod\limits_{i \in T}f_i(x)$，考虑到 $|T|,s1$ 和次数上线都在 $400$ 以内，这个式子可以多项式递推了。令 $dp_{i,j,h}$ 表示考虑前 $i$ 个数，$s1=j,k=h$ 的答案 $\times s1^k$ 的值，当把第 $i$ 个数加进去时，容斥系数肯定取反，然后在 $[0,B_i-1]$ 之间枚举 $e_i$，时间复杂度为 $O((n+\sum B_i)\sum A_i\sum B_i)=O(n^3)$，最终答案为 $\sum\limits_{s1,k} dp_{n,s1,k}\frac{\sum S}{s1^{k+1}}$。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const int p=998244353;
LL dp[411][411][411],a[411],b[411],s[411],s1[411],frc[100011],inv[100011];
inline LL add(LL x,LL y){return x+y>=p?x+y-p:x+y;}
inline LL ksm(LL x,LL y){
    LL k=1,l=x;if(l>=p)l%=p;
    while(y){if(y&1)k=k*l%p;l=l*l%p,y>>=1;}
    return k;
}inline LL rd(){
	LL i=0,j=1;char g=getchar();
	while(g>57||g<48){if(g=='-')j=-1;g=getchar();}
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*j;
}
int main()
{
	LL i,j,k,h,ans=0,h1,m,n=rd();
	for(i=frc[0]=1;i<=400;i++)frc[i]=frc[i-1]*i%p;
	for(i=400,inv[i]=ksm(frc[i],p-2);i;i--)inv[i-1]=inv[i]*i%p;
	for(i=1;i<=n;i++)
		a[i]=rd(),b[i]=rd(),s1[i]=s1[i-1]+a[i],s[i]=s[i-1]+b[i];
	for(i=1,dp[0][0][0]=p-1;i<=n;i++)
		for(j=0;j<=s1[i];j++)
			for(h=0;h<=s[i];h++){
				for(h1=0,k=1,dp[i][j][h]=dp[i-1][j][h];h1<b[i]&&h1<=h;k=k*a[i]%p,h1++)
					if(j>=a[i])dp[i][j][h]=add(dp[i][j][h],p-dp[i-1][j-a[i]][h-h1]*k%p*inv[h1]%p);
	}for(i=0;i<=s1[n];i++)
		for(j=0;j<=s[n];j++)
			ans=add(ans,ksm(i,(j+1)*(p-2))*frc[j]%p*dp[n][i][j]%p);
	printf("%lld\n",ans*s1[n]%p);		
	return 0;
}
```

当然，上述做法是建立在看到求次数 $\max$ 直接想到 min-max 容斥的基础上，可不可以正面求出 $\max$ 呢，其实是可以的。不过推式子疑似过于麻烦，在这里不说了。

---

## 作者：Graphcity (赞：1)

分享一个民工级多项式做法。

考虑 $\min-\max$ 容斥。容斥之后，转化为求一些数第一次满足条件的期望时间，也就是 $\sum_{S}(-1)^{|S|-1}E(\min_{i\in S}t_{cnt_i\ge B_i})$，其中 $t_{A}$ 表示事件 $A$ 发生的期望时间。

不妨钦定集合 $S$ 中第一次满足条件的是 $i$。我们把随机数生成器生成的数从左往右排成一行，然后提取出仅由 $S$ 中数字构成的子序列。思考我们要求什么：

1. 有多少种合法子序列，每一种合法子序列出现的概率是多少。
2. 恰好能够形成合法子序列的期望时间。

先求第一问。找到合法子序列的条件：

1. 有 $B_i$ 个 $i$，且子序列的最后一个数一定是 $i$。
2. 集合中的其它数出现次数小于对应的 $B$。

然后思考它在所有合法子序列出现的概率：设 $sum=\sum_{k\in S}A_k$，那么概率显然是
$$
(\dfrac{A_i}{sum})^{B_i}\times \prod_{j\in S,j\not=i}(\dfrac{A_j}{sum})^{C_j}
$$
其中 $C_j$ 为 $j$ 在子序列中出现的次数。

考虑使用 EGF 刻画它。设 $f_i=\sum_{k=0}^{B_i-1}\dfrac{1}{k!}A_i^kx^k$，$g_i=\dfrac{1}{(B_i-1)!}A_i^{B_i-1}x^{B_i-1}$，刻画合法子序列的生成函数就是：
$$
F=g_i\times \prod_{j\in S,j\not = i}f_j
$$
有 $k+1$ 个数的合法子序列的概率之和就是 $F_k\times k!\times A_i\times sum^{-(k+1)}$。（这是因为生成函数并没有包含最后一个固定为 $i$ 的数）

接下来就是第二问。下一个生成的随机数中，有 $\dfrac{sum}{all}$ 的概率为集合中的数，其中 $all=\sum_i A_i$。也就是说，生成一个集合中的数的期望次数就是 $\dfrac{all}{sum}$。综合之前的概率式子，这个集合中 $i$ 对应的贡献为：
$$
(-1)^{|S|-1}\sum_k (k+1)!\times \dfrac{all}{sum} \times sum^{-(k+1)} \times A_i\times [x^k]g_i\prod_{j\in S,j\not = i}f_j
$$
接下来就是快速求出所有集合中所有 $i$ 的贡献之和。分析贡献式跟什么有关：$S$ 的大小，$sum$，子序列的长度 $k+1$，$g_i$ 和不等于 $i$ 的 $f_j$。考虑枚举 $i$，计算所有 $i$ 带来的贡献：

对于 $sum$，根据题目它应该 $\le 400$，考虑类似背包的东西。设 $h_k$ 表示 $sum=k$ 时对应的生成函数。往背包中加入 $j$ 时，有 $h_k\gets h_k+h_{k-A_j}\times (-f_j)$。这里的 $-f_j$ 是因为加入 $j$ 时有 $-1$ 的容斥系数。

如果把所有不等于 $i$ 的 $j$ 全都加入背包后，总的贡献就很好表示了：
$$
A_i\times \sum_{sum}\sum_k[x^k]g_i h_{sum}\times \frac{all}{sum}\times (k+1)!\times sum^{-(k+1)}
$$
如果暴力进行卷积，最坏是 $O(n^5)$ 的。考虑进行优化。

注意到我们背包的都是除了 $i$ 以外的元素。如果我们提前先往背包中加入所有元素，枚举到 $i$ 时再去掉 $i$ 带来的贡献，这样就是 $O(n^4)$ 的。使用 NTT 可以做到 $O(n^3\log n)$。跑过去还是挺难的。

继续优化！考虑分离贡献：
$$
\sum_{sum}\sum_k\frac{all}{sum}\times (k+1)!\times sum^{-(k+1)}\times \sum_iA_i\times [x^k]g_ih_{i,sum}
$$
这样做有什么用呢？如果我们求出整的多项式组 $w_{sum}=\sum_ig_ih_{i,sum}\times A_i$，那么就只要对这其中的每一项乘上一个固定的系数，然后相加就行了。

接下来的问题就是怎么快速求出这个多项式组。注意到子序列长度至多为 $\sum B_i\le 400$，那多项式的次数也不会超过 $400$！如果我们一开始就将 $0\sim 400$ 的点值代入，那么做多项式四则运算的时间复杂度就是线性的！

最后一个问题，如果我们知道了一个多项式在 $0\sim n$ 处的点值，该怎么还原这个多项式？思考一下拉格朗日插值的形式：
$$
f(x)=\sum_{i=0}^ny_i\frac{\prod_{j\not= i}x-j}{\prod_{j\not= i}i-j}
$$
分母部分为常数，不妨令 $p_i=y_i\prod_{j\not = i}i-j$，那么多项式就长这样：$f(x)=\sum_{i=0}^np_i\prod_{j\not= i}x-j$。

右边的部分相当于一个背包。如果同之前的方式进行背包，就可以用 $O(n^2)$ 的方式还原整个多项式。

总时间复杂度 $O(n^3)$，模数甚至都不需要是 $998244353$！

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=400,Mod=998244353;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
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

int n,sum,ans,A[Maxn+5],B[Maxn+5],fac[Maxn+5],num[Maxn+5];
int p[Maxn+5][Maxn+5],f[Maxn+5][Maxn+5],inv[Maxn+5],g[Maxn+5];
int pw[Maxn+5][Maxn+5],h[Maxn+5][Maxn+5],val[Maxn+5],q[Maxn+5];

int main()
{
    n=read(),fac[0]=inv[0]=1;
    For(i,1,Maxn) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[Maxn]=Pow(fac[Maxn],Mod-2);
    Rof(i,Maxn-1,1) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    For(i,0,Maxn) For(j,0,Maxn) pw[i][j]=Pow(i,j);
    For(i,1,n) A[i]=read(),B[i]=read(),sum+=A[i];
    For(i,1,n)
    {
        memset(g,0,sizeof(g)); g[0]=1;
        For(j,1,B[i]-1) g[j]=1ll*g[j-1]*A[i]%Mod;
        For(j,0,B[i]-1) g[j]=1ll*(Mod-g[j])*inv[j]%Mod;
        For(j,0,Maxn) For(k,0,B[i]-1) p[i][j]=(p[i][j]+1ll*pw[j][k]*g[k])%Mod;
    }
    For(i,0,Maxn) f[0][i]=1;
    For(i,1,n) Rof(k,sum,A[i]) For(x,0,Maxn)
        f[k][x]=(f[k][x]+1ll*f[k-A[i]][x]*p[i][x])%Mod;
    For(i,1,n)
    {
        For(j,A[i],sum) For(x,0,Maxn) f[j][x]=(f[j][x]-1ll*f[j-A[i]][x]*p[i][x]%Mod+Mod)%Mod;
        memset(g,0,sizeof(g));
        int res=1ll*Pow(A[i],B[i]-1)*inv[B[i]-1]%Mod;
        For(j,0,Maxn) g[j]=1ll*pw[j][B[i]-1]*res%Mod;
        For(j,0,sum-A[i]) For(k,0,Maxn) h[j+A[i]][k]=(h[j+A[i]][k]+1ll*f[j][k]*g[k]%Mod*A[i])%Mod;
        Rof(j,sum,A[i]) For(x,0,Maxn) f[j][x]=(f[j][x]+1ll*f[j-A[i]][x]*p[i][x])%Mod;
    }
    For(i,0,Maxn)
    {
        val[i]=1;
        For(j,0,Maxn) if(i!=j) val[i]=1ll*val[i]*(i-j+Mod)%Mod;
        val[i]=Pow(val[i],Mod-2)%Mod;
    }
    q[1]=1; For(i,1,Maxn) Rof(j,Maxn+1,1) q[j]=(1ll*(Mod-i)*q[j]+q[j-1]+Mod)%Mod;
    For(i,0,sum)
    {
        memset(num,0,sizeof(num));
        For(j,0,Maxn) h[i][j]=1ll*h[i][j]*val[j]%Mod;
        For(j,0,Maxn) num[j]=(num[j]+1ll*h[i][0]*q[j+1])%Mod;
        For(j,1,Maxn)
        {
            int w=Pow(Mod-j,Mod-2);
            For(k,1,Maxn+1) q[k]=1ll*(q[k]-q[k-1]+Mod)*w%Mod;
            For(k,0,Maxn) num[k]=(num[k]+1ll*h[i][j]*q[k])%Mod;
            Rof(k,Maxn+1,1) q[k]=(1ll*(Mod-j)*q[k]+q[k-1])%Mod;
        }
        For(j,0,Maxn)
        {
            int k=1ll*num[j]*fac[j]%Mod;
            int w=1ll*sum*Pow(i,Mod-2)%Mod; w=1ll*w*(j+1)%Mod;
            k=1ll*k*Pow(Pow(i,j+1),Mod-2)%Mod;
            ans=(ans+1ll*k*w)%Mod;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```



---

