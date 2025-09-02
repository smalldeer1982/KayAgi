# Remove Directed Edges

## 题目描述

You are given a directed acyclic graph, consisting of $ n $ vertices and $ m $ edges. The vertices are numbered from $ 1 $ to $ n $ . There are no multiple edges and self-loops.

Let $ \mathit{in}_v $ be the number of incoming edges (indegree) and $ \mathit{out}_v $ be the number of outgoing edges (outdegree) of vertex $ v $ .

You are asked to remove some edges from the graph. Let the new degrees be $ \mathit{in'}_v $ and $ \mathit{out'}_v $ .

You are only allowed to remove the edges if the following conditions hold for every vertex $ v $ :

- $ \mathit{in'}_v < \mathit{in}_v $ or $ \mathit{in'}_v = \mathit{in}_v = 0 $ ;
- $ \mathit{out'}_v < \mathit{out}_v $ or $ \mathit{out'}_v = \mathit{out}_v = 0 $ .

Let's call a set of vertices $ S $ cute if for each pair of vertices $ v $ and $ u $ ( $ v \neq u $ ) such that $ v \in S $ and $ u \in S $ , there exists a path either from $ v $ to $ u $ or from $ u $ to $ v $ over the non-removed edges.

What is the maximum possible size of a cute set $ S $ after you remove some edges from the graph and both indegrees and outdegrees of all vertices either decrease or remain equal to $ 0 $ ?

## 说明/提示

In the first example, you can remove edges $ (1, 2) $ and $ (2, 3) $ . $ \mathit{in} = [0, 1, 2] $ , $ \mathit{out} = [2, 1, 0] $ . $ \mathit{in'} = [0, 0, 1] $ , $ \mathit{out'} = [1, 0, 0] $ . You can see that for all $ v $ the conditions hold. The maximum cute set $ S $ is formed by vertices $ 1 $ and $ 3 $ . They are still connected directly by an edge, so there is a path between them.

In the second example, there are no edges. Since all $ \mathit{in}_v $ and $ \mathit{out}_v $ are equal to $ 0 $ , leaving a graph with zero edges is allowed. There are $ 5 $ cute sets, each contains a single vertex. Thus, the maximum size is $ 1 $ .

In the third example, you can remove edges $ (7, 1) $ , $ (2, 4) $ , $ (1, 3) $ and $ (6, 2) $ . The maximum cute set will be $ S = \{7, 3, 2\} $ . You can remove edge $ (7, 3) $ as well, and the answer won't change.

Here is the picture of the graph from the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1674G/ea3975363bf1572eafbd52c82cc1fe5e48b9fade.png)

## 样例 #1

### 输入

```
3 3
1 2
2 3
1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 0```

### 输出

```
1```

## 样例 #3

### 输入

```
7 8
7 1
1 3
6 2
2 3
7 2
2 4
7 3
6 3```

### 输出

```
3```

# 题解

## 作者：CGDGAD (赞：12)

## CF1674G Remove Directed Edges

### 算法

首先回顾一下「Cute Set」的定义：

> 一个顶点的集合 $S$ 被称作可爱的当且仅当任意两个顶点 $v$ 和 $u$（$v \neq u,v \in S,u \in S$），可以经过由未删除的边组成的路径由 $u$ 达到 $v$，或是从 $v$ 达到 $u$。

由于原图是一个 DAG，集合中点和未删除的边构成的也是一个 DAG。由 DAG 联想到可以进行拓扑排序。拓扑序中，任何一对相邻的顶点 $(i, i+1)$，都满足：由 $i$ 可以通过一条路径到达 $i+1$，或是由 $i+1$ 可以通过条路径到达 $i$。若是后者，则 $i+1$ 在拓扑序中，必位于 $i$ 之前，矛盾。因此拓扑序中，总可以由靠前的顶点经过一些边到达靠后的顶点。由此推出一个重要的结论：**存在一条经过一个 Cute Set 中所有顶点的路径，一条路径经过的顶点的集合也是一个 Cute Set**。

问题转化为：在 DAG 中找一条最长路，且经过的边均未删除。

