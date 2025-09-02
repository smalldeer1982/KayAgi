# Colorful Bricks

## 题目描述

On his free time, Chouti likes doing some housework. He has got one new task, paint some bricks in the yard.

There are $ n $ bricks lined in a row on the ground. Chouti has got $ m $ paint buckets of different colors at hand, so he painted each brick in one of those $ m $ colors.

Having finished painting all bricks, Chouti was satisfied. He stood back and decided to find something fun with these bricks. After some counting, he found there are $ k $ bricks with a color different from the color of the brick on its left (the first brick is not counted, for sure).

So as usual, he needs your help in counting how many ways could he paint the bricks. Two ways of painting bricks are different if there is at least one brick painted in different colors in these two ways. Because the answer might be quite big, you only need to output the number of ways modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, since $ k=0 $ , the color of every brick should be the same, so there will be exactly $ m=3 $ ways to color the bricks.

In the second example, suppose the two colors in the buckets are yellow and lime, the following image shows all $ 4 $ possible colorings.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1081C/4fa7a2f23ff4f46a8191eb0b20c44295510018b7.png)

## 样例 #1

### 输入

```
3 3 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2 1
```

### 输出

```
4
```

# 题解

## 作者：houzhiyuan (赞：8)

# CF1081C 【Colorful Bricks】

## 题意

有$n$个砖，染$m$种颜色，$k$个间隔两边的砖颜色不同，求方案总数。

这显然是一个组合题，可以将颜色相同的球看做是一个球，如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/aqpxa44l.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这是$n=6,m=3,k=2$的一种情况。

显然，这样整合之后会有$k+1$个整体，那么对这$k+1$个整体染$m$种颜色，第一个整体有$m$种染色，后面每一个都不能染上一个染过的颜色，故总方案数为$m(m-1)^k$

那么我们下一步就要求有多少种整合的方法。

由于一共$n$个球，有$n-1$个空隙，在这些空隙中任意选择$k$个不同的空隙，使得两边的颜色不同的整合方案都是不一样的，即为$  \mathrm C_{n-1}^{k}  $

最后答案就是$  \mathrm C_{n-1}^{k} * m(m-1)^k$

最后献上特别丑的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long jie[2001],ni[2001],max1=2000,mod=998244353,n,k,m;
long long cheng(long long x,long long y){//乘法
	return (x*y)%mod;
}
long long kuai(int k,int x){//快速幂
	long long s=1;
	for(;x;k=cheng(k,k),x=x>>1){
		if(x&1){
			s=cheng(s,k);
		}
	}
	return s;
}
void work(){//求阶乘，逆元
	jie[0]=ni[0]=1;
	for(int i=1;i<=max1;i++){//阶乘
		jie[i]=cheng(jie[i-1],i);
	}
	ni[max1]=kuai(jie[max1],mod-2);//根据费马小定理求逆元
	for(int i=max1-1;i>=1;i--){//逆元递推
		ni[i]=cheng(ni[i+1],i+1);
	}
}
long long C1(long long a,long long b){//计算组合数
	return cheng(jie[a],cheng(ni[b],ni[a-b]));
}
int main(){
	cin>>n>>m>>k;
	work();
	cout<<cheng(C1(n-1,k),cheng(kuai(m-1,k),m));//计算最后的结果
	return 0;
}

