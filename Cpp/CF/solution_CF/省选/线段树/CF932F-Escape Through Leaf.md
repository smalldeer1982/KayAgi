# Escape Through Leaf

## 题目描述

You are given a tree with $ n $ nodes (numbered from $ 1 $ to $ n $ ) rooted at node $ 1 $ . Also, each node has two values associated with it. The values for $ i $ -th node are $ a_{i} $ and $ b_{i} $ .

You can jump from a node to any node in its subtree. The cost of one jump from node $ x $ to node $ y $ is the product of $ a_{x} $ and $ b_{y} $ . The total cost of a path formed by one or more jumps is sum of costs of individual jumps. For every node, calculate the minimum total cost to reach any leaf from that node. Pay attention, that root can never be leaf, even if it has degree $ 1 $ .

Note that you cannot jump from a node to itself.

## 说明/提示

In the first example, node $ 3 $ is already a leaf, so the cost is $ 0 $ . For node $ 2 $ , jump to node $ 3 $ with cost $ a_{2}×b_{3}=50 $ . For node $ 1 $ , jump directly to node $ 3 $ with cost $ a_{1}×b_{3}=10 $ .

In the second example, node $ 3 $ and node $ 4 $ are leaves, so the cost is $ 0 $ . For node $ 2 $ , jump to node $ 4 $ with cost $ a_{2}×b_{4}=100 $ . For node $ 1 $ , jump to node $ 2 $ with cost $ a_{1}×b_{2}=-400 $ followed by a jump from $ 2 $ to $ 4 $ with cost $ a_{2}×b_{4}=100 $ .

## 样例 #1

### 输入

```
3
2 10 -1
7 -7 5
2 3
2 1
```

### 输出

```
10 50 0 ```

## 样例 #2

### 输入

```
4
5 -10 5 7
-8 -80 -3 -10
2 1
2 4
1 3
```

### 输出

```
-300 100 0 0 ```

# 题解

## 作者：dqa2022 (赞：59)

一个显然的DP，方程就不再赘述了，前人之述备矣。

我写了一发李超线段树合并的做法。大致过程就是在合并线段树的时候先合并结构，最后再把根节点的信息合并起来。

看别人的题解，很多神仙好像要么不会证明复杂度，要么认为是$O(n\log^2 n)$的（值域同阶）。

通过一些思考，我认为其复杂度为$O(n\log n)$的。下面给出大致的证明：

* 现在仅研究李超线段树合并的复杂度，其他部分复杂度显然不会超过$O(n\log n)$；

* 在动态开点的李超线段树中，每个点都恰好保存了一条直线的信息，并且每条直线的信息最多在一个点被记录。熟悉基础李超树的神仙们应该能够通过李超线段树的实现得出这个结论；

* $merge$函数合并子树时如果有至少一个为空，这种情况下的复杂度可以不单独考虑，因为它和两个子树都不为空的复杂度是相关的；

* 定义一条直线的深度为记录它信息的节点的深度，特别地，如果一条直线的信息消失了，那么它的深度为$maxdep+1$。对于两个子树都不为空的合并过程，更新答案即合并根节点的直线信息的过程要么就是把某条直线的深度直接设为$maxdep+1$，要么就是把一条直线的深度$++$。根据势能分析，这里最多进行$O(n\times maxdep)$次，即$O(n \log n)$次。


```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
#define G getchar()
int read()
{
	int x=0; bool flg=false; char ch=G;
	for (;!isdigit(ch);ch=G) if (ch=='-') flg=true;
	for (;isdigit(ch);ch=G) x=(x<<3)+(x<<1)+(ch^48);
	return flg?-x:x;
}
const int Base=1e5,MAXW=2e5;
typedef long long ll;
const ll INF=0x7fffffffffffffffLL;

int n,a[100010],b[100010];
ll dp[100010];
struct Rec{
	ll b;
	int k;
}rec[100010];
ll getval(int id,int pos)
{
	pos-=Base;
	return 1LL*pos*rec[id].k+rec[id].b;
}
struct Edge{
	int to,nxt;
}edge[200010];
int cnt=1,last[100010];
inline void addedge(int x,int y)
{
	edge[++cnt]=(Edge){y,last[x]},last[x]=cnt;
	edge[++cnt]=(Edge){x,last[y]},last[y]=cnt;
}
#define mid (l+r>>1)
struct Node{
	int lson,rson,id;
}node[100010];
int idtot,rt[100010];
void update(int &cur,int l,int r,int y)
{
	if (!cur) return node[cur=y]=(Node){0,0,node[y].id},void();
	if (getval(node[cur].id,l)>=getval(node[y].id,l)&&getval(node[cur].id,r)>=getval(node[y].id,r))
		return node[cur].id=node[y].id,void();
	if (getval(node[cur].id,l)<=getval(node[y].id,l)&&getval(node[cur].id,r)<=getval(node[y].id,r))
		return;
	int &a=node[cur].id,&b=node[y].id;
	if (rec[a].k<rec[b].k)
		if (getval(a,mid)>getval(b,mid)) swap(a,b),update(node[cur].rson,mid+1,r,y);
		else update(node[cur].lson,l,mid,y);
	else
		if (getval(a,mid)>getval(b,mid)) swap(a,b),update(node[cur].lson,l,mid,y);
		else update(node[cur].rson,mid+1,r,y);
}
int merge(int x,int y,int l,int r)
{
	if (!x||!y) return x|y;
	if (l==r) return getval(node[x].id,l)>getval(node[y].id,l)?y:x;
	node[x].lson=merge(node[x].lson,node[y].lson,l,mid);
	node[x].rson=merge(node[x].rson,node[y].rson,mid+1,r);
	update(x,l,r,y);
	return x;
}
ll query(int cur,int l,int r,int pos)
{
	if (!cur) return INF;
	ll res=getval(node[cur].id,pos);
	if (l==r) return res;
	if (pos<=mid) return min(res,query(node[cur].lson,l,mid,pos));
	return min(res,query(node[cur].rson,mid+1,r,pos));
}
#undef mid
void dfs(int cur,int fat)
{
	for (int i=last[cur];i;i=edge[i].nxt)
		if (edge[i].to^fat)
			dfs(edge[i].to,cur),rt[cur]=merge(rt[cur],rt[edge[i].to],0,MAXW);
	if (rt[cur]) dp[cur]=query(rt[cur],0,MAXW,a[cur]+Base);
	rec[cur]=(Rec){dp[cur],b[cur]};
	node[++idtot]=(Node){0,0,cur};
	update(rt[cur],0,MAXW,idtot);
}
int main()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++) b[i]=read();
	for (int i=2;i<=n;i++) addedge(read(),read());
	dfs(1,0);
	for (int i=1;i<=n;i++) printf("%I64d ",dp[i]); putchar('\n');
	return 0;
}
```


如果有任何错漏，敬请批评指正！愿多交流学习。

---

## 作者：critnos (赞：17)

偶不会李超线段树合并怎么办？

当然是万能的 dsu on tree 啦qwq

我们有 dp 式子 $dp_x=dp_y+a_xb_y$（$y$ 在 $x$ 的子树内）

然后把 $dp_y$ 截距，$b_y$ 视作斜率，插入这个直线。

那么 $dp_x$ 就是这些直线和 $x=a_x$ 的交点的 $y$ 的最小值。李超线段树对不对！（老生常谈）

每次把除了重儿子的子树先计算，每次计算完清空，最后再计算重儿子，这时不用清空。

再把前面的子树重新插入一次，最后求现在正在求的节点就好了qwq

李超线段树要实现一个 clear。。

李超线段树插入直线是一个 $\log$ 的，dsu 的复杂度是 $O(n\log n)\times O(ds)=O(n\log^2 n)$ 的。

