# Trader Problem

## 题目描述

Monocarp plays a computer game (yet again!). This game has a unique trading mechanics.

To trade with a character, Monocarp has to choose one of the items he possesses and trade it for some item the other character possesses. Each item has an integer price. If Monocarp's chosen item has price $ x $ , then he can trade it for any item (exactly one item) with price not greater than $ x+k $ .

Monocarp initially has $ n $ items, the price of the $ i $ -th item he has is $ a_i $ . The character Monocarp is trading with has $ m $ items, the price of the $ i $ -th item they have is $ b_i $ . Monocarp can trade with this character as many times as he wants (possibly even zero times), each time exchanging one of his items with one of the other character's items according to the aforementioned constraints. Note that if Monocarp gets some item during an exchange, he can trade it for another item (since now the item belongs to him), and vice versa: if Monocarp trades one of his items for another item, he can get his item back by trading something for it.

You have to answer $ q $ queries. Each query consists of one integer, which is the value of $ k $ , and asks you to calculate the maximum possible total cost of items Monocarp can have after some sequence of trades, assuming that he can trade an item of cost $ x $ for an item of cost not greater than $ x+k $ during each trade. Note that the queries are independent: the trades do not actually occur, Monocarp only wants to calculate the maximum total cost he can get.

## 样例 #1

### 输入

```
3 4 5
10 30 15
12 31 14 18
0 1 2 3 4```

### 输出

```
55
56
60
64
64```

# 题解

## 作者：Tyyyyyy (赞：4)

# CF1618G
#### 题意简述
- 你手上有 $n$ 个物品，第 $i$ 个物品价值 $a_i$。
- 商人手上有 $m$ 个物品，第 $i$ 个物品价值 $b_i$。
- 你能用一个价值为 $x$ 的物品换取一个价值不超过 $x+k$ 的物品。$k$ 是给定常数。
- $q$ 个询问，每次给定 $k$，问最后手上物品价值之和的最大值。
- 询问之间相互独立。
- $1 \leq n,m,q \leq 2 \times 10^5,1 \leq a_i,b_i,k \leq 10^9$。

#### 题目分析
考虑将所有物品按价值从小到大排序。显然，对于一个确定的 $k$，从某个物品开始能换的物品是包含该物品的一个区间。

可以使用并查集来维护这些区间。

具体来说，记录排序后相邻物品价值差为定值时物品的下标，则当存在 $val_i-val_{i-1}\leq k$ 时，需要将 $i$ 和 $i-1$ 合并，同时重新计算它们对答案的贡献。

我们离线询问，将询问按 $k$ 值从小到大排序，即可依次处理。这样，已经合并过的部分就无需再次合并。每个位置最多只会被合并一次，时间复杂度为 $O(n+m+q)$ 或者 $O((n+m)\operatorname{log}(n+m)+q)$（根据并查集的实现而定）。

