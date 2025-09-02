# A/B Problem（高精度除法）

## 题目描述

给你两个正整数 $a,b$，求 $\lfloor a/b \rfloor$。  
为了卡掉一些乱搞做法，你需要对答案进行如下处理：  
设答案为 $r$，构造一个多项式 $F(x)$：

$$ F(x) = \sum\limits_{i=0}^{\lfloor \lg r \rfloor} (\lfloor 10^{-i}r \rfloor \bmod 10) \cdot x^i$$

简单地说，就是从 $r$ 的低位到高位，每一位对应 $F(x)$ 一项的系数。

设 $F(x)$ 的最高非零次数为 $n$，你需要求出一个 $n$ 次多项式 $G(x)$，使得：  
$$ F(x) \cdot G(x) \equiv 1 \pmod{x^{n+1}}$$   
将 $G(x)$ 的系数对 $998244353$ 取模，然后升幂输出 $G(x)$ 的系数即可。

保证满足条件的 $G(x)$ 存在。

## 说明/提示

**【样例解释】**

$\left\lfloor \dfrac{19260817}{114514} \right\rfloor = 168$。

由此构造出的多项式 $F(x)=x^2+6x+8$  
求出来对应的 $G(x)$ 就是 $943652865x^2 + 93585408x +  873463809$。

**【数据范围】**

对于 $100 \%$ 的数据，$1\le b \le a \le 10^{200000}$。

## 样例 #1

### 输入

```
19260817
114514```

### 输出

```
873463809 93585408 943652865 ```

# 题解

## 作者：NaCly_Fish (赞：91)

update：修整了一下题解格式。

看看题目让我们求什么：$\lfloor a/b \rfloor$  

我们可以考虑求出 $b$ 的倒数，然后再乘上 $a$，得出结果。   
高精度实数运算实现起来并不复杂，每个数记一下乘了 $10$ 的多少次方，做加减的时候移位一下就行。   
做乘法会更简单，不用移位，把幂次加起来即可。

关于怎么求 $b$ 的倒数，可以考虑牛顿迭代：  
$$ x-\frac1b=0$$  
$$ x_{i+1}=2x_i-bx_i^2$$  
这里只用到了乘法和减法，所以可以直接用 $\Theta(n\log n)$ 的乘法来算（这里设 $a$ 的位数为 $n$）。   
一般把 $x$ 的初值选为 $10^{-\lfloor \lg b \rfloor}$ 左右的数，这样减小一些常数（一次迭代）。

由于每次迭代精度翻一倍，所以时间复杂度为  
$$ T(n)=T(n/2)+\Theta(n\log n)=\Theta(n\log n)$$  
由于 $\lfloor a/b \rfloor$ 的位数最多不超过 $n$，故计算 $1/b$ 的误差只要小于 $10^{-n}$，$a\times (1/b)$ 的误差就小于 $1$，直接取整就得到了 $\lfloor a/b \rfloor$。


