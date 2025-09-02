# Minimum Array

## 题目描述

Given an array $ a $ of length $ n $ consisting of integers. Then the following operation is sequentially applied to it $ q $ times:

- Choose indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) and an integer $ x $ ;
- Add $ x $ to all elements of the array $ a $ in the segment $ [l, r] $ . More formally, assign $ a_i := a_i + x $ for all $ l \le i \le r $ .

Let $ b_j $ be the array $ a $ obtained after applying the first $ j $ operations ( $ 0 \le j \le q $ ). Note that $ b_0 $ is the array $ a $ before applying any operations.

You need to find the lexicographically minimum $ ^{\dagger} $ array among all arrays $ b_j $ .

 $ ^{\dagger} $ An array $ x $ is lexicographically smaller than array $ y $ if there is an index $ i $ such that $ x_i < y_i $ , and $ x_j = y_j $ for all $ j < i $ . In other words, for the first index $ i $ where the arrays differ, $ x_i < y_i $ .

## 说明/提示

In the first test case:

- $ b_0 = [1,2,3,4] $ ;
- $ b_1 = [1,2,3,4] $ ;
- $ b_2 = [-99,-98,-97,4] $ .

Thus, the lexicographically minimum array is $ b_2 $ .

In the second test case, the lexicographically minimum array is $ b_0 $ .

## 样例 #1

### 输入

```
2
4
1 2 3 4
2
1 4 0
1 3 -100
5
2 1 2 5 4
3
2 4 3
2 5 -2
1 3 1```

### 输出

```
-99 -98 -97 4 
2 1 2 5 4```

# 题解

## 作者：Milthm (赞：13)



教练给我们搬的一道题，放在了周赛（暂且这么称呼）的最后一题，没想到能做出来（虽然做了两天），纪念一下。~~虽然看完题解才发现我的做法是小丑~~。

首先考虑一个差分数组，根据差分基础知识，我们知道：

- 在 $[l,r]$ 区间加 $x$ 相当于差分数组 $b$ 上 $b_l$ 加上 $x$，$b_{r+1}$ 减去 $x$。

我们考虑如果差分数组第一个不为 $0$ 的数是小于 $0$ 的，那么一定比上一次记录答案时字典序小，记录本次答案。但是这只是对于第一次，容易发现只要把差分数组清空，那么就可以每次都这样，最后记录的那个答案就是最终答案。

然后因为我是很不会用 `set` 之类的东西的，所以我直接写了个线段树维护。维护两个变量，一个维护区间和，一个维护是否全部为 $0$。后来发现这么写会多一个“查询第一个不为 $0$ 的数”的操作，不过无所谓，线段树上直接找就可以。

最后亮出我的年度小丑代码：

### AC code

