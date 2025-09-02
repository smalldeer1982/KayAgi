# Complex Segments (Hard Version)

## 题目描述

这是这个问题的困难版本。在这个版本中， $n$ 的范围和时间限制都变高了。

当一个区间的集合可以被分割成一些子集并满足以下条件时，这个集合是复杂的：

- 所有的子集的大小相同
- 当且仅当两个区间在同一子集内时，这两个区间相交。

$t$ 组数据，每组数据给你一个集合包含 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$。求出最大的子集满足其为复杂的，输出这个集合的大小。

## 样例 #1

### 输入

```
3
3
1 2 3
5 4 6
5
1 2 3 6 8
5 4 7 9 10
5
3 1 4 1 5
7 2 6 5 10```

### 输出

```
3
4
4```

# 题解

## 作者：ForgotMe (赞：7)

E1 赛时可以做的啊，但是跑去看 F 了/fn。

首先如果一堆线段可以分成一组当且仅当这些线段存在共同的交集，这是显然的。

那么就可以考虑枚举一组线段的大小 $M$，求出其对应最多能够分出的组数 $f(M)$。

一个 $f(M)$ 是好求的，有一个显然的贪心算法，先把线段按照 $r$ 从小到大排序，然后从左往右扫，当加入一条线段 $[l,r]$，就把 $[l,r]$ 加上一，然后检查是否存在一个点的值为 $M$，如果有就说明形成了新的组，并记录下新的边界 $r$，下一组选的线段必须满足左端点大于 $r$。使用线段树就可以在 $\mathcal{O(n\log n)}$ 完成一次求解。

注意到 $f(M)\le \frac{n}{M}$，考虑根号分治，$f(M)\le C$ 就二分连续段求解，$M\le C$ 就直接跑暴力，能够做到 $\mathcal{O}((n\log n)^{\frac{3}{2}})$，可以跑过 E1。

考虑优化，有一个非常厉害的分治做法，可以解决以下问题：

有一个序列 $A$，满足如下条件：

- $A$ 是单调不增的。
- $0\le A_i\le \frac{n}{i}$。

这个算法伪代码表示如下：

```
inline void solve(int l,int r){
  if(f[l]==f[r]){
    for(int i=l+1;i<r;i++)f[i]=f[l];
    return ;
  }
  if(r-l<=1)return ;
  int mid=(l+r)>>1;
  f[mid]=get(mid);
  solve(l,mid);
  solve(mid,r);
}
```

最开始先求出 $f(1),f(n)$，然后递归求解即可。

考虑分析这个算法的复杂度，我们声称：对于递归的第 $d$ 层，最多只有 $\mathcal{O}(2^{d/2})$ 次询问。

注意到第 $d$ 层每个节点对应的区间长度是 $n/2^{d}$，那么第 $d$ 层前 $2^{d/2}$ 个区间最坏每一个都查一遍，否则对于后面的区间也即是 $[n/2^{d/2},n]$ 这一段一定有 $A_i\le 2^{d/2}$，最坏只有 $2^{d/2+1}$ 次查询，所以这个算法最坏会查询 $\sum_{i=0}^{\log_2 n}2^{d/2}=\sqrt{n}$ 次，复杂度就是 $\mathcal{O}(n+\sqrt{n}f(n))$，其中 $f(n)$ 表示求出一个 $f$ 的复杂度。

所以现在就可以做到 $\mathcal{O}(n\sqrt{n}\log n)$ 了。

但是还可以更快，考虑到查询的是全局最大值，那么只需要保存后缀最大值的信息即可。这里有一个 trick，对区间重编号使得 $l,r$ 都两两不同，但是是否相交与重编号之前保持一致。

```
for(int i=1;i<=n;i++){
    G1[l[i]].push_back(i);
    G2[r[i]].push_back(i);
}
cnt=0;
for(int i=1;i<=2*n;i++){
    for(auto x:G1[i])l[x]=++cnt;
    for(auto x:G2[i])r[x]=++cnt;
}
```

为什么要这么做呢？发现重编号后可以保证后缀最大值序列的相邻两项的差值一定为 $1$，于是直接去维护后缀最大值的位置，转化为 $01$ 序列。每次加入一个区间相当于把一个位置上的 $1$ 变成 $0$，全局最大值就是 $1$ 的个数，使用并查集维护即可，时间复杂度 $\mathcal{O}(n\sqrt{n}\alpha(n))$。

