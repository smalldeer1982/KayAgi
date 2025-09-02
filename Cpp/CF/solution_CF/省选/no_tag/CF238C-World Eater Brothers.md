# World Eater Brothers

## 题目描述

You must have heard of the two brothers dreaming of ruling the world. With all their previous plans failed, this time they decided to cooperate with each other in order to rule the world.

As you know there are $ n $ countries in the world. These countries are connected by $ n-1 $ directed roads. If you don't consider direction of the roads there is a unique path between every pair of countries in the world, passing through each road at most once.

Each of the brothers wants to establish his reign in some country, then it's possible for him to control the countries that can be reached from his country using directed roads.

The brothers can rule the world if there exists at most two countries for brothers to choose (and establish their reign in these countries) so that any other country is under control of at least one of them. In order to make this possible they want to change the direction of minimum number of roads. Your task is to calculate this minimum number of roads.

## 样例 #1

### 输入

```
4
2 1
3 1
4 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 1
2 3
4 3
4 5
```

### 输出

```
0
```

# 题解

## 作者：Loser_King (赞：6)

模拟赛 T3，赛时写了部分分（10pts+20pts）来不及写正解了（悲）

## 题意

给定一棵边有方向的树，求出至少将几条边反转方向后满足没有入度的结点最多有两个。

$n\le 3000$

## 做法

虽然 $n\le 3000$，$O(n^2)$ 是可以过的，但是实际上本题存在 $O(n)$ 的简单做法，

本篇题解对 $O(n^2)$ 做法不再描述。

考虑树形 DP。（为方便，下称以 $x$ 为根的子树为 $x$ 子树）

1. **状态**：$f_{i,j,k}$ 表示 $i$ 子树中，当前有 $j$ 个结点没有入度（包括 $i$ 结点本身），且当前 $i$ 是否有入度（$k=0/1$）。容易发现这样的状态没有后效性。
  
2. **转移**：考虑 $x$ 结点要合并其儿子 $y$ 的答案时边 $x-y$ 的方向，即图中的 `↕(*)`。
  
```plain
(x) o---┐
    ↕   |
(y)┌o┐ ┌┴┐
   |j| |i|
   └-┘ └-┘
```
  
  枚举当前 $x$ 子树已合并部分中没有入度的点数 $i$ 和 $y$ 子树中没有入度的点数 $j$，以及 $x$ 和 $y$ 结点分别是否有入度，记为 $k_x$ 和 $k_y$ $(0\le i+j\le 2,0\le k_x,k_y \le 1)$。
  
  - 若确定这条边的方向为 $x\Rightarrow y$，那么 $y$ 结点已有入度。若其在 $y$ 子树状态中没有入度，则需将其从没有入度的点中删去。
    
    可以得到 $f_{x,i+j,k_x}=\min(w+f_{x,i,k_x}+f_{y,j+k_y,k_y})$ 。其中 $w$ 为将这条边方向设为 $x\Rightarrow y$ 的费用。
    
  - 同理，若确定这条边的方向为 $x\Leftarrow y$，那么 $x$ 结点已有入度。若其在 $x$ 子树之前的状态中没有入度，则需将其从没有入度的点中删去。
    
    可以得到 $f_{x,i+j,0}=\min(w+f_{x,i+k_x,k_x}+f_{y,j,k_y})$ 。其中 w 为将这条边方向设为 $x\Leftarrow y$ 的费用。
    
  
  实际转移的时候需要使用辅助数组 $g$ 记录，防止状态发生重叠。
  
3. **初始**：$f_{x,1,1}=0$，表示只有根节点的树没有入度，且不需花费。其他状态皆为无穷大。
  
4. **答案**：$\min\limits_{0\le j\le 2,0\le k\le 1} f_{root,j,k}$，其中 $root$ 为指定的树根，树形 DP 的起点。
  

读入时建边 $x\xrightleftharpoons[1]{0} y$，表示将边方向变为 $x\Rightarrow y$ 的代价为 0，将边方向变为 $x\Leftarrow y$ 的代价为 1。

由 DP 过程可知时间复杂度为 $O(n)$ 。

事实上这种 DP 可以解决类似于”没有入度的结点最多有 $k$ 个“的问题，时间复杂度为 $O(nk^2)$ 。

## 代码

目前是洛谷和 CF（并列）最快解。

