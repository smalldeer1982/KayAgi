# Magic Gems

## 题目描述

xht37 有很多魔法宝石。每颗魔法宝石可以分解成 $ m $ 颗普通宝石，魔法宝石和普通宝石都占据 $ 1 $ 体积的空间，但普通宝石不能再被分解。

xht37 想要使一些魔法宝石分解，使得所有宝石占据的空间**恰好**为 $ n $ 单位体积。显然，一个魔法宝石分解后会占据 $ m $ 体积空间，不分解的魔法宝石仍占据 $ 1 $ 体积空间。

现在 xht37 想要求出有多少种分解方案，可以让最后得到的宝石**恰好**占据 $ n $ 单位体积。两种分解方案不同当且仅当分解的魔法宝石数量不同，或者是所用的宝石的编号不同。

xht37 当然知道怎么做，但是他想考考你。

## 样例 #1

### 输入

```
4 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
3
```

# 题解

## 作者：Grisses (赞：8)

## upd：

- 感谢 VitrelosTia 指出的问题，并修改了一些其他的问题。

---

就是一些转移式，用矩阵快速幂优化一下就可以了。

首先，定义矩阵乘法：

对于一个 $n\times k$ 的矩阵 $A$ 和一个 $k\times m$ 的矩阵 $B$ 还有一个矩阵 $C=A\times B$。那么 $C$ 是一个 $n\times m$ 的矩阵，且 $C_{ij}=\sum\limits_{p=1}^kA_{i,p}\times B_{p,j}(i=\overline{1,2,\cdots,n},j=\overline{1,2,\cdots,m})$。

然后，因为矩阵乘法满足结合律，所以我们有了矩阵快速幂。矩阵快速幂的话就是把快速幂的板子套在矩阵上而已。

## 题目

$$f_i=1(i<m)$$
$$f_i=f_{i-1}+f_{i-m}(m\le i)$$

求 $f_n$。

用一个 $m\times m$ 的矩阵就可以了。

$$\begin{pmatrix}f_{i-1}+f_{i-m}\\f_{i-1}\\f_{i-2}\\\vdots\\f_{i-m+1}\end{pmatrix}=\begin{pmatrix}1&0&0&\cdots&0&0&1\\1&0&0&\cdots&0&0&0\\0&1&0&\cdots&0&0&0\\\vdots&&&\ddots&&&\vdots\\0&0&0&\cdots&0&1&0\end{pmatrix}\begin{pmatrix}f_{i-1}\\f_{i-2}\\f_{i-3}\\\vdots\\f_{i-m}\end{pmatrix}$$

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int mod=1e9+7;
  int n,m,sum;
  struct M{
      int a[100][100];
      M operator*(M t){
          M res;
          for(int i=0;i<m;i++)for(int j=0;j<m;j++)res.a[i][j]=0;
          for(int i=0;i<m;i++){
              for(int j=0;j<m;j++){
                  for(int k=0;k<m;k++){
                      res.a[i][j]=((res.a[i][j]+a[i][k]*t.a[k][j]%mod+mod)%mod+mod)%mod;
                  }
              }
          }
          return res;
      }
      M operator^(int x){
          M res,_=*this;
          for(int i=0;i<m;i++)for(int j=0;j<m;j++)res.a[i][j]=(i==j);
          while(x){
              if(x&1)res=res*_;
              _=_*_;
              x>>=1; 
          }
          return res;
      }
  }ans,base;
  signed main()
  {
      scanf("%lld%lld",&n,&m);
      if(n<m)puts("1");
      else{
          for(int i=0;i<m;i++)for(int j=0;j<m;j++)ans.a[i][j]=(!j);
          for(int i=0;i<m;i++)for(int j=0;j<m;j++)base.a[i][j]=0;//设置矩阵
          for(int i=1;i<m;i++)base.a[i][i-1]=1;
          base.a[0][0]=base.a[0][m-1]=1;
          ans=(base^(n-m+1))*ans;
          printf("%lld",ans.a[0][0]);
      }
      return 0;
  }
