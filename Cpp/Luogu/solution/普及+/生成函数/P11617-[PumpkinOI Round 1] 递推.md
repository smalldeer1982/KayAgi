# [PumpkinOI Round 1] 递推

## 题目背景

>一个简单的问题，什么是递推？

## 题目描述

定义一个数列 $\{a_0 \dots a_{n - 1} \}$ 的递推式为满足下式的序列 $\{r_0\dots r_m\}$：

$$\sum_{j = 0} ^ m r_j a_{i - j} = 0, \forall i \ge m$$

$m$ 称为该递推式的阶数。特别地，$r_0\neq 0$。

给你一个无限长的数列 $\{a_i\}$ 的前 $n$ 项以及数列 $\{a_i\}$ 的一个阶数为 $n$ 的递推式 $\{b_i\}$。

要求求出数列 $\{a_i\}$ 的所有项之和。答案对 $998244353$ 取模。

可以证明，对于任意一个模 $998244353$ 意义下输入，都存在实数意义下的一个对应数列的答案是收敛的。

## 说明/提示

**样例解释 #1**

$499122176\equiv -\frac12\pmod {998244353}$。

$\forall i\ge n,a_i-\frac12\times a_{i-1}=0$ 即 $a_i=\frac12\times a_{i-1}$，即数列 $\{a_i\}$ 是等比数列 $1,\frac12,\frac14,\dots$。其和收敛于 $2$。

**样例解释 #2**

$199648870\equiv -0.6\pmod {998244353},99824435\equiv -0.3\pmod {998244353}$。

$\forall i\ge n,a_i-0.6\times a_{i-1}-0.3\times a_{i-2}=0$ 即 $a_i=0.6\times a_{i-1}+0.3\times a_{i-2}$。经计算，其和收敛于 $14$。

**本题使用子任务捆绑/依赖**

对于所有子任务，$1\le n\le5\times 10^3$， $0\le a_i,b_i< 998244353$。特别地，$b_0\neq 0$。

| 子任务编号 | 分值 | $n\le$ | 依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $30$ | $1$ | 无 |
| $2$ | $30$ | $2$ | $1$ |
| $3$ | $40$ | $5\times 10^3$ | $1,2$ |


## 样例 #1

### 输入

```
1
1
1 499122176
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 1
1 199648870 99824435
```

### 输出

```
14```

## 样例 #3

### 输入

```
1
1
1 499122177
```

### 输出

```
665496236
```

# 题解

## 作者：chenly8128 (赞：8)

简单题，稍微推推就好了。

### 题解
主要利用 $\sum_{j = 0} ^ n r_j a_{i - j} = 0, \forall i \ge n$。
将这个式子的所有 $i \ge n$ 形式累加起来。设收敛数列总和为 $ans$。

|$i$\\$j$|$0$|$1$|$\dots$|$n$| 总和 |
|:-:|:-:|:-:|:-:|:-:|:-:|
|$n$|$r_0 \times a_n$|$r_1 \times a_{n-1}$|$ \dots $|$r_n \times a_0$| 0 |
|$n+1$|$r_0 \times a_{n+1}$|$r_1 \times a_n$|$\dots$|$r_n \times a_1$| 0 |
|$n+2$|$r_0 \times a_{n+2}$|$r_1 \times a_{n+1}$|$\dots$|$r_n \times a_2$| 0 |
|$ \dots $|$ \dots $|$ \dots $|$ \dots $|$ \dots $| 0 |
| 总和 |$r_0 \times (ans-\sum_{i=0}^{n-1} a_i)$|$r_1 \times (ans-\sum_{i=0}^{n-2} a_i)$|$ \dots $|$r_n \times ans$| **0** |

最关键的是最后一行，最后一行 

$$r_0 \times (ans-\sum_{i=0}^{n-1} a_i) + r_1 \times (ans-\sum_{i=0}^{n-2} a_i) +  \dots + r_n \times (ans-0) = 0$$

整理一下：

$$ans \times \sum_{i=0}^n r_i = r_0 \times \sum_{i=0}^{n-1}a_i + r_1 \times \sum_{i=0}^{n-2} a_i + \dots + r_n \times 0$$

因此：

$$ans = \dfrac{r_0 \times \sum_{i=0}^{n-1}a_i + r_1 \times \sum_{i=0}^{n-2} a_i + \dots + r_n \times 0}{\sum_{i=0}^n r_i} $$

上下面都算出来，最后乘法逆元算一下乘起来就行了。

### 代码

```cpp

// Author: chenly8128
// Created: 2025-01-25 14:07:20

#include <bits/stdc++.h>
#define int long long
const int mod = 998244353;
const int MAXN = 5e3+10;
using namespace std;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
int qpow (int a,int k) {
	int ans = 1;
	while (k) {
		if (k&1) ans = ans * a % mod;
		a = a * a % mod;
		k >>= 1;
	}
	return ans;
}
int n,a[MAXN],r[MAXN];
signed main (void) {
	n = read();
	for (int i = 0;i < n;i++) a[i] = read();
	int sum = 0,res = 0,sum2 = 0;
	for (int i = 0;i <= n;i++)
		r[i] = read();
	for (int i = n;i >= 0;i--) {
		sum2 = (sum2 + r[i]) % mod;
		sum = (sum + res * r[i]) % mod;
		res = (res + a[n-i]) % mod;
	}
	printf ("%lld\n",sum * qpow(sum2,mod-2) % mod);
	return 0;
}
```

