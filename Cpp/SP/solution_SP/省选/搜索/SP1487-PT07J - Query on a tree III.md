# PT07J - Query on a tree III

## 题目描述

你被给定一棵带点权的 $n$ 个点的有根树，点从 $1$ 到 $n$ 编号。

定义查询 $q(x,k)$：寻找以 $x$ 为根的子树中的第 $k$ 小点的编号（从小到大排序第 $k$ 个点）。

保证没有两个相同的点权。

## 样例 #1

### 输入

```
5
1 3 5 2 7
1 2
2 3
1 4
3 5
4
2 3
4 1
3 2
3 2```

### 输出

```
5
4
5
5```

# 题解

## 作者：dayz_break404 (赞：6)

~~感觉和题解区大佬们不太一样呢qwq。。。~~

### 题目描述

给出一棵有 $n$ 个节点的树，每个节点有边权，询问 $m$ 次，每次查询根为 $u$ 的子树边权的第 $k$ 大的编号。

### 题目分析

对于每次查询边权静态区间第 $k$ 小，我们可以用可持久化权值线段树（主席树）维护。

边权范围是 $0 \leq l_i \leq 10^9$，需要离散化。

维护的思想就是依次在树上加入 $n$ 个节点的权值 $v_i$，将每次加入在可持久化权值线段树上的根节点记录在数组 $root$ 里，若查询闭区间 $[l,r]$ 中的边权第 $k$ 大，对于每个主席树中的节点，设左儿子权值大小为 $x$，若 $x \geq k$，则第 $k$ 大在左子树中，否则第 $k$ 大则在右子树之中的第 $k-x$ 大，递归地直至到达叶子节点。

这里只是简单地提一下静态区间第 $k$ 小维护法，进一步了解请右转：[P3834 【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)

但是，主席树维护第 $k$ 小是在序列中的，本题是在树上。

我们不妨将原树的节点用特定的顺序排在序列中，并使子树的各个节点在序列中是连续的，将树上问题转化为序列问题。

具体的做法，从节点 $1$ 开始递归处理每一个节点，若节点 $u$ 的子节点已递归完成，就将其记录在顺序数组中。（有点类似于二叉树的后序遍历，能保证子树的各个节点在序列中是连续的）

再记录每个节点的子树大小，就可以维护并查询啦。

### 代码说明

代码长度较大，维护的数组较多，特此说明。

- $b$ 数组表示初始的树上点权。
- $vl$ 数组表示离散化后的树上点权。
- $kl$ 数组表示点权所对应的点编号。
- $siz$ 数组表示子树的大小。
- $dfn$ 数组表示各个编号对应的节点。
- $id$ 数组表示各个节点对应的编号。

注意细节，以及思路清晰。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100020;
int n,m,b[maxn],idx,head[maxn],vl[maxn],kl[maxn];
struct node1{//初始部分
	int next,to;
}e[maxn<<1];
inline void add(int u,int v){
	e[++idx].next=head[u],e[idx].to=v,head[u]=idx;
}
inline void lsh(){
	sort(b+1,b+n+1);
	int k=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		vl[i]=lower_bound(b+1,b+k+1,vl[i])-b;
		kl[vl[i]]=i;
	}
}


int dfx,siz[maxn],dfn[maxn],id[maxn];
int dfs(int now,int f){//树的处理部分
	siz[now]=1;
	for(int i=head[now];i;i=e[i].next){
		int x=e[i].to;
		if(x==f) continue;
		siz[now]+=dfs(x,now);
	}
	dfn[++dfx]=now;
	id[now]=dfx;
	return siz[now];
}


struct node2{//主席树部分
	int l,r,val;
}tree[maxn<<5];
int cnt,root[maxn];
struct presistable_segment_tree{
	inline int clone(int x){
		tree[++cnt]=tree[x];
		return cnt;
	}
	int build(int p,int l,int r){
		p=++cnt;
		if(l==r){
			return p;
		}
		int mid=(l+r)>>1;
		tree[p].l=build(tree[p].l,l,mid);
		tree[p].r=build(tree[p].r,mid+1,r);
		return p;
	}
	int update(int p,int l,int r,int x){
		p=clone(p);
		tree[p].val++;
		if(l==r) return p;
		int mid=(l+r)>>1;
		if(mid>=x) tree[p].l=update(tree[p].l,l,mid,x);
		else tree[p].r=update(tree[p].r,mid+1,r,x);
		return p;
	}
	int query(int l,int r,int u,int v,int k){
		int x=tree[tree[v].l].val-tree[tree[u].l].val;
		if(l==r) return kl[l];
		int mid=(l+r)>>1;
		if(x>=k) return query(l,mid,tree[u].l,tree[v].l,k);
		else return query(mid+1,r,tree[u].r,tree[v].r,k-x);
	}
}S;


int main(){
	int u,v;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		vl[i]=b[i];
	} 
	lsh();
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	siz[1]=dfs(1,0);
	root[0]=S.build(root[0],1,n);
	for(int i=1;i<=n;i++){//修改与查询注意思路清晰
		root[i]=S.update(root[i-1],1,n,vl[dfn[i]]);
	}
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&u,&v);
		printf("%d\n",S.query(1,n,root[id[u]-siz[u]],root[id[u]],v));
		
	}
	return 0;
} 
```

---

## 作者：abs001 (赞：3)

### 这是一道裸的dfs序（树链剖分）+权值主席树

对于这道题，首先可以想到将子树转换为区间，然后就可以用dfs序或树链剖分进行转换，然后就跟区间第k大一样了，最后询问就用主席树求一下k大值

可以先看这两道：

[【模板】树链剖分](https://www.luogu.org/problem/P3384)

[【模板】可持久化线段树 1（主席树）](https://www.luogu.org/problem/P3834)



```
主席树k大值求法：

权值主席树中存贮的是每个值出现的次数，然后取中点，比较左边和右边出现次数的多少，然后缩小范围，递归实现
```

代码：

```cpp
#include<bits/stdc++.h>
#define N 100001
using namespace std;

struct node{
    int to, ne;
}e[N * 2];

int n, m, len, l1, l2;
int id[N], rk[N], eid[N], re[N];
int he[N], a[N], b[N];
int val[N << 5], lc[N << 5], rc[N << 5], rt[N << 5];

void add(int x, int y)
{
    e[++l2].to = y, e[l2].ne = he[x];
    he[x] = l2;
}

