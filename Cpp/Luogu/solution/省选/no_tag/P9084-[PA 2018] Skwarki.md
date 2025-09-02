# [PA 2018] Skwarki

## 题目描述

**题目译自 [PA 2018](https://sio2.mimuw.edu.pl/c/pa-2018-1/dashboard/) Runda 5 [Skwarki](https://sio2.mimuw.edu.pl/c/pa-2018-1/p/skw/)** 。

求有多少种长度为 $ N $ 的满足以下条件的序列 ：

* $ 1 \sim N $ 这 $ N $ 个数在序列中各出现了一次；
* 进行恰好 $K$ 次操作后，该序列才只含有 $1$ 个元素。

下面对操作进行描述：

设 $A_i$ 为序列中的第 $i$ 个元素（$1 < i < \mathrm{len}$ ， $\mathrm{len}$ 为序列长度），若 $A_{i-1} > A_{i}$ 或 $A_{i+1} > A_{i}$ 则标记 $A_i$ 。 若 $A_2 > A_1$ 则标记 $A_1$ ， 若 $A_{\mathrm{len}-1} > A_{\mathrm{len}}$ 则标记 $A_{\mathrm{len}}$ 。

然后，将有标记的元素从序列中删除。

满足条件的序列可能很多，所以请将结果对 $P$ 取模。

## 说明/提示

#### 样例 1 解释

所有满足条件的序列列举如下：

- $(4,1,3,2,5)$
- $(4,2,3,1,5)$
- $(5,1,3,2,4)$
- $(5,2,3,1,4)$

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1 \le K,N \le 1000$ , $N \ge 2$ , $10^8 \le P \le 10^9$。

## 样例 #1

### 输入

```
5 3 100000007```

### 输出

```
4```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

每次操作至多保留一半的数字，$m>10$ 就无解了。

操作是删掉非局部峰顶，但是对着这个做肯定寄。

考虑笛卡尔树，每次删掉不是有两个儿子的。因为叶子肯定是局部谷底，有一个儿子的一定有个相邻的比他大。

但是边界比较特殊。如果说中间的点需要两个条件才能保留，那么边界就只需要一个，靠边的那侧免疫。

考虑到全局最大值一定是最后留下来的，我们枚举 $n$ 的位置，两边分别算。我们并不在乎边界是在左边还是右边，设状态：$f[i][j][0/1]$ 表示长度为 $i$ 的排列 $j$ 次删空有无边界的方案数。

转移直接枚举 $i$ 的位置和左右两边的步数。总步数的计算详见代码。

## code

```cpp
#include<stdio.h>
#define N 1009
#define M 11
#define max(x,y) ((x)>(y)?(x):(y))
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,mod,c[N][N],ans;__int128 f[N][M][2];
main()
{
	read(n);read(m);read(mod);
	if(m>10)return putchar('0'),0;
	for(int i=0;i<N;++i)
	{
		c[i][0]=1;
		for(int j=1;j<=i;++j)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	f[0][0][0]=f[0][0][1]=1;
	for(int i=1;i<n;++i)
	{
		for(int j=1;j<=i;++j)for(int k=0;k<=m;++k)for(int l=0,nxt;l<=m;++l)
		{
			nxt=k==l?k+1:max(k,l);
			f[i][nxt][0]+=f[j-1][k][0]*f[i-j][l][0]*c[i-1][j-1];
			nxt=max(k,l+1);
			f[i][nxt][1]+=f[j-1][k][1]*f[i-j][l][0]*c[i-1][j-1];
		}
		for(int j=0;j<=m;++j)f[i][j][0]%=mod,f[i][j][1]%=mod;
	}
	for(int j=1;j<=n;++j)for(int k=0;k<=m;++k)for(int l=0;l<=m;++l)
		if(max(k,l)==m)ans=(ans+(long long)(f[j-1][k][1])*f[n-j][l][1]%mod
			*c[n-1][j-1])%mod;
	printf("%d",ans);
}
```

---

## 作者：bugmaker3243 (赞：6)

首先一次操作至少删去一半元素，所以 $k\leq\log n$。也就是 $k≤10$ 时答案才可能不为 $0$。

进一步发现一次操作相当于删去当前笛卡尔树上所有儿子数 $<2$ 的点（特别的，对于下标最小 / 最大的点，其不存在儿子才会被删去)。

