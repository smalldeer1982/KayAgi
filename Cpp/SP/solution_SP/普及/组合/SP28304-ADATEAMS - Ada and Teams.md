# ADATEAMS - Ada and Teams

## 题目描述

有 $N$ 所学校，要从中选择 $A$ 所学校出来参赛。每一所学校中一共有 $B$ 名学生，每所参赛的学校会从中选择$D$ 名学生参赛，问一共有多少种不同的选择方案。

# 题解

## 作者：DecemberFox (赞：3)

# SP28304

## 题目分析

本题大致意思为从 $n$ 所学校中选出 $a$ 所后，然后再从这 $a$ 所各有 $b$ 人的学校中选出 $d$ 名学生，求最终的方案数。

## 解法分析

本题需要排列组合及乘法逆元的前置知识。

本题为一个排列组合题目。

其中，从 $n$ 所学校选 $a$ 所学校共有 $C^a_n$ 种方案，而从 $1$ 所学校的 $b$ 名学生中选出 $d$ 名学生的方案数为 $C^d_b$，根据乘法原理在 $a$ 所学校种就总共有 $(C^d_b)^a$ 种方案，最后再乘上选取学校的方案数 $C^a_n$ 即可。

即最终答案为 $C^a_n\times (C^d_b)^a$。

因为最终答案需要模 $10^9+7$，因此这里使用预处理阶乘及其乘法逆元的方法来计算组合数的值。

```cpp
#include<iostream>
#include<cstdio>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int n(1);
		now=0;
#define isdigit(c) ((c)>='0'&&(c)<='9')
		while(!isdigit(c)){if(c=='-') n=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
#undef isdigit
		now*=n;
		read(next...);
	}
	template<typename nowtype>
	void write(nowtype num,char end='\n')
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
	template<typename nowtype,typename ...nexttype>
	void write(nowtype num,char end,nexttype ...next)
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
		write(next...);
	}
}
//以上为快读快写
using namespace io;
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const int const1=1e6+10;
	const ll mod=1e9+7;
	ll f[const1],g[const1];
	ll pow(ll a,ll x)//快速幂
	{
		ll ans(1);
		while(x)
		{
			if(x&1) ans=ans*a%mod;
			a=a*a%mod;
			x>>=1;
		}
		return ans;
	}
	void init()//初始化阶乘及其逆元
	{
		ll i;
		f[0]=g[0]=1;
		for(i=1;i<const1;++i)
		{
			f[i]=f[i-1]*i%mod;
			g[i]=g[i-1]*pow(i,mod-2)%mod;
		}
	}
	ll C(ll n,ll m)//求组合数
	{
		return f[n]*g[m]%mod*g[n-m]%mod;
	}
	void solve()
	{
		ll n,a,b,d;
		init();
		while(scanf("%lld%lld%lld%lld",&n,&a,&b,&d)!=EOF) write(C(n,a)*pow(C(b,d),a)%mod);
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：1)

## 分析
这种从一个集合中选 $n$ 个数据的题一看就是要用[组合数](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0/2153250)。从 $N$ 所学校中选 $A$ 所的方案数为 $C _ {N} ^ {A}=\frac{N!}{A!(N-A)!}$，从 $B$ 名学生中选 $D$ 名的方案数为 $C _ {B} ^ {D}=\frac{B!}{D!(D-B)!}$，由[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447)得，总方案数为 $C _ {N} ^ {A} \times (C _ {B} ^ {D})^{A}$。

**但是**，题目要求我们对 $10 ^ {9} + 7$ 取模，这个时候就有个问题，答案是个**有理数**，不能直接取模，所以要取**逆元**。

逆元，相当于在模意义下的倒数，即 $a \cdot a ^ {-1} \equiv 1 \pmod p$，求法有扩展欧几里得法，在 $\gcd(a,p) = 1$ 时使用，和费马小定理法，在模数为质数时使用，所以此题我们选用费马小定理法。

费马小定理：当模数 $p$ 为质数时，有 $a^{p - 1} \equiv 1 \pmod p$。

由费马小定理得：$a^{p-2} \equiv a^{-1}\ \pmod p$。所以我们就可以用快速幂来求逆元了。

还有一个方法线性时间复杂度求阶乘逆元，但是本题用不上，~~绝对不是我懒得讲~~。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define inv(x) qpow(x,MOD - 2) // 费马小定理求逆元
using namespace std;

constexpr int MOD = 1e9 + 7,MAXN = 1e6 + 24;
int qpow(int b,int p)
{
    int res = 1;
    while(p)
    {
        if(p & 1)
            res = res * b % MOD;
        b = b * b % MOD;
        p >>= 1;
    }
    return res;
}
int fac[MAXN]; //预处理阶乘
int T,n,a,b,d;
int Comp(int n,int m)
{
    return (fac[m] * inv(fac[n]) % MOD * inv(fac[m - n] % MOD)) % MOD;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    fac[0] = 1; //不要直接用花括号初始化,数组大了会CE
    for(int i = 1;i <= 1e6 + 1;i++)
        fac[i] = fac[i - 1] * i % MOD;
    while(scanf("%lld %lld %lld %lld",&n,&a,&b,&d) != EOF)
    {
        int scd = Comp(d,b);
        printf("%lld\n",Comp(a,n) * qpow(scd,a) % MOD);
    }
}
```

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP28304)

