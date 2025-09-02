# There Should Be a Lot of Maximums

## 题目描述

You are given a tree (a connected graph without cycles). Each vertex of the tree contains an integer. Let's define the $ \mathrm{MAD} $ (maximum double) parameter of the tree as the maximum integer that occurs in the vertices of the tree at least $ 2 $ times. If no number occurs in the tree more than once, then we assume $ \mathrm{MAD}=0 $ .

Note that if you remove an edge from the tree, it splits into two trees. Let's compute the $ \mathrm{MAD} $ parameters of the two trees and take the maximum of the two values. Let the result be the value of the deleted edge.

For each edge, find its value. Note that we don't actually delete any edges from the tree, the values are to be found independently.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1805E/fb29b941280a29636ad3eeec2c7af98726fa00f1.png)In the first example, after removing edge $ (1, 2) $ no number repeats $ 2 $ times in any of the resulting subtrees, so the answer is $ \max(0, 0)=0 $ .

After removing edge $ (2, 3) $ , in the bigger subtree, $ 1 $ is repeated twice, and $ 2 $ is repeated twice, so the $ \mathrm{MAD} $ of this tree is $ 2 $ .

After removing edge $ (2, 4) $ , in the bigger subtree, only the number $ 1 $ is repeated, and in the second subtree, only one number appears, so the answer is $ 1 $ .

In the second example, if edge $ 1 \leftrightarrow 4 $ is not removed, then one of the subtrees will have two $ 1 $ , so the answer — $ 1 $ . And if edge $ 1 \leftrightarrow 4 $ is deleted, both subtrees have no repeating values, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
1 5
2 1 3 2 1```

### 输出

```
0
2
1
2```

## 样例 #2

### 输入

```
6
1 2
1 3
1 4
4 5
4 6
1 2 3 1 4 5```

### 输出

```
1
1
0
1
1```

# 题解

## 作者：Alex_Wei (赞：9)

### [CF1805E There Should Be a Lot of Maximums](https://www.luogu.com.cn/problem/CF1805E)

提供一个不基于 $\mathrm{occ} = 2$ 的，时间复杂度 $\mathcal{O}(n\log n)$，空间复杂度 $\mathcal{O}(n)$ 的做法（这个比题解区现有题解均优秀）。

考虑快速描述一条边的两侧，自然想到 DFS 序拍平，子树是一段区间，子树外是一段前缀拼上一段后缀。将 DFS 序复制一遍，两部分都是区间。

问题来到：区间查询出现次数不小于 $k$ 的数的最大值。将询问离线扫描线，用权值线段树实时维护每个数当前的倒数第 $k$ 次出现的位置，查询相当于线段树上值不小于 $l$ 的最大下标，这个线段树二分即可。

代码想必不难写。

---

## 作者：Twig_K (赞：4)

这篇题解比较简单粗暴，没有用数据结构。

## 整体思路

我们先考虑整棵树的 MAD 值，设为 $m$，设其出现 $t$ 次。

三种情况：
- $m=0$，则每条边答案均为 $0$.
- $m>0$ 且 $t >2$，答案恒为 $m$.
- $m>0$ 且 $t=2$，设出现两次分别位于节点 $x$ 和 $y$，则除了 $x$ 到 $y$ 的链，答案均为 $m$.

其中前两种情况输入后特判即可。对于第三种情况，只需要单独算一条链的删边情况即可。

## 实现细节
这一段解释链上的方法（也可以选择直接看代码）。

放一组样例：
```php
10
1 9
1 10
1 7
1 8
8 6
8 5
6 4
4 2
8 3
6 2 5 19 19 10 4 15 9 10
```

考虑找到 $x$ 和 $y$ 节点后，先把这条链拉出来（我用了 bfs），如图。

拉出来时记得记录每个点的前驱（或许不是必要的？）和读入时边的编号（必要的，因为之后链上更新时直接更新到读入边的 ans 数组里）。
![](https://cdn.luogu.com.cn/upload/image_hosting/cfzm5qdh.png)
对于图中每一条红边，如果将它断开，所求值为左树和右树的较大值。

可以发现此时（即断开红边时） $x$ 和 $y$ 不会在同一棵子树。

于是可以从右往左更新一遍，再从左往右更新一遍，每条红边被更新两边。

具体地，先从右往左更新，如图：

1. 加入节点 $x$ 及下方挂着的树（蓝色），更新蓝边的答案。
2. 加入节点 $6$ 及下方挂着的树（绿色），更新绿边的答案。
3. 加入节点 $8$ 及下方挂着的树（紫色），更新紫边的答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/r7ylut6x.png)

同样，再从左往右更新（指取较大值）如下图：

1. 加入节点 $y$ 及下方挂着的树（蓝色），更新蓝边的答案。
2. 加入节点 $8$ 及下方挂着的树（绿色），更新绿边的答案。
3. 加入节点 $6$ 及下方挂着的树（紫色），更新紫边的答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/sttx4wg5.png)
每一次更新的是一个点，以及下方挂着的树（太菜了，之前没考虑挂着的树半天查不出来）。这块我用了 dfs 实现。

这样每条链上的边就被左右树分别更新了一遍。

另外，显然黑色边就是全局最优值（前面提到）。最后输出 ans 数组。

上面样例的输出：
```php
19
19
19
19
0
10
10
19
19
```

## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define f first
#define s second
using namespace std;
const int maxn=1e5+10;
typedef pair<int,int> pii;

int n,mx,x,y,tmp;
int a[maxn],vis[maxn],id[maxn],ans[maxn];
//有一些存的东西可能会开重复，或许可以更简洁，但自己码的时候没想太多
queue<int> q;
map<int,int> c;
vector<int> lk;//存一条链
vector<pii> ve[maxn];

void dfs(int u,int k)//用 dfs 更新某一节点以及它下方挂着的树
{
	//这里 vis 数组用来染色。
	//刚才已经将链上的点染成了颜色 1，这里 k 也为颜色（k=2 或 3），其实就是不用每次清空的打标记
	for(int i=0;i<ve[u].size();i++){
		int v=ve[u][i].f;
		if(vis[v]==1||vis[v]==k) continue;
		vis[v]=k;
		if(++c[a[v]]>=2) tmp=max(tmp,a[v]);
		dfs(v,k);
	}
}
void findpath()//在 main 里找到 x 和 y 之后，把这一条链拉出来。这里用 bfs.
{
	q.push(x);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(u==y)
		{
			int i=y;
			//把整条链拉出来，存好
			while(i) lk.push_back(i),i=vis[i];
			break;
		}
		for(int i=0;i<ve[u].size();i++)
		{
			int v=ve[u][i].f;
			if(vis[v]||v==x) continue;
			//vis 存的是链上前驱点，id 存输入时边的编号（方便之后记录答案）
			//在这个函数中 vis 表示前驱点。在这个函数结束清空 vis 之后就不是了
			vis[v]=u,id[v]=ve[u][i].s,q.push(v);
		}
	}
	while(!q.empty()) q.pop();
}
signed main()
{
	scanf("%d",&n);
	int u,v;x=n+1;
	//存图。这里 vector 用了一个 pair，前一个数表示目标节点，后一个数存输入时边的顺序。
	//读入权值，c 是一个桶，用 map 实现。
	//mx：寻找出现次数>=2 的最大点权。
	for(int i=1;i<n;i++) scanf("%d%d",&u,&v),ve[u].push_back(mp(v,i)),ve[v].push_back(mp(u,i));
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),c[a[i]]++;
	for(int i=1;i<=n;i++) if(c[a[i]]>=2&&a[i]>a[mx]) mx=i;
	//对应题解的情况一和情况二（这里合并在一起写了）
	if(mx==0||c[a[mx]]>=3){
		for(int i=1;i<n;i++) printf("%d\n",a[mx]);
		return 0;
	}
	//剩下就是情况三：及出现次数>=2的最大点权刚好出现两次。
	//把这两个点找出来，记为 x 和 y，这里默认 x<y （其实不重要）
	for(int i=1;i<=n;i++) if(a[i]==a[mx]) x=min(x,i),y=max(y,i);
	findpath();
	//vis 和 c 清空（后面要表示不同的意义）
	for(int i=1;i<=n;i++) vis[i]=c[a[i]]=0;
	//赋予 vis 新意义：首先将所有链上的点染为颜色 1
	for(int i=0;i<lk.size();i++) vis[lk[i]]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<ve[i].size();j++)
			if(vis[i]==0||vis[ve[i][j].f]==0)
				ans[ve[i][j].s]=a[mx]; //除了这条链上，其他的边答案都是全局最大值。
	//下面开始暴力跑这一条链（可以结合题解上面的图）
	//以 x 为起点，更新一遍
	tmp=0;
	if(++c[a[x]]>=2) tmp=max(tmp,a[x]);
	//为了区分，以 x 为起点更新染成颜色 2 （习惯上避免清空操作，也可以开 bool 两次清空）
	dfs(x,2);
	for(int i=lk.size()-2;i>=0;i--)
	{
		int v=lk[i];
		ans[id[v]]=tmp;//存边的编号在这里有用
		if(++c[a[v]]>=2) tmp=max(tmp,a[v]);
		dfs(v,2);
	}
	//清空 c 数组，以 y 为起点，反向更新
	for(int i=1;i<=n;i++) c[a[i]]=0;
	tmp=0;
	if(++c[a[y]]>=2) tmp=max(tmp,a[y]);
	//以 y 为起点更新染成颜色 3（习惯上避免清空操作，也可以开 bool 两次清空）
	dfs(y,3);
	for(int i=0;i<=lk.size()-2;i++)//两次 for 循环遍历顺序相反
	{
		int v=lk[i],pre=lk[i+1];
		ans[id[v]]=max(ans[id[v]],tmp);//存边的编号在这里有用
		if(++c[a[pre]]>=2) tmp=max(tmp,a[pre]);
		dfs(pre,3);
	}
	for(int i=1;i<n;i++) printf("%d\n",ans[i]);
	return 0;
}
```
### 再放一个对拍造数据的
$n=10$ 的情况，自己 debug 的时候写的（有点乱）。
```cpp
#include<bits/stdc++.h>
using namespace std;

int mp[100][100];
int fa[100];
int fd(int x){
	if(x==fa[x]) return x;
	return fa[x]=fd(fa[x]);
}
signed main()
{
 	freopen("data.in","w",stdout);
	srand(time(0));
	int n=10;
	printf("%d\n",n);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++){
		int u=rand()%10+1,v=rand()%10+1;
		int fx=fd(u),fy=fd(v);
		while(mp[u][v]||fx==fy) u=rand()%10+1,v=rand()%10+1,fx=fd(u),fy=fd(v);
		printf("%d %d\n",u,v);
		mp[u][v]=mp[v][u]=1;
		fa[fy]=fx;
	}
	for(int i=1;i<=n;i++) printf("%d ",rand()%20+1);
	printf("\n");
	return 0;
}
```

