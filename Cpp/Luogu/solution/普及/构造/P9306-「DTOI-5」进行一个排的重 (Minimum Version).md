# 「DTOI-5」进行一个排的重 (Minimum Version)

## 题目背景

**本题与 Maximum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个 pair $(p_i, q_i)$。

为了让 $a$ 看起来规整一些，他钦定 $p, q$ 分别均为长为 $n$ 的排列。

为了对 $a$ 的规整程度进行量化计算，他给出了一个权值函数 $f(a) = \displaystyle\sum_{i = 1}^n ([p_i > \max_{j = 1}^{i - 1} p_j] + [q_i > \max_{j = 1}^{i - 1} q_j])$。**注意 $i = 1$ 时两个方括号都能取到值，因为我们认为 $\displaystyle\max_{j = 1}^0 p_j = \displaystyle\max_{j = 1}^0 q_j = -\infty$。**

为了让 $a$ 看起来更加规整，他决定分别以某种方式重排 $a$ 得到 $a'$ 使得 $f(a')$ 最小。**注意重排时必须将 $a'_i = (p'_i, q'_i)$ 视为整体。**

他希望你求出 $f(a')_{\min}$ 的值，以及分别有多少个 $a'$ 可以取到 $f(a')_{\min}$。

由于方案数可能很大，你只需要求出结果对 $998244353$ 取模的值。

## 说明/提示

**【数据范围】**

$$
\def\or{\operatorname{or}}
%\def\arrayscretch{1.5}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask}&n\le &\textbf{Points}\cr\hline
\sf1&10&10 \operatorname{pts}\cr\hline
\sf2&500&20 \operatorname{pts}\cr\hline
\sf3&5\times10^3&20 \operatorname{pts}\cr\hline
\sf4&10^5&20 \operatorname{pts}\cr\hline
\sf5&5\times10^5&30 \operatorname{pts}\cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$1 \leq p_i, q_i \leq n$，保证 $p, q$ 均为**排列**。

## 样例 #1

### 输入

```
5
1 5 2 4 3
1 4 2 5 3```

### 输出

```
3 48```

# 题解

## 作者：FFTotoro (赞：7)

本题需要使用**分类讨论**。

这道题我们需要分 $2$ 种情况讨论：

1. 当重排前存在 $i$ 满足 $p_i=q_i=n$：

   重排后要使得答案最小，则必须把满足 $a_i=(p_i,q_i)=(n,n)$ 的元素放在排列的第一项，让后面的数都没有贡献，所以第一问的答案是 $2$；
   
   把 $(n,n)$ 固定在开头后，后面 $n-1$ 个元素可以任意排列，第二问的方案数共有 $(n-1)!$ 种。
   
2. 当重排前不存在 $i$ 满足 $p_i=q_i=n$：

   重排后要使得答案最小，则必须把 $p_i=n$ 的一项或 $q_j=n$ 的一项放在排列的第一项；
   
   不妨设把 $p_i=n$ 放在第一项，$q_j$ 必然会比它前头的数大，只有排列第一项产生 $2$ 的贡献和 $q_j$ 产生的至少为 $1$ 的贡献，第一问答案是 $3$；
   
   如果我们把 $p_i=n$ 放在第一项，那么考虑 $q_j$ 怎么放才能产生正好为 $1$ 的贡献：只要不把大于 $q_i$ 的数放在 $q_j$ 的前面即可（因为如果我们这么做，那么会再产生若干贡献），方案数即为 $\dfrac{(n-1)!}{n-q_i}$。对称地，考虑把 $q_j=n$ 放在第一项的情况，总方案数即为 $\dfrac{(n-1)!}{n-q_i}+\dfrac{(n-1)!}{n-p_j}$。
   
除法可以用乘法逆元实现。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
const int mod=998244353;
int f(int n){
  int s=1;
  for(int i=2;i<=n;i++)
    (s*=i)%=mod;
  return s;
}
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%mod*a%mod;
    a=a%mod*a%mod; b>>=1;
  }
  return r;
}
int inv(int x){return qpow(x,mod-2);}
// 快速幂求逆元
main(){
  ios::sync_with_stdio(false);
  int n,x,y; cin>>n;
  vector<pii> a(n);
  for(auto &i:a)cin>>i.first;
  for(auto &i:a)cin>>i.second;
  for(auto [p,q]:a){
    if(p==n)x=q; if(q==n)y=p;
  } // 找到 q[i] 和 p[j]
  if(x==n)cout<<"2 "<<f(n-1)<<endl; // 第一种情况
  else cout<<"3 "<<f(n-1)*((inv(n-x)+inv(n-y))%mod)%mod<<endl; // 第二种情况
  return 0;
}
```

---

## 作者：DengDuck (赞：4)

# 情况 1
 
存在 $p_i=n,q_i=n$，那么可以将其放置在最前，答案为 $2$，其他随便放置，方案数 $(n-1)!$。

# 情况 2

不存在 $p_i=n,q_i=n$，但是将 $p_i=n$ 或者 $q_i=n$ 放置在第一项，答案为 $3$。

这个很显然，首先第一项肯定会有 $2$ 的贡献，然后我们以 $p_i=n$ 放在第一项为例。

观察到只要保证所有在 $q_i=n$ 之前的 $q_j$ 都满足 $q_j<q_1$ 即可。

这个方案怎么算呢？我们先在 $n-1$ 个位置中，选择 $q_1-1$ 个位置放小的数字，方案数为 $C_{n-1}^{q_1-1}$。

这些小的数字内部随意排序，即为 $(q_1-1)!$。

然后在第一个空位放置 $q_i=n$，其他自然就是大的数字了，方案为 $(n-q_1-1)!$ 个。

总方案数为：

$$
C_{n-1}^{q_1-1}(q_1-1)!(n-q_1-1)!
$$

拆开化简之后，发现方案数为 $\dfrac {(n-1)!}{q_1-1}$。

我们发现 $q_i=n$ 放在第一项也是一个道理，所以最终的方案就为：

$$
\frac {(n-1)!}{q_1-1}+\frac {(n-1)!}{p_1-1}
$$
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=998244353;
struct node
{
	LL p,q;
}a[500005];
LL n,x,y,F=1; 
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)F=F*i%mod;
	for(int i=1;i<=n;i++)cin>>a[i].p;
	for(int i=1;i<=n;i++)cin>>a[i].q;
	for(int i=1;i<=n;i++)
	{
		if(a[i].p==n)x=a[i].q;
		if(a[i].q==n)y=a[i].p;
	}
	if(x==n)
	{
		cout<<2<<' '<<F<<endl;
	}
	else 
	{
		cout<<3<<' '<<F*(ksm(n-x,mod-2)+ksm(n-y,mod-2))%mod<<endl;
	}
}
```

