# Beautiful Sequence Returns

## 题目描述

我们称一个整数序列为美丽的，当且仅当其满足以下条件：
- 对于除第一个元素外的每个元素，其左侧存在一个比它小的元素；
- 对于除最后一个元素外的每个元素，其右侧存在一个比它大的元素；

例如，$[1, 2]$、$[42]$、$[1, 4, 2, 4, 7]$ 和 $[1, 2, 4, 8]$ 是美丽的，但 $[2, 2, 4]$ 和 $[1, 3, 5, 3]$ 不是。

注意：子序列是指通过删除原序列中某些元素（可能为零个）而不改变剩余元素顺序得到的新序列。

给定一个长度为 $n$ 的整数数组 $a$。请找出数组 $a$ 的最长美丽子序列，并输出其长度。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1
42
5
1 2 3 4 5
6
6 5 4 3 2 1
7
1 1 3 4 2 3 4
6
2 3 1 1 2 4```

### 输出

```
1
5
1
5
3```

# 题解

## 作者：Zzzcr (赞：2)

把点放平面上，有用的左端点是前缀严格 min，有用的右端点是后缀严格 max，把这些端点重标号，考虑对中间的每个点算贡献。容易发现这相当于 $l\in[a,b]\wedge r\in[c,d]$ 的矩形加一，最后查一下全局 max，扫描线维护即可。

---

## 作者：Hooch (赞：1)

子序列合法的充要条件是 $a_1, a_n$ 分别为严格最小和最大值。

那么可以转化成：有 $n$ 个点 $(i, a_i)$，求出 $i, j$ ( $i < j \land a_i < a_j$ ) 使得点 $(i, a_i + 1)$ 和 $(j, a_j - 1)$ 矩形中框住的点最多。

对于 $(i, a_i)$，如果它的左下角有点，那么它作为矩形的左下角一定不优，同理，对于 $(j, a_j)$，如果它右上角有点，那么它作为矩形右上角一定不优。

所以我们可以分离出两个下降的点对序列 $l, r$，也就是序列的前缀最小值和后缀最大值。

枚举 $l$ 中的每个点并将其作为矩形左下角，用线段树维护 $r$ 中每个点作为矩形右上角的答案，考虑由 $l_i$ 到 $l_{i + 1}$ 有哪些点的贡献会有变化：

+ 若 $l_i < j \le l_{i + 1}$，那么 $j$ 的贡献应当减去。
+ 若 $a_{l_i} \ge a_j > a_{l_{i + 1}}$，那么 $j$ 的贡献应当加上。

由于每个 $j$ 都是对序列 $r$ 中的一段区间产生贡献，可以二分出这个区间然后线段树区间加。贡献计算完毕后求线段树全局 $\max$ 即可。

时间复杂度 $\mathcal{O}(n \log n)$。

代码：

```cpp
//seg.add(l, r, v) : 将区间 [l, r) 加上 v。
//seg.query(l, r) : 查询区间 [l, r) 的最大值。
//seg.modify(i, v) ：将位置 i 赋值为 0。

