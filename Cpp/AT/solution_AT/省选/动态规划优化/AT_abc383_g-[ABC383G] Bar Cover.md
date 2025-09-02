# [ABC383G] Bar Cover

## 题目描述

你有一排 $N$ 个格子，第 $i$ 个格子（从左到右）包含一个整数 $A _ i$。

你还有 $\lfloor \frac{N} {K} \rfloor$ 块瓷砖，每块瓷砖可以覆盖连续的 $K$ 个格子。

对于每一个 $i = 1, \ldots, \lfloor \frac{N} {K} \rfloor$，解决如下问题：

-   恰好放置 $i$ 块瓷砖且不重叠时，求所覆盖格子中数字之和的最大值。

## 说明/提示

**「数据范围」**

-   $1 \leq N \leq 2 \times 10^5$
-   $1 \leq K \leq \min(5, N)$
-   $-10^9 \leq A_i \leq 10^9$
-   所有输入值均为整数。

**「样例 1 解释」**

对于 $i=1$，如果用一个瓷砖覆盖第 2 和第 3 个格子，被覆盖格子的数字之和为 $7$。

对于 $i=2$，如果用一个瓷砖覆盖第 2 和第 3 个格子，再用另一个瓷砖覆盖第 4 和第 5 个格子，被覆盖格子的数字之和为 $12$。

## 样例 #1

### 输入

```
6 2
-5 3 4 -1 6 -2```

### 输出

```
7 12 5```

## 样例 #2

### 输入

```
20 4
-5 3 4 -1 6 -2 13 -1 13 7 6 -12 3 -5 12 -6 -3 10 -15 -5```

### 输出

```
32 45 57 52 22```

# 题解

## 作者：ケロシ (赞：23)

本题解证明比较粗略，欢迎 Hack 或补充。

提供一种复杂度与 $k$ 无关的算法。

设 $a$ 的前缀和为 $s$。

首先考虑 dp，设 $f_{i,j}$ 为前 $i$ 个数中已经选了 $j$ 个区间了，列出方程：

$$
f_{i,j}=\max(f_{i-1,j},f_{i-k,j-1}+s_i-s_{i-k})
$$

考虑优化这个东西。

根据数学直觉，发现其每个 $f_i$ 都是上凸的。

