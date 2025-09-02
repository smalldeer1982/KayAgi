# RNG - Random Number Generator

## 题目描述

LoadingTime got a RNG (_Random Number Generator_) from his classmate several weeks ago. And he spent a lot of time study it. He found that RNG can generate a real number in range \[-**S**,**S**\] by executing following steps. First RNG generates n integer **X** $ _{1} $ ..**X** $ _{n} $ , the sum of which is equal to **S**. Then for each **X** $ _{i} $ , it generates a real number in range \[-**X** $ _{i} $ ,**X** $ _{i} $ \] randomly. The output (a real number) of RNG will be the sum of the **N** generated real numbers. LoadingTime noticed that the distribution of the output was very interesting, and he wanted to know: for given **N** and **X**, what's the probability that the generated number is in range \[**A**,**B**\]. Could you help him?

## 样例 #1

### 输入

```
5
1 -100 100
10
1 10 90
10
1 -20 5
10
2 -20 5
5 5
5 -5 10
1 2 3 4 5```

### 输出

```
1.000000000
0.000000000
0.750000000
0.875000000
0.864720052```

# 题解

## 作者：bsdsdb (赞：3)

题意；给定 $\{a_i\}_{i=1}^n,A,B\in\R$，$x_i\in\R$ 随机生成于 $[-a_i,a_i]$，求 $\sum_{i=1}^nx_i\in[A,B]$ 的概率。$n\le20$。

先将这个题目做两步转化：

1. 改成求 $\sum_{i=1}^nx_i<C$ 的概率，那么原题的答案就是 $C=B$ 时该问题的答案减去 $C=A$ 时的；
2. 注意到 $x_i+a_i$ 是一个随机生成于 $[0,2a_i]$ 的数，我们可以求 $x_i$ 随机生成于 $[0,2a_i]$ 时他们的和小于 $C+\sum a$ 的概率，和原问题是一样的。

结合一下，我们令 $b_i\coloneqq 2a_i,C\gets C+\sum a$，问题变成 $x_i$ 随机生成于 $[0,b_i]$ 时 $\sum_{i=1}^nx_i<C$ 的概率。转化成拓扑意义，我们要求的是两个点集

$$
R\coloneqq\left\{\bm x\left\lvert x_i\in[0,b_i],\sum_{i=1}^nx_i<C\right.\right\}\\
S\coloneqq\{\bm x\mid x_i\in[0,b_i]\}
$$

的体积之比 $\frac{\mathrm{vol}\,R}{\mathrm{vol}\,S}$。

为了方便，下面只考虑 $\{\bm x\mid x_i\ge 0\}$ 内的点。

$\mathrm{vol}\,S$ 是简单的，他就等于 $\prod_{i=1}^n b_i$。

对于 $R$，考虑一个更简单的版本：

$$
R'(n,C)\coloneqq\left\{\bm x\left\lvert\sum_{i=1}^nx_i<C\right.\right\}\\
$$

