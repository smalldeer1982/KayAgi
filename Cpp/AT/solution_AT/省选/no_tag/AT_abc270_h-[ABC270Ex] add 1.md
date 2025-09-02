# [ABC270Ex] add 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc270/tasks/abc270_h

$ A_1=0 $ かつ $ A_N\ >\ 0 $ であるような、$ N $ 個の非負整数の組 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。

高橋君は $ N $ 個のカウンターを持っており、最初、全てのカウンターの値は $ 0 $ です。  
高橋君は、全ての $ 1\leq\ i\leq\ N $ について $ i $ 番目のカウンターの値が $ A_i $ 以上となるまで次の操作を繰り返します。

> $ N $ 個のカウンターの中から $ 1 $ つを等確率に選び、その値を $ 0 $ にする。（選択は毎回独立に行う。）  
> 選んだカウンター **以外** のカウンターの値を $ 1 $ 増加させる。

高橋君の操作回数の期待値を $ \mathrm{mod} $ $ 998244353 $ で出力してください（注記参照）。

## 说明/提示

### 注記

求める期待値は必ず有限値かつ有理数となることが証明できます。また、この問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 0=A_1\leq\ A_2\leq\ \cdots\ \leq\ A_N\leq\ 10^{18} $
- $ A_N\ >\ 0 $
- 入力は全て整数

### Sample Explanation 1

$ i $ 番目のカウンターの値を $ C_i $ で表します。 高橋君の操作が終了するまでの一連の流れの例は次の通りです。 - $ 1 $ 番目のカウンターの値を $ 0 $ にした後、それ以外のカウンターの値を $ 1 $ 増加させる。 $ (C_1,C_2)=(0,1) $ となる。 - $ 2 $ 番目のカウンターの値を $ 0 $ にした後、それ以外のカウンターの値を $ 1 $ 増加させる。 $ (C_1,C_2)=(1,0) $ となる。 - $ 1 $ 番目のカウンターの値を $ 0 $ にした後、それ以外のカウンターの値を $ 1 $ 増加させる。 $ (C_1,C_2)=(0,1) $ となる。 - $ 1 $ 番目のカウンターの値を $ 0 $ にした後、それ以外のカウンターの値を $ 1 $ 増加させる。 $ (C_1,C_2)=(0,2) $ となる。 この場合の操作回数は $ 4 $ となります。 $ 1,2,3,4,5,\ldots $ 回で操作が終了する確率はそれぞれ $ 0,\frac{1}{4},\ \frac{1}{8},\ \frac{1}{8},\ \frac{3}{32},\ldots $ であり、 期待値は $ 2\times\frac{1}{4}+3\times\frac{1}{8}+4\times\frac{1}{8}+5\times\frac{3}{32}+\dots=6 $ となります。 よって、 $ 6 $ を出力します。

## 样例 #1

### 输入

```
2
0 2```

### 输出

```
6```

## 样例 #2

### 输入

```
5
0 1 3 10 1000000000000000000```

### 输出

```
874839568```

# 题解

## 作者：翼德天尊 (赞：12)

这场的 H 也尝试补了一下。感觉很妙。

题目中的状态是复杂的，且 $n$ 的范围很大，无法状压。但是我们是需要进行状态之间的转移的。

所以我们就需要考虑如何才能高效地表示一个状态。我们都关注哪些信息呢？每个数当前距离 $a_i$ 的差值？这太冗余了。事实上，由于本题特殊的性质，我们只需要关注 $n$ 个数中，当前值 $c_i$ 距离 $a_i$ 最大的差值即可。

很奇怪？但是这却是可以转移的。设这个最大的差值为 $s$，我们显然可以找到一个 $r$，使得 $a_r<s\le a_{r+1}$。此时如果我们对于 $a_1$ 到 $a_r$ 进行之间的某一个数进行了清零操作，由于其他数的值都会加 $1$，所以我们都 $s$ 就会被更新为 $s-1$；如果我们对于 $a_{r+1}$ 到 $a_n$ 中的录一个数 $a_k$ 进行了清零操作，那么由于 $a_k\ge s$，所以此时 $s$ 就会变成 $a_k$。

发现了吗？这个状态虽然简洁，但是在找到 $r$ 的情况下，是可以进行转移的。（其实这里用**一个简单**的 $s$ 映射**一类复杂**的状态的设计，有点类似于 hash 的感觉了，个人感觉非常妙）