```cpp
//CF238C AC Code
//written by Loser_King(159686)
//180ms(30ms) / 950B
#include<bits/stdc++.h>
#define to first
#define val second
using namespace std;
int const N=3010,INF=0x3f3f3f3f;
int n,f[N][8][2],g[8][2];
vector<pair<int,int> >e[N];
void add_edge(int x,int y,int v){
	e[x].push_back({y,v});
}
void tomin(int&x,int y){
	if(x>y)x=y;
}
void dfs(int x,int fa){
	f[x][1][1]=0;
	for(auto t:e[x]){
		int y=t.to,w=t.val;
		if(y==fa)continue;
		dfs(y,x);
		memset(g,INF,sizeof g);
		for(int i=0;i<3;i++)
			for(int j=0;j<3-i;j++)
				for(int kx=0;kx<2;kx++)
					for(int ky=0;ky<2;ky++)
						tomin(g[i+j][kx],f[x][i][kx]+f[y][j+ky][ky]+w),//x->y
						tomin(g[i+j][0],f[x][i+kx][kx]+f[y][j][ky]+(w^1));//y->x
		memcpy(f[x],g,sizeof g);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		add_edge(x,y,0),add_edge(y,x,1);
	}
	memset(f,INF,sizeof f);
	dfs(1,0);
	int ans=INF;
	for(int i=0;i<6;i++)
		tomin(ans,f[1][i/2][i&1]);
	cout<<ans<<"\n";
}
```

---

## 作者：AladV (赞：3)

## 题意分析
首先！本题给出的是一个**连通树！！！** 是的非常要命。
然后题意就分析完了$(？！)$

## 做法分析
我们首先感性理解一下，除非这道题最开始就满足条件，否则留 2 个点保持入度为 0 一定比 1 个点优。

理解了上面这一点，我们继续考虑。如果我们设 A 和 B 这两个点是幸运儿，那么又因为这是个连通图，所以他们俩之间一定是这样子的微妙的局势：

$A\to O\to O\to O\to C\leftarrow O\leftarrow O\leftarrow O\leftarrow B$

这个应该也很好理解。如果我们把整个树补全，你会发现一个微妙的事实：这颗树的所有叶子节点也有可能是入度为 0 的。然后你慌了，因为如果是这样子的话就不对了。所以，如果我们设我们两个幸运儿中的一个是根节点，我们就要一点一点往下推进，把所有之前是儿子节点指向父亲节点的边转方向，变为父亲节点指向儿子节点，注意，在这个过程中，幸运儿 A  和幸运儿 B 中间的那段不用管他。

所以上面的部分中我们花费了一个 n 的时间复杂度来枚举 A 点。

都操作完之后，我们得到了一个 sum ，表示目前已经花费的操作数。然后我们想一下，上图中 C 到 B 的这段。显然，这一段我们是希望他能从儿子指向父亲的，但是因为 A 是根节点，所以在刚才的大洗劫中，这二位之间的边都已经转了，所以我们对这一段的花费就是 $edgenum_1-edgenum_2$，其中 $edgenum_1$ 表示父亲指向儿子的边的数量， $edgenum_2$ 表示儿子指向父亲的边的数量。然后我们得到了答案的计算公式 $sum+edgenum_1-edgenum_2$。我们的题目是要求答案最小，所以我们想到了用 dp 来求解 $edgenum_1-edgenum_2$ 部分的最小值。

dp部分：如果 x 是 y 的父亲节点，那么，如果这二位之间的边是反着的，我们就要给 $dp_y+1$，然后不停的跟 $dp_x$ 取 min。

