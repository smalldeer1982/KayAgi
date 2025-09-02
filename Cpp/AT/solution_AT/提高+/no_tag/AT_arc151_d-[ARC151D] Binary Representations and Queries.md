# [ARC151D] Binary Representations and Queries

## 题目描述

给定一个长度为 $2^N$ 的整数序列 $A = (A_0, A_1, \ldots, A_{2^N-1})$。

同时给出 $Q$ 个查询。对于第 $i$ 个查询（$i = 1, 2, \ldots, Q$），给定两个整数 $X_i$ 和 $Y_i$，执行以下操作：

> 按顺序对 $j = 0, 1, 2, \ldots, 2^N-1$ 执行以下步骤：
> 
> 1. 首先，将 $j$ 的 $N$ 位二进制表示记为 $b_{N-1}b_{N-2}\ldots b_0$。然后，通过反转 $b_{X_i}$（$0$ 变为 $1$，$1$ 变为 $0$）得到一个新的二进制表示，并将其对应的整数记为 $j'$。
> 2. 如果 $b_{X_i} = Y_i$，则将 $A_j$ 的值加到 $A_{j'}$ 上。

请输出所有查询按给定顺序执行后，$A$ 中每个元素对 $998244353$ 取模的结果。

关于 $N$ 位二进制表示的定义：非负整数 $X$（$0 \leq X < 2^N$）的 $N$ 位二进制表示是唯一满足以下条件的长度为 $N$ 的 $0$ 和 $1$ 组成的序列 $b_{N-1}b_{N-2}\ldots b_0$：

- $\sum_{i=0}^{N-1} b_i \cdot 2^i = X$

## 说明/提示

### 约束条件

- $1 \leq N \leq 18$
- $1 \leq Q \leq 2 \times 10^5$
- $0 \leq A_i < 998244353$
- $0 \leq X_i \leq N-1$
- $Y_i \in \{0, 1\}$
- 所有输入均为整数

### 样例解释 #1

第一个查询的操作如下：
- 当 $j=0$ 时，$b_1b_0=00$，$j'=2$。由于 $b_1 \neq 1$，不执行加法。
- 当 $j=1$ 时，$b_1b_0=01$，$j'=3$。由于 $b_1 \neq 1$，不执行加法。
- 当 $j=2$ 时，$b_1b_0=10$，$j'=0$。由于 $b_1=1$，将 $A_2$ 加到 $A_0$ 上，$A$ 变为 $(2,1,2,3)$。
- 当 $j=3$ 时，$b_1b_0=11$，$j'=1$。由于 $b_1=1$，将 $A_3$ 加到 $A_1$ 上，$A$ 变为 $(2,4,2,3)$。

第二个查询的操作如下：
- 当 $j=0$ 时，$b_1b_0=00$，$j'=1$。由于 $b_0=0$，将 $A_0$ 加到 $A_1$ 上，$A$ 变为 $(2,6,2,3)$。
- 当 $j=1$ 时，$b_1b_0=01$，$j'=0$。由于 $b_0 \neq 0$，不执行加法。
- 当 $j=2$ 时，$b_1b_0=10$，$j'=3$。由于 $b_0=0$，将 $A_2$ 加到 $A_3$ 上，$A$ 变为 $(2,6,2,5)$。
- 当 $j=3$ 时，$b_1b_0=11$，$j'=2$。由于 $b_0 \neq 0$，不执行加法。

最终 $A$ 的结果为 $(2,6,2,5)$


## 样例 #1

### 输入

```
2 2
0 1 2 3
1 1
0 0```

### 输出

```
2 6 2 5```

## 样例 #2

### 输入

```
3 10
606248357 338306877 919152167 981537317 808873985 845549408 680941783 921035119
1 1
0 0
0 0
0 0
0 1
0 1
0 1
2 0
2 0
2 0```

### 输出

```
246895115 904824001 157201385 744260759 973709546 964549010 61683812 205420980```

# 题解

## 作者：CReatiQ (赞：8)

### 题意概述

给定正整数 $1 \leq N \leq 18$，$1 \leq Q \leq 2 \times 10^5$。

长为 $2^N$ 的序列 $A=(A_0,A_1,\dots,A_{2^N-1})$。

有 $Q$ 次操作，第 $i$ 次操作给出 $1 \leq X_i \leq N-1$，$Y_i \in \{ 0,1 \}$。

对于每个二进制表示（最低位为第 $0$ 位）第 $X_i$ 位为 $Y_i$ 的下标 $j$，令 $A_{j \oplus 2^{X_i}}$ 加上 $A_j$。

求按顺序执行 $Q$ 次操作后的 $A$ 序列。

---

### 思路

其实就是序列里按某个二进制位的 $0/1$，拎一半元素出来，拍到另外那一半上。

直接按操作将元素相加不容易观察性质，我们不直接把数加上去，而是对于每个元素，把它应该加的数整成一个序列插在它下面，这样每次操作像接火车一样一节一节接下去就好。

可能说得有点抽象，上图。

![](https://cdn.luogu.com.cn/upload/image_hosting/tc97clxs.png)

刚开始序列长这样。

我们进行一次 $X_i=2,Y_i=0$ 的操作。

说人话就是把 $A_{0,1,2,3}$ 接到 $A_{4,5,6,7}$ 下面。

![](https://cdn.luogu.com.cn/upload/image_hosting/gftsga3p.png)

就像上面这样。

如果我们再做一次 $X_i=1,Y_i=0$ 的操作，把 $A_{0,1,4,5}$ 接到 $A_{2,3,6,7}$ 下面。

![](https://cdn.luogu.com.cn/upload/image_hosting/9uy4le2l.png)

像这样，不太美观。

为什么不美观呢？$A_{2,3}$ 的序列之前没被接过，$A_{6,7}$ 之前被接过，现在接上去的位置也就不同。

但发现第 $i$ 次操作接的序列最长是 $2^{i-1}$ 格，不妨钦定第 $i$ 次操作接的序列开头在从上往下数第 $2^{i-1}+1$ 格开始往下接，这样每次操作接的序列起始行就相同了。

第二次操作后的序列就会变成下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/satnxhw2.png)

再进行 $X_i=0,Y_i=1$ 的操作，把 $A_{1,3,5,7}$ 接到 $A_{0,2,4,6}$ 下面。

![](https://cdn.luogu.com.cn/upload/image_hosting/91ra6o4x.png)

观察序列（其实已经变成图表的形状了），每个元素至多接着 $N-1$ 段不同开头的序列，开头的元素是自己异或上 $2^i$。

但是每个序列里有很多对方之前被接上的元素，不方便直接计贡献，考虑能否将操作序列交换顺序，逐位处理。

试在上面的例子中，把第一个操作放到最后一次做，得到的序列会变成下面这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/d1s509ye.png)

发现只是将之前行号为奇数的行挪到上方，行号为偶数的行挪到下方。

为什么呢？

不难发现，第一步操作在第一步进行后产生的贡献在第 $2$ 行，第二步进行后被复制到第 $4$ 行，第三步再把 $2,4$ 行的贡献复制到第 $6,8$ 行。

以此类推，第一步操作的贡献在随后的操作中总是被复制到所有偶数行。

而把第一步挪到最后一步，相比原来，只是把所有偶数行的贡献抽出，放到最后一步结算而已。

但其实还有问题。

如果第一步操作为 $X_i,Y_i$，中间有操作为 $X_i,Y_i \oplus 1$，移位后，这步操作的贡献在此处会被算反，导致结果出错。

所以结论是：

> 记操作序列为 $q$。对于 $1 \leq l < i < r \leq Q$，不存在询问 $X_i=X_l,Y_i=Y_l \oplus 1$，则可以将 $q_l$ 移动至 $q_{r-1}$ 与 $q_{r}$ 之间。

所以将询问按 $X$ 分成一段一段，再统计贡献即可。

---

### Code

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN (int)(5e5+233)
#define int long long
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

const int mod=998244353;
int n,q,A[MAXN],tmp[MAXN];
vector<bool> tag[20];

inline int read()
{
	int x=0,f=1;char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}

signed main()
{
	n=read(),q=read();
	rep(i,0,(1<<n)-1) A[i]=read();
	rep(i,1,q)
	{
		int a=read(),b=read();
		tag[a].push_back(b);
	}
	rep(i,0,n-1)
	{
		int a=1,b=0,c=1,d=0;
		for (auto x:tag[i])
			if (x) a=(a+d)%mod,b=(b+c)%mod;
			else c=(b+c)%mod,d=(a+d)%mod;
		rep(j,0,(1<<n)-1)
		{
			if ((j>>i)&1) tmp[j]=(A[j]*c%mod+A[j^(1<<i)]*d%mod)%mod;
			else tmp[j]=(A[j]*a%mod+A[j^(1<<i)]*b%mod)%mod;
		}
		rep(j,0,(1<<n)-1) A[j]=tmp[j];
	}
	rep(i,0,(1<<n)-1) printf("%lld ",A[i]);
	return 0;
}
```


---

## 作者：do_while_true (赞：5)

### 克罗内克积（Kronecker Product）

大小为 $m\times n$ 的矩阵 $A$ 和大小为 $p\times q$ 的矩阵 $B$ 的克罗内克积 $A\otimes B$ 被定义为：
$$
\begin{pmatrix}
 a_{1,1}B & \cdots & a_{1,n}B\\
\vdots   & \ddots  & \vdots \\
 a_{m,1}B & \cdots  & a_{m,n}B
\end{pmatrix}
$$
显然不满足交换律，但是容易验证其满足结合律。

性质 1：$(A\otimes B)(C\otimes D)=(AC)\otimes (BD)$，其中 $AC$ 表示矩阵 $A$ 与 $C$ 的乘积。证明直接按定义写出矩阵来即可。

推论 1：$(A_1\otimes B_1\otimes \cdots \otimes Z_1)(A_2\otimes B_2\otimes \cdots \otimes Z_2)\cdots (A_n\otimes B_n\otimes \cdots \otimes Z_n)=(A_1A_2\cdots A_n)\otimes (B_1B_2\cdots B_n)\cdots \otimes (Z_1Z_2\cdots Z_n)$

根据性质 1，不难通过每次取出每个括号的最前面的矩阵来证明。

推论 2：

假设 $A,B,C,I_n$ 是大小为 $n\times n$ 的矩阵，其中 $I_n$ 为单位矩阵。那么即有：$A \otimes B \otimes C = (A\otimes I_n\otimes I_n)(I_n\otimes B\otimes I_n)(I_n\otimes I_n\otimes C)= (I_n \otimes I_n \otimes C)(I_n \otimes B \otimes I_n)(A \otimes I_n \otimes I_n)$．

这里可以任意排列，同样可以扩展到 $k$ 个矩阵的情况。

再根据推论 1 将最后一个式子拆开，然后再以任意的方式合并，可以得出相邻的两个括号中间的矩阵 $A$ 在夹在 $I_n$ 中不同的位置时可以任意交换，而夹在相同的位置时则不行。

也就是 $(A \otimes I_n \otimes I_n)(I_n \otimes B \otimes I_n)=(I_n \otimes B \otimes I_n)(A \otimes I_n \otimes I_n)$ 成立，但不会有 $(A \otimes I_n \otimes I_n)(B \otimes I_n \otimes I_n)=(B \otimes I_n \otimes I_n)(A \otimes I_n \otimes I_n)$

（不难理解，$n=1$ 相当于矩阵乘法具有交换律了）

回到 ARC151D，对于仅有一个长度为 2 的向量 $\mathbf{a} $ 的特殊情况，构造矩阵 $A_0,A_1$ 使得操作 $Y=0$ 时等价于 $\mathbf{a}\gets A_0\mathbf{a}$，操作 $Y=1$ 时等价于 $\mathbf{a}\gets A_1\mathbf{a}$．

仿照 FWT 的方法，对于长度为 $2^n$ 的向量 $\mathbf{a}$ 如果只想对第 $X$ 位进行操作，那么相当于 $\mathbf{a}\gets (I_2\otimes \cdots \otimes I_2\otimes A_Y\otimes I_2\otimes \cdots \otimes  I_2)\mathbf{a}$，这里一共有 $n$ 个大小为 $2\times 2$ 的矩阵，$A_Y$ 在第 $X$ 个（最开头为第 0 个）。

根据结论，可以将 $A_Y$ 处在不同位置的矩阵进行交换，但是 $A_Y$ 相同的则不能。先将 $X$ 相同的矩阵移动到一起，再根据推论 1 可以将同一 $X$ 的矩阵乘在一起看作一个矩阵 $B_X$．

那么现在问题就变成了计算 $(B_0\otimes I_n\otimes \cdots)(I_n\otimes B_1\otimes I_n\otimes \cdots)\cdots (I_n\otimes \cdots \otimes I_n\otimes B_n)\mathrm{a}$．

考虑左乘上一个 $(I_n\otimes \cdots \otimes B_i\otimes \cdots \otimes I_n)$ 具体是在固定除了第 $i$ 位以外的所有位置，然后单独对 $i$ 这一位左乘上 $B_i$（人话：对于每个第 $X$ 为 $0$ 的数 $v$，将 $a_v,a_{v+2^{X}}$ 构成的向量左乘 $B_i$）

直接按照这个写，就是和平常写高维前缀和 / 高维后缀和的 FMT 写法一样。

或者按照 FWT_xor 的写法也可以，就是把第 $i$ 层合并的时候进行的线性变换改成左乘上 $B_i$ 这个样子。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=18;
int n,q;
int a[(1<<N)+10];
int f[N][2][2];
int g[2][2][2],h[2][2];
void FWT(){
	for(int o=2,k=1,c=0;c<n;o<<=1,k<<=1,++c){
		for(int i=0;i<(1<<n);i+=o){
			for(int j=0;j<k;j++){
				int x=a[i+j],y=a[i+j+k];
				int u=add(1ll*x*f[c][0][0]%mod,1ll*y*f[c][0][1]%mod);
				int v=add(1ll*x*f[c][1][0]%mod,1ll*y*f[c][1][1]%mod);
				a[i+j]=u;a[i+j+k]=v;
			}
		}
	}
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);read(q);
	for(int i=0;i<(1<<n);i++)read(a[i]);
	for(int i=0;i<n;i++)f[i][0][0]=f[i][1][1]=1;
	g[0][0][0]=g[0][1][0]=g[0][1][1]=1;
	g[1][0][0]=g[1][0][1]=g[1][1][1]=1;
	while(q--){
		int x,y;read(x,y);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					cadd(h[i][j],1ll*g[y][i][k]*f[x][k][j]%mod);
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				f[x][i][j]=h[i][j],h[i][j]=0;
	}
	FWT();
	for(int i=0;i<(1<<n);i++)cout << a[i] << ' ';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```



---

## 作者：binbin_200811 (赞：2)

# ARC151D Binary Representations and Queries

题目链接：[ARC151D Binary Representations and Queries](https://www.luogu.com.cn/problem/AT_arc151_d)

非常好思维题。

#### 思路

首先我们会发现每个操作都是 $\frac{n}{2}$ 的 $A_i$，给另外 $\frac{n}{2}$ 的 $A_j$ 的增加。

这题直接去维护每个操作时间复杂度会开心的笑。

所以我们换个思路，先去探究一下这题的性质。

考虑一下，是否操作直接可以交换顺序？

~~反正我觉得不可以~~

现在我们来证明一下，交换操作不会对答案造成影响（这里交换的前提是**要求** $x_i\neq x_j$）。

设有操作 $i,j$，且 $x_i\neq x_j,i<j$。

那么我们可以将 $2^n$ 个下标分为 $4$ 个集合。

1.$b_{x_i}=y_i$ 且 $b_{x_j}=y_j$。

2.$b_{x_i}=y_i$ 且 $b_{x_j}\neq y_i$。

3.$b_{x_i}\neq y_i$ 且 $b_{x_j}=y_j$。

4.$b_{x_i} \neq y_i$ 且 $b_{x_j}\neq y_j$。

这里的 $b_i$ 表示第 $i$ 位二进制的数。

我们将集合 $u$ 向 $v$ 连有向边，表示集合 $u$ 内的下标会给 $v$ 内的下标做贡献，边的权值为这次操作的编号。

注意这里的权值仅表示操作的编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/lxdj9a3k.png)

* 如果先做操作 $i$，每个集合最终所得到的值如下：

  ​	$2\gets 1$。

  ​	$3 \gets 1$。

  ​	$4 \gets 2+3+1$。

* 如果先做操作 $j$，每个集合最终所得到的值如下：

  ​	$2\gets 1$。

  ​	$3 \gets 1$。

  ​	$4 \gets 3+2+1$。

不难发现，每个集合所得到的值并没有发生变化。

也就是说，只要满足 $x_i\neq x_j$，我们是可以交换操作的。

有了这个性质，我们考虑把所有 $x_i$ 相等的操作交换到一起操作。

这样就被分成了两个集合，这两个集合间互相给对方做贡献，方便我们快速统计每个集合收到贡献的系数。

这样就可以快速求 $A_i$ 了。

时间复杂的 $O(n\log n)$。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 998244353

const int maxn=3e5+5;

int n,q;

ll a[maxn],tmp[maxn];

vector<int>tag[20];

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<(1<<n);i++) scanf("%lld",&a[i]);
    for(int i=1;i<=q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        tag[x].push_back(y);
    }
    for(int i=0;i<n;i++)
    {
        int x_1=1,y_1=0,x_0=1,y_0=0;//x是自己对自己的贡献系数，y是对方对自己的贡献系数
        for(int k:tag[i])
        {
            if(k) x_0=(x_0+y_1)%mod,y_0=(y_0+x_1)%mod;
            else x_1=(x_1+y_0)%mod,y_1=(y_1+x_0)%mod;
        }
        for(int j=0;j<(1<<n);j++)
        {
            if((j>>i)&1) tmp[j]=(x_1*a[j]%mod+y_1*a[j^(1<<i)]%mod)%mod;
            else tmp[j]=(x_0*a[j]%mod+y_0*a[j^(1<<i)]%mod)%mod;
        }
        for(int j=0;j<(1<<n);j++) a[j]=tmp[j];
    }
    for(int j=0;j<(1<<n);j++) printf("%lld ",a[j]);
}
```



---

## 作者：Eric998 (赞：1)

并非思维。

我们考虑这些操作在 ```FWT``` 中的意义。注意到 ```FWT``` 的本质是对每对二进制恰好差一位的数乘上一个转移矩阵。

在一般的 ```FWT``` 中，这个矩阵是不变的。在此题中，我们考虑对于每一位维护一个矩阵。每次操作是对该位的转移矩阵乘上一个上/下三角矩阵。维护好后 ```FWT``` 即可。

复杂度 $O(2^nn+q)$。

---

## 作者：Maverik (赞：1)

## Statement

给定一个整数 $n$ 和一个长度为 $2^n-1$，下标从 0 开始的序列 $A$。你需要按顺序执行 $Q$ 次操作，每次操作内容如下：

给定两个整数 $X,Y$，若整数 $i\in [0,2^n)$ 满足它的二进制第 $X$ 位为 $Y$，设 $i$ 翻转第 $X$ 位后的值为 $i'$，则让 $A_{i'}$ 的值加上 $A_i$。

所有操作执行完后，请输出整个序列 $A$。

$1\le N\le 18,\ 1\le Q\le 2\times 10^5,\ 0\le X\le N-1,\ Y\in \{0,1\}$。

## Solution

首先考虑 $n=2$ 情况，$f_{x,y}$ 表示通过操作集合使得二进制位从 $x$ 变为 $y$ 的方案数，那么 $ans_i=f_{i,i}a_i + f_{i,j} a_j (j\oplus i=0)$ 。

考虑多位的时候，如果沿用以上思路，设 $f_{k,x,y}$ 表示通过操作集合使得二进制第 $k$ 位从 $x$ 变为 $y$ 的方案数，那么：

$$
ans_i=\sum_{j=1}^{n} a_j \sum_{k=1}^{bits} f_{k,i \text{~and~} 2^k,j \text{~and~} 2^k}
$$

手玩一下发现，二进制的每位之间是相互独立的，由此可以按位一层一层处理。由于对于二进制的每一位，$a_i$ 得贡献者是唯一的，由此可以做到 $O(n\log n)$。


## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int maxn=5e5+10,mod=998244353;
vector<int>tag[maxn];
int n,Q,a[maxn],b[maxn],f[2][2];
inline void Add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
inline void solve()
{
    cin>>n>>Q; for(int i=0;i<(1<<n);i++) cin>>a[i];
    for(int i=1,x,y;i<=Q;i++) cin>>x>>y,tag[x].pb(y);
    for(int bit=0;bit<n;bit++)
    {
        f[1][1]=f[0][0]=1,f[1][0]=f[0][1]=0;
        for(auto w:tag[bit])
            if(w) Add(f[0][0],f[0][1]),Add(f[1][0],f[1][1]);
            else Add(f[1][1],f[1][0]),Add(f[0][1],f[0][0]);
        for(int i=0;i<(1<<n);i++)
            if(i&(1<<bit)) b[i]=(a[i]*f[1][1]%mod+a[i^(1<<bit)]*f[0][1]%mod)%mod;
            else b[i]=(a[i]*f[0][0]%mod+a[i^(1<<bit)]*f[1][0]%mod)%mod;
        memcpy(a,b,sizeof(b));
    }
    for(int i=0;i<(1<<n);i++) cout<<a[i]<<' ';
}
signed main(){ios::sync_with_stdio(false);cin.tie(NULL);return solve(),0;}
```

---

## 作者：masonpop (赞：0)

首先把 $n$ 位二进制数当成 $n$ 维空间里面的点，那么操作就相当于每次选定一个维度做一遍高维前/后缀和。

然后高维前缀和有显然的结论，就是哪一维先做是不影响答案的。这个题东西也差不多，但是每一维可能做很多次，类似的可以猜测，在不改变每一维内部操作的顺序基础上，先做哪一维是不影响的！事实上这个是对的，而且很好证明。

然后你发现只考虑第 $i$ 维时，对于其它维相同的两个对应点 $a_x,a_y$，其经过变换一定会变成一个形如 $k_1a_x+k_2a_y,k_3a_x+k_4a_y$ 的形式，以及这四个系数显然是和 $x,y$ 无关的。于是先扫一遍操作把系数处理出来就行。

复杂度 $O(n2^n)$。[代码](https://atcoder.jp/contests/arc151/submissions/60636015)。

---

## 作者：SoyTony (赞：0)

规定 $x$ 相等的操作为“同一层的”，$y=0$ 的操作为“向右的”，$y=1$ 的操作为“向左的”。

显然同一层的操作之间不能交换位置，我们考虑处在不同层的两个操作能否交换位置。

显然这种操作等价于连边，而只考虑交换两个不同层操作，只需要看这两个操作代表的边，也就是说，每个大小为 $4$ 的联通块之间是独立的。

接下来可以画图理解。

容易得到这样一个联通块中，两条边都是入边的和都是出边的有一个，另两个一出一入。交换遍历边的顺序之后，直接相连的贡献没有改变，只需要考虑从只有出边的走到只有入边的，这条路径显然存在，而其余相对位置没有改变的边的转移自然没有发生变化，因此交换两个不同层的操作是不改变答案的。

将交换拓展，也就是在不改变同一层边的相对顺序情况下，按照层数排序是不影响答案的。

于是对于每一层都可以得到一个转移矩阵，对每个点对矩阵乘法转移即可。

```cpp
int n,q;
int a[maxn];
struct Matrix{
    int num[3][3];
    Matrix(){
        num[1][1]=num[1][2]=num[2][1]=num[2][2]=0;
    }
    Matrix operator*(const Matrix&rhs)const{
        Matrix res;
        for(int k=1;k<=2;++k){
            for(int i=1;i<=2;++i){
                for(int j=1;j<=2;++j){
                    res.num[i][j]=(res.num[i][j]+1ll*num[i][k]*rhs.num[k][j]%mod)%mod;
                }
            }
        }
        return res;
    }
    inline void output(){
        printf("%d %d\n%d %d\n",num[1][1],num[1][2],num[2][1],num[2][2]);
    }
}bs0,bs1,bs[20],tmp;
int main(){
    // freopen("test.in","r",stdin);
    n=read(),q=read();
    for(int i=0;i<(1<<n);++i) a[i]=read();
    bs0.num[1][1]=bs0.num[2][1]=bs0.num[2][2]=1;
    bs1.num[1][1]=bs1.num[1][2]=bs1.num[2][2]=1;
    for(int i=0;i<n;++i) bs[i].num[1][1]=bs[i].num[2][2]=1;
    for(int i=1;i<=q;++i){
        int x=read(),y=read();
        if(!y) bs[x]=bs0*bs[x];
        else bs[x]=bs1*bs[x];
    }
    for(int k=0;k<n;++k){
        // printf("**%d**\n",k);
        // bs[k].output();
        for(int i=0;i<(1<<n);++i){
            if(i&(1<<k)) continue;
            tmp.num[1][1]=a[i],tmp.num[2][1]=a[i+(1<<k)],tmp.num[1][2]=tmp.num[2][2]=0;
            tmp=bs[k]*tmp;
            // tmp.output();
            a[i]=tmp.num[1][1],a[i+(1<<k)]=tmp.num[2][1];
        }
    }
    for(int i=0;i<(1<<n);++i) printf("%d ",a[i]);
    printf("\n");
    return 0;
}
```

---

