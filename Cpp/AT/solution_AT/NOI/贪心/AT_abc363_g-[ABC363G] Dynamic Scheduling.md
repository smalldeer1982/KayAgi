# [ABC363G] Dynamic Scheduling

## 题目描述

给定长度为 $N$ 的数列 $D=(D_1,\ D_2,\ \dots,\ D_N),\ P=(P_1,\ P_2,\ \dots,\ P_N)$。

请按顺序处理 $Q$ 个查询。每个查询的格式如下：

- `c x y` ：将 $D_c$ 改为 $x$，将 $P_c$ 改为 $y$。然后，解决以下问题并输出答案。

> 有 $N$ 个编号为 $1$ 到 $N$ 的工作。  
> 你从今天（记为第 $1$ 天）开始，每天可以选择 $1$ 个工作完成，连续进行 $N$ 天。  
> 如果在第 $D_i$ 天之前（含第 $D_i$ 天）完成第 $i$ 个工作，可以获得 $P_i$ 的报酬。（如果没有在 $D_i$ 天之前完成，则没有报酬）  
> 请你选择完成工作的顺序，使得可以获得的报酬总和最大，并输出该最大值。

## 说明/提示

### 数据范围

- $1 \leq N \leq 10^5$
- $1 \leq Q \leq 10^5$
- $1 \leq D_i \leq N$
- $1 \leq P_i \leq 10^9$
- $1 \leq c \leq N$
- $1 \leq x \leq N$
- $1 \leq y \leq 10^9$
- 输入的所有值均为整数

### 样例解释 1

第 $1$ 个查询如下：  
- 将 $D_3$ 改为 $1$，$P_3$ 改为 $4$。此时 $D = (1, 2, 1),\ P = (3, 6, 4)$。  
- 在子问题中，按如下顺序完成工作是最优方案之一：第 $1$ 天做工作 $3$，第 $2$ 天做工作 $2$，第 $3$ 天做工作 $1$，此时报酬总和为 $10$，因此输出 $10$。

