# [ABC127E] Cell Distance

## 题目描述

有一个 $n \times m$ 的矩形，你会从中选出 $k$ 个坐标为整数的位置 $(x_1,y_1),(x_2,y_2)\dots(x_{k},y_{k})$ 。

你定义一个选出 $k$ 个位置的方案的权值为$\textstyle \sum_{i=1}^{k-1}\sum_{j=i+1}^{k}(|x_{i}-x_{j}|+|y_{i}-y_{j}|)$

你需要求出，所有可能的选出 $k$ 个位置的方案的权值之和，答案对 $1000000007$ 取模

## 说明/提示

$2 \le k \le n \times m \le 200000$

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
8```

## 样例 #2

### 输入

```
4 5 4```

### 输出

```
87210```

## 样例 #3

### 输入

```
100 100 5000```

### 输出

```
817260251```

# 题解

## 作者：_lyx111 (赞：13)

# [ABC127E] Cell Distance

[link](https://atcoder.jp/contests/abc127/tasks/abc127_e)

## 分析

转换一下，先考虑 $x$ 坐标的贡献。

考虑两个点间 $x$ 坐标相差为 $d\ ( 1\le d\le n-1)$ 时的贡献（ $d=0$ 的时候没有贡献所以这里不考虑）。设这两个点的坐标为 $(x_1,y_1),(x_2,y_2)$，那么就有 $x_1-x_2=d,1\le x_1,x_2\le n,1\le y_1,y_2\le m$。

则可行的 $x_1,x_2$ 有 $n-d$ 对（$(1,d+1),(2,d+2),\cdots,(n-d,n)$），$y_1,y_2$ 各有 $m$ 种取法。所以像这样的点对共有 $(n-d)\times m^2$ 对，每一对的贡献为 $d$，总的贡献就是 $d\times (n-d)\times m^2$。

每一个点对出现在选出的 $k$ 个点中的方案数共有 $C_{n\times m-2}^{k-2}$ （除去这两个点之外，剩下 $n\times m-2$ 个点中，选出 $k-2$ 个点，与这两个点组成要选出的 $k$ 个点），那么总的贡献就是 $d\times (n-d)\times m^2 \times C_{n\times m-2}^{k-2}$。

同理可以计算 $y$ 坐标的贡献，得到最终答案为：

$$(\sum_{d=1}^{n-1} d\times (n-d)\times m^2+\sum_{d=1}^{m-1} d\times (m-d)\times n^2)\times C_{n\times m-2}^{k-2}$$

那么就做完了。

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,k;
int ans;
int ksm(int u,int v)
{
	int res=1;
	while(v)
	{
		if(v&1) res=1ll*res*u%mod;
		u=1ll*u*u%mod; v>>=1;
	}
	return res;
}
int C(int p,int q)
{
	int s=1,t=1; //s：分子，t：分母 
	for(int i=p;i>=p-q+1;i--)
		s=1ll*s*i%mod;
	for(int i=1;i<=q;i++)
		t=1ll*t*i%mod;
	return 1ll*s*ksm(t,mod-2)%mod;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int d=1;d<n;d++)
		ans=(ans+1ll*d*(n-d)%mod*m%mod*m%mod)%mod;
	for(int d=1;d<m;d++)
		ans=(ans+1ll*d*(m-d)%mod*n%mod*n%mod)%mod;
	ans=1ll*ans*C(n*m-2,k-2)%mod;
	printf("%d\n",ans);
	return 0;
}
~~~

[AC记录](https://atcoder.jp/contests/abc127/submissions/37918668)

## 写在最后

蒟蒻很菜，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：qwerty12346 (赞：6)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc127_e)

## 题意

求出所有可能的选出 $k$ 个位置的方案的权值之和，答案对 $1000000007$ 取模。

## 思路

考虑两个之间行距为 $i$ 都可以随便选择一列，从 $n-i$ 个行距为 $i$ 的行组合中挑选一个，然后再选择剩余的 $k-2$ 个，那么可以推出方案数为 $i×(n-i)×m×m$ 再乘一个 $nm-2$ 和 $k-2$ 的排列组合就行了。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
const long long M=1000000007;
long long n,m,k,ret;
long long a(long long x,long long y){
    long long ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%M;
	x=x*x%M;
        y>>=1;
    }
    return ret;
}
long long b(long long x,long long y){//排列组合
    long long sum=1,num=1;
    for(int i=x;i>=x-y+1;i--)sum=sum*i%M;
    for(int i=1;i<=y;i++)num=num*i%M;
    return sum*a(num,M-2)%M;
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<n;i++)ret=(ret+i*(n-i)%M*m%M*m%M)%M;//套公式
    for(int i=1;i<m;i++)ret=(ret+i*(m-i)%M*n%M*n%M)%M;//套公式
    ret=ret*b(n*m-2,k-2)%M;//在乘上nm-2和k-2的排列组合
    cout<<ret<<endl;
    return 0;
}
```