```

---

## 作者：August_Light (赞：6)

# CF1117D Magic Gems 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1117D)

## 题意简述

给定正整数 $n, m$，寻找一个 $\texttt{01}$ 串 $s$，记串中 $\texttt 0$ 的数目为 $p$，$\texttt 1$ 的数目为 $q$，使得 $p + mq = n$。

求符合条件的 $s$ 的个数模 $10^9+7$ 的值。

数据范围：$1 \le n \le 10^{18}$，$2 \le m \le 100$。

## 前置知识：

- 基础 DP

- 矩阵快速幂

    - 模板题目：[P1939 【模板】矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)

    - 练习题：[P1349 广义斐波那契数列](https://www.luogu.com.cn/problem/P1349)

请确保你已经理解了**矩阵乘法的具体原理**以及**递推矩阵的构造**。

## 解法

可以用 DP 来做。

设 $f_i$ 为符合 $p + mq = i$ 的 $s$ 的数目。

因为

- 要么从少一个 $\texttt 0$ 转移而来（$f_{i-1}$）

- 要么从少一个 $\texttt 1$ 转移而来（$f_{i-m}$）

$$
f_i =
\begin{cases}
1                 & i  <  m \\
f_{i-1} + f_{i-m} & i \ge m
\end{cases}
$$

直接做这个 DP 的话时间复杂度为 $O(n)$，发现 $n \le 10^{18}$，过不去（悲）。

注意到这是一个递推的 DP，考虑使用矩阵快速幂优化。

容易构造出以下矩阵：

$$
\begin{bmatrix}
f_i       \\
f_{i-1}   \\
\vdots    \\
f_{i-m+2} \\
f_{i-m+1}
\end{bmatrix}

=

\begin{bmatrix}
1 &   &        &   &   & 1 \\
1 &   &        &   &   &   \\
  & 1 &        &   &   &   \\
  &   & \ddots &   &   &   \\
  &   &        & 1 &   &   \\
  &   &        &   & 1 &   \\
\end{bmatrix}

\begin{bmatrix}
f_{i-1}   \\
f_{i-2}   \\
\vdots    \\
f_{i-m+1}   \\
f_{i-m}
\end{bmatrix}
$$

其中大方阵为 $m \times m$ 的矩阵。

可以做矩阵快速幂。最终时间复杂度 $O(m^3\log n)$。

矩阵构造：（下标从 $1$ 开始）

```cpp
A.M[1][1] = 1; A.M[1][m] = 1;
for (int i = 2; i <= m; i++)
    A.M[i][i - 1] = 1;
```

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// 省略快读快写的实现

const int MAXN = 105;
const int MOD = 1e9 + 7;
int L;
struct Matrix {
    LL M[MAXN][MAXN];
    void clear() {
        memset(M, 0, sizeof(M));
    }
    void reset() {
        clear();
        for (int i = 1; i <= L; i++)
            M[i][i] = 1;
    }
    Matrix friend operator* (const Matrix &A, const Matrix &B) {
        Matrix Ans; Ans.clear();
        for (int i = 1; i <= L; i++)
            for (int k = 1; k <= L; k++)
                for (int j = 1; j <= L; j++)
                    Ans.M[i][j] = (Ans.M[i][j] + A.M[i][k] * B.M[k][j]) % MOD;
        return Ans;
    }
};
Matrix expow(Matrix T, LL k) {
    Matrix Ans; Ans.reset();
    while (k) {
        if (k & 1)
            Ans = Ans * T;
        T = T * T, k >>= 1;
    }
    return Ans;
}

LL n, m, ans;
int main() {
    n = read(); m = read();

    if (n < m)
        ans = 1;
    else {
        L = m;
        Matrix A; A.clear();
        A.M[1][1] = 1; A.M[1][m] = 1;
        for (int i = 2; i <= m; i++)
            A.M[i][i - 1] = 1;

        ans = expow(A, n).M[1][1];
    }

    write(ans, '\n');
    return 0;
}
```

## 矩阵快速幂优化 DP 的练习题

[P4910 帕秋莉的手环](https://www.luogu.com.cn/problem/P4910)

---

## 作者：chlchl (赞：4)

## 做法
本题矩阵快速幂加速好题。

$n\leq 10^{18}$ 显然需要 $\log$ 级别的算法。我们先考虑一个朴素的 DP：设 $f_i$ 为刚好占据 $i$ 空间的方案数。

显然，转移有两种情况：如果是普通宝石或未拆开的魔法宝石，占据空间为 $1$，$f_i\leftarrow f_i+f_{i-1}$。

如果是拆开的魔法宝石，占据空间为 $m$，$f_i\leftarrow f_i+f_{i-m}$。

所以最后就是 $f_i=f_{i-1}+f_{i-m}$。

但是这个是 $O(n)$ 的，我们需要矩阵优化。

注意到它涉及到前 $m$ 个位置的元素，所以我们开一个 $m\times m$ 的矩阵。

一开始，我们是 $\lbrack f_i,f_{i-1},\cdots,f_{i-m+1} \rbrack$。

考虑一次乘法怎么乘过去。容易发现，当 $m=2$ 时，矩阵是：

$\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}$

