# Lena and Queries

## 题目描述

Lena is a programmer. She got a task to solve at work.

There is an empty set of pairs of integers and $ n $ queries to process. Each query is one of three types:

1. Add a pair $ (a,b) $ to the set.
2. Remove a pair added in the query number $ i $ . All queries are numbered with integers from $ 1 $ to $ n $ .
3. For a given integer $ q $ find the maximal value $ x·q+y $ over all pairs $ (x,y) $ from the set.

Help Lena to process the queries.

## 样例 #1

### 输入

```
7
3 1
1 2 3
3 1
1 -1 100
3 1
2 4
3 1
```

### 输出

```
EMPTY SET
5
99
5
```

# 题解

## 作者：Flying2018 (赞：14)

## [原题链接](http://codeforces.com/problemset/problem/678/F)

## 题目大意
$n$ 次操作，支持：
1. 插入一个点 $(a_i,b_i)$。
2. 删除一个点 $i$。
3. 当前集合中 $a_ix+b_i$ 最大值是多少。

## 题解

首先可以发现：

$$a_1x+b_1\leq a_2x+b_2(a_1<a_2)$$
$$\Leftrightarrow (a_1-a_2)x\leq b_2-b_1$$
$$\Leftrightarrow -x\leq \frac{b_1-b_2}{a_1-a_2}$$

可以发现这等价于两点之间的斜率（的相反数）。

也就是说，随着 $x$ 的增长可以看成一条斜率为 $-x$ 的直线去切这个凸包。

一种很明显的方式是直接维护上凸包，二分斜率。

但是这样需要平衡树，而且很难写。

按照套路，我们把操作离线，然后使用线段树分治，把每个点有效的区间插入到对应的线段树节点上。

然后我们把所有线段树上的点建出对应的凸包。直接暴力二分斜率就可以做到 $O(n\log^2 n)$。

考虑优化。首先建凸包的部分瓶颈在于排序。而我们对每个点都求一遍排序，复杂度会变成 $O(n\log^2 n)$。

但是我们发现我们只插入 $O(n)$ 种不同的点，那么我们完全可以把这些点离线排好序，再依次插入。这样复杂度就是 $O(n\log n)$ 的。

然后考虑处理二分部分的瓶颈。可以发现，实际上随着 $x$ 的增大，凸包上关键点的移动一定是单调的。所以我们可以把询问离线，然后按 $x$ 递增顺序处理，每次贪心找到峰值，这样凸包上每个点最多访问一次，复杂度 $O(\text{凸包上点数}+n\log n)=O(n\log n)$。

这样总复杂度 $O(n\log n)$。

但众所周知运行效率与理论复杂度没有关系，上述实现方式常数巨大，直接被 $O(n\log^2 n)$ 吊打。。。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 300010
#define inf 2000000000000000000
#define ll long long
#pragma GCC optimize(2,3)
using namespace std;
struct node{
    ll x,y;
    node(ll X=0,ll Y=0):x(X),y(Y){}
    node operator +(node a){return node(x+a.x,y+a.y);}
    node operator -(node a){return node(x-a.x,y-a.y);}
    ll operator *(node a){return x*a.y-y*a.x;}
    bool operator <(const node a)const{return x==a.x?y<a.y:x<a.x;}
};
ll cross(node a,node o,node b){return (a-o)*(b-o);}
node tmp[N];
ll calc(node a,ll k){return a.x*k+a.y;}
struct convex{
    vector<node>v;
    int pos;
    void push(node a){v.push_back(a);}
    void init()
    {
        int t=0;pos=0;
        for(node u:v)
        {
            while(t>1 && cross(tmp[t-1],tmp[t],u)<=0) --t;
            tmp[++t]=u;
        }
        v.clear();
        for(int i=1;i<=t;i++) v.push_back(tmp[i]);
    }
    ll answer(ll k)
    {
        if(v.empty()) return -inf;
        if(pos+1==v.size()) return calc(v[pos],k);
        while(pos+1<v.size() && calc(v[pos],k)<=calc(v[pos+1],k)) pos++;
        return calc(v[pos],k);
    }
}t[N<<2];
void insert(int u,int l,int r,int L,int R,node v)
{
    if(L<=l && r<=R){t[u].push(v);return;}
    int mid=(l+r)>>1;
    if(L<=mid) insert(u<<1,l,mid,L,R,v);
    if(R>mid) insert(u<<1|1,mid+1,r,L,R,v);
}
ll answer(int u,int l,int r,int p,ll v)
{
    ll ans=t[u].answer(v);
    if(l==r) return ans;
    int mid=(l+r)>>1;
    if(p<=mid) return max(ans,answer(u<<1,l,mid,p,v));
    else return max(ans,answer(u<<1|1,mid+1,r,p,v));
}
struct ques{
    int p;ll k,ans;
    bool operator <(const ques a)const{return k<a.k;}
}q[N];
bool cmp(ques a,ques b){return a.p<b.p;}
int qt=0;
struct nodes{
    node p;int l,r;
    bool operator <(const nodes a)const{return p<a.p;}
}rem[N];
bool has[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int opt;ll x,y;
        scanf("%d%lld",&opt,&x);
        if(opt==1)
        {
            scanf("%lld",&y);
            rem[i].p=node(x,y);has[i]=true;
            rem[i].l=i;
        }
        else if(opt==2) rem[x].r=i,has[x]=false;
        else q[++qt]=(ques){i,x};
    }
    for(int i=1;i<=n;i++) if(has[i]) rem[i].r=n;
    sort(rem+1,rem+n+1);
    for(int i=1;i<=n;i++)
    if(rem[i].r) insert(1,1,n,rem[i].l,rem[i].r,rem[i].p);
    for(int i=1;i<=2*n-1;i++) t[i].init();
    sort(q+1,q+qt+1);
    for(int i=1;i<=qt;i++) q[i].ans=answer(1,1,n,q[i].p,q[i].k);
    sort(q+1,q+qt+1,cmp);
    for(int i=1;i<=qt;i++)
    if(q[i].ans<=-inf) puts("EMPTY SET");
    else printf("%lld\n",q[i].ans);
    return 0;
}
```

---

## 作者：include_BM (赞：9)

如果没有删除操作，每个点对看作线段，那么这道题就是[李超树](https://oi-wiki.org/ds/li-chao-tree/)板子，但是李超树不支持删除。

考虑线段树分治。

按时间开一颗线段树，每个节点维护一个动态开点李超树，同时记录每条线段存在的时间，若存在时间为 $[l_i,r_i]$，就给 $[l_i,r_i]$ 这段时间所对应的线段树区间上的所有李超树插入这条线段。

查询时只需要查询线段树从根到当前时间对应的叶子这条链上的所有李超树，取最大值即可。

由于每次插入最多只会影响到线段树上 $O(\log n)$ 个节点，一颗李超树每插入一条线段最多只会新增一个节点，所以这样做的空间复杂度为 $O(n\log n)$，时间复杂度 $O(n\log n\log V)$，其中 $V$ 为值域大小。

```cpp
const int N=3e5+10;
int n,op[N],k[N],b[N],l[N],r[N],ans[N],rt[N<<2],tot,pos[N];
struct node{
    int ls,rs,id;
}tr[N*40];