---

## 作者：Pengzt (赞：4)

[CF1805E](https://www.luogu.com.cn/problem/CF1805E)

看到维护树上问题，可以想到线段树合并。

但直接维护显然不行，要一点技巧。

发现 $val$ 的出现次数 $cnt_{val}$ 如果 $\ge 3$，那么一定是一个候选项，若 $cnt_{val}  = 1$，那么一定不能作为候选项。

于是可以用权值线段树维护对于 $val$ 有 $cnt_{val} = 2$ 的 $val$。先离散化，然后再合并线段树。查找时，若右子节点的 $\max = 2$ 或右子节点的 $\min = 0$，就递归查找右节点，反之亦然。若左右子节点都不满足，就返回 $0$，实现需要一点细节。

空间只需要开 $32$ 倍。

时间复杂度：$\mathcal{O}(n\log n)$。

[评测记录](https://www.luogu.com.cn/record/108317122)

最后提供一组 hack：

输入：
```
10 
1 2
1 3
1 4
1 5
1 6
2 7
2 8
3 9
4 10
1 3 3 3 3 4 10 4 6 2
```

输出：
```
3
4
4
4
3
4
3
4
4
```

---

## 作者：_•́へ•́╬_ (赞：4)

## 思路

考虑对每个数值做：

- 这个数值只出现了一次：没用。
- 出现了至少三次：这个数值对整棵树所有边都有贡献。  
    证明这一点：~~感性理解~~。官方题解写的是抽屉原理，割了一条边后两棵肯定是一棵一个，另一棵两个。
- 正好两次：对于这两个点之间的边没贡献，其他都有贡献。

考虑直接写个树剖跑这个东西。可以套线段树区间赋值。我写的是离线。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#define N 100009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,h[N],e[N<<1],nxt[N<<1],a[N],lsh[N],lsz;vector<int>b[N],c[N];
int dfn[N],mmp[N],now,fa[N],top[N],dep[N],sz[N],son[N],ans[N];
map<int,int>cnt;
inline int dfs1(const int&i,const int&f)
{
	fa[i]=f;dep[i]=dep[f]+1;son[i]=-1;sz[i]=1;int maxn=-1;
	for(int j=h[i];j;j=nxt[j])if(e[j]^f)
	{
		sz[i]+=dfs1(e[j],i);
		if(maxn<sz[e[j]])maxn=sz[e[j]],son[i]=e[j];
	}
	return sz[i];
}
inline void dfs2(const int&i,const int&t)
{
	top[i]=t;dfn[i]=now;mmp[now++]=i;
	if(~son[i])
	{
		dfs2(son[i],t);
		for(int j=h[i];j;j=nxt[j])if(e[j]^fa[i])if(e[j]^son[i])
			dfs2(e[j],e[j]);
	}
}
inline void work(int u,int v,const int&i)
{
	c[0].emplace_back(i);
	for(;top[u]^top[v];)
		if(dep[top[u]]>dep[top[v]])
			c[dfn[u]+1].emplace_back(i),
			c[dfn[top[u]]].emplace_back(~i),
			u=fa[top[u]];
		else c[dfn[v]+1].emplace_back(i),
			c[dfn[top[v]]].emplace_back(~i),
			v=fa[top[v]];
	if(dep[u]>dep[v])u^=v^=u^=v;
	c[dfn[u]+1].emplace_back(~i);
	c[dfn[v]+1].emplace_back(i);
}
main()
{
	read(n);
	for(int i=1,u,v;i<n;++i)read(u),read(v),--u,--v,
		e[i]=v,nxt[i]=h[u],h[u]=i,
		e[i+n]=u,nxt[i+n]=h[v],h[v]=i+n;
	for(int i=0;i<n;read(a[i]),lsh[i]=a[i],++i);
	sort(lsh,lsh+n);lsz=unique(lsh,lsh+n)-lsh;
	for(int i=0;i<n;ans[i++]=-1)a[i]=lower_bound(lsh,lsh+lsz,a[i])-lsh;//离散化
	dfs1(0,0);dfs2(0,0);//树剖
	for(int i=0;i<n;++i)b[a[mmp[i]]].emplace_back(mmp[i]);
	for(int i=0;i<lsz;++i)
		if(b[i].size()==2)work(b[i][0],b[i][1],i);//正好两个
		else if(b[i].size()>2)c[0].emplace_back(i);//至少三个
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<c[i].size();++j)
			if(c[i][j]>>31)--cnt[~c[i][j]];
			else++cnt[c[i][j]];
		for(;cnt.size()&&!(--cnt.end())->second;cnt.erase(--cnt.end()));
		if(cnt.size())ans[mmp[i]]=(--cnt.end())->first;
		else ans[mmp[i]]=-1;
	}//离线处理
	for(int i=1;i<n;++i)
	{
		int u=e[i],v=e[i+n];
		if(dep[u]<dep[v])u^=v^=u^=v;
		v=ans[u];
		printf("%d\n",~v?lsh[v]:0);
	}
}
```

## 看看官方题解写了个啥

对于最大的出现至少两次的值进行考虑：

- 至少三次：整棵树答案都是他。
- 两次：除了一条链，答案都是他。  
    然后对于这条链暴力跑。

## [code](https://codeforces.com/blog/entry/114644)

## 看看大佬写了个啥

树剖，然后直接暴力。

## [code](https://codeforces.com/contest/1805/submission/200407518)

---

## 作者：EityDawn (赞：3)

## 思路

首先，分析一下什么时候这个颜色可能成为答案。

1. 全局内这个颜色只出现一次，你无论切哪一条边，这个颜色肯定都不是答案。
2. 全局内这个颜色出现次数 $>2$，你无论切哪一条边，总有一棵树内这种颜色出现次数 $\ge 2$，那么对于所有边，这个颜色有可能是这条边切完后的答案。
3. 全局内这个颜色出现次数 $=2$，比较特殊。我们这样想，整棵树上这种颜色只有两个节点，显然，我们将这两个节点间的某条边切断后，这种颜色必然不会成为这条边的答案。但如果我们切断的是这条路径以外的边，那么这种颜色就有可能成为这条边的答案。

那么分析完后，发现我们要做的，其实就是：

初始时有一棵树，边权都为 $0$，对于情况 $2$ 中的颜色 $c$，我们把所有边的边权 $w_i$ 变为 $\max(w_i,c)$，对于情况 $3$ 中的颜色 $c$，我们需要对除了这两个颜色为 $c$ 的节点之间的路径以外的边的边权 $w_i$ 变为 $\max(w_i,c)$。

最后每条边的边权就是答案。

那么做法就非常清晰了：对树进行树剖，建出线段树，对于 $2$ 全局做 $w_i\leftarrow\max(w_i,c)$，对于 $3$ 把路径对应的区间扣出来，取对于全局的补集，进行 $w_i\leftarrow\max(w_i,c)$ 的操作。

时间复杂度为 $O(n\log^2n)$。

### code

```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<climits>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+10;
vector<int>G[N];
int a[N],b[N],Cnt[N],n,rt=1;
pair<int,int>pos[N];
int dep[N],siz[N],son[N];
pair<int,int>Edge[N];
int top[N],id[N],dfn[N],fa[N],o=0;
void dfs(int now,int from)
{
	siz[now]=1;
	for(int to:G[now])
	{
		if(to==from) continue;
		dep[to]=dep[now]+1,fa[to]=now;
		dfs(to,now);
		siz[now]+=siz[to];
		if(siz[to]>siz[son[now]]) son[now]=to;
	}
	return;
}
void redfs(int now,int Top)
{
	id[dfn[now]=++o]=now;top[now]=Top;
	if(son[now]) redfs(son[now],Top);
	for(int to:G[now])
		if(to==fa[now]||to==son[now]) continue;
		else redfs(to,to);
	return;
}
int ma[N<<2],tag[N<<2];
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
void Max(int val,int x)
{
	ma[x]=max(ma[x],val);
	tag[x]=max(tag[x],val);
}
void push_up(int x){ma[x]=max(ma[lc(x)],ma[rc(x)]);}
void push_down(int x)
{
	if(!tag[x]) return;
	Max(tag[x],lc(x)),Max(tag[x],rc(x)),tag[x]=0;
}
void modify(int p,int q,int val,int l,int r,int x)
{
	if(p>q) return;
	if(p<=l&&q>=r) return Max(val,x);
	push_down(x);
	int mid=(l+r)>>1;
	if(p<=mid) modify(p,q,val,l,mid,lc(x));
	if(q>mid) modify(p,q,val,mid+1,r,rc(x));
	return push_up(x);
}
struct Modify{
	int l,r;
	bool operator<(const Modify&a) const{return l<a.l;}
}q[N];int m=0;
void modify(int x,int y,int w)
{
	m=0;
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		q[++m]={dfn[top[x]],dfn[x]};
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) q[++m]={dfn[x]+1,dfn[y]};
	sort(q+1,q+1+m);
	modify(q[m].r+1,n,w,1,n,1),modify(1,q[1].l-1,w,1,n,1);//情况 3，取补集进行操作
	for(int i=1;i<m;i++) modify(q[i].r+1,q[i+1].l-1,w,1,n,1);
	return;
}
int query(int pos,int l,int r,int x)
{
	if(l==r) return ma[x];
	push_down(x);
	int mid=(l+r)>>1;
	if(pos<=mid) return query(pos,l,mid,lc(x));
	else return query(pos,mid+1,r,rc(x));
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<n;i++)
	{
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
		Edge[i]={x,y};
	}
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+1+n);int len=unique(b+1,b+1+n)-(b+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=lower_bound(b+1,b+1+len,a[i])-b;
		++Cnt[a[i]];
		if(!pos[a[i]].first) pos[a[i]].first=i;
		else pos[a[i]].second=i;
	}
	dfs(rt,0),redfs(rt,rt);
	for(int i=1;i<=len;i++)
	{
		if(Cnt[i]>2) modify(1,n,b[i],1,n,1);//情况 2，全局进行操作
		if(Cnt[i]==2) modify(pos[i].first,pos[i].second,b[i]);
	}
	for(int i=1;i<n;i++)
	{
		if(dep[Edge[i].first]>dep[Edge[i].second])
			cout<<query(dfn[Edge[i].first],1,n,1)<<'\n';
		else cout<<query(dfn[Edge[i].second],1,n,1)<<'\n';
	}
	return 0;
}
```

---

## 作者：CuCl4Loliko (赞：3)

~~大半夜看同学打 CF，自己却没有设备只能口胡，结果直接把五个题全口胡出来了，赛后来补一个题解，十分感谢管理员的审核~~

------------

## 题意
定义一棵树的 $ \text{MAD} $ 值为其出现次数大于等于两次的点权最大值，现在给出一棵树，对于每一条边，你要求出将其删除后形成的两棵新树的 $ \text{MAD} $ 值的最大值。

注意不是真正删掉边，询问间相互独立。

------------

## 暴力

将一条边删除，事实上就是把这棵树分为一棵原树的子树和子树外的节点构成的树。每条边的答案就是两棵树的答案的最大值。

那么我们可以对值域进行离散化，对于每个点进行一次 DFS，开一个桶记录其子树中每个值出现的次数，每个值在子树外的出现次数也可以开一个桶来维护，暴力求解出答案。

时间复杂度为 $ O(n^{2}) $，~~可以通过样例~~。

## 正解

注意到不存在修改，而且需要对每个点进行值域上的统计，那么可以考虑使用树上启发式合并，快速合并出每个节点的答案。

将询问离线到边上，DFS 时统计每条边的答案，开桶维护值域答案时可以使用两个 set 来维护子树内与子树外所有可能答案，以便在值域上进行操作时更新答案。

总时间复杂度为 $ O(n\log^{2}n) $，可以通过此题。

关于什么是树上启发式合并，可以自行查阅相关资料，下面代码中有注释解释具体的合并方法。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
struct egde{
	int to,nxt,id;
}e[maxn];
int cnt,c,tot;
int dfn[maxn],id[maxn];
int a[maxn],w[maxn],X[maxn],head[maxn],t[maxn];
int s[maxn],ans[maxn],son[maxn],tong1[maxn],tong2[maxn];
set<int>S1,S2;

void adde(int u,int v,int id)//加边 
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].id=id;
	head[u]=cnt;
}

void dfs1(int u,int fa)//重链剖分方便找轻重儿子 
{
	s[u]=1;
	dfn[u]=++c;
	id[c]=u;
	int m=0;
	for(int i=head[u];i;i=e[i].nxt)
	{
	 	int y=e[i].to;
	 	if(y==fa) continue;
	 	dfs1(y,u);
	 	s[u]+=s[y];
	 	if(s[y]>m)
	 	{
	 		m=s[y];
	 		son[u]=y;
		}
	}
}

void add(int u)//在子树桶中加入当前节点 
{
	tong1[w[u]]++;
	if(tong1[w[u]]==2) S1.insert(X[w[u]]);
	tong2[w[u]]--;
	if(tong2[w[u]]==1) S2.erase(X[w[u]]);
}

void del(int u)//在子树桶中删除当前节点 
{
	tong1[w[u]]--;
	if(tong1[w[u]]==1) S1.erase(X[w[u]]);
	tong2[w[u]]++;
	if(tong2[w[u]]==2) S2.insert(X[w[u]]);
}

void dfs3(int u,int fa)//暴力dfs并将节点加入桶中 
{
	add(u);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa) continue;
		dfs3(y,u);
	}
}

int dfs2(int u,int fa)//树上启发式合并 
{
	for(int i=head[u];i;i=e[i].nxt)//先求解轻儿子 
	{
		int y=e[i].to;
		if(y==fa||y==son[u]) continue;
		ans[e[i].id]=dfs2(y,u);
	}
	for(int i=head[u];i;i=e[i].nxt)//求解重儿子 
	{
		int y=e[i].to;
		if(y==fa||y!=son[u]) continue;
		ans[e[i].id]=dfs2(y,u);
	}
	for(int i=head[u];i;i=e[i].nxt)//将轻儿子的点权合并到上面重儿子的桶中 
	{
		int y=e[i].to;
		if(y==fa||y==son[u]) continue;
		dfs3(y,u);
	}
	add(u);//求解完当前节点的孩子的答案后将当前节点加入桶 
	int res=max((S1.size()!=0?*(--S1.end()):0),(S2.size()!=0?*(--S2.end()):0));//统计答案 
	if(son[fa]!=u)//如果这个节点是父亲的轻儿子，则将桶清空 
		for(int i=dfn[u];i<=dfn[u]+s[u]-1;i++)
			del(id[i]);
	return res;
}

int main()
{
	int n,u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		adde(u,v,i);
		adde(v,u,i);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),X[i]=a[i];
	sort(X+1,X+1+n);
	tot=unique(X+1,X+1+n)-X-1;//离散化与预处理 
	for(int i=1;i<=n;i++)
	{
		w[i]=lower_bound(X+1,X+1+tot,a[i])-X;
		tong2[w[i]]++;
		if(tong2[w[i]]==2) S2.insert(X[w[i]]);
	}
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Luciylove (赞：2)

貌似直接把标程给大力创飞了？？

来点可以通过 $k$ 为任意数的奇怪想法。

对于每种颜色建立虚树，然后我们考虑虚树对于每一条返祖边的贡献，记下一共出现次数为 $w$。

我们分类断开后子树外和子树内的贡献。

我们枚举虚树上的节点 $x$，如果 $sz_x \geq k$ 我们可以对 $x$ 的返祖链上的边取 $\max$，如果 $w - sz_x \geq k$ 我们则是对于割去子树内的边有贡献。

发现贡献是对一段链上的边取 $\max$ 和单点查询和对于子树内的边取 $\max$，我们可以把贡献挂在点 $x$ 上。对于子树内的答案就是子树最大值，子树外的答案就是祖先链上标记的最大值。

如果你是 $O(n)$ 建立虚树，不难得到线性复杂度。

代码不难写，没写。

---

## 作者：lfxxx (赞：2)

考虑一下，我们发现断了一条边后整棵树变成了一个子树节点和其他节点两个部分。

利用 dfs 序转换为区间问题，得到：

询问区间 $[l,r]$ 内出现次数大于等于 $2$ 的数的最大值与总出现次数减去区间内出现次数大于等于 $2$ 的数的最大值。

我们有两个方案维护。

方案 $1$：

先使用 **回滚莫队（不删）** 维护区间 $[l,r]$ 内出现次数大于等于 $2$ 的数的最大值，当区间添加一个新的数 $x$ 时，先更新区间内出现次数，再判断 $x$ 区间内出现次数是否等于 $2$，如果是的就更新最大值。

再使用 **回滚莫队（不增）** 维护总出现次数减去区间内出现次数大于等于 $2$ 的数的最大值，当区间删除一个数 $x$ 时，先更新区间内出现次数，再判断总出现次数减去区间内出现次数是否等于 $2$，如果是的也更新最大值。

但事实上回滚莫队的常数有点大，所以考虑另一种方案。

方案 $2$：

不难发现我们现在需要用一个数据结构维护莫队，这个数据结构应该有一下功能：

1. $O(1)$ 加入或者删除一个数。

2. $O(\sqrt n)$ 查询最大值。

这个时候就可以很自然的想到值域分块，用其记录每种数出现次数，以及查询最大的出现过的数。

并且两种方法复杂度都是 $O(n \sqrt n)$。

由于常数等原因，此处给出方案 $2$ 的实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxsq = 500;
const int B = 317;
const int maxn = 2e5+114;
int sq;
vector<int> edge[maxn];
int dfn[maxn];//dfs 序列颜色 
int val[maxn];//点的颜色
int mx[maxn],mi[maxn];//子树内 dfs 序最大/最小值 
int num;//记录目前 dfs了多少点 
map< pair<int,int> ,int> edge_pos;//记录每条边的编号 
int id[maxn];//记录点 u-fa[u] 这条路径的编号 
int id_dfn[maxn];//dfs 序为 u 的 id[u] 
int anser[maxn];//记录答案 
int cnt[maxn][2];//序列 内/外 出现次数
map<int,int> lsh;//离散化后映射回来 
int n;
inline int pmap(int x){
	return x/B;
}
inline int Lmap(int x){
	return x*B;
}
inline int Rmap(int x){
	return (x+1)*B-1;
}
class Node{
	private:
		int bl_cnt[maxsq];
		int cnt[maxn];
	public:
		inline void add(int x);
		inline void del(int x);
		inline int query();
}chifan;
inline void Node::add(int x){
	int bl=pmap(x);
	cnt[x]++;
	bl_cnt[bl]++;
}
inline void Node::del(int x){
	int bl=pmap(x);
	cnt[x]--;
	bl_cnt[bl]--;
}
inline int Node::query(){
	for(int i=B+3;i>=0;i--){
		if(bl_cnt[i]>0){
			int L=Lmap(i),R=Rmap(i);
			for(int j=R;j>=L;j--){
				if(cnt[j]>0) return j;
			}
		}
	}
	return -1;
}
inline void add(int x){
	if(cnt[x][1]==2){
		chifan.del(x);
	}
	cnt[x][0]++;
	cnt[x][1]--;
	if(cnt[x][0]==2){
		chifan.add(x);
	}
}
inline void del(int x){
	if(cnt[x][0]==2){
		chifan.del(x);
	}
	cnt[x][0]--;
	cnt[x][1]++;
	if(cnt[x][1]==2){
		chifan.add(x);
	}
}
map<int,int> lwx;//反向映射 
inline void dfs(int u,int fa){
	id[u]=edge_pos[make_pair(max(u,fa),min(u,fa))];
	mi[u]=mx[u]=++num;
	lwx[num]=u;
	id_dfn[num]=id[u];
	dfn[num]=val[u];
	for(int v:edge[u]){
		if(v==fa) continue;
		dfs(v,u);
		mx[u]=max(mx[u],mx[v]);
	}
}
struct Query{
	int l,r,id;//存储询问：左右端点以及编号 
}q[maxn];
inline bool cmp(Query a, Query b){
    return (a.l/sq)==(b.l/sq) ? a.r<b.r : a.l<b.l;
}
inline void work(){
	for(int i=1;i<=n;i++){
		q[i].id=id_dfn[i];
		q[i].l=mi[lwx[i]];
		q[i].r=mx[lwx[i]];
		//初始化出现次数 
		cnt[dfn[i]][1]++;
		if(cnt[dfn[i]][1]==2){
			chifan.add(dfn[i]);
		}
	}
	sort(q+1,q+n+1,cmp);
	int l=1,r=1;
	add(dfn[1]);
	for(int i=1;i<=n;i++){
		while(r<q[i].r){
			r++;
			add(dfn[r]);
		}
		while(l>q[i].l){
			l--;
			add(dfn[l]);
		}
		while(r>q[i].r){
			del(dfn[r]);
			r--;
		}
		while(l<q[i].l){
			del(dfn[l]);
			l++;
		}
		anser[q[i].id]=lsh[chifan.query()];
	}
}
inline void edge_add(int u,int v,int pos){
	edge[u].push_back(v);
	edge[v].push_back(u);
	edge_pos[make_pair(max(u,v),min(u,v))]=pos;
}
inline void init(){
	cin>>n;
	sq=sqrt(n);
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		edge_add(u,v,i);
	}
	vector< pair<int,int> > wyb;//val:id
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		wyb.push_back(make_pair(x,i));
	}
	sort(wyb.begin(),wyb.end());
	int last=1;
	for(int i=0;i<wyb.size();i++){
		if(wyb[i].first!=wyb[last].first){
			last=i;
		}
		val[wyb[i].second]=(last+1);
		lsh[(last+1)]=wyb[i].first;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	init();
	dfs(1,0);
	work();
	for(int i=1;i<n;i++){
		cout<<anser[i]<<'\n';
	}
	return 0;
}
```



