# Expected Median

## 题目描述

Arul 有一个长度为 $n$ 的二进制数组 $a$。

他将取出该数组所有长度为 $k$（$k$ 为奇数）的子序列，并找到它们的中位数。

所有这些中位数的值之和是多少？

由于这个和可能非常大，请输出它对 $10^9 + 7$ 取模的结果。换句话说，输出这个和除以 $10^9 + 7$ 的余数。

一个二进制数组是仅由 $0$ 和 $1$ 组成的数组。

数组 $b$ 是数组 $a$ 的子序列，如果 $b$ 可以通过从 $a$ 中删除若干（可能为零或全部）元素得到。子序列不要求连续。

长度为奇数 $k$ 的数组的中位数是将其排序后第 $\frac{k+1}{2}$ 个元素。

## 说明/提示

在第一个测试用例中，$[1,0,0,1]$ 的所有长度为 $k=3$ 的子序列有四个：

- $[1,0,0]$：中位数 $=0$。
- $[1,0,1]$：中位数 $=1$。
- $[1,0,1]$：中位数 $=1$。
- $[0,0,1]$：中位数 $=0$。

结果之和为 $0+1+1+0=2$。在第二个测试用例中，所有长度为 $1$ 的子序列的中位数都是 $1$，所以答案是 $5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
2
5
0
16
4
7
0
333606206```

# 题解

## 作者：aeiouaoeiu (赞：6)

题目要求的实际上就是有至少 $m=\frac{k+1}{2}$ 个 $1$ 的，长度为 $k$ 的 $a$ 的子序列数量。

我们把至少 $m$ 个转化为恰好 $i$ 个，其中 $m\le i\le k$。

如何求恰好 $i$ 个？设 $a$ 中 $1$ 数量为 $c$，我们要从这 $c$ 个 $1$ 中取出 $i$ 个，从 $n-c$ 个 $0$ 中 取出 $k-i$ 个。方案数为 $\dbinom{c}{i}\dbinom{n-c}{k-i}$。

求和，答案为：$\displaystyle{\sum_{i=m}^k{\dbinom{c}{i}\dbinom{n-c}{k-i}}}$。时间复杂度 $\mathcal{O}(n+k)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
#define mkt make_tuple
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1000000000000000007ll,p=1e9+7;
ll n,k,a[maxn],frac[maxn],inv[maxn],ans,m,cnt,bas[maxn],sum;
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
ll C(ll a,ll b){return (a<b||b<0)?0:frac[a]*inv[b]%p*inv[a-b]%p;}
signed main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	frac[0]=1;
	for(int i=1;i<maxn;i++) frac[i]=frac[i-1]*i%p;
	inv[maxn-1]=qpow(frac[maxn-1],p-2);
	for(int i=maxn-1;i>=1;i--) inv[i-1]=inv[i]*i%p;
	ll T=1;
	cin>>T;
	for(;T--;){
		cin>>n>>k; ans=cnt=sum=0,m=(k+1)/2;
		for(int i=1;i<=n;i++) cin>>a[i],cnt+=a[i];
		for(int i=m;i<=k;i++) ans=(ans+C(cnt,i)*C(n-cnt,k-i)%p)%p;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：5)

# CF1999F Expected Median 题解

[Luogu Link](https://www.luogu.com.cn/problem/CF1999F)|[CF Link](https://codeforces.com/contest/1999/problem/F)|[My AC submission](https://codeforces.com/contest/1999/submission/274911994)。

数学题。

### 解析

由于是 $01$ 串，所以中位数一定是 $0$ 或 $1$，又只有 $1$ 会对答案产生贡献，所以我们只需要把数列里的 $1$ 找出来即可。

读入的时候统计有多少个 $1$，记为 $c$，定义 $m=\left \lceil \frac{k}{2}  \right \rceil $。

所以答案就是 $\sum_{i=m}^{\min (k,c)}  \binom{i}{c}\binom{k-i}{n-c}$。

解读一下，这个大 $\sum$ 指我可以在所有的 $c$ 个 $1$ 里面选 $k,k+1,\dots,\min(k,c)$ 个。接下来的组合数是选 $1$ 的情况数和这个区间中选 $0$ 的情况数，并将其求积就行。

又由于公式 $\binom{m}{n}=\frac{n!}{m!\times (n-m)!}$，我们用乘法逆元就可以解决了。同时，我们还需要预处理一个阶乘数组。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=1e9+7;
int T;
int n,k,cnt;
bool a[N];
int ksm(int a,int b){ //快速幂求逆元
	int ans=1;
	while(b){
		if(b&1){ 
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
return ans%mod;
}
int f[N],ans;
int C(int n,int m){
	if(n<m){
		return 0;
	}
return f[n]*ksm(f[m],mod-2)%mod*ksm(f[n-m],mod-2)%mod; //乘法逆元
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	f[0]=1;
	for(int i=1;i<=2e5;i++){
		f[i]=f[i-1]*i%mod; //预处理阶乘数组
	}
	while(T--){
		cin>>n>>k;
		ans=cnt=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]){
				cnt++;
			}
		}
		int m=k+1>>1;
		for(int i=m;i<=min(k,cnt);i++){
			ans+=C(cnt,i)*C(n-cnt,k-i)%mod; ans%=mod; //不要忘了 0 的情况
		}
		cout<<ans<<"\n";
	}
return 0;
}
```