```cpp
#include<bits/stdc++.h>
#define ls w<<1
#define rs w<<1|1
#define int long long
using namespace std;
vector<int> a[100005];
int dp[100005];
int aa[100005],b[100005];
int size[100005];
int son[100005];
struct line
{
	double k,b;
	int id;
};
double f(line p,int x)
{
	return p.k*x+p.b;
}
struct LiChao_Segment_Tree
{
	line t[800005];
	int rubbishbin[800005];
	bool v[800005];
	int del;
	void insert(int w,int l,int r,line x,int L,int R)
	{
		int mid=L+R>>1;
		if(L>=l&R<=r)
		{
			if(!v[w])
				v[w]=1,rubbishbin[del++]=w;
			if(!t[w].id||f(t[w],mid)>f(x,mid)) swap(t[w],x);
			double crs=(t[w].b-x.b)/(x.k-t[w].k);
			if(L==R||t[w].k==x.k||crs<1.0*L||crs>1.0*R||!x.id) return;
			if(x.k>t[w].k) insert(ls,l,r,x,L,mid);
			else insert(rs,l,r,x,mid+1,R);
			return;
		}
		if(l<=mid)
			insert(ls,l,r,x,L,mid);
		if(r>mid)
			insert(rs,l,r,x,mid+1,R);
	}
	line ask(int w,int x,int L,int R)
	{
		if(L==R) return t[w];
		int mid=L+R>>1;
		line r;
		if(x<=mid)
			r=ask(ls,x,L,mid);
		else
			r=ask(rs,x,mid+1,R);
		return (!r.id||f(r,x)>f(t[w],x))?t[w]:r;
	}
	void clear()
	{
		for(int i=0;i<del;i++)
			v[rubbishbin[i]]=0,t[rubbishbin[i]].id=t[rubbishbin[i]].k=t[rubbishbin[i]].b=0;
		del=0;
	}
}tr;
struct RealDS
{
	void add(int dp,int b)
	{
		tr.insert(1,-1e5,1e5,line({(double)b,(double)dp,1}),-1e5,1e5);
	}
	int ask(int x)
	{
		return f(tr.ask(1,x,-1e5,1e5),x);
	}
	void clear()
	{
		tr.clear();
	}
}t;
void dfssize(int d,int fa)
{
	size[d]=1;
	for(int i=0;i<a[d].size();i++)
	{
		if(a[d][i]==fa) continue;
		dfssize(a[d][i],d);
		if(size[son[d]]<size[a[d][i]])
			son[d]=a[d][i];
		size[d]+=size[a[d][i]];
	}
}
void add(int d,int fa)
{
	t.add(dp[d],b[d]);
	for(int i=0;i<a[d].size();i++)
		if(a[d][i]!=fa)
			add(a[d][i],d);
}
void dfs(int d,int fa)
{
	int i;
	for(i=0;i<a[d].size();i++)
	{
		if(a[d][i]==fa||a[d][i]==son[d]) continue;
		dfs(a[d][i],d);
		t.clear();
	}
	if(son[d]) dfs(son[d],d);
	for(i=0;i<a[d].size();i++)
	{
		if(a[d][i]==fa||a[d][i]==son[d]) continue;
		add(a[d][i],d);
	}
	dp[d]=t.ask(aa[d]);
	t.add(dp[d],b[d]);
}
signed main()
{
	int n,i,x,y,k;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
		scanf("%lld",&aa[i]);
	for(i=1;i<=n;i++)
		scanf("%lld",&b[i]);
	for(i=1;i<n;i++)
	{
		scanf("%lld%lld",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfssize(1,0);
	dfs(1,0);
	for(i=1;i<=n;i++)
		printf("%lld ",dp[i]);
}
```


---

## 作者：hs_black (赞：14)

# CF932F(李超线段树+dp)

此题又是新玩法, 李超线段树合并优化$dp$

一个显然的$\Theta(n^2)dp$: $dp[x]$表示从x出发到叶子节点的最小代价

$dp[x] = \min(dp[y] + a[x] * b[y]) ~~(y \in subtree(x))$ 

如果我们将$b[y]$看成斜率, $dp[y]$看成纵截距, $a[x]$看成横坐标, 那么问题转为了在平面上有一些直线, 选出与直线$x = a[x]$相交的最靠下的点吗, 李超线段树板题, 但这道题出到了树上所以要用上线段树合并 因为有负数所以要整体右移一下, 相应的直线也需变换, 具体见代码

代码:

```cpp
#pragma GCC optimize(3)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
using namespace std;

template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 200500;
const int Delta = 100005;
const int Len = Delta << 1;


int h[N], ne[N<<1], to[N<<1];
int T[N], tot, cnt;
inline void add(int x, int y) {
	ne[++tot] = h[x], to[tot] = y, h[x] = tot;
}

int ls[N<<5], rs[N<<5], p[N<<5];
ll n, ans[N], a[N], b[N];
struct node {
	ll k, b;
}line[N];

inline ll calc(int num, ll x) {
	return line[num].k * x + line[num].b;
}

void insert(int &x, int l, int r, int num) {
	if (!x) return x = ++cnt, p[x] = num, void();
	int mid = (l + r) >> 1;
	if (calc(p[x], mid) > calc(num, mid)) swap(p[x], num);
	if (calc(p[x], l) <= calc(num, l) && 
		calc(p[x], r) <= calc(num, r)) return;
	if (calc(p[x], l) > calc(num, l)) insert(ls[x], l, mid, num);
	else insert(rs[x], mid + 1, r, num);
}

const ll INF = 0x7fffffffffff;
ll query(int now, int l, int r, ll x) {
	if (!now) return INF;
	int mid = (l + r) >> 1;
	return min(calc(p[now], x), x <= mid ?
		query(ls[now], l, mid, x) : query(rs[now], mid + 1, r, x));
}

int merge(int x, int y, int l, int r) {
	if (!x || !y) return x | y;
	insert(x, l, r, p[y]);
	int mid = (l + r) >> 1;
	ls[x] = merge(ls[x], ls[y], l, mid);
	rs[x] = merge(rs[x], rs[y], mid + 1, r);
	return x;
}

void dfs(int x, int fa) {
	for (re int i = h[x], y; i; i = ne[i]) {
		if ((y = to[i]) == fa) continue;
		dfs(y, x); 
		T[x] = merge(T[x], T[y], 1, Len);
	}
	ans[x] = query(T[x], 1, Len, a[x] + Delta);
	if (ans[x] == INF) ans[x] = 0;
	line[x] = (node){b[x], ans[x] - b[x] * Delta}; 
	insert(T[x], 1, Len, x);
}

int main() {
	read(n);
	for (re int i = 1;i <= n; i++) read(a[i]);
	for (re int j = 1;j <= n; j++) read(b[j]);
	for (re int i = 1;i < n; i++) {
		int x, y; read(x), read(y);
		add(x, y), add(y, x);
	} dfs(1, 0);
	for (re int i = 1;i <= n; i++) 
		write(ans[i]), putchar(' ');
	return 0;
}
```



---

## 作者：cyffff (赞：8)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF932F)

又是一道妙题。

又是一篇迟到一周的题解。
## 题意
给一棵树，$n$ 个节点，每个节点又两个权值 $a_i$ 和 $b_i$，记 $x\to y$ 表示 $x$ 到 $y$ 的转移，条件为 $y$ 在 $x$ 的子树内，代价为 $a_x\times b_y$。

求每个节点到任意叶节点的代价最小值。

$2\le n\le 10^5,-10^5\le a_i,b_i\le 10^5$。
## 思路
首先思考 $\text{dp}$，设 $dp_i$ 表示节点 $i$ 的答案，于是转移方程很好搞出来：

