# [POI 2011] SEJ-Strongbox

## 题目描述

有一个密码箱，$0$ 到 $n-1$ 中的某些整数是它的密码。且满足：若 $a$ 和 $b$ 是它的密码，则 $(a+b)\bmod n$ 也是它的密码（$a$，$b$ 可以相等）。某人试了 $k$ 次密码，前 $k-1$ 次都失败了，最后一次成功了。

问，该密码箱最多有多少种不同的密码。

## 样例 #1

### 输入

```
42 5
28 31 10 38 24```

### 输出

```
14```

# 题解

## 作者：KaisuoShutong (赞：40)

码长文不易，点个赞吧。

## 写在题解之前

不知道这个题为什么这么多伞兵做法。大概是洛谷用的不是官方数据的原因？

建议加强数据/添加官方数据。

## 题意

很清楚了，略过。

## 题解

容易列出最基础款的条件：  
若可能的密码为 $c_1,c_2,...,c_w$，则对于 $\forall i\in [1,k-1]$，$\forall t,q_0,q_1,...,q_w$，都满足：

$$t\cdot n+q_0\cdot m_k+q_1\cdot c_1+q_2\cdot c_2+...+q_w\cdot c_w\not = m_i$$

根据裴蜀定理可知，左式的最小整数值为 $\gcd(n,m_k,c_1,c_2,...,c_k)$，不妨设其为 $g$。  
也就是说，如果要满足条件，$g \nmid m_i$。

又因为 $n$ 和 $m_k$ 都是定值，可以挖掘出两个条件。  
1. $g \mid \gcd(n,m_k)$。
2. 若 $g$ 值一定，则 $w$ 的值（即 $c$ 的个数）为 $\displaystyle\frac{n}{g}$。

一个基本的算法轮廓就出来了，这应该也是洛谷大部分题解的做法。  
枚举 $\gcd(n,m_k)$ 的因数作为 $g$，逐个判断 $g$ 是否整除 $m_i$。