Code：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
using namespace std;
int n,m,Q;
int fa[400010],sz[400010];
ll res,ans[200010],sum[400010];
pii q[200010],a[400010];
map<int,vector<int> >mp;
int find(int x)
{
	if(x!=fa[x])return fa[x]=find(fa[x]);
	return fa[x];
}
int main()
{
	scanf("%d%d%d",&n,&m,&Q);
	for(int i=1;i<=n+m;i++)scanf("%d",&a[i].first),a[i].second=i;
	sort(a+1,a+n+m+1);
	for(int i=1;i<=n+m;i++)
	{
		if(a[i].second<=n)res+=a[i].first;
		sz[i]=(a[i].second<=n);
		sum[i]=sum[i-1]+a[i].first,fa[i]=i;
		if(i>1)mp[a[i].first-a[i-1].first].push_back(i-1);
	}
	for(int i=1;i<=Q;i++)scanf("%d",&q[i].first),q[i].second=i;
	sort(q+1,q+Q+1);
	auto it=mp.begin();
	for(int i=1;i<=Q;i++)
	{
		if(q[i].first==q[i-1].first){ans[q[i].second]=res;continue;}
		while(it!=mp.end()&&it->first<=q[i].first)
		{
			for(auto k:it->second)
			{
				int fu=find(k),fv=find(k+1);
				res-=(sum[fv]-sum[fv-sz[fv]]+sum[fu]-sum[fu-sz[fu]]);
				sz[fv]+=sz[fu],fa[fu]=fv;
				res+=(sum[fv]-sum[fv-sz[fv]]);
			}
			it++;
		}
		ans[q[i].second]=res;
	}
	for(int i=1;i<=Q;i++)printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：DerrickLo (赞：2)

我们先将两个数组合并在一起排序，设排序后的数组为 $c$。

然后我们发现对于每个 $k$，能互相交换的物品都对应着合并后的数组中若干个互不相交的区间。那么对于每个区间，我们很明显会让最终手中的物品是这个区间中最大的那些。

所以如果 $k$ 固定，那么我们找到这些区间后贪心的取就是答案了。

对于这道题，我们可以把所有询问排序，接着不难发现这些区间是只会合并而不会分裂的，所以我们对于每个 $i$，二分出第 $i$ 个物品与第 $i+1$ 的物品合并在一起的时间，即找到最小的 $j$ 使得 $c_{i+1}-c_i\le k_j$。

那么每次询问我们只需要处理恰好在这次询问中合并的物品，这能用并查集很好的维护。每个并查集维护这个集合所对应的区间和这个集合所对应的区间内有多少个原先在手中的数即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,ans[200005],fa[400005],cnt[400005],sum[400005],anss,l[400005],r[400005];
struct nd{
	int x,id;
	friend bool operator<(const nd&a,const nd&b){
		return a.x<b.x;
	}
}a[400005],b[200005];
vector<int>ve[200005];
int find(int x){
	return(fa[x]==x)?x:fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n+m;i++){
		cin>>a[i].x,a[i].id=i;
		if(i<=n)anss+=a[i].x;
	}
	sort(a+1,a+n+m+1);
	for(int i=1;i<=n+m;i++)fa[i]=i,cnt[i]=a[i].id<=n,sum[i]=sum[i-1]+a[i].x,l[i]=r[i]=i;
	for(int i=1;i<=q;i++)cin>>b[i].x,b[i].id=i;
	sort(b+1,b+q+1);
	for(int i=1;i<n+m;i++){
		int xx=lower_bound(b+1,b+q+1,nd{a[i+1].x-a[i].x,0ll})-b;//二分出合并的时间
		ve[xx].emplace_back(i);
	}
	for(int i=1;i<=q;i++){
		for(int v:ve[i]){//恰好在i时刻合并的位置
			int x=find(v),y=find(v+1);
			anss-=sum[r[x]]-sum[r[x]-cnt[x]];
			anss-=sum[r[y]]-sum[r[y]-cnt[y]];//减去合并前的贡献
			fa[x]=y,l[y]=l[x],cnt[y]+=cnt[x];
			anss+=sum[r[y]]-sum[r[y]-cnt[y]];//加上合并后的贡献
		}
		ans[b[i].id]=anss;
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：AK_heaven (赞：1)

### [CF1618G Trader Problem](https://www.luogu.com.cn/problem/CF1618G)

很显然，并查集维护哪些数字可以互相到达，这个应该熟练并查集的人都可以想到，包括离线做询问保证了只合并，不分裂。

难点我认为有两个：

- 1. 如何维护一个集合里面前 $i$ 大的数字和如何计算，很巧妙，考虑到这个区间在排序后是连续的，所以直接前缀和就行了。
- 2. 如何去检查合并，难道真的要一个一个的跳，那么最坏情况是 $O(n^2)$ 的，肯定会 TLE，我们可以先二分计算出第一个合并的询问编号，然后到时候合并均摊下来就是 $O(1)$ 的。
 
算法流程：

- 1. 排序商品和询问。
- 2. 二分出商品 $i$ 和 $i+1$ 最早合并的询问编号，$ 1 \le i \le n+m-1$。
- 3. 处理每个询问，计算贡献变化，这里可以先减去合并前的变化，然后再加上合并后的贡献。
 
**The code**


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long

using namespace std;

const int N = 1e6 + 10;

int n, m, q, fa[N], cnt[N]; ll ans = 0, sum[N], Ans[N];

struct Nod {
	int v, id;
	bool operator < (const Nod &T) const {
		return v < T.v;
	}
}a[N];

struct Node {
	int id, k;
	bool operator < (const Node&T) const {
		return k < T.k;
	}
}Q[N];

vector<int> vec[N];

int find(int x) {
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]); 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);  cout.tie(0);
	cin >> n >> m >> q;
	L(i, 1, n+m) cin >> a[i].v, a[i].id = i, ans += (i <= n ? a[i].v : 0);
	L(i, 1, q) cin >> Q[i].k, Q[i].id = i;
	sort(a+1, a+n+m+1);
	sort(Q+1, Q+q+1);
	L(i, 1, n+m) sum[i] = sum[i-1] + a[i].v, cnt[i] = (a[i].id <= n);
	n += m;
	L(i, 1, n-1) {
		int l = 0, r = q, p = q+1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(Q[mid].k >= a[i+1].v - a[i].v) r = mid-1, p = mid;
			else l = mid+1;
		}
		vec[p].push_back(i);
	}
	L(i, 1, n) fa[i] = i;
	L(i, 0, q) {
		for(int x : vec[i]) {
			int y = x + 1;
			x = find(x); y = find(y);
			ans -= sum[x] - sum[x - cnt[x]];
			ans -= sum[y] - sum[y - cnt[y]];
			fa[x] = y; cnt[y] += cnt[x];
			ans += sum[y] - sum[y - cnt[y]];
		}
		Ans[Q[i].id] = ans;
	}
	L(i, 1, q) cout << Ans[i] << '\n';
	return 0;
}



```

---

## 作者：wangzhiyuan123 (赞：1)

写出来感觉和[csp-j2021 T4](https://www.luogu.com.cn/blog/511303/solution-p7912)差不多。

具体实现方法：将两个数组放在一起排序后求前缀和，维护一个链表，链表除了记录前一块和后一块之外，还要统计当前块的头和尾。用堆维护两个块之间的距离的集合，对问题离线。   

设当前块有 $c$ 个原来是 $a$ 数组里的数字，块的值为当前块最大的 $c$ 个数的和。  

当前查询的值大于两个块的距离时，统计答案的变量减去当前两个块的值，合并这两个块，再加上这两个块的值。

具体实现见代码注释。   
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,al,q,ans;
int as[400005];
int qzhv[800005],qzhc[800005];
struct dt{
	int val,c;
}d[800005];
struct qst{//存储问题以离线 
	int rk,qv;
}qs[400005];
struct blk{//链表 
	int lst,nxt;
	int frm,to;
}k[800005];
dt make_dt(int v,int f){
	dt xf;
	xf.val=v;xf.c=f;
	return xf;
}
bool cmp(dt a1,dt a2){return a1.val<a2.val;}
bool qcmp(qst a1,qst a2){return a1.qv<a2.qv;}
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;//用以统计相邻块的间隙 
#define gtblock(x) (qzhv[k[x].frm]-qzhv[max(0ll,k[x].frm-qzhc[k[x].frm]+qzhc[k[x].to-1])])//求当前块的最大值 
main(){
	scanf("%lld%lld%lld",&n,&m,&q);
	for(int i=1,u;i<=n;i++){
		scanf("%lld",&u);
		d[i]=make_dt(u,1);
	}
	for(int i=1,u;i<=m;i++){
		scanf("%lld",&u);
		d[i+n]=make_dt(u,0);
	}
	al=n+m;
	sort(d+1,d+1+al,cmp);
	for(int i=1;i<=al;i++){//初始每个块只包含一个元素 
		k[i].frm=k[i].to=i;
		qzhc[i]=qzhc[i-1]+d[i].c;
		qzhv[i]=qzhv[i-1]+d[i].val;//有了前缀和以及每个块统计的头和尾后，可以快速求出块里原来a数组的数的个数和最大的一段 
		ans+=d[i].c*d[i].val;
	}
	for(int i=1;i<al;i++){
		pq.push(make_pair(d[i+1].val-d[i].val,i));//把这个间隙丢进堆里 
		k[i].nxt=i%al+1;//连接链表 
		k[i%al+1].lst=i;
	}
	for(int i=1;i<=q;i++) scanf("%lld",&qs[i].qv),qs[i].rk=i;
	sort(qs+1,qs+1+q,qcmp);
	for(int i=1;i<=q;i++){
		while(!pq.empty()&&pq.top().first<=qs[i].qv){
			int x=pq.top().second;
			pq.pop();
			ans-=gtblock(x);
			ans-=gtblock(k[x].nxt);
			k[k[x].lst].nxt=k[x].nxt;
			k[k[x].nxt].lst=k[x].lst;
			k[k[x].nxt].to=k[x].to;
			ans+=gtblock(k[x].nxt);
		}
		as[qs[i].rk]=ans;
	}
	for(int i=1;i<=q;i++) printf("%lld\n",as[i]);
}
```


