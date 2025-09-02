# Yet Another Number Sequence

## 题目描述

Everyone knows what the Fibonacci sequence is. This sequence can be defined by the recurrence relation:

 $ F_{1}=1,F_{2}=2,F_{i}=F_{i-1}+F_{i-2} (i&gt;2). $ We'll define a new number sequence $ A_{i}(k) $ by the formula:

 $ A_{i}(k)=F_{i}×i^{k} (i>=1). $ In this problem, your task is to calculate the following sum: $ A_{1}(k)+A_{2}(k)+...+A_{n}(k) $ . The answer can be very large, so print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 1
```

### 输出

```
34
```

## 样例 #3

### 输入

```
5 2
```

### 输出

```
316
```

## 样例 #4

### 输入

```
7 4
```

### 输出

```
73825
```

# 题解

## 作者：Poncirus (赞：19)

### Description

#### 题意简述

设 $F_i$ 表示Fibonacci数列的第 $i$ 项，即 $F_1=1,F_2=2,F_i=F_{i-1}+F_{i-2}$。

设 $A_i=F_i\times i^k(k\leqslant 40)$，你的任务是求出其前 $n$ 项和 $(n\leqslant 10^{18})\bmod 10^9+7$ 的结果。

### Solution

注意到Fibonacci，$n\leqslant 10^{18}$ 等关键词，明摆着就是一道矩阵加速嘛。

但是，，，$(i-1)^k$ 怎么转移到 $i^k$ 呢？

BDFS了一大堆后，发现了方法：二项式定理。

$k$ 那么小，那你干脆把 $(i-1)^1,(i-1)^2,(i-1)^3,\cdots,(i-1)^k$ 丢到初始矩阵里去不就行了？

顺便还得把 $i^1,i^2,i^3,\cdots,i^k$ 丢进去，然后 $(i-1)^x$ 就可以直接转换成 $i^x$。

那么 $i^x$ 也得转换为 $(i+1)^x$，所以关键在于 $i^x$ 怎么转换为 $(i+1)^x$。

* 那这不是又回到原问题上了吗！

* 咱不要急，先慢慢看

经过作者一阵乱搞，发现矩阵乘法是处理不了 $A_i$ 的。

所以只能把矩阵里的 $i^1,i^2,\cdots,i^k$ 都乘上一个 $F_i$ 来充数。

那么我们看一看 $F_{i+1}\times(i+1)^k$ 是怎么得到的：
$$
\begin{aligned}
F_{i+1}\times(i+1)^k&=(F_{i-1}+F_i)\times(i+1)^k\\
&=F_{i-1}\times(i+1)^k+F_i\times(i+1)^k\\
&=F_{i-1}\times[(i-1)+2]^k+F_i\times[(i)+1]^k
\end{aligned}
$$
是时候亮出二项式定理了！

我们都知道，二项式定理是一个酱紫的东西：
$$
(x+y)^k=\sum\limits_{i=0}^kC_k^ix^iy^{k-i}
$$
代入到 $[(i-1)+2]^k$ 中来，就是：
$$
[(i-1)+2]^x=\sum\limits_{j=0}^xC_x^j(i-1)^j2^{x-j}
$$
而我们刚好有 $(i-1)^j$。

$C_x^j\times2^{x-j}$ 就是 $(i-1)^j$ 在加速矩阵里对应的系数。

又代入到 $[(i)+1]^x$ 中，得：
$$
[(i)+1]^x=\sum\limits_{j=0}^xC_x^ji^j
$$
挺巧的，我们也有 $i^j$。

$C_x^j$ 就是 $i^j$ 在加速矩阵中对应的系数。

设 $S_x=\sum\limits_{i=1}^xA_i$。

那么初始矩阵就长这样：
$$
[F_1,F_2,S_1,F_1\times1^1,F_1\times 1^2,\cdots,F_1\times1^k,F_2\times2^1,F_2\times2^2,\cdots,F_2\times2^k]
$$
转移一步后长这样：
$$
[F_2,F_3,S_3,F_2\times2^1,F_2\times2^2,\cdots,F_2\times2^k,F_3\times3^1,F_3\times3^2,\cdots,F_3\times3^k]
$$
转移 $n-1$ 步后的最终矩阵长这样：
$$
[F_n,F_{n+1},S_n,F_n\times n^1,F_n\times n^2,\cdots,F_n\times n^k,F_{n+1}\times(n+1)^1,F_{n+1}\times(n+1)^2,\cdots,F_{n+1}\times(n+1)^k]
$$
加速矩阵长这样：
$$
\begin{bmatrix}
&F_i&F_{i+1}&S_i&F_i\times i^1&F_i\times i^2&\cdots&F_i\times i^k&F_{i+1}\times(i+1)^1&F_{i+1}\times(i+1)^2&\cdots&F_{i+1}\times(i+1)^k
\\
F_{i-1}(\times(i-1)^0)&0&1&0&0&0&\cdots&0&2^{1-0}\times C_1^0=2&2^{2-0}\times C_2^0=4&\cdots&2^{k-0}\times C_k^0\\
F_{i}(\times i^0)&1&1&0&0&0&\cdots&0&C_1^0=1&C_2^0=1&\cdots&C_k^0\\
S_{i-1}&0&0&1&0&0&\cdots&0&0&0&\cdots&0\\
F_{i-1}\times(i-1)^1&0&0&0&0&0&\cdots&0&2^{1-1}\times C_1^1=1&2^{2-1}\times C_2^1=4&\cdots&2^{k-1}\times C_k^1\\
F_{i-1}\times(i-1)^2&0&0&0&0&0&\cdots&0&0&2^{2-2}\times C_2^2=1&\cdots&2^{k-2}\times C_k^2\\
\cdots&\vdots&\vdots&\vdots&\vdots&\vdots&\cdots&\vdots&\vdots&\vdots&\cdots&\vdots\\
F_{i-1}\times(i-1)^k&0&0&0&0&0&\cdots&0&0&0&\cdots&2^{k-k}\times C_k^k\\
F_i\times i^1&0&0&0&1&0&\cdots&0&C_1^1=1&C_2^1=2&\cdots&C_k^1\\
F_i \times i^2&0&0&0&0&1&\cdots&0&0&C_2^2=1&\cdots&C_k^2\\
\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\cdots&\vdots&\vdots&\vdots&\cdots&\vdots\\
F_i\times i^k&0&0&1&0&0&\cdots&0&0&0&\cdots&C_k^k
\end{bmatrix}
$$


（这个$\LaTeX$ 是给人打的吗。。。）

好了，除了初始化麻烦点，代码还是比较简单的。

### Code


时间复杂度 $\mathcal O($能过$)$

感谢@w23c3c3 大巨佬让我逃离了手推 $k=40$ 大数据然后真·清明节快乐的厄运。

```cpp
#include<cstdio>
#include<cstring>
#define int long long
const int mod=1e9+7;
const int maxn=105;
struct Matrix{
	int n,m;
	int c[maxn][maxn]; 
	Matrix(int N=0,int M=0){
		n=N,m=M;
		memset(c,0,sizeof(c));
	}
	Matrix operator*(const Matrix a)const{
		int l=n,r=a.m;
		Matrix x=Matrix(l,r);
		for(int i=1;i<=l;++i){
			for(int j=1;j<=r;++j){
				for(int k=1;k<=m;++k){
					x.c[i][j]+=c[i][k]*a.c[k][j];
					x.c[i][j]%=mod;
				}
			}
		}
		return x;
	}
}A,B;
int n,k,x=4;
int f[45][45]; 
Matrix pow(Matrix&x,int b){
	Matrix ans=Matrix(x.n,x.m);
	for(int i=1;i<=x.m;++i)
        ans.c[i][i]=1;
	while(b){
		if(b&1)
			ans=x*ans;
		x=x*x;
		b>>=1;
	}
	return ans;
}
inline void init(void){
	f[0][0]=1;
	for(int i=1;i<=k;++i){
        f[i][0]=1;
		for(int j=1;j<=i;++j)
			f[i][j]=(f[i-1][j-1]+f[i-1][j])%mod;
	}
    return;
}
signed main(){
    scanf("%lld%lld",&n,&k);
    init();
    A=Matrix(1,3+(k<<1));
    A.c[1][1]=1;A.c[1][2]=2;A.c[1][3]=1;
    for(int i=1;i<=k;++i){
        A.c[1][3+i]=1;
        A.c[1][k+3+i]=x%mod;
        x<<=1;
    }
    B=Matrix(3+(k<<1),3+(k<<1));
    B.c[2][1]=1;
    B.c[1][2]=B.c[2][2]=1;
    B.c[3][3]=B.c[3+(k<<1)][3]=1;
    for(int i=1;i<=k;++i){
        B.c[1][i+k+3]=(1ll<<i)%mod;
        B.c[3+k+i][3+i]=1;
        B.c[2][3+i+k]=1;
    }
    for(int i=1;i<=k;++i){
        for(int j=i;j<=k;++j){
            B.c[3+i][3+k+j]=(((1ll<<j-i)%mod)*f[j][i])%mod;
            B.c[3+k+i][3+k+j]=f[j][i];
        }
    }
    A=A*pow(B,n-1);
    printf("%lld",A.c[1][3]);
    return 0;
}
```

---

## 作者：Aleph1022 (赞：12)

不妨令 $F_0=1$，那么 $F_i = F_{i-1}+F_{i-2}$ 就对所有 $i\ge 1$ 满足。  
然后我们考虑求出
$$
F(z) = \frac1{1-z-z^2} \bmod z^{n+1} = \sum\limits_{i=0}^n F_i z^i
$$

那么其显然要在 $n+1,n+2$ 处去除贡献。即
$$
\begin{aligned}
F(z) &= zF(z) + z^2F(z) + 1 - (F_{n-1}+F_n)z^{n+1} - F_nz^{n+2} \\
F(z) &= \frac{1 - (F_{n-1}+F_n)z^{n+1} - F_nz^{n+2}}{1-z-z^2}
\end{aligned}
$$

则答案就是
$$
\begin{aligned}
\sum\limits_{i=0}^n F_i i^k
&= \left[\frac{z^k}{k!}\right] \sum\limits_{i=0}^n F_i \mathrm e^{iz} \\
&= \left[\frac{z^k}{k!}\right] F(\mathrm e^z)
\end{aligned}
$$

设 $\mathscr F(z + 1) = F(z+1) \bmod z^{k+1}$。  
令 $P(z) = 1 - (F_{n-1}+F_n)z^{n+1} - F_nz^{n+2}$，则
$$
\begin{aligned}
F(z+1) &= -\frac{P(z+1)}{1+3z+z^2} \\
\left([z^i] F(z+1)\right) &= -\left([z^i] P(z+1)\right) - 3\left([z^{i-1}] F(z+1)\right) - \left([z^{i-2}] F(z+1)\right)
\end{aligned}
$$

则令 $\mathscr P(z+1) = P(z+1) \bmod z^{k+1}$，先求 $\mathscr P(z)$，主要是要考虑
$$
\mathscr G_m(z+1) = (1+z)^m \bmod z^{k+1}
$$

考虑
$$
\begin{aligned}
(1+z)[(1+z)^m]' &= m(1+z)^m \\
(1+z)[\mathscr G_m(z+1)]' &= m\mathscr G_m(z+1) - (m-k) \binom mk z^k \\
z\mathscr G_m'(z) &= m\mathscr G_m(z) - (m-k) \binom mk (z-1)^k
\end{aligned}
$$

从而可以求出 $\mathscr P(z)$。

而
$$
\begin{aligned}
&\quad\;\left([z^i] \mathscr F(z+1)\right) \\
&= -\left([z^i] \mathscr P(z+1)\right) - 3\left([z^{i-1}] \mathscr F(z+1)\right) - \left([z^{i-2}] \mathscr F(z+1)\right) \\
&+ [i=k+1]\left[3\left([z^k] \mathscr F(z+1)\right) + \left([z^{k-1}] \mathscr F(z+1)\right)\right] \\
&+ [i=k+2]\left([z^k] \mathscr F(z+1)\right)
\end{aligned}
$$

不妨令 $C_1 = \left[3\left([z^k] \mathscr F(z+1)\right) + \left([z^{k-1}] \mathscr F(z+1)\right)\right]$，$C_2 = \left([z^k] \mathscr F(z+1)\right)$，则
$$
\mathscr F(z+1) = \frac{-\mathscr P(z+1)+C_1 z^{k+1}+C_2 z^{k+2}}{1+3z+z^2}
$$

即
$$
\mathscr F(z) = \frac{\mathscr P(z) - C_1(z-1)^{k+1} - C_2(z-1)^{k+2}}{1-z-z^2}
$$

根据 EI 的结果，$[z^k] F(\mathrm e^z) = [z^k] \mathscr F(\mathrm e^z)$。线性求出 $\mathscr F(z)$ 即可。  
时间复杂度 $\Theta(k + \log n)$。

代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int K = 42;
const int mod = 1e9 + 7;
inline int norm(int x)
{
    return x >= mod ? x - mod : x;
}
inline int reduce(int x)
{
    return x < 0 ? x + mod : x;
}
inline int neg(int x)
{
    return x ? mod - x : 0;
}
inline void add(int &x,int y)
{
    if((x += y - mod) < 0)
        x += mod;
}
inline void sub(int &x,int y)
{
    if((x -= y) < 0)
        x += mod;
}
inline void fam(int &x,int y,int z)
{
    x = (x + (long long)y * z) % mod;
}
inline int fpow(int a,int b)
{
    int ret = 1;
    for(;b;b >>= 1)
        (b & 1) && (ret = (long long)ret * a % mod),a = (long long)a * a % mod;
    return ret;
}
long long n;
int k;
int F_n_1,F_n;
inline int bostanMori(long long n,int p0,int p1,int q0,int q1,int q2)
{
    for(;n;n >>= 1)
    {
        if(n & 1)
            p0 = ((long long)q0 * p1 + (long long)(mod - q1) * p0) % mod,
            p1 = (long long)q2 * p1 % mod;
        else
            p1 = ((long long)q2 * p0 + (long long)(mod - q1) * p1) % mod,
            p0 = (long long)q0 * p0 % mod;
        q1 = (2LL * q0 * q2 + (long long)(mod - q1) * q1) % mod,
        q0 = (long long)q0 * q0 % mod,
        q2 = (long long)q2 * q2 % mod;
    }
    return q0 == 1 ? p0 : (long long)p0 * fpow(q0,mod - 2) % mod;
}
int vis[K + 5],cnt,prime[K + 5],pw[K + 5];
int fac[K + 5],ifac[K + 5],inv[K + 5];
int prod[K + 5],iprod[K + 5],inv_n_2[K + 5];
int C_n_1_k,C_n_2_k;
int C_1,C_2;
int G_n_1[K + 5],G_n_2[K + 5];
int P[K + 5],F[K + 5];
int ans;
inline int C(int n,int m)
{
    return n < m || m < 0 ? 0 : (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int main()
{
    scanf("%lld%d",&n,&k);
    pw[1] = 1;
    for(int i = 2;i <= k;++i)
    {
        if(!vis[i])
            pw[prime[++cnt] = i] = fpow(i,k);
        for(int j = 1;j <= cnt && i * prime[j] <= k;++j)
        {
            vis[i * prime[j]] = 1,pw[i * prime[j]] = (long long)pw[i] * pw[prime[j]] % mod;
            if(!(i % prime[j]))
                break;
        }
    }
    if(n <= k)
    {
        F[0] = 1;
        for(int i = 0;i <= n;++i)
            i && (add(F[i],F[i - 1]),1),
            i > 1 && (add(F[i],F[i - 2]),1),
            fam(ans,F[i],pw[i]);
        printf("%d\n",ans);
        return 0;
    }
    F_n_1 = bostanMori(n - 1,1,0,1,mod - 1,mod - 1),
    F_n = bostanMori(n,1,0,1,mod - 1,mod - 1),
    add(F_n_1,F_n);
    n %= mod;
    prod[0] = norm(n + 2);
    for(int i = 1;i <= k + 1;++i)
        prod[i] = prod[i - 1] * (n + 2 - i + mod) % mod;
    iprod[k + 1] = fpow(prod[k + 1],mod - 2);
    for(int i = k + 1;i;--i)
        iprod[i - 1] = iprod[i] * (n + 2 - i + mod) % mod;
    for(int i = 1;i <= k + 1;++i)
        inv_n_2[i] = (long long)iprod[i] * prod[i - 1] % mod;
    inv_n_2[0] = iprod[0];
    fac[0] = 1;
    for(int i = 1;i <= k + 2;++i)
        fac[i] = (long long)fac[i - 1] * i % mod;
    ifac[k + 2] = fpow(fac[k + 2],mod - 2);
    for(int i = k + 2;i;--i)
        ifac[i - 1] = (long long)ifac[i] * i % mod;
    for(int i = 1;i <= k + 1;++i)
        inv[i] = (long long)ifac[i] * fac[i - 1] % mod;
    C_n_1_k = C_n_2_k = 1;
    C_2 = norm(F_n_1 + F_n),sub(C_2,1);
    for(int i = 1,C_t;i <= k;++i)
        C_n_1_k = C_n_1_k * (n - i + 2 + mod) % mod * inv[i] % mod,
        C_n_2_k = C_n_2_k * (n - i + 3 + mod) % mod * inv[i] % mod,
        C_t = ((long long)F_n_1 * C_n_1_k + (long long)F_n * C_n_2_k - 3LL * C_2 - C_1 + 4LL * mod) % mod,
        C_1 = C_2,C_2 = C_t;
    fam(C_1,3,C_2);
    C_n_1_k = C_n_1_k * (n - k + 1 + mod) % mod,
    C_n_2_k = C_n_2_k * (n - k + 2 + mod) % mod;
    for(int i = 0;i <= k;++i)
        G_n_1[i] = (long long)(k - i & 1 ? mod - C_n_1_k : C_n_1_k) * C(k,i) % mod * inv_n_2[i + 1] % mod,
        G_n_2[i] = (long long)(k - i & 1 ? mod - C_n_2_k : C_n_2_k) * C(k,i) % mod * inv_n_2[i] % mod,
        P[i] = ((long long)F_n_1 * G_n_1[i] + (long long)F_n * G_n_2[i]) % mod,
        P[i] = neg(P[i]);
    add(P[0],1);
    for(int i = 0;i <= k;++i)
        F[i] = ((long long)(k - i & 1 ? mod - C_1 : C_1) * C(k + 1,i) + (long long)(k - i & 1 ? C_2 : mod - C_2) * C(k + 2,i)) % mod,
        add(F[i],P[i]),
        i && (add(F[i],F[i - 1]),1),
        i > 1 && (add(F[i],F[i - 2]),1),
        fam(ans,F[i],pw[i]);
    printf("%d\n",ans);
}
```

