# [ABC408F] Athletic

## 题目描述

场上有 $N$ 个脚手架，第 $i$ 个脚手架的高度为 $H_i$。

高桥将用这些脚手架玩一个游戏。他将任意选定一个脚手架作为起点并持续移动到其他脚手架，从脚手架 $i$ 可以移动到脚手架 $j$ 当且仅当 $H_j\le H_i-D$ 且 $\vert i-j\vert \le R$。

求在游戏过程中他最多可以移动多少次。

## 说明/提示

**样例 1 解释**

高桥可以选择脚手架 $1$ 作为起点。
- 因为 $H_2\le H_1-D,\vert 2-1\vert\le R$，所以高桥可以从脚手架 $1$ 移动到脚手架 $2$。
- 因为 $H_3\le H_2-D,\vert 3-2\vert\le R$，所以高桥可以从脚手架 $2$ 移动到脚手架 $3$。

共移动两次。可以证明高桥不能移动更多次数，故答案为 $2$。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
5 2 1
5 3 1 4 2```

### 输出

```
2```

## 样例 #2

### 输入

```
13 3 2
13 7 10 1 9 5 4 11 12 2 8 6 3```

### 输出

```
3```

# 题解

## 作者：_zuoqingyuan (赞：7)

# 思路分析

注意到无论怎么爬梯子都是越爬越低，满足无后效性，显然可以设计 dp，按照高度从高到低为顺序状态转移。设 $dp_i$ 表示爬到梯子 $i$ 最多爬几次。

$dp_i$ 可以转移的范围是 $[i-r,i+r]$ 的最大 dp 值，区间最大值，不难想到线段树，另一个关键的限制在于 $H_i\le H_j-D$，我们可以用可持久化线段树来完成这一限制，不过太过麻烦。

注意到 $H_i$ 为 $n$ 的一个排列，所以第 $i$ 个转移的 dp 值可以转移的是 $i-D$ 之前的 dp 值，所以当我们将第 $i$ 个 dp 值插入线段树时，让第 $i+D$ 个 dp 值进行转移即可。

时间复杂度 $O(n\log n)$，不懂的可以看代码。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
const int N=5e5+10;
const int inf=1e9;
struct sgt{
	int mx[N<<2];
	void push_up(int p){
		mx[p]=max(mx[ls],mx[rs]);
	}
	void build(int p,int l,int r){
		mx[p]=-inf;
		if(l==r)return;int mid=(l+r)>>1;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void change(int p,int l,int r,int x,int v){
		if(l==r)mx[p]=max(mx[p],v);
		else{
			int mid=(l+r)>>1;
			if(x<=mid)change(ls,l,mid,x,v);
			if(x>mid)change(rs,mid+1,r,x,v);
			push_up(p);
		}
	}
	int ask(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return mx[p];
		int mid=(l+r)>>1,res=-inf;
		if(L<=mid)res=max(res,ask(ls,l,mid,L,R));
		if(R>mid)res=max(res,ask(rs,mid+1,r,L,R));
		return res;
	}
}tr;
struct node{
	int h,id,dp;
}a[N];
bool cmp(node a,node b){
	return a.h>b.h;
}
int n,d,r,ans;
int main(){
	scanf("%d %d %d",&n,&d,&r);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].h);
		a[i].id=i,a[i].dp=1;
	}
	tr.build(1,1,n);
	sort(a+1,a+1+n,cmp);
	for(int i=1,j;i<=n;i++){
		tr.change(1,1,n,a[i].id,a[i].dp);
		j=i+d;
		if(j<=n){
			int val=tr.ask(1,1,n,max(1,a[j].id-r),min(n,a[j].id+r));
			val=max(val,0)+1,a[j].dp=max(a[j].dp,val);
		}
	}
	for(int i=1;i<=n;i++)ans=max(ans,a[i].dp);
	printf("%d\n",ans-1);
	return 0;
}
```

如有错误，请指出。

---

## 作者：anke2017 (赞：3)

容易想到一个 dp，令 $dp_i$ 表示当前在第 $i$ 个位置的最多跳跃次数，转移也是显然的：

