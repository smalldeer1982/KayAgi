# [NERC 2020 Online] Find a Square

## 题目描述

Frank 喜欢平方数。平方数是指某个整数与自身相乘得到的数。Frank 还喜欢二次多项式，他尤其钟爱一个特定的二次多项式：$p(x) = a \cdot x^2 + b \cdot x + c$。

今天早上，Frank 用他最喜欢的二次多项式计算了从 $0$ 开始的连续 $n$ 个整数的值，并将所有结果相乘。

如果最终乘积是一个平方数，那么他今天就会非常开心。但实际情况可能并非如此。因此，他请你找出这个乘积的最大平方因数。


## 说明/提示

在第一个样例中，乘积为 $1 \cdot 3 \cdot 7 \cdot 13 \cdot 21 \cdot 31 \cdot 43 \cdot 57 \cdot 73 \cdot 91 = 2893684641939 = 38826291 \cdot 273^2$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1 1 1 10```

### 输出

```
74529```

## 样例 #2

### 输入

```
1 2 1 10```

### 输出

```
189347824```

# 题解

## 作者：littlez_meow (赞：2)

似乎只能分解质因数。直接分解质因数是 $O(n^{\frac 7 4})$，显然跑不了。

那就要分析 $P(n)$ 的性质。感觉起来这个问题可能稍微比分解质因数弱一点，但是没有弱特别多，所以应该不太能 $O(\operatorname{polylog}(n))$。非筛法的数论题中常见的复杂度还有 $\dfrac 1 3$ 次方和 $\dfrac 1 4$ 次方，但是这个和 $\dfrac 1 4$ 次方的分解质因数与最小原根看起来没什么关系。那初步判断可能就是 $O(P(n)^{\frac 1 3}\operatorname{polylog}(n))$。

常见的 $\dfrac 1 3$ 的算法是先把小于等于 $\dfrac 1 3$ 次方的质数除掉，剩下的至多为两个质数相乘。我们也尝试往这个方向靠。

接下来我们把 $P$ 看成一个数组，称把 $P(x)$ 除掉 $i$ 表示若 $i|P(x)$ 则 $P(x)\leftarrow\dfrac{P(x)}i$，否则 $P(x)$ 不变。

对于某个质数 $p$，若 $\gcd(2a,p)=1$，那么同余方程 $P(x)\equiv 0\pmod p$ 至多只有两个解 $2ax\equiv-b\pm\sqrt{b^2-4ac}\pmod p$，其中根号可以用 cipolla 算法来算二次剩余求。解出 $x$ 后我们就知道有哪些 $i\in[0,n-1]$ 满足 $P(i)\equiv 0\pmod p$，它们满足 $i\equiv x\pmod p$，一共只有 $\lfloor\dfrac n p\rfloor$ 个。

那么从小到大枚举质数 $p$，一直枚举到 $\sqrt[3]{P(n-1)}$。若 $\gcd(p,2a)\neq 1$，就遍历每个 $P(i)$ 把 $p$ 除掉。否则就解出 $P(x)\equiv 0\pmod p$ 然后把满足 $i\equiv x\pmod p$ 的 $P(i)$ 中除掉 $p$。这一部分的时间复杂度是 $O(n\log n)$。

把所有质数都这样处理过一遍后，先把 $P$ 中剩下的平方数统计进答案并设为 $1$。$P$ 数组中剩下的元素要么是 $1$，要么是质数 $p$，要么是两个不同的质数之积 $pq$。能对答案造成贡献的质数至少要能整除 $P$ 中两个数。

考虑 $P(x)$ 和 $P(y)$ 一开始的 $\gcd$。我们有 $\gcd(P(x),P(y))=\gcd(P(x),a(x^2-y^2)+b(x-y))=\gcd(P(x),(x-y)(a(x+y)+b))$。也就是说，至少能整除两个 $P$ 中元素的质数 $p$ 要么是一个 $<n$ 的数的因数，要么是一个形如 $ax+b,x<2n$ 的数的因数。

$p$ 是一个 $<n$ 的数的因数的情况我们上面已经处理过了。怎么处理第二种情况呢？

你发现这个问题和原问题很类似。原问题是对二次函数 $P(x)=ax^2+bx+c$ 质因数分解 $P(i),i\in[0,n-1]$，现在的问题是要对一次函数 $Q(x)=ax+b$ 分解 $Q(i),i\in[0,2n-1]$。

那么类似地，从小到大枚举质数 $p$，一直枚举到 $\sqrt{Q(2n-1)}$，如果 $\gcd(a,p)\neq 1$ 就暴力除，否则解出 $Q(x)\equiv 0\pmod p$ 然后对 $i\equiv x\pmod p$ 的 $Q(i)$ 除掉 $p$。

处理过后 $Q$ 中元素要么是 $>\sqrt{Q(2n-1)}$ 质数要么是 $1$。

由于 $O(\sqrt Q(2n))=O(\sqrt[3]{P(n)}$，其实 $\le\sqrt{Q(2n)}$ 的质数我们也处理过了，我们只需要处理现在 $Q$ 中的非 $1$ 元素 $p$ 即可。处理方式即解出 $P(x)\equiv 0\pmod p$，同上。

总时间复杂度是 $O(n\log n)$。

注意很多地方要开 `long long` 和 `__int128`。

### 代码

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i)
#define ll long long
#define File(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
using namespace std;
const int MAXN=1.3e6+1,MOD=1e9+7;
namespace Quadratic{
	ll imod,p;
	mt19937_64 gen(20090708);
	inline ll qpow(__int128 b,ll e){ll res=1;while(e)(e&1)&&(res=res*b%p),b=b*b%p,e>>=1;return res;}
	inline bool euler(ll x){return qpow(x,(p-1)>>1)==1;}
	struct Complex{
		__int128 re,im;
		inline bool operator==(Complex x){return re==x.re&&im==x.im;}
		inline Complex operator*(Complex x){return (Complex){(re*x.re+imod*x.im%p*im)%p,(im*x.re+re*x.im)%p};}
		inline Complex operator^(ll expo){
			Complex res({1,0}),base(*this);
			while(expo){
				(expo&1)&&(res=res*base,1);
				base=base*base;
				expo>>=1;
			}
			return res;
		}
	};
	inline void cipolla(ll&x1,ll&x2,ll n){
		__int128 a;
		do{
			a=gen()%p,imod=a*a%p-n;
			imod<0&&(imod+=p);
		}while(!a||euler(imod));
		x1=((Complex){a,1}^((p+1)>>1)).re;
		x2=p-x1;
		return;
	}
	ll x1,x2;
	inline void solve(ll pr,ll x){
		p=pr;(x%=p)<0&&(x+=p);x1=x2=-1;
		if(x==0) return x1=0,void();
		if(!euler(x)) return;
		cipolla(x1,x2,x);
		return;
	}
}
inline ll qpow(__int128 b,ll e,const ll M){(b>=M)&&(b%=M);ll res=1;while(e)(e&1)&&(res=res*b%M),b=b*b%M,e>>=1;return res;}
inline ll qpow(ll b,int e){(b>=MOD)&&(b%=MOD);ll res=1;while(e)(e&1)&&(res=res*b%MOD),b=b*b%MOD,e>>=1;return res;}
int pr[MAXN],cnt,vis[MAXN];
inline void init(){
	F(i,2,MAXN-1){
		!vis[i]&&(pr[++cnt]=i,vis[i]=i);
		F(j,1,cnt){
			int t=i*pr[j];
			if(t>MAXN-1) break;
			vis[t]=pr[j];
			if(vis[i]==pr[j]) break;
		}
	}
	return;
}
int a,b,c,n;
ll delta,p[MAXN],q[MAXN],ans=1;
__gnu_pbds::gp_hash_table<ll,int>e;
inline void ins(ll pri){
	Quadratic::solve(pri,delta);
	__int128 xx[2]={Quadratic::x1,Quadratic::x2};
	ll inv=qpow(a+a,pri-2,pri);
	F(j,0,1) if(xx[j]!=-1) xx[j]=((xx[j]-b)*inv%pri+pri)%pri;
	for(auto x:xx) if(x!=-1) for(ll j=x;j<n;j+=pri) while(p[j]%pri==0) p[j]/=pri,++e[pri];
}
signed main(){ 
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	init();
	cin>>a>>b>>c>>n;delta=b*1ll*b-4ll*a*c;
	F(i,0,n-1) p[i]=a*1ll*i*i+b*1ll*i+c;
	F(i,1,cnt){
		if(__gcd(pr[i],2*a)!=1){
			F(j,0,n-1) while(p[j]%pr[i]==0) p[j]/=pr[i],++e[pr[i]];
			continue;
		}
		ins(pr[i]);
	}
	F(i,0,n-1) if(p[i]!=1){
		ll qwq=sqrt(p[i]);
		if(qwq*qwq==p[i]) ans=p[i]%MOD*ans%MOD,p[i]=1;
	}
	F(i,0,2*n-1) q[i]=a*1ll*i+b;
	F(i,1,cnt){
		if(__gcd(pr[i],a)!=1){
			F(j,0,2*n-1) while(q[j]%pr[i]==0) q[j]/=pr[i];
			continue;
		}
		ll x=pr[i]-qpow(a,pr[i]-2,pr[i])*b%pr[i];
		(x>=pr[i])&&(x-=pr[i]);
		for(ll j=x;j<2*n;j+=pr[i]) while(q[j]%pr[i]==0) q[j]/=pr[i];
	}
	F(i,0,2*n-1) if(q[i]!=1) ins(q[i]);
	for(auto i:e) ans=ans*qpow(i.first,i.second-(i.second&1))%MOD;
	cout<<ans;
	return 0;
}

---