于是我们设 $dp_i$ 表示当前 $s=i$ 时，距离终点最大差值为 $0$ 状态的期望轮数（倒序转移），则初始状态 $dp_0=0$。有转移方程：
$$
dp_i=\frac{1}{n}(r_i\times dp_{i-1}+\sum_{j=r_i+1}^ndp_{a_j})+1
$$
我们转移顺序变一致一下，把 $dp_{i-1}$ 拉出来：
$$
dp_{i-1}=\frac{1}{r_i}(n\times (dp_{i}-1)-\sum_{j=r_i+1}^ndp_{a_j})
$$
然后我们发现此时 $i$ 较小的状态是由较大的状态转移过来的，而初始状态好像是 $dp_0$，顺序反了。于是我们考虑将 $dp$ 的意义颠倒一下，设 $f_i$ 表示 $dp_{a_n}-dp_i$，则有 $dp_i=dp_{a_n}-f_i$。考虑将转移方程化为只和 $f$ 有关的式子，则有：
$$
\begin{aligned}
dp_{a_n}-f_{i-1}
&=\frac{1}{r_i}(n\times (dp_{a_n}-f_i-1)-\sum_{j=r_i+1}^ndp_{a_j})\\
&=\frac{1}{r_i}(\sum_{j=r_i+1}^n(dp_{a_n}-dp_{a_j})+r\times dp_{a_n}-n\times(f_i+1))\\
&=\frac{1}{r_i}(\sum_{j=r_i+1}^nf_{a_j}-n\times(f_i+1))+dp_{a_n}
\end{aligned}
$$
将 $dp_{a_n}$ 消去，变号得：
$$
f_{i-1}=\frac{1}{r_i}(n\times (f_i+1)-\sum_{j=r_i+1}^nf_{a_j})
$$
此时我们发现 $dp_n$ 全部消去了，变了个号后 $f_i$ 还是从小向大转移，但是由于 $f_i$ 的意义和 $dp_i$ 正好相反，所以我们就成功改变了转移顺序。此时我们就已经可以正常转移了。

又注意到 $n$ 非常大，所以我们可以考虑采用矩阵加速的方式优化转移，转移过程中以每一个 $a_i$ 为关键转移点停止转移找到当前的 $r$ 后再重新开始转移即可。设单次矩阵乘法的时间复杂度为 $ω=2^3$，则时间复杂度 $O(\omega n\log A)$。

听说还有更高级的优化方式可以进一步优化。不过与我无关（