---

## 作者：狂风之息 (赞：1)

给一个时间复杂度瓶颈在排序上的算法。

显然对于每个权值，要分出现次数 $k$ 来讨论：

- $k=1$ 时没用。

- $k=2$ 时会对除了两个点之间的路径以外的边产生贡献。

- $k\ge3$ 时会对所有边产生贡献。

考虑把最大的有用的（$k\ge2$）权值 $x$ 拉出来，出现次数 $k\ge3$ 就直接判掉（输出 $n-1$ 个 $x$）。

只需要考虑此时 $k=2$ 的情况就行。

因为 $x$ 是最大的有用的数，此时除了对应的那条链上的边其他边答案都为 $x$。

链上的边的答案由其它 $x$ 来贡献。具体做法是遍历一遍把离每个点最近的链上的点求出来，转换成在链上的区间修改。

转化成在链上的区间修改单点查询最大值的问题之后可以排序后使用并查集维护。注意对于其它数还是要分 $k=2$，$k\ge3$ 来讨论。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];

struct Edge{
	int fr,to;
}Ed[100005];

struct Node{
	int x,p;
	friend bool operator<(Node a,Node b){return a.x>b.x;}
}z[100005]; int T;

int Rt,Rt2;
vector<int> ed[100005];

int fa[100005],dep[100005];
void dfs1(int u,int fat,int dept){
	fa[u]=fat; dep[u]=dept;
	for (auto v:ed[u]){
		if (v==fat) continue;
		dfs1(v,u,dept+1);
	}
	return;
}

