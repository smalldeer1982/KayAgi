# King Kog's Reception

## 题目描述

有些骑士想要拜访国王，但是由于这里的骑士都很遵守礼节，他们都会提前预约好他要来拜访的时刻和拜访将持续的时间。骑士按照接待处记录的时刻顺序依次拜访国王，每个骑士必须等前面的骑士结束拜访。

很不幸，公主也准备要来拜访国王，但善良的公主并不会为此而打乱骑士们拜访的顺序，而她会等待骑士们拜访完了再来拜访，请你计算公主要等多长时间。

## 说明/提示

对于所有数据，保证 $1 \leq q \leq 3 \times 10^5$，$1 \leq t \leq 10^6$，$1 \leq d \leq 10^6$。

## 样例 #1

### 输入

```
19
? 3
+ 2 2
? 3
? 4
+ 5 2
? 5
? 6
+ 1 2
? 2
? 3
? 4
? 5
? 6
? 7
? 9
- 8
? 2
? 3
? 6
```

### 输出

```
0
1
0
2
1
3
2
1
2
1
0
0
2
1
1
```

# 题解

## 作者：lolte (赞：7)

### 这是GD初二蒟蒻 $lolte$ 的题解

最近在做杂题，刚好做到了这道题。然后就开心写题了。顺便交了翻译，就来写题解了。

**算法标签** ：
- 值域线段树

参考了部分网上的blog。

----

**题目包括三种操作**：

- $+$ $t$ $d$ ，表示在时刻 $t$ 来了骑士，占用国王 $d$ 的时间。
- $-$ $i$ ，表示撤销第 $i$ 次操作。
- $?$ $t$ ，表示询问公主在时刻 $t$ 时来到，需要等多久。

由于题目给出 $1≤t_i≤10^6$ ，考虑使用值域线段树。

我们用 $sum$ 表示区间内所占用国王的时间总长，$wait$ 表示要等到什么时刻才处理完。

则可知：
```cpp
sum[now]=sum[lson]+sum[rson];
wait[now]=max(wait[lson]+sum[rson],wait[rson]);
```

由此可建值域线段树。

对于 $+$ 操作，则为单点修改。 $-$ 操作将 $d$ 取反再修改即可。

考虑 $?$ 操作。

用 $x$ 表示当前要查询的时刻，则有：

```cpp
long long query(int l,int r,int t,int x) {
	if (r<=x) {
    	//对于小于x的，取wait和ans+sum的最大值
		ans=max(wait[t],ans+sum[t]);//
		return ans;
	}
	int mid=(l+r)>>1;
	query(lson,x);//必定往左
	if (x>mid) query(rson,x);
	return ans;
}
```