$$
dp_{pos}=\max_{i=\max(1,pos-R+1)}^{\min(n,pos+R-1)}{((dp_i+1)\times[h_{pos}-h_i\ge D])}
$$

实际实现的时候要从按 $h_i$ 从小到大转移，所以发现可以使用线段树优化，将满足条件的 $dp_i$ 值放进线段树里，查询 $\max$，实现 $O(n\log_2{n})$ 的总复杂度。

注意不能认为最高的杆子的答案一定最优。赛时因为这个被罚了一发。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;
constexpr int maxn=500005;
struct seg
{
	int val[maxn<<2];
	inline int ls(int x){return x<<1;}
	inline int rs(int x){return (x<<1)+1;}
	inline void change(int now,int l,int r,int pos,int v)
	{
		if(l==r)
		{
			val[now]=v;return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)change(ls(now),l,mid,pos,v);
		else change(rs(now),mid+1,r,pos,v);
		val[now]=max(val[ls(now)],val[rs(now)]);
	}
	inline int query(int now,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)return val[now];
		int mid=(l+r)>>1;
		int mx=0;
		if(ql<=mid)mx=max(mx,query(ls(now),l,mid,ql,qr));
		if(mid<qr)mx=max(mx,query(rs(now),mid+1,r,ql,qr));
		return mx;
	}
}tree;//单点修改，区间查询最大的线段树
struct node
{
	int val,pos;
	inline bool operator <(const node tmp)const
	{
		return val<tmp.val;
	}
}st[maxn];
int dp[maxn];//存储每个点的 max 值
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	int n,d,r;cin>>n>>d>>r;
	for(int i=1;i<=n;i++)(cin>>st[i].val),st[i].pos=i;
	sort(st+1,st+1+n);
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
    //将可以转移的 dp 值放进线段树，容易发现最多加入 n 个值
		while(st[cnt].val+d<=st[i].val)
			tree.change(1,1,n,st[cnt].pos,dp[cnt]),cnt++;
		dp[i]=tree.query(1,1,n,max(1,st[i].pos-r),min(n,st[i].pos+r))+1;//直接查询即可。
	}
	int ans=0;for(int i=1;i<=n;i++)ans=max(ans,dp[i]-1);//-1是因为第一次不算
	cout<<ans;
	return 0;
}
```

---

## 作者：P2441M (赞：2)

## 题意

给定 $n,d,r$ 和长度为 $n$ 的排列 $h$。一个人初始时会自由选择一个起始位置 $i(1\leq i\leq n)$，然后不断重复以下操作直到无法操作：

- 选择一个 $j(1\leq j\leq n)$，满足 $h_j\leq h_i-d\land 1\leq |i-j|\leq r$，令 $i\rightarrow j$。

求最大操作次数。$1\leq d,r\leq n\leq 5\times 10^5$。

## 题解

很好想的题。

考虑 DP。我们按值 DP 就不会有后效性了，也就是令 $f_i$ 表示从 $h_{pos_i}$ 开始的最大操作次数，其中 $pos_{h_i}=i$。转移显然：

$$
f_i=\max_{j\leq i-d\land |pos_i-pos_j|\leq r} \{f_j+1\}
$$

一眼数据结构优化。枚举到 $i$ 时，把 $f_{i-d}$ 挂到 $pos_{i-d}$ 的位置，然后查询 $[\max(pos_i-r,1),\min(pos_i+r,n)]$ 的区间最大值，用线段树维护即可。

注意 $f_i$ 要初始化为 $-1$，这个害我吃了一发罚时。

时间复杂度 $\mathcal{O}(n\log{n})$。

## 代码

```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e5 + 5;

int n, d, r, ans, h[N], f[N], pos[N];