$$dp_x=\min_{y\in\text{subtree}(x)}(dp_y+a_x\times b_y)$$

可以发现，这样 $\text{dp}$ 是 $O(n^2)$ 的，不过提供了一个很不错的思路。

接下来，我们考虑使用数据结构优化这个 $\text{dp}$。

我们~~不知道为什么~~拿出一个一次函数 $f(x)=b+ky$，我们~~惊奇地~~发现，如果将 $dp_y,b_y$ 分别看作 $b,k$，则问题转化为求平面内一些一次函数与直线 $x=a_x$ 的交点中纵坐标的最小值。

然后既然要维护平面直角坐标系里面的一次函数最值问题，我们可以使用李超线段树，不会的可以先去做 [$\text{[HEOI2013]Segment}$](https://www.luogu.com.cn/problem/P4097)。

然后我们发现，如果对于每一次转移重建李超线段树的话，复杂度是 $O(n^2\log n)$ 的。。。我们发现当前节点的线段树维护的函数就是其子树的线段树维护的函数的并集，考虑线段树合并，直接 $\text{dfs}$ 时进行合并，合并完再统计答案即可。合并的方法与板子没什么不同，只是把维护的信息改为最小值即可，不会的可以去做 [【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)。

还有一点要注意，我们维护的是 $x=a_x$ 的线段树，题目中 $a_i$ 的数据范围是 $[-10^5,10^5]$，我们要将其向右平移 $10^5$ 至 $[0,2\times 10^5]$ 的下标范围防止出现负下标，记得算斜率时要减回去。

可以看出时间复杂度是 $O(n\log n)$ 的。

至此解决了这道题。

代码（也是很短的）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e5+10,rsh=1e5;
const ll INF=2e18+10;
int n,cnt,A[N],B[N],head[N];
ll dp[N];
struct Line{
	ll b,k;
	//y=b+kx
	Line(ll x=0,ll y=0){ b=x,k=y; }
	inline ll f(int x){
		x-=rsh;
		return k*x+b;
	}
}line[N];
struct Edge{
	int from,to,nxt;
}edgea[N<<1];
inline void add(int u,int v){
	cnt++;
	edgea[cnt].nxt=head[u];
	edgea[cnt].to=v;
	head[u]=cnt;
}
struct Li_Chao_segment{
	int cnt=0,root[N];
	struct node{
		int l,r;
		int best;
	}a[N];
	#define ls (a[rt].l)
	#define rs (a[rt].r)
	inline void insert(int &rt,int pre,int l=0,int r=rsh*2){
		if(!rt) return (void)(a[rt=pre]=(node){ 0,0,a[pre].best });
		int mid=l+r>>1;
		int &q=a[rt].best;
		int &x=a[pre].best;
		double l1=line[q].f(l),r1=line[q].f(r);
		double l2=line[x].f(l),r2=line[x].f(r);
		if(l1<=l2&&r1<=r2) return;
		if(l1>=l2&&r1>=r2) return (void)(a[rt].best=x);
		if(line[q].k>line[x].k){
			if(line[q].f(mid)>line[x].f(mid)){
				swap(q,x);
				insert(ls,pre,l,mid);
			}else{
				insert(rs,pre,mid+1,r);
			}
		}else{
			if(line[q].f(mid)<=line[x].f(mid)){
				insert(ls,pre,l,mid);
			}else{
				swap(q,x);
				insert(rs,pre,mid+1,r);
			}
		}
	}
	inline ll query(int rt,int k,int l=0,int r=rsh*2){
		if(!rt) return INF;
		ll ans=line[a[rt].best].f(k);
		if(l==r) return ans;
		int mid=l+r>>1;
		if(k<=mid){
			ans=min(ans,query(ls,k,l,mid));
		}else{
			ans=min(ans,query(rs,k,mid+1,r));
		}
		return ans;
	}
	inline int merge(int x,int y,int l=0,int r=rsh*2){
		if(!x||!y) return x+y;
		if(l==r)
			return line[a[x].best].f(l)>line[a[y].best].f(l)?y:x;
		int mid=l+r>>1;
		a[x].l=merge(a[x].l,a[y].l,l,mid);
		a[x].r=merge(a[x].r,a[y].r,mid+1,r);
		insert(x,y,l,r);
		return x;
	}
	inline void dfs(int rt,int f){
		for(int i=head[rt];i;i=edgea[i].nxt){
			if(edgea[i].to!=f){
				dfs(edgea[i].to,rt);
				root[rt]=merge(root[rt],root[edgea[i].to]);
			}
		}
		if(root[rt]) dp[rt]=query(root[rt],A[rt]);
		line[rt]=Line(dp[rt],B[rt]);
		a[++cnt]=(node){ 0,0,rt };
		insert(root[rt],cnt);
	}
}t;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		A[i]=read()+rsh;
	}
	for(int i=1;i<=n;i++){
		B[i]=read();
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	t.dfs(1,0);
	for(int i=1;i<=n;i++){
		write(dp[i]);
		putc(' ');
	}
	flush();
}
```
再见 qwq~

---

## 作者：QuantAsk (赞：5)

# 正题
题目链接:[https://www.luogu.com.cn/problem/CF932F](https://www.luogu.com.cn/problem/CF932F)

## 题目大意
- 给出 $n$ 个节点的一棵树。
- 从一个节点 $x$ 跳到其子树中的一个节点 $y$ 的代价是 $A_x\times B_y$ 。
- 对于每个节点求到某个叶子节点的最小代价。

$2\leq n\leq10^5,-10^5\leq A_i,B_i\leq 10^5$

## 解题思路
懒得写平衡树，提供一个CDQ分治维护凸壳+树上启发式合并的做法。

首先我们很容易列出 $O(n^2)$ 的dp方程
$$f_x=min\{f_y+A_x\times B_y\}(y\in subtree_x)$$

这个 $A_x\times B_y$ 的权值我们考虑用斜率优化维护。

如果这棵树是一条链我们做起来比较简单，类似于题目[[CEOI2017]Building Bridges](https://www.luogu.com.cn/problem/P4655)，使用CDQ分治来维护凸壳。对于前半段我们处理完后根据 $B_y$ 的大小排序，对于后半段我们根据 $A_x$ 进行排序。然后在左边建立出一个凸壳储存在单调栈里面，然后再枚举右边的更新每一个的答案。

但是这题转到了树上，考虑到CDQ分治能够做什么，它能够 $O(n\log n)$ 的统计一个序列的答案。我们其实只需要确定一些先后顺序然后用CDQ分治来做就好了。

使用树上启发式合并，统计每条重链的序列。对于每个节点我们保留下重子树的序列，然后将轻子树的所有节点加到序列末端，最后再把这个节点加入序列，这样我们就保证了这些轻子树只能影响到深度再往上的节点。

然后每次到一条链的顶部时再全部做一遍CDQ分治，然后清空序列。需要注意的是这次CDQ分治时轻子树中的节点的答案不能够被修改。

这样每个节点会被加入序列 $\log n$ 次。总共的时间复杂度 $O(n \log^2 n)$。

## code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#define ll long long
using namespace std;
const ll N=1e5+10;
struct node{
	ll to,next;
}e[N*2];
ll n,tot,ls[N],a[N],b[N],f[N],siz[N],son[N];
ll cnt,q[N],p[N],v[N],st[N],rfn[N];
void addl(ll x,ll y){
	e[++tot].to=y;
	e[tot].next=ls[x];
	ls[x]=tot;return;
}
void dfs(ll x,ll fa){
	siz[x]=1;
	for(ll i=ls[x];i;i=e[i].next){
		ll y=e[i].to;
		if(y==fa)continue;
		dfs(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])son[x]=y;
	}
	return;
}
bool cmp(ll x,ll y)
{return a[x]<a[y];}
bool cMp(ll x,ll y)
{return (b[x]==b[y])?(f[x]<f[y]):(b[x]<b[y]);}
double slope(ll x,ll y)
{return (double)(f[x]-f[y])/(b[x]-b[y]);}
void cdq(ll l,ll r){
	if(l==r)return;
	ll mid=(l+r)>>1,cnt1=l-1,cnt2=mid;
	for(ll i=l;i<=r;i++)
		if(rfn[p[i]]<=mid)q[++cnt1]=p[i];
		else q[++cnt2]=p[i];
	for(ll i=l;i<=r;i++)p[i]=q[i];
	cdq(l,mid);ll tot=0;
	for(ll i=l;i<=mid;i++){
		if(b[p[i]]==b[p[i-1]]&&i!=l)continue;
		while(tot>1&&slope(st[tot-1],st[tot])>slope(st[tot-1],p[i]))tot--;
		st[++tot]=p[i];
	}
	for(ll i=mid+1;i<=r;i++){
		if(v[p[i]])continue;
		while(tot>1&&slope(st[tot-1],st[tot])>-a[p[i]])tot--;
		ll x=p[i],y=st[tot];
		f[x]=min(f[x],f[y]+a[x]*b[y]);
	}
	cdq(mid+1,r);
	sort(p+l,p+1+r,cMp);
	return;
}
void calc(ll x,ll fa){
	p[++cnt]=x;rfn[x]=cnt;v[x]=1;
	for(ll i=ls[x];i;i=e[i].next){
		ll y=e[i].to;
		if(y==fa)continue;
		calc(y,x);
	}
}
void solve(ll x,ll fa,ll top){
	for(ll i=ls[x];i;i=e[i].next){
		ll y=e[i].to;
		if(y==fa||y==son[x])continue;
		solve(y,x,y);
	}
	if(son[x])
		solve(son[x],x,top);
	else f[x]=0;
	for(ll i=ls[x];i;i=e[i].next){
		ll y=e[i].to;
		if(y==fa||y==son[x])continue;
		calc(y,x);
	}
	p[++cnt]=x;rfn[x]=cnt;
	v[x]=(!son[x]);
	if(x==top){
		sort(p+1,p+1+cnt,cmp);
		cdq(1,cnt);cnt=0;
	}
	return;
}
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(ll i=1;i<=n;i++)scanf("%lld",&b[i]);
	for(ll i=1;i<n;i++){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		addl(x,y);addl(y,x);
	}
	memset(f,0x3f,sizeof(f));
	dfs(1,1);
	solve(1,1,1);
	for(ll i=1;i<=n;i++)
		printf("%lld\n",f[i]);
	return 0;
}
```

