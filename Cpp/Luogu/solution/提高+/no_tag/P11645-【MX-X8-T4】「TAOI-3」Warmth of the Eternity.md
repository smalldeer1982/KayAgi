# 【MX-X8-T4】「TAOI-3」Warmth of the Eternity

## 题目背景

原题链接：<https://oier.team/problems/X8E>。

## 题目描述

Kukuru 是 AI 领域大神。[如果你是 E.Space 的粉丝的话](/problem/P8294)，你应该知道，$n$ 个 AI 会组成一个树形结构。具体地，对于 $n$ 个 AI，它们之间会构建出恰好 $(n-1)$ 条通路，每条通路会连接两个 AI，并且任意两个 AI 都被直接或间接地连接起来。

但是 Kukuru 忘记了她的 $n$ 个 AI 是如何连接的了。所幸，她还记得：对于所有 $i$，假如删去第 $i$ 个 AI 并断开所有和它相连的通路之后，剩下的 AI 组成的所有连通块的大小。

称若干 AI 形成一个连通块，当且仅当它们两两之间可以通过若干通路互相连接，且没有该连通块外的 AI 与连通块内的 AI 之间存在通路。一个连通块的大小被定义为这个连通块包含的 AI 的个数。

现在 Kukuru 想要知道：在给定这些信息的情况下，这 $n$ 个 AI 有多少种可能的连接方式呢？称两种连接方式不同，当且仅当在一个方案中某两个 AI $u,v$ 之间存在直接通路，而在另一种方案中不存在。因为方案可能很多，所以 Kukuru 只需要你告诉她答案对 $998244353$ 取模的结果就好了。你能解决这个问题吗？**特别地，保证存在至少一种合法的 AI 连接方式符合题意**。

## 说明/提示

**【样例解释 \#1】**