贴个代码
```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<int,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	Invn[0]=Invn[1]=1;
	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int t,n,l[300005],r[300005],po[600005],cnt,f[300005],res,fa[600005],tot;
vector<int>G1[600005],G2[600005];
inline int findSet(int u){
	return fa[u]==u?u:fa[u]=findSet(fa[u]);
} 
inline void merge(int u,int v){
	u=findSet(u),v=findSet(v);
	if(u==v)return ;
	if(u>v)swap(u,v); 
	fa[v]=u;
	tot++;
}
inline int calc(int m){
	for(int i=0;i<=2*n;i++)fa[i]=i;
	int lst=0,pos=0,ans=0;
	tot=0;
	for(int i=1;i<=2*n;i++){
		if(po[i]!=-1){
			if(po[i]<=lst)continue;
			for(int j=pos+1;j<i;j++)merge(pos,j);
			pos=i;
			int pre=findSet(po[i]-1);
			if(pre)merge(pre-1,pre);
			if(i-tot==m){
				ans++;
				lst=i;
				while(1){
					int pre=findSet(i);
					if(pre)merge(pre-1,pre);
					else break; 
				}
			}
		}
	}
	res=max(res,ans*m);
	return ans;
} 
inline void solve2(int l,int r){
	if(f[l]==f[r])return ;
	if(r-l<=1)return ;
	if(res>=1ll*(r-1)*f[l])return ;
	int mid=(l+r)>>1;
	f[mid]=calc(mid);
	solve2(l,mid);
	solve2(mid,r);
}
inline void solve(){
	gi(n);
	for(int i=1;i<=n;i++)gi(l[i]);
	for(int i=1;i<=n;i++)gi(r[i]);
	for(int i=1;i<=2*n;i++)G1[i].clear(),G2[i].clear(); 
	for(int i=1;i<=n;i++){
		G1[l[i]].push_back(i);
		G2[r[i]].push_back(i);
	}
	cnt=0;
	for(int i=1;i<=2*n;i++){
		for(auto x:G1[i])l[x]=++cnt;
		for(auto x:G2[i])r[x]=++cnt;
		po[i]=-1;
	}
	for(int i=1;i<=n;i++)po[r[i]]=l[i];
	res=0;
	f[1]=calc(1),f[n]=calc(n);
	solve2(1,n);
	pi(res);
}
signed main(){
	srand(time(0));
	gi(t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2018E2)

**题目大意**

> 给定 $n$ 个区间，选出若干个区间，使得其可以分割成若干个大小相同的子集，且两个区间相交当且仅当他们属于同一个子集，最大化选出区间个数。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

一个子集中的线段两两有交，相当于有一个公共点。

很自然的想法是枚举每个子集的大小 $k$，算出能分出多少个组 $f_k$。

一种求 $f_k$ 的方法如下：按右端点从小到大考虑每条线段，数据结构维护每个点被覆盖的次数，如果存在一个点被覆盖 $\ge k$ 次，那么就把 $l_j\le r_i$ 的线段全部删除。

此时我们得到了 $\mathcal O(n\log n)$ 求单个 $f_k$ 的算法。

注意到 $f_k\le \dfrac nk$ 并且 $f_k$ 单调递减，于是可以整体二分，在 $f_l=f_r$ 的时候直接得到返回。

此时考虑第 $d$ 层的递归次数：前 $2^{d/2}$ 个区间每个查询一次，剩余的区间左端点至少是 $\dfrac{n}{2^d}\times  2^{d/2}$，那么 $f_i\le 2^{d/2}$，这部分的查询次数也是 $2^{d/2}$ 的。

那么总的查询次数就是 $\sum 2^{d/2}=\mathcal O(\sqrt n)$。

直接计算可以做到 $\mathcal o(n\sqrt n\log n)$。

需要优化计算 $f_k$ 的复杂度，需要解决的问题就是扫描线的时候后缀加，查询全局最大值，很显然我们只关心后缀最大值。

首先我们可以离散化，使得所有区间的左右端点互不重合，那么后缀最大值每次变化量为 $\{0,1\}$。

给 $[l,r]$ 后缀加的时候就是找 $<l$ 的最后一个后缀最大值 $+1$ 的位置，并把把差分值改成 $+0$。

如果 $+1$ 不存在说明全局最大值 $+1$，用并查集就能维护这个过程。

时间复杂度 $\mathcal O(n\alpha(n)\sqrt n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=6e5+5;
array<int,2> a[MAXN];
int n,dsu[MAXN],ans;
int find(int x) { return dsu[x]^x?dsu[x]=find(dsu[x]):x; }
int f(int k) {
	iota(dsu,dsu+2*n+1,0);
	int s=0,lim=0,lst=0,cnt=0;
	for(int i=1;i<=n;++i) {
		int l=a[i][0],r=a[i][1];
		if(l<=lim) continue;
		for(int u=lst+1;u<r;++u) dsu[u]=lst;
		int p=find(l); lst=r;
		if(p<=lim) ++cnt;
		else dsu[p]=p-1;
		if(cnt>=k) cnt=0,lim=r,++s;
	}
	ans=max(ans,s*k);
	return s;
}
void cdq(int l,int r,int lo,int hi) {
	if(l>r||lo==hi) return ;
	int mid=(l+r)>>1,z=f(mid);
	cdq(l,mid-1,lo,z),cdq(mid+1,r,z,hi);
}
void solve() {
	cin>>n;
	vector <array<int,2>> st;
	for(int i=1;i<=n;++i) cin>>a[i][0],st.push_back({a[i][0],-i});
	for(int i=1;i<=n;++i) cin>>a[i][1],st.push_back({a[i][1],i});
	sort(st.begin(),st.end());
	for(int i=0;i<2*n;++i) {
		if(st[i][1]<0) a[-st[i][1]][0]=i+1;
		else a[st[i][1]][1]=i+1;
	}
	sort(a+1,a+n+1,[&](auto x,auto y){ return x[1]<y[1]; });
	ans=0,cdq(2,n-1,f(1),f(n));
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：irris (赞：0)

[?] problem，首先做法有一种莫名其妙的感觉，其次卡常得十分浪费人的感情......

> 有 $n$ 条线段 $[l_i, r_i]$，定义一个集合 $S$ 是好的当且仅当 $S$ 内所有线段交不为空，定义一个集合 $T$ 是复杂的当且仅当 $T$ 能被划分为若干好的子集 $S_1, \ldots, S_m$ 使得 $\lvert S_i\rvert$ 相等，且 $\forall u \in S_i, v \in S_j\;(i \neq j)$，都有 $u, v$ 不交。求最大的复杂子集。
>
> $1 \leq l_i \leq r_i \leq 2n$。E1：$\sum n \leq 2\cdot 10^4$，6 秒，256 MB；E2：$\sum n \leq 3\cdot 10^5$，12 秒，256 MB。

考虑枚举划分出的子集合的大小 $x$，有贪心：考虑按照 $r$ 排序依次加入线段，每次加入线段后，如果存在某个位置被覆盖的次数至少为 $x$，那么则删去所有的 $l$ 坐标不超过当前 $r$ 的线段，并将答案增加 $1$。时间复杂度 $\mathcal O(n^2\log n)$。

原过程相当于有 $\mathcal O(n\log n)$ 个查询，每次查询形如「保留所有 $l \geq k$ 的线段后，$r$ 最小为多少能够让某个位置被覆盖的次数至少为 $x$」，考虑分块，对每个 $(r - l)$ 为 $B$ 的倍数预处理可持久化线段树，时间复杂度 $\mathcal O(\frac{n^2\log n}{B})$，查询时先二分具体位置再暴力枚举不超过 $B$ 个数的影响即可，为 $\mathcal O(nB\log^2 n)$，取 $B = \mathcal O(\sqrt{\frac{n}{\log n}})$ 后，时空复杂度 $\mathcal O((n\log n)^{1.5})$。事实上我们强行给这个做法加入了在线元素，但实际上我们可以每次同时处理当前 $l$ 最小的关于所有 $x$ 的询问并推进，不需要可持久化，空间复杂度就少了一只 $\log n$。本人并未实现此算法，但猜测其足够通过 Easy Version。

有一个非常深刻的道理：我们考虑不维护所有 $x$ 的答案 $f_1, \ldots, f_n$，而是利用 $f_i \cdot i \leq n$ 且 $f_i$ 单调不降的性质，**设计一个算法，通过询问 $\boldsymbol{\mathcal O(\sqrt{n})}$ 次 $\boldsymbol f$ 的值，求出所有 $\boldsymbol{f_1, \ldots, f_n}$**。而这是可以做到的（并且容易证明这是理论下界）。我会在此提供一种与已知分治做法不同的做法：

- 令 $B = \lfloor \sqrt{n} \rfloor$。
- 首先，询问 $f_1, \ldots, f_{B}$，以及 $f_{n}, f_{n/2}, \ldots, f_{n/B}$。
- 考虑从小到大确定所有 $f_i = k$ 的区间，其中 $k = 1, 2, \ldots, B$。由于我们已经知道所有 $n/i$ 处的点值，所以我们会在一个 **长度不超过** $\frac{n}{k} - \frac{n}{k+1} \leq \frac{n}{k^2}$ 的范围内二分 $f_i$ 不超过 $k$ 和大于 $k$ 的分界线；而熟知 $\sum_{i=1}^{\sqrt{n}} \log(\frac{n}{i^2}) = \sum_{k \geq 1} \sum_{i \geq 1} [i^2 \leq \frac{n}{2^k}] = \sum_{k \geq 1} \sqrt{\frac{n}{2^k}} = \mathcal O(\sqrt{n})$，所以总询问次数为 $\mathcal O(\sqrt{n})$ 的。

我们成功去掉了 $\log^{0.5}$ 的复杂度因子，但是这仍旧不足够让我们通过本题。考虑进一步优化单次 $\mathcal O(n\log n)$ 的查询 $f_i$。注意到我们可以将操作抽象为：选定一个后缀并 $+1$；在后缀插入一个 $0$；查询全局最大值。

这个问题的做法是经典的：通过并查集维护所有后缀最大值即可。时间复杂度 $\mathcal O(n\sqrt{n}\alpha(n))$，空间复杂度 $\mathcal O(n)$。卡常后即可通过。

参考代码（不保证其随时均能通过本题）：

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

namespace FastIO {
	int fastio_digit[67], fastio_len = 0;
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return (void)putchar('0'); while (x) fastio_digit[++fastio_len] = x % 10, x /= 10; while (fastio_len > 0) putchar(fastio_digit[fastio_len--] ^ '0'); }
	template <typename T> inline void print(T x) { if (x >= 0) write<T>(x); else putchar('-'), write<T>(-x); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;

#define MAXN 300001

namespace DFU {
	int fa[MAXN], siz[MAXN], mn[MAXN], val[MAXN], cnt = 0;
	inline void clear() { cnt = 0; }
	inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	inline void merge(int x, int y) {
		if ((x = find(x)) == (y = find(y))) return;
		if (siz[x] > siz[y]) std::swap(x, y);
		mn[y] = std::min(mn[x], mn[y]);
		siz[y] += siz[x], val[y] += val[x], fa[x] = y;
	}
	inline void newNode(int v) { ++cnt, fa[cnt] = mn[cnt] = cnt, val[cnt] = v, siz[cnt] = 1; }
};

int a[MAXN], b[MAXN], c[MAXN], ans[MAXN];
std::vector<int> vec[MAXN];
void solve() {
	int n = read<int>(), m = (n << 1), k = 0;
	for (int i = 1; i <= m; ++i) 
		vec[i].clear();
	for (int i = 1; i <= n; ++i) 
		a[i] = read<int>();
	for (int i = 1; i <= n; ++i) 
		b[i] = read<int>(), c[i] = b[i];
	std::sort(c + 1, c + n + 1);
	k = std::unique(c + 1, c + n + 1) - c - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(c + 1, c + k + 1, a[i]) - c;
		b[i] = std::lower_bound(c + 1, c + k + 1, b[i]) - c;
	}
	for (int i = 1; i <= n; ++i) 
		vec[b[i]].push_back(a[i]);
	int cnt_solve_f = 0;
	auto solveF = [&](int x) -> int {
		if (ans[x] != 0) return ans[x];
		int res = 0, cur = 0; DFU::clear();
		for (int i = 1, j = 1, opt = n + 1, limr = 0; i <= k; ++i, ++j) {
			DFU::newNode(opt);
			if (opt == 0) DFU::merge(j - 1, j);
			opt = 0;
			for (int l : vec[i]) if (l > limr) {
				int pos = DFU::find(l - limr);
				cur += (DFU::mn[pos] == 1), ++opt;
				if ((--DFU::val[pos]) == 0) 
					DFU::merge(DFU::mn[pos] - 1, pos);
			}
			if (cur >= x) 
				++res, DFU::clear(), limr = i, j = cur = 0, opt = n + 1;
		}
		return ans[x] = res;
	};
	int tot = 0, b = (int)sqrtl(n);
	for (int i = 1; i <= n; ++i) 
		ans[i] = 0;
	if (n <= 3) {
		for (int i = 1; i <= n; ++i) 
			tot = std::max(tot, i * solveF(i));
		print<int>(tot, '\n');
		return;
	}
	for (int i = 1; i <= b + 1; ++i) 
		solveF(i), solveF(n / i);
	for (int k = 1; k <= b; ++k) {
		int p = n / (k + 1), q = n / k;
		while (ans[p] != ans[q]) {
			while (ans[p] != ans[q]) {
				int mid = (p + q + 1) >> 1; solveF(mid);
				if (ans[mid] == ans[q]) {
					for (int j = mid + 1; j < q; ++j) 
						ans[j] = ans[mid];
					solveF(q = mid - 1);
				} else {
					p = mid;
				}
			}
			if ((p = n / (k + 1)) == q) break;
			solveF(--q);
		}
		for (int j = p + 1; j < q; ++j) 
			ans[j] = ans[p];
	}
	for (int i = 1, f = 0; i <= n; ++i) 
		tot = std::max(tot, i * ans[i]);
	print<int>(tot, '\n');
}

int main() { int t = read<int>(); while (t--) solve(); return 0; }
```

---