---

## 作者：Leasier (赞：4)

1. 求解 $f(a)_{\min}$

不难发现如下结论：

- 最优情况下，$p'_1$ 和 $q'_1$ 中至少一个为 $n$。

若不是这样，选一个 $p'_i = n$ 或 $q'_i = n$ 并 swap $a'_1, a'_i$ 即可得到一个更优的解。

- $f(a)_{\min} \in \{2, 3\}$。

当存在 $p'_i = q'_i = n$ 时，我们把这对 $(n, n)$ 重排至最前面，此时只有两个首项产生的贡献，则此时权值为 $2$。

否则，我们将 $p'_i = n$ 那对 pair 放到最前面，再将 $q'_i = n$ 那对 pair 放在第二个即可构造出权值为 $3$ 的结果。

不难发现上述两种构造方式均为最优者之一。

假如不这样构造，则产生的贡献至少为：

- 两个首项的贡献 $2$。
- 两个 $n$ 出现的位置的贡献 $2$。

则此时总权值 $\geq 4$，显然不能为最优解。

2. 求解 $f(a)_{\min}$ 的方案数

这里需要分类讨论一下：

- $f(a)_{\min} = 2$

此时首项确定，后面的项无论咋排都不影响，于是答案为 $(n - 1)!$。

- $f(a)_{\min} = 3$

此时需要讨论一下 $p'_1 = n$ 还是 $q'_1 = n$。下面以 $p'_1 = n$ 为例。

设满足 $p'_i = n$ 的 pair 为 $(n, x)$，满足 $q'_i = n$ 的 pair 为 $(y, n)$。