![](https://cdn.luogu.com.cn/upload/image_hosting/425v8z3m.png)

**【样例解释 \#2】**

![](https://cdn.luogu.com.cn/upload/image_hosting/h6wzikqz.png)

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（16 分）：$n \leq 8$。
- 子任务 2（9 分）：存在合法的 AI 连接方式，使得至少一个 AI 与所有其它 AI 直接相连。
- 子任务 3（9 分）：存在合法的 AI 连接方式，使得 AI 都和不超过 $2$ 个其它 AI 直接相连。
- 子任务 4（21 分）：$n \leq 20$。
- 子任务 5（18 分）：$n \leq 5\times 10^3$。
- 子任务 6（27 分）：无特殊限制。

对于所有数据，保证 $2 \leq n \leq 3\times 10^5$。保证取模前的真实答案大于 $0$。

## 样例 #1

### 输入

```
4
1 3
2 1 2
2 1 2
1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
2 2 4
1 6
3 1 1 4
1 6
2 3 3
2 1 5
1 6```

### 输出

```
3
```

## 样例 #3

### 输入

```
20
2 18 1 
3 2 5 12 
2 2 17 
2 1 18 
2 14 5 
1 19 
1 19 
1 19 
3 16 2 1 
1 19 
2 18 1 
2 15 4 
3 16 1 2 
2 15 4 
2 13 6 
1 19 
2 18 1 
1 19 
1 19 
4 8 1 3 7 ```

### 输出

```
483840
```

## 样例 #4

### 输入

```
50
1 49 
1 49 
2 48 1 
1 49 
1 49 
2 36 13 
1 49 
1 49 
3 39 1 9 
1 49 
1 49 
5 6 1 39 1 2 
2 48 1 
6 1 5 1 4 37 1 
1 49 
1 49 
1 49 
2 1 48 
2 29 20 
1 49 
2 1 48 
2 1 48 
4 46 1 1 1 
1 49 
1 49 
1 49 
1 49 
1 49 
7 1 3 1 1 41 1 1 
4 30 1 4 14 
1 49 
1 49 
5 1 1 45 1 1 
1 49 
1 49 
5 11 5 21 11 1 
1 49 
1 49 
3 1 1 47 
1 49 
3 1 2 46 
1 49 
1 49 
1 49 
1 49 
4 1 1 2 45 
1 49 
1 49 
1 49 
4 44 2 1 2 ```

### 输出

```
268867231
```

# 题解

## 作者：Register_int (赞：14)

对于一个点 $u$，我们将它的每个连通块个数 $a_{u,i}$ 视为一个**接口**，称其**大小**为对应的 $a$ 值。那么你容易发现，两个接口可以用一条边连起来，当且仅当接口大小相加为 $n$。并且，一个点的接口大小总和为 $n-1$。

你发现叶子是最特殊的，因为它必然只有一个大小为 $n-1$ 的接口，那么叶子必然会把所有大小为 $1$ 的接口全部匹配掉。这个方案数是好算的，相当于每个其他点选固定个数的叶子挂上去，组合数算一算即可。那么大小为 $1,n-1$ 的接口就被排除掉了。

有啥用呢？你还会发现更加奇妙的事情。考虑一个节点若有大小为 $n-2$ 的接口会发生什么？因为接口大小总和为 $n-1$，那么剩下的那个接口大小必定为 $1$，已经匹配掉了。所以我们可以将大小 $n-2$ 的接口再次视为叶子接口，与所有大小为 $2$ 的接口匹配。更近一步地，假设当前我们将所有 $\le k$ 的接口匹配完毕了，那么删掉这些接口后，大小为 $n-k$ 的接口必然是叶子接口！

从小到大枚举 $k$ 即可。剩下一个 corner case 就是 $n$ 为偶数时 $k=n/2$ 的情况。不过大小都为 $n/2$ 了，说明砍掉接口这条边，树会恰好分成大小相等的两半。这个的方案数显然为 $1$，所以不用管就好了。

有更聪明的实现方法，因为对于大小 $<\lfloor(n+1)/2\rfloor$ 的接口，其贡献都是个数的阶乘倒数，反之贡献为个数的阶乘，可以边读入来算。时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;
const int mod = 998244353;

inline 
int qpow(int b, int p) {
	int res = 1;
	for (; p; p >>= 1, b = (ll)b * b % mod) if (p & 1) res = (ll)res * b % mod;
	return res;
}

int n, m, a[MAXN], c1[MAXN], c2[MAXN], fac[MAXN], ifac[MAXN], ans = 1;

int main() {
	scanf("%d", &n), *fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &m);
		for (int j = 1; j <= m; j++) scanf("%d", &a[j]), c1[a[j]]++, c2[a[j]]++;
		for (int j = 1; j <= m; j++) {
			if (a[j] < (n + 1) / 2) ans = (ll)ans * ifac[c1[a[j]]] % mod;
			c1[a[j]] = 0;
		}
	}
	for (int i = n / 2 + 1; i < n; i++) ans = (ll)ans * fac[c2[i]] % mod;
	printf("%d", ans);
}
```

做完这题可以去做[猫娘](//www.luogu.com.cn/problem/P11628)。

---

## 作者：chenly8128 (赞：8)

## 思路

第一眼：什么？形态数？Prüfer 序列？

第二眼：不对啊，T3 不可能这么难，肯定又简单的方法。只需要排列组合。

## 解法

### 1
首先，可以把每一条边都考虑一遍。对于一条边，它两边都联通块的总节点数一定为 $n$。所以可以统计一下输入数据中不同大小的联通块的数量，设大小为 $i$ 的联通块共有 $cnt_i$ 个。对于任意小于等于 $\dfrac{n}{2}$ 的联通块大小 $i$，大小为 $i$ 的两个联通块之间位置可以任意互换，因此有 $A_{cnt_i}^{cnt_i}$ 种可能性。根据乘法原理，把可能性数乘起来，就能得到答案。

但是如果你按照上面的解法写代码，会发现连样例 2 都过不了。

### 2

为什么呢，因为如下情况被当成了两种，计算了两遍。
![](https://cdn.luogu.com.cn/upload/image_hosting/i9ucpvll.png)  ![](https://cdn.luogu.com.cn/upload/image_hosting/0kqzfa06.png)

因此，我们需要把 1 中算出的答案除掉重复数量。对于一个节点，如果去掉它有 $k$ 个联通块大小相等，那么答案应该除以 $k{!}$。当然，除法要使用逆元。

### 3

然后就过了。


```cpp

