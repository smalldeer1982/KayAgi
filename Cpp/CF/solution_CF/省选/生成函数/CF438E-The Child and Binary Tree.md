# The Child and Binary Tree

## 题目描述

Our child likes computer science very much, especially he likes binary trees.

Consider the sequence of $ n $ distinct positive integers: $ c_{1},c_{2},...,c_{n} $ . The child calls a vertex-weighted rooted binary tree good if and only if for every vertex $ v $ , the weight of $ v $ is in the set $ {c_{1},c_{2},...,c_{n}} $ . Also our child thinks that the weight of a vertex-weighted tree is the sum of all vertices' weights.

Given an integer $ m $ , can you for all $ s $ $ (1<=s<=m) $ calculate the number of good vertex-weighted rooted binary trees with weight $ s $ ? Please, check the samples for better understanding what trees are considered different.

We only want to know the answer modulo $ 998244353 $ ( $ 7×17×2^{23}+1 $ , a prime number).

## 说明/提示

In the first example, there are $ 9 $ good vertex-weighted rooted binary trees whose weight exactly equal to $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF438E/eac2c310aa15e844747811a6717476e6a022e10e.png)

## 样例 #1

### 输入

```
2 3
1 2
```

### 输出

```
1
3
9
```

## 样例 #2

### 输入

```
3 10
9 4 3
```

### 输出

```
0
0
1
1
0
2
4
2
6
15
```

## 样例 #3

### 输入

```
5 10
13 10 6 4 15
```

### 输出

```
0
0
0
1
0
1
0
2
0
5
```

# 题解

## 作者：Sai0511 (赞：44)

自己在家里乱搞了搞竟然搞出来了2333。    
看到模数$\text{998244353}$第一反应就是多项式题。  
首先可以列出一个很显然易见的式子：       
设$f_i$表示点权和为$i$的符合条件的二叉树的个数，$g_i$表示权值$i$是否包含在$c$中  
$$f_0=1$$
$$f_n=\sum_{i=1}^ng_i\sum_{j=1}^{n-i}f_jf_{n-i-j}[n>0]$$
这个式子的意思枚举一下一个权值是否存在，然后枚举一下左右子树的权值，方案数加起来就好。      
不难发现这个式子就是$3$个多项式卷在一起。   
令$F$表示序列$f$的生成函数，$G$表示序列$G$的生成函数。
那么：
$$F=G*F^2+1$$
根据小学数学中的一元二次方程求根公式，我们可以把这个式子的根求出来。
$$F=\frac{1± \sqrt{1-4G}}{2G}$$   
此时发现有$2$解，分别讨论一下。
$$\text{当取正}\text{号时}\lim_{x→0}\text{为}\infty,\text{舍去}$$
$$\text{当取负}\text{号时}\lim_{x→0}\text{为1},\text{满足}$$
故$F=\frac{1-\sqrt{1-4G}}{2G}$  
化简一下得到
$$F=\frac{2}{1+\sqrt{1-4G}}$$
开根+求逆即可。




---

## 作者：Mr_Wu (赞：21)

我看这题的题解看的真的有点蒙。。

所以我带来了一份看起来比较严谨的题解(?)

## 定义

我们在使用形式幂级数，并定义了加法、减法、乘法。

能够求逆的充要条件是 $a_0\not=0$，即零次项不等于 0。

能够开根的充分条件是 $a_0>0$。这里我写充分条件是因为 $a_0<0$ 肯定不行，而 $a_0=0$ 时要讨论一些东西，我就先省略掉了，而且这个充分条件在下面也够用了。

若 $A(x)B(x)=0$，则 $A(x)=0$ 或 $B(x)=0$。

## 题解

别的题解已经说了：

$$ G*F^2+1=F $$

接下来别的题解都直接使用一元二次方程求根公式，我表示疑惑，因为 $G$ 根本不可求逆，得出来的究竟是个啥 ...

所以我们手动求解（第一步是等式两边同时乘 $G$，第二步是配方，都没有问题罢）：

$$ \begin{aligned} G^2F^2-FG+G=0 \\ (GF-\frac{1}{2})^2=\frac{1}{4}-G \end{aligned} $$

先来讨论 $GF-\frac{1}{2} = \sqrt{\frac{1}{4}-G}$ （很明显 $\frac{1}{4}-G$ 的 0 次项为 $\frac{1}{4}$ 是存在逆元的），此时

$$GF=\frac{\sqrt{1-4G}+1}{2}$$

我们应当表示疑惑，事实上右式零次项为 1，而 $G$ 的零次项为 0，而 $f_0g_0=1$，这不可能！于是我们否决了取正。

再来讨论 $GF-\frac{1}{2}=-\sqrt{\frac{1}{4}-G}$，此时

$$GF=\frac{-\sqrt{1-4G}+1}{2}$$

分式上下同时乘 $1+\sqrt{1-4G}$ （一次项不是 0，当然可以乘），得

$$ GF=\frac{2G}{1+\sqrt{1-4G}} $$

接下来

$$ G \left( F-\frac{2}{1+\sqrt{1-4G}} \right) = 0 $$

故

$$ F=\frac{2}{1+\sqrt{1-4G}} $$

接下来的事情就是上开根和求逆的板子，恕我从略。。

---

## 作者：p_b_p_b (赞：17)

