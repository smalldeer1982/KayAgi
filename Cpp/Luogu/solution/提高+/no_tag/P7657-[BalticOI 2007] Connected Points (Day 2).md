# [BalticOI 2007] Connected Points (Day 2)

## 题目描述

考虑一个有 $3×N$ 点的规则网格，网格中的每个点最多有八个相邻点（见图 $1$）。  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/4j322bxt.png)  
我们有兴趣计算连接网格点以形成满足以下条件的多边形的不同方式的数量：  
1. 多边形的顶点集由所有 $3×N$ 个点组成。
1. 多边形的相邻顶点是网格中的相邻点。  
1. 每个多边形都很简单，即不能有任何自相交。  

当 $N=6$ 时的两个可能的多边形如图 $2$。
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/e2yye0px.png)  
请编写一个程序，为给定的 $N$ 计算连接点的可能方法数，答案对 $10^9$ 取模。

## 说明/提示

#### 数据规模与约定  
对于 $30 \% $ 的数据，$0 < N \le 200$。  
对于 $70 \% $ 的数据，$0 <N \le 10^5$。  
对于 $100 \%$ 的数据，$0 <N \le 10^9$。
#### 题目说明  
来源于 [Baltic Olympiad in Informatics 2007](https://www.boi2007.de/en/welcome) 的 [Day 2:points](https://www.boi2007.de/tasks/points.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
3```

### 输出

```
8```

## 样例 #2

### 输入

```
4```

### 输出

```
40```

# 题解

## 作者：封禁用户 (赞：6)

# Picture

![](https://cdn.luogu.com.cn/upload/image_hosting/xu1z0z9v.png)

# Main Solution

分类讨论题！放一张图（图在上面），我们慢慢来。

~~不要在意这个字迹……~~

如图 $1$，连接 $3 \times n$ 的网格，可以先连个方框，再改掉一些边，塞进剩下 $n-2$ 个点。

$n-2$ 个点中，最左边和最右边的点单独考虑，剩下的 $n-4$ 个点塞进去的方式有 $4$ 种，如图 $2$。

设 $a_i,b_i,c_i,d_i$ 分别为 $4$ 种状态下塞进前 $i$ 个点的状态数。

如图 $4$，考虑 $i=1$，可得初始状态：

$$\begin{cases} a_1=2, \\ b_1=2, \\ c_1=2, \\ d_1=0. \end{cases}$$

如图 $5$，考虑 $i=n-2$，可得答案 $X$ 的计算方式：

$$X=7a_{n-3}+7b_{n-3}+6c_{n-3}+6d_{n-3}$$

如图 $3$，考虑由 $i-1$ 转移到 $i$：

$$\begin{cases} a_i=2a_{i-1}+2b_{i-1}+2c_{i-1}+2d_{i-1}, \\ b_i=2a_{i-1}+2b_{i-1}+2c_{i-1}+2d_{i-1}, \\ c_i=a_{i-1}, \\ d_i=b_{i-1}. \end{cases}$$

于是，我们上矩阵快速幂计算就行了，如图 $6$：

$$\begin{bmatrix}2 \\ 2 \\ 2 \\ 0\end{bmatrix}
 \times \begin{bmatrix}2 & 2 & 2 & 2 \\ 2 & 2 & 2 & 2 \\ 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \end{bmatrix}^{n-4}=\begin{bmatrix}a_{n-3} \\ b_{n-3} \\ c_{n-3} \\ d_{n-3}\end{bmatrix}$$

记得特判 $n \le 4$。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=1e9;
struct Square
{
	int n,m;
	long long a[5][5];
};
Square operator*(Square a,Square b)
{
	if(a.m!=b.n) exit(-1);
	int n=a.n,m=a.m,k=b.m;
	Square c;
	c.n=n,c.m=k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			c.a[i][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			for(int l=1;l<=m;l++)
				c.a[i][j]+=a.a[i][l]*b.a[l][j],c.a[i][j]%=P;
	return c;
}
Square operator^(Square a,long long b)
{
	int n=a.n;
	if(a.n!=a.m) exit(-1);
	Square tmp[64];
	tmp[0]=a;
	for(int i=1;i<=63;i++)
		tmp[i]=tmp[i-1]*tmp[i-1];
	Square c;
	c.n=c.m=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c.a[i][j]=(i==j);
	for(long long i=0,j=1;i<=63;i++,j<<=1)
		if(b&j) c=c*tmp[i];
	return c;
}
int main()
{
    int n;
    cin>>n;
    if(n==1) cout<<0;
    if(n==2) cout<<1;
    if(n==3) cout<<8;
    if(n==4) cout<<40;
    if(n<=4) return 0;
    Square s=((Square){4,4,{{0,0,0,0,0},{0,2,2,2,2},{0,2,2,2,2},{0,1,0,0,0},{0,0,1,0,0}}})^(n-4);
    Square t=s*((Square){4,1,{{0,0},{0,2},{0,2},{0,2},{0,0}}});
    cout<<(7*t.a[1][1]+7*t.a[2][1]+6*t.a[3][1]+6*t.a[4][1])%P;
    return 0;
}
```

# Extended Solution

很明显，当 $n \ge 2$ 时，$a_n=b_n$，$c_n=d_n=a_{n-1}$。

此时的初始状态是：

$$\begin{cases} a_1=2, \\ a_2=12. \end{cases}$$

答案 $X$ 的计算方式是：

$$X=14a_{n-3}+12a_{n-4}$$

由 $i-1$ 转移到 $i$：

$$a_i=4a_{i-1}+4a_{i-2}$$

于是，我们上矩阵快速幂计算就行了：

$$\begin{bmatrix}4 & 4 \\ 1 & 0\end{bmatrix}^{n-5} \times \begin{bmatrix}12 \\ 2\end{bmatrix}=\begin{bmatrix}a_{n-3} \\ a_{n-4}\end{bmatrix}$$

记得特判 $n \le 5$。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=1e9;
struct Square
{
	int n,m;
	long long a[3][3];
};
Square operator*(Square a,Square b)
{
	if(a.m!=b.n) exit(-1);
	int n=a.n,m=a.m,k=b.m;
	Square c;
	c.n=n,c.m=k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			c.a[i][j]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			for(int l=1;l<=m;l++)
				c.a[i][j]+=a.a[i][l]*b.a[l][j],c.a[i][j]%=P;
	return c;
}
Square operator^(Square a,long long b)
{
	int n=a.n;
	if(a.n!=a.m) exit(-1);
	Square tmp[64];
	tmp[0]=a;
	for(int i=1;i<=63;i++)
		tmp[i]=tmp[i-1]*tmp[i-1];
	Square c;
	c.n=c.m=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c.a[i][j]=(i==j);
	for(long long i=0,j=1;i<=63;i++,j<<=1)
		if(b&j) c=c*tmp[i];
	return c;
}
int main()
{
    int n;
    cin>>n;
    if(n==1) cout<<0;
    if(n==2) cout<<1;
    if(n==3) cout<<8;
    if(n==4) cout<<40;
    if(n==5) cout<<192;
    if(n<=5) return 0;
    Square s=((Square){2,2,{{0,0,0},{0,4,4},{0,1,0}}})^(n-5);
    Square t=s*((Square){2,1,{{0,0,0},{0,12,0},{0,2,0}}});
    cout<<(14*t.a[1][1]+12*t.a[2][1])%P;
    return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

目前这题唯一的题解是我最强的一位学弟发的，但是感觉有点复杂，我肯定是没耐心慢慢分讨的。

先做一点基本的观察。除了最左端和最右端，必定没有贯穿一整列的竖线（当然最左端和最右端也都没有）；**这张图所有点的度数恰为 2**。

考虑联通的二正则图必定为一个环（求出这个图的一棵 DFS 树即证），所以我们只需要保证这张图联通且所有点的度数恰好为 $2$ 即可。

首先考虑如何保证度数为 $2$。这个比较容易，你在转移的过程中，每次枚举第 $i$ 和 $i+1$ 列相连的所有边以及第 $i+1$ 列中的所有边，记录第 $i$ 列所有点的度数即可。

然后考虑如何保证点联通。这里只需要保证没有第二个连通块。那么再在状态里面增加第 $i$ 列三个点之间两两是否在同一个连通块中。每次转移的时候保证一下没有哪个连通块出现在第 $i$ 列缺没出现在第 $i+1$ 列即可。

这样一共有 $3 \times 3 \times 3 \times 5$ 种状态，使用矩阵快速幂大差不差能通过。（有用状态比这少，但是我太懒了，那就凑合着过吧）

又慢，代码又长，唯一的优点是不需要分类讨论和画图。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MOD=1000000000;
struct Matrix {int v[135][135];}T,M;
Matrix operator *(Matrix A,Matrix B) {
	Matrix C; memset(C.v,0,sizeof(C.v));
	ffor(i,0,134) ffor(j,0,134) ffor(k,0,134) C.v[i][k]=(C.v[i][k]+1ll*A.v[i][j]*B.v[j][k])%MOD;
	return C;
}
Matrix operator ^(Matrix A,int n) {
	Matrix res; memset(res.v,0,sizeof(res.v)); ffor(i,0,134) res.v[i][i]=1;
	while(n) {
		if(n&1) res=res*A;
		A=A*A,n>>=1;	
	}
	return res;
}
int trans(int x,int y,int z,int xy,int xz,int yz) {
	int st1=x+y*3+z*9,st2=0;
	if(xy&&xz&&yz) st2=4;
	else if(xy) st2=1;
	else if(xz) st2=2;
	else if(yz) st2=3;
	return 27*st2+st1;
}
int q(int st,int p) {return !!(st&(1<<p));}
int n,fa[7];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void merge(int u,int v) {return fa[find(v)]=find(u),void();}
int nxt(int x,int y,int z,int xy,int xz,int yz,int st) {
	if(xy+xz+yz==2) return -1;
	if((st&6)==6) return -1;
	if((st&48)==48) return -1;
	if(x+q(st,0)+q(st,1)!=2) return -1;
	if(y+q(st,2)+q(st,3)+q(st,4)!=2) return -1;
	if(z+q(st,5)+q(st,6)!=2) return -1;
	int X=q(st,0)+q(st,2)+q(st,7),Y=q(st,7)+q(st,3)+q(st,1)+q(st,8)+q(st,5),Z=q(st,4)+q(st,6)+q(st,8);
	if(X>2||Y>2||Z>2) return -1;
	ffor(i,1,6) fa[i]=i;
	if(xy) merge(1,2); if(xz) merge(1,3); if(yz) merge(2,3);
	if(q(st,0)) merge(1,4); if(q(st,1)) merge(1,5); if(q(st,2)) merge(4,2); if(q(st,3)) merge(2,5);
	if(q(st,4)) merge(2,6); if(q(st,5)) merge(3,5); if(q(st,6)) merge(3,6); if(q(st,7)) merge(4,5); if(q(st,8)) merge(5,6);
	int XY=(find(4)==find(5)),XZ=(find(4)==find(6)),YZ=(find(5)==find(6));
	ffor(i,1,3) {
		int flg=0;
		ffor(j,4,6) flg|=(find(i)==find(j));
		if(!flg) return -1;
	}
	return trans(X,Y,Z,XY,XZ,YZ);
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	ffor(x,0,2) ffor(y,0,2) ffor(z,0,2) ffor(xy,0,1) ffor(xz,0,1) ffor(yz,0,1) ffor(st,0,(1<<9)-1) {
		int lst=trans(x,y,z,xy,xz,yz),mzx=nxt(x,y,z,xy,xz,yz,st);
		if(mzx!=-1) M.v[lst][mzx]++;
	}
	cin>>n,M=M^(n-1);
	T.v[0][trans(0,0,0,0,0,0)]=1;
	T.v[0][trans(0,1,1,0,0,1)]=1;
	T.v[0][trans(1,1,0,1,0,0)]=1;
	T.v[0][trans(1,2,1,1,1,1)]=1;
	T=T*M;
	cout<<T.v[0][trans(2,2,2,1,1,1)];
	return 0;
}
```

---