bool tag[100005];
void jump(int u){
	tag[u]=1;
	if (u!=Rt) jump(fa[u]);
	return;
}

int rt[100005];
void dfs2(int u,int Rt){
	if (tag[u]) Rt=u;
	rt[u]=Rt;
	for (auto v:ed[u])
		if (v!=fa[u]) dfs2(v,Rt);
}

int Fa[100005];
int find(int x){
	return (x==Fa[x])?x:Fa[x]=find(Fa[x]);
}

int m;
int ans[100005];
void upd(int l,int r,int x){  
	while (find(l)<=r){
		ans[find(l)]=max(x,ans[find(l)]);
		Fa[find(l)]=find(find(l)+1);
	}
	return;
}

int main(){
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v; scanf("%d %d",&u,&v);
		ed[u].push_back(v); ed[v].push_back(u);
		Ed[i]=(Edge){u,v};
	}
	for (int i=1;i<=n;i++) scanf("%d",a+i),z[i]=(Node){a[i],i};
	sort(z+1,z+n+1);
	for (int i=1;i<=n;i++){
		int p=i;
		while (z[i].x==z[p].x&&p<=n) p++;
		if (p-i==2){
			Rt=z[i].p;
			Rt2=z[i+1].p;
			break;
		}
		if (p-i>=3){
			for (int j=1;j<n;j++) printf("%d\n",z[i].x);
			return 0;
		}
		i=p-1;
	}
	dfs1(Rt,Rt,1); jump(Rt2); dfs2(Rt,Rt);
	m=dep[Rt2];
	for (int i=1;i<=m;i++) Fa[i]=i;
	for (int i=1;i<=n;i++){
		int p=i;
		while (z[i].x==z[p].x&&p<=n) p++;
		if (p-i==2){
			if (z[i].p==Rt) continue;
			int l=dep[rt[z[i].p]], r=dep[rt[z[i+1].p]];
			if (l>r) swap(l,r);
			upd(1,l-1,z[i].x); upd(r,m-1,z[i].x);
		}
		if (p-i>=3){
			upd(1,m-1,z[i].x);
			break;
		}
		i=p-1;
	}
	for (int i=1;i<n;i++){
		int u=Ed[i].fr, v=Ed[i].to;
		if (!tag[u]||!tag[v]) printf("%d\n",a[Rt]);
		else printf("%d\n",ans[min(dep[u],dep[v])]);
	}
}
```

---

## 作者：luohanzhao (赞：1)

### 做法：树上莫队+值域分块

我们发现，每一条边都连接一个子树和其他部分，所以我们可以分别统计子树的  MAD 和其他所有点的 MAD。

当我们要处理子树答案的时候，容易想到可以用 dfn 序来进行区间处理以此减小时间复杂度。

所以问题就转化为 **在 dfn 序上查询区间出现次数大于等于2的数的最大值**，而这个过程可以用莫队来做。

统计其他部分的 MAD 亦是同理，我们只需要先把所有的点都 ```add``` 一次，再把正常莫队的操作取反。具体地说，在原本莫队的基础上该 ```add``` 时 ```sub```,该 ```sub``` 时 ```add```。这样就可以统计 **l 到 r 区间外的数的出现次数**。

### 但是

容易发现删去一个数后答案是不好统计的。所以用 ~~树上回滚莫队~~ 值域分块，在每次操作完后统计答案。

我们用 $cc_i$ 表示 **第 i 个块中出现次数大于等于2的数的数量**，$cnt_i$ 表示 **i 的出现次数**，最后再写一个 get 函数统计下答案就行了。具体实现可以看代码。

最终时间复杂度为 $O(m \sqrt n + n\sqrt n )$。


## CODE

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int N=2e5+5;
int n,cnt_,head[N],dfn[N],in[N],out[N],k;
int real_num[N],a[N],bel[N],hd[N],cnt[N];
int ans[N][2],fa[N],dep[N],x[N],y[N],cc[N];
map<int,int>mp;
struct node{int v,nxt;}e[N<<1];
struct query{int l,r,id;}q[N];
struct node1{int v,id;}t[N];
bool cmp1(node1 a,node1 b)
{
	return a.v<b.v;
}
void lsh()//离散化 
{
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),t[i].v=a[i],t[i].id=i;
	sort(t+1,t+n+1,cmp1);
	for(int i=1,tot=0;i<=n;i++)if(t[i].v!=t[i-1].v)mp[t[i].v]=++tot,real_num[tot]=t[i].v;
	for(int i=1;i<=n;i++)a[i]=mp[a[i]];
}
void adde(int u,int v)
{
	e[++cnt_]={v,head[u]};
	head[u]=cnt_;
}
void dfs(int u,int f)
{
	dfn[++cnt_]=u,in[u]=cnt_;
	dep[u]=dep[f]+1;fa[u]=f;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==f)continue;
		dfs(v,u);
	}
	out[u]=cnt_;
}
bool cmp(query x,query y)
{
	return (bel[x.l]==bel[y.l]?x.r<y.r:x.l<y.l);
}
void add(int w)//莫队加数操作 
{
	++cnt[a[dfn[w]]];
	if(cnt[a[dfn[w]]]==2)cc[bel[a[dfn[w]]]]++;
}
void sub(int w)//莫队删数操作 
{
	--cnt[a[dfn[w]]];
	if(cnt[a[dfn[w]]]==1)cc[bel[a[dfn[w]]]]--;
} 
int ask()
{
	for(int i=bel[n];i>=1;i--)//从大到小枚举 
	{
		if(!cc[i])continue;
		for(int j=hd[i+1]-1;j>=hd[i];j--)//从大到小枚举 
			if(cnt[j]>=2)return real_num[j];//记得返回真实值 
	}
	return 0;
}
void mo_algorithm_which_can_not_roll_back()
{
	int l=q[1].l,r=l-1;
	for(int i=1;i<=n;i++)
	{
		while(l>q[i].l)add(--l);
		while(l<q[i].l)sub(l++);
		while(r<q[i].r)add(++r);
		while(r>q[i].r)sub(r--);
		ans[q[i].id][0]=ask();
	}
	memset(cnt,0,sizeof(cnt));
	memset(cc,0,sizeof(cc));
}//本来想写回滚莫队的，但发现不需要，于是就有了这个愚蠢的函数名QAQ
void mo_algorithm()
{
	int l=q[1].l,r=l-1;
	for(int i=1;i<=n;i++)add(i);
	for(int i=1;i<=n;i++)
	{
		while(l<q[i].l)add(l++);//操作取反 
		while(l>q[i].l)sub(--l);
		while(r>q[i].r)add(r--);
		while(r<q[i].r)sub(++r);
		//执行到这步时cnt里记的就是除了子树外的其他部分的出现次数。 
		ans[q[i].id][1]=ask();
	}
}
int main()
{
	scanf("%d",&n);k=sqrt(n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		adde(x[i],y[i]),adde(y[i],x[i]);
	}
	lsh();cnt_=0;//回收再利用
   dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		bel[i]=(i-1)/k+1;
		if(bel[i]!=bel[i-1])hd[bel[i]]=i;
	}
	hd[bel[n]+1]=n+1;
	q[n]={in[1],out[1],n};
	for(int i=1;i<n;i++)
	{
		if(fa[y[i]]==x[i])swap(y[i],x[i]);
		q[i]={in[x[i]],out[x[i]],i};//记一下子树的区间 
	}
	sort(q+1,q+n+1,cmp); 
	mo_algorithm_which_can_not_roll_back();
	mo_algorithm();
	for(int i=1;i<n;i++)cout<<max(ans[i][0],ans[i][1])<<"\n";
	return 0;
}
```

