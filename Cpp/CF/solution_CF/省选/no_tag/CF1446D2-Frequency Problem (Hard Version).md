# Frequency Problem (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is in the constraints on the array elements. You can make hacks only if all versions of the problem are solved.

You are given an array $ [a_1, a_2, \dots, a_n] $ .

Your goal is to find the length of the longest subarray of this array such that the most frequent value in it is not unique. In other words, you are looking for a subarray such that if the most frequent value occurs $ f $ times in this subarray, then at least $ 2 $ different values should occur exactly $ f $ times.

An array $ c $ is a subarray of an array $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first sample, the subarray $ [1, 1, 2, 2, 3, 3] $ is good, but $ [1, 1, 2, 2, 3, 3, 3] $ isn't: in the latter there are $ 3 $ occurrences of number $ 3 $ , and no other element appears $ 3 $ times.

## 样例 #1

### 输入

```
7
1 1 2 2 3 3 3```

### 输出

```
6```

## 样例 #2

### 输入

```
10
1 1 1 5 4 1 3 1 2 2```

### 输出

```
7```

## 样例 #3

### 输入

```
1
1```

### 输出

```
0```

# 题解

## 作者：tommymio (赞：38)

结论题。一个很常用的结论，众数与子区间的关系。

可以发现，答案子段的众数集合一定包含整个序列的众数 $X$。反证法证明：如果不包含这个众数 $X$，则说明子段众数出现次数在这个子段中，大于序列众数 $X$。因为众数 $X$ 是序列中出现最多的数，所以我们可以向左 $/$ 向右拓展这个子段，令众数的 $X$ 的出现次数不小于子段众数出现次数，这样做答案显然更优。

问题即转化为，找一个子段令其中 $X$ 的出现次数与其中另一个数出现次数相同，并且令这个子段长度最大。考虑 $\text{Easy Version}$ 的做法：枚举另一个数 $Y$，找一段 $X$ 出现次数与 $Y$ 出现次数相同的子段，时间复杂度为 $O(nV)$，其中 $V$ 为值域。

怎么优化呢？像这类与值域相关的问题，我们一般会想到根号分治。考虑那些出现次数 $> \sqrt n$ 的数，这些数的种类 $< \sqrt n$，所以可以使用 $\text{Easy Version}$ 的做法，时间复杂度为 $O(n\sqrt n)$。再考虑那些出现次数 $\leq \sqrt n$ 的数，我们枚举区间内一个数的最大出现次数，使用 $\text{two-pointer}$ 判断是否有至少两个不同的达到这个最大出现次数即可，时间复杂度为 $O(n\sqrt n)$。所以总时间复杂度就为 $O(n\sqrt n)$。

$\text{two-pointer}$ 的部分有些小细节，可以参考代码理解一下。

```cpp
#include<cstdio>
#include<cmath>
const int N=200000;
int t[N<<1|1],tmp[N<<1|1],a[N];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f; 
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
int main() {
	int n=read(),bound=sqrt(n);
	for(register int i=1;i<=n;++i) {a[i]=read(); ++t[a[i]];}
	int mode=0,mx=0;
	for(register int i=1;i<=n;++i) if(t[mode]<t[i]) mode=i;
	for(register int x=1;x<=n;++x) {
		if(t[x]>bound) {
			if(x==mode) continue;
			int cnt=0;tmp[N]=0;
			for(register int i=1;i<=n;++i) {
				if(a[i]==mode) {++cnt;}
				else if(a[i]==x) {--cnt;}
				if(tmp[cnt+N]||cnt==0) {mx=max(mx,i-tmp[cnt+N]);}
				else {tmp[cnt+N]=i;}
			}
			cnt=0;
			for(register int i=1;i<=n;++i) {
				if(a[i]==mode) {++cnt;}
				else if(a[i]==x) {--cnt;}
				tmp[cnt+N]=0;
			}
		}
	} 
	for(register int x=1;x<=bound;++x) {
		int L=1,cnt=0;
		for(register int i=1;i<=n;++i) tmp[i]=0;
		for(register int i=1;i<=n;++i) {
			++tmp[a[i]];
			if(tmp[a[i]]==x) ++cnt;
			while(L<=i&&tmp[a[i]]>x) {
				if(tmp[a[L]]==x) --cnt;
				--tmp[a[L]]; 
				++L;
			}
			if(cnt>=2) mx=max(mx,i-L+1);
		} 
	}
	printf("%d\n",mx);
	return 0; 
}
```

---

## 作者：Alan_Zhao (赞：22)

## 题意

给定正整数数列 $\{a_n\}$，求最长的子区间的长度，使得这个区间内有至少两种出现次数最多的数。

$1\le n\le 2\times 10^5$。

## 题解