很遗憾，这个做法的时间复杂度是 $O(\sigma(\gcd(n,m_k))\cdot k)$ 的，其中 $\sigma$ 表示因数个数。因为 $\sigma(\gcd(n,m_k)$ 的值大于 $10000$，所以不可能过官方数据，但可以过洛谷数据。

我还是写了代码，放在这里。
```cpp
char calc(ll x) {for(int i=1;i<K;i++) if(m[i]%x==0) return 0;return 1;}
signed main() {
	n=read(),K=read();
	for(int i=1;i<=K;i++) m[i]=read();
	ll i,t=__gcd(n,m[K]);
	for(i=1;i*i<=t;i++) if(t%i==0&&calc(i)) return cout<<n/i<<'\n',0;
	for(--i;i;i--) if(t%i==0&&calc(t/i)) return cout<<n/(t/i)<<'\n',0;
	return 0;
}
```

考虑怎么优化。

首先，根据定义，有且仅有所有 $m_i$ 的因数不可以作为 $g$。  
所以，我们可以对于每个 $m_i'$ 都枚举因数，用 `map` 保存不可以作为 $g$ 的数。最后再枚举 $g$，判断时间降至 $O(\log)-O(1)$。

可惜，这样复杂度瓶颈转移到了预处理，没有实质性优化。


观察发现，我们将 $m_i$ 和 $\gcd(n,m_k)$ 取 $\gcd$ 后作为新的 $m_i'$，对答案没有影响。这很显然，因为 $g$ 全都是 $\gcd(n,m_k)$ 的因子。  
观察整体性质，容易发现 $m_i$ 中所含的质因子数量在 $20$ 个以内。  
所以，不妨预处理出所有可能的质因子，对 $m_i$ 分解质因数时枚举指数即可。这样，时间复杂度会大大降低。

恕我不太会算这个东西的复杂度，但是把 `map` 换成 `unordered_map` 即可通过 LOJ 上的官方数据。代码如下。
```cpp
void dfs(int x,ll s) {
	if(x==pr[0]+1) return mp[s]=1,void();
	for(int i=0;i<=c[x];i++) dfs(x+1,s),s*=pr[x];
}
signed main() {
	n=read(),K=read();
	for(int i=1;i<=K;i++) m[i]=read();
	ll t=__gcd(n,m[K]),tt=t;
	for(int i=1;i<K;i++) v[__gcd(m[i],t)]=1;
	for(ll i=2;i*i<=tt;i++) if(tt%i==0) {
		pr[++pr[0]]=i;while(tt%i==0) tt/=i;}
	if(tt>1) pr[++pr[0]]=tt;
	for(auto y:v) {
		for(int i=1;i<=pr[0];i++) {
			ll w=y.first;c[i]=0;
			while(w%pr[i]==0) ++c[i],w/=pr[i];
		}
		dfs(1,1);
	}
	ll i;for(i=1;i*i<=t;i++) if(t%i==0&&!mp[i]) return cout<<n/i<<'\n',0;
	for(--i;i;i--) if(t%i==0&&!mp[t/i]) return cout<<n/(t/i)<<'\n',0;
	return 0;
}
```

显然，这个东西还是不太稳。我们考虑~~时间都去哪了~~时间多花在了什么上。  
对于一个可能的 $g$，我们仅仅标记它一次就够了。所以如果记忆化 `dfs` 的话，分解的时间复杂度就会稳定于 $O(\sigma(\gcd(n,m_k))$。  
这样，总共的时间复杂度即为 $O(k\cdot \log + \sqrt{\gcd(n,m_k)} + \sigma(\gcd(n,m_k))$，瓶颈在于对每个 $m_i$ 求一次 $\gcd$ 上。

代码如下。
```cpp
void dfs(ll s) {
	if(mp[s]) return;mp[s]=1;
	for(int x=1;x<=pr[0];x++) if(s%pr[x]==0) dfs(s/pr[x]);
}
signed main() {
	n=read(),K=read();
	for(int i=1;i<=K;i++) m[i]=read();
	ll t=__gcd(n,m[K]),tt=t;
	for(int i=1;i<K;i++) v[__gcd(m[i],t)]=1;
	for(ll i=2;i*i<=tt;i++) if(tt%i==0) {
		pr[++pr[0]]=i;while(tt%i==0) tt/=i,++mc[pr[0]];}
	if(tt>1) pr[++pr[0]]=tt,++mc[pr[0]];
	for(auto y:v) dfs(y.first);
	ll i;for(i=1;i*i<=t;i++) if(t%i==0&&!mp[i]) return cout<<n/i<<'\n',0;
	for(--i;i;i--) if(t%i==0&&!mp[t/i]) return cout<<n/(t/i)<<'\n',0;
	return 0;
}
```

---

## 作者：Alex_Wei (赞：21)

- Update on 2025.1.22：修订。

### [P3518 [POI2011] SEJ-Strongbox](https://www.luogu.com.cn/problem/P3518)

若 $v$ 是密码，则所有 $\leq n$ 且是 $\gcd(v, n)$ 的倍数的数也是密码，因为 $kv \bmod n$ 取到了所有这样的数。

> **证明**
>
> 设 $d = \gcd(v, n)$，$d\mid t$ 且 $t$ 不是密码，则 $kv \equiv t\pmod n$ 无解。根据裴蜀定理，它等价于 $\gcd(v, n) \nmid t$ 即 $d\nmid t$，矛盾。

进一步地，若 $u, v$ 是密码，则 $u' = \gcd(u, n)$ 和 $v' = \gcd(v, n)$ 是密码。由裴蜀定理，$\gcd(u', v')$ 在模 $n$ 意义下能被 $u'x + v'y$ 表出，所以 $\gcd(u', v')$ 是密码。

因此，设密码集合为 $S$，则 $d = \gcd(n, \gcd_{u\in S} u)\in S$。显然，$S$ 恰由 $d$ 的所有倍数组成。

考虑枚举这个 $d = \gcd(v, n)$，若合法则答案即 $\max\frac n d$，即我们需要找到最小的合法的 $d$。

设 $d_i = \gcd(m_i, n)$，$d$ 必须是密码与 $n$ 的 $\gcd$ 即 $d_k$ 的因数，其次任何 $d_i\ (1\leq i < k)$ 不能是 $d$ 的倍数。对于后者的限制，相当于在 $n$ 的所有因子形成的图上，一个点向它的因子连边，能被某个 $d_i$ 到达的因子是不合法的。

首先给所有 $d_i\ (1\leq i\leq k)$ 打上标记。从大到小枚举 $n$ 的每个因数 $c$，若 $c$ 被打上标记，则 $\frac{c}{p_j}$ 也应被打上标记，其中 $p_j$ 表示能整除 $c$ 的 $n$ 的质因子，表示若 $c$ 是某个 $d_i$ 的因数，则 $\frac c {p_j}$ 也是。

剩下没有被打标记的 $n$ 的因数 $d$，若 $d$ 能被 $d_k$ 整除则合法。找到最小的这样的 $d$，则答案为 $\frac n d$。

打标记的过程可以使用哈希表实现，时间复杂度 $\mathcal{O}(\sqrt n + k\log n + d(n)\omega(n))$，其中 $\omega(i)$ 表示 $i$ 的质因数个数。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
inline ll read() {
	ll x = 0; char s = getchar();
	while(!isdigit(s)) s = getchar();
	while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
	return x;
}

const int N = 2e4 + 5;
ll n, k, v, ans;
ll cpr, pr[N], cdv, dv[N];
void dfs(int p, ll v) { // dfs 找到所有 n 的因数
	if(p > cpr) return dv[++cdv] = v, void();
	dfs(p + 1, v);
	while(n / pr[p] >= v && n % (v *= pr[p]) == 0) dfs(p + 1, v);
}
void init() {
	ll x = n;
	for(ll i = 2; i * i <= x; i++)
		if(x % i == 0) {
			while(x % i == 0) x /= i;
			pr[++cpr] = i;
		} if(x > 1) pr[++cpr] = x; // 找到所有 n 的质因子
	dfs(1, 1), sort(dv + 1, dv + cdv + 1), reverse(dv + 1, dv + cdv + 1); // 别忘了排序
}
gp_hash_table <ll, bool> mp; // 哈希表标记
int main() {
	cin >> n >> k, init();
	for(ll i = 1; i < k; i++) mp[__gcd(read(), n)] = 1;
	v = __gcd(read(), n);
	for(int i = 1; i <= cdv; i++) {
		if(mp.find(dv[i]) != mp.end()) {
			for(int j = 1; j <= cpr; j++)
				if(dv[i] % pr[j] == 0) mp[dv[i] / pr[j]] = 1;
		} else if(v % dv[i] == 0) ans = n / dv[i];
	} cout << ans << endl;
	return 0;
}
```

---

## 作者：IsoTls (赞：15)

题目分析：
依据题意，所有的密码会形成一个模 $n$ 的加法群 $(G,+)$。

证明：


封闭性：$a \in G, b \in G \Rightarrow a+b \mod n\in G$， 这是已知条件

结合性：$(a + b) + c = a + (b + c) \mod n$ 

单位元：如果 $a \in G $

$\Rightarrow 2*a \mod n \in G$

$\Rightarrow 3*a \mod n \in G$

$ \Rightarrow ... \Rightarrow n*a \mod n \in G$

$ \Rightarrow 0 \in G$。

而 $0$ 满足性质 $a + 0 = 0 + a \mod n$，所以 $0$ 就是 $(G,+)$ 的单位元。

逆元：假设 $a \in G$，现在我们来寻找 $a$的逆元，由于 $a + (n-1)*a = n*a = 0 \mod n$，并且 $(n-1)*a + a = n*a = 0 \mod n$，所以对任意元素 $a$，都存在一个逆元，为$(n-1)*a \mod n$

**由上可知，$(G,+)$是一个群。**

由于逆元的存在，使得如果 $a \in G$，那么 $-a \in G$，这里的 $-a$ 并不是一个真的负数， $-a$指的是 $a$ 的逆元。为了表述方便，以下的加减乘运算也都是模n意义下的。显然如果 $a \in G, b \in G \Rightarrow a - b = a + (-b) \mod n \in G$。

**推论一：如果 $a \in G, b \in G$，那么 $gcd(a, b) \in G$**

证明：由群的封闭性可知

$a \in G \Rightarrow x*a \in G$，其中 $x$ 为任意整数 $(1)$

$b \in G \Rightarrow y*b \in G$，其中 $y$ 为任意整数 $(2)$

由于有逆元的存在，上述的系数 $x,y$ 可以为负数。

结合$(1),(2)$可知，$x*a + y*b \in G$，所以 $gcd(a, b) \in G$


**推论二：如果 $a \in G$，那么 $gcd(n, a) \in G$**

证明：
不妨设 $n = a*k + r$，其中 $k$ 和 $r$ 都是整数，并且 $r < a$，由数论知识可知
$gcd(n, a) = gcd(a, r)$

$a \in G \Rightarrow (k+1)*a \in G$

$ \Rightarrow a*k + a \in G$

$ \Rightarrow n - r + a \in G$

$ \Rightarrow a - r \in G $，结合 $a \in G$，可推出

$ \Rightarrow r \in G$

$ \Rightarrow gcd(a, r) \in G$

$ \Rightarrow gcd(n, a) \in G$

**推论三：$G$ 是一个循环群，假设 $G$ 中最小非零元素为 $g$，那么集合 $G = \{ 0,g,2*g,3*g,... \}$**

证明：

(1) 对集合 $G$ 中的任意一个元素 $x$， 由推论二可知 $gcd(x, g) \in G$，由于$g$ 是最小的元素，所以 $g \leq gcd(g, x) \leq g$，所以 $g = gcd(g,x)$，所以 $g$ 一定能被 $x$ 整除，换而言之 $g$ 一定可以整除集合 $G$ 中的任意一个元素。

(2) 因为 $g \in G \Rightarrow 2*g \in G \Rightarrow 3*g \in G \Rightarrow ... \Rightarrow g$ 的任意整数倍模 $n$ 都在 $G$ 中。当然单位元 $0$ 也在 $G$ 中。

结合(1)(2)可知，$G$ 是一个循环群


**推论四：假设 $G$ 中最小非零元素为 $g$，那么 $g$ 可以被 $n$ 整除，并且 $G$ 中元素个数 $|G| = n/g$**

证明：

由于 $g \in G$，由推论二可知 $gcd(n, g) \in G$，又由于 $g$ 是最小的非零元素，所以 $g \leq gcd(n, g) \leq g$，所以 $g = gcd(n, g)$，$g$ 可以被 $n$ 整除。

由于题目中要求 $G$ 中最大元素小于 $n$，结合推论三可知，$G$ 中最大的元素为 $n - g$。$|G| = (n-g)/g + 1 = n/g$

下面回到题目本身，由推论三可知，只要我们确定了生成元 $g$，那么集合 $G$就确定了，下面我们来寻找符合条件的 $g$。由于前 $k-1$ 次尝试没有打开锁，所以前 $k-1$ 次尝试的数字一定不在集合 $G$ 中。由推论三可知: $m_1, m_2, ... m_{k-1}$一定都不能被 $g$ 整除。而结合推论四可知： $n$ 和 $m_k$ 都可以被 $g$ 整除，所以$gcd(n, m_k)$ 可以被 $g$ 整除。 题目要求让 $|G|$ 最大，只需要找到最小的 $g$ 满足这个约束条件即可。

可以先计算 $gcd(n, m_k)$，然后从1开始往上遍历筛选符合条件的 $g$

代码如下：

```c
#include <stdio.h>

#define SIZE 250000
long long a[SIZE];

long long gcd(long long x, long long y) {
    long long t = 0;
    while (y != 0) {
        t = x;
        x = y;
        y = t % y;
    }
    return x;
}

int is_valid(long long x, int k) {
    int i;
    for (i = k - 1; i >= 0; i--) {
        if (a[i] % x == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    long long n, k, b;
    long long i, j, len = 0;
    scanf("%lld%lld", &n, &k);
    k--;
    for (i = 0; i <= k; i++) {
        scanf("%lld", &a[i]);
    }

    a[k] = gcd(a[k], n);
    long long r = 0;
    long long g = 0;
    for (g = 1; g <= a[k] / g; g++) {
        if (a[k] % g != 0) {
            continue;
        }
        if (is_valid(g, k)) {
            printf("%lld\n", n / g);
            return 0;
        } else if (is_valid(a[k] / g, k)) {
            r = n / a[k] * g;
        }
    }
    printf("%lld\n", r);
    return 0;
}
```


---

## 作者：abruce (赞：7)

看了下题解，感觉只有 kczno1 的题解时间复杂度是对的，但我不会证。于是我自己来写一篇阳间点的题解，可以通过 loj 上的数据。  
思路来源：Saliеri（大家快来膜他！！1）  
很明显如果 $x$ 是密码，那么 $2x,3x...$ 都是密码。由于需要 $\bmod n$，所以这个 $x$ 必须满足 $x|n$。由于前 $k-1$ 次都没试出来最后一次试出来了，所以需要满足 $\forall x\nmid a_i(1\le i<k),x|a_k$。  
总而言之：$x|\gcd(a_k,n),\forall x\nmid a_i(1\le i<k)$。  
对于前半部分，我们可以 $O(\sqrt{n})$ 得到 $gcd(a_k,n)$ 的每一个因数，接下来我们需要检验这些因数。  
对于暴力的解法，是直接一个一个一个判，这样做复杂度是 $O(kd(n))$ 的，但洛谷数据较水，可以通过。但 POI 的官方数据时没有这么水的，我们需要考虑如何优化。  
我们先把 $\gcd(a_k,n)$ 的因数全部抽出来。离线进行判断。我们发现，如果一个数被判掉了，那么它的所有因数也会被判掉。于是我们可以进行记忆化，对于每个 $a_i(1\le i<k)$，我们首先让它与 $\gcd(a_k,n)$ 取 $\gcd$，因为只有这部分是有效的。然后我们写一个函数把一些因数判掉，如果当前数已经无效，则返回，否则继续去它的因数判。  
由于 $10^{14}$ 方内质因子个数并不大，所以我们只需要得到 $\gcd(a_k,n)$ 的质因子即可。  
时间复杂度 $O(k\log n+d(n)(\omega(n)+\log d(n)))$，可以无压力通过本题。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2.5e5+5;
int k,cnt;
ll n,ans,a[maxn],p[maxn];
set<ll> s;
bool pd(ll x) {
	for(register int i=1; i<k; i++)if(a[i]%x==0)return 0;
	return 1;
}
void ban(ll x) {
	if(s.find(x)==s.end())return;
	s.erase(x);
	for(register int i=1; i<=cnt; i++)
		if(x%p[i]==0)ban(x/p[i]);
}
ll gcd(ll x,ll y) {
	if(!y)return x;
	return gcd(y,x%y);
}
int main() {
	scanf("%lld%d",&n,&k);
	for(register int i=1; i<=k; i++)scanf("%lld",&a[i]);
	ll w=gcd(n,a[k]),y=w;
	for(register ll i=2; i*i<=w; i++) {
		if(y%i)continue;
		p[++cnt]=i;
		while(y%i==0)y/=i;
	}
	if(y!=1)p[++cnt]=y;
	for(register int i=1; i<=sqrt(w); i++) {
		if(w%i)continue;
		s.insert(i),s.insert(w/i);
	}
	for(register int i=1; i<k; i++)ban(gcd(w,a[i]));
	printf("%lld",n/(*s.begin()));
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：5)

在看《信息学奥赛之数学一本通》的时候做到的题，这里简记一下更简单的分析方法。

## 分析

看到题目最后的提示才想起用群的。

群的定义就不说了。考虑构造模 $n$ 意义下的加法群 $(G, +)$。首先分析一下这个群是否成立。依次分析群的定义：

 - 封闭性：根据题目要求，显然对于 $a, b \in G$，有 $a + b \in G$。
 
 - 结合律：根据模的性质，显然有 $(((a + b) \bmod n) + c) \bmod n = (a + (b + c) \bmod n) \bmod n$。
 
 - 单位元：$0$ 即为该群单位元 $e$。
 
 - 逆元：对于群内元素 $a$，其逆元 $a ^ {-1}$ 为 $(n - 1) \times a$。可以看出，$a + a ^ {-1} = (n \times a) \bmod n = 0 = e$。
 
下面回归题目。首先有两个重要结论：

 - $\forall x \in G$，则对于任意正整数 $k$，都有 $k \times x \bmod n\in G$。
 
 证明显然。根据群的封闭性，$x \in G, x + x = 2x \in G \cdots$。
 
 - $\forall x \in G$，都有 $(x, n) \in G$。这里的 $(x, n)$ 指求最大公约数。
 
 证明：考虑构造关于 $k, c$ 的不定方程 $x \times k - n \times c = (x, n)$。根据裴蜀定理，该方程一定有解。那么一定存在 $k$，使得 $x \times k \bmod n = (x, n)$。而由结论 $1$ 得，一定有 $x \times k \bmod n \in G$。故结论成立。
 
那么对于第 $k$ 个输入的密码 $a_k$，就一定有 $(a_k, n) \in G$。而 $(a_k, n) \in G$ 的充分必要条件是存在 $d \in G \wedge d \mid (a_k, n)$。所以问题转化为：

求最小的 $d$，使得 $d \mid (a_k, n)$ 且 $\forall i \in [1, k), d \nmid (a_i, (a_k, n))$。最简单的思路是遍历 $(a_k, n)$ 的因子 $d$，然后依次判断它成不成立（即是否满足第二个条件）。由于求出所有因子的复杂度为 $O(\sqrt{n})$，而判断是否合法的单次复杂度为 $O(k)$，故总复杂度为 $O(k \sqrt{n})$。

```cpp
int n, k;
int a[N], ans;

bool check(int x) {
	for (int i = 1; i < k; i ++ )
		if (a[i] % x == 0) return false;
	return true;
}
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= k; i ++ )
		scanf("%lld", &a[i]);
	int dk = gcd(a[k], n);
	for (int i = 1; i * i <= dk; i ++ ) {
		if (dk % i == 0 and check(i)) return printf("%lld\n", n / i), 0;
		if (dk % i == 0 and check(dk / i)) ans = n / (dk / i);
	}
	printf("%lld\n", ans);
	return 0;
}
```

时间复杂度明显过高。实测能拿 $76$ 分。

考虑优化上面的算法。可以发现，复杂度的瓶颈在于判断每个因子是否合法上。考虑使用染色的方法进行记忆化。即先求出 $n$ 的 **质因子** $p_w$，然后对于 $a_i(i \in [1, k))$ 染色。接下来对于能够整除 $a_i$ 的 $p_j$，对 $\dfrac{a_i}{p_j}$ 递归染色。当然，你需要提前对 $a_i$ 与 $n$ 求 $\gcd$。

染色过程可以开一个 `unordered_map` 来搞。跑得飞快。

```cpp
int n, k;
int a[N], ans;
vector<int> p;
unordered_map<int, bool> Map;

void color(int x) {
	if (Map[x] == false) return;
	Map[x] = false;
	for (auto i : p) 
		if (x % i == 0) color(x / i);
}
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= k; i ++ )
		scanf("%lld", &a[i]);
	a[k] = gcd(a[k], n);
	for (int i = 1; i < k; i ++ )
		a[i] = gcd(a[i], a[k]);
	
	int dk = a[k];
	for (int i = 2; i * i <= dk; i ++ ) { // 求出 dk 的所有质因子
		if (dk % i) continue;
		p.push_back(i); 
		while (dk % i == 0) dk /= i;
	} if (dk != 1) p.push_back(dk);
	
	dk = a[k];
	for (int i = 1; i * i <= dk; i ++ ) { // 标记 dk 的所有因子
		if (dk % i) continue;
		Map[i] = Map[dk / i] = true;
	}
	
	for (int i = 1; i < k; i ++ )
		color(a[i]);
	
	for (int i = 1; i * i <= dk; i ++ ) {
		if (dk % i) continue;
		if (Map[i]) return printf("%lld\n", n / i), 0;
		if (Map[dk / i]) ans = n / (dk / i);
	}
	printf("%lld\n", ans);
	return 0;
}
```

我不会分析时间复杂度，大概是个 $O(\sqrt{n} + k \log n + d(n) \omega (n))$ 罢。手写哈希表反而更慢了，是不是我手太臭了。

---

## 作者：kczno1 (赞：5)

若x,y存在，则(x+y)%n存在

注意到,x存在<=>gcd(x,n)的所有倍数都存在。

证明:设gcd(x,n)=d，x=d\*a,n=d\*b。若x存在，则kx存在，kx%n=d\*(ka%b)

因为gcd(a,b)=1，所以当k%b=0->b-1时，ka%b一定两两不同余，因为同余<=>b|(k1-k2)\*a

所以ka%b会取遍0->b-1,所以kx%n会取遍且仅会取一切d的倍数。

所以最后的选择是形如0,d,..kd的，其中d是n的一个因子。

所以我们就只用求出这个d就行了。

也就是说:d|n,d|a[k],d不整除a[1]..a[k-1],且d最小。
所以d|gcd(n,a[k])

考虑gcd(n,a[k])的因子也就几万个，让他们被线性筛掉，之后再找最小的那个,n/它就是ans了。

将他根号时间分解质因数，质因数是log个，

之后将a[1]..a[k-1]放在这些质因数上走一遍，相当于求gcd+分解质因数，时间也是log的，

那么分解出来的gcd的所有因数都要被删掉。

考虑一个数如果被删了，他的因数都要被删;实际上我们可以做到使得每个数只被删一次。

由于数很大，可以考虑离散化或者用平衡树或者用hash来存储所有因数;

但考虑10^7的bool数组也就10MB,可以把<10^7的数存下来，>10^7的用n/它来存，这样就可以线性访问了。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define N 250010
#define U 10000000
ll a[N];
bool vis[U+5],vis2[U+5];

ll gcd(ll x,ll y)
{
    while (y)
    {
        ll temp=x;
        x=y;y=temp%y;
    }
    return x;
}

ll n;
ll p[50];int num[50],top;
ll nowp[50];int now[50],top2;
void del(int i,ll x,bool first)
{
    if (first)
    if (x<=U) 
    {
        if (vis[x]) return ;
        vis[x]=1;
    }
    else
    {
        if (vis2[n/x]) return ;
        vis2[n/x]=1;
    }
    if (i>top2) return ;
    del(i+1,x,0);
    for (int j=1;j<=now[i];++j)
     del(i+1,x/=nowp[i],1);
}

int main()
{
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int k,i;
    scanf("%lld%d",&n,&k);ll n0=n;
    for (i=1;i<=k;++i) scanf("%lld",a+i);
    n=gcd(n,a[k]);
    int u=sqrt(n);ll x=n;
    for (i=2;i<=u;++i)
    if (!(x%i))
    {
        p[++top]=i;
        while (!(x%i))
        {
            x/=i;++num[top];
        }
    }
    if (x>1) { p[++top]=x;num[top]=1; }
    for (i=1;i<k;++i)
    {
        x=a[i];top2=0;
        for (int j=1;j<=top;++j)
        if (!(x%p[j]))
        { nowp[++top2]=p[j]; now[top2]=0;
          while (!(x%p[j])) { x/=p[j];if ((++now[top2])==num[j]) break; }
        }
        del(1,a[i]/x,1);
    }
    for (i=1;i<=u;++i)
    if (!vis[i]&&!(n%i)) 
    {
        printf("%lld\n",n0/i);return 0;
    }
    for (i=u;i;--i)
    if (!(n%i))
    {
        if (n/i<=U)
        {
            if(vis[n/i]) continue;
        }
        else if (vis2[i]) continue;
        printf("%lld\n",n0/(n/i));return 0;
    }
    puts("0");
}
```

---

## 作者：EmpyreanCz (赞：4)

这是一道数论题...

## 思路：

首先先将每个输入的数据与n的最大公约数求出（因为如果a[i]是密

码，那么所有a[i]与n最大公约数的倍数也是密码；于是如果a[i]不

是密码，那么所有a[i]与n最大公约数的倍数也都不是密码）

再从1到sqrt(a[k])(其实1到a[k]也行)找，最小且符合条件就是最

小密码。

## 代码实现：

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
ll n,k;
ll a[250005];
ll num=0;
ull ans;inline ll read()
{
    ll x=0;
    bool f=1;
    char c=getchar();
    for(; !isdigit(c); c=getchar()) if(c=='-') f=0;
    for(; isdigit(c); c=getchar()) x=(x<<3)+(x<<1)+c-'0';
    if(f) return x;
    return 0-x;
}
inline ll gcd(long long a,long long b)//求两个数最大公约数的函数 
{
    return b?gcd(b,a%b):a;
}
inline bool check(int x)
{
    for(ll i=1;i<=num-1;i++)//-1：不包含密码与n的最大公约数 
    {
        if(a[i]%x==0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    n=read();k=read();
    for(ll i=1;i<=k;i++)
    {
    	a[i]=read();
    }
    for(ll i=1;i<=k;i++)
    {
        a[i]=gcd(a[i],n);//求a[i]与n的最大公约数 
    }
    sort(a+1,a+k);//排序（不排也可以，只不过时间更长）至于不是 sort(a+1,a+k+1)是因为密码不能与不是密码的数混在一起 
    for(ll i=1;i<=k;i++)
    {
        if(a[i]!=a[i-1])//去重 
        {
            num++;
            a[num]=a[i];
        }
    }
    for(ll i=1;i<=sqrt(a[k]);i++)//节约时间 
    {
        if(a[k]%i==0)//第一层筛选 
        {
            if(check(i)==true)//既是最小又是符合题意的 ，一定是最优解 
            {
                ans=n/i;
                break;
            }
            else if(check(a[k]/i)==true)//符合条件但不一定是最小，算但不break 
            {
                ans=n/a[k]*i;
            }
        }
    }
    cout<<ans;
    return 0;
}
/*
42 5
28 31 10 38 24
*/

```


---

## 作者：半仙胡小桃 (赞：2)

分析可以得出

结论1：如果x是密码，那么GCD（x,n）也是密码

结论2：如果x和y是密码，那么GCD（x，y）也是密码

做法：首先令l=GCD（a[k]，n），处理出l的所有因子，然后筛去这些因子中为GCD（l，不是密码的数）的因子（因为根据结论2，这些因子绝对不是密码），然后找出最小的因子，为k，输出n/k就行啦。

顺便一说lower\_bound函数的作用

形如lower\_bound（a+1,a+n+1,x），a为一个数组，这个函数的作用是返回在a[1]—a[n+1]第一个比x小的数的地址（所以要求a数组升序）。

AC程序如下










```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<queue>
#include<vector>
#include<climits>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
long long a[500000],q[1000005],f[1000005],i,j,ans;
long long tot,n,k;
long long gcd(long long a,long long b)
{
    return b? gcd(b,a%b):a;
} 
int main()
{
    scanf("%lld%lld",&n,&k);
    for(i=1;i<=k;i++)
     scanf("%lld",&a[i]);
    a[k]=gcd(a[k],n);
    for(i=1;i<k;i++)
     a[i]=gcd(a[i],a[k]);
    for(i=1;i*i<=a[k];i++)
     if(a[k]%i==0)
      {
          q[++tot]=i;
          if(i*i!=a[k]) q[++tot]=a[k]/i;
      } 
    sort(q+1,q+tot+1);
    for(i=1;i<k;i++)
     f[lower_bound(q+1,q+tot+1,a[i])-q]=1;
    for(i=1;i<=tot;i++)
     if(f[i])
      for(j=1;j<i;j++)
       if(q[i]%q[j]==0)
        f[j]=1;
    for(ans=1;f[ans];ans++);
     printf("%lld\n",n/q[ans]);
    return 0;
}

```

---

## 作者：Mirasycle (赞：1)

noip 考前复习数论，希望别考。

从限制入手，最后密码的线性组合不能表示出 $m_i,i\in [1,k-1]$。假设最后的密码序列为 $\{a_i\}$，那么必须满足 $\sum x_ia_i\bmod n \neq m_j，j\in [1,k-1]$。

这个取模可以很经典地转化成 $\sum x_ia_i+x n$，也就是 $a_1,a_2,..,n$ 的线性组合，利用裴蜀定理可以转化为 $d=\gcd(a_1,a_2...n)$ 的倍数中 $<n$ 的数。

考虑枚举 $d$，由于我们已经知道了 $a_i$ 中的一个数为 $m_k$，故 $d\mid \gcd(m_k,n)$。考虑枚举符合要求的 $d$，然后只需要满足 $d\nmid m_i,i\in[1,k-1]$ 即可。

暴力做的话，时间复杂度为 $O(d(n)k)$，会超时。

考虑反向求出所有不能被用的数，不过如果枚举 $m_i$，再枚举其因数用 map 保存肯定还是不太行。

不过可以发现上述过程干了很多没有用的事情，可能作为答案的数只有 $d(\gcd(m_k,n))$ 个，而我们预处理不合法的数却足足标记了 $\sum\limits_{i=1}^{k-1}d(m_i)$ 个数，很多都是无用的数！

于是我们只需要在 $\gcd(m_k,n)$ 的因数集内做标记不合法的数即可。从大到小枚举因数集中的数，如果遇到了 $m_i$，首先将这个数标记不合法，其次 $m_i$ 的约数集和 $\gcd(m_k,n)$ 约数集的交集中的数要标记不合法，暴力枚举还是不合适。考虑 "不合法标记下传"，由于我们是从大到小枚举，所以我们可以将不合法的标记往下传递给最大的几个数，使得这几个数是其他并集中数的倍数，这样子等枚举到他们的时候标记可以继续下传至所有数。我们可以把标记传给 $\dfrac{m_i}{p_j}$，其中 $p_j$ 为 $n$ 的质因子。这样子，我们就只会标记 $d(\gcd(m_k,n))$ 个数，时间复杂度就正确了。

注意因为是在 $\gcd(m_k,n)$ 的因数集合内进行的操作，所以开始之前需要所有 $m_i\gets \gcd(m_i,\gcd(m_k,n))$。

在得到符合所有要求的最小 $d$ 之后，最后的答案即为 $\dfrac{n-1}{d}$ 吗？其实别忘记考虑 $0$，可以发现 $0$ 不可能作为不合法密码，因为 $xd_k\bmod n$ 必然可以取到 $0$，如果 $0$ 是不合法密码的话就矛盾了，所以本题答案就是 $\dfrac{n-1}{d}+1=\dfrac{n}{d}$（$d\mid n$）。

时间复杂度 $O(\sqrt n+(k+d(n)w(n))\log n)$。

---

## 作者：yinianxingkong (赞：1)

# [P3518 [POI2011] SEJ-Strongbox](https://www.luogu.com.cn/problem/P3518)

# 前言

本题解的时间复杂度优化方法与其它题解无异，主要是给出一种新的基于抽象代数的推结论方式。如果要学习实现建议看其它题解。

文中的一些基础结论会略过证明，可以自行搜索。

笔者的抽象代数是自学的，如有误请指出。

# 解法分析

抽象一下：求 $H<Z_n$ 使得 $\forall i\in[1,k-1],m_i\notin H$ 且 $m_k\in H$。

知周所众，$Z_n$ 对加法成循环群，$Z_n=\left \langle 1 \right \rangle $。循环群的子群是循环群，故 $H$ 是循环群。

**引理**：$a,b\in H \Rightarrow \gcd(a,b) \in H$。

由裴蜀定理立得。$\gcd(a,b)$ 是 $ax+by$ 的最小正整数解，任意解皆是 $\gcd(a,b)$ 的倍数。于是，令 $a$ 表示 $H$ 中的最小正整数，有 $H=\left \langle a \right \rangle $。

现在我们探讨 $a$ 的性质。由循环群的性质，$\forall i\in[1,k-1],m_i \not| a$ 且 $m_k | a$。

令 $p=|\left \langle a \right \rangle |$，有 $\overline{pa}=\overline{0}$。$p=1$ 时 $a=0$，考虑在代码中特判。否则，因为 $a$ 是 $H$ 中的最小正整数，一定有 $pa=n$，即 $a | n$。

找到最小的满足上述条件的 $a$ 即可。

---

## 作者：FeelGood (赞：1)

首先我们发现 $a$ 和 $b$ 可以相同，于是考虑让 $a$ 和 $b$ 相同。设新的密码为 $k$，那么它可以表示为 $ax \equiv k \pmod n$。

我们可以知道一个性质：$k$ 一定是 $\gcd(a,n)$ 的倍数。证明：把它转化为不定方程 $ax + ny = k$，设 $d = \gcd(a,n)$，那么 $a'x \times d + n'y \times d = k$。此时 $a' \bot n'$，可以证明 $a'x + n'y$ 能够取到 $[0,n - 1]$ 内的任意数，所以 $k$ 一定是 $d$ 的倍数。

如果我们不考虑其它限制，根据上面的性质，我们枚举 $l \mid \gcd(a, n)$（此时 $l$ 相当于一个新的 $\gcd(a, n)$），那么密码的数量为 $\frac{n}{l}$。所以我们很容易想到只需要找到最小的一个数 $l$，那么 $\frac{n}{l}$ 就是答案。

接下来我们考虑非正确密码的限制。根据上面的性质反推，我们可以知道当 $a_i$ 不是密码时，$a_i$ 的所有因子都不是密码。知道了这些，我们就很容易做这题了。

设 $l = \gcd(a_k, n)$，首先我们先标记出 $l$ 的所有因数。然后枚举前 $k - 1$ 个 $a_i$，对于 $a_i$ 如果它有因数和 $l$ 的因数相同，就去除这个因数的标记。但是这样暴力去除标记的时间复杂度是 $O(k \sqrt{n})$，无法通过，于是我们考虑用搜索去除重复的因数。

对 $a_i$ 进行质因数分解，并对去除标记。同时使用记忆化优化，如果一个数被去除了，那么它的所有因数也被去除了。最后我们在所有没被去除标记的因数里找最小的一个，就可以得到答案了。

这样时间复杂度是 $O(\sqrt{n} + k \log n + d(n)\omega(n))$ 的，可以通过。

代码如下：

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

#define ll long long
#define lll __int128

using namespace std;

namespace IO
{
	void read() {}
	template <typename T1, typename ...T2>
	void read(T1 &n, T2 &...m)
	{
		T1 op = 1;
		char c;
		while (isdigit(c = getchar()) == false)
			if (c == '-') op = -1;
		n = c ^ 48;
		while (isdigit(c = getchar()))
			n = (n << 1) + (n << 3) + (c ^ 48);
		n *= op;
		read(m...);
	}
}

using IO::read;

namespace Solve
{
	const int MaxK = 2.5e5;
	
	__gnu_pbds::cc_hash_table<ll, bool> mk;
	ll a[MaxK + 10], prm[MaxK + 10], cntp;
	
	void dfs(ll n)
	{
		if (mk[n] == false) return;
		mk[n] = false;
		for (int i = 1; i <= cntp; ++i)
			if (n % prm[i] == 0) dfs(n / prm[i]);
	}
	
	void Sol()
	{
		ll n, k;
		read(n, k);
		for (int i = 1; i <= k; ++i)
			read(a[i]);
		a[k] = __gcd(a[k], n);
		ll t = a[k];
		for (ll i = 2; i * i <= t; ++i)
		{
			if (t % i != 0) continue;
			prm[++cntp] = i;
			while (t % i == 0) t /= i;
		}
		if (t != 1) prm[++cntp] = t;
		for (ll i = 1; i * i <= a[k]; ++i)
		{
			if (a[k] % i != 0) continue;
			mk[i] = mk[a[k] / i] = true;
		}
		for (int i = 1; i < k; ++i)
		{
			a[i] = __gcd(a[i], a[k]);
			dfs(a[i]);
		}
		ll ans = LLONG_MAX;
		for (ll i = 1; i * i <= a[k]; ++i)
		{
			if (a[k] % i != 0) continue;
			if (mk[i] == true)
			{
				ans = n / i;
				break;
			}
			if (mk[a[k] / i] == true)
				ans = n / (a[k] / i);
		}
		printf("%lld\n", ans);
	}
}

using Solve::Sol;

int main()
{
	Sol();
	return 0;
}
```

---

## 作者：EAlivn (赞：1)

$\texttt{luogu}$ 上单: 数论你\*什么时候\*啊？

分析
---

- 每个输入的数据与 $n$ 的 $\gcd$ 求出

- 如果 $a[i]$ 是密码，那么所有 $a[i]$ 与 $n$ 最大公约数的倍数也是密码；

- 如果 $a[i]$ 不是密码，那么所有a[i]与n最大公约数的倍数也都不是密码

- 那么从 $1 $到 $\sqrt{ a[k] }$ ~~这样分块就能使时间复杂度降低)~~ 寻找，最小且符合条件的就是密码。

代码
---


```C++
#include<bits/stdc++.h>
#define ll long long 
#define ull unsigned ll
using namespace std;
const ll maxn=2000000+5; //数组开小了就不会过
ll a[maxn],num=0,ans=0;
inline ll read() {
	ll k=0;
	int fu=1;
	char ch=getchar();
	(ch=='-')?fu=-1:k=ch-'0';
	while((ch=getchar())!=' '&&ch!='\n'){
		k=k*10+ch-'0';
	}
	return fu*k;  //ÌÓ 
}
inline ll gcd(long long a,long long b) { 
	return b?gcd(b,a%b):a;
}//Ò²¿ÉÒÔÓÃ×Ô´øµÄ __gcd(item x,item b) 
inline bool check(int x) {
	for(ll i=1; i<num; i++) { 
		if(a[i]%x==0) return false;
	}
	return true;
}
int main() {
	ll n=read(),k=read();
	for(ll i=1; i<=k; i++)  a[i]=read();
	for(ll i=1; i<=k; i++) {
		a[i]=gcd(a[i],n);
		// a[i]=__gcd(a[i],n);
	}
	sort(a+1,a+k);
	for(ll i=1; i<=k; i++)  if(a[i]!=a[i-1]) a[++num]=a[i];
	ll sak=sqrt(a[k]);
	for(ll i=1; i<=sak; i++) { 
		if(a[k]%i==0) { 
			if(check(i)==true) { 
				ans=n/i;
				break;
			} else if(check(a[k]/i)==true)  ans=n/a[k]*i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```


```C++
#include<bits/stdc++.h>
#define ll long long 
#define ull unsigned ll
using namespace std;
const ll maxn=2000000+5;
ll a[maxn],num=0,ans=0;
inline ll read() {
	ll k=0;
	int fu=1;
	char ch=getchar();
	(ch=='-')?fu=-1:k=ch-'0';
	while((ch=getchar())!=' '&&ch!='\n'){
		k=k*10+ch-'0';
	}
	return fu*k;  //ÌÓ 
}
inline ll gcd(long long a,long long b) { 
	return b?gcd(b,a%b):a;
}//Ò²¿ÉÒÔÓÃ×Ô´øµÄ __gcd(item x,item b) 
inline bool check(int x) {
	for(ll i=1; i<num; i++) { 
		if(a[i]%x==0) return false;
	}
	return true;
}
int main() {
	ll n=read(),k=read();
	for(ll i=1; i<=k; i++)  a[i]=read();
	for(ll i=1; i<=k; i++) {
		a[i]=gcd(a[i],n);
		// a[i]=__gcd(a[i],n);
	}
	sort(a+1,a+k);
	for(ll i=1; i<=k; i++)  if(a[i]!=a[i-1]) a[++num]=a[i];
	ll sak=sqrt(a[k]);
	for(ll i=1; i<=sak; i++) { 
		if(a[k]%i==0) { 
			if(check(i)==true) { 
				ans=n/i;
				break;
			} else if(check(a[k]/i)==true)  ans=n/a[k]*i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

