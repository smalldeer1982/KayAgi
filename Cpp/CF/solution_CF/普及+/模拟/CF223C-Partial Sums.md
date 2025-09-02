# Partial Sums

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers. The array elements are indexed from 1 to $ n $ . Let's determine a two step operation like that:

1. First we build by the array $ a $ an array $ s $ of partial sums, consisting of $ n $ elements. Element number $ i $ ( $ 1<=i<=n $ ) of array $ s $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF223C/c051478f9fc3965030766767424a5562a646a777.png). The operation $ x mod y $ means that we take the remainder of the division of number $ x $ by number $ y $ .
2. Then we write the contents of the array $ s $ to the array $ a $ . Element number $ i $ ( $ 1<=i<=n $ ) of the array $ s $ becomes the $ i $ -th element of the array $ a $ ( $ a_{i}=s_{i} $ ).

You task is to find array $ a $ after exactly $ k $ described operations are applied.

## 样例 #1

### 输入

```
3 1
1 2 3
```

### 输出

```
1 3 6
```

## 样例 #2

### 输入

```
5 0
3 14 15 92 6
```

### 输出

```
3 14 15 92 6
```

# 题解

## 作者：ql12345 (赞：6)

### 题意：

求一个数组求k次前缀和后的数组

n<=2000,k<=1e9,ai<=1e9

### Solution：

n这么大，肯定不能矩阵快速幂

先手玩小范围试试，想推出系数的表达式：

```
a1  a2      a3        a4

1 | 1 1 | 1  1 1 | 1  1  1 1    k=1
1 | 2 1 | 3  2 1 | 4  3  2 1    k=2
1 | 3 1 | 6  3 1 | 10 6  3 1    k=3
1 | 4 1 | 10 4 1 | 20 10 4 1    k=4
1 | 5 1 | 15 5 1 | 35 15 5 1    k=5
a1 a1 a2 a1 a2 a3 a1 a2 a3 a4

```

咦？a4这一大列，同一小列上的数怎么这么熟悉？
~~然后你显然可以发现就是组合数~~

然后在帕斯卡三角上对，就可以得到：

ai对最后答案中aj的贡献（系数）为C(j+k-i-1,j-i)

然后就可以O(N^2)计算出答案了

其实，对这个结论还有另一种理解方式：

```
a1   a2   a3   a4
|    |    |    |
s1---s2---s3---s4
|    |    |    |
ss1--ss2--ss3--ss4
```
第一次的前缀和显然是固定的，s1可以对s2和ss1做贡献，然后再通过这两个对别的做贡献，所以最后s1到一点的方案数，就是s1对这一点的贡献

坐标：(1,i)->(k,j) 显然方案数就是C(j+k-i-1,j-i)

### 实现：

困难在计算组合数：显然不可以暴力预处理阶乘，也不可以暴力算阶乘（k太大了）

可以发现，我们需要的组合数中m和n的差都是固定的，所以可以先算出来j-i=0的情况，然后递推，将n和m各多乘1个即可推出所有需要的组合数，查询的时候，直接找j-i为一个值的组合数即可

时间复杂度O(N)

### Code：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,k,a[2020],inv[2020],c[2020];
signed main(){
	cin>>n>>k; for(int i=1;i<=n;++i)cin>>a[i];
	if(!k){for(int i=1;i<=n;++i)cout<<a[i]<<' ';return 0;}
	inv[0]=inv[1]=1; for(int i=2;i<=n;++i)inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	c[0]=1; for(int i=1;i<=n;++i)c[i]=c[i-1]*inv[i]%mod*(i+k-1)%mod;
	for(int i=1,ans=0;i<=n;++i,ans=0){
		for(int j=1;j<=i;++j)(ans+=a[j]*c[i-j]%mod)%=mod;
		cout<<ans<<' ';
	}
}
```


---

## 作者：nekko (赞：5)

就是这玩意：https://loj.ac/problem/6261

感觉就是个div2A难度啊？连ntt都不需要

# 题目大意

给定序列 $\{a_n\}$，求其 $k$ 次前缀和的结果

其中 $1 \le n \le 2000, 0 \le k \le 10^9$，答案模 $10^9+7$

# 算法讨论

对于形式幂级数 $A(x)$，以及实数 $p$ 来说，有下式成立：

$$F(x)=A(x)^p \Rightarrow A(x)F'(x)=pF(x)A'(x)$$

对于一个序列 $\{a_n\}$ 来说，求一次前缀和相当于把 $A(x)$ 变为 $\frac{A(x)}{1-x}$

若做 $k$ 次前缀和，相当于乘上 $\frac{1}{(1-x)^k}$，由于乘法具有结合律，只需要考虑后式即可

令 $F(x)=\sum_{n=0}^{\infty}f_nx^n=\frac{1}{(1-x)^k}$，则有：

$$ \begin{aligned} &F(x)=\frac{1}{(1-x)^k}=(1-x)^{-k} \\ \Rightarrow &(1-x)F'(x)=-kF(x)(-1)=kF(x) \\ \Rightarrow &\sum_{n=0}^{\infty}f_{n+1}(n+1)x^n-\sum_{n=1}^{\infty}f_nnx^n=\sum_{n=0}^{\infty} kf_nx^n \end{aligned} $$

即：

$$ \begin{cases} f_0=F(0)=1 \\ f_{0+1}(0+1)=kf_0 \Rightarrow f_1=k \\ f_{n+1}(n+1) - f_nn=kf_n \quad (n \ge 1) \\ \end{cases} $$

最后一个即：

$$ \begin{aligned} &f_{n+1}=\frac{(k+n)f_n}{n+1} \\ \Rightarrow &f_{n}=\frac{(k+n-1)f_{n-1}}{n} \\ \end{aligned} $$

因此可以 $O(n)$ 计算出 $\{f_n\}$ 后，再进行一次 $O(n^2)$ 的卷积即可

---

## 作者：johnsmith0x3f (赞：4)

## 0x00 Outline

给定 $\{ a_n \}$ 和 $k$，求数组 $\{ a_n \}$ 的 $k$ 阶前缀和数组。

## 0x01

设 $\{ a_n \}$ 的 $k$ 阶前缀和为 $\{ pre_n^k \}$，其中

$$
pre_i^k = 

\begin{cases}

a_i & k = 0 \\

pre_{i-1}^k + pre_i^{k-1} & k > 0 \\

\end{cases}
$$

显然对每个 $1 \le j \le i$ 都有一个确定的系数 $c_j$，使得

$$
pre_i^k = \sum_{j=1}^i c_ja_j
$$

## 0x02

考虑如何求 $c_j$：注意到 $pre$ 的递推式形式与杨辉三角相同，不难得出 $c_j =  C_{k+i-j}^{i-j}$。

但此题 $k$ 太大，无法预处理阶乘，此时又注意到 $i-j \le n \le 2000$，则我们可以 $O(n^2)$ 对 $i-j$ 的每种取值暴力预处理出对应的组合数。

## 0x03 Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){
	int x = 0, f = 1; char c = getchar();
	while(isdigit(c)^1) f &= (c!=45), c = getchar();
	while(isdigit(c)) x = (x<<1) + (x<<3) + (c^48), c = getchar();
	return f ? x : -x;
}

const int maxn = 2005;
const int mod = 1000000007;
int n, m, a[maxn], inv[maxn], C[maxn];

inline void init(){
	inv[1] = 1;
	for(int i=2; i<=n; ++i) inv[i] = (mod-mod/i) * inv[mod%i] % mod;
}

signed main(){
	n = read(), m = read(), init(), C[0] = C[1] = 1;
	for(int i=1; i<=n; ++i) a[i] = read();
	for(int i=1; i<=n; C[++i]=1)
		for(int j=1; j<=i; ++j) C[i] = C[i] * (m+j-1) % mod * inv[j] % mod;
	for(int i=1, ans=0; i<=n; ++i, ans=0){
		for(int j=1; j<=i; ++j) ans = (ans+C[i-j]*a[j]%mod) % mod;
		printf("%lld ", ans);
	}
	return 0;
}
```

