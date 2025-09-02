# Penacony

## 题目描述

在梦乡 $\text{Penacony}$ ，有 $n$ 栋房子和 $n$ 条双向的路。第 $i$ 栋和第 $i+1$ 栋房子（包括第 $n$ 和第 $1$ 栋之间）有双向的路连接。然而，由于梦乡的危机，领主陷入债务，难以维护所有的路。

梦乡的居民之中，有 $m$ 对好朋友。如果住在 $a$ 栋的居民和住在 $b$ 栋的居民是好朋友，那么他们必须能够通过受到维护的道路相互来往，即要求维护 $a$ 栋和 $b$ 栋之间那些的路。

请求出梦乡的领主最少需要维护多少条路。

## 样例 #1

### 输入

```
7
8 3
1 8
2 7
4 5
13 4
1 13
2 12
3 11
4 10
10 2
2 3
3 4
10 4
3 8
5 10
2 10
4 10
4 1
1 3
5 2
3 5
1 4
5 2
2 5
1 3```

### 输出

```
4
7
2
7
2
3
3```

# 题解

## 作者：modfisher (赞：14)

## 题意
给定一个 $n$ 个点的环，$i$ 与 $i+1$ 之间有一条无向边。有 $m$ 对点对 $a_i,b_i$，要求删掉尽可能多的边，使得删完后，每对 $a_i,b_i$ 仍联通。求出剩余边数的最小值。

## 思路
这题的一个很麻烦的点在于，每对 $a_i,b_i$ 之间有 $2$ 条路径（由 $a_i$ 到 $b_i$，或由 $a_i$ 到 $1$ 到 $n$ 再到 $b_i$），我们无法判断是通过哪条路径联通的。

让我们思考：造成这点的根本原因是什么？因为这是一个环，环上任意两点间有两条路径。所以，如果能将这个环断开，这个问题就简单了。

再想想，我们正在做的事情是什么？不正是删边使环断开吗？这两件事是不矛盾的。

我们不妨枚举我们删掉的第一条边，删完后，环变成了一条链。在这条链上，每对 $a_i,b_i$ 之间的路径是唯一的，我们便可以放心大胆地标出哪些边是绝对不能删掉的，最后，不能删掉的边数即为答案。将所有答案取最小值，就得到答案了。

有关标记的动态维护，可以用线段树实现。区间加一表示打标记，区间减一表示撤掉标记。最后统计 $0$ 的数量即可。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int a[maxn], b[maxn];
vector<int> V[maxn];

