# [ABC151E] Max-Min Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc151/tasks/abc151_e

有限個の整数からなる集合 $ X $ に対し $ f(X)=\max\ X\ -\ \min\ X $ と定義します。

$ N $ 個の整数 $ A_1,...,A_N $ が与えられます。

このうち $ K $ 個を選び、それらからなる集合を $ S $ とします。同じ値であっても添字が異なる要素を区別すると、そのような選び方は $ {}_N\ C_K $ 通りありますが、その全てについての $ f(S) $ の合計を求めてください。

答えは非常に大きくなる可能性があるので、$ \bmod\ 10^9+7 $ で出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N $
- $ |A_i|\ \leq\ 10^9 $

### Sample Explanation 1

$ S $ の選び方は $ \{1,1\},\{1,3\},\{1,4\},\{1,3\},\{1,4\},\{3,4\} $ の $ 6 $ 通りあり (ふたつの $ 1 $ は区別します)、$ f(S) $ はそれぞれ $ 0,2,3,2,3,1 $ となるので、合計は $ 11 $ です。

### Sample Explanation 2

$ S $ の選び方は $ 20 $ 通りあり、そのうち $ 18 $ 通りで $ f(S)=20 $、$ 2 $ 通りで $ f(S)=0 $ となります。

### Sample Explanation 4

合計は $ \bmod\ 10^9+7 $ で出力してください。

## 样例 #1

### 输入

```
4 2
1 1 3 4```

### 输出

```
11```

## 样例 #2

### 输入

```
6 3
10 10 10 -10 -10 -10```

### 输出

```
360```

## 样例 #3

### 输入

```
3 1
1 1 1```

### 输出

```
0```

## 样例 #4

### 输入

```
10 6
1000000000 1000000000 1000000000 1000000000 1000000000 0 0 0 0 0```

### 输出

```
999998537```

# 题解

## 作者：TonyYin (赞：8)

本题标签：组合数学

大致难度：绿～蓝？

### 如果你没有思考超过十分钟，建议你再去思考一下。

## $\rm{Description}$

给定 $n$ 个数，构成集合 $A$。从 $A$ 中任取 $k$ 个数，构成 $A$ 的子集 $S$. 

记 $\rm{Max}$ 为 $S$ 中的最大值，$\rm{Min}$ 为 $S$ 中的最小值，$f(S)=\rm{Max-Min}$.

题目要求：所有满足 $|S|=k$ 的 $f(S)$ 之和。（对 $1e9+7$ 取模）

## $\rm{Solution}$

观察数据范围，期望时间复杂度为： $\mathcal{O}(n\log n)$ 或者 $\mathcal{O}(n\log |x|)$ 的做法。

暴力的方法就是 $C_n^k$ 枚举元素个数为 $k$ 的子集，然后找最大值和最小值，复杂度爆炸，期望得分 $0$ 分.

考虑**集合的无序性**。

将集合内的元素升序排序，之后发现可以**计算每个数可能在多少个子集中成为最大值/最小值**。

考虑如何**统计作为子集中最大值的次数**。

具体地，对于前 $k - 1$ 个数，不可能成为任何一个子集的最大值；对于其余的数，第 $i$ 个数成为最大值的方法数是 $C_{i-1}^{k-1}$ 种，也就是在前 $i-1$ 个数中取 $k-1$ 个，与第 $i$ 个数一起构成子集，这样的子集能使 $i$ 为最大值。

```cpp
for(int i = k; i <= n; i++) { //算一遍最大值
	ans += a[i] * C(i - 1, k - 1);
}
//为了美观，这里的代码没有取模。下面Code部分的代码有取模。
```

对于**统计作为子集中最小值的次数**，与最大值同理。

```cpp
for(int i = 1; i <= n - k + 1; i++) { //算一遍最小值
	ans -= a[i] * C(n - i, k - 1);
}
//为了美观，这里的代码没有取模。下面Code部分的代码有取模。
```

