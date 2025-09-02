# [ARC158E] All Pair Shortest Paths

## 题目描述

有一个 $2$ 行 $N$ 列的网格。我们用 $(i,j)$ 表示从上往下第 $i$ 行、从左往右第 $j$ 列的格子。在 $(i,j)$ 这个格子上写有正整数 $x_{i,j}$。

如果两个格子有公共边，则称它们**相邻**。

从格子 $X$ 到格子 $Y$ 的**路径**，是指由若干互不相同的格子组成的序列 $(P_1,\ \ldots,\ P_n)$，满足 $P_1 = X$，$P_n = Y$，并且对于任意 $1 \leq i \leq n-1$，$P_i$ 和 $P_{i+1}$ 相邻。该路径的**权值**定义为 $P_1,\ldots,P_n$ 上所写整数的总和。

对于任意两个格子 $X,\ Y$，记 $f(X,\ Y)$ 为从 $X$ 到 $Y$ 的所有路径中权值的最小值。

请你求出所有格子对 $(X,Y)$ 的 $f(X,\ Y)$ 之和，并对 $998244353$ 取模。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq x_{i,j} \leq 10^9$

## 样例解释 1

需要计算以下 $4$ 种情况的总和：

- $X = (1,1), Y = (1,1)$ 时：$f(X,Y) = 3$。
- $X = (1,1), Y = (2,1)$ 时：$f(X,Y) = 8$。
- $X = (2,1), Y = (1,1)$ 时：$f(X,Y) = 8$。
- $X = (2,1), Y = (2,1)$ 时：$f(X,Y) = 5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
3
5```

### 输出

```
24```

## 样例 #2

### 输入

```
2
1 2
3 4```

### 输出

```
76```

## 样例 #3

### 输入

```
5
1 1000000000 1 1 1
1 1 1 1000000000 1```

### 输出

```
66714886```

# 题解

## 作者：Tony2 (赞：4)

考虑扫描线。左端点从右到左枚举，对于所有 $(i,1/2)$ 满足 $i\ge l$ 的格子，记录下这个格子分别到 $(l,1)$ 和 $(l,2)$ 的最短路。

设这两个值在 $l+1$ 分别是 $p_1,p_2$，扫描到 $l$ 时为 $q_1,q_2$，能得出转移式子为 $q_1=\min(p_1,p_2+b_l)+a_l,q_2=\min(p_1+a_l,p_2)+b_l$。

能发现 $q_1$ 被 $p_2+b_l$ 转移的条件为 $p_2+b_l<p_1$ 即 $p_1-p_2>b_l$，同样的 $q_2$ 被 $p_1+a_l$ 转移的条件为 $p_1-p_2<-a_l$。扫描线时把在 $l$ 右侧所有的格子按照 $p_1-p_2$ 排序，先对于所有 $p_1$ 加 $a_l$，对于所有 $p_2$ 加 $b_l$，再暴力修改上述讨论的两种情况的格子，能发现是一个前缀和一个后缀，暴力查暴力修改，单次修改会让 $p_1-p_2$ 不同的格子的数量减少 $1$，所以修改总复杂度为 $\Theta(n\log n)$。

全体加用两个变量存标记即可。注意取模，不取模会爆 long long。

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define mod 998244353
using namespace std;
const int N = 2e5 + 5;
int n, a[N], b[N];
ll taga, tagb, sa, sb, ans;
struct node{
	ll d, suma, sumb;//a - b
	int sz;
	node() : d(0) {}
	node(ll d) : d(d) {}
	node(ll d, ll suma, ll sumb, int sz) : d(d), suma(suma), sumb(sumb), sz(sz) {}
	friend bool operator < (const node &a, const node &b){
		return a.d < b.d;
	}
};
set<node> st;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = n; i >= 1; i--){
		taga += a[i];
		tagb += b[i];
		auto insert = [&](ll aa, ll bb){
			aa -= taga;
			bb -= tagb;
			set<node>::iterator it = st.lower_bound(node(aa - bb));
			if (it != st.end() && it -> d == aa - bb){
				node nd = *it;
				nd.sz++;
				nd.suma = (nd.suma + aa) % mod;
				nd.sumb = (nd.sumb + bb) % mod;
				st.erase(it);
				st.insert(nd);
			}else
				st.insert(node(aa - bb, aa, bb, 1));
			sa = (sa + aa) % mod;
			sb = (sb + bb) % mod;
		};
		insert(a[i], a[i] + b[i]);
		insert(a[i] + b[i], b[i]);
		{
			node nd;
			nd.d = a[i] - (taga - tagb);
			nd.suma = nd.sumb = 0;
			nd.sz = 0;
			while (!st.empty() && prev(st.end()) -> d >= nd.d){
				set<node>::iterator it = prev(st.end());
				nd.sumb = (nd.sumb + it -> sumb) % mod;
				nd.sz += it -> sz;
				sa = (sa - it -> suma) % mod;
				sb = (sb - it -> sumb) % mod;
				st.erase(it);
			}
			nd.suma = (nd.sumb + nd.d % mod * nd.sz) % mod;
			sa = (sa + nd.suma) % mod;
			sb = (sb + nd.sumb) % mod;
			if (nd.sz)
				st.insert(nd);
		}
		{
			node nd;
			nd.d = -b[i] - (taga - tagb);
			nd.suma = nd.sumb = 0;
			nd.sz = 0;
			while (!st.empty() && st.begin() -> d <= nd.d){
				set<node>::iterator it = st.begin();
				nd.suma = (nd.suma + it -> suma) % mod;
				nd.sz += it -> sz;
				sa = (sa - it -> suma) % mod;
				sb = (sb - it -> sumb) % mod;
				st.erase(it);
			}
			nd.sumb = (nd.suma - nd.d % mod * nd.sz) % mod;
			sa = (sa + nd.suma) % mod;
			sb = (sb + nd.sumb) % mod;
			if (nd.sz)
				st.insert(nd);
		}
		ans = (ans + sa + taga % mod * 2 * (n - i + 1) + sb + tagb % mod * 2 * (n - i + 1)) % mod;
	}
	for (int i = 1; i <= n; i++)
		ans = (ans - (a[i] + b[i])) % mod;
	ans = 1ll * ans * 2 % mod;
	for (int i = 1; i <= n; i++)
		ans = (ans - a[i] - b[i]) % mod;
	cout << (ans + mod) % mod;
	return 0; 
}
```