// Author: chenly8128
// Created: 2025-01-31 14:42:02

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 3e5+10;
const int mod = 998244353;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
ll ghi[MAXN],d = 1;
int cnt[MAXN],n;
map <int,int> m;
ll qpow (ll a) {
	ll ans = 1;int k = mod-2;
	while (k) {
		if (k&1) ans = ans * a % mod;
		a = a * a % mod;
		k >>= 1;
	}
	return ans;
}
int main (void) {
	ghi[0] = 1;n = read();
	for (int i = 1;i <= n;i++) ghi[i] = ghi[i-1] * i % mod;
	for (int i = 1;i <= n;i++) {
		int k = read(),x;
		m.clear();
		for (int i = 1;i <= k;i++) {
			x = read();
			if (m.find(x) == m.end()) m[x] = 1;
			else {
				d = d * (m[x]+1) % mod;
				m[x]++;
			}
			cnt[x]++;
		}
	}
	ll ans = 1;
	if (n%2 == 0) cnt[n>>1] >>= 1;
	for (int i = 1;i <= n/2;i++)
		ans = ans * ghi[cnt[i]] % mod;
	printf ("%lld\n",ans * qpow(d) % mod);
	return 0;
}
```

---

## 作者：gcx12012 (赞：7)

### 前言
这个题真的比 MX-X8-T5 简单太多了啊。
### Solution
我们先钦定树的重心作为根来计数，考虑重心有以下性质：

- 删去有关树的重心的点和边，其余子树的大小 $sz\le \frac{n}{2}$。

这样我们就可以很方便地处理题目所给的信息。在以树的重心为根节点的前提下，对于非根节点，设断开该节点后的最大子树大小为 $mx$，其子树大小为 $n-mx$。

于是我们就得出了每个非根节点的子树大小，对于题目所给的每个子树大小 $d_i$，只需要匹配对应大小的子树即可。

然后注意一下相同 $d_i$ 的个数需要用组合数来算，这个题就做完了。时间复杂度为 $O(n \log n)$。

代码如下。
### Code

```cpp
const ll mod=998244353;
vector<int >e[N];
int cnt[N];
ll fac[N],inv[N];
int n,rt;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll ksm(ll x,ll y){
	ll p=1;
	while(y){
		if(y&1) p=p*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return p;
}
ll C(int u,int v){
	if(u<v) return 0;
	return fac[u]*inv[v]%mod*inv[u-v]%mod;
}

int main()
{
	fac[0]=1;
	For(i,1,N-1) fac[i]=fac[i-1]*i%mod;
	inv[N-1]=ksm(fac[N-1],mod-2);
	Rof(i,N-2,0) inv[i]=inv[i+1]*(i+1)%mod;
	n=read();
	For(i,1,n){
		int u=read();
		For(j,1,u) e[i].pb(read());
		sort(e[i].begin(),e[i].end());
		cnt[n-e[i][u-1]]++;
		if(e[i][u-1]<=n/2) rt=i;
	}
	ll ans=1;
	cnt[n-e[rt][e[rt].size()-1]]--;
	For(i,1,n){
		int len=e[i].size()-1,l=0,r=0;
		if(i==rt) len++;
		while(l<len){
			while(r<len-1 && e[i][r+1]==e[i][l]) r++;
			ans=ans*C(cnt[e[i][l]],r-l+1)%mod;
			cnt[e[i][l]]-=(r-l+1);
			l=r+1;
			r=l;
		}
	}
	cout<<ans;
    return 0;
}
/*

*/
```

---

## 作者：251Sec (赞：6)

### 题意简述

给定一棵无根树删去每个点之后得到的所有连通块大小，问这棵树的方案数。对 $998244353$ 取模。

$1 \leq n \leq 3\times 10^5$。保证取模前的真实答案大于 $0$。

### 解法

先考虑这样一个问题：给定有根树每个点的所有儿子的子树大小，问方案数。

首先我们可以得到每个点本身的子树大小，然后我们把所有点按照它排序，然后尝试依次加入每个点，维护当前加点形成的森林。可以发现每个时刻森林中每种大小的连通块个数都是固定的，可以维护出来，每次加入一个点的贡献可以简单计算。

接下来考虑原问题，考虑找到树的任意一个重心，即所有相连的连通块大小都 $\le \frac{n}{2}$ 的节点，然后把它作为根，其它点全部删掉相连的大小 $\ge \frac{n}{2}$ 的连通块。这就转化成了上面的问题。

---

## 作者：Y2y7m (赞：5)

纯纯诈骗题。

就是你发现两个点 $u$，$v$ 之间能连边，当且仅当分别删掉这两个点后，删掉点 $u$ 后出现的连通块中存在一个连通块大小 $x$ 与删掉点 $v$ 后出现的连通块中的一个连通块的大小 $y$ 满足 $x+y=n$。

然后我们钦定一条边在 $x$ 和 $y$ 中较小的那一边计算。不妨设 $x$ 较小。

然后直接将大于 $\frac{n}{2}$ 的那部分扔到桶里，枚举小于 $\frac{n}{2}$ 的连通块组合数计算即可。

当我们算到点 $i$ 的时候，我们设其小于 $\frac{n}{2}$ 的连通块为大小分别为 $a_{i,1},a_{i,2},...,a_{i,k_i}$，我们对于 $i$ 的每一种不同的 $a_{i,j}$，假设其出现了 $x_{i,a_{i,j}}$ 次，剩余的未被计算的 $n-{a_{i,j}}$ 的连通块数量为 $r$，那么将答案乘上 $C_{r}^{x_{i,a_{i,j}}}$ 即可。

代码：


```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
const int maxn=3e5+10,mod=998244353;
int n;
map<int,int> b[maxn];
int q_pow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int fac[maxn],inv[maxn];
void init()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,inv[i]=q_pow(fac[i],mod-2);
}
int C(int n,int m)
{
	if(n<0||m<0||n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int cnt[maxn];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	init();
	for(int i=1;i<=n;i++)
	{
		int d,x;
		cin>>d;
		for(int j=1;j<=d;j++)
		{
			cin>>x;
			b[i][x]++;
			if(x>n/2) cnt[x]++;
		}
	}
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		for(pii x:b[i])
		{
			if(x.fi>=n/2) continue;
			int c=x.se;
			ans=ans*C(cnt[n-x.fi],c)%mod;
			cnt[n-x.fi]-=c;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：LostKeyToReach (赞：4)

### 题目大意

给定 $n$ 个 AI，它们之间连成一棵树。对每个节点 $i$，若删去它，则会分裂成 $d_i$ 个连通块，大小分别为：

$$
c_{i, 1}, c_{i, 2}, \ldots ,c_{i, d_i}
$$

求所有满足条件的树的数量对 $998244353$ 取模的结果。

### 题目解法

容易发现 $d_i$ 为 $i$ 节点的度数，那么肯定有：

$$
\sum_{i = 1} ^ n d_i = 2(n - 1).
$$

这一步暂时先放着，待会儿用。

接下来设 $\exists i, j$，满足 $i$ 和 $j$ 有直接连边，那么：

- 当「删去 $i$」时，$j$ 所在连通块大小为 $c_{i, x}, 1 \le x \le d_i$。
  
- 当「删去 $j$」时，$i$ 所在连通块大小为 $c_{j, y}, 1 \le y \le d_j$。

在一棵树中，删除 $i$ 和删除 $j$ 得到的那两个「含有对方的连通块」实际上是互补的：它们加在一起正好包含整棵树的所有 $n$ 个节点，但由于「删点」各自去掉了 $i$ 或 $j$ 本身，所以这两个连通块在原图里其实是不重叠的。由此可得：

$$
c_{i, x} + c_{j, y} = n.
$$

那么我们可以得到一个重要结论：**若 $i$ 和 $j$ 相邻，则必存在一对 $\bigl(c_{i,x},\,c_{j,y}\bigr)$ 使它们之和等于 $n$。反之，若能在两个点的「子树大小多重集」里分别找到一对数之和为 $n$，就可以作为一条 $i$ 到 $j$ 的边。**

我们把节点的所有 $c_{i, x}$ 收集在一起构成一个大小为 $\displaystyle\sum_{i = 1} ^ n d_i = 2(n - 1)$ 的多重集 $S$。树的每条边都会对应一对 $(k, n - k)$，此时我们得到「边的集合」，再确保第 $i$ 个点的度数为 $d_i$ 便可求出方案数。

**问题：如何求出方案数？**

我们先令 $\text{cnt}_x$ 为所有 $c_{i, x}$ 中连通块大小为 $x$ 的数量，$\text{mult}_{i, x}$ 为删除第 $i$ 个点时产生的连通块中大小为 $x$ 的连通块数量，考虑分为两步求解：

- **统计「纯粹的」方案数（不考虑重复）**：

  > - 当 $k \neq n - k$ 时，两者必须一一匹对，所以这里的方案数为 $\text{cnt}_k!$。因为题目保证有解，所以 $\text{cnt}_k$ 必然等于 $\text{cnt}_{n - k}$。
  > - 当 $n \equiv 0 \pmod{2}$ 时，我们需要配对 $\displaystyle\frac{\text{cnt}_{\frac{n}{2}}}{2}$ 对 $\displaystyle(\frac{n}{2}, \frac{n}{2})$，设 $k = \displaystyle\frac{\text{cnt}_{\frac{n}{2}}}{2}$，那么此时的方案数为：
  
  $$
  k!! = \frac{k!}{2^{\frac{k}{2}}(\frac{k}{2})!}.
  $$

  这些式子相乘即可求出。

- **去除重复的方案**：

  > - 我们发现这个算法会重复计算。举个例子，比如 $\{2, 2, 3\}$，两个 $2$ 并无顺序可言，无论把「第 $1$ 个 $2$」匹配给邻居 $A$，把「第 $2$ 个 $2$」匹配给邻居 $B$，都对应一组同样的边 $\{(i, A), (i, B), (i, ?)\}$，只要这两个邻居在最终树中的度数信息等都吻合，就不能算作两种不同的树。
  > - 为了避免这个问题，我们对于每个节点 $i$，将答案乘上 $\displaystyle\frac{1}{\text{mult}_{i, x}!}$ 即可。

综上，我们的答案可以表示为：

> 令 $M$ 为：
>
> $$
> \left(\prod_{2k < n}\text{cnt}_k!\right) \times \begin{cases}(\frac{\text{cnt}_{\frac{n}{2}}}{2})!!, & n\text{ is even,}\\[6pt]1, & n\text{ is odd.}\end{cases}
> $$
>
> 令 $D$ 为：
>
> $$
> \prod_{i = 1} ^ n \prod_{x}\left(\text{mult}_{i, x}!\right)
> $$
>
> 则答案为 $\displaystyle\frac{M}{D}$。

### 复杂度分析

- 时间复杂度：$O(n + \log P)$。

- 空间复杂度 $O(n)$。

### 代码实现

```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 6, P = 998244353;

int power(int a, int b, int p) {
    int ans = 1;
    a %= p;
    while (b > 0) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> d(n + 1, 0);
    int sum = 0;
    std::vector<int> freq(n + 1, 0);
    std::vector<std::unordered_map<int, int>> cont(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> d[i];
        sum += d[i];
        for (int j = 1; j <= d[i]; ++j) {
            int sz;
            std::cin >> sz;
            ++freq[sz];
            ++cont[i][sz];
        }
    }
    int MAX = 2 * (n - 1);
    std::vector<int> fact(MAX + 1, 0), ifact(MAX + 1, 0);
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i) {
        fact[i] = fact[i - 1] * i % P;
    }
    ifact[MAX] = power(fact[MAX], P - 2, P);
    for (int i = MAX - 1; i >= 0; --i) {
        ifact[i] = ifact[i + 1] * (i + 1) % P;
    }
    int m = 1;
    for (int k = 1; k * 2 < n; ++k) {
        m = m * fact[freq[k]] % P;
    }
    auto so = [&](int x) -> int {
        int res = fact[x];
        res = res * power(power(2, x / 2, P), P - 2, P) % P;
        res = res * ifact[x / 2] % P;
        return res;
    };
    if (n % 2 == 0) {
        int x = freq[n / 2];
        m = m * so(x) % P;
    }
    int dd = 1;
    for (int i = 1; i <= n; ++i) {
        for (auto & kv : cont[i]) {
            dd = dd * fact[kv.second] % P;
        }
    }
    std::cout << m * power(dd, P - 2, P) % P;
}

int32_t main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);

    int t;
    // std::cin >> t;
    t = 1;

    while (t--) {
        solve();
    }

    return 0;
}
```

---

## 作者：_lmh_ (赞：2)

经典套路，把重心拉上来作为根，只考虑大小 $<\frac{n}{2}$ 的子树，否则如果有两个重心则会重复计数。这样的话，每个节点的子树大小就是固定的。

现在按照子树大小从小到大考虑每一个节点，注意到任一特定大小的子树两两不同（与它们的根节点编号一一对应），所以从这里面选几个拼到节点下面相当于从这些根节点当中选几个拼到下面，这些子树长什么样子不重要。

然后问题转化成把 $k$ 个节点分成大小固定的几个互不相同的组（设其大小为 $k_1\sim k_l$）里面，这是经典问题，答案就是 $\frac{k!}{k_1!k_2!\cdots k_l!}$，预处理阶乘即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=300007,MOD=998244353;
ll n,m,cnt[N],fac[N],ifac[N],ans=1;
map<ll,ll> mp;
ll qpow(ll x,ll k){
	ll sum=1;
	while(k){
		if (k&1) (sum*=x)%=MOD;
		(x*=x)%=MOD;k>>=1;
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	for (int i=fac[0]=1;i<N;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[N-1]=qpow(fac[N-1],MOD-2);
	for (int i=N-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	cin>>n;
	for (int x,i=1;i<=n;++i){
		cin>>m;mp.clear();
		while(m--){
			cin>>x;
			if (x<n/2){++cnt[x];++mp[x];}
		}
		for (auto p:mp) (ans*=ifac[p.second])%=MOD;
	}
	for (int i=1;i<n/2;++i) (ans*=fac[cnt[i]])%=MOD;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：1)

笑点解析：这题在 T2 之前过。

考虑拓扑排序，因为树最多只有两个重心你其实可以把 $\ge \dfrac{n}{2}$ 的限制全部丢掉也可以做。

那么我们考虑一个朴素的想法，先把 $d_i=1$ 的处理一下，然后把这些点加入一个虚拟的连通块大小桶里，每次当一个点连的所有连通块大小的最大值被选到就处理这个点，把每个连通块拿走一个算方案。

这个基本上是对的了，但是同大小连通块之间拿的顺序没有区分，所以要去重。加上就对了，线性求逆元则时间复杂度 $O(n)$。

前两篇题解没贴代码那我贴一个吧不然又要被踩了哈哈哈。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> p[300007];
int d[300007],s[300007];
vector<int> w[300007];
const int mod=998244353;
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b=b>>1;
	}
	return ans;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
		p[i].push_back(0);
		for(int j=1,x;j<=d[i];j++) scanf("%d",&x),p[i].push_back(x);
		sort(p[i].begin(),p[i].end());
		w[p[i][d[i]-1]].push_back(i);
	}
	int ans=1;
	for(int i=0;i<=n;i++){
		for(int x:w[i]){
			int r=1,ww=1,lst=0;
			for(int j=1;j<=d[x];j++){
				if(s[p[x][j]]>0&&p[x][j]<n/2){
					r+=p[x][j],ans=1ll*ans*s[p[x][j]]%mod,s[p[x][j]]--;
					if(lst!=p[x][j]) ww=0;
					lst=p[x][j],ww++;
					ans=1ll*ans*qpow(ww,mod-2)%mod;
				}
			}
			s[r]++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：1)

# P11645 题解

赛时硬控两个半小时。

## 思路

~~首先数据保证有解，省去了判无解的一堆麻烦，剩下的是求解的更多麻烦。~~

对于两个节点 $u,v(u \neq v)$，$u$ 一定存在于输入数据中断开 $v$ 形成的某一个连通块内，$v$ 也一定存在于输入数据中断开 $u$ 形成的某一个连通块内，而当 $u,v$ 相邻时，这两个连通块的并，就是一整棵树，因此这两个连通块的大小之和应当为 $n$。

也就是说，输入数据中，大小为 $i$ 的连通块应当寻找大小为 $n-i$ 的连通块，这两个点接到一起。这里可以证明直接选的话两个连通块不会出自同一个 $u$，因为它们的大小之和为 $n$，加上 $u$ 则有 $n+1$ 个点，显然不可能。

拿样例输入 $2$ 为例子：

```plaintext
7
2 2 4
1 6
3 1 1 4
1 6
2 3 3
2 1 5
1 6
```

考虑 $(1,6)$ 的情况，将大小分别为 $1$ 和 $6$ 的连通块取出来，去掉其它数字，列出来是这样的：

```plaintext
6
1 1
6
1
6
```

第一行表示要寻找一个 $1$ 匹配，第二行表示要寻找两个 $6$ 匹配，依此类推。

这里可以证明同一行内出现重复的只会是数字更小者，因为更大者大于等于 $\frac{n}{2}$，出现重复意味着至少出现两次，那么它们的和就肯定大于等于 $n$ 了，而删除一个点形成的连通块的大小总和肯定不超过 $n-1$。

于是，剩下的 $1$ 的个数分别为 $2,1$，去匹配 $3$ 个单独的 $6$，这里就是排列组合了，先是 $3$ 个中取 $2$ 个来组合，剩下 $1$ 个中取 $1$ 个来组合。

枚举其它可能的组合，$(1,n)$ 接着是 $(2,n-1)$，然后一直枚举下去，每种组合的方案数的乘积，就是最后的答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[++idx]=c,c=getchar();
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=300005;
const int mod=998244353;

int n;
int ans=1;
unordered_map<int,int> arr[N];
unordered_set<int> hs[N];
int fac[N],inv[N];

bool cmp(const int& a,const int& b) {
    return a>b;
}

int exgcd(int a,int b,int& x,int& y) {
    if (!b) {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

int inverse(int a) {
    int x,y;
    exgcd(a,mod,x,y);
    x=(x%mod+mod)%mod;
    return x;
}

int C(int n,int m) {
    return (((i64)fac[n]*inv[m])%mod)*inv[n-m]%mod;
}

void init() {
    fac[0]=fac[1]=1;
    inv[0]=inv[1]=1;
    _rep(i,2,N-1) {
        fac[i]=((i64)fac[i-1]*i)%mod;
        inv[i]=inverse(fac[i]);
    }
}

int main() {
    init();
    read(n);
    _rep(i,1,n) {
        int d;
        read(d);
        _rep(j,1,d) {
            int a;
            read(a);
            arr[i][a]++;
            hs[a].emplace(i);
        }
    }
    // puts("================test===============");
    // _rep(i,1,n) {
    //     int j=n-i;
    //     if (i>j) break;
    //     _iter(it,hs[i]) {
    //         _rep(k,1,arr[*it][i]) printf("%d ",i);
    //         putchar(10);
    //     }
    //     if (i!=j) {
    //         _iter(it,hs[j]) {
    //             _rep(k,1,arr[*it][j]) printf("%d ",j);
    //             putchar(10);
    //         }
    //     }
    //     putchar(10);
    // }
    _rep(l,1,n) {
        int r=n-l;
        if (l>=r) break;
        // printf("l,r: %d %d\n",l,r);
        vector<int> vec;
        int cnt=0;
        _iter(it,hs[l]) vec.emplace_back(arr[*it][l]),cnt+=arr[*it][l];
        _iter(it,hs[r]) vec.emplace_back(arr[*it][r]),cnt+=arr[*it][r];
        if (vec.empty()) continue;
        sort(vec.begin(),vec.end(),cmp);
        // printf("vec: "); _iter(it,vec) printf("%d ",*it); putchar(10);
        int pos;
        int sum=0;
        _rep(i,0,(int)vec.size()-1) {
            sum+=vec[i];
            if (sum==cnt/2) {
                pos=i;
                break;
            }
            assert(sum<cnt/2);
        }
        cnt=(int)vec.size()-1-(pos+1)+1;
        // cout<<"TEST: "<<cnt<<" "<<pos<<endl;
        _rep(i,0,pos) {
            int k=C(cnt,vec[i]);
            // printf("C(%d,%d) = %d\n",cnt,vec[i],k);
            cnt-=vec[i];
            ans=(i64)ans*k%mod;
        }
    }
    write(ans);
    return 0;
}
```

---

## 作者：MicroSun (赞：0)

我超 喜欢这题。

---

首先，你可以发现题目给你的是树上每个点的邻边数和以它为根时每个子树的大小。

看到这个形式，你想到了什么？没错，重心！然后你想到，这既然是一颗无根树，那试着以重心为根拎起这棵树会怎样？我们飞快地就发现了非常良好的性质！根据重心的定义，以重心为根时每棵子树大小都小于等于 $\frac n 2$，那么对于每个非根节点，它的每棵子树大小必然也小于 $\frac n 2$，则唯一一条大于等于 $\frac n 2$ 的边就是连接它和它父亲的边！以它为根的子树大小可以通过直接减去非其子树的节点个数来得到！既然有这么多良好性质，那么是这么做没错了。

开场 1h 推到了这里，然后过了一会就被拉去看电影了。下面的部分全世界就我场上没推出来。

你可以发现，贡献是独立的，我们可以对于每种子树大小拆开来计算。我们将每个点需要的子树大小和其匹配，问题就转变为了将元素划分为固定大小的几个组的方案数之积。这显然可以直接算。

然后就做完了。我也是真的菜完了。


Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;++i)
#define dep(i,s,e) for(int i=s;i>=e;--i)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int N=3e5+10,mod=998244353;

map<int,int> mp[N],mp2;
ll fac[N],ifac[N];
ll fp(ll a,ll n){
	ll ret=1;
	while(n){
		if(n&1) ret=ret*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return ret;
}
ll C(int n,int m){
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void __solve(){
	int n,rt;cin>>n;
	fac[0]=1;
	rep(i,1,n) fac[i]=fac[i-1]*i%mod;
	ifac[n]=fp(fac[n],mod-2);
	dep(i,n-1,0) ifac[i]=ifac[i+1]*(i+1)%mod;
	rep(i,1,n){
		int t,mx=0;cin>>t;
		rep(j,1,t){
			int x;cin>>x;
			++mp[i][x];++mp2[x];
		}
		if(mx<=n/2) rt=mx;
		else for(auto [v,c]:mp[i]) if(v>=n/2) mp2[v]-=c;
	}
	ll ans=1;
	rep(i,1,n){
		for(auto [v,c]:mp[i]) if(v<n/2||v==n/2&&i==rt){
			ans=ans*C(mp2[v],c)%mod;
			mp2[v]-=c;
		}
	}
	cout<<ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) __solve();
    return 0;
}
```

---

## 作者：Wei_Han (赞：0)

代码过了脑子都还没转过来。

钦定树的重心作为根，按层来考虑，叶子节点很好找到，而叶子节点的父亲，一定拥有至少一个大小为 $1$ 的连通块，只要选一些叶子结点挂下来即可，假设这个点只有一个连通块，这个连通块大小为 $1$，那么他的方案数就数完了，将它和叶子看做一个大小为 $2$ 的连通块继续向上数。这样按照当前数的连通块大小来数数就好了，而且会发现连通块大小之间互不影响，所以可以分开计数，问题就转化为将 $k$ 个点划分为 $m$ 组，每组大小一定，不区分顺序的方案数，答案即 $\prod_{i=1}^m \binom{n-\sum_{j=1}^{i-1} a_j}{a_i} $，每次加和可以做到 $O(m)$，每一层合并答案时相乘即可，注意每一个点需要它的所有子树都被处理完之后才能向上数数，可以参考具体实现。

每个点不属于子树内的连通块是不处理的，因为我们以重心为根，最大的连通块一定不在子树内，前提是此点不为根，但是我们无法确定哪个点作为重心来数数，根不数最后一个连通块会对答案造成影响吗？因为根是作为最后一层只会有一个点，等价于乘了 $1$，所以对答案无影响。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
//typedef int ll;
// typedef long long ll;
typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=1e6+5,M=2e4+5,mod=998244353;
ll n,d[N],pre[N],ans=1,fac[N],inv[N];
inline ll qpow(ll a,ll b){return (!b?1:qpow(a*a%mod,b>>1)*((b&1ll)?a:1ll))%mod;}
inline ll C(ll n,ll m){return fac[n]*inv[n-m]%mod*inv[m]%mod;}
vector<ll> P[N],g[N];
signed main(){
	read(n);
	fac[0]=1;fo(1,i,n) fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);Fo(n-1,i,1) inv[i]=inv[i+1]*(i+1)%mod;inv[0]=1;
	fo(1,i,n)
	{
		read(d[i]);
		fo(0,j,d[i]-1){ll x;read(x);P[i].pb(x);}
		if(d[i]==1){pre[1]++;continue;}
		sort(P[i].begin(),P[i].end());
		ll sum=1,now=P[i][0],cnt=P[i][0];
		fo(1,j,d[i]-1)
		{
			if(P[i][j]!=P[i][j-1]) g[now+1].pb(sum),now=P[i][j],sum=0;
			if(j==d[i]-1) pre[cnt+1]++;//除了最后一个连通块，其他的连通块和算上这个点为cnt+1
			cnt+=P[i][j],sum++;
		}
	}
	fo(2,i,n)
	{
		ll now=pre[i-1];
		for(ll cnt:g[i]) ans*=C(now,cnt)%mod,ans%=mod,now-=cnt;
	}
	wr(ans%mod),pr;
	return 0;
}

``````

---