---

## 作者：_Cyan_ (赞：1)

## 题目大意
有一棵有 $n$ 个节点的树，定义一个树的 $MAD$ 是这棵树中点权出现至少两次的数的最大值。现在删掉一条边，原来的树被分成两棵树，让你求这两棵树的 $MAD$ 中的较大值。输出中第 $i$ 行的数表示在删掉第 $i$ 条边后的答案。
## 题目分析
首先我们可以很容易就想到一共只有 $3$ 种情况：

1. 点权两两都不相同。

1. 值为 $MAD$ 的点刚好有两个。

1. 值为 $MAD$ 的点有两个以上。

## 解题思路
首先我们看第一种，无论删去哪一条边，答案永远为 $0$ ，所以直接输出 $0$ 即可。

我们再看第三种，无论删去哪一条边，其中总会有一棵树有大于等于 $2$ 个值与原树的 $MAD$ 相等的点存在，所以答案一定是原树的 $MAD$ 。

最后是第二种，我们可以这样想，值与 $MAD$ 相同的点只有两个，那要使答案不是原树的 $MAD$，那就只可能删掉的边在这两个点之间的链上，我们就先处理出在这条链上的边，删掉这条边后分左右两棵树**从大到小枚举**，因为这样就能保证删去上一条边的树的 $MAD$ 必然大于等于删去这一条边的树的 $MAD$，于是只需要顺着依次枚举可能的 $MAD$ 即可(注意要离散化)。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1; c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return x*f;
}
const int N=1e5+5;
int n=read(),head[N],a[N],gen[N],cnt,ans,rt,fl,rr;
int u[N],v[N],tot,res[N];
int qi[N];
map<int,int> yuan,num;
struct node{int v,nxt,id;}p[N<<1];
struct path{int u,v,id;}path[N];
inline void add(int x,int y,int id){
	p[++cnt].v=y;
	p[cnt].id=id;
	p[cnt].nxt=head[x];
	head[x]=cnt;
}
inline void dfs(int x,int fa){
	if(fl) return ;
	for(int i=head[x];i;i=p[i].nxt){
		int v=p[i].v;
		if(v==fa) continue;
		if(!fl){
			path[++tot].id=p[i].id;
			path[tot].u=x;
			path[tot].v=v;	
		}
		if(a[v]==ans){
			fl=1;
			rr=v;
			return ;
		}
		dfs(v,x);
		if(!fl)tot--;
	}
}
inline void dfs2(int x,int fa){
	qi[yuan[a[x]]]++;
	for(int i=head[x];i;i=p[i].nxt){
		int v=p[i].v;
		if(v==fa) continue;
		dfs2(v,x);
	}
}
inline void dfs3(int x,int fa){
	qi[yuan[a[x]]]--;
	for(int i=head[x];i;i=p[i].nxt){
		int v=p[i].v;
		if(v==fa) continue;
		dfs3(v,x);
	}
}
signed main(){
	for(int i=1;i<n;i++){
		u[i]=read(),v[i]=read();
		add(u[i],v[i],i),add(v[i],u[i],i);
	}
	for(int i=1;i<=n;i++) a[i]=read(),++num[a[i]],gen[i]=a[i];
	sort(gen+1,gen+n+1);
	for(int i=n;i>=1;i--){
		if(num[gen[i]]>=2){
			ans=gen[i];
			fl=1;
			if(num[gen[i]]>2) fl=2;
			break;
		}
	}
	if(!fl){for(int i=1;i<n;i++) cout<<0<<'\n'; return 0;} //第一种 
	if(fl==2){for(int i=1;i<n;i++) cout<<ans<<'\n'; return 0;} //第三种
	//第二种 
	int m=unique(gen+1,gen+n+1)-gen-1;//离散化 
	for(int i=1;i<=m;i++) yuan[gen[i]]=i;
	for(int i=1;i<=n;i++) if(a[i]==ans){rt=i; break;}
	int pos=yuan[ans];
	fl=0;
	for(int i=1;i<n;i++) res[i]=-1;
	dfs(rt,0);
	dfs2(path[1].v,path[1].u);//左树从最大的开始 
	for(int i=1;i<=tot;i++){
		while(qi[pos]<2&&pos>0) pos--;
		res[path[i].id]=gen[pos];
		int k=path[i].v;
		qi[yuan[a[k]]]--;
		for(int j=head[k];j;j=p[j].nxt){
			int v=p[j].v;
			if(v!=path[i+1].v&&v!=path[i].u)
			dfs3(v,k);
		}
	}
	//右树同理 
	int k=path[tot].u;
	qi[yuan[a[k]]]++;
	for(int i=head[k];i;i=p[i].nxt){
		int v=p[i].v;
		if(v==path[tot].v) continue;
		dfs2(v,k);
	}
	pos=yuan[ans];
	for(int i=tot;i>=1;i--){
		while(qi[pos]<2&&pos>0) pos--;
		res[path[i].id]=max(res[path[i].id],gen[pos]);
		int k=path[i].u;
		qi[yuan[a[k]]]--;
		for(int j=head[k];j;j=p[j].nxt){
			int v=p[j].v;
			if(v==path[i].v||v==path[i-1].u) continue;
			dfs3(v,k);
		}
		
	}
	for(int i=1;i<n;i++){
		if(res[i]==-1){
			cout<<ans<<'\n';
			continue;
		}
		cout<<res[i]<<'\n';
	}
}
```

---

## 作者：Take_A_Single_6 (赞：0)

duel 赢的题！  
想没想多久，卡细节卡了一会。  
首先观察到 $n\le 10^5$ 这是可以用 $O(n\log^2{n})$ 直接草过去的复杂度。发现启发式合并可以大力出奇迹，直接暴力统计每个值的出现次数，如果子树中某个值出现的次数 $cnt_x\ge 2$ 或者总数 $tot_x-cnt_x\ge2$ 就丢进 set 里面。然后就做完了。  
有一些**坑点**：  
1. $a_i$ 要离散化一下，如果直接丢进 map 里面虽然理论复杂度没变但是常数爆炸。
2. 不要用 long long，常数爆炸。
3. 注意有两棵树要维护。
4. ~~不要把小于号写成小于等于号了。~~

代码如下：

```cpp
#include<bits/stdc++.h>
//#define int long long ！！！
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int n,a[maxn],id[maxn],siz[maxn],l[maxn],clo,son[maxn],ans[maxn],x[maxn],y[maxn],b[maxn],tmp;
vector<int>e[maxn];
int tot[maxn],cnt[maxn];
set<int>mx;
void dfs(int u,int fa)
{
	l[u]=++clo,id[clo]=u,siz[u]=1;
	for(int v:e[u])
	{
		if(v==fa)continue;
		dfs(v,u),siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void getans(int u,int fa,int Son)
{
	cnt[a[u]]++;
	if(tot[a[u]]-cnt[a[u]]<2)mx.erase(a[u]);
	if(cnt[a[u]]>=2)mx.insert(a[u]);//两棵树都要考虑
	for(int v:e[u])if(v!=Son&&v!=fa)getans(v,u,Son);
}
void dsu(int u,int fa,bool kp)
{
	for(int v:e[u])if(v!=fa&&v!=son[u])dsu(v,u,0);
	if(son[u])dsu(son[u],u,1);
	getans(u,fa,son[u]),ans[u]=mx.size()?*--mx.end():0;
	if(!kp)
	{
		for(int i=l[u];i<l[u]+siz[u];i++)
		{
			cnt[a[id[i]]]--;
			if(cnt[a[id[i]]]<2)mx.erase(a[id[i]]);
			if(tot[a[id[i]]]-cnt[a[id[i]]]>=2)mx.insert(a[id[i]]);//两棵树都要考虑
		}
	}
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)x[i]=read(),y[i]=read(),e[x[i]].pb(y[i]),e[y[i]].pb(x[i]);
	for(int i=1;i<=n;i++)a[i]=read(),b[++tmp]=a[i];
	sort(b+1,b+1+tmp);
	tmp=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+tmp,a[i])-b;//离散化
	for(int i=1;i<=n;i++)tot[a[i]]++;
	for(int i=1;i<=n;i++)if(tot[a[i]]>=2)mx.insert(a[i]);//初始化
	dfs(1,1),dsu(1,1,0);
	for(int i=1;i<n;i++)
	{
		if(l[x[i]]>l[y[i]])write(b[ans[x[i]]]),puts("");
		else write(b[ans[y[i]]]),puts("");
	}//边权转dfn较大的点权
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
定义一棵树的价值是其中出现次数大于等于 $2$ 的点权的最大值

给定一棵树，对每条边求删去这条边后分成的两棵树的价值较大值。
### 分析
给树钦定一个根。然后删掉一条边等于从原树里剥出一棵子树。

于是我们求出每个子树的价值和这个子树外的价值就好了。

然后又跟权值出现次数相关，所以容易想到 dsu on tree。

把点权离散化以后，维护子树每种权值出现次数，同时维护两个 `set` 表示子树内/子树外出现次数大于等于 $2$ 的点权最大值。可以统计每种权值全局出现次数用于计算子树外某权值出现次数，这样动态更新集合直接查 $\max$ 即可，其余都是 dsu on tree 板子，时间复杂度 $O(n\log^2 n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
const int maxn=1e5+5;
int n;
int ans[maxn];
pii e[maxn];
vector<int> T[maxn];
int a[maxn],t[maxn],tt;
int bin[maxn];
int siz[maxn],hson[maxn];
int dfn[maxn],nfd[maxn],id[maxn],dfc;
void dfs(int u,int f){
	siz[u]=1,dfn[u]=++dfc,id[dfc]=u;
	for(int v:T[u]){
		if(v==f) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]]) hson[u]=v;
	}
	nfd[u]=dfc;
}
int cnt[maxn];
set<int> ins,ous;
void add(int x){
	cnt[x]++;
	if(cnt[x]>=2) ins.insert(x);
	if(bin[x]-cnt[x]<2) ous.erase(x);
}
void del(int x){
	cnt[x]--;
	if(bin[x]-cnt[x]>=2) ous.insert(x);
	if(cnt[x]<2) ins.erase(x);
}
void solve(int u,int f,int k){
	for(int v:T[u]){
		if(v==f||v==hson[u]) continue;
		solve(v,u,1);
	}
	if(hson[u]) solve(hson[u],u,0);
	for(int v:T[u]){
		if(v==f||v==hson[u]) continue;
		for(int i=dfn[v];i<=nfd[v];i++) add(a[id[i]]);
	}
	add(a[u]);
	if(u!=1) ans[u]=max((*ins.rbegin()),(*ous.rbegin()));
	if(k) for(int i=dfn[u];i<=nfd[u];i++) del(a[id[i]]);
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		T[u].eb(v),T[v].eb(u);
		e[i]=mkpr(u,v);
	}
	for(int i=1;i<=n;i++) t[i]=a[i]=read();
	sort(t+1,t+n+1),tt=unique(t+1,t+n+1)-t-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(t+1,t+tt+1,a[i])-t;
		bin[a[i]]++;
	}
	dfs(1,0);
	ins.insert(0),ous.insert(0);
	for(int i=1;i<=n;i++) if(bin[a[i]]>=2) ous.insert(a[i]);
	solve(1,0,0);
	for(int i=1;i<n;i++){
		int u=e[i].fir,v=e[i].sec;
		if(siz[u]>siz[v]) cout<<t[ans[v]]<<'\n';
		else cout<<t[ans[u]]<<'\n';
	}
	return 0;
}
```

---

## 作者：Engulf (赞：0)

考虑离线处理这个问题，离线子树信息维护可以考虑树上启发式合并（dsu on tree）。

假设我们在 $u$ 这个节点，考虑断掉 $u$ 与其父亲这条边，并将答案存储在 $u$ 上，输出答案的时候就输出边两个端点中深度大的那个。

断掉的这条边把整棵树分为了两棵，考虑用两个 set 来维护，具体地，对于每个权值统计出现次数，若 $\ge 2$ 则扔进 set 里，否则就删掉。可以方便地统计最大值。

时间复杂度 $O(n \log ^2 n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e5 + 5;

int n;

pii e[N];

vector<int> g[N];

int a[N], lsh[N];
int ans[N];

int inc[N], ouc[N];
set<int> in, out;

int siz[N], son[N], dep[N];

void dfs(int u, int fa) {
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    for (auto v: g[u])
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
}

void add(int x) {
    inc[x]++;
    if (inc[x] == 2) in.insert(x);

    if (ouc[x] == 2) out.erase(x);
    ouc[x]--;
}
void del(int x) {
    if (inc[x] == 2) in.erase(x);
    inc[x]--;

    ouc[x]++;
    if (ouc[x] == 2) out.insert(x);
}

void addtr(int u, int fa) {
    add(a[u]);
    for (auto v: g[u])
        if (v != fa)
            addtr(v, u);
}
void deltr(int u, int fa) {
    del(a[u]);
    for (auto v: g[u])
        if (v != fa)
            deltr(v, u);
}

void dsu(int u, int fa, bool keep) {
    for (auto v: g[u])
        if (v != fa && v != son[u])
            dsu(v, u, 0);
    if (son[u]) dsu(son[u], u, 1);
    add(a[u]);
    for (auto v: g[u])
        if (v != fa && v != son[u])
            addtr(v, u);
    ans[u] = max(!in.empty() ? *--in.end() : 0, !out.empty() ? *--out.end() : 0);
    if (!keep) deltr(u, fa);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        e[i] = {u, v};
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> a[i], lsh[i] = a[i];

    sort(lsh + 1, lsh + 1 + n);
    int m = unique(lsh + 1, lsh + n + 1) - lsh - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(lsh + 1, lsh + 1 + m, a[i]) - lsh;
        ouc[a[i]]++;
    }

    for (int i = 1; i <= m; i++)
        if (ouc[i] >= 2)
            out.insert(i);

    dfs(1, 0);
    dsu(1, 0, 0);

    for (int i = 1; i < n; i++) {
        int x = dep[e[i].first] > dep[e[i].second] ? e[i].first : e[i].second;
        cout << lsh[ans[x]] << "\n";
    }

    return 0;
}
```