---

## 作者：Lvlinxi2010 (赞：0)

考场上想到如果可以应该一直往上换是最优的然后就没有时间写了。

我们先将这 $n+m$ 个物品排序，然后发现这个往上换的操作可以用并查集维护可以换到的最高价值（很好理解吧当两个相邻的差小于给定的 $k$，那就是联通的也就是可以交换的），

我们很容易想到把询问离线下来然后按照 $k$ 排序，这样这就是一个只合并不分裂的并查集（因为 $k$ 小的时候可以换到的物品 $k$ 变大的时候也一定可以换到），并且合并的并查集一定是一段区间，就很好维护了。

然后我们只需要维护两个相邻的数第一次合并的时间然后每次询问前合并即可。

附上代码：


```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
#define PII pair<ll,ll>
using namespace std;
const ll MAXN = 4e5 + 10;
ll n,m,Q;
ll now=0;
ll ans[MAXN];
ll fa[MAXN],siz[MAXN],s[MAXN];
PII a[MAXN],q[MAXN];
vector<ll>E[MAXN];
ll find(ll x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&Q);
	FL(i,1,n+m) scanf("%lld",&a[i].first),a[i].second=i;
	FL(i,1,n) now+=a[i].first;
	sort(a+1,a+n+m+1);
	FL(i,1,n+m) fa[i]=i,s[i]=s[i-1]+a[i].first,siz[i]=(a[i].second<=n);
	FL(i,1,Q) scanf("%lld",&q[i].first),q[i].second=i;
	sort(q+1,q+Q+1);
	FL(i,1,n+m-1){
		ll pos=lower_bound(q+1,q+Q+1,(PII){a[i+1].first-a[i].first,0})-q;
		E[pos].push_back(i);
	}
	FL(i,1,Q){
		for(ll j:E[i]){
			ll x=find(j),y=find(j+1);
			now-=(s[x]-s[x-siz[x]]);
			now-=(s[y]-s[y-siz[y]]);
			fa[x]=y,siz[y]+=siz[x];
			now+=(s[y]-s[y-siz[y]]);
		}
		ans[q[i].second]=now;
	}
	FL(i,1,Q) printf("%lld\n",ans[i]);
}
```

---

## 作者：longlinyu7 (赞：0)

## [$ CF1618G-Trader Problem$](https://www.luogu.com.cn/problem/CF1618G)

考虑到性质，可以把 $a$ 数组和 $b$ 数组合并到 $c$ 中，然后从小到大排序，再把询问离线，也是按照 $k$ 的大小从小到大进行，然后每次按照 $k$ 的大小把 $c_i -c_{i-1} \le k$ 的合并，形成若干个联通块，设第 $i$ 个联通块中有 $cnt_i$ 个数原先是 $a$ 中的，那该询问的答案加上这个联通块的最大的 $cnt_i$ 个数字即可。

如何这些维护联通块呢，以及前 $cnt_i$ 大的数的和，暴力想法可以每次询问都搜一遍，考虑使用并查集维护这些联通块，显然，还需要顺带维护每个联通块的 $cnt$，即需要使用带权并查集来维护。具体细节看代码。

重新梳理下步骤：

- 先把 $a$ 和 $b$ 合并再排序，询问离线，再维护一个差分数组，算出相邻的数的差值，再从小到大排序。总共排序三遍。
- 考虑如何维护带权并查集，需要知道每个联通块的左右端点，以及 $cnt$，然后合并的时候把信息合并到父节点中。然后这题就很简单了。
## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
const int N=1e6+10;
const int inf=1e15;
int n,m,Q,x;
int a[N],b[N];
struct node{
    int val,id;
    friend bool operator<(node a,node b){
        return a.val<b.val;
    }
}c[N];
struct edge{
    int k,id;
    friend bool operator<(edge a,edge b){
        return a.k<b.k;
    }
}q[N];
struct E{
    int val,id;
    friend bool operator<(E a,E b){
        return a.val<b.val;
    }
}d[N];

