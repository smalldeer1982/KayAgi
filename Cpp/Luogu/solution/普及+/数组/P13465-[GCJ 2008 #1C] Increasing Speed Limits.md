# [GCJ 2008 #1C] Increasing Speed Limits

## 题目描述

你在高速公路上行驶时因超速被交警拦下。原来他们一直在跟踪你，他们惊讶地发现你一路都在加速，完全没有踩刹车！现在你急需一个借口来解释这一切。

你决定说：“我看到的所有限速标志都是递增的，所以我一直在加速。”警察听后大笑，并把你经过的这段高速公路上所有的限速标志都告诉了你，并表示你不太可能这么幸运，刚好只看到了一段递增的标志。

现在你需要估算这种情况发生的概率，换句话说，就是要找出给定序列中有多少个不同的严格递增子序列。空子序列不计入答案，因为那意味着你根本没看任何限速标志！

例如，$(1, 2, 5)$ 是 $(1, 4, 2, 3, 5, 5)$ 的一个递增子序列，并且我们要计数两次，因为有两种方式可以从原序列中选出 $(1, 2, 5)$。

## 说明/提示

**样例说明**

对于第 $2$ 个测试用例，限速标志序列应为 $1, 2, 0, 0, 0, 4$。

**数据范围**

- $1 \leq N \leq 20$
- $1 \leq m \leq 100$
- $0 \leq X \leq 10^9$
- $0 \leq Y \leq 10^9$
- $1 \leq Z \leq 10^9$
- $0 \leq A[i] < Z$

**小数据范围（15 分，测试点 1 - 可见）**

- $1 \leq m \leq n \leq 1000$

**大数据范围（35 分，测试点 2 - 隐藏）**

- $1 \leq m \leq n \leq 500000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5 5 0 0 5
1
2
1
2
3
6 2 2 1000000000 6
1
2```

### 输出

```
Case #1: 15
Case #2: 13```

# 题解

## 作者：MonKeySort_ZYczc (赞：1)

好板子啊，总感觉有原题呢（思考）。
## 思路流程
以下用“好子序列”代替“非空严格递增子序列”。  
转化题意，原题要求我们求序列好子序列的数量。  
设 $dp_i$ 为以 $a_i$ 结尾的好子序列的数量，有
$$
dp_i=(\sum_{j=1}^{i-1}[a_j<a_i]\times dp_j)+1
$$
（其中 $[]$ 为 Iverson 括号，若其中表达式为真值就是 1，否则是 0）。  
后面有一个 $+1$ 原因是，只有一个数也是好子序列。  
但是这样复杂度是 $O(Nn^2)$ 的，写的比较丑小数据也许都跑不过去。  
考虑优化。  
由于对于每个 $a_i$ 只有每个小于 $a_i$ 的 $a_j$ 能计入答案，考虑使用值域树状数组。  
具体的，设 $c_i=\sum[a_j=i]dp_j$，则 $dp_i=c_{a_i-1}+1$（假如从前往后按顺序扫）。  
由于值域比较大，先离散化一下就行了。  
时间复杂度为 $O(Nn\log n)$，6s 可以跑过。

千万，千万，不要忘记开 ```long long```！
## 代码实现
我去大数据跑了 5.76s，是离散化 ```set``` 与 ```unodered_map``` 慢了？树状数组常数不大吧。  
注意离散化不要从 0 开始，树状数组有死循环的风险。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define sit set<int>::iterator
const int N=5e5+10,mod=1e9+7;
int n,m,x,y,z,seed[N],a[N],T,c[N],tot;
inline int read()
{
	char c=getchar();
	while(c>'9'||c<'0') c=getchar();
	int a=c-'0';
	while((c=getchar())<='9'&&c>='0') a=(a<<3)+(a<<1)+c-'0';
	return a;
}
inline void upt(int p,int k)
{
	for(;p<=tot;p+=p&-p) c[p]=(c[p]+k)%mod;
}
inline int que(int p)
{
	int ans=0;
	for(;p;p-=p&-p) ans=(ans+c[p])%mod;
	return ans;
}
inline void sol(int sum)
{
	memset(c,0,sizeof(c));tot=0;
	n=read();m=read();x=read();y=read();z=read();
	for(int i=0;i<m;i++) seed[i]=read();
	set<int>s;
	for(int i=0;i<n;i++)
	{
		a[i+1]=seed[i%m];
		seed[i%m]=(x*seed[i%m]+y*(i+1))%z;
		s.insert(a[i+1]);
	}
	unordered_map<int,int>mp;
	for(sit it=s.begin();it!=s.end();it++) mp[*it]=++tot;
	for(int i=1;i<=n;i++) a[i]=mp[a[i]];
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int t=que(a[i]-1)+1;
		ans=(ans+t)%mod;
		upt(a[i],t);
	}
	printf("Case #%d: %d\n",sum,ans);
}
signed main(){
	T=read();
	int temp=0;
	while(T--) sol(++temp);
}

