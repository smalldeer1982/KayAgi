# Sonya and Informatics

## 题目描述

克雷姆兰王国的科学高中里有一个名叫 Sonya 的女孩。她最喜欢的学科是信息学，信息学老师为她出了一道题。

给定一个长度为 $n$ 的数组 $a$，数组元素仅包含 $0$ 和 $1$，以及一个整数 $k$。接下来恰好进行 $k$ 次如下操作：

- 每次等概率地选择两个数 $i$ 和 $j$，满足 $1 \leq i < j \leq n$。
- 交换 $a$ 数组中第 $i$ 和第 $j$ 个位置的数。

Sonya 的任务是求出，所有操作完成后，数组 $a$ 恰好为非递减有序的概率。她向你寻求帮助。请你帮 Sonya 解决这个问题。

可以证明，所求概率要么为 $0$，要么可以表示为 $\dfrac{P}{Q}$，其中 $P$ 和 $Q$ 是互质的整数，且 $Q \not\equiv 0~\pmod {10^9+7}$。

## 说明/提示

在第一个样例中，经过恰好两次操作后，所有可能的最终数组为：$(0, 1, 0)$、$(0, 0, 1)$、$(1, 0, 0)$、$(1, 0, 0)$、$(0, 1, 0)$、$(0, 0, 1)$、$(0, 0, 1)$、$(1, 0, 0)$、$(0, 1, 0)$。因此，答案为 $\dfrac{3}{9}=\dfrac{1}{3}$。

