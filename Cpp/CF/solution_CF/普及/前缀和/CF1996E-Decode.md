# Decode

## 题目描述

In a desperate attempt to obtain your waifu favorite character, you have hacked into the source code of the game. After days of struggling, you finally find the binary string that encodes the gacha system of the game. In order to decode it, you must first solve the following problem.

You are given a binary string $ s $ of length $ n $ . For each pair of integers $ (l, r) $ $ (1 \leq l \leq r \leq n) $ , count the number of pairs $ (x, y) $ $ (l \leq x \leq y \leq r) $ such that the amount of $ \mathtt{0} $ equals the amount of $ \mathtt{1} $ in the substring $ s_xs_{x+1}...s_y $ .

Output the sum of counts over all possible $ (l, r) $ modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
4
0000
01010101
1100111001
11000000111```

### 输出

```
0
130
147
70```

# 题解

## 作者：ZhaoV1 (赞：8)

# 题目大意

首先选中一个区间 $(x,y)$，该区间内数字 $1$ 的个数和与数字 $0$ 的个数和应当相等，由于区间 $(x,y)$ 是区间 $(l,r)$ 的子串，而我们所要求的是对于所有满足条件的区间 $(x,y)$，一共有多少种区间 $(l,r)$。

# 解析

首先经过简单的模拟，我们发现前缀和可以完好吻合这道题，我们维护一个见到 $s_i=1$ 则 $+1$，反之见到 $s_i=0$ 则 $-1$的前缀和，每当前缀和在某两位上的值相同时，例如 $sum_x=sum_y$，这表明区间 $(x+1,y)$ 内的 $1$ 数量的总和与 $0$ 数量的总和相等，因此区间 $(x+1,y)$ 对答案的贡献为 $(x+1)×(n-y+1)$，其中 $n$ 为字符串总长度。

举个例子：

```
对于如下样例：
  s串    1100111001
前缀和：01210123212

按照刚才所说的，相同前缀和相同的两个位置做乘法计算贡献。

对于前缀和为 0 的位置：
res += 1*7（即第 1 位左边项数×第 5 位右边项数和）

对于前缀和为 1 的位置：
res += 2*8 + 2*6 + 2*2
res += 4*6 + 4*2

对于......

最终 res = 147
```

为了达到上述模拟的效果和速度，我们使用 map 存前缀和值，数量累加 $i+1$（由于是前缀和，右边减左边和 $1$ 的差，所以要 $+1$），不断做 $(x+1)×(n-y+1)$ 计入答案。


AC Code
---


```cpp
#define int long long
const int MOD = 1e9+7;
int t,n;
string s;

void solve(){
	int res = 0;
	cin >> s;
	n = s.size(); s = " " + s;

	map<int,int> mp;
	mp[0] = 1;
	int sum = 0;
	for(int i=1;i<=n;i++){
		if(s[i] == '1') sum++;
		else sum--;
		res = (res+mp[sum]*(n-i+1))%MOD;
		mp[sum] = (mp[sum] + i+1)%MOD;
	}
	cout << (res+MOD)%MOD << '\n';
}
```

---

## 作者：PineappleSummer (赞：4)

[CF1996E Decode](https://codeforces.com/problemset/problem/1996/E)

套路题。

考虑将原串中的 `0` 当作 $1$，`1` 当作 $-1$，对数组做一遍前缀和，如果 $x$ 和 $y$ 的前缀和相同，那么 $(x+1,y)$ 这个区间中 `0` 的个数等于 `1` 的个数。

考虑每一个合法区间 $(l,r)$ 对答案的贡献，发现 $(l,r)$ 对答案的贡献为 $l\times (n-r+1)$。对于每一个 $r$，设以 $r$ 为右端点的合法区间的左端点为 $l_1,l_2,l_3\ldots l_k$，对答案的贡献即为 $l_1\times (n-r+1)+l_2\times (n-r+1)\times \ldots=(\sum\limits _{i=1}^kl_i)\times (n-r+1)$。开一个 `map` 统计相同前缀和的 $l$ 之和，然后累加答案即可。

时间复杂度 $\mathcal O(n)$，可能会带一个 `map` 的 $\log$。也可以不用 `map`，对前缀和加一个偏移量避免负数。

```cpp
void solve () {
	scanf ("%s", s + 1);
	n = strlen (s + 1);
	cnt.clear (); int ans = 0;
	cnt[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + (s[i] == '0' ? 1 : -1);
		ans = (ans + cnt[f[i]] * (n - i + 1) % mod) % mod;
		cnt[f[i]] = (cnt[f[i]] + i + 1) % mod;
	}
	printf ("%lld\n", ans);
}
```

---

## 作者：___w (赞：3)

[CF1996E Decode](https://codeforces.com/contest/1996/problem/E)

题目要求所有子区间的子区间的贡献之和，那么一个子区间 $[l,r]$ 的贡献就要乘上 $l*(n-r+1)$，因为左端点在 $[1,l]$ 内，右端点在 $[r,n]$ 范围内的区间均包含该区间。

我们令 $0$ 为 $-1$，计算前缀和 $s$，那么一个区间 $[l,r]$ 内 $0$ 的个数等于 $1$ 个个数等价于 $s_r=s_{l-1}$。我们考虑枚举右端点 $r$，去数 $[0,r-1]$ 内有多少个 $s_i$ 满足 $s_i=s_r$。所有的区间要乘上系数 $(i+1)*(n-r+1)$，故贡献之和为 $(n-r+1)$ 乘上所有满足的 $i+1$ 之和。这里我们可以用数组 $cnt_i$ 表示 $[0,i-1]$ 内满足 $s_j=s_i$ 的 $j+1$ 之和，实现的时候注意负数的情况。时间复杂度为 $O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

const int mod = 1e9+7;
char c[200005];

void solve() {
	cin >> (c+1);
	int n = strlen(c+1), ans = 0; vi s(n+1), cnt(n*2+5);
	for (int i = 1; i <= n; ++i) {
		s[i] = c[i] == '0' ? -1 : 1;
		s[i] += s[i-1];
	}
	cnt[n] = 1;
	for (int i = 1; i <= n; ++i) {
		ans = (ans+1ll*(n-i+1)*cnt[s[i]+n]%mod)%mod;
		cnt[s[i]+n] = (cnt[s[i]+n]+i+1)%mod;
	}
	cout << ans << '\n';
}

int main() {
	int t = rd();
	while (t--) solve();
	return 0;
}
```