---

## 作者：TernaryTree (赞：3)

一眼分治，不就是一个 P7482+CF413E 二合一吗！感觉挺套路的。

每次取一个中点 $mid$，对于两端点都在 $[l,mid]$ 或 $[mid+1,r]$ 的情况就递归下去做咯。那么此时就处理左端点在 $[l,mid]$，右端点在 $[mid+1,r]$ 的格子最短路之和。

那么处理出 $f_{i,j}$ 表示 $(i,j)$ 到中点上面的最短路，当 $i\le mid$ 时是到 $(mid,0)$ 的最短路，否则是到 $(mid+1,0)$ 的最短路。$g_{i,j}$ 同理表示到中点下面的最短路。这个可以递推。

然后两个点 $(i,p)$ 和 $(j,q)$ 的最短路就是 $\min(f_{i,p}+f_{j,q},g_{i,p}+g_{j,q})$。

接下来推式子。

$$
\begin{aligned}
&\sum_{i=l}^{mid}
\sum_{j=mid+1}^r 
\sum_{p=0}^1
\sum_{q=0}^1 
\min(f_{i,p}+f_{j,q},g_{i,p}+g_{j,q})
\\
=&\sum_{i=l}^{mid}
\sum_{j=mid+1}^r 
\sum_{p=0}^1
\sum_{q=0}^1 
\min(f_{i,p}-g_{i,p}+f_{j,q}-g_{j,q},0)+g_{i,p}+g_{j,q}
\\
=&\sum_{i=l}^{mid}
\sum_{j=mid+1}^r 
\sum_{p=0}^1
\sum_{q=0}^1 
\min(f_{i,p}-g_{i,p}+f_{j,q}-g_{j,q},0)
+
2(r-mid)
\sum_{i=l}^{mid}
\sum_{p=0}^1
g_{i,p}
+
2(mid-l+1)
\sum_{j=mid+1}^r 
\sum_{q=0}^1 
g_{j,q}
\\
\end{aligned}
$$