```

---

## 作者：YB_is_short (赞：6)

- 首先，很显然可以看出是在$n$个球之间放$k$个隔板，每两个隔板之间的颜色都是相同的，每个隔板两边的求颜色不同，所以方案数为$\binom{n-1}{k}$。

- 然后，就把所有的求分成了$k+1$份，第一部分的颜色可以是全部的，有$m$种可能，后面的k个部分的颜色就不能和前面的一样了，所以就只能有$m-1$种可能，总数就为$m(m-1)^k$

- 所以，就可以~~很容易~~地求出总方案数：$\binom{n-1}{k}m(m-1)^k$

---

## 作者：Ousmane_Dembele (赞：5)

一道水水的dp题……

定义$dp[i][j][k]$表示在第i个，当前颜色是j，包括i在内的2-i共有k个和前面不一样。

我们可以发现，答案跟具体的颜色并没有关系，所以可以删去j维

初始化很简单 
$from- one-to- n, dp[i][0]=m$因为无论在第几个上如果有0个和前面不一样，那就只能全部是一个颜色，共m中可能

那么如何转移？

两种可能。

第一种是前面一个就有k个和前面不一样的颜色了，那为了保持住k个，这个要跟之前一样，共1种可能

第二种是前面一个有$k-1$个和前面不一样的颜色，为了到达k个，这个要跟之前不一样，共$m-1$种可能

所以状态转移方程就出来了。

$dp[i][j]=dp[i-1][j-1]*(m-1)+dp[i-1][j] (1<=i<=n,1<=j<=k)$

代码：
```
#include<bits/stdc++.h>
using namespace std;
long long dp[2001][2001];
long long md=998244353;
int n,m,k;
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        dp[i][0]=m;
        for(int j=1;j<min(k+1,i);j++){
            dp[i][j]=dp[i-1][j]+dp[i-1][j-1]*(m-1);
            dp[i][j]%=md;
        }
    }
    cout<<dp[n][k];
}
```


---

## 作者：Wf_yjqd (赞：3)

好吧，作业第一题——瞎推就行了。

------------

考虑转化问题，分成两部分进行讨论。

先是要分成 $k+1$ 块，每块的和相等。

运用隔板法可知，答案为 $C_{n-1}^k$（在 $n-1$ 个空格中选 $k$ 个）。

第二部分为，将每个块染上与前一个不同的颜色。

考虑第一个块有 $m$ 种选法，而剩下的各有 $m-1$ 种，快速幂维护即可。

运用乘法原理，总体答案为两个部分的和。

于是结束了。。

------------

数学题也需要看代码？。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
const ll maxn=2e3+84;
ll n,m,k,inv[maxn],jc[maxn][2];
inline ll C(ll n,ll m){
    return jc[n][0]*jc[m][1]%mod*jc[n-m][1]%mod;
}
inline ll poww(ll n,ll m){
    if(m<0)
        return 1;
    if(!m)
        return 1;
    if(m&1)
        return poww(n,m-1)*n%mod;
    ll ans=poww(n,m>>1)%mod;
    return ans*ans%mod;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    inv[0]=jc[0][0]=jc[0][1]=inv[1]=jc[1][0]=jc[1][1]=1;
    for(ll i=2;i<=max(n,m);i++){
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
        jc[i][0]=jc[i-1][0]*i%mod;
        jc[i][1]=jc[i-1][1]*inv[i]%mod;
    }
    printf("%lld",C(n-1,k)*poww(m-1,k)%mod*m%mod);
    return 0;
}
```


---

## 作者：sunzz3183 (赞：3)

# CF1081C 【Colorful Bricks】

## 题意

给一个长度为 $n$ 的序列染色，每个元素可以染 $m$ 种颜色，要求**恰好**有 $k$ 对相邻的元素颜色**不同**，问方案数。

## 分析

我们把相同颜色的元素给看做一个元素。

那么此时就有 $k+1$ 个元素。

所以，第一个元素有 $m$ 种选法，后 $k$ 个数有 $m-1$ 种选法，所以答案为：

$$ m\times (m-1)^k $$

然后我们发现，一共有 $n-1$ 对元素，选 $k$ 对不同的，所以方案为：

$$ C_{n-1}^k $$

所以总方案数为：

