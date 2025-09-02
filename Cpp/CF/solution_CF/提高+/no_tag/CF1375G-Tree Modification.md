# Tree Modification

## 题目描述

You are given a tree with $ n $ vertices. You are allowed to modify the structure of the tree through the following multi-step operation:

1. Choose three vertices $ a $ , $ b $ , and $ c $ such that $ b $ is adjacent to both $ a $ and $ c $ .
2. For every vertex $ d $ other than $ b $  that is adjacent to $ a $ , remove the edge connecting $ d $ and $ a $ and add the edge connecting $ d $ and $ c $ .
3. Delete the edge connecting $ a $ and $ b $ and add the edge connecting $ a $ and $ c $ .

As an example, consider the following tree:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1375G/eafeabf55552a872e419f2e9d6a1d53612765f20.png)The following diagram illustrates the sequence of steps that happen when we apply an operation to vertices $ 2 $ , $ 4 $ , and $ 5 $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1375G/c824e4b3dc28492ea8b0c323d7e50d614cefde05.png)It can be proven that after each operation, the resulting graph is still a tree.

Find the minimum number of operations that must be performed to transform the tree into a star. A star is a tree with one vertex of degree $ n - 1 $ , called its center, and $ n - 1 $ vertices of degree $ 1 $ .

## 说明/提示

The first test case corresponds to the tree shown in the statement. As we have seen before, we can transform the tree into a star with center at vertex $ 5 $ by applying a single operation to vertices $ 2 $ , $ 4 $ , and $ 5 $ .

In the second test case, the given tree is already a star with the center at vertex $ 4 $ , so no operations have to be performed.

## 样例 #1

### 输入

```
6
4 5
2 6
3 2
1 2
2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4
2 4
4 1
3 4```

### 输出

```
0```

# 题解

## 作者：Andrewzdm (赞：14)

这道题问我们最少通过多少步把普通的树变成菊花图，找不到什么比较好的算法（反正我是没找到），于是不得不分析题目里一连串复杂操作的实质。

树是一个二分图，也就是说，我们可以对树进行黑白染色，使得一个黑色节点周围所有与它相邻的节点都是白色节点，反之亦然。而菊花图进行黑白染色过后，其中有一个颜色只出现了 $1$ 次，所以我们的目标就是让其中一个颜色出现的次数变为 $1$。

逐一分析题目中的操作：

操作 $1$ 中我们选择了三个相邻的节点 $a,b,c$，因为 $b$ 与 $a,c$ 相邻，所以不妨设 $b$ 为黑色，$a,c$ 为白色。

操作 $2$ 中，所有除 $b$ 外与 $a$ 相邻的节点均为黑色，把它们从 $a$ 上挂到 $c$ 上，它们还是黑色，颜色并未改变。

操作 $3$ 中，把 $a$ 从 $b$ 挂到 $c$ 上，$a$ 由白色变为黑色。

所以我们一连串操作下来**只改变了一个节点的颜色**！

那么我们首先**猜想**，设 $cnt_w$ 表示原树中被染成白色的节点个数，$cnt_b$ 表示原树中被染成黑色的节点个数，那么答案就是 $\min\{cnt_w, cnt_b\}-1$。

实际上这是正确的，因为我们每次一定能将 $cnt_w$ 和 $cnt_b$ 其中一个减去 $1$。我们可以证明，只要其中一种颜色，满足被染成这种颜色的节点数大于 $1$，那么必定有两个节点被染成这种颜色，且存在另一个不同色的节点与它们都相邻，那么我们就可以通过题目中的操作将这种颜色所对应的 $cnt$ 减去 $1$。

最后就是一个 DFS 黑白染色的事了。
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 2e5 + 10;
vector<int> g[maxn];
int n, cnt[2];