[$$\large \color{purple} My\; Blog$$](https://www.cnblogs.com/p-b-p-b/p/10426011.html)

------------------------

## 思路

看到计数和$998244353$，可以感觉到这是一个DP+生成函数+NTT的题。

设$s_i$表示$i$是否在集合中，$A$为$s$的生成函数，即$A(x)=\sum_n s_nx^n$。

设$f_n$为有$n$分时二叉树的个数。

考虑枚举左子树大小和根节点权值，得到

$$f_n=[n=0]+\sum_{i=1}^{mx} s_i \sum_{j=0}^{n-i} f_jf_{n-i-j}$$

然后记$F(x)$为$f$的生成函数：

$$F(x)=\sum_n f_nx^n$$
$$=1+\sum_n x^n\sum_{i=1}^{mx} s_i \sum_{j=0}^{n-i} f_jf_{n-i-j}$$


可以发现 $(i)+(j)+(n-i-j)=n$

，即后面是三个多项式卷积在一起，得到$F=1+A*F^2$。

利用求根公式得到$F=\frac{1\pm \sqrt{1-4A}}{2A}$。

用某种奇怪的理论得到只能取减号，于是有

$$F=\frac{1-\sqrt{1-4A}}{2A}$$

似乎做完了，但你会发现下面$2A$的常数项为$0$，好像不能多项式求逆。（也许可以？大佬能教我一下吗？）

**update：已经学会如何求逆，将其放在最后。**

怎么办呢？我们可以把这个式子再化一下：
$$
F=\frac{1-\sqrt{1-4A}}{2A}=\frac{2}{1+\sqrt{1-4A}}
$$
此时开根和求逆都没有问题，可以做了。

------------------

## 代码

```cpp
#include<bits/stdc++.h>
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define sz 404040
    #define mod 998244353
    typedef long long ll;
    template<typename T>
    inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();
        double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.')
        {
            ch=getchar();
            while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
        }
        t=(f?-t:t);
    }
    template<typename T,typename... Args>
    inline void read(T& t,Args&... args){read(t); read(args...);}
    void file()
    {
        #ifndef ONLINE_JUDGE
        freopen("a.txt","r",stdin);
        #endif
    }
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

ll ksm(ll x,int y)
{
    ll ret=1;
    for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;
    return ret;
}
ll inv(ll x){return ksm(x,mod-2);}

int limit,r[sz];
ll G[sz],_G[sz];
void init(){for (int mid=1;mid<sz;mid<<=1) _G[mid]=inv(G[mid]=ksm(3,(mod-1)/mid>>1));}
void NTT_init(int n)
{
    limit=1;int l=-1;
    while (limit<=n+n) limit<<=1,++l;
    rep(i,0,limit-1) r[i]=(r[i>>1]>>1)|((i&1)<<l);
}
void NTT(ll *a,int type)
{
    rep(i,0,limit-1) if (i<r[i]) swap(a[i],a[r[i]]);
    rep(i,0,limit-1) a[i]%=mod;
    for (int mid=1;mid<limit;mid<<=1)
    {
        ll Wn=(type==1)?G[mid]:_G[mid];
        for (int j=0,len=mid<<1;j<limit;j+=len)
        {
            ll w=1;
            for (int k=0;k<mid;k++,w=w*Wn%mod)
            {
                ll x=a[j+k],y=a[j+k+mid]*w;
                a[j+k]=(x+y)%mod;a[j+k+mid]=(1ll*mod*mod-y+x)%mod;
            }
        }
    }
    if (type==1) return;
    ll I=inv(limit);
    rep(i,0,limit-1) a[i]=a[i]*I%mod;
}
ll tmp1[sz],tmp2[sz],tmp3[sz],tmp4[sz];
void PolyInv(ll *a,ll *f,int n) // f=a^{-1}
{
    if (n==1) return (void)(f[0]=inv(a[0]));
    int mid=(n+1)>>1;
    PolyInv(a,f,mid);
    NTT_init(n);
    rep(i,0,mid-1) tmp1[i]=f[i];rep(i,mid,limit-1) tmp1[i]=0;
    rep(i,0,n-1) tmp2[i]=a[i];rep(i,n,limit-1) tmp2[i]=0;
    NTT(tmp1,1);NTT(tmp2,1);
    rep(i,0,limit-1) tmp1[i]=tmp1[i]*(mod+2-tmp1[i]*tmp2[i]%mod)%mod;
    NTT(tmp1,-1);
    rep(i,0,n-1) f[i]=tmp1[i];
    rep(i,0,limit-1) tmp1[i]=tmp2[i]=0;
}
void PolySqrt(ll *a,ll *f,int n)
{
    if (n==1) return (void)(f[0]=sqrt(a[0])+0.5);
    int mid=(n+1)>>1;
    PolySqrt(a,f,mid);
    PolyInv(f,tmp3,n);
    rep(i,0,n-1) tmp1[i]=a[i],tmp2[i]=f[i];
    NTT_init(n);
    NTT(tmp1,1);NTT(tmp2,1);NTT(tmp3,1);
    ll inv2=inv(2);
    rep(i,0,limit-1) tmp1[i]=inv2*(tmp1[i]*tmp3[i]%mod+tmp2[i])%mod;
    NTT(tmp1,-1);
    rep(i,0,n-1) f[i]=tmp1[i];
    rep(i,0,limit-1) tmp1[i]=tmp2[i]=tmp3[i]=0;
}

int n,m;
ll a[sz];
ll tt1[sz],tt2[sz];
ll ans[sz];

int main()
{
    file();
    init();
    read(n,m);
    int x;
    rep(i,1,n) read(x),a[x]=1;
    tt1[0]=1;rep(i,1,m) tt1[i]=mod-4*a[i]%mod;
    PolySqrt(tt1,tt2,m+1);
    ++tt2[0];
    PolyInv(tt2,ans,m+1);
    rep(i,1,m) ans[i]=ans[i]*2%mod;
    rep(i,1,m) printf("%lld\n",ans[i]);
    return 0;
}
```

----------------------

## 更新

前文说到不知道怎么多项式求逆，现在学会了更新一发。

考虑到你推出的式子肯定是正确的（不正确我也没办法），那么下面多出来的那些$x^n$肯定可以被上面消掉，否则就没法做了。

那么可以先把$\min\{a_i\}$（记作$mn$）提出来，然后给下面求逆。然后上面开完根之后整体除一个$x^{mn}$即可。

然而这样会有一些奇怪的事情发生：由于对开根后的多项式做了除法，原来全都对$x^{m+1}$取模，现在要搞一些事情，对$x^{\max(m,\max\{a_i\})+mn+1}$取模。（或者你懒的话直接对$x^{200000}$取模也可以）

这样常数会大一些，但也可以通过。

代码：（只有主函数）

```cpp
int n,m;
ll a[sz];int mn=1e9,mx;
ll tt1[sz],sqr[sz],tt2[sz],inva[sz];
ll ans[sz];

int main()
{
    file();
    init();
    read(n,m);
    int x;
    rep(i,1,n) read(x),a[x]=1,mn=min(mn,x),mx=max(mx,x);
    mx=max(mx,m);
    tt1[0]=1;rep(i,1,mx) tt1[i]=(mod-4*a[i])%mod;
	rep(i,0,mx) tt2[i]=2*a[i+mn];
    PolySqrt(tt1,sqr,mx+1+mn);
    PolyInv(tt2,inva,mx+1);
    rep(i,0,mx) sqr[i]=(mod-sqr[i+mn])%mod;
    NTT_init(mx+1);
	rep(i,mx+1,limit-1) sqr[i]=inva[i]=0;
    NTT(inva,1);NTT(sqr,1);
    rep(i,0,limit-1) ans[i]=inva[i]*sqr[i]%mod;
    NTT(ans,-1);
    rep(i,1,m) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：Aleph1022 (赞：15)

众所周知有根无标号二叉树的生成函数就是卡特兰数
$$
C = xC^2+1
$$

现在我们构造单个结点的权值的生成函数
$$
W(x) = \sum\limits_{i=1}^n x^{c_i}
$$

然后根据幂级数的复合的组合意义，我们知道答案的生成函数就是 $C(W(x))$，设其为 $F(x)$。  
我们代入卡特兰数的方程就有
$$
F = W F^2 + 1
$$

即
$$
W F^2 - F + 1 = 0
$$

考虑运用求根公式（如果你因为「不可求逆」而感到困惑，不妨临时将运算视为分式域上的运算，即形式 Laurent 级数）或直接对其牛顿迭代即可。

---

## 作者：bztMinamoto (赞：10)

可以……这很多项式开根模板……而且也完全不知道大佬们怎么把这题的式子推出来的……

首先，这题需要多项式开根和多项式求逆。多项式求逆可以看看蒟蒻写的->[这里](https://www.cnblogs.com/bztMinamoto/p/9743310.html)，这里讲一讲多项式开根

多项式开方：已知多项式$A$，求多项式$B$满足$A^2\equiv B\pmod{x^n}$（和多项式求逆一样这里需要取模，否则$A$可能会有无数项）

假设我们已经求出$A'^2\equiv B\pmod{x^n}$，考虑如何计算出$A^2\equiv B\pmod{x^{2n}}$

首先肯定存在$A^2\equiv B\pmod{x^n}$

然后两式相减$$A'^2-A^2\equiv 0\pmod{x^n}$$

$$(A'-A)(A'+A)\equiv 0\pmod{x^n}$$

我们假设$A'-A\equiv 0\pmod{x^n}$，然后两边平方$$A'^2-2A'A+A^2\equiv 0\pmod{x^{2n}}$$

（关于平方之后模数变化的原因可以看我多项式求逆那篇文章，里面有写）

又因为$A^2\equiv B\pmod{x^{2n}}$，代入得$$A'^2-2A'A+B\equiv 0\pmod{x^{2n}}$$

$$A\equiv\frac{A'^2-B}{2A'}\pmod{x^{2n}}$$

那么这个只要递归计算就可以了

然后多项式开方就讲到这里

下面说一下本题的做法（基本都是抄楼下两位大佬说的）

首先，~~我也不知道怎么想到的~~构造出生成函数，$C=\sum_{i=1}^{lim}s_ix^i$，其中$s_i$表示$i$是否在集合中出现过，然后再设一个$F_k$表示权值为$k$时的答案

因为一棵二叉树可以由根节点，左右子树构成（左右子树可以是空的）

那么存在如下关系$$F_k=1+\sum_{i=1}^ks_i\sum_{j=0}^{k-i}F_jF_{i-j-k}$$

然后~~我也不知道怎么看出来的~~发现这是一个卷积的形式，即$$F=1+C*F*F$$（这里$*$是多项式乘法）

把它看做一个一元二次方程求解，得$$F=\frac{1\pm \sqrt{1-4C}}{2C}=\frac{2}{1\pm\sqrt{1-4C}}$$

然后因为$F_0=1,C_0=0$，所以符号取正，即$$F=\frac{2}{1+\sqrt{1-4C}}$$

那么把多项式开根和多项式求逆的板子带进去就好了
```
//minamoto
#include<iostream>
#include<cstdio>
#include<algorithm>
#define swap(x,y) (x^=y,y^=x,x^=y)
#define mul(x,y) (1ll*x*y%P)
#define add(x,y) (x+y>=P?x+y-P:x+y)
#define dec(x,y) (x-y<0?x-y+P:x-y)
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int K=-1,Z;
inline void Ot(){fwrite(sr,1,K+1,stdout),K=-1;}
inline void print(int x){
    if(K>1<<20)Ot();if(x<0)sr[++K]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++K]=z[Z],--Z);sr[++K]='\n';
}
const int N=500005,P=998244353,G=3,inv2=499122177;
inline int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=mul(res,a);
		a=mul(a,a),b>>=1;
	}
	return res;
}
int n,m,r[N],A[N],B[N],C[N],D[N],O[N],d[N],c[N];
void NTT(int *A,int type,int len){
	int limit=1,l=0;
	while(limit<len) limit<<=1,++l;
	for(int i=0;i<limit;++i)
	r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	for(int i=0;i<limit;++i)
	if(i<r[i]) swap(A[i],A[r[i]]);
	for(int mid=1;mid<limit;mid<<=1){
		int R=mid<<1,Wn=ksm(G,(P-1)/R);O[0]=1;
		for(int j=1;j<mid;++j) O[j]=mul(O[j-1],Wn);
		for(int j=0;j<limit;j+=R){
			for(int k=0;k<mid;++k){
				int x=A[j+k],y=mul(O[k],A[j+k+mid]);
				A[j+k]=add(x,y),A[j+k+mid]=dec(x,y);
			}
		}
	}
	if(type==-1){
		reverse(A+1,A+limit);
		for(int i=0,inv=ksm(limit,P-2);i<limit;++i)
		A[i]=mul(A[i],inv);
	}
}
void Inv(int *a,int *b,int len){
	if(len==1) return (void)(b[0]=ksm(a[0],P-2));
	Inv(a,b,len>>1);
	for(int i=0;i<len;++i) A[i]=a[i],B[i]=b[i];
	NTT(A,1,len<<1),NTT(B,1,len<<1);
	for(int i=0,l=(len<<1);i<l;++i) A[i]=mul(mul(A[i],B[i]),B[i]);
	NTT(A,-1,len<<1);
	for(int i=0;i<len;++i) b[i]=dec(1ll*(b[i]<<1)%P,A[i]);
	for(int i=0,l=(len<<1);i<l;++i) A[i]=B[i]=0;
}
void Sqrt(int *a,int *b,int len){
	if(len==1) return (void)(b[0]=a[0]);
	Sqrt(a,b,len>>1);
	for(int i=0;i<len;++i) C[i]=a[i];
	Inv(b,D,len);
	NTT(C,1,len<<1),NTT(D,1,len<<1);
	for(int i=0,l=len<<1;i<l;++i) D[i]=mul(D[i],C[i]);
	NTT(D,-1,len<<1);
	for(int i=0;i<len;++i) b[i]=mul(add(b[i],D[i]),inv2);
	for(int i=0,l=(len<<1);i<l;++i) C[i]=D[i]=0;
}
int main(){
//	freopen("testdata.in","r",stdin);
	n=read(),m=read();
	for(int i=1,x;i<=n;++i) x=read(),++d[x];
	int len;for(len=1;len<=m;len<<=1);
	for(int i=1;i<len;++i) d[i]=(-4*d[i]+P)%P;
	++d[0];
	Sqrt(d,c,len);
	for(int i=0;i<len;++i) d[i]=0;
	c[0]=add(c[0],1);
	Inv(c,d,len);
	for(int i=0;i<=m;++i) d[i]=add(d[i],d[i]);
	for(int i=1;i<=m;++i) print(d[i]);
	Ot();
	return 0;
}
```

---

## 作者：周道_Althen (赞：7)

## 题目大意

$\ \ \ \ \ \ \,$给你 $n$ 和 $m$，和大小为 $n$ 的集合 $C$。

$\ \ \ \ \ \ \,$需要你统计点权在集合 $C$ 内，且点权之和分别为 $[1,m]$ 的二叉树个数。

## 想法
$\ \ \ \ \ \ \,$根据题目，我们可以想到$DP$公式求解：

$$f(n)=\begin{cases} 1, & \text {$(n=0)$} \\ \sum_{i=1}^{n}g(i)\sum_{j=0}^{n-i}f(j)\cdot f(n-i-j), & \text{$(n > 0)$}\end{cases} $$

$\ \ \ \ \ \ \,$其中：

- $f(i)$意思是且点权之和 $i$ 的二叉树个数。
- $g(i)$意思是集合 $C$ 中是否含有元素 $i$，既 $g(i)=[i\in C]$ 。

$\ \ \ \ \ \ \,$怎么得到这个公式的就不说了，还是比较显然的 ~~（雾~~ 。但是很明显复杂度过不去。我们把它们写成生成函数会好一些 ~~（计数题套路？）~~：

$\ \ \ \ \ \ \,$令函数 $F$ 为序列 $f(x)$ 的生成函数，函数 $G$ 为序列 $g(x)$的生成函数。

$\ \ \ \ \ \ \,$可以得到：

$$F=G*F^2+1$$

$\ \ \ \ \ \ \,$解得：

$$F=\frac{2}{1\pm\sqrt{1-4G}}$$

$\ \ \ \ \ \ \,$那么是加号还是减号啊？已知$F_0=1$。而题目保证 $(1\leq c_i \leq 10^5)$，所以有$G_0=0$。那么带入可以得到应该是取加号。

$\ \ \ \ \ \ \,$所以说只需要求出多项式$\frac{2}{1+\sqrt{1-4G}}$的$[1,m]$项就好了。

$\ \ \ \ \ \ \,$格式挺清新的，需要求逆和开根，模板直接往上套就好了呢：[【多项式的操作大赏】](https://blog.csdn.net/weixin_43973966/article/details/87864851)。我写的开根比较麻烦，还要写 $\ln$ 和 $\exp$，然后 $\ln$ 还要写求积分和求导。所以说……基本上……所有模板都用到了。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190221144821392.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzk3Mzk2Ng==,size_16,color_FFFFFF,t_70)


```cpp
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
using namespace std;
const int inf=0x7fffffff;
const double eps=1e-10;
const double pi=acos(-1.0);
//char buf[1<<15],*S=buf,*T=buf;
//char getch(){return S==T&&(T=(S=buf)+fread(buf,1,1<<15,stdin),S==T)?0:*S++;}
inline int read(){
	int x=0,f=1;char ch;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
	if(f)return x;else return -x;
}
const int mod=998244353,mod_g=3,N=1600000;
int R[N];
int power(int a,int b){
  	int ans=1;
  	for(;b;b>>=1,a=1ll*a*a%mod)
	if(b&1)ans=1ll*ans*a%mod;
  	return ans;
}
#define Inv(x) power(x,mod-2)
int Polynomial_init(int n){
	int len;for(len=1;len<=n;len<<=1);
	return len;
}
void NTT(int *a,int f,int la){
	int n=la;
  	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
  	for(int i=1;i<n;i<<=1){
    	int gn=power(mod_g,(mod-1)/(i<<1));
    	for(int j=0;j<n;j+=(i<<1)){
      		int g=1;
      		for(int k=0;k<i;k++,g=1ll*g*gn%mod){
	        	int x=a[j+k],y=1ll*g*a[i+j+k]%mod;
	        	a[j+k]=(x+y)%mod;a[i+j+k]=(x-y+mod)%mod;
	      	}
    	} 
  	}
  	if(f==-1){
   		reverse(a+1,a+n);
    	int inv=Inv(n);
    	for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
  	}
}
int Convolution(int *a,int *b,int la,int lb){
	int n=la,m=lb;
	int L=0;for(m+=n,n=1;n<m;n<<=1)L++;
	for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	NTT(a,1,n);NTT(b,1,n);
	for(int i=0;i<=n;i++)a[i]=1ll*a[i]*b[i]%mod;
	NTT(a,-1,n);
	return m;
}
int C[N];
void Inverse(int *a,int *b,int len){
  	if(len==1){b[0]=Inv(a[0]);return;}
  	Inverse(a,b,(len+1)>>1);
  	int L=0,n=1;
  	for(;n<(len<<1);n<<=1)L++;
  	for(int i=1;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
  	for(int i=0;i<len;i++)C[i]=a[i];
  	for(int i=len;i<n;i++)C[i]=0;
  	NTT(C,1,n);NTT(b,1,n);
  	for(int i=0;i<=n;i++)b[i]=1ll*(2ll-1ll*C[i]*b[i]%mod+mod)%mod*b[i]%mod;
  	NTT(b,-1,n);
  	for(int i=len;i<n;i++)b[i]=0;
}
void Derivation(int *a,int *b,int n){
	for(int i=1;i<n;i++)
  	b[i-1]=1ll*i*a[i]%mod;
	b[n-1]=0;
}
void Integral(int *a,int *b,int n){
	for(int i=1;i<n;i++)
  	b[i]=1ll*Inv(i)*a[i-1]%mod;
	b[0]=0;
}
int A[N],B[N];
void Logarithmic(int *a,int *b,int len){
	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));
  	Derivation(a,A,len);
  	memset(C,0,sizeof(C));
  	Inverse(a,B,len);
  	Convolution(A,B,len,len);
  	Integral(A,b,len);
}
int D[N];
void Exponential(int *a,int *b,int len){
  	if(len==1){b[0]=1;return;}
  	Exponential(a,b,len>>1),Logarithmic(b,D,len);
  	D[0]=(1ll*a[0]+1ll-D[0]+mod)%mod;
  	for(int i=1;i<len;++i) D[i]=(1ll*a[i]-D[i]+mod)%mod;
  	Convolution(b,D,len<<1,len<<1);
  	for(int i=len;i<(len<<1);++i) b[i]=D[i]=0;
}
int E[N];
void Kth_root(int *a,int *b,int len,int k){
	Logarithmic(a,E,len);
	for(int i=1;i<=len;i++)E[i]=499122177ll*E[i]%mod;
	Exponential(E,b,len);
}
int n,m,F[N],G[N];
int main()
{
	n=read();m=read();
  	for(int i=1;i<=n;++i)++G[read()];
  	int len=Polynomial_init(m);
  	for(int i=0;i<len;++i)G[i]=(mod-(4ll*G[i]%mod))%mod;
  	++G[0];
  	Kth_root(G,F,len,2);
  	for(int i=0;i<len;++i)G[i]=0;
  	F[0]=(F[0]+1)%mod;
  	Inverse(F,G,len);
  	for(int i=0;i<=m;++i)G[i]=(2ll*G[i])%mod;
  	for(int i=1;i<=m;++i)printf("%d\n",G[i]);
	return 0;
}

