# sequence

## 题目背景

Wolfycz很喜欢数列（雾

## 题目描述

Wolfycz非常喜欢研究数列，同时他也喜欢研究黄金分割率，有一天Wolfycz写下了一个数列，他令$A_i=\lceil(\dfrac{\sqrt{5}+1}{2})^i\rceil$，但是Wolfycz并不知道$A_n$的值，所以希望你来帮帮他

注：请注意常数因子对程序运行效率的影响

## 说明/提示

对于$5\%$的数据，$n\leqslant 20$

对于$40\%$的数据，$T\leqslant 5×10^4$

对于$100\%$的数据，$T\leqslant 10^5,n\leqslant 10^{18}$

## 样例 #1

### 输入

```
5
1
9
20
50
100```

### 输出

```
2
77
15127
192911239
996781931```

# 题解

## 作者：Transfixion_ (赞：13)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P5136)
## $\textbf{Update}$

- 2022.10.24 被 @lingfunny Hack 了。

- 2023.3.1 修改并重写题解 & 代码。

## $\textbf{Description}$
已知 $1\le n\le 10^{18}$，试求出
$$\left\lceil{\left(\dfrac{\sqrt 5 + 1}{2} \right)}^n\right\rceil$$

## $\textbf{Solution}$
显然这是一个斐波那契数列。

考虑其共轭：设 $ x = \dfrac{\sqrt 5 + 1}{2}, y = \dfrac{1 - \sqrt 5}{2}$。

由共轭的性质，$x+y=1,xy=-1$。

那么一个思路是构造数列 $F_n = x^n + y^n$。 

$\begin{aligned}F_n&=(x+y)(x^{n-1}+y^{n-1})-xy(x^{n-2}+y^{n-2})\\&=(x+y)F_{n-1}-xy\times F_{n-2}\\&=F_{n-1}+F_{n-2}.\end{aligned}$

也就是 $F_n=F_{n-1}+F_{n-2}$，即证。

我们需要通过 $\begin{bmatrix}F_{n-1} & F_{n-2}\end{bmatrix}$ 推得 $\begin{bmatrix}F_{n} & F_{n-1}\end{bmatrix}$。

手推一下得到 $\begin{bmatrix}F_{n-1} & F_{n-2}\end{bmatrix} \times \begin{bmatrix}1&1\\1&0\end{bmatrix} = \begin{bmatrix}F_{n} & F_{n-1}\end{bmatrix}$。

$F_n$ 的问题已经解决，考虑 $A_n$。

由于 $A_n=\lceil F_n-y^n\rceil$，我们需要讨论 $y^n$ 的范围。

注意到 $y \in (-1, 0)$，于是：

- $n$ 为奇数时，$y^n\in(-1,0)\Rightarrow A_n =  F_n+1$；

- $n$ 为偶数时，$y^n\in(0,1)\Rightarrow A_n =  F_n$。

## $\textbf{Extra}$

- 注意取模 & 溢出问题；
- 特判 $n=0$ 和 $n=1$ 的情况；
- 注意 $F_1=1,F_2=3$。

## $\textbf{AC Code}$
```cpp
#include <bits/stdc++.h>
#define int long long
const int p = 998244353;
int T, n;

struct Matrix {
    int a[2][2];
    Matrix() {memset(a, 0, sizeof(a));}
    Matrix operator * (const Matrix &mat) {
	    Matrix res;
	    for(int i = 0; i < 2; i++) {
		    for(int k = 0; k < 2; k++) {
				for(int j = 0; j < 2; j++) {
				    res.a[i][j] += a[i][k] * mat.a[k][j];
				    res.a[i][j] %= p;
				}
			}
		} return res;
	}
}ans, base;

inline void init() {
	base.a[0][0] = 1, base.a[0][1] = 1;
	base.a[1][0] = 1, base.a[1][1] = 0;
	ans.a[0][0] = 3, ans.a[0][1] = 1;
	ans.a[1][0] = 0, ans.a[1][1] = 0;
}

inline int solve(int b) {
	init();
	int f = (b -= 2) & 1;
	while(b) {
		if(b & 1) ans = ans * base;
		base = base * base, b >>= 1;
	} return (ans.a[0][0] + f) % p;
	// Hack:注意先加再取模
}

signed main() {
	std::cin >> T;
	while(T--) {
		std::cin >> n;
		if(n == 0) {puts("1"); continue;}
		if(n == 1) {puts("2"); continue;}
		std::cout << solve(n) << std::endl;
	}
    return 0;
}
```

---

## 作者：Dumby_cat (赞：8)

## 题目描述