---

## 作者：Disjoint_cat (赞：3)

# [ABC127E](https://www.luogu.com.cn/problem/AT_abc127_e) [Cell Distance](https://atcoder.jp/contests/abc127/tasks/abc127_e)

## 题意

有一个 $n\times m$ 的网格，在里面随机撒 $k$ 个点，求所有撒点方式中两两曼哈顿距离的和。答案模 $10^9+7$。

Data range：$k\le n\times m\le2\times10^5$。

Bonus data range：$n,m\le10^9$，$k\le5\times10^7$。

## 题解

### 原题

首先，我们发现每**对**点同时出现的次数是相同的。

只要钦定这两个点被选，则易得它们同时被选中的方案数是

$$\binom{nm-2}{k-2}.$$

那就只要统计每两个点的距离和，再乘上这个系数即可。

直接枚举是 $\Theta(n^2m^2)$ 的，肯定不行。

我们发现行和列可以分开考虑。

我们考虑横向距离为 $i(i>0)$ 的点对个数，就可以得到横向距离的和。

因为距离为 $i$ 的列有 $n-i$ 对，而每列有 $m$ 个点，所以横向距离的和为

$$\sum_{i=1}^{n-1}i\cdot(n-i)\cdot m^2.$$

纵向距离同理计算即可。时间复杂度为 $\Theta(nm)$，瓶颈在于计算二项式系数。

### Bonus 题

我们注意到二项式系数只需计算一次，所以没必要预处理阶乘。

根据 $\dbinom xy=\dfrac{\prod_{i=x-y+1}^xi}{y!}$，我们就可以把这部分优化到 $\Theta(k)$。

所以总时间复杂度降到了 $\Theta(n+m+k)$。

继续优化，我们化简距离和的柿子：

$$\begin{aligned}&\sum_{i=1}^{n-1}i\cdot(n-i)\cdot m^2\\= \ &m^2\sum_{i=1}^{n-1}(ni-i^2)\\=\ &m^2\left(n\sum_{i=1}^{n-1}i-\sum_{i=1}^{n-1}i^2\right)\\=\ &m^2\left(\dfrac{n^2(n-1)}2-\dfrac{n(n-1)(2n-1)}6\right)\end{aligned}$$

到此这个柿子已经可以 $\Theta(1)$ 计算了，~~但是为了代码美观~~，还可以继续简化，最后变成这个样子：

$$\frac{m^2(n^3-n)}6.$$

于是这部分的时间复杂度降到 $\Theta(1)$，总时间复杂度 $\Theta(k)$。

代码不给了，对着柿子写就行了。

---

## 作者：high_sky (赞：3)

## 题解
我们先从小的开始，即从 $2$ 个点开始考虑：那么两个点之间 $x$ 的贡献就是 $| x_1-x_2 |$，设 $d$ 为这个数，那么每行就有 $(n-d)$ 个，也就是整个图有 $(n-d) \times m^2$ 个，贡献也就是 $(n-d)\times m^2\times d$ 个；两个点之间 $y$ 的贡献就是 $|y_1-y_2|$，也是设这个数为 $d$，那么每列就有 $(m-d)$ 个，整个图就有 $(m-d) \times n^2$ 个，贡献也就是 $(m-d)\times n^2\times d$。

求出了两个点的对整个图的贡献，就下来就要考虑重复的情况了，即：
$C_{n\times m-2}^{k-2}$

