# Magnitude (Hard Version)

## 题目描述

**注意：** 本题的两个版本题意是有不同的，你可能需要同时阅读两个版本的题意。

给定一个长度为 $n$ 的数组 $a$。初始有 $c=0$；接下来，对每个在 $1$ 到 $n$ 范围内的 $i$（按递增的顺序） ，要执行以下两种操作中的恰好一种：

- 操作 $1$：将 $c$ 修改为 $c+a_i$。

- 操作 $2$：将 $c$ 修改为 $|c+a_i|$，这里 $|x|$ 表示 $x$ 的绝对值。

令所有操作后 $c$ 能取得的最大值为 $k$，你需要求出有多少种本质不同的方案使得 $c=k$。这里两个方案被视为不同，当且仅当存在一个 $i$ 使得其中一个方案选了操作 $1$ 而另一个选了操作 $2$，即便这步操作后两个方案对应的 $c$ 相等。

由于答案可能很大，请输出答案对 $998244353$ 取模后的结果。

## 样例 #1

### 输入

```
5
4
2 -5 3 -3
8
1 4 3 4 1 4 3 4
3
-1 -2 -3
4
-1000000000 1000000000 1000000000 1000000000
4
1 9 8 4```

### 输出

```
12
256
1
8
16```

# 题解

## 作者：Louis_lxy (赞：8)

首先由一个容易发现的规律，我们只需要使用一次操作 2 即可达到最大值，因为显然我们要让负数的和更加大，到最后一次时能造成更大的贡献，如果在和为负数时使用了两次操作 2，显然他们会抵消，从而使得答案更小。

接着我们考虑答案数量，显然我们可以发现，进行操作 2 的时候一定在最小值的位置，因为此时不会造成负贡献，接着我们考虑它造成的贡献。显然他之前的所有负数都不能使用操作 2，因此正数都可以使用 2 中操作，而后面的所有数也可以随意选择操作方案，令进行操作前用 $cnt$ 个正数，此时是第 $i$ 项，造成的贡献为 $2^{cnt+n-i}$。

记得要对每次是最小值的地方都计算贡献。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1, mod = 998244353;
int _, n, a[N], cnt;
long long ans, mn, sum[N], pw[N << 1];

void solve()
{
	scanf("%d", &n);
	for (int i 
	= 1; i <= n; ++i) scanf("%d", &a[i]);
	ans = cnt = 0, mn = a[1];
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i], mn = min(mn, sum[i]);
	for (int i = 1; i <= n; ++i)
	{
		if (sum[i] >= 0) ++cnt;
		if (sum[i] == mn && mn < 0) ans = (ans + pw[cnt + n - i]) % mod;
	}
	if (mn >= 0) ans = pw[n];
	printf("%lld\n", ans);
}

int main()
{
	pw[0] = 1;
	for (int i = 1; i <= 2e6; ++i) pw[i] = (pw[i - 1] << 1) % mod;
	scanf("%d", &_);
	while (_--) solve();
	return 0;
}
```

---

## 作者：jzcrq (赞：5)

最大 $c$ 可能来自：

1. 对最大 $c$ 进行操作 $1$。
2. 对最大 $c$ 进行操作 $2$。
3. 对最小 $c$ 进行操作 $2$。

最小 $c$ 可能来自:

1. 对最小 $c$ 进行操作 $1$。
2. 对最小 $c$ 进行操作 $2$。

当上一位的最大 $c$ 与最小 $c$ 相同时，该位最大 $c$ 的后两种贡献同源，只计一次。

根据上面的递推关系 dp 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5,MAXN=N+7,mod=998244353,inf=1e18;
int n,a[MAXN],f[MAXN],g[MAXN],nf[MAXN],ng[MAXN];

signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		cin>>n;
		nf[0]=ng[0]=1;
		for (int i=1;i<=n;i++) f[i]=-inf,g[i]=nf[i]=ng[i]=0;
		for (int i=1;i<=n;i++) cin>>a[i];
		for (int i=1;i<=n;i++)
		{
			f[i]=max(f[i-1]+a[i],abs(g[i-1]+a[i]));
			g[i]=g[i-1]+a[i];
			if (f[i]==f[i-1]+a[i]) nf[i]+=nf[i-1];
			if (f[i]==abs(f[i-1]+a[i])&&f[i-1]!=g[i-1]) nf[i]+=nf[i-1];
			if (f[i]==abs(g[i-1]+a[i])) nf[i]+=ng[i-1];
			ng[i]=ng[i-1];
			if (g[i]>=0) ng[i]<<=1;
			nf[i]%=mod;
			ng[i]%=mod;
		}
		cout<<nf[n]<<'\n';
	}
	return 0;
}
```

