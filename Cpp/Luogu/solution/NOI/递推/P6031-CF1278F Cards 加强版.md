# CF1278F Cards 加强版

## 题目背景

[原题链接](https://www.luogu.com.cn/problem/CF1278F)

## 题目描述

有 $m$ 张牌，其中有一张是王牌。将这些牌均匀随机打乱 $n$ 次，设有 $x$ 次第一张为王牌，求 $x^k$ 的期望值。

答案对 $998244353$ 取模。

## 说明/提示

【数据范围】  
对于 $20\%$ 的数据，$1\le k \le 5000$；  
对于 $40\%$ 的数据，$1\le k \le 10^5$；  
对于 $100\%$ 的数据，$1\le k \le 10^7$，$1\le n,m \le 998244352$。

Solution：iostream  
Data：NaCly\_Fish

## 样例 #1

### 输入

```
1234 2345 3456```

### 输出

```
398700213```

## 样例 #2

### 输入

```
998244352 1337 5000```

### 输出

```
326459680```

## 样例 #3

### 输入

```
233333333 114514 9982443```

### 输出

```
825888958```

# 题解

## 作者：command_block (赞：24)

一道 组合数&斯特林数 处理的练习题。

------------

可以观察出,每次洗牌是独立的。

设第一张是王牌的概率为$p=\frac{1}{m}$,不是的概率即为$1-p$

那么就是要求计算如下式子

$$\sum\limits_{i=0}^n\dbinom{n}{i}p^i(1-p)^{n-i}i^k$$

意义 : 枚举洗出王牌的次数,选出若干轮,乘上对应概率和贡献。

然后观察到$n$大,$k$小,容易想到使用第二类斯特林数展开幂次。

有$m^n=n$个球放进$m$个有区别的箱子里,允许空盒的方案数。

第二类斯特林数$\begin{Bmatrix}n\\m\end{Bmatrix}$为将$n$个球放入$m$个无区别的盒子中,无空盒的方案数。

$$m^n=\sum\limits_{i=0}^{\min(n,m)}\dbinom{m}{i}i!\begin{Bmatrix}n\\i\end{Bmatrix}$$

等号右边的组合意义是 : 选出盒子,盒子排列,向盒子里放球。

代入最开始的式子可得 :

$$\sum\limits_{i=0}^n\dbinom{n}{i}p^i(1-p)^{n-i}\sum\limits_{j=0}^k\dbinom{i}{j}j!\begin{Bmatrix}k\\j\end{Bmatrix}$$

$$\sum\limits_{j=0}^k\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits_{i=0}^n\dbinom{i}{j}\dbinom{n}{i}p^i(1-p)^{n-i}$$

考虑后面的$\sum\limits_{i=0}^n\dbinom{i}{j}\dbinom{n}{i}p^i(1-p)^{n-i}$

广义的情形 : $\sum\limits_{i=0}^n\dbinom{i}{j}\dbinom{n}{i}a^ib^{n-i}$

$$=\sum\limits_{i=0}^n\dfrac{i!n!}{j!(i-j)!i!(n-i)!}a^ib^{n-i}$$

$$=\dfrac{1}{j!}\sum\limits_{i=0}^n\dfrac{n!}{(i-j)!(n-i)!}a^ib^{n-i}$$

$$=\dfrac{n!}{j!(n-j)!}\sum\limits_{i=0}^n\dfrac{(n-j)!}{(i-j)!(n-i)!}a^ib^{n-i}$$

$$=a^j\dbinom{n}{j}\sum\limits_{i=0}^n\dbinom{n-j}{i-j}a^ib^{n-i}$$

$$=a^j\dbinom{n}{j}\sum\limits_{i=0}^{n-j}\dbinom{n-j}{i}a^ib^{n-i-j}$$

$$=a^j\dbinom{n}{j}(a+b)^{n-j}$$

注意对于$n\leq k$不合法,此时直接按照最初的暴力式计算即可。

后面的部分就是$\dbinom{n}{j}p^j$,代回原式可得

$$=\sum\limits_{j=0}^k\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}p^j$$

求出一行第二类斯特林数就可以计算了,

原题可以直接$O(k^2)$递推。

使用NTT,复杂度为$O(klogk)$。

我们还不满足于这个复杂度,考虑对

$$m^n=\sum\limits_{i=0}^{m}\dbinom{m}{i}i!\begin{Bmatrix}n\\i\end{Bmatrix}$$

二项式反演得到:

$$\begin{Bmatrix}n\\m\end{Bmatrix}=\frac{1}{m!}\sum\limits_{i=0}^{m}(-1)^{m-i}\dbinom{m}{i}i^n$$

回代到最后的式子

$$=\sum\limits_{j=0}^k\frac{1}{j!}\sum\limits_{i=0}^{j}(-1)^{j-i}\dbinom{j}{i}i^kj!\dbinom{n}{j}p^j$$

$$=\sum\limits_{i=0}^{k}(-1)^ii^k\sum\limits_{j=i}^k\dbinom{n}{j}\dbinom{j}{i}(-p)^j$$

$$=\sum\limits_{i=0}^{k}(-1)^ii^k\sum\limits_{j=i}^k\dfrac{n!j!}{j!(n-j)!i!(j-i)!}(-p)^j$$

$$=\sum\limits_{i=0}^{k}(-1)^ii^k\dbinom{n}{i}\sum\limits_{j=i}^k\dbinom{n-i}{j-i}(-p)^j$$

$$=\sum\limits_{i=0}^{k}i^k\dbinom{n}{i}p^i\sum\limits_{j=0}^{k-i}\dbinom{n-i}{j}(-p)^j$$

观察后面的$S(i)=\sum\limits_{j=0}^{k-i}\dbinom{n-i}{j}(-p)^{j}$,似乎并没有一个很好的封闭形式。

我们考虑裂开组合数递推(手残裂错了一次qwq):

$=\sum\limits_{j=0}^{k-i}\Bigg(\dbinom{n-i-1}{j}+\dbinom{n-i-1}{j-1}\Bigg)(-p)^{j}$

$=S(i+1)+\dbinom{n-i-1}{k-i}(-p)^{k-i}+\sum\limits_{j=0}^{k-i}\dbinom{n-i-1}{j-1}(-p)^{j}$

令$C=S(i+1)+\dbinom{n-i-1}{k-i}(-p)^{k-i}$。

$=C+(-p)\sum\limits_{j=0}^{k-i}\dbinom{n-i-1}{j-1}(-p)^{j-1}$

$=C+(-p)\sum\limits_{j=0}^{k-i-1}\dbinom{n-i-1}{j}(-p)^{j}$

得到$S(i)=C+(-p)S(i+1)$

即$S(i)=(1-p)S(i+1)+\dbinom{n-i-1}{k-i}(-p)^{k-i}$,边界是$S(k)=1$

回到原式$=\sum\limits_{i=0}^{k}i^k\dbinom{n}{i}p^iS(i)$

线性筛一下$id_k$就可以$O(k)$完成了。

$\dbinom{n}{i}$似乎不是很好算,考虑变成$\dfrac{n^{\underline i}}{i!}$,阶乘逆元预处理,下降幂边算边乘。

对于$\dbinom{n-i-1}{k-i}$就更烦了。

有吸收公式$\dfrac{n-i-1}{k-i}\dbinom{n-i-1}{k-i}=\dfrac{}{}\dbinom{n-(i+1)-1}{k-(i+1)}$

这还需要额外的求逆元,似乎也可以线性筛。

代码里使用了较多卡常技巧。

```cpp
#include<algorithm>
#include<cstdio>
#define ll long long
#define mod 998244353
#define MaxK 10050000
using namespace std;
ll powM(ll a,int t=mod-2)
{
  ll ans=1;
  while(t){
    if (t&1)ans=ans*a%mod;
    a=a*a%mod;
    t>>=1;
  }return ans;
}
int n,m,k,c;
int p[MaxK],id[MaxK],inv[MaxK],tn;
void getsth(int lim)
{
  inv[1]=id[1]=1;
  for (int i=2;i<=lim;i++){
    if (!id[i]){
      id[i]=powM(p[++tn]=i,k);
      inv[i]=powM(i);
    }for (int j=2,t;j<=tn&&(t=i*p[j])<=lim;j++){
      id[t]=1ll*id[i]*id[p[j]]%mod;
      inv[t]=1ll*inv[i]*inv[p[j]]%mod;
      if (i%p[j]==0)break;
    }
  }
}
void solve1()
{
  getsth(k);
  int p=powM(m),q=mod+1-p;
  ll x1=1,x2=powM(q,n),C=1,ans=0;
  q=powM(q);
  for (int i=1;i<=k;i++){
    x1=x1*p%mod;
    x2=x2*q%mod;
    C=C*(n-i+1)%mod*inv[i]%mod;
    ans=(ans+x1*x2%mod*C%mod*id[i])%mod;
  }printf("%lld",ans);
}
int S[MaxK];
void solve2()
{
  getsth(k);
  int p=powM(m);
  ll C=1,x=1;S[k]=1;
  for (int i=k-1;i;i--){
    C=C*(n-i-1)%mod*inv[k-i]%mod;
    x=x*(mod-p)%mod;
    S[i]=(1ll*S[i+1]*(mod+1-p)+C*x)%mod;
  }
  C=x=1;ll ans=0;
  for (int i=1;i<=k;i++){
    x=x*p%mod;
    C=C*(n-i+1)%mod*inv[i]%mod;
    ans=(ans+S[i]*C%mod*id[i]%mod*x)%mod;
  }printf("%lld",ans);
}
int main()
{
  scanf("%d%d%d",&n,&m,&k);
  if (m==1){printf("%lld",powM(n,k));return 0;}
  if (n<=k)solve1();
  else solve2();
  return 0;
}
```