```



---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF438E)
## 题意
对 $1\le i\le m$ 求满足所有节点权值在集合 $\{c_i|1\le i\le n\}$ 中的有根二叉树个数。其中一节点的权值为其子树中所有节点的权值和。

$1\le n,m,c_i\le10^5$.
## 思路
这题是一道生成函数入门题。

首先想一个 $\text{dp}$，设 $f_i$ 表示权值为 $i$ 的答案，$g_i=[i\in\{c_i\}]$。

$$f_n=[n=0]+\sum_{i\ge1}g_i\sum_{j=1}^{n-i}f_jf_{n-i-j}$$

写出 $f$ 的 $\text{OGF}$，

$$F(x)=\sum_{n\ge0}f_nx^n$$
$$F(x)=1+\sum_{n\ge0}\sum_{i\ge1}g_i\sum_{j=1}^{n-i}f_jf_{n-i-j}x^n$$
$$F(x)=1+G(x)F^2(x)$$
$$G(x)F^2(x)-F(x)+1=0$$

可以解得
$$F(x)=\dfrac{-b\pm\sqrt{b^2-4ac}}{2a}=\dfrac{1\pm\sqrt{1-4G(x)}}{2G(x)}$$
有两解，于是可以将式子化为
$$2F(x)G(x)=1\pm\sqrt{1-4G(x)}$$
此时若取 $+$ 号，有
$$[x^0]2F(x)G(x)=0,[x^0]1+\sqrt{1-4G(x)}\ne0$$
即
$$2F(x)G(x)\ne1+\sqrt{1-4G(x)}$$
故取 $-$ 号。

$$F(x)=\dfrac{1-\sqrt{1-4G(x)}}{2G(x)}$$

$[x^0]G(x)=0$，无法对 $G(x)$ 求逆，考虑上下同乘 $1+\sqrt{1-4G(x)}$，
$$F(x)=\dfrac{4G(x)}{2G(x)+2G(x)\sqrt{1-4G(x)}}$$
$$F(x)=\dfrac{2}{1+\sqrt{1-4G(x)}}$$
接下来就可以直接开根+求逆了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int mod=998244353,inv2=mod+1>>1,N=262145+10;
namespace Poly{
	int a[N],b[N],c[N],rev[N],f[N],g[N],inv[N],fac[N],ifac[N],lim;
	inline void init(int n,int mode=1){
		if(mode){
			int l=0;
			for(lim=1;lim<=n;lim<<=1)l++;
			for(int i=1;i<lim;i++){
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
			}
		}else{
			for(lim=1;lim<=n;lim<<=1);
		}
	}
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
		inv[1]=1;
		for(int i=2;i<=n;i++)
			inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		fac[0]=1;
		for(int i=1;i<=n;i++)
			fac[i]=1ll*fac[i-1]*i%mod;
		ifac[n]=qpow(fac[n],mod-2);
		for(int i=n;i>=1;i--)
			ifac[i-1]=1ll*ifac[i]*i%mod;
	}
	inline void NTT(int *a,int t){
		for(int i=0;i<lim;i++)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(int i=1;i<lim;i<<=1){
			int gl=qpow(3,(mod-1)/(i<<1));
			for(int j=0;j<lim;j+=(i<<1)){
				int t1,t2,now=1;
				for(int k=0;k<i;k++,now=1ll*now*gl%mod){
					t1=a[j+k];
					t2=1ll*now*a[i+j+k]%mod;
					a[j+k]=(t1+t2)%mod;
					a[i+j+k]=(t1-t2+mod)%mod;
				}
			}
		}
		if(t==1) return ;
		int Inv=qpow(lim,mod-2);
		reverse(a+1,a+lim);
		for(int i=0;i<lim;i++)
			a[i]=1ll*a[i]*Inv%mod;
	}
	inline void Inv(int *a,int *b,int n){
		if(n==1){
			b[0]=qpow(a[0],mod-2);
			return ;
		}
		Inv(a,b,n+1>>1);
		init(n<<1);
		for(int i=0;i<n;i++)
			c[i]=a[i];
		for(int i=n;i<lim;i++)
			c[i]=0;
		NTT(c,1),NTT(b,1);
		for(int i=0;i<lim;i++)
			b[i]=1ll*(2-1ll*c[i]*b[i]%mod+mod)%mod*b[i]%mod;
		NTT(b,-1);
		for(int i=n;i<lim;i++)
			b[i]=0;
	}
	inline void Mul(int *f,int *g,int *h,int n){
		static int a[N],b[N];
		init(n<<1);
		memset(a,0,lim<<2);
		memcpy(a,f,n<<2);
		memset(b,0,lim<<2);
		memcpy(b,g,n<<2);
		NTT(a,1),NTT(b,1);
		for(int i=0;i<lim;i++){
			h[i]=1ll*a[i]*b[i]%mod;
		}
		NTT(h,-1);
	}
	inline void Sqrt(int *f,int *g,int n){
		if(n==1){ g[0]=1;return ; }
		Sqrt(f,g,n+1>>1);
		memset(a,0,n<<2);
		Inv(g,a,n);
		Mul(f,a,a,n);
		for(int i=0;i<n;i++)
			g[i]=1ll*(g[i]+a[i])*inv2%mod;
	} 
}
using namespace Poly;
int n,m,mx;
int main(){
	n=read(),m=read()+1;
	for(int i=0;i<n;i++){
		int x=read();
		g[x]++;
		mx=max(mx,x);
	}
	mx++;
	for(int i=1;i<mx;i++)
		if(g[i])
			g[i]=mod-4*g[i];
	g[0]++;
	Sqrt(g,b,m);
	b[0]++;
	Inv(b,f,m);
	for(int i=1;i<m;i++)
		write(f[i]*2%mod),putc('\n');
	flush();
}
```
再见 qwq~

---

## 作者：shadowice1984 (赞：4)

都是多项式开根啊……虽然可以理解

不过我非常喜欢分治fft所以我用分治fft过了这题
__________________

### 前置芝士：快速傅里叶变换/快速数论变换(ftt/ntt)

那个……如果不会多项式的基础芝士的话还是出门左转你站模板区去学习一下好了

## 本题题解

那么我们先来推一下dp式子不然我们做不了这题……

我们设$f(n)$表示权值恰好为n的二叉树的个数，设$c(i)$表示i这种权值是否出现

接下来我们的转移就十分的简单粗暴了，我们枚举根的权值是什么，这样我们就可以得到这样一个柿子

$$f(n)=\sum_{i+j=n}c(i)g(j),f(0)=1$$

等一下，g是什么呢？

我们发现我们枚举完根的权值之后还剩下一些权值分给左右儿子,由于左子树和右子树是两颗树，因此我们不能简单的递归到f来解决问题，所以我们设了一个中转数组g来解决问题，我们令$g(n)$表示权值和恰好为n的有序二叉树对的个数，或者说，我们令g表示这个式子

$$g(n)=\sum_{i+j=n}f(i)f(j),g(0)=1$$

然后这又有什么用呢?

似乎我们推出来的式子和普通的分治fft式子相去甚远。

我们推出来的式子似乎是一个**我 卷 我 自 己**的形式，或者更加准确点，f和g这两个数组在左右互搏……，看起来此时我们似乎不能使用传统的分治fft来解决这个问题了……

但是事实上这种式子分治fft还是能做的，因为分治fft本质上是一个cdq分治，因此我们依然可以使用cdq分治的思想解决这个问题

再具体点来讲我们依然使用cdq分治的老套路，考虑左侧询问对右侧询问的贡献

当然前提是我们递归下去了左半边，这样的话我们可以假设左侧的f和g是全部求好的

假设我们正在分治区间$[l,r)$，左侧区间是$[l,mid)$右侧区间是$[mid,r)$

接下我们希望求出左侧区间对于右侧区间中一个点n的贡献，换句话说，我们希望计算这个式子

$$\sum_{i+j=n}c(i)g(j)$$

并且满足一个限制条件是i和j至少有一个落在$[l,mid)$这个区间当中

那么我们把这个贡献拆成三部分来计算，第一部分是i和j都落在$[l,mid)$这个区间时对答案的贡献，也就是让我们求出这个式子

$$\sum_{i=l}^{mid-1}c(i)\sum_{j=l}^{mid}g(j)[i+j=n]$$

然后我们令$c'(i)=c(i-l),g'(j)=g(j-l)$我们会得到这样一个神奇的式子

$$\sum_{i=0}^{mid-l-1}c'(i)\sum_{j=0}^{mid-l-1}g'(j)[i+j=n-2l]$$

那么我们只需要对$c',g'$做一遍卷积就可以计算出这一部分的贡献了，此时我们的卷积的序列长度是分治区间长度级别的所以复杂度依然是对的

接下来我们考虑i落在这个区间而j不落在这个区间的贡献，它是这个式子

$$\sum_{i=l}^{mid-1}c(i)\sum_{j=0}^{l-1}g(j)[i+j=n]$$

当然此时我们依然用$c'$来代换$c$所以我们可以得到这个式子

$$\sum_{i=0}^{mid-1}c(i)\sum_{j=0}^{l-1}g(j)[i+j=n-l]$$

我们注意到一件事情是$n$是在$(mid,n]$这个区间内的，所以$n-l$的值不会超过$r-l$也就是当前分治区间的长度,所以对于g这个多项式，我们仅仅需要保留前$(r-l)$项

此时我们将$c'$和$g$卷出来依然可以正确的推出这一部分的贡献，并且我们此时卷积的序列长度依然是分治区间长度级别的，所以我们的复杂度依然是对的

对于第三部分的贡献也就是i不落在左侧区间而j落在左侧区间的贡献，计算方法和上面一致，我们用$g'$卷上保留前$(r-l)$系数的c多项式就可以轻松计算出这部分的贡献了

那么我们计算完左侧c和g对右侧f的贡献之后我们还需要计算左侧f对右侧g的贡献

这个部分和刚才的推导方式差不多，都是分情况讨论3种不同情况的贡献，不过这里有一个好处就是第二种贡献和第3种贡献的权值相等，因此可以只做一遍卷积然后把权值乘2就可以计算了

如此这般我们就将每一层的卷积长度控制在了分治区间长度级别

所以我们的复杂度就是$T(n)=2T(n/2)+O(nlogn)=O(nlog^2n)$了

这样的话我们就成功通过cdq分治处理出了f数组，然后我们就可以通过这道题啦~

注意一件事情是当分治区间长度是1的时候我们需要特殊处理一下c对f的贡献和f对g的贡献，这个自己手动加上就行了

