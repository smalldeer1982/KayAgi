# [DTCPC 2024] mex,min,max

## 题目描述

给定序列 $\{a_n\}$ 和 $k$，求有多少子区间 $[l,r]$ 满足 $\operatorname{mex}\{a_l,a_{l+1},\dots,a_{r-1},a_r\}+\min\{a_l,a_{l+1},\dots,a_{r-1},a_r\}+k\geq \max\{a_l,a_{l+1},\dots,a_{r-1},a_r\}$。

$\operatorname{mex}$ 定义为集合内没有出现过的最小的**非负整数**。

## 样例 #1

### 输入

```
3 0
1 0 2```

### 输出

```
5```

# 题解

## 作者：Reunite (赞：5)

## 一
---
需要发现，$\min(mex(l,r),\min(l,r))=0$ 是恒成立的，因为如果 $\min =0$，则 $mex$ 一定不为 $0$，若 $\min \ne 0$，则 $mex=0$。

那么我们可以把合法区间的条件容斥拆开，记 $A$ 为满足 $mex+k \ge \max$ 的区间个数，$B$ 为 $\min+k \ge \max$ 的个数，$C$ 为 $k \ge \max$ 的个数，则由上述性质可以得到，$ans=A+B-C$。接下来只需分别考虑 $A,B,C$ 如何求解即可。

对于 $C$，固定右端点，合法的左端点是一段连续区间，可以预处理 ST 表，二分解决，对于 $B$，因为极差也满足单调性（固定右端点，越往左 $\min$ 越小，$\max$ 越大，极差越大），所以合法的左端点也是一段区间，同样可以二分解决。

现在重点考虑 $C$。

---
## 二 
---
首先需要知道一个**极短极长 $mex$ 段** 的东西。具体说，如果把所有 $\frac{n(n+1)}{2}$ 个区间 $mex$ 提取出来拍到二维平面上，划分出一些极大的 $mex$ 相同的矩形，这样的矩形只有 $O(n)$ 个。这是个经典结论，不会自行去看 [P9970 [THUPC 2024 初赛] 套娃](https://www.luogu.com.cn/problem/P9970)。

如果我们求出了这 $O(n)$ 个矩形，把坐标信息看成 $l \in [L_i,l_i],r\in[r_i,R_i]$ 的话，$[l_i,r_i],[L_i,R_i]$ 就分别是极短极长的 $mex$ 段。对于每一段，上述满足条件的 $l,r$，其 $mex$ 都是相等的。又因为 $\max$ 具有可重合并的性质，如果我们找到最靠左的 $x\in[L_i,l_i],mex+k \ge\max(x,r_i)$，找到最靠右的 $y \in [r_i,R_i],mex+k \ge \max(l_i,y)$，那么任意 $l\in[x,l_i],r\in[r_i,y]$ 的区间都是满足条件的。这部分可以 $O(n\log n)$ 求出。

但是还有一个问题，这样做会算重，如果我们把上面的 $[x,l_i],[r_i,y]$ 重新看成一个矩形的话，再做一边矩形面积并就不会算重了。因为每个极短极长 $mex$ 段最多只会产生一个矩形，所以复杂度是对的。

---
## 三
---

分析一下复杂度，预处理 ST 表，各种二分，矩形面积并，都是 $O(n\log_2 n)$ 的，空间 $O(n\log_2n)$，因为要主席树动态求区间 $mex$。

代码略长，应该每部分分开写的很清楚。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define PI pair <int,int>
#define fir first
#define sec second
#define ll long long
using namespace std;

int n,k,tot,m;
int a[500005];
int lg[500005];
int mx[21][500005];
int mn[21][500005];
vector <int> f[500005];
vector <PI> g[500005];
struct node{int p,l,r,op;}aa[2000005];
ll ans;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

namespace segmenttree{

	int tot;
	int rt[500005];
	int lc[10000005];
	int rc[10000005];
	int t[10000005];

	inline int ins(int u,int l,int r,int k,int x){
		++tot;
		lc[tot]=lc[u],rc[tot]=rc[u],t[tot]=t[u];
		u=tot;
		if(l==r){t[u]=x;return u;}
		int mid=(l+r)>>1;
		if(k<=mid) lc[u]=ins(lc[u],l,mid,k,x);
		else rc[u]=ins(rc[u],mid+1,r,k,x);
		t[u]=min(t[lc[u]],t[rc[u]]);
		return u;
	}
	
	inline int mex(int u,int l,int r,int k){
		if(l==r) return l;
		int mid=(l+r)>>1;
		if(t[lc[u]]<k) return mex(lc[u],l,mid,k);
		else return mex(rc[u],mid+1,r,k);
	}

}
using namespace segmenttree;


inline int pre(int x,int i){
	auto p=lower_bound(f[x].begin(),f[x].end(),i);
	if(p!=f[x].begin()) return *(--p);
	return 0;
}

inline int nxt(int x,int i){
	auto p=upper_bound(f[x].begin(),f[x].end(),i);
	if(p!=f[x].end()) return *p;
	return 0;
}

inline int askmx(int l,int r){
	int len=lg[r-l+1];
	return max(mx[len][l],mx[len][r-(1<<len)+1]);
}

inline int askmn(int l,int r){
	int len=lg[r-l+1];
	return min(mn[len][l],mn[len][r-(1<<len)+1]);
}

inline void init(){
	for(int i=1;i<=n;i++) f[a[i]].emplace_back(i),rt[i]=ins(rt[i-1],0,n,a[i],i);
	for(int i=1;i<=n;i++) g[a[i]==0].push_back({i,i});
	for(int i=1;i<=n;i++){
		for(auto tmp:g[i-1]){
			int l=tmp.fir,r=tmp.sec;
			int p=pre(i-1,l);
			if(p) g[mex(rt[r],0,n,p)].push_back({p,r});
			int q=nxt(i-1,r);
			if(q) g[mex(rt[q],0,n,l)].push_back({l,q});
		}
		sort(g[i].begin(),g[i].end(),[](PI p,PI q){return p.fir==q.fir?p.sec<q.sec:p.fir>q.fir;});
		vector <PI> gg;
		int R=1e9;
		for(auto tmp:g[i]){
			if(R>tmp.sec) gg.emplace_back(tmp);
			R=min(R,tmp.sec);
		}
		g[i]=gg;
	}
	for(int i=1;i<=n;i++) mx[0][i]=mn[0][i]=a[i];
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<(j-1))]),
			mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<(j-1))]);

	return ;
}

