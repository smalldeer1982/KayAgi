# Cut Substrings

## 题目描述

给出两个非空字符串$s$和$t$，以最小次数删除使得字符串$s$中不会出现字符串$t$，每次可以将字符串$s$中所有任意一个字符串$t$删除，并且有多少种不同的的方案，如：删除序列$\{1,2,3\}$与删除序列$\{1,2,4\}$是不同的，删除序列$\{2,4,6\}$和删除序列$\{2,6\}$也是不同的，但删除序列$\{3,5\}$与删除序列$\{5,3\}$是相同的


现有$q$次询问，每次输出最小删除次数与以最小删除次数删除的方案数(对$10^9+7$取模)

## 说明/提示

第一个测试用例可以在第$3$个位置和第$9$位置删除，也可以在第$3$个位置和第$11$个位置删除，因此最优删除次数为$2$,有两种方案。


第二个测试用例下，只需要删除$4$个能够匹配的字符串任何一个就足够了


第三个测试用例下，字符串$s=\{xyzxyz\}$是两个字符串$t=\{xyz\}$的串联，因此存在 $2$ 个删除的唯一最优序列。


在第四个和第六个测试用例下，字符串 $s$ 不包含字符串 $t$ 。


在第五个测试用例下,字符串 $s$ 恰好为字符串 $t$ 。

## 样例 #1

### 输入

```
8
abababacababa
aba
ddddddd
dddd
xyzxyz
xyz
abc
abcd
abacaba
abaca
abc
def
aaaaaaaa
a
aaaaaaaa
aa```

### 输出

```
2 2
1 4
2 1
0 1
1 1
0 1
8 1
3 6```

# 题解

## 作者：tuxuanming2024 (赞：6)

看到题解好多都用了kmp，这里提供一个 $O(nm^2)$，使用字符串hash可优化至 $O(nm)$ 的方法。

首先，考虑 DP。令 $s$ 长度为 $n$，$t$ 长度为 $m$。设 $f_i$ 表示 $s$ 中以 $i$ 为结尾的前缀不含有子串 $t$ 的最小删除次数，$g_i$ 表示方案数。那么此时有三种情况：

- 情况一：$i<m$。显然删除次数为 $0$，所以 $f_i=0,g_i=1$。

- 情况二：$i \ge m$ 但 $s$ 中 $[i-m+1,i]$ 所构成的子串不等于 $t$。
那么此时 $f_i=f_{i-1},g_i=g_{i-1}$。

- 情况三：$i \ge m$ 且 $s$ 中 $[i-m+1,i]$ 所构成的子串恰好为 $t$。如图所示：