---

## 作者：forest114514 (赞：11)

### P6031 CF1278F Cards 加强版

斯特林数被我杀死了。

感觉 analysis 大佬的那个 binomial sums 做法稍微复杂了点，所以我这里分享了个简单点的 binomial sums 做法。

答案式子列出来是容易的，显然每次王牌出现在第一个的概率是 $p=\frac{1}{m}$。
$$
\sum\limits_{i=0}^{n}\binom{n}{i}p^i(1-p)^{n-i}i^k
$$
然后你意识到这不就是 **P6667 [清华集训2016] 如何优雅地求和**？其中 $f(i)=i^k$ 的点值容易线性筛出的，然后套那个题的 binomial sums 做法就完了。

>求 $\sum\limits_{i=0}^{n}f(i)\binom{n}{i}a^{i}(1-a)^{n-i}$，给了 $m$ 次多项式 $f(x)$ 的 $0\sim m$ 的点值。
>
>首先对于 $a=0/1$ 或 $m\leq n$ 这些 corner cases 都是可以容易直接求的先求了。
>
>给了点值，相当于给咱们 $b_{X}=\sum\limits_{i=0}^{m} f_{i} [\frac{x^{i}}{i!}](e^{x})^{X}$，求：
>$$
>\sum\limits_{j=0}^mf_{j}[\frac{x^j}{j!}]\sum\limits_{i=0}^{n}\binom{n}{i}a^{i}(1-a)^{n-i}e^{ix}
>$$
>可以构造出 $F(x)=(ax+(1-a))^n$，需要进行截断。
>
>直接上 ODE！还是设 $\mathbb F(x+1)=F(x+1)\bmod x^{m+1}$，显然根据 binomial sums 的结论我们的答案就是 $\sum\limits_{i=0}^{m}b_i[x^i]\mathbb F(x)$。
>$$
>\begin{aligned}
>anF(x)-(ax-a+1)F'(x)&=0\\
>anF(x+1)-(ax+1)F'(x+1)&=0\\
>an\mathbb F(x+1)-(ax+1)\mathbb F'(x+1)&=(an-am)x^m[x^m]F(x+1)\\
>an\mathbb F(x)-(ax-a+1)\mathbb F'(x)&=(an-am)\binom{n}{m}a^m(x-1)^m\\
>(an-ai)f_{i}+(a-1)(i+1)f_{i+1}&=(an-am)\binom{n}{m}\binom{m}{i}a^m(-1)^{m-i}
>\end{aligned}
>$$
>然后做完了，时间复杂度 $O(m)$。

放回本题就是 $O(k)$ 啦！

code：
```cpp
const int N=1e7+100,mod=998244353;
int n,m,k,fac[N],ifac[N],inv[N];
LL ksm(LL a,LL b){
	LL res=1;for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;return res;
}
LL C(int n,int m){
	return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
int pri[N],tot,pw[N];
bool vis[N];
void sieve(){
	pw[1]=1;
	rep(i,2,k){
		if(!vis[i]) pri[++tot]=i,pw[i]=ksm(i,k);
		for(int j=1;j<=tot&&i*pri[j]<=k;++i){
			vis[i*pri[j]]=1;
			pw[i*pri[j]]=1ll*pw[i]*pw[pri[j]]%mod;
			if(i%pri[j]==0) break;
		}
	}
}
bool _ED;
signed main(){
	fprintf(stderr,"%.20lf MB\n",(&_ST-&_ED)/1048576.0);
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,m,k),m=ksm(m,mod-2);
	if(m==1) return write(ksm(n,k),'\n'),0;
	sieve();
	fac[0]=1;
	rep(i,1,k) fac[i]=1ll*fac[i-1]*i%mod;
	ifac[k]=ksm(fac[k],mod-2);
	per(i,k-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
	if(n<=k){
		LL ans=0,iv=ksm((mod+1-m)%mod,mod-2),mul=ksm((mod+1-m)%mod,n)*iv%mod*m%mod;
		rep(i,1,n) ans=(ans+C(n,i)*mul%mod*pw[i])%mod,mul=mul*iv%mod*m%mod;
		write(ans,'\n');return 0;
	}
	LL tmp=ksm(m,k+1)*(n-k)%mod*ifac[k]%mod,ans=0;
	inv[0]=1;
	rep(i,1,k) inv[i]=1ll*inv[i-1]*(n-i)%mod,tmp=tmp*(n-i+1)%mod;
	LL INV=ksm(inv[k],mod-2),f=0,ip=ksm(m,mod-2);
	per(i,k,1) {
		inv[i]=1ll*inv[i-1]*INV%mod,INV=INV*(n-i)%mod;
		LL res=tmp*C(k,i)%mod;
		if((k-i)&1) res=mod-res;
		res=(res+1ll*(mod+1-m)*(i+1)%mod*f)%mod;
		f=res*ip%mod*inv[i]%mod;
		ans=(ans+f*pw[i])%mod;
	}
	write(ans,'\n');
	fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：Albedo (赞：6)

# Introduction 

`*2600`

# Solution

我们发现答案的表达式如下式子：
$$
\dfrac{\sum_{i=0}^{n} i^k\times [(m-1)!]^i\times (m-1)^{n-i}\times [(m-1)!]^{n-i}\times \binom{n}{i}}{(m!)^n}
$$

$$
\dfrac{\sum_{i=0}^{n} i^k\times [(m-1)!]^n\times (m-1)^{n-i}\times \binom{n}{i}}{(m!)^n}
$$

$$
\dfrac{\sum_{i=0}^{n} i^k\times (m-1)^{n-i}\times \binom{n}{i}}{m^n}
$$

$$
\dfrac{\sum_{i=0}^{n} \sum_{j=0}^{k}{k \brace j}\times j!\times \binom{i}{j}\times (m-1)^{n-i}\times \binom{n}{i}}{m^n}
$$

$$
\dfrac{\sum_{i=0}^{n} \sum_{j=0}^{k}{k \brace j}\times j!\times \binom{n-j}{i-j}\times (m-1)^{n-i}\times \binom{n}{j}}{m^n}
$$

考虑调换求和顺序：
$$
\sum_{j=0}^{k} {k \brace j}\times j!\times \binom{n}{j}\times \sum_{i=0}^{n-j}\binom{n-j}{i}\times (m-1)^{n-i-j}
$$

$$
\sum_{j=0}^{k} {k \brace j}\times j!\times \binom{n}{j}\times m^{n-j}
$$

$$
\sum_{j=0}^{k} m^{n-j}\sum_{G=0}^{j}(-1)^{j-G}\times G^k\times \binom{j}{G}\times \binom{n}{j}
$$

$$
\sum_{j=0}^{k} m^{n-j}\sum_{G=0}^{j}(-1)^{j-G}\times G^k\times \binom{n-G}{j-G}\times \binom{n}{G}
$$

$$
\sum_{G=0}^{k} G^k\times \binom{n}{G}\times \sum_{j=0}^{k-G} \binom{n-G}{j}\times (-1)^{j}\times m^{n-G-j}
$$

现在问题的优化方向就在这个式子：
$$
\sum_{j=0}^{k-G} \binom{n-G}{j}\times (-1)^{j}\times m^{n-G-j}
$$
考虑能不能递推做，首先考虑 $ G=k $ 时的情况，这时候显然有 $ F(k)=\binom{n-k}{0}\times m^{n-k} $ ，考虑继续写出 $ F(k-1)=\binom{n-k+1}{0}\times 1\times m^{n-k+1}+\binom{n-k+1}{1}\times (-1)\times m^{n-k} $ 。

这时候还发现不了规律，但是我们知道有一个组合恒等式：$ \binom{m}{n}=\binom{m-1}{n}+\binom{m-1}{n-1}$ 。

那么考虑把 $ F(k-1) $ 化开可以得到下面的式子：
$$
F(k-1)=\binom{n-k}{0}\times 1\times m^{n-k+1}+\binom{n-k}{1}\times (-1)\times m^{n-k}+\binom{n-k}{0}\times (-1)\times m^{n-k}
$$

$$
F(k-2)=\binom{n-k+1}{0}\times 1\times m^{n-k+2}+\binom{n-k+1}{1}\times (-1)\times m^{n-k+1}+\binom{n-k+1}{0}\times (-1)\times m^{n-k+1}+\binom{n-k+1}{2}\times 1\times m^{n-k}+\binom{n-k+1}{1}\times 1\times m^{n-k}
$$

$$
F(k-2)=F(k-1)\times (m-1)+\binom{n-k+1}{2}\times m^{n-k}
$$

$$
F(k-1)=F(k)\times (m-1)+\binom{n-k}{1}\times (-1)\times m^{n-k}
$$

然后发现可以这样子递推下来，然后就做完了。

# Code

```cpp
long long pow(long long x,long long y,long long p){
	long long ans=1;
	for (;y;y>>=1,x=x*x % p) 
	   if (y&1) ans=ans*x % p;
    return ans;
}
int main() {
//	freopen("testdata.in","r",stdin);
cin>>n>>m>>K;MOD=998244353;
V[1]=1;
for (i=2;i<=K;i++){
	if (vis[i]==false){
		V[i]=pow(i,K,MOD);prim[++len]=i;
       }
    for  (j=1;j<=len&&prim[j]*i<=K;j++){
    	G=(long long)V[i]*V[prim[j]] % MOD;
    	V[i*prim[j]]=G;
    	vis[i*prim[j]]=true;
    	if (i % prim[j]==0) break;
	}
}
if (n<K)
   {
   	down[0]=1;inv[0]=1;
down[1]=n;inv[1]=1;G=1;
for (i=2;i<=n;i++) {
	down[i]=down[i-1]*(n-i+1) % MOD;
	inv[i]=(MOD-MOD/i)*inv[MOD % i] % MOD;
	down[i]=down[i]*inv[i] % MOD;
    }
O=pow(m,n,MOD);O=pow(O,MOD-2,MOD);
m--;G=pow(m,n,MOD);P=pow(m,MOD-2,MOD);
for (i=0;i<=n;i++) ans=(ans+V[i]*G % MOD*down[i]) % MOD,G=G*P % MOD;
cout<<ans*O % MOD<<endl;
   	return 0;
   }
down[0]=1;inv[0]=1;
down[1]=n;inv[1]=1;G=1;
for (i=2;i<=K;i++) {
	down[i]=down[i-1]*(n-i+1) % MOD;
	inv[i]=(MOD-MOD/i)*inv[MOD % i] % MOD;
	down[i]=down[i]*inv[i] % MOD;
    }
if (n-K<0) O=pow(pow(m,K-n,MOD),MOD-2,MOD);
else O=pow(m,n-K,MOD);
if (n-K<0) F[K]=0;
else F[K]=O;
up=1;
for (i=K-1;i>=1;i--)
     {
     	F[i]=F[i+1]*(m-1) % MOD;
     	//C(n-i-1,K-i)=C(n-i+1,n-i-1-K+i)
     	if (n-K>=0) {
     		up=up*(n-i-1) % MOD;
     		up=up*inv[K-i] % MOD;
     		if (((K-i)&1)==0) F[i]=(F[i]+up*O) % MOD;
     		else
     		    {
     		    	F[i]=(F[i]-up*O) % MOD;
     		    	F[i]=(F[i]+MOD) % MOD;
				 }
		 }
	 }
for (i=1;i<=K;i++)
    ans=(ans+V[i]*down[i] % MOD*F[i] % MOD) % MOD;
O=pow(m,n,MOD);O=pow(O,MOD-2,MOD);
cout<<ans*O % MOD<<endl;
return 0;
}