理解的话就是考虑笛卡尔树的性质：中序遍历是原数列，且区间最大值等于 $\text{LCA}$。

于是我们考虑对笛卡尔树计数。容易发现下标最小 / 最大的点一定在根的两个不同子树里（或为根本身），于是考虑设 $f_{i,j,0/1}$，表示树大小为 $i$，操作了 $j$ 次后只剩下一个点，且有 $0/1$ 个边界点的方案数。

边界：$f_{0,0,0}=f_{0,0,1}=1$

转移比较麻烦，先设 $F_{i,j,op}=\sum\limits_{k=0}^j f_{i,k,op}$

考虑 $f_{i,j,0}$ 怎么转移，考虑 $j$ 是通过哪里得到的：

- 根节点最后被删（钦定其他所有点都在 $j$ 之前被删）:$f_{i,j,0}= \sum\limits_{k=0}^{i-1} f_{k,j-1,0}\times f_{i-k-1,j-1,0}\times \binom{i-1}{k}$

- 有儿子节点最后被删：$f_{i,j,0}= \sum\limits_{k=0}^{i-1} 2\times f_{k,j,0}\times F_{i-k-1,j-1,0}\times \binom{i-1}{k}$

转移中的组合数是分配权值的过程。

再考虑 $f_{i,j,1}$ 的转移：

容易发现由于存在边界点的缘故，当前根的其中一个子树被删空后，会使得根成为新的边界点，因此此时的根节点的被删时间就是没有边界点的子树的被删时间再加 $1$。

- 根节点最后被删（钦定其他所有点都在 $j$ 之前被删）:$f_{i,j,1}= \sum\limits_{k=0}^{i-1} F_{k,j-1,1}\times f_{i-k-1,j-1,0}\times \binom{i-1}{k}$

- 有儿子节点最后被删：$f_{i,j,1}= \sum\limits_{k=0}^{i-1} f_{k,j,1}\times F_{i-k-1,j-1,0}\times \binom{i-1}{k}$

最后再枚举两个子树的大小，统计答案：

$ans=\sum\limits_{i=0}^{n-1} F_{i,m,1}\times F_{n-i-1,m,1}\times \binom{n-1}{i}-F_{i,m-1,1}\times F_{n-i-1,m-1,i}\times \binom{n-1}{i}$

## Code