---

## 作者：iostream (赞：7)

发一个复杂度优秀的做法

设$F(n,m)$表示$\sum_{i=1}^n G^i*i^m$

其中$G[2][2]$是斐波那契的转移矩阵

显然答案为$F(N,K)$

直接递推求$F(N,K)$复杂度显然不可接受。

考虑快速幂形式的倍增：

$$F(2n,m)$$
$$=\sum_{i=1}^{2n} G^i*i^m$$
$$=\sum_{i=1}^n G^i*i^m + G^n\sum_{i=1}^n G^i*(i+n)^m$$
$$=F(n,m)+G^n\sum_{i=1}^n G^i\sum_{j=0}^m \dbinom{m}{j} i^j n^{m-j}$$
$$=F(n,m)+G^n\sum_{j=0}^m \dbinom{m}{j} n^{m-j}\sum_{i=1}^n G^ii^j$$
$$=F(n,m)+G^n\sum_{j=0}^m \dbinom{m}{j} n^{m-j} F(n,j)$$

对$i$维护$F(i,0...m)$
然后做快速幂
复杂度$O(8KlogN)$

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

const int N=45;
const int mod=1000000007;

ll n;
int k;
int w[N],C[N][N];

int fpow(int a,int b)
{
	int r(1);
	while(b) {
		if(b&1) r=(ll)r*a%mod;
		a=(ll)a*a%mod;
		b>>=1;
	}
	return r;
}