然后听起来这东西挺麻烦其实代码并不长……

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=262144+10;typedef unsigned long long ll;const ll mod=998244353;
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=a*a%mod)if(p&1)r=r*a%mod;return r;}
int rv[22][N];ll rt[2][22];int n;int m;
inline void pre()//简易的ntt板子 
{
    for(int i=1;i<=18;i++)
        for(int j=1;j<(1<<i);j++)rv[i][j]=(rv[i][j>>1]>>1)|((j&1)<<(i-1));
    for(int i=1,t=(mod-1)/2;i<=20;t>>=1,i++)rt[0][i]=po(3,t);
    for(int i=1,t=(mod-1)/2;i<=20;t>>=1,i++)rt[1][i]=po(332748118,t);
}
# define md(x) (x=((x>mod)?x-mod:x))
inline void ntt(ll* a,int len,int d,int o)
{
    for(int i=0;i<len;i++)if(i<rv[d][i])swap(a[rv[d][i]],a[i]);
    for(int k=1,j=1;k<len;k<<=1,j++)
        for(int s=0;s<len;s+=(k<<1))
            for(int i=s,w=1;i<s+k;i++,w=w*rt[o][j]%mod)
                {ll a1=a[i+k]*w%mod;a[i+k]=a[i]+mod-a1;md(a[i+k]);a[i]+=a1;md(a[i]);}
    if(o){ll iv=po(len,mod-2);for(int i=0;i<len;i++)(a[i]*=iv)%=mod;}
}ll f[N];ll g[N];ll c[N];ll tr1[N];ll tr2[N];ll tr3[N];
ll tf[20][N];ll tg[20][N];ll tc[20][N];ll ck[N];ll bru[N];
inline void solve(int l,int r,int k)//分治fft 
{
    if(r-l==1){f[0]=1;g[0]=1;(f[l]+=c[l])%=mod;(g[l]+=f[l]*2)%=mod;return;}
    int mid=(l+r)/2;solve(l,mid,k-1);
    for(int i=l;i<mid;i++)tr1[i-l]=c[i];for(int i=(1<<(k-1));i<(1<<(k+1));i++)tr1[i]=0;
    for(int i=l;i<mid;i++)tr2[i-l]=g[i];for(int i=(1<<(k-1));i<(1<<(k+1));i++)tr2[i]=0;	
    ntt(tr1,(1<<(k+1)),k+1,0);ntt(tr2,(1<<(k+1)),k+1,0);//左侧对右侧的贡献 
    for(int i=0;i<(1<<(k+1));i++)tr3[i]=tr1[i]*tr2[i]%mod;ntt(tr3,(1<<(k+1)),k+1,1);
    for(int i=max(mid,(l<<1));i<r;i++)(f[i]+=tr3[i-(l<<1)])%=mod;
    for(int i=0;i<(1<<(k+1));i++)tr3[i]=tr1[i]*tg[k][i]%mod;ntt(tr3,(1<<(k+1)),k+1,1);
    for(int i=mid;i<r;i++)(f[i]+=tr3[i-l])%=mod;
    for(int i=0;i<(1<<(k+1));i++)tr3[i]=tr2[i]*tc[k][i]%mod;ntt(tr3,(1<<(k+1)),k+1,1);
    for(int i=mid;i<r;i++)(f[i]+=tr3[i-l])%=mod;
    for(int i=l;i<mid;i++)tr1[i-l]=f[i];for(int i=(1<<(k-1));i<(1<<(k+1));i++)tr1[i]=0;
    ntt(tr1,(1<<(k+1)),k+1,0);
    for(int i=0;i<(1<<(k+1));i++)tr3[i]=tr1[i]*tr1[i]%mod;ntt(tr3,(1<<(k+1)),k+1,1);
    for(int i=max(mid,(l<<1));i<r;i++)(g[i]+=tr3[i-(l<<1)])%=mod;
    for(int i=0;i<(1<<(k+1));i++)tr3[i]=tr1[i]*tf[k][i]%mod;ntt(tr3,(1<<(k+1)),k+1,1);
    for(int i=mid;i<r;i++)(g[i]+=2*tr3[i-l])%=mod;solve(mid,r,k-1);
    if(l==0)
    {
        for(int i=0;i<r;i++)tf[k][i]=f[i];ntt(tf[k],(1<<(k+1)),k+1,0);
        for(int i=0;i<r;i++)tg[k][i]=g[i];ntt(tg[k],(1<<(k+1)),k+1,0);
        for(int i=0;i<r;i++)tc[k][i]=c[i];ntt(tc[k],(1<<(k+1)),k+1,0);
    }
}
int main()
{
    pre();scanf("%d%d",&n,&m);for(int i=1,t;i<=n;i++)scanf("%d",&t),c[t]=1;
    solve(0,131072,17);for(int i=1;i<=m;i++)printf("%I64d\n",f[i]);return 0;//拜拜程序~ 
}
```















---

## 作者：Orion545 (赞：4)

# 题面

[传送门](https://www.lydsy.com/JudgeOnline/problem.php?id=3625)

# 思路

首先，我们把这个输入的点的生成函数搞出来：

$C=\sum_{i=0}^{lim}s_ix^i$

其中$lim$为集合里面出现过的最大的数，$s_i$表示大小为$i$的数是否出现过

我们再设另外一个函数$F$，定义$F_k$表示总权值为$k$的二叉树个数

那么，一个二叉树显然可以通过两个子树（可以权值为0，也就是空子树）和一个节点构成

那么有如下求$F$的式子

$F_0=1$

$F_k=\sum_{i=0}^k s_i \sum_{j=0}^{k-i} F_j F_{k-i-j}$

显然这个式子是一个卷积的形式

我们把这个三个东西的卷积放到整个函数上来考虑（也就是把$F_kC_k$看做多项式的系数做卷积），可以得到：

$F=C\ast F\ast F +1$，这里的$\ast$是多项式乘法

由于多项式乘法和普通乘法一样满足各种定律之类的，所以我们可以解个一元二次方程

$C\ast F^2 - F + 1=0$

$F=\frac{1\pm \sqrt{1-4C}}{2C}$

先考虑上面是+的情况

此时${\lim_{x \to 0}}F(x)=+\infty$，舍去

再考虑-的情况

此时${\lim_{x \to 0}}F(x)=1$，OK

其实到这里就可以算了，一个多项式开方+多项式求逆就解决了

但是我们更进一步，再划一划这个式子，可以变成如下形式：

$F=\frac{2}{1+\sqrt{1-4C}}$

这样更加方便求根+求逆一波解决，不用两个东西分开求

多项式开方+多项式求逆解决问题

# Code:

这题超！级！卡！常！我这种人傻常数大的，只能参照爷稳稳的代码写一写了qwq

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<cmath>
#include<ctime>
#define ll long long
#define MOD 998244353
using namespace std;
inline int read(){
	int re=0,flag=1;char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
	return re*flag;
}
int n,m,K;
ll A[600010],B[600010],C[600010],x[600010],y[600010];
int g=3,ginv,inv2,r[600010],lim,cnt;
ll qpow(ll a,ll b){
	ll re=1;
	while(b){
		if(b&1) re=re*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return re;
}
ll add(ll a,ll b){
	a+=b;
	return (a>=MOD)?a-MOD:a;
}
ll dec(ll a,ll b){
	a-=b;
	return (a<0)?a+MOD:a;
}
void ntt(ll *a,ll type){
	int i,j,k;ll x,y,w,wn,inv,mid;
	for(i=0;i<lim;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(mid=1;mid<lim;mid<<=1){
		wn=qpow((type==1)?g:ginv,(MOD-1)/(mid<<1));
		for(j=0;j<lim;j+=(mid<<1)){
			w=1;
			for(k=0;k<mid;k++,w=w*wn%MOD){
				x=a[j+k];y=a[j+k+mid]*w%MOD;
				a[j+k]=add(x,y);
				a[j+k+mid]=dec(x,y);
			}
		}
	}
	if(~type) return;
	inv=qpow(lim,MOD-2);
	for(i=0;i<lim;i++) a[i]=a[i]*inv%MOD;
}
void getinv(ll *a,ll *b,int len,int lena){
	if(len==1){b[0]=qpow(a[0],MOD-2);return;}
	assert(len==((len>>1)<<1));
	int i,mid=len>>1;
	getinv(a,b,mid,lena);
	lim=1;cnt=0;r[0]=0;
	while(lim<=(len<<1)) lim<<=1,cnt++;
	for(i=0;i<lim;i++) r[i]=((r[i>>1]>>1)|((i&1)<<(cnt-1)));

	for(i=0;i<len;i++) x[i]=a[i];
	for(i=len;i<lim;i++) x[i]=0;
	for(i=0;i<mid;i++) y[i]=b[i];
	for(i=len;i<lim;i++) y[i]=0;

	ntt(x,1);ntt(y,1);
	for(i=0;i<lim;i++) x[i]=y[i]*(2ll-y[i]*x[i]%MOD+MOD)%MOD;
	ntt(x,-1);
	for(i=0;i<len;i++) b[i]=x[i];
}
void getrt(ll *a,ll *b,int len){
	if(len==1){b[0]=1;return;}
	int i,mid=len>>1;
	
	getrt(a,b,mid);
	memset(C,0,sizeof(C));getinv(b,C,len,len);
	
	lim=1;cnt=0;r[0]=0;
	while(lim<=(len<<1)) lim<<=1,cnt++;
	for(i=0;i<lim;i++) r[i]=((r[i>>1]>>1)|((i&1)<<(cnt-1))),x[i]=a[i];
	for(i=len;i<lim;i++) x[i]=C[i]=b[i]=0;
	
	ntt(x,1);ntt(C,1);
	for(i=0;i<lim;i++) x[i]=x[i]*C[i]%MOD;
	ntt(x,-1);
	
	for(i=0;i<len;i++) b[i]=add(b[i],x[i])*inv2%MOD;
}
void init(){
	ginv=qpow(g,MOD-2);
	inv2=qpow(2,MOD-2);
}
int main(){
	init();
	n=read();m=read();int i,t1;A[0]=K=1;
	for(i=1;i<=n;i++) t1=read(),A[t1]=dec(A[t1],4);
	while(K<=m) K<<=1;

	getrt(A,B,K);
	B[0]=add(B[0],1);
	memset(C,0,sizeof(C));
	getinv(B,C,K,K);
	for(i=1;i<=m;i++) printf("%lld\n",(2*C[i]+MOD)%MOD);
}

```

---

## 作者：Illusory_dimes (赞：3)

### 题目描述
给定一个包含 $n$ 个正整数的集合 $\xi$ 和一个正整数 $m$ 。

定义一个合法的二叉树为在一个二叉树中每个点的点权均属于正整数集 $\xi$ ，规定一个合法的二叉树的权值为所有点的点权之和。

问：对于任意 $\forall\ i\in [1,m]$ 求权值为 $i$ 的合法二叉树个数。

$1\leq n,m\leq 10^5$ ，所有正整数均不超过 $10^5$ 。

### 前置芝士
多项式开根（和已经包括进去的多项式求逆）

### solution
直接找到所有合法的肯定不现实，那么怎么将大化归到小呢

首先，没有节点肯定合法（虽然从答案贡献上没有意义）

其次一个合法的二叉树可以表示成两个合法的子树外加根节点（也要合法）

设合法的二叉树的生成函数为 $f(x)$ ，定义函数 $g(x)=\sum_{i=0}^{\infty}[i\in\xi]\cdot x^i$ 。

那么，方程也就写出来了： $f(x)=g(x)\cdot f^2(x)+1$ 。

再根据我们已有的小学知识“一元二次方程求根公式”（差点就忘了）

所以 $f=\Large\frac{1\pm \sqrt{1\ -\ 4\cdot g}}{2\cdot g}$

显然，取正号的时候在 $x$ 趋于 $0$ 的时候是 $\infty$ ，也就舍掉了。

所以 $f=\Large\frac{1-\sqrt{1\ -\ 4\cdot g}}{2\cdot g}$

通过 $g$ 的定义看得出， $[x^0]g(x)=0$ ，是不能做多项式求逆的，所以分子有理化一下，就是

$f=\Large\frac{2}{1+\sqrt{1\ -\ 4\cdot g}}$