```



---

## 作者：critnos (赞：5)

尽管我已经用纸笔推完了，感觉还是用电脑写清醒一点。

$$\sum_{i=0}^n i^kC(n,i)(m-1)^{n-i}$$

$$\sum_{i=0}^n \sum_{j=0}^k S(k,j)i^{\underline j}C(n,i)(m-1)^{n-i}$$

$$\sum_{j=0}^kS(k,j)\sum_{i=0}^n C(i,j)j!C(n,i)(m-1)^{n-i}$$

$$\sum_{j=0}^kS(k,j)\sum_{i=0}^n C(n,j)j!C(n-j,i-j)(m-1)^{n-i}$$

$$\sum_{j=0}^kS(k,j)n^{\underline j}\sum_{i=0}^n C(n-j,i-j)(m-1)^{n-i}$$

感恩 $C$ 的良好定义

$$\sum_{j=0}^kS(k,j)n^{\underline j}\sum_{i=0}^n C(n-j,n-i)(m-1)^{n-i}$$

$$\sum_{j=0}^kS(k,j)n^{\underline j}\sum_{i=0}^{n-j} C(n-j,i)(m-1)^i$$

设 $p=\dfrac 1 m$

$$m^n\sum_{j=0}^kS(k,j)n^{\underline j}p^j$$

注意算的是求和，最后恰好要除掉一个 $m^n$，下面就不写它了。

看上去已经取得了阶段性胜利（一坨东西被二项式掉了），不过 $S$ 算不得。

显然拆掉。

$$\sum_{j=0}^k\sum_{i=0}^j\dfrac {i^k(-1)^{j-i}}{i!(j-i)!}n^{\underline j}p^j$$

$$\sum_{i=0}^k\dfrac {i^k}{i!}\sum_{j=i}^k\dfrac {(-1)^{j-i}}{(j-i)!}C(n,j)j!p^j$$

看一下感觉能凑

$$\sum_{i=0}^k i^k\sum_{j=i}^k(-1)^{j-i}C(j,i)C(n,j)p^j$$

$$\sum_{i=0}^k i^kC(n,i)\sum_{j=i}^k(-1)^{j-i}C(n-i,j-i)p^j$$

$$\sum_{i=0}^k i^kC(n,i)(-1)^{-i}\sum_{j=i}^kC(n-i,j-i)(-p)^j$$

（好烦，设 $q=-p$）

$$\sum_{i=0}^k i^kC(n,i)p^i\sum_{j=0}^{k-i}C(n-i,j)q^j$$

但是别高兴的太早阿，因为后面的东西不是二项式。

众所周知组合数前缀和的根号方法是莫队，所以这个看上去能递推。

考虑从

$$\sum_{j=0}^{k-i}C(n-i,j)q^j$$

推出

$$\sum_{j=0}^{k-i+1}C(n-i+1,j)q^j$$

我设第一个是 $x$，第二个是 $s$

$s-x=$

$$\sum_{j=0}^{k-i}(C(n-i+1,j)-C(n-i,j))q^j+C(n-i+1,k-i+1)q^{k-i+1}$$

$$\sum_{j=0}^{k-i}C(n-i,j-1)q^j+C(n-i+1,k-i+1)q^{k-i+1}$$

$$q\sum_{j=0}^{k-i-1}C(n-i,j)q^j+C(n-i+1,k-i+1)q^{k-i+1}$$

ohh 看起来 $x$ 确实被凑出来了

$$q(x-C(n-i,k-i))+C(n-i+1,k-i+1)q^{k-i+1}$$

$s=x+q(x-C(n-i,k-i))+C(n-i+1,k-i+1)q^{k-i+1}$

$C$ 也可以递推算，就好了。

---

## 作者：peterwuyihong (赞：5)

颓疯了。。。。

题意：有 $m$ 张牌，其中有一张是王牌。将这些牌均匀随机打乱 $n$ 次，设有 $x$ 次第一张为王牌，求 $x^k$ 的期望值。

我们算柿子，枚举 $x$

$$(m!)^{-n}\sum_{i=0}^ni^k(m!-(m-1)!)^{n-i}((m-1)!)^i\binom n i$$

$$=(m!)^{-n}\sum_{i=0}^ni^k(m-1)^{n-i}((m-1)!)^n\binom n i$$

$$=m^{-n}\sum_{i=0}^ni^k(m-1)^{n-i}\binom n i$$

$$=m^{-n}\sum_{i=0}^n\sum_{j=0}^{\infty}{k\brace j}j!\binom n i\binom i{j}(m-1)^{n-i}$$

$$=m^{-n}\sum_{j=0}^{\infty}{k\brace j}j!\sum_{i=j}^n\binom n i\binom i{j}(m-1)^{n-i}$$

$$=m^{-n}\sum_{j=0}^{\infty}{k\brace j}j!\sum_{i=j}^n\binom n j\binom {n-j}{i-j}(m-1)^{n-i}$$

$$=m^{-n}\sum_{j=0}^{\infty}{k\brace j}j!\binom n j\sum_{i=0}^{n-j}\binom {n-j}{i}(m-1)^{n-i-j}$$

$$=m^{-n}\sum_{j=0}^{\infty}{k\brace j}j!\binom n jm^{n-j}$$

$$=\sum_{j=0}^{\infty}{k\brace j}j!\binom n jm^{-j}$$

$$\sum_{j=0}^{\min(n,k)}j!\binom n jm^{-j}\sum_{i=0}^j\frac{(-1)^{j-i}i^k}{i!(j-i)!}$$

$$\sum_{j=0}^{\min(n,k)}\sum_{i=0}^{\infty}[i\le j]j!\binom n jm^{-j}\frac{(-1)^{j-i}i^k}{i!(j-i)!}$$

$$\sum_{i=0}^{\infty}\sum_{j=i}^{\min(n,k)}j!\binom n jm^{-j}\frac{(-1)^{j-i}i^k}{i!(j-i)!}$$

$$\sum_{i=0}^{\min(n,k)}({i!})^{-1}i^k(-1)^i\sum_{j=i}^{\min(n,k)}\frac{j!}{(j-i)!}\binom n{j}{(-m)}^{-j}$$

$$\sum_{i=0}^{\min(n,k)}i^k(-1)^i\sum_{j=i}^{\min(n,k)}\frac {j!n!}{i!(j-i)!j!(n-j)!}{(-m)}^{-j}$$

$$\sum_{i=0}^{\min(n,k)}i^k(-1)^i\sum_{j=i}^{\min(n,k)}\binom n j\binom j i{(-m)}^{-j}$$

$$\sum_{i=0}^{\min(n,k)}i^k(-1)^i\sum_{j=i}^{\min(n,k)}\binom n i\binom{n-i}{j-i}{(-m)}^{-j}$$

$$\sum_{i=0}^{\min(n,k)}i^k(-1)^i\binom n i\sum_{j=0}^{\min(n,k)-i}\binom{n-i}{j}{(-m)}^{-j-i}$$

$$\sum_{i=0}^{\min(n,k)}i^k\binom n im^{-i}\sum_{j=0}^{\min(n,k)-i}\binom{n-i}{j}{(-m)}^{-j}$$

记 $F(i)=\sum_{j=0}\limits^{\min(n,k)-i}\dbinom{n-i}{j}{(-m)}^{-j}$

$$F(\min(n,k))=1$$

$$F(i)=\sum_{j=0}\limits^{\min(n,k)-i}\dbinom{n-i}{j}{(-m)}^{-j}$$

$$F(i+1)=\sum_{j=0}\limits^{\min(n,k)-i-1}\dbinom{n-i-1}{j}{(-m)}^{-j}$$

我们不考虑 $j=0$ 的情况，因为这时后面的值必为 $1$，此时这样可以对的上。

$$F(i)+\frac{F(i+1)}m=1+\sum_{j=1}\limits^{\min(n,k)-i}\dbinom{n-i}{j}{(-m)}^{-j}-\dbinom{n-i-1}{j-1}{(-m)}^{-j}$$

$$F(i)+\frac{F(i+1)}m=1+\sum_{j=1}\limits^{\min(n,k)-i}\frac{n-i}j\dbinom{n-i-1}{j-1}{(-m)}^{-j}-\dbinom{n-i-1}{j-1}{(-m)}^{-j}$$

$$F(i)+\frac{F(i+1)}m=1+\sum_{j=1}\limits^{\min(n,k)-i}\frac{n-i-j}j\dbinom{n-i-1}{j-1}{(-m)}^{-j}$$

$$F(i)+\frac{F(i+1)}m=1+\sum_{j=1}\limits^{\min(n,k)-i}\dbinom{n-i-1}{j}{(-m)}^{-j}$$

$$F(i)+\frac{F(i+1)}m=\sum_{j=0}\limits^{\min(n,k)-i}\dbinom{n-i-1}{j}{(-m)}^{-j}$$

$$F(i)+\frac{F(i+1)}m=F(i+1)+\binom{n-i-1}{\min(n,k)-i}(-m)^{-\min(n,k)+i}$$

$$F(i)=\frac{m-1}mF(i+1)+\binom{n-i-1}{\min(n,k)-i}(-m)^{-\min(n,k)+i}$$

```cpp
#include<stdio.h>
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
const int p=998244353;
void add(int&x,const int& y){((x+=y)>=p)&&(x-=p);}
int Add(int x,const int y){add(x,y);return x;}
void sub(int&x,const int&y){((x-=y)<0)&&(x+=p);}
int Sub(int x,const int y){sub(x,y);return x;}
void mul(int&x,const int&y){x=1ll*x*y%p;}
int Mul(const int x,const int y){return 1ll*x*y%p;}
int ksm(int a,int b){int ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
int div2(int a){if(a&1)a+=p;return a>>1;}
int pri[664579],tot,v[10000010],G[10000010];
int inv[10000010],F[10000010];
int n,m,k,lim;
void shai(int n){
	inv[1]=1;
	rep(i,2,n)inv[i]=Mul(p-p/i,inv[p%i]);
	G[1]=1;
	rep(i,2,n){
		if(!v[i])pri[++tot]=i,G[i]=ksm(i,k);
		for(int j=1;j<=tot&&i*pri[j]<=n;j++){
			v[i*pri[j]]=1;
			G[i*pri[j]]=Mul(G[i],G[pri[j]]);
			if(i%pri[j]==0)break;
		}
	}
}
int min(int a,int b){
	if(a<b)return a;
	return b;
}
int c[10000010];//c[i]表示 \binom{n-i-1}{\min(n,k)-i} 
int C[10000010];//C[i]表示 \binom{n}{i} 
signed main(){
	scanf("%d%d%d",&n,&m,&k);
	lim=min(n,k);
	shai(lim);
	int ans=0;
	c[lim]=1;
	per(i,lim-1,0)c[i]=Mul(c[i+1],Mul(n-i-1,inv[lim-i]));
	C[0]=1;
	rep(i,1,lim)C[i]=Mul(C[i-1],Mul(n-i+1,inv[i]));
	F[lim]=1;
	int invm=ksm(m,p-2),invnegm=ksm(p-m,p-2),u=1;
	per(i,lim-1,0)mul(u,invnegm),F[i]=Add(Mul(F[i+1],Mul(m-1,invm)),Mul(c[i],u));
	u=1;
	rep(i,0,lim)add(ans,Mul(Mul(C[i],G[i]),Mul(u,F[i]))),mul(u,invm);
	printf("%d",ans);
}
```
一遍推对这个柿子也是我没想到的。。。

顺便拿了 $\text{CF}$ 的最优解。。

---

## 作者：NGC5457 (赞：3)

[**洛谷题库 P6031 Cards 加强版**](https://www.luogu.com.cn/problem/P6031)

对于每一轮对局的 $m!$ 种排列，对于编号为 $a$ 的牌，恒有 $(m-1)!$ 种是以牌 $a$ 为首的。因此一轮可以归为 $m$ 种情况，首张为王牌的概率为 $\frac{1}{m}$。

这是某场模拟考试给出的部分分：
$$
\begin{array}{cccc}
\text{Subtask ID}&\text{Properties}&\text{Points}&\text{Dependencies}\\ \hline
1&n,m,k\leq 5&2&\\
2&k=1&2&\\
3&k\leq 5000&10&1,2\\
4&m\leq 100&10&1\\
5&n\leq k&5&\\
6&k\leq 10^5&10&1,2,3\\
7&k\leq 5\times 10^6&20&1,2,3,6\\
8&&41&1\sim 7
\end{array}
$$
### 部分分
我首先考虑的是**期望的线性性**。

记 $E_n(x^k)$ 为洗牌 $n$ 次，获胜场次的 $k$ 次方的期望。考虑下一场的胜负情况。对于 $n>0$，有转移
$$\begin{aligned}
E_n(x^k)&=\frac{m-1}{m}E_{n-1}(x^k)+\frac{1}{m}E_{n-1}\left((x+1)^k\right)\\
&=\frac{m-1}{m}E_{n-1}(x^k)+\frac{1}{m}E_{n-1}\left(\sum_{i=0}^k\binom{k}{i}x^i\right)\\
&=\frac{m-1}{m}E_{n-1}(x^k)+\frac{1}{m}\sum_{i=0}^k\binom{k}{i}E_{n-1}(x^i)\\
&=E_{n-1}(x^k)+\frac{1}{m}\sum_{i=0}^{k-1}\binom{k}{i}E_{n-1}(x^i)
\end{aligned}$$

想象一张无穷大的网格图：第 $n$ 列第 $k$ 行表示的是 $E_n(x^k)$。对于每个点 $(n,k)\ \ (n>0,k\geq 0)$，我们设立 $k$ 条边 $(n-1,i)\rightarrow(n,k)$（$i$ 取遍 $0,1,\cdots,k-1$），边权分别为 $\binom{k}{i}/m$，称经过它们为**大跳**；同时有边 $(n-1,k)\rightarrow(n,k)$，边权为 $1$。定义一条路径的权值为路径上所有边的边权之*积*。又有 $E_0(x^k)=[k=0]$，于是由上文转移式得到 $E_n(x^k)$ 等于在网格图上从 $(0,0)$ 到 $(n,k)$ 的所有合法路径的权值之和。又因为非大跳的权值为 $1$，故我们只需考虑大跳的起终点。设某条路径有 $c$ 次大跳，每次大跳落点为 $p_0=0,p_1,p_2,\cdots,p_c=k$。那么，这条路径的权值为
$$\begin{aligned}
&\prod_{i=1}^c \frac 1m\binom{p_i}{p_{i-1}}\\
=&\frac{1}{m^c}\binom{p_c}{p_c-p_{c-1}}\binom{p_{c-1}}{p_{c-1}-p_{c-2}}\cdots\binom{p_2}{p_2-p_1}\binom{p_1}{p_1}\\
=&\frac{1}{m^c}\binom{k}{p_1-p_0,p_2-p_1,\cdots,p_c-p_{c-1}}&(p_c=k)\\
=&\frac{k!}{\prod_{i=1}^c\frac 1m(p_i-p_{i-1})!}
\end{aligned}$$

于是我们不妨修改每条大跳边 $(n-1,k-\Delta)\rightarrow(n,k)\ \ (\Delta>0)$ 的权值为 $\frac{1}{m\Delta!}$，$E_n(x^k)$ 的实际值为路径权值和与 $k!$ 的积。

#### $\text{24 pts}$ - I - $k\leq 10^5$，生成函数与多项式快速幂
注意到从 $(n-1,k)$ 转移到 $(n,k+\Delta)$ 的权只与 $\Delta$ 有关，自然想到生成函数的卷积。我们构造数列 $\langle f_n\rangle$，满足 $f_0=1,f_i=\frac{1}{m\cdot i!}\ \ (i>0)$。记 $F(z)=1+\frac{1}{m}z+\frac{1}{2!m}z^2+\cdots$ 为它的普通生成函数，则有 $E_n(x^k)=k!\cdot [z^k]F^n(z)$。

暴力求取快速幂，复杂度为 $\operatorname{O}(k\log^2 k)$；使用多项式 $\exp,\ln$ 优化到 $\operatorname{O}(k\log k)$。

#### $\text{24 pts}$ - II - 多项式乘法
我们直接对所有路径的权值求和。枚举 $c$，“枚举”所有合法落点序列（的差分形式），考虑大跳是在 $n$ 次转移的哪些位置进行的，得到如下式子：
$$
\begin{aligned}
E_n(x^k)=&\sum_{c=0}^{\min\{n,k\}}\binom{n}{c}\frac{1}{m^c}\sum_{\substack{\Delta_1+\cdots+\Delta_c=k,\\ \forall i,0<i\leq c,\Delta_i>0}}\binom{k}{\Delta_1,\Delta_2,\cdots,\Delta_c}
\end{aligned}
$$

$\forall i,0<i\leq c,\Delta_i>0$ 的限制很烦。若没有它，那么不难得到
$$
\sum_{\Delta_1+\cdots+\Delta_c=k}\binom{k}{\Delta_1,\Delta_2,\cdots,\Delta_c}=(\underbrace{1+1+\cdots+1}_{c\text{ 个 }1})^k=c^k
$$
考虑以该简化形式为基础，使用**容斥原理**计算带有 $\Delta_i>0$ 限制的结果。我们钦定其中 $i$ 个位置满足 $\Delta_j=0$。于是剩下的 $c-i$ 个 $\Delta_j$ 之和为 $k$，是为 $c-i$ 项式系数，也即
$$
\sum_{\Delta_1+\cdots+\Delta_{c-i}=k}\binom{k}{\Delta_1,\Delta_2,\cdots,\Delta_{c-i},\underbrace{0,\cdots,0}_{i\text{ 个 }0}}=(c-i)^k
$$
考虑从 $c$ 个位置中选取这 $i$ 个位置，乘上容斥系数，得到答案为
$$
E_n(x^k)=\sum_{c=0}^{\min\{n,k\}}\binom{n}{c}\frac{1}{m^c}\sum_{i=0}^{c}(-1)^i\binom{c}{i}(c-i)^k\quad\quad(1)
$$

内部的和式可以被改写为 $c!\sum_{i=0}^c\left((-1)^i/i!\right)\left((c-i)^k/(c-i)!\right)$，可以用多项式乘法优化卷积。时间复杂度 $\operatorname{O}(k\log k)$。

### 优化多项式乘法得到的另解

就算时间给够，我们似乎也不能简单地用 NTT（$\mathbb{Z}/n\mathbb{Z},n=998244353$ 域上）计算 $k\geq 2^{22}$ 时的卷积。原因很简单：这个群的阶只有 $2^{23}$ 的偶因数。但学习了宋佳兴学长的代码后发现，我们可以将数列作拆分：$F(z)=F_0(z)+z^{2^l}F_1(z)+z^{2\times 2^l}F_2(z)+\cdots$ 然后将每一部分分别相乘后再相加，就能得到正确的卷积结果。

#### 常数优化
- 手写不带分支的取模函数（用数的符号位判断是否应补全/减去 $P=998244353$）；
- （NTT 过程中）不要每一次迭代时重新计算 $\operatorname{O}(n\log n)$ 次原根的次幂，可以预处理后花费 $\operatorname{O}(n\log n)$ 的空间存下来。

时间复杂度 $\operatorname{O}(kl+\lceil k/2^l\rceil^2k)$（点值相乘后直接相加，最后再 IDFT 以省时），尝试后发现 $l=19$ 时较快。当然，洛谷的时限只给了 $\text{2 s}$，本写法是过不去的。可以尝试换成 DIT/DIF 再卡卡常。

**[代码](https://www.luogu.com.cn/paste/iwgjovd7)**

### 正解
直接从期望的定义下手：所有情况下 $x^k$ 的和除以情况总数。枚举 $x$，那么答案为
$$
E_n(x^k)=\frac{\sum_{x=0}^{n}x^k\binom{n}{x}(m-1)^{n-x}}{m^n}=\left(\frac{m-1}{m}\right)^n\sum_{x=0}^nx^k\binom{n}{x}\frac{1}{(m-1)^x}
$$

暴力计算该式答案，将得到 $\text{5 pts}$ 的好成绩（$n\leq k$）。我们希望得到 $\operatorname{O}(k)$ 的算法，故尝试[将 $x^k$ 用**第二类斯特林数**转化为下降幂](https://oi-wiki.org/math/combinatorics/stirling/#%E4%B8%8B%E9%99%8D%E5%B9%82%E4%B8%8E%E6%99%AE%E9%80%9A%E5%B9%82%E7%9A%84%E7%9B%B8%E4%BA%92%E8%BD%AC%E5%8C%96)：
$$\begin{aligned}
x^k&=\sum_{c=0}^kx^{\underline c}\begin{Bmatrix}k\\c\end{Bmatrix}=\sum_{c=0}^kx^{\underline c}\frac{(-1)^c}{c!}\sum_{i=0}^c(-1)^i\binom ci i^k\\
\text{原式}&=\left(\frac{m-1}{m}\right)^n\sum_{x=0}^n\binom{n}{x}\frac{1}{(m-1)^x}\sum_{c=0}^kx^{\underline c}\frac{(-1)^c}{c!}\sum_{i=0}^c(-1)^i\binom ci i^k\\
&=\left(\frac{m-1}{m}\right)^n\sum_{c=0}^k\frac{(-1)^c}{c!}\left(\sum_{i=0}^c(-1)^i\binom ci i^k\right)\boxed{\sum_{x=0}^{n}\binom{n}{x}\frac{x^{\underline c}}{(m-1)^x}}
\end{aligned}$$
化简方框内和式：
$$\begin{aligned}
\sum_{x=0}^{n}\binom{n}{x}\frac{x^{\underline c}}{(m-1)^x}&=\sum_{x=0}^{n}\frac{n!}{x!(n-x)!}\frac{x!}{(x-c)!}\frac{1}{(m-1)^x}\\
&=\sum_{x=c}^n\binom{n-c}{x-c}\frac{n^{\underline c}}{(m-1)^x}\\
&=\sum_{x=0}^{n-c}\binom{n-c}x\frac{n^{\underline c}}{(m-1)^{x+c}}\\
&=n^{\underline c}\frac{1}{(m-1)^c}\left(\frac{m}{m-1}\right)^{n-c}=n^{\underline c}\frac{m^{n-c}}{(m-1)^n}
\end{aligned}$$
$$\begin{aligned}
\text{原式}&=\left(\frac{m-1}{m}\right)^n\sum_{c=0}^k\frac{(-1)^c}{c!}n^{\underline c}\frac{m^{n-c}}{(m-1)^n}\sum_{i=0}^c(-1)^i\binom ci i^k\\
&=\sum_{c=0}^{\min\{n,k\}}\binom{n}{c}\frac{1}{(-m)^c}\sum_{i=0}^c(-1)^i\binom ci i^k
\end{aligned}$$

与部分分解法式 $(1)$ 殊途同归。现在考虑它的化简。记 $\text{lmt}=\min\{n,k\}$。$\binom{n}{c}\binom{c}{i}$ 惹人注意，我们尝试交换求和顺序并交换指标：
$$\begin{aligned}
\text{原式}&=\sum_{i=0}^{\text{lmt}}(-1)^ii^k\sum_{c=i}^{\text{lmt}}\binom nc\binom ci\frac{1}{(-m)^c}\\
&=\sum_{i=0}^{\text{lmt}}(-1)^ii^k\binom ni\sum_{c=i}^{\text{lmt}}\binom{n-i}{c-i}\frac{1}{(-m)^c}\\
&=\sum_{i=0}^{\text{lmt}}(-1)^ii^k\frac{1}{(-m)^i}\sum_{c=0}^{\text{lmt}-i}\binom{n-i}c\frac{1}{(-m)^c}
\end{aligned}$$

记 $h(i)=\sum_{c=0}^{\text{lmt}-i}\binom{n-i}c\frac{1}{(-m)^c}$。假若 $\text{lmt}=n$，也即 $n\leq k$，那么显然有 $h(i)=\left(1+\frac{1}{-m}\right)^{n-i}=\left(\frac{m}{m-1}\right)^{n-i}$；否则似乎难以求出它的封闭形式。但我们发现在 $i$ 不同时，变化的只有二项式系数的上指标。根据递推公式 $\binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}\ \ (n,m>0)$ 以及 $\binom n0=1\ \ (n\geq 0)$，我们尝试从 $h(i+1)$ 转移到 $h(i)\ \ (i<\text{lmt})$。转写为
$$\begin{aligned}
h(i)&=\sum_{c=0}^{\text{lmt}-i}\binom{n-i}c\frac{1}{(-m)^c}\\
&=\binom{n-i}0\frac{1}{(-m)^0}+\sum_{c=1}^{\text{lmt}-i}\left(\binom{n-(i+1)}c+\binom{n-(i+1)}{c-1}\right)\frac{1}{(-m)^c}\\
&=\binom{n-(i+1)}0\frac{1}{(-m)^0}+\left(\sum_{c=1}^{\text{lmt}-i}\binom{n-(i+1)}c\frac{1}{(-m)^c}\right)+\frac{1}{-m}\left(\sum_{c=0}^{\text{lmt}-(i+1)}\binom{n-(i+1)}c\frac{1}{(-m)^c}\right)\\
&=\left(h(i+1)+\binom{n-(i+1)}{\text{lmt}-i}\frac{1}{(-m)^{\text{lmt}-i}}\right)-\frac 1mh(i+1)
\end{aligned}$$
$$
\text{answer}=\sum_{i=0}^{\text{lmt}}(-1)^ii^k\frac{1}{(-m)^i}h(i)
$$

$h(\text{lmt})$ 可以在 $\operatorname{O}(\text{lmt})$ 的时间内算出；而所有上指标与 $n$ 相关的二项式系数，下指标均不超过 $\text{lmt}\leq k$，可以通过下降幂等递推求出。于是我们可以 $\operatorname{O}(k)$ 的时间计算出本题答案。

[**R99501601 记录详情**](https://www.luogu.com.cn/record/99501601)

以下代码因省空间省时间而可读性较差，仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define inl __always_inline
typedef unsigned long long ull;
using ulll = __uint128_t;

constexpr uint N = 1e7 + 10, P = 998244353;
uint n, m, k, p[N], pk[N], fac[N], *ppt = p; ulll ans;
constexpr uint *const inv = p, *const f = fac;

inl ull fpow (ull a, ull b) {
	ull c = 1; a %= P;
	for (; b; b >= 1) {
		if (b & 1) (c *= a) %= P;
		(a *= a) %= P;
	}
	return c;
}
inl void calc_inv () {
	constexpr uint *const fact = inv;
	fact[0] = 1;
	for (ull x = 1; x < N; ++x)
		fact[x] = fact[x-1] * x % P;
	ull finv = fpow (fact[N-1], P-2);
	for (ull x = N-1; x; --x)
		inv[x] = finv * fact[x-1] % P,
		(finv *= x) %= P;
}
inl void sieve () {
	pk[1] = 1;
	for (ull x = 2, _pk, y; x < N; ++x) {
		if (!fac[x]) fac[x] = *ppt++ = x,
			pk[x] = fpow (x, k);
		_pk = pk[x];
		for (uint *pt = p; pt != ppt & (y = *pt*x) <= N-1
			& fac[x] >= *pt; ++pt)
			fac[y] = *pt,
			pk[y] = _pk * pk[*pt] % P;
	}
}

int main () {
	/*  */
	scanf ("%u%u%u", &n, &m, &k);
	const uint lmt = min (n, k), invm = fpow (m, P-2),
		minvm = invm * (P-1ull) % P;
	sieve (); calc_inv (); f[lmt+1] = 0;
	uint *pt1 = inv, *_f = f + lmt, *pt2 = pk;
	ull p = lmt, co = 1;
	while (~p)
		*_f = (_f[1] * (minvm + 1ull) + co) % P, --_f,
		co = co * (n-p--) % P * *++pt1 % P * minvm % P;
	pt1 = inv, _f = f, p = 0, co = 1;
	while (p <= lmt)
		ans += co * *pt2++ * (ulll) *_f++,
		(co *= *++pt1 * (n-p++) % P * invm % P) %= P;
	printf ("%llu", ull (ans % P));

	return 0;
}
```

---

## 作者：zhylj (赞：3)

记 $p = \dfrac 1m$，则答案为：

$$\begin{aligned}& \sum_{i=0}^n {n\choose i} p^i(1-p)^{n-i}i^k \\= & p^n\sum_{i=0}^n {n\choose i} \left(\frac{1-p}p\right)^{n-i}i^k\end{aligned}$$

若 $n < k$ 则暴力计算，否则记 $A = \dfrac{1-p}p$，考虑 $(x + A)^n$ 及其展开式的 $k$ 阶导数：

$$\begin{aligned}(x+A)^n & = \sum_{i=0}^n A^{n-i}{n\choose i}x^i \\n^{\underline k}(x+A)^{n-k} & = \sum_{i=k}^n i^{\underline k} A^{n-i}{n\choose i}x^i\end{aligned}$$

令 $x = 1$，则有：

$$n^{\underline k}(A+1)^{n-k} = \sum_{i=k}^n i^{\underline k} A^{n-i}{n\choose i}$$

于是我们考虑把答案中的幂转化成下降幂：

$$\begin{aligned}& p^n\sum_{i=0}^n {n\choose i} \left(\frac{1-p}p\right)^{n-i}i^k \\= & p^n\sum_{i=0}^k\left\{\begin{matrix}k\\ i\end{matrix}\right\}\sum_{j=0}^n {n\choose j} A^{n-j}j^{\underline i} \\= & p^n\sum_{i=0}^k\left\{\begin{matrix}k\\ i\end{matrix}\right\}n^{\underline i}(A+1)^{n-i}{n \choose i} \\= & \sum_{i=0}^k\left\{\begin{matrix}k\\ i\end{matrix}\right\}n^{\underline i}p^i\end{aligned}$$

然后考虑出现斯特林数是一定无法在我们想要的时间内求出来的，于是用通项公式替代斯特林数：

$$\begin{aligned}& \sum_{i=0}^k\frac{1}{i!}\sum_{j=0}^i(-1)^{i-j} {i\choose j}j^kn^{\underline i}p^i \\= & \sum_{i=0}^k\sum_{j=0}^i(-1)^{i-j} {i\choose j}{n \choose i}j^kp^i \\= & \sum_{i=0}^k\sum_{j=0}^i(-1)^{i-j} {n - j\choose i - j}{n \choose j}j^kp^i\\= & \sum_{j=0}^k(-1)^jj^k{n \choose j}\sum_{i=j}^k {n - j\choose i - j}(-p)^i\\= & \sum_{j=0}^kp^jj^k{n \choose j}\sum_{i=0}^{k-j} {n - j\choose i}(-p)^i\end{aligned}$$

记：

$$f(x) = \sum_{i=0}^{k-x} {n - x\choose i}(-p)^i$$

假如我们能在 $\mathcal O(k)$ 时间内求出前 $k$ 个 $f(x)$，就能在 $\mathcal O(k)$ 时间内求出答案了。

$$\begin{aligned}& \sum_{i=0}^{k-x} {n - x\choose i}(-p)^i \\= & \sum_{i=0}^{k-x} \left[{n - x - 1\choose i}+{n - x - 1\choose i - 1}\right](-p)^i \\= & \sum_{i=0}^{k-x} {n - x - 1\choose i}(-p)^i + (-p)\sum_{i=0}^{k-x-1}{n - x - 1\choose i}(-p)^i \\= & (1 - p)f(x + 1) + {n - x - 1\choose k - x}(-p)^{k - x}\end{aligned}$$

考虑 ${n - x - 1\choose k - x}$ 如何求，注意到我们有：

$${n - x - 1\choose k - x} = \frac{n-x-1}{k-x} {n - x - 2\choose k - x - 1}$$

所以从 ${n - 1\choose k}$ 开始递推就好了。

```cpp
const int kN = 1e7 + 5, kP = 1e6 + 5, kInf = 0x3f3f3f3f;
const ll kMod = 998244353, kInfLL = 0x3f3f3f3f3f3f3f3fLL;

ll QPow(ll a, ll b) {
	ll ret = 1, bas = a % kMod;
	for(; b; b >>= 1, bas = bas * bas % kMod) if(b & 1) ret = ret * bas % kMod;
	return ret;
}

int n, m, k, p;

int prime[kP], cnt = 0, pw_xk[kN];
bool flag[kN];
void Sieve() {
	pw_xk[1] = 1;
	for(int i = 2; i <= k; ++i) {
		if(!flag[i]) {
			prime[++cnt] = i;
			pw_xk[i] = QPow(i, k);
		}
		for(int j = 1; j <= cnt && i * prime[j] <= k; ++j) {
			flag[i * prime[j]] = true;
			pw_xk[i * prime[j]] = (ll)pw_xk[i] * pw_xk[prime[j]] % kMod;
			if(i % prime[j] == 0) break;
		}
	}
}
int pw_px[kN], C_n_x[kN], C_nx1_kx[kN], inv[kN], f[kN];
void Init() {
	Sieve();
	pw_px[0] = C_n_x[0] = 1; f[0] = 0;
	ll np = -p + kMod, fac = 1;
	for(int i = 1; i <= k; ++i) fac = fac * i % kMod;
	inv[k] = QPow(fac, kMod - 2); fac = 1;
	for(int i = k - 1; ~i; --i) inv[i] = (ll)inv[i + 1] * (i + 1) % kMod;
	for(int i = 1; i <= k; ++i) {
		inv[i] = (ll)inv[i] * fac % kMod;
		fac = fac * i % kMod;
	}
	for(int i = 1; i <= k; ++i) {
		pw_px[i] = (ll)pw_px[i - 1] * np % kMod;
		C_n_x[i] = (ll)C_n_x[i - 1] * (n - i + 1) % kMod * inv[i] % kMod;
	}
	C_nx1_kx[0] = (ll)C_n_x[k] * QPow(n, kMod - 2) % kMod * (n - k) % kMod;
	for(int i = 1; i <= k; ++i)
		C_nx1_kx[i] = C_nx1_kx[i - 1] * QPow(n - i, kMod - 2) % kMod * (k - i + 1) % kMod;
	f[k] = 1;
	for(int i = k - 1; ~i; --i) {
		f[i] = (ll)f[i + 1] * (1 + np) % kMod + (ll)C_nx1_kx[i] * pw_px[k - i] % kMod;
	}
}

ll Calc() {
	ll ret = 0;
	if(n > k) {
		ll bas_p = 1;
		for(int i = 0; i <= k; ++i) {
			ret = (ret + (ll)bas_p * pw_xk[i] % kMod * C_n_x[i] % kMod * f[i]) % kMod;
			bas_p = bas_p * p % kMod;
		}
	} else {
		ll bas_p = 1, bas_1p = QPow(1 - p + kMod, n), inv_1p = QPow(1 - p + kMod, kMod - 2);
		for(int i = 0; i <= k; ++i) {
			ret = (ret + C_n_x[i] * bas_p % kMod * bas_1p % kMod * pw_xk[i]) % kMod;
			bas_p = bas_p * p % kMod;
			bas_1p = bas_1p * inv_1p % kMod;
		}
	}
	return ret;
}

int main() { 
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	int T = 1; //rd(T);
	while(T--) {
		rd(n, m, k);
		if(m == 1) {
			printf("%d\n", QPow(n, k));
			continue;
		}
		p = QPow(m, kMod - 2);
		Init();
		printf("%lld\n", Calc());
	} return 0;
}
```

---

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/P6031)