---

## 作者：s_y_z_r_y (赞：5)

发现洛谷题解只有李超线段树和平衡树维护凸壳，但是这也可以用点分治做。

设 $f_i$ 表示从 $i$ 出发到达子树内的叶子的最小花费。那么有转移方程
$$
f_i=\min(f_j+a_i×b_j),j\in subtree(i)
$$
考虑用斜率优化这个 dp式子。下面是我的优化方式，和这道题里面其他题解的优化方式不太一样，如果知道怎么斜率优化可以跳过不看。

设 $j$ ， $k$ 是 $i$ 子树内的点，且 $b_k>b_j$ ， $f_i$ 从 $j$ 点转移。那么有不等式
$$
f_j+a_i\times b_j\leq f_k+a_i\times b_k 
$$
$$
f_j-f_k\leq a_i\times (b_k-b_j)
$$
$$
\frac{f_k-f_j}{b_k-b_j}\geq -a_i
$$
设 $j$ 代表的点为 $(b_j,f_j)$ ，最后的不等式的意思是 当 $j$ 点和 $k$ 点的连线的斜率大于 $-a_i$ 时，用 $j$ 点转移会更优。于是可以维护一个下凸壳然后做了。

点分治时要注意这是有根树，每次处理完 当前联通块的重心 的 子树节点 后，再拿它们来更新 重心以及它在这个联通块里的祖先。因为不保证子树节点的 $b_j$ 递增，所以还要排个序。被更新的 重心和祖先节点 我也以 $a_i$ 为关键字排序了一遍，不过也可以二分凸壳，反正时间复杂度都一样。

点分治一个 log，排序一个 log，总时间复杂度 $O(nlog^2n)$

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef double db;
const db eps=1e-16;
const db maxn=1e21;
#define M 100005
#define pb push_back

template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}

int al[M<<1],cl[M<<1],tp[M],ttp;
int Al,rt,sz[M],fa[M],vis[M];
int sl[M];
int qe[M];
ll A[M],B[M];
ll dp[M];
vector<int> G[M];

int Mx(int x,int y){ return x>y?x:y; }
db xian(int x,int y){
	if(B[x]==B[y]) return dp[x]<=dp[y]?maxn:-maxn;
	return (dp[x]-dp[y])/(db)(B[x]-B[y]);
}
int cmp(db x){
	if(fabs(x)<eps) return 0;
	return x<0?-1:1;
}
bool cmp2(int x,int y){ if(B[x]==B[y]) return dp[x]>dp[y]; return B[x]<B[y]; }
bool cmp3(int x,int y){ return A[x]>A[y]; }

void dfs(int x,int f){
	int v,t=1;
	fa[x]=f;
	for(int i=tp[x];i;i=cl[i]) if((v=al[i])!=f){
		dfs(v,x);
		t=0;
	}
	if(t) dp[x]=0;
}

void fin_rt(int x,int f){
	int v,mx=0;
	sz[x]=1;
	for(int i=tp[x];i;i=cl[i]) if((!vis[v=al[i]]) && v!=f){
		fin_rt(v,x);
		mx=Mx(mx,sz[v]);
		sz[x]+=sz[v];
	}
	mx=Mx(mx,Al-sz[x]);
	if(mx<=(Al>>1)) rt=x;
}

void get_G(int x,int f){
	int v;
	G[rt].pb(x);
	for(int i=tp[x];i;i=cl[i]) if((!vis[v=al[i]])&&v!=f) get_G(v,x);
}

void sol(int x,int siz){
	if(siz==1) return (void)(vis[x]=1);
	Al=siz;
	fin_rt(x,fa[x]);
	int f=rt,q,ct=0,op=0,ed=0;

	vis[f]=1;
	for(int i=tp[f];i;i=cl[i]) if(al[i]!=fa[f]) get_G(al[i],f);
	for(int i=tp[f];i;i=cl[i]) if(al[i]!=fa[f]) siz-=sz[al[i]],sol(al[i],sz[al[i]]);
	for(int i=f;i!=fa[x];i=fa[i]) sl[++ct]=i;
	if(!G[f].empty()) sort(G[f].begin(),G[f].end(),cmp2);

	for(int v:G[f]){
		while(ed>1 && cmp(xian(qe[ed-1],qe[ed-2]) - xian(qe[ed-1],v)) >=0) --ed;
		if((!ed) || B[v]!=B[qe[ed-1]]) qe[ed++]=v;
		else if(dp[v]<dp[qe[ed-1]]) qe[ed-1]=v;
	}

	if(ct){
		sort(sl+1,sl+1+ct,cmp3);
		for(int i=1;i<=ct;++i){
			q=sl[i];
			while(op<ed-1 && cmp(xian(qe[op],qe[op+1]) + A[q]) <=0) ++op;
			dp[q]=min(dp[q],dp[qe[op]]+A[q]*B[qe[op]]);
		}
	}

	vis[f]=0;
	for(int i=tp[f];i;i=cl[i]) if(al[i]!=fa[f]) vis[al[i]]=1;
	G[f].clear();
	sol(x,siz);
}