欸，能做了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+10;
typedef ll arr[N];
const int mod=998244353;
const int inv3=332748118;
const int inv2=499122177;
int n,m,inv,lim=1,fre,id[N];
arr f,g,h,ans,tmp;
inline ll inc(ll x,ll y){return x+y>=mod?x+y-mod:x+y;}
inline ll dec(ll x,ll y){return x-y<0?x-y+mod:x-y;}
inline ll mul(ll x,ll y){return 1ll*x*y%mod;}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline int ksm(int a,int b)
{
	int tmp=1;
	while(b)
	{
		if(b&1)tmp=(1ll*tmp*a)%mod;
		b>>=1,a=(1ll*a*a)%mod;
	}
	return tmp;
}
inline void Never_Tell_TLE(ll* NTT,int sign)
{
	for(int i=0;i<=lim;++i)if(i<id[i])
	{
		ll NTt=NTT[i];
		NTT[i]=NTT[id[i]];
		NTT[id[i]]=NTt;
	}
	for(int mid=1;mid<lim;mid<<=1)
	{
		int Unit_root;
		if(sign==1)Unit_root=ksm(3,(mod-1)/(mid<<1));
		else Unit_root=ksm(inv3,(mod-1)/(mid<<1));
		for(int R=mid<<1,r=0;r<lim;r+=R)
		{
			int pw=1;
			for(int l=0;l<mid;++l,pw=(1ll*pw*Unit_root)%mod)
			{
				int butt=NTT[l+r],rfly=(1ll*pw*NTT[l+r+mid])%mod;
				NTT[l+r]=inc(butt,rfly);
				NTT[l+r+mid]=dec(butt,rfly);
			}
		}
	}
	if(sign==-1)
	{
		int inv_lim=ksm(lim,mod-2);
		for(int i=0;i<=lim;++i)NTT[i]=mul(NTT[i],inv_lim);
	}
}
inline void Inv(ll* F,ll* G,int nm)
{
	if(nm==1)
	{
		G[0]=ksm(F[0],mod-2);
		return;
	}
	Inv(F,G,(nm+1)>>1);
	lim=1,fre=0;
	for(;lim<(nm<<1);lim<<=1)++fre;
	for(int i=0;i<=lim;++i)id[i]=(id[i>>1]>>1)|((i&1)<<(fre-1));
	for(int i=0;i<nm;++i)ans[i]=F[i];
	for(int i=nm;i<=lim;++i)ans[i]=0;
	Never_Tell_TLE(ans,1),Never_Tell_TLE(G,1);
	for(int i=0;i<=lim;++i)G[i]=mul(inc(2ll,-mul(ans[i],G[i])+mod),G[i]);
	Never_Tell_TLE(G,-1);
	for(int i=nm;i<=lim;++i)G[i]=0;
}
inline void solve(ll* F,ll* G,int nm)
{
	if(nm==1)
	{
		G[0]=ksm(F[0],mod-2);
		return;
	}
	solve(F,G,(nm+1)>>1);
	for(int i=0;i<=(nm<<1);++i)tmp[i]=0;
	Inv(G,tmp,nm);
	lim=1,fre=0;
	for(;lim<(nm<<1);lim<<=1)++fre;
	for(int i=0;i<=lim;++i)id[i]=(id[i>>1]>>1)|((i&1)<<(fre-1));
	for(int i=0;i<nm;++i)ans[i]=F[i];
	for(int i=nm;i<=lim;++i)ans[i]=0;
	Never_Tell_TLE(ans,1),Never_Tell_TLE(tmp,1),Never_Tell_TLE(G,1);
	for(int i=0;i<=lim;++i)G[i]=mul(inc(G[i],mul(ans[i],tmp[i])),inv2);
	Never_Tell_TLE(G,-1);
	for(int i=nm;i<=lim;++i)G[i]=0;
}
int main()
{
	n=read(),m=read();
	for(int i=0;i<n;++i)++f[read()];
	for(int i=1;i<=1e5;++i)f[i]=dec(mod,f[i]<<2);
	f[0]=1;
	lim=1,fre=0;
	for(;lim<=m;lim<<=1)++fre;
	solve(f,g,lim);
	g[0]=inc(g[0],1);
	lim=1,fre=0;
	for(;lim<=m;lim<<=1)++fre;
	Inv(g,h,lim);
	for(int i=1;i<=m;++i)printf("%d\n",mul(2,h[i]));
	return 0;
}
```
只求能帮助到几个人罢。。

---

## 作者：RyexAwl (赞：3)

令$f_k$为价值恰好为$k$的二叉树个数，$g_k$为$k$是否在集合$\{c[1],c[2],c[3]...c[n]\}$中：
$$
f_k=\sum_{i=1}^kg_i\sum_{j=0}^{k-i}f_{k-i-j}
$$

考虑其$\text{OGF}\ \ F(x),G(x)$

$$
\begin{aligned}
F(x) &=\sum_{k\ge 1}(\sum_{1\le i\le k}g_i\sum_{0\le j\le k-i}f_jf_{k-i-j} )x^k +1\\
&=\sum_{k\ge 1}(\sum_{i=1}^kg_i[x^{k-i}]F(x)^2) x^k+1\\
&=\sum_{k\ge 1}(\sum_{i=1}^k[x^i]G(x) [x^{k-i}]F(x)^2) x^k+1\\
&=\sum_{k\ge 1}([x^k]G(x)F(x)^2)x^k+1
\end{aligned}
$$

因此
$$
F(x)=G(x)F(x)^2+1
$$

故有：

$$
F(x)=\frac{1\pm\sqrt{1-4G(x)}}{2G(x)}
$$

考虑取正
$$
2G(x)F(x)=1+\sqrt{1-4G(x)}
$$

右式常数项系数不为$0$，而左式常数项系数显然为$0$，因此只能取负。

$$
F(x)=\frac{1-\sqrt{1-4G(x)}}{2G(x)}
$$

因为$G(x)$常数项系数为$0$，不可求逆，考虑化简。

上下同时乘$(1+\sqrt{1-4G(x)})$

可得

$$
F(x)=\frac{2}{1+\sqrt{1-4G(x)}}
$$

开根求逆即可。



---

## 作者：Great_Influence (赞：3)

多项式开根模板题。

设$C=\displaystyle\sum_{i\in c}x^i$，答案为$F$，则

存在关系

$F(i)=1+\sum\limits_{t=1}^n\sum\limits_{j=0}^{i-c[t]}F(j)F(i-c[t]-j)$

$=(C*F*F)(i)+1$

即$F=C*F^2+1$。

利用初中解方程的方法，可以解出

$\displaystyle F=\frac{1\pm\sqrt{1-4C}}{2C}=\frac{2}{1\pm\sqrt{1-4C}}$

根据$F(0)=1,C(0)=0$可以知道$\displaystyle F=\frac{2}{1+\sqrt{1-4C}}$。

然后就直接多项式开根+求逆即可解决此题。时间复杂度$O(nlogn)$。

至于怎么开根，详情请见[多项式总结](https://www.luogu.org/blog/user7035/duo-xiang-shi-zong-jie)。

代码:

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
const int MAXN=1<<20;

typedef long long ll;

namespace polynomial
{
	static int mod=998244353,gen=3,g[21],rev[MAXN],Len;

	inline int ad(int a,int b){return (a+=b)>=mod?a-mod:a;}

	inline int power(int a,int b)
	{
		static int sum;
		for(sum=1;b;b>>=1,a=(ll)a*a%mod)if(b&1)
			sum=(ll)sum*a%mod;
		return sum;
	}

	inline void predone()
	{
		static int i,j;
		for(i=1,j=2;i<=20;++i,j<<=1)g[i]=power(gen,(mod-1)/j);
	}

	inline void calrev(int Len)
	{
		static int Logl;Logl=(int)floor(log(Len)/log(2)+0.3)-1;
		Rep(i,1,Len-1)rev[i]=(rev[i>>1]>>1)|((i&1)<<Logl);
	}

	inline void NTT(int X[],int typ)
	{
		Rep(i,1,Len-1)if(i<rev[i])swap(X[i],X[rev[i]]);
		static int i,j,k,kk,w,t,wn,r;
		for(k=2,kk=1,r=1;k<=Len;k<<=1,kk<<=1,++r)
		{
			wn=g[r];
			for(i=0;i<Len;i+=k)for(j=0,w=1;j<kk;++j,w=(ll)w*wn%mod)
			{
				t=(ll)w*X[i+j+kk]%mod;
				X[i+j+kk]=ad(X[i+j],mod-t);
				X[i+j]=ad(X[i+j],t);
			}
		}
		if(typ==-1)
		{
			reverse(X+1,X+Len);
			static int invn;invn=power(Len,mod-2);
			Rep(i,0,Len-1)X[i]=(ll)X[i]*invn%mod;
		}
	}

	static int x[MAXN],y[MAXN];
	inline void mul(int a[],int b[])
	{
		memset(x,0,sizeof x);memset(y,0,sizeof y);
		Rep(i,0,(Len>>1)-1)x[i]=a[i],y[i]=b[i];
		NTT(x,1);NTT(y,1);
		Rep(i,0,Len-1)x[i]=(ll)x[i]*y[i]%mod;
		NTT(x,-1);
		Rep(i,0,Len-1)a[i]=x[i];
	}
	
	static int c[2][MAXN];
	
	inline void Inv(int a[],int n)
	{
		static int t;t=0;
		memset(c,0,sizeof c);
		c[0][0]=power(a[0],mod-2);
		Len=2;
		while(Len<=(n<<1))
		{
			Len<<=1;calrev(Len);t^=1;
			memset(c[t],0,sizeof c[t]);
			Rep(i,0,Len)c[t][i]=ad(c[t^1][i],c[t^1][i]);
			mul(c[t^1],c[t^1]);mul(c[t^1],a);
			Rep(i,0,Len)c[t][i]=ad(c[t][i],mod-c[t^1][i]);
		}
		Rep(i,0,Len-1)a[i]=c[t][i];
	}
	
	static int sq[2][MAXN];

	inline void Sqrt(int *a,int n)
	{
		static int t,z;t=0;
		memset(sq,0,sizeof sq);
		sq[0][0]=sqrt(a[0]);
		Len=z=2;
		while(z<=(n<<1))
		{
			z<<=1;t^=1;
			memset(sq[t],0,sizeof sq[t]);
			Rep(i,0,z)sq[t][i]=sq[t^1][i],sq[t^1][i]=ad(sq[t^1][i],sq[t^1][i]);
			calrev(Len=z);
			mul(sq[t],sq[t]);
			Rep(i,0,z)sq[t][i]=ad(sq[t][i],a[i]);
			Inv(sq[t^1],z>>1);
			calrev(Len=z);
			mul(sq[t],sq[t^1]);
		}
		Rep(i,0,n)a[i]=sq[t][i];
	}
}
using namespace polynomial;

static int n,m,F[MAXN];

int main(void){
	predone();
	read(n);read(m);
	static int x;
	Rep(i,1,n)
	{
		read(x);
		if(x<=m)F[x]=1;
	}
	Rep(i,0,m)F[i]=ad((i==0),mod-F[i]*4);
	Sqrt(F,m+1);F[0]=ad(F[0],1);
	Inv(F,m+1);
	Rep(i,1,m)printf("%d\n",ad(F[i],F[i]));
	return 0;
}
```

---

## 作者：JustinRochester (赞：2)

明天考大物，今晚冲一发......生成函数

~~话说冲生成函数，真的有助于明天大物考试吗~~

---

**【分析】**
--

不难列出 dp 方程：设 $f_m$ 表示权值和为 $m$ 的二叉树种类

初始值 $f_0=1$

考虑枚举根节点：

$\displaystyle f_m=\sum_{i=0}^n(\sum_{p+q=m-c_i}f_pf_q)(m>0)$

但是显然，这样的枚举肯定是复杂度不够的

我们设 $g_n=[\exists t\wedge c_t=n]$ ，即表示 $n$ 是否在 $\{c_n\}$ 序列中出现

则转移方程可改为 $\displaystyle f_m=\sum_{i=0}^m g_i(\sum_{p+q=m-i}f_pf_q)=\sum_{p+q+r=m}f_pf_qg_r(m>0)$

显然，右边的和式为卷积的形式

分别构造序列 $\{f_m\},\{g_m\}$ 的 OGF 为 $F(x),G(x)$

$\therefore F(x)$

$\displaystyle =\sum_{m=0}^\infty f_mx^m$

$\displaystyle =\sum_{m=1}^\infty (\sum_{p+q+r=m}f_pf_qg_r)x^m+f_0x^0$

$=F^2(x)\cdot G(x)+1$

故得到 $G\cdot F^2+(-1)\cdot F+1=0$

解方程得 $\displaystyle F={1-\sqrt{1-4G}\over 2G}$

这个式子本可以直接求解了，但由于 $\{c_n\}$ 序列中不存在等于 $0$ 的项，故不好直接求逆（或者根本不行）

考虑化简表达式：

$\displaystyle F={(1-\sqrt{1-4G})(1+\sqrt{1-4G})\over 2G\cdot (1+\sqrt{1-4G})}={1-(1-4G)\over 2G(1+\sqrt{1-4G})}={2\over 1+\sqrt{1-4G}}$

故先将 $(1-4G)$ 进行多项式开方，常数项 $+1$ 后直接求逆，然后翻倍即可

由于根据上面的分析， $G[0]=0$ ，因此 $(1-4G)[0]=1$ ，开方的时候常数项直接视为 $1$ 即可，避免写 BSGS

接下来就是板子的事情了

总结一下，现在需要输出前 $m$ 项，即求 $\displaystyle F(x)={2\over 1+\sqrt{1-4G(x)}}\pmod{x^m}$

---

**【代码】**
--

