# Cloud Computing

## 题目描述

$\text{Buber}$ 是一家致力于浪费投资者的钱的 $\text{Berland}$ 技术公司。最近，$\text{Buber}$ 决定将他的设施转移到云端。公司决定连续$\ n\ $天云端租用$\text{CPU}$。$\text{Buber}$每天都要租用$\ k\ $个$\text{CPU}$。

云端供应商提供$\ m\ $个租用计划，第$i$个计划有如下的特征：

- $l_i,r_i$ 表示第$\ i\ $个计划从第$\ l_i\ $天开始，第$\ r_i\ $天结束。
- $c_i$ 表示第$\ i\ $个计划中，每天最多租用$\text{CPU}$个数。
- $p_i$ 表示第$\ i\ $个计划中，租用一个$\text{CPU}$一天的花费。

$\text{Buber}$ 可以同时使用多个计划，即他可以在第$\ x\ $天在每个进行中的计划（即$l_i≤x≤r_i$）中租用 $[0,c_i]$个$\text{CPU}$.

现在$\text{Buber}$告诉你正整数$\ k\ $，表示每天所需的$\text{CPU}$个数（如果某一天无论怎么租用都不能租到$\ k\ $个，他也希望租尽量多的$\text{CPU}$）。请你告诉他，他在这$\ n\ $天中最少需要花费多少钱来租用$\text{CPU}$？

## 样例 #1

### 输入

```
5 7 3
1 4 5 3
1 3 5 2
2 5 10 1
```

### 输出

```
44
```

## 样例 #2

### 输入

```
7 13 5
2 3 10 7
3 5 10 10
1 2 10 6
4 5 10 9
3 4 10 8
```

### 输出

```
462
```

## 样例 #3

### 输入

```
4 100 3
3 3 2 5
1 1 3 2
2 4 4 4
```

### 输出

```
64
```

# 题解

## 作者：StayAlone (赞：6)

### 瞎扯

最近学线段树啊，这题大约都是自己想出来的。~~主要是老师讲课的时候没听，题解又看不懂啊啊。~~做法比较直接。

### 题意

在 $n$ 天内，有 $m$ 种物品。其中第 $i$ 种物品有 $c_i$ 个，且将在 $[l_i, r_i]$ 这几天出现，价格为每个 $p_i$。给定一个 $k$，每天要**租借一天**价格最小的 $k$ 个物品（如不够就能租多少租多少）。求这 $n$ 天要花的钱。

### 思路

建一棵线段树，维护两个信息。区间 $[l, r]$ 表示：  
1. $cnt$。价值为 $[l, r]$ 之间的物品数量之和。
2. $sum$。价值为 $[l, r]$ 之间的物品全部租完所需的代价。

两个东西的 pushup 都是直接相加。然后就很裸了。

拿一个 vector，$op_i$ 表示在第 $i$ 天要进行的操作。如果有一种物品要出现，就把它的数量放进来；反之，把它的数量的相反数放进来。注意是在 $r_i + 1$ 的位置放删除标记，因为第 $r_i$ 天这个物品仍然存在。

循环模拟每一天的情况，然后每一天求前 $k$ 大的和即可。  

```cpp
il ll get()
{
	ll all = t[1].cnt; // 有的物品的总量
	if (all <= k) return query(1, 1, T, 1, T, 0); // 如果总量不及 k，全部租借
	int k_0th = kth(1, 1, T, k); // 表示第 k 贵的代价。
	ll k1num = query(1, 1, T, 1, k_0th - 1, 1);
	return query(1, 1, T, 1, k_0th - 1, 0) + (k - k1num) * k_0th;
}
```

做完了。时间复杂度 $O(m\log n + n\log n)$。~~我猜常数有个 3。~~

[AC code 记录](https://www.luogu.com.cn/record/69805564)  

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define ptc putchar
#define il inline
#define pb push_back
#define fst first
#define snd second
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define ......
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef ......
const int MAXN = 1e6 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)

    il int read()

	template <typename T, typename ...L>
	il void read(T &x, L &...y) {read(x); read(y...);}

	template <typename T>
	il void write(T x)

	template <typename T>
	il T my_max(const T &x, const T &y)
}
using namespace stupid_lrc;
// 奇妙缺省源
int n, m, k; int T;
vector <pii> op[MAXN]; ll ans;

