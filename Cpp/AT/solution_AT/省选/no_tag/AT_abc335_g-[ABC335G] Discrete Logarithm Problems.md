# [ABC335G] Discrete Logarithm Problems

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc335/tasks/abc335_g

$ N $ 個の整数 $ A_1,\ldots,A_N $ と素数 $ P $ が与えられます。 次の条件をともに満たす整数の組 $ (i,j) $ の個数を求めてください。

- $ 1\ \leq\ i,j\ \leq\ N $
- ある正整数 $ k $ が存在し、$ A_i^k\ \equiv\ A_j\ \bmod\ P $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ <\ P $
- $ 2\ \leq\ P\ \leq\ 10^{13} $
- $ P $ は素数
- 入力は全て整数
 
### Sample Explanation 1

$ (1,1),(1,2),(1,3),(2,2),(3,3) $ の $ 5 $ 組が条件を満たします。 例えば $ (1,3) $ については、$ k=9 $ とすると $ A_1^9\ =\ 512\ \equiv\ 5\ =\ A_3\ \bmod\ 13 $ となります。

## 样例 #1

### 输入

```
3 13
2 3 5```

### 输出

```
5```

## 样例 #2

### 输入

```
5 2
1 1 1 1 1```

### 输出

```
25```

## 样例 #3

### 输入

```
10 9999999999971
141592653589 793238462643 383279502884 197169399375 105820974944 592307816406 286208998628 34825342117 67982148086 513282306647```

### 输出

```
63```

# 题解

## 作者：Purslane (赞：7)

# Solution

标题上面说了这是离散对数问题。于是我们不妨找出原根，然后用 BSGS 求出每个数的离散对数。这样等价于 $k \log a_i \equiv \log a_j \pmod {p-1}$。考虑 $(\log a_i,p-1)=d$，那么等价于 $d \mid \log a_j$。而这个实际上等价于 $d \mid (p-1,\log a_j)$。于是令 $b_j = (p-1,\log a_j)$。我们只需统计 $1 \le i < j \le n$ 且 $b_i \mid b_j$。的数量。不妨将 $p-1$ 质因数分解，这样很容易比较快速的找到 $b_j$ 的所有因数。（事实上，所有的 $b$ 只有 $d(p-1) \le 1.1 \times 10^4$ 种情况。很容易找所有倍数关系，而这种倍数关系显然不是很密集。）

但是很遗憾，BSGS 是复杂度是错的。于是我们考虑求出每个数对 $p$ 的阶，假设这是 $t$，那么说明 $t \log a_i \equiv 0 \pmod {p-1}$，显然有 $t = \dfrac{p-1}{(p-1,\log a_i)}$。
 
然后考虑怎么求阶。我们枚举 $p-1$ 的每个素因子，看能不能除掉即可。

这样你最多进行 $O(n\log^2 p)$ 次乘法操作。我也许感觉能过。如果假了别嘲笑我。