void link(int x,int y){ al[++ttp]=y; cl[ttp]=tp[x]; tp[x]=ttp; }

int main(){
	int n,t,x,y;
	ll v;
	rd(n);
	for(int i=1;i<=n;++i) rd(A[i]);
	for(int i=1;i<=n;++i) rd(B[i]);
	for(int i=2;i<=n;++i){
		rd(x); rd(y);
		link(x,y);
		link(y,x);
	}
	memset(dp,127,sizeof(dp));
	dfs(1,0);
	sol(1,n);
	for(int i=1;i<=n;++i) printf("%lld ",dp[i]);
	puts("");
	return 0;
}
```

---

## 作者：jpwang (赞：5)

考虑dp，我们设f[i]为以i为起点的答案，那么有f[i]=min(f[j]+a[i]*b[j])这个东西，其中j的范围是i子树内任意点

考虑优化这个东西，我们发现把b看成斜率，f看成截距，那么等价于我们要在一堆直线中找到x=a[i]时的最低点，这个点显然在凸壳上

考虑怎么维护这个凸壳。可以用李超线段树+动态开点合并，也可以用平衡树动态维护凸壳启发式合并，然后就做完了

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define rep(i,st,ed) for (int i=st;i<=ed;++i)

typedef long long LL;
const LL INF=1000000000000000LL;
const int N=200005;

struct line {LL k,b;};
struct edge {int y,next;} e[N*2];
struct treeNode {int l,r; line rec;} t[N*51];

int a[N],b[N];
int root[N],tot;
int ls[N],edCnt;

LL f[N];

int read() {
	int x=0,v=1; char ch=getchar();
	for (;ch<'0'||ch>'9';v=(ch=='-')?(-1):(v),ch=getchar());
	for (;ch<='9'&&ch>='0';x=x*10+ch-'0',ch=getchar());
	return x*v;
}

void add_edge(int x,int y) {
	e[++edCnt]=(edge) {y,ls[x]}; ls[x]=edCnt;
	e[++edCnt]=(edge) {x,ls[y]}; ls[y]=edCnt;
}

double get_x(line a,line b) {
	return (double)(a.b-b.b)/(b.k-a.k);
}

LL get_y(line a,LL x) {
	return a.k*x+a.b;
}

void modify(int &now,int tl,int tr,line x) {
	if (!now) {
		t[now=++tot].rec=x;
		return ;
	}
	if (get_y(t[now].rec,tl)<get_y(x,tl)&&get_y(t[now].rec,tr)<get_y(x,tr)) return ;
	if (get_y(t[now].rec,tl)>get_y(x,tl)&&get_y(t[now].rec,tr)>get_y(x,tr)) {
		t[now].rec=x; return ;
	}
	double pos=get_x(t[now].rec,x);
	int mid=(tl+tr)>>1;
	if (t[now].rec.k<x.k) {
		if (pos>mid) {
			modify(t[now].r,mid+1,tr,t[now].rec);
			t[now].rec=x;
		} else modify(t[now].l,tl,mid,x);
	} else {
		if (pos<mid) {
			modify(t[now].l,tl,mid,t[now].rec);
			t[now].rec=x;
		} else modify(t[now].r,mid+1,tr,x);
	}
}

LL query(int now,int tl,int tr,int x) {
	if (!now) return INF;
	if (tl==tr) return get_y(t[now].rec,x);
	int mid=(tl+tr)>>1;
	LL tmp,ret=get_y(t[now].rec,x);
	if (x<=mid) tmp=query(t[now].l,tl,mid,x);
	else tmp=query(t[now].r,mid+1,tr,x);
	return std:: min(ret,tmp);
}

int merge(int x,int y,int tl,int tr) {
	if (!x||!y) return x+y;
	if (tl==tr) {
		if (get_y(t[y].rec,tl)<get_y(t[x].rec,tl)) {
			t[x].rec=t[y].rec;
		}
		return x;
	}
	int mid=(tl+tr)>>1;
	t[x].l=merge(t[x].l,t[y].l,tl,mid);
	t[x].r=merge(t[x].r,t[y].r,mid+1,tr);
	modify(x,tl,tr,t[y].rec);
	return x;
}

void dfs(int now,int fa) {
	bool flag=true;
	for (int i=ls[now];i;i=e[i].next) {
		if (e[i].y==fa) continue;
		dfs(e[i].y,now);
		root[now]=merge(root[now],root[e[i].y],-N,N);
		flag=false;
	}
	if (!flag) f[now]=query(root[now],-N,N,a[now]);
	modify(root[now],-N,N,(line) {b[now],f[now]});
}

int main(void) {
	freopen("data.in","r",stdin);
	freopen("myp.out","w",stdout);
	int n=read();
	rep(i,1,n) a[i]=read();
	rep(i,1,n) b[i]=read();
	rep(i,2,n) add_edge(read(),read());
	dfs(1,0);
	rep(i,1,n) printf("%lld\n", f[i]);
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

~~奇怪的线段树合并增加了！~~

朴素的 $dp$ 是 $dp_u = \min\{dp_v + a_u \times b_v\} [v \in subtree(u)]$

然后我们发现这个是一个 $kx + b$ 的形式，也就是 $b_v(a_u) + dp_v$，所以需要的是一个子树信息，子树信息能想到什么？线段树合并？dsu on tree？启发式合并？感觉都能做。

然后的话这里选择了线段树合并，至于朴素的线段树合并，线段树合并的复杂度是 $n \log n$ 的，证明的话，就考虑 $f(a + b) = f(a) + f(b) + sz(a \bigcap b)$ 容易发现这边 $sz(a \bigcap b)$ 不会超过 $\min\{a,b\}$ 然后证明就很显然了，但是对于李超树合并，需要做的一点是，这个信息不可加，不可减，不可简单合并，所以要把 $a \bigcap b$ 的部分直接插到树上，复杂度是 $n \log^2 n$，所以做完了。

```cpp
// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)

using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define pii pair<int, int>
#define fir first
#define sec second

template <class T>

void cmax(T& x, const T& y) {
  if (x < y) x = y;
}

template <class T>

void cmin(T& x, const T& y) {
  if (x > y) x = y;
}

#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back

template <class T>

void sort(vector<T>& v) {
  sort(all(v));
}

template <class T>

void reverse(vector<T>& v) {
  reverse(all(v));
}

template <class T>

void unique(vector<T>& v) {
  sort(all(v)), v.erase(unique(all(v)), v.end());
}

void reverse(string& s) { reverse(s.begin(), s.end()); }

const int io_size = 1 << 23 | 233;
const int io_limit = 1 << 22;
struct io_in {
  char ch;
#ifndef __WIN64
  char getchar() {
    static char buf[io_size], *p1 = buf, *p2 = buf;

    return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, io_size, stdin), p1 == p2) ? EOF : *p1++;
  }
