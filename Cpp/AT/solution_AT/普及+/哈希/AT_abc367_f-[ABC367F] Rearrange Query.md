# [ABC367F] Rearrange Query

## 题目描述

给定两个长度为 $N$ 的正整数序列 $A=(A_1,A_2,\ldots,A_N)$ 和 $B=(B_1,B_2,\ldots,B_N)$。

你需要处理 $Q$ 个查询。对于第 $i$ 个查询，给定四个正整数 $l_i$, $r_i$, $L_i$, 和 $R_i$。你需要判断是否可以通过重新排列序列 $(A_{l_i},A_{l_i+1},\ldots,A_{r_i})$ 来使其与 $(B_{L_i},B_{L_i+1},\ldots,B_{R_i})$ 完全相同。如果可以做到，则输出 `Yes`；否则输出 `No`。

## 说明/提示

#### 制约条件

- $1 \leq N, Q \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq N$
- $1 \leq l_i \leq r_i \leq N$
- $1 \leq L_i \leq R_i \leq N$
- 所有输入均为整数。

#### 示例解释 1

- 对于第 1 个查询，$(1,2,3)$ 可以通过重排变为 $(2,3,1)$。因此输出 `Yes`。
- 对于第 2 个查询，无论怎样重排 $(1,2)$ 都无法变为 $(1,4,2)$。因此输出 `No`。
- 对于第 3 个查询，无论怎样重排 $(1,2,3,2)$ 都无法变为 $(3,1,4,2)$。因此输出 `No`。
- 对于第 4 个查询，$(1,2,3,2,4)$ 可以通过重排变为 $(2,3,1,4,2)$。因此输出 `Yes`。

## 样例 #1

### 输入

```
5 4
1 2 3 2 4
2 3 1 4 2
1 3 1 3
1 2 3 5
1 4 2 5
1 5 1 5```

### 输出

```
Yes
No
No
Yes```

## 样例 #2

### 输入

```
4 4
4 4 4 4
4 4 4 4
1 2 2 3
3 3 1 1
1 3 1 4
1 4 2 3```

### 输出

```
Yes
Yes
No
No```

# 题解

## 作者：nr0728 (赞：22)

考虑随机化。

我们对每个相同的数随机赋一个相同的权值。即使用一个映射 $mp$，且 $mp_{A_i}$ 和 $mp_{B_i}$ 均为随机数。这里可以用 `mt19937` 的 $[0,2^{32})$ 范围的随机数，如果要更高的正确率可以用 `mt19937_64` 的 $[0,2^{64})$ 范围的随机数。

然后对于第 $i$ 个询问，如果 $\sum\limits_{j=l_i}^{r_i} mp_{A_j}=\sum\limits_{j=L_i}^{R_i} mp_{B_j}$，那么我们认为两区间相等。这个可以前缀和 $\mathcal O(1)$ 解决。

