# Graph Coloring (hard version)

## 题目描述

本题的简单版和困难版唯一的区别在于 $ n $ 的限制。

给定一个有 $ n $ 个顶点的无向完全图。完全图是指任意两个顶点之间都有一条边相连。你需要将图中的每条边涂成红色或蓝色（每条边只能有一种颜色）。

对于一个顶点集合 $ S $，如果对于 $ S $ 中任意一对顶点 $ (v_1, v_2) $，存在一条仅经过 $ S $ 中顶点且只经过红色边的路径从 $ v_1 $ 到 $ v_2 $，则称 $ S $ 是红连通的。同理，如果对于 $ S $ 中任意一对顶点 $ (v_1, v_2) $，存在一条仅经过 $ S $ 中顶点且只经过蓝色边的路径从 $ v_1 $ 到 $ v_2 $，则称 $ S $ 是蓝连通的。

你需要对图进行染色，使得：

- 至少有一条红色边；
- 至少有一条蓝色边；
- 对于每一个满足 $ |S| \ge 2 $ 的顶点集合 $ S $，$ S $ 要么是红连通的，要么是蓝连通的，但不能同时两者都是。

请计算有多少种不同的染色方案，并将结果对 $ 998244353 $ 取模后输出。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3```

### 输出

```
6```

## 样例 #2

### 输入

```
4```

### 输出

```
50```

## 样例 #3

### 输入

```
100```

### 输出

```
878752271```

## 样例 #4

### 输入

```
1337```

### 输出

```
520628749```

## 样例 #5

### 输入

```
42013```

### 输出

```
906821221```

# 题解

## 作者：Kubic (赞：7)

设 $\overline G$ 为 $G$ 的补图。

对于任意一个无向图 $G$，$G$ 与 $\overline G$ 中至少有一个连通。

称一个无向图 $G$ 时好的当且仅当它满足以下条件：

- 对于 $G$ 的任意一个点导出子图 $H$，如果 $|H|\ge 2$，那么 $H$ 与 $\overline H$ 不同时联通。

设 $f_n$ 表示有多少个无向**连通**图 $G$ 满足 $|G|=n$ 且 $G$ 是好的。

答案即为 $2f_n-2$。

因为 $G$ 是连通的，所以 $\overline G$ 必须不连通。对于一个 $H$，如果 $H$ 中的点不在 $\overline G$ 的同一个连通块中，那么一定满足条件。

因此我们只需要保证 $\overline G$ 的每一个连通块中的所有点的导出子图是好的即可推出 $G$ 是好的。而 $\overline G$ 中一个大小为 $k$ 的连通块的方案数为 $f_k$，因此容易推出 $O(n^2)$ 的做法直接计算出 $f$。

为了进一步优化，我们需要考虑 $\operatorname{EGF}$：$F(x)=\sum\limits_{i=1}^\infty f_i\dfrac{x^i}{i!}$。

先计算出将 $\overline G$ 分为 $\ge 2$ 个好的连通块的方案数，可以得到这一部分的方案数的 $\operatorname{EGF}$ 为：

$$e^{F(x)}-F(x)-1$$

其中 $-F(x)$ 是为了排除掉只有一个连通块的情况。

再进行边界上的一些修正可以得到：

$$F(x)=e^{F(x)}-F(x)+x-1$$

$$e^{F(x)}-2F(x)+x-1=0$$

我们需要求的是 $F(x)$ 的 $n$ 次项系数。

考虑牛顿迭代。设我们需要求 $F(x)$ 的 $0\sim n-1$ 次项系数，即：

$$e^{F(x)}-2F(x)+x-1\equiv 0\pmod{x^n}$$

我们先递归到 $\left\lceil\dfrac{n}{2}\right\rceil$ 规模的子问题，求出一个解 $F_0(x)$，即：

$$e^{F_0(x)}-2F_0(x)+x-1\equiv 0\pmod{x^{\lceil\frac{n}{2}\rceil}}$$

设：

$$G(t)=e^t-2t+x-1$$

根据牛顿迭代的公式可以得到：

$$F(x)=F_0(x)-\dfrac{G(F(x))}{G'(F(x))}$$

$$=F_0(x)-\dfrac{e^{F_0(x)}-2F_0(x)+x-1}{e^{F_0(x)}-2}$$

$$=F_0(x)+\dfrac{2F_0(x)-x-1}{e^{F_0(x)}-2}-1$$

通过这个公式我们可以得到 $F(x)$。通过 $F_0(x)$ 求 $F(x)$ 需要 $O(1)$ 次多项式乘法、求逆、exp，时间复杂度为 $O(n\log n)$。

因此总时间复杂度为 $T(n)=T\left(\dfrac{n}{2}\right)+O(n\log n)=O(n\log n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 400005
#define MOD 998244353
int n,ans,tmp4[N],tmp5[N],tmp6[N],a[N];
int l,lim,invN,r[N],g[N],invG[N],g1[N],inv[N],tmp1[N],tmp2[N],tmp3[N];
void W(int &x,int y) {x+=y;if(x>=MOD) x-=MOD;}
int add(int x,int y) {x+=y;return x<MOD?x:x-MOD;}
int qPow(int x,int y)
{int res=1;for(;y;y>>=1,x=1ll*x*x%MOD) if(y&1) res=1ll*res*x%MOD;return res;}
void init(bool fl,int n)
{
	l=0;lim=1;while(lim<n) ++l,lim*=2;invN=qPow(lim,MOD-2);
	for(int i=0;i<lim;++i) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
	if(fl) for(int i=1,t1,t2,t3,t4;i<lim;i*=2)
	{
		for(int i=1;i<lim;++i) inv[i]=i==1?1:1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
		t1=qPow(3,(MOD-1)/(i*2));t2=qPow(t1,MOD-2);t3=t4=1;
		for(int j=0;j<i;++j,t3=1ll*t3*t1%MOD,t4=1ll*t4*t2%MOD)
			g[i+j]=t3,invG[i+j]=t4;
	}
}
void deriv(int n,int a[]) {for(int i=1;i<n;++i) a[i-1]=1ll*a[i]*i%MOD;a[n-1]=0;}
void integ(int n,int a[]) {for(int i=n-1;i;--i) a[i]=1ll*a[i-1]*inv[i]%MOD;a[0]=0;}
void NTT(bool fl,int a[])
{
	for(int i=0;i<lim;++i) {g1[i]=fl?invG[i]:g[i];if(i<r[i]) swap(a[i],a[r[i]]);}
	for(int i=1,t1,t2;i<lim;i*=2) for(int j=0;j<lim;j+=i*2) for(int k=0;k<i;++k)
	{
		t1=a[j+k];t2=1ll*g1[i+k]*a[i+j+k]%MOD;
		a[j+k]=add(t1,t2);a[i+j+k]=add(t1,MOD-t2);
	}if(fl) for(int i=0;i<lim;++i) a[i]=1ll*a[i]*invN%MOD; 
}
void polyInv(int n,int a[],int res[])
{
	if(n==1) {res[0]=qPow(a[0],MOD-2);return;}polyInv((n+1)/2,a,res);
	for(int i=0;i<n;++i) tmp1[i]=a[i];for(int i=n;i<lim;++i) tmp1[i]=0;
	init(0,n*2);NTT(0,tmp1);NTT(0,res);
	for(int i=0;i<lim;++i) res[i]=(2-1ll*tmp1[i]*res[i]%MOD+MOD)*res[i]%MOD;
	NTT(1,res);for(int i=n;i<lim;++i) res[i]=0;
}
void polyLn(int n,int a[])
{
	init(0,n*2);for(int i=0;i<lim;++i) tmp2[i]=0;
	polyInv(n,a,tmp2);deriv(n,a);NTT(0,a);NTT(0,tmp2);
	for(int i=0;i<lim;++i) a[i]=1ll*a[i]*tmp2[i]%MOD;
	NTT(1,a);integ(n,a);for(int i=n;i<lim;++i) a[i]=0;
}
void polyExp(int n,int a[],int res[])
{
	if(n==1) {res[0]=1;return;}polyExp((n+1)/2,a,res);
	for(int i=0;i<n;++i) tmp3[i]=res[i];for(int i=n;i<lim;++i) tmp3[i]=0;
	polyLn(n,tmp3);for(int i=0;i<n;++i) tmp3[i]=add(a[i],MOD-tmp3[i]);++tmp3[0];
	NTT(0,tmp3);NTT(0,res);for(int i=0;i<lim;++i) res[i]=1ll*res[i]*tmp3[i]%MOD;
	NTT(1,res);for(int i=n;i<lim;++i) res[i]=0;
}
void slv(int n,int res[])
{
    if(n==1) {res[0]=0;return;}slv((n+1)/2,res);
    for(int i=0;i<n;++i) tmp4[i]=res[i],tmp5[i]=0;
    for(int i=n;i<lim;++i) tmp4[i]=tmp5[i]=0;
    polyExp(n,tmp4,tmp5);W(tmp5[0],MOD-2);
    for(int i=0;i<n;++i) tmp4[i]=0;polyInv(n,tmp5,tmp4);
    for(int i=0;i<n;++i) tmp5[i]=add(res[i],res[i]);
    W(tmp5[0],MOD-1);W(tmp5[1],MOD-1);NTT(0,tmp4);NTT(0,tmp5);
    for(int i=0;i<lim;++i) tmp4[i]=1ll*tmp4[i]*tmp5[i]%MOD;
    NTT(1,tmp4);for(int i=0;i<n;++i) W(res[i],tmp4[i]);W(res[0],MOD-1);
}
int main()
{
	scanf("%d",&n);++n;init(1,n*2);slv(n,a);ans=a[n-1];
    for(int i=1;i<n;++i) ans=1ll*ans*i%MOD;
    printf("%d\n",add(add(ans,ans),MOD-2));return 0;
}
```