在这个数据范围下，**使用逆元求组合数**就可以了，如果不会用逆元求组合数，可以看一下我写的[这篇博客](https://tonyyin.blog.luogu.org/jin-jie-shuo-lun)，往下翻，可以找到关于组合数取模的部分。

## $\rm{Code}$

给出完整的代码。

```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 100008
using namespace std;
int mod = 1e9 + 7;
int n, k, a[MAXN], fac[MAXN], ans = 0;
int power(int x, int k, int p) {
	int ret = 1;
	while(k) {
		if(k & 1) ret = ret * x % p;
		k >>= 1;
		x = x * x % p;
	}
	return ret % p;
}
int inv(int x, int p) {//求x关于模p的逆元
	return power(x, p - 2, p) % mod;
}
int C(int a, int b) {//直接用逆元求解组合数C(a, b)
	return fac[a] * inv(fac[b], mod) % mod * inv(fac[a - b], mod) % mod;
}
signed main() {
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	sort(a + 1, a + n + 1); //升序排序
	//对于每个数，计算在多少种个子集中，这个数能作为最大值/最小值
	//作为最大值的可能情况是C(i - 1, k - 1)，最小值类似
	for(int i = k; i <= n; i++) { //算一遍最大值
		ans = (ans + a[i] * C(i - 1, k - 1) % mod) % mod;
	}
	for(int i = 1; i <= n - k + 1; i++) { //算一遍最小值
		ans = (ans - a[i] * C(n - i, k - 1) % mod) % mod;
	}
	cout << (ans % mod + mod) % mod << endl;
	return 0;
}
```



---

## 作者：_determination_ (赞：3)

简单组合数学，五分钟秒了。建议评黄。

观察这个式子形式，发现可以把最大和最小分开处理。

考虑统计每个数的贡献。$a_i$ 的贡献就是能选出多少个子序列满足 $a_i$ 是最大值的方案数乘上 $a_i$。

这个系数我们可以直接算。显然其他数都应当小于等于这个数。考虑排序。这样 $a_i$ 的贡献系数就是 $C_{i-1}^{m-1}$。直接预处理阶乘然后逆元快速幂启动即可。最大值和最小值都是类似的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
#define endl '\n'
#define debug cout << "114514" << endl
int n,m;
int a[100010];
const int mod=1e9+7;
int jc[100010];
void init()
{
    jc[0]=1;
    for ( int i = 1 ; i <= n ; i++ )
    {
        jc[i]=jc[i-1]*i%mod;
    }
}
int fp(int x,int p)
{
    int ans=1;
    while(p)
    {
        if(p&1)ans=ans*x%mod;
        x=x*x%mod;
        p>>=1;
    }
    return ans;
}
int inv(int x){return fp(x,mod-2);}
int c(int n,int m)
{
    return jc[n]*inv(jc[m])%mod*inv(jc[n-m])%mod;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for ( int i = 1 ; i <= n ; i++ )
    {
        cin >> a[i]; 
    }
    sort(a+1,a+1+n);
    int ans1=0,ans2=0;
    init();
    for ( int i = m ; i <= n ; i++ )
    {
        ans1=(ans1+c(i-1,m-1)*a[i]%mod)%mod;
        // cout << ans1 << " ";
    }
    // cout << endl;
    for ( int i = 1 ; i <= n-m+1 ; i++ )
    {
        ans2=(ans2+c(n-i,m-1)*a[i]%mod)%mod;
        // cout << c(n-i,m-1) << " " << a[i] << " " << c(n-i,m-1)*a[i] << " ";
        // cout << ans2 << endl;;
    }
    // cout << endl;
    cout << (ans1-ans2+mod)%mod;
    return 0;
}
```

---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DAT_abc151_e%20%5BABC151E%5D%20Max-Min%20Sums/)

# 思路

考虑将 $\max$ 和 $\min$ 的贡献分开计算。

显然我们对这个序列进行一次排序不会影响最终的答案，因此我们可以先排序一下。

然后有一个很经典的 trick，就是你枚举每一个数 $x$，将 $x$ 令为最大值（最小值）。因为我们先前排序过一次，因此我们可以轻易的计算出比 $x$ 小（大）的数的数量，然后我们需要在这些数里面选出剩下的 $k - 1$ 个数，直接组合数算一下，得出方案数 $num$。那么 $x$ 的贡献就是 $num \times x$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Add(a,b) (((a) % mod + (b) % mod) % mod)
#define Sub(a,b) (((a) % mod - (b) % mod + mod) % mod)
#define Mul(a,b) (((a) % mod) * ((b) % mod) % mod)

using namespace std;

const int N = 1e5 + 10,mod = 1e9 + 7;
int n,k,a,b;
int arr[N],fac[N],inv[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline int qmi(int a,int b){
    int res = 1;
    while (b){
        if (b & 1) res = Mul(res,a);
        a = Mul(a,a);
        b >>= 1;
    }
    return res;
}

inline void init(){
    fac[0] = 1;
    for (re int i = 1;i <= n;i++) fac[i] = Mul(fac[i - 1],i);
    inv[n] = qmi(fac[n],mod - 2);
    for (re int i = n - 1;~i;i--) inv[i] = Mul(inv[i + 1],i + 1);
}

inline int C(int n,int m){
    if (n < m) return 0;
    return Mul(Mul(fac[n],inv[m]),inv[n - m]);
}

signed main(){
    n = read();
    k = read();
    init();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    sort(arr + 1,arr + n + 1);
    for (re int i = 1;i <= n;i++){
        a = Add(a,Mul(C(n - i,k - 1),arr[i]));
        b = Add(b,Mul(C(i - 1,k - 1),arr[i]));
    }
    printf("%lld",Sub(b,a));
    return 0;
}
```

---

## 作者：cheatme (赞：0)

## 题目描述
给定 $n$ 个数的集合 $A$，任意选择 $k$ 个数构成集合 $S$，求每个集合 $S$ 的最大值减最小值的总和。
## 题目分析
首先可以想到暴力枚举每个集合 $S$，并求出每个集合的最大值减最小值的差再相加，但是时间复杂度会爆炸。

考虑优化，可以先将集合 $A$ 从小到大排序，在依次判断最大值和最小值，再用逆元来求 $C$。

最大值：令现在最大值的下标为 $i$，一共需要 $k$ 个数，除最大值外还需要有 $k-1$ 个数，除最大值之外还有 $i-1$ 个数，所以方案数为 $C_{i-1}^{k-1}$ 种，在乘上最大值的值，就是以下标为 $i$ 的最大值所贡献的大小 $(i \ge k)$。
```cpp
for(int i=k;i<=n;++i)
{
  sum=(sum+C(i-1,k-1)*a[i])%mod;
}
```
最小值：和最大值同理，分开判断在相减即可，最小值下标从 $i=1$ 开始，到 $i=n-k+1$ 结束，因为排序后第一个数是最小的，并且选 $k$ 个数，再选到 $n-k+1$ 个数时就到了最后，在多选一个就选不满 $k$ 个数了，所以方案数为 $C_{n-i}^{k-1}$ 种，再乘上最小值的值，就是以下标为 $i$ 的最小值所贡献的大小。
```cpp
for(int i=1;i<=n-k+1;++i)
{
  sum=(sum-C(n-i,k-1)*a[i])%mod;
}
```

## [Code](https://www.luogu.com.cn/record/178566761)
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+7,mod=1e9+7;
int n,k,a[N],inv[N],sv[N];
int ksm(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res%mod;
}
int C(int a,int b)
{
	return inv[a]*sv[b]%mod*sv[a-b]%mod;
}
void solve()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+1+n);
	inv[0]=1;
	for(int i=1;i<=n;++i) inv[i]=(inv[i-1]*i)%mod;
	sv[n]=ksm(inv[n],mod-2);
	for(int i=n;i>=1;--i) sv[i-1]=(sv[i]*i)%mod;
	int sum=0,res=0;
	for(int i=k;i<=n;++i)
	{
		sum=(sum+C(i-1,k-1)*a[i])%mod;
	}
	for(int i=1;i<=n-k+1;++i)
	{
		res=(res+C(n-i,k-1)*a[i])%mod;
	}
	cout<<((sum-res)+mod)%mod<<'\n';
}
signed main()
{
	solve();
	return 0;
}
```

---

## 作者：_WF_ (赞：0)

## 题意分析
给定 $n$ 个数和一个 $k$ 求最大值减去最小值的总和。并对 $10 ^ 9+7$ 取模。
* 前置知识：逆元，组合数。
## 具体解决
对于每一位数，考虑它作为**最小值**和**最大值**出现的次数。

因为**最大值**和**最小值**一定在一个**排序后**的序列的两边，所以考虑对已知队列排序。因而每次固定前后判断组合数即可。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000000+7;
long long num[100005];
long long vis[105000];
long long ans=0;
long long qpow(long long a, long long b){
    long long sum=1;
    while(b>0){
        if(b&1)sum=sum*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return sum;
}
long long C(long long a,long long b){
    if(b>a)return 0;
    return vis[a]*qpow(vis[b]*vis[a-b]%mod,mod-2)%mod;
}
int main(){
    int n,k;
    cin>>n>>k;
    vis[0]=1;
    for(int i=1;i<n+2;++i)
        vis[i]=vis[i-1]*i%mod;
    for(int i=0;i<n;++i)cin>>num[i];
    
    sort(num, num+n);
    for(int i=0;i<n-k+1;++i){
        ans=(ans+(num[n-i-1]-num[i])%mod*C(n-i-1,k-1)%mod)%mod;
    }
    printf("%lld\n" ,(ans % mod + mod)%mod);
}
```