inline ll at(int i,int x){return (ll)k[i]*x+b[i];}

#define mid ((l+r)>>1)
void chg(int &x,int l,int r,int p){
    if(!x) x=++tot;
    if(!tr[x].id) return tr[x].id=p,void();
    if(at(p,mid)>at(tr[x].id,mid)) swap(p,tr[x].id);
    if(at(p,l)>at(tr[x].id,l)) chg(tr[x].ls,l,mid,p);
    if(at(p,r)>at(tr[x].id,r)) chg(tr[x].rs,mid+1,r,p);
}
ll que(int x,int l,int r,int p){
    if(!x) return LLONG_MIN; if(l==r) return at(tr[x].id,p);
    return max(p<=mid?que(tr[x].ls,l,mid,p):que(tr[x].rs,mid+1,r,p),at(tr[x].id,p));
}

#define ls (x<<1)
#define rs (x<<1|1)
void build(int x,int l,int r){
    if(l==r) return pos[l]=x,void(); build(ls,l,mid),build(rs,mid+1,r);
}
void chg(int x,int l,int r,int p,int q,int k){
    if(l==p&&r==q) return chg(rt[x],-1e9,1e9,k);
    if(q<=mid) chg(ls,l,mid,p,q,k);
    else if(p>mid) chg(rs,mid+1,r,p,q,k);
    else chg(ls,l,mid,p,mid,k),chg(rs,mid+1,r,mid+1,q,k);
}

