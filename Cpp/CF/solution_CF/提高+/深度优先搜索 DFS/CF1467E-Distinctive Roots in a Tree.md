# Distinctive Roots in a Tree

## 题目描述

You are given a tree with $ n $ vertices. Each vertex $ i $ has a value $ a_i $ associated with it.

Let us root the tree at some vertex $ v $ . The vertex $ v $ is called a distinctive root if the following holds: in all paths that start at $ v $ and end at some other node, all the values encountered are distinct. Two different paths may have values in common but a single path must have all distinct values.

Find the number of distinctive roots in the tree.

## 说明/提示

In the first example, $ 1 $ , $ 2 $ and $ 5 $ are distinctive roots.

## 样例 #1

### 输入

```
5
2 5 1 1 4
1 2
1 3
2 4
2 5```

### 输出

```
3```

## 样例 #2

### 输入

```
5
2 1 1 1 4
1 2
1 3
2 4
2 5```

### 输出

```
0```

# 题解

## 作者：OMG_wc (赞：12)

![](https://cdn.luogu.com.cn/upload/image_hosting/1yju9cc8.png)

有两个颜色相同的点 $A,B$ 如上图所示，它们造成的影响是各自朝外的两个子树内所有点不能作为答案了。而中间部分暂时安全，不会受这两个同色点影响。一个思路是：对所有的同色点对，标记它们朝外的两个子树，最后所有没标记过的点就能记入答案了。

要做的话肯定得转成有根树来做，规定 $1$ 为根，这时候每个同色点对有两种可能性：

- 非祖孙关系
- 祖孙关系

第一种情况就很简单了，在 DFS 到结点 $u$ 的时候，如果发现除了 $u$ 子树外还存在颜色 $a_u$ 的话，就把整个 $u$ 子树给标记。

标记子树，只需求出一进一出的时间戳，然后差分标记来实现区间加。

第二种情况，参考下图

![](https://cdn.luogu.com.cn/upload/image_hosting/8ymi0ija.png)

对晚辈 $B$ 来说，同样是标记子树，但对祖先 $A$ 来说，标记的是除了 $B$ 所在的 $S$ 子树外的任何结点。

综合一下，具体的做法就是：

- 在 DFS 到结点 $u$ 时，如果存在某个子树 $S$ 也包含颜色 $a_u$ ，那就标记除 $S$ 子树外的其他所有点（在时间戳上可以拆成两个区间）。

- 在 DFS 到结点 $u$ 时，统计完 $u$ 子树的 $a_u$ 的颜色后，发现少于总共的 $a_u$ 颜色，说明外部也存在 $a_u$，那就把整个 $u$ 子树标记。

然后怎么统计颜色个数？直接用`map` 记录全局每个颜色的个数，递归后和递归前的差值就是子树里这种颜色的个数。

参考代码如下，时间复杂度 $O(n\log n)$：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

vector<int> G[N];
int a[N], d[N];
int dfn[N], out[N], ck;
map<int, int> mp, c;
void dfs(int u, int fa) {
    dfn[u] = ++ck;
    int tt = c[a[u]];
    c[a[u]]++;
    for (auto v : G[u]) {
        if (v == fa) continue;
        int tmp = c[a[u]];
        dfs(v, u);
        if (c[a[u]] > tmp) {
            d[1]++, d[dfn[v]]--;
            d[out[v] + 1]++;
        }
    }
    out[u] = ck;
    if (c[a[u]] - tt < mp[a[u]]) {
        d[dfn[u]]++, d[out[u] + 1]--;
    }
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mp[a[i]]++;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
        if (d[i] == 0) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：睿智的憨憨 (赞：6)

## 题目大意

给定一颗节点数为 $n(1 \le n \le 2 \times 10^5$) 的树，每个点都有一个点权 $a_i(1 \le a_i \le 10^9)$，求有多少个节点 $u$ 满足任意以 $u$ 为端点的路径上的权值不重复。

## 解法分析

题目要求的是以 $u$ 为端点，但是我们不一定必须在 dfs 到 $u$ 时判断并只判断所有以 $u$ 为端点的路径。

当 dfs 到 $u$ 时，若除了 $u$ 的子树中的点（含 $u$）外，还有点的点权与 $a_u$ 相等,那么 $u$ 就不符合要求，而且因为以 $u$ 的子树中的任意一点为端点的路径中都包含了以 $u$ 为端点的路径，所以整颗 $u$ 的子树中的点也都不符合要求。如果 $u$ 的子树中存在两个 $a_u$，那么 $u$ 的子树以外的节点也都不符合要求。

如果老老实实一个一个点标记的话，时间复杂度会嗖的一下升天，所以我们利用 dfs 序将树转成序列并用差分数组标记，这样时间复杂度就省去了一个 $n$。

最终时间复杂度：$O(n \log n)$，带 $\log$ 是因为使用了 map 来计数。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, a[N];
vector<int> e[N];
map<int, int> cnt, mp;
int tot, dfn[N], sz[N], d[N];
void dfs(int u, int pr){
	int t = cnt[a[u]];
	cnt[a[u]]++, dfn[u] = ++tot, sz[u] = 1;
	for (int v : e[u]){
		if (v != pr){
			int tmp = cnt[a[u]];
			dfs(v, u);
			sz[u] += sz[v];
			if (tmp != cnt[a[u]])
				d[1]++, d[dfn[v]]--, d[dfn[v] + sz[v]]++;
		}
	}
	if (cnt[a[u]] - t != mp[a[u]])
		d[dfn[u]]++, d[dfn[u] + sz[u]]--;
}
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]), mp[a[i]]++;
	for (int i = 1, u, v; i < n; i++){
		scanf("%d %d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	int val = 0, ans = 0;
	for (int i = 1; i <= n; i++){
		val += d[i];
		if (val == 0)
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：wmy_goes_to_thu (赞：3)

先确立一个根。我们要判断以每一个点开始的所有路径是否存在重复值。那么可以 dfs：

1. 往下爬

这部分很好做，直接进行一次自下而上的 dfs 即可，$u$ 如果可行，就需要在 $u$ 的子树中的所有值都和 $u$ 的值不一样（可以用 dfs 序实现），而且满足 $fa[v]=u$ 的所有 $v$ 也需要可行。如果可以那么称之为 $1$ 类可行。

2. 往上跑后往下爬

这部分也不难，直接进行一次自上而下的 dfs 即可。$u$ 如果可行，就需要 $u$ 和 $fa[u]$ 在除去 $u$ 的子树的大树上的值是唯一的，$fa[u]$ 需要可行，而且 $fa[u]$ 的子树的子节点（除去 $u$）也需要 $1$ 类可行，如果满足这些条件（当然需要 $1$ 类可行），就可以了。

---

## 作者：新版米奇奇米 (赞：2)

突然发现深究一些树上问题还是挺有意思的哈。

显然对于同一种权值的任意两个结点，其两端的部分都是不合法的。

![](https://gitee.com/May2nd/pic-cloud/raw/master/14269432-1.png)

维护两个标记表示子树内均不合法和子树**外**均不合法即可。但相同权值对数是 $O(n^2)$ 的，我们要优化这个过程。

发现很多对都是无用的。DFS 下去，遇到一个 $x$ 权值的结点 $u$，其实只需要与上一个遇到的 $x$ 权值的结点 $v$ 做一下就好了，原因如下：

- $v$ 是 $u$ 的祖先。$u$ 与 $v$ 子树外的结点做没有影响。
- $v$ 不是 $u$ 的祖先。能不经过其它 $x$ 权值的除 $v$ 外的结点直接走到 $u$ 的 $x$ 权值的结点一定已经做过了且 $u$ 与它们做没有影响。

![](https://gitee.com/May2nd/pic-cloud/raw/master/14269432-2.png)

红色结点表示权值 $x$ 的结点，蓝色结点就是 $u$。

画图就会发现这个结论太容易得出啦。

最后再来一次 DFS 处理所有标记。记一下是否存在子树外均不合法标记和**当前**子树内合法结点数。当一个结点的两个儿子中都出现子树外均不合法时答案一定为 $0$。细节仔细思考一下。

时间复杂度 $O(n\log n)$。瓶颈在于离散化，放一下代码叭。

***code:***

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define For(i,x,y)for(i=x;i<=(y);i++)
struct node
{
	int next,to;
}e[400005];
map<int,int>col;
bool vis[N],fa[N],son[N];
int a[N],head[N],sta[N],last[N],pos[N],g,cnt,top;
int read()
{
	int A;
	bool K;
	char C;
	C=A=K=0;
	while(C<'0'||C>'9')K|=C=='-',C=getchar();
	while(C>'/'&&C<':')A=(A<<3)+(A<<1)+(C^48),C=getchar();
	return(K?-A:A);
}
inline void add(int u,int v)
{
	e[++g].to=v;
	e[g].next=head[u];
	head[u]=g;
}
void dfs(int u,int t)
{
	int i,v,tmp;
	vis[u]=1;
	sta[++top]=u;
	pos[u]=top;
	if(!col.count(a[u]))tmp=col[a[u]]=++cnt;
	else
	{
		tmp=col[a[u]];
		if(vis[last[tmp]])fa[sta[pos[last[tmp]]+1]]=1;
		else son[last[tmp]]=1;
		son[u]=1;
	}
	last[tmp]=u;
	for(i=head[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==t)continue;
		dfs(v,u);
		last[tmp]=u;
	}
	vis[u]=0;
	top--;
}
pair<int,int>calc(int u,int t)
{
	int i,v,tot,siz;
	pair<int,bool>pa;
	tot=siz=0;
	for(i=head[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==t)continue;
		pa=calc(v,u);
		/*cout<<v<<' '<<pa.first<<' '<<pa.second<<endl;*/
		siz+=pa.second;
		if(siz>1)cout<<0,exit(0);
		if(!siz)tot+=pa.first;
		else if(pa.second)tot=pa.first;
	}
	return make_pair((son[u]?0:tot+!siz),siz||fa[u]);
}
int main()
{
	int n,i,u,v;
	n=read();
	For(i,1,n)a[i]=read();
	For(i,1,n-1)
	{
		u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	/*For(i,1,n)cout<<son[i]<<' '<<fa[i]<<endl;*/
	cout<<calc(1,0).first;
	return 0;
}
```

---

## 作者：RyexAwl (赞：2)

我们先随便钦定点$root$为根，我们发现对于任一点$u$，其能够保证要求当且仅当点$u$到子树内的所有路径不经过重复点且$u$到子树外的路径不经过重复点。

只要我们分别维护这两个要求最后与一下即可。

首先我们考虑维护子树内的情况：我们发现如果要满足要求必须要满足其所有子节点到其子树内的所有点的路径上不经过重复点，且以$u$为根的子树内点权$w[u]$仅出现一次。 至于出现次数的维护方法，可以类似[P1600 [NOIP2016 提高组] 天天爱跑步](https://www.luogu.com.cn/problem/P1600) 用桶维护全局的情况在遍历完当前子树时将子树内的情况差分出来。

接下来考虑子树外的情况：我们发现，如果要满足要求，那么其父节点$fa$必须要满足要求，即$fa$到$fa$子树外的所有点的路径必须不经过重复点，且父节点到其兄弟节点不能经过重复点（用类似上面维护子树内的方法可以简单check），而且在$u$的子树外不能出现点权$w[u]$，这个我们也是可以用桶差分出来的。

最后两个要求与一下即可

```cpp
#include <iostream>
#include <algorithm>

namespace wxy{
	const int N = 2e5 + 5;
	int head[N],fail[N << 1],edge[N << 1],tot,n;
	int a[N],b[N],w[N],cnt[N],d[N],f[N],s[N],son[N],size[N],sf[N],m;
	inline void add(int x,int y){
		edge[++tot] = y;
		fail[tot] = head[x];
		head[x] = tot;
	}
	inline int get(int x){return std::lower_bound(b + 1,b + 1 + m,x) - b;}
	inline void dfs1(int x,int fa){
		int pre = cnt[w[x]];d[x] = 1;int pre2;
		if (x != 1) pre2 = cnt[w[fa]];
		for (int i = head[x];i;i = fail[i]){
			int v = edge[i];
			if (v == fa) continue;
			size[x]++;
			dfs1(v,x);
			d[x] &= d[v];
			if (d[v] == 1) son[x]++;
		}
		int sum = cnt[w[x]]; 
		if (sum - pre > 0) d[x] = 0;
		cnt[w[x]]++;
		s[x] = sum - pre + 1;
		if (x != 1){
			int sum2 = cnt[w[fa]];
			sf[x] = sum2 - pre2;
			if (w[x] == w[fa]) sf[x]++;
		}
	}
	inline void dfs2(int x,int fa){
		if (x != 1){
			if (f[fa] == 1 && son[fa] - d[x] == size[fa] - 1 && s[fa] - sf[x] == 1){
				f[x] = 1;
			}
			if (cnt[w[x]] - s[x] != 0) f[x] = 0;
		}
		for (int i = head[x];i; i = fail[i]){
			int v = edge[i];
			if (v == fa) continue;
			dfs2(v,x);
		}
	}
	void main(){
		m = tot = 0;
		std::cin >> n;
		for (int i = 1; i <= n; i++) std::cin >> a[i];
		for (int i = 1; i < n; i++){
			int x,y;std::cin >> x >> y;
			add(x,y);add(y,x);
		}
		for (int i = 1; i <= n; i++)w[i] = a[i];
		std::sort(a + 1,a + n + 1);
		for (int i = 1; i <= n; i++)
			if (i == 1 || a[i] != a[i - 1]) b[++m] = a[i];
		
		for (int i = 1; i <= n; i++) w[i] = get(w[i]);
		dfs1(1,0);f[1] = 1;dfs2(1,0);
		int ans = 0;
		for (int i = 1; i <= n; i++) f[i] &= d[i];
		for (int i = 1; i <= n; i++)
			if (f[i] == 1) ans++;
		std::cout << ans;
	}
}signed main(){wxy::main();return 0;}
```


---

## 作者：chenxia25 (赞：1)

注意到对于任意一个点，它满足条件当且仅当，若以它为根的话，那么没有颜色相同的祖先后代对。

那么很自然的想到换根，实时维护当前颜色相同的祖先后代对个数（注意要开 `ll`）。

首先求出初始值。我们考虑换一次根这个值会有什么变化。

考虑所有点对。如果点对在老根和新根的子树中的同一个的话，那关系显然不变。然后如果是不同的，并且两个都不是老根或新根，那显然也不变。于是只需要考虑新根子树对老根的贡献和老根子树对新根的贡献即可。这个只需要一开始离散化一下，装个桶，然后在 dfs 序上二分即可。

复杂度线对。有时候研究线性做法也是没啥意义的。

---

## 作者：Imitators (赞：1)

给出一个数据结构暴力方法。

对于 $v$ ,当他为根的时候，假如存在子树，以 $u$ 为根的子树中，有 $a_x=a_v$ 那么，答案只可能出现在 $a_u$ 的子树。

因为不在 $u$ 的子树中，存在路径，同时经过 $u$ , $x$。这个不合法。

每个点都进行这个操作，那么我们可以确定可以选的区间，剩下的就好做了。

1. 第一步想怎么确定以 $v$ 为根，哪个子树里面有没有 $a_v$。

   可以用权值线段树来维护这个序列。(线段树维护的是权值 $c$ 出现的次数)
   
   首先，我们用 可持久化“线段树合并”来维护，每个节点的子树里面什么颜色出现的次数。这个很简单。
   
   其次，与 $v$ 相连的无非就是 $v$ 在有根树中的儿子，或父亲。
   
   1. 儿子可以直接在儿子那棵线段树中查询。
   
   2. 父亲就相当于全体- $v$ 的线段树中出现的次数。
   
2. 如果在 第 $1$ 步，有 $2$ 个以上的有 $a_x=a_v$,那么此时，总体答案就是 $0$。
   否则在用一个线段树维护是否可行。
   1. 如果是 $v$ 在有根树中的儿子中存在 $a_x=a_v$，那么我们直接就把 以 $u$ 为根的子树 中的所有点 $+1$。
   2. 如果是 $v$ 在有根树中的父亲中存在 $a_x=a_v$，那么我们把整个线段树 $+1$,特别的把 以 $x$ 为根的子树 $-1$。
   3. 如果没有，就全体 $+1$。
3. 可行的是每一次都被包含的点，最后一遍 $dfs$ 统计所有 权值等于 $n$的点，即每一次都被包含的点。

$\mathcal{Tips}$
因为我的方法大多只用到数据结构模板，在确定模板没打错的时候，细节较少。
如果对数据结构特别熟悉的话，这个题看起来也就十分简单了。

对于 $1$ 的讨论，给出一个图把。
![](https://cdn.luogu.com.cn/upload/image_hosting/lzohm0v9.png)


``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5,M=9e6;
int ls[M],rs[M],f[M];
struct node{int x,id;}a[N];
vector<int> v[N];
int cnt,rt[N],n;
int fa[N],sz[N];
inline void insert(int &pos,int x,int l,int r)
{
    if(pos==0) pos=++cnt;
    if(l==r)
    {
        f[pos]++;
        return ;
    }
    int mid=l+r>>1;
    if(x<=mid) insert(ls[pos],x,l,mid);
    else insert(rs[pos],x,mid+1,r);
    f[pos]=f[ls[pos]]+f[rs[pos]];
}
inline int merge(int x,int y,int l,int r)
{
    if(x==0) return y;
    if(y==0) return x;
    int t=++cnt,mid=l+r>>1;
    f[t]=f[x]+f[y];
    ls[t]=merge(ls[x],ls[y],l,mid);
    rs[t]=merge(rs[x],rs[y],mid+1,r);
    return t;
}
inline int ask(int pos,int x,int l,int r)
{
    if(l==r)
        return f[pos];
    int mid=l+r>>1;
    if(x<=mid)
    {
        if(ls[pos]) return ask(ls[pos],x,l,mid);
        return 0;
    }
    if(rs[pos]) return ask(rs[pos],x,mid+1,r);
    return 0;
}
int id[N],num[N],kth;
inline void dfs(int x,int f)
{
    fa[x]=f,sz[x]=1;
    id[x]=++kth,num[kth]=x;
    insert(rt[x],a[x].x,1,n);
    for(int i=0;i<v[x].size();i++)
    {
        int y=v[x][i];
        if(y==f) continue;
        dfs(y,x);
        rt[x]=merge(rt[x],rt[y],1,n);
        sz[x]+=sz[y];
    }
}
inline bool cmp(node a,node b){return a.x<b.x;}
inline bool cmp1(node a,node b){return a.id<b.id;}
int b[N];
struct seg{int l,r,v,tag;}t[N<<2];
inline void build(int pos,int l,int r)
{
    t[pos].l=l,t[pos].r=r;
    if(l==r) return ;
    int mid=l+r>>1;
    build(pos<<1,l,mid),build(pos<<1|1,mid+1,r);
}
inline void pushdown(int pos)
{
    if(t[pos].tag)
    {
        int tag=t[pos].tag;
        t[pos].tag=0;
        t[pos<<1].tag+=tag,t[pos<<1|1].tag+=tag;
        t[pos<<1].v  +=tag*(t[pos<<1].r  -t[pos<<1].l+1);
        t[pos<<1|1].v+=tag*(t[pos<<1|1].r-t[pos<<1|1].l+1);
    }
}
inline void modify(int pos,int x,int y,int v)
{
    if(x<=t[pos].l&&t[pos].r<=y)
    {
        t[pos].tag+=v;
        t[pos].v+=v*(t[pos].r-t[pos].l+1);
        return ;
    }
    pushdown(pos);
    int mid=t[pos].l+t[pos].r>>1;
    if(y<=mid) modify(pos<<1,x,y,v);
    else if(x>mid) modify(pos<<1|1,x,y,v);
    else modify(pos<<1,x,y,v),modify(pos<<1|1,x,y,v);
    t[pos].v=t[pos<<1].v+t[pos<<1|1].v;
}
int ans=0;
inline void find(int pos)
{
    if(t[pos].l==t[pos].r)
    {
        if(t[pos].v==n) ans++;
        return ;
    }
    pushdown(pos);
    find(pos<<1);
    find(pos<<1|1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].x,a[i].id=i;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        if(a[i].x==a[i-1].x) b[i]=b[i-1];
        else b[i]=b[i-1]+1;
    }
    for(int i=1;i<=n;i++) a[i].x=b[i];
    sort(a+1,a+1+n,cmp1);
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        v[x].push_back(y),v[y].push_back(x);
    }
    dfs(1,0);
    build(1,1,n);
    for(int x=1;x<=n;x++)
    {
        int num=0,pos=0;
        for(int i=0;i<v[x].size();i++)
        {
            int y=v[x][i];
            if(y==fa[x])
            {
                if(ask(rt[1],a[x].x,1,n)-ask(rt[x],a[x].x,1,n))
                    num++,pos=y;
            }
            else
            {
                if(ask(rt[y],a[x].x,1,n))
                    num++,pos=y;
            }
        }
        if(num>=2) cout<<"0",exit(0);
        if(pos==0)
        {
            modify(1,1,n,1);
            continue;
        }
        if(pos==fa[x])
        {
            modify(1,1,n,1);
            modify(1,id[x],id[x]+sz[x]-1,-1);
        }
        else
            modify(1,id[pos],id[pos]+sz[pos]-1,1);
    }
    find(1);
    cout<<ans<<endl;
}
```

---

## 作者：zjjws (赞：1)

考虑把所有权值相同的点划分成一组，作为当前的 **关键点**，我们要使得选定的根 **不能让任意两个关键点有祖先后代关系**。

考虑对于关键点按照 dfn 序（任意指定一个根，以下称作 **假根** ）进行排序，我们会得到一些情况的图：


#### Case 1

![](https://cdn.luogu.com.cn/upload/image_hosting/2i7ygo5k.png)


红点表示关键点，其中最上面有一个红点是所有点的祖先；黄点表示剩余红点的 Lca，绿点表示黄点往假根方向走，**能到达的最远的一个点，满足 dfn 序比最上面那个红点大**（找到最上面红点的某个儿子，是剩余点的公共祖先）

那么如果黄点就是最上面那个红点呢？此时是一个无解的情况，因为出现了 **三个关键点在同一条链上** 的情况。

除了上述的特殊情况，**绿点的后代且非下面红点的后代（包括下面红点自身）**，在只考虑当前组的时候可以作为合法的根。会发现，这些点作为根的时候，所有关键点并不存在子孙后代关系。

---

#### Case 2

![](https://cdn.luogu.com.cn/upload/image_hosting/noniiawj.png)

没错，只是把上面那个红点掐掉了。

此时只要把所有关键点的后代（包括自身）叉掉就好了，其他点都可以作为根。

---

#### 实现

具体的，由于上述操作可以转化成将 **若干个子树的交或并** 打上 **不能作为根的标记**。

我们可以利用 dfn 序，在差分数组上进行操作，最后扫一遍，统计那些点没有被打上标记即可。

---

#### 代码

```cpp
#include <stdio.h>
#include <vector>
#include <algorithm>
#define LL long long
using namespace std;
const int N=2e5+3;
inline LL rin()
{
    LL s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)s=-s;
    return s;
}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void jh(int &x,int &y){if(x!=y)x^=y^=x^=y;return;}


int n;
struct gyq
{
    int val,num,dfn;
}a[N];
inline bool myru_gyq(gyq x,gyq y){return (x.val==y.val)?(x.dfn<y.dfn):(x.val<y.val);}
int nam;
vector<int>b[N];

int fa[20][N];
int dep[N];
int lar[N];
int dfn[N];
inline void dfs(int x,int Fa)
{
    a[x].dfn=++nam;
    dfn[x]=nam;
    dep[x]=dep[Fa]+1;
    lar[x]=1;
    fa[0][x]=Fa;
    for(int i=b[x].size()-1;i>=0;i--)
    {
        int to=b[x][i];
        if(to==Fa)continue;
        dfs(to,x);
        lar[x]+=lar[to];
    }
    return;
}

inline int Lca(int x,int y)
{
    if(dep[x]<dep[y])jh(x,y);
    for(int i=dep[x]-dep[y],j=0;i;i>>=1,j++)if(i&1)x=fa[j][x];
    for(int j=0;j>=0;)
    {
        if(fa[j][x]!=fa[j][y])x=fa[j][x],y=fa[j][y],j++;
        else j--;
    }
    if(x!=y)x=fa[0][x];
    return x;
}

int sl[N];
inline void add(int l,int r,int s){sl[l]+=s;sl[r+1]-=s;return;}
inline int work()
{
    n=rin();
    for(int i=1;i<=n;i++)a[i].val=rin(),a[i].num=i;
    for(int i=1;i<n;i++){int x=rin(),y=rin();b[x].push_back(y);b[y].push_back(x);}
    dfs(1,0);
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++)fa[i][j]=fa[i-1][fa[i-1][j]];
    sort(a+1,a+n+1,myru_gyq);
    for(int i=1,j;i<=n;i=j)
    {
        for(j=i+1;j<=n&&a[j].val==a[i].val;j++)if(j!=i+1&&a[j].dfn<a[j-1].dfn+lar[a[j-1].num])return 0;
        if(j==i+1)continue;
        for(int _=i;_<j;_++)add(a[_].dfn,a[_].dfn,1);
        for(;true;)
        {
            int _;
            for(_=i+1;_<j;_++)
            {
                if(a[_].dfn>=a[i].dfn+(lar[a[i].num]))
                {
                    if(_==i+1)break;
                    return 0;
                }
            }
            if(_==j)
            {
                int z=a[i+1].num;
                for(_=i+2;_<j;_++)z=Lca(z,a[_].num);
                if(z==a[i].num)return 0;
                
                add(1,n,1);
                int lxt=z;
                for(int p=19;p>=0;p--)if(dfn[fa[p][lxt]]>a[i].dfn)lxt=fa[p][lxt];
                add(dfn[lxt],dfn[lxt]+lar[lxt]-1,-1);
                i++;
            }
            break;
        }
        for(int _=i;_<j;_++)add(a[_].dfn,a[_].dfn+lar[a[_].num]-1,1);
    }
    int sum=0;
    LL cutt=0;
    for(int i=1;i<=n;i++)cutt+=sl[i],sum+=(cutt==0);
    return sum;
}
int main()
{
    int i,j;
    printf("%d\n",work());
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1467E)

## 思路

这种难度的题有 $2500$？

考虑我们先统计根节点能否被记入答案，这是简单的，我们记录每个节点的子树内是否有与它相同颜色的节点即可。

然后考虑换根，把根从 $u$ 换到它的一个子节点 $v$，受到影响的只有 $u$ 和 $v$，而且影响也很好算：

+ $u$ 的子树从全体节点变成了全体节点除去当前 $v$ 的子树。
+ $v$ 的子树变成了全体节点。

然后就做完了，复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
int const N=2e5+10;
int a[N],t[N],siz[N],ct[N],f[N],s[N],dfn[N],cnt;
vector<int>b[N],c[N];
inline void dfs(int x,int fa){
    dfn[x]=++cnt,siz[x]=1;
    for (auto v:b[x])
        if (v^fa) dfs(v,x),siz[x]+=siz[v];
}
int sum,ans;
inline void bfs(int x,int fa){
    ans+=!sum;
    for (auto v:b[x]){
        if (v==fa) continue;
        int la=s[v],pre=sum,La=s[x];
        sum-=s[x];
        s[x]=!!(ct[a[x]]-1-(upper_bound(all(c[a[x]]),dfn[v]+siz[v]-1)-ower_bound(all(c[a[x]]),dfn[v])));
        sum+=s[x];
        sum-=s[v],
        s[v]=!!(ct[a[v]]-1),
        sum+=s[v];
        bfs(v,x);
        sum=pre,s[v]=la;
        s[x]=La;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for (int i=1;i<=n;++i)
        cin>>a[i],t[i]=a[i];
    sort(t+1,t+n+1);
    int l=unique(t+1,t+n+1)-t-1;
    for (int i=1;i<=n;++i)
        a[i]=lower_bound(t+1,t+l+1,a[i])-t,
        ++ct[a[i]];
    for (int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        b[u].push_back(v),
        b[v].push_back(u);
    }
    dfs(1,0);
    for (int i=1;i<=n;++i) c[a[i]].push_back(dfn[i]);
    for (int i=1;i<=n;++i) sort(all(c[i]));
    for (int i=1;i<=n;++i){
        int L=upper_bound(all(c[a[i]]),dfn[i])-c[a[i]].begin();
        int R=upper_bound(all(c[a[i]]),dfn[i]+siz[i]-1)-c[a[i]].begin();
        if (L<R) s[i]=1;
    }
    for (int i=1;i<=n;++i) sum+=s[i];
    bfs(1,0);
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一棵 $n$ 个点的树，每个点有颜色。求满足**从它出发的每条路径都没有重复颜色**的点的数量。
### 分析
不让颜色重复，就先选两个同色的，看看它们可以把哪些点扬了。

发现是两个点割掉对方方向子树后的子树。

于是你想办法给这些子树打上标记，最后统计没标记的数量就行了。

找出所有同色点对显然很唐，我们只看一个点。先随便定个根，我们只需要 check 是否需要对其自己子树或某个子树以外的部分打标记即可。打标记的实现为了方便，可以 dfn 序上差分做前缀和，不多赘述。

显然的，如果一个点自己子树外有与其同色的，那么它的子树需打标记；如果一个点某个子树有与其同色的，那么这棵子树以外的所有部分需打标记。注意子树外有同色的等价于子树内该颜色数小于整棵树内该颜色数，所以本质是要维护个子树数 x 的东西，先离散化，然后方法一车，比如给每个颜色开个 dfn 序的 `vector` 然后在上面二分，或者像我这里直接弄个 dsu on tree，就都是小常数单 log 喵。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=4e5+5;
int n;
int a[maxn];
int t[maxn],tt;
vector<int> T[maxn];
int siz[maxn],hson[maxn];
int dfn[maxn],nfd[maxn],id[maxn],dfc;
void dfs(int u,int f){
	dfn[u]=++dfc,id[dfc]=u;
	siz[u]=1;
	for(int v:T[u]){
		if(v==f) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]]) hson[u]=v;
	}
	nfd[u]=dfc;
}
int tot[maxn],cur[maxn];
int ans[maxn],cnt;
void add(int l,int r,int k){ans[l]+=k,ans[r+1]-=k;}
void solve(int u,int f,int k){
	for(int v:T[u]){
		if(v==f||v==hson[u]) continue;
		solve(v,u,1);
	}
	if(hson[u]){
		solve(hson[u],u,0);
		if(cur[a[u]]) add(1,n,1),add(dfn[hson[u]],nfd[hson[u]],-1);
	}
	for(int v:T[u]){
		if(v==f||v==hson[u]) continue;
		int ori=cur[a[u]];
		for(int i=dfn[v];i<=nfd[v];i++) cur[a[id[i]]]++;
		if(cur[a[u]]>ori) add(1,n,1),add(dfn[v],nfd[v],-1);
	}
	cur[a[u]]++;
	if(cur[a[u]]<tot[a[u]]) add(dfn[u],nfd[u],1);
	if(k) for(int i=dfn[u];i<=nfd[u];i++) cur[a[id[i]]]--;
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++) t[i]=a[i]=read();
	sort(t+1,t+n+1);tt=unique(t+1,t+n+1)-t-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(t+1,t+tt+1,a[i])-t;
		tot[a[i]]++;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		T[u].eb(v),T[v].eb(u);
	}
	dfs(1,0);
	solve(1,0,0);
	for(int i=1;i<=n;i++){
		ans[i]+=ans[i-1];
		if(!ans[i]) cnt++;
	}
	cout<<cnt<<"\n";
	return 0;
}
```

---

## 作者：allqpsi (赞：0)

### 题意很清楚，我们直接讲思路：

首先可以想到考虑每个相同权值的点对答案的反贡献，这时我们画个图（图又丑又抽象，请勿喷）：

![](https://cdn.luogu.com.cn/upload/image_hosting/9vzu6kif.png)

假设点 $A$,$B$ 权值相同，容易发现两点之间的点是可选的，而两点子树不可选。但因发现两点之间的点不好维护，而子树做个 DFS 序就可维护，于是我们直接考虑哪些点无法成为一个可行根。

对于维护无法取的区间我们是全部更新后统计答案，又有区间修改，直接上差分。

那这时思路就清晰了：我们随便取一个点作为根，找到所有权值相同的点对，再差分统计答案。

那点对如何找并有什么贡献呢？容易发现只会有两种点对：

- 第一个点是第二个点的祖先，此时除第一个点的儿子，第二个点的祖先那个点的子树外的点都不可取。
- 第一个点不是第二个点的祖先，此时第二个点的子树不可取。

**注意：第一种情况两个点反过来便是第二种情况，也要算在内。**

对于判定，我们多开一个桶，第一种情况统计一下子树便可。第二种将此权值总共有几个减去此节点子树内有几个此权值，若大于零便存在。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define set(ai) memset(ai,0,sizeof(ai));
#define fset(ai) memset(ai,127,sizeof(ai));
#define hset(ai) memset(ai,63,sizeof(ai));
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define frep(i,s,t) for(int i=s;i>=t;i--)
#define rep1(i,s,t) for(int i=s;i<t;i++)
#define frep1(i,s,t) for(int i=s;i>t;i--)
#define srt(ai,n) sort(ai+1,ai+n+1)
#define csrt(ai,n,cmp) sort(ai+1,ai+n+1,cmp)
#define pb push_back
#define ppb pop_back
using namespace std;
const int N=2e5+5;
int n,ai[N],cnt=0,in[N],a,b,out[N],f[N],ans=0;
map<int,int>mi,ff;
vector<int>vi[N];
void dfs(int x){
	int a=ff[ai[x]];
	in[x]=++cnt,ff[ai[x]]++;
	rep1(i,0,vi[x].size()){
		int v=vi[x][i],b=ff[ai[x]];
		if(in[v])continue;
		dfs(v);
		if(b!=ff[ai[x]])f[1]++,f[in[v]]--,f[out[v]+1]++;
	}
	out[x]=cnt;
	if(ff[ai[x]]-a!=mi[ai[x]])f[in[x]]++,f[out[x]+1]--;
}
signed main(){
	set(in);set(out);set(f);
	cin>>n;
	rep(i,1,n)cin>>ai[i],mi[ai[i]]++;
	rep1(i,1,n)cin>>a>>b,vi[a].pb(b),vi[b].pb(a);                                                              
	dfs(1);
	rep(i,1,n)f[i]+=f[i-1],ans+=(f[i]==0);
	cout<<ans;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

树上差分结合 dfs 序。分为两种情况：

1. 当前结点 $cur$ 的权值为 $x$，发现邻接点 $nxt$ 的子树内有结点的权值也为 $x$。

整棵树都被标记，只有 $nxt$ 的子树不标记，之后再做讨论。

2. 当前结点 $cur$ 的权值为 $x$，在遍历完所有子树后，发现整棵树结点权值为 $x$ 的点的个数大于这颗子树中结点权值为 $x$ 的点的个数。即这颗子树不包含所有权值为 $x$ 的点。

如果是这样，那子树内的所有点均可以先到 $cur$，再前往子树外权值为 $x$ 的点，标记 $cur$ 的整颗子树。

标记根节点为 $cur$ 的子树可以使用树上差分：

$$
\text{diff}_{dfn_{cur}}\gets\text{diff}_{dfn_{cur}}+1,\\\text{diff}_{dfn_{cur}+sz_{cur}}\gets\text{diff}_{dfn_{cur}+sz_{cur}}-1
$$

或者

$$
\text{diff}_{dfn_{cur}}\gets\text{diff}_{dfn_{cur}}+1,\\\text{diff}_{out_{cur}}\gets\text{diff}_{out_{cur}}-1
$$

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, a[N], dfn[N], out[N], dfncnt, diff[N], ans;

vector<int> nbr[N];

unordered_map<int, int> mp, cnt;

void dfs(int cur, int fa) {
    dfn[cur] = ++dfncnt;
    int tmp = cnt[a[cur]];
    cnt[a[cur]]++;
    for (auto nxt : nbr[cur]) {
        if (nxt == fa)
            continue;
        int val = cnt[a[cur]];
        dfs(nxt, cur);
        if (cnt[a[cur]] > val) {
            diff[1]++;
            diff[dfn[nxt]]--, diff[out[nxt] + 1]++;
        }
    }
    out[cur] = dfncnt;
    if (cnt[a[cur]] - tmp < mp[a[cur]]) 
        diff[dfn[cur]]++, diff[out[cur] + 1]--;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)   
        cin >> a[i], mp[a[i]]++;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        nbr[u].emplace_back(v);
        nbr[v].emplace_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) 
        diff[i] += diff[i - 1], ans += !diff[i];
    cout << ans;
    return 0;
}
```

---

## 作者：COsm0s (赞：0)

## 思路

每个点的权值最大在 $10^9$ 大小，这使得数组存不下。我们又注意到此题对权值具体大小并不敏感，仅仅对相对大小有要求。那么就可以用离散化降低权值大小。

显然，用普通搜索很容易过。但是复杂度是 $O(n^2)$ 的，因此我们需要剪枝。

假设 $1$ 为树根。

在搜索时，我们建立两个数组，使得他们分别维护当前节点的子树中可选点与子树外可选点。

在搜索过程中，如果遇到相同权值的点（设为 $u$ 和 $v$），则分两种情况：

+ $u,v$ 是子孙关系。则此子树外任意一点不受影响。

+ $u,v$ 非子孙关系。则子树内任意一点走到这两点必是两条路径。但子树外必是一条路径。故子树内任意一点不受影响。

然后 DFS 处理所有标记。判断是否存在子树外均不合法标记和当前子树内合法结点数。当同一子树中两点中都出现子树外均不合法时答案一定为 $0$。

复杂度：DFS $O(n)$，离散化 $O(n \log n)$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
const int N = 5e5 + 10;
int n;
int a[N], b[N], s[N], lst[N], pos[N];
int fath[N], son[N];
vector<int> vec[N];
bool vis[N];
int top;
inline void dfs(int u, int fa) {
	vis[u] = 1;
	s[++ top] = u;
	pos[u] = top;
	if(lst[a[u]]) {
		if(vis[lst[a[u]]]) fath[s[pos[lst[a[u]]] + 1]] = 1;
		else son[lst[a[u]]] = 1;
		son[u] = 1; 
	}
	lst[a[u]] = u;
	for(auto v :vec[u]) {
		if(v == fa) continue;
		dfs(v, u);
		lst[a[u]] = u;
	}
	vis[u] = 0;
	-- top;
}
inline pii work(int u, int fa) {
	pii now;
	int sum = 0, ans = 0;
	for(auto v : vec[u]) {
		if(v == fa) continue;
		now = work(v, u);
		sum += now.second;
		if(sum > 1) cout << 0, exit(0);
		if(!sum) ans += now.first;
		if(sum == 1 && now.second) ans = now.first; 
	}
	return make_pair((son[u] ? 0 : ans + sum ^ 1), sum != 0 || fath[u]);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1); 
	int len = unique(b + 1, b + n + 1) - b - 1;
	for(int i = 1; i <= n; i ++) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
	for(int i = 1; i < n; i ++) {
		int l, r;
		cin >> l >> r;
		vec[l].push_back(r);
		vec[r].push_back(l);
	}
	dfs(1, 0);
	cout << work(1, 0).first;
	return 0;
}
```

Upd：代码方面借鉴了一下 @新版米奇奇米 的代码。

---

## 作者：yi_fan0305 (赞：0)

题目传送门：[CF1467E](https://www.luogu.com.cn/problem/CF1467E)

看到题目，原本考虑的是先把颜色相同的点打上标记，深搜时在比较父节点与子节点的颜色，最后从上往下更新，如果父节点被打了标记，那么子节点也随着父节点打上标记。

看着很合理，但实际是测试点三就被卡了，找了几篇题解看了看，才发现问题，两个颜色相同的点之间的点有可能是符合要求的点，但如果颜色相同的点做了树根，那么，这些点就全枪毙了。

所以要换思路，我们可以发现，两个颜色相同的点，它们往外的点就都不符合要求。

如图![](https://cdn.luogu.com.cn/upload/image_hosting/93p7a821.png)

我们设 $1$ 为树根。

在搜索到一个结点时，如果存在某个子树中包含颜色与该节点颜色相同的节点，那就标记除该子树外的其他所有点。

在搜索到一个结点时，统计完它的子树中与它颜色相等的颜色后，发现少于总共的颜色个数，说明外部也存在该颜色，那就把整个子树标记。

利用树上差分和dfs序来打标记。

由于 $a_i$ 数据范围过大，所以数据还要离散化。

上代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int n, cnt, tim;
bool g;
int h[N], vis[N], st[N], en[N], k[N], calubound[N];
// st dfs序起始位置 en dfs序结束位置 calubound 差分数组
ll a[N], col[N];
// a 原颜色 col 离散后的颜色
struct edge 
{
	int v, nxt;
} e[N << 1];

inline ll read()
{
	ll x = 0;
	bool fg = false;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		fg |= (ch == '-');
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return fg ? ~x + 1 : x;
}
void add(int u, int v)
{
	e[++cnt].v = v;
	e[cnt].nxt = h[u];
	h[u] = cnt;
}
void dfs(int u, int fat)
{
	st[u] = ++tim;
	int g = k[col[u]];
	++k[col[u]];
	for(int i = h[u]; i; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fat)	continue;
		int tmp = k[col[u]];
		dfs(v, u);
		if(k[col[u]] > tmp)
		{
			calubound[1]++;
			calubound[st[v]]--;
			calubound[en[v] + 1]++;
		}
	}
	en[u] = tim;
	if(k[col[u]] - g < vis[col[u]])
	{
		calubound[st[u]]++;
		calubound[en[u] + 1]--;
	}
}

int main()
{
	n = read();
	for(int i = 1; i <= n; ++i)
	{
		a[i] = read();
		col[i] = a[i];
	}
	for(int i = 1; i <= n-1; ++i)
	{
		int x = read(), y = read();
		add(x, y);
		add(y, x);
	}
	sort(a + 1, a + n + 1);
	int last = unique(a + 1,a + n + 1) - a - 1;
	for(int i = 1; i <= n; ++i)
	{
		col[i] = lower_bound(a + 1, a + last + 1, col[i]) - a;
		vis[col[i]]++;
	}
	dfs(1, 0);
	ll ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		calubound[i] += calubound[i-1];
		if(calubound[i] == 0)	++ans;
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：MCAdam (赞：0)

赛时想到一种虚树+树状数组的做法，但是细节很多没有rush出来

就是对每种颜色建出虚树，然后把每个子树内的点标记（大概是这样把？）

考虑换了种写法，也差不多是这样，但实现起来简单很多

首先钦定一个根，同样是考虑相同颜色的一条路径去标记不合法的点

- 两个点没有祖孙关系：

标记两个点的子树

- 两个点有祖孙关系：

晚辈的子树同样要标记，以及抠掉晚辈对应到祖先那个子树剩下部分

利用天天爱跑步子树差分的思路，并且不需要树状数组，因为最后才统计答案

时间复杂度$O(n\log n+n)$，主要瓶颈在离散化上

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=2e5+10;
int n,tot,ts;
int fir[N],v[N],tmp[N],size[N],cnt[N],val[N],all[N],dfn[N][2];
struct edge
{
	int to;
	int nxt;
}e[N<<1];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
inline void update(int l,int r,int opt)
{
	if(opt) val[1]++,val[l]--,val[r+1]++,val[n+1]--;
	else val[l]++,val[r+1]--;
}
inline void dfs(int p,int fa)
{
	dfn[p][0]=++ts;
	int cur0=-size[v[p]];
	cnt[v[p]]++,size[v[p]]++;
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to,cur;
		if(q==fa) continue;
		cur=size[v[p]],dfs(q,p);
		if(cur^size[v[p]]) update(dfn[q][0],dfn[q][1],1);
	}
	dfn[p][1]=ts;
	cur0+=size[v[p]];
	if(cnt[v[p]]>1||cur0<all[v[p]]) update(dfn[p][0],dfn[p][1],0);
	cnt[v[p]]--;
}
int main()
{
	int a,b,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&v[i]),tmp[i]=v[i];
	sort(tmp+1,tmp+n+1);
	int m=unique(tmp+1,tmp+n+1)-(tmp+1);
	for(int i=1;i<=n;i++)
		v[i]=lower_bound(tmp+1,tmp+m+1,v[i])-tmp,all[v[i]]++;
	for(int i=1;i<n;i++)
		scanf("%d%d",&a,&b),add(a,b);
	dfs(1,0);
	for(int i=1;i<=n;i++)
		val[i]+=val[i-1],ans+=(!val[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Piwry (赞：0)

讨论了下发现貌似还有个 $\Theta(n\sqrt n)$ 或 $\Theta(n\log n)$ 的枚举每个根是否能作为答案的做法

大致即随意固定一个根 dp 子树内是否存在为前后代关系的同色节点对，可以发现当前根合法当且仅当不存在这样的节点对；然后再换根

主要问题在于第二次 dfs（换根）时询问子树内是否存在某种颜色的结点时要如何处理。简单地可以想到把询问都离线下来，然后可以直接莫队做（主席树则貌似搞不了...）；更进一步的可以发现询问都是依赖于边（有向）的，即最多有 $2(n-1)$ 种询问（包括第一次 dfs 时）且很容易在第一次 dfs 时用常规方法都求出来（向儿子的边的询问可以直接线段树合并或 dsu on tree 做；向父亲的边的询问可以用总同颜色数减去子树内同颜色数），这样就能做到 $\Theta(n\log n)$

讲得比较简略，不过没要求的话这里就不详细展开了 \kk

## 解析

枚举路径不太好搞

一条路径不合法的本质是含有相同颜色的一对结点

考虑一对同色结点 $u, v$ 会使哪些结点不能作为答案

设 $x$ 为路径 $p(u, v)$（有向）的 $u$ 的下一个结点；同样设 $y$ 为路径 $p(v, u)$的 $v$ 的下一个结点。同色结点对 $u, v$ 会导致，根在 $u$ 的 $(u, x)$ 方向的意义下的 $u$ 子树，和根在 $v$ 的 $(v, y)$ 方向的意义下的 $v$ 子树，这些结点无法作为答案

如果将上述的 “$u$ 子树”、“$v$ 子树” 视为 $u$、$v$ 对答案的贡献，那么要想知道一个结点的贡献，实际上就只需确定其所有连出去的边的 “方向” 是否存在同色结点（即来自同一条边的方向的同色结点产生的贡献是一样的）。接下来称对于 $u$，存在同色结点的边 $(u, x)$（有向）是 “产生贡献的”

如果知道了每条边是否产生贡献，那么剩下的问题就是最多 $2(n-1)$ 个子树染色的修改，这个很容易解决；由于本题染色的特殊性（仅有一种颜色，最后询问未染色结点数目），还可以考虑直接转区间 $+1$ 差分做，最后输出值为 $0$（即未被染色）的元素数即可

接下来就考虑如何求出每条边是否产生贡献

这可以随意固定一个根 dfs，对于向子树的边可以用线段树合并或 dsu on tree 确定；至于向父亲的边，可以用全局同颜色数减去子树内同颜色数来确定，子树内同颜色数可以用一样的方式求出。如果是 dsu on tree 的话写起来也不会很麻烦；这部分复杂度即为 $\Theta(n\log n)$

但能不能再给力点？

冷静一下，刚才我们做的其实就是，询问子树（处理的那条有向边连向的那个结点的子树）内是否存在某种颜色的结点（`1.`），和询问子树内和子树根同颜色的结点数目（`2.`）

考虑反过来处理这些询问。即在 dfs 时维护当前结点 $u$ 到根 $r$ 的路径 $p(u, r)$，并考虑更新它们

看起来貌似更难做了。但仔细观察，首先发现在结点 $u$ 我们只会更新和结点 $u$ 同色的结点，接着发现我们其实只需对每种颜色维护深度最深的那个就可以做了。具体来说，对于 `1.`，从 $u$ 的边 $(u, v)$ dfs 进入 $v$ 子树时会有一个 “$v$ 子树内是否存在 $u$ 的颜色的结点” 的询问，我们比较这里的 “$u$” 的深度并保留，容易反证这样是不重不漏的；对于 `2.`，我们单纯地对每种颜色维护 $p(u, r)$ 上深度最深的那个结点，然后用类似 dp 的思路更新即可（感觉比较显然就不具体描述了；由于转移只在同颜色结点间，可以考虑同颜色的结点的虚树进行理解）

于是就能把这部分做到 $\Theta(n)$ 了

（这里已经尽力详细地描述了，如果还感觉讲不清楚可以参考代码qaq）

## CODE

实现细节可能较多

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using std::vector;
using std::min;
using std::sort;

const int MAXN =2e5+20;

/*------------------------------IO------------------------------*/

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
}
using namespace IO_number;

/*------------------------------Graph------------------------------*/

int first[MAXN], tote;
struct edge{
	int net, to;
}e[MAXN<<1];

inline void addedge(const int &u, const int &v){
	++tote, e[tote].to =v, e[tote].net =first[u], first[u] =tote;
	++tote, e[tote].to =u, e[tote].net =first[v], first[v] =tote;
}

inline int twin(const int &eid){
	return ((eid-1)^1)+1;
}

/*------------------------------Arrays------------------------------*/

vector<int> a, cnt_tot_color;

/*------------------------------Range_Query------------------------------*/

namespace RQ{
	vector<int> diff;
	
	void init(const int &n){
		diff.resize(n+2, 0);
	}

	void assign(const int &l, const int &r){
		const int n =a.size()-1;
		
		++diff[l], --diff[min(r, n)+1];
	}
}
using RQ::assign;

/*------------------------------Dfs------------------------------*/

namespace Dfs{
	vector<int> dfn, siz;
	int Dfn =0;
	
	void dfs_pre(const int &u, const int &fa){
		siz[u] =1, dfn[u] =++Dfn;
		for(int l =first[u]; l; l =e[l].net)
			if(e[l].to != fa)
				dfs_pre(e[l].to, u), siz[u] +=siz[e[l].to];
	}
	
	int vis[MAXN];
	vector<int> cnt;
	/**
	 * vis[color]: p(r, u) 每种颜色深度最深的结点，的进入当前子树的边 id //
	 * cnt[u]: u 子树内有多少同颜色结点 ( 含 u ) //
	**/
	void dfs(const int &u, const int &fa){
		cnt[u] =1;
		
		for(int l =first[u]; l; l =e[l].net)
			if(e[l].to != fa){
				int backup =vis[a[u]];
				vis[a[u]] =l;
				dfs(e[l].to, u);
				vis[a[u]] =backup;
			}
		
		// 1. 考虑边 vis[a[u]] ( 有向 ) 是否产生贡献 //
		if(vis[a[u]]){
			const int eid_into_subtree =vis[a[u]];
			const int _u =e[eid_into_subtree].to;
			/* V- 可能有多次相同的修改，不过无所谓 */
			assign(1, dfn[_u]-1), assign(dfn[_u]+siz[_u], 0x3f3f3f3f);
			
			// 类似 dp 地统计 cnt //
			cnt[e[twin(eid_into_subtree)].to] +=cnt[u];
		}
		// 2. 考虑 u 向根方向的边是否产生贡献 //
		if(cnt[u] < cnt_tot_color[a[u]])
			assign(dfn[u], dfn[u]+siz[u]-1);
	}
	
	void init(const int &n){
		dfn.resize(n+1), siz.resize(n+1), cnt.resize(n+1);
	}
}
using Dfs::dfs_pre;
using Dfs::dfs;

/*------------------------------Main------------------------------*/

void recolor(){
	const int n =a.size()-1;
	
	struct node{
		int val, pos;
	};
	vector<node> arr(n);
	for(int i =0; i < n; ++i)
		arr[i].val =a[i+1], arr[i].pos =i+1;
	sort(arr.begin(), arr.end(), [&](const node &A, const node &B){ return A.val < B.val; });
	int Col =0;
	for(int i =0; i < n; ++i){
		if(i != 0 && arr[i].val != arr[i-1].val)
			++Col;
		a[arr[i].pos] =Col;
		++cnt_tot_color[Col];
	}
}

int main(){
	int n =read();
	a.resize(n+1), cnt_tot_color.resize(n, 0);
	for(int i =1; i <= n; ++i)
		a[i] =read();
	for(int i =0; i < n-1; ++i)
		addedge(read(), read());
	
	recolor();
	Dfs::init(n);
	dfs_pre(1, 0);
	RQ::init(n);
	dfs(1, 0);
	int ans =0;
	for(int i =1, sum =RQ::diff[1]; i <= n; ++i, sum +=RQ::diff[i])
		if(sum == 0)
			++ans;
	printf("%d", ans);
}
```

---

