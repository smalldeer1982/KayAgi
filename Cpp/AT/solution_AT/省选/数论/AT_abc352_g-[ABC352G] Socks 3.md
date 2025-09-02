# [ABC352G] Socks 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc352/tasks/abc352_g

高橋君のタンスの中には様々な色の靴下が入っています。 靴下の色は $ 1 $ 以上 $ N $ 以下の整数として表され、色 $ i $ の靴下は $ A_i\ (\geq\ 2) $ 枚入っています。

高橋君は、以下の操作を行うことで今日履く靴下を選ぼうとしています。

- 今までに取り出した靴下の中で同じ色の靴下の $ 2 $ 枚組が作れるようになるまで、タンスの中からランダムに等確率で $ 1 $ 枚の靴下を取り出すことを繰り返す。 なお、一度取り出した靴下はタンスの中には戻さない。

高橋君がタンスから靴下を取り出す回数の期待値を $ \text{mod\ }\ 998244353 $ で求めてください。

期待値を $ \text{mod\ }\ 998244353 $ で求めるとは求める期待値は必ず有理数になることが証明できます。 また、この問題の制約下では、期待値を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。 このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まるので、この $ z $ を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 3\times\ 10^5 $
- $ 2\leq\ A_i\ \leq\ 3000 $
- 入力は全て整数

### Sample Explanation 1

例えば、以下のように操作を行うことが考えられます。 1. タンスの中から色 $ 1 $ の靴下を $ 1 $ 枚取り出す。タンスの中には色 $ 1 $ の靴下が $ 1 $ 枚と色 $ 2 $ の靴下が $ 2 $ 枚残っている。 2. タンスの中から色 $ 2 $ の靴下を $ 1 $ 枚取り出す。タンスの中には色 $ 1,2 $ の靴下が $ 1 $ 枚ずつ残っている。 3. タンスの中から色 $ 1 $ の靴下を $ 1 $ 枚取り出す。今までに取り出した靴下は色 $ 1 $ の靴下が $ 2 $ 枚と色 $ 2 $ の靴下が $ 1 $ 枚であり、この中で色 $ 1 $ の靴下の $ 2 $ 枚組が作れるので操作を終了する。 この例の場合、高橋君がタンスから靴下を取り出す回数は $ 3 $ 回です。 高橋君がタンスから靴下を取り出す回数は $ \frac{2}{3} $ の確率で $ 3 $ 回、$ \frac{1}{3} $ の確率で $ 2 $ 回なので、求める期待値は $ 3\times\ \frac{2}{3}\ +\ 2\times\ \frac{1}{3}\ =\ \frac{8}{3}\ \equiv\ 665496238\ \pmod\ {998244353} $ です。

## 样例 #1

### 输入

```
2
2 2```

### 输出

```
665496238```

## 样例 #2

### 输入

```
1
352```

### 输出

```
2```

## 样例 #3

### 输入

```
6
1796 905 2768 253 2713 1448```

### 输出

```
887165507```

# 题解

## 作者：Milthm (赞：7)

这个期望值可以用一堆概率加起来求，具体地说，设 $p_i$ 表示在第 $i$ 次及以后才抽到两个颜色相同袜子的概率。因为最多挑 $(n+1)$ 次就一定能挑出两个颜色相同的袜子（抽屉原理），所以答案为 $\sum\limits_{i=1}^{n+1}p_i$。

然后 $p_i$ 其实就是前 $(i-1)$ 只袜子都不同的概率，也就是符合条件的数量除以总数，那么就有：

$$p_{i+1}=\frac{\sum\limits_{b_1\sim b_i}\prod\limits_{j=1}^i a_{b_j}}{C_{s}^{i}}$$

其中 $s=\sum a_i$。

然后这个分子其实就是 $[x^i]\prod\limits_{i=1}^n(1+xa_i)$，可以用 NTT 求，但是我不会，所以我用了 Atcoder Library 自带的 NTT。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all> 
using namespace std;
using namespace atcoder;
using mint=modint998244353;
vector<mint> calc(vector<int>&a,int l,int r){
	if(r-l==1)return {1,a[l]};
	int mid=(l+r)>>1;
	return convolution(calc(a,l,mid),calc(a,mid,r));
}
int n,sum;
vector<int>a;
mint ans,C=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		int x;cin>>x;
		a.push_back(x);sum+=x;
	}
	vector<mint>qwq=calc(a,0,n);
	for(int i=0;i<=n;++i){
		ans+=qwq[i]/C;C*=sum-i;C/=i+1;
	}
	cout<<ans.val();
	return 0;
}