学习一下斯特林相关技巧，这是一道基础练习题。
## 题意

有 $m$ 张牌，其中一张为特殊牌，其余为相同的普通牌。将牌均匀打乱 $n$ 次，如果有 $x$ 次特殊牌在第一位，则得分为 $x^k$，求 $E(x^k)$ 对 $998244353$ 取模的结果。

$1\le k\le 10^7$，$1\le n,m<\bmod$。
## 思路

写出式子。

$$\sum_{i=0}^n\binom{n}{i}p^{i}(1-p)^{n-i}i^k$$

其中 $p=\dfrac 1 m$。

展开普通幂。

$$\sum_{i=0}^n\binom{n}{i}p^{i}(1-p)^{n-i}\sum_{j=0}^k{k\brace j}i^{\underline{j}}$$

交换求和顺序。

$$\sum_{j=0}^k{k\brace j}\sum_{i=0}^n\binom{n}{i}i^{\underline{j}}p^{i}(1-p)^{n-i}$$

$$\sum_{j=0}^k{k\brace j}n^{\underline{j}}\sum_{i=0}^n\binom{n-j}{i-j}p^{i}(1-p)^{n-i}$$

用 $i-j$ 替换 $i$。

$$\sum_{j=0}^k{k\brace j}n^{\underline{j}}\sum_{i=0}^{n-j}\binom{n-j}{i}p^{i+j}(1-p)^{n-i-j}$$