struct setr
{
	ll cnt, sum;
} t[MAXN << 2];

il void pushup(int x)
{
	t[x].cnt = t[ls(x)].cnt + t[rs(x)].cnt;
	t[x].sum = t[ls(x)].sum + t[rs(x)].sum;
}

il void upd(int x, int l, int r, int k, int num)
{
	if (l > k || r < k) return;
	if (l == r && r == k) return t[x].cnt += num, t[x].sum = t[x].cnt * l, void();
	int mid = l + r >> 1;
	upd(ls(x), l, mid, k, num); upd(rs(x), mid + 1, r, k, num);
	pushup(x);
}

il ll query(int x, int l, int r, int ql, int qr, bool h)
{
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return h ? t[x].cnt : t[x].sum;
	int mid = l + r >> 1;
	return query(ls(x), l, mid, ql, qr, h) + query(rs(x), mid + 1, r, ql, qr, h);
}

il int kth(int x, int l, int r, int k)
{
	if (l == r) return l;
	int mid = l + r >> 1;
	if (k <= t[ls(x)].cnt) return kth(ls(x), l, mid, k);
	return kth(rs(x), mid + 1, r, k - t[ls(x)].cnt);
}

il ll get()
{
	ll all = t[1].cnt;
	if (all <= k) return query(1, 1, T, 1, T, 0);
	int k_0th = kth(1, 1, T, k);
	ll k1num = query(1, 1, T, 1, k_0th - 1, 1);
	return query(1, 1, T, 1, k_0th - 1, 0) + (k - k1num) * k_0th;
}