```

---

## 作者：masterhuang (赞：5)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)！第 $18$ 题。

~~我起了，一枪秒了。~~

**ABC g** 就这素质了，感觉好熟悉的题，但一下子又找不到原题。

套路性的，设抽袜子次数为 $X$。则 $\mathbb{E}(X)=\sum\limits_{k=0}^n \mathbb{P}(X>k)$。

考虑 $\mathbb{P}(X>k)$ 的意义，即抽 $k$ 次后袜子仍两两不同的概率。

首先算方案数，设 $s=\sum\limits_{i=1}^n a_i$，显然是 $\prod\limits_{i=0}^{k-1}(s-i)=k!\dbinom{s}{k}$。

考虑两两不同的方案数，颜色 $i$ 的生成函数为：$1+a_ix$，即不选有一种方案，选一个有 $a_i$ 种方案。

而最后 $k$ 个袜子可以任意排列，于是方案数为：$k![x^k]\prod\limits_{i=1}^n(1+a_ix)$。

于是 $\mathbb{E}(X)=\sum\limits_{k=0}^n \dfrac{k![x^k]\prod\limits_{i=1}^n(1+a_ix)}{k!\binom{s}{k}}=\sum\limits_{k=0}^n \dfrac{[x^k]\prod\limits_{i=1}^n(1+a_ix)}{\binom{s}{k}}$.

于是只需求出 $f(x)=\prod\limits_{i=1}^n(1+a_ix)$ 的 $0\sim n$ 次项系数即可。

这是一个经典分治 $\texttt{NTT}$ 问题，复杂度 $O(n\log^2 n)$，$\texttt{NTT}$ 不要太慢就足以通过。

求 $\dbinom{s}{k}$ 利用 $\dfrac{s-k}{k+1}\dbinom{s}{k}=\dbinom{s}{k+1}$ 递推即可。

---

记 $a_i=k$ 的个数为 $c_k$，$m=\max a$，则 $f(x)=\prod\limits_{i=2}^m(1+ix)^{c_i}=\prod\limits_{i=2}^m g_i(x)$。

单个 $g$ 直接二项式定理展开即可，而后对 $g_2\sim g_m$ 做分治 $\texttt{NTT}$，此时复杂度应为 $O(n\log n\log m)$，更优秀一点，但我懒得写啦，自己上面那个做法已经跑飞快了。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353,N=12e5+5;
int n,s,f[N],a[N],w[N],*b[N],mmax,ans;
inline int rd()
{
    int x=0,zf=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') (ch=='-')and(zf=-1),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*zf;
}
inline void wr(int x)
{
    if(x==0) return putchar('0'),putchar('\n'),void();
    int num[35],len=0;
    while(x) num[++len]=x%10,x/=10;
    for(int i=len;i>=1;i--) putchar(num[i]+'0');
    putchar('\n');
}
inline int bger(int x){return x|=x>>1,x|=x>>2,x|=x>>4,x|=x>>8,x|=x>>16,x+1;}
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline void init(int mmax)
{
	for(int i=1,j,k;i<mmax;i<<=1)
		for(w[j=i]=1,k=ksm(3,(mod-1)/(i<<1)),j++;j<(i<<1);j++)
			w[j]=1ll*w[j-1]*k%mod;
}
inline void DNT(int *a,int mmax)
{
	for(int i,j,k=mmax>>1,L,*W,*x,*y,z;k;k>>=1)
		for(L=k<<1,i=0;i<mmax;i+=L)
			for(j=0,W=w+k,x=a+i,y=x+k;j<k;j++,W++,x++,y++)
				*y=1ll*(*x+mod-(z=*y))* *W%mod,*x=md(*x+z);
}
inline void IDNT(int *a,int mmax)
{
	for(int i,j,k=1,L,*W,*x,*y,z;k<mmax;k<<=1)
		for(L=k<<1,i=0;i<mmax;i+=L)
			for(j=0,W=w+k,x=a+i,y=x+k;j<k;j++,W++,x++,y++)
				z=1ll* *W* *y%mod,*y=md(*x+mod-z),*x=md(*x+z);
	reverse(a+1,a+mmax);
	for(int inv=ksm(mmax,mod-2),i=0;i<mmax;i++) a[i]=1ll*a[i]*inv%mod;
}
inline void NTT(int *a,int *b,int n,int m)
{
	mmax=bger(n+m);DNT(a,mmax);DNT(b,mmax);
	for(int i=0;i<mmax;i++) a[i]=1ll*a[i]*b[i]%mod;IDNT(a,mmax);
}
void sol(int l,int r,int wz)
{
	b[wz]=new int[r-l+2];
	if(l==r) return b[wz][0]=1,b[wz][1]=a[l],void();
	int mid=(l+r)>>1;sol(l,mid,wz<<1);sol(mid+1,r,wz<<1|1);
	static int A[N],B[N];for(int i=0;i<bger(r-l+3);i++) A[i]=B[i]=0;
	for(int i=0;i<=mid-l+1;i++) A[i]=b[wz<<1][i];
	for(int i=0;i<=r-mid;i++) B[i]=b[wz<<1|1][i];
	NTT(A,B,mid-l+2,r-mid+1);for(int i=0;i<=r-l+1;i++) b[wz][i]=A[i];
}
int main()
{
	n=rd();init(bger(n<<1));for(int i=1;i<=n;i++) s=md(s+(a[i]=rd()));
	f[0]=1;for(int i=0;i<n;i++) f[i+1]=1ll*f[i]*(i+1)%mod*ksm(s-i,mod-2)%mod;
	sol(1,n,1);for(int i=0;i<=n;i++) ans=(ans+1ll*b[1][i]*f[i])%mod;
	return wr(ans),0;
}
```