---

## 作者：pyiming (赞：5)

upd：修复了代码（给成了旧版题目代码）

考虑 $n=1$ 时的做法。此时，$\forall i\ge 1,a_i\times b_0+a_{i-1}\times b_1=0$ 即 $a_i=-\frac{b_1}{b_0}\times a_{i-1}$。这是一个等比数列，令 $k=-\frac{b_1}{b_0}$，则 $a_i=k\times a_{i-1}(i\ge1)$。

设答案为 $S=\sum_{i=0}^\infty a_i$，则 $kS=\sum_{i=1}^\infty a_i$，那么 $S-kS=a_0$，$S=\frac{a_0}{1-k}$。

考虑扩展到 $n=2$。设答案为 $S=\sum_{i=0}^\infty a_i$，则 

$$S\times b_0=b_0\sum_{i=0}^\infty a_i$$
$$S\times b_1=b_1\sum_{i=0}^\infty a_i$$
$$S\times b_2=b_2\sum_{i=0}^\infty a_i$$

依题意得，$\sum_{j=0}^2 a_{i-j}\times b_j=0$。所以将上三式相加的结果为 $S\times(b_0+b_1+b_2)=b_0\times a_0+b_0\times a_1+b_1\times a_0$，所以答案为 $S=\frac{b_0\times a_0+b_0\times a_1+b_1\times a_0}{b_0+b_1+b_2}$。

同理可以扩展到 $n>2$，答案为 $S=\frac{\sum_{i=0}^{n-1}\sum_{j=0}^{i+j<n}a_i\times b_j}{\sum_{i=0}^nb_i }$。

可以通过前缀和优化将做到时间复杂度 $O(n)$，但不是本题主要考察内容，所以直接做 $O(n^2)$ 也可以通过。

再给出以下内容的证明。

> 可以证明，对于任意一个模意义下输入，都存在实数意义下的一个对应数列的答案是收敛的。

首先，我们将递推关系转化为生成函数的形式。设生成函数为：

$$
a(x) = \sum_{i=0}^\infty a_i x^i
$$

根据递推关系，我们有：

$$
\sum_{j=0}^m r_j x^j a(x) = p(x)
$$

其中，$p(x)$ 是一个多项式。因此，生成函数可以表示为：

$$
a(x) = \frac{p(x)}{g(x)}
$$

其中，$g(x) = r_0 + r_1 x + r_2 x^2 + \dots + r_m x^m$ 是递推系数的生成函数。

生成函数 $a(x)$ 的收敛半径由 $g(x)$ 的零点决定，具体来说，收敛半径是 $g(x)$ 的最小模的零点。

如果 $r > 1$，即 $g(x)$ 的所有零点的模都大于1，那么 $a(x)$ 在 $|x| \le r$ 内解析，包括 $x=1$，所以 $\sum_{i=0}^\infty a_i$ 收敛。

反之，如果 $r \le 1$，即 $g(x)$ 至少有一个零点的模小于或等于1，那么 $a(x)$ 在 $x=1$ 处可能发散，即 $\sum_{i=0}^\infty a_i$ 可能发散。

因此，$\sum_{i=0}^\infty a_i$ 收敛当且仅当 $r > 1$。

