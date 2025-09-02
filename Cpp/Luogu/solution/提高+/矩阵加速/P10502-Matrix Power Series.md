# Matrix Power Series

## 题目描述

给定一个 $n×n$ 矩阵 $A$ 和一个正整数 $k$，找出和 $S=A+A^2 +A^3 +...+A^k$。

## 样例 #1

### 输入

```
2 2 4 
0 1 
1 1```

### 输出

```
1 2
2 3```

# 题解

## 作者：vicissitudes (赞：10)

# Matrix Power Series 矩阵幂求和
~~写不来分治，只好慢慢推公式。~~

**引理**：两个矩阵相乘能分解为若干个矩阵相乘（如果能的话）。

即：
$$\left[
\begin{matrix}
	A B
	\end{matrix}
	\right]\times
\left[
\begin{matrix}
	CD\\
	EF
	\end{matrix}
	\right]=
	\left[
\begin{matrix}
	A\times C + B\times E  & A\times D+B\times F
	\end{matrix}
	\right]
$$，

其中 $ABCDEF$ 均为大小相等的**矩阵**。

~~可以手算。~~

## 本题思路
令 $F_n = [A_n,S_n]$ ，其中 $A_n$ 与 $S_n$ 均为题目含义。
$B$ 为 $2n\times2n$ 的矩阵。

列得： 
$$[A_n,S_n]\times B=[A_{n + 1}, S_{n + 1}]$$，

已知：
$$A_{n+1} = A_n \times A$$，

$$S_{n+1} = S_n + A_{n+1}$$，

推导可得：
$$B =\left[
\begin{matrix}
	A&A\\
	0&E
	\end{matrix}
	\right]
$$。

其中 $A$ 为题目所给，
$E$ 为单位矩阵。

即：
$$F_{n} = F_1\times B^{k-1}$$。

**快速幂**计算即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 80;
long long n, k, m;
long long a[N][N], b[N][N];
void mul1(long long c[][N], long long a[][N], long long b[][N]) {
	long long temp[N][N] = {0};
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= 2 * n; j ++) {
			for(int k = 1; k <= 2 * n; k ++) {
				temp[i][k] = (temp[i][k] + a[i][j] * b[j][k] % m) % m;
			}
		}
	}	
	memcpy(c, temp, sizeof temp);
}//n * 2n的矩阵与2n * 2n的矩阵相乘

void mul2(long long c[][N], long long a[][N], long long b[][N]) {
	long long temp[N][N] = {0};
	for(int i = 1; i <= 2 * n; i ++) {
		for(int j = 1; j <= 2 * n; j ++) {
			for(int k = 1; k <= 2 * n; k ++) {
				temp[i][k] = (temp[i][k] + a[i][j] * b[j][k] % m) % m;
			}
		}
	}	
	memcpy(c, temp, sizeof temp);
}//2n * 2n的矩阵与2n * 2n的矩阵相乘

int main() {
	cin >> n >> k >> m;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++) {
			cin >> a[i][j];
			a[i][j + n] = a[i][j];//F1 = [A A]
			b[i][j] = b[i][j + n] = a[i][j]; 
			b[i + n][i + n] = 1;//B = [A A
		}                            //0 E]
	}
	k --;
	while(k) {
		if (k & 1) mul1(a, a, b);
		k /= 2;
		mul2(b, b, b);
	}//矩阵快速幂
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++) {
			cout << (a[i][j + n] + m) % m << " ";//输出Fn的Sn
		}
		puts("");
	}
	return 0; 
}
```

---

## 作者：yinbe (赞：4)

## 题目描述

给定一个 $n×n$ 矩阵 $A$ 和一个正整数 $k$，求 $A+A^2 +A^3 +...+A^k$，对 $m$ 取模。

### 数据范围

- $n\le 30$
- $k\le 10^9$

## 思路

### 暴力思路

首先想暴力，类似[求阶乘和](https://www.luogu.com.cn/problem/P1009)的方式，边乘边加，时间复杂度是 $O(kn^3)$，可以获得[ $25$ 分的好成绩](https://www.luogu.com.cn/record/204050324)。

### 暴力代码

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int n,a[35][35],ans[35][35],k,mod;
void jia(int a[35][35],int b[35][35])
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]+=b[i][j];
			a[i][j]%=mod;
		}
	}
}
void mul(int a[35][35],int b[35][35])
{
	int c[35][35];
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
				c[i][j]%=mod;
			}	
		}
	}
	memcpy(a,c,sizeof(c));
}
void slow_add(int ans[35][35],int k)
{
	int ai[35][35];
	memset(ai,0,sizeof(ai));
	for(int i=1;i<=n;i++)
		ai[i][i]=1;
	for(int i=1;i<=k;i++)
	{
		mul(ai,a);
		jia(ans,ai);
	}
}
signed main()
{
	scanf("%lld%lld%lld",&n,&k,&mod);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a[i][j]);
			a[i][j]%=mod;
		}
	}
	slow_add(ans,k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%lld ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
```

### 正解思路

假设 $sum(k)=A+A^2 +A^3 +\ldots+A^k$，$m= \left \lfloor   k\div 2\right \rfloor$。

#### 当 $k$ 为偶数

$$ \begin{aligned} sum(k)&=A+A^2 +A^3 +\ldots+A^k \\ & =(A+A^2 +A^3+\ldots +A^m)+(A^{m+1}+A^{m+2} +A^{m+3}+\ldots +A^k )\\&=(A+A^2 +A^3+\ldots +A^m)+A^m\times(A+A^2 +A^3+\ldots +A^{k\div 2})\\&=(A+A^2 +A^3+\ldots +A^m)+A^m\times(A+A^2 +A^3+\ldots +A^{m})\\&=sum(m)+A^m\times sum(m) \end{aligned}$$

#### 当 $k$ 为奇数

$$ \begin{aligned} sum(k)&=A+A^2 +A^3 +\ldots+A^k \\ & =(A+A^2 +A^3+\ldots +A^m)+(A^{m+1}+A^{m+2} +A^{m+3}+\ldots +A^{m\times 2} )+A^k\\&=(A+A^2 +A^3+\ldots +A^m)+A^m\times(A+A^2 +A^3+\ldots +A^{m})+A^k\\&=sum(m)+A^m\times sum(m)+A^k \end{aligned}$$

