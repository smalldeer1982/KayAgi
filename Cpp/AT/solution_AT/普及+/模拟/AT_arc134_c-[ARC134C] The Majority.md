# [ARC134C] The Majority

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc134/tasks/arc134_c

$ 1 $ から $ K $ の番号がついた $ K $ 個の箱があります。はじめ、箱は全て空です。

すぬけ君は $ 1 $ 以上 $ N $ 以下の整数が書かれたボールをいくつか持っています。 すぬけ君が持っているボールのうち、$ i $ が書かれたものは $ a_i $ 個あります。 同じ整数が書かれたボール同士は区別できません。

すぬけ君は持っている全てのボールを箱にしまうことにしました。 すぬけ君はどの箱についても $ 1 $ と書かれたボールが過半数を占めるようにしたいです。 過半数を占めるとは、$ 1 $ と書かれたボールの個数がそれ以外のボールの個数より多いことを意味します。

そのようなしまい方の個数を $ 998244353 $ で割ったあまりを求めてください。

$ 2 $ つのしまい方が異なるとは、$ 1\ \leq\ i\ \leq\ K,\ 1\ \leq\ j\ \leq\ N $ を満たす整数の組 $ (i,j) $ であって、箱 $ i $ に入っている $ j $ が書かれたボールの個数が異なるようなものが存在することをいいます。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 200 $
- $ 1\ \leq\ a_i\ <\ 998244353 $

### Sample Explanation 1

\- $ 1 $ と書かれたボールが過半数を占めるようなしまい方は $ 2 $ 通りあります。 - 例えば $ 1 $ と書かれたボールを箱 $ 1 $ に $ 2 $ 個、箱 $ 2 $ に $ 1 $ 個入れ、$ 2 $ と書かれたボールを箱 $ 1 $ に $ 1 $ 個入れたとき条件を満たします。

### Sample Explanation 2

\- 条件を満たすようなしまい方が存在しないこともあります。

### Sample Explanation 3

\- $ 998244353 $ で割ったあまりを求めるのを忘れずに。

## 样例 #1

### 输入

```
2 2
3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1
1 100```

### 输出

```
0```

## 样例 #3

### 输入

```
20 100
1073813 90585 41323 52293 62633 28788 1925 56222 54989 2772 36456 64841 26551 92115 63191 3603 82120 94450 71667 9325```

### 输出

```
313918676```

# 题解

## 作者：ln001 (赞：3)

## 题意
$n$ 种小球，每种有 $a_i$ 个，同种小球本质相同。

有 $k$ 个本质不同的盒子，现在要将所有的小球都放到盒子里，并要求**在每个盒子中**，种类为 $1$ 的小球出现次数**超过**该盒子中小球个数的一半。

求方案数，结果对 $998244353$ 取模。

## 做法
设第 $ i $ 个盒子中装有 $ b_i $ 个编号不是 $ 1 $ 的小球。要使方案合法当且仅当该盒子放**至少** $ b_i + 1 $ 个编号为 $ 1 $ 的小球。

有 $ \sum\limits_{j = 1}^k (b_j + 1) = \sum\limits_{j = 1}^k b_j + \sum\limits_{j = 1}^k 1 = \sum\limits_{i = 2}^n a_i + k $。即对于任意一种放置方案，有 $\sum\limits_{i = 2}^n a_i + k$ 个编号为 $ 1 $ 的小球放置位置与方案的合法性有关，不可被移动。其余编号为 $ 1 $ 的小球与其他小球可随意放置。