inline int get1(int l,int r,int p,int x){
	int mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(askmx(mid,p)<=x) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}

inline int get2(int l,int r,int p,int x){
	int mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(askmx(p,mid)<=x) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}

inline void work(){
	for(int i=n;i>=0;i--){
		for(auto tmp:g[i]){
			int l=tmp.fir,r=tmp.sec;
			int p=pre(i,l);
			if(p) p++;
			else p=1;
			int q=nxt(i,r);
			if(q) q--;
			else q=n;
			int L=max(1,get1(p,l,r,i+k)),R=min(n,get2(r,q,l,i+k));
			if(L>R) continue;
			aa[++m]={L,r,R,1};
			aa[++m]={l+1,r,R,-1};
		}
	}

	return ;
}

namespace Segmenttree{

	int tg[2000005];
	int mnn[2000005];
	int ctt[2000005];

	inline void pushup(int u){
		mnn[u]=min(mnn[u<<1],mnn[u<<1|1]);
		ctt[u]=0;
		if(mnn[u]==mnn[u<<1]) ctt[u]+=ctt[u<<1];
		if(mnn[u]==mnn[u<<1|1]) ctt[u]+=ctt[u<<1|1];
		return ;
	}

	inline void build(int u,int l,int r){
		ctt[u]=r-l+1;
		if(l==r) return ;
		int mid=(l+r)>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		return ;
	}

	inline void down(int u,int x){mnn[u]+=x;tg[u]+=x;return ;}

	inline void pushdown(int u){
		if(!tg[u]) return ;
		down(u<<1,tg[u]);
		down(u<<1|1,tg[u]);
		tg[u]=0;
		return ;
	}

	inline void updata(int u,int l,int r,int L,int R,int x){
		if(L<=l&&r<=R){down(u,x);return ;}
		pushdown(u);
		int mid=(l+r)>>1;
		if(L<=mid) updata(u<<1,l,mid,L,R,x);
		if(R>mid) updata(u<<1|1,mid+1,r,L,R,x);
		pushup(u);
	}

}
using namespace Segmenttree;

inline void solveA(){
	sort(aa+1,aa+1+m,[](node p,node q){return p.p==q.p?p.op<q.op:p.p<q.p;});
	build(1,1,n);
	int l=1;
	for(int i=1;i<=n;i++){
		while(aa[l].p<=i&&l<=m) updata(1,1,n,aa[l].l,aa[l].r,aa[l].op),l++;
		ans+=n-(mnn[1]?0:ctt[1]);
	}

	return ;
}

inline void solveB(){
	for(int i=1;i<=n;i++){
		int l=1,r=i,mid,pos=i+1;
		while(l<=r){
			mid=(l+r)>>1;
			if(askmn(mid,i)+k>=askmx(mid,i)) pos=mid,r=mid-1;
			else l=mid+1;
		}
		ans+=i-pos+1;
	}

	return ;
}

inline void solveC(){
	for(int i=1;i<=n;i++){
		int l=1,r=i,mid,pos=i+1;
		while(l<=r){
			mid=(l+r)>>1;
			if(k>=askmx(mid,i)) pos=mid,r=mid-1;
			else l=mid+1;
		}
		ans-=i-pos+1;
	}

	return ;
}

int main(){
	in(n),in(k);
	for(int i=1;i<=n;i++) in(a[i]);
	init();
	work();
	solveA();
	solveB();
	solveC();
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：4)

# Solution

思路很顺的一个题。

好像和官方做法不太一样。

## Part I

观察到一个性质：对于一个区间，$\text{mex}(l,r)=0$ 与 $\min(l,r)=0$ 至少成立一个。证明显然。

记 $A$ 为 $\text{mex}(l,r)+k\geq\max(l,r)$ 的区间个数，$B$ 为 $\min(l,r)+k\geq\max(l,r)$ 的区间个数，$C$ 为 $\max(l,r)\leq k$ 的区间个数。

根据性质，简单容斥一下，答案 $ans=A+B-C$。

$B,C$ 好求，因为固定了右端点后合法的左端点在一个区间内，枚举右端点二分左端点即可。这部分用 ST 表处理极值，可以做到 $\mathcal{O}(n\log n)$。

考虑怎么求 $A$。

## Part II