代码很短，精华在于式子的转化。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
const int N=2e5+5;
const int mod=998244353;
int n,a[N];
struct node{
	int a[2][2];
	node(){
		memset(a,0,sizeof(a));
	}
	void init(){
		a[0][0]=a[1][1]=1;
	}
	void init1(int x,int y){
		a[0][0]=1,a[0][1]=((n-x)*y%mod+mod)%mod;
		a[1][0]=0,a[1][1]=n*y%mod;
	}
}S,Z;
node operator *(const node&x,const node&y){
	node z;
	for (int k=0;k<2;k++)
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%mod)%mod;
	return z;
}
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
int ksm(int x,int y){
	int ans=1;
	x%=mod;
	while (y){
		if (y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int inv(int x){
	return ksm(x,mod-2);
}
node _ksm(node x,int y){
	node ans;
	ans.init();
	while (y){
		if (y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	S.a[0][0]=1,S.a[0][1]=0;
	int sum=0;
	for (int i=n-1;i>=1;i--){
		Z.init1(sum,inv(i));
		S=S*_ksm(Z,a[i+1]-a[i]);
		sum=(sum+S.a[0][1])%mod;
	}
	cout<<S.a[0][1]<<'\n';
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：7)

# ABC270Ex 题解



## 思路分析

用 $C_i$ 表示第 $i$ 个计数器的值。

首先考虑如何把 $\{C_i\}$ 的信息压缩简单化。

考虑用 $k$ 表示 $\max_{i=1}^n\left\{A_i-C_i\right\}$，显然最终的答案就是 $k=0$，初始的条件就是 $k=A_n$。

那么讨论接下来选的下标 $p$ 和新的状态 $k'$ 的关系，显然有 $k'=\max\{A_p,k-1\}$。

- $A_p<k$，$k'=k-1$。
- $A_p\ge k$，$k'=A_p$。

因此我们设 $f_k$ 表示从状态 $k$ 转移到答案的期望操作次数，显然 $f_{A_n}=0$，即求 $f_0$ 的值。

假设 $A_p< k\le A_{p+1}$ 那么由上面的讨论我们有：
$$
f_k=\dfrac 1n\left( pf_{k-1}+\sum_{i=p+1}^n f_{A_i}\right)+1
$$
但是这样的转移式要从前面和后面分别转移，非常不方便，因此考虑把 $f_{k-1}$ 提出来：
$$
f_{k-1}=\dfrac 1p\left[n(f_k-1)-\sum_{i=p+1}^nf_{A_i}\right]
$$
置换 $k-1$ 和 $k$，并且利用 $A_i\ge k>k-1$ 改写 $\sum$，可以得到：
$$
f_{k}=\dfrac 1p\left[n(f_{k+1}-1)-\sum_{A_i>k} f_{A_i}\right]
$$
条件限制为 $A_p\le k<A_{p+1}$。

注意到对于所有 $k\in[A_p,A_{p+1})$，$f_k$ 的转移是相对稳定的，因此记 $X_i=f_{A_i},S=\sum_{k=i+1}^n X_k$。

简单解一个线性递推可以得到：

若记 $U=\dfrac ni,V=\dfrac {n-S}i,k=A_{i+1}-A_i$。
$$
X_i=U^k\cdot X_{i+1}+V\cdot\dfrac{U^k-1}{U-1}
$$
因此直接转移即可，时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
#define div division_operator
using namespace std;
const int MAXN=2e5+1,MOD=998244353;
int a[MAXN],f[MAXN];
inline int ksm(int a,int b=MOD-2,int m=MOD) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%m;
		a=a*a%MOD; 
		b=b>>1;
	}
	return res;
}
inline int div(int a,int b) {
	return a*ksm(b)%MOD;
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	f[n]=0;
	int sum=0;
	for(int i=n-1;i>=1;--i) {
		int A=div(n,i),B=div(((n-sum)%MOD+MOD)%MOD,i),k=a[i+1]-a[i];
		f[i]=(ksm(A,k)*f[i+1]%MOD+div(ksm(A,k)-1,A-1)*B%MOD)%MOD;
		sum=(sum+f[i])%MOD;
	}
	printf("%lld\n",f[1]);
	return 0;
} 
```



---

## 作者：FZzzz (赞：5)

来点无脑生成函数。

假设这个过程是无限的，设 $[x^i]F(x)$ 为从初始状态经过 $i$ 步到达一个终态的概率，$[x^i]G(x)$ 为从某个终态（可以发现我们并不关心这个终态具体长什么样）经过 $i$ 步到达一个终态的概率。那么 $[x^i]\dfrac{F(x)}{G(x)}$ 即是从初始状态经过 $i$ 步第一次到达一个终态的概率。

考虑 $F(x)$ 和 $G(x)$ 是啥。发现对于 $G$ 来说只需要最后 $a_i$ 步里不选到 $i$ 即可，对于 $F$ 来说则加一个至少有 $a_n$ 步的限制。令
$$s_i=\prod_{j=1}^{i-1}\left(\dfrac jn\right)^{a_{j+1}-a_j}$$
设 $b(i)$ 为最大的 $j$ 使得 $a_j\le i$，则有
$$[x^i]F(x)=[i\ge a_n]s_n$$
$$[x^i]G(x)=s_{b(i)}\left(\frac{b(i)}n\right)^{i-a_{b(i)}}$$
即
$$F(x)=\frac{s_nx^{a_n}}{1-x}$$
$$G(x)=\frac{s_nx^{a_n}}{1-x}+\sum_{i=1}^{n-1}\frac{n(s_ix^{a_i}-s_{i+1}x^{a_{i+1}})}{n-ix}$$
我们要求的即为
$$\left.\left(\frac{F(x)}{G(x)}\right)'\right|_{x=1}=\frac{F'(1)G(1)-F(1)G'(1)}{G^2(1)}$$
但 $F(1)$ 和 $G(1)$ 是没有意义的，所以把 $F(x)$ 和 $G(x)$ 都乘上 $1-x$，这样所有需要计算的东西都有意义，且 $G(1)=s_n$ 不为 $0$。

至此我们已经可以写出 $F'(x)$ 和 $G'(x)$ 的表达式并计算答案，时间复杂度 $O(n\log a)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n;
ll a[maxn];
const ll mod=998244353;
ll ksm(ll a,ll b){
	ll c=1;
	while(b){
		if(b%2==1) c=c*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return c;
}
ll s[maxn];
ll calc(ll a,int b){
	return (a%mod*(n-b)%mod+b)%mod*ksm(n-b,mod*2-4)%mod;
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	s[1]=1;
	ll invn=ksm(n,mod-2);
	for(int i=2;i<=n;i++) s[i]=s[i-1]*ksm((i-1)*invn%mod,a[i]-a[i-1])%mod;
	ll gg=a[n]%mod*s[n]%mod;
	for(int i=1;i<n;i++){
		gg=(gg+(calc(a[i],i)-calc(a[i]+1,i)+mod)%mod*s[i]%mod*n%mod)%mod;
		gg=(gg-(calc(a[i+1],i)-calc(a[i+1]+1,i)+mod)%mod*s[i+1]%mod*n%mod+mod)%mod;
	}
	printf("%lld\n",(a[n]%mod-gg*ksm(s[n],mod-2)%mod+mod)%mod);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：lzytag (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc270_h)

# Sol
首先我们发现，在一种计数器的状态 $B_1,B_2······B_n$ 中，我们唯一在意的值就是 $\max_{1 \le j \le n} (A_i - B_i)$。当以上值为 $0$ 时即为最终状态。

我们设 $f_x$ 为当 $\max_{1 \le j \le n} (A_i - B_i)=x$ 时期望还需的操作步数。假设下一次操作选择 $j$ ，那么 $x$ 就会变为 $\max(A_j,x-1)$
于是我们可以得到式子：
$$f_x = \frac{\sum_{j=1}^nf_{\max(x-1,A_j)}}{n} + 1 (x>0)$$
我们按照 $A_j$ 与 $x-1$ 的大小分开讨论，记 $s_x$ 为小于 $x$ 的 $A_j$ 的数量，则有:
$$f_x = \frac{s_x}{n}\times f_{x-1} + \frac{\sum_{j=s_x+1}^nf_{j}}{n}+1$$
仅仅通过上面这个式子仍不够直观，让我们而当我们列出所有相邻的两个式子。
$$f_x = \frac{s_x}{n}\times f_{x-1} + \frac{\sum_{j=s_x+1}^nf_{j}}{n}+1$$
$$f_{x+1} = \frac{s_{x+1}}{n}\times f_x + \frac{\sum_{j=s_{x+1}+1}^nf_{j}}{n}+1$$
又因为下式等同于：
$$f_{x+1} = \frac{s_x}{n}\times f_x + \frac{\sum_{j=s_x+1}^nf_{j}}{n}+1$$
(很明显这俩是一样的吧)。

两式相减，即得。
$$f_{x+1} - f_x=\frac{s_x}{n}\ \times(f_x-f_{x-1})$$
最后又根据
$$f_{A_n+1} = f_{A_n} + 1$$
也就是
$$f_{A_n+1} - f_{A_n}= 1$$
（注意此时 $f_{A_n+1}$ 并无实际意义，只是为了计算方便假设出来的）。

即可从后往前算出所有的 $f_x - f_{x-1}$ 然后将他们相加即可，设上式为 $g_x$。

根据之前的式子，$g_x$ 在每一个 $A_i+1\le x \le A_{i+1}$ 的段内都是等比数列，对于每一个等比数列使用求和公式即可，不需要矩阵乘法。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 2e5;
int read()
{
	int x;scanf("%d",&x);
	return x;
}
ll lread()
{
	ll x;scanf("%lld",&x);
	return x;
}
ll qpow(ll x,ll y)
{
	ll res = 1;
	for(;y;y>>=1,x=x*x%mod) if(y&1) res = res*x%mod;
	return res;
}
ll inv(ll x)
{
	return qpow(x,mod-2);
}
ll a[N+5];
int n;
ll ans;
int main()
{
	n = read();
	for(int i = 1;i <= n;i++) a[i] = lread();
	ll g = 1;
	for(int i = n;i > 0;i--)
	{
		if(a[i] == a[i-1]) continue;
		ll p = inv(i-1)*n%mod,q = a[i]-a[i-1];
		ans = (ans + g*(p-qpow(p,q+1)+mod)%mod*inv((mod+1-p)%mod)%mod)%mod;
		g = g*qpow(p,q)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Tsawke (赞：4)

#  [[ABC270Ex] add 1](https://www.luogu.com.cn/problem/AT_abc270_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC270Ex)

## 题面

给定序列 $ A_n $，存在 $ n $ 个初始为 $ 0 $ 的计数器，每次可以进行如下操作：选定一个计数器使其变为 $ 0 $ 并使得其它所有计数器 $ +1 $。求期望的使对于每个 $ i $ 满足第 $ i $ 个计数器的数值不小于 $ A_i $ 的操作次数。对 $ 998244353 $ 取模。

## Solution

大概是一道没有什么高端的算法，仅靠推式子的难度评黑的题。

首先我们不难想到，如果设当前计数器的值为 $ C_i $，那么我们的目的就是要满足所有 $ A_i - C_i \le 0 $。

然后不太严谨地思考一下不难发现，我们每次是使除了选择的其它的计数器都加一，所以拖后腿的一定是 $ \max\{A_i - C_i\} $，令 $ k = \max\{A_i - C_i\} $ 则状态将仅与 $ k $ 相关。

于是此时不难想到一个较为简单的状态：令 $ F(k) $ 表示状态为 $ k $ 时的期望操作次数。

显然 $ F(0) = 0 $，考虑转移，不难发现状态 $ k $ 肯定对应这一个或者一段 $ A $，因为序列 $ A $ 是不降的，所以我们假设第一个对应的前一个为 $ A_{idx} $，显然对于前 $ idx $ 个的操作都会使 $ k \leftarrow k - 1 $，对于 $ idx $ 之后的操作都会使当前的 $ k $ 变为新的 $ A_i $，所以转移显然为：
$$
F(k) = \dfrac{idx}{N}F(k - 1) + \dfrac{1}{N} \sum_{i = idx + 1}^N F(A_i) + 1
$$
转化一下：
$$
N \times F(k) = idx \times F(k - 1) + \sum_{i = idx + 1}^N F(A_i) + N
$$

$$
idx \times F(k - 1) = N \times F(k) - \sum_{i = idx + 1}^N F(A_i) - N
$$

$$
F(k - 1) = \dfrac{N \times (F(k) - 1) - \sum_{i = idx + 1}^N F(A_i)}{idx}
$$

现在不难发现即较小的都在左侧，较大的都在右侧，不过这个转移仍然不行，也就是我们是已知 $ F(0) $ 然后想要求 $ F(A_n) $，但是这个式子却是需要反过来转移的，所以需要优化。

考虑令 $ G(k) $ 表示从状态 $ 0 $ 转移到状态 $ k $ 的期望次数，所以显然有 $ G(k) + F(k) = F(A_n) $。移个项然后带进去 $ F $，显然有：
$$
F(A_n) - G(k) = \dfrac{idx}{N}((F(A_n) -  G(k - 1)) + \dfrac{1}{N} \sum_{i = idx + 1}^N (F(A_n) - G(A_i)) + 1
$$


显然 $ F(A_n) $ 抵消了，则：
$$
G(k) = \dfrac{idx}{N} G(k - 1) + \dfrac{1}{N} \sum_{i = idx + 1}^N G(A_i) - 1
$$
类比一下之前的推出来：
$$
G(k - 1) = \dfrac{N(G(k) + 1) - \sum_{i = idx + 1}^N G(A_i)}{idx}
$$
显然：$ G(A_n) = 0 $，我们要求 $ G(0) $，符合转移。

不难发现对于固定的 $ k $ 一定对应着固定的 $ idx $，也就是 $ \dfrac{N - \sum_{i = idx + 1}^N G(A_i)}{idx} $ 可以认为是一个常数，令其为 $ C $，若再令 $ B = \dfrac{N}{idx} $，所以有 $ G(k - 1) = B \times G(k) + C $，属于较为简单的转移，考虑矩乘优化，构造矩阵的过程也是平凡的，得到：
$$
\begin{pmatrix}
G(k) & 1
\end{pmatrix} \times
\begin{pmatrix}
B & 0 \\
C & 1
\end{pmatrix}
=
\begin{pmatrix}
G(k - 1), 1
\end{pmatrix}
$$
对于 $ [A_i, A_{i + 1}] $ 之间的部分的所有 $ k $ 显然 $ B $ 和 $ C $ 是相同的，这一部分用矩阵快速幂优化一下即可，最后复杂度应为 $ O(2^3 n \log A_i) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

struct Matrix2{
    ll v00, v01, v10, v11;
    friend Matrix2 operator * (const Matrix2 &a, const Matrix2 &b){
        return Matrix2{
            (a.v00 * b.v00 % MOD + a.v01 * b.v10 % MOD) % MOD,
            (a.v00 * b.v01 % MOD + a.v01 * b.v11 % MOD) % MOD,
            (a.v10 * b.v00 % MOD + a.v11 * b.v10 % MOD) % MOD,
            (a.v10 * b.v01 % MOD + a.v11 * b.v11 % MOD) % MOD
        };
    }
};
Matrix2 base{1, 0, 0, 1};

ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}
ll inv(ll v){return qpow(v, MOD - 2);}
Matrix2 qpow(Matrix2 a, ll b){
    Matrix2 ret(base), mul(a);
    while(b){
        if(b & 1)ret = ret * mul;
        b >>= 1;
        mul = mul * mul;
    }return ret;
}

int N;
ll A[210000];

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)A[i] = read < ll >();
    Matrix2 ans{0, 1, 0, 0};
    ll cur(0);
    for(int i = N - 1; i >= 1; --i){
        ll B = N * inv(i) % MOD, C = (N - cur) * inv(i) % MOD;
        ans = ans * qpow(Matrix2{B, 0, C, 1}, A[i + 1] - A[i]);
        (cur += ans.v00) %= MOD;
    }printf("%lld\n", (ans.v00 % MOD + MOD) % MOD);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_27 初稿

---

## 作者：foreverlasting (赞：3)

题意：给定一个由非负整数组成的 $n$ 元组 $A=(A_1,A_2,\cdots,A_n)$，其中 $A_1=0$ 且 $A_n>0$。

有 $n$ 个初始值为 $0$ 的计数器。

需要进行下述操作，直到对于每个 $i$，第 $i$ 个计数器均至少为 $A_i$：

> 均匀随机地选定某一个计数器，并将该计数器归零。其他的计数器增加 $1$。

输出操作次数的期望对 $998244353$ 取模的结果。

题解：考虑离散时间鞅那一套逻辑，设当前局面的描述手段为 $\min_i (A_i-a_i)$，终态则为 $0$。设 $f_x$ 表示从 $x$ 开始到终态 $0$ 的期望步数，容易写出转移式，$k\in (A_r,A_{r+1}],f_{k} = \frac{1}{n}(rf_{k-1} + \sum_{j = r + 1}^{n} f_{A_j}) + 1.
$

稍微改写下式子，有 $f_{k-1}=\frac{1}{r}(nf_k-n-\sum_{j=r+1}^n f_{A_j})$

接下来推导出 $f_{A_j}$ 与 $f_{A_{j-1}}$ 的关系，设 $A_{r+1}-A_r=p$，则 $f_{A_r}=\frac{n^p}{r^p}f_{A_{r+1}}-\frac{\frac{n^p}{r^p}-1}{n-r}(n+\sum_{j=r+1}^n f_{A_j})$. 

已知 $f_{A_1}=f_0=0$，要求 $f_{A_n}$. 注意到转移式都是线性的，所以可以一次函数高斯消元，设 $f_{A_n}=x$，我们一路倒推回 $f_{A_1}=0=kx+b$，则可以得到答案了，时间复杂度 $O(n)$。

我代码偷懒写了 $O(n\log A)$。

```cpp
//2022.11.1 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
const int N=2e5+10;
namespace MAIN {
	int n;
	LL a[N];
	inline void MAIN(const int &Case) {
		n=read();
		for(int i=1;i<=n;i++)a[i]=Read();
		Z k=1,b=0,sk=1,sb=0;
		for(int r=n-1;r>=1;r--){
			LL p=a[r+1]-a[r];
			Z pwn=Z(n).qpow(p),pwr=Z(r).qpow(p);
			pwr=pwr.inverse();
			Z pw=pwn*pwr;
			Z K=k*pw,B=b*pw;
			pw-=1,pw*=Z(n-r).inverse();
			K-=sk*pw,B-=pw*(n+sb);
			k=K,b=B,sk+=k,sb+=b;
		}
		printf("%d\n",-b/k);
	}
}
```



---

## 作者：kradcigam (赞：2)

WXQ 给我看的题，想了下就会了，然后调了一年（拷的矩阵板子没 memset）。

最近学习了根据鞅与鞅的停时定理构造势能函数来解决这类操作结束时间的期望的问题。但这道题并不能用这个做法，主要的原因在于终止状态的统计学性质不够优秀，结束状态有无穷多个。

我们考虑观察下性质。首先，如果一个操作序列 $B_1, \cdots, B_n$ 满足条件当且仅当 $\forall i, n - i \ge A_{B_i}$。我们发现对于当前的一段操作，最短的结束时间为 $\max_{i = 1}^{n}\limits A_{B_i} - (n - i)$。于是，一次对 $A_i$ 的操作就相当于对当前的所有数减一，并且在序列中新加入一个数 $A_i$，结束状态为所有数小于等于 $0$。

设 $f_i$ 表示当前序列中的最大值为 $i$ 的期望结束时间，暴力枚举下一次操作是对哪个数操作：

$$f_i=\sum_{i = 1}^{n} f_{\max(i - 1, A_i)}$$

考虑对 $a_i \le i - 1$ 和 $a_i\ge i$ 分开来，设 $s_i$ 表示 $A_i$ 中小于等于 $i-1$ 的个数：

$$f_i=s_i \times  f_{i - 1} + \sum_{i = s_i + 1}^{n} f_{A_i}$$

考虑主元法可以求出目标 $f_{\max_{i=1}^{n}\limits A_i}$，但这道题 $A_i$ 的范围很大。我们发现对于 $[A_i, A_{i+1})$ 的状态，转移是一样的，于是考虑矩阵乘法优化这个过程，复杂度 $O(n \log A)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define SZ(x) (int) x.size() - 1
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); }
template <typename T> void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
const int N = 2e5 + 10, MOD = 998244353;
int n, a[N];
pair <int, int> f[N], sum;
struct WXQ_matrix{
	int n, m;
	int a[5][5];
	WXQ_matrix () {
		ms(a, 0);
	}
	WXQ_matrix operator * (const WXQ_matrix &x) const{
		assert(m == x.n);
		WXQ_matrix z;
		z.n = n; z.m = x.m;
		F(k, 1, m)
			F(i, 1, n)
				F(j, 1, x.m)
					z.a[i][j] = (z.a[i][j] + (ll) a[i][k] * x.a[k][j]) % MOD;
		return z;
	}
};
inline int Quickpow(int x, int y) {
	int ans = 1;
	for (; y; x = (ll) x * x % MOD,y >>= 1)
		if (y & 1) ans = (ll) ans * x % MOD;
	return ans;
}
signed main() {
	read(n);
	F(i, 1, n) read(a[i]);
	sum.first = f[n].first = 1;
	DF(i, n - 1, 1) {
		int k = Quickpow(i, MOD - 2);
		WXQ_matrix t, ans;
		t.n = 2; t.m = 2;
		t.a[1][1] = (ll) n * k % MOD; t.a[1][2] = 0;
		t.a[2][1] = MOD - k; t.a[2][2] = 1;
		ans.n = 2; ans.m = 2;
		ans.a[1][1] = 1; ans.a[1][2] = 0;
		ans.a[2][1] = 0; ans.a[2][2] = 1;
		int kk = a[i + 1] - a[i];
		for (; kk; kk >>= 1, t = t * t)
			if (kk & 1) ans = ans * t;
		f[i].first = ((ll) f[i + 1].first * ans.a[1][1] + (ll) sum.first * ans.a[2][1]) % MOD;
		f[i].second = ((ll) f[i + 1].second * ans.a[1][1] + (ll) (sum.second + n) * ans.a[2][1]) % MOD;
		sum.first = (sum.first + f[i].first) % MOD;
		sum.second = (sum.second + f[i].second) % MOD;
	}
	cout << ((ll) -f[1].second * Quickpow(f[1].first, MOD - 2) % MOD + MOD) % MOD;
	return 0;
}
```

---