#endif
  io_in& operator>>(char& c) {
    for (c = getchar(); isspace(c); c = getchar());

    return *this;
  }
  io_in& operator>>(string& s) {
    for (s.clear(); isspace(ch = getchar());)
      ;

    if (!~ch) return *this;

    for (s = ch; !isspace(ch = getchar()) && ~ch; s += ch)
      ;

    return *this;
  }

  io_in& operator>>(char* str) {
    char* cur = str;
    while (*cur) *cur++ = 0;

    for (cur = str; isspace(ch = getchar());)
      ;
    if (!~ch) return *this;

    for (*cur = ch; !isspace(ch = getchar()) && ~ch; *++cur = ch)
      ;

    return *++cur = 0, *this;
  }

  template <class T>

  void read(T& x) {
    bool f = 0;
    while ((ch = getchar()) < 48 && ~ch) f ^= (ch == 45);

    x = ~ch ? (ch ^ 48) : 0;
    while ((ch = getchar()) > 47) x = x * 10 + (ch ^ 48);
    x = f ? -x : x;
  }

  io_in& operator>>(int& x) { return read(x), *this; }

  io_in& operator>>(ll& x) { return read(x), *this; }

  io_in& operator>>(uint& x) { return read(x), *this; }

  io_in& operator>>(ull& x) { return read(x), *this; }

  io_in& operator>>(db& x) {
    read(x);
    bool f = x < 0;
    x = f ? -x : x;
    if (ch ^ '.') return *this;

    double d = 0.1;
    while ((ch = getchar()) > 47) x += d * (ch ^ 48), d *= .1;
    return x = f ? -x : x, *this;
  }
} in;

struct io_out {
  char buf[io_size], *s = buf;
  int pw[233], st[233];

  io_out() {
    set(7);
    rep(i, pw[0] = 1, 9) pw[i] = pw[i - 1] * 10;
  }

  ~io_out() { flush(); }

  void io_chk() {
    if (s - buf > io_limit) flush();
  }

  void flush() { fwrite(buf, 1, s - buf, stdout), fflush(stdout), s = buf; }

  io_out& operator<<(char c) { return *s++ = c, *this; }

  io_out& operator<<(string str) {
    for (char c : str) *s++ = c;
    return io_chk(), *this;
  }

  io_out& operator<<(char* str) {
    char* cur = str;
    while (*cur) *s++ = *cur++;
    return io_chk(), *this;
  }

  template <class T>

  void write(T x) {
    if (x < 0) *s++ = '-', x = -x;

    do {
      st[++st[0]] = x % 10, x /= 10;
    } while (x);

    while (st[0]) *s++ = st[st[0]--] ^ 48;
  }

  io_out& operator<<(int x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ll x) { return write(x), io_chk(), *this; }

  io_out& operator<<(uint x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ull x) { return write(x), io_chk(), *this; }

  int len, lft, rig;

  void set(int _length) { len = _length; }

  io_out& operator<<(db x) {
    bool f = x < 0;
    x = f ? -x : x, lft = x, rig = 1. * (x - lft) * pw[len];
    return write(f ? -lft : lft), *s++ = '.', write(rig), io_chk(), *this;
  }
} out;
#define int long long

template <int sz, int mod>

struct math_t {
	math_t() {
    fac.resize(sz + 1), ifac.resize(sz + 1);
    rep(i, fac[0] = 1, sz) fac[i] = fac[i - 1] * i % mod;

    ifac[sz] = inv(fac[sz]);
    Rep(i, sz - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }

  vector<int> fac, ifac;

  int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = x * x % mod)
      if (y & 1) ans = ans * x % mod;
    return ans;
  }

  int inv(int x) { return qpow(x, mod - 2); }

  int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }
};

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x * y / gcd(x, y); }

// dp_x = min{dp_y + a_x * b_y}
// a_x 处的 min { (b_y)a_x + dp_y }
// merge

const int maxn = 1e5 + 51;
int rt[maxn], ls[maxn << 5], rs[maxn << 5], id[maxn << 5], cnt = 0;
struct Line {
	int k, b; inline int val(int x) { return k * x + b; }
} s[maxn];

void ins(int &p, int l, int r, int num) {
	if(!p) { p = ++cnt; id[p] = num; return; }
	int mid = l + r >> 1, &x = num, &y = id[p];
	int midx = s[x].val(mid), midy = s[y].val(mid);
	if(midx < midy) { x ^= y ^= x ^= y; }
	int lx = s[x].val(l), ly = s[y].val(l);
	int rx = s[x].val(r), ry = s[y].val(r);
	if(lx >= ly && rx >= ry) return;
	if(lx < ly) ins(ls[p], l, mid, num);
	else ins(rs[p], mid + 1, r, num);
}

int merge(int x, int y, int l, int r) {
	if(!x || !y) return x + y;
	ins(x, l, r, id[y]);
	int mid = l + r >> 1;
	ls[x] = merge(ls[x], ls[y], l , mid);
	rs[x] = merge(rs[x], rs[y], mid + 1, r);
	return x;
}

int qry(int p, int l, int r, int pos) {
	if(!p) return 1e18;
	if(l == r) { return s[id[p]].val(pos); }
	int mid = l + r >> 1, ans = s[id[p]].val(pos);
	if(pos <= mid) { cmin(ans, qry(ls[p], l, mid, pos)); }
	else { cmin(ans, qry(rs[p], mid + 1, r, pos)); }
	return ans;
}

int n;
int L = -1e5, R = 1e5;
int dp[maxn], a[maxn], b[maxn];
vector <int> g[maxn];
void dfs(int u, int f) {
	for(int v: g[u])
		if(v ^ f) { dfs(v, u), rt[u] = merge(rt[u], rt[v], L, R); }
	dp[u] = qry(rt[u], L, R, a[u]);
	if(dp[u] == 1e18) dp[u] = 0;
	s[u] = { b[u], dp[u] }, ins(rt[u], L, R, u);
}