struct mat {
	int a[2][2];
	mat(int o=0) {
		a[0][0]=a[1][1]=o;
		a[0][1]=a[1][0]=0;
	}
	void operator*=(const mat&y)
	{
	    static ll Tmp[N][N];
		int i,j,k;
		for(i=0; i<2; i++)
			for(j=0; j<2; j++)
				for(Tmp[i][j]=k=0; k<2; k++)
					Tmp[i][j] += (ll)a[i][k]*y.a[k][j];
		for(i=0; i<2; i++)
			for(j=0; j<2; j++)
				a[i][j]=Tmp[i][j] % mod;
	}
	void operator+=(const mat&y)
	{
		int i,j;
		for(i=0; i<2; i++)
			for(j=0; j<2; j++)
				a[i][j]=(a[i][j]+y.a[i][j])%mod;
	}
	void operator*=(const int y)
	{
		int i,j;
		for(i=0; i<2; i++)
			for(j=0; j<2; j++)
				a[i][j]=(ll)a[i][j]*y%mod;
	}
}a,b[N],t[N],tmp;

mat fpow(const mat &a,ll n)
{
	mat x=mat(1);
	mat y=a;
	while(n)
	{
		if(n&1)x*=y;
		y*=y;
		n>>=1;
	}
	return x;
}

