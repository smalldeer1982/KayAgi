# Doremy's Drying Plan (Easy Version)

## 题目描述

The only differences between the two versions of this problem are the constraint on $ k $ , the time limit and the memory limit. You can make hacks only if all versions of the problem are solved.

Doremy lives in a rainy country consisting of $ n $ cities numbered from $ 1 $ to $ n $ .

The weather broadcast predicted the distribution of rain in the next $ m $ days. In the $ i $ -th day, it will rain in the cities in the interval $ [l_i, r_i] $ . A city is called dry if it will never rain in that city in the next $ m $ days.

It turns out that Doremy has a special power. She can choose $ k $ days (in the easy version, $ k = 2 $ ), and during these days it will not rain. Doremy wants to calculate the maximum number of dry cities after using the special power.

## 说明/提示

In the first test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 2 $ will be dry;
- rain $ 2,3 $ , then no city will be dry;
- rain $ 1,3 $ , then no city will be dry;

So there is at most $ 1 $ dry city.

In the second test case, if Doremy prevents

- rain $ 1,2 $ , then city $ 1,2 $ will be dry;
- rain $ 2,3 $ , then city $ 4,5 $ will be dry;
- rain $ 1,3 $ , then city $ 1,5 $ will be dry.

So there are at most $ 2 $ dry cities.

In the third test case, it is optimal to prevent rain $ 2,5 $ .

In the forth test case, there is always $ 4 $ days of rain that wets all the cities and cannot be prevented.

## 样例 #1

### 输入

```
6
2 3 2
1 2
1 2
1 1
5 3 2
1 3
2 4
3 5
10 6 2
1 5
6 10
2 2
3 7
5 8
1 4
100 6 2
1 100
1 100
1 100
1 100
1 100
1 100
1000 2 2
1 1
1 1
20 5 2
9 20
3 3
10 11
11 13
6 18```

### 输出

```
1
2
3
0
1000
15```

# 题解

## 作者：红黑树 (赞：6)