int tot,ans[N];
int f[N],s[N],cnt[N],L[N],R[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void merge(int x,int y){ f[find(x)]=find(y);}
ll S;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>Q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        c[++tot]=(node){a[i],0};
        S+=a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
        c[++tot]=(node){b[i],1};
    }
    sort(c+1,c+1+tot);
    for(int i=2;i<=tot;i++){
        d[i].val=c[i].val-c[i-1].val;  //? 每条边的差值排序
        d[i].id=i;
    }
    sort(d+2,d+1+tot);
    for(int i=1;i<=tot;i++){
        s[i]=s[i-1]+c[i].val; //前缀和
        if(c[i].id==0)cnt[i]=1; //? 预处理这个有几个
        L[i]=R[i]=f[i]=i;  //? 预处理并查集
    }

    for(int i=1;i<=Q;i++){  //!离线
        cin>>x;
        q[i]=(edge){x,i};
    }
    sort(q+1,q+1+Q);
    int l=2;
    for(int i=1;i<=Q;i++){

        for(;d[l].val<=q[i].k&&l<=n+m ;l++){
            int x=find(d[l].id),y=find(d[l].id-1);
            //? 删去两个区间合并前 各自的贡献
            S-= s[R[x]] - s[R[x]-cnt[x]];
            S-= s[R[y]] - s[R[y]-cnt[y]];
            // cout<<x<<","<<L[x]<<","<<R[x]<<","<<cnt[x] <<"\n";
            // cout<<y<<","<<L[y]<<","<<R[y]<<","<<cnt[y] <<"\n";
            f[x]=y;
            cnt[y]+=cnt[x]; L[y]=min(L[x],L[y]);R[y]=max(R[x],R[y]);
            S+=s[R[y]]-s[R[y]-cnt[y]]; //加上新的贡献。
            // cout<<y<<","<<L[y]<<","<<R[y]<<","<<cnt[y] <<"\n";
            // cout<<"\n";

        }
        ans[q[i].id]=S;
    }
    for(int i=1;i<=Q;i++){
        cout<<ans[i]<<"\n";
    }
    return 0;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

### 题意

给定一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$，有 $q$ 组询问。对于每个询问：

给定一个 $k$，可进行若干次如下操作：$\forall i\in a$ 和 $\forall j\in b$ 满足 $\lvert a_i-b_j\rvert\le k$，交换 $a_i$ 和 $b_j$。求 $\max\sum_{i=1}^na_i$。

对于 $100\%$ 的数据，$1\le n,m,q\le2\times10^5$。

### 解析

首先肯定是要离线的，将 $k$ 存下来然后升序排序。对于当前的 $k$，我们可以将绝对值之差小于 $k$ 的数合并成一组。

> 例如当 $k=3$ 时，$a=[1,7,13,15]$，$b=[4,18,20]$：
> 
> 可以分成 $[1,4,7]$ 和 $[13,15,18,20]$ 两组，由于每组中的任意两个数都是可交换的，此时得到的答案为 $4+7+18+20=49$。

可见答案就是**每组中所有的数最大的 $\boldsymbol n$ 个**。

所以我们可以通过并查集维护每组中所有的数最大的 $n$ 个，合并的时候更新答案。

具体合并方法，**启发式合并**！

对于每个组，维护两个 multiset，$\textit{sa}$ 代表最大的 $a$ 个数（如上文所示），$\textit{sb}$ 代表剩下的数，每次将总数少的那个组转到总数多的组：

```cpp
void combine(int u, int v) {
	u = find(u), v = find(v);
	if (sa[u].size() + sb[u].size() < sa[v].size() + sb[v].size()) swap(u, v);
	for (auto x : sa[v]) sa[u].insert(x);
	for (auto x : sb[v]) sb[u].insert(x);
	while (!sa[u].empty() && !sb[u].empty() && *sa[u].begin() < *sb[u].rbegin()) {
		int p = *sa[u].begin(), q = *sb[u].rbegin();
		sum += q - p;
		sa[u].erase(sa[u].find(p));
		sb[u].erase(sb[u].find(q));
		sa[u].insert(q);
		sb[u].insert(p);
	}
	f[v] = u;
}
```

这就是启发式合并，看似暴力实则很快的算法。

> 复杂度分析：
> 
> 先分析两个 for 的时间复杂度，考虑具体到每个数被移动了多少次。一开始是一个数，移动后所在组的大小为 $2$，如果再次移动大小为 $4$，然后是 $8,16,\dots$
> 
> 可见每个数最多被来回移动 $\log n$ 次，所以总的时间复杂度为 $O(n\log^2n)$。
> 
> while 的时间复杂度等同于 for。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef tuple<int, int, int> tiii;
constexpr int MAXN = 2e5 + 5;
int n, m, q, a[MAXN], b[MAXN], sum, ans[MAXN];
int f[MAXN << 1];
vector<pair<int, int>> g;
multiset<int> sa[MAXN << 1], sb[MAXN << 1];
vector<tiii> t;

int find(int x) {
	if (f[x] != x) f[x] = find(f[x]);
	return f[x];
}