signed main() {
  // code begin.
	in >> n;
	rep(i , 1 , n) in >> a[i]; rep(i , 1 , n) in >> b[i];
	rep(i , 2 , n) { int u, v; in >> u >> v, g[u].pb(v), g[v].pb(u); }
	dfs(1, 0);
	rep(i , 1 , n) { out << dp[i] << '\n'; }
  return 0;
  // code end.
}
```

---

## 作者：fjy666 (赞：3)

可以列出一个显然的 dp 方程 $f_u = f_v+ a_ub_v(v\in\rm{Subtree_u})$，$f_u$ 代表结点 $u$ 的答案。  

大部分题解选择用 **李超树合并** 来处理上面的信息，但是在这里我将给出一个较为简单的方法。

我们先处理处每个结点的 dfn 序，那么可以拿来更新 $f_u$  的 $v$ 属于 $(\mathrm{dfn}_u,\mathrm{dfn}_u+\mathrm{siz}_u)$ 。  
把这个放到线段树上，相当于要处理一下两个操作
- 往位置 $p$ 插入一条直线 $l$。
- 查询 $[l,r]$ 中所有直线在 $x=q$ 时的 $\min\{y\}$。

很容易发现 **可能** 产生答案的直线形成一个凸壳，且斜率单调递减。  

如果每次插入直线都要重构整个凸壳复杂度无法承受。  
此时有两种选择：
- 平衡树维护凸壳（CF70D plus）
- 只在一个结点中所有线段都被插入后再重构（SDOI2014 向量集）

显然，每当你询问一个区间 $[l,r]$，那么所有编号在 $[l,r]$ 之间的直线都在线段树内了，所以第二种方法是正确的。  

重构总次数为线段树节点个数 $=\mathcal{O}(n\log n)$。  
总时间复杂度 $\mathcal{O}(n\log^2n)$。  

[参考代码实现](https://codeforc.es/contest/932/submission/206076302)。 

---

## 作者：tommymio (赞：2)

题面说的很清楚了，这题想让我们求树上每个点 $x$ 到 树上任一叶子节点 $y$ 的最小代价。

设 $f_{x,y}$ 为从 $x$ 号节点到达 $i$ 号叶子节点的最小费用。
![](https://cdn.luogu.com.cn/upload/image_hosting/k6wnbfvy.png)

$subtree(x)$ 为以 $x$ 为根的子树内的点构成的集合。

观察上式可以发现，当 $y$ 的值固定的时候，这个式子其实就是 $kx+b$，于是可以使用李超线段树来维护。

但是这是一个树上问题，我们考虑每次如何合并 $x$ 的子树对应的李超线段树，可以想到使用线段树合并来解决这个问题。

李超线段树的合并也很简单，边 $add$ 新合并的树的当前节点的 $tag$，然后递归合并即可，大体同线段树合并是一样的。

**Code**

```cpp
#include<cstdio>
#include<climits>
typedef long long ll;
const ll inf=LLONG_MAX;
const int infL=-1e5,infR=1e5;
int tot=0,num=0,cnt=0;
ll b[300005],k[300005],res[300005];
int a[300005],c[300005];
int h[300005],to[600005],ver[600005];
int rt[300005],sonL[5000005],sonR[5000005],tag[5000005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline ll min(ll x,ll y) {return x<y? x:y;}
inline ll calc(ll x,int id) {return k[id]*x+b[id];}
inline void change(int &p,int l,int r,int id) {
	if(!p) {tag[p=++tot]=id;return;}
	if(l==r) {
        if(calc(l,id)<calc(l,tag[p])) tag[p]=id;
        return;
    }
    int mid=l+r>>1;
    if(k[id]<k[tag[p]]) {
        if(calc(mid,id)<=calc(mid,tag[p])) {change(sonL[p],l,mid,tag[p]);tag[p]=id;}
        else {change(sonR[p],mid+1,r,id);}
    }
    else if(k[id]>k[tag[p]]) {
        if(calc(mid,id)<=calc(mid,tag[p])) {change(sonR[p],mid+1,r,tag[p]);tag[p]=id;}
        else {change(sonL[p],l,mid,id);}
    }
    else if(b[id]<b[tag[p]]) {
        tag[p]=id;
        return;
    }
}
inline ll ask(int p,int l,int r,int x) {
	if(!p) return inf;
	if(l==r) return calc(l,tag[p]);
	int mid=l+r>>1;
	ll minn=calc(x,tag[p]);
	if(x<=mid) return min(minn,ask(sonL[p],l,mid,x));
	else return min(minn,ask(sonR[p],mid+1,r,x));
}
inline int merge(int x,int y,int l,int r) {
	if(!x||!y) return x+y;
	if(l==r) return calc(l,tag[x])>calc(l,tag[y])? y:x;
	int mid=l+r>>1;
	sonL[x]=merge(sonL[x],sonL[y],l,mid);
	sonR[x]=merge(sonR[x],sonR[y],mid+1,r);
	change(x,l,r,tag[y]);
	return x;
}
inline void dfs(int x,int fa) {
	int du=0;
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		if(y==fa) continue;
		dfs(y,x);++du;
		rt[x]=merge(rt[x],rt[y],infL,infR);
	}
	k[++num]=c[x];
	if(du) res[x]=b[num]=ask(rt[x],infL,infR,a[x]); 
	else res[x]=b[num]=0;
	change(rt[x],infL,infR,num);
}
signed main() {
	int n=read();
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=1;i<=n;++i) c[i]=read();
	for(register int i=1;i<n;++i) {int x=read(),y=read();add(x,y);add(y,x);}
	dfs(1,-1);
	for(register int i=1;i<=n;++i) printf("%lld ",res[i]);
	return 0;
}
```

---

## 作者：Terac (赞：1)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF932F)

update 2021.10.13：修正了某些错误。

很有意思的一道题，总算调出来了，分享下自己的思路。

显然可以树形 DP，$f_i$ 表示节点 $i$ 的答案，有转移方程
$$f_u=\min (f_v+a_u b_v),v\in \text{subtree}(u)$$

这样就有了个 $O(n^2)$ 的做法，考虑能否用 DS 优化 DP。

观察到有 $f_v+a_ub_v$ 这一形式，若把 $f_v$ 视为截距，$a_u$ 视作要求值的点，$b_v$ 视为斜率，发现与一次函数 $kx+b$ 的形式很相似，可以把其看成一条直线。


于是问题转化为在若干直线中，求 $x=a_u$ 时最小值所对应直线。

维护若干直线某点最值，可以对于每个点，开一棵李超线段树，但若每到一个新节点，都重新建树，复杂度仍不能接受。

令 $mn_u(x)$ 表示对于点 $u$ 的直线集在 $x$ 处的最小值，发现 $mn_u(x)=\min (mn_v(x)),v\in \text{son}(u)$，可以用线段树合并维护最小值，这样做的复杂度可以通过摊到 $O(n\log n)$，具体证明可以看下[这篇题解](https://www.luogu.com.cn/blog/dqa2020/cf932f-escape-through-leaf-ti-xie)。

有很多题解说要平移值域，事实上李超线段树合并不需要平移值域，正常写就好了。

然后直接套板子就好了，~~我人傻常数大跑了 12.22s~~。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, W = 1e5;
int n, a[N], b[N];
ll f[N];
struct edge {
	int to, nxt;
} e[N << 1];
int head[N], cnt;
void add(int u, int v) {
	e[++cnt] = (edge){v, head[u]};
	head[u] = cnt;
}
struct line {
	ll k, b;
	int id;
} t[N << 2];
ll calc(line x, int d) { return x.k * d + x.b; }
ll cross(line x, line y) { return (x.b - y.b) / (y.k - x.k); }
int rt[N * 20], ls[N * 20], rs[N * 20], tot;
void insert(int &x, int l, int r, line s) {
	if(!x) x = ++tot;
	int mid = l + r >> 1;
	if(calc(t[x], mid) > calc(s, mid) || !t[x].id) swap(t[x], s);
	if(l == r || t[x].k == s.k || !s.id) return;
	ll p = cross(t[x], s);
	if(p < l || p > r) return;
	if(s.k > t[x].k) insert(ls[x], l, mid, s);
	else insert(rs[x], mid + 1, r, s);
}
int merge(int x, int y, int l, int r) {
	if(!x || !y) return x + y;
	insert(x, l, r, t[y]);
	int mid = l + r >> 1;
	ls[x] = merge(ls[x], ls[y], l, mid);
	rs[x] = merge(rs[x], rs[y], mid + 1, r);
	return x;
}
line query(int x, int l, int r, int p) {
	if(l == r) return t[x];
	int mid = l + r >> 1;
	line res;
	if(mid >= p) res = query(ls[x], l, mid, p);
	else res = query(rs[x], mid + 1, r, p);
	if(!res.id || calc(t[x], p) < calc(res, p)) return t[x];
	return res;
}
void dfs(int u, int fa) {
	for(int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if(v == fa) continue;
		dfs(v, u);
		rt[u] = merge(rt[u], rt[v], -W, W);
	}
	int mn = query(rt[u], -W, W, a[u]).id;
	f[u] = 1ll * a[u] * b[mn] + f[mn];
	insert(rt[u], -W, W, (line){b[u], f[u], u});
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) printf("%lld ", f[i]);
	return 0;
}
```


---

## 作者：H6_6Q (赞：1)

$\large\text{Solution}$

我们设 $dp_i$ 表示编号为 $i$ 的节点到达该树叶子节点的最小花费，那么显然我们有以下的转移方程：

$$dp_i=\begin{cases}0&i \text{ is leaf}\\\min\limits_{j \in child_s}\left\{dp_j+a_i \times b_j\right\}&\text{Otherwide}\\\end{cases}$$

直接转移是 $\text{O}\left(n^2\right)$ 的，考虑如何优化。