当 $n=3$ 时，矩阵为：

$\begin{bmatrix}
1 & 1 & 0\\
0 & 0 & 1\\
1 & 0 & 0
\end{bmatrix}$

当 $n=4$ 时，矩阵为：

$\begin{bmatrix}
1 & 1 & 0 & 0\\
0 & 0 & 1 & 0\\
0 & 0 & 0 & 1\\
1 & 0 & 0 & 0
\end{bmatrix}$

注意这种东西尽量推到 $4$，因为那个 $2\times 2$ 的你实在是看不出什么东西的。

以此类推，我们可以得出：$matrix_{i,i+1}=matrix_{m-1,0}=matrix_{0,0}=1$（下标从 $0$ 开始）。

时间复杂度 $O(m^3\log n)$，因为 $m$ 很小，然后就没有然后了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;
const int N = 100 + 10;
ll n, m;

struct matrix{
	int r, c;
	ll a[N][N];
	
	matrix(int R, int C, int p = 0): r(R), c(C){
		memset(a, 0, sizeof(a));
		for(int i=0;i<min(c,r);i++)	a[i][i] = p;
	}
	ll* operator [] (int id){return a[id];}
	
	const ll* operator [] (int id) const{return a[id];}
	
	matrix operator * (const matrix &m) const {
		matrix ans(r, m.c);
		for(int i=0;i<r;i++) for(int j=0;j<m.c;j++)	for(int k=0;k<c;k++) ans[i][j] = (ans[i][j] + (ll)a[i][k] * m[k][j]) % MOD;
		return ans;
	}
	
	matrix exp(ll b){
		matrix a = *this, ans(r, r, 1);
		while(b){
			if(b & 1)	ans = ans * a;
			a = a * a, b >>= 1;
		}
		return ans;
	}
};

int main(){
	scanf("%lld%lld", &n, &m);
	matrix a(m, m), v(1, m);
	for(int i=0;i<m;i++)	a[i][i + 1] = a[0][0] = a[m - 1][0] = 1;
	v[0][0] = 1, v = v * a.exp(n);
	printf("%lld\n", v[0][0]);
	return 0;
}
```


---

## 作者：FxorG (赞：3)

### 前言：这题是复习矩阵加速的时候找到的

首先 我们令 $f_i$ 为取 $i$ 个的方案数 显然 $f_0=1$ 答案为 $f_n$ 

考虑转移  我们考虑不用魔法 即 $f_i=f_{i-1}$

使用魔法 则 $[i-m+1,i]$ 必定为不是魔法的 直接 $f_i=f_i+f_{i-m}$

然而这样复杂度是 $O(n)$ 的 观察递推式 发现是个线性的递推式 又因为 m 很小 考虑矩阵加速

初始矩阵为 

$ \begin{bmatrix}
f_{n-1} \ f_{n-2} \ ... \ f_{n-m-1}\\
\end{bmatrix}
$

显然转移矩阵为(m=3)

$ \begin{bmatrix}
0 \ 0 \ 1\\
1 \ 0 \ 0\\
0 \ 1 \ 1
\end{bmatrix}
$

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

#define N 200
#define mod (int)(1e9+7)
#define int long long

using namespace std;

int n,m;

struct node {
	int a[N][N];
	node () {
		memset(a,0,sizeof(a));
	}
}ans,A;

node operator * (node x,node y) {
	node ret;
	for(int i=1;i<=m;i++) {
		for(int j=1;j<=m;j++) {
			for(int k=1;k<=m;k++) {
				ret.a[i][j]=(ret.a[i][j]+x.a[i][k]*y.a[k][j])%mod;	
			}
		}
	}
	return ret;
}

int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}

void fpow(int y) {
	while(y) {
		if(y&1) ans=ans*A;
		y>>=1; A=A*A;
	}
}

signed main() {
	n=rd(); m=rd();
	if(n<m) {
		puts("1"); return 0;
	} 
	for(int i=1;i<m;i++) ans.a[1][i]=1;
	ans.a[1][m]=2;
	for(int i=1;i<m;i++) A.a[i+1][i]=1;
	A.a[1][m]=A.a[m][m]=1;
	fpow(n-m);
	printf("%lld",ans.a[1][m]%mod);
	return 0;
}
```

