# Infected Tree

## 题目描述

Byteland is a beautiful land known because of its beautiful trees.

Misha has found a binary tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . A binary tree is an acyclic connected bidirectional graph containing $ n $ vertices and $ n - 1 $ edges. Each vertex has a degree at most $ 3 $ , whereas the root is the vertex with the number $ 1 $ and it has a degree at most $ 2 $ .

Unfortunately, the root got infected.

The following process happens $ n $ times:

- Misha either chooses a non-infected (and not deleted) vertex and deletes it with all edges which have an end in this vertex or just does nothing.
- Then, the infection spreads to each vertex that is connected by an edge to an already infected vertex (all already infected vertices remain infected).

As Misha does not have much time to think, please tell him what is the maximum number of vertices he can save from the infection (note that deleted vertices are not counted as saved).

## 说明/提示

In the first test case, the only possible action is to delete vertex $ 2 $ , after which we save $ 0 $ vertices in total.

In the second test case, if we delete vertex $ 2 $ , we can save vertices $ 3 $ and $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1689C/1f479df0f6df9637a1dfee43da055c650bdae647.png)

## 样例 #1

### 输入

```
4
2
1 2
4
1 2
2 3
2 4
7
1 2
1 5
2 3
2 4
5 6
5 7
15
1 2
2 3
3 4
4 5
4 6
3 7
2 8
1 9
9 10
9 11
10 12
10 13
11 14
11 15```

### 输出

```
0
2
2
10```

# 题解

## 作者：冬天的雨 (赞：20)

这是个动态规划啊……

还是一个比较基础的树形动规。

当然赛时我差点写了一个树链剖分，然后突然发现是一棵二叉树……

可惜同机房的 @artalter 大佬和 @Sakura_Lu 大佬没有注意惨遭爆零。

言归正传，我们当然想尽可能多的保留节点，而且每一次肯定是删除被病毒感染的节点的某个子节点。

而删除之后我们的问题就可以转化为它的另一个儿子（注意为**二叉树**）的根被感染病毒能保留多少节点的子问题，

那么很明显可以考虑一下动规。

它的状态也很简单：$dp[i]$ 表示在以 $i$ 为根的子树中，若 $i$ 被感染病毒，最多能保留多少节点。

那么考虑如何转移，很明显我们考虑删掉 $i$ 的哪一个子节点即可。

我们就首先来分别考虑究竟删除哪一个子节点。

假设删除 $lson$，那么相当于在 $lson$ 的子树里我们可以保留下 $size[lson]-1$ 个节点，$size[i]$ 代表以 $i$ 为根的子树的大小（包含节点 $i$），

而在 $rson$ 的子树里，我们依旧可以保留下 $dp[rson]$ 个节点，所以最终的状态转移方程就是：

$dp[i]=\operatorname{max}(dp[lson]+size[rson]-1,dp[rson]+size[lson]-1)$

需要注意可能子树为空，那么 $size[son]-1$ 就是一个负数，所以需要对 $0$ 取 $\operatorname{max}$。

为避免这种情况，我们要先进行 dfs 再更新 $size$ 和 $dp$ 数组。