void solve() {
	cin >> n;

	bool dec = 1;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		if (i > 0 && a[i - 1] < a[i]) {
			dec = 0;
		}
	}
	if (dec) {
		cout << 1 << "\n";
		return ;
	}

	vector<int> l, r;
	for (int i = 0; i < n; ++i) {
		if (l.empty() || a[i] < a[l.back()]) {
			l.push_back(i);
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		if (r.empty() || a[i] > a[r.back()]) {
			r.push_back(i);
		}
	}

	for (int i = 0; i < r.size(); ++i) {
		seg.modify(i, 0);
	}

	vector<int> ord(n);
	iota(ord.begin(), ord.end(), 0);
	sort(ord.begin(), ord.end(), [&](int x, int y) {
		return a[x] > a[y];
	});

	auto add = [&](int i, int v) {
		int p = upper_bound(r.begin(), r.end(), i, [&](int x, int y) {
			return a[x] < a[y];
		}) - r.begin();
		int q = lower_bound(r.begin(), r.end(), i, greater()) - r.begin();
		seg.add(p, q, v);
	} ;

	int ans = 0;
	for (int i = 0, ptr = 0; i < l.size(); ++i) {
		while (ptr < n && a[ord[ptr]] > a[l[i]]) {
			if (ord[ptr] > l[i]) {
				add(ord[ptr], 1);
			}
			++ptr;
		}
		ans = max(ans, seg.query(0, r.size()).max);
		if (i + 1 < l.size()) {
			for (int j = l[i]; j < l[i + 1]; ++j) {
				if (a[j] > a[l[i]]) {
					add(j, -1);
				}
			}
		}
	}

	cout << ans + 2 << "\n";
}
```

---

## 作者：未来姚班zyl (赞：1)

这道题和 [AT_joi2013ho5 Bubble Sort](https://www.luogu.com.cn/problem/AT_joi2013ho5) 几乎一模一样，这是[我的题解](https://www.luogu.com.cn/article/q9ennsl9)。真可惜我参加的不是这场 ECR。

首先一个序列合法的充要条件是第一位是严格最小值，最后一位是严格最大值，因为如果它们出现在序列中间就会违反条件。否则它们会自然地使中间的数满足条件。

所以我们的子序列形如找到 $l<r,a_l<a_r$，然后把下标在 $[l+1,r-1]$，值域在 $[a_l+1,a_r-1]$ 的点全部选上，我们可以把第 $i$ 个点视为 $(i,a_i)$，则这个相当于矩阵数点。

考虑一个微不足道的贪心，如果存在 $l'<l,a_{l'}\le a_l$，则 $l'$ 一定优于 $l$。所以最优解的 $l$ 一定满足 $a_l$ 是**严格前缀最小值**。右端点 $r$ 的选择同理，应为**严格后缀最大值**。（简直和我引用的原题一模一样）。

提取可能做为最优解的 $l$ 和 $r$，我们发现左端点的 $a_i$ 随 $i$ 单调递减，右端点也一样。

有什么用呢，单调性！

我们把矩阵数点转为求每个点对矩阵的贡献，这时候我们发现，对于位置 $i$，它能够产生贡献的左端点 $l$ 和右端点 $r$ 都是一段区间！所以可以对右端点扫描线，维护左端点的贡献，用线段树维护区间加和全局最大值，复杂度 $O(n\log n)$。

我看赛时很多人吃了罚时，应该是扫描线后忽略了 $a_l<a_r$ **且 $l<r$**，这个应该要特判一下。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,nb
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){if(b<0)b+=mod;((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){add(b,mod);return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,a[N],b[N],nb,c[N],nc,mx[N],mn[N];
struct seg{
	int mx,laz;
}xd[N<<2];
inline void insert(int x,int k){
	xd[x].mx+=k,xd[x].laz+=k;
}
inline void getup(int x){
	xd[x].mx=max(xd[L].mx,xd[R].mx);
}
inline void pushdown(int x){
	insert(L,xd[x].laz),insert(R,xd[x].laz),xd[x].laz=0;
}
inline void build(int x,int l,int r){
	xd[x]={0,0};
	if(l==r)return;
	build(lc),build(rc);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k){
	if(OK)return insert(x,k);
	pushdown(x);
	if(Ll<=mid)modify(lc,Ll,Rr,k);
	if(Rr>mid)modify(rc,Ll,Rr,k);
	getup(x);
}
struct node{
	int l,r,k;
};
vector<node>d[N];

inline void Main(){
	n=read(),nb=nc=mx[n+1]=0,mn[0]=inf;
	repn(i)a[i]=read(),mn[i]=min(mn[i-1],a[i]);
	per(i,n,1)mx[i]=max(a[i],mx[i+1]);
	repn(i)if(mn[i]!=mn[i-1])b[++nb]=i;
	repn(i)if(mx[i]!=mx[i+1])c[++nc]=i;
	repn(i){
		int l=1,r=nb,Ll=n+1,Rr=-1,tl=n+1,tr=-1;
		while(l<=r)if(a[b[mid]]<a[i])Ll=mid,r=mid-1;
		else l=mid+1;
		l=1,r=nb;
		while(l<=r)if(b[mid]<i)Rr=mid,l=mid+1;
		else r=mid-1;
		if(Ll>Rr)continue;
		l=1,r=nc;
		while(l<=r)if(a[c[mid]]>a[i])tr=mid,l=mid+1;
		else r=mid-1;
		l=1,r=nc;
		while(l<=r)if(c[mid]>i)tl=mid,r=mid-1;
		else l=mid+1;
		if(tl>tr)continue;
		d[tl].pb({Ll,Rr,1}),d[tr+1].pb({Ll,Rr,-1});
		
	}
	int ans=1;
	bool fl=0;
	rep(i,1,n-1)if(mn[i]<mx[i+1])fl=1;
	if(!fl){
		rep(i,1,n+1)d[i].clear();
		return puts("1"),void();
	}
	build(Root);
	rep(i,1,nc+1){
		for(auto y:d[i])modify(Root,y.l,y.r,y.k);
		d[i].clear();
		ans=max(ans,xd[1].mx+2);
	}
	cout <<ans<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：cyh_qwq (赞：1)

思路十分钟，调试两小时。

首先我们可以将题面转换为：有一个长为 $n$ 的序列，定义 $(i,j)$ 的贡献为区间 $(l,r)$ 中大于 $a_i$ 且小于 $a_j$ 的数的数量加上**起点和终点的贡献**，求最大的 $(i,j)$ 值。

乍一看似乎不太可做，因为要考虑所有的 $i$ 和 $j$，因此考虑能对答案产生贡献的 $i$ 和 $j$ 具有什么性质。注意到有这么一个性质：如果子序列的最左边选择了 $k$ 位置，那么对于所有的 $s$ 满足 $s>k$ 且 $a_s>=a_k$ 来说，选 $k$ 比选 $s$ 做序列左端是更优的。所以我们就得到了一个新的左端点序列，端点序列里的元素都满足在原序列中没有一个在他前面的值小于等于它。而对于右端点同理，满足在原序列中没有一个在它后面的值大于等于它。

这样做法就比较显然了，先用单调栈搞出端点序列。这里我是从在左端点序列中从右往左确认最左边（也就是 $i$），用线段树维护右端点序列，维护选择当前左端点时的最值。设当前的左端点在原序列中的位置为 $x$ 上一个为 $y$，考虑需要进行哪些操作：对于位置 $z$，如果 $z$ 满足 $z>y$，$a_y<a_z<a_x$,需要撤回它的贡献，因此做一个区间减 $1$ 的操作；对于位置 $z$，如果 $z$ 满足 $x<y<z$，$a_z>a_x$,会对某些右端点产生 $1$ 的贡献，又因为右端点序列对应的 $a$ 值和位置是单减的，因此可以线段树二分。

还有一点细节，当最大值为 $1$ 的时候，线段树的写法是很难判断的。又因为最大值为 $1$ 时，序列是单调不增的，因此可以直接特判。

下面是具体实现：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<cstring>
#define lc (p<<1)
#define rc ((p<<1)|1)
#define ll long long
using namespace std;
const int N=5e5+10;
inline int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}
int T,maxx,sss;
int n,a[N],b[N],tot,c[N],d[N];
int maxn[N<<2],tag[N<<2],cnt;
bool flag;
inline bool cmp(int x,int y){
	return a[x]<a[y];
}
stack<int> st;
inline void pd(int p){
	tag[lc]+=tag[p];
	maxn[lc]+=tag[p];
	tag[rc]+=tag[p];
	maxn[rc]+=tag[p];
	tag[p]=0;
}
inline void up(int p){
	maxn[p]=max(maxn[lc],maxn[rc])+tag[p];
}
inline void build(int l,int r,int p){
	maxn[p]=tag[p]=0;
	if(l==r)return;
	register int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
} 
inline void add1(int l,int r,int k,int val,int p){
	if(k<=b[l]){
		tag[p]+=val;
		maxn[p]+=val;
		return;
	}
	register int mid=(l+r)>>1;
	pd(p);
	if(k<=b[mid])add1(l,mid,k,val,lc);
	if(k<=b[r])add1(mid+1,r,k,val,rc); 
	up(p);
}
inline void add2(int l,int r,int k,int val,int p){
	if(k<=b[l]&&a[k]<a[b[r]]){
		tag[p]+=val;
		maxn[p]+=val;
		return;
	}
	if(l==r)return;
	register int mid=(l+r)>>1;
	pd(p);
	if(k<=b[mid]&&a[k]<a[b[l]])add2(l,mid,k,val,lc);
	if(k<=b[r]&&a[k]<a[b[mid+1]])add2(mid+1,r,k,val,rc); 
	up(p);
}
inline int qy(int l,int r,int k,int p){
	if(k<=b[l]){
		return maxn[p];
	}
	register int mid=(l+r)>>1,res=0;
	pd(p);
	if(k<=b[mid])res=max(res,qy(l,mid,k,lc));
	if(k<=b[r])res=max(res,qy(mid+1,r,k,rc));
	return res;
}
int main(){
	register int i,x,p,it,lst;
	T=read();
	a[0]=1000000000;
	while(T--){
		n=read();
		flag=1;
		maxx=0;
		while(!st.empty())st.pop();
		for(i=1;i<=n;++i){
			a[i]=read();
			if(a[i-1]<a[i])flag=0;
			while(!st.empty()&&a[st.top()]<=a[i])st.pop();
			c[i]=i;
			st.push(i);
		}
		if(flag){
			printf("1\n");
			continue;
		}
		sort(c+1,c+1+n,cmp);
		tot=st.size();
		for(i=tot;i>=1;--i){
			b[i]=st.top();
			st.pop();
		}
		for(i=n;i>=1;--i){
			while(!st.empty()&&a[st.top()]>=a[i])st.pop();
			st.push(i);
		}
		cnt=st.size();
		for(i=cnt;i>=1;--i){
			d[i]=st.top();
			st.pop();
		}
		it=1,lst=n+1;
		for(i=1;i<=cnt;++i){
			x=d[i];
			while(it<=n&&a[c[it]]<=a[x]){
				if(c[it]>=lst)add1(1,tot,c[it],-1,1);
				++it;
			}
			while(lst!=x){
				lst--;
				if(a[lst]>a[x])add2(1,tot,lst,1,1);
			}
			maxx=max(qy(1,tot,x,1)+2,maxx);
		}
		build(1,tot,1); 
		printf("%d\n",maxx);
	}
}
```