# 前置知识

[乘法逆元](https://oi-wiki.org/math/number-theory/inverse/) | [排列组合](https://oi-wiki.org/math/combinatorics/combination/)

# 解法

简单的排列组合。从 $n$ 个学校中选出 $a$ 个学校，共有 $\dbinom{n}{a}$ 种不同的方案数。选出的 $a$ 个学校中每所学校再从 $b$ 个人中选出 $d$ 个人，共有 $\dbinom{b}{d}^a$ 种不同的方案数。依据乘法原理，二者相乘即为所求。

另外，记得预处理阶乘和逆元。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
ll jc[1000001],inv[1000001],jc_inv[1000001];
ll C(ll n,ll m,ll p)
{
    if(n>=m&&n>=0&&m>=0)
    {
        return (jc[n]*jc_inv[m]%p)*jc_inv[n-m]%p;
    }
    else
    {
        return 0;
    }
}
ll qpow(ll a,ll b,ll p)
{
    ll ans=1;
    while(b>0)
    {
        if(b&1)
        {
            ans=ans*a%p;
        }
        b>>=1;
        a=a*a%p;
    }
    return ans;
}
int main()
{
    ll n,a,b,d,i,p=1000000007;
    inv[1]=1;
    jc[0]=jc_inv[0]=jc[1]=jc_inv[1]=1;
    for(i=2;i<=1000000;i++)
    {
        inv[i]=(p-p/i)*inv[p%i]%p;
        jc[i]=jc[i-1]*i%p;
        jc_inv[i]=jc_inv[i-1]*inv[i]%p;
    }
    while(cin>>n>>a>>b>>d)
    {
        cout<<C(n,a,p)*qpow(C(b,d,p),a,p)%p<<endl;
    }
    return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/SP28304)      
是首 A，不过这道水题为啥没人切呢？   
## 题意
有 $n$ 所学校，选出 $a$ 个学校，每个学校有 $b$ 名学生，选出的学校里又选出 $d$ 个学生，求方案数。   
## 解法
我们容易发现从 $n$ 所学校选出 $a$ 所和从 $d$ 名学生选出 $b$ 名都是组合问题，结果分别为 $C^a_n$ 和 $C^d_b$。       
同时，根据乘法原理可得 $a$ 所学校的方案数为 $(C^d_b)^a$。    
同样是乘法原理，我们可得答案为 $C^a_n\times(C^d_b)^a$。     
根据组合数公式，上式可化简为 $\dfrac{\frac{n!}{(n-a)!}}{a!}\times(\dfrac{\frac{b!}{(b-d)!}}{d!})^a$。       
因为要模 $10^9+7$ 且这个数为质数，我们除法时可以用快速幂求逆元。        
这个结果里求幂我们可以用快速幂，而阶乘可以预处理。      
这么做的时间复杂度为 $O(t\log a)$，$t$ 为数据组数，注意本题多测。        
那么我们的代码也很容易写了。     
[CODE](https://www.luogu.com.cn/paste/ld19o8eh)

---

## 作者：Alice2012 (赞：0)

简单数学题。

分步运算用乘法原理。从 $N$ 所学校中选出 $A$ 所的方案数是 $C_{N}^{A}$，每所学校从 $B$ 个学生中选出 $D$ 名的方案数是 $C_{B}^{D}$，那么 $N$ 所学校选学生的总方案数就是 $(C_{B}^{D})^N$。根据乘法原理，总的方案数就是 $C_{N}^{A}\times (C_{B}^{D})^N$。

计算组合数使用公式 $C_{N}^{M}=\dfrac{n!}{m!\times (n-m)!}$，可以预处理阶乘并使用逆元求解。

注意要随时取模，且要开 `long long`。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=1e9+7;
int n,A,B,D,fac[N]; 
int fpow(int a,int b,int p){int ans=1;while(b){if(b&1)ans=ans*a%p;a=a*a%p,b>>=1;}return ans;}//快速幂 
int inv(int x,int p){return fpow(x,p-2,p);}//费马小求逆元 
int C(int n,int m,int p){if(n<m)return 0;return ((fac[n]*inv(fac[m],p))%p*inv(fac[n-m],p))%p;}//组合数 
signed main(){
	fac[0]=1;
	for(int i=1;i<=1e6;i++)fac[i]=fac[i-1]*i%mod;//预处理阶乘 
	while(cin>>n>>A>>B>>D)
		cout<<fpow(C(B,D,mod),A,mod)*C(n,A,mod)%mod<<"\n";//计算公式+输出答案 
	return 0;
}
```

---

## 作者：zzhbpyy (赞：0)

### [ADATEAMS](https://www.spoj.com/problems/ADATEAMS/)

## 分析

就是一道求组合数的模板体。从 $N$ 个学校中选出 $A$ 个的方案数为 $\binom{N}{A}$，从任意一个有 $B$ 个人的学校里选 $D$ 个的方案数为 $\binom{B}{D}$。根据乘法定理，答案就是 $\binom{N}{A}\times \binom{B}{D}^A$。求组合数可以预处理 $1$ 到 $10^6$ 之间所有数的阶乘和它们的逆元。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,a,b,d,fac[1000005],inv[1000005];
int po(int a,int b){
	if(b==1)return a;
	if(b==0)return 1;
	int d=po(a,b>>1);
	return d*d%mod*po(a,b&1)%mod;
}
inline int c(int n,int m){
	if(m==0||m==n)return 1;
	return fac[n]*inv[n-m]%mod*inv[m]%mod;
}
signed main(){
	fac[0]=1;
	for(int i=1;i<=1000000;i++)fac[i]=fac[i-1]*i%mod;
	inv[1000000]=po(fac[1000000],mod-2);
	for(int i=999999;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
	ios::sync_with_stdio(0),cin.tie(nullptr);
	while(cin>>n>>a>>b>>d){
		int u=c(b,d);
		cout<<po(u,a)*c(n,a)%mod<<'\n';
	}
}
```

---

## 作者：Eterna (赞：0)

一道简单的数学题。

我们可以按题意一段一段地考虑。

有 $N$ 所学校，要从中选择 $A$ 所学校出来参赛。

显然的，这部分答案是 $C_N^A$。

再看后面，每一所学校中一共有 $B$ 名学生，每所参赛的学校会从中选择 $D$ 名学生参赛。

对于一所学校的情况，结果是 $C_B^D$。

而现在是 $A$ 所学校，自然就是 $(C_B^D)^a$。

但是，我们发现组合数的计算是 $O(n)$ 的，我们可以想到预处理阶乘，因为组合数有除法，所以要逆元。

###   code


```cpp
int C(int n,int m){return (jc[n]*jv[m]%p)*jv[n-m]%p;}
int qpow(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%p;
        b>>=1;a=a*a%p;
    }
    return ans;
}
signed main()
{
    inv[1]=jc[0]=jv[0]=jc[1]=jv[1]=1;
    for(int i=2;i<=1000000;i++)inv[i]=(p-p/i)*inv[p%i]%p,jc[i]=jc[i-1]*i%p,jv[i]=jv[i-1]*inv[i]%p;
    while(cin>>n>>a>>b>>d)cout<<(C(n,a)*qpow(C(b,d),a))%p<<endl;
    return 0;
}
```

---

## 作者：Linge_Zzzz (赞：0)

题面不再赘述。

从 $n$ 个学校中选 $a$ 个的方案数是 $C_n^a$。

同样地，从 $b$ 个人中选 $d$ 个的方案数是 $C_b^d$。

$a$ 个学校，每个学校从 $b$ 个人中选 $d$ 个，根据乘法原理，方案数为 $(C_b^d)^a$。

再根据乘法原理可得问题的解为 $C_n^a\times (C_b^d)^a$。

众所周知 $C_n^m=\frac{n!}{(n-m)!m!}$，所以我们预处理阶乘和阶乘的逆元之后就可以 $O(1)$ 回答组合数 $\bmod (10^9+7)$ 的值。

注意多测，没有给出数据组数。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;
const ll mod=1e9+7;
int n,a,b,d;
ll qpow(ll a,ll p){
	ll ans=1;
	while(p){
		if(p&1)ans=ans*a%mod;
		a=a*a%mod;
		p>>=1;
	}
	return ans;
}
ll jc[N],jcinv[N];
void init(){
	jc[0]=jcinv[0]=1;
	for(ll i=1;i<N;i++){
		jc[i]=jc[i-1]*i%mod;
		jcinv[i]=qpow(jc[i],mod-2);
	}
}
ll C(ll n,ll m){return jc[n]*jcinv[n-m]%mod*jcinv[m]%mod;}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	init();
	while(cin>>n>>a>>b>>d)cout<<C(n,a)*qpow(C(b,d),a)%mod<<'\n';
	return 0;
}
```

---