后面求出来这个数就可以直接乘上它就能求出贡献！

但是，又有一个问题：除数太大了！！！这时候逆元就登场了！
## 逆元
取模的规律如下：
- $(a+b)\bmod p=(a\bmod p+b\bmod p)\bmod p$
- $(a-b)\bmod p=(a\bmod p-b\bmod p)\bmod p$
- $(a\times b)\bmod p=(a\bmod p\times b\bmod p)\bmod p$

那么除法怎么办呢？

这时要想到他的逆元了：

根据费马小定理，可得出：
$\frac{a}{b}\bmod{p}=(a\times b^{p-2})\bmod{p}$。

所以在逆元下，用个快速幂就能轻松搞定这一个题。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1000000007;
ll n,m,k,ans=0;
ll qpow(ll a,ll b){
	ll sum = 1;
	while(b){
		if(b & 1) sum = (sum * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	} 
	return sum % mod;
}
ll C(ll a,ll b){//C(n,m)=C(n*m-2,k-2)
	if(a==b||b==0) return 1;
	if(a<b) return 0;
	ll fz=1;
	for(ll i=1;i<=a;i++)fz*=i,fz%=mod;
	ll fm=1;
	for(ll i=1;i<=b;i++)fm*=i,fm%=mod;
	ll other=1;
	for(ll i=1;i<=a-b;i++)other*=i,other%=mod;
	fm=(fm*other)%mod;
	fm=qpow(fm,mod-2)%mod;
	return (fz*fm)%mod;
}
int main(){//
	cin>>n>>m>>k;
	for(ll i=1;i<n;i++)
		ans += ((n-i)*i*m*m)%mod;
	for(ll j=1;j<m;j++)
		ans += ((m-j)*j*n*n)%mod;
	ans %= mod;
	ans=(ans*C(n*m-2,k-2))%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Sexy_Foxy (赞：2)

## 题意：

给你一个 $n \times m$ 大小的矩阵，定义一个选出$k$个位置的方案的权值为     $\textstyle \sum_{i=1}^{k-1}\sum_{j=i+1}^{k}(|x_{i}-x_{j}|+|y_{i}-y_{j}|)$ ，问你从里面选出所有可能的 $k$ 个位置的方案的权值之和，答案对 $1000000007$ 取模。

## 解题思路：

首先，不要被 $\bmod1000000007$ 所迷惑，这题不是地推。但是一看这$\bmod       1000000007$ 就知道这题肯定不能暴力，那怎么办呢？（~~我真是废话连篇啊~~）我们可以把这道题当作一道数学题来解。

### 第一步：

我们不妨先选定两个点，看它们对答案的贡献有多少，然后求这 $k$ 个点的所有组合，在乘这个贡献值，就能求出答案。那么第一步完成。

### 第二步：

但这两个点对答案的贡献有多少呢？难不成要暴力吗？恭喜你，答对了。首先，看它们对每一列的贡献有多少，考虑它们之间的行的距离为 $i$ ，那么行距为 $i$ 的那一列上的点都可以随便选，所以可以推出以下代码：

```
int sum=0;
for(int i=1;i<=n;i++)
{
	sum+=(n-i)*i*m*m;
}
```
而这个 $sum$ 就是这两个点的列对答案的贡献。

而行也是同理：

```
for(int i=1;i<=m;i++)
{
	sum+=(m-i)*i*n*n;
}
```
最后的 $sum$ 值就是两个点对于答案的贡献。

但求出来 $sum$ 的值后怎么办？我们知道一共能选 $n \times m$ 个点，一共要选 $k$ 个点，但是已经选择了两个点，所以还要综上所述，我们要求的答案就是：

## $sum \times C_{n \times m-2}^{k-2}$

### 第三步：

接下来就是代码实现：

#### 定义部分：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1000000000+7;
ll n,m,k,ans;
//没有什么好讲的......

```

#### 输入+求 $sum$ 值：

```
scanf("%lld%lld%lld",&n,&m,&k);
ll sum=0;
for(int i=1;i<=n;i++) //对每一列对答案的贡献
{
	sum+=(n-i)*i*m*m;
	sum%=mod;
}
for(int i=1;i<=m;i++) //对每一行对答案的贡献
{
	sum+=(m-i)*i*n*n;
	sum%=mod;
}
```

#### 全排列：

```
ll qpow(ll a,ll b) //快速幂（用于处理逆元）
{
	ll sum=1;
	while(b)
	{
		if(b&1)
		{
			sum=(sum*a)%mod;
		}
		a=(a*a)%mod;
		b>>=1;
	}
	return sum;
}
ll A(ll n,ll m) //求组合数
{
	ll ns=1;
	for(int i=1;i<=n;i++)
	{
		ns*=i;
		ns%=mod;
	}
	ll ms=1;
	for(int i=1;i<=(n-m);i++)
	{
		ms*=i;
		ms%=mod;
	}
	return ((ns%mod)*(qpow(ms,mod-2)%mod))%mod; //里面运用了费马小定理，不懂得可以去查一查
}
ll C(ll n,ll m) //求组合
{
	if(n<m)
	{
		return 0;
	}
	if(n==m)
	{
		return 1;
	}
	ll sum=1;
	for(int i=1;i<=m;i++)
	{
		sum*=i;
		sum%=mod;
	}
	return ((A(n,m)%mod)*(qpow(sum,mod-2)%mod))%mod;
}
```

#### 输出答案：

```
ans=(sum*C(n*m-2,k-2))%mod; //如第二步的
printf("%lld",ans%mod);
return 0; //完美结束
```

## 完整的Code

接下来是不加注释的完整代码（~~知道你们就是冲着这个来的~~）：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1000000000+7;
ll n,m,k,ans;
ll qpow(ll a,ll b)
{
	ll sum=1;
	while(b)
	{
		if(b&1)
		{
			sum=(sum*a)%mod;
		}
		a=(a*a)%mod;
		b>>=1;
	}
	return sum;
}
ll A(ll n,ll m)
{
	ll ns=1;
	for(int i=1;i<=n;i++)
	{
		ns*=i;
		ns%=mod;
	}
	ll ms=1;
	for(int i=1;i<=(n-m);i++)
	{
		ms*=i;
		ms%=mod;
	}
	return ((ns%mod)*(qpow(ms,mod-2)%mod))%mod;
}
ll C(ll n,ll m)
{
	if(n<m)
	{
		return 0;
	}
	if(n==m)
	{
		return 1;
	}
	ll sum=1;
	for(int i=1;i<=m;i++)
	{
		sum*=i;
		sum%=mod;
	}
	return ((A(n,m)%mod)*(qpow(sum,mod-2)%mod))%mod;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	ll sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=(n-i)*i*m*m;
		sum%=mod;
	}
	for(int i=1;i<=m;i++)
	{
		sum+=(m-i)*i*n*n;
		sum%=mod;
	}
	ans=(sum*C(n*m-2,k-2))%mod;
	printf("%lld",ans%mod);
	return 0;
}
```

## 后记：

写了这篇题解以后，一看时间发现已经5点多了，发个题解可真难啊！！！

#### qwq

---

## 作者：daniEl_lElE (赞：2)

## 思路

转化一下，分离行列，针对**每一对**去计算方案。

以下以行为例子。

考虑两个之间行距为 $i$，都可以随便选择一列，从 $n-i$ 个行距为 $i$ 的行组合中挑选一个，然后再选择剩余 $k-2$ 个，方案数就是 $i\times (n-i)\times m^2\times \dbinom{nm-2}{k-2}$。

加起来即可，复杂度 $O(n+m)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
signed main(){
	init();
	int n,m,k,ans=0;
	cin>>n>>m>>k;
	for(int i=1;i<n;i++){
		ans=(ans+(i*m%mod)*((n-i)*m%mod)%mod*C(n*m-2,k-2)%mod)%mod;
	}
	for(int i=1;i<m;i++){
		ans=(ans+(i*n%mod)*((m-i)*n%mod)%mod*C(n*m-2,k-2)%mod)%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZnPdCo (赞：1)

首先考虑最朴素做法，每次取出 $k$ 个点，然后暴力计算。

时间复杂度：$O({(nm)}^{k})$。

---

考虑优化，发现每一对点（两个点）的权值会被重复计算很多遍。一对点重复计算的个数为选择的 $k$ 个点中包含这一对点的情况数（废话），即 $C_{nm}^{k}$ 中包含这一对点的个数。

如何计算这个值？可以假设已经选择这一对点，那么还需要在剩下 $nm-2$ 个点中选择 $k-2$ 个点，即 $C_{nm-2}^{k-2}$ 遍。

那么我们可以设计出一个 $O({(nm)}^2)$ 的做法，枚举一对点，计算出权值，然后乘以 $C_{nm-2}^{k-2}$ 的和。

---

把公式拆开，单独计算 $x$ 和 $y$。以 $x$ 为例，发现当 $i$ 固定时，某一行的权值为 $1+2+3+\cdots+(n-i)$，因为 $j$ 不固定，一对点的第一个点可以取 $m$ 列中任何一列，第二个点也可以取 $m$ 列中任意一列。所以最终权值和为等差数列之和乘以 $m^2$。时间复杂度 $O(n+m)$。

关键代码：

```c++
ll calc(ll x) {
	return (x+1)*x/2;
}
void solve() {
	scanf("%lld %lld %lld", &n, &m, &k);
	for(ll i = 1; i <= n; i++) {
		(ans1 += m*m*calc(n-i)) %= P;
	}
	(ans1 *= C(k-2, n*m-2)) %= P;
	for(ll i = 1; i <= m; i++) {
		(ans2 += n*n*calc(m-i)) %= P;
	}
	(ans2 *= C(k-2, n*m-2)) %= P;
	printf("%lld", (ans1+ans2)%P);
}
```

---

## 作者：joe_zxq (赞：1)

# 思路分析

假设两个点的 $x$ 坐标相差 $i$，即 $x_2-x_1=i$。此时，$x_1,x_2$ 有 $n-i$ 种选法，即 $(1,i+1),(2,i+2),\dots,(n-i,n)$，$y1,y2$ 可以任意选择，有 $m^2$ 种选法。

除了这两个点以外，其他 $k-2$ 个点要从剩下的 $n \times m-2$ 个点中选择，即有 $C_{n \times m-2}^{k-2}$ 种选法。

因此从 $x$ 坐标的贡献考虑，一共是 $(\sum\limits_{i=1}^{n-1}{i \times (n-i) \times m^2}) \times C_{n \times m-2}^{k-2}$。

同理从 $y$ 坐标的贡献考虑，一共是 $(\sum\limits_{i=1}^{m-1}{i \times (m-i) \times n^2}) \times C_{n \times m-2}^{k-2}$。

加起来答案为 $(\sum\limits_{i=1}^{m-1}{i \times (m-i) \times n^2} + \sum\limits_{i=1}^{m-1}{i \times (m-i) \times n^2}) \times C_{n \times m-2}^{k-2}$。

# 代码实现

注意，求 $\frac{s}{t} \bmod m$ 时可以使用费马小定理，即 $\frac{s}{t} \equiv s \times t^{-1} \pmod m$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll mod=1e9+7;
ll quickpow(ll a,ll b){
	if(b==0)return 1;
	if(b==1)return a;
	ll ans=quickpow(a,b/2)%mod;
	if(b%2)return ans%mod*ans%mod*a%mod;
	else return ans%mod*ans%mod;
}
ll C(ll a,ll b){
	ll up=1,down=1;
	for(ll i=a;i>=a-b+1;i--) up=up*i%mod;
	for(ll i=1;i<=b;i++) down=down*i%mod;
	return up*quickpow(down,mod-2)%mod;
}
int main(){
	ll n,m,k,ans=0; cin>>n>>m>>k;
	for(ll i=1;i<n;i++) ans=(ans+i*(n-i)%mod*m%mod*m%mod)%mod;
	for(ll i=1;i<m;i++) ans=(ans+i*(m-i)%mod*n%mod*n%mod)%mod;
	cout<<ans*C(n*m-2,k-2)%mod;
	return 0;
}
```



---

## 作者：Populus_euphratica (赞：1)

## 分析
首先这是一个平面，直接在平面上做的话太麻烦了，所以我们可以一个平面图拆成两列，一列是横轴，一列是竖轴。然后我们可以惊奇的发现，这两列是对称的，所以我们只用处理一个，另一个直接照搬就可以了。

而在一列上，我们统计贡献时，可以先算出两个点的贡献，然后在计算出这一段在多少种方案里面有贡献。所以，我们就可以枚举两个点之间的距离 $d$，由于这两个端点可以移动，所以还要乘上 $(n-d)$，而且因为这只是一列，所以我们还要分别乘上m，也就是一起 $m^2$。又因为有 $k$ 个位置，并且是无序的，所以再乘上 $C^k_{mn}$。接着，再处理一下 $m$（与 $n$ 的处理方法一样），然后把所有的加起来。

也就是：
$$ 
sum= \sum_{d = 1}^{n}(n-d)m^2C^k_{mn}
$$
最后，因为在 $C^k_{mn}$ 中有除法，所以在取模的时候要加上一个逆元。\
附图一张:![](https://cdn.luogu.com.cn/upload/image_hosting/5t3bnjil.png)




---

## 作者：OrangeEye (赞：0)

考虑每一对点的贡献。对于一对点 $(X_1,Y_1)$ 和 $(X_2,Y_2)$，考虑计算这一对点在多少种方案中产生了贡献，即在多少种方案中同时取了这两个点。容易想到，在 $k$ 个点中除了这两个点以外的其他 $k-2$ 个点都可以任意取，所以这两个点在 $C^{k-2}_{nm-2}$ 中被计算过。所以我们就要计算：
$$\sum^{(x_1,y_1)}\sum^{(x_2,y_2)}(|x_2-x_1|-|y_2-y_1|)\times C^{k-2}_{nm-2}$$
而如果枚举所有点对，则复杂度为 $O((nm)^2)$，无法通过。所以需要对于每一个点 $O(1)$ 计算到其他所有点的距离之和。此时可以将横向和纵向的距离分开来考虑。由于横向（或纵向）和当前点距离为 $k$ 的点的个数是确定的，只需要用等差数列求和公式相加就可以了。

注意不要算重点对。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
int n,m,k;
int fct[200009],divfct[200009];
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%mod;
		a=(a*a)%mod;
		b/=2;
	}
	return ans;
}
void init(){
	fct[0]=1;
	for(int i=1;i<=200000;i++)fct[i]=(fct[i-1]*i)%mod;
	divfct[200000]=qpow(fct[200000],mod-2);
	for(int i=200000-1;i>=0;i--)divfct[i]=(divfct[i+1]*(i+1))%mod;
}
int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	if(x==y||y==0)return 1;
	else return fct[x]*divfct[x-y]%mod*divfct[y]%mod;
}
int sf(int x){return (x*(x+1)%mod*qpow(2,mod-2)%mod);}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	init();
	cin>>n>>m>>k;
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			(ans+=sf(i-1)*j%mod+sf(n-i)*(j-1)%mod+n*sf(j-1)%mod)%=mod;//计算到已经枚举过的点之间的距离，防止算重
	cout<<ans*C(n*m-2,k-2)%mod<<endl;
	return 0;
}
```

---

## 作者：Purslane (赞：0)

## Solution

运用几个经典 trick 即可 .

- 忽略其他

我们研究问题 , 总是越少越好研究 . 比如这题 , 让我们直接研究 $n$ 个数未免过于麻烦 , 那我们把每一对給拆开 . 所以我们其实就是研究很多二元数对的和 . 注意一个二元数对会给答案贡献 $C_{nm-2}^{k-2}$ 次 , 所以注意乘上系数 .

- 省去一维

二元的东西也比较麻烦 , 可能无法直接全部求出 . 这时候我们应枚举一维 , 然后快速计算第二维 .

对于这一题  , 我们给了一个格子 $(x_1,y_1)$ , 需要快速求出它到其他格子的距离总和 . 额 , 如果直接求距离和 , 有点困难 . 于是用第三个 trick

- 分开考虑

刚才那个距离和由于是纵向与横向的加 , 不是很有规律 , 所以我们考虑把纵向距离和横向距离分开计算 . 这样 , 单独考虑一维的时候 , 这个点到其他点的距离都是一行一行或一列一列全部相等的 , 可使用等差数列 .

- 除序

欸等等 , 怎么样例 1 输出 16 啊 ! 因为我们一对数正反都计算了一次 , 这时候我们要除序 . 

一般除序的时候 , 要考虑自己对自己其实只有一次 , 不能直接除以 $2$ . 不过这道题自己对自己是 $0$ , 所以直接除以 $2$ 也没问题 .

所以就做完了 ?

code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10,MOD=1e9+7;
int n,m,k;
int get_sum(int u,int v) {
	if(v==0) return 0;
	int x=u+v,y=v-u+1;
	if(x%2==0) x/=2;else y/=2;
	return x*y%MOD;
}
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans*=base,ans%=MOD;
		base*=base,base%=MOD,p>>=1;
	}
	return ans;
}
int fuc(int u) {
	int ans=1;ffor(i,1,u) ans*=i,ans%=MOD;
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	int ans=0;
	ffor(i,1,n) ffor(j,1,m) {
		int tot1=get_sum(1,i-1)+get_sum(1,n-i),tot2=get_sum(1,j-1)+get_sum(1,m-j);
		tot1%=MOD,tot2%=MOD;
		ans+=tot1*m%MOD,ans+=tot2*n%MOD;ans%=MOD;
	}
	cout<<ans*fuc(n*m-2)%MOD*qpow(fuc(n*m-k),MOD-2)%MOD*qpow(fuc(k-2),MOD-2)%MOD*qpow(2,MOD-2)%MOD;
	return 0;
}
```

---

## 作者：Acfboy (赞：0)

简单推柿子题，还没有题解就来交一发。

首先分开考虑每对的贡献，最后答案乘一个 $n\times m-2 \choose k-2$ 就可以了。

为了避免重复，我们可以规定一个方向，比如说向右下方，但是这样左下和右上的贡献就没有考虑到了，不过由于形式是相同的，所以在转过来跑一遍就可以了。   
这里只考虑右下。

令 $n = N-x+1, m = M-y$，点 $(x, y)$ 和后每所有点的曼哈顿距离和是

$$
\sum_{i=0}^{n-1} \sum_{j=i}^{m+i}j
$$

等差数列求和得

$$
\text{原式}=\frac{1}{2} \sum_{i=0}^{n-1} 2im + 2i + m^2 + m
$$

拆开


$$
= m\sum_{i=0}^{n-i} i + \sum_{i=0}^{n-1}i + \frac{1}{2} n (m^2+m)
$$

然后发现这里面的和式都可以用等差数列求和代替。  
基本上就做完了。

注意为了避免重复计算左下和右上贡献的时候要把当前行列都减掉。

代码。

```cpp
void add(int &a, int b) { a = (a + b) % P; }
int get(int n, int m) {
    if (n <= 0 || m < 0) return 0;
    int sum = (0+n-1) * n / 2 % P;
    return ((sum*m%P + sum)%P + n*(m*m+m)/2%P) % P; 
}
int fix(int a, int b) {
    int an1 = (1+a) * a / 2 % P;
    int an2 = (1+b) * b / 2 % P;
    return (an1 + an2) % P;
}
signed main() {
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++)
            add(ans, (get(n-i+1, m-j) + get(i, m-j) - fix(i-1, m-j)) % P);
    ans = ans * C(n*m-2, k-2) % P;
    std::cout << ans;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc127_e)

我非常害怕，好像只有我用了范德蒙德卷积。

## 思路

首先考虑把这个 $\large \sum \sum$ $|x_i-x_j|+|y_i-y_j|$ 拆开来，变成 $\large \sum \sum$ $|x_i-x_j|+$ $\large \sum \sum$ $|y_i-y_j|$。

这两个 $\large \sum \sum$ 实际上是等价的，我们做完第一个 $\large \sum \sum$ 后把 $n,m$ 交换一下就可以得到第二个 $\large \sum \sum$。

然后考虑拆绝对值，容易发现若 $x_i>x_j$，那么 $|x_i-x_j|=x_i-x_j$，否则 $|x_i-x_j|=x_j-x_i$，然后分离贡献，发现 $x_i$ 的贡献就是数列中 $< x_i$ 的数的个数减去 $>x_i$ 的数的个数（相等反正是 $0$，不考虑）。

然后考虑如何计数这个东西。

我们枚举一个横坐标 $i$，然后枚举一个 $j$，表示这个横坐标 $j$ 选了几个，如果我们可以 $\mathcal O(1)$ 计算它的贡献，那么就过了。

考虑列出此贡献的柿子：枚举我们选了 $p$ 个横坐标 $<i$ 的点，那么我们选了 $q=k-p-j$ 个横坐标 $>i$ 的点。

设 $s=(i-1) \times m$，$t=(n-i) \times m$。那么我们选出 $p$ 个点和 $q$ 个点的方案数就是 $\dbinom{s}{p} \times \dbinom{t}{q}$。

然后考虑当前横坐标的贡献，前面有 $p$ 个比它小的，后面有 $q$ 个比它大的，贡献就是 $p-q$，然后乘上当前横坐标 $i$，乘横坐标个数 $j$，所以最终我们要求的柿子就是 $\large \sum$ $\dbinom{s}{p} \times \dbinom{t}{q} \times i \times j \times (p-q)$。

把 $q=k-p-j$ 带入，得到：

$$\dbinom{s}{p} \times \dbinom{t}{q} \times i \times j \times (2 \times p-k-j)$$

$$=\dbinom{s}{p} \times \dbinom{t}{q} \times i \times j \times (-k-j) + \dbinom{s}{p} \times \dbinom{t}{q} \times 2 \times p$$

注意到左边这一项实际上是 $\large \sum$ $\dbinom{s}{p} \times \dbinom{t}{q}$ 乘一个常数的形式，所以左边求和，范德蒙德卷积一下就是 $\dbinom{s+t}{p+q}$ 乘一个常数。

考虑右边 $\large \sum $ $\dbinom{s}{p} \times \dbinom{t}{q} \times 2 \times p$，怎么做。

首先把 $2$ 提出，变成 $\large \sum $ $\dbinom{s}{p} \times \dbinom{t}{q} \times p$，考虑它的组合意义：在 $s+t$ 个数里选出 $p+q$ 个数，然后再从前 $p$ 个数里选出一个特殊点。

而它的组合意义等价于这个柿子：$\dbinom{s+t-1}{p+q-1} \times p$。

所以也可以 $\mathcal O(1)$ 算出来，这题就解决了，时间复杂度 $\mathcal O(nm)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int const mod=1e9+7;
int fac[N],inv[N];
int qpow(int a,int b){int res=1;while (b){if (b&1) res*=a,res%=mod;a*=a,a%=mod,b>>=1;}return res;}
int C(int n,int m){
    if (n<m) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m,k;cin>>n>>m>>k;
    fac[0]=1;
    for (int i=1;i<N;++i) fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    for (int i=N-2;~i;--i) inv[i]=inv[i+1]*(i+1)%mod;
    int ans=0;
    for (int i=1;i<=n;++i){
        for (int j=1;j<=min(m,k);++j){
            //计算 i 选 j 个的贡献
            int res=0;
            int p=(i-1)*m,q=(n-i)*m,s=k-j;
            res=C(p+q-1,s-1)*p%mod;
            res*=2,res%=mod;
            res+=(j-k)*C(p+q,s)%mod;
            res*=(i*j)%mod,res%=mod;
            res*=C(m,j),res%=mod;
            ans+=res,ans%=mod;
        }
    }
    swap(n,m);
    for (int i=1;i<=n;++i){
        for (int j=1;j<=min(k,m);++j){
            //计算 i 选 j 个的贡献
            int res=0;
            int p=(i-1)*m,q=(n-i)*m,s=k-j;
            res=C(p+q-1,s-1)*p%mod;
            res*=2,res%=mod;
            res+=(j-k)*C(p+q,s)%mod;
            res*=(i*j)%mod,res%=mod;
            res*=C(m,j),res%=mod;
            ans+=res,ans%=mod;
        }
    }
    cout<<(ans+mod)%mod<<'\n';
    return 0;
}
```

---