我们只需要计算 $sum(m)$ 就可以计算出 $sum(k)$，每次可以缩小问题规模的一半，我们只需递归 $\log k$ 次就可以求出答案，总时间复杂度 $O(n^3\log^2 k)$。

### 正解代码

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
int n,a[35][35],ans[35][35],k,mod;
void jia(int a[35][35],int b[35][35])
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]+=b[i][j];
			a[i][j]%=mod;
		}
	}
}
void mul(int a[35][35],int b[35][35])
{
	int c[35][35];
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
				c[i][j]%=mod;
			}	
		}
	}
	memcpy(a,c,sizeof(c));
}
void quick_pow(int a[35][35],int b[35][35],int k)
{
	int yuan[35][35];
	memcpy(yuan,b,sizeof(yuan));
	while(k)
	{
		if(k&1)
			mul(a,b);
		mul(b,b);
		k>>=1;
	}
	memcpy(b,yuan,sizeof(yuan));
}
void quick_add(int ai[35][35],int k)
{
	if(k==1)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				ai[i][j]=a[i][j];
		}
		return;
	}
	if(k&1)
	{
		int b[35][35],ak[35][35],an[35][35];
		memset(b,0,sizeof(b));
		memset(ak,0,sizeof(ak));
		memset(an,0,sizeof(an));
		for(int i=1;i<=n;i++)
		{
			ak[i][i]=1;	
			an[i][i]=1;
		}
		quick_add(b,k/2);
		quick_pow(ak,a,k/2);
		quick_pow(an,a,k);
		jia(ai,b);
		mul(ak,b);
		jia(ai,ak);
		jia(ai,an);
	}
	else
	{
		int b[35][35],ak[35][35];
		memset(b,0,sizeof(b));
		memset(ak,0,sizeof(ak));
		for(int i=1;i<=n;i++)
			ak[i][i]=1;	
		quick_add(b,k/2);
		quick_pow(ak,a,k/2);
		jia(ai,b);
		mul(ak,b);
		jia(ai,ak);
	}
}
signed main()
{
	scanf("%lld%lld%lld",&n,&k,&mod);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a[i][j]);
			a[i][j]%=mod;
		}
	}
	quick_add(ans,k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%lld ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：OneLeft (赞：4)

## 题意
给定一个长宽均为 $n(n\le 30)$ 的矩阵 $A$，两个整数 $k(k\le 10^9)$ 和 $m(m\le 10^4)$，求

$$S=\sum_{i=1}^kA^i$$

需要对 $m$ 取模。

## 解法
不难发现 $k$ 非常大，但是给定的 $n$，考虑矩阵快速幂。但是题目要求我们求矩阵的和，所以不能简单的使用矩阵快速幂，需要在矩阵中嵌套矩阵，然后再快速幂。

这里默认 $E$ 为单位矩阵，$O$ 为空矩阵。

设

$$
ANS_{i}=\sum_{j=1}^iA^j\\
[ANS_i,A^i]=[ANS_{i-1},A^{i-1}]\times BASE\\
ANS_0=O,A^0=E\\
BASE=\begin{bmatrix}
M_{11}&M_{12}\\
M_{21}&M_{22}
\end{bmatrix}
$$

则有

$$
ANS_i=M_{11}\times ANS_{i-1}+M_{21}\times A^{i-1}\\
A^i=M_{12}\times ANS_{i-1}+M_{22}\times A^{i-1}
$$

又因为

$$
ANS_i=ANS_{i-1}+A^{i-1}\times A\\
A^i=A^{i-1}\times A
$$

所以

$$M_{11}=E,M_{12}=O,M_{21}=A,M_{22}=A$$

即

$$
BASE=\begin{bmatrix}
E&O\\
A&A
\end{bmatrix}
$$

然后进行矩阵快速幂即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=35;
struct matrix
{
	int m[N][N];
	matrix()
	{
		for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			m[i][j]=0;
	}
	matrix(bool flag)
	{
		if(!flag)return;
		for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			m[i][j]=0;
		for(int i=1;i<N;i++)
			m[i][i]=1;
	}
	friend matrix operator+(matrix x,matrix y);
	friend matrix operator*(matrix x,matrix y);
	friend matrix operator%(matrix x,int mod);
	matrix operator+=(matrix x)
	{
		return (*this)=(*this)+x;
	}
	matrix operator*=(matrix x)
	{
		return (*this)=(*this)*x;
	}
	matrix operator%=(int mod)
	{
		return (*this)=(*this)%mod;
	}
}A,O,E(true);
struct two_matrix
{
	matrix m[5][5];
	two_matrix()
	{
		for(int i=1;i<5;i++)
		for(int j=1;j<5;j++)
			m[i][j]=O;
	}
	two_matrix(bool flag)
	{
		for(int i=1;i<5;i++)
		for(int j=1;j<5;j++)
			m[i][j]=O;
		if(!flag)return;
		for(int i=1;i<5;i++)
			m[i][i]=E;
	}
	friend two_matrix operator*(two_matrix x,two_matrix y);
	friend two_matrix operator^(two_matrix x,int y);
	two_matrix operator*=(two_matrix x)
	{
		return (*this)=(*this)*x;
	}
	two_matrix operator^=(int x)
	{
		return (*this)=(*this)^x;
	}
}ans,base;
int n,k,m;
matrix operator+(matrix x,matrix y)
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		x.m[i][j]=(x.m[i][j]+y.m[i][j])%m;
	return x;
}
matrix operator*(matrix x,matrix y)
{
	matrix res;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	for(int k=1;k<=n;k++)
		res.m[i][j]+=x.m[i][k]*y.m[k][j];
	return res;
}
matrix operator%(matrix x,int mod)
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		x.m[i][j]=x.m[i][j]%mod;
	return x;
}
two_matrix operator*(two_matrix x,two_matrix y)
{
	two_matrix res;
	for(int i=1;i<=2;i++)
	for(int j=1;j<=2;j++)
	for(int k=1;k<=2;k++)
		res.m[i][j]=(res.m[i][j]+x.m[i][k]*y.m[k][j])%m;
	return res;
}
two_matrix operator^(two_matrix x,int y)
{
	two_matrix ans(true),base=x;
	for(;y>0;y/=2)
	{
		if(y%2==1)ans*=base;
		base*=base;
	}
	return ans;
}
signed main()
{
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		cin>>A.m[i][j];
	ans.m[1][2]=base.m[1][1]=E;
	base.m[2][1]=base.m[2][2]=A;
	ans*=base^k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<ans.m[1][1].m[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：2)

Upd on 2024.6.2：修改了错误的复杂度。

## 分析

很久前在 POJ 做的好题，但是反复神秘 RE。在洛谷过了。

原式是 $A+A^2+\cdots+A^k$，可以考虑到如果 $k$ 是偶数，把式子拆成两段，也就是 $(A+A^2+\cdots+A^{\frac{k}{2}})+(A^{\frac{k}{2}+1}+A^{\frac{k}{2}+2}+\cdots+A^k)$；如果是奇数，把 $A^k$ 单独算，其它变成 $k$ 是偶数的情况。

对于被拆成两段的式子，注意到右边提出 $A^{\frac{k}{2}}$ 就可以变成左段，那么递归一下可以解决本题（当然是有必不可少的矩阵快速幂），复杂度约为 $O(n^3\times (\log k)^2)$，完全过得去。

## AC Code
```cpp
#include <iostream>
using namespace std;
long long n,k,mod;
struct matrix
{
	long long g[101][101],sz;
};
matrix unit()
{
	matrix ret;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		if(i==j) ret.g[i][j]=1;
		else ret.g[i][j]=0;
	} 
	return ret;
}
matrix emp()
{
	matrix ret;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	ret.g[i][j]=0;
	return ret;
}
matrix times(matrix a,matrix b)
{
	matrix ans;
	ans=emp();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	for(int l=1;l<=n;l++)
	ans.g[i][j]=(ans.g[i][j]+a.g[i][l]*b.g[l][j]%mod)%mod;
	return ans;
}
matrix sum(matrix a,matrix b)
{
	matrix ans;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	ans.g[i][j]=(a.g[i][j]+b.g[i][j])%mod;
	return ans;
}
matrix mqpow(matrix b,long long p)
{
	if(p==1) return b;
	matrix ret;
	ret=unit();
	while(p)
	{
		if(p&1) ret=times(ret,b);
		b=times(b,b);
		p>>=1ll;
	}
	return ret;
}
matrix sum2(matrix a,long long k)
{
	matrix ret;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		ret.g[i][j]=k+a.g[i][j];
		ret.g[i][j]%=mod;
	}
	return ret;
}
matrix solve(matrix a,long long k)
{
	if(k==1ll) return a;
	long long mid=k>>1ll;
	matrix ans;
	ans=times(solve(a,mid),sum(mqpow(a,mid),unit()));
	if(k%2) ans=sum(ans,mqpow(a,k));
	return ans;
}
int main()
{
	cin>>n>>k>>mod;
	matrix a;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)    
	cin>>a.g[i][j];
	matrix ans;
	ans=solve(a,k);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		cout<<ans.g[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}

---

## 作者：GY程袁浩 (赞：2)

### 解法

提供一种较新颖的做法，首先由题会先想到一个经典的问题，求斐波那契数列的第 $n$ 项前缀和，即 $\sum_{i=1}^{n}f_{i}$。这道题的解法即为维护总和与目前的 $f_{i}$，构造出转移矩阵后矩阵快速幂解决即可。

考虑 $A_{i}$ 表示 $A^i$，那么此题就是求 $\sum_{i=1}^{n}A_{i}$，与上段介绍的问题极其相似，于是考虑上问的类似解法。

但是我们想知道的答案是一个矩阵怎么办呢？创新点！由于矩阵加满足交换律，并且满足分配律，所以就可以推出矩阵套矩阵满足结合律，那我们就可以矩阵套矩阵快速幂。

维护由矩阵构成的答案，然后设计一个由矩阵构成的状态转移矩阵！

状态矩阵套矩阵为：

$$
\huge
\begin{bmatrix}
S
&
A_{i}
\end{bmatrix}
$$

其中，$S$ 表示目前的前缀和，$A_{i}$ 表示 $A^{i}$。

设全零矩阵为 $E$，单位矩阵为 $R$，$A$ 表示给定矩阵，那么显然转移矩阵如下：

$$
\huge
\begin{bmatrix}
R & E\\
A & A\\
\end{bmatrix}
$$

矩阵快速幂转移即可，时间复杂度 $O(S^3n^3 \log k)$，其中 $S$ 为转移矩阵套矩阵行数与列数，在刚才的推导中 $S=2$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=35;
struct matrix {
	int n,m,a[N][N];
	matrix(){memset(a,0,sizeof a);}
}E,R,A;
struct Smatrix {
	int n,m;
	matrix a[4][4];
};
int p;
matrix operator*(matrix a,matrix b) {
	if(a.n>b.n) swap(a,b);
	matrix c;c.n=a.n,c.m=a.m;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=a.m;j++)
			for(int k=1;k<=a.m;k++)
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%p)%p;
	return c;
}
matrix operator+(matrix a,matrix b) {
	matrix c;c.n=max(a.n,b.n),c.m=max(a.m,b.m);
	for(int i=1;i<=max(a.n,b.n);i++)
		for(int j=1;j<=max(a.m,b.m);j++)
			c.a[i][j]=(a.a[i][j]+b.a[i][j])%p;
	return c;
}
Smatrix operator*(Smatrix a,Smatrix b) {
	if(a.n>b.n) swap(a,b);
	Smatrix c;c.n=a.n,c.m=a.m;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=a.m;j++)
			c.a[i][j].n=a.a[i][j].n,c.a[i][j].m=a.a[i][j].m;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=a.m;j++)
			for(int k=1;k<=a.m;k++)
				c.a[i][j]=c.a[i][j]+a.a[i][k]*b.a[k][j];
	return c;
}
Smatrix qmi(Smatrix a,int b) {
	b--;
	Smatrix res;res.n=a.n,res.m=a.m;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=a.m;j++) res.a[i][j]=a.a[i][j];
	while(b) {
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
int n,k;
signed main() {
	cin>>n>>k>>p;
	A.n=n,A.m=n;R.n=R.m=n;E.n=E.m=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>A.a[i][j],R.a[i][j]=(i==j);
	Smatrix O,G;
	O.n=1,O.m=2,G.n=2,G.m=2;
	O.a[1][1]=A,O.a[1][2]=A;
	G.a[1][1]=R,G.a[2][1]=A;
	G.a[1][2]=E,G.a[2][2]=A;
	if(k-1>0) {
		G=qmi(G,k-1);
		O=O*G;
	}
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)
			cout<<O.a[1][1].a[i][j]<<' ';
	return 0;
}
```

---

## 作者：cjh20090318 (赞：2)

不是很难的矩阵快速幂，~~老师说用等比数列公式求逆矩阵做，然而这题模数并不是质数。~~

## 题意

给定一个 $n×n$ 矩阵 $A$ 和一个正整数 $k$，求 $S=\sum\limits_{i=1}^k A^i$。

## 分析

模数不为质数就不要想等比数列求和公式求逆矩阵做了，考虑一个比较朴素的实现。

直接求肯定会超时，又因矩阵乘法存在分配律，所以考虑分治。

### 当 $k$ 为奇数时

设 $x=\dfrac {k+1} 2 $，则可以推出：
$$
\sum\limits_{i=1}^k A^i = \left(\sum\limits_{i=1}^{x-1} A^i\right) + A^x + A^x \sum\limits_{i=1}^{x-1} A^i
$$

### 当 $k$ 为偶数时

设 $x=\dfrac k 2$，则可以推出：
$$
\sum\limits_{i=1}^k A^i = \left(\sum\limits_{i=1}^{x} A^i\right) + A^x \sum\limits_{i=1}^{x} A^i
$$
这个可以通过分治求解，时间复杂度 $T(k) = T(\dfrac k 2) + O(n^3 \log k)$，所以总体时间复杂度为 $O(n^3 \log^2 k)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;
int n,k,mod;
template<typename T>
struct Mat{
    int n,m;
    T **a;
    Mat(int _n=0,int _m=0):n(_n),m(_m){
        a=new T*[n];
        for(int i=0;i<n;i++) a[i]=new T[m],memset(a[i],0,sizeof(T)*m);
    }
    Mat(const Mat&B){
        n=B.n,m=B.m;
        a=new T*[n];
        for(int i=0;i<n;i++) a[i]=new T[m],memcpy(a[i],B.a[i],sizeof(T)*m);
    }
    ~Mat(){delete[] a;}
    Mat&operator = (const Mat&B){
        delete[] a;
        n=B.n,m=B.m;
        a=new T*[n];
        for(int i=0;i<n;i++) a[i]=new T[m],memcpy(a[i],B.a[i],sizeof(T)*m);
        return *this;
    }
    Mat operator + (const Mat&B)const{//矩阵加法。
    	assert(n==B.n&&m==B.m);
    	Mat ret(n,m);
    	for(int i=0;i<n;i++)for(int j=0;j<m;j++) ret.a[i][j]=(a[i][j]+B.a[i][j])%mod;
    	return ret;
	}
	Mat&operator += (const Mat&B){return *this=*this+B;}
    Mat operator * (const Mat&B)const{//矩阵乘法。
        Mat ret(n,B.m);
        for(int i=0;i<n;++i)for(int j=0;j<B.m;ret.a[i][j++]%=mod)for(int k=0;k<m;++k)ret.a[i][j]+=a[i][k]*B.a[k][j]%mod;
        return ret;
    }
    Mat&operator *= (const Mat&B){return *this=*this*B;}
};
Mat<int> qpow(Mat<int> A,int b){//矩阵快速幂。
	Mat<int> ret(A);
	for(--b;b;b>>=1,A*=A)if(b&1)ret*=A;
	return ret;
}
Mat<int>dfs(const Mat<int>&A,const int x){//递归求解。
	if(x==1) return A;
	Mat<int> ret(dfs(A,x>>1));
	if(x&1) ret+=qpow(A,(x+1)>>1)+qpow(A,(x+1)>>1)*ret;//分类讨论。
	else ret+=qpow(A,x>>1)*ret;
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&k,&mod);
	Mat<int> A(n,n);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++) scanf("%d",&A.a[i][j]),A.a[i][j]%=mod;
	Mat<int> ans(dfs(A,k));
	for(int i=0;i<n;i++,putchar('\n'))for(int j=0;j<n;j++) printf("%d ",ans.a[i][j]);
	return 0;
}