[可能更好的阅读题意](https://rbtr.ee/CF1889C)

## 题意
给定 $n$ 个点，$m$ 条线段。你可以删除其中的 $k$ 条线段，问最终最多有多少点可以不被任何区间覆盖。

$1 \leq n \leq 2 \times 10^5, 2 \leq m \leq 2 \times 10^5, 2 \leq k \leq 10$

在简单版本中，$k = 2$。

## 题解
首先看简单版本。如果有一个点被覆盖达到 $3$ 次，那么最终这个点不可能不被覆盖，因此可以不考虑这种点。

如果一个点没有被覆盖，那么它最终一定不会被覆盖，因此可以对这种点计数，最后加上即可。

那么剩下情况就是一个点一定被覆盖 $1$ 次或 $2$ 次。

如果两条线段没有交，那么他们的贡献就是区间中仅被覆盖一次的点的个数之和。最终取最大值和次大值相加即可。

如果两条线段有交，那么他们的贡献是相交区间中被覆盖两次的点的个数，加上这两条线段不相交部分的仅被覆盖一次的点的个数之和。

可以使用一个类似于扫描线的东西维护当前点被哪些线段覆盖。

## 代码
```cpp
void STRUGGLING([[maybe_unused]] unsigned TEST_NUMBER) {
  tp n, m, k, tar = 0, cnt = 0; bin >> n >> m >> k;
  mt19937_64 rnd(217);
  set<tp> seg;
  vector<vector<unsigned long long>> in(n + 1), out(n + 2);
  map<tp, tp> sig;
  map<pair<unsigned long long, unsigned long long>, tp> db;
  while (m--) {
    tp l, r, id = rnd(); bin >> l >> r;
    in[l].push_back(id);
    out[r + 1].push_back(id);
  }
  for (tp i = 1; i <= n; ++i) {
    for (auto& j : out[i]) seg.erase(j);
    for (auto& j : in[i]) seg.insert(j);
    if (seg.empty()) ++cnt;
    else if (seg.size() == 1) ++sig[*seg.begin()];
    else if (seg.size() == 2) ++db[make_pair(*seg.begin(), *seg.rbegin())];
  }
  multiset<tp> tmp;
  for (auto& i : sig) tmp.insert(-i.second);
  if (tmp.size() > 0) tar -= *tmp.begin();
  if (tmp.size() > 1) tar -= *next(tmp.begin());
  for (auto& [i, j] : db) tar = max(tar, j + sig[i.first] + sig[i.second]);
  bin << tar + cnt << '\n';
}
```

---

## 作者：happybob (赞：4)

Hard Version 的做法貌似是 DP，但是 Easy Version 的做法也十分有启发性。

Easy Version 中 $k=2$，即只进行两次操作。通常见到两次操作，大概的做法就是枚举其中一次操作，本题也是这样。

设 $c_i$ 表示第 $i$ 个城市在这 $m$ 天内下雨天数。如果只进行一次操作，那么这段区间中所有 $c_i=1$ 的城市会变得干旱。

对于进行两次操作，两个区间中分别的 $c_i=1$ 的会变得干旱，然而还有区间交集中 $c_i=2$ 的也会变干旱。

不妨这样考虑：枚举第一次操作，先计算第二次操作中两个区间没有交集的贡献。接着枚举区间中每个 $c_i=2$ 的并统计这一个城市另一天降雨是哪一天。算一下贡献即可。

注意到我们只枚举 $c_i=2$ 的，所以每个 $c_i=2$ 至多只会被枚举到两遍，于是可以 $O(n)$ 做完。$c_i$ 和每个 $c_i=2$ 的另一天是哪一天降雨都可以通过差分算出。

具体地，$c_i$ 容易转化成区间加，由于询问都在加之后，差分维护即可。

对于 $c_i=2$，设 $g_i$ 表示第 $i$ 个城市所有下雨天的编号和。$c_i=2$ 表示 $g_i=x+y$。我们在枚举时已经确定了 $x$，$y$ 则容易通过 $y=g_i-x$ 算出。$g_i$ 也可以转化为区间加，差分维护即可。

我写的比较丑，所以带个 $\log$，不过可以优化掉。

启示：操作两次或求满足条件 $(i,j)$ 对数之类的问题，大都可以通过枚举其中一次，用一些技巧维护另一次。比如 CSP-S 2023 T2 也是一样的。 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 5e5 + 5, MOD = 1e9 + 7; // Remember to change

int n, m, k, c[N], t;
int l[N], r[N], p[N], g[N], gp[N];
int ps[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i++) c[i] = p[i] = gp[i] = g[i] = ps[i] = 0;
		for (int i = 1; i <= m; i++)
		{
			cin >> l[i] >> r[i];
			p[r[i] + 1]--;
			p[l[i]]++;
			gp[r[i] + 1] -= i;
			gp[l[i]] += i;
		}
		int ans = 0;
		set<int> pp;
		multiset<int> st;
		for (int i = 1; i <= n; i++) 
		{
			c[i] = c[i - 1] + p[i], g[i] = g[i - 1] + gp[i];
			ans += (c[i] == 0), ps[i] = ps[i - 1] + (c[i] == 1);
			if (c[i] == 2) pp.insert(i);
		}
		int maxn = 0;
		for (int i = 1; i <= m; i++)
		{
			st.insert(ps[r[i]] - ps[l[i] - 1]);
		}
		for (int i = 1; i <= m; i++)
		{
			map<int, int> cc;
			int g = ps[r[i]] - ps[l[i] - 1], rg = g;
			st.erase(st.find(g));
			if (st.size()) g += *(st.rbegin());
			st.insert(rg);
			auto it = pp.lower_bound(l[i]);
			for (; it != pp.end() && *it <= r[i]; ++it)
			{
				cc[::g[*it] - i]++;
			}
			for (auto &[x, y] : cc)
			{
				int h = ps[r[i]] - ps[l[i] - 1] + ps[r[x]] - ps[l[x] - 1];
				g = max(g, h + y);
			}
			maxn = max(maxn, g);
		}
		cout << ans + maxn << "\n";
	}
	return 0;
}