代码使用了本人前一段时间整理的多项式全家桶的一部分，仅需要用到 NTT、多项式乘法、多项式求逆、多项式开方

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1<<18,MOD=998244353;
inline int add(int a,int b) { return (a+b>=MOD)?(a+b-MOD):(a+b); }
inline int dis(int a,int b) { return (a-b<0)?(a-b+MOD):(a-b); }
inline int fpow(ll a,ll x) { ll ans=1; for(;x;x>>=1,a=a*a%MOD) if(x&1) ans=ans*a%MOD; return ans; }
//快速幂
inline int inv(ll a) { return fpow(a,MOD-2); }//数的逆元
int Omega[2][22],Frac[MAXN],InF[MAXN],InV[MAXN];
inline void pre(){
    Omega[1][21]=fpow(3,MOD>>21);
    Omega[0][21]=inv( Omega[1][21] );
    for(int i=20;i>=0;i--)
        Omega[1][i]=1ll*Omega[1][i+1]*Omega[1][i+1]%MOD,
        Omega[0][i]=1ll*Omega[0][i+1]*Omega[0][i+1]%MOD;
    //预处理单位根
    
    Frac[0]=1;
    for(int i=1;i<=1e5;i++) Frac[i]=1ll*Frac[i-1]*i%MOD;
    InF[int(1e5)]=inv(Frac[int(1e5)]);
    for(int i=1e5;i>=0;i--) InF[i-1]=1ll*InF[i]*i%MOD;
    for(int i=1;i<=1e5;i++) InV[i]=1ll*InF[i]*Frac[i-1]%MOD;
    //预处理阶乘、阶乘逆元、数的逆元
}
int L,Rev[MAXN],invL;
inline void preNTT(){
    Rev[1]=L>>1;
    for(int i=2;i<L;i++) Rev[i]=(Rev[i>>1]>>1)|Rev[i&1];
    invL=inv(L);
}
inline void NTT(int f[MAXN],short op){
    for(int i=1;i<L;i++) if(i<Rev[i]) swap(f[i],f[Rev[i]]);
    for(int bas=2,mid=1,lb=1;bas<=L;bas<<=1,mid<<=1,lb++)
        for(int l=0,omega=Omega[op][lb],buf,tmp;buf=1,l<L;l+=bas)
            for(int k=l;tmp=1ll*buf*f[k+mid]%MOD,k<mid+l;k++,buf=1ll*buf*omega%MOD)
                f[k+mid]=dis(f[k],tmp),f[k]=add(f[k],tmp);
    if(!op) for(int i=0;i<L;i++) f[i]=1ll*f[i]*invL%MOD;
}
inline void mul(int f[MAXN],int g[MAXN],int h[MAXN],int N,int M,int mod=-1){
    static int p[MAXN],q[MAXN];
    L=1;
    while(L<N+M) L<<=1;
    preNTT();
    for(int i=0;i<L;i++) p[i]=q[i]=0;
    for(int i=0;i<N;i++) p[i]=f[i];
    for(int i=0;i<M;i++) q[i]=g[i];
    //拷贝一份进行变换
    NTT(p,1);
    NTT(q,1);
    for(int i=0;i<L;i++) h[i]=1ll*p[i]*q[i]%MOD;
    NTT(h,0);
    if(mod>=0) for(int i=mod;i<L;i++) h[i]=0;
}
inline void inv(int f[MAXN],int g[MAXN],int mod){
    static int p[MAXN];
    if(mod==1){
        g[0]=inv(f[0]);
        return ;//递归边界
    }
    inv(f,g,mod+1>>1);
    for(int i=0;i<mod;i++) p[i]=0;
    mul(f,g,p,mod,mod,mod);
    for(int i=0;i<mod;i++) p[i]=dis(0,p[i]);
    p[0]=add(p[0],2);
    mul(g,p,g,mod,mod,mod);
}
inline void sqrt(int f[MAXN],int g[MAXN],int mod){
    static int p[MAXN];
    if(mod==1){
        g[0]=1;//常数项直接确定，一定是 1
        return ;
    }
    sqrt(f,g,mod+1>>1);
    for(int i=0;i<mod;i++) p[i]=0;
    inv(g,p,mod);
    mul(f,p,p,mod,mod,mod);
    for(int i=0;i<mod;i++) g[i]=1ll*InV[2]*(g[i]+p[i])%MOD;
}
int F[MAXN],G[MAXN],N,M;
inline void work(){
    pre();
    static int p[MAXN],q[MAXN];
    ++M;
    for(int i=0;i<M;i++) p[i]=q[i]=0;
    for(int i=0;i<M;i++) p[i]=dis(0,4ll*G[i]%MOD);
    p[0]=add(p[0],1);
    sqrt(p,q,M);
    q[0]=add(q[0],1);
    inv(q,F,M);
    for(int i=0;i<M;i++) F[i]=add(F[i],F[i]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>M;
    for(int i=1,c;i<=N;i++) cin>>c,G[c]=1;
    work();
    for(int i=1;i<M;i++) cout<<F[i]<<'\n';
    cout.flush();
    return 0;
}
```

最后安利一下 [本蒟蒻的博客](https://www.luogu.com.cn/blog/JustinRochester/)

---

## 作者：Jμdge (赞：2)


推推式子套套板子就过去了？

这题套路就是 NTT 优化 dp 转移

于是我们先列 dp 转移:

这里令  $d_i$ 表示 S 中是否出现了元素 $i$ ，$f_i$ 表示树权值为 $i$ 的答案

$$f_n=\left\{\begin{aligned}1~~~~~~~~~~~~~~~~~~~~~~~ &&& n=0 \\ \sum_{i=1}^n d_i \sum_{j=0}^{n-i} f_j·f_{n-i-j} &&& n>0\\ \end{aligned} \right. $$


那么我们发现后边的 两个 f 相乘很像卷积的形式，原式也就可以变成这样


$$f_n=\sum_{i=1}^n d_i· f*f(n-i)$$

然后把前面的 $d_i$ 也卷进去：

$$f=1+d*f*f$$

然后我们成功地把这道 dp 转化为了多项式求解...

我们现在推式子：

$$cf^2-f+1=0$$

把式子中的 f、c 看做已经点值转化，然后套套求根公式：

$$f={1±\sqrt{1-4c}\over 2c}$$

这里上下乘个 $1±\sqrt{1-4c}$：

$$f={2\over 1±\sqrt{1-4c}}$$

然后我们看着这里不知道取加号还是减号，那么假设 S 中没有元素，要求 $f_0$

那么 $c_0=0,f_0=1$

带入发现这里取正号是对的，于是我们就取正号吧（后面要证的话就归纳法？反正我不会）

$$f={2\over 1+\sqrt{1-4c}}$$


然后多项式求逆和多项式开根的板子搬过来就好了


```cpp
//by Judge
#include<cstdio>
#include<iostream>
#define ll long long
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
using namespace std;
const int mod=998244353;
const int invG=332748118;
const int M=8e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int Inc(int x,int y){return (x+y)%mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int CC=-1,Z;
inline void Ot(){fwrite(sr,1,CC+1,stdout),CC=-1;}
inline void print(int x,char chr='\n'){
    if(CC>1<<20)Ot();if(x<0)sr[++CC]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++CC]=z[Z],--Z);sr[++CC]=chr;
} int n,m,inv2; arr r,a,b,c,d,C,D,F;
inline int qpow(int x,int p=mod-2){ int s=1;
	for(;p;p>>=1,x=Mul(x,x))
		if(p&1) s=Mul(s,x); return s;
}
inline void get_rev(int limit,int len){
	for(int i=0;i<limit;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<len-1);
}
inline void NTT(int* a,int n,int tp){
	for(int i=0;i<n;++i)
		if(i<r[i]) swap(a[i],a[r[i]]);
	for(int mid=1;mid<n;mid<<=1){
		int Gn=qpow(tp?3:invG,(mod-1)/(mid<<1));
		for(int j=0,x,y;j<n;j+=mid<<1)
			for(int k=0,g=1;k<mid;++k,g=Mul(g,Gn))
				x=a[j+k],y=Mul(g,a[j+k+mid]),
				a[j+k]=Inc(x,y),a[j+k+mid]=Inc(x,mod-y);
	} if(tp) return ; int inv=qpow(n);
	for(int i=0;i<n;++i) a[i]=Mul(a[i],inv);
}
void get_inv(int* a,int* b,int n){
	if(n==1) return b[0]=qpow(a[0]),void();
	get_inv(a,b,n+1>>1); int limit=1,len=0;
	for(;limit<n<<1;limit<<=1) ++len;
	get_rev(limit,len);
	for(int i=0;i<n;++i) C[i]=a[i];
	for(int i=n;i<=limit;++i) C[i]=0;
	NTT(C,limit,1),NTT(b,limit,1);
	for(int i=0;i<limit;++i)
		b[i]=Mul(Inc(2,mod-Mul(C[i],b[i])),b[i]);
	NTT(b,limit,0);
	for(int i=n;i<limit;++i) b[i]=0;
}
void get_sqrt(int* a,int* b,int n){ b[0]=1;
	if(n==1) return b[0]=1,void();
	get_sqrt(a,b,n+1>>1);
	for(int i=0;i<=n<<1;++i) F[i]=0;
	get_inv(b,F,n); int limit=1,len=0;
	for(;limit<n<<1;limit<<=1)++len;
	get_rev(limit,len);
	for(int i=0;i<n;++i) D[i]=a[i];
	for(int i=n;i<limit;++i) D[i]=0;
	NTT(D,limit,1),NTT(b,limit,1),NTT(F,limit,1);
	for(int i=0;i<limit;++i)
		b[i]=Mul(Inc(b[i],Mul(D[i],F[i])),inv2);
	NTT(b,limit,0);
	for(int i=n;i<limit;++i) b[i]=0;
}
///////////////上面都是板子////////////////
int main(){ n=read(),m=read(),inv2=qpow(2);
	int x; fp(i,1,n) x=read(),++d[x];
	int len; for(len=1;len<=m;len<<=1);
	fp(i,1,len-1) d[i]=(-4*d[i]+mod)%mod;
	++d[0],get_sqrt(d,c,len);
	fp(i,0,len-1) d[i]=0;
	c[0]=Inc(c[0],1),get_inv(c,d,len);
	fp(i,0,m) d[i]=Inc(d[i],d[i]);
	fp(i,1,m) print(d[i]);
	return Ot(),0;
}
```









---

## 作者：Terac (赞：0)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF438E)

## 题意

给定集合 $S=\{c_1,c_2,\cdots c_n\}$，求 $\forall{i\in\left[1,m\right]\cap\mathbb{N}}$，点权在给定 $S$ 内且点权和为 $i$ 的二叉树个数。  

数据范围：$1\le n,m \le 10^5,1\le c_i\le10^5$  

## 题解  

令 $f_i$ 表示点权和为 $i$ 时的答案，$g_i=\left[i\in S\right]$。

有 DP 转移方程
$$f_n=\begin{cases}1,n=0\\\sum\limits_{i=1}^n g_i\sum\limits_{j=0}^{n-i}f_jf_{n-i-j},n>0\end{cases}$$  

可以理解为先枚举根节点的权值，再枚举左右子树的权值。  

发现后半部分实质上是三个多项式卷起来后的系数，于是令 $F(x)$ 表示 $f$ 的生成函数，$G(x)$ 表示 $g$ 的生成函数。  

可得
$$F(x)=1+G(x)F^2(x)$$
$$\Rightarrow G(x)F^2(x)-F(x)+1=0$$

由一元二次求根公式得 

$$F(x)=\frac{-b\pm \sqrt{b^2-4ac}}{2a}=\frac{1\pm\sqrt{1-4G(x)}}{2G(x)}$$

发现有两个根，继续化简原式得
$$2F(x)G(x)=1\pm\sqrt{1+4G(x)}$$
当 $2F(x)G(x)=1+\sqrt{1+4G(x)}$ 时
$$\because g_0=0$$
$$\therefore \left[x^0\right]G(x)=0$$
$$\therefore \left[x^0\right]2F(x)G(x)=0$$
又 
$$\left[x^0\right]1+\sqrt{1-4G(x)}\ge1$$
$$\therefore 2F(x)G(x)\ne1+\sqrt{1-4G(x)}$$
故
$$2F(x)G(x)=1-\sqrt{1-4G(x)}$$
$$F(x)=\frac{1-\sqrt{1-4G(x)}}{2G(x)}$$
$\left[x^0\right]G(x)=0$，无法求逆，考虑改变分子分母的形式。  

分子分母同乘共轭根式 $1+\sqrt{1-4G(x)}$

$$F(x)=\frac{1-(1-4G(x))}{2G(x)(1+\sqrt{1-4G(x)})}$$
$$F(x)=\frac{4G(x)}{2G(x)+2G(x)\sqrt{1-4G(x)}}$$
$$F(x)=\frac{2}{1+\sqrt{1-4G(x)}}$$
至此可以用多项式开根和多项式求逆求 $F(x)$。  

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
	//read and write
} using namespace IO;
const int N = 2.7e5 + 10;
namespace Polynomial {
	const int P = 998244353, G = 3, Gi = 332748118, inv2 = 499122177;
	int lim, rev[N], a[N], b[N];
	int qpow(int n, int k) {
		int res = 1;
		for(; k; n = 1ll * n * n % P, k >>= 1)
			if(k & 1) res = 1ll * res * n % P;
		return res;
	}
	void NTT(int *f, int T) {
		for(int i = 0; i < lim; i++)
			if(i < rev[i]) 
				swap(f[i], f[rev[i]]);
		for(int mid = 1; mid < lim; mid <<= 1) {
			int wn = qpow(T == 1 ? G : Gi, (P - 1) / (mid << 1));
			int len = mid << 1;
			for(int i = 0; i < lim; i += (mid << 1)) {
				int w = 1;
				for(int j = 0; j < mid; j++, w = 1ll * w * wn % P) {
					int x = f[i + j], y = 1ll * w * f[i + j + mid] % P;
					f[i + j] = (x + y) % P;
					f[i + j + mid] = (x - y + P) % P;
				}
			}
		}
		if(T == -1) {
			int inv = qpow(lim, P - 2);
			for(int i = 0; i < lim; i++) 
				f[i] = 1ll * f[i] * inv % P;
		}
	}
	void init(int n) {
		for(lim = 1; lim < n; lim <<= 1);
		for(int i = 0; i < lim; i++)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
	} 
	void mul(int *f, int *g, int *h, int n, int m) {
		static int a[N], b[N];
		init(n + m - 1);
		memset(a, 0, lim << 2);
		memcpy(a, f, n << 2);
		memset(b, 0, lim << 2);
		memcpy(b, g, m << 2);
		NTT(a, 1), NTT(b, 1);
		for(int i = 0; i < lim; i++) 
			h[i] = 1ll * a[i] * b[i] % P;
		NTT(h, -1);
	}
	void inv(int *f, int *g, int n) {
		if(n == 1) { g[0] = qpow(f[0], P - 2); return; }
		inv(f, g, n + 1 >> 1);
		init(n << 1);
		copy(f, f + n, a);
		fill(a + n, a + lim, 0);
		NTT(a, 1), NTT(g, 1);
		for(int i = 0; i < lim; i++)
			g[i] = (2 - 1ll * a[i] * g[i] % P + P) % P * g[i] % P;
		NTT(g, -1);
		fill(g + n, g + lim, 0);
	}
	void sqrt(int *f, int *g, int n) {
		if(n == 1) { g[0] = 1; return; }
		sqrt(f, g, n + 1 >> 1);
		memset(b, 0, n << 2);
		inv(g, b, n);
		mul(f, b, b, n, n);
		for(int i = 0; i < n; i++)
			g[i] = 1ll * (g[i] + b[i]) * inv2 % P;
	}
}
using namespace Polynomial;
int n, m, maxn, f[N], g[N], h[N];
int main() {
	n = read(), m = read() + 1;
	f[0] = 1;
	for(int i = 1, x; i <= n; i++)
		x = read(), g[x] = 1, maxn = max(maxn, x);
	for(int i = 1; i <= maxn; i++)
		if(g[i]) g[i] = P - 4 * g[i];
	g[0]++;
	sqrt(g, h, m);
	h[0]++;
	inv(h, f, m);
	for(int i = 1; i < m; i++)
		write(2 * f[i] % P), putc('\n');
	flush();
	return 0;
}
```


---

## 作者：蒟蒻丁 (赞：0)