---

## 作者：DiDi123 (赞：0)

给一个回滚莫队的实现。

其实思路跟大部分题解差不多，就是把树上的数转化到 dfn 序上，然后再拷贝一份复制到后面。这样每次删掉一条边的询问就相当于**查询两端区间里出现次数大于等于 $2$ 的所有数的最大值是多少**。这样的话用回滚莫队可以很容易地实现（每次加入一个数只需要看它是否出现大于等于 $2$ 次即可）。具体实现可以看代码。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200010
struct node
{
	int id,l,r;
}qs[MAXN],eg[MAXN];
struct edge
{
	int to,nex;
}Edge[MAXN];
int cnt,head[MAXN];
void add(int u,int v)
{
	Edge[cnt].to=v;
	Edge[cnt].nex=head[u];
	head[u]=cnt++;
}
int q[MAXN],buk[MAXN],n,a[MAXN],raw[MAXN],dfn[MAXN],num,tw[MAXN],ans[MAXN],sz[MAXN];
int tt[MAXN],dep[MAXN],ct,res,len;
void dfs(int x,int fa,int depth) //把树拍成一个序列
{
	dfn[x]=++num,tw[num]=a[x],sz[x]=1,dep[x]=depth;
	for(int i=head[x];i!=-1;i=Edge[i].nex)
	{
		int y=Edge[i].to;
		if(y==fa) continue;
		dfs(y,x,depth+1),sz[x]+=sz[y];
	}
}
void pre()
{
	len=sqrt(2*n);
	for(int i=1;i<=2*n;i++) q[i]=(i-1)/len+1;
}
bool cmp(node x,node y) //莫队排序
{
	if(q[x.l]!=q[y.l]) return q[x.l]<q[y.l];
	return x.r<y.r;
}
void add(int x)
{
	buk[x]++;
	if(buk[x]>=2) res=max(res,raw[x]);
}
int main()
{
	memset(head,-1,sizeof(head));
	int a1,a2;
	cin>>n;
	pre();
	for(int i=1;i<n;i++)
	{
		cin>>a1>>a2,eg[i]={i,a1,a2};
		add(a1,a2),add(a2,a1);
	}
	for(int i=1;i<=n;i++) cin>>a[i],tt[i]=a[i];
	sort(tt+1,tt+1+n);
	ct=unique(tt+1,tt+1+n)-tt-1;
	for(int i=1;i<=n;i++)
	{
		int tp=lower_bound(tt+1,tt+1+ct,a[i])-tt;
		raw[tp]=a[i],a[i]=tp;
	}
	dfs(1,0,0);
	for(int i=1;i<=n;i++) tw[i+n]=tw[i];
	for(int i=1;i<n;i++)
	{
		int tp=dep[eg[i].l]>dep[eg[i].r]?eg[i].l:eg[i].r;
		int tl=dfn[tp],tr=tl+sz[tp]-1;
		qs[i]={i,tl,tr},qs[i+n-1]={i,tr+1,tl+n-1};
	}
	sort(qs+1,qs+2*n-1,cmp);
	bool flag=true; //表示上一次询问是否跨块
	for(int i=1,j=1,k=1;k<=2*n-2;k++)
	{
		int id=qs[k].id,l=qs[k].l,r=qs[k].r;
		if(q[l]==q[r])
		{
			if(!flag) memset(buk,0,sizeof(buk));
			for(int p=l;p<=r;p++)
			{
				buk[tw[p]]++;
				if(buk[tw[p]]>=2) ans[id]=max(ans[id],raw[tw[p]]);
			}
			for(int p=l;p<=r;p++) buk[tw[p]]--;
			flag=true;
			continue;
		}
		if(q[l]!=q[qs[k-1].l] || flag)
		{
			j=q[l]*len,res=0,flag=false,i=j-1;
			memset(buk,0,sizeof(buk));
		}
		while(i<r) add(tw[++i]);
		for(int p=l;p<j;p++)
		{
			buk[tw[p]]++;
			if(buk[tw[p]]>=2) ans[id]=max(ans[id],raw[tw[p]]);
		}
		for(int p=l;p<j;p++) buk[tw[p]]--;
		ans[id]=max(ans[id],res);
	}
	for(int i=1;i<n;i++) cout<<ans[i]<<'\n';
}
```


---

## 作者：六楼溜刘 (赞：0)

## 题意
- 给你一棵有 $n$ 个结点的树，点有点权。
- 定义一棵树的 $\operatorname{MAD}$ 为这棵树中出现两次及以上的点权中最大的（若没有出现超过两次的那么价值为 $0$）。
- 定义断开一条边的价值为断开后的两棵树的 $\operatorname{MAD}$ 中较大的那个。
- 问断开每条边对应的价值。
- $2 \le n \le 10^5$

## 题解
首先我们可以判定一些显然的结论：
- 所有点权均不相同，全输出 $0$（这个不用证吧）。
- 整棵树的 $\operatorname{MAD}$ 对应的点权出现次数大于 $2$，全输出这个值（我们发现，无论断开哪一条边都有一边有至少两个这样的点，且显然不可能有比它更大的）。

接下来我们就只需要判断整棵树的 $\operatorname{MAD}$ 出现恰好两次的情况。

![图示](https://cdn.luogu.com.cn/upload/image_hosting/heiri6dc.png)

此处加粗的两点是 $\operatorname{MAD}$。

容易发现，此处除了标红的两条边，其它所有边断开后答案均为 $2$。

我们就把问题简化到了这条路径上所有边断开后分成的两棵树的答案。

容易想到，假如（在上图中）从 $1$ 到 $4$ 一条条的考虑，可以从上一条边的答案推出下一条边的答案。

比如断开 $1,2$ 之间的边后，$1$ 所在的这个子树答案就包含了 $1,5$ 的结果，如果要断开 $2,4$ 之间的边就只需要在原先答案上加上 $2,3$ 的影响（莫队既视感Σ(⊙▽⊙"a））。

正如普通莫队存在的问题，我们并不能用这种方法计算减点的贡献，对于这个问题，我选择从另一个方向再跑一次，这样就避免了难以处理减点（我们机房有一个神犇用了两棵权值线段树处理加减点，但是我懒得打线段树，这里权当提供另一种思路）。

并且这个方法的实现异常简便，我们将其中一个结点定为根，从另一个结点一步步往上跳（存一个 $fa$ 数组即可），每次统计当前结点字数内的答案，再存一个 $vis$ 数组防止重复计算。

~~需要注意，这个方法需要离散化，不然会遇到下面这种情况。~~

![其实这是数据点 $3$](https://cdn.luogu.com.cn/upload/image_hosting/8a35gvi5.png)

离散化复杂度 $O(n \log n)$，后面计算的复杂度是 $O(n)$（因为每次每个点只会计算一次，并且只会跑两次），时间复杂度非常优秀，最慢的点只跑了 $202$ 毫秒。

## code

```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#define mem(a,b) memset(a,b,sizeof(a))
#include<vector>
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=1e5+5,inf=0x3f3f3f3f;
int n,a[N],tt[N],ans,rt,f[N],pf[N],st,vis[N];
vector<int> lsh;
struct edge{
	int v,pos;//记录每条边的编号。
	edge(int _v=0,int _pos=0){pos=_pos;v=_v;};
};
vector<edge> e[N];
void dfs(int x,int fa){
	f[x]=fa;
	if(x!=rt&&a[x]==ans) st=x;
	for(auto i:e[x]){
		if(i.v==fa) continue;
		pf[i.v]=i.pos;
       //记录每个节点到父结点这条边的编号，每次一颗子树会对这条边产生贡献。
		dfs(i.v,x);
	}
}
int anst[N],res;//桶和统计答案。
int res1[N],res2[N];//两次分别算出的答案。
void dfs1(int x,int fa){//计算每一层新增的
	anst[a[x]]++;vis[x]=1;
	if(anst[a[x]]>=2&&res<a[x]) res=a[x];
	for(auto i:e[x]){
		if(i.v==fa||vis[i.v]) continue;
		dfs1(i.v,x);
	}
}
signed main(){
	n=read();
	forup(i,1,n-1){
		int u=read(),v=read();
		e[u].push_back(edge(v,i));e[v].push_back(edge(u,i));
	}
	lsh.push_back(0);//塞一个 0，后面有用。
	forup(i,1,n){
		a[i]=read();
		lsh.push_back(a[i]);
	}
	sort(lsh.begin(),lsh.end());
	lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
	forup(i,1,n){
		a[i]=lower_bound(lsh.begin(),lsh.end(),a[i])-lsh.begin();
		tt[a[i]]++;
		if(tt[a[i]]>=2&&a[i]>ans){ans=max(ans,a[i]);rt=i;}
	}//离散化顺带特判，定根。
	if(ans==0){
		forup(i,1,n-1){
			puts("0");
		}
		return 0;
	}else if(tt[ans]>2){
		forup(i,1,n-1){
			printf("%d\n",lsh[ans]);
		}
		return 0;
	}
	dfs(rt,0);//先以其中一个为根。
	int l=st;
	while(l!=rt){
		dfs1(l,f[l]);
		res1[pf[l]]=res==0?-1:res;//特判没找到的情况
		l=f[l];//一步步往上跳
	}
	rt=st;//换根
	mem(anst,0);res=0;mem(vis,0);//一定记得清空
	dfs(rt,0);
	l=st;
	while(l!=rt){
		dfs1(l,f[l]);
		res2[pf[l]]=(res==0?-1:res);
		l=f[l];
	}
	forup(i,1,n-1){
		int asdf=max(res1[i],res2[i]);//防重名，另外答案应取较大值
		if(asdf==-1){//如果是 -1 说明没答案
			puts("0");
		}else if(asdf==0){//如果是 0 说明不在那条路径上
			printf("%d\n",lsh[ans]);
		}else{//其余的则是找到答案
			printf("%d\n",lsh[asdf]);
		}
	}
}
```


---

## 作者：YocyCraft (赞：0)

题意：给出一棵树（顶点数 $n \le 2 \cdot 10^{5}$ )， 每个顶点有一个权重 $a_{i}$ ，定义一棵树的 $MAD$ 为：这棵树的顶点上出现至少 $2$ 次的权重的最大值（如果没有出现至少 $2$ 次的，就定义为 $0$ 。对每条边，求出这条边将原来的树分成的两棵子树的 $MAD$ 值的最大值。

思路：选定一个根，将节点按照 DFS 序重新编号，那么每个节点对应的子树的 DFS 序都是一个区间，这样我们可以将原问题转换为区间查询问题：给定 $n-1$ 个区间，对区间内部和外部分别查询出现至少 $2$ 次的最大的数。从而想到我们可以用莫队维护区间内外部所有数的出现频率。

令 `in` ， `out` 分别表示“区间内部出现至少 $2$ 次的数构成的集合”与“区间外部出现至少 $2$ 次的数构成的集合”， `cnt_in` ， `cnt_out` 分别表示区间内部、外部中每个数的出现频率，我们可以写出如下的代码：

```cpp
void add(int u){
	cnt_in[u]++;
	if(cnt_in[u]==2) in.insert(u);
	cnt_out[u]--;
	if(cnt_out[u]==1) out.erase(u);
}