signed main(){
    n=read(),build(1,1,n);
    for(int i=1;i<=n;++i){
        op[i]=read();
        if(op[i]==1) k[i]=read(),b[i]=read(),l[i]=i,r[i]=n;
        else if(op[i]==2) r[read()]=i; else k[i]=read();
    }
    for(int i=1;i<=n;++i) if(op[i]==1) chg(1,1,n,l[i],r[i],i);
    for(int i=1;i<=n;++i) if(op[i]==3){
        ll ans=LLONG_MIN;
        for(int x=pos[i];x;x>>=1) ans=max(ans,que(rt[x],-1e9,1e9,k[i]));
        ans==LLONG_MIN?puts("EMPTY SET"):printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：xyloph0nex17 (赞：3)

本题的三个操作可以分别看作：
- $1$：在集合中加入一条斜率为 $x$，纵截距为 $y$ 的直线。
- $2$：删除集合中的一条直线。
- $3$：求此时所有集合中所有直线在 $k$ 处的最大值。  

操作 $1,3$ 均容易用李超线段树维护，但李超线段树难以进行删除操作，因为本题没有要求强制在线，考虑离线乱搞。  
发现在 $t1$ 时刻加入一条线段与在 $t2$ 时刻删除一条线段可以看成在 $[t1,t2]$ 时间内加入一条线段。于是我们可以大力树套树，外层以时间为下标建立线段树，在线段树上的每一个节点处建一棵动态开点李超树，先将所有线段挂在线段树上，再依次查询即可。  
因为动态开点李超树的节点数与插入的线段数相等，此时的空间为 $O(n \log n)$ 级别，已经足以通过本题。  
但如果我们采用一些线段树分治的思想，此时还可以将空间进一步优化。将某一区间内的所有询问一次处理完，此时该区间及其子区间内的李超树均没有机会再用到了，便可以将节点回收。此时只有线段树上的某一叶子到根路径上的节点分别存有一棵李超树，根据线段树的性质可知一条线段至多在这些 $ \log n $ 个节点中的一个上的李超树所插入，此时空间是非常优秀的 $O(n)$ 级别。  
时间复杂度为 $O(n \log n \log V)$，$V$ 为值域。  

## code
```cpp
//by xyloph0nex17
#include<bits/stdc++.h>
#define ri int
#define db double
#define mid ((l + r) >> 1)
#define pb push_back
#define pii pair<int,int>
#define ll long long
#define int long long
const int N = 3e5 + 10 ;
const int M = 1e6 + 10 ;
const ll inf = 9e18 ;
const int mod = 998244353 ;
using namespace std ;
template <typename T>
inline void read(T&x){
	x = 0 ; bool flg = 1 ; char c = getchar() ;
	while(c > '9' || c < '0'){
		if(c == '-')
		flg = 0 ;
		c = getchar() ;
	}
	while(c >= '0' && c <= '9'){
		x = (x << 1) + (x << 3) + (c ^ 48) ;
		c = getchar() ;
	}
	x = flg ? x : -x ;
}
int rt[N<<2],n ;
ll ans[N] ;
vector<int>vc[N<<2] ;
struct qs{int pos,k;};
vector<qs>q[N<<2] ;
struct node{
	int id,ls,rs ;
	inline void clear(){id=ls=rs=0;}
}tr[N*10] ;
int trn,stk[N],top ;
int newnode(){if(top)return tr[stk[top]].clear(),stk[top] ; else return ++trn ;}
struct line{
	ll k,b,l,r ;
	ll val(int x){return k * x + b ;}
}L[N] ;
void chg2(int &x,int l,int r,int id){
	if(!x)x = ++trn , tr[x].clear() ;
	if(!tr[x].id)return tr[x].id=id,void() ;
	else{
		int pid = tr[x].id ;
		if(L[pid].val(mid) < L[id].val(mid)){
			tr[x].id = id ;
			if(L[pid].val(l) > L[id].val(l))chg2(tr[x].ls,l,mid,pid) ;
			if(L[pid].val(r) > L[id].val(r))chg2(tr[x].rs,mid+1,r,pid) ;
		}
		else{
			if(L[id].val(l) > L[pid].val(l))chg2(tr[x].ls,l,mid,id) ;
			if(L[id].val(r) > L[pid].val(r))chg2(tr[x].rs,mid+1,r,id) ;
		}
	}
}
ll qry2(int x,int l,int r,int pos){
	if(!tr[x].id)return -inf ;
	if(pos <= mid)return max(L[tr[x].id].val(pos),qry2(tr[x].ls,l,mid,pos)) ;
	else return max(L[tr[x].id].val(pos),qry2(tr[x].rs,mid+1,r,pos)) ; 
}
#define ls x << 1
#define rs x << 1 | 1
void chg1(int x,int l,int r,int L,int R,int k){
	if(L <= l && r <= R)return vc[x].pb(k),void() ;
	if(L <= mid)chg1(ls,l,mid,L,R,k) ;
	if(mid < R)chg1(rs,mid+1,r,L,R,k) ;
}
void add(int x,int l,int r,int pos,int k){
	q[x].pb({pos,k}) ;
	if(l == r)return ;
	if(pos <= mid)add(ls,l,mid,pos,k) ;
	else add(rs,mid+1,r,pos,k) ;
}
void qry1(int x,int l,int r){
	if(!q[x].size())return ;
	int tmp = trn ;
	for(ri i = 0 ; i < (int)vc[x].size() ; i++)chg2(rt[x],-1e9,1e9,vc[x][i]) ;
	for(ri i = 0 ; i < (int)q[x].size() ; i++)ans[q[x][i].pos] = max(ans[q[x][i].pos],qry2(rt[x],-1e9,1e9,q[x][i].k)) ;
	if(l == r){if(ans[l]==-inf)puts("EMPTY SET");else printf("%lld\n",ans[l]); return;}
	qry1(ls,l,mid),qry1(rs,mid+1,r) ;
	trn = tmp ;
}
#undef ls
#undef rs
signed main(){
	read(n) ;
	for(ri i = 1 , opt , k , b ; i <= n ; i++){
		read(opt) ;
		if(opt == 1)read(k),read(b),L[i].k = k,L[i].b=b,L[i].l=i,L[i].r=n ;
		else if(opt == 2)read(k),L[k].r = i - 1 ;
		else read(k),add(1,1,n,i,k),ans[i]=-inf ;
	}
	for(ri i = 1 ; i <= n ; i++)if(L[i].l==i)chg1(1,1,n,L[i].l,L[i].r,i) ;
	qry1(1,1,n) ;
	return 0 ;
}
```

---

## 作者：Rorschachindark (赞：3)

# Lena and Queries
[题目传送门](https://www.luogu.com.cn/problem/CF678F)
## 题目大意
$n$个操作:

1. 添加一对$(x,y)$进入集合

2. 删除第$k$个操作所添加的数对，保证第$k$个操作是操作1且对应的数对未被删除

3. 给定参数$k$求集合中$kx+y$的最大值

## 思路
我这道题因为$\text {static int}$的一个细节问题$\text {WA}$ $n^+$次，差点自闭了，只好把网上的题解魔改成自己的代码的样子，在错了$12$次终于发现锅了。。。

开始正言吧。首先不难想到的就是斜率优化了，我们发现对于这个东西直接维护一个凸包就好了。

好了，问题就来了，如何维护呢？一开始我sx地以为直接用平衡树维护斜率就好了。结果，发现加入点的时候就不好维护了。

实际上，我们可以离线下来用线段树分治解决。这样我们就很好维护凸包了。

那如何查询答案呢？因为这是凸包，所以我们如果要算一个时间段的答案就直接三分就好了。因为我们的答案实际上算$[1,x]$这个时间段的答案，所以直接线段树上二分就好了，常数会少一些。结果时间还是被一堆巨佬吊打。。。

于是时间复杂度为$\Theta(n\log^2 n)$（假设$n,m$同阶）。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define int long long
#define MAXN 300010
#define INF 2e18 

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

struct Node{
	int x,y;
	int f (int k){
		return x * k + y;
	}
	bool operator < (const Node &p)const{
		return x != p.x ? x < p.x : y < p.y;
	}
};

int n,cnt;
int q[MAXN][3],opt[MAXN][3];

vector <Node> Tree[MAXN << 1];

void update (int l,int r,int tl,int tr,Node oo){
	int p = (l + r) | (l != r);
	if (l >= tl && r <= tr)	return Tree[p].push_back (oo);
	int mid = (l + r) >> 1;
	if (tl <= mid) update (l,mid,tl,tr,oo);
	if (tr > mid) update (mid + 1,r,tl,tr,oo);
} 

bool check (vector <Node> &t,int i,int j,int k){
	return ((t[i].y - t[j].y) * (t[k].x - t[i].x) >= (t[i].y - t[k].y) * (t[j].x - t[i].x));
}

void maintain (vector <Node> &t){
	static int S[MAXN],size;vector <Node> tmp;
	sort (t.begin(),t.end());
	size = 0;
	for (Int i = 0;i < t.size();++ i){
		while ((size && t[S[size]].x == t[i].x) || (size > 1 && check (t,S[size - 1],S[size],i))) size --;
		S[++ size] = i;
	}
	for (Int i = 1;i <= size;++ i) tmp.push_back (t[S[i]]);
	t = tmp;
}

int get (int k,int id){
	if (!Tree[id].size()) return -INF;
	int l = 0,r = Tree[id].size() - 1;
	while (l < r){
		int mid = (l + r) >> 1;
		if (Tree[id][mid].f (k) > Tree[id][mid + 1].f (k)) r = mid;
		else l = mid + 1;
	}
	return Tree[id][l].f (k);
}

int calc (int l,int r,int k,int pos){
	int res = -INF;
	while (l < r){
		int p = (l + r) | (l != r),mid = (l + r) >> 1;
		res = max (res,get (k,p));
		if (pos <= mid) r = mid;
		else l = mid + 1;
	}
	return res = max (res,get (k,(l + r) | (l != r)));
}

signed main(){
	read (n);
	for (Int i = 1,op;i <= n;++ i){
		read (op,opt[i][1]);
		if (op == 1) read (opt[i][2]);
		else if (op == 2){
			int x = opt[i][1];
			update (1,n,x,i,Node {opt[x][1],opt[x][2]});
			opt[x][1] = opt[i][1] = INF;
		}
		else{
			q[++ cnt][1] = opt[i][1];
			q[cnt][2] = i,opt[i][1] = INF;
		}
	}
	for (Int i = 1;i <= n;++ i) if (opt[i][1] != INF) update (1,n,i,n,Node {opt[i][1],opt[i][2]});
	for (Int i = 1;i <= (n << 1);++ i)  if (Tree[i].size()) maintain (Tree[i]);
	for (Int i = 1;i <= cnt;++ i){
		int res = calc (1,n,q[i][1],q[i][2]);
		if (res == -INF) puts ("EMPTY SET");
		else write (res),putchar ('\n');
	}
	return 0;
}
```

---

## 作者：Prean (赞：2)

首先题意中的有撤销操作，直接李超树肯定不行，题目允许离线，所以考虑线段树分治

所以问题就变成了求一次函数最大值

这不是李超树板子吗？？？

然后可以对每个节点都建立动态开点李超树，查询的时候直接从叶子节点跳到根节点就好了

但是直接这样做的话时空复杂度都是 $ O(n\log n\log V) $ 的，空降将近 1.2GB，会被直接卡掉

优化就是，只保留目前节点到根节点的节点的李超树（因为只有这些用得上），然后在 $ O(\log n) $ 个李超树中查询，空间复杂度就变成了 $ O(n\log V) $。如果想跑得快一点儿的话可以把李超树可持久化，虽然说复杂度仍然是 $ O(n\log n\log V) $ 的。

不过我倒是可持久化了，感觉码量都差不多（

吐槽一下，为啥李超树的效率和维护凸包的效率差不多啊（
```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
typedef long long ll;
const int M=3e5+5,V=1e9;
const ll INF=0x7fffffffffffffff;
int n,tot,root,k[M],opt[M],t[M*50],chi[M*50][2];ll ans[M];
std::vector<int>id[M<<2];
struct line{
	int k,b;
	line(const int&x=0,const int&y=0):k(k),b(b){}
	inline ll get(const int&x)const{
		return 1ll*k*x+b;
	}
}p[M];
inline void swap(int&a,int&b){
	int c=a;a=b;b=c;
}
inline ll max(const ll&a,const ll&b){
	return a>b?a:b;
}
int Modify(int u,int id,int L=0,int R=V*2){
	if(!u)return t[++tot]=id,tot;
	int mid=(1ll*L+R)*.5,now=++tot;
	t[now]=t[u];chi[now][0]=chi[u][0];chi[now][1]=chi[u][1];
	if(p[id].get(mid-V)>p[t[now]].get(mid-V))swap(id,t[now]);
	if(p[t[now]].get(L-V)>p[id].get(L-V)&&p[t[now]].get(R-V)>p[id].get(R-V))return now;
	if(p[id].get(L-V)>p[t[now]].get(L-V))return chi[now][0]=Modify(chi[u][0],id,L,mid),now;
	else return chi[now][1]=Modify(chi[u][1],id,mid+1,R),now;
}
ll Query(int u,int x,int L=0,int R=V*2){
	if(!u)return-INF;
	if(L==R)return p[t[u]].get(x-V);
	int mid=(1ll*L+R)*.5;
	if(x<=mid)return max(p[t[u]].get(x-V),Query(chi[u][0],x,L,mid));
	else return max(p[t[u]].get(x-V),Query(chi[u][1],x,mid+1,R));
}
void modify(int u,int d,int l,int r,int L=1,int R=n){
	if(l>R||L>r)return;
	if(l<=L&&R<=r)return id[u].push_back(d);
	int mid=L+R>>1;
	modify(u<<1,d,l,r,L,mid);modify(u<<1|1,d,l,r,mid+1,R);
}
void Solve(int u=1,int L=1,int R=n){
	int lroot=root,ltot=tot;
	for(int&L:id[u])root=Modify(root,L);
	if(L<R){
		int mid=L+R>>1;
		Solve(u<<1,L,mid);Solve(u<<1|1,mid+1,R);
	}
	else if(opt[L]==3)ans[L]=root?Query(root,k[L]+V):-INF;
	while(tot>ltot)chi[tot][0]=chi[tot][1]=t[tot]=0,--tot;root=lroot;
}
signed main(){
	register int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		scanf("%d",opt+i);
		if(opt[i]==1)scanf("%d%d",&p[i].k,&p[i].b),k[i]=n;
		if(opt[i]==2)scanf("%d",k+i),k[k[i]]=i;
		if(opt[i]==3)scanf("%d",k+i);
	}
	for(i=1;i<=n;++i)if(opt[i]==1)modify(1,i,i,k[i]);
	Solve();
	for(i=1;i<=n;++i){
		if(opt[i]==3){
			if(ans[i]==-INF)printf("EMPTY SET\n");
			else printf("%lld\n",ans[i]);
		}
	}
}
```

---

## 作者：pldzy (赞：1)

Happy New Year!

## Solution

线段树分治 + 直线凸包板子题。

发现可以将 $(x,y)$ 视作给了一条斜率为 $x$，截距为 $y$ 的直线。每次查询就是在现有直线中找到和直线 $x=k$ 交点纵坐标最大值。

考虑李超树，但李超树做不了可撤销（或者说这里很难维护）。

发现等价于每条直线有一段区间的“存活时间”，直接线段树分治，因为李超树做不了撤销所以直接在每个线段树节点维护一个直线下凸壳即可。

查询的时候就在每个包含 $k$ 的线段树节点上二分一下即可。

所以默写一下直线凸包就好啦。复杂度两只老哥。

哦还有一个细节需要注意一下，值域边界 `inf` 要设得非常大。

## Code

````cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define per(i, a, b) for(int i = (a); i >= (b); --i)
#define pll pair<ll, ll>
#define fi first
#define se second
#define mkp make_pair

const int maxn = 3e5 + 5;
const ll inf = 2e18;

int n;
pll p[maxn]; int op[maxn], ano[maxn];

vector<pll> t[maxn << 2];

#define ls (x << 1)
#define rs (x << 1 | 1)

inline void updtr(int x, int l, int r, int L, int R, pll v){
	if(l >= L and r <= R) return t[x].push_back(v), void();
	int mid = l + r >> 1;
	if(L <= mid) updtr(ls, l, mid, L, R, v);
	if(R > mid) updtr(rs, mid + 1, r, L, R, v);
} 

pll st[maxn]; int tp;

inline bool cmp(pll x, pll y, pll z){
	return (y.se - x.se) * (x.fi - z.fi) <= (z.se - x.se) * (x.fi - y.fi);
} 

inline void build(int x, int l, int r){
	if(t[x].size()){
		sort(t[x].begin(), t[x].end()); 
		unique(t[x].begin(), t[x].end());
		tp = 0;
		for(int it = 0; it < t[x].size(); ++it){
			if(it + 1 < t[x].size() and t[x][it].fi == t[x][it + 1].fi) continue;
			while(tp > 1 and cmp(t[x][it], st[tp], st[tp - 1])) --tp;
			st[++tp] = t[x][it];
		}
		t[x].clear();
		rep(i, 1, tp) t[x].push_back(st[i]);
	}
	if(l == r) return;
	int mid = l + r >> 1;
	build(ls, l, mid); build(rs, mid + 1, r);
}

inline ll gety(pll x, ll k){
	return k * x.fi + x.se;
}

inline ll calc(vector<pll> &ve, ll k){
	if(!ve.size()) return -inf;
	int l = 1, r = ve.size() - 1; ll pos = gety(ve[0], k);
	while(l <= r){
		int mid = l + r >> 1;
		pll x = ve[mid], y = ve[mid - 1];
		if(y.se - x.se <= (x.fi - y.fi) * k) 
			pos = max(pos, gety(x, k)), l = mid + 1;
		else r = mid - 1;
	}
	return pos;
}

inline ll qryp(int x, int l, int r, int pos, ll k){
	ll tmp = calc(t[x], k);
	if(l == r) return tmp;
	int mid = l + r >> 1;
	if(pos <= mid) return max(qryp(ls, l, mid, pos, k), tmp);
	else return max(qryp(rs, mid + 1, r, pos, k), tmp);
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	
	cin >> n;
	rep(i, 1, n){
		cin >> op[i] >> p[i].fi, (op[i] == 1) and (cin >> p[i].se);
		if(op[i] == 2) ano[p[i].fi] = i - 1;
	} 
	rep(i, 1, n) if(op[i] == 1){
		if(!ano[i]) ano[i] = n;
		updtr(1, 1, n, i, ano[i], p[i]);
	} 
	build(1, 1, n);
	rep(i, 1, n) if(op[i] == 3){
		ll ans = qryp(1, 1, n, i, p[i].fi);
		if(ans == -inf) cout << "EMPTY SET" << '\n';
		else cout << ans << '\n';
	} 
	return 0;
}
````

---

## 作者：Luciylove (赞：1)

好题。

大致题面：

动态加入删除直线 $kx+b$，查询所有直线过某条竖线 $x=p$ 的最高点。

这个不带删除显然是李超树模板题，但是李超树不可以进行删除。一般来说，我们可以考虑线段树分治来解决这一类难以删除的问题。

一个不成熟的想法是把李超树交换节点的信息存储到了栈里，然后交换，这个是可以做的。

但是我们可以保留线段树分治的想法。因为动态开点李超树的空间是 $O(n)$ 的，所以我们可以考虑线段树套动态开点李超树，然后把其每一条直线存在的时间段若干 $[l_i, r_i]$ 插入这一条直线。

查询就直接查询从该点到根的路径上套的所有李超树的过该竖线的最大值就行了。

然后我们就可以时间 $O(n\log n \log v)$，空间 $O(n\log n)$ 来解决这一个问题，代码实现是简易的。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5, MOD = 998244353;

int n, op[N], k[N], b[N], lp[N], rp[N], rt[N << 2], tot, pos[N];
int lc[N << 5], rc[N << 5], id[N << 5];

inline long long val (int x, int i) { return 1ll * k[i] * x + b[i]; }
inline void insert (int & u, int l, int r, int p) {
	if (! u) u = ++ tot;
	if (! id[u]) return id[u] = p, void();
	int mid = (l + r) >> 1;
	if (val(mid, p) > val(mid, id[u])) swap(id[u], p);
	if (val(l, p) > val(l, id[u])) insert(lc[u], l, mid, p);
	if (val(r, p) > val(r, id[u])) insert(rc[u], mid + 1, r, p);
}
inline long long query (int u, int l, int r, int p) {
	if (! u) return LLONG_MIN;
	long long res = val(p, id[u]);
	if (l == r) return res;
	int mid = (l + r) >> 1;;
	if (p <= mid) return max(res, query(lc[u], l, mid, p));
	else return max(res, query(rc[u], mid + 1, r, p));
}

#define ls u << 1
#define rs u << 1 | 1

inline void build (int u, int l, int r) { 
	if (l == r) return pos[l] = u, void(); 
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
}
inline void assign (int u, int l, int r, int ql, int qr, int x) {
	if (ql <= l && r <= qr) insert(rt[u], -1e9, 1e9, x);
    else {
	    int mid = (l + r) >> 1;
	    if (ql <= mid) assign(ls, l, mid, ql, qr, x);
	    if (qr > mid) assign(rs, mid + 1, r, ql, qr, x);
    }
}
int main () {
	ios :: sync_with_stdio(0);
	cin >> n, build(1, 1, n);
	for (int i = 1, idx; i <= n; i ++) {
		cin >> op[i];
		if (op[i] == 1)	cin >> k[i] >> b[i], lp[i] = i, rp[i] = n;
		else if (op[i] == 2) cin >> idx, rp[idx] = i;
		else cin >> k[i];
	}
	for (int i = 1; i <= n; i ++) if (op[i] == 1) assign(1, 1, n, lp[i], rp[i], i);
	for (int i = 1; i <= n; i ++)
		if (op[i] == 3) {
			long long ans = LLONG_MIN;
			for (int u = pos[i]; u; u >>= 1) ans = max(ans, query(rt[u], -1e9, 1e9, k[i]));
			if (ans == LLONG_MIN) puts("EMPTY SET");
			else printf("%lld\n", ans);
		}
	return 0;
}

```

---

## 作者：Gmt丶FFF (赞：1)

对于每一次询问，有 $x\times q+y=ans$。

可以推出： $y=-q\times x+y$，那么不难看出这是一个直线解析式，而 $x,y$ 则是集合中的点，所以是固定的，斜率 $-q$ 已给出，要使 $ans$ 最大，那么截距，即直线与 $y$ 轴交点越高。

那么可以想到维护凸包，维护凸包方法挺多，平衡树、李超线段树或是 cdq 其实都可以，但由于带增加与删除，所以 cdq 不好处理。看到删除可以选择平衡树，但增加不好维护。看到增加想到李超线段树，但又不好删除。

这个时候就轮到我们主角出场：线段树分治。

线段树上的每个节点代表这个时间存在的节点的集合，那么我们可以先离线预处理出来每个节点的进来和出去的时间，在线段树上进行区间修改。

注意：线段树分治不会进行上传与下放操作，节点间是独立的。

那么每放入一个点，维护上凸包的性质，保证斜率是递减的，如果不是就弹出之前的点。

对于每个询问，找到询问的时间，然后在线段树从上往下找，经过的每个节点都对这个节点中的集合求一次本询问的最佳答案，即斜率比前面小且比后面大的那个点，然后更新所有集合的最大值，求询问可以利用二分来解决。

时间复杂度：$O(n\times\log_2^2(n))$。

不够优秀，继续优化。

对于每次询问，按照斜率递减排序，然后利用每个集合的单调性，寻找出第一个最佳答案，即斜率比前面小比后面大的点。下次更新时就可以从这个点开始往下找了。

时间复杂度：$O(n\times \log(n))$

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
const int N=3e5+5;
int n,id[N],cnt,cnt2,nl,nr,k,lent[4*N],ans[N];
int num;
vector<int>f[4*N];
int t[4*N];
struct node
{
	int from,to,x,y;
}a[N];
struct ask
{
	int name,tim,a;
}q[N];
int cmp(node fi,node se)
{
	if(fi.x==se.x)return fi.y<se.y;
	return fi.x<se.x;
}
int cmp2(ask fi,ask se)
{
	return -fi.a>-se.a;
}
inline int ls(int x)
{
	return x<<1;
}
inline int rs(int x)
{
	return x<<1|1;
}
double clac(int x1,int y1,int x2,int y2)
{
	if(x1<=-1e17||x2<=-1e17)return 1e18;
	if(x1==x2)return 1e18; 
	return 1.0*(y1-y2)/(1.0*(x1-x2));
}
void build(int x,int l,int r)
{
	f[x].push_back(0);
	if(l==r)return;
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
}
void update(int x,int l,int r)
{
	if(l>=nl&&r<=nr)
	{
		while(lent[x]>1&&clac(a[f[x][lent[x]]].x,a[f[x][lent[x]]].y,a[f[x][lent[x]-1]].x,a[f[x][lent[x]-1]].y)<=clac(a[k].x,a[k].y,a[f[x][lent[x]]].x,a[f[x][lent[x]]].y))lent[x]--;
		int len=f[x].size();
		if(len-1==lent[x])f[x].push_back(k),lent[x]++;
		else f[x][++lent[x]]=k;
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=nl)update(ls(x),l,mid);
	if(mid<nr)update(rs(x),mid+1,r);
}
void search(int x,int l,int r)
{
	int len=lent[x]+1;
	for(;t[x]<len-1;t[x]++)
	{
		if(clac(a[f[x][t[x]]].x,a[f[x][t[x]]].y,a[f[x][t[x]+1]].x,a[f[x][t[x]+1]].y)<=-1.0*q[k].a)break;
	}
	if(t[x]!=0)
	{
		if(q[k].a*a[f[x][t[x]]].x+a[f[x][t[x]]].y>num)
		{
			num=q[k].a*a[f[x][t[x]]].x+a[f[x][t[x]]].y;
		}
	}
	else if(len>1)num=max(num,q[k].a*a[f[x][1]].x+a[f[x][1]].y);
	if(l==r)return;
	int mid=(l+r)>>1;
	if(mid>=nl)search(ls(x),l,mid);
	else search(rs(x),mid+1,r);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		int opt;
		scanf("%lld",&opt);
		if(opt==1)
		{
			int x,y;
			scanf("%lld%lld",&x,&y);
			a[++cnt]={i,n,x,y};
			id[i]=cnt;
		}
		if(opt==2)
		{
			int k;
			scanf("%lld",&k);
			a[id[k]].to=min(a[id[k]].to,i-1);
		}
		if(opt==3)
		{
			int x;
			scanf("%lld",&x);
			q[++cnt2]={cnt2,i,x};
		}
	}
	a[0].x=a[0].y=-1e18;
	build(1,1,n);
	sort(a+1,a+1+cnt,cmp);
	for(int i=1;i<=cnt;i++)
	{
		nl=a[i].from,nr=a[i].to,k=i;	
		update(1,1,n);
	}
	sort(q+1,q+1+cnt2,cmp2);
	for(int i=1;i<=cnt2;i++)
	{
		nl=q[i].tim,k=i;
		num=-9e18;
		search(1,1,n);
		ans[q[i].name]=num;
	}
	for(int i=1;i<=cnt2;i++)
	{
		if(ans[i]<=-9e18+5)printf("EMPTY SET\n");
		else printf("%lld\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：Tyyyyyy (赞：1)

## CF678F

### 题意简述
维护一个集合，支持三种操作：
- 插入二元组 $(x,y)$。

- 删除一个二元组。

- 给定 $q$，求 $\max\{qx+y\}$。

操作次数 $n\leq 3\times 10^5$。

### 题目分析
询问分块。考虑将一个二元组加入到它的作用区间。

相当于是对一个区间 $[l,r]$ 加入一个二元组，那么散块暴力更新答案，整块上我们可以对于每一块维护凸壳，最后更新整块的答案。

维护凸壳要排序和二分，平衡一下复杂度是 $O(n\sqrt{n\log n})$ 的。考虑到他不可能每次都是加入，手动调一下块长可以发现 $3000\sim 4000$ 最优。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pll pair<long long,long long>
#define fi first
#define se second
using namespace std;
const int N=3e5+10;
int n,del[N];
struct query
{
	int t,a,b;
}q[N];
struct ConvexHull
{
	vector<pll>v;
	ll f(pll p,ll x){return p.fi*x+p.se;}
	int check(pll A,pll B,pll C)
	{
		return (B.se-C.se)*(B.fi-A.fi)>(A.se-B.se)*(C.fi-B.fi);
	}
	void ins(int k,int b)
	{
		v.push_back({k,b});
		int i;
		while((i=v.size())>=3&&check(v[i-3],v[i-2],v[i-1]))v[i-2]=v[i-1],v.pop_back();
	}
	void ins(vector<pll>nv)
	{
		sort(nv.begin(),nv.end());
		reverse(nv.begin(),nv.end());
		for(auto p:nv)ins(p.fi,p.se);
	}
	ll ask(ll x)
	{
		int l=-1,r=v.size()-1,mid;
		while(l+1<r)
		{
			mid=(l+r)>>1;
			if(f(v[mid],x)<=f(v[mid+1],x))l=mid;
			else r=mid;
		}
		return f(v[r],x);
	}
};
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&q[i].t);
		if(q[i].t==1)scanf("%d%d",&q[i].a,&q[i].b);
		else scanf("%d",&q[i].a);
	}
	int sz=4000;
	vector<int>tmp,cur;
	for(int i=1;i<=n;i+=sz)
	{
		tmp.resize(0);ConvexHull ch;
		for(int j=i;j<=min(n,i+sz-1);j++)
			if(q[j].t==2&&q[j].a<i)tmp.push_back(q[j].a),del[q[j].a]=2;
		vector<pll>v;
		for(int i:cur)if(!del[i])v.push_back({q[i].a,q[i].b});
		ch.ins(v);
		for(int j=i;j<=min(n,i+sz-1);j++)
			if(q[j].t==1)tmp.push_back(j);
			else if(q[j].t==2)del[q[j].a]=1;
			else
			{
				ll ans=-9e18;
				for(int i:tmp)if(del[i]!=1)ans=max(ans,1ll*q[i].a*q[j].a+q[i].b);
				if(v.size())ans=max(ans,ch.ask(q[j].a));
				if(ans==-9e18)puts("EMPTY SET");
				else printf("%lld\n",ans);
			}
		for(int i:tmp)if(!del[i])cur.push_back(i);
	}
	return 0;
}
```

---

## 作者：Diaоsi (赞：0)

[Lena and Queries](https://www.luogu.com.cn/problem/CF678F)

先从弱化版问题入手。给定若干个点 $(x,y)$，给定 $k$，求 $kx+y$ 的最大值。

不妨令 $s=kx+y$，移项得 $y=-kx+s$，转化成给定一个斜率为 $-k$ 的直线，求这条直线经过点集中哪一个点时截距最大。对于这个问题只需要维护一个上凸壳，可能构成答案的点一定在这个凸壳上。

接下来思考怎么支持插入和删除工作，发现这玩意动态维护不了，于是考虑用线段树分治。

先把所有操作离线下来，对时间轴建出线段树，假设某个点在 $l$ 时刻出现，$r$ 时刻被删除，那它出现的时间就是 $[l,r-1]$，把这个点挂在线段树对应的区间上。

接下来遍历整棵线段树，在线段树的每个节点上都建出一个凸壳。对于查询操作，每一个查询操作对应一个时刻，相当于是线段树单点查询。根据标记永久化的思想，只需要对查询时经过的所有凸壳都求出一个截距，然后在这些截距中取最大即可。

在凸壳上求答案可以采用朴素的二分，现在我们得到了一个 $\mathcal{O}(n\log^2n)$ 的做法，不够优秀。

继续优化，当前时间复杂度的瓶颈在于建凸壳时的排序和求答案时的二分。

建凸壳时需要以 $x$ 为关键字进行排序，若在最开始时对所有的点进行一次排序，然后按排序后的顺序插入线段树。插入后的结果自然也是有序的，就不需要进行二次排序了。

仿照这个做法，把所有询问按照 $-k$ 降序排序，然后对每个凸壳都维护一个指针，由于询问单调，所以指针只能单调后移。

凸壳上的每个点只能被指针访问一次，所以在单个凸壳上查询的复杂度就变成均摊 $\mathcal{O}(1)$ 了。

于是就得到了一个时间空间复杂度均为 $\mathcal{O}(n\log n)$ 的做法。

Code：
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=300010,M=3000010;
const ll INF=0x3f3f3f3f3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int n,t,tot,cnt,s[N];
ll ans[N];
struct node{
	ll x,y;
	int id;
	bool operator <(const node &a)const{
		return x!=a.x?x<a.x:y>a.y;
	}
}q[N];
struct rec{
	ll x,y;
	int l,r,id;
	bool operator <(const rec &a)const{
		return x!=a.x?x<a.x:y>a.y;
	}
}p[N],w[N];
ll cmp(int u,int v,int y){return (q[u].y-q[v].y)*(q[u].x-q[y].x)-(q[u].y-q[y].y)*(q[u].x-q[v].x);}
bool cmp(int u,int v){return q[u].x==q[v].x&&q[u].y==q[v].y;}
vector<int> h[N<<2];
struct SegmentTree{
	int l,r,p;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define p(x) tree[x].p
}tree[N<<2];
void build(int x,int l,int r){
	l(x)=l,r(x)=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void insert(int x,int L,int R,int d){
	int l=l(x),r=r(x);
	if(L<=l&&r<=R){h[x].push_back(d);return;}
	int mid=(l+r)>>1;
	if(L<=mid)insert(x<<1,L,R,d);
	if(R>mid)insert(x<<1|1,L,R,d);
}
void solve(int x){
	int l=l(x),r=r(x);
	if(h[x].size()){
		s[t=1]=h[x][0];
		for(int i=1;i<(int)h[x].size();i++){
			if(cmp(s[t],h[x][i]))continue;
			while(t>1&&cmp(s[t-1],s[t],h[x][i])<=0)t--;
			s[++t]=h[x][i];
		}
		h[x].clear();
		for(int i=1;i<=t;i++)
			h[x].push_back(s[i]);
	}
	if(l==r)return;
	solve(x<<1),solve(x<<1|1);
}
ll query(int x,int pos,ll k){
	int l=l(x),r=r(x);
	ll res=-INF;
	if(h[x].size()){
		int ql=p(x),qr=(int)h[x].size()-1;
		while(ql<qr&&(ld)(q[h[x][ql]].y-q[h[x][ql+1]].y)/(q[h[x][ql]].x-q[h[x][ql+1]].x)>=-k)ql++;
		res=k*q[h[x][ql]].x+q[h[x][ql]].y;p(x)=ql;
	}
	if(l==r)return res;
	int mid=(l+r)>>1;
	if(pos<=mid)res=std::max(res,query(x<<1,pos,k));
	if(pos>mid)res=std::max(res,query(x<<1|1,pos,k));
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int op;
		scanf("%d",&op);
		if(op==1){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			q[i]=(node){x,y,++tot};
			p[tot]=(rec){q[i].x,q[i].y,i,n,i};
		}
		if(op==2){
			int x;
			scanf("%d",&x);
			p[q[x].id].r=i;
		}
		if(op==3){
			ll k;
			scanf("%lld",&k);
			w[++cnt]=(rec){k,i,0,0,cnt};
		}
	}
	build(1,1,n);
	sort(p+1,p+tot+1);
	sort(w+1,w+cnt+1);
	for(int i=1;i<=tot;i++)
		insert(1,p[i].l,p[i].r,p[i].id);
	solve(1);
	for(int i=1;i<=cnt;i++)
		ans[w[i].id]=query(1,w[i].y,w[i].x);
	for(int i=1;i<=cnt;i++)
		if(ans[i]==-INF)puts("EMPTY SET");
		else printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：lzytag (赞：0)

怎么回事，线段树分治板子题居然没有单 log 的线段树分治题解。

那就让我来水一发吧。

## 前置知识
线段树分治，斜率优化。
## 解法
首先我们发现这个问题如果没有删除，那很显然可以用**李超线段树** $O(n \log V)$ 维护，但加入了删除操作后，**时间**维度就会变得复杂。

于是，我们考虑离线用**线段树分治**解决时间维度，然后就可以用李超树维护了。（有一篇题解就是这么写的）

关于线段树分治：一个数对 $(x,y)$ 在时间 $l$ 加入，时间 $r$ 删除（如果没有删除就视 $r=n+1$），那么就相当于在时间 $[l,r-1]$ 内插入了 $(x,y)$，那么问题就和[线段树分治模板](https://www.luogu.com.cn/problem/P5787)一样了

但是，我们用了线段树分治后，问题不就已经变成了**静态问题**了吗。

这题中的线段树分治我们其实并不需要考虑撤销，因为所有加入数对的操作都是独立的,而不是和板子中的并查集一样会互相影响的。

当我们在时间 $t$ 进行查询时，我们只需要把线段树上所有包含 $t$ 的区间都加入查询即可。

既然是静态问题，为什么不直接用 $O(n)$ 的**斜率优化**呢？

我们对线段树上每个节点的操作按 $x$ 排序，查询按 $k$ 排序，考虑数对 $(x_1,y_1)$ 比数对 $(x_2,y_2)(x_1>x_2)$ 对于查询 $k$ 更优的条件。

$$x_1\times k+y_1 > x_2\times k + y_2$$

$$(x_1-x_2)\times k > y_2-y_1$$

$$k > \frac{y_2-y_1}{x_1-x_2}$$

这就是很明显的斜率优化的形式了，大家可以结合代码理解一下。

于是就单 log 了。

**tip**：线段树分治千万不要插入后再排序，而要先排序后插入，不然复杂度会因为排序假掉。

可惜的是这样写常数太大了，时间效率可能还不如实现的好的双 log。

悲哀

## 代码

变量名比较随意，凑合着看吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#pragma optimize(3)
#pragma optimize(2)
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define zsj return
#define akioi 0
int read()
{
	int x;scanf("%d",&x);
	return x;
}
ll lread()
{
	ll x;scanf("%lld",&x);
	return x;
}
//file head over
#define MaxN 300005
#define pb push_back
#define lc c<<1
#define rc c<<1|1
#define mid (l+r>>1) 
struct Node{
	ll k,b;
	int l,r;
};
struct Ask{
	int pos;
	ll x;
	int id;
};
vector<Node>a[MaxN*4];
vector<Ask>b[MaxN*4];
vector<Ask>e;
vector<Node>d;
int n,to[MaxN],qr;
ll ans[MaxN];
bool cmp1(Node i,Node j)
{ 
	if(i.k == j.k) return i.b < j.b; 
	return i.k < j.k;
}
bool cmp2(Ask i,Ask j){return i.x < j.x;} 
void InsertAsk(int c,int l,int r,int x,Ask y)
{
	b[c].pb(y);
	if(l == r) return ;
	if(x > mid) InsertAsk(rc,mid+1,r,x,y);
	else InsertAsk(lc,l,mid,x,y);
}
void InsertOp(int c,int l,int r,int ql,int qr,Node x)
{
	if(l == ql && r == qr) return a[c].pb(x),void();
	if(ql > mid) InsertOp(rc,mid+1,r,ql,qr,x);
	else if(qr <= mid) InsertOp(lc,l,mid,ql,qr,x);
	else InsertOp(lc,l,mid,ql,mid,x),InsertOp(rc,mid+1,r,mid+1,qr,x);
}
Node q[MaxN];
int h,t;
void Solve(int c,int l,int r)
{
	if(l != r) Solve(lc,l,mid),Solve(rc,mid+1,r);
	if(a[c].empty() || b[c].empty()) return ;
	h = 1,t = 0;
	for(auto p:a[c])
	{
		while(h <= t-1 && (q[t].b-p.b)*(q[t].k-q[t-1].k) <= (q[t-1].b-q[t].b)*(p.k-q[t].k)) t--;
		q[++t] = p;
	}
	for(auto p:b[c])
	{
		while(h+1 <= t && q[h].k*p.x+q[h].b <= q[h+1].k*p.x+q[h+1].b) h++;
		if(h <= t) ans[p.id] = max(ans[p.id],q[h].k*p.x+q[h].b);
	}
}
int main()
{
	n = read();
	for(int i = 1;i <= n;i++)
	{
		int op = read();
		if(op == 1)
		{
			int x = read(),y = read();
			d.pb(Node{x,y,i,n}),to[i] = d.size()-1;
		}
		if(op == 2)
		{
			int x = read();
			d[to[x]].r = i;	
		}
		if(op == 3)
		{
			int x = read();
			e.pb(Ask{i,x,++qr}),ans[qr] = -LINF;
		}
	}
	sort(d.begin(),d.end(),cmp1);
	sort(e.begin(),e.end(),cmp2);
	for(auto p:d) InsertOp(1,1,n,p.l,p.r,p);
	for(auto p:e) InsertAsk(1,1,n,p.pos,p);
	Solve(1,1,n);
	for(int i = 1;i <= qr;i++)
	{
		if(ans[i] != -LINF)printf("%lld\n",ans[i]);
		else puts("EMPTY SET");
	}
	zsj akioi;
}

```

---

