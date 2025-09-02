# [CCC 2025 Senior] 写作业 / To-Do List

## 题目背景

译自 CCC 2025 Senior T5。本题满分为 $15$。


## 题目描述


你的待办事项列表现在是空的。但是你需要处理 $q$ 次对待办事项列表的更新：

- $\texttt{A}$ $s$ $t$：

    向你的待办事项列表内加入一个任务：这个任务在第 $s$ 秒发布，需要 $t$ 秒完成。

- $\texttt{D}$ $x$：

    删除第 $x$ 个被加入的任务。

在每次操作后，求出最早能在什么时候完成列表中所有的任务。

一次只能完成一个任务。**一旦开始一个任务，必须一口气完成**，不能中途去做别的任务。

为了锻炼你的水平，我们会使用一些手段让你**在线**处理更新。


## 说明/提示



#### 样例解释

- 样例 $1$ 解释：

加密前的样例 $1$ 为

```plain
6
A 3 3
A 7 5
A 4 3
D 1
A 8 2
D 2
```

 
- 在第一次更新后，我们可以在第二秒的开始时开始第一次任务，并在第五秒的结束时完成（区间 $[3, 5]$）。  
- 在第二次更新后，我们可以在区间 $[3, 5]$ 上完成第一次任务，在区间 $[7, 11]$ 上完成第二次任务。  
- 在第三次更新后，我们可以在区间 $[3, 5]$ 上完成第一次任务，在区间 $[6, 8]$ 上完成第三次任务，然后在区间 $[9, 13]$ 上完成第二次任务。  
- 在第四次更新后，我们可以在区间 $[4, 6]$ 上完成第三次任务，在区间 $[7, 11]$ 上完成第二次任务。  
- 在第五次更新后，我们可以在区间 $[4, 6]$ 上完成第三次任务，在区间 $[7, 11]$ 上完成第二次任务，然后在区间 $[12, 13]$ 上完成第四次任务。  
- 在第六次更新后，我们可以在区间 $[4, 6]$ 上完成第三次任务，在区间 $[8, 9]$ 上完成第四次任务。  



- 样例 $2$ 解释：

加密前的样例 $2$ 为
```plain
2
A 1000000 1000000
A 1000000 1000000
```
#### 子任务

对于 $100\%$ 的数据，保证：

- $1\le q\le 10^6$；
- $1\le s,t\le 10^6$；
- 不会删除不存在（或已被删除）的任务。
- 在每次更新后，列表中至少有一个任务。

---

- $\text{Subtask 0(0 points)}$：样例。
- $\text{Subtask 1(2 points)}$：$q\le 3000$。
- $\text{Subtask 2(6 points)}$：只有第一种更新。
- $\text{Subtask 3(7 points)}$：无额外限制。

## 样例 #1

### 输入

```
6
A 3 3
A 2 0
A 999996 999995
D 999991
A 1000000 999994
D 999992```

### 输出

```
5
11
13
11
13
9```

## 样例 #2

### 输入

```
2
A 1000000 1000000
A 4 4```

### 输出

```
1999999
2999999```

# 题解

## 作者：chenly8128 (赞：7)

赛时想出来怎么做已经晚了，时间不够写了。
### 知识点

- 线段树

### 思路

根据贪心思想，任意空闲时间点如果有任务，则立即开始任务，这么做一定不劣。

假定任务全部按照开始时间排好了顺序，总共有 $n$ 个任务，设任务 $x$ 是最后一个在发布时间**准时准点**开始的任务。由于一定有最早开始的任务，所以 $x$ 一定存在。

可以发现，此时的最短用时即为 $x$ 的开始时间，加上 $x$ 和它之后开始的任务的总用时。

为了避免统计最后一个 $x$ 在哪里（嫌麻烦），所以干脆把每一个任务都当作最后一个准时准点开始的任务，然后把计算出的结果取最大值，即为答案。答案为 $\max(s_i - 1 + \sum_{j=i}^{n} + t_j)$。

我们需要做的就是快速计算以上公式的值。

由于强制在线，且时间点个数不多，所以首选线段树。