---

## 作者：analysis (赞：0)

容易发现，$k=1$ 时答案为 $0$。

$k\geq2$ 时
$$
ans = \sum_{i=1}^{n}\sum_{j=i+k-1}^{n}\binom{j-i-1}{k-2}a_j - \sum_{i=1}^{n}\sum_{j=i+k-1}^{n}\binom{j-i-1}{k-2}a_i = S_1-S_2
$$

$$
S_1 = \sum_{i=1}^{n}\sum_{j=i+k-1}^{n}\binom{j-i-1}{k-2}a_j \\
= \sum_{j=k}^{n}a_j\sum_{i=1}^{j - k + 1}\binom{j-i-1}{k-2}\\
$$

后面的东西：
$$
\sum_{i=1}^{j - k + 1}\binom{j-i-1}{k-2} \\
= \sum_{i=k-2}^{j -2}\binom{i}{k-2} \\
$$
是一个上指标求和：
$$
\sum_{i=0}^{n}\binom{i}{m} = \binom{n+1}{m+1} \\ \\
$$
所以：
$$
\sum_{i=k-2}^{j -2}\binom{i}{k-2} \\
= \sum_{i=0}^{j -2}\binom{i}{k-2} \\
= \binom{j-1}{k-1}\\
S_1 = \sum_{j=k}^{n}a_j\binom{j-1}{k-1}\\
$$
容易计算得到 $S_1$。