---

## 作者：ChrysanthBlossom (赞：4)

设期望时间为 $t$，在第 $i$ 次仍未停下的概率为 $p_i$。

那么根据期望的线性性，$t=1+\sum\limits^{n}_{i=1}p_i$。

考虑求出每个 $p_i$。

设 $s=\sum\limits^{n}_{i=1}a_i$。显然此时概率等于能每个只取一次的方案数除以总的方案数。设当前时间为 $d$，分母肯定是 $\binom{s}{d}$，考虑 dp 出来分子（即取出 $d$ 个互不相同的方案数）。

设 $f_{i,j}$ 表示考虑了前 $i$ 个颜色，取出来 $j$ 个且互不相同的方案数。由此，$p_d=\dfrac{f_{n,d}}{\binom{s}{d}}$。

转移式显然：

 $$f_{i,j}=f_{i-1,j-1} \times A_i + f_{i-1,j}$$
 
初始时 $f_{0,0}=1$。

然后你观察到这玩意显然就是若干个 $1+A_ix$ 的卷积，于是直接分治 + NTT 即可。

对于求 $p_d$ 的分母，可以把他拆成 $\dfrac{s^{\underline{d}}}{d!}$ ，然后下降幂和阶乘分别维护。

代码：

```cpp
#include<bits/stdc++.h> 
#define ri register int
#define ll long long
#define ld long double
#define mkp make_pair
using namespace std;
const int maxn=3e5+7;
ll qpow(ll a,ll b,ll p){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
const int mod=998244353;
const int G=3;
const int invG=qpow(G,mod-2,mod);
int n;
int A[maxn];
struct Poly{
	vector<ll>f;
	vector<int>rev;
	int limit;
	int siz;
	void resize(int sizz){
		siz=sizz;
		limit=1;
		while(limit<siz)limit<<=1;
		f.resize(limit);
		rev.resize(limit);
	}
	void init(){
		for(ri i=1;i<limit;i++){
			rev[i]=((rev[i>>1]>>1)|(i&1?limit>>1:0));
		}
	}
	void NTT(bool r){
		init();
		for(ri i=0;i<limit;i++){
			if(i<rev[i])swap(f[i],f[rev[i]]);
		}
		for(ri len=2;len<=limit;len<<=1){
			int dwg=qpow(r?G:invG,(mod-1)/len,mod);
			int pa=len>>1;
			for(ri i=0;i<limit;i+=len){
				ll bf=1;
				for(ri j=i;j<i+pa;j++){
					ll t=bf*f[j+pa]%mod;
					f[j+pa]=(f[j]-t+mod)%mod;
					f[j]=(f[j]+t)%mod;
					bf=bf*dwg%mod;
				}
			}
		}
		if(!r){
			ll invn=qpow(limit,mod-2,mod);
			for(ri i=0;i<limit;i++){
				f[i]=f[i]*invn%mod;
			}
		}
	}
	void times(Poly b){
		for(ri i=0;i<limit;i++){
			f[i]=f[i]*b.f[i]%mod;
		}
	}
};
Poly solve(int l,int r){
	if(l==r){
		Poly a;
		a.resize(2);
		a.f[0]=1;
		a.f[1]=A[l];
		return a;
	}
	int mid=l+r>>1;
	Poly a=solve(l,mid);
	Poly b=solve(mid+1,r);
	int siza=a.siz,sizb=b.siz;
	a.resize(siza+sizb);
	b.resize(siza+sizb);
	a.NTT(1);
	b.NTT(1);
	a.times(b);
	a.NTT(0);
	return a;
}
ll jc[maxn];
ll xjm[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	ll sum=0;
	for(ri i=1;i<=n;i++){
		cin>>A[i];
		sum+=A[i];
	}
	sum%=mod;
	Poly f=solve(1,n);
	ll fm=1;
	ll ans=0;
	xjm[0]=sum;jc[0]=1;
	for(ri i=1;i<=n;i++){
		jc[i]=jc[i-1]*i%mod;
		xjm[i]=xjm[i-1]*(sum-i)%mod;
	}
	for(ri i=1;i<=n;i++){
		ans=(ans+f.f[i]*jc[i]%mod*qpow(xjm[i-1],mod-2,mod)%mod)%mod;
	}
	cout<<(ans+1)%mod<<endl;
	return 0;
}
```