---

## 作者：_sin_ (赞：3)

对于 $01$ 数量相同问题有个经典套路：把 $0$ 设为 $-1$ 转换为区间和为 $0$ 的问题。

对于区间和为 $0$ 的问题，先做一个前缀和，转换为两点前缀和相减为 $0$ 的问题，即两点前缀和一样。

考虑扫描线求解，固定 $y$ 端点，用数据结构维护所有 $x$ 端点对答案的贡献。对于区间 $[x,y]$,它会被覆盖 $x(n-y+1)$ 次。

具体我们可以用 map 进行维护，时间复杂度为 $O(Tn\log n)$.

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5+5,mod=1e9+7;
int T, n;
ll a[N],sum[N],ans=0;
char s[N];
map<ll,ll>mp;

void solve(){
	scanf("%s",s+1);n=strlen(s+1);mp.clear();ans=0;mp[0]=1;
	for(int i=1;i<=n;i++)a[i]=(s[i]=='1'?1:-1),sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++){
		ans=(ans+(n-i+1)*mp[sum[i]]%mod)%mod;mp[sum[i]]+=i+1;
	}printf("%lld\n",ans);
}

int main(){
	scanf("%d",&T);while(T--)solve();
	return 0;
}
```

---

## 作者：yemuzhe (赞：2)

考虑一段区间 $[l, r]$ 什么时候是合法的。

设 $s0 _ i$ 为字符串 $s _ {1 \sim i}$ 中出现的 $0$ 的个数，$s1 _ i$ 为字符串 $s _ {1 \sim i}$ 中出现的 $1$ 的个数，则字符串 $s _ {l \sim r}$ 中 $0$ 的个数为 $s0 _ r - s0 _ {l - 1}$，$1$ 的个数为 $s1 _ r - s1 _ {l - 1}$（其实 $s0, s1$ 就是前缀和）。

也就是说，一段区间 $[l, r]$ 是合法的当且仅当 $s0 _ r - s0 _ {l - 1} = s1 _ r - s1 _ {l - 1}$。把关于 $r$ 的项移到左边，关于 $l$ 的项移到右边，则 $s0 _ r - s1 _ r = s0 _ {l - 1} - s1 _ {l - 1}$。

也就是说，对于两个位置 $l - 1, r$，只要它们 $s0, s1$ 的差相等，中间的 $[l, r]$ 就是合法的。

所以我们记录一个桶 $cnt _ i$ 表示 $s0 _ {l - 1} - s1 _ {l - 1} = i$ 的下标 $l$ 的个数。从前往后遍历每个 $r$，并动态更新 $cnt$ 数组，对于一个下标 $r$，答案就是 $cnt _ {s0 _ r - s1 _ r}$。所以我们先进行 `ans += cnt[s0[r] - s1[r]]` 操作，再进行 `cnt[s0[r] - s1[r]] ++` 操作。

由于 $s0 - s1$ 可能是负数，所以存数组时要向右平移一段距离。注意刚开始时 $cnt _ 0 = 1$（因为 $l - 1$ 可能为 $0$）。

这样我们可以求出合法区间的个数，但题目让我们对于每个区间，都求出其内部合法区间的个数。

于是考虑拆贡献，就是对于一个合法区间 $[l, r]$，算一下它被几个区间包含。容易发现，它会被 $l \cdot (n - r + 1)$ 个区间包含，因为 $l$ 及其左边有 $l$ 个空位，$r$ 及其右边有 $n - r + 1$ 个空位，两者相乘即可。

因为我们枚举的是 $r$，所以 $n - r + 1$ 是个定值，在外面乘就好。于是我们只要把 `ans += cnt[s0[r] - s1[r]]` 改成 `ans += cnt[s0[r] - s1[r]] * (n - r + 1)`；`cnt[s0[r] - s1[r]] ++` 改成 `cnt[s0[r] - s1[r]] += r + 1` 就行。

为什么最后一个代码块中是 $r + 1$ 而不是 $r$？因为我们动态更新的时候其实这里的 $r$ 是新的 $l ^ \prime - 1$，而左边的空位有 $l ^ \prime$ 个，所以相当于是加上 $l ^ \prime = r + 1$。

最后注意答案要取模。

放上代码（代码中的 $sum$ 其实是 $s1 - s0$，因为 $s0, s1$ 顺序调换没有本质区别）：

```cpp
#include <cstdio>
#include <cstring>
#define N 200005
using namespace std;

