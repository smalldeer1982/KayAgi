# Contemplation! Algebra

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1596

[PDF](https://uva.onlinejudge.org/external/106/p10655.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10655/dbec0a8cf5c06f09ce23405958f51502311809a2.png)

## 样例 #1

### 输入

```
10 16 2
7 12 3
0 0```

### 输出

```
68
91```

# 题解

## 作者：peterwuyihong (赞：4)

题意：给你 $a+b,ab,n$ 求 $a^n+b^n$。

$a^n+b^n=(a^{n-1}+b^{n-1})(a+b)-(ab)(a^{n-2}+b^{n-2})$

然后你矩阵递推即可，记 $f_i=a^i+b^i$

$ \begin{bmatrix}  f_{i+1}&f_i     \end{bmatrix} = \begin{bmatrix}    f_i&f_{i-1} \end{bmatrix} \begin{bmatrix} a+b&1 \\ -ab&0 \end{bmatrix}  $

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
const int p=LLONG_MAX;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
struct mat{
	#define Bsiz 3
	int n,m,_[Bsiz][Bsiz];
	mat(int N=0,int M=0){
		memset(_,0,sizeof _);
		n=N,m=M;
	}
	int*operator[](const int&x){return _[x];}
	void Read(int n,int m){for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>_[i][j];}
	void Read(){cin>>n>>m,Read(n,m);}
	void Print(){
		for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=m;j++,cout<<' ')cout<<_[i][j];
	}
	mat operator+(const mat&a){
		assert(a.n==n&&a.m==m);mat ans(n,m);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
		ans[i][j]=Add(_[i][j],a._[i][j]);return ans;
	}
	mat operator*(const mat&a){
		assert(m==a.n);mat ans(n,a.m);
		for(int i=1;i<=ans.n;i++)
		for(int j=1;j<=ans.m;j++)
		for(int k=1;k<=m;k++)
		add(ans[i][j],Mul(_[i][k],a._[k][j]));
		return ans;
	}
}G(2,2),F;
mat e(int n){
	mat __(n,n);for(int i=1;i<=n;i++)
	__[i][i]=1;return __;
}
mat Ksm(mat a,long long b){
	mat ans=e(a.n);
	for(;b;b>>=1,a=a*a)
	if(b&1)ans=ans*a;
	return ans;
}
int A,B;
signed main(){
	G[1][2]=1;
	while(scanf("%lld%lld%lld",&A,&B,&n)==3){
		G[2][1]=-B,G[1][1]=A;
		F=mat(2,2);
		F[1][1]=A,F[1][2]=2;
		F=F*Ksm(G,n);
		cout<<F[1][2]<<endl;
	}
}
```
被这个输入格式恶心到了，并不能写
```cpp
while(cin>>A>>B,A+B)
```
因为存在 `A=0,B=0,n` 的情况

---

## 作者：Karry5307 (赞：4)

### 题意

给定$a+b$，$ab$，求$a^n+b^n$。

$\texttt{Data Range:}0\leq a,b,n,a^n+b^n\leq 2^{63}$

### 题解

这道题有一个显而易见的分治做法。

对$n$的奇偶性分类讨论，可得

$$a^n+b^n=\begin{cases}(a^{\frac{n}{2}}+b^{\frac{n}{2}})^2-2(ab)^{\frac{n}{2}}&,\texttt{if }n\texttt{ is even}\\(a^{\lfloor\frac{n}{2}\rfloor}+b^{\lfloor\frac{n}{2}\rfloor})(a^{\lceil\frac{n}{2}\rceil}+b^{\lfloor\frac{n}{2}\rceil})-(ab)^{\lfloor\frac{n}{2}\rfloor}(a+b)&,\texttt{if }n\texttt{ is odd}\end{cases}$$

分治做就行了qwq。可是要特判一下。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
li p,q,num;
unordered_map<li,li>mp;
inline li read()
{
    register li num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline li qpow(li base,li exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=res*base;
		}
		base=base*base,exponent>>=1;
	}
	return res;
}
inline li calc(li num)
{
	if(!num)
	{
		return 2;
	}
	if(num==1)
	{
		return p;
	}
	if(mp.find(num)!=mp.end())
	{
		return mp[num];
	}
	li x=calc(num>>1),t=qpow(q,num>>1);
	if(num&1)
	{
		li y=calc(num-(num>>1));
		mp[num]=x*y-t*p;
		return mp[num];
	}
	mp[num]=x*x-(t<<1);
	return mp[num];
}
int main()
{
    while(scanf("%lld%lld%lld",&p,&q,&num)==3)
	{
		if(!p&&!q)
		{
			puts("0");
			continue;
		}
		if(!q)
		{
			printf("%lld\n",qpow(p,num));
			continue;
		}
		printf("%lld\n",calc(num));
		mp.clear();
	}
}

```