别忘了还要对最后算出来的结果用[【模板】多项式求逆](https://www.luogu.org/problemnew/show/P4238) 处理一下。
  
****
上述做法需要实现高精度实数运算，可能稍微有些麻烦。在 WC2012 的论文《理性愉悦：高精度数值计算》（原作者：倪泽堃）中有提到一种只用高精度整数的做法，这里复述一下：

设 $b$ 有 $n$ 位，那么我们希望求得 $b'=\lfloor 10^{2n}/b\rfloor$，然后计算出 $\lfloor ab'/10^{2n}\rfloor$，经调整后即得到 $\lfloor a/b\rfloor$。  
不过这里面有个 $b'$ 舍入的误差问题，为了保证最后调整的次数是 $\Theta(1)$ 的，那么 $b$ 相对 $a$ 的位数不能太少。  
假设 $a$ 有 $m$ 位，我们需要使得 $m\le 2n$。这样可以证明最后调整时，误差不超过$10$。这很简单，假设 $m>2n$，两者同时左移若干位即可。  

下面的问题就是求解 $\lfloor10^{2n}/b\rfloor$。设前一次迭代求解的是 $b_k'=\lfloor10^{2k}/b_k\rfloor$（其中$ b_k$ 为 $b$ 的前 $k$ 位组成的数），那么这一次的迭代式为：  
$$ b'^*/10^{2n}=2b_k'/10^{2k}/10^{n-k}-b(b_k'/10^{2k}/10^{n-k})^2$$  
也就是：  
$$ b'^*=2b_k'\times10^{n-k}-bb_k'^2/10^{2k} \approx 2b_k'\times10^{n-k}-\lfloor bb_k'^2/10^{2k} \rfloor$$  

求得 $b'^*$ 当然还没完，这只是迭代的结果，不是 $\lfloor 10^{2n}/b \rfloor$ 的精确值。  
误差分析表明，当 $k>n/2$ 时，误差不超过 $100$，于是还要在求得余数 $10^{2n}-bb'^*$ 后对 $b'^*$ 进行 $\Theta(1)$ 次的调整（为了降低常数，还可以二分误差）。这样就迭代求出了 $\lfloor 10^{2n}/b \rfloor$  
迭代边界为 $n\le 2$，此时 $b$ 在小整数范围内，可以直接求解。  

求解出 $\lfloor 10^{2n}/b \rfloor$ 后与 $a$ 相乘，在计算出余数后和上面类似的调整，即可求解出$\lfloor a/b \rfloor$。  

时间复杂度分析同高精度实数做法。
****



---

## 作者：xenonex (赞：38)

居然只有一篇题解

~~而且不给代码~~

~~调死我这个退役菜鸡了qaq~~

------------

**这是一篇C++题解**

这道题目里，神鱼让我求两个$10^{200000}$级别的大数的整除商$\lfloor\frac{a}{b}\rfloor$。显然普通的$O(n^2)$做法不再适用。直接考虑高精度实数方法，计算$\frac{a}{b}$然后取整数部分，先计算$\frac{1}{b}$，然后与$a$相乘。

至于$\frac{1}{b}$的求法与多项式求逆有点类似，也利用迭代法计算。具体地，若已有$x_0$满足
$$bx_0=1-\epsilon$$
其中$\epsilon$代表一个小于$1$的误差，则有
$$bx_0-1=-\epsilon$$
$$(bx_0-1)^2=\epsilon^2$$
$$b^2x_0^2-2bx_0+1=\epsilon^2$$
$$b(2x_0-bx_0^2)=1-\epsilon^2$$
所以只要不断迭代：
$$x_0\longleftarrow 2x_0-bx_0^2$$
误差就能平方级地缩小，换言之一次迭代后有效位数是之前的$2$倍，所以完成倒数计算需要$O(\log(\text{精度}))$次迭代。若配合FFT及倍增实现，整个过程就是$O(n\log n)$的。但我们只需要整数部分，所以有效位数取$\log_{10}\frac{a}{b}$位左右就差不多了。

~~后来发现这就是牛顿迭代~~

然后……就没了？注意各种细节吧，题目数据挺强的。特别注意算出来的整数部分可能会比真实值少1，微调下就可以了。

之所以主过程用FFT实现而不是NTT是因为中间结果会爆int。

~~但题目要求求逆输出于是单独写了一个NTT然后代码就5k了~~

~~高精度存char是为了省空间~~

~~码风诡异不喜勿喷~~

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#define inline __inline__ __attribute__((always_inline))
#define L 524288
#define mod 998244353
typedef long long LL;

int rev[L<<1];

namespace NTT //为了输出而写的NTT……
{
	int W[2][L],_i[20],invtmp[L],x[L],y[L];
	inline int invx(int x){int r=1;for(x%=mod;x>1;x=mod%x)r=LL(mod-mod/x)*r%mod;return r;}
	inline int ksm(LL a,LL b){int r=1;for(;b;a=a*a%mod,b>>=1)if(b&1)r=r*a%mod;return r;}
	void NTT_Init()
	{
		int i,t;
		const int G = 3,Gi = invx(G),i2 = invx(2),l = L>>1;
		t = ksm(G,mod/L), W[0][l] = 1;
		for(i=1;i<l;i++)W[0][i+l] = (LL)W[0][i+l-1]*t%mod;
		for(i=l-1;i;i--)W[0][i] = W[0][i<<1];
		t = ksm(Gi,mod/L), W[1][l] = 1;
		for(i=1;i<l;i++)W[1][i+l] = (LL)W[1][i+l-1]*t%mod;
		for(i=l-1;i;i--)W[1][i] = W[1][i<<1];
		for(_i[0]=i=1;i<20;i++)_i[i] = (LL)_i[i-1]*i2%mod;
	}
	void NTT(int *f,int len,int sign)
	{
		int i = 1,j,k,*w,*p,*q,t; sign = (sign < 0);
		for(int *r=rev+len+1;i<len;i++,r++)if(i<(k=*r))t=f[i],f[i]=f[k],f[k]=t;
		for(i=1;i<len;i<<=1)for(j=0;j<len;j+=i<<1)for(w=W[sign]+i,q=(p=f+j)+i,k=0;k<i;k++)
			{t=*q*LL(*w++)%mod;if((*q=*p-t)<0){*q+=mod;}if((*p+=t)>=mod){*p-=mod;}p++,q++;}
		if(sign)for(k=_i[__builtin_ctz(len)],i=0;i<len;i++)f[i] = (LL)k*f[i]%mod;
	}
	void poly_inv(int *a,int len,int *f)
	{
		int l,l2,i;len <<= 1;
		memset(f,0,len<<2), memset(invtmp,0,len<<2);
		for(f[0]=invx(a[0]),l=2,l2=4;l<len;l<<=1,l2<<=1)
		{
			memcpy(invtmp,a,l<<2), NTT(invtmp,l2,1), NTT(f,l2,1);
			for(i=0;i<l2;i++)f[i] = f[i]*(2-(LL)invtmp[i]*f[i]%mod+mod)%mod;
			NTT(f,l2,-1), memset(f+l,0,l<<2);
		}
	}
	void getout(char *s,int d)
	{
		int i,l;
		NTT_Init();
		for(i=0;i<d;i++)x[i] = s[i];
		for(l=1;l<d;l<<=1);
		poly_inv(x,l,y);
		for(i=0;i<d;i++)printf("%d ",y[i]);
	}
}

struct complex
{
	double a,b;
	inline void operator+=(const complex &z){a += z.a, b += z.b;}
	inline complex operator-(const complex &z){return {a-z.a,b-z.b};}
	inline complex operator*(const complex &z){return {a*z.a-b*z.b,a*z.b+b*z.a};}
}W[2][L];
void FFT_Init()
{
	int i,j; const int l = L>>1;
	const double pi = acos(-1);
	for(i=j=1;j<L;j<<=1)for(;i<j<<1;i++)rev[i<<1]=rev[i],rev[i<<1|1]=rev[i]+j;
	for(i=0;i<l;i++)W[0][i+l] = {cos(pi*i/l),sin(pi*i/l)};
	for(i=l-1;i;i--)W[0][i] = W[0][i<<1];
	memcpy(W[1],W[0],sizeof W[1]);
	for(i=1;i<L;i++)W[1][i].b *= -1;
}
void FFT(complex *f,int len,int sign)
{
	int i = 1,j,k; complex *p,*q,*w,t; sign = (sign < 0);
	for(int *r=rev+len+1;i<len;i++,r++)if(i<(k=*r))t=f[i],f[i]=f[k],f[k]=t;
	for(i=1;i<len;i<<=1)for(j=0;j<len;j+=i,j+=i)
		for(q=(p=f+j)+i,w=W[sign]+i,k=0;k<i;k++,p++,q++)t=*q**w++,*q=*p-t,*p+=t;
	if(sign){double p=1./len;for(i=0;i<len;i++,f++)f->a *= p, f->b *= p;}
}
int get(char *s)
{
	int c,l = 0;
	do c = getchar(); while(c < '1' || c > '9');
	do *s++ = char(c^48), l++, c = getchar(); while(c >= '0' && c <= '9');
	return l;
}
char a[L],b[L],bi[L],x[L],y[L];
complex t1[L],t2[L]; LL t3[L+1];
void majutsu(int len) //计算b的倒数，有效位数为len，结果存进bi里
{
	bool g = 1;
	int l = 16,l2 = 32,l4 = 64,i;
	long double d = 0,e = 1;
	for(i=0;i<20;i++)d = d+e*b[i], e *= 0.1;
	d = 10./d;
	if(d < 10)
	{
		for(i=0;i<=l;i++)bi[i] = d, d = (d-bi[i])*10;
		bi[l-1] += (bi[l] > 4);
	}
	else bi[0] = 10;
	while(l < len)
	{p:
		memset(t1,0,sizeof(complex)*l4);
		memset(t2,0,sizeof(complex)*l4);
		for(i=0;i<l2;i++)t1[i].a = b[i];
		for(i=0;i<l;i++)t2[i].a = bi[i];
		FFT(t1,l4,1), FFT(t2,l4,1);
		for(i=0;i<l4;i++)
		{
			t1[i] = t1[i]*t2[i];
			t1[i].a = 20-t1[i].a, t1[i].b = -t1[i].b;
			t2[i] = t1[i]*t2[i];
		}
		FFT(t2,l4,-1); t3[l4] = 0;
		for(i=l4-1;i>=0;i--)
		{
			t3[i] = LL(floor(t2[i].a+0.5))+t3[i+1]/10, t3[i+1] %= 10;
			if(t3[i+1] < 0)t3[i+1] += 10, t3[i]--;
		}
		if(t3[0] > 9)
		{
			bi[0] = t3[0]/10, t3[0] %= 10;
			for(i=1;i<l2;i++)bi[i] = t3[i-1];
			bi[l2-1] += (t3[l2-1] > 4);
		}
		else
		{
			for(i=0;i<l2;i++)bi[i] = t3[i];
			bi[l2-1] += (t3[l2] > 4);
		}
		l <<= 1, l2 <<= 1, l4 <<= 1;
	}
	if(g){g = 0, l >>= 1, l2 >>= 1, l4 >>= 1; goto p;} //迭代过程结束后末几位仍会有偏差，于是再单独迭代一次
}
int divide(int n,int m) //计算a/b，整数部分存进x里
{
	int p = n-m+16,l,i;
	majutsu(p);
	for(l=1;l<n+p;l<<=1);
	memset(t1,0,sizeof(complex)*l);
	memset(t2,0,sizeof(complex)*l);
	for(i=0;i<n;i++)t1[i].a = a[i];
	for(i=0;i<p;i++)t2[i].a = bi[i];
	FFT(t1,l,1), FFT(t2,l,1);
	for(i=0;i<l;i++)t1[i] = t1[i]*t2[i];
	FFT(t1,l,-1); t3[l] = 0;
	for(i=l-1;i>=0;i--)t3[i] = LL(t1[i].a+0.5)+t3[i+1]/10, t3[i+1] %= 10;
	if(t3[0] > 9)
	{
		x[0] = t3[0]/10, t3[0] %= 10, l = n-m+1;
		for(i=0;i<n-m;i++)x[i+1] = t3[i];
	}
	else for(l=n-m,i=0;i<n-m;i++)x[i] = t3[i];
	return l;
}
void lack(int n,int m,int &d) //微调
{
	int l,i,j; char t; LL tl = 0;
	for(i=0,j=n-1;i<j;i++,j--)t = a[i], a[i] = a[j], a[j] = t;
	for(i=0,j=m-1;i<j;i++,j--)t = b[i], b[i] = b[j], b[j] = t;
	for(i=0,j=d-1;i<j;i++,j--)t = x[i], x[i] = x[j], x[j] = t;
	for(l=1;l<n;l<<=1);
	memset(t1,0,sizeof(complex)*l);
	memset(t2,0,sizeof(complex)*l);
	for(i=0;i<m;i++)t1[i].a = b[i];
	for(i=0;i<d;i++)t2[i].a = x[i];
	t2[0].a += 1.;
	FFT(t1,l,1), FFT(t2,l,1);
	for(i=0;i<l;i++)t1[i] = t1[i]*t2[i];
	FFT(t1,l,-1);
	for(i=0;i<=n;i++)tl += LL(t1[i].a+0.5), y[i] = tl%10, tl /= 10;
	for(i=n;i>=0;i--){if(y[i] > a[i])return;else if(y[i] < a[i])break;}
	for(x[0]++,i=0;x[i]>9;i++)x[i+1] += x[i]/10, x[i] %= 10;
	if(x[d])d++;
}
int main()
{
	int n,m,d;
	FFT_Init();
	n = get(a), m = get(b);
	d = divide(n,m);
	lack(n,m,d);
	NTT::getout(x,d);
	return 0;
}
```


---

## 作者：hly1204 (赞：16)

我们关注题目中实现高精度整数除法的运算，这里沿用 C++ 中的整数除法的定义并假设除数和被除数都是正整数，以避免一些额外的判断。为了方便，下文讨论十进制下的运算，但也可以思考对于其他进制的扩展。

## 整数乘法表为多项式乘法

我们考虑使用多项式 $f(x)=4+x+5x^2+4x^3+x^4+x^5$ 来表示整数 `114514` 那么 $f(10)$ 即这个整数本身，考虑另一个多项式 $g(x)=x+8x^2+9x^3+x^4+9x^5+x^6$ 其 $g(10)=1919810$ 进行卷积，那么

$$
f(10)g(10)=114514\cdot 1919810
$$

显然，但由于多项式乘法没有进位而整数乘法需要考虑进位，于是对 $f(x)g(x)$ 结果的系数进行调整即可得到类似的多项式表示，这也告诉我们需要考虑多项式系数的值域能否容纳结果。

## Newton 法

我们使用 Newton 法计算 $a^{-1}$ 的近似值，然后计算 $b\cdot a^{-1}$ 来近似的得到 $b/a$ 。

### 使用 Newton 法计算倒数的误差分析

二阶的 Newton 法一般描述为

$$
x _ {i+1}=x_i-\frac{f(x_i)}{f'(x_i)}
$$

这里我们构造 $f(x)=x^{-1}-a$ 来计算 $a^{-1}$ 的近似值，那么 $f'(x)=-x^{-2}$

$$
\begin{aligned}
x _ {i+1}&=x_i-\frac{x_i^{-1}-a}{-x_i^{-2}}\\
&=x_i(2-ax_i)
\end{aligned}
$$

设误差 $\varepsilon_i=1-ax_i$ 那么

$$
\begin{aligned}
\varepsilon _ {i+1}&=1-ax_i(2-ax_i)\\
&=1-2ax_i+(ax_i)^2\\
&=(1-ax_i)^2\\
&=\varepsilon_i^2
\end{aligned}
$$

不妨假设开始时 $0\lt \varepsilon _ {0}\lt 10^{-1}$ 那么 $\varepsilon _ {1}\lt 10^{-2}$ ，这也说明了 $x_0$ 的取值范围是很重要的，不一定可以随意取，并且上述运算假设加减法和乘法不会丢失精度并且使用到了浮点数的运算，所以在实现中如果进行舍入那么误差的分析更为复杂。

### 基于 Newton 法的方法

[Lehmer 的最大公因数算法](https://en.wikipedia.org/wiki/Lehmer%27s_GCD_algorithm)告诉我们商通常和两个整数的高位更加相关，可以通过仅高位的运算先求出一个商的近似值，但是整数运算有进位所以需要一些误差分析和舍入/调整来获取正确的商。由于本人能力有限所以后面没有误差分析，仅参考文献中的算法。

倪泽堃指出，对于 $n$ 位的正整数 $A=a_0+a_1\cdot 10+\cdots +a _ {n-1}\cdot 10^{n-1}$ （其中整数 $0\leq a_i\lt 10$ ）和 $m$ 位的正整数 $B$ ，可以计算 $A'=\left\lfloor 10^{2n}/A\right\rfloor$ 后计算 $\lfloor A'B/10^{2n}\rfloor$ 后进行调整可以得到 $\left\lfloor B/A\right\rfloor$ 。

既然我们使用十进制表示，那么对于形如 $\lfloor A/10^t\rfloor$ 可以简单使用类似于位运算的移位，此时对于 Newton 法也改造为求 $A/10^{2n}$ 的倒数

$$
\begin{aligned}
&{}x _ {i+1}=x_i(2-x_iA/10^{2n})\\
\iff &x _ {i+1}\cdot 10^{2n}=x_i(2\cdot 10^{2n}-x_iA)
\end{aligned}
$$

文中表示，若 $m\leq 2n$ 最后调整时误差不超过 $10$ ，否则我们令 $A'=\left\lfloor 10^{m+n}/A\right\rfloor$ 后计算 $\lfloor A'B/10^{m+n}\rfloor$ 即可。

考虑

$$
\begin{aligned}
&{}\frac{10^{2n}}{A}-1\lt A'\leq \frac{10^{2n}}{A}\\
\iff &\frac{10^{2n}B}{A}-B\lt A'B\leq \frac{10^{2n}B}{A}\\
\iff &\frac{B}{A}-\frac{B}{10^{2n}}\lt \frac{A'B}{10^{2n}}\leq \frac{B}{A}\\
\implies &\frac{B}{A}-1\lt \frac{A'B}{10^{2n}}\leq \frac{B}{A}\quad \left(\because \frac{B}{10^{2n}}\lt 1\right)
\end{aligned}
$$

在这里向下取整可以发现误差最多为 $1$ ，并且此处用 $m+n$ 替换 $2n$ 结果也是一样的，可以发现这实际上就是 [Barrett reduction](https://en.wikipedia.org/wiki/Barrett_reduction) 。

难点在于如何求解 $A'$ ，文中给出了一种递归算法为

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{compute}(A)\text{:} \\
&\textbf{Input}\text{: an integer }A\gt 0 \text{ with }n\text{ digits (radix-10).}\\
&\textbf{Output}\text{: an integer }B\text{ such that }0\leq \left\lfloor \dfrac{10^{2n}}{A}\right\rfloor -B\leq 10^2\text{.}\\
1&\textbf{if }n\leq 2\textbf{ then return }\left(\left\lfloor \dfrac{10^{2n}}{A}\right\rfloor \right)\text{;}\\
2&n'\gets \left\lfloor \dfrac{n}{2}\right\rfloor +1\text{;}\\
3&q\gets \operatorname{compute}\left(\left\lfloor \dfrac{A}{10^{n-n'}}\right\rfloor\right)\cdot 10^{n-n'}\text{;}\\
4&\textbf{return }\left(\left\lfloor \dfrac{q(2\cdot 10^{2n}-qA)}{10^{2n}}\right\rfloor \right)\text{;}
\end{array}
$$

在第三步时我们取 $A$ 的高 $n'$ 位为 $A_0$ 计算 $q\approx \left\lfloor \dfrac{10^{2n'}}{A_0}\right\rfloor \cdot 10^{n-n'}\approx \left\lfloor\dfrac{10^{2n}}{A}\right\rfloor$ 后面为一次 Newton 迭代，个人猜测最坏的情况即 $A_0=\underbrace{10\dots 0} _ {n'\text{ digits}}$ 而 $A=\underbrace{10\dots 0} _ {n'\text{ digits}}\underbrace{9\dots 9} _ {n-n'\text{ digits}}$ 此时 Newton 迭代时误差最大，那么结果的误差看起来似乎也是最大的。下面使用 Python 代码进行了一些测试

```py
def count_digit(a):
    cnt = 0
    while a != 0:
        a //= 10
        cnt += 1
    return cnt
def compute(a):
    da = count_digit(a)
    print(da, a)
    if da <= 2:
        return (10 ** (da * 2)) // a
    da0 = da // 2 + 1
    r = compute(a // (10 ** (da - da0))) * 10 ** (da - da0)
    print(r)
    return r * (2 * 10 ** (da * 2) - r * a) // 10 ** (da * 2)
a = 1000000000000000999999999999999
da = count_digit(a)
print(10 ** (da * 2) // a - compute(a))
```

最后输出的误差为 `99` ，原文中为“不超过 `100` ”，这里不清楚我的猜测是否正确。

最后在算出 $A_0'\approx A'$ 后计算 $10^{2n}-AA_0'$ 二分误差即可算出 $A'$ 。

## 参考文献

- [倪泽堃. 理性愉悦——高精度数值计算（2012WC）](https://github.com/lzyrapx/Competitive-Programming-Docs/blob/master/WC%E8%AE%B2%E8%AF%BE%E8%B5%84%E6%96%99/%E7%90%86%E6%80%A7%E6%84%89%E6%82%A6%E2%80%94%E2%80%94%E9%AB%98%E7%B2%BE%E5%BA%A6%E6%95%B0%E5%80%BC%E8%AE%A1%E7%AE%97%EF%BC%882012WC%EF%BC%89.pdf)
- stackoverflow - [Newton-Raphson Division With Big Integers](https://stackoverflow.com/questions/27801397/newton-raphson-division-with-big-integers).

---

## 作者：acniu (赞：14)

这是一篇基于 $FFT$ 的压 4 位高精度题解（我写的是 `loj` 版，没有最后的多项式求逆，[提交记录（写的巨丑）](https://loj.ac/s/1026697)）。

本文大致参考[楼下大佬](https://www.luogu.com.cn/blog/_post/138771)，附蒟蒻自己瞎搞的误差分析。

---

假设你在 $g$ 进制下进行运算，$a,b$ 在 $g$ 进制下分别有 $n,m$ 位。

考虑这样一件事情：
$$
\left\lfloor\dfrac ab\right\rfloor-\left\lceil\dfrac at\right\rceil\le \left\lfloor\dfrac ab-\dfrac at\right\rfloor\le \left\lfloor\dfrac{a\lfloor\frac tb\rfloor}t\right\rfloor\le \left\lfloor\dfrac ab\right\rfloor
$$

因此 $\left\lfloor\dfrac{a\lfloor\frac tb\rfloor}t\right\rfloor$ 与答案的差 $\le \left\lceil\dfrac at\right\rceil$，只需取 $t=g^n>a$ 就能保证误差 $\le 1$，同时方便做除 $t$ 的运算，求出“余数”微调答案即可。

当 $n>2m$ 时，可以将 $a,b$ 同时乘以 $g^{n-2m}$ 使得 $n'\le 2m'$，因此只需求出 $\left\lfloor\dfrac {g^{2m}}b\right\rfloor$ 。

---

考虑牛顿迭代：

事实上实数求逆的牛迭形如 $x_{n+1}=2x_n-ax_n^2$，考虑仿照这个来。

取 $k$ 为一个 $m/2$ 左右的数，且你已求出 $b$ 的最高 $k$ 位的答案。形式化地说，

设 $c=\dfrac {g^{2m}}b,b'=\left\lfloor\dfrac{b}{g^{m-k}}\right\rfloor,c'=\left\lfloor\dfrac {g^{2k}}{b'}\right\rfloor$
，你已经知道 $b',c'$，要求 $\lfloor c\rfloor$。

那么迭代得到 $c^*=2c'g^{m-k}-bc'^2g^{-2k}$ 作为 $c$ 的近似值。

设 $c'=\dfrac{g^{m+k}}{b}+\Delta$，则 $c^*$ 的绝对误差为
$$
c-c^*=\dfrac{g^{2m}}{b}-\left(2\dfrac{g^{2m}}{b}+2\Delta g^{m-k}-\dfrac{g^{2m}}{b}-2\Delta g^{m-k}-b\Delta^2g^{-2k}\right)=b\Delta^2g^{-2k}
$$
考虑 $c'$ 的取值范围：
$$
\dfrac{g^{m+k}}{b}-1\le \dfrac{g^{2k}}{b'}-1\le c'\le \dfrac{g^{2k}}{b'}\le \dfrac{g^{2k}}{\dfrac{b}{g^{m-k}}-1}=\dfrac{g^{m+k}}{b-g^{m-k}}
$$
因此 $\Delta$ 的取值范围是：
$$
-1\le\Delta\le g^{m+k}\dfrac{g^{m-k}}{b(b-g^{m-k})}=\dfrac{g^{2m}}{b(b-g^{m-k})}
$$

所以（$b\ge g^{m-1}$）
$$
b\Delta^2 g^{-2k}\le \dfrac{g^{4m-2k}}{b(b-g^{m-k})^2}\le \dfrac{g^{m+1}}{(g^{k-1}-1)^2}=\dfrac{g^{m+1}}{g^{2k-2}-2\cdot g^{k-1}+1}\le
\dfrac{g^{m-k+2}}{g^{k-1}-2}=g^{m-2k+3}\left(1+\dfrac{2}{g^{k-1}-2}\right)
$$

当 $g\ge 10$ 时，保守估计误差不超过 $2g^{m-2k+3}$ 。

取 $k=\left\lceil\dfrac{m}2\right\rceil+2$，则 $m+4\le 2k\le m+5$，误差 $\le 2g^{-1}<1$，只需调整至多一次。

---

至于递归次数，每次 $k\le \dfrac{m+5}2$，所以递归 $x$ 次后 $m'$ 不超过 $\dfrac{m}{2^x}+5$
，可以当 $m\le 10$ 时直接暴力。

复杂度 $T(n)=T(n/2)+O(n\log n)=O(n\log n)$

---

## 作者：warzone (赞：13)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/wangrx/solution-p5432)

本文将介绍基于科学计数法的方法，使用 FFT 优化高精度除法、开根、指数、对数等。

对于多项式 

$$f(x)=f_0+f_1x+f_2x^2+f_3x^3+\cdots$$

对于高精度整数，通常是将其表示为 $f(10)$ 的形式，如

$$3579=9+7\times 10+5\times 10^2+3\times 10^3$$

但这一方法不能较好地表示小数。

考虑科学计数法，将每个数表示为 $f(10^{-1})\times10^n$ 的形式，如

$$158.97=1.5897\times 10^2$$
$$=(1+5\times 10^{-1}+8\times 10^{-2}+9\times 10^{-3}+7\times 10^{-4})\times 10^2$$

由此我们得到了高精度小数的表示方法。

## 高精度小数的乘法

$$(f(10^{-1})\times 10^n)\times(g(10^{-1})\times 10^m)=(f\times g)(10^{-1})\times 10^{n+m}$$

FFT 优化即可，注意进位跟整数是反过来的。

## 高精度小数的倒数

对于高精度整数，求倒数显然是不可能的。

但高精度小数可以，根据多项式求逆：

$$a(x)f(x)\equiv 1\pmod{x^n}$$
$$a(x)\equiv 1\pmod{x^{\frac{n}{2}}}$$

$$f(x)\equiv g(x)(2-a(x)g(x))\pmod{x^n}$$

但我们无法使用多项式求逆的终止条件 $(a_0f_0=1)$，  
考虑将同余式展开并代入

$$A=a(10^{-1}),F=f(10^{-1}),G=g(10^{-1})$$

$$AF=1-10^{-n}C_0,C_0\in[0,1)$$

$$AG=1-10^{-\frac{n}{2}}C,C\in[0,1)$$

$$1-2AG+A^2G^2=10^{-n}C^2,C^2\in[0,1)$$

$$F^2-2FG+G^2=(1-10^{-n}C_0)10^{-n}C,C\in[0,1)$$


$$F=G(2-AG)-10^{-n}C,C\in[0,1)$$

选择 $[0,1)$ 而非 $[0,10)$ 是为了避免进位的情况。

终止条件是 $n=2$，此时 $F=10^{-1}{\left\lfloor\dfrac{100}{10a_0+a_1}\right\rfloor}$。


## 高精度小数的除法


$$\dfrac{f(10^{-1})\times 10^n}{g(10^{-1})\times 10^m}=f(10^{-1})g^{-1}(10^{-1})\times 10^{n-m}$$

计算出 $f(10^{-1})g^{-1}(10^{-1})$ 即可。

整除保留整数即可，可能有 $1$ 的误差，需要作出调整。

可以发现，这一做法跟多项式除法“先翻转再求逆”的方法是一致的，  
实际上体现了多项式除法的直观意义。

## 高精度开根

开根可以使用牛顿迭代法计算

$$x^2-a=0$$

$$x=\dfrac{x_0}{2}+\dfrac{a}{2x_0}$$

每迭代一次精度翻倍，结合倍增可以 $\Theta(n\log n)$ 求出。

## 高精度 ln 和 exp
与多项式 ln 和 exp 不同的是，$\ln f(x)=\displaystyle\int^x\dfrac{f'(t)}{f(t)}\mathrm{d}t$ 没法用了。

这里搬一下 WC2012《理性愉悦: 高精度数值计算》中的原内容，对于数列 

$$a_0=a,b_0=b,a_{n+1}=\dfrac{a_n+b_n}{2},b_{n+1}=\sqrt{a_nb_n}\quad(n\in \mathbf{N})$$

则 $\displaystyle \lim_{n\rightarrow\infty}a_n=\lim_{n\rightarrow\infty}b_n=\dfrac{\pi}{2}{\left(\int_0^{\frac{\pi}{2}}\dfrac{\mathrm{d}x}{\sqrt{a^2\cos^2x+b^2\sin^2x}}\right)}^{-1}$，  
且跟牛顿迭代一样误差是平方级别的缩小。

称这一极限为 $a,b$ 的**算术几何平均数**，记为$\operatorname{AG}(a,b)$ 。它有如下性质：

$$\forall x\ge 4,{\left|\dfrac{\pi}{2\operatorname{AG}{\left(1,\dfrac{4}{x}\right)}}-\ln x\right|}\le\dfrac{64}{x^2}{\left(8+\ln\dfrac{x}{4}\right)}$$

$\pi$ 可通过 Salamin-Brent 算法计算。若取 $a=1,b=\dfrac{1}{\sqrt{2}}$ 为上文数列的初值，则

$$\lim_{n\rightarrow\infty} \dfrac{4a_n^2}{1-\displaystyle\sum_{k=0}^n2^k(a_k-b_k)^2}=\pi$$

同样误差是平方级别的缩小。

对于较大的 $x$，可以通过计算 $\dfrac{\pi}{2\operatorname{AG}{\left(1,\dfrac{4}{x}\right)}}$ 达到 $\lfloor\log_{10}x\rfloor$ 的精度。



对于较小的 $x$，
- 若 $x>1$，可以通过 $\ln x=\dfrac{1}{2}\ln x^2$ 放大 $x$ 来提高精度。
- 否则，计算出 $\ln 10$ 后，通过 $\ln x=\ln (10^mx)-m\ln 10$ 提高精度。

时间复杂度 $\Theta(n\log^2 n)$。

有了 ln 后，exp 也就可用牛顿迭代求得。

## 总结
相比于仅仅是将整数换为小数，就能更有效地解决乘除、开根一类的问题。

由此可见，看待问题的角度，有时比解决问题的方法更为重要。

---

## 作者：stripe_python (赞：6)

蒟蒻的第一篇黑题题解。

前置知识：$O(n \log n)$ 高精度乘法 + $O(n^2)$ 高精度除法 + 牛顿迭代（当然还有求导）。

对于 $\lfloor \dfrac{a}{b} \rfloor$，普通压位试商很难通过，考虑使用牛顿迭代计算 $\dfrac{1}{b}$ 的近似值，然后使用 $a \times \dfrac{1}{b}$ 计算并调整得到精确值。

牛顿迭代的式子如下： 

$$
x=x_0-\dfrac{f(x_0)}{f'(x_0)}
$$

求解 $\dfrac{1}{b}$ 就是解方程 $x-\dfrac{1}{b}=0$，将 $f(x)=x-\dfrac{1}{b}$ 代入得

$$
\begin{aligned}
x&=x_0-\dfrac{f(x_0)}{f'(x_0)}\\
&=x_0-\dfrac{x_0-\dfrac{1}{b}}{1}\\
&=\dfrac{1}{b}
\end{aligned}
$$

没什么用。那么换个方程 $\dfrac{1}{x}-b=0$ 代入

$$
\begin{aligned}
x&=x_0-\dfrac{f(x_0)}{f'(x_0)}\\
&=x_0-\dfrac{\dfrac{1}{x_0}-b}{-\dfrac{1}{{x_0}^2}}\\
&=2x_0-b{x_0}^2
\end{aligned}
$$

其实和多项式求逆的 $g(x)\equiv 2g_0(x)-f(x){g_0}^2(x) \pmod {x^n}$ 一样。

这个迭代式是二阶收敛的，复杂度 $O(n \log n)$，但是需要使用高精小数。

下面的做法来自著名论文《理性愉悦：高精度数值计算》。

考虑把小数的那些位保存到整数上，也就是求得 $x=\lfloor \dfrac{10^{2n}}{b} \rfloor$，那么设 $x_0=\lfloor \dfrac{10^{2n_0}}{b_0} \rfloor$，代入 $x=2x_0-b{x_0}^2$ 得：

$$
\dfrac{10^{2n}}{b}=2\dfrac{ \dfrac{10^{2n_0}}{b_0}}{10^{n-n_0}}-b(\dfrac{ \dfrac{10^{2n_0}}{b_0}}{10^{n-n_0}})^2
$$

整理得：

$$
x =2\times 10^{n-n_0} x_0-\dfrac{b{b_0}^2}{10^{2n_0}}
$$

为了保证调整次数，这里需要使 $b$ 的位数不过少，可以令 $b$ 左移到 $n_b \le 2n_a$。

取 $n_0=\lfloor \dfrac{n+2}{2} \rfloor$ 可得到复杂度为 $O(n \log n)$。

小优化：对于 $n \le 16$ 可以直接暴力计算。

关键代码如下：

```cpp
inline BigInteger BigInteger::move_r(int d) const {
	if (*this == 0 || d >= size) return 0;
	if (d == 0) return *this;
	BigInteger res; res.reserve(size - d + 1);
	for (int i = d + 1; i <= size; i++) res.push(digits[i]);
	return res;
}
inline BigInteger BigInteger::move_l(int d) const {
	if (*this == 0) return 0;
	if (d == 0) return *this;
	BigInteger res; res.reserve(size + d + 1);
	for (int i = 1; i <= d; i++) res.push(0);
	for (int i = 1; i <= size; i++) res.push(digits[i]);
	return res;
}

BigInteger BigInteger::newton_inv(int n) const {
	if (*this == 0) throw ZeroDivisionError();
	if (std::min(size, n - size) <= NEWTON_MIN_LEVEL) {  // 取 NEWTON_MIN_LEVEL = 16
		BigInteger a; a.resize(n + 1);
		std::memset(a.digits, 0, sizeof(digit_t) * a.size);
		a.digits[n + 1] = 1;
		return a.divmod(*this, true).first;
	}
	int k = (n - size + 2) >> 1, k2 = k > size ? 0 : size - k;
	BigInteger x = move_r(k2);
	int n2 = k + x.size;
	BigInteger y = x.newton_inv(n2), a = y + y, b = (*this) * y * y;
	
	return a.move_l(n - n2 - k2) - b.move_r(2 * (n2 + k2) - n) - 1;
}

std::pair<BigInteger, BigInteger> BigInteger::newton_div(const BigInteger& x) const {
	int k = size - x.size + 2, k2 = k > x.size ? 0 : x.size - k;
	// 为了保证调整次数，这里需要使x的位数不过少
	BigInteger x2 = x.move_r(k2);
	if (k2 != 0) x2 += 1;
	int n2 = k + x2.size;
	BigInteger u = (*this) * x2.newton_inv(n2);
	BigInteger q = u.move_r(n2 + k2), r = (*this) - q * x;
	while (r >= x) q += 1, r -= x;  // 调整
	return std::make_pair(q, r);
}
```

完整代码可见 [BigInteger](https://www.luogu.com.cn/paste/om9o27fi)，这里就不给多项式求逆了。

---