![](https://s1.ax1x.com/2022/11/30/zw8XOs.png)

那么我们就需要使用一次操作破坏这个子串。我们可以直接删除 $[i-m+1,i]$，或者找到一个 $j$ 满足 $i-2m+2 \le j \le i-m+1$ 且 $[j,j+m-1]$ 所构成的子串也恰好等于 $t$，将这个子串删除。如图所示：

![](https://s1.ax1x.com/2022/11/30/zwGf9U.png)

则可以更新答案，即 $f_i=\min_j\{f_{j-1}+1\}$。

那么算出 $f_i$ 后，也可计算 $g_i$：$g_i=\sum_j [f_i=f_{j-1}+1]g_{j-1}$。

答案为 $f_n$ 与 $g_n$。时间复杂度 $O(nm^2)$，使用字符串哈希或其他字符串匹配算法可降至 $O(nm)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=505,mod=1e9+7,p=998244353,q=1e9+9,INF=0x3f3f3f3f;
int n,m,f[N];
string a,b;
ll s[N],ss,pw[N],g[N];
ll Hash(int l,int r) {return (s[r]-s[l-1]*pw[r-l+1]%q+q)%q;}
void solve()
{
	cin>>a>>b;
	n=a.size(),m=b.size();
	a=' '+a,b=' '+b;
	pw[0]=1;
	for(int i=1;i<=n;i++)
	{
		s[i]=(s[i-1]*p%q+(a[i]-'a'+1))%q;
		pw[i]=pw[i-1]*p%q;
	}
	ss=0;
	for(int i=1;i<=m;i++) ss=(ss*p%q+b[i]-'a'+1)%q;
	g[0]=1;
	for(int i=1;i<=n;i++)
	{
		if(i<m) {f[i]=0,g[i]=1; continue;}
		if(Hash(i-m+1,i)!=ss) f[i]=f[i-1],g[i]=g[i-1];
		else
		{
			f[i]=INF;
			for(int j=max(1,i-2*m+2);j<=i-m+1;j++)
				if(Hash(j,j+m-1)==ss) f[i]=min(f[i],f[j-1]+1);
			g[i]=0;
			for(int j=max(1,i-2*m+2);j<=i-m+1;j++)
				if(Hash(j,j+m-1)==ss&&f[j-1]+1==f[i]) g[i]=(g[i]+g[j-1])%mod;
		}
	}
	cout<<f[n]<<" "<<g[n]<<'\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```


---

## 作者：Leasier (赞：6)

前置芝士：[KMP](https://oi-wiki.org/string/kmp/)

首先可以用 KMP 抓出 $t$ 在 $s$ 中所有出现的位置 $pos_1, pos_2, \cdots, pos_k$。

当 $k = 0$，答案显然为 `0 1`。

否则考虑 dp。这里先不考虑求方案数，反正也差不多。

设 $dp_i$ 表示让 $pos_1 \sim pos_i$ 都消失的最小删除次数。

初值：$dp_0 = 0$。

转移：现在我们希望让一个 $i$ 转移到 $j > i$，有 $dp_j \leftarrow \min(dp_j, dp_i + 1)$。

那什么样的 $j$ 满足条件呢？

- $pos_j > pos_i + m - 1$，因为 $i, j$ 必须无交。
- 设第一个满足 $pos_j > pos_i + m - 1$ 的 $j$ 为 $j_0$，则 $pos_j \leq pos_{j_0} + m - 1$，因为你不能跳过 $j_0$。

直接转移即可。时间复杂度为 $O(\sum n^2)$。

代码：
```cpp
#include <stdio.h>
#include <string.h>

const int mod = 1e9 + 7;
int fail[507], pos[507], dp2[507], dp1[507];
char s[507], t[507];
bool vis[507];

inline int kmp(int n, int m){
	int ans = 0;
	for (register int i = 2, j = 0; i <= m; i++){
		while (j >= 1 && t[i] != t[j + 1]) j = fail[j];
		if (t[i] == t[j + 1]) j++;
		fail[i] = j;
	}
	for (register int i = 1, j = 0; i <= n; i++){
		while (j >= 1 && s[i] != t[j + 1]) j = fail[j];
		if (s[i] == t[j + 1]) j++;
		if (j == m){
			pos[++ans] = i - m + 1;
			j = fail[j];
		}
	}
	return ans;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){
	int q;
	scanf("%d", &q);
	for (register int i = 1; i <= q; i++){
		int n, m, k;
		scanf("%s", &s[1]);
		n = strlen(&s[1]);
		scanf("%s", &t[1]);
		m = strlen(&t[1]);
		k = kmp(n, m);
		if (k == 0){
			printf("0 1\n");
			continue;
		}
		int ans1 = 0x7fffffff, ans2 = 0;
		dp2[0] = 1;
		for (register int j = 1; j <= k; j++){
			dp1[j] = 2e9;
		}
		for (register int j = 0; j < k; j++){
			if (j == 0){
				for (register int x = 1; x <= k && pos[x] <= pos[1] + m - 1; x++){
					if (dp1[x] > dp1[j] + 1){
						dp1[x] = dp1[j] + 1;
						dp2[x] = dp2[j];
					} else if (dp1[x] == dp1[j] + 1){
						dp2[x] = (dp2[x] + dp2[j]) % mod;
					}
				}
			} else {
				int x = j + 1, y;
				while (x <= k && pos[x] <= pos[j] + m - 1) x++;
				y = x;
				while (y <= k && pos[y] <= pos[x] + m - 1){
					if (dp1[y] > dp1[j] + 1){
						dp1[y] = dp1[j] + 1;
						dp2[y] = dp2[j];
					} else if (dp1[y] == dp1[j] + 1){
						dp2[y] = (dp2[y] + dp2[j]) % mod;
					}
					y++;
				}
			}
		}
		for (register int j = k; j >= 1 && pos[j] + m - 1 >= pos[k]; j--){
			if (ans1 > dp1[j]){
				ans1 = dp1[j];
				ans2 = dp2[j];
			} else if (ans1 == dp1[j]){
				ans2 = (ans2 + dp2[j]) % mod;
			}
		}
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}
```

---

## 作者：Sellaris (赞：5)

- 很呆很显然，但是为什么没人这样写，难道真的是因为太呆了吗？

- 容易想到动态规划，于是开始设状态。令 $dp_{i,j,k}$ 表示 $s$ 串中前 $i$ 个，删了 $j$ 个的方案数，$k \in [0,1]$ 表示第 $i$ 个是原串中不删或删的某次的终点。

- 于是转移就出来了，令 $v_i$ 表示 $s_{i-m+1}$ 到 $s_{i}$ 这段是否等于 $t$ ，即这个位置是否是一次目标串在原串中的出现终点，我们有：

$$dp_{0,0,0}=1$$

$$ dp_{i,j,1}=\begin{cases}

dp_{i-m,j-1,1}+dp_{i-m,j-1,0} & j>0 & and & v[i]=1\\

\end{cases}$$

$$ dp_{i,j,0}=\begin{cases}
dp_{i-1,j,0}+dp_{i-1,j,1} & v[i]=0\\
\sum_{k=i-n+1}^{i-1} dp_{k,j,1} & v[i]=1\\

\end{cases}$$

答案就是 $i$ 和 $dp_{n,i,1}+dp_{n,i,0}$，其中 $i \in [1,m]$ 是满足 $\forall j \in[1,i-1]$， $dp_{n,j,0}=dp_{n,j,1}=0$ 且 $dp_{n,i,0} + dp_{n,i,1} >0$ 的最小整数。

这样我们就会 $O(n^2m)$ 了，直接就能过，跑得飞快，实测只跑了 $15ms$。

滚一下数组和前缀和就是时间 $O(n^2)$，空间 $O(n)$ 了。

- *2100 ？ *800 ！

---

## 作者：MortisM (赞：4)

> [CF1729G Cut Substrings](https://codeforces.com/contest/1729/problem/G)

一道挺棒难度的 Div.3 G，思路不是特别难，但需要冷静思考，像我这种场上摆烂的就被区分掉了。

考虑到这个数据范围特别小，你肯定随便匹配一下所有 $t$ 在 $s$ 中出现的位置就行了，不一定要用 KMP 匹配，暴力匹配就是 $O(n^2)$ 的，但好像有个老哥场上 9min 切掉而且用的 KMP，感觉有点强的。

然后下面你就想你每个匹配的串都代表一个区间 $[l_i,r_i]$，这个区间之间互相勾连在一起。这时候你就想到 DP，用一个 pair 表示到第 $i$ 位的最小步数和在保证最小步数的情况下所用的时间。

DP 的过程需要分析，如果直接上来就撸可能就会炸，要钦定一个顺序比较舒适，大概就是一个只能转移到紧接着的下一个，然后就没啥了。这样时间复杂度就是 $O(n^2)$ 而且炒鸡好写。

**总结：** 冷静分析，不要摆烂（

**Code:**

```cpp
#include<bits/stdc++.h>
#define F first
#define S second
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define sz(x) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define srt(x) sort(all(x))
#define rsrt(x) sort(rall(x))
#define lwb lower_bound
#define upb upper_bound
#define getp(x,v) lwb(all(x),v)-(x).begin()
#define Getp(x,v) upb(all(x),v)-(x).begin()
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
#define mod 998244353
#define MOD 1000000007
#define N 510
using namespace std;
int n,m;
string s,t;
bool f[N];
pii dp[N];
int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		cin>>s>>t;
		n=sz(s);
		m=sz(t);
		memset(f,0,sizeof(f));
		for(int i=0;i+m<=n;i++)
		{
			if(s.substr(i,m)==t)
			{
				f[i]=1;
			}
		}
		dp[0]=make_pair(0,1);
		for(int i=1;i<=n;i++)
		{
			dp[i]=make_pair(n+1,0);
		}
		for(int i=0;i<n;i++)
		{
			for(int j=i;j<=n;j++)
			{
				if(j-i>=m&&f[j-m])
				{
					break;
				}
				if(f[j])
				{
					if(dp[i].F+1<dp[j+m].F)
					{
						dp[j+m]=make_pair(dp[i].F+1,dp[i].S);
					}
					else if(dp[i].F+1==dp[j+m].F)
					{
						dp[j+m].S+=dp[i].S;
						dp[j+m].S%=MOD;
					}
				}
			}
		}
		int lst=0;
		for(int i=n-1;i>=0;i--)
		{
			if(f[i])
			{
				lst=i+1;
				break;
			}
		}
		pii ans=make_pair(n+1,0);
		for(int i=lst;i<=n;i++)
		{
			if(dp[i].F<ans.F)
			{
				ans=dp[i];
			}
			else if(dp[i].F==ans.F)
			{
				ans.S+=dp[i].S;
				ans.S%=MOD;
			}
		}
		if(ans.F>n)
		{
			ans=make_pair(-1,-1);
		}
		cout<<ans.F<<" "<<ans.S<<endl;
	}
	return 0;
}
```

---

## 作者：haochengw920 (赞：2)

这里给一个 $O(n\log n)$ 的解法。

先跑 KMP，得到 $T$ 在 $S$ 的出现位置为 $\{pos\}$。

令 $dp_i$ 为消除 $pos_j \forall j\in[1,i]$ 的最小代价，容易发现转移位置是一段区间的（如果不理解可以看看其它 $O(n^2)$ 的题解）。

于是二分找到转移点，线段树维护即可。

```cpp
#include<cstdio>
#include<cstring>
#include<utility>
#include<algorithm>
#define fir first
#define sec second
#define mkp make_pair
#define int long long
#define Mod (1000000007)
#define Pii pair<int, int>
#define INF (0x3f3f3f3f3f3f3f3f) 
#define rep(i, l, r) for(int i(l); i <= (r); ++ i) 
#define per(i, r, l) for(int i(r); i >= (l); -- i) 
using namespace std;

const int N = 505;

int T, n, m;
int tot, p[N];

char s[N], t[N];
int fail[N], r[N];
void Prew() {
	int j = 0;
	rep(i, 2, m) {
		while (j && t[j + 1] != t[i]) 
			j = fail[j];
		if (t[j + 1] == t[i]) ++ j;
		fail[i] = j;
	} j = 0;
	rep(i, 1, n) {
		while (j && s[i] != t[j + 1]) 
			j = fail[j];
		if (s[i] == t[j + 1]) ++ j;
		if (j == m) p[++ tot] = i, j = fail[j];
	}
	j = 1; p[tot + 1] = INF;
	rep(i, 1, tot) {
		while (p[j] <= p[i] + m - 1) 
			++ j; r[i] = p[j];
	}
}

Pii Merge(Pii x, Pii y) {
	if (x.fir ^ y.fir) return min(x, y);
	return mkp(x.fir, (x.sec + y.sec) % Mod);
}
class Segment_tree {
	#define lc (u << 1)
	#define rc (u << 1 | 1)
	public : 
	Pii tr[N << 2];
	inline void push_up(int u) {
		tr[u] = Merge(tr[lc], tr[rc]);
	}
	public : 
	void Build(int u = 1, int l = 1, int r = tot) {
		if (l == r) {
			tr[u] = mkp(INF, 0);
			return;
		} int mid = (l + r) >> 1;
		Build(lc, l, mid); 
		Build(rc, mid + 1, r);
		push_up(u);
	} 
	void Modify(int p, Pii x, int u = 1, int l = 1, int r = tot) {
		if (l == r) return tr[u] = x, void();
		int mid = (l + r) >> 1; 
		if (p <= mid) Modify(p, x, lc, l, mid);
		else Modify(p, x, rc, mid + 1, r);
		push_up(u);
	}
	Pii Query(int bg, int nd, int u = 1, int l = 1, int r = tot) {
		if (bg <= l && r <= nd) return tr[u];
		int mid = (l + r) >> 1; Pii res = mkp(INF, 0);
		if (bg <= mid) res = Merge(res, Query(bg, nd, lc, l, mid));
		if (nd > mid) res = Merge(res, Query(bg, nd, rc, mid + 1, r));
		return res;
	} 
	#undef lc
	#undef rc
}st;
Pii ans, dp[N];
void DP() {
	dp[1] = mkp(0, 1);
	st.Build(); st.Modify(1, dp[1]);
	rep(i, 2, tot) {
		int nd = lower_bound(p + 1, p + tot + 1, p[i] - m + 1) - p - 1;
		int bg = lower_bound(r + 1, r + nd + 1, p[i] - m + 1) - r;
		dp[i] = st.Query(bg, nd); ++ dp[i].fir; st.Modify(i, dp[i]);
	} ans = mkp(INF, 0);
	for (int i = tot; i && p[i] + m - 1 >= p[tot]; -- i) 
		ans = Merge(ans, dp[i]);
}
void Solve() {
	p[tot = 1] = -INF;
	scanf ("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	Prew(); DP(); 
	printf ("%lld %lld\n", ans.fir, ans.sec);
}

signed main()
{
	scanf ("%lld", &T);
	while (T --) Solve();
	return 0;
}
```

---

## 作者：xiazha (赞：2)

首先注意一个点：删除完一个 $t$ 后新串不用拼接，即空出来删除的这一段。

进入正题，显然这是一个动规题，我们定义 $dp_{i,j,0/1}$ 为操作到了第 $i$ 个字符，目前删除了 $j$ 个 $t$，是否为删除一个 $t$ 的区间终点。

为了状态转移方便，我们预处理一个 $f_i$ 表示 $s_{i-m+1 \sim i}$ 是否与 $t$ 相等。

下面上方程：

- $dp_{i,j,1}=dp_{i-m,j-1,0}+dp_{i-m,j-1,1}$，注意这里需要满足 $j>0$ 且 $f_i =1$。

- 若 $f_i=0$，$dp_{i,j,0}=dp_{i-1,j,0}+dp_{i-1,j,1}$

- 若 $f_i=1$，这里需要解释以下，因为最终 $s$ 中不能有 $t$，所以一定至少要删除 $i-m+1\sim i$ 中其中一个字符，而 $i$ 又不能删，所以 $dp_{i,j,0}=\sum_{k=i-m+1}^{i-1} dp_{k,j,1}$。

注意到 $j$ 的范围实际上是 $0\sim \lfloor \frac{n}{m}\rfloor$ 的，所以时间复杂度为 $O(n^2)$ 的，显然可以很快的跑过，十分优秀。

---

## 作者：_edge_ (赞：2)

### 题意

给定一个字符串 $s$，再给定一个字符串 $t$。

每次可以从 $s$ 里面找出 $t$ 然后删掉，求最少删的次数使得 $s$ 没有 $t$。

注意！这里 $s$ 删除之后不会合并。。。。

也就是说比如 `ababcc` 那么我删除 `abc` 之后就可以把中间踢掉了。

然后就变成了 `ab...c`，而这个串不含有 `abc`。

### 思路

其实看到这种最小化问题就是很容易想到 DP，这东西贪也贪不好把。

那么我们常见的套路就是设 $f_{i}$ 表示以 $i$ 为结尾的字符串，他们最少用多少次删除操作。

然后仔细一想，这东西咋维护他没有出现过 $t$ 呀！

所以我们稍微对状态修改，设 $f_{i,j}$ 表示到第 $i$ 位，当前匹配 $t$ 已经匹配到了第 $j$ 位。

那么非常非常简单的转移，就是枚举后面那个断点 $l$，然后 $f_{l,p}=f_{i,j}+solve(i+1,l-1)$，$solve$ 是啥先不管，我们来考虑 $p$ 怎么求，相当于是后面加一个字符然后匹配，这东西不就是 KMP 的套路么。

于是我们把 KMP 建出来，然后加个字符往后跳就可以了。

然后考虑这个 $solve$ 咋写，很简单就是看他是否是 $t$ 字符串组成的。

我这里写的非常非常冗余，写了个区间 DP，这东西适用字符串能合并的时候。

然后我们就很愉快的用 $O(n^3)$ 的复杂度做完了。

注意这里对删的顺序没有要求，所以区间 DP 不用记录那个方案数。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=505;
const int Mod=1e9+7;
string s1,s2;
int f[INF][INF],g[INF][INF],f1[INF][INF],f2[INF][INF],kmp[INF];
int DFS(int l,int r) {
//	cout<<l<<" "<<r<<" over?\n";
	if (l>r) return g[l][r]=1;
	if (~f[l][r]) return f[l][r];
	if (r-l+1<s2.size()-1) return f[l][r]=0;
	if (r-l+1==s2.size()-1) {
		for (int i=l;i<=r;i++)
			if (s2[i-l+1]==s1[i]) ;
			else return f[l][r]=0;
		return f[l][r]=g[l][r]=1;
	}
//	else return 0; 
	f[l][r]=0;
	for (int i=l;i<r;i++) {
		int xx=DFS(l,i)&DFS(i+1,r);
		f[l][r]|=xx;
		if (xx==1) 
			g[l][r]+=g[l][i-1]*g[i+1][r]%Mod,g[l][r]%=Mod;
	}
//	cout<<l<<" "<<r<<" "<<f[l][r]<<" qwq\n";
//	int L=l,R=r;
//	while (s2[L-l+1]==s1[L] && L<=r) L++;L--;
//	while (s2[R-l+1]==s1[R] && R>=l) R--;R++;
//	
//	for (int i=l;i<=L;i++) {
//		int xx=r-(s2.size()-(i-l+1))+1;
//		if (xx<R) continue;
//		int yy=DFS(i+1,xx-1);
//		f[l][r]|=yy;
//		if (yy==1) 
//			g[l][r]+=g[i+1][xx-1]%Mod,g[l][r]%=Mod;
//	}
//	cout<<l<<" "<<r<<" "<<f[l][r]<<" "<<g[l][r]<<" fadfad\n";
	return f[l][r];
}
void solve() {
	memset(f,255,sizeof f);
	memset(f1,63,sizeof f1);
	memset(f2,0,sizeof f2); 
	cin>>s1>>s2;
	int len=s1.size();
	s1=" "+s1;
	int j=0,len2=s2.size();
	s2=" "+s2;
	for (int i=1;i<=len2;i++) kmp[i]=0;
	for (int i=2;i<=len2;i++) {
		while (j && s2[j+1]!=s2[i]) j=kmp[j];
		if (s2[j+1]==s2[i]) kmp[i]=++j;
	}
	f1[0][0]=0;f2[0][0]=1;
	for (int i=0;i<len;i++) {
		for (int j=0;j<len2;j++) {
//			cout<<i<<" "<<j<<" "<<f1[i][j]<<" "<<f2[i][j]<<" "<<DFS(2,3)<<" over?\n";
			for (int l=i+1;l<=len+1;l++) {
				if (DFS(i+1,l-1)) {
					int k=j;
					while (k && s2[k+1]!=s1[l]) k=kmp[k];
//					cout<<i<<" "<<l<<" keklek\n";
					if (s2[k+1]==s1[l]) k++;
					if (l==i+1) ;
					else {
						k=0;
						if (s2[k+1]==s1[l]) k++;
					}
//					cout<<i<<" "<<l<<" "<<k<<" awejrijw\n";
					if (f1[l][k]>f1[i][j]+(l-1-(i+1)+1)/(s2.size()-1)) {
						f1[l][k]=f1[i][j]+(l-1-(i+1)+1)/(s2.size()-1);
						f2[l][k]=f2[i][j];
					}
					else if (f1[l][k]==f1[i][j]+(l-1-(i+1)+1)/(s2.size()-1)) {
						f2[l][k]+=f2[i][j];
						f2[l][k]%=Mod;
					}
				}
			}
		}
//		for (int j=1;j<=i;j++) {
//			if (DFS(j,i)) {
//				f1[i]=f1[j-1]+(i-j+1)/s2.size();
//				f2[i]=f2[j-1]*g[j][i];f2[i]%=Mod;
////				cout<<i<<" "<<f1[i]<<" "<<j-1<<" kelkelkel\n";
//				break;
//			}
//		}
	}
//	cout<<f1[len]<<" "<<f2[len]<<"\n";
	int ans=1e18,ans1=0;
	for (int j=0;j<len2;j++)
		if (ans>f1[len][j]) ans=f1[len][j],ans1=f2[len][j];
		else if (ans==f1[len][j]) ans1+=f2[len][j],ans1%=Mod;
	for (int j=0;j<len2;j++)
		if (ans>f1[len+1][j]) ans=f1[len+1][j],ans1=f2[len+1][j];
		else if (ans==f1[len+1][j]) ans1+=f2[len+1][j],ans1%=Mod;
	cout<<ans<<" "<<ans1<<"\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	int t=0;cin>>t;
	while (t--) solve();
	return 0;
}
```


---

## 作者：BigSmall_En (赞：1)

### [CF1729G](https://codeforces.com/problemset/problem/1729/G) Cut Substrings

> 给出两个字符串 $s,t$，每次可以将字符串 $s$ 中任意一个为 $t$ 的子串删除，删除位置的字符变为空格（或理解为无实义）。求最少删除几次可以使得字符串 $s$ 中不会出现字符串 $t$，以及在这个最小次数下的方案数。$1\leq |s|,|t|\leq 500$。

给出一种与官方题解相同的做法。

#### 题解

首先可以先用字符串匹配算法算出 $s$ 中每个与 $t$ 相同的子串的出现位置 $pos$，记第 $i$ 次出现的位置为 $pos_i$。

定义 $f_i,dp_i$ 分别为删除以原字符串 $pos_i$ 下标开始的与 $t$ 相同的子串后，使得**原**字符串 ${1\sim pos_i}$ 下标范围内对应新字符串中不存在 $t$ 子串的最小操作数和方案数。

假设删除 $pos_i$ 开始的一个子串后，存在一个 $j>i$，使得原字符串下标 $pos_i\sim pos_j-1$ 范围内对应的新的字符串中不存在一个 $t$。那么可以得到转移。
$$
\begin{aligned}
f_j&\gets f_i+1\\
dp_j&\gets
\begin{cases}\begin{aligned}
dp_i &\quad f_i\neq  f_i+1\\
dp_i+dp_j&\quad f_j=f_i+1
\end{aligned}\end{cases}
\end{aligned}
$$

#### 实现

假设 $pos$ 位置一共有 $tot$ 个，容易发现 $pos_{tot}$ 开始的子串不一定要被删除。所以我们建立一个必须被删除的无实义节点 $pos_{tot+1}=n+m$。最后输出 $f_{tot}-1$ 和 $dp_{tot}$。

现在的问题是找到满足条件的 $j$。

容易发现删除 $pos_i$ 开始的子串后，$\forall pos_k\leq pos_{i}+|t|-1$ 均不会作为一个完整的 $t$ 出现在目前 $s$ 中。找到最小的 $l$，使得 $pos_l>pos_i+|t|-1$，那么 $pos_l\leq pos_j\leq pos_l+|t|-1$，才能使得 $pos_l$ 开始的子串不再出现。

其他细节具体见代码，时间复杂度 $O(n^2)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;
typedef pair<int,int>ttfa;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
const ll MOD=1000000007;
const int N=503;
char s[N],t[N];
int n,m,f[N],pos[N],tot;
ll dp[N];
inline void Tesc(){
	memset(f,0x3f,sizeof(f));
	memset(dp,0,sizeof(dp));
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1),tot=0;
	for(int i=1;i+m-1<=n;++i){
		bool flag=1;
		for(int j=1;j<=m;++j)
			if(s[i+j-1]!=t[j])
				{flag=0;break;}
		if(flag)pos[++tot]=i;
	}
	f[0]=0,dp[0]=1;pos[0]=-114514,pos[++tot]=n+m;
	for(int i=0;i<tot;++i){
		int loc=i+1;
		while(loc<=tot&&pos[loc]<=pos[i]+m-1)++loc;
		for(int j=loc;j<=tot&&pos[j]<=pos[loc]+m-1;++j){
			if(f[i]+1<f[j]){
				f[j]=f[i]+1;
				dp[j]=dp[i];
			}else if(f[i]+1==f[j])dp[j]=(dp[j]+dp[i])%MOD;
		}
	}
	printf("%d %lld\n",f[tot]-1,dp[tot]);
}
int main(){
	int T=read();
	while(T--)Tesc();
	return 0;
}
```



---