---

## 作者：cool_milo (赞：5)

# CF1792F1&F2 题解

摘要：自己开的题，跪着也要做完。

## 题意描述

给你 $n$ 个点的完全图，问用红蓝两种颜色给图染色，任意导出子图**均由红色边或蓝色边连通，且均不由两种颜色的边同时连通**的方案数。（必须两种颜色都出现）  

![](https://cdn.luogu.com.cn/upload/image_hosting/0hh0dfcc.png)

图为一种不合法的方案。（由两种颜色的边同时连通）

## 数据范围

$\text{\rm F1 : } n \leq 5\times10^3;\text{\rm F2 : } n \leq 5\times10^4$。

## 观察性质

先删掉“必须两种颜色都出现”的条件，最后答案减去二即可。

### Lemma 1

如果一个导出子图不由蓝色边连通，必由红色边连通，反之亦然。  

证明：不由蓝色边连通，说明蓝色边必然形成若干个分散的连通块。而这些连通块上任意点到其他连通块上的点必然有直接的边相连（导出子图也是完全图），到当前连通块上的点只需经由其他连通块上的点中转即可。  

由此看来，我们只关心任意导出子图均不由两种颜色的边同时连通。

### Lemma 2

合法方案中，考虑没有删去点的原始图，这张图由红色边或蓝色边连通的方案数相等。

证明：显然。

## 大力 DP

设 $f_i$ 为 $i$ 个点的完全图，且原始图由红色边连通的合法方案数（但其实也是由蓝色边连通的合法方案数）。则 $ans = 2f_n-2$。

考察蓝色的边，它不能连通所有的点，我们只考虑 $i$ 号点由蓝色的边连通了哪些点。

容易~~个鬼~~写出状态转移方程：
$$
f_i = (\sum_{j=1}^{i-2}2f_{i-j}f_j\binom{i-1}{j-1}) + f_{1}f_{i-1}\binom{i-1}{i-2}
$$

解释： $j$ 是 $i$ 号点由蓝色的边连通的连通块大小。枚举 $j$ ，那么剩下的部分的方案数就是 $2f_{i-j}$ （剩下的部分既可以由红色边连通，也可以由蓝色边连通），然后乘上在剩下 $i-1$ 个点里选出 $j-1$ 个点的方案数就是答案。但是如果只剩下一个点，那么就无所谓红色或者蓝色了。方案数也就不能乘以二，所以要加入特判。  

边界条件 $f_1=1$，直接算这个式子即可通过 $\text{\rm F1}$。~~使用指令集等优化技巧可能可以通过 $\text{\rm F2}$~~。

## 多项式

你只需要会分治 FFT 就可以了。

我做到这里，一看 $\text{\rm F2}$ 的时限：5.5s，优势在我！  
但是极限数据下暴力 dp 跑了 7s。。。  

看来我还是 too naive。

把式子变得好看一点。。

$$
f_i = (\sum_{j=1}^{i-1}2f_{i-j}f_j\binom{i-1}{j-1}) - (i-1)f_{i-1}
$$

令 

$$
f'_i = \sum_{j=1}^{i-1}f_{i-j}f_j\binom{i-1}{j-1}
$$

那么有

$$
f_i = 2f'_i - (i-1)f_{i-1}
$$

拆开组合数，把 $f'_i$ 写成卷积的形式。

$$
f'_i = \sum_{j=1}^{i-1}f_{i-j}f_j\frac{(i-1)!}{(j-1)!(i-j)!}  
$$
$$
\frac{f'_i}{(i-1)!} = \sum_{j=1}^{i-1}\frac{f_j}{(j-1)!}\frac {f_{i-j}}{(i-j)!}
$$

令 $F_i = \frac{f_i}{(i-1)!},G_i = \frac{f_i}{i!}$，则有：

$$
\frac{f'_i}{(i-1)!} = \sum_{j=1}^{i-1}F_jG_{i-j}
$$
然后就是一个标准的卷积形式，但是这个卷积是在线的，和普通的分治 FFT 不太一样，怎么办呢？  
我们还是有办法算的~  

如果做过 [青蕈领主](https://www.luogu.com.cn/problem/P4566)，那可能就已经知道怎么做了。

没做过的话，先把 $G_i$ 当做已知数列，想正常的分治 FFT，就是分治的时候把 $F_{[l,mid]}$ 卷上 $G_{[1,r-l]}$，给对应右区间加上贡献。  
考虑这个算法什么时候会出问题：$r-l>mid=\frac{(l+r)}{2}$，即 $r>3l$。  
但是满足这个条件的区间是且只会是左端点为 $1$ 的区间。证明就是第一次在分治树上往右走的时候必定满足 $r<2l$，以后 $l$ 不降，$r$ 不增，必然也不会出问题。

我们把对位置 $i$ 的贡献拆成 $3$ 部分，
$$
\frac{f'_i}{(i-1)!} = \sum_{j=i-mid}^{mid}F_jG_{i-j} + \sum_{j=mid+1}^{i-1}F_jG_{i-j} + \sum_{j=1}^{i-mid-1}F_jG_{i-j} 
$$
$$
=\sum_{j=i-mid}^{mid}F_jG_{i-j} + \sum_{j=mid+1}^{i-1}F_jG_{i-j}+\sum_{j=mid+1}^{i-1}F_{i-j}G_{j}
$$

第一部分是在 $[1,r]$ 就能算出来的，剩下两类贡献形式相同，其中 $\sum_{j=mid+1}^{i-1}F_jG_{i-j}$ 是正常分治 FFT 就需要递归算的，所以可以“延迟贡献”，把第三类贡献下放到右区间，和第二类贡献同步计算。就做完了。

## code

~~你的码风怎么那么扭曲？——$\rm{\textcolor{black}{S}\textcolor{red}{word\_K}}$~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;

int n,f[N],F[N],G[N],frac[N],inv[N];

namespace Polynomial{
	#define all(x) x.begin(),x.end()
	const int _g = 3,P = 998244353,_invg = 332748118;
	int rev[N];
	
	inline int mul(int a,int b){
		return (long long)a * b % P; 
	}
	
	inline int add(int a,int b){
		return a + b >= P ? a + b - P : a + b; 
	}
	
	inline void inc(int &a,int b){
		a = add(a,b);
	}
	
	inline int mius(int a,int b){
		return a - b < 0 ? a - b + P : a - b; 
	}
	
	inline void dec(int &a,int b){
		a = mius(a,b);
	}
	
	int qmi(int a,int b)
	{
		int ans = 1;
		while(b)
		{
			if(b & 1)	ans = mul(ans,a);
			a = mul(a,a);
			b>>=1;
		}
		return ans;
	}	
	
	int init(int _lim){
		int lim=1;
		while(lim < _lim)	lim<<=1;
		for(int i=1;i<=lim;i++)
			rev[i] = (rev[i>>1] >> 1) + (i & 1) * (lim >> 1);
		return lim;
	}
	
	struct Poly{
		int lim;
		vector<int> a;
		
		Poly(int lim=0,int x=0) :lim(lim){
			a.resize(lim);
			if(lim)	a[0] = x; 
		}
		
		void NTT(int type){
			for(int i=0;i<lim;i++)
				if(rev[i] > i)	swap(a[i],a[rev[i]]);
			for(int i=1;i<lim;i<<=1)
			{
				int w = qmi(type ? _invg : _g,(P - 1) / i / 2);
				for(int j=0;j<lim;j+=(i<<1))
				{
					int W = 1;
					for(int k=j;k<j+i;k++)
					{
						int r = mul(a[i + k],W);
						a[i + k] = mius(a[k],r);
						a[k] = add(a[k],r);
						W = mul(W,w);
					}
				}
			}
		}
	};
	
	
	Poly Merge(Poly A,Poly B){
		Poly C;
		C=Poly(A.lim,0);
		for(int i=0;i<A.lim;i++)	
			C.a[i] = mul(A.a[i],B.a[i]);
		return C;
	}
		
	Poly operator * (Poly A,Poly B){
		Poly C;
		int l = init(A.lim + B.lim - 1);
		A.lim = l,A.a.resize(l),B.lim = l,B.a.resize(l),C = Poly(l,0);
		A.NTT(0),B.NTT(0);
		C = Merge(A,B);
		C.NTT(1);
		for(int i=0;i<l;i++)
			C.a[i] = mul(C.a[i],qmi(l,P - 2));
		return C;
	}
}

using namespace Polynomial;

Poly A,B,C;

void cdq(int l,int r)
{
	if(l == r)
	{
		if(l > 1)	f[l] = mius(mul(mul(f[l],frac[l-1]),2),mul(l-1,f[l-1])),F[l] = mul(f[l],inv[l-1]),G[l] = mul(f[l],inv[l]);
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l,mid);
	if(l == 1)
	{
		A = Poly(mid - l + 1,0),B = Poly(mid - l + 1,0);
		for(int i=0;i<mid - l + 1;i++)
			A.a[i] = F[i + 1],B.a[i] = G[i + 1];
		C = A * B;
		for(int i=mid - 1;i<=r - 2;i++) 
			inc(f[i + 2],C.a[i]);
	}
	else
	{
		A = Poly(r - l),B = Poly(mid - l + 1);
		for(int i=0;i<r - l;i++)
			A.a[i] = F[i + 1];
		for(int i=0;i<mid - l + 1;i++)
			B.a[i] = G[i + l];
		C = A * B;
		for(int i=mid - l;i<=r - l - 1;i++)
			inc(f[i + l + 1],C.a[i]);
		A = Poly(r - l),B = Poly(mid - l + 1);
		for(int i=0;i<r - l;i++)
			A.a[i] = G[i + 1];
		for(int i=0;i<mid - l + 1;i++)
			B.a[i] = F[i + l];
		C = A * B;
		for(int i=mid - l;i<=r - l - 1;i++)
			inc(f[i + l + 1],C.a[i]);
	}
	cdq(mid+1,r);
}

int main()
{
	scanf("%d",&n);
	frac[0] = 1;
	for(int i=1;i<N;i++)	frac[i] = mul(frac[i-1],i);
	inv[N-1] = qmi(frac[N-1],P-2);
	for(int i=N-2;i>=0;i--)	inv[i] = mul(inv[i+1],i+1);
	f[1] = F[1] = G[1] = 1;
	cdq(1,n);
	printf("%d\n",(((f[n] << 1) - 2) % P + P) % P);
}
```

Q: 这道题那么简单，我一眼就秒了，为什么要跪着做完？  
A: 这是 MnZn 的第一道多项式计数题，我太蒻辣，宁太巨辣~

---

## 作者：Gorenstein (赞：4)

大家都用在线卷积或牛迭去做，其实这个只要求一项，拉反就可以。

令 $G$ 为红图，$\overline G$ 为其补图，即蓝色。

$\bf Lemma.\quad$任意一个图 $G$，$G$ 与 $\overline G$ 至少有一个连通。

依题设，如果 $G$ 连通，则 $\overline G$ 必须不连通。这里钦定 $G$ 连通，且没有必须要有两种颜色的限制。计算出答案之后互换红蓝需要乘 $2$，再减去同一个颜色的 $2$ 种情况。

$\forall S\subseteq G$，$S$ 不同属于 $\overline G$ 的一个连通块中。也即对于 $\overline G$ 每个连通块的所有导出子图 $K$，$\overline K$ 不连通。从而 $\overline G$ 每个连通块的导出子图都符合要求。

令 $\mathcal A$ 为满足条件的（红色图）$G$ 构成的组合类，且不考虑必须既要有蓝边也要有红边的限制。因为 $G$ 与 $\overline G$ 一一对应，所以有：

$$
\mathcal A\cong\mathcal Z+\mathsf{SET}(\mathcal A)-\mathcal A-\mathcal E
$$

即 $\mathcal A$ 同构于符合条件的 $\overline G$ 组合类（$\mathsf{SET}(\mathcal A)-\mathcal A-\mathcal E$）加上仅有一个点的对象 $\mathcal Z$，也即：

$$
-e^{E_f(z)}+2E_f(z)+1=z
$$

这个时候就可以牛迭了。设我们已经求出了 $g(z,f)=e^{f(z)}-2f(z)+z-1=0\pmod{x^{\frac{n}{2}}}$，根据牛迭有：

$$
\begin{aligned}
E_{f_1}(z)&=f(z)-g(z,f)\left(\frac{\partial g}{\partial f}(z,f)\right)^{-1}\\
&=f(z)-\frac{e^{f(z)}-2f(z)+z-1}{e^{f(z)}-2}&\pmod{x^n}
\end{aligned}
$$

但是这只要求一项，所以可以拉反。

$\bf Theorem.\;(The\;Lagrange\;Inversion\;Formula.)$

$$
n[z^n]F^{\langle-1\rangle}(z)^k=k\!\left[z^{n-k}\right]\!\left(\frac{z}{F(z)}\right)^n=k\!\left[z^{-k}\right]\!F(z)^{-n}
$$

这里令 $G(z)=-e^z+2z+1$，则 $G\circ E_f(z)=z$，应用拉格朗日反演有：

$$
f_n=(n-1)!\left[z^{n-1}\right]\!\left(\frac{z}{-e^z+2z+1}\right)^n
$$

直接算即可。

```cpp
ll n,f[N],g[N],zdg[N],nzdg[N];
int main(){
	Pre(),n=read();
	for(ll i=0;i<=n;i++)g[i]=mod-jcinv[i];
	g[0]++,g[1]=(g[1]+2)%mod;
	for(ll i=0;i<n;i++)g[i]=g[i+1];
	Inv(g,zdg,n+1),Pow(zdg,nzdg,n+1,n);
	printf("%lld\n",(nzdg[n-1]*jc[n-1]%mod-1+mod)*2%mod);
	return 0;
}
```

---

## 作者：David24 (赞：3)

结论：一个子点集不可能既不蓝联通也不红联通。

证明：

因为整个图为完全图，所以一个子点集及其相关的边也是完全图。
容易发现，保留所有蓝边和保留所有红边互为补图，接下来只需要证明一个完全图自己或者其补图至少有一个联通。
假设在原图中有两个之间没有边的联通块。
那么在补图中这两个联通块之间的所有点对都有连边，也就一定联通。

有了这个结论，我们只需要计算不存在同时蓝联通和红联通的染色方案即可。

显然整个图作为一个子图也是蓝联通/红联通的。
设 $f_i$ 表示 $i$ 个点，整个图蓝联通的方案数，$g_i$ 表示 $i$ 个点，整个图蓝联通/红联通的方案数。

如何转移？
枚举 1 号点所在的极大蓝联通块大小 $j$，那么这种方案对 $f_i$ 的贡献是 $f_j g_{i - j} \binom{i - 1}{j - 1}$。

因为这个联通块是极大的，所以这 $j$ 个点到其余 $i - j$ 的所有边都必须是红色的，因此此时算出的是对整个图红联通方案数的贡献。
把红色和蓝色互换后所有子图的联通颜色也互换，所以整个图红联通的方案数等于整个图蓝联通的方案数，这样贡献的是对的。

于是有转移方程：$f_i = \sum_{j = 1}^{i-1} \limits f_j g_{i-j} \binom{i-1}{j-1}$，$g_i = 2f_i$。
容易发现第二条对 $i = 1$ 不成立，$f_1, g_1$ 特判即可。
答案是 $g_n - 2$。

将上面的式子拆开：$B_i = \sum_{j = 1}^{i-1} \limits B_{j}A_{i-j} \binom{i-1}{j-1}$。这里的 $B_i$ 对应 $f_i$，$A_i$ 对应 $g_i$。

$B_i = \sum_{j=0}^i \limits B_j A_{i-j}\dfrac{(i-1)!}{(i-j)!(j-1)!} = (i-1)!\sum_{j=0}^i \limits \dfrac{B_j}{(j-1)!} \dfrac{A_{i-j}}{(i-j)!}$。

设 $C_i = \dfrac{A_i}{i!}, D_i = \dfrac{B_i}{(i-1)!}$。

$B_i = (i-1)!\sum_{j=0}^{i} \limits C_{i-j}D_j$。 

这是一个非常漂亮的卷积形式，可惜 $C_i$ 和 $D_i$ 都对 $B_i$ 有依赖性。

考虑根号重构，每 $B$ 个元素计算一次 $C$ 和 $D$ 的卷积。

假设当前计算到 $i$，上一次卷积的编号在 $t$，考虑如何利用卷积结果快速计算 $B_i$。

容易发现，对于 $i-j \le t, j \le t$ 的所有 $j$，$C_{i-j}D_j$ 的和正好在卷积中计算过，答案记在 $C$ 与 $D$ 卷积得到的 $c$ 数组第 $i$ 项。

换言之，$c_i = \sum_{j=i-t}^t \limits C_{i-j}D_j$。

距离 $B_i$ 中的求和式只差 $j < i-t$ 和 $j > t$ 的部分。

容易发现，这两部分的 $j$ 最多只有 $B$ 个，于是我们暴力计算这一部分的贡献即可。

$B_i = (i-1)!(c_i + \sum_{j=0}^{i-t-1} \limits C_{i-j}D_j + \sum_{j=t+1}^{i} \limits C_{i-j}D_j)$。

复杂度为 $O(\dfrac{n^2\log n}{B} + nB)$。

当 $B = \sqrt{n \log n}$ 时最优，为 $O(n\sqrt{n \log n})$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cstdlib>
#include <cmath>
#include <deque>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
const int N = 2e5 + 10, G = 3, GI = 332748118, mod = 998244353, T = 1000;
#define int long long
int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
int n, t;
int qpow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
void NTT(int len, int * a, int coe)
{
    for (int mid = 1; mid < len; mid <<= 1)
    {
        int Wn = qpow(((coe == 1) ? G : GI), (mod - 1) / (mid << 1));
        for (int i = 0; i < len; i += mid << 1)
        {
            int W = 1;
            for (int j = 0; j < mid; j++, W = (W * Wn) % mod)
            {
                int x = a[i + j], y = (a[i + j + mid] * W) % mod;
                a[i + j] = (x + y) % mod;
                a[i + j + mid] = (x - y + mod) % mod;
            }
        }
    }
}
int rev[N], c[N];
void mul(int len, int * a, int * b)
{
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) ? (len >> 1) : 0);
    for (int i = 0; i < len; i++) if (i < rev[i]) swap(a[i], a[rev[i]]); NTT(len, a, 1);
    for (int i = 0; i < len; i++) if (i < rev[i]) swap(b[i], b[rev[i]]); NTT(len, b, 1);
    for (int i = 0; i <= len; i++) a[i] = (a[i] * b[i]) % mod;
    for (int i = 0; i < len; i++) if (i < rev[i]) swap(a[i], a[rev[i]]); NTT(len, a, -1);
    int inv = qpow(len, mod - 2);
    for (int i = 0; i <= len; i++) c[i] = (a[i] * inv) % mod;
}
int len;
int A[N], B[N], C[N], D[N], a[N], b[N], inv[N], fac[N];
void init()
{
    inv[0] = inv[1] = fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * i) % mod;
    for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n; i++) inv[i] = (inv[i - 1] * inv[i]) % mod;
}
signed main()
{
    n = read(); init();
    len = 1;
    A[1] = B[1] = C[1] = D[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (t * 2 < i)
        {
            for (int j = 0; j <= i; j++) B[i] = (B[i] + C[i - j] * D[j] % mod) % mod;
            B[i] = (B[i] * fac[i - 1]) % mod;
            A[i] = (B[i] * 2) % mod;
            C[i] = (A[i] * inv[i]) % mod;
            D[i] = (B[i] * inv[i - 1]) % mod;
        }
        else
        {
            B[i] = c[i];
            for (int j = 0; j < i - t; j++) B[i] = (B[i] + C[i - j] * D[j] % mod) % mod;
            for (int j = t + 1; j <= i; j++) B[i] = (B[i] + C[i - j] * D[j] % mod) % mod;
            B[i] = (B[i] * fac[i - 1]) % mod;
            A[i] = (B[i] * 2) % mod;
            C[i] = (A[i] * inv[i]) % mod;
            D[i] = (B[i] * inv[i - 1]) % mod;
        }
        if (i - t == T)
        {
            while (len <= i * 2) len <<= 1;
            for (int i = 0; i <= len; i++) a[i] = C[i], b[i] = D[i];
            mul(len, a, b);
            t = i;
        }
    }
    printf("%lld\n", (A[n] + mod - 2) % mod);
    return 0;
}
```


---

## 作者：寄风 (赞：2)

提示：这篇题解属于 $O(n^2)$ 不正经做法，如果想要学习多项式科技可移步至其余题解。

## 题解
### F1做法
一个很显然的结论一个图的补图和这个图不可能都不连通。

然后又因为由蓝边构成的图和由红边构成的图互为补图，所以不可能都不连通。

然后对于任意点集 $S$，由蓝边构成的图和由红边构成的图不能都连通，然后又因为由蓝边构成的图和由红边构成的图是完全等价的，所以不妨设蓝边构成的图不连通。

设 $dp_i$ 表示大小为 $i$ 的满足约束的图的个数。

转移的话，考虑 $1$ 所在蓝色边构成的连通块，设大小为 $s$，那么这个块就是蓝色连接的，但由于蓝色连接和红色连接完全的等价，所以方案数还是 $dp_s$。

剩下的点呢？它们是红色还是蓝色没有影响，都可以选。

但是注意当只剩余一个点的时候只有一种选法。

答案最后要减 $2$，因为至少要染一条红边和一条蓝边。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n , dp[1000005] , C[1000005];
inline void add(int &x,int y){
    x+=y-mod;
    x+=(x>>31)&mod;
} 
int main(){
	cin>>n; 
	dp[1]=C[0]=1;
	for(int i=2;i<=n;i++) {
		for(int j=i-1;j;j--) add(C[j],C[j-1]);		
		for(int j=1;j<i;j++) add(dp[i],1LL*C[j-1]*dp[j]%mod*dp[i-j]%mod*(2-(j==i-1?1:0))%mod);
	}
    add(dp[n],dp[n]-2);
	cout<<dp[n]<<endl;
	return 0;
}
```
### F2做法
你发现数据范围从 $5\times 10^3$ 扩大到了 $5\times 10^4$，$n^2$ 的运算量达到了 $2.5\times 10^9$，但是时限有 $5.5$ s，按理说能过。

自信的交了一法 F1 的代码上去，T 了。

于是开始卡常。

有位卡常带师说过，
>数组的 Cache miss 是致命的。

我们看到我们 F1 的代码，$dp$ 数组的内存访问极其不连续，`dp[j]` 和 `dp[i-j]` 造成了大量的 Cache miss，所以我们再开一个 $dp2$，里面存的东西和 $dp$ 一模一样，但我们更新的时候只访问 `dp[j]`，访问 `dp[i-j]` 改成访问 `dp2[i-j]`，这样就减少了 Cache miss。

然后这个问号表达式很烦，注意到只有 $j=i-1$ 的时候才不会乘 $2$，这个时候访问到的 `dp2[i-j]` 就是 `dp2[1]`，所以我们把 `dp2[1]` 设成和 `dp1[1]` 一样，其余的设成 $dp1$ 的两倍，这样就避免了问号表达式的计算，减小了常数。

然后交一发就过了。

多说一句，较为正常的正解大概 3s 就能跑完，为啥要开 5.5s 呢，这不是放暴力过吗？

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n , dp1[1000005] , dp2[1000005] , C[1000005];
//use one dp can make Cache miss and TLE
inline void add(int &x,int y){
    x+=y-mod;
    x+=(x>>31)&mod;
} 
int main(){
	cin>>n; 
	dp1[1]=dp2[1]=C[0]=1;
	for(int i=2;i<=n;i++) {
		for(int j=i-1;j;j--) add(C[j],C[j-1]);		
		for(int j=1,k=i-1;j<i;j++,k--) add(dp1[i],(1LL*C[j-1]*dp1[j]%mod*dp2[k]%mod)%mod);
        dp2[i]=dp1[i]<<1;
        if(dp2[i]>mod)dp2[i]-=mod;
	}
	cout<<(dp2[n]-2+mod)%mod;
	return 0;
}
```

---