第 $2$ 个查询如下：  
- 将 $D_2$ 改为 $3$，$P_2$ 改为 $9$。此时 $D = (1, 3, 1),\ P = (3, 9, 4)$。  
- 在子问题中，按如下顺序完成工作是最优方案之一：第 $1$ 天做工作 $3$，第 $2$ 天做工作 $1$，第 $3$ 天做工作 $2$，此时报酬总和为 $13$，因此输出 $13$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 2 3
3 6 3
3 1 4
2 3 9```

### 输出

```
10
13```

## 样例 #2

### 输入

```
5 1
1 2 3 4 5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1000000000```

### 输出

```
5000000000```

## 样例 #3

### 输入

```
10 10
6 2 4 1 5 1 6 6 5 3
45 65 71 52 86 52 48 60 40 98
5 6 5
8 4 34
6 7 83
1 3 21
7 5 85
7 4 51
8 2 81
2 7 54
6 1 5
8 6 30```

### 输出

```
394
379
462
457
459
414
443
479
401
396```

# 题解

## 作者：SegTree (赞：12)

首先考虑一个贪心：

插入一个任务时，如果还能放下这个任务，那肯定直接放；否则找一个能用它顶掉的收益最小的，如果比新插入的任务收益小就换；

删除一个任务时，如果这个任务在原方案里没出现，直接删；否则找那些没出现的任务能顶掉它的收益最大的顶上。

这个贪心明显正确，下面考虑如何实现这些操作：

+ 判断方案是否合法：我们维护一颗线段树，在线段树上对于下标 $i$，维护 $i$ 减去方案中必须在 $i$ 之前完成任务个数，那么任务合法当且仅当全局最小值 $\ge 0$。

+ 什么样的任务是可以被替换的：时间 $\ge$ 这个截止日期之后的第一个 $0$。

+ 什么样的任务是可以顶上的：时间 $>$ 最后一个 $0$。

我们需要再维护两颗线段树，维护方案中的价值的区间 $\min$，不在方案中的价值的区间 $\max$。每次插入/删除在第一颗线段树上二分即可。

细节：线段树的叶子节点需要使用 multiset 维护，因为可能有截止时间相同的任务。

---

## 作者：六楼溜刘 (赞：3)

**线段树分治** $+$ **模拟费用流**解法。

前置知识：线段树分治，费用流。

## 题意

- 有两个长度为 $n$ 的数组 $d_n,p_n$，表示有一个若在 $d_i$ 时刻前做完会获得 $p_i$ 收益的任务（若在 $d_i$ 时刻前没有昨晚则任务作废），每个时刻可以做一个任务。
- $q$ 次修改，每次在数据范围内修改某一个任务的参数。每次修改后输出最大收益
- $1\le n,q,\le 10^5,1\le d_i\le n,1\le p_i\le 10^9$。

## 题解

jiangly 讲课时讲了这道题，受益良多，遂以题解记之。

首先对于静态问题有一个经典贪心，把每个人物挂在时间 $p_i$ 处，每个时刻都做时间后缀中剩下的收益最大的任务。

但是贪心显然不好改成在线。jiangly 的解法是考虑改成费用流，然后离线下来线段树分治去掉删除操作，用模拟费用流解决。

首先费用流是好改的，每个时刻开一个点向前连容量无限费用为 $0$ 的边，每个点向汇点连容量为 $1$ 费用为 $0$ 的边，根据每个任务的参数从源点向 $d_i$ 连容量为 $1$ 费用为 $p_i$ 的边，求最大费用最大流。这种费用流改成模拟费用流是比较经典的。

用线段树分治去掉删除操作后，考虑如何在网络流图上加边，加边后有三种可能：产生新的流，产生新的正环（显然求最大费用流时也有消圈定理），不对结果产生影响。

容易发现，任意时刻残量网络都形如时间轴上每个点向源汇点连若干条边（向汇点连的就是原先的边，向源点连的是流过后的反向边）。考虑如何新增一个流量（或者去掉一个正环），那么要么在时间轴上往前流找到一个费用最大的出边（可能是指向汇点的边或指向源点的反向边，前者流量 $+1$，后者解决正环），或者向后流若干条反向边找到费用最大的出边（同理）。

不妨设从某个点指向源汇的出边费用最大值为 $x$，那么第一种是简单的，就是从前缀 $x$ 的最大值处流出（因为时间轴上的边容量无限可以随便流），但是第二种还要考虑反向边是否存在，这怎么办呢？

考虑设某一条边的反向边容量为 $c$，那么就是往后走若干条 $c\ge 1$ 的边找到 $x$，即找到**第一个 $c=0$ 之前的 $x$ 最大值**。

容易发现这些都可以线段树维护，如果费用 $p+x >0$ 就流一下，那么考虑一个流量会对网络流图产生什么影响。

首先向左流会使区间的 $c$ 增加 $1$，向右流会使得区间的 $c$ 减少 $1$。然后会用掉原有的一条出边并新增一条反向边。

乂？我们发现了一个问题：$c$ 有区间加的操作，可能让区间内的 $0$ 突然出现或消失，怎么维护**第一个 $0$ 之前 $x$ 的最小值**呢？

这是经典的，先在序列末尾新增一条 $c$ 恒定为 $0$ 的边，然后改为维护 $c$ 的**区间最小值**之前 $x$ 的最大值，这样 $c$ 的区间加就不会对它产生影响，并且在后缀查询时和原问题是完全相同的。然后结点合并是简单的，不会可以参考代码实现。

注意一个点可能连多条反向边，需要用 `std::multiset` 在叶子处维护。

最后考虑线段树分治如何回退操作。每一层干的事情大致是若干个 $c$ 的区间修改和 $x$ 的单点修改，那么用一个栈把每一层的修改存下来，退出结点时反向做一遍就行了，因为每次操作只会对应 $O(1)$ 的修改所以不会使复杂度变劣。

线段树分治中，每条流会被考虑 $O(\log q)$ 次，每次复杂度 $O(\log n)$。于是复杂度 $O(q\log q\log n)$。

## code

```cpp
#include<bits/stdc++.h>
#define forup(i,s,e) for(i64 i=(s),E123=(e);i<=E123;++i)
#define fordown(i,s,e) for(i64 i=(s),E123=(e);i>=E123;--i)
#define mem(a,b) memset(a,b,sizeof(a))
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void()
#endif
using namespace std;
using i64=long long;
using pii=pair<i64,i64>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
i64 read(){
	i64 x=0,f=1;char c;
	while(!isdigit(c=gc)) if(c=='-') f=-1;
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
	return x*f;
}
#undef gc
const i64 N=1e5+5,inf=0x3f3f3f3f;
i64 n,q,d[N],p[N],pre[N],ans[N];
//pre 数组用来预处理每个任务影响的区间。
#define mid ((l+r)>>1)
#define lson l,mid,id<<1
#define rson mid+1,r,id<<1|1
struct Node{
	pii maxv,lmax;//区间最大值及其下标，第一个最小的 c 前的区间最大值及其下标。
	i64 minc;//区间 c 最小值。
	Node operator +(const Node &r){
		Node res;
		res.maxv=max(maxv,r.maxv);
		res.minc=min(minc,r.minc);
		if(res.minc==minc){
//如果当前结点 c 的最小值从左边继承过来则第一个最小的 c 在左边。
			res.lmax=lmax;
		}else{
//否则在右边。
			res.lmax=max(maxv,r.lmax);
		}
		return res;
	}
};//线段树结点信息及合并。
multiset<i64> ed[N];//存储结点所有出边的费用。
struct SegTree{
	Node info[N<<2];//结点信息。
	i64 mark[N<<2];//c 的区间修改的懒标记。
	void PushDown(i64 id){
		info[id<<1].minc+=mark[id];
		info[id<<1|1].minc+=mark[id];
		mark[id<<1]+=mark[id];
		mark[id<<1|1]+=mark[id];
		mark[id]=0;
	}
	void Build(i64 l=1,i64 r=n,i64 id=1){//初始化。
		mark[id]=0;
		if(l==r){
			ed[l].insert(0);
			info[id].maxv=info[id].lmax=mkp(0,l);
			return;
		}
		Build(lson);Build(rson);
		info[id]=info[id<<1]+info[id<<1|1];
	}
	void UpdateV(i64 P,i64 X,i64 l=1,i64 r=n,i64 id=1){//新增出边。
		if(l==r){
			ed[l].insert(X);
			info[id].maxv=info[id].lmax=mkp(*prev(ed[l].end()),l);
			return;
		}
		if(mark[id]) PushDown(id);
		if(P<=mid) UpdateV(P,X,lson);
		else       UpdateV(P,X,rson);
		info[id]=info[id<<1]+info[id<<1|1];
	}
	void EraseV(i64 P,i64 X,i64 l=1,i64 r=n,i64 id=1){//删除出边。
		if(l==r){
			ed[l].erase(ed[l].find(X));
			info[id].maxv=info[id].lmax=mkp(-inf,l);
			if(ed[l].size()) info[id].maxv=info[id].lmax=mkp(*prev(ed[l].end()),l);
			return;
		}
		if(mark[id]) PushDown(id);
		if(P<=mid) EraseV(P,X,lson);
		else       EraseV(P,X,rson);
		info[id]=info[id<<1]+info[id<<1|1];
	}
	void Modify(i64 L,i64 R,i64 X,i64 l=1,i64 r=n,i64 id=1){//c 的区间加。
		if(L>R) return;
		if(L<=l&&r<=R){
			info[id].minc+=X;
			mark[id]+=X;
			return;
		}
		if(mark[id]) PushDown(id);
		if(L<=mid) Modify(L,R,X,lson);
		if(mid< R) Modify(L,R,X,rson);
		info[id]=info[id<<1]+info[id<<1|1];
	}
	Node Query(i64 L,i64 R,i64 l=1,i64 r=n,i64 id=1){//查询，注意信息如何合并。
		if(L>R){
			return Node{mkp(-inf,-1),mkp(-inf,-1),0};
		}
		if(L<=l&&r<=R){
			return info[id];
		}
		if(mark[id]) PushDown(id);
		if(R<=mid){
			return Query(L,R,lson);
		}else if(mid<L){
			return Query(L,R,rson);
		}else{
			return Query(L,R,lson)+Query(L,R,rson);
		}
	}
}mt;
vector<pii> node[N<<2];
void Update(i64 L,i64 R,i64 D,i64 P,i64 l=0,i64 r=q,i64 id=1){//线段树分治部分，将问题扔到时间轴上。
	if(L<=l&&r<=R){
		node[id].push_back(mkp(D,P));
		return;
	}
	if(L<=mid) Update(L,R,D,P,lson);
	if(mid< R) Update(L,R,D,P,rson);
}
i64 ncost;
struct oper{//存储操作方便回退。
	i64 l,r,v;
};
void solve(i64 l=0,i64 r=q,i64 id=1){//线段树分治，处理问题。
	stack<oper> sv;
	i64 add=0;
	for(auto op:node[id]){
		i64 d=op.fi,p=op.se;
		pii lmx=mt.Query(1,d).maxv,rmx=mt.Query(d,n).lmax;
		if(lmx>=rmx){//走较大的那边。
			if(p+lmx.fi>0){//如果不是正环且不增加流量则不增广。
				ncost+=p+lmx.fi;
				add+=p+lmx.fi;
				mt.EraseV(lmx.se,lmx.fi);
				sv.push(oper{-2,lmx.se,lmx.fi});
				mt.UpdateV(d,-p);
				sv.push(oper{-1,d,-p});
				mt.Modify(lmx.se,d-1,1);
				sv.push(oper{lmx.se,d-1,1});
			}
		}else{
			if(p+rmx.fi>0){
				ncost+=p+rmx.fi;
				add+=p+rmx.fi;
				mt.EraseV(rmx.se,rmx.fi);
				sv.push(oper{-2,rmx.se,rmx.fi});
				mt.UpdateV(d,-p);
				sv.push(oper{-1,d,-p});
				mt.Modify(d,rmx.se-1,-1);
				sv.push(oper{d,rmx.se-1,-1});
			}
		}
	}
	if(l==r){
		ans[l]=ncost;
	}else{
		solve(lson);solve(rson);
	}
	while(sv.size()){//回退操作
		oper i=sv.top();sv.pop();
		if(i.l==-1){
			mt.EraseV(i.r,i.v);
		}else if(i.l==-2){
			mt.UpdateV(i.r,i.v);
		}else{
			mt.Modify(i.l,i.r,-i.v);
		}
	}
	ncost-=add;
}
#undef mid
#undef lson
#undef rson
signed main(){
	n=read();q=read();
	forup(i,1,n) d[i]=read();
	forup(i,1,n) p[i]=read();
	forup(i,1,q){//预处理每个任务影响的区间。
		i64 c=read(),x=read(),y=read();
		Update(pre[c],i-1,d[c],p[c]);
		pre[c]=i;d[c]=x;p[c]=y;
	}
	forup(i,1,n){
		Update(pre[i],q,d[i],p[i]);
	}
	mt.Build();//记得建树。
	solve();
	forup(i,1,q){
		printf("%lld\n",ans[i]);
	}
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

对于插入操作，设插入 $\{t,p\}$：

- 若当前 $1 \sim t$ 有空位，那么就放进去。

- 否则，$1 \sim t$ 是被塞满了的：

  - 首先容易想到的是找到 $1 \sim t$ 中贡献最小的那个工作，若贡献比 $p$ 还小，可以与之替换掉。
 
  - 但是假了，考虑这样一种情况：在 $1 \sim t$ 外有一个更小的值，可以跟 $1 \sim t$ 中的某个工作换一个位置，然后再将这个替换过来的工作替换掉，这样无疑是更优的。
 
  - 考虑如何快速维护这个东西，使用两棵线段树：
 
    - 第一棵线段树维护所有截止时间在区间 $[l,r]$ 的时刻完成的任务的截止时间的最大值。
   
    - 第二棵线段树维护所有截止时间在区间 $[l,r]$ 的时刻完成的任务的贡献的最小值。
   
  - 我们需要找到经过替换能替换到的最远时刻：
 
    - 令 $A_{fi}$ 表示当前 $1 \sim t$ 中截止时间最晚的时间，$A_{se}$ 为 $1 \sim t$ 中截止时间最晚的工作完成的时刻。
   
    - 令 $B_{fi}$ 表示当前 $1 \sim A_{fi}$ 中截止时间最晚的时间，$B_{se}$ 为 $1 \sim A_{fi}$ 中截止时间最晚的工作完成的时刻。
   
    - 那么若 $A_{fi} < B_{fi}$：
   
      - 说明可以将 $A_{se}$ 与 $B_{se}$ 时刻的工作调换一下。
     
      - 因为可以使得 $1 \sim t$ 内的工作的最晚截止时刻更长。
     
    - 然后一直重复交换操作，直到不满足 $A_{fi} < B_{fi}$ 为止。

  - 经过上述的操作，$A_{fi}$ 达到了最大值；令 $C_{fi}$ 表示当前 $1 \sim A_{fi}$ 中工作贡献的最小值，$C_{se}$ 表示完成最小贡献的工作所处的时刻。
 
  - 若 $C_{se} > t$，可以将 $A_{se}$ 与 $C_{se}$ 交换一下。
 
  - 此时的 $C_{fi}$ 就是可以找到替换的最小值，若 $p > C_{fi}$，则可以替换。
 
对于删除操作：

- 若删除的工作我们选择完成了，设在 $t$ 时刻完成：

  - 那么容易想到，可以找到截止时间在 $t \sim T$ 中贡献最大且没有完成的工作，顶替上来即可。
 
  - 但是也假了，考虑这样一种情况，可以将 $t$ 与 $1 \sim t-1$ 时刻的某个工作 $t'$ 交换，使得 $t' \sim T$ 的最大贡献在 $t' \sim t$ 中，则只看 $t \sim T$ 是不优的。
 
  - 我们需要将 $t$ 换到尽可能前面去，考虑二分：
 
    - 若 $1 \sim mid$ 中截止时间最晚的时间是大于等于 $t$ 的，说明 $1 \sim mid$ 中有一个位置可以与 $t$ 换，令 $r=mid-1$；否则 $l=mid+1$。
   
    - 设当前找到的最靠前的时刻为 $t'$，令 $t \gets t'$，然后再在 $1 \sim t$ 的范围内二分。
   
    - 重复二分直到找不到 $1 \sim t-1$ 范围内的点与 $t$ 交换，即不存在 $t'$。
   
  - 此时我们得到了最小的 $t$，找 $t \sim T$ 内贡献最大且没有完成的工作顶替即可。
 
  - 可以使用第三棵线段树：维护所有截止时间在区间 $[l,r]$ 的时刻未完成的任务的贡献的最大值。
 
- 若并没有完成该工作，则直接在第三棵线段树上将这个点的贡献消除即可。

第三棵线段树需要支持一个撤销操作，因为可能有完全一模一样的工作，需要在叶子节点处使用 `multiset` 维护最大值。

时间复杂度为 $O(N \log^3 N)$。

**该做法码量和常数较大，谨慎使用。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=1e5+10,INF=1e18;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
// T1 维护 1 ~ x 时刻中完成的任务的截止时间的最大值
// T2 维护 1 ~ x 时刻中完成的任务的得分的最小值
// T3 维护 1 ~ x 时刻中未完成的任务的得分的最大值 
ll n,q,c,x,y,z,l,r,t,ans;
ll a[N],b[N],X[N],Y[N],Z[N];
map<pi,ll> cnt;
map<iip,ll> F;
class Tree1{
public:
	pi H[N<<2];  //{最大值,位置}
	pi add(pi a,pi b){
		if(a.fi>b.fi)
		  return a;
		return b;
	}
	void pushup(ll k){
		H[k]=add(H[k<<1],H[k<<1|1]);
	}
	void build(ll k,ll l,ll r){
		if(l==r){
			H[k].fi=0;
			H[k].se=l;
			return ;
		}
		ll mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		pushup(k);
	}
	void update(ll k,ll l,ll r,ll i,ll v){
		if(l==i&&i==r){
			H[k].fi=v;
			return ;
		}
		ll mid=(l+r)>>1;
		if(i<=mid)
		  update(k<<1,l,mid,i,v);
		else
		  update(k<<1|1,mid+1,r,i,v);
		pushup(k);
	}
	void del(ll k,ll l,ll r,ll i){
		if(l==i&&i==r){
			H[k].fi=0;
			return ;
		}
		ll mid=(l+r)>>1;
		if(i<=mid)
		  del(k<<1,l,mid,i);
		else
		  del(k<<1|1,mid+1,r,i);
		pushup(k);
	}
	pi query(ll k,ll l,ll r,ll L,ll R){
		if(L>R)
		  return {-INF,0};
		if(l==L&&R==r)
		  return H[k];
		ll mid=(l+r)>>1;
		if(R<=mid)
		  return query(k<<1,l,mid,L,R);
		else if(L>mid)
		  return query(k<<1|1,mid+1,r,L,R);
		else
		  return add(query(k<<1,l,mid,L,mid),query(k<<1|1,mid+1,r,mid+1,R));
	}
	void Swap(ll x,ll y){
		ll xx=query(1,1,n,x,x).fi;
		ll yy=query(1,1,n,y,y).fi;
		update(1,1,n,x,yy);
		update(1,1,n,y,xx);
	} 
}T1;
class Tree2{
public:
	pi H[N<<2];  //{最小值,位置}
	pi add(pi a,pi b){
		if(a.fi<b.fi)
		  return a;
		return b;
	}
	void pushup(ll k){
		H[k]=add(H[k<<1],H[k<<1|1]);
	}
	void build(ll k,ll l,ll r){
		if(l==r){
			H[k].fi=0;
			H[k].se=l;
			X[l]=Y[l]=Z[l]=0;
			return ;
		}
		ll mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		pushup(k);
	}
	void update(ll k,ll l,ll r,ll i,ll x,ll y,ll c){
		if(l==i&&i==r){
			H[k].fi=y;
			X[i]=x,Y[i]=y,Z[i]=c;
			F[{{x,y},c}]=i;
			return ;
		}
		ll mid=(l+r)>>1;
		if(i<=mid)
		  update(k<<1,l,mid,i,x,y,c);
		else
		  update(k<<1|1,mid+1,r,i,x,y,c);
		pushup(k);
	}
	void del(ll k,ll l,ll r,ll i){
		if(l==i&&i==r){
			H[k].fi=0;
			F[{{X[i],Y[i]},Z[i]}]=0;
			X[i]=Y[i]=Z[i]=0;
			return ;
		}
		ll mid=(l+r)>>1;
		if(i<=mid)
		  del(k<<1,l,mid,i);
		else
		  del(k<<1|1,mid+1,r,i);
		pushup(k);
	}
	pi query(ll k,ll l,ll r,ll L,ll R){
		if(L>R)
		  return {INF,0}; 
		if(l==L&&R==r)
		  return H[k];
		ll mid=(l+r)>>1;
		if(R<=mid)
		  return query(k<<1,l,mid,L,R);
		else if(L>mid)
		  return query(k<<1|1,mid+1,r,L,R);
		else
		  return add(query(k<<1,l,mid,L,mid),query(k<<1|1,mid+1,r,mid+1,R));
	}
	void Swap(ll x,ll y){
		ll xx1=X[x],yy1=Y[x],cc1=Z[x],xx2=X[y],yy2=Y[y],cc2=Z[y];
		update(1,1,n,x,xx2,yy2,cc2);
		update(1,1,n,y,xx1,yy1,cc1);
	}
}T2;
class Tree3{
public:
	ll id[N];
	multiset<pii> S[N];
	iip H[N<<2]; // {{x,y},c}
	iip add(iip a,iip b){
		if(a.fi.se>b.fi.se)
		  return a;
		return b;
	}
	void pushup(ll k){
		H[k]=add(H[k<<1],H[k<<1|1]);
	}
	void update(ll k,ll l,ll r,ll x,ll y,ll c){
		if(l==x&&x==r){
			S[x].insert({-y,{-x,-c}});
			auto t=(*S[x].begin());
			H[k]={{-t.se.fi,-t.fi},-t.se.se};
			return ;
		}
		ll mid=(l+r)>>1;
		if(x<=mid)
		  update(k<<1,l,mid,x,y,c);
		else
		  update(k<<1|1,mid+1,r,x,y,c);
		pushup(k);
	}
	void del(ll k,ll l,ll r,ll x,ll y,ll c){
		if(l==x&&x==r){
			S[x].erase({-y,{-x,-c}});
			auto t=(*S[x].begin());
			H[k]={{-t.se.fi,-t.fi},-t.se.se};
			return ;
		}
		ll mid=(l+r)>>1;
		if(x<=mid)
		  del(k<<1,l,mid,x,y,c);
		else
		  del(k<<1|1,mid+1,r,x,y,c);
		pushup(k);
	}
	iip query(ll k,ll l,ll r,ll L,ll R){
		if(l==L&&R==r)
		  return H[k];
		ll mid=(l+r)>>1;
		if(R<=mid)
		  return query(k<<1,l,mid,L,R);
		else if(L>mid)
		  return query(k<<1|1,mid+1,r,L,R);
		else
		  return add(query(k<<1,l,mid,L,mid),query(k<<1|1,mid+1,r,mid+1,R));
	}
}T3;
void insert(ll x,ll y){
	c=++cnt[{x,y}];
	pi A,B;
	pi C;
	while(1){
		A=T1.query(1,1,n,1,x);
		B=T1.query(1,1,n,1,A.fi);
		if(A.fi<B.fi){
			T1.Swap(A.se,B.se);
			T2.Swap(A.se,B.se);
		}
		else
		  break;
	}
	A=T1.query(1,1,n,1,x);
	C=T2.query(1,1,n,1,A.fi);
	if(C.se>x){
		T1.Swap(A.se,C.se);
		T2.Swap(A.se,C.se);
	}
	C=T2.query(1,1,n,1,x);
	if(C.fi<y){
		ans+=y-C.fi;
		if(C.fi){
			T3.update(1,1,n,X[C.se],Y[C.se],Z[C.se]);
			T1.del(1,1,n,C.se);
			T2.del(1,1,n,C.se);
		}
		T1.update(1,1,n,C.se,x);
		T2.update(1,1,n,C.se,x,y,c);
	}
	else
	  T3.update(1,1,n,x,y,c);
}
void del(ll x,ll y){
	c=cnt[{x,y}]--;
	if(F[{{x,y},c}]){
		ans-=y;
		while(1){
			z=F[{{x,y},c}];
			l=1,r=z-1,t=-1;
			while(l<=r){
				ll mid=(l+r)>>1;
				if(T1.query(1,1,n,1,mid).fi>=z){
					t=mid;
					r=mid-1;
				}
				else
				  l=mid+1;
			}
			if(t==-1)
			  break;
			T1.Swap(t,z);
			T2.Swap(t,z);
		}
		z=F[{{x,y},c}];
		T1.del(1,1,n,z);
		T2.del(1,1,n,z);
		iip A=T3.query(1,1,n,z,n);
		if(A.se){
			ans+=A.fi.se;
			T1.update(1,1,n,z,A.fi.fi);
			T2.update(1,1,n,z,A.fi.fi,A.fi.se,A.se);
			T3.del(1,1,n,A.fi.fi,A.fi.se,A.se);
		}
	}
	else
	  T3.del(1,1,n,x,y,c);
}
bool End;
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=1;i<=n;i++)
	  b[i]=read();
	T1.build(1,1,n);
	T2.build(1,1,n);
	for(int i=1;i<=n;i++)
	  insert(a[i],b[i]);
