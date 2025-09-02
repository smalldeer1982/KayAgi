# [COCI 2015/2016 #3] NEKAMELEONI

## 题目背景

> 「嘿，亲爱的！我要去给 $11$ 月 $28$ 日的 Croatian Open Competition In Informatics 出 T5。」      
> 「去吧，去吧……」 　　                       
> 「…」
> _____
> 「这题怎么样？」          
> 「唔……这太难了……会把那些小可爱难住的，换个简单些的吧……」           
> 于是可爱的出题人便出了这道题。
> ______
> 嘿！我会 $O(n^6)$ 的做法，$ n$ 的范围是什么？？

## 题目描述

给你一个 $n$ 个元素的数组。你需要处理 $q$ 个查询。

- 第一种查询需要你将数组中的第 $p$ 个数字改为 $v$。
- 第二种查询需要你确定当前数组中最短的连续子数组的长度，这个子数组必须要包含从 $1$ 到 $k$ 的所有数字。


## 说明/提示

#### 数据范围及约定
- 对于 $30\%$ 的数据，$1\le n, m \le 5 \times 10 ^ 3$。
- 对于 $100\%$ 的数据，$1 \le n, m \le 10^5$，$1\le k \le 50$，$1 \le p \le n$，$1\le v \le k$。

#### 说明
翻译自 [COCI 2015-2016 #3 E NEKAMELEONI](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)，满分 140。



## 样例 #1

### 输入

```
4 3 5
2 3 1 2
2
1 3 3
2
1 1 1
2
```

### 输出

```
3
-1
4
```

## 样例 #2

### 输入

```
6 3 6
1 2 3 2 1 1
2
1 2 1
2
1 4 1
1 6 2
2```

### 输出

```
3
3
4
```

# 题解

## 作者：Inui_Sana (赞：11)

模拟赛搬了这题的 $k=10^5$ 加强版。于是有了一个复杂度和 $k$ 无关的做法。感觉学到了。

设 $f_i$ 为左端点为 $i$ 时，最小的可行右端点。考虑维护这个东西。但是你发现修改一个位置的值很难维护。

你又发现每次只修改一个数，考虑线段树分治。但是你又发现你连插入都不会做。但是删除非常简单。设删了 $p$ 位置的一个 $x$，左右第一个 $x$ 分别在 $l,r$，就只要 $\forall i\in[l+1,p],f_i\to \max(f_i,r)$ 就行。于是还是线段树分治，但是对**删除操作**进行。

具体地，把修改操作视作一次删除一次插入。先默认进行所有插入，再在某一些时间区间上进行删除。再来看看我们要维护什么：

- 找一个数的前驱后继，删除/插入一个数。

使用 multiset 维护即可。

- 区间对 $x$ 取 $\max$。

一般需要吉司机，但是发现这题 $f_i$ 一定单调递增，于是转化成一段区间赋值 $x$。使用线段树，支持区间赋值以及线段树上二分。

同时注意到将一个区间 $[l,r]$ 赋值成 $x$ 的时候，区间 $[l,r]$ 内的答案一定是 $x-r+1$，于是可以同时维护答案。

至于线段树分治上的撤销操作，只需要每次这棵线段树上维护的值改变（包括 tag），就将原来的值压进一个栈里，撤销时直接修改即可。

时间复杂度 $O(q\log q\log n)$ 解决。

code：

```cpp
int n,m,q,top,a[N],f[N],ans[N];
bool vis[N];
multiset<int> st[N];
vector<int> g[N];
struct node{
	int l,r,k;
	node(int _l=0,int _r=0,int _k=0):l(_l),r(_r),k(_k){}
	bool operator<(const node &rhs)const{
		return k<rhs.k;
	}
};
struct Node{
	int o,x,y,z;
}d[N*400];
struct Sgt{
	int tr[N<<2],tag[N<<2],mn[N<<2];
	il void pushup(int o){
		d[++top]={o,tr[o],tag[o],mn[o]};
		tr[o]=max(tr[o<<1],tr[o<<1|1]);
		mn[o]=min(mn[o<<1],mn[o<<1|1]);
	}
	il void reset(int l,int r,int o,int k){
		d[++top]={o,tr[o],tag[o],mn[o]};
		tr[o]=k,tag[o]=k;
		mn[o]=k-r+1;
	}
	il void pushdown(int l,int r,int o){
		if(tag[o]){
			int mid=(l+r)>>1;
			reset(l,mid,o<<1,tag[o]);
			reset(mid+1,r,o<<1|1,tag[o]);
			d[++top]={o,tr[o],tag[o],mn[o]};
			tag[o]=0;
		}
	}
	void update(int l,int r,int o,int x,int y,int k){
		if(l>=x&&r<=y){
			reset(l,r,o,k);
			return;
		}
		pushdown(l,r,o);
		int mid=(l+r)>>1;
		if(x<=mid){
			update(l,mid,o<<1,x,y,k);
		}
		if(y>mid){
			update(mid+1,r,o<<1|1,x,y,k);
		}
		pushup(o);
	}
	int find(int l,int r,int o,int k){
		if(l==r){
			return tr[o]>=k?l:n+1;
		}
		pushdown(l,r,o);
		int mid=(l+r)>>1;
		if(tr[o<<1]<k){
			return find(mid+1,r,o<<1|1,k);
		}
		return find(l,mid,o<<1,k);
	}
	int query(int l,int r,int o,int x){
		if(l==r){
			return tr[o];
		}
		pushdown(l,r,o);
		int mid=(l+r)>>1;
		if(x<=mid){
			return query(l,mid,o<<1,x);
		}
		return query(mid+1,r,o<<1|1,x);
	}
}R;
il void upd(int l,int r,int k){
	l=max(l,1),r=min(r,R.find(1,n,1,k)-1);
	if(l>r){
		return;
	}
	R.update(1,n,1,l,r,k);
}
struct SGT{
	vector<pii> tr[N<<2];
	void delet(int o,int tmp){
		while(top>tmp){
			Node u=d[top--];
			R.tr[u.o]=u.x,R.tag[u.o]=u.y,R.mn[u.o]=u.z;
		}
		for(auto [i,j]:tr[o]){
			st[j].insert(i);
		}
	}
	void update(int l,int r,int o,int x,int y,int a,int b){
		if(x<0||y>q||x>y){
			return;
		}
		if(l>=x&&r<=y){
			tr[o].eb(a,b);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			update(l,mid,o<<1,x,y,a,b);
		}
		if(y>mid){
			update(mid+1,r,o<<1|1,x,y,a,b);
		}
	}
	void solve(int l,int r,int o){
		int tmp=top;
		for(auto [i,j]:tr[o]){
			st[j].erase(st[j].find(i));
			if(st[j].find(i)!=st[j].end()){
				continue;
			}
			auto it=st[j].lower_bound(i);
			int x=*prev(it),y=*it;
			upd(x+1,i,y);
		}
		if(l==r){
			ans[l]=R.mn[1];
			return delet(o,tmp);
		}
		int mid=(l+r)>>1;
		solve(l,mid,o<<1),solve(mid+1,r,o<<1|1);
		return delet(o,tmp);
	}
}T;
void Yorushika(){
	read(n,m,q);
	rep(i,1,m){
		st[i].insert(-inf),st[i].insert(inf);
	}
	rep(i,1,n){
		read(a[i]),st[a[i]].insert(i);
		g[i].eb(a[i]);
	}
	rep(i,1,q){
		int op,x,y;read(op);
		if(op==1){
			read(x,y);
			st[y].insert(x);
			g[x].eb(y);
			T.update(1,q,1,1,i-1,x,y);
			T.update(1,q,1,i,q,x,a[x]);
			a[x]=y;
		}else{
			vis[i]=1;
		}
	}
	rep(i,1,m){
		f[1]=max(f[1],*st[i].lower_bound(1));
	}
	rep(i,2,n){
		f[i]=f[i-1];
		for(int j:g[i-1]){
			f[i]=max(f[i],*st[j].lower_bound(i));
		}
	}
	rep(i,1,n){
		R.update(1,n,1,i,i,f[i]);
	}
	top=0;
	T.solve(1,q,1);
	rep(i,1,q){
		if(vis[i]){
			printf("%d\n",ans[i]>1e9?-1:ans[i]);
		}
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Vidoliga (赞：7)

**提供在线做法/复杂度较优做法**。

设数组为 $a$。

考虑 $O(qn)$ 怎么做，暴力双指针计算每个点作为右端点时，可行的最靠右左端点。

然后考虑优化，首先需要观察出一个比较关键的性质：

最优区间一定满足，左端点/右端点值在区间中**至多出现一次**。

证明，不然左端点向右/右端点向左移一定更优。

接下来考虑如何找一个点作为右端点的答案。

设当前点位于 $i$，首先一个必要条件是 $a_{1},\dots,a_{i}$ 包含 $[1,m]$。

然后考虑这样一个过程求解 $f_{i}$ 即 $i$ 作为右端点时，可行的最靠右左端点。

初始设 $f_{i}=1$，如果 $f_i$ 在 $a_{f_i},\dots,a_{i}$ 中出现超过 $2$ 次，则将 $f_i$ 加 $1$，否则停止。

这个显然是正确的，形式化得求解 $f_i$：

设 $r_i$ 表示最小的 $j\in[i+1,n]$，满足 $a_j=a_i$，若不存在，则 $r_i=n+1$。

有 $f_i=\min_{r_j>i}\{j\}$。

设 $R$ 为最小的 $i$，满足 $a_{1},\dots,a_{i}$ 包含 $[1,m]$，若不存在则 $R=n+1$。

此时答案即为求解 $\min_{i=R}^{n}\{i-f_{i}+1\}$

考虑设 $A_{r_i-1}=i$，若有多个 $i$ 的 $r_i$ 相同，则取最小的 $i$。

若没有 $r_i-1=j$，则 $A_j=-n$。

不难发现，答案即为求解 $\min_{i=R}^{n}\{i-\min_{j=i}^{n} \{ A_j\}+1\}$。

带修的话，运用”楼房重构“的套路可以做到 $O(q \log ^2 n)$。

具体维护细节可以参考我代码（？）

一个有趣的事情是，正常做区间查询的话常数可能很大，然后发现特判不存在某个值，再直接查询全局就是对的。

原因是因为 把某些没有 $r_i-1=j$ 的 $A_j$ 设成 $-n$，这样不难发现 $R$ 一定是最后一个 $A_j=-n$ 的后一个位置，这样就很对了。

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
//#define int ll
#define pb push_back
#define pii pair<int,int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
const int N=1e5+10,M=1e6+10,mod=998244353;
set<int> A[N]; 
int n,m,p[N],a[N],q;
set<int> st[N];
int cnt=0;
struct Seg{
	int s[N<<2],t[N<<2],L[N<<2],R[N<<2];
	inline int F(int rt,int x){
		if(x<=s[rt]) return L[rt]-x+1;
		if(L[rt]==R[rt]) return L[rt]-min(s[rt],x)+1;
		int mid=(L[rt]+R[rt])>>1;
		if(s[rt<<1|1]<x) return min(t[rt],F(rt<<1|1,x));
		else return min(mid+1-x+1,F(rt<<1,x));
	}
	inline void ph(int rt){s[rt]=min(s[rt<<1],s[rt<<1|1]),t[rt]=F(rt<<1,s[rt<<1|1]);}
	inline void build(int rt,int l,int r){
		L[rt]=l,R[rt]=r;
		if(l==r) return s[rt]=A[l].empty()?-n:*A[l].begin(),t[rt]=n+1,void();
		int mid=(l+r)>>1;
		build(rt<<1,l,mid),build(rt<<1|1,mid+1,r),ph(rt);
	}
	inline void upd(int rt,int x){
		if(L[rt]==R[rt]) return s[rt]=A[L[rt]].empty()?-n:*A[L[rt]].begin(),t[rt]=n+1,void();
		int mid=(L[rt]+R[rt])>>1;
		if(x<=mid) upd(rt<<1,x);else upd(rt<<1|1,x);
		ph(rt);	
	}
	inline int qry(int rt){return L[rt]==R[rt]?t[rt]:min(t[rt],qry(rt<<1|1));}
}t;
void ins(int v,int x){
	int l=*(--st[v].lower_bound(x)),r=*st[v].upper_bound(x);
	cnt-=st[v].size()==2;
	st[v].insert(x);
	if(l) A[p[l]-1].erase(l),t.upd(1,p[l]-1),p[l]=x,A[p[l]-1].insert(l),t.upd(1,p[l]-1);
	A[p[x]-1].erase(x),t.upd(1,p[x]-1),p[x]=r,A[p[x]-1].insert(x),t.upd(1,p[x]-1);
}
void era(int v,int x){
	int l=*(--st[v].lower_bound(x)),r=*st[v].upper_bound(x);
	st[v].erase(x);
	cnt+=st[v].size()==2;
	if(l) A[p[l]-1].erase(l),t.upd(1,p[l]-1),p[l]=r,A[p[l]-1].insert(l),t.upd(1,p[l]-1);
	A[p[x]-1].erase(x),t.upd(1,p[x]-1),p[x]=n+1,A[p[x]-1].insert(x),t.upd(1,p[x]-1);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++) st[i].insert(0),st[i].insert(n+1);
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n==1){
		while(q--){int x,v;cin>>x>>v;cout<<1<<'\n';}
		return 0;
	}
	for(int i=n;i;i--) p[i]=*st[a[i]].lower_bound(i),st[a[i]].insert(i);
	for(int i=1;i<=n;i++) A[p[i]-1].insert(i);
	for(int i=1;i<=m;i++) cnt+=st[i].size()==2;
	t.build(1,1,n);
	for(int i=1,op,x,v;i<=q;i++){
		cin>>op;
		if(op==1){
			cin>>x>>v;
			if(a[x]!=v) era(a[x],x),ins(v,x),a[x]=v;
		}
		else{
			if(cnt){cout<<-1<<'\n';continue;}
			int as=t.qry(1),val=(A[n].empty()?-n:*A[n].begin());
			as=min(as,n-val+1);
			cout<<(as>=n+1?-1:as)<<'\n'; 
		}
	}
	return 0;
}

```

---

## 作者：Silence_water (赞：4)

先说当 $1\le n,m\le 5\times 10^3$ 的做法。由于这是暴力，放弃维护一切信息。直接修改数组中的值，查询时二分长度，然后相当于一个固定长度的区间从左往右扫，当区间内 $1$ 到 $k$ 都包含时说明可行。单次修改复杂度为 $O(1)$，单次查询复杂度最坏为 $O(nk\log n)$。总时间复杂度最坏为 $O(mkn\log n)$，理论上过不去这部分数据，实际上可过。

我觉得上面那个部分和正解没啥关系。注意到 $1\le k\le 50$，这个数据范围仿佛在暗示我们些什么。

1. 升维。将 $k$ 作为一维放到我们要维护的信息中。
2. 二进制优化。用二进制数记录连续子数组中含数字 $1$ 到 $k$ 的情况，当该数等于 $2^k-1$ 时说明满足。

下面具体说明如何实现：类似于带修最大连续和的线段树求法，我们维护线段树上每个区间的前缀、后缀信息。那么答案为左区间最短长度、右区间最短长度、左区间后缀与右区间前缀拼接成的区间最短长度中的最小值。

难点在于左右区间合并的这一部分。直接合并前后缀信息，要枚举左区间所有后缀和右区间所有前缀，复杂度直接上天。改成维护前后缀第一次出现 $i$ 种不同颜色时的位置以及其颜色的状态。考虑如何维护：

对于前缀信息，我们先将左儿子对应信息复制，然后再根据右儿子的前缀进行扩展。双指针，一个指针 $i$ 为右区间所含颜色种类，一个指针 $j$ 为当前前缀所含颜色种类。如果出现新的颜色，我们就更新状态。

```cpp
for(int i=1,j=Sum[ls];i<=Sum[rs];i++)
    if((t[p].pre[j]&t[rs].pre[i])!=t[rs].pre[i])
    {
        t[p].pre[j+1]=t[p].pre[j]|t[rs].pre[i];
        t[p].P[j+1]=t[rs].P[i];
        j++,Sum[p]=j;
    }
```

后缀信息的处理同理。注意两个指针仍然是从小到大，因为我们枚举的是种类，而不是下标。

```cpp
for(int i=1,j=Sum[rs];i<=Sum[ls];i++)
    if((t[p].suf[j]&t[ls].suf[i])!=t[ls].suf[i])
    {
        t[p].suf[j+1]=t[p].suf[j]|t[ls].suf[i];
        t[p].S[j+1]=t[ls].S[i];
        j++;
    }
```

上面两部分代码中出现的 $P$ 和 $S$ 数组分别为前缀、后缀第一次出现 $i$ 种不同颜色时的位置。比如一个序列 $\{1,4,3,3,2,1\}$，它的 $S[3]$ 就等于 $4$，而不是 $3$。而它的 $S[4]$ 则等于 $2$。

为何要维护第一次的位置？因为我们需要最短的连续子数组。而上面例子中，当 $k=3$ 时我们得到的为 $3$ 而不是 $4$。再次使用双指针，$i$ 表示左区间后缀中含的颜色种类数，$j$ 表示右区间前缀中含的颜色种类数。为了具备单调性，$i$ 从大到小，$j$ 从小到大，这就相当与左区间后缀的左端点在不断右移，右区间前缀的右端点也在不断右移，两个指针都在右移，具有单调性。

```cpp
for(int i=Sum[ls],j=1;i>0;i--)
{
    while(j<=Sum[rs]&&((t[ls].suf[i]|t[rs].pre[j])!=(1ll<<k)-1))j++;
    if(j<=Sum[rs])
        Ans[p]=min(Ans[p],t[rs].P[j]-t[ls].S[i]+1);
}
```

剩余的就是普通的线段树操作，查询只需查全局即可。

[具体代码实现](https://www.luogu.com.cn/paste/g06xc1q5)



---

## 作者：Computer1828 (赞：4)

显然要丢到线段树上维护。

这个问题和 [求最大子段和](https://www.luogu.com.cn/problem/SP1043) 的做法有异曲同工之妙：利用分治的思想，设 $L$ 为线段树某节点左儿子的答案，$R$ 为右儿子的答案，$O$ 为左边的某个后缀加上右边的某个前缀且包含 $1$ 到 $k$ 的答案，那么这个节点的答案就是 $\min(L,R,O)$。

就是说，整个问题变成求 $O$，也就是算前缀和后缀然后把它们合并。

观察到 $k \leq 50$，所以我们考虑把每一种情况压到一个 `long long` 里，每一位表示这个数是否出现过。注意这时候其实并不需要 $2^{50}$，因为在处理前缀和后缀的时候，每遇到一个新数，才会更新，所以只有 $50$ 种情况。

处理前缀，我们可以先把左儿子的前缀复制到当前根，然后对于右儿子，如果它有左儿子没有的数，那么更新，也就是根存储的情况 $+1$，这种情况是 $pre[left] \mid pre[right]$（二进制或运算），并且更新所需位置。

处理后缀同理，复制右儿子，用左儿子更新。

然后合并信息。处理一般的最大子段和（无修改单次查询全局），显然有一个 $O(n)$ 的尺取做法。仿照这个做法，我们可以在线段树上进行尺取，找到一个合法位置（后缀状态二进制或前缀状态等于 $(1<<k)-1$），运用前面的对应位置，就是两位置间的距离。

这道题有个很奇妙的卡空间细节：一般来说，线段树开 $4n$ 的空间，但实际上~~根据标程~~，只需要 $262144$，所以我开了 $3 \cdot 10^5$。

代码跑得飞快。上传的复杂度应该带个常数的 $O(k)$，总复杂度大概是 $O(km\log n)$。

代码：

```cpp
int n,k,q;ll maxi;//(1<<k)-1
int a[100005];//读入
int len[N],ans[N];
struct node{ll s;int u;}pre[N][51],suf[N][51];//s是情况，u是位置 
inline bool inn(ll a,ll b){return ((a&b) == b);}//这个是判断b是不是a的子集 
#define ls o<<1
#define rs o<<1|1
inline void pushup(int o){
	ans[o] = min(ans[ls],ans[rs]);
	FOR(i,1,len[ls]) pre[o][i] = pre[ls][i];//前缀 
	int tmp = len[ls];
	FOR(i,1,len[rs]){
		if(!inn(pre[o][tmp].s,pre[rs][i].s)) pre[o][++tmp] = (node){pre[o][tmp-1].s | pre[rs][i].s,pre[rs][i].u};
	}
	len[o] = tmp;
	
	FOR(i,1,len[rs]) suf[o][i] = suf[rs][i];//后缀 
	tmp = len[rs];
	FOR(i,1,len[ls]){
		if(!inn(suf[o][tmp].s,suf[ls][i].s)) suf[o][++tmp] = (node){suf[o][tmp-1].s | suf[ls][i].s,suf[ls][i].u};
	}
	
	tmp = 1;
	for(int i = len[ls];i>=1;--i){//合并 
		while(tmp<=len[rs] && (suf[ls][i].s | pre[rs][tmp].s)!= maxi) ++tmp;
		if(tmp <= len[rs]) ans[o] = min(ans[o],pre[rs][tmp].u-suf[ls][i].u+1);
	}
}

inline void build(int l,int r,int o){
	if(l == r){
		len[o] = 1,ans[o] = inf;
		pre[o][1] = suf[o][1] = (node){1ll<<(a[l]-1),l};
		return ;
	}
	...
}

inline void change(int l,int r,int o,int p,int v){
	if(l == r){
		pre[o][1] = suf[o][1] = (node){1ll<<(v-1),l};
		return ;
	}
	...
}
```

---

## 作者：activeO (赞：2)

模拟赛出了这题的加强版，把 $k$ 的范围也设为了 $10^5$，正解复杂度为 $O(n\log^2(n))$ 记录一手。

首先考虑对于每个左端点 $l$ 维护满足条件的最小的 $r$，记为 $R_l$，一次修改操作就相当于是先删除这个点上的数，再插入一个数。

发现删除一个数是好维护的，记要删除的位置是 $x$，上一个和下一个与 $x$ 数相同的位置分别是 $pl,pr$，那么就相当于 $R_i \leftarrow \max(R_i,r) (l<i\leq x)$。

而插入一个数不好维护了，所以考虑不插入了，刚开始把所有的数都先插进去，然后线段树分治去进行删除，即对于第 $i$ 次修改 $(p,x)$，对应到 $[i,n]$ 删除 $a_p$，$[1,i)$ 删除 $x$。

求 $pl,pr$ 可以用 multiset 维护，然后可以用主席树维护 $R$ 序列做到撤销删除操作，撤销时把这个点多开的节点回收。

而对于答案的维护，可以发现 $R_i$ 显然是非严格递增的，所以如果我们维护线段树每个区间的答案，然后删除时对一个区间取 $\max$ 的操作其实就相当于二分到第一个大于 $r$ 的位置 $pos$，区间推平 $[1,pos]\cap[l+1,x]$，这部分修改区间的答案是容易得到的（就是取右端点时最短），然后在线段树上更新答案。

这实际实现上也可以用栈维护线段树节点的值的变化用于撤销，和写主席树本质上是一样的。


```cpp
// Problem: P7230 [COCI2015-2016#3] NEKAMELEONI
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7230
// Memory Limit: 488 MB
// Time Limit: 3000 ms

#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

const int inf=0x3f3f3f3f;
const int maxn=1e5+5;
int a[maxn],b[maxn];
multiset<int> st[maxn];
int tr[maxn<<6],lc[maxn<<6],rc[maxn<<6];
int tag[maxn<<6],res[maxn<<6],cnt=0;
vector<pii> vec[maxn<<2];
vector<int> vc[maxn];
int rt[maxn],tot=1;
int rb[maxn<<6][6],top=0;
bool bk[maxn];

void rec(int now){
	rb[++top][0]=now;
	rb[top][1]=tr[now];
	rb[top][2]=lc[now];
	rb[top][3]=rc[now];
	rb[top][4]=tag[now];
	rb[top][5]=res[now];
}
void pushup(int now){
	tr[now]=max(tr[lc[now]],tr[rc[now]]);
	res[now]=inf;
	if(lc[now]) res[now]=min(res[now],res[lc[now]]);
	if(rc[now]) res[now]=min(res[now],res[rc[now]]);
}
void pushdown(int now,int l,int r){
	if(!tag[now]) return;
	// printf("kk%d %d\n",lc[now],rc[now]);
	int mid=(l+r)>>1;
	rec(now);
	rec(lc[now]);
	rec(rc[now]);
	tr[lc[now]]=tag[lc[now]]=tag[now];
	res[lc[now]]=(tag[now]-mid+1);
	tr[rc[now]]=tag[rc[now]]=tag[now];
	res[rc[now]]=(tag[now]-r+1);
	tag[now]=0;
}
int update1(int now,int l,int r,int ql,int qr,int v){
	if(ql>qr) return 0;
	if(!now) now=++cnt;
	// printf("%d %d %d %d %d\n",now,l,r,tr[now],res[now]);
	rec(now);
	if(ql<=l&&qr>=r){
		tr[now]=tag[now]=v;
		res[now]=(v-r+1);
		return now;
	}
	pushdown(now,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid) lc[now]=update1(lc[now],l,mid,ql,qr,v);
	if(qr>mid) rc[now]=update1(rc[now],mid+1,r,ql,qr,v);
	pushup(now);
	return now;
}
int update2(int now,int l,int r,int x,int v){
	if(!now) now=++cnt;
	// printf("%d %d %d %d %d\n",now,l,r,x,v);
	if(l==r){
		tr[now]=v;
		res[now]=v-l+1;
		return now;
	}
	int mid=(l+r)>>1;
	if(x<=mid) lc[now]=update2(lc[now],l,mid,x,v);
	else rc[now]=update2(rc[now],mid+1,r,x,v);
	pushup(now);
	return now;
}
int query(int now,int l,int r,int x){
	if(l==r) return l;
	int mid=(l+r)>>1;
	pushdown(now,l,r);
	if(tr[lc[now]]<x) return query(rc[now],mid+1,r,x);
	else return query(lc[now],l,mid,x);
}
int query2(int now,int l,int r,int x){
	if(!now) return 0;
	if(l==r) return tr[now];
	int mid=(l+r)>>1;
	pushdown(now,l,r);
	if(x<=mid) return query2(lc[now],l,mid,x);
	else return query2(rc[now],mid+1,r,x);
}

void update3(int now,int l,int r,int ql,int qr,pii x){
	if(ql>qr) return;
	if(ql<=l&&qr>=r){
		vec[now].push_back(x);
		return;
	}
	int mid=(l+r)>>1;
	if(ql<=mid) update3(now<<1,l,mid,ql,qr,x);
	if(qr>mid) update3(now<<1|1,mid+1,r,ql,qr,x);
}

int n,m,q;

void dfs(int now,int l,int r){
	int lst=tot,lst2=top;
	int tt=tot+1;
	tot++;
	rt[tt]=rt[lst];
	// printf("%d %d %d : %d %d\n",now,l,r,lst2,rt[tt]);
	for(int j=0;j<(int)vec[now].size();j++){
		pii x=vec[now][j];
		// printf("%d %d %d : %d %d\n",now,l,r,x.first,x.second);
		st[x.second].erase(st[x.second].find(x.first));
		auto ttt=st[x.second].lower_bound(x.first);
		if(ttt==st[x.second].end()){
			int ll=*(--ttt);
			// printf("here %d\n",ll);
			rt[tt]=update1(rt[tt],1,n,ll+1,n,inf);
			continue;
		}
		int rr=*(ttt),ll=*(--ttt);
		// printf("here %d %d\n",ll,rr);
		int tmp=query(rt[tt],1,n,rr)-1;
		if(tmp>ll) rt[tt]=update1(rt[tt],1,n,ll+1,min(x.first,tmp),rr);
	}
	// printf("kk%d %d %d\n",now,l,r);
	// for(int i=1;i<=n;i++) printf("%d ",query2(rt[tt],1,n,i));
	// puts("");
	if(l==r){
		if(bk[l]){
			if(res[rt[tt]]<=n) printf("%d\n",res[rt[tt]]);
			else puts("-1");
		}
		for(pii x : vec[now]) st[x.second].insert(x.first);
		tot=lst;
		while(top>lst2){
			int x=rb[top][0];
			tr[x]=rb[top][1];
			lc[x]=rb[top][2];
			rc[x]=rb[top][3];
			tag[x]=rb[top][4];
			res[x]=rb[top][5];
			top--;
		}
		// printf("%d %d back%d\n",l,r,lst2);
		return;
	}
	int mid=(l+r)>>1;
	dfs(now<<1,l,mid);
	dfs(now<<1|1,mid+1,r);
	for(pii x : vec[now]) st[x.second].insert(x.first);
	tot=lst;
	while(top>lst2){
		int x=rb[top][0];
		tr[x]=rb[top][1];
		lc[x]=rb[top][2];
		rc[x]=rb[top][3];
		tag[x]=rb[top][4];
		res[x]=rb[top][5];
		top--;
	}
	// printf("%d %d back%d\n",l,r,lst2);
}

int num[maxn];

int main(){
	
	// freopen("mex.in","r",stdin);
	// freopen("mex.out","w",stdout);
	
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1;i<=m;i++) st[i].insert(0);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		st[a[i]].insert(i);
		b[i]=a[i];
		vc[i].push_back(a[i]);
	}
	for(int i=1;i<=q;i++){
		int op,x,y;
		scanf("%d",&op);
		if(op==1){
			scanf("%d %d",&x,&y);
			update3(1,1,q,1,i-1,make_pair(x,y));
			update3(1,1,q,i,q,make_pair(x,b[x]));
			b[x]=y;
			st[y].insert(x);
			vc[x].push_back(y);
		}else bk[i]=1;
	}
	
	int now=0,j=0;
	for(int i=1;i<=n;i++){
		while(j<n&&now<m){
			j++;
			for(int x : vc[j]){
				if(!num[x]) now++;
				num[x]++;
			}
		}
		// printf("%d : %d %d\n",i,j,now);
		if(now==m) rt[1]=update2(rt[1],1,n,i,j);
		else rt[1]=update2(rt[1],1,n,i,inf);
		for(int x : vc[i]){
			num[x]--;
			if(!num[x]) now--;
		}
	}
	
	// for(int i=1;i<=n;i++) printf("%d ",query2(rt[1],1,n,i));
	// puts("kk");
	
	// printf("kk%d %d\n",tr[rt[1]],res[rt[1]]);
	
	dfs(1,1,q);
	
	return 0;
}
```

---

## 作者：NKL丶 (赞：2)

## Description

维护一个长度为 $n$ 的序列 $v$，支持两种操作：

1. 将第 $p$ 位改为 $v$。
2. 询问序列内长度最小的区间 $[l,r]$，满足 $\operatorname{mex}^{r}_{i=l}=k$。

$1 \le n,q \le 10^5,1 \le v_i \le k \le 50$

## Solution

注意到 $k$ 的范围并不大，提示我们可以从值入手，维护序列内不同值的信息。

考虑不带修怎么做。由于这题内的区间信息是可以合并的，我们可以像求最大子段和一样将每个区间前缀，后缀及区间内的答案存下来，具体的，我们将区间内的值二进制状压成一个数存下来，然后用位运算来表示求交集。可是这样子做仍然需要枚举两个区间的前缀后缀，复杂度是 $O(n^2)$ 的，不能接受，但可以发现区间前后缀的状态变化只有 $k$ 种，也就是说，我们可以将每个变化位置及变化后的状态记录下来，然后合并时在前后缀的数组上用双指针更新，这样做的复杂度是 $O(k)$ 的，从而能正确维护区间信息。

上述过程显然可以用线段树维护，那么就变成了线段树上单点修改全局查询问题了，复杂度为 $O(kn \log n)$。

## [Code](https://www.luogu.com.cn/paste/unrawzxo)

---

## 作者：daniEl_lElE (赞：1)

考虑线段树。对于每一个区间，注意到只有 $O(k)$ 种包含数字本质不同的前缀/后缀。考虑维护他们的位置与包含数字。

合并的时候，如果一个区间本质不同前缀不满 $k$ 个，那么需要合并下一个序列的。每次加入的时候如果出现增加那么将位置记录下来即可。后缀同理。

同时，我们需要记录答案。考虑将左边后缀、右边前缀的首次出现位置留下来，做一个双指针合并时计算答案即可。

总复杂度 $O(nk\log n)$。

```cpp
#include <bits/stdc++.h>
#define double long double
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
int n,k,q,a[100005];
struct node{
	pair<int,int> pre[51],suf[51];
	int ans;
	int lsiz,rsiz;
};
node merge(node x,node y){
	node z; z.ans=min(x.ans,y.ans);
	pair<int,int> a[105]; int tsiz=0;
	for(int i=x.rsiz;i>=1;i--) a[++tsiz]=x.suf[i];
	for(int i=1;i<=y.lsiz;i++) a[++tsiz]=y.pre[i];
	int tag[55]; for(int i=1;i<=k;i++) tag[i]=0;
	int r=0,tot=0;
	while(tot<k&&r<tsiz){
		r++;
		if(!tag[a[r].first]) tot++; tag[a[r].first]++;
	}
	if(tot==k) z.ans=min(z.ans,a[r].second-a[1].second+1);
	for(int l=1;l<tsiz;l++){
		if(tag[a[l].first]==1) tot--; tag[a[l].first]--;
		while(tot<k&&r<tsiz){
			r++;
			if(!tag[a[r].first]) tot++; tag[a[r].first]++;
		}
		if(tot==k) z.ans=min(z.ans,a[r].second-a[l+1].second+1);
	}
	for(int i=1;i<=k;i++) tag[i]=0;
	for(int i=1;i<=x.lsiz;i++) z.pre[i]=x.pre[i],tag[x.pre[i].first]=1; z.lsiz=x.lsiz;
	for(int i=1;i<=y.lsiz;i++) if(!tag[y.pre[i].first]) tag[y.pre[i].first]=1,z.pre[++z.lsiz]=y.pre[i];
	for(int i=1;i<=k;i++) tag[i]=0;
	for(int i=1;i<=y.rsiz;i++) z.suf[i]=y.suf[i],tag[y.suf[i].first]=1; z.rsiz=y.rsiz;
	for(int i=1;i<=x.rsiz;i++) if(!tag[x.suf[i].first]) tag[x.suf[i].first]=1,z.suf[++z.rsiz]=x.suf[i];
	return z;
}
struct sgt{
	node f[400005];
	void build(int i,int l,int r){
		if(l==r){
			f[i].lsiz=f[i].rsiz=1;
			f[i].pre[1]=f[i].suf[1]=make_pair(a[l],l);
			f[i].ans=1e9;
			if(k==1) f[i].ans=1;
			return ; 
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int pos,int cg){
		if(l==r){
			f[i].lsiz=f[i].rsiz=1;
			f[i].pre[1]=f[i].suf[1]=make_pair(cg,l);
			f[i].ans=1e9;
			if(k==1) f[i].ans=1;
			return ; 
		}
		if(pos<=mid) change(i*2,l,mid,pos,cg);
		else change(i*2+1,mid+1,r,pos,cg);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
}tree;
signed main(){
	cin>>n>>k>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	tree.build(1,1,n);
	while(q--){
		int opt; cin>>opt;
		if(opt==1){
			int p,v; cin>>p>>v;
			tree.change(1,1,n,p,v);
		}
		else{
			if(tree.f[1].ans<=n) cout<<tree.f[1].ans<<"\n";
			else cout<<-1<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[https://www.cnblogs.com/yhddd/p/18405064](https://www.cnblogs.com/yhddd/p/18405064)

[P7230](https://www.luogu.com.cn/problem/P7230)

### 思路

对每个左端点维护右端点 $res_i$。操作形如删去一个数再加入一个数。如果删掉 $p$ 上的 $a_p$，找到左右最近的 $l,r$ 使得 $a_l=a_r=a_p$。那么 $res_{l+1},\dotsb,res_p$ 对 $r$ 取 max。实际上要维护 $\max res_i-i+1$，因为 $res_i$ 单调，所以相当于线段树上二分找到最左的小于 $r$ 的位置然后区间覆盖。

删除好做，加入难做，考虑线段树分治。先把所有的时刻的 $a_i$ 都当作存在，右移右端点维护出所有 $res_i$。multiset 维护每个值出现的位置来求 $l,r$。进入一个区间后进行删除操作。撤销操作可以用主席树，也可以记录下所有修改和下传的位置和值。

### code

```cpp
int n,m,q,a[maxn];
multiset<int> s[maxn];
int que[maxn],res[maxn],cnt[maxn];
vector<int> val[maxn];
int st[maxn<<6][4],tp;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
namespace sgt{
	int mx[maxn<<2],tag[maxn<<2],ans[maxn<<2];
	void build(int nd,int l,int r){
		if(l==r){
			mx[nd]=res[l];ans[nd]=mx[nd]-l+1;
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		mx[nd]=max(mx[ls],mx[rs]),ans[nd]=min(ans[ls],ans[rs]);
	}
	void down(int nd,int l,int r){
			st[++tp][0]=nd,st[tp][1]=mx[nd],st[tp][2]=tag[nd],st[tp][3]=ans[nd];
		st[++tp][0]=ls,st[tp][1]=mx[ls],st[tp][2]=tag[ls],st[tp][3]=ans[ls];
		mx[ls]=tag[nd],tag[ls]=tag[nd],ans[ls]=mx[ls]-mid+1;
		st[++tp][0]=rs,st[tp][1]=mx[rs],st[tp][2]=tag[rs],st[tp][3]=ans[rs];
		mx[rs]=tag[nd],tag[rs]=tag[nd],ans[rs]=mx[rs]-r+1;
		tag[nd]=0;
	}
	void updata(int nd,int l,int r,int ql,int qr,int w){
		if(ql>qr)return ;
		if(l>=ql&&r<=qr){
			st[++tp][0]=nd,st[tp][1]=mx[nd],st[tp][2]=tag[nd],st[tp][3]=ans[nd];
			mx[nd]=w,tag[nd]=w,ans[nd]=mx[nd]-r+1;
			return ;
		}
		if(tag[nd])down(nd,l,r);
		if(ql<=mid)updata(ls,l,mid,ql,qr,w);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
		st[++tp][0]=nd,st[tp][1]=mx[nd],st[tp][2]=tag[nd],st[tp][3]=ans[nd];
		mx[nd]=max(mx[ls],mx[rs]),ans[nd]=min(ans[ls],ans[rs]);
	}
	int fd(int nd,int l,int r,int w){
		if(mx[nd]<w)return -1;
		if(l==r)return l;
		if(tag[nd])down(nd,l,r);
		int val=fd(ls,l,mid,w);
		if(val==-1)return fd(rs,mid+1,r,w);
		return val;
	}
}
vector<pii> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,pii w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd].pb(w);
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void add(pii p){
	int l=*--s[p.se].find(p.fi);
	auto it=s[p.se].erase(s[p.se].find(p.fi));
	if(it==s[p.se].end()){
		sgt::updata(1,1,n,l+1,n,inf);
		return ;
	}
	int r=*it;
	int pos=sgt::fd(1,1,n,r);
	if(pos>l+1)sgt::updata(1,1,n,l+1,pos-1,r);
}
void del(){
	int nd=st[tp][0];
	sgt::mx[nd]=st[tp][1],sgt::tag[nd]=st[tp][2],sgt::ans[nd]=st[tp][3];
	tp--;
}
void dfs(int nd,int l,int r){
	int tmp=tp;
	for(pii p:tree[nd])add(p);
	if(l==r){
		if(que[l])printf("%lld\n",sgt::ans[1]>n?-1:sgt::ans[1]);
	}
	else{
		dfs(ls,l,mid),dfs(rs,mid+1,r);
	}
	while(tp>tmp)del();
	for(pii p:tree[nd])s[p.se].insert(p.fi);
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[a[i]].insert(i),val[i].pb(a[i]);
	for(int i=1;i<=m;i++)s[i].insert(0);
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1){
			int p=read(),v=read();
			updata(1,1,q,i,q,{p,a[p]});
			a[p]=v;s[a[p]].insert(p);val[p].pb(a[p]);
			updata(1,1,q,1,i-1,{p,a[p]});
		}
		else que[i]=1;
	}
	for(int i=1,j=1,num=0;i<=n;i++){
		while(j<=n&&num<m){
			for(int k:val[j]){
				if(!cnt[k])++num;
				cnt[k]++;
			}
			j++;
		}
		if(num<m)res[i]=inf;
		else res[i]=j-1;
		for(int k:val[i]){
			cnt[k]--;
			if(!cnt[k])--num;
		}
	}
	sgt::build(1,1,n);
	dfs(1,1,q);
}
```

### upd

当线段树分治到叶子是也最多只有 $O(n)$ 个操作，所以栈的大小是 $O(n\log n)$ 的。如果用主席树，整个线段树分治下来有 $O(n\log n)$ 个操作，主席树空间 $O(n\log^2 n)$ 寄了。可以回收节点，线段树分治撤销操作时不只跳到父亲版本，而是直接把当前版本新的点都删了，这样一来直接等价于对每层维护一个线段树了。

---

## 作者：takanashi_mifuru (赞：0)

暴力是显然的，我们只需要对于 $m$ 个数，每个数维护 $nxt$ 从当前位置开始往后第一个这个数的位置，那么枚举左端点 $i$，这里给答案的贡献就是 $\max(nxt_j)-i+1$。

我们考虑优化这个暴力，也就是想办法维护这个 $\max(nxt_i)$。

把每个位置看做一个集合，你修改一个数可以看做删除原来的数再插入新的数，容易发现插入一个数对答案肯定没坏处，删除一个数对答案肯定没好处，但是我们要求的是 $\max(nxt_j)$，如果我们操作过后有一个 $nxt_j$ 变小，我们不好统计他的贡献，删除的话直接找到我的影响范围，把他们和下一个点取 $\max$ 就好了，这是好维护的。

所以我们想到把这个东西写成线段树分治，把插入拍掉，来考虑删除操作，用主席树随便维护一下就行了。

然后你空间爆了。

一个比较常用的优化方法是记录你下去的时候有多少个节点，回溯上来的时候直接把下面新加的节点全割掉，然后空间就够了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int a[100005];
int lst[100005];
struct node{
    int lt,rt,id,val;
};
vector<node> usr;

int ans[100005];
bool Tag[100005];
multiset<int> T[100005];

class tzkTree{
    public:
    int R[100005<<5];
    int Min[100005<<5];
    int Tag[100005<<5];
    int ans[100005<<5];
    int lson[100005<<5];
    int rson[100005<<5];
    int rt[100005<<3];
    int tot;
    void pushup(int cur,int lt,int rt){
        ans[cur]=min(ans[lson[cur]],ans[rson[cur]]);
        R[cur]=max(R[lson[cur]],R[rson[cur]]);
        Min[cur]=min(Min[lson[cur]],Min[rson[cur]]);
        return;
    }
    void build(int &cur,int lt,int rt,int nxt[]){
        if(!cur)cur=++tot;
        if(lt==rt){
            R[cur]=nxt[lt];
            Min[cur]=nxt[lt];
            ans[cur]=nxt[lt]-lt+1;
            return;
        }
        int mid=lt+rt>>1;
        build(lson[cur],lt,mid,nxt);
        build(rson[cur],mid+1,rt,nxt);
        pushup(cur,lt,rt);
        return;
    }
    void addtag(int &cur,int lt,int rt,int val){
        Tag[cur]=val;
        ans[cur]=val-rt+1;
        Min[cur]=val;
        R[cur]=val;
        return;
    }
    void pushdown(int cur,int lt,int rt){
        if(!Tag[cur])return;
        int mid=lt+rt>>1;
        addtag(lson[cur],lt,mid,Tag[cur]),addtag(rson[cur],mid+1,rt,Tag[cur]);
        Tag[cur]=0;
    }
    void update(int pre,int &cur,int lt,int rt,int qx,int qy,int val){
        if(tot>(100000<<9))assert(0);
        if(!lson[cur]){
            lson[cur]=lson[pre];
            
        }
        if(!rson[cur])rson[cur]=rson[pre];
        if(lt>qy||rt<qx)return;
        if(Min[cur]>=val)return;
        if(lt>=qx&&rt<=qy){
            if(R[cur]<=val)return addtag(cur,lt,rt,val);
        }
        tot++;
        R[tot]=R[lson[cur]];
        Min[tot]=Min[lson[cur]];
        ans[tot]=ans[lson[cur]];
        Tag[tot]=Tag[lson[cur]];
        lson[tot]=lson[lson[cur]];
        rson[tot]=rson[lson[cur]];
        lson[cur]=tot;
        tot++;
        R[tot]=R[rson[cur]];
        Min[tot]=Min[rson[cur]];
        ans[tot]=ans[rson[cur]];
        Tag[tot]=Tag[rson[cur]];
        lson[tot]=lson[rson[cur]];
        rson[tot]=rson[rson[cur]];
        rson[cur]=tot;
        //
        pushdown(cur,lt,rt);
        int mid=lt+rt>>1;
        update(lson[pre],lson[cur],lt,mid,qx,qy,val);
        update(rson[pre],rson[cur],mid+1,rt,qx,qy,val);
        pushup(cur,lt,rt);
    }
}Q;

class SegTree{
    public:
    vector<pair<int,int> > del[100005<<2];
    void insert(int cur,int lt,int rt,int qx,int qy,pair<int,int> val){
        if(lt>qy||rt<qx)return;
        if(lt>=qx&&rt<=qy)return del[cur].push_back(val),void();
        int mid=lt+rt>>1;
        insert(cur<<1,lt,mid,qx,qy,val),insert(cur<<1|1,mid+1,rt,qx,qy,val);
        return;
    }
    int done=1;
    void query(int cur,int lt,int rt,int p){
        done++;
        Q.rt[done]=++Q.tot;
        Q.Tag[Q.rt[done]]=Q.Tag[Q.rt[p]];
        Q.ans[Q.rt[done]]=Q.ans[Q.rt[p]];
        Q.Min[Q.rt[done]]=Q.Min[Q.rt[p]];
        Q.R[Q.rt[done]]=Q.R[Q.rt[p]];
        Q.lson[Q.rt[done]]=Q.lson[Q.rt[p]];
        Q.rson[Q.rt[done]]=Q.rson[Q.rt[p]];
        for(int i=0;i<del[cur].size();i++){
            int now=del[cur][i].first;
            int val=del[cur][i].second;
            T[val].erase(T[val].find(now));
            int nxt;
            if(T[val].lower_bound(now)==T[val].end()){
                nxt=-1;
            }
            else{
                nxt=*T[val].lower_bound(now);
            }
            int pre;
            if((T[val].lower_bound(now))==T[val].begin()){
                pre=-1;
            }
            else{
                pre=*--T[val].lower_bound(now);
            }
            if(now==1)pre=0;
            if(pre==-1)pre=0;
            if(nxt==-1)nxt=1e9;
            Q.update(Q.rt[p],Q.rt[done],1,n,pre+1,now,nxt);
        }
        if(lt==rt){
            ans[lt]=Q.ans[Q.rt[done]];
            for(int i=0;i<del[cur].size();i++){
                int now=del[cur][i].first;
                T[del[cur][i].second].insert(now);
            }
            return;
        }
        int nd=done;
        int mid=lt+rt>>1;
        int Dt=Q.tot;
        query(cur<<1,lt,mid,nd);
        Q.tot=Dt;
        query(cur<<1|1,mid+1,rt,nd);
        Q.tot=Dt;
        for(int i=0;i<del[cur].size();i++){
            int now=del[cur][i].first;
            T[del[cur][i].second].insert(now);
        }
        return;
    }
}P;
int nxt[100005];
int swp[100005];
vector<int> need[100005];
int main(){
    Q.ans[0]=1e9;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        T[a[i]].insert(i);
        lst[i]=0;
        need[i].push_back(a[i]);
    }
    for(int i=1;i<=q;i++){
        int opt;
        int x,y;
        scanf("%d",&opt);
        if(opt==1){
            scanf("%d%d",&x,&y);
            usr.push_back(node{lst[x],i-1,x,a[x]});
            lst[x]=i;
            a[x]=y;
            T[y].insert(x);
            need[x].push_back(y);
        }
        else{
            Tag[i]=true;
        }
    }
    for(int i=1;i<=n;i++){
        usr.push_back(node{lst[i],q,i,a[i]});
    }
    for(int i=0;i<usr.size();i++){
        if(usr[i].lt>0){
            P.insert(1,0,q,0,usr[i].lt-1,make_pair(usr[i].id,usr[i].val));
        }
        if(usr[i].rt<q){
            P.insert(1,0,q,usr[i].rt+1,q,make_pair(usr[i].id,usr[i].val));
        }
    }
    for(int i=1;i<=m;i++)nxt[i]=1e9;
    for(int i=n;i>=1;i--){
        for(int j=0;j<need[i].size();j++){
            swp[i]=max(nxt[need[i][j]],swp[i]);
            nxt[need[i][j]]=i;
        }
        nxt[a[i]]=i;
    }
    int N=0;
    for(int i=1;i<=m;i++){
        N=max(N,nxt[i]);
    }
    for(int i=1;i<=n;i++){
        nxt[i]=N;
        N=max(N,swp[i]);
    }
    Q.build(Q.rt[1],1,n,nxt);
    P.query(1,0,q,1);
    for(int i=1;i<=q;i++){
        if(Tag[i]){
            if(ans[i]>n){
                puts("-1");
            }
            else{
                printf("%d\n",ans[i]);
            }
        }
    }
    return 0;
}
/*

*/
```

---

## 作者：XuYueming (赞：0)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P7230)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18345966)。

## 题意简述

你要维护一个序列 $a_i \in [1, k]$（$k \leq 50$），支持：

1. 单点修改；
1. 询问最短的包含全部 $1 \sim k$ 的自区间长度，或报告无解。

## 题目分析

我想到了两种做法，写题解以加深印象。

### 方法 $1$：直接用线段树维护

只有单点修改，尝试用线段树维护分治。考虑如何 `pushup`。

`pushup` 先继承左右区间的答案，然后考虑经过当前分治中心的区间对答案的贡献。

先考虑暴力。枚举左区间里一个端点 $l$，那么我们要找到在右区间里找到一个 $r$，使得所有颜色均在 $l \sim r$ 中出现。记录选出左半区间的颜色集合为 $\mathcal{S}$，需要找到右半部分出现颜色集合为 $\complement_{\lbrace i \rbrace _ {i = 1} ^ {k}} \mathcal{S}$。因为 $k$ 的范围很小，我们想到状压，用一个 01 串刻画每种颜色是否出现。那么只用用全集异或一下，再用个桶什么的记一下右半部分的信息即可。

时间复杂度想要正确，那么 `pushup` 应该和 $k$ 有关。发现，取按位或的过程是单调不降的，增加到全集最多增加 $k$ 次，因此，我们只需要记 $k$ 个按位或发生突变的位置即可。换句话说，你只用关心新的一个颜色出现的位置，而这种位置最多只有 $k$ 个。

因此，线段树结点里我们只需要记录前缀和后缀的按位或发生突变的位置以及相应值即可。合并的时候，使用双指针即可在 $\Theta(k)$ 的时间内完成。

时间复杂度：$\Theta((n+q) k \log n)$，空间复杂度：$\Theta(nk)$。

### 方法 $2$：找性质 + 线段树

我们考虑，一个最优的区间一定满足什么。显然，此时两个端点必定不能往里面缩。说明了什么？说明往里缩的话会有一个颜色没有出现。换句话说，两个端点必定是在区间内仅出现过一次的颜色。不妨只考虑 $\Theta(n)$ 枚举一端，是其必要不充分条件，要快速找到另一个端点，使这段区间内出现了所有 $k$ 种颜色。这一步可以用线段树上二分 $\Theta(\log n)$ 地求出。于是，我们用 $\Theta(n \log n)$ 的时间搞出了本来 $\Theta(n ^ 2)$ 的所有区间。

具体地，我们可以用 $k$ 个 `set` 维护 $k$ 种颜色出现的所有位置。特别地，每一个 `set` 都插入 $0$ 和 $n + 1$。对于某个位置 $i$，我们找到上一个出现 $a_i$ 的位置 $j$，并在二分出一个 $p \in (j, i]$，使 $[p, i]$ 包含了 $k$ 种颜色。对于后继同理。

别忘了，我们还要支持修改。显然，我们需要删除包含这个点的信息，再加上修改后的信息。我们不妨枚举 $k$ 种颜色，然后把包括这个位置的这一段的信息删除。这一步体现在在每一种颜色的 `set` 里，找到这一个位置前驱后继，并删除答案。维护所有区间的答案可以用可删堆或 `multiset`。想通了实现起来很简单。

时间复杂度：$\Theta(n \log n + qk \log n)$，空间复杂度：$\Theta(n)$，均优于第一种做法。但是，无奈它常数大。

考虑优化？

预处理可以双指针 $\Theta(n)$ 地搞，不过加到答案堆里有一个 $\log$。

我们在修改 $p$ 的时候，不断二分，找到一个位置 $p'$ 使 $a_{p'}$ 在 $(p', p]$ 中第一次出现，那么，答案可能是以 $p'$ 为左端点的一段区间，二分找到右端点并更新到答案里即可。

等等！那这样原先的有些区间不会失效吗？是的，但是与其考虑去删除这些区间，不如在查询的时候再判断。即如果堆顶不合法直接舍弃。

时间复杂度依然是：$\Theta(n \log n + qk \log n)$，尽管空间变成了 $\Theta(n + qk)$，但是常数小了很多，比法 $1$ 快了 $2$ 秒左右。

## 代码

### 方法 $1$

[代码](https://www.luogu.com.cn/paste/qftkvfa3)，[提交记录](https://www.luogu.com.cn/record/168822473)。

### 方法 $2$

#### 优化前

[代码](https://www.luogu.com.cn/paste/am9is1jh)，[提交记录](https://www.luogu.com.cn/record/168957486)。

#### 优化后

[提交记录](https://www.luogu.com.cn/record/168975673)。

```cpp
// #pragma GCC optimize(3)
// #pragma GCC optimize("Ofast", "inline", "-ffast-math")
// #pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <cstdio>
#include <set>
#include <queue>
using namespace std;

int n, k, m;
long long all;
int val[100010];

struct Segment_Tree {
	#define lson (idx << 1    )
	#define rson (idx << 1 | 1)
	
	struct node {
		int l, r;
		long long val;
	} tree[100010 << 2];
	
	void pushup(int idx) {
		tree[idx].val = tree[lson].val | tree[rson].val;
	}
	
	void build(int idx, int l, int r) {
		tree[idx] = {l, r, 0};
		if (l == r) return tree[idx].val = 1ll << (val[l] - 1), void();
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(idx);
	}
	
	void modify(int idx, int p, int v) {
		if (tree[idx].l > p || tree[idx].r < p) return;
		if (tree[idx].l == tree[idx].r) return tree[idx].val = 1ll << (v - 1), void();
		modify(lson, p, v), modify(rson, p, v), pushup(idx);
	}
	
	long long query(int idx, int l, int r) {
		if (tree[idx].l > r || tree[idx].r < l) return 0;
		if (l <= tree[idx].l && tree[idx].r <= r) return tree[idx].val;
		return query(lson, l, r) | query(rson, l, r);
	}
	
	int find(int idx, long long d) {
		if (tree[idx].l == tree[idx].r) return tree[idx].l;
		if ((tree[rson].val | d) == all) return find(rson, d);
		return find(lson, d | tree[rson].val);
	}
	
	int queryl(int idx, int l, int r, long long &d) {
		if (tree[idx].l > r || tree[idx].r < l) return -1;
		if (l <= tree[idx].l && tree[idx].r <= r) {
			if ((d | tree[idx].val) != all)
				return d |= tree[idx].val, -1;
			if (tree[idx].l == tree[idx].r)
				return tree[idx].l;
			int res = queryl(lson, l, r, d);
			if (~res) return res;
			return queryl(rson, l, r, d);
		}
		int res = queryl(lson, l, r, d);
		if (~res) return res;
		return queryl(rson, l, r, d);
	}
	
	int find(int idx, int l, int r, long long d) {
		if (tree[idx].l > r || tree[idx].r < l) return -1;
		if (l <= tree[idx].l && tree[idx].r <= r) {
			if ((tree[idx].val | d) == d) return -1;
			if (tree[idx].l == tree[idx].r) return tree[idx].l;
			if ((tree[rson].val | d) ^ d)
				return find(rson, l, r, d);
			return find(lson, l, r, d);
		}
		int res = find(rson, l, r, d);
		return ~res ? res : find(lson, l, r, d);
	}
	
	#undef lson
	#undef rson
} yzh;

inline bool check(int l, int r) {
	return yzh.query(1, l, r) == all;
}

int queryl(int L, int R) {
	long long done = 0;
	return yzh.queryl(1, L, R, done);
}

struct Heap {
	struct node {
		int l, r;
		inline bool friend operator < (const node & a, const node & b) {
			return a.r - a.l > b.r - b.l;
		}
	};
	priority_queue<node> yzh;
	
	inline void push(int l, int r) { yzh.push({l, r}); }
	inline int top() {
		while (!check(yzh.top().l, yzh.top().r)) yzh.pop();
		return yzh.top().r - yzh.top().l + 1;
	}
} ans;

inline void add(int p) {
	ans.push(p, queryl(p, n));
}

inline void modify(int p, int v) {
	val[p] = v, yzh.modify(1, p, v);
	if (yzh.tree[1].val == all) {
		int x = min(p, yzh.find(1, 0));
		long long cur = 1ll << (val[p] - 1);
		add(x);
		while (x > 1) {
			x = yzh.find(1, 1, x - 1, cur);
			if (!~x) return;
			cur |= 1ll << (val[x] - 1), add(x);
		}
	}
}

signed main() {
	fread(buf, 1, MAX, stdin);
	read(n), read(k), read(m), all = (1ll << k) - 1;
	for (int i = 1; i <= n; ++i) read(val[i]);
	yzh.build(1, 1, n);
	for (int l = 1, r = 0, tot = 0; l <= n; ++l) {
		static int cnt[55];
		while (r < n && tot < k) tot += !cnt[val[++r]]++;
		if (!--cnt[val[l]] && r <= n && tot-- == k) ans.push(l, r);
	}
	for (int op, p, v; m--; ) {
		read(op);
		if (op == 1) {
			read(p), read(v), modify(p, v);
		} else {
			if (yzh.tree[1].val == all)
				write(ans.top()), putchar('\n');
			else
				putchar('-'), putchar('1'), putchar('\n');
		}
	}
	fwrite(obuf, 1, o - obuf, stdout);
	return 0;
}
```

---