void dfs(int x, int fa)
{
    id[x] = ++l1, rk[l1] = x;
    for(int i = he[x]; i; i = e[i].ne)
    {
        int y = e[i].to;
        if(y == fa) continue;
        dfs(y, x);
    }
    eid[x] = l1;
}

int change(int rt, int l, int r, int x, int y)
{
    int now = ++len;
    lc[now] = lc[rt], rc[now] = rc[rt], val[now] = val[rt] + 1;
    if(l == r)
	{
		re[l] = y;
		return now;
	}
    int mid = (l + r) >> 1;
    if(x <= mid) lc[now] = change(lc[rt], l, mid, x, y);
    else rc[now] = change(rc[rt], mid + 1, r, x, y);
    return now;
}

int query(int u, int v, int l, int r, int k)
{
    if(l == r) return re[l];
    int mid = (l + r) >> 1, s = val[lc[v]] - val[lc[u]], res;
    if(s >= k) res = query(lc[u], lc[v], l, mid, k);
    else res = query(rc[u], rc[v], mid + 1, r, k - s);
    return res;
}

int main()
{
    scanf("%d", &n);
    for(register int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    for(register int i = 1; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);//dfs序
    for(int i = 1; i <= n; i++)
	{
		a[rk[i]] = lower_bound(b + 1, b + n + 1, a[rk[i]]) - b;
		rt[i] = change(rt[i - 1], 1, n, a[rk[i]], rk[i]);
        //修改操作（主席树）
	}
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        int x, k;
        scanf("%d%d", &x, &k);
        printf("%d\n", query(rt[id[x] - 1], rt[eid[x]], 1, n, k));//输出询问
    }
    return 0;
}
```


---

## 作者：BFSDFS123 (赞：2)

气抖冷，我大线段树合并为什么没人写！

不难想到查询树上从小到大第 $k$ 大是一个弱智的线段树合并加线段树二分的题目。

考虑到把所有的询问先离线，放到每一个点上进行询问。我们从叶子节点建立权值线段树，存储每个权值出现的次数。

具体操作是，每次在某个子树的根节点将所有儿子的线段树合并，处理这一个节点上的所有询问，存储答案即可。

权值很大，记得离散化。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=2e5+10;
int n;
int root[Maxn];
struct segtree{
	struct seg{
		int lson,rson;
		int cnt;
	}t[Maxn<<5];
	int newnode;
	void update(int &node,int l,int r,int pos)
	{
		if(!node)
		{
			node=++newnode;
		}
		t[node].cnt++;
		if(l==r)
		{
			return ;
		}
		int mid=l+r>>1;
		if(pos<=mid)
		{
			update(t[node].lson,l,mid,pos);
		}else{
			update(t[node].rson,mid+1,r,pos);
		}
	}
	int merge(int node1,int node2,int l,int r)
	{
		if(!node1 || !node2)
		{
			return node1+node2;
		}
		t[node1].cnt+=t[node2].cnt;
		if(l==r)
		{
			return node1;
		}
		int mid=(l+r)>>1;
		t[node1].lson=merge(t[node1].lson,t[node2].lson,l,mid);
		t[node1].rson=merge(t[node1].rson,t[node2].rson,mid+1,r);
		return node1;
	}
	int query(int node,int l,int r,int k)
	{
		if(l==r)
		{
			return l;
		}
		int mid=(l+r)>>1;
		if(t[t[node].lson].cnt>=k)
		{
			return query(t[node].lson,l,mid,k);
		}else{
			return query(t[node].rson,mid+1,r,k-t[t[node].lson].cnt);
		}
	}
}seg;
struct Node{
	int k;
	int id;
};
vector<Node> queris[Maxn];
struct Edge{
	int to;
	int nxt;
}E[Maxn<<1];
int head[Maxn],tot;
void addedge(int u,int v)
{
	tot++;
	E[tot].to=v;
	E[tot].nxt=head[u];
	head[u]=tot;
}
int Ar[Maxn];
int tmp[Maxn];
int siz;
int mp[Maxn];
int ans[Maxn];
void dfs(int u,int fa)
{
//	cout<<"u:"<<u<<endl;
	for(int i=head[u];i;i=E[i].nxt)
	{
		int v=E[i].to;
		if(v==fa) continue;
		dfs(v,u);
		seg.merge(root[u],root[v],1,siz);
		
	}
//	cout<<seg.t[root[u]].cnt<<endl;
	for(auto i:queris[u])
	{
		int k=i.k,id=i.id;
		ans[id]=seg.query(root[u],1,siz,k);
		ans[id]=mp[ans[id]];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&Ar[i]);
		tmp[i]=Ar[i];
	}
	sort(tmp+1,tmp+1+n);
	siz=unique(tmp+1,tmp+1+n)-tmp-1;
	for(int i=1;i<=n;i++)
	{
		Ar[i]=lower_bound(tmp+1,tmp+1+siz,Ar[i])-tmp;
		mp[Ar[i]]=i;
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);addedge(v,u);
	}
	for(int i=1;i<=n;i++)
	{
		seg.update(root[i],1,siz,Ar[i]);
	} 
	int m;scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,k;
		scanf("%d%d",&x,&k);
		queris[x].push_back((Node){k,i});
	}
	dfs(1,0);
	
	for(int i=1;i<=m;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}

```

---

## 作者：hovny (赞：2)

## [戳这里看题面](https://www.luogu.org/problemnew/show/SP1487)

一道挺有意思的题，可以练一下板子

大意：给出$n(1\le n \le10^5)$个结点的树，$m$组询问，求 以$x$为根节点的树中 第$k$小的数（从小到大第$k$个） 

题目中没翻译清楚，该树树**以$1$为根节点**

## 思路：

对于树上操作，我已开始想到的是树剖，但是题目中所求的是**以$x$为根的树**，那么那么就应该想到**DFS序**

这和树剖一样，是一个能将**树形结构转化为线性结构**的神奇的东西

确定了使用$DFS$序之后，对于树中第$k$小，由于它是不带修的，所以很容易想到使用**主席树**

~~然后就开始乱搞了~~

## 注意要点：

题目中所求的是第$k$小点的**编号**！！

主席树查询出结果后，这个l值**不是实际上的编号**

因为主席树最后得到`l==r`的时候，`l`的值实际上是这个点在权值线段树中的位置

而这个点原先的`Id`并不一定是`l`，所以还要记录一下`Id`然后再对应回去

具体详见代码吧，结合代码说的更清楚

Code：

