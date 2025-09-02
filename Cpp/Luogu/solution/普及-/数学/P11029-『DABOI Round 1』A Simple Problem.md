# 『DABOI Round 1』A Simple Problem

## 题目背景

> 红题令人红温。

## 题目描述

求 $\prod \limits_{i=1}^{n} \prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k$ 对 $998244353$ 取模后的值。

## 说明/提示

**【数据范围】**

- 对于 $20\%$ 的数据，$n\leq5\times10^2$；
- 对于 $50\%$ 的数据，$n\leq5\times10^3$;
- 对于 $100\%$ 的数据，$1\leq n\leq1.8\times10^6$。

## 样例 #1

### 输入

```
3```

### 输出

```
1728```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/P11029)

### 思路

考虑使用**前缀积**与**快速幂**。

不难发现，第 $3$ 层循环中的 $k^k$ 的值永远不变。可以从第 $3$ 向第 $1$ 层循环用前缀积初始化。对于 $k^k$ 的计算，考虑使用快速幂。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e6+10,MOD=998244353;
long long f1[N],f2[N],f3[N];
long long q_pow(long long a,long long b){
	long long ans=1,p=a;
	while(b){
		if(b%2==1)
			ans=ans*p%MOD;
		b/=2;
		p=p*p%MOD;
	}
	return ans;
}
int main(){
	int n=read();
	long long res=1;
	for(int i=1;i<=n;++i)
		f1[i]=q_pow(i,i);
	f2[1]=f1[1];
	for(int i=2;i<=n;++i)
		f2[i]=f2[i-1]*f1[i]%MOD;
	f3[1]=f2[1];
	for(int i=2;i<=n;++i)
		f3[i]=f3[i-1]*f2[i]%MOD;
	for(int i=1;i<=n;++i)
		res=(res*f3[i])%MOD;
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：cjh20090318 (赞：6)

验题人题解。

出题人标程一开始写错了，所以我重写了 std 并造了数据。

## 题意

$$
\left( \prod\limits^n_i\prod\limits^i_j\prod\limits^j_k k^k \right) \bmod 998244353
$$

## 分析

观察到 $k$ 是最不好求的，且答案和 $i,j$ 没有关系。

现在的问题是求 $k^k$ 相乘了多少次，也就是求 $k \le i \le j \le n$ 的 $(i,j)$ 对数，问题也就转化成了 $n-k+1$ 个数中选两个数（可选两个相同的数）的方案数，即：

$$
\begin{aligned}
\dbinom{n-k+1}{2} + (n-k+1) 
& = \dfrac{(n-k+1)(n-k)} 2  + (n-k+1)\\
& = \dfrac{(n-k+1)(n-k+2)} 2
\end{aligned}
$$
因此我们所求答案：
$$
\prod\limits^n_i\prod\limits^i_j\prod\limits^j_k k^k = \prod\limits^n_k (k^k)^{\frac{(n-k+1)(n-k+2)} 2} = \prod\limits^n_k k^{\frac 1 2 k(n-k+1)(n-k+2)}
$$
做到这里其实可以直接求了，但是进一步由费马小定理 $a^{p-1} \equiv 1 \pmod p$ 推导可以得到：
$$
\left( \prod\limits^n_k k^{\frac 1 2 k(n-k+1)(n-k+2)} \right) \bmod 998244353 = \left( \prod\limits^n_k k^{\frac 1 2 k(n-k+1)(n-k+2) \bmod 998244352} \right) \bmod 998244353
$$
然后就可以愉快的枚举 $k$ 再快速幂了，时间复杂度 $O(n \log n)$，有点小卡常。

最大点在 C++14 O2 下跑了 $\text{236ms}$，但是有些选手被卡常了，建议自行优化常数。

```cpp
//the code is from chenjh
#include<cstdio>
using namespace std;
typedef long long LL;
const int mod=998244353;
int qpow(int a,int b){
	int ret=1;
	for(;b;b>>=1,a=(LL)a*a%mod)if(b&1)ret=(LL)ret*a%mod;
	return ret%mod;
}
int n;
int main(){
	scanf("%d",&n);
	int ans=1;
	for(int i=1;i<=n;i++) ans=(LL)ans*qpow(i,(LL)i*((LL)(n-i+1)*(n-i+2)/2%(mod-1))%(mod-1))%mod;
	printf("%d\n",ans);
	return 0;
}
```

Update on 2024/9/9：

用 PyPy 3 写了个解法，可以通过，请不要再说卡常了。

```python
n=int(input())
s=1
for i in range(1,n+1):
    s=s*pow(i,i*(n-i+1)*(n-i+2)//2%998244352,998244353)%998244353
print(s)
```

---

## 作者：dongzirui0817 (赞：3)

### 题目大意
求 $\prod \limits_{i=1}^{n} \prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k$ 对 $998244353$ 取模后的值。

### 思路
显然可以暴力 $O(n^4)$ ，并获得 $20 \;pts$ 的部分分。

可以得出， $k^k$ 会被重复计算多次，可以预处理 $k^k$ 的结果，到时候带进去就行。\
时间复杂度优化至 $O(n^3)$ ，显然会 TLE。

显然可以利用这种做法来优化。

同理，$\prod \limits_{k=1}^{j} k^k$ 也会被重复计算多次，也可以预处理。\
时间复杂度优化至 $O(n^2)$ ，依然要 TLE。

现在来说正解，设 $s_i = \prod \limits_{j=1}^{i} j^j$ ，$c_i = \prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k$ ，则 $s_i = s_{i - 1} \times i ^ i$ ，$c_i = \prod\limits_{j=1}^{i} s_i = c_{i - 1} \times s_i$ ，$答案=\prod\limits_{j=1}^{i} c_i$；算出了 $s_i$ ，就可以线性算出 $c_i$ ；算出了 $c_i$ ，就可以线性算出答案。
(其中设 $s_0 = c_0 = 1$)

但算 $s_i$ 时要 $O(n^2)$ ，开个快速幂即可（不会？出门右转 [P1226](https://www.luogu.com.cn/problem/P1226)）

时间复杂度 $O(n \log n)$ ，空间复杂度 $O(n)$

```
#include <bits/stdc++.h>
using namespace std;

const int p = 998244353;

long long Pow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		a = a * a % p; 
		b >>= 1;
	}
	return res;
}

int n;
int s[2000010] = {1}, c[2000010] = {1};
int ans = 1;

int main() {
	scanf("%d", &n);
	for (int i = 1 ; i <= n ; i++)
		s[i] = s[i - 1] * Pow(i, i) % p;
	for (int i = 1 ; i <= n ; i++)
  		c[i] = 1LL * c[i - 1] * s[i] % p; //记得加 1LL
	for (int i = 1 ; i <= n ; i++)
		ans = 1LL * ans * c[i] % p;
	printf("%d\n", ans);
	return 0;
} 
```

什么，空间想要 $O(1)$ ？\
其实也很好想。显然， $s_i$ 需要 $s_{i - 1}$ 算出 ，$c_i$ 需要 $c_{i - 1} ,\; s_i$ 算出。可以在算出 $s_i$ 时马上算出 $c_i$ 。\
然后，就没有然后了。

空间复杂度优化至 $O(1)$

```
#include <bits/stdc++.h>
using namespace std;

const int p = 998244353;

long long Pow(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		a = a * a % p; 
		b >>= 1;
	}
	return res;
}

int n;
int s = 1, c = 1;
int ans = 1;

int main() {
	scanf("%d", &n);
	for (int i = 1 ; i <= n ; i++)
		s = s * Pow(i, i) % p,
		c = 1LL * c * s % p,
		ans = 1LL * ans * c % p;
	printf("%d\n", ans);
	return 0;
} 
```

---

## 作者：卷王 (赞：3)

做法：前缀积

### $O(n^3)$

首先考虑暴力模拟，代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 998244353;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 1;
int sum[2000007];
inline int power(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)
			for(int k=1;k<=j;k++)
			ans=ans*power(k,k)%mod;
	}
	cout<<ans;
	return 0;
}
```

### $O(n^2)$

我们发现 $k$ 这个地方是可以用前缀积预处理的，于是：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 998244353;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 1;
int sum[2000007];
inline int power(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main() {
	cin>>n;sum[0]=1;
	for(int i=1;i<=n;i++)sum[i]=(sum[i-1]*power(i,i))%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)
			ans=ans*sum[j]%mod;
	}
	cout<<ans;
	return 0;
}
```