好它过了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,p,a[MAXN];
int qpow(__int128 base,int p,int mod) {
	__int128 ans=1;
	while(p) {
		if(p&1) ans=ans*base%mod;
		base=base*base%mod,p>>=1;	
	}
	return ans;
}
vector<int> frac;
map<int,int> mp;
int calc_b(int v) {
	int ans=p-1;
	for(auto id:frac) if(qpow(v,ans/id,p)==1) ans/=id;
	return (p-1)/ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>p; ffor(i,1,n) cin>>a[i];
	int v=p-1;
	ffor(i,2,v/i) while(v%i==0) frac.push_back(i),v/=i;
	if(v) frac.push_back(v);
	sort(frac.begin(),frac.end());
	ffor(i,1,n) mp[calc_b(a[i])]++;
	int ans=0;
	for(auto pr1:mp) for(auto pr2:mp) if(pr1.first%pr2.first==0) ans+=pr1.second*pr2.second;
	cout<<ans;
	return 0;
}
```

---

## 作者：_jimmywang_ (赞：5)

杀到 g 面前挂了。还在考虑原根 $a_i \equiv g^{k_i}\pmod p$ ，然后发现不会批量 BSGS。会的大佬教。

首先找出最小的 $k_i$ 使 $a_i^{k_i}\equiv 1 \pmod p$。（就是 $a_i$ 的阶）容易发现 $k_i$ 一定是 $p-1$ 的因数，那么直接找出 $p-1$ 的质因数然后依次往下除。

这样一来，$a_i^x\equiv a_j \pmod p$ 就可以转化为 $a_i^{xk_i}\equiv a_j^{k_i} \pmod p$，即 $1\equiv a_j^{k_i} \pmod p$。

所以等价于 $k_i$ 是 $k_j$ 的倍数，做完了。

复杂度差不多是 $O(d(p-1)^2\log)$，而范围内最大 $d(p-1)$ 大概 $1\times 10^4$，能跑。

---

## 作者：TLE_Automat (赞：3)

## 题目链接

[https://atcoder.jp/contests/abc335/tasks/abc335_g](https://atcoder.jp/contests/abc335/tasks/abc335_g)

## 题目大意

给定 $n$ 个正整数 $a_1,a_2,\cdots,a_n$ 和一个素数 $P$。求满足以下条件的二元组 $(i,j)$ 的个数。

- $1\leq i,j\leq N$。

- 存在正整数 $k$ ，使得 $A_i^k\equiv A_j\pmod P$。

## 数据范围

- $1\le n\le 2\times 10^{5}$
- $1\le a_i < P$ 
- $2 < P \le 10^{13}$ 且 $P$ 是素数 

## 解题思路

考虑同余式 $x^k \equiv y \pmod P$ 能推出什么结论。

令 $\delta_{P}(x)$ 表示 $x$ 在模 $P$ 意义下的阶，因为 $x^k$ 和 $y$ 在模 $P$ 意义下同余，所以一定有 $\delta_{P}(x^{k}) = \delta_P(y)$。

其实以上的转化是我看题解看到的，至于应该怎么想才能自然地想到这一步，感觉需要一定的数学直觉，并且需要靠多做题积累经验。 

根据阶的性质，有 $\delta_{P}(x^{k}) = \displaystyle\frac{\delta_{P}(x)}{\gcd(k, \delta_{P}(x))}$，所以可以得到 $\delta_{P}(x) = \gcd(k, \delta_{P}(x)) \cdot \delta_{P}(y)$，所以我们能推出一个必要条件

$$
\begin{aligned}

\exists{k \in \mathbb{N}} , x^{k} \equiv y \pmod P \implies \delta_{P}(y) \mid \delta_{P}(x) 

\end{aligned}
$$

那么该条件的充分性是否成立呢。

- **lemma 1**

  如果 $ta \equiv tb \pmod {tc}$，则 $a \equiv b \pmod c$ 成立，其中 $t,a,b\in \mathbb{N_{+}}$。

  证明非常简单，只需要把取模运算的表达式写出来即可证明。

假设 $g$ 为 $P$ 的一个原根，根据原根的性质，一定存在 $e_1$ 和 $e_2$ 使得 $g^{e_1} \equiv x \pmod P$，$g^{e_2} \equiv y \pmod P$，两边取离散对数有 $e_{1} \equiv \operatorname{ind}_{g}(x) \pmod{P-1}$，$e_{2} \equiv \operatorname{ind}_{g}(y) \pmod{P - 1}$。我们要证 $\exists{k \in \mathbb{N}}, x^{k} \equiv y \pmod P$，即证 $\exists{k \in \mathbb{N}}, ke_{1} \equiv e_2 \pmod{P-1}$。

根据条件有

$$
\begin{aligned}

\delta_{P}(y) \mid \delta_{P}(x) \iff\delta_{P}(g^{e_2}) \mid \delta_{P}(g^{e_1}) \iff \displaystyle\frac{P-1}{\gcd(e_2, P-1)} \mid \displaystyle\frac{P-1}{\gcd(e_1, P-1)} \iff \gcd(e_1, P-1) \mid \gcd(e_2, P-1)

\end{aligned}
$$


 令 $t = \gcd(e_1, P - 1)$，根据 **lemma 1** 和要证的式子 $ke_{1}\equiv e_2 \pmod{P-1}$，有

$$
\begin{aligned}

k\frac{e_1}{t} \equiv \frac{e_{2}}{t} \pmod{\frac{P-1}{t}}

\end{aligned}
$$

因为 $\displaystyle\frac{e_{1}}{t}$ 与 $\displaystyle\frac{P-1}{t}$ 互质，所以有

$$
\begin{aligned}

k\equiv \frac{e_{2}}{t} \cdot \left(\frac{e_1}{t}\right)^{-1} \pmod{\frac{P-1}{t}}

\end{aligned}
$$

 所以条件的充分性成立，即

$$
\begin{aligned}

\exists{k \in \mathbb{N}} , \text{ }x^{k} \equiv y \pmod P \implies \delta_{P}(y) \mid \delta_{P}(x) 

\end{aligned}
$$

接下来，考虑如何求一个数 $a$ 在模 $P$ 意义下的阶 $\delta_{P}(a)$。因为 $\delta_{P}(a) \mid (P - 1)$，并且若 $\delta_{P}(a) \mid b$，那么 $x^{b} \equiv 1 \pmod P$ 成立，所以可以先将 $P - 1$ 质因数分解，初始时令 $b = P - 1$，每次选取一个质因数 $p$，判断 $x ^ {\frac{b}{p}} \equiv 1 \pmod P$ 是否成立，成立则将 $p$ 除掉，不成立就取下一个质因数做相同的操作，这样最后得到的 $b$ 就是 $a$ 的阶。对于给定序列的每一个 $a_i$ 做一遍上述操作的时间复杂度为 $O(\sqrt{P} + n \log^{2} P)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ok46vsq.png)

根据上表，我们发现 $P - 1$ 的约数个数的级别不超过 $10^4$，所以可以直接 $O(\operatorname{d}(P)^{2})$ 计算 $\delta_{P}(a_i)$ 对答案的贡献。

所以总时间复杂度为 $O(\sqrt{P} + n \log^{2} P + \operatorname{d}(P)^{2})$，时限为 $5\text{s}$，足够通过本题。

## 参考代码

[https://atcoder.jp/contests/abc335/submissions/49356980](https://atcoder.jp/contests/abc335/submissions/49356980)

---

## 作者：EuphoricStar (赞：2)

考虑若我们对于每个 $a_i$ 求出来了使得 $g^{b_i} \equiv a_i \pmod P$ 的 $b_i$（其中 $g$ 为 $P$ 的原根），那么 $a_i^k \equiv a_j \pmod P$ 等价于 $kb_i \equiv b_j \pmod{P - 1}$，有解的充要条件是 $\gcd(b_i, P - 1) \mid b_j$。

显然我们不可能对于每个 $a_i$ 都求出来 $b_i$。注意到我们只关心 $c_i = \gcd(b_i, P - 1)$，而 $c_i$ 为满足 $a_i^{c_i} \equiv 1 \pmod P$ 的最小正整数。若求出 $c_i$ 则等价于统计 $c_i \mid c_j$ 的对数。于是问题变成求出 $c_i$。

因为我们一定有 $a_i^{P - 1} \equiv 1 \pmod P$，所以 $c_i$ 一定为 $P - 1$ 的因数。所以我们初始令 $c_i = P - 1$，然后对 $P - 1$ 分解质因数，依次让 $c_i$ 试除 $P - 1$ 的每个质因子，判断除完后是否还有 $a_i^{c_i} \equiv 1 \pmod P$ 即可。这部分复杂度大概是 $O(n \log^2 P)$ 的。

问题还剩下统计 $c_i \mid c_j$ 的对数。因为 $c_i$ 为 $P - 1$ 的因数，所以我们可以做一遍 Dirichlet 后缀和求出 $f_x$ 表示满足 $x \mid c_i$ 的 $i$ 的个数。最后遍历 $c_i$ 统计即可。

总时间复杂度大概是 $O(n \log^2 P + m \log m \log P)$，其中 $m$ 为 $P - 1$ 因数个数。

[code](https://atcoder.jp/contests/abc335/submissions/49256589)

---

## 作者：Starrykiller (赞：2)


数论好题。第一次做到和阶有关的题目。

首先是一个定义。

在模 $p$ 意义下，$x$ 的**阶**定义为最小的正整数 $m$，使得 $x^m\equiv 1\pmod p$，记为 $\operatorname{ord}(x)=m$。若没有，则称 $x$ 阶为无穷。

不难发现 $x$ 在模 $p$ 意义下阶不为无穷的充要条件是 $\gcd(x,p)=1$。由于 $p$ 为素数且本题中 $x\in [1,p-1]$，所以我们可以省略讨论。

我们有如下的引理。

**Lemma 1** 模 $p$ 意义下，$\operatorname{ord}(x)\mid p-1$。

**Lemma 2** 存在正整数 $k$，使得 $A_i^k\equiv A_j\pmod p\iff \operatorname{ord}(A_j)\mid \operatorname{ord}(A_i)$。

以上都可以用群论关于子群的部分证明，这里粗略地带过（可能有错误）。所有与 $p$ 同余的元素构成一个模 $p$ 意义下的乘法群，记为 $(\mathbb{Z}/p\mathbb{Z})^*$，而 $x$，$x^2$，$\cdots$，$x^n$ 构成 $(\mathbb{Z}/p\mathbb{Z})^*$ 的子群，由 Langrange 定理可以知道，子群的阶必为（母）群的阶的因数。

本题中 $P\leq 10^{13}$，由于 $\operatorname{ord}(x)$ 只会是 $P-1$ 的因数（其个数最大是 $10^4$ 数量级的），因此可以对于每一个 $\operatorname{ord}(x)$ 算贡献。

最后只需要算出 $\operatorname{ord}(x)$ 就可以了。具体地，初始化 $m=P-1$，对于所有的 $p\in \mathbb{P}$，且 $p\mid m$，$x^{\frac{m}{p}}\equiv 1\pmod P$，令 $m\gets \frac{m}{p}$。由于 $P$ 的因数是 $\log P$ 级别的，而快速幂也是 $\log P$ 的，因此单次求复杂度为 $\mathcal{O}(\log ^2 P)$。

综上，我们在 $\mathcal{O}(n\log^2 P+\left[d(P)\right]^2)$ 的时间内解决了本题。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long 

constexpr int MAXN=2e5+10;

int a[MAXN], b[MAXN], p, n;
int prime[MAXN*20], tot, v[MAXN*20],
    d[MAXN], dtot;

int qpow(int a, int n) {
    int res=1;
    while (n) {
        if (n&1) res=__int128(res)*a%p;
        a=__int128(a)*a%p; n>>=1;
    }
    return res;
}

int xp[MAXN], xtot;
void euler(int n) {
    for (int i=2; i<=n; ++i) {
        if (!v[i]) v[i]=prime[++tot]=i;
        for (int j=1; j<=tot&&i*prime[j]<=n; ++j) {
            if (prime[j]>v[i]) break;
            v[i*prime[j]]=prime[j];
        }
    }
}

int ord(int a) {
    int ans=p-1;
    for (int i=1; i<=xtot; ++i)
        if (qpow(a,ans/xp[i])==1)
            ans/=xp[i];
    return ans;
}

map<int,int> mp;

int ans=0, sum=0, cnt=0; 

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    euler(4e6);
    cin>>n>>p;
    int cur=p-1;
    for (int i=1; i<=tot&&prime[i]<=sqrt(cur); ++i) {
        while (cur%prime[i]==0) cur/=prime[i], xp[++xtot]=prime[i];
    }
    if (cur>1) xp[++xtot]=cur;
    sort(xp+1,xp+1+xtot);
    for (int i=1; i<=n; ++i) {
        cin>>a[i];
        mp[b[i]=ord(a[i])]++;
    }
    for (auto [u,v]: mp) 
        for (auto [u2,v2]: mp)
            if (u%u2==0)
                ans+=v*v2;
    cout<<ans<<'\n';
}
```