void dfs(int x, int fa, int col)
{
	cnt[col]++;
	for(int v : g[x])
		if(v != fa)
			dfs(v, x, col ^ 1);
	return;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0, 0);
	printf("%d\n", min(cnt[0], cnt[1]) - 1);
	return 0;
}
```

---

## 作者：123456zmy (赞：3)

题意：  
给一棵树，要将其转为一个菊花图，问最小操作次数。  
一次操作为选择一个点，并将其与其相邻的点一起连到一个距离这个点 $2$ 的点上。
___
可以通过 dp 求解：$dp_i$ 表示将以 $i$ 为根的子树内的节点挂到 $i$ 点的操作次数，对于每个点，其 $dp$ 值为这个点的孙子节点的 $dp$ 值之和加上其孙子节点的数量（实际意义大概是把其所有孙子节点的子树挂到这些点，然后再将这些点并到这个点）。使用换根 dp 就可以过了。

```cpp
#include<bits/stdc++.h>
int n,a[400001],a1[400001],a2[200001],u,v,ans[200001],ansm=1e9,cnt[200001];
void dfs(int i,int fa)
{
	int a3=a2[i];
	do if(a3!=fa)dfs(a[a3],a3^1),++cnt[i],ans[a[fa]]+=ans[a[a3]]+1;
	while(a3=a1[a3]);
}
void dfs1(int i,int fa)
{
	int a3=a2[i];
	do if(a3!=fa)ansm=std::min(ansm,ans[a[a3]]=ans[a[fa]]+cnt[a[fa]]-1+(bool)fa,dfs1(a[a3],a3^1);
	while(a3=a1[a3]);
}
int main()
{
	std::cin>>n;
	for(int i=1;i<n;i++)scanf("%d%d",&u,&v),a[i<<1]=v,a1[i<<1]=a2[u],a2[u]=i<<1,a[i<<1|1]=u,a1[i<<1|1]=a2[v],a2[v]=i<<1|1;
	dfs(1,0),dfs1(1,0),std::cout<<std::min(ansm,ans[1]);
}
```

---

## 作者：dztlb (赞：2)

#### 题目大意：让一棵树通过若干次操作成为一个菊花图的最小操作数

众所周知树是一个二分图，但考场上如何将操作与树的二分图特性联系起来？

楼上题解是从二分图出发，本篇题解试从操作本身角度给出思维过程。

观察一次操作，一个距离根为二的点挂到了根上，同时它的子树都挂了上去。

#### 开始

![](https://cdn.luogu.com.cn/upload/image_hosting/zrgtlvzh.png)

#### 结束

![](https://cdn.luogu.com.cn/upload/image_hosting/f3nq1su3.png)

考虑最终的目的：菊花图。一个根节点到所有点的距离为一。发现选择操作的点距离变为一，原本的子树下距离统一减二。观察到以上点到根的奇偶性，只有我们选择的点发生变化。

定义：距离根为偶数的点为偶点，否则为奇点。

注意到，由于操作本身的限制，我们每次只能选择距离为二的点进行处理。
而每次操作本质上消去了一个偶点，其子树距根的距离之奇偶不变。

我们猜测确定根后只用统计偶点数量。

证明：

1. 一个距离不为二的偶点，必然先操作在它之上的偶点。
2. 每次操作都减少一偶点，同时拉近其子树到根的距离。
3. 我们的目标是全为距离一的奇点。
4. 距离大于一奇点的存在建立在偶点中转的前提上。
5. 只要不存在偶点，就没有距离大于一的奇点存在。

对于整棵树，根节点是任选的。事实上通过选择不同的根节点，偶点的集合与奇点集合可以互换。于是进行间隔染色，通过选择不同的根来选择黑色或白色的点为偶点。答案取黑白点数最小值减一。根节点颜色和偶点一样但是不用操作，所以减一。

关键代码：

```cpp
const int maxn=505000;
int co[maxn],n,tot,head[maxn],num[2];
//num[0]为白点数，num[1]为黑点数
struct node{
	int to,next;
}e[maxn*2];
inline void add(int u,int v){
	e[++tot].next=head[u],head[u]=tot,e[tot].to=v;
	e[++tot].next=head[v],head[v]=tot,e[tot].to=u;
}
void dfs(int u,int fap){
	co[u]=!co[fap];//间隔黑白染色，染与其父亲不同的颜色
	++num[co[u]];//统计颜色数量。
	for(register int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==fap) continue;
		dfs(v,u);
	}
}
int main(){
	n=read();
	for(register int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v);
	}
	co[0]=1;//如此1号点颜色为白
	dfs(1,0);
	printf("%d\n",min(num[0],num[1])-1);
	return 0;
}
```



---

## 作者：Kingna (赞：0)

## [CF1375G](https://www.luogu.com.cn/problem/CF1375G) 

树是一个二分图，我们把初始的图进行二分图染色，使得一个黑色节点周围所有与它相邻的节点都是白色节点，反之亦然。因最终是一个菊花图，则一定有一种颜色只出现一次。也就是问操作多少次会让某一种颜色只出现 $1$ 次。

观察操作：选择相邻节点 $a,b,c$，不妨把 $a,c$ 设置为白色，$b$ 设置为黑色。

* 所有与 $a$ 相邻的节点与 $c$ 连边，可以发现这些点颜色不变。
* 将 $a$ 连 $c$，则 $a$ 的颜色变为黑色。

也就是说每一次操作只有一个节点的颜色发生变化。那么下限就是 $\min(cnt_0,cnt_1)-1$。可证明可以取到最小值。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long

const int N = 3e5 + 5, mod = 998244353;

int n, t1, t2, c[N];
vector<int> G[N];

void dfs(int u, int col) {
	c[u] = col;
	if (col == 1) t1++;
	if (col == 2) t2++;
	for (auto v : G[u]) {
		if (c[v]) continue;
		dfs(v, 3 - col);
	}
}

signed main() {
	cin >> n;
	_for(i, 1, n - 1) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u); 
	} 
	dfs(1, 1);
	cout << min(t1, t2) - 1 << endl;
}
```