这玩意在拓朴学上叫[单纯形](https://zh.wikipedia.org/wiki/%E5%8D%95%E7%BA%AF%E5%BD%A2)，他的体积是 $[C>0]\frac{C^n}{n!}$。

> 证：
>
> 考虑归纳。设它的体积是 $f(n,C)$，那么 $f(1,C)=[C>0]C$。对于 $n>1$ 的情形，可以考虑对于每个 $u\in[0,C)$ 观察 $x_n=u$ 的那一层在 $\R^{n-1}$ 中的样子：
>
> $$
> \begin{aligned}
> R'(n,C)_u=&\left\{\bm x\left\lvert\sum_{i=1}^nx_i<C,x_n=u\right.\right\}\text{ in }\R^n\\
> =&\left\{\bm x\left\lvert\sum_{i=1}^{n-1}x_i<C-u,x_n=u\right.\right\}\text{ in }\R^n\\
> =&\left\{\bm x\left\lvert\sum_{i=1}^{n-1}x_i<C-u\right.\right\}\text{ in }\R^{n-1}\\
> =&R'(n-1,C-u)\\
> f(n,C)=&[C>0]\int_0^Cf(n-1,C-u)\,\mathrm du\\
> =&[C>0]\int_0^Cf(n-1,u)\,\mathrm du\\
> =&[C>0]\int_0^C\frac{u^{n-1}}{(n-1)!}\,\mathrm du\\
> =&[C>0]\frac{C^n}{n(n-1)!}\\
> =&[C>0]\frac{C^n}{n!}
> \end{aligned}
> $$

接下来，我们需要剔除掉那些满足「存在 $i$ 使得 $x_i>b_i$」的点 $\bm x$ 对体积的贡献。设 $n$ 个点集 $\{E_i\}_{i=1}^n$，其中 $E_i$ 表示 $R'(n,C)$ 中 $x_i>b_i$ 的那些点，即：

$$
E_i\coloneqq\left\{\bm x\left\lvert x_i>b_i,\sum_{j=1}^nx_j<C\right.\right\}\\
$$

要剔除掉的，就是 $\bigcup_{i=1}^nE_i$ 中的点。这个并的大小是不好求的，但是交的大小是好求的（此处 $S\neq\varnothing$，否则第二行会出错）：

$$
\gdef\vol#1{\mathrm{vol}\left(#1\right)}
\begin{aligned}
&\vol{\bigcap_{i\in S}E_i}\\
=&\vol{\left\{\bm x\left\lvert\sum_{i=1}^nx_i<C,\forall i\in S:x_i>b_i\right.\right\}}\\
=&\vol{\left\{\bm{x'}\left\lvert\sum_{i=1}^n{x'}_i<C-\sum_{i\in S}b_i\right.\right\}},\quad\text{with }{x'}_i\coloneqq x_i-[i\in S]b_i\\
=&\vol{\left\{\bm{x'}\left\lvert\sum_{i=1}^n{x'}_i<C-b_S\right.\right\}},\quad\text{with }b_S\coloneqq\sum_{i\in S}b_i\\
=&\vol{R'(n,C-b_S)}\\
=&f(n,C-b_S)
\end{aligned}
$$

然后，容斥原理又告诉我们：

$$
\gdef\card#1{\mathrm{card}\left(#1\right)}
\card{\bigcup_{i\in S}E_i}=\sum_{\substack{T\subseteq S\\T\neq\varnothing}}(-1)^{|T|+1}\card{\bigcap_{i\in T}E_i}
$$

其中，映射 $\mathrm{card}$ 需要且仅需要满足 $\card{A\cup B}=\card A+\card B-\card{A\cap B}$ 和 $\card\varnothing=0$。因此，$\mathrm{vol}$ 是一个合法的 $\mathrm{card}$。那么，要剔除掉的体积就是：

$$
\gdef\vol#1{\mathrm{vol}\left(#1\right)}
\begin{aligned}
&\vol{\bigcup_{i=1}^nE_i}\\
=&\sum_{\substack{T\subseteq([1,n]\cap\N)\\T\neq\varnothing}}(-1)^{|T|+1}\vol{\bigcap_{i\in T}E_i}\\
=&\sum_{\substack{T\subseteq[n]\\T\neq\varnothing}}(-1)^{|T|+1}f(n,C-b_T),\quad\text{with }[n]\coloneqq[1,n]\cap\N\\
\end{aligned}
$$

最后，$R$ 的体积就是：

$$
\begin{aligned}
\vol R=&\vol{R'(n,C)\setminus\bigcup_{i=1}^nE_i}\\
=&\vol{R'(n,C)}-\vol{\bigcup_{i=1}^nE_i}\\
=&f(n,C)-\sum_{\substack{T\subseteq[n]\\T\neq\varnothing}}(-1)^{|T|+1}f(n,C-b_T)\\
=&f(n,C-b_\varnothing)+\sum_{\substack{T\subseteq[n]\\T\neq\varnothing}}(-1)^{|T|}f(n,C-b_T)\\
=&\sum_{T\subseteq[n]}(-1)^{|T|}f(n,C-b_T)\\
\end{aligned}
$$

---

## 作者：苹果蓝17 (赞：1)


对于定义在 $\mathbb{R}$ 上的函数 $f(x),g(x)$，定义连续卷积为定义在 $\mathbb{R}$ 上的函数 $h(x)$，对所有 $x \in \mathbb{R}$ 满足：

$$h(x)=\int_{-\infty}^{\infty} f(t) g(x-t) dt$$

若 $f(x),g(x)$ 均为分段函数且每一段为低次多项式，可以考虑这样求解：

枚举 $f(x)$ 中的每一段 $\forall x \in [l,r],f(x)=F(x)$，$g(x)$ 中的每一段 $\forall x \in [L,R],g(x)=G(x)$，其中 $F(x),G(x)$ 分别为 $d1,d2$ 次多项式。

下面假设 $r+L \leq l+R$，否则交换 $F(x),G(x)$。

计算二元多项式 $s(t,x)=f(t)g(x-t)$，关于 $t$ 求 $s(t,x)$ 的不定积分 $S(t,x)=\int s(t,x) dt+C$。

对于某个 $x$，$t$ 需要满足 $l \leq t \leq r \wedge L \leq x-t \leq R$。对 $t$ 的取值区间进行分类讨论：

+ 当 $x \in [l+L,r+L]$ 时，$t \in [l,x-L]$，故 $h(x)=S(x-L,x)-S(l,x)$。
+ 当 $x \in [r+L,l+R]$ 时，$t \in [l,r]$，故 $h(x)=S(r,x)-S(l,x)$。
+ 当 $x \in [l+R,r+R]$ 时，$t \in [x-R,r]$，故 $h(x)=S(r,x)-S(x-R,x)$。

以上所有操作均可以在 $O((d1+d2)^3)$ 时间内完成，同时注意到若设 $f(x)$ 共 $n$ 段，$g(x)$ 共 $m$ 段，则分段端点至多只有 $(n-1)(m-1)$ 个。故可以利用差分与前缀和在 $O(nm(d1+d2)^3)$ 内计算 $h(x)$。

注意到 $h(x)$ 内每一段的次数不高于 $d1+d2+1$，故若计算 $n$ 个函数 $f_1(x),f_2(x),\cdots,f_n(x)$ 的连续卷积，设其次数分别为 $d_1,d_2,\cdots,d_n$，段数分别为 $k_1,k_2,\cdots,k_n$，则可以在 $O(\prod (k_i+1) (\sum d_i+n)^3)$ 内计算其连续卷积。

回到原问题，直接计算 $n$ 个 $0$ 次多项式的连续卷积 $h(x)$（即答案的概率密度函数），再对 $h(x)$ 每一段 $[A,B]$ 内的部分进行积分求和即可。

总时间复杂度 $O(n^3 2^n)$。

#### Code

```cpp
const int N=1e5+5,M=22;

long double C[M][M];
void init(long long lim){
	for(int i=0;i<=lim;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
}
long double ID(long long x){
    return (x & 1ll)?(-1):(1);
}

struct poly{
	vector <long double> V;
	int l,r;
};
struct abc{
	vector <poly> P;
	int deg;
};

int v[N],vid;

long double F[M][M],G[M][M],P[M];
vector <long double> S[N];
void merge(poly X,poly Y,int d1,int d2){
	if(X.r+Y.l>X.l+Y.r) swap(X,Y),swap(d1,d2);
	for(int i=0;i<=d1+d2;i++)
		for(int j=0;j<=d2;j++)
			F[i][j]=0;
	for(int i=0;i<=d1;i++){
		if(!X.V[i]) continue;
		for(int j=0;j<=d2;j++){
			if(!Y.V[j]) continue;
			for(int k=0;k<=j;k++){
				F[i+k][j-k]+=ID(k)*C[j][k]*X.V[i]*Y.V[j];
			}
		}
	}
	
	for(int j=0;j<=d2;j++) G[0][j]=0;
	for(int i=1;i<=d1+d2+1;i++)
		for(int j=0;j<=d2;j++)
			G[i][j]=F[i-1][j]/i;
	
	int pos1=lower_bound(v+1,v+vid+1,X.l+Y.l)-v,
	pos2=lower_bound(v+1,v+vid+1,X.l+Y.r)-v,
	pos3=lower_bound(v+1,v+vid+1,X.r+Y.l)-v,
	pos4=lower_bound(v+1,v+vid+1,X.r+Y.r)-v;
	
	for(int i=0;i<=d1+d2+1;i++) P[i]=0;
	for(int i=0;i<=d1+d2+1;i++){
 		for(int j=0;j<=d2;j++){
			if(!G[i][j]) continue;
			for(int k=0;k<=i;k++){
				P[k+j]+=ID(k-i)*C[i][k]*pow(Y.l,i-k)*G[i][j];
			}
			P[j]-=pow(X.l,i)*G[i][j];
		}
	}
	for(int i=0;i<=d1+d2+1;i++)
		S[pos1][i]+=P[i],
		S[pos3][i]-=P[i];
	
	if(pos3<=pos2){
		for(int i=0;i<=d1+d2+1;i++) P[i]=0;
		for(int i=0;i<=d1+d2+1;i++){
			for(int j=0;j<=d2;j++){
				if(!G[i][j]) continue;
				P[j]+=pow(X.r,i)*G[i][j];
				P[j]-=pow(X.l,i)*G[i][j];
			}
		}
		for(int i=0;i<=d1+d2+1;i++)
			S[pos3][i]+=P[i],
			S[pos2][i]-=P[i];
	}
	
	for(int i=0;i<=d1+d2+1;i++) P[i]=0;
	for(int i=0;i<=d1+d2+1;i++){
		for(int j=0;j<=d2;j++){
			if(!G[i][j]) continue;
			P[j]+=pow(X.r,i)*G[i][j];
			for(int k=0;k<=i;k++){
				P[k+j]-=ID(k-i)*C[i][k]*pow(Y.r,i-k)*G[i][j];
			}
		}
	}
	for(int i=0;i<=d1+d2+1;i++)
		S[pos2][i]+=P[i],
		S[pos4][i]-=P[i];
}

abc solve(abc X,abc Y){
	vid=0;
	int siz1=X.P.size(),siz2=Y.P.size();
	for(int i=0;i<siz1;i++)
		for(int j=0;j<siz2;j++)
			v[++vid]=X.P[i].l+Y.P[j].l,
			v[++vid]=X.P[i].l+Y.P[j].r,
			v[++vid]=X.P[i].r+Y.P[j].l,
			v[++vid]=X.P[i].r+Y.P[j].r;
	
	sort(v+1,v+vid+1);
	vid=unique(v+1,v+vid+1)-v-1;
	
	int d1=X.deg,d2=Y.deg,d=d1+d2+1;
	for(int i=1;i<=vid;i++){
		S[i].resize(d+1);
		for(int t=0;t<=d;t++) S[i][t]=0;
	}
	for(int i=0;i<siz1;i++)
		for(int j=0;j<siz2;j++){
			merge(X.P[i],Y.P[j],d1,d2);
		}
	for(int i=2;i<=vid;i++){
		for(int t=0;t<=d;t++) S[i][t]+=S[i-1][t];
	}
	
	abc T; T.deg=d;
	for(int i=1;i<vid;i++){
		T.P.push_back({S[i],v[i],v[i+1]});
	}
	return T;
}

///////////////////////////

int T,n,L_,R_;
long double ans,alc;
abc A[N];

int main(){
	init(M-2);
	cin>>T;
	while(T--){
		ans=0,alc=1;
		cin>>n>>L_>>R_;
		for(int i=1;i<=n;i++){
			A[i].deg=0; A[i].P.clear();
			
			poly x;
			int w; cin>>w;
			x.l=-w,x.r=w;
			x.V.resize(A[i].deg+1);
			x.V[0]=1;
			alc=alc*(x.r-x.l);
			
			A[i].P.push_back(x);
		}
		abc T=A[1];
		for(int i=2;i<=n;i++) T=solve(T,A[i]);
		
		for(poly x: T.P){
			int L=max(x.l,L_),R=min(x.r,R_);
			if(L<=R){
				for(int t=0;t<=T.deg;t++){
					ans+=(pow(R,t+1)-pow(L,t+1))*x.V[t]/(t+1);
				}
			}
		}
		cout<<setprecision(9)<<fixed<<ans/alc<<'\n';
	}
}
```

---

## 作者：foreverlasting (赞：1)

[推销博客](https://foreverlasting1202.github.io/)

容斥+微积分。
<!--more-->

这其实是一道结论题啦。

首先，求$s$在$[a,b]$就是一个幌子，这显然是独立的，只用考虑一边就可以了。如果生成的不是浮点数，那就是一个简单的$O(2^n)$的容斥了。那如果是浮点数，我们就不知道贡献了。于是要知道一个简单的结论：设$f(x)$为$0≤a_1,a_2,a_3,⋯,a_n≤x$时$\sum a_i≤x$的概率$\ast x^n$，那么$f(x)=\frac {x^n}{n!}$。这个怎么证明呢，可以考虑把这个东西放到$n$维空间里去，那么$f(x)$表示的就会是$(0,...,0)(x,0,...,0)(0,x,0,...,0)...(0,0,...,x)$这么些点所表示的体积。这个体积大家可以想象一下，或者简单的数学证明一下（积分一下就可以了，用角度去积），就会得到上面的结论。

于是又变成了简单的容斥。

$HDU$的那道题也差不多，就是它变成求期望了。期望好像是无限多个上述的东西乘上权值加起来，这怎么办呢？简单的积分一下就可以了，求出来会发现$f(x)$的期望就是$\frac {x^n}{n!\ast \prod (r_i-l_i)}$。于是还是简单的容斥一下。

SP的code:
```cpp
//2019.3.16 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
#define RG register
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y) {
    x^=y^=x^=y;
}
inline int _abs(const res &x) {
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y) {
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
#define lb long double
namespace MAIN{
    int n;
    int x[10+10],a,b;
    lb tot;
    lb dfs(const res &dep,const res &sum,const res &fl){
        if(sum<=0)return 0;
        if(dep==n){
            RG lb ret=1;
            for(res i=1;i<=n;i++)ret*=(lb)sum/i;
            return ret*fl;
        }
        return dfs(dep+1,sum,fl)+dfs(dep+1,sum-x[dep+1],-fl);
    }
    inline void MAIN(){
        res T=read();
        while(T--){
            n=read(),a=read(),b=read(),tot=1;
            for(res i=1;i<=n;i++)x[i]=read(),a+=x[i],b+=x[i],x[i]<<=1,tot*=x[i];
            printf("%.9Lf\n",(dfs(0,b,1)-dfs(0,a,1))/tot);
        }
    }
}
int main() {
    MAIN::MAIN();
    return 0;
}
```

HDU的code:
```cpp
//2019.3.16 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
#define RG register
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y) {
    x^=y^=x^=y;
}
inline int _abs(const res &x) {
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y) {
    return x>y?x:y;
}
inline int _min(const res &x,const res &y) {
    return x<y?x:y;
}
const int kcz=998244353;
namespace MAIN{
    int n;
    int x[15+10];
    inline int mul(const res &x,const res &y){
        return x>kcz/y?int(1LL*x*y%kcz):x*y;
    }
    inline int Add(const res &x,const res &y){
        return x+y>=kcz?x+y-kcz:(x+y<0?x+y+kcz:x+y);
    }
    inline void add(res &x,const res &y){
        x+=y,x>=kcz?x-=kcz:(x<0?x+=kcz:1);
    }
    inline int qpow(res x,res y){
        res ret=1;
        while(y){
            if(y&1)ret=mul(ret,x);
            x=mul(x,x),y>>=1;
        }
        return ret;
    }
    int inv[15+10];
    inline void pre(){
        res fac=1;
        for(res i=2;i<=n+1;i++)fac=mul(fac,i);
        inv[n+1]=qpow(fac,kcz-2);
        for(res i=n;i;i--)inv[i]=mul(inv[i+1],i);
    }
    int tot=1,a,b;
    int dfs(const res &dep,const res &sum,const res &dsum,const res &fl){
        if(sum<=0)return 0;
        if(dep==n)return mul(mul(qpow(sum,n+1),inv[n+1]),fl);
        return Add(dfs(dep+1,sum,dsum,fl),dfs(dep+1,sum-x[dep+1],dsum+x[dep+1],-fl));
    }
    inline void MAIN(){
        n=read(),pre();
        for(res i=1;i<=n;i++){
            res l=read(),r=read();
            x[i]=r-l;
            if(x[i])tot=mul(tot,x[i]);
            a+=l,b+=r;
        }
        if(1LL*a*b>=0){printf("%d\n",mul(_abs(Add(a,b)),qpow(2,kcz-2)));return;}
        printf("%d\n",mul(Add(dfs(0,b,0,1),dfs(0,-a,0,1)),qpow(tot,kcz-2)));
    }
}
int main() {
    MAIN::MAIN();
    return 0;
}
```

---