```cpp
#include<bits/stdc++.h>
#define N 100010
using namespace std;
struct node{
	int to,nxt;
}b[N<<1];
struct Node{
	int l,r,sum;
}T[N*80];//开大点没事，但是算一下，实际上40差不多了
int head[N],in[N],out[N],a[N],p[N],rev[N],root[N],Id[N];
int n,Ts,num,x,y,res,t,ans,k;//rev数组将dfs序对应会原来的编号
int read()
{
	int s=0;
	char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
void add(int x,int y){
	b[++t].to=y;b[t].nxt=head[x];head[x]=t;
	b[++t].to=x;b[t].nxt=head[y];head[y]=t;
}
void dfs(int k,int fa)//这里求的是dfs序，in[k]表示k这个点的dfs序
{//out[k]表示k这个点的子树中最大dfs序，也就是说，在in[k]~out[k]这个区间，都是以k为根的树 的节点的dfs序
	in[k]=++num;//有点绕口
	rev[num]=k;
	int i,to;
	for(i=head[k];i;i=b[i].nxt)
	{
		to=b[i].to;
		if(to==fa)
			continue;
		dfs(to,k);
	}
	out[k]=num;
}
void Modify(int l,int r,int &x,int y,int pos,int i)
{
	T[++res]=T[y];T[res].sum++;x=res;
	if(l==r)
	{
		Id[l]=i;//顺便记录一下这个点原先的编号
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		Modify(l,mid,T[x].l,T[y].l,pos,i);
	else
		Modify(mid+1,r,T[x].r,T[y].r,pos,i);
}
void query(int l,int r,int x,int y,int k)
{
	if(l==r)
	{
		ans=Id[l];//这样就可以直接对应了
		return;
	}
	int mid=(l+r)>>1;
	int sum=T[T[y].l].sum-T[T[x].l].sum;
	if(k<=sum)
		query(l,mid,T[x].l,T[y].l,k);
	else
		query(mid+1,r,T[x].r,T[y].r,k-sum);
}
int main()
{
	int i;
	n=read();
	for(i=1;i<=n;i++)
		p[i]=a[i]=read();
	for(i=1;i<n;i++)
	{
		x=read();y=read();
		add(x,y);
	}
	dfs(1,0);
	sort(p+1,p+1+n);
	for(i=1;i<=n;i++)//i表示的是dfs序
	{
		a[rev[i]]=lower_bound(p+1,p+1+n,a[rev[i]])-p;//离散化
		Modify(1,n,root[i],root[i-1],a[rev[i]],rev[i]);
	}
	Ts=read();
	while(Ts--)
	{
		x=read();k=read();
		query(1,n,root[in[x]-1],root[out[x]],k);
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：zzx0102 (赞：2)

谁告诉你这题不能莫队了。

考虑到如果是一条树上路径的话，那么可以用欧拉序，因为树上路径在欧拉序上是连续的。

但是子树呢？

考虑一颗子树在 dfs 序上是连续的，所以 dfs 序上莫队是可行的。

处理区间第 $k$ 大，考虑值域分块。

$g_i$ 表示第 $i$ 个数的出现次数，$G_i$ 表示第 $i$ 个块所有数的出现次数。

所以查询时，先跳 $G_i$ 找出第 $k$ 大的块，然后块内暴力，复杂度 $\mathcal{O(n\sqrt n})$。

跑的飞快，直接最优解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100010; int cnt[N], a[N], n, q, k, ans[N];
struct Query {int id, l, r, k;} Q[N]; int now, in[N];
void add(int x) {cnt[x]++; if(cnt[x] == 1) now++;}
void del(int x) {cnt[x]--; if(!cnt[x]) now--;}
bool cmp(Query a, Query b) {return in[a.l] != in[b.l] ? in[a.l] < in[b.l] : a.r < b.r;}
vector<int> e[N]; int sz[N], D[N], d[N], tot;
void dfs(int u, int fa) {
	sz[u] = 1; D[++tot] = u; d[u] = tot;
	for(int v: e[u]) {
		if(v == fa) continue;
		dfs(v, u); sz[u] += sz[v];
	}
}
int g[N], G[N], base, L[N], R[N], B, to[N];
void Add(int x) {g[x]++; G[in[x]]++;}
void Del(int x) {g[x]--; G[in[x]]--;}
int find(int k) {
	int sum = 0, pos = -1;
	for(int i = 1; i <= B; i++) {sum += G[i]; if(sum >= k) {pos = i; break;} }
//	cout << "pos = " << pos << ' ' << G[pos] << '\n';
	sum -= G[pos];
	for(int i = L[pos]; i <= R[pos]; i++) {sum += g[i]; if(sum >= k) return i;}
	return 114514;
}
int b[N];
int main() {
	ios::sync_with_stdio(0); cin >> n; for(int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + 1 + n); for(int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
//	for(int i = 1; i <= n; i++) cout << a[i] << ' '; cout << '\n';
	for(int i = 1; i <= n; i++) to[a[i]] = i;
	for(int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		e[a].push_back(b); e[b].push_back(a);
	}
	dfs(1, 0); cin >> q; base = sqrt(n); for(int i = 1; i <= n; i++) in[i] = (i + base - 1) / base; int x; B = in[n];
	for(int i = 1; i <= B; i++) L[i] = (i - 1) * base + 1, R[i] = min(i * base, n);
	for(int i = 0; i < q; i++) cin >> x >> Q[i].k, Q[i].l = d[x], Q[i].r = d[x] + sz[x] - 1, Q[i].id = i; int l = 1, r = 0; sort(Q, Q + q, cmp);
//	for(int i = 0; i < q; i++) cout << Q[i].l << ' ' << Q[i].r << '\n';
//	for(int i = 1; i <= n; i++) cout << D[i] << ' ';
	for(int i = 0; i < q; i++) {
		while(r < Q[i].r) Add(a[D[++r]]);
		while(l > Q[i].l) Add(a[D[--l]]);
		while(r > Q[i].r) Del(a[D[r--]]);
		while(l < Q[i].l) Del(a[D[l++]]);
//		cout << "l = " << l << " r = " << r << '\n';
//		cout << "find = " << find(Q[i].k) << '\n';
		ans[Q[i].id] = to[find(Q[i].k)];
	}
	for(int i = 0; i < q; i++) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：happybob (赞：2)

## 题意

给定一颗树，树有点权。多次询问，每次询问以 $u$ 为根的子树中第 $k$ 小的点权的点编号，点权互不相同。

## 解法

要求树上询问问题，可以想到树剖套各种数据结构，但是注意到这道题只需要求子树的问题，所以考虑用 `dfs` 序和主席树解决这个问题。

主席树其实就是[【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)，`dfs` 序很好处理，所以这道题很容易地被切掉了！

另外注意，询问求的是点的编号，而非点权。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

const int N = 1e5 + 5;

int a[N], n, m, na[N];
unordered_map<int, int> mp;
vector<int> G[N], b;

class Persis_Segment_Tree
{
public:
	struct Node
	{
		int l, r, sum;
	}tr[N * 23];
	int root[N], idx;
	Persis_Segment_Tree() : idx(0) {}
	int build(int l, int r)
	{
		int q = ++idx;
		tr[q].sum = 0;
		if (l == r) return q;
		int mid = l + r >> 1;
		tr[q].l = build(l, mid);
		tr[q].r = build(mid + 1, r);
		return q;
	}
	int update(int u, int l, int r, int x)
	{
		int q = ++idx;
		tr[q] = tr[u];
		if (l == x and r == x)
		{
			tr[q].sum++;
			return q;
		}
		int mid = l + r >> 1;
		if (x <= mid) tr[q].l = update(tr[u].l, l, mid, x);
		else tr[q].r = update(tr[u].r, mid + 1, r, x);
		tr[q].sum = tr[tr[q].l].sum + tr[tr[q].r].sum;
		return q;
	}
	int query(int old, int now, int l, int r, int k)
	{
		if (l == r) return mp[b[l]];
		int cnt = tr[tr[now].l].sum - tr[tr[old].l].sum, mid = l + r >> 1;
		if (k <= cnt)
		{
			return query(tr[old].l, tr[now].l, l, mid, k);
		}
		return query(tr[old].r, tr[now].r, mid + 1, r, k - cnt);
	}
};

class TreeCut
{
public:
	int idx, id[N], sz[N];
	Persis_Segment_Tree sg;
	TreeCut() : idx(0) {}
	void dfs(int u, int father)
	{
		id[u] = ++idx;
		sz[u] = 1;
		na[idx] = a[u];
		for (int i = 0; i < G[u].size(); i++)
		{
			int nx = G[u][i];
			if (nx != father)
			{
				dfs(nx, u);
				sz[u] += sz[nx];
			}
		}
	}
	void build()
	{
		dfs(1, 1);
		for (int i = 1; i <= n; i++) b.push_back(na[i]);
		sort(b.begin(), b.end());
		//b.erase(unique(b.begin(), b.end()), b.end());
		sg.root[0] = sg.build(0, b.size() - 1);
		for (int i = 1; i <= n; i++)
		{
			int g = lower_bound(b.begin(), b.end(), na[i]) - b.begin();
			sg.root[i] = sg.update(sg.root[i - 1], 0, b.size() - 1, g);
		}
	}
	int query(int u, int k)
	{
		int l = id[u], r = id[u] + sz[u] - 1;
		return sg.query(sg.root[l - 1], sg.root[r], 0, b.size() - 1, k);
	}
};

TreeCut tc;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		mp[a[i]] = i;
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	tc.build();
	scanf("%d", &m);
	while (m--)
	{
		int u, k;
		scanf("%d%d", &u, &k);
		printf("%d\n", tc.query(u, k));
	}
	return 0;
}
```


