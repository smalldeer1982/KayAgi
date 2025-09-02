# [PumpkinOI Round 1] 种南瓜

## 题目背景

> 秋天到了，又到了收获的季节。

## 题目描述

小 P 要在一段长度为 $n$ 的土地上种魔法南瓜，但是魔法南瓜十分珍贵并且种植它还需要特殊的地质。

所以他对土地进行了 $q$ 次勘测，第 $i$ 次勘测是如下两种结果之一：

`1 l r` : 表示他发现 $[l,r]$ 的土地含有一种全新的元素。

`2 x` : 他发现之前的第 $x$ 次勘测是错误的，所以会删除第 $x$ 次的勘测结果（保证第 $x$ 次操作是之前未被删除的第一种勘测结果）。

魔法南瓜对于地质的要求十分严苛，必须满足对于任意两个区间，它们的关系只能为包含、被包含或不相交。否则，就会因为元素混乱而无法种植魔法南瓜。

请在每次勘测后给出这片土地是否能种植魔法南瓜。

以上的 $[l,r]$ 指的是 $l$ 地块到 $r$ 地块的所有地块。

**形式化题意：**

给你一个标号为 $1 \dots n$ 的数轴，有 $q$ 次操作：

`1 l r` : 表示在数轴 $l$ 放置左括号，$r$ 放置右括号。

`2 x` : 表示删除第 $x$ 次操作放置的括号。

每次操作后，问能否从数轴 $1$ 到 $n$ 的位置依次取出括号（同一位置的括号应先取出左括号再取出右括号，同种括号可以任意顺序取出）形成一个序列。要求这是一个括号序列，并且该括号序列中任意一对匹配的括号对应该是在同一次操作中放置的。

## 说明/提示

**本题开启子任务捆绑/依赖**

对于所有子任务，$1\le n,q\le 2\times10^5$，$1\le op\le 2$，$1\le l_i\le r_i\le n$，$1\le x_i< q$。（$x_i$ 次操作是之前未被删除的操作 $1$)

| 子任务编号 | 分值 |$n\le$ | $q\le$ | 依赖 | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ |$10$ | $10$ | 无 | 无 |
| $2$ | $10$ |$500$ | $500$ | $1$ | 无 |
| $3$ | $4$ |$2\times10^3$ | $2\times10^3$ | $2$ | 无 |
| $4$ | $20$ |$2\times10^5$ | $2\times10^3$ | $3$ | 无 |
| $5$ | $20$ |$5\times10^4$ | $5\times10^4$ | $3$ | 无 |
| $6$ | $15$ |$2\times10^5$ | $2\times10^3$ | 无 | 所有区间都相交 |
| $7$ | $15$ |$2\times10^5$ | $2\times10^5$ | $6$ | 所有区间都相交 |
| $8$ | $15$ |$2\times10^5$ | $2\times10^5$ | $4,5,7$ | 无 |

## 样例 #1

### 输入

```
5 3
1 2 4
1 3 5
2 1
```

### 输出

```
Yes
No
Yes
```

# 题解

## 作者：yizcdl2357 (赞：10)

不到 10min 胡出来了，感觉这题严格小于 T3 啊。

# 题意

一个长为 $n$ 的数轴，每次可以在两个点上分别插入左右括号，或者删除一对之前插入的括号。每次操作结束后你需要判断是否可以重排每格内的括号，使每格中的左括号排在右括号前，且同一次插入的左右括号互相匹配。

# 题解

记 $(i,j)$ 为左括号在 $i$、右括号在 $j$ 的一对括号。