---

## 作者：lfxxx (赞：0)

最后图要收缩成一个菊花。

假若这个菊花的中心是 $u$，我们来思考下收缩过程。

首先我们会把 $u$ 三级邻域外的所有点收缩到 $u$ 的三级邻域上，然后对 $u$ 的二级邻域中所有点执行操作，注意到这个过程世纪上将问题分割成了将所有点收缩到三级邻域上的若干个子问题。

于是考虑 dp，不妨设计状态 $dp_u,g_u$ 分别表示将 $u$ 的子树内所有点挂到 $u$ 的一级邻域上所需步数与将 $u$ 子树外所有点挂到 $u$ 的一级邻域上所需步数。

有 $dp_u = \sum_{v \in son_u} \sum_{w \in son_v} dp_v+1,g_u = \sum_{v \in son_{fa_u}} (dp_v + 1) - dp_u - 1 + g_{fa_{fa_u}} + dp_{fa_{fa_u}} - dp_{fa_u} - 1$。

对于每个 $u$ 处理出 $\sum_{v \in u} dp_v + 1$ 的值后再暴力枚举转移，由于一个点只会被暴力枚举 $O(1)$ 次，因此总的时间复杂度是 $O(n)$ 的。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
int dp[maxn],g[maxn],n;
vector<int> E[maxn];
void dfs1(int u,int fa){
    for(int v:E[u]){
        if(v!=fa){
            dfs1(v,u);
            for(int w:E[v]){
                if(w!=u) dp[u]+=(dp[w]+1);
            }
        }
    }
}
void dfs2(int u,int fa){
    int sum=0;
    for(int v:E[u]){
        if(v!=fa) sum+=(dp[v]+1);
    }
    for(int v:E[u]){
        if(v!=fa){
            sum-=(dp[v]+1);
            if(fa!=0) g[v]+=g[fa]+1+dp[fa]-dp[v]-1;
            g[v]+=sum;
            dfs2(v,u);
            sum+=(dp[v]+1);
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    int ans=1e18;
    for(int i=1;i<=n;i++) ans=min(ans,dp[i]+g[i]);
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

很好的思维题。考虑将树黑白染色，分析题目中操作的三个步骤：（由于 $a$ 与 $b$ 相邻，$b$ 与 $c$ 相邻，不妨设 $a,c$ 为白色，$b$ 为黑色）

1. 所有与 $a$ 相邻的节点和 $c$ 连边。由于 $a$ 是白色，所以与 $a$ 相邻的点都是黑色，可以连到同为白色的 $c$ 上。
2. 断掉连接 $a$ 与其所有相邻节点的边。无颜色被改变。
3. $a$ 与 $c$ 连边。由于 $a,c$ 同色，所以需要改变 $a$ 的颜色。

综上，一次操作只会改变一个节点的颜色，要将树改为菊花（有一种颜色的节点数只有一），只需要 $\min(w,b)-1$ 即可（$w$ 为白节点个数，$b$ 为黑节点个数）。由于整棵树没有边的损失，且每次操作会把 $a$ 及其子树连到 $c$ 上，所以执行完 $\min(w,b)-1$ 次操作后，一定能把树变成菊花。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int nxt[N<<1],head[N<<1],to[N<<1],cnt,w,b,vis[N];
void addedge(int u,int v)
{
	cnt++;
	nxt[cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}
void dfs(int u,int col)//染色
{
	if(col) w++;//白节点
	else b++;//黑节点
	for(int i=head[u];i;i=nxt[i])
	{
		if(!vis[to[i]])
		{
			vis[to[i]]=1;
			dfs(to[i],col^1);
		}
	}
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		addedge(u,v);
		addedge(v,u);
	}
	vis[1]=1;
	dfs(1,1);
	cout<<min(w,b)-1;//答案
	return 0;
}

---

## 作者：DJRzjl (赞：0)

## [CF1375G](https://www.luogu.com.cn/problem/CF1375G)  Tree Modification

其实原操作就是将某个点 $a$​ 以及它相邻的点内部连边全部断开，连到一个与其距离为 $2$​ 的点 $c$​ 上。

考虑对原树黑白染色，则 $a,c$​ 同色，与 $a$ 相邻的点与 $a,c$ 异色，所以一次操作后重新黑白染色，$a$​ 点颜色会取反，其它点都不变，

于是原操作本质就是取反某个点黑白染色的结果。

考虑最后要求使得原树变为菊花图，而黑白染色时，为菊花图的充要条件是 $n-1$ 个点同色，$1$ 个点异色。

综上，可以推得，答案就是对原树黑白染色后 $\min($黑点数量，白点数量$)-1$。 


---

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int n,a[N],col[N],sa;
vector<int>e[N];

void dfs(int u){
	sa+=(col[u]==1);
	for(auto v:e[u]) if(!col[v]) col[v]=-col[u],dfs(v);
}

int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	col[1]=1,dfs(1);
	printf("%d\n",min(sa,n-sa)-1);
	return 0;
}
```


---

## 作者：Demoe (赞：0)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1375G)

## $\text{Description}$

- 给定一棵 $n$ 个点的树，每次选三个点 $a,b,c$ 要求存在边 $(a,b)$ 和 $(a,c)$，并进行如下操作：
	- 将所有除 $(a,b)$ 的含 $a$ 的边 $(a,x)$ 全改为 $(c,x)$。
    - 将边 $(a,b)$ 改为 $(a,c)$。
- 求最小操作次数使得原图变成菊花图。

## $\text{Solution}$

考虑到原图操作的 $a,c$ 距离定为 $2$。

考虑到 $2$ 不改变奇偶性，则~~瞎~~考虑对树黑白染色。

可发现若钦定 $b$ 点颜色不变，只有 $a$ 点颜色翻转。（可借助题目图观察。）

然后考虑最终状态即菊花图，即为黑白染色后黑白有一种只有 $1$ 个。

那么每次我们最多使黑或白点数减 $1$。

则答案为 $\min\{cnt_{\text{黑}},cnt_{\text{白}}\}-1$。

---

然后来证明每次存在操作使得黑或白点数减 $1$。不妨让黑点减 $1$，白点同理。

若黑点只有 $1$ 个，则已结束。

否则必定存在两个黑点距离为 $2$。（存在白点度数大于 $1$。）

然后钦定这两个黑点为 $a,c$，中间夹着的白点为 $b$。

然后就可以让黑点数量减 $1$ 了。

## $\text{Code}$

```cpp
const int N=2e5+5;
int n,cnt[2],hd[N],cnte;
struct edge{int nxt,t;}es[N<<1];
inline void add(int x,int y){es[++cnte]=(edge){hd[x],y};hd[x]=cnte;}

inline void dfs(int x,int fa,int op){
	++cnt[op];
	for(re i=hd[x];i;i=es[i].nxt)
		if(fa^(es[i].t)) dfs(es[i].t,x,op^1);
}

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);
	for(re i=1;i<n;++i){int x,y;rd(x);rd(y);add(x,y);add(y,x);}
	dfs(1,0,0);
	wr(min(cnt[0],cnt[1])-1);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑操作带来的影响：即将 $a$ 变成一个叶子节点并且不改变除 $a,b$ 其它节点的性质。这里的性质即针对于是否为叶子节点。               

要求构造菊花图，即一个节点是根其它的节点是叶子。

用上述的模型解决问题显得比较困难所以我们不妨稍微换一种模型阐述问题。            

不难发现一个树是菊花图的充要条件是对树进行黑白染色其中有一种颜色只有 $1$ 个另一种颜色有 $n - 1$ 个，这里很重要。              

再带回原来的模型中去，发现这样就相当于 $a,c$ 是同色，然后把 $a$ 的颜色变成 $c$ 的相反色而其它节点颜色不变从而抹去了 $b$ 的讨论，一次操作转化为对一个二元组操作。                 

由于一次只能转换一个颜色，所以答案自然也就是对原树染色后黑白点个数少的那一种颜色个数减 $1$。              

时间复杂度 $O(n)$，难度虚高。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,head[Len],cnt,sum[2],color[Len];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int x,int f)
{
	sum[color[x]] ++;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		color[to] = color[x] ^ 1;
		dfs(to , x);
	}
}
signed main()
{
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);	
	}
	dfs(1 , 0);
	printf("%d\n",min(sum[0] , sum[1]) - 1);
	return 0;
}
```

---

## 作者：feicheng (赞：0)

## $\mathtt{Description}$

给 $n$ 个点的树，可以进行如下操作：

选择三个点 $a,b,c$，要求 $a,b$ 相邻，$b,c$ 相邻，断掉 $a$ 的所有边，并连到 $c$ 上，将 $a,c$ 连边。

求最小操作次数使得该树变成菊花图。

$n\le2\times 10^5$

## $\mathtt{Solution}$

考虑这个魔性的修改带来的效果。

对树进行黑白染色（即 $x$ 节点的父亲和儿子都是与其相反的颜色）并动态维护颜色，发现一次操作之后，只会改变 $a$ 的颜色。

而菊花图的条件则是只有一个点是黑或白，所以答案就是 $\min(\text{white,black)}-1$（即至修改黑点颜色或至修改白点颜色）。

## $\mathtt{Code}$


```cpp
#include <cstdio> 
#include <algorithm>