---

## 作者：Aftglw (赞：2)

~~以为 Qtree3 消失了，原来在这里~~

不知道为什么大家看了都说是主席树，我一看这静态子树查询，就觉得是 $\texttt{dsu on tree}$ ![qq_emoji: fad](https://xn--9zr.tk/fad)

然后事实证明，它就是 $\texttt{dsu on tree}$

将问题离线下来，拿一个平衡树维护子树第 $k$ 大，清空时也不用一个个删，直接把根设成 `0` 或 `NULL`，反正根据 $\texttt{dsu on tree}$ 的性质，每个点只会插入平衡树 $O(\log n)$ 次，所以空间不会炸。

然后这道题注意输出的是第 $k$ 大的节点编号，所以应将权值带着编号一起插入平衡树中。

总时间复杂度 $O(n\log^2n+q\log n)$，~~虽然慢了点，但是可以过~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define re register
// #define int long long
// #define pair pair<int, int>
// #define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout);
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int read()
{
   re int x = 0, f = 0;
    re char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = 1;c = getchar();}
    while (isdigit(c)) {x = (x << 3) + (x << 1) + c - 48;c = getchar();}
    return f ? -x : x;
}
inline string getstr()
{
    string res = "";
    re char ch = getchar();
    while (isspace(ch)) ch = getchar();
    while (!isspace(ch)) res.push_back(ch), ch = getchar();
    return res;
}
const int N = 1e5 + 5, inf = 0x7fffffff, P = 998244353;
int n, w[N];
int first[N], nex[N << 1], to[N << 1], num;
inline void Add(int u, int v)
{
    nex[++num] = first[u];
    first[u] = num;
    to[num] = v;
}
int son[N], siz[N], dfn[N], cnt, rnk[N];
inline void dfs1(int u)
{
    son[u] = -1, siz[u] = 1, dfn[u] = ++cnt, rnk[cnt] = u;
    for (re int i = first[u]; i; i = nex[i])
    {
        int v = to[i];
        if (siz[v]) continue;
        dfs1(v);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }
}
struct node
{
	int val, siz, rand, id;
	node *ls, *rs;
	inline void Update() {siz = ls->siz + rs->siz + 1;}
	inline void Clear() {val = siz = rand = 0;}
}*null, *rt;
inline node* New(int val, int id) {return new node {val, 1, rand(), id, null, null};}
inline void Split(node *p, int val, node *&x, node *&y)
{
	if (p == null) return void(x = y = null);
	if (p->val < val) {x = p; Split(p->rs, val, p->rs, y);}
	else {y = p; Split(p->ls, val, x, p->ls);}
	p->Update();
}
inline node* Merge(node *x, node *y)
{
	if (x == null) return y;
	if (y == null) return x;
	if (x->rand < y->rand) {x->rs = Merge(x->rs, y); x->Update(); return x;}
	else {y->ls = Merge(x, y->ls); y->Update(); return y;}
}
inline void Insert(int val, int id)
{
	node *x, *y;
	Split(rt, val, x, y);
	rt = Merge(Merge(x, New(val, id)), y);
}
inline int Find(node *p, int k)
{
	re int now = 0;
	while (p != null)
	{
		if (p->ls->siz + 1 + now == k) return p->id;
		if (p->ls->siz + 1 + now > k) p = p->ls;
		else
		{
			now += p->ls->siz + 1;
			p = p->rs;
		}
	}
}
int k[N], ans[N];
vector<int> q[N];
inline void add(int u) {Insert(w[u], u);}
inline void dfs2(int u, int fa, bool flag) // dsu on tree
{
    for (re int i = first[u]; i; i = nex[i])
    {
        int v = to[i];
        if (v == fa || v == son[u]) continue;
        dfs2(v, u, 0);
    }
    if (son[u] != -1) dfs2(son[u], u, 1);
    for (re int i = first[u]; i; i = nex[i])
    {
        int v = to[i];
        if (v == fa || v == son[u]) continue;
        for (re int j = dfn[v], up = dfn[v] + siz[v] - 1; j <= up; ++j) add(rnk[j]);
    }
    add(u);
    for (int i : q[u]) ans[i] = Find(rt, k[i]);
    if (!flag) rt = null; // 清空平衡树
}
signed main()
{
    srand(time(0));
    rt = null = new node {0, 0, 0, 0, nullptr, nullptr};
    n = read();
    for (re int i = 1; i <= n ; ++i) w[i] = read();
    for (re int i = 1; i < n; ++i)
    {
        int u = read(), v = read();
        Add(u, v), Add(v, u);
    }
    dfs1(1);
    int m = read();
    for (re int i = 1; i <= m; ++i)
    {
        int u = read(); k[i] = read();
        q[u].push_back(i); // 将询问存入节点中，离线
    }
    dfs2(1, 1, 1);
    for (re int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：辰星凌 (赞：2)

# **【题解】Query on a tree III [SP1487] [Bzoj1803]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12209965.html)

传送门：[$\text{Query on a tree III [SP1487]}$](https://www.luogu.com.cn/problem/SP1487) [$\text{[Bzoj1803]}$](https://oi-archive.memset0.cn/problem/bzoj/1803)

## **【题目描述】**

给出一棵 $n$ $(n \leqslant 10^5)$ 个节点的树，每个点都带有点权，一共 $m$ $(m \leqslant 10^4)$ 个询问，每次查询以 $x$ 为根的子树内权值第 $k$ 小的节点编号。

## **【分析】**

发现网上所有题解都是主席树，我线段树合并表示不服！

~~明明就是树上线段树合并的板子，居然没一个人写。。。~~

查询若干个子树的相关信息且不强制在线，可以先用链表把询问挂到 $x$ 上，初始化对每个节点开一棵，从下往上逐步合并，每合并完一棵子树就把链表掏出来查询一波信息，然后再继续往上合并。

由于节点权值两两不同，所以离散化后映射一下每个权值所在的节点编号即可。

时间复杂度：$O((n+m)logn)$ 。

## **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,o,x,y,T,b[N],A[N],ID[N],Ans[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    Re fu=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=fu?-x:x;
}
struct QWQ{//用链表挂询问
    int o,head[N];
    struct QAQ{int k,id,next;}a[N<<1];
    inline void add(Re x,Re k,Re id){a[++o].k=k,a[o].id=id,a[o].next=head[x],head[x]=o;}
}T0;
struct Segment_Tree{
    #define pl tr[p].lp
    #define pr tr[p].rp
    #define mid (L+R>>1)
    int O,pt[N];
    struct QAQ{int S,lp,rp;}tr[N*18];
    inline void change(Re &p,Re L,Re R,Re x){//单点修改
        if(!p)p=++O;++tr[p].S;
        if(L==R)return;
        if(x<=mid)change(pl,L,mid,x);
        else change(pr,mid+1,R,x);
    }
    inline void build(){for(Re i=1;i<=n;++i)change(pt[i],1,m,A[i]);}//初始化建立n棵权值线段树
    inline int merge(Re p,Re q){//线段树合并
        if(!p)return q;if(!q)return p;
        tr[p].S+=tr[q].S;
        pl=merge(pl,tr[q].lp);
        pr=merge(pr,tr[q].rp);
        return p;
    }
    inline int ask(Re p,Re L,Re R,Re k){//查询第k小
        if(L==R)return ID[L];
        Re tmp=tr[pl].S;
        if(tmp>=k)return ask(pl,L,mid,k);
        else return ask(pr,mid+1,R,k-tmp);
    }
}T1;
inline void dfs(Re x,Re fa){
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa)dfs(to,x),T1.pt[x]=T1.merge(T1.pt[x],T1.pt[to]);//合并儿子
    for(Re i=T0.head[x];i;i=T0.a[i].next)Ans[T0.a[i].id]=T1.ask(T1.pt[x],1,m,T0.a[i].k);//把x节点上挂着的询问都拿出来跑一下
}
int main(){
//  freopen("123.txt","r",stdin);
    in(n),m=n-1;
    for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
    while(m--)in(x),in(y),add(x,y),add(y,x);
    sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;//离散化
    for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+m+1,A[i])-b,ID[A[i]]=i;
    T1.build(),in(T);
    for(Re i=1;i<=T;++i)in(x),in(y),T0.add(x,y,i);//把询问挂到链表上
    dfs(1,0);
    for(Re i=1;i<=T;++i)printf("%d\n",Ans[i]);
}
```

另附主席树代码：

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define LL long long
#define Re register int
using namespace std;
const int N=1e5+3;
int n,m,o,x,y,T,dfn_o,b[N],A[N],AA[N],ID[N],dfn[N],size[N],head[N];
struct QAQ{int to,next;}a[N<<1];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    Re fu=0;x=0;char ch=getchar();
    while(ch<'0'||ch>'9')fu|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=fu?-x:x;
}
struct Segment_Tree{
    #define pl tr[p].lp
    #define pr tr[p].rp
    #define mid (L+R>>1)
    int O,pt[N];
    struct QAQ{int S,lp,rp;}tr[N*18];
    inline void creat(Re &p,Re q,Re L,Re R,Re x){
        tr[p=++O]=tr[q],++tr[p].S;
        if(L==R)return;
        if(x<=mid)creat(pl,tr[q].lp,L,mid,x);
        else creat(pr,tr[q].rp,mid+1,R,x);
    }
    inline int ask(Re p,Re q,Re L,Re R,Re k){//查询区间第k小
        if(L==R)return ID[L];
        Re tmp=tr[tr[q].lp].S-tr[pl].S;
        if(tmp>=k)return ask(pl,tr[q].lp,L,mid,k);
        else return ask(pr,tr[q].rp,mid+1,R,k-tmp);
    }
}T1;
inline void dfs(Re x,Re fa){
    AA[dfn[x]=++dfn_o]=A[x],size[x]=1;
    for(Re i=head[x],to;i;i=a[i].next)
        if((to=a[i].to)!=fa)dfs(to,x),size[x]+=size[to];
}
int main(){
//  freopen("123.txt","r",stdin);
    in(n),m=n-1;
    for(Re i=1;i<=n;++i)in(A[i]),b[i]=A[i];
    while(m--)in(x),in(y),add(x,y),add(y,x);
    sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;//离散化
    for(Re i=1;i<=n;++i)A[i]=lower_bound(b+1,b+m+1,A[i])-b,ID[A[i]]=i;
    dfs(1,0);
    for(Re i=1;i<=n;++i)T1.creat(T1.pt[i],T1.pt[i-1],1,m,AA[i]);//建主席树
    in(T);
    while(T--)in(x),in(y),printf("%d\n",T1.ask(T1.pt[dfn[x]-1],T1.pt[dfn[x]+size[x]-1],1,m,y));
    
}
```