为了不让 $a'_1 = (n, x)$ 和 $a'_i = (y, n)$ 中间夹着的若干项不产生新的贡献，则需要满足 $\forall 1 < j < i, q'_j < x$。

显然符合上述条件的 $j$ 有 $x - 1$ 个，则我们枚举 $a'_1, a'_i$ 之间夹了几个，不难得到答案为：

- $\displaystyle\sum_{i = 0}^{x - 1} A_{x - 1}^i (n - i - 2)!$

综上，时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
int p[500007], q[500007];
ll fac[500007], inv_fac[500007];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[n] = quick_pow(fac[n], mod - 2, mod);
	for (register int i = n - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline ll arrange(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * inv_fac[n - m] % mod;
}

int main(){
	int n = read(), pos1, pos2;
	init(n);
	for (register int i = 1; i <= n; i++){
		p[i] = read();
		if (p[i] == n) pos1 = i;
	}
	for (register int i = 1; i <= n; i++){
		q[i] = read();
		if (q[i] == n) pos2 = i;
	}
	if (pos1 == pos2){
		printf("2 %lld", fac[n - 1]);
	} else {
		ll ans = 0;
		for (register int i = 0; i < q[pos1]; i++){
			ans = (ans + fac[n - i - 2] * arrange(q[pos1] - 1, i) % mod) % mod;
		}
		for (register int i = 0; i < p[pos2]; i++){
			ans = (ans + fac[n - i - 2] * arrange(p[pos2] - 1, i) % mod) % mod;
		}
		printf("3 %lld", ans);
	}
	return 0;
}
```

---

## 作者：gyyyyx (赞：1)

[题面](https://www.luogu.com.cn/problem/P9306)

很简单的结论题。

首先可以肯定，对于仅有的一个 $p_x=n$ 的 $x$，**一定会**对权值产生 $1$ 的贡献，$\forall_{k>x}$ 则**不可能**产生贡献。

对于仅有的一个 $q_y=n$ 也是一样。

分两种情况：

1. $x=y$

	此时如果将 $a_{x(y)}$ 放在开头，则后面无论如何排列都不会产生贡献，总权值最小为 $2$，方案数为 $(n-1)!$。

2. $x\neq y$

	此时我们可以选择将 $a_x$ 或 $a_y$ 放在开头，这样就只需要考虑另一维的排列方式了。

	假设将 $a_x$ 放在开头，即只考虑 $q_x$ 在第一位的 $q$ 的排列。

	很显然 $q$ 的贡献最小为 $2$，加上 $p$ 的贡献 $1$，总权值最小为 $3$。

	之后我们会发现后面排列满足这样的性质：

	- $\forall_{q_k>q_x}$，$a_k$ 之前必须有 $a_y$（$q_y=n$）；$\forall_{q_k<q_x}$，无论如何排列都不会产生贡献。

	那么方案数就应该有：

    $$(n-q_x-1)!C_{n-1}^{q_x-1}(q_x-1)!=\frac{(n-1)!}{n-q_x}$$

    同理可得将 $a_y$ 放在开头的方案数为：

    $$(n-p_y-1)!C_{n-1}^{p_y-1}(p_y-1)!=\frac{(n-1)!}{n-p_y}$$

    所以总方案数为：

    $$\frac{(n-1)!}{n-q_x}+\frac{(n-1)!}{n-p_y}$$

代码：

```cpp
#include<bits/stdc++.h>
#define N 500005
#define P 998244353
#define LL long long
using namespace std;
inline LL read(){
    LL x(0),f(1);char c(getchar());
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int n,p[N],q[N],mp,mq;
inline LL MUL(int x,int y){
	LL res(1);
	for(int i(1);i<=x;++i)
		if(i^y) (res*=i)%=P;
	return res;
}
int main(){
	n=read();
	for(int i(1);i<=n;++i){
		p[i]=read();
		if(p[i]==n) mp=i;
	}
	for(int i(1);i<=n;++i){
		q[i]=read();
		if(q[i]==n) mq=i;
	}
	if(mp^mq) printf("3 %lld\n",(MUL(n-1,n-q[mp])+MUL(n-1,n-p[mq]))%P);
	else printf("2 %lld\n",MUL(n-1,0));
	return 0;
}
```

---