//	write(ans);
//	putchar('\n');
	while(q--){
		x=read();
		del(a[x],b[x]);
		a[x]=read(),b[x]=read();
		insert(a[x],b[x]);
		write(ans);
		putchar('\n');
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC363G] Dynamic Scheduling

这里提供一个暴力但是比较简单的做法。

### 初值

首先发现如果没有修改操作，就是 [P2949](https://www.luogu.com.cn/problem/P2949) 反悔贪心板子。

那就先模拟一遍，求出方案。

```cpp
 std::priority_queue<std::pair<int, int> > qu;
  for (int i = n; i; --i) {
    for (int id : ps[i]) qu.push({p[id], id});
    if (!qu.empty()) {
      auto [w, id] = qu.top();
      qu.pop();
      work[i] = id;
      use[id] = i;
      res += w;
    }
  }

  for (int i = 1; i <= n; ++i)
    if (!use[i]) unu[d[i] / B].insert({{p[i], i}});
```

其中 $work_i$ 表示在 $i$ 时刻工作的是哪一个任务，$use_i$ 表示任务 $i$ 做的使劲按，$unu_{i}$ 是一个 `std::set<std::pair<int, int> >` 的容器，表示时间截至 $t$ 符合 $\lfloor t/B \rfloor=i$ 的若干未完成任务，按价值为第一关键字排序。$B$ 时块长，可以取 $1000$。

### 修改

每次修改相当于一次删除和一次添加。

#### 删除

如果没用用过当前认为就不用管了，否则：

1. 此时多了一个空位，把之前时间做的认为中，**截至时间大于空位时间**的任务放在这个空位上：
    
    ```cpp
    int tim = use[c];
    res -= p[c];
    for (int i = use[c] - 1; i; --i)
      if (work[i] && d[work[i]] >= tim) {
        work[tim] = work[i];
        use[work[i]] = tim;
        tim = i;
      }
    work[tim] = 0;
    ```

2. 找一个**截至时间大于空位时间的、价值最大的任务**。上边让所有任务向后平移的目的就是让这一步的选择尽可能多。所在时间块中可以直接暴力找，之后的整块一定符合时间要求，取价值最大者即可：

    ```cpp
    int id = 0;
    for (int i = n / B; i > tim / B; --i)
      if (!unu[i].empty())
        if (unu[i].rbegin()->first > p[id]) id = unu[i].rbegin()->second;
    for (auto it = unu[tim / B].end(); it != unu[tim / B].begin();) {
      --it;
      if (d[it->second] >= tim) {
        if (it->first > p[id]) id = it->second;
        break;
      }
    }
    if (id) {
      use[id] = tim;
      work[tim] = id;
      res += p[id];
      unu[d[id] / B].erase({p[id], id});
    }
    use[c] = 0;
    ```

#### 加入

3. 钦定选择当前任务：
    
    ```cpp
    d[c] = x, p[c] = y, res += y; 
    ```

4. 找到时间小于当前截至时间的一个空位，或者价值更小的一个任务，将任务填入这个空位，或代替当前任务，同时插入这个任务，表现为交换：

    ```cpp
    for (int i = d[c]; i; --i) {
      if (!work[i]) {
        y = 0;
        use[c] = i;
        std::swap(c, work[i]);
        break;
      } else if (p[work[i]] < y) {
        y = p[work[i]];
        use[c] = i;
        std::swap(c, work[i]);
      }
    }
    res -= y;
    ```

5. 然后删除没插进去的那个任务。

    ```cpp
    if (c) use[c] = 0, unu[d[c] / B].insert({y, c});
    ```

### 时间

上述过程中，`3.`、`5.` 操作是 $O(1)$ 的，`2.` 操作是单次 $O(\frac NB+B)$ 的。

考虑 `1.`、`4.` 操作干了什么。`1.` 遍历了当前任务占用时间之前的时间，`4.` 找到了当前时间前的一个空位，或者是找到了一个低价值的任务。这两个操作都是 $O(n)$ 的，的确可能有办法卡到  $O(n)$，但是本题数据没有精心构造，并且这两个 $O(n)$ 的操作常数较小，卡卡常就过了。

---