void remove(int u){
	cnt_out[u]++;
	if(cnt_out[u]==2) out.insert(u);
	cnt_in[u]--;
	if(cnt_in[u]==1) in.erase(u);
}
```

但是注意了：我们需要查询集合中的最大值，如果我们直接用 `std::set` 维护数据的话，单次操作的复杂度是 $O(\log n)$ ，而我们总共需要对集合进行 $O(n \sqrt{n})$ 次增删操作，总共的时间复杂度可以达到 $O(n \sqrt{n} \log n)$ ，这样是会超时的（这就是为什么我在比赛的时候只做出 A-D 题。要是 div1+div2 的话肯定狠狠地掉分了）

所以为了过题，我们需要对集合本身也进行平方根分块处理：将集合中的数每 $\sqrt{n}$ 个分一个块，在增删的过程中维护每个块的元素个数（这样增删操作都是 $O(1)$ ），查找最大值的时候我们从最后一个块向前找，找到一个非空块后就在这个块里找最大值。由于我们每次查询最多找 $\sqrt{n}$ 个块，在一个块内部最多找 $\sqrt{n}$ 次， 单次查询的复杂度是 $O(\sqrt{n})$ 。由于我们只需要查询 $n-1$ 次最大值，总的时间复杂度依然是 $O(n \sqrt{n})$ 。

这样我们就能过题了。下面分块查询的实现代码：

```cpp
class sqrt_set{
public:
	sqrt_set(int M=1){
		assert(M>=0);
		max_value=M;
		block_size=(int)sqrt(M+1);
		block_cnt=(M+block_size)/block_size;
		block=new int[block_cnt];
		for(int i=0;i<block_cnt;i++){
			block[i]=0;
		}
		exist=new bool[M+1];
		for(int i=0;i<=M;i++){
			exist[i]=false;
		}
		_size=0;
	}
	