$$\sum_{j=0}^k{k\brace j}n^{\underline{j}}p^j\sum_{i=0}^{n-j}\binom{n-j}{i}p^{i}(1-p)^{n-i-j}$$

二项式定理。

$$\sum_{j=0}^k{k\brace j}n^{\underline{j}}p^j$$

此时复杂度只能做到 $O(k\log k)$ 无法通过。

第二类斯特林数通项公式。

$${n\brace m}=\dfrac{1}{m!}\sum_{i=0}^m (-1)^{m-i}\binom mii^n$$

$$\sum_{i=0}^k\dfrac{n^{\underline{i}}p^i}{i!}\sum_{j=0}^i(-1)^{i-j}\binom{i}{j}j^k$$

交换求和顺序。

$$\sum_{j=0}^k(-1)^{j}j^k\sum_{i=j}^k\dfrac{n^{\underline{i}}(-p)^i}{i!}\binom{i}{j}$$

展开组合数。

$$\sum_{j=0}^k\dfrac{(-1)^{j}j^k}{j!}\sum_{i=j}^k\dfrac{n^{\underline{i}}(-p)^i}{(i-j)!}$$

用 $i-j$ 替换 $i$。

$$\sum_{j=0}^k\dfrac{(-1)^{j}j^k(-p)^j}{j!}\sum_{i=0}^{k-j}\dfrac{n^{\underline{i+j}}(-p)^i}{i!}$$