---

## 作者：CRTL_xzh2009 (赞：2)

设 $f[n]$ 为生成 $n$ 个宝石的方案数，它可以来自 $n-1$ 个宝石加 $1$ 个魔法宝石，或 $n-m$ 个宝石加 $m$ 个宝石（由一个魔法金币分裂而来）。

递推式前提：`f[i]=1`，满足 $i<m$；`f[0]=f[1]=1`。

递推式：

```cpp
f[i]=f[i-m]+f[i-1];
```

然后就可以用矩阵快速幂求了。

$\left[\begin{array}{lllll}
f_{i-1} & f_{i-2} & f_{i-3} & \cdots & f_{i-m}
\end{array}\right] \times\left[\begin{array}{ccccccc}
1 & 1 & 0 & \cdots & 0 & 0 & 0 \\
0 & 0 & 1 & \cdots & 0 & 0 & 0 \\
0 & 0 & 0 & \cdots & 0 & 0 & 0 \\
& \vdots & & \ddots & & \vdots & \\
0 & 0 & 0 & \cdots & 0 & 0 & 1 \\
1 & 0 & 0 & \cdots & 0 & 0 & 0
\end{array}\right]=\left[\begin{array}{lllll}
f_{i} & f_{i-1} & f_{i-2} & \cdots & f_{i-m+1}
\end{array}\right]$

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
typedef long long ll;
ll n;	
int m,base[105][105],ans[105][105];
void multi(int a[105][105],int b[105][105])
{
	int c[105][105]{};
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=m;++k)
				c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j]%mod)%mod;
	for(int i=1;i<=m;++i)
	    for(int j=1;j<=m;++j)
		    a[i][j]=c[i][j];
} 
int ksm(ll p)
{
	while(p)
	{
		if(p&1)
		    multi(ans,base);
		multi(base,base);
		p>>=1;
	}
	return ans[1][1];
}
int main(){
	scanf("%lld%d",&n,&m);
	for(int i=2;i<=m;++i)base[i][i-1]=1;
	base[1][m]=1,base[m][m]=1;
	for(int i=1;i<=m;++i)
	    ans[1][i]=1;
	++ans[1][m];
	printf("%d",ksm(n-1));
	return 0;
}
```


---

## 作者：lhc0707 (赞：1)

## 题意

很多个魔法宝石，每个魔法宝石都可以分解成 $m$ 个普通宝石，普通宝石不可以被分解。分解前，每个魔法宝石占据 $1$ 单位空间，分解后，每个普通宝石各占 $1$ 单位空间，共占 $m$ 个单位空间，问有多少种情况使最后得到的宝石**恰好**占据 $n$ 个单位空间。

## 题解

先考虑最简单的动态规划。我们设 $f_i$ 表示占据 $i$ 个空间有多少种情况。

我们可以很容易地列出方程转移式：

$$f_i = \begin{cases} 1 & i < m \\ f_{i-1}+f_{i-m} & i  \ge  m \end{cases}$$

结果取 $f_n$ 的值即可。

这样递推下去，时间复杂度是 $O(N)$，而 $1 \le N \le 10^{18}$ 的数据量告诉我们这样做是不行滴。


对付这么大的数据，只好用矩阵快速幂优化递推了。

不会矩阵快速幂？[看这里](https://oi-wiki.org/math/linear-algebra/matrix/)

这样转移矩阵就可以了：

$$
[f_{n-1},f_{n-2},\cdots ,f_{n-m-1}] \times   \begin{bmatrix} 0 & 0 & \cdots & 0 & 1 \\ 1 & 0 & \cdots & 0 & 0 \\ 0 & 1 & \cdots & 0 & 0 \\ \vdots & \vdots & \ddots & \vdots & \vdots \\ 0 & 0 & \cdots & 1 & 0\\ 0 & 0 & \cdots & 1 & 1 \end{bmatrix}  = [f_{n-1},f_{n-2},\cdots ,f_{n-m}]
$$

中间的转移矩阵大小为 $m \times m$，设计出矩阵的转移之后，我们就可以用矩阵快速幂计算了。时间复杂度是 $O(M^3\log N)$，可过。

下面放上代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define N 105
#define il inline
#define ll long long
#define mod 1000000007
ll m,n;
il void rd(ll &x){
	x=0;int f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f*=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	x*=f;
}
struct Mat{
	ll a[N][N];
	il Mat(){memset(a,0,sizeof(a));}
	il Mat operator *(const Mat &b)const{
		Mat c;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++)
				for(int k=1;k<=m;k++)
					(c.a[i][j]+=a[i][k]*b.a[k][j])%=mod;
		return c;
	}
}ans,base;
il void init(){
	for(int i=1;i<m;i++) ans.a[1][i]=1;
	ans.a[1][m]=2;
	for(int i=1;i<m;i++) base.a[i+1][i]=1;
	base.a[1][m]=1,base.a[m][m]=1;
}
il void qPow(ll b){
	for(;b;b>>=1){
		if(b&1) ans=ans*base;
		base=base*base;
	}
}
int main(){
	rd(n),rd(m);
	if(n<m)return puts("1"),0;
	init();
	qPow(n-m);
	printf("%lld\n",ans.a[1][m]%mod);
	return 0;
}
```