若我们求出收敛半径在模意义下的值为 $R$，则必然存在一个实数意义下的 $R$ 满足 $R>1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998'244'353;
struct modint{
    int v;
    modint(int v=0):v(v){}
    modint operator+(modint o){
        int t=v+o.v;
        if(t>=mod){
            t-=mod;
        }
        return t;
    }
    modint operator-(modint o){
        int t=v-o.v;
        if(t<0){
            t+=mod;
        }
        return t;
    }
    modint operator*(modint o){
        return 1ll*v*o.v%mod;
    }
};
modint qpow(modint a,int b){
    modint ans=1;
    while(b){
        if(b&1){
            ans=ans*a;
        }
        a=a*a;
        b>>=1;
    }
    return ans;
}
modint solve(int n,vector<modint> a,vector<modint> b){
    modint ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=n&&i-j>=0;j++){
            ans=ans+b[j]*a[i-j];
        }
    }
    modint temp=0;
    for(int i=0;i<=n;i++){
        temp=temp+b[i];
    }
    return ans*qpow(temp,mod-2);
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<modint> a,b;
    for(int i=0;i<n;i++){
        long double x;
        cin>>x;
        a.push_back(x);
    }
    for(int i=0;i<=n;i++){
        long double x;
        cin>>x;
        b.push_back(x);
    }
    cout<<solve(n,a,b).v<<"\n";
    return 0;
}
```

---

## 作者：complete_binary_tree (赞：2)

验题人题解。

---

让我们设 $\displaystyle \sum_{i=0}^{\infin} a_i = S, \sum_{i=0}^n r_i = R$，那么 $RS = \sum_{i=0}^{\infin} \sum_{j=0}^n a_ir_j$。

根据题目定义，即 $\displaystyle\sum_{j=0}^n r_ja_{i-j}=0$，我们惊喜地发现上式中有很多东西可以消去！

> 如果我们把 $RS$ 乘积看作一个 $n+1$ 行 $\infin$ 列的矩阵元素之和，其中 $i$ 行 $j$ 列表示 $r_ia_j$，那么它长这样：
> 
> $$\begin{bmatrix}a_0r_0& a_1r_0& a_2r_0 &\dots \\ a_0r_1 & a_1r_1 & a_2r_1 & \dots \\ a_0r_2 & a_1r_2 & a_2r_2 & \dots\\ \vdots & \vdots & \vdots & \ddots \\ a_0r_n & a_1r_n & a_2r_n & \dots\end{bmatrix}$$
>
> 此时，$\displaystyle\sum_{j=0}^n r_ja_{i-j}$ 可以看作很多条斜线的组合体，如：
>
> $$\begin{bmatrix}
> a_0r_0 & a_1r_0 & a_2r_0 & \dots & \color{red} a_{n-1}r_0 & \color{blue}a_nr_0 & \dots\\
> \vdots & \vdots & \vdots & \color{red}\vdots & \color{blue}\vdots & \dots\\ 
> a_0r_{n-2}  & a_1r_{n-2} & \color{red}a_2r_{n-2} & \color{blue}a_3r_{n-2} & \dots \\
> a_0r_{n-1} & \color{red}a_1r_{n-1} & \color{blue}a_2r_{n-1} & \dots \\
> \color{red}a_0r_n & \color{blue} a_1r_n & \dots\\
> \end{bmatrix}$$
>
> （$\LaTeX$ 没有反斜省略号，就暂时用竖省略号代替）
>
> 其中红、蓝两色分别代表 $\displaystyle\sum_{j=0}^n r_ja_{n-j},\displaystyle\sum_{j=0}^n r_ja_{n+1-j}$，根据题面，它们的和均为 $0$。
>
> 进一步，我们发现所有反斜列的和都是 $0$。于是我们最后会得到左上角那块黑色的三角形代表 $RS$。

至此，我们把剩下的东西加起来，然后除掉 $R$ 即可。

时间复杂度可以做到线性。 

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5005],b[5005],sumb;
const int mod=998244353;
int ksm(int a,int b){
    long long ans=1,x=a;
    while(b){
        if(b&1)ans=ans*x%mod;
        x=x*x%mod,b>>=1;
    }
    return ans;
}
int main(){
    cin>>n;
    for(int i=0;i<n;++i)cin>>a[i],(a[i]+=a[i-1])%=mod;
    for(int i=0;i<=n;++i)cin>>b[i],(sumb+=b[i])%=mod;
    long long ans=0;
    for(int i=0;i<n;++i)ans+=1ll*a[i]*b[n-i-1]%mod;
    cout<<ans%mod*ksm(sumb,mod-2)%mod<<'\n';
    return 0;
}
```


---

验题记（改模意义前的另一思路）

刚出来这道题时并不是在模意义下，而是实数范围，答案只要求误差不超过 $10^{-9}$ 即可。

由于一些原因，递推式系数在 $10^{18}$ 到 $10^{-9}$ 的范围（为了保证精度）数据只能出到 $n=30$。于是我当时的想法就是矩阵拟合，具体如下：

首先显然有 $\displaystyle a_i = \frac{r_1a_{i-1} + r_2a_{i-2} + \dots + r_na_{i-n}}{r_0}(n \le i)$。（就是把原式拆开移下项再把 $r_0$ 除过去）

这玩意显然可以矩阵倍增来进行递推优化，当矩阵倍增进行了 $1000$ 次，就相当于直接递推 $2^{1000}$ 次，其中极小的误差就可以忽略不计。（然而实际操作时 $\text C++$ 由于精度原因过不去，换成 $\text{Python}$ 才过的）

代码：
```py
from decimal import Decimal as bigfloat
import decimal

n=int(input())
a=list(map(bigfloat,input().split()))
b=list(map(bigfloat,input().split()))

decimal.getcontext().prec = 50

def pre(n,m):
    ret=[]
    for i in range(1,n+1):
        list=[]
        for j in range(1,m+1):
            list.append(bigfloat(0.0))
        ret.append(list)
    return ret

mata=pre(n+3,n+3)

def mul(a,b):
    c=pre(n+3,n+3)
    #print(a)
    for i in range(1,n+2):
        for j in range(1,n+2):
            for k in range(1,n+2):
                c[i][j]+=a[i][k]*b[k][j]
    return c

for i in range(1,n+1):
    mata[i][i-1]=bigfloat(1.0)
    mata[i][n]=-b[n-i+1]/b[0]

mata[n][n+1]=bigfloat(1.0)
mata[n+1][n+1]=bigfloat(1.0)

for i in range(15):
    mata=mul(mata,mata)

ans=bigfloat(0.0)
for i in range(1,n+1):
    ans+=mata[i][n+1]*a[i-1]
    if i < n:
        ans+=a[i-1]

print(ans)
```