- 对于每次增加任务，都将开始时间点和以前所有时间点的权值加上 $t$。如果开始的时间点目前没有别的开始任务，则在该时间点加上一个额外权值 $s-1$。
- 对于删除任务，采用逆的操作即可。
- 每次统计全局最大权值。

复杂度 $O(q \log n)$。

### 代码


```cpp
#include <bits/stdc++.h>
#define int long long
#define ls(i) ((i)<<1)
#define rs(i) ((i)<<1|1)
using namespace std;
const int MAXN = 1e6+10;
const int mod = 1e6+3;
int m,seg[(MAXN<<2)+100],lz[(MAXN<<2)+100];
string tmp;int s,t,x,last;
int l[MAXN],r[MAXN],cnt;
void pushdown(int i) {
	seg[ls(i)] += lz[i];
	seg[rs(i)] += lz[i];
	lz[ls(i)] += lz[i];
	lz[rs(i)] += lz[i];
	lz[i] = 0;
}
void pushup(int i) {
	seg[i] = max(seg[ls(i)],seg[rs(i)]);
}
void add (int begin,int end,int v,int l,int r,int i) {
	if (begin <= l && end >= r) {
		lz[i] += v;
		seg[i] += v;
		return;
	}
	pushdown(i);
	int mid = (l+r) >> 1;
	if (mid >= begin) add(begin,end,v,l,mid,ls(i));
	if (mid < end) add(begin,end,v,mid+1,r,rs(i));
	pushup(i);
}
int ct[MAXN];
signed main (void) {
	ios::sync_with_stdio(false);
	cin >> m;
	while (m--) {
		cin >> tmp;
		if (tmp[0] == 'A') {
			cin >> s >> t;
			l[++cnt] = s = (s+last) % mod;
			r[cnt] = t = (t+last) % mod;
			add(1,s,t,1,MAXN,1);
			add(s,s,ct[s]++ ? 0 : s-1,1,MAXN,1);
		}
		else if (tmp[0] == 'D') {
			cin >> x;
			x = (x+last) % mod;
			add(1,l[x],-r[x],1,MAXN,1);
			add(l[x],l[x],-(--ct[l[x]] ? 0 : l[x]-1),1,MAXN,1);
		}
		last = seg[1];
		cout << last << '\n';
	}
	return 0;
}
```

---

## 作者：wangyizhi (赞：6)

神奇 DS 题。

提供一个与众不同的大常数解法！！！

## 题目分析

根据生活经验，**优先做 $s$ 小的任务一定不劣**。

证明：设 $s_1<s_2$，则先做第 $1$ 个任务的时间为 $S_1=\max\{s_1+t_1+t_2,s_2+t_2\}$，先做第 $2$ 个任务的时间为 $S_2=\max\{s_2+t_2+t_1,s_1+t_1\}$。显然 $S_2=s_2+t_2+t_1>S_1$。证毕。

注意到**做任务的时间段可能会连在一起形成一个大段**，而**只有最后一个大段会影响答案**。设排好序后最后一个大段从 $k$ 开始，则答案为 $s_k+\sum_{i=k}t_i-1$。

记 $W_i=s_i+\sum_{j=i}^{n}t_i-1$。考虑这个 $W_k$ 有什么特别之处。摆结论：**$W_k$ 是所有 $W_i$ 中最大的**。

证明：对于 $i<k$，一定有 $W_i<W_k$，因为其中存在空的部分，如果计算的时候把它去掉了必定会使其减小。对于 $i>k$，一定有 $W_i\le W_k$，因为去掉第一段后可能导致后面的前移，会使其减小。

考虑用平衡树维护。对每个节点维护 $s_i,t_i$，子树内的 $W_i+1$ 的最大值，子树内的总和。`push_up` 应该比较简单了，详见代码实现。

## AC Code