我们令 $dp_j+a_i \times b_j$ 为 $y$ ，$a_i$ 为 $x$ ，则我们可以在二维平面上用 $y=b_j \times x + dp_j$ 这条直线表示出一种转移的情况，那么我们求 $\min\left\{dp_j+a_i \times b_j\right\}$ 等价于在若干条直线找到一条直线，使其与 $x=a_i$ 交点的纵坐标最小，因此可以直接使用李超树维护。

可以先将树的 dfs 序处理出来，那么 dp 的转移便是一个区间，因此线段树套李超树维护一下就行了。

复杂度 $\text{O}\left(n \log^2 n\right)$

$\large\text{Code}$

```cpp
const int N=4e5+5;
int n,a[N],b[N],dfn[N],low[N],ans[N],cnt;

vector<int> val,lcc,rcc;

struct Edge
{
	int v,ne;
}e[N*2];
int head[N],tot;

struct Line
{
	int k,b;
}c[N];

inline int f(int id,int v);
inline void add(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa);
void build(int x,int l,int r);
void update1(int x,int l,int r,int p,int v);
int query1(int x,int l,int r,int L,int R,int v);
void update2(int x,int l,int r,int v);
int query2(int x,int l,int r,int v);

signed main()
{
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) b[i]=read();
	for(int i=1;i<=n-1;++i)
	{
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	c[0].b=1e18;
	dfs1(1,0);
	cnt=0;build(1,1,n);
	for(int i=0;i<=cnt;++i)
	{
		val.push_back(0);
		lcc.push_back(0);
		rcc.push_back(0);
	}
	dfs2(1,0);
	for(int i=1;i<=n;++i)
		printf("%lld ",ans[i]);
	return 0;
}

inline int f(int id,int v)
{
	return c[id].k*v+c[id].b;
}

inline void add(int u,int v)
{
	e[++tot]=(Edge){v,head[u]};
	head[u]=tot;
}

void dfs1(int u,int fa)
{
	dfn[u]=++cnt;
	for(int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs1(v,u);
	}
	low[u]=cnt;
}

void dfs2(int u,int fa)
{
	int fl=1;
	for(int i=head[u];i;i=e[i].ne)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs2(v,u);fl=0;
	}
	if(fl) ans[u]=0;
	else ans[u]=query1(1,1,n,dfn[u]+1,low[u],a[u]+100001);
	c[u]=(Line){b[u],ans[u]};
	update1(1,1,n,dfn[u],u);
}

void build(int x,int l,int r)
{
	cnt=max(cnt,x);
	if(l==r) return;
	build(lc,l,mid);
	build(rc,mid+1,r);
}

void update1(int x,int l,int r,int p,int v)
{
	update2(x,1,200001,v);
	if(l==r) return;
	if(p<=mid) update1(lc,l,mid,p,v);
	else update1(rc,mid+1,r,p,v);
}

int query1(int x,int l,int r,int L,int R,int v)
{
	if(L<=l&&r<=R) return query2(x,1,200001,v);
	int res=1e18;
	if(L<=mid) res=min(res,query1(lc,l,mid,L,R,v));
	if(mid+1<=R) res=min(res,query1(rc,mid+1,r,L,R,v));
	return res;
}

void update2(int x,int l,int r,int v)
{
	if(l==r)
	{
		if(f(v,l-100001)<f(val[x],l-100001))
			val[x]=v;
		return;
	}
	if(c[v].k>c[val[x]].k)
	{
		if(f(v,mid-100001)<f(val[x],mid-100001))
		{
			if(!rcc[x])
			{
				rcc[x]=++cnt;
				val.push_back(0);
				lcc.push_back(0);
				rcc.push_back(0);
			}
			update2(rcc[x],mid+1,r,val[x]),val[x]=v;
		}
		else
		{
			if(!lcc[x])
			{
				lcc[x]=++cnt;
				val.push_back(0);
				lcc.push_back(0);
				rcc.push_back(0);
			}
			update2(lcc[x],l,mid,v);
		}
	}
	if(c[v].k<c[val[x]].k)
	{
		if(f(v,mid-100001)<f(val[x],mid-100001))
		{
			if(!lcc[x])
			{
				lcc[x]=++cnt;
				val.push_back(0);
				lcc.push_back(0);
				rcc.push_back(0);
			}
			update2(lcc[x],l,mid,val[x]);val[x]=v;
		}
		else
		{
			if(!rcc[x])
			{
				rcc[x]=++cnt;
				val.push_back(0);
				lcc.push_back(0);
				rcc.push_back(0);
			}
			update2(rcc[x],mid+1,r,v);
		}
	}
	if(c[v].k==c[val[x]].k)
	{
		if(f(v,mid-100001)<f(val[x],mid-100001))
			val[x]=v;
		return;
	}
}

int query2(int x,int l,int r,int v)
{
	if(x==0) return 1e18;
	int res=f(val[x],v-100001);
	if(l==r) return res;
	if(v<=mid) return min(res,query2(lcc[x],l,mid,v));
	else return min(res,query2(rcc[x],mid+1,r,v));
}
```

---

## 作者：JoaoFelix (赞：0)

我们发现求的式子是一个y = kx + b的形式

这可以用李超线段树！

接下来就是我们在树上处理李超树的问题，我们需要用到李超线段树合并，然后求最值即可！

这里讲一下如何李超树合并！

```cpp
inline LL calc(LL x, LL k, LL b) { return k * x + b; }
```

```cpp
inline void insert(int &rt, int l, int r, LL k, LL b) {
	if (!rt) {
		rt = ++cnt; t[cnt].k = k; t[cnt].b = b; return;
	}
	if (calc(l, k, b) <= calc(l, t[rt].k, t[rt].b) && calc(r, k, b) <= calc(r, t[rt].k, t[rt].b)) {
		t[rt].k = k; t[rt].b = b; return;
	}
	if (calc(l, k, b) >= calc(l, t[rt].k, t[rt].b) && calc(r, k, b) >= calc(r, t[rt].k, t[rt].b)) return;
	int mid = (l + r) >> 1;
	if (calc(mid, k, b) < calc(mid, t[rt].k, t[rt].b)) swap(t[rt].k, k), swap(t[rt].b, b);
	insert(ls[rt], l, mid, k, b);
	insert(rs[rt], mid + 1, r, k, b); 
}
```
我们方便起见要动态开点！

然后如果这个节点没有，代表这个节点一下也是没有的，因此我们可以直接
rt = ++cnt并且保存信息！

然后下面的和普通的李超树没有区别！

```cpp
inline int merge(int x, int y, int l, int r) {
	if (!x || !y) return x + y;
	int mid = (l + r) >> 1;
	ls[x] = merge(ls[x], ls[y], l, mid);
	rs[x] = merge(rs[x], rs[y], mid + 1, r);
	insert(x, l, r, t[y].k, t[y].b);
	return x;
}
```
merge和普通的线段树合并差不多，只是我们需要把y的信息插入合并的x里面！

接下来是Query，就完全和普通李超树的Query一样了！

```cpp
inline LL Query(int rt, int l, int r, int x) {
	if (!rt) return INFLL;
	LL ret = calc((LL)x, t[rt].k, t[rt].b);
	if (l == r) return ret;
	int mid = (l + r) >> 1;
	if (x <= mid) return min(ret, Query(ls[rt], l, mid, x));
	return min(ret, Query(rs[rt], mid + 1, r, x));
}
```
剩下的就是复杂度证明：这里由于篇幅原因，简单地说一下

大概是：

首先insert的复杂度是logN的，因为只要有一个没有出现的，我们直接return！

合并可以根据层数考虑一下，发现和普通的线段树合并一样，只是我们要在每次merge的时候insert一次，这导致复杂度多了一个log，因此是(logN)^2的！

所以总复杂度O(N*(logN)^2)，可以通过本题！



---