转化为一个更简单直白问题后，再来看删边的条件。每个顶点要么没有入边，要么被删一条入边，出边同理。下面思考的问题是，在选择路径的时候，哪些顶点可以被加入集合中？路径对于一个顶点而言，就是一条入边和一条出边。在保留这条路径不能删的同时，它还要预留可以删除的入边、出边各一条，以满足题意。因此，第二个重要的结论是：除了路径的起点没有入度要求、路径的终点没有出度要求以外，对于路径上每一个点的要求是至少分别有两条入边和两条出边，即**对于路径上的每一条边 $u \to v$，都要满足 $out_u>1$ 且 $in_v>1$**。

对于 DAG 上最长路问题，直接在拓扑序上 DP 即可，具体方法不再赘述。

### 实现

```cpp
int n, m;
int ind[200001], oud[200001], del[200001];
std::vector<int> e[200001];
std::queue<int> q;
int f[200001];

int main() {
    n = read(), m = read();
    while (m--) {
        int u = read(), v = read();
        ++ind[v], ++del[v], ++oud[u];
        e[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        if (!del[i]) q.push(i);
    }
    int ans = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans = std::max(ans, f[u]);
        for (int v : e[u]) {
            if (ind[v] > 1 && oud[u] > 1)
                f[v] = std::max(f[v], f[u] + 1);
            if (!--del[v])
                q.push(v);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Argon_Cube (赞：2)

* **【题目链接】**

[Link:CF1674G](https://www.luogu.com.cn/problem/CF1674G)

* **【解题思路】**

题目本质上就是求删边后最大最长路长度。要求每一个点要么删边之前没有出$/$入边，要么至少删去一个出$/$入边。

我们考虑 $\rm DAG$ 上 $\rm DP$，如果没有删边即为拓扑排序模板题。有了删边，还是一样的转移，但是只有符合条件才能转移。

当两点 $u,v$ 间有 $u\to v$ 的边，能从 $u$ 转移至 $v$ 当且仅当

* $in_v>1$，因为如果这么转移是最优的，就可以割掉一条不优的边，不然直接割这条边也没什么问题，反正也不会选从这条边转移。如果不满足 $in_v>1$ 则这条边必须被割掉。
* $out_u>1$，证明同上。

最后取 $\rm DP$ 数组的最大值即可。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
#include <queue>

using namespace std;

struct edge
{
	int to,nxt;
};

array<edge,200001> edges;
array<int,200001> head,in_deg,out_deg,DP_arr,cpy_in;
queue<int> BFS_que;
int edgecnt;

inline void add_edge(int from,int to)
{
	edges[++edgecnt]={to,head[from]};
	head[from]=edgecnt;
	++in_deg[to],++out_deg[from];
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,cntedge;
	cin>>cnt>>cntedge;
	while(cntedge--)
	{
		int from,to;
		cin>>from>>to;
		add_edge(from,to);
	}
	for(int i=1;i<=cnt;i++)
	{
		if(!in_deg[i])
			BFS_que.push(i);
		cpy_in[i]=in_deg[i];
	}
	while(!BFS_que.empty())
	{
		int tmp=BFS_que.front();
		BFS_que.pop();
		for(int i=head[tmp];i;i=edges[i].nxt)
		{
			int temp=edges[i].to;
			--cpy_in[temp];
			if(!cpy_in[temp])
				BFS_que.push(temp);
			if(out_deg[tmp]!=1&&in_deg[temp]!=1)
				DP_arr[temp]=max(DP_arr[tmp]+1,DP_arr[temp]);
		}
	}
	int ans=0;
	for(int i=1;i<=cnt;i++)
		ans=max(ans,DP_arr[i]);
	cout<<ans+1;
	return 0;
}


```

---

## 作者：jucason_xu (赞：1)

### 重要结论

**有向无环图的弱联通分量必然是链。**

### 证明

首先，因为它是有向无环图的一个子图，所以它必然没有环，所以它也是一个DAG。

那么，从起始点开始，给每一层的点打上度数，即是到原点（入度为0的点）的距离。