const int N = 2e5 + 5 ;

int n,cnt;

int head[N],to[N << 1],nxt[N << 1],clr[N] ;

void add(int u,int v) {
	to[++cnt] = v,nxt[cnt] = head[u],head[u] = cnt ;
}

void dfs(int x,int f) {
	clr[x] = clr[f] ^ 1;
	for (int i = head[x]; i; i = nxt[i]){
		int v = to[i] ;
		if (v == f) continue ;
		dfs(v,x) ;
	}
}

int main() {
	scanf("%d",&n) ;
	for (int i = 1,u,v; i < n; ++i)
		scanf("%d%d",&u,&v),add(u,v),add(v,u) ;
	dfs(1,0) ; 
	int w = 0,b = 0 ;
	for (int i = 1; i <= n; ++i)
		w += clr[i],b += clr[i] ^ 1;
	printf("%d",std::min(w,b) - 1) ;
	return 0 ; 
}	 
```


---

## 作者：Cutest_Junior (赞：0)

## 题解 CF1375G 【Tree Modification】

### 做法

记 $f_i$ 为以 $i$ 为中心，全图形成菊花图的最少操作次数。

记 $dp_i$ 为以 $i$ 为中心，$i$ 的子树形成菊花图的最少操作次数。

先证明一个结论：任意距离为 $2$ 的点 $a$、$c$，$f_a=f_c$。

以 $b$ 为树根。

先做 $dp_a$ 次，再做 $dp_c$ 次，使全图只剩两个菊花图和一个根。

若是要以 $a$ 为中心，再 $1$ 次把 $c$ 并过来，若是要以 $c$ 为中心，再 $1$ 次把 $a$ 并过来。

所以，$f_a=f_c=dp_a+dp_c+1$。

然后我们就可以发现，所有 $f$ 中只有两个值，一部分等于 $f_1$，一部分等于 $f_{son_1}$。

然后树形 dp 处理出 $dp$ 数组，然后比较 $f_1$ 和 $f_{son_1}$ 的大小。 

### 代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 5e5 + 5;

vector<int> edge[N];

void add(int u, int v) {
	edge[u].push_back(v);
}

int father[N];
int dp[N];

void dfs(int x) {
	for (int i = 0; i < (int)edge[x].size(); ++i) {
		int to = edge[x][i];
		if (to == father[x]) {
			continue;
		}
		father[to] = x;
		dfs(to);
		dp[father[x]] += dp[to] + 1;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs(1);
	int ans = -1;
	for (int i = 0; i < (int)edge[1].size(); ++i) {
		int to = edge[1][i];
		ans += dp[to] + 1;
	}
	printf("%d", min(ans, dp[1]));
}
```