namespace seg{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
int min1[maxn << 2], cnt[maxn << 2], tag[maxn << 2];
void up(int x){
	if(min1[l(x)] == min1[r(x)]) min1[x] = min1[l(x)], cnt[x] = cnt[l(x)] + cnt[r(x)];
	else if(min1[l(x)] < min1[r(x)]) min1[x] = min1[l(x)], cnt[x] = cnt[l(x)];
	else min1[x] = min1[r(x)], cnt[x] = cnt[r(x)];
}
void down(int x){
	min1[l(x)] += tag[x], tag[l(x)] += tag[x];
	min1[r(x)] += tag[x], tag[r(x)] += tag[x];
	tag[x] = 0;
}
void build(int x, int l, int r){
	tag[x] = 0;
	if(l == r){
		min1[x] = 0, cnt[x] = 1;
		return;
	}
	int mid = l + r >> 1;
	build(l(x), l, mid);
	build(r(x), mid + 1, r);
	up(x);
}
void update(int x, int l, int r, int ql, int qr, int k){
	if(ql <= l && r <= qr){
		min1[x] += k, tag[x] += k;
		return;
	}
	down(x);
	int mid = l + r >> 1;
	if(ql <= mid) update(l(x), l, mid, ql, qr, k);
	if(qr > mid) update(r(x), mid + 1, r, ql, qr, k);
	up(x);
}}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= m; i ++){
			scanf("%d %d", &a[i], &b[i]);
			V[a[i]].push_back(i), V[b[i]].push_back(i);
		}
		seg::build(1, 1, n);
		for(int i = 1; i <= m; i ++){
			if(a[i] == 1) seg::update(1, 1, n, b[i], n, 1);
			else seg::update(1, 1, n, a[i], b[i] - 1, 1);
		}
		int ans = seg::min1[1] == 0 ? n - seg::cnt[1] : n;
		for(int i = 2; i <= n; i ++){
			for(int j = 0; j < V[i].size(); j ++){
				int x = V[i][j];
				if(a[x] == i){
					seg::update(1, 1, n, a[x], b[x] - 1, -1);
					if(a[x] > 1) seg::update(1, 1, n, 1, a[x] - 1, 1);
					seg::update(1, 1, n, b[x], n, 1);
				}else{
					if(a[x] > 1) seg::update(1, 1, n, 1, a[x] - 1, -1);
					seg::update(1, 1, n, b[x], n, -1);
					seg::update(1, 1, n, a[x], b[x] - 1, 1);
				}
			}
			ans = min(ans, seg::min1[1] == 0 ? n - seg::cnt[1] : n);
		}
		printf("%d\n", ans);
		for(int i = 1; i <= n; i ++) V[i].clear();
	}
	return 0;
}
```

---

## 作者：int08 (赞：9)

## 前言
看到 Xor-Hash 之后想的做法，感觉太妙妙了，没这个 Tag 我肯定想不到。
# Solution
首先说说正常的扫描线做法：按顺序枚举删去的边，然后发现只要确定删去的一条边，所有路径选法都确定了，再加上只要按顺序每条路径方向只变化两次，可以线段树维护区间加减区间 $0$ 个数。

但是 Xor-Hash 压倒性简单。

我们先假设路径选择了一个方向，最后来修改。

我们发现，选择修改某一条路径的方向，就是翻转了全局对于这条路径的选择情况，这个翻转使人联想到了异或。

那么变成，对于第 $i$ 条路径，我们选择一个方向让它所有边权值异或 $2^i$，然后全部赋值之后还可以所有边整体异或任意数，最大化 $0$ 的个数。

显然选择出现最多的那个数就行了，具体实现的时候，使用随机数来代替 $2^i$ 是异或哈希的精髓。

然后变成区间异或（用差分改成单点修改），查询出现最多的数出现次数，直接做就好了。

使用 `unordered_map<ull,int>`，时间复杂度 $O(n+m)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int Rand()
{
	return 65536ull*rand()*65536*65536+65536ull*rand()*65536+65536ull*rand()+rand();
}
int n,m,x,y,i,T,a[208555];
unordered_map<int,int> ma;
signed main()
{
	srand(20080506);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(i=1;i<=m;i++)
		{
			cin>>x>>y;
			int r=Rand();
			a[x]^=r,a[y]^=r;
		}
		for(i=1;i<=n;i++) a[i]^=a[i-1],ma[a[i]]++;
		int ans=0;
		for(auto x:ma) ans=max(ans,x.second);
		cout<<n-ans<<endl;
		for(i=1;i<=n+1;i++) a[i]=0;
		ma.clear();
	}
}
```
# The End.

---

## 作者：初星逝者 (赞：3)

首先观察，必定至少有一条路不会被维护到，因为所有经过这一条路的都一定可以通过环从另一边去走。

例：$1 \to 2$。

同样也可以：$1 \to n \to n-1 \to ... \to 3 \to 2$。

那么可以通过枚举这条断路，从而计算出在此基础上需要的路即可。

但是怎么统计答案呢？

我们想到，维护所有的边，如果我们能通过对我们当前需要的边进行 $+1$，那么所有不需要的边的值就都为 $0$，那么我们就可以维护最小值 $a$ 和最小值出现的个数 $cnt$。

设点数为 $n$。

- 如果最小值 $a$ 为 $0$，答案为 $n-cnt$。
- 如果最小值 $a$ 不为 $0$，答案为 $cnt$。

上述操作可以利用线段树进行维护。

因为 $m$ 和 $n$ 同阶，所以时间复杂度为 $\mathcal{O}(n \log n)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,t,q;
vector<int> v[200005];
int b[200005<<2],cnt[200005<<2],add[200005<<2];

void pushup(int rt){
	b[rt]=min(b[rt<<1],b[rt<<1|1]);
	cnt[rt]=0;
	if(b[rt]==b[rt<<1])cnt[rt]+=cnt[rt<<1];
	if(b[rt]==b[rt<<1|1])cnt[rt]+=cnt[rt<<1|1];
}

void build(int l,int r,int rt){
	add[rt]=0;
	b[rt]=0;
	if(l==r){
		cnt[rt]=1;
		return ;
	}
	int m=(l+r)>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	pushup(rt); 
}

void pushdown(int rt){
	b[rt<<1]+=add[rt];
	b[rt<<1|1]+=add[rt];
	add[rt<<1]+=add[rt];
	add[rt<<1|1]+=add[rt];
	add[rt]=0;
} 