	void add(int t){
		assert(0<=t && t<=max_value);
		if(exist[t]) return;
		exist[t]=true;
		block[t/block_size]++;
		_size++;
	}
	
	void remove(int t){
		assert(0<=t && t<=max_value);
		if(!exist[t]) return;
		exist[t]=false;
		block[t/block_size]--;
		_size--;
	}
	
	int get_max(){
		for(int i=block_cnt-1;i>=0;i--){
			if(block[i]==0) continue;
			for(int j=min(max_value,(i+1)*block_size-1);j>=i*block_size;j--){
				if(exist[j]) return j;
			}
		}
		return -1;
	}
	
	int get_min(){
		for(int i=0;i<block_cnt;i++){
			if(block[i]==0) continue;
			for(int j=i*block_size;j<=min(max_value,(i+1)*block_size-1);j++){
				if(exist[j]) return j;
			}
		}
		return max_value+1;
	}
	
	int size(){
		return _size;
	}
	
	bool empty(){
		return _size==0;
	}
	
private:
	bool* exist;
	int* block;
	int max_value;
	int block_size;
	int block_cnt;
	int _size;
};
```

[完整代码链接](https://codeforc.es/contest/1805/submission/200532197)


---

## 作者：苏联小渣 (赞：0)

真的很遗憾的一场 CF。就差那么一点就调出 E 了。

考虑一下如果只要求求子树内，出现次数 $\ge 2$ 的最大的数怎么做：对每个点开权值线段树，下标表示权值，线段树合并，维护出现次数的最大值，若右子树最大值 $\ge 2$ 就更新为右子树的答案，否则若左子树最大值 $\ge 2$ 就更新为左子树的答案，否则不更新。

现在加上子树外的限制。容易发现，子树外一个权值出现次数等于总次数减去子树内的次数。所以，对于子树内出现过的权值，我们同样可以用类似上面的方法，维护子树外部分的最大值。对于子树内没有出现过的，它在子树外的出现次数就等于总的出现次数。总次数可以用另一棵线段树维护，那么在 pushup 的时候，我们只需要把这一种情况考虑上就行了。时间复杂度 $O(n \log n)$。

赛后发现官方题解的做法是基于出现次数 $\ge 2$ 这个性质的。事实上题目这个限制完全是多余的。而且 1log 只开了 $10^5$，很不理解。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define lc(x) x<<1
#define rc(x) x<<1|1
int n, p, x, y, cnt, tot, t[100010], a[100010], h[100010], f[400010], g[400010], tm1[100010], ans[100010], rev[100010], F[100010];
map <int, int> mp;
map <int, int> :: iterator it;
struct ask{
	int x, y;
}q[200010];
struct node{
	int x, y, next;
}d[200010];
struct segment{
	int l, r, s, sx, yu, yux;
}seg[2000010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
void build(int k, int l, int r){
	if (l == r){
		f[k] = tm1[l];
		g[k] = l;
		return ;
	}
	int mid = l + r >> 1;
	build(lc(k), l, mid);
	build(rc(k), mid+1, r);
	if (f[rc(k)] >= 2) f[k] = f[rc(k)], g[k] = g[rc(k)];
	else if (f[lc(k)] >= 2) f[k] = f[lc(k)], g[k] = g[lc(k)]; 
}
void pushup(int k, int p){
	if (seg[seg[p].r].s >= 2){
		seg[p].s = seg[seg[p].r].s;
		seg[p].sx = seg[seg[p].r].sx;
	}
	else if (seg[seg[p].l].s >= 2){
		seg[p].s = seg[seg[p].l].s;
		seg[p].sx = seg[seg[p].l].sx;
	}
	else seg[p].s = seg[p].sx = 0;
	if (seg[seg[p].r].yu >= 2){
		seg[p].yu = seg[seg[p].r].yu;
		seg[p].yux = seg[seg[p].r].yux;
	}
	else if (seg[seg[p].l].yu >= 2){
		seg[p].yu = seg[seg[p].l].yu;
		seg[p].yux = seg[seg[p].l].yux;
	}
	else seg[p].yu = seg[p].yux = 0;
	if (!seg[p].l){
		if (f[lc(k)] >= 2 && seg[p].yux < g[lc(k)]) seg[p].yu = f[lc(k)], seg[p].yux = g[lc(k)];
	}
	if (!seg[p].r){
		if (f[rc(k)] >= 2) seg[p].yu = f[rc(k)], seg[p].yux = g[rc(k)];
	}
}
void modify(int &p, int k, int l, int r, int x){
	if (!p) p=++cnt;
	if (l == r){
		seg[p].s = 1;
		seg[p].yu = tm1[x] - 1;
		if (seg[p].yu >= 2) seg[p].yux = x;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(seg[p].l, lc(k), l, mid, x);
	else modify(seg[p].r, rc(k), mid+1, r, x);
	pushup(k, p);
}
int hb(int X, int Y, int k, int l, int r){
	if (!X) return Y;
	if (!Y) return X;
	if (l == r){
		seg[X].s += seg[Y].s;
		if (seg[X].s >= 2) seg[X].sx = l;
		seg[X].yu = tm1[l] - seg[X].s;
		if (seg[X].yu >= 2) seg[X].yux = l;
		return X; 
	}
	int mid = l + r >> 1;
	seg[X].l = hb(seg[X].l, seg[Y].l, lc(k), l, mid);
	seg[X].r = hb(seg[X].r, seg[Y].r, rc(k), mid+1, r);
	pushup(k, X);
	return X;
}
void dfs(int x, int fa){
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		dfs(y, x);
		t[x] = hb(t[x], t[y], 1, 1, tot);
	}
	int now = max(seg[t[x]].sx, seg[t[x]].yux);
	F[x] = fa;
	ans[x] = now;
}
int main(){
	scanf ("%d", &n);
	for (int i=1; i<n; i++){
		scanf ("%d%d", &x, &y);
		q[i].x = x, q[i].y = y;
		add(x, y); add(y, x);
	}
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
		mp[a[i]] = 1;
	}
	for (it=mp.begin(); it!=mp.end(); it++){
		it->second = ++tot;
		rev[tot] = it->first;
	}
	for (int i=1; i<=n; i++){
		a[i] = mp[a[i]];
		tm1[a[i]] ++;
	}
	build(1, 1, tot);
	for (int i=1; i<=n; i++){
		modify(t[i], 1, 1, tot, a[i]);
	}
	dfs(1, 0);
	for (int i=1; i<n; i++){
		if (F[q[i].x] == q[i].y) printf ("%d ", rev[ans[q[i].x]]);
		else printf ("%d ", rev[ans[q[i].y]]);
	}
	return 0;
}
```

---