[更加~酷~炫~的体验](https://www.cnblogs.com/caijiLYC/p/14477037.html)  
新手表示满脑子只有 DP …… 
设一个数组 $s$，值只有 $0/1$ 第 $i$ 位表示 $i$ 这个数字是否合法。  
首先找到 dp 方程： $f_n=\sum{s_i\sum{f_{n-j-i}f_{j}}}$。  
同时知道 $f_0=1$。  
~~嗯，看起来很好吃。~~ 
然后我们设 $f$ 的生成函数为 $F(x)=\sum{f_ix^i}$。   
设 $s$ 的生成函数是 $G(x)=\sum{s_ix^i}$。    
我们规定常数项为 $0$ ,因为原题中给定的合法数大于 $0$ ($\forall i,s_i>0$)
那么每一项就是：    
$$F_i=\sum\limits_{j=1}^{j \leq i}{s_j\sum\limits_{k=0}^{k \leq i-j}{F_{i-j-k} \cdot F_{k}}}$$  
$$F=1+G \cdot F^2$$  
然后考虑化简，题解有人对直接求根表示质疑，我觉得他的证明非常好，值得学习。
$$GF=F^2G^2+G$$  
$$0=F^2G^2-GF+G$$
$$0=(FG+\frac{1}{2})^2-\frac{1}{4}+G$$
$$\frac{1}{4}-G=(GF-\frac{1}{2})^2$$
$$1-4G=4(GF-\frac{1}{2})$$
然后因为左式的常数项不是 $0$ 了，我们可以开根。
$$-\sqrt[2]{1-4G}=2(GF-\frac{1}{2})$$
考虑到我们还有个 $GF$ ，这个小家伙的常数项必为 $0$ ($GF_0=G_0 \cdot F_0$)。  
如果我们选择了正，那么左式的常数项就不为 $0$ 所以我们必须得选择取负。
$$\frac{1-\sqrt[2]{1-4G}}{2}=GF$$
初一数学，上下同乘 $1+\sqrt[2]{1-4G}$ ，于是原式就被化简成了：
$$F=\frac{2}{1+\sqrt[2]{1-4G}}$$
~~是的是的我跳步了~~不过这步不难。  
然后让我们冲！  
(代码一如既往地加了些许常数优化啊~。)
```c++11
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const ll mod=998244353,g=3,N=8e5+10,inv2=499122177;
ll aa[N],bb[N],ans[N];

static inline ll ksm(ll x,ll k,ll tmp=1){
	while(k){
		if(k&1)tmp=tmp*x%mod;
		x=x*x%mod,k>>=1;
	}
	return tmp;
}

namespace NTT{
	ll rev[N];
	static inline ll pre(ll n,ll m,ll l=0){
		while((1<<l)<=n+m)l++;
		for(ll i=0;i<(1<<l);i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return l;
	}
	inline void Ntt(ll *f,ll inv,ll li){
		for(ll i=0;i<li;i++)if(i<rev[i])swap(f[i],f[rev[i]]);
		for(ll mid=1;mid<li;mid<<=1){
			ll tmp=ksm(g,(mod-1)/(mid*2));
			ll tp=mid<<1;
			if(inv==-1)tmp=ksm(tmp,mod-2);
			for(ll i=0;i<li;i+=tp){
				ll w=1;
				for(register ll x,y,j=0;j<mid;j++,w=w*tmp%mod){
					x=f[i+j],y=f[i+j+mid]*w%mod;
					f[i+j]=(x+y)%mod,f[i+j+mid]=(x-y+mod)%mod;
				}
			}
		}
		if(inv==-1){
			ll t=ksm(li,mod-2);
			for(ll i=0;i<li;i++)f[i]=f[i]*t%mod;
		}
	}
}

namespace Ln{
	inline void Inv(ll *s,ll *f,ll n){
		ll A[N],B[N],S[N];
		memset(S,0,sizeof(S));
		S[0]=ksm(f[0],mod-2);
		for(ll len=2;len<=(n<<1);len<<=1){
			ll li=len<<1,l=0;
			for(ll i=0;i<len;i++)A[i]=f[i],B[i]=S[i];
			for(ll i=len;i<li;i++)A[i]=B[i]=0;
			memset(NTT::rev,0,sizeof(NTT::rev));
			l=NTT::pre(len,0);
			NTT::Ntt(A,1,li);
			NTT::Ntt(B,1,li);
			for(ll i=0;i<li;i++){
				S[i]=(2*B[i]+mod-A[i]*B[i]%mod*B[i]%mod)%mod;
			}
			NTT::Ntt(S,-1,li);
			for(ll i=len;i<li;i++)S[i]=0;
		}
		for(ll i=0;i<=n;i++)s[i]=S[i];
	}
	inline void Sqrt(ll *s,ll *f,ll n){
		ll A[N],B[N],C[N],S[N];
		memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));
		memset(S,0,sizeof(S));
		S[0]=1;
		for(ll len=1;len<=(n<<1);len<<=1){
			ll li=len<<1,ui;
			for(ll i=0;i<li;i++)A[i]=B[i]=C[i]=0;
			for(ll i=0;i<len;i++)A[i]=f[i],B[i]=S[i];
			Inv(C,B,len);
			ui=NTT::pre(len,0);
			NTT::Ntt(A,1,li);
			NTT::Ntt(C,1,li);
			for(ll i=0;i<li;i++)S[i]=A[i]*C[i]%mod;
			NTT::Ntt(S,-1,li);
			for(ll i=0;i<li;i++)S[i]=(S[i]+B[i])%mod*inv2%mod;
			for(ll i=len;i<li;i++)S[i]=0;
		}
		for(ll i=0;i<=n;i++)s[i]=S[i];
	}
}

int main(){
	ll n,m;
	cin>>n>>m,n--;
	for(ll a1,i=0;i<=n;i++){
		scanf("%lld",&a1),aa[a1]++;
	}
	bb[0]=1;
	for(ll i=1;i<=m;i++)bb[i]-=4*aa[i];
	Ln::Sqrt(bb,bb,m),bb[0]++;
	Ln::Inv(ans,bb,m);
	for(ll i=1;i<=m;i++)ans[i]=ans[i]*2%mod;
	for(ll i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
```

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF438E)看题目。  
# 分析  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设集合$S=\{c_i|1\le i\le n\}$。设$c(i)=[i\in S]$。于是可以设计如下的$DP$：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i)$：树的权重和为$i$的方案数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移为： 
$$f(n)=\sum_{i=1}^mc(i)\sum_{j=1}^{n-i}f(j)f(n-i-j)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难发现这是“卷积套卷积”的形式。因此，我们考虑引入生成函数来简化运算。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设两个生成函数$C(x)$和$F(x)$：  
$$C(x)=\sum_{i=0}^{+\infty}c(i)x^i$$  
$$F(x)=\sum_{i=0}^{+\infty}f(i)x_i$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;则转移可以被描述为： 
$$F(x)=C(x)F^2(x)+1$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中$C(x)F^2(x)$描述的是卷积转移。加$1$是因为卷积后常数项为$0$，但是空树有$1$种方案，所以要补上。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;整理得到： 
$$C(x)F^2(x)-F(x)+1=0$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;运用二次求根公式： 
$$F(x)=\frac{1\pm \sqrt{1-4C(x)}}{2C(x)}$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此时有两个根，但是我们只能选一个。将$x=0$代入这个式子后，如果取正号，就会出现$\frac 2 0$的尴尬情况。如果取负号，那么使用洛必达法则可以得到结果为$1$。所以选负号。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~实在是解释不来了......~~ 可以参考 Catalan 数的生成函数推导。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后发现由于$C(x)$没有常数项，不能求逆，因此我们乘上一个共轭式进行分子有理化： 
$$F(x)=\frac 2{1+\sqrt{1-4C(x)}}$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后套上多项式开根和多项式求逆计算即可。时间是$O(n\log_2n)$。  
# 代码
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>

const int mod = 998244353, phi = mod - 1, g = 3, inv2 = 499122177;
const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
void swapp( _T &x, _T &y )
{
	_T t = x; x = y, y = t;
}

int A[MAXN << 2], H_[MAXN << 2], C1[MAXN << 2], C2[MAXN << 2];
int a[MAXN];
int N, M;

int qkpow( int base, int indx )
{
	int ret = 1;
	while( indx )
	{
		if( indx & 1 ) ret = 1ll * ret * base % mod;
		base = 1ll * base * base % mod, indx >>= 1;
	}
	return ret;
}

int inv( const int a ) { return qkpow( a, mod - 2 ); }
int fix( const int a ) { return ( a % mod + mod ) % mod; }

void NTT( int *coe, const int len, const int t )
{
	int lg2 = log2( len );
	for( int i = 0, rev ; i < len ; i ++ )
	{
		rev = 0;
		for( int j = 0 ; j < lg2 ; j ++ ) rev |= ( ( i >> j ) & 1 ) << ( lg2 - j - 1 );
		if( rev < i ) swapp( coe[rev], coe[i] );
	}
	int wp, wo, we;
	for( int s = 2, p ; s <= len ; s <<= 1 )
	{
		p = s >> 1; wp = t > 0 ? qkpow( g, phi / s ) : inv( qkpow( g, phi / s ) );
		for( int i = 0 ; i < len ; i += s )
			for( int j = 0, w = 1 ; j < p ; j ++, w = 1ll * w * wp % mod )
			{
				we = coe[i + j], wo = 1ll * coe[i + j + p] * w % mod;
				coe[i + j] = ( we + wo ) % mod, coe[i + j + p] = fix( we - wo );
			}
	}
	if( t > 0 ) return ;
	int inver = inv( len );
	for( int i = 0 ; i <= len ; i ++ ) coe[i] = 1ll * coe[i] * inver % mod;
}

void polyInv( const int n, int *F, int *H )
{
	if( n == 1 ) { H[0] = inv( F[0] ); return ; }
	int half = n + 1 >> 1, len = 1;
	polyInv( half, F, H );
	while( len < ( n << 1 ) ) len <<= 1;
	for( int i = 0 ; i < n ; i ++ ) A[i] = F[i];
	for( int i = n ; i <= len ; i ++ ) H[i] = A[i] = 0;
	NTT( A, len, 1 ), NTT( H, len, 1 );
	for( int i = 0 ; i <= len ; i ++ ) H[i] = 1ll * H[i] * fix( 2 - 1ll * A[i] * H[i] % mod ) % mod; 
	NTT( H, len, -1 );
	for( int i = n ; i <= len ; i ++ ) H[i] = 0;
}

void polySqrt( const int n, int *F, int *H )
{
	if( n == 1 ) { H[0] = 1; return ; }
	int half = n + 1 >> 1, len = 1;
	polySqrt( half, F, H );
	while( len < ( n << 1 ) ) len <<= 1;
	polyInv( n, H, H_ );
	for( int i = 0 ; i < n ; i ++ ) A[i] = F[i];
	for( int i = n ; i <= len ;            i ++ ) A[i] = 0;
	NTT( A, len, 1 ), NTT( H_, len, 1 );
	for( int i = 0 ; i <= len ; i ++ ) A[i] = 1ll * A[i] * H_[i] % mod;
	NTT( A, len, -1 );
	for( int i = 0 ; i < n ; i ++ ) H[i] = 1ll * ( H[i] + A[i] ) % mod * inv2 % mod;
	for( int i = n ; i <= len ; i ++ ) H[i] = 0;
}