注意到如果两对括号 $(i,j)(i,j')$ 左端点相同，那重排时应该使右括号靠右的那一对括号的左括号靠左（否则不优）。

![](https://cdn.luogu.com.cn/upload/image_hosting/1ahw8sy1.png)

同理，如果两对括号 $(i,j)(i',j)$ 右端点相同，那重排时应该使左括号靠右的那一对括号的右括号靠左。

我们离线询问，把所有 $2\times(\text{操作 1 次数})$ 个括号按以下规则排序：

- 不同格内的括号，靠左的排前面；
- 同一格内的括号，左括号排在右括号前面；
- 同一格内的左括号，对应右括号位置越右的排在越前面；
- 同一格内的右括号，对应左括号位置越右的排在越前面。

这样，问题划归为括号两两不同格的情况。

如果没有删除操作，对一对在时刻 $id$ 输入的括号 $(i,j)$ 赋权值 $val=(j-i+1)\times 10^9+id$，则每两对括号权值不等，且若两对括号满足 $i<i',j'<j$ 则 $val_{i,j}>val_{i',j'}$。

用支持区间取 $\min$、单点查询的线段树维护长为 $n$ 的序列 $t$，每次插入一对括号 $(i,j)$ 时判断 $t_i$ 是否等于 $t_j$，若不等于则输出 `No`，若等于则输出 `Yes` 并将区间 $t_{i\sim j}$ 对 $val_{i,j}$ 取 $\min$ 即可。

有删除用线段树分治转化为只有加入，复杂度 $O(n\log^2 n)$。

# 代码

对括号排序后要 $n\leftarrow 2q$。


```cpp
#include<bits/stdc++.h>
#define N 200000
#define int long long
#define ls id<<1,l,(l+r)>>1
#define rs id<<1|1,((l+r)>>1)+1,r
using namespace std;
struct xds{
	int a[8*N+5];
	int tp,stid[50000005],sta[50000005];
	inline void init(int id,int l,int r)
	{
		a[id]=1e18;
		if(r>l) init(ls),init(rs);
	}
	inline void add(int id,int x)
	{
		tp++;
		stid[tp]=id;
		sta[tp]=a[id];
		a[id]=x;
	}
	inline void ret()
	{
		a[stid[tp]]=sta[tp];
		tp--;
	}
	inline void upd(int id,int l,int r,int x,int y,int z)
	{
		if(r<x||l>y) return;
		if(x<=l&&r<=y){if(a[id]>z)add(id,z);return;}
		upd(ls,x,y,z),upd(rs,x,y,z);
	}
	inline int query(int id,int l,int r,int x)
	{
		if(r<x||l>x) return 2e18;
		if(l==r){return a[id];}
		return min(min(query(ls,x),query(rs,x)),a[id]);
	}
};
xds t;
int n,q,ans[4*N+5];
struct que{
	int tp,l,r,id,eid;
};
que a[N+5],lsh[2*N+5];
vector<que> ev[4*N+5];
inline bool cmp(que x,que y)
{
	if(x.l<y.l) return 1;
	if(x.l>y.l) return 0;
	if(x.r>y.r) return 1;
	if(x.r<y.r) return 0;
	if(x.r<0) return x.id<y.id;
	else return x.id>y.id;
}
inline void ins(int id,int l,int r,que x)
{
	if(r<x.id||l>x.eid) return;
	if(x.id<=l&&r<=x.eid){ev[id].push_back(x);return;}
	ins(ls,x),ins(rs,x);
}
inline void solve(int id,int l,int r)
{
	int _=t.tp;
	ans[id]=1;
	for(que i:ev[id])
	{
		if(t.query(1,1,2*q,i.l)!=t.query(1,1,2*q,i.r))
			{ans[id]=0;break;}
		t.upd(1,1,2*q,i.l,i.r,(i.r-i.l+1)*1e9+i.id);
	}
	if(r>l) solve(ls),solve(rs);
	while(t.tp>_) t.ret();
}
inline void getans(int id,int l,int r,int now)
{
	now&=ans[id];
	if(l==r){if(now==0)cout<<"No\n";else cout<<"Yes\n";return;}
	getans(ls,now),getans(rs,now);
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1,x;i<=q;i++) 
	{
		cin>>a[i].tp;
		if(a[i].tp==1)
			cin>>a[i].l>>a[i].r,a[i].id=i;
		else cin>>x,a[x].eid=i;
	}
	for(int i=1;i<=q;i++)
	{
		lsh[i].tp=1;
		lsh[i].l=a[i].l,
		lsh[i].r=a[i].r,
		lsh[i].id=a[i].id,
		lsh[q+i].tp=1;
		lsh[q+i].l=a[i].r,
		lsh[q+i].r=-1e9+a[i].l,
		lsh[q+i].id=a[i].id;
	}
	sort(lsh+1,lsh+1+2*q,cmp);
	for(int i=1;i<=2*q;i++)
	{
		if(lsh[i].tp==0) continue;
		int now=lsh[i].id;
		if(lsh[i].r>=0) a[now].l=i;
		else a[now].r=i;
	}
//	for(int i=1;i<=q;i++) cout<<a[i].l<<' '<<a[i].r<<' '<<a[i].id<<' '<<a[i].eid<<'\n';
	for(int i=1;i<=q;i++)
	{
		if(a[i].tp==2) continue;
		if(a[i].eid==0) a[i].eid=q;
		else a[i].eid--;
		ins(1,1,q,a[i]);
	}
	t.init(1,1,2*q);
	solve(1,1,q);
	getans(1,1,q,1);
	return 0;
}/*8 2
1 1 4
1 4 4
*/
```


---

想借这篇题解总结一下备战省选的第一场比赛。

- 细节吃完了。A 一开始没看到 $m$ 的限制被控一小会；B 先想了一个假做法只有 60pts，不能处理重根；后来才想到生成函数。D 不知道如何处理多个括号在同一格的情况。
- - 以后思考一道题的同时想这个做法暂时不好处理的细节，敲代码前在草稿纸上把这些细节玩清楚、最好能把一组有一定强度的小样例玩清楚了再开写。
- 调试时间长于敲代码。调不出来的原因（如果不是细节的话）主要是想不到 hack 数据。
- - 在省选时这种情况多半可以通过大样例解决。
  - 我在这场比赛中的处理方法同样值得借鉴：把比较可能出错的部分替换成暴力，然后逐块换回原来的代码，这样可以精确定位到哪一个代码块有问题。

希望和我一样手跟不上脑子的 OIer 能有所收获，也祝各位省选 rp++。

---

## 作者：Mr_Az (赞：5)

# PumpkinOI Round 1 T4 种南瓜

验题人题解。

标签：**线段树分治**

### Solution:

考虑没有删除操作时如何维护答案，即每次加入一个区间 $[l,r]$。不合法的情况当且仅当加入的时候，之前存在有区间与当前 $[l,r]$ 有交且不包含，这是一个经典的**二维偏序**问题。只需要用两颗线段树分别维护以此处为右端点最大的左端点和以此处为左端点的最小右端点判断即可。支持区间取 $\max/\min$，单点查询即可。

考虑加入删除操作，我们会发现每一个加区间操作影响的是一段时间区间，考虑**线段树分治**。

我们对时间这一维建一颗线段树，树的每一个节点存储的信息是在**这个时间区间内的操作区间**。求答案只需要遍历整颗线段树，维护两颗线段树，每次进入一个节点的时候把所有区间全部加进去，直到叶子结点。这样我们就可以保证在走到叶子结点的时候，两颗线段树里全都是在这一段时间存在的操作区间的影响。

如果此时仍然没有出现矛盾，则在这个时间时刻是合法的。但如果在加区间的过程中出现了不合法的情况，那么这一个时间时刻是不合法的。对应的输出即可。

一个小优化，如果在走到一个节点（维护的时间区间是 $[l,r]$）时已经出现了矛盾，则说明 $[l,r]$ 这段时间内的所有操作**全部都是不合法的**。此时直接跳出即可。

对于离开这个节点的撤销操作，只需要维护一个栈存储线段树内**哪些点被修改了以及其原来的值**，离开的时候回溯成进入该节点时的状态即可。

#### 时间复杂度

遍历线段树复杂度 $O(n\log n)$，每一个节点内用线段树判断合法复杂度 $O(\log n)$，则总时间复杂度为 $O(n \log^2 n)$。

### Code:

```cpp
int n,m,q;
int pos[N];
struct node{int l,r,L,R;};
vector<node> a;
#define mid (l+r>>1)
namespace mx{//维护区间最大值 支持区间取 max，单点查询
	vector<pii> cl;
	struct tree{
		int val;
		#define val(p) t[p].val
	}t[N*4];
	inline void clear(int p){
		while(cl.size()>p){
			auto [x,y]=cl[cl.size()-1];cl.pop_back();
			val(x)=y;
		}
	}//撤销操作
	inline void cg(int p,int k){if(val(p)<k) cl.pb({p,val(p)}),val(p)=k;}
	inline void spread(int p){
		if(val(p)){
			cg(ls,val(p)),cg(rs,val(p));
			cl.pb({p,val(p)}),val(p)=0;
		}
	}
	void change(int p,int l,int r,int L,int R,int k){
		if(L<=l&&r<=R){cg(p,k);return ;}
		spread(p);
		if(L<=mid) change(ls,l,mid,L,R,k);
		if(R>mid)  change(rs,mid+1,r,L,R,k);
		return ;
	}
	int ask(int p,int l,int r,int pos){
		if(l==r&&l==pos) return val(p);
		int res=0;
		spread(p);
		if(pos<=mid) res=ask(ls,l,mid,pos);
		else res=max(res,ask(rs,mid+1,r,pos));
		return res;
	}
	#undef val
}
namespace mn{//维护区间最小值 支持区间取 min，单点查询
	vector<pii> cl;
	struct tree{
		int val;
		#define val(p) t[p].val
	}t[N*4];
	inline void build(int p,int l,int r){
		val(p)=INF;
		if(l==r) return ;
		build(ls,l,mid);build(rs,mid+1,r);
	}
	inline void clear(int p){
		while(cl.size()>p){
			auto [x,y]=cl[cl.size()-1];cl.pop_back();
			val(x)=y;
		}
	}//撤销操作
	inline void cg(int p,int k){if(val(p)>k) cl.pb({p,val(p)}),val(p)=k;}
	inline void spread(int p){
		if(val(p)!=INF){
			cg(ls,val(p)),cg(rs,val(p));
			cl.pb({p,val(p)}),val(p)=INF;
		}
	}
	void change(int p,int l,int r,int L,int R,int k){
		if(L<=l&&r<=R){cg(p,k);return ;}
		spread(p);
		if(L<=mid) change(ls,l,mid,L,R,k);
		if(R>mid)  change(rs,mid+1,r,L,R,k);
		return ;
	}
	int ask(int p,int l,int r,int pos){
		if(l==r&&l==pos) return val(p);
		int res=INF;
		spread(p);
		if(pos<=mid) res=ask(ls,l,mid,pos);
		else res=min(res,ask(rs,mid+1,r,pos));
		return res;
	}
	#undef val
}
struct tree{
	vector<pii> a;
	#define sq(p) t[p].a
}t[N*4];
void add(int p,int l,int r,int L,int R,pii a){
	if(L<=l&&r<=R){sq(p).pb(a);return ;}
	if(L<=mid) add(ls,l,mid,L,R,a);
	if(R>mid)  add(rs,mid+1,r,L,R,a);
	return ;
}	
void ask(int p,int l,int r){
	int mx1=mx::cl.size(),mn1=mn::cl.size();//初始栈的状态
	for(auto [ll,rr]:sq(p)){
		if(ll!=rr){
			int t1=mx::ask(1,1,n,rr),t2=mn::ask(1,1,n,ll);
			if(ll<t1||rr>t2){
				for(rint i=l;i<=r;i++) puts("No");
				goto clean;
			}//在其中某一处不合法的时候，直接对于 [l,r] 全部输出 No
			mx::change(1,1,n,ll,rr-1,ll);
			mn::change(1,1,n,ll+1,rr,rr);
		}
	}
	if(l==r) puts("Yes");//到叶子结点都合法，则输出 Yes
	else{
		ask(ls,l,mid);
		ask(rs,mid+1,r);
	}
	clean:
	mx::clear(mx1);mn::clear(mn1);//回溯
}
#undef sq
#undef mid
signed main(){
	read(n,q);
	for(rint i=1,op,l,r;i<=q;i++){
		read(op);
		if(op==1){
			read(l,r);
			a.pb({l,r,i,q});
			pos[i]=m;m++;
		}
		else{
			read(l);
			a[pos[l]].R=i-1;
		}
	}
	for(auto [l,r,L,R]:a) add(1,1,q,L,R,{l,r});//存在时间区间 [L,R]，操作区间 [l,r]
	mn::build(1,1,n);//最小值线段树初始化为 inf
	ask(1,1,q);
	return 0;
}
```

---

## 作者：┭┮﹏┭┮ (赞：4)

很板的东西。

首先考虑没有删除，我们可以每次加入一个区间判断是否与当前区间**有交且不包含**。

对于两个区间 $[l1,r1],[l2,r2]$，考虑其满足**有交但不包含**时的条件，首先分类讨论。

- 若 $l1 < l2$，则只有满足 $r1 \in [l2,r2)$ 时**有交但不包含**。
- 若 $r1 > r2$，则只有满足 $l1 \in (l2,r2]$ 时**有交但不包含**。

可以画图理解。

则对于新加的区间 $[l2,r2]$，对于第一种情况，我们只需判断所有右端点在 $[l2,r2)$ 的区间的 $l$ 端点是否小于 $l2$，可以用线段树维护最小值。

类似的对于第二种情况，可以用线段树维护所有左端点为 $l$ 的最大右端点。

然后考虑删除，可以直接线段树分治，具体的将每个区间的存在时间 $[l,r]$ 拆分成 $\log{n}$ 个线段树上的区间，最后我们 dfs 一遍，每当进入 $p$ 节点，将节点上的所有修改加入，这样我们到达叶子节点即可得到每个时间的答案，最后当我们退出节点时，要**撤销**我们所修改的东西。

总复杂度 $\mathcal{O}(n\log^2{n})$。

[代码](https://www.luogu.com.cn/paste/381jdqbl)

---

## 作者：ini2015_____ (赞：1)

赛后来补题了 qwq

### 题意简述
给定一个空的数轴，从 $1\sim n$ 标号，有 $m$ 个操作：

1. ```1 l r``` 在 $l,r$ 处分别放置一个**独一无二**的括号对
2. ```2 x``` 撤回第 $x$ 次操作

每次操作完后查询序列是否可以构成合法括号序列（在同一位置的同种括号可看成任意顺序，否则左括号在前）

### Subtask 1
指数级随便乱搞就过了

### Subtask 2
考虑 $O(q^3)$ 的做法 。

题目里查询的问题很复杂，我们考虑化简这个问题。

手玩几个样例会发现其等价条件：

对于任意两对括号对 $(l_1,r_1),(l_2,r_2)$ ，满足集合 $[l_1,r_1],[l_2,r_2]$ 要么是包含关系，要么是不相交关系。

证明如下：

若该条件不满足，假设 $l_2 \le r_1$ 那么第二组的左括号会先匹配上第一组的右括号，得到答案为 "No" 。

若该条件满足，则可以采用归纳法证明答案为 "Yes" ，此处省略。

按照上述条件直接模拟即可

### Subtask 3~4
发现上述做法实在是太唐了，每次加入/删除一个区间时 $O(q)$ 维护，就做到 $O(q^2)$ 了
### Subtask 5~8
发现插入一个区间是好做的：

首先，对于两对左括号重合的括号对，他们之间的顺序是明确的：右括号靠右的左括号放在左面，靠左的放在右边。

说起来很抽象，实际画一下就很显然。

那么考虑按照上述顺序排序，每对括号随机赋一个值，每次插入时检查区间内的异或，这个异或和可以用树状数组或线段树维护，异或和为 $0$ 说明合法，否则说明不合法，后面无论怎么插入都不对。

既然这样，考虑线段树分治，这样只用插入，不用删除，就做完了。

coding:

鸽，有时间再补

---

## 作者：qczrz6v4nhp6u (赞：1)

### Solution

显然一个时刻合法的充要是满足 $l_1<l_2\le r_1<r_2$ 的区间对 $([l_1,r_1],[l_2,r_2])$ 为 $0$。对时间轴差分一下，将加入看作加入一个权值为 $1$ 的区间，删除看作加入一个权值为 $-1$ 的区间，那么就只剩加入操作了。

设一个区间 $[l,r]$ 的权值为 $v$，加入的时刻为 $t$，那么一个满足条件的区间对 $([l_1,r_1],[l_2,r_2])$ 会对答案的差分数组的 $\max(t_1,t_2)$ 处产生 $v_1\times v_2$ 的贡献。分讨一下 $t_1,t_2$ 的大小，剩下的就是个三维数点，cdq 即可。

### Code

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=2e5+5,mod=998244353;
int n,q;
struct node{
	int l,r,v,t;
	node(){l=r=v=t=0;}
	node(int _l,int _r,int _v,int _t){l=_l,r=_r,v=_v,t=_t;}
	bool operator <(const node &_)const{return t<_.t;}
};
node a[N],tmp[N];
ll ans[N];
int c[N];
inline void upd(int x,int v){
	for(;x<=n;x+=x&-x)c[x]+=v;
}
inline int ask(int x){
	int res=0;
	for(;x;x-=x&-x)res+=c[x];
	return res;
}
inline void clear(int x){
	for(;x<=n;x+=x&-x)
		if(c[x])c[x]=0;
		else break;
}
void solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid){
		while(j<=r&&a[i].l>=a[j].l)
			ans[a[j].t]+=a[j].v*(ask(a[j].r-1)-ask(a[j].l-1)),tmp[k++]=a[j++];
		upd(a[i].r,a[i].v),tmp[k++]=a[i++];
	}
	while(j<=r)
		ans[a[j].t]+=a[j].v*(ask(a[j].r-1)-ask(a[j].l-1)),tmp[k++]=a[j++];
	for(i=l;i<=mid;i++)clear(a[i].r);
	for(k=l;k<=r;k++)a[k]=tmp[k];
}
void work(){
	sort(a+1,a+q+1);
	solve(1,q);
	for(int i=1;i<=q;i++)
		a[i].l=n-a[i].l+1,a[i].r=n-a[i].r+1,swap(a[i].l,a[i].r);
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		int op;cin>>op;
		if(op==1){
			int l,r;cin>>l>>r;
			a[i]=node(l,r,1,i);
		}
		else{
			int x;cin>>x;
			a[i]=node(a[x].l,a[x].r,-1,i);
		}
	}
	work();
	work();
	for(int i=1;i<=q;i++)
		cout<<((ans[i]+=ans[i-1])?"No":"Yes")<<'\n';
	return 0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：1)

转化成每次可以增删一条线段，判断是否满足每条线段都包含或不包含或不相交。

每条线段会出现和消失，想到线段树分治。现在只需要判断每次加入的线段是否满足要求即可。先处理被此线段完全包含的线段。建一颗用于查区间异或值的线段树，每次加入一条线段时将这条线段左右端点的位置都异或上一个随机值。如果 $l,r$ 内的所有线段都被 $l,r$ 包含，那么区间 $[l,r]$ 内数的异或值为 0。


发现这样无法处理到与此线段共用一个端点且完全包含此线段的线段。那么在每个点处开一棵线段树，那么合法的条件就是 $[l,r]$ 中异或值异或 $l$ 处线段树 $[r+1,n]$ 内的异或值再异或 $r$ 处线段树 $[1,l-1]$ 内的异或值为 0。复杂度 $O(n\log n\log q)$。

代码。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+100;
int n,m;
mt19937 rd(time(0));
struct seg
{
	int l,r,val;
}u[N];
vector<seg> s[N*4];
#define ll (x<<1)
#define rr (x<<1|1)
#define mid ((l+r)>>1)
namespace sg
{
	int t[N*4];
	inline void insert(int pos,int l,int r,int x,int val)
	{
		t[x]^=val;
		if(l==r)return;
		if(pos<=mid)insert(pos,l,mid,ll,val);
		else insert(pos,mid+1,r,rr,val);
	}
	inline int get(int l1,int r1,int l,int r,int x)
	{
		if(l>=l1&&r<=r1)return t[x];
		int res=0;
		if(l1<=mid)res^=get(l1,r1,l,mid,ll);
		if(r1>mid)res^=get(l1,r1,mid+1,r,rr);
		return res;
	}
}
using namespace sg;
inline void add(int l1,int r1,int l,int r,int x,seg v)
{
	if(l>=l1&&r<=r1){s[x].push_back(v);return;}
	if(l1<=mid)add(l1,r1,l,mid,ll,v);
	if(r1>mid)add(l1,r1,mid+1,r,rr,v);
}
map<pair<int,int>,int> mp;
struct node
{
	int x;
	node *ls,*rs;
	node(){x=0;ls=rs=0;}
	inline void insert(int pos,int l,int r,int val)
	{
		x^=val;
		if(l==r)return;
		if(pos<=mid)(ls?ls:ls=new node)->insert(pos,l,mid,val);
		else (rs?rs:rs=new node)->insert(pos,mid+1,r,val);
	}
	inline int get(int l1,int r1,int l,int r)
	{
		if(l1>r1)return 0;
		if(l>=l1&&r<=r1)return x;
		int res=0;
		if(ls&&l1<=mid)res^=ls->get(l1,r1,l,mid);
		if(rs&&r1>mid)res^=rs->get(l1,r1,mid+1,r);
		return res;
	}
}tl[N],tr[N];
inline void work(int l,int r,int x,bool ok)
{
	bool tmp=ok;
	if(tmp)
	for(auto i:s[x])
	{
		if(get(i.l,i.r,1,n,1)^tl[i.l].get(i.r+1,n,1,n)^tr[i.r].get(1,i.l-1,1,n))ok=0;
		insert(i.l,1,n,1,i.val);
		insert(i.r,1,n,1,i.val);
		tl[i.l].insert(i.r,1,n,i.val);
		tr[i.r].insert(i.l,1,n,i.val);
	}
	if(l==r)
		cout<<(ok?"Yes\n":"No\n");
	else work(l,mid,ll,ok),work(mid+1,r,rr,ok);
	if(tmp)
	for(auto i:s[x])
	{
		insert(i.l,1,n,1,i.val);
		insert(i.r,1,n,1,i.val);
		tl[i.l].insert(i.r,1,n,i.val);
		tr[i.r].insert(i.l,1,n,i.val);
	}
}
#undef ll
#undef rr
#undef mid
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int op,x,y;
	set<int> tmp;
	for(int i=1;i<=m;i++)
	{
		cin>>op;
		if(op==1)cin>>x>>y,tmp.insert(i),u[i]={x,y,rd()};
		else cin>>x,tmp.erase(x),add(x,i-1,1,m,1,u[x]);
	}
	for(auto i:tmp)add(i,m,1,m,1,u[i]);
	work(1,m,1,1);
}
```

---

## 作者：xxr___ (赞：1)

### **撤回操作要倒着撤！**

如果没有操作 $2$，那么实际上就是裸的二维数点问题。

设当前这个线段是 $[l,r]$ 如果有线段 $[l',r']$ 和它有交，无非是两种情况：
1. 当 $l' < l$ 时，需要满足 $l\leq r'< r$。
2. 当 $r' > r$ 时，需要满足 $l < l' \leq r$。

所以，如果当前线段和之前的线段有交集，那么必定满足原来线段中右端点是 $[l,r)$ 范围内，左端点小于 $l$。或者是左端点是 $(l,r]$ 范围内，且右端点大于 $r$。

这两者可以用线段树维护区间最小值，最大值分别实现。

那么如果带修改，且不强制在线。我们可以考虑把询问离线下来，做线段树分治，这样只有加的操作和撤回操作。

加操作和上述相同，撤回操作可以用一个栈实现，注意我开头所说，要从后往前倒着撤回，因为最后的是递归刚进来的。

撤回操作可以使用 `vector` 实现，具体实现请看代码。

代码：
```cpp
#include<iostream>
#include<utility>
#include<vector>