const int mod = 1e9 + 7;

int T, n, ans, cnt[N * 2];
char s[N];

int add (int &x, long long y) {return x = (x + y) % mod;}

int main ()
{
    scanf ("%d", &T);
    while (T --)
    {
        scanf ("%s", s + 1), n = strlen (s + 1);
        add (cnt[N], 1), ans = 0;
        for (int i = 1, sum = 0; i <= n; i ++)
        {
            sum += s[i] == '1' ? 1 : -1;
            add (ans, cnt[N + sum] * (n - i + 1ll));
            add (cnt[N + sum], i + 1);
        }
        printf ("%d\n", ans);
        for (int i = N - n; i <= N + n; i ++) cnt[i] = 0;
    }
    return 0;
}
```

---

## 作者：Kindershiuo (赞：1)

# 解题思路
赛时差一点没想出来，连夜写了一篇题解。题目是让我们锁定一个区间然后找到这个区间里面 $0$ 和 $1$ 数量相等的一个区间，那么我们转换一下思路，我们先找到一个 $0$ 和 $1$ 数量相等的一个区间，然后再去把它左右都扩展不就好了嘛，那么问题来了，我们如何找到一个 $0$ 和 $1$ 数量相等的区间呢，我们转换成前缀和来想，我们要把 $0$ 当成对前缀和是减一（不然不好算）然后我们就计算前缀和，但我们发现这个和在之前出现过了，那么就意味着我们中间有一段是和为 $0$ 的区间，也就是说是 $0$ 和 $1$ 数量相等的一段区间，那么我们就把它拎出来左右扩展计算答案就行，但是我们这样的做法会有一点点的小问题，就比如样例的 $01010101$，我们单纯这样算的话会忽略一个情况，就是当两个 $01$ 叠加的情况我们会忽略掉，所以我们还要保存每次我们遇到的 $0$ 和 $1$ 数量相等的区间的左端点的情况，不然的就会出问题。 
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;//别忘记取mod哦//
#define endl '\n'
int T;

void solve() {
	string s;
	cin>>s;
	int n=s.length();
	s=' '+s;
	int sum=0;
	map<int,int>f,ff;
	f[0]=1;
	ff[0]=1;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='0')sum--;
		else sum++;
		if(f.count(sum)){
			ans+=((n-i+1)*ff[sum]%mod);
		}
		f[sum]++;
		ff[sum]+=i+1;
	}
	cout<<ans%mod<<endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
//	T=1;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

题目要求统计的是每一个 $(l,r)$ 中合法子串的数量，意味着暴力的来做需要枚举 $l,r$ 以及其子串来统计答案。

可以想到一个子串会在不同的 $(l,r)$ 中被统计多次。具体的，对于合法子串 $(L,R)$ 来说，可以被 $l\in[1,L],r\in[R,n]$ 所组成的 $(l,r)$ 统计到。所以单个 $[L,R]$ 的贡献为 $L\times(n-R+1)$。

考虑如何快速统计合法字串 $(L,R)$。固定左端点 $L$，将原序列做前缀和，$0$ 的贡献记为 $-1$，$1$ 的贡献记为 $1$，若前缀和数组中位置 $i$ 出现了 $A=0$，则说明 $(L,i)$ 为合法字串，可以计入贡献。当 $L$ 移动，会使前缀和数组以 $L$ 往后做全局加或减的操作。计入贡献的标准 $A$ 也会随之变化。而 $A$ 的变化和前缀和数组的变化同步进行，于是在操作开始之前将前缀和数组出现的数用桶存起来，统计答案时改变标准后将贡献累计答案即可。

由于前缀和可能出现负数，所以桶用 map 替代时间复杂度 $O(n\log n)$。

# Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define mod 1000000007

using namespace std;

const int N = 2e5 + 10; 

int T, n, sum[N];

char s[N];

map<int, int> mp;

void solve() {
  int ans = 0;
  map<int, int>().swap(mp);
  cin >> (s + 1);
  n = strlen(s + 1);
  For(i,1,n) sum[i] = sum[i-1] + (s[i] == '0' ? -1 : 1);
  For(i,1,n) {
    mp[sum[i]] = (mp[sum[i]] + (n-i+1) % mod) % mod;
  }
  int A = 0;
  For(i,1,n) {
    ans = (ans + (i * mp[A]) % mod) % mod;
    mp[sum[i]] = (mp[sum[i]] - (n-i+1) % mod + mod) % mod;
    if(s[i] == '0') A--;
    else A++;
  }
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve(); 
  return 0;
}
```