---

## 作者：lfxxx (赞：2)

首先，因为 $P$ 是质数，所以一定存在原根 $g$。

假若有 $x^k \equiv y \pmod{m}$ 那么令 $x=g^{x_1},y=g^{y_1}$。

有 $g^{k \times x_1} \equiv g^{y_1}$。

则 $k \times x_1 - y_1 = m \times (P-1)$。

所以 $k \times x_1 - m \times (P-1) = y_1$。

这个方程有解说明 $\gcd(x_1,P-1) \mid y_1$。

这等价于 $\gcd(x_1,P-1) \mid \gcd(y_1,P-1)$。

而我们有 $\gcd(x,P-1) = \frac{P-1}{a_x}$ 这里 $a_x$ 是 $x$ 的阶。

求出每个数的阶可以用试除法在 $O(n \log^2 P)$ 的时间内求出。

接下来的问题变成了找倍数关系，不难发现不同的阶的数量很少，所以把相同的合并起来然后 $O(\tau(P-1)^2)$ 的复杂度内求出答案，这里手算一下发现大概要算 $10^8$ 次所以可过。放一下主函数。

```cpp
signed main(){
    //freopen("G.in","r",stdin);
    //freopen("G.out","w",stdout);
    read(n);
    read(P);
    int T=P-1;
    while(T!=1&&Miller_Rabin(T)!=true){
        Ans=0;
        Fac(T);
        prime.push_back(Ans);
        T/=Ans;
    }
    if(T!=1) prime.push_back(T);
    sort(prime.begin(),prime.end(),cmp);
    for(int i=1;i<=n;i++){
        int x;
        read(x);
        int A=P-1;
        for(int y:prime){
            while(A%y==0&&qpow(x,A/y)==1) A/=y;
        }
        a[i]=A;
    }
    sort(a+1,a+n+1,cmp);
    b[++tot].first=a[1];
    b[tot].second=1;
    for(int i=2;i<=n;i++){
        if(a[i]!=b[tot].first){
            b[++tot].first=a[i];
            b[tot].second=1;
        }else b[tot].second++;
    }
    int ans=0;
    for(int i=1;i<=tot;i++){
        for(int j=1;j<=tot;j++){
            if(b[i].first%b[j].first==0){
                ans+=b[i].second*b[j].second;
            }
        }
    }
    write(ans);
    return 0;
}

```