#define pii std::pair<int,int>

inline void rd(int & x){
	x = 0;char c = getchar();
	while(!(c >= '0' && c <= '9')) c = getchar();
	while(c >= '0' && c <= '9'){
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar(); 
	}
}

const int N = 2e5 + 5;
int n,q,mn[N << 2],mx[N << 2];
int op[N],l[N],r[N],nxt[N];
std::vector<pii> line[N << 2];
bool is[N << 2];
inline int ls(int x){return x << 1;}
inline int rs(int x){return x << 1 | 1;}

void build(int x,int l,int r){
	mn[x] = n + 1,mx[x] = 0;
	if(l == r){
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(x),l,mid);
	build(rs(x),mid + 1,r);
}
void add_lines(int u,int l,int r,int ql,int qr,pii li){
	if(ql <= l && qr >= r){
		line[u].push_back(li);
		return;
	}
	int mid = (l + r) >> 1;
	if(ql <= mid) add_lines(ls(u),l,mid,ql,qr,li);
	if(qr > mid) add_lines(rs(u),mid + 1,r,ql,qr,li);
}
int query_min(int u,int l,int r,int ql,int qr){
	if(ql > qr) return n + 1;
	if(qr < l || ql > r) return n + 1;
	if(ql <= l && qr >= r) return mn[u];
	int mid = (l + r) >> 1;
	return std::min(query_min(ls(u),l,mid,ql,qr),query_min(rs(u),mid + 1,r,ql,qr));
}
int query_max(int u,int l,int r,int ql,int qr){
	if(ql > qr) return 0;
	if(qr < l || ql > r) return 0;
	if(ql <= l && qr >= r) return mx[u];
	int mid = (l + r) >> 1;
	return std::max(query_max(ls(u),l,mid,ql,qr),query_max(rs(u),mid + 1,r,ql,qr));
}
void upd_min(int u,int l,int r,int x,int k,std::vector<pii> &s){
	s.push_back({u,mn[u]});
	mn[u] = std::min(mn[u],k);
	if(l == r){
		return;
	}
	int mid = (l + r) >> 1;
	(x <= mid ? upd_min(ls(u),l,mid,x,k,s) : upd_min(rs(u),mid + 1,r,x,k,s));
}
void upd_max(int u,int l,int r,int x,int k,std::vector<pii> &s){
	s.push_back({u,mx[u]});
	mx[u] = std::max(mx[u],k);
	if(l == r){
		return;
	}
	int mid = (l + r) >> 1;
	(x <= mid ? upd_max(ls(u),l,mid,x,k,s) : upd_max(rs(u),mid + 1,r,x,k,s));
}
void recover(std::vector<pii> s1,std::vector<pii> s2){
	for(int j = s1.size() - 1;~j; --j){
		mn[s1[j].first] = s1[j].second;
	}
	for(int j = s2.size() - 1;~j; --j){
		mx[s2[j].first] = s2[j].second;
	}
}
void dfs(int u,int l,int r){
	std::vector<pii> s1,s2;
	s1.clear(),s2.clear();
	//s1,s2存的是需要回溯的时候删除的线段
	if(!is[u]){
		for(pii &it : line[u]){
			//[l1,r1] 和 [l2,r2] 有交集且不重当且仅当
			//l1 < l2 且 r2 > r1
			//也就是此时 r1 满足 l2 <= r1 < r2 的
			//查询一下右端点在 [l2,r2) 中 l1 的最小值即可
			int l2 = it.first,r2 = it.second;
			if(l2 < r2){
				if(query_min(1,1,n,l2,r2 - 1) < l2){
					is[u] = true;
					break;
				}
				if(query_max(1,1,n,l2 + 1,r2) > r2){
					is[u] = true;
					break;
				}
			}
			//否则，就是 r1 > r2 的话
			//需要满足 l2 < l1 <= r2
			//那就是查询左端点在 (l2,r2] 中 右端点的最大值 
			upd_min(1,1,n,r2,l2,s1);
			upd_max(1,1,n,l2,r2,s2); 
		}
	}
//	std::cout << u << ' ' << is[u] << '\n';
	if(l == r){
		recover(s1,s2);
		std::cout << (is[u] ? "No\n" : "Yes\n" );
		return;
	}
	is[ls(u)] = is[rs(u)] = is[u];
	int mid = (l + r) >> 1;
	dfs(ls(u),l,mid); dfs(rs(u),mid + 1,r);
	recover(s1,s2);
}
int main(){
	rd( n );rd( q );
	std::fill(is + 1,is + q + 1,false);
	for(int i = 1;i <= q; ++i){
		rd( op[i] );rd( l[i] );
		nxt[i] = q;
		if(op[i] == 1) rd( r[i] );
		else nxt[l[i]] = i - 1;
	}
	build(1,1,n);
	for(int i = 1;i <= q; ++i){
		if(op[i] == 1){
			add_lines(1,1,q,i,nxt[i],std::make_pair(l[i],r[i]));
		}
	}
	dfs(1,1,q);
	return 0;
}
```

---

## 作者：yzq_yzq (赞：1)

题意很简单，每次加入线段或者删除一条已有线段。

假如只有加入是好做的，我们每次加入 $[l,r]$ ，要判断是否有 $[L,R]$ 满足 $L < l \leq R < r$ 或者 $l < L \leq r < R$ ，对 $R$ 为下标维护区间 $L$ 的最小值，对 $L$ 为下标维护区间 $R$ 最大值，两颗线段树即可。

有删除加上线段树分治即可，复杂度是 $q\log q\log n$ 的。

至于回撤操作，用栈序撤销的线段树即可，写 zkw 的话常数极小，不怕被卡常。代码也很简单。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i <= y; ++i)
#define drep(i, x, y) for (int i = x; i >= y; --i)
#define ll long long
#define pb push_back
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 200020;
int n, q, lst[N], l[N], r[N], op[N], stk[N], tp; vector<int> T[N << 2];
struct zkw {
	int t[N << 2], m, tp; pair<int, int> stk[N << 3]; // Min SegTree
	inline void build() { m = 1, memset(t, 0x3f, sizeof t); while(m <= n) m <<= 1; }
	inline void pushup(int p) { t[p] = min(t[p << 1], t[p << 1 | 1]); }
	inline void up(int p) { while(p >>= 1) pushup(p); }
	inline void upd(int x, int y) { x += m, stk[++tp] = {x, t[x]}, t[x] = min(t[x], y), up(x); }
	inline void undo(int lst) { while(tp > lst) t[stk[tp].first] = stk[tp].second, up(stk[tp].first), --tp; }
	inline int qry(int l, int r) { int res = 1e9; if(l > r) return res;
		for(l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) res = min(res, t[l ^ 1]); if(r & 1) res = min(res, t[r ^ 1]);
		} return res;
	}
} t1, t2;
inline void insert(int ql, int qr, int x, int p = 1, int l = 1, int r = q) {
	if(qr < l || r < ql) return; if(ql <= l && r <= qr) return void(T[p].pb(x));
	int mid = (l + r) >> 1; insert(ql, qr, x, p << 1, l, mid);
	insert(ql, qr, x, p << 1 | 1, mid + 1, r); }
inline void Ins(int l, int r) {
	++tp, stk[tp] = stk[tp - 1];
	if(t1.qry(l, r - 1) < l) stk[tp] = 1;
	if(-t2.qry(l + 1, r) > r) stk[tp] = 1;
	t1.upd(r, l), t2.upd(l, -r);
}
inline void solve(int p = 1, int l = 1, int r = q) {
	int lst = tp; for(int x : T[p]) Ins(::l[x], ::r[x]);
	if(l == r) cout << (stk[tp] ? "No\n" : "Yes\n");
	else { int mid = (l + r) >> 1;
		solve(p << 1, l, mid), solve(p << 1 | 1, mid + 1, r);
	} t1.undo(lst), t2.undo(lst), tp = lst;
}
int main() {
	IOS; cin >> n >> q, t1.build(), t2.build();
	rep(i, 1, q) {
		cin >> op[i];
		if(op[i] == 1) cin >> l[i] >> r[i];
		else cin >> l[i], lst[l[i]] = i; 
	}
	rep(i, 1, q) if(op[i] == 1) insert(i, (!lst[i] ? q : lst[i] - 1), i);
	solve(); return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑只插入的话怎么做。

首先若前面已经有不合法的地方，显然还是不合法。

否则设我要插入 $[l, r]$，需要判断前面是否有线段与其相交。

容易发现只有 $l' \in [l + 1, r], r' > r$ 或者 $r' \in [l, r - 1], l' < l$ 时才会相交且不包含且不被包含。

故考虑维护 $t_{1, i}, t_{2, i}$ 分别表示当 $l_j = i$ 时最大的 $r_j$，当 $r_j = i$ 时最大的 $l_j$。

若存在某区间与 $[l, r]$ 有交且不包含且不被包含，当且仅当：

$$[\max_{i = l + 1}^r t_{1, i} > r] \vee [\min_{i = l}^{r - 1} t_{2, i} < l]$$

使用两个线段树维护区间最大值，单点修改即可。

但是现在有删除操作，看起来很不好做；注意到上面是单点修改，很容易进行撤销，故考虑线段树分治，转化为只插入，支持撤销。

时间复杂度为 $O(N \log N \log Q)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define mkp(x, y) make_pair(x, y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 10; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	vector<pair<int, int>> V;
}X[N << 2];
int n, q, op, x, cnt;
int l[N], r[N], id[N], st[N], ed[N], t1[N], t2[N];
bool ans[N];
class Tree{
public:
	struct Node{
		int l, r;
		int Max, Min;
	}X[N << 2];
	inline void pushup(int k){
		X[k].Max = max(X[k << 1].Max, X[k << 1 | 1].Max);
		X[k].Min = min(X[k << 1].Min, X[k << 1 | 1].Min);
	}
	inline void build(int k, int l, int r, int* a){
		X[k].l = l, X[k].r = r;
		if(l == r){
			X[k].Max = X[k].Min = a[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid, a);
		build(k << 1 | 1, mid + 1, r, a);
		pushup(k);
	}
	inline void update(int k, int i, int v){
		if(X[k].l == i && i == X[k].r){
			X[k].Max = X[k].Min = v;
			return ;
		}
		int mid = (X[k].l + X[k].r) >> 1;
		if(i <= mid)
		  update(k << 1, i, v);
		else
		  update(k << 1 | 1, i, v);
		pushup(k);
	}
	inline int queryMax(int k, int l, int r){
		if(X[k].l == l && r == X[k].r)
		  return X[k].Max;
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return queryMax(k << 1, l, r);
		else if(l > mid)
		  return queryMax(k << 1 | 1, l, r);
		else
		  return max(queryMax(k << 1, l, mid), queryMax(k << 1 | 1, mid + 1, r)); 
	}
	inline int queryMin(int k, int l, int r){
		if(X[k].l == l && r == X[k].r)
		  return X[k].Min;
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return queryMin(k << 1, l, r);
		else if(l > mid)
		  return queryMin(k << 1 | 1, l, r);
		else
		  return min(queryMin(k << 1, l, mid), queryMin(k << 1 | 1, mid + 1, r)); 
	}
}T1, T2;
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r)
	  return ;
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}
inline void update(int k, int l, int r, pair<int, int> v){
	if(X[k].l == l && r == X[k].r){
		X[k].V.push_back(v);
		return ;
	}
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v);
	else{
		update(k << 1, l, mid, v);
		update(k << 1 | 1, mid + 1, r, v);
	}
}
inline void Back(stack<pair<int, int>>&S1, stack<pair<int, int>>&S2){
	while(!S1.empty()){
		auto h = S1.top();
		S1.pop();
		t1[h.fi] = h.se;
		T1.update(1, h.fi, h.se);
	}
	while(!S2.empty()){
		auto h = S2.top();
		S2.pop();
		t2[h.fi] = h.se;
		T2.update(1, h.fi, h.se);
	}	
}
inline void dfs(int k){
	stack<pair<int, int>> S1, S2;
	for(auto t : X[k].V){
		int l = t.fi, r = t.se;
		if(r - l + 1 == 1)
		  continue;
		if(T1.queryMax(1, l + 1, r) > r){
			Back(S1, S2);
			return ;
		}
		if(T2.queryMin(1, l, r - 1) < l){
			Back(S1, S2);		
			return ;
		}
		if(r > t1[l]){
			S1.push({l, t1[l]});
			t1[l] = r;
			T1.update(1, l, r);
		}
		if(l < t2[r]){
			S2.push({r, t2[r]});
			t2[r] = l;
			T2.update(1, r, l);
		}
	}
	if(X[k].l == X[k].r){
		ans[X[k].l] = 1;
		Back(S1, S2);
		return ;
	}
	dfs(k << 1);
	dfs(k << 1 | 1);
	Back(S1, S2);
}
int main(){
	n = read(), q = read();
	for(int i = 1; i <= q; ++i){
		op = read();
		if(op == 1){
			++cnt;
			l[cnt] = read(), r[cnt] = read();
			st[cnt] = i;
			id[i] = cnt;
		}
		else{
			x = read();
			ed[id[x]] = i - 1;
		}
	}
	build(1, 1, q);
	for(int i = 1; i <= cnt; ++i){
		if(!ed[i])
		  ed[i] = q;
		update(1, st[i], ed[i], mkp(l[i], r[i]));
	}
	for(int i = 1; i <= n; ++i){
		t1[i] = 0;
		t2[i] = n + 1;
	}
	T1.build(1, 1, n, t1);
	T2.build(1, 1, n, t2);
	dfs(1);
	for(int i = 1; i <= q; ++i)
	  puts(ans[i] ? "Yes" : "No");
	return 0;
}
```

---