$$\sum_{j=0}^k\dfrac{j^kp^jn^{\underline{j}}}{j!}\sum_{i=0}^{k-j}\dfrac{(n-j)^{\underline{i}}(-p)^i}{i!}$$

$$\sum_{j=0}^k\dfrac{j^kp^jn^{\underline{j}}}{j!}\sum_{i=0}^{k-j}\binom{n-j}{i}(-p)^i$$

下文 $p$ 等于原来的 $-p$。

记：
$$f(j)=\sum_{i=0}^{k-j}\binom{n-j}{i}p^i$$


$$\begin{aligned}f(j-1)-f(j)

&=\sum_{i=0}^{k-j+1}\binom{n-j+1}{i}p^i-\sum_{i=0}^{k-j}\binom{n-j}{i}p^i\\

&=\sum_{i=0}^{k-j}p^i\left[\binom{n-j+1}{i}-\binom{n-j}{i}\right]+\binom{n-j+1}{k-j+1}p^{k-j+1}\\

&=\sum_{i=0}^{k-j}\binom{n-j}{i-1}p^i+\binom{n-j+1}{k-j+1}p^{k-j+1}\\

&=p\sum_{i=0}^{k-j-1}\binom{n-j}{i}p^i+\binom{n-j+1}{k-j+1}p^{k-j+1}\\