那么这题差不多就做完了，注意细节。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,a[maxn],b[maxn];
long long ans,sum[maxn*4],wait[maxn*4];
#define lson l,mid,t<<1
#define rson mid+1,r,t<<1|1
void build(int l,int r,int t) {//建树 
	if (l==r) {
		wait[t]=l;
		return;
	}
	int mid=(l+r)>>1;
	build(lson);
	build(rson);
	wait[t]=max(wait[t<<1]+sum[t<<1|1],wait[t<<1|1]);
	sum[t]=sum[t<<1]+sum[t<<1|1];
}
void update(int l,int r,int t,int x,int y) {//修改 
	if (l==r) {
		sum[t]+=y;
		wait[t]+=y;
		return;
	}
	int mid=(l+r)>>1;
	if (x<=mid) update(lson,x,y);
	else update(rson,x,y);
	wait[t]=max(wait[t<<1]+sum[t<<1|1],wait[t<<1|1]);
	sum[t]=sum[t<<1]+sum[t<<1|1];
}
long long query(int l,int r,int t,int x) {//查询 
	if (r<=x) {
		ans=max(wait[t],ans+sum[t]);
		return ans;
	}
	int mid=(l+r)>>1;
	query(lson,x);
	if (x>mid) query(rson,x);
	return ans;
}
signed main(){
	scanf("%d",&n);
	char cz;
	build(1,1e6,1);//值域线段树上界是数值最大，即最大的t 
	for (int i=1;i<=n;++i) {//按题意进行操作 
		scanf(" %c%d",&cz,&a[i]);
		if (cz=='+') {
			scanf("%d",&b[i]);
			update(1,1e6,1,a[i],b[i]);
		}
		else if (cz=='-') {
			update(1,1e6,1,a[a[i]],-b[a[i]]);
		}
		else {
			ans=0;
			printf("%I64d\n",query(1,1e6,1,a[i])-a[i]);//记得是等待的时长，要减去原时刻 
		}
	}
	return 0;
}
```

---

> 最后……

![](https://z4请更换图床a.net/images/2019/01/22/zuosha.jpg)

---

## 作者：wth2026 (赞：0)

# 题目思路
一眼数据结构题。

本题我使用的是线段树，模拟即可（详见代码）。

大体思路：

将骑士的时间变成一个区间，然后使用单点修改，区间查询的线段树维护此区间，即可。

基本上没有什么值得注意的地方（除了线段树不要打挂了以外）。
# AC Code 
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

using namespace std;

struct node {//每一个节点
    int sum;
    int js;
} jd[8000005];

node pushup(node x, node y) {//每一次修改完后的修改上传
    node ans;
    ans.sum = x.sum + y.sum;
    ans.js = max(y.js, x.js + y.sum);
    return ans;
}

void update(int u, int l, int r, int x, int k) {//修改
    if (l == r) {
        jd[u].sum = k;
        jd[u].js = x + k;
        return;
    }

    int m = (l + r) >> 1;

    if (x <= m)
        update(u << 1, l, m, x, k);
    else
        update((u << 1) + 1, m + 1, r, x, k);

    jd[u] = pushup(jd[u << 1], jd[(u << 1) + 1]);
}

node query(int u, int l, int r, int xl, int xr) {//查询
    if (l <= xl && xr <= r)
        return jd[u];

    if (xr < l || xl > r) {
        node ans;
        ans.js = 0;
        ans.sum = 0;
        return ans;
    }

    int m = (xl + xr) >> 1;
    return pushup(query(u << 1, l, r, xl, m), query((u << 1) + 1, l, r, m + 1, xr));
}

int q;
string s;
int t[300005];

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

signed main() {
	init();
	cin >> q;

    for (int i = 1, x; i <= q; ++ i) {
        cin >> s;

        if (s[0] == '+') {
            cin >> t[i] >> x;
            update(1, 1, 1000000, t[i], x);
        } else if (s[0] == '-') {
            cin >> x;

            if (t[x] != 0) {
                update(1, 1, 1000000, t[x], 0);
            }
        } else {
            cin >> x;
            node ans = query(1, 1, x, 1, 1000000);
            cout << max(0ll, ans.js - x) << endl;
        }
    }

    return 0;
}
```

---

## 作者：banned_gutongxing (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9801)

# 思路

这道题很水，一眼线段树。我们维护一根时间轴，其中区间 $[l,r]$ 维护两个值 $sum$ 和 $end$，代表在这个区间中所有士兵的总时间数以及最后这个区间的最后一个士兵拜访完的结束时间，那么考虑怎么合并区间。

假设 $lsum$、$rsum$、$lend$、$rend$ 分别代表左儿子的 $sum$，右儿子的 $sum$，左儿子的 $end$，右儿子的 $end$。那么：

+ 考虑 $sum$ 的转移\
	不用质疑，$sum=lsum+rsum$

+ 考虑 $end$ 的转移\
	整个区间的结束时间分为两种：
	1. 左区间的结束位置过远，其他的士兵只能排在左区间最后一个士兵拜访完的后面。此时的结束时间为 $lend+rsum$。
    2. 左区间不够远，只能让其中一些士兵（可以为 $0$）后退，此时并不影响最后一个士兵的拜访，所以结束时间就是原本右区间的结束时间，即 $rend$。