---

## 作者：cjh20090318 (赞：4)

如果把 $01$ 序列改为正整数序列，此题该如何应对。

## 题意

给定一个长度为 $n$ 的 $01$ 序列，求所有长度为 $k$ 的**子序列**的**中位数**之和（$k$ 为奇数），答案对 $10^9 + 7$ 取模。

## 分析

因为 $01$ 序列只含两个数，且只有中位数为 $1$ 的情况会对答案产生影响。

设 $s$ 为 $1$ 的个数，当 $1$ 的个数大于等于 $\dfrac {k+1} 2$ 时中位数才为 $1$，考虑枚举 $1$ 的个数 $i$，$1$ 的选择方案数为 $\dbinom s i$，$0$ 的选择方案数为 $\dbinom{n-s}{k-i}$，所以子序列方案数为 $\dbinom s i \dbinom{n-s}{k-i}$。

答案即为：
$$
\sum\limits_{i=\frac{k+1} 2}^{\min(s,k)} \dbinom s i \dbinom{n-s}{k-i}
$$
至于求组合数的方法可以参考 [B3717 组合数问题](https://www.luogu.com.cn/problem/B3717)，提前预处理阶乘和逆元可以做到 $O(1)$ 求组合数。

单次时间复杂度为 $O(k)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define MAXN 200002
using namespace std;
typedef long long LL;
const int mod=1000000007;
int f[MAXN],v[MAXN];
int C(const int n,const int m){return n<m?0:(LL)f[n]*v[m]%mod*v[n-m]%mod;}//组合数。
int n,k;
void solve(){
	scanf("%d%d",&n,&k);
	int s=0,ans=0;
	for(int i=1,x;i<=n;i++) scanf("%d",&x),s+=x;
	for(int i=(k+1)>>1,mi=s<k?s:k;i<=mi;i++) ans=(ans+(LL)C(s,i)*C(n-s,k-i)%mod)%mod;
	printf("%d\n",ans);
}
int main(){
	*f=f[1]=*v=v[1]=1;
	for(int i=2;i<MAXN;i++) f[i]=(LL)f[i-1]*i%mod,v[i]=(LL)(mod-mod/i)*v[mod%i]%mod;//预处理阶乘和逆元。
	for(int i=1;i<MAXN;i++) v[i]=(LL)v[i-1]*v[i]%mod;//预处理阶乘的逆元。
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

长度为 $k$ 的子序列中位数为 $1$ 的条件为至少出现了 $\left\lceil\dfrac{k}{2}\right\rceil$ 个 $1$。设 $s=\sum a_i$，枚举子序列中 $1$ 的个数为 $i$，答案为 $\displaystyle\sum_{i=\lceil\frac{k}{2}\rceil}^{\min(k,s)}\binom{s}{i}\binom{n-s}{k-i}$。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
int fact[200005],inv[200005];
inline int C(int n,int m){
	return 1ll*fact[n]*inv[m]%mod*inv[n-m]%mod;
}
int T,n,m,s,ans;
int main(){
	fact[0]=inv[0]=fact[1]=inv[1]=1;
	for(int i=2;i<=200000;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=200000;++i)
		fact[i]=1ll*fact[i-1]*i%mod,inv[i]=1ll*inv[i-1]*inv[i]%mod;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		ans=s=0;
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),s+=x;
		for(int i=std::max((m>>1)+1,m-n+s);i<=s&&i<=m;++i)
			ans=(ans+1ll*C(s,i)*C(n-s,m-i))%mod;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Gapple (赞：1)

我们发现，当选择的 $0$ 的个数小于 $1$ 的个数时，中位数为 $1$，否则为 $0$。

我们设共有 $c_0$ 个 $0$，$c_1$ 个 $1$。

我们考虑当我们选 $i$（$0 \le i \le \dfrac{k - 1}{2}$）个 $0$ 时的答案：此时有 $\dbinom{c_0}{i}$ 种选 $0$ 的方案，和 $\dbinom{c_1}{k - i}$ 种选 $1$ 的方案，所以共有 $\dbinom{c_0}{i} \dbinom{c_1}{k - i}$ 种方案，故此时答案为 $\dbinom{c_0}{i} \dbinom{c_1}{k - i}$。

对上式从 $i = 0$ 到 $i = \dfrac{k - 1}{2}$ 求和，则最终的答案为 $\displaystyle \sum_{i = 0}^{(k - 1) / 2} \dbinom{c_0}{i} \dbinom{c_1}{k - i}$。

先 $O(n)$ 预处理阶乘与其逆元，再 $O(k)$ 计算答案即可。

```cpp
#include <iostream>

using namespace std;
using i64 = long long;

constexpr int MOD = 1e9 + 7, N = 2e5;

inline int mul(int x, int y)
{
    return (i64)x * y % MOD;
}

inline int mul(int x, int y, int z)
{
    return mul(x, mul(y, z));
}

int fact[N + 5], ifact[N + 5], inv[N + 5];

void prep()
{
    fact[0] = fact[1] = ifact[0] = ifact[1] = inv[1] = 1;

    for (int i = 2; i <= N; ++i) {
        fact[i] = mul(fact[i - 1], i);
        inv[i] = mul(MOD - MOD / i, inv[MOD % i]);
        ifact[i] = mul(ifact[i - 1], inv[i]);
    }
}

inline int C(int n, int m)
{
    return m > n ? 0 : mul(fact[n], ifact[m], ifact[n - m]);
}

inline int add(int x, int y)
{
    return (x + y) % MOD;
}

void solve_test()
{
    int n, k, ans = 0;
    int cnt[2] = { 0, 0 };

    cin >> n >> k;

    while (n-- > 0) {
        int x;
        cin >> x;
        ++cnt[x];
    }

    for (int i = 0; i <= k >> 1; ++i)
        ans = add(ans, mul(C(cnt[0], i), C(cnt[1], k - i)));

    cout << ans << '\n';
}

int main()
{
    prep();

    int t;
    cin >> t;

    while (t-- > 0)
        solve_test();

    return 0;
}
```

---

## 作者：aCssen (赞：1)

### Solution

考虑枚举这个子序列中有几个 $0$，假设共有 $i$ 个 $0$，那么就有 $k-i$ 个 $1$。

设 $a$ 中 $0$ 的数量为 $S_0$，$1$ 的数量为 $S_1$，那么显然答案就是 $\sum_{i=0}^{\lfloor \frac{k}{2} \rfloor } \binom{S_0}{i}\binom{S_1}{k-i}$。原理就是对于每个 $0$ 的选取方案，都可以选择这 $\binom{S_1}{k-i}$ 个选取方案，而这每种方案又对应了不同的子序列。枚举的上界是为了保证这个序列的中位数为 $1$。

考虑 $\binom{n}{m}$ 怎么求，根据定义，它等于 $\frac{n!}{m!(n-m)!}$，那么可以每次预处理阶乘和阶乘的逆元后 $\mathcal{O}(1)$ 计算。

有一个小技巧，在求出了 $n!$ 的逆元 $inv_n$ 后，$n-1$ 的逆元可以 $\mathcal{O}(1)$ 求得。考虑 $inv_n \equiv \frac{1}{n!}$，那么 $inv_{n-1} \equiv \frac{1}{(n-1)!} \equiv \frac{1}{n!} \times n$，即 $inv_i=inv_{i+1} \times (i+1)$。

总时间复杂度 $\mathcal{O}(\sum n)$

---

## 作者：ANDER_ (赞：1)

#### 考察：组合数学、逆元。
## 题意
给定一个只有 $0$ 和 $1$ 的，长度为 $n$ 的数组 $A$。以及一个整数 $k$。

求出所有长度为 $k$ 的子序列，求它们中位数的加和模 $10^9 + 7$ 的值。

## 思路
发现在中位数为 $1$ 时，才会对答案造成影响，我们就需要思考什么时候中位数为 $1$。注意到当且仅当序列中 $0$ 的个数 $s_0 \le \lfloor \frac{k}{2} \rfloor$ 时，中位数为 $1$。枚举 $s_0$，然后组合数统计答案：

$$\displaystyle\sum^{\lfloor \frac{k}{2} \rfloor}_{s_0 = 0} \binom{C_1}{k - s_0} \binom{C_0}{s_0}$$

其中 $C_1$ 是序列中 $1$ 的总量。$C_0$ 是序列中 $0$ 的总量。当然，从序列中 $1$ 的个数入手也是可以的。

额外注意的一点是，数的范围比较大。求组合数时，会用到逆元，求逆元的方法可以借鉴我的代码。


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
#define MSOD
const int N = 2e5 + 5, MOD = 1e9 + 7;

inline int lowbit(int x) {return x & (-x); }
inline int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b); }
inline int lcm(int a, int b) {return a * b / gcd(a, b); }
inline int exgcd(int a, int b, int &x, int &y) {if(!b) {x = 1, y = 0; return a; } int d = exgcd(b, a % b, y, x); y -= (a / b) * x; return d; }
inline int inv(int a, int m) {int x, y; exgcd(a, m, x, y); return (x % m + m) % m; }
inline int quick_pow(int a, int b) {int res = 1; while(b) {if(b & 1) {res = res * a % MOD; }a = a * a % MOD, b >>= 1; }return res; }

