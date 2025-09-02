# [ABC222F] Expensive Expense

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc222/tasks/abc222_f

AtCoder 王国は $ N $ 個の街と $ N-1 $ 個の道路からなります。  
 街には 街 $ 1 $, 街 $ 2 $, $ \dots $, 街 $ N $ と番号がついています。道路にも同様に 道路 $ 1 $, 道路 $ 2 $, $ \dots $, 道路 $ N-1 $ と番号が付いています。 道路 $ i $ は街 $ A_i $ と $ B_i $ を双方向に結んでいて、通過するときに $ C_i $ の通行料がかかります。すべての異なる街の組 $ (i,\ j) $ に対して、道路を経由して街 $ i $ から街 $ j $ に行くことができます。

今、列 $ D\ =\ (D_1,\ D_2,\ \dots,\ D_N) $ が与えられます。 $ D_i $ は街 $ i $ を観光するときにかかる費用です。 このとき、街 $ i $ から街 $ j $ への旅費 $ E_{i,j} $ を、(同じ道を $ 2 $ 回以上使わずに街 $ i $ から街 $ j $ へ向かうときにかかる通行料の和) に $ D_{j} $ を足したものとして定めます。

- 厳密に言い換えると、$ i\ -\ j $ 間の最短パスを $ i\ =\ p_0,\ p_1,\ \dots,\ p_{k-1},\ p_k\ =\ j $ として、街 $ p_{l} $ と街 $ p_{l+1} $ を結ぶ道路の通行料を $ c_l $ と置いたときに $ E_{i,j}\ =\ D_j\ +\ \displaystyle\sum_{l=0}^{k-1}\ c_l $ と定義します。

すべての $ i $ に対して、街 $ i $ を始点として他の街へ旅行したときにありえる旅費の最大値を求めてください。

- 厳密に言い換えると、すべての $ i $ に対して $ \max_{1\ \leq\ j\ \leq\ N,\ j\ \neq\ i}\ E_{i,j} $ を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ N-1) $
- $ 1\ \leq\ B_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ N-1) $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ N-1) $
- $ 1\ \leq\ D_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ N) $
- 整数の組 $ (i,j) $ が $ 1\ \leq\ i\ \lt\ j\ \leq\ N $ を満たすならば、街 $ i $ から街 $ j $ へいくつかの道路を通ることで移動できる。
- 入力はすべて整数である。

### Sample Explanation 1

すべての街の順序つき組 $ (i,j) $ に対して $ E_{i,j} $ を計算すると次のようになります。 - $ E_{1,2}\ =\ 2\ +\ 2\ =\ 4 $ - $ E_{1,3}\ =\ 5\ +\ 3\ =\ 8 $ - $ E_{2,1}\ =\ 2\ +\ 1\ =\ 3 $ - $ E_{2,3}\ =\ 3\ +\ 3\ =\ 6 $ - $ E_{3,1}\ =\ 5\ +\ 1\ =\ 6 $ - $ E_{3,2}\ =\ 3\ +\ 2\ =\ 5 $

## 样例 #1

### 输入

```
3
1 2 2
2 3 3
1 2 3```

### 输出

```
8
6
6```

## 样例 #2

### 输入

```
6
1 2 3
1 3 1
1 4 4
1 5 1
1 6 5
9 2 6 5 3 100```

### 输出

```
105
108
106
109
106
14```

## 样例 #3

### 输入

```
6
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
5 6 1000000000
1 2 3 4 5 6```

### 输出

```
5000000006
4000000006
3000000006
3000000001
4000000001
5000000001```

# 题解

## 作者：_zzzzzzy_ (赞：4)

# 思路
我们可以用一个巧妙的操作把点权变成边权，可以新建一个 $i+n$ 的点边权是 $d_i$ 这样。

然后对于第 $i$ 个点距离最远的点是两个端点中的一个，我们就把这一个问题转化成了求树的直径。

我们考虑怎么求左端点，可以对于节点 $1$ 求一遍距离，离最远的就是左节点。

然后我们可以通过左端点求出右端点，最后跑一遍右端点，如果枚举到的点是左端点，那么不可能走到左端点，如果是右端点也同理。