[提交记录](https://www.luogu.com.cn/record/193804663)

然而由于精度原因，数据不能出的收敛很慢（不然会因为精度误差变成不收敛），于是收敛很快的数据被[暴力](https://www.luogu.com.cn/record/193808168)（摁递推，甚至精度都卡不掉）跑过去了。

于是出题人换了模意义。

于是矩阵似了。

---

## 作者：HasNoName (赞：2)

### 思路
显然，$n=1$ 是可以直接用等比数列做，所以我们开始考虑 $n=2$ 的情况。

考虑将原式写成 $a_i=xa_{i-1}+ya_{i-2}$。

设 $S=\sum_{j=1}^i a_j$。

又注意到：
$$
a_i=xa_{i-1}+ya_{i-2}
$$
$$
a_{i+1}=xa_i+ya_{i-1}
$$
$$
a_{i+2}=xa_{i+1}+ya_i
$$

所以：$S+a_{i+1}+a_{i+2}-a_1-a_2=x(S+a_{i+1}-a_1)+yS$，即 $(x+y-1)S=a_{i+1}+a_{i+2}-xa_{i+1}+xa_1-a_1-a_2$，所以 $S=\frac{a_{i+1}+a_{i+2}-xa_{i+1}+xa_1-a_1-a_2}{x+y-1}$，当 $i$ 趋近于无穷大时，答案为 $S=\frac{xa_1-a_1-a_2}{x+y-1}$。

类似的，当 $n=3$ 时，可以推出，$S=\frac{x(a_1+a_2)+ya_1-a_1-a_2}{x+y+z-1}$。

然后就不难看出规律。设 $a_i=x_1a_{i-1}+x_2a_{i-2}+\dots+x_na_{i-n}$。则答案为 $S=\frac{x_1(a_1+a_2+\dots+a_{n-1})+x_2(a_1+a_2+\dots+a_{n-2})+\dots+x_{n-1}a_1-a_1-a_2-\dots-a_{n-1}}{x_1+x_2+\dots+x_n-1}$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD=998244353;
const int N=5005;
ll a[N],b[N],x[N];
ll mypow(ll a,ll b)
{
	if(b==0)return 1;
	ll mi=mypow(a,b>>1);
	mi=mi*mi%MOD;
	if(b&1)mi=mi*a%MOD;
	return mi;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n,ccc=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ccc=(ccc+a[i])%MOD;
	}
	cin>>b[1];
	ll sum=0,q=0;
	for(int i=2;i<=n+1;i++)
	{
		cin>>b[i];
		x[i-1]=(MOD-b[i])*mypow(b[1],MOD-2)%MOD;
		sum=(sum+x[i-1])%MOD;
	}
	sum=(sum-1+MOD)%MOD;
	for(int i=1;i<n;i++)
	{
		ll s=0;
		for(int j=1;j<=n-i;j++)
		{
			s=(s+a[j])%MOD;
		}
		q=(q+s*x[i])%MOD;
	}
	q=(q-ccc+2*MOD)%MOD;
	cout<<q*mypow(sum,MOD-2)%MOD<<'\n';
	return 0;
}
```

---

## 作者：Aaronwrq (赞：2)

将序列 $a$ 写成生成函数 $F(x)=\sum\limits_{i=0}^{+\infty} a_ix^i$。

根据题面中给出的递推式 $\sum\limits_{j=0}^n b_j a_{i-j} = 0, \forall i\ge n$，可以得出一个经典构造。以 $n=3$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/vkcncpo5.png)

由递推式，**红色部分每列的和均为 $0$**。因此，**绿色部分的和等于蓝色部分的和**。即：

$$\sum\limits_{i=0}^n b_ix^i\times F(x)=\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-i-1}b_ia_jx^{i+j}$$

将 $\sum\limits_{i=0}^n b_ix^i$ 除到右边即可得到 $F(x)$ 的封闭式。

不过，本题要求 $S=\sum\limits_{i=0}^{+\infty} a_i$。发现 $S=F(1)$，直接带入 $x=1$ 计算即可。

使用前缀和优化右侧求和，时间复杂度 $O(n)$。


```cpp
#include <bits/stdc++.h>
#define MAXN 5010
using namespace std;

int n;
long long a[MAXN], b[MAXN], sl, sr;
const long long mod = 998244353;

long long fastpow(long long a, long long b) {
	long long ans = 1;
	while (b) {
		(b & 1) && (ans = ans * a % mod);
		a = a * a % mod, b >>= 1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i <= n; ++i) cin >> b[i];
	for (int i = 0; i <= n; ++i) sl = (sl + b[i]) % mod;
	for (int i = 1; i < n; ++i) a[i] = (a[i] + a[i - 1]) % mod;
	for (int i = 0; i < n; ++i) sr = (sr + b[i] * a[n - i - 1]) % mod;
	cout << sr * fastpow(sl, mod - 2) % mod << "\n";
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：2)

### Solution

设 $A(z),B(z)$ 分别为数列 $a,b$ 的 OGF，不难有

$$A(z)B(z)-\sum_{i+j<n}a_ib_jz^{i+j}=0$$

解得

$$A(z)=\frac{\sum_{i+j<n}a_ib_jz^{i+j}}{B(z)}$$

取 $z=1$ 即得答案。可以线性。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=5e3+5,mod=998244353;
int n,a[N],b[N];
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<=n;i++)cin>>b[i];
	ll ans1=0,ans2=0;
	for(int i=0;i<n;i++)
		for(int j=0;i+j<n;j++)
			ans1=(ans1+1ll*a[i]*b[j])%mod;
	for(int i=0;i<=n;i++)ans2=(ans2+b[i])%mod;
	cout<<ans1*qpow(ans2,mod-2)%mod<<'\n';
	return 0;
}
```

---

## 作者：K_J_M (赞：2)

## 题目大意

定义一个数列 $\{a_0 \dots a_{n - 1} \}$ 的递推式为满足下式的序列 $\{r_0\dots r_m\}$：

$$\sum_{j = 0} ^ m r_j a_{i - j} = 0, \forall i \ge m$$

$m$ 称为该递推式的阶数。特别地，$r_0\neq 0$。

给你一个无限长的数列 $\{a_i\}$ 的前 $n$ 项以及数列 $\{a_i\}$ 的一个阶数为 $n$ 的递推式 $\{b_i\}$。

要求求出数列 $\{a_i\}$ 的所有项之和。答案对 $998244353$ 取模。
## Solution
既然题目让我们求出 $\{a_i\}$ 的所有项之和，提示我们肯定是有公式的，下面开始推式子。

首先看 $n=1$ 时，我们有 $b_0a_{i}+b_1a_{i-1}=0$，于是 $a_i=-\frac{b_1}{b_0} a_{i-1}$，这是一个等比数列，直接用等比数列求和公式即可，这样有30pts，下面考虑通解。

对于条件，我们有
$$b_0a_{n}+b_1a_{n-1}+ \dots +b_na_0=0$$

也就是
$$a_n=-\frac{\sum_{j=1}^{n}b_ja_{n-j}}{b_0}$$

我们记
$$f_i=\sum_{j=1}^{n}b_ja_{i-j}$$

那么
$$a_i=-\frac{f_i}{b_0}$$

我们写出 $f_n,f_{n+1} \dots$
$$f_n=b_1a_{n-1}+b_2a_{n-2}+\dots b_na_0$$
$$f_{n+1}=b_1a_{n}+b_2a_{n-1}+\dots b_na_1$$
$$f_{n+2}=b_1a_{n+1}+b_2a_{n}+\dots b_na_2$$
$$\dots$$

将上面左边与右边累加即可得到

$$\sum_{i=n}^{+∞}f_{i}=b_1\sum_{j=n-1}^{+∞}a_j + b_2\sum_{j=n-2}^{+∞}a_j + \dots +b_n\sum_{j=0}^{+∞}a_j$$

注意到右边的关于 $a$ 的和式有很多重复的部分，我们将 $\sum_{j=n}^{+∞}a_j$ 记做 $S$。那么右边为
$$b_1(a_{n-1}+S)+b_2(a_{n-2}+a_{n-1}+S)+\dots +b_n(a_0+\dots +b{n-1}+S)$$
我们再记
$$g_i=\sum_{j=0}^{i}a_j$$
那么右边等于
$$b_1(g_{n-1}-g_{n-2}+S)$$
$$+b_2(g_{n-1}-g_{n-3}+S)$$
$$+b_3(g_{n-1}-g_{n-4}+S)$$
$$\dots$$
$$+b_n(g_{n-1}-0+S)$$
展开合并可以得到
$$(g_{n-1}+S)\sum_{j=1}^{n}b_j-\sum_{j=1}^{n}b_jg_{n-1-j}$$
我们记
$$\sum_{j=1}^{n}b_j=C_1$$
$$\sum_{j=1}^{n}b_jg_{n-1-j}=C_2$$
注意这两个都是常数，那么我们的右边就等于
$$(g_{n-1}+S)C_1-C_2$$
由于我们有
$$a_i=-\frac{f_i}{b_0}$$
而我们的左边为
$$\sum_{i=n}^{+∞}f_{i}=-b_0\sum_{i=n}^{+∞}a_i=-b_0(g_{n-1}+S)$$
由于左边等于右边，所以
$$-b_0(g_{n-1}+S)=(g_{n-1}+S)C_1-C_2$$
而我们所要求的答案为
$$Ans=g_{n-1}+S$$
所以
$$-b_0Ans=C_1Ans-C_2$$
$$(C_1+b_0)Ans=C_2$$
$$Ans=\frac{C_2}{C_1+b_0}$$
这样用费马小定理求解逆元就可以了。\
[Ac Code](https://www.luogu.com.cn/paste/or226nxz)

---

## 作者：Null_h (赞：2)

## 前言

只是题面看着吓人而已，技巧还是挺显然的。

下文中所有同余的模数为 $998244353$。

## 题面
给定数列：

$\{a_i\}$ 的前 $n$ 项$ \{a_0 \dots a_{n - 1} \}$ 每一项的值，$\{b_0 \dots b_{n} \}$ 每一项的值。

给定条件：
$$\sum_{j = 0} ^ {n} b_j a_{i - j} \equiv 0, \forall i \ge {n}$$
记为 ① 式。

求：
$$S = \sum_{j = 0} ^ {\infty}a_{i} $$

## 思路

记 $T_n = \sum_{i = 0} ^ {n} b_{i}$，将 ① 式对所有 $i\ge n$ 求和，对所有 $a_i$ 合并同类项得到：

$$\sum_{i = n} ^ {\infty} T_{n} a_{i}+\sum_{i = 0} ^ {n-1} (T_n-T_{n-i-1} )a_{i}\equiv 0$$

（其实就是错位相加）。

也就是：

$$T_nS\equiv\sum_{i = 0} ^ {n-1}T_{n-i-1}a_{i}$$

即可算出 $S$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
const int mod=998244353;
int a[N],b[N];
int po(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		b>>=1;
		a*=a;
		a%=mod;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	n++;
	for(int i=1;i<n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		b[i]+=b[i-1];
		b[i]%=mod;
	}
	int ans=0;
	for(int i=1;i<n;i++){
		ans+=a[i]*b[n-i];
		ans%=mod;
	}
	ans*=po(b[n],mod-2);
	ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：gac497 (赞：1)

# 问题描述

定义一个数列 $\{a_0, a_1, \dots, a_{n-1}\}$ 的递推式为满足下式的序列 $\{r_0, r_1, \dots, r_m\}$：

$$
\sum_{j=0}^m r_j a_{i-j} = 0, \quad \forall i \ge m
$$

其中 $m$ 是递推式的阶数，且 $r_0 \neq 0$。

给定数列的前 $n$ 项和递推式 $\{b_i\}$，求数列的所有项之和 $S$，答案对 $998244353$ 取模。

# 解题思路

## 1. 递推式的性质

递推式描述了数列的后续项与前面项的关系。对于递推式：

$$
\sum_{j=0}^m b_j a_{i-j} = 0, \quad \forall i \ge m
$$

我们可以将其改写为：

$$
a_i = -\frac{1}{b_0} \sum_{j=1}^m b_j a_{i-j}, \quad \forall i \ge m
$$

这表明数列的每一项 $a_i$ 都可以由前 $m$ 项线性表示。

## 2. 数列和的表示

- 设数列的所有项之和为 $S$，即：

$$
S = \sum_{i=0}^\infty a_i
$$

- 根据递推式，我们可以将 $S$ 表示为：

$$
S = \sum_{i=0}^{m-1} a_i + \sum_{i=m}^\infty a_i
$$

- 将递推式代入第二项：

$$
\sum_{i=m}^\infty a_i = \sum_{i=m}^\infty \left( -\frac{1}{b_0} \sum_{j=1}^m b_j a_{i-j} \right)
$$

- 交换求和顺序：

$$
\sum_{i=m}^\infty a_i = -\frac{1}{b_0} \sum_{j=1}^m b_j \sum_{i=m}^\infty a_{i-j}
$$

- 令 $k = i - j$，则：

$$
\sum_{i=m}^\infty a_i = -\frac{1}{b_0} \sum_{j=1}^m b_j \sum_{k=m-j}^\infty a_k
$$

- 注意到 $\sum_{k=m-j}^\infty a_k = S - \sum_{k=0}^{m-j-1} a_k$，因此：

$$
\sum_{i=m}^\infty a_i = -\frac{1}{b_0} \sum_{j=1}^m b_j \left( S - \sum_{k=0}^{m-j-1} a_k \right)
$$

- 将 $\sum_{i=m}^\infty a_i$ 代入 $S$ 的表达式：

$$
S = \sum_{i=0}^{m-1} a_i - \frac{1}{b_0} \sum_{j=1}^m b_j \left( S - \sum_{k=0}^{m-j-1} a_k \right)
$$

- 整理方程：

$$
S = \sum_{i=0}^{m-1} a_i - \frac{1}{b_0} \sum_{j=1}^m b_j S + \frac{1}{b_0} \sum_{j=1}^m b_j \sum_{k=0}^{m-j-1} a_k
$$

- 将 $S$ 的项移到左边：

$$
S + \frac{1}{b_0} \sum_{j=1}^m b_j S = \sum_{i=0}^{m-1} a_i + \frac{1}{b_0} \sum_{j=1}^m b_j \sum_{k=0}^{m-j-1} a_k
$$

- 提取 $S$：

$$
S \left( 1 + \frac{1}{b_0} \sum_{j=1}^m b_j \right) = \sum_{i=0}^{m-1} a_i + \frac{1}{b_0} \sum_{j=1}^m b_j \sum_{k=0}^{m-j-1} a_k
$$

- 设 $sum_b = \sum_{j=0}^m b_j$，则：

$$
S \cdot \frac{sum_b}{b_0} = \sum_{i=0}^{m-1} a_i + \frac{1}{b_0} \sum_{j=1}^m b_j \sum_{k=0}^{m-j-1} a_k
$$

- 最终解得：

$$
S = \frac{b_0 \sum_{i=0}^{m-1} a_i + \sum_{j=1}^m b_j \sum_{k=0}^{m-j-1} a_k}{sum_b}
$$

---

## 3. 代码实现

根据上述推导，代码的实现步骤如下：

### 1. 计算前缀和：
   - 定义 $pre[i] = \sum_{k=0}^{i-1} a_k$，用于快速计算 $\sum_{k=0}^{m-j-1} a_k$。

### 2. 计算递推式系数的和：
   - 计算 $sum_b = \sum_{j=0}^m b_j$。

### 3. 计算分子部分：
   - 计算分子 $mole = b_0 \cdot pre[m] + \sum_{j=1}^m b_j \cdot pre[m-j]$。

### 4. 计算数列和：
   - 使用逆元计算 $S = \frac{mole}{sum_b}$。

# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
const int MAXN=100010;
long long pow_mod(long long a,long long b,long long mod){
    long long res=1;
    while(b){
        if(b&1){
            res=res*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
long long inv(long long x){
    return pow_mod(x,MOD-2,MOD);
}
int main(){
    int n;
    scanf("%d",&n);
    long long a[MAXN],b[MAXN],pre[MAXN]={0};
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=0;i<=n;i++){
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=n;i++){
        pre[i]=(pre[i-1]+a[i-1])%MOD;
    }
    long long sum_b=0;
    for(int i=0;i<=n;i++){
        sum_b=(sum_b+b[i])%MOD;
    }
    long long mole=0;
    for(int j=0;j<=n;j++){
        mole=(mole+b[j]*pre[n-j])%MOD;
    }
    long long S=mole*inv(sum_b)%MOD;
    printf("%lld\n",(S%MOD+MOD)%MOD);
    return 0;
}

---

## 作者：_Kenma_ (赞：0)

## 前言

第一次在 OI 中见到求数列极限的题，有点意思。

但是为什么会过这么多人啊。

## 思路分析

做一点尝试：

$$\sum_{i=m} \sum_{j=0}^{m} r_ja_{i-j}=0$$

然后对于相同的 $a_i$，合并同类项：

$$\sum_{i=m}\sum_{j=0}^{m} r_ja_i + \sum_{i=0}^{m-1}\sum_{j=0}^{i} r_{m-j}a_i=0$$

然后凑出我们的目标：

$$\sum_{i=0} a_i=\sum_{i=0}^{m-1}a_i-\frac{\sum_{i=0}^{m-1}\sum_{j=0}^{i} r_{m-j}a_i}{\sum_{i=0}^{m} r_i}$$

做完了，不难发现可以 $O(m^2)$ 计算和柿。

其实画一个草表也能看出来怎么做，以 $m=3$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/z2xee3pw.png)

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
inline int binpow(int a,int b){
	if(!b) return 1;
	int res=binpow(a,b/2);
	if(b&1) return res*res%mod*a%mod;
	else return res*res%mod;
}
int n,a[30005],r[30005],ans,sumr,suma;
signed main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		ans=(ans+a[i])%mod;
	}
	for(int i=0;i<=n;i++){
		cin>>r[i];
		sumr=(sumr+r[i])%mod; 
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			suma=(suma+r[n-j]*a[i]%mod)%mod;
		}
	}
	ans=(ans-suma*binpow(sumr,mod-2)%mod+mod)%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11617 递推
[题目传送门](https://www.luogu.com.cn/problem/P11617)
## 思路

数列 $\{a_i\}$ 满足递推式：

$\sum_{j=0}^{m} b_j a_{i-j} = 0, \quad \forall i \ge m$。

其中 $b_0 \neq 0$，$m$ 为递推式的阶数。给定的递推式就是一个线性递推关系。

1. **递推关系转化**：
   
   数列 $a$ 和递推系数 $b$ 之间的关系可以看作线性方程组的递推形式。我们知道：

   $\sum_{j=0}^{m} b_j a_{i-j} = 0 \quad \forall i \ge m$。
   
   对于所有 $i \ge m$。

   快速幂用于计算 $sl$ 的模逆元。根据 [Fermat 小定理](https://answer.baidu.com/answer/land?params=oBcw0W6eYHRq5RqEXcjwfIkOMsSd6OuEnK2JiWr2YPb%2B9YEMUPHKFXeQO0VFulQkyz2lkeApG1NX%2FATINaq3WkugUefd%2BYNEB0LkGjDo9xBpRyy8sRuH2qn1kGpMsLUkj6hOskKslCwnOp2v8%2Bh96c62aqE2u%2BXBUSH4m%2BJ6hVTVm3Pizip8vJ52YS66Xe9jEAt5tHHP%2F4MKuF%2B2MQRQqQ%3D%3D&from=dqa&lid=923666420001661d&word=fermat%E5%AE%9A%E7%90%86)，如果 $p$ 是质数，则对模 $p$ 的逆元 $a^{-1}$ 可以通过 $a^{p-2} \bmod p$ 来计算。

   最后，通过 $sr \times sl^{-1} \bmod 998244353$ 计算出数列所有项的和即可。

   **时间/空间复杂度均为** $O(n)$。

 

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define N 5010
namespace fastIO{char *p1,*p2,buf[100000];
	#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
	inline void read(int&n){int x=0,f=1;char ch=nc();while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=nc();}while(ch>=48&&ch<=57){x=(x<<3)+(x<<1)+(ch^48),ch=nc();}n=x*f;}
	inline void read(string&s){char ch=nc();while(ch==' '||ch=='\n'){ch=nc();}while(ch!=' '&&ch!='\n'){s+=ch,ch=nc();}}
	inline void read(char&ch){ch=nc();while(ch==' '||ch=='\n'){ch=nc();}}
	inline void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');return;}
	inline void write(const string&s){for(register int i=0;i<(int)s.size();i++){putchar(s[i]);}}
	inline void write(const char&c){putchar(c);}
}using namespace fastIO;
int n;
int a[N], b[N], sl, sr;
constexpr int mod = 998244353;
signed main() {
    read(n);
    for (int i = 0; i < n; ++i) read(a[i]);
    for (int i = 0; i <= n; ++i) read(b[i]);
    for (int i = 0; i <= n; ++i) sl = (sl + b[i]) % mod;
    for (int i = 1; i < n; ++i) a[i] = (a[i] + a[i - 1]) % mod;
    for (int i = 0; i < n; ++i) sr = (sr + b[i] * a[n - i - 1]) % mod;
    long long sl_inv = 1, base = sl, exp = mod - 2;
    while (exp) {
        if (exp & 1) {
            sl_inv = sl_inv * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    write(sr * sl_inv % mod);
    putchar('\n');
    return 0;
}
```

