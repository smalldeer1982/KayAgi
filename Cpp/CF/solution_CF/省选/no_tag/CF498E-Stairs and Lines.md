# Stairs and Lines

## 题目描述

You are given a figure on a grid representing stairs consisting of 7 steps. The width of the stair on height $ i $ is $ w_{i} $ squares. Formally, the figure is created by consecutively joining rectangles of size $ w_{i}×i $ so that the $ w_{i} $ sides lie on one straight line. Thus, for example, if all $ w_{i}=1 $ , the figure will look like that (different colors represent different rectangles):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF498E/c6fb7071f303e3a83e13342e5c3149c16ebc124c.png)And if $ w={5,1,0,3,0,0,1} $ , then it looks like that:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF498E/81e637747a334268bc5ee9870a6a97e0703d91ae.png)Find the number of ways to color some borders of the figure's inner squares so that no square had all four borders colored. The borders of the squares lying on the border of the figure should be considered painted. The ways that differ with the figure's rotation should be considered distinct.

## 说明/提示

All the possible ways of painting the third sample are given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF498E/c78e55a2090821d569ec77d319a0ea4d99457273.png)

## 样例 #1

### 输入

```
0 1 0 0 0 0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
0 2 0 0 0 0 0
```

### 输出

```
7
```

## 样例 #3

### 输入

```
1 1 1 0 0 0 0
```

### 输出

```
9
```

## 样例 #4

### 输入

```
5 1 0 3 0 0 1
```

### 输出

```
411199181
```

# 题解

## 作者：warzone (赞：11)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/wangrx/solution-cf498e)

## 题目大意
已知一排高度为 $1$ 到 $7$ 的整数的，单调不降的阶梯，高度为 $i$ 的阶梯有 $w_i$ 个。  
你要给**阶梯块**的**边沿**上色，要求**整个阶梯**的边缘必须上色。  
求上色的方案数，答案对 $10^9+7$ 取模。  
$\texttt{Data Range: }0\le w_i\le10^5$

------------------------------
## 题解
非常好的一道题，有利于提升对状压 dp 的理解。  

首先肯定是用 $0$ 表示上了色，$1$ 表示没上色。  
（为什么不是反过来？ 因为整个阶梯的边缘必须上色，这样阶梯上升的时候补 $0$ 就行）  

设 $dp_{i,k}$ 表示第 $i$ 列阶梯**右侧边沿**涂色状态为 $k$ 的方案总数。  
（$i=0$ 时，表示的是第 $1$ 个阶梯的左侧边沿）  

$k$ 为一个二进制串，从低位到高位依次表示阶梯从低到高的涂色状态。  
（由于左右两侧边缘必须上色，可知初始状态 $dp_{0,0}=1$，答案为 $dp_{\sum w_i,0}$）

考虑 $dp_{i-1,j}$ 和 $dp_{i,k}$ 之间的转移，我们只需要考虑二者之间横线的涂色状态：  