以及多组数据所以每次需要将各种数组清零，清零 $head$ 数组也相当于清零边，小小地卡一点常数。

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define int long long
#define WR WinterRain
using namespace std;
const int WR=1001000,mod=1e9+7;
struct Edge{
    int pre,to;
}edge[WR];
int t;
int n,sze[WR];
int head[WR],tot;
int dp[WR];
int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=(s<<3)+(s<<1)+ch-48;
        ch=getchar();
    }
    return s*w;
}
void add(int u,int v){
    edge[++tot].pre=head[u];
    edge[tot].to=v;
    head[u]=tot;
}
void dfs(int u,int root){
    sze[u]=1,dp[u]=0;//dp数组存储如果我被感染了能活多少个
    int sum=0;
    for(int i=head[u];i;i=edge[i].pre){
        int v=edge[i].to;
        if(v!=root){
            dfs(v,u);
            sum+=dp[v];
            sze[u]+=sze[v];
        }
    }
    for(int i=head[u];i;i=edge[i].pre){
        int v=edge[i].to;
        if(v!=root){
            dp[u]=max(dp[u],sum-dp[v]+sze[v]-1);
        }
    }
}
signed main(){
    t=read();
    while(t--){
        n=read();
        tot=0;
        for(int i=1;i<=n;i++) head[i]=0;
        for(int i=1;i<n;i++){
            int u=read(),v=read();
            add(u,v);
            add(v,u);
        }
        dfs(1,0);
        printf("%lld\n",dp[1]);
    }
    return 0;
}
```


---

## 作者：artalter (赞：11)

# CF1689C Infected Tree 题解
## 1.做法
首先，这是一颗二叉树。

然而，（可能楼上冬天的雨先生说了），我没有注意到，试图寻找一个适用于多叉树的做法，惨遭爆零。

我的做法极其简单：

我们强制在能删除的时候一定删除，那么在最优解中病毒能感染的节点一定构成了一条从根节点出发的链，并且这条链的末端是叶子节点或是只有一个孩子（这样就可以把他的唯一一个孩子堵住）的节点。

如果是叶子节点，被删除的节点数为这个节点的深度 $s1=dep-1$。

如果是只有一个孩子的节点，被删除的节点数为 $s1=dep$。

病毒能感染的节点数为 $s2=dep$。

我们要找的就是 $n-(s1+s2)$ 的最大值。

## 2.代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 300005;
struct edge
{
	int v,nxt;
}e[maxn*2];
int head[maxn],cnt,ans,dep;
int n;
void add(int u,int v)
{
	cnt++;
	e[cnt]=edge{v,head[u]};
	head[u]=cnt;
}
void dfs1(int u,int fa,int d)
{
	int x=0;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs1(v,u,d+1);
		x++;
	}
	if(x==1)
	{
		ans=max(ans,n-2*d);
	}else if(x==0)
	{
		ans=max(ans,n-2*d+1);
	}
}
int main()
{
	int T;
	cin>>T;
	while(T-->0)
	{
		scanf("%d",&n);
		for(int i=1;i<=n-1;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
		}
		dfs1(1,0,1);
		printf("%d\n",ans);
		memset(head,0,sizeof(head));
		memset(e,0,sizeof(e));
		cnt=ans=dep=0;
	}
	
	return 0;
}
```

---

## 作者：sutong2009 (赞：4)

# CF1689C Infected Tree 题解
~~怎么只有我这个蒟蒻不会 DP 啊。~~
#### 回归正题……

# 简化题意
给定一棵以 $1$ 号节点为根的二叉树，总节点个数为 $n$。现在 $1$ 号节点感染了病毒，你在这一回合里可以使病毒所在节点的一个儿子不被感染，而病毒会感染一个不受保护的儿子。

询问最多可以有多少不被病毒感染且不被保护的点。

# 思路整理

这是**二叉树!!!**

由于我们要求最多**不被感染且不被保护**的点，可以贪心地想：想要答案最大，不就是病毒行走**路径最短**吗？

DP 来干嘛？DFS 就完事了嘛!

设置变量 $ans$，表示被保护的点和被感染的点的总和；设当前节点儿子数量为 $D$。

如果 $D = 0$，说明病毒**已经无法继续感染**了，那么 $ans = \max(ans, now)$。

如果 $D = 1$，说明只要**保护子节点**，病毒**将无法继续感染**了，那么 $ans = \max(ans, now)$。

如果 $D = 2$，说明防疫工作仍然漫长，那么**继续向下搜索**。

最终答案就是 $n - ans$。
# 核心代码：
```cpp
void dfs(int fa, int root, int now){
	if(G[root].size() == 1){
		if(now < ans)ans = now;//病毒感染到树顶
		return ;
	}
	if(G[root].size() == 2){
		if(now + 1 < ans)ans = now + 1//只有一个儿子, 赶紧保护;
		return ;
	}
	for(int i = 0; i < G[root].size(); i++){
		if(G[root][i] == fa)continue;
		dfs(root, G[root][i], now + 2); // now + 2是因为你要保护一个儿子，而病毒会感染一个孩子
	}
}
```
代码运行很成功，没有花里胡哨的优化，但是当时是最优解。
###### ~~求赞~~

---

## 作者：Special_Tony (赞：2)

# 思路
这题的舍取我们可以分情况考虑：
1. $x$ 是叶子结点，删不删无所谓，都是 $0$；
1. $x$ 有一个儿子，果断删，保全它的所有子节点，共 $s_x-1$ 个（其中 $s_x$ 表示以 $x$ 为根的子树下的节点个数）；
1. $x$ 有两个儿子，只能舍一个保一个，保左儿子和保右儿子取个 $\max$ 就行。舍的部分继续递归。

# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, x, y, s[300005];
vector <int> v[300005];
int sum (int x, int f) {
	if (s[x])
		return s[x];
	s[x] = 1;
	for (int i : v[x])
		if (i != f)
			s[x] += sum (i, x);
	return s[x];
}
int fun (int x, int f) {
	int l = 0, r = 0;
	for (int i : v[x])
		if (i != f)
			if (l)
				r = i;
			else
				l = i;
	if (r)
		return max (fun (l, x) + sum (r, x), sum (l, x) + fun (r, x)) - 1;
	if (l)
		return sum (l, x) - 1;
	return 0;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			v[i].clear (), s[i] = 0;
		while (-- n)
			cin >> x >> y, v[x].push_back (y), v[y].push_back (x);
		cout << fun (1, 0) << '\n';
	}
	return 0;
}
```

---

## 作者：qzhwlzy (赞：2)

## [原题](http://codeforces.com/problemset/problem/1689/C)

### 大意

有一棵以 $1$ 为根、有 $n$ 个节点的二叉树。树根现在遭受了感染，在之后的每一秒钟，你能够去除树的一个节点，之后感染的节点向未感染的相邻节点传染。求能够保住的节点数的最大值（显然去除的节点不算保住）。

![](https://cdn.luogu.com.cn/upload/image_hosting/p7eusdve.png)

### 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/jh1ay3ce.png)

如图，当一个节点被感染时，我们若想去除其某棵子树里的点时，一定是去除与其直接相连的点更优。因为去除发生在感染之前，若去除不直接相连的点会让直接相连的点被感染，多损失了一个点。

之后，我们考虑到使用树形 DP 求解。令 $f_i$ 为 $i$ 被感染时，以 $i$ 为根的子树中最多能够保住多少个点。答案就是 $f_1$。

接下来是转移方程：
因为是二叉树，那么一个点被感染后，接下来去除的点一定是其左右儿子 $son_l$ 和 $son_r$ 之一。当去除一个儿子之后，以该儿子为根的子树中的点（除了去除的儿子）全部存活，另一个儿子接下来被感染，问题转化为了被感染的儿子的那棵子树能够存活多少，成了原问题的子问题。那么，就能得到：$f_i = \max(f_{son[l]} + size_{son[r]} - 1 , f_{son[r]} + size_{son[l]} - 1)$，其中 $size$ 存子树大小，要减 $1$ 是因为我们去除的那个点不算存活。

**数组要开够！**

### 代码

```cpp
#include<iostream>
#include<cstdio>
#define maxn 300005
using namespace std;
int T,n,u,v; int f[maxn],size[maxn]; struct node{int to,nex;}a[maxn*2]; int head[maxn],tot=0;
void add(int from,int to){a[++tot].to=to;a[tot].nex=head[from];head[from]=tot;}
void set(){tot=0; for(int i=1;i<=n;i++){head[i]=0;f[i]=0;size[i]=0;}}
void dfs(int p,int fa){
	size[p]=1; int res=0;
	for(int i=head[p];i;i=a[i].nex) if(a[i].to!=fa){dfs(a[i].to,p);size[p]+=size[a[i].to];res+=f[a[i].to];}
	//res 存两个儿子的 f 值之和,以便快速求出另一个儿子的 f 值 
	for(int i=head[p];i;i=a[i].nex) if(a[i].to!=fa) f[p]=max(f[p],(res-f[a[i].to])+(size[a[i].to]-1));
	//假设要去除 a[i].to 这个儿子 
}
int main(){
	scanf("%d",&T);
	while(T--){
		set(); scanf("%d",&n); for(int i=1;i<n;i++){scanf("%d%d",&u,&v); add(u,v); add(v,u);}
		dfs(1,0); printf("%d\n",f[1]);
	}
	return 0;
}
```

---

## 作者：sLMxf (赞：1)

题意就不说了。

病毒走的路线其实是我们人为控制的，因为这是一颗二叉树。

定义 $s_i$ 表示儿子个数，$lt$ 表示左儿子，$tr$ 表示右儿子，$S_i$ 表示子树大小，$dp_i$ 表示以 $i$ 为根的最优解，其中 $i$ 已经被感染。
## $s_i=0$
显然的，$dp_i=0$。
## $s_i=1$
显然的，$dp_i=S_i-2$，因为根被感染、儿子被封锁。
## $s_i=2$
要么封锁左子树，要么封锁~~柚~~右子树。

就有 $dp_i=\max(dp_{lt}+S_{rt}-1,dp_{rt}+S_{lt}-1)$

最终的答案就是 $dp_1$。

---

## 作者：linyihdfj (赞：1)

## C. Infected Tree ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16366229.html)
#### 题目描述 ####
[原题面](https://codeforces.com/problemset/problem/1689/C)

给定一棵以 $1$ 号节点为根的二叉树，现在 $1$ 号节点感染了病毒，病毒每一回合都会去感染与该节点直接相连的节点，而你在这一回合里可以选择删除任意一个没有被病毒感染的点，这样就断开了它与其直接相连的点得关系，询问最多可以有多少不被病毒感染的点，被删除的点不算做不被病毒感染的点。
#### 题目分析 ####
我们考虑为了尽可能多的保留节点，我们每一次肯定是会删除被病毒感染的节点的某个子节点，而删除之后我们的问题就可以转化为它的另一个儿子（注意为二叉树）根被感染病毒能保留多少节点的子问题，那么这很明显就可以考虑一下 $DP$。$DP$ 状态也很简单：$dp[i]$ 表示以 $i$ 为根的子树若 $i$ 被感染病毒，最多能保留多少节点。

那么下面就是考虑转移了，转移很明显就是我们考虑删除哪一个 $i$ 的子节点就好了，因为是二叉树所以不用考虑更多的情况。那么我们就分别考虑究竟删除哪一个子节点，假设删除 $son_1$，那么相当于在 $son_1$ 的子树里我们可以保留下 $size[son_1] - 1$ 个节点，$size[i]$ 代表以 $i$ 为根的子树的大小（包含节点 $i$），而在 $son_2$ 的子树里，我们依旧可以保留下 $dp[son_2]$ 个节点，所以最终的状态就是：
$$
dp[i] = \max(dp[son_1] + size[son_2] - 1,dp[son_2] + size[son_1] - 1)
$$
需要注意可能该子树为空，那么 $size[son] - 1$ 就是一个负数，所以需要对 $0$ 取 $\max$，避免这种情况。
#### 代码详解 ####

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
struct edge{
	int nxt,to;
	edge(){}
	edge(int _nxt,int _to){
		nxt = _nxt,to = _to;
	}
}e[2 * MAXN];
int ans = 0,cnt,head[MAXN],dp[MAXN],sz[MAXN];
//dp[now] 表示以 now 为根的子树，假设 now 被感染，最多保留多少个 
void add_edge(int from,int to){
	e[++cnt] = edge(head[from],to);
	head[from] = cnt;
}
void dfs(int now,int fa){
	sz[now] = 1;
	int son[3] = {0,0,0};
	int tot = 0;
	for(int i=head[now]; i;i = e[i].nxt){
		int to = e[i].to;
		if(to == fa)	continue;
		son[++tot] = to;
		dfs(to,now);
		sz[now] += sz[to];
	}
	//去 son[1] / 去 son[2] 
	dp[now] = max(dp[son[1]] + max(sz[son[2]] - 1,0),dp[son[2]] + max(sz[son[1]] - 1,0));
}
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(head,0,sizeof(head));
		memset(dp,0,sizeof(dp));
		memset(sz,0,sizeof(sz));
		ans = 0;
		int n;
		cin>>n;
		for(int i=1; i<n; i++){
			int from,to;
			cin>>from>>to;
			add_edge(from,to);
			add_edge(to,from);
		}
		dfs(1,0);
		printf("%d\n",dp[1]);
	}
	return 0;
}

```


