# Ladies' Shop

## 题目描述

A ladies' shop has recently opened in the city of Ultima Thule. To get ready for the opening, the shop bought $ n $ bags. Each bag is characterised by the total weight $ a_{i} $ of the items you can put there. The weird thing is, you cannot use these bags to put a set of items with the total weight strictly less than $ a_{i} $ . However the weights of the items that will be sold in the shop haven't yet been defined. That's what you should determine right now.

Your task is to find the set of the items' weights $ p_{1},p_{2},...,p_{k} $ $ (1<=p_{1}<p_{2}<...<p_{k}) $ , such that:

1. Any bag will be used. That is, for any $ i $ $ (1<=i<=n) $ there will be such set of items that their total weight will equal $ a_{i} $ . We assume that there is the infinite number of items of any weight. You can put multiple items of the same weight in one bag.
2. For any set of items that have total weight less than or equal to $ m $ , there is a bag into which you can put this set. Similarly, a set of items can contain multiple items of the same weight.
3. Of all sets of the items' weights that satisfy points 1 and 2, find the set with the minimum number of weights. In other words, value $ k $ should be as small as possible.

Find and print the required set.

## 样例 #1

### 输入

```
6 10
5 6 7 8 9 10
```

### 输出

```
YES
5
5 6 7 8 9 
```

## 样例 #2

### 输入

```
1 10
1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 10
6
```

### 输出

```
YES
1
6 
```

# 题解

## 作者：crashed (赞：7)