对于同一层的点来说，它只能被层数更小的点到达，只能到达层数更大的点（必要条件）。所以，**同一层的点不能互相到达**。

所以，每一层最多一个点。

所以，它是一条链。

### 算法

再发现，这个删边的条件，其实就是**有入边的至少删一条，有出边的至少删一条**。而在链上，每个点使用一次，最多用到它的一条出边和一条入边。对于一个点：

+ 如果它还有别的出边和入边，对于当前的链，删别的（_不包含在这个链的边_）即可。

+ 对于只有一条出边的点，一定要删掉这条出边，dfs到此为止，找到一条链。

+ 对于只有一条入边的点，不能作为源点以外的任何点，中间过程遇到，返回，不构成链。

但是每个点开始都跑一遍dfs是会炸的。我们可以在DAG上跑DP，设dp[i]为以第i个点为源点所能达到的最长的链的长度。转移就是：

>>```
>>if i has more than one son:
>>
>>   for all j: son[i]
>>
>>       if j has more than one parents:
>>
>>          answer:=min{dfs{j}and answer}
>>        
>>dp[i]:=answer+1;
>> ```

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,dp[200005],vis[200005];
vector<int>v1[200005],v2[200005];
int dfs(int i,int typ){
	if(v2[i].size()<=1&&typ==0)return 0;
	if(dp[i]!=-1)return dp[i];
	vis[i]=1;
	int res=0;
	if(v1[i].size()>1)for(auto j:v1[i]){
		res=max(res,dfs(j,0));
	}
	return dp[i]=res+1;
}
void solve(){
	int ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)dp[i]=-1;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		v1[a].push_back(b);
		v2[b].push_back(a);
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		ans=max(ans,dfs(i,1));
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t=1;
	for(int _=1;_<=t;_++)solve();
	return 0;
}
```


---

## 作者：MuelsyseU (赞：1)

题目大意：求将一个有向无环图删除若干边使得所有点的入度及出度要么减小，要么变为 $0$ 的所有方案中，最终的图最长路径最大值。

显然到达某个点的最长路可以用拓扑排序简单处理。但是对于入度仅为 $1$ 的节点，它的入边只能被删除从而其答案只能为 $1$。而如果不为 $1$，那么只需删除能到达该节点的所有节点中答案最小的节点连过来的边，因为这样仍然可以从更大的节点转移从而无影响。

同理，如果某个点只有唯一的出边，它这条边只能被割掉而不能转移到该边的终点。

对到达每个点的路径长度取 $\max$ 即可。

---

## 作者：ncwzdlsd (赞：0)

在一个 DAG 上找最长链，且最长链不包含删掉的边。

如何判断最长链上的边是否删掉？对于一个点 $i$，设 $f_i$ 表示以它为起点的符合条件的最长链长度，如果它的出度小于 $2$，则它的这条入边一定被删去，此时无法继续转移，$f_i=1$。而对于出度大于 $1$ 的点，再判断它所能到达的点的入度，如果入度小于 $2$ 则这条边会被删去，也不能转移。

注意转移要记忆化，如果以该点为起点的最长链长度已经计算过了就不用再算一遍了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
struct edge{int to,nxt;}e[maxn];
int head[maxn],f[maxn],in[maxn],out[maxn],cnt;

void add(int x,int y){e[++cnt]={y,head[x]},head[x]=cnt;}

void dfs(int x,int fa)
{
    if(f[x]) return;
    f[x]=1;
    if(out[x]<2) return;
    for(int i=head[x];i;i=e[i].nxt)
    {
        if(e[i].to==fa) continue;
        dfs(e[i].to,x);
        if(in[e[i].to]>1) f[x]=max(f[x],f[e[i].to]+1);
    }
}

int main()
{
    int n,m;cin>>n>>m;
    for(int i=1,u,v;i<=m;i++) cin>>u>>v,add(u,v),in[v]++,out[u]++;
    for(int i=1;i<=n;i++) dfs(i,0);
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,f[i]);
    cout<<ans;
    return 0;
}
```

---