剩下的细节问题详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010;
int dp[N],ans,sum,tot,head[N],ver[N<<1],nxt[N<<1],edge_type[N<<1];
int n;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void add(int x,int y,int z)
{
	tot++;
	ver[tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	edge_type[tot]=z;
}
void DFS(int u,int fa)
{
	for(int i=head[u];i;i=nxt[i])
	{
		int v=ver[i];
		if(v==fa) continue;
		DFS(v,u);
		dp[u]=min(dp[v]+edge_type[i],dp[u]);
		if(edge_type[i]==-1) sum++;
	}
}
int main()
{
	n=read();
	ans=0x3f3f3f3f;
	for(int i=1;i<n;i++) 
	{
		int x=read(),y=read();
		add(x,y,1);
		add(y,x,-1);
	}
	for(int i=1;i<=n;i++)
	{
		memset(dp,0,sizeof(dp));
		sum=0;
		DFS(i,0);
		for(int j=1;j<=n;j++) ans=min(ans,dp[j]+sum);
	}
	cout<<ans<<endl;
	return 0;
}
```
谢谢观看！

---

## 作者：whiteqwq (赞：3)

[CF238C World Eater Brothers](https://www.luogu.com.cn/problem/CF238C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1772965)

## 题意
- 题意：给定一个$n$个点，$n-1$条边的有向树，求至少翻转多少条边的方向才能让入度为$0$的点数量不超过$2$。
- 数据范围：$1\leqslant n\leqslant 3000$。

## 分析
这道题题解说的有点不清楚，看了cf上的题解才搞懂这道题。

首先我们可以考虑只有一个入度为$0$的点的情况：直接枚举这个点，然后遍历一遍树就得到了答案，时间复杂度是$O(n^2)$的。

对于有两个入度为$0$的点的情况，我们不难发现这两个入度为$0$的点的路径一定是类似这样的：
```
1-->2-->3<--4<--5->...
|               |
v               v
...            ...
```

我们考虑枚举这两个点的路径上的中心点连接的边（如上图$3$连接的边$(2\rightarrow 3)$和$(4\rightarrow 3)$），也就是说**枚举一条边，在这条边分成的两个连通块中分别选择一个点作为入度为$0$的点**。

具体地，我们假装把这条边当做一个虚点作为根，并做一遍遍历得到以这个虚点为根的答案。

我们根据上图可得两个入度为$0$的点到虚点的路径会反向（虚点代表的边方向不改变），因此我们在遍历的时候在两个连通块里分别选取到达虚点的路径上**需要反向的边数量减不需要反向的边的数量最小**的点就好了。

时间复杂度：$O(n^2)$。

## 代码
```
#include<stdio.h>
#define inf 1000000000
const int maxn=3005,maxm=maxn<<1;
int n,e,ans,minn;
int start[maxn],to[maxm],then[maxm],worth[maxm],f[maxn],tot[maxn],xx[maxm],yy[maxm];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int max(int a,int b){
	return a>b? a:b;
}
inline void add(int x,int y,int z){
	then[++e]=start[x],start[x]=e,to[e]=y,worth[e]=z;
}
void dfs(int x,int last){
	minn=min(minn,tot[x]);
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		tot[y]=tot[x]+(worth[i]==0? -1:1);
		dfs(y,x);
		f[x]+=f[y]+(worth[i]^1);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,1),add(y,x,0);
	}
	ans=n-1;
	for(int i=1;i<=n;i++)
		for(int j=start[i];j;j=then[j])
			if(worth[j]==1){
				int k=to[j],sum=0;
				for(int p=1;p<=n;p++)
					f[p]=tot[p]=0;
				dfs(i,0),ans=min(ans,f[i]);
				for(int p=1;p<=n;p++)
					f[p]=tot[p]=0;
				minn=inf,dfs(i,k);
				sum+=f[i]+minn;
				for(int p=1;p<=n;p++)
					f[p]=tot[p]=0;
				minn=inf,dfs(k,i);
				sum+=f[k]+minn;
				ans=min(ans,sum);
			}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：1saunoya (赞：3)

一定是两个连通块然后我们遍历两个连通块，令 $f_u$ 为 $u$ 能到达所有点的代价，然后这个是一个固定的东西，$u$ 可以到子树的所有点，那么我们把这一条路径的权值算出来比如说是 $u \to x$。


然后找到最小的那一条，就做完了。

另外一个连通块同理，记得判断 (n=1)。

---

## 作者：ModestCoder_ (赞：2)

大意是改变最少的边的方向使得选两个点，能遍历完整棵树

考虑枚举两个起点。

对于一个起点，用树形dp计算出$dp_u$表示以$u$为根的子树的答案

然后若以$u$作为真正的起点，那么答案就是$dp_u$

如果选择$u$子树中的某个点$v$作为起点，那么答案是

$dp_u-(u->v反向的边)+(u->v正向的边)$

发现所以维护$-(u->v反向的边)+(u->v正向的边)$的最小值，加上$dp_u$就是答案

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 3010
using namespace std;
struct Edge{
	int to, next, len;
}edge[maxn << 1];
int num, head[maxn], dp[maxn], Min, n;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y, int z){ edge[++num] = (Edge){y, head[x], z}, head[x] = num; }