在第二个样例中，经过一次操作后，数组不会变为非递减有序，因此答案为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
0 1 0
```

### 输出

```
333333336```

## 样例 #2

### 输入

```
5 1
1 1 1 0 0
```

### 输出

```
0```

## 样例 #3

### 输入

```
6 4
1 0 0 1 1 0
```

### 输出

```
968493834```

# 题解

## 作者：enucai (赞：10)

## 题意

有一个长度为 $n$ 的 $01$ 串，对其进行 $k$ 此如下操作：选择两个位置 $i,j(1\le i<j\le n)$，交换两个位置的数。问操作后该串变成非降序 $01$ 串的概率，对 $10^9+7$ 取模。数据范围 $2\le n\le 100,1\le k\le 10^9$。

## 思路

要让这个串变成非递减，即要让串中的所有 $0$ 在前，所有 $1$ 在后。我们假设 $0$ 的数量为 $m$，即最终 $a_1,a_2,\dots,a_m$ 均为 $0$，$a_{m+1},a_{m+2},\dots,a_n$ 均为 $1$。

令 $dp_{i,j}$ 表示经过 $i$ 次随机操作后，前 $m$ 个数中恰好有 $j$ 个 $0$ 的方案数。初始化 $dp_{0,x}=1$，其中 $x$ 是原序列中前 $m$ 个数里 $0$ 的个数。

对于 $dp_{i,j}$：
- 有 $(m-j)^2$ 的部分转移到了 $dp_{i+1,j+1}$。

  因为 $1$ 到 $m$ 中的 $1$ 有 $m-j$ 个，$m+1$ 到 $n$ 中的 $0$ 有 $m-j$ 个。

- 有 $j\times (n-2\times m+j)$ 的部分转移到了 $dp_{i+1,j-1}$。

  因为 $1$ 到 $m$ 中的 $0$ 有 $j$ 个，$m+1$ 到 $n$ 中的 $1$ 有 $n-2\times m+j$ 个。

- 其余部分全部转移到了 $dp_{i+1,j}$。

然而 $k$ 有 $10^9$，所以肯定是不能直接转移的。但可以将转移写成矩阵的形式：

$$
\begin{bmatrix}
C_0&B_1&0&0&\dots&0\\
A_0&C_1&B_2&0&\dots&0\\
0&A_1&C_2&B_3&\dots&0\\
0&0&A_2&C_3&\dots&0\\
0&0&0&A_3&\dots&0\\
\dots&\dots&\dots&\dots&\dots&\dots\\
0&0&0&0&\dots&C_m
\end{bmatrix}
\times
\begin{bmatrix}
dp_{i,0}\\
dp_{i,1}\\
dp_{i,2}\\
dp_{i,3}\\
dp_{i,4}\\
\dots\\
dp_{i,m}
\end{bmatrix}

=
\begin{bmatrix}
dp_{i+1,0}\\
dp_{i+1,1}\\
dp_{i+1,2}\\
dp_{i+1,3}\\
dp_{i+1,4}\\
\dots\\
dp_{i+1,m}
\end{bmatrix}
$$

其中 $A_i=(m-i)^2,B_i=i\times (n-2\times m+i),C_i=\frac{n\times (n-1)}{2}-(m-i)^2-i\times (n-2\times m+i)$。各式子的理由均已解释。

而且以上 $A,B,C$ 三个函数的定义域均为 $[0,n]$，可以直接预处理，接下来就是矩阵快速幂模板了。

复杂度：矩阵大小 $m\times m$，矩阵乘法复杂度 $m^3$，快速幂 $\log k$，最终复杂度 $O(m^3\times \log k)$。

## 代码

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1151/submission/145208714)

```cpp
#define int long long
int a[110],n,k,m=0;
int A[110],B[110],C[110];//A,B,C函数
struct matrix{
	int a[110][110];
	void init(){memset(a,0,sizeof(a));}//清空矩阵
	matrix mul(matrix x){
		matrix res;res.init();
		For(i,0,m) For(j,0,m) For(k,0,m) (res.a[i][j]+=a[i][k]*x.a[k][j]%mod)%=mod;
		return res;
	}//矩阵乘法
}base,E;
void qpow(int k){
	while(k){
		if(k%2==1) base=base.mul(E);
		k/=2;
		E=E.mul(E);
	}
}//矩阵快速幂
signed main(){
	read(n,k);
	For(i,1,n) read(a[i]);
	For(i,1,n) if(a[i]==0) m++;
	For(i,0,m){
		A[i]=(m-i)*(m-i);ckmax(A[i],0ll);A[i]%=mod;
		B[i]=i*(n-2*m+i);ckmax(B[i],0ll);B[i]%=mod;
		C[i]=n*(n-1)/2-A[i]-B[i];ckmax(C[i],0ll);C[i]%=mod;
	}//预处理A,B,C
	base.init();
	For(i,0,m) base.a[i][i]=1;
	E.init();
	E.a[0][0]=C[0],E.a[0][1]=B[1];
	For(i,1,m-1) E.a[i][i-1]=A[i-1],E.a[i][i]=C[i],E.a[i][i+1]=B[i+1];
	E.a[m][m-1]=A[m-1],E.a[m][m]=C[m];//处理用于快速幂的矩阵
	qpow(k);
	int sum=0,t=0;
	For(i,1,m) if(a[i]==0) t++;
	For(i,0,m) (sum+=base.a[i][t])%=mod;//统计合法的方案数
	write(base.a[m][t]*minv(sum)%mod);
}
```

---

## 作者：喵仔牛奶 (赞：5)

在蒟蒻的博客食用更佳：<https://www.cnblogs.com/Milkcatqwq/p/17559812.html>

# Descirption

给定一个 01 序列，每次随机交换两个不同位置的数，求交换 $k$ 次后序列排序好的概率。答案对 $10^9+7$ 取模。

对于 $100\%$ 的数据，$1\leq n\leq 100$，$1\leq k\leq 10^9$。

# Solution

定义 $\text{cnt}$ 是序列中 $0$ 的个数，发现排序好的序列是前面 $\text{cnt}$ 个 $0$，后面全是 $1$。那么把序列分成 $1\sim \text{cnt}$ 与 $\text{cnt}+1\sim n$ 两段，同段内的数位置没有用。

定义 $f_{i,j}$ 为换了 $i$ 次，前 $cnt$ 个数有 $j$ 个 $1$ 的方案数。定义 $\text{calc}(x)=\dfrac{x(x-1)}{2}$，转移如下：

1. 两端内部互换：$f_{i,j}\gets f_{i-1,j}\times(\text{calc}(\text{cnt})+\text{calc}(n-\text{cnt}))$
1. 前面的 $1$ 与后面的 $0$ 互换：$f_{i,j}\gets f_{i-1,j+1}\times(j+1)^2$
1. 前面的 $0$ 与后面的 $1$ 互换：$f_{i,j}\gets f_{i-1,j-1}\times(\text{cnt}-j+1)\times(n-\text{cnt}-j+1)$
1. 前面的 $0$ 与后面的 $0$ 互换：$f_{i,j}\gets f_{i-1,j}\times(\text{cnt}-j)\times j$
1. 前面的 $1$ 与后面的 $1$ 互换：$f_{i,j}\gets f_{i-1,j}\times j\times(n-\text{cnt}-j)$

整理一下：
$$\begin{aligned}
f_{i,j}=
&f_{i-1,j-1}\times(\text{cnt}-j+1)\times(n-\text{cnt}-j+1)+\\
&f_{i-1,j}\times(\text{calc}(\text{cnt})+\text{calc}(n-\text{cnt})+(\text{cnt}-j)\times j+j\times(n-\text{cnt}-j))+\\
&f_{i-1,j+1}\times(j+1)^2
\end{aligned}$$

然后矩阵快速幂求出 $f_{k,0}$，答案即为 $\dfrac{f_{k,0}}{\text{calc}(n)^k}$。

时间复杂度 $\mathcal{O}(n^3\log k)$。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace ModInt {
	int inverse(int a, int m) {
	    int r = 1; while (a > 1) { int t = m / a; r = 1LL * r * (m - t) % m, a = m - t * a; } return r; }
	#define MI ModInt::Mint<mod>
	template <int mod> struct Mint {
	    typedef long long LL; int x;    
	    Mint(int x = 0) : x(normal(x)) {}
	    Mint(LL x) : x(normal(x % mod)) {}
	    int normal(int x) { if (x >= mod) x -= mod; if (x < 0) x += mod; return x; }
	    int val() const { return x; }
	    Mint inv() const { assert(x != 0); return Mint(inverse(x, mod)); }
	    Mint operator - () const { return Mint(mod - x); }
	    Mint operator += (const Mint &rhs) { x = normal(x + rhs.x); return *this; }
	    Mint operator -= (const Mint &rhs) { x = normal(x - rhs.x); return *this; }
	    Mint operator *= (const Mint &rhs) { x = 1LL * x * rhs.x % mod; return *this; }
	    Mint operator /= (const Mint &rhs) { return *this *= rhs.inv(); }
	    friend Mint operator + (const Mint &lhs, const Mint &rhs) { Mint res = lhs; res += rhs; return res; }
	    friend Mint operator - (const Mint &lhs, const Mint &rhs) { Mint res = lhs; res -= rhs; return res; }
	    friend Mint operator * (const Mint &lhs, const Mint &rhs) { Mint res = lhs; res *= rhs; return res; }
	    friend Mint operator / (const Mint &lhs, const Mint &rhs) { Mint res = lhs; res /= rhs; return res; }
	    friend istream &operator >> (istream &is, Mint &a) { LL v; is >> v; a = Mint(v); return is; }
	    friend ostream &operator << (ostream &os, const Mint &a) { return os << a.x; }
	};
}
namespace Milkcat {
    typedef long long LL;
    const int N = 105, K = 1e5 + 5, mod = 1e9 + 7;
    LL n, k, qwq, cnt, a[N];
    struct matrix {
	    MI a[N][N];
	    matrix() { memset(a, 0, sizeof a); } 
	    matrix operator * (const matrix& x) const {
	        matrix c;
	        for (int i = 0; i <= cnt; i ++)
	            for (int k = 0; k <= cnt; k ++)
	                for (int j = 0; j <= cnt; j ++)
	                    c.a[i][j] += a[i][k] * x.a[k][j];
	        return c;
	    }
	} bas, mat;
	MI qpow(MI b, LL k) { MI r = 1; for (; k; b *= b, k >>= 1) if (k & 1) r *= b; return r; }
	matrix qpow(matrix b, LL k) { matrix r = b; k --; for (; k; b = b * b, k >>= 1) if (k & 1) r = r * b; return r; }
	MI calc(MI x) { return x * (x - 1) / 2; }
    int main() {
		cin >> n >> k;
		for (int i = 1; i <= n; i ++)
			cin >> a[i], cnt += !a[i];
		for (int i = 1; i <= cnt; i ++) qwq += a[i];
		mat.a[qwq][0] = 1;
		for (int i = 0; i <= cnt; i ++) {
			bas.a[i][i] = calc(cnt) + calc(n - cnt) + (cnt - i) * i + i * (n - cnt - i);
			if (i > 0) bas.a[i][i - 1] = (cnt - i + 1) * (n - cnt - i + 1);
			if (i < cnt) bas.a[i][i + 1] = (i + 1) * (i + 1);
		}
		cout << (qpow(bas, k) * mat).a[0][0] / qpow(calc(n), k) << '\n';
        return 0;
    }
}
int main() {
	freopen("randsort.in", "r", stdin);
	freopen("randsort.out", "w", stdout);
    int T = 1;
    while (T --) Milkcat::main();
    return 0;
}

/*
010->001->001
010->010->001
010->100->001
*/
```