~~试~~求出：

$$\left \lceil \left ( \frac{1+\sqrt{5}}{2}  \right )^{n}  \right \rceil \bmod 998244353$$

多测

## 题解报告

有一道本题的进阶版：[洛谷 P3263 有意义的字符串](https://www.luogu.com.cn/problem/P3263)。

看楼下大佬们都是找规律推递推式，我来一个略有不同的解法（不一样的递推式，主体都为矩乘）。

先不考虑向上取整和取模运算。首先需要将根号去掉，否则会有小数。

可以想到在原式后加上一个 $\left ( \frac{1-\sqrt{5}}{2}  \right )^{n}$，使式子变为：

$$ \left ( \frac{1+\sqrt{5}}{2}  \right )^{n} + \left ( \frac{1-\sqrt{5}}{2}  \right )^{n} $$

此时便可以将根号消掉。（注意最后需要减去一个 $\left ( \frac{1-\sqrt{5}}{2}  \right )^{n}$）

我们设 $x= \left ( \frac{1+\sqrt{5}}{2}  \right )$，$y=\left ( \frac{1-\sqrt{5}}{2}  \right )$。

再设 $f_{n}=x^{n}+y^{n}$。

稍微考虑一下便可得到：

$$x^{n}+y^{n}=\left ( x+y \right ) \left ( x^{n-1}+y^{n-1} \right ) -xy \times \left ( x^{n-2}+y^{n-2} \right )$$

$$f_{n}=\left ( x+y \right )f_{n-1}-xy \times f_{n-2} $$

这个就是我们的递推式啦。

其中有些东西可以直接算出来：$x+y=1$，$xy=-1$，$f_{1}=1$，$f_{2}=3$。

于是乎我们的矩阵就~~很容易~~地得出来了：

需要由 $\begin{bmatrix} f_{n-1} &f_{n-2}\end{bmatrix}$ 推得 $\begin{bmatrix} f_{n} &f_{n-1}\end{bmatrix}$。

转移矩阵如下：

$$\begin{bmatrix} 1 &1 \\ 1 &0\end{bmatrix}$$

最后再来看看减去的那个式子对最终答案的影响：

> 注意最后需要减去一个 $\left ( \frac{1-\sqrt{5}}{2}  \right )^{n}$

注意到 $\left ( \frac{1-\sqrt{5}}{2}  \right )$ 是一个在 $\left ( -1,0 \right ]$ 上的负小数。

当 $n$ 为偶数时，$-\left ( \frac{1-\sqrt{5}}{2}  \right )$ 为负，由于是向上取整，所以此时该式对答案没有影响。

当 $n$ 为奇数时，$-\left ( \frac{1-\sqrt{5}}{2}  \right )$ 为正，因为向上取整，最终答案需要加一。

综上，该式对答案有影响，当且仅当 $n$ 为奇数。

最后到了~~大家最爱的~~代码时光。

## 嗲吗
```cpp
#define int long long
const int MOD = 998244353;
struct mat 
{
	int a[2][2];
	mat() { memset(a, 0, sizeof a); }
	mat operator *(const mat &b)const 
	{
		mat op;
		for (int i = 0; i < 2; i++)
			for (int k = 0; k < 2; k++)
				for (int j = 0; j < 2; j++)
					op.a[i][j] = (op.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
		return op;
	}
} ans, I;
void init() 
{
	I.a[0][0] = I.a[0][1] = I.a[1][0] = 1;
	I.a[1][1] = 0;
	ans.a[0][0] = 3, ans.a[0][1] = 1;
	ans.a[1][0] = ans.a[1][1] = 0;
}
signed main() 
{
	int T = read();
	while (T--) 
	{
		n = read();
		init();
		if (n == 0) 
		{
			printf("1\n");
			continue;
		}else if (n == 1) 
		{
			printf("2\n");
			continue;
		}
		int ff = 0;
		if (n % 2 == 1)ff++;
		n -= 2;
		while (n) 
		{
			if (n & 1)ans = ans * I;
			I = I * I;
			n >>= 1;
		}
		ans.a[0][0] += ff;  //这里加了ff以后不要忘记取模
		printf("%lld \n", ans.a[0][0]%MOD);
	}
	return 0;
}
```

感谢 @lingfunny 大佬指出错误

有错误请 D 我。

---

## 作者：liuhaoyan0323 (赞：2)

本蒟蒻通过的第一道紫题，连夜肝出题解纪念。

## 思路

首先发个[感性思路](https://www.luogu.com.cn/paste/t4vsew9b)，下面给出详细过程。\
前置芝士：\
[Lucas 数列](https://baike.so.com/doc/6373417-6587061.html)

首先题目给出的数为 $\phi$，求 $\phi$ 的 $n$ 次幂并向上取整。题目背景也提到了数列，基于此不难想到斐波那契数列。

我们设 $a = (\dfrac{1+\sqrt{5}}{2})^n = \phi$，$b = (\dfrac{1-\sqrt{5}}{2})^n = \psi$。

Lucas 数列的递推式为 $L_n = \begin{cases} 
1 & n=1 \\ 
2 & n=0 \\ 
L_{n-1}+L_{n-2} & n>1 
\end{cases}$，通项式为 $L_{n} = a^{n} + b^{n}$。

据此我们易知 $a^{n} = L_n - b^{n}$，注意到 $\left| b \right| < 1$，所以 $\lim_{n \to \infty} b^n =0\ $，因此 $a^{n} \approx L_n$，代入具体数字：

- $n=1$，$b^n \approx -0.618$
- $n=2$，$b^n \approx 0.381$
- ……

我们知道，当 $n \equiv 1 \pmod{2}$ 时，$b<0$；否则 $b>0$。\
也就是说当 $n$ 为奇数时 $a^n = L_n - b^n = L_n + |b^n| > L_n$，否则 $a^n = L_n - b^n < L_n$

注意到题目要求的是 $\lceil{a^n}\rceil$，上文我们已经求出了 $\left| b \right| < 1$，所以在 $a^n < L_n$ 的情况下对结果无影响；在 $a^n > L_n$ 的情况下，需要加上 $1$。

综上所述，结论已经呼之欲出了，$a^n=L_n+n \& 1$。\
现在我们只需要计算 Lucas 数列便可以了，聪明的你一定想到计算方法 ---- 矩阵快速幂！
构造矩阵的方法就不介绍了。

## 代码

矩阵快速幂的代码模板采用的是[这个](https://blog.csdn.net/HXX904/article/details/116738452)。

#### $5pts$
[代码](https://www.luogu.com.cn/paste/22yah82n)
#### $5pts$ 越界优化版
[代码](https://www.luogu.com.cn/paste/ezp04mga)
#### $100pts$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 3
#define MOD 998244353
using namespace std;
int base[N][N],tmp[N][N],n;
inline void Init();
inline void mult(int x[N][N],int y[N][N]);
inline int fpow(int b);
inline void read(int &num);
signed main(){
    int T;
    read(T);
    while(T--){
		Init();
    	read(n);
    	int res=fpow(n-1);
    	if(n&1)++res;
    	printf("%lld\n",res%MOD);
	}
}
inline void Init(){
    base[1][1]=0;
    base[1][2]=1;
    base[2][1]=1;
    base[2][2]=1;
}
inline void mult(int x[N][N],int y[N][N]){
    int tmp[N][N];
    for(int i=1;i<N;++i){
    	for(int j=1;j<N;++j){
            tmp[i][j]=0;
            for(int k=1;k<N;++k){
            	tmp[i][j]=(tmp[i][j]+x[i][k]*y[k][j])%MOD;
			}  
        }
	} 
    memcpy(x,tmp,sizeof(tmp));
}
inline int fpow(int b){
    int ans[N][N];
    for(int i=1;i<N;++i){
        for(int j=1;j<N;++j){
        	ans[i][j]=1;
		}
    }
    ans[1][1]=1;
    ans[1][2]=3;
    while(b){
        if(b&1)mult(ans,base);
        mult(base,base);
        b/=2;
    }
    return ans[1][1];
}
inline void read(int &num){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	num=x*f;
}
```

---

## 作者：Ruiqun2009 (赞：2)

~~毒瘤卡常题~~

题目给我们 $n$，要让我们求 $\lceil(\dfrac{1+\sqrt{5}}{2})\rceil^n \bmod 998244353$。
## 方法 1
### 过程
有没有见过斐波那契数列的通项公式？我们设一个序列 $F$，满足：
$$
F_n=(\dfrac{1+\sqrt{5}}{2})^n+(\dfrac{1-\sqrt{5}}{2})^{n}
$$
现在我们只需要知道 $(\dfrac{1-\sqrt{5}}{2})^n$ 的范围就好了。

然后我们发现 $\dfrac{1-\sqrt{5}}{2}\in(-1,0)$。于是：
- 当 $n\bmod 2=1$ 时， $(\dfrac{1-\sqrt{5}}{2})^n<0$。
- 否则，$(\dfrac{1-\sqrt{5}}{2})^n>0$。

### 计算 $F_n$

我们设 $x=\dfrac{1+\sqrt{5}}{2},y=\dfrac{1-\sqrt{5}}{2}$。

复习完立方和公式的证明方法之后，我们试着递推：
$$
\begin{aligned}
F_n&=x^n+y^n\\
&=x^n+y^n+xy^{n-1}+yx^{n-1}-(xy^{n-1}+yx^{n-1})\\
&=(x+y)(x^{n-1}+y^{n-1})-xy(x^{n-2}+y^{n-2})\\
&=(x+y)F_{n-1}-xy\times F_{n-2}\\
\end{aligned}
$$
于是转移矩阵为
$$
\left[\begin{array}{cc}F_n&F_{n-1}\end{array}\right]
\times
\left[\begin{array}{cc}F_{n-1}&F_{n-2}\end{array}\right]^{-1}=
\left[\begin{array}{cc}
1&1\\
1&0\\
\end{array}\right]
$$
于是就可以递推了。注意 $F_1=1,F_2=3$。

### 实现
```cpp
mat base, res;
constexpr mint one(1), zero(0), three(3);
mint ans;
unsigned long long n = 0;
size_t T = 0;
inline void solve() {
    cin >> n;
    if (n == 0) cout << '1' << '\n';
    else if (n == 1) cout << '2' << '\n';
    else {
        base.mat[1][1] = zero;
        base.mat[0][0] = base.mat[0][1] = base.mat[1][0] = one;
        ans = (n & 1);
        n -= 2;
        res.mat[0][0] = three;
        res.mat[1][0] = res.mat[1][1] = zero;
        res.mat[0][1] = one;
        for (; n; base *= base, n >>= 1) if (n & 1) res *= base;
        ans += res.mat[0][0];
        cout << ans << '\n';
    }
}
int main() {
    base.mat.resize(2);
    base.mat[0].resize(2);
    base.mat[1].resize(2);
    res.mat.resize(2);
    res.mat[0].resize(2);
    res.mat[1].resize(2);
    cin >> T;
    for (size_t t = 0; t < T; t++) solve();
}
```
## 方法2
求出第 $n$ 个斐波那契数并乘以 $\sqrt{5}$，即得 $\sqrt{5}\times F_n$。

移项，得到 $\sqrt{5}\times F_n+(\dfrac{1-\sqrt{5}}{2})^n=(\dfrac{1+\sqrt{5}}{2})^n$。

按照上述方法，我们分析 $(\dfrac{1-\sqrt{5}}{2})^n$ 的结束了。

---

## 作者：Memory_of_winter (赞：2)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10356832.html)

**题目大意：**有$T(T\leqslant10^5)$组询问，每次求$A_n(n\leqslant10^{18})$：
$$A_n=\left\lceil\left(\dfrac{\sqrt5+1}2\right)^n\right\rceil$$
**题解：**通过打表~~看题解~~发现，这个序列是$2,3,5,7,\dots$，即$A_n=A_{n-1}+A_{n-2}-[n\equiv0\pmod2]$，题解中说可以记录三个信息矩阵快速幂一下，然后我并不会处理$[n\equiv0\pmod2]$（果然我最菜）

继续看下去，他说可以构造数列$F$，$F_n=F_{n-1}+F_{n-1}(F_1=1,F_2=3)$，$A_n=F_n+(n\bmod2)$，这样就可以过去了，复杂度$O(2^3T\log_2n)$

但是这样似乎感觉不够优秀，可以把转移矩阵分块预处理出来，$n\leqslant10^{18}<2^{60}$，可以$\sqrt{\sqrt n}$即$2^{15}$分一块，这样就可以在常数复杂度内求出一次的答案了，复杂度$O(4\times2^3T)$

更进一步的是，$F$为斐波那契数列，它在模一个数下有循环节，洛谷上有这么[一道题](https://www.luogu.org/problemnew/show/P4000)，比如在$998244353$下为$1996488708$，这样就可以取模后分块，就可以只分成两块，减少常数，复杂度$O(2\times2^3T)$（但是我跑的比上一个慢。。。~~加了编译指令才比上一个快~~）



**C++ Code：**

```cpp
#include <cstdio>
#include <cctype>
#define N 65537
const int mod = 998244353, cover = (1 << 16) - 1;

namespace std {
	struct istream {
#define M (1 << 23 | 3)
		char buf[M], *ch = buf - 1;
		inline istream() { fread(buf, 1, M, stdin); }
		inline istream& operator >> (int &x) {
			while (isspace(*++ch));
			for (x = *ch & 15; isdigit(*++ch); ) x = x * 10 + (*ch & 15);
			return *this;
		}
		inline istream& operator >> (long long &x) {
			while (isspace(*++ch));
			for (x = *ch & 15; isdigit(*++ch); ) x = x * 10 + (*ch & 15);
			return *this;
		}
#undef M
	} cin;
	struct ostream {
#define M (1 << 22 | 3)
		char buf[M], *ch = buf - 1;
		inline ostream& operator << (int x) {
			if (!x) {*++ch = '0'; return *this;}
			static int S[20], *top; top = S;
			while (x) {*++top = x % 10 ^ 48; x /= 10;}
			for (; top != S; --top) *++ch = *top;
			return *this;
		}
		inline ostream& operator << (const char x) {*++ch = x; return *this;}
		inline ~ostream() { fwrite(buf, 1, ch - buf + 1, stdout); }
#undef M
	} cout;
}

struct Matrix {
	int s00, s01, s10, s11;
	Matrix() { }
	Matrix(int __00, int __01, int __10, int __11) : s00(__00), s01(__01), s10(__10), s11(__11) { }
	inline Matrix operator * (const Matrix &rhs) {
#define M(l, r) static_cast<long long> (s##l) * rhs.s##r
#define C(ll, lr, rl, rr) (M(ll, lr) + M(rl, rr)) % mod
		return Matrix(C(00, 00, 01, 10), C(00, 10, 01, 11), C(10, 00, 11, 10), C(10, 01, 11, 11));
#undef M
#undef calc
	}
} base0[N], base1[N], ans(3, 1, 0, 0);

void init() {
	const Matrix I(1, 0, 0, 1);
#define work(x) \
	*base##x = I; \
	for (int i = 1; i < N; ++i) base##x[i] = base##x[i - 1] * __base##x;
	const Matrix __base0(1, 1, 1, 0); work(0);
	const Matrix __base1 = base0[N - 1]; work(1);
#undef work
}

int Tim;
int main() {
	init();
	std::cin >> Tim;
	while (Tim --> 0) {
		static long long n;
		static int res;
		std::cin >> n; --n, n %= 1996488708;
		res = (ans * base0[n & cover] * base1[n >> 16 & cover]).s01 + !(n & 1) - mod;
		std::cout << res + (res >> 31 & mod) << '\n';
	}
	return 0;
}

```



---

## 作者：mrsrz (赞：2)

~~打表找规律~~

既然都打出表来了，规律就不用手找了，直接扔OEIS上（逃

没错就是它！[A169986](http://oeis.org/A169986)

好我们直接拉那个递推公式：$a_n=a_{n-1}+2a_{n-2}-a_{n-3}-a_{n-4},a_1=2,a_2=3,a_3=5,a_4=7$。

接着对它矩阵快速幂。时间复杂度$O(4^3T\log n)$。看起来很不能过的样子。

对于这种底数不变的求幂，分块然后$O(1)$求是基本套路。

本题的$n$高达$10^18$，所以考虑分成$4$块，每块$\sqrt{\sqrt{n}}$个。然后每次求幂的复杂度降为$O(1)$，用初始状态左乘，常数大约$4\times 4^2=64$。

这样就砍掉一个$\log$，复杂度$O(64T)$。

当然用其他的矩阵小的转移方法可以做到更优的常数。

## Code：
```cpp
#include<cstdio>
#define md 998244353
#define M 32767
typedef long long LL;
struct matrix{
    int a[4][4];
    int r;
    matrix operator*(const matrix&b)const{
        matrix c;
        c.r=r;
        for(int i=0;i<r;++i)
        for(int j=0;j<4;++j){
            LL tmp=0;
            for(int k=0;k<4;++k)
            tmp+=LL(a[i][k])*b.a[k][j];
            c.a[i][j]=tmp%md;
        }
        return c;
    }
}_1[32769],_2[32769],_3[32769],_4[32769],a;
void init(){
	_1->r=_1[1].r=4;
	_1[1].a[0][0]=_1[1].a[0][1]=_1[1].a[1][2]=_1[1].a[2][3]=_1[0].a[0][0]=_1[0].a[1][1]=_1[0].a[2][2]=_1[0].a[3][3]=1;
	_1[1].a[1][0]=2;_1[1].a[2][0]=_1[1].a[3][0]=md-1;
	for(int i=2;i<=32768;++i)_1[i]=_1[i-1]*_1[1];
	*_2=*_1;_2[1]=_1[32768];
	for(int i=2;i<=32768;++i)_2[i]=_2[i-1]*_2[1];
	*_3=*_1;_3[1]=_2[32768];
	for(int i=2;i<=32768;++i)_3[i]=_3[i-1]*_3[1];
	*_4=*_1;_4[1]=_3[32768];
	for(int i=2;i<=32768;++i)_4[i]=_4[i-1]*_4[1];
}
int main(){
	init();
	a.r=1;
	a.a[0][0]=7,a.a[0][1]=5,a.a[0][2]=3,a.a[0][3]=2;
	int t;
	for(scanf("%d",&t);t--;){
		LL x;
		scanf("%lld",&x);--x;
		printf("%d\n",(a*_1[x&M]*_2[x>>15&M]*_3[x>>30&M]*_4[x>>45]).a[0][3]);
	}
	return 0;
}
```

---

## 作者：lemondinosaur (赞：2)

# 题目
求
$$\lceil(\frac{\sqrt 5+1}{2})^n\rceil$$

---
# 分析
这种题目肯定要打表找规律了呀，于是就顺着OEIS，有题解说是
$$F_n=F_{n-1}+2*F_{n-2}-F_{n-3}-F_{n-4}$$
结果就WA了，现在发现符号弄反了，然而

[OEIS来一波](http://oeis.org/A169986)
突然捡漏发现了下面一行，？？？这不是斐波那契数列吗,
$a(n) = 3*Fibonacci(n-1) + Fibonacci(n-2) + (n \bmod 2), n>0.$
so

---
# 代码
```cpp
#include <cstdio>
#include <cctype>
#define rr register
using namespace std;
const int mod=998244353;
struct maix{int p[2][2];}A,ANS;
inline long long iut(){
    rr long long ans=0; rr char c=getchar();
    while (!isdigit(c)) c=getchar();
    while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
    return ans;
}
inline maix mul(maix A,maix B,int k){
    rr maix C;
    for (rr int i=0;i<k;++i)
    for (rr int j=0;j<2;++j) C.p[i][j]=0;
    for (rr int i=0;i<k;++i)
    for (rr int j=0;j<2;++j)
    for (rr int k=0;k<2;++k)
    C.p[i][j]=(1ll*A.p[i][k]*B.p[k][j]+C.p[i][j])%mod;
    return C;
}
signed main(){
    for (rr int t=iut();t;--t){
        rr long long n=iut()-1; rr int k=(n&1)^1; n=n%1996488708;
        if (!n) {printf("1\n"); continue;}
        A.p[0][0]=1; A.p[0][1]=1; A.p[1][0]=1; A.p[1][1]=0;
        ANS.p[0][0]=1; ANS.p[0][1]=0; ANS.p[1][0]=0; ANS.p[1][1]=0;
        for (;n;n>>=1,A=mul(A,A,2))
            if (n&1) ANS=mul(ANS,A,1);
        printf("%d\n",(ANS.p[0][0]+(ANS.p[0][1]<<1)%998244353+k)%998244353);
    }
    return 0;
} 
```

---

## 作者：strcmp (赞：1)

首先很遗憾我们并不能直接上二次剩余，因为题目所求的外面有一个上取整。

令 $\phi = \dfrac{1 + \sqrt{5}}{2}$。

我们打个表出来：

```
2
3
5
7
12
18
30
47
77
123
200
322
```

那么规律已经很明显，对于 $n \ge 3$：

$$
f_n = \begin{cases}f_{n - 1} + f_{n - 2} & \text{n is odd}\\f_{n - 1} + f_{n - 2} - 1 & \text{n is even} \end{cases}
$$

考虑证明。

对于 $k \ge 3$ 我们有 $\phi^{k - 2} + \phi^{k - 1} = \phi^k$。数学归纳即可，$\phi^2 = 1 + \phi,\,\phi^{k - 2}(1 + \phi) = \phi^k$。

同理，$(1 - \phi)^k = (1 - \phi)^{k - 1} + (1 - \phi)^{k - 2}$，也是使用数学归纳容易得到。

而我们又有 $\phi^k + (1 - \phi)^k$ 是整数，原因还是数学归纳，$\phi + (1 - \phi) = 1$ 显然是整数，$\phi^2 + (1 - \phi)^2 = 3$ 显然是整数。然后就根据两边的递推式递归下去即可。

显然 $(1 - \phi)^k < 1$，当 $k \ge 1$ 时候。

于是根据 $(1 - \phi)^k$ 的正负性容易得到 $\phi^k + (1 - \phi)^k$ 在 $k$ 为奇数时是 $\lfloor \phi^k \rfloor$，否则是 $\lceil \phi^k \rceil$。

令 $a_k = \phi^k + (1 - \phi)^k$，我们有 $a_k = a_{k - 1} + a_{k - 2},\,k \ge 3$。并且 $a_1 = 1,\,a_2 = 3$。

显然 $\phi^k$ 不会是整数，因为 $0 < |(1 - \phi)^k| < 1$，所以 $\lfloor \phi^k \rfloor = \lceil \phi^k \rceil - 1$。

然后根据 $k$ 的奇偶性我们求出了 $a_k$ 就能知道 $\lceil \phi^k \rceil$。

对 $a_k$ 使用矩阵快速幂即可，时间复杂度 $\Theta(T \log n)$ 带一个 $8$ 倍常数，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pq = priority_queue<int>;
using ld = double;
constexpr int maxn = 1e5 + 10, mod = 998244353, B = 230, inf = 1e9;
struct mat {
    ll a[2][2];
    mat() { memset(a, 0, sizeof(a)); }
    ll* operator[](int x) { return a[x]; }
    const ll* operator[](int x) const { return a[x]; }
    mat operator*(const mat& b) const {
        mat c;
        rep(i, 0, 1) rep(k, 0, 1) {
            c[i][0] = (c[i][0] + a[i][k] * b[k][0] % mod) % mod;
            c[i][1] = (c[i][1] + a[i][k] * b[k][1] % mod) % mod;
        }
        return c;
    }
};
int T; ll n;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &n);
        if (n == 1) puts("1");
        else if (n == 2) puts("3");
        else {
            mat a, b; a[0][1] = a[1][0] = a[1][1] = 1; b[0][0] = 1, b[1][0] = 3; int w = n; n -= 2;
            while (n) {
                if (n & 1) b = a * b;
                a = a * a; n >>= 1;
            }
            ll ans = (b[1][0] + (w & 1 ? 1 : 0)) % mod;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
```

---

## 作者：lingfunny (赞：1)

## P5136 sequence 题解

发现要求的是带根号的，考虑~~二次剩余~~共轭。

参考 [[JLOI2015]有意义的字符串](https://www.luogu.com.cn/problem/P3263)。

令 $p=\frac{1+\sqrt{5}}{2},q=\frac{1-\sqrt{5}}{2}$，显然有：

1. $p+q=1$
2. $pq=-1$

对于方程 $x^2-x-1$，$p,q$ 即为方程两根。

直接求 $p^n$ 较为困难，考虑记 $f_n=p^n+q^n$。有：
$$
\begin{array}{c}
p^n+q^n=(p^{n-1}+q^{n-1})(p+q)-(p^{n-2}+q^{n-2})pq\\
\Updownarrow\\
f_n=f_{n-1}+f_{n-2}
\end{array}
$$
根据这个递推式和上面的特征方程，发现这是一个斐波那契数列，首项可以手推：$f_0=p^0+q^0=2,f_1=p+q=1$。

注意到最后答案应该是 $f_n-q^n$，发现 $\left|q\right|<\overline\phi$，根据上取整的性质，有 $\texttt{ans}=f_n+[n\text { is odd}]$。

至此，可以用矩阵快速幂在 $\Theta(T\log n)$ 的时间复杂度内解决本题。

不过根据**斐波那契循环节**的常识，本题还能继续优化。

发现模数 $998244353\equiv3\pmod{5}$，则循环节为 $2\times(998244353+1)$（详见 [斐波那契循环节](https://blog.csdn.net/ding4440/article/details/101250954)）。

至此，可以通过 $n\le10^{114514+1919810}$ 的数据了，复杂度与 $n$ 无关（除读入）。

~~时间复杂度 $\Theta(T\log 998244353)=\Theta(T)$（雾~~

时间复杂度 $\Theta(T\log p)$。

还可以继续拓展。若 $p$ 不为质数，则可以继续分解（详见 [斐波那契循环节](https://blog.csdn.net/ding4440/article/details/101250954)）求出循环节 $G$，由于 $G\le 6p$，时间复杂度 $\Theta(\sqrt{p}+\log p)\sim\Theta(T\log p)$。

更进一步，发现有多组询问，我们考虑降低一次查询的复杂度。

类似 BSGS 的思想，我们可以对矩阵幂分块，记转移矩阵为 $P$，$S = \sqrt{p}$，用哈希表记录 $P^S,P^{2S},P^{3S},\cdots$ 和 $P,P^2,\cdots,P^{S-1}$，求解时只需完成三个矩阵相互乘即可。

时间复杂度 $\Theta(\sqrt{p}+\log p)\sim\Theta(T)$。

### CODE

```cpp
// Problem: P5136 sequence
// From: Luogu
// URL: https://www.luogu.com.cn/problem/P5136
// Time: 2022-03-06 15:59
// Author: lingfunny

#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
#define LL long long
const int mod = 998244353, loop = (mod+1)<<1, S = ceil(sqrt(loop));
using namespace std;

int tt, n;
inline int mul(int x, int y) { return (LL)x*y%mod; }

struct matrix {
	int a[2][2], n, m;
	inline matrix operator * (const matrix& rhs) const {
		matrix res;
		res.n = n, res.m = rhs.m;
		for(int i = 0; i < n; ++i)
		for(int j = 0; j < rhs.m; ++j) {
			res.a[i][j] = 0;
			for(int k = 0; k < m; ++k)
			(res.a[i][j] += mul(a[i][k], rhs.a[k][j])) %= mod;
		}
		return res;
	}
} A = { { {2, 1}, {0, 0} }, 1, 2 }, ls[S+5];
const matrix P = { { {0, 1}, {1, 1} }, 2, 2 };
gp_hash_table <int, matrix> gs;
inline void init() {
	matrix x = {{{1,0},{0,1}},2,2}, y;
	gs[0] = x;
	for(int i = 0; i < S; ++i) {
		ls[i] = x;
		x = x * P;
	}
	y = x;
	for(int i = 1; i <= S; ++i) {
		gs[i] = y;
		y = y * x;
	}
}
#define GC getchar()
inline int read() {
	unsigned x = 0; char ch = GC;
	while(ch < '0') ch = GC;
	while('0' <= ch) { x = ((x<<1) + ((LL)x<<3) + (ch^48)) % loop; ch = GC; }
	return x;
}

signed main() {
	init();
	tt = read();
	while(tt--) {
		n = read();
		A.a[0][0] = 2; A.a[0][1] = 1;
		A = A * (gs[n/S] * ls[n%S]);
		printf("%d\n", (A.a[0][0]+(n&1))%mod);
	}
	return 0;
}
```



---

## 作者：orz_z (赞：1)


求：
$$
\left\lceil\left(\frac{1+\sqrt{5}}{2}\right)^{i}\right\rceil
$$

#### sol

首先考虑将原式转换为：
$$
\left\lceil\left(\frac{1+\sqrt{5}}{2}\right)^{i}+\left(\frac{1-\sqrt{5}}{2}\right)^{i}-\left(\frac{1-\sqrt{5}}{2}\right)^{i}\right\rceil
$$
显然有：
$$
\left(\frac{1+\sqrt{5}}{2}\right)^{i}+\left(\frac{1-\sqrt{5}}{2}\right)^{i}=f(i)
$$
其中 $f$ 为斐波那契数列。

考虑用矩阵快速幂优化递推计算。

显然，设状态矩阵为：

$$
\begin{bmatrix}f_{n}&f_{n-1}\end{bmatrix}
$$
显然，转移矩阵为：
$$
\begin{bmatrix}1&1\\1&0\end{bmatrix}
$$
最后再来看看减去的 $\left(\frac{1-\sqrt{5}}{2}\right)^{i}$ 对最终答案的影响。

考虑分奇偶性讨论：

* 当 $i$ 为偶数时，$-\left(\frac{1-\sqrt{5}}{2}\right)^{i}$ 为负，无影响。
* 当 $i$ 为奇数时，$-\left(\frac{1-\sqrt{5}}{2}\right)^{i}$ 为正，最终答案加一。

那就没了。。。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

int T, n;

const int MOD = 998244353;

struct mat
{
    int a[2][2];
    mat()
    {
        memset(a, 0, sizeof a);
    }
    mat operator*(const mat &b) const
    {
        mat op;
        for (int i = 0; i < 2; i++)
            for (int k = 0; k < 2; k++)
                for (int j = 0; j < 2; j++)
                    op.a[i][j] = (op.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
        return op;
    }
} ans, I;

void init()
{
    I.a[0][0] = I.a[0][1] = I.a[1][0] = 1;
    I.a[1][1] = 0;
    ans.a[0][0] = 3, ans.a[0][1] = 1;
    ans.a[1][0] = ans.a[1][1] = 0;
}

signed main()
{
    T = read();
    while (T--)
    {
        n = read();
        init();
        if (n == 0)
        {
            printf("1\n");
            continue;
        }
        else if (n == 1)
        {
            printf("2\n");
            continue;
        }
        bool flag = 0;
        if(n % 2 == 1) flag = 1;
        n -= 2;
        while (n)
        {
            if (n & 1)
                ans = ans * I;
            I = I * I;
            n >>= 1;
        }
        printf("%lld\n", (ans.a[0][0] + flag) % MOD);
    }
    return 0;
}
```



---