---

## 作者：littlebug (赞：3)

## Solution

[请先阅读 C1 的题解](/article/yb2sd5ua)。

设前缀和数组为 $sum$，其最小值为 $mn$。

考虑对于每个能且只能进行操作二的 $i$ 分别计算贡献。

首先，我们需要在遍历过程中记录一个 $cnt$，表示在当前位置之前共有几个位置可以进行任意一种操作。对于一个 $i$，若 $sum_i \ge 0$，那么取不取绝对值就和 $sum_i$ 没关系了，因此将 $cnt$ 加 $1$。

接下来，对于 $i$，如果 $sum_i = mn$，那么可以选择将这个位置进行操作二，同时**它后面的其它位置可以任意操作**（因为有 $sum_i = mn$，所以它后面一定是非负的了），所以它对答案的贡献为 $2^{cnt} \times 2^{n-i}$（$i$ 前面可以任意操作的和 $i$ 后面可以任意操作的）。

特判：如果 $mn=0$，即没有只能进行操作二的位置，那么答案为 $2^n$，因为任意一个位置都可以进行两种操作。

因为要频繁使用 $2^x$，而且需要取模，所以需要先对 $2$ 的 $0 \sim n$ 次幂进行一个预处理。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
#define ll long long
using namespace std;
const ll mod=998244353;
const int MAXN=2e5+5;
int n;
ll a[MAXN];
ll sum[MAXN];
ll pow2[MAXN];
il void init()
{
	pow2[0]=1;
	for(int i=1;i<=MAXN-3;++i)
		pow2[i]=(pow2[i-1]<<1)%mod;
	return;
}
il void solve()
{
	cin>>n;
	ll mn=0;
	ll ans=0,cnt=0;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		mn=min(mn,sum[i]);
	}
	if(!mn)
	{
		cout<<pow2[n]<<'\n';
		return;
	}
	for(int i=1;i<=n;++i)
	{
		if(sum[i]>=0) ++cnt;
		if(sum[i]==mn)
			ans+=pow2[cnt]*pow2[n-i],ans%=mod;
	}
	cout<<ans<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：dutianchen1 (赞：1)

# CF1984C2 Magnitude (Hard Version)
---
# 思路简析