---

## 作者：Dreamweaver (赞：1)

# Preface

主席树板子。

# Description

给定一棵以 1 号点为根的 $n$ 个点的有根树，点有点权 $a_i$，每个点点权互不相同。

$m$ 次查询：以 $x$ 为根的子树中点权第 k **小**（从小到大排序第 $k$ 个点）的点的**编号**。

$1 \le n \le 10 ^{5},1 \le m \le 10^4,0 \le a_i \le 10^9$ 。
 
# Solution

看到查询子树中的信息直接用 dfs 序转化为序列上的信息，然后套主席树查询静态区间第 k 小就可以了。

注意查询的是点的编号，我直接用了 map 来映射。

最后再推荐一道~~主席上树~~树上主席树的[问题](https://www.luogu.com.cn/problem/P2633)。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010
#define re register
#define Orz cout<<"stO %王队% Orz"<<'\n';
int n,mm,a[maxn],cnt,ccnt,head[maxn],size[maxn],id[maxn],w[maxn],root[maxn],t;
map<int,int>m;
vector<int>v;
struct node
{
	int l,r,sum;
	#define ls(x) z[x].l
	#define rs(x) z[x].r
	#define s(x) z[x].sum
}z[2000020];
struct Edge
{
	int s,t,nex;
}edge[maxn<<1];
void add(int s,int t)
{
	edge[++ccnt].s=s;
	edge[ccnt].t=t;
	edge[ccnt].nex=head[s];
	head[s]=ccnt;
}
void dfs(int u,int fa)
{
	id[u]=++t;
	w[t]=a[u];
	size[u]=1;
	for(re int i=head[u];i;i=edge[i].nex)
	{
		int tt=edge[i].t;
		if(tt==fa)	continue;
		dfs(tt,u);
		size[u]+=size[tt];
	}
}
int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
void insert(int l,int r,int pre,int &now,int p)
{
	z[now=++cnt]=z[pre];
	s(now)++;
	if(l==r)	return ;
	int mid=l+r>>1;
	if(p<=mid)	insert(l,mid,ls(pre),ls(now),p);
	else		insert(mid+1,r,rs(pre),rs(now),p);
}
int query(int l,int r,int a,int b,int k)
{
	if(l==r)	return l;
	int tmp=s(ls(b))-s(ls(a));
	int mid=l+r>>1;
	if(k<=tmp)	return query(l,mid,ls(a),ls(b),k);
	else		return query(mid+1,r,rs(a),rs(b),k-tmp);
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if(ch=='-')f=-1; ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0'; ch=getchar();}
    return x*f;
}
inline void wn(int x){if (x<0) {putchar('-');wn(-x);return;}if(x>=10)wn(x/10);putchar(x%10+'0');}
inline void wr(int x){wn(x);putchar('\n');}
inline void wi(int x){wn(x);putchar(' ');}
signed main()
{
	cin>>n;
	for(re int i=1;i<=n;++i)	v.push_back(a[i]=read()),m[a[i]]=i;
	for(re int i=1;i<n;++i)
	{
		int a,b;
		a=read(),b=read();
		add(a,b),add(b,a);
	}
	dfs(1,0);
	sort(v.begin(),v.end());
	for(re int i=1;i<=n;++i)	insert(1,n,root[i-1],root[i],getid(w[i]));
	cin>>mm;
	while(mm--)
	{
		int u,k;
		u=read(),k=read();
		wr(m[v[query(1,n,root[id[u]-1],root[id[u]+size[u]-1],k)-1]]);
	}
	return 0;
}
```


---

## 作者：年华天地 (赞：1)

## 思路
首先一看到树，我们就应该想起几个把树变为链的方法，DFS序，欧拉序和树剖（抱歉我太弱了，只知道这几个），再一看子树，一般都是DFS序了，不会的戳[这里](https://blog.csdn.net/hpu2022/article/details/81910490)。我还是简单的讲一下吧，DFS序就是在用DFS遍历一颗树时，在刚遍历到这个点时给它一个新编号，这样的序列满足一个性质，那就是任意一颗子树在DFS序中都是一段连续的区间。

知道了DFS序这题就很好做了，因为是求子树第k小，我们转化为一段区间后就是区间第k小了，那么套上主席树的板子就好了。

## 注意
1. 首先要注意各个数组的含义，不要搞混淆。

2. 数组空间要开够

3. 注意离散化

4. 题目中求得是编号

## 代码
```
#include<cstdio>
#include<algorithm>
#define mid (l+r)/2
using namespace std;
const int N=5e5;
int n,head[N],k,w[N],root[N],cnt,tim,num[N],size[N],m,a[N],pos[N],old[N];
struct node{
	int next,to;
}e[N];
struct tree{
	int l,r,size;
}t[N*30];
void lsh()
{
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++)
	{
		int t=lower_bound(a+1,a+n+1,w[i])-a;	
		pos[t]=i;
		w[i]=t;
	}
}
void add(int u,int v)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void renew(int id)
{
	t[id].size=t[t[id].l].size+t[t[id].r].size;
}
int build(int l,int r)
{
	int now=++k;
	if (l==r)return now;
	t[now].l=build(l,mid);
	t[now].r=build(mid+1,r);
	return now;
}
void dfs(int x,int ff)
{
	num[x]=++tim;
	old[tim]=x;
	size[x]=1;
	for (int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if (y==ff)continue;
		dfs(y,x);
		size[x]+=size[y];
	}
}
int merge(int pre,int x,int l,int r)
{
	int now=++k;
	t[now]=t[pre];
	if(l==r)return t[now].size++,now;
	if (x<=mid)t[now].l=merge(t[pre].l,x,l,mid);
	else t[now].r=merge(t[pre].r,x,mid+1,r);
	renew(now);
	return now;
}
int query(int pre,int now,int l,int r,int x)
{
    if (l==r)return pos[l];
    int tmp=t[t[now].l].size-t[t[pre].l].size;
    if (x<=tmp)return query(t[pre].l,t[now].l,l,mid,x);
    else return query(t[pre].r,t[now].r,mid+1,r,x-tmp);
}
void leaf(int id,int l,int r)
{
	if (l==r)
	{
		printf("%d ",t[id].size);
		return ;
	}
	leaf(t[id].l,l,mid);
	leaf(t[id].r,mid+1,r);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d",&w[i]),a[i]=w[i];
	lsh();
	for (int i=1,x,y;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	} 
	root[0]=build(1,n);
	dfs(1,0);
	for (int i=1;i<=n;i++)root[i]=merge(root[i-1],w[old[i]],1,n);
	scanf("%d",&m);
	for (int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",query(root[num[x]-1],root[num[x]+size[x]-1],1,n,y));
	}
	return 0;
}
```


---

## 作者：Graphcity (赞：1)

首先，一看到静态第 $k$ 大这种问题，就能够想到 **主席树** 这个东西。但不过，这次这个问题是在树上。

树上的点权在 $[0,10^9]$ 这个范围之内，主席树明显不能开这么大的空间，所以我们需要先行 **离散化** 。

接着，主席树模板的询问只要求第 $k$ 大的数是什么，而这次需要求出这个数是哪一个结点的点权。对此，可以使用 **哈希表** 提前存储每个结点的编号和点权，方便查找。

所有的询问都是在 $x$ 的子树这个范围之内，而子树内的 dfs 序都是连续的，我们就可以使用 **树链剖分** 将树上问题转化为在 dfs 序列中的区间问题。

由于区间询问不涉及链，我们可以只用一次 dfs 求出每个结点的 dfs 序编号，子树大小和每个 dfs 序编号对应的结点。

**Code:**

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define Maxn int(1e5)
using namespace std;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m;

namespace C//主席树部分
{
    struct Node
    {
        int l,r,sum;
    } t[Maxn*40+5];
    int tot,root[Maxn+5];
    #define ls(x) t[x].l
    #define rs(x) t[x].r

    inline void Insert(int l,int r,int pre,int &now,int k)//插入一个数k
    {
        t[++tot]=t[pre];
        t[tot].sum++;
        now=tot;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(k<=mid) Insert(l,mid,ls(pre),ls(now),k);
        else Insert(mid+1,r,rs(pre),rs(now),k);
    }
    inline int Count(int l,int r,int x,int y,int k)//询问区间第k大
    {
        if(l==r) return l;
        int mid=(l+r)>>1,res=t[ls(y)].sum-t[ls(x)].sum;
        if(res>=k) return Count(l,mid,ls(x),ls(y),k);
        else return Count(mid+1,r,rs(x),rs(y),k-res);
    }
}

namespace T//树链剖分部分
{
    struct Node
    {
        int to,nxt;
    } Edge[(Maxn<<1)+5];
    int tot,Head[Maxn+5];

    inline void Addedge(int x,int y)
    {
        Edge[++tot].to=y;
        Edge[tot].nxt=Head[x];
        Head[x]=tot;
    }

    int val[Maxn+5],siz[Maxn+5];
    int dfn[Maxn+5],pre[Maxn+5],nowdfn;

    inline void dfs(int x,int f)//树链剖分
    {
        siz[x]=1,dfn[x]=++nowdfn,pre[dfn[x]]=x;
        for(register int i=Head[x];i;i=Edge[i].nxt)
        {
            int y=Edge[i].to;
            if(y==f) continue;
            dfs(y,x);
            siz[x]+=siz[y];
        }
    }

    inline void Discrete()//离散化
    {
        vector<int> v;
        for(register int i=1;i<=n;++i)
            v.push_back(val[i]);
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        for(register int i=1;i<=n;++i)
            val[i]=lower_bound(v.begin(),v.end(),val[i])-v.begin()+1;
    }

    typedef pair<int,int> Pair;
    #define Mod 23333
    vector<Pair> h[Mod+5];
    inline void Makehash()//构造哈希表
    {
        for(register int i=1;i<=n;++i)
            h[val[i]%Mod].push_back(make_pair(val[i],i));
    }
    inline int Hash(int x,int l,int r)//查询哈希值
    {
        int nowh=x%Mod;
        for(register int i=0;i<h[nowh].size();++i)
        {
            int a=h[nowh][i].first,b=h[nowh][i].second;
            if(a==x && dfn[b]>=l && dfn[b]<=r)
                return b;
        }
        return -1;
    }

    inline void Run()
    {
        n=read();
        for(register int i=1;i<=n;++i)
            val[i]=read();
        Discrete();
        Makehash();
        for(register int i=1;i<n;++i)
        {
            int a=read(),b=read();
            Addedge(a,b);
            Addedge(b,a);
        }
        dfs(1,0);
        
        for(register int i=1;i<=n;++i)
            C::Insert(1,n,C::root[i-1],C::root[i],val[pre[i]]);
        m=read();
        while(m--)//回答询问
        {
            int a=read(),b=read();
            int ans=C::Count(1,n,C::root[dfn[a]-1],C::root[dfn[a]+siz[a]-1],b);
            printf("%d\n",Hash(ans,dfn[a],dfn[a]+siz[a]-1));
        }
    }
}

int main()
{
    T::Run();
    return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/SP1487)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到了求第$K$大的问题，我们不难想到使用权值的主席树。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;但是主席树只能处理区间第$K$大呀，怎么将求子树内的第$K$大转换成求区间第$K$大呢？  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个时候我们就需要用到另一个东西——$DFS$序。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DFS$序就是树上每一个节点被遍历到的顺序。树链剖分用到的序列实际上就是一种特殊的$DFS$序。设$p(u)$为$u$在$DFS$序中的位置，$s(u)$为$u$的子树的大小。则$DFS$序还满足$[p(u),p(u)+s(u)-1]$都是$u$的子树内的点。这个的证明可以参考$DFS$本身的顺序，这里略过。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们可以通过$DFS$序将树上问题转化到序列上面来，然后这就是一个常规的主席树的问题了。还要注意的是，题目求的是第$K$大的点的编号，所以还需要用一个映射的关系（比如数组或者$map$）来对应权值和编号。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;问题的总时间复杂度是$O((n+m)\log_2n)$（还要离散化，或者写动态开点应该也可以）。  
# 代码
```cpp
#include <cstdio>
#include <utility>
#include <algorithm>