---

## 作者：RE_Prince (赞：1)

# CF223C Partial Sums

[link](https://www.luogu.com.cn/problem/CF223C)

## 思路

数学题。

我们先用四个数 $a_1,a_2,a_3,a_4$ 考虑 $k$ 次操作后的结果，找完规律再推广。

当 $k=0$：

$a_1=a_1,a_2=a_2,a_3=a_3,a_4=a_4$

当 $k=1$：

$a_1=a_1,a_2=a_1+a_2,a_3=a_1+a_2+a_3,a_4=a_1+a_2+a_3+a_4$

当 $k=2$：

$a_1=a_1,a_2=2a_1+a_2,a_3=3a_1+2a_2+a_3,a_4=4a_1+3a_2+2a_3+a_4$


当 $k=3$：

$a_1=a_1,a_2=3a_1+a_2,a_3=6a_1+3a_2+a_3,a_4=10a_1+6a_2+3a_3+a_4$

诶？最后一组的系数怎么那么熟悉呢？

再推几组，可以发现第 $k$ 次操作后的系数等同于杨辉三角形的第 $k$ 列的前 $n$ 个数。我们还知道杨辉三角形的第 $i$ 行第 $j$ 列的值等于 $C^j_i$。因此，这道题的根本就是求组合数。先预处理组合数，再枚举每个位置，以及之前的位置要乘上的系数（也就是算出来的组合数）。

求组合数先预处理阶乘，但是因为 $k$ 高达 $10^9$，所以我们必须化简下组合数的柿子：

$$C^j_i=\frac{i!}{j!(i-j)!}=\frac{1\times 2\times\cdots\times i}{1\times 2\times\cdots\times j\times (i-j)!}=\frac{(j+1)\times (j+2)\times\cdots\times i}{(i-j)!}$$
（为了大家方便理解就不写 $\Pi$ 了）

因为 $n$ 最大是 $2000$，所以 $i-j$ 最大也是 $2000$，不会超时。我们再预处理 $fac_i=fac_{i-1}\times (k+i)$，其中 $fac_0=0$。这是为了可以较快的求出组合数的分子。


因为要除，所以用费马小定理 
$$\frac{a}{b}\equiv a\times b^{p-2}\pmod p$$

至此，此题已经做完了。

贴个代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int n,m,i,j,k;
int fac[2009],f[2009],a[2009];
int ksm(int x,int y)
{
	int ret=1;
	while(y)
	{
		if(y&1) ret=ret*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ret;
}
int C(int j)
{
	return fac[j-k]*ksm(f[j-k],mod-2)%mod;
}
int c[100009];
signed main()
{
	cin>>n>>k;k--;
	for(i=1;i<=n;i++) cin>>a[i];
	f[0]=1;
	for(i=1;i<=n+1;i++) f[i]=f[i-1]*i%mod;
	fac[0]=1;
	for(i=1;i<=n+1;i++) fac[i]=fac[i-1]*(k+i)%mod;
	for(i=k;i<=k+n-1;i++) c[i-k+1]=C(i);
	for(i=1;i<=n;i++)
	{
		int cnt=0,ret=0;
		for(j=i;j>=1;j--)
		{
			cnt++;
			ret+=a[j]*c[cnt],ret%=mod;
		}
		cout<<ret<<" ";
	}
	return 0;
}
```

---

