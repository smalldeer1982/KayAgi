# [USACO25OPEN] Moo Decomposition G

## 题目描述

给定一个由 $\texttt{M}$ 和 $\texttt{O}$ 组成的长字符串 $S$ 和一个整数 $K \geq 1$。计算将 $S$ 分解为若干子序列的方式数，其中每个子序列形如 $\texttt{MOOO...O}$（恰好包含 $K$ 个 $\texttt{O}$），结果对 $10^9+7$ 取模。

由于字符串非常长，我们不直接给出 $S$。而是给定一个整数 $L$（$1 \leq L \leq 10^{18}$）和一个长度为 $N$ 的字符串 $T$（$1 \leq N \leq 10^6$）。字符串 $S$ 是 $T$ 重复 $L$ 次拼接而成。


## 说明/提示

样例一解释：唯一分解方式是将前三个字符组成一个 $\texttt{MOO}$，后三个字符组成另一个 $\texttt{MOO}$。

样例二解释：共有六种不同的分解方式（大写字母组成一个 $\texttt{MOO}$，小写字母组成另一个 $\texttt{MOO}$）：
1. $\texttt{MmOOoo}$
2. $\texttt{MmOoOo}$
3. $\texttt{MmOooO}$
4. $\texttt{MmoOOo}$
5. $\texttt{MmoOoO}$
6. $\texttt{MmooOO}$

样例四解释：注意：结果需对 $10^9+7$ 取模。

- 测试点 $5\sim7$：$K=1$，$L=1$。
- 测试点 $8\sim10$：$K=2$，$N \leq 1000$，$L=1$。
- 测试点 $11\sim13$：$K=1$。
- 测试点 $14\sim19$：$L=1$。
- 测试点 $20\sim25$：无额外限制。

## 样例 #1

### 输入

```
2 6 1
MOOMOO```

### 输出

```
1```

## 样例 #2

### 输入

```
2 6 1
MMOOOO```

### 输出

```
6```

## 样例 #3

### 输入

```
1 4 2
MMOO```

### 输出

```
4```

## 样例 #4

### 输入

```
1 4 100
MMOO```

### 输出

```
976371285```

# 题解

## 作者：donaldqian (赞：2)

这个数据范围很吓人啊！

但是我们冷静思考一下，如果一个字符串中 $\text O$ 的个数不是 $\text M$ 的个数的 $K$ 倍，那么答案显然是 $0$。所以如果 $T$ 不满足上述条件，$S$ 也一定不满足，即无解。首先把这种东西判掉。

其次，考虑 $S$ 中最后一个 $T$ 串。容易发现我们只能将 $T$ 完整地划分成若干子序列。证明如下：
> 假设某种划分方案跨过了最后一个 $T$ 串。那么相当于用掉了最后一个 $T$ 串中的若干个 $\text O$，$cnt\text O = k\times cnt\text M$ 的条件就不满足了，得证。

于是就好做了，考虑对于单个 $T$ 串怎么做，显然倒序枚举，算出每个 $\text M$ 后面有多少个还没用过的 $\text O$，组合数学一下即可。最后输出答案的 $L$ 次幂。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 1e6 + 10, mod = 1e9 + 7;
int k, n, fac[maxn], inv[maxn], sum, ans;
char s[maxn]; ll l;

int quickpow (int a, ll b) {
	int x = 1; while (b) {
		if (b & 1) x = 1ll * x * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	}
	return x;
}
int C (int x, int y) { return (y < 0 || y > x) ? 0 : 1ll * fac[x] * inv[y] % mod * inv[x - y] % mod; }