这种方法正确率极高，直接就[过了](https://atcoder.jp/contests/abc367/submissions/56810883)。

---

## 作者：sevenki (赞：16)

首先，题目的条件等价于：对于每种元素，两个区间内该元素的数量相等。

然后我们可以直接开桶前缀和做，但是这样做的复杂度是不可接受的。

发现我们并不需要存储每个数究竟出现了几次这种具体的细节。如果对于每个数都存在一种权值，使得如果任意给出一个合法的结果 $x$（保证他是由区间内所有的数的权值相加的结果），只存在一种相加的方案，那我们就可以直接前缀和存储权值和，询问时直接判断两区间权值和是否相等即可。

容易发现，如果我们随机赋权，那么 $x$ 碰撞的概率非常低。那么我们可以考虑为每种数值分别赋随机权值，然后使用上述方法，配合自然溢出，即可通过此题。

注意为了防止被卡，进一步减少碰撞的概率，我们可以使用两套不同的权值。

---

## 作者：小粉兔 (赞：5)

在博客园食用更佳：<https://www.cnblogs.com/PinkRabbit/p/-/ABC367>。

## 题意简述（\*1540）

给定两个长度为 $n$ 的序列 $(a_1, \ldots, a_n)$ 和 $(b_1, \ldots, b_n)$。

回答 $q$ 次询问，每次给定 $l, r, L, R$（保证 $1 \le l \le r \le n$ 且 $1 \le L \le R \le n$），判断是否可以通过重排将 $a$ 的子串 $(a_l, \ldots, a_r)$ 变为 $b$ 的子串 $(b_L, \ldots, b_R)$。

数据范围：$n, q \le 2 \times 10^5$，$1 \le a_i, b_i \le n$。

## 题解

也就是判断子串 $a[l:r]$ 和 $b[L:R]$ 作为多重集是否相等。

一个熟知的判断多重集相等的办法是**散列**。即将多重集**映射为一个数**，以**数的相等**代**多重集的相等**，这个数称作**散列值**。为了确保正确性，需要在映射过程中引入随机性，并通过分析证明错误概率极小。

适用于本题的散列方式是令多重集 $S = \{ s_1, \ldots, s_k \}$ 映射为 $\bigl( \sum_{i = 1}^{k} g(s_i) \bigr) \bmod m$。其中 $g$ 为一个定义域为 $s$ 的取值范围，值域为 $[0, m)$ 的均匀随机函数，即所有 $g(s)$ 对于不同的 $s$ 来说都是独立的随机变量。

分析：
- 如果两多重集 $S, T$ 相同，则它们通过散列被映射到的数也相同。
- 如果两多重集 $S, T$ 不同，则它们的对称差 $D = S \mathbin{\Delta} T$ 非空。
  - 同时，作差得到 $S' = S \setminus T$ 和 $T' = T \setminus S$，此时有 $S'$ 与 $T'$ 无交且 $D = S' \cup T'$。
  - 此时 $S, T$ 的散列值相同当且仅当 $S', T'$ 的散列值相同。
  - 设 $S'$ 中有 $k$ 种数值 $(s_1, \ldots, s_k)$ 分别出现了 $(c_1, \ldots, c_k)$ 次；
  - 设 $T'$ 中有 $l$ 种数值 $(t_1, \ldots, t_l)$ 分别出现了 $(d_1, \ldots, d_l)$ 次；
  - 且 $k + l \ge 1$，即 $S' \cup T' = D$ 非空。
  - 则 $S', T'$ 的散列值相同等价于 $\sum_{i = 1}^{k} c_i \cdot g(s_i) + \sum_{i = 1}^{l} (-d_i) \cdot g(t_i) \equiv 0 \pmod{m}$。
  - 根据 $k + l \ge 1$，求和式中至少包含一项，设为 $C \cdot g(V)$，即该项的 $c_i$ 或 $-d_i$ 记作 $C$ 而 $s_i$ 或 $t_i$ 记作 $V$。
  - 有 $g(V)$ 是在 $[0, m)$ 中均匀取值的随机变量，则（根据熟知数论知识）该项**取任意特定值**的概率最大不会超过 $\gcd(C, m) / m$。
  - 故 $S, T$ 的散列值相同的概率不超过 $\gcd(C, m) / m$，其中 $C$ 可以在 $\lvert C \rvert \le n$ 且 $C \ne 0$ 的条件下取“最坏”的值。

其中 $C$ 最坏的值可以取到 $n$ 以内 $m$ 的最大因数。

**一种最优的选择是取 $\bm{m = p}$ 为素数**，从而只要 $n < p$，错误率就不超过 $1 / p$。

回看散列函数 $S \mapsto \bigl( \sum_{i = 1}^{k} g(s_i) \bigr) \bmod m$，当作用于序列 $a, b$ 的区间上时，可以用前缀和的手法处理：令 $\Sigma a_i = \bigl( \sum_{j = 1}^{i} g(a_j) \bigr) \bmod m$，则 $a[l:r]$ 作为多重集的散列值为 $(\Sigma a_r - \Sigma a_{l - 1}) \bmod m$。对序列 $b$ 的处理同理。

代码实现上，可以取 $m = 2^{64}$，使用 `unsigned long long` 进行计算，并使用 C++ 中的伪随机数生成器 `std::mt19937_64` 来生成 $g$ 的取值。
- 此时单次错误率不超过 $n / m$，故总错误率不超过 $q n / m$。取 $m = \Omega(\epsilon^{-1} q n)$ 即可达到 $\mathcal O(\epsilon)$ 的错误率要求。
- 计算可知，在 $m = 2^{64}$ 的设置下，单测试点错误率不超过 $3 \times 10^{-9}$。

时间复杂度为 $\mathcal O(n + q)$。

注：存在其他多种不同的散列方式。

## 参考 AC 代码

```cpp
#include <iostream>
#include <vector>
#include <random>
using std::cin, std::cout;

#define F(i, a, b) for(int i = a; i <= (b); ++i)

void Solve();
int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    Solve();
    return 0;
}

using ULL = unsigned long long;

void Solve() {
    int n, q;
    cin >> n >> q;
    std::vector<int> a(n + 1), b(n + 1);
    F(i, 1, n)
        cin >> a[i];
    F(i, 1, n)
        cin >> b[i];
    std::mt19937_64 rng(0x12345);
    std::vector<ULL> g(n + 1);
    F(i, 1, n)
        g[i] = rng();
    std::vector<ULL> sa(n + 1), sb(n + 1);
    sa[0] = sb[0] = 0;
    F(i, 1, n) {
        sa[i] = sa[i - 1] + g[a[i]];
        sb[i] = sb[i - 1] + g[b[i]];
    }
    F(q_, 1, q) {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        ULL v = sa[r] - sa[l - 1] - sb[R] + sb[L - 1];
        cout << (v ? "No" : "Yes") << '\n';
    }
}
```

---

## 作者：dyc2022 (赞：4)

注意到，我们需要维护一个**快速**的数据结构，使得我们可以快速地根据一个区间的值来得到这个区间的数字**组成**，而和顺序无关。

那么我们可以使用和哈希的技巧。

我们可以对于每一个 $a_i$，随机赋一个值，然后我们可以对这个随机值做一个前缀和。注意到，这个和是和顺序无关的。

那么我们对于两个序列都求完了哈希和，我们就可以比较读入的两个区间的哈希和是否相等，如果相等，基本可以认定是相同的区间，冲突的概率很低，用 `mt19937_64` 相当方便。

认为是 abc 最简单的一题 f，[AC Code.](https://atcoder.jp/contests/abc367/submissions/56801391)

---

## 作者：CQ_Bab (赞：3)

# 思路
看到这种题直接一眼 Hash 即可，我们 Hash 得越多正确性越高所以考虑 Hash 和，积，平方和，这里就是一个 Hash 模板没什么可讲性，如果不会建议去看一下代码或者 [Hash 例题](https://www.luogu.com.cn/problem/P3370)。
# 代码
还是很好写的。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define int long long
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T;
int n,m;
const int N=2e5+10,mod=998244353,mod1=1e9+7;
int a[N],b[N],cc1[N],cc[N],gg[N],gg1[N];
int qmi(int x,int y){
	int res=1;
	while(y) {
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}return res;
}
int ha(int x,int y) {
	return cc[y]*qmi(cc[x-1],mod-2)%mod;
}
int hh(int x,int y) {
	return cc1[y]*qmi(cc1[x-1],mod-2)%mod;
}
int ha1(int x,int y) {
	return (gg[y]-gg[x-1]+mod1)%mod1;
}
int hh1(int x,int y) {
	return (gg1[y]-gg1[x-1]+mod1)%mod1;
}
void solve() {
	in(n),in(m);
	cc[0]=cc1[0]=1;
	rep(i,1,n) {
		in(a[i]);
		cc[i]=cc[i-1]*a[i]%mod;
		gg[i]=(gg[i-1]+a[i]*a[i]%mod1)%mod1;
		a[i]+=a[i-1];
	}
	rep(i,1,n) {
		in(b[i]);
		cc1[i]=cc1[i-1]*b[i]%mod;
		gg1[i]=(gg1[i-1]+b[i]*b[i]%mod1)%mod1;
		b[i]+=b[i-1];
	}
	while(m--) {
		int l,r,x,y;
		cin>>l>>r>>x>>y;
		if(a[r]-a[l-1]!=b[y]-b[x-1]||ha(l,r)!=hh(x,y)||ha1(l,r)!=hh1(x,y)) puts("No");
		else {
			cout<<"Yes\n";
		}
	}
}
fire main() {
	T=1;
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：Register_int (赞：3)

场外选手。

容易发现对应的必要条件就是 $\sum a_i=\sum b_i$。我们充分发扬人类智慧，将 $1\sim n$ 的每个数 $i$ 随机映射到一个 $[0,2^{64})$ 内的整数 $v_i$，再直接判断是否有 $\sum v_{a_i}\equiv\sum v_{b_i}\pmod{2^{64}}$ 即可。实际正确率非常高，没啥办法卡。复杂度 $O(n+m)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAXN = 2e5 + 10;

mt19937_64 eng(time(0));

int n, m, a[MAXN], b[MAXN];

ull h[MAXN], v0a[MAXN], v0b[MAXN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) h[i] = eng();
	for (int i = 1; i <= n; i++) v0a[i] = h[a[i]], v0b[i] = h[b[i]];
	for (int i = 1; i <= n; i++) v0a[i] += v0a[i - 1];
	for (int i = 1; i <= n; i++) v0b[i] += v0b[i - 1];
	for (int al, ar, bl, br; m--;) {
		scanf("%d%d%d%d", &al, &ar, &bl, &br);
		ull sv0a = v0a[ar] - v0a[al - 1], sv0b = v0b[br] - v0b[bl - 1];
		puts(sv0a == sv0b ? "Yes" : "No");
	}
}
```

---

## 作者：Swirl (赞：2)

> 涉及知识点：哈希。

### 思路

将所有的 $a$ 和 $b$ 中所有元素的值都一一对应到一个很大的随机值，将对应后的数组记为 $c$ 和 $d$。

一次询问中，若 $r - l + 1 \ne R - L + 1$ 则显然不可能匹配。

剩下的每一次询问，若有：

$$
\sum ^ {r} _ {i = l}c_i=\sum ^ {R} _ {i = L} d_i
$$

则能满足条件。

虽然可能会出现错误，但出错率是 $10^{-9}$ 数量级的，可以忽略不计。

~~如果错了可以多交几遍，没准过了呢。~~

### 代码

```cpp
namespace zqh {
int a[200005], b[200005], n, q;
u_m<int, int> mp;
mt19937_64 rd(time(NULL));// 请尽量不要用 rand()，其不仅值域小还不均匀。

void init() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!mp.count(a[i])) {
            mp[a[i]] = rd() % (int)(1e18) + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!mp.count(b[i])) {
            mp[b[i]] = rd() % (int)(1e18) + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i] = mp[a[i]];
        b[i] = mp[b[i]];
        a[i] += a[i - 1];
        b[i] += b[i - 1];
    }
    while (q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        if (a[r] - a[l - 1] == b[y] - b[x - 1])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}

void main() {
    init();
    solve();
}
}  // namespace zqh
```

### 后记

`rand()` 函数返回的是一个介于 $0$ 到 $32767$ 之间的整数，显然在本题中值域不太够，为了保险还是用 `mt199337` 或 `mt19937_64`（如果你认为你足够欧皇可以试试）。

---

## 作者：zzhbpyy (赞：2)

### [传送门](https://www.luogu.com.cn/problem/AT_abc367_f)
## 思路
题目要求判断两个序列中的子段重排后是否相同，我们可以采用集合哈希的方法来判断两个子段包含的元素是否一致。对每个元素，我们可以随意的搞出一个映射函数，然后对每个序列求出其前缀积。查询区间 $[l,r]$ 时，我们用 $r$ 处的前缀积乘上 $l-1$ 处前缀积的逆元，判断两个哈希值是否相等即可。

## 代码
```c++
#include<bits/stdc++.h>
#define int long long//要开long long
#define mod 1000000007
using namespace std;
int n,q,a[200005],b[200005],ha[200005],hb[200005];
unsigned shift(unsigned v){//乱搞出一个映射函数
	v^=20090803;
	int y=v<<17;
	v=(v>>7)^(v<<6);v+=13;
	return v^1145141;
}
int po(int a,int b){
	if(b==1)return a;
	if(b==0)return 1;
	int d=po(a,b>>1);
	return d*d%mod*po(a,b&1)%mod;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>q;ha[0]=hb[0]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ha[i]=ha[i-1]*shift(a[i])%mod;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		hb[i]=hb[i-1]*shift(b[i])%mod;
	}int l,r,L,R;
	while(q--){
		cin>>l>>r>>L>>R;
		if(ha[r]*po(ha[l-1],mod-2)%mod==hb[R]*po(hb[L-1],mod-2)%mod)cout<<"Yes\n";
		else cout<<"No\n";
	}
}
```

---

## 作者：Meickol (赞：2)

比较简单的 F 题。

如果序列 $(A _ {l},A _ {l+1},\ldots,A _ {r})$ 可通过重新排列子序列与序列 $(B _ {L},B _ {L+1},\ldots,B _ {R}) $ 完全匹配，说明序列 $(A _ {l},A _ {l+1},\ldots,A _ {r})$ 和序列 $(B _ {L},B _ {L+1},\ldots,B _ {R}) $ 两者的可重集相同。

于是转化成了一个集合哈希问题。

两个可重集相同，可推出两个可重集中元素总和也相同；但是，两个可重集元素总和相同，不能推出两个可重集相同。所以我们需要先进行哈希处理一下，让每个数都映射成一个较复杂的值，以降低冲突概率，这样当两个可重集元素总和相同时就能认为两个可重集相同了。

因为 $1\leq A_i,B_i\leq N$，我们可以开一个 $h$ 数组作为辅助，先预处理 $h[i]$ 存储值为 $i$ 对应的哈希值，接着让 $A_i$ 的值取为 $h[A_i]$，让 $B_i$ 的值取为 $h[B_i]$。

然后再用两个前缀和数组分别预处理保存 $A$ 序列的前缀和以及 $B$ 序列的前缀和。

最后给定 $l,r,L,R$，要判定序列 $(A _ {l},A _ {l+1},\ldots,A _ {r})$ 的可重集是否与序列 $(B _ {L},B _ {L+1},\ldots,B _ {R}) $ 的可重集相同，只需要判定 `prefix1[r]-prefix[l-1]==prefix2[R]-prefix2[L-1]` 是否成立即可。

使用 `unsigned long long` 处理了自然溢出。

代码如下：

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef unsigned long long ULL;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int N=2e5+5;
int n,q;
ULL h[N],a[N],b[N],prefix1[N],prefix2[N];
void solve(){
	cin>>n>>q;
	rep(i,1,n) h[i]=rnd();
	rep(i,1,n){
		int x;
		cin>>x;
		a[i]=h[x];
		prefix1[i]=prefix1[i-1]+a[i];
	}
	rep(i,1,n){
		int x;
		cin>>x;
		b[i]=h[x];
		prefix2[i]=prefix2[i-1]+b[i];
	}
	while(q--){
		int l,r,L,R;
		cin>>l>>r>>L>>R;
		if(prefix1[r]-prefix1[l-1]==prefix2[R]-prefix2[L-1]) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}
```

---

## 作者：__O_v_O__ (赞：1)

这题我一看到题面，就想到了哈希。可是怎么哈希呢？

考虑一种神奇的做法：给每个数赋一个权值，如果两个区间的数的权值和相等，则输出 `Yes`，否则输出 `No`。

权值又赋成什么呢？有两种做法。

1. 用随机权值。根据官方题解的说法，这样成功的可能性很大，实测确实可通过。不过我认为这种方法很玄学。

2. 使用这个数的次方。这样也可过，看起来没有那么玄学。

**AC code:**

