# Falling Sand (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is the constraints on $ a_i $ . You can make hacks only if all versions of the problem are solved.

Little Dormi has recently received a puzzle from his friend and needs your help to solve it.

The puzzle consists of an upright board with $ n $ rows and $ m $ columns of cells, some empty and some filled with blocks of sand, and $ m $ non-negative integers $ a_1,a_2,\ldots,a_m $ ( $ 0 \leq a_i \leq n $ ). In this version of the problem, $ a_i $ will be equal to the number of blocks of sand in column $ i $ .

When a cell filled with a block of sand is disturbed, the block of sand will fall from its cell to the sand counter at the bottom of the column (each column has a sand counter). While a block of sand is falling, other blocks of sand that are adjacent at any point to the falling block of sand will also be disturbed and start to fall. Specifically, a block of sand disturbed at a cell $ (i,j) $ will pass through all cells below and including the cell $ (i,j) $ within the column, disturbing all adjacent cells along the way. Here, the cells adjacent to a cell $ (i,j) $ are defined as $ (i-1,j) $ , $ (i,j-1) $ , $ (i+1,j) $ , and $ (i,j+1) $ (if they are within the grid). Note that the newly falling blocks can disturb other blocks.

In one operation you are able to disturb any piece of sand. The puzzle is solved when there are at least $ a_i $ blocks of sand counted in the $ i $ -th sand counter for each column from $ 1 $ to $ m $ .

You are now tasked with finding the minimum amount of operations in order to solve the puzzle. Note that Little Dormi will never give you a puzzle that is impossible to solve.

## 说明/提示

For example $ 1 $ , by disturbing both blocks of sand on the first row from the top at the first and sixth columns from the left, and the block of sand on the second row from the top and the fourth column from the left, it is possible to have all the required amounts of sand fall in each column. It can be proved that this is not possible with fewer than $ 3 $ operations, and as such the answer is $ 3 $ . Here is the puzzle from the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534F1/3a2f28320c431f7fc4be328a7626876c2ea55199.png)For example $ 2 $ , by disturbing the cell on the top row and rightmost column, one can cause all of the blocks of sand in the board to fall into the counters at the bottom. Thus, the answer is $ 1 $ . Here is the puzzle from the second example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534F1/a5e473b6fa07dabecf94f6cfb85782199edfaea0.png)

## 样例 #1

### 输入

```
5 7
#....#.
.#.#...
#....#.
#....##
#.#....
4 1 1 1 0 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
#.#
#..
##.
3 1 1```

### 输出

```
1```

# 题解

## 作者：Dfkuaid (赞：9)