signed main () {
	scanf("%d%d%lld%s", &k, &n, &l, s + 1), fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[n] = quickpow (fac[n], mod - 2), ans = 1;
	for (int i = n - 1; ~i; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
	for (int i = n; i >= 1; i--) {
		if (s[i] == 'O') sum++;
		else ans = 1ll * ans * C (sum, k) % mod, sum -= k;
	}
	ans *= (sum == 0);
	printf("%d", quickpow (ans, l));
	return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：2)

### 分析

因为后面的 $M$ 不能用前面的 $O$，并且字符串最后还有一个单独的 $S$，所以每个 $S$ 一定可以独立计算贡献，因此答案是单个 $S$ 的答案的 $l$ 次方。

考虑怎么计算单个 $S$ 的贡献，还是因为后面的 $M$ 不能用前面的 $O$，所以我们可以把一个 $S$ 分解为 $M$ 和 $O$ 交替出现的段，相邻的两段来计算贡献。设有 $n$ 个 $M$,$m$ 个 $O$，第一个 $M$ 要从后面的 $m$ 个 $O$ 中选出 $k$ 个，方案数是 $C _ {m} ^ {k}$，因为选走了 $k$ 个，因此第二个 $M$ 只能从 $m - k$ 个 $O$ 中选 $k$ 个，方案数为 $C _ {m - k} ^ k$，以此类推，每一个 $M$ 的贡献又相互独立，用乘法原理合并，因此这一段的方案数就是 $\prod _ {i = 1} ^ {n} C _ {m - k(i - 1)} ^ {k}$。

后面的 $O$ 不一定会被分解完，所以剩下的 $O$ 我们直接加到上一段里面，方案一样是独立的，用乘法原理合并。综上，答案为 $(\prod _ {i} (\prod _ {j = 1} ^ {n _ {i}} C _ {m _ i - k (j - 1)} ^ {k})) ^ {l}$。

### Code

```cpp
#include <bits/extc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 1e6 + 5,MOD = 1e9 + 7;
int k,n,l,fac[MAXN],ifac[MAXN];
string s;
vector<pair<char,int> > seg;
inline int qpow(int b,int p)
{
    int res = 1;
    while(p)
    {
        if(p & 1)
            res = res * b % MOD;
        b = b * b % MOD;
        p >>= 1;
    }
    return res;
}
inline int C(int m,int n)
{
    if(m < 0 || n < 0 || m < n)
        return 0;
    return fac[m] * ifac[n] % MOD * ifac[m - n] % MOD;
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> k >> n >> l;
    fac[0] = 1;
    for(int i = 1;i <= n;i++)
        fac[i] = fac[i - 1] * i % MOD;
    ifac[n] = qpow(fac[n],MOD - 2);
    for(int i = n - 1;i >= 0;i--)
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    cin >> s;
    for(int i = 0;i < n;i++)
    {
        if(seg.empty() || s[i] != seg.back().first)
            seg.emplace_back(s[i],1);
        else
            ++seg.back().second;
    }
    int M = 0,O = 0,res = 1;
    while(!seg.empty())
    {
        seg.back().second += O;
        O = seg.back().second,seg.pop_back();
        M = seg.back().second,seg.pop_back();
        for(int i = 1;i <= M;i++)
        {
            res = res * C(O,k) % MOD;
            O -= k;
        }
    }
    cout << qpow(res,l);
}
```

---

## 作者：tomAmy (赞：1)

简单绿，思维难度不大。~~我这么弱都能做出来。~~

### 题目大意：

一串由 M、O 组成的字符串，重复 $L$ 次得到一个新的字符串。把不同位置的 M、O 视作不同，若一个 M 向后匹配 $K$ 个 O，有多少种方案？保证有解。

### 思路：

先考虑其中一段循环节：

记遇到字符 O 的数量为 $O$，局部的方案数为 $ans$。

从后往前枚举。如果遇到 O，令 $O$ 增加一；如果遇到 M，从 $O$ 个中选 $K$ 个匹配，令 $O$ 减少 $K$，令 $ans$ 增加从 $O$ 个中选 $K$ 个的方案数，即 $\operatorname{C}^K_O$。

那如果重复 $L$ 次，每一段循环节之间会不会互相影响呢？答案很好想，不会。如果不同段的 M、O 匹配，说明有一段必然有剩余的 O，总体的 M、O 数量一定不匹配，必然无解，与题目描述矛盾。即只需要求出 $ans^L$ 即可，考虑使用快速幂。

接着我们解决一下 $\operatorname{C}^K_O$ 的计算问题：

$$\operatorname{C}^K_O = \dfrac{O(O-1)\cdots (O-K+1)}{K!}$$

其中 $O(O-1)\cdots (O-K+1)$ 直接暴力计算总量是 $O(N)$ 量级的，可以忽略。而除法不能在取模下直接计算，由于 $K$ 固定，可以先用费马小定理求出 $K!$ 的逆元，计算时乘上逆元即可。

贴上代码：

```cpp
#include <iostream>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
ll kmod;
ll f[1000005];
ll k, n, l;

ll power(ll x, ll y)
{
	if (y == 0) return 1;
	ll A = power(x, y / 2);
	if (y & 1) return A * A % mod * x % mod;
	else return A * A % mod;
}

ll C(ll x)
{
	ll ans = 1;
	for (int i = x - k + 1; i <= x; i++)
		ans = ans * i % mod;
	ans = ans * kmod % mod;
	return ans;
}

int main()
{
	cin >> k >> n >> l;
	string s;
	cin >> s;
	s = " " + s;
	
	ll ans1 = 1;
	for (int i = 1; i <= k; i++)
		ans1 = ans1 * i % mod;
	kmod = power(ans1, mod - 2);
	
	
	ll cnt = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == 'O') cnt++;
	
	
	
	
	ll O = 0, ans = 1;
	for (int i = n; i >= 1; i--)
	{
		if (s[i] == 'O') O++;
		else
		{
			ans = ans * C(O) % mod;
			O -= k;
		}
	}
	cout << power(ans, l) << endl;
	return 0;
}
```

---

## 作者：yuyc (赞：1)

其实从前往后做也是可以的。

## 解析

先不考虑 $L$。

一个很自然的想法是从前往后让每个 $\texttt{O}$ 跟一个在它前面的 $\texttt{M}$ 配对。问题在于 $K$ 的限制难以满足。

所以先满足 $K$ 的限制，对于每个 $\texttt{M}$，在它后面预留 $K$ 个空位用来放 $\texttt{O}$。这样对于每个 $\texttt{O}$，只需要随便找一个在它前面的 $\texttt{M}$ 的一个空位放进去就好，这一步的方案数就是当前空位个数，利用乘法原理就可以求出总方案数。

但是我们发现这样放的话 $\texttt{O}$ 的顺序是乱的，实际上 $\texttt{O}$ 的顺序应该是按照其在 $S$ 中的位置来排的，所以对于每个 $\texttt{M}$，需要除一个排列数。

然后来考虑 $L$。

如果 $T$ 无解，要么是当前的 $\texttt{O}$ 找不到一个合适的 $\texttt{M}$ 匹配，要么是 $\texttt{O}$ 不够拿来匹配。对于前者，不管后面拼多少个 $T$ 都匹配不了前面的 $\texttt{O}$；对于后者，不管后面拼多少个 $T$ 都拿不出多余的 $\texttt{O}$。也就是说，一个无解的 $T$，不管拼接多少次，它都是无解的。

如果 $T$ 有解，考虑拼接后前一段的 $\texttt{M}$ 会不会匹配上后一段的 $\texttt{O}$，答案是不会，因为这样的话前一段就会有 $\texttt{O}$ 匹配不上了。

综上，每一段对答案做的贡献是独立且相同的，最终要求的答案就是单段方案数的 $L$ 次幂。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)
#define mid ((l + r) >> 1)
#define eps 0.000001
using namespace std;
typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,int> pii;
const int N = 1e5 + 5, M = 2e5 + 5,base1 = 13331,base2 = 131,mod = 1e9 + 7;
int qmi(int a,ll b){
	int res = 1;
	while(b){
		if(b & 1) res = 1ll * res * a % mod;
		b >>= 1;
		a = 1ll * a * a % mod;
	}
	return res;
} 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	ll k,n,l;
	cin>>k>>n>>l;
	int fac = 1;
	for(int i=1;i<=k;i++){
		fac = 1ll * i * fac % mod;
	}
	string s;
	cin>>s;
	int now = 0,res = 1,cntm = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == 'M') now += k,cntm++;
		else{
			res = 1ll * res * now % mod;
			now--;
		}
	}
	assert(now == 0);