这启发我们使用 slope trick（参考 [CF1787H](https://www.luogu.com.cn/problem/CF1787H)）。

套路的，设出差分数组 $g_{i,j}=f_{i,j}-f_{i,j-1}$，那么 $f_{i,j}=\sum_{l=1}^{j} g_{i,l}$。

代入原转移方程：

$$
\begin{aligned}
g_{i,j}&=\max(\sum_{l=1}^{j} g_{i-1,l},\sum_{l=1}^{j-1} g_{i-k,l}+s_i-s_{i-k})\\
&-\max(\sum_{l=1}^{j-1} g_{i-1,l},\sum_{l=1}^{j-2} g_{i-k,l}+s_i-s_{i-k})
\end{aligned}
$$

然后就要计算这些 $\max$ 取到哪个，因为根据数学直觉，$f_{i-1}$ 肯定比 $f_{i-k}$ 更凸，

所以猜测或打表，发现对于 $\max(\sum_{l=1}^{j} g_{i-1,l},\sum_{l=1}^{j-1} g_{i-k,l}+s_i-s_{i-k})$，存在一个分割点，使得所有的 $p \le j$ 取到前者，对于所有的 $p > j$ 取到后者。

所以对于 $g_{i,j}$ 的转移有三种情况：

$$
g_{i,j}=
\left\{\begin{matrix}
g_{i-1,j} & j \le p\\
\sum_{l=1}^{j-1} g_{i-k,l}+s_i-s_{i-k}-\sum_{l=1}^{j-1} g_{i-1,l} & j=p+1\\
g_{i-k,j-1}  & j > p + 1
\end{matrix}\right.
$$

然后应该可以通过归纳法，证明出 $f_{i}$ 是凸的。

然后考虑如何维护这个，类似 CF1787H，不难想到使用持久化平衡树，通过二分 $p$ 再在两颗平衡树上二分来找到 $p$，然后从 $g_{i-1}$ 和 $g_{i-k}$ 的平衡树上裂出一部分拼到 $g_i$ 即可。


时间复杂度 $O(n \log^2 n)$。

使用了 Leafy Tree 实现。

```cpp
const int N = 2e5 + 5;
const int M = 3e7 + 5;
const ll LNF = 1e18;
int n, k, m; 
ll a[N], s[N];
int rt[N], tot, ls[M], rs[M], sz[M]; ll F[M];
ll ans[N]; int cnt;
int add() {
	return ++ tot;
}
int add(ll x) {
	int u = add();
	sz[u] = 1;
	F[u] = x;
	return u;
}
void up(int u) {
	sz[u] = sz[ls[u]] + sz[rs[u]];
	F[u] = F[ls[u]] + F[rs[u]];
}
int up(int l, int r) {
	int u = add();
	ls[u] = l, rs[u] = r;
	up(u);
	return u;
}
int merge(int u, int v) {
	if(! u || ! v) return u | v;
	if(sz[u] <= sz[v] * 4 && sz[v] <= sz[u] * 4) {
		return up(u, v);
	}
	if(sz[u] >= sz[v]) {
		int l = ls[u], r = rs[u];
		if(sz[l] * 4 > (sz[u] + sz[v])) return merge(l, merge(r, v));
		return merge(merge(l, ls[r]), merge(rs[r], v));
	}
	else {
		int l = ls[v], r = rs[v];
		if(sz[r] * 4 > (sz[u] + sz[v])) return merge(merge(u, l), r);
		return merge(merge(u, ls[l]), merge(rs[l], r));
	}
}
void split(int u, int p, int & x, int & y) {
	if(! u || ! p) {
		x = 0, y = u;
		return;
	}
	if(sz[u] == p) {
		x = u, y = 0;
		return;
	}
	if(p <= sz[ls[u]]) {
		split(ls[u], p, x, y);
		y = merge(y, rs[u]);
	}
	else {
		split(rs[u], p - sz[ls[u]], x, y);
		x = merge(ls[u], x);
	}
}
ll query(int u, int r) {
	if(! u || ! r) return 0;
	if(sz[u] <= r) {
		return F[u];
	}
	if(r <= sz[ls[u]]) return query(ls[u], r);
	return F[ls[u]] + query(rs[u], r - sz[ls[u]]);
}
void print(int u) {
	if(! ls[u]) {
		ans[++ cnt] = F[u];
		return;
	}
	print(ls[u]);
	print(rs[u]);
}
void solve() {
	cin >> n >> k; m = n / k;
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, n) s[i] = s[i - 1] + a[i];
	REP(i, k) rt[i] = add(- LNF);
	FOR(i, k, n) {
		int L = 1, R = i / k, pos = 0;
		while(L <= R) {
			int mid = L + R >> 1;
			ll vl = query(rt[i - 1], mid);
			ll vr = query(rt[i - k], mid - 1) + s[i] - s[i - k];
			if(vl >= vr) {
				pos = mid;
				L = mid + 1;
			}
			else {
				R = mid - 1;
			}
		}
		ll vl = query(rt[i - 1], pos + 1);
		ll vr = query(rt[i - k], pos) + s[i] - s[i - k];
		if(pos == i / k) {
			rt[i] = rt[i - 1];
		}
		else if(! pos && vl < vr) {
			rt[i] = merge(add(s[i] - s[i - k]), rt[i - k]);
		}
		else {
			int x, y, z;
			split(rt[i - 1], pos, x, z);
			split(rt[i - k], pos, z, y);
			ll val = query(rt[i - k], pos) - query(rt[i - 1], pos) + s[i] - s[i - k];
			rt[i] = merge(merge(x, add(val)), y);
		}
	}
	print(rt[n]);
	FOR(i, 1, n / k) ans[i] += ans[i - 1];
	FOR(i, 1, n / k) cout << ans[i] << " "; cout << endl;
}
```

---

## 作者：Optimistic2 (赞：14)

题面：https://www.luogu.com.cn/problem/AT_abc383_g。

题目大意：

给定 $n$ 个数，对于 $i=1,2,3,\cdots\lfloor\frac{n}{k}\rfloor$：

求出在这 $n$ 个数中选出 $i$ 个块，每个块长度为 $k$，并且块与块之间两两不重叠的最大块内数字和。

首先先简化问题：

设 $b_i=\sum\limits_{j=i}^{i+k-1}a_j$，此时 $b$ 的长度为 $n-k+1$。

那么现在问题转化为：

在一个长度为 $n-k+1$ 的一个数组 $b$ 中，选出 $i$ 个数，使得两两中间至少有 $k-1$ 个数，求这 $i$ 个数的和的最大值。

发现 $k\le 5$，并且要对 $i=1,2,3,\cdots\lfloor \frac{n}{k}\rfloor$ 进行求解，这不免会让我们想到 wqs 之类的技巧。

虽然这道题并不需要 wqs，但是也启示我们可以发现一些性质：

设 $g_i$ 表示放 $k$ 个的最优答案，那么 $g_i$ 是凸的，并且差分数组是递减的。

**证明放在最后。**

知道这个结论之后，我们发现顺着做很难降低复杂度，那么我们考虑分治。

设 $f_{x,i,j,w}$ 表示当前在分治树上的点 $x$，左边保证至少有 $i$ 个数没有被选择，右边至少有 $j$ 个数没有被选择，并且现在已经选择了 $w$ 个数的答案。

合并两个块很简单：

枚举一个 $t$ 表示左边的块的右侧至少有 $t$ 个数没有选。

对于 $f_{x,i,j}$ 由 $f_{2x,i,t}$ 和 $f_{2x+1,k-t-1,j}$ 进行转移。

由于我们定义的是**至少**，那么转移完之后要用类似二维前缀和的方式进行更新。

合并的过程相当于是 $i$ 和 $j$ 的位置贡献到 $i+j$ 位置，并且在 $i+j$ 位置上取最大值。

但是合并的过程似乎带一个平方？怎么优化呢？

因为 $f_{x,i,j}$ 数组是凸的，它的差分数组是递减的，所以合并可以优化到 $O(n)$。

具体来说，合并相当于每次取两个差分数组下一个贡献最大的一个，类似归并。

这样我们就可以做到复杂度为 $O(nk^{3}\log{n})$。

但是发现过不了，考虑再将 $k^3$ 变为 $k^2$。

发现对于区间满足 $r-l+1\le k$ 的可以直接处理，因为它们只能选择一个，直接用 ST 表维护区间最大值即可。

此时分治树的叶子节点数量变成了 $O(\lfloor\frac{n}{k}\rfloor)$ 的级别，乘上 $k^3$ 就变为了 $O(nk^2)$，由于是分治树所以带一个 $\log{n}$。

那么最后的复杂度就是 $O(nk^2\log{n})$。

**关于选择的 $g_i$ 凸性的证明：**

其实这里的凸性其实是差分数组递减。

证明考虑使用归纳法证明，我们知道刚开始的 dp 数组（初始化）是凸的。

那么我们合并的过程，本质是像归并那样取出两个数组最大贡献的，那么取完之后差分数组一定是递减的。
 
```c++
#include<bits/stdc++.h>
using namespace std;
namespace IO{
	template<typename T>
	inline void read(T &x){
		short f=1;x=0;char ch=getchar();
		while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
		while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
		x*=f;
		return;
	}
	template<typename T>
	inline void out_(T x){
		if(x<0) putchar('-'),x=-x;
		if(x>9) out_(x/10);
		putchar(x%10+'0');
		return;
	}
	template<typename T>
	inline void out(T x){
		out_(x),putchar(' ');
		return;
	}
	inline void endl(){putchar('\n');return;}
	inline void air(){
		while(true) putchar('R'),putchar('E'),endl();
		return;
	}
};
using IO::read;
using IO::out;
using IO::endl;
using IO::air;
typedef long long ll;
typedef vector<ll> dp;
const int N=200005;
const ll inf=1e16;
dp t[4*N][5][5],ans;
int n,k;
int a[N];
ll s[N],b[N];
ll f[N][20];
void Max(dp &a,dp b){ //dp 取 max
	int len=max((int)a.size(),(int)b.size());
	while((int)a.size()<len) a.push_back(-inf);
	while((int)b.size()<len) b.push_back(-inf);
	for(register int i=0;i<len;++i)
		a[i]=max(a[i],b[i]);
	return;
}
dp Merge(dp a,dp b){ //合并两个凸包
	int len=(int)a.size()+(int)b.size()-1,pos1=0,pos2=0;
	dp res;
	for(int i=0;i<len;++i){
		res.push_back(a[pos1]+b[pos2]);
		if(pos1==(int)a.size()-1) pos2++;
		else if(pos2==(int)b.size()-1) pos1++;
		else if(a[pos1+1]-a[pos1]>b[pos2+1]-b[pos2]) pos1++;
		else pos2++;
	}
	return res;
}
inline ll ask(int l,int r){
	if(l>r) return 0;
	int k=__lg(r-l+1);
	return max(f[l][k],f[r-(1<<k)+1][k]);
}
inline void solve(int x,int l,int r){
	for(register int i=0;i<k;++i)
		for(register int j=0;j<k;++j)
			if(i<=r-l+1&&j<=r-l+1) t[x][i][j].push_back(0);
			else t[x][i][j].push_back(-inf);
	if(l==r) t[x][0][0].push_back(b[l]);
	else{
		int mid=(l+r)>>1;
		solve(x<<1,l,mid);
		solve(x<<1|1,mid+1,r);
		if(r-l+1<=k){ //特判区间长度小于等于 k
			for(register int w1=0;w1<k;w1++)
				for(register int w2=0;w2<k;w2++)
					if(l+w1<=r-w2) t[x][w1][w2].push_back(ask(l+w1,r-w2));
			return;
		} 
		for(register int w1=0;w1<k;++w1){
			for(register int w2=0;w2<k;++w2){
				Max(t[x][w1][min(k-1,w2+r-mid)],t[x<<1][w1][w2]);
				Max(t[x][min(k-1,w1+mid-l+1)][w2],t[x<<1|1][w1][w2]);
			}
		}
		for(register int i=0;i<k;++i)
			for(register int j=0;j<k;++j)
				for(register int w=0;w<k;w++)
					Max(t[x][i][j],Merge(t[x<<1][i][w],t[x<<1|1][k-w-1][j]));
		for(register int i=k-1;i>=0;i--)
			for(register int j=k-1;j>=0;j--){
				if(i-1>=0) Max(t[x][i-1][j],t[x][i][j]);
				if(j-1>=0) Max(t[x][i][j-1],t[x][i][j]);
			}//二维前缀和
	}
	return;
}
signed main(){
	read(n),read(k);
	for(register int i=1;i<=n;++i) read(a[i]);
	for(register int i=1;i<=n;++i) s[i]=s[i-1]+a[i];
	for(register int i=1;i<=n-k+1;++i) b[i]=s[i+k-1]-s[i-1];
	for(int i=n-k+1;i>=1;i--){
		f[i][0]=b[i];
		for(int j=1;i+(1<<j)-1<=n-k+1;j++){
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
	solve(1,1,n-k+1);
	for(register int i=0;i<k;++i)
		for(register int j=0;j<k;++j)
			Max(ans,t[1][i][j]);
	for(register int i=1;i<=(n/k);++i) out(ans[i]);
	return 0;
}
```
跑得很慢。

完结撒花。✿✿ヽ(°▽°)ノ✿

---

## 作者：_Cheems (赞：8)

记 $b_i=\sum\limits_{j=i}^{i+k-1} a_j$，即 $i$ 为起点的块的价值。

考虑分治，枚举跨过中点的块，于是有状态 $f_{l,r,i,j,s}$ 表示 $[l,r]$ 区间中放了 $s$ 个块，且开始 $i$ 个、结尾 $j$ 个位置强制不放块，最大权值是多少。

枚举中间块占据左边区间 $p$ 个位置，左部区间有 $c$ 个块，则有转移：

$$f_{l,r,i,j,s}\gets f_{l,mid,i,p,c}+f_{mid+1,r,k-p,j,s-1-c}+b_{r-p+1}$$

对于恰好放多少块的问题，大胆猜测是个凸包，打个表发现确实如此。

所以转移可以视为凸包的合并，由于凸包斜率单调，不难发现转移具有决策单调性，即 $s+1$ 的最优决策点 $c_1$ 与 $s$ 的决策点 $c_0$，一定满足 $c_1\ge c_0$。所以可以做到线性合并。从中可以感性理解出确实是凸包。

对于大小 $<2k$ 的区间，直接计算出 $f$ 即可。于是分治树叶子数量为 $\frac nk$，总复杂度 $O(nk^2\log \frac nk)$。

其实看出凸包就可以用 slope trick 解决无需分治，复杂度会更好。但是此题 $k$ 过小，有种大炮打蚊子的感觉。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5, K = 5, inf = 1e15;
int n, k, a[N], b[N];
vector<int>f[N << 2][K][K];

inline void mer(const vector<int> &A, const vector<int> &B, vector<int> &C, int add){
	bool fl = (add != inf);
	int na = A.size() - 1, nb = B.size() - 1, nc = na + nb;
	for(int k = 0, st = 0, ed; k <= nc; ++k){
		ed = k - st;
		if(ed > nb) ed = nb, st = k - ed;
		while(st < na && ed > 0 && A[st] + B[ed] < A[st + 1] + B[ed - 1]) ++st, --ed;
		C[k + fl] = max(C[k + fl], A[st] + B[ed] + fl * add); 
	}
}
inline void calc(int u, int l, int r){
	int len = r - l + 1;	
	for(int i = 0; i < k; ++i) 
		for(int j = 0; j < k && i + j <= len; ++j) 
			f[u][i][j] = vector<int> (1 + (len - i - j) / k, -inf);
	if(len < 2 * k){
		for(int i = 0; i < k; ++i) 
			for(int j = 0; j < k && i + j <= len; ++j){
				f[u][i][j][0] = 0;
				for(int p = l + i; p + k - 1 < r - j + 1; ++p) f[u][i][j][1] = max(f[u][i][j][1], b[p]); 
			}
		return ;
	}
	
	int mid = (l + r) >> 1, ls = (u << 1), rs = (u << 1) | 1;
	calc(ls, l, mid), calc(rs, mid + 1, r); 
	
	for(int i = 0; i < k && i <= mid - l + 1; ++i)
		for(int j = 0; j < k && j <= r - mid; ++j){
			mer(f[ls][i][0], f[rs][0][j], f[u][i][j], inf);
			for(int p = 1; p < k; ++p)
				if(i + p <= mid - l + 1 && j + k - p <= r - mid)
					mer(f[ls][i][p], f[rs][k - p][j], f[u][i][j], b[mid - p + 1]);
		}
}
signed main(){
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), a[i] += a[i - 1];
	for(int i = 1; i <= n - k + 1; ++i) b[i] = a[i + k - 1] - a[i - 1];
	calc(1, 1, n);
	for(int i = 1; i < f[1][0][0].size(); ++i) printf("%lld ", f[1][0][0][i]);
	return 0;
}
```

---

## 作者：Richard_Whr (赞：7)

很容易观察出来凸性。

凸性问题几个想法：模拟费用流，wqs 二分，slope trick，分治闵可夫斯基合并。

费用流建不动图。

wqs 二分只能求点值。

slope trick 倒是可以，题解区另外有高手（不过我是不会可持久化平衡树的啊）。

注意到 $k$ 很小，在分治合并的时候只需要枚举跨过中点的 $O(k)$ 个位置合并就行了。比较有前途。

闵可夫斯基和部分就不详细讲解了，如果需要可以百度。

设 $f_{l,r,j,k}$ 表示区间 $[l,r]$，左侧空了至少 $j$ 个，右侧空了至少 $k$ 个，构成的凸包。

先枚举 $j,k$，如果中间不选，那就是 $F_{l,r,j,k}=F_{l,mid,j,0}+F_{mid+1,r,0,k}$。

这里的 $+$ 就是凸包的合并，具体来说就是对差分数组归并排序。

如果中间选，枚举左侧占几个 $x$：

可以分解成先合并凸包：

$F_{l,r,j,k}=F_{l,mid,j,x}+F_{mid+1,r,m-x,k}$。

再记录 $w=s(mid-x+1,mid+m-k)$，则对整个凸包进行：$f_i=\max(f_i,f_{i-1}+w)$，这里的 $f_i$ 是凸包前 $i$ 个点的前缀和。

这个操作相当于将 $w$ 有序插入到 $f$ 的差分数组中。

复杂度看似是 $O(n \log n \times k^3)$。

但是由于区间长度为 $n$ 的凸包大小是 $\frac{n}{k}$，因此合并两个凸包的复杂度其实是 $O(\frac{n}{k})$，现在复杂度是 $O(n \log n \times k^2)$ 的了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=5,Inf=1e15;
vector<int> F[N*2][M][M];
int a[N],s[N];
int n,m;
int idx;

vector<int> Merge(vector<int> A,vector<int> B)
{
	if(!A.size()) return B;
	if(!B.size()) return A;
	vector<int> res;
	res.resize(A.size()+B.size());
	merge(A.begin(),A.end(),B.begin(),B.end(),res.begin(),greater<int>());
	return res;
}

vector<int> Max(vector<int> A,vector<int> B)
{
	if(!A.size()) return B;
	if(!B.size()) return A;
	vector<int> res;
	res.resize(max(A.size(),B.size()));
	for(int i=1;i<A.size();i++) A[i]+=A[i-1];
	for(int i=1;i<B.size();i++) B[i]+=B[i-1];
	for(int i=0;i<res.size();i++)
	{
		res[i]=-Inf;
		if(i<A.size()) res[i]=max(res[i],A[i]);
		if(i<B.size()) res[i]=max(res[i],B[i]);
	} 
	for(int i=res.size()-1;i>=1;i--) res[i]=res[i]-res[i-1];
	return res;
}

int solve(int l,int r)
{
	int u=++idx;
	if(l>=r) 
	{
		if(m<=r-l+1) F[u][0][0].push_back(s[r]-s[l-1]);
		return u;
	}
	int mid=l+r>>1;
	int L=solve(l,mid),R=solve(mid+1,r);
	for(int v1=0;v1<m;v1++)
	{
		for(int v2=0;v2<m;v2++)
		{
			if(v1+v2>r-l+1) continue;
			F[u][v1][v2]=Merge(F[L][v1][0],F[R][0][v2]);
			for(int k=1;k<m;k++)
			{
				if(v1+k>mid-l+1 || v2+m-k>r-mid) continue;
				int w=s[mid+m-k]-s[mid-k];
				vector<int> Vc=Merge(F[L][v1][k],F[R][m-k][v2]);
				F[u][v1][v2]=Max(F[u][v1][v2],Merge(Vc,{w}));
			}
		}
	}
	return u;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
	
	int rt=solve(1,n);
	
	int sum=0;
	for(auto x:F[rt][0][0]) sum+=x,cout<<sum<<" ";
	
	return 0;
}
```

---

## 作者：_Catluo_ (赞：7)

考虑 DP。

首先，不考虑重叠的限制。记 $s_i$ 表示从 $i$ 开始覆盖的贡献，记 $f_{i,j}$ 表示前 $i$ 个选了 $j$ 个，那么转移显然为：

$$ f_{i,j}=max(f_{i-1,j},f_{i-1,j-1}+s_i) $$

注意到，这个东西是凸的。所以我们可以 $O(n)$ 的合并两个 $f$，于是考虑分治，枚举跨过分界线的那一段，记 $g_{l,r,s_1,s_2}$ 表示区间 $l,r$，左边空了 $s_1$ 个，右边空了 $s_2$ 个时的 $f$ 的差分数组，枚举中间的段合并即可。时间复杂度 $O(nk^2\log n)$。

代码很丑。

```cpp

#include<bits/stdc++.h>
#define int long long 
#define mid ((l+r)>>1)
#define ls (x<<1)
#define rs ((x<<1)|1) 
using namespace std;
namespace IO{
    char buff[1<<21],*p1=buff,*p2=buff;
    inline char getch(){
        return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;
    }
    template<typename T>
    inline void read(T &x){
        char ch=getch();int fl=1;x=0;
        while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}
        while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}
        x*=fl;
    }
    template<typename T,typename ...Args>
    inline void read(T &x,Args& ...args){
        read(x);read(args...);
    }
    char obuf[1<<21],*p3=obuf;
    inline void putch(char ch){
        if(p3-obuf<(1<<21))*p3++=ch;
        else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
    }
    char ch[100];
    template<typename T>
    void write(T x){
        if(!x)return putch('0');
        if(x<0)putch('-'),x*=-1;
        int top=0;
        while(x)ch[++top]=x%10+48,x/=10;
        while(top)putch(ch[top]),top--;
    }
    template<typename T,typename ...Args>
    void write(T x,Args ...args){
        write(x);write(args...);
    }
    void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N=2e5+5,Inf=2e14+100;
int n,k;
int a[N],s[N];
struct node{
	vector<int>f[5][5]; 
}tree[N<<2];
vector<int>tmp;
void sol(int x,int l,int r){
	int len=r-l+1;
	if(r-l+1<2*k){
		for(int i=0;i<k;i++){
			for(int j=0;j<k&&i+j<=len;j++){
				int sum=-Inf;
				for(int w=l+i;w+k-1+j<=r;w++)
					sum=max(sum,s[w]);
				tree[x].f[i][j].push_back(sum); 
			}
		}
		return;
	}
	sol(ls,l,mid),sol(rs,mid+1,r);
	for(int s1=0;s1<k;s1++){
		for(int s2=0;s2<k;s2++){
			int Siz=(len-s1-s2)/k;
			for(auto i=tree[ls].f[s1][0].begin(),j=tree[rs].f[0][s2].begin();i!=tree[ls].f[s1][0].end()||j!=tree[rs].f[0][s2].end();){
				if(i!=tree[ls].f[s1][0].end()&&(j==tree[rs].f[0][s2].end()||*j<=*i))tree[x].f[s1][s2].push_back(*i++);
				else tree[x].f[s1][s2].push_back(*j++);
			}
			while(tree[x].f[s1][s2].size()<Siz)tree[x].f[s1][s2].push_back(-Inf);
			for(int w=0;w+1<k;w++){
				if(k-w-1+s2>(r-mid)||s1+w+1>(mid-l+1))continue;
				tmp.clear();
				int c=s[mid-w],ops=1;
				for(auto i=tree[ls].f[s1][w+1].begin(),j=tree[rs].f[k-w-1][s2].begin();i!=tree[ls].f[s1][w+1].end()||j!=tree[rs].f[k-w-1][s2].end()||ops;){
					if(ops&&(i==tree[ls].f[s1][w+1].end()||*i<=c)&&(j==tree[rs].f[k-w-1][s2].end()||*j<=c))tmp.push_back(c),ops=0;
					else if(i!=tree[ls].f[s1][w+1].end()&&(ops==0||c<=*i)&&(j==tree[rs].f[k-w-1][s2].end()||*j<=*i))tmp.push_back(*i++);
					else tmp.push_back(*j++);
				}
				while(tmp.size()<Siz)tmp.push_back(-Inf);
				int last=0;
				int now1=0,now2=0;
				for(int i=0;i<Siz;i++){
					now1+=tree[x].f[s1][s2][i];
					now2+=tmp[i];
					tree[x].f[s1][s2][i]=max(now1,now2)-last;
					last=max(now1,now2);
				}
			}
		}
	}
}
int dp[N];
signed main(){
	read(n,k);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i+k-1<=n;i++)
		for(int j=0;j<k;j++)
			s[i]+=a[i+j];
	sol(1,1,n);
	memset(dp,-0x3f,sizeof dp);
	for(int s1=0;s1<k;s1++){
		for(int s2=0;s2<k;s2++){
			int Siz=(n-s1-s2)/k;
			int now=0;
			for(int i=0;i<Siz;i++){
				now+=tree[1].f[s1][s2][i];
				dp[i+1]=max(dp[i+1],now);
			}
		}
	}
	for(int i=1;i<=(n/k);i++){
		write(dp[i]),putch(' ');
	}
	flush();
	return 0;
}


```

---

## 作者：Felix72 (赞：3)

值得一做的题目，建议自认为对套路不熟悉的选手练练。如果想不出来，不妨参考一下这篇题解的思路，看看哪一步卡住了。

我们先分析这个题难在哪里。我们会发现这个题的难点在于，一次放置操作具有较强的后效性，会影响到后续的决策可行性，因此这 $\lfloor \frac{n}{k} \rfloor$ 个问题关联性较弱。

那么相应的，我们一般有如下方式破除后效性：

- 通过 DP 消除后效性；
- 设计一种巧妙的反悔贪心以涵盖最优决策。

这个题难以转化为模拟费用流的模型，手玩也不太能找到一种固定的反悔模式，因此我们先认为这题的模式是 DP。设计状态 $f_{i, j}$ 表示考虑到第 $i$ 个格子且选择了 $j$ 个连续段的最优答案。容易写出 $O(n^2)$ 算法，接下来对着常见优化方式思考如何优化：

- 更改 DP 状态或变化转移顺序；
- 根据题目的自带性质优化；
- 数据结构优化；
- 推式子，找数学性质。

这个题中我们容易想到第二种优化方式。因为一开始的选择相对自由，已选位置越多越难选到权值大的位置，所以 DP 数组具有凸性。然而，简单地维护 $k$ 个凸包仍然不能快速合并。

我们发现这是由于凸包大小是 $O(n)$ 级别的，因此进行复合时复杂度较高。思考如何人为地减小这个大小。最终我们发现可以用分治使得凸包的总大小仅为 $O(n \log n)$ 级别，于是用建线段树的顺序 DP 就可以了。

---

## 作者：ty_mxzhn (赞：2)

[决策单调性学习笔记第二组例题](https://www.luogu.com.cn/article/xj5zm8kg)。

题意：有 $k$ 长度的块，选 $i$ 个不交的块求覆盖数和最大值。对 $1\le i\le \lfloor \dfrac{n}{k}\rfloor$ 求答案。$n \le 2\times 10^5,k\le 5$。

选块显然可以预处理，问题变成任意两个点距离不能 $\le k$ 选最大价值的点。

考虑动态规划，把剩余位置计入状态。考虑形式幂级数的形式，可以完美的表示动态规划的状态。不过写成矩阵也行。

考虑分治。思考分治乘形式幂级数，如何使用 $(\max,+)$ 卷积快速合起来。

这本质上是简单的。复杂度可以做到 $O(nk^3\log n)$。

具体的，考虑分治了 $[l,mid]$ 的答案和 $[mid+1,r]$ 的答案。

为了合并这两组答案，设置 $f_{j,a,b}$ 表示选了 $j$ 个点，这个区间里到左边的最近距离是 $a$ 到右边最近距离是 $b$。合并时跑闵可夫斯基和即可。

因为实际上长度为 $n$ 的区间只能放 $\dfrac{n}{k}$ 个块，所以时间复杂度是 $O(nk^2\log n)$。

---

## 作者：cforrest (赞：0)

对 [这篇题解](https://www.luogu.com.cn/article/ub9rdvqn) 的一点补充。

沿用记号，状态转移方程为

$$
f_{i,j} = \max\{f_{i-1,j},f_{i-k,j-1}+s_i-s_{i-k}\}.
$$

现在归纳证明两点：

1.  $f_{i,j}-f_{i-k,j-1}$ 关于 $j$ 递减；
2.  $f_{i,j}-f_{i-1,j}$ 关于 $j$ 递增。

归纳起点是平凡的。假设命题对 $i-1$ 及之前的自然数都成立，现在证明它对 $i$ 也成立。直接验证即可。

首先，有

$$
f_{i-1,j}-f_{i-k,j-1}=(f_{i-1,j}-f_{i-1-k,j-1})-(f_{i-k,j-1}-f_{i-1-k,j-1})
$$

关于 $j$ 递减，因为它的被减数关于 $j$ 递减，减数关于 $j$ 递增。

利用这个结论，有

$$f_{i,j}-f_{i-k,j-1}=\max\{f_{i-1,j}-f_{i-k,j-1},s_i-s_{i-k}\}$$ 

关于 $j$ 递减，且

$$f_{i,j}-f_{i-1,j}=\max\{0,s_i-s_{i-k}+f_{i-k,j-1}-f_{i-1,j}\}$$

关于 $j$ 递增。这就完成了归纳。

更进一步，有

$$
f_{i,j}-f_{i,j-1} = f_{i,j}-f_{i-k,j-1}-\sum_{\ell=1}^k(f_{i-\ell+1,j-1}-f_{i-\ell,j-1})
$$

关于 $j$ 递减，因为被减数递减，减数中的每一项都递增。这就说明 $f_{i,j}$ 关于 $j$ 是凹函数。

同时，上面推导中的那个结论也说明对于任何 $i$，都存在 $p_i$ 使得

$$
f_{i,j} = \begin{cases}f_{i-1,j},&j\le p_i,\\ f_{i-k,j-1}+s_i-s_{i-k},&j>p_i.\end{cases}
$$

虽然 [这篇题解](https://www.luogu.com.cn/article/ub9rdvqn) 求了个差分，凑成了 Slope Trick 的形式，但是似乎这个形式直接对原序列本身操作也是容易的，还不用维护平衡树中各项的和，直接二分完之后打个懒标记，再合并，然后直接输出最后的序列就好。

时间复杂度仍然是 $O(n\log^2n)$ 的。

```cpp
/*  headers */

class WBLT {
    struct Node {
        int ch[2], sz;
        long long lz;
        Node() : ch{}, sz{}, lz{} {}
    };

    static constexpr int DELTA = 3;
    static constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

    int id;
    std::vector<int> rt;
    std::vector<Node> node;    
    
#define getter(var) \
    auto var(int x) const { return node[x].var; } \
    auto& var(int x) { return node[x].var; }

    getter(sz)
    getter(lz)

#undef getter

    auto& ch(int x, int i) { return node[x].ch[i]; }
    auto ch(int x, int i) const { return node[x].ch[i]; }

    int new_node() { return ++id; }
    void del_node(int& x) { /* pass */ }

    void copy_node(int& x) {
        int y = new_node();
        node[y] = node[x];
        x = y;
    }

    int new_leaf(long long v) {
        int x = new_node();
        lz(x) = v;
        sz(x) = 1;
        return x;
    }

    int new_tree(int x, int y) {
        int z = new_node();
        ch(z, 0) = x;
        ch(z, 1) = y;
        push_up(z);
        return z;
    }

    std::pair<int, int> cut_tree(int& x) {
        int y = ch(x, 0);
        int z = ch(x, 1);
        del_node(x);
        return { y, z };
    }

    void lazy_add(int& x, long long v) {
        if (!x) return;
        copy_node(x);
        lz(x) += v;
    }

    void push_up(int x) {
        sz(x) = sz(ch(x, 0)) + sz(ch(x, 1));
    }

    void push_down(int& x) {
        if (lz(x)) {
            copy_node(x);
            lazy_add(ch(x, 0), lz(x));
            lazy_add(ch(x, 1), lz(x));
            lz(x) = 0;
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (sz(x) > sz(y) * DELTA) {
            push_down(x);
            auto [a, b] = cut_tree(x);
            if (sz(a) * DELTA >= (sz(b) + sz(y))) {
                return merge(a, merge(b, y));
            } else {
                push_down(b);
                auto [c, d] = cut_tree(b);
                return merge(merge(a, c), merge(d, y));
            }
        } else if (sz(y) > sz(x) * DELTA) {
            push_down(y);
            auto [a, b] = cut_tree(y);
            if (sz(b) * DELTA >= (sz(a) + sz(x))) {
                return merge(merge(x, a), b);
            } else {
                push_down(a);
                auto [c, d] = cut_tree(a);
                return merge(merge(x, c), merge(d, b));
            }
        } else {
            return new_tree(x, y);
        }        
    }

    long long kth_elem(int x, int k, long long v) {
        if (k <= 0 || k > sz(x)) return -inf;
        if (sz(x) == 1) return lz(x) + v;
        return k <= sz(ch(x, 0))
            ? kth_elem(ch(x, 0), k, v + lz(x))
            : kth_elem(ch(x, 1), k - sz(ch(x, 0)), v + lz(x));
    }

    std::pair<int, int> split(int x, int k) {
        if (!x) return { 0, 0 };
        if (k <= 0) return { 0, x };
        if (k >= sz(x)) return { x, 0 };
        push_down(x);
        auto [a, b] = cut_tree(x);
        if (k <= sz(a)) {
            auto [ll, rr] = split(a, k);
            return { ll, merge(rr, b) };
        } else {
            auto [ll, rr] = split(b, k - sz(a));
            return { merge(a, ll), rr };
        }
    }

    void print(int x, long long v) {
        if (!x) return;
        print(ch(x, 0), v + lz(x));
        if (sz(x) == 1) std::cout << (v + lz(x)) << ' ';
        print(ch(x, 1), v + lz(x));
    }

public:
    WBLT(int n) : id(0), rt(n), node(n << 1) {
        rt[0] = new_leaf(0);
    }

    void modify(int i, int k, long long v) {
        if (i < k) {
            rt[i] = rt[0];
            return;
        }
        int ll = 1, rr = sz(rt[i - 1]);
        int p = 0;
        while (ll <= rr) {
            int mm = (ll + rr) / 2;
            if (kth_elem(rt[i - 1], mm, 0) >= kth_elem(rt[i - k], mm - 1, 0) + v) {
                p = mm;
                ll = mm + 1; 
            } else {
                rr = mm - 1;
            }
        }
        auto [l, r] = split(rt[i - 1], p);
        rt[i] = l;
        std::tie(l, r) = split(rt[i - k], p - 1);
        lazy_add(r, v);
        rt[i] = merge(rt[i], r);
    }

    void print(int i) {
        auto [ll, rr] = split(rt[i], 1);
        print(rr, 0);
        std::cout << '\n';
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<long long> s(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> s[i];
        s[i] += s[i - 1];
    }
    WBLT dp(2e7);
    for (int i = 1; i <= n; ++i) {
        dp.modify(i, k, i >= k ? s[i] - s[i - k] : 0);
    }
    dp.print(n);
    return 0;
}
```

因为全是区间复制，所以用了 WBLT 实现。区间加操作用标记永久化，不然会爆空间。

---