你如果做过 [[THUPC 2024 初赛] 套娃](https://www.luogu.com.cn/problem/P9970) 的话，就会知道一个叫『极小 mex 区间』的东西。

一个结论是这样的『极小 mex 区间』只有 $\mathcal{O}(n)$ 个。所以用那题的做法求出所有『极小 mex 区间』，并对每个『极小 mex 区间』求出包含它的『极大 mex 区间』。这部分可以做到 $\mathcal{O}(n\log n)$。

枚举所有极小区间。对于一个极小区间 $[l,r]$，它的 $\text{mex}$ 为 $p$，极大区间为 $[L,R]$。那么对于 $\forall l'\in[L,l],r'\in[r,R]$，$\text{mex}(l',r')=p$。这样，$\text{mex}+k$ 就固定了。二分出极大的区间 $[l',r']$，使得 $l'\in[L,l],r'\in[r,R]$ 且 $p+k\geq \max(l'\,r')$。$\forall pl\in[l',l],pr\in[r,r']$，$[pl,pr]$ 是合法区间。

我们发现这样求合法区间不漏但是会重。不过没关系，直接扫描线，对所有 $(l',l)(r',r)$ 组成的矩阵求面积并就行了。这部分复杂度为 $\mathcal{O}(n\log n)$。

总复杂度 $\mathcal{O}(n\log n)$，可以通过。码量其实没有想象中多，只有 4K 不到，而且好调。

实现的时候二分容易出错，所以把二分换成了更简洁的倍增。

# Code

```cpp
// writer: Milkcat
// time: 2024.2.17
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 5e5 + 5;
	
	namespace HJT {
		int cnt, s[N << 5], Ls[N << 5], Rs[N << 5];
		int modify(int p, int l, int r, int t, int k) {
			int rt = ++ cnt; Ls[rt] = Ls[p], Rs[rt] = Rs[p];
			if (l == r) return s[rt] = k, rt;
			int mid = (l + r) >> 1;
			if (t <= mid) Ls[rt] = modify(Ls[p], l, mid, t, k);
			if (t > mid) Rs[rt] = modify(Rs[p], mid + 1, r, t, k);
			s[rt] = min(s[Ls[rt]], s[Rs[rt]]);
			return rt;
		}
		int query(int p, int l, int r, int k) {
			if (l == r) return l;
			int mid = (l + r) >> 1;
			if (s[Ls[p]] < k) return query(Ls[p], l, mid, k);
			return query(Rs[p], mid + 1, r, k);
		}
	}
	
	namespace SGT {
		LL sum[N << 3], ass[N << 3];
		void pushup(int p, int l, int r) {
			if (ass[p]) sum[p] = r - l + 1;
			else sum[p] = sum[p << 1] + sum[p << 1 | 1]; 
		}
		void upd(int p, int l, int r, int nl, int nr, int k) {
			if (nl <= l && r <= nr) { ass[p] += k, pushup(p, l, r); return; }
			int mid = (l + r) >> 1;
			if (nl <= mid) upd(p << 1, l, mid, nl, nr, k);
			if (nr > mid) upd(p << 1 | 1, mid + 1, r, nl, nr, k);
			pushup(p, l, r);
		}
	}
	
	int n, k, a[N], rt[N], cnt[N], mn[22][N], mx[22][N]; LL ans;
	vector<pii> g[N]; vector<int> vec[N];
	vector<tuple<int, int, int>> s[N];
	
	int mex(int l, int r) { return HJT::query(rt[r], 0, n, l); }
    
	int main() {
		cin >> n >> k;
		REP(i, 1, n) {
			cin >> a[i], mx[0][i] = mn[0][i] = a[i];
			rt[i] = HJT::modify(rt[i - 1], 0, n, a[i], i);
			vec[a[i]].pb(i), g[a[i] > 0 ? 0 : 1].pb(pii(i, i));
		}
		
		auto Pre = [&](int t, int x) {
			auto it = lower_bound(vec[x].begin(), vec[x].end(), t);
			return (it == vec[x].begin() ? 0 : *prev(it)); 
		};
		auto Nxt = [&](int t, int x) {
			auto it = upper_bound(vec[x].begin(), vec[x].end(), t);
			return (it == vec[x].end() ? n + 1 : *it);
		};
		REP(i, 0, n) {
			for (pii t : g[i - 1]) {
				int l = Pre(t.fi, i - 1), r = Nxt(t.se, i - 1);
				if (l >= 1) g[mex(l, t.se)].pb(pii(l, t.se));
				if (r <= n) g[mex(t.fi, r)].pb(pii(t.fi, r));
			}
			vector<pii> tmp; int las = 1e9;
			sort(g[i].begin(), g[i].end(), [&](pii x, pii y) { return x.fi == y.fi ? x.se < y.se : x.fi > y.fi; });
			for (auto t : g[i]) if (las > t.se) tmp.pb(t), las = t.se;
			g[i].swap(tmp);
		}
		
		REP(j, 1, __lg(n)) REP(i, 1, n - (1 << j) + 1) {
			mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
			mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
		}
		auto ask = [&](int l, int r) -> pii {
			int d = __lg(r - l + 1);
			return {max(mx[d][l], mx[d][r - (1 << d) + 1]), min(mn[d][l], mn[d][r - (1 << d) + 1])};
		};
		
		REP(i, 0, n) for (auto [l, r] : g[i]) {
			if (i + k < ask(l, r).fi) continue;
			int L = l + 1, R = r - 1, Lm = Pre(l, i) + 1, Rm = Nxt(r, i) - 1;
			DEP(j, __lg(n), 0) {
				int t = L - (1 << j);
				if (t >= Lm && i + k >= ask(t, l).fi) L = t;
			}
			DEP(j, __lg(n), 0) {
				int t = R + (1 << j);
				if (t <= Rm && i + k >= ask(r, t).fi) R = t;
			}
			s[L].pb(r, R, 1), s[l + 1].pb(r, R, -1);
		}
		REP(i, 1, n) {
			for (auto [l, r, v] : s[i]) SGT::upd(1, 1, n, l, r, v);
			ans += SGT::sum[1];
		}
		
		
		REP(R, 1, n) {
			int L = R + 1;
			DEP(i, __lg(n), 0) {
				int t = L - (1 << i);
				auto [mx, mn] = ask(t, R);
				if (t >= 1 && mx - mn <= k) L = t;
			}
			ans += R - L + 1;
		}
		REP(R, 1, n) {
			int L = R + 1;
			DEP(i, __lg(n), 0) {
				int t = L - (1 << i);
				if (t >= 1 && ask(t, R).fi <= k) L = t;
			}
			ans -= R - L + 1;
		}
		
		cout << ans << '\n';
		
        return 0;
    }
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}

```

---

## 作者：ღꦿ࿐ (赞：3)

对以一个集合，一个重要的性质就是 $\text{mex}(S) \times \min(S) =0$。

- 当 $0 \in S$ 时 $\min(S)=0$

- 当 $0 \notin S$ 时 $\text{mex}(S)=0$

因此我们考虑将原式分成两种情况统计，第一种是不含有 $0$ 的区间，统计 $max - min \leq k$ 的区间个数，第二种是含有 $0$ 的区间，我们统计 $max-mex\leq k$ 的区间个数。


第一种我们可以将序列以 $0$ 隔开分段，每段内统计极差不超过 $k$ 的区间数，考虑从小到大枚举 $\max$，激活所有属于 $[max - k,max]$ 的数，那么可能 $\max(a_{[l,r]})$ 为 $a_i$ 的 $l$ 和 $r$ 分别在 $i$ 之前、之后的极长的，全部激活的段里任选，可以用数据结构维护操作支持 激活、关闭、查询之前之后的第一个未激活元素。

对于第二种区间，我们考虑扫描线地枚举 $r$，而此时 $\max(a_{[l,r]})$、$\text{mex}(a_{[l,r]})$ 均只会发生均摊 $O(n)$ 次区间赋值形态的变化，前者因为单调栈，后者是[经典套路](https://www.luogu.com.cn/problem/P4137)。

又因为 $\max(a_{[l,r]})$、$\text{mex}(a_{[l,r]})$ 都具有包含单调性，即对于相同的 $r$，$\max(a_{[l,r]})$ 和 $\text{mex}(a_{[l,r]})$ 都会随着 $l$ 的增大而减小。

于是接下来问题就变成了这样：维护两个数组 $A_i,B_i$，支持区间赋值，查询区间 $A_i+k\geq B_i$ 的 $i$ 的个数，且 $A_i,B_i$ 都**单调不增**。

区间赋值可以使用颜色段均摊成 $O(n)$ 次将全 $x$ 区间替换成全 $y$ 区间（其实这两个变化都是天然均摊地，可以不用珂朵莉树），所以我们只需要扣除掉全 $x$ 区间的贡献再加上全 $y$ 区间的贡献即可。因为 $A_i,B_i$ 都不增，考虑对于 $A$ 的一个全 $x$ 区间，可能产生贡献的 $i$ 一定是 $B_{i}$ 的 $\leq x+k$ 的一个后缀，同理对于 $B$ 的一个全 $x$ 区间可能产生贡献的 $i$ 是 $A_i$ 的一个前缀。因为两者都具有单调性，我们可以二分找到这个前缀/后缀，直接进行区间加即可。


时间复杂度 $O(n\log n)$，常数很大。

---

## 作者：Administrator_Steam (赞：1)

## Description

给一个数列 $\{a_n\}$ 和正整数 $k$，求有几组 $[l, r]$ 满足 $\mathrm{mex}(l, r) + \min(l, r) + k \geq \max(l, r)$。

## Solution

来一发不用脑子的做法。

## Part I

观察到一个性质：对于一个区间，$\mathrm{mex} = 0$ 与 $\min = 0$ 至少成立一个。证明显然。

记 $A$ 为 $\mathrm{mex} + k \geq \max$ 的区间个数，$B$ 为 $\min + k \geq \max$ 的区间个数，$C$ 为 $\max \leq k$ 的区间个数。

根据性质，简单容斥一下，答案 $ans = A + B - C$。

$B, C$ 好求，因为固定右端点后合法的左端点在一个区间内，枚举右端点二分左端点即可。这部分用 ST 表处理极值，可以做到 $O(n\log n)$。

考虑怎么求 $A$。

## Part II

你如果做过 [P9970 [THUPC 2024 初赛] 套娃](https://www.luogu.com.cn/problem/P9970) 的话，就知道一个叫「极小 mex 区间」的东西。

一个结论是这样的「极小 mex 区间」只有 $O(n)$ 个。 所以用那题的做法求出所有「极小 mex 区间」，并对每个「极小 mex 区间」求出包含它的所有区间。这部分可以做到 $O(n\log n)$。

枚举所有极小区间。对于一个极小区间 $[l, r]$，它的 $\mathrm{mex}$ 为 $p$，极大区间为 $[L, R]$，那么对于 $\forall l'\in [L, l], r' \in [r, R] $，$\mathrm{mex}(l', r') = p$。这样，$\mathrm{mex} + k$ 就固定了。二分出极大的空间 $[l', r']$，使得 $l' \in [L, l], r' \in [r, R]$ 且 $p + k \geq \max(l', r')$。

$
\forall pl \in [l', l], pr \in [r, r'], [pl, pr] \text{ 是合法区间。}
$

我们发现这样去合法区间不漏但是会重。通过关系，直接扫描线，对所有 $(l', l)(r', r)$ 组成的矩阵求面积并就行了。这部分复杂度为 $O(n\log n)$。

总复杂度 $O(n\log n)$，可以通过。码量其实没有想象中多，只有 4K 不到，而且好调。

实现的时候二分容易出错，所以把二分换成了更简洁的倍增。

## Code
```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++i)
#define DEP(i, r, l) for (int i = (r); i >= (l); --i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat
{
    typedef long long LL;
    typedef pair<LL, LL> pii;
    const int N = 5e5 + 5;

    namespace HJT
    {
        int cnt, s[N << 5], Ls[N << 5], Rs[N << 5];
        int modify(int p, int l, int r, int t, int k)
        {
            int rt = ++cnt;
            Ls[rt] = Ls[p], Rs[rt] = Rs[p];
            if (l == r)
                return s[rt] = k, rt;
            int mid = (l + r) >> 1;
            if (t <= mid)
                Ls[rt] = modify(Ls[p], l, mid, t, k);
            if (t > mid)
                Rs[rt] = modify(Rs[p], mid + 1, r, t, k);
            s[rt] = min(s[Ls[rt]], s[Rs[rt]]);
            return rt;
        }
        int query(int p, int l, int r, int k)
        {
            if (l == r)
                return l;
            int mid = (l + r) >> 1;
            if (s[Ls[p]] < k)
                return query(Ls[p], l, mid, k);
            return query(Rs[p], mid + 1, r, k);
        }
    }

    namespace SGT
    {
        LL sum[N << 3], ass[N << 3];
        void pushup(int p, int l, int r)
        {
            if (ass[p])
                sum[p] = r - l + 1;
            else
                sum[p] = sum[p << 1] + sum[p << 1 | 1];
        }
        void upd(int p, int l, int r, int nl, int nr, int k)
        {
            if (nl <= l && r <= nr)
            {
                ass[p] += k, pushup(p, l, r);
                return;
            }
            int mid = (l + r) >> 1;
            if (nl <= mid)
                upd(p << 1, l, mid, nl, nr, k);
            if (nr > mid)
                upd(p << 1 | 1, mid + 1, r, nl, nr, k);
            pushup(p, l, r);
        }
    }

    int n, k, a[N], rt[N], cnt[N], mn[22][N], mx[22][N];
    LL ans;
    vector<pii> g[N];
    vector<int> vec[N];
    vector<tuple<int, int, int>> s[N];

    int mex(int l, int r) { return HJT::query(rt[r], 0, n, l); }

    int main()
    {
        cin >> n >> k;
        REP(i, 1, n)
        {
            cin >> a[i], mx[0][i] = mn[0][i] = a[i];
            rt[i] = HJT::modify(rt[i - 1], 0, n, a[i], i);
            vec[a[i]].pb(i), g[a[i] > 0 ? 0 : 1].pb(pii(i, i));
        }

        auto Pre = [&](int t, int x)
        {
            auto it = lower_bound(vec[x].begin(), vec[x].end(), t);
            return (it == vec[x].begin() ? 0 : *prev(it));
        };
        auto Nxt = [&](int t, int x)
        {
            auto it = upper_bound(vec[x].begin(), vec[x].end(), t);
            return (it == vec[x].end() ? n + 1 : *it);
        };
        REP(i, 0, n)
        {
            for (pii t : g[i - 1])
            {
                int l = Pre(t.fi, i - 1), r = Nxt(t.se, i - 1);
                if (l >= 1)
                    g[mex(l, t.se)].pb(pii(l, t.se));
                if (r <= n)
                    g[mex(t.fi, r)].pb(pii(t.fi, r));
            }
            vector<pii> tmp;
            int las = 1e9;
            sort(g[i].begin(), g[i].end(), [&](pii x, pii y)
                 { return x.fi == y.fi ? x.se < y.se : x.fi > y.fi; });
            for (auto t : g[i])
                if (las > t.se)
                    tmp.pb(t), las = t.se;
            g[i].swap(tmp);
        }

        REP(j, 1, __lg(n))
        REP(i, 1, n - (1 << j) + 1)
        {
            mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
            mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
        }
        auto ask = [&](int l, int r) -> pii
        {
            int d = __lg(r - l + 1);
            return {max(mx[d][l], mx[d][r - (1 << d) + 1]), min(mn[d][l], mn[d][r - (1 << d) + 1])};
        };

        REP(i, 0, n)
        for (auto [l, r] : g[i])
        {
            if (i + k < ask(l, r).fi)
                continue;
            int L = l + 1, R = r - 1, Lm = Pre(l, i) + 1, Rm = Nxt(r, i) - 1;
            DEP(j, __lg(n), 0)
            {
                int t = L - (1 << j);
                if (t >= Lm && i + k >= ask(t, l).fi)
                    L = t;
            }
            DEP(j, __lg(n), 0)
            {
                int t = R + (1 << j);
                if (t <= Rm && i + k >= ask(r, t).fi)
                    R = t;
            }
            s[L].pb(r, R, 1), s[l + 1].pb(r, R, -1);
        }
        REP(i, 1, n)
        {
            for (auto [l, r, v] : s[i])
                SGT::upd(1, 1, n, l, r, v);
            ans += SGT::sum[1];
        }

        REP(R, 1, n)
        {
            int L = R + 1;
            DEP(i, __lg(n), 0)
            {
                int t = L - (1 << i);
                auto [mx, mn] = ask(t, R);
                if (t >= 1 && mx - mn <= k)
                    L = t;
            }
            ans += R - L + 1;
        }
        REP(R, 1, n)
        {
            int L = R + 1;
            DEP(i, __lg(n), 0)
            {
                int t = L - (1 << i);
                if (t >= 1 && ask(t, R).fi <= k)
                    L = t;
            }
            ans -= R - L + 1;
        }

        cout << ans << '\n';

        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Milkcat::main();
    return 0;
}

```

---

## 作者：IvanZhang2009 (赞：1)

一个大概率跟别人不一样的做法。

首先观察到 $\min$ 和 $\text{mex}$ 至少有一个是 $0$。

先考虑 $\text{mex}=0$，问题变成了极差 $\le k$，且不含 $0$ 的区间个数。极差是有单调性的，随便做。

再考虑 $\min=0$，要求区间含 $0$。考虑到这个限制不好做，正难则反，用整个序列答案减去不含 $0$ 子区间答案。

我们从小到大枚举 $\max=mx$，并实时维护 $p_l=x$ 表示最小的使区间 $[l,x]$ 满足 $\text{mex}\ge mx-k$ 的 $x$。由于 $\text{mex}$ 也有单调性，我们发现 $p_l$ 是单调递增的。

考虑 $[l,p_l]$ 的限制：$\text{mex}\ge mx-k$，当 $mx$ 变大的时候，对序列的要求是在原来的基础上**必须多包含 $mx-k-1$ 这个数**。考虑枚举 $mx-k-1$ 这个数的位置，对应的就是一段区间让 $p_l$ 进行 checkmax。考虑到 $p_l$ 的单调性，实现区间推平区间 $\max$ 进行线段树二分即可。但是我们要算很多子区间的答案，不一定能一位一位枚举 $mx$。这里对 $\text{mex}$ 和 $\max$ 的值双指针即可。

再考虑区间满足 $\max=mx$。这就是平面上矩形的形式，仍然考虑线段树二分出边界，再多维护区间和即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
int n,_,ans;
int a[500005],st[500005][24],ts[500005][24],L[500005],R[500005];
int Qst(int l,int r){
    int s=__lg(r-l+1);
    return max(ts[l][s],ts[r-(1<<s)+1][s])-min(st[l][s],st[r-(1<<s)+1][s]);
}
vector<int>occ[500005];
int mxn[2000005],seg[2000005],tag[2000005];
void build(int l,int r,int p){
    tag[p]=-1;
    if(l==r){
        seg[p]=mxn[p]=l;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,p*2+1);build(m+1,r,p*2+2);
    seg[p]=seg[p*2+1]+seg[p*2+2];mxn[p]=mxn[p*2+2];
}
void pushdown(int l,int r,int m,int p){
    if(tag[p]==-1)return;
    mxn[p*2+1]=mxn[p*2+2]=tag[p*2+1]=tag[p*2+2]=tag[p];
    seg[p*2+1]=tag[p]*(m-l+1);seg[p*2+2]=(r-m)*tag[p];
    tag[p]=-1;
}
void update(int l,int r,int s,int t,int p,int val){
    if(l<=s&&t<=r){
        seg[p]=val*(t-s+1);tag[p]=val;mxn[p]=val;
        return;
    }
    int m=(s+t)>>1;
    pushdown(s,t,m,p);
    if(m>=l)update(l,r,s,m,p*2+1,val);
    if(m<r)update(l,r,m+1,t,p*2+2,val);
    seg[p]=seg[p*2+1]+seg[p*2+2];mxn[p]=mxn[p*2+2];
}
int querysum(int l,int r,int s,int t,int p){
    if(l<=s&&t<=r)return seg[p];
    int m=(s+t)>>1,res=0;
    pushdown(s,t,m,p);
    if(m>=l)res=querysum(l,r,s,m,p*2+1);
    if(m<r)res+=querysum(l,r,m+1,t,p*2+2);
    return res;
}
int query(int l,int r,int p,int val){
    if(l==r)return mxn[p]<=val? r:l-1;
    int m=(l+r)>>1;
    pushdown(l,r,m,p);
    if(mxn[p*2+1]>val)return query(l,m,p*2+1,val);
    else return query(m+1,r,p*2+2,val);
}
void solve(int l,int r,int c){
    vector<int>m;
    REP(i,l,r+1)occ[a[i]].clear(),m.pb(a[i]);
    REP(i,l,r+1)occ[a[i]].pb(i);
    build(l,r,0);
    sort(all(m));
    m.erase(unique(all(m)),m.end());
    int x=0,mex=m.size();
    REP(i,0,m.size())if(m[i]!=i){
        mex=i;
        break;
    }
    int res=0;
    for(auto i:m)if(i-_<=mex){
        while(x<(int)m.size()&&m[x]<=i-_-1){
            if(occ[m[x]][occ[m[x]].size()-1]<r)update(occ[m[x]][occ[m[x]].size()-1]+1,r,l,r,0,n);
            int lst=l;
            for(auto j:occ[m[x]]){
                int z=query(l,r,0,j);
                if(z>=lst)update(lst,z,l,r,0,j);
                lst=j+1;
            }
            ++x;
        }
        for(auto j:occ[i]){
            int ll=query(l,r,0,j-1)+1,rr=query(l,r,0,min(R[j],r));
            ll=max(ll,max(L[j],l));rr=min(rr,j);
            if(rr<max(L[j],l))continue;
            res+=(ll-max(L[j],l))*(min(R[j],r)-j+1);
            if(ll<=rr)res+=(rr-ll+1)*(min(R[j],r)+1)-querysum(ll,rr,l,r,0);
        }
    }
    ans+=c*res;
}
void Main() {//mex-1>=max-_-1
    cin>>n>>_;
    REP(i,0,n)cin>>a[i],st[i][0]=ts[i][0]=a[i];
    stack<int>s;
    L[0]=0;s.push(0);
    REP(i,1,n){
        while(s.size()&&a[s.top()]<=a[i])s.pop();
        L[i]=s.empty()? 0:s.top()+1;
        s.push(i);
    }
    while(!s.empty())s.pop();
    R[n-1]=n-1;s.push(n-1);
    for(int i=n-2;i>=0;--i){
        while(s.size()&&a[s.top()]<a[i])s.pop();
        R[i]=s.empty()? n-1:s.top()-1;
        s.push(i);
    }
    REP(j,0,__lg(n)){
        REP(i,0,n-(1<<(j+1))+1)st[i][j+1]=min(st[i][j],st[i+(1<<j)][j]),ts[i][j+1]=max(ts[i][j],ts[i+(1<<j)][j]);
    }
    solve(0,n-1,1);
    int lst=0,cur=0;
    REP(i,0,n+1)if(a[i]==0){
        if(lst==i)++lst;
        else{
            REP(j,lst,i){
                int l=j,r=i-1,res=l-1;
                while(l<=r){
                    int mid=(l+r)>>1;
                    if(Qst(j,mid)<=_)res=mid,l=mid+1;
                    else r=mid-1;
                }
                cur+=res-j+1;
            }
        }
        lst=i+1;
    }
    lst=0;
    REP(i,0,n)if(!a[i]){
        if(lst+1<=i)solve(lst,i-1,-1);
        lst=i+1;
    }
    if(lst<=n-1)solve(lst,n-1,-1);
    cout<<ans+cur<<endl;
    // ans 是 min=0 的答案，cur 是 mex=0 的答案
}
```

---

## 作者：rainygame (赞：0)

想了大概 2h，感觉这道题有点反套路？

显然 $\min$ 和 $\operatorname{mex}$ 中必有一个为 $0$。设 $\operatorname{mex}+k\ge\max$ 的方案数为 $x$，$\min+k\ge\max$ 的为 $y$，$\max\le k$ 的为 $z$，那么有答案等于 $x+y-z$。$y,z$ 是容易求出的，现在求 $x$。

考虑枚举 $r$，计算有多少个 $l$ 满足条件。设 $v_i$ 表示最大的 $j\le r$ 满足 $a_i=j$，那么显然对于 $l\in(v_{i+1},\min\limits_{j=0}^iv_j]$，$[l,r]$ 的 $\operatorname{mex}$ 为 $i+1$。可以将问题转化为每次将某个数变大到比所有数都大，查询 $\sum\limits_i\sum\limits_{j=i}^{\min\{i+k+1,n\}}[v_j\in(v_{i+1},\min\limits_{l=0}^iv_l]]$。

注意到一定要满足 $v_{i+1}<\min\limits_{l=0}^iv_l$ 才会产生区间，且区间是不交的。考虑修改 $v_x$ 的影响，显然若 $v_x$ 不是前缀最小值，那么区间不会有变动；否则会将 $O(1)$ 个区间变为若干个区间（可以模拟理解一下）。由于同时出现的区间至多只有 $O(n)$ 个，所以显然增加的区间个数也是 $O(n)$ 的。

对于每个区间 $[l,r]$ 维护可行的 $[L,R]$ 表示对于 $i\in[L,R]$ 且 $v_i\in[l,r]$ 的 $v_i$ 对答案有贡献。用 ODT 维护 $[l,r]$。考虑修改 $v_x$ 对答案的变化。

---

## 作者：StayAlone (赞：0)

- 注意到 $\operatorname{mex}\cdot \min=0$。

于是将情况分为：

- $\operatorname{mex}(l, r)+k\geq \max(l, r)$
- $\min(l, r)+k\geq \max(l, r)$
- 发现满足 $k\geq \max(l, r)$ 的区间被计算两遍，因此需要计算出来减掉。

对于后两种区间，$l$ 固定时，$r$ 的取值为一段区间，倍增或二分即可。

对于第一种，考虑一个经典结论：极短 $\operatorname{mex}$ 区间只有 $\mathcal O(n)$ 个。

求解方式：先求出 $\operatorname{mex}=0$ 和 $\operatorname{mex}=1$ 的极短区间，长度均为 $1$。接下来，从小到大枚举 $x$，倘若 $\operatorname{mex}=x$ 的所有极短区间已被找到，则用来向后推新的极短区间。可以证明，将某 $\operatorname{mex}(l, r) = x$ 的极短区间左侧扩展到第一个 $x$，或者右侧扩展到第一个 $x$，只有这两个区间可能成为极短区间。新的区间 $\operatorname{mex}$ 需要一个主席树在线求。

这样求出的区间可能不是极短的，按照对区间右端点排序后贪心处理即可。求解极短区间的时间复杂度为 $\mathcal O(n\log n)$。

回到原问题，对于每个 $\operatorname{mex}=x$ 的极短区间 $[l, r]$，向左找到第一个 $x$，向右找到第一个 $x$，所获区间 $[L, R]$ 是一个极长区间。此时 $\forall l_0\in[L, l],r_0\in[r, R]$，均有 $\operatorname{mex}(l_0,r_0)=x$。由于区间 $\max$ 的单调性，可以倍增或二分出一个极长区间 $[l_0,r_0]$，使得 $\operatorname{mex}(l_0, r_0)+k\geq \max(l_0, r_0)$，则合法区间为 $l'\in[l_0,l],r'\in[r,r_0]$。矩形面积并即可。

倍增比较好写，常数也小。总时间复杂度 $\mathcal O(n\log n)$。

[AC record](https://www.luogu.com.cn/record/213624413)

```cpp
int n, k, a[MAXN], rt[MAXN], cnt[MAXN], mx[20][MAXN], mi[20][MAXN];
vector <int> pos[MAXN];
vector <pii> seg[MAXN], add[MAXN], del[MAXN], tmp;
ll A, B, C;

struct setr {
    int tot;
    
    struct {
        int lp, rp, mii;
    } t[MAXN * 20];

    il void pushup(int x) {
        t[x].mii = min(t[t[x].lp].mii, t[t[x].rp].mii);
    }

    il int upd(int x, int l, int r, int k, int p) {
        int now = ++tot; t[now] = t[x];
        if (l == r) return (k ? seg[0].eb(p, p) : seg[1].eb(p, p)), pos[k].eb(p), t[now].mii = p, now;
        int mid = l + r >> 1;
        if (k <= mid) t[now].lp = upd(t[x].lp, l, mid, k, p);
        else t[now].rp = upd(t[x].rp, mid + 1, r, k, p);
        return pushup(now), now;
    }

    il int query(int x, int l, int r, int k) {
        if (l == r) return l;
        int mid = l + r >> 1;
        if (t[t[x].lp].mii < k) return query(t[x].lp, l, mid, k);
        return query(t[x].rp, mid + 1, r, k);
    }
} T;

struct {
    #define ls(x) x << 1
    #define rs(x) x << 1 | 1
    int cnt[MAXN << 3], tag[MAXN << 3];

    il void pushup(int x, int l, int r) {
        cnt[x] = tag[x] ? r - l + 1 : cnt[ls(x)] + cnt[rs(x)];
    }

    il void upd(int x, int l, int r, int ql, int qr, int k) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) return tag[x] += k, pushup(x, l, r);
        int mid = l + r >> 1;
        upd(ls(x), l, mid, ql, qr, k); upd(rs(x), mid + 1, r, ql, qr, k);
        pushup(x, l, r);
    }

    il int query() { return cnt[1]; }
} T2;

il int mex(int l, int r) {
    return T.query(rt[r], 0, n, l);
}

int main() {
    read(n, k);
    rep1(i, 1, n) rt[i] = T.upd(rt[i - 1], 0, n, mx[0][i] = mi[0][i] = read(), i);
    rep1(i, 1, 19) rep1(j, 1, n - (1 << i - 1)) mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << i - 1)]), mi[i][j] = min(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
    rep1(l, 1, n) {
        int now = -1, r = l - 1;
        rep2(j, 19, 0) if (r + (1 << j) <= n && max(now, mx[j][r + 1]) <= k) gmax(now, mx[j][r + 1]), r += 1 << j;
        C += r - l + 1; r = l;
        int mn = mi[0][l], ma = mx[0][l];
        rep2(j, 19, 0) if (r + (1 << j) <= n && max(ma, mx[j][r + 1]) <= k + min(mn, mi[j][r + 1])) gmax(ma, mx[j][r + 1]), gmin(mn, mi[j][r + 1]), r += 1 << j;
        B += r - l + 1;
    }
    rep1(i, 0, n) {
        sort(begin(seg[i]), end(seg[i]), [&](const pii &x, const pii &y) {return x.snd < y.snd; }); int mxl = -1;
        for (auto [l, r] : seg[i]) if (l > mxl) tmp.eb(mxl = l, r);
        seg[i].clear(); swap(seg[i], tmp);
        for (auto [l, r] : seg[i]) {
            int L = 1, R = n;
            auto it = lower_bound(begin(pos[i]), end(pos[i]), l);
            if (it != begin(pos[i])) L = *--it + 1, seg[mex(*it, r)].eb(*it, r);
            it = upper_bound(begin(pos[i]), end(pos[i]), r);
            if (it != end(pos[i])) R = *it - 1, seg[mex(l, *it)].eb(l, *it);
            
            int now = -1, r2 = l - 1, t = i + k;
            rep2(j, 19, 0) if (r2 + (1 << j) <= R && max(now, mx[j][r2 + 1]) <= t) gmax(now, mx[j][r2 + 1]), r2 += 1 << j;
            now = -1; int l2 = r + 1;
            rep2(j, 19, 0) if (l2 - (1 << j) >= L && max(now, mx[j][l2 - (1 << j)]) <= t) gmax(now, mx[j][l2 - (1 << j)]), l2 -= 1 << j;
            if (l2 <= l && r2 >= r) add[l2].eb(r, r2), del[l + 1].eb(r, r2);
        }
    }
    rep1(i, 1, n) {
        for (auto [l, r] : add[i]) T2.upd(1, 1, n, l, r, 1);
        for (auto [l, r] : del[i]) T2.upd(1, 1, n, l, r, -1);
        A += T2.query();
    } printf("%lld", A + B - C);
    return 0;
}
```

---

## 作者：SegTree (赞：0)

注意到 $\min=0$ 和 $\text{mex}=0$ 一定恰好成立一个，考虑分讨。

## Case 1 $\text{mex}=0$
限制等价于 $\min+k\ge \max$，枚举 $\min$，然后使用 ST 表+二分求出向左或向右最远可以扩展到哪里满足条件即可。

因为是枚举 $\min$，所以每次计算的区间一定不会重复，可直接累加。
## Case 2 $\min=0$
限制等价于 $\text{mex}+k\ge\max$，枚举 $\text{mex}$，根据经典结论极短 $\text{mex}$ 区间是 $\mathcal{O}(n)$ 级别的，直接枚举这些区间并求出基于这些区间 $\text{mex}$ 向左向右最远扩展到哪里能保证 $\text{mex}$ 不变，对于前面的限制可以直接 ST 表+二分，即可得到形如 $L_1\le l\le R_1,L_2\le r\le R_2$ 的限制。

注意：这里直接将面积加和会重复，所以需要扫描线求这些矩形覆盖的面积。

实现上需要使用单调栈维护最小值的上一个和下一个更小的位置、ST 表维护区间最大值、主席树求区间 mex、线段树处理扫描线问题，常数较大，时间复杂度和空间复杂度均为 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define up(i,l,r) for(int i=(l);i<=(r);++i)
#define down(i,l,r) for(int i=(l);i>=(r);--i)
#define p_b push_back
#define pi pair<int,int>
#define m_p make_pair
#define p1 first
#define p2 second
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
inline ll read(){
    ll x=0;short t=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*t;
}
int n,K,a[maxn];
int pre[maxn],suf[maxn],stk[maxn],tp;
struct ST {
    int t[maxn][20],Log[maxn];
    void init(){
        up(i,2,n)Log[i]=Log[i>>1]+1;up(i,1,n)t[i][0]=a[i];
        up(i,1,Log[n])up(j,1,n-(1<<i)+1)t[j][i]=max(t[j][i-1],t[j+(1<<i-1)][i-1]);
    }int qry(int l,int r){
        int k=Log[r-l+1];
        return max(t[l][k],t[r-(1<<k)+1][k]);
    }
}T;
vector<pi>g[maxn];
ll getmin(){
    T.init();tp=0;
    up(i,1,n){
        while(tp&&a[stk[tp]]>a[i])tp--;
        pre[i]=stk[tp],stk[++tp]=i;
    }
    stk[tp=0]=n+1;
    down(i,n,1){
        while(tp&&a[stk[tp]]>=a[i])tp--;
        suf[i]=stk[tp],stk[++tp]=i;
    }
    ll res=0;
    up(i,1,n)if(a[i]){
        int l=pre[i]+1,r=suf[i]-1;
        int mx=a[i]+K;int w1=i,w2=i;
        down(j,19,0)if((w1+(1<<j))<=r&&T.qry(i,w1+(1<<j))<=mx)w1+=(1<<j);
        down(j,19,0)if((w2-(1<<j))>=l&&T.qry(w2-(1<<j),i)<=mx)w2-=(1<<j);
        res+=(i-w2+1)*1ll*(w1-i+1);
    }return res;
}
struct SegTree {
    int RT[maxn],ct;
    struct node {
        int ls,rs,sm;
    }d[maxn*30];
    #define ls(p) d[p].ls
    #define rs(p) d[p].rs
    #define sm(p) d[p].sm
    void pu(int p){
        sm(p)=min(sm(ls(p)),sm(rs(p)));
    }void upd(int l,int s,int t,int &p,int q,int w){
        p=++ct,d[p]=d[q];
        if(s==t){sm(p)=w;return;}
        int mid=s+t>>1;
        if(l<=mid)upd(l,s,mid,ls(p),ls(q),w);else upd(l,mid+1,t,rs(p),rs(q),w);pu(p);
    }int get_mex(int s,int t,int p,int q){
        if(s==t)return s;
        int mid=s+t>>1;
        if(sm(ls(p))>=q)return get_mex(mid+1,t,rs(p),q);return get_mex(s,mid,ls(p),q);
    }int qry(int l,int r){return get_mex(0,n,RT[r],l);}
    void bd(){up(i,1,n)upd(a[i],0,n,RT[i],RT[i-1],i);}
    #undef ls
    #undef rs
    #undef sm
}Tree;
vector<int>P[maxn];
pi binary(int pos,int w){
    pi res(1,n);
    auto it=lower_bound(P[w].begin(),P[w].end(),pos);
    if(it!=P[w].end())res.p2=(*it)-1;
    if(it!=P[w].begin())res.p1=(*(--it))+1;
    return res;
}
vector<pi>INS[maxn];
vector<pi>DEL[maxn];
struct SGT {
    struct node {
        int sm,len;
        int lz;
    }d[maxn<<3];
    #define ls(p) (p<<1)
    #define rs(p) (p<<1|1)
    #define sm(p) d[p].sm
    #define len(p) d[p].len
    #define lz(p) d[p].lz
    void pu(int p){
        if(lz(p))sm(p)=len(p);
        else sm(p)=sm(ls(p))+sm(rs(p));
    }void bd(int l,int r,int p){
        len(p)=r-l+1;
        if(l==r)return;
        int mid=l+r>>1;
        bd(l,mid,ls(p)),bd(mid+1,r,rs(p));
    }void upd(int l,int r,int s,int t,int p,int x){
        if(l<=s&&t<=r){
            lz(p)+=x,pu(p);return;
        }int mid=s+t>>1;
        if(l<=mid)upd(l,r,s,mid,ls(p),x);if(r>=mid+1)upd(l,r,mid+1,t,rs(p),x);pu(p);
    }
}S;
ll getmex(){
    up(i,1,n)if(a[i])g[0].p_b(m_p(i,i));
    up(i,1,n)if(!a[i])g[1].p_b(m_p(i,i));
    up(i,1,n)P[a[i]].p_b(i);
    Tree.bd();up(i,1,n)if(a[i]){
        if(Tree.qry(i,n)<=a[i])continue;
        int x=i;
        down(j,19,0)if(x+(1<<j)<=n&&Tree.qry(i,x+(1<<j))<=a[i])x+=(1<<j);x++;
        g[Tree.qry(i,x)].p_b(m_p(i,x));
    }up(i,1,n)if(a[i]){
        if(Tree.qry(1,i)<=a[i])continue;
        int x=i;
        down(j,19,0)if(x-(1<<j)>=1&&Tree.qry(x-(1<<j),i)<=a[i])x-=(1<<j);x--;
        g[Tree.qry(x,i)].p_b(m_p(x,i));
    }
    up(i,1,n)for(auto it:g[i]){
        auto w=binary(it.p1,i);
        int mx=i+K;if(T.qry(it.p1,it.p2)>mx)continue;
        int lt=it.p1,rt=it.p2;
        down(j,19,0)if(lt-(1<<j)>=w.p1&&T.qry(lt-(1<<j),it.p1)<=mx)lt-=(1<<j);
        down(j,19,0)if(rt+(1<<j)<=w.p2&&T.qry(it.p2,rt+(1<<j))<=mx)rt+=(1<<j);
        INS[lt].p_b(m_p(it.p2,rt)),DEL[it.p1+1].p_b(m_p(it.p2,rt));
    }S.bd(1,n,1);ll res=0;
    up(i,1,n){
        for(auto it:INS[i])S.upd(it.p1,it.p2,1,n,1,1);
        for(auto it:DEL[i])S.upd(it.p1,it.p2,1,n,1,-1);
        res+=S.d[1].sm;
    }return res;
}
void slv(){
    n=read(),K=read();up(i,1,n)a[i]=read();
    ll res1=getmin();
    ll res2=getmex();
    cout<<res1+res2;
}int main(){
    slv();
    return 0;
}
```

---