typedef std :: pair<int, int> node;

#define xx first
#define yy second

const int MAXN = 1e5 + 5, MAXLOG = 20;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt;
	edge() {} edge( const int T, const int N ) { to = T, nxt = N; }
}Graph[MAXN << 2];

struct segmentTreeNode
{
	int lch, rch, cnt, id;
	#define id( x ) ( segTree[x].id )
	#define lch( x ) ( segTree[x].lch )
	#define rch( x ) ( segTree[x].rch )
	#define cnt( x ) ( segTree[x].cnt )
}segTree[MAXN * MAXLOG];

node dat[MAXN];

int seq[MAXN], rt[MAXN];
int head[MAXN], LPos[MAXN], siz[MAXN], lab[MAXN], ref[MAXN];
int N, M, cnt, ID, nsiz;

void upt( const int u ) { cnt( u ) = cnt( lch( u ) ) + cnt( rch( u ) ); }
void addEdge( const int from, const int to ) { Graph[++ cnt] = edge( to, head[from] ), head[from] = cnt; }

void DFS( const int u, const int fa )
{
	LPos[u] = ++ ID, seq[ID] = u, siz[u] = 1;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa ) DFS( v, u ), siz[u] += siz[v];
}

int update( const int u, const int l, const int r, const int pos, const int indx )
{
	int cur = ++ nsiz, mid = l + r >> 1; segTree[cur] = segTree[u];
	if( pos <= l && r <= pos ) { id( cur ) = indx, cnt( cur ) ++; return cur; }
	if( pos <= mid ) lch( cur ) = update( lch( u ), l, mid, pos, indx );
	else rch( cur ) = update( rch( u ), mid + 1, r, pos, indx );
	upt( cur ); return cur;
}