void combine(int u, int v) {
	u = find(u), v = find(v);
	if (sa[u].size() + sb[u].size() < sa[v].size() + sb[v].size()) swap(u, v);
	for (auto x : sa[v]) sa[u].insert(x);
	for (auto x : sb[v]) sb[u].insert(x);
	while (!sa[u].empty() && !sb[u].empty() && *sa[u].begin() < *sb[u].rbegin()) {
		int p = *sa[u].begin(), q = *sb[u].rbegin();
		sum += q - p;
		sa[u].erase(sa[u].find(p));
		sb[u].erase(sb[u].find(q));
		sa[u].insert(q);
		sb[u].insert(p);
	}
	f[v] = u;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	iota(f + 1, f + (MAXN << 1) + 1, 1);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		g.push_back(make_pair(a[i], 1));
		sum += a[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
		g.push_back(make_pair(b[i], 0));
	}
	sort(g.begin(), g.end());
	for (int i = 0; i < n + m; i++)
		if (g[i].second) sa[i].insert(g[i].first);
		else sb[i].insert(g[i].first);
	for (int i = 0; i < n + m; i++)
		t.push_back(make_tuple(g[i + 1].first - g[i].first, 0, i));
	for (int i = 1; i <= q; i++) {
		int k;
		cin >> k;
		t.push_back(make_tuple(k, 1, i));
	}
	sort(t.begin(), t.end(), [](tiii a, tiii b) {
		if (get<0>(a) != get<0>(b)) return get<0>(a) < get<0>(b);
		return get<1>(a) < get<1>(b);
	});
	for (auto x : t)
		if (get<1>(x)) ans[get<2>(x)] = sum;
		else combine(get<2>(x), get<2>(x) + 1);
	for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
	
	return 0;
}
```

---

## 作者：DengStar (赞：0)

# CF1618G Trader Problem 题解

题目链接：[CF](codeforces.com/contest/1618/problem/G)|[洛谷](www.luogu.com.cn/problem/CF1618G)

提供一个 $O(n \log n)$ 预处理，$O(\log n)$ 查询的做法。

## 分析1

我们不妨把 $a$ 和 $b$ 合并为一个序列，称合并后的序列为 $c$，并将其不降序排序。把玩样例后不难发现：对于一个物品序列 $c_1, c_2, \cdots, c_l$，满足 $\forall i < l, c_{i+1} - c_i \le k$（即任意两个相邻的物品都可以交换），要使最后的总价值最大，最优的方法显然是把初始物品一直往后换。如果在这个序列中我们一开始有 $cnt$ 个物品，那么交换完之后我们的总价值就是 $\sum_{i=l-cnt+1}^{l} c_i$，即最后 $cnt$ 个物品的价值和。

## 分析2

上面的分析中，我们假设对于某个特定的 $k$，序列满足任意两个相邻的物品可以交换。但如果序列不满足这个性质呢？不难想到，可以把序列断开：对于所有满足 $c_{i+1} - c_i > k$ 的 $i$ （也就是说第 $i$ 个物品不能与第 $i+1$ 个物品交换），我们就让 $i$ 和 $i+1$ 分别属于两个链（子序列）。这样对于每个条链，都满足它任意两个相邻的物品可以交换。把所有链的答案加起来就是总答案。于是，对于每次询问，我们都可以 $O(n)$ 扫一遍解决。

单次询问 $O(n)$ 的代码如下：

```cpp
// mark[i]: 第i个物品是否是一开始手里拥有的
// cnt: 当前这条链中有多少个物品时一开始就有的
void solve(int k)
{
	int pos = 2, lst = 1, cnt = mark[1];
	ll ans = 0;
	for(; pos <= tot; pos++)
	{
		if(c[pos] - c[pos-1] > k) // 如果这两个相邻的物品不能交换，就断开，统计上一段的贡献
		{
			ans += sum[pos - 1] - sum[pos - cnt - 1];
			lst = pos, cnt = 0;
		}
		cnt += mark[pos];
	}
	cout << ans << endl;
}
```



## 分析3

上面我们一直默认 $k$ 为定值，如果 $k$ 不确定，有没有什么办法能一次处理好所有可能的 $k$ 对应的答案呢？

首先明确一个问题：虽然 $k$ 有很多种取值（$0 \le k \le 10^9$），但并不是每个不同的 $k$ 都对应不同的答案。可以这样理解：假设现在我们已经对于某个特定的 $k$ 把原序列断成了几条链，然后让 $k$ 不断增大，只有当 $k$ 可以“跨越”某两条链之间的间隔时，这两条链才会合并到一起，同时答案才可能发生改变。因此，实际上我们并不需要对所有的 $k$ 都算一个答案。设所有的**相邻物品价值差**的集合为 $dif$，我们只需要让 $k$ 取遍 $dif$ 中的每个值即可。将 $dif$ 排序，设 $k = dif_i$ 时的答案为 $ans_i$。对于每次询问的 $k$，二分找出一个 $i$ 使得 $dif_i \le k < dif_{i+1}$ ，答案便为 $ans_i$。

接下来的做法便不难想到了。一开始令 $k = 0$，这时每个物品都只能和**与它价值相同的物品**构成链，因为任意两个价值不同的物品都不能交换。当 $k \in [0, dif_1)$ 时，总不会有新的可以交换的物品对产生。只有当 $k = dif_1$ 时，才可以进行合并。同理，我们继续让 $k$ 取遍所有的 $dif_i$，每次都合并所有可以合并的链，同时统计答案。

可以使用并查集维护链。同时维护每条链包含的**初始物品数**。合并时，新链的初始物品数即为原来两条链的初始物品数之和。

## 时间复杂度

（因为 $n$ 和 $m$ 数量级相同，下面把所有的 $n + m$ 都当作 $n$。）

因为总共只会合并 $n-1$ 次，所以统计答案的时间复杂度为 $O(n)$。而先前对 $c$ 排序的时间复杂度为 $O(n \log n)$，单次查询的时间复杂度为 $O(\log n)$，所以总的时间复杂度为 $O(n \log n)$。

## 代码

```cpp
// CF1618G Trader Problem
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
constexpr int MAXN = 2e5 + 10;
int n, m, q, p, a[MAXN], b[MAXN];
int tot, c[MAXN << 1], dif[MAXN << 1], cnt[MAXN << 1];
// cnt[i]: 以i结尾的链中的原始商品的数量 
ll sum[MAXN << 1], ans[MAXN << 1];
bool mark[MAXN << 1];
struct Node
{
	ll dif;
	int pos; // c[pos+1] - c[pos] = dif
	Node(int dif, int pos): dif(dif), pos(pos) {}
	bool operator > (const Node &rhs) const
	{
		return dif > rhs.dif;
	}
};
priority_queue<Node, vector<Node>, greater<Node>> que;