$$ m\times (m-1)^k \times C_{n-1}^k $$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0;bool f=0;char c=getchar();
    while(c<'0'||'9'<c){if(c=='-')f=1;c=getchar();}
    while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return f?-x:x;
}
const int mod=998244353;
inline int ksm(int a,int b){int t=1;for(;b;b>>=1,a=a*a%mod)if(b&1)t=t*a%mod;return t%mod;}//快速幂
int n,m,k,ans;
inline int C(int n,int m){//求组合数
    if(n<m)return 0;
    if(m>n-m)m=n-m;
    int a=1,b=1;
    for(int i=1;i<=m;i++)
        a=a*(n-i+1)%mod,b=b*i%mod;
    return a*ksm(b,mod-2)%mod;
}
signed main(){
    n=read();m=read();k=read();
    printf("%lld\n",m*ksm(m-1,k)%mod*C(n-1,k)%mod);
    return 0;
}
```

---

## 作者：zhangqiuyanAFOon2024 (赞：2)

### 读题
先读题，题目意思很简单。
### 思路
像这种求个数的，肯定先想到的是 `dp`。

我们设一个数组，$dp_{i,j}$ 表示前 $i$ 块砖，有 $j$ 个颜色与左边相同的砖块。

答案就是 $dp_{n,k}$。
### 解决
想要写 `dp` 就必须知道动态转移方程。

考虑 $dp_{i+1,j}$ 如何从 $dp_{i,j}$ 转移。

显然，$j$ 没有发生改变，所有只能是与上面同一种颜色。

即只有一种方案，所以 $dp_{i+1,j}\gets dp_{i+1,j}+dp_{i,j}$。

接着，考虑如何转移 $dp_{i+1,j+1}$。

$j$ 加了 $1$，所以颜色不同，有 $m-1$ 种方案，即 $dp_{i+1,j+1}\gets dp_{i+1,j+1}+dp_{i,j}\times(m-1)$。

### 注意

$1$.要开 `long long`。

$2$.$dp_{1,0}\gets m$，因为任意一种颜色都可以。

$3$.取模。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353;
int n,m,k;
int dp[2005][2005];
signed main(){
	cin>>n>>m>>k;
	dp[1][0]=m;
	for(int i=1;i<n;++i)
		for(int j=0;j<=k;++j){
			dp[i+1][j]=(dp[i+1][j]+dp[i][j])%MOD,
			dp[i+1][j+1]=(dp[i][j]*(m-1)+dp[i+1][j+1])%MOD;
		}
	cout<<dp[n][k];
}
```
### 完结撒花！

---

## 作者：Sincerin (赞：1)