![](https://cdn.luogu.com.cn/upload/image_hosting/encibtj9.png)

由此可知，
- 当阶梯块的左右两侧同时涂色时，上下两侧不能同时涂色。
- 当阶梯块的左右两侧未同时涂色时，上下两侧能同时涂色。

因此，只要检查 $j\operatorname{or} k$ 的每一位，就可以以插头 dp 的形式转移。

时间复杂度 $\Theta(\sum (2^{i})^3w_i)$ 。
- 第一个 $2^i$ 表示枚举 $j$ 的状态。
- 第二个 $2^i$ 表示枚举 $k$ 的状态。
- 第三个 $2^i$ 表示枚举横线的状态。  

显然，$w_i$ 较大的时候，该做法不能通过。

--------------------------------

我们发现，转移只与高度和 $j,k$ 有关，与 $i$ 是无关的。  
我们可以将 第 $i-1$ 列右侧边沿**所有可能的状态**   
至 第 $i$ 列右侧边沿**所有可能的状态** 的转移写成一个矩阵 $A$。  
具体的，构造方阵 $A$，$A_{k,j}$ 表示 $dp_{i-1,j}$ 向 $dp_{i,k}$ 的贡献。  

于是就可以用矩阵快速幂完成同一高度的转移了。  
至于如何构造 $A$，暴力枚举 $j,k$，按照原来的方法考虑横线的状态就可以了。  
$\Theta(\sum (2^i)^2)$ 就可以递推地将 $7$ 个矩阵全部构造出来。

时间复杂度被优化到 $\Theta(\sum (2^{i})^3\log w_i)$，可以通过。

```cpp
#include<stdio.h>
#include<string.h>
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned char byte;
struct READ{//快读
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator>>(register type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
const word mod=1e9+7;
template<word msize,word nsize>
struct matrix{//矩阵
	word num[msize][nsize];
	inline matrix(){}
	inline matrix(const matrix&p){
		memcpy(num,p.num,sizeof(num));}
	inline word* operator[](word id){return num[id];}
	template<word lsize>
	inline matrix<msize,lsize> operator*
		(const matrix<nsize,lsize>&p){//矩阵乘法
			matrix<msize,lsize> out;
			register ull ans;
			for(register word i=0;i<msize;++i)
				for(register word j=0;j<lsize;++j){
					for(register word k=ans=0;k<nsize;++k){
						ans+=(ull)(num[i][k])*p.num[k][j]%mod;
						if(ans>=mod) ans-=mod;
					}
					out[i][j]=ans;
				}
			return out;
		}
};
template<word size>
struct vector: public matrix<size,1>{//向量（派生自矩阵）
	inline vector(){}
	template<typename type>
	inline vector(const type &p){
		memcpy(matrix<size,1>::num,p.num,
			sizeof(matrix<size,1>::num));}
	inline word& operator[](word id){
		return matrix<size,1>::num[id][0];}
};
//0 涂了
//1 没涂
template<byte size>
struct getans{//同一高度的转移
	matrix<1<<(size+1),1<<(size+1)> A0,A1;
	// A0 表示顶端横线涂了时的贡献
	// A1 表示顶端横线没涂时的贡献
	vector<1<<(size+1)> out;
	getans<size-1> down;
	inline getans():down(){
		//O(n^2) 枚举
		for(register word i=0;i<1u<<(size+1);++i)
			for(register word j=0;j<1u<<(size+1);++j){
				register word num0=down.A0[i&~(1<<size)][j&~(1<<size)];
				register word num1=down.A1[i&~(1<<size)][j&~(1<<size)];
				//考虑顶端横线，进行递推
				if((i|j)>>size&1) A0[i][j]=A1[i][j]=(num0+num1)%mod;
				// 左右不同时涂色，上下可同时涂色
				else A0[i][j]=num1,A1[i][j]=(num0+num1)%mod;
				// 左右同时涂色，上下不能同时涂色
			}
	}
	inline word operator()(){
		down();
		memcpy(out.num,down.out.num,4u<<size);
		memset(out.num+(1u<<size),0,4u<<size);
		//高度增加时补齐 0
		register word k;
		for(cin>>k;k;k>>=1){
			if(k&1) out=A0*out;
			A0=A0*A0;
		}//矩阵快速幂
		return out[0];//最右侧横线必涂色
	}
};
template<>
struct getans<0xff>{//边界情况
	matrix<1,1> A0,A1;
	vector<1> out;
	inline getans(){A0[0][0]=1,A1[0][0]=0;}//底端横线必涂色
	inline word operator()(){return out[0]=1;}//最左侧横线必涂色
};
getans<6> f;
int main(){
	printf("%u",f());
	return 0;
}

```

---

## 作者：PragmaGCC (赞：8)

首先看到高度很小，考虑状压。

我们发现每一列的横线不会对下一列产生影响，因此我们可以考虑把枚举横线放到转移中。

因此我们有 $f_{i,S}$ 表示当前考虑第 $i$ 列，这一列的竖线涂色状态为 $S$，且之前的全部合法的方案数。

我们将 $0$ 设为涂色，$1$ 设为不涂色，这样在高度不同的地方我们就可以直接看成在前面补 $0$。

考虑同高度该怎么做：

由于每次转移都是从一个高度 $h$ 转移到下一个高度 $h$，所以每次的转移都应当是相同的。每一个 $f_{i-1,S_j}$ 都会以一个固定的系数累加到 $f_i,S_k$，设这个系数为 $g_{S_j,S_k}$，可以暴力求。

并且这个转移只与上一列的状态有关，所以可以压掉 $i$ 这一维。

这样就可以直接做了。复杂度为 $O(\sum 2^{2w}w)$，爆炸了。

注意到 $f$ 的大小是 $2^h$，$g$ 的大小是 $2^h \times 2^h$，并且 $g$ 是固定的。因此可以用矩阵加速递推，这样可以优化到一个 $\log$，非常优秀。

这里有一个高明的求 $g$ 的方法：

考虑到每一个正方形只要有一条边没被涂色即可，因此只要把上下左右的涂色情况或起来就可以得到每一个正方形的合法情况，判断最后是不是全部合法即可。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7, N = 128;
int n, m = 2;
struct Matrix {
    int a[N][N];
    Matrix() { memset(a, 0, sizeof(a)); }
    void reset() { for (int i = 0; i < N; i++) a[i][i] = 1; }
    Matrix operator*(const Matrix &rhs) const {
        Matrix res;
        int r;
        for (int i = 0; i < m; i++)
            for (int k = 0; k < m; k++) {
                r = a[i][k];
                for (int j = 0; j < m; j++)
                    res.a[i][j] = (res.a[i][j] + 1ll * rhs.a[k][j] * r % MOD) % MOD;
            }
        return res;
    }
} f, g;
void init(int w) {
    g = Matrix();
    for (int L = 0; L < m; L++) for (int R = 0; R < m; R++) 
        for (int k = 0; (k << 1) < m; k++)
            g.a[L][R] += (L | R | k | (k << 1)) == m - 1;
}
Matrix qpow(Matrix f, int b) {
    Matrix res; res.reset();
    for (; b; b >>= 1, f = f * f)
        if (b & 1) res = res * f;
    return res;
}
int main(void) {
    f.reset();
    for (int w; m <= 128; m <<= 1) {
        scanf("%d", &w);
        if (!w) continue;
        init(w);
        g = qpow(g, w);
        f = g * f;
    }
    printf("%d\n", f.a[0][0]);
    return 0;
}
```





---

## 作者：CDFLS_mao_zx (赞：6)

## CF498E

### 题意:

方格中给定一个楼梯，需要将方格的边缘选择一部分，使得选择的那些部分不会围成一个 $1*1$ 的方格。楼梯的边缘必选，楼梯高度不超过 $7$ 。



### 思路：

计数问题，每一列安排的方式仅仅和上一列有关，考虑 $\text{DP}$ ，高度不超过 $7$ 这很状压。

我们设 $dp[i][s]$ 表示考虑到第 $i$ 列，这一列竖着的边和横着的边填的状态时 $s$ 的总方案数，转移方程不难推出。

很快我们发现其实并没有必要记录横着的边的状态，因为下一次的转移不需要它。

于是 $dp[i][s]$ 表示考虑到第 $i$ 列，竖着的边填的状态为 $s$ 的方案总数。

枚举横着的边填的状态转移即可，判断有一个比较方便的办法：

```cpp
if(!(j&k&(s|(1<<i))&((s<<1)|1)))
dp[i][k]+=dp[i-1][j];
```

意思是上下左右不能都有。

这样的复杂度高达 $\sum w_i * 2^{21}$ 难以通过本题。

可以预处理出当前 $j-k$ 的转移系数，然后直接用这个转移系数搞。

复杂度 $\sum w_i *2^{14} + 2^{21} *7$ ，同样难以通过。

考虑到 $w_i$ 有点大，然而转移系数又被我们搞出来了，不妨直接矩阵乘法优化。

复杂度 $(7+\sum{logw_i}) * 2^{21}$。

稍微有点大，矩阵乘法的时候可以每 $8$ 次加法取一次 $mod$ ，并且小矩阵的转移建立小矩阵。

注意处理好高度不同的地方的交接。

这个暴力做一次转移就行了。

### 参考代码:

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define next nxt
#define LL long long
using namespace std;
inline int read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
int i,j,k,n,s,t,m;
const int mod=1e9+7;
const int N=7e3+10;
struct matri{
	int n,m,num[128][128];
	friend matri operator *(matri aa,matri bb)
	{
		matri ret;
		ret.n=bb.n,ret.m=aa.m;
		for(int i=0;i<=ret.n;i++)
		for(int j=0;j<=ret.m;j++)
		{
			ret.num[i][j]=0;
			for(int k=0;k<=aa.n;k++)
			ret.num[i][j]=(ret.num[i][j]+1ll*aa.num[k][j]*bb.num[i][k]%mod)%mod;
		}
		return ret;
	}
}E,Z,S,Ans;
int w[10];
inline void quick(matri &ret,matri aa,int ss)
{
	while(ss)
	{
		if(ss&1)
		ret=ret*aa;
		aa=aa*aa;
		ss>>=1;
	}
}
int dp[N][128],p[128][128];
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	matri Ans;
	Ans.n=127,S.n=S.m;
	for(i=0;i<=127;i++)
	E.num[i][i]=1;
	int maxn=0;
	for(i=1;i<=7;i++)
	{
		read(w[i]);
		if(w[i])maxn=i;
	}
	int now=0,tmp=0;
	if(w[1]==0)
	dp[now][1]=1;
	else
	dp[now][0]=1;
	p[0][0]=p[1][0]=p[0][1]=1;
	for(i=1;i<=maxn;i++)
	{
		tmp|=1<<i;
		if(w[i])
		{
			Ans.n=S.n=S.m=(1<<i)-1;
			for(int j=0;j<1<<i;j++)
			Ans.num[j][0]=dp[now][j];
			for(int j=0;j<1<<i;j++)
			for(int k=0;k<1<<i;k++)
			S.num[j][k]=p[j][k];
			quick(Ans,S,w[i]-1);
			for(int j=0;j<1<<i;j++)
			dp[now][j]=Ans.num[j][0];
		}
		memset(p,0,sizeof(p));
		if(w[i+1])
		{	
			now++;
			for(k=0;k<1<<(i+1);k++)
			for(s=0;s<1<<i;s++)
			for(j=0;j<1<<(i+1);j++)
			{
				if(!(j&k&(s|(1<<i))&((s<<1)|1)))
				p[j][k]++;
				if(!((j|tmp)&k&(s|(1<<i))&((s<<1)|1)))
				dp[now][k]=(dp[now][k]+dp[now-1][j])%mod;
			}
			tmp=1<<i+1;
		}
	}
	printf("%d",dp[now][(1<<maxn)-1]);
	return 0;
}
```





---

## 作者：不知名用户 (赞：0)

题意：给定一个高度为 $7$ 的阶梯，高度为 $i$ 的阶梯宽度为 $w_i$，现在你需要给阶梯上网格的边缘上色，要求最外层的边缘必须上色，且不能使任意一个 $1 \times 1$ 的小正方形四个边都被上色。求方案数对 $10^9+7$ 取模。

考虑递推 `DP`，从左往右考虑，由于考虑到某一列时关乎后面状态的只有这一列的涂色，所以状态为：$f_{i,mask}$ 表示考虑到第 $i$ 列且第 $i$ 列涂色方案为 $mask$ 的方案数（$mask$ 是二进制状压，不过本人从转移方法上感觉这题更偏向于线性递推而非状压 `DP`）。为方便写代码，$mask$ 中 $0$ 的位表示涂，$1$ 表示不涂。

初始状态为 $f_{0,0}=1$，答案为 $f_{w_1+w_2+\cdots+w_7,0}$。

核心是考虑 $f_{x-1,i}\to f_{x,j}(0\le i,j<2^h)$ 有多少种方案（中间竖线的涂色方案数）。枚举中间竖线的涂色方案数 $k(0\le k<2^{h-1})$，那么每个正方形必须有一边不涂，即：$i~bitor~j~bitor~k~bitor~2k=2^h-1$。

但是发现 $x-1$ 转移到 $x$ 是 $\Theta(2^{3h})$ 的，而同一高度转移系数相同，可以矩阵快速幂。时间复杂度 $\Theta(2^{3h}\log w)$。

[AC Code](https://codeforces.com/contest/498/submission/250925452)。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

struct mat
{
	int r, c, a[200][200];
	friend mat operator * (const mat &a, const mat &b)
	{
		mat c;memset(c.a,0,sizeof c.a);
		c.r = a.r, c.c = b.c;
		for(int i=0;i<c.r;i++) for(int j=0;j<c.c;j++) for(int k=0;k<a.c;k++)
			(c.a[i][j] += 1ll * a.a[i][k] * b.a[k][j] % mod) %= mod;
		return c;
	}
}a,b;

void init(int n)
{
	int i, j, k;
	b.r = b.c = n;memset(b.a,0,sizeof b.a);
	for(i=0;i<n;i++) for(j=0;j<n;j++) for(k=0;k<n/2;k++)
		b.a[i][j] += ((i | j | k | (k << 1)) == n - 1);
}

mat power(mat a, int b)
{
	mat c;memset(c.a,0,sizeof c.a);
	c.r = c.c = a.r;
	for(int i=0;i<c.r;i++) c.a[i][i] = 1;
	while(b)
	{
		if(b&1) c = c * a;
		b >>= 1;
		a = a * a;
	}
	return c;
}

int main()
{
	int i;
	a.a[0][0] = 1;
	for(i=1;i<=7;i++)
	{
		int x;scanf("%d", &x);
		init(1<<i), a.r = 1, a.c = 1 << i;
		a = a * power(b,x);
	}
	printf("%d", a.a[0][0]);
	return 0;
} 
```

---

## 作者：OtterZ (赞：0)

# 题意
给定 $7$ 台阶，每集有宽度 $w_i$，把台阶放在小方格上，显然边缘，再染内部网格边，有多少种方案不存在一个小正方形四边都被染上。
# 状压 `DP`
这题中，我们发现，一个小正方格对应两个在不同列的竖线和在同一列的横线，考虑从左到右对竖线的状态进行转移，由于竖线占不超过 $7$ 格，考虑状态压缩 `DP`，枚举合法横向边进行转移，此时时间复杂度为 $\operatorname{O}(\sum_{i = 1} ^ {7}((2^i)^3 \times w_i))$。
# 矩阵加速
直接状压 `DP` 显然会 `TLE`，此时我们会发现，同样高度的两条竖线的转移是相同的，故通过矩阵快速幂进行加速，可以优化到 $\operatorname{O}(\sum_{i = 1} ^ {7}((2^i)^3 + sz^3 \log w_i))$，$sz$ 指矩阵大小，在这里是 $128$。

```cpp
#include<cstdio>
#include<cstring>
//矩阵乘法维护状压dp
using namespace std;
int n,w[8];
const int mod = 1e9 + 7;
struct matrix{ 
	int mat[130][130];
}nmat,cmat; 
//矩阵乘积
matrix operator*(const matrix &a,const matrix &b){
	matrix c;
	for(int i = 0; i < 128; i ++){
		for(int j = 0; j < 128; j ++){
			c.mat[i][j] = 0;
			for(int k = 0; k < 128; k ++){
				c.mat[i][j] = (c.mat[i][j] + 1ll * a.mat[i][k] * b.mat[k][j] % mod) % mod;
			}
		}
	}
	return c;
} 
int nbit[128],cntb,las,lbit[128],lcnt;
matrix fst_times(const matrix &a,int b){
	matrix x,ret;
	for(int i = 0; i < 128; i ++){
		for(int j = 0; j < 128; j ++){
			x.mat[i][j] = a.mat[i][j];
			ret.mat[i][j] = (i == j);
		}
	}
	int u = 1;
	while(b){
		if(b & 1){
			ret = ret * x;
		}
		b = (b >> 1);
		x = x * x;
	}
	return ret;
}
int rk,rl;
char rc(){
	static const int RL = 7;
	static char buf[RL],*p1 = buf,*p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,RL,stdin),p1 == p2) ? EOF : *p1 ++;
}
int ri(){
	int f = 0;
	char c = ' ';
	while(c < '0' || c > '9')
		c = rc();
	while(c >= '0' && c <= '9')
		f = f * 10 + c - '0',c = rc();
	return f;
}
int main(){
	for(int i = 1; i <= 7; i ++){
		w[i] = ri();
		if(w[i] == 0)//没有这一层则跳过 
			continue;
		if(las == 0){//第一层次
			nmat.mat[0][(1 << i) - 1] = 1;
			goto skp;//跳过过渡段 
		}
		memset(cmat.mat,0,sizeof(cmat.mat));
		for(int j = 0; j < (1 << las); j ++){//过渡递推 
			for(int k = 0; k < (1 << las); k ++){
				rk = (((1 << i) - 1) ^ k);
				for(int l = 0; l < (1 << las - 1); l ++){
					rl = (((1 << las - 1) | l) << 1) | 1;
					if((j & rk & rl & (rl >> 1)) == 0){ //合法 
						cmat.mat[j][rk] ++;//dp[rk] = dp[j] * mat[j][rk];
					}
				}
			}
		}
		nmat = nmat * cmat;
		skp:
      //同层递推 
		memset(cmat.mat,0,sizeof(cmat.mat));
		for(int j = 0; j < (1 << i); j ++){ 
			for(int k = 0; k < (1 << i); k ++){
				for(int l = 0; l < (1 << i - 1); l ++){
					rl = (((1 << i - 1) | l) << 1) | 1;
					if((j & k & rl & (rl >> 1)) == 0){//合法 
					//printf("%d %d %d\n",j,k,rl);
						cmat.mat[j][k] ++;//dp[rk] = dp[j] * mat[j][k];
					}
				}
			}
		}
		nmat = nmat * fst_times(cmat,w[i] - 1);
		las = i;
		/*
		for(int mi = 0; mi < 128; mi ++){
			for(int mj = 0; mj < 128; mj ++){
				printf("%d ",nmat.mat[mi][mj]);
			}
			puts("");
		}
		puts("");
		*/
	}
	nmat = nmat * cmat;//最后一列
	/*
	for(int i = 0; i < 128; i ++){
		for(int j = 0; j < 128; j ++){
			printf("%d ",nmat.mat[i][j]);
		}
		puts("");
	}
	*/
	printf("%d\n",nmat.mat[0][(1 << las) - 1]); 
	return 0;
}
```
# 进一步优化
如上的算法理论上可以过，但实际上会被卡常，相比于普通的缩小常数的做法，如下优化更为有效。

“我是 `otter`，”  
“乌鸦开矩阵！”

我们可以发现，事实上对于高度为 $i$ 的阶梯只会转移 $2^i$ 种状态，且状态数单调递增（事实上没那么必要说），故而我们可以动态的加大矩阵大小，扩大的位置补 $0$ 即可，此时算法优化至 $\operatorname{O}(\sum_{i = 1} ^ {7}((2^i)^3 \times \log w_i))$。

```cpp
#include<cstdio>
#include<cstring>
//矩阵乘法维护状压dp 
//大小单调递增 
using namespace std;
int n,w[8];
const int mod = 1e9 + 7;
struct matrix{//矩阵 
	int mat[130][130];
	int sz;
}nmat,cmat; 
//矩阵乘积
matrix operator*(const matrix &a,const matrix &b){
	matrix c;
	for(int i = 0; i < a.sz; i ++){
		for(int j = 0; j < a.sz; j ++){
			c.mat[i][j] = 0;
			for(int k = 0; k < a.sz; k ++){
				c.mat[i][j] = (c.mat[i][j] + 1ll * a.mat[i][k] * b.mat[k][j] % mod) % mod;
			}
		}
	}
	c.sz = a.sz;
	return c;
} 
int nbit[128],cntb,las,lbit[128],lcnt;
matrix fst_times(const matrix &a,int b){
	matrix x,ret;
	for(int i = 0; i < a.sz; i ++){
		for(int j = 0; j < a.sz; j ++){
			x.mat[i][j] = a.mat[i][j];
			ret.mat[i][j] = (i == j);
		}
	}
	x.sz = ret.sz = a.sz;
	int u = 1;
	while(b){
		if(b & 1){
			ret = ret * x;
		}
		b = (b >> 1);
		x = x * x;
	}
	return ret;
}
int rk,rl;
//快读
char rc(){
	static const int RL = 7;
	static char buf[RL],*p1 = buf,*p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,RL,stdin),p1 == p2) ? EOF : *p1 ++;
}
int ri(){
	int f = 0;
	char c = ' ';
	while(c < '0' || c > '9')
		c = rc();
	while(c >= '0' && c <= '9')
		f = f * 10 + c - '0',c = rc();
	return f;
}
int main(){
	nmat.sz = cmat.sz = 1;
	for(int i = 1; i <= 7; i ++){
		w[i] = ri();
		//printf("%d\n",w[i]);
		if(w[i] == 0)//没有这一层则跳过 
			continue;
		nmat.sz = (1 << i),cmat.sz = (1 << i);
		if(las == 0){//第一层次
			nmat.mat[0][(1 << i) - 1] = 1;
			goto skp;//跳过过渡段 
		}
		memset(cmat.mat,0,sizeof(cmat.mat));
		for(int j = 0; j < (1 << las); j ++){//过渡递推 
			for(int k = 0; k < (1 << las); k ++){
				rk = (((1 << i) - 1) ^ k);
				for(int l = 0; l < (1 << las - 1); l ++){
					rl = (((1 << las - 1) | l) << 1) | 1;
					if((j & rk & rl & (rl >> 1)) == 0){//合法 
						cmat.mat[j][rk] ++;//dp[rk] = dp[j] * mat[j][rk];
					}
				}
			}
		}
		nmat = nmat * cmat;
		skp:
		memset(cmat.mat,0,sizeof(cmat.mat));
		for(int j = 0; j < (1 << i); j ++){//递推 
			for(int k = 0; k < (1 << i); k ++){
				for(int l = 0; l < (1 << i - 1); l ++){
					rl = (((1 << i - 1) | l) << 1) | 1;
					if((j & k & rl & (rl >> 1)) == 0){//合法 
					//printf("%d %d %d\n",j,k,rl);
						cmat.mat[j][k] ++;//dp[rk] = dp[j] * mat[j][k];
					}
				}
			}
		}
		nmat = nmat * fst_times(cmat,w[i] - 1);
		las = i;
		/*
		for(int mi = 0; mi < 128; mi ++){
			for(int mj = 0; mj < 128; mj ++){
				printf("%d ",nmat.mat[mi][mj]);
			}
			puts("");
		}
		puts("");
		*/
	}
	nmat = nmat * cmat;//最后一列
	/*
	for(int i = 0; i < 128; i ++){
		for(int j = 0; j < 128; j ++){
			printf("%d ",nmat.mat[i][j]);
		}
		puts("");
	}
	*/
	printf("%d\n",nmat.mat[0][(1 << las) - 1]); 
	return 0;
}
```
[“`otter` 击败了 `CF498E`。”](https://codeforces.com/contest/498/submission/234224665)

---

## 作者：_edge_ (赞：0)

考虑容斥，相当于数一种方案里面所有的四条边都黑的正方形，乘上组合系数加起来即为答案。

由于高度不超过 $7$，所以可以考虑直接轮廓线 dp。

[code](https://codeforces.com/contest/498/submission/227072012)

---