先进行 $dfs$ 再更新 $sz$ 和 $dp$，以及多组数据所以每次需要将各种数组清零，清零 $head$ 数组也相当于清零边的数组了。

---

## 作者：KukCair (赞：1)

树形 DP。

$size_v$ 为以 $v$ 为根的子树大小。

设 $dp_x$ 为 $x$ 被感染时其子树能留下几个点。

对于一个被感染的点 $x$ 的孩子的点 $v$（未被感染），作如下考虑：

- 删除 $v$，则它的子树全部都得以保存。$dp_x$ 不能加上 $dp_v$，但可以加上 $size_v-1$（$v$ 本身不能算）。

- 不删除它，$dp_x$ 直接加上 $dp_v$。

这样，对于每个 $x$，枚举删除哪个孩子即可。

又因为原图是一颗二叉树，可以记一个 $sum$ 为 $x$ 所有孩子的 $dp$ 值之和，以快速求出另一个子树的 $dp$ 值。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int t, n, sz[300005], dp[300005];
vector<int> vc[300005];
int dfs(int x, int fa){
	sz[x] = 1;
	dp[x] = 0;
	int sum = 0;
	for(int i = 0; i < vc[x].size(); i++){
		int v = vc[x][i];
		if(v == fa) continue;
		sz[x] += dfs(v, x);
		sum += dp[v];
	}
	for(int i = 0; i < vc[x].size(); i++){
		int v = vc[x][i];
		if(v == fa) continue;
		dp[x] = max(sum - dp[v] + sz[v] - 1, dp[x]);
	}
	return sz[x];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++) vc[i].clear();
		for(int i = 1; i <= n - 1; i++){
			int a, b;
			cin >> a >> b;
			vc[a].push_back(b);
			vc[b].push_back(a);
		}
		dfs(1, 0);
		cout << dp[1] << '\n';
	}
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## CF1689C Infected Tree 题解
### Solution
树形动态规划。