```cpp
#include<bits/stdc++.h>
#define N 1005
//#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
#define gc() getchar()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int inf=2e9;
const ll INF=4e18;
bool Memory_Begin;
namespace IO{const int SIZE=(1<<21)+1;char ibuf[SIZE],*iS,*iT,obuf[SIZE],*oS=obuf,*oT=oS+SIZE-1,c,qu[55];int f,qr;inline void flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}inline void putc(char x){*oS++=x;if(oS==oT)flush();}template <class I>inline void read(I &x){for(f=1,c=gc();c<'0'||c>'9';c=gc())if(c=='-')f=-1;for(x=0;c<='9'&&c>='0';c=gc())x=x*10+(c&15);x*=f;}template <class I>inline void print(I x){if(!x)putc('0');if(x<0)putc('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)putc(qu[qr --]);}inline void reads(string &s){s.clear();for(c=gc();(c<'a'||c>'z')&&(c<'A'||c>'Z')&&(c<'0'||c>'9');)c=gc();for(;(c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9');c=gc())s.push_back(c);}struct Flusher_ {~Flusher_(){flush();}}io_flusher_;}
using IO::read;using IO::putc;using IO::print;using IO::reads;
ll updiv(ll x,ll y){return (x%y==0?x/y:x/y+1);}

int tid,T,n,m,mod;
int f[N][N][2],F[N][N][2],C[N][N];
void A(int &x,ll y){x=(x+y%mod);if(x>mod) x-=mod;if(x<0) x+=mod;}
void Sub(int i)
{
	F[i][0][0]=f[i][0][0];
	F[i][0][1]=f[i][0][1];
	for(int j=1;j<=m;j++)
	{
		F[i][j][0]=(F[i][j-1][0]+f[i][j][0])%mod;
		F[i][j][1]=(F[i][j-1][1]+f[i][j][1])%mod;
	}
}
bool Memory_End;
signed main()
{
//	freopen("lifetime.in","r",stdin);
//	freopen("lifetime.out","w",stdout);
	cerr<<"Memory: "<<(&Memory_Begin-&Memory_End)/1048576.0<<" MiB\n";
	read(n),read(m),read(mod);
	if(m>10) {print(0),putc('\n');return 0;}
	m++;
	C[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	memset(f,0,sizeof(f));
	memset(F,0,sizeof(F));
	f[0][0][0]=f[0][0][1]=f[1][1][0]=f[1][1][1]=1;
	Sub(0),Sub(1);
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			for(int k=0;k<i;k++)
			{
				A(f[i][j][0],(ll)f[k][j-1][0]*f[i-k-1][j-1][0]%mod*C[i-1][k]);
				A(f[i][j][0],(ll)2*f[k][j][0]*F[i-k-1][j-1][0]%mod*C[i-1][k]);
				A(f[i][j][1],(ll)F[k][j-1][1]*f[i-k-1][j-1][0]%mod*C[i-1][k]);
				A(f[i][j][1],(ll)f[k][j][1]*F[i-k-1][j-1][0]%mod*C[i-1][k]);
			}
		}
		Sub(i);
	}
	int ans=0;
	for(int i=0;i<n;i++)
	{
		A(ans,(ll)F[i][m-1][1]*F[n-i-1][m-1][1]%mod*C[n-1][i]);
		A(ans,-(ll)F[i][m-2][1]*F[n-i-1][m-2][1]%mod*C[n-1][i]);
	}
	print(ans),putc('\n');
	return 0;
}
```


---

## 作者：wjyppm1403 (赞：3)