```

---

## 作者：liuchuliang666 (赞：0)

这题就是 $O(n \log n)$ 求 LIS 的简单变式。

记 $a_i$ 为限速标志序列，我们令 $f_i$ 为以 $a_i$ 结尾的上升子序列的个数，那么 $a_i$ 既可以作为新序列的开头，也可以拼在 $a_j \ (j < i \land a_j < a_i)$ 的后面，则有转移方程：

$$f_i = 1 + \sum_{j < i \land a_j < a_i} f_j$$

这个是 $O(n ^ 2)$ 的，考虑优化。

首先由于我们是按序处理的，因此 $j < i$ 天然满足，那么我们可以考虑一个数据结构，每次转移后将下标为 $a_i$ 的地方增加 $f_i$，那么我们只需将下标为 $1 \sim a_i - 1$ 的地方求和，就是 $\sum_{j < i \land a_j < a_i} f_j$ 的值。

我们需要单点加，前缀查，可以选择树状数组和线段树，这里选用了常数小还好写的树状数组。

注意到 $a_i$ 值域很大，因此需要离散化。

献上巨丑的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...)
#else
#define debug(fmt, ...) fprintf(stderr, "Debug at function %s, line %d: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#endif
#define endl '\n'
#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define rep(i, l, r, ...) for (int i = (l), i##e = (r), ##__VA_ARGS__; i <= i##e; ++i)
#define per(i, r, l, ...) for (int i = (r), i##e = (l), ##__VA_ARGS__; i >= i##e; --i)
#define mst(x, val, len) memset(x, val, sizeof((x)[0]) * (int(len) + 1))
#define mcp(from, to, len) memcpy(to, from, sizeof((to)[0]) * (int(len) + 1))
#define mid (((l) + (r)) >> 1)
#define ls ((x) << 1)
#define rs ((x) << 1 | 1)
#define pbds __gnu_pbds
#define int ll
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
constexpr int MAXN = 5e5 + 10, N = 5e5, inf = 1e9, mod = 1e9 + 7, MAXV = MAXN << 2;
int lowbit(int x) { return x & (-x); }
template <typename T> inline void chkmx(T &a, const T b) { a = a < b ? b : a; }
template <typename T> inline void chkmn(T &a, const T b) { a = a > b ? b : a; }
template <typename T> inline void Add(T &a, const T b) { a = ((a + b) % mod + mod) % mod; }
template <typename T> inline void Mul(T &a, const T b) { a = ((a * b) % mod + mod) % mod; }
template <typename T> inline void add(T &a, const T b) { a = (a + b >= mod ? a + b - mod : a + b); }
template <typename T> inline void mul(T &a, const T b) { a = a * b % mod; }
bool MST;
int n, m, X, Y, Z, A[MAXN], a[MAXN], tr[MAXN], b[MAXN], blen;
void input()
{
    cin >> n >> m >> X >> Y >> Z;
    rep(i, 0, m - 1) cin >> A[i];
    rep(i, 0, n - 1) b[i + 1] = a[i + 1] = A[i % m], A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
}
void upd(int x, int v)
{
    for (; x <= N; x += lowbit(x)) add(tr[x], v);
}
int qry(int x)
{
    static int res;
    for (res = 0; x; x -= lowbit(x)) add(res, tr[x]);
    return res;
}
void solve()
{
    input();
    sort(b + 1, b + 1 + n);
    blen = unique(b + 1, b + 1 + n) - b - 1;
    mst(tr, 0, N);
    rep(i, 1, n)
    {
        a[i] = lower_bound(b + 1, b + 1 + blen, a[i]) - b;
        upd(a[i], qry(a[i] - 1) + 1);
    }
    rep(i, 1, n) debug("a[%lld] = %lld\n", i, a[i]);
    cout << qry(N) << endl;
}
bool MED;
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    debug("Memory Used: %.2lf Mib.\n", (&MST - &MED) / 1024. / 1024.);
    int T;
    cin >> T;
    rep(i, 1, T) cout << "Case #" << i << ": ", solve();
    return 0;
}
```

---

