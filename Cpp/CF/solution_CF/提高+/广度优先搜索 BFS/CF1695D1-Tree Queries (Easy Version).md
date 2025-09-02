# Tree Queries (Easy Version)

## 题目描述

此问题与[CF1695D2 Tree Queries (Hard Version)](https://www.luogu.com.cn/problem/CF1695D2)的唯一区别是树的大小的限定。

给定一棵无根树，有 $ n $ 个顶点。在这棵树上有一个顶点 $ x $ ,你希望找到它。

要找到 $ x $ ，你可以进行 $ k $ 次查询 $ v_1 , v_2 ，\ldots , v_k $ (其中 $ v_i $ 是树中的各个顶点)。当你进行完所有查询后，你会得到 $ k $ 个数字 $ d_1 , d_2 ，\ldots , d_k $ ，( $ d_i $ 是 $ v_i $ 和 $ x $ 之间的最短路径上的边数)。注意，您知道哪个距离对应于哪个查询。

请你求出最小的 $ k $ ，使存在这样的一些查询 $ v_1 , v_2 ，\ldots , v_k $ ，让你总能找到唯一的一个节点 $ x $ (无论 $ x $ 是什么)。

注意，你不需要输出这些查询。

## 说明/提示

在第一组数据中，只有一个顶点，因此不需要任何查询。

在第二组数据中，你可以进行关于节点 $ 1 $ 的单个查询从而得到 $ x $ 节点的信息。

## 样例 #1

### 输入

```
3
1
2
1 2
10
2 4
2 1
5 7
3 10
8 6
6 1
1 3
4 7
9 6```

### 输出

```
0
1
2```

# 题解

## 作者：王熙文 (赞：5)

为什么 D1 的题解全是可以通过 D2 的做法？这篇题解是只能通过 D1 的做法。

## 思路

考虑钦定一个点 $r$ 必选，将 $r$ 设为树根。为什么要这么做？因为一个点子树外的点以及当前点对这棵子树没有意义，它们的效果和 $r$ 一样。

考虑 dp，设 $dp_u$ 表示区分 $u$ 的子树内所有点的最小点数。对于 $u$ 的一个儿子 $v$，首先要区分 $v$ 子树内，至少要有 $dp_v$ 的代价。儿子之间也需要区分。注意到如果两个儿子其中的一个子树内有选的点，则可以区分这两个儿子。因此如果 $dp_v \not=0$，则 $v$ 的子树内的所有点就一定确定了。那么对于剩下 $dp_v=0$ 的儿子，需要在其中选个数减一个儿子在子树内放一个点。

综上，转移是 $dp_u=\sum_v  dp_v + \max(\sum_v [dp_v=0]-1,0)$。

答案是 $dp_r+1$ 的最小值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; vector<int> e[200010];
int dp[200010];
void dfs(int u,int fa)
{
	dp[u]=0;
	int cnt=0;
	for(int v:e[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		dp[u]+=dp[v],cnt+=(dp[v]==0);
	}
	dp[u]+=max(cnt-1,0);
}
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n;
		for(int i=1; i<=n; ++i) e[i].clear();
		for(int i=1; i<=n-1; ++i)
		{
			int u,v; cin>>u>>v;
			e[u].push_back(v),e[v].push_back(u);
		}
		if(n==1) { cout<<0<<'\n'; continue; }
		int in=1e9;
		for(int i=1; i<=n; ++i) dfs(i,0),in=min(in,dp[i]+1);
		cout<<in<<'\n';
	}
	return 0;
}
```

---

## 作者：Sellaris (赞：3)

- 首先，将原问题抽象为另一个等价命题：
	
	在一颗无根树上选择 $k$ 个点。树上每个点到这 $k$ 个点的距离构成一个 $k$ 维向量。求得最小的 $k$ 使得每个向量都不相同。
    
- 于是考虑坐标会相同的的情况，以某点为根，有两棵子树没有选择的点的时候向量会相同。于是从原树中的所有度为 $1$ 的点往上走，给度数 $2$ 大的点打标记。又因为有一颗子树可以不选择，所以把叶子数减去有标记的点就是答案了。线性复杂度。

- 记得把链判掉。

- 代码：

```cpp
//#pragma once
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define ll long long
using namespace std;
//using namespace __gnu_pbds;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
const int maxn=1e5+10;
int n,ans;
vector<int> vec[maxn<<1];
bool vis[maxn];
 
int dfs(int u,int fa){
    if(vec[u].size()>2) return u;
    for(auto v:vec[u]) if(v!=fa) return dfs(v,u);
    return u;
}
 