```


---

## 作者：FFTotoro (赞：3)

考虑两个区间会对答案造成什么样的影响。显然重叠部分内的城市能“干涸”当且仅当这个城市仅仅被这两个区间覆盖；不重叠部分的城市能“干涸”当且仅当这个城市仅仅被这一个区间覆盖。

一个城市被几个区间覆盖可以用优先队列贪心来解决；记 $c_{l,r}$ 为 $l\sim r$ 城市中被一个区间覆盖的城市个数。如果两个区间不交，那么答案就是从所有 $[l_i,r_i]$ 中选出最大的两个 $c_{l_i,r_i}$ 相加；如果两个区间相交，答案可以用前面的性质简易统计——只需枚举每个被覆盖两次的城市，然后考虑这两个区间即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,m,k,l=0,c=0; cin>>n>>m>>k;
    vector<pii> a(m);
    for(auto &[l,r]:a)cin>>l>>r,l--,r--;
    sort(a.begin(),a.end());
    multiset<pii> q;
    vector<int> w(n),s1(n),s2(n),p;
    vector<pii> b1(n),b2(n);
    for(int i=0;i<n;i++){
      while(!q.empty()&&q.begin()->first<i)q.erase(q.begin());
      while(l<m&&a[l].first<=i)q.emplace(a[l].second,a[l].first),l++;
      if(w[i]=q.size();q.empty())c++;
      if(s1[i]=(i?s1[i-1]:0);q.size()==1)s1[i]++;
      if(s2[i]=(i?s2[i-1]:0);q.size()==2)s2[i]++,
        b1[i]=make_pair(max(q.begin()->second,next(q.begin())->second),q.begin()->first),
        b2[i]=make_pair(min(q.begin()->second,next(q.begin())->second),next(q.begin())->first);
    }
    auto c1=[&](int l,int r){return l<=r?s1[r]-(l?s1[l-1]:0):0;};
    auto c2=[&](int l,int r){return l<=r?s2[r]-(l?s2[l-1]:0):0;};
    for(auto [l,r]:a)p.emplace_back(c1(l,r));
    sort(p.begin(),p.end(),greater<>());
    int s=p[0]+(m>1?p[1]:0);
    for(int i=0;i<n;i++)
      if(w[i]==2)s=max(s,c1(b2[i].first,b1[i].first-1)+c2(b1[i].first,b1[i].second)+c1(b1[i].second+1,b2[i].second));
    cout<<s+c<<'\n';
  }
  return 0;
}
```

---

## 作者：Diaоsi (赞：2)