---

## 作者：Guchenxi0971 (赞：0)

~~感觉 E 比 D 还简单。~~

题目给定一个字符串 $S$ ，定义 $f(l,r)$ 表示所有的 $(x, y)$ $(l \leq x \leq y \leq r)$ 的对数，使其满足 $S[x,y]$ 中 $1$ 的个数等于 $0$ 的个数，然后求出所有  $(l,r),(1\leq l\leq r\leq n)$ 的 $f(l,r)$ 之和。

### Sol

感觉不能通过 $(l,r)$ 计算，可以考虑计算一对 $(x,y)$ 对答案的贡献。

发现题目不带修，考虑前缀和，将 $0$ 的值设为 $-1$，$1$ 的值就是 $1$。那么满足条件的 $(x,y)$ 满足 $sum_y-sum_{x-1}=0$，我们可以枚举 $x$，找到所有满足条件的 $y$，那么 $x$ 会产生的贡献是：
$$
\sum_{i=1}^Y (n-y_i+1)x\\
=x\sum_{i=1}^Y (n-y_i+1)
$$
（其中 $Y$ 表示满足条件的 $y$ 的个数，$y_i$ 表示第 $i$ 个满足条件的 $y$）

因为所有满足条件的 $y$ 的 $sum_y$ 值都是等于 $sum_{x-1}$ 的，可以考虑使用，那么我们可以先使用一个东西维护。那么每次移动 $x$ 都只会修改一个值，同时查询一个值，那么我们可以使用 ~~单修单查线段树~~ 一个桶维护答案，那么我们就先将 $(n-i+1)$ 这个值加入到 $sum_i$ 这个桶中，然后再遍历 $i$，当遍历到 $i$ 时将其贡献删除，然后查询再 $sum_{i-1}$ 这个桶中的元素的值之和然后成员 $i$ 就行。

### Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define int long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
const int Max=2e5+10;
const int mod=1e9+7;
const int inf=1e9+10;



inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

int sum[Max];
map <int,int>num;//桶
char c[Max];

void work(){
	scanf("%s",c+1);
	int n=strlen(c+1);
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1];
		if(c[i]=='1')sum[i]++;
		else sum[i]--;
		num[sum[i]]+=(n-i+1);
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		num[sum[i]]-=(n-i+1);
		int z=sum[i-1];
		ans=(ans+i*(num[z])%mod)%mod; 
	}
	cout << ans << "\n";
	
}

signed main(){
	int t=read();
	while(t--)work();
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## CF1996E

如果问的是整串中 $\texttt 0$ 的个数等于 $\texttt 1$ 的个数的子串数量，可以把 $\texttt 1$ 看作 $1$，把 $\texttt 0$ 看作 $-1$，然后对每个点的前缀和 $sum$，统计之前还有多少个点的前缀和等于 $sum$，累加，用桶维护即可。

考虑如果一个子串 $l\sim r$ 是符合条件的，那么包含它的子串有左右两部分距离完整串距离乘积个子串。可以把左半部分的贡献每次加入桶，右半部分的贡献每次计算时乘上。

代码：

```cpp
void Main() {
  scanf("%s", a + 1);
  n = strlen(a + 1), ans = 0;
  f.clear();
  f[0] = 1;
  for (int i = 1, sum = 0; i <= n; i++) {
    sum += (a[i] == '0' ? -1 : 1);
    ans = (ans + f[sum] * (n - i + 1) % P) % P;
    f[sum] = (f[sum] + 1 + i) % P;
  }
  printf("%lld\n", ans);
}
```

---