望过审QWQ。

---

## 作者：markding (赞：1)

前言：这个题目原本是紫题，我做了此题~~后觉得这种水死的题目居然配得上紫？~~，最终此题变为蓝题。正好水个题解（

回归正题。对于这道题目，首先令我们头疼的是 $n$ 的数据范围。

而当 $n$ 较小时，读者应该可以想出一个较为 naive 的 dp 方程：$f_i=f_{i-1}+f_{i-m}$，其中 $f_i$ 表示总体积为 $i$ 的方案数。该转移式的含义是，对于一颗宝石，要么分解了变为 $m$ 体积，要么不分解，体积为 $1$。初值 $f_0=1$，目标 $f_n$。

当然啦这个方法在 $n$ 过大时是肯定会超时的，需要加以优化。当 $m=2$ 时，该方程是经典的斐波那契数列，我们可以用矩阵乘法加以计算，初始矩阵为 $\begin{bmatrix}1&0\end{bmatrix}$，加速矩阵为 $\begin{bmatrix}1&1\\1&0\end{bmatrix}$。

进一步，当 $m>2$ 时，也可以用矩阵加速。由于 dp 转移式里最多只会涉及到位置处于往前 $m$ 个的元素，所以可以将 $m$ 个数的值都放入初始矩阵里，也就是 $\begin{bmatrix}f_i&f_{i-1}&\cdots&f_{i-m+1}\end{bmatrix}$，我们希望在一次转移后，初始矩阵前 $m-1$ 个数都向后挪一格，第一个数变为 $f_i+f_{i-m+1}$，也就是：

$$\begin{bmatrix}1&1&0&0&\cdots&0\\0&0&1&0&\cdots&0\\0&0&0&1&\cdots&0\\\vdots&\vdots&\vdots&\vdots&\ddots&\vdots&\\0&0&0&0&\cdots&1\\1&0&0&0&0&0\end{bmatrix}$$

于是就顺利的解决了这道题。
```cpp
#include<iostream>
#include<vector>
using namespace std;
struct matrix
{
	int n,m;vector<vector<int>> mat;
	matrix(int _n,int _m){n=_n,m=_m,mat.resize(_n,vector<int>(_m,0));}
};
matrix operator *(matrix a,matrix b)
{
	matrix c(a.n,b.m);
	for(int i=0;i<a.n;i++)
		for(int j=0;j<b.m;j++)
			for(int k=0;k<a.m;k++)
				c.mat[i][j]=(c.mat[i][j]+1ll*a.mat[i][k]*b.mat[k][j])%1000000007;
	return c;
}
matrix operator ^(matrix a,long long p)
{
	matrix ret(a.n,a.n);
	for(int i=0;i<ret.n;i++)ret.mat[i][i]=1;
	for(;p;a=a*a,p/=2)if(p%2)ret=ret*a;
	return ret;
}
int main()
{
	long long n;int m;cin>>n>>m;
	matrix f(1,m),a(m,m);
	for(int i=0;i<m-1;i++)a.mat[i][i+1]=1;
	a.mat[0][0]=a.mat[m-1][0]=f.mat[0][0]=1;
	cout<<(f*(a^n)).mat[0][0];
}
```

---

## 作者：wdgm4 (赞：0)

## 前言

这是一道矩阵快速幂的水题。QWQ

## 正文

废话不多数，显然我们可以直接去推转移方程。设 $f_i$ 表示从左至右放若干可以分解也可以不分解的魔法宝石（分解魔法宝石视为直接在现已放置的宝石右面放 $m$ 个不分解的宝石）的方案数。则可以列出转移方程：