---

## 作者：orz_z (赞：3)

 给一个长度为 $n (n\leq 100)$ 的 $0/1$ 串，进行 $k (k \leq 10^9)$ 次操作，每次操作选择两个位置 $i,j (1 \leq i < j \leq n)$，交换 $i,j$ 上的数，求 $k$ 次操作后，该 $0/1$ 串变成非降序列的概率，答案对 $10^9+7$ 取模。

### sol

好题，概率 `dp`。

设有 $m$ 个 $0$，那么题意就是让 $a[1,m]$ 均为 $0$，$a[m+1,n]$ 均为 $1$。

令 $f_{i,j}$ 表示 $i$ 个操作后，前 $m$ 个数中有 $j$ 个 $0$ 的方案数，答案即为 $\frac{f_{k,m}}{\sum\limits_{i=0}^{m}f_{k,i}}$，边界：$f_{0,p}=1$，$p$ 为原序列前 $m$ 个数中 $0$ 的个数。

对于 $f_{i,j}$，考虑它是如何转移来的：

* 之前有 $j-1$ 个 $0$，第 $i$ 次交换换来一个 $0$，由于前面 $1$ 的个数与后面 $0$ 的个数均为 $m-j+1$，顾方案数为 $f_{i-1,j-1}\times (m-j+1)^2$。
* 之前有 $j + 1$ 个 $0$，第 $i$ 次交换换走一个 $0$，由于前面有 $j+1$ 个 $0$，后面有 $n-m-(m-j-1)=n-2m+j+1$ 个 $1$，顾方案数为 $f_{i-1,j+1}\times (j+1)(n-2m+j+1)$。
* 之前本来就有 $j$ 个 $0$，第 $i$ 次操作没换走也没换来，四种情况：前面交换，后面交换，前后交换 $0$，前后交换 $1$，则方案数为 $C_{m}^{2}+C_{n-m}^{2}+j(m-j)+(m-j)(n-2m+j)$。

到这里差点结束了，总结：$f_{i,j}=f_{i-1,j-1}\times (m-j+1)^2+f_{i-1,j+1}\times (j+1)(n-2m+j+1)+C_{m}^{2}+C_{n-m}^{2}+j(m-j)+(m-j)(n-2m+j)$。