利用[隔板法](https://zhuanlan.zhihu.com/p/106135565#:~:text=%E7%94%B1%E4%BA%8E%E9%9A%94%E6%9D%BF%E6%B3%95,%E4%B9%9F%E5%B0%B1%E8%BF%8E%E5%88%83%E8%80%8C%E8%A7%A3%E4%BA%86%E3%80%82)对每个小球计算方案数即可。

[Code](https://vjudge.net/solution/55592613/mFsr0FQbTdK5j8iNgx26)

---

## 作者：binbin_200811 (赞：2)

# ARC134C The Majority

link：[【ARC134C】 The Majority](https://www.luogu.com.cn/problem/AT_arc134_c)

小清新数学题。（反正我做不出来）

#### 简要题意

有 $K$ 个箱子，编号为 $1$ 到 $K$ 的箱子。起初，所有箱子都是空的。

史努克有一些球，球上写着 $1$ 到 $N$ 的整数。在这些球中，有 $a_i$ 个球上写着数字 $i$。带有相同数字的球无法区分。

史努克决定把他所有的球都放进箱子里。他希望每个箱子里写着数字 $1$ 的球都是多数。换句话说，每个箱子里，写着数字 $1$ 的球的数量应该多于其他球的数量，即占到一半以上。

找出这样放置球的方法数，结果对 $998244353$ 取模。

当存在一对整数 $(i,j)$ 满足 $1\leq i\leq K,1\leq j\leq N$，并且在第 $i$ 个箱子中，写着数字 $j$ 的球的数量不同时，两种方式被认为是不同的。

#### 思路

把每个 $1$ 号球先和每个不是 $1$ 号球配对一下，再在每个盒子里都放 $1$ 个 $1$ 号球。

这样子剩下了 $a_1-\sum\limits_{i=2}^na_i-k$ 个 $1$ 号球。

同时保证了 $1$ 号球是多数的条件。

现在使 $a_1-\sum\limits_{i=2}^na_i-k \to a_1$。

接下来球都可以任意放，对于单个种类的球看做有 $a_i$ 个球，放到 $k$ 个盒子里，允许空放的问题。

这个经典问题的答案是 $C_{a_i+k-1}^{k-1}$。

最终答案是
$$
\prod_{i=1}^n C_{a_i+k-1}^{k-1}
$$

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 998244353

const int maxn=1e5+5;

ll n,k,sum,ans;
ll a[maxn],fac[maxn],inv[maxn];

ll ksm(ll x,ll y)
{
    ll sum=1;
    for(;y;y/=2,x=x*x%mod) if(y&1) sum=sum*x%mod;
    return sum;
}
ll C(ll n,ll m)
{
    if(n<=m) return 1;
    ll sum=inv[m];
    for(ll i=n-m+1;i<=n;i++) sum=sum*i%mod;
    return sum;
}

int main()
{
    scanf("%lld%lld",&n,&k);

    fac[0]=1;
    for(int i=1;i<=k;i++) fac[i]=fac[i-1]*i%mod;
    inv[k]=ksm(fac[k],mod-2);
    for(int i=k-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;

    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=2;i<=n;i++) sum+=a[i];

    a[1]=a[1]-sum-k;
    if(a[1]<0)
    {
        printf("0");
        return 0;
    }

    ans=1;
    for(int i=1;i<=n;i++)
        ans=ans*C(a[i]+k-1,k-1)%mod;
    printf("%lld",ans);
}
```

---

## 作者：Pretharp (赞：2)

upd on 2024.1.5：将之前写反的、写错的式子更正了。

## 思路

我们不妨先将所有编号为 $1$ 的和编号为其它一一配对。我们将配对好的球按对放入盒子中，方案数为：

$$
\prod\limits^N_{i=2}\binom{a_i+K-1}{K-1}
$$

这里可以用插板法理解，其中 $a_i+K-1$ 可以理解为板子不必插满 $K-1$ 个。

此时，我们已经做到每个盒子之中编号为 $1$ 的球的数量等于编号不为 $1$ 的球的数量。我们只要再将剩下的（即之前没有配对的）编号为 $1$ 的球放入盒子中（其中每个盒子至少放入一个），方案数为：

$$
\binom{(a_1-\sum\limits^N_{i=2}a_i)-1}{K-1}
$$

同样可以用插板法理解。

所以最终答案为：

$$
\binom{(a_1-\sum\limits^N_{i=2}a_i)-1}{K-1}\prod\limits^N_{i=2}\binom{a_i+K-1}{K-1}
$$

时间复杂度 $O(NK)$。

## 代码：

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define db long double
#define endl '\n'
#define pii pair<int,int>
#define fir first
#define sec second
#define pb push_back
#define mijacs using
#define so namespace
#define lovely std
mijacs so lovely;
const int INF2=0x3f3f3f3f;
const int mod1=998244353;
const int mod2=1e9+7;
const ll INF1=1e18;
const int N=1e5+5,K=205;
int n,k,a[N],sum,f[K],ans=1;
int qmi(int a,int k)
{
	int res=1;
	while(k){
		if(k&1) (res*=a)%=mod1;
		(a*=a)%=mod1;
		k>>=1;
	}
	return res;
}
int C(int x,int y)
{
	int res=1;
	for(int i=x-y+1;i<=x;i++){
		(res*=i)%=mod1;
	}
	(res*=qmi(f[y],mod1-2))%=mod1;
	return res;
}
signed main()
{
	//freopen("input.in","r",stdin);
	//freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum=sum+a[i];
	}
	sum=a[1]-(sum-a[1]);
	if(sum<k) return cout<<0<<endl,0;
	f[0]=1;
	for(int i=1;i<=k;i++){
		f[i]=f[i-1]*i%mod1;
	}
	ans=C(sum-1,k-1)%mod1;
	for(int i=2;i<=n;i++){
		ans=(ans*C(a[i]+k-1,k-1))%mod1;
	} 
	return cout<<ans<<endl,0;
}
```

---

## 作者：zhangjiahe__ (赞：1)

# 思路：

除第一种角色外，都可以视作一种角色，所以把他们的数量相加。

考虑将第一种角色和其余角色如何配对，可以利用插板法进行思考。公式为：

 $\prod_{i=2}^{n} \binom {a_i+K-1} {K-1}$

已经将辅助角色配完，还有一些待配的一角色，也可以用插板法解决，配对方案数为：

 $\binom {({a_1 - \sum_{i=2}^{n} a_i)-1}} {K-1}$

综上，将两种方案数相乘，即为最终答案。

设 $p$ 为模数 $=998244353$，

计算时间复杂度为 $O(\log p \times Kn)$。

# 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, a[100005], p = 998244353, dp[305], els, ans;
long long fastpow(long long a, long long b)
{
	if(b == 1) return a;
	if(b == 0) return 1;
	if(b % 2 == 0)
	{
		long long t = fastpow(a, b / 2) % p;
		return (t % p) * (t % p) % p;
	}
	else
	{
		long long t = fastpow(a, b / 2) % p;
		return (t % p) * (t % p) % p * (a % p) % p;
	}
}
long long C(long long n, long long m)
{
    long long res = 1;
    for(int i = n-m+1; i <= n; i++)
    {
        res *= i;
        res %= p;
    }
    res *= fastpow(dp[m], p-2);
    return res % p;
}
int main()
{
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        els += a[i]; //els为
    }
    if(2*a[1]-k < els) //配不开
    {
        cout << 0;
        return 0;
    }
    els = 2*a[1]-els;
    dp[0] = 1;
    for(int i = 1; i <= k; i++)
        dp[i] = dp[i-1]*i%p;
    ans = C(els-1, k-1) % p;
    for(int i = 2 ; i<= n; i++)
    {
        ans *= C(a[i]+k-1, k-1);
        ans %= p;
    }
    cout << ans;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{40}$ 篇题解。

# $\mathbf{0x01}$ 承

有 $n$ 种角色，分别为 $a_1,a_2,a_3\cdots a_n$，还有 $k$ 个副本，记第 $i$ 每种角色使用数量为 $c_i$，每个副本需要的角色中，$c_{a_1}>c_{a_2}+c_{a_3}+\cdots +c_{a_n}$，要用完全部角色，有多少种方式？

# $\mathbf{0x02}$ 转

一道非常好的组合计算题（以下简称 $a_1$ 种角色为主 C，其余角色为辅助）。

很显然当一个副本里面 $c_{a_1}=c_{a_2}+c_{a_3}+\cdots +c_{a_n}$ 时可以认为这个副本没有人，还需要一个主 C 才能满足条件；而如果我们连上面情况都不能满足，即 $c_{a_1}<k+c_{a_2}+\cdots c_{a_n}$ 时（加 $k$ 是因为每个副本在主 C 数与辅助数量相等时还要有一个主 C），就没有方案可行，输出 $0$；否则对于主 C 和辅助配对完之后的结果，剩余的主 C 数量 $c_{a_1}-c_{a_2}-c_{a_3}-\cdots c_{a_n}$ 可以放到 $k$ 个副本里面且每个副本至少有一个主 C，这一点可以用隔板法解决，答案为：$\prod_{i = 2}^{n}C^{k-1}_{a_i+k-1}$。

# $\mathbf{0x03}$ 合

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll n,k,tmp,x=0,y=0,a[100005];
ll ksm(ll b,ll e=mod-2) {
	ll a=1;
	while(e) {
		if(e%2)(a*=b)%=mod;
		(b*=b)%=mod,e/=2;
	}
	return a;
}
ll C(ll n,ll m) {
	if(m>n/2)m=n-m;
	if(n<m)return 0;
	ll r1=1,r2=1;
	for(ll i=0; i<m; i++)(r1*=(n-i))%=mod,(r2*=(i+1))%=mod;
	return r1*ksm(r2,mod-2)%mod;
}
int main() {
	cin>>n>>k;	
	for(ll i=1;i<=n;i++){
		if(i==1)cin>>a[i];
		if(i>=2){
			cin>>a[i];
			y+=a[i];
		}
	}
	if(a[1]<y+k) {
		cout<<0;
		return 0;
	}
	a[1]-=(y+k);
	//put x balls into k boxes
	ll ans=1;
	for(ll i=1; i<=n; i++) {
		ans=ans*(C(a[i]+k-1,k-1)%mod)%mod;
	}
	cout<<(ans%mod+mod)%mod;
}
```

---