int main()
{
	read(n, k, m);
	rep1(i, 1, m)
	{
		int l, r, c, p; read(l, r, c, p); T = my_max(T, p);
		op[l].pb(mp(c, p)); op[r + 1].pb(mp(-c, p));
	}
	rep1(i, 1, n)
	{
		for (auto p : op[i]) upd(1, 1, T, p.snd, p.fst);
		ans += get();
	}
	write(ans); rout;
}
```

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]CF1070C%20Cloud%20Computing)

# 思路

考虑用线段树维护区间信息：

1. 价格在 $[l,r]$ 之间的 CPU 的数量。

2. 购买所有价格在 $[l,r]$ 之间 CPU 所需的钱。

容易将区间修改转化为差分，从而实现单点修改。于是可以使用 $n$ 个 `vector` 存储第 $i$ 天所需进行的修改。

查询第 $i$ 天的答案时，如果不足 $k$ 个 CPU 则直接选完所有的 CPU；否则贪心地选择价格前 $k$ 小的 CPU。

这里实现的方法是，先求出第 $k$ 小的值 $x$，将小于 $x$ 的所有 CPU 全部卖掉，然后剩下的用 $x$ 补满 $k$ 即可。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 1e6 + 10;
int n,k,m,ans;
vector<pii> Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int cnt,sum;
    }tr[N << 2];

    inline void pushup(int u){
        tr[u].cnt = tr[ls(u)].cnt + tr[rs(u)].cnt;
        tr[u].sum = tr[ls(u)].sum + tr[rs(u)].sum;
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(u),l,mid),build(rs(u),mid + 1,r);
    }

    inline void modify(int u,int x,int k){
        if (tr[u].l == x && tr[u].r == x){
            tr[u].cnt += k;
            tr[u].sum = tr[u].cnt * x;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(ls(u),x,k);
        if (x > mid) modify(rs(u),x,k);
        pushup(u);
    }

    inline int query_kth(int u,int k){
        if (tr[u].l == tr[u].r) return tr[u].l;
        if (tr[ls(u)].cnt < k) return query_kth(rs(u),k - tr[ls(u)].cnt);
        else return query_kth(ls(u),k);
    }

    inline int query_cnt(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].cnt;
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query_cnt(ls(u),l,r);
        if (r > mid) res += query_cnt(rs(u),l,r);
        return res;
    }

    inline int query_sum(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query_sum(ls(u),l,r);
        if (r > mid) res += query_sum(rs(u),l,r);
        return res;
    }

    inline int get(){
        if (tr[1].cnt <= k) return tr[1].sum;
        int kth = query_kth(1,k);
        int rk = query_cnt(1,1,kth - 1);
        return query_sum(1,1,kth - 1) + (k - rk) * kth;
    }

    #undef ls
    #undef rs
}T;

signed main(){
    n = read(),k = read(),m = read();
    T.build(1,1,1e6);
    for (re int i = 1;i <= m;i++){
        int l,r,c,p;
        l = read(),r = read(),c = read(),p = read();
        Q[l].push_back({c,p}),Q[r + 1].push_back({-c,p});
    }
    for (re int i = 1;i <= n;i++){
        for (auto p:Q[i]) T.modify(1,p.snd,p.fst);
        ans += T.get();
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：绝顶我为峰 (赞：3)

题意：一个时间轴，在 $[l_i,r_i]$ 时刻会出现 $c_i$ 个价值为 $p_i$ 的物品，求每个时刻出现的物品价值前 $k$ 小（不足 $k$ 个则剩余补 $0$）之和。

考虑 $l_i=r_i=1$ 怎么做，那么有显然的贪心：直接从小到大取即可。

但是现在物品是动态的，于是考虑用数据结构维护物品。

为了契合上面的贪心，我们使用以物品价值为下标的树状数组来维护这一过程。扫描线扫描时间，那么每个物品等价于一次插入，一次删除操作。然后我们用树状数组维护每种价值的物品个数。由于我们要对每个时间快速计算答案，我们不能从小到大枚举价值。但由于我们选择的物品价值是不降的，且只有最大的权值有可能不全选中，于是可以在树状数组上倍增（不会树状数组倍增请左转 2020 联合省选 冰火战士，这个 trick 应该很普及了），找到全选的部分的权值最大值，然后比最大值小的前缀一定都选，直接计算贡献。

算完全选的部分，后面可能剩一点边角料还没算，我们就直接找到比最大值大的下一个物品数量不为 $0$ 的价值，然后计算这部分贡献。这一部分可以直接用一个 set 来维护所有有物品的位置。

总复杂度 $O((n+m)\log v)$。

```cpp
//noip rp++!
#include<iostream>
#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
#define int long long
struct element
{
    int opt,t,c,p;
    bool operator <(const element &other) const
    {
        return t<other.t;
    }
}a[200001<<1];
int n,k,m,cnt[1000001],val[1000001],ans,maxn;
set<int> s;
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline int lowbit(int x)
{
    return x&-x;
}
inline void update(int x,int val1,int val2)
{
    for(;x<=maxn;x+=lowbit(x))
    {
        cnt[x]+=val1;
        val[x]+=val2;
    }
}
inline int query1(int x)
{
    int res=0;
    for(;x;x-=lowbit(x))
        res+=cnt[x];
    return res;
}
inline int query2(int x)
{
    int res=0;
    for(;x;x-=lowbit(x))
        res+=val[x];
    return res;
}
signed main()
{
    n=read(),k=read(),m=read();
    for(int i=1;i<=m;++i)
    {
        int l=read(),r=read(),c=read(),p=read();
        maxn=max(maxn,p);
        a[(i<<1)-1]={1,l,c,p};
        a[i<<1]={-1,r+1,c,p};
    }
    m<<=1;
    sort(a+1,a+m+1);
    int p=1;
    for(int i=1;i<=n;++i)
    {
        while(p<=m&&a[p].t<=i)
        {
            update(a[p].p,a[p].c*a[p].opt,a[p].p*a[p].c*a[p].opt);
            if(query1(a[p].p)-query1(a[p].p-1))
                s.insert(a[p].p);
            else
                if(s.find(a[p].p)!=s.end())
                    s.erase(s.find(a[p].p));
            ++p;
        }
        if(query1(maxn)<=k)
        {
            ans+=query2(maxn);
            continue;
        }
        int pos=0,tmp=0,val=0,v=0;
        for(int j=20;~j;--j)
        {
            tmp=pos|(1<<j);
            if(tmp>maxn)
                continue;
            v=val+cnt[tmp];
            if(v>k)
                continue;
            val=v;
            pos=tmp;
        }
        ans+=query2(pos);
        if(val==k)
            continue;
        int num=*s.upper_bound(pos);
        ans+=num*(k-val);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：星·辉 (赞：2)

一开始很懵逼。。。后来想了想这不就是离散化+权值线段树吗？调了一会儿就AC了。

首先，处理读入。注意到对于一个计划，有开始时间和结束时间，可以开一个$\text{struct}$处理。

对每一个$\text{Plan}$，可以记录它的(开始/结束)时间，再记录每天最多可租个数即$\ c\ $(结束就把个数记成负数)，以及每一个的租金$\ p\ $。

然后对于每一个$\ \text{Plan}\ $变化(开始或结束) 按时间排序一下，就是线段树单点修改裸题。

上代码：

```cpp
#include<bits/stdc++.h>//Could Computing 
#define LL long long
using namespace std;
inline LL read(){
	char c=getchar();while(c>'9'||c<'0')c=getchar();
	LL ans=0;for(;c<='9'&&c>='0';c=getchar())ans=ans*10+c-'0';return ans;
}
int n,m;
LL k,ans,tt,Pmax;
struct Plan{ int t;LL c,p; }p[400010];
inline bool tdn(Plan x,Plan y){ return x.t<y.t; }
struct Reply{ 
	int h=0;//表示要将价格在[1,h]间的都租走 
	LL ex=0;//表示除了上述的还要租走多少钱的 CPU 
};
struct Node{//按p开权值线段树 
	LL cnt=0,wgh=0;//个数和总价钱 
}node[4000010];

inline void push_up(int t){
	node[t].cnt=node[t<<1].cnt+node[t<<1|1].cnt;
	node[t].wgh=node[t<<1].wgh+node[t<<1|1].wgh;
}

void update(int t,int l,int r,int x){//单点修改 
	if(l==p[x].p&&r==p[x].p){
		node[t].cnt+=p[x].c;
		node[t].wgh+=p[x].c*p[x].p;
		return;
	}
	int mid=(l+r)>>1;
	if(p[x].p<=mid) update(t<<1,l,mid,x);
	else update(t<<1|1,mid+1,r,x);
	push_up(t);
}

Reply query(int t,int l,int r,LL num){
	if(l==r){
		Reply ans;
		if(num==node[t].cnt) ans.h=l;
		else ans.h=l-1,ans.ex=l*num;
		return ans;
	}
	if(node[t].cnt==num){ Reply ans;ans.h=r;return ans;}//据说这样可以省一点时间而且答案不会受影响
	int mid=(l+r)>>1;
	if(node[t<<1].cnt>=num) return query(t<<1,l,mid,num);
	return query(t<<1|1,mid+1,r,num-node[t<<1].cnt);//标准的 线段树上二分 操作 
}
LL sum_query(int t,int l,int r,int L,int R){
	/*查一下区间和(其实这个可以和query一起写的),但是我太菜了,怕写炸*/
	if(L<=l&&r<=R) return node[t].wgh;
	int mid=(l+r)>>1;LL ans=0;
	if(L<=mid) ans+=sum_query(t<<1,l,mid,L,R);
	if(R>mid) ans+=sum_query(t<<1|1,mid+1,r,L,R);
	return ans;
}

int main(){
	n=read(),k=read(),m=read();
	for(int i=1;i<=m;i++){//初始化 
		p[(i<<1)-1].t=read(),p[i<<1].t=read()+1;
		/*这里由于给出的是[开始时间,结束时间),所以对于结束时间加1使时间变成闭区间*/
		p[(i<<1)-1].c=read(),p[i<<1].c=-p[(i<<1)-1].c;//结束时个数c是负的 
		p[(i<<1)-1].p=read(),p[i<<1].p=p[(i<<1)-1].p;
		if(p[i<<1].p>Pmax) Pmax=p[i<<1].p;
	}
	sort(p+1,p+(m<<1|1),tdn);//排序 
	update(1,1,Pmax,1);
	/*由于第一个Plan开始前每天都没有可以租的,没有答案贡献,所以直接将第一个Plan加入线段树 */
	for(int i=2;i<=(m<<1);i++){
		tt=p[i].t-p[i-1].t;//每一段分段处理, 相当于离散化 
		if(node[1].cnt<=k) ans+=node[1].wgh*tt;//如果所有能租的都不到k个,只能全部买走了... 
		else{
			Reply u=query(1,1,Pmax,k);
			LL res=u.ex;
			if(u.h) res+=sum_query(1,1,Pmax,1,u.h);
			ans+=res*tt;//对于这tt天都是一样的,直接将每一天的花费乘上天数就好了 
		}
		update(1,1,Pmax,i);//不要忘了把新的Plan加入 
	}
	printf("%lld",ans);
}
```


---

## 作者：CQ_Bob (赞：2)

## 分析

思路不难想，我们对于第 $i$ 个计划的时间，可以分成 $l$ 和 $r+1$ 两部分。用权值线段树维护，在第 $l$ 天的时候就将该计划的内容加入权值线段树中，直到过了该计划的时间，也就是第 $r+1$ 天，再将这个计划的内容删除。把每一天需要修改的内容存进 vector 中，修改完查询权值线段树中前 $k$ 个数的值即可。

比较难想的是查询。如果当前区间中的 CPU 数量不超过 $k$，则表示这个区间能够凑出的 CPU 数量是无法达到 $k$ 的。为了使答案尽量趋近于 $k$，这个区间的贡献就是区间的代价和。如果区间中 CPU 数量比 $k$ 大，则优先考虑左子区间，右子区间只需要补上左区间差的那些数量。这里要特判一下边界，在左右端点相同且数量大于 $k$ 的时候，直接返回 $k \times val$。$val$ 是这个点的点权，也就是端点下标。

复杂度是 $O((n+m) \log V)$ 的，$V$ 是值域。


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
#define re register
#define il inline

const int N=1e6+10;
int n,k,m,ans;
struct node{
	int l,r,cnt,val;
}tr[N<<2];
vector<PII> add[N];

il void up(int now){
	tr[now].cnt=tr[now<<1].cnt+tr[now<<1|1].cnt;
	tr[now].val=tr[now<<1].val+tr[now<<1|1].val;
	return ;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l!=r){
		int mid=l+r>>1;
		build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	}
	return ;
}
il void insert(int now,int k,int c){
	if(tr[now].l==tr[now].r) tr[now].cnt+=c,tr[now].val+=k*c;
	else{
		int mid=tr[now].l+tr[now].r>>1;
		if(k<=mid) insert(now<<1,k,c);
		else insert(now<<1|1,k,c);
		up(now);
	}
	return ;
}
il int query(int u,int k){
	if(tr[u].cnt<=k) return tr[u].val;
	else{
		if(tr[u].l==tr[u].r) return k*tr[u].l;
		if(tr[u<<1].cnt>=k) return query(u<<1,k);
		else return tr[u<<1].val+query(u<<1|1,k-tr[u<<1].cnt); 
	}
}

il void solve(){
	cin>>n>>k>>m;
	build(1,1,N-9);
	for(re int i=1,l,r,c,p;i<=m;++i)
		cin>>l>>r>>c>>p,
		add[l].push_back({c,p}),add[r+1].push_back({-c,p});
	for(re int i=1;i<=n;++i){
		for(auto j:add[i]) insert(1,j.y,j.x);
		ans+=query(1,k);
	}
	cout<<ans;
	return ;
}

signed main(){
	solve();
	return 0;
}
```

CSP2023 RP++。


---

## 作者：ballpoint_pen (赞：1)

考虑开一颗权值线段树记录价格在 $[l,r]$ 之间的所有计划的CPU个数之和、价格之和。那么问题在于如何维护每天有哪些计划可用。

一个很典的套路是开一堆 vector，对于每个计划，在 $vc_{l_i}$ 中加入 $\{ c_i,p_i\}$，在 $vc_{r_i+1}$ 中加入 $\{ -c_i,p_i\}$。

对于每一天分别计算答案。遍历到第 $i$ 天时，对于所有 $vc_i$ 中的二元组 $\{x,y\}$，我们在线段树上将编号 $y$ 对应的节点的 CPU 总数加上 $x$，总价值更新为当前的数量乘单价。然后购买 $k$ 个 CPU 就相当于购买当前可用的前 $k$ 便宜的 CPU。如果当前总数不到 $k$，那么全买；否则可以在线段树上二分出当前的第 $k$ 便宜的价格，设这个值为 $id$，答案即为：当前价格小于 $id$ 的总价 $+(k-($ 价格小于 $id$ 的 CPU 总数 $))\times id$。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=(int)(1e6)+5;
vector<pair<int,int> > vc[N];
int l[N],r[N],c[N],p[N];
int cnt[N<<2],sm[N<<2];
int qcnt(int p,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(ql<=l&&r<=qr)return cnt[p];
	int mid=l+r>>1,ret=0;
	if(ql<=mid)ret+=qcnt(p<<1,l,mid,ql,qr);
	if(qr>mid)ret+=qcnt(p<<1|1,mid+1,r,ql,qr);
	return ret;
}
int qsum(int p,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(ql<=l&&r<=qr)return sm[p];
	int mid=l+r>>1,ret=0;
	if(ql<=mid)ret+=qsum(p<<1,l,mid,ql,qr);
	if(qr>mid)ret+=qsum(p<<1|1,mid+1,r,ql,qr);
	return ret;
}
void update(int p,int l,int r,int qid,int x){
	if(l==r){
		cnt[p]+=x;
		sm[p]=cnt[p]*l;
		return;
	}
	int mid=l+r>>1;
	if(qid<=mid)update(p<<1,l,mid,qid,x);
	else update(p<<1|1,mid+1,r,qid,x);
	cnt[p]=cnt[p<<1]+cnt[p<<1|1];
	sm[p]=sm[p<<1]+sm[p<<1|1];
}
int binary(int p,int l,int r,int k){
	if(l==r)return r;
	int mid=l+r>>1;
	if(k<=cnt[p<<1])return binary(p<<1,l,mid,k);
	else return binary(p<<1|1,mid+1,r,k-cnt[p<<1]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,k,m;
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++){
		cin>>l[i]>>r[i]>>c[i]>>p[i];
		vc[l[i]].push_back({p[i],c[i]});
		vc[r[i]+1].push_back({p[i],-c[i]});
	}
	int tot=0;
	for(int i=1;i<=n;i++){
		for(auto j:vc[i])update(1,1,(int)(1e6),j.first,j.second);
		if(cnt[1]<=k) tot+=sm[1];
		else{
			int id=binary(1,1,(int)(1e6),k);
			tot+=qsum(1,1,(int)(1e6),1,id-1)+(k-qcnt(1,1,(int)(1e6),1,id-1))*id;
		}
	}
	cout<<tot<<endl;
	return 0;
}

```

---

## 作者：Asedwai (赞：0)

## 思路
  明显想到的贪心是按价格排序然后进行租用，越多越好，但如果一天租用的数量已经到达 $k$ 就没有必要租用更多的了。那么我们要维护一个数据结构，储存每一天租借的 CPU 数量，能够计算每个位置还需要租用多少 CPU（在每个位置最多租用 $c_i$ 个的情况下）。换个思路，可以通过维护租用前和租用后的 CPU 数量得到租用的数量。即对于第 $i$ 个租用计划，将区间 $[l_i,r_i]$ 里的数全部加上 $c_i$，并且每个数不能超过 $k$（即与 $k$ 取最小值），然后计算这个区间实际加上了多少，乘上 $p_i$ 就是其对答案的贡献。  

  那么就可以套吉司机线段树了。直接按以上过程维护就可以了。  
## 核心代码
```cpp
sort(a + 1, a + m + 1, [](node a, node b) { return a.p < b.p; }); 
for(int i = 1; i <= m; i ++) {
  long long t = s.query(1, a[i].l, a[i].r); 
  add(1, a[i].l, a[i].r, a[i].c); 
  change(1, a[i].l, a[i].r, k); //将区间 [l,r] 的数与 k 取最小值
  t = query(1, a[i].l, a[i].r) - t; //实际使用的 CPU 数量
  ans += t * a[i].p; 
}
cout << ans << endl; 
```

---

## 作者：AlicX (赞：0)

致敬传奇巨神 @StayAlone，他在初一时就爆切了这道题。 

## Solution  

首先十分套路地想到用差分的思想把一个询问拆成两个单点修改：`v[l].pb({c,p}),v[r+1].pb({-c,p})`，然后用权值线段树维护节区间总的费用以及区间内包含的点。

然后遍历 $1 \sim n$ 天，每天首先把这一天的计划放进去，然后写一个 `find` 函数，函数里传一个 $p$ 表示区间内还需要 $p$ 个点，每次判断做区间是否包容 $p$ 就可以了。最终找到一个 $x$ 表示 $1 \sim x$ 上的点的数量已经大于等于 $k$，再求出这段区间的价值和即可。因为是单点修改，所以不用 `pushdown`，`pushup` 的操作也是很好完成，所以代码很好实现吧。

注：线段树维护的应该是 $1 \sim V$ 的区间，其中 $V$ 是 $p$ 的值域。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define il inline 
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e6+10,INF=1e9+7;  
int n,m,k; 
vector<pii> v[N]; 
struct Mind{ 
	bool operator<(Mind &Cyan)const{ } 
}; 
struct Node{ 
	int l,r; 
	int w,cnt; 
}tr[N<<2]; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void pushup(int u){ 
	tr[u].w=tr[u<<1].w+tr[u<<1|1].w; 
	tr[u].cnt=tr[u<<1].cnt+tr[u<<1|1].cnt; 
} 
il void build(int u,int l,int r){ 
	tr[u]={l,r}; 
	if(l==r) return ; 
	int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
} 
il void modify(int u,int x,int w){ 
	if(tr[u].l==tr[u].r){ 
		tr[u].cnt+=w,tr[u].w+=w*x; 
		return ; 
	} int mid=tr[u].l+tr[u].r>>1; 
	if(abs(x)<=mid) modify(u<<1,x,w); 
	else modify(u<<1|1,x,w); pushup(u); 
} 
il int query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w; 
	int mid=tr[u].l+tr[u].r>>1,w=0; 
	if(l<=mid) w=query(u<<1,l,r); if(r>mid) w+=query(u<<1|1,l,r); 
	return w; 
} 
il int find(int u,int x){ 
	if(tr[u].l==tr[u].r){ 
		int ans=query(1,1,tr[u].l-1); 
		return ans+x*tr[u].l; 
	} int mid=tr[u].l+tr[u].r>>1; 
	if(tr[u<<1].cnt>=x) return find(u<<1,x); 
	return find(u<<1|1,x-tr[u<<1].cnt); 
} 
signed main(){ int ans=0; 
	n=read(),k=read(),m=read(); build(1,1,N-1); 
	for(int i=1,l,r,c,p;i<=m;i++) l=read(),r=read(),c=read(),p=read(),v[l].push_back({c,p}),v[r+1].push_back({-c,p}); 
	for(int i=1;i<=n;i++){ 
		for(int j=0;j<v[i].size();j++) modify(1,v[i][j].y,v[i][j].x); 
		if(tr[1].cnt<=k) ans+=tr[1].w; else ans+=find(1,k); 
	} printf("%lld\n",ans); 
	return 0;
} /* */ 
```

CSP2023 RP++。



---