---

## 作者：sbno333 (赞：0)

看到题，不会？没关系，考虑特殊性质，当 $n=1$ 时，设序列和为 $x$，$a_i=a_{i-1}\times c$，有 $cx+a_1=x$，容易解出来。

现在扩展，发现还是不会，不妨试试把数列变成多项式，多项式 $X=\sum_{i\ge1} a_i x^{i-1}$。

这时候借用上面的，把它乘上一个东西，显然也需要多项式，发现 $r$ 数组骨骼惊奇，和上面类似，把 $r$ 数组变成多项式，$R=\sum_{i\ge0} r_i x^i$，$RX$ 看看会发生什么。

这时候发现，从 $X$ 的 $x^n$ 开始，均为 $0$，因为题面中给到的 $\sum_{j = 0}^n r_j a_{i - j} = 0$。

所以 $XR=Y$，其中 $Y$ 为有限项数的多项式。

移项，$X=\frac{Y}{R}$。

当然，这时候你可能就蒙了，这是不是要多项式科技呀？

需要不了一点。

假设我们已经解出来了 $X$，我的最终是要计算每一项的和，也就是带入 $x=1$。

那我们可不可以解出来之前就这么做呢？

我们可以 $Y,R$ 分别带入 $x=1$，然后算一个除法逆元。