$$f_i=f_{i-m}+f_{i-1}$$

因为我们可以通过 $i-m$ 个宝石后面放上 $m$ 颗不分解的宝石（即一颗要分解的魔法宝石）或者 $i-1$ 个宝石后面放上 $1$ 颗不分解的宝石从而变成共有 $i$ 颗宝石。

可以发现这个转移方程和斐波那契数列非常像，所以我们可以矩阵快速幂实现上面的转移方程。

显然初始化时 $f_{1} =1,f_{2}=1,...,f_{m-1}=1,f_{m}=2$，因为对于 $i=1,2,...,m-1$ 时只能一个一个地放共 $i$ 颗不分解的宝石，而对于 $i=m$，可以直接让一个宝石分解，也可以一个一个地放共 $m$ 颗不分解的宝石，所以 $f_m=2$。

剩下的就是矩阵快速幂的模版了，代码如下。QWQ

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define MAXN 110
#define int long long
using namespace std;
int n,m;
struct QWQ{
	int a[MAXN][MAXN];
	int n,m;
} a,ans;
int k;
const int mod=1e9+7;
QWQ operator *(QWQ x,QWQ y){
	QWQ z;
	z.n=x.n;z.m=y.m;
	for(int i=1;i<=z.n;i++){
		for(int j=1;j<=z.m;j++){
			z.a[i][j]=0;
		}
	}
	for(int i=1;i<=z.n;i++){
		for(int j=1;j<=z.m;j++){
			for(int k=1;k<=x.m;k++){
				z.a[i][j]+=x.a[i][k]*y.a[k][j];
				z.a[i][j]%=mod;
			}
		}
	}
	return z;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	if(n<m){
		cout<<"1\n";
		return 0;
	}
	ans.n=m;ans.m=1;
	ans.a[1][1]=2;
	for(int i=2;i<=m;i++) ans.a[i][1]=1;
	a.n=m;a.m=m;
	a.a[1][1]=1;a.a[1][m]=1;
	for(int i=1;i<m;i++) a.a[i+1][i]=1;
	k=n-m;
	while(k){
		if(k&1) ans=a*ans;
		a=a*a;k>>=1;
	}
	cout<<ans.a[1][1]%mod<<"\n";
	return 0;
}
```


---

## 作者：RP_INT_MAX (赞：0)

矩阵加速递推典题。

## $\tt Solution$

先推朴素递推方程，再考虑矩阵优化。

设 $f(i)$ 表示占据单位体积为 $i$ 时放宝石的方案数。

很显然，$i<m$ 时无法分解，故此时 $f(i)=1$。

$i \ge m$ 时，分讨两种情况：

- 不将魔法宝石分解，此时占据 $1$ 单位体积的空间。

- 将魔法宝石分解掉，此时占据 $m$ 单位体积的空间。

易得转移方程：

$$
f(i)=\left\{
\begin{aligned}
& 1 & i<m \\
& f(i-1)+f(i-m) & i \ge m
\end{aligned}
\right.
$$

接下来思考如何构造矩阵。由特殊到一般。

$m=2$ 时，显然是斐波那契数列。矩阵如下：

$$
\begin{pmatrix}
1 & 1 \\
1 & 0
\end{pmatrix}
$$

$m=3$ 时，构造矩阵如下：

$$
\begin{pmatrix}
1 & 1 & 0 \\
0 & 0 & 1 \\
1 & 0 & 0
\end{pmatrix}
$$

$m=4$ 时，构造矩阵如下：

$$
\begin{pmatrix}
1 & 1 & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1 \\
1 & 0 & 0 & 0
\end{pmatrix}
$$

可得一般情况。设构造矩阵为 $A$，则（下标从 $0$ 计算）：

$$
A_{ij}=\left\{
\begin{aligned}
& 1 & j=i+1,0 \le i < m-1\\
& 1 & i=0,j=0\\
& 1 & i=m-1,j=0\\
& 0 & \text{Otherwise}
\end{aligned}
\right.
$$

时间复杂度：$O(m ^ 3 \log n)$。

## $\tt Code$

```cpp
// 以上省略头文件及快读快输部分。
#define pcs putchar(' ')
#define pcn putchar('\n')
#define for1(i,a,b) for(int i=(a);i<=(b);++i)
#define for2(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int N=110;
ll n;
int m;
struct M{
	ll m[N][N]; // 模数 1e9+7，两个数相乘可能爆 int，注意开 long long。
};
M operator*(const M&A,const M&B) {
	M C={0};
	for1(i,0,m-1) for1(k,0,m-1) for1(j,0,m-1)
		(C.m[i][j]+=A.m[i][k]*B.m[k][j])%=mod;
	return C;
}
M qp(M A,ll b) {
	M C={0};
	for1(i,0,m-1) C.m[i][i]=1; // 记得初始化单位矩阵。
	while(b) {if(b&1) C=C*A;A=A*A,b>>=1;}
	return C;
}
M A,B;
int main () {
	in(n),in(m);
	if(n<m) {out(1);return 0;} // 特判一种特殊情况。
	for1(i,0,m-2) A.m[i][i+1]=1;
	A.m[0][0]=A.m[m-1][0]=B.m[0][0]=1; // 初始化。
//	for1(i,0,m-1)
//		for1(j,0,m-1)
//			printf("%d%c",A.m[i][j]," \n"[j==m-1]);
	out((B*qp(A,n)).m[0][0]);
	return 0;
}
```

---

## 作者：bwartist (赞：0)

先不考虑 $n$ 的范围，就是很简单的dp。

设 `dp[i]` 为总体积为 `i` 的时候的方案数。

有两种情况，一种是不分解最后一颗魔法宝石，`dp[i]=dp[i-1]`。另一种情况，分解最后一颗魔法宝石，`dp[i]=dp[i-m]`。两种情况加起来来，`dp[i]=dp[i-1]=dp[i-m]`。

现在的时间复杂度是 $O(n)$。**考虑用 [矩阵加速](https://oi-wiki.org/math/matrix/#%E7%9F%A9%E9%98%B5%E5%8A%A0%E9%80%9F%E9%80%92%E6%8E%A8)优化。**
$$
\left[\begin{matrix}
dp_i & dp_{i-1} & dp_{i-2} &\dots dp_{i-m+1}
\end{matrix}\right]
$$
设这样一个行数为 $1$，列数为 $m$ 的矩阵为 $s_i$。

设以 $dp_{i+1}$ 开头的类似的矩阵为 $s_{i+1}$。

现在要使 $s_i$ 乘上一个矩阵 $k$ 后得到 $s_{i+1}$。

先从简单的开始推。

当 $m$ 为 $2$ 时，$k$ 为：
$$
\left[
\begin{matrix}
1 & 1 \\
1 & 0 \\ 
\end{matrix} \right]
$$

当 $m$ 为 $3$ 时，$k$ 为：
$$
\left[
\begin{matrix}
1 & 1 & 0\\
0 & 0 & 1\\
1 & 0 & 0
\end{matrix} \right]
$$

发现对于第一列：第一行，第 $m$ 行，数值是 1；对于第二列以及后面的，只有一个数为 1，且 1 的行数为列数减一。（其实是因为 $s_2$ 的第一个数对应着 $k$ 的第一列，第二个数对应 $k$ 的第二列......这里自己很容易推出来，在草稿本上画一下就行）

所以说每一次用 $s_{i-1} \times k = s_{i}$ 一直推就行，又因为是一直乘 $k$ 这同一个矩阵，就可以用**矩阵快速幂**解决。(其实跟整数的快速幂是差不多的，只是重新定义了乘法)

注意要开 longlong。

Code:

```cpp
//代码里面的变量名和上文的不一样，注意区分!
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
const int mo=1e9+7; 
int m;
ll n;
struct Matrix{
	ll a[105][105];
	Matrix(){
		memset(a,0,sizeof(a));
	}
}pr,k;
Matrix operator *(const Matrix &P,const Matrix &Q){
	Matrix ans;
	for(int i=1;i<=m;i++){
		for(int k=1;k<=m;k++){ 
			for(int j=1;j<=m;j++){
				ans.a[i][j]=((ans.a[i][j]+P.a[i][k]*Q.a[k][j]%mo)%mo+mo)%mo;
			} 
		}
	}
	return ans;
}
void mpow(ll x){
	while(x){
		if(x&1)	k=k*pr;
		x/=2;
		pr=pr*pr;
	}
}
int main(){
	cin>>n>>m;
	pr.a[1][1]=pr.a[m][1]=1;
	for(int i=2;i<=m;i++)	pr.a[i-1][i]=1;
	for(int i=1;i<=m;i++)	k.a[1][i]=1;
	if(n<m){ 
		cout<<1;
	}else{
		mpow(n-m+1);
		cout<<k.a[1][1];
	}
	return 0;
}
```


---

## 作者：dxrS (赞：0)

设 $dp_i$ 表示前 $i$ 个的方案数，那么 $i$ 可以单独不分裂，此时就是 $dp_{i-1}$；也可以分裂组成 $m$ 个普通的，此时就是 $dp_{i-m}$。

所以 $dp_i\gets dp_{i-1}+dp_{i-m}$。

初始状态 $dp_{i\in[0,m-1]}\gets1$。

观察到 $n$ 很大，可以使用矩阵快速幂优化，时间复杂度 $O(m^3\log n)$。

---

## 作者：Dilute (赞：0)

[$$\huge\texttt{在本人blog食用更佳}$$](http://dilute.coding.me/2019/03/02/Solutions/Solution-CF1117D/)

## 有趣的矩阵乘法

（为方便，下文中“大号宝石”代指连续的$m$个分裂出来的宝石，“小号宝石”代指未分裂的单个宝石）

首先，我们观察这题，考虑$DP$，设状态$f_i$表示已经取了$i$个单元的方案数的不难推出一个朴素的$O(n^2) DP$方程$f_i = \displaystyle\sum_{i - j \geq m} f_j  +1$（可以理解成上一个大号宝石放的位置，最后一个$1$即为全部用小号宝石填满的方案）

我们再仔细看看这个式子，加个前缀和，不难优化到$O(n)$，然而数据范围$n \leq 10^{18}$，这让我们考虑$O(\log n)$级别的算法，我们接下来考虑矩阵乘法优化这个式子。

<!--more-->

显然，这个式子跟满足$i - j \geq m$的$j$有关，但是这些数字的数量是$n$级别的，我们考虑将$\displaystyle\sum_{i - j \geq m} f_j$变形，变成$\displaystyle\sum_{j = 1}^{i} f_j - \sum_{j = i - m}^{j < i} f_j$ 这样只要我们维护一下$\displaystyle\sum_{j = 1}^{i} f_j$就可以把需要维护的值的数量降到$m$级别。

接下来直接在矩阵的第一行的第$j (1 \leq j \leq m) $ 位放上$f_{i - j}$，然后第$m + 1$位维护$\displaystyle\sum_{j = 1}^{i} f_j$，第$m + 2$位再弄个$1$，瞎构造一通转移矩阵，就可以愉快的套矩阵快速幂板子了，最终复杂度$O(m^3 \log n)$。

（转移的矩阵的具体构造建议看代码）

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define mod 1000000007

ll inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    ll sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

class Square{
    public:
        long long num[110][110];
        int len;
        Square operator *(Square b){
            Square ans;
            memset(ans.num, 0, sizeof(ans.num));
            for(int i = 1;i <= len; i++)
    			for(int j = 1; j <= len; j++)
        			for(int k = 1; k <= len; k++){
        			    ans.num[i][j] += num[i][k] * b.num[k][j];
        			    ans.num[i][j] %= mod;
        			}
            ans.len = len;
            return ans;
        }
};

int main(){
    ll n = inp();
    int m = inp() - 1;
    Square a, b;
    a.len = m + 2;
    b.len = m + 2;
    memset(a.num, 0, sizeof(a.num));
    a.num[1][m + 2] = 1;
    a.num[1][1] = 1;
    a.num[1][m + 1] = 1;
    memset(b.num, 0, sizeof(b.num));
    for(int i = 1; i <= m; i++)
        b.num[i][m + 1] = -1;
    b.num[m + 1][m + 1] = 2;
    b.num[m + 2][m + 1] = 1;
    b.num[m + 2][m + 2] = 1;
    for(int i = 2; i <= m; i++)
        b.num[i - 1][i] = 1;
    for(int i = 1; i <= m; i++)
        b.num[i][1] = -1;
    b.num[m + 2][1] = b.num[m + 1][1] = 1;
    // n -= 2;
    while(n){
        if(n & 1)
            a = a * b;
        b = b * b;
        n >>= 1;
        // printf("%lld\n", a.num[1][1]);
    }
    // printf("%lld\n", (a * (b * b) * b * b).num[1][1]);
    // for(int i = 1; i <= n; i++){
    //     printf("%lld\n", a.num[1][1]);
    //     a = a * b;
    // }
    std::cout << a.num[1][1] << std::endl;
}
```



---