**[获得更好的阅读体验](https://www.cnblogs.com/alan-zhao-2007/p/cf1446d2-sol.html)**。

来自 lxl 的 $1\log$ 做法！不过在这个数据范围下并无优势。

定义一个区间是合法的，当且仅当其中有至少两种出现次数最多的数。

首先，找到全局的众数 $m$，$m$ 一定是答案区间的两个众数之一。因为如果一个区间内 $m$ 的出现次数不是最多的，那我们一定可以向外扩充区间，找到更大的一个合法区间。

我们枚举一个 $x(x\neq m)$，并计算以 $x,m$ 为众数的最大区间。设 $x$ 的全局出现次数为 $c(x)$，若我们能在 $\mathcal{O}(c(x)\log n)$ 的复杂度内计算这个，问题就解决了。

我们将 $x$ 的所有出现位置从小到大排序。维护 $m$ 的出现位置的集合 $S$，按顺序枚举 $x$ 的所有出现位置 $p_i$，并将 $S$ 中 $>p_i$ 且最小的元素标记，然后删除。然后我们倒序枚举 $x$ 的出现位置，对于 $S$ 中的每个前驱做一遍这个操作。

例如，对于 `mxxmm` 这个序列，我们会让第一个 $x$ 标记第二个 $m$，第二个 $x$ 标记第一、三个 $m$。

这样每个 $x$ 的出现位置都标记了不超过两个 $m$，总的个数是 $\mathcal{O}(c(x))$ 的。对于那些没被标记的 $m$，我们一定不能让它出现在答案区间中。所以它们充当了分隔符的作用，对于每两个相邻的分隔符之间，计算最长的合法区间即可。

复杂度 $\mathcal{O}(\sum_x c(x)\log n)=\mathcal{O}(n\log n)$。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
typedef long long ll;
const int N=2e5+5;
int n,a[N],cnt[N];
vector<int> occ[N];
struct Point{int p,v;};
bool operator<(const Point &p1,const Point &p2){
	return p1.p<p2.p;
}
bool operator==(const Point &p1,const Point &p2){
	return p1.p==p2.p&&p1.v==p2.v;
}
bool Between(int mode,int x,int y){
	auto it=upper_bound(occ[mode].begin(),occ[mode].end(),x);
	return it!=occ[mode].end()&&*it<y;
}
int val[N*2],tot,tm[N*2];
int main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	For(i,1,n){
		cin>>a[i];
		++cnt[a[i]],occ[a[i]].push_back(i);
	}
	int mode=max_element(cnt+1,cnt+n+1)-cnt,ans=0;
	set<int> st(occ[mode].begin(),occ[mode].end());
	vector<int> del;
	For(x,1,n){
		if(x==mode||!cnt[x]) continue;
		for(int i:del) st.insert(i);
		del.clear();
		vector<Point> tg;
		for(int i:occ[x]){
			auto it=st.upper_bound(i);
			if(it!=st.end()) tg.push_back({*it,-1}),del.push_back(*it),st.erase(it);
			tg.push_back({i,1});
		}
		for(int i=occ[x].size()-1;i>=0;--i){
			auto it=st.lower_bound(occ[x][i]);
			if(it!=st.begin()) tg.push_back({*--it,-1}),del.push_back(*it),st.erase(it);
		}
		sort(tg.begin(),tg.end());
		tg.erase(unique(tg.begin(),tg.end()),tg.end());
		for(auto i=tg.begin();i!=tg.end();++i){
			auto l=i;
			for(;next(i)!=tg.end()&&!Between(mode,i->p,next(i)->p);++i);
			int lim,rim;
			auto it=lower_bound(occ[mode].begin(),occ[mode].end(),l->p),itr=upper_bound(occ[mode].begin(),occ[mode].end(),i->p);
			if(it==occ[mode].begin()) lim=0;
			else lim=*--it;
			if(itr==occ[mode].end()) rim=n;
			else rim=*itr-1;
			++tot,val[0+n]=lim,tm[0+n]=tot;
			int cur=0;
			for(auto j=l;j<=i;++j){
				cur+=j->v;
				if(tm[cur+n]==tot) ans=max(ans,(j==i?rim:next(j)->p-1)-val[cur+n]);
				else val[cur+n]=j->p,tm[cur+n]=tot;
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Alex_Wei (赞：20)

> E. [CF1446D2 Frequency Problem (Hard Version)](https://www.luogu.com.cn/problem/CF1446D2)

关键结论：原序列众数 $M$ 为答案序列众数之一，若非，可不断扩张直到 $M$ 成为区间众数之一，此时因存在其它区间众数，故合法。

根据结论，考虑枚举所有其他数 $v$，求出所有使得 $M, v$ 出现次数相同的子区间 $[l, r]$，如果存在出现次数比 $M$ 出现次数更大的数，则 $[l, r]$ 不优于答案，不会产生贡献。

求 $l, r$ 为经典套路：将 $M$ 视为 $+1$，$v$ 视为 $-1$，其它数视为 $0$，则和为 $0$ 的区间合法。据此有 $\mathcal{O}(occ(M) + occ(v))$ 求出 $M, v$ 答案的做法：初始化 $val_0 = acc = 0$，其它位置 $val_i = +\infty$。按顺序考虑所有 $M$ 或 $v$ 的出现位置 $p_1, p_2, \cdots, p_k$：

- 若 $a(p_i) = M$ 则令 $acc$ 加 $1$，否则令 $acc - 1$。
- 若 $val_{acc} = +\infty$ 则将 $val_{acc}$ 改为 $p_i$。
- 用 $p_{i + 1} - 1 - val_{acc}$ 更新答案。

第二和第三步简称用 $(acc, p_i, p_{i + 1} - 1)$ 三元组更新答案。

考虑 [SDOI2022 D1T1](https://www.luogu.com.cn/problem/P8349) 的技巧，将前缀和序列用折线描述，发现仅 $\mathcal{O}(occ(v))$ 个位置有用。下图中，实线部分可能对答案产生贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/qdin0za9.png)

考虑 $v$ 相邻的两次出现 $pre$ 与 $cur$，分别是第 $p$ 和 $p + 1$ 次。令 $pre$ 之前 $M$ 出现了 $pos$ 次，$pre$ 与 $cur$ 之间 $M$ 出现了 $num$ 次。容易发现 $pre$ 处的折线高度为 $acc = pos - p$。

令折线在 $pre$ 之前的历史最大值为 $hmax$，在 $cur$ 之后的历史最小值为 $hmin$，则对于 $pre$ 和 $cur$ 之间的上升线段而言，仅有高度 $\leq hmax$ 与 $\geq hmin$ 的部分有用。

令 $skip = \max(0, hmin - 1 - acc)$，则 $skip$ 表示当前长为 $num$ 的线段在 $skip + 1 \sim num$ 处有用，即上图 $y\sim cur$ 的部分。 

可使用小技巧避免记录 $hmax$：从 $1$ 到 $skip$ 枚举 $i$，若 $val_{acc +i} = +\infty$ 说明 $acc + i$ 已经超出 $hmax$ 范围，否则用 $(acc + i, P(M, pos + i), \min(P(M, pos + i + 1), cur) - 1)$ 更新答案，其中 $P(i, j)$ 表示 $i$ 第 $j$ 次出现在序列中的位置，若 $j$ 大于 $occ(i)$ 则视 $P(i, j) = n + 1$。

同样的，从 $skip + 1$ 到 $num$ 枚举 $i$，用上式更新答案。

最后不要忘了用 $(acc + num - 1, cur, \min(P(M, pos + num + 1), P(v, p + 2)) - 1)$ 更新答案。暂时性地令 $a_0 = a_{n + 1} = v$ 可以在一开始和最后对边界进行讨论，但当 $p = occ(v)$ 即 $cur = n + 1$ 时不能进行前一句话所描述的答案更新。

时间复杂度 $\mathcal{O}(\sum occ(v))$，即 $\mathcal{O}(n)$，比根号分治优秀不少。在洛谷上获得了最优解（2022.7.10）。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool Mbe;
constexpr int N = 2e5 + 5;
int n, a[N], occ[N], val[N << 1], ans;
vector<int> buc[N];
int P(int v, int p) {return p == buc[v].size() ? n + 1 : buc[v][p];}
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  memset(val, 0x3f, sizeof(val)), val[N] = 0;
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i], buc[a[i]].push_back(i);
  int mx = 0, oc = 0, id;
  for(int i = 1; i <= n; i++)
    if(buc[i].size() > mx) mx = buc[i].size(), oc = 1, id = i;
    else oc += buc[i].size() == mx;
  if(oc >= 2) cout << n << endl, exit(0);
  for(int it : buc[id]) occ[it] = 1;
  for(int i = 1; i <= n + 1; i++) occ[i] += occ[i - 1];
  for(int i = 1; i <= n; i++) {
    if(i == id) continue;
    if(buc[i].empty()) continue;
    static int w[N], suf[N], modi[N];
    int cnt = 0;
    for(int p = 0; p < buc[i].size(); p++) w[p] = occ[buc[i][p]] - p - 1;
    suf[buc[i].size()] = w[buc[i].size()] = buc[id].size() - buc[i].size();
    for(int p = buc[i].size() - 1; ~p; p--) suf[p] = min(w[p], suf[p + 1]);
    auto upd = [&](int v, int p, int q) {
      if(val[N + v] > N) modi[++cnt] = N + v, val[N + v] = p;
      ans = max(ans, q - val[N + v]);
    };
    for(int p = 0; p <= buc[i].size(); p++) {
      int pre = p ? buc[i][p - 1] : 0, cur = p < buc[i].size() ? buc[i][p] : n + 1;
      int pos = occ[pre], num = occ[cur] - occ[pre], acc = p ? w[p - 1] : 0;
      int skip = max(0, suf[p] - acc - 1);
      for(int q = 1; q <= skip; q++) {
        if(val[N + acc + q] > N) break;
        upd(acc + q, buc[id][pos + q - 1], min(cur, P(id, pos + q)) - 1);
      }
      for(int q = skip + 1; q <= num; q++) upd(acc + q, buc[id][pos + q - 1], min(cur, P(id, pos + q)) - 1);
      if(p < buc[i].size()) upd(acc + num - 1, cur, min(P(id, pos + num), P(i, p + 1)) - 1);
    }
    for(int p = 1; p <= cnt; p++) val[modi[p]] = 1e9;
  }
  cout << ans << endl;
  return cerr << "Time: " << clock() << "\n", 0;
}
/*
2022/7/10
start coding at
finish debugging at
*/
```

---

## 作者：Spartan117 (赞：15)

# 题意简述
- 给出$n(1 \le n \le 200000)$个元素组成的序列$a_1,a_2,……,a_n$。

- 求最长的子段使得其中有至少两个出现次数最多的元素。

- 输出最长子段长度。

# 题目分析
- 考虑取整个序列。设其中出现次数最多的元素为$D$。

- 若这样的元素有两个及以上，那么直接输出$n$。

- 如果没有，那么我们就要削减掉前缀和后缀使得满足题意。

- 考虑削减的过程，为使得满足题意，最优的时间点一定是出现了另一个元素，它与$D$同时成为了出现次数最多的元素。即，最终的答案子段中，出现次数最多的元素一定有一个是$D$。

## 证明
- 假设最终答案子段中出现次数最多的元素没有一个是$D$。

- 现在将子段向两边扩展。由于扩展到整个序列时，出现次数最多的元素一定是$D$，那么在扩展过程中，$D$的出现次数一定在某个时间点“追上”了答案子段中出现次数最多的其他元素。易知这些“追上”的时间点中一定存在满足题意的状态，此时的子段一定长于答案子段，矛盾。


现在我们已经有了一个超强的结论：最终的答案子段中，出现次数最多的元素一定有一个是$D$。

## 算法1
- 枚举另一个和$D$同为答案子段中出现次数最多的元素，设其为$X$，设总共要枚举$p_1$个元素。

- 一旦$(D,X)$确定，其答案便可在$O(n)$时间复杂度中被求出。

- 将所有值为$D$的位置放上$1$，值为$X$的位置放上$-1$，其他位置放上$0$。

- 答案即为最长的和为$0$的子段。

- 处理出序列前缀和，和每个前缀和取得的值第一次出现的位置。

- 然后扫一遍，答案即为此位置减去此位置前缀和的值第一次出现的位置。

- 总时间复杂度$O(p_1n)$

## 算法2
- 枚举答案子段中$D$出现的次数$k$，设要枚举的范围为$[1,p_2]$。

- 通过$k$可以双指针挪动（/尺取/蠕动区间）找到所有这样的子段。$O(n)$

- 由于使用双指针，子段是连续变换的，维护一个$cnt$数组变得简单至极。

- 同时要维护$cnx$数组。$cnx[cnt[i]]=cnt[i]$在cnt数组的所有元素中的出现次数。

- 这样，由于只有$cnt$上的$+1$，$-1$操作，使得我们可以$O(1)$查询$cnt[i]$中的最大元素，然后通过$cnx$判断这样的元素是否有两个及以上，即可判断合法性。

- 总时间复杂度$O(p_2n)$

## 最终算法
- 发现$p_1$和$p_2$的针对性恰好相反，考虑平衡。

- 对于出现次数$\ge \sqrt{n}$的元素，我们采用算法1。

- 其他的我们采用算法2。

- 答案即为两者中较大的。

- 最终时间复杂度：$O(n\sqrt{n})$

# 代码
```cpp
#include<bits/stdc++.h>
#define ll int
using namespace std;
const ll N=2e5+5,M=2e5;
ll n;
ll a[N];
ll cnt[N];
ll sq;
ll nb[N],cnb;
ll stx[N],fp[N<<1];
ll D;
ll ans;
ll cnn[N],cnx[N],mx;
inline ll tx(ll x,ll els){
	if(a[x]==D) return 1;
	if(a[x]==els) return -1;
	return 0;
}
inline ll calc(ll num){//求出tx数组中最长的子段使得sum=0 
	for(ll i=-n;i<=n;i++) fp[i+M]=-1;
	fp[M]=0;
	for(ll i=1;i<=n;i++){
		stx[i]=stx[i-1]+tx(i,num);
		if(fp[stx[i]+M]==-1) fp[stx[i]+M]=i;
	}
	ll rt=0;
	for(ll i=1;i<=n;i++)
		rt=max(rt,i-fp[stx[i]+M]);
	return rt;
}
inline void ins(ll x){
	--cnx[cnn[x]];
	++cnn[x];
	++cnx[cnn[x]];
	mx=max(mx,cnn[x]);
}
inline void del(ll x){
	--cnx[cnn[x]];
	--cnn[x];
	++cnx[cnn[x]];
	if(cnx[mx]==0) mx=cnn[x];
}
int main(){
	scanf("%d",&n);
	sq=512;
	for(ll i=1;i<=n;i++){
		scanf("%d",a+i); 
		++cnt[a[i]];
		if(cnt[a[i]]>cnt[D]) D=a[i];
	}
	 
	for(ll i=1;i<=n;i++){
		if(i==D||cnt[i]<sq) continue;
		ans=max(ans,calc(i));
	}
	for(ll k=1;k<=sq;k++){
		for(ll i=1;i<=n;i++) cnn[i]=cnx[i]=0; 
		ll nd=0;cnx[0]=n;mx=0;
		for(ll i=1,j=1;i<=n;i++){
			while(j<=n&&nd+(a[j]==D)<=k) ins(a[j]),nd+=(a[j]==D),++j;
			if(cnx[mx]>=2) ans=max(ans,j-i);
			del(a[i]);
			nd-=(a[i]==D);
		}
	}
	printf("%d\n",ans);
	puts("Don't Copy");
	return 0;
}

```




---

## 作者：Celtic (赞：14)

一篇复杂度为 $O(n)$ 的题解（含代码）。

首先特判掉有两个全局众数的情况，此时答案为 $n$。

容易发现的是全局的众数一定是答案区间的众数之一，感性理解考虑最优解一定是将全局范围一点一点缩小到有一个数和全局众数的出现次数相同。

那么可以枚举另一个出现次数和全局众数相同的数。设全局众数为 $x$，枚举的这个数为 $y$，那么如果将 $a_i=x$ 的位置设为 $1$， $a_i=y$ 的位置设为 $-1$，其他位置设为 $0$，此时问题就等价于找到一个最长的区间，他的区间和为 $0$。（当然这样可能有不合法的区间，但是由于 $x$ 一定是最优解中的众数所以不合法的区间一定不优，不用考虑）

这个问题有一个很经典的操作就是对于每个 $a_i=y$，将他加入一个数组中，再找到他前面和后面当前的第一个 $a_i=x$，将他也加入这个数组中再从原序列中删掉，然后对这个数组求一下最长的合法子段，求前驱和后继可以用 `set`，但是这样复杂度会多一个 $\log n$，不优秀。

我们观察上面的操作其实就是在找前缀和 $\ge0$ 的位置，那么我们可以维护一个 $cur$ 表示当前的前缀和，然后用链表往后跳最近的 $x$ 或 $y$，如果 $cur=0$ 那么我们就强制跳到下一个 $y$ （不管中间的 $x$）。这样正着做一次再反着做一次，然后归并一下就可以做到 $O(n)$。

具体细节见[代码](https://codeforces.com/contest/1446/submission/162509664)（~~由于我比较懒使用了 `unordered_map` 所以常数不优秀，可以用 `bool` 数组来代替~~）


---

## 作者：zhoukangyang (赞：14)

[来蒟蒻的博客园里看 /kel](https://www.cnblogs.com/zkyJuruo/p/14097060.html)

给出一个跑得快一点的做法，洛谷最优解 (时间是第二名的 $\frac{1}{2}$), CF 第一页

## D1

首先找到整个序列的众数 $G$, 很容易证明答案序列中的两个众数中其中一个是 $G$ 。

知道了这个结论以后，我们可以枚举在序列中出现的数 $K$, 让 $G$ 的权值为 $1$, $K$ 的权值为 $-1$, 然后就找一下最长的权值为 $0$ 的串即可。这个开个桶统计即可。

这个和大家一样，就不多说了。

Code(片段) :

```cpp
const int N = 2e5 + 7;
int n, a[N], cnt[N], zs, ans, fir[N << 1];
void work(int x) {
	int now = N;
	memset(fir, -1, sizeof(fir));
	fir[now] = 0;
	L(i, 1, n) {
		if(a[i] == zs) now ++;
		else if(a[i] == x) now --;
		if(fir[now] == -1) fir[now] = i;
		else ans = max(ans, i - fir[now]);
	}
}
int main() {
	scanf("%d", &n);
	L(i, 1, n) scanf("%d", &a[i]), cnt[a[i]] ++;
	L(i, 1, n) if(cnt[i] > cnt[zs]) zs = i;
	L(i, 1, min(n, 100)) if(i != zs) work(i); 
	printf("%d\n", ans);
	return 0;
}
```

## D2

同样令众数为 $G$。

根号分治。

对于出现次数 $> B$ 的数，可以像 $D1$ 一样处理。

对于出现次数 $\le B$ 的数 (设为 $K$)（重点）：

设出现次数为 $cnt$。

首先可以枚举选中的序列的第一个出现 $K$ 的位置是 $K$ 的第几次出现的位置。

然后发现这个序列中包含的 $G$ 的个数一定 $\le cnt$。

于是我们可以只考虑枚举的这个位置前面的 $cnt$ 个 $G$ (不能包含上一个数字 $K$) 和后面 $cnt$ 个 $G$ (可以包含后面的数字 $K$) ，然后按照 $D1$ 的方法做即可。

有一些细节，具体见代码。

Code :

```cpp
#include<bits/stdc++.h>
#define L(i, j, k) for(int i = j, i##E = k; i <= i##E; i++) 
#define R(i, j, k) for(int i = j, i##E = k; i >= i##E; i--)
#define ll long long
#define ull unsigned long long 
#define db double
#define pii pair<int, int>
#define mkp make_pair
using namespace std;
char buf[256],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,256,stdin),p1==p2)?EOF:*p1++)
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch)) { if(ch=='-') f = -1; ch = getchar(); }
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return x * f;
}
const int N = 2e5 + 7;
const int B = 233;
int n, a[N], cnt[N], zs, ans;
int fir[N << 1];
int max(int x, int y) { return x > y ? x : y; }
void worka(int x) {
	int now = N;
	memset(fir, -1, sizeof(fir));
	fir[now] = 0;
	L(i, 1, n) {
		if(a[i] == zs) now ++;
		else if(a[i] == x) now --;
		if(!~fir[now]) fir[now] = i;
		else ans = max(ans, i - fir[now]);
	}
}
int lef[N], rig[N], f[N], fg[N];
vector<int> ve[N];
void workb(int x) {
	L(i, 1, cnt[x]) {
		fill(fir + N - cnt[x] - 2, fir + N + cnt[x] * 2 + 3, -1);
		int tot = 0, las = (i == 1 ? 0 : ve[x][i - 2]), now = ve[x][i - 1], len = 0;
		while(lef[now - 1] > las && len <= cnt[x]) now = lef[now - 1], ++len, f[++tot] = now;
		int dd = i, KK = N;
		if(!lef[now - 1] && i == 1) fir[N] = 0;
		reverse(f + 1, f + tot + 1);
		f[++tot] = ve[x][i - 1], fg[tot] = 1;
		now = ve[x][i - 1], len = 0;
		while(rig[now + 1] && len <= cnt[x]) {
			now = rig[now + 1];
			while(dd < cnt[x] && ve[x][dd] < now) f[++tot] = ve[x][dd], fg[tot] = 1, ++ dd;
			++len, f[++tot] = now;
		}
		if(len <= cnt[x]) while(dd < cnt[x]) f[++tot] = ve[x][dd], fg[tot] = 1, ++ dd;
		f[tot + 1] = n + 1;
		if(rig[now + 1]) f[tot + 1] = rig[now + 1];
		L(j, 1, tot) {
			if(fg[j] == 1) -- KK, fg[j] = 0; else ++ KK;
			if(!~fir[KK]) fir[KK] = f[j];
			else ans = max(ans, f[j + 1] - 1 - fir[KK]); 
		}
	}
}
int main() {
	n = read(); 
	L(i, 1, n) a[i] = read(), cnt[a[i]] ++;
	L(i, 1, n) if(cnt[i] > cnt[zs]) zs = i;
	L(i, 1, n) if(a[i] == zs) lef[i] = rig[i] = i;
	L(i, 1, n) if(!lef[i]) lef[i] = lef[i - 1];
	R(i, n, 1) if(!rig[i]) rig[i] = rig[i + 1];
	L(i, 1, n) if(cnt[a[i]] <= B) ve[a[i]].push_back(i);
	L(i, 1, n) if(i != zs) {
		if(cnt[i] > B) worka(i); 
		else workb(i);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：FreshP_0325 (赞：8)

提出一个 $O(n)$ 的解法。

有个简单结论是，最终选出的子段中的众数包含全局众数。证明很简单，也就是如果当前的子段的众数不包含全局众数，我们可以扩大这个子段使得全局众数的出现次数和子段内出现次数最多的其他数出现一样多，显然更优。

一般的做法是考虑根号分治，分出现次数大于 $\sqrt n$ 的和不满 $\sqrt n$ 的考虑。前者可以直接 $O(n)$ 暴力复杂度 $O(n \sqrt n)$，后者采取双指针也能做到 $O(n \sqrt n)$。总时间复杂度 $O(n \sqrt n)$。

考虑优化。注意到我们确定了一个众数 $c$，再枚举区间内的一个其他的众数 $d$，那么将 $c$ 看做 $1$，$d$ 看做 $-1$，其他看做 $0$，我们需要找到一个和为 $0$ 的子段。我们抽出这样一段并让单点带权，问题的形式已经被完全转化成[此题](https://www.luogu.com.cn/problem/P8349)，并有了比较优秀的性质：每次查询的 $x$ 有一个相等。

我们直接采用上面提及的题目中大数对小数的做法，维护可能在子段中的 $1$ 的集合。枚举其他的所有众数后，集合的大小也不过 $O(n)$。这样直接算就好了。

时间复杂度最终取决于造出集合的时间复杂度。暴力删点是 $O(n \log n)$ 的。注意到我们并不需要实时回答问题，可以分开维护向左和向右取的全局众数，用栈维护全局众数若干个连续的连续段集合即可。

---

## 作者：duyi (赞：8)

[勇敢向前进，前进有奖品！](https://www.cnblogs.com/dysyn1314/p/14007922.html)

# CF1446D1, D2 Frequency Problem

## 题目大意

[题目链接](https://codeforces.com/contest/1446/problem/D2)

有一个长度为 $n$ 的序列 $a_1,a_2,\dots ,a_n$。

我们定义一个子段（连续子序列）是好的，当且仅当其中出现次数最多的元素不唯一。

请求出，最长的、好的子段的长度。

数据范围：$1\leq n\leq 2\times10^5$。对于 D1，$1\leq a_i\leq \min(n,100)$，对于 D2，$1\leq a_i\leq n$。

## 本题题解

### D1

如果原序列里，出现次数最多的数不唯一，则答案就是 $n$。否则，考虑那个唯一的、出现次数最多的元素，记为 $x$。

发现，最长的、好的子段（也就是答案），有个必要条件是：$x$ 是其中出现次数最多的元素之一。

证明：考虑一个好的子段 $[l,r]$，如果 $x$ 不是其中出现次数最多的元素。那么，我们依次考虑 $[l-1,r]$, $[l-2,r]$, ... ..., $[1,r]$, $[1,r+1]$, $[1,r+2]$, ... ..., $[1,n]$。因为 $x$ 的数量每次最多增加 $1$ 个，且它是整个序列里出现次数最多的元素。那么总有某一步后，$x$ 和序列里其他出现最多的元素一样多。

我们枚举，答案的子段里，和 $x$ 出现次数一样多的元素是谁，记为 $y$。问题转化为，对一组数值 $(x,y)$ 计算答案。

我们可以忽略数列里除 $x$, $y$ 外的其他数。问题进一步转化为：求一个最长的子段，满足 $x$, $y$ 的出现次数一样多。

把数列里的 $x$ 看做 $1$，$y$ 看做 $-1$，其他数看做 $0$。得到一个序列 $b$。那么，我们要求最长的、和为 $0$ 的子段长度。做前缀和，令 $\text{sum}_i=\sum_{j=1}^{i}b_j$。问题相当于找两个位置 $0\leq l < r\leq n$，满足 $\text{sum}_r = \text{sum}_l$。对每个 $\text{sum}$ 值 $v$（$[-n,n]$，共 $2n+1$ 个值）记录它最早的出现位置。然后枚举 $r$，并更新答案即可。

有读者可能对“忽略数列里除 $x$, $y$ 外的其他数”这一做法心存疑虑。因为有可能，我们找到的序列里，存在一个其他数值 $z$，出现次数多于 $x,y$。但是，基于以下两点：

1. 存在这样 "$z$" 的子段，长度一定小于答案。证明：我们按和上面同样的方法，向两边扩展一下，直到 $x$ 和 $z$ 出现次数相等。得到的序列仍然满足：存在两个数 $(x,z)$ 出现次数相等，且新的子段长度比原来长。所以只要存在这样的 "$z$"，我们就扩展一下，最终一定能得到没有 "$z$" 的，也就是以 $x$ 为出现次数最多的数的子段，且长度一定严格大于原来的子段。
2. 答案的子段，一定会被考虑到。因为只要满足 $x$, $y$ 出现次数相等，就会被考虑到。

我们用这种方法，求出的就是答案。

时间复杂度 $O(n\times\text{maxa})=O(n\times 100)$。可以通过 D1。

### D2

考虑答案序列里，出现次数最多的数，的出现次数。如果出现次数 $>\sqrt{n}$，则满足条件的数值只有不超过 $\sqrt{n}$ 个，我们套用 D1 的做法，时间复杂度 $O(n\sqrt{n})$。

如果出现最多的数，出现次数 $\leq \sqrt{n}$，我们枚举这个出现次数，记为 $t$。然后做 two pointers。

具体来说，枚举区间的右端点 $r$。对每个 $r$，记最小的，使得 $[l,r]$ 内所有数出现次数都 $\leq t$ 的 $l$ 为 $L_r$。容易发现，对于 $r=1,2,\dots,n$，$L_r$ 单调不降。并且，在当前的 $t$ 下，对一个 $r$ 来说，如果 $[L_r,r]$ 不是好的子段（出现次数为 $t$ 的数值，不到 $2$ 个），那么其他 $[l,r]$ ($L_r<l\leq r$) 也不可能是。因为出现次数为 $t$ 的数值，只会更少。

所以，随着我们从小到大枚举 $r$，只需要用一个变量来记录当前的 $L_r$。同时用数组维护一下，当前每个数的出现次数，以及**每个出现次数**的出现次数。就能确定，当前的 $[L_r,r]$ 是否是好的区间。具体可以见代码。这个 two pointers 的过程是 $O(n)$ 的。因为有 $\sqrt{n}$ 个 $t$，所以这部分的时间复杂度也是 $O(n\sqrt{n})$。

总时间复杂度 $O(n\sqrt{n})$。

## 总结

本题首先需要一个结论。通过观察、分析题目性质，是可以想到的。

然后需要一个技巧：把一个普通序列，转化为只含 $0$, $1$, $-1$ 的序列。这样就把复制的、出现次数的关系，转化为了简单的数值关系。这个技巧，在一些经典的，二分中位数的题里也有用到（把 $> \text{mid}$ 的视为 $1$，$\leq \text{mid}$ 的视为 $-1$）。

在 D2 里，想到根号分治以后，应该就不是太难了。

## 参考代码(both D1 & D2)


[我要开飞机！！！我要当经理！！！](https://www.cnblogs.com/dysyn1314/p/14007922.html)


---

## 作者：TonyYin (赞：5)

[更好的阅读体验](https://www.tonyyin.top/2021/12/cf1446d2/)

根号分治好题。

## 题意

给出一个序列 $a_1, a_2\cdots, a_n$，求最长的子段，使得其中有至少两个出现次数最多的元素。

输出子段的长度，$1\leq n\leq 2\times 10^5$.

## 题解

#### 引理及证明

> 众数：一个序列中出现次数最多的数，可以有多个。

首先有一个关于众数的结论：**答案子段的众数集合，一定包含原序列的众数。**

可以通过**反证法**来证明：

记 $x$ 是原序列的众数，**假设存在**子段 $a_l, a_{l+1}, \cdots, a_r$ 是题目所求的最长子段，且子段的众数不包含 $x$.

根据众数的定义，在 $a_{[1, l-1]}$ 和 $a_{[r+1, n]}$ 中一定还包含 $x$。不妨设左侧包含 $x$，即 $\exists a_p=x, p\in[1, l-1]$.

**考虑将子段 $a_{[l, r]}$ 向两侧扩展，把 $a_p$ 包含进去**，这样使子段长度变大，下面说明一定存在方案可以包含 $a_p$.

把 $a_{[l, r]}$ 扩展为 $a_{[p,r]}$ 后，

- 若其众数的出现次数**不变**，则 $a_{[p,r]}$ 即为更优答案。
- 若其众数的出现次数**增加**，那么我们继续扩展，使更多的 $x$ 被包含进去。由于 $x$ 是整个序列中出现次数最多的数，所以把 $x$ 一个一个加进去，最后就变成了上面的情况，可以满足条件。

因此，我们总可以找到一个比 $a_{[l,r]}$ 更优的答案，**假设不成立**。

所以结论成立。

#### 思路

先找到序列 $a$ 的众数 $x$，若存在多个众数，则答案为 $n$.

对答案中**众数的出现次数**进行根号分治，分别采用不同的方法处理。

设 $\operatorname{C}$ 为**答案子段的众数的出现次数**，$x,y$ 表示答案子段的众数，$\operatorname{cnt_i}$ 为值 $i$ 在序列 $a$ 中的出现次数。

下面进行分类讨论。

#### $\operatorname{C} > \sqrt{n}$ 的情况

由于答案子段一定包含众数 $x$，且 $\operatorname{C}>\sqrt{n}$，所以 $y$ 也满足 $\operatorname{cnt}_y>\sqrt{n}$.

显然，满足这个条件的 $y$ 最多有 $\sqrt{n}$ 个，考虑枚举 $y$。

只需在 $\mathcal{O}(n)$ 的复杂度内**求出：以 $(x,y)$ 作为众数的最大子段长度**。

此时问题只与 $x,y$ 这两个值有关，需要用到一个常见套路，**让 $x$ 的权值为 $1$，$y$ 的权值为 $-1$，其余为 $0$**.

只需在新序列中找：数值和为 $0$ 的最长子段。

对新数列维护前缀和 $s_i$，子段 $[l,r]$ 的数值和为 $0$ 等价于：$s_r=s_{l-1}$，只需记录每个 $s_i$ 的最早出现位置即可。

```cpp
// 1. 答案区间中众数的出现次数 > sqrt(n)，枚举所有可行的数值check
for(int i = 1; i <= n; i++) if(cnt[i] >= Sqrt && i != mxval) {
    memset(L, 0, sizeof(L)); L[0 + N] = 0;
    for(int j = 1; j <= n; j++) {
        s[j] = s[j - 1] + (a[j] == mxval ? 1 : (a[j] == i ? -1 : 0));
        if(!L[s[j] + N] && s[j]) L[s[j] + N] = j; //注意这里下标可能为负，所以要都加上N
        else ans = max(ans, j - L[s[j] + N]);
    }
}

```

注意 $s_i\in[-n, n]$，记录最早出现位置的数组，下标需要整体 $i\leftarrow i+n$.

#### $\operatorname{C} \leq \sqrt{n}$ 的情况

考虑枚举 $\operatorname{C}$，只需在 $\mathcal{O}(n)$ 的复杂度内**求出：众数出现次数为 $\operatorname{C}$ 的最大子段**。

这可以用**双指针**解决，**细节有点多**。

```cpp
// 2. 答案区间中众数的出现次数 <= sqrt(n)，枚举所有可行的答案，双指针判断是否合法
for(int C = 1; C <= Sqrt; C++) {
    memset(cnt, 0, sizeof(cnt));
    for(int l = 1, r = 1, C_cnt = 0; r <= n; r++) {
        cnt[a[r]]++; if(cnt[a[r]] == C) C_cnt++;
        while(l <= r && cnt[a[r]] > C) {
            if(cnt[a[l]] == C) C_cnt--;
            cnt[a[l++]]--;
        }
        if(C_cnt >= 2) ans = max(ans, r - l + 1);
    }
}
```

在上面的代码中，$\operatorname{C_{cnt}}$ 代表出现次数为 $\operatorname{C}$ 的数的个数，动态维护桶。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10, N = 2e5;
int n, a[MAXN], ans;
int L[MAXN << 1], s[MAXN]; //情况一，L[i]为前缀和i第一次出现的下标，s[i]为前缀和
int cnt[MAXN]; //情况2，对于目前的尺取区间，cnt是对a[]的桶
int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	int Sqrt = (int)(sqrt(n));
	for(int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
	int mxcnt = 0, mxval = -1;
	for(int i = 1; i <= n; i++) {
		if(cnt[a[i]] > mxcnt) mxcnt = cnt[a[i]], mxval = a[i];
		else if(cnt[a[i]] == mxcnt && a[i] != mxval) mxval = n + 1;
	}
	if(mxval == n + 1) { cout << n << endl; return 0; } //若众数有俩，直接输出n
//	1. 答案区间中众数的出现次数 > sqrt(n)，枚举所有可行的数值check
	for(int i = 1; i <= n; i++) if(cnt[i] >= Sqrt && i != mxval) {
		memset(L, 0, sizeof(L)); L[0 + N] = 0;
		for(int j = 1; j <= n; j++) {
			s[j] = s[j - 1] + (a[j] == mxval ? 1 : (a[j] == i ? -1 : 0));
			if(!L[s[j] + N] && s[j]) L[s[j] + N] = j; //注意这里下标可能为负，所以要都加上N
			else ans = max(ans, j - L[s[j] + N]);
		}
	}
//	2. 答案区间中众数的出现次数 <= sqrt(n)，枚举所有可行的答案，双指针判断是否合法
	for(int C = 1; C <= Sqrt; C++) {
		memset(cnt, 0, sizeof(cnt));
		for(int l = 1, r = 1, C_cnt = 0; r <= n; r++) {
			cnt[a[r]]++; if(cnt[a[r]] == C) C_cnt++;
			while(l <= r && cnt[a[r]] > C) {
				if(cnt[a[l]] == C) C_cnt--;
				cnt[a[l++]]--;
			}
			if(C_cnt >= 2) ans = max(ans, r - l + 1);
		}
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：panyf (赞：5)

首先发现一个性质，记 $m$ 为整个序列的众数，则 $m$ 一定是某个所求最长子段的众数。假设 $m$ 不是，那么存在一个 $x$ 在子段中出现次数比 $m$ 多，可以扩大子段使得 $x$ 和 $m$ 的出现次数相同。

枚举子段中的另一个众数 $x$，将 $x$ 视为 $-1$，$m$ 视为 $1$，其他数视为 $0$，问题转化为求一个最长子段满足和为 $0$。用一个数组 $w$ 存最小的 $w_i$ 满足长度为 $w_i$ 的前缀和为 $i$，从小到大枚举 $j$，则 $ans$ 和 $j-w_{sum}$ 取 $\max$，其中 $sum$ 为长度为 $j$ 的前缀和。这样就可以以 $cnt_x+cnt_m$ 的复杂度解决，其中 $cnt_x$ 表示原序列中 $x$ 出现的次数。

考虑优化掉这个 $cnt_m$。假设我们选择了一段 $x$，第一个为 $l$，最后一个为 $r$，$[l,r]$ 内共有 $k$ 个 $x$。那么我们考虑大于 $l$ 的最小的 $k$ 个 $m$，和小于 $r$ 的最大的 $k$ 个 $m$，那么 $x$ 和 $m$ 数量相同的子段，一定只会包含这两部分 $m$ 中的 $k$ 个。

从小到大枚举 $x$ 的位置 $p$，找到大于 $p$ 的第一个 $m$，然后删掉。将删掉的 $m$ 还原，再从大到小枚举 $p$，找到小于 $p$ 的第一个 $m$，然后删掉。只有这些 $m$ 是有用的，复杂度就从 $\sum cnt_x+cnt_m$ 优化到 $\sum cnt_x$，也就是 $O(n)$。预处理 $pr_i,nx_i$ 分别表示小于/大于 $i$ 的第一个 $m$ 的位置，这样找到有用的 $m$ 的过程就可以线性了。然后合并有用的 $m$ 和 $x$ 的位置，可以用归并。注意如果两个有用的 $m$ 之间存在没用的 $m$，那么答案子段不能跨过没用的 $m$。

```cpp
#include<bits/stdc++.h>
using namespace std;
enum{N=200009};
int a[N],n,m,ans,c[N],pr[N],nx[N],id,vv[N*2],ww[N*2],*v=vv+N,*w=ww+N;
basic_string<int>g[N],p,p0,p1,p2;
int main(){ios::sync_with_stdio(0);cin.tie(0);
	int i,j,o,l=0,t,k,x;
	cin>>n;
	for(i=1;i<=n;++i)cin>>a[i],g[a[i]]+=i,++c[a[i]];
	for(i=1;i<=n;++i)if(c[i]>c[m])m=i;//求众数
	for(i=1;i<=n;++i){
		pr[i]=l;
		if(a[i]==m)l=i;
	}
	for(l=n+1,pr[l]=l,i=n;i;--i){
		nx[i]=l;
		if(a[i]==m)l=i;
	}//预处理pr，nx
	for(i=1;i<=n;++i)if(i!=m&&g[i].size()){//这里的i就是题解中的x
		l=0,p1=p2={};
		for(int o:g[i]){
			l=max(nx[l],nx[o]);
			if(l>n)break;
			p1+=l;
		}
		l=n+1;
		for(j=g[i].size()-1;~j;--j){
			o=g[i][j],l=min(pr[l],pr[o]);
			if(!l)break;
			p2+=l;
		}//找到有用的m，存入p1和p2
		reverse(begin(p2),end(p2)),p0.resize(p1.size()+p2.size()),merge(begin(p1),end(p1),begin(p2),end(p2),begin(p0));
		p.resize(g[i].size()+p0.size()),merge(begin(p0),end(p0),begin(g[i]),end(g[i]),begin(p)),l=0,x=p.size();//归并
		for(j=0;j<x;++j){
			if(o=p[j],j+1<x&&o==p[j+1])continue;
			if(!l||(a[o]==m&&a[l]==m&&pr[o]!=l)){
				if(v[t=0]=++id,a[o]==m)w[t]=pr[o]+1;
				else w[t]=1;
			}else if(v[t]<id)v[t]=id,w[t]=l+1;
			if(a[o]==m)++t;else --t;//t表示当前的前缀和sum，w[t]表示最小的位置满足前缀和为t
			if(v[t]==id){//不能跨过没用的m，如果v[t]<id就表示跨过了没用的m
				if(j+1<x)k=p[j+1]-1;else k=n;
				k=min(k,nx[o]-1),ans=max(ans,k-w[t]+1);
			}
			l=o;
		}
	}
	cout<<ans;
}
```


直接套用这个做法应该可以通过 [P8349 [SDOI/SXOI2022] sequence](https://www.luogu.com.cn/problem/P8349)。

---

## 作者：vectorwyx (赞：1)

首先看全局的众数是否唯一，如果不唯一答案肯定为 $n$。否则令 $x$ 为全局众数。

然后考虑从 $[1,n]$ 开始不断缩小子段直到众数不唯一，由于每个数的出现次数一定是**连续变化**的，且**在此之前**得到的子段里众数是唯一的，所以这时候 $x$ 也一定是众数之一。换句话说，最长子段里 $x$ 一定仍为众数。这也表明如果有一个区间内 $x$ 不是众数，那么一定有一个更大的 $x$ 是不唯一众数的区间包含了它。

一个很自然的想法是枚举另一个众数 $y(y\not=x)$ 然后计算贡献。把 $y$ 看做 $+1$，$x$ 看做 $-1$，其余位置看做 $0$，问题变成求最长的和为零的子段。把 $x,y$ 的出现位置拎出来做前缀和，复杂度为 $O(a+b)$，其中 $a$ 为 $x$ 的出现次数，$b$ 为 $y$ 的出现次数，如果 $a>>b$ 就会被卡。

但是 $a>>b$ 的情况下会有很多 $x$ 根本不可能包含在答案区间内。仔细感受一下会发现多出来的 $x$ 大概会把序列分割成若干个小段，只有这些小段里的位置是有意义的。这个东西具体怎么描述呢？如果说对于某个位置上的 $x$，以它为结尾和以它为开头的所有区间里 $x$ 出现次数均大于 $y$，那么一定没有一个合法区间跨过了它。这个有点像括号匹配，我们可以正着扫一遍，把每个 $+1$ 之前的离它最近的 $-1$ 删掉。那么如果一个 $-1$ 在扫完之后没有被删掉，以它为起点的所有区间的和一定都小于零。倒着扫一遍同理，两次都没被删掉的点一定不可能出现在答案区间里。显然被删掉的点数是 $O(b)$ 的，我们对这些点加上所有 $y$ 的点形成的连续段分别做前缀和，复杂度就是 $O(b)$ 的。删点可以用 set 维护，总复杂度为 $O(n\log n)$。

具体实现看代码：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5;
int a[N],n,l[N],r[N],t[N],pre[N],suf[N],mx,rp,we,S[N],ans,ti;
pii vis[2][N];
vector<int> g[N];
set<int> s;
#define It set<int>::iterator

void deal(int v){
	//printf("deal(%d)\n",v);
	vector<int> wyx;wyx.pb(1),wyx.pb(n);
	++ti;
	It it;
	//for(It qwq=s.begin();qwq!=s.end();++qwq) cout<<*qwq<<' ';puts("");
	for(int i:g[v]){
		wyx.pb(i);//,wyx.pb(i-1),wyx.pb(i+1);
		it=s.lower_bound(i);
		if(it!=s.begin()){
			--it;
			l[i]=*it;
			s.erase(it);
		}
	}
	for(int i:g[v]) if(l[i]) 
		s.insert(l[i]),wyx.pb(pre[l[i]]+1);//,wyx.pb(l[i]),wyx.pb(l[i]-1),wyx.pb(l[i]+1);
	for(int i:g[v]){
		it=s.lower_bound(i);
		if(it!=s.end()){
			r[i]=*it;
			s.erase(it);
		}
	}
	for(int i:g[v]) if(r[i]) 
		s.insert(r[i]),wyx.pb(suf[r[i]]-1);//,wyx.pb(r[i]),wyx.pb(r[i]-1),wyx.pb(r[i]+1);
	sort(wyx.begin(),wyx.end());
	wyx.erase(unique(wyx.begin(),wyx.end()),wyx.end());
	int cnt=0;
	//cout<<"positions:";for(int i:wyx) cout<<i<<' ';puts("");
	for(int i:wyx)if(i>0&&i<=n){
		pii &j=vis[cnt<S[i-1]][abs(cnt-S[i-1])];
		if(j.se<ti) j=mk(i,ti);
		if(a[i]==v) cnt++;
		int x=cnt-S[i];
		if(vis[x<0][abs(x)].se==ti) big(ans,i-vis[x<0][abs(x)].fi+1);
	}
}

signed main(){
	cin>>n;
	fo(i,1,n) a[i]=read(),g[a[i]].pb(i),t[a[i]]++;
	fo(i,1,n) big(mx,t[i]);
	fo(i,1,n) if(t[i]==mx) rp++,we=i;
	if(rp>1) return cout<<n,0;
	int x=0;
	fo(i,1,n){
		if(a[i]==we) S[i]=S[i-1]+1,s.insert(i),pre[i]=x,x=i;
		else S[i]=S[i-1];
	}
	x=0;
	go(i,n,1) if(a[i]==we) suf[i]=x,x=i;
	//printf("we=%d    S:",we);out(S,1,n);
	fo(i,1,n) if(i!=we) deal(i);
	cout<<ans;
	return 0;
}
/*
20
13 16 6 13 19 7 18 5 17 8 11 13 19 11 19 18 18 13 14 1
-------------------------------------------------
19
*/

```


---

## 作者：whiteqwq (赞：1)

[CF1446D1 Frequency Problem (Easy Version)](https://www.luogu.com.cn/problem/CF1446D1)&[CF1446D2 Frequency Problem (Hard Version)](https://www.luogu.com.cn/problem/CF1446D2)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1758352)

## 题意
- 给定一个长度为$n$的序列，定义好的序列为众数不唯一的序列，求最长的好的连续子序列。
- 数据范围：$1\leqslant n\leqslant 2\times 10^5$，$1\leqslant a_i\leqslant n$，对于Easy Version，$a_i\leqslant 100$。

## 分析
首先有一个结论：**最长的众数不唯一的子序列一定包含整个序列的众数**。

反证法：设整个序列的众数为$x$，如果这个子序列中众数不含有$x$，那么我们尝试每次给这个子序列扩展一个位置（如果扩展不了那么众数一定含有这个$x$），因为$x$为整个序列的众数，每一次扩展会最多让$x$增加$1$，所以总有一个时间$x$的数量会等于当前序列众数的数量，此时这个序列满足条件，且它一定优于原来的序列。

有了这个结论，我们先求得整个序列的众数$x$，如果众数不唯一，那么答案就是$n$，否则我们继续分析：

先考虑Easy Version，因为$a_i$的值域为$[1,100]$，所以我们直接枚举这个众数（设为$y$），然后重构一个新序列$b$：

- 当$a_i=x$时，$b_i=1$；
- 当$a_i=y$时，$b_i=-1$；
- 否则，$b_i=0$。

对于一个满足条件的序列，**它的$x$出现次数与$y$的出现次数一定相等**，因此我们可以统计所有$b$之和为$0$的序列进答案。

但是这里有一个疑问：如果在某一个区间中存在一个数$z$，出现次数比$x$和$y$均多，那这样的序列是否合法？

还是可以用上面的那种扩展的方法，发现一定存在一个更长的序列众数为$x,z$，且比刚才的序列更优，因此刚刚的序列被统计了也不会对最终答案造成影响。

这样我们就用$O(maxa\times n)$的复杂度解决了Easy Version。

对于Hard Version，观察数据范围，我们可以考虑进行根号分治。

设定一个阈值$S$，对于出现次数大于$S$的数字，它的个数一定不会超过$\frac{n}{S}$，因此我们可以用一个$\text{vector}$存下所有出现次数大于$S$的数字，然后用Easy Version的方法暴力统计答案，时间复杂度$O(n\sqrt{n})$。

然后，对于出现次数小于等于$S$的数字，我们很显然可以**枚举这个出现次数**（设为$i$），然后对于整个序列做一遍$\text{two pointer}$，里面**维护所有数的出现次数**和**出现次数的出现次数**，只要出现次数$i$的出现次数大于等于$2$，我们就统计这个答案。这样我们可以用$O(n\sqrt{n})$的复杂度解决问题。

时间复杂度：$O(n\sqrt{n})$。

## 代码
Easy Version:
```
#include<stdio.h>
#define inf 1000000000
const int maxn=200005,maxk=105;
int n,maxx,cnt,ans;
int a[maxn],tot[maxk],sum[maxn],t[maxn*2];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int max(int a,int b){
	return a>b? a:b;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tot[a[i]]++;
	}
	for(int i=1;i<=100;i++){
		if(tot[i]==maxx)
			cnt++;
		if(tot[i]>maxx)
			cnt=1,maxx=tot[i];
	}
	if(cnt>1){
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<=100;i++)
		if(tot[i]==maxx){
			maxx=i;
			break;
		}
	for(int i=1;i<=100;i++){
		for(int j=1;j<=n;j++)
			sum[j]=sum[j-1]+(a[j]==i? -1:(a[j]==maxx? 1:0));
		for(int j=-n;j<=n;j++)
			t[n+j]=inf;
		for(int j=1;j<=n;j++){
			ans=max(ans,j-t[n+sum[j]]+1);
			t[n+sum[j-1]]=min(t[n+sum[j-1]],j);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

Hard Version
```
#include<stdio.h>
#include<math.h>
#include<vector>
#define inf 1000000000
using namespace std;
const int maxn=200005,maxt=505;
int n,maxx,cnt,ans,S,val;
int a[maxn],tot[maxn],sum[maxn],t[maxn*2],cnt1[maxn],cnt2[maxn];
vector<int>v;
inline void modify(int x,int v){
	cnt2[cnt1[x]]--;
	cnt1[x]+=v;
	cnt2[cnt1[x]]++;
}
int main(){
	scanf("%d",&n),S=sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tot[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(tot[i]==maxx)
			cnt++;
		if(tot[i]>maxx)
			cnt=1,maxx=tot[i];
	}
	if(cnt>1){
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(tot[i]==maxx)
			val=i;
		else if(tot[i]>S)		
			v.push_back(i);
	}
	for(int i=0;i<v.size();i++){
		int k=v[i];
		for(int j=1;j<=n;j++)
			sum[j]=sum[j-1]+(a[j]==k? -1:(a[j]==val? 1:0));
		for(int j=-n;j<=n;j++)
			t[n+j]=inf;
		for(int j=1;j<=n;j++){
			ans=max(ans,j-t[n+sum[j]]+1);
			t[n+sum[j-1]]=min(t[n+sum[j-1]],j);
		}
	}
	for(int i=1;i<=S;i++){
		for(int j=1;j<=n;j++)
			cnt1[j]=cnt2[j]=0;
		int l=1,r=0;
		while(r<n){
			r++,modify(a[r],1);
			while(cnt1[a[r]]>i)
				modify(a[l],-1),l++;
			if(cnt2[i]>=2)
				ans=max(ans,r-l+1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lightup37 (赞：0)

## 题意

给定一个序列 $\{a_i\}$，求其中最长的合法区间。一个区间合法当且仅当其中的众数不唯一。

## 解法

考察极长合法且不靠边的区间的性质。如果其两边至少有一个数不是此区间中的众数，我们显然可以让这个区间向那个方向延长 1 格，所以这个区间必然不是极长的。

如果两边都是这个区间的众数且不相等，那么显然可以让区间同时向左右各延长 1 格，所以这个区间也不是极长的。

所以极长合法且不靠边的区间，其两边必然是相等的数，并且那个数一定是这个区间中的众数之一。

为了消除歧义，接下来称极长合法且不靠边的区间的众数为其两侧的那个数。

接下来考虑到如果一个区间 $[l, r]$ 是极长合法且不靠边的区间，其众数为 $k$，那么必然 $[L, R](L \leq l, R\geq r, [L, R]\not=[l, r])$ 都不合法。也即所有包含 $[l, r]$ 的区间，其必然有唯一的众数。容易发现除非 $k$ 是全局众数，必然存在这样的一个区间 $[L, R]$ 包括 $[l, r]$，使得 $[L, R]$ 的唯一众数不是 $k$。不妨设那个数是 $t$。考虑将 $L$ 移动到 $l-1$, 将 $R$ 移动到 $r+1$ 的过程中，区间中 $t$ 的出现次数减去 $k$ 的出现次数。下称为区间的价值。若 $L$ 或 $R$ 移动 1 步，区间的价值至多变化 1。又因为起始时区间的价值大于 0，结束时区间的价值为 -2，所以必然存在一个中间状态，区间的价值为 0。这与假设（$[l, r]$ 是极长合法且不靠边的区间）不符。

由此我们得知了可能是(极长合法且不靠边的区间)的区间 $[l, r]$ 的性质：

- 包含全局众数 $k$, 且 $a_{l-1} = a_{r+1} = k$，且 $[l, r]$ 的众数为 $k$;

- 存在一个数 $t$, $t$ 和 $k$ 在 $[l, r]$ 中的出现次数相等。

由此我们得到了一个算法：枚举每个 $[l, r]$ 区间的 $t$，对于每个右端点 $R$，找到位置最前的左端点使得 $[L, R]$ 中，$t$ 和 $k$ 的出现次数相等。这样的区间数量是 $O(n)$ 的。值得注意的是不需要考虑这些区间是否合法：因为如果这个区间是不合法的，那么肯定不优（不包含全局众数）。

<https://codeforces.com/contest/1446/submission/189158202>

我们考虑对于区间中包含的全局众数个数根号分治。如果区间中包含的全局众数的数量不多于 $T$，容易在 $O(Tn)$ 的时间复杂度内计算出这些区间中最长合法且不靠边区间的长度。

否则只需要考虑那些总共出现次数多于 $T$ 的数，这些数的个数是不多于 $n/T$ 的。对于这些数做 D1 的算法即可。

取 $T = \sqrt n$，得到时间复杂度 $O(n\sqrt n)$。

<https://codeforces.com/contest/1446/submission/189181040>

笔者代码中没有考虑到“不需要考虑这些区间是否合法”。

---

## 作者：Piwry (赞：0)

## 解析

设整个序列的众数 $\texttt{D}$

首先考虑一个引理：答案子串的众数一定包含 $\texttt{D}$

证明考虑反证。若答案子串的众数不包含 $\texttt{D}$，我们考虑左右 “扩张”（即一个个添加元素）子串；不难发现最后 $\texttt{D}$ 一定会成为子串的众数。由于每次 “扩张” 仅添加一个数字，因此一定有 $\texttt{D}$ 刚成为众数的时刻，和添加该数前的众数数量相等（注意这时的众数可能不是原来答案子串的众数）；不难发现这时的子串也是一种答案，并比原来更优

先考虑下 Easy Version 怎么做

不难想到枚举另一个众数 $k$。我们考虑将数字为 $k$ 的序列位置的权设为 $-1$，数字为 $\texttt{D}$ 的序列位置的权设为 $-1$，其它位置的权则设为 $0$；设前缀和 $s_i$，我们就相当于要找到一个 $s_r-s_{l-1}=0$，那么 $[l, r]$ 就是一种答案

可能会有人觉得不能简单地忽略其它数字。其实只需考虑这样两个事实：

1. 这样算出的答案一定不会比最优的答案更大
2. 设 $[l, r]$ 为最优答案的子串，我们一定会统计到它

这里仅具体说明下 $1.$；主要令人迷惑的点是在 $k, \texttt{D}$ 实际上不为众数时怎么办。其实只需考虑刚才我们提到的引理，“答案子串的众数一定包含 $\texttt{D}$”

接着解决 Hard Version

结合 Easy Version 的限制，不难想到可以考虑根号分治的做法

具体来说，对于出现次数超过 $\sqrt n$ 的数字，我们直接套用 Easy Version 的方法做——这样的数字不会超过 $\sqrt n$ 个

对于出现次数不超过 $\sqrt n$ 的数字，我们抛掉刚才的方法，考虑枚举答案子串的众数出现次数。具体来说，不难发现众数的出现次数随着子串长度的增加是**不减**的，于是就可以直接双指针搞

具体实现时只需注意我们不能直接维护众数具体的值，从而用来查询众数的出现次数（维护众数值不好搞）；而是转而直接维护众数的出现次数，因为每次移动指针时其变化不会超过 $1$

还有一些实现方式及细节问题可参考代码

## CODE

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
using std::max;

const int MAXN =2e5+20, MAXS =450;

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

int a[MAXN];
int D, cnt[MAXN], cnt_cnt[MAXN]/*每个出现次数的出现次数 \fad*/;

int pos_s[MAXN<<1];

int main(){
	int n =read(), S =sqrt(n), Max_Val =0;
	for(int i =0; i < n; ++i){
		a[i] =read(), ++cnt[a[i]];
		if(cnt[a[i]] > cnt[D])
			D =a[i];
		Max_Val =max(Max_Val, a[i]);
	}
	
	int ans =0;
	
	for(int k =1; k <= Max_Val; ++k)
		if(k != D && cnt[k] > S){
			int s =0;
			memset(pos_s, -1, sizeof(pos_s));
			pos_s[(int)2e5+ 0] =0;
			for(int i =0; i < n; ++i){
				if(a[i] == D)
					s +=1;
				else if(a[i] == k)
					s -=1;
				
				// 某个前缀和第一次出现的地方 //
				// 因为统计时我们要贪心取最左的 //
				if(pos_s[(int)2e5+ s] == -1)
					pos_s[(int)2e5+ s] =i+1;
				
				if(pos_s[(int)2e5+ -(-s)] != -1)
					ans =max(ans, i-(pos_s[(int)2e5+ -(-s)]-1 +1)+1);
			}
		}
	
	for(int d_limit =1; d_limit <= S; ++d_limit){
		int max_cnt =0;
		memset(cnt, 0, sizeof(cnt));
	//	cnt_cnt[0] =cnt_different_val;/*<<- 这个其实可以不用管*/
		// 可以发现区间众数个数随区间增大单调不减，因此可以双指针 //
		// 注意这里不直接维护众数，因为不好处理；转而直接维护众数的出现次数 //
		for(int l =0, r =0; l < n; ++l){
			while(r < n && max(max_cnt, cnt[a[r]]+1) <= d_limit){
				--cnt_cnt[cnt[a[r]]], ++cnt[a[r]], ++cnt_cnt[cnt[a[r]]];
				max_cnt =max(max_cnt, cnt[a[r]]);
				++r;
			}
			
			if(cnt_cnt[max_cnt] >= 2)
				ans =max(ans, r-l);
			
			--cnt_cnt[cnt[a[l]]], --cnt[a[l]], ++cnt_cnt[cnt[a[l]]];
			if(cnt_cnt[max_cnt] == 0)
				--max_cnt;/*可知 max_cnt 一定恰好减小一*/
		}
	}
	
	printf("%d", ans);
}
```

---