令 $f_i$ 表示以 $i$ 为根节点的子树中，若 $i$ 节点被感染，能够有多少节点不被感染。

首先需要通过 dfs 计算出 $sz_i$，即以 $i$ 为根节点的子树大小（包含根节点）。

因为是二叉树，所以我们只需要考虑两个子节点。
- 若选择断开左子节点，则左子树会有 $sz_{lson}-1$ 个节点可以免受感染；右子树会有 $f_{rson}$ 个节点不被感染。
- 同理，断开右子节点，会有 $sz_{rson}-1+f_{lson}$ 个节点不受感染。

综上，得出公式 $f_i=\max\{dp_{lson}+sz_{rson}-1,dp_{rson}+sz_{lson}-1\}$。

### [Accepted Code](https://codeforces.com/problemset/submission/1689/304546458)
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#define pb push_back
#define ll long long
using namespace std;
const int N=3e5+10;
vector<int>G[N];
int dp[N],siz[N],T,n,u,v;
void dfs(int x,int fa){
	siz[x]=1;
	dp[x]=0;
	int tmp=0;
	for(auto i:G[x]){
		if(i==fa) continue;
		dfs(i,x);
		siz[x]+=siz[i];
		tmp+=dp[i];//dp[左子树]和dp[右子树]之和 
	}
	for(auto i:G[x]){
		if(i==fa) continue;
		dp[x]=max(dp[x],(tmp-dp[i])+siz[i]-1);
	}
	return;
}
int main(){
	scanf("%d",&T);
	for(;T;T--){
		scanf("%d",&n);
		for(int i=1;i<n;i++){
			scanf("%d%d",&u,&v);
			G[u].pb(v);
			G[v].pb(u);
		}
		dfs(1,0);
		printf("%d\n",dp[1]);
		for(int i=1;i<=n;i++) G[i].clear();
		memset(siz,0,sizeof(siz));
		memset(dp,0,sizeof(dp));
	}
	return 0;
}
```

---

## 作者：legend_cn (赞：0)

# 1.0 解题思路
这是一道树形 $DP$。

我们的目的解释尽可能多的保留节点，每一次删除被感染了的节点的某一个儿子。删除之后问题就可以转化为它一个没有被删除的那个儿子的根被感染病毒能保留多少节点的子问题。

### 1.1 状态
$dp(i)$ 表示在以 $i$ 为根的子树中，若 $i$ 这个根被感染病毒，最多能保留多少节点。

现在我们只需要考虑删掉 $i$ 的左儿子还是右儿子就可以了。

假设删除 $lc$，那么相当于在 $lc$ 的子树里我们可以保留下 $sz(lc)-1$ 个节点。$sz$ 表示以 $i$ 为根节点，它的子树的大小（包括了根节点）。

而在 $rc$ 的子树里，我们依旧可以保留下 $dp(rc)$ 个节点。

### 1.2状态转移方程
$$dp(i)=\max \left (dp(lc)+sz(rc)-1,dp(rc)+sz(lc)-1\right )$$

### 1.3特殊情况
当子树为空，那么他保留的节点就是负数。

为避免这种情况，我们要先使用 $dfs$ 再更新 $sz$ 和 $dp$ 数组。

### 1.4坑点
因为本题是多组数据，所以每次需要将各种数组清零。

# 2.0 AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int vtx,nxt;
}e[1000005];
int sz[1000005];
int h[1000005],idx;
int dp[1000005];
void add(int u,int v)
{
	e[idx].vtx=v;
	e[idx].nxt=h[u];
	h[u]=idx++;
}
void dfs(int u,int rt)
{
	sz[u]=1;
	dp[u]=0;
	int sum=0;
	for(int i=h[u];~i;i=e[i].nxt)
	{
		int v=e[i].vtx;
		if(v!=rt)
		{
			dfs(v,u);
			sum+=dp[v];
			sz[u]+=sz[v];
		}
	}
	for(int i=h[u];~i;i=e[i].nxt)
	{
		int v=e[i].vtx;
		if(v!=rt)
			dp[u]=max(dp[u],sum-dp[v]+sz[v]-1);
	}
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(h,-1,sizeof h);
		int n;
		cin>>n;
		idx=1;
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		dfs(1,0);
		cout<<dp[1]<<endl;
	}
	return 0;
}
```


---