int p[N], in[N];
inline int C(int a, int b) {
	return (a < b || a < 0 || b < 0 ? 0 : p[a] * in[b] % MOD * in[a - b] % MOD);
}
inline void solve() {
	int n, k, c[2] = {0, 0}, ans = 0;
	cin>>n>>k;
	for(int i = 1, x ; i <= n ; i ++) {
		cin>>x;
		c[x] ++;
	}
	for(int i = (k + 1) / 2 ; i <= k && i <= c[1] ; i ++) {
		ans += C(c[1], i) * C(c[0], k - i) % MOD; 
	}
	cout<<ans % MOD<<endl;
	return;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);
#ifdef MSOD
	p[0] = 1;
	for(int i = 1 ; i < N ; i ++) {
		p[i] = p[i - 1] * i % MOD;
	}
	in[N - 1] = quick_pow(p[N - 1], MOD - 2);
	for(int i = N - 2 ; i >= 0 ; i --) {
		in[i] = in[i + 1] * (i + 1) % MOD;
	} 
	int T;
	for(cin>>T ; T -- ; ) {
		solve();
	}
#else
	solve();
#endif
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999F](https://www.luogu.com.cn/problem/CF1999F)

# 解题思路

注意到特殊的数据范围 $0 \le a_i \le 1$。

这启示我们写一个依赖当前值域的做法。

由于我们要统计的是子序列，因此我们可以直接枚举选几个 $0$，而由于题目限制，我们可以直接求出需要选出几个 $1$，在所有 $0$ 中选几个，在所有 $1$ 中选几个，这部分可以通过预处理组合数的方式来解决。

时间复杂度 $O(V \log V)$，其中 $V$ 为值域。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll n,m,mod=1e9+7;
ll a[200010];
ll pw(ll x,ll y,ll mod)
{
	if(x==0)
		return 0;
	ll an=1,tmp=x;
	while(y!=0)
	{
		if(y&1)
			an=(an%mod*tmp%mod)%mod;
		tmp=(tmp%mod*tmp%mod)%mod;
		y=y>>1;
	}
	an=an%mod;
	return an%mod;
}
ll fac[300010],inv[300010];
void init()
{
	fac[0]=1;
	forl(i,1,300005)
		fac[i]=i*fac[i-1],fac[i]%=mod;
	inv[300005]=pw(fac[300005],mod-2,mod);
	forr(i,300005,1)
		inv[i-1]=inv[i]*i%mod;
}
ll C(ll n,ll m)
{
	if(n<m || m<0)
		return 0;
	return (fac[n]%mod)*(inv[n-m]*inv[m]%mod)%mod;
}
ll ans;
ll sum0,sum1;
void solve()
{
	ans=sum0=sum1=0;
	_clear();
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i],sum0+=!a[i],sum1+=a[i];
	forl(i,(m+1)/2,m)
		ans+=C(sum1,i)*C(sum0,m-i)%mod,ans%=mod;
	cout<<ans<<endl;
}
int main()
{
	init();
	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：block_in_mc (赞：1)

## 题目大意

给出长度为 $n$ 的 $01$ 序列，求其所有长度为 $k$ 的子序列（可以不连续）的中位数之和。

## 解题思路

不难发现，只有中位数为 $1$ 才能对答案做出贡献，即子序列中 $1$ 的个数至少为 $\dfrac{k+1}{2}$。因此，我们可以枚举子序列中 $1$ 的个数 $i$，求出长度为 $k$ 的含有 $i$ 个 $1$ 的子序列的个数，这实际上就是从所有的 $1$ 中选出 $i$ 个 $1$，再在所有的 $0$ 中选出 $k-i$ 个 $0$ 的方案数。

设 $01$ 序列中 $0$ 的个数为 $c_0$，$1$ 的个数为 $c_1$，则答案为：

$$\sum\limits_{i=\frac{k+1}{2}}^{k}(C_{c_1}^i\times C_{c_0}^{k-i})$$

这里可以认为当 $n<m$ 时，$C_n^m=0$，也可以特判 $i>c_1$ 与 $k-i>c_0$ 的情况。

接下来考虑如何计算这个式子。

计算 $C_n^m$ 的公式为 $C_n^m=\dfrac{n!}{m!(n-m)!}$，我们可以预处理出 $i!$ 的值进行计算。另外，计算时涉及到了除法，在模 $p$ 意义下，一个数除以 $a$ 的值等于其乘以 $a$ 的逆元的值。由于 $10^9+7$ 是质数，$a$ 的逆元 $a^{-1}=a^{p-2}=a^{10^9+5}$，利用快速幂计算逆元即可，计算 $C_n^m$ 的式子可以转化为：

$$C_n^m=(m!(n-m)!)^{10^9+5}n!$$

直接计算即可，时间复杂度 $O(n\log n)$（$n,k$ 同阶）。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 1e9+7, N = 2e5+10;
ll t, n, k, x, cnt0, cnt1, ans, pre[N];
ll fpow(ll a,ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % p;
        a = (a * a) % p, b >>= 1;
    }
    return res % p;
}
ll C(ll n,ll m) {
    return pre[n] * fpow(pre[m] * pre[n-m] % p, p - 2) % p;
}
int main() {
    pre[0]=1;
    for (int i = 1; i < N; i++)
        pre[i] = (pre[i - 1] * i) % p;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        ans = cnt0 = cnt1 = 0;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            if (x == 0) cnt0++;
            else cnt1++;
        }
        for (int i = (k + 1) / 2; i <= min(cnt1, k); i++)
            if (k - i <= cnt0)
                ans = (ans + C(cnt1, i) * C(cnt0, k - i) % p) % p;
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：0)