inline void solve(){
    n=read();ans=0;
    for(int i=1;i<=n;i++) vec[i].clear(),vis[i]=0;
    if(n==1) {
    	puts("0");return;
	}
    for(int i=1,u,v;i<n;i++)
        u=read(),v=read(),vec[u].push_back(v),vec[v].push_back(u);
    for(int i=1;i<=n;i++)
        if(vec[i].size()==1) vis[dfs(i,0)]=true,ans++;
    for(int i=1;i<=n;i++) if(vis[i]) ans--;
    if(ans==0) puts("1");
	else printf("%d\n",ans);
}
int main(){
	int t=read();
	while(t--){
		solve();
	}
	return 0;
}
```





---

## 作者：BqtMtsZDnlpsT (赞：0)

分享一个做法。


------------

题意：

给你一棵树，你可以询问一些点 $v_1,\dots,v_k$（仅一次），你可以获得它们到一个神秘节点的距离 $d_1,\dots,d_k$。

问至少询问多少个节点，可以在神秘节点是任意节点时，将其推断出来。


------------

以下 $d_i$ 表示神秘节点到 $i$ 的距离。

首先我们考虑选了两个点可以知道那些信息：

[![XXaj54.png](https://s1.ax1x.com/2022/06/19/XXaj54.png)](https://imgtu.com/i/XXaj54)

假设我们当前选了 $7,9$ 两个点，如果 $d_7+d_9=dis(7,9)$（$dis(x,y)$ 表示 $x,y$ 间的最短距离），那么这个点可以被唯一确定（如上图若 $d_7=3,d_9=2$，那么神秘节点一定是 $1$）。

那么如果 $d_7+d_9>dis(7,9)$（显然 $d_7+d_9\ge dis(7,9)$），可以考虑把这两点路径上每一个点附带部分分成一组（看图，蓝圈代表一组），若神秘点在某个组内，那么 $7,9$ 都是先走到该组内的红色节点（$7,9$ 路径上的点），再从红色点往下走。可以发现 $7,9$ 在神秘点所在组内走的路径都是相同的，即红色点到神秘点的最短路径。

所以，

我们可以通过不断将 $d_7,d_9$ 分别减 $1$，直到 $d_7+d_9=dis(7,9)$ 来确定红色点；

再通过减了几次 $1$ 来确定：这组内以红色节点为根的树，神秘节点的深度。

如上图若 $d_7=5,d_9=4$，那么我们先化为 $d_7=3+2,d_9=2+2$，确定红色点是 $1$，并且神秘点的深度为 $2$，因为在 $\{1,3,10\}$ 内，深度为 $2$ 的节点只有 $10$，所以神秘点是 $10$。

若我们已经选了两个点，那么什么情况下不能问出全部神秘节点？
我们发现，这两个点确定了这条路径上所有点，因此我们可以将这条路径上的所有边看做“虚化”了，一条边虚化后，不计入度数。若此时有一个点度数 $\ge3$，神秘节点若在这个点的子树内，则有可能无法唯一确定。

[![XXL3v9.png](https://s1.ax1x.com/2022/06/19/XXL3v9.png)](https://imgtu.com/i/XXL3v9)


如图，如果我们仅仅是知道了走到红色节点 $1$ 并且深度为 $2$，那么有可能是 $8,9$ 中的任意一个。

利用虚化的思想拓广：三个点时会怎么样，仔细思考后就会发现，虚化的边集即为三个点两两间路径边集的并，也就是说，把三个点两两间路径上的边全部虚化。

在虚化过程中，选择度为 $2$ 的点，一定不如选择其连接至的度为非 $2$ 的节点。否则不是选了没用，就是两边都得选别的点，但是两边都得选，不就覆盖其本身了吗？**所以度为 $2$ 的点可以直接删除，并不影响结果**（不影响别的点的度数）。

具体的，对于一个度为 $2$ 的点，我们直接将其连到的两个点连边，并删除其。

删完度为 $2$ 的点后，场上还剩下这些东西：一些度 $\ge3$ 的节点，构成一个树形结构（称之为新树），每个点上带了一些度为一的点（称为附属点）。接下来我们要选点，使得所有度 $\ge3$ 的点变小。

贪心选择，选择新树上所有度为 $1$ 的点中的一个附属点，这样就可以把整个新树边全部虚化并且花费最小。若连非附属点，则比连附属点少虚化一条边。若连度非 $1$ 的节点，则度为 $1$ 的还要单独处理，至少不劣。

至于最后剩下的附属点，那只能暴力选了，注意可以留一个不选。

复杂度 $O(n\log n)$

代码：

```cpp
//赛时的，由于一些原因可能有一些神秘操作
//其实不是赛时的，赛时的代码由于两个小问题 wa on 2了
int n,m,d[200005],vis[200005];
set<int>E[200005]; 
inline void work(){
	for(int i=1;i<=n;i++){
		E[i]=set<int>();
		d[i]=vis[i]=0;
	}
	n=read();
	if(n==1)return pus("0"); 
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		E[x].insert(y);E[y].insert(x);
	}
	if(n==2)return pus("1");
	for(int i=1;i<=n;i++){
		if(E[i].size()==2){//删度为 2 的点
			int u=*E[i].begin(),v=*--E[i].end();
			vis[i]=1;
			E[u].erase(i);E[v].erase(i);
			E[u].insert(v);E[v].insert(u);
		}
	}
	for(int i=1;i<=n;i++)d[i]=E[i].size();
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=(E[i].size()==1);
		if(E[i].size()==1)vis[i]=2;
	}
	if(cnt==2)return pus("1");
	for(int i=1;i<=n;i++){
		if(vis[i]==2){//找新树
			vis[i]=1;
			int u=*E[i].begin();
			E[u].erase(i);E[i].erase(u);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(E[i].size()==1){d[i]-=2;ans++;}
		else d[i]-=(int)E[i].size();
		//如果在新树上度为 1，那就是其中一条上出边，与一条连到附属点的边虚化
		//否则减新树上所有出边
		if(!vis[i])ans+=max(d[i]-1,0);//还有剩下的附属点
	}
	write(ans,'\n');
}
```

---