后面那坨直接算。现在看前面那坨。记 $h_{i,j}=f_{i,j}-g_{i,j}$。

$$
\begin{aligned}
=&\sum_{i=l}^{mid}
\sum_{j=mid+1}^r 
\sum_{p=0}^1
\sum_{q=0}^1 
\min(h_{i,p}+h_{j,q},0)
\\
=&\sum_{i=l}^{mid}
\sum_{j=mid+1}^r 
\sum_{p=0}^1
\sum_{q=0}^1 
h_{i,p}+h_{j,q}[h_{j,q}<-h_{i,p}]
\\
\end{aligned}
$$

于是就可以把右边的 $h$ 值全扔到一个桶里边排序再做一下前缀和，枚举左边的格子再二分找出 $h_{j,q}<-h_{i,p}$ 的个数以及 $\sum h_{j,q}$ 即可。

记得处理横坐标相等的情况。

时间复杂度 $T(n)=2T\left(\dfrac n2\right)+\Theta(n\log n)=\Theta(n\log ^2 n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int mod = 998244353;

int n, ans, res;
int a[maxn][2];
int f[maxn][2], g[maxn][2], h[maxn][2];
int b[maxn], s[maxn], cnt;

void solve(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	f[mid][0] = a[mid][0];
	f[mid][1] = a[mid][0] + a[mid][1];
	for (int i = mid - 1; i >= l; i--) 
		f[i][0] = min(f[i + 1][0], f[i + 1][1] + a[i][1]) + a[i][0],
		f[i][1] = min(f[i + 1][1], f[i + 1][0] + a[i][0]) + a[i][1];
	f[mid + 1][0] = a[mid + 1][0];
	f[mid + 1][1] = a[mid + 1][0] + a[mid + 1][1];
	for (int i = mid + 2; i <= r; i++) 
		f[i][0] = min(f[i - 1][0], f[i - 1][1] + a[i][1]) + a[i][0],
		f[i][1] = min(f[i - 1][1], f[i - 1][0] + a[i][0]) + a[i][1];
	g[mid][0] = a[mid][0] + a[mid][1];
	g[mid][1] = a[mid][1];
	for (int i = mid - 1; i >= l; i--) 
		g[i][0] = min(g[i + 1][0], g[i + 1][1] + a[i][1]) + a[i][0],
		g[i][1] = min(g[i + 1][1], g[i + 1][0] + a[i][0]) + a[i][1];
	g[mid + 1][0] = a[mid + 1][0] + a[mid + 1][1];
	g[mid + 1][1] = a[mid + 1][1];
	for (int i = mid + 2; i <= r; i++) 
		g[i][0] = min(g[i - 1][0], g[i - 1][1] + a[i][1]) + a[i][0],
		g[i][1] = min(g[i - 1][1], g[i - 1][0] + a[i][0]) + a[i][1];
	for (int i = l; i <= r; i++) 
		h[i][0] = f[i][0] - g[i][0],
		h[i][1] = f[i][1] - g[i][1];
	int suml = 0, sumr = 0;
	for (int i = l; i <= mid; i++) 
		(suml += g[i][0] + g[i][1]) %= mod;
	for (int i = mid + 1; i <= r; i++) 
		(sumr += g[i][0] + g[i][1]) %= mod;
	(res += suml * (r - mid) % mod * 2 % mod + sumr * (mid - l + 1) % mod * 2 % mod) %= mod;
	cnt = 0;
	for (int i = mid + 1; i <= r; i++) 
		b[++cnt] = h[i][0], b[++cnt] = h[i][1];
	sort(b + 1, b + 1 + cnt);
	s[1] = (b[1] % mod + mod) % mod;
	for (int i = 2; i <= cnt; i++) s[i] = (s[i - 1] + (b[i] % mod + mod) % mod) % mod;
	for (int i = l; i <= mid; i++) {
		for (int p = 0; p <= 1; p++) {
			int k = lower_bound(b + 1, b + 1 + cnt, -h[i][p]) - b - 1;
			(res += ((h[i][p] % mod + mod) % mod * k % mod + s[k]) % mod) %= mod;
		}
	}
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i][0], (ans += a[i][0]) %= mod;
	for (int i = 1; i <= n; i++) cin >> a[i][1], (ans += a[i][1]) %= mod;
	solve(1, n);
	cout << (ans * 3 + res * 2) % mod << endl;
	return 0;
}