首先由[简单版](https://www.luogu.com.cn/problem/CF1984C1)求最大值 $k$ 开始考虑，经过分析可以得到：

假设我们原来都只执行操作一（也就是**前缀和**），若要执行操作二获得最大值，我们只会在执行操作一时获得**最小的负数值时执行操作二**。

也就是说，**只需要执行一次操作二**就可以得到最大值 $k$。

为什么只执行一次？画个图来看看。

![(伪函数)图像](https://cdn.luogu.com.cn/upload/image_hosting/7iuw70f6.png)

假定我们只执行操作一后，$c$ 的变化曲线如图。

很容易就能发现，当 $c \ge 0$ 时，我们执行操作一还是操作二对于 $c$ 的值无影响。

而当 $c < 0 $ 时，若我们对最小负值之前的负值处使用操作二，会导致我们在 $c$ 为最小负值时使用操作二的收益更小。（可以试着将最小值之前的图像沿 $x$ 轴对称再观察图像。）

不过当我们对 $c$ 为最小负值时使用操作二后，哪怕后面的 $c$ 再次达到负值甚至等于最小负值，我们执行操作一还是操作二也不会影响最终的 $c$ 达到最大值 $k$。

综上，我们总结出来如下几条策略来求得使得 $c=k$ 的方案数：

1. 令 $sum_{i}=\sum_{j=1}^{i}$ ，记 $sum_{i}\min$ 为 ``minn``。
2. 当 $sum_{i}$ 为正数时，两种操作都可，记 $tot=$ 在 $i$ 之前的正数个数。
3. 当 $sum_{i}$ 为负数且不为最小值时且在最小值之前，只能使用操作一。
4. 当 $sum_{i}$ 为最小负值时，后面的 $n-i$ 个数都可以使用两个操作。所以我们把方案数累加 $2^{tot}\times 2^{n-i} $ 即可。
5. 由于我们对于不同位置的最小负值，至少对其中一个使用操作二就能达到最大值，所以我们对于每个 $sum{i}=minn$，都进行方案累加。

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+5;
const int mod = 998244353;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline ll min(ll a,ll b){return a>=b?b:a;}
ll T;
ll n;
ll num[N],sum[N];
ll qpow[N];
void init()
{
	qpow[0]=1;
	for(int i=1;i<=N;i++)
	{
		qpow[i]=(qpow[i-1]<<1)%mod;
	}
}
int main()
{
	cin.tie(0);cout.tie(0);
	init();
	T=read();
	while(T--)
	{
		n=read();
		ll minn=0;//以防全为正数时，误减 
		ll ans=0,tot=0;
		for(int i=1;i<=n;i++)
		{
			num[i]=read();
			sum[i]=sum[i-1]+num[i];
			minn=min(minn,sum[i]);//只在最小时使用操作2，否则求得的值不是最优。 
		}
//		cout<<sum[n]-minn*2<<'\n';//第一问 
		
		if(minn==0)
		{
			cout<<qpow[n]<<'\n';
			continue;
		}
		
		for(int i=1;i<=n;i++)
		{
			if(sum[i]>=0) tot++;//正数两种操作均可使用
			//当为负数时，我们只能使用操作1。 
			if(sum[i]==minn)
			{
				ans+=qpow[tot]*qpow[n-i]; 
				ans%=mod;
			}
		}
		cout<<ans<<'\n'; 
	}
	return 0;
}

```

---

## 作者：aeiouaoeiu (赞：1)

upd 2024.7.7：修改一处笔误，补充解释。

先阅读 [Easy version](https://www.luogu.com.cn/article/qg2n96jc)。

在列出 $f_{i,0/1}$ 的转移后，我们令 $g_{i,0/1}$ 表示在第 $i$ 次操作后 $c$ 取得最小/最大值的方案数。

根据 $f_{i,0/1}$ 的转移中有多少个等于最终的 $f_{i,0/1}$，转移方案数即可。注意当 $f_{i-1,0}=f_{i-1,1}$ 时要特判，令 $g_{i,0/1}\leftarrow \frac{g_{i,0/1}}{2}$。

另：$g_{i,0/1}\leftarrow \frac{g_{i,0/1}}{2}$ 更合理的解释方法是 $g_{i,1}\leftarrow 0$，因为同时保留 $g_{i,0/1}$ 会算重。两种方法结果一致。

时间复杂度：提前特判可以做到 $\mathcal{O}(n)$，转移后再特判若没有预处理 $2$ 的逆元会变成 $\mathcal{O}(n\log p)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
#define mkt make_tuple
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1000000000000000007ll,p=998244353;
ll n,a[maxn],f[maxn][2],g[maxn][2];
ll myabs(ll a){return (a<0?-a:a);}
void ups(ll &a,ll b){a=(a+b>=p?a+b-p:a+b);}
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
signed main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(;T--;){
		cin>>n; f[0][0]=f[0][1]=0,g[0][0]=g[0][1]=1;
		for(int i=1;i<=n;i++) cin>>a[i],f[i][0]=ee,f[i][1]=-ee,g[i][0]=g[i][1]=0;
		for(int i=1;i<=n;i++){
			f[i][0]=min(min(f[i-1][0]+a[i],myabs(f[i-1][0]+a[i])),
			min(f[i-1][1]+a[i],myabs(f[i-1][1]+a[i])));
			if(f[i-1][0]+a[i]==f[i][0]) ups(g[i][0],g[i-1][0]);
			if(myabs(f[i-1][0]+a[i])==f[i][0]) ups(g[i][0],g[i-1][0]);
			if(f[i-1][1]+a[i]==f[i][0]) ups(g[i][0],g[i-1][1]);
			if(myabs(f[i-1][1]+a[i])==f[i][0]) ups(g[i][0],g[i-1][1]);
			if(f[i-1][0]==f[i-1][1]) g[i][0]=g[i][0]*qpow(2,p-2)%p;
			f[i][1]=max(max(f[i-1][0]+a[i],myabs(f[i-1][0]+a[i])),
			max(f[i-1][1]+a[i],myabs(f[i-1][1]+a[i])));
			if(f[i-1][0]+a[i]==f[i][1]) ups(g[i][1],g[i-1][0]);
			if(myabs(f[i-1][0]+a[i])==f[i][1]) ups(g[i][1],g[i-1][0]);
			if(f[i-1][1]+a[i]==f[i][1]) ups(g[i][1],g[i-1][1]);
			if(myabs(f[i-1][1]+a[i])==f[i][1]) ups(g[i][1],g[i-1][1]);
			if(f[i-1][0]==f[i-1][1]) g[i][1]=g[i][1]*qpow(2,p-2)%p;
		}
		//for(int i=1;i<=n;i++) cout<<f[i][0]<<" "<<f[i][1]<<" "<<g[i][0]<<" "<<g[i][1]<<"\n";
		cout<<g[n][1]<<"\n";
	}
	return 0;
}
```

---

## 作者：Xiphi (赞：1)

鉴定为 `labs` 是傻逼导致的。赛时用 `labs` 挂了 $4$ 发（交 C1 的时候）。感觉这题有点虚高了。

首先让我们复述一下 C1 的 dp 过程。我们设 $f_{i,0/1}$ 表示到
 $i$ 为止最小可达值和最大可达值分别是多少（$0$ 代表最小，$1$ 代表最大）。
 
于是很容易就可以推出递推式子，每次转移时枚举前一位与这一位 $4$ 种组合情况分别是什么即可。如果不会推的话看代码。

回到这道题上，要求的是求方案数，那么我们另设 $F_{i,0/1}$ 表示到
 $i$ 为止最小可达值和最大可达值分别的方案数是多少（$0$ 代表最小，$1$ 代表最大）。
 
 很自然的，直接在每次枚举 $4$ 种情况时算出有那个可以达到最大或最小值，再与上一轮的 $F$ 数组相乘即可。
 
 但测一遍样例，发现这是有问题的。因为可能会出现最大值和最小值相同的情况。于是，我们特判，若上一轮的可达的最大最小值相等且方案数相等时，当前这一轮已经算出的两个 $F_{i,0/1}$ 分别除以 $2$。
 
```cpp
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
#define _forp(i,x,y,z) for(int i=x;i<=y;i+=z)
#define _rep(i,x,y) for(int i=x;i<y;++i)
using namespace std;
#define int long long
int n,a[500005],T;
const int p=998244353;
int f[500005][5];
int F[500005][5];
int Abs(int x){
	return (x>0?x:-x);
}
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		_for(i,1,n){
			cin>>a[i];
		}
		f[0][1]=f[0][0]=0;
		F[0][1]=F[0][1]=1;
		_for(i,1,n){
			int X=f[i-1][0]+a[i],Y=f[i-1][1]+a[i];
			f[i][0]=min({f[i-1][0]+a[i],f[i-1][1]+a[i],Abs(X),Abs(Y)});
			int c1=(f[i-1][0]+a[i]==f[i][0] )*F[i-1][0]+F[i-1][1]*(f[i][0]==f[i-1][1]+a[i])+F[i-1][0]*(Abs(X)==f[i][0])+F[i-1][1]*(Abs(Y)==f[i][0]);
			f[i][1]=max({f[i-1][0]+a[i],f[i-1][1]+a[i],Abs(X),Abs(Y)});
			int c2=(f[i-1][0]+a[i]==f[i][1])*F[i-1][0]+F[i-1][1]*(f[i][1]==f[i-1][1]+a[i])+F[i-1][0]*(Abs(X)==f[i][1])+F[i-1][1]*(Abs(Y)==f[i][1]);
			if(F[i-1][0]==F[i-1][1]&&f[i-1][0]==f[i-1][1]) c1/=2,c2/=2;
			F[i][0]=c1;
			F[i][0]%=p;
			F[i][1]=c2;
			F[i][1]%=p;
		}
		cout<<F[n][1]<<'\n';
	}
	return 0;
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1984C2)

气死了 `llabs` 写成 `labs` 赛时罚坐一小时。

## $\mathtt{Solution}$

首先考虑最优解是如何构造出来的，蒙了一个结论：

- $ans=s_n-\min\{2\min\limits_{i=1}^{n} a_i,0\}$。

$\mathbf{Proof:}$

如果把 $2$ 操作看成改变一些数的正负，显然，最优情况下一定会导致**每一个位置的前缀和都是正的**。

接下来就是证明为什么只有一次本质有效的 $2$ 操作。

如果你在位置 $i$ 做了 $2$ 操作后，又对 $j$ 位置做了 $2$ 操作（$i<j$），我们发现：

 1. 若答案有所增加，那么在 $i$ 位置做 $2$ 操作是没有意义的。
 
 2. 若答案没有增加，那么在 $j$ 位置做 $2$ 操作是没有意义的。
 
证毕，所以你就可以通过简单版了。

----

考虑最终答案的计算。

上文已经证明只有一次有意义的 $2$ 操作，那么我们可以枚举最后一次进行 $2$ 操作的位置 $i$。

前面 $1\sim i-1$ 前缀和为负数的都只能是 $2$ 操作，后面 $i+1\sim n$ 的都可以。

所以位置 $i$ 的贡献为：$2^{n-i+p_i}$，其中 $p_i=\sum\limits_{j=1}^{i-1}[s_j\ge0]$。

特判一下所有前缀和均为非负的即可。

参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5, MOD = 998244353;
int t, n, h, minn, ans, a[MAXN], s[MAXN], tot[MAXN], pw[MAXN];
signed main(){
	t = read();
	while(t --){
		n = read(), ans = 0, pw[0] = 1, minn = 0;
		for(int i = 1;i <= n;i ++){
			a[i] = read(), s[i] = s[i - 1] + a[i];
			tot[i] = tot[i - 1] + (s[i] >= 0);
			pw[i] = pw[i - 1] * 2 % MOD;//预处理2的幂
			minn = min(minn, s[i]);
		}
		int v = s[n] - 2 * minn;
		if(tot[n] == n){//均为非负数
			printf("%lld\n", pw[n]);
			continue;
		}
		for(int i = 1;i <= n;i ++){
//			printf("%lld %lld %lld\n", i, lastans, v);
			if((llabs(s[i]) + s[n] - s[i]) == v)
				ans = (ans + pw[n - i + tot[i]]) % MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Lu_xZ (赞：1)

### C1

最多只会用一次操作二。

反证法。考虑最后两次操作二分别对应 $c + a_i$ 和 $c + a_j$。显然 $c + a < 0$，否则没必要用操作二。如果 $i$ 处用了操作 $1$，$c + a_j$ 将变得更小，从而使答案增大。

维护最小前缀和 $x = \min(s_i, 0)$，则最终的 $c = s_n - 2x$。

```cpp
void solve() {
	ll n, mi = 0, s = 0;
	cin >> n;
	for(int i = 1; i <= n; ++ i) {
		int x; cin >> x;
		mi = min(mi, s += x);
	}
	cout << s - mi * 2 << '\n';
}
```

### C2

延续 C1 的思考方向。

如果 $x = 0$，操作中不出现负数。因此操作一操作二是等效的，方案数为 $2^n$。

如果 $s_i = x$，说明可以在这一步进行操作二达到最终的 $c$。

记 $k = \sum\limits_{j <i}[s_j\ge0]$，表示在 $i$ 之前有 $k$ 步可以用两种操作。

因为 $c \ge 0$，所以在 $i$ 之后的所有的操作都是非负的，贡献为 $2^k \times 2^{n - i}$。

```cpp
void solve() {
	cin >> n;
	mi = 0;
	for(int i = 1; i <= n; ++ i) {
		cin >> s[i];
		mi = min(mi, s[i] += s[i - 1]);
	}
	if(mi == 0) {
		cout << p[n] << '\n';
		return;
	}
	ll ans = 0;
	for(int i = 1, k = 0; i <= n; ++ i) {
		if(s[i] >= 0) ++ k;
		if(s[i] == mi) {
			ans = (ans + p[k] * p[n - i]) % P;
		}
	}
	cout << ans << '\n';
}
```

---

## 作者：yuyc (赞：0)

[Easy Version 传送门](https://www.luogu.com.cn/problem/CF1984C1)

这里给出一个相对复杂的解法 ~~因为我赛时没有观察到一个重要的性质~~
## 题意

给定一个长度为 $n$ 的数组 $a$ 以及初始值为 $0$ 的变量 $c$，共有 $n$ 次操作，对于第 $i$ 次操作，有两种选择：

1. $c \gets c + a_i$
2. $c \gets \lvert c + a_i \rvert$

求所有操作过后，能使 $c$ 的值最大的方案个数对 $998244353$ 取模的结果。

## 解析

不难发现，对于第 $i$ 次操作，当且仅当 $c+a_i<0$ 时，选择操作 1 与选择操作 2 得到的结果不同，且操作 2 得到的结果必定更大，即 $c+a_i < \lvert c + a_i \rvert$，我们记这样的操作 2 为“**必要的**”。

进一步观察得到，一个能使 $c$ 的值最大的方案，**至多**出现一个“必要的”操作 2。

这是因为“必要的”操作 2 总是把加上 $a_i$ 后为负数的 $c$ 变为正的，且操作前 $c+a_i$ 越小，操作后 $c$ 越大。

对于一种方案，如果有多个“必要的”操作 2，不妨只保留最后一个，那么在最后一个“必要的”操作 2 之前，我们希望 $c$ 尽可能小，但是前面的“必要的”操作 2 对 $c$ 做的贡献必定大于改为进行操作 1 所能做的贡献，即把前面的操作全改为操作 1 后，**最终**的 $c$ 会更大，故这种方案不能使 $c$ 最大。

考虑枚举“必要的”操作 2 的位置，令 $s$ 为 $a$ 的前缀和数组，对于每个 $s_i<0$，如果在第 $i$ 次操作进行“必要的”操作 2，**最终**得到的 $c=-s_i + s_n-s_i$，在 $i$ 之前，操作 1 与操作 2 等价的位置数量 $cnt_1=\sum_{j=1}^{i-1} [s_j\ge 0]$，在 $i$ 之后，等价的位置数量 $cnt_2=\sum_{j=i+1}^{n} [s_j\ge s_i \times 2]$，前者可以在求前缀和的时候预处理得出，后者可以通过从 $n$ 到 $1$ 枚举位置，再利用树状数组来求，最终答案为 $2^{cnt_1} \times 2^{cnt_2}$。

另外，当 $s$ 中不存在负数时，对于每一步操作，选择操作 1 和操作 2 都是等价的，答案为 $2^n$。 

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5,p = 998244353;
int a[N],cnt[N],d[N * 2],mi2[N];
ll s[N];
void add(int x,int k){
	for(;x<N*2;x += x & -x){
		d[x] += k;
	}
}
int ask(int x){
	int res = 0;
	for(;x;x -= x & -x){
		res += d[x];
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	mi2[0] = 1;
	for(int i=1;i<N;i++) mi2[i] = mi2[i - 1] * 2 % p; //预处理2的幂 
	int T;
	cin>>T;
	while(T--){
		int n;
		ll k = 0,ans = 0;
		vector<ll> v;
		vector<int> modi;   // 回溯修改以清空树状数组 
		v.push_back(-1e15); // 防止后面ask的时候越界 
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s[i] = s[i - 1] + a[i];
			v.push_back(s[i]);
			v.push_back(s[i] * 2);
			cnt[i] = cnt[i - 1] + (s[i] >= 0);
		}
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());
		k = s[n];
		ans = mi2[n];
		for(int i=n;i>=1;i--){
			ll x = - s[i] + s[n] - s[i];
			if(s[i] < 0 && x >= k){
				if(x > k){
					k = x;
					ans = 0;
				}
				int t = lower_bound(v.begin(),v.end(),2 * s[i]) - v.begin();
				ans = (ans + 1ll * mi2[cnt[i]] * mi2[ask(v.size()) - ask(t - 1)] % p) % p;
			}
			int pos = lower_bound(v.begin(),v.end(),s[i]) - v.begin();
			add(pos,1);
			modi.push_back(pos);
		}
		cout<<ans<<'\n';
		for(int i : modi) add(i,-1);
	}
	return 0;
}
```

---

## 作者：jhdrgfj (赞：0)

感谢此题送我下 1700。
## 解法
考虑 C1 的贪心做法，显然我们会在前缀和 $\min$ 处取绝对值，而且只会取一次绝对值。这是因为整个数列的和是已经确定的，而在前缀和为负数处取绝对值，相当于 $c$ 加上这个数的相反数，我们最终加上的数尽量大，所以这个负数要尽可能小。又因为我们希望这个数尽可能小，所以不会在这之前取绝对值加上任何数。

有了贪心的做法，再考虑计数。显然，如果在某一处 $c+a_i \ge 0$，那么两种操作是等价的，有 $2$ 种选择方案。我们枚举每个前缀和 $\min$ 取绝对值，那么在这个数之前我们不会对负数取绝对值，所以前面的数的贡献为 $2$ 的前缀和  $\ge 0 $ 的数的个数次方。而在当前位置取绝对值后便不会再有前缀和为负数，否则当前位置就不是前缀 $\min$，所以两种操作始终等价，对答案的贡献为 $2$ 的后面的数的个数次方。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[4000005],n,p[240008];
const int mod=998244353;
signed main()
{
	int t;
	cin>>t;
	p[0]=1;
	for (int i=1;i<=200000;i++){
		p[i]=p[i-1]*2%mod;	
	}
	while (t--){
		cin>>n;
		int ct=0,ans=0,sm1=0,sm2=0;
		for (int i=1;i<=n;i++){
			cin>>a[i];
			sm2+=a[i];
			sm1=min(sm2,sm1);
		}
		if (!sm1){         //特判前缀 min>=0 的情况
			cout<<p[n]<<endl;
			continue;
		}
		sm2=0;
		for (int i=1;i<=n;i++){
			sm2+=a[i];
			if (sm2==sm1){
				ans=(ans+p[n-i+ct])%mod;
              //n-i 为后面的数的个数，ct 为前缀和 >=0 的数的个数，前面的选择方案和后面的选择方案任选一种都合法，因此对答案的贡献为 2^(n-i+ct)
			}
			ct+=(sm2>=0) ;
		}
		cout<<ans<<endl;
	} 
}
```

---

## 作者：ttq012 (赞：0)

不会猜结论。每一步结束之后，若当前的前缀和取到了全部前缀和的最小值，则这一步对答案造成了 $2^{n-i+r}$，其中 $r$ 是在这一步操作中前缀和 $\ge0$ 的位置的数量。若全部操作中没有任何一个前缀和 $<0$ 则答案为 $2^n$。考虑这个为什么是对的。

+ 不存在任何一个前缀和使得这个前缀和 $\le 0$。此时对于任意一个位置 $1$ 操作和 $2$ 操作没有任何本质区别。任意一步都可以在 $1$ 操作和 $2$ 操作中任选一个操作执行。
+ 存在一个前缀和使得这个前缀和 $\le0$。因为执行完这一步之后后面不论怎么走答案都不会偏离最大值（参见 C1 的结论），所以说后面的任意一步都可以在 $1$ 操作和 $2$ 操作中任选，即 $2^{n-i}$ 种不同选择；若前面有前缀和 $\ge 0$ 的那么 $1$ 操作和 $2$ 操作没有本质的区别，若有 $r$ 个满足这样条件的则有 $2^r$ 种不同选择。根据乘法原理可知对答案的贡献为 $2^{n-i+r}$。其中 $r$ 可以在枚举的时候扫一遍得出答案。

时间复杂度为 $O(n)$。

**Brute Code**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100;
int a[N],pre[N];
signed main() {
    int T;
    cin>>T;
    while(T--){
        int n,id=-1;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i],pre[i]=pre[i-1]+a[i];
        int mi=0;
        for(int i=n;i;i--)if(pre[i]<mi){
            mi=pre[i];
            id=i;
            // break;
        }
        if(id==-1){
            cout<<pre[n]<<'\n';
            int s=pre[n];
            int cnt=0;
            for(int i=0;i<(1ll<<n);i++){
                int now=0;
                for(int j=1;j<=n;j++)if(i>>(j-1)&1)now+=a[j];
                else now=abs(now+a[j]);
                if (now==s)cnt++;
            }
            cout<<cnt<<'\n';
        }
        else{
            int s=0;
            for(int i=1;i<=n;i++){
                if(i<=id)s-=a[i];
                else s+=a[i];
            }
            cout<<s<<'\n';
            int cnt=0;
            for(int i=0;i<(1ll<<n);i++){
                int now=0;
                for(int j=1;j<=n;j++)if(i>>(j-1)&1)now+=a[j];
                else now=abs(now+a[j]);
                if (now==s)cnt++;
            }
            cout<<cnt<<'\n';
        }
    }
}
```

**Correct Code**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100,mod=998244353;
int a[N],pre[N],bin[N];
signed main() {
    int T;
    cin>>T;
    bin[0]=1;
    for(int i=1;i<N;i++)bin[i]=bin[i-1]*2%mod;
    while(T--){
        int n,id=-1;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i],pre[i]=pre[i-1]+a[i];
        int mi=0,r=0;
        for(int i=1;i<=n;i++)mi=min(mi,pre[i]);
        if(mi==0)cout<<bin[n]<<'\n';
        else{
            int ans=0;
            for(int i=1;i<=n;i++){
                if(pre[i]>=0)r++;
                if(pre[i]==mi)ans=(ans+bin[n-i+r])%mod;
            }
            cout<<ans<<'\n';
        }
    }
}
```

---

## 作者：wly09 (赞：0)

## 题意简述

给定一个长为 $n$ 的数组 $a$，一个初值为 $0$ 的变量 $c$，对于第 $i$ 次操作，您可以选择一种：

+ $c\gets c+a_i$
+ $c\gets |c+a_i|$

求完成所有操作后，使 $c$ 达到最大值 $k$ 的方案数。

答案对 $998244353$ 取模。

## 思路

我们延续[简单版的思路](https://www.luogu.com.cn/article/9lds24yz)，维护每次操作后的最小值和最大值，最终即可得到 $k$。

我们只需在每次计算完最小值和最大值后，检查他们分别是如何扩展来的即可。

注意这种实现有一个坑，如果某次扩展后的最大值与最小值相同，我们需要认为此时达到最小值得方案数为 $0$，否则会重复计算。

取初值：$i=0$ 时，达到最大值 $0$ 的方案数为 $1$，达到最小值 $0$ 的方案数为 $0$。

## Code

```cpp
const int N = 3e5;
const int P = 998244353;
int n;
long long a[N], g[N], l[N], p[N], q[N];
 
void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) {
    array<long long, 4> v;
    v[0] = g[i - 1] + a[i];
    v[1] = abs(v[0]);
    v[2] = l[i - 1] + a[i];
    v[3] = abs(v[2]);
    g[i] = max(v[1], v[3]);
    l[i] = min(v[0], v[2]);
    p[i] = ((v[0] == g[i]) + (v[1] == g[i])) * p[i - 1];
    p[i] += ((v[2] == g[i]) + (v[3] == g[i])) * q[i - 1];
    p[i] %= P;
    if (l[i] == g[i])
      q[i] = 0;
    else {
      q[i] = ((v[0] == l[i]) + (v[1] == l[i])) * p[i - 1];
      q[i] += ((v[2] == l[i]) + (v[3] == l[i])) * q[i - 1];
      q[i] %= P;
    }
  }
  cout << p[n] << '\n';
}
```

---

## 作者：cause_u (赞：0)

## 思路

考虑贪心算法。

不妨设 $sum_i$ 表示 $a_1+a_2+a_3+...+a_i$ 的和。$minn$ 表示数组 $sum$ 中的最小值。

首先，不难发现对于 $sum$ 数组中的每一个元素 $sum_i$ ：

- 如果 $sum_i\ge0$ 那么操作一与操作二所造成的贡献相同，所以我们可以选择执行操作一或执行操作二。
- 如果 $sum_i<0$ 那么为了保证最后取到最大值，只能执行选择执行操作二。

所以，在统计情况数量的时候我们可以使用乘法原理，存下两种操作都可以执行的 $sum_i$ 的个数 $cnt$。此时我们很容易得出答案就是 $2^{cnt}$ 。

但是，我们会发现当 $minn$ 在 $sum$ 数组中重复出现的时候，这样计算会漏掉一些情况。因为对于一个 $i$，如果 $sum_i=minn$，我们可以选择对其执行操作二，那么它后面的所有数**都不会再出现负数**。这意味着再往后的任意元素 $sum_j$ 都可以选择执行操作一或者操作二。所以对于这个 $sum_i$ 它的实际贡献应该为 $2^{cnt}\times 2^{n-i}$，即 $2^{cnt+n-1}$。 

## 注意事项
- 对于每个 $sum_i$，它们的 $cnt$ 是不一样的，因此我们需要开一个数组来存储遍历到不同元素时的 $cnt$。
- $minn$ 可能出现多次，因此要用一个变量存储贡献。
- 因为一共有 $t$ 组数据，所以记得要初始化变量。
- 因为要多次获取 $2^x$，建议使用快速幂避免超时。
- 得出的数据较大，记得开 long long。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 3e5+5,mod = 998244353,inf = 1e9;
int t,n,sum(1),cnt[maxn],b[maxn],minn;
long long fpow(long long a,long long b) {
	if(b == 0)return 1;
	if(b % 2 == 1)return fpow(a,b - 1) * a % mod;
	long long tmp = fpow(a,b / 2);
	return tmp * tmp % mod;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int tt = 1; tt<=t; tt++) {
		sum = 0,minn = 0;
		memset(cnt,0,sizeof cnt); 
		cin>>n;
		for(int i = 1,x; i<=n; i++) {
			cin>>x;
			b[i] = b[i-1] + x;
			cnt[i] = cnt[i-1];
			if(b[i] >= 0)cnt[i]++;
			if(b[i] < minn)minn = b[i];
		}
		for(int i = 1; i<=n; i++) {
			if(b[i]==minn)sum += fpow(2,cnt[i]+n-i),sum%=mod;
		}
		sum %= mod; 
		if(minn == 0) {
			cout<<fpow(2,n)<<'\n';
			continue;
		}
		cout<<sum<<'\n';
	}
	return 0;
}
```

---