&=p\left[f(j)-\binom{n-j}{k-j}p^{k-j}\right]+\binom{n-j+1}{k-j+1}p^{k-j+1}\\

&=pf(j)+\left[\binom{n-j+1}{k-j+1}-\binom{n-j}{k-j}\right]p^{k-j+1}\\

&=pf(j)+\binom{n-j}{k-j+1}p^{k-j+1}
\end{aligned}$$

所以，

$$\begin{aligned}f(j-1)&=(p+1)f(j)+\binom{n-j}{k-j+1}p^{k-j+1}\\
&=(p+1)f(j)+\dfrac{(n-j)^{\underline{k-j+1}}}{(k-j+1)!}p^{k-j+1}\\
&=(p+1)f(j)+\dfrac{n^{\underline{k+1}}}{n^{\underline{j}}(k-j+1)!}p^{k-j+1}

\end{aligned}$$

边界是：

$$f(\min(n,k))=1$$

注意 $p$ 符号变了。

$$\sum_{j=0}^k\dfrac{j^k(-p)^jn^{\underline{j}}}{j!}f(j)$$

递推求出 $f(j)$，时间复杂度 $O(k)$。

预处理 $i^k$，$p^i$，$\dfrac{1}{i!}$，$n^{\underline{i}}$，$\dfrac 1 {n^{\underline{i}}}$ 即可。注意一下空间。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e7+10,mod=998244353;
int n,m,k,p,q,f[N],ifac[N],dw[N],idw[N],pwk[N],pwp[N];
int cnt,pri[N/10];
bool vis[N];
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
inline void Prefix(int n){
	f[1]=1,pwk[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			pri[++cnt]=i;
			pwk[i]=qpow(i,k);
		}
		for(int j=1;j<=cnt&&i*pri[j]<=n;j++){
			pwk[i*pri[j]]=1ll*pwk[i]*pwk[pri[j]]%mod;
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
	ifac[0]=1;
	for(int i=1;i<=n;i++)
		ifac[i]=1ll*ifac[i-1]*i%mod;
	ifac[n]=qpow(ifac[n],mod-2);
	for(int i=n;i>=1;i--)
		ifac[i-1]=1ll*ifac[i]*i%mod;
	pwp[0]=1;
	for(int i=1;i<=n;i++)
		pwp[i]=1ll*pwp[i-1]*p%mod;
}
inline void Prefix2(int u){
	dw[0]=1;
	for(int i=1;i<=u;i++)
		dw[i]=1ll*dw[i-1]*(n-i+1)%mod;
	idw[u]=qpow(dw[u],mod-2);
	for(int i=u;i>=1;i--)
		idw[i-1]=1ll*idw[i]*(n-i+1)%mod; 
}
int main(){
	n=read(),m=read(),k=read();
	p=qpow(m,mod-2),p=(mod-p)%mod;
	Prefix(k+5),Prefix2(k+5);
	f[min(k,n)]=1;
	for(int i=min(k,n);i>=1;i--)
		f[i-1]=(1ll*(p+1)*f[i]+1ll*dw[k+1]*idw[i]%mod*ifac[k-i+1]%mod*pwp[k-i+1])%mod;
	int ans=0;
	for(int i=0;i<=k;i++){
		int tmp=1ll*pwk[i]*pwp[i]%mod*dw[i]%mod*ifac[i]%mod*f[i]%mod;
		if(i&1) ans=(ans+mod-tmp)%mod;
		else ans=(ans+tmp)%mod;
	}
	write(ans);
	flush();
}
```


---

## 作者：whiteqwq (赞：1)

[P6031 CF1278F Cards 加强版](https://www.luogu.com.cn/problem/P6031)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1787069)

## 题意
$m$张牌，有一张是王牌，打乱$n$次，设有$x$次第一次为王牌，求$x^k$的期望。（$1\leqslant n,m<998244353,1\leqslant k\leqslant 10^7$）

## 分析
死亡推式子题。。。刚好可以总结一些推式子题套路。

设$p=\frac{1}{m}$，那么首先很容易列出式子（$i$枚举王牌出现次数）：

$$\sum_{i=0}^n{n\choose i}p^i(1-p)^{n-i}i^k$$

但这个和式的上界是$n$，怎么优化枚举都没有办法，所以套路地用第二类斯特林数展开，然后交换求和式（组合意义就是$m$个球放到$n$个盒子里）：

$$
=\sum_{i=0}^n{n\choose i}p^i(1-p)^{n-i}\sum_{j=0}^i\begin{Bmatrix}k\\j\end{Bmatrix}{i\choose j}j!
$$
$$
=\sum_{j=0}^n j!\begin{Bmatrix}k\\j\end{Bmatrix}\sum_{i=j}^n{n\choose i}{i\choose j}p^i(1-p)^{n-i}
$$

然后利用一个结论${n\choose i}{i\choose k}={n\choose k}{n-k\choose i-k}$（下方有说明）继续推：

$$
=\sum_{j=0}^nj!\begin{Bmatrix}k\\j\end{Bmatrix}\sum_{i=j}^n{n\choose j}{n-j\choose i-j}p^i(1-p)^{n-i}
$$
$$
=\sum_{j=0}^nj!\begin{Bmatrix}k\\j\end{Bmatrix}{n\choose j}\sum_{i=0}^{n-j}{n-j\choose i}p^{i+j}(1-p)^{n-i-j}
$$
$$
=\sum_{j=0}^nj!\begin{Bmatrix}k\\j\end{Bmatrix}{n\choose j}p^j\sum_{i=0}^{n-j}{n-j\choose i}p^i(1-p)^{(p-j)-i}
$$
$$
=\sum_{j=0}^nj!\begin{Bmatrix}k\\j\end{Bmatrix}{n\choose j}p^j(1-p+p)^{n-j}=\sum_{j=0}^kj!p^j{n\choose j}\begin{Bmatrix}k\\j\end{Bmatrix}$$

利用上面提到的第二类斯特林数通项暴力展开，再次交换求和式：

$$
=\sum_{j=0}^kj!p^j{n\choose j}\frac{1}{j!}\sum_{i=0}^j{j\choose i}(-1)^{j-i}i^k
$$
$$
=\sum_{i=0}^ki^k\sum_{j=i}^k{n\choose j}{j\choose i}p^j(-1)^{j-i}
$$
$$
=\sum_{i=0}^k (-1)^ki^k{n\choose i}\sum_{j=i}^n{n-i\choose j-i}(-p)^j
$$
$$
=\sum_{i=0}^k(-1)^ki^k{n\choose i}\sum_{j=0}^{k-i}{n-i\choose j}(-p)^{j+i}
$$
$$=\sum_{i=0}^kp^ii^k{n\choose i}\sum_{j=0}^{k-i}{n-i\choose j}(-p)^j$$

设$S(i)=\sum_{j=0}^{k-i}{n-i\choose j}(-p)^j$，那么原式就变成可以$O(k)$递推的式子了：
$$=\sum_{i=0}^kp^ii^k{n\choose i}S(i)$$

那么我们现在就要求出$S(1\cdots k)$，很容易知道$i=k$时$S(i)=1$。

考虑倒序递推$S(i)$，直接暴力展开组合数：

$$
S(i)=\sum_{j=0}^{k-i}{n-i\choose j}(-p)^j
$$
$$
=\sum_{j=0}^{k-i}({n-i-1\choose j}+{n-i-1\choose j-1})(-p)^j
$$
$$
=\sum_{j=0}^{k-i}{n-(i+1)\choose j}(-p)^j+\sum_{j=0}^{k-i}{n-i-1\choose j-1}(-p)^j
$$
$$
=S(i+1)+{n-i-1\choose k-i}(-p)^{k-i}+(-p)\sum_{j=0}^{k-(i+1)}{n-(i+1)\choose j}(-p)^j
$$
$$=(1-p)S(i+1)+{n-i-1\choose k-i}(-p)^{k-i}$$

那么我们随便筛一下，然后拆一下组合数，就可以线性递推出来$S(1\cdots k)$了。

## 代码

谨慎起见，可以特判一下$n<k$的情况。

```
#include<stdio.h>
const int maxk=10000005,mod=998244353;
int n,m,k,p,cnt,ans,mul;
int pw[maxk],c[maxk],P[maxk],inv[maxk],S[maxk],pmul[maxk],npmul[maxk],fmul[2];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
void sieve(int n){
	fmul[0]=1,fmul[1]=mod-1;
	inv[1]=c[1]=pw[1]=1;
	for(int i=2;i<=n;i++){
		inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
		if(c[i]==0)
			P[++cnt]=i,pw[i]=ksm(i,k);
		for(int j=1;j<=cnt;j++){
			if(i*P[j]>n)
				break;
			c[i*P[j]]=1,pw[i*P[j]]=1ll*pw[i]*pw[P[j]]%mod;
			if(i%P[j]==0)
				break;
		}
	}
	pmul[0]=npmul[0]=1;
	for(int i=1;i<=n;i++)
		pmul[i]=1ll*pmul[i-1]*p%mod,npmul[i]=1ll*npmul[i-1]*(1-p+mod)%mod;
}
int main(){
	scanf("%d%d%d",&n,&m,&k),p=ksm(m,mod-2);
	sieve(k);
	if(n<k){
		mul=1;//C(n,0)
		for(int i=0;i<=n;i++){
			ans=(ans+1ll*mul*pmul[i]%mod*npmul[n-i]%mod*pw[i]%mod)%mod;
			mul=1ll*mul*inv[i+1]%mod*(n-i)%mod;//C(n,i)->C(n,i+1)
		}
		printf("%d\n",ans);
		return 0;
	}
	S[k]=1;
	mul=n-k;//C(n-k,1)
	for(int i=k-1;i>=0;i--){
		S[i]=(1ll*(1-p+mod)*S[i+1]%mod+1ll*mul*fmul[(k-i)&1]%mod*pmul[k-i]%mod)%mod;
		mul=1ll*mul*inv[k-i+1]%mod*(n-i)%mod;//C(n-i-1,k-i)->C(n-i,k-i+1)
	}
	mul=1;//C(n,0)
	for(int i=0;i<=k;i++){
		ans=(ans+1ll*pmul[i]*pw[i]%mod*mul%mod*S[i]%mod)%mod;
		mul=1ll*mul*inv[i+1]%mod*(n-i)%mod;//C(n,i)-C(n,i+1)
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P6031)

u1s1 这个推式子其实挺套路的吧，可惜有一步没推出来看了题解
$$
\begin{aligned}
res&=\sum\limits_{i=0}^ni^k\dbinom{n}{i}(\dfrac{1}{m})^i(\dfrac{m-1}{m})^{n-i}\\
&=\sum\limits_{i=0}^n\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}i^{\underline{j}}\dbinom{n}{i}(\dfrac{1}{m})^i(\dfrac{m-1}{m})^{n-i}\\
&=(\dfrac{m-1}{m})^{n}\sum\limits_{i=0}^n\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}i^{\underline{j}}\dbinom{n}{i}(\dfrac{1}{m-1})^i\\
&=(\dfrac{m-1}{m})^{n}\sum\limits_{i=0}^n\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}i^{\underline{j}}\dbinom{n}{i}(\dfrac{1}{m-1})^i\\
&=(\dfrac{m-1}{m})^{n}\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}j!\sum\limits_{i=0}^n\dbinom{i}{j}\dbinom{n}{i}(\dfrac{1}{m-1})^i\\
&=(\dfrac{m-1}{m})^{n}\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}(\dfrac{1}{m-1})^j\sum\limits_{i=0}^{n-j}\dbinom{n-j}{i-j}(\dfrac{1}{m-1})^i\\
&=(\dfrac{m-1}{m})^{n}\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}(\dfrac{1}{m-1})^j(\dfrac{m}{m-1})^{n-j}\\
&=\sum\limits_{j=1}^k\begin{Bmatrix}k\\j\end{Bmatrix}j!\dbinom{n}{j}(\dfrac{1}{m})^j\\
&=\sum\limits_{j=1}^k\sum\limits_{l=0}^j\dbinom{j}{l}l^k(-1)^{j-l}\dbinom{n}{j}(\dfrac{1}{m})^j\\
&=\sum\limits_{l=0}^jl^k\sum\limits_{j=1}^k\dbinom{j}{l}(-1)^{j-l}\dbinom{n}{j}(\dfrac{1}{m})^j\\
&=\sum\limits_{l=0}^kl^k\dbinom{n}{l}\sum\limits_{j=l}^k(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^j\\
\end{aligned}
$$
前面那东西我们要枚举 $l$，复杂度自然有一个 $k$，后面那东西看似可以二项式定理，但是由于上界为 $k$ 而不是 $n$，实则不能，因此考虑按照套路进行递推，设 $f_l$​ 表示
$$
f_l=\sum\limits_{j=l}^k(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^j
$$
那么
$$
\begin{aligned}
f_{l-1}&=\sum\limits_{j=l-1}^k(-1)^{j-l+1}\dbinom{n-l+1}{j-l+1}(\dfrac{1}{m})^j\\
&=-\sum\limits_{j=l-1}^k(-1)^{j-l}\dbinom{n-l+1}{j-l+1}(\dfrac{1}{m})^j\\
&=-\sum\limits_{j=l-1}^k(-1)^{j-l}\dbinom{n-l}{j-l+1}(\dfrac{1}{m})^j-\sum\limits_{j=l-1}^k(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^j\\
&=-\sum\limits_{j=l}^{k+1}(-1)^{j-1-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^{j-1}-\sum\limits_{j=l-1}^k(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^j\\
&=m\sum\limits_{j=l}^{k+1}(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^{j}-\sum\limits_{j=l-1}^k(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^j\\
&=m(\sum\limits_{j=l}^{k}(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^{j}+(-1)^{k+1-l}\dbinom{n-l}{k+1-l}(\dfrac{1}{m})^{k+1})-\sum\limits_{j=l}^k(-1)^{j-l}\dbinom{n-l}{j-l}(\dfrac{1}{m})^j\\
&=m(f_l+(-1)^{k+1-l}\dbinom{n-l}{n-k-1}(\dfrac{1}{m})^{k+1})-f_l
\end{aligned}
$$
从后往前一遍递推即可。$\text{id}_k$ 可以一遍线筛筛出，复杂度 $\mathcal O(k)$

至于我是哪里被卡住了呢……在第一个公式的第七个等于号那边，我上来就想拆开来递推，然后发现递推完了要套好几层，然后就 quit 了。事实证明一般只有只带一个组合数的式子才能递推求解。

那么问题就来了，为什么我的 $\mathcal O(k)$ 跑不过 $\mathcal O(k\log k)$/yun/yun

```cpp
const int MAXK=1e7+1;
const int MOD=998244353;
int n,m,k;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int fac[MAXK+5],ifac[MAXK+5],f[MAXK+5],inv[MAXK+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=inv[0]=inv[1]=1)+1;i<=n;i++) inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*inv[i]%MOD;
}
int pwk[MAXK+5],pr[MAXK/10+5],prcnt=0;
bitset<MAXK+5> vis;
void sieve(int n){
	pwk[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]) pwk[i]=qpow(i,k);
		for(int j=1;j<=prcnt&&pr[j]*i<=n;j++){
			vis[pr[j]*i]=1;pwk[pr[j]*i]=1ll*pwk[pr[j]]*pwk[i]%MOD;
			if(i%pr[j]==0) break;
		}
	}
}
int main(){
	init_fac(MAXK);int res=0;
	scanf("%d%d%d",&n,&m,&k);sieve(k+1);
	int ivm=qpow(m,MOD-2),pw=qpow(ivm,k+1);
	for(int l=k+1,cur=1;l>=2;l--){
		int t=1ll*cur*pw%MOD;
//		printf("%d\n",cur);
		if((k+1-l)&1) f[l-1]=(1ll*m*(f[l]-t+MOD)%MOD-f[l]+MOD)%MOD;
		else f[l-1]=(1ll*m*(f[l]+t)%MOD-f[l]+MOD)%MOD;
		cur=1ll*cur*(n-l+1+MOD)%MOD*inv[k+2-l]%MOD;
	}
	for(int l=1,cur=n;l<=k;l++){
		res=(res+1ll*f[l]*pwk[l]%MOD*cur)%MOD;
		cur=1ll*cur*(n-l)%MOD*inv[l+1]%MOD;
	} printf("%d\n",res);
	return 0;
}
```


---