---

## 作者：August_Light (赞：3)

# UVA10655 Contemplation! Algebra 题解

[题目传送门](https://www.luogu.com.cn/problem/UVA10655)

## 题意简述

$x+y = p, xy = q$，已知 $p,q,n$，求 $x^n + y^n$。

保证答案是 $64$ 位有符号整数。

## 前置知识

- 快速幂

## 解法

**并非正常解法，欢迎大家来 hack**。

不妨设 $x \ge y$，根据初中数学知识可知：设 $M = p^2 - 4q$。

$$x = \dfrac {p + \sqrt M} 2, y = \dfrac {p - \sqrt M} 2$$

用一个 `complex<long double>` 存储，直接快速幂就行了。

吗？

[这个帖子](https://www.luogu.com.cn/discuss/679743)中 @[Jasminoides](https://www.luogu.com.cn/user/322792) 提供的数据，使得这个方法爆精度了，成功 hack 了相同方法的[这篇题解](https://www.luogu.com.cn/blog/366338/solution-uva10655)。

所以我这篇题解就是来搞定这个问题的。

首先，我们知道爆 `long long` 时可以用 `__int128`，同理，`long double` 精度不足时可以使用 `__float128`。

但是仅仅使用这个优化依然不能通过该数据。

所以我们使用**扩域快速幂**。相关资料：[神鱼](https://www.luogu.com.cn/blog/NaCly-Fish-blog/solution-p1962)。

具体到这道题：

- 当 $M \ge 0$ 时，我们以 $\sqrt M$ 为虚数单位。
- 当 $M < 0$ 时，我们以 $\sqrt {-M} i$ 为虚数单位。

这样可以很大程度上减少精度损失。

时间复杂度 $O(\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef __float128 f128;

LL p, q, n;

LL M, flg;
struct Complex {
    f128 real = 0, imag = 0;
    Complex(f128 real, f128 imag) : real(real), imag(imag) {}
    Complex friend operator*(const Complex& x, const Complex& y) {
        Complex ret(0, 0);
        ret.real += x.real * y.real;
        ret.real += x.imag * y.imag * M * flg;
        ret.imag += x.real * y.imag;
        ret.imag += x.imag * y.real;
        return ret;
    }
};

Complex qpow(Complex a, LL b) {
    Complex ret(1, 0);
    while (b) {
        if (b & 1)
            ret = ret * a;
        a = a * a;
        b >>= 1;
    }
    return ret;
}

int main() {
    while (scanf("%lld %lld %lld", &p, &q, &n) == 3) {
        M = p * p - 4 * q;
        if (M < 0) {
            M = -M;
            flg = -1;
        } else
            flg = 1;
        Complex x((f128)p / 2, (f128)1 / 2), y((f128)p / 2, (f128)-1 / 2);
        LL ans = qpow(x, n).real + qpow(y, n).real;
        cout << ans << '\n';
    }
    return 0;
}
```



---

## 作者：DepContain (赞：3)

$Update$

$2023-05-07$ 修改码风
    
$2023-07-05$ 修改题解中的错误

$Link$

题目链接:[UVA10655](https://www.luogu.com.cn/problem/UVA10655)

前置：[P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390)或[P1939 【模板】矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)

# Description
给定 $p$，$q$，$n$，求 $a^n+b^n$。
（其中 $p=a+b$，$q=ab$）

# Solution
由于观察到待求式为 $a^n + b^n$ 故考虑**快速幂**，但由于 $a$、$b$ 直接给出，考虑用矩阵转移至 $n$ 次方。故用**矩阵加速**。

1. 为了方便描述，我们记 $\operatorname{Sum} (n)=a^n+b^n$。

2. 记矩阵 $\boldsymbol{Mat}(n) = \begin{bmatrix}Sum(n) & Sum(n-1)\end{bmatrix}$

3. 显然的，$ (a^{n-1} + b^{n-1})(a+b)=a^n+b^n+ab(a^{n-2}+b^{n-2})$

故有 $\operatorname{Sum} (n)=p\times \operatorname{Sum} (n-1)-q\times \operatorname{Sum} (n-2)$（记为**式 1**）

## How to construct

我们首先要确定目标矩阵。下面这个矩阵就是需要的矩阵。
 
$$\boldsymbol{Mat}(n)=\begin{bmatrix}Sum(n) & Sum(n-1)\end{bmatrix}$$

那么这个矩阵要怎样算？

根据**式 1**我们可以得到 $\boldsymbol{Mat}(n-1)\times \begin{bmatrix}p & 1\\ -q &0\end{bmatrix}=\boldsymbol{Mat}(n)$

从而推得 $\boldsymbol{Mat}(n)=\begin{bmatrix}p & 2\end{bmatrix}\times\begin{bmatrix}p & 1\\ -q &0\end{bmatrix}^{n-1}$

然后我们就可以通过**矩阵快速幂**进行求解（特判 $n=0$ 或 $n=1$，分别输出 $2$，$p$）。

# AC Code
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Mat{
	ll a[2][2];
	ll* operator [](int x) { return a[x]; }
	Mat(){ memset(a, 0, sizeof a);}
	Mat operator *(const Mat &x) const{
		Mat z; 
	
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k) z.a[i][j] += a[i][k] * x.a[k][j];
		
		return z;
	}
};


Mat quickpower(Mat a, ll k){
	Mat ret = a,base = a;k--;
	
	while(k > 0){
		if(k % 2 == 1)	ret = base * ret;		
		base = base * base;
		k /= 2;
	}
	
	return ret;
}

ll p, q, n;

int main(){
	while(scanf("%lld%lld%lld", &p, &q, &n) == 3){
		if (n == 0){
			printf("2\n");
			continue;
		}
		else if(n == 1){
			printf("%lld\n", p);
			continue;
		}
		
		Mat prc, init;
		init[0][0] = p; init[0][1] = 2;
		prc[0][0] = p;  prc[0][1] = 1;
		prc[1][0] = -q; prc[1][1] = 0;
		Mat c = quickpower(prc, n - 1);
		
		c = init * c;
		printf("%lld\n", c[0][0]);
	}
	
	return 0;
}

```



---

## 作者：zhylj (赞：3)

为了更好的阅读体验，你可以前往我的博客：[https://www.cnblogs.com/zhylj/p/9931671.html](https://www.cnblogs.com/zhylj/p/9931671.html)

### 题目

给定 $p = a + b$ 和 $q = ab$ 和 $n$，求 $a ^ n + b ^ n$。

$0\le n\lt 2^{63} $

### 分析

大水题。

先考虑 $n$ 较小的情况，可以很容易的想到递推：
$$\begin{array}{}\text{令} F(i) & = a ^ n + b ^ n \\& = (a + b)(a ^ {n - 1} + b ^ {n - 1}) - (ab ^ {n - 1} + a^{n - 1}b) \\& = (a + b)(a ^ {n - 1} + b ^ {n - 1}) - ab(a ^ {n - 2} + b ^ {n - 2}) \\& = p \times F(i - 1) - q \times F(i - 2)\end{array}$$
然后发现这个递推式可以用矩阵优化：
$$\left[\begin{matrix}p & - q \\1 & 0\end{matrix}\right]\times\left[\begin{matrix}	F[i] \\	F[i - 1]\end{matrix}\right] =\left[\begin{matrix}	F[i] \times p & + & F[i - 1]\times (-q) \\	F[i] \times 1 & + & F[i - 1]\times 0\end{matrix}\right] =\left[\begin{matrix}	F[i + 1] \\	F[i]\end{matrix}\right]$$
即：
$$\left[\begin{matrix}	p & - q \\	1 & 0\end{matrix}\right]^n\times\left[\begin{matrix}	F[1] \\	F[0]\end{matrix}\right] =\left[\begin{matrix}F[n + 1] \\F[n]\end{matrix}\right]$$
显然，$F[1] = p,\ F[0] = 2$。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 10;

struct matrix {
    ll a[MAXN][MAXN]; int rowSize, lineSize;

    matrix(int x, int y) {
        rowSize = x; lineSize = y;
    }
    
    ll *operator [](const unsigned &i) {return a[i];}

    matrix operator *(matrix y) {
        matrix ans(rowSize, y.lineSize);
        for(int i = 0; i < ans.rowSize; i++)
            for(int j = 0; j < ans.lineSize; j++) {
                ans[i][j] = 0;
                for(int k = 0; k < lineSize; k++)
                    ans[i][j] += a[i][k] * y[k][j];
            }
        return ans;
    }
} u(2, 2);

matrix qPow(matrix x, ll b) {
    matrix ans = u, base = x;
    while(b) {
        if(b & 1)
            ans = ans * base;
        base = base * base;
        b >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    u[0][0] = 1; u[0][1] = 0;
    u[1][0] = 0; u[1][1] = 1;
    ll p, q, n;
    while(scanf("%lld%lld%lld", &p, &q, &n) == 3) {
        matrix a(2, 2), b(2, 2), st(2, 1);
        a[0][0] = p; a[0][1] = -q;
        a[1][0] = 1; a[1][1] = 0;
        st[0][0] = p; st[1][0] = 2;
        b = qPow(a, n) * st;
        printf("%lld\n", b[1][0]);
    }
    return 0;
}
```



---

## 作者：cyq32ent (赞：1)

这里介绍一种不需要使用浮点数或者复数运算的扩域快速幂做法。

我们知道，$a=\frac{p+\sqrt{z}}{2}, b=\frac{p-\sqrt{z}}{2}$，其中 $z=p^2-4q$。注意到

$$\begin{align*}
2^n(a^n+b^n)&=\sum_{i=0}^n{n\choose i}p^{n-i}\sqrt{z}^{i}+\sum_{i=0}^n{n\choose i}p^{n-i}\sqrt{z}^{i}(-1)^i \\
&= \sum_{i=0}^n{n\choose i}p^{n-i}\sqrt{z}^i(1+(-1)^i)
\end{align*}$$

我们惊奇地发现，所有诸如 $\sqrt{z}^{2k+1}$ 的项，系数中 $(1+(-1)^i)$ 都为 $0$。所以，我们考虑将非负整数域扩展至如下的域：$x+y\sqrt{z}$，这样，最后计算出来的结果中，$\sqrt{z}$ 一项的系数一定为 $0$。容易定义该域上的加法、乘法运算。但是如何处理除以 $2$ 呢？只需要乘以它的逆元即可。题目保证答案小于 $2^{63}$ ，但是 $2^{63}$ 不是一个素数。注意到比 $2^{63}$ 略大的 $9223372036854775837$ 是一个素数，所以我们可以对它取模。

这样，我们就严谨地秒掉了这道紫题。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=__int128;
const ll M=9223372036854775837ull;
ll z;
ll qpow(ll a,ll p){
	ll res=1;a%=M;
	for(;p;p>>=1){
		if(p&1)res=res*a%M;
		a=a*a%M;
	}return res;
}struct LL{
	ll x,y;//x+y sqrt(z)
	LL(){}
	LL(ll x,ll y):x(x),y(y){};
	friend LL operator+(LL a,LL b){
		return LL((a.x+b.x)%M,(a.y+b.y)%M);
	}friend LL operator*(LL a,LL b){
		return LL((a.x*b.x%M+a.y*b.y%M*z%M)%M,(a.x*b.y%M+b.x*a.y%M)%M);
	}friend LL operator/(LL a,ll b){
		return LL(a.x*qpow(b,M-2)%M,a.y*qpow(b,M-2)%M);
	}
};LL qpow(LL a,ll p){
	LL res(1,0);
	for(;p;p>>=1){
		if(p&1)res=res*a;
		a=a*a;
	}return res;
}
int main(){
	int _p,_q,_n;
	while(cin>>_p>>_q>>_n){
		ll p=_p,q=_q,n=_n;
		z=p*p-4*q;
		LL a=LL(p,1),b=LL(p,M-1);
		a=a/2;b=b/2;
		LL x=qpow(a,n)+qpow(b,n);
		cout<<(long long)x.x<<endl;
	}
	return 0;
}
```

---

## 作者：AlexandreLea (赞：1)

## 题意简述

给出三个数 $s,p,n$，其中 $s=a+b,p=ab$，求 $a^n+b^n$ 的值。

## 题目思路

使用题面的解法，我们可以迅速地得出两个方程

$$\begin{cases}a+b=s\\ab=p\end{cases}$$

然后消元得到二元一次方程组

$$x^2-sx+p=0$$

然后，$a=x_0,b=x_1$。对于 $\Delta =s^2-4p<0$，可以使用 C++ 自带的虚数求解 $a$ 和 $b$，然后快速幂求出解。下面是代码：

```cpp
#include <iostream>
#include <complex>
#include <iomanip>
#define fs0 fixed<<setprecision(0)
using namespace std;
complex<long double> pow(complex<long double> a,long long n){
    complex<long double> ans=complex<long double>(1.0,0.0);
    for(;n;n/=2,a*=a) if(n%2!=0) ans*=a;
    return ans;
}
signed main(){
    long long su,pr,n;
    while(scanf("%lld %lld %lld",&su,&pr,&n)==3){
        long double s=su,p=pr,delta=s*s-4.0*p;
        complex<long double> a,b,ans;
        a=b=complex<long double>(s,.0);
        if(delta<0) a+=complex<long double>(.0,sqrtl(-delta));
        else a+=complex<long double>(sqrtl(delta),.0);
        a/=(long double)2.0;
        cout<<(long long)(pow(a,n)+pow(b-a,n)).real()<<endl;
    }
    return 0;
}
```

然而这个思路行不通。由于 `long double` 的精度限制（我 Hack 了使用虚数解题的题解），我们的答案永远和标准答案差一部分。这里就不放数据了。

怎么办呢？

现在我们设 $F_n=a^n+b^n$。我们知道，

$$a^3+b^3=(a+b)(a^2-ab+b^2)$$

因此我们完全可以考虑通过递推式来求它。~~根据直觉~~，我们设

$$(a+b)(F_{n-1})-S=F_n$$

即

$$(a+b)(a^{n-1}+b^{n-1})-S=a^n+b^n$$

拆开括号，就有

$$a^n+b^n+a^{n-1}b+ab^{n-1}-S=a^n+b^n$$

而后，消掉同类项并移相：

$$S=a^{n-1}b+ab^{n-1}$$

提公因式 $ab$，就有

$$S=ab(a^{n-2}+b^{n-2})$$

最后，将 $S$ 带入，就有

$$a^n+b^n=(a+b)(a^{n-1}+b^{n-1})-ab(a^{n-2}b^{n-2})$$

改写成 $F_n$ 的形式，就是这样：

$$F_n=sF_{n-1}-pF_{n-2}$$

这里

$$F_0=2$$

$$F_1=s$$

现在，我们有了一种新的方式，即递推法求出 $F_n$，然而肯定会爆炸。

然而，上面的式子……看上去就像下面的式子：

$$F_n=F_{n-1}+F_{n-2}$$

$$F_0=0,F_1=1$$

斐波那契数列的推广！

众所周知，斐波那契可以通过矩阵快速幂来解，然而在这个例子中该如何使用呢？

现在，我们假设

$$\begin{bmatrix}F_n&F_{n-1}\end{bmatrix}=\begin{bmatrix}F_{n-1}&F_{n-2}\end{bmatrix}\times \mathbf M$$

我们知道，$\mathbf M$ 必然是二行二列的，不然就乘不动了。设

$$\mathbf M=\begin{bmatrix}m_{11}&m_{12}\\m_{21}&m_{22}\end{bmatrix}$$

而乘法结果会长成这样：

$$\begin{bmatrix}F_n&F_{n-1}\end{bmatrix}=\begin{bmatrix}F_{n-1}&F_{n-2}\end{bmatrix}\times\begin{bmatrix}m_{11}&m_{12}\\m_{21}&m_{22}\end{bmatrix}$$

$$=\begin{bmatrix}F_{n-1}m_{11}+F_{n-2}m_{21}&F_{n-1}m_{12}+F_{n-2}m_{22}\end{bmatrix}$$

由于 $F_n=sF_{n-1}-pF_{n-2}$ 则 $m_{11}=s,m_{21}=-p$；而由于第二项 $F_{n-1}$ 与 $F_{n-1}$ 相同，所以 $m_{12}=1,m_{22}=0$。

所以

$$\mathbf M=\begin{bmatrix}s&1\\-p&0\end{bmatrix}$$

由于矩阵乘法满足结合律，所以我们可以先计算出 $\mathbf M^{n-1}$ 再乘以原来的 $\begin{bmatrix}s&2\end{bmatrix}$ 并取出第一项就是我们的答案。

所以，

$$\begin{bmatrix}F_n&F_{n-1}\end{bmatrix}=\begin{bmatrix}F_1&F_0\end{bmatrix}\times\mathbf M^{n-1}=\begin{bmatrix}s&2\end{bmatrix}\times\begin{bmatrix}s&1\\-p&0\end{bmatrix}^{n-1}$$

注意特判 $n$ 的初始条件。

代码如下：

```cpp
#include <iostream>
#define int long long
using namespace std;
struct mat{
    int r,c,d[3][3]={};
};
mat operator*(mat a,mat b){
    mat c;
    c.r=a.r,c.c=b.c;
    for(int i=1;i<=c.r;i++) for(int j=1;j<=c.c;j++) for(int k=1;k<=a.c;k++){
        c.d[i][j]+=a.d[i][k]*b.d[k][j];
    }
    return c;
}
mat matpow(mat a,int n){
    mat dw=a;n--;
    for(;n;n/=2,a=a*a) if(n%2==1) dw=dw*a;
    return dw;
}
signed main(){
    int s,p,n;
    while(scanf("%lld %lld %lld",&s,&p,&n)==3){
        mat px;
        px.r=2,px.c=2;
        px.d[1][1]=s,px.d[1][2]=1,px.d[2][1]=-p,px.d[2][2]=0;
        if(n!=0&&n!=1){
            px=matpow(px,n-1);
            cout<<s*px.d[1][1]+2*px.d[2][1]<<endl;
        }else cout<<(n==0?2:s)<<endl;
    }
    return 0;
}
```

**EOF**

---

## 作者：_lfxxx_ (赞：1)

题意就是说给你 $a+b$ 和 $ab$，让你求 $a^n+b^n$，保证 $a,b,n$ 在 $32$ 位有符号整形范围内，答案在 $64$ 位有符号整形范围内，不会让你算 $0^0$ 这种离谱的东西。

初二数学告诉我们，$a+b$ 和 $ab$ 是能凑出来 $a^n+b^n$ 的，这不好直接看出来，先写几个看看。

$$a^2+b^2=(a+b)^2-2ab$$

$$a^3+b^3=(a^2+b^2)(a+b)-ab^2-a^2b=(a^2+b^2)(a+b)-ab(a+b)$$

$$a^4+b^4=(a^3+b^3)(a+b)-ab^3-a^3b=(a^3+b^3)(a+b)-ab(a^2+b^2)$$

发现了吗，如果我们设 $f(n)=a^n+b^n$，那么 $f(n)=(a+b) \cdot f(n-1)-ab \cdot f(n-2)$（上面为体现思考过程第一个柿子并没有写成这样的形式）。这个递推式我们可以矩阵加速，构造下面的柿子：（$a+b$ 记作 $p$，$ab$ 记作 $q$）

$$\begin{bmatrix} 0 & 1 \\ -q & p \end{bmatrix}\times \begin{bmatrix} f(n-2) \\ f(n-1) \end{bmatrix}=\begin{bmatrix} f(n-1) \\ f(n) \end{bmatrix}$$

初始 $f(0)=a^0+b^0=2$，$f(1)=a^1+b^1=a+b$。

然后就愉快的水掉这道题了。

代码：
```cpp
struct mat{
	long long a[3][3];
	mat(){memset(a,0,sizeof a);}
	inline mat operator*(const mat&b){
		mat res;
		for(int i=1;i<=2;++i)
			for(int j=1;j<=2;++j)
				for(int k=1;k<=2;++k)
					res.a[i][k]+=a[i][j]*b.a[j][k];
		return res;
	}
	inline mat operator^(int k){
		mat res,b=*this;
		res.a[1][1]=res.a[2][2]=1;
		while(k){
			if(k&1)
				res=res*b;
			b=b*b;
			k>>=1;
		}
		return res;
	}
}a,bas;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	a.a[1][1]=2;
	bas.a[1][2]=1;
	while(cin>>bas.a[2][2]>>bas.a[2][1]>>n){
		a.a[2][1]=bas.a[2][2],bas.a[2][1]=-bas.a[2][1];
		cout<<((bas^n)*a).a[1][1]<<'\n';
	}
	return 0;
}
```

---

## 作者：fjy666 (赞：1)

题意：给定 $a+b,ab$，求 $(a+b)^n$

矩阵递推？  
是的，但我今天不讲这个。  
我们充分发扬人类智慧，直接解方程解出 $a,b$。  
什么？你说 $\Delta<0$？  
`std::complex` 可以搞。  
然后直接快速幂就行了。  
注意：一定要用 `complex<long double>` 这种精度最高的东西，否则就卡精度没商量。  
尽管这种做法不是出题人的意思，但我还是想说：人类智慧，yyds！
```cpp
//Code by fjy666
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = a_; i_ <= b_; ++i_)
#define mid ((L+R) >> 1)
#define get(x) (((x) - 1) / kb + 1)
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
using Comp = complex<long double>;

Comp fpm(Comp a, ll n) {
	Comp res = Comp(1.0, 0);
	for(;n; n >>= 1, a *= a) if(n & 1) res *= a;
	return res;
}

int main() { 
	long double p, q; ll n;
	while(3 == scanf("%Lf%Lf%lld", &p, &q, &n)) {
		//a(p-a) = q
		//-a^2+pa-q=0
		long double A = -1, B = p, C = -q;
		long double delta = B * B - 4 * A * C;
		Comp root = Comp(-B, 0);
		//(-B+sqrt(delta)) / 2A
		if(delta >= 0) root += Comp(sqrtl(delta),0);
		else root += Comp(0,sqrtl(-delta));
		root /= 2 * A;

		// printf("%.0Lf %.0Lf\n", root.real(), root.imag());
		printf("%.0Lf\n", (fpm(root, n) + fpm(Comp(p, 0) - root, n)).real());
	}	
	return 0;
}

/* 
a list of keywords 
clear empty push_back pop_back push pop top front back
emplace_back emplace push_front pop_front insert erase
find count set reset bitset map vector string multiset
first second iterator prev next deque multimap reverse
*/
```


---

## 作者：梧桐灯 (赞：1)

此题有一个坑点：

如果循环判断条件是

while (a+b != 0 且 ab != 0){}

是不行的，因为输入可能包括0 0 n

即a+b &&ab可能等于0.

其他没什么，楼下（上）推导十分详细就不赘述了。

还有，千万不要因为怕爆long long而使用unsigned long long！

还是贴一下代码吧，~~但我的矩阵加速有点丑~~

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;
ll a, b, n;

struct stu {
	ll a, b, c, d;
	inline stu operator * (const stu& p) const {
		stu r;
		r.a = a * p.a + b * p.c;
		r.b = a * p.b + b * p.d;
		r.c = c * p.a + d * p.c;
		r.d = c * p.b + d * p.d;
		return r;
	}
};

inline stu ksm (ll x) {
	stu p = {a, -b, 1, 0}, s = {1, 0, 0, 1};
	while (x) {
		if (x & 1) s = s * p;
		p = p * p;
		x >>= 1;
	}
	return s;
}

inline ll anksm (ll p, ll x) {
	ll ans = 1;
	while (x) {
		if (x & 1) ans *= p;
		p *= p;
		x >>= 1;
	}
	return ans;
}

int main () {
	cin >> a >> b;
	while (cin >> n) {
		if (n == 0) puts ("2");
		else if (n == 1) cout << a << '\n';
		else {
			stu ans = ksm (n - 1);
			cout << ans.a * a + ans.b * 2 << '\n';
		}
		cin >> a >> b;
	}
	return 0;
}
```

---

## 作者：D2T1 (赞：0)

题意：给你 $p=a+b,q=ab,n$，求出 $a^n+b^n$。

## Step 1.

可以发现 $a^n+b^n=(a+b)(a^{n-1}+b^{n-1})-ab(a^{n-2}+b^{n-2})$（$n>2$）,其实这里 $n=2$ 也没多大关系，虽然在这里出现 $0^0$，但实际运算时不会出现。

设 $S_k=a^k+b^k$，就会出现一个递推式：

$$
\begin{cases}
2&if ~k=0\\
p&if~k=1\\
pS_{k-1}-qS_{k-2}&if~k\geq2
\end{cases}
$$

化成矩阵

$$
\begin{bmatrix}S_{k-1}&S_{k-2}\end{bmatrix}
\begin{bmatrix}p&1\\-q&0\end{bmatrix}=
\begin{bmatrix}S_{k}&S_{k-1}\end{bmatrix}
$$

所以

$$
\begin{bmatrix}S_1&S_0\end{bmatrix}
\begin{bmatrix}p&1\\-q&0\end{bmatrix}^{n-1}=
\begin{bmatrix}S_{n}&S_{n-1}\end{bmatrix}
$$

套矩阵快速幂即可。

## Step 2.

接下来，才是题目的难点——**读入**。

你提交了代码，发现自己出现奇怪的错误，又打开了Udebug，发现了这么一组神奇的数据：

```
0 0 1
0 0 100
0 0 200000000
1 3 0
...
0 0
```

是的，如果一行有三个数，前两个是 $0$，不算结束。那怎么办呢？可以利用 `scanf` 函数返回值：

> `scanf()` 函数返回的值为：正确按指定格式输入变量的个数；也即能正确接收到值的变量个数。

如果返回 $2$ 再退出。

## Step 3.

记得特判 $n<2$ 的情况。

```cpp
//UVA10655
#include <bits/stdc++.h>
using namespace std;

//give a+b, ab, n, get a^n+b^n 

struct matrix{ long long a, b, c, d; } mat;

matrix mul(matrix x, matrix y){
	matrix z;
	z.a = x.a*y.a + x.b*y.c;
	z.b = x.a*y.b + x.b*y.d;
	z.c = x.c*y.a + x.d*y.c;
	z.d = x.c*y.b + x.d*y.d;
	return z;
}
matrix qp(matrix a, long long b){
	matrix ans = a; -- b;
	while(b){
		if(b&1) ans = mul(ans, a);
		a = mul(a, a);
		b >>= 1;
	}
	return ans;
}

int main(){
	long long p, q, n;
	while(scanf("%lld%lld%lld", &p, &q, &n)==3){
		mat.a = p, mat.b = 1, mat.c = -q, mat.d = 0;
		if(n == 0){ printf("%lld\n", 2); continue; }
		if(n == 1){ printf("%lld\n", p); continue; }
		mat = qp(mat, n-1);
		printf("%lld\n", mat.a*p+mat.c*2);
	}
	return 0;
}
```

---