[题目链接](https://www.luogu.com.cn/problem/CF1534F1)

## #1.0 题目大意

一个网格图，`#` 表示沙子，`.` 表示空，你可以选择某些沙子使其掉落，沙子掉落过程中会扰动它下落路径周围四格（上下左右）的沙子，使他们一同掉落，问最少选择几块沙子可以使全部沙子掉落。

## #2.0 思路

### #2.1 整体想法

考虑将 “扰动” 这一关系转化成边，“扰动” 这一关系是单向的，即若 $A$ 能扰动 $B$，不代表 $B$ 能扰动 $A$。

将图中的 `#` 用 “扰动” 为边连接后会得到一张有向图，我们发现，在这张图中存在许多**强连通分量（SCC）**，很显然，每一个 $\text{SCC}$ 中的沙子扰动任意一个，该 $\text{SCC}$ 中的所有沙子都会掉落，那么我们便可以将每个 $\text{SCC}$ 看做一个点，即用 $\text{Tarjan}$ 算法进行缩点。

缩点之后会得到一个**有向无环图（DAG）**，在这张图上，无论如何都不会被扰动的点就是我们要选择的点。那么我们只需要知道这张 $\text{DAG}$ 中有多少个入度为 $0$ 的点即可。

下面来看每一步的细节。

### #2.2 储存

题目中只给了这样一条对网格大小的限制：

$$
n\cdot m\leq400000.
$$

也就是说，$n$ 和 $m$ 都有可能达到 $4\cdot10^5$ 的级别，我们并不能直接开两维大小都是 $4\cdot10^5$ 的二维数组进行储存。但是，**格子的数量范围是确定的**，我们可以直接开一维数组 ```mp[400010]``` 来储存格子的信息。

转换方法也很简单，将格子 $(i,j)$ 编号为 $(i-1)\cdot m+j$ 即可，其实就是自左而右、自上而下地编号。

``` cpp
inline int get_ind(const int &i,const int &j){
    return (i - 1) * m + j;
}
```

### #2.3 建图

找到真正可能出现的 “扰动” 并转化成边是建图的关键。我们来看一个沙子 $A$ 下落时究竟可能会扰动哪些沙子（假设这些沙子存在）。

- $A$ 正上方一格的沙子；
- $A$ 正下方距离最近的沙子；
- $A$ 左边一列，比 $A$ 正下方距离最近的沙子高度更高的最高的沙子。
- $A$ 右边一列，比 $A$ 正下方距离最近的沙子高度更高的最高的沙子。

![](https://pic.imgdb.cn/item/60c73fb2844ef46bb266b8a8.png)

上图中，$A$ 被选中，只有 $B,C,D,E$ 会被扰动，因为 $F$ 会被 $D$ 先扰动，$G$ 会先被 $C$ 扰动，正对应了我们上面的四种情况。

当然，假若 $C$ 不存在，$G$ 也不会被 $A$ 扰动，显然 $B$ 会比 $A$ 更早接触 $G.$

### #2.4 缩点 & 统计

缩点正常用 $\text{Tarjan}$ 缩点即可。

因为我用的链式前向星存图，记录了边的数量，在统计时直接枚举每条边，判断该边两端点是否在同一 $\text{SCC}$ 中，如果不在，将终点所在的 $\text{SCC}$ 的入度加一即可。

这里不用去重边，因为入度只要有，再多也是有，入度要没有，咋整也没有。

之后统计入度为 $0$ 的 $\text{SCC}$ 的数量即可。

## #3.0 代码实现

``` cpp
const int N = 500010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 2];

char mp[N];
int n,m,a[N],head[N],cnt = 1,ck[N];
int T,dfn[N],low[N],inst[N],st[N],frt;
int scc[N],scnt,icnt[N],ans;

/*获取格子的编号*/
inline int get_ind(const int &i,const int &j){
    return (i - 1) * m + j;
}

/*加边*/
inline void add(const int &u,const int &v){ 
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void tarjan(int x){ // Tarjan 算法缩点
    dfn[x] = low[x] = ++ T;
    inst[x] = true;st[++ frt] = x;
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = min(low[x],low[e[i].v]);
      }
      else if (inst[e[i].v])
        low[x] = min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y = 0;++ scnt;
        do{
            y = st[frt --];
            scc[y] = scnt;
            inst[y] = false;
        }while (y != x);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= m;j ++)
        cin >> mp[get_ind(i,j)];
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    /*建图*/
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= m;j ++){
          if (mp[get_ind(i,j)] == '#'){
              ck[get_ind(i,j)] = true;//标记为沙子
              if (i > 1 && mp[get_ind(i - 1,j)] == '#')//如果正上方一格有沙子
                add(get_ind(i,j),get_ind(i - 1,j));
              /*找正下方最近的沙子*/
              for (int k = i + 1;k <= n;k ++)
                if (mp[get_ind(k,j)] == '#'){
                    add(get_ind(i,j),get_ind(k,j));
                    break;
                }
              /*左边一列，比正下方距离最近的沙子高度更高的最高的沙子*/
              if (j > 1) for (int k = i;k <= n && (mp[get_ind(k,j)] != '#' || k ==  i);k ++)
                if (mp[get_ind(k,j - 1)] == '#'){
                    add(get_ind(i,j),get_ind(k,j - 1));
                    break;
                }
              /*右边一列，比正下方距离最近的沙子高度更高的最高的沙子*/
              if (j < m) for (int k = i;k <= n && (mp[get_ind(k,j)] != '#' || k ==  i);k ++)
                if (mp[get_ind(k,j + 1)] == '#'){
                    add(get_ind(i,j),get_ind(k,j + 1));
                    break;
                }
          }
      }
    /*找 SCC, 缩点*/
    for (int i = 1;i <= n * m;i ++)
      if (ck[i] && !dfn[i]) tarjan(i);
    for (int i = 1;i < cnt;i ++)
      if (scc[e[i].u] != scc[e[i].v])
        icnt[scc[e[i].v]] ++;//统计入度
    for (int i = 1;i <= scnt;i ++)
      if (!icnt[i]) ans ++;//统计答案
    printf("%d",ans);
    return 0;
}
```

## End

希望能给您带来收获。

---

## 作者：gyh20 (赞：3)

根据沙子之间的扰动关系，我们可以建出图，若 $i$ 可以直接扰动 $j$，则 $i$ 向 $j$ 连一条有向边。那么每当我们选择一个沙子之后，所有它能到达的沙子都会掉落。

直接缩点，选择所有入度为 $0$ 的点即可。

当然，建图不能 $n^2$ 建，发现每一个点和它正下方的点一定有边，于是一个点只需要向上，下，以及左/右列在它下面第一个点，于是边数就是 $4n$ 的级别。

```
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
struct edge{int to,next;}e[8000002];
int t,n,m,ans,cnt,head[1000002],b[1000002],dfn[400002],low[400002],tot,stk[400002],ist[400002],tp,tim,bl[400002],blk,rd[400002],lst[400002];
inline void add(re int x,re int y){
	e[++cnt]=(edge){y,head[x]},head[x]=cnt;
}
inline void tj(re int x){
	dfn[x]=low[x]=++tim,ist[x]=1,stk[++tp]=x;
	for(re int i=head[x];i;i=e[i].next)
		if(!dfn[e[i].to])tj(e[i].to),low[x]=min(low[x],low[e[i].to]);
		else if(ist[e[i].to])low[x]=min(low[x],dfn[e[i].to]);
	if(dfn[x]==low[x]){
		++blk;
		do{
			ist[stk[tp]]=0;
			bl[stk[tp]]=blk;
			--tp;
		}while(stk[tp+1]^x);
	}
}
vector<char>a[400002];
vector<int>pos[400002];
char s[400002];
signed main(){
	n=read(),m=read();
	a[0].resize(m+3),pos[0].resize(m+3);
	for(re int i=1;i<=n;++i){
		a[i].resize(m+3),pos[i].resize(m+3);
		scanf("%s",s+1);
		for(re int j=1;j<=m;++j)pos[i][j]=++tot,a[i][j]=s[j];
	}
	for(re int i=n;i;--i){
		for(re int j=1;j<=m;++j)
			if(a[i][j]=='#'){
				if(a[i][j-1]=='#')add(pos[i][j],pos[i][j-1]);
				else if(lst[j-1])add(pos[i][j],lst[j-1]);
				if(lst[j])add(pos[i][j],lst[j]);
				if(a[i][j+1]=='#')add(pos[i][j],pos[i][j+1]);
				else if(lst[j+1])add(pos[i][j],lst[j+1]);
				if(a[i-1][j]=='#')add(pos[i][j],pos[i-1][j]);
			}
		for(re int j=1;j<=m;++j)
			if(a[i][j]=='#')lst[j]=pos[i][j];
	}
	for(re int i=1;i<=n;++i)for(re int j=1;j<=m;++j)if(a[i][j]=='#'&&!dfn[pos[i][j]])tj(pos[i][j]);
	for(re int i=1;i<=tot;++i)for(re int j=head[i];j;j=e[j].next)if(bl[i]^bl[e[j].to])++rd[bl[e[j].to]];
	for(re int i=1;i<=blk;++i)if(rd[i]==0)++ans;
	printf("%d",ans);
}


---

## 作者：Prean (赞：1)

首先，对于一个在第 $ i $ 行 $ j $ 列的沙子，如果他开始下降，他能够使哪些沙子下降呢？

很容易得知是第 $ j-1,j,j+1 $ 列所有行号不小于 $ i $ 的沙子。

对于沙子 $ u $ 下降能够使沙子 $ v $ 下降，我们连一条边 $ (i,j) $。然后缩点，对于度数为0的点，我们他不可能因为别的沙子下降而下降，所以我们得手动扰动这些沙子。

那么答案就是缩点后的图中度数为 $ 0 $ 的点的个数。

然而暴力连边的时空复杂度是 $ O(n^2m) $ 的，我们考虑省掉一些不要的边。

对于三个点 $ (u,v,w) $，若存在边 $ (u,v) $ 和 $ (v,w) $，那么边 $ (u,w) $ 明显可以被省掉。

根据这个优化，我们可以省掉很多边。

比如对于三个点 $ u,v,w $，其中 $ v $ 在 $ u $ 的左下方，$ w $ 在 $ v $ 正下方，那么 $ u $ 很明显只需要连接 $ v $ 而不需要连接 $ w $。

所以，对于一个点，需要连接这些边：

1. 若 $ (i,j) $ 有一块沙子且 **正上方一格** 也有一块沙子，连接 $ (i,j) $ 和 $ (i-1,j) $；
2. 若 $ (i,j) $ 的正下方存在沙子，连接正下方第一块沙子；
3. 若 $ (i,j) $ 的下一列的下方存在沙子，连接下一列的下方第一块沙子；
4. 若 $ (i,j) $ 的上一列的下方存在沙子，连接上一列的下方第一块沙子；

对于 $ 3 $ 类边和 $ 4 $ 类边，反过来从左上/右上第一个沙子连接自己，预处理正上方第一块沙子即可。

当然也可以预处理正下方的第一块沙子，然后不反过来。

code:
```cpp
#include<cstdio>
#include<vector>
const int M=4e5+5;
int n,m,ans,dfc,BCC,in[M],on[M],bl[M],dfn[M],low[M];std::vector<int>G[M];
bool val[M],istk[M];int top,stk[M];
inline int id(const int&x,const int&y){
	return x?(x-1)*m+y:0;
}
inline int min(const int&a,const int&b){
	return a>b?b:a;
}
inline char read_c(){
	char s;while(s=getchar(),s!='.'&&s!='#');
	return s;
}
void Tarjan(int u){
	istk[stk[++top]=u]=true;
	low[u]=dfn[u]=++dfc;
	for(int&v:G[u]){
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(istk[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		register int v;++BCC;
		do bl[v=stk[top--]]=BCC,istk[v]=false;while(v!=u);
	}
}
signed main(){
	register int i,j,lst;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			on[id(i,j)]=(val[id(i,j)]=read_c()=='#')?id(i,j):on[id(i-1,j)];
		}
	}
	for(j=1;j<=m;++j){
		lst=0;
		for(i=n;i>=1;--i){
			if(!val[id(i,j)])continue;
			if(lst)G[id(i,j)].push_back(lst);lst=id(i,j);
			if(val[id(i-1,j)])G[id(i,j)].push_back(id(i-1,j));
			if(j!=1&&on[id(i,j-1)])G[on[id(i,j-1)]].push_back(id(i,j));
			if(j!=m&&on[id(i,j+1)])G[on[id(i,j+1)]].push_back(id(i,j));
		}
	}
	for(i=1;i<=n*m;++i)if(!dfn[i]&&val[i])Tarjan(i);
	for(i=1;i<=n*m;++i){
		for(int&v:G[i])if(bl[v]!=bl[i])++in[bl[v]];
	}
	for(i=1;i<=BCC;++i)ans+=!in[i];
	printf("%d\n",ans);
}
```

---

## 作者：Mobius127 (赞：1)

我爬了，并查集缩点被卡了。

[题目传送门](https://www.luogu.com.cn/problem/CF1534F1)

题目要求所有的沙子都要掉下去，因此最后一行数没用。~~但是我因为读错数而卡了好久珂海星。~~

因为一个沙子若珂以影响到非自身操作列的其他沙子，那么它必然事通过某一条链式的操作影响该点。

说的好迷，我们举个例子：
```
#..

.#.

..#
```

如上，左上角的沙子通过中间的沙子将右下角的沙子给拉了下去。

这引起我们的一个思路：如果我们对每一个沙子与其每一个珂扰动的沙子连上一条有向边，最后统计入度为 $0$ 的点不就好了？

实际上事不行的，因为你少考虑了一个点：图中有环，这简单，上 Tarjan

然后你发现一个问题，这样的话，找点的过程事 $O(n^2m)$ 的，极其容易被卡。

然后就运用到可我们上面的那个例子：我们没必要在左上往右下之间连边，因为中间点已经帮我们连好了。

我们直接往每一个点上下左右最近的四个点连边，这样边的规模就降到了 $4mn$ ，再跑 Tarjan 就珂以了。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <queue>
#define N 410005
using namespace std;
const int M=1e6+5;
typedef long long ll;
const int INF=0x3f3f3f3f;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n, m, a[N], cnt;
vector <int> las[N];
vector <int> pos[N];
char tmp[N];
struct edge{
	int to, nxt;
}G[M*8];
//int f[N], dep[N];
int h[N], tot, in[N];
void add(int x, int y){G[++tot].to=y, G[tot].nxt=h[x], h[x]=tot;}
//int find(int x){
//	if(f[x]==x) return x;
//	return f[x]=find(f[x]);
//}
//void dfs(int x){//被卡的并查集缩点
//	queue <int> Q;
//	for(int i=h[x]; i; i=nxt[i]){
//		int ot=to[i];
//		if(!dep[ot]) dep[ot]=dep[i]+1, dfs(ot);
//		if(dep[find(ot)]>0){
//			if(dep[find(x)]<dep[f[ot]]) f[f[ot]]=f[x];
//			else f[f[x]]=f[ot];
//		}
//	}
//	dep[x]=-dep[x];
//}
int dfn[N], low[N], st[N], top, T, SCC[N], tnc;
bool vis[N];
void tarjan(int x){
	dfn[x]=low[x]=++T;
	vis[x]=true, st[++top]=x;
	for(int i=h[x]; i; i=G[i].nxt){
		int ot=G[i].to;
		if(!dfn[ot]) tarjan(ot), low[x]=min(low[x], low[ot]);
		else if(vis[ot]) low[x]=min(low[x], dfn[ot]);
	}
	if(dfn[x]==low[x]){
		int y=0;tnc++;
		do{SCC[st[top]]=tnc;vis[st[top]]=false;top--;}while(st[top+1]!=x);
	}
}
void solve(){
	int ans=0;
//	for(int i=1; i<=cnt; i++) f[i]=i;
	for(int i=1; i<=cnt; i++)
		if(!dfn[i]) tarjan(i);
	for(int x=1; x<=cnt; x++)
		for(int i=h[x]; i; i=G[i].nxt)
			if(SCC[x]!=SCC[G[i].to]) in[SCC[G[i].to]]++;
//			if(find(x)!=find(to[i])) in[f[to[i]]]++;
//	for(int i=1; i<=cnt; i++)
//		if(!in[i]&&find(i)==i) ans++;
	for(int i=1; i<=tnc; i++)
		if(!in[i]) ans++;
	printf("%d", ans);
}
signed main(){
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	n=read(), m=read();
	las[0].resize(m+9), pos[0].resize(m+9);
	pos[n+1].resize(m+9), las[n+1].resize(m+9);
	for(int i=1; i<=n; i++){
		scanf("%s", tmp+1);
		pos[i].resize(m+9), las[i].resize(m+9);
		for(int j=1; j<=m; j++)
			las[i][j]=0, pos[i][j]=tmp[j]=='#'?++cnt:0;
	}
	for(int i=1; i<=m; i++) a[i]=read();
	for(int j=1, lt=0; j<=m; j++, lt=0)
		for(int i=n; i>=1; i--)
			las[i][j]=lt, lt=pos[i][j]?i:lt;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(pos[i][j]){
				if(j<m&&pos[i][j+1]) 
					add(pos[i][j], pos[i][j+1]);
				else if(j<m&&las[i][j+1]) 
					add(pos[i][j], pos[las[i][j+1]][j+1]);
				if(j>1&&pos[i][j-1]) 
					add(pos[i][j], pos[i][j-1]);
				else if(j>1&&las[i][j-1]) 
					add(pos[i][j], pos[las[i][j-1]][j-1]);
				if(las[i][j]) 
					add(pos[i][j], pos[las[i][j]][j]);
				if(i>1&&pos[i-1][j]) 
					add(pos[i][j], pos[i-1][j]);
			}
	solve();
	return 0;
}

```

---

## 作者：cirnovsky (赞：1)

考虑将一块沙块向其能影响到的沙块连有向边。

具体来讲，我们设 $\textit{last}(i,j)$ 为第 $i$ 行第 $j$ 列往下望见的第一个沙块，若没有则设为 $-1$。然后连边方式就是（研究 $(i,j)$）：

1. 首先 $(i,j)$ 本身是沙块；
2. 向 $\textit{last}(i,j)$ 连边（如果存在，下同）；
3. 若 $(i,j+1)$ 存在，则连 $(i,j+1)$，否则连 $\textit{last}(i,j+1)$；
4. $(i,j-1)$ 同理。

连出来一张图，你可能觉得这张图里面所有出度为 $0$ 的就是答案，实则需要缩个点，然后才成立（样例 #2 就能 hack 非常良心）。

```cpp
#include <bits/stdc++.h>
using ll = long long;
#define all(x) (x).begin(), (x).end()
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int n, m, cnt = 0;
	std::cin >> n >> m;
	std::vector<std::vector<char>> a(n, std::vector<char>(m));
	std::vector<std::vector<int>> last(n, std::vector<int>(m)), id = last;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> a[i][j];
			if (a[i][j] == '#') id[i][j] = cnt++;
		}
	}
	for (int j = 0; j < m; ++j) {
		int pos = -1;
		for (int i = n - 1; ~i; --i) {
			last[i][j] = pos;
			if (a[i][j] == '#') pos = i;
		}
	}
	int col = 0, tot = 0;
	std::vector<std::pair<int, int>> edgeSet;
	std::vector<std::vector<int>> e(cnt);
	std::vector<int> color(cnt), order(cnt), low(cnt);
	std::vector<bool> inStk(cnt);
	std::stack<int> stk;
	auto add = [&] (int x, int y) {
		e[x].emplace_back(y);
		edgeSet.emplace_back(std::make_pair(x, y));
	};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '#') {
				if (j < m - 1) {
					if (a[i][j + 1] == '#') add(id[i][j], id[i][j + 1]);
					else if (~last[i][j + 1]) add(id[i][j], id[last[i][j + 1]][j + 1]);
				}
				if (j > 0) {
					if (a[i][j - 1] == '#') add(id[i][j], id[i][j - 1]);
					if (~last[i][j - 1]) add(id[i][j], id[last[i][j - 1]][j - 1]);
				}
				if(~last[i][j]) add(id[i][j], id[last[i][j]][j]);
				if (i > 0) {
					if (a[i - 1][j] == '#') add(id[i][j], id[i - 1][j]);
				}
			}
		}
	}
	std::function<void(int)> compress = [&] (int x) {
		order[x] = low[x] = tot++;
		inStk[x] = true;
		stk.emplace(x);
		for (int y : e[x]) {
			if (!order[y]) {
				compress(y);
				low[x] = std::min(low[x], low[y]);
			}
			else if (inStk[y]) low[x] = std::min(low[x], order[y]);
		}
		if (order[x] == low[x]) {
			int y = 0;
			++col;
			while (x != y) {
				y = stk.top();
				stk.pop();
				color[y] = col;
				inStk[y] = false;
			}
		}
	};
	for (int i = 0; i < cnt; ++i) {
		if (!order[i]) compress(i);
	}
	std::vector<int> deg(col);
	for (std::pair<int, int> edge : edgeSet) {
		if (color[edge.first] != color[edge.second]) ++deg[color[edge.second]];
	}
	std::cout << std::count(all(deg), 0) << "\n";
	return 0;
}
```

---

## 作者：wizardMarshall (赞：0)

## 题意

$n$ 行 $m$ 列的网格中，`#` 为沙子。若扰动一个沙子，则沙子往下掉落，同时在此过程中相邻四格的沙子都会收到扰动。

## 思路

首先我们发现扰动是单向的，比如处于 $(1,1)$ 位置的沙子可以向下掉扰动 $(3,1)$ 的沙子，反过来就不行。所以很容易想到将扰动关系转换为有向边。

这样我们就可以将网格转换成一个有向图，问题就变成了选择最少的点使得所有点都可以走到。

如果是在一个 DAG 上做这个问题，只要选择没有入度的点就可以了。证明：若一个点有入度，则可以回溯到上一个点，这样由于是有向无环图，所以最终总会找到一个没有入度的点。因此所有有入度的点都会被覆盖。而没有入度的点是一定要选的（不然没有点可以到达它），因此这样最优。

但是这是一个普通的有向图，因此可能存在环。很自然地想到使用 tarjan 来进行缩点，由于一个强连通分量内的点互相都可以到达，所以可以视为一个点。

缩完点后看一下多少点没有入度就行了。

回过头来说说扰动关系怎么建图：只要将一个沙子上一格（若有沙子）、下面的第一个、左边一列的第一个以及右边一列的第一个即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/r31uvqxl.png)

如上图 $(3,1)$ 可扰动 $(2,2)$、$2,4$ 以及 $(5,3)$ 的格子。注意 $(3,4)$ 不被记录，因为其本身就可以被 $(2,4)$ 扰动，没有必要多余记录。


## 代码

实现细节：

其实不用真的把缩点后的图建出来，只要对照原图看一下两个强连通分量是否有连边然后记录被连分量的序号即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

string s[400005];
int n, m;
int idd(int i, int j) {
	return (i - 1) * m + j;
}
vector <int> edge[400005];

int id[400005], dis[400005];
int top = 0, E = 0, dfnn = 0;
int dfn[400005], low[400005];
int stk[400005], in[400005];
void tarjan(int x) {
	dfn[x] = low[x] = ++ dfnn;
	stk[++top] = x;in[x] = 1;
	for (auto i : edge[x]) {
		if (!dfn[i]) {
			tarjan(i);
			low[x] = min(low[x], low[i]);
		}else if (in[i]) {
			low[x] = min(low[x], dfn[i]);
		}
	}
	if (dfn[x] == low[x]) {
		E++;int y;
		do {
			y= stk[top--];
			id[y] = E;in[y] = 0;
		}while(y != x);
	}
	return;
}


signed main() {
	ios::sync_with_stdio();
	cin.tie();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		s[i] = " " + s[i];
	}
	for (int i = 1; i <= m; i++) {
		int x;cin >> x;
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			if (s[i][j] == '#') {
				if (i != 1 && s[i - 1][j] == '#') {
					edge[idd(i, j)].push_back(idd(i - 1, j));
				}int op1 = 0, op2 = 0;
				for (int ni = i; ni <= n; ni++) {
					if (ni != i && s[ni][j] == '#') {
						edge[idd(i, j)].push_back(idd(ni, j));
						break;
					}else {
						if (j != 1 && !op1) {
							if (s[ni][j - 1] == '#') {op1 = 1;
								edge[idd(i, j)].push_back(idd(ni, j - 1));
							}
						}
						if (j != m && !op2) {
							if (s[ni][j + 1] == '#') {op2 = 1;
								edge[idd(i, j)].push_back(idd(ni, j + 1));
							}
						}
					}
				}//cout << endl;
			}
		}
	}
	for (int i = 1; i <= n * m; i++) {
		if (!dfn[i] && s[(i - 1) / m + 1][((i - 1) % m) + 1] == '#')tarjan(i);
	}
	for (int i = 1; i <= n * m; i++) {
		for (auto j : edge[i]) {
			if (id[i] != id[j]) {
				dis[id[j]]++;
			}
		}
	}int ans = 0;
	for (int i = 1; i <= E; i++) {
		if (!dis[i]) {
			ans++;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：fire_and_sweets (赞：0)

我们把一个点和他在重力下落的过程中可以直接影响到的点连边。具体地，我们把一个点和他正下方的第一个点，右边一行下方的第一个点和左边一行下方的第一个点分别都连一条边。

当然，如果这个点上方有与他相邻的点，则也要向上面连一条边。

然后对这个图做一遍 Tarjan 缩点之后，统计有多少个点入度为 $0$，即为答案。

```
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 400010, M = N * 8; 

int n, m; 
vector<vector<char> > a;
int last[N], fei[N], stk[N], top, dfn[N], low[N], din[N];
int h[N], e[M], ne[M], idx, timestamp, id[N], scc_cnt;
bool in_stk[N];

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
} 

int get(int x, int y)
{
	return m * (x - 1) + y;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ timestamp;
	stk[ ++ top] = u, in_stk[u] = true;
	for (int i = h[u]; ~i; i = ne[i])
	{
		int j = e[i];
		if (!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u], low[j]);
		}
		else if (in_stk[j])
			low[u] = min(low[u], dfn[j]);
	}
	if (low[u] == dfn[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
        }   
        while (y != u);
    }
}

signed main() {
	memset(h, -1, sizeof h);
	cin >> n >> m;
	a.resize(n + 3);
	a[0].resize(m + 3);
	for (int i = 1; i <= n; i ++ )
	{
		a[i].resize(m + 3);
		for (int j = 1; j <= m; j ++ ) cin >> a[i][j];
	}
	for (int i = 1; i <= m; i ++ ) cin >> fei[i];
	for (int i = n; i >= 1; i -- )
	{
		for (int j = 1; j <= m; j ++ )
			if (a[i][j] == '#')
			{
				if (a[i][j - 1] == '#') add(get(i, j), get(i, j - 1));
				else if (last[j - 1]) add(get(i, j), last[j - 1]);
				if (last[j]) add(get(i, j), last[j]);
				if (a[i][j + 1] == '#') add(get(i, j), get(i, j + 1));
				else if (last[j + 1]) add(get(i, j), last[j + 1]);
				if (a[i - 1][j] == '#') add(get(i, j), get(i - 1, j));
			}
		for (int j = 1; j <= m; j ++ )
			if (a[i][j] == '#') last[j] = get(i, j);
	}
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
			if (a[i][j] == '#' && !dfn[get(i, j)]) tarjan(get(i, j));
	for (int i = 1; i <= n * m; i ++ )
		for (int j = h[i]; ~j; j = ne[j])
		{
			int k = e[j];
			int a = id[i], b = id[k];
			if (a != b) din[b] ++ ;
		}
	int res = 0;
	for (int i = 1; i <= scc_cnt; i ++ ) 
		res += din[i] == 0;
	cout << res << endl;
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

好奇这道题是不是受到了 MC 的启发。

## 思路

首先我们考虑沙子的“连带”下落机制。

不难发现，一个沙子最多会影响四个位置的沙子：

- 紧挨着在这个沙子上面的

- 这个沙子会落到的下面的那个沙子

- 左下（含同一行）第一个，为什么是第一个呢？因为下面的那些沙子可以转化成第二种情况。

- 右下（含同一行）第一个。与左下的同理。

所以我们对每个沙子建出最多 $4$ 条有向边，总边数是 $n \times m$ 级别的可以接受。

然后不难发现这些沙子会形成很多强联通分量，我们任意扰动一个沙子，那么这个强联通分量就垮了。

所以对原图 Tarjan 一下缩个点，变成一个 DAG。那么我们最后需要手动扰动的就是 DAG 中入度为 0 的点的个数。

---