---

## 作者：Halberd_Cease (赞：1)

逆天题序 F<<E。

题目很好往二维平面上刻画，如当是序列中每一个数代表一个点，坐标为 $(i,a_i)$，需要选择两个数 $x,y$ 使得横坐标在 $(x,y)$ 且纵坐标在 $(a_x,a_y)$ 的点的个数最大。

也就是选择一个点作为左下角，一个点作为右上角，然后求严格在这两个点中间的矩形包含的点。

有一个比较显然的观察，就是如果 $i<j$，$a_i \le a_j$，那么我们一定不会选择 $j$ 作为矩形的左下角，这个比较显然。

于是我们可以处理出所有可能作为矩形左下角的点，这些点一定满足 $i<j$ 那么 $a_i>a_j$。

然后考虑平面上任意一个点可能被以哪些点为左下角的矩形包含，容易发现需要满足 $x<now$ 且 $a_x<a_{now}$，其中 $now$ 是当前点的坐标，$x$ 是可以作为左下角的点。

画一下图可以知道这些点在之前预处理出的可能作为矩形左下角的点的序列中呈一个连续的子段。这个性质十分的重要也十分优美，我们可以用一段区间 $[l,r]$ 来刻画每一个点可以被包含进以哪些点为左下角的矩形。每个点的 $l,r$ 都可以使用二分查找求出。