---

## 作者：_fairytale_ (赞：1)

考虑对每个 $a_i$，求出其在模 $P$ 意义下的阶 $q_i$。

因为 $P$ 是素数，根据费马小定理，显然有 $a_i^{P-1}\equiv 1\pmod P$，于是 $q_i | (P-1)$。

枚举 $(P-1)$ 的素因子 $p$，判断 $a_i^{\frac{P-1}{p}}\equiv 1\pmod P$ 是否成立，如果是就除掉，每次用 $\log P$（快速幂）的代价除掉 $(P-1)$ 的一个素因子，因此复杂度大概是 $\mathcal O(\log^2P)$ 级别的。

求出 $\{q_i\}$ 之后，考虑 $a_i^k\equiv a_j\pmod P\iff a_i^{kq_i}\equiv a_j^{q_i}\pmod P\iff 1\equiv a_j^{q_i}\pmod P\iff q_j|q_i$，于是统计 $q_j|q_i$ 的 $(i,j)$ 对数即可。因为 $q_i|(P-1)$，所以枚举 $(P-1)$ 的所有约数统计即可。

复杂度 $\mathcal O(n\log^2 P+d(P-1)^2)$。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define ll long long
#define emp emplace_back
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define maxn 201000
int n;
ll P,mod;
ll a[maxn];
vector<ll>pfac;
template<typename Tp>
ll qp(__int128 x,Tp y) {
	assert(y>=0);
	__int128 res=1;
	while(y) {
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
ll getord(ll x){
	ll res=P;
	for(ll p:pfac)while(res%p==0&&qp(x,res/p)==1)res/=p;
	return res;
}
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>mod;
	rep(i,1,n){
		cin>>a[i];
		a[i]%=mod;
	}
	P=mod-1;
	for(int i=2;1ll*i*i<=P;++i){
		if(P%i==0){
			pfac.emp(i);
			while(P%i==0)P/=i;
		}
	}
	if(P!=1)pfac.emp(P);
	P=mod-1;
	gp_hash_table<ll,int>cnt;
	rep(i,1,n)++cnt[getord(a[i])];
	vector<ll>fac;
	for(int i=1;1ll*i*i<=P;++i){
		if(P%i==0){
			if(1ll*i*i!=P)fac.emp(P/i);
			fac.emp(i);
		}
	}
	ll ans=0;
    for(ll p:fac)for(ll q:fac)if(p%q==0)ans+=1ll*cnt[p]*cnt[q];
    cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

后文，设群 $G = \mathbb F_p^\times$，$p - 1$ 的质因数分解 $p_1^{e_1}p_2^{e_2}\dots$。

## 群中的阶

在群 $G$ 中，对于一个元素 $x$，其阶 $|x|$ 是 $|G|$ 的因数。注意到如下事实：

$\textbf{Lemma.}$ 若 $x^{a} = x^b = 1$，则 $x^{\gcd(a,b)}=1$。

$\textbf{Proof.}$ 因为 $x^a = x^b = 1$，所以 $x^{ma} = x^{nb} = 1~(\forall m,n)$，也即 $x^{ma+nb}=1~(\forall m, n)$，根据 Bézout 定理，$x^{\gcd(a,b)}=1$。

取 $k = \dfrac{|G|}{|x|}$，则设 $k = p_1^{f_1} p_2^{f_2} \dots$。由于 $|x|$ 是最小的使得 $x^a = 1$ 的 $a$，所以 $k$ 是最大的使得 $x^{|G|/k} = 1$ 的 $k$。根据引理，如果 $x^{|G|/p}=x^{|G|/q}=1$，那么 $x^{|G|/\mathrm{lcm}(p,q)}=1$。当 $p$ 和 $q$ 都形如 $p_i^{m_i}$（$p,q$ 对应的 $p_i$ 不同）时，简化为 $x^{|G|/pq}=1$。所以 $x^{|G|/k} = 1$ 当且仅当 $x^{|G|/p_i^{f_i}} = 1~(\forall i)$。

于是我们得到了如下算法：对于每一个 $i$，枚举 $j$ 的值，然后看 $x^{|G|/p_i^{j}}$ 是否为 $1$，如果是 $1$，那么继续枚举，否则最大的 $f_i$ 就等于 $j - 1$。时间复杂度为 $\Theta(\sum e_i) = \mathrm O(\log p)$。

## 转化

$\textbf{Lemma.}$ $\operatorname{ind}_a b$ 存在当且仅当 $|b|$ 能被 $|a|$ 整除。

$\textbf{Proof.}$ 由于有限域的乘法群是循环群，所以 $G \cong \mathbb Z_{|G|}$，这样这个引理就可以通过这个同构等价地变为 $a'x=b'$ 有解当且仅当 $\gcd(b',|G|) \mid \gcd(a',|G|)$。这样就变成了一个简单的初等数论定理。

现在我们算出每一个元素的阶，就能求出答案了，由于 $\mathrm d(|G|) \le \max_{\mathrm d}(10^{13}) = 10\ 752$，所以可以把它塞进桶中然后暴力枚举。这样的复杂度是能过的。利用 Dirichlet 前缀和可以进一步优化。

---

## 作者：WorldMachine (赞：0)

直观的想法是求出 $\log a$ 然后判倍数关系，不同的 $\log a$ 差不多是 $10^4$ 级别的直接暴力判即可。不知道用批量 BSGS 能不能过，可能可以但还要找原根不是很想写。

改求每个元素的阶 $\delta_p(a)$，那么 $a^k\equiv b\pmod p\Rightarrow a^{\delta_p(a)k}\equiv b^{\delta_p(a)}\pmod p\Rightarrow b^{\delta_p(a)}\equiv 1\pmod p$，也即 $\delta_p(b)|\delta_p(a)$。倍数关系还是暴力判即可。

阶一定是 $\varphi(p)$ 的因子，求的时候直接枚举 $\varphi(p)$ 的每个素因子看能否除掉即可。代码是很好写的。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef __int128 lll;
int n;
ll a, p, tp, ans;
vector<ll> fac;
gp_hash_table<ll, int> mp;
ll qpow(ll a, ll b) {
	ll c = 1;
	while (b) {
		if (b & 1) c = (lll)c * a % p;
		a = (lll)a * a % p, b >>= 1;
	}
	return c;
}
ll ord(ll a) {
	ll d = p - 1;
	for (ll x : fac) while (!(d % x) && qpow(a, d / x) == 1) d /= x;
	return (p - 1) / d;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> p, tp = p - 1;
	for (ll i = 2; i * i <= tp; i++) {
		if (tp % i) continue;
		fac.emplace_back(i);
		while (!(tp % i)) tp /= i;
	}
	if (tp > 1) fac.emplace_back(tp);
	for (int i = 1; i <= n; i++) cin >> a, mp[ord(a)]++;
	for (auto p1 : mp) {
		for (auto p2 : mp) {
			if (!(p1.first % p2.first)) ans += (ll)p1.second * p2.second;
		}
	}
	cout << ans;
}
```

好困啊。

---

## 作者：tribool4_in (赞：0)

看到幂次，不妨考虑取 $a_i$ 的离散对数 $b_i$ 满足 $g^{b_i}\equiv a_i\pmod P$。于是题意化为统计存在 $k$ 的 $(i,j)$ 对满足 $kb_i\equiv b_j\pmod {P-1}$（费马小定理）。

然后发现直接 BSGS 会寄掉。于是很关键的，注意到原式等价于 $kb_i+l(P-1)=b_j$，以 $k,l$ 为未知数，有整数解的条件为 $\gcd(b_i,P-1)\mid b_j$，等价于 $\gcd(b_i,P-1)\mid \gcd(b_j,P-1)$。

然后再考虑 $b_j$ 的“加法阶”（跟乘法阶同理，即最小 $k$ 满足 $kx\equiv 0 \pmod p$），显然有性质 $\delta_+(b)=\dfrac{\operatorname{lcm}(b,p)}{b}=\dfrac{p}{\gcd(b,p)}$，且由于 $g^{b_i}\equiv a_i\pmod P$，$b_i$ 的加法阶等于 $a_i$ 的乘法阶 $\delta(a_i)$。于是代入原式便有 $\dfrac{P-1}{\delta(a_i)}\mid \dfrac{P-1}{\delta(a_j)}$，等价于 $\delta(a_j)\mid \delta(a_i)$。然后发现由于 $\delta(a_i)\mid (P-1)$，枚举 $P-1$ 的因数试除法即可求出每个 $\delta(a_i)$。

然后可以发现不同的 $\delta(a_i)$ 个数很少，于是去重一下暴力枚举判断就行了。

由于 $P$ 很大，快速幂乘方时需要开 `int128`。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, P, a[N], b[N];
    vector<int> pr;
    auto qpow = [&](int a, int b) {
        int res = 1;
        for (; b; a = (__int128_t)a * a % P, b >>= 1)
            if (b & 1) res = (__int128_t)res * a % P;
        return res;
    };
    auto input = [&]() {
        cin >> n >> P;
        for (int i = 1; i <= n; i++) cin >> a[i];
    };
    auto divide = [&]() {
        int x = P - 1;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                pr.push_back(i);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) pr.push_back(x);
    };
    auto work = [&]() {
        fill(b + 1, b + n + 1, P - 1);
        for (int i = 1; i <= n; i++)
            for (auto p : pr)
                while (b[i] % p == 0 && qpow(a[i], b[i] / p) == 1) b[i] /= p;
        map<int, int> mp;
        for (int i = 1; i <= n; i++) mp[b[i]] += 1;
        int ans = 0;
        for (auto p1 : mp)
            for (auto p2 : mp)
                if (p1.first % p2.first == 0) ans += p1.second * p2.second;
        cout << ans << '\n';
    };
    input(), divide(), work();
    return 0;
}
```

---

## 作者：mango2011 (赞：0)

一道有趣的数学题。

首先来说几个结论：

1) 如果 $p$ 是素数，那么 $\operatorname{ord}_p(a)|\varphi(a)$。
 
2) 如果 $p$ 是素数，那么存在正整数 $x$ 使得 $a^x\equiv b\pmod p$ 的充分必要条件是 $\operatorname{ord}_p(b)|\operatorname{ord}_p(a)$。

其中 $\operatorname{ord}_p(d)$ 表示使得 $d^t\equiv1\pmod p$ 的最小正整数 $t$，$\varphi(d)$ 表示 $1\sim d$ 中与 $d$ 互素的数的个数。

这两个结论的证明过程比较复杂，在此不再赘述（可以参考网上的证明）。

有了上面的结论，我们就可以计算出 $b_i=\operatorname{ord}_p(a_i)$（具体计算方法就是利用第一个结论）。

然后根据第一个结论，我们就是要求出有多少个 $(i,j)$ 使得 $b_i|b_j$（第二个结论）。又因为 $b_i$ 都是 $\varphi(p)$ 的因数，因此我们可以统计出每一种因数出现的次数，然后暴力枚举二元组进行统计。

总的复杂度大约是 $O(d(p)^2)$ 级别的，可以通过。

---