考虑到 $k\leq 10^9$，经验告诉我们直接上矩阵快速幂，毕竟这转移无需判断。
$$
\begin{bmatrix}c_0& b_1& 0 & 0&\cdots & 0\\
a_0 & c_1 & b_2 & 0&\cdots & 0\\
0 & a_1 & c_2 & b_3 & \cdots & 0\\
0&0&a_2&c_3&\cdots&0\\
0&0&0&a_3&\cdots&0\\
\cdots&\cdots&\cdots&\cdots&\cdots&\cdots\\
0&0&0&0&\cdots&c_m\end{bmatrix} \times \begin{bmatrix}f_{i-1,0}\\f_{i-1,1}\\f_{i-1,2}\\f_{i-1,3}\\f_{i-1,4}\\ \cdots \\f_{i-1,m}\end{bmatrix}=\begin{bmatrix}f_{i,0}\\f_{i,1}\\f_{i,2}\\f_{i,3}\\f_{i,4}\\ \cdots \\f_{i,m}\end{bmatrix}
$$
其中 $a_i=(m-i)^2$，$b_i=i(n-2m+i)$，$c_i=C_{m}^{2}+C_{n-m}^{2}+i(m-i)+(m-i)(n-2m+i)$。

时间复杂度 $\mathcal O(n^3\log k)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

const int _ = 107, p = 1e9 + 7;

int n, k, m, t, Ans, A[_], a[_], b[_], c[_];

struct matrix {
	int a[_][_];
	void init() {
		memset(a, 0, sizeof a);
	}
	matrix mul(matrix x) {
		matrix res;
		res.init();
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= m; ++j)
				for (int k = 0; k <= m; ++k)
					res.a[i][j] = (res.a[i][j] + a[i][k] * x.a[k][j] % p) % p;
		return res;
	}
} ans, base;

void Qpow(int k) {
	while (k) {
		if (k & 1)
			ans = ans.mul(base);
		k >>= 1, base = base.mul(base);
	}
}

inline int qpow(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1)
			res = res * x % p;
		y >>= 1, x = x * x % p;
	}
	return res;
}

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; ++i) A[i] = read();
	for (int i = 1; i <= n; ++i) m += (A[i] == 0);
	for (int i = 1; i <= m; ++i) t += (A[i] == 0);
	for (int i = 0; i <= m; ++i) {
		a[i] = (m - i) * (m - i) % p;
		b[i] = i * (n - 2 * m + i) % p;
		c[i] = (m * (m - 1) * qpow(2, p - 2) % p + (n - m) * (n - m - 1) * qpow(2, p - 2) % p + (m - i) * (n - 2 * m + 2 * i) % p) % p;
	}
	ans.init();
	for (int i = 0; i <= m; ++i) ans.a[i][i] = 1;
	base.init();
	base.a[0][0] = c[0], base.a[0][1] = b[1];
	base.a[m][m - 1] = a[m - 1], base.a[m][m] = c[m];
	for (int i = 1; i <= m - 1; ++i) {
		base.a[i][i - 1] = a[i - 1];
		base.a[i][i] = c[i];
		base.a[i][i + 1] = b[i + 1];
	}
	Qpow(k);
	base.init();
	base.a[t][0] = 1;
	ans = ans.mul(base);
	for (int i = 0; i <= m; ++i)
		Ans = (Ans + ans.a[i][0]) % p;
	printf("%lld", ans.a[m][0] * qpow(Ans, p - 2) % p);
	return 0;
}
```



---

## 作者：云浅知处 (赞：3)


非降序列就是让 $0$ 都在前面，$1$ 都在后面。设 $0$ 的数量为 $m$。

考虑设 $F(i,j)$ 为前 $i$ 次交换后，前 $m$ 个数中有 $j$ 个 $0$ 的方案数。

考虑这 $j$ 个 $0$ 是怎么来的：

- 有可能之前只有 $j-1$ 个 $0$，第 $i$ 次交换将后面的一个 $0$ 和前面的一个 $1$ 交换了。注意到前面 $1$ 的个数和后面 $0$ 的个数都是 $m-j+1$，因此方案数为 $F(i-1,j-1)\cdot (m-j+1)^2$。
- 有可能本来有 $j+1$ 个 $0$，第 $i$ 次换走了一个。前面有 $j+1$ 个 $0$，后面有 $n-2m-(m-j-1)=n-2m+j+1$ 个 $1$，因此方案数为 $F(i-1,j+1)\cdot(j+1)(n-2m+j+1)$。
- 有可能本来就有 $j$ 个 $0$，第 $i$ 次交换并没有什么用。分四种情况讨论：交换了两个前面的，交换了两个后面的，交换了前后的两个 $1$，交换了前后的两个 $0$。那么方案数就是 $C_m^2+C_{n-m}^2+j(m-j)+(m-j)(n-2m+j)$

然而 $k\le 10^9$，并不能直接这么转移。

见过了矩阵快速幂优化 dp 的套路之后，再看到 $10^9$ 的范围，很容易想到把这个转移写成矩阵。

$F(i,j)$ 和 $F(i-1,j-1/j/j+1)$ 有关，那么只需要在矩阵的这三项中填上对应的系数，其余都填 $0$ 即可。

时间复杂度 $O(n^3\log k)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=105;
const int mod=1e9+7;
int n,m,k;
int p[MN];

struct Mat{
	int a[MN][MN];

	Mat(){
		memset(a,0,sizeof(a));
	}

	inline Mat operator*(const Mat &rhs)const{
		Mat res;
		for(int i=0;i<=m;i++){
			for(int j=0;j<=m;j++){
				for(int k=0;k<=m;k++)res.a[i][j]=(res.a[i][j]+a[i][k]*rhs.a[k][j]%mod)%mod;
			}
		}
		return res;
	}
}f,z;

int ksm(int x,int y,int p=mod){
	int res=1;
	for(int i=y;i;i>>=1,x=x*x%p)if(i&1)res=res*x%p;
	return res;
}

int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}

signed main(void){

	n=read(),k=read();int cnt=0;
	for(int i=1;i<=n;i++)p[i]=read(),m+=(p[i]==0);
	for(int i=1;i<=m;i++)cnt+=(p[i]==0);
	f.a[cnt][0]=1;

	for(int i=0;i<=m;i++){
		if(i-1>=0)z.a[i][i-1]=(m-i+1)*(m-i+1)%mod;
		if(i+1<=m)z.a[i][i+1]=(i+1)*(n-2*m+i+1+mod)%mod;
		z.a[i][i]=max(0ll,n*(n-1)%mod*inv(2)%mod-(m-i)*(m-i)%mod-i*(n-2*m+i+mod)%mod+mod)%mod;
	}

	for(int i=k;i;i>>=1,z=z*z)if(i&1)f=z*f;
	cout<<f.a[m][0]*inv(ksm(n*(n-1)%mod*inv(2)%mod,k))%mod<<endl;

	return 0;
}
```

