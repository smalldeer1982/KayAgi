# [GXOI/GZOI2019] 逼死强迫症

## 题目描述

ITX351 要铺一条 $2 \times N$ 的路，为此他购买了 $N$ 块 $2 \times 1$ 的方砖。可是其中一块砖在运送的过程中从中间裂开了，变成了两块 $1 \times 1$ 的砖块！  
ITX351 由此产生了一个邪恶的想法：他想要在这条路上故意把两块 $1 \times 1$ 的砖块分开铺，**不让两块砖有相邻的边**，其他砖块可以随意铺，直到整条路铺满。这样一定可以逼死自身强迫症 sea5！

也许下面的剧情你已经猜到了——他为此兴奋不已，以至于无法敲键盘。于是，他请你帮忙计算一下，有多少种方案可以让自己的阴谋得逞。

## 说明/提示

样例中 $ N=4 $ 解释见下图：

![](https://cdn.luogu.com.cn/upload/pic/56734.png)

### 数据范围

|测试点编号|$N$ 的规模|$T$ 的规模|
|:-:|:-:|:-:|
|$1$|$N \le 10$|$T \le 10$|
|$2$|$N \le 10$|$T \le 10$|
|$3$|$N \le 10^5$|$T \le 50$|
|$4$|$N \le 10^5$|$T \le 50$|
|$5$|$N \le 10^5$|$T \le 50$|
|$6$|$N \le 2 \times 10^9$|$T \le 50$|
|$7$|$N \le 2 \times 10^9$|$T \le 50$|
|$8$|$N \le 2 \times 10^9$|$T \le 50$|
|$9$|$N \le 2 \times 10^9$|$T \le 500$|
|$10$|$N \le 2 \times 10^9$|$T \le 500$|

## 样例 #1

### 输入

```
3
1
2
4```

### 输出

```
0
0
6```

# 题解

## 作者：mrsrz (赞：24)

令$f_i$表示$N=i$时的方案数。

考虑最右侧多出了一列，我们可以直接放一个$1\times 2$的方块，也可以横着放两个$1\times 2$的方块覆盖$2\times 2$的区域。

这是最右边不放$1\times 1$的方块的情况。

考虑最右侧放了$1\times 1$的方块。

发现另一个这个方块能放在$1\sim i-2$列上，且每列恰只有一个位置可行（同行还是异行与列数差的奇偶性有关）。

然后这个$1\times 1$的方块左边的区域可以任意摆放，右边的区域只有一种方案。

设$g_i$表示$2\times i$的区域只用$1\times 2$的方块覆盖的方案数，$h_i$表示$g_i$的前缀和（特别地，$g_0$=1\\）。

那么有$f_i=f_{i-1}+f_{i-2}+2h_{i-3}$。

发现$g$是斐波那契数列，而斐波那契数列的前缀和满足$h_i=g_{i+2}-1$。

所以$f_i=f_{i-1}+f_{i-2}+2g_{i-1}-2$。

用矩阵快速幂维护即可。需要维护$5\times 5$的矩阵。

时间复杂度$O(125T\log n)$。

## Code：
```cpp
#include<cstdio>
#include<cstring>
const int md=1e9+7;
typedef long long LL;
struct mat{
    int a[5][5];
    inline mat(){memset(a,0,sizeof a);}
    inline mat operator*(const mat&b)const{
        mat c;
        for(int i=0;i<5;++i)
            for(int k=0;k<5;++k)
                for(int j=0;j<5;++j)
                    c.a[i][j]=(c.a[i][j]+(LL)a[i][k]*b.a[k][j])%md;
        return c;
    }
}s;
mat pow(mat a,int b){
    mat ret;
    ret.a[0][0]=ret.a[1][1]=ret.a[2][2]=ret.a[3][3]=ret.a[4][4]=1;
    for(;b;b>>=1,a=a*a)
        if(b&1)ret=ret*a;
    return ret;
}
int main(){
    s.a[0][1]=s.a[1][0]=s.a[1][1]=s.a[2][3]=s.a[3][2]=s.a[3][3]=s.a[4][4]=1;
    s.a[3][1]=2,s.a[4][1]=md-1;
    int T;
    for(scanf("%d",&T);T--;){
        int n;
        scanf("%d",&n);
        if(n<3)
            puts("0");
        else{
            mat ans;
            ans.a[0][2]=1,ans.a[0][3]=ans.a[0][4]=2;
            printf("%d\n",(ans*pow(s,n-2)).a[0][1]);
        }
    }
    return 0;

}
```

---

## 作者：Great_Influence (赞：16)

推式子题。

首先，我们考虑算出不包含 $1\times 1$ 的块的答案。

因为每个 $1\times 2$ 的块要么横着放，要么两个一起竖着放，因此存在关系式 $F_n=F_{n-1}+F_{n-2}$ ，就是斐波那契数列。

然后考虑包含 $1\times 1$ 的块的答案。

可以发现，这两个块放完后，中间的块就最多只有 $1$ 种放法。而这两个块的整体最小是 $2\times 3$ 的块。再算上两个块上下摆放，两个块构成 $2\times n(n\ge 3)$ 大小的方案数都是 $2$ 。因此我们就得到了一个式子:

$$ans=2\sum_{i=3}^n\sum_{j=0}^{n-i} F_j*F_{n-i-j}$$

推一下:

$$ans=2\sum_{i=3}^n\sum_{j=0}^{n-i} F_j*F_{n-i-j}$$

$$=2\sum_{i=0}^{n-3} F_i\sum_{j=0}^{n-3-i} F_j$$

$$=2\sum_{i=0}^{n-3}F_i*(F_{n-1-i}-1)$$

$$=2-2F_{n-1}+2\sum_{i=0}^{n-3}F_i*F_{n-1-i}$$

我们设 $S_n=\sum_{i=0}^n F_i*F_{n-i}$ ，则:

答案就是 $2-2F_{n-1}+2(S_{n-1}-F_{n-2}*F_1-F_{n-1}*F_{0})$ ，即 $2(1+S_{n-1}-2F_{n-1}-F_{n-2})$ 。

$$S_n=\sum_{i=0}^n F_i*F_{n-i}$$

$$=F_n+F_{n-1}+\sum_{i=0}^{n-2} F_i*(F_{n-i-1}+F_{n-i-2})$$
$$=F_n+F_{n-1}+\sum_{i=0}^{n-2}F_i*F_{n-1-i}+\sum_{i=0}^{n-2} F_i*F_{n-2-i}$$
$$=F_n+\sum_{i=0}^{n-1}F_i*F_{n-1-i}+\sum_{i=0}^{n-2} F_i*F_{n-2-i}$$
$$=F_n+S_{n-1}+S_{n-2}$$

考虑利用矩阵快速幂解决这个问题。可以列出转移矩阵:

$$\begin{bmatrix}F_{n-2}\\F_{n-1}\\S_{n-2}\\S_{n-1}\end{bmatrix}\begin{bmatrix}0&1&0&0\\1&1&0&0\\0&0&0&1\\1&1&1&1\end{bmatrix}=\begin{bmatrix}F_{n-1}\\F_n\\S_{n-1}\\S_n\end{bmatrix}$$

如果预处理出 $2^k$ 的矩阵，总复杂度为 $O(64\log W+\sum 16\log n)$ 。

代码:

```cpp
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<queue>
#include<iostream>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
	const uint32 Buffsize=1<<15,Output=1<<24;
	static char Ch[Buffsize],*S=Ch,*T=Ch;
	inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
	static char Out[Output],*nowps=Out;
	
	inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

	template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

void file()
{
#ifndef ONLINE_JUDGE
	FILE*DSD=freopen("water.in","r",stdin);
	FILE*CSC=freopen("water.out","w",stdout);
#endif
}

const int mod=1e9+7;

static struct matrix
{
	int c[4][4];

	matrix operator*(const matrix&a)const
	{
		matrix x;
		Rep(i,0,3)Rep(j,0,3)
			x.c[i][j]=((ll)c[i][0]*a.c[0][j]+(ll)c[i][1]*a.c[1][j]+
				(ll)c[i][2]*a.c[2][j]+(ll)c[i][3]*a.c[3][j])%mod;
		return x;
	}
}bs[35];

static int n;

inline void init(){read(n);}

static int vec[4],as[4];

inline void solve()
{
	if(n<=3){write(n==3?2:0);return;}
	n-=2;
	vec[0]=vec[1]=vec[2]=1,vec[3]=2;
	Rep(i,0,30)if(n>>i&1)
	{
		Rep(j,0,3)
		as[j]=((ll)vec[0]*bs[i].c[j][0]+(ll)vec[1]*bs[i].c[j][1]
		+(ll)vec[2]*bs[i].c[j][2]+(ll)vec[3]*bs[i].c[j][3])%mod;
		Rep(j,0,3)vec[j]=as[j];
	}
	write((((vec[3]-vec[0]-2ll*vec[1]+mod+mod+mod)%mod<<1)%mod+2)%mod);
}

int main()
{
	file();
	bs[0].c[0][1]=bs[0].c[1][0]=bs[0].c[1][1]=bs[0].c[2][3]=bs[0].c[3][0]=bs[0].c[3][1]=bs[0].c[3][2]=bs[0].c[3][3]=1;
	Rep(i,1,30)bs[i]=bs[i-1]*bs[i-1];
	static int _;
	read(_);
	while(_--)init(),solve();
	flush();
	return 0;
}
```

---

## 作者：lhm_ (赞：10)

可以先去考虑没有$1 \times 1$的砖块的情况，对于最后一个位置只有两种情况，一个是竖着用一块砖铺设$2 \times 1$，另一个为横着用两块砖铺设$2 \times 2$。

设没有$1 \times 1$的砖块的情况铺$2 \times n$的路的方案数为$F_n$，根据上面的分析得$F_n=F_{n-1}+F_{n-2}$，发现其为斐波那契数列。

用同样的方法考虑有$1 \times 1$的砖块的情况，设$f_n$表示按题意铺$2 \times n$的路的方案数，当最后的位置没有$1 \times 1$的砖块的影响时，其也是有两种放置情况，也就是说$f_{i-1}$和$f_{i-2}$对$f_i$都有贡献。

当最后一个位置需要铺设为$1 \times 1$的砖块时，可以发现该砖块到另一个砖块的区间的铺设情况是唯一的，所以这种情况决定方案数的是这两个$1 \times 1$的砖块形成的区间之前的$2 \times 1$砖块铺设情况。因此我们得：

$$f_i=f_{i-1}+f_{i-2}+2\sum_{j=0}^{i-3}F_j$$

设$S_i=\sum\limits_ {j=0}^{i}F_j$，得$f_i=f_{i-1}+f_{i-2}+2S_{i-3}$

然后就可以递推来求解了，但是发现$n$很大，所以用矩阵快速幂来加速递推。

设矩阵$\begin{bmatrix} f_i&f_{i-1}&F_{i-2}&F_{i-3}&S_{i-3}\end{bmatrix}
\quad$，经过分析得，将其转移到$\begin{bmatrix} f_{i+1}&f_i&F_{i-1}&F_{i-2}&S_{i-2}\end{bmatrix}
\quad$的转移矩阵为：

$$

	\begin{bmatrix} 
		
        1&1&0&0&0\\
		1&0&0&0&0\\
		2&0&1&1&1\\
		0&0&1&0&0\\
		2&0&0&0&1\\
        
    \end{bmatrix}
	\quad
$$

然后每次询问矩阵快速幂一下就好了。

$code:$

```cpp
#include<bits/stdc++.h>
#define p 1000000007
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll T,n;
struct matrix
{
    ll a[6][6];
    matrix()
    {
        memset(a,0,sizeof(a));
    }
}m,ans;
matrix operator *(const matrix &a,const matrix &b)
{
    matrix c;
    for(int i=0;i<5;++i)
        for(int j=0;j<5;++j)
            for(int k=0;k<5;++k)
                c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%p+p)%p;
    return c;
}
matrix qp(matrix x,ll y)
{
    matrix e;
    for(int i=0;i<5;++i) e.a[i][i]=1;
    while(y)
    {
        if(y&1) e=e*x;
        x=x*x,y>>=1;
    }
    return e;
}
ll m1[6][6]=
{
    {2,0,1,1,1}
};
ll m2[6][6]=
{
    {1,1,0,0,0},
    {1,0,0,0,0},
    {2,0,1,1,1},
    {0,0,1,0,0},
    {2,0,0,0,1}
};
int main()
{
    read(T);
    memcpy(ans.a,m1,sizeof(ans.a));
    memcpy(m.a,m2,sizeof(m.a));
    while(T--)
    {
        read(n);
        if(n<3) puts("0");
        else printf("%lld\n",(ans*qp(m,n-3)).a[0][0]);
    }
    return 0;
}
```

---

## 作者：Daidly (赞：7)

好的计数原理与矩阵快速幂练习题。

强调递推式的适用范围，快速推式子。

---

手玩可以得到，若确定第一个 $1\times 1$ 的位置与两个 $1\times 1$ 之间的距离，这部分贡献为 $2$（翻转后也算一种）。而考虑这部分以外的贡献，即正常铺满的计数。

记 $f_i$ 为长度是 $2\times i$ 的路铺满的方案数，可以在 $2\times (i-1)$ 的基础上放一个竖着的，也可以在 $2\times(i-2)$ 的基础上放两个横着的，则有 $f_i=f_{i-1}+f_{i-2},(i\ge 2)$，初始值为 $f_0=1,f_1=1$（或者可以认为是 $f_1=1,f_2=2$），这是一个从 $0$ 开始的斐波那契数列。

先枚举两个 $1\times 1$ 之间的距离，再枚举第一个 $1\times 1$ 的位置，则有（分离常项，提取公因式，将复杂的式子变简单）：
$$
\begin{aligned}

ans&=\sum_{i=3}^n\sum_{j=1}^{n-i+1}f_{j-1}\times 2\times f_{n-j-i+1}\\
&=2\sum_{i=0}^{n-3}\sum_{j=0}^{n-i-3}f_jf_{n-j-i-3}\\
&=2\sum_{i=0}^{n-3}f_i\sum_{j=0}^{n-3-i}f_j

\end{aligned}
$$
斐波那契数列有前缀和公式，此处从 $0$ 开始，$\sum\limits_{i=0}^{n}f_i=f_{n+2}-1$

证明如下（同样是从 $0$ 开始）：

分离奇偶项，不妨设 $n$ 为奇数，偶数也差不多。
$$
\begin{aligned}
f_0+f_1+\cdots+f_{n-1}+f_n&=(f_0+f_2+f_4+\cdots+f_{n-1})+(f_1+f_3+f_5+\cdots +f_n)\\

&=(f_1+f_2+f_4+\cdots+f_{n-1})+(f_0+f_1+f_3+f_5+\cdots +f_n)-f_0\\

&=(f_3+f_4+\cdots+f_{n-1})+(f_2+f_3+f_5+\cdots +f_n)-f_0\\

&=(f_5+\cdots+f_{n-1})+(f_4+f_5+\cdots +f_n)-f_0\\

&=f_{n}+f_{n+1}-1\\

&=f_{n+2}-1

\end{aligned}
$$
由此可得：
$$
\begin{aligned}

2\sum_{i=0}^{n-3}f_i\sum_{j=0}^{n-3-i}f_j&=2\sum_{i=0}^{n-3}f_i(f_{n-1-i}-1)\\

&=2\Bigg(\sum_{i=0}^{n-3}f_if_{n-1-i}-\sum_{i=0}^{n-3}f_i\Bigg)\\

&=2\Bigg(\sum_{i=0}^{n-3}f_if_{n-1-i}-f_{n-1}+1\Bigg)\\

\end{aligned}
$$
如何快速求乘积和那一项，记 $S_{n}=\sum\limits_{i=0}^{n}f_if_{n-i}$，观察到有 $f_{(n-1)-i}$，则有：
$$
\begin{aligned}

ans&=2\Bigg(\sum_{i=0}^{n-3}f_if_{n-1-i}-f_{n-1}+1\Bigg)\\

&=2\Bigg(S_{n-1}-(f_{n-1}+f_{n-2})-f_{n-1}+1\Bigg)\\

&=2\Bigg(S_{n-1}-2f_{n-1}-f_{n-2}+1\Bigg)\\

\end{aligned}
$$
如何求出 $S_{n}$，根据 $n\leq 2\times 10^9$ 很快可以想到矩阵快速幂，有递推式：
$$
\begin{aligned}

S_n&=\sum_{i=0}^nf_if_{n-i}\\

&=f_n+\sum_{i=0}^{n-1}f_i(f_{n-1-i}+f_{n-2-i})\\

&=f_n+\sum_{i=0}^{n-1}f_if_{n-1-i}+\sum_{i=0}^{n-2}f_if_{n-2-
i}\\

&=f_n+S_{n-1}+S_{n-2},(n\ge 2)

\end{aligned}
$$
其中，初始值 $S_0=1,S_1=2$。

可得出转移矩阵：
$$
\begin{gathered}

\begin{pmatrix} S_{n-1}&S_{n-2}&f_{n-1}&f_{n-2} \end{pmatrix}
\times

\begin{pmatrix} 1&1&0&0\\1&0&0&0\\1&0&1&1\\1&0&1&0 \end{pmatrix}

=

\begin{pmatrix} S_{n}&S_{n-1}&f_{n}&f_{n-1} \end{pmatrix}

\end{gathered}
$$
如何又快又准地解决这类问题是关键，需要有丰富的推式子经验以及化简的能力。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int mod=1e9+7;
struct Matrix{
	int n,m,f[5][5];
	Matrix(){
		memset(f,0,sizeof(f));
	}
}base,tmp;

Matrix mul(Matrix a,Matrix b){
	Matrix ans;
	ans.n=a.n,ans.m=b.m;
	for(int i=1;i<=a.n;++i){
		for(int j=1;j<=b.m;++j){
			for(int k=1;k<=a.m;++k){
				ans.f[i][j]=(ans.f[i][j]+a.f[i][k]*b.f[k][j]%mod)%mod;
			}
		}
	}
	return ans;
}

Matrix qpow(Matrix a,int b){
	Matrix ans;
	ans.n=ans.m=a.n;
	for(int i=1;i<=ans.n;++i)ans.f[i][i]=1;
	while(b){
		if(b&1)ans=mul(ans,a);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
 
void solve(){
	int n=read();
	if(n==1||n==2){puts("0");return;}
	base.n=base.m=4;
	base.f[1][1]=base.f[2][1]=base.f[3][1]=base.f[4][1]=base.f[1][2]=base.f[3][3]=base.f[4][3]=base.f[3][4]=1;
	tmp.n=1,tmp.m=4;
	tmp.f[1][1]=2,tmp.f[1][2]=tmp.f[1][3]=tmp.f[1][4]=1;
	tmp=mul(tmp,qpow(base,n-2));
	print((2*(tmp.f[1][1]-2*tmp.f[1][3]%mod-tmp.f[1][4]+1ll)%mod+mod)%mod),puts("");
}

signed main(){
	int tt=read();
	while(tt--)solve();	
	return 0;
}
```

如果有帮助就点个赞吧。

---

## 作者：peterwuyihong (赞：6)

陷入了数数题的深渊

题意：给你 $2$ 个 $1\times1$ 板，$n-1$ 个 $1\times2$ 板，铺成一条 $2\times n$ 的路，两个 $1\times1$ 板不能相邻，求出铺法数量 $\bmod\ 10^9+7$。多测，$T\le500,n\le 2\times10^9$。

引理：$n$ 个 $1\times2$ 的板，铺成 $2\times n$ 的路，有 $Fib_n$ 种铺法。

证明：你考虑用任意多个 $1\times1$ 板和 $1\times2$ 板铺出第一行，那么下面必然是对应的。然后铺第一行就有一个显然的 $dp$，$f_i=f_{i-1}+f_{i-2}$。

然后我们解决这个问题，我们枚举两个 $1\times1$ 板出现的地方，那么这两个 $1\times1$ 板包含住的区间**已经固定了**！根据黑白染色，仅有两种是合法的放置，于是柿子就是：

这里挂一个我推到一半的柿子

$$2\sum_{len=3}^n\sum_{l=1}^{n-len+1}Fib_{l-1}Fib_{n-(l-1)-len}$$

$$2\sum_{len=3}^n\sum_{l=0}^{n-len}Fib_{l}Fib_{n-l-len}$$

我超，卷积！

你设一个牛逼的斐波那契数列，即 $\texttt{Myee}$ 数列：${Myee}_n=\sum_{i=0}^nFib_iFib_{n-i}$。

那么 $\texttt{Myee}$ 数列的生成函数为 $(\dfrac{x}{1-x-x^2})^2$

然后这玩意儿前缀和就是乘上一个 $1+x+x^2+\ldots$ 即 $(1-x)^{-1}$，前缀和的生成函数就是

$$\frac{x^2}{(1-x-x^2)^2(1-x)}$$

设通项为 $F_n=A+(Bn+C)(\dfrac{1+\sqrt5}2)^n+(Dn+E)(\dfrac{1-\sqrt5}2)^n$

写个多项式板子跑出前几项，

```
G=(1+sqrt(5))/2,
H=(1-sqrt(5))/2,
A+C+E=0,
A+(B*1+C)*G^1+(D*1+E)*H^1=0,
A+(B*2+C)*G^2+(D*2+E)*H^2=0,
A+(B*3+C)*G^3+(D*3+E)*H^3=2,
A+(B*4+C)*G^4+(D*4+E)*H^4=6
```
放到数字帝国上一跑
$$A = 2,B = \frac{\sqrt5+1}5,C = -\frac{11\sqrt5+25}{25},D = \frac{-\sqrt5+1}5,E = \frac{11\sqrt5-25}{25}$$

牛了，写就行了。

```cpp
#define maxn 100010
const int p=1e9+7;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
const int inv5=ksm(5,p-2);
const int inv2=(p+1)>>1;
struct Cp{
	int a,b;
	Cp(int A=0,int B=0):a(A),b(B){}
	inline Cp operator+(Cp x)const{return Cp(Add(a,x.a),Add(b,x.b));}
	inline Cp operator-(Cp x)const{return Cp(Sub(a,x.a),Sub(b,x.b));}
	inline Cp operator*(Cp x)const{return Cp(Add(Mul(a,x.a),Mul(5,Mul(b,x.b))),Add(Mul(a,x.b),Mul(b,x.a)));}
	inline Cp operator~()const{return Cp(a,p-b);}
}A(2,0),B(inv5,inv5),C(p-1,Mul(p-11,Mul(inv5,inv5))),D(inv5,p-inv5),E(p-1,Mul(11,Mul(inv5,inv5))),G(inv2,inv2),H(inv2,p-inv2);
Cp ksm(Cp a,int b){
	Cp ans(1,0);
	for(;b;b>>=1,a=a*a)
	if(b&1)ans=ans*a;
	return ans;
}
int n,T;
signed main(){
	for(cin>>T;T;T--){
		cin>>n;
		Cp ans=A+(B*Cp(n,0)+C)*ksm(G,n)+(D*Cp(n,0)+E)*ksm(H,n);
		cout<<ans.a<<endl;
	}
}
```
说句闲话，我之前直接把 $\dfrac{1+\sqrt5}2$ 带入数字帝国，结果太长了！于是我只能用字母表示数。

---

## 作者：StudyingFather (赞：6)

**如果公式炸了的话，更好的阅读体验可以点 [这里](https://studyingfather.com/archives/2935)。**

神仙推式子题，推了快一下午 /kk

容易发现整个区域可以分为三部分：第一个 $1 \times 1$ 方块左边，两个 $1 \times 1$ 方块中间部分（至少 $2 \times 3$ 的区域），第二个 $1 \times 1$ 方块右边部分。

如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/3gzn31qa.png)

其中两个 $1 \times 1$ 方块是同行还是异行取决于中间列数的奇偶性（奇数为异行，偶数为同行）。

如果两个 $1 \times 1$ 方块的位置定下来了，上图中间的红色区域就只有一种摆法。

而左边黑色区域和右边绿色区域，显然分别有 $F_x,F_y$ 种摆法（$F_x$ 为斐波那契数列，满足 $F_0=F_1=1$，$F_i=F_{i-1}+F_{i-2}$）。

根据乘法原理，答案可以表示为：

$$
2 \sum_{x=0}^{n-3} \sum_{y=0}^{n-x-3}F_x \times F_y
$$

（中间的红色区域考虑上下行交换，所以答案乘二）

运用乘法分配律：

$$
2 \sum_{x=0}^{n-3}F_x \sum_{y=0}^{n-x-3}F_y
$$

斐波那契数列满足 $\sum_{i=0}^x F_i=F_{x+2}-1$，所以把后面的 $\sum F_y$ 换掉：

$$
2 \sum_{x=0}^{n-3}F_x \times (F_{n-x-1}-1)
$$

整理后得到：

$$
2 (\sum_{x=0}^{n-3}F_x \times F_{n-x-1}-F_{n-1}+1)
$$

现在重点放到 $\sum_{x=0}^{n-3}F_x \times F_{n-x-1}$ 上。

我们设：

$$
G_n=\sum_{x=0}^{n}F_x \times F_{n-x}
$$

将 $x=n$ 和 $x=n-1$ 提出来：

$$
G_n=\sum_{x=0}^{n-2}F_x \times F_{n-x} + F_n+F_{n-1}
$$

把 $F_{n-x}$ 也拆开：

$$
G_n=\sum_{x=0}^{n-2}F_x \times (F_{n-x-1}+F_{n-x-2})+F_n+F_{n-1}
$$

用乘法分配律：

$$
G_n=\sum_{x=0}^{n-2}F_x \times F_{n-x-1}+\sum_{x=0}^{n-2}F_x \times F_{n-x-2}+F_n+F_{n-1}
$$

把 $F_{n-1}$ 放回到式子的第一块：

$$
G_n=\sum_{x=0}^{n-1}F_x \times F_{n-x-1}+\sum_{x=0}^{n-2}F_x \times F_{n-x-2}+F_n
$$

到这里终于豁然开朗啦。

$$
G_n=G_{n-1}+G_{n-2}+F_n
$$

把 $G_n$ 代入到答案中，可得答案为：

$$
2(1+G_{n-1}-2 \times F_{n-1}-F_{n-2})
$$

最后的问题就是用矩阵快速幂来递推 $F_n,G_n$ 了。

稍微推一下就能得到：

$$
\begin{bmatrix}
F_{n-1} & F_{n-2} & F_{n-3} & G_{n-1} & G_{n-2} & G_{n-3}
\end{bmatrix}
\begin{bmatrix}
1 & 1 & 0 & 1 & 0 & 0\\ 
1 & 0 & 1 & 1 & 0 & 0\\ 
0 & 0 & 0 & 0 & 0 & 0\\ 
0 & 0 & 0 & 1 & 1 & 0\\ 
0 & 0 & 0 & 1 & 0 & 1\\ 
0 & 0 & 0 & 0 & 0 & 0
\end{bmatrix}=
\begin{bmatrix}
F_n & F_{n-1} & F_{n-2} & G_n & G_{n-1} & G_{n-2}
\end{bmatrix}
$$

时间复杂度 $O(6^3 T \log n)$。

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
#define MOD 1000000007
using namespace std;
struct mat
{
 long long a[15][15];
 mat(int x=0)
 {
  memset(a,0,sizeof(a));
  for(int i=1;i<=6;i++)
   a[i][i]=x;
 }
 mat operator*(const mat&A)const
 {
  mat ans;
  for(int k=1;k<=6;k++)
   for(int i=1;i<=6;i++)
    for(int j=1;j<=6;j++)
     ans.a[i][j]=(ans.a[i][j]+a[i][k]*A.a[k][j])%MOD;
  return ans;
 }
}f,g;
void init()
{
 //[f_3,f_2,f_1,g_3,g_2,g_1]
 f.a[1][1]=3,f.a[1][2]=2,f.a[1][3]=1,f.a[1][4]=10,f.a[1][5]=5,f.a[1][6]=2;
 /*
 1 1 0 1 0 0
 1 0 1 1 0 0
 0 0 0 0 0 0
 0 0 0 1 1 0
 0 0 0 1 0 1
 0 0 0 0 0 0
 */
 g.a[1][1]=1,g.a[1][2]=1,g.a[1][3]=0,g.a[1][4]=1,g.a[1][5]=0,g.a[1][6]=0;
 g.a[2][1]=1,g.a[2][2]=0,g.a[2][3]=1,g.a[2][4]=1,g.a[2][5]=0,g.a[2][6]=0;
 g.a[3][1]=0,g.a[3][2]=0,g.a[3][3]=0,g.a[3][4]=0,g.a[3][5]=0,g.a[3][6]=0;
 g.a[4][1]=0,g.a[4][2]=0,g.a[4][3]=0,g.a[4][4]=1,g.a[4][5]=1,g.a[4][6]=0;
 g.a[5][1]=0,g.a[5][2]=0,g.a[5][3]=0,g.a[5][4]=1,g.a[5][5]=0,g.a[5][6]=1;
 g.a[6][1]=0,g.a[6][2]=0,g.a[6][3]=0,g.a[6][4]=0,g.a[6][5]=0,g.a[6][6]=0;
}
mat fpow(mat x,int y)
{
 mat ans(1);
 while(y)
 {
  if(y&1)ans=ans*x;
  x=x*x;
  y>>=1;
 }
 return ans;
}
int main()
{
 int t;
 cin>>t;
 init();
 while(t--)
 {
  int n;
  cin>>n;
  if(n<=2)cout<<0<<endl;
  else
  {
   mat res=f*fpow(g,n-3);
   cout<<(2*(-2*res.a[1][2]-res.a[1][3]+res.a[1][5]+1)%MOD+MOD)%MOD<<endl;
  }
 }
 return 0;
}
```


---

## 作者：FZzzz (赞：5)

大佬们的做法都太神啦，我这个菜鸡只会暴力 dp。

首先我们发现题目这个东西不好设状态，所以我们先做一个简单的容斥，将所有方案数量减去不合法（即两块单砖挨在一起了）的数量。

不合法的数量是多少呢？我们发现两块砖既然挨在一起了，就可以直接看作是一块大的砖，所以就是斐波那契数列。但是这里由于每一块大砖都可以变成两块小砖，所以实际上要乘上 $n$。

对于所有方案的我们暴力 dp。设 $f_{i,j,k}$ 为当前考虑到第 $i$ 行，该行已经被放置了 $k$ 块，还有 $j$ 块小砖没有用的方案数，则不难写出状态转移。然后我们发现 $j$ 和 $k$ 的取值是 $0$ 到 $2$，我们将其合为一维，这样就可以直接上矩乘了。

这个算法的时间复杂度是 $O(9^3\log n)$。~~还是那句话，因为 $9$ 是常数，所以实际上是 $O(\log n)$。~~

下面是~~奇丑无比的~~代码，使用了 C++11 的写法减少码量，在提交后成功拿到[全谷最劣解](https://www.luogu.com.cn/record/list?pid=P5303&orderBy=1&status=&page=13)。
```cpp
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
typedef long long ll;
const ll mod=1e9+7;
typedef vector<ll> col;
typedef vector<col> matrix;
matrix operator *(matrix a,matrix b){
	int n=a.size();
	matrix c;
	for(int i=0;i<n;i++){
		c.push_back(col());
		for(int j=0;j<n;j++) c[i].push_back(0);
	}
	for(int i=0;i<n;i++) for(int j=0;j<n;j++)
		for(int k=0;k<n;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j]%mod)%mod;
	return c;
}
matrix ksm(matrix a,ll b){
	matrix ans;
	int n=a.size();
	for(int i=0;i<n;i++){
		ans.push_back(col());
		for(int j=0;j<n;j++) ans[i].push_back(0);
	}
	for(int i=0;i<n;i++) ans[i][i]=1;
	while(b>0){
		if(b%2==1) ans=ans*a;
		a=a*a;
		b/=2;
	}
	return ans;
}
const matrix m1={{0,1},{1,1}},
             m2={
                	{1,0,1,0,0,0,0,0,0},
                	{0,1,0,0,0,0,0,0,0},
                	{1,0,0,0,0,0,0,0,0},
                	{0,2,0,1,0,1,0,0,0},
                	{1,0,0,0,1,0,0,0,0},
                	{0,0,0,1,0,0,0,0,0},
                	{1,0,0,0,2,0,1,0,1},
                	{0,0,0,1,0,0,0,1,0},
                	{0,0,0,0,0,0,1,0,0}
			    };
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif  
    int t=readint();
    while(t--){
    	int n=readint();
    	ll ans=ksm(m2,n)[6][0];
    	matrix res=ksm(m1,n);
    	ans=(ans+mod-(res[0][0]+res[0][1])%mod*n%mod)%mod;
    	printf("%d\n",(int)ans);
	}
    return 0;
}
```
这个算法其实是有优化的余地的，比如 $j=0,k=1$ 的状态就完全没有必要保留。但是我懒，所以就不写了。

---

## 作者：crashed (赞：4)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5303)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这道题......好像本来应该很水的样子......  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~我就是做不来~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;好吧。这道题不难让我们联想到一个经典的问题，也就是没有碎砖的问题。考虑按照相同的方法来尝试推出这个问题的递推式子：    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i)$：$2\times i$的格子铺满的方案数。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;三种转移：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$1.$最后一列直接铺一块$1\times 2$的砖：  
$$f(i)=f(i-1)+...$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$2.$倒数两列铺两块$1\times 2$的砖：  
$$f(i)=f(i-1)+f(i-2)+...$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$3.$考虑在最后一列铺上$1\times 1$的砖。两块砖必须同时铺上才可以保证可以铺满。如果一块$1\times 1$的砖铺在了最后一列，那么另外一块只能铺在$1\sim i-2$的位置。设不用碎砖的铺满前$i$列的方案数为$g(i)$，则有：  
$$f(i)=f(i-1)+f(i-2)+2\sum_{j=0}^{i-3}g(j)$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难发现$g$就是$Fibonacci$数列（$g(0)=1,g(1)=1$）。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到$n$这么大，转移又这么简洁，我们就可以想到矩阵加速。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设计一个$1\times 5$的初始矩阵和$5\times5$的转移矩阵，具体细节略。然后就可以$O(5^3T\log_2n)$了。  
# 代码
```cpp
#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;
const int MAXN = 1e5 + 5, MAXSIZ = 10;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
   	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct matrix
{
	int mat[MAXSIZ][MAXSIZ];
	int n, m;
	matrix(){ memset( mat, 0, sizeof mat ); }
	matrix( const int N, const int M ) { n = N, m = M, memset( mat, 0, sizeof mat ); }
	int* operator [] ( const int indx ) { return mat[indx]; }
	matrix operator * ( matrix other ) const
	{
		matrix ret = matrix( n, other.m );
		for( int i = 1 ; i <= ret.n ; i ++ )
			for( int j = 1 ; j <= ret.m ; j ++ )
				for( int k = 1 ; k <= m ; k ++ )
					ret[i][k] = ( ret[i][k] + 1ll * mat[i][j] * other[j][k] % mod ) % mod;
		return ret;
	}
}A, B;

int N;

matrix I( const int n )
{
	matrix ret = matrix( n, n );
	for( int i = 1 ; i <= n ; i ++ ) ret[i][i] = 1;
	return ret;
}

matrix qkpow( matrix base, int indx )
{
	matrix ret = I( base.n );
	while( indx )
	{
		if( indx & 1 ) ret = ret * base;
		base = base * base, indx >>= 1;
	}
	return ret;
}

void init()
{
	A = matrix( 1, 6 );
	A[1][1] = A[1][2] = 0, A[1][3] = A[1][4] = A[1][5] = 1;
    //前两个为f(i)和f(i-1)，第三个为∑g(0~i-3)，后两个为g(i-2)和g(i-3)
	B = matrix( 5, 5 );
	B[1][1] = 1, B[1][2] = 1;
	B[2][1] = 1;
	B[3][1] = 2, B[3][3] = 1;
	B[4][3] = 1, B[4][4] = 1, B[4][5] = 1;
	B[5][4] = 1;
}

int cal( const int n )
{
	if( n < 3 ) return 0;
	matrix part = qkpow( B, n - 2 );
	return ( A * part )[1][1];
}

int main()
{
	init();
	int T;
	read( T );
	while( T -- )
	{
		read( N );
		write( cal( N ) ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：xht (赞：4)


题目地址：[P5303 [GXOI/GZOI2019]逼死强迫症](https://www.luogu.org/problemnew/show/P5303)

这里是官方题解

## 初步分析

从题目和数据范围很容易看出来这是一个递推 + 矩阵快速幂，那么主要问题在于递推的过程。

满足条件的答案一定是以下的形式，设 $k = n - 1$ ，左右两边为整齐的道路，中间为长度 $p(p \geq 3)$ 的组合块：

![](https://cdn.luogu.com.cn/upload/pic/56828.png)

由 $p$ 的奇偶性，可以得到两种不同的基本图形，即 $1 \times 1$ 的小块在同一行（ $p$ 是偶数）和各占一行（ $p$ 是奇数）。

## 数学方法

左右均为普通的铺地板问题，可以用斐波那契数列表示，通过上下翻转可以得到两种不同的中间块方案，于是答案可以表示为：

$$F_k = 2 \sum_{p=3}^{n}\ \sum_{m=p}^{n}\ f_{k-m}\ f_{m-p+1}$$

其中 $f$ 为斐波那契数列。

转化为母函数可得：

$$\sum_{k=0}^{\infty}\ x^n\ F_k = \frac{2x^3}{(1-x)(1-x-x^2)^2}$$

## DP方法

思考如何构造方案，在 $p = 3$ 时，有两个无法分割的排列（想一想，哪两个？），其余方案可以通过在中心块一侧加入一个竖向的 $1 \times 2$ 地砖或者两个横向的 $1 \times 2$ 地砖组成的方形获得。答案就是上述方案的所有排列数之和。

### 问题转化

为了更好的求解问题，将所有方案放在一棵树上，称之为“方案树”，用 $T$ 表示。具体而言，在树上 **level** $q$ 的每个节点放入 $q$ 个配置，这些配置可以把方案拆解为 $q$ 块可以循环排列的结构。用这种方法，每个节点的 **level** 数就代表该层节点的整体重复次数。那么我们的目的就是构造这样一棵树，然后求每个节点到达根节点的距离和。

![](https://cdn.luogu.com.cn/upload/pic/56829.png)

### 构建方案树

方案树本身的递推关系可以通过如下的方式获得：

1. 在 $T_{k-1}$ 的 **level** $(q - 1)$ 的每个节点末端放一个竖向的 $1 \times 2$ 地砖。按这样的规则把新的节点从左到右放到 $T_n$ 的 **level** $q$ 的节点上。
2. 在 $T_{k-2}$ 的 **level** $(q - 1)$ 的每个节点末端放两个横向的 $1 \times 2$ 地砖组成的方形。按这样的规则把新的节点从左到右放入 $T_n$ 的 **level** $q$ 的其余节点上。

### 斐波那契树

这样抽象之后，我们得到了一棵“斐波那契树”：初始 $T_0$ 和 $T_1$ 是两棵单点树，对于所有的 $k(k \geq 2)$ ， $T_k$ 的左子树是 $T_{k-1}$ ，右子树是 $T_{k-2}$ 。我们的问题就转化成了对于每一个 $n$，求 $T_k$ 上所有节点到根节点的距离之和。

将 $T_{k-1}$ 放入 $T_k$ 的左子树中时， $T_{k-1}$ 的所有节点深度加深一层，那么左子树的答案就是原本的解 $F_{k-1}$ 与 $T_{k-1}$ 的节点个数 $N_{k-1}$ 之和。同理，右子树的答案就是原本的解 $F_{k-2}$ 与 $T_{k-2}$ 的节点个数 $N_{k-2}$ 之和。得到 **DP** 方程如下：

$$N_0 = N_1 = 1, N_k = N_{k-1} +N_{k-2} + 1(k \geq 2)$$

$$F_0 = F_1 = 0, F_k = F_{k-1} + F_{k-2} + N_{k-1} +N_{k-2}(k \geq 2)$$

其对应的矩阵如下：

![](https://cdn.luogu.com.cn/upload/pic/56817.png)

把这个矩阵拿去就可以用矩阵快速幂直接得到答案了。

### Further more

递推方程如果进一步化简可以得到：

$$F_0 = F_1 = 0, F_k = F_{k - 1} + F_{k - 2} + 2f_n - 2 (k \geq 2)$$

其中 $f$ 为斐波那契数列。

同样可以用于本问题的求解。

## std

这里提供两份

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 5;
const int MOD = 1e9 + 7;

struct Matrix {
	int n, m;
	long long a[MAXN][MAXN];
	Matrix(int _n, int _m) : n(_n), m(_m) {
		memset(a, 0, sizeof(a));
	}

	friend Matrix operator*(const Matrix &x, const Matrix &y) {
		Matrix ans = Matrix(x.n, y.m);
		for (int i = 0; i < ans.n; ++i) {
			for (int j = 0; j < ans.m; ++j) {
				for (int k = 0; k < x.m; ++k) {
					ans.a[i][j] += x.a[i][k] * y.a[k][j] % MOD;
					ans.a[i][j] %= MOD;
				}
			}
		}
		return ans;
	}
};

Matrix qpow(Matrix a, int pow) {
	Matrix ans = Matrix(a.n, a.m);
	for (int i = 0; i < ans.n; i++) {
		ans.a[i][i] = 1;
	}
	for (; pow; pow >>= 1) {
		if (pow & 1) {
			ans = ans * a;
		}
		a = a * a;
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while (T--) {
		int n;
		cin >> n;
		if (n == 1 || n == 2) {
			cout << 0 << endl;
			continue;
		}
		n--;
		Matrix f = Matrix(1, 5);
		f.a[0][2] = f.a[0][3] = f.a[0][4] = 1;
		Matrix fuck = Matrix(5, 5);
		fuck.a[0][0] = fuck.a[1][0] = fuck.a[2][0] = fuck.a[3][0] = 1;
		fuck.a[0][1] = fuck.a[2][2] = fuck.a[3][2] = fuck.a[4][2] = 1;
		fuck.a[2][3] = fuck.a[4][4] = 1;
		Matrix ans = f * qpow(fuck, n - 1);
		cout << ans.a[0][0] << endl;
	}
	return 0;
}
```

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
int a[27][27], f[27][27];
int n, mod = 1000000007;

int num(int x, int y, int z) {
	return x * 9 + y * 3 + z;
}

void mul(int a[27][27], int b[27][27]) {
	int c[27][27];
	memset(c, 0, sizeof(c));
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 27; j++)
			for (int k = 0; k < 27; k++)
				c[i][j] = (c[i][j] + (long long)a[i][k] * b[k][j]) % mod;
	memcpy(a, c, sizeof(c));
}

int main() {
	for (int z = 0; z < 3; z++) {
		a[num(0, 0, z)][num(0, 0, z)] = 1;
		a[num(0, 0, z)][num(1, 1, z)] = 1;
		if (z < 2) a[num(0, 0, z)][num(1, 2, z + 1)] = 1;
		if (z < 2) a[num(0, 0, z)][num(2, 1, z + 1)] = 1;

		a[num(0, 1, z)][num(1, 0, z)] = 1;
		if (z < 2) a[num(0, 1, z)][num(2, 0, z + 1)] = 1;

		a[num(0, 2, z)][num(0, 0, z)] = 1;
		a[num(0, 2, z)][num(1, 1, z)] = 1;
		if (z < 2) a[num(0, 2, z)][num(2, 1, z + 1)] = 1;

		a[num(1, 0, z)][num(0, 1, z)] = 1;
		if (z < 2) a[num(1, 0, z)][num(0, 2, z + 1)] = 1;

		a[num(1, 1, z)][num(0, 0, z)] = 1;

		a[num(1, 2, z)][num(0, 1, z)] = 1;

		a[num(2, 0, z)][num(0, 0, z)] = 1;
		a[num(2, 0, z)][num(1, 1, z)] = 1;
		if (z < 2) a[num(2, 0, z)][num(1, 2, z + 1)] = 1;

		a[num(2, 1, z)][num(1, 0, z)] = 1;
	}
	f[0][num(0, 0, 0)] = 1;

	cin >> n;
	for (; n; n >>= 1) {
		if (n & 1) mul(f, a);
		mul(a, a);
	}
	cout << ((f[0][num(0, 0, 2)] + f[0][num(0, 2, 2)]) % mod + f[0][num(2, 0, 2)]) % mod << endl;
}
```

---

## 作者：mango09 (赞：3)

[P5303 [GXOI/GZOI2019]逼死强迫症](https://www.luogu.com.cn/problem/P5303)

## Preface

矩阵题的登峰造极之作。

## Description

有 $T$ 组数据。

对于每组数据，给定正整数 $N$，请求出用 $(N-1)$ 个 $2\times 1$ 的方格和 $2$ 个 $1\times 1$ 的方格铺满 $2\times N$ 的大方格的方案数，**其中 $2$ 个 $1\times 1$ 的方格不能有相邻的边**。

- 答案对 $10^9+7$ 取模。
- 对于 $100\%$ 的数据，$N\le 2\times 10^9,T\le 500$。

## Solution

**前置芝士：**

- 一定的小奥基础
- 矩阵快速幂

### 第一部分：何为所求

这两个 $1\times 1$ 一定能框出一个 $2\times m$ 的长方形，其中因为不能相邻，所以 $m\ge 3$。

考虑这 $2$ 个 $1\times 1$ 的摆放位置：同行或异行。

举个例子：

当 $m$ 为偶数时：

![](https://cdn.luogu.com.cn/upload/image_hosting/v9if19e5.png)

同行是可以的，而且这个长方形内只有 $1$ 种方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/jkivdx16.png)

异行是不行的。

当 $m$ 为奇数时：

![](https://cdn.luogu.com.cn/upload/image_hosting/tzr5l954.png)

异行是可以的，而且这个长方形内只有 $1$ 种方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/u77u4bdx.png)

同行是不行的。

综上可以发现无论 $m$ 的奇偶性，框出的 $2\times m$ 有且仅有一种方法。

是吗？

因为 $2$ 个小正方形的位置可以上下调换，所以这两种都需要乘 $2$。

再考虑全部：

![](https://cdn.luogu.com.cn/upload/image_hosting/21yyk8ro.png)

左右两边都是形如 $2\times k$ 的长方形，根据小学奥数可知用 $k$ 个 $2\times 1$ 的覆盖 $2\times k(k\in\mathbf{N})$ 的有 $F_k$ 种（其中 $\{F_k\}$ 为斐波那契数列，下标从 $0$ 开始）。

确定了两边的 $i,j$，中间的 $m$ 就自动确定了。

中间是 $2$ 个 $1\times 1$ 的框出的长方形，有 $2$ 种方法，又 $m\ge 3$，所以
$$
\begin{aligned}
ans
&=2\sum\limits_{i=0}^{n-3}\sum\limits_{j=0}^{n-i-3} F_i\cdot F_j\\
&=2\sum\limits_{i=0}^{n-3}F_i\sum\limits_{j=0}^{n-i-3}F_j
\end{aligned}
$$
### 二、推式子

根据斐波那契数列的前缀和 $\sum\limits_{i=0}^n F_i=F_{n+2}-1$，有
$$
\begin{aligned}
ans
&=2\sum\limits_{i=0}^{n-3}F_i\sum\limits_{j=0}^{n-i-3}F_j\\
&=2\sum\limits_{i=0}^{n-3}F_i\cdot (F_{n-i-1}-1)\\
&=2\sum\limits_{i=0}^{n-3}(F_i\cdot F_{n-i-1}-F_i)\\
&=2(\sum\limits_{i=0}^{n-3}F_i\cdot F_{n-i-1}-\sum\limits_{i=0}^{n-3}F_i)\\
&=2(\sum\limits_{i=0}^{n-3}F_i\cdot F_{n-i-1}-(F_{n-1}-1))\\
&=2(1-F_{n-1}+\sum\limits_{i=0}^{n-3}F_i\cdot F_{n-i-1})
\end{aligned}
$$
令 $S_n=\sum\limits_{i=0}^n F_n\cdot F_{n-i}$，则
$$
\begin{aligned}
ans
&=2(1-F_{n-1}+\sum\limits_{i=0}^{n-3}F_i\cdot F_{n-i-1})\\
&=2[1-F_{n-1}+(\sum\limits_{i=0}^{n-1}F_i\cdot F_{n-i-1}-F_{n-2}\cdot F_1-F_{n-1}\cdot F_0)]\\
&=2(1+S_{n-1}-2F_{n-1}-F_{n-2})
\end{aligned}
$$
现在的问题就是如何求出 $S_n$。
$$
\begin{aligned}
S_n
&=\sum\limits_{i=0}^n F_n\cdot F_{n-i}\\
&=F_n\cdot F_0+F_{n-1}\cdot F_1+\sum\limits_{i=0}^{n-2}F_i\cdot F_{n-i}\\
&=F_n+F_{n-1}+\sum\limits_{i=0}^{n-2}F_i\cdot (F_{n-i-1}+F_{n-i-2})\\
&=F_n+(F_{n-1}\cdot F_0+\sum\limits_{i=0}^{n-2}F_i\cdot F_{n-i-1})+\sum\limits_{i=0}^{n-2}F_i\cdot F_{n-i-2}\\
&=F_n+\sum\limits_{i=0}^{n-1}F_i\cdot F_{n-i-1}+\sum\limits_{i=0}^{n-2}F_i\cdot F_{n-i-2}\\
&=F_{n-1}+F_{n-2}+S_{n-1}+S_{n-2}
\end{aligned}
$$
可以用矩阵快速幂解决：
$$
\begin{cases}
S_n&=1\cdot S_{n-1}+1\cdot S_{n-2}+1\cdot F_{n-1}+1\cdot F_{n-2}\\
S_{n-1}&=1\cdot S_{n-1}+0\cdot S_{n-2}+0\cdot F_{n-1}+0\cdot F_{n-2}\\
F_{n}&=0\cdot S_{n-1}+0\cdot S_{n-2}+1\cdot F_{n-1}+1\cdot F_{n-2}\\
F_{n-1}&=0\cdot S_{n-1}+0\cdot S_{n-2}+1\cdot F_{n-1}+0\cdot F_{n-2}
\end{cases}
$$
那么矩阵就是
$$
\begin{bmatrix}
1 & 1 & 1 & 1\\
1 & 0 & 0 & 0\\
0 & 0 & 1 & 1\\
0 & 0 & 1 & 0
\end{bmatrix}
\times
\begin{bmatrix}
S_{n-1}\\
S_{n-2}\\
F_{n-1}\\
F_{n-2}
\end{bmatrix}
=
\begin{bmatrix}
S_n\\
S_{n-1}\\
F_n\\
F_{n-1}
\end{bmatrix}
$$
初始值为
$$
\begin{bmatrix}
S_1\\
S_0\\
F_1\\
F_0
\end{bmatrix}
=
\begin{bmatrix}
2\\
1\\
1\\
1
\end{bmatrix}
$$
$ans=2(1+S_{n-1}-2F_{n-1}-F_{n-2})$，所以求 $S_{n-1}$ 乘 $(n-2)$ 次转移矩阵即可。

**时间复杂度为 $O(T\cdot 64\log n)$。**

## Code

```cpp
//18 = 9 + 9 = 18.
#include <iostream>
#include <cstdio>
#include <cstring>
#define Debug(x) cout << #x << "=" << x << endl
#define int long long
using namespace std;

struct matrix
{
	int a[5][5];
	matrix()
	{
		memset(a, 0, sizeof(a));
	}
	void build()
	{
		for (int i = 1; i <= 4; i++)
		{
			a[i][i] = 1;
		}
	}
};

const int MOD = 1e9 + 7;

matrix operator *(matrix x, matrix y)
{
	matrix res;
	for (int k = 1; k <= 4; k++)
	{
		for (int i = 1; i <= 4; i++)
		{
			if (!x.a[i][k])
			{
				continue;
			}
			for (int j = 1; j <= 4; j++)
			{
				res.a[i][j] = (res.a[i][j] + x.a[i][k] * y.a[k][j] % MOD) % MOD;
			}
		}
	}
	return res;
}

matrix qpow(matrix a, int b)
{
	matrix base = a, ans;
	ans.build();
	while (b)
	{
		if (b & 1)
		{
			ans = ans * base;
		}
		base = base * base;
		b >>= 1;
	}
	return ans;
}

signed main()
{
	int t;
	scanf("%lld", &t);
	matrix base;
	base.a[1][1] = base.a[1][2] = base.a[1][3] = base.a[1][4] = base.a[2][1] = base.a[3][3] = base.a[3][4] = base.a[4][3] = 1; //转移矩阵
	matrix fst;
	fst.a[1][1] = 2, fst.a[2][1] = fst.a[3][1] = fst.a[4][1] = 1; //初始矩阵
	while (t--)
	{
		int n;
		scanf("%lld", &n);
		if (n == 1)
		{
			puts("0");
			continue;
		}
		matrix res = qpow(base, n - 2) * fst;
		int S = res.a[1][1], F1 = res.a[3][1], F2 = res.a[4][1]; //S : S_{n-1}, F1 : F_{n-1}, F2 : F_{n-2}
		printf("%lld\n", (((1 + S - (F1 << 1) - F2) << 1) % MOD + MOD) % MOD);
	}
	return 0;
}
```

## Reference

- [1] Great_Influence：[题解 P5303 【[GXOI/GZOI2019]逼死强迫症】](https://www.luogu.com.cn/blog/user7035/solution-p5303)
- [2] StudyingFather：[[洛谷 5303,loj 3086][GXOI/GZOI2019]逼死强迫症](https://studyingfather.com/archives/2935)

---

## 作者：Rainybunny (赞：3)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.com.cn/problem/P5303).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难想到$50pts$的暴力.
## $50pts$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;关键在于两个$1\times1$砖中间的位置, 显然, 中间的$1\times2$砖是不能竖着防止的. 否则, 就会使左右部分都只剩下奇数个空位, 不可能完成任务.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;那么, 被夹在这两块砖中间的部分就只有两种方案, 左右就都是普通的情况. 所以可以先求出斐波那契数列$F_n$及其前缀和$S_n$, 枚举左侧砖的位置, 求得答案:
$$
Ans=\sum_{i=1}^{n-2}F_{i-1}S_{n-i-2}
$$
## $100pts$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们把$50pts$的思路向矩阵加速靠拢. 记$f(i)$为$n=i$时的答案, 那么:
$$
f(i)=f(i-1)+f(i-2)+2S_{i-3}
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;推一下式子, 就可以发现斐波那契数列的前缀和$S_n=F_{n+2}-1$. 所以将上式变成:
$$
f(i)=f(i-1)+f(i-2)+2F_{i-1}-2
$$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;矩阵加速. ( 可以, 这题很黑$qwq$. )
## 代码 ( $100pts$ )
```cpp
#include <cstdio>
#include <assert.h>

#define Int register int

const int MOD = 1e9 + 7;

class Matrix {
private:
	int n, m, mat[10][10];

public:
	Matrix ( const int tn, const int tm ): n ( tn ), m ( tm ) {
		for ( Int i = 1; i <= n; ++ i ) for ( Int j = 1; j <= m; ++ j ) mat[i][j] = 0;
	}
	inline int Getn () { return n; }
	inline int Getm () { return m; }
	inline int* operator [] ( const int Key ) { return mat[Key]; }
	inline void SetUnit () {
		assert ( n == m );
		for ( Int i = 1; i <= n; ++ i ) for ( Int j = 1; j <= n; ++ j ) mat[i][j] = i == j;
	}
	friend inline Matrix operator * ( Matrix a, Matrix b ) {
		assert ( a.m == b.n );
		Matrix ret ( a.n, b.m );
		for ( Int i = 1; i <= ret.n; ++ i ) {
			for ( Int k = 1; k <= a.m; ++ k ) {
				for ( Int j = 1; j <= ret.m; ++ j ) {
					ret[i][j] = ( ret[i][j] + 1LL * a[i][k] * b[k][j] % MOD ) % MOD;
				}
			}
		}
		return ret;
	}
} S ( 5, 5 );

inline Matrix MatPower ( Matrix A, int k ) {
	Matrix ret ( A.Getn (), A.Getm () ); ret.SetUnit ();
	for ( ; k; A = A * A, k >>= 1 ) if ( k & 1 ) ret = ret * A;
	return ret;
}

inline void Work () {
	S[1][1] = S[1][2] = S[2][1] = S[3][3] = S[3][4] = S[4][3] = S[5][5] = 1;
	S[3][1] = 2, S[5][1] = MOD - 2;
	int T; scanf ( "%d", &T );
	for ( int n; T --; ) {
		scanf ( "%d", &n );
		if ( n < 3 ) { puts ( "0" ); continue; }
		Matrix A ( 1, 5 );
		A[1][3] = 2, A[1][4] = A[1][5] = 1;
		printf ( "%d\n", ( A * MatPower ( S, n - 2 ) )[1][1] );
	}
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：hl666 (赞：3)

~~怎么还有这么SB的省选题啊~~

首先容易想到枚举右边的一个$1\times 1$的小方块所在的列$i$，然后暴枚左边小方块所在的列$j$在哪里，然后我们发现所有$j\in [1,i-1)$的列都**有且仅有**一种选择，具体和两者纵坐标的差值有关，画个图就知道了

然后每一对$i,j$的贡献是多少呢，很简单，显然在$[i,j]$之间的列只有唯一的放置方案，那么要乘上的系数就是两边$2\times (i-1)$和$2\times (n-j)$大小的放法了

我们令$2\times i$大小的放置方案为$f_i$，考虑每次在右边放，要么是竖着从$f_{i-1}$转移而来，要么是横着放两个从$f_{i-2}$转移来，因此这就是一个**斐波那契数列**

然后考虑前面那个暴力的思路，我们预处理出$f_i$和$f_i$的前缀和$s_i$即可拿到50pts（注意右边的有上下两种方法互相等价，因此要$\times 2$）

50pts暴力代码

```cpp
#include<cstdio>
#define RI register int
using namespace std;
const int N=1e5+5,mod=1e9+7;
int t,n,ans,fib[N],sum[N];
inline void init(void)
{
	sum[0]=fib[0]=fib[1]=1; for (RI i=sum[1]=2;i<N;++i)
	fib[i]=(fib[i-2]+fib[i-1])%mod,sum[i]=(sum[i-1]+fib[i])%mod;
}
int main()
{
	for (scanf("%d",&t),init();t;--t)
	{
		RI i; for (scanf("%d",&n),ans=0,i=3;i<=n;++i)
		(ans+=2LL*sum[i-3]*fib[n-i]%mod)%=mod; printf("%d\n",ans);
	}
	return 0;
}
```

然后我们再用类似$f_i$的推导方式推导答案$F_i$，考虑如何从之前的状态转移而来

很容易用一样的思路得到，如果之前$i-1$列没有放$1\times 1$的小方块，那么$F_i$可以从$F_{i-1}$和$F_{i-2}$转移来

如果放了呢，那么其实就是上面暴力的转移过程，因为我们此时在第$i$列的放法唯一，因此系数就是$1$

所以综合一下就有$F_i=F_{i-2}+F_{i-1}+2\times s_{i-3}$，然后用斐波那契数列前缀和的性质$s_i=f_{i+2}-1$即可推出$F_i=F_{i-2}+F_{i-1}+2\times f_{i-1}-2$

直接矩阵快速幂维护转移的$5$个值（有一个是常数项），复杂度$O(T\times 5^3\times \log n)$

100pts矩乘CODE

```cpp
#include<cstdio>
#include<cstring>
#define RI register int
#define CI const int&
using namespace std;
const int N=5,mod=1e9+7;
struct Matrix
{
    int n,m; long long mat[N][N];
    inline Matrix(CI N=0,CI M=0) { n=N; m=M; memset(mat,0,sizeof(mat)); }
    inline long long* operator [] (CI x) { return mat[x]; }
    friend inline Matrix operator * (Matrix A,Matrix B)
    {
        Matrix C(A.n,B.m); for (RI i=0;i<C.n;++i)
        for (RI j=0;j<C.m;++j) for (RI k=0;k<A.m;++k)
        (C[i][j]+=A[i][k]*B[k][j])%=mod; return C;
    }
    friend inline Matrix operator ^ (Matrix A,long long p)
    {
        Matrix T(A.n,A.m); for (RI i=0;i<A.n;++i) T[i][i]=1;
        for (;p;p>>=1LL,A=A*A) if (p&1) T=T*A; return T;
    }
}; int t,n;
int main()
{
    for (scanf("%d",&t);t;--t)
    {
        scanf("%d",&n); if (n<=2) { puts("0"); continue; }
        Matrix S(5,1),D(5,5); S[2][0]=S[3][0]=1; S[4][0]=2;
        D[0][0]=D[0][1]=D[1][0]=D[2][2]=D[2][3]=D[3][2]=D[4][4]=1;
        D[0][2]=2; D[0][4]=mod-1; S=(D^(n-1))*S; printf("%d\n",S[0][0]);
    }
    return 0;
}
```



---

## 作者：GreenDay (赞：2)

这是一道数学必修五的好题（

大家都是用矩阵快速幂做的，这里有一种比较清真而纯粹的数学做法。

---

首先，我们知道，**用$2*1$的骨牌贴满$2*N$的方格，方案数是$fib_{N+1}$** ,其中$fib$表示斐波那契数列。

这个可以由比较相应的递推式得到。

----

若我们在第$i$列放了一个$1*1$的方块，我们枚举另一个$1*1$方块放在$j$处。容易发现：(不妨设$j>i$)

- $j\ge i+2$(否则不合法)

- 当$j-i\equiv 0 \mod2$时，$j$需要和$i$放在不同行；反之应该放在同一行。(否则$[i,j]$之间没有方案)

- $[i,j]$的列之间有唯一的贴瓷砖方法，$i$左侧，$j$右侧方案独立，即“用$2*1$的骨牌贴满$2*N$的方格”的情况，分别是$fib_i$和$fib_{n-j+1}$.

我们立刻得到：

$$ans=2\sum\limits_{i=1}^{n-2}fib_i\sum\limits_{j=1}^{n-i-1}fib_j$$

看作是枚举两个特殊瓷砖铺在哪两列（当然注意行上的情况有两种，所以最后答案要*2）。这样就可以$O(T*n)$得50分了。

我们利用斐波那契数列的性质继续往下推：

$$\sum_{i=1}^n fib_{i}=fib_{n+2}-1$$
$$fib_i=\frac{1}{\sqrt{5}}((\frac{1+\sqrt{5}}{2})^i-(\frac{1-\sqrt{5}}{2})^i)$$

第一个式子可以用数学归纳法证明，第二个式子可以用生成函数/待定系数等一些列方法证明（你可以用搜索引擎搜索一下这两个性质）。

把这两个式子暴力带进去，发现答案仅仅是由**等比数列求和** 和 **常数项** 的形式组成。使用**拓域**，用$a+b\sqrt{5}$表示一个数，实现基本运算即可（这是因为5在模意义下没有二次剩余）。$O(T\log n)$

```cpp
#include <iostream>
using namespace std;

const int mod = 1e9 + 7;
typedef long long i64;

i64 qpow(i64 x , i64 y = mod - 2) {
    i64 z = 1;
    for( ; y ; y >>= 1 , x = x * x % mod) if(y & 1) z = z * x % mod;
    return z;
}

template<int T> struct Comp {
    int x , y;
    Comp(int x = 0, int y = 0) : x(x) , y(y) {}
};

template<int T> Comp<T> operator+ (Comp<T> a , Comp<T> b) {return Comp<T>((a.x+b.x)%mod , (a.y+b.y)% mod);}
template<int T> Comp<T> operator- (Comp<T> a , Comp<T> b) {return Comp<T>((a.x-b.x+mod)%mod , (a.y-b.y+mod)%mod);}
template<int T> Comp<T> operator* (Comp<T> a , Comp<T> b) {return Comp<T>((1ll*a.x*b.x+1ll*T*a.y%mod*b.y)%mod , (1ll*a.x*b.y+1ll*a.y*b.x)%mod);}
template<int T> Comp<T> operator* (Comp<T> a , i64 b) {return Comp<T>(a.x*b%mod ,a.y*b%mod);}
template<int T> Comp<T> operator~ (Comp<T> a) {return Comp<T>(a.x , (mod-a.y)%mod) * qpow(((1ll*a.x*a.x-1ll*T*a.y%mod*a.y)%mod+mod)%mod); }
template<int T> Comp<T> operator/ (Comp<T> a , Comp<T> b) {return a*(~b);}
template<int T> Comp<T> operator^ (Comp<T> a , i64 b) {
    Comp<T> x(1);
    for( ; b ; b >>= 1 , a = a * a) if(b & 1) x = x * a;
    return x;
}
template<int T> bool operator== (Comp<T> a , Comp<T> b) {return a.x==b.x&&a.y==b.y;}
template<int T> Comp<T> sum(Comp<T> a1 , Comp<T> q , i64 n) {
	Comp<T> _1(1);
    if(q == _1) return a1 * n;
    return a1 * (_1 - (q^n)) / (_1 - q);
}

const int Inv2 = mod - mod/2 , T = 800000006;
const Comp<5> a(Inv2 , Inv2) , b(Inv2 , mod - Inv2);
const Comp<5> ab = a/b , ba = b/a;

int solve(int n) {
    if(n < 3) return 0;
    Comp<5> an1 = a^(n+1) , bn1 = b^(n+1);
    return (((an1+bn1)*(n-2)-bn1*sum(ab,ab,n-2)-an1*sum(ba,ba,n-2))*T
            - (sum(a,a,n-2)-sum(b,b,n-2))*Comp<5>(0,T)).x;
}

int main() {
    int t , n;
    for(cin >> t ; t ; t--) cin >> n , cout << solve(n) << endl;
}
```

---

## 作者：ダ月 (赞：1)

### 题目分析：

首先，我们先考虑没有砖裂掉的情况，即用 $n$ 块 $2\times 1$ 的转填满 $2\times n$ 的道路。记 $f_i$ 为考虑到第 $i$ 列的方案数。我们可以在最后一列地方放上 $2\times 1$ 的砖块（竖着放），可以从 $f_{i-1}$ 转移过来。在最后两列地方放上两个 $1\times2$ 的砖块（横着放），可以从 $f_{i-2}$ 转移过来。所以 $f_i=f_{i-1}+f_{i-2}$，显然 $f_{0}=1,f_{1}=1$，依次往后，$f_i$ 为一个菲波那切数列。

好了，考虑有一块砖破碎的状态。首先，我们可以确定的是，假如两块 $1\times 1$ 的砖块位置已经确定的话，记左边 $1\times1$ 的列数为 $l$，右边为 $r$，则 $[l,r]$ 内所有的砖块位置确定下来。即 $[l,r]$ 内非 $1\times 1$ 的砖块只能横着放，且放置方案唯一。所以我们记 $g_i$ 为考虑到第 $i$ 列的方案数。首先，我们同理可以从 $g_{i-2}$ 和 $g_{i-1}$ 转移过来。其次，若这一列放置了右端 $1\times 1$ 的砖块，我们枚举左端 $1\times 1$ 的砖块，显然可以从 $f_{1\sim i-3}$ 转移过来。所以 $\begin{aligned}g_i=g_{i-1}+g_{i-2}+2\sum_{j=0}^{i-3}\end{aligned}f_{j}$，其中记 $\begin{aligned}\sum_{j=0}^{i-3}f_j=S_{i-3}\end{aligned}$。而 $S_i$ 的转移就是 $S_i=S_{i-1}+f_i$。

因为这些转移都是线性的，我们考虑矩阵快速幂，我们可以得到 $\begin{bmatrix}g_i\\g_{i-1}\\f_{i-1}\\f_{i-2}\\S_{i-3}\end{bmatrix}$ 转移矩阵为：$\begin{bmatrix}1&1&2&0&2\\1&0&0&0&0\\0&0&1&1&0\\0&0&1&0&0\\0&0&1&0&1\end{bmatrix}$。

初始矩阵为：$\begin{bmatrix}2\\0\\1\\1\\1\end{bmatrix}$。

时间复杂度：$O(k^3\log n)$，其中 $k$ 为矩阵大小，这里记作 $k=5$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd push_back
#define all(x) x.begin(),x.end()
#define Clear(x,n) for(int i=0;i<=n;i++)x[i]=0;
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10+'0');}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=1e5+10;
const int mod=1e9+7;
struct Matrix{
	ll a[6][6];
	int n,m;
	void init1(int c){memset(a,0,sizeof(a));n=m=c;for(int i=1;i<=n;i++)a[i][i]=1;}
	void init2(int _n,int _m,vector<int> c){
		assert(c.size()==_n*_m);
		n=_n,m=_m;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=c[(i-1)*m+j-1];
	}
	void init3(int _n,int _m){memset(a,0,sizeof(a));n=_n;m=_m;}
	Matrix operator *(const Matrix B){
		Matrix ans;ans.init3(n,B.m);
		assert(m==B.n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=B.m;j++)
				for(int k=1;k<=m;k++)
					ans.a[i][j]=(ans.a[i][j]+a[i][k]*B.a[k][j])%mod;
		return ans;
	}Matrix operator ^(int y){
		Matrix ans;assert(n==m);ans.init1(n);
		Matrix x=(*this);
		for(;y;y>>=1,x=x*x)if(y&1)ans=ans*x;
		return ans;
	}
};
Matrix Bas1,Bas2;
int T;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    scanf("%d",&T);
    while(T--){
    	ll n;scanf("%lld",&n);
    	Bas1.init2(5,5,{1,1,2,0,2,
						1,0,0,0,0,
						0,0,1,1,0,
						0,0,1,0,0,
						0,0,1,0,1});
		Bas2.init2(5,1,{2,
						0,
						1,
						1,
						1});
		if(n<=2){puts("0");continue;}
		Matrix ans=(Bas1^(n-3))*Bas2;
		printf("%lld\n",ans.a[1][1]);
	}return 0;
}


```


---

## 作者：Supor__Shoep (赞：1)

看到 $N\leq 2\times 10^9$ 的范围，一眼**矩阵快速幂优化 DP**。

首先考虑朴素 DP 怎么写。根据题目所给信息，我们设 $dp_{i,0}$ 表示前面 $i$ 个方砖，并且已经使用了 $2$ 个 $1\times 1$ 的方砖，$dp_{i,1}$ 则表示前面 $i$ 个方砖，**没有使用任何一个** $1\times 1$ 的方砖。

为了转移至 $dp_{i,0}$，既然已经使用过了 $2$ 个 $1\times 1$ 的方砖，那么我们剩下的都是 $1\times 2$ 的方砖，对于这样的方砖，我们有两种可行的摆放，一种是直接**竖着放**，可以由 $dp_{i-1,0}$ 转移得到；另一种是**两个横着放**，可以由 $dp_{i-2,0}$ 得到。而我们还可以在 $[1,i-3]$ 选择一个 $j$，然后利用后面的区间 $[j+1,i]$ 放置两个 $1\times 1$ 的方砖，且两个方砖放置的位置分别在第 $j+1$ 列和第 $i$ 列。而我们不难发现有两种情况，一种是这个区间长度为奇数，另一种是区间长度为偶数。

对于奇数长度的区间，我们可以让两个方砖放在**不同的行**，这里各自的行剩下的长度就是偶数（奇数减一是偶数），我们就每行横着放 $1\times 2$ 的方砖就可以了。而如果放在同一行，那么我们就无法填满里面的空缺（可以自己画图理解一下）。对于偶数长度的区间，我们可以让两个方砖在**同一行**，这样上下两行剩余的长度就都是偶数了，就可以横着放 $1\times 2$ 的方砖来填满空缺，反之如果是在不同的行，那么我们就不可以完成。

如果实在理解不了，我可以给一点提示，就是当区间两边填了 $1\times 1$ 的方砖后，那么对于所填方砖的另外一行，我们只可能使用 $1\times 2$ 的方砖填满那个 $1\times 1$ 的空缺，而此时又会产生新的 $1\times 1$ 的空缺……以此类推。（这样提示还不够，那我可能就帮不了你了。。）

总之我们可以发现，不管是放在**不同的行或者相同的行**，都会得到 $2$ 种答案。而且此时我们转移的是 $dp_{j,1}$，因为如果在 $[j+1,i]$ 放置两个裂开的砖块，那么 $[1,j]$ 肯定就是没有裂开的砖块的。

而我们的 $dp_{i,1}$ 就非常好转移了，就是要么竖着放，要么两个横着放，即 $dp_{i,1}=dp_{i-1,1}+dp_{i-2,1}$。

所以我们列出方程：

$$\begin{cases} dp_{i,0}=dp_{i-1,0}+dp_{i-2,0}+2\times \sum _{j=1}^{i-3}dp_{j,1}\\ dp_{i,1}=dp_{i-1,1}+dp_{i-2,1} \\\end{cases}$$

但是这样肯定是会超时的，所以就会想到使用**矩阵**。

但是我们又发现这个 $dp_{i,0}$ 的转移不是 $O(1)$ 的，所以考虑将方程进行改造。对于 $\sum _{j=1}^{i-3}dp_{j,1}$，我们不难发现每次 $i$ 增加 $1$，我们原来的值就会增加一个 $dp_{j,1}$ 的值。根据这个形式，我们就想到使用**前缀和**储存这个区间值。设 $sum_i$ 表示 $\sum_{j=1}^i dp_{j,1}$ 的值。原方程变为：

$$dp_{i,0}=dp_{i-1,0}+dp_{i-2,0}+2\times sum_{i-3}$$

我们将一次转移使用到的值提出来：$dp_{i-1,0}$，$dp_{i-2,0}$，$sum_{i-3}$，$dp_{i-1,1}$，$dp_{i-2,1}$。然后利用这些值构造初始矩阵：

$$
\left(
\begin{matrix}
dp_{i-1,0} & dp_{i-2,0} & dp_{i-1,1} & dp_{i-2,1} & sum_{i-3}
\end{matrix}
\right)
$$

换成具体的数值，真正的初始矩阵是：

$$
\left(
\begin{matrix}
0 & 0 & 2 & 1 & 1
\end{matrix}
\right)
$$

注意这个 $sum_0$ 是 $1$，因为放置 $0$ 个方砖也是一种答案。

每次转移按照上述方程进行转移，得到转移矩阵：

$$
\left(
\begin{matrix}
1 & 1 & 0 & 0 & 0\\
1 & 0 & 0 & 0 & 0\\
0 & 0 & 1 & 1 & 0\\
0 & 0 & 1 & 0 & 1\\
2 & 0 & 0 & 0 & 1
\end{matrix}
\right)
$$

所以得到答案为：

$$
\left(
\begin{matrix}
0 & 0 & 2 & 1 & 1
\end{matrix}
\right)
\times
\left(
\begin{matrix}
1 & 1 & 0 & 0 & 0\\
1 & 0 & 0 & 0 & 0\\
0 & 0 & 1 & 1 & 0\\
0 & 0 & 1 & 0 & 1\\
2 & 0 & 0 & 0 & 1
\end{matrix}
\right)
^{n-2}
$$

这样代码就非常简单了：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7;
long long n,p,q;
void mul(long long f[5],long long a[5][5])
{
    long long c[5];
    memset(c,0,sizeof(c));
    for(int j=0;j<5;j++)
    {
    	for(int k=0;k<5;k++)	c[j]=(c[j]+f[k]*a[k][j])%MOD;
	}
    memcpy(f,c,sizeof(c));
}
void mulself(long long a[5][5])
{
    long long c[5][5];
    memset(c,0,sizeof(c));
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)    c[i][j]=(c[i][j]+(long long)a[i][k]*a[k][j])%MOD;
        }
    }
    memcpy(a,c,sizeof(c));
}
signed main()
{
	long long T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		long long f[5]={0,0,2,1,1};
		long long a[5][5]={0};
		a[0][0]=a[0][1]=a[1][0]=a[2][2]=a[2][3]=a[3][2]=a[3][4]=a[4][4]=1,a[4][0]=2;
		if(n==1||n==2||!n)
		{
			puts("0");
			continue;
		}
		n-=2;
		while(n)
		{
			if(n&1)	mul(f,a);
			mulself(a);
			n>>=1;
		}
		cout<<f[0]<<endl;
	}
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：1)

## 前置知识

斐波那契数列

## 分析

首先，先放完两个 $1 \times 1$ 的块之后，中间的块就没有方法可以选了。然后，这两个块加起来的长度最少是 $3$，外面随便乱摆就可以了。然后就再把翻转的可能性加进去，就推出了式子：

$$ans = 2\sum\limits_{i = 0}^{n-3}F_i\sum\limits_{j=0}^{n-3-i}F_j$$

为了化简，我们需要知道的是斐波那契数列前缀和公式。前缀和公式很简洁，是：

$$\sum\limits_{i=0}^nF_i=F_{n+2}-1$$

证明可以找规律后数学归纳证明。

这东西就可以帮助我们化简上式

$$
\begin{aligned}
ans &= 2\sum\limits_{i = 0}^{n-3}F_i(F_{n-i-1}-1)\\
&= 2(\sum\limits_{i = 0}^{n-3}F_iF_{n-i-1}-\sum\limits_{i = 0}^{n-3}F_i)\\
&= 2(\sum\limits_{i = 0}^{n-3}F_iF_{n-i-1}-F_{n-1}+1)\\
\end{aligned}
$$

下一步，我们就需要找到化简 $\sum\limits_{i = 0}^{n-3}F_iF_{n-i-1}$ 的方法。

我们令 $S_n = \sum\limits_{i = 0}^nF_iF_{n-i}$。

$$
\begin{aligned}
S_n &= \sum\limits_{i = 0}^nF_iF_{n-i}\\
&= \sum\limits_{i = 2}^n(F_{i-1}+F_{i-2})F_{n-i}+F_1F_{n-1}+F_0F_n\\
&= \sum\limits_{i = 2}^nF_{i-1}F_{n-i}+\sum\limits_{i = 2}^nF_{i-2}F_{n-i}+F_1F_{n-1}+F_0F_n\\
&= S_{n-1}-F_0F_{n-1}+S_{n-2}+F_1F_{n-1}+F_0F_n\\
&= S_{n-1}+S_{n-2}+F_0F_n\\
&= S_{n-1}+S_{n-2}+F_n
\end{aligned}
$$

看上去很难搞。

但是发现这个形式，可以仿照斐波那契数列的矩阵快速幂做法。

于是找到一个矩阵：

$$
\left[
\begin{matrix}
0&1&0&0\\
1&1&0&0\\
0&0&0&1\\
1&1&1&1\\
\end{matrix}
\right]
$$

我们发现这个矩阵可以用来递推 $S_n$：

$$
\left[
\begin{matrix}
F_{n-2}\\
F_{n-1}\\
S_{n-2}\\
S_{n-1}\\
\end{matrix}
\right]
\left[
\begin{matrix}
0&1&0&0\\
1&1&0&0\\
0&0&0&1\\
1&1&1&1\\
\end{matrix}
\right]
=
\left[
\begin{matrix}
F_{n-1}\\
F_{n}\\
S_{n-1}\\
S_{n}\\
\end{matrix}
\right]
$$

于是，我们就可以用初始值矩阵快速幂后得出 $S_n$ 了，也可以算出答案了：


$$
\begin{aligned}
ans &= 2(\sum\limits_{i = 0}^{n-3}F_iF_{n-i-1}-F_{n-1}+1)\\
&= 2(S_{n-1}-F_{n-2}F_{1}-F_{n-1}F_0-F_{n-1}+1)\\
&= 2(S_{n-1}-F_{n-2}-F_{n-1}-F_{n-1}+1)\\
&= 2(S_{n-1}-2F_{n-2}-F_{n-2})\\
\end{aligned}
$$

然后就解决了

## 代码

```cpp
#include <bits/stdc++.h> 
#define lld long long 
using namespace std;
const lld mod = 1e9 + 7;
struct matrix {
	lld a[5][5];
	matrix() { memset(a, 0, sizeof(a)); }
	lld * operator [] (lld x) { return a[x]; }
};
matrix _unit;
matrix unit() {
	if (!_unit[1][1]) for (int i = 1; i <= 4; ++ i) _unit[i][i] = 1;
	return _unit;
}
matrix operator * (const matrix & a, const matrix & b) {
	matrix ret;
	for (int k = 1; k <= 4; ++ k)
		for (int i = 1; i <= 4; ++ i)
			for (int j = 1; j <= 4; ++ j)
				ret[i][j] = (ret[i][j] + a.a[i][k] * b.a[k][j]) % mod;
	return ret;
}
matrix qpow(matrix a, lld b) {
	matrix ret = unit();
	for (; b; b >>= 1, a = a * a)
		if (b & 1) ret = ret * a;
	return ret;
}
int t;
lld n;
int main() {
	scanf("%d", &t);
	matrix base;
	/* 拿来乘的矩阵 */
    base[1][1] = base[1][2] = base[1][3] = base[1][4] = 1;
	base[2][1]										  = 1;
							  base[3][3] = base[3][4] = 1;
							  base[4][3]			  = 1;
	matrix init;
	/* 初始矩阵 */
	init[1][1] = 2;
	init[2][1] = 1;
	init[3][1] = 1;
	init[4][1] = 1;
	while (t --) {
		scanf("%lld", &n);
		if (n <= 2) {
			puts("0");
			continue;
		}
		matrix res = qpow(base, n - 2) * init;
		lld Sn = res[1][1], Fn = res[3][1], Fn_1 = res[4][1]; // 顺便乘出结果 
        printf("%lld\n", (((1 + Sn - (Fn << 1) - Fn_1) << 1) + mod * 114514) % mod);
	}
}
```



---

## 作者：MLEAutoMaton (赞：1)

## 传送门
[Loj](https://loj.ac/problem/3086)

## Solution
比较简单.
考虑设$f_i$表示当$N$为$i$的时候的答案,$g_i$表示只用1\*2的铺满$2*i$格子的方案数.
有:$f_i=f_{i-1}+f_{i-2}+2*\sum_{j=1}^{i-3}g_j$
然后我们又知道斐波那契数列的前缀和$s_i$=$g_i+2$,直接矩阵快速幂就好了.

## 代码实现
```cpp
/*
  mail: mleautomaton@foxmail.com
  author: MLEAutoMaton
  This Code is made by MLEAutoMaton
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define ll long long
#define re register
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi()
{
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int Mod=1e9+7;
struct matrix
{
	int a[5][5];
}S,T;
matrix cheng(matrix a,matrix b)
{
	matrix c;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
		{
			c.a[i][j]=0;
			for(int k=0;k<5;k++)
				c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j]%Mod)%Mod;
		}
	return c;
}
int main()
{
	freopen("obsession.in","r",stdin);
	freopen("obsession.out","w",stdout);
	int Case=gi();
	while(Case--)
	{
		int n=gi();
		S.a[0][0]=0;S.a[0][1]=0;S.a[0][2]=1;S.a[0][3]=2;S.a[0][4]=2;
		
		T.a[0][0]=0;T.a[0][1]=1;T.a[0][2]=0;T.a[0][3]=0;T.a[0][4]=0;
		T.a[1][0]=1;T.a[1][1]=1;T.a[1][2]=0;T.a[1][3]=0;T.a[1][4]=0;
		T.a[2][0]=0;T.a[2][1]=0;T.a[2][2]=0;T.a[2][3]=1;T.a[2][4]=0;
		T.a[3][0]=0;T.a[3][1]=2;T.a[3][2]=1;T.a[3][3]=1;T.a[3][4]=0;
		T.a[4][0]=0;T.a[4][1]=Mod-1;T.a[4][2]=0;T.a[4][3]=0;T.a[4][4]=1;
		if(n==1){puts("0");continue;}
		n-=2;
		while(n)
		{
			if(n&1)S=cheng(S,T);
			T=cheng(T,T);n>>=1;
		}
		printf("%d\n",S.a[0][1]);
	}
	return 0;
}
```

---

## 作者：creation_hy (赞：0)

## 前言

一道不错的矩阵优化题。

## 思路

设 $f[i]$ 表示有 $i$ 列时候的方案数。

考虑几种情况：

- $i-1$ 列是平的。
   
  可以直接在后面加一个两行一列的瓷砖，即（蓝色代表新增部分）：
   
  ![](https://cdn.luogu.com.cn/upload/image_hosting/k19ffcyf.png)
   
  转移式：$f[i]+=f[i-1]$。

- $i-2$ 列是平的。

  多了一种方法：横铺。即：
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/dvoc6bau.png)
  
  转移式：$f[i]+=f[i-2]$。
  
- 放了 $1\times1$ 的方块：

  稍微麻烦一点。
  
  首先，方块只能在 $[1,i-2]$ 放，因为如果在 $i-1$ 放的话，它右面那个格子也只能放 $1\times1$ 的方块，连起来不符合题目要求。如果不放只能放在上面，右面用 $1\times2$，但是和上面连起来也不符合要求。
  
  其次，因为距离原因，每列的 $1\times1$ 方格只有一种放法。具体原因参考下图：
  
  偶数差（不同行）：
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/j3if31bf.png)
  
  奇数差（同行）：
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/7navddvv.png)
  
然后你又会发现一个事情：

前两种情况，$1\times1$ 方格在前面（已经考虑过）；

最后一种情况，前面没有 $1\times1$ 方格（只有两块）。

于是，前面两种情况直接用 $f$ 即可，最后一种要用一个不包含 $1\times1$ 方格的方案数，我们假设是 $g$。

于是就有：

$f[i]=f[i-1]+f[i-2]+2\times\displaystyle\sum_{j=1}^{i-3}g[i]$。

（为什么有个 $2$ 呢，虽然只有一种放法（同行或不同行），但是你可以选择第一个 $1\times1$ 瓷砖是哪一行的）

时间复杂度：$O(Tn^2)$

完了吗？怎么可能啊，数据范围这么大呢（

发现 $g$ 其实就是个斐波那契数列（其实 $g$ 就是不考虑第三种情况的 $f$）。

所以可以拿 $g[i-1]-1$ 代替 $\displaystyle\sum_{j=1}^{i-3}g[i]$（斐波那契数列基本性质）。

于是，式子优化为：

$f[i]=f[i-1]+f[i-2]+2\times (g[i-1]-1)$

时间复杂度：$O(Tn)$。

然后看了眼恐怖的范围……

想到了什么？

$O(\log n)$

然后呢？

矩阵快速幂优化。~~（想不到建议先多做几道）~~

最终时间复杂度：$O(T\log n)$，矩阵大小 $5$，乘法常数 $5^3=125$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
typedef long long ll;
int n;
struct Matrix
{
    ll a[5][5], r, c;
    inline Matrix()
    {
        memset(a, 0, sizeof(a));
    }
    inline Matrix(int x, int y)
    {
        r = x, c = y;
        memset(a, 0, sizeof(a));
    }
    inline Matrix(int x)
    {
        r = c = x;
        memset(a, 0, sizeof(a));
        for (int i = 0; i < 5; i++)
            a[i][i] = 1;
    }
    inline Matrix operator*(const Matrix &t) const
    {
        Matrix res(r, t.c);
        for (int i = 0; i < res.r; i++)
            for (int j = 0; j < res.c; j++)
                for (int k = 0; k < c; k++)
                    (res.a[i][j] += a[i][k] * t.a[k][j]) %= mod;
        return res;
    }
    inline Matrix operator^(ll k)
    {
        Matrix res(r), base = *this;
        while (k)
        {
            if (k & 1)
                res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Matrix A(5, 5);
    A.a[0][1] = A.a[1][0] = A.a[1][1] = A.a[2][3] = A.a[3][2] = A.a[3][3] = A.a[4][4] = 1;
    A.a[3][1] = 2;
    A.a[4][1] = mod - 1;
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        if (n <= 2)
        {
            cout << "0\n";
            continue;
        }
        Matrix B(1, 5);
        B.a[0][2] = 1;
        B.a[0][3] = B.a[0][4] = 2;
        Matrix tmp = A ^ (n - 2);
        B = B * tmp;
        cout << B.a[0][1] << '\n';
    }
    return 0;
}
```

---

## 作者：pengyule (赞：0)

拿到这题，第一想法是状压，用 $F_{i,j}$ 表示填满 $2\times i$ 的方格图的方案数，对于最后一列（第 $i$ 列），$j=0,1,2,3,4$ 分别表示：不填，左边填一个，右边填一个，两边各填一个，竖着放一个。这样我们就可以求出没有 $1\times 1$ 的砖块时填满的方案数为 $F_{n,0}+F_{n,4}$。那现在有分裂的砖啊！我们用 $dp_i$ 表示将其中一块 $1\times 1$ 的砖放在第 $i$ 列，另外一块放在 $1\sim i$ 列之间，恰好铺满 $2\times i$ 的区域的方案数。我们发现 $dp_{i-1}$ 已经帮 $dp_i$ 做了很大一部分工作，现在我们只需考虑如何转移。\
![图片.png](https://i.loli.net/2021/02/03/ewb9IZgyvz2OScH.png)\
我们发现当 $i-1$ 时填上棕色那块时，①②③三个块块我们是不会选择去用另一个 $1\times 1$ 填它的；那 $i$ 时是否可以填呢？我们发现 $i$ 时②块是可以填的，填上后增加的方案数为 $F_{i-3,0}+F_{i-3,4}$。因此转移方程为
$dp_{i}=dp_{i-1}+2(F_{n,0}+F_{n,4})$（乘2是因为翻过来又有一种情况）。多嘴一下，初始有 $dp_1=dp_2=0,dp_3=2,G_0=1$。我们奇妙地发现，$F_{n,0}+F_{n,4}=fib_{n+1}$，是斐波那契数列！而根据组合数学，我们最终的答案应该是 $\sum _{i=1}^n dp_i\times (F_{n-i,0}+F_{n-i,4})$。代码1：（用的是状压求 $F_0+F_4$）
[link](https://paste.ubuntu.com/p/jX33D6bCn6/)
Result: 50pts, TLE/RE.

然后我们把 $G_i=fib_{i+1}$ 代入得到了更糟的结果（20pts+3TLE+4RE），这里不展示代码了。

第二步，
$$dp_n=dp_{n-1}+2fib_{n-2}=dp_{n-2}+2fib_{n-3}+2fib_{n-2}=\cdots=2\sum_{i=1}^{n-2}fib_i=2(fib_n-1)$$
$$ ans=\sum _{i=1}^n dp_i\times fib_{n-i+1}=2 \sum_{i=1}^n (fib_i-1)\times fib_{n-i+1}=2\cdot(1+\sum_{i=1}^n fib_i\times fib_{n-i+1}-\sum_{i=1}^n fib_{n-i+1})=2\cdot(1-fib_{n+2}+\sum_{i=1}^n fib_i\times fib_{n-i+1})$$
代码2：[link](https://paste.ubuntu.com/p/2RbWR9cyDj/)

第三步，
令 $G_i=\sum_{i=1}^n fib_i\times fib_{n-i+1}$，则 $G_i=\sum_{i=1}^n fib_i\times fib_{n-i+1}=fib_n+\sum_{i=1}^{n-1} fib_i\times (fib_{n-i}+fib_{n-i+1}-fib_{n-i})=fib_n+\sum_{i=1}^{n-1} fib_i\times (fib_{n-i}+fib_{n-i-1})=fib_n+\sum_{i=1}^{n-1} fib_i\times fib_{n-i}+\sum_{i=1}^{n-2}fib_{(n-2)-i+1}=G_{n-1}+G_{n-2}+fib_n$。真是有种拨云见日的感觉！

有这个转移方程式，得到矩阵的转移式：
$$\begin{bmatrix}fib_{n-1} fib_n G_{n-1} G_n\end{bmatrix}$$
$$\times \begin{bmatrix}0&1&0&1\\1&1&0&1\\0&0&0&1\\0&0&1&1\end{bmatrix}$$
$$=\begin{bmatrix}fib_n fib_{n+1} G_n G_{n+1}\end{bmatrix}$$

代码3(Final)：（复杂度 $O(4^3\log n)$）
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=1e9+7;
void mul(int a[4],int b[4][4]){
    int c[4]; memset(c,0ll,sizeof(c));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            c[i]=(c[i]+a[j]*b[j][i]%Mod)%Mod;
    memcpy(a,c,sizeof(c));
}
void mulself(int a[4][4]){
    int c[4][4]; memset(c,0ll,sizeof(c));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            for(int k=0;k<4;k++)
                c[i][j]=(c[i][j]+a[i][k]*a[k][j]%Mod)%Mod;
    memcpy(a,c,sizeof(c));
}
void PowerMod(int b){
    int ans[4]={0,1,0,1};
    int a[4][4]={{0,1,0,1},{1,1,0,1},{0,0,0,1},{0,0,1,1}};
    while(b){
        if(b%2ll) mul(ans,a);
        b/=2ll,mulself(a);
    }
    int Ans=2ll*((ans[3]+Mod-(ans[0]+ans[1]*2ll%Mod)%Mod+1ll)%Mod)%Mod;
    //一定注意这里的"+Mod"，因为ans[3]和后面那堆都是%过Mod的，作差后不再一定为正数
	cout<<Ans<<endl;
}
void solve()
{
	int n;
	cin>>n;
	if(n<3){
		cout<<0<<endl; return;
	}
	PowerMod(n-1);
}
signed main(){
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```



---