```

---

## 作者：_ZSR_ (赞：1)

### [[ARC158E] All Pair Shortest Paths](https://www.luogu.com.cn/problem/AT_arc158_e)

因为只有两行，所以有一个很显然的性质：不可能往回走。那么路径上的节点的列数是单调不降的。考虑第 $l$ 到第 $r$ 列间的格子的贡献。我们可以把贡献分为三部分计算。假设中间节点的列数为 $mid$，那么 $[l,r]$ 的总贡献就是 $[l,mid]$ 的贡献加上 $[mid+1,r]$ 的贡献以及跨区间的贡献。前面两个直接递归求解，考虑跨区间的贡献。

令 $a_{i,j}$ 表示格子 $(i,j)$ 到第一行的某个点的路径长度，$b_{i,j}$ 表示格子 $(i,j)$ 到第二行的某个点的路径长度。然后考虑怎么转移。为了方便，我们令第一行的格子上的值为 $x_i$，第二行为 $y_i$。先转移 $[l,mid]$。令 $a_{0,mid}=x_{mid},a_{1,mid}=x_{mid}+y_{mid}$。很明显，这时的那个未知的点是 $(0,mid)$。并且令 $b_{0,mid}=x_{mid}+y_{mid},b_{1,mid}=y_{mid}$，同理，那个点是 $(1,mid)$。然后从 $mid-1$ 到 $l$ 遍历，转移方程就不多说，比较简单，如果不会的话可以看代码。这样处理完后我们就知道了左区间每个点到 $(0,mid)$ 和 $(1,mid)$ 的最短路径。同理，我们也处理出右区间每个点到 $(0,mid+1)$ 和 $(1,mid+1)$ 的最短路径。答案可能有两种情况，一种是在第一行连接起来，一种是在第二行连接起来。假设 $X$ 是左区间的格子，$Y$ 是右区间的格子，当 $b_X+b_Y \leq a_X+a_Y$ 的时候，答案会加上两倍的 $b_X+b_Y$，因为是无序对，所以要乘二。

考虑移项，$b_Y-a_Y\leq a_X-b_X$。开一个 $vector$，对于左区间，我们插入 $a_X-b_X$，对于右区间，我们插入 $b_Y-a_Y$。根据上面的式子很好理解。然后把所有的值排序并且离散化。从小到大遍历，对于 $b_Y-a_Y\leq a_X-b_X$ 的贡献，我们遍历到一个右区间的值的时候，在树状数组 $tr3$ 的 $b_Y-a_Y$ 的位置加 $b_Y$，在树状数组 $tr4$ 的 $b_Y-a_Y$ 的位置加 $1$。当遍历到一个左区间的值时，所有小于等于 $a_X-b_X$ 的 $b_Y-a_Y$ 已经全部加入树状数组中，因此我们知道所有 $b_Y$ 的和以及有多少个 $b_Y-a_Y$ 小于等于 $a_X-b_X$，那么 $b_X+b_Y$ 的和就很好计算了。至于 $b_Y-a_Y>a_X-b_X$ 的贡献也是一样算的，这里就不再多说，具体可以看代码。

时间复杂度是 $O(n\log^2n)$，虽然不是最优秀的，但是已经可以通过此题。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+10,mod=998244353;
int n,ans;
int x[N],y[N];
int a[2][N],b[2][N];
struct Tree{
	int tr[N];
	inline int lowbit(int x)
	{
		return x & -x;
	}
	inline void add(int x,int k)
	{
		for (int i=x;i<=n*2;i+=lowbit(i)) tr[i]+=k; 
	}
	inline int query(int x)
	{
		int res=0;
		for (int i=x;i;i-=lowbit(i)) res+=tr[i];
		return res;
	}
}tr1,tr2,tr3,tr4;
struct Data{
	int a,b,val,side;
	Data(int _a,int _b,int _side) : a(_a), b(_b), side(_side) 
	{
		val=side?b-a:a-b;
	}
	bool operator< (const Data &t) const
	{
		return val==t.val?side>t.side:val<t.val;
	}
};
vector<Data> q;
vector<int> num; 
void solve(int l,int r)
{
	if (l==r)
	{
		ans=(ans+3*(x[l]+y[l])%mod)%mod;
		return;
	}
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);
	a[0][mid]=x[mid],a[1][mid]=x[mid]+y[mid];
	b[0][mid]=x[mid]+y[mid],b[1][mid]=y[mid];
	for (int i=mid-1;i>=l;--i)
	{
		a[0][i]=min(a[0][i+1]+x[i],a[1][i+1]+x[i]+y[i]);
		a[1][i]=min(a[1][i+1]+y[i],a[0][i+1]+x[i]+y[i]);
		b[0][i]=min(b[0][i+1]+x[i],b[1][i+1]+x[i]+y[i]);
		b[1][i]=min(b[1][i+1]+y[i],b[0][i+1]+x[i]+y[i]); 
	}
	q.clear();
	for (int i=l;i<=mid;++i)
	{
		q.push_back({a[0][i],b[0][i],0});
		q.push_back({a[1][i],b[1][i],0});
	}
	a[0][mid+1]=x[mid+1],a[1][mid+1]=x[mid+1]+y[mid+1];
	b[0][mid+1]=x[mid+1]+y[mid+1],b[1][mid+1]=y[mid+1];
	for (int i=mid+2;i<=r;++i)
	{
		a[0][i]=min(a[0][i-1]+x[i],a[1][i-1]+x[i]+y[i]);
		a[1][i]=min(a[1][i-1]+y[i],a[0][i-1]+x[i]+y[i]);
		b[0][i]=min(b[0][i-1]+x[i],b[1][i-1]+x[i]+y[i]);
		b[1][i]=min(b[1][i-1]+y[i],b[0][i-1]+x[i]+y[i]);
	}
	for (int i=mid+1;i<=r;++i)
	{
		q.push_back({a[0][i],b[0][i],1});
		q.push_back({a[1][i],b[1][i],1});
	}
	sort(q.begin(),q.end());
	num.clear();
	for (auto p:q) num.push_back(p.val);
	num.erase(unique(num.begin(),num.end()),num.end());
	for (auto &p:q) p.val=lower_bound(num.begin(),num.end(),p.val)-num.begin()+1;
	for (auto p:q)
	{
		if (!p.side)
		{
			ans=(ans+2*tr3.query(p.val)%mod)%mod;
			ans=(ans+2*p.b%mod*tr4.query(p.val)%mod)%mod;
			tr1.add(p.val,p.a%mod);
			tr2.add(p.val,1);
		}
		else 
		{
			ans=(ans+2*tr1.query(p.val-1)%mod)%mod;
			ans=(ans+2*p.a%mod*tr2.query(p.val-1)%mod)%mod;
			tr3.add(p.val,p.b%mod);
			tr4.add(p.val,1);
		}
	}
	for (auto p:q)
	{
		if (!p.side)
		{
			tr1.add(p.val,-p.a%mod);
			tr2.add(p.val,-1);
		}
		else
		{
			tr3.add(p.val,-p.b%mod);
			tr4.add(p.val,-1);
		}
	}
}
signed main()
{
	scanf("%lld",&n);
	for (int i=1;i<=n;++i) scanf("%lld",&x[i]);
	for (int i=1;i<=n;++i) scanf("%lld",&y[i]);
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：wishapig (赞：1)

一个好想，但巨大麻烦的做法。

先弱化一下问题，如果求一个点到其他所有点的最短路长度之和，这个问题用最短路树可以方便地解决，答案为树上每个节点的权值乘上其子树大小。

比如（树根为第二行第一列的 $15$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/pa8ow2jv.png)

而现在要对所有点对都求，于是考虑强行递推最短路树的形态。

根从第 $n$ 列扫到第 $1$ 列，先讨论在第一行的情况，最短路树有两种可能的形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/tvm9rvwb.png)

或者

![](https://cdn.luogu.com.cn/upload/image_hosting/n4d1mvz9.png)

我们只需要对每个点快速找到它后面的 $j$，就可以进行递推。

为方便下面的分析，给出几个定义

- $p[1/2][i]$ 表示第一/二行的 $a[][i]$ 的前缀和
- $s[1/2][i]$ 表示第一/二行的 $a[][i]\times i$ 的前缀和
- $res[1/2][i]$ 表示树根为第一/二行第 $i$ 列时的贡献

那么第一种情况需要满足：
$$
\begin{aligned}
p[1][j]-p[1][i]<p[2][j-1]-p[2][i-1]\\
\Rightarrow p[2][i-1]-p[1][i]<p[2][j-1]-p[1][j]
\end{aligned}
$$
可以拿单调栈找到满足条件的第一个 $j$。

第二种情况需要满足：
$$
\begin{aligned}
p[2][j]-p[2][i-1]<p[1][j-1]-p[1][i]\\
\Rightarrow p[1][i]-p[2][i-1]<p[1][j-1]-p[2][j]
\end{aligned}
$$
两边形式不同，只能拿 ST 表查区间 $\max$ + 二分来找（捂脸）。

然后两种情况的 $j$ 取个 $\min$ 就是真实的 $j$ 了（如果不存在，则令 $j=n+1$）。

求出 $j$ 之后进行递推，即第 $j$ 列之后的子问题，加上 $i\sim j-1$ 列的贡献。

具体来说：

1. 如果子根取第一行第 $j$ 列，那么为：
   $$
   \begin{aligned}
   res[1][i]=&\ \ \ \ \ 2\cdot (n-i+1)\cdot a[1][i]\ (根的贡献)\\
   		&+res[1][j]\ (子根的贡献)\\
   		&+\sum_{k=i+1}^{j-1}a[1][k]\cdot (2\cdot (n-j+1)+j-k)\ (第一行的贡献)\\
   		&+\sum_{k=i}^{j-1}a[2][k]\cdot(j-k)\ (第二行的贡献)
   \end{aligned}
   $$

2. 如果子根取第二行第 $j$ 列，那么为：
   $$
   \begin{aligned}
   res[1][i]=&\ \ \ \ \ 2\cdot (n-i+1)\cdot a[1][i]\ (根的贡献)\\
   		&+res[2][j]\ (子根的贡献)\\
   		&+\sum_{k=i+1}^{j-1}a[1][k]\cdot (j-k)\ (第一行的贡献)\\
   		&+\sum_{k=i}^{j-1}a[2][k]\cdot(2\cdot (n-j+1)+j-k)\ (第二行的贡献)
   \end{aligned}
   $$



使用预处理出的 $p$ 和 $s$ 不难 $O(1)$ 求出。

然后根在第二行的情况是完全一样的，一/二行取反就可以了。

最终的贡献由于要考虑前后与算重，最后答案化出来是：
$$
ans=\sum_{i=1}^n(2\cdot (res[1][i]+res[2][i])-3\cdot (a[1][i]+a[2][i]))
$$
时间是 $O(n\log n)$，瓶颈在于 ST 表 + 二分。

代码细节较多

```cpp
typedef long long ll;
#define F first
#define S second
const int N=2e5+5,mod=998244353;
ll pre[3][N],mx[3][N][20];
int p[3][N],a[3][N],nex[3][N][3],res[3][N],Log[N];
int n,ans,top;
pair<ll,int> stk[N];
int Sum(int d, int l, int r, int k){
	return (1ll*(r+k)*((pre[d][r]-pre[d][l-1])%mod)+p[d][r]+mod-p[d][l-1])%mod;
}
ll query(int d, int l, int r){
	int k=Log[r-l+1];
	return max(mx[d][l][k],mx[d][r-(1<<k)+1][k]);
}
int main(){
	scanf("%d",&n);
	for (int k=1; k<=2; k++) for (int i=1; i<=n; i++){
		scanf("%d",&a[k][i]);
		pre[k][i]=pre[k][i-1]+a[k][i];
		p[k][i]=(p[k][i-1]+1ll*(mod-i+1)*a[k][i])%mod;
	}
	stk[top=1]={-1e18,n+1};
	for (int i=n; i>=1; i--){
		ll val=pre[1][i]-pre[2][i-1];
		while (top && stk[top].F>val) top--;
		nex[1][i][2]=stk[top].S; stk[++top]={val,i};
	}
	stk[top=1]={-1e18,n+1};
	for (int i=n; i>=1; i--){
		ll val=pre[2][i]-pre[1][i-1];
		while (top && stk[top].F>val) top--;
		nex[2][i][1]=stk[top].S; stk[++top]={val,i};
	}
	Log[0]=-1;
	for (int i=1; i<=n; i++){
		Log[i]=Log[i>>1]+1;
		mx[1][i][0]=pre[1][i-1]-pre[2][i];
		mx[2][i][0]=pre[2][i-1]-pre[1][i];
	}
	for (int i=n; i>=1; i--)
		for (int j=1; i+(1<<j)-1<=n; j++){
			mx[1][i][j]=max(mx[1][i][j-1],mx[1][i+(1<<(j-1))][j-1]);
			mx[2][i][j]=max(mx[2][i][j-1],mx[2][i+(1<<(j-1))][j-1]);
		}
	for (int i=1; i<=n; i++){
		int l=i+1,r=n; nex[1][i][1]=n+1;
		while (l<=r){
			int mid=(l+r)>>1;
			if (query(1,i+1,mid)>pre[1][i]-pre[2][i-1]) nex[1][i][1]=mid,r=mid-1;
			else l=mid+1;
		}
		l=i+1,r=n; nex[2][i][2]=n+1;
		while (l<=r){
			int mid=(l+r)>>1;
			if (query(2,i+1,mid)>pre[2][i]-pre[1][i-1]) nex[2][i][2]=mid,r=mid-1;
			else l=mid+1;
		}
	}
	for (int i=n; i>=1; i--){
		int d=min(nex[1][i][1],nex[1][i][2]);
		if (d==nex[1][i][1])
			res[1][i]=(1ll*res[2][d]+2ll*a[1][i]*(n-i+1)+Sum(1,i+1,d-1,0)+Sum(2,i,d-1,2*(n-d+1)))%mod; else
			res[1][i]=(1ll*res[1][d]+2ll*a[1][i]*(n-i+1)+Sum(1,i+1,d-1,2*(n-d+1))+Sum(2,i,d-1,0))%mod;
		d=min(nex[2][i][1],nex[2][i][2]);
		if (d==nex[2][i][1])
			res[2][i]=(1ll*res[2][d]+2ll*a[2][i]*(n-i+1)+Sum(1,i,d-1,0)+Sum(2,i+1,d-1,2*(n-d+1)))%mod; else
			res[2][i]=(1ll*res[1][d]+2ll*a[2][i]*(n-i+1)+Sum(1,i,d-1,2*(n-d+1))+Sum(2,i+1,d-1,0))%mod;
		ans=(1ll*ans+2ll*res[1][i]+2ll*res[2][i])%mod;
		ans=(1ll*ans+mod-3ll*(a[1][i]+a[2][i])%mod)%mod;
	}
	printf("%d\n",ans);
}
```



---

## 作者：qnqfff (赞：0)

### 思路

考虑分治，设当前区间为 $[l,r]$，区间中点为 $mid$，设 $a_{i,{0/1}}$ 表示第 $1/2$ 行第 $i$ 个到 $(1,mid),i\le mid$ 或 $(1,mid+1),i>mid$ 的答案，设 $b_{i,{0/1}}$ 表示第 $1/2$ 行第 $i$ 个到 $(2,mid),i\le mid$ 或 $(2,mid+1),i>mid$ 的答案，都可以简单 dp 求出。

于是答案为 $\sum\limits_{i=l}^{mid}\sum\limits_{j=mid+1}^{r}\sum\limits_{x\in\{0,1\}}\sum\limits_{y\in\{0,1\}}\min(a_{i,x}+a_{j,y},b_{i,x}+b_{j,y})$。

$\sum\limits_{i=l}^{mid}\sum\limits_{j=mid+1}^{r}\sum\limits_{x\in\{0,1\}}\sum\limits_{y\in\{0,1\}}\min(a_{i,x}+a_{j,y}-b_{i,x}-b_{j,y},0)+b_{i,x}+b_{j,y}$。

设 $c_{i,0/1}=a_{i,0/1}-b_{i,0/1}$。

$\sum\limits_{i=l}^{mid}\sum\limits_{j=mid+1}^{r}\sum\limits_{x\in\{0,1\}}\sum\limits_{y\in\{0,1\}}\min(c_{i,x}+c_{j,y},0)+b_{i,x}+b_{j,y}$。

分成两部分。

1. $\min(c_{i,x}+c_{j,y},0)$。

直接排个序后双指针。

2. $b_{i,x}+b_{j,y}$。

等于 $\sum\limits_{i=l}^{mid}\sum\limits_{x\in\{0,1\}}b_{i,x}\cdot2(r-mid)$ 和 $\sum\limits_{i=mid+1}^{r}\sum\limits_{x\in\{0,1\}}b_{i,x}\cdot2(mid-l+1)$，直接算即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int __int128
const int mod=998244353;
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,a[200010][2],dp[200010][2],_dp[200010][2],__dp[200010][2];
int solve(int l,int r){
	if(l==r) return (a[l][0]+a[l][1]<<1)%mod;int mid=(l+r)>>1,res=0;
	dp[mid][0]=a[mid][0];dp[mid][1]=a[mid][0]+a[mid][1];for(int i=mid-1;i>=l;i--){dp[i][0]=a[i][0]+min(dp[i+1][0],a[i][1]+dp[i+1][1]);dp[i][1]=a[i][1]+min(dp[i+1][1],a[i][0]+dp[i+1][0]);}
	dp[mid+1][0]=a[mid+1][0];dp[mid+1][1]=a[mid+1][0]+a[mid+1][1];for(int i=mid+2;i<=r;i++){dp[i][0]=a[i][0]+min(dp[i-1][0],a[i][1]+dp[i-1][1]);dp[i][1]=a[i][1]+min(dp[i-1][1],a[i][0]+dp[i-1][0]);}
	_dp[mid][0]=a[mid][0]+a[mid][1];_dp[mid][1]=a[mid][1];for(int i=mid-1;i>=l;i--){_dp[i][0]=a[i][0]+min(_dp[i+1][0],a[i][1]+_dp[i+1][1]);_dp[i][1]=a[i][1]+min(_dp[i+1][1],a[i][0]+_dp[i+1][0]);}
	_dp[mid+1][0]=a[mid+1][0]+a[mid+1][1];_dp[mid+1][1]=a[mid+1][1];for(int i=mid+2;i<=r;i++){_dp[i][0]=a[i][0]+min(_dp[i-1][0],a[i][1]+_dp[i-1][1]);_dp[i][1]=a[i][1]+min(_dp[i-1][1],a[i][0]+_dp[i-1][0]);}
	for(int i=l;i<=mid;i++) for(int x:{0,1}) (res+=(_dp[i][x])%mod*(r-mid<<1)%mod)%=mod;
	for(int i=mid+1;i<=r;i++) for(int x:{0,1}) (res+=(_dp[i][x])*(mid-l+1<<1)%mod)%=mod;
	for(int i=l;i<=r;i++) for(int x:{0,1}) __dp[i][x]=dp[i][x]-_dp[i][x];
	vector<int>A,B;for(int i=l;i<=mid;i++) for(int x:{0,1}) A.push_back(__dp[i][x]);for(int i=mid+1;i<=r;i++) for(int x:{0,1}) B.push_back(__dp[i][x]);
	sort(A.begin(),A.end());sort(B.begin(),B.end());for(int i=1;i<B.size();i++) B[i]+=B[i-1];
	for(int i=0,j=B.size()-1;i<A.size();i++){
		while(j&&A[i]+B[j]-B[j-1]>=0) j--;
		if(j&&A[i]+B[j]-B[j-1]<0) (res+=((j+1)*A[i]+B[j])%mod+mod)%=mod;if(!j&&A[i]+B[j]<0) (res+=(A[i]+B[j])%mod+mod)%=mod; 
	}return ((res<<1)+solve(l,mid)+solve(mid+1,r))%mod;
}
signed main(){
	n=read();int sum=0;for(int i=1;i<=n;i++) a[i][0]=read(),(sum+=a[i][0])%=mod;for(int i=1;i<=n;i++) a[i][1]=read(),(sum+=a[i][1])%=mod;
	int ans=(sum+solve(1,n))%mod;cout<<(long long)ans;
	return 0;
}
```

---