为了减少代码量，$Y$ 不需要算出来，只需要算出每一项的和即可。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353ll
int a[1000009];
int r[1000009];
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=0;i<=n;i++){
		cin>>r[i];
	}
	int ans;
	ans=0;
	for(int i=n;i>=1;i--){
		for(int j=0;j<i;j++){//对于 Y 第 i 项的贡献进行累计
			ans+=a[i-j]*r[j]%mod;
			ans%=mod;
		}
	}
	int pp;
	pp=0;
	for(int i=0;i<=n;i++){
		pp+=r[i];
		pp%=mod;
	}
	if(!pp){
		cout<<a[1]<<endl;
	}else{
		cout<<ans*ksm(pp,mod-2)%mod<<endl;
	}
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	std::ios::sync_with_stdio(0);
	int t;
	//cin>>t;
	t=1;
	while(t--){
		_main();
	}
	return 0;
}
```

发现复杂度瓶颈在于 $Y$ 的计算，此时发现可以对于每一个 $a_i$，考虑贡献了几个，对于 $a_1$，它的贡献为 $\sum_{i=0}^{n-1} r_i$。

对于 $a_i$，它的贡献为 $\sum_{i=0}^{n-i} r_i$。

前缀和优化即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353ll
int a[1000009];
int r[1000009];
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int sum;
	sum=0;
	for(int i=0;i<=n;i++){
		cin>>r[i];
		sum+=r[i];
		sum%=mod;
	}
	sum-=r[n];
	sum+=mod;
	sum%=mod;
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		ans+=a[i]*sum%mod;
		ans%=mod;
		sum-=r[n-i];
		sum+=mod;
		sum%=mod;
	}
	int pp;
	pp=0;
	for(int i=0;i<=n;i++){
		pp+=r[i];
		pp%=mod;
	}
	if(!pp){
		cout<<a[1]<<endl;
	}else{
		cout<<ans*ksm(pp,mod-2)%mod<<endl;
	}
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	std::ios::sync_with_stdio(0);
	int t;
	//cin>>t;
	t=1;
	while(t--){
		_main();
	}
	return 0;
}
```
时间复杂度 $O(n)$。

---