做法1：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=2305843009213693951;
int n,q,a[200001],b[200001];
int hx[200001],s1[200001],s2[200001];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>q,srand(time(0));
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=200000;i++)hx[i]=rand();\\随机数
	for(int i=1;i<=n;i++)s1[i]=(s1[i-1]+hx[a[i]])%mo;
	for(int i=1;i<=n;i++)s2[i]=(s2[i-1]+hx[b[i]])%mo;
	for(int i=1;i<=q;i++){
		int l,r,L,R;
		cin>>l>>r>>L>>R;
		if((s1[r]-s1[l-1])%mo==(s2[R]-s2[L-1])%mo)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

做法2：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=1e9+7;
int n,q,a[200001],b[200001];
int hx[200001],s1[200001],s2[200001];
int po(int a,int b){
	int an=1;
	while(b){
		if(b&1)an=an*a%mo;
		a=a*a%mo,b>>=1;
	}
	return an;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>q,srand(time(0));
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=200000;i++)hx[i]=po(i,114514);\\次方
	for(int i=1;i<=n;i++)s1[i]=(s1[i-1]+hx[a[i]])%mo;
	for(int i=1;i<=n;i++)s2[i]=(s2[i-1]+hx[b[i]])%mo;
	for(int i=1;i<=q;i++){
		int l,r,L,R;
		cin>>l>>r>>L>>R;
		if(((s1[r]-s1[l-1])%mo+mo)%mo==((s2[R]-s2[L-1])%mo+mo)%mo)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：mayike (赞：1)

~~为什么我会写一道板题的题解？~~

赛时只因这题吃了一发罚时。

[[ABC367F] Rearrange Query](https://www.luogu.com.cn/problem/AT_abc367_f)

## 思路

一眼哈希，为了不被卡，我采用了随机数，异或，前缀和。由于这题过于简单，具体见细节。

奇怪的是，我赛时代码没判长度过了。欢迎 hack。

赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rd(time(0));
const int N=2e5+5;
int n,Q,a[N],b[N];
long long s1[N],s2[N],t1[N],t2[N];
unsigned long long c[N],c1[N],c2[N];
__int128 d1[N],d2[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++)c[i]=rd();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		t1[i]=t1[i-1]+a[i];
		s1[i]=s1[i-1]+1ll*a[i]*a[i];
		d1[i]=d1[i-1]+1ll*a[i]*a[i]*a[i];
		c1[i]=c1[i-1]^c[a[i]];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		t2[i]=t2[i-1]+b[i];
		s2[i]=s2[i-1]+1ll*b[i]*b[i];
		c2[i]=c2[i-1]^c[b[i]];
		d2[i]=d2[i-1]+1ll*b[i]*b[i]*b[i];
	}
	while(Q--){
		int l,r,L,R;
		cin>>l>>r>>L>>R;
		int w1=s1[r]-s1[l-1],w2=c1[r]^c1[l-1],w3=t1[r]-t1[l-1],p1=s2[R]-s2[L-1],p2=c2[R]^c2[L-1],p3=t2[R]-t2[L-1];
		__int128 w4=d1[r]-d1[l-1],p4=d2[R]-d2[L-1];
		if(w1==p1&&w2==p2&&w3==p3&&w4==p4)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

判了长度的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rd(time(0));
const int N=2e5+5;
int n,Q,a[N],b[N];
long long s1[N],s2[N],t1[N],t2[N];
unsigned long long c[N],c1[N],c2[N];
__int128 d1[N],d2[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++)c[i]=rd();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		t1[i]=t1[i-1]+a[i];
		s1[i]=s1[i-1]+1ll*a[i]*a[i];
		d1[i]=d1[i-1]+1ll*a[i]*a[i]*a[i];
		c1[i]=c1[i-1]^c[a[i]];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		t2[i]=t2[i-1]+b[i];
		s2[i]=s2[i-1]+1ll*b[i]*b[i];
		c2[i]=c2[i-1]^c[b[i]];
		d2[i]=d2[i-1]+1ll*b[i]*b[i]*b[i];
	}
	while(Q--){
		int l,r,L,R;
		cin>>l>>r>>L>>R;
		int w1=s1[r]-s1[l-1],w2=c1[r]^c1[l-1],w3=t1[r]-t1[l-1],p1=s2[R]-s2[L-1],p2=c2[R]^c2[L-1],p3=t2[R]-t2[L-1];
		__int128 w4=d1[r]-d1[l-1],p4=d2[R]-d2[L-1];
		if(r-l==R-L&&w1==p1&&w2==p2&&w3==p3&&w4==p4)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：SpringFullGarden (赞：1)

## 题意

给定长度为 $n$ 的正整数序列 $a_i$ 和 $b_i$。

每次查询 $l,r,L,R$。求 $a[l,r]$ 和 $b[l,r]$ 中每个数字出现次数是否相同。

## 思路

考虑哈希，随机选取每个数所代表的值，看两个区间的和是否相同。

可以用前缀和维护，但是赛场上的我不知不觉就写上了线段树。

代码中写的是三哈希，实际上单哈希就能过。

## 代码

```
#define mo1 998244343434343434
#define mo2 100000000000000007
#define mo3 100000000000000009

struct node {
	ll l, r, asum[4], bsum[4];
} tr[800005], zero;
ll a[200005], b[200005], seed[200005][4];

ll rnd() {
	return (rand() << 30) | (rand() << 16) | rand();
}
void bd(ll x, ll l, ll r) {
	tr[x].l = l, tr[x].r = r;
	if(l == r) {
		tr[x].asum[1] = a[l] * seed[a[l]][1] % mo1;
		tr[x].asum[2] = a[l] * seed[a[l]][2] % mo2;
		tr[x].asum[3] = a[l] * seed[a[l]][3] % mo3;
		tr[x].bsum[1] = b[l] * seed[b[l]][1] % mo1;
		tr[x].bsum[2] = b[l] * seed[b[l]][2] % mo2;
		tr[x].bsum[3] = b[l] * seed[b[l]][3] % mo3;
		return;
	}
	ll mid = (l + r) >> 1;
	bd(x << 1, l, mid), bd(x << 1 | 1, mid + 1, r);
	tr[x].asum[1] = (tr[x << 1].asum[1] + tr[x << 1 | 1].asum[1]) % mo1;
	tr[x].asum[2] = (tr[x << 1].asum[2] + tr[x << 1 | 1].asum[2]) % mo2;
	tr[x].asum[3] = (tr[x << 1].asum[3] + tr[x << 1 | 1].asum[3]) % mo3;
	tr[x].bsum[1] = (tr[x << 1].bsum[1] + tr[x << 1 | 1].bsum[1]) % mo1;
	tr[x].bsum[2] = (tr[x << 1].bsum[2] + tr[x << 1 | 1].bsum[2]) % mo2;
	tr[x].bsum[3] = (tr[x << 1].bsum[3] + tr[x << 1 | 1].bsum[3]) % mo3;
}
node fd(ll x, ll l, ll r) {
	if(tr[x].l >= l && tr[x].r <= r) return tr[x];
	if(tr[x].l > r || tr[x].r < l) return zero;
	node ans, lson = fd(x << 1, l, r), rson = fd(x << 1 | 1, l, r);
	ans.asum[1] = (lson.asum[1] + rson.asum[1]) % mo1;
	ans.asum[2] = (lson.asum[2] + rson.asum[2]) % mo2;
	ans.asum[3] = (lson.asum[3] + rson.asum[3]) % mo3;
	ans.bsum[1] = (lson.bsum[1] + rson.bsum[1]) % mo1;
	ans.bsum[2] = (lson.bsum[2] + rson.bsum[2]) % mo2;
	ans.bsum[3] = (lson.bsum[3] + rson.bsum[3]) % mo3;
	return ans;
}
signed main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	srand(time(0));
    ll n = rd(), Q = rd();
    for(ll i = 1; i <= n; i++) a[i] = rd();
    for(ll i = 1; i <= n; i++) b[i] = rd();
    for(ll i = 1; i <= n; i++)
    	for(ll j = 1; j <= 3; j++)
    		seed[i][j] = rnd() % 99824435353535353;
	bd(1, 1, n);
	while(Q--) {
		ll l = rd(), r = rd(), L = rd(), R = rd();
		node A = fd(1, l, r), B = fd(1, L, R);
		if(A.asum[1] == B.bsum[1] && A.asum[2] == B.bsum[2] && A.asum[3] == B.bsum[3])
			puts("Yes");
		else puts("No");
	}
	return 0;
}
/*

*/

```

---

## 作者：SunSkydp (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/sunskydp/p/18365614/abc367f_solution)
## 简要题意
给定两个长度为 $N$ 的序列 $A$ 和 $B$。  
有 $Q$ 个查询，每个查询给定 $l,r,L,R$，其中 $l \leq r, L \leq R$，要求判断 $A$ 的第 $l$ 项到第 $r$ 项构成的集合与 $B$ 的第 $L$ 项到第 $R$ 项构成的集合是否相等。

## 题解
显然两个相等的集合所有元素之和相等，但是如果直接判断和肯定是不行的，有反例 `1 2 2 3` 和 `2 2 2 2`，于是我们考虑类似哈希的做法，把每个数映射到随机的值，然后判断映射值的和是否相等。  

这里我们可以用 map 维护映射的随机值，读入时即判断该数是否映射，若没有则赋一个随机值加到 map 中，这里随机值对 $1000000$ 取模。然后预处理映射的随机值的前缀和，询问时 $\mathcal{O(1)}$ 减一下判断即可。

代码见下
```cpp
#include <bits/stdc++.h>
#define _for(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 200005;
int n, q, a[N], b[N];
int s[N], s2[N];
map<int, int> mp;
signed main() {
    srand(time(0));
    cin >> n >> q;
    _for(i, 1, n) {
        cin >> a[i];
        if(mp.find(a[i]) == mp.end()) mp[a[i]] = rand() % 1000000;
        s[i] = s[i - 1] + mp[a[i]];
    }
    _for(i, 1, n) {
        cin >> b[i];
        if(mp.find(b[i]) == mp.end()) mp[b[i]] = rand() % 1000000;
        s2[i] = s2[i - 1] + mp[b[i]];
    }
    while(q--) {
        int l, r, L, R; cin >> l >> r >> L >> R;
        if(s[r] - s[l - 1] == s2[R] - s2[L - 1]) puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

## 作者：appear_hope (赞：1)

这题不要被重新排列序列迷惑了，其实显然是判断区间可重集是否相同，给每一个数随机赋权，算出前缀的权值总和，每次查询区间可重集权值总和用两个前缀相减得到，从而根据权值去判断两个可重集是否相等。

代码如下：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const long long mod = 1e18 + 3;

mt19937_64 rnd(time(0));

int n, q, a[N], b[N];
long long s[N], sum[N], w[N];

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) cin >> b[i];
  for(int i = 1; i <= n; i++) w[i] = rnd() % mod;
  for(int i = 1; i <= n; i++){
    s[i] = (s[i - 1] + w[a[i]]) % mod;
    sum[i] = (sum[i - 1] + w[b[i]]) % mod;
  }
  for(int i = 1, l, r, L, R; i <= q; i++){
    cin >> l >> r >> L >> R;
    if(r - l != R - L){
      cout << "No\n";
      continue;
    }
    long long na = (s[r] - s[l - 1] + mod) % mod, nb = (sum[R] - sum[L - 1] + mod) % mod;
    cout << (na != nb ? "No\n" : "Yes\n");
  }
  return 0;
}

```

---

## 作者：liruixiong0101 (赞：1)

# F - Rearrange Query
## 题意：
给定两个长度为 $n$ 的数组 $a,b$，一共有 $q$ 次询问，每次询问由四个数 $l_i,r_i,L_i,R_i$，如果序列 $(a_{l_i},a_{l_i+1},\cdots,a_{r_i})$ 和 $(b_{L_i},b_{L_i+1},\cdots,b_{R_i})$ 经过重排，可以使得每一位都相同，那么输出 `Yes`，否则输出 `No`。

## 思路：
以一下有两种思路，第一种是我自己在场上想到的思路，第二种是场下想到的思路。

### 主席树+哈希：
考虑将题意转化，转化为两个数组在区间内出现的数的个数相同，这可以用主席树解决，但是用普通的主席树需要枚举每一个数，算出其出现次数，然后一一比较，这样时间复杂度比暴力还高，考虑优化。我们希望的是整体比较，而不是对于每一个数进行比较，所以我们可以用到一个类似于哈希的操作，将每一个数赋予一个权值，当这个数出现，就将他所在桶（主席树）加上这个权值，然后直接判断这两个区间的总权值是否相同即可。每一个数的权值该赋多少好呢，那就随机数吧。

### 直接哈希：
我们发现我们想要的是区间整体比较，而不是每一个数进行比较，主席树计算区间内每一个数的出现次数时间复杂度很优，但是对于整体比较，复杂度就比直接哈希要更劣。考虑到题目中数组可以重排，我们选择用由交换律的哈希，那么我们对于每出现一个数就将其前缀的哈希值加上这个数的权值（也是随机数），那么在最后询问的时候可以直接用两个端点的哈希值一减比较是否相等即可。

## 代码：
- 主席树+哈希：<https://atcoder.jp/contests/abc367/submissions/56851481>
- 直接哈希：<https://atcoder.jp/contests/abc367/submissions/56851526>

---

## 作者：FreedomKing (赞：1)

哈希前缀和模板题。

### 思路

对于这种裸的区间元素集判等问题可以非常自然的想到哈希前缀和。

显然普通的维护前缀和是无法通过的，考虑给每个元素乘上一个权值进行哈希，这样再维护前缀和得到正确答案的概率就会高很多，如果模数被卡掉了可以多尝试几种模数或者自然溢出。

关于模数问题，常用质数和查大质数表找到的 $998244353,10^9+7,10^{18}+9,10^{16}+1743$ 都被卡了，但是自然溢出可过。

### AC Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
#define int unsigned long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=3e5+5,mN=1e2+5,mod=10000000000001743;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	inline int abss(int x){return (x>=0?x:-x);}
}
const int base=13331;
int p[N],asum[N],bsum[N];
bool M2;signed main(){
	int n=qr,T=qr;
	p[0]=1;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*base;
	for(int i=1;i<=n;i++) asum[i]=asum[i-1]+p[qr];
	for(int i=1;i<=n;i++) bsum[i]=bsum[i-1]+p[qr];
	while(T--){
		int l=qr,r=qr,L=qr,R=qr;
		puts(((asum[r]-asum[l-1])==(bsum[R]-bsum[L-1])&&r-l==R-L)?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：stripe_python (赞：1)

F 最乱搞的一集。

直接去做比较困难，考虑去比较两个区间的特征值。形式化地，我们需要找到一种满足交换律的运算，使两个区间中的数依次运算后相同则认为一样。

对于这一运算，本蒟蒻采用加法和异或双重哈希。

这很容易被卡，所以我们开一个哈希表，把每个输入映射到随机值，再使用双哈希即可。复杂度 $O(n)$。

随机数据下，对 $2^{64}$ 取模（自然溢出法）冲突的概率是极小的，不需要取模。

```cpp
unsigned long long n, q, a[N], b[N], mp[N], l1, r1, l2, r2, pa[N], pb[N], xa[N], xb[N];
mt19937 ran(random_device{}());

void _main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; 
		if (!mp[a[i]]) mp[a[i]] = ran();
		a[i] = mp[a[i]];
		pa[i] = pa[i - 1] + a[i];
		xa[i] = xa[i - 1] ^ a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		if (!mp[b[i]]) mp[b[i]] = ran();
		b[i] = mp[b[i]];
		pb[i] = pb[i - 1] + b[i];
		xb[i] = xb[i - 1] ^ b[i];
	}
	while (q--) {
		cin >> l1 >> r1 >> l2 >> r2;
		if (r2 - l2 != r1 - l1) cout << "No\n";
		else {
			if (pa[r1] - pa[l1 - 1] == pb[r2] - pb[l2 - 1] &&
				(xa[r1] ^ xa[l1 - 1]) == (xb[r2] ^ xb[l2 - 1])) {
				cout << "Yes\n";
			} else cout << "No\n";
		}
	}
} 
```

需要注意的是，不能只使用异或哈希，因为异或会把相同的数字抵消，这样 `2 2` 和 `3 3` 就能 hack 掉。

---

## 作者：Redshift_Shine (赞：1)

## 6. Rearrange Query

看到区间排序后相同，果断转化为区间所代表的多重集相等，于是哈希。

这里，仍然要**强烈推荐**一种非常好写的随机算法。

定义一个梅森旋转器，用 `random_device` 初始化，在每个值上调用一次梅森旋转。这样既好写又不用担心固定 base 被卡。

时间复杂度 $O(n+q)$。

```c++
#include <iostream>
#include <random>
using namespace std;
const int N = 2e5 + 10;
int n, q, a[N], b[N];
using ull = unsigned long long;
random_device rd;
mt19937 mt(rd());
ull hs[N], hspa[N], hspb[N];
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        hs[i] = mt();
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        hspa[i] = hspa[i - 1] + hs[a[i]];
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", b + i);
        hspb[i] = hspb[i - 1] + hs[b[i]];
    }
    for (int i = 1, ta, tb, tc, td; i <= q; i++)
    {
        scanf("%d%d%d%d", &ta, &tb, &tc, &td);
        if (tb - ta + 1 != td - tc + 1)
        {
            puts("No");
            continue;
        }
        if (hspa[tb] - hspa[ta - 1] != hspb[td] - hspb[tc - 1])
        {
            puts("No");
            continue;
        }
        puts("Yes");
    }
}
```

---

## 作者：Fire_flame (赞：1)

有人赛时降智。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc367_f)

## $\mathtt{Solution}$

首先肯定可以想到哈希，但是我突然忘记了哈希可差分（

于是就写了莫队，其实本质相同，记录 $num_i$ 为每一个数 $i$ 出现了多少次，然后把这个数组哈希即可。

十分钟就写完了，赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 1e6 + 5, E = 1907, E2 = 1009;
const int MOD1 = 911451407, MOD2 = 1e9 + 7;
int n, m, k, res, res2, a[MAXN], b[MAXN], pw[MAXN], pw2[MAXN], ans[MAXN], ans2[MAXN], ans3[MAXN], ans4[MAXN];
int get_block(int x){
	return (x - 1) / k + 1;
}
struct query{
	int l, r, id;
	bool operator < (const query &zzz)const{
		if(get_block(l) != get_block(zzz.l))return l < zzz.l;
		return r > zzz.r;
	}
}q[MAXN], q2[MAXN];
void add(int x){res += pw[x];res %= MOD1;res2 += pw2[x];res2 %= MOD2;}
void del(int x){res -= pw[x];res = (res + MOD1) % MOD1;res2 -= pw2[x];res2 = (res2 + MOD2) % MOD2;}
signed main(){
	n = read(), m = read(), k = sqrt(n);
	for(int i = 1;i <= n;i ++)a[i] = read();
	for(int i = 1;i <= n;i ++)b[i] = read();
	pw[0] = pw2[0] = 1;
	for(int i = 1;i <= n;i ++)pw[i] = pw[i - 1] * E % MOD1, pw2[i] = pw2[i - 1] * E2 % MOD2;
	for(int i = 1;i <= m;i ++){
		q[i] = {read(), read(), i};
		q2[i] = {read(), read(), i};
	}
	sort(q + 1, q + m + 1);
	sort(q2 + 1, q2 + m + 1);
	int l = 1, r = 0;
	for(int i = 1;i <= m;i ++){
		while(l > q[i].l)add(a[-- l]);
		while(l < q[i].l)del(a[l ++]);
		while(r > q[i].r)del(a[r --]);
		while(r < q[i].r)add(a[++ r]);
		ans[q[i].id] = res;
		ans3[q[i].id] = res2;
	}
	l = 1, r = 0, res = res2 = 0;
	for(int i = 1;i <= m;i ++){
		while(l > q2[i].l)add(b[-- l]);
		while(l < q2[i].l)del(b[l ++]);
		while(r > q2[i].r)del(b[r --]);
		while(r < q2[i].r)add(b[++ r]);
		ans2[q2[i].id] = res;
		ans4[q2[i].id] = res2;
	}
	for(int i = 1;i <= m;i ++){
		if(ans[i] == ans2[i] && ans3[i] == ans4[i])puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：yanqijin (赞：1)

# 题目大意
给你两个长度为 $n$ 的序列，一个为 $A$，一个为 $B$。

现在给你 $q$ 个询问，对于第 $i$ 次询问给你四个数：$l_i,r_i,L_i,R_i$，然后问你序列 $A$ 的 $l_i$ 到 $r_i$ 的部分能否通过重新排列得到序列 $B$ 的 $L_i$ 到 $R_i$ 的部分。
# 思路
对于一次询问，本质上就是在求序列 $A$ 的 $l_i$ 到 $r_i$ 的部分每个数字出现的次数是否等于序列 $B$ 的 $L_i$ 到 $R_i$ 的部分。

考虑随机化和前缀和。我们给所有数字随机一个权值，第 $i$ 个数字的权值记为 $val_i$，然后求一下序列 $A$ 的前缀和以及序列 $B$ 的前缀和，再对比一下即可。
# code

```cpp
#include<bits/stdc++.h>
#define mod 993797405063//模数要特殊一点
using namespace std;
__int128 n,q,a[200005],val[200005],b[200005],sum[200005],sums[200005];
void read(__int128 &x) {
	x=0;
	int w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=w;
}
void write(__int128 x) {
	if(x<0) {
		putchar('-');
		x=-x;
	}
	int sta[100],top=0;
	do {
		sta[top++]=x%10;
		x/=10;
	} while(x);
	while(top--) putchar(sta[top]+48);
	putchar(' ');
}
int main() {
	mt19937 myrand(time(0));
	read(n);
	read(q);
	val[0]=14;
	for(int i=1; i<=n; i++) val[i]=val[i-1]*myrand()%mod;//随机化
	for(int i=1; i<=n; i++) read(a[i]),sum[i]=(sum[i-1]+val[a[i]])%mod;
	for(int i=1; i<=n; i++) read(b[i]),sums[i]=(sums[i-1]+val[b[i]])%mod;
	__int128 l,r,l1,r1;
	while(q--) {
		read(l);read(r);read(l1);read(r1);
		if((sum[r]+mod-sum[l-1])%mod==(sums[r1]+mod-sums[l1-1])%mod) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：1)

我这里有一张意义不明的图片。

为什么会出现在这一篇题解我也不知道。

![](https://cdn.luogu.com.cn/upload/image_hosting/y27yfulg.png)

## 解题思路

一个很典型的 trick。

考虑两段重排之后相等的必要条件：

- 两段长度相等。
- 两段的和相等。

---

为什么是必要条件而不是充分条件？

考虑以下反例：

$$A=3,2$$

$$B=1,4$$

即便两段和相等，长度相等，还是不能重排使得两段相等。

---

前者简单判断即可，而后者可以使用一个 trick 来避免被出题人构造数据卡掉：

考虑对于两个数列中的每一个数随机映射到另一个数，判断时同时判断映射前后的两段和是否相等。

如果能重排使得两段相等，那么映射后重排也一定能使得两段相等。因此可以建立多个映射，只要有一个映射使得两段不相等，那么这两段就一定不能重排相等。

相类似的 trick 还有 [CF1746F Kazaee](https://www.luogu.com.cn/problem/CF1746F) 这一道题，感兴趣的可以去看看。

使用前缀和维护区间和，假定你构建的映射个数为 $\omega$，时间复杂度即为 $O((N+Q)\omega)$。

我的 $\omega$ 取的是 $60$。事实上由于根本卡不了而且数据极其水（不构建映射都能过 $\frac 3 4$ 的点）$\omega$ 取 $5$ 左右就能通过本题。

---

## 作者：Heldivis (赞：0)

## [ABC367F] Rearrange Query

非常智慧的一个题。

考虑对于两段区间相等，显然一个必要条件是两段区间和相等，可以使用前缀和。但是这样显然不充分，有一组反例：$\{1, 3\}$ 和 $\{2, 2\}$。这是因为 $1+3=2+2$，只要我们构造一种方法，使得最少出现这种情况。

考虑把每个 $1\sim N$ 的整数映射到一个大整数上，这样就减少一些冲突情况。这样每次仍然进行区间和的判断就能有筛掉一部分不合法的询问。

为了保证正确性，每次改变映射方式，重复多次，只有每次有合法才是最终合法的询问。时间复杂度 $O(TN)$，$T$ 是重复次数，$T=500$ 可以基本完全避免冲突，实际上 $T=500$ 只耗时不到 $1$ 秒，为了保证正确性可以开到 $T=1000$。

代码：

```cpp
mt19937 rd(114514);

const int N = 3E5 + 100;

int n, q, l[N], r[N], L[N], R[N], a[N], b[N];
bool res[N];
unsigned ha[N], hb[N], t[N];

signed main() {
  n = read(), q = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  for (int i = 1; i <= n; i++) b[i] = read();
  for (int i = 1; i <= q; ++i)
    l[i] = read(), r[i] = read(), L[i] = read(), R[i] = read(), res[i] = 1;
  for (int T = 1; T <= 500; ++T) {
    for (int i = 1; i <= n; ++i) t[i] = rd();
    for (int i = 1; i <= n; ++i) ha[i] = (ha[i - 1] + t[a[i]]);
    for (int i = 1; i <= n; ++i) hb[i] = (hb[i - 1] + t[b[i]]);
    for (int i = 1; i <= q; ++i)
      res[i] = res && (ha[r[i]] - ha[l[i] - 1] == hb[R[i]] - hb[L[i] - 1]);
  }
  for (int i = 1; i <= q; ++i) puts(res[i] ? "Yes" : "No");
  return 0;
}
```

---

## 作者：Gapple (赞：0)

我们很容易想到要维护每种元素（$i$）在 $A$ 的前 $j$ 个中的个数 $a_{i, j}$ 与在 $B$ 的前 $j$ 个中的个数 $b_{i, j}$。

于是当 $a_{i, r} - a_{i, l - 1} = b_{i, R} - b_{i, L - 1}$ 对于所有的 $1 \le i \le n$ 都满足时，输出 `Yes`。

但是这样是 $O(QN)$ 的，会超时，所以我们用哈希的思想优化。

设（$B$ 为常数，$j$ 为每种元素，$i$ 为下标）：

$$
\begin{aligned}
  h_A(i) &\equiv \sum_{j = 1}^N a_{j, i} \cdot B^{j - 1} \pmod {2^{64} - 1} \\
  h_B(i) &\equiv \sum_{j = 1}^N b_{j, i} \cdot B^{j - 1} \pmod {2^{64} - 1}
\end{aligned}
$$

可以发现，$h_A(i) = h_A(i - 1) + B^{A_i - 1}, h_B(i) = h_B(i - 1) + B^{B_i - 1}$，故可以 $O(N)$ 预处理。

于是当 $h_A(r) - h_A(l - 1) = h_B(R) - h_B(L - 1)$ 时，输出 `Yes`，否则输出 `No`。

```cpp
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using i64 = long long;

constexpr size_t BASE = 233;

size_t power(size_t base, size_t expo)
{
    size_t res = 1;

    for (; expo > 0; expo >>= 1, base = base * base) {
        if (expo & 1)
            res *= base;
    }

    return res;
}

size_t gen_hash(size_t lst, int val)
{
    return lst + power(BASE, val - 1);
}

int main()
{
    int n, q;
    vector<size_t> cnt_a { 0 }, cnt_b { 0 };

    cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt_a.emplace_back(gen_hash(cnt_a.back(), x));
    }

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt_b.emplace_back(gen_hash(cnt_b.back(), x));
    }

    while (q-- > 0) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (r1 - l1 == r2 - l2 && cnt_a[r1] - cnt_a[l1 - 1] == cnt_b[r2] - cnt_b[l2 - 1] ? "Yes\n" : "No\n");
    }

    return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[[ABC367F] Rearrange Query](https://www.luogu.com.cn/problem/AT_abc367_f)

随机化。

对于 $1\sim n$ 中的每个数分配一个随机数，对原数组的每个数，将它们的随机数做一个前缀和。

如果 $a$ 数组 $[l,r]$ 中的和与 $b$ 数组 $[L,R]$ 中的和相同，那么这两个区间**大概率**数字相同。如果两个和不相同，那么这两个区间中的数字**一定**不相同。

为了保证判断的更加准确，随机 $500$ 次即可。这时复杂度为 $O((n+q)\times 500)$，可以通过。

用 `mt19937 rnd (1919810)` 进行随机化即可。

```cpp
for (int i = 1; i <= q; i++)
	cin >> l[i] >> r[i] >> L[i] >> R[i], ans[i] = 1;
int ti = 501;
while (ti--) {
	for (int i = 1; i <= n; i++) val[i] = rnd ();
	for (int i = 1; i <= n; i++) cnt1[i] = cnt1[i - 1] + val[a[i]];
	for (int i = 1; i <= n; i++) cnt2[i] = cnt2[i - 1] + val[b[i]];
	for (int i = 1; i <= q; i++) {
		if (cnt1[r[i]] - cnt1[l[i] - 1] != cnt2[R[i]] - cnt2[L[i] - 1])
			ans[i] = 0;
	}
}
for (int i = 1; i <= q; i++)
	cout << (ans[i] ? "Yes\n" : "No\n");
```

---

## 作者：incra (赞：0)

### Sol
观察到两个区间等价当且仅当我们可以通过一种哈希方法，使得顺序不影响这个哈希值的大小。

不难想到求和，异或还有乘法军不受这个影响。

所以直接每个区间求异或，求和，求积，如果都相等，那么这两个区间不同的概率就很低了。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
#define endl '\n'
LL _time = chrono :: steady_clock :: now ().time_since_epoch ().count ();
mt19937 _rd (_time);
LL rd (LL l,LL r) {
	return _rd () % (r - l + 1) + l;
}
const int N = 200010,MOD[3] = {(int)1e9 + 7,(int)1e9 + 9,998244353};
int n,q;
int a[N],b[N];
LL sa[N],sb[N];
LL suma[N],sumb[N];
LL proa[N][3],prob[N][3];
LL weight[N];
int main () {
	cin >> n >> q;
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = 1;i <= n;i++) cin >> b[i];
	for (int i = 1;i <= n;i++) weight[i] = rd (1,1e18);
	for (int i = 1;i <= n;i++) sa[i] = sa[i - 1] ^ weight[a[i]],sb[i] = sb[i - 1] ^ weight[b[i]];
	for (int i = 1;i <= n;i++) suma[i] = suma[i - 1] + a[i],sumb[i] = sumb[i - 1] + b[i];
	for (int j = 0;j < 3;j++) {
		proa[0][j] = prob[0][j] = 1;
		for (int i = 1;i <= n;i++) proa[i][j] = proa[i - 1][j] * a[i] % MOD[j],prob[i][j] = prob[i - 1][j] * b[i] % MOD[j];
	}
	while (q--) {
		int l1,r1,l2,r2;
		cin >> l1 >> r1 >> l2 >> r2;
		bool flag = true;
		for (int i = 0;i < 3;i++) flag &= proa[r1][i] * power (proa[l1 - 1][i],MOD[i] - 2,MOD[i]) % MOD[i] == prob[r2][i] * power (prob[l2 - 1][i],MOD[i] - 2,MOD[i]) % MOD[i];
		if (r1 - l1 + 1 == r2 - l2 + 1 && (sa[r1] ^ sa[l1 - 1]) == (sb[r2] ^ sb[l2 - 1])
		 && suma[r1] - suma[l1 - 1] == sumb[r2] - sumb[l2 - 1] && flag) puts ("Yes");
		else puts ("No");
	}
	return 0;
}
```

---

## 作者：xuduang (赞：0)

### 题意

给两个长为 $n$ 的序列 $A,B$，多次询问两个序列中的两个区间通过重排后是否相同。

### 分析

也是比较神奇的。

如果我们要通过前缀和一个一个数字比较的话，需要花费很多的时间，不可取。

那发现 $A_i,B_i \le n$，我们可以考虑类似哈希的随机数算法。

我们使用 `mt19937_64` 随出来一个很大的数，将每个数对应到一个随机的数上去。现在再做一遍前缀和，就可以直接比较了。这样做的错误率非常小，比较难卡。（也是可以再交一遍的）

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int s = 0, w= 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}
const int N = 2e6 + 10;
int n, q;
int a[N], b[N];
int sa[N], sb[N];
int num[N];
mt19937_64 md(random_device{}());//随机数
signed main()
{
    n = read(), q = read();
    for(int i = 1; i <= n; i++) num[i] = md();//给每个数随出来
    for(int i = 1; i <= n; i++) a[i] = read(), sa[i] = sa[i - 1] + num[a[i]];
    for(int i = 1; i <= n; i++) b[i] = read(), sb[i] = sb[i - 1] + num[b[i]];
    //简单来做一下前缀和
    while(q--)
    {
        int l1, l2, r1, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if(sa[r1] - sa[l1 - 1] == sb[r2] - sb[l2 - 1]) cout << "Yes\n";
        else cout << "No\n";
        //直接比较
    }
    return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

## AT_abc367_f [ABC367F] Rearrange Query 题解

### 题意
给你两个长度为 $n$ 的序列 $A$ 和 $B$ 以及 $Q$ 次询问，对于每次询问，判断是否可以重排 $A$ 的一个子序列以匹配 $B$ 的一个子序列。

### 思路
第一次场切 F，写篇题解纪念一下。

一眼哈希。

考虑哈希，给每一种数分配一个随机权值，再维护 $A$ 和 $B$ 新权值的前缀和。每次查询判断区间和是否相同即可。

注意相同的数的随机权值应相同，建议使用和哈希而非异或哈希。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
const int maxn=2e5+7;
int a[maxn];
int b[maxn];
int q;
int suma[maxn],sumb[maxn];
mt19937_64 rnd(233);
int rad[maxn];
void solve(){
	int n;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		rad[i]=rnd()%998244353;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=rad[a[i]];
		suma[i]=suma[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		b[i]=rad[b[i]]; 
		sumb[i]=sumb[i-1]+b[i];
	}
	while(q--){
		int l1,r1,l2,r2;
		cin>>l1>>r1>>l2>>r2;;
		if(suma[r1]-suma[l1-1]==sumb[r2]-sumb[l2-1]){
			puts("Yes");
		}
		else{
			puts("No");
		}
	}
}

int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
//	cin>>T;
	T=1;
	while(T--){
		solve();
	}
	return 0;
}



```

---

## 作者：EricWan (赞：0)

裸的哈希水题。

将每一个元素进行映射，我用的是 $123454321^x$，$x$ 是原数值，我们维护前缀和，看两个序列中的映射值和是否相等就可以 AC。

```cpp
#include <bits/stdc++.h>
#define int unsigned long long // 考试时打成了 unordered long long，还好马上改过来了
#define MAXN 10000005
using namespace std;
int quickpower(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) {
			c *= a;
		}
		a *= a;
		b >>= 1;
	}
	return c;
}
int n, m, a[MAXN], ha[MAXN], b[MAXN], hb[MAXN], la, ra, lb, rb;
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ha[i] = ha[i - 1] + quickpower(123454321, a[i]);
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		hb[i] = hb[i - 1] + quickpower(123454321, b[i]);
	}
	for (int i = 1; i <= m; i++) {
		cin >> la >> ra >> lb >> rb;
		if (ha[ra] - ha[la - 1] == hb[rb] - hb[lb - 1])
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

这题唯一的难点是，一共有两个序列而不是一个。

我们充分发扬人类智慧，把每个值映射 $a$ 到 $P^a$。对 $a, b$ 分别求映射后的前缀和。

利用哈希思想，只要询问的区间的和相等那么大概率他们就相等。直接询问 $a, b$ 两个数组对应区间的和即可。复杂度 $O(n + m)$。

模数选 $1222827239$ 能过。

每日一笑：

```cpp
rep(i, 1, n) s1[i] = (s1[i - 1] + p[a[i]]) % mod3;
rep(i, 1, n) s2[i] = (s2[i - 1] + p[a[i]]) % mod3;
```

---

## 作者：_sin_ (赞：0)

给出两个长度为 $n$ 的序列 $a,b$ 和 $q$ 个询问。每个询问都有两个区间 $[l,r],[L,R]$，判断序列 $a$ 的子区间 $[l,r]$ 和序列 $b$ 的子区间 $[L,R]$ 所构成的可重集是否相等。

首先，暴力判断是没有前途的，考虑构造哈希函数。考虑给 $1\sim n$ 的所有数都赋一个随意数作为哈希值，若序列 $a$ 的区间 $[l,r]$ 的哈希值和与序列 $b$ 的区间 $[L,R]$ 的哈希值想等，则判断相等，否则就判断不相等。

由于哈希值是随机数，不容易被卡掉。而区间和可以用前缀和做。时间复杂度为 $O(n+q)$。

注意这里不能用异或和，对于下面这组数据是可以卡掉异或和的：
```
3 1
1 2 2
1 3 3
1 3 1 3
```
代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return f*x;
}

const int N = 2e5+5;
ll n, q, a[N],b[N],hs[N];
ll sa[N],sb[N];

int main(){
	srand(time(0));n=read(),q=read();for(int i=1;i<=n;i++)hs[i]=rand();
	for(int i=1;i<=n;i++)a[i]=read(),sa[i]=sa[i-1]+hs[a[i]];
	for(int i=1;i<=n;i++)b[i]=read(),sb[i]=sb[i-1]+hs[b[i]];
	while(q--){
		int l=read(),r=read(),L=read(),R=read();
		puts(sa[r]-sa[l-1]==sb[R]-sb[L-1]?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：jhdrgfj (赞：0)

发现这个东西用数据结构不好维护，于是考虑哈希。

我们考虑选一个权值 $x$，维护 $\sum a_i^x$ 和 $\sum b_i^x$，再上几个不同的模数。询问先判长度相等，再用前缀和判哈希值是否相等即可。

[赛时代码](https://atcoder.jp/contests/abc367/submissions/56818391)。写了个用 $50$ 个模数维护 $1$ 到 $50$ 次方和的抽象东西。其实直接用一个种子上三模哈希就能过。

[同学的代码](https://atcoder.jp/contests/abc367/submissions/56833022)。只维护了 $\sum 17771^{a_i} \bmod 10^9+7$ 和 $\sum 17771^{b_i} \bmod 10^9+7$。能过，还很好写。

---

## 作者：maxyzfj (赞：0)

### 解题思路

原题要求的其实就是可重集 $\{A_l,A_{l+1},\cdots,A_r\}$ 是否与可重集 $\{B_L,B_{L+1},\cdots,B_R\}$ 完全相同。

首先，两个区间长度不相等时，答案一定是 $\texttt{No}$。

否则，注意到两个可重集完全相同，有一个必要条件：$\sum\limits_{i=l}^ra_i=\sum\limits_{i=L}^Rb_i$。然而，如果直接判断两可重集内元素的和是否相等，很容易被卡掉。因此，可以考虑一个更强的结论，即 $\sum\limits_{i=l}^ra_i^k=\sum\limits_{i=L}^Rb_i^k$ 对于任意实数 $k$ 都成立。同时，当 $k$ 比较大时，很难构造出两组不同的可重集使得其 $k$ 次方和相等。于是，我们可以考虑自己选择一个较大的自然数 $k$，并根据两可重集内元素的 $k$ 次方和是否相等来判断两可重集是否相同，这样错误的概率就很小了，可以通过。

时间复杂度 $O(n)$。

#### P.S.

- 如果选取的 $k$ 较大，可以考虑判断取模之后的结果，且对多个模数取模后依次判断更不容易出错。

- 我们还可以继续借鉴 [[CSP-S 2022] 星战](https://www.luogu.com.cn/problem/P8819) 的思路，考虑对每个不同的数值赋上一个不同的随机权值，再按照上述方案进行判断，在某些情况下可进一步减小出错的可能。

### 参考代码

本人的写法是取 $k=5$，并分别对三个不同模数取模再比较。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define mp(x,y) make_pair(x,y)
#define lb(x) (x&(-x))
#define fi first
#define se second
#define pii pair<int,int>
int read(){
	int x=0,f=1;
    char ch=getchar();
	while(ch<'0'||ch>'9'){
    	if(ch=='-')f=-1;
		ch=getchar();
    }
	while(ch>='0'&&ch<='9'){
    	x=x*10+ch-48;
		ch=getchar();
    }
	return x*f;
}
void writ(int x){
    if(x<0){
		putchar('-'),x=-x;
	}
    if(x>9){
		writ(x/10);
	}
    putchar(x%10 +'0');
}
void write(int x,char p=' '){
    writ(x);
    putchar(p);
}
string sread(){
    string t="";
    char c=getchar();
    while(c==' '||c=='\t'||c=='\r'||c=='\n'||c==0||c==EOF){
        c=getchar();
    }
    while(!(c==' '||c=='\t'||c=='\r'||c=='\n'||c==0||c==EOF)){
        t+=c,c=getchar();
    }
    return t;
}
const int mod1=1000000007,mod2=998244353,mod3=1004535809,inf=2e18+31,N=1e6+5;
mt19937 rnd(time(0)^clock());
int cal(int a,int b,int p){
	int base=a,ret=1;
	while(b){
		if(b&1){
			ret=ret*base%p;
		}
		base=base*base%p;
		b>>=1;
	}
	return ret;
}
int n,q;
struct node{
	int x,y,z;
	void operator=(node b){
		x=b.x;y=b.y;z=b.z;
	}
}a[N],b[N],s[N],t[N];
node operator+(node a,node b){
	return {(a.x+b.x)%mod1,(a.y+b.y)%mod2,(a.z+b.z)%mod3};
}
node operator-(node a,node b){
	return {(a.x-b.x+mod1)%mod1,(a.y-b.y+mod2)%mod2,(a.z-b.z+mod3)%mod3};
}
bool operator==(node a,node b){
	return a.x==b.x&&a.y==b.y&&a.z==b.z;
}
signed main(){
    n=read();q=read();
    for(int i=1;i<=n;i++){
    	a[i].x=read();a[i].y=a[i].z=a[i].x;
    	s[i]=(s[i-1]+node{cal(a[i].x,5,mod1),cal(a[i].y,5,mod2),cal(a[i].z,5,mod3)});
	}
    for(int i=1;i<=n;i++){
    	b[i].x=read();b[i].y=b[i].z=b[i].x;
    	t[i]=(t[i-1]+node{cal(b[i].x,5,mod1),cal(b[i].y,5,mod2),cal(b[i].z,5,mod3)});
	}
	while(q--){
		int x=read(),y=read(),z=read(),w=read();
		if(y-x!=w-z){
			puts("No");continue;
		}
		if(s[y]-s[x-1]==t[w]-t[z-1]){
			puts("Yes");
		}
		else{
			puts("No");
		}
	}
	return 0;
}
```

---

## 作者：WorldMachine (赞：0)

大多数人都维护的是和哈希，我是维护的区间最大值、最小值、平方和、立方和，如果都相等说明两个区间有很大概率是本质相同的。正确性可以参考 P3792。

我怎么写了个线段树。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 200005;
int n, q, a[N], b[N];
struct Seg {
	struct node {
		ull mx, mn, sum, sum2, sum3;
		node() {}
		node(ull v): mx(v), mn(v), sum(v), sum2(v * v), sum3(v * v * v) {}
		node(ull a, ull b, ull c, ull d, ull e): mx(a), mn(b), sum(c), sum2(d), sum3(e) {}
		node operator+(node b) {
			node c;
			c.mx = max(mx, b.mx);
			c.mn = min(mn, b.mn);
			c.sum = sum + b.sum;
			c.sum2 = sum2 + b.sum2;
			c.sum3 = sum3 + b.sum3;
			return c;
		}
		bool operator==(node b) {
			return mx == b.mx && mn == b.mn && sum == b.sum && sum2 == b.sum2 && sum3 == b.sum3;
		}
	} c[N * 4];
	void build(int l, int r, int p, int a[]) {
		if (l == r) {
			c[p] = node(a[l]);
			return;
		}
		int mid = (l + r) / 2;
		build(l, mid, p * 2, a), build(mid + 1, r, p * 2 + 1, a);
		c[p] = c[p * 2] + c[p * 2 + 1];
	}
	node query(int s, int e, int l, int r, int p) {
		if (s <= l && r <= e) return c[p];
		int mid = (l + r) / 2;
		node ans = node(0, ULLONG_MAX, 0, 0, 0);
		if (s <= mid) ans = ans + query(s, e, l, mid, p * 2);
		if (e > mid) ans = ans + query(s, e, mid + 1, r, p * 2 + 1);
		return ans;
	}
} ta, tb;
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	ta.build(1, n, 1, a), tb.build(1, n, 1, b);
	int la, ra, lb, rb;
	while (q--) {
		scanf("%d%d%d%d", &la, &ra, &lb, &rb);
		if (ra - la != rb - lb) { puts("No"); continue; }
		auto pa = ta.query(la, ra, 1, n, 1);
		auto pb = tb.query(lb, rb, 1, n, 1);
		puts(pa == pb ? "Yes" : "No");
	}
}
```

---

## 作者：mango2011 (赞：0)

好像是不怎么难的题。

首先，我们发现两个子段重排之后完全相同的充要条件就是它们每一种数出现的次数都相同。显然，我们不可能去计算每一个数出现的次数，因此，我们可以借鉴哈希的方法：

令一个数 $x$ 对总“哈希值”的贡献为 $s^{x}$，其中 $s>n$。这样子的话，我们就排除了顺序的影响，也同时避免了枚举每一个数。我们只需要分别维护 $A,B$ 的哈希前缀和数组，就可以单次做到 $O(1)$ 查询了。

总复杂度为 $O(n+q)$，因为 $n,q$ 同阶，所以也可以写作 $O(n)$。

---

## 作者：maokaiyu (赞：0)

[链接](https://atcoder.jp/contests/abc367/tasks/abc367_f)

**随机化大法好。**
## 思路
并没有想到什么合适的数据结构维护，于是考虑哈希。
## 做法
设数组 $X$ 是一个长度为 $n$ 的随机数组，范围在 $0$ 到 `unsigned long long` 的最大值。  
由于 $a_i$ 与 $b_i$ 并不大，所以可以继续设两个数组维护 $A$ 与 $B$ 集合的哈希值，不妨设为 $Y$ 与 $Z$，其中 $Y_i=Y_{i-1}+X_{a_i}$，特别的，$Y_0=0$。$Z$ 同理。  
那么，对于每一次询问，区间 $A$ 的哈希值为 $Y_r-Y_{l-1}$，区间 $B$ 为 $Z_r-Z_{l-1}$，若哈希值相同，我们便认为这两个区间是相同的，而且我们可以让其哈希值自然溢出。  
并且，在随机的情况下，我们也是很难被卡掉的。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
const I N = 2e5 + 10;
I n,q,a[N],b[N];
unsigned long long x[N],y[N],y2[N];//分别对应文中的 X,Y,Z 
I main(){
	scanf("%d%d",&n,&q);
	for(I i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	for(I i = 1;i <= n;i++){
		scanf("%d",&b[i]);
	}
	for(I i = 1;i <= n;i++){
		x[i] = rand() % ULONG_LONG_MAX;
	}
	for(I i = 1;i <= n;i++){
		y[i] = x[a[i]] + y[i - 1];//A的哈希值 
	}
	for(I i = 1;i <= n;i++){
		y2[i] = x[b[i]] + y2[i - 1];//B的哈希值 
	}
	for(;q--;){
		I l1,r1,l2,r2;
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		if(y[r1] - y[l1 - 1] != y2[r2] - y2[l2 - 1]){//哈希值相同则区间相同 
			puts("No");
		}else{
			puts("Yes");
		}
	}
	return 0;
}
```

---

## 作者：xz001 (赞：0)

看到大家都是用随机数维护的，我给一个新做法：

维护每个数的 $5$ 次方，用前缀和判断即可。

这样错误概率很小，和随机数类似，但这题卡掉了维护立方和。

代码：

```cpp
#include <bits/stdc++.h>

#define int __int128
#define re register 
#define il inline

using namespace std;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

const int N = 1e6 + 10;

int n, q, sum1[N], sum2[N], a[N], b[N]; 

signed main() {
    n = read(), q = read();
    for (int i = 1; i <= n; ++ i ) a[i] = read();
    for (int i = 1; i <= n; ++ i ) b[i] = read();
    for (int i = 1; i <= n; ++ i ) {
    	sum1[i] = sum1[i - 1] + a[i] * a[i] * a[i] * a[i] * a[i];
    	sum2[i] = sum2[i - 1] + b[i] * b[i] * b[i] * b[i] * b[i];
	}
	while (q -- ) {
		int l1, r1, l2, r2;
		l1 = read(), r1 = read(), l2 = read(), r2 = read();
		if (sum1[r1] - sum1[l1 - 1] == sum2[r2] - sum2[l2 - 1] && r1 - l1 == r2 - l2) {
			puts("Yes");
		} else {
			puts("No");
		}
	}
	return 0;
}

```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
对于一个排序后的序列看它是否与另一个序列相同，我们考虑前缀和，但是和相同会有很多可能，会发生冲突。

于是我们考虑哈希，将一个数反复乘很多遍以此来区分不同但和相同的序列。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long a[5000005],b[5000005],sum1[5000005],sum2[5000005];
long long qpow(long long a,long long b)
{
    long long res=1;
    while(b)
    {
        if(b%2==1)res*=a,res%=mod;
        b/=2,a*=a,a%=mod;
    }
    return res;
}
int main()
{
    long long n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++)
    {
        sum1[i]=sum1[i-1]+qpow(a[i],mod-114514),sum1[i]%=mod;
        sum2[i]=sum2[i-1]+qpow(b[i],mod-114514),sum2[i]%=mod;
    }
    for(int i=1;i<=m;i++)
    {
        long long lx,rx,ly,ry;
        cin>>lx>>rx>>ly>>ry;
        if(((sum1[rx]-sum1[lx-1])%mod+mod)%mod==((sum2[ry]-sum2[ly-1])%mod+mod)%mod)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}
```

---

## 作者：Lotus_Land (赞：0)

### 题意

给你长度为 $N$ 的正整数序列：$A=(A_1,A_2,\ldots,A_N)$ 和 $B=(B_1,B_2,\ldots,B_N)$。

您需要依次处理 $Q$ 个查询。第 $i$ 个查询的解释如下。

- 给定正整数 $l_i,r_i,L_i,R_i$。判断 $(A_{l_i},A_{l_i+1},\ldots,A_{r_i})$ 是否能在重新排列之后与序列 $(B_{L_i},B_{L_i+1},\ldots,B_{R_i})$ 相同。

### 分析

感觉 E、F 都比 D 简单。

思路来源自 P3792。

要使两个序列能够相同，只需要保证每个数在两个序列中出现的次数相等就可以了。即，不用考虑顺序。

标准做法当然是哈希。我的做法是对于每个 $i(1\leq i\leq N)$，分别算出 $A_i,B_i,A_i^2,B_i^2,\dots,A_i^5,B_i^5$ 的前缀和。查询的时候，只要判断两个序列的元素和、平方和、立方和……五次方和是否全部相等就行。

```cpp
int n,m;
ull a[N],b[N],sa[N][5],sb[N][5];
ull geta(int l,int r,int t){
	return sa[r][t]-sa[l-1][t];
}
ull getb(int l,int r,int t){
	return sb[r][t]-sb[l-1][t];
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++)cin>>a[i];
	for(int i=1; i<=n; i++)cin>>b[i];
	ull tmp;
	for(int i=1; i<=n; i++) {
		tmp=a[i];
		for(int j=0;j<=4;j++){
			sa[i][j]=sa[i-1][j]+tmp;
			tmp*=a[i];
		}
		tmp=b[i];
		for(int j=0;j<=4;j++){
			sb[i][j]=sb[i-1][j]+tmp;
			tmp*=b[i];
		}
	}
	int l1,r1,l2,r2;
	for(int i=1;i<=m;i++){
		cin>>l1>>r1>>l2>>r2;
		if(r1-l1!=r2-l2)cout<<"No\n";
		else{
			bool flg=1;
			for(int j=0;j<=4;j++){
				if(geta(l1,r1,j)!=getb(l2,r2,j)){
					flg=0;
					break;
				}
			}
			if(flg)cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：gavinliu266 (赞：0)

# 思路
观察到值域很小，于是考虑哈希，把每个数映射为一个大整数，这样可以减少两个数哈希值之和等于另一个数的哈希值的情况。然后统计区间和，最后通过判断区间和是否相等来判断区间内相同元素的个数是否相等。

高质量的随机数可以用 `mt19937_64`，同时可以多用几个模数，以提高准确率。

单次询问时间复杂度：$\Theta(1)$。
# 代码实现
```cpp
#include <cstdio>
#include <ctime>
#include <random>
using namespace std;
typedef long long ll;
const ll mod1 = 1e18 + 3;
const ll mod2 = 1e17 + 3;
const ll mod3 = 1e16 + 61;  // 我不信三模数哈希还会被卡
const int N = 2e5 + 5;
int n, q, x;
struct hsh {
    ll hsh1, hsh2, hsh3;
    hsh operator-(const hsh &o) const {
        return {(hsh1 - o.hsh1 + mod1) % mod1, (hsh2 - o.hsh2 + mod2) % mod2, (hsh3 - o.hsh3 + mod3) % mod3};
    }
    hsh operator+(const hsh &o) const {
        return {(hsh1 + o.hsh1) % mod1, (hsh2 + o.hsh2) % mod2, (hsh3 + o.hsh3) % mod3};
    }
    bool operator==(const hsh &o) const {
        return hsh1 == o.hsh1 && hsh2 == o.hsh2 && hsh3 == o.hsh3;
    }
} thsh[N], hsha[N], hshb[N];
int main() {
    scanf("%d%d", &n, &q);
    mt19937_64 gen(time(NULL));
    for(int i = 1; i <= n; ++i) {
        ll t = gen();
        thsh[i] = {(t % (mod1 - 1) + mod1 - 1) % (mod1 - 1) + 1,
                   (t % (mod2 - 1) + mod2 - 1) % (mod2 - 1) + 1, 
                   (t % (mod3 - 1) + mod3 - 1) % (mod3 - 1) + 1};  // 哈希值不要为 0。
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        hsha[i] = hsha[i - 1] + thsh[x];
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        hshb[i] = hshb[i - 1] + thsh[x];
    }
    while(q--) {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if(hsha[r1] - hsha[l1 - 1] == hshb[r2] - hshb[l2 - 1])
            printf("Yes\n");
        else printf("No\n");
    }
}
```

---

## 作者：hhhqx (赞：0)

这题等价于要我们比较两个可重集合是否完全相等。

比较可重集合，考虑用和哈希，给每个值随机一个权值，再前缀和就可以了。

注意题目是给了 $1 \le A_i,B_i \le n$。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using PII = pair<int, int>;

const int MAXN = 2e5 + 3;

int n, Q;
int a[MAXN], b[MAXN];
LL w[MAXN];
LL sa[MAXN], sb[MAXN];

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> Q;
  mt19937_64 rnd(time(0));
  for(int i = 1; i <= n; i++) w[i] = rnd() % LL(1e12);
  for(int i = 1; i <= n; i++){
    cin >> a[i], sa[i] = sa[i - 1] + w[a[i]];
  }
  for(int i = 1; i <= n; i++){
    cin >> b[i], sb[i] = sb[i - 1] + w[b[i]];
  }
  while(Q--){
    int l, r, L, R;
    cin >> l >> r >> L >> R;
    LL ss = sa[r] - sa[l - 1], _ss = sb[R] - sb[L - 1];
    cout << (ss == _ss ? "Yes\n" : "No\n");
  }
  return 0;
}
```

---

## 作者：zhlzt (赞：0)

### 官方题解

对于一个数列 $c_1,c_2,\ldots,c_m$，我们定义哈希函数 $h(c)$ 为：

$$h(c)=\left(\sum\limits_{i=1}^m seed^{c_i}\right)\bmod p$$

那么只要 $seed$ 和 $p$ 足够大，就可以避免冲突，取 $seed>m$ 和 $p=10^9+7$ 即可。

对于询问我们只需判断 $h(A_{l\sim r})$ 和 $h(B_{L\sim R})$ 是否相等，预处理 $A,B$ 的前缀哈希值即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int seed=233333;
const int mod=1e9+7;
const int maxn=2e5+10;
int dp[maxn],prea[maxn],preb[maxn];
int a[maxn],b[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	dp[0]=1;
	for(int i=1;i<=n;i++) dp[i]=1ll*dp[i-1]*seed%mod;
	for(int i=1;i<=n;i++){
		prea[i]=(prea[i-1]+dp[a[i]])%mod;
		preb[i]=(preb[i-1]+dp[b[i]])%mod;
	}
	while(q--){
		int la,ra;cin>>la>>ra;
		int lb,rb;cin>>lb>>rb;
		int val1=(prea[ra]-prea[la-1]+mod)%mod;
		int val2=(preb[rb]-preb[lb-1]+mod)%mod;
		cout<<(val1==val2?"Yes\n":"No\n");
	}
	return 0;
}
```

---

## 作者：zbrprogrammer (赞：0)

### [\[ABC367F\] Rearrange Query - 洛谷](https://www.luogu.com.cn/problem/AT_abc367_f)

### 题意简述：

给出两个序列 $A,B$，询问子序列 $A_l,\dots,A_r$ 与 $B_L,\dots,B_R$ 是否相同。

### 问题分析：

本题的 $A_i,B_i$ 都较小，考虑分块，对每个块开桶比较。

但每次桶比较都是 $O(N)$ 的，会超时。因此考虑数据压缩，这里选择使用哈希。

由于加法是满足交换律与结合律的，所以加法哈希的正确性可以保证。

我们对 $1,\dots,N$ 之间的每一个数通过 `map` 转化为一个随机数，每个块内随机数求和。

提交后发现分块会超时，所以弃用分块，考虑使用前缀和。

每次询问时分别求出两个序列的区间哈希值和，判断是否相同。

### Code:

```cpp
#include<bits/stdc++.h>
#ifndef ONLINE_JUDGE
		#define DEBUG(x) std::cerr<<#x<<":"<<x<<endl
		#define DEBUGP(x) std::cerr<<#x<<":"<<x<<endl;system("pause")
		#define FILE(x) freopen(#x ".in","r",stdin);freopen(#x ".out","w",stdout);
#else
	 #define DEBUG(x)
	 #define DEBUGP(x)
	 #define FILE(x)
#endif
using namespace std;
const int MAXN=200005;
int n,q,bn,a[MAXN],b[MAXN];
unsigned long long hasha[MAXN],hashb[MAXN];
//选用 unsigned long long 是为了保证哈希值足够分散，不会碰撞。
map<int,unsigned long long>mp;
//前缀和求区间哈希和。
unsigned long long getans(int x,int l,int r){
	if(x==1){
		return hasha[r]-hasha[l-1];
	}
	return hashb[r]-hashb[l-1];
}
int main(){
	srand(time(0));
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mp[i]=(unsigned long long)rand()*rand();
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
//	for(int i=1;i<=n;i++){
//		printf("%llu ",mp[i]);
//	}
//	printf("\n");
	for(int i=1;i<=n;i++){
		hasha[i]=hasha[i-1]+mp[a[i]];
		hashb[i]=hashb[i-1]+mp[b[i]];
	}
	int l,r,L,R;
	while(q--){
		scanf("%d%d%d%d",&l,&r,&L,&R);
		unsigned long long ansa=getans(1,l,r),ansb=getans(2,L,R);
//		printf("%llu %llu\n",ansa,ansb);
		printf(ansa==ansb?"Yes\n":"No\n");
	}
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/173524465)

---

## 作者：Albatross_LC (赞：0)

很水的一道 F 题。

由于 $1\le A_i,B_i \le N$，且 $1\le N\le 2\times 10^5$，我们便可以先处理出数组 $a$、$b$ 中每个数的哈希值，再求出前缀和数组，取然后对于每个询问求出数组中对应区间的哈希值的和，哈希值的和相等则输出 `Yes`，否则输出 `No`。

代码如下：

```cpp
//Albatross_LC
#include <bits/stdc++.h>
#define int long long
#define uint unsigned int
#define PII pair<int, int>
#define x first
#define z second
#define up(i, x, y) for(int i = x; i <= y; i ++ )
#define dn(i, x, y) for(int i = x; i >= y; i -- )
using namespace std;
int read() {
  int res = 0, c = getchar(), s = 0;
  while (!isdigit(c)) s |= c == '-', c = getchar();
  while (isdigit(c)) res = (res << 1) + (res << 3) + c - '0', c = getchar();
  return s ? -res : res;
}
const int N = 2e5 + 10, M = 4444455555666667ll, base = 16793;
int n, m, q, l1, r1, l2, r2, t1, t2, a[N], b[N], p[N];
signed main() {
  n = read(),m = read();
  p[0]= 1;
  up(i, 1, n) p[i] = p[i - 1] * base % M;
  up(i, 1, n) a[i] = a[i - 1] + p[read()];
  up(i, 1, n) b[i] = b[i - 1] + p[read()];
  while (m -- ) puts(a[read() - 1] - a[read()] == b[read() - 1] - b[read()] ? "Yes" : "No");
}
```

---