int main()
{
	read( N ), read( M );
	for( int i = 1, v ; i <= N ; i ++ ) read( v ), a[v] = 1;
	for( int i = 0 ; i <= M ; i ++ ) C1[i] = 1ll * ( mod - 4 ) * a[i] % mod;
	C1[0] = ( C1[0] + 1 ) % mod;
	polySqrt( M + 1, C1, C2 );
	C2[0] = ( C2[0] + 1 ) % mod;
	memset( C1, 0, sizeof C1 );
	polyInv( M + 1, C2, C1 );
	for( int i = 1 ; i <= M ; i ++ ) write( 2ll * C1[i] % mod ), putchar( '\n' );
	return 0;
}
```

---

## 作者：VenusM1nT (赞：0)

$\textbf{DP}$ + 生成函数 + $\textbf{NTT}$.  
~~因为数组开小查了一年~~  
首先考虑 $\textbf{DP}$，令 $s_i=[\exists c_k=i]$，也就是 $i$ 有没有出现过，然后令 $f_i$ 表示权值为 $i$ 的“神犇二叉树”有多少种，那么可以通过枚举根的权值和左子树的大小得出一个式子：
$$f_i=\sum_{k=0}^is_k\sum_{j=0}^{i-k}f_j\times f_{i-j-k}$$
其中 $f_0=1$.  
那么这个式子可以看做是三个式子的卷积，卷积不好处理，考虑将其转化为多项式乘法，令
$$S(x)=\sum_{i=0}^\infty s_i\times x^i,F(x)=\sum_{i=0}^\infty f_i\times x^i$$
即让 $S(x)$ 为 $s_i$ 的生成函数，$F(x)$ 为 $f_i$ 的生成函数，那么原式可以化作：
$$F(x)=S(x)\times F(x)^2+1$$
此处 $+1$ 是因为要考虑 $f_0=1$ 的情况，对应的答案就是 $F(x)$ 对应项的系数。现在的问题就是如何处理这个式子，$S(x)$ 已知，考虑一元二次方程的通解，则可以得到
$$F(x)=\frac{1\pm \sqrt{1-4\times S(x)}}{2\times S(x)}$$
现在的问题就转化为到底是取加号还是减号，对此可以分类讨论：

  1. 取加号

已知
$$\lim_{x\to 0}\frac{1+ \sqrt{1-4\times S(x)}}{2\times S(x)}=f_0=1$$
因为
$$\lim_{x\to 0} S(x)=0$$
所以上式可以化为
$$\lim_{x\to 0}\frac{1+ \sqrt{1-4\times S(x)}}{2\times S(x)}=\lim_{x\to 0}\frac{1+ \sqrt{1-4\times x}}{2\times x}=\infty\neq1$$
舍去。  

  2. 取减号

同上：
$$\lim_{x\to 0}\frac{1- \sqrt{1-4\times S(x)}}{2\times S(x)}=\lim_{x\to 0}\frac{1- \sqrt{1-4\times x}}{2\times x}$$
发现 $x\to 0$ 时上下都趋近于 $0$，属于 $0\over 0$ 式极限，考虑洛必达法则。对分子求导得：
$$\frac{d(1-\sqrt{1-4\times x})}{dx}=\frac{d(1-\sqrt{1-4\times x})}{d(1-4\times x)}\times \frac{d(1-4\times x)}{dx}=\frac{1}{2\times \sqrt{1-4\times x}}\times 4=\frac{2}{\sqrt{1-4\times x}}$$
对分母求导得：
$$(2x)'=2$$
则原式可以化作：
$$\frac{\lim_{x\to 0}\frac{2}{\sqrt{1-4\times x}}}{\lim_{x\to 0}2}=\frac22=1$$
符合要求，所以取减号，但
$$F(x)=\frac{1- \sqrt{1-4\times S(x)}}{2\times S(x)}$$
并不方便求出，考虑分子有理化，上下同乘 $1-\sqrt{1-4\times S(x)}$，就可以得到：
$$F(x)=\frac{2}{1-\sqrt{1-4\times S(x)}}$$
然后只需要做一遍多项式开根、一遍多项式求逆即可完成。  
（注释掉的是自己写的常数巨大的开根，由于太不优美换了一个优美的写法qwq）  
（这种题赛场上真的有人写得出来吗……出题人也太屑了吧）
```cpp
#include<bits/stdc++.h>
#define MAXN 1000005
#define reg register
#define inl inline
#define int long long
using namespace std;
const int Mod=998244353,Gi=3;
int n,m,c[MAXN],B[MAXN],C[MAXN],D[MAXN],s[MAXN],f[MAXN],g[MAXN],lim=1,maxn,rev[MAXN];
inl int Pow(reg int x,reg int y)
{
	reg int res=1;
	for(;y;y>>=1,x=x*x%Mod) if(y&1) res=res*x%Mod;
	return res;
}
const int inv2=Pow(2,Mod-2);
template <typename T> inl void Read(reg T &x)
{
	x=0;
	reg int fu=1;
	reg char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
	for(;isdigit(ch);ch=getchar()) x=x*10+(ch-48);
	x*=fu;
}
inl void NTT(reg int *A,reg int opt)// A
{
	for(reg int i=0;i<lim;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
	for(reg int mid=1;mid<lim;mid<<=1)
	{
		reg int Wn=Pow(Gi,(Mod-1)/(mid<<1));
		for(reg int j=0;j<lim;j+=(mid<<1))
		{
			reg int W=1;
			for(reg int k=0;k<mid;k++,W=W*Wn%Mod)
			{
				reg int x=A[j+k],y=W*A[j+k+mid]%Mod;
				A[j+k]=(x+y)%Mod;
				A[j+k+mid]=(x-y+Mod)%Mod;
			}
		}
	}
	if(opt==1) return;
	reverse(A+1,A+lim);
	reg int inv=Pow(lim,Mod-2);
	for(reg int i=0;i<lim;i++) A[i]=A[i]*inv%Mod;
}
void GetInv(reg int *F,reg int *G,reg int len)// C
{
	if(len==1) return G[0]=Pow(F[0],Mod-2),void();
	GetInv(F,G,(len+1)>>1);
	lim=1;
	maxn=0;
	while(lim<=(len<<1))
	{
		lim<<=1;
		maxn++;
	}
	for(reg int i=0;i<lim;i++) rev[i]=((rev[i>>1]>>1)|((i&1)<<(maxn-1)));
	for(reg int i=0;i<len;i++) C[i]=F[i];
	for(reg int i=len;i<lim;i++) C[i]=0;
	NTT(C,1); NTT(G,1);
	for(reg int i=0;i<lim;i++) G[i]=((2ll-G[i]*C[i]%Mod)+Mod)%Mod*G[i]%Mod;
	NTT(G,-1);
	for(reg int i=len;i<lim;i++) G[i]=0;
}
void GetSqrt(reg int *F,reg int *G,reg int len)// B D
{
	if(len==1) return G[0]=F[0],void();
	GetSqrt(F,G,(len+1)>>1);
	memset(B,0,sizeof(B));
	memset(D,0,sizeof(D));
	for(reg int i=0;i<len;i++) B[i]=F[i];
	GetInv(G,D,len);
	lim=1;
	maxn=0;
	while(lim<=(len<<1))
	{
		lim<<=1;
		maxn++;
	}
	for(reg int i=0;i<lim;i++) rev[i]=((rev[i>>1]>>1)|((i&1)<<(maxn-1)));
	NTT(B,1); NTT(D,1);
	for(reg int i=0;i<lim;i++) D[i]=B[i]*D[i]%Mod;
	NTT(D,-1);
	for(reg int i=0;i<len;i++) G[i]=(G[i]+D[i])*inv2%Mod;
}
/*inl void GetDev(reg int *F,reg int *G,reg int len)
{
	for(reg int i=1;i<len;i++) G[i-1]=F[i]*i%Mod;
	G[len-1]=0;
}
inl void GetInt(reg int *F,reg int *G,reg int len)
{
	for(reg int i=1;i<len;i++) G[i]=F[i-1]*Pow(i,Mod-2)%Mod;
	G[0]=0;
}
inl void GetLn(reg int *F,reg int *G,reg int len)// B D
{
	memset(B,0,sizeof(B));
	memset(D,0,sizeof(D));
	GetDev(F,B,len);
	GetInv(F,D,len);
	lim=1;
	maxn=0;
	while(lim<=(len<<1))
	{
		lim<<=1;
		maxn++;
	}
	for(reg int i=1;i<lim;i++) rev[i]=((rev[i>>1]>>1)|((i&1)<<(maxn-1)));
	NTT(B,1); NTT(D,1);
	for(reg int i=0;i<lim;i++) B[i]=B[i]*D[i]%Mod;
	NTT(B,-1);
	GetInt(B,G,len);
}
void GetExp(reg int *F,reg int *G,reg int len)// E H
{
	if(len==1) return G[0]=1,void();
	GetExp(F,G,(len+1)>>1);
	lim=1;
	maxn=0;
	while(lim<=(len<<1))
	{
		lim<<=1;
		maxn++;
	}
	for(reg int i=1;i<lim;i++) rev[i]=((rev[i>>1]>>1)|((i&1)<<(maxn-1)));
	memset(E,0,sizeof(E));
	memset(H,0,sizeof(H));
	GetLn(G,E,len);
	for(reg int i=0;i<len;i++) H[i]=F[i];
	NTT(G,1); NTT(E,1); NTT(H,1);
	for(reg int i=0;i<lim;i++) G[i]=(1ll-E[i]+H[i]+Mod)*G[i]%Mod;
	NTT(G,-1);
	for(reg int i=len;i<lim;i++) G[i]=0;
}
void GetSqrt(reg int *F,reg int len)// I J
{
	GetLn(F,I,len);
	reg int inv=Pow(2,Mod-2);
	for(reg int i=0;i<len;i++) I[i]=I[i]*inv%Mod;
	GetExp(I,J,len);
	for(reg int i=0;i<len;i++) F[i]=J[i];
}*/
signed main()
{
	Read(n);
	Read(m);
	for(reg int i=1;i<=n;i++)
	{
		reg int x;
		Read(x);
		s[x]++;
	}
	reg int len=1;
	while(len<=m) len<<=1;
	for(reg int i=1;i<len;i++) s[i]=(Mod-4*s[i])%Mod;
	s[0]++;
	GetSqrt(s,g,len);
	g[0]=(g[0]+1)%Mod;
	GetInv(g,f,len);
	for(reg int i=1;i<=m;i++) printf("%lld\n",f[i]*2%Mod);
	return 0;
}
```

---

## 作者：Genius_Z (赞：0)

## CF438E The Child and Binary Tree

先考虑$dp$的做法，我们枚举根节点的权值，设$f_k$为权值为$k$的满足条件的二叉树的个数，$g_i$为$[i\in c]$ ，很容易可以得到$dp$方程：$f_k=\sum\limits_{i=1}^m g_i\sum\limits_{j=0}^{k-c[i]}f_jf_{k-c[i]-j}+[k=0]$

直接做肯定是会$T$的，考虑用生成函数优化，记$F=\sum\limits_{i=1}^\infty f_i$，$G=\sum\limits_{i=1}^{\infty}g_i$

原式可化为$F=G*F^2+1$

用求根公式可得$F=\dfrac{1\pm\sqrt{1-4G}}{2G}$，当$F=\dfrac{1+\sqrt{1-4G}}{2G}$时，$F=\frac{1+1}{0}=\inf$，舍去，当$F=\dfrac{1-\sqrt{1-4G}}{2G}$时，$F=\frac{0}{0}=1$，所以分式上下同乘以$1+\sqrt{1-4G}$得$\dfrac{2}{1+\sqrt{1-4G}}$

之后开根加求逆即可。

$\large Code:$

```cpp
const int p = 998244353, G = 3, iG = 332748118, N = 1.6e6, k = 499122177;
int rev[N], a[N], ans[N];
inl int qpow(int x, int y) {
	re ans = 1, base = x;
	for (; y; y >>= 1, base = 1ll * base * base % p) {
		if (y & 1) ans = 1ll * ans * base % p;
	}
	return ans;
}
inl void NTT(int *a, int lim, int op = 1) {
	for (re i = 1; i < lim; i++)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (re mid = 1, r = 2; mid < lim; mid <<= 1, r <<= 1) {
		re g = qpow(op == 1 ? G : iG, (p - 1) / r);
		for (re j = 0; j < lim; j += r) {
			for (re k = 0, gn = 1, x, y; k < mid; k++, gn = 1ll * g * gn % p) {
				x = a[j + k], y = 1ll * a[j + k + mid] * gn % p;
				a[j + k] = (x + y) % p, a[j + k + mid] = (x - y + p) % p;
			}
		}
	}
	if (op != 1) {
		re inv = qpow(lim, p - 2);
		for (re i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv % p;
	}
}
inl int getlim(int n) {
	re lim = 1, lg = -1;
	while (lim <= n) lim <<= 1, lg++;
	for (re i = 1; i < lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lg);
	return lim;
}
inl void getinv(int *f, int *g, int n) {
	if (n == 1) return (void)(g[0] = qpow(f[0], p - 2));
	getinv(f, g, n >> 1);
	re lim = getlim(n);
	for (re i = 0; i < n; i++) a[i] = f[i];
	for (re i = n; i < lim; i++) a[i] = 0;
	NTT(a, lim), NTT(g, lim);
	for (re i = 0; i < lim; i++) g[i] = (2ll - 1ll * a[i] * g[i] % p + p) % p * g[i] % p;
	NTT(g, lim, -1);
	for (re i = n; i < lim; i++) g[i] = 0;
}
inl void der(int *a, int *b, int n) {
	for (re i = 1; i < n; i++) b[i - 1] = 1ll * i * a[i] % p;
	b[n - 1] = 0;
}
inl void inter(int *a, int *b, int n) {
	for (re i = 1; i < n; i++) b[i] = 1ll * a[i - 1] * qpow(i, p - 2) % p;
	b[0] = 0;
}
int f[N], g[N], b[N], c[N], d[N], e[N], h[N];
inl void getln(int *f, int *g, int n) {
	getinv(f, b, n), der(f, c, n);
	re lim = getlim(n);
	for (re i = n; i < lim; i++) b[i] = c[i] = 0;
	NTT(b, lim), NTT(c, lim);
	for (re i = 0; i < lim; i++) b[i] = 1ll * b[i] * c[i] % p;
	NTT(b, lim, -1);
	inter(b, g, n);
	for (re i = n; i < lim; i++) g[i] = 0;
	for (re i = 0; i < lim; i++) b[i] = c[i] = 0;
}
inl void getexp(int *f, int *g, int n) {
	if (n == 1) return (void)(g[0] = 1);
	getexp(f, g, n >> 1), getln(g, d, n);
	for (re i = 0; i < n; i++) e[i] = f[i];
	re lim = getlim(n);
	NTT(e, lim), NTT(d, lim), NTT(g, lim);
	for (re i = 0; i < lim; i++) g[i] = 1ll * g[i] * (1ll - d[i] + e[i] + p) % p;
	NTT(g, lim, -1);
	for (re i = n; i < lim; i++) g[i] = 0;
	for (re i = 0; i < lim; i++) e[i] = 0, d[i] = 0;
}
signed main() {
	re n = read<int>(), m = 1, q = read<int>();
	for (re i = 1, x; i <= n; i++) f[read<int>()] = p - 4;
	for (; m < q; m <<= 1) {};
	f[0]++, m <<= 1;
	getln(f, h, m);
	for (re i = 0; i < (q << 1); i++) h[i] = (1ll * h[i] * k) % p;
	for (re i = (q << 1); i < m; i++) h[i] = 0;
	getexp(h, g, m);
	g[0]++;
	getinv(g, ans, m);
	for (re i = 1; i <= q; i++) writeln((ans[i] * 2 % p + p) % p);
} 
```



---