[可能更好的阅读体验](https://worldcpu.github.io/P9804-Skwarki%E9%A2%98%E8%A7%A3.html)

好题，写一篇题解记录一下。

首先考虑计数 DP，但是直接做发现不太好做，我们思考能否对删除操作进行进一步转化成好的条件取做。

对于原题目的限制，即只要一个数左右两侧一旦有一个大的就会被删，既有位置限制和数值限制。一步很妙的转化的就是将这个思想转成笛卡尔树，那么删除操作就是在笛卡尔树上删有儿子的点。

我们不妨设 $g_{u}$ 表示删空 $u$ 子树（包括 $u$ 号点）的所需次数，因为题意表明删除操作是同时进行的，不难有如下转移：

$$g_{u}=\max\left\{ g_{\text{ls}},g_{\text{rs}},\min(g_{\text{ls}},g_{\text{rs}})+1 \right\}$$

其中 ls 表示左儿子，rs 表示右儿子，注意在没有左儿子和右儿子的时候要特判。

方程表明如下情况：

- $g_{\text{ls}},g_{\text{rs}}$：因为操作是并行的，我们可以直接对左右儿子删除操作取 $\max$ 即可。
- 某一子树删除完毕后，花一次操作删根节点 $u$ 让后把剩下子树接上去。

注意到删除最多删除树的一半节点，也就是当删除操作数量 $k\le \log(n)$ 时才可能有解。

验证考虑分类讨论，讨论左右子树操作次数相同和不同的情况即可简明验证。不难发现的一点是答案一定是全局的最大值，并且一定作为叶子节点出现。

接下来我们考虑如何把它搬到计数 DP 上，真的在笛卡尔树上 DP 显然是不现实的，因为树的结构会改变。

我们利用笛卡尔树的性质：我们设一个区间 $[l,r]$ 最大值的位置为 $pos$，发现可以把区间分成 $[l,pos]$和 $[pos,r]$ 两个区间，并且两个区间互不影响，也就是说我左边怎么乱搞放数也不会影响右边的区间。这个时候全局最大值作为区间的端点出现。

![](https://cdn.luogu.com.cn/upload/image_hosting/z1lulne1.png)

我们利用笛卡尔树结构的特点，设 $f(i,j,0/1)$ 表示 $i$ 个元素的排列，恰好 $j$ 次删空，全局最大值是否在区间的端点。

对于 $f(i,j,0)$ 的转移，根据我们上面所述的笛卡尔树的节点，我们需要枚举区间的最大值的位置来进行转移，对于每个位置 $k$ 在分配左儿子的方案有 $\binom{i-1}{k-1}$ 种方案给乘起来，左儿子 $f(k-1,l,0)$ 右儿子 $f(i-k,r,0)$，其中 $l,r$ 是枚举儿子区间最大值的位置，转移即可。

考虑 $f(i,j,1)$ 的转移，我们不考虑区间端点到底在哪里，因为排列的对称性可以完全统计答案，那么转移只需统计左儿子或者右儿子任一出现最大值的方案数即可，再乘上 $\binom{i-1}{k-1}$ 即可。

转移的 $j$ 需要通过上面的 $g$ 单独计算，答案统计仍枚举最大值转移即可，见代码，时间复杂度 $O(n^{2}k^{2})$。

注意到 $k$ 最大为 $\log(n)$，那么时间复杂度就是 $O(n^2 \log^{2} n)$，这个复杂度下会被卡常，需要减少取模操作。注意到转移方程可以前缀和优化，那么时间复杂度即为 $O(n^{2} \log n)$，这里就不用关心了。

不同于一些连续段 DP，这种转移的技巧叫做枚举最大值转移，实质就是上面所提到的在笛卡尔树上排列的 DP 结构，这种题类型很少见，但是我可以推荐一道题供大家练习：[CF1580B](https://www.luogu.com.cn/problem/CF1580B)。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=1520;
int f[MN][MN][2],pw[MN],inv[MN],n,K,nj,MOD;

template<typename type>
inline type read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return flag?x=-x:x;
}

template<typename type>
inline void write(type x)
{
    x<0?x=-x,putchar('-'):0;
    static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10;while(x);
    while(top) putchar(Stack[top--]|48);
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    read(n),read(K),read(MOD);
    if(K>__lg(n)+1){
        cout<<0;
        return 0;
    }
    init();
    f[0][0][0]=f[0][0][1]=1;
    for(int i=1;i<n;i++){
        for(int j=1;j<=i;j++){
            for(int l=0;l<=K;l++){
                for(int r=0;r<=K;r++){
                    // l和r枚举两个孩子区间最大值位置
                    nj=(l==r)?l+1:max(l,r);// 小 g 的凭借
                    f[i][nj][0]=(f[i][nj][0]+f[j-1][l][0]*f[i-j][r][0]*getC(i-1,j-1)%MOD)%MOD;
                    nj=max(l,r+1);
                    f[i][nj][1]=(f[i][nj][1]+f[j-1][l][1]*f[i-j][r][0]%MOD*getC(i-1,j-1)%MOD)%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int l=0;l<=K;l++){
            for(int r=0;r<=K;r++){
                if(max(l,r)==K){
                    // 根据方程枚举区间拼接，可以看上面图理解
                    ans=(ans+(f[i-1][l][1]*f[n-i][r][1]%MOD*getC(n-1,i-1)%MOD))%MOD;
                }
            }
        }
    }
    write(ans);
    return 0;
}
```

---

## 作者：UNVRS (赞：1)

## 题意

定义在排列上进行操作为删去所有存在一个相邻的数大于自身的数，若只剩下一个数则中止。

给定 $n,m$，计数所有长度为 $n$ 的可以进行恰好 $m$ 次操作后中止的排列。

$n,m\le 10^3$

## 思路

对于本题，思考时切入点较多，不过经过交流后我认为最后得到的做法应该都是本质相同的，本文提供笛卡尔树为基本视图的路径。

---

对于排列的大小关系一类的问题，不难想到转化为笛卡尔树。此时，操作的形式变为删去所有一度点与（除了最左与最右）二度点，将原先的二度点替换为一条边，即树收缩（tree contraction）操作：

![rake and compress](https://cdn.luogu.com.cn/upload/image_hosting/z58rxinv.png)

如果你听说过 top cluster 理论，你会知道这个过程只会执行 $\log n$ 次，不过这个理论与本文并无关系，而且我们有一个更为简单的证明：因为一个不被删去的点两边都是被删去的点，故而每次操作都将删去一半的点。

在开始刻画状态之前，我们需要进一步的简化操作轮数的计算（我们称将某个子树删空需要的操作次数为操作轮数，注意并不一定是其根节点删除的时间），我们发现对于非根结点 $x$，其操作轮数是其两个子树的操作轮数的 $\min+1$（当其一个子树为空时，下回合它就会被删除），特殊的，我们认为 最左/最右 的结点的 左子树/右子树 的操作轮数为无穷大（之后称 最左/最右 结点为**端点**）。

对于笛卡尔树上的 DP，常见的形式是自底向上进行多区间合并，不过本题我们需要记录区间自身的信息，故这种方式并不可行。由于本题中区间之间的影响较小，考虑自顶向下拆分区间，我们设 $f_{i,j}$ 表示包含 $i$ 个结点的、删除时间为 $j$ 的笛卡尔树数量，不过注意到**端点**处转移会略有不同，所以还需要记录**端点**的状态。

一个朴素的想法是记录 $0/1/2/3$ 表示其左右**端点**的存在情况，不过显然，当最大值插入之后（由于其不能被删除所以需要特殊讨论），所有位置都有了一个**端点**，并且只有左**端点**和只有右**端点**是等价的，于是可以简化为 $0/1$ 表示其存在 一个/两个 **端点**。

转移较为自然，分为两部分：

1. 将长度为 $i$ 的序列枚举分割为 $i=x+1+y$，首先我们需要把 $i-1$ 个数分配到左右两个区间，这个系数显然为 $\binom{i-1}{x}$。

   一个**端点**的状态可以令有**端点**的一侧操作轮数为 $j-1$，另一侧小于等于 $j$ 轮；或无**端点**的一侧操作轮数为 $j$，另一侧小于等于 $j-1$ 轮（这两种当全取等于的时候实际上是同一种，以下不讨论这类问题，由读者自行决定如何去重）。

   两个**端点**的状态则可以令两侧全为 $j-1$，或者任意一侧为 $j$，另一侧小于等于 $j-1$。

2. 该点为最左或最右，此时转移系数为 $1$。

   一个**端点**的状态可以建立另一个端点，此时令间的操作轮数为 $j-1$，或者延续之前的端点，此时中间的操作轮数为 $j$。

   两个**端点**的状态可以选择随意放置在左侧或右侧（转移系数为 $2$），$j$ 不变。

实际的转移顺序为按照长度顺序，当然你可以写记搜。

对于根节点，其操作轮数是两个子树的 $\max+1$，容易处理。

注意到转移过程中存在一个偏序的贡献，可使用前缀和优化至 $O(1)$。

状态数 $O(n\log n)$，转移 $O(n)$，总时间复杂度为 $O(n^2\log n)$。

~~观察第一维贡献形式看起来可以卷积啊，不过以我的多项式水平这种东西就留给后人了。~~

## CODE

```c++
#include<cstdio>
#include<algorithm>
using namespace std;
using ll=long long;
const int N=1010,FSIZE=1<<26;
int tn,n,m,mo,f[N][20][2],s[N][20][2],C[N][N];
char BuF[FSIZE],*InF=BuF;
template<typename T>void read(T &x){
    for(;48>*InF||*InF>57;++InF);
    for(x=0;47<*InF&&*InF<58;x=x*10+(*InF++^48));
}
int add(int x,int y){if((x+=y)>=mo) x-=mo;return(x);}
void add(int &x,ll y){x=(x+y)%mo;}
int main(){
    fread(BuF,1,FSIZE,stdin);
    read(n);read(m);read(mo);
    if(m>__lg(n)+1){
        printf("0\n");
        return(0);
    }
    f[0][1][0]=f[0][1][1]=f[1][1][0]=f[1][1][1]=1;
    for(int i=1;i<=m;++i)
        s[0][i][0]=s[1][i][0]=s[0][i][1]=s[1][i][1]=1;
    for(int i=C[0][0]=1;i<=n;++i)
        for(int j=C[i][0]=1;j<=i;++j)
            C[i][j]=add(C[i-1][j-1],C[i-1][j]);
    for(int i=2;i<n;++i)
        for(int j=0;j<=m;++j){
            for(int k=2;k<i;++k){
                ll x=C[i-1][k-1];
                add(f[i][j][0],
                    (ll)f[k-1][j-1][1]*s[i-k][j-1][0]%mo*x+
                    (ll)s[k-1][j-1][1]*f[i-k][j][0]%mo*x);

                add(f[i][j][1],
                    (ll)f[k-1][j-1][1]*f[i-k][j-1][1]%mo*x+
                    (ll)f[k-1][j][1]*s[i-k][j-1][1]%mo*x+
                    (ll)s[k-1][j-1][1]*f[i-k][j][1]%mo*x);
            }
            add(f[i][j][0],ll(f[i-1][j-1][1]+f[i-1][j][0]));

            add(f[i][j][1],(ll)f[i-1][j][1]*2);

            s[i][j][0]=add(s[i][j-1][0],f[i][j][0]);
            s[i][j][1]=add(s[i][j-1][1],f[i][j][1]);
        }
    int ans=f[n-1][m][0]+f[n-1][m][0];
    for(int i=2;i<n;++i){
        int x=C[n-1][i-1];
        add(ans,(ll)f[i-1][m][0]*s[n-i][m-1][0]%mo*x);
        add(ans,(ll)s[i-1][m-1][0]*f[n-i][m][0]%mo*x);
        add(ans,(ll)f[i-1][m][0]*f[n-i][m][0]%mo*x);
    }
    printf("%d\n",ans);
    return(0);
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

对于一个排列 $p$，一次操作定义为：

- 如果与 $p_i$ 相邻的数中存在比 $p_i$ 大的，就标记 $p_i$。

- 然后，删除被标记的数。

定义一个排列 $p$ 是好的，当且仅当对其做恰好 $k$ 次操作后 $p$ 只剩下一个元素。对好的排列计数。

## 题目分析

我们考虑枚举排列最大值的位置，这样就可以递归处理。

设 $f_{len,k}$ 表示把长度为 $len$ 的排列删到只剩 $p_i=len$，操作次数小于等于 $k$ 的排列个数。则答案为 $f_{n,k}-f_{n,k-1}$。

设 $g_{len,k,1/2}$ 表示有 $1/2$ 个端点处有比 $len$ 大的数，把 $p$ 删空，操作次数小于等于 $k$ 的排列个数。

转移十分简单，枚举 $p_i=len$ 的位置即可。

所以只用到了递归，所以感觉这题是绿题？？？

```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =1e3+5;
int mod,n,k;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
int C[N][N];
inline void prep(){
	C[0][0]=1;
	rep(i,1,N-5){
		C[i][0]=1;
		rep(j,1,i)C[i][j]=Add(C[i-1][j],C[i-1][j-1]);
	}
}
int f[N][15][3];
inline int solve(int len,int k,int ty){
	if(f[len][k][ty]!=-1)return f[len][k][ty];
	if(k<0)return 0;
	if(len<=0)return 1;
	int &ans=f[len][k][ty];
	ans=0; 
	if(!ty){
		rep(i,1,len)
			add(ans,mul(C[len-1][i-1],mul(solve(i-1,k,1),solve(len-i,k,1))));
		return ans;
	} 
	if(!k)return 0;
	if(ty==2){
		rep(i,2,len-1){
			int W=0;
			add(W,mul(solve(i-1,k-1,2),solve(len-i,k,2)));
			add(W,mul(Red(solve(i-1,k,2),solve(i-1,k-1,2)),solve(len-i,k-1,2)));
			add(ans,mul(C[len-1][i-1],W));
		}
		add(ans,mul(1+(len>1),solve(len-1,k,2)));
		return ans;
	}
	rep(i,1,len)add(ans,mul(C[len-1][i-1],mul(solve(i-1,k-1,2),solve(len-i,k,1))));
	return ans;
}
signed main(){
	n=read(),k=read(),mod=read(),prep();
	if(k>10)return puts("0"),0;
	memset(f,-1,sizeof(f));
	cout <<Red(solve(n,k,0),solve(n,k-1,0));
	return 0;
}
```

---