void update(int L,int R,int c,int l,int r,int rt){
	if(L<=l&&r<=R){	
		b[rt]+=c;
		add[rt]+=c;
		return ; 
	}
	int m=(l+r)>>1;
	pushdown(rt);
	if(L<=m)update(L,R,c,l,m,rt<<1);
	if(R>m)update(L,R,c,m+1,r,rt<<1|1);
	pushup(rt);
}

int query(int L,int R,int l,int r,int rt){
	if(L<=l&&r<=R){
		return cnt[rt];
	}
	int m=(l+r)>>1;
	int ans=0;
	pushdown(rt);
	if(L<=m&&b[rt<<1]==b[rt])ans+=query(L,R,l,m,rt<<1);
	if(R>m&&b[rt<<1|1]==b[rt])ans+=query(L,R,m+1,r,rt<<1|1);
	return ans;
}

int qry(){
	int x=query(1,n,1,n,1);
	if(b[1]==0)return n-x;
	return x;
}

int main(){
	cin >> t;
	while(t--){
		cin >> n >> q;
		for(int i=1;i<=n;i++)v[i].clear();
		build(1,n,1);
		while(q--){
			int x,y;
			cin >> x >> y;
			v[x].push_back(y);
			v[y].push_back(x);
			update(x,y-1,1,1,n,1);
		}
		int ans=INT_MAX;
		ans=min(ans,qry());
		for(int i=1;i<=n;i++){
			for(auto y:v[i]){
				if(y>i){
					update(1,n,1,1,n,1);
					update(i,y-1,-2,1,n,1);
				}
				else{
					update(1,n,-1,1,n,1);
					update(y,i-1,2,1,n,1);
				}
			}
			ans=min(ans,qry());
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：LETTTER (赞：1)

## 哈希做法
容易发现，把整个图看成一个圆，对每对朋友代表的两个点，只有两种选择：维护优弧/劣弧的连通性，当我们选择维护优弧的连通性，对于其他的朋友，我们只需要考虑至少有一点在劣弧内的朋友对，我们需要维护的长度是优弧的全部长度加上劣弧的部分长度，反过来想，我们不需要维护的长度是劣弧内的部分长度，我们需要最大化这部分长度，设为 $len$。维护劣弧也是一样的道理。


对每对朋友的左右端点，我们对异或差分数组这两点赋值随机数，然后异或前缀和差分数组，因为把前缀和相同的点之外的点连通可以让这个图符合要求，我们把出现次数最多的前缀和连成的若干线段的长度作为 $len$，即可得到答案 $n-len$。


```cpp
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false), cin.tie(0)
using namespace std;
using ll = long long;
template <class T>
using vc = vector<T>;
mt19937_64 rng(
    (unsigned int)chrono::steady_clock::now().time_since_epoch().count());
void solve() 
{
	int n,m;
	cin>>n>>m;
	vc<ll>p(n+1);
	for(int i=0;i<m;i++)
	{
		int a,b;
		cin>>a>>b;
		a--,b--;
		ll x=rng();
		p[a]^=x;
		p[b]^=x;
		
	}
	for(int i=1;i<n;i++)
	{
		p[i]^=p[i-1];
	}
	map<ll,int>cnt;
	int ans=0;
	for(int i=0;i<n;i++)
	{
		ans=max(ans,++cnt[p[i]]);
	}
	ans=n-ans;
	cout<<ans<<"\n";
}
int main() {
  IOS;
  int t;
  t = 1;
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  cin >> t;
  while (t--) {
    solve();
  }
}










```

---

## 作者：SamHJD (赞：1)

> 有一个 $n$ 个结点的环，给出若干个信息形如环上 $a$ 和 $b$ 连通，求最少保留几条边能满足这些信息。

对于一对 $a,b$，一共有两条路径：通过 $(n,1)$ 和不通过 $(n,1)$，显然这两条路径的并集为整个环。因此考虑枚举每一条边做为最终方案中不选的一条边，不难发现此时每对 $a,b$ 的路径选择方案确定。

进行扫描线，纵轴为边的编号（不妨将边的编号设为其左端点的编号，$(n,1)$ 的编号为 $n$），对于每一对 $(a,b)$，$[1,a),[b,n]$ 中的边不选时其覆盖区间为 $[a,b)$，否则为 $[1,a),[b,n]$。

区间加，查询全局非 $0$ 的数的个数，容易用线段树维护。

```cpp
#include "bits/stdc++.h"
#define ls p*2
#define rs p*2+1
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=2e5+10;
int n,m,a[N];
struct SGT{
	struct node{
		int l,r,tag,sum;
	}t[N*4];
	void build(int p,int l,int r){
		t[p].l=l;t[p].r=r;t[p].tag=0;t[p].sum=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
	void pushup(int p){
		if(t[p].tag) t[p].sum=t[p].r-t[p].l+1;
		else t[p].sum=t[ls].sum+t[rs].sum;
	}
	void upd(int p,int nl,int nr,int k){
		if(nl>nr) return;
		if(nl<=t[p].l&&t[p].r<=nr){
			t[p].tag+=k;
			if(t[p].l==t[p].r) t[p].sum=(bool)(t[p].tag);
			else pushup(p);
			return;
		}
		if(nl<=t[ls].r) upd(ls,nl,nr,k);
		if(nr>=t[rs].l) upd(rs,nl,nr,k);
		pushup(p);
	}
}t;
struct LINE{
	int x,l,r,k;
}l[N*7];
bool cmp(LINE a,LINE b){return a.x<b.x;}
int T;
void solve(){
	read(n);read(m);
	rep(i,1,n) a[i]=0;
	int lcnt=0;
	t.build(1,1,n);
	rep(i,1,m){
		int L,R;read(L);read(R);
		l[++lcnt]=(LINE){L,R,n,1};
		l[++lcnt]=(LINE){L,1,L-1,1};
		l[++lcnt]=(LINE){R,R,n,-1};
		l[++lcnt]=(LINE){R,1,L-1,-1};
		l[++lcnt]=(LINE){R,L,R-1,1};
		l[++lcnt]=(LINE){1,L,R-1,1};
		l[++lcnt]=(LINE){L,L,R-1,-1};
	}
	sort(l+1,l+lcnt+1,cmp);
	int ans=n;
	rep(i,1,lcnt){
		if(l[i].x!=l[i-1].x&&i!=1) ans=min(ans,t.t[1].sum);
		t.upd(1,l[i].l,l[i].r,l[i].k);
	}
	ans=min(ans,t.t[1].sum);
	printf("%d\n",ans);
}
int main(){
	read(T);while(T--) solve();
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1996G Penacony](https://www.luogu.com.cn/problem/CF1996G)

# 解题思路

考虑把约束都记录到 $a_i$ 上，$a_i$ 表示 $i \sim i + 1$ 受到的约束个数。

那么约束显然可以使用 xor hash 的形式来表示，我们只需要随机一个 $val$，对于每个约束 $l,r$，都将 $a_{l \sim r - 1}$ 都异或上 $val$ 即可，那么这个约束表述形式显然可以使用差分异或来维护。

还原时只需要将每个 $i \in [1,n-1]$，$pre_i \gets pre_i \oplus pre_{i-1}$ 即可，下文设 $a$ 为还原后的 $pre$。

设 $ans$ 为 $a$ 数组的众数出现次数，答案即为 $n - ans$，因为你完全可以将受到的约束取反，将所有**值相等**的 $a_i$ 变成 $0$，而 $a_i$ 一旦变成 $0$，这意味着 $i$ 到 $i + 1$ 这个路径**没有**任何约束，因此一定是不用铺设道路的。

时间复杂度 $O(n \log n)$。

# 参考代码

```cpp
ll n,m;
ll a[1000010];
ll pre[1000010];
ll sum[1000010];
ll ans;
map<ll,ll>mp;
ll Ss=chrono::steady_clock::now().time_since_epoch().count();mt19937_64 Apple(Ss);ll rand_lr(ll l,ll r){return Apple()%(r-l+1)+l;}
void _clear(){}
void solve()
{
    ans=1e18;
    _clear();
    cin>>n>>m;
    forl(i,1,n*2)
        pre[i]=0;
    forl(i,1,m)
    {
        ll x,y;
        cin>>x>>y;
        ll num=rand_lr(1,1e18);
        pre[x]^=num,pre[y]^=num;
    }
    forl(i,1,n)
        pre[i]^=pre[i-1];
    ll maxn=0;
    forl(i,1,n)
        Max(maxn,++mp[pre[i]]);
    cout<<n-maxn<<endl;
    mp.clear();
}
```

---

## 作者：Priestess_SLG (赞：0)

一个很好理解很好写的做法。显然答案的上界是 $n$。

考虑对于一条 $a\sim b$ 的路径，则要么在圆上顺时针走要么逆时针走。考虑定义一条路径的状态 $F(u\to v)$：

+ $F(u\to v)=1$：即维护 $u$ 顺时针走到 $v$ 的路径。
+ $F(u\to v)=0$：即维护 $u$ 逆时针走到 $v$ 的路径。

那么可以定义一段路 $x\to y$ 的状态（$x,y$ 相邻），记作 $G(x\to y)$：

+ 对于一条从 $u$ 走到 $v$ 的路径，若其顺时针走包含 $x\sim y$，则在 $G(x\to y)$ 中添加 $u\to v$ 的路径，否则其便然逆时针走包含 $x\sim y$，不添加该条路径。

此时 $G(x\to y)$ 为一个路径集合。下面说明对于两个路径集合 $G_1,G_2$，若 $G_1\neq G_2$，则 $G_1,G_2$ 所对应的环上路径必然不能都不维护：

因为 $G_1\neq G_2$，所以 $G_1,G_2$ 中必然存在一个路径 $u\sim v$ 满足其在 $G_1,G_2$ 中恰好出现了一次。考虑到若 $G_1,G_2$ 对应路径同时不维护，则对于上面的 $u\sim v$ 路径而言，其无法顺时针或逆时针来从 $u$ 移动到 $v$ 而不经过任何不维护的路段。因此可以证明选择的删除集合 $S$ 必然不能同时包含 $G_1,G_2$。

然后下面说明若 $\forall G_1,G_2\in S,G_1=G_2$，则该删除方案必然可行：此时只需要按照 $S$ 中维护出现的路径集合 $G$，按照 $G$ 的方式来顺时针 / 逆时针维护路径即可。

因此可以证明，答案必然是选择一个合法的路径集合 $g$，然后对于所有 $G(x\sim y)=g$ 的环上路径，停止对其的维护，其余路径全部维护。此时问题变为如何快速的记录 $G(x\sim y)$ 的值。考虑对于每一条路径 $u\sim v$ 随机一个整数 $r$，然后让 $u\sim v$ 顺时针下所有经过的边全部异或上 $r$，这个操作可以使用差分来实现。最后只需要用 `map` 求出所有 $G(x\sim y)$ 的众数，用 $n$ 减去她即可。时间复杂度为 $O(n\log n)$。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define int long long
using namespace std;
const int N = 500010;
int diff[N];
mt19937_64 mt(time(0));
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) diff[i] = 0;
        for (int i = 1; i <= m; ++i) {
            int a, b;
            cin >> a >> b;
            int rng = mt();
            diff[a] ^= rng, diff[b] ^= rng;
        }
        for (int i = 2; i <= n; ++i) diff[i] ^= diff[i - 1];
        map<int, int> mp;
        for (int i = 1; i <= n; ++i) ++mp[diff[i]];
        int res = n;
        for (auto &[i, j] : mp) res = min(res, n - j);
        cout << res << '\n';
    }
    return 0;
}
```

---

## 作者：蒋辰逸 (赞：0)

[CF1996G Penacony](https://www.luogu.com.cn/problem/CF1996G)

## 题意

给定一个环，环上有 $n$ 对点，用最少的边数使每对点都联通。

## 思路

在环上，两点之间有两种连接方式（如果看做圆上两点，分别是优弧和劣弧）。翻转这个连接（从一个弧至对面的弧）就相当于将其异或，因为异或有如下性质：
$$a \oplus a = 0$$
所以，对于每一对点，我们对其分别分配一个相同但与其他点对不同的值，并处理异或前缀和，前缀和相同的边就代表拥有同样的连边情况，就可以同时翻转至对面。由于异或值容易重复，例如 $1 \oplus 2 = 5 \oplus 6$，$1 \oplus 2 \oplus 3 = 4 \oplus 8 \oplus 12$。所以我们用随机哈希来避免冲突。保险起见，再加上双哈希。

最终，策略就是删去相同的哈希值的边，我们枚举每个哈希值，统计最多的数量。

## 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int T;
int n,m;
int ans;
pair<int,int> a[200010];
map<pair<int,int>,int>mp;
signed main(){
	srand(time(0));
	cin>>T;
	while(T--){
		memset(a,0,sizeof(a));
		mp.clear();
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			int x,y;
			cin>>x>>y;
			int r1=666ull*rand()*rand()*rand()+rand()*rand()+rand();//随机生成哈希值
			int r2=114514ull*rand()*rand()*rand()+1919810ull*rand()*rand()+360ull*rand();
			a[x].first^=r1;a[y].first^=r1;
			a[x].second^=r2;a[y].second^=r2;//对两关联点分配同样的哈希值
		}
		for(int i=1;i<=n;i++){
			a[i].first^=a[i-1].first;
			a[i].second^=a[i-1].second;//前缀和
			mp[a[i]]++;//统计一样的哈希值最多的边
		}
		for(map<pair<int,int>,int>::iterator it=mp.begin();it!=mp.end();it++){
			ans=max(ans,it->second);
		}
		cout<<n-ans<<endl;
	}
}
```

---

