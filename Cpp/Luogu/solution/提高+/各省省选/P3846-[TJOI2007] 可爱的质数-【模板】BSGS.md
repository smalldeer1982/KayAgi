# [TJOI2007] 可爱的质数/【模板】BSGS

## 题目描述

给定一个质数 $p$，以及一个整数 $b$，一个整数 $n$，现在要求你计算一个最小的非负整数 $l$，满足 $b^l \equiv n \pmod p$。

## 说明/提示

#### 数据规模与约定

- 对于所有的测试点，保证 $2\le b < p<2^{31},1\leq n<p$。

## 样例 #1

### 输入

```
5 2 3
```

### 输出

```
3```

# 题解

## 作者：zombie462 (赞：105)

这道题的数据范围很友好（$p<2^{31}$），可以直接使用 `Baby Step Giant Step` ~~水~~过。然而，如果数据加强到 $p\leq 10^{18}$ ，我们也可以通过它。

这篇题解讲述的是如何使用优化后的 `Pohlig-Hellman` 通过本题。

为了达成这一点，下面的优化算法含有以下前置知识（如果你有哪一个前置知识不理解，那么请事先查看有关知识）

+ `Miller-Rabin`

+ `Pollard-Rho`

+ `Excrt`

+ `Baby Step Giant Step`

+ `Exgcd`

+ 一般的 `DLP` 算法

我们先从阶讲起：

设 $a,p\in z,\gcd(a,p)=1$，使 $a^n\equiv 1\pmod p$ 成立的最小正整数 $n$ 称为 $a$ 模 $p$ 的阶，记作 $ord_p(a)=n$

设 $ord(a)=n=\prod^m_{i=1}q^{k_i}_i$。

令 $r_i=\dfrac{n}{q_i^{k^i}}$，由 $a^x\equiv b\pmod p,(a^x)^{r_i}\equiv b^{r_i}\pmod p$。

显然，$ord(a^{r_i})^x=q_i^{k_i}$，$(a^{r_i})^x\equiv b^{r_i}\pmod p$。

设 $(a^{r_i})^x\equiv b^{r_i}\pmod p$ 的解为 $x_i$，则原问题的解 $x$ 满足 $x\equiv x_i\pmod{q_i^{k_i}}$

若能求出这 $m$ 个 $q^k$ 阶的 `DLP`，则可以进一步通过 `CRT` 进行合并求解。

设 $ord(a)=q^k$，其中 $q$ 为一个质数。

显然有 $0\leq x<q^k$，设：

$x=x_0+x_1q+x_2q^2+\cdots+x_{k-1}q^{k-1},0\leq x_i<q$
                                                    
则有：

$(a^x)^{q^{k-1}}=(a^{x_0+x_1q+x_2q^2+\cdots+x_{k-1}q^{k-1}})^{q^{k-1}}\equiv a^{x_0q^{k-1}}\equiv (a^{q^{k-1}})^{x_0}\equiv b^{q^{k-1}}\pmod p$


所以 $ord(a^{q^{k-1}})=q$。

这样我们就能通过求解一个 $q$ 阶的 `DLP` 得到 $x_0$ 的值。

得出 $x_0$ 后，我们可以用类似的方法解出：

$(a^x)^{q^{k-2}}=(a^{x_0+x_1q+x_2q^2+\cdots+x_{k-1}q^{k-1}})^{q^{k-2}}\equiv a^{x_0q^{k-2}+x_1q^{k-1}}\equiv b^{q^{k-2}}\pmod p$

由于我们已经知道了 $x_0$ 的值，于是有：

$(a^{q^{k-1}})^{x_1}\equiv b^{q^{k-2}}\cdot a^{-x_0q^{k-2}}\pmod p$

可以发现如果我们一直这样递归下去，左边一直都是 $(a^{q^{k-1}})^{x_i}$。

右边显然可以简便计算。

对于每一个 $q$，只需要进行一次 `BSGS` 的预处理即可。

时间复杂度特别玄学，但是 $p\leq 10^{18}$ 且 $p$ 不怎么毒瘤能够通过。具体地，复杂度取决于分解 $p$ 的质因子的速度，这部分可以用某个神奇的 `Pollard-Rho` 优化。

（但是似乎不见得这道题跑得比直接的 `BSGS` 快）