---

## 作者：Starrykiller (赞：4)

和分治 NTT 爆了。

我们有如下引理：

> **Lemma 1**
> $$ \sum_{i=1}^{n}i\cdot \mathrm{Prob}(X=i)=\sum_{i=1}^n \mathrm{Prob}(X\ge i)$$
> 
> **Proof.** 
> 
> $$
> \begin{aligned}
> \text{LHS}&=\sum_{i=1}^n\mathrm{Prob}(X=i)\sum_{j=1}^n 1\\
> &=\sum_{j=1}^n \sum_{i=j}^n\mathrm{Prob}(X=i)\\
> &=\sum_{i=1}^n \mathrm{Prob}(X\ge i)=\text{RHS}.\\
> \square
> 
> \end{aligned}
> $$

那么我们所求就是 $\sum_{i=1}^{n+1} \mathrm{Prob}(X\ge i)$，其中 $\mathrm{Prob}(X\ge i)$ 代表在第 $i$ 次或以后挑到一双颜色相同的袜子（且之前没有挑到过颜色相同的袜子）的概率。

考虑怎么计算 $\mathrm{Prob}(X\ge i)$。不难发现，这等效于**在前 $(i-1)$ 轮里面挑到的袜子颜色都不同**的概率。记 $S=\sum_{i=1}^n A_i$，则 

$$\mathrm{Prob}(X\ge \textcolor{red}{i+1})=\frac{\sum_{b_1,b_2,\cdots,b_{i}}\prod_{j=1}^i A_{b_j} }{{S\choose i}}$$


（符合条件的方案数除以总方案数）