int query( const int lr, const int rr, const int l, const int r, const int rnk )
{
	if( l == r ) return id( rr );
	int mid = l + r >> 1, cost = cnt( lch( rr ) ) - cnt( lch( lr ) );
	if( rnk <= cost ) return query( lch( lr ), lch( rr ), l, mid, rnk );
	return query( rch( lr ), rch( rr ), mid + 1, r, rnk - cost );
}

int main()
{
	int x, k, tot = 0;
	read( N );
	for( int i = 1 ; i <= N ; i ++ ) read( dat[i].xx ), dat[i].yy = i;
	for( int i = 1, u, v ; i < N ; i ++ ) read( u ), read( v ), addEdge( u, v ), addEdge( v, u );
	std :: sort( dat + 1, dat + 1 + N );
	for( int i = 1 ; i <= N ; i ++ ) 
		lab[dat[i].yy] = ( tot += ( dat[i].xx != dat[i - 1].xx ) ), ref[tot] = dat[i].yy;
	DFS( 1, 0 );
	for( int i = 1 ; i <= N ; i ++ ) rt[i] = update( rt[i - 1], 0, tot, lab[seq[i]], ref[lab[seq[i]]] );
	read( M );
	while( M -- )
	{
		read( x ), read( k );
		write( query( rt[LPos[x] - 1], rt[LPos[x] + siz[x] - 1], 0, tot, k ) ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：KSkun (赞：1)

本题解同步发布于我的博客：[[SPOJ-PT07J]Query on a tree III 题解 | KSkun's Blog](https://ksmeow.moe/pt07j_spoj_sol/)，欢迎来逛~

其实这个题才是QTREE系列的正统续作233（因为和QTREE、QTREE2同作者）。

# 题解
DFS序+主席树。主席树的叶子节点可以存一下DFS序号，这样方便查。

# 代码
```cpp
// Code by KSkun, 2018/3
#include <cstdio>

#include <vector>
#include <algorithm>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1;
	register char c = fgc();
	while(c < '0' || c > '9') {
		if(c == '-') neg = -1;
		c = fgc();
	}
	while(c >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		c = fgc();
	}
	return res * neg;
}

const int MAXN = 100005;

std::vector<int> gra[MAXN];

int dfn[MAXN], ptn[MAXN], siz[MAXN], clk;

inline void dfs(int u, int fa) {
	dfn[u] = ++clk;
	ptn[dfn[u]] = u;
	siz[u] = 1;
	for(int v : gra[u]) {
		if(v == fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

struct SGT {
	struct SGTNode {
		int lch, rch, val, dfn;
	} tr[MAXN * 20];
	int rt[MAXN], cnt = 0;

	inline void insert(int &o, int l, int r, int x, int dfn) {
		tr[++cnt] = tr[o]; o = cnt;
		tr[o].val++;
		if(l == r) {
			tr[o].dfn = dfn;
			return;
		}
		int mid = (l + r) >> 1;
		if(x <= mid) insert(tr[o].lch, l, mid, x, dfn);
		else insert(tr[o].rch, mid + 1, r, x, dfn);
	}

	inline int query(int o1, int o2, int l, int r, int k) {
		if(l == r) return ptn[tr[o2].dfn];
		int mid = (l + r) >> 1;
		if(k <= tr[tr[o2].lch].val - tr[tr[o1].lch].val) {
			return query(tr[o1].lch, tr[o2].lch, l, mid, k);
		} else {
			k -= tr[tr[o2].lch].val - tr[tr[o1].lch].val;
			return query(tr[o1].rch, tr[o2].rch, mid + 1, r, k);
		}
	}
} sgt;

int n, m, w[MAXN], ut, vt, xt, kt;
std::vector<int> tmp;

int main() {
	n = readint();
	tmp.push_back(-1);
	for(int i = 1; i <= n; i++) {
		w[i] = readint();
		tmp.push_back(w[i]);
	}
	std::sort(tmp.begin(), tmp.end());
	tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
	int N = tmp.size() - 1;
	for(int i = 1; i <= n; i++) {
		w[i] = std::lower_bound(tmp.begin(), tmp.end(), w[i]) - tmp.begin();
	}
	for(int i = 1; i < n; i++) {
		ut = readint(); vt = readint();
		gra[ut].push_back(vt);
		gra[vt].push_back(ut);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) {
		sgt.rt[i] = sgt.rt[i - 1];
		sgt.insert(sgt.rt[i], 1, N, w[ptn[i]], i);
	}
	m = readint();
	while(m--) {
		xt = readint(); kt = readint();
		printf("%d\n", sgt.query(sgt.rt[dfn[xt] - 1], sgt.rt[dfn[xt] + siz[xt] - 1], 1, N, kt));
	}
	return 0;
}
```

---