总之这道题就相当于把无数个模板无缝衔接就是了！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define IL __int128
LL read(){
	LL x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';ch=getchar();
	}
	return x*f;
}
namespace PhoRho{ //Phollard-Rho不解释（见Luogu P4718）
	LL gcd(LL a,LL b){
		if (b==0) return a;
		return gcd(b,a%b);
	}
	LL fastpow(LL x,LL p,LL mod){
		LL ans=1;
		while (p){
			if (p&1) ans=(IL)ans*x%mod;
			x=(IL)x*x%mod;
			p>>=1;
		}
		return ans;
	}
	LL max_factor;
	bool MillerRabin(LL x,LL b){
		LL k=x-1;
		while (k){
			LL cur=fastpow(b,k,x);
			if (cur!=1 && cur!=x-1) return false;
			if ((k&1)==1 || cur==x-1) return true;
			k>>=1;
		}
		return true;
	}
	bool prime(LL x){
		if (x==46856248255981LL || x<2) return false;
		if (x==2 || x==3 || x==7 || x==61 || x==24251) return true;
		return MillerRabin(x,2) && MillerRabin(x,3) && MillerRabin(x,7) && MillerRabin(x,61);
	}
	LL f(LL x,LL c,LL n){
		return ((IL)x*x+c)%n;
	}
	LL PRho(LL x){
		LL s=0,t=0,c=1LL*rand()*(x-1)+1;
		int stp=0,goal=1;
		LL val=1;
		for (goal=1;;goal<<=1,s=t,val=1){
			for (stp=1;stp<=goal;++stp){
				t=f(t,c,x);
				val=(IL)val*abs(t-s)%x;
				if (stp%127==0){
					LL d=gcd(val,x);
					if (d>1) return d;
				}
			}
			LL d=gcd(val,x);
			if (d>1) return d;
		}
	}
	void fac(LL x){
		if (x<=max_factor || x<2){
			return;
		}
		if (prime(x)){
			max_factor=max_factor>x?max_factor:x;
			return;
		}
		LL p=x;
		while (p>=x) p=PRho(x);
		while ((x%p==0)) x/=p;
		fac(x);fac(p);
	}
	LL divide(LL n){
		srand((unsigned)time(NULL));
		max_factor=0;
		fac(n);
		return max_factor;
	}
} 
namespace DLP{
	const int N=1111111;
	LL fastpow(LL a,LL n){ //快速幂不解释
		LL res=1;
		while (n>0){
			if (n&1) res=res*a;
			a=a*a;
			n>>=1;
		}
		return res;
	}
	LL fastpow(LL a,LL n,LL p){ //快速幂*2不解释
		LL res=1;
		a%=p;
		while (n>0){
			if (n&1) res=(IL)res*a%p;
			a=(IL)a*a%p;
			n>>=1;
		}
		return res;
	}
	int prime[N],ptot;
	bool ispr[N];
	struct pt{
		LL p;
		int c;
	};
	void getprime(){ //获取10^6以内的质数
		memset(ispr,1,sizeof(ispr));
		for (int i=2;i<N;++i){
			if (ispr[i]) prime[++ptot]=i;
			for (int j=1;j<=ptot && prime[j]<=(N-1)/i;++j){
				ispr[i*prime[j]]=0;
				if (!i%prime[j]) break;
			}
		}
	}
	bool cmp(pt x,pt y){
		return x.p<y.p;
	}
	void findorg(vector <pt> &v,LL num){ //num分解质因数
		while (num>=N){ //大于10^6的部分，每次用Pho-Rho算法找出最大的一个质因子，然后除掉即可
			LL maxf=PhoRho::divide(num);
			int cnt=0;
			while (num%maxf==0){
				cnt++;
				num=num/maxf;
			}
			v.push_back((pt){maxf,cnt});
		}
		if (ptot==0) getprime();
		for (int i=1;i<=ptot && prime[i]<=num;++i){ //剩下的就是不大于10^6的质因子了，直接暴力枚举
			if (num%prime[i]==0){
				int cnt=0;
				while (num%prime[i]==0){
					cnt++;
					num/=prime[i];
				}
				v.push_back((pt){prime[i],cnt});
			}
		}
		if (num>1) v.push_back((pt){num,1});
		sort(v.begin(),v.end(),cmp); //这句话说实在没有意义
	}
	int getorg(LL p,LL phi,vector <pt> &v){ //获取ord
		for (int k=2;;k++){
			int flag=1;
			for (int i=0;i<(int)v.size();++i){
				if (fastpow(k,phi/v[i].p,p)==1){
					flag=0;
					break;
				}
			}
			if (flag) return k;
		}
	}
	LL BSGS(LL a,LL b,LL p,LL mod){ //BSGS模板，具体可以见其它题解的一般做法
		a%=mod;b%=mod;
		if (b==1) return 0;
		if (a==0){
			if (b==0) return 1;
			else return -1;
		}
		LL t=1;
		int m=int(sqrt(1.0*p)+1);
		LL base=b;
		unordered_map <LL,LL> vis;
		for (int i=0;i<m;++i){
			vis[base]=i;
			base=(IL)base*a%mod;
		}
		base=fastpow(a,m,mod);
		LL now=t;
		for (int i=1;i<=m+1;++i){
			now=(IL)now*base%mod;
			if (vis.count(now)) return i*m-vis[now];
		}
		return -1;
	}
	LL getksi(LL g,LL h,LL p,LL c,LL n,LL mod){ //得到合并后的解集，然后上BSGS
		vector <LL> pi;
		LL tp=1;
		for (int i=0;i<=c;++i){
			pi.push_back(tp);
			tp*=p;
		}
		LL gq=fastpow(g,pi[c-1],mod);
		LL inv=0;
		tp=1;
		for (int i=c-1;i>=0;--i){
			LL tx=tp*BSGS(gq,fastpow((IL)h*fastpow(g,pi[c]-inv,mod)%mod,pi[i],mod),p,mod);
			inv+=tx;tp*=p;
		}
		return inv;
	}
	LL exgcd(LL a,LL b,LL &x,LL &y){ //exgcd模板不解释
		if (b==0){
			x=1;y=0;
			return a;
		}
		LL d=exgcd(b,a%b,y,x);
		y-=a/b*x;
		return d;
	}
	LL getinv(LL a,LL p){ //逆元不解释
		if (a==0) return 1;
		LL x,y;
		exgcd(a,p,x,y);
		return (x%p+p)%p;
	}
	LL gcd(LL x,LL y){ //gcd不解释
		if (x%y==0) return y;
		return gcd(y,x%y);
	}
	LL ExgcdSolve(LL a,LL b,LL c,LL &x,LL &y){ //求解exgcd
		LL d;
		if (c%(d=gcd(a,b))) return -1;
		a/=d;b/=d;c/=d;
		exgcd(a,b,x,y);
		x=(IL)x*c%b;
		while (x<=0) x+=b;
		return x; 
	}
	LL crt(vector <LL> ksi,vector <pt> v){ //crt不解释
		int sz=v.size();
		LL M=1,ans=0;
		vector <LL> m;
		for (int i=0;i<sz;++i){
			m.push_back(fastpow(v[i].p,v[i].c));
			M*=m[i];
		}
		for (int i=0;i<sz;++i){
			LL Mi=M/m[i];
			ans=((IL)ans+(IL)Mi*getinv(Mi,m[i])*ksi[i])%M;
		}
		if (ans<0) ans+=M;
		return ans;
	}
	LL getx(LL h,LL g,LL N,LL mod,vector <pt> &v){ //获取解集，然后用crt合并
		vector <LL> ksi;
		for (pt tp:v){
			LL tg=fastpow(g,N/fastpow(tp.p,tp.c),mod);
			LL th=fastpow(h,N/fastpow(tp.p,tp.c),mod);
			ksi.push_back(getksi(tg,th,tp.p,tp.c,N,mod));
		}
		return crt(ksi,v);
	}
	LL solve(LL g,LL h,LL p){ //求解
		if (h==1) return 0;
		LL phiP=p-1;
		vector <pt> v;
		findorg(v,phiP);
		int rt=getorg(p,phiP,v);
		LL x=getx(g,rt,phiP,p,v);
		LL y=getx(h,rt,phiP,p,v);
		LL a=0,b=0;
		if (x==0){
			if (y==0) return 1;
			else if (y==1) return 0;
			else return -1;
		}else return ExgcdSolve(x,phiP,y,a,b);
	}
};
signed main(){
	LL p=read(),g=read(),h=read(); 
    LL ans=DLP::solve(g,h,p);
    if (ans==-1) puts("no solution");
    else cout<<ans<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```


---

## 作者：Isprime (赞：70)

BSGS板子题。

大步小步算法(Baby Step,Giant Step,BSGS)用来求解形如$a^x\equiv b(mod\;p)$或$x^a\equiv b(mod\;p)$的高次同余方程，其中a,b,p已经被给出。

第一种方程就是本题，第二种叫做`N次剩余`，也可以用BSGS算法求解~~但是比这个难多了~~。

题目告诉我们 $a,p$ 互质，由此可得在模 $p$ 意义下可以执行关于 $a$ 的乘除运算。设 $t=\biggl\lfloor\sqrt{p}\biggr\rfloor,0≤j≤t-1$，设$x=i*t-j$,可得 $a^{i*t-j}\equiv b(mod\; p)$，同乘 $a^j$ 可得 $(a^t)^i\equiv b*a^j(mod\; p)$.

那么怎么求解这个方程呢？

考虑对于所有的 $j∈[0,t-1]$ 把 $b*a^j\;mod\;p$ 插入一个Hash表，枚举 $i∈[0,t]$，计算出 $(a^t)^i\;mod\;p$，在Hash表中查找是否存在对应的 $j$ 并更新答案，这样就得出了 $i,j$ ，又因为 $t$ 已知，所以可以求出方程的解 $x$ . 

时间复杂度 $O(t)$，即 $O(\sqrt{p})$，数据规模 $10^{16}$ 以下都没有什么大问题。

如果到 $10^{18}$ BSGS算法就废了题解里有神仙说用`Pohlig-Hellman`但我也不晓得这是个啥（

Code（其实BSGS理解了思路之后代码很好写）

（数论基本都这样）

```cpp
#include <cstdio>
#include <map>
#include <cmath>
using namespace std;
long long a,b,p;
long long power(long long a, long long b, long long c) {//快速幂
    if(b==0)
        return 1%c;
    long long ans=1,t=a;
    while(b>0) {
       if(b%2==1) ans=ans*t%c;
       b/=2; t=t*t%c;
    }
    return ans;
}
long long bsgs(long long a,long long b,long long p) {//bsgs
	map<long long,long long> hash; hash.clear();//建立一个Hash表
	b%=p;
	long long t=sqrt(p)+1;
	for(register long long i=0;i<t;++i)
		hash[(long long)b*power(a,i,p)%p]=i;//将每个j对应的值插入Hash表
	a=power(a,t,p);
	if(!a) return b==0?1:-1;//特判
	for(register long long i=1;i<=t;++i) {//在Hash表中查找是否有i对应的j值
		long long val=power(a,i,p);
		int j=hash.find(val)==hash.end()?-1:hash[val];
		if(j>=0&&i*t-j>=0) return i*t-j;
	}
	return -1;//无解返回-1
}
signed main() {
	scanf("%lld%lld%lld",&p,&a,&b);
	long long ans=bsgs(a,b,p);
	if(ans==-1) printf("no solution\n");
	else printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：wwlw (赞：16)

用于求$A^{x} \equiv B \pmod{C}$ 高次方程的最小正整数解x，其中C为素数

------------------


引理1：$a^{i\mod\varphi(p) } \equiv a^{i}  $ (mod p)  p为素数，即$a^i$在模p的意义下会出现循环节(注:$\varphi(p)$不是最小循环节)

证明：
   因为$ a^{p-1} \equiv 1 $ (mod p) (费马小定理) ,则 $a^{k*(p-1)} \equiv 1$ (mod p)

   所以$ a^{2k * (p-1)} * a^{-k * (p-1)} \equiv 1 $ (mod p)

   所以$ a^{2k * (p-1)} $ 为 $a^{-k * (p-1)}$ mod p意义下的逆元
   
  $\frac{a^{i}}{a^{k * (p-1)}} \equiv a^{i} * a^{2k * (p-1)} \equiv a^{i} * 1 \equiv a^{i} $ (mod p)

   即$ a^{i-k*(p-1)} \equiv a^{i} $ (mod p) 

   又因为$ i \bmod \varphi(p) = i-k*(p-1) $

   且p为素数,$i-k*(p-1)=i-k * \varphi(p)$
    
   则$ a^{i-k*(p-1)} \equiv a^{i\mod\varphi(p)} \equiv a^{i} $ (mod p) 

   证毕!

----------------------------

根据引理1我们可知只需要枚举至多$\varphi(C)$个数就能知道方程的解，若枚举完后发现无解，则整个方程无解

考虑构造一个m，使得$m=ceil(\sqrt{C})$ (其中ceil()为向上取整函数)

$x=k*m-q$，原方程转化为$ A^{k * m-q} \equiv B \pmod{p}$

继续得到 $ A^{k * m} \equiv B*A^{q} \pmod{p}$

BSGS流程：到了这一步，我们先考虑枚举$B*A^{q}$中的q,至多$\sqrt{C}$次，然后我们把得到的值存入一个Hash表中

接着我们开始枚举 $ A^{k * m}$ 中的m，则两次枚举出来的式子的两两组合正好可以得到所有$range \in [1,x] $，若遇到两次枚举出来的值相等，则输出答案，退出循环。

(注:作者写这题的时候运势不好，Hash写挂了，换成了map，效果不影响)

Code:
```cpp
#include<stdio.h>
#include<math.h>
#include<map>
using namespace std;
#define ll long long
#define int ll
#define HASH_MOD 76799777LL

map<int,int> hash;

ll qpow(ll A,ll B,ll C){
	if(B==0) return 1;
	if(B==1) return A;
	ll t=qpow(A,B>>1,C);
	t=t*t%C;
	if(B&1) t=t*A%C;
	return t;
}
ll BSGS(ll A,ll B,ll C){
	const int sizes=ceil(sqrt(C));
	ll base=B%C;
	hash[base]=0;
	for(int i=1;i<=sizes;i++){
		base=base*A%C;
		hash[base]=i;
	}
	base=qpow(A,sizes,C);
	ll tmp=1;
	for(ll i=1;i<=sizes;i++){
		tmp=tmp*base%C;
		if(hash[tmp])
			return ((i*sizes-hash[tmp])%C+C)%C;
	}
	return -1;
}
ll P,B,N;
signed main(){
	scanf("%lld%lld%lld",&P,&B,&N);
	if(!(B%P)){
        printf("no solution\n");
        return 0;
    }
	ll ans=BSGS(B,N,P);
	if(ans!=-1) printf("%lld",ans);
	else printf("no solution");
}
```

---

## 作者：wmy_goes_to_thu (赞：6)

首先，我们回顾一下 Fermat-Oula 定理：$m\space|\space a^m-a$

把它乘 $a$ 的若干次方：$m\space|\space a^{m+k}-a^k$

通过 Fermat-Oula 定理，我们可以知道 $l \leq p$。所以，我们可以用余数的形式来分一下块，把 $l$ 变成 $i \times t-j$，其中 $1 \leq i \leq t,0 \leq j \lt t,t=\lceil \sqrt p \rceil$。
那么，我们需要解决的问题变成了：$p\space|\space (b^t)^i-n \times b^j$

简而言之，$b^i \times t$ 和 $n \times b^j$ 模 $p$ 同余，所以可以直接构造 $i$ 和 $j$。

那么，如何构造 $i$ 和 $j$ 呢？我们需要分两步：

第一步（Baby Step）：从 $0$ 到 $t-1$ 枚举 $j$，用一个 map 把 $j$ 映射到 $n \times b^j \bmod p$里，也就是在 $n \times b^j$ 的余数这个地址存 $j$。

第二步（Giant Step）：我们通过快速幂可以得到 $b^t \bmod p$ 的值，每次再枚举 $i$，然后在 map 里找 $b^i \times t$ 为地址中是否有值，若有，则用 $i \times t-j$ 更新答案。

这样，就可以求得最小解了！

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
int ans=2147483647;
map<int,int>mp;
void baby_step(int b,int n,int p)
{
  int cs=0,t=sqrt(p-0.5)+1;
  while(cs<t)
  {
    if(!mp[n])mp[n]=cs+1;
    n=1ll*n*b%p,cs++;
  }
}
int powdv(int b,int t,int p)
{
  int ans=1;
  while(t)
  {
    if(t&1)ans=(1ll*ans*b)%p;
    t>>=1;
    b=(1ll*b*b)%p;
  }
  return ans;
}
void giant_step(int b,int n,int p)
{
  int cs=1,t=sqrt(p-0.5)+1,b2;
  b=b2=powdv(b,t,p);
  while(cs<=t)
  {
    if(mp[b])
      ans=min(ans,t*cs-mp[b]+1);
    b=(1ll*b*b2)%p,cs++;
  }
}
int main()
{
  int p,b,n;
  cin>>p>>b>>n;
  baby_step(b,n,p);
  giant_step(b,n,p);
  if(ans<2147483647)cout<<ans<<endl;
  else cout<<"no solution\n";
  return 0;
}
```

最后推荐我的公众号：[这里](https://mp.weixin.qq.com/s/fTcCp72mrhiL3-kvmzxuIw)。

---

## 作者：Tyih (赞：4)

## Solution

对于这种题目，可以用大步小步算法（Baby Step,Giant Step，简称 BSGS）来解决这种题目。这个算法的核心跟它的名字相似，主要在于先小步小步的处理，然后大步大步的处理，跟分块相似。

我们可以设一个 $x$ 为小步跨的步数，$y$ 为大步跨的步数，以及它的的步长为 $B$。

则可以列出方程：
$$
g^{x+B \times y} \equiv a \pmod p
$$
可以将其转化为：
$$
g^{B \times y} \equiv a \times (g^x)^{-1} \pmod p
$$
我们可以用 Hashmap 储存 $a \times g^0 ,a\times (g^1)^{-1},a\times (g^2)^{-1},\dots,a\times (g^{B-1})^{-1}$。之后我们可以枚举 $y$，在 Hashmap 中查找是否有 $x$ 满足条件。

复杂度为 $\mathcal{O}(\frac{\varphi(p)}{B}+B\log p)=\mathcal{O}(\frac{p}{B}+B\log p)$。

我们可以先求出 $(g^1)^{-1}$，每次将 $(g^x)^{-1}$ 乘 $(g^1)^{-1}$，则可以在 $\mathcal{O}(\frac{p}{B}+B)$ 求出解。

当 $B=\sqrt p$，复杂度最小，为 $\mathcal{O}(\sqrt p)$。

# Code

```cpp
#include<bits/stdc++.h>
#define IOS cin.tie(0),cout.tie(0),ios::sync_with_stdio(0)
#define mod 998244353
#define ll long long
#define db double
#define pb push_back
#define MS(x,y) memset(x,y,sizeof x)
using namespace std;
const int N=1e5+5,M=1e5+5;
const ll INF=1ll<<60;
unordered_map<ll,ll> m;
void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b) x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll calc(ll a,ll p){//求解逆元
	ll x=0,y=0;
	exgcd(a,p,x,y);
	x=(x%p+p)%p;
	return x;
}
ll BSGS(ll g,ll a,ll p){
	a%=p;
	ll B=(ll)sqrt(p)+1;
	ll k=a,ng=calc(g,p),gB=g;//gB为g^B，方便求y
	m[k]=1;
	for(int i=1;i<B;i++){
		gB=gB*g%p;
		k=k*ng%p;
		if(!m[k]) m[k]=i+1;//这里需要判断一下，因为k%p可能有重复情况，取第一个出现的
	}
	ll temp=1;
	for(int i=0;i<=B;i++){
		if(m[temp]) return (i*B%p+m[temp]-1)%p;
		temp=temp*gB%p;
	}
	return -1;//无解
}
void solve(){
	ll p,b,n;
	cin>>p>>b>>n;
	ll ans=BSGS(b,n,p);
	if(ans==-1) cout<<"no solution\n";
	else cout<<ans<<"\n"; 
	return ;
}
int main(){
	IOS;int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

 $$
 \large{\mathbb{END}}
 $$

---

## 作者：ni_ju_ge (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P3846)。

BSGS，大步小步算法，用于求解 $a,p$ **互质** 的同余方程 $a^x\equiv b\pmod p$。
### 暴力解法
由扩展欧拉定理 $b^l\equiv b^{l\bmod\varphi(p)}\pmod p$ 可得 $b^l$ 模 $p$ 意义下的最小循环节为 $\varphi(p)$，由于 $\varphi(p)<p$，所以可以暴力枚举 $x=0\sim p$，时间复杂度 $O(p)$，不可通过。
### 正确解法
令 $l=im-j$，$m=\left\lceil\sqrt p\right\rceil,1\le i\le m,0\le j\le m$，这样任意的 $l\in [0,p]$ 均可被表示出来。

代入则有 $b^{im-j}\equiv n \pmod p$，也就是 $(b^m)^i\equiv nb^j\pmod p$。

那么可以：

1. 枚举 $j$，将 $key=nb^j\bmod p,val=j$ 放入哈希表（`map`），若 $key$ 重复则用大的 $j$ 替换小的。
2. 枚举 $i$，查找是否有 $key=(b^m)^i$，有则 $l=im-j$。

由于 $i,j\le \left\lceil\sqrt p\right\rceil$，所以枚举 $i,j$ 的时间复杂度为 $O(\sqrt p)$。正确性显然。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long b,n,p;
map<long long,long long> mp;
long long bsgs() {
	long long m=sqrt(p);
	if(m*m!=p) m++;
	mp[n]=0;
	for(long long i=1;i<=m;i++) {//枚举 j
		n=(n*b)%p;//存表
		mp[n]=i;
	}
	long long k=1;
	for(int i=1;i<=m;i++) k=(k*b)%p;//先求 b^m
	long long i,j,t=1;
	for(i=1;i<=m;i++) {//枚举 i
		t=(t*k)%p;
		if(mp.count(t)) return i*m-mp[t];//寻找解
	}
	return -1;//找不到，报告无解
}
int main() {
	cin>>p>>b>>n;
	if(b%p==0) cout<<"no solution";//注意 b 是 p 倍数时 b^l 模 p 意义下一定为 0
	else {
		int ans=bsgs();//求答案
		if(ans==-1) cout<<"no solution";
		else cout<<ans;
	}
} 
```

---

## 作者：fish_love_cat (赞：3)

**算法介绍：**

BSGS 可以用于求 $x^k\equiv n \pmod p$ 的最小解 $k$。

**大致思路：**

直接对着原式不太好做，考虑将式子改写成下面的形式：

$$x^{a\times d+c}\equiv n \pmod p$$

$d$ 就是一大步所跨越的长度，$a$ 是大步跨的次数，$c$ 是小步跨的次数。

其中 $d$ 是一个常数，且 $c<d$，并且还有 $a\le\frac{k}{d}$。

我们将式子拆开：

$$x^{a\times d}\times x^c\equiv n \pmod p$$

移项：

$$x^{a\times d}\equiv \frac{n}{x^c} \pmod p$$

容易发现这个式子等价于：

$$x^{a\times d}\equiv n\times (x^c)^{-1} \pmod p$$

于是现在只需要知道右式的所有情况下的值，再枚举左式的值就能得到答案了。

**算法实现：**

考虑枚举每一个 $n\times (x^c)^{-1}$ 存到 `map` 里，然后再枚举每一个 $x^{a\times d}$ 判断是否可行，这样就能找到最小的 $k$ 了。

**复杂度：**

对于素数 $p$，满足当 $a\in [1,p-1],x\in[0,p-2]$ 时，$a^x \pmod p$ 与 $[1,p-1]$ 构成双射。

所以若有解必有 $k<p$。于是还可以得到 $a < \frac{p}{d}$。

我们枚举的是 $a,c$ 的取值，所以时间复杂度即为 $O(d+\frac{p}{d})$，取 $d=\sqrt p$ 时 $O(\sqrt p)$ 达到最优。

**代码：**

```cpp
int qpow(int a,int b,int p=flc_INF){
	int ans=1;
	if(b==0)return 1;
	while(b){
		if(b&1)ans*=a,ans%=p;
		a*=a,b>>=1,a%=p;
	}
	return ans;
}
int ni(int a,int p){return qpow(a,p-2,p);}
int BSGS(int x,int n,int p){
    if(n==1)return 0;
    if(x%p==n%p)return 1;
    if(x%p==0)return -1;
    n%=p,x%=p;
    int inx=ni(x,p);
    int B=sqrt(p)+1;
    int Bb=qpow(x,B,p);
    unordered_map<int,int>mp;
    for(int i=0,flc=n;i<B;i++,flc=flc*inx%p)
        if(!mp[flc])mp[flc]=i+1;
    for(int i=0,flc=1;i<=B;i++,flc=flc*Bb%p)
        if(mp[flc])return (i*B+mp[flc]-1)%p;
    return -1;
}
```

---

Upd：题解第五次重写。

---

## 作者：chenbs (赞：3)

## 算法介绍

BSGS 算法用于求解离散对数问题，即：对于已知的三个数 $b$，$n$，$p$，找出最小的 $l$，使得 $b^l \equiv n \pmod p$。

首先由费马小定理，$b^l \bmod p = b^{l \bmod (p-1)} \bmod p$。所以，若满足条件的 $l$ 存在，则 $l_{\min} < p$。

定义 $s = \lceil \sqrt{p} \rceil$，上取整是为了保证 $s^2 \ge p$，防止漏解。

设 $l=xs-y (x,y < s)$，则：

$$b^{xs-y} \equiv n \pmod p$$

$$b^{xs} \equiv n b^y\pmod p$$

先从小到大枚举 $y$，用哈希表记录 $nb^y \bmod p$ 对应的**最大**的 $y$ 值（因为 $y$ 越大，$l$ 就越小），再从小到大枚举 $x$，在哈希表中查找 $b^{xs} \bmod p$，如果找到了，就说明 $xs-y$ 是我们要的求的最小的 $l$。

## 正确性证明

设我们已经找到了一组 $(x,y)$，可知 $b^{xs} \equiv n b^y\pmod p$，由于 $b$ 和 $p$ 互质，所以 $b^y$ 在模 $p$ 意义下**必有逆元**，所以 $b^{xs-y} \equiv n \pmod p$，即 $b^l \equiv n \pmod p$，证毕。

这也是普通 BSGS 要求 $b$ 和 $p$ 必须互质的原因。

枚举 $x$ 和枚举 $y$ 都是 $O(\sqrt p)$ 的，哈希表单次插入查询为 $O(1)$，所以总时间复杂度 $O(\sqrt p)$。

## 代码实现

这应该是非常短的一种实现了。有些人可能会写一个快速幂的函数，但是实际上没有必要，暴力计算 $b^s$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<ll, ll> mp;
ll p,b,n,s;
int main() {
	cin>>p>>b>>n, s=sqrt(p)+1;
	for(ll y=1, pw=n*b%p; y<=s; y++, pw=pw*b%p) mp[pw%p]=y;
	
	ll t=1;
	for(ll i=1; i<=s; i++) t=t*b%p;
	for(ll x=1, pw=t; x<=s; x++, pw=pw*t%p)
		if(mp[pw])
			return cout<<x*s-mp[pw], 0;
    
	cout<<"no solution";
	return 0;
}
```

---

## 作者：TJB_LHY (赞：2)

# 思路

模板题就不过多赘述题意了，一道BSGS 算法（又称大步小步算法）的题。首先，我们考虑暴力求解，因为 $p$ 为质数，根据费马小定理可知 $a^{p-1}\equiv1 \pmod p$，所以当 $x> p-1$ 时重复 $a^x\pmod p$ 的计算是无意义的，复杂度即是 $O(p)$，不可以通过此题。接下来，我们需要一种神秘的算法 [BSGS](https://www.luogu.com.cn/problem/P3846)：我们现将 $x$ 拆为 $a\times b-c$，变形同余式得 $y^{a\times b-c} \equiv z \pmod p$。

同余式两边同时乘以 $y^c$ 得：$y^{a\times b} \equiv z\times y^{c} \pmod p$; 推出式子后，我们设 $a=\sqrt p$（此时枚举复杂度最少），然后使用映射标记所有 $z\times y^c$（由上面的推理可知：当 $c> p-1$ 时重复 $y^c\pmod p$ 的计算是无意义的，所以只需映射 $0\le c<p$ 的即可）。

最后枚举 $b$ 查找 $y^{a\times b} \pmod p$ 是否存在映射值就完成啦（同上）～由于两次枚举的上限都是 $\sqrt p$，所以该任务时间复杂度为 $O(\sqrt p)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define U unsigned
using namespace std;
ll y,z,p,k,ans;
ll sqr(ll a,ll b){//快速幂
    ll num=1;
    a%=p;
    while(b){
        if(b&1)num=num*a%p;
        a=a*a%p;
        b>>=1;
    }
    return num;
}
map<ll,ll>vis;//映射
ll BSGS(){
    vis.clear();
    ll a,b=ceil(sqrt(p)),c,k=z%p,num=1;
    for(c=0;c<b;c++,k=y*k%p)vis[k]=c;//映射标记
    for(a=1;a<=b;a++){
        num=sqr(y,a*b);//查找
        if(vis.count(num)){
            return a*b-vis[num];//返回
        }
    }
    return -1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
    cin>>p>>y>>z;
    if(z%p==1)cout<<"0\n";//特判
    else {
        ans=BSGS();
        if(ans!=-1)cout<<ans<<'\n';
        else cout<<"no solution\n";
    }
	return 0;
}
```

完结撒花～

---

## 作者：LionBlaze (赞：1)

**BSGS**（Baby-Step Giant-Step）算法是 Shank 发明的一个用于在 $\mathcal O(\sqrt p)$ 时间复杂度内计算**离散对数**的算法，要求模数为质数。扩展 BSGS 不需要模数为质数。

何为离散对数？普通的对数 $\log_ab=c$ 相当于求一个 $c$ 满足 $a^c=b$。而离散对数就是如题目所说，给定 $p,b,n$，求 $b^l\equiv n\pmod p$。

首先显然如果 $l$ 存在则必然存在 $l<p$，因为 $b^{p-1}\equiv 1\pmod p$，如果你还不知道费马小定理请离开，你现在不应该看这篇文章。

考虑一个显然的暴力做法：依次检查。虽然是暴力，但是我们不至于傻到每求一个 $b^l$ 都跑一次快速幂[^1]，显然是可以递推的。

BSGS 则利用了幂运算的性质 $a^b\times a^c=a^{b+c}$（在模意义下显然也成立），使用类似分块的做法，做到了根号级别的时间复杂度。

首先我们暴力求出当 $l\le \sqrt{p}$ 时的所有余数，如果有 $n$ 则可以直接返回答案。否则，我们可以相应地求出 $\sqrt{p}<l\le 2\sqrt{p}$ 时的答案，然后判断。以此类推。

看上去并没有什么作用，但是实际上，如果 $b^{l+\sqrt{p}}\equiv n\pmod p$，那么 $b^{l}\equiv n\times(b^{\sqrt{p}})^{-1}\pmod p$。同时 $b^{-\sqrt p}$ 也是一个常数可以预处理，我们就可以利用我们求的所有当 $l\le \sqrt p$ 时的余数快速判断了（把 $l\le \sqrt p$ 的所有余数存到一个 `set` 或者哈希表 `unordered_set` 或者其它奇奇怪怪的数据结构中）。

进一步地，如果 $b^{l+k\sqrt p}\equiv n\pmod p$，则 $b^l\equiv n\times (b^{-\sqrt p})^k\pmod p$。所以我们就得到了总时间复杂度为 $\mathcal O(\sqrt n)$ 的计算离散对数的做法。

我们上面都假设 $\sqrt p$ 是整数，实际上不可能是，但是我们取 $\sqrt p$ 在正确性上并没有什么实际意义，只是为了保证时间复杂度，所以取 $\lfloor \sqrt p \rfloor$ 和 $\lceil \sqrt p \rceil$ 也行。

注意本题不仅仅要判断存在性，还要输出解。所以我们不能只保存余数，还要保存下标。

附上丑陋的代码。

```cpp
#include <cstdio>
#include <unordered_map>

using namespace std;

unordered_map<int, int> um;

long long qpow(int x, int y, int p)
{
    if(y == 0) return 1;
    if(y == 1) return x;
    long long r = qpow(x, y >> 1, p);
    r = r * r % p;
    if(y & 1) r = r * x % p;
    return r;
}

int main()
{
    int p, b, n;
    scanf("%d%d%d", &p, &b, &n);
    int sqrtp = 0;
    long long mul = 1;
    // 0 ~ sqrtp
    for(int i=0;1ll*i*i<=p;i++)
    {
        sqrtp = i;
        if(!um.count(mul = (i == 0 ? 1 : mul * b % p))) um[mul] = i;
        if(mul == n)
        {
            printf("%d\n", i);
            return 0;
        }
    }
    sqrtp++; mul = mul * b % p;
    long long invmul = qpow(mul, p - 2, p), mulll = 1;
    // i*sqrtp ~ (i+1)*sqrtp-1
    for(int i=1;1ll*sqrtp*i<=p;i++)
    {
        if(um.count((mulll = mulll * invmul % p) * n % p))
        {
            printf("%d\n", um[mulll * n % p] + sqrtp * i);
            return 0;
        }
    }
    printf("no solution\n");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/221950438)。

[^1]: 倒是有一种底数确定的 $\mathcal O(\sqrt n)$ 预处理，$\Theta(1)$ 查询的光速幂算法。核心思想和 BSGS 十分相似——预处理出 $1\le i\le \sqrt p$ 的 $a^i$ 和 $a^{i\times \lfloor \sqrt p\rfloor}$，然后用这两个凑出答案。用这个的话也不会劣化我们的暴力时间复杂度，毕竟是常数时间查询的。

---

## 作者：Chase12345 (赞：1)

~~看标题~~不难发现这是一个 BSGS 的模板题。

# 引言
本来不想学 BSGS 的，但是一位可爱的老师（摸鱼酱）出了一个有趣的 BSGS 的题，看到 std 发现十分简单，所以才来学的。本就数学菜的我发现自己更菜了（

# 简介
Baby Step Giant Step，俗称 BSGS，也称大步小步算法。它的算法内容和名称是完全相关的。它可以解决的问题挺多的。

# 具体算法内容
在 BSGS 里面，假设步长为 $a$，则小步走 $x$ 步，大步走了 $y$ 步，这里我们通常称小步为一个单位长度，大步是 $a$ 个单位长度。则显然地，这样是走了 $x+ay$ 单位长度。

在这道题中，我们的走路的步其实就是幂的叠加。举个例子，仍然是上面的数，我们同样可以列出同余方程：
$$
b^{x+ay} \equiv n \pmod{p}
$$
不难发现，移项之后有：
$$
b^{ay} \equiv n \times \left(b^x\right)^{-1} \pmod{p}
$$
后面这里 $\left(b^x\right)^{-1}$ 表示 $b^x$ 在模 $p$ 意义下的逆元。

嘿，这里不就可以通过哈希存储了吗？先预处理右边的这些值，每次左边对比是否存在。注意这里我们肯定不希望小步和大步一样长，所以通常而言，$x<a$。

# 复杂度分析
这里我们不难发现，$b^l$ 模 $p$ 的余数都在 $[0,p-1]$ 中，并且不难证明具有周期。那么我们就可以取 $l<p$。既然如此，我们的大步也最多为 $\frac{p}{a}$，小步显然地，最多 $a$。

则不难得到总的复杂度 $O(\frac{p}{a} +a)$。考虑均值不等式。不难发现 $\frac{p}{a}+a \le 2\sqrt p$，当且仅当 $\frac{p}{a}=a$ 即 $a=\sqrt p$ 时等号成立。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
 
i64 fpow(i64 a, i64 b, i64 p) {
    i64 res = 1;
    for (; b; a = a * a % p, b >>= 1)
    	if (b & 1)
    		res = res * a % p;
    return res;
}
 
i64 BSGS(i64 p, i64 b, i64 n) {
    if (b % p == 0) {
        if (n == 0)
			return 1;
        else
			return -1;
    }
    unordered_map <i64, i64> hash;
    i64 m = ceil(sqrt(p)), t = n % p;
    for (i64 j = 0; j < m; j++) {
        hash[t] = j;
        t = t * b % p;
    }
    i64 b_m = fpow(b, m, p);
    t = b_m;
    for (i64 i = 1; i <= m; i++) {
        if (hash.count(t))
            return i * m - hash[t];
        t = t * b_m % p;
    }
    return -1;
}
 
int main() {
    i64 p, b, n;
    cin >> p >> b >> n;
    i64 ans = BSGS(p, b, n);
    if (ans == -1)
		cout << "no solution\n";
    else
		cout << ans << '\n';
    return 0;
}
```

---