---

## 作者：crashed (赞：0)

# 题目
[点这里](https://www.luogu.com.cn/problem/CF1375G)看题目。   
# 分析
这道题......第一眼以为是和 [[CF1025G]Company Acquisitions](https://www.luogu.com.cn/problem/CF1025G) 相似的题目。   
   
最后发现它们确实很像......仅限于思考方向，实际方法完全不同。   
    
本题中，由于树是二分图，因此我们可以对它进行黑白染色。对于菊花图，某种颜色只出现在一个点上。因此，我们要考虑操作的颜色数量的影响。   
   
不难发现，一次操作**会且仅会**令一种颜色出现次数减少 1 ，另一种增加 1 ：
   
1. 当我们将 $a$ 连向 $c$ 的时候，它的颜色会改变；
2. 当我们将 $a$ "子树"连向 $c$ 的时候，它们的颜色都不会改变；   
   
......所以......我们只需要统计每种颜色的出现次数，并且决定最终是哪种颜色出现在根就行了。具体而言，我们直接染色，然后数一下每种颜色各自的出现次数，最后计算输出即可。   
    
小结：

这些题实际上都是在考虑**将图整体量化为一个指标**，并且分析操作对这个指标的影响，最终求解（往往求解的时候毫无难度，难度全在思考上了(╯‵□′)╯︵┻━┻）。      
    
~~至于怎么把图化成指标......见仁见智吧~~。入手点在于操作的特点，或许可以帮助你反推出它？
# 代码
```cpp
#include <cstdio>

const int MAXN = 2e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct Edge
{
	int to, nxt;
}Graph[MAXN << 1];

int tot[2];
int head[MAXN];
int N, cnt;

void AddEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void DFS( const int u, const int fa, const int dep )
{
	tot[dep & 1] ++;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa )
			DFS( v, u, dep + 1 );
}

int main()
{
	read( N );
	for( int i = 1, a, b ; i < N ; i ++ )
		read( a ), read( b ), AddEdge( a, b ), AddEdge( b, a );
	DFS( 1, 0, 0 );
	write( MIN( tot[0] - 1, tot[1] - 1 ) ), putchar( '\n' );
	return 0;
}
```

---

## 作者：神之右大臣 (赞：0)

发现这题只有个类似二分图的题解，但是考场上不太好想到吧。
这里有更加贴近蒟蒻的算法：DP。

首先我们可以考虑枚举每个点当根，但是复杂度会爆炸。
于是我们想到了换根法dp。

由于我们会发现，b一定与a和c相连，所以dp时需要考虑隔代关系。

首先默认这棵树以1为根。
我们设f[u]表示把u的子树中的所有点变成一个菊花图，中心是u的最少操作次数。
g[u]表示把u的所有子树上的点合并到u的父亲上的最小花费。h[u]表示把整个图变成一个菊花图且中心节点是u的最小操作次数。

首先看两个显然的转移：

$f[fa]=\sum_{v\neq fa \cap (u,v)\in edge}f[v]+1$

$g[u]=\sum_{v\neq fa \cap (u,v)\in edge}f[v]+1$

如果不理解的话可以看一下手胡的草图（windows自带的画图好丑啊~）

![](https://cdn.luogu.com.cn/upload/image_hosting/e1rh0a6u.png)


我们发现如果把节点v的子树变成形如图中那个框框的样子的操作数可以认为是f[v]。而把以v为中心的子树菊花图全部连接到fa节点上只需要一次操作：u节点是b，fa节点是c，v节点是a。

以上是二次扫描换根法的从下往上递归的部分。

然后考虑从下往上扫描求答案。

初始化肯定是$h[1]=f[1]$。因为我们默认1是根节点。

假如点u的父亲是根节点1，那么$h[u]=g[1]-1$。
否则$h[u]=h[fa]$。

如果看上面的式子比较懵，我们对照着看下面的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/i0v0f9i3.png)

对于v的父亲u是根节点1的情况，我们首先知道把v的子树合并成菊花图的操作次数是$f[v]$。然后加上把除了儿子v以外的所有u的儿子合并到u的父亲节点上的操作次数（注意，这里的父亲指的是广义的父亲，即：一个与其相连的点）
所以$f[v]=f[v]+g[u]-f[v]-1=g[u]-1=g[1]-1$


否则，我们发现这意味着v的父亲u之上还有点，设这个点为fa。那么在原来的操作次数之上我们再加上$h[fa]-g[u]+1$就好了。即$f[v]=f[v]+g[u]-f[v]-1+h[fa]-g[u]+1=h[fa]$
```cpp
#include <bits/stdc++.h>
#define int long long
#define inc(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
int head[200010],cnt;
class littlestar{
	public:
	int to,nxt;
	void add(int u,int v){
		to=v; nxt=head[u];
		head[u]=cnt;
	}
}star[400010];
int n,f[200010],g[200010],h[200010];
void dfs(int u,int fa){
	for(int i=head[u];i;i=star[i].nxt){
		int v=star[i].to;
		if(v==fa) continue;
		dfs(v,u);
		f[fa]=f[fa]+f[v]+1;
		g[u]=g[u]+f[v]+1;
	}
}
void dp(int u,int fa){
	for(int i=head[u];i;i=star[i].nxt){
		int v=star[i].to;
		if(v==fa) continue;
		h[v]=g[u]-1;
        if(fa) h[v]=h[fa];
		dp(v,u);
	}
}
signed main(){
	cin>>n;
	inc(i,1,n-1){
		int x,y;
		scanf("%lld%lld",&x,&y);
		star[++cnt].add(x,y);
		star[++cnt].add(y,x);
	}
	dfs(1,0); h[1]=f[1];
	dp(1,0);
	int ans=LLONG_MAX;
	inc(i,1,n) ans=min(ans,h[i]);
	cout<<ans;
}
/*
6
1 2
2 3
2 4
4 5
4 6
*/
```


---

## 作者：TernaryTree (赞：0)

妙妙题。

考虑对树进行二分图染色。容易发现，进行一次操作会有一个结点的颜色取反。于是答案即为 $\min(cnt_0,cnt_1)-1$。

代码非常简短：

![](https://s2.loli.net/2023/01/22/HeSRmpMWLgrTac2.png)

---

