# Combinatorics Problem

## 题目描述

# 组合数学问题


回顾一下二项式系数 $ \binom{x}{y} $ 的计算方法（其中 $ x $ 和 $ y $ 是非负整数）：

- 如果 $ x < y $ ，则 $ \binom{x}{y} = 0 $ ；
- 否则，$ \binom{x}{y} = \frac{x!}{y! \cdot (x-y)!} $ 。

给定一个数组 $ a_1, a_2, \dots, a_n $ 和一个整数 $ k $ ，你需要计算一个新数组 $ b_1, b_2, \dots, b_n $ ，其中

- $ b_1 = (\binom{1}{k} \cdot a_1) \bmod 998244353 $ ；
- $ b_2 = (\binom{2}{k} \cdot a_1 + \binom{1}{k} \cdot a_2) \bmod 998244353 $ ；
- $ b_3 = (\binom{3}{k} \cdot a_1 + \binom{2}{k} \cdot a_2 + \binom{1}{k} \cdot a_3) \bmod 998244353 $ ，依此类推。

具体而言，$ b_i = (\sum\limits_{j=1}^{i} \binom{i - j + 1}{k} \cdot a_j) \bmod 998244353 $ 。

注意，数组以一种修改的方式给出，你也需要以一种修改的方式输出。

## 样例 #1

### 输入

```
5 8 2 3 100 2```

### 输出

```
1283```

# 题解

## 作者：hgzxwzf (赞：9)

### [CF1832E](https://www.luogu.com.cn/problem/CF1832E)
这么水的 $E$ 没有场切，菜死了。

$\begin{aligned}b_{i,k}&=\sum_{j=1}^iC_{i-j+1}^ka_j\\&=\sum_{j=1}^i(C_{i-j}^{k-1}+C_{i-j}^k)a_j\\&=\sum_{j=1}^iC_{i-j}^{k-1}a_j+\sum_{j=1}^iC_{i-j}^ka_j\\&=C_{0}^{k-1}a_i+b_{i-1,k-1}+C_{0}^ka_i+b_{i-1,k}\end{aligned}$

暴力算，时间复杂度 $O(nk)$。