一道组合数学的好题。

话说这翻译真的是给人看的吗。

### 题意

有一个长度为 $n$ 的二进制数组 $A$，求至少有 $x=\frac{k+1}{2}$ 个 $1$ 的，长度为 $k$ 的数组的子序列数量。

### 分析

因为这是一个二进制数组，所以如果有 $x$ 个 $1$ 的话，必然剩下的全部是 $0$，所以我们直接统计 $A$ 内 $1$ 和 $0$ 的数量 $sum1$ 和 $sum0$。

对于计算的 $1$ 的数量 $i$，如果说 $i$ 超过半个子序列长度 $k$，就一定符合条件，我们直接将 $i$ 从左往右推，$i$ 就是 $1$ 的个数，$k-i$ 就是 $0$ 的个数，所以答案直接是 $\sum_{i=1}^{sum1}C_{k-i}^{sum0}\times C_{i}^{sum1}$。

求个逆元把组合数求出来直接计算就行了。

不会求逆元或者没看懂的，建议你[去学习一下](https://www.luogu.com.cn/article/y49px6kk)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls ((now<<1))
#define rs ((now<<1)|1)
#define mid ((l+r)>>1)
const int maxn=2e5+10;
const int inf=1e9;
const int maxa=2e3+10;
const int modd=1e9+7;
int f[maxn],inv[maxn];
int ksm(int a,int b,int p){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a%p;
		}
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
void init(){
	f[0]=f[1]=1;
	for(int i=1;i<=maxn;i++){
		f[i]=f[i-1]*i%modd;
	}
	inv[maxn]=ksm(f[maxn],modd-2,modd);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%modd;
	}
}
int c(int a,int b){
	if(a==0)return 1ll;
 	if(a>b)return 0;
	return f[b]*inv[a]%modd*inv[b-a]%modd; 
}
void work(){
	int n,k;
	cin >> n >> k;
	int ans=0;
	int sum1=0,sum0=0;
//	for(int i=1;i<=15;i++){
//		cout << inv[i] << " ";
//	}
	for(int i=1;i<=n;i++){
		int x;
		cin >> x;
		if(x==1)sum1++;
		else sum0++;
	}
	for(int i=1;i<=sum1;i++){
		if(2*i>k&&k>=i){
			ans+=c(k-i,sum0)*c(i,sum1)%modd;
			ans%=modd; 
		}
	}
	cout << ans << endl;
}
signed main(){
	int t;
	cin >> t;
	init();
	while(t--){
		work();
	}
	return 0;
}
```

---

## 作者：ZhaoV1 (赞：0)

## 题解

在所有数组中数字都为 $0$ 或 $1$ 的前提下，我们要计算所有长度为 $k$ 的子序列中中位数总和，也就是说只有中位数为 $1$ 即长度为 $k$ 的子序列中 $1$ 的个数大于 $0$ 的个数时，对答案的贡献加 $1$。

记数组中 $1$ 的个数为 $one$，$0$ 的个数为 $zero$。那么存在：  
（组合数）$\binom{i}{one}×\binom{k-i}{zero}+\binom{i+1}{one}×\binom{k-i-1}{zero}+...+\binom{k}{one}×\binom{0}{zero}=res$，其中 $i$ 为某子序列中 $1$ 得个数。  
当然，若 $zero<i+\lambda$（其中 $0≤\lambda≤k-i$）时，就不再累加答案。若 $k-i-\lambda>zero$ 时，应当跳过该项。

AC Code
---


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9+7;
const int N = 2e5+5;
int t,n,k;
int a[N];
int f[N], g[N];
//组合数
long long fast_power(long long base, long long power){
	int res = 1;
	base %= MOD;
	while(power){
		if(power&1){
			res = res*base%MOD;
		}
		power /= 2;
		base = base*base%MOD;
	}
	return res;
}
void cal_init(){
	f[0] = g[0] = 1;
	for(int i=1;i<N;i++){
		f[i] = f[i-1]*i%MOD;
		g[i] = g[i-1]*fast_power(i,MOD-2)%MOD;
	}
}
long long calculate(long long n, long long m){
	return f[n]*g[m]%MOD*g[n-m]%MOD;
}

void solve(){
	int res = 0, one = 0, zero = 0;
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		one += (a[i] == 1);
		zero += (a[i] == 0);
	}
	for(int i=(k+1)/2;i<=k;i++){
		if(one < i) break;
		if(zero < k-i) continue;
		int num1 = calculate(one,i);
		int num2 = calculate(zero,k-i);
		res = (res+num1*num2)%MOD;
	}
	cout << (res+MOD)%MOD << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cal_init();
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一个长度为 $n$ 的仅包含 $0,1$ 的数列 $a$ 和 $k$，$k$ 是奇数；求出 $a$ 中所有长度为 $k$ 的子序列的中位数之和，答案对 $10^9+7$ 取模。此题中一个数列的中位数被定义为第 $\cfrac{k+1}{2}$ 个数。

## 解法

注意到当子序列的中位数是 $0$ 时对答案并无贡献。于是一个子序列有 $1$ 的贡献，当且仅当 $1$  的个数大于 $0$ 的个数，即 $1$ 的个数 $\ge\cfrac{k+1}{2}$。我们考虑枚举 $1$ 的个数，设为 $x$，那么 $0$ 的个数就有 $(k-x)$ 个；我们预处理组合数分别计算从所有 $1$ 中挑出 $x$ 个和从所有 $0$ 中挑出 $(k-x)$ 个方案数，相乘即为当前的答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn], n, k;
int fac[maxn], inv[maxn]; const int P = 1e9 + 7;
int qp(int x, int y) {
	int res = 1;
	for (; y; y >>= 1, x = (1ll * x * x) % P)
		if (y & 1) res = (1ll * res * x) % P;
	return res;
}
void init() { // 预处理阶乘和逆元
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= maxn - 5; i ++)
		fac[i] = (1ll * fac[i - 1] * i) % P;
	inv[maxn - 5] = qp(fac[maxn - 5], P - 2);
	for (int i = maxn - 6; i >= 0; i --)
		inv[i] = (1ll * inv[i + 1] * (i + 1)) % P;
}
int C(int x, int y) {
	if (x < y) return 0;
	int p = (1ll * fac[x] * inv[y]) % P;
	return (1ll * p * inv[x - y]) % P;
}
int main() {
	int T; init();
	for (scanf("%d", &T); T --; ) {
		scanf("%d %d", &n, &k);
		int c0 = 0, c1 = 0, ans = 0;
		for (int i = 1; i <= n; i ++)
			scanf("%d", &a[i]), a[i] == 0 ? ++ c0 : ++ c1; // 这句可以写成一对 if else
		for (int i = (k + 1) / 2; i <= k; i ++) {
			ans = (1ll * ans + (1ll * C(c1, i) * C(c0, k - i)) % P) % P;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：GoldenCreeper (赞：0)

注意到序列中的顺序是无关紧要的，我们只需要关注 $0$ 和 $1$ 的个数。

不妨设序列中有 $a$ 个 $0$，$b$ 个 $1$，选取后的序列中有 $c$ 个 $0$，$d$ 个 $1$。如果选取后的中位数为 $1$，那么有 $c\ge\dfrac{k+1}2$，此时 $d = k - c$，所以会对答案产生 $C_k^c\times C^d_k$ 的贡献。

故只需计算 $\sum\limits_{i=\frac{k+1}2}^kC_i^c\times C_i^d$ 即可，[参考实现](https://codeforces.com/contest/1999/submission/275395698)。

---

## 作者：PineappleSummer (赞：0)

[CF1999F Expected Median](https://www.luogu.com.cn/problem/CF1999F)

简单组合计数。

设 $1$ 的个数为 $cnt$，那么 $0$ 的个数为 $n-cnt$。

发现合法的子序列中 $1$ 的个数为 $\left\lfloor\frac{k}{2}\right\rfloor +1\sim k$，考虑依次枚举子序列中 $1$ 的个数并计算贡献。

对于 $\left\lfloor\frac{k}{2}\right\rfloor +1\sim k$ 中的一个数 $i$，含有 $i$ 个 $1$ 的子序列共有 $C_{cnt}^i\times C_{n-cnt}^{k-i}$ 个。这个式子不难理解，就是从 $cnt$ 个 $1$ 中选出 $i$ 个 $1$ 并从 $n-cnt$ 个 $0$ 中选出 $k-i$ 个 $0$ 的方案数。

那么最终答案即为 $\sum\limits_{i=\left\lfloor\frac{k}{2}\right\rfloor +1}^kC_{cnt}^i\times C_{n-cnt}^{k-i}$。

线性预处理阶乘逆元，单组询问时间复杂度 $\mathcal O(n)$。

```cpp
void solve () {
	cin >> n >> k;
	int cnt = 0, ans = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], cnt += a[i];
	for (int i = k / 2 + 1; i <= k; i++)
		ans = (ans + C (cnt, i) * C (n - cnt, k - i) % mod) % mod;
	cout << ans << '\n';
}
```

---

## 作者：_O_v_O_ (赞：0)

[点此查看这个蒟蒻写的该场比赛所有题目的题解](https://www.luogu.com.cn/article/opat7vrj)

转化一下问题：

> 选 $x$ 个 $1$，$y$ 个 $0$，使得 $x+y=k$ 且 $x>y$ 且$x\le \text{a中的1的个数}$ 且 $y\le \text{a中的0的个数}$，求方案数。

很明显可以直接上组合，答案为 $\sum_{i=\lceil \frac{k}{2} \rceil}^x\binom{x}{i}\binom{y}{k-i}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=1e9+7;

int T,n,k,a[1000001],nu,an;
int fa[1000001],in[1000001];

int po(int a,int b,int p){
	int an=1;
	while(b){
		if(b&1)an=an*a%p;
		a=a*a%p,b>>=1;
	}return an;
}

int ny(int x,int p){
	return po(x,p-2,p)%mo;
}

int C(int x,int y){
	if(x<y)return 0;
	return fa[x]*in[y]%mo*in[x-y]%mo;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	fa[0]=in[0]=1;
	for(int i=1;i<=(int)(3e5);i++) fa[i]=fa[i-1]*i%mo;
	for(int i=1;i<=(int)(3e5);i++) in[i]=ny(fa[i],mo);
	while(T--){
		nu=an=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i],nu+=a[i];
		for(int i=k/2+1;i<=k;i++){
			int x=i,y=k-i;
			an=(an+C(nu,x)*C(n-nu,y)%mo)%mo;
		}
		cout<<an<<endl;
	}
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## CF1999F Expected Median

中位数为 $1$ 的序列才有贡献，只需计算中位数为 $1$ 的序列个数即可。

记 $c_0,c_1$ 表示 $0,1$ 的个数。

考虑如果有 $i$ 个 $1$，那么合法的序列个数为 ${c_1\choose i}\times{c_0\choose k-i}$，即选出 $i$ 个 $1$ 和 $k-i$ 个 $0$ 的方案数。

根据题意，$1$ 的个数至少为 $\lceil\dfrac k2\rceil$，最多为 $c_1$。枚举累加即可。

注意可能再求组合数时出现非法情况，判断一下即可。

代码：

```cpp