void init()
{
	C[0][0]=1;
	for(int i=1; i<=k; i++)
	{
		C[i][0]=1;
		for(int j=1; j<=i; j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}

void solve(ll n)
{
	if(n==1)
	{
		for(int i=0; i<=k; i++)
			b[i]=a;
		tmp=a;
		return;
	}
	ll mid=n>>1;
	solve(mid);
	for(int i=0; i<=k; i++)
	{
		t[i]=b[i];
		b[i]=mat();
	}
	w[0]=1;
	for(int i=1,o=mid%mod; i<=k; i++)
		w[i]=(ll)w[i-1]*o%mod;
	for(int i=0; i<=k; i++)
	{
		for(int j=0; j<=i; j++)
		{
			mat now=t[j];
			now*=((ll)C[i][j]*w[i-j]%mod);
			b[i]+=now;
		}
		b[i]*=tmp;
	}
	for(int i=0; i<=k; i++)
		b[i]+=t[i];
	tmp*=tmp;
	if(n&1)
	{
		tmp*=a;
		w[0]=1;
		for(int i=0,o=n%mod; i<=k; i++)
		{
			t[i]=tmp;
			t[i]*=w[0];
			b[i]+=t[i];
			w[0]=(ll)w[0]*o%mod;
		}
	}
}

int main()
{
	scanf("%lld %d",&n,&k);
	
	a.a[0][0] = a.a[0][1] = a.a[1][0] = 1;
	a.a[1][1] = 0;
	
//	fprintf(stderr, "%d\n", fpow(a, 4).a[0][0]);
	
	init();
	
	solve(n);
	
	printf("%d", b[k].a[0][0]); 
	return 0;
}

---

## 作者：toolazy (赞：3)

见数据范围知算法，很明显，**矩阵快速幂**！

但是矩阵快速幂只能解决 **线性递推** 的问题，所以我们需要**转化**！

怎么转呢？自已观察题目，可以发现最棘手的问题在这里：

$A_i(k)=\color{orangered}i^k\color{black}F_i$

这里因为 $\color{orangered}i^k$ 的存在导致我们无法简单地转移，怎么办呢？

既然是 **线性递推** ，我们就肯定要**拆解**，考虑使用 **二项式定理** 展开！

接下来使用二项式定理展开 $(i+1)^k$，来思考一下矩阵中需要保留的元素：

$\begin{aligned}(i+1)^k=\sum^k_{n=0}\color{orangered}C_k^n\color{#AA00AA}i^n\end{aligned}$

可以发现，转移需要所有的 $\color{#AA00AA}i^n\color{black}(n\le k)$ ，而系数 $\color{orangered}C_k^n\color{black}(n\le k)$ 都可以提前计算，并保存到矩阵中！

那不就简单了，带上 $F_{i+1}$ 再来试一下：

$\begin{aligned}
(i+1)^kF_{i+1}&=(i+1)^kF_{i-1}+(i+1)^kF_i\\
&=[(i-1)+2]^kF_{i-1}+(i+1)^kF_i\\
&=\sum_{n=0}^k\color{orangered}2^{k-n}C_k^n\color{#AA00AA}(i-1)^nF_{i-1}\color{black}+\sum_{n=0}^k\color{orangered}C_k^n\color{#AA00AA}i^nF_i
\end{aligned}$

可以看到，我们只需要同时保留 $\color{#AA00AA}(i-1)^nF_{i-1}\color{black}(n\le k)$ 和 $\color{#AA00AA}i^nF_i\color{black}(n\le k)$，它们的形式都是一样的，至于两种系数 $\color{orangered}2^{k-n}C_k^n\color{black}(n\le k)$ 和 $\color{orangered}C_k^n\color{black}(n\le k)$ 也可以提前计算存矩阵中！

那么我们就可以开始了！矩阵就定义成这样吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/ojcufevq.png)

那么递推方程就应该长这样，照着上面的式子写，分分块，挺有规律的：

![](https://cdn.luogu.com.cn/upload/image_hosting/emexjzom.png)

之中还有很多有趣的东西：

- 第一区的 $1$，表示 $S$ 的递增。
- 第二、三区的 全零矩阵 ，表示 $(i-1)^nF_{i-1}$ 和 $i^nF_i$ 的转移与 $S$ 无关。
- 第八区的 单位矩阵 ，表示一次转移之后 $(i-1)^nF_{i-1}$ 直接被对应的 $i^nF_i$ 所覆盖。类似的，第五区的 全零矩阵 表示直接抛弃。
- **第九区就是 杨辉三角 ！**
- $F_i$ 对应的一列（上图中第三、六、九区最左边列）中只有两个 $1$，这正好对应了普通的 斐波那契数列 的递推矩阵

还有很多，你愿意的话可以自己发掘一下~

最后附上代码，~~带空格属于是老年人码风力~~：

```C++
#include <iostream>
#include <cstring>
using namespace std;

#define int unsigned long long
#define mod 1000000007

#define MATRIXSIZE 125
struct matrix {
	int m[MATRIXSIZE][MATRIXSIZE], w, h;
	matrix(int width, int height) : w(width), h(height) {
		memset(m, 0, sizeof(m));
	}
	int * operator [] (int p) {
		return m[p];
	}
	matrix operator * (matrix x) const {
		matrix res(x.w, h);
		for (int a = 1; a <= h; a ++)
			for (int b = 1; b <= x.w; b ++)
				for (int c = 1; c <= w; c ++)
					res[a][b] = (res[a][b] +
						m[a][c] * x[c][b] % mod) % mod;
		return res;
	}
	matrix operator ^ (int k) const {
		matrix res(w, w), times(*this);
		for (int i = 1; i <= w; i ++)
			res[i][i] = 1;
		while (k) {
			if (k & 1)
				res = res * times;
			times = times * times;
			k >>= 1;
		}
		return res;
	}
	void output() const {
		cout << "width: " << w << endl;
		cout << "height: " << h << endl;
		for (int i = 1; i <= 2; i ++) {
			cout << "[ ";
			for (int j = 1; j <= w; j ++)
				cout << m[i][j] << ' ';
			cout << ']' << endl;
		}
	}
};

int n, k;

int solvo() {
	int siz = 1 + ((++ k) << 1);
	matrix res(siz, 1), times(siz, siz);
	
	res[1][1] = res[1][2] = 1;
	for (int i = 2 + k; i <= siz; i ++)
		res[1][i] = 1;
	
	// 第一区
	times[1][1] = 1;
	
	// 第八区
	for (int i = 2; i <= 1 + k; i ++)
		times[i + k][i] = 1;
	
	// 第九区
	times[2 + k][2 + k] = 1;
	for (int i = 3 + k; i <= siz; i ++)
		for (int j = 2 + k; j <= i; j ++)
			times[j][i] = (times[j][i - 1] + times[j - 1][i - 1]) % mod;
	
	// 第六区
	for (int i = 2; i <= 1 + k; i ++)
		for (int j = i + k; j <= siz; j ++)
			times[i][j] = (times[i + k][j] << (j - i - k)) % mod;
	
	// 第四及第七区
	for (int i = 2; i <= siz; i ++)
		times[i][1] = times[i][siz];
	
	times = times ^ (n - 1);
	res = res * times;
	return res[1][1];
}

main() {
	cin >> n >> k;
	cout << solvo();
	return 0;
}
```

拜拜~

---

## 作者：Weng_Weijie (赞：3)

题解：

设$ f(n,k)=\displaystyle\sum_{i=1}^nF_ii^k$

为了方便，令$ F_0=1,F_{-1}=0 $

$$f(n,k)=\sum_{i=1}^nF_ii^k$$

$$=\sum_{i=1}^n(F_{i-1}+F_{i-2})i^k$$

二项式定理展开

$$=\sum_{i=1}^nF_{i-1}\sum_{j=0}^k(i-1)^j\binom kj+\sum_{i=1}^nF_{i-2}\sum_{j=0}^k\binom kj(i-2)^j2^{k-j}$$

交换求和顺序

$$=\sum_{j=0}^k\binom kj\sum_{i=1}^nF_{i-1}(i-1)^j+\sum_{j=0}^k\binom kj2^{k-j}\sum_{i=1}^nF_{i-2}(i-2)^j$$

这一步需要注意一下边界情况，$F_0=1,0^0=1$

$$=\sum_{j=0}^k\binom kj\sum_{i=1}^{n-1}F_ii^j+1+\sum_{j=0}^k\binom kj2^{k-j}\sum_{i=1}^{n-2}F_ii^j+2^k$$

$$=\sum_{j=0}^k\binom kjf(n-1,j)+\sum_{j=0}^k\binom kj2^{k-j}f(n-2,j)+2^k+1$$

矩阵快速幂优化即可，注意一下初始状态

时间复杂度 $O(k^3\log n)$

```cpp
#include <iostream>
const int mod = 1000000007;
using LL = long long;
int k, C[50][50], pow[50], num[2][50], K, tot;
void up(int &x, int y) { if ((x += y) >= mod) x -= mod; }
struct matrix {
	int num[83][83];
	matrix operator * (matrix rhs) const {
		matrix res;
		for (int i = 0; i <= K; i++)
			for (int j = 0; j <= K; j++) {
				int ans = 0;
				for (int k = 0; k <= K; k++) up(ans, static_cast<LL> (num[i][k]) * rhs.num[k][j] % mod);
				res.num[i][j] = ans;
			}
		return res;
	}
} base, init;
LL n;
int main() {
	std::cin >> n >> k; K = 2 * k + 2;
	for (int i = 0; i <= k + 1; i++) pow[i] = (1LL << i) % mod;
	for (int i = 0; i <= k; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			up(C[i][j] = C[i - 1][j - 1], C[i - 1][j]);
		}
	}
	for (int i = 0; i < 2; i++) for (int j = 0; j <= k; j++) num[i][j] = tot++;
	for (int j = 0; j <= k; j++) {
		for (int p = 0; p <= j; p++)
			base.num[num[0][p]][num[0][j]] = C[j][p];
		for (int p = 0; p <= j; p++)
			base.num[num[1][p]][num[0][j]] = static_cast<LL> (C[j][p]) * pow[j - p] % mod;
		base.num[K][num[0][j]] = pow[j] + 1;
		base.num[num[0][j]][num[1][j]] = 1;
	}
	base.num[K][K] = 1;
	for (int j = 0; j <= k; j++) {
		init.num[0][num[0][j]] = (1 + pow[j + 1]) % mod;
		init.num[0][num[1][j]] = 1;
	}
	init.num[0][K] = 1;
	if (n == 1) std::printf("%d\n", init.num[0][num[1][k]]);
	else {
		for (----n; n; n >>= 1, base = base * base) if (n & 1) init = init * base;
		std::printf("%d\n", init.num[0][num[0][k]]);
	}
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

~~应为是数列，所以考虑矩阵快速幂~~

这个题目本身看起来不能使用矩阵快速幂，但是仔细看看到 $k$ 特别小，可以保存所有 $F_i*i^x$ 在一个状态里。

我们的状态是

$$\begin{pmatrix}S(i)\\F_i\\F_i*i\\F_i*i^2\\F_i*i^3\\F_{i+1}\\F_{i+1}*(i+1)\\F_{i+1}*(i+1)^2\\F_{i+1}*(i+1)^3\end{pmatrix}$$

并且希望从

$$\begin{pmatrix}S(i-1)\\F_{i-1}\\F_{i-1}*(i-1)\\F_{i-1}*(i-1)^2\\F_{i-1}*(i-1)^3\\F_i\\F_i*i\\F_i*i^2\\F_i*i^3\end{pmatrix}$$

前 $k+1$ 项可以直接移动到，但是后 $k$ 项需要更复杂的展开。

$$F_{i+1}*(i+1)^k=F_{i-1}*(i+1)^k+F_{i}*(i+1)^k$$
$$=F_{i-1}*((i-1)+2)^k+F_{i}*((i)+1)^k$$

应用二项式定理展开：

$$=\sum^k_{j=0}(\binom{k}{j}2^{j-k})[F_{i-1}*(i-1)^j]+\sum^k_{j=0}(\binom{k}{j})[F_i*i^j]$$

这些系数直接用 dp 放到转移矩阵里，得到一个类似于这样他矩阵：

$$\begin{pmatrix}S(i)\\F_i\\F_i*i\\F_i*i^2\\F_i*i^3\\F_{i+1}\\F_{i+1}*(i+1)\\F_{i+1}*(i+1)^2\\F_{i+1}*(i+1)^3\end{pmatrix}=\begin{pmatrix}1&0&0&0&0&0&0&0&1\\0&0&0&0&0&1&0&0&0\\0&0&0&0&0&0&1&0&0\\0&0&0&0&0&0&0&1&0\\0&0&0&0&0&0&0&0&1\\0&1&0&0&0&1&0&0&0\\0&2&1&0&0&1&1&0&0\\0&4&4&1&0&1&2&1&0\\0&8&12&6&1&1&3&3&1\end{pmatrix}\begin{pmatrix}S(i-1)\\F_{i-1}\\F_{i-1}*(i-1)\\F_{i-1}*(i-1)^2\\F_{i-1}*(i-1)^3\\F_i\\F_i*i\\F_i*i^2\\F_i*i^3\end{pmatrix}$$


简化成初始值：

$$\begin{pmatrix}S(n)\\F_n\\F_n*n\\F_n*n^2\\F_n*n^3\\F_{n+1}\\F_{n+1}*(n+1)\\F_{n+1}*(n+1)^2\\F_{n+1}*(n+1)^3\end{pmatrix}=\begin{pmatrix}1&0&0&0&0&0&0&0&1\\0&0&0&0&0&1&0&0&0\\0&0&0&0&0&0&1&0&0\\0&0&0&0&0&0&0&1&0\\0&0&0&0&0&0&0&0&1\\0&1&0&0&0&1&0&0&0\\0&2&1&0&0&1&1&0&0\\0&4&4&1&0&1&2&1&0\\0&8&12&6&1&1&3&3&1\end{pmatrix}^{n-1}\begin{pmatrix}1\\1\\0\\0\\0\\1\\1\\1\\1\end{pmatrix}$$

矩阵大小是 $2K+3$，所以总共复杂度是 $(2K+3)^3O(\log n)=O(K^3\log n)$，可过。

主要代码：

```cpp
int p2[42];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll n; int k; gi(n), gi(k);
	if(n==1) {
		pc('1');
		return 0;
	}
	matt v; v.init();
	p2[0] = 1;
	rep1(i, k+1) p2[i] = (p2[i-1]<<1)%MOD;
	v[0][0] = 1;
	rep(i, k+1) v[i+1][k+i+2] = 1;
	rep(i, k+1)
		rep(j, i+1) {
			if(!(i|j)) v[k+2][k+2] = 1;
			else v[k+i+2][k+j+2] = (v[k+i+1][k+j+1]+v[k+i+1][k+j+2])%MOD;
			v[k+i+2][j+1] = 1ll*v[k+i+2][k+j+2]*p2[i-j]%MOD;
		}
	rep1(i, 2*k+2) v[0][i] = v[2*k+2][i];
	matt i; i.init();
	i[0][0] = i[1][0] = 1;
	rep(r, k+1) i[k+r+2][0] = 1;
	print(qpow(v,n-1).mult(i)[0][0]);
}
```

---

## 作者：forest114514 (赞：2)

**CF392C Yet Another Number Sequence**

Aleph1022 大神的做法我不是很懂，这里分享一种思想简单但是细节比较多的 Binomial Sums 做法（做法一）。

**做法一：**

原题可以写成 $\frac{1}{\sqrt{5}}\sum\limits_{i=0}^{n}[(\frac{1+\sqrt 5}{2})^n-(\frac{1-\sqrt 5}{2})^n]i^k$，在 $\sqrt 5$ 有二次剩余的时候就和 P5907 一模一样了，那个题的做法可以看[我的题解](https://www.luogu.com.cn/article/sephh4td)。

但是 $\sqrt 5$ 在本题没有二次剩余，考虑扩域即可，可以做到 $O(k+\log n)$，考虑如果 $\log n$ 很大是没法接受的数的话你扩域的数 $(a+\sqrt 5b)^i$ 满足 $(a+\sqrt 5b)^{p^2}=a+\sqrt 5b$，可以做到 $O(k+\log p)$。

**做法二：**

其实还是可以根据斐波那契数列的 GF 直接截断然后得到 ODE 来做的，只是麻烦一点。

截断可以得到：
$$
(x^2+x-1)F(x)=(fib_{n-1}+fib_{n})x^{n+1}+fibx^{n+2}-1
$$
设右边那个为 $P(x)$，两边求导可以得到 ODE 为：
$$
(2x+1)F(x)+(x^2+x-1)F'(x)=P'(x)
$$
带入 $x+G(0)=x+1$ 得到：
$$
(2x+3)F(x+1)+(x^2+3x+1)F'(x+1)=P'(x+1)
$$
设 $\mathbb F(x)=F(x)\bmod x^{k+1},\mathbb P(x)=P(x)\bmod x^{k+1}$，就能截断得到：
$$
(2x+3)\mathbb F(x+1)+(x^2+3x+1)\mathbb F'(x+1)=\mathbb P'(x+1)+Ax^k+Bx^{k+1}
$$
其中 $A=(n+1)[x^{k-1}]F(x+1)+(3n+3)[x^k]F(x+1),B=(n+2)[x^k]F(x+1)$，对于 $F(x+1)$ 的某一项的系数其实就是求 $\sum\limits_{i=n}^{k}fib_i\binom{i}{n}$，直接扩域后就和 P5907 的某个部分一样的了，可以看我的题解。

后面带回 $x$ 就能得到：
$$
(2x+1)\mathbb F(x)+(x^2+x-1)\mathbb F'(x)=[\mathbb P(x+1)\circ (x-1)]'+A(x-1)^n+B(x-1)^{n+1}
$$
$[\mathbb P(x+1)\circ (x-1)]'$ 就是直接 $Tx^n\to (T(x+1)^k\bmod x^{n+1})\circ (x-1)$，处理方法还是和  P5907 相似，显然麻烦很多。

---

## 作者：_Katyusha (赞：2)

纪念一下完全凭借自己想出来的的第一道黑题。

### 思路

首先看到数据范围 $n\leq 10^{17}$ 就知道本题是矩阵快速幂或者推式子。

首先发现对于不同的 $i,j$ $f_i\times i^{k},f_j\times j^{k}$ 非常难合并，除非用出[斐波那契通项公式](https://baike.baidu.com/item/%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97/99145?fr=ge_ala)，所以放弃这条道路，走矩阵快速幂道路。

考虑一个最简单的初始矩阵：

$$\begin{bmatrix}{f_i\times i^k} &{f_{i+1}\times (i+1)^k}\end{bmatrix}$$

我们要转移到的目标矩阵：

$$\begin{bmatrix}{f_{i+1}\times {(i+1)}^k} &{f_{i+2}\times (i+2)^k}\end{bmatrix}$$

我们发现这是不可行的。因为 $(i+2)^k$ 不是 $(i+1)^k$ 且增广矩阵中的量必须为常数的缘故，转移到第一个数十分简单，但是第二个数就很困难了。

于是我们尝试着倒退，将 $f_{i+2}\times (i+2)^k$ 拆成与 $f_{i}\times i^k \ f_{i+1}
\times (i+1)^k$ 有关的数，并尝试将其加入初始矩阵与增广矩阵中。

$$f_{i+2}\times(i+2)^k$$



$$=f_{i}\times(i+2)^k+f_{i+1}\times (i+2)^k$$

由二项式定理：

$$(i+2)^k=((i+1)+1)^k=\sum\limits_{j=0}^k{\dbinom{k}{j}(i+1)^k}$$

$$(i+2)^k=\sum\limits_{j=0}^k{\dbinom{k}{j}i^j\times2^{j-k}}$$

将上式子带回原式：

$$=f_i\times\sum\limits_{j=0}^k{\dbinom{k}{j}i^j\times2^{j-k}}+f_{i+1}\times \sum\limits_{j=0}^k{\dbinom{k}{j}(i+1)^k}$$

将外面的乘进去：

$$=\sum\limits_{j=0}^k{f_i\times i^j\dbinom{k}{j}2^{j-k}}+\sum\limits_{j=0}^k{f_{i+1}\times (i+1)^j\dbinom{k}{j}}$$

你会惊奇的发现：加和中的 $\dbinom{k}{j}$ 以及 $\dbinom{k}{j}2^{j-k}$ 均为可以提前预处理的常数。结合 $k$ 又非常小，可以将 $p\in [0,k] $ $f_i\times i^{p}$ 全部预处理出来，塞进初始矩阵里就可以了。

还有，题目中要求求的是和，你还得在初始矩阵中额外添加一个和的数据。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 40
#define int long long 

const int mod = 1e9 + 7;

struct matrix {
	int n, m;
	int a[(MAXN<<1)+5][(MAXN<<1)+5];
	matrix() { memset(a, 0, sizeof a); }
} ans, p;

void debug(matrix x) {
	cout << x.n << ' ' << x.m << ":\n";
	for (int i = 1; i <= x.n; ++i) {
		for (int j = 1; j <= x.m; ++j) cout << x.a[i][j] <<' ';
		cout << endl;
	}
}

matrix operator * (matrix x, matrix y) {
	matrix z;
	z.n = x.n, z.m = x.m;
	for (int i = 1; i <= x.n; ++i) 
		for (int j = 1; j <= y.m; ++j)
			for (int k = 1; k <= x.m; ++k)
				(z.a[i][j] += x.a[i][k] * y.a[k][j] % mod) %= mod;
	return z;
}

matrix mpow(matrix x, int y) {
	matrix ans;
	ans.n = x.n, ans.m = x.m;
	for (int i = 1; i <= min(ans.n, ans.m); ++i) ans.a[i][i] = 1; 
	while (y) {
		if (y & 1) ans = ans * x;
		x = x * x;
		y >>= 1;
	}
	return ans;
}

int mpow(int x, int y) {
	if (y < 0) return 0;
	int s = 1;
	while (y) {
		if (y & 1) s = s * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return s;
}

int C(int a, int b) {
	if (a < b) return 0;
	if (b > a / 2) b = a - b;
	int s = 1;
	for (int i = a - b + 1; i <= a; ++i) s = s * i % mod;
	for (int i = 1; i <= b; ++i) s = s * mpow(i, mod - 2) % mod;
	return s;
}

int n, k;

signed main() {
	cin >> n >> k;
	if (n == 1) {
		puts("1");
		return 0;
	} 
	ans.n = 1, ans.m = 2 * k + 3;
	for (int i = 0; i <= k; ++i) 
		ans.a[1][i + 1] = 1, ans.a[1][i + k + 2] = 2 * mpow(2, i) % mod;
	ans.a[1][2 * k + 3] = (1 + mpow(2, k + 1)) % mod;
	p.n = p.m = 2 * k + 3;
	for (int j = 1; j <= 2 * k + 3; ++j) {
		if (j <= k + 1) 
			p.a[j + k + 1][j] = 1;
		else if (j <= 2 * k + 2) {
		 	// F[i] * i ^ p
		 	// F[i + 1] * (i + 1) ^ p
		 	// ↓
			// F[i + 1] * (i + 2) ^ p + F[i] * (i + 2) ^ p 
			for (int i = k + 2; i <= 2 * k + 2; ++i) // F[i + 1]
				p.a[i][j] = C(j - k - 2, i - k - 2);
			for (int i = 1; i <= k + 1; ++i) 
				p.a[i][j] = mpow(2, j - k - 1 - i) * C(j - k - 2, i - 1) % mod;
		}
		else {
			for (int i = k + 2; i <= 2 * k + 2; ++i) // F[i + 1]
				p.a[i][j] = C(k, i - k - 2);
			for (int i = 1; i <= k + 1; ++i) 
				p.a[i][j] = mpow(2, k + 1 - i) * C(k, i - 1) % mod;
			p.a[2 * k + 3][j] = 1;
		}
	}
//	debug(ans), debug(p);
	ans = ans * mpow(p, n - 2);
//	debug(ans);
	cout << ans.a[1][2 * k + 3] << endl;
	return 0;
}
```

---

## 作者：Mr_H2T (赞：2)

### 题意

$F_1=1,F_2=2,F_n=F_{n-1}+F_{n-2}$，求 $\sum_{i=1}^ni^kF_i$。

### 分析

暴推式子。

我们记 $\alpha=\dfrac{1+\sqrt5}2,\beta=\dfrac{1-\sqrt5}2$。

由于 $F_n=\dfrac 1{\sqrt{5}}(\alpha^{n+1}-\beta^{n+1})$，

记 $S_{k,d}=\sum_{i=1}^ni^kd^i$，则我们要求的答案即为 $\dfrac1{\sqrt5}(\alpha S_{k,\alpha}-\beta S_{k,\beta})$。

下面计算 $S_{k,\alpha}$，$\beta$ 同理，思路是**差分**。

首先，当 $k=0$ 时，原式即为 $\sum_{i=1}^nd^i=d\cdot\dfrac{d^n-1}{d-1}$，可以直接求出。

然后，当 $k\neq0$ 时，进行以下转化：
$$
\begin{aligned}
S_{k,d}&=\sum_{i=1}^ni^kd^i\\
d\cdot S_{k,d}&=\sum_{i=1}^ni^kd^{i+1}\\
(d-1)S_{k,d}&=\sum_{i=2}^{n}((i-1)^kd^i-i^kd^i)-d+n^kd^{n+1}\\
S_{k,d}&=\dfrac{\sum_{i=2}^{n}(((i-1)^k-i^k)d^i)-d+n^kd^{n+1}}{d-1}
\end{aligned}
$$
我们注意到，求和式中的 $(i-1)^k-i^k=\sum_{j=1}^k\binom kj(-1)^{j}\cdot i^{k-j}$，则原求和式可转化为
$$
\begin{aligned}
&\;\;\;\;\; \sum_{i=2}^n(((i-1)^k-i^k)d^i)\\
&=\sum_{i=2}^n(\sum_{j=1}^k(-1)^j\binom kji^{k-j}d^i)\\
&=\sum_{j=1}^k(-1)^j\binom kj\sum_{i=2}^ni^{k-j}d^i\\
&=\sum_{j=1}^k(-1)^j\binom kj S_{k-j,d}
\end{aligned}
$$
而其中的 $k-j<k$， $S_{k-j,d}$ 均是我们已经求出的答案。因而，我们最终的式子就化为
$$S_{k,d}=\dfrac{\sum_{j=1}^k(-1)^j\binom kj S_{k-j,d}-d+n^kd^{n+1}}{d-1}$$

那么我们就可以在 $O(k^2)$ 的复杂度内递推出所有的 $S_{k,d}$，就可以求得我们最后的答案了。

当然，这里还有一个重要的细节：由于题目要求对 $1e9+7$ 取模，而 $\sqrt5$ 在模 $1e9+7$ 下没有二次剩余的样子，因而我们还需要定义一个“复”数 $a+b\sqrt5$。

注意到有一个奇妙的性质：这个“复”数的 “$1$ 部”和“$\sqrt5$ 部”可以对 $1e9+7$ 取模，最终计算得的答案由于原本就必然是整数，因而不会改变。所以我们只要定义这个“复”数的四则运算即可。注意到除法时由于要把分母有理化，还要 $\log p$ 的时间求逆元；我们的 $n^kd^{n+1}$ 可以提前处理，因而总的复杂度是 $O(k^2\log p)$，非常的优秀。

### 代码

```cpp
//sigma(i^k*Fib(i))
#include<bits/stdc++.h>
#define int long long
#define rint register int
#define fu(i,a,b,d,c) for(rint i=a;i<=b&&c;i+=d)
#define fd(i,a,b,d,c) for(rint i=a;i>=b&&c;i-=d)
using namespace std;
inline int read(){
    char c=0,f=1;int num=0;
    while(c<'0'||c>'9'&&c!='-')((c=getchar())=='-')&&(f=-f);
    while(c>='0'&&c<='9')num=(num<<1)+(num<<3)+(c^48),c=getchar();
    return num*f;
}

const int LJC = 1e9+7, MAXK = 50;
int qp(int x,int p){
    int res=1;
    for(x%=LJC;p;x=1ll*x*x%LJC,p>>=1)(p&1)&&(res=1ll*res*x%LJC);
    return res;
}
int inv(int x){return qp(x,LJC-2);}
struct S{
    int a,b;
    S():a(0),b(0){}
    S(int a_,int b_):a((a_%LJC+LJC)%LJC),b((b_%LJC+LJC)%LJC){}
    S operator+(const S y){return S(a+y.a,b+y.b);}
    S operator-(const S y){return S(a-y.a,b-y.b);}
    S operator*(const S y){return S(1ll*a*y.a+5ll*b*y.b,1ll*a*y.b+1ll*b*y.a);}
    S operator/(const S y){
        int fm=inv(((1ll*y.a*y.a-5ll*y.b*y.b)%LJC+LJC)%LJC);
        return S(1ll*(1ll*a*y.a-5ll*b*y.b)%LJC*fm,1ll*(1ll*b*y.a-1ll*a*y.b)%LJC*fm);
    }
};
S qp(S x,int p){
    S res(1,0);
    for(;p;x=x*x,p>>=1)(p&1)&&(res=res*x,0);
    return res;
}
void write(int n){
    if(n==0)putchar('0');
    char c[30]={0};int len=0;
    while(n)c[++len]=n%10+'0',n/=10;
    while(len)putchar(c[len--]);
}
int n,nk[MAXK];
int k;
S ansA[MAXK],ansB[MAXK],an,bn;
int C[MAXK][MAXK];
signed main(){
    n=read(),k=read();
    S A(inv(2),inv(2)),B(inv(2),LJC-inv(2));
    nk[0]=1;an=qp(A,n+1),bn=qp(B,n+1);
    fu(i,1,k,1,1)nk[i]=1ll*nk[i-1]*(n%LJC)%LJC;
    C[0][0]=1;
    fu(i,1,k,1,1){
        C[i][0]=1;
        fu(j,1,i,1,1)C[i][j]=(1ll*C[i-1][j-1]+C[i-1][j])%LJC;
    }
    ansA[0]=A*((qp(A,n)-S(1,0))/(A-S(1,0)));
    ansB[0]=B*((qp(B,n)-S(1,0))/(B-S(1,0)));
    fu(i,1,k,1,1){
        S tmpA(0,0),tmpB(0,0);
        fu(j,0,i-1,1,1){
            tmpA=tmpA+S(((i-j&1)?LJC-1:1),0)*S(C[i][j],0)*(ansA[j]-A);
            tmpB=tmpB+S(((i-j&1)?LJC-1:1),0)*S(C[i][j],0)*(ansB[j]-B);
        }
        tmpA=tmpA-A+S(nk[i],0)*an;
        tmpB=tmpB-B+S(nk[i],0)*bn;
        ansA[i]=tmpA/(A-S(1,0));
        ansB[i]=tmpB/(B-S(1,0));
    }
    S res=((A*ansA[k]-B*ansB[k])/S(0,1));
    // printf("%lld",res.a);
    write(res.a);
}
```

---

## 作者：cwfxlh (赞：1)

# [CF392C](https://www.luogu.com.cn/problem/CF392C)     

儿简送。       

因为 $k$ 比较小，所以考虑记下 $f_x\times x^i$，$i\in [0,k]$，如果不带斐波那契的系数的话就可以转移了，但是因为有斐波那契，所以加记一组 $f_{x-1}\times x^i$，$i\in [0,k]$。最后为了求和，再记一个 sum。发现这两组是可以互相递推下去的，递推可以写成矩阵的形式，就可以矩阵快速幂了。    

具体的，转移如下：    

$f_xx^i= \sum_{j=0}^k{C_j^i\times f_{x-1}(x-1)^j}+\sum_{j=0}^k{C_j^i\times f_{x-2}(x-1)^j}$     

$f_{x-1}x^i=\sum_{j=0}^k{C_j^i\times f_{x-1}(x-1)^j}$       

写成转移矩阵大概是三块组合数的样子。     

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int n,k,ans,C[103][103];
struct Matrix{
	int h,w;
	int v[103][103];
}respd,tr,bs,bse,ret;
Matrix pdct(Matrix A,Matrix B){
	respd.h=B.h;
	respd.w=A.w;
	for(int i=1;i<=respd.h;i++){
		for(int j=1;j<=respd.w;j++){
			respd.v[i][j]=0;
			for(int u=1;u<=A.h;u++)respd.v[i][j]=(respd.v[i][j]+A.v[u][j]*B.v[i][u])%MOD;
		}
	}
	return respd;
}
Matrix fstp(Matrix X,int Y){
	bse=X;
	ret=X;
	for(int i=1;i<=X.h;i++){
		for(int j=1;j<=X.w;j++)ret.v[i][j]=(i==j);
	}
	while(Y){
		if(Y&1)ret=pdct(ret,bse);
		bse=pdct(bse,bse);
		Y>>=1;
	}
	return ret;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=0;i<=100;i++)C[i][0]=1;
	for(int i=1;i<=100;i++){
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	}
	bs.h=2*(k+1)+1;
	bs.w=1;
	for(int i=0;i<=k;i++){
		bs.v[i+1][1]=1;
		bs.v[i+1+(k+1)][1]=1;
	}
	tr.h=tr.w=2*(k+1)+1;
	for(int i=0;i<=k;i++){
		for(int j=0;j<=k;j++){
			tr.v[i+1][j+1]=C[i][j];
			tr.v[i+1][j+1+(k+1)]=C[i][j];
			tr.v[i+1+(k+1)][j+1]=C[i][j];
		}
	}
	tr.v[2*(k+1)+1][k+1]=1;
	tr.v[2*(k+1)+1][2*(k+1)+1]=1;
	tr=fstp(tr,n-1);
	bs=pdct(bs,tr);
	ans=bs.v[2*(k+1)+1][1]+bs.v[k+1][1];
	ans%=MOD;
	ans+=MOD;
	ans%=MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：Fhr123456 (赞：1)

[题目传送门](https://codeforces.com/contest/392/problem/C)

## 题意:
斐波那契数列 $F_1=1$，$F_2=2$，$F_i=F_{i-1}+F_{i-2}(i>2)$。对于数列 $A$，$A_i(k)=F_i \times i^k(i>1)$。求 $A_1(k)+A_2(k)+...A_n(k)$，答案对 $10^9+7$ 取模。
## 解题思路
发现 $n<=10^{17}$，考虑使用矩阵加速。因为矩阵中向量只能求和不能相乘，所以我们只能把 $F_i \times i^k$ 看成一个整体。接着考虑转移，首先 $F_i=F_{i-1}+F_{i-2}$，然后对于 $i^k = (i-1+1)^k$。对其进行二项式展开得 $(i-1+1)^k=\sum\limits_{r=0}^kC_k^r \times (i-1)^k$。所以把 $\sum$ 拆开得到矩阵：
$$\begin{bmatrix}(i-1)^0 \times F_{i-2}\\(i-1)^1 \times F_{i-2}\\\vdots\\(i-1)^k \times F_{i-2}\\(i-1)^0 \times F_{i-1}\\(i-1)^1 \times F_{i-1}\\\vdots\\(i-1)^k \times F_{i-1}\end{bmatrix} \times C=\begin{bmatrix}i^0 \times F_{i-1}\\i^1 \times F_{i-1}\\\vdots\\i^k \times F_{i-1}\\i^0 \times F_{i}\\i^1 \times F_{i}\\\vdots\\i^k \times F_{i}\end{bmatrix}$$
接着思考如何构建操作矩阵 $C$。显然 $i^0 \times F_{i-1}=(i-1)^0 \times F_{i-1}$，$i^1 \times F_{i-1}=(i-1)^0 \times F_{i-1}+(i-1)^1 \times F_{i-1}$，$i^2 \times F_{i-1}=(i-1)^0 \times F_{i-1}+2 \times (i-1)^1 \times F_{i-1}+(i-1)^2 \times F_{i-1}$。其实就是一个杨辉三角。 $i^0 \times F_i=(i-1)^0 \times (F_{i-2}+F_{i-1})$，所以就是两个杨辉三角，这样就得到了操作矩阵 $C$。
$$\begin{bmatrix}0&0&0&\cdots&0&1&0&0&\cdots&0\\0&0&0&\cdots&0&1&1&0&\cdots&0\\0&0&0&\cdots&0&1&2&1&\cdots&0\\\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\\1&0&0&\cdots&0&1&0&0&\cdots&0\\1&1&0&\cdots&0&1&1&0&\cdots&0\\1&2&1&\cdots&0&1&2&1&\cdots&0\\\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\vdots&\end{bmatrix}$$
## AC代码
```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int mod=1e9+7;
struct Matrix{//矩阵结构体 
	vector<vector<int> > mp;
	Matrix(int n,int val=0):mp(n,vector<int>(n,0)){
		for(int i=0;i<n;i++) mp[i][i]=val;
	}
	Matrix(const vector<vector<int> >& _m):mp(move(_m)){}
	Matrix operator*(const Matrix& _m)const{
		int n=mp[0].size();
		Matrix res(n);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					res.mp[i][j]=(res.mp[i][j]+mp[i][k]*_m.mp[k][j])%mod;
		return res;
	}
	Matrix operator^(int l){
		Matrix res(mp.size(),1),tmp=*this;
		while(l){
			if(l&1) res=res*tmp;
			tmp=tmp*tmp;
			l>>=1;
		}
		return res;
	}
};
int n,k,ans;
signed main(){
	scanf("%lld%lld",&n,&k);
	if(n==1){
		printf("1");
		return 0;
	}
	if(n==2){
		printf("%lld",1+2*(1<<k));
		return 0;
	}//特判小于等于二的情况 
	Matrix C((k<<1)+3);
	C.mp[0][k+1]=1;
	for(int i=1;i<k+1;i++){
		for(int j=k+1;j<(k<<1)+2;j++){
			if(j==k+1) C.mp[i][j]=1;
			else C.mp[i][j]=(C.mp[i-1][j-1]+C.mp[i-1][j])%mod;
		}
	}
	C.mp[k+1][0]=C.mp[k+1][k+1]=1;
	for(int i=k+2;i<(k<<1)+2;i++){
		for(int j=0;j<k+1;j++){
			if(j==0) C.mp[i][j]=C.mp[i][j+k+1]=1;
			else C.mp[i][j]=C.mp[i][j+k+1]=(C.mp[i-1][j-1]+C.mp[i-1][j])%mod;
		}
	}
	for(int i=0;i<(k<<1)+2;i++) C.mp[(k<<1)+2][i]=C.mp[(k<<1)+1][i];
	C.mp[(k<<1)+2][(k<<1)+2]=1;//创建操作矩阵C 
	C=C^(n-1);//矩阵快速幂 
	for(int i=0;i<(k<<1)+3;i++) ans=(ans+C.mp[(k<<1)+2][i])%mod;//统计答案 
	printf("%lld",ans%mod);
	return 0;
}
```

---

## 作者：Mobius127 (赞：1)

[题传](https://www.luogu.com.cn/problem/CF392C)


给定 $n \leq 10^{17}, K \leq 40, F$ 为 fibonacci 数列，求:

$$

\sum_{i=1}^{n} F_{n} \times i^{K}

$$

先暴力推推柿子，记 $S_{i}(K)=F_{i} \times i^{K}$, sum $_{i}=\sum S_{i}(K)$

$$

\begin{gathered}

S_{i}(K)=\left(F_{i-1}+F_{i-2}\right) i^{K} \\

=F_{i-1} i^{K}+F_{i-2} i^{K}

\end{gathered}

$$

一般地，我们希望拆开后下标对应，所以重写成 :

$$

=F_{i-1}(i-1+1)^{K}+F_{i-2}(i-2+2)^{K}

$$

二项式定理

$$

\begin{gathered}

=F_{i-1}\left(\sum_{k=0}^{K} C_{K}^{k}(i-1)^{k}\right)+F_{i-2}\left(\sum_{k=0}^{K} C_{K}^{k}(k-2)^{k} 2^{K-k}\right) \\

=\sum_{k=0}^{K} C_{K}^{k}\left(F_{i-1}(i-1)^{k}+F_{i-2}(i-2)^{k}2^{K-k}\right) \\

=\sum_{k=0}^{K} C_{K}^{k}\left(S_{i-1}(k)+S_{i-2}(k) 2^{K-k}\right)

\end{gathered}

$$

即

$$

S_{i}(K)=\sum_{k=0}^{K} C_{K}^{k} S_{i-1}(k)+C_{K}^{k} 2^{K-k}S_{i-2}(k) 

$$

注意到 k 很小，所以直接把所有的 $S(k)$ 丢进矩阵是没有问题的。

现在就可以矩阵快速幂了。时间复杂度 $O(K^3 \log n)$。



### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#define int long long
using namespace std;
const int N=101;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
long long n;
int K, S, C[N][N], pow2[N];
struct node{
	int r[N][N];
	int* operator [](int i){return r[i];}
	void reset(){memset(r, 0, sizeof(r));}
	void debug(){
		for(int i=0; i<S; i++, puts(""))
			for(int j=0; j<S; j++)
				printf("%d ", r[i][j]);
	}
	node operator * (node x){
		node c;c.reset();
		for(int i=0; i<S; i++)
			for(int j=0; j<S; j++)
				for(int k=0; k<S; k++)
					c[i][j]=(c[i][j]+1ll*r[i][k]*x[k][j]%mo)%mo;
		return c;
	}
}A, I, X;
node ksm(node a, long long b){
	node res=I;
	for(; b; b=b/2, a=a*a)
		if(b&1) res=res*a;
	return res;
}
/*
S(i, 0)
S(i, 1)
S(i, 2)
...
S(i, K)
S(i-1, 0)
S(i-1, 1)
S(i-1, 2)
...
S(i-1, K)
Sum(i-1)
*/
signed main(){
	n=read(), K=read();S=2*K+3;pow2[0]=1;
	for(int i=1; i<=K; i++) pow2[i]=1ll*pow2[i-1]*2%mo;
	for(int i=0; i<=K; i++){
		C[i][0]=1;
		for(int j=1; j<=i; j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mo;
	}
	I.reset();for(int i=0; i<S; i++) I[i][i]=1;
	X.reset();
	for(int i=0; i<=K+1; i++)
		X[0][i]=1;//X[0][S-1]=0;
	A.reset();
	for(int i=0; i<=K; i++) //S(i, (0-K)) 中的 (0-K) 
		for(int k=0; k<=i; k++) //sigma  中的 小k 
			A[k][i]=C[i][k],
			A[k+K+1][i]=C[i][k]*pow2[i-k]%mo;
	for(int i=0; i<=K; i++)
		A[i][i+K+1]=1;
	A[2*K+2][2*K+2]=1, A[K][2*K+2]=1;
//	X.debug();puts("CRX AK IOI");
//	A.debug();puts("CHT AK IOI");
	X=X*ksm(A, n);//X.debug();
	printf("%lld\n", X[0][2*K+2]);
    return 0;
}
```







---

## 作者：TernaryTree (赞：0)

令 $f_{i,j}$ 表示 $n=i,k=j$ 时的答案。

$$
\begin{aligned}
f_{n,k}
&=\sum_{i=1}^nF_i \cdot i^k \\
&=F_1\cdot 1^k+F_2\cdot 2^k+\sum_{i=3}^n (F_{i-1}+F_{i-2})\cdot i^k \\
&=1+2^{k+1}+\sum_{i=3}^n F_{i-1}\cdot i^k+\sum_{i=3}^n F_{i-2}\cdot i^k \\
&=1+2^{k+1}+\sum_{i=2}^{n-1} F_i\cdot (i+1)^k+\sum_{i=1}^{n-2} F_{i}\cdot (i+2)^k \\
&=1+2^{k+1}-F_1\cdot 2^k+\sum_{i=1}^{n-1} F_i\cdot (i+1)^k+\sum_{i=1}^{n-2} F_{i}\cdot (i+2)^k \\
&=1+2^{k}+\sum_{i=1}^{n-1} F_i\cdot (i+1)^k+\sum_{i=1}^{n-2} F_{i}\cdot (i+2)^k \\
&=1+2^{k}+\sum_{i=1}^{n-1} F_i \sum_{j=0}^k\dbinom{k}{j} i^j+\sum_{i=1}^{n-2} F_{i}\sum_{j=0}^k \dbinom kj 2^{k-j}i^j \\
&=1+2^{k}+\sum_{j=0}^k\dbinom{k}{j}\sum_{i=1}^{n-1} F_i\cdot  i^j+\sum_{j=0}^k \dbinom kj 2^{k-j}\sum_{i=1}^{n-2} F_{i}\cdot i^j \\
&=1+2^{k}+\sum_{j=0}^k\dbinom{k}{j}f_{n-1,j}+\sum_{j=0}^k \dbinom kj 2^{k-j}f_{n-2,j} \\
\end{aligned}
$$

转移形式与 $n$ 无关，$n$ 有 $10^{17}$，$k$ 只有 $40$，直接矩阵快速幂优化即可。时间复杂度 $\Theta(k^3\log n)$。[Code](https://www.luogu.com.cn/paste/ef142995)。

---