```cpp
by wangyizhi(571247)
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
//bool Mst;
const int V=2e6+5;
mt19937 rnd(time(nullptr));
struct piii
{
	ll fi,se,th;
};
inline piii nxt(piii x){return {x.fi,x.se,x.th+1};}
inline piii pre(piii x){return {x.fi,x.se,x.th-1};}
bool operator==(piii x,piii y){return x.fi==y.fi&&x.se==y.se&&x.th==y.th;}
bool operator<(piii x,piii y)
{
	if(x.fi!=y.fi) return x.fi<y.fi;
	if(x.se!=y.se) return x.se<y.se;
	return x.th<y.th;
}
bool operator>(piii x,piii y)
{
	if(x.fi!=y.fi) return x.fi>y.fi;
	if(x.se!=y.se) return x.se>y.se;
	return x.th>y.th;
}
bool operator<=(piii x,piii y){return x==y||x<y;}
bool operator>=(piii x,piii y){return x==y||x>y;}
struct treap
{
	struct node
	{
		node *ch[2];
		int w;
		piii v; // fir:s sec:t
		ll ans,st; // ans:max{s+pret},st:sumt
		node(piii _v={0,0,0}){ch[0]=ch[1]=nullptr,w=rnd(),v=_v,ans=v.fi+v.se,st=v.se;}
		node(node &x){w=x.w,v=x.v,ans=x.ans,st=x.st;}
		void push_up()
		{
			ans=st=0;
			if(ch[1]!=nullptr) ans=max(ans,ch[1]->ans),st=ch[1]->st;
			ans=max(ans,v.fi+v.se+st),st+=v.se;
			if(ch[0]!=nullptr) ans=max(ans,ch[0]->ans+st),st+=ch[0]->st;
		}
	};
	node *rt;
	pair<node*,node*> split_val(piii v,node *cur)
	{
		if(cur==nullptr) return {nullptr,nullptr};
		else if(cur->v<=v)
		{
			auto tmp=split_val(v,cur->ch[1]);
			cur->ch[1]=tmp.first,cur->push_up();
			return {cur,tmp.second};
		}
		else
		{
			auto tmp=split_val(v,cur->ch[0]);
			cur->ch[0]=tmp.second,cur->push_up();
			return {tmp.first,cur};
		}
	}
	node *merge(node *u,node *v)
	{
		if(u==nullptr&&v==nullptr) return nullptr;
		else if(u==nullptr) return v;
		else if(v==nullptr) return u;
		else if(u->w<v->w)
		{
			u->ch[1]=merge(u->ch[1],v),u->push_up();
			return u;
		}
		else
		{
			v->ch[0]=merge(u,v->ch[0]),v->push_up();
			return v;
		}
	}
	void insert(piii v)
	{
		auto tmp=split_val(v,rt);
		node *nd=new node(v);
		rt=merge(merge(tmp.first,nd),tmp.second);
	}
	void erase(piii v)
	{
		auto tmp=split_val(v,rt);
		auto tmpl=split_val(pre(v),tmp.first);
		if(tmp.first==tmpl.second) tmp.first=nullptr;
		delete tmpl.second;
		tmpl.second=nullptr;
		rt=merge(tmpl.first,tmp.second);
	}
}tr;
const int N=1e6+5,p=1e6+3;
ll s[N],t[N];
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int q,cnt=0,x;
	ll lstans=0;
	char op;
	cin>>q;
	while(q--)
	{
		cin>>op;
		if(op=='A') cnt++,cin>>s[cnt]>>t[cnt],(s[cnt]+=lstans)%=p,(t[cnt]+=lstans)%=p,tr.insert({s[cnt],t[cnt],cnt});
		else if(op=='D') cin>>x,x=(x+lstans)%p,tr.erase({s[x],t[x],x});
		cout<<(lstans=tr.rt->ans-1)<<"\n",lstans%=p;
	}
	return 0;
}
```

---

## 作者：modfish_ (赞：2)

居然没有人写矩乘吗？（虽然本质是一样的）。

## 思路
考虑静态如何实现。不妨将任务按发布时间排序，显然按这个顺序做是最优的。从前往后扫描。记完成第 $1$ 至第 $i$ 个任务至少要到第 $f_i$ 秒，容易得出转移：

$$f_i=\max(f_{i-1}+1,s_i)+t_i-1$$

很显然可以用广义矩阵乘法优化。具体如下：