```

---

## 作者：O_v_O (赞：1)

题目算法： #矩阵乘法 #快速幂 
## 题意

给定一个 $n \times n$ 矩阵 $A$ 和一个正整数 $k$，找出和 $S=A+A_2+A_3+\dots+A_k$。

## 思路

这道题是矩阵乘法和矩阵快速幂的的板子题。

### 什么是矩阵？

我们可以将其抽象成一个二维数组。

### 矩阵乘法

设A为 $m \times p$ 的矩阵，$B$ 为 $p \times n$ 的矩阵，那么称 $m \times n$ 的矩阵 $C$ 为矩阵 $A$ 与 $B$ 的乘积，记作 $C = AB$ ，其中矩阵 $C$ 中的第 $i$ 行第 $j$ 列元素可以表示为：

$$
(AB)_{i, j} = \sum_{k = 1}^{p} a_{i,k}b_{k,j} = a_{i, 1}b_{1, j} + a_{i, 2}b_{2, j} + \dots + a_{i, p}b_{p, j}
$$
我们知道以上概念后，我们就可以继续做这道题了。

我们发现 $k$ 有 $10^9$，直接枚举做是不可能的，但矩阵是满足分配率和交换率的，所以我们可以用递推来求。

- **情况1：$k$ 为奇数时**
	 设 $x = \frac{k + 1}{2}$，即可推出：
	 $$
	  \sum_{i = 1}^{k}A^i = (\sum^{x - 1}_{i = 1}A^i) + A^x + A^x \sum_{i = 1}^{x - 1}A^i
	  $$
- **情况2：$k$ 为偶数时**
     设 $x = \frac{k}{2}$，即可推出：
     $$
      \sum_{i = 1}^{k}A^i = (\sum_{i = 1}^{x}A^i) + A^x\sum_{i = 1}^{x}A^i
      $$
这道题就结束了
## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, mod;

struct Matrix {
  int data[50][50];
  void init() {
    memset(data, 0, sizeof data);
  }
  friend Matrix operator + (Matrix a, Matrix b) {
    Matrix ans;
    ans.init();
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) 
        ans.data[i][j] = (a.data[i][j] + b.data[i][j]) % mod;
    return ans;
  }
  friend Matrix operator * (Matrix a, Matrix b) {
    Matrix ans;
    ans.init();
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        for (int k = 1; k <= n; k++)
          ans.data[i][j] = (ans.data[i][j] + 1ll * a.data[i][k] * b.data[k][j]) % mod;
    return ans;
  }
} a;

Matrix quick_pow(Matrix a, int k) {
  Matrix ans;
  ans.init();
  for (int i = 1; i <= n; i++)
    ans.data[i][i] = 1;
  while (k) {
    if (k & 1) ans = ans * a;
    k >>= 1;
    a = a * a;
  }
  return ans;
}

Matrix sum(Matrix a, int k) {
  if (k == 1) return a;
  Matrix c;
  c.init();
  for (int i = 1; i <= n; i++)
    c.data[i][i] = 1;
  c = (c + quick_pow(a, k >> 1)) * sum(a, k >> 1);
  if (k & 1) 
    c = c + quick_pow(a, k);
  return c;
}

int main() {
  cin >> n >> k >> mod;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> a.data[i][j];
  a = sum(a, k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << a.data[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：_zuoqingyuan (赞：1)

# 题意简述

给定矩阵 $A$，常数 $k$，求出

$$S_{k}=\sum_{i=1}^kA^i$$

的值，答案对 $y$ 取模，其中 $k\le 10^9$。

# 思路分析

很好的题目。

首先思考常规等比数列求和的方法，即 

$$S_{k}=\sum_{i=1}^k{A^i}=\frac{A^{k+1}-1}{A-1}$$

但当数变为矩阵时，就十分难处理了，矩阵求逆的难度本身比较大，还不一定拥有逆矩阵。

我们不得不采用另一种方法：分治法。

将等比数列按中位数分成两部分，我们发现后一部分其实就是前一部分乘上了某个矩阵的幂。我们可以将其分解为小问题，一层层递归。

接下来讲讲具体做法：

### 对于 $k$ 为偶数

令 $x=\frac{k}{2}$，显然：

$$\begin{aligned}S_k&=\sum_{i=1}^k{A^i}\\
&=\sum_{i=1}^xA^i+A^x\sum_{i=1}^xA^i\\
&=S_{x}+A^xS_{x}
\end{aligned}$$

### 对于 $k$ 为奇数

令 $x=\frac{k-1}{2}$，显然：

$$\begin{aligned}S_k&=\sum_{i=1}^k{A^i}\\
&=\sum_{i=1}^xA^i+A^x\sum_{i=1}^xA^i+A^{k}\\
&=S_{x}+A^xS_{x}+A^{k}
\end{aligned}$$

每一次计算 $S_k$ 都只需计算 $S_{\frac{k}{2}}$ 的值，每一轮的问题都会缩小一半，所以递归树的深度为 $\log k$。

每一轮递归还需计算矩阵的幂，对于大小为 $n$ 的矩阵 $A$，计算 $A^{m}$，借助快速幂可以在 $n^3\log m$ 的时间复杂度解决。

总时间复杂度为 $O(n^3\log^2k)$，可以通过本题。

# Code：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,k,mod;
struct mat{
	int n,s[35][35];
	mat(int m){
		n=m;
		memset(s,0,sizeof(s));
	}//初始化
	mat operator * (const mat &b)const{
		mat c(n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					c.s[i][j]=(c.s[i][j]+s[i][k]*b.s[k][j])%mod;	
				}
			}
		}
		return c;
	} //重载乘运算
	mat operator + (const mat &b)const{
		mat c(n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				c.s[i][j]=(s[i][j]+b.s[i][j])%mod;
			}
		}
		return c;
	}//重载加运算
	void print(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<s[i][j]<<" ";
			}
			cout<<endl;
		}
	}//输出矩阵
	void init(){
		for(int i=1;i<=n;i++)s[i][i]=1;
	}//初始化后变为单位矩阵
};
mat ksm(mat a,int b){
	mat ans(n);
	ans.init();
	while(b){
		if(b&1)ans=(ans*a);
		a=(a*a);
		b>>=1;
	}
	return ans;
}//矩阵快速幂
mat solve(mat a,int k){
	if(k==1)return a;
	if(k&1){
		k=k/2;
		mat b=solve(a,k);
		return (b+(ksm(a,k)*b)+ksm(a,2*k+1));
	}else{
		k=k/2;
		mat b=solve(a,k);
		return (b+(ksm(a,k)*b));
	}
}//递归函数
int tot;
int main(){
	cin>>n>>k>>mod;
	mat a(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a.s[i][j];
		}
	}
	solve(a,k).print();
	return 0;
}
```