[题目传送门！](https://www.luogu.com.cn/problem/CF1081C)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-cf1081c)

## 题意

给定 $n$ 块排成一排的砖，你手上一共有 $m$ 种颜料，可以给这些砖块染色。你希望在染完色以后一共只会有 $k$ 块砖与它左边的砖颜色**不同**，请你计算一共有多少种不同的染色方案。答案对 $998244353$ 取模。

- $1 \leq n,m \leq 2000 \ , 0 \leq k \lt n $。

## 解析

先来看一种情况，当 $n=8$，$k=3$ 时，我们假设与它左边的砖颜色不同的砖就是下图标红的三块砖。

![](https://cdn.luogu.com.cn/upload/image_hosting/uq4aeyhu.png)

很明显，$1$ 号砖与左边第一块标灰的砖不是同一种颜色。由于 $1$ 号左边第一块砖并不是与左边的砖颜色不同的 $k$ 块砖之一，所以 $1$ 号左边两块标灰的砖是相同的颜色，并且他们的颜色与 $1$ 号不同。

同理，因为 $1$ 号右边第一块标灰的砖不是与左边的砖颜色不同的 $k$ 块砖之一，所以它与 $1$ 号颜色相同。由此也可知 $1$ 号右边两块标灰的砖是相同的颜色，并且他们的颜色与 $1$ 号相同。$2$ 号，$3$ 号也是如此。

这样我们就很容易看出来了，其实这 $k$ 块与左边颜色不同的砖相当于 $k$ 块隔板，将整排砖分成了 $k+1$ 段，每段内部的颜色都相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/ich1krjo.png)

如上图，分成四份是因为第一块与左边颜色不同的砖将最左边的部分也划成了颜色相同的一部分。

当然也可以这样理解，有 $k$ 块砖与前面的部分颜色不同，每块砖标记前面的一段，划成了 $k$ 段，但是最后一块这样的砖和它后面的砖无法被标记，自成一段，共 $k+1$ 段。

这样第一段可以有 $m$ 种颜色选择，后面每段与前一段不同，都有 $m-1$ 种颜色选择。$k+1$ 段的总方案数为 $m \times (m-1)^k$。

上述的方案数是在 $k$ 块砖确定的情况下计算的。我们刚才提到可以在这 $k$ 块砖前面都放上一块隔板来把这排砖分成 $k+1$ 段，但第一块砖不能选，只能在剩下 $n-1$ 块砖中选 $k$ 块砖在其前面放上隔板，方案数为 $C_{n-1}^k$ 种。

总方案数为 $C_{n-1}^k \times m \times (m-1) ^k$ 种。


注意组合数的公式 $C_{n}^m =\large\frac{n!}{m! \times (n-m)!}$ 中出现了除法，而题目又要求对质数 $998244353$ 取模，我们知道除法取模是错误的，这时可以把除法转换成乘法，约分得到 $C_{n}^m=\large \frac{ \prod\limits_{ i=n-m+1}^n {i}}{m!}$。这时可以将其看成分子和 $(m!)^{-1}$ 相乘的结果，在对其进行乘法取模即可。

根据费马小定理可知，当 $p$ 为质数且 $\operatorname{gcd}(a,p)=1$ 时，$a^{-1} \equiv a^{p-2} \pmod p$。$a^{p-2}$ 就叫做 $a$ 在模 $p$ 意义下的逆元。很显然在计算 $m!$ 时也对 $p$ 取模了，所以 $m! \in [1,p-1]$。此时无论 $m!$ 取何值，都有 $\operatorname{gcd}(m!,p)=1$。此时，$\large\frac{n!}{m! \times (n-m)!}\normalsize  \equiv  (m!)^{p-2} \times \prod\limits_{ i=n-m+1}^n  {i} \pmod p$。


## AC Code

```cpp
//C++14(GCC 9) 721B 15ms 8.00KB
#include<iostream>
#include<cstdio> 
#define _ 1 
using namespace std;
#define int long long //防止见祖宗 
int n,m,k,ans;
const int mod=998244353;
inline int power(int a,int b)//快速幂 
{
	int ans=1;
	for(;b;b>>=1)
	{
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
	}
	return ans%mod;
}
inline int Combination(int n,int m)//组合数 
{
	if(n<m) return 0;//C(n,m) (n<m)不合法 
	int res=1,s=1;
	for(register int i=n-m+1;i<=n;++i) res=(res*i)%mod;
	for(register int i=1;i<=m;++i) s=(s*i)%mod; 
	int Inverse=power(s,mod-2);//乘法逆元 
	return (res*Inverse)%mod;
}
signed main(void)
{
	scanf("%lld%lld%lld",&n,&m,&k);
	ans=Combination(n-1,k)%mod*m%mod*power(m-1,k)%mod;
	printf("%lld\n",ans);
	return !(0^_^0);//完结撒花 
}
```

[AC Record](https://www.luogu.com.cn/record/119858296)

---

## 作者：卷王 (赞：0)

我们可以在每一个满足要求的砖头后面插一个板子，这样就是要在 $n-1$ 个空位里插 $k$ 个，方案数为 $C(n-1,k)$。然后，对于第一块砖，有 $m$ 种涂颜色的方式。对于后面的 $k$ 块砖，有 $m-1$ 种涂色方式，因为要跟前面的不同。根据乘法原理可知，答案为 $C(n-1,k) \times m \times {(m-1)}^k$。

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

int C[2007][2007];
int n, m, k, Q, T, _, ans = 0;
inline int power(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline void init(){
	for(int i=0;i<=2000;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
signed main() {
	init();
	n=read(),m=read(),k=read();
	printf("%lld",C[n-1][k]*m%mod*power(m-1,k)%mod);
	return 0;
}
```

---

## 作者：_Only_this (赞：0)

### CF1081C Colorful Bricks 题解

------------

有 $n$ 个砖，把它们分成 $k+1$ 块，每个块里的颜色相同，共有 $m$ 种颜色，求总共的方案数，并对 $998244353$ 取模。

不懂请看例子，（借用一下你谷的图）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1081C/4fa7a2f23ff4f46a8191eb0b20c44295510018b7.png)

此时，$n$ 为 $3$，$m$ 为 $2$，$k$ 为 $1$，方案数为 $4$。

------------

读完题意，容易想到此题要用到组合数学。

首先，先思考块的方案数，显然，方案数为 $C_{n-1}^{k}$，

然后，考虑对于每个块的颜色，第一个块的颜色有 $m$ 种选择，剩下的每个块都有 $m-1$ 种选择，即共有 $m(m-1)^k$ 种选择。

所以，总方案数即为 $C_{n-1}^{k}\times m(m-1)^k$。

至于如何求组合数，这应该不是个难点（下面还是给列出来了）。

$C_{n}^{m}=\dfrac{n!}{m!(n-m)!}$

这个可以用逆元求。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e3+5;
const ll p = 998244353;
int n,m,k;
ll inv[maxn],fac[maxn],ifac[maxn];
void Init(){
	inv[1]=fac[1]=ifac[1]=1;
	for(int i=2;i<=n;i++){
		inv[i]=(p-p/i)*inv[p%i]%p;
		fac[i]=fac[i-1]*i%p;
		ifac[i]=ifac[i-1]*inv[i]%p;
	}
	return ;
}
ll C(ll n,ll m){
	if(!m)
		return 1;
	if(n==m)
		return 1;
	return fac[n]*ifac[m]%p*ifac[n-m]%p;
}
ll Pow(ll x,ll y){
	ll zjx=1;
	if(!y)
		return 1;
	while(y!=1){
		if(y&1)
			zjx*=x,zjx%=p;
		x*=x,x%=p;
		y/=2;
	}
	return x*zjx%p;
}
int main(){
	scanf("%d%d%d",&n,&m,&k),k++;
	Init();
	printf("%lld",C(n-1,k-1)%p*m%p*Pow(m-1,k-1)%p);
	return 0;
}
```

完结，散花(～￣▽￣)～


---

## 作者：chlchl (赞：0)

~~这个题想咋样吧，又不卡 DP，又是数论题……~~

原本以为题解里的都是数论做法，结果发现我并不是唯一一个发现有 DP 做法的人。

## Solution
言归正传，这个题数据很水，所以考虑方案数 DP。

思路：设 $f_{i,j,l}$ 为第 $i$ 个格子染 $j$ 颜色，一共有 $l$ 个格子颜色与上一个不一样的方案数。这个枚举是 $n^3$ 的，转移是 $n$ 的，总时间复杂度是 $O(n^4)$，~~写个搜索都比你家快~~。

但是注意到，我们枚举的 $m$ 完全多余，根本不需要在意染的是什么颜色，只需要知道是否相等就可以了。

考虑删掉 $j$ 这一维。现在，$f_{i,l}$ 表示前 $i$ 个格子有 $l$ 个与上一格颜色不相同的方案数。这是可以转移的。
- 这个格子颜色与上一格不相同，那就从前 $i-1$ 个格子有 $l-1$ 个不相同的状态，即 $f_{i-1,l-1}$ 转移过来。这一格只需要跟前面一格颜色不同就行了，所以有 $m-1$ 种颜色可填，乘上 $m-1$。
- 这个格子颜色与上一格相同，那就从前 $i-1$ 个格子有 $l$ 个不相同的状态，即 $f_{i-1,l}$ 转移过来。此时只能填上一格的那种颜色，所以只有一种情况。

然后就做完了。~~也不知道为啥滚动数组炸了。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2000 + 10;
const int MOD = 998244353;
int n, m, k, f[N][N];

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i=1;i<=n;i++)	f[i][0] = m;
	for(int i=1;i<=n;i++){
		for(int l=1;l<=k;l++)	(f[i][l] += 1LL * f[i - 1][l] * (m - 1) % MOD + f[i - 1][l - 1] % MOD) %= MOD;
	}
	printf("%d\n", f[n][k]);
	return 0;
} 
```


---

## 作者：Tony102 (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1081C)

[更好的阅读体验](https://tony102.xyz/index.php/2020/11/14/cf1081c-colorful-bricks/)

### Sol

这种跟旁边的的东西有限制的题目通常可以用插板法做

相当于现在我要插$k$块板子进去，现在这一排砖被分成了$k+1$段

现在钦定有第一块板子右边那块砖的颜色，有 $m$ 种选择。那么剩下的 $k-1$ 块板子右边的都可以涂 $m-1$ 种颜色，就有$(m-1)^k$ 种方案。同时保证板子左边和右边的颜色不同。

现在的问题是，要在这$n$块砖中选择一些位置插板子，因为 $n$ 个球只有 $n-1$ 个位置，所以有 $\binom{n-1}{k}$ 种方案。

根据乘法原理可得最后的答案是：

$$\binom{n-1}{k}\times m(m-1)^k$$



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int SIZE = 2e3 + 5;
const int mod = 998244353;

int n, m, k;
int fac[SIZE], inv[SIZE];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline int qPow(int a, int b)
{
	int ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return ans % mod;
}

inline void init()
{
	fac[0] = 1;
	for (int i = 1; i <= 2000; ++ i) fac[i] = fac[i - 1] * i % mod;
	inv[2000] = qPow(fac[2000], mod - 2) % mod;
	for (int i = 1999; i >= 0; -- i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

inline int C(int x, int y)
{
	if (y == 0) return 1;
	return ((fac[x] % mod) * (inv[y] * inv[x - y] % mod) % mod);
}

signed main()
{
	// freopen("code.in", "r", stdin);
	// freopen("code.out", "w", stdout);
	init();
	n = read(), m = read(), k = read();
	// for (int i = 1; i <= 10; ++ i) printf("%lld ", inv[i]);
	// puts("");
	if (!k) {
		int ans = m * qPow(m - 1, k) % mod;
		printf("%lld\n", ans % mod);
	}
	else {
		int ans = C(n - 1, k) * m % mod * qPow(m - 1, k) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
```



---

## 作者：VenusM1nT (赞：0)

这题数据范围真是低到令人发指……完全可以用 Lucas / ExLucas 的【雾】  
紫题偏高，可以作为一道组合数学的入门题来做的……  

给初学者讲一下排列组合（？）  
首先考虑 $n$ 个不同数中选 $m$ 个**有序排成一列**一共有多少种方法，显然第一个位置有 $n$ 中选法，第二个位置有 $n-1$ 种选法（因为第一个位置已经确定了），以此类推，总数就是
$$\frac{n!}{(n-m)!}$$
其中
$$n!=\prod_{i=1}^{n}i=n\times(n-1)\times...\times1$$
特殊地
$$0!=1$$
（为了防止 $\frac{1}{0}$ 的出现）  
上下约个分就发现是对的，我们称其为“排列”，记为
$$\text{A}_{n}^{m}=\frac{n!}{(n-m)!}$$
其中 $m=n$ 时答案为 $n!$，即 $n$ 个数的全排列个数。  

考虑 $n$ 个不同数中选 $m$ 个**组成一个集合**一共有多少种方法，首先依然像排列一样考虑每个位置有几种选法，得
$$\frac{n!}{(n-m)!}$$
此时因为集合有无序性，考虑重复的集合。因为现在是把集合当做排列来考虑，也就是说每种选法选了一个全排列，也就是 $m!$ 种，因此最终得到方法数为
$$\frac{n!}{(n-m)!\ m!}$$
记为
$$\text{C}_{n}^m=\text{C}(n,m)=\binom{n}{m}=\frac{n!}{(n-m)!\ m!}$$

---
回到这道题，$k$ 个不同位置可以看做将序列分成了 $k+1$ 段颜色相同的序列，考虑隔板法，也就是在 $n-1$ 个位置里放 $k$ 块板，共
$$\binom{n-1}{k}$$
种方法。接下来考虑每块的颜色，发现可以重复，但是要保证相邻块的颜色不同，第一块显然可以选 $m$ 种，第二块和第一块不同，于是为 $m-1$ 种，以此类推后面均为 $m-1$ 种。整个序列共 $k+1$ 块，所以答案为
$$\binom{n-1}{k}\times m\times (m-1)^k$$

---

## 作者：k2saki (赞：0)

组合水题。

其中“恰有 k 块颜色与其左边的那块砖不同”就代表把序列分成 k+1 段，每一段颜色都一样，方案数是$C_{n-1}^k$（用插板法可以得出，n-1 个空隙 插 k 个板子）。

然后考虑对 k+1 段染色。第一段显然是 m 种颜色，然后剩下的 k 段由于不能和前一段一样，只有 m-1 种颜色，所以方案数是 $m*(m-1)^k$

总方案是 $C_{n-1}^k*m*(m-1)^k$

---