类似的，有：
$$
S_2 = \sum_{i=1}^{n}\sum_{j=i+k-1}^{n}\binom{j-i-1}{k-2}a_i\\
=\sum_{i=1}^{n}a_i\sum_{w=k-2}^{n-i-1}\binom{w}{k-2}\\
=\sum_{i=1}^{n}a_i\binom{n-i}{k-2}\\
$$

---

## 作者：_Flame_ (赞：0)

## 思路

先看数据范围，枚举每一个大小为 $k$ 的子集肯定不实际，于是改变思路，开始思考其他方法。

思考一下每个数作为长度为 $k$ 的子集中最大值与最小值的可能性，对集合内元素进行排序后，可以发现对于较小的 $k-1$ 个数，他们是不可能作为长度为 $k$ 子集的最大值，对于剩下的数，第 $i$ 个数会有 $C_{i-1}^{k-1}$ 种可能性，对于最小值，同理求解即可。

最后统计答案，对于每个数 $i$，若是作为最大值，则答案加上 $a_i\times C_{i-1}^{k-1}$，若是作为最小值，减去 $a_i\times C_{n-i}^{k-1}$ 即可。
## Code

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=500010;
const int mod=1e9+7;

int ksm(int a,int b){
    int ans=1;
    while(b>0){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b/=2;
    }
    return ans%mod;
}

int n,k;
int a[maxn];
int pre[maxn],v[maxn];
int mn[maxn],mx[maxn],tot1,tot2;

void init(int n){for(int i=2;i<=n;i++) pre[i]=pre[i-1]*i%mod,v[i]=ksm(pre[i],mod-2);}

int C(int a,int b){
	if(!a) return 1;
	else if(a==b) return 1;
	else return (pre[a]*v[a-b]%mod*v[b]%mod)%mod;
}

int ans=0;

void solve(){
	n=read(),k=read();
	pre[1]=1,v[1]=1;
	init(n);
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for(int i=k;i<=n;i++) mx[++tot1]=(a[i]*C(i-1,k-1)%mod)%mod; 
	for(int i=1;i<=n-k+1;i++) mn[++tot2]=(a[i]*C(n-i,k-1)%mod)%mod; 
	for(int i=1;i<=tot1;i++) ans=(ans+mx[i])%mod;
	for(int i=1;i<=tot2;i++) ans=(ans-mn[i])%mod;
	write((ans+mod)%mod);
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

组合数学题。

## 思路：
(下文中的子集均指长度为 $k$ 的子集)

首先，显然不能直接暴力枚举每个子集，否则 T 飞。

发现我们只用到了集合的最大值和最小值，那么转换一下切入点：我们只考虑每一个位置上的数能成为几个子集的最大值、最小值。


所以将 $a$ 数组排序，设第 $i$ 个数是 $a_i$，是 $minc_i$ 个子集的最小值，$maxc_i$ 个子集的最大值，则此位置对答案的贡献就是 $a[i] \times (maxc_i - minc_i)$。

现在来求 $minc_i$ 和 $maxc_i$。 显然，当 $a_i$ 为子集的最大值，剩下 $k-1$ 个数都得在 $a_i$ 前面的数选。故 $minc_i = C_{i-1}^{k-1}$；同理有 $maxc_i=C_{n-i}^{k-1}$。

最后统计答案即可，复杂度 $O(n)$。

## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
using namespace std;
const int N=1e5+5;
const int p=1e9+7;

il int wrd(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,k,a[N],minc[N],maxc[N],pre[N],ans;

il int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=p;
		(a*=a)%=p;
		b>>=1;
	}
	return ans;
}