数组要开大一点，不然会像我一样调一个晚上。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000005;
int T,n,b[N],q,l[N],r[N],x[N],z[N*4],ans,diff[N]; 
struct Seg{
	int sum,qwq;
}a[N*4]; 
void pushup(int x){
	a[x]={a[x*2].sum+a[x*2+1].sum,a[x*2].qwq|a[x*2+1].qwq};
}
void pushdown(int x){
	if(z[x]){
		a[x*2]=a[x*2+1]={0,0};z[x*2]=z[x*2+1]=1;z[x]=0;
	}
}
void build(int x,int l,int r){
	if(l==r){
		a[x]={b[l],1};a[x*2]=a[x*2+1]={0,0};
		return;
	}
	int mid=(l+r)>>1;
	build(x*2,l,mid);build(x*2+1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,int k,int p){
	//cout<<l<<" "<<r<<" "<<k<<' '<<p<<'\n';
	//if(r>l)return;
	if(k==l&&k==r){
		a[x].sum+=p;
		if(a[x].sum!=0)a[x].qwq=1;
		else a[x].qwq=0;
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if(k<=mid)update(x*2,l,mid,k,p);
	else update(x*2+1,mid+1,r,k,p);
	pushup(x);
}
bool Find(int x,int l,int r){
	if(l==r&&a[x].qwq){
		if(a[x].sum>=0)return 0;
		else return 1;
	}
	int mid=(l+r)>>1;
	if(a[x*2].qwq)return Find(x*2,l,mid);
	else if(a[x*2+1].qwq)return Find(x*2+1,mid+1,r);
	else return 0;
}
signed main(){
	//freopen("F.in","r",stdin);
	//freopen("F.in","w",stdout);
	cin>>T;
	while(T--){
		ans=0;
		cin>>n;
		for(int i=1;i<=n;++i)scanf("%lld",&b[i]),diff[i]=b[i]-b[i-1];
		build(1,1,n);
		for(int i=1;i<=4*n;++i)a[i]={0,0},z[i]=0;
		cin>>q;
		for(int i=1;i<=q;++i){
			scanf("%lld%lld%lld",&l[i],&r[i],&x[i]);
			update(1,1,n,l[i],x[i]);
			if(r[i]<n)update(1,1,n,r[i]+1,-x[i]);
			if(Find(1,1,n)){
				ans=i;z[1]=1;a[1]={0,0};
			}
		}
		if(ans==0)for(int i=1;i<=n;++i)printf("%lld ",b[i]);
		else{
			for(int i=1;i<=ans;++i)diff[l[i]]+=x[i],diff[r[i]+1]-=x[i];
			int sum=0;
			for(int i=1;i<=n;++i){
				sum+=diff[i];printf("%lld ",sum);
			}
		}
		cout<<'\n';
	}
	return 0;
}


```


---

## 作者：樱雪喵 (赞：6)

被 A2 卡没时间了 /oh

## Description

给一个长度为 $n$ 的初始序列 $a$ 和 $q$ 次操作。每次操作形如给 $a_l\sim a_r$ 的值加上 $k$。

依次进行这些操作，求过程中得到过字典序最小的序列。

$n,q\le 5\times 10^5,\ -10^9\le a_i,k\le 10^9 $。

## Solution 1

考虑依次进行每个操作，维护当前能使答案字典序最小的**操作编号** $ans$。

只考虑从上一个 $ans$ 到当前时刻的操作，设它们操作后形成的序列为 $b$。那么当前的实际序列就是 $[1,ans]$ 的实际序列与 $b$ 数组对应位相加后的结果。

当前序列比 $[1,ans]$ 字典序更小的充要条件是 $b$ 中第一个不为 $0$ 的位置的值 $<0$，证明是显然的。每次修改后判断，满足这个条件就更新 $ans$，并清零 $b$ 数组。

也就是说我们只需要一个数据结构支持区间加、求第一个不为 $0$ 的位置、单点求值。

直接上线段树是可做的。不过发现第一个不为 $0$ 的位置只能是某个 $l_i$ 或 $r_i+1$，所以把这些点塞进 `set` 里暴力判断即可，区间加用树状数组维护。


## Solution 2

看了下官方题解。  

我们直接在差分数组上考虑这个问题，修改变成了单点，更新答案还是求第一个不为 $0$ 的位置。这样就不用写树状数组了。

```cpp
#define int long long
const int N=5e5+5,inf=1e9;
int t,n,a[N];
struct node{int l,r,k;} q[N];
struct BIT
{
    int tr[N];
    il void modify(int x,int k) {for(;x<=n;x+=x&(-x)) tr[x]+=k;}
    il void add(int l,int r,int k) {modify(l,k),modify(r+1,-k);}
    il int query(int x) {int res=0;for(;x;x-=x&(-x)) res+=tr[x];return res;}
}tr;
int ans;
signed main()
{
    int T=read();
    while(T--)
    {
        n=read(); ans=0;
        for(int i=1;i<=n;i++) a[i]=read(),tr.tr[i]=0;
        t=read(); set<int> st;
        for(int i=1;i<=t;i++) q[i].l=read(),q[i].r=read(),q[i].k=read();
        for(int i=1;i<=t;i++)
        {
            tr.add(q[i].l,q[i].r,q[i].k);
            st.insert(q[i].l),st.insert(q[i].r+1);
            while(st.size()&&!tr.query(*st.begin())) st.erase(st.begin());
            if(!st.empty()&&tr.query(*st.begin())<0)
            {
                for(int j=i;j>ans;j--) tr.add(q[j].l,q[j].r,-q[j].k);
                ans=i,st.clear();
            }
        }
        for(int i=1;i<=n;i++) tr.tr[i]=0;
        for(int i=1;i<=n;i++) tr.modify(i,a[i]-a[i-1]);
        for(int i=1;i<=ans;i++) tr.add(q[i].l,q[i].r,q[i].k);
        for(int i=1;i<=n;i++) printf("%lld ",tr.query(i));
        printf("\n");
    }
}
```

---

## 作者：Neil_Qian (赞：5)

# CF1887C Minimum Array 题解

## 题目描述

给定一个长度为 $n$ 的序列 $a$，共 $Q$ 次操作，每次将区间 $[l,r]$ 每个数加上 $k$，求所有 $a$序列中字典序最小的（包括初始状态）。$n,Q\le 5\times 10^5$，多测。

## 解决方案

其实一开始的 $a$ 序列的值到底时多少不重要，所有序列加上 $a$ 序列后字典序排序显然不变。回到字典序的定义：第一个 $j$ 使得所有 $1\le i<j$，有 $a_i=b_i$ 且 $a_j\not=b_j$，此时 $a_j$ 和 $b_j$ 哪个小哪个序列的字典序就小。那么显然，将长度相同的序列 $a,b$ 同时加上一个序列 $c$，它们长度相同，那么 $a,b$ 的字典序大小不变，因为 $a_j+c_j$ 和 $b_j+c_j$ 的大小关系与上文相同。

同样，利用这个性质，令 $c_i=-a_i$，故比较 $b_j-a_j$ 和 $0$ 的大小即可，也就是比较两个数组的差和全是 $0$ 的序列的大小。但仍然比较复杂，不难发现其实可以直接用差分数组，因为第一个不为 $0$ 的位置的数显然一样。于是问题转化成一个序列，支持单点修改、查找第一个不为 $0$ 的位置的数，就是一个简单的线段树问题。

拉回原题，找到一个更好的，直接把线段树清空，可以把操作反着做一遍即可。注意可能是初始序列，最后加上 $a$ 序列本身即可。时间复杂度 $O((n+Q)\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;const int N=5e5+2;
struct SegmentTree{
	ll val[N<<2];bool zero[N<<2];
	inline void init(ll x,ll l,ll r){//初始化
		zero[x]=1,val[x]=0;
		if(l==r)return;
		ll mid=(l+r)>>1;init(x<<1,l,mid),init(x<<1|1,mid+1,r);
	}
	inline void update(ll x,ll l,ll r,ll p,ll k){//差分数组-单点修改
		if(l==r){val[x]+=k,zero[x]=(!val[x]);return;}
		ll mid=(l+r)>>1;
		if(p<=mid)update(x<<1,l,mid,p,k);
		else update(x<<1|1,mid+1,r,p,k);
		zero[x]=zero[x<<1]&&zero[x<<1|1];
	}
	inline ll query(ll x,ll l,ll r){//查询第一个不为0的数
		if(zero[x])return -1e18;
		if(l==r)return val[x];
		ll mid=(l+r)>>1;
		if(zero[x<<1])return query(x<<1|1,mid+1,r);
		else return query(x<<1,l,mid);
	}
}sgt;ll T,n,a[N],Q,l[N],r[N],k[N],d[N],res,ans;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>T;
	while(T--){
		cin>>n,ans=0,sgt.init(1,1,n);
		for(ll i=1;i<=n;i++)cin>>a[i];
		cin>>Q;
		for(ll i=1;i<=Q;i++){
			cin>>l[i]>>r[i]>>k[i],sgt.update(1,1,n,l[i],k[i]);
			if(r[i]!=n)sgt.update(1,1,n,r[i]+1,-k[i]);//更新差分数组
			res=sgt.query(1,1,n);
			if(res==-1e18)continue;
			if(res<0){
				for(int j=ans+1;j<=i;j++){//清空
					sgt.update(1,1,n,l[j],-k[j]);
					if(r[j]!=n)sgt.update(1,1,n,r[j]+1,k[j]);
				}
				ans=i;
			}
		}
		fill(d+1,d+n+1,0);
		for(ll i=1;i<=ans;i++)d[l[i]]+=k[i],d[r[i]+1]-=k[i];
		for(ll i=1;i<=n;i++)d[i]+=d[i-1];
		for(ll i=1;i<=n;i++)cout<<d[i]+a[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：ケロシ (赞：2)

是题解里没有的做法。

考虑到字典序是从第一位开始依次往后比较，
对于 $m+1$ 个版本，考虑对于时间轴建立线段树，
若第 $i$ 次操作为 $[l,r]$ 加上 $x$ 的操作则可以转变为了 $[l,r]$ 在版本中 $[i,m]$ 加上了 $x$，这可以将 $[l,r]$ 差分后推进线段树，即为到 $l$ 时 $[i,m]$ 区间加 $x$，到 $r+1$ 时 $[i,m]$ 区间减 $x$。

过程是每次保留最小的，但是可能有多个最小值。
反过来考虑，一个版本若不优，则只会被丢一次，所以暴力将大的扔掉即可，时间复杂度 $O(n\log m)$。

```cpp
const int N = 5e5 + 5;
const ll LNF = 1e18 + 117;
int n, m, a[N];
vector<PII> e[N];
struct SgT {
	int le[N << 2], ri[N << 2];
	ll F[N << 2], G[N << 2], T[N << 2];
	void pushup(int u) {
		F[u] = max(F[u << 1], F[u << 1 | 1]);
		G[u] = min(G[u << 1], G[u << 1 | 1]);
	}
	void push(int u, ll x) {
		F[u] += x, G[u] += x;
		T[u] += x;
	}
	void pushdown(int u) {
		if(T[u]) {
			push(u << 1, T[u]);
			push(u << 1 | 1, T[u]);
			T[u] = 0;
		}
	}
	void build(int u, int l, int r) {
		le[u] = l, ri[u] = r;
		T[u] = 0;
		if(l == r) {
			F[u] = G[u] = 0;
			return;
		}
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void modify(int u, int l, int r, int x) {
		if(l <= le[u] && ri[u] <= r) {
			push(u, x);
			return;
		}
		pushdown(u);
		int mid = le[u] + ri[u] >> 1;
		if(l <= mid) modify(u << 1, l, r, x);
		if(mid < r) modify(u << 1 | 1, l, r, x);
		pushup(u);
	}
	void maintain(int u, ll x) {
		if(F[u] <= x) return;
		if(le[u] == ri[u]) {
			G[u] = LNF;
			F[u] = -LNF;
			return;
		}
		pushdown(u);
		maintain(u << 1, x);
		maintain(u << 1 | 1, x);
		pushup(u);
	}
} t;
void solve() {
	cin >> n;
	FOR(i, 1, n) cin >> a[i];
	cin >> m;
	FOR(i, 1, n) e[i].clear();
	FOR(i, 1, m) {
		int l, r, x;
		cin >> l >> r >> x;
		e[l].push_back({i, x});
		e[r + 1].push_back({i, - x});
	}
	t.build(1, 0, m);
	FOR(i, 1, n) {
		for(auto h : e[i])
			t.modify(1, FI(h), m, SE(h));
		cout << t.G[1] + a[i] << " ";
		t.maintain(1, t.G[1]);
	}
	cout << endl;
}
```

---

## 作者：菲斯斯夫斯基 (赞：2)

## CF1887C Minimum Array 题解

妙妙题。

题意明了，不再赘述。

### 思路

不难想到暴力：暴力修改区间，然后比较取最优。

这样做的复杂度是 $\mathcal{O}(n^2)$ 的，考虑如何优化。

回归题目，显然加**负数**更优。所以可以发现**若第一个加了非 $0$ 的数**加上了负数，那么会比原答案更优。

注意到是每做一次操作就要取优，所以发现更优的答案时就要更新，**然后视为所有的数都没有操作**。（实际上就是清空）

区间加不难想到这些东西：线段树（树状数组）、差分。

把刚才的操作都搞到线段树上面去，是其中一种方法。

但是不用这么麻烦。因为第一个被操作的数都在边界，所以可以用差分处理区间加，开一个 `set` 记录差分中修改过的位置，注意当某个位置为 $0$ 时踢出 `set`。

代码实现是容易的，细节是多测清零的时候要清到第 $n+1$ 位。

[Code](https://codeforces.com/contest/1887/submission/253497444)

---

## 作者：CarroT1212 (赞：1)

VP 时的我：

问：维护区间加的方法有什么？

答：暴力，线段树，树状数组！

然后漏了一个差分。

差分强在哪？差分数组不仅可以直接用来比较题目中 $q$ 个序列的字典序，而且只要记录两个序列对应的操作中间出现的差分变化（而不需要从第一次询问开始），就能做到比较它们的**相对**字典序，而且的而且，每次只需要更改两个值。

也就是说，只要弄个 `set` 维护所有差分被修改过的位置，如果一次修改后发现第一个改过的位置小于 $0$ 就说明目前的序列是最小值，更新结果后清空差分数组，从这一次操作开始重新统计，不断重复以上过程即可……

```cpp
ll n,a[N],ans,cf[N];
ll q,cl[N],cr[N],cx[N],b[N];
void mian() {
	scanf("%lld",&n);
	ans=0,memset(cf,0,n+1<<3),memset(b,0,n+1<<3);
	for (ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	scanf("%lld",&q);
	set<ll> s;
	for (ll i=1;i<=q;i++) {
		scanf("%lld%lld%lld",&cl[i],&cr[i],&cx[i]);
		b[cl[i]]+=cx[i],b[cr[i]+1]-=cx[i];
		if (b[cl[i]]) s.insert(cl[i]);
		else if (s.count(cl[i])) s.erase(cl[i]);
		if (b[cr[i]+1]) s.insert(cr[i]+1);
		else if (s.count(cr[i]+1)) s.erase(cr[i]+1);
		if (s.size()&&b[*s.begin()]<0) {
			for (ll i:s) b[i]=0;
			s.clear(),ans=i;
		}
	}
	for (ll i=1;i<=ans;i++) cf[cl[i]]+=cx[i],cf[cr[i]+1]-=cx[i];
	for (ll i=1;i<=n;i++) cout<<a[i]+(cf[i]+=cf[i-1])<<" ";
	cout<<"\n";
}
```

---

## 作者：AC_love (赞：0)

因为两种修改方式都是在原序列的基础上进行修改，因此原序列是什么其实并不重要。我们考虑直接在差分数组上做。

首先我们考虑：对于第一次操作，怎么判断它会不会让字典序变得更小呢？

不难发现：如果差分数组第一个不为 $0$ 的数是负数，那么字典序就会变小，反之则变大。

但这样我们只能判断第一次操作相比原序列的大小，考虑这玩意怎么推广。

不妨每次求出一个最小值就把差分数组清零，此后只要发现第一个非 $0$ 的数是负数就相当于发现了一个新的最小值，再次清零，以此类推。

考虑怎么求第一个非 $0$ 的数是正是负。

显然可以直接用线段树或树状数组来做。

---

## 作者：1234567890sjx (赞：0)

~~【】本不愿写题解的。她老了，身体不好，写题解多一点儿就觉得累。我说，正因为如此，才应该多写题解。【】信服地点点头，便去拿电脑。她现在很听我的话，就像我小时候很听她的话一样。~~

lxoi 的 T6，感觉有点水。

容易发现，原来的 $a$ 数组的值对答案毫无影响。因此考虑把 $a$ 数组中的所有元素全部看作 $0$，到最后计算答案的时候再加上。

然后考虑差分。令 $f_i=a_i-a_{i-1}$，显然初始时 $f_i=0$。然后考虑用 `set` 来动态维护执行到第 $i$ 次操作之后有哪一些 $f_i$ 的值不为 $0$。显然执行一次把 $l_i\sim r_i$ 这一段区间内的所有元素全部加上 $v_i$ 的操作，只需要在差分数组 $f$ 上更新 $l$ 和 $r+1$ 两个位置的值。

初始设原数组为最优解。判定新的数组是否比原数组更优秀只需要贪心的判断当前第一个在差分数组上下标不为 $0$ 的位置的值是否小于 $0$ 即可。若小于 $0$ 那么将当前数组覆盖原数组成为最优解，并以当前数组为目标做差分即清空差分数组。显然只需要清空所有非 $0$ 的位置，总的清空的数量级是 $O(\min(n,m))$ 级别的。

记录一下是第几次操作得到最优解的即可，最后重新做差分然后跑前缀和得到真实的原数组。单组数据的时间复杂度为 $O(n\log n)$，瓶颈在于 `set` 的基本操作为 $O(\log n)$。代码才 $80$ 行不到，很好写。

注意：多测不清空，抱铃两行泪。

---

## 作者：August_Light (赞：0)

# CF1887C Minimum Array 题解

差分、map（平衡树）。

[题目传送门](https://www.luogu.com.cn/problem/CF1887C)

## 题意简述

给定一个 $n$ 个元素的整数序列 $a$，有 $q$ 次区间加（加的数可以为负），求出所有操作产生的新序列中字典序最小的那个。

$1 \le n,q \le 5 \times 10^5$，$-10^9 \le a_i \le 10^9$。

## 解法

序列字典序最小等价于差分序列字典序最小。区间加变为两次单点修改。

如果一个时刻，差分序列的第一个非 $0$ 数是负数，则此时这个序列一定比初始序列的字典序小。

我们将此时的序列设为答案，并认为此时的序列是初始序列，将差分序列清零，重复这个过程即可。

所以我们需要一个数据结构来维护：

- 修改：单点加。
- 查询：第一个非零数。

平衡树非常合适。这个平衡树不需要支持查询第 $k$ 小，所以一个 `std::map` 就可以胜任。

若认为 $n,q$ 同阶，则时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 5;

ll a[MAXN], dif[MAXN];
map<int, ll> mp;
int l_[MAXN], r_[MAXN]; ll x_[MAXN];

int main() { ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int ans = 0;
        int q; cin >> q; for (int i = 1; i <= q; i++) {
            int l, r; ll x; cin >> l >> r >> x; l_[i] = l; r_[i] = r, x_[i] = x;
            mp[l] += x;
            if (r+1 <= n)
                mp[r+1] -= x;
            while (!mp.empty() && mp.begin()->second == 0)
                mp.erase(mp.begin());
            if (!mp.empty() && mp.begin()->second < 0) {
                ans = i;
                mp.clear();
            }
        }
        for (int i = 1; i <= ans; i++) {
            int l = l_[i], r = r_[i]; ll x = x_[i];
            dif[l] += x;
            if (r+1 <= n)
                dif[r+1] -= x;
        }
        for (int i = 1; i <= n; i++) {
            dif[i] += dif[i-1];
            a[i] += dif[i];
            cout << a[i] << " \n"[i == n];
        }

        // init
        for (int i = 1; i <= n; i++)
            dif[i] = 0;
        mp.clear();
    }
    return 0;
}
```


---

## 作者：RockyYue (赞：0)

最暴力的想法是从前往后每个操作执行，比较每次操作执行后序列的字典序，这样是 $O(n^2)$ 的。

执行这一步是不可以省略的，可以用一些更优的方式维护，瓶颈在于比较字典序部分。因为执行的操作是区间加，可以想到用以下方式判断两个序列 $a_{1\dots n}$ 和 $b_{1\dots n}$ 字典序大小：

> 记 $c_i=b_i-a_i$，则若 $c$ 中第一个非零位为负数，$b$ 的字典序比 $a$ 更小。

还有一个性质：要求选取的操作是操作序列的前缀。于是我们利用上述方式比较，设当前处理到操作 $i$，$a$ 为在前 $i$ 个操作中选择一个前缀操作可以得到的字典序最小的序列，$b$ 为操作全部前 $i$ 个操作的结果序列。我们并不需要维护 $a$ 和 $b$ 两个序列，只需要维护 $c$ 即可判断，具体地：

- 原数组初始值并不重要，故我们将其置为 $0$，最后将答案对应位加上原数组对应位的值即可。
- 对于一次操作，如果这次加的值为非负数，执行操作即可，这次操作不可能成为最优操作的结束位置。
- 若这次加的值是负数，记当前最优操作前缀为 $1\dots k$，当前处理到操作 $i$，那么我们要判断从操作 $k+1$ 一直到操作 $i$ 这一段执行后是否可以使序列字典序更小。
- 我们现在需要的 $c$ 即为一个初始全 $0$ 的数组，经过操作 $k+1\dots i$ 后的结果，在这个过程中要维护第一个非零位的正负性。
- 需要操作 $k+1\dots i$ 的结果，我们可以想到若执行操作 $1\dots i$ 优于 $1\dots k$，即当前前缀是新的最优前缀，就将 $c$ 清空，问题转化为如何在区间加时维护第一个非零位的正负性。
- 这里的方法是，使用线段树维护，记录线段树上每个节点对应区间中是否有非零位，这样就可以找到第一个非零位，再判断其值的正负性即可。
- 最终我们得到最优操作前缀，模拟对应操作再加上初始值即可，复杂度 $O(T n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
ll a[N];
int l[N], r[N]; ll k[N];
ll s[N << 2], d[N];
bool not0[N << 2];
vector<int> U;
void upd(int id, int l, int r, int x, ll v) {
	U.push_back(id);
	if (l == x && r == x) {
//		cout << "pre: " << l << ' ' << s[id] << '\n';
		s[id] += v;
		if (s[id] == 0) not0[id] = 0;
		else not0[id] = 1;
//		cout << "upd: " << l << ' ' << x << ' ' << v << ' ' << s[id] << ' ' << not0[id] << '\n';
		return ;
	}
	if (l == r) return ;
	int mid = (l + r) >> 1;
	if (x <= mid) upd(id << 1, l, mid, x, v);
	else upd(id << 1 | 1, mid + 1, r, x, v);
	not0[id] = not0[id << 1] | not0[id << 1 | 1];
}
int n;
bool firneg(int id, int l, int r) {
//	cout << l << ' ' << r << ' ' << s[id] << '\n';
	if (l == r) return s[id] < 0;
	int mid = (l + r) >> 1;
	if (not0[id << 1]) return firneg(id << 1, l, mid);
	if (not0[id << 1 | 1]) return firneg(id << 1 | 1, mid + 1, r);
	return 0;
}
void cls() {
	for (int x : U) s[x] = not0[x] = 0;
	U.clear();
}
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		int q; cin >> q;
		for (int i = 1; i <= q; ++i) {
			cin >> l[i] >> r[i] >> k[i];
			if (!k[i]) --q, --i;
		}
		int i = 1, to = 0;
		while (1) {
			int j = i;
			while (k[j] > 0) ++j;
			if (j > q) break;
			for (int p = i; p <= j; ++p) upd(1, 1, n, l[p], k[p]), upd(1, 1, n, r[p] + 1, -k[p]);
//			cout << "test: " << i << ' ' << j << ' ' << firneg(1, 1, n) << '\n';
			if (firneg(1, 1, n)) to = j, cls();
			i = j + 1;
			if (i > q) break;
		}
		for (int i = 0; i <= n + 5; ++i) d[i] = 0;
		for (int i = 1; i <= to; ++i) d[l[i]] += k[i], d[r[i] + 1] -= k[i];
		for (int i = 2; i <= n; ++i) d[i] += d[i - 1];
		for (int i = 1; i <= n; ++i) cout << d[i] + a[i] << ' '; cout << '\n';
		for (int i = 0; i <= (n << 2) + 5; ++i) s[i] = not0[i] = 0;
	}
	return 0;
}
```



---

## 作者：henrytb (赞：0)

首先序列初始长成啥样是不重要的，完全可以当成 $0$ 来做。然后考虑字典序最小等价于差分数组的字典序最小（应该可以归纳证明）。令初始答案时刻为 $0$，我们维护这个差分数组，然后假如当前的这个差分数组的第一个非 $0$ 位置 $< 0$，就令答案时刻 $=$ 当前时刻，然后把差分数组清空继续做。感觉显然是对的。因为这样的话每次更改答案的时候字典序一定都较先前变小了。

我赛时脑抽用了线段树，其实用 `set` 也是可以的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 5e5 + 5;
int _, n, a[N], q;
int bok[N];
int l[N], r[N], x[N];
struct Segment {
    int l, r, fst, val;
} t[N << 2];
inline void pushup(int p) {
    if (t[p << 1].fst) t[p].fst = t[p << 1].fst;
    else t[p].fst = t[p << 1 | 1].fst;
}
void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r; t[p].fst = 0; t[p].val = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}
void modify(int p, int pos, int val) {
    if (t[p].l == t[p].r) {
        // printf("de:%lld\n", t[p].l);
        t[p].val += val;
        if (!t[p].val) t[p].fst = 0;
        else t[p].fst = t[p].l;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if (pos <= mid) modify(p << 1, pos, val);
    else modify(p << 1 | 1, pos, val);
    pushup(p);
}
signed main() {
    for (scanf("%lld", &_); _; --_) {
        scanf("%lld", &n);
        rep(i, 1, n) scanf("%lld", &a[i]), bok[i] = 0;
        build(1, 1, n);
        scanf("%lld", &q);
        int res = 0, lst = 1;
        rep(i, 1, q) {
            scanf("%lld%lld%lld", &l[i], &r[i], &x[i]);
            bok[l[i]] += x[i];
            bok[r[i] + 1] -= x[i];
            modify(1, l[i], x[i]);
            if (r[i] < n) modify(1, r[i] + 1, -x[i]);
            int pos = t[1].fst;
            if (bok[pos] < 0) {
                res = i;
                rep(j, lst, i) {
                    bok[l[j]] -= x[j];
                    bok[r[j] + 1] += x[j];
                    modify(1, l[j], -x[j]);
                    if (r[j] < n) modify(1, r[j] + 1, x[j]);
                }
                lst = res + 1;
            }
        }
        rep(i, 1, n) bok[i] = 0;
        rep(i, 1, res) bok[l[i]] += x[i], bok[r[i] + 1] -= x[i];
        partial_sum(bok + 1, bok + n + 1, bok + 1);
        rep(i, 1, n) printf("%lld ", a[i] + bok[i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：impuk (赞：0)

一个无脑哈希做法。

区间加太不好维护了，所以对原数组进行差分。容易看出如果一个数组差分字典序大于另一个数组差分，那么它不差分字典序也一定大于另一个数组。

所以一个区间加被拆成两个单点加操作。

然后这个题要我们找到所有历史数组中最小的数组，对于 $O(n^2)$ 的暴力，我们可以很容易写出如下内容：

```
min=a[0],now=a[0]
for operation in input:
   now.apply(operation)
   if min>now:
      min=now
```
对于这个暴力中的每一个 $O(n^2)$ 的部分，都可以很容易的优化至 $O(n\log n)$，然后通过此题。

对于 `min>now` 的比较部分，可以在线段树上二分，找到第一个哈希值不同的位置（这里可以使用多项式哈希），然后只比较第一个不同的位置，返回结果。

对于赋值部分，可以简单的记录一下 `min` 上一次被赋值的位置，然后添加上一次到现在中 `now` 经过的所有操作。显然总修改次数是 $O(q)$ 的。

但是，这么写会因为 $2\times10^6$ 个线段树操作卡满被卡常，所以需要一些比较晦气的卡常手法，这里介绍两个。

第一个是 `__int128` 乘法很慢，可以使用如下代码代替，然后能擦边冲过去。
```
inline long long mmul(long long a,long long b,const long long& Mod) {
   long long lf=a*(b>>25LL)%Mod*(1LL<<25);
   long long rg=a*(b&((1LL<<25)-1));
   return (lf+rg)%Mod;
}
```

或者说，第二个，实际上我们并不需要多项式哈希，因为每两个比较的位置都是相同的，例如我们对 `now` 查询 $[l,r]$ 时，对 `min` 的查询也必定是相同的 $[l,r]$。因此哈希函数可以简单的设置为 $(\text{base}^{\text{idx}}\times a_i)\bmod p$，此处 $\text{base}$ 需要是一个 $10^{15}$ 级别的数。预处理 $\text{base}^{\text{idx}}$ 之后线段树的 `pushup` 只需要异或即可。

代码（使用第一个优化）： 
```
#include "bits/stdc++.h"
using namespace std;
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
const long long mod=1000000000000000003,base=904654042736697;
long long pw[1000001];
inline long long mmul(long long a,long long b,const long long& Mod) {
   long long lf=a*(b>>25LL)%Mod*(1LL<<25);
   long long rg=a*(b&((1LL<<25)-1));
   return (lf+rg)%Mod;
}
template <class node> class segment1 {
   private:
      int id(int l,int r){return (l+r)|(l!=r);}
      void change(int l,int r,int x,node &y){if(l==r){seg[id(l,r)]=y;return;}int mid=(l+r)/2;if(x<=mid)change(l,mid,x,y);else change(mid+1,r,x,y);seg[id(l,r)]=node::merge(seg[id(l,mid)],seg[id(mid+1,r)]);}
      node query(int L,int R,int l,int r){if(l<=L&&R<=r)return seg[id(L,R)];int mid=(L+R)/2;if(l<=mid&&r>mid)return node::merge(query(L,mid,l,r),query(mid+1,R,l,r));if(l<=mid)return query(L,mid,l,r);return query(mid+1,R,l,r);}
      void build(int l,int r,node &y){if(l==r){seg[id(l,r)]=y;return;}int mid=(l+r)/2;build(l,mid,y);build(mid+1,r,y);seg[id(l,r)]=node::merge(seg[id(l,mid)],seg[id(mid+1,r)]);}
   public:
      vector<node> seg;int siz;
      void init(int n,node y){siz=n;seg.resize(2*n+4);build(1,siz,y);}
      void change(int x,node y){change(1,siz,x,y);}
      node query(int l,int r){return query(1,siz,l,r);}
};
struct node { // 线段树的合并规则，这里使用多项式哈希
   long long value;
   int len;
   static inline node merge(node a,node b) {
      return {(mmul(a.value,pw[b.len],mod)+b.value+mod)%mod,a.len+b.len};
   }
};
long long n,q,P1[500002],P2[500002];
int l[500002],r[500002],x[500002],a[500002];
void Delta() {
   cin >> n;
   for(int i=1;i<=n;++i) {
      cin >> a[i];
      P1[i]=P2[i]=0;
   }  
   P1[n+1]=P2[n+1]=0;
   segment1<node> Q1,Q2;
   Q1.init(n+1,{0,1});Q2.init(n+1,{0,1});
   cin >> q;
   for(int i=1,pt=0;i<=q;++i) {
      cin >> l[i] >> r[i] >> x[i];
      P2[l[i]]+=x[i];P2[r[i]+1]-=x[i];
      for(int j:{l[i],r[i]+1}) Q2.change(j,{(P2[j]+mod)%mod,1});
      if(Q1.query(1,n).value!=Q2.query(1,n).value) {
         int L=1,R=n+1;
         while(L!=R) { // 线段树上找到第一个不同的位置，记录为 L
            int M=(L+R)/2;
            if(Q1.seg[(L+M)|(L!=M)].value==Q2.seg[(L+M)|(L!=M)].value) L=M+1;
            else R=M;
         }
         if(P1[L]>P2[L]) { // 比较不同的位置，获得结果
            for(int j=pt+1;j<=i;++j) { // 一个类似双指针的玩意，保证总循环次数为 O(p)
               P1[l[j]]+=x[j];
               P1[r[j]+1]-=x[j];
               for(int k:{l[j],r[j]+1}) Q1.change(k,{(P1[k]+mod)%mod,1});
            }
            pt=i; // 更新位置
         }
      }
   }
   for(int i=1;i<=n;++i) P1[i]+=P1[i-1];
   for(int i=1;i<=n;++i) cout << P1[i]+a[i] << ' ';
   cout << endl;
}
signed main() {
   pw[0]=1;
   for(int i=1;i<=1000000;++i) pw[i]=mmul(pw[i-1],base,mod);
   ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
   int T=1; cin >> T;
   while(T--) Delta();
}
```

---

## 作者：耶梦加得 (赞：0)

显然 $a$ 数组没啥用，我们只关心后面的修改

官方做法：

我们依次遍历每个修改，设当前考虑的是第 $i$ 个修改。维护一个值 $j$ 表示目前为止字典序最小的 $b$ 为 $b_j$，同时维护第 $j+1$ 到 $i$ 个修改带来的影响。显然，当最靠左的被修改的位置 $\Delta < 0$ 我们用 $i$ 更新 $j$，反之我们继续考虑下一个修改。

为了简化问题，我们稍加思考可以发现，要求数组字典序最小，等于要求**差分数组**字典序最小。感性理解一下，假如差分数组比较到第 $p$ 个数，那么前面 $p-1$ 位的差分显然是一样的（不然就已经分出大小了），在原数组上的贡献就抵消了。

此时区间修改简化为两个单点修改。前面我们要求维护 $(j, i]$ 这些修改的影响，我们可以用一个 map ，以修改的位置为关键字，每个位置上的 $\Delta$ 为值。每次插入（或修改）两个值。查找“最靠左的被修改的位置”直接 mp.begin() 即可，但要注意这个位置上的修改可能互相抵消了，这时候要把它 erase 掉继续找下一个位置。

代码（官方做法）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 500007;
int T;
int n, m;
int a[N];
int l[N], r[N], v[N];
long long d[N];
map<int, long long> mp;
signed main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        scanf("%d", &m);
        int cur = 0;
        mp.clear();
        for(int i = 1; i <= m; ++i) {
            scanf("%d %d %d", &l[i], &r[i], &v[i]);
            if(mp.count(l[i])) mp[l[i]] += v[i];
            else mp[l[i]] = v[i];
            if(r[i] < n) {
                if(mp.count(r[i] + 1)) mp[r[i] + 1] -= v[i];
                else mp[r[i] + 1] -= v[i];
            }
            while(!mp.empty() && mp.begin() -> second == 0) mp.erase(mp.begin());
            if(!mp.empty() && mp.begin() -> second < 0) {
                cur = i; mp.clear();
            }
        }
        for(int i = 1; i <= cur; ++i) {
            d[l[i]] += v[i]; d[r[i] + 1] -= v[i];
        }
        for(int i = 1; i <= n; ++i) {
            d[i] += d[i - 1];
            printf("%lld ", d[i] + a[i]);
        }
        puts("");
        for(int i = 1; i <= n + 1; ++i) d[i] = 0;
    }
    return 0;
}

```
顺带一提我赛时不是模拟修改，而是直接从左往右枚举位置然后排除劣的修改……特别蠢的做法……[赛时代码](https://www.luogu.com.cn/paste/1k3lo80l)

---

## 作者：zhongpeilin (赞：0)

## 题目大意：
有个数组 $A$，现在有 $Q$ 次操作，第 $i$ 此操作形如 $l_{i}, r_{i}, x_{i}$ 表示 将 $A_{l_{i}} \sim A_{r_{i}}$ 都加上 $x_{i}$。现在设 $b_{i}$ 表示 $A$ 在 操作 $i$ 次以后的操作。那么字典序最小的 $b$ 是什么？

## 解题思路：
首先我们不难想到一个 $O(nq)$ 的做法，就是暴力加，然后暴力检查，但是显然这里是过不掉的，我们考虑优化。  
首先，字典序这个东西很难直接维护，所以我们考虑一下怎样才能去方便维护。举个栗子，要比较 $3, 2, 1, 4 ,3$ 和 $3, 2, 1, 3, 4$，但是只需要比较字典序，我们发现只需要将他们作差，然后判断第一个非 $0$ 数是正数还是负数就行！  
而上面所说的就可以和区间加一块用 **单侧递归线段树** 解决，具体怎么做呢？因为我们发现，首先要找出第一个非 $0$ 的位置，当递归到 $u$ 时，如果 $u \times 2$ 的 $minn$ 和 $maxn$ 都为 $0$，那么说明左儿子全为 $0$，递归右儿子，否则，递归左儿子。求出第一个非 $0$ 位置后，只需要单点查询即可。  
接下来考虑因为只需要比较变化数组，所以 $A$ 就没用了，初始化成 $0$，但是通过上面的操作，我们发现还会有很多很多操作满足第一个非 $0$ 的位置上是负数，暴力比较还是 $O(nq)$ 的，所以考虑只需要和之前的最优解比较，但是问题又来了，我们不能直接存变化数组，那怎么办？**我们只需要维护的变成之前的最优决策点后一个位置到 $i$ 的变化数组就行，也相当于我们可以将上一个最优决策点到上上个决策点的改变减去即可**，均摊 $O(q)$ 次，总复杂度为 $O(q \log n)$，就可通过此题。  
## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
 
struct Segment_Tree{
	int minn, maxn;
}tree[2000005];
 
struct query{
	int l, r, val;
}Q[500005];
int lazy[2000005], n, q, a[500005];
 
void push_up(int u){//最大值最小值
	tree[u].minn = min(tree[u * 2].minn, tree[u * 2 + 1].minn);
	tree[u].maxn = max(tree[u * 2].maxn, tree[u * 2 + 1].maxn);
}
void push_down(int u){ //记得lazy[u] = 0
	tree[u << 1].minn += lazy[u]; //都加上
	tree[u << 1].maxn += lazy[u];
	lazy[u << 1] += lazy[u];
	
	tree[u << 1 | 1].minn += lazy[u];
	tree[u << 1 | 1].maxn += lazy[u];
	lazy[u << 1 | 1] += lazy[u];
	
	lazy[u] = 0;
}
 
void add(int u, int l, int r, int L, int R, int val){ //区间加
	if(R < l || r < L) return ;
	if(L <= l && r <= R){
		tree[u].minn += val;
		tree[u].maxn += val;
		lazy[u] += val;
		return ;
	}
	int mid = (l + r) >> 1;
	push_down(u); //先下传
	add(u << 1, l, mid, L, R, val);
	add(u << 1 | 1, mid + 1, r, L, R, val);
	push_up(u); //再上传
}
int ask(int u, int l, int r){
	if(l == r) return l;
	int mid = (l + r) / 2;
	push_down(u); //记得干啥前都要懒标记下传
	if(tree[u << 1].minn == 0 && tree[u << 1].maxn == 0) return ask(u << 1 | 1, mid + 1, r); //左儿子全0，遍历右儿子
	return ask(u << 1, l, mid);
}
int ask_val(int u, int l, int r, int pos){
	if(l == r) return tree[u].minn;
	
	int mid = (l + r) / 2;
	push_down(u); //下传啊啊啊啊啊啊啊啊啊
	if(l <= pos && pos <= mid) return ask_val(u << 1, l, mid, pos); //由于单点查询，直接比较在左/右儿子中即可
	return ask_val(u << 1 | 1, mid + 1, r, pos);
}
 
void solve(){
	cin >> n;
	for(int i = 1; i <= 4 * n; i++){ //清空
		tree[i] = (Segment_Tree){0, 0};
		lazy[i] = 0;
	}
	for(int i = 1; i <= n; i++) cin >> a[i];
	cin >> q;
	
	int lst_choose = 0; //上一个最优点
	for(int rp = 1; rp <= q; rp++){
		cin >> Q[rp].l >> Q[rp].r >> Q[rp].val;
		
		add(1, 1, n, Q[rp].l, Q[rp].r, Q[rp].val); //区间加
		if(tree[1].minn == 0 && tree[1].maxn == 0) continue; //如果全0就不用比了
		
		int first_not_zero = ask(1, 1, n); //第一个不是 0 的位置
		
		if(ask_val(1, 1, n, first_not_zero) < 0){ //查询它的大小
			for(int j = lst_choose + 1; j <= rp; j++){ //清除区间加
				add(1, 1, n, Q[j].l, Q[j].r, -Q[j].val); 
			}
			lst_choose = rp; //更新
		}
	}
	for(int i = 1; i <= 4 * n; i++){ //先清空
		tree[i] = (Segment_Tree){0, 0};
		lazy[i] = 0;
	}
	for(int i = 1; i <= lst_choose; i++){ //加上
		add(1, 1, n, Q[i].l, Q[i].r, Q[i].val);
	}
	for(int i = 1; i <= n; i++){ //记得加上 a[i]
		cout << a[i] + ask_val(1, 1, n, i) << " ";
	}
	cout << endl;
}
signed main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int rp = 1; rp <= t; rp++) solve();
	return 0;
}
```
喜欢的话，点个赞吧！

---

## 作者：蒟蒻君HJT (赞：0)

你发现 $a_i$ 字典序最小等价于其差分数组字典序最小。归纳即可。

这样的好处是：一次区间加操作只影响了两个位置的差分值。

接下来只考虑差分数组。称第 $i$ 次操作**后**为第 $i$ 时刻。

考虑维护仅仅考虑前 $i$ 个位置的情况下，能使得前 $i$ 个位置字典序最小的所有时刻构成的集合 $S_i$。显然 $S_0=\{0,1,2,3,\cdots q\}$，$S_{i+1}\subset S_i$。

从 $S_{i-1}$ 推向 $S_i$。位置 $i$ 总共被操作了 $m_i$ 次，并且有相应的时刻。前缀和一下，得到进行完前若干次操作后这个位置的值。对这些值排序后，对于每个值，可以求出在哪些时刻区间，位置 $i$ 处于这个值。将这些区间与 $S_{i-1}$ 求交，非空说明这个值可以达到。贪心地找出最小的可以达到的值，将这些区间的并集与 $S_{i-1}$ 求交集即得到 $S_i$。

最后任意取出 $S_n$ 中的一个元素，模拟操作过程即可。

实现时用 ```std::set``` 维护 $S_i$。考虑到取交难以保证复杂度，不妨在求出第 $i$ 个位置能达到的最小值后，算出不合法的时刻区间，用 ```lower_bound()``` 剔除不合法的时刻。

[for reference only.](https://codeforces.com/contest/1887/submission/229257331)

---