$$\begin{pmatrix}t_i & s_i+t_i-1\\-\infty & 0\end{pmatrix}\begin{pmatrix}f_{i-1}\\0\end{pmatrix}=\begin{pmatrix}f_i\\0\end{pmatrix}$$

每次操作相当于单点修改矩阵。直接在值域上建线段树，维护矩阵乘法即可。

一个问题是 $s_i$ 相同的如何处理，解决方法是直接把 $t_i$ 相加即可，因为这两个任务一起做肯定是不劣的。

时间复杂度 $O(q\log V)$，其中 $V=\max s_i$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e6 + 5;

struct matrix{
    ll a[2][2];
};
inline matrix operator * (const matrix &x, const matrix &y){
    matrix z;
    z.a[0][0] = max(x.a[0][0] + y.a[0][0], x.a[0][1] + y.a[1][0]);
    z.a[0][1] = max(x.a[0][0] + y.a[0][1], x.a[0][1] + y.a[1][1]);
    z.a[1][0] = max(x.a[1][0] + y.a[0][0], x.a[1][1] + y.a[1][0]);
    z.a[1][1] = max(x.a[1][0] + y.a[0][1], x.a[1][1] + y.a[1][1]);
    return z;
}
int cmd[maxn][2];

namespace seg{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
matrix pd[maxn << 2];
int val[maxn << 2];
void up(int x){
    pd[x] = pd[r(x)] * pd[l(x)];
}
void build(int x, int l, int r){
    if(l == r){
        pd[x].a[0][0] = 0, pd[x].a[0][1] = -1e9, pd[x].a[1][0] = -1e9, pd[x].a[1][1] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(l(x), l, mid), build(r(x), mid + 1, r);
    up(x);
}
void update(int x, int l, int r, int id, int k){
    if(l == r){
        val[x] += k;
        if(val[x] > 0) pd[x].a[0][0] = val[x], pd[x].a[0][1] = val[x] + l - 1;
        else pd[x].a[0][0] = 0, pd[x].a[0][1] = -1e9;
        return;
    }
    int mid = l + r >> 1;
    if(id <= mid) update(l(x), l, mid, id, k);
    else update(r(x), mid + 1, r, id, k);
    up(x);
}}

int main(){
    int q;
    scanf("%d", &q);
    ll lans = 0, p = 1e6 + 3;
    string s;
    int cnt = 0;
    seg::build(1, 1, 1e6);
    matrix res;
    res.a[0][0] = 1, res.a[0][1] = res.a[1][0] = res.a[1][1] = 0;
    for(int i = 1; i <= q; i ++){
        cin >> s;
        if(s == "A"){
            int s, t;
            scanf("%d %d", &s, &t);
            s = (1ll * s + lans) % p, t = (1ll * t + lans) % p;
            cmd[++ cnt][0] = s, cmd[cnt][1] = t;
            seg::update(1, 1, 1e6, s, t);
        }else{
            int x;
            scanf("%d", &x);
            x = (1ll * x + lans) % p;
            int s = cmd[x][0], t = cmd[x][1];
            seg::update(1, 1, 1e6, s, -t);
        }
        lans = max(seg::pd[1].a[0][0], seg::pd[1].a[0][1]);
        printf("%lld\n", lans);
    }
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：2)

首先发现这个任务显然是按 $s$ 从小到大做。

然后发现最后的时间肯定是从某个 $s$ 开始加上 $t$ 的后缀和然后 $-1$，设这个值为某个任务的**完成值**。

最后把每个任务都算一遍完成值，然后取 max 就是答案。

这里还是稍微证明一下吧：首先做任务的过程会分成很多段，每段都是从某个 $s$ 开始做一个区间中的任务。也就是说从最后一段的 $s$ 开始算得的完成值是最大的，也就是答案。

由于最后一段可以连续做，所以这一段中的 $s$ 一定不大于开始做这个任务的时刻，所以这一段中的任务算出的完成值不大于答案。

而最后一段之前的值，因为做完之后还会等一些时间才开始做最后一段的任务，所以完成值也不会大于答案。所以就得证了。

这个东西按 $s$ 开线段树维护即可（即把所有任务存在 $s$ 处）。

一个细节就是需要每次维护现在存在的任务的 $s$ 最大值 $maxs$，然后线段树查询时只查询 $1\sim maxs$。

时间复杂度 $O(W\log W)$，$W=10^6$ 是值域。

```cpp
#include<iostream>
#include<algorithm>
#include<set>
#define int long long
using namespace std;
const int mod=1e6+3;
int q,lastans;
multiset<int>se;
int s[1000010],t[1000010],cur;
struct segtree{int l,r,maxn,lazy;}a[4000010];
void pushup(int x)
{
    a[x].maxn=max(a[x*2].maxn,a[x*2+1].maxn)+a[x].lazy;
}
void build(int x,int l,int r)
{
    a[x].l=l,a[x].r=r;
    if(l==r)return;
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    pushup(x);
}
void add(int x,int l,int r,int k)
{
    if(a[x].l==l&&a[x].r==r)
    {
        a[x].maxn+=k;
        a[x].lazy+=k;
        return;
    }
    int mid=(a[x].l+a[x].r)/2;
    if(l<=mid)add(x*2,l,min(r,mid),k);
    if(r>mid)add(x*2+1,max(l,mid+1),r,k);
    pushup(x);
}
int query(int x,int l,int r)
{
    if(a[x].l==l&&a[x].r==r)return a[x].maxn;
    int mid=(a[x].l+a[x].r)/2,ret=0;
    if(l<=mid)ret=max(ret,query(x*2,l,min(r,mid)));
    if(r>mid)ret=max(ret,query(x*2+1,max(l,mid+1),r));
    return ret+a[x].lazy;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>q;
    build(1,1,1e6);
    for(int i=1;i<=1e6;i++)add(1,i,i,i);
    while(q--)
    {
        char op;
        cin>>op;
        if(op=='A')
        {
            cur++;
            cin>>s[cur]>>t[cur];
            s[cur]=(s[cur]+lastans)%mod;
            t[cur]=(t[cur]+lastans)%mod;
            se.insert(s[cur]);
            add(1,1,s[cur],t[cur]);
        }
        else
        {
            int x;
            cin>>x;
            x=(x+lastans)%mod;
            add(1,1,s[x],-t[x]);
            auto pos=se.lower_bound(s[x]);
            se.erase(pos);
        }
        int maxs=*prev(se.end());
        lastans=query(1,1,maxs)-1;
        cout<<lastans<<'\n';
    }
    return 0;
}
```

---

## 作者：SunburstFan (赞：1)

## [P11861 [CCC 2025 Senior] 写作业 / To-Do List](https://www.luogu.com.cn/problem/P11861)

### 题目大意

维护一个待办任务列表，支持两种加密更新操作：
- `A s t`：添加一个任务（发布时间 $s$，所需时间 $t$）
- `D x`：删除第 $x$ 个加入的任务  
每次更新后，求最早完成所有任务的时刻（任务必须按顺序连续完成）。

### 解题思路
利用线段树维护时间区间的累积值，支持区间加法更新。

对于每次任务添加或删除，通过更新相应区间来调整整体完成时间（即树根的最大值）。

每次操作均为 $O(\log N)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6+5;
const int mod=1e6+3;

int m,seg[(N<<2)+100],lz[(N<<2)+100];
string tmp;int s,t,x,last;
int l[N],r[N],cnt;

namespace seg_tree{
	void pushdown(int rt){
		seg[rt<<1]+=lz[rt];
		seg[rt<<1|1]+=lz[rt];
		lz[rt<<1]+=lz[rt];
		lz[rt<<1|1]+=lz[rt];
		lz[rt]=0;
	}
	void pushup(int rt){
		seg[rt]=max(seg[rt<<1],seg[rt<<1|1]);
	}
	void add(int L,int R,int v,int l,int r,int rt){
		if(L<=l&&R>=r){
			lz[rt]+=v;
			seg[rt]+=v;
			return;
		}
		pushdown(rt);
		int mid=(l+r)>>1;

		if(mid>=L)add(L,R,v,l,mid,rt<<1);
		if(mid<R)add(L,R,v,mid+1,r,rt<<1|1);

		pushup(rt);
	}
}
using namespace seg_tree;

int ct[N];

signed main(){
    ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

    cin>>m;
    while(m--){
        cin>>tmp;

        if(tmp[0]=='A'){
            cin>>s>>t;
            l[++cnt]=s=(s+last)%mod;
            r[cnt]=t=(t+last)%mod;

            add(1,s,t,1,N,1);
            add(s,s,ct[s]++?0:s-1,1,N,1);
        }

        else if(tmp[0]=='D'){
            cin>>x;
            x=(x+last)%mod;

            add(1,l[x],-r[x],1,N,1);
            add(l[x],l[x],-(--ct[l[x]]?0:l[x]-1),1,N,1);
        }

        last=seg[1];
        cout<<last<<'\n';
    }
    return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

最优策略下，第一个开始做的任务一定是准时开始的。若我们决定第一个做任务 $i$，那么总用时即为 $s_i-1+\sum_{j=i}^{n}t_j$，答案即为 $\max(s_i-1+\sum_{j=i}^{n}t_j)$。

用一颗线段树维护每一位开始的总和。插入新任务 $(s,t)$ 时，给 $[1,s]$ 加上 $t$。若目前它是第一个在时间 $s$ 开始的任务，则额外给 $[s,s]$ 加上 $s-1$。删除操作取反即可。

```cpp
const ll N=1e6+10,mod=1e6+3;
ll Q,last,sgtr[N*4],lz[N*4],cnt[N];
vector<ll> ss,tt;

ll ls(ll p){
	return p*2;
}

ll rs(ll p){
	return p*2+1;
}

void pushdown(ll p){
	sgtr[ls(p)]+=lz[p];
	sgtr[rs(p)]+=lz[p];
	lz[ls(p)]+=lz[p];
	lz[rs(p)]+=lz[p];
	lz[p]=0;
}

void pushup(ll p){
	sgtr[p]=max(sgtr[ls(p)],sgtr[rs(p)]);
}

void upd(ll p,ll l,ll r,ll ql,ll qr,ll v){
	if(r<ql or l>qr) return;
	
	if(ql<=l and r<=qr){
		sgtr[p]+=v;
		lz[p]+=v;
	}else{
		if(lz[p]) pushdown(p);
		
		ll mid=(l+r)/2;
		upd(ls(p),l,mid,ql,qr,v);
		upd(rs(p),mid+1,r,ql,qr,v);
		pushup(p);
	}
}

int main(){
	ss.pb(-1);
	tt.pb(-1);
	cin>>Q;
	
	count(Q){
		char ty;
		cin>>ty;
		
		if(ty=='A'){
			ll s,t;
			cin>>s>>t;
			s=(s+last)%mod;
			t=(t+last)%mod;
//			cout<<"s="<<s<<",t="<<t<<'\n';
//			pause;
			ss.pb(s);
			tt.pb(t);
			upd(1,1,N,1,s,t);
			
			if(cnt[s]==0) upd(1,1,N,s,s,s-1);
				
			cnt[s]++;
		}else{
			ll x;
			cin>>x;
			x=(x+last)%mod;
//			cout<<"x="<<x<<'\n';
			upd(1,1,N,1,ss[x],-tt[x]);
			cnt[ss[x]]--;
			
			if(cnt[ss[x]]==0) upd(1,1,N,ss[x],ss[x],1-ss[x]);
		}
		
		last=sgtr[1];
		cout<<last<<'\n';
	}
}
```

---

## 作者：Coffee_zzz (赞：0)

设 $n$ 表示任务的数量，$s_i$ 表示第 $i$ 个任务的发布时刻，$t_i$ 表示完成第 $i$ 个任务所需的时间。  

我们首先考虑单次询问怎么做。容易想到一个策略是，直接把所有任务按照 $s_i$ 从小到大排序，设初始时的时刻为 $0$，依次做每个任务，遇到当前时刻小于 $s_i$ 的情况就直接把当前时刻跳到 $s_i+t_i-1$，否则把当前时刻增加 $t_i$，正确性显然。

接下来我们考虑一个更优美的做法。我们考虑最后一次出现「当前时刻小于 $s_k$」的情况的位置 $k$，则答案 $ans$ 可以表示为 $s_k-1+\sum_{s_k\le s_i} t_i$。注意到，对于所有的 $1 \le x \lt s_k$，由于在进行第 $k$ 个任务前一定有一段空闲时间，所以 $x-1+\sum_{x\le s_i} t_i$ 一定小于 $ans$；同时，对于所有的 $s_k \lt x \le s_n$，由于在进行第 $k$ 个任务后一定没有空闲时间，所以 $x-1+\sum_{x\le s_i} t_i$ 一定不大于 $ans$。于是我们惊奇地发现，$ans=\max\limits_{x=1}^{s_n} \left(x-1+\sum_{x \le s_i} t_i\right)$！！！

在这个形式下，多次询问的答案就变得容易维护了许多。设 $w_x=x-1+\sum_{x \le s_i} t_i$，于是我们可以用一棵线段树维护 $w$ 的值。初始时令 $w_i=i-1$，每次加入一个任务时给 $w_1 \sim w_{s_i}$ 增加 $t_i$，删除一个任务时给 $w_1 \sim w_{s_i}$ 减少 $t_i$，答案即为 $w_1 \sim w_{s_n}$ 的最大值，其中 $s_n$ 可以用 multiset 维护。

我们认为 $q,s,t$ 同阶，则时间复杂度为 $\mathcal O(q \log q)$。

---

## 作者：Purslane (赞：0)

# Solution

把所有作业按照 $s$ 排序后，答案显然是：

$$
\max_{1 \le i \le n} s_i + \sum_{j \ge i} t_j
$$

使用平衡树维护即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,rt;
struct Node {int ls,rs,key,sum,s,t,ans,fa;}t[MAXN];
mt19937 myrand(time(NULL));
void push_up(int u) {return t[t[u].ls].fa=t[t[u].rs].fa=u,t[u].sum=t[t[u].ls].sum+t[t[u].rs].sum+t[u].t,t[u].ans=max({t[t[u].rs].ans,t[t[u].ls].ans+t[u].sum-t[t[u].ls].sum,t[u].s+t[u].sum-t[t[u].ls].sum}),void();}
void split(int u,int v,int &p,int &q) {
	if(!u) return p=q=0,void();
	if(t[u].s<=v) return p=u,split(t[u].rs,v,t[u].rs,q),push_up(u),void();
	return q=u,split(t[u].ls,v,p,t[u].ls),push_up(u),void();
}
int merge(int u,int v) {
	if(!u||!v) return u|v;
	if(t[u].key<=t[v].key) return t[u].rs=merge(t[u].rs,v),push_up(u),u;
	return t[v].ls=merge(u,t[v].ls),push_up(v),v;
}
void del(int id) {
	if(rt==id) return rt=merge(t[id].ls,t[id].rs),t[rt].fa=0,void();	
	if(t[t[id].fa].ls==id) {
		int f=t[id].fa;
		t[f].ls=merge(t[id].ls,t[id].rs);
		while(f) push_up(f),f=t[f].fa;	
	}
	else {
		int f=t[id].fa;
		t[f].rs=merge(t[id].ls,t[id].rs);
		while(f) push_up(f),f=t[f].fa;	
	}
	t[rt].fa=0;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	int p=1000003,lstans=0,cnt=0;
	ffor(i,1,n) {
		char ch;
		cin>>ch;
		if(ch=='A') {
			int ss,tt;
			cin>>ss>>tt,cnt++;
			ss=(ss+lstans)%p,tt=(tt+lstans)%p;
			int A,B;
			split(rt,ss,A,B);
			t[cnt]={0,0,myrand(),tt,ss,tt,ss+tt,0};
			rt=merge(merge(A,cnt),B);
			t[rt].fa=0;
		}
		else {
			int x;
			cin>>x;
			x=(x+lstans)%p;
			del(x);
		}
		cout<<(lstans=t[rt].ans-1)<<'\n';
	}
	return 0;
}
```

---