struct DSU
{
	int fa[MAXN << 1];
	void init()
	{
		for(int i = 1; i <= tot; i++)
		{
			fa[i] = i;
			cnt[i] = mark[i];
		}
	}
	int getfa(int u)
	{
		return fa[u] == u ? u : fa[u] = getfa(fa[u]);
	}
	void merge(int x, int y) // x < y
	{
		int fx = getfa(x), fy = getfa(y);
		fa[fx] = fy;
		cnt[fy] += cnt[fx], cnt[fx] = 0; 
	}
}dsu;

void merge() // 直接 sort 应该也行
{
	int i = 1, j = 1, k = 1;
	while(i <= n && j <= m)
	{
		if(a[i] <= b[j]) mark[k] = true, c[k++] = a[i++];
		else c[k++] = b[j++];
	}
	while(i <= n) mark[k] = true, c[k++] = a[i++];
	while(j <= m) c[k++] = b[j++];
	for(int i = 1; i <= tot; i++) sum[i] = sum[i-1] + c[i];
	for(int i = 1; i < tot; i++)
	{
		dif[i] = c[i+1] - c[i];
		que.push(Node(dif[i], i));
	}
	sort(dif + 1, dif + tot);
	dif[0] = unique(dif + 1, dif + tot) - dif - 1;
}

inline int getrk(int x)
{
	return lower_bound(dif + 1, dif + dif[0] + 1, x) - dif;
}

void solve()
{
	merge();
	dsu.init();
	for(int i = 1; i <= n; i++) ans[0] += a[i];
	while(!que.empty()) // 这里用优先队列维护 dif，实际上直接把 dif 排序再枚举应该也可以 
	{
		Node u = que.top();
		que.pop();
		int nowdif = u.dif, rk = getrk(nowdif);
		int ori = dsu.getfa(u.pos), tail = dsu.getfa(u.pos + 1); 
		if(!ans[rk]) ans[rk] = ans[rk - 1];
		// 因为没有对 dif 去重，所以第一次遇到 dif 时要先取用上一个 dif 的 ans 
		ll d1 = (sum[ori] - sum[ori - cnt[ori]]) + (sum[tail] - sum[tail - cnt[tail]]);
		dsu.merge(u.pos, u.pos + 1);
		ll d2 = sum[tail] - sum[tail - cnt[tail]];
		ans[rk] = ans[rk] - d1 + d2;
		// 去除原先两条链的贡献，加上新链的贡献 
	}
}

