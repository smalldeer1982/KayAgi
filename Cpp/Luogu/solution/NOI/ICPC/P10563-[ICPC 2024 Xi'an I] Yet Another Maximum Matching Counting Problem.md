# [ICPC 2024 Xi'an I] Yet Another Maximum Matching Counting Problem

## 题目描述

在一个二维平面上，

你有一组点 $\{(x_i,y_i)\}$，满足 $1\le x_i\le n, 1\le y_i\le m$（$x_i$ 和 $y_i$ 都是整数），并且没有两个点具有相同的坐标。

如果两个点具有相同的水平或垂直坐标，我们将在这两个点之间连接一条边。这将形成一个图。

你需要找到由所有可能的 $2^{nm}-1$ 个非空集合形成的图中的最大匹配数之和，并输出结果对 $998244353$ 取模。

在这里，图中的最大匹配数定义为：选择最多的边，使得任何两条边之间没有公共顶点。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
10
1 1
1 2
2 2
4 4
3 3
5 5
1 8
20 20
100 100
500 500```

### 输出

```
0
1
10
241456
964
200419152
448
985051144
370696900
357517517```

# 题解

## 作者：Larunatrecy (赞：11)

首先，对于一个确定的图，我们先考虑怎么计算最大匹配数，设图中一共有 $m$ 个连通块，第 $i$ 个大小为 $s_i$，那么最大匹配数有显然上界 $\sum_i \lfloor \frac{s_i}{2}\rfloor$，并且我们总是可以取到这个上界的，这一点不难证明。

现在考虑计数，因为 $\lfloor \frac{s_i}{2}\rfloor=\frac{s_i-[s_i\bmod 2\equiv 1]}{2}$，我们只需要对 $s_i,[s_i\bmod 2\equiv 1]$ 分别求和就行了，前者就是 $nm2^{nm-1}$，后者就是求有奇数个点的连通块个数。

考虑一个二分图，左部点代表所有行，右部点代表所有列，那么每个原图的点就代表了一条新图中的边，并且原图和新图的连通关系是等价的，我们只需要求所有这样的二分图中的奇数条边的连通块个数和就行了，只要能求出 $f_{i,j}$ 表示 $i$ 个左部点，$j$ 个右部点的奇数条边的连通二分图个数即可，设其二元生成函数为 $F$。

设 $i$ 个左部点，$j$ 个右部点的，奇数/偶数条边的二分图的二元生成函数为 $G_1,G_0$，那么有：

$F=\frac{\ln(G_0+G_1)-\ln(G_0-G_1)}{2}$，因此只需要实现二元多项式的 Ln 就可以通过了。 

多组询问也不难通过二维 FFT 做，因此复杂度为 $O(n^2\log n)$，但是因为常数过大所以范围开的比较小。

---

## 作者：Seauy (赞：4)

题面简单翻译一下，$n$ 行 $m$ 列的网格中点被染成黑白两种颜色，若两个黑点同行或同列就连边，问在所有染色情况下，最后形成的图的最大匹配数之和。

网格中存在行/列的限制有个套路，就是建左部有 $n$ 个点右部有 $m$ 个点的二分图，左部第 $i$ 个点与右部第 $j$ 个点的连边代表点 $(i,j)$，这样同行/列的点被抽象成了共用端点的边。现在每种染色情况与每种二分图连边情况一一对应，且原图联通性与二分图联通性一致。

从二分图视角考虑匹配的过程，发现有 $t$ 条边的联通块最多能贡献原图中 $\lfloor \frac{t}{2} \rfloor$ 个匹配且这个最大值总能取到，具体来讲的话可以找出联通块的一棵生成树，每次都能找到共用端点的两条边删去（在树最“边缘”的两条），剩下的边依然形成一棵树，直到只剩下一或零条边。

现在问题变成如何求所有连边情况下 $\lfloor \frac{t}{2} \rfloor$ 之和的和。可以把 $\lfloor \frac{t}{2} \rfloor$ 拆成 $\frac{1}{2}(t-(t \bmod 2))$，$t$ 的和很好求，就是 $nm2^{nm-1}$，接下来只要考虑如何统计 $t\bmod 2$ 的和，即有奇数条边的联通块个数之和。设 $f_{i,j}$ 为左部有 $i$ 个点右部有 $j$ 个点的奇数边联通二分图个数，计算每种联通块在多少种连边情况中出现，得到答案的式子：

$$ nm2^{nm-1}-\sum_{i=1}^n \sum_{j=1}^m {n\choose i} {m\choose j} f_{i,j} 2^{(n-i)(m-j)} $$

只要得到 $f$ 就能 $O(Tnm)$ 暴力求出答案了（此处可以二元NTT做到 $O(T+nm\log m)$）。计算 $f$ 有两个限制，联通和奇数条边，联通性的套路可以参考 [[集训队作业2013] 城市规划](https://www.luogu.com.cn/problem/P4841)，我们反过来计算奇数边非联通图个数，枚举某个点所在联通块的左部结点数 $i$ 和右部结点数 $j$，设 $g_{i,j}$ 为左部有 $i$ 个点右部有 $j$ 个点的联通二分图总数，就有

$$ f_{n,m}=2^{nm-1}-\sum_{i=1}^{n-1} \sum_{j=1}^{m-1} {n-1 \choose i-1}{m\choose j} g_{i,j}2^{(n-i)(m-j)-1}-2^{(n-1)m-1}-\sum_{i=1}^{n-1} {n-1 \choose i-1}f_{i,m}-\sum_{j=1}^{m-1}{m \choose j}f_{n,j} $$

所以还要得到 $g$，他的递推关系是

$$ g_{n,m}=2^{nm}-\sum_{i=1}^{n-1}\sum_{j=1}^{m-1} {n-1 \choose i-1}{m\choose j} g_{i,j}2^{(n-i)(m-j)}-2^{(n-1)m}-\sum_{i=1}^{n-1} {n-1 \choose i-1}g_{i,m}-\sum_{j=1}^{m-1}{m \choose j}g_{n,j} $$

$n$ 或 $m$ 为 $1$ 或 $0$ 的情况单独考虑一下。观察形式发现只要算出 $g$ 就能用简单方法得到 $f$（暴力 $O(nm(n+m))$，可能可以用多项式优化一下），并且 $g$ 的递推有很好看的形式：

$$ \sum_{i=1}^n\sum_{j=0}^m {n-1\choose i-1}{m\choose j}g_{i,j}2^{(n-i)(m-j)}=2^{nm} $$

做简单变换可得

$$ \sum_{i=0}^{n-1}\sum_{j=0}^m \frac{g_{i+1,j}}{i!j!}\frac{2^{(n-1-i)(m-j)}}{(n-1-i)!(m-j)!}=\frac{2^{nm}}{(n-1)!m!} $$

还是个二元多项式卷积的形式，具体来说，设母函数

$$ G(x,y)=\sum_{i=0}^{+\infty}\sum_{j=0}^{+\infty}\frac{g_{i+1,j}}{i!j!}x^iy^j $$

$$ H(x,y)=\sum_{i=0}^{+\infty}\sum_{j=0}^{+\infty} \frac{2^{ij}}{i!j!}x^iy^j $$

$$ P(x,y)=\sum_{i=0}^{+\infty}\sum_{j=0}^{+\infty} \frac{2^{(i+1)j}}{i!j!}x^iy^j $$

就有 $G(x,y)H(x,y)=P(x,y)$（当然 $P$ 是 $H$ 的偏导但不重要），也就是说只要做二元多项式求逆算出 $G(x,y)=\frac{P(x,y)}{H(x,y)}$ 就大功告成了。

然后请教了 [NaCly_Fish](https://www.luogu.com.cn/user/115864)，他说可以把二元多项式看成关于 $y$ 的一元多项式只不过系数是关于 $x$ 的多项式，然后正常做普通多项式求逆就好了（在此非常感谢鱼神的帮助！），复杂度 $O(nm\log m)$。

下面给个总复杂度 $O(nm(n+m+T))$ 的丑八怪写法，按道理来说应该龟速（复杂度不是最好的）但是截止到写题解时还是榜一（？！？！）

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXT=100,MAXN=500,MOD=998244353,ALL=MAXN*MAXN;

int T,n,m;
int f[MAXN+5][MAXN+5],g[MAXN+5][MAXN+5]; 
int Base[ALL+5],fac[MAXN+5],faci[MAXN+5],C[MAXN+5][MAXN+5];
int H[MAXN+5][MAXN+5];

inline int POW(int a,int b)
{
	int res=1;
	for(int i=a;b;b>>=1,i=1ll*i*i%MOD)
		if(b&1) res=1ll*res*i%MOD;
	return res;
}

const int SIZ=1024;
int r[SIZ],A[2][SIZ];
int numlg,numlen;
inline void GetR() {for(int i=1;i<numlen;i++) r[i]=((r[i>>1]>>1)|((i&1)<<(numlg-1)));}
inline void numNTT(int x,bool t)
{
	for(int i=0;i<numlen;i++) if(i<r[i]) swap(A[x][i],A[x][r[i]]);
	for(int i=1;i<numlen;i<<=1)
	{
		int uni=POW(3,(MOD-1)/(i<<1));
		for(int j=0;j<numlen;j+=(i<<1))
		{
			int Root=1;
			for(int k=0;k<i;k++,Root=1ll*Root*uni%MOD)
			{
				int a=A[x][j+k],b=1ll*Root*A[x][i+j+k]%MOD;
				A[x][j+k]=a+b; if(A[x][j+k]>=MOD) A[x][j+k]-=MOD;
				A[x][i+j+k]=a-b; if(A[x][i+j+k]<0) A[x][i+j+k]+=MOD;
			}
		}
	}
	if(t) return;
	int div=POW(numlen,MOD-2);
	reverse(A[x]+1,A[x]+numlen);
	for(int i=0;i<numlen;i++) A[x][i]=1ll*A[x][i]*div%MOD;
}
struct Poly
{
	int data[MAXN];
	inline Poly operator * (const Poly &a)
	{
		for(int i=0;i<MAXN;i++) A[0][i]=data[i],A[1][i]=a.data[i];
		for(int i=MAXN;i<SIZ;i++) A[0][i]=A[1][i]=0;
		numNTT(0,1),numNTT(1,1);
		for(int i=0;i<SIZ;i++) A[0][i]=1ll*A[0][i]*A[1][i]%MOD;
		numNTT(0,0);
		Poly res;
		for(int i=0;i<MAXN;i++) res.data[i]=A[0][i];
		return res;
	}
	inline Poly operator * (int a)
	{
		Poly res;
		for(int i=0;i<MAXN;i++) res.data[i]=1ll*data[i]*a%MOD;
		return res;
	}
	inline Poly operator + (const Poly &a)
	{
		Poly res;
		for(int i=0;i<MAXN;i++) {res.data[i]=data[i]+a.data[i]; if(res.data[i]>=MOD) res.data[i]-=MOD;}
		return res;
	}
	inline void operator += (int a) {data[0]+=a; if(data[0]>=MOD) data[0]-=MOD;}
	inline Poly operator - (const Poly &a)
	{
		Poly res;
		for(int i=0;i<MAXN;i++) {res.data[i]=data[i]-a.data[i]; if(res.data[i]<0) res.data[i]+=MOD;}
		return res;
	}
	inline void operator = (int a) {data[0]=a; for(int i=1;i<MAXN;i++) data[i]=0;}
	inline void neg() {for(int i=0;i<MAXN;i++) {data[i]=-data[i]; if(data[i]<0) data[i]+=MOD;}}
};
int lglen,len,oppo[SIZ];
inline void GetOppo() {for(int i=1;i<len;i++) oppo[i]=((oppo[i>>1]>>1)|((i&1)<<(lglen-1)));}
struct Matrix
{
	Poly data[SIZ];
	inline void NTT(bool t)
	{
		for(int i=0;i<len;i++) if(i<oppo[i]) swap(data[i],data[oppo[i]]);
		for(int i=1;i<len;i<<=1)
		{
			int uni=POW(3,(MOD-1)/(i<<1));
			for(int j=0;j<len;j+=(i<<1))
			{
				int Root=1;
				for(int k=0;k<i;k++,Root=1ll*Root*uni%MOD)
				{
					Poly a=data[j+k],b=data[i+j+k]*Root;
					data[j+k]=a+b,data[i+j+k]=a-b;
				}
			}
		}
		if(t) return;
		int div=POW(len,MOD-2);
		reverse(data+1,data+len);
		for(int i=0;i<len;i++) data[i]=data[i]*div;
	}
}P,H_,h;

void GetInv(int xi)
{
	if(xi==1) {H_.data[0].data[0]=1;return;}
	GetInv((xi+1)>>1);
	numlg=ceil(log(2*xi)/log(2));
	numlen=(1<<numlg);
	GetR();
	for(int i=0;i<xi;i++) A[0][i]=H_.data[0].data[i],A[1][i]=H[i][0];
	for(int i=xi;i<numlen;i++) A[0][i]=A[1][i]=0;
	numNTT(0,1),numNTT(1,1);
	for(int i=0;i<numlen;i++)
	{
		int tmp=2-1ll*A[0][i]*A[1][i]%MOD; if(tmp<0) tmp+=MOD;
		A[0][i]=1ll*A[0][i]*tmp%MOD;
	}
	numNTT(0,0);
	for(int i=0;i<xi;i++) H_.data[0].data[i]=A[0][i];
	for(int i=xi;i<numlen;i++) H_.data[0].data[i]=0;
}

void GetH_(int xi)
{
	if(xi==1) {GetInv(MAXN);return;}
	GetH_((xi+1)>>1);
	lglen=ceil(log(2*xi)/log(2));
	len=(1<<lglen);
	GetOppo();
	for(int i=0;i<xi;i++)
		for(int j=0;j<MAXN;j++)
			h.data[i].data[j]=H[j][i];
	for(int i=xi;i<len;i++) h.data[i]=0;
	h.NTT(1),H_.NTT(1);
	for(int i=0;i<len;i++)
	{
		Poly tmp=h.data[i]*H_.data[i];
		tmp.neg(),tmp+=2;
		H_.data[i]=H_.data[i]*tmp;
	}
	H_.NTT(0);
	for(int i=xi;i<len;i++) H_.data[i]=0;
}

inline void pret()
{
	fac[0]=fac[1]=faci[0]=faci[1]=1;
	for(int i=2;i<=MAXN;i++) faci[i]=1ll*(MOD-MOD/i)*faci[MOD%i]%MOD;
	for(int i=2;i<=MAXN;i++) fac[i]=1ll*fac[i-1]*i%MOD,faci[i]=1ll*faci[i-1]*faci[i]%MOD;
	Base[0]=1; for(int i=1;i<=ALL;i++) {Base[i]=Base[i-1]<<1; if(Base[i]>=MOD) Base[i]-=MOD;}
	for(int i=0;i<=MAXN;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++) {C[i][j]=C[i-1][j-1]+C[i-1][j]; if(C[i][j]>=MOD) C[i][j]-=MOD;}
	}
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<=MAXN;j++)
			H[i][j]=1ll*Base[i*j]*faci[i]%MOD*faci[j]%MOD;
	GetH_(MAXN+1);
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<=MAXN;j++)
			P.data[j].data[i]=1ll*Base[(i+1)*j]*faci[i]%MOD*faci[j]%MOD;
	P.NTT(1),H_.NTT(1);
	for(int i=0;i<len;i++) P.data[i]=P.data[i]*H_.data[i];
	P.NTT(0);
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<=MAXN;j++)
			g[i+1][j]=1ll*P.data[j].data[i]*fac[i]%MOD*fac[j]%MOD;
	for(int i=1;i<=MAXN;i++) f[1][i]=f[i][1]=i&1;
	for(int i=2;i<=MAXN;i++)
		for(int j=2;j<=MAXN;j++)
		{
			f[i][j]=g[i][j];
			for(int k=1;k<i;k++) {f[i][j]+=1ll*C[i-1][k-1]*g[k][j]%MOD; if(f[i][j]>=MOD) f[i][j]-=MOD;}
			for(int l=1;l<j;l++) {f[i][j]+=1ll*C[j][l]*g[i][l]%MOD; if(f[i][j]>=MOD) f[i][j]-=MOD;}
			f[i][j]=1ll*f[i][j]*faci[2]%MOD;
			for(int k=1;k<i;k++) {f[i][j]-=1ll*C[i-1][k-1]*f[k][j]%MOD; if(f[i][j]<0) f[i][j]+=MOD;}
			for(int l=1;l<j;l++) {f[i][j]-=1ll*C[j][l]*f[i][l]%MOD; if(f[i][j]<0) f[i][j]+=MOD;}
		}
}

int main()
{
	pret();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&m);
		int ans=1ll*n*m*Base[n*m-1]%MOD;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				ans-=1ll*C[n][i]*C[m][j]%MOD*f[i][j]%MOD*Base[(n-i)*(m-j)]%MOD;
				if(ans<0) ans+=MOD;
			}
		ans=1ll*ans*faci[2]%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