[代码](https://codeforces.com/contest/1832/submission/205789618)。

---

## 作者：arrow_king (赞：4)

# CF1832E

真唐，秒了。

考虑差分，设 $b_n^{(j)}=\sum_{i=1}^n\binom{n-i+1}{j}a_i$。

拆组合数得到
$$
\begin{aligned}
b_{n}^{(j)}-b_{n-1}^{(j)}&=\dbinom{1}{j}a_n+\sum_{i=1}^{n-1}\dbinom{n-i+1}{j}a_i-\dbinom{n-i}{j}a_i\\
&=\dbinom 1ja_n+\sum_{i=1}^{n-1}\dbinom{n-i}{j-1}a_i\\
&=b_{n-1}^{(j-1)}+\dbinom 1ja_n
\end{aligned}
$$
于是这道题做完了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 10000005
#define mod 998244353
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll n,x,y,m,k,ans;
ll a[N],b[6][N];
int main() {
	n=read(),a[1]=read(),x=read(),y=read(),m=read(),k=read();
	for(int i=2;i<=n;i++) a[i]=(a[i-1]*x+y)%m;
	for(int i=1;i<=n;i++) b[0][i]=(b[0][i-1]+a[i])%mod;
	for(int j=1;j<=k;j++) {
		for(int i=1;i<=n;i++) b[j][i]=(b[j-1][i-1]+(j<=1)*a[i])%mod;
		for(int i=1;i<=n;i++) b[j][i]=(b[j][i]+b[j][i-1])%mod;
	}
	for(int i=1;i<=n;i++) {
		ll tmp=b[k][i]*i;
		ans^=tmp;
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：封禁用户 (赞：3)

# 题意
回顾一下二项式系数 $ \binom{x}{y} $ 的计算方法（其中 $ x $ 和 $ y $ 是非负整数）：

- 如果 $ x < y $，则 $ \binom{x}{y} = 0 $；
- 否则，$ \binom{x}{y} = \frac{x!}{y! \cdot (x-y)!} $。

给定一个数组 $ a_1, a_2, \dots, a_n $ 和一个整数 $ k $，你需要计算一个新数组 $ b_1, b_2, \dots, b_n $，其中

- $ b_1 = (\binom{1}{k} \cdot a_1) \bmod 998244353 $；
- $ b_2 = (\binom{2}{k} \cdot a_1 + \binom{1}{k} \cdot a_2) \bmod 998244353 $；
- $ b_3 = (\binom{3}{k} \cdot a_1 + \binom{2}{k} \cdot a_2 + \binom{1}{k} \cdot a_3) \bmod 998244353 $，依此类推。

具体而言，$ b_i = (\sum\limits_{j=1}^{i} \binom{i - j + 1}{k} \cdot a_j) \bmod 998244353 $。

注意，数组以一种修改的方式给出，你也需要以一种修改的方式输出。

输入的第一行包含六个整数 $ n $，$ a_1 $，$ x $，$ y $，$ m $ 和 $ k $。

数组 $[a_1, a_2, \dots, a_n] $ 的生成方式如下：

- 输入给定了 $ a_1 $；

- 对于 $ 2 \le i \le n $，$ a_i = (a_{i-1} \cdot x + y) \bmod m $。

由于输出最多可能有 $ 10^7 $ 个整数，可能会导致速度过慢，因此你需要进行以下处理：

设 $ c_i = b_i \cdot i $（不在乘法后取模 $ 998244353 $）。

输出整数 $ c_1 \oplus c_2 \oplus \dots \oplus c_n $，其中 $ \oplus $ 表示按位异或运算。

# 思路
我们知道，组合数有一个神奇的公式：

$$C^j_i=C^j_{i-1}+C^{j-1}_{i-1}$$

那么，我们可以对 $b_i$ 替换为：

$$ b_i = \sum\limits_{j=1}^{i} C_{i - j + 1}^{k} \times a_j$$

$$= \sum\limits_{j=1}^{i-1} C_{(i - 1) - j + 1}^{k} \times a_j + \sum\limits_{j=1}^{i-1} C_{(i - 1) - j + 1}^{k-1} \times a_j + C^k_0 \times a_i + C^{k-1}_0 \times a_i$$

由此，我们发现，第一项是 $b_{i-1}$，第二项是 $k-1$ 的 $i-1$ 项，后面两项都可以直接得到。这就是一个递推结构。

我们可以定义数组 $dp_{i,j}$ 表示：
$$ dp_{i,j} = \sum\limits_{j=1}^{i} C_{i - j + 1}^{j} \times a_j$$

转移方程：

$$ dp_{i,j} = \sum\limits_{j=1}^{i-1} C_{(i - 1) - j + 1}^{j} \times a_j + \sum\limits_{j=1}^{i-1} C_{(i - 1) - j + 1}^{j-1} \times a_j + C^j_0 \times a_i + C^{j-1}_0 \times a_i$$

$$=dp_{i-1,j} + dp_{i-1,j-1} + C^j_0 \times a_i + C^{j-1}_0 \times a_i$$

答案即为：
$$dp_{1,k} \oplus dp_{2,k} \oplus \dots \oplus dp_{n,k}$$


## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int n,x,y,m,k;
const int mod=998244353;
int a[10000010];
int dp[10000010][7];
void exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	int o=x;
	x=y;
	y=(o-(a/b)*y);
}
int jc[10000011];
int C(int a,int b){
	if(a<b){
		return 0;
	}
	int opt=jc[a];
	int s=jc[b],t=jc[a-b];
	int xx,yy,xxx,yyy;
	exgcd(s,mod,xx,yy);
	exgcd(t,mod,xxx,yyy);
	return ((opt*xx%mod*xxx)%mod+mod)%mod;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>a[1]>>x>>y>>m>>k;
	jc[0]=1;
	dp[1][0]=a[1];
	for(int i=1;i<=n;i++){
		jc[i]=jc[i-1]*i%mod;
	}
	for(int i=2;i<=n;i++){
		a[i]=(a[i-1]*x+y)%m;
		dp[i][0]=dp[i-1][0]+a[i];
	}
	for(int i=1;i<=n+1;i++){
		dp[i][1]=(dp[i-1][0]+dp[i-1][1]+C(0,1)*a[i])%mod;
	}
	for(int j=2;j<=k;j++){
		for(int i=1;i<=n+1;i++){
			dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]+C(0,j-1)*a[i])%mod;
		}
	}
	int ans=0;
	for(int i=2;i<=n+1;i++){
		ans^=(dp[i][k]*(i-1));
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：qiuzijin2026 (赞：2)

# Combinatorics Problem

[题面](https://www.luogu.com.cn/problem/CF1832E)

## 思路

数学题。

从题目给的式子入手：

$$
b_{i,k}=

\sum_{j = 1}^{i}

\begin{pmatrix}
  i-j+1 \\
  k \\
\end{pmatrix}

\times

a_{j}
$$

------------------------

$$
b_{i,k}=

\sum_{j = 1}^{i-1}

\begin{pmatrix}
  i-j+1 \\
  k \\
\end{pmatrix}

\times

a_{j}

+

\begin{pmatrix}
  1 \\
  k \\
\end{pmatrix}

\times

a_{i}
$$

------------------------

$$
b_{i,k}=

\sum_{j = 1}^{i-1}

\begin{pmatrix}
  (i-1)-j+1 \\
  k \\
\end{pmatrix}

\times

a_{j}

+

\sum_{j = 1}^{i-1}

\begin{pmatrix}
  (i-1)-j+1 \\
  k-1 \\
\end{pmatrix}

\times

a_{j}

+

\begin{pmatrix}
  1 \\
  k \\
\end{pmatrix}

\times

a_{i}
$$

------------

$$
b_{i,k}=b_{i-1,k}+b_{i-1,k-1}+ 

\begin{pmatrix}
  1 \\
  k \\
\end{pmatrix}

\times

a_{i}
$$

于是我们就可以愉快的递推了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
long long a,x,y,m;
long long md=998244353;
long long jc[10000005];
long long jcs[10000005];
long long ny[10000005];
long long f[2][10];
long long ans;
long long ksm(long long a,long long x){
	long long ans=1;
	while(x){
		if(x&1){
			ans*=a;
			ans%=md;
		}
		a*=a;
		a%=md;
		x>>=1;
	}
	return ans;
}
long long c(long long x,long long y){
	return (((jc[x]*ny[x-y])%md)*ny[y])%md;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&x,&y,&m,&k);
	jc[0]=1;
	jcs[0]=1;
	long long tp=max(n,k);
	for(int i=1;i<=tp;i++){
		jc[i]=jc[i-1]*i%md;
		jcs[i]=jcs[i-1]*jc[i]%md;
	}
	long long tmp=ksm(jcs[tp],md-2);
	for(int i=tp;i>=1;i--){
		ny[i]=tmp*jcs[i-1]%md;
		tmp=tmp*jc[i]%md;
	}
	ny[0]=1;
	for(long long i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			f[i%2][j]=(f[(i+1)%2][j]+(c(1,j)*a)%md)%md;
			if(j>0) f[i%2][j]=(f[i%2][j]+f[(i+1)%2][j-1])%md;
		}
		a=(a*x+y)%m;
		ans^=f[i%2][k]*i;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

我们直接对着 $b$ 的定义式 $b_i=\left(\sum\limits ^i_{j=1} \dbinom {i-j+1} k \cdot a_i\right)\bmod p$ 一堆猛推。

![](https://cdn.luogu.com.cn/upload/image_hosting/gam0quzz.png)

其中使用了 $\dbinom n m=\dbinom {n-1} {m}+\dbinom {n-1}{m-1}$。

证明：

![](https://cdn.luogu.com.cn/upload/image_hosting/n94qp3vv.png)

~~这样免掉一坨要人命的格式~~。我们发现，$b_i$ 的定义式可以推成两个长得和 $b_{i-1}$ 很像的，但是有一个 $k$ 变成了 $k-1$ 的式子。

我们不妨就对着 $b$ 来一顿猛拆，设 $f_{i,j}$ 表示 $b_i$ 在 $k$ 为 $j$ 时的取值。根据上面的推导不难得到 $f_{i,j}=f_{i-1,j}+f_{i-1,j-1}$。

然后按照这个转移就可以了，边界 $f_{i,0}=\sum\limits^i_{j=1} \sum\limits_{k=1}^j a_{k}$，直接把 $\dbinom n 0=1$ 带入即可。不难发现就是前缀和相加。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
using namespace std;
const int N=1e7+5, K=6;
long long a[N], pre[N], f[K][N];
long long n, m, x, y, k, i, j;
const int p=998244353;
long long ret;
int main( )
{
	scanf("%d %d %d %d %d %d", &n, a+1, &x, &y, &m, &k);
	rep(i, 2, n) a[i]=(x*a[i-1]%m+y)%m;
	rep(i, 1, n) pre[i]=(pre[i-1]+a[i])%p, f[1][i]=(f[1][i-1]+pre[i])%p;
	rep(i, 2, k) rep(j, 1, n) f[i][j]=(f[i-1][j-1]+f[i][j-1])%p;//,printf("%d %d %d\n",i,j,f[i][j]);
	rep(i, 1, n) ret^=f[k][i]*i;
	printf("%lld\n", ret);
	return 0;
}
```


---

## 作者：Prophesy_One (赞：2)

#### 题意：

给定 $n,k$，令 $f_x=(\sum_{i=1}^{x} C_{x-i+1}^{k} \times a_i) \bmod 998244353$，求 $\oplus_{i=1}^{n} i\times f_i$。

$n \leq 10^7,1 \leq k \leq 5$。

#### 思路：

赛时死磕 D 然后错过了大水 E。

由 $C_n^k=C_{n-1}^k+C_{n-1}^{k-1}$ 得

$f_{n,k}=\sum_{i=1}^{n} C_{n-i+1}^{k} \times a_i
=\sum_{i=1}^n (C_{n-i}^k+C_{n-i}^{k-1}) \times a_i
=f_{n-1,k-1}+f_{n-1,k}$。

暴力 $O(nk)$ 求解即可。

#### 代码：
```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=1e7+5;
const int mod=998244353;
ll n,k,m,x,y,a[N],f[N][7];
ll read()
{
	ll res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
int main()
{
	ll i,j,ans=0;
	n=read();a[1]=read();x=read();y=read();m=read();k=read();
	for(i=2;i<=n;i++)
	a[i]=(x*a[i-1]%m+y)%m;
	for(i=1;i<=n;i++)
	f[i][0]=f[i-1][0]+a[i];
	for(j=1;j<=k;j++)
		for(i=1;i<=n;i++)
		f[i][j]=(f[i-1][j-1]+f[i-1][j]+(j==1)*a[i])%mod;
	for(i=1;i<=n;i++)
	ans^=f[i][k]*i;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：FBW2010 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1832E)

# 前言

教练比赛时放的的题，本蒟蒻一直想按 $a$ 来递推，结果被模 $m$ ~~打趴在地~~。后来发现可以用组合数递推，便有了这篇题解。

# 思路

首先，题目中 $n \le 10^7$，而 $k \le 5$，我们不难想到用 $O(nk)$ 的复杂度递推解决此题。这时，我们需要引入一个组合数的重要递推式：

$$
\dbinom{n}{m}=\dbinom{n-1}{m}+\dbinom{n-1}{m-1}
$$

这时，递推式就显而易见了。我们设 $b_{i,j}$ 为 $k$ 的值是 $j$ 时 $b_i$ 的值，即可推出如下式子：

$$
b_{i,1}=b_{i-1,1}+\sum_{k=1}^{i}a_k
$$

$$
b_{i,j}=b_{i-1,j}+b_{i-1,j-1}
$$

然后就可以愉快地 AC 了！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e7+5,mod=998244353;
int n,x,y,m,k,ans,a[N],b[N][6];
signed main(){
	scanf("%lld %lld %lld %lld %lld %lld",&n,&a[1],&x,&y,&m,&k);
	b[1][1]=a[1];
	int sum=a[1],ans=b[1][k];
	for(int i=2;i<=n;i++){
		a[i]=(a[i-1]*x%m+y)%m;
		b[i][1]=((b[i-1][1]+sum)%mod+a[i])%mod;
		for(int j=2;j<=k;j++){
			b[i][j]=(b[i-1][j]+b[i-1][j-1])%mod;
		}
		ans^=b[i][k]*i;
		sum+=a[i];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：1)

大力开干。

$ b_i = \displaystyle\sum_{j=1}^{i} \binom{i - j + 1}{k} \times a_j $ 这个式子说明固定 $i$ 之后，所有 $a_j$ 前的系数是关于 $j$ 的 $k$ 阶多项式 $f(j)$，系数可以暴力乘得出。

设 $f(j)=\displaystyle\sum_{x=0}^k c_x\times j^x$，于是 $b_i = \displaystyle\sum\limits_{j=1}^{i} f(j)\times a_j=\displaystyle\sum_{x=0}^k c_x\sum_{j=1}^{i} j^x\times a_j$。

把一切问题统一化为求出 $\forall x\in[0,k],j^x \times a_j$ 关于 $j$ 的前缀和。

当然实际上 $i$ 不固定。那么可以再把 $c_x$ 写成关于 $i$ 的多项式 $g_x(i)$（同样暴力乘法得出），即将 $\displaystyle\binom{i - j + 1}{k}$ 写成关于 $i,j$ 的二元多项式并按照 $j$ 的次数整理。这样我们需要求出的东西不变，只是 $c_x$ 会随着 $i$ 的取值而变化。

[for reference only.](https://codeforces.com/contest/1832/submission/209241638)

---

## 作者：wzy2021 (赞：0)

[原题链接](https://codeforces.com/contest/1832/problem/E)

众所周知，有如下组合恒等式（由定义证明即可）：

$$\dbinom{n}{m} = \dbinom{n - 1}{m - 1} + \dbinom{n - 1}{m}$$

那么令 $f_{p, i} = \sum_{j=1}^i \dbinom{i - j + 1}{p}\times a_j$，由上述恒等式可得转移方程：

$$f_{p, i} = \sum_{j=1}^i\dbinom{i - j}{p}\times a_j + \dbinom{i - j}{p - 1}\times a_j = f_{p - 1, i - 1} + f_{p, i - 1}$$

由 $f$ 的定义，得到转移式子的初始化为：

$$f_{1, i} = \sum_{j=1}^i(i - j + 1)\times a_j$$

用一个前缀和优化即可，剩下直接暴力转移，复杂度 $O(nk)$。

由于本蒟蒻觉得空间会炸，所以用了滚动数组，具体见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e7 + 10;
const int mod = 998244353;

int a[N], s[N], f[2][N];

signed main() {
	int n, x, y, m, k; scanf ("%lld%lld%lld%lld%lld%lld", &n, &a[1], &x, &y, &m, &k);
	for (int i = 2; i <= n; ++i) a[i] = (1ll * a[i - 1] * x % m + y) % m;
	for (int i = 1; i <= n; ++i) s[i] = (s[i - 1] + a[i]) % mod, f[0][i] = (f[0][i - 1] + s[i]) % mod;
	int flag = 1;
	for (int p = 2; p <= k; ++p) {
		for (int i = 1; i <= n; ++i) f[flag][i] = (f[flag][i - 1] + f[flag ^ 1][i - 1]) % mod; flag ^= 1;
	} flag ^= 1;
	for (int i = 1; i <= n; ++i) f[flag][i] = 1ll * f[flag][i] * i;
	long long ans = 0;
	for (int i = 1; i <= n; ++i) ans ^= f[flag][i];
	printf ("%lld\n", ans); 
	return 0;
}

```


---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个长度为 $n$ 的序列 $a$ 和一个参数 $k$，你需要求出一个长度为 $n$ 的序列 $b$，满足：

$$
b_i=\sum_{j=1}^{i}\binom{i-j+1}{k}
$$

$1\leq n\leq 10^7,1\leq k\leq 5$。

## 思路

记 $b_{i,j}$ 表示当 $k=j$ 时的答案，则：

$$
\begin{aligned}
b_{n,k}&=\sum_{i=1}^{n}\binom{n-i+1}{k}a_i\\
&=\sum_{i=1}^{n}\left(\binom{n-i}{k-1}+\binom{n-i}{k}\right)a_i\\
&=\sum_{i=1}^{n}\binom{n-i}{k-1}a_i+\sum_{i=1}^{n}\binom{n-i}{k}a_i\\
&=\left(\binom{0}{k}+\binom{0}{k-1}\right)a_n+\sum_{i=1}^{n-1}\binom{n-i}{k-1}a_i+\sum_{i=1}^{n-1}\binom{n-i}{k}a_i\\
&=[k\in\{0,1\}]a_n+b_{n-1,k-1}+b_{n-1,k}
\end{aligned}
$$

直接递推，边界 $b_{n,0}=b_{n-1,0}+a_n$。

时间复杂度 $O(nk)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

const int N = 1e7 + 5;
int a[N], b[N][6], n, k;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int x, y, m; cin >> n >> a[1] >> x >> y >> m >> k;
    for(int i=2;i<=n;i++) a[i] = (1ll * a[i - 1] * x + y) % m;
    for(int i=1;i<=n;i++) b[i][0] = Add(b[i - 1][0], a[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(j == 1) b[i][j] = a[i];
            b[i][j] = Add(b[i][j], Add(b[i - 1][j], b[i - 1][j - 1]));
        }
    }
    long long ans = 0;
    for(int i=1;i<=n;i++) ans ^= 1ll * i * b[i][k];
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：wth2026 (赞：0)

# 题目大意
em……不好总结，自己看吧 _~~（逃~~_。
# 题目思路
_~~我就是个￥%#&~~_。

在教练考试的时候，我看见比赛名写的是计数，当时的我就天真的以为计数只能用**纯组合数学**，然后当场爆炸……

其实**用组合数学的公式换个思路想**是很简单的。

先把 $a$ 数组求出来，然后顺带着把 $f_{0,i}$ 和 $f_{1,i}$ 求出来，用求 $C^n_m$ 的公式的思路就可以轻而易举的想到 $f_{i,j} = f_{i-1,j-1} + f_{i-1,j}$。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define float double
#define int long long
#define inf 998244353

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

int ans, n, k, m, x, y, a[10000005], f[10000005][7];

void init() {
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	
	cin >> n >> a[1] >> x >> y >> m >> k;
	f[1][0] = f[1][1] = a[1];
	
	for (int i = 2; i <= n; ++ i) {
		a[i] = ((a[i - 1] * x) % m + y) % m;
		f[i][0] = (f[i - 1][0] + a[i]) % inf;
		f[i][1] = (f[i - 1][0] + f[i - 1][1] + a[i]) % inf;
	}
	
	for (int j = 2; j <= k; ++ j) {
		for (int i = 1; i <= n; ++ i) {
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % inf;
		}
	}
	
	for (int i = 1; i <= n; ++ i) {
		ans ^= f[i][k] * i;
	}
	
	cout << ans;
	return 0;
}
```

---

## 作者：729hao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1832E)

------------
## 思路
首先算出 $a$ 数组。

由题可得：
$$
b_i=\binom{i}{k}\times a_1+\binom{i-1}{k}\times a_2+\binom{i-2}{k}\times a_3+\cdots+\binom{2}{k}\times a_{i-1}+\binom{1}{k}\times a_i
$$
众所周知，组合数学有一个神奇的公式：
$$
\binom{n}{m}=\binom{n-1}{m}+\binom{n-1}{m-1}
$$
于是，我们可以得出：
$$
b_i=\color{red}\binom{i-1}{k}\times a_1+\binom{i-2}{k}\times a_2+\binom{i-3}{k}\times a_3+\cdots+\binom{1}{k}\times a_{i-1}+\color{blue}\binom{i-1}{k-1}\times a_1+\binom{i-2}{k-1}\times a_2+\binom{i-3}{k-1}\times a_3+\cdots+\binom{1}{k-1}\times a_{i-1}+\color{green}\binom{1}{k}\times a_i
$$
显然，上面的红色部分就是 $b_{i-1}$，蓝色部分就是当题目输入 $k$ 的值为 $k-1$ 时的 $b_{i-1}$。  
## 递推式
所以，我们定义 $B_{i,j}=\binom{i}{j}\times a_1+\binom{i-1}{j}\times a_2+\binom{i-2}{j}\times a_3+\cdots+\binom{2}{j}\times a_{i-1}+\binom{1}{j}\times a_i$。
则有递推式 $B_{i,j}=B_{i-1,j}+B_{i-1,j-1}+\binom{1}{j}\times a_i$。  
根据定义，$b_i=B_{i,k}$。  
**注意别忘了取模！**

那么怎么处理边界呢？

- $B_{1,i}=\begin{cases}a_1&i=1\\0&i>1\end{cases}$，根据定义显然如此。
- 因为对于任意自然数 $p$，$\binom{p}{0}=1$，所以 $B_{i,0}=\sum\limits_{j=1}^{i}a_j$。

最后递推算出 $b$ 数组，根据题目中 $c_i=b_i\times i$ 求出 $c$ 数组，最后算出 $c$ 数组的异或和即可。  
**注意 $c$ 数组不取模！**

时间复杂度 $O(nk)$，空间复杂度 $O(nk)$，均在题目数据范围内。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long Mod=998244353;
int n,k;
long long a[10000005],x,y,m,B[10000005][6],ans;
int main(){
	scanf("%d %lld %lld %lld %lld %d",&n,&a[1],&x,&y,&m,&k); 
	for(int i=2;i<=n;i++){
		a[i]=(a[i-1]*x+y)%m;
	}
	B[1][0]=B[1][1]=a[1];
	ans^=B[1][k]*1;
	for(int i=2;i<=n;i++){
		B[i][0]=(B[i-1][0]+a[i])%Mod;
		for(int j=1;j<=k;j++){
			B[i][j]=(B[i-1][j]+B[i-1][j-1])%Mod;
			if(j==1)B[i][j]=(B[i][j]+a[i])%Mod;
		}
		ans^=B[i][k]*i;
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：chlchl (赞：0)

距离赛后多久了？已经忘了。

现在才来补题，仍然记得那场 div 3 过后看着榜一的 dp 大呼惊奇：这题怎么这么 ** 简单！！！

## Solution
这一看就得推式子，那就推推看嘛。

观察式子：

$$b_i=\sum\limits_{j=1}^{i}C_{i-j+1}^{k}\times a_j$$

试图使用组合数基本公式：$C_{n}^{m}=C_{n-1}^{m}+C_{n-1}^{m-1}$ 拆开上面的式子。

好吧证明一下这个式子。

我们都知道 $C_{n}^{m}=\dfrac{n!}{m!(n-m)!}$。

所以有：

$$C_{n-1}^{m}+C_{n-1}^{m-1}=\dfrac{(n-1)!}{m!(n-m-1)!}+\dfrac{(n-1)!}{(m-1)!(n-m)!}$$

$$=\dfrac{(n-m)(n-1)!}{m!(n-m)!}+\dfrac{m(n-1)!}{m!(n-m)!}$$

$$=\dfrac{n(n-1)!}{m!(n-m)!}$$

$$=C_{n}^{m}$$

好的，那么我们令 $b_{i,j}=\sum\limits_{p=1}^{i}C_{i-p+1}^{j}\times a_p$。

则有：

$$b_{i,j}=\sum\limits_{p=1}^{i}\big(C_{i-p}^{j}+C_{i-p}^{j-1}\big)\times a_p$$

$$=\sum\limits_{p=1}^{i}C_{i-p}^{j}\times a_p+\sum\limits_{p=1}^{i}C_{i-p}^{j-1}\times a_p$$

$$=b_{i-1,j}+b_{i-1,j-1}$$

边界显然，$b_{i,0}=b_{i-1,0}+a_i$。

好了结束了，$O(nk)$ 直接跑递推即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int MOD = 998244353;
const int N = 1e7 + 10;
int n, k;
ll x, y, m, a[N], f[N][7];

int main(){
	scanf("%d%lld%lld%lld%lld%d", &n, &a[1], &x, &y, &m, &k);
	for(int i=2;i<=n;i++)
		a[i] = (a[i - 1] * x + y) % m;
	for(int i=1;i<=n;i++)
		f[i][0] = (f[i - 1][0] + a[i]) % MOD;
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % MOD;
			if(j == 1)
				(f[i][j] += a[i]) %= MOD;
		}
	}
	ll ans = 0;
	for(int i=1;i<=n;i++)
		ans ^= i * f[i][k];
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：0)

## [CF1832E Combinatorics Problem](https://codeforces.com/contest/1832/problem/E)

比 D 水好多。

**声明：下文统一使用 $C_n^m$ 表示组合数。**

### 题意

- 给出长度为 $n$ 的数列 $a_1,a_2,\ldots,a_n$，求序列

$$b_i=\sum\limits_{j=1}^iC_{i-j+1}^k\cdot a_j\ (1\le i\le n)$$

- $1\le n\le10^7,1\le k\le5$，输入输出经过处理，模数 $998244353$。

### 题解

第一眼看上去，这不是 FFT 板子吗？！

然后看见 $n\le10^7$。如果常数小也许能过。

但是他显然不是让你去写 FFT 的。

我们令 $b_{K,i}$ 为 $k=K$ 时的 $b_i$。 

注意到 $C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$，设 $k>1$，可得

$$\begin{aligned}b_{k,i}&=\sum\limits_{j=1}^iC_{i-j+1}^k\cdot a_j\\&=\sum\limits_{j=1}^iC_{i-j}^k\cdot a_j+\sum\limits_{j=1}^iC_{i-j}^{k-1}\cdot a_j\\&=\sum\limits_{j=1}^{i-1}C_{(i-1)-j+1}^k\cdot a_j+C_0^k\cdot a_i+\sum\limits_{j=1}^{i-1}C_{(i-1)-j+1}^{k-1}\cdot a_j+C_0^{k-1}\cdot a_i\\&=b_{k-1,i-1}+b_{k,i-1}\end{aligned}$$

然后就可以在 $\Theta(n)$ 的时间内由 $b_{K-1}$ 得到 $b_K$。

所以我们就可以在 $\Theta(nk)$ 内解决本题。

还需要注意一些细节，比如 $C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$ 的边界情况。

### Code

下面是赛时的（部分）代码。

```cpp
const int N=10000005;
int n,a1,X,Y,M,k;
ll a[N];
void gen()
{
	a[1]=a1;
	for(int i=2;i<=n;i++)
		a[i]=(1ll*a[i-1]*X+Y)%M;
}
ll ans;
void Solve()
{
	cin>>n>>a1>>X>>Y>>M>>k;
	gen();
	for(int i=0;i<=k;i++)
	{
		for(int j=2;j<=n;j++)
			(a[j]+=a[j-1])%=MOD;
		if(i>1)for(int j=n;j;j--)a[j]=a[j-1];
	}
	for(int i=1;i<=n;i++)
		ans^=(a[i]*i);
	cout<<ans;
}
```

---

## 作者：Unnamed114514 (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/378n0t88.png)

这么简单的题都要吃罚时。![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

使用传统艺能：找规律！

发现 $1\le k\le 5$，所以可以直接把 $k\in [1,5]$ 的情况枚举出来，由于 $a_2$ 相对于 $a_1$ 的系数只是向下移动了 $1$，所以说只需要考虑 $a_1$ 的变化。

$k=1:\{1,2,3,\cdots\}$

对此进行差量分析，发现它的差就是 $1$，所以我们打个前缀和即可。

$k=2:\{0,1,3,6,\cdots\}$

同样的，对此进行差量分析，得到差的序列为 $\{1,2,3,\cdots\}$，可以发现其实就是 $k=1$ 的序列。

$k=3:{0,0,1,4,10,\cdots}$

同样地，此时得到的序列是 $\{0,1,3,6,\cdots\}$，可以发现此时正好是 $k=2$ 的序列。

~~此时可以大胆地猜结论~~以此类推，$dp_{i,j}$ 表示 $k=i$ 时第 $j$ 为的答案，那么 $dp_{i,j}=dp_{i-1,j-1},+dp_{i,j-1}(dp_{0,i}=\sum\limits_{j=1}^n a_j)$。

时间复杂度 $O(nk)$。

[code](https://codeforces.com/contest/1832/submission/205607655)

---