### $O(n)$

我们发现 $j$ 这一维依然可以用前缀积优化，对 $sum_i$ 做前缀积，所以 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 998244353;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 1;
int sum[2000007];
int sum2[2000007];
inline int power(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main() {
	cin>>n;sum[0]=1;sum2[0]=1;
	for(int i=1;i<=n;i++)sum[i]=(sum[i-1]*power(i,i))%mod;
	for(int i=1;i<=n;i++)sum2[i]=sum2[i-1]*sum[i]%mod;
	for(int i=1;i<=n;i++)ans=ans*sum2[i]%mod;
	cout<<ans;
	return 0;
}
```

总体还是非常简单的。

---

## 作者：_Deer_Peach_ (赞：2)

题意已经很直接了就不赘述。

先介绍一下 $\prod$ 怎么算。$\begin{aligned} \prod _ {i=1} ^ {n} i = 1 \times 2 \times 3 \cdots \times i\end{aligned}$。

思路：

先按照题目给出的公式直接暴力一遍可得 $20$ 分：

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=1;const int Mod=998244353;
int Pow(int x,int y){
	int res=1;while(y){
		if(y&1)(res*=x)%=Mod;
		y>>=1;(x*=x)%=Mod;
	}return res%Mod;
}signed main(){
	cin>>n;for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<=j;k++){
				(ans*=Pow(k,k))%=Mod;
			}
		}
	}cout<<ans%Mod;return 0;
}
```
把式子展开，得到：
$\begin{aligned} \prod _ {i=1} ^ {n} \prod _ {j=1} ^ {i} \prod _ {k=1} ^ {j} k^k &= \prod _ {i=1} ^ {n} \prod _ {j=1} ^ {i} (1^1 \times 2^2 \times \cdots \times j^j)\end{aligned}$。

设 $las=1^1 \times 2^2 \times \cdots \times j^j$，答案 $ans = (1^1) \times (1^1 \times 2^2) \times \cdots \times(1^1 \times 2^2 \times \cdots \times j^j)$，那么 $ans$ 每次都乘以一个 $las$，而 $las$ 随着 $j$ 加 $1$ 而乘以 $(j+1)^{j+1}$。

那么就可以将三重循环优化成两重循环：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=1;const int Mod=998244353;
int Pow(int x,int y){
	int res=1;while(y){
		if(y&1)(res*=x)%=Mod;
		y>>=1;(x*=x)%=Mod;
	}return res%Mod;
}signed main(){
	cin>>n;int las=1;for(int i=1;i<=n;i++){
    	int cnt=1;for(int i=2;i<=x;i++)(cnt*=Pow(i,i))%=Mod;
		(las*=cnt)%=Mod;
		(ans*=las)%=Mod;
	}cout<<ans%Mod;return 0;
}
```
因为 $ans$ 每次都乘以一个 $las$，而 $las$ 随着 $j$ 加 $1$ 而乘以 $(j+1)^{j+1}$。所以设 $la=(j+1)^{j+1}$，每一次 $las$ 更新只需要乘上 $la$ 即可。

那么这样可以将两重循环优化到一重循环：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=1;const int Mod=998244353;
int Pow(int x,int y){
	int res=1;while(y){
		if(y&1)(res*=x)%=Mod;
		y>>=1;(x*=x)%=Mod;
	}return res%Mod;
}int p(int x){int res=1;for(int i=2;i<=x;i++)(res*=Pow(i,i))%=Mod;return res%Mod;}
signed main(){
	cin>>n;int las=1,la=1;for(int i=1;i<=n;i++){
		(la*=Pow(i,i))%=Mod;
		(las*=la)%=Mod;
		(ans*=las)%=Mod;
	}cout<<ans%Mod;return 0;
}
```

---

## 作者：ZinfI_Sh (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11029)

在赛场上，我们为了求快，使用一种“找规律不证”的方法。

观察样例 $n=3$，展开式子：


$\begin{aligned}
& \prod\limits_{i=1}^{3}\prod\limits_{j=1}^{i}\prod\limits_{k=1}^{j}k^k&\\
= &(1^1)\times ((1^1)\times (1^1\times 2^2))\times ((1^1)\times (1^1\times 2^2)\times (1^1\times 2^2\times 3^3))&\\
= &1^1\times 1^1\times 1^1\times 1^1\times 1^1\times 1^1\times 2^2\times 2^2\times 2^2\times 3^3&\\
= &(1^1)^6\times (2^2)^3\times (3^3)^1&\\
\end{aligned}$

记 $(1^1)^6$，$(2^2)^3$ 和 $(3^3)^1$ 的指数 $6$，$3$，$1$ 分别为 $e_1$，$e_2$，$e_3$，
故：

$\begin{aligned}
&(1^1)^6\times (2^2)^3\times (3^3)^1&\\
=&(1^1)^{e_1}\times (2^2)^{e_2}\times (3^3)^{e_3}\\
\end{aligned}$

容易发现：

$e_i=\sum\limits_{i=1}^{n-i+1}i$

故我们以 $O(n)$ 的复杂度倒序枚举 $i$，就可以用 $O(n\log n)$ 的时间复杂度求解。其中 $O(\log n)$ 是快速幂的复杂度。

# AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define lowbit(x) (x & -x)
using namespace std;
const int DM[8][2] = {0, 1, 0, -1, 1, 0, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1};
const int HASHMOD = 9223372036854775783;
const int HASHBASE = 131;
const int HASHITEM = 999997;
const int MOD = 998244353;
int qpow(int x, int k)
{
    if (k == 1)
    {
        return x;
    }
    int tmp = qpow(x, k >> 1);
    tmp = (tmp * tmp) % MOD;
    if (k & 1)
    {
        return (tmp * x) % MOD;
    }
    return tmp;
}
signed main()
{
    int n;
    cin >> n;
    int res = 1;
    for (int i = n, mi = 1, pl = 2; i >= 1; i--)
    {
        // cout << i << ' ' << mi << '\n';
        res = (res * qpow(qpow(i, i), mi)) % MOD;
        mi += pl;
        pl++;
    }
    cout << res;
    return 0;
}
```

---

## 作者：crzcqh (赞：1)

### 思路

考虑枚举所有 $k$，求出每一个 $k$ 的贡献。

先思考一个问题：$k$ 在什么情况下会产生贡献？显然会在每一个二元组 $(i,j)$ 满足 $i\in[k,n],j\in[k,i]$ 产生 $k^k$ 的贡献。现在问题变成求有多少个二元组 $(i,j)$ 满足 $i\in[k,n],j\in[k,i]$。

对于 $i=k+l$，有 $l+1$ 个 $j$ 满足 $j\in[k,i]$，而 $l\in[0,n-k]$，所以总共有 $(\sum^{n-k}_{l=0}l+1)$ 组二元组 $(i,j)$，$k$ 的贡献为 $(k^k)^{(\sum^{n-k}_{l=0}l+1)}=(k^k)^{\frac{1}{2}(1+n-k)\times n}$ 的贡献，最后的答案即是：
$$(\prod\limits_{k=1}^{n}(k^k)^{\frac{1}{2}(1+n-k)\times n})\bmod 998244353$$

中间的式子可以使用快速幂求，最终时间复杂度 $O(n\log n)$。

---

## 作者：Indestructible (赞：1)

考虑把三个 $\prod$ 拆成一个，再用快速幂求解。

$$\begin{aligned}
\prod \limits_{i=1}^{n} \prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k &= \prod \limits_{i=1}^{n} \prod\limits_{j=1}^{i}1^12^2\dots j^j \\
&=\prod \limits_{i=1}^{n} 1^1\times1^12^2\times\dots\times(1^12^2\dots i^i) \\
&=\prod \limits_{i=1}^{n} 1^{1\times i}\times2^{2\times(i-1)}\times\dots\times i^1 \\
&=1^{1\times(1+2+\dots+n)}\times2^{2\times[1+2+\dots+(n-1)]}\times\dots\times n^1\\
&=\prod \limits_{i=1}^{n} i^{\frac{(n-i+1)(n-i+2)i}{2}}
\end{aligned}$$

下面是代码。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
inline int fpow(int a,int b)
{
	int ans = 1ll;
	while (b)
	{
		if (b & 1ll) ans = ans * a % mod;
		a = a * a % mod, b >>= 1ll;
	}
	return ans;
}
int n, ans = 1;
signed main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++)
		ans = ans * fpow(i, (n - i + 1) * (n - i + 2) * i >> 1) % mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：tder (赞：1)

You can view the [English version](https://www.luogu.com/article/0whanyvc/) of this solution.

锅锅锅，摆摆摆，喵喵喵。

考虑每个 $k^k$ 的贡献。

当钦定了 $i$ 时，每个 $j\ge k$ 都有 $1$ 次贡献，故共 $i-k+1$ 次贡献。因此，其总贡献次数为：

$$
\begin{aligned}
\text{cnt}_k&=\sum_{i=k}^n(i-k+1) \\
&=\sum_{i=k}^ni-(n-k+1)\cdot(k-1) \\
&=\frac{(k+n)(n-k+1)}2-(n-k+1)\cdot(k-1)
\end{aligned}
$$

对每个 $(k^k)^{\text{cnt}_k}$  累乘即可。

时间复杂度 $\mathcal{O}(n\log n)$。

---

## 作者：wo_hen_la (赞：0)

这是我赛时的解法。

首先我们发现 $n\le1.8 \times 10^6$，可以 $O(n)$ 做，那么枚举每个 $i$，又发现对于每个 $i$，$\prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k$ 就是这个图里所有数相乘起来：

![tu](https://cdn.luogu.com.cn/upload/image_hosting/cyuzpdeo.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

现在就好做了，先预处理每个 $x^x$，再对它做前缀积得到每个 $\prod \limits_{k=1}^{j} k^k$，然后对前缀积再做前缀积，得到 $\prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k$，然后就做完了这题。

### Code


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int P=998244353,N=2e6+5; 
int n;
int qpow(ll a,int b)
{
	ll ans=1;
	while(b){
		if(b&1) ans=(ans*a)%P;
		a=(a*a)%P;
		b>>=1;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;
	ll sum=1,summ=1,ans=1;
	for(int i=1;i<=n;i++){
		sum=(sum*qpow(i,i))%P;
		summ=(summ*sum)%P;
		ans=(ans*summ)%P;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lihl (赞：0)

### 20 分
预处理 $k^k\bmod998244353$，其中 $k\in\left[0,n\right]\cap\mathbb N$。

时间复杂度 $O(n^3+n\log n)$，优于暴力 $O(n^4 \log n)$。
### 100 分
递推。

$k^k$ 一定被累乘 $\sum_{i=1}^{n-k+1}$ 次，因为存在 $k-1$ 个小于 $k$ 的正整数，即 $k^k$ 会被累乘 $n-k+1$ 次，于是

表示为 
$$
\begin{aligned}
\prod \limits_{i=1}^{n} \prod\limits_{j=1}^{i} \prod \limits_{k=1}^{j} k^k &=\prod_{k=1}^{n}k^{k\cdot \sum_{i=1}^{n-k+1}} \\
&=\prod_{k=1}^{n}k^{k\frac{(n-k+1)(n-k+2)}{2}}

\end{aligned}$$

快速幂计算即可，时间复杂度 $O(n\log n)$。

**请写对快速幂**。

---

## 作者：Scean_Tong (赞：0)

### P11029 『DABOI Round 1』A Simple Problem

#### 做法

先看第一档部分分，考虑暴力枚举 $i,j,k$ 的 $n^3$ 做法，实现非常简单，代码如下。

```cpp
void solve(){
	cin>>n;
	int ans=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<=j;k++){
				ans=ans*qpow(k,k)%mod;
			}
		}
	}
	cout<<ans<<'\n';
}
```

考虑优化。

观察到这个式子的答案只和 $k$ 有关，所以 $i,j$ 是没用的，所以只需要统计每个 $k$ 出现的次数就可以了，那么考虑在上述暴力代码统计每个 $k$ 出现的次数。

你会发现。

当 $n$ 为 $3$ 时，$2$ 出现了 $3$ 次，$3$ 出现了 $1$ 次。

当 $n$ 为 $4$ 时，$2$ 出现了 $6$ 次，$3$ 出现了 $3$ 次，$4$ 出现了 $1$ 次。

当 $n$ 为 $5$ 时，$2$ 出现了 $10$ 次，$3$ 出现了 $6$ 次，$4$ 出现了 $3$ 次，$5$ 出现了 $1$ 次。


对于每个 $k$，求出 $k^k$ 被乘了几次，假设乘了 $num_k$ 次，用快速幂求 $k^{k \times num_k}$ 即可。

上代码。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
int n;
const int mod=998244353;
int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=ret*x%mod;
		x=x*x%mod;
		y>>=1;
	}	
	return ret;
}
const int maxn=2e6+7;
int num[maxn];
void solve(){
	cin>>n;
	int ans=1;
	for(int i=1;i<=n;i++){
		num[i]=num[i-1]+i;
	}
	int k=2;
	for(int i=n-1;i>=1;i--){
		ans=ans*qpow(qpow(k,k),num[i])%mod;
		k++;
	}
	cout<<ans<<'\n';
}
int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：jjy2023 (赞：0)

# P11029 『DABOI Round 1』A Simple Problem
## Solution：
根据题意计算即可。
## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,result=1;
const int MOD=998244353;
inline int power(int base,int zhi,int mod) 
{
    int res=1;
    while(zhi>0) 
	{
        if(zhi%2==1) res=(res*base)%mod;
        base=(base*base)%mod;
        zhi/=2;
    }
    return res;
}
signed main() 
{
    cin>>n;
    for(register int k=1;k<=n;++k)
	{
        long long count=(k*(n-k+1)*(n-k+2))/2;
        result=(result*power(k,count,MOD))%MOD;
    }
    cout<<result%MOD<<endl;
    return 0;
}
```

---