int C(int n,int m){
	int x=pre[n]*qpow(pre[n-m],p-2)%p,y=pre[m];
	return x*qpow(y,p-2)%p;
}

main(){
	n=wrd(),k=wrd(),pre[0]=1;
	for(int i=1;i<=n;++i) a[i]=wrd(),pre[i]=pre[i-1]*i%p;
	sort(a+1,a+n+1);
	if(k==1) return puts("0"),0;
	
	for(int i=1;i<=n-k+1;++i) minc[i]=C(n-i,k-1); //a[i]作为能作为几个集合的最小值。
	for(int i=k;i<=n;++i) maxc[i]=C(i-1,k-1); //a[i]作为能作为几个集合的最大值。
	for(int i=1;i<=n;++i) ans=(ans+(((maxc[i]-minc[i]+p)%p*a[i]%p)+p)%p)%p; //位置i对答案的贡献：a[i]*(maxc[i]-minc[i])。
	return printf("%lld",ans),0;
}
```

---

## 作者：f_x_f (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4846)

# 翻译

给你一个整数集合 $A,|A|=n$ 和一个数 $k$ 。

求 $\displaystyle\sum_{S\in A,|S|=k} f(S)$ ，对 $10^9+7$ 取模。

其中，定义几何运算 $f(S)=\displaystyle\max_{x\in S}x-\displaystyle\min_{x\in S}x$ 。 

# 题目分析

对于一个正数 $x,x\in A$ 一定会有 $C_{n}^{i}$ 次是作为集合中最大的元素，其中 $i$ 表示比 $x$ 小的数的个数，也一定会有 $C_{n}^{j}$ 次是作为集合中最小的元素，其中 $j$ 表示的是比 $x$ 大的数的个数。

因此我们可以从 1 到 $n$ ，把其中每个数的作为最大的元素的次数与作为最小元素的次数统计出来就行了。

# 代码

```cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(ll &p){
    ll x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+c-48;c=getchar();}
	return p=x*f;
}
const ll mod=1000000007;
ll n,k,ans,a[100001],Cys[100001];
ll bin_pow(ll na,ll m){
	ll tot=1;
	while(m){
		if(m&1){
			tot=tot*na%mod;
		}
		m>>=1;
		na=na*na%mod;
	}
	return tot;
} 
ll ny(ll na){
	return bin_pow(na,mod-2)%mod;
}
ll CC(ll na,ll m){
	return Cys[na]*ny(Cys[m])%mod*ny(Cys[na-m])%mod;
}
signed main(){
	read(n),read(k);
	Cys[0]=1;
	for(ll i=1;i<=100000;i++){
		Cys[i]=Cys[i-1]*i;
		Cys[i]%=mod;
	}
	for(ll i=1;i<=n;i++){
		read(a[i]);
	}
	sort(a+1,a+n+1);
	for(ll i=1;i<=n;i++){
		if(i>=k)ans=(ans+a[i]*CC(i-1,k-1)%mod)%mod;
		if(i<=n-k+1)ans=(ans-a[i]*CC(n-i,k-1)%mod+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}


```

---

## 作者：Jairon314 (赞：0)

> [题目链接](https://atcoder.jp/contests/abc151/tasks/abc151_e)

$ Solution $

------------

撞不知道哪次比赛的原题了，经典 trick 。先考虑最大值的和，排一遍序，枚举 $ i $ 为扫到了当前第 $ i $ 个位置，那么前 $ i-1 $ 个数都比第 $ i $ 个位置的数小，那么这个数能构成的贡献即为 $ a_i \times C(i-1,k-1) $ 。意思是从前面 $ i-1 $ 个数中取出 $ k-1 $ 个与第 $ i $ 个数结合就形成了一个最大值为 $ a_i $ 长度为 $ k $ 的子序列。

最小值同理。

[AC记录](https://atcoder.jp/contests/abc151/submissions/29157246)

代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
using namespace std;

#define int long long

/***** Fast_IO *****/

using vii = vector<int>;
using pii = pair<int,int>;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	#define gc getchar
	#define pc putchar

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
	
	template<class I>
	inline void chmax(I &x,I y){ return x=max(x,y),void(); }
	
	template<class I>
	inline void chmin(I &x,I y){ return x=min(x,y),void(); }

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define sqr(k) ((k)*(k))
	#define inf 0x3f3f3f3f
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
	#define db double
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

const int mod = 1e9+7;

int N,K;
int A[maxn];

int fac[maxn]={1,1};

void initial(){ FOR(i,1,N){ fac[i]=(fac[i-1]*i)%mod; } }

int qpow(int a,int b){
	int res=1,tmp=a;
	while(b){ if(b&1){ res=(1ll*res*tmp)%mod; } tmp=(1ll*tmp*tmp)%mod; b>>=1; }
	return res;
}

int inv(int k){ return qpow(k,mod-2); }

int C(int n,int m){
	if(n<m){ return 0; }
	return 1ll*fac[n]*inv(fac[n-m])%mod*inv(fac[m])%mod;
}

int Mx,Mn;

signed main(){
	read(N,K);
	initial();
	FOR(i,1,N){ read(A[i]); }
	sort(A+1,A+N+1);
	FOR(i,K,N){ Mx=(Mx+1ll*A[i]*C(i-1,K-1)%mod)%mod; }
	reverse(A+1,A+N+1);
	FOR(i,K,N){ Mn=(Mn+1ll*A[i]*C(i-1,K-1)%mod)%mod; }
	outn((Mx-Mn+mod)%mod);
	return 0;
}
```


---

## 作者：Lynkcat (赞：0)

模拟赛做到的题，感觉想到的思路有点新奇，就来写一发题解。

首先容易想到将 $a$ 升序排序，这样在处理的时候就会方便很多。现在我们考虑一个长度为 $x(k\leq x)$ 的区间在序列中滑动，这个区间对答案的贡献就是右端点的权值减去左端点的权值乘上区间中选 $k-2$ 个数的方案，即 $(a[r]-a[l])\times C_{x-2}^{k-2}$，拆开来为 $a[r]\times C_{x-2}^{k-2}-a[l]\times C_{x-2}^{k-2}$，发现 $C_{x-2}^{k-2}$ 对于相同的 $x$ 是固定的，考虑如何计算 $\sum a[r]-a[l]$。 

接下来考虑每个点可以作为长度为多少的区间的左端点，容易发现第 $i(i\leq n-k+1)$ 个点可以作为 $k$ 到 $n-k+1$ 长度的区间的左端点，那么我们直接差分计算贡献。右端点同理。

最后 $O(n)$ 计算即可。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 1000000007
#define int ll
#define N 100005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int fc[N],inv[N],a[N],n,m,ans,lastans,s[N];
inline ll quickPower(int x,int y)
{
	ll res=1;
	while (y)
	{
		if (y&1)res=(res*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return res;
}
inline ll C(int x,int y)
{
	if (y==0) return 1;
	if (x==0) return 0;
	return (1LL*inv[y]%mod*inv[x-y]%mod*fac[x]%mod)%mod;
}
signed main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	fac[0]=1;
	for (int i=1;i<=n;i++) fac[i]=(fac[i-1]*i)%mod;
	inv[0]=1;
	for (int i=1;i<=n;i++) inv[i]=quickPower(fac[i],mod-2);
	for (int i=1;i<=n;i++)
	{
		s[1]=(s[1]-a[i]+mod)%mod;
		s[n-i+2]=(s[n-i+2]+a[i]+mod)%mod;
	}
	for (int i=1;i<=n;i++)
	{
		s[1]=(s[1]+a[i]+mod)%mod;
		s[i+1]=(s[i+1]-a[i]+mod)%mod;
	}
	for (int i=1;i<=n;i++) s[i]=(s[i-1]+s[i]+mod)%mod;
	for (int i=m;i<=n;i++)
	{
		ans=(ans+(s[i]%mod*C(i-2,m-2))%mod)%mod
	}
	writeln(ans);
		
}
/*

*/



---