分子的式子是一个经典问题（[P6012](https://www.luogu.com.cn/problem/P6012)），设 $F(z)=\prod_{i=1}^n (1+A_iz)$，那么分子就是 $[z^i]F(z)$。

$F(z)$ 可以利用分治 NTT 求，由 $T(n)=2T(\frac{n}{2})+\Theta(n\log n)$ 解得 $T(n)=\Theta(n\log^2 n)$。

代码很好写就不放了。

---

## 作者：lss_ak_gcd (赞：2)

考虑设 $f_i$ 表示当前选择了恰好 $i$ 只袜子，分别为 $D_1,D_2,D_3,\ldots,D_i$，且不存在 $j_1,j_2$ 满足 $1\le j_1<j_2\le n$ 满足 $D_{j_1}\neq D_{j_2}$ 的概率。根据鸽巢原理可以知道 $n$ 个不同的数，最多选择 $n+1$ 个数就可以得到两只相同的袜子，证明显然。

问题在于，若目前已知 $f_{1\sim n}$，则答案怎么计算。容易发现答案为 $\sum\limits_{i=1}^n f_i$。证明：若当前选择到第 $2$ 个袜子，则：

+ 若目前已经选择了第 $1$ 个袜子，则肯定不存在两个不同的袜子但是它们的颜色相同。此时答案加上了 $f_1$。
+ 若目前开始选择第 $2$ 个袜子并选择完了，则：
  + 若第一个袜子的颜色和第二个袜子的颜色相同，则该部分的答案不会累加到 $f_2$ 上，只会累加到 $f_1$。
  + 若第一个袜子的颜色和第二个袜子的颜色不同，则答案在 $f_1$ 算过之后又在 $f_2$ 算了一遍，恰好算了正确的两次答案。
  
$i$ 更大的情况同理。所以证明了结论。问题在于如何求出 $f_i$ 的值。

容易发现在总的 $\sum\limits_{i=1}^n a_i$ 只袜子中选出 $i$ 只袜子的不同方案数为 $\binom{\sum\limits_{j=1}^n a_j}{i}$，而满足 $f_i$ 定义的**方案数**为所有满足每一个元素都不重复且都在 $1\sim n$ 中的包含 $i$ 个元素的序列 $S$ 的 $\prod\limits_{j\in S} a_j$ 的和。完整的写就是：

$$
f_i=\frac{\sum\limits_{S_1,S_2,S_3,\ldots,S_i} \prod\limits_{j=1}^n a_{S_j}}{\binom{\sum\limits_{j=1}^n a_j}{i}}
$$

~~于是我们得到了一个指数级的求答案算法。~~

然后根据 P6012 的经典套路，上面这个式子的分子的每一项的系数为 $[x^i]\prod\limits_{i=1}^n(1+xa_i)$ 的第 $i$（$0\le i\le n$）项系数。所以说可以把每一个这样的多项式都直接乘起来然后直接求答案。这样就有了一个 $O(n^2)$ 的解。

然后你发现这个东西可以分治 NTT，所以就可以在 $O(n\log^2n)$ 的时间复杂度内解决这个问题了。因为这是 ATcoder，所以你可以用 lib 而不是手写 NTT。

```cpp
using mint=atcoder::modint998244353;vector<int>a;
vector<mint>cdq(int l,int r){
    if(l==r)return{1,a[l]};int mid=l+r>>1;
    return atcoder::convolution(cdq(l,mid),cdq(mid+1,r));
}
auto main()[[O3]]->signed{
    PRESOLVE int n;cin>>n;a.resize(n);F(i,0,n-1)cin>>a[i];
    int smz=accumulate(a.begin(),a.begin()+n,0ll);vector<mint>res=cdq(0,n-1);
    mint s=smz,binom=1,ss=0;F(i,0,n)ss+=res[i]/binom,binom=binom*(s-i)/(i+1);cout<<ss.val()<<'\n';
}
```

---

## 作者：songhongyi (赞：0)

只需要求第 $i$ 次仍然无重的概率 $p_i$，则答案为 $\sum{p_i}$。注意到当 $i > n$ 时，显然据抽屉原理有 $p_i =0$。

那么取 $i$ 次袜子的总次数是 $\binom{\sum a}{i}$，这个可以递推得出。现在只需要求有多少方案取得的是互不相同的。这个是经典问题，其等价于 $[x^i]\prod(1+a_jx)$，可以认为成每个括号内如果选了 $1$ 就是没取，否则就是取了。而 $i$ 次项系数保证了取了恰 $i$ 个。这个系数可以通过分治 NTT 求得，复杂度 $O(n \log^2 n)$。

---

