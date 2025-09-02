# [NERC 2018] King Kog’s Reception

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) K 题。

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
? 6```

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
1```

# 题解

## 作者：hzoi_Shadow (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P9801)

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

## 作者：meyi (赞：4)

弱智吧入吧检测题，我和 std 和某位集训队大神均成功入吧。

先介绍下我的做法：设 $a_i$ 表示公主 $i$ 的 $t$，$b_i$ 表示骑士 $i$ 的 $t$，容易发现对于公主 $i$，只有满足 $a_i\ge b_j$ 的骑士 $j$ 才会影响她的等待时间，因此我们将所有操作按 $t$ 排序，在计算公主 $i$ 的答案前添加相应骑士 $j$。对于骑士 $i$，由线段树分治的思想可知，他只会影响一段区间的公主，具体来说，对于这段区间的公主的答案 $ans_{[l,r]}$，先将它们对 $b_i$ 取 $\max$，再让它们加上 $d$，那么最终公主 $j$ 的答案就是 $\max(ans_j-a_j,0)$。所以需要一个数据结构，支持区间加，区间取 $\max$，单点查询，容易发现这个就是 Segment Tree Beats 的板子，故时间复杂度 $O(n\log n)$。

由于码风冗长，所以[第一种做法的参考代码](https://www.luogu.com.cn/paste/s30i1fel)放剪贴板了。

然后发现上面那个东西不仅要离线还要写 beats 太过于弱智吧了，考虑使用值域线段树在线维护计算公主的答案的过程，你发现每个点可以用两个变量 $ans$ 和 $sum$ 来表示，$ans_{[l,r]}$ 表示 $r$ 时刻到达的公主在只考虑 $[l,r]$ 内的骑士需要等到哪个时刻，$sum_{[l,r]}$ 表示 $[l,r]$ 内的骑士的 $d$ 之和为多少。初始 $ans_{[i,i]}=i$，$sum_{[i,i]}=0$。`+` 和 `-` 操作时对 $ans_{[t,t]}$ 进行单点加减即可。合并左右儿子的过程就是 $ans_{[l,r]}=\max(ans_{[l,mid]}+sum_{[mid+1,r]},ans_{[mid+1,r]})$，$sum_{[l,r]}=sum_{[l,mid]}+sum_{[mid+1,r]}$。最后 $t$ 的答案就是 $ans_{[1,t]}-t$，也即查询前缀。我们在 $O(n\log n)$ 的时间内解决了本题。

第二种做法的参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define fi first
#define se second
pll t[4000000];
inline pll merge(const pll &x,const pll &y){return {max(x.fi+y.se,y.fi),x.se+y.se};}
void build(int p,int l,int r){
	t[p].fi=r;
    if(l==r)return;
    int mid=l+r>>1;
    build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
ll ret;
void query(int p,int l,int r,int k){
    if(r<=k){ret=max(t[p].fi,ret+t[p].se);return;}
    int mid=l+r>>1;
    query(p<<1,l,mid,k);
    if(k>mid)query(p<<1|1,mid+1,r,k);
}
void modify(int p,int l,int r,int k,int v){
    if(l==r){t[p].fi+=v,t[p].se+=v;return;}
    int mid=l+r>>1;
    k<=mid?modify(p<<1,l,mid,k,v):modify(p<<1|1,mid+1,r,k,v);
    t[p]=merge(t[p<<1],t[p<<1|1]);
}
pii a[300000];
int main(){
	int n;
	scanf("%d",&n);
	build(1,0,1e6-1);
	for(int i=0;i<n;++i){
		char op;
		while((op=getchar())!='+'&&op!='-'&&op!='?');
		if(op=='+'){
			scanf("%d%d",&a[i].fi,&a[i].se),--a[i].fi;
			modify(1,0,1e6-1,a[i].fi,a[i].se);
		}
		else if(op=='-'){
			int j;
			scanf("%d",&j),--j;
			modify(1,0,1e6-1,a[j].fi,-a[j].se);
		}
		else{
			int t;
			scanf("%d",&t),--t;
			ret=0;
			query(1,0,1e6-1,t);
			printf("%lld\n",ret-t);
		}
	}
	return 0;
}

```

---

## 作者：wind_seeker (赞：3)

~~没有题解，吃个螃蟹。~~

考虑用线段树维护。

维护两个值，一个 $sum_{l,r}$ 表示该区间骑士总消耗时间，一个 $R_{l,r}$ 表示该区间骑士访谈后最后的时间。注意题目要求对于骑士 $i$，结束时间为 $t_i+d_i$ 不是 $t_i+d_i-1$。

考虑如何 $\text{pushup}$，如果左儿子的 $R$ 值超过右儿子的起始点，那么右儿子所有骑士访谈时间都要往后顺延，判断左儿子的 $R$ 值加上右儿子所有骑士总时间是否超过右儿子的 $R$ 值即可。

考虑如何 $\text{query}$，访问右儿子时，将左儿子的 $R$ 值传入，算答案时取 $\text{max}$ 即可。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;

int q,t[N],num[N];
#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
int sum[N<<2],R[N<<2];
void push_up(int rt){
	sum[rt]=sum[ls]+sum[rs];
	R[rt]=max(R[ls]+sum[rs],R[rs]);
}
void update(int rt,int l,int r,int pos,int k){
	if(l==r) return sum[rt]=k,R[rt]=l+k,void();
	int mid=(l+r)>>1;
	if(pos<=mid) update(lson,pos,k);else update(rson,pos,k);
	push_up(rt);
}
int query(int rt,int l,int r,int ql,int qr,int now){
	if(ql<=l&&r<=qr) return max(R[rt],now+sum[rt]);
	int mid=(l+r)>>1,resl=0,resr=0;
	if(ql<=mid) resl=query(lson,ql,qr,now);
	if(mid<qr) resr=query(rson,ql,qr,resl);
	return max(resl,resr);
}

signed main(){
	scanf("%lld",&q);
	for(int i=1,x;i<=q;i++){
		char op=getchar();
		while(op!='?'&&op!='+'&&op!='-') op=getchar();
		if(op=='+'){
			scanf("%lld%lld",&t[i],&num[i]);
			update(1,1,N,t[i],num[i]);
		}
		if(op=='-'){
			scanf("%lld",&x);
			update(1,1,N,t[x],0);
		}
		if(op=='?') scanf("%lld",&x),printf("%lld\n",max(0ll,query(1,1,N,1,x,0)-x));
	}
	return 0;
}
```

---

## 作者：FBW2010 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9801)

# 题意

这道题题面坑点巨多，~~也许是这样才紫的~~，这里提醒几点。

+ 骑士实际拜访的顺序是来的时间决定的，而不是预约的顺序。

+ 公主只会等待在他之前到的骑士，包括和她一起来的。

+ 如果上一个骑士没拜访完，下个骑士要等他拜访完。

# 思路

由于公主等待的人数只由到的顺序决定，我们根据到的时间维护一颗线段树，$sum_{l,r}$ 就表示来的时间在 $l,r$ 之间的骑士全部拜访完所需的时间。问了方便合并区间，我们再设 $max_{l,r}$ 为 $l,r$ 之间的骑士全部拜访完后的时间，那么便可以这么 `pushup`：

```
root.sum=lson.sum+rson.sum;
root.max=max(lson.max+rson.sum,lson.max);
```

我们来分析一下。$sum$ 就不用多说了，重点在于 $max$。这就有点像推箱子，如果右边有足够的间隙，那么答案就是上面公式中右边的情况；否则，右边所有的间隙都会被顶满，那就是上面左边的情况。

对于删除，其实和添加是相反的，直接加原来的相反数抵消掉即可。

对于询问，问题就相当于是要求在公主之前到的骑士全部拜访完的时间，这与 `pushup` 一样，我们可以将 `ask` 的返回值设为一个结构体，直接 `pushup` 就可以了。

具体可详见代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int q; 
struct node{
	int l,r;
	long long sum,max;
}tree[N*4];
struct did{
	int x,v;
}a[N];
void pu(node &k,node x,node y){
	k.sum=x.sum+y.sum;
	k.max=max(x.max+y.sum,y.max);
}
void bui(int k,int l,int r){
	tree[k].l=l;
	tree[k].r=r;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	bui(k*2,l,mid);
	bui(k*2+1,mid+1,r);
}
void cha(int k,int x,int v){
	if(tree[k].l>x||tree[k].r<x)return;
	if(tree[k].l==tree[k].r){
		tree[k].sum+=v;
		tree[k].max=tree[k].l+tree[k].sum;
		return;
	}
	cha(k*2,x,v);
	cha(k*2+1,x,v);
	pu(tree[k],tree[k*2],tree[k*2+1]);
}
node ask(int k,int x,int y){
	if(tree[k].l>y||tree[k].r<x)return {};
	if(tree[k].l>=x&&tree[k].r<=y){
		return tree[k];
	}
	node p;
	pu(p,ask(k*2,x,y),ask(k*2+1,x,y));
	return p;
}
int main(){
	scanf("%d\n",&q);
	bui(1,1,1e6);
	for(int i=1;i<=q;i++){
		char ch;
		int x,y;
		scanf("%c %d",&ch,&x);
		if(ch=='+'){
			scanf(" %d",&y);
			a[i]={x,y};
			cha(1,x,y);
		}
		else if(ch=='-'){
			cha(1,a[x].x,-a[x].v); 
		}
		else{
			printf("%lld\n",max(0ll,ask(1,1,x).max-x));
		}
		scanf("\n");
	} 
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
嗯，翻译讲得很清楚，自己看吧……~~溜）~~
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