# 【 CF 286E 】Ladies' Shop
# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF286E)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;最简单的方法，贪心。由于小的数只有可能被更小的数凑出来，因此我们从小到大枚举数，如果发现当前的数没法被凑出来，就只能选入集合。如果最后发现有多余的数，就是无解。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用一个背包维护一下可以组成的数值。时间是$O(nm)$， T 了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这只是一个引子，跟正解没关系。~~水长度被打死~~    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;正紧一点。我们假设问题有解。则**在解中**，对于原序列每个数$s$，它可以被拆分成原序列中的$k$个数的和，即：     
$$s=\sum_{i=1}^k b_k$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们可以变化为：  
$$s=b_1 + \sum_{i=2}^k b_k$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据假设，$b_1$肯定是原序列里面的数；而题目要求告诉我们，$\sum_{i=2}^k b_k$一定是序列里面的数，否则这就不是个解。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;因此我们得到结论：原序列中的每个数**在解中**一定可以被拆成原序列中两个数的和。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如何确定哪些数可以被拆成原序列中两个数的和呢？我们考虑：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(x)$： $x$被拆成原序列两个数的方案数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这样我们只需要判定$f(x)$是否为正。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$S=\{a_i \}$, $f(x)$实际上就为：  
$$f(x)=\sum_{i=1}^{x-1} [i\in S][(x-i)\in S]$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由于$a_i> 0$，因此有：  
$$f(x)=\sum_{i=0}^{x} [i\in S][(x-i)\in S]$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;进一步的，我们设函数$A(x)=\sum_{i=0}^m[i\in S]x^i, F(x)=\sum_{i=0}^m f(i)x^i$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后发现：    
$$F(x)=A^2(x)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$FFT/NTT$解决。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此时再判断无解就很简单了。假如存在$x\not\in S, x\in[1,m]$，且$x$可以被分解为原序列的两个数的和，此时就是无解的情况。因为，如果我们选择不凑出其中一个数，那么就不符合题意，不算解；否则就一定会构造出$x$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;时间复杂度$O(m\log_2m)$。  
# 代码
```cpp
#include <cmath>
#include <cstdio>

const int mod = 998244353, G = 3, phi = mod - 1;
const int MAXN = 1e6 + 5, MAXM = 1e6 + 5;

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

int A[MAXM << 2];
int a[MAXN], bac[MAXM];
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
int fix( const int x ) { return ( x % mod + mod ) % mod; }

void NTT( int *coe, const int len, const int type )
{
	int lg2 = log2( len );
	for( int i = 0, rev ; i < len ; i ++ )
	{
		rev = 0; for( int j = 0 ; j < lg2 ; j ++ ) rev |= ( ( i >> j ) & 1 ) << ( lg2 - j - 1 );
		if( rev < i ) swapp( coe[rev], coe[i] );
	}
	int wp, we, wo;
	for( int s = 2, p ; s <= len ; s <<= 1 )
	{
		p = s >> 1, wp = type > 0 ? qkpow( 3, phi / s ) : inv( qkpow( 3, phi / s ) );
		for( int i = 0 ; i < len ; i += s )
			for( int j = 0, w = 1 ; j < p ; j ++, w = 1ll * w * wp % mod )
			{
				we = coe[i + j], wo = 1ll * coe[i + j + p] * w % mod;
				coe[i + j] = ( we + wo ) % mod, coe[i + j + p] = fix( we - wo );
			}
	}
	if( ~ type ) return ;
	int inver = inv( len );
	for( int i = 0 ; i <= len ; i ++ ) coe[i] = 1ll * coe[i] * inver % mod;
}

int main()
{
	read( N ), read( M );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i] ), A[a[i]] = 1, bac[a[i]] = 1;
	int len = 1, K = M << 1;
	while( len <= K ) len <<= 1;
	NTT( A, len, 1 );
	for( int i = 0 ; i <= len ; i ++ ) A[i] = 1ll * A[i] * A[i] % mod;
	NTT( A, len, -1 );
	for( int i = 1 ; i <= M ; i ++ ) if( ! bac[i] && A[i] ) { puts( "NO" ); return 0; }
	int tot = 0;
	for( int i = 1 ; i <= N ; i ++ )
		if( A[a[i]] == 0 )
			tot ++;
	puts( "YES" );
	write( tot ), putchar( '\n' );
	for( int i = 1 ; i <= N ; i ++ )
		if( A[a[i]] == 0 )
			write( a[i] ), putchar( ' ' );
	puts( "" );
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：4)

[portal to luogu](https://www.luogu.com.cn/problem/CF286E)

[portal to CF](http://codeforces.com/problemset/problem/286/E)

大神的题解十分严谨，严谨到我都看不懂的地步……只能自己研究题解了。

我们把题目中给出的两个限制命个名：

限制一：任何包的容量都要能被拼出

限制二：任何和$\leq m$的方案都必须是某个包的容量

首先，我们选数时，一定选的都是$\leq m$的数。因为大于$m$的数选了跟没选一样，既不能参与满足限制一（所有包的容量都$\leq m$），又不能采用满足限制二（与任何其它物品的容量和肯定都$>m$），因此对答案没有影响，不如不选。

其次，我们选数时，一定选的都是$A$集合内的数。不然，设某个$p_i\notin A$，则单独只选$p_i$肯定是一种合法的方案（$p_i\leq m$），但是$p_i \notin A$，故这种选择方案不合法，必定有$\forall p_i\in P,p_i\in A$。换句话说，$P\subseteq A$。

我们不妨思考一下，如果在一种$P\subseteq A$的选择方案里，存在$i,j,k$使得$p_i+p_j=p_k$会发生什么。我们可以在任何一种包含$p_k$的方案里，用$p_i+p_j$替换$p_k$。这样的话，如果$p_i,p_j,p_k$同时被选入$P$集合，且$P$集合是一种合法的解的话，剔除$p_k$只保留$p_i,p_j$一定也是一种合法的解。

这样，我们可以初始化令$P=A$。接下来，我们尝试在$P$中寻找这样的三元组$p_i,p_j,p_k$，并剔除$p_k$。

如果存在某个集合$t$使得$\sum\limits_{i=1}^tp_{t_i}=p_x$的情况，实际上$p_x$也可以被剔除。但是，因为$P$是一组合法的解，所以必有$\sum\limits_{i=1}^{t-1}p_{t_i}\in A$。设$\sum\limits_{i=1}^{t-1}p_{t_i}=p_y$，则有$p_{t_1}+p_y=p_x$，$p_x$仍然可以被表示成两个数的和。尽管，这个$p_y$也是一个可以被剔除的值。因此，在枚举三元组$p_i,p_j,p_k$时，$p_i$与$p_j$应该在所有的值里面枚举，不管它是否已经被剔除。

这样，我们可以很简单地设一个函数$f(x)=[x\in A]$。这样的话，我们设$g(x)=\sum\limits_{i+j=x}f(i)\times f(j)$，即$g=f^2$，则只有当$f(i)=f(j)=1$时，才有$f(i)\times f(j)=1$。这就意味着$i$和$j$可以拼出$x$，$x$可以被剔除。

但是，假如存在这样一个$x$，有$g(x)\geq 1$但$x\notin A$，这表明即使选择$A$中每一个元素，也无法构造出一种合法解，直接输出$\color{red}\colorbox{white}{NO}$。

如果对于所有$g(x)\geq 1$，都有$x\in A$，这意为着存在合法解。对于所有$x\in A$，如果$g(x)=0$，则意味着$x$不能被两个数的和表示出来，必须选它。

在求出$g$时，我们可以采取FFT直接求出。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
const int N=5e6;
int n,m,occ[N],lim=1,lg,rev[N],qwq[N],cnt;
struct cp{
	double x,y;
	cp(double u=0,double v=0){x=u,y=v;}
	friend cp operator +(const cp &u,const cp &v){return cp(u.x+v.x,u.y+v.y);}
	friend cp operator -(const cp &u,const cp &v){return cp(u.x-v.x,u.y-v.y);}
	friend cp operator *(const cp &u,const cp &v){return cp(u.x*v.x-u.y*v.y,u.x*v.y+u.y*v.x);}
}f[N];
void FFT(cp *a,int tp){
	for(int i=0;i<lim;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int md=1;md<lim;md<<=1){
		cp rt=cp(cos(pi/md),tp*sin(pi/md));
		for(int stp=md<<1,pos=0;pos<lim;pos+=stp){
			cp w=cp(1,0);
			for(int i=0;i<md;i++,w=w*rt){
				cp x=a[pos+i],y=w*a[pos+md+i];
				a[pos+i]=x+y;
				a[pos+md+i]=x-y;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	while(lim<m*2)lim<<=1,lg++;
	for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=0,x;i<n;i++)scanf("%d",&x),occ[x]=true;
	for(int i=1;i<=m;i++)f[i]=cp(occ[i],0);
	FFT(f,1);
	for(int i=0;i<lim;i++)f[i]=f[i]*f[i];
	FFT(f,-1);
	for(int i=0;i<lim;i++)qwq[i]=(int)(f[i].x/lim+0.5);
	for(int i=1;i<=m;i++){
		if(!qwq[i])continue;
		cnt++;
		if(!occ[i]){puts("NO");return 0;}
	}
	puts("YES");
	printf("%d\n",n-cnt);
	for(int i=1;i<=m;i++)if(occ[i]&&!qwq[i])printf("%d ",i);
	return 0;
}
```