[Doremy's Drying Plan (Easy Version)](https://www.luogu.com.cn/problem/CF1889C1)

想法很简单，显然只有被覆盖次数小于等于 $2$ 的点会对答案产生贡献，于是我们可以对每个覆盖次数小于等于 $2$ 的点考虑覆盖它的区间是否会成为被删去的区间。

被删去的区间只可能有两种情况：

- 互不相交

- 部分（也可能是完全）重合

第一种情况十分好处理，求出每个区间单独删除之后全局的空点个数，排个序取最大的两个进行删除即可，不难发现这样的贪心是不会让答案变得更劣的。

对于第二种情况，我们可以使用开头提到的结论，遍历每一个覆盖次数等于 $2$ 的点，然后把覆盖它的区间删除，统计此时全局的空点个数。

把两种情况的答案取 $\max$ 就能得到最终答案。

第二种情况的具体实现可以使用线段树分治，把 $m$ 个区间用 ```std::vector``` 挂在线段树对应的 $\log n$ 个节点上，遍历到叶子节点时用栈记录下当前有多少个区间覆盖该节点。

然后使用一个支持区间加法，查询全局 $\min$ 以及这个值出现的次数的线段树进行维护，在遍历到符合条件的叶子节点时删去覆盖它的两个区间并统计答案即可，具体实现中细节较多，可以参考我的代码。

时间复杂度 $\mathcal{O(n\log n)}$ 

```Code:```
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,m,k,num,cnt,top,ans;
struct rec{
	int l,r,id,val;
	bool operator <(const rec &x)const{
		return val<x.val;
	}
	bool operator ==(const rec &x)const{
		return l==x.l&&r==x.r;
	}
}q[N],st[N];
vector<rec> h[N<<2];
struct SegmentTree{
	int l,r;
	int cnt,dat,tag;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define cnt(x) tree[x].cnt
	#define dat(x) tree[x].dat
	#define tag(x) tree[x].tag
}tree[N<<2];
void pushup(int x){
	dat(x)=min(dat(x<<1),dat(x<<1|1));
	if(dat(x<<1)<dat(x<<1|1))cnt(x)=cnt(x<<1);
	if(dat(x<<1)>dat(x<<1|1))cnt(x)=cnt(x<<1|1);
	if(dat(x<<1)==dat(x<<1|1))cnt(x)=cnt(x<<1)+cnt(x<<1|1);
}
void build(int x,int l,int r){
	l(x)=l,r(x)=r;h[x].clear();
	dat(x)=tag(x)=0;
	if(l==r){cnt(x)=1;return;}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushdown(int x){
	if(!tag(x))return;
	dat(x<<1)+=tag(x);
	dat(x<<1|1)+=tag(x);
	tag(x<<1)+=tag(x);
	tag(x<<1|1)+=tag(x);
	tag(x)=0;
}
void insert(int x,int L,int R,rec t){
	int l=l(x),r=r(x);
	if(L<=l&&r<=R){
		h[x].push_back(t);
		dat(x)+=1;tag(x)+=1;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(x);
	if(L<=mid)insert(x<<1,L,R,t);
	if(R>mid)insert(x<<1|1,L,R,t);
	pushup(x);
}
void change(int x,int L,int R,int d){
	int l=l(x),r=r(x);
	if(L<=l&&r<=R){
		dat(x)+=d;tag(x)+=d;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(x);
	if(L<=mid)change(x<<1,L,R,d);
	if(R>mid)change(x<<1|1,L,R,d);
	pushup(x);
}
void query(int x){
	int l=l(x),r=r(x),o=top;
	for(rec z:h[x])st[++top]=z;
	if(l==r){
		if(top==2){
			change(1,st[1].l,st[1].r,-1);
			change(1,st[2].l,st[2].r,-1);
			if(!dat(1))ans=max(ans,cnt(1));
			change(1,st[1].l,st[1].r,1);
			change(1,st[2].l,st[2].r,1);
		}
	}
	else pushdown(x),query(x<<1),query(x<<1|1),pushup(x);
	while(o<top)--top;
}
int main(){
	scanf("%d",&T);
	while(T--){
		top=cnt=ans=0;
		scanf("%d%d%d",&n,&m,&k);
		build(1,1,n);
		for(int i=1;i<=m;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			q[i]=(rec){l,r,i,0};
			insert(1,l,r,q[i]);
		}
		query(1);
		for(int i=1;i<=m;i++){
			change(1,q[i].l,q[i].r,-1);
			q[i].val=!dat(1)?cnt(1):0;
			change(1,q[i].l,q[i].r,1);
		}
		sort(q+1,q+m+1);
		change(1,q[m-1].l,q[m-1].r,-1);
		change(1,q[m].l,q[m].r,-1);
		if(!dat(1))ans=max(ans,cnt(1));
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：樱雪喵 (赞：1)

## Description

给定 $m$ 条线段 $[l_i,r_i]$，其中 $l_i,r_i\in [1,n]$。至多删除 $k$ 条线段，使 $[1,n]$ 中未被任何线段覆盖的点数最多。输出这个数。

$n,m\le 2\times 10^5,\, k=2$。

## Solution

观察到 $k$ 只有 $2$，这意味着如果某点 $i$ 被 $\ge 3$ 条线段覆盖，这个点无论如何最后都还是被覆盖，不需要考虑它对答案的贡献。

而一开始就不被覆盖的点也是容易计算的，可以直接加进答案。

那么剩下的点对答案有贡献的情况只分两种：

- 点 $i$ 被覆盖了两次，且这两条线段都被删了。
- 点 $i$ 被覆盖了一次，且这条线段被删了。

因此被删除的线段也只有两种情况：

- 如果这两条线段造成了第一类点的贡献，直接枚举每个可能的点，并尝试删除覆盖它的两条线段。
- 否则，这两条线段造成了两个第二类点的贡献。预处理出每条线段删除的贡献，选最大和次大值。

第二类是容易统计答案的，我们考虑第一类怎么统计。删除两条线段对答案造成的贡献即为恰好只被其中一条覆盖的点数与恰好被它们两个覆盖的点数之和。前者在维护第二类的时候已经求了。而这样的线段至多有 $n$ 对，可以暴力地维护后者。

求每个点被哪些线段覆盖可以把 $[l,r]$ 拆成 $l$ 和 $r+1$，`multiset` 维护。

---

## 作者：Eason2009 (赞：1)

这是只能过 C1 的题解。

大致题意：$n$ 个点，$m$ 个区间，每个区间覆盖连续的一些点，你可以删除任意两个区间，最大化所有点中没有被覆盖的点的个数。

首先，容易用前缀和和差分维护每个点被覆盖的次数，没有被覆盖过的点可以直接计入答案。

观察到只能进行两次操作，这也就意味着只有最多被覆盖 $2$ 次的点是对答案有贡献的，由于没有被覆盖过的点已被计入答案，只剩下了一些被覆盖 $1$ 次的点和被覆盖 $2$ 次的点，可以想到分类讨论。

情况一：只有被覆盖 $1$ 次的点对答案产生贡献。

这种情况较为简单，设 $cnt1_i$ 为第 $i$ 个区间有多少个点被覆盖 $1$ 次，则答案即为 $cnt1_i$ 的最大值与次大值之和。

由于每个对答案造成贡献的点仅被覆盖 $1$ 次，这么算是不会重复的。

情况二：有一个被覆盖 $2$ 次的点对答案产生贡献。

可以枚举这个点，将区间按左端点排序后用优先队列维护，算出是哪两个区间包括这个点（类似扫描线）。

那此时的答案即为同时被两个区间所包含的点中被覆盖 $2$ 次的点的个数加上两个区间中所有被覆盖一次的点的个数，在所有被覆盖 $2$ 次的点中取最大值即可。

至于怎样求一个区间内被覆盖 $1$ 或 $2$ 次的点的个数，还是可以用前缀和和差分维护。

最后的答案即为两种情况的最大值。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define ls now<<1
#define rs now<<1|1
#define QwQ puts("QwQ")
using namespace std;
const int N=200005;
int _,n,m,k,f1[N],f2[N],val[N],cnt1[N];
struct node
{
	int l,r;
}a[N];
bool cmp(node a,node b)
{
	if(a.l==b.l) return a.r<b.r;
	return a.l<b.l;
}
inline int read()
{
	int ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ans=(ans<<3)+(ans<<1)+(c^48);
		c=getchar();
	}
	return ans*f;
}
inline void write(int x)
{
    if(x<0)
    {
        printf("-"),write(-x);
        return;
    }
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
signed main()
{
	_=read();
	while(_--)
	{
		int ans=0,s=0;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) val[i]=0;
		for(int i=1;i<=m;i++)
		{
			cin>>a[i].l>>a[i].r;
			val[a[i].l]++;
			val[a[i].r+1]--;
		}
		sort(a+1,a+m+1,cmp);
		for(int i=1;i<=n;i++) val[i]+=val[i-1];
		for(int i=1;i<=n;i++) s+=(val[i]==0);
		for(int i=1;i<=n;i++) f1[i]=f1[i-1]+(val[i]==1);
		for(int i=1;i<=n;i++) f2[i]=f2[i-1]+(val[i]==2);
		for(int i=1;i<=m;i++) cnt1[i]=f1[a[i].r]-f1[a[i].l-1];
		sort(cnt1+1,cnt1+m+1,greater<int>());
		ans=s+cnt1[1]+cnt1[2];
		int j=1;
		priority_queue<pii,vector<pii>,greater<pii> >q;
		for(int i=1;i<=n;i++)
		{
			while(!q.empty())
			{
				if(q.top().fi<i) q.pop();
				else break;
			}
			while(j<=m)
			{
				if(a[j].l==i) q.push({a[j].r,j}),j++;
				else break;
			}
			if(val[i]!=2) continue;
			int id1=q.top().se;
			q.pop();
			int id2=q.top().se;
			ans=max(ans,s+f2[min(a[id1].r,a[id2].r)]-f2[max(a[id1].l,a[id2].l)-1]+f1[a[id1].r]-f1[a[id1].l-1]+f1[a[id2].r]-f1[a[id2].l-1]);
			q.push({a[id1].r,id1});
		}
		write(ans);
		printf("\n");
	}
	return 0;
}
```

代码实现有些许细节，希望读者注意。


---

## 作者：Mikazuki_Munechika (赞：0)

首先考虑被覆盖了 $ 2 $ 个以上的肯定不会造成任何贡献，于是直接忽略。
于是剩下的就是被覆盖了 $ 1 $ 个或 $ 2 $ 个的。

很自然的想法是记录下来每对线段能够造成的贡献，但是这样就需要 $ O(m^2) $ 枚举了，更不用说还要有个 $ \log $ 来统计贡献了。

但是我们发现其实有的线段对根本不会造成贡献，于是就可以考虑直接记录下来每天需要删除哪几个线段才能有贡献（如果需要的线段个数超过了 $ 2 $ 不妨直接考虑不管）然后存到一个 set 里， 然后再建立一个索引为 set 的 map 到时候直接枚举就是 $ O(n \log n) $ 的了。

于是就是 STL 套 STL。

自认为还是比较简洁的做法，好像赛时大家都写的线段树啊？

Code:
```cpp
#include<bits/stdc++.h>
#define endl '\n'
// #define int long long
using i64=long long;
using u64=unsigned long long;
using u32=unsigned int;
using pii=std::pair<int,int>;
//using i128=__int128;
bool Mbe;
const int N = 2e5 + 5,  M = 65, mod = 1e9 + 7;
const int inf = 1e9;
int l[N], r[N], n, m, k;
std::vector<int> g[N],t[N];
std::set<int> s;
std::map<std::set<int>,int> cnt;
std::vector<std::set<int>> ca;
std::vector<pii> aa;
bool Med;
// template<class T>inline void up(T &a, T b){if(a < b) a = b;}
// template<class T>inline void down(T &a, T b){if(a > b) a = b;}
// template<class T>inline void Mod(T &a){return (a > mod || a < 0) && ((a += mod) %= mod), void();}
// template<class T1, class T2>inline int qpow(T1 a, T2 b){int res = 1;for(;b;b >>= 1, a = 1ll * a * a % mod) if(b & 1) res = 1ll * res * a % mod; return res;}
inline i64 read() {
    i64 x = 0,f = 1;char c = getchar();
    while(!isdigit(c)){if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)){ x = x * 10 + (c ^ 48); c = getchar();}
    return x * f;
}
signed main() {
    std::cerr<<1.00*(&Med-&Mbe)/1024/1024<<"MB"<<endl;
    // freopen("set03.in","r",stdin);
    // freopen("set.out","w",stdout);
    int tt = read();
    clock_t be = clock();
    // int tt = 1;
    while(tt --){
        n = read(), m = read(), k = read();
        cnt.clear(), ca.clear(), s.clear(), aa.clear();
        for(int i = 1; i <= n; i ++) g[i].clear(), t[i].clear();
        for(int i = 1; i <= m; i ++){
            l[i] = read(), r[i] = read();
            g[l[i]].push_back(i), t[r[i]+1].push_back(i);
        }
        for(int i = 1; i <= n; i ++){
            for(int u:g[i]){
                s.insert(u);
            }
            for(int u:t[i]){
                s.erase(u);
            }
            if(s.size() < 3){
                cnt[s] ++;
                ca.push_back(s);
            }
        }
        int mn = n;
        for(auto u:ca){
            if(u.size() == 2){
                mn = std::min(mn, n - cnt[u] - cnt[{*u.begin()}]-cnt[{*u.rbegin()}]-cnt[{}]);
            }else if(u.size() == 1){
                mn = std::min(mn, n - cnt[u] - cnt[{}]);
            }else{
                mn = std::min(mn, n - cnt[{}]);
            }
        }
        // std::cout << "orz" << endl;
        for(int i = 1; i <= m; i ++){
            aa.push_back({cnt[{i}], i});
        }
        sort(aa.begin(), aa.end());
        if(aa.size() >= 2){
            mn = std::min(mn, n - aa[aa.size() - 1].first - aa[aa.size() - 2].first - cnt[{}]);
        }
        n -= mn;
        std::cout << n << endl;
    }
    std::cerr<<clock()-be<<"ms"<<endl;
    return 0;
}
```


---

## 作者：2020kanade (赞：0)

前情提要：打的 div2，CD 都不会，最后半分钟不到交了 E1，prtest passed 但是 810ms，加上一车 STL 还没关流同步。

FST。

喜剧效果拉满。

进正题。这个做法扩展不到 C2 正解，但是简单粗暴，过这道足够了。

首先差分一波求出不删的情况下每个点被多少区间覆盖顺便扫出来本来有多少地方没有覆盖作为初始答案。

考虑删掉的两个区间的状态：贡献部分有交或无交。

如果贡献部分无交，这些删掉后会产生贡献的区间一定和被覆盖次数为 $1$ 的区间有交，交集大小就是删掉之后对答案的贡献，扫一遍完事。

如果贡献部分有交，考虑它们的交集一定和被覆盖次数为 $2$ 的区间有交，这就是有交的贡献部分。考虑直接合成一个长区间，贡献是交集长度加上分别独立删除这两个区间的贡献，后者前一部分无交情况已经处理。

对第一种情况的所有贡献排序选最大与非严格次大，再与后一种情况的最大值取较大者加入答案即可。

笔者实现比较智障，常数很大，不少东西可以省掉。

时间复杂度 $\Theta ((n+m)\log n+(n+m)\log m)$，实现上带一个至少为 $4$ 的常数。

下面这份 code 是最后半分钟交上去的会 FST 的那份。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+11;
int n,t,m;
set<int> l[N],r[N];
int sum[N],ans[N],il,k,ir;
set<int> p;
map<pair<int,int>,int> ans2;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		for(int i=1;i<=m;++i)
		{
			cin>>il>>ir;
			++sum[il],--sum[ir+1];
			l[il].insert(i);
			r[ir+1].insert(i);
		}
		for(int i=1;i<=n;++i) sum[i]+=sum[i-1];
	for(int i=1;i<=n;++i)
	{
		for(auto x:l[i]) p.insert(x);
		for(auto x:r[i]) p.erase(x);
		if(sum[i]==1) ++ans[*p.begin()];
	}
	p.clear();
	for(int i=1;i<=n;++i)
	{
		for(auto x:l[i]) p.insert(x);
		for(auto x:r[i]) p.erase(x);
		if(sum[i]==2)
		{
			auto x=*p.begin(),y=*p.rbegin();
			if(!ans2[make_pair(x,y)]) ans2[make_pair(x,y)]=ans[x]+ans[y];
			++ans2[make_pair(x,y)];
		}
	}
	int pans=0;
	for(int i=1;i<=n;++i) if(sum[i]==0) ++pans;
	sort(ans+1,ans+m+1);
	int qans=ans[m]+ans[m-1];
	for(auto x:ans2) qans=max(qans,x.second);
	cout<<pans+qans<<endl;
	for(int i=1;i<=n+1;++i) sum[i]=0,l[i].clear(),r[i].clear();
	ans2.clear();for(int i=1;i<=m+1;++i) ans[i]=0;p.clear();
	}
	
}
```


---