---

## 作者：Rhodoks (赞：3)

我们称$a_1-a_m$这一区间为前半区，$a_{m+1}-a_{n}$为后半区。

$DP_i[x]$代表随机交换i次后，数列中前半区中有$x$个$0$的方案数。

初始$DP_0[t]=1$，其余为$0$。$t$是初始状态前半区的$0$个数。

转移：


对$DP_i[x]$状态，此时前$m$个数中有$x$个$0$和$(m-x)$个$1$，后$(n-m)$个数中有$(m-x)$个$0$和$(n-2m+x)$个$1$


从$n$个数中任选两个进行交换，那么

有$f_{+1}[x]=C_{m-x}^1*C_{m-x}^1=(m-x)^2$种方案，选到了前半区的$1$和后半区的$0$，$x$变成了$x+1$。


同时，有$f_{-1}[x]=C_x^1*C_{n-2m+x}^1=x*(n-2m+x)$种方案，选到了前半区的$0$和后半区的$1$，$x$变成了$x-1$。

对于其他$f_{0}[x]=C_n^2-(m-x)^2-x*(n-2m+x)$种情况，不会改变$dp$的状态。

写成矩阵形式的状态转移方程（$latex$矩阵炸掉了，换成矩阵再上传一波）


![](https://cdn.luogu.com.cn/upload/pic/57624.png)
$$M \times DP_i=DP_{i+1} (0<=i<n)$$

最终结果$ans=DP_k[m]/\sum_{i=0}^n DP_k[i]=M^k[m][t]/\sum_{i=0}^{m}m^k[i][t]$

$k$很大，所以要用矩阵快速幂。

复杂度$\mathcal{O}(n^3logk)$


代码：
```cpp
#include <bits/stdc++.h>
#define INL inline
#define REG register
#define DB double
#define LDB long double
#define ULL unsigned long long
#define LL long long

#define RPT(i,x,y) for (REG int i=x;i<y;i++)
#define DRPT(i,x,y) for (REG int i=x;i>y;i--)
#define MST(a,b) memset(a,b,sizeof(a))
#define MRK() cout<<"Mark"<<endl;
#define WRT(x) cout<<#x<<" = "<<x<<endl;

#define MAXN 10000
#define MAXM 10000
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define EPS 1e-5

#define _ 0
using namespace std;

//自己瞎写的矩阵板子
struct MATRIX
{
	LL row,col;
	LL data[101][101];
	
	MATRIX(int n,int m)
	{
		row=n;
		col=m;
		RPT(i,0,n)
			RPT(j,0,n)
				data[i][j]=0;
	}
	
	MATRIX(const MATRIX &m)
	{
		*this=m; 
	}
	
	~MATRIX()
	{
	}
	
	void input()
	{
		RPT(i,0,row)
			RPT(j,0,col)
				scanf("%d",&data[i][j]);
	}
	
	void output()
	{
		if (!islegal())
		{
			cout<<"illegal matrix!"<<endl;
			return;
		}
		RPT(i,0,row)
		{
			RPT(j,0,col)
				printf("%d ",data[i][j]);
			printf("\n");
		}
	}
	
	bool islegal()
	{
		if (col<=0 || row<=0)
			return false;
		return true;
	}
	
	MATRIX operator - ()
	{
		if (!this->islegal())
		{
			MATRIX fault(-1,-1);
			return fault;
		}
		MATRIX ans(row,col);
		RPT(i,0,row)
			RPT(j,0,col)
				ans.data[i][j]=((-this->data[i][j])%MOD+MOD)%MOD;
		return ans;
	}
	
	MATRIX operator + (MATRIX m)
	{
		if (this->col!=m.col || this->row!=m.col || !this->islegal() || !m.islegal())
		{
			MATRIX fault(-1,-1);
			return fault;
		}
		MATRIX ans(*this);
		RPT(i,0,row)
			RPT(j,0,col)
				ans.data[i][j]=(ans.data[i][j]+m.data[i][j])%MOD;
		return ans;
	}
	
	MATRIX operator - (MATRIX m)
	{
		if (this->col!=m.col || this->row!=m.col || !this->islegal() || !m.islegal())
		{
			MATRIX fault(-1,-1);
			return fault;
		}
		MATRIX ans(*this);
		RPT(i,0,row)
			RPT(j,0,col)
				ans.data[i][j]=((ans.data[i][j]-m.data[i][j])%MOD+MOD)%MOD;
		return ans;
	}
	
	
	MATRIX operator * (MATRIX m)
	{
		if (this->col!=m.row || !this->islegal() || !m.islegal())
		{
			MATRIX fault(-1,-1);
			return fault;
		}
		MATRIX ans(this->row,m.col);
		RPT(i,0,ans.row)
			RPT(j,0,ans.col)
				RPT(k,0,this->col)
					ans.data[i][j]=(ans.data[i][j]+this->data[i][k]*m.data[k][j])%MOD;
		return ans;
	}
};

LL n,m,k,t;

LL f1(LL x)
{
	return (x*(n-2*m+x)%MOD+MOD)%MOD;
}

LL f3(LL x)
{
	return ((m-x)*(m-x)%MOD+MOD)%MOD;
}

LL f2(LL x)
{
	return ((n*(n-1)/2-f1(x)-f3(x))%MOD+MOD)%MOD;
}


LL fastpow(LL x,LL n)
{
	LL ans=1;
	while (n)
	{
		if (n&1)
			ans=ans*x%MOD;
		x=x*x%MOD;
		n/=2;
	}
	return ans;
}

int main()
{
	LL x;
	LL a[MAXN];
	cin>>n>>k;
	RPT(i,1,n+1)
	{
		cin>>a[i];
		if (a[i]==0)
			m++;
	}
	RPT(i,1,m+1)
		if (a[i]==0)
			t++;
	static MATRIX ma(m+1,m+1);
	RPT(i,0,m+1)
	{
		if (i!=0)
			ma.data[i-1][i]=f1(i);
		ma.data[i][i]=f2(i);
		if (i!=m)
			ma.data[i+1][i]=f3(i);
	}
	MATRIX ans(m+1,m+1);
	RPT(i,0,m+1)
		ans.data[i][i]=1;
	while (k)
	{
		if (k&1)
			ans=ans*ma;
		ma=ma*ma;
		k/=2;
	}
	LL tem=0;
	RPT(i,0,m+1)
		tem=(tem+ans.data[i][t])%MOD;
	cout<<ans.data[m][t]*fastpow(tem,MOD-2)%MOD;
	return ~~(0^_^0);
}

```


---

## 作者：zhengjinyi (赞：2)

### Solution
看到 $n\le100,k\le10^9$，容易想到矩阵快速幂。关键在于如何设计状态和矩阵转移。\
设串中有 $m$ 个 $1$，一个单调不减的 $0/1$ 串显然形如前 $n-m$ 个为 $0$，后 $m$ 个为 $1$。发现每次操作都随机选择数对交换，因此一个局面能交换为上述局面的概率不与每个 $1$ 的位置有关，**仅与其在最后 $m$ 位的 $1$ 个数有关**。\
于是可以设 $f_i$ 表示当前最后 $m$ 位（以下称为右侧，其他为左侧）有 $i$ 个 $1$ 的概率，考虑转移：
1. $f_i\to f_{i-1}$。一个右侧的 $1$ 与左侧的 $0$ 交换，方案数为 $i\times(n-m-(m-i))$。
2. $f_i\to f_{i+1}$。一个右侧的 $0$ 与左侧的 $1$ 交换，方案数为 $(m-i)\times(m-i)$。
3. $f_i\to f_i$。用 $1$ 减去上面两种情况概率。

方案数除去 $n(n-1)/2$，就是此种转移的概率。\
于是可以设计出矩阵，跑一遍矩阵快速幂即可。
### Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define R read()
using namespace std;
inline int read(){
	int x=0;char c=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}
const int inf=0x3f3f3f3f,N=105;
const ll INF=0x3f3f3f3f3f3f3f3f,M=1000000007;
int n,m,k,a[N],cnt;
struct matrix{
	ll s[N][N];
	friend matrix operator* (matrix x,matrix y){
		matrix z;
		for(int i=0;i<=m;i++){
			for(int j=0;j<=m;j++){
				z.s[i][j]=0;
				for(int k=0;k<=m;k++)
					z.s[i][j]+=x.s[i][k]*y.s[k][j],z.s[i][j]%=M;
			}
		}
		return z;
	}
}A,B,E;
ll power(ll x,int y){
	ll res=1;
	while(y){
		if(y&1) res*=x,res%=M;
		x*=x,x%=M,y>>=1;
	}
	return res;
}
matrix power(matrix x,int y){
	matrix res=E;
	while(y){
		if(y&1) res=res*x;
		x=x*x,y>>=1;
	}
	return res;
}
ll qwq;
int main(){
	n=R,k=R;
	for(int i=1;i<=n;i++) a[i]=R,m+=a[i];
	for(int i=n-m+1;i<=n;i++) cnt+=a[i];
	for(int i=0;i<=m;i++) E.s[i][i]=1;
	qwq=power(n*(n-1)>>1,M-2);
	for(int i=0;i<=m;i++){
		ll sum=3*M+1;
		if(i){
			B.s[i][i-1]=i*(n-m-m+i)%M*qwq%M;
			sum-=B.s[i][i-1];
		}
		if(i<m){
			B.s[i][i+1]=(m-i)*(m-i)%M*qwq%M;
			sum-=B.s[i][i+1];
		}
		B.s[i][i]=sum%M;
	}
	A.s[0][cnt]=1;
	A=A*power(B,k);
	printf("%lld\n",A.s[0][m]);
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

设序列里有 $c$ 个 $1$。

观察到一个非降序列一定由 $n-c$ 个 $0$ 再加上 $c$ 个 $1$ 组合而成，于是我们只需要注意最后 $c$ 位 $1$ 的情况

考虑令 $dp_{i,j}$ 为在第 $i$ 次交换后最后 $c$ 位中有 $j$ 个 $1$ 的概率。考虑刷表，则转移有以下几种

1.前 $0$ 换后 $1$ ，有

$$\frac{(n-2c-j)j}{n(n-1)/2}dp_{i,j} \rightarrow dp_{i+1,j-1}$$

2.前 $1$ 换后 $0$ ，有

$$\frac{(c-j)(c-j)}{n(n-1)/2}dp_{i,j} \rightarrow dp_{i+1,j+1}$$

3.其他类型交换：

$$(1-\frac{(c-j)(c-j)+(n-2c-j)j}{n(n-1)/2})dp_{i,j} \rightarrow dp_{i+1,j}$$

滚动掉第一维后使用矩阵快速幂优化即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int mod=1e9+7;

int Mod(int x){
	while(x<0){
		x+=mod;
	}
	if(x>=mod){
		x%=mod;
	}
	return x;
}

int n,k;
const int maxn=100;

struct matrix{
	int a[105][105];
	
	matrix(){
		memset(a,0,sizeof(a));
	}
};

matrix operator * (matrix a,matrix b){
	matrix ans;
	for(int i=0;i<=k;i++){
		for(int _k=0;_k<=k;_k++){
			for(int j=0;j<=k;j++){
				ans.a[i][j]=Mod(ans.a[i][j]+Mod(a.a[i][_k]*b.a[_k][j]));
			}
		}
	}
	return ans;
}

int ksm(int a,int b){
	int ans=a;
	b--;
	while(b){
		if(b&1){
			ans=Mod(ans*a);
		}
		a=Mod(a*a);
		b>>=1;
	}
	return ans;
}

matrix ksm(matrix a,int b){
	matrix ans=a;
	b--;
	while(b){
		if(b&1){
			ans=ans*a;
		}
		a=a*a;
		b>>=1;
	}
	return ans;
}

int a[maxn+5];
int t;
matrix init;

signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		k+=a[i];
	}
	int cnt=0;
	for(int i=n-k+1;i<=n;i++){
		if(a[i]){
			cnt++;
		}
	}
	int fenmu=ksm(Mod(n*(n-1)/2),mod-2);
	for(int i=0;i<=k;i++){
		int s1=0,s2=0;
		if(i!=0){
			init.a[i-1][i]=s1=Mod(Mod((n-2*k+i)*i)*fenmu);
		}
		if(i!=k){
			init.a[i+1][i]=s2=Mod(Mod((k-i)*(k-i))*fenmu);
		}
		init.a[i][i]=Mod(1-s1-s2);
	}
	init=ksm(init,t);
	cout<<init.a[k][cnt];
}
```cpp

---

## 作者：MerlinLee (赞：0)

大家思路其实是不是都差不多啊？

首先令 $c$ 为序列中 $0$ 的个数，那么排序后序列肯定是前面 $c$ 个 $0$，后面 $n-c$ 个 $1$。

那么就能上 DP 了。（居然卡在这里……）

$f[i][j]$ 表示经过 $i$ 次操作后，前 $c$ 个数中有 $j$ 个 $0$ 的方案数。答案就是 $\dfrac{f[k][c]}{\sum f[k][i]}$。

这个状态的好处就是可以直接求出以下这些值：

前 $c$ 个数中 $1$ 的个数为 $c-j$
后 $c$ 个数中 $0$ 的个数为 $c-j$
后 $c$ 个数中 $1$ 的个数为 $n-2c+j$（所以 $j\ge 2c-n$）
初始状态：令初始序列前 $c$ 个数中 $0$ 的个数为 $cnt$，那么 $f[0][cnt]=1$，其它的 $f[0][i]=0$ 就行。

转移：


括号中第一个是前 $c$ 个中交换，第二个是后 $n-c$ 个中交换，第三个是前面的 $0$ 和后面的 $0$ 交换，第四个是前面的 $1$ 和后面的 $1$ 交换。


前 $c$ 个中的 $0$ 和后 $n-c$ 个中的 $1$ 交换。


前 $c$ 个中的 $1$ 和后 $n-c$ 个中的 $0$ 交换。

然后发现第 $i$ 层之和第 $i-1$ 层有关，那么可以矩阵快速幂。

时间复杂度 $O(n^3\log k)$ 这个样子。

代码：


```cpp
#include<bits/stdc++.h>
#define inl inline
using namespace std;
const int Maxn=101;
const int mod=1e9+7;
int n,k,a[Maxn],c,cnt;
inl int add(int a,int b)
{
	return a+b<mod?a+b:a+b-mod;
}
inl int sub(int a,int b)
{
	return a<b?a-b+mod:a-b;
}
inl int mul(int a,int b)
{
	return 1ll*a*b%mod;
}
inl int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=mul(a,a))
	  if(b&1)
	    ans=mul(ans,a);
}
struct matrix
{
    int a[maxn][maxn];
    matrix(){MEM(a,0);}
    matrix operator*(const matrix &t)const
	{
        matrix ans;
        for(int i=0;i<=c;i++) 
		  for(int k=0;k<=c;k++)
		    for(int j=0;j<=c;j++)
			  ans.a[i][j]=add(ans.a[i][j],mul(a[i][k],t.a[k][j]));
        return ans;
    }
}beg,fac,ans;
matrix qpow(matrix a,int b)
{
    matrix ans;
    for(int i=0;i<=c;i++) 
	  ans.a[i][i]=1;
    for(;b;b>>=1,a=a*a)
	  if(b&1)
	    ans=ans*a;
    return ans;
}
int main()
{
	
	n=read(),k=read();
	for(int i=1;i<=n;i++)
	  a[i]=read(),c+=!a[i];
	for(int i=1;i<=c;i++)
	  cnt+=!a[i];
	beg.a[cnt][0]=1;
	for(int i=0;i<=c;i++)
	{
		fac.a[i][i]=(1ll*c*(c-1)/2+1ll*(n-c)*(n-c-1)/2+1ll*i*(c-i))%mod;
        if(i>=2*c-n)
		  fac.a[i][i]=add(fac.a[i][i],mul(c-i,n-2*c+i));
        if(i)
		  fac.a[i][i-1]=mul(c-i+1,c-i+1);
        if(i!=c and i+1>=2*c-n)
		  fac.a[i][i+1]=mul(i+1,n-2*c+i+1);
	}
	ans=qpow(fac,k)*beg;
	int s=0;
	for(int i=0;i<=c;i++)
	  s=add(s,ans.a[i][0]);
	s=mul(qpow(s,mod-2),ans.a[c][0]);
	printf("%d\n",s);
	return 0;
}
```

---

## 作者：masonpop (赞：0)

独立做出的 *2300，记之。

首先假设序列中有 $k$ 个 $0$。然后可以设 $f_{i,j}$ 表示经过 $i$ 次操作后前 $k$ 个位置有 $j$ 个 $1$ 的概率。转移：

① 把之前的一个 $1$ 换成 $0$，转移到 $f_{i+1,j-1}$。

② 把一个 $0$ 换成 $1$，转移到 $f_{i+1,j+1}$。

③ 同值交换，转移到 $f_{i+1,j}$。

然后发现操作数很大没法直接做，直接矩阵加速。总复杂度 $O(n^3\log k)$。[代码](https://www.luogu.com.cn/paste/3n7nlboc)。

---

## 作者：kkio (赞：0)

# CF1151F #

因为这个串里只有 $ 0 $ 和 $ 1 $，所以必须要将 $ 0 $ 全部放前面，$ 1 $ 全部放后面。假设有 $ m $ 个 $ 0 $。

然后我们就可以设 $ f_{i,j} $ 表示现在在第 $ i $ 步操作，数组里已经有了 $ j $ 个 $ 0 $ 在第 $ m $ 个位置及之前的方案数。有转移：

1. $ f_{i,j} \times (m-j)^2 \rightarrow f_{i+1,j+1} $
2. $ f_{i,j} \times (n-m-m+j) \times j \rightarrow f_{i+1,j-1}$

剩余情况均转移到 $ f_{i+1,j} $ 中。

然后就发现 $n$ 很小，$ k $ 很大，并且可以矩阵优化，构造转移矩阵就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=105,mod=1e9+7;
int ksm(int b,int p){int ret=1;while(p){if(p&1)ret=1ll*ret*b%mod;b=1ll*b*b%mod;p>>=1;}return ret;}
int n,m,k;
struct matrix
{
	int a[maxn][maxn];
	matrix(int x=0){memset(a,0,sizeof a);for(int i=0;i<=m;i++)a[i][i]=x;}
}t,f;
matrix mul(matrix a,matrix b)
{
	matrix ret;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=m;k++)
				ret.a[i][j]=(ret.a[i][j]+1ll*a.a[i][k]*b.a[k][j]%mod)%mod;
	return ret;
}
int a[maxn],b[maxn],c[maxn],inv,r;
char s[maxn];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=1;i<=n;i++)
		if(s[i]=='0')m++;
	for(int i=1;i<=m;i++)
		if(s[i]=='0')r++;
	//printf("%d\n",m);
	inv=n*(n-1)/2;
	//printf("%d\n",inv);
	for(int i=0;i<=m;i++)
		a[i]=1ll*(m-i)*(m-i),a[i]%=mod;
	for(int i=1;i<=m;i++)
		b[i]=1ll*i*(n-2*m+i),b[i]%=mod;
	for(int i=0;i<=m;i++)
		c[i]=1ll*(inv-a[i]-b[i]),c[i]%=mod;
	for(int i=0;i<=m;i++)
	{
		if(i>0)f.a[i-1][i]=a[i-1];
		if(i<m)f.a[i+1][i]=b[i+1];
		f.a[i][i]=c[i];
	}
	matrix ans(1);
	while(k){if(k&1)ans=mul(ans,f);f=mul(f,f);k>>=1;}
	int sum=0;
	for(int i=0;i<=m;i++)
		sum=(sum+ans.a[r][i])%mod;
	sum=1ll*ans.a[r][m]*ksm(sum,mod-2)%mod;
	printf("%d\n",sum);
}
```


---