如果枚举到的不是左右端点，那就直接取距离两个端点最远的就行了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=10000000;
int n,h[maxn],tot,dis1[maxn],disl[maxn],disr[maxn],l=1,r=1;
struct edge{int to,nxt,w;}e[maxn];
void add(int u,int v,int w){
	e[++tot].to=v;
	e[tot].nxt=h[u];
	e[tot].w=w;
	h[u]=tot;
}
void dfs(int u,int fa,int dis[]){
	for (int i=h[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v!=fa){
			dis[v]=dis[u]+e[i].w;
			dfs(v,u,dis);
		}
	}
}
signed main() {
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	for (int i=1;i<=n;i++){
		int x;
		cin>>x;
		add(i,n+i,x);
		add(n+i,i,x);
	}
	dfs(1,0,dis1);
	int l=max_element(dis1+1,dis1+1+2*n)-dis1;
	dfs(l,0,disl);
	int r=max_element(disl+1,disl+1+2*n)-disl;
	dfs(r,0,disr);
	for (int i=1;i<=n;i++){
		if(i==l-n){
			cout<<disr[i]<<"\n";
		}
		else if(i==r-n){
			cout<<disl[i]<<"\n";
		}
		else{
			cout<<max(disl[i],disr[i])<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：In_Memory (赞：3)

# 题目大意
给出一棵有边权的无向树，每个点有点权 $d_u$。定义一条路径的权值为路径上经过的所有边的边权和再加上终点的点权。求从每个点出发权值最大的路径。
# 解法说明
首先考虑，如果只求从 $1$ 出发的最长路径怎么做。设 $f_u$ 表示以 $1$ 为根，起点为 $u$，终点在 $u$ 子树中所可以得到的最大权值。显然有转移 $f_u = \max\limits_{v \in son_u} (f_v + w_{u, v})$。此时 $f_1$ 就是我们要的答案。在树上跑一遍 `DFS` 就可以求出来。注意我们在这里将 $u \rightarrow u$ 算做一条权值为 $d_u$ 的路径，以处理路径权值要加上终点点权的要求。
```cpp
void dfs1(int u,int fa)
{
	int v,i;
	f[u]=d[u];
	for(i=0;i<s[u].size();i++)
	{
		v=s[u][i].v;
		if(v==fa)
			continue;
		dfs1(v,u);
		f[u]=max(f[u],f[v]+s[u][i].w);
	}
}
```
题目要我们求出 $1 \thicksim n$ 每个点的最大权值，但时间不允许我们对每个点都做一次以上操作。考虑当根变换时会发生什么。先看到这样一棵树。（括号内的数为点权，括号外的数为编号。）

![以1为根的树](https://cdn.luogu.com.cn/upload/image_hosting/z9mht5qt.png?x-oss-process=image/resize,m_lfit,h_800,w_1200)

这个时候我们将根换为 $2$，看看它有什么变化。

![以2为根的树](https://cdn.luogu.com.cn/upload/image_hosting/209s2sci.png?x-oss-process=image/resize,m_lfit,800,w_1200)

设 $g_u$ 表示 $u$ 点走到其他点的最长路径，则 $g_1 = f_1$。考虑怎么由 $g_1$ 转移 $g_2$。我们发现，$g_2$ 由两部分构成，一部分是原树上自己的子树，一部分是原本的根节点。但 $g_1$ 也变了，$2$ 不再对 $1$ 有贡献，应当在 $g_1$ 中剔除 $2$。

考虑如何实现快速剔除。最值操作显然不支持差分。如何处理？

我们可以对每个点 $u$ 记录它儿子 $f$ 值的前缀最大值 $pre$ 和后缀最大值 $suf$。当根从 $u$ 换到第 $i$ 个儿子 $v$ 时，就将 $g_u$ 赋值为 $\max\{pre_{i - 1}, suf_{i + 1}\}$ 剔除 $v$ 的贡献。则 $g_2 = \max\{f_2, g_1 + w_{1, 2}\}$。

然后就可以换根了。注意根换完后 $g_u$ 要还原。
```cpp
void dfs2(int u,int fa)
{
	int v,i;
	pre[u].push_back(INT_MIN);
	for(i=1;i<=s[u].size();i++)
	{
		v=s[u][i-1].v;
		if(v==fa)
			pre[u].push_back(max(pre[u][i-1],g[v]+s[u][i-1].w));	//注意到 fa 此时也是 u 的一个儿子，但 f[fa] 里有 u 的贡献，所以必须用剔除了 u 贡献的 g[fa]。
		else
			pre[u].push_back(max(pre[u][i-1],f[v]+s[u][i-1].w));		
	}
	suf[u].push_back(INT_MIN);
	for(i=s[u].size();i>=1;i--)
	{
		v=s[u][i-1].v;
		if(v==fa)
			suf[u].push_back(max(suf[u][s[u].size()-i],g[v]+s[u][i-1].w));	//解释同上。
		else
			suf[u].push_back(max(suf[u][s[u].size()-i],f[v]+s[u][i-1].w));			
	}
	for(i=0;i<=(s[u].size()+1)/2;i++)
		swap(suf[u][i],suf[u][s[u].size()-i+1]);//vector 只能从后端插入，suf 的顺序是反的，需要交换。
	for(i=1;i<=s[u].size();i++)
	{
		v=s[u][i-1].v;
		if(v==fa)
			continue;
		g[u]=max(d[u],max(pre[u][i-1],suf[u][i+1]));//剔除 v 贡献。
		g[v]=max(f[v],s[u][i-1].w+g[u]);
		dfs2(v,u);
		g[u]=max(g[u],f[v]+s[u][i-1].w);//还原。
	}
}
```
但是，这样求出来的结果真的会将 $u \rightarrow u$ 当作一条权值为 $d_u$ 的路径，而这不符合题意。处理方法很简单，记录 $h\_f$ 和 $h\_g$ 数组表示剔除自己的贡献后的答案，与 $f$ 和 $g$ 一样转移即可。注意转移都要用 $f$ 和 $g$，不要用 $h\_f$ 和 $h\_g$ 数组更新别人。

完整代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tim,bfn[210000],l[210000],r[210000];
long long d[210000],f[210000],g[210000],h_f[210000],h_g[210000];
bool used[210000];
struct edge
{
	int v;
	long long w;
};
vector<long long> pre[210000],suf[210000];
vector<edge> s[210000];
void dfs1(int u,int fa)
{
	int v,i;
	f[u]=d[u];
	h_f[u]=INT_MIN;
	for(i=0;i<s[u].size();i++)
	{
		v=s[u][i].v;
		if(v==fa)
			continue;
		dfs1(v,u);
		f[u]=max(f[u],f[v]+s[u][i].w);
		h_f[u]=max(h_f[u],f[v]+s[u][i].w);
	}
}
void dfs2(int u,int fa)
{
	int v,i;
	pre[u].push_back(INT_MIN);
	for(i=1;i<=s[u].size();i++)
	{
		v=s[u][i-1].v;
		if(v==fa)
			pre[u].push_back(max(pre[u][i-1],g[v]+s[u][i-1].w));	
		else
			pre[u].push_back(max(pre[u][i-1],f[v]+s[u][i-1].w));		
	}
	suf[u].push_back(INT_MIN);
	for(i=s[u].size();i>=1;i--)
	{
		v=s[u][i-1].v;
		if(v==fa)
			suf[u].push_back(max(suf[u][s[u].size()-i],g[v]+s[u][i-1].w));	
		else
			suf[u].push_back(max(suf[u][s[u].size()-i],f[v]+s[u][i-1].w));			
	}
	for(i=0;i<=(s[u].size()+1)/2;i++)
		swap(suf[u][i],suf[u][s[u].size()-i+1]);
	for(i=1;i<=s[u].size();i++)
	{
		v=s[u][i-1].v;
		if(v==fa)
			continue;
		g[u]=max(d[u],max(pre[u][i-1],suf[u][i+1]));
		g[v]=max(f[v],s[u][i-1].w+g[u]);
		h_g[v]=max(h_f[v],s[u][i-1].w+g[u]);
		dfs2(v,u);
		g[u]=max(g[u],f[v]+s[u][i-1].w);
	}
}
int main()
{
	int u,v,i;
	long long w;
	cin>>n;
	for(i=1;i<n;i++)
	{
		cin>>u>>v>>w;
		s[u].push_back((edge){v,w});
		s[v].push_back((edge){u,w});
	}
	for(i=1;i<=n;i++)
		cin>>d[i];
	dfs1(1,0);
	h_g[1]=h_f[1];
	dfs2(1,0);
	for(i=1;i<=n;i++)
		cout<<h_g[i]<<endl;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/185669332)

---

## 作者：creepier (赞：1)

题面要求求每个点的答案，考虑换根。因为有 $d$ 数组的限制，每次维护所有点与当前点的距离。每次换根时子树内的点距离减 1，子树外的点距离加 1，可以转化为 dfn 序上最多 3 个区间的区间加，同时维护最大值，用线段树实现。换回根时减去相应贡献即可。注意统计最长距离时不要算上自己，虽然不知道数据中有没有这样的点。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5+100;
int n,b[N];
struct edge{int t,w;};vector<edge> a[N];
int d[N];
int dfn[N],udfn[N],ls[N],tot;
void dfs2(int x,int fa)
{
	dfn[x]=ls[x]=++tot;
	udfn[dfn[x]]=x;
	for(auto i:a[x])
	{
		if(i.t==fa)continue;
		dfs2(i.t,x);
	}
	ls[x]=tot;
}
void dfs(int x,int fa)
{
	for(auto i:a[x])
	{
		if(i.t==fa)continue;
		d[i.t]=d[x]+i.w;
		dfs(i.t,x);
	}
}
namespace sg
{
	struct node
	{
		int add,mx;
	}t[N*4];
	#define ll (x<<1)
	#define rr (x<<1|1)
	#define xx (t[x])
	#define mid ((l+r)>>1)
	void build(int x,int l,int r)
	{
		if(l==r){xx.mx=d[udfn[l]];return;}
		build(ll,l,mid);
		build(rr,mid+1,r);
		xx.mx=max(t[ll].mx,t[rr].mx);
	}
	inline void add(int l1,int r1,int l,int r,int x,int val)
	{
		if(l>=l1&&r<=r1){xx.add+=val,xx.mx+=val;return;}
		if(l1<=mid)add(l1,r1,l,mid,ll,val);
		if(r1>mid)add(l1,r1,mid+1,r,rr,val);
		xx.mx=max(t[ll].mx,t[rr].mx)+xx.add;
	}
	inline int get(int pos,int l,int r,int x)
	{
		if(l==r)return t[x].mx;
		if(pos<=mid)return get(pos,l,mid,ll)+xx.add;
		else return get(pos,mid+1,r,rr)+xx.add;
	}
	#undef ll
	#undef rr
	#undef xx
	#undef mid
}
using namespace sg;
int ans[N];
void dfs1(int x,int fa)
{
	add(dfn[x],dfn[x],1,n,1,-b[x]);
	// assert(get(dfn[x],1,n,1)==0);
	ans[x]=t[1].mx;
	add(dfn[x],dfn[x],1,n,1,b[x]);
	for(auto i:a[x])
	{
		if(i.t==fa)continue;
		add(dfn[i.t],ls[i.t],1,n,1,-i.w);
		if(dfn[i.t]!=1)add(1,dfn[i.t]-1,1,n,1,i.w);
		if(ls[i.t]!=n)add(ls[i.t]+1,n,1,n,1,i.w);
		dfs1(i.t,x);
		add(dfn[i.t],ls[i.t],1,n,1,i.w);
		if(dfn[i.t]!=1)add(1,dfn[i.t]-1,1,n,1,-i.w);
		if(ls[i.t]!=n)add(ls[i.t]+1,n,1,n,1,-i.w);
	}
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	int x,y,z;
	for(int i=1;i<n;i++){cin>>x>>y>>z;a[x].push_back({y,z});a[y].push_back({x,z});}
	for(int i=1;i<=n;i++)cin>>b[i];
	dfs2(1,0);
	dfs(1,0);
	for(int i=1;i<=n;i++)d[i]+=b[i];
	build(1,1,n);
	dfs1(1,0);
	for(int i=1;i<=n;i++)cout<<ans[i]<<'\n';
}
```

---

## 作者：Shunpower (赞：1)

## 思路

我很不懂树的直径的性质啊！怎么办？

注意到想要求每个点的某种神秘树上距离最大值，我们考虑线段树强行维护答案，操作换根。下文中的距离即指题目中新定义的距离。

我们先将树用 DFS 序拍扁，这样一个子树就被表示为了连续的一段区间，然后我们考虑在子树 $u$ 时我们怎么做。

首先确保我们进入 $u$ 子树时，$d_u$ 已经从线段树中清掉，这样我们可以直接在进入某个子树时调用线段树根的最大值得到答案。

然后把 $u$ 的 $d$ 值放回去，很明显在此之后 $u$ 应当一直存在于线段树中，不再被清掉了，因为没有哪个点获取答案时需要排除 $d_u$。

接下来枚举儿子，考虑换根。假设走向一个儿子，这将导致儿子子树中每一个点到根的距离都减少这条经过的边的边权 $w$，而其他所有点到根的距离都将增加 $w$，这可以直接使用线段树先全体加 $w$ 再区间减 $2w$ 维护。走入儿子之前还需要将儿子的 $d$ 从线段树中清掉，方便儿子获取答案。

处理完 $u$ 子树的所有答案，考虑将根回溯到 $u$ 的父亲。此时 $u$ 子树中每一个点到根的距离都将减少回溯到父亲的这条边的边权 $w'$，而其他所有点到根的距离都将减少 $w'$，同理可以使用线段树先全体减 $w'$ 再区间加 $2w'$ 维护。

于是我们就用线段树暴力维护了换根操作，时间复杂度 $\mathcal O(n\log n)$，注意修改线段树时传入的下标要转为 DFS 序，得到根为 $1$ 时的初始距离要将这个距离放在下标为 DFS 序的位置上再建树，DFS 开始之前要清掉 $d_1$。

## 代码

只有 DFS 部分。线段树中 `insert` 为单点修改，`modify` 为区间加法，`maxn` 维护最大值。

```
void calc(int x,int fa,int fr){
    // cout<<"!"<<x<<endl;
    // T.draw(1,1,n);
    ans[x]=T.maxn[1];
    T.insert(1,1,n,dfn[x],d[x]);
    fv(i,p[x]){
        int y=p[x][i].fi,v=p[x][i].se;
        if(y==fa){
            continue;
        }
        T.modify(1,1,n,1,n,v);
        T.modify(1,1,n,dfn[y],dfn[y]+siz[y]-1,-2*v);
        T.insert(1,1,n,dfn[y],0);
        calc(y,x,v);
    }
    T.modify(1,1,n,1,n,-fr);
    T.modify(1,1,n,dfn[x],dfn[x]+siz[x]-1,2*fr);
}
```

---

## 作者：GI录像机 (赞：1)

## 思路：

我们知道，在一棵树上，离任意一个点最远的点就是树的直径的端点，我们可以通过两次 dfs 求出树直径的端点。

对于本题多出的 $d_i$，我们可以将其等效成树上的一个点，其父亲为 $i$ 点。

这样对于每一个 $i$，只用计算它离直径上的哪个端点更远就行了，分别以两个端点为根 dfs，就求出每个点和端点的距离。由于题目中 $i\neq j$ 的限制，当 $i$ 是其中一个端点的父亲时，只能取与另一个端点的距离。证明也很简单，如果 $i$ 到 $k$ 的距离大于 $i$ 到另一个端点的距离，直径就应该是 $k$ 到 $i$ 的儿子。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), head[N << 1], tot, d[N], dis1[N << 1], disl[N << 1], disr[N << 1], l = 1, r = 1;
struct Node {
	int to, nxt, w;
} e[N << 2];
void add(int u, int v, int w) {
	e[++tot].to = v;
	e[tot].nxt = head[u];
	e[tot].w = w;
	head[u] = tot;
}
void dfs1(int pos, int fa) {
	for (int i = head[pos]; i; i = e[i].nxt) {
		if (e[i].to == fa)continue;
		dis1[e[i].to] = dis1[pos] + e[i].w;
		if (dis1[e[i].to] > dis1[l])l = e[i].to;
		dfs1(e[i].to, pos);
	}
}
void dfsl(int pos, int fa) {
	for (int i = head[pos]; i; i = e[i].nxt) {
		if (e[i].to == fa)continue;
		disl[e[i].to] = disl[pos] + e[i].w;
		if (disl[e[i].to] > disl[r])r = e[i].to;
		dfsl(e[i].to, pos);
	}
}
void dfsr(int pos, int fa) {
	for (int i = head[pos]; i; i = e[i].nxt) {
		if (e[i].to == fa)continue;
		disr[e[i].to] = disr[pos] + e[i].w;
		dfsr(e[i].to, pos);
	}
}
signed main() {
	for (int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		add(u, v, w);
		add(v, u, w);
	}
	for (int i = 1; i <= n; i++) {
		d[i] = read();
		add(i, n + i, d[i]);
		add(n + i, i, d[i]);
	}
	dfs1(1, 0);
	dfsl(l, 0);
	dfsr(r, 0);
	for (int i = 1; i <= n; i++) {
		write(max(l - n != i ? disl[i] : 0, r - n != i ? disr[i] : 0));
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：YuYuanPQ (赞：0)

这题不是独立切的，但是看了题解后发现自己没想到用线段树维护，大失败。

---
树上问题，$N\leq 2\times 10^5$，要求每一个点的答案。\
综上，我们可以想到换根 DP。

先不换根，设 $f_i$ 表示 $i$ 到以 $i$ 为根的子树内的点 $j$ 这条路径的边权和的最大值。
于是做树形 DP，枚举到以 $i$ 为根的子树时，对于每个子树内的节点 $j$，转移是显然的：
$$f_i=\max(d_i,f_j+w_{i,j})$$

然后做换根 DP，思考一下换根的时候答案会怎么改：\
令父节点为 $x$，子节点为 $y$。
- 当根从 $x$ 换为 $y$ 时，因为少了一条边，所以在以 $y$ 为根的子树内，每个点都要减去 $w_{x,y}$；而在子树外，每个点都要加上 $w_{x,y}$。
- 当根从 $y$ 换为 $x$ 时，显然，在以 $y$ 为根的子树内，每个点都要加上 $w_{x,y}$；而在子树外，每个点都要减去 $w_{x,y}$。

怎么高效维护？\
用线段树维护单点最大值，并支持查询区间和。

我们发现，一个子树内的修改是好做的，因为子树内的点的 DFS 序是一段连续区间，所以只需要求 DFS 序来维护即可。\
但是怎么修改子树外的所有点呢？\
用差分来做就方便了：\
先对所有点做一次操作，再对子树内的做一次，使得其抵消了第一次操作的影响并且达到目的。\
很经典，没学过的去看看树上差分板题吧。

具体实现如下：
- 当根从 $x$ 换为 $y$ 时，先把所有点 $+w_{x,y}$，再把以 $x$ 为根的子树内的点 $-2\times w_{x,y}$。
- 当根从 $y$ 换为 $x$ 时，先把所有点 $-w_{x,y}$，再把以 $x$ 为根的子树内的点 $+2\times w_{x,y}$。

注意：在点 $x$ 查询其答案时，为避免重复计算需要先 $-d_x$。

## Code
[Link](https://atcoder.jp/contests/abc222/submissions/62949476)

---

## 作者：ben090302 (赞：0)

# [ABC222F]

第一眼想跑最长路，但是最长路自己的复杂度和这题的奇怪点权共同告诉咱这个想法不行。

感觉貌似想的有点歪，可能不太正常这个解法，我是数据结构魔怔人。
 
我们设 $dp_u$ 表示 $u$ 到 $u$ 子树内一点路径加末点权的最大值，先以 $1$ 为根跑一遍。

转移应该是简单的， $dp_u=\max(d_u,\max\limits_{v\in son_u} w(u,v)+dp_v)$，边界显然是叶子的答案为自己的点权，于是我们能够线性求出以某个点为根的答案。

 考虑换根，假设从 $u$ 把根变成 $v$ 不难发现答案会变化的只有 $u$ 和 $v$ ， $dp_v$ 需要跟 $w(u,v)+dp_u$ 取一下 $\max$，所以 $v$ 是简单的，因为 $v$ 相当于增加一个子树，但是 $u$ 的效果不太一样， $u$ 相当于自己砍掉了一个子树，那么 $u$ 需要从他的所有儿子（除了 $v$ ，当然的）重新取答案,这样遍历肉眼可见复杂度不太对劲，据说用bfs序可以搞但是我不太敢写。
 
于是我们换一种换根的脑回路，我们不希望再去留着每一个点的 $dp$ 值等着他去贡献一步步算，我们尝试动态计算。

从父亲 $u$ 换到子 $v$ 的时候，造成的影响是什么？显然就是新根到子树内的所有点的 $dp$ 值变为父亲为根时的减去 $w(u,v)$，$v$ 子树外的加上 $w(u,v)$，我们设 $f_u$ 表示当前根到 $u$ 的距离，我们可以用线段树维护 $f$ 数组，换根同时取 $\max$ 即可。

如何实现线段树的维护？可以用 dfs 序，这样我们实现的操作就是区间加、区间最大值了。

于是完成了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
struct edge{
    int v,w,nxt;
}e[N];
int tot,hd[N];
void add(int u,int v,int w){
    e[++tot]={v,w,hd[u]},hd[u]=tot;
}
int n;
int d[N];
struct node{
    int val,tag;
}tr[N*4];
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
void pushup(int rt){
    tr[rt].val=max(tr[ls].val,tr[rs].val);
}
void pushdown(int rt,int l,int r){
    if(!tr[rt].tag) return;
    int k=tr[rt].tag;tr[rt].tag=0;
    tr[ls].tag+=k,tr[rs].tag+=k;
    tr[ls].val+=k,tr[rs].val+=k;
}
void modi(int rt,int l,int r,int L,int R,int k){
    if(L<=l and r<=R){
        tr[rt].val+=k;
        tr[rt].tag+=k;
        return;
    }
    if(l>R or r<L) return;
    pushdown(rt,l,r);
    modi(ls,l,mid,L,R,k);
    modi(rs,mid+1,r,L,R,k);
    pushup(rt);
}
int query(int rt,int l,int r,int L,int R){
    if(L<=l and r<=R) return tr[rt].val;
    if(L>r or l>R) return 0;
    pushdown(rt,l,r);
    return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
}
int dfn[N],idx,nfd[N],ot[N];
void dfs(int u,int fa,int sum){
    dfn[u]=++idx;
    nfd[idx]=u;
    modi(1,1,n,idx,idx,sum+d[u]);
    for(int i=hd[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        dfs(v,u,sum+e[i].w);
    }
    ot[u]=idx;
}
int ans[N];
void gt(int u,int fa,int w){
    modi(1,1,n,1,n,w);
    modi(1,1,n,dfn[u],ot[u],-2*w);
    modi(1,1,n,dfn[u],dfn[u],-d[u]);
    ans[u]=query(1,1,n,1,n);
    modi(1,1,n,dfn[u],dfn[u],d[u]);
    for(int i=hd[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        gt(v,u,e[i].w);
    }
    modi(1,1,n,1,n,-w);
    modi(1,1,n,dfn[u],ot[u],2*w);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w),add(v,u,w);
    }
    for(int i=1;i<=n;i++) cin>>d[i];
    dfs(1,0,0);
    gt(1,0,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<"\n";
    }
}
```

---

## 作者：tanshunyu0913 (赞：0)

# [ABC222F] Expensive Expense 题解
## 题目描述
给你一棵树，每条边有边权，每个点有点权，定义 $i$ 到 $j$ 的距离为 $i$ 到 $j$ 的路径上的所有边的边权和加上 $j$ 的点权，问每一个点到其它点的最长距离。
## 思路
看到最长距离，很容易想到树的直径，但是我们还有点权要处理。这时我们可以给每一个点建一个虚拟点，该点到它的虚拟点的边权为该点的点权，此时再求直径就可以了。

我们以直径的两个端点为根遍历整棵树，并记录每一个点到根的距离，根据直径的定义，树上每一个点到其它点的最长距离一定是到直径的两个端点中的一个的距离。

不过我们注意一个点不能到自己，如果直径的一个端点是 $i$ 的虚拟点，那么 $i$ 到其它点的最长距离一定是 $i$ 到直径的另一个端点的距离。
## 代码
```cpp
#include<bits/stdc++.h>
#define to first
#define w second
using namespace std;
typedef long long ll;
typedef pair<int,ll> PIL;
const int N=2e5+10; 
vector<PIL> e[N*2];//因为有虚拟点的存在所以开2N
int n;
ll d[N],dep[N],dp[N],dq[N],S=0;//dp[i]表示i到p（直径的一个端点）的距离
void dfs(int u,int fa){
	if(dep[u]>dep[S])S=u;
	for(auto v:e[u]){
		if(v.to==fa)continue;
		dep[v.to]=dep[u]+v.w;
		dfs(v.to,u);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;ll w;cin>>u>>v>>w;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	for(int i=1;i<=n;i++){
		cin>>d[i];
		e[i].push_back({n+i,d[i]});
		e[n+i].push_back({i,d[i]});
	}
	dfs(1,0);int p=S;S=0;dep[p]=0;//请注意对距离数组的清空
	dfs(p,0);int q=S;S=0;dep[q]=0;
	memcpy(dp,dep,sizeof dep);
	dfs(q,0);
	memcpy(dq,dep,sizeof dep);
	for(int i=1;i<=n;i++){
		if(i+n==q)cout<<dp[i];
		else if(i+n==p)cout<<dq[i];
		else cout<<max(dp[i],dq[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：ChenYanlin_20 (赞：0)

### 思路：这道题有点权，又有边权，~~听老师说~~可以建虚拟点来做。
我们将 $i$ 点的虚拟点设置为 $i+n$，数组要开 $2n$。求出树的直径端点，两端端点为 $t$，$s$。然后对于每一个点，找端点两边距离最大一个。注意：当 $i+n=t$ 或 $i+n=s$ 时，由于自己不能走向自己，所以只能取另一端点。
### CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5;
map<pair<int,int>,int> mp;
vector<int> n[N];
int d[N],dge[N],tt[N],ss[N],s;
void dfs(int u,int fa){
	dge[u]=dge[fa]+mp[{u,fa}];
	for(int i=0;i<n[u].size();i++){
		int j=n[u][i];
		if(j==fa) continue;
		dfs(j,u);
	}
}
signed main(){
	int di;
	cin>>di;
	for(int i=1;i<di;i++){
		int a,b,c;
		cin>>a>>b>>c;
		n[a].push_back(b);
		n[b].push_back(a);
		mp[{a,b}]=c;
		mp[{b,a}]=c;
	}
	for(int i=1;i<=di;i++){
		cin>>d[i];
		n[i].push_back(i+di);
		n[i+di].push_back(i);
		mp[{i,i+di}]=d[i];
		mp[{di+i,i}]=d[i];
	}
	
	dfs(1,0);
	int maxx=dge[1],t=1;
	for(int i=2;i<=di*2;i++){
		if(dge[i]>maxx){
			maxx=dge[i];
			t=i;
		}
	}
	
	dge[0]=0,dge[t]=0;
	dfs(t,0);
	for(int i=1;i<=di*2;i++){
		tt[i]=dge[i];
	}
	
	maxx=dge[1],s=1;
	for(int i=2;i<=di*2;i++){
		if(dge[i]>maxx){
			maxx=dge[i];
			s=i;
		}
	}
	dfs(s,0);
	for(int i=1;i<=di*2;i++){
		ss[i]=dge[i];
	}
//	cout<<t<<' '<<s;
	for(int i=1;i<=di;i++){
		if(i+di==t) cout<<ss[i]<<'\n';
		else if(i+di==s) cout<<tt[i]<<'\n';
		else cout<<max(ss[i],tt[i])<<'\n';
	}
	return 0;
}

```


---

## 作者：mz2022 (赞：0)

~~今天队测出了这题，来淼一发题解，人生第一发蓝题题解！！！~~

思路：
--------
题目要求每个点到其他点的最长距离，显然离一个点最远的点必定是树的直径两个端点之中的一个。

但是我们还有一个问题，就是这个 ${d_i}$ 不好处理，所以我们建出一个 $i$ 到 $i+n$ 的点边权为 ${d_i}$，然后跑树的直径求出距两个端点最远的就可以了。

Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//记得开long long!!! 
struct tree
{
	int node,val;
	
};
const int N=4e5+5;//数组这里要开两倍。 
vector<tree> g[N];
int n,maxx=-INT_MAX,maxn,l[N],l1[N],l2[N];
bool f[N];
void add(int uu,int vv,int ww)
{
	g[uu].push_back({vv,ww});
}
void clear()
{		
	memset(f,0,sizeof(f));
	memset(l,0,sizeof(l));
	maxx=-INT_MAX;
	maxn=0;
}
void dfs(int now)// 
{
	f[now]=true;
	for(int i=0;i<g[now].size();i++)
	{
		int node=g[now][i].node;
		int val=g[now][i].val;
		if(!f[node])
		{
			l[node]=l[now]+val;
			if(l[node]>maxx)
			{
				maxx=l[node];
				maxn=node;
			}
			dfs(node); 
		}
	}
}
void dfs_l1(int now)
{
	f[now]=true;
	for(int i=0;i<g[now].size();i++)
	{
		int node=g[now][i].node;
		int val=g[now][i].val;
		if(!f[node])
		{
			l1[node]=l1[now]+val;
			if(l1[node]>maxx)
			{
				maxx=l1[node];
				maxn=node;
			}
			dfs_l1(node); 
		}
	}
}
void dfs_l2(int now)
{
	f[now]=true;
	for(int i=0;i<g[now].size();i++)
	{
		int node=g[now][i].node;
		int val=g[now][i].val;
		if(!f[node])
		{
			l2[node]=l2[now]+val;
			if(l2[node]>maxx)
			{
				maxx=l2[node];
				maxn=node;
			}
			dfs_l2(node); 
		}
	}
}
signed main()
{
	cin>>n;
	for(int u,v,w,i=1;i<=n-1;i++)
	{
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	} 
	for(int d,i=1;i<=n;i++)
	{
		cin>>d;
		add(i,i+n,d);//建一个类似于虚点的东西。 
		add(i+n,i,d);
	}
	dfs(1);
	int first=maxn;
	clear();
	dfs_l1(first);
	int last=maxn;
	clear();
	dfs_l2(last);//求出树的直径的左右端点，并算出距每个点的距离。 
	for(int i=1;i<=n;i++)
	{
		if(last==i+n)cout<<l1[i]<<endl;//这里注意右端点是不能走到右端点的，左端点也是一样。 
		else if(first==i+n)cout<<l2[i]<<endl;
		else cout<<max(l1[i],l2[i])<<endl;//求出距两个端点最远的就可以了 
	}
	return 0;
} 
```

---

## 作者：AlicX (赞：0)

## Solution 

不会推性质和直径怎么办？当然是线段树换根！

首先不难发现由 $fa$ 转移到 $u$ 对于其它节点的影响有两种：

1. $v$ 是 $u$ 子树内的节点，此时 $v$ 的路径和应减去 $w$，$w$ 为 $fa$ 到 $u$ 的边权。

2. $v$ 不是 $u$ 子树内的节点，此时 $v$ 的路径和应加上 $w$。

如果将路径和与点权一起放到线段树里，不难发现每次换根后直接求最大值即可。注意不能取自己。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define debug() puts("-------") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10; 
int n; 
int mp[N]; 
int cnt=0; 
int ans[N];
int a[N],f[N];  
int h[N],idx=0; 
int in[N],out[N];
struct Edge{
	int w; 
	int to,ne; 
}e[N<<1]; 
struct Node{
	int l,r; 
	int w,add; 
}tr[N<<2]; 
void add(int u,int v,int w){
	e[idx].w=w,e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
void pushup(int u){
	tr[u].w=max(tr[u<<1].w,tr[u<<1|1].w);  
} 
void pushdown(int u){ 
	if(!tr[u].add) return ; 
	tr[u<<1].w+=tr[u].add,tr[u<<1|1].w+=tr[u].add; 
	tr[u<<1].add+=tr[u].add,tr[u<<1|1].add+=tr[u].add,tr[u].add=0; 
} 
void build(int u,int l,int r){ 
	tr[u]={l,r,0,0}; 
	if(l==r){ 
		tr[u].w=a[mp[l]]; 
		return ; 
	} int mid=(l+r)>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	pushup(u); 
} 
void modify(int u,int l,int r,int w){ 
	if(l<=tr[u].l&&tr[u].r<=r){ 
		tr[u].w+=w,tr[u].add+=w; 
		return ; 
	} pushdown(u); 
	int mid=(tr[u].l+tr[u].r)>>1; 
	if(l<=mid) modify(u<<1,l,r,w); 
	if(r>mid) modify(u<<1|1,l,r,w); 
	pushup(u); 
} 
int query(int u,int l,int r){ 
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w; 
	pushdown(u); int w=0,mid=(tr[u].l+tr[u].r)>>1; 
	if(l<=mid) w=query(u<<1,l,r); 
	if(r>mid) w=max(w,query(u<<1|1,l,r)); 
	return w; 
} 
void dfs(int u,int fa){ 
	in[u]=++cnt; mp[cnt]=u; 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		f[to]=f[u]+e[i].w; dfs(to,u); 
	} out[u]=cnt; 
} 
void work(int u,int fa,int w){ 
	modify(1,1,n,w); 
	modify(1,in[u],out[u],-w*2); 
	modify(1,in[u],in[u],-a[u]); 
	ans[u]=query(1,1,n); 
	modify(1,in[u],in[u],a[u]); 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		work(to,u,e[i].w); 
	} modify(1,1,n,-w); 
	modify(1,in[u],out[u],w*2); 
} 
signed main(){ 
	memset(h,-1,sizeof h); 
	scanf("%lld",&n); 
	for(int i=1;i<n;i++){ 
		int u,v,w; 
		scanf("%lld%lld%lld",&u,&v,&w); 
		add(u,v,w),add(v,u,w); 
	} for(int i=1;i<=n;i++) scanf("%lld",&a[i]); 
	dfs(1,0); build(1,1,n); 
	for(int i=1;i<=n;i++) modify(1,in[i],in[i],f[i]); 
	work(1,0,0); for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);  
	return 0; 
} /*
3
1 2 2
2 3 3
1 2 3

6
1 2 3
1 3 1
1 4 4
1 5 1
1 6 5
9 2 6 5 3 100

*/
```


---

## 作者：WaterSun (赞：0)

板子题，模拟赛场切了。

# 思路

线段树换根板子题。

因为需要求每一个点的答案，所以定义 $dp_i$ 表示以 $i$ 为根的最长距离。

考虑将一个点 $v$ 转化为根，树的形态会发生什么变化（假设 $v$ 的父亲节点是 $u$）。

发现在 $v$ 子树中的节点，距离都会减少 $w_{u \to v}$，其它节点都会加 $w_{u \to v}$。这个变化显然是可以将 DFS 序剖出来，然后用线段树优化的。

因为不能选择自己作为终点，所以查询最大值的时候避开即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10;
int n;
int dp[N];
int idx,h[N],ne[M],e[M],w[M],p[N];
int num,f[N],d[N],sz[N],wson[N],id[N],tp[N];

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

inline void add(int a,int b,int c){
    ne[idx] = h[a];
    e[idx] = b;
    w[idx] = c;
    h[a] = idx++;
}

struct chain{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int Max,tag;
    }tr[N << 2];

    inline void calc(int u,int k){
        tr[u].Max += k;
        tr[u].tag += k;
    }

    inline void pushup(int u){
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag);
            calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(u),l,mid);
        build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r){
            calc(u,k);
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    inline int query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].Max;
        pushdown(u);
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res = max(res,query(ls(u),l,r));
        if (r > mid) res = max(res,query(rs(u),l,r));
        return res;
    }

    inline void modify_node(int x,int k){
        modify(1,id[x],id[x],k);
    }

    inline void modify_tree(int x,int k){
        modify(1,id[x],id[x] + sz[x] - 1,k);
    }

    inline int query_sec(int l,int r){
        if (l > r) return 0;
        return query(1,l,r);
    }

    #undef ls
    #undef rs
}tree;

inline void dfs1(int u,int fa){
    sz[u] = 1;
    f[u] = fa;
    d[u] = d[fa] + 1;
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs1(j,u);
        if (sz[j] > sz[wson[u]]) wson[u] = j;
        sz[u] += sz[j];
    }
}