void dfs(int u, int pre, int val){
	dp[u] = 0;
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to, l = edge[i].len;
		if (v != pre){
			dfs(v, u, val + l);
			dp[u] += dp[v] + (l != 1);
		}
	}
	Min = min(Min, val);
}

int main(){
	n = read();
	if (n == 1) return puts("0"), 0;
	for (int i = 1; i < n; ++i){
		int x = read(), y = read();
		addedge(x, y, 1), addedge(y, x, -1);
	}
	int ans = 1e9;
	for (int u = 1; u <= n; ++u)
		for (int i = head[u]; i; i = edge[i].next)
			if (edge[i].len == 1){
				int v = edge[i].to, tmp;
				Min = 1e9;
				dfs(u, v, 0);
				tmp = dp[u] + Min;
				Min = 1e9;
				dfs(v, u, 0);
				tmp += dp[v] + Min;
				ans = min(ans, tmp);
			}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：王熙文 (赞：1)

## 题解

首先，我们需要转化一下题意：求最少翻转边的次数，使得在树上可以从两个起点遍历到所有点。

为什么呢？可以把两个起点当成入度为 $0$ 的点，那么如果它们遍历不了整棵树，说明一定至少有一个点没法进去（入度为 $0$），如果能遍历整棵树，那么每个节点都是从这两个地方进去的，入度至少为 $1$。

那么，如果使答案最少，这两个点一定是各管一边，被一条边分开的。

因为如果一个点（设为 $x$）“侵犯”了另一个点（设为 $y$）的地方，如果只进到了一个点（设为 $z$），那么那个点的子树（除了 $y$ 所在的子树）谁来遍历呢？如果还是 $x$ 来遍历，那会在 $z$ 与 $y$ 所在的子树的根节点的边分开的情况出现，否则，如果是 $y$ 遍历，那 $y$ 就得访问到 $z$，这时 $x$ 遍历到 $z$ 产生的代价就没有意义了。

所以，我们枚举分割的边，然后对于这两部分都跑一个换根 dp，求出从哪个点开始遍历需要翻转的边最少，加起来就好了。

那么，如何求出来这个值呢？其实这个问题就是 CF219D，但我还会讲一下具体如何实现。

首先，设 $dp_i$ 表示 $i$ 遍历它的子树需要翻转的边。显然，它遍历子树就需要走到它的子节点，那么答案即为对于每一个子节点，是否要翻转 $i$ 到子节点的边加上子节点遍历它的子树的答案。

接下来考虑对于一个点，遍历整个树需要翻转的边。对于每一个节点 $i$，如果它不是根节点（根节点上面已经求好了），那它与父亲的答案之差只有是否翻转它到父亲的边。即如果父亲能到儿子，那么儿子的答案就得加上翻转这条边的代价（其实就是 $1$），否则，儿子的答案就得减去翻转这条边的代价（因为之前父亲到儿子需要翻转，但儿子到父亲不用翻转）。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int tot=0,var[6010],len[6010],nxt[6010],head[3010];

void add(int u,int v,int w)
{
	var[++tot]=v;
	len[tot]=w;
	nxt[tot]=head[u];
	head[u]=tot;
}

int dp[3010];

void dfs1(int u,int fa,int avoid) // 第一次 dfs，求子树里
{
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fa || v==avoid) continue;
		dfs1(v,u,avoid);
		dp[u]+=dp[v]+len[i];
	}
}

int in;

void dfs2(int u,int fa,int avoid) // 第二次 dfs，换根
{
	in=min(in,dp[u]);
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fa || v==avoid) continue;
		dp[v]=(len[i]?-1:1)+dp[u];
		dfs2(v,u,avoid);
	}
}

int main()
{
	int n,u,v,ans=1e9;
	scanf("%d",&n);
	if(n==1) return printf("0"),0;
	for(int i=1; i<n; ++i)
	{
		scanf("%d%d",&u,&v);
		add(u,v,0),add(v,u,1);
	}
	for(int i=1; i<n; ++i) // 枚举边
	{
		u=var[i*2],v=var[i*2-1];
		memset(dp,0,sizeof(dp));
		dfs1(u,0,v);
		in=1e9;
		dfs2(u,0,v);
		int now=in;
		dfs1(v,0,u);
		in=1e9;
		dfs2(v,0,u);
		now+=in;
		ans=min(ans,now);
	}
	printf("%d",ans);
	return 0;
}
```



---