---

## 作者：封禁用户 (赞：3)

[原博客地址](https://blog.csdn.net/qq_42101694/article/details/103632064)

# 题目
[传送门 to luogu](https://www.luogu.com.cn/problem/CF286E)

洛谷上根本交不起……建议直接去$\text{CF}$上提交。

[传送门 to CF](http://codeforces.com/problemset/problem/286/E)

__题目概要__

给定集合$A=\{a_1,a_2,a_3,\dots,a_n\}$和$m$，求一个集合$P=\{p_1,p_2,p_3,\dots,p_k\}$，满足这些条件：

- $$\forall\langle t_1,t_2,t_3,\dots,t_k\rangle\in\Bbb{N}^k,\sum_{i=1}^{k}t_ip_i>m\vee \sum_{i=1}^{k}t_ip_i\in A$$

- $\forall a\in A$，存在$\langle t_1,t_2,t_3,\dots,t_k\rangle\in\Bbb{N}^k,\sum_{i=1}^{k}t_i p_i=a$

用大白话说一遍：

- 从$P$中选若干个元素（可以重复选择），对其求和，如果不大于$m$，则这个和应当为$A$中的元素。
- $A$中的任意一个元素都可以由上面的这种选择方式凑成。

这样的$P$可能有很多个，你只需要输出集合大小，也就是$k$，最小的一个。没有则输出“$\text{NO}$”。

__数据范围与约定__

- $n,m\le 10^6$
- $A∈Z,A∈\left[1,n\right]$

# 思路
首先，$p\le m$；否则将其去掉，仍然合法。

#### 结论一
显然，只在$P$中选一个元素$p_x$，也应当满足`限制一`。根据题意有$p_x>m\vee p_x\in A$。

而$p_x\le m$，所以只能是

$$p_x\in A\Leftrightarrow P\subseteq A$$

然而，__这并不是充要条件__。在下文的论述中也应该注意这些关系，读者不妨自己考究一下，下面的这些结论也好、推论也罢，究竟是不是充要关系。

#### 结论二
考虑$a_x,a_y\in A(x\ne y)$两个元素。

由`限制二`，$a_x,a_y$可以写成$p$之和。故，$a_x+a_y$可以写成$p$之和。由`限制一`，$p$之和应当为$A$的元素，否则大于$m$。

总结一下，

$$a_x+a_y\in A\vee a_x+a_y>m$$

用群论的话来说，$(A,+)$部分满足封闭性。
#### 推论二
将一个累和的式子多用几次上面的`结论二`，就会发现：

$$\sum_{\{u\}\subseteq A}u\in A$$

由于$P\subseteq A$，它还有一个附加产品：

$$\sum_{\{u\}\subseteq P}u\in A$$

#### 结论三
怎样让这个$P$最小呢？

首先令$P=A$，这样`结论一`和`限制二`都满足了。

如果去掉一些元素，`结论一`显然仍然成立，所以只需要使`限制二`仍成立。

考虑去掉$p_x$的影响。不妨设$p_x=a_y$，那么原本`限制二`中$a_y$可以由$p_x$构成，那么现在便不可了。也就是说，$a_y$可以由$p_x$以外的$p$构成。

不妨设$a_y=p_1+p_2+p_3+\cdots+p_t$（对于集合中的元素，顺序是无关紧要的，我完全可以将其重新排列）。

根据`推论二`，$p_1+p_2\in A,p_3+p_4\in A,\dots,p_{t-1}+p_t\in A$（即使$t$为奇数，根据`结论一`，$p_t\in A$）。

所以，

$$p_x=a_y=\sum_{\{u\}\subseteq A}u\Leftrightarrow \neg(p_x\in P)$$

用文字来说，如果$p$能够由$A$中的元素表示，则$p$可以不属于$A$。

有意思的是，这是充要条件：$a$之和一定可以用$p$之和来表示；不能由$a$之和表示，也一定不能由$p$之和表示。

#### 推论三
`结论二`告诉我们，两个$a$的和也是$A$中的元素。

于是乎，如果$p$可以不属于$P$，当且仅当
$$p=a_x+a_y$$

#### 检查限制一
由于之前的`结论一`并不是`限制一`的充要条件，我们还需要再验证一次`限制一`。

假设`限制一`没有被满足，也就是

$$\neg\left(\sum_{\{u\}\subseteq P}u\in A\right)$$

发现这是很荒谬的：`结论二`已经帮你解决了该问题。

#### 总结
- `结论一`：$P\subseteq A$
- `结论二`：$a_x+a_y\in A\vee a_x+a_y>m$
- `推论三`：如果$p=a_x+a_y$，那么$P$可以去掉$p$，否则不能

所以，算法就是下面的这个流程：

- 初始化集合$P=A$
- 求出所有不超过$m$的$a_x+a_y$
- 对于其中一个和$r$，如果$r\in A$，则将其从$P$中删去，否则输出$\text{NO}$
- 检查完所有的和之后，$P$集合就是答案

那么怎么求$a_x+a_y$呢？用一个生成函数即可：

$$f(x)=\sum_{i=0}^{m}b_i x^i$$

$b_i=1$当且仅当$i\in A$，或者$i=0$。

$f(x)$与自己作卷积，那么$x^k$的系数就是$\sum_{i=0}^{k}b_ib_{k-i}$，将其记为$g(k)$。

显然，这个$g(k)$的意义就是选择$A\cup 0$中的两个元素（可以相同），有多少种不同的方案满足求和为$k$。

只考虑$k\ne 0$的情况。分一个类：

- 如果原本$k\in A$：若$g(k)=2$，显然，$2=b_0b_k+b_kb_0$——也就是说，$k$不能由两个$A$中的元素相加而成——故$k\in P$；若$g(k)\ne 2$，则$k$不属于$P$。
- 如果$k$不属于$A$：若$g(k)>0$，显然，这意味着两个$A$中的元素（可以重复）之和不属于$A$。这意味着无解。反之，什么也不会发生。

卷积就很简单了，只需要做一次$\text{FFT/NTT}$即可。反正我打的$\text{NTT}$。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0' or c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c and c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(long long x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) writeint(x/10);
	putchar(x%10+'0');
}
inline int qkpow(long long base,int q,int Mod){
	long long ans = 1; base %= Mod;
	for(; q; q>>=1,base=base*base%Mod)
		if(q&1) ans = ans*base%Mod;
	return ans;
}

const int MaxN = 4000005;

int omg[MaxN];
void NTT(int a[],int n,int Mod,int g,int opt){
	omg[0] = 1;
	for(int i=1; i<n; ++i)
		omg[i] = 1ll*omg[i-1]*g%Mod;
	int logN = 0;
	while((1<<logN) < n) ++ logN;
	for(int i=0; i<n; ++i){
		int t = 0;
		for(int j=0; (i>>j)!=0; ++j)
			if(i>>j&1) t |= 1<<(logN-j-1);
		if(t < i) swap(a[t],a[i]);
	}
	for(int len=2; len<=n; len<<=1)
		for(int *p=a; p!=a+n; p+=len)
			for(int i=0; i<(len>>1); ++i){
				int t = 1ll*omg[(n/len*i*opt+n)%n]*p[i+(len>>1)]%Mod;
				p[i+(len>>1)] = (p[i]-t+Mod)%Mod, p[i] = (p[i]+t)%Mod;
			}
	if(opt == -1){
		int inv = qkpow(n,Mod-2,Mod);
		for(int i=0; i<n; ++i)
			a[i] = 1ll*a[i]*inv%Mod;
	}
}

int n, m, f[MaxN], F[MaxN];
void input(){
	n = readint(), m = readint();
	for(int i=1; i<=n; ++i)
		f[readint()] = 1;
	f[0] = 1;
}

void solve(){
	int N = 1;
	while(N <= (m<<1)) N <<= 1;
	const int Mod = 998244353;
	const int g = qkpow(3,(Mod-1)/N,Mod);
	for(int i=0; i<=m; ++i) F[i] = f[i];
	NTT(f,N,Mod,g,1);
	for(int i=0; i<N; ++i)
		f[i] = 1ll*f[i]*f[i]%Mod;
	NTT(f,N,Mod,g,-1);
	bool ok = true;
	for(int i=1; i<=m; ++i)
		if(F[i] == 0 and f[i] >= 1)
			ok = false;
	if(not ok)
		puts("NO");
	else{
		puts("YES");
		int k = 0;
		for(int i=1; i<=m; ++i)
			if(F[i] == 1 and f[i] == 2)
				++ k;
		writeint(k), putchar('\n');
		for(int i=1; i<=m; ++i)
			if(F[i] == 1 and f[i] == 2)
				writeint(i), putchar(' ');
		putchar('\n');
	}
}

int main(){
	input(), solve();
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

[Codeforces 题面传送门](https://codeforces.ml/contest/286/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF286E)

好久没刷过 FFT/NTT 的题了，写篇题解罢（

首先考虑什么样的集合 $T$ 符合条件。我们考察一个 $x\in S$，根据题意它能够表示成若干个 $\in T$ 的数之和，这样一来我们可以分出两种情况，如果 $x$ 本来就属于 $T$，那么 $x$ 自然就符合条件，这种情况我们暂且忽略不管。否则根据题设，必然存在一个数列 $b_1,b_2,\cdots,b_m$，满足 $m\ge 2,\forall i\in[1,m],b_i\in T$，且 $\sum\limits_{i=1}^mb_i=x$。由于 $m\ge 2$，我们可以将第一项与后面 $m-1$ 项分开来，即 $b_1+\sum\limits_{i=2}^mb_i$。根据题意前两个应当都 $\in S$，也就是说如果一个数 $x$ 可以表示成两个及以上的 $T$ 中的数的和的必要条件是 $\exists y,z\in S,s.t.y+z=x$，因此我们假设 $S'$ 为可以表示成两个 $S$ 中元素之和的 $x$ 组成的集合，那么考虑分以下几种情况考虑：

- 如果存在一个 $x\in S'$ 但不属于 $S$，那么根据题意可知 $x$ 也应当可以被 $T$ 中元素表示出来，与条件不符。
- 如果不存在属于 $S'$ 但不属于 $S$ 的 $S$，那么我们考虑 $T=\{x|x\notin S',x\in S\}$，那么 $T$ 即为所求。为什么呢？首先显然所有 $x\in S',x\in S$ 的数必须都属于 $T$，因为根据之前的分析，所有可以表示成两个即以上 $T$ 中数的和的数都应当 $\in S'$。其次对于所有可以表示成两个及以上的数的 $x$，也就是每个集合中的 $x$，学过线性代数那一套理论的同学应该明白，删掉这样的 $x$ 是不影响集合所有数能拼出的数的集合的，这样反复进行下去即可将 $S'$ 删空，剩余的部分就是集合 $T$ 了。因此集合 $T$ 符合条件。

那么怎么求 $S'$ 呢？其实非常 trivial（）考虑幂级数 $A(x)=\sum\limits_{i=1}^nx^{a_i}$，那么 $S'$ 即为 $A^2(x)$ 中系数非零且 $\le m$ 的项组成的集合。FFT 求出即可。

时间复杂度 $m\log m$

```cpp
const int MAXN=1e6;
const int MAXP=1<<21;
const double Pi=acos(-1);
int n,m,a[MAXN+5];
struct comp{
	double x,y;
	comp(double _x=0,double _y=0):x(_x),y(_y){}
	comp operator +(const comp &rhs){return comp(x+rhs.x,y+rhs.y);}
	comp operator -(const comp &rhs){return comp(x-rhs.x,y-rhs.y);}
	comp operator *(const comp &rhs){return comp(x*rhs.x-y*rhs.y,x*rhs.y+y*rhs.x);}
} A[MAXP+5];
int rev[MAXP+5],LEN=1;
void FFT(comp *a,int len,int type){
	int lg=31-__builtin_clz(len);
	for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<lg-1);
	for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		comp W(cos(2*Pi/i),type*sin(2*Pi/i));
		for(int j=0;j<len;j+=i){
			comp w(1,0);
			for(int k=0;k<(i>>1);k++,w=w*W){
				comp X=a[j+k],Y=a[(i>>1)+j+k]*w;
				a[j+k]=X+Y;a[(i>>1)+j+k]=X-Y;
			}
		}
	} if(!~type){
		for(int i=0;i<len;i++) a[i].x=(int)(a[i].x/len+0.5);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),a[x]++;
	for(int i=1;i<=m;i++) A[i].x=a[i];
	while(LEN<=(m+m)) LEN<<=1;FFT(A,LEN,1);
	for(int i=0;i<LEN;i++) A[i]=A[i]*A[i];
	FFT(A,LEN,-1);
//	for(int i=1,v;i<=m;i++) printf("%d%c",(v=(int)(A[i].x))," \n"[i==m]);
	for(int i=1,v;i<=m;i++) if((v=(int)(A[i].x))&&!a[i]) return puts("NO"),0;
	vector<int> res;
	for(int i=1,v;i<=m;i++) if(((v=(int)(A[i].x))>0)^a[i]) res.pb(i);
	printf("YES\n%d\n",res.size());
	for(int x:res) printf("%d ",x);
	return 0;
}
```



---

## 作者：LastKismet (赞：0)

# Prob
对形式化题意进行一次中译中，为了方便理解以及后续讲述。

给出一个不可重集，希望你在其中选出一个子集，满足原集合中每个元素均可由这个子集中的一些元素凑得，同时这个子集中凑不出在 $m$ 以内且不在原集合中的数。

找出最小的合法子集。

# Sol
先不考虑无解的情况，假定当前集合有解。

先把所有元素全部加入答案集合，若有解，这样显然是合法的。

接下来考虑缩减集合大小，考虑哪些元素是不必要的。不难发现，倘若一个元素可以被其他元素凑出，那么它就是不必要的。

一个引理是只要一个元素可以被集合中另外两个元素凑出，那么它就是不必要的。如果这个元素需要被另外三个及以上元素凑出，由于“这个子集中凑不出在 $m$ 以内且不在原集合中的数”的性质，随便去除一个元素后，其余元素凑出的数必然存在于原集合中，否则不合法。因此只需要考虑两个元素能否凑出即可判定。

接下来考虑合法性判定，其实只需要判定是否没有不在集合中的 $m$ 以内的数可以被原集合中任意两个数凑出来即可。倘若有这样的数，那么根据“原集合中每个元素均可由这个子集中的一些元素凑得”性质，凑成它的两个数必然可以被我们选定的子集凑出来，因此这个数必然被我们选定的子集凑出来。否则必然有解。

# Code
```cpp
namespace NTT{
    const mint p=0,g=3,gi=332748118;
    typedef vec<mint> poly;
    vec<int> r;
    void ntt(int lim,poly &a,int type){
        a.resize(lim);
        repl(i,0,lim)if(i<r[i])swap(a[i],a[r[i]]);
        for(int mid=1;mid<lim;mid<<=1){
            mint w1=((~type)?g:gi)^((p-1)/(mid<<1));
            for(int j=0;j<lim;j+=(mid<<1)){
                mint w=1;
                repl(k,0,mid){
                    mint x=a[j+k],y=w*a[j+mid+k];
                    a[j+k]=x+y;
                    a[j+mid+k]=x-y;
                    w=w*w1;
                }
            }
        }
    }
    poly operator*(poly a,poly b){
        int lim=1,l=0,len=a.size()+b.size()-1;
        while(lim<a.size()+b.size())lim<<=1,l++;
        r.resize(lim);
        repl(i,0,lim)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        ntt(lim,a,1);ntt(lim,b,1);
        repl(i,0,lim)a[i]=a[i]*b[i];
        ntt(lim,a,-1);
        a.resize(len);
        mint inv=(mint)lim^(p-2);
        repl(i,0,a.size())a[i]*=inv;
        return a;
    }
    poly operator+(poly a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]+b[i];
        return a;
    }
    poly operator-(poly a,poly b){
        if(a.size()<b.size())a.resize(b.size());
        repl(i,0,b.size())a[i]=a[i]-b[i]+p;
        return a;
    }
}
using namespace NTT;

const int N=1e6+5;

int n,m;
int x[N];
bool vis[N];

inline void Main(){
    read(n,m);
    poly a(m+1);
    rep(i,1,n){
        read(x[i]);
        ++a[x[i]];
        vis[x[i]]=1;
    }
    a=a*a;
    int ans=0;
    rep(i,1,m)if(!vis[i]&&a[i]>0)return put((string)"NO");else if(vis[i])++ans;
    put((string)"YES");
    put(ans);
    rep(i,1,n)if(!a[x[i]].x)put(x[i],' ');
}
```

---

## 作者：Provicy (赞：0)

$\text{Problem}$：[[CF286E]Ladies' Shop](http://codeforces.com/problemset/problem/286/E)

$\text{Solution}$：

题目给出两个限制：

$1$、选出的数构成的集合可以拼出序列 $a$ 中的所有数。

2、选出的数构成的集合拼出了一个数 $x$ 且 $x\leq m$，则 $x$ 一定是序列 $a$ 中的一个数。

根据这两个条件，我们显然得到无解的条件：对于 $\forall i \in [1,m]$，设 $S=\{a_{k}\}(1\leq k \leq n)$，则如果 $i \notin S$ 并且 $i=a_{p}+a_{q}(1\leq p,q\leq n)$，则无解。因为不满足限制 $(2)$。

现在考虑有解的情况。设选出的数集为 $Q$，如果存在 $Q_{i}=Q_{j}+Q_{k}$，则我们可以考虑不选择 $Q_{i}$ 而只选择 $Q_{j}$ 和 $Q_{k}$，因为 $Q_{i}$ 可以被拼出，则此时我们可以把 $Q_{j}+Q_{k}$ 看成是一个数。所以如果存在 $i\in S$ 并且 $i=a_{p}+a_{q}(1\leq p,q \leq n)$，则我们不选 $i$ 这个数。我们的目标转换为求所有满足以上条件的 $i$。

考虑设计函数 $f_{i}$ 表示 $i$ 能否被拆成序列 $a$ 中的两数之和。即 $f_{i}=[\exists j\in [1,i-1] ,j\in S,(i-j)\in S]$，发现 $a_{i}>0$，则有 $f_{i}=[\exists j\in [0,i] ,j\in S,(i-j)\in S]$，表示如果 $f_{i}=1$，则 $f_{i}$ 能被拆成序列 $a$ 中的两数之和。发现这个函数非常没用，因为函数之间一点联系都没有......考虑乘法的运算方式，$1\times 1=1$，$0\times 1=1\times 0=0\times 0$。所以我们改 $f_{i}$ 表示 $i$ 被拆成序列 $a$ 中的两数之和的方案数，得到：

$$\qquad f_{i}=\sum\limits_{j=0}^{i}[j\in S][(i-j)\in S] \qquad$$

观察上面的式子，有点像卷积的形式。我们考虑再构造出一个函数 $g_{x}=[x\in S]$，则显然的，$f_{i}=\sum\limits_{j=0}^{i}g_{j}\times g_{i-j}=\sum\limits_{p+q=i}g_{p}\times g_{q}$

这东西就是卷积形式了。再构造 $F_{x}=\sum\limits_{j=0}^{M}g_{j}\times x^{i}$，$G_{x}=\sum\limits_{j=0}^{M}f_{j}\times x^{i}$，则由上式，得到 $F=G*G$。

直接 $\text{FFT}$ 或者 $\text{NTT}$ 即可解决。最后如果 $F_{i}=0$ 并且 $i\in S$，则这个数我们要选中，否则我们不选。

$\text{Code}$：

```cpp
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <bitset>
#define ri register
#define inf 0x7fffffff
#define E (1)
#define mk make_pair
//#define int long long
//#define double long double
using namespace std; const int N=4000010, Mod=998244353;
inline int read()
{
    int s=0, w=1; ri char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch-'0'), ch=getchar();
    return s*w;
}
void print(int x) { if(x<0) x=-x, putchar('-'); if(x>9) print(x/10); putchar(x%10+'0'); }
int n,m,a[N],g[N],f[25][2],book[N],T,rev[N];
inline void Get_Rev() { for(ri int i=0;i<T;i++) rev[i]=(rev[i>>1]>>1)|((i&1)?(T>>1):0); }
inline int ksc(int x,int p) { int res=1; for(;p;p>>=1, x=1ll*x*x%Mod) if(p&1) res=1ll*res*x%Mod; return res; }
inline void NTT(int *s,int type)
{
    for(ri int i=0;i<T;i++) if(i<rev[i]) swap(s[i],s[rev[i]]);
    for(ri int i=2,cnt=1;i<=T;cnt++, i<<=1)
    {
        int wn=f[cnt][type];
        for(ri int j=0, mid=(i>>1);j<T;j+=i)
        {
            for(ri int k=0, w=1;k<mid;k++, w=1ll*w*wn%Mod)
            {
                int x=s[j+k], y=1ll*w*s[j+mid+k]%Mod;
                s[j+k]=(x+y)%Mod, s[j+mid+k]=(x-y+Mod)%Mod;
            }
        }
    }
    if(!type) for(ri int i=0,inv=ksc(T,Mod-2);i<T;i++) s[i]=1ll*s[i]*inv%Mod;
}
signed main()
{
    f[23][1]=ksc(3,119), f[23][0]=ksc(332748118,119);
    for(ri int i=22;~i;i--) f[i][1]=1ll*f[i+1][1]*f[i+1][1]%Mod, f[i][0]=1ll*f[i+1][0]*f[i+1][0]%Mod;
    n=read(), m=read();
    for(ri int i=1;i<=n;i++) a[i]=read(), g[a[i]]=book[a[i]]=1;
    T=1; while(T<=m+m) T<<=1; Get_Rev();
    NTT(g,1);
    for(ri int i=0;i<T;i++) g[i]=1ll*g[i]*g[i]%Mod;
    NTT(g,0);
    for(ri int i=1;i<=m;i++) if(g[i] && !book[i]) { puts("NO"); return 0; }
    puts("YES"); int cnt=0;
    for(ri int i=1;i<=n;i++) if(!g[a[i]]) cnt++;
    printf("%d\n",cnt);
    for(ri int i=1;i<=n;i++) if(!g[a[i]]) printf("%d ",a[i]);
    puts("");
    return 0;
}
```



---

## 作者：大菜鸡fks (赞：0)

$noip2018 d1t2$?

我不加证明地猜一个看起来很显然的结论：如果$a[i]$可以被前面的数组合出来，那么，$a[i]$可以去掉。

于是我们用fft模拟背包的过程。

```cpp
#include<cstdio>
#include<complex>
#include<cmath>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
typedef complex<double> E;
const double pi=acos(-1.0);
const int N=1<<21;
int sum,n,m,lim,L,rev[N],ans[N],num[N];
E a[N];
inline void init(){
	n=read(); m=read();
	for (int i=1;i<=n;i++) num[i]=read();
}
inline void FFT(E *A,int opt){
	for (int i=0;i<lim;i++) if (i>rev[i]) swap(A[i],A[rev[i]]);
	for (int s=1;s<lim;s<<=1){
		E Wn(cos(pi/s),opt*sin(pi/s));
		for (int i=0;i<lim;i+=(s<<1)){
			E w(1,0);
			for (int j=0;j<s;j++,w=w*Wn){
				E tmp=A[i+j+s]*w; A[i+j+s]=A[i+j]-tmp; A[i+j]+=tmp;
			}
		}
	}
	if (opt==-1) for (int i=0;i<lim;i++) A[i]/=lim;
}
inline void solve(){
	for (lim=1;lim<=m*2;lim<<=1,L++);
	for (int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=1;i<=n;i++) a[num[i]]=1,ans[num[i]]=1;
	FFT(a,1);
	for (int i=0;i<lim;i++) a[i]*=a[i];
	FFT(a,-1);
	for (int i=1;i<=m;i++)
		if ((int)(a[i].real()+0.5>=1)){
			if (!ans[i]) {puts("NO"); return;}
			ans[i]=0;
		}
	puts("YES");
	for (int i=1;i<=m;i++) if (ans[i]) sum++;
	writeln(sum);
	for (int i=1;i<=m;i++) if (ans[i]) write(i),putchar(' ');
	puts("");
}
int main(){
	init(); solve();
	return 0;
}
```

---