如有错误，请指出。

---

## 作者：tder (赞：1)

You can view the [English version](https://www.luogu.com/article/gp9mnj6w/) of this solution.

考虑分治。

根据矩阵乘法分配律，若我们已经算出了 $A+A^2+\cdots+A^p$，便可以将其乘上 $A^{q}$，从而在 $\mathcal{O}(n^3\log k)$ 的复杂度内，得到 $A^{q+1}+A^{q+2}+\cdots+A^{q+p}$。

这启示我们参考分块思想，将所求和式分为若干个长度相等的区间，以及一些散块。整块递归计算下一层答案并乘上系数即可，散块暴力计算。

令分了 $x$ 块，分治计算 $\mathcal{O}(\log_x k)$ 层，计算每层的复杂度为 $\mathcal{O}(x\cdot n^3\log k)$，总复杂度 $\mathcal{O}(x\log_x k\cdot n^3\log k)$。

取 $k=10^{18}$，考察函数 $f(x)=x\log_x k$，当 $x$ 约为 $2.7$ 时取最小值，故取 $x=3$ 最优。复杂度 $\mathcal{O}(\log_3 k\cdot n^3\log k)$，有三倍常数。应该是理论最优解。

---

```cpp
Martix solve(int r) {
	if(r == 1) return a;
	if(r == 2) return a + a * a;
	auto p = solve(r / 3);
	if(r % 3 == 1) return p + pow(a, r / 3) * p + pow(a, r / 3 * 2) * p + pow(a, r);
	else if(r % 3 == 2) return p + pow(a, r / 3) * p + pow(a, r / 3 * 2) * p + pow(a, r) + pow(a, r - 1);
	else return p + pow(a, r / 3) * p + pow(a, r / 3 * 2) * p;
}
```

---

## 作者：lyh227 (赞：1)

## 题意
给定一个 $n \times n$ 的矩阵 $A$ 和整数 $k$ 求：
$$
\sum_{i=1}^{k}A^i
$$
矩阵中每个数都对 $m$ 取模。
## 思路
### 递推
显然可以用递推，式子很简单，$f_k$ 即为最终的答案。
$$
f_i=f_{i-1}+A^i
$$
但 $k\le10^9$，怎么办呢？

可以考虑矩阵优化。
### 优化
**以下 $I$ 代表单位矩阵，$Z$ 代表全 $0$ 矩阵。**

由于转移的内容为矩阵，所以需要用矩阵套矩阵，设我们所需求的转移矩阵为 $B$（写在原矩阵前仅为个人习惯，勿喷），即
$$
B \times 
\begin{bmatrix}
f_i\\
A^{i+1}
\end{bmatrix}=
\begin{bmatrix}
f_{i+1}\\
A^{i+2}
\end{bmatrix}
$$
$B$ 矩阵显然为 $2 \times 2$，设它为$\begin{bmatrix}a&b\\c&d\end{bmatrix}$，可得
$$
\begin{bmatrix}
a&b\\
c&d
\end{bmatrix}
\times
\begin{bmatrix}
f_i\\
A^{i+1}
\end{bmatrix}=
\begin{bmatrix}
f_{i+1}\\
A^{i+2}
\end{bmatrix}
$$
$$
af_i+bA^{i+1}=f_{i+1}
\\
cf_i+dA^{i+1}=A^{i+2}
$$
解出 $a=I,b=I,c=Z,d=A$

那么 $B=\begin{bmatrix}I&I\\Z&A\end{bmatrix}$
### 代码
时间复杂度 $O(n^3\log n)$（$n^3$ 为矩阵乘法复杂度）
```cpp
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
long long mod;
long long n,k;
struct matrix //小矩阵
{
	long long mat[40][40];
	long long n,m;
}I,Z,a;
struct matr //大矩阵
{
	matrix mat[40][40];
	long long n,m;
}zy,cs;
matrix operator +(matrix a,matrix b) //小矩阵加法
{
	matrix tmp;
	for(int i=1;i<=a.n;i++)
	{
		for(int j=1;j<=a.m;j++)
		{
			tmp.mat[i][j]=a.mat[i][j]+b.mat[i][j];
			tmp.mat[i][j]%=mod;
		}
	}
	tmp.n=a.n,tmp.m=a.m;
	return tmp;
}
matrix operator *(matrix a,matrix b) //小矩阵乘法
{
	matrix tmp;
	for(int i=1;i<=a.n;i++)
	{
		for(int j=1;j<=b.m;j++)
		{
			tmp.mat[i][j]=0;
			for(int k=1;k<=a.m;k++)
			{
				tmp.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
				tmp.mat[i][j]%=mod;
			}
		}
	}
	tmp.n=a.n,tmp.m=b.m;
	return tmp;
}
matr operator *(matr a,matr b) //大矩阵乘法
{
	matr tmp;
	for(int i=1;i<=a.n;i++)
	{
		for(int j=1;j<=b.m;j++)
		{
            tmp.mat[i][j]=Z;
			for(int k=1;k<=a.m;k++)
			{
				tmp.mat[i][j]=tmp.mat[i][j]+a.mat[i][k]*b.mat[k][j];
			}
		}
	}
	tmp.n=a.n,tmp.m=b.m;
	return tmp;
}
matr ksm(matr a,long long u) //快速幂
{
	matr tmp;
	for(int i=1;i<=a.n;i++)
	{
		for(int j=1;j<=a.n;j++)
		{
			tmp.mat[i][j]=Z;
		}
	}
	for(int i=1;i<=a.n;i++) tmp.mat[i][i]=I;
	tmp.n=a.n,tmp.m=a.m;
	while(u>0){
		if((u&1)==1) tmp=tmp*a;
		a=a*a;
		u>>=1;
	}
	return tmp;
}
void init()
{
	zy.mat[1][1]=I,zy.mat[1][2]=I;  //转移矩阵
	zy.mat[2][1]=Z,zy.mat[2][2]=a;
	zy.n=2,zy.m=2;
	cs.mat[1][1]=a,cs.mat[2][1]=a*a;
	cs.n=2,cs.m=1;
}
int main()
{
	scanf("%lld%lld%lld",&n,&k,&mod);
    Z.n=Z.m=n;
    I.m=I.n=n;
	a.n=a.m=n;
	for(int i=1;i<=n;i++) I.mat[i][i]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a.mat[i][j]);
		}
	}
	init();
	zy=ksm(zy,k-1); //转移
	cs=zy*cs;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%lld",cs.mat[1][1].mat[i][j]);
			if(j!=n) printf(" ");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Seqfrel (赞：1)

# 题解：P10502 Matrix Power Series

update on 2024.6.1：感谢 @[cjh20090318](https://www.luogu.com.cn/user/577880) 提出的一处笔误。

## 题意分析

给定一个 $n \times n$ 的矩阵 $A$ 和正整数 $k$，求 $S=A^1+A^2+\cdots+A^k$。

## 解题思路

求 $A^n$ 要用到[矩阵快速幂](https://www.luogu.com.cn/problem/P3390)。但是 $k \le 10^9$，求 $k$ 个幂会超时，所以需要用到分治的策略。

我们知道，矩阵乘法满足乘法分配律，即 $A \times C + B \times C = (A + B) \times C$。那么我们就可以二分 $k$，$A^{mid+1}$ 加到 $A^r$ 就等于 $A^l$ 加到 $A^{mid}$ 乘 $A^{\frac{r-l+1}{2}}$。当 $(r-l+1)$ 是偶数即 $l$ 到 $r$ 之间的项数为偶数时，求 $A^l$ 加到 $A^{mid}$ 乘 $A^{\frac{r-l+1}{2}}$ 再加 $A^l$ 加到 $A^{mid}$，而求 $A^l$ 加到 $A^{mid}$ 时可以继续二分，直到 $l=r$ 为止。当 $(r-l+1)$ 是奇数时，我们把多出来的一项单独求（这里选择第 $l$ 项），剩下的用二分求。如此一来时间复杂度就会压缩到 $O(\log k)$。

写一个简单的递归即可。

## 代码实现

```cpp
#include<iostream>
#include<cstring>
#define int long long 
using namespace std;
struct Matrix{
	int mx[110][110];
}a,s,c;
int n,m,k;
Matrix operator *(const Matrix &a,const Matrix &b){//运算符重载为矩阵乘法 
	memset(c.mx,0,sizeof(c.mx));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int d=1;d<=n;d++){
				c.mx[i][j]=(c.mx[i][j]+(a.mx[i][d]*b.mx[d][j])%m)%m;
			}
		}
	}
	return c;
}
Matrix operator +(const Matrix &a,const Matrix &b){//运算符重载为矩阵加法 
	memset(c.mx,0,sizeof(c.mx));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			c.mx[i][j]=(a.mx[i][j]+b.mx[i][j])%m;
		}
	}
	return c;
}
Matrix ksm(Matrix a,int k){//快速幂 
	Matrix d,e=a;
	memset(d.mx,0,sizeof(d.mx));
	for(int i=1;i<=n;i++) d.mx[i][i]=1;
	while(k){
		if(k&1) d=d*e;
		e=e*e;
		k>>=1;
	}
	return d;
}
Matrix sum(int l,int r){//二分 
	if(l==r){
		return ksm(a,l);
	}
	if((r-l+1)%2==0){
		int mid=(l+r)/2;
		Matrix x=ksm(a,mid+1-l),y=sum(l,mid);
		return y+y*x;
	}else{
		return sum(l,l)+sum(l+1,r);
	}
}
signed main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++) s.mx[i][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a.mx[i][j];
			a.mx[i][j]%=m;
		}
	}
	s=sum(1,k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cout<<s.mx[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
```

## 注意事项

记得随时取余 $m$。

---

## 作者：AmaoFox (赞：1)

## 题意
+ 给定矩阵 $A$ 和 $k$，求 $A^1+A^2+\dots+A^k$。$k\le10^9$。

## 思路

前置知识：矩阵、矩阵乘法、矩阵快速幂。

如果你还不会如上知识，请点击 [**OI Wiki** 矩阵乘法](https://oi-wiki.org/math/linear-algebra/matrix/#%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95) 进行学习。

由于 $k$ 实在是太大了，一个个加显然不行。矩阵的乘法同样具有分配律，因此

$$(A^x+A^{x+1}+\dots+A^{x+y})\times A^z=A^{x+z}+A^{x+z+1}+\dots+A^{x+y+z}$$

所以我们定义函数 $f(l,r)$ 表示 $A^l+A^{l+1}+\dots+A^r$，则有

$$ f(l,r) =\begin{cases} A^l & l=r \\ f(l,\dfrac{l+r-1}{2})+f(l,\dfrac{l+r-1}{2})\times A^\frac{r-l+1}{2} & 2\mid (r-l+1) \\ A^l+f(l+1,r) & \text{otherwise} \end{cases}$$

其中不难发现重复计算的部分比较多，只要开一些变量记录一下，我们就可以愉快的通过这个题了。

## 代码：
``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 35;

int m;

struct MA {
  int a[N][N], h, w;
  MA() {
    for(int i = 1; i < N; i++) {
      for(int j = 1; j < N; j++) {
        a[i][j] = 0;
      }
    }
    h = 0, w = 0;
  }
  MA(int x, int y) {
    h = x, w = y;
    for(int i = 1; i <= h; i++) {
      for(int j = 1; j <= w; j++) {
        a[i][j] = 0;
      }
    }
  }
  MA(int x, int y, int z) {
    h = y, w = z;
    for(int i = 1; i <= h; i++) {
      for(int j = 1; j <= w; j++) {
        a[i][j] = (i == j) * x;
      }
    }
  }
};

MA operator +(const MA &x, const MA &y) {
  if(x.h != y.h || x.w != y.w) {
    exit(1);
  }
  MA z(x.h, y.w);
  for(int i = 1; i <= x.h; i++) {
    for(int j = 1; j <= y.w; j++) {
      z.a[i][j] = (x.a[i][j] + y.a[i][j]) % m;
    }
  }
  return z;
}

MA operator *(const MA &x, const MA &y) {
  if(x.w != y.h) {
    exit(1);
  }
  MA z(x.h, y.w);
  for(int i = 1; i <= x.h; i++) {
    for(int j = 1; j <= y.w; j++) {
      for(int k = 1; k <= x.w; k++) {
        (z.a[i][j] += (x.a[i][k] * y.a[k][j])) %= m;
      }
    }
  }
  return z;
}

MA operator *=(MA &x, const MA &y) {
  x = x * y;
  return x;
}

MA qmi(const MA &x, int y) {
  MA ans(1, x.h, x.w), z = x;
  while(y) {
    if(y & 1) {
      ans *= z;
    }
    z *= z, y >>= 1;
  }
  return ans;
}

MA a;

MA mul(int l, int r) {
  if(l == r) {
    return qmi(a, l);
  }
  if((r - l) % 2) {
    int mid = (l + r) / 2;
    auto x = qmi(a, mid + 1 - l), y = mul(l, mid);
    return y + y * x;
  } else {
    return mul(l, l) + mul(l + 1, r);
  }
}

signed main() {
  int n, k;
  cin >> n >> k >> m;
  a.h = a.w = n;  
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cin >> a.a[i][j];
      a.a[i][j] %= m;
    }
  }
  MA ans = mul(1, k);
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cout << ans.a[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：jqQt0220 (赞：0)

矩阵快速幂加点数学。

有矩阵有乘方肯定要矩阵快速幂。但是直接暴力一个个加是 $O(k\log k)$ 的（把矩阵加法和乘法看做常数），再看数据范围，$k\le10^{9}$，寄。

尝试优化。令 $S_{k}=A+A^{2}+A^{3}+\cdots+A^{k}$。

当 $k$ 为偶数时：（$I$ 为单位矩阵）
$$
\begin{aligned}
S_{k}&=(A+A^{2}+\cdots+A^{\frac{k}{2}})+(A^{\frac{k}{2}+1}+A^{\frac{k}{2}+2}+\cdots+A^{k})\\
&=I(A+A^{2}+\cdots+A^{\frac{k}{2}})+A^{\frac{k}{2}}(A+A^{2}+\cdots+A^{\frac{k}{2}})\\
&=(I+A^{\frac{k}{2}})(A+A^{2}+\cdots+A^{\frac{k}{2}})\\
&=(I+A^{\frac{k}{2}})\cdot S_{\frac{k}{2}}
\end{aligned}
$$

当 $k$ 为奇数时：
$$
\begin{aligned}
S_{k}&=A+(A^{2}+A^{3}+\cdots+A^{k})\\
&=A+A(A+A^{2}+A^{3}+\cdots+A^{k-1})\\
&=A+A\cdot S_{k-1}
\end{aligned}
$$

这样就有了递推式：
$$
S_{k}=
\begin{cases}
\begin{aligned}
A&(k=1)\\
(I+A^{\frac{k}{2}})\cdot S_{\frac{k}{2}}&(k\bmod2=0)\\
A+A\cdot S_{k-1}&(k\bmod2=1)
\end{aligned}
\end{cases}
$$

直接递归求解即可。代码：
```cpp
#define ll long long
const int _mxn=100+5;
int _mod;
struct matrix//贼丑的矩阵结构体，不要学我（
{
    int n,m;
    ll val[_mxn][_mxn];
    matrix(){}
    matrix(int _n):n(_n),m(_n)//单位阵的构造函数
    {
        memset(this->val,0,sizeof(this->val));
        for(int i=1;i<=_n;i++)
            this->val[i][i]=1;
    }
    matrix(int _n,int _m):n(_n),m(_m)//空矩阵的构造函数
    {
        memset(this->val,0,sizeof(this->val));
    }
    void print()//输出（其实单独在外面写一个函数更好一点）
    {
        for(int i=1;i<=this->n;i++)
            for(int j=1;j<=this->m;j++)
                cout<<this->val[i][j]<<" \n"[j==this->m];
    }
}I;
matrix operator+(matrix x,matrix y)//矩阵加
{
    int n=x.n,m=x.m;
    matrix res(n,m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            res.val[i][j]=(x.val[i][j]+y.val[i][j])%_mod;
    return res;
}
matrix operator*(matrix x,matrix y)//矩阵乘
{
    int n=x.n,m=y.m,l=x.m;
    matrix res(n,m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=l;j++)
            for(int k=1;k<=m;k++)
                res.val[i][j]=(res.val[i][j]+x.val[i][k]*y.val[k][j]%_mod)%_mod;
    return res;
}
matrix qpow(matrix x,ll n)//矩阵快速幂
{
    matrix res(x.n);
    while(n>0)
    {
        if(n&1)
            res=res*x;
        x=x*x;
        n>>=1;
    }
    return res;
}
matrix sum(matrix a,int x)//求解
{
    if(x==1)
        return a;
    if(x%2==0)
        return sum(a,x/2)*(I+qpow(a,x/2));
    else
        return a+a*sum(a,x-1);
}
int n,k;
int main()
{
    ___();
    cin>>n>>k>>_mod;
    matrix a(n,n);
    I=matrix(n);//构造单位阵
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a.val[i][j];
    sum(a,k).print();//求解并输出
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 思路

发现这个式子可以通过提 $A_x$ 为公因数来避免重复计算，因为矩阵乘法满足分配律。

比如 $k=5$ 时式子 $A+A^2+A^3+A^4+A^5$可以表示为 $A+A^2+A^3+A^3(A+A^2)$。

此时令 $A+A^2=T$，式子化为 $T+A^3+A^3\times T$，$T$ 只用计算一遍，时间自然会优很多。

类似二分的思想，显然在 $x=\left \lceil \frac{k}{2} \right \rceil $ 的时候会把递推的时间优化成 $\log k$。

因为正如上文的例子，此时我们把整个式子变成了形如 $A+B\times A$ 的式子。而我们只用计算一次 $A$，复杂度自然减半。

考虑分治解决。

令 $f(x)=\sum\limits_{i=1}^x A^i$。

则有：

$$f(x)=\begin{cases}
 f( \frac{x}{2}) +A^{\frac{x}{2}}\times f(\frac{x}{2})& x\in \{x\mid x=2k,k\in \mathbb{N} \}\\ 
 f( \left \lfloor \frac{x}{2} \right \rfloor ) +A^{\left \lceil \frac{x}{2} \right \rceil }+A^{\left \lceil \frac{x}{2} \right \rceil }\times f(\left \lfloor \frac{x}{2} \right \rfloor ) & x\in \{x\mid x=2k+1,k\in \mathbb{N_+}\}\\
A & x=1

\end{cases}$$

分治复杂度 $O(\log k)$，计算 $A^k$ 复杂度 $O(n^3\log k)$，总复杂度 $O(n^3\log^2 k)$。

# Code

```cpp
#include<bits/stdc++.h>
#define inf 2e9
#define linf 1e18
#define db double
#define ldb long double
#define sd std::
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define umap(x,y) sd unorded_map<x,y>
#define pque(x) sd priority_queue<x>
#define MAX(x,y) (x>y?x:y)
#define MIN(x,y) (x<y?x:y)
#define il inline
#define pii sd pair<int,int>
#define X first
#define Y second
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<":"<<x<<"\n"
#define me(x,y) memset(x,y,sizeof x)
#define kg putchar(' ')
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),x=-x;printt(x);}
il void printk(int x){print(x),kg;}
il void put(int x){print(x);puts("");}
const int N=110;
int n,mod;
struct M//矩阵 
{
	int a[N][N];
	int* operator[](int x){return a[x];}
	il void clear(){me(a,0);}
	il void init(){F(i,1,n) a[i][i]=1;}
	il M operator*(M t)
	{
		M res;
		res.clear();
		F(i,1,n) F(j,1,n) F(k,1,n) res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
		return res;
	}
	il M operator^(int k)
	{
		M res,_=*this;
		res.init();
		while(k)
		{
			if(k&1) res=res*_;
			_=_*_;
			k>>=1;
		}
		return res;
	}
	il M operator+(M t)
	{
		M res;
		res.clear();
		F(i,1,n) F(j,1,n) res.a[i][j]=(a[i][j]+t.a[i][j])%mod;
		return res;
	}
}A;
int k;
M f(int x)//计算 
{
	if(x==1) return A;
	if(x&1)//奇数 
	{
		M p=f(x/2);
		return p+(A^((x+1)/2))+(A^((x+1)/2))*p;
	}
	else//偶数 
	{
		M p=f(x/2);
		return p+(A^(x/2))*p;
	}
}
il void solve()
{
	n=read(),k=read(),mod=read();
	F(i,1,n) F(j,1,n) A[i][j]=read();
	M ans=f(k);
	F(i,1,n) 
	{
		F(j,1,n) printk(ans[i][j]);
		puts("");
	}
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
}
```

---