struct SegTree {
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
	int mx[N << 2];
	inline void push_up(int p) { mx[p] = max(mx[ls(p)], mx[rs(p)]); }
	inline void build(int p, int l, int r) {
		if (l == r) { mx[p] = -1; return; }
		int mid = (l + r) >> 1;
		build(ls(p), l, mid), build(rs(p), mid + 1, r);
		push_up(p);
	}
	inline int query(int p, int l, int r, int x, int y) {
		if (x <= l && y >= r) return mx[p];
		int mid = (l + r) >> 1, res = -1e9;
		if (x <= mid) res = query(ls(p), l, mid, x, y);
		if (y > mid) chk_max(res, query(rs(p), mid + 1, r, x, y));
		return res;
	}
	inline void change(int p, int l, int r, int x, int v) {
		if (l == r) { mx[p] = v; return; }
		int mid = (l + r) >> 1;
		if (x <= mid) change(ls(p), l, mid, x, v);
		else change(rs(p), mid + 1, r, x, v);
		push_up(p);
	}
#undef ls
#undef rs
} sgt;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> d >> r;
    for (int i = 1; i <= n; ++i) cin >> h[i], pos[h[i]] = i;
    sgt.build(1, 1, n);
    for (int i = 1; i <= d; ++i) f[i] = 0;
    for (int i = d + 1; i <= n; ++i) {
    	sgt.change(1, 1, n, pos[i - d], f[i - d]);
    	f[i] = sgt.query(1, 1, n, max(pos[i] - r, 1), min(pos[i] + r, n)) + 1;
    	chk_max(ans, f[i]);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：AK_400 (赞：1)

记 $dp_i$ 表示从第 $i$ 个脚手架开始最多跳几次。

注意到只能从高往低跳，于是从低到高计算。

转移即对于满足题意的 $j$，$dp_i\leftarrow \max(dp_i,dp_j+1)$。

注意到合法的 $j$ 一定是一段区间，于是可以线段树优化为 $O(n\log n)$。

具体地，当考虑高度为 $h$ 的脚手架时，插入高度为 $h-d$ 的脚手架的 dp 值，这样在线段树中的都是高度合法的。

只需要查询对应区间的最大值即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define db long double
using namespace std;
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
int mx[2000005];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r>>1)
void bd(int l,int r,int p){
    mx[p]=-1e18;
    if(l==r)return;
    bd(l,mid,ls);
    bd(mid+1,r,rs);
}
void upd(int l,int r,int id,int x,int p){
    mx[p]=max(mx[p],x);
    if(l==r)return;
    if(mid>=id)upd(l,mid,id,x,ls);
    else upd(mid+1,r,id,x,rs);
}
int qu(int l,int r,int ql,int qr,int p){
    if(ql<=l&&r<=qr)return mx[p];
    int res=-2e18;
    if(ql<=mid)res=qu(l,mid,ql,qr,ls);
    if(mid<qr)res=max(res,qu(mid+1,r,ql,qr,rs));
    return res;
}
int n,d,r,h[500005],id[500005],dp[500005];
void slv(){
    read3(n,d,r);
    for(int i=1;i<=n;i++)read(h[i]);
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+1+n,[&](int x,int y){return h[x]<h[y];});
    bd(1,n,1);
    for(int i=d+1;i<=n;i++){
        upd(1,n,id[i-d],dp[id[i-d]],1);
        dp[id[i]]=qu(1,n,max(1ll,id[i]-r),min(n,id[i]+r),1);
        if(dp[id[i]]<0)dp[id[i]]=0;
        else dp[id[i]]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
    cout<<ans<<endl;
    return;
}
signed main(){
    // int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：I_Love_DS (赞：1)

评蓝明显虚高，觉得绿比较合适。

## 思路

考虑 DP，以梯子高度从小到大的顺序转移一定没有问题，因为只能往下走，不能往上攀爬。

$f_i$ 表示高度第 $i$ 小的梯子，最多能走多少步。显然，如果区间里没有符合条件的梯子，那么 $f_i = 0$，否则 $f_i = \max_{j = l}^r f_j$，其中 $l$ 为区间左边界，$r$ 为区间右边界。但是这是 $O(n^2)$ 的，无法通过。

转移的过程就是在原数组下标上的区间最大值，按原数组下标建立线段树动态更新即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 1000050, p = 998244353, inf = 1000000000;

struct node {
	int x, id;
} a[N];
bool operator < (const node &x, const node &y) {
	return x.x < y.x;
}

int n, d, r, t[4 * N], f[N];
// t -> segment
// f -> dp

void modify(int k, int l, int r, int x, int z) {
	if (l == r) {
		t[k] = max(t[k], z);
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify(k + k, l, mid, x, z);
	else modify(k + k + 1, mid + 1, r, x, z);
	t[k] = max(t[k + k], t[k + k + 1]);
}

int query(int k, int l, int r, int x, int y) {
	if (l == x && r == y) return t[k];
	int mid = (l + r) >> 1;
	if (y <= mid) return query(k + k, l, mid, x, y);
	else if (x > mid) return query(k + k + 1, mid + 1, r, x, y);
	else return max(query(k + k, l, mid, x, mid), query(k + k + 1, mid + 1, r, mid + 1, y));
}

void init() {
	
}

void solve() {
	scanf("%d%d%d", &n, &d, &r);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].x), a[i].id = i;
	sort(a + 1, a + n + 1);
	int ans = 0;
	for (int i = 1; i <= 4 * n + 520; i++) t[i] = -1 << 30; // Too lazy to write build function
	for (int i = 2; i <= n; i++) {
		if (i - d >= 1) modify(1, 1, n, a[i - d].id, f[i - d]); // update
		int L = max(1, a[i].id - r), R = min(n, a[i].id + r);
		int res = query(1, 1, n, L, R);
		if (res >= 0) f[i] = res + 1;
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
}

int main() {
	init();
	int T = 1;
	// scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

省流：一道线段树优化 DP 状态转移板子。

注意到本题对移动路径进行图论建模后是一张有向无环图。这样，我们不难想到进行动态规划以高度倒着推上去。状态的线性设计和转移顺序都是显然的，关键看如何转移。

暴力枚举状态显然会超时，但我们发现，状态的转移来源是在一个已知区间里的，于是我们想到线段树维护区间最大值。再看约束条件 $H_j \le H_i−D$，注意到高度是个排列，于是我们具体可以将第 $i$ 次状态的在线段树上的更新延迟到 $i+D$ 次前即可。

[Code](https://atcoder.jp/contests/abc408/submissions/66364493)

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc408_f [ABC408F] 运动型 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc408_f)

### 题目大意

$N$ 个高度不一的梯子，高度分别是 $H_i$。初始选择一个梯子站在上面。

假设现在在 $i$ 梯上，可以选择跳到 $j$ 梯仅当：$1 \le |i - j| \le R$、$H_j \le H_i - D$。即水平和竖直有一定距离要求。

问一直到不能再跳的最大跳跃次数。

### 思路及实现

我们需要一个数据结构能够把高度满足条件的点先后纳入，并且在一定范围内高效查询极值。

这里加入高度满足的点只能越来越多。所以如果每次删掉一些不好维护。所以把梯子降序排序，再每次选择比当前高度高 $D$ 的梯子加入。

定义 $dp_i$ 表示以 $i$ 结尾的最长链长度，移动次数等于链长减 $1$。

然后我们就可以用线段树完成这个题目。

时间复杂度 $O(N \log_2 N)$，空间复杂度 $O(N)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, D, R;
struct node
{
    ll h, pos;
} a[500005];
bool cmp(node a, node b)
{
	return a.h > b.h;
}
ll tree[2000005];
ll dp[500005];
ll ans = 0;
void build(int id, int l, int r)
{
    if (l == r)
	{
        tree[id] = -9e18;
        return;
    }
    ll mid = (l + r) / 2;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    tree[id] = max(tree[id << 1], tree[id << 1 | 1]);
}
void update(int id, int l, int r, int pos, int val)
{
    if (l == r)
	{
        tree[id] = val;
        return;
    }
    ll mid = (l + r) / 2;
    if (pos <= mid) 
        update(id << 1, l, mid, pos, val);
    else 
        update(id << 1 | 1, mid + 1, r, pos, val);
    tree[id] = max(tree[id << 1], tree[id << 1 | 1]);
}
ll query(int id, int l, int r, int ql, int qr)
{
    if (ql > qr) 
        return -9e18;
    if (ql <= l && r <= qr) 
        return tree[id];
    ll mid = (l + r) / 2;
    ll res = -9e18;
    if (ql <= mid) 
        res = max(res, query(id << 1, l, mid, ql, qr));
    if (qr > mid) 
        res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
    return res;
}
int main()
{
    scanf("%lld%lld%lld", &N, &D, &R);
    for (int i = 1; i <= N; i++)
	{
        scanf("%lld", &a[i].h);
        a[i].pos = i;
    }
    sort(a + 1, a + N + 1, cmp);
    build(1, 1, N);
    for (int i = 1, j = 1; i <= N; i++)
	{
        while (j <= N && a[j].h >= a[i].h + D)
		{
            update(1, 1, N, a[j].pos, dp[a[j].pos]);
            j++;
        }
        ll l = max(1ll, a[i].pos - R), r = min(N, a[i].pos + R);
        dp[a[i].pos] = query(1, 1, N, l, r) + 1;
        if (dp[a[i].pos] < 0)
            dp[a[i].pos] = 0;
        ans = max(ans, dp[a[i].pos]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：sSkYy (赞：1)

## 题意

有 $N$ 个平台排成一列，每个平台有一个高度 $H_i$，你可以选择从任意一个平台开始，并在满足一定条件时，可以跳跃到其他平台上，求最大跳跃次数。

能从 $i$ 平台跳到 $j$ 平台，当且仅当满足以下条件：

- $H_j \leq  H_i-D$
- $|i-j|\leq R$

$D$ 和 $R$ 是给定的数字，$1\leq N \leq 5\times 10^5$。
## 题解

观察到数据范围，一般是贪心或者 DP，可能会夹杂一点数据结构。

我们考虑 DP，设 $dp_i$ 为从 $i$ 平台开始最多能跳多少步。

容易得到 DP 转移方程：

$$
dp_i=\max_{H_j \leq  H_i-D}^{|i-j|\leq R}(dp_j+1)
$$

直接转移复杂度是 $O(NR)$ 的，考虑优化。

先将 $|i-j|\leq R$ 写成 $i-R\leq j\leq i+R$，这是一段连续的区间，如果没有高度的限制，可以直接用线段树优化，即将 $dp_i$ 加入转移区间 $[i-R,i+R]$ ，那么加上高度的限制之后呢？

我们发现 DP 转移时高度时从低到高枚举的，也就是说，对于 $i$ 来说，满足高度的限制的 $j$ 是一段前缀区间 $[1,i-D]$,于是我们可以用一个队列缓存这些 $j$，每次在 $i$ 转移之前将队列中合法的 $j$ 加入线段树维护的转移区间，然后从队头弹出，队列中的 $j$ 的高度是严格单调递增的，最后将新的 $i$ 放入队列等待使用。

因为每个元素只会进一次队列，再加上线段树，总的时间复杂度是 $O(n \log n)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int N=5e5+5;

int n,d,r;
int pos[N],mx[N<<2];

void upd(int k,int l,int r,int x,int v){
	if(l==r){
		mx[k]=v;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) upd(ls,l,mid,x,v); 
	else upd(rs,mid+1,r,x,v);
	mx[k]=max(mx[ls],mx[rs]);
}
int qry(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return mx[k];
	int mid=l+r>>1,res=0;
	if(x<=mid) res=qry(ls,l,mid,x,y); 
	if(y>mid) res=max(res,qry(rs,mid+1,r,x,y));
	return res;
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin>>n>>d>>r;
	for(int i=1;i<=n;i++){
		int h;
		cin>>h;
        pos[h]=i;
	}
	
	queue<tuple<int,int,int>> q;
	int ans=0;
	for(int h=1;h<=n;h++){
		int i=pos[h];
		int L=max(1,i-r),R=min(n,i+r);
		while(!q.empty()){
			auto [H,x,v]=q.front();
			if(H>h-d) break;
			upd(1,1,n,x,v);
			q.pop();
		}
		int cur=qry(1,1,n,L,R)+1;
		q.push({h,i,cur});
		ans=max(ans,cur);
	}
	cout<<ans-1;
	return 0;
}
```

---

## 作者：3a51_ (赞：0)

简单题。~~赛时因为 `<=` 和 `>=` 打反多调了 15min 还吃了 3 发罚时。~~

首先显然有 dp 状态 $f_i$ 表示从 $i$ 脚手架开始移动最后能移动多少步。由于只能往高度更低的脚手架走，所以按照高度从小到大枚举转移。

维护一棵线段树记录当前所有可以被转移的位置的 $f$ 最大值。可以用一个类似双指针的东西维护一下哪些位置可以被转移。

转移的时候区间查询 $(x-r,x+r)$ 的 $f$ 最大值即可。时间复杂度 $O(n\log n)$。

[Submission](https://atcoder.jp/contests/abc408/submissions/66343966)

---

## 作者：zhangbo1000 (赞：0)

首先我们容易发现，从某个点能出发走几次，跟我们走到这个点的路径无关，再加上题目保证 $H$ 是个排列，不难想到我们应该按照每个点的高度来逐个考虑而不是按照排列顺序，不妨设 $dp_i$ 为从高度为 $i$ 的点出发最多走几次，$p_{H_i}=i$，那么显然，$dp_i$ 应是所有满足 $\max(1,p_i-R)\le p_j\le \min(n,p_i+R)$ 且 $j\le i-D$ 的 $dp_j$ 的最大值。

其中 $\max(1,p_i-R)\le p_j\le \min(n,p_i+R)$ 可以使用维护区间最大值的线段树搞定，$j\le i-D$ 的限制条件则可以“延迟”线段树更新：在计算 $dp_i$ 时才往线段树上“加入”$dp_{i-D}$。

[代码和评测记录。](https://atcoder.jp/contests/abc408/submissions/66397653)

---

## 作者：Crazyouth (赞：0)

## 分析

我们首先考虑倒着做，也就是每次跳高至少 $d$。

这样我们获得了一个思路，从小到大遍历 $1\sim n$ 所在的位置，$i$ 的位置记为 $pos_i$，并设它最多可以经过 $f_{pos_i}$ 轮跳上来，则我们要找 $[pos_i-r,pos_i+r]$ 中 $h_j\le i-d$ 的最大 $f_j$ 作为转移。如果我们能排除 $h_j\le i-d$ 的干扰，那么剩下的可以用线段树做完。那么排除干扰的方法很简单，我们让线段树中不存储 $h_j\in (i-d,i)$ 的信息即可，为了保证 $h_j=i-d$ 能随时访问，每次遍历新的 $i$ 时再更新 $i-d$ 的结果就行。时间复杂度 $O(n\log n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=500010;
int mx[N<<2],n,h[N],pos[N],d,r,dp[N];
void upd(int k,int c,int s=1,int t=n,int p=1)
{
	if(s==t)
	{
		mx[p]=max(mx[p],c);
		return; 
	}
	int m=s+t>>1;
	if(k<=m) upd(k,c,s,m,p<<1);
	else upd(k,c,m+1,t,p<<1|1);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int qry(int l,int r,int s=1,int t=n,int p=1)
{
	if(l<=s&&t<=r) return mx[p];
	int m=s+t>>1,ans=0;
	if(l<=m) ans=qry(l,r,s,m,p<<1);
	if(r>m) ans=max(ans,qry(l,r,m+1,t,p<<1|1));
	return ans;
}
int main()
{
	cin>>n>>d>>r;
	for(int i=1;i<=n;i++) cin>>h[i],pos[h[i]]=i;
	for(int i=1;i<=n;i++)
	{
		if(i>d) upd(pos[i-d],dp[pos[i-d]]);
		dp[pos[i]]=qry(max(1,pos[i]-r),min(n,pos[i]+r))+1;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	cout<<ans-1;
}

---

## 作者：Greenzhe (赞：0)

先明确题意：

- $n$ 栋楼排成一列，每栋楼有一个高度 $h_i$；

- 现在要从某一栋楼开始，不断在楼之间跳跃，从 $i$ 跳到 $j$ 要满足：

  - $j$ 至少比 $i$ 低 $D$ 个高度；（限制 $\textcircled{1}$）
  - $i,j$ 的横向距离不超过 $R$。（限制 $\textcircled{2}$）

- 求最多能跳多少次。

---

观察题目给出的两个限制。很显然，如果没有限制 $\textcircled{2}$，本题就类似一个 LIS 问题。

于是考虑 dp，设 $f_i$ 表示从第 $i$ 栋楼开始最多能跳跃的次数。转移方程为：$\displaystyle f_i = \max\{f_j\}+1$，其中 $j$ 满足限制 $\textcircled{1}$ 与 $\textcircled{2}$。

首先处理限制 $\textcircled{1}$。考虑转移顺序，可以发现我们只能从 $h_i$ 大的跳到 $h_i$ 小的。所以**将所有位置按 $h_i$ 排序**，按 $h_i$ 从小到大依次转移，计算 $f_i$ 的时刻为 $h_i$。

每次求 $f_i$ 时，就维护时刻 $h_i-D$ 以前的 $f_j$ 的最大值，这些 $f_j$ 的值一定是已经求出的。于是我们就处理完了限制 $\textcircled{1}$，相当于**把限制 $\textcircled{1}$ 放到了时间轴上去做**。

然后处理限制 $\textcircled{2}$，发现这是一个关于下标的限制，相当于求 $j \in [L(i),R(i)]$ 的 $f_j$ 的最大值，其中 $L(i)=i-R, R(i)=i+R$。考虑数据结构维护区间最大值。开一颗线段树，每次线段树求区间最大值得出 $f_i$，然后在 $h_i+D$ 的时刻把它更新到线段树上去即可。

代码：<https://atcoder.jp/contests/abc408/submissions/66337308>。

---

## 作者：Exscallop64_ (赞：0)

~切了 F 居然没切 E，小丑🤡。~

## 题目简述

$n$ 个脚手架，第 $i$ 个脚手架高度为 $H_i$，你可以选择从任意一个脚手架开始，从第 $i$ 个脚手架可以移动至脚手架 $j$ 当且仅当 $H_j \le H_i - D$ 且 $\vert i - j \vert \le R$，问你最多可以移动多少次。

## 思路

很经典的数据结构优化动态规划。

可以发现脚手架的高度不增，因此不妨先将脚手架按 $H_i$ 从大到小排序。

**排序后**，令 $h_i$ 为现在的第 $i$ 个脚手架的高度，$id_i$ 表示现在的第 $i$ 个脚手架在**原来**的编号。

此时我们可以写出 $O(n^2)$ 的子序列 DP，令 $dp_i$ 表示以**现在**第 $i$ 个脚手架结尾的最多可以**经过**多少脚手架，则有转移 $dp_i = \max_{1 \le j < i, h_j \ge h_i - D, \vert id_i - id_j \vert \le R} dp_j + 1$，初始时 $dp_i$ 为 $1$。

可以发现 $j$ 有两个较为强硬的限制，先来考虑 $h_j \ge h_i - D$。注意 $h$ 单调不增，我们可以使用双指针维护。

再来考虑 $\vert id_i - id_j \vert \le R$，所以 $\max(id_i - R, 1) \le id_j \le \min(id_i + R, n)$，显然是一段区间。

所以我们可以维护一棵单点修改、区间查询最大值的线段树，若线段树的叶子节点的区间为 $[x, x]$，则存储当 $id_j = x$ 时的 $dp_j$。

因此双指针维护时，每次当指针往右移动时对线段树进行修改，最后查询区间最大值即可。

答案即为 $\max_{i=1}^{n} dp_i - 1$，注意题目问的是最多移动次数，$dp$ 表示的是最多经过的脚手架数。

## 复杂度分析

+ 时间复杂度：线段树 + 双指针 $O(n \log n)$。

+ 空间复杂度：$O(4n) \approx O(n)$，注意线段树需要四倍空间。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using int128 = __int128;
using pii = pair<int, int>;

const int MAXN = 5e5 + 5;

int n, D, R, dp[MAXN];
pii a[MAXN];

struct Info{
  int mx;
};

struct SegTree{
  Info tr[MAXN << 2], E = {0};//注意四倍空间
  
  Info Comb(const Info &L, const Info &R){
  	return {max(L.mx, R.mx)};
  }
  
  void Modify(int i, int l, int r, int x, int k){
  	if(l == r){
  	  tr[i].mx = max(tr[i].mx, k);
	  return;	
	}
	int mid = (l + r) >> 1;
	x <= mid ? Modify(i << 1, l, mid, x, k) : Modify(i << 1 | 1, mid + 1, r, x, k);
	tr[i] = Comb(tr[i << 1], tr[i << 1 | 1]); 
  }
  
  Info Query(int i, int l, int r, int ql, int qr){
  	if(qr < ql || r < ql || qr < l) return E;
  	if(ql <= l && r <= qr) return tr[i];
  	int mid = (l + r) >> 1;
  	Info L = Query(i << 1, l, mid, ql, qr);
  	Info R = Query(i << 1 | 1, mid + 1, r, ql, qr);
  	return Comb(L, R);
  }
}T;

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> D >> R;
  for(int i = 1; i <= n; i++){
  	cin >> a[i].first;
	a[i].second = i;
  }
  sort(a + 1, a + 1 + n, greater<pii>());//此时的 first 便是 h[i]，second 即为 id[i]
  for(int i = 1, j = 1; i <= n; i++){
  	for(; j <= i && a[j].first - D >= a[i].first; j++){//双指针
  	  T.Modify(1, 1, n, a[j].second, dp[j]);	//修改
	}
	dp[i] = T.Query(1, 1, n, max(1, a[i].second - R), min(n, a[i].second + R)).mx + 1;
  }
  cout << *max_element(dp + 1, dp + 1 + n) - 1;
  return 0;
}
``````

---

## 作者：Xuan_qwq (赞：0)

同步发表于 [My blog](https://www.cnblogs.com/Xuan-qwq/p/18905640)。

>#### translation:
>给定一个排列 $p$，规定位置 $i$ 可以移动到任意满足 $|i-j|\le R,p_j\le p_i+D$ 的位置 $j$。问从某个位置开始，至多能做多少次移动。

一个 dp。朴素的想法是按照 $p_i$ 从大到小更新，每次取 $dp_i=1+\max_{|i-j|\le R,p_j\le p_i+D}dp_j$，但是我们发现这是平方量级的。

考虑如何优化。我们发现这个更新过程本质上是一个区间最大值，于是考虑线段树。初始时每个位置都是 $-1$，当我们更新到 $p_i$ 时，将 $p_{i}+D$（如果存在）的值更新到线段树内，然后查询区间最大值并记录即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,mx[2000005];
void pushup(int x){
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
}
void build(int x,int l,int r){
	if(l>r)return;
    if(l==r){
		mx[x]=-1;
		return;
	}
	int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
void upd(int x,int l,int r,int ps,int k){
	if(l==r){
		mx[x]=k;
		return;
	}
	int mid=(l+r)>>1;
	if(ps<=mid)upd(x<<1,l,mid,ps,k);
    else upd(x<<1|1,mid+1,r,ps,k);
    pushup(x);
}
int query(int x,int l,int r,int L,int R){
    if(L<=l&&r<=R)return mx[x];
	int mid=(l+r)>>1,res=-1;
    if(L<=mid)res=max(res,query(x<<1,l,mid,L,R));
    if(R>mid) res=max(res,query(x<<1|1,mid+1,r,L,R));
    return res;
}
int p[500005],ip[500005],R,D,ans[500005];
signed main(){
    cin>>n>>D>>R;
    for(int i=1;i<=n;i++)cin>>p[i],ip[p[i]]=i;
    build(1,1,n);
    for(int i=n;i>=1;i--){
    	if(i+D<=n)upd(1,1,n,ip[i+D],ans[i+D]);
    	int l=max(1ll,ip[i]-R);
    	int r=min(n,ip[i]+R);
    	ans[i]=query(1,1,n,l,r)+1;
	}
	int res=0;
	for(int i=1;i<=n;i++)res=max(res,ans[i]);
	cout<<res<<endl;
    return 0;
}
```

---