//	cout<<s.size()<<" "<<res<<" "<<fac<<" "<<cntm<<'\n';
	cout<<qmi(1ll * res * qmi(qmi(fac,cntm),mod - 2) % mod,l);
	return 0;
}
```

---

## 作者：Modulus998244353 (赞：1)

**解题思路**



---



不难发现，我们其实只要考虑 $S$ 的排列方式，答案就是这个数的 $l$ 次方。那如何去求 $S$ 中的排列方式呢？

我们可以从后往前算，不难发现，在 $S$ 中最后一个 M 的可选 O，就是 $n-p$ 个（这里假设最后一个 M 的位置就是 $p$），从这里往前推，那倒数第二个 M 的可选 O 其实就是，在它位置后面的所有的 O 数量减去第一个 M 选的 O 的数量，又由于我们可以知道第一个 M 选了多少个 O（$p$ 个)，所以，我们也可以知道倒数第二个 M 有多少个可选的 O，在继续往前推，我们就可以知道倒数第三个 M 的可选 O 了，继续往前推，就可以知道每一个 M 有多少个可选 O 了（这个 M 的位置往后数有多少个 O 减去前面的 M 拿走了多少个 O）。乘起来就好了。

**代码**



---



```c++
inline ll qpow(ll a, ll b)
{
	ll ans = 1;
	a = a % mod;
	while (b)
	{
		if (b & 1)
			ans = (ans * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return ans;
}
ll fac[Maxn], inv[Maxn];
inline void init()
{
	fac[0] = 1;
	for (int i = 1; i < Maxn; i++)
		fac[i] = (fac[i - 1] * i) % mod;
	for (int i = 0; i < Maxn; i++)
		inv[i] = qpow(fac[i], mod - 2);
}
inline ll C(ll n, ll k)
{
	if (n == k)
		return 1;
	ll res = (fac[n] * inv[n - k] % mod) * inv[k] % mod;
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll k, n, l;
	cin >> k >> n >> l;
	init();
	str s;
	cin >> s;
	s = '$' + s;
	int ms = 0, os = 0;
	for (int i = 1; i <= n; i++)
		if (s[i] == 'M')
			ms++;
		else
			os++;
	// cout<<ms<<' '<<os<<"\n";
	if ((ms * k) != os)
	{
		cout << 0;
		return 0;
	}
	ll ans = 1, now = 0;
	for (int i = n; i >= 1; i--)
	{
		if (s[i] == 'O')
			now++;
		else if (now < k)
		{
			cout << 0;
			return 0;
		}
		else
		{
			ans = (ans * C(now, k)) % mod;
			// cout<<now<<' '<<C(now,k)<<"\n";
			now -= k;
		}
		// cout<<ans<<' '<<i<<"\n";
	}
	ans = qpow(ans, l);
	cout << ans;
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

一道经典排列组合的数学题。~~（也是我银组 AK 后周一晚上尝试金组唯一通过的题）~~

根据题意，本题是计数类问题，我们需要求（凑）出形为 $\texttt{MO\dots O}$ 的序列，求总组合数。我们不妨对于每个 $\texttt{M}$，配凑出另 $K$个 $\texttt{O}$。而且，由于题目保证有解，字符串每一个循环节都能实现“自产自销”，即互不影响，这样，我们只要求出每个循环节分解方式数，答案即为其 $L$ 次方（快速幂可求）。

那么问题来了，这总组合数怎么求？此种题有两种思路，一是计数 DP，二是数学。由于本题算法要求线性，且本蒟蒻水平有限，只会数竞的组合问题，在此便用数学解法。我们发现，这题正推极为困难，而反推最后一个 $\texttt{M}$ 是容易的。于是我们从后往前推所有的 $\texttt{M}$，我们惊喜地发现，对于每个 $\texttt{M}$ 时，其组合情况就是简单的从后面没选的 $m$ 个 $\texttt{O}$ 中选 $K$ 个，这不正可以用组合公式计算吗，每个循环节结果即这些组合数相乘结果！

最后一个问题，如何在常数时间内解决组合数公式：不妨预处理 $1$ 至 $N$ 的阶乘，用组合数公式仅与阶乘有关的版本。处理取模下相除时，只需求逆元即可，首推费马小定理。

Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int k,n,l,cnt,ans=1,jc[1000010]={1};
char c[1000010];
int qp(int a,int b)//快速幂
{if(b==1) return a;
 int k=qp(a,b/2);
 if((b&1)==0)
 return k*k%mod;
 return k*k%mod*a%mod;
}
int zhs(int a,int b) //组合数公式
{int jj=jc[b]*qp(jc[b-a],mod-2)%mod;
 return jj*qp(jc[a],mod-2)%mod;
}
signed main()
{ios::sync_with_stdio(0);
 cin>>k>>n>>l>>c;
 for(int i=1;i<=1e6;i++)
 jc[i]=jc[i-1]*i%mod;
 for(int i=n-1;i>=0;i--)
 {if(c[i]=='M')
  ans=ans*(zhs(k,cnt-(n-i-1-cnt)*k))%mod;
  else
  cnt++;
 }
 cout<<qp(ans,l);
}
```

---

## 作者：I_will_AKIOI (赞：0)

我们发现从前往后选择 $\texttt{O}$ 会出现不够用的情况。例如样例 $\texttt{MOOMOO}$，你第一步把第一个 $\texttt{M}$ 和最后两个 $\texttt{OO}$ 配对，最后一个 $\texttt{M}$ 就没 $\texttt{O}$ 能用了。因为题目保证有解，因此这里出现了矛盾。

因此我们考虑从后往前选择 $\texttt{O}$。这样可以保证不会出现上述情况。对于每一个 $\texttt{M}$，我们计算在其后面有多少个 $\texttt{O}$ 还能使用，记为 $sum$。把答案乘上 $C(sum,k)$ 即可。由于每一个 $\texttt{M}$ 互不干扰，因此把每个 $\texttt{M}$ 的答案乘在一起就行。
 
最后要重复拼接 $L$ 次怎么办？由于保证有解，所以 $\texttt{M}$ 和 $\texttt{O}$ 能恰好匹配完，因此每一个 $T$ 之间也互不干扰，所以输出答案的 $L$ 次幂。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define N 1000005
using namespace std;
int n,m,k,sum,ans=1,fac[N],inv[N];
char c[N];
vector<int>v;
int Pow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main()
{
	ios::sync_with_stdio(0);
	fac[0]=1;
	for(int i=1;i<=1000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[1000000]=Pow(fac[1000000],mod-2);
	for(int i=999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	//预处理阶乘及其逆元用于计算组合数
	cin>>k>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		if(c[i]=='M') v.push_back(i);
	}
	v.push_back(n+1);
	for(int i=v.size()-1;i>0;i--)
	{
		sum+=v[i]-v[i-1]-1;//加入 O
		ans=ans*C(sum,k)%mod;
		sum-=k;//用掉的 O
	}
	cout<<Pow(ans,m);
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

首先，发现 $L=1$ 是好做的。

考虑倒着操作，设当前操作到位置 $i$，维护一个 $cnt$ 表示有多少可用的 $\texttt{O}$。

此时若 $s_i=\texttt{O}$，则 $cnt\leftarrow cnt+1$。

否则，就相当于从可用的 $\texttt{O}$ 中选 $k$ 个给 $\texttt{M}$，即 $ans\leftarrow \binom{cnt}{k},cnt\leftarrow cnt-k$。

注意判最后是否有多余的 $0$。

$L\neq 1$ 时，我们发现若答案不为 $0$，则两个 $T$ 之间的贡献是 $0$（只有 $T$ 内部的贡献），答案为 $0$ 时 $L=1$ 的答案也为 $0$，记 $L=1$ 时的答案为 $a$，最终答案就是 $a^L$。

做完了，复杂度 $O(|T|+\log L)$。

代码：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ldb long double 
#define bi __int128_t
using namespace std;
const int N=1e6+10;
const int mod=1e9+7;
int fac[N],inv[N];
int qp(int a,ll b){
    int x=1;
    while(b){
        if(b&1) x=1ll*a*x%mod;
        b>>=1;a=1ll*a*a%mod;
    }return x;
}
int C(int u,int d){
    if(u<0||d<0) return 0;
    if(u>d) return 0;
    return 1ll*fac[d]*inv[u]%mod*inv[d-u]%mod;
}
int cnt=0,res=1;
int k,n;ll L;
int main(){
    //freopen("3.in","r",stdin);
    //freopen("3.out","w",stdout);
    cin>>k>>n>>L;
    fac[0]=1;for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=qp(fac[n],mod-2);for(int i=n-1;i>=0;i--) inv[i]=1ll*(i+1)*inv[i+1]%mod;
    string s;cin>>s;s=' '+s;
    for(int i=n;i>=1;i--){
        if(s[i]=='O'){
            cnt++;
        }else{
            res=1ll*res*C(k,cnt)%mod;
            cnt-=k;
        }
    }if(cnt!=0) res=0;
    cout<<qp(res,L)<<endl;
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

我们从后往前考虑字符串 $S$。假设第 $i$ 位为 M，则我们需要找到 $K$ 个 O，且这 $K$ 个字符的下标均大于 $i$。我们设 $i$ 后面一共有 $o_i$ 个 O，$m_i$ 个 M，则后面可用的 O 一共有 $o_i-K m_i$ 个。将所有的 ${o_i-K m_i}\choose K$ 相乘就能得到答案。

考虑优化。由于 $S$ 是 $T$ 复制 $L$ 次得到的，那么我们考虑第 $c$ 个 $T$ 串的第 $p$ 位（下面用 $(c,p)$ 表示）。我们设在 $T$ 中，第 $p$ 位后面一共有 $m'_p$ 个 M 和 $o'_p$ 个 O，总共有 $M$ 个 M 和 $O$ 个 O。那么有一个很显然的性质，即 $O=KM$。因此，第 $(c,p)$ 位后面可用的 O 一共有 $o_p-Km_p$ 个（因为在第 $c+1$ 到 $L$ 个 $T$ 串中，$O$ 和 $KM$ 恰好抵消）。所以答案为

$$\prod_{c=1}^L\prod_{p=1}^N {{o'_p-Km'_p}\choose K}=(\prod_{p=1}^N {{o'_p-Km'_p}\choose K})^L$$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int P=1e9+7;
char s[1010101];
int N,K,L,O[1010101],M[1010101],frac[1010101],ans=1;
int qp(int a,int b){
	int r=1;
	for(;b;a=a*a%P,b>>=1)if(b&1)r=r*a%P;
	return r;
}int C(int n,int k){
	return frac[n]*qp(frac[k],P-2)%P*qp(frac[n-k],P-2)%P;
}
signed main(){
	cin>>K>>N>>L>>s+1;
	frac[0]=1;
	for(int i=1;i<=N+5;i++)frac[i]=frac[i-1]*i%P;
	for(int i=N;i;i--)
		if(s[i]=='O')O[i-1]=O[i]+1,M[i-1]=M[i];
		else O[i-1]=O[i],M[i-1]=M[i]+1;
	for(int i=1;i<=N;i++)
		if(s[i]=='M')
			ans=ans*C(O[i]-K*M[i],K)%P;
	cout<<qp(ans,L)<<endl;
	
	return 0;
}
```

---

## 作者：Yao_yx (赞：0)

题目保证 $S$ 可被分解，故 $T$ 可被分解，否则 $S$ 中最后一个 $T$ 将无法匹配完。

所以对每个 $T$ 计算方案数，从后往前枚举，遇到字符 $M$ 就乘上一个组合数，即从后面剩余的 $O$ 选择 $k$ 个的方案数。最后方案数的 $L$ 次幂即为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
const int mod = 1e9 + 7;

int n, k, ans = 1; long long l; string s;
int fac[MAXN], inv[MAXN];

int qpow(int a, int b){ int res = 1; for(; b; b >>= 1, a = 1ll * a * a % mod) if(b & 1) res = 1ll * res * a % mod; return res; }
int C(int x, int y){ return (x < y || x < 0 || y < 0 ? 0 : 1ll * fac[x] * inv[y] % mod * inv[x - y] % mod); }

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> k >> n >> l >> s; s = " " + s;
	fac[0] = 1; for(int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n], mod - 2); for(int i = n; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	for(int i = n, j = 0; i >= 1; --i){
		(s[i] == 'O' ? j++ : (ans = 1ll * ans * C(j, k) % mod, j -= k));
	}
	cout << qpow(ans, l % (mod - 1));
	
	return 0;
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
简单题。
### Solution
首先设字符 $\texttt M$ 的数量为 $cntm$，字符 $\texttt O$ 的数量为 $cnto$，显然有 $\frac{cnto}{cntm}=k$。

然后一个串 $T$ 内的 $\texttt M$ 和 $\texttt O$ 一定能够互相匹配，所以只需要求出一个串的方案数然后乘 $L$ 次即可。

从后往前考虑，如果我们考虑到字符 $\texttt M$，设其后缀（不包括它自己）有 $prem$ 个字符 $\texttt M$，有 $preo$ 个字符 $\texttt O$，那么方案数会乘上一个 $\binom{preo-prem\times k}{k}$。

于是我们就做完了。
```
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 1000010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int >
#define fi first
#define se second

using namespace std;
const ll mod=1e9+7;
char s[N];
ll fac[N],inv[N];
ll k,n,l;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll ksm(ll x,ll y){
	ll p=1;
	while(y){
		if(y&1ll) p=p*x%mod;
		x=x*x%mod;
		y>>=1ll;
	}
	return p;
}
ll C(int x,int y){
	if(x<y) return 0;
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}

int main()
{
	fac[0]=1;
	For(i,1,N-1) fac[i]=fac[i-1]*i%mod;
	inv[N-1]=ksm(fac[N-1],mod-2);
	Rof(i,N-2,0) inv[i]=inv[i+1]*(i+1)%mod;
	k=read(),n=read(),l=read();
	cin>>(s+1);
	ll ans=1,c1=0,c2=0;
	Rof(i,n,1){
		if(s[i]=='O') c1++;
		else{
			ans=ans*C(c1-c2*k,k)%mod;
			c2++;
		}
	}
	cout<<ksm(ans,l);
	return 0; 
}
/*

*/
```

---