然后，就结束了。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
const int MAXN = 3e5+10;
using namespace std;
class SegmentTree{
	private:
		struct something{
			int sum;
			int end;
		};
		something merge(something a,something b){
			something ans;
			ans.sum = a.sum+b.sum;
			ans.end = max(a.end+b.sum,b.end);
			return ans;
		}
		struct segmenttree{
			int l,r,len;
			something a;
		}tree[MAXN<<3];
		bool is_son(int k){
			return (tree[k].l==tree[k].r);
		}
		void pushup(int k){
			if(is_son(k)) return;
			tree[k].a = merge(tree[k*2].a,tree[k*2+1].a);
		}
	public:
		void build(int k,int l,int r){
			tree[k].l = l;
			tree[k].r = r;
			tree[k].len = r-l+1;
			if(l==r){
				return;
			}
			int mid = (l+r)>>1;
			build(k*2,l,mid);
			build(k*2+1,mid+1,r);
		}
		void add(int k,int a,int b){
			if(tree[k].l>a||tree[k].r<a) return;
			if(tree[k].l==a&&tree[k].r==a){
				tree[k].a.sum = b;
				tree[k].a.end = a+b; 
				return;
			}
			add(k*2,a,b);
			add(k*2+1,a,b);
			pushup(k);
		}
		void reset(int k,int a){
			if(tree[k].l>a||tree[k].r<a) return;
			if(tree[k].l==a&&tree[k].r==a){
				tree[k].a.sum = 0;
				tree[k].a.end = 0; 
				return;
			}
			reset(k*2,a);
			reset(k*2+1,a);
			pushup(k);
		}
		something ask(int k,int a){
			if(tree[k].l>a) return {0,0};
			if(tree[k].r<=a){
				return tree[k].a;
			}
			auto ans = merge(ask(k*2,a),ask(k*2+1,a));
			pushup(k);
			return ans;
		}
}t;
int n;
char op[10];
int mp[MAXN];
signed main(){
	scanf("%lld",&n);
	t.build(1,1,1e6+10);
	for(int i = 1;i<=n;i++){
		int x,y;
		scanf("%s%lld",op,&x);
		if(op[0]=='?'){
			printf("%lld\n",max(0ll,t.ask(1,x).end-x));
		}else if(op[0]=='+'){
			scanf("%lld",&y);
			t.add(1,x,y);
			mp[i] = x;
		}else{
			t.reset(1,mp[x]);
		}
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1089K)

# 前置知识

[线段树](https://oi-wiki.org/ds/seg/)

# 解法 

第一眼感觉和 [luogu P1083 [NOIP2012 提高组] 借教室](https://www.luogu.com.cn/problem/P1083) 很像。本题同样采用线段树维护，$sum_{l,r}(1 \le l \le r \le 10^6)$ 表示从 $l \sim r$ 时刻内骑士拜访的总时间，$maxx_{l,r}(1 \le l \le r \le 10^6)$ 表示从 $l \sim r$ 时刻内骑士拜访完的最后时间。

build 函数和普通线段树一样。

update 函数和普通单点修改一样。
  - 如果不会线段树单点修改，请左转 [luogu P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)。

pushup 函数是本题一个难点。考虑对于从 $l \sim r(1 \le l \le r \le 10^6)$ 时刻，如果左区间 $l \sim mid$ 时刻骑士拜访完的最后时间大于右区间 $mid+1 \sim r$ 时刻的起始点，则右区间 $mid+1 \sim r$ 时刻内所有骑士拜访均要向后推迟，即 ``tree[rt].maxx=max(tree[lson(rt)].maxx+tree[rson(rt)].sum,tree[rson(rt)].maxx);``。

query 函数同理，查询时需要额外记录左区间 $l \sim mid$ 时刻骑士拜访完的最后时间，对于最终时间时需要取 $\max$，即 ``max(tree[rt].maxx,tree[rt].sum+maxxx);``。最终答案即为最终时间减去起始拜访时间。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long//本题需要开 long long 
#define sort stable_sort 
#define endl '\n'
ll t[400000],d[400000],ans=0;
struct SegmentTree
{
	ll l,r,sum,maxx;
}tree[5000000];
ll lson(ll x)
{
	return x*2;
}
ll rson(ll x)
{
	return x*2+1;
}
void pushup(ll rt)
{
	tree[rt].sum=tree[lson(rt)].sum+tree[rson(rt)].sum;
	tree[rt].maxx=max(tree[lson(rt)].maxx+tree[rson(rt)].sum,tree[rson(rt)].maxx);
}
void build(ll rt,ll l,ll r)
{
	tree[rt].l=l;
	tree[rt].r=r;
	if(l==r)
	{
		tree[rt].maxx=tree[rt].sum=0;
		return;
	}
	ll mid=(l+r)/2;
	build(lson(rt),l,mid);
	build(rson(rt),mid+1,r);
	pushup(rt);
}
void update(ll rt,ll pos,ll val)
{
	if(tree[rt].l==tree[rt].r)
	{
		tree[rt].sum=val;
		tree[rt].maxx=tree[rt].l+val;
		return;
	}
	else
	{
		ll mid=(tree[rt].l+tree[rt].r)/2;
		if(pos<=mid)
		{
			update(lson(rt),pos,val);
		}
		else
		{
			update(rson(rt),pos,val);
		}
	}
	pushup(rt);
}
ll query(ll rt,ll l,ll r,ll maxxx)
{
	if(l<=tree[rt].l&&tree[rt].r<=r)
	{
		return max(tree[rt].maxx,tree[rt].sum+maxxx);
	}
	else
	{
		ll mid=(tree[rt].l+tree[rt].r)/2;
		if(l<=mid)
		{
			ans=max(ans,query(lson(rt),l,r,maxxx));
		}
		if(mid<r)
		{
			ans=max(ans,query(rson(rt),l,r,ans));
		}
		return ans;
	}
}
int main()
{
	ll q,n,i,val;
	char pd;
	cin>>q;
	build(1,1,1000000);
	for(i=1;i<=q;i++)
	{
		cin>>pd;
		if(pd=='+')
		{
			cin>>t[i]>>d[i];
			update(1,t[i],d[i]);//因为第i位骑士访谈的时间是t[i]到t[i]+d[i]
		}
		if(pd=='-')
		{	
			cin>>val;
			update(1,t[val],0);
		}
		if(pd=='?')
		{
			cin>>val;
			ans=0;
			cout<<max(0ll,query(1,1,val,ans)-val)<<endl;
		}
	}
	return 0;
} 
```

# 后记

双倍经验：P9801 | CF1089K

---

## 作者：Felix72 (赞：0)

读完题后，我们发现如果不同骑士之间的安排有冲突，应该按照队列顺序，即后面的顺推。那我们也可以理解为把冲突的时间打碎成若干个小段，后面区间的空白部分用前面超出的时间补。

这个显然可以使用线段树维护，具体的，对于一个树点，维护当前区间超出的时间和内部的空格两个标记，再写一个区间询问即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair < long long, long long > PII;
const int N = 1000010;
int n, sve[N][2], cur[N];
int rt, idx;
struct SGT
{
	int ls, rs;
	long long sum, space;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	#define sum(x) tree[x].sum
	#define space(x) tree[x].space
}tree[N * 4];
inline void pushup(int now)
{
	int del = min(sum(ls(now)), space(rs(now)));
	space(now) = space(ls(now)) + space(rs(now)) - del;
	sum(now) = sum(ls(now)) + sum(rs(now)) - del;
}
inline void build(int &now, int l, int r)
{
	if(!now) now = ++idx;
	if(l == r) {space(now) = 1; return ;}
	int mid = l + r >> 1;
	if(l <= mid) build(ls(now), l, mid);
	if(mid < r) build(rs(now), mid + 1, r);
	pushup(now);
}
inline void insert(int now, int l, int r, int pos, int num)
{
	if(l == r)
	{
		space(now) = 0;
		sum(now) = num - 1;
		return ;
	}
	int mid = l + r >> 1;
	if(pos <= mid) insert(ls(now), l, mid, pos, num);
	if(mid < pos) insert(rs(now), mid + 1, r, pos, num);
	pushup(now);
}
inline void clear(int now, int l, int r, int pos)
{
	if(l == r) {space(now) = 1, sum(now) = 0; return ;}
	int mid = l + r >> 1;
	if(pos <= mid) clear(ls(now), l, mid, pos);
	if(mid < pos) clear(rs(now), mid + 1, r, pos);
	pushup(now);
}
inline PII ask(int now, int l, int r, int L, int R)
{
	if(L <= l && r <= R)
	{
		return {space(now), sum(now)};
	}
	int mid = l + r >> 1;
	if(R <= mid) return ask(ls(now), l, mid, L, R);
	if(mid < L) return ask(rs(now), mid + 1, r, L, R);
	PII p1 = ask(ls(now), l, mid, L, R), p2 = ask(rs(now), mid + 1, r, L, R);
	long long del = min(p1.second, p2.first);
	return {p1.first + p2.first - del, p1.second + p2.second - del};
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	build(rt, 1, 1e6);
	for(int i = 1; i <= n; ++i)
	{
		char c; int x, y;
		cin >> c >> x;
		if(c == '?')
		{
			long long ans = 0;
			if(x >= 2) ans = ask(rt, 1, 1e6, 1, x - 1).second;
			cout << ans + cur[x] << '\n';
		}
		if(c == '+')
		{
			cin >> y;
			sve[i][0] = x, sve[i][1] = y;
			cur[x] = y;
			insert(rt, 1, 1e6, x, y);
		}
		if(c == '-') clear(rt, 1, 1e6, sve[x][0]), cur[sve[x][0]] = 0;
	}
	return 0;
}
```

---

