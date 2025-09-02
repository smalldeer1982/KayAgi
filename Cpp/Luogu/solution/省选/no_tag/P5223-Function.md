# Function

## 题目背景

${\rm CYJian}$最近想起了[水の三角](https://www.luogu.org/problemnew/show/P5014)，他觉得太水了，于是想了一个更加有意思的版本。

## 题目描述

给你$N$和$K$，请你求出：

$$\sum_{i=1}^{K}f[N][i] \ (\bmod\ 998244353)$$

其中：

$$f[i][j]=f[i-1][j]+f[i][j-1]+f[i-1][j-1](i>1,j \leq i)$$

$$f[1][1] = 1 \qquad f[i][0] = 0 \qquad f[i][j]=0(j>i)$$

## 说明/提示

对于$10\%$的数据：$1 \leq N \leq 10^3 \qquad 1 \leq K \leq 10^2$

对于$30\%$的数据：$1 \leq N \leq 10^6 \qquad 1 \leq K \leq 10^2$

对于$50\%$的数据：$1 \leq N \leq 10^{18} \qquad 1 \leq K \leq 10^2$

对于另$20\%$的数据：$1 \leq N \leq 10^6 \qquad 1 \leq K \leq 10^3$

对于$100\%$的数据：$1 \leq N \leq 10^{18} \qquad 1 \leq K \leq 10^3$

保证$K \leq N$

Upd：时限改为了：第$1$~$35$的测试点时限为$600ms$，第$36$~$50$的测试点时限为$400ms$。

## 样例 #1

### 输入

```
1 1```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
11
```

## 样例 #4

### 输入

```
4 3
```

### 输出

```
23
```

# 题解

## 作者：SSerxhs (赞：7)

提供一种乱搞做法

由递推式可以知道,$f[i][j](j\leq i)$一定是一个关于$i$的$j-1$次函数。具体证明可以通过数学归纳法，这里略去。所以可以考虑打表打出$f[2000][1000]$以内的值，用拉格朗日重心插值法$O(k)$插值并求值，总复杂度$O(k^2)$。

```cpp
#include <stdio.h>
#include <string.h>
typedef long long ll;
const int N=2002,M=1002,p=998244353;
int f[N][M],w[M],l[M],r[M],ifac[M],inv[M];
ll qq;
int main()
{
	register int n,m,i,j,k,tq,q,ans=0;
	scanf("%lld%d",&qq,&m);
	n=m<<1;tq=qq%p;tq+=p;
	for (i=1;i<=n;i++) f[i][1]=1;
	for (i=2;i<=n;i++)
	{
		k=i;if (k>m) k=m;
		for (j=1;j<=k;j++)
		{
			if ((f[i][j]=f[i-1][j]+f[i][j-1])>=p) f[i][j]-=p;
			if ((f[i][j]=f[i][j]+f[i-1][j-1])>=p) f[i][j]-=p;
		}
	}
	ifac[0]=ifac[1]=inv[1]=1;
	for (i=2;i<=m;i++) ifac[i]=(ll)ifac[i-1]*(inv[i]=p-(ll)p/i*inv[p%i]%p)%p;
	for (i=1;i<=m;i++)
	{
		k=(i<<1)-1;q=tq-i;
		for (j=i;j<=k;j++) w[j-i]=f[j][i];k-=i;
		for (j=0;j<=k;j++)
		{
			w[j]=(ll)w[j]*ifac[j]%p*ifac[k-j]%p;
			if ((j^k)&1) w[j]=p-w[j];
		}
		l[0]=q;
		for (j=1;j<=k;j++) l[j]=(ll)l[j-1]*(q-j)%p;
		r[k]=q-k;
		for (j=k-1;~j;j--) r[j]=(ll)r[j+1]*(q-j)%p;
		ans=(ans+(ll)r[1]*w[0]+(ll)l[k-1]*w[k])%p;
		for (j=1;j<k;j++) ans=(ans+(ll)l[j-1]*r[j+1]%p*w[j])%p;
	}
	printf("%d",(ans+1)%p);
}
```


---

## 作者：wangyizhi (赞：5)

[**题目传送门**](https://www.luogu.com.cn/problem/P5223)

多项式做法。

~~喜提最劣解！！！~~

## 题目分析

下文中所有题目中的下标都减 $1$。

考虑每一列的生成函数：

$$F_m(x)=\sum_{i=0}^{m}f_{m,i}x^i$$

考虑先从前一行转移过来。即令 $g_{i,j}=f_{i-1,j-1}+f_{i-1,j}$。此时有

$$G_m=F_{m-1}*(x+1)$$

再考虑从本行转移。此时有 $f_{i,j}=f_{i,j-1}+g_{i,j}$。相当于对 $G_m$ 做了一个前缀和。

令 $A_m(x)=\sum_{i=0}^{m-1}x^i$。则可得 $F_m=F_{m-1}*(x+1)*A_m \bmod x^m$

考虑如何计算。注意到当 $m>k$ 的时候我们事实上只需用到前 $k$ 项。于是此时的式子就可以写成 $F_m=F_{m-1}*(x+1)*A_k \bmod x^k$ 。这部分可以用多项式快速幂解决。

当 $m\le k$ 的时候，我们直接暴力计算，把所有 $(x+1)*A_m$ 卷起来即可。

前 $k$ 个多项式卷积时间复杂度 $O(k^2\log k)$，多项式快速幂由于蒟蒻比较懒所以写了 $O(k\log k\log n)$。总时间复杂度 $O(k^2 \log k + k \log k \log n)$

## AC Code

```cpp
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
//bool Mst;
const int N=(1<<20)+5,mod=998244353;
inline int qpow(int a,int b,int mod){int res=1;while(b){if(b&1)res=1ll*res*a%mod;b>>=1,a=1ll*a*a%mod;}return res;}
const int B=3,iB=qpow(B,mod-2,mod);
int rev[N];
inline int rd(int x){return x>=mod?x-mod:x;}
inline int pr(int x){return x<0?x+mod:x;}
void ntt(int *a,int n,int op)
{
	for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int mid=1,len=2;mid<n;mid<<=1,len<<=1)
		for(int i=0,g=qpow(op>0?B:iB,(mod-1)/len,mod);i<n;i+=len)
			for(int j=0,x,y,o=1;j<mid;j++,o=1ll*o*g%mod)
				x=a[i+j],y=1ll*o*a[i+j+mid]%mod,a[i+j]=rd(x+y),a[i+j+mid]=pr(x-y);
	if(op<0)
	{
		int iv=qpow(n,mod-2,mod);
		for(int i=0;i<n;i++) a[i]=1ll*a[i]*iv%mod;
	}
}
ll n,k;int a[N],f[N],g[N],sz=1,l,ans;
void power(ll n)
{
	if(n==0){f[0]=1;return;}
	power(n>>1);
	ntt(f,sz,1);for(int i=0;i<sz;i++)f[i]=1ll*f[i]*f[i]%mod;
	ntt(f,sz,-1);for(int i=k;i<sz;i++)f[i]=0;
	if(n&1)
	{
		ntt(f,sz,1);for(int i=0;i<sz;i++)f[i]=1ll*f[i]*a[i]%mod;
		ntt(f,sz,-1);for(int i=k;i<sz;i++)f[i]=0;
	}
}
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
//	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>k;
	while(sz<(k<<1)) sz<<=1,l++;
	for(int i=1;i<sz;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	g[0]=1;a[0]=1;
	for(int i=1;i<=min(n,k);i++)
	{
		a[i]=2;
		ntt(a,sz,1),ntt(g,sz,1);for(int j=0;j<sz;j++)g[j]=1ll*g[j]*a[j]%mod;
		ntt(a,sz,-1),ntt(g,sz,-1);for(int j=i;j<sz;j++)g[j]=0; 
	}
	ntt(a,sz,1);
	power(max(n-k,0ll));
	ntt(f,sz,1),ntt(g,sz,1);
	for(int i=0;i<sz;i++)  f[i]=1ll*f[i]*g[i]%mod;
	ntt(f,sz,-1);
	for(int i=0;i<k;i++) ans=(ans+f[i])%mod;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：CYJian (赞：4)

## Function

### 10分做法

直接拿转移方程搞就好了。。

### 50分做法

直接拿[水の三角](https://www.luogu.org/problemnew/show/P5014)的做法，相当于$K$次询问($1$~$K$)加起来。。

### 另一个50分做法

应该还是挺好想的。。

首先拿出那个转移方程：

$$f[i][j]=f[i][j - 1] + f[i-1][j-1] + f[i-1][j]$$

如果我们把$f[i][j-1]$拆开：

$$f[i][j] = f[i][j-2]+f[i-1][j-2]+2f[i-1][j-1] + f[i-1][j]$$

如果把第一维为$i$的一直拆下去的话，式子就成了这个样子：

$$f[i][j] = 2\sum_{k=1}^{j-1} f[i-1][k] + f[i-1][j]$$

然后就能矩阵快速幂了是吧。。

大概就构造个这样的矩阵就好了。。(太弱了只会用表格)

$A=$

| **1** | **2** | **2** | $\dots$ | **2** | **2** | **2** |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| **0** | **1** | **2** | $\dots$ | **2** | **2** | **2** |
| **0** | **0** | **1** | $\dots$ | **2** | **2** | **2** |
| $\dots$ | $\dots$ | $\dots$ | $\dots$ | $\dots$ | $\dots$ | $\dots$ |
| **0** | **0** | **0** | $\dots$ | **1** | **2** | **2** |
| **0** | **0** | **0** | $\dots$ | **0** | **1** | **2** |
| **0** | **0** | **0** | $\dots$ | **0** | **0** | **1** |

然后拿$A^N \ast f_0$做答案就行了。。

$f_1$是一个$K \ast 1$的矩阵，从上到下分别是$f[0][1],f[0][2]\dots$

### 70分做法

合并两种50分做法。

### 100分做法

其实和上面的做法差不多。。

可以考虑构造一个多项式$A(x)=1+2x+2x^2+2x^3+2x^4 \dots+2x^k$

然后设$f_i(x)=f[i][0]+f[i][1]x+f[i][2]x^2+f[i][3]x^3\dots+f[i][k]x^k$

易得：$f_{i+1}(x) = f_i \ast A(x)\ (\bmod\ x^{k+1})$

然后我们就可以得到：$f_N=f_k \ast A^{N-k}(x)$

这样就只需要按照转移方程暴力跑出$f_k$的系数，然后一个多项式快速幂就行了。。

注意：不能用$f_i (i < k)$乘。因为涉及取模的$x_{i+1}$不同。$i<k$的时候，取模的$x$的幂次为$i+1$，而$i \ge k$的时候，更大的位置的答案是不需要的了。所以我们可以不用$x^{i+1}$而是$x^{k+1}$。

不信可以自己试试。

### 100分做法(顺便提一句)

事实上。。BM套上去也是可以做的。。BM怎么做的话。。可以在[fjzzq2002的博客](https://www.cnblogs.com/zzqsblog/p/6877339.html)上找到一篇讲解。

代码太丑了，就不放了。。

---

## 作者：lemondinosaur (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P5223)

---
首先观察一下这个网格图的走法，实际上就是 [水の三角(修改版)](https://www.luogu.com.cn/problem/P5014)

$f[i-1][j-1]$ 相当于是横叉边，$f[i-1][j]$ 和 $f[i][j-1]$ 相当于三角形的斜边。

引用 水の三角 的结论：

$$
f[n][i]=\sum_{j=0}^{i-1}\binom{n-1+i-1-j}{j}\left[\binom{n-1+i-1-j*2}{n-1-j}-\binom{n-1+i-1-j*2}{n-j}\right]
$$

也就是枚举 $j$ 条横叉边，那么路径长度就是 $n-1+i-1-j$，从中选择 $j$ 条横叉边。

在 $n-1+i-1-j*2$ 条斜边中选择 $n-1-j$ 条往上斜，不合法的方案类似于卡特兰数的求法，减去选择 $n-j$ 条斜边往上斜的方案。

这个式子有点不好看，考虑将 $n$ 和 $i$ 都减一，实际上就是

$$
f[n][i]=\sum_{j=0}^{i}\binom{n+i-j}{j}\left[\binom{n+i-j*2}{i-j}-\binom{n+i-j*2}{i-j-1}\right]
$$

观察到在 $i=j$ 时 $i-j-1$ 是一个负数，不妨单独把这一项提出来，也就是

$$
f[n][i]=\binom{n}{i}+\sum_{j=0}^{i-1}\binom{n+i-j}{j}\left[\binom{n+i-j*2}{i-j}-\binom{n+i-j*2}{i-j-1}\right]
$$

可以发现组合数实际上是可以在 $O(k^2)$ 内预处理出来的。

具体地，可以先求出 $C(n-k,0\sim k)$，因为 $k$ 足够小，所以直接在 $O(k)$ 的时间复杂度内解决。

然后直接用杨辉三角求出 $C(n-k\sim n+k,0\sim k)$ 就可以了。

时间复杂度为 $O(k^2)$

---
代码
```cpp
#include <iostream>
using namespace std;
const int N=1011,mod=998244353;
int k,ans,c[N<<1][N],inv[N]; long long n;
int mo(int x,int y){return x+y>=mod?x+y-mod:x+y;}
int main(){
	ios::sync_with_stdio(0);
	c[0][0]=1,inv[0]=inv[1]=1;
	cin>>n>>k,--n,--k;
	for (int i=2;i<=k;++i) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for (int i=1;i<=k;++i){
		if ((n-k-i+1)%mod==0) break;
	    c[0][i]=(n-k-i+1)%mod*c[0][i-1]%mod*inv[i]%mod;
	}
	for (int i=1;i<=2*k;++i){
		c[i][0]=c[i-1][0];
		for (int j=1;j<=k;++j)
		    c[i][j]=mo(c[i-1][j-1],c[i-1][j]);
	}
	for (int i=0;i<=k;++i){
		ans=mo(ans,c[k][i]);
		for (int j=0;j<i;++j)
		    ans=mo(ans,1ll*c[k+i-j][j]*mo(c[k+i-j*2][i-j],mod-c[k+i-j*2][i-j-1])%mod);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Weng_Weijie (赞：1)

记状态

$$v_i=\begin{bmatrix}f[i][1]&f[i][2] &\dots&f[i][K]\end{bmatrix}$$

由于前 $K$ 行十分不优美（即有 $j\gt i$ 的情况），所以钦定 $i\geq K$

搞出转移矩阵

$$C=\left[\begin{matrix}1&2&2&\cdots&2\\&1&2&\cdots&2\\&&1&\cdots&2\\&&&\ddots\\&&&&1\end{matrix}\right]$$

然后用线性递推模板区的线性代数魔法优化

显然 $C$ 的特征多项式为 $f(\lambda)=(\lambda-1)^K$

只需要计算 $x^{n-K} \bmod f(x)$ 的各项系数对应乘上初始值的和即可

复杂度 $O(K^2\log n)$

可以使用 FFT 优化，由于需要递推前 $K$ 行，复杂度为 $O(k^2+k\log k\log n)$

```cpp
#include <iostream>

const int mod = 998244353;
const int N = 2005;
using LL = long long;
LL n;
int k, f[N], p[N], tmp[N];
void reduce(int &x) {
    x += x >> 31 & mod;
}
int pow(int x, int y, int ans = 1) {
    for (; y; y >>= 1, x = (LL) x * x % mod)
        if (y & 1) ans = (LL) ans * x % mod;
    return ans;
}
void poly_pow(LL n) {
    if (n == 0) { f[0] = 1; return; }
    poly_pow(n >> 1);
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j)
            reduce(tmp[i + j + (n & 1)] += (LL) f[i] * f[j] % mod - mod);
    for (int i = k + k - 1; i >= k; --i) {
        for (int j = 0; j < k; ++j)
            reduce(tmp[i - (k - j)] -= (LL) tmp[i] * p[j] % mod);
        tmp[i] = 0;
    }
    for (int i = 0; i < k; ++i) f[i] = tmp[i], tmp[i] = 0;
}
int s[N][N], sum[N];
int main() {
    std::cin >> n >> k;
    if (k == 1) {
        std::cout << "1" << std::endl;
        return 0;
    }
    p[0] = 1;
    for (int i = 1; i < k; ++i) p[i] = (LL) p[i - 1] * pow(i, mod - 2) % mod * (k - i + 1) % mod;
    for (int i = k - 1; i >= 0; i -= 2) p[i] = mod - p[i];
    poly_pow(n - k);
    s[0][0] = 1; 
    for (int i = 1; i < k << 1; ++i)
        for (int j = 1; j <= std::min(k, i); ++j)
            s[i][j] = ((LL) s[i - 1][j] + s[i][j - 1] + s[i - 1][j - 1]) % mod, reduce(sum[i] += s[i][j] - mod);
    int ans = 0;
    for (int i = 0; i < k; ++i)
        reduce(ans += (LL) sum[k + i] * f[i] % mod - mod);
    std::cout << ans << std::endl;
    return 0;
}
```


---

## 作者：zjhztxy (赞：0)

并不需要多项式科技。。。

首先暴力递推$f[i][j]$的前$k$行，然后就可以无视$j \le i$的条件。

令$f[i][j]$的生成函数为$F_i(x)=\sum_{j=0}^kf[i][j]x^j$

由递推式

$$f[i][j]=f[i-1][j]+f[i][j-1]+f[i-1][j-1]$$

得出
$$f[i][j]-f[i][j-1]=f[i-1][j]+f[i-1][j-1]$$

所以
$$(1-x)F_i(x)=(1+x)F_{i-1}(x)$$
$$F_i(x)=\frac{1+x} {1-x}F_{i-1}(x)$$
那么
$$F_n(x)=\frac{(1+x)^{n-k}}{(1-x)^{n-k}}F_k(x)$$
注意到
$$(1+x)^n=\sum_{i=0}^n \binom n i x^i$$
$$\frac 1 {(1-x)^n}=\sum_{i=0}\binom {i+n-1}{n-1}x^i$$
那么直接将$F_k(x)$乘上这两个玩意就行了。

什么？为啥要写FFT？暴力乘啊！
```cpp
#include<cstdio>
#define ll long long
using namespace std;
ll tmp[1005][1005], f[2005], g[1005];
const ll mod = 998244353;
ll qpow(ll a, ll b, ll k)
{
	ll res = 1;
	while(b)
	{
		if(b & 1) res = res * a % k;
		a = a * a % k;
		b >>= 1;
	}
	return res;
}
int main()
{
	ll n, k, t0, ans = 0;
	tmp[1][1] = 1;
	scanf("%lld%lld", &n, &k);
	for(int i = 2; i <= k; i++)
		for(int j = 1; j <= i; j++)
			tmp[i][j] = (tmp[i - 1][j] + tmp[i][j - 1] + tmp[i - 1][j - 1]) % mod;
	for(int i = 1; i <= k; i++) f[i] = tmp[k][i];
	n -= k;
	g[0] = 1;
	for(int i = 1; i <= k; i++)
	{
		t0 = (n - i + 1) % mod;
		g[i] = g[i - 1] * t0 % mod * qpow(i, mod - 2, mod) % mod;
	}
	for(int i = k; i; i--)
	{
		t0 = 0;
		for(int j = 0; j <= i; j++)
			t0 = (t0 + f[j] * g[i - j] % mod) % mod;
		f[i] = t0;
	}
	for(int i = 1; i <= k; i++)
	{
		t0 = (n + i - 1) % mod;
		g[i] = g[i - 1] * t0 % mod * qpow(i, mod - 2, mod) % mod;
	}
	for(int i = k; i; i--)
	{
		t0 = 0;
		for(int j = 0; j <= i; j++)
			t0 = (t0 + f[j] * g[i - j] % mod) % mod;
		f[i] = t0;
	}
	for(int i = 1; i <= k; i++) ans = (ans + f[i]) % mod;
	printf("%lld", ans);
	return 0;
}
```
时间$\Theta(k^2+k\log mod)$，暴打多项式快速幂。

---