signed main()
{
	cin >> n >> m >> q;
	tot = n + m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];
	sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
	solve();
	while(q--)
	{
		cin >> p;
		int rk = upper_bound(dif + 1, dif + dif[0] + 1, p) - dif - 1;
		cout << ans[rk] << endl;
	}
	return 0;
}
```

---

## 作者：subcrip (赞：0)

也想了用并查集，但是觉得还是有点太麻烦了。

把两个数组拍到一起排序，然后把询问也离线下来排序，然后根据数组中元素之间的距离可划分成多个块。维护一个数组 `O` 表示块的左端点对应的右端点位置，以及右端点对应的左端点位置。按照询问的大小去合并元素之间距离足够小的块就行了。合并过程的计算使用前缀和，也就是块的答案等于块中最大的 $m$ 个元素，其中 $m$ 表示块中来自 $a$ 数组的元素个数。时间复杂度是 $O((n+m)\log(n+m)+q\log q)$。

## Code

```cpp
void solve() {
    read(int, n, m, q);
    vector<pii> a;
    for (int i = 0; i < n; ++i) {
        read(int, x);
        a.emplace_back(x, 0);
    }
    for (int i = 0; i < m; ++i) {
        read(int, x);
        a.emplace_back(x, 1);
    }
    n += m;
    sort(a.begin(), a.end());
    vector<pii> query;
    for (int i = 0;i < q; ++i) {
        read(int, x);
        query.emplace_back(x, i);
    }
    sort(query.begin(), query.end());
    vector<ll> res(q);
    vector<int> cnt_ps(n + 1);
    vector<ll> ps(n + 1);
    for (int i = 1; i <= n; ++i) {
        ps[i] = ps[i - 1] + a[i - 1].first;
        cnt_ps[i] = cnt_ps[i - 1] + not a[i - 1].second;
    }
    vector<pli> sep;
    for (int i = 0; i < n - 1; ++i) {
        sep.emplace_back(a[i + 1].first - a[i].first, i);
    }
    sort(sep.begin(), sep.end());
    int ptr = 0;
    vector<int> O(n);
    ll curr = 0;
    auto calc_range = [&] (int l, int r) -> ll {
        return ps[r + 1] - ps[r + 1 - (cnt_ps[r + 1] - cnt_ps[l])];
    };
    for (int i = 0; i < n; ++i) {
        curr += a[i].first * not a[i].second;
        O[i] = i;
    }
    for (auto&& [x, idx] : query) {
        while (ptr < sep.size() and sep[ptr].first <= x) {
            int sep_left = sep[ptr++].second;
            // merge two branches
            int new_left = O[sep_left], new_right = O[sep_left + 1];
            curr -= calc_range(new_left, sep_left) + calc_range(sep_left + 1, new_right);
            curr += calc_range(new_left, new_right);
            O[new_left] = new_right, O[new_right] = new_left;
        }
        res[idx] = curr;
    }
    putvec_eol(res);
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1618G Trader Problem](https://www.luogu.com.cn/problem/CF1618G)

并查集不错，线段树也不差。

### 思路

为了使最终价值尽可能的大，我们换物品一定会往大的换。并且随着常数 $k$ 的增大，可换的物品种类数越多，答案也会越大。此时我们把询问离线，按 $k$ 从小到大计算答案。

由于所有出现的物品都可能作为答案，我们把 $n+m$ 的物品合到一起，对一开始拥有的物品做标记。为了方便从小到大换，我们按物品价值从小到大排序。如果强制加上一个询问 $k=0$，那么此时的答案就是所选物品价值之和。我们新设一个数组 $c$ 表示合并后的物品序列，$c_i$ 代表其价值。考虑如果第 $i$ 个当前选中的物品要往后换，那么至少要满足 $c_i+k\ge c_{i+1}$。本着能换就换的原则，我们只关心它取到等号的 $k$ 值。也就是在 $k=c_{i+1}-c_i$ 时，第 $i$ 个物品可以和第 $i+1$ 个物品交换。注意到在它们俩可以交换的时候，第 $i+1$ 个物品可能与它之后、第 $i$ 个物品可能与它之前若干个物品已经可以交换。这两个区间如果有一定数量可以选择的物品数目，那么肯定会尽可能地靠右堆。

于是在 $i$ 和 $i+1$ 左右两个区间打通的时候，我们统计一下这两个区间的可选物品总数，把它们标记到合并后区间的最右侧。这个过程有如下两种做法：

1. 线段树：节点维护区间可选物品个数、已选物品价值总和，查询区间可选物品个数。由于合并后标记存在于靠右的一个区间，所以还要区间赋值操作。但是不好计算合并时节点所处区间，所以还要记录所有区间左端点编号。

2. 并查集：一开始每一个节点属于自己的集合，合并时右端点向左端点区间连边，父亲节点作为右端点统计该区间物品个数，然后前缀和一下就可以快速取出区间若干最大值。

时间复杂度线段树 $O((n+m)\log(n+m)+q\log q)$，带大常数；并查集带小常数，并且可以做到 $O(n+m+q\log q)$。

这里只有线段树，并查集看其它题解吧。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
using std::cin;using std::cout;
constexpr int N=200005,M=400005,K=1600005;
int n,m,q,now=1;
long long ans[N];//不开long long见祖宗
struct A{int k,id;}c[N],d[M];
struct B{int v;bool vis;}a[M];
std::map<int,bool>p;
struct SegmentTree{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	long long sum[K],b[K];//sum计算区间所有物品价值和，b计算可选价值和
	int tot[K],tag[K];//tot计算选择物品个数，tag为选择标记，线段树4倍空间
	inline void pushup(int p){
		sum[p]=sum[ls]+sum[rs];
		b[p]=b[ls]+b[rs];
		tot[p]=tot[ls]+tot[rs];
	}
	inline void pushdown(int p,int l,int r){
		if(tag[p]!=-1){
			b[ls]=sum[ls]*tag[p];b[rs]=sum[rs]*tag[p];
			tot[ls]=(mid-l+1)*tag[p];tot[rs]=(r-mid)*tag[p];
			tag[ls]=tag[rs]=tag[p];
			tag[p]=-1;
		}
	}
	inline void build(int l,int r,int p){
		tag[p]=-1;
		if(l==r){tot[p]=a[l].vis;b[p]=a[l].vis*a[l].v;sum[p]=a[l].v;return ;}
		build(l,mid,ls);build(mid+1,r,rs);
		pushup(p);
	}
	inline void update(int l,int r,int x,int y,int p,int k){//区间更新标记
		if(x>y) return ;
		if(x<=l&&r<=y){b[p]=sum[p]*k;tot[p]=(r-l+1)*k;tag[p]=k;return ;}
		pushdown(p,l,r);
		if(x<=mid) update(l,mid,x,y,ls,k);
		if(mid<y) update(mid+1,r,x,y,rs,k);
		pushup(p);
	}
	inline int query(int l,int r,int x,int y,int p){//查询选择物品个数
		if(x<=l&&r<=y) return tot[p];
		pushdown(p,l,r);int ans=0;
		if(x<=mid) ans=query(l,mid,x,y,ls);
		if(mid<y) ans+=query(mid+1,r,x,y,rs);
		return ans;
	}
}seg;
signed main(){
	freopen("trade.in","r",stdin);
	freopen("trade.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=n;++i){cin>>a[i].v;a[i].vis=1;}
	for(int i=1;i<=m;++i){cin>>a[n+i].v;a[n+i].vis=0;}
	for(int i=1;i<=q;++i){cin>>c[i].k;c[i].id=i;}
	std::sort(c+1,c+q+1,[](A a,A b){return a.k<b.k;});
	std::sort(a+1,a+n+m+1,[](B a,B b){return a.v<b.v;});//离线、合并
	for(int i=0;i<=n+m+1;++i) p[i]=1;//记录区间左端点
	for(int i=1;i<n+m;++i) d[i]=A{a[i+1].v-a[i].v,i};
	std::sort(d+1,d+n+m,[](A a,A b){return a.k<b.k;});
	seg.build(1,n+m,1);
	for(int i=1;i<=q;++i){
		for(;now<n+m&&d[now].k<=c[i].k;++now){
			auto l2=p.upper_bound(d[now].id),l1=prev(l2),l3=next(l2);
			int a1=l1->first,a2=l2->first,a3=l3->first;//查询合并左右区间
			int tot=seg.query(1,n+m,a1,a3-1,1);
			p.erase(l2);//合并
			seg.update(1,n+m,a1,a3-tot-1,1,0);
			seg.update(1,n+m,a3-tot,a3-1,1,1);//更新
		}
		ans[c[i].id]=seg.b[1];//此时所有已选物品价值总和即为答案
	}
	for(int i=1;i<=q;++i) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Forg1weN (赞：0)

# [CF1618G Trader Problem](https://www.luogu.com.cn/problem/CF1618G)

第一步转换：将 $x$ 与 $x+k$ 价值交换的操作同时考虑执行多次，即假设非严格递增序列 $x_1,x_2,x_3$ 相邻两项可以互相交换，若最后只能持有 $1$ 个，则无论初始持有哪个都可以得到最大的 $x_3$，拓展到多个，不难发现这是一个块取合法的前 $k$ 大。

于是将操作离线，从小到大合并块，维护每个块的左右端点以及左右邻居，这里用每个块的左端点代表它，用 multiset 来维护相邻两个块之间的差值，每次新增贡献为合并后的新块能取得的前 $k_1+k_2$ 大的数字之和前去原先两块各自前 $k1,k2$ 大的数字之和，不难用前缀和维护。

时间复杂度 $O(n\log n)。$
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn=5e5+10;
LL n,m,q;
LL pt[maxn],sum[maxn],vis[maxn];

struct sub { LL l,r,sum,m,v; }s[maxn];
bool cmp(sub a,sub b) { return a.v<b.v; }
struct Qry { LL a,id; }Q[maxn];
bool cmp2(Qry a,Qry b) { return a.a<b.a; }
struct srt { 
	LL p,l,r; 
	bool operator < (const srt &s) const {
		return p<s.p;
	}
};
multiset<srt>st;
int main() {
	scanf("%lld%lld%lld",&n,&m,&q);
	for(LL i=1;i<=n;i++)scanf("%lld",&s[i].v),s[i].m=1;
	for(LL i=n+1;i<=n+m;i++)scanf("%lld",&s[i].v),s[i].m=0;
	sort(s+1,s+1+n+m,cmp);
	for(LL i=1;i<=q;i++)scanf("%lld",&Q[i].a),Q[i].id=i;
	sort(Q+1,Q+1+q,cmp2);
	n=n+m;
	for(LL i=0;i<=n+1;i++)s[i].l=i-1,s[i].r=i+1;
	for(LL i=1;i<=n;i++)sum[i]=sum[i-1]+s[i].v;
	LL ans=0;
	for(LL i=1;i<=n;i++)ans+=s[i].v*s[i].m,s[i].sum=s[i].v*s[i].m;
	for(int i=1;i<n;i++)
		st.insert({s[i+1].v-s[i].v,i,i+1});
	for(LL i=1;i<=q;i++) {
		LL k=Q[i].a;
		while(!st.empty()&&st.begin()->p<=k) {
			int now=st.begin()->l,nxt=st.begin()->r;
			st.erase(st.begin());
			if(vis[now])continue;
			ans-=s[now].sum+s[nxt].sum;
			s[now].m+=s[nxt].m;
			LL R=s[nxt].r-1;
			s[now].sum=sum[R]-sum[R-s[now].m];
			ans+=s[now].sum;
			s[now].r=s[nxt].r;
			vis[nxt]=1;
			nxt=s[now].r;
			if(nxt!=n+1)st.insert({s[nxt].v-s[nxt-1].v,now,nxt});
		}
		pt[Q[i].id]=ans;
	}
	for(LL i=1;i<=q;i++)printf("%lld\n",pt[i]);
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [ CF1618G Trader Problem](https://www.luogu.com.cn/problem/CF1618G)

首先考虑将所有物品从小到大排序。可以发现，每次交易实质上是将排序后的数组相邻的两部分合并起来。例如你手上有 $13,15$，商人手上有 $10,16$，排序后为 $10,13,15,16$。当 $k=1$ 的时候，我们将 $15,16$ 合并。当 $k=2$ 时我们将 $13,15$ 合并。当 $k=3$ 时，我们将 $10,13$ 合并。自此，所有的数都合并到了一起。

那么怎么计算答案？根据题意，我们用手上的一个商品兑换了商人手上的一个商品后，如果可行且更优，我们可以用手上的另外一个商品去换回之前的商品。回到之前的合并操作，我们发现，每一段对答案的贡献都是这一段内前 $x$ 大的数的和，其中 $x$ 表示这一段中一开始属于自己的商品数量。

考虑使用并查集维护，以每一段最右边（即最大的数的位置）作为这一段的代表。预处理排序后序列的前缀和，并记录每一段中一开始属于自己的商品的数量。答案初始为手上的每一件商品的价值和。合并时先减去两段的贡献，然后合并，再加上新段的贡献。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010,M=400010;
typedef pair<int,int> pii;
int n,m,Q;
pii a[M],q[N];
int fa[M],size[M],sum[M],ans[N];
map<int,vector<int>> mp; 
int get(int x)
{
    return x==fa[x]?x:fa[x]=get(fa[x]);
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
    scanf("%lld%lld%lld",&n,&m,&Q);
    for (int i=1;i<=n+m;++i) scanf("%lld",&a[i].first),a[i].second=i;
    sort(a+1,a+n+m+1);
    int res=0;
    for (int i=1;i<=n+m;++i)
    {
        if (i>1) mp[a[i].first-a[i-1].first].push_back(i-1);
        sum[i]=sum[i-1]+a[i].first;
        size[i]=(a[i].second<=n);
        fa[i]=i;
        if (a[i].second<=n) res+=a[i].first;
    }
    for (int i=1;i<=Q;++i) scanf("%lld",&q[i].first),q[i].second=i;
    sort(q+1,q+Q+1);
    auto it=mp.begin();
    for (int i=1;i<=Q;++i)
    {
        if (i>1&&q[i].first==q[i-1].first)
        {
            ans[q[i].second]=ans[q[i-1].second];
            continue;
        }
        while (it!=mp.end()&&it->first<=q[i].first)
        {
            for (auto j:it->second)
            {
                int fu=get(j),fv=get(j+1);
                if (fu==fv) continue;
                res-=sum[fu]-sum[fu-size[fu]]+sum[fv]-sum[fv-size[fv]];
                size[fv]+=size[fu],fa[fu]=fv;
                res+=sum[fv]-sum[fv-size[fv]];
            }
            it++;
        }
        ans[q[i].second]=res;
    }
    for (int i=1;i<=Q;++i) printf("%lld\n",ans[i]);
    return 0;
}
```


---