ll C(int n, int m) {
  if (n < 0 || m < 0 || n < m) return 0;
  return fac[n] * inv[m] % P * inv[n - m] % P;
}

void Main() {
  n = read(), k = read(), res = 0;
  c[0] = c[1] = 0;
  for (int i = 1; i <= n; ++i) ++c[read()];
  for (int i = k / 2 + 1; i <= c[1]; ++i)
    res = (res + C(c[1], i) * C(c[0], k - i) % P) % P;
  printf("%lld\n", res);
}
```

---

## 作者：__O_v_O__ (赞：0)

首先，我们把问题转化为从数列中选 $x$ 个 $1$，$y$ 个 $0$，使得 $x+y=k$ 且 $x>y$ 且 $x$ 小于等于数列中的 $1$ 的个数，$y$ 小于等于数列中的 $0$ 的个数，求方案数。

解释一下：$x+y=k$ 是题目中要求子序列长度为 $k$，$x>y$ 是子序列中位数为 $1$ 的条件，而后面两个条件是限制子序列合法。

有了这个转化，原问题就迎刃而解：我们在 $[\frac{k}{2}+1,k]$ 范围内枚举 $x$，对于每个枚举的数，我们算出 $y$，再把答案加上 $\binom{s}{x}\times\binom{n-s}{y}$（这里 $s$ 表示数列中 $1$ 的个数）。

这里，我使用的是阶乘加逆元求组合数。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=1e9+7;
int t,n,k,a[1000001],nu,an;
int fa[1000001],in[1000001];
int po(int a,int b,int p){
	int an=1;
	while(b){
		if(b&1)an=an*a%p;
		a=a*a%p,b>>=1;
	}
	return an;
}
int ny(int x,int p){
	return po(x,p-2,p)%mo;
}
int C(int x,int y){
	if(x<y)return 0;
	return fa[x]*in[y]%mo*in[x-y]%mo;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>t,fa[0]=in[0]=1;
	for(int i=1;i<=300000;i++)fa[i]=fa[i-1]*i%mo;
	for(int i=1;i<=300000;i++)in[i]=ny(fa[i],mo);
	while(t--){
		nu=0,cin>>n>>k,an=0;
		for(int i=1;i<=n;i++)cin>>a[i],nu+=a[i];
		for(int i=k/2+1;i<=k;i++){
			int x=i,y=k-i;
			an=(an+C(nu,x)*C(n-nu,y)%mo)%mo;
		}
		cout<<an<<'\n';
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

当你没有思路的时候就要去看数据范围。

我们注意到题目中保证了 $n$ 的和不会超过 $2\times10^5$。猜测是线性的。

这时候我们换一个思路。既然我们不能够直接枚举子序列，那我们可不可以间接枚举呢？

我们注意到，只有这个子序列中的中位数为 $1$，也就是说 $1$ 的个数大于等于 $\frac{k+1}{2}$ 时才对答案有贡献。

同时我们知道，$1$ 和 $0$ 的具体位置我们并不关心。我们只需要有那么多个 $1$ 和剩下的那么多个 $0$ 就够了。

思路顺势就出来了：排列组合。

首先枚举子序列中有多少个 $1$。假设子序列中有 $c$ 个 $1$，原序列中有 $t$ 个 $1$，可能的情况数为 $C_t^c$。然后考虑 $0$。子序列中有 $k-c$ 个，原序列中有 $n-t$ 个，可能的情况数为 $C_{n-t}^{k-c}$。因此，子序列中有 $c$ 个一的情况数为 $C_t^c\times C_{n-t}^{k-c}$。

枚举一下答案就出来了。注意 $c\ge\frac{k+1}{2}$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int mod=1e9+7,lim=2e5;
int t,n,m,a,jc[200005],ny[200005],cnt,ans;
inline int cvl(const int&n,const int&m){
	if(m>n) return 0;
	return jc[n]*ny[m]%mod*ny[n-m]%mod;
}
inline int qpow(int a,int b=mod-2,int p=mod){
	int tmp=1;
	while(b){
		if(b&1) tmp*=a,tmp%=p;
		a*=a; a%=p; b>>=1;
	}
	return tmp;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>t; jc[0]=1;
	for(int i=1;i<=lim;++i) jc[i]=jc[i-1]*i%mod;
	ny[lim]=qpow(jc[lim]);
	for(int i=lim;i>0;i--) ny[i-1]=ny[i]*i%mod;
	while(t--){
		cin>>n>>m; ans=cnt=0;
		for(int i=1;i<=n;++i)
			cin>>a,cnt+=a;
		for(int i=m/2+1;i<=m&&i<=cnt;++i)
			ans+=cvl(cnt,i)*cvl(n-cnt,m-i),
			ans%=mod;
		cout<<ans<<endl;
	}
	return 0;
}
//私は猫です
```

---