inline void dfs2(int u,int fa,int top){
    num++;
    id[u] = num;
    tp[u] = top;
    if (!wson[u]) return;
    dfs2(wson[u],u,top);
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa || j == wson[u]) continue;
        dfs2(j,u,j);
    }
}

inline void dfs_val(int u,int fa,int d){
    tree.modify_node(u,d + p[u]);
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs_val(j,u,d + w[i]);
    }
}

inline void dfs_get(int u,int fa){
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        tree.modify_tree(1,w[i]);
        tree.modify_tree(j,-2 * w[i]);
        dp[j] = max(tree.query_sec(1,id[j] - 1),tree.query_sec(id[j] + 1,n));
        dfs_get(j,u);
        tree.modify_tree(1,-w[i]);
        tree.modify_tree(j,2 * w[i]);
    }
}

signed main(){
    memset(h,-1,sizeof(h));
    n = read();
    for (re int i = 1;i < n;i++){
        int a,b,c;
        a = read();
        b = read();
        c = read();
        add(a,b,c);
        add(b,a,c);
    }
    for (re int i = 1;i <= n;i++) p[i] = read();
    dfs1(1,0);
    dfs2(1,0,1);
    tree.build(1,1,n);
    dfs_val(1,0,0);
    dp[1] = max(tree.query_sec(1,id[1] - 1),tree.query_sec(id[1] + 1,n));
    dfs_get(1,0);
    for (re int i = 1;i <= n;i++) printf("%lld\n",dp[i]);
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

没脑子的题目。

一眼换根 DP。定义 $\mathit{f}_{i}$ 表示 $i$ 到 $i$ 为根子树中某一个节点的距离最大值；$\mathit{g}_{i}$ 表示 $i$ 经过其父节点到某个节点的距离最大值。那答案就是 $\max(\mathit{f}_i,\mathit{g}_i)$。

考虑转移。$\mathit{f}_i$ 的转移很简单，就是 $\mathit{f}_{i} =\max\{\max(val_j,f_j)+w_k|i \to j\}$。这里将 $val_j$ 和 $\mathit{f}_i$ 取最大值是因为会出现 $j$ 是叶子节点的情况。求 $\mathit{g}_i$ 的时候换根 DP 就行了。定义 $\mathit{fa}_i$ 表示 $i$ 的父亲节点。那么 $\mathit{g}_i=\max(\max(val_{fa_i},g_{fa_i})+w_k,\max\{\max(val_j,f_j)+w_{k'}+w_k|fa_i \to j\land fa_i \to i\})$。前半部分是由父亲直接转移的情况，后半部分是由与 $i$ 同备份的节点转移的情况。用两个变量存最大值和次小值可以 $O(n)$ 求出来，当然也是可以 $O(n \log n)$ 用大根堆乱搞。 

## 代码

[Link](https://atcoder.jp/contests/abc222/submissions/47196923).

---