所有能作为右上角的点按相同方式处理。

于是题目转化成了这样一个问题：每个点有 $4$ 个值 $ld,rd,lu,ru$，选择两个数 $d,u$ 使得 $ld\le d\le rd$ 且 $lu\le u\le ru$ 的点的个数最多。

这个东西就可以直接线段树扫描线做了，将 $d$ 部分看作时间轴，对于每个点，在 $ld$ 时线段树上将 $[lu,ru]$ 区间整体 $+1$，$rd$ 时将区间整体 $-1$，每个时刻求线段树上所有点的最大值。

注意特殊情况：如果所有数全部单调不升，那么答案为 $1$ 特判掉即可。

[submission](https://codeforces.com/contest/2075/submission/311501002)

---

## 作者：masonpop (赞：0)

没脑子做法。

首先序列合法等价于 $a_l<a_r$，且中间的数全部落在开区间 $(a_l,a_r)$ 里面。

注意到若 $i<j,a_i<a_j$ 则 $j$ 永远不可能作为左端点，对于右端点同理。于是可以先把能作为左/右端点的点提取出来，在二维平面上表现为左右端点均单调。

考虑对于一个点 $i$，能对哪些区间 $[l,r]$ 产生贡献，容易发现其对应二维平面上一个矩形。于是就是矩形加整体查最值，扫描线即可。

$O(n\log n)$。代码没啥难度。

---

## 作者：TheForsaking (赞：0)

首先，一个合法序列等同于第一个数是整个序列中唯一最小值，而最后一个数是唯一最大值的序列。

观察后可以发现，对于一个位置 $i$，如果在它前面存在一个位置 j 满足 $a_j \le a_i$，那么以 $i$ 作为序列的左端点的答案肯定不会优于以 $j$ 作为左端点，因此我们只需要考虑左端点是前缀最小值的序列。

我们从左往右枚举每一个前缀最小值作为序列的左端点，在固定了合法的左端点 $i$ 后，只考虑 $i$ 右侧那些满足 $a_j > a_i$ 的点 $j$，每个这样的 $j$ 都会对 $j$ 右侧所有值比 $a_j$ 大的位置产生 $1$ 点贡献。对于每个点 $j$，定义其累计贡献值为 $C(j)$，则以 $i$ 作为序列左端点的最长合法序列长度为 $\max_{\substack{j>i \\ a_j > a_i}} C(j) + 2$。

由于一个位置右侧比自己值更大的位置有 $O(n)$ 个，若对每个位置逐一更新显然会超时。令 $\lg_i = \max\{\, j \in \{i+1, i+2, \ldots, n\} \mid a_j > a_i \,\}$，即 $\lg_i$ 为满足 $j > i$ 且 $a_j > a_i$ 中最大的下标，在固定序列左端点 $i$ 后，对于每一个合法位置 $j$（满足 $j > i$ 且 $a_j > a_i$），用对 $[j + 1,lg_j]$ 这个区间增加 $1$ 点贡献来代替原来对每个位置逐个增加贡献的操作，这样做会使得一些位置的累计贡献增多，但是并不会影响 $\max_{\substack{j>i \\ a_j > a_i}} C(j)$ 的值。

证明： \
固定左端点 $i$ 后，对于每一个合法位置 $j$，我们令其贡献区间 $I(j) = [j + 1, lg_j]$。令 $M = \max_{\substack{j>i \\ a_j > a_i}} C(j)$，我们把累计贡献为 $M$ 的位置集合分成两部分：

- $S_e$：获得了额外贡献的位置
- $S_n$：没有获得额外贡献的位置

如果 $S_n \neq \varnothing$，则两种操作的 $\max_{\substack{j>i \\ a_j > a_i}} C(j)$ 是相同的。假设 $S_n = \varnothing$，即所有累计贡献为 $M$ 的位置属于 $S_e$，令 $u = \max\{ t \mid t \in S_e \}$，由于 $u \in S_e$，存在至少一个贡献区间 $I(j)$ 使得 $j + 1 \le u < lg_j$ 且 $a_{lg_j} > a_j \ge a_u$，由于 $lg_j > u$ 且 $a_{lg_j} > a_u$，那么对于任意包含 $u$ 的贡献区间，其右端点都严格大于 $u$，所有包含 $u$ 的贡献区间也包含 $u + 1$，因此 $C(u + 1) \ge C(u) = M$，由于 $u = \max\{ t \mid t \in S_e \}$，所以 $u + 1 \in S_n$，这与假设 $S_n = \varnothing$ 矛盾，因而至少存在一个贡献值为 $M$ 的位置属于 $S_n$。

代码：

```
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int N = 2000086, MOD = 998244353, INF = 0x3f3f3f3f;
int n, m, cnt, w[N];

struct Node {
    int l, r, max, flag;
}tr[N << 2];
void pushup(int u) { tr[u].max = max(tr[u << 1].max, tr[u << 1 | 1].max); }
void pushdown(Node& u, Node& l, Node& r) { l.max += u.flag, r.max += u.flag, l.flag += u.flag, r.flag += u.flag, u.flag = 0; }
void pushdown(int u) { pushdown(tr[u], tr[u << 1], tr[u << 1 | 1]); }

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].max;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1, res = 0;
    if (l <= mid) res = query(u << 1, l, r);
    if (r > mid) res = max(res, query(u << 1 | 1, l, r));
    return res;
}

void modify(int u, int l, int r, int v) {
    if (tr[u].l >= l && tr[u].r <= r) { tr[u].max += v, tr[u].flag += v; return; }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) modify(u << 1, l, r, v);
    if (r > mid) modify(u << 1 | 1, l, r, v);
    pushup(u);
}

int lg[N];
void solve() {
    cin >> n;
    for (int i = 1; i < n + 1; i++) scanf("%d", w + i);
    build(1, 1, n);
    
    vector<pii> v;
    lg[n] = n, v.push_back({w[n], n});
    for (int i = n - 1; i; i--) {
        if (v.back().first <= w[i]) lg[i] = i, v.push_back({w[i], i});
        else lg[i] = lower_bound(v.begin(), v.end(), (pii){w[i], INF})->second;
    }

    int pre = INF, res = 1;
    priority_queue<pii, vector<pii>, less<pii> > q;
    for (int i = 1; i < n + 1; i++) q.push({w[i], i});
    for (int i = 1; i < n + 1; i++) {
        if (w[i] < pre) {
            while (q.size() && q.top().first > w[i]) {
                auto u = q.top().second; q.pop();
                if (u > i && lg[u] != u) modify(1, u + 1, lg[u], 1);
            } 

            if (lg[i] != i) res = max(res, query(1, i + 1, n) + 2);
            pre = w[i];
        } else if (w[i] > pre && lg[i] != i) modify(1, i + 1, lg[i], -1);
    }
    printf("%d\n", res);
}

int main() {
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```

---

