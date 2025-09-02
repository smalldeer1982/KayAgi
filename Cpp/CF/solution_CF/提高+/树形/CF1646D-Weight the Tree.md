# Weight the Tree

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ . A tree is a connected undirected graph without cycles.

For each $ i=1,2, \ldots, n $ , let $ w_i $ be the weight of the $ i $ -th vertex. A vertex is called good if its weight is equal to the sum of the weights of all its neighbors.

Initially, the weights of all nodes are unassigned. Assign positive integer weights to each vertex of the tree, such that the number of good vertices in the tree is maximized. If there are multiple ways to do it, you have to find one that minimizes the sum of weights of all vertices in the tree.

## 说明/提示

This is the tree for the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646D/c1443959610684ba1c023451af2be26a243d7782.png) In this case, if you assign a weight of $ 1 $ to each vertex, then the good vertices (which are painted black) are $ 1 $ , $ 3 $ and $ 4 $ . It impossible to assign weights so that all vertices are good vertices. The minimum sum of weights in this case is $ 1+1+1+1=4 $ , and it is impossible to have a lower sum because the weights have to be positive integers.This is the tree for the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646D/5f2b683a0e657b99ca0eb99ee84a2529445c05d6.png) In this case, if you assign a weight of $ 1 $ to each vertex, then the good vertices (which are painted black) are $ 2 $ and $ 3 $ . It can be proven that this is an optimal assignment.

## 样例 #1

### 输入

```
4
1 2
2 3
2 4```

### 输出

```
3 4
1 1 1 1```

## 样例 #2

### 输入

```
3
1 2
1 3```

### 输出

```
2 3
1 1 1```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
2 2
1 1```

## 样例 #4

### 输入

```
9
3 4
7 6
2 1
8 3
5 6
1 8
8 6
9 6```

### 输出

```
6 11
1 1 1 1 1 1 1 3 1```

# 题解

## 作者：Zimo_666 (赞：12)



## CF1646D

### 题意

给定一个无根树，点从 $1$ 到 $n$ 编号。你需要给每个点分配一个**正整数**权值 $w_i$。定义一个节点为**好节点**，当且仅当**其权值等于所有相邻节点的权值之和**。

请**最大化**好节点的个数，并且在好节点个数最大的前提下**最小化**所有节点的权值和。

### 分析

我们先考虑一种特殊情况，当 $n=2$ 时我们有唯一可以使一个点和它的父亲都为**好的节点**，这样我们先特判这种情况。

而后我们考虑设两个状态来转移本题。我们设 $f_{i,1/0}$ 表示该点是**好的节点或不好的节点**子树内好的节点数（包含该点）。显然我们有一个节点和它的父亲不能同时为好的节点。而后我们显然有转移

$f_{u,0}=\sum \min({f_{son[u],0},f_{son[u],1}})$

$f_{u,1}=\sum f_{sum[u],0}$。

而后我们考虑设 $g_{i,1/0}$ 表示该点是**好的节点或者不好的节点**子树内点权和（包含该点）。显然

$g_{u,1}=\sum g_{son[u],0}$。

当 $f_{u,0}=f_{u,1}$ 时有 $g_{u,0}=\sum \min(g_{son[u],0},g_{son[u],1})$。

当 $f_{u,0}>f_{u,1}$ 时有 $g_{u,0}=\sum f_{son[u],0}$。

当 $f_{u,0}<f_{u,1}$ 时有 $g_{u,0}=\sum f_{son[u],1}$。

而后我们考虑一种方案，即若该点为**好的节点**该点权值为 $deg[i]$ 否则为 $1$。显然最优。而后我们考虑怎么标记。我们考虑再进行一次 $mark$ 操作，如果该点的父亲被标记那么显然它肯定不能被标记，而后如果该点被该点不被标记是 $f$ 值大或者 $f$ 值相同 $g$ 值更小，那么不被标记，反之被标记。而后我们下传这个标记给他的儿子，这样使得它的儿子必须不能被标记，这样 dfs 下去显然可以得出一个方案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int n;
vector<int> G[N<<2];
int deg[N];
int f[N<<2][2],g[N<<2][2];
void dfs(int u,int father){
  f[u][1]=1,g[u][1]=deg[u],g[u][0]=1;
  for(int k:G[u]) if(k!=father){
    dfs(k,u);
    f[u][1]+=f[k][0];
    g[u][1]+=g[k][0];
    f[u][0]+=max(f[k][0],f[k][1]);
    if(f[k][0]==f[k][1]) g[u][0]+=min(g[k][0],g[k][1]);
    else g[u][0]+=(f[k][0]>f[k][1]?g[k][0]:g[k][1]);
  }
}
bool mrk[N];
void mark(int u,int father,bool fl){
  if(fl) mrk[u]=0;
  else{
    if(f[u][0]>f[u][1]||f[u][0]==f[u][1]&&g[u][0]<g[u][1])
    mrk[u]=0;
    else mrk[u]=1;
  }
  for(int k:G[u]){
    if(k!=father)
    mark(k,u,mrk[u]);
  }
}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n-1;i++){
    int u,v;scanf("%d%d",&u,&v);G[u].push_back(v),G[v].push_back(u);
    ++deg[u],++deg[v];
  }
  if(n==2) return printf("2 2\n1 1\n"),0;
  dfs(1,0);
  mark(1,0,0);
  printf("%d %d\n",max(f[1][0],f[1][1]),f[1][0]==f[1][1]?min(g[1][0],g[1][1]):(f[1][0]>f[1][1]?g[1][0]:g[1][1]));
  for(int i=1;i<=n;i++) printf("%d ",mrk[i]?deg[i]:1);
  return 0;
}
```



---

## 作者：Duramente (赞：8)

[传送门](https://codeforces.com/contest/1646/problem/D)  

## 题意
给一棵树，要求给每个点一个正整数权值，使在好点最多的情况下权值总和最小。  
好点的定义为，权值等于邻居权值之和。  

## Solution  
首先容易发现一个性质。当 $n> 2$ 时，相邻两个点不可能全是好点。

假设我们已经知道哪些点是好点了，怎么样才能使权值总和最小。  
不难发现，可以把不是好点的全标上 $1$，好点标上邻居个数。  

接着就是算好点个数了。  
我们可以在树上 dp 解决这个问题。  
令 $dp(u,0/1)$ 表示在以 $u$ 为根的子树中，当 $u$ 是好点或者不是好点的时候，最多有多少个好点。  
转移时，当钦定 $u$ 为好点，那么所有的儿子 $v$ 都不能是好点，$u$ 不是好点，所有儿子无论是不是好点都可以。    
最后还原路径构造方案。

## Code  

```cpp
#include<bits/stdc++.h>
#define forn(i,a,b)for(int i=(a),_b=(b);i<=_b;i++)
#define fore(i,b,a)for(int i=(b),_a=(a);i>=_a;i--)
#define rep(i,n)for(int i=0,_n=n;i<n;i++)
#define ll long long
#define pii pair<int,int>
#define m_p make_pair
#define pb push_back
#define fi first
#define se second
#define int ll
#define foreach(i,c) for(__typeof(c.begin())i=(c.begin());i!=(c).end();i++)
using namespace std;
const int N=200010;
int n;
pii dp[N][2];
vector<int>g[N]; 
int ans[N];
bool cmp(pii x,pii y){
	if(x.fi!=y.fi)return x.fi>y.fi;
	return x.se<y.se;
}
void dfs(int u,int fa){
	dp[u][1]=m_p(1,g[u].size());
	dp[u][0]=m_p(0,1);
	rep(i,g[u].size()){
		int v=g[u][i];
		if(v==fa)continue;
		dfs(v,u);
		dp[u][1].fi+=dp[v][0].fi;dp[u][1].se+=dp[v][0].se;
		if(cmp(dp[v][0],dp[v][1])){
			dp[u][0].fi+=dp[v][0].fi;dp[u][0].se+=dp[v][0].se;
		}
		else{
			dp[u][0].fi+=dp[v][1].fi;dp[u][0].se+=dp[v][1].se;
		}
	}
}
void _dfs(int u,int fa,int st){
	if(st)ans[u]=g[u].size();
	else ans[u]=1;
	rep(i,g[u].size()){
		int v=g[u][i];
		if(v==fa)continue;
		if(st){
			_dfs(v,u,0);
		}
		else{
			if(cmp(dp[v][0],dp[v][1])){
				_dfs(v,u,0);
			}
			else{
				_dfs(v,u,1);
			}
		}
	}
}
signed main(){
    cin.tie(0);
	ios::sync_with_stdio(0);
	cin>>n;
	rep(i,n-1){
		int u,v;
		cin>>u>>v;
		g[u].pb(v);g[v].pb(u);
	} 
	if(n==2){
		cout<<"2 2\n";
		cout<<"1 1\n";
    	return 0;
	}
	dfs(1,0);
	if(cmp(dp[1][0],dp[1][1])){
		cout<<dp[1][0].fi<<" "<<dp[1][0].se<<"\n";
		_dfs(1,0,0);
	}
	else{
		cout<<dp[1][1].fi<<" "<<dp[1][1].se<<"\n";
		_dfs(1,0,1);
	}
	forn(i,1,n)cout<<ans[i]<<" ";cout<<"\n";
	return 0;
}

---

## 作者：文曲兔 (赞：5)

### 题目描述

给定一个无根树，需要给每个点一个**正整数**权值 $w_i$。定义一个节点为好的当且仅当其权值等于所有相邻节点的权值之和。目标为最大化好节点的个数，在此基础上最小化所有节点的权值和，需要输出权值分配方案。

### 分析

首先需要注意到一个性质：$n \geq 3$ 时任何相邻节点不可能同时是好的。

> 证明：假设 $u,v$ 是相邻的好节点，$A,B$ 分别是与 $u,v$ 相邻的节点中除去对方以外的节点的权值和（可以为空）。根据好节点的定义有 $w_u = w_v + A$ 且 $w_v = w_u + B$，这就导出 $A = B = 0$，即 $n = 2$。

于是对于 $n = 2$ 特判即可。否则，如果节点 $u$ 是好的，则它的子节点 $v$ 必定是不好的，这立刻让我们想到[没有上司的舞会](https://www.luogu.com.cn/problem/P1352)。于是考虑树形 dp，以节点 $1$ 为根，令 $dp_{u,1/0}$ 表示**钦定 $u$ 是好的/不好的的情况下 $u$ 子树内好节点个数最大值**，转移即为：
$$
\begin{cases}
dp_{u,0} = \sum_{v \in son[u]} \max \{dp_{v,1},dp_{v,0}\} \\
dp_{u,1} = \sum_{v \in son[u]} dp_{v,0} + 1
\end{cases}
$$
边界 $dp_{u,0} = 0, dp_{u,1} = 1$，而答案是 $\max\{dp_{1,0},dp_{1,1}\}$。但还没有最小化权值之和，这也很容易构造出来：贪心地，不好的节点权值至少为 $1$，而好的节点 $u$ 的权值至少为 $deg_u$，其中 $deg_u$ 为 $u$ 的度数。注意到只要好节点的个数取到最大值，这样的构造总是可以成立的，于是它就是最优的。这样，我们只要能判断出最优方案下所有节点的好坏就做完了。

于是发现在 dp 过程中，还需要记录转移路径。令 $good_u$ 表示 **当 $u$ 的父亲是不好的的情况下，$u$ 应该是好的还是不好的才能使答案最优**（如果 $u$ 的父亲是好的那就没必要了，因为 $u$ 一定是不好的）。要判断这个东西的话发现还需要求出**钦定 $u$ 是好的/不好的情况下 $u$ 子树好节点取到最大值时，$u$ 子树内权值的最小值**。记这个东西为 $weighsum_{u,1/0}$，可以和 $dp$ 在同一次 dfs 内求出，转移略去。官方题解里把 $dp$ 和 $weighsum$ 封装成 pair 了，代码更加简洁一点。

最后根据根节点的状态求出 $1$ 究竟是好的还是不好的，再做第二次 dfs 通过父亲的好坏判断出儿子的好坏，就求出了方案。

复杂度 $O(n)$。

### 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 2e5+5;
const int MAXM = 4e5+5;

int head[MAXN], to[MAXM], nxt[MAXM], deg[MAXN], tot;
int dp[MAXN][2]; long long weighsum[MAXN][2];
int weigh[MAXN]; bool good[MAXN];
int n;

void addedge(int x, int y)
{
    ++deg[x];
    to[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}

//返回一个节点的 good 值
bool cmp(int v)
{
    if(dp[v][0] != dp[v][1]) return dp[v][1] > dp[v][0];
    return weighsum[v][1] < weighsum[v][0];
}

void dfs(int u, int f)
{
    dp[u][0] = 0; dp[u][1] = 1;
    weighsum[u][0] = 1; weighsum[u][1] = deg[u];
    for(int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if(v == f) continue;
        dfs(v, u);
        good[v] = cmp(v);
        dp[u][0] += dp[v][good[v]];
        dp[u][1] += dp[v][0];
        weighsum[u][0] += weighsum[v][good[v]];
        weighsum[u][1] += weighsum[v][0];
    }
}

void dfs2(int u, int f, bool g)
{
    weigh[u] = g ? deg[u] : 1;
    for(int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if(v == f) continue;
        dfs2(v, u, g ? 0 : good[v]);
    }
}

int main()
{
    scanf("%d",&n);
    for(int i = 1,u,v; i < n; ++i)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v); addedge(v,u);
    }
    if(n == 2)
    {
        printf("2 2\n1 1");
        return 0;
    }
    dfs(1,0);
    bool good1 = cmp(1);
    dfs2(1,0,good1);
    printf("%d %lld\n",dp[1][good1],weighsum[1][good1]);
    for(int u = 1; u <= n; ++u) printf("%d ",weigh[u]);
    return 0;
}
```



---

## 作者：qiuzijin2026 (赞：3)

# CF1646D Weight the Tree

[题面](https://www.luogu.com.cn/problem/CF1646D)

## 思路

裸的树形 `DP`。

显然在 $n\ge3$ 时，任意两个相邻结点不可能都是好节点。

所以对于 $n=2$ 的情况要特判一下。

我们设 $f_{i,0/1}$ 表示结点 $i$ 不选与选时以结点 $i$ 为根的子树好节点个数的最大值，$s_{i,0/1}$ 表示结点 $i$ 不选与选时以结点 $i$ 为根的子树好节点个数的最大时权值最小是多少。

设 $j$ 是 $i$ 的一个子结点，有转移方程：

- $f_{i,0}=f_{i,0}+\min(f_{j,0},f_{j,1})$

	1. $f_{j,0}>f_{j,1}:s_{i,0}=s_{i,0}+s_{j,0}$

	2. $f_{j,0}<f_{j,1}:s_{i,0}=s_{i,0}+s_{j,1}$

	3. $f_{j,0}=f_{j,1}:s_{i,0}=s_{i,0}+\min(s_{j,0},s_{j,1})$


- $f_{i,1}=f_{i,1}+f_{j,0}$
	
	$s_{i,1}=s_{i,1}+s_{j,0}$

做完树形 `DP` 后，跑一遍 `dfs` 标记所有好节点。

最后，对于每一个结点，有以下两种情况：

- 不是好结点，权值为 $1$。

- 是好结点，权值为它的入度。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int to;
	int next;
}b[400005];
int h[200005],l;
void jb(int x,int y){
	b[++l].to=y;
	b[l].next=h[x];
	h[x]=l;
}
int n;
int f[200005][2];
int s[200005][2];
bool flag[200005];
int rd[200005];
int ans;
void dfs(int x,int fa){
	s[x][0]=1;
	for(int i=h[x];i;i=b[i].next)
		if(b[i].to!=fa){
			dfs(b[i].to,x);
			if(f[b[i].to][0]>f[b[i].to][1]){
				f[x][0]+=f[b[i].to][0];
				s[x][0]+=s[b[i].to][0];
			}
			else if(f[b[i].to][0]<f[b[i].to][1]){
				f[x][0]+=f[b[i].to][1];
				s[x][0]+=s[b[i].to][1]+1;
			}
			else{
				f[x][0]+=f[b[i].to][0];
				s[x][0]+=min(s[b[i].to][0],s[b[i].to][1]+1);
			}
			f[x][1]+=f[b[i].to][0];
			s[x][1]+=s[b[i].to][0];
		}
	f[x][1]++;
	if(fa) s[x][1]+=rd[x]-1;
	else s[x][1]+=rd[x];
}
void dfsans(int x,int fa,int d){
	flag[x]=d;
	for(int i=h[x];i;i=b[i].next)
		if(b[i].to!=fa){
			if(d==0){
				if(f[b[i].to][0]>f[b[i].to][1]) dfsans(b[i].to,x,0);
				else if(f[b[i].to][0]<f[b[i].to][1]) dfsans(b[i].to,x,1);
				else{
					if(s[b[i].to][0]<=s[b[i].to][1]) dfsans(b[i].to,x,0);
					else dfsans(b[i].to,x,1);
				}
			}
			else if(d==1) dfsans(b[i].to,x,0);
		}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		jb(x,y);
		jb(y,x);
		rd[x]++;
		rd[y]++;
	}
	if(n==2){
		printf("2 2\n");
		printf("1 1");
		return 0;
	}
	dfs(1,0);
	if(f[1][0]>f[1][1]) dfsans(1,0,0);
	else if(f[1][0]<f[1][1]) dfsans(1,0,1);
	else{
		if(s[1][0]<s[1][1]) dfsans(1,0,0);
		else dfsans(1,0,1);
	}
	for(int i=1;i<=n;i++)
		if(flag[i]) ans+=rd[i];
		else ans++;
	printf("%d %d\n",max(f[1][0],f[1][1]),ans);
	for(int i=1;i<=n;i++)
		if(flag[i]) printf("%d ",rd[i]);
		else printf("1 ");
	return 0;
}
```

---

## 作者：Argon_Cube (赞：1)

* **【题目链接】**

[Link:CF1646D](https://www.luogu.com.cn/problem/CF1646D)

* **【解题思路】**

首先易证所有符合条件的点一定构成原树的独立集。$n=2$ 是唯一的反例，把它特判掉即可。

现在我们的问题变成：找出原树中度数之和最小的最大独立集。显然符合条件的点带着的值即为它的度数，其它点赋值为 $1$ 即可。

如果不考虑度数，那么就是没有上司的舞会，一个简单的树形 DP。我们也和那道题一样，不过因为是无根树，随便以一个点作为根结点即可。

有了度数的限制，我们就多记录一个度数，当某个子结点选与不选得到的独立集大小一样，我们认为度数总和更小的方案更优。

DP 时顺便记录转移路径，最后一遍 DFS 求答案即可。

* **【代码实现】**

```cpp
#include <iostream>
#include <vector>
#include <array>
 
using namespace std;
 
array<int,200001> degs,answers;
array<vector<int>,200001> sons;
array<array<int,200001>,2> DP_arr,DP_deg;
array<array<vector<pair<int,int>>,200001>,2> state;
 
int DFS(int root,int father)
{
	DP_arr[1][root]=1,DP_deg[1][root]=degs[root]-1;
	for(const int tmp:sons[root])
		if(tmp!=father)
		{
			DFS(tmp,root);
			DP_arr[1][root]+=DP_arr[0][tmp],DP_deg[1][root]+=DP_deg[0][tmp],state[1][root].push_back(make_pair(0,tmp));
			if(DP_arr[0][tmp]>DP_arr[1][tmp])
				DP_arr[0][root]+=DP_arr[0][tmp],DP_deg[0][root]+=DP_deg[0][tmp],state[0][root].push_back(make_pair(0,tmp));
			else if(DP_arr[0][tmp]<DP_arr[1][tmp])
				DP_arr[0][root]+=DP_arr[1][tmp],DP_deg[0][root]+=DP_deg[1][tmp],state[0][root].push_back(make_pair(1,tmp));
			else
				if(DP_deg[0][tmp]>DP_deg[1][tmp])
					DP_arr[0][root]+=DP_arr[1][tmp],DP_deg[0][root]+=DP_deg[1][tmp],state[0][root].push_back(make_pair(1,tmp));
				else
					DP_arr[0][root]+=DP_arr[0][tmp],DP_deg[0][root]+=DP_deg[0][tmp],state[0][root].push_back(make_pair(0,tmp));
		}
	return max(DP_arr[0][root],DP_arr[1][root]);
}
 
void DFS_2(int root,int cur_st,int father)
{
	if(cur_st)
		answers[root]=degs[root];
	for(const auto& tmp:state[cur_st][root])
		if(tmp.second!=father)
			DFS_2(tmp.second,tmp.first,root);
}
 
int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	answers.fill(1);
	int cnt;
	cin>>cnt;
	if(cnt==2)
		return cout<<"2 2\n1 1",0;
	for(int i=1;i<cnt;i++)
	{
		int tmpfrom,tmpto;
		cin>>tmpfrom>>tmpto;
		sons[tmpfrom].push_back(tmpto);
		sons[tmpto].push_back(tmpfrom);
		degs[tmpfrom]++,degs[tmpto]++;
	}
	cout<<DFS(1,0)<<' ';
	if(DP_arr[0][1]>DP_arr[1][1])
		cout<<DP_deg[0][1]+cnt;
	else if(DP_arr[0][1]<DP_arr[1][1])
		cout<<DP_deg[1][1]+cnt;
	else
		cout<<min(DP_deg[0][1],DP_deg[1][1])+cnt;
	cout<<'\n';
	if(DP_arr[0][1]>DP_arr[1][1])
		DFS_2(1,0,0);
	else if(DP_arr[0][1]<DP_arr[1][1])
		DFS_2(1,1,0);
	else
		if(DP_deg[0][1]<DP_deg[1][1])
			DFS_2(1,0,0);
		else 
			DFS_2(1,1,0);
	for(int i=1;i<=cnt;i++)
		cout<<answers[i]<<' ';
 	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
构造方案使在权值等于临点权值和的点最大化的情况下最小化权值和（权值为正）。

# 题目思路
首先思考一下，除了两个点的情况，没有可能父子都符合要求（这个都看不出来就可以放弃这道题了）。

于是猜一个结论（其实也不叫猜）：
- 如果不选这个节点，将权值变成 $1$；
- 否则，权值为其度数。

满足以上条件的时候可以在确定那些点选的情况下获取最小权值。

所以问题就转变成了构造方案。

考虑定义：
- 数组 $f_{i, 0/1}$ 表示选或不选这个节点时其子树内满足条件的点数的最大值；
- 数组 $g_{i, 0/1}$ 表示选或不选这个节点时其子树内满足 $f_{i, 0/1}$ 最大时的最小权值和。

考虑转移（下文中，$j$ 表示 $i$ 的儿子）：
- 对于数组 $f$：
  - $f_{i,0} = \sum \max(f_{j, 0},f_{j, 1})$；
  - $f_{i,1} = 1 + \sum f_{j, 0}$。
- 对于数组 $g$：
  - $g_{i, 0}$ 的转移详见注释（公式太麻烦了）；
  - $g_{i, 1} = deg(i) + \sum g_{j, 0}$。

啊啊啊，公式好烦，答案表示也见注释吧（其实和 $g_{i, 0}$ 的转移同理）。

~~啊啊啊啊啊啊，公式好烦，构造也见注释吧（和前两个同理）。~~

还是简单说一下如何构造：
  - 如果父亲不选：
    - 如果 $f$ 不相等，按照大的来；
    - 否则，按照 $g$ 小的来。
  - 如果父亲选：
    - 肯定不选。

其实感觉这个题后面那三个不想写公式的情况的处理方式差不多。

# [AC Code](https://codeforces.com/contest/1646/submission/292459831)

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n;
int u, v;
vector <int> _Mp[N];
int f[N][2], g[N][2];
bool _Flg[N];
int _Ansf, _Ansg;

void Dfs (int id, int fa) {
	f[id][1] = 1;
	g[id][0] = 1;
	g[id][1] = _Mp[id].size ();
	
	for (auto it : _Mp[id]) {
		if (it ^ fa) {
			Dfs (it, id);
			f[id][0] += max (f[it][0], f[it][1]);

			//因为我们要先保证个数最多，所以如果 f 不等，就要按照 f 那个大转；
			//反之，就要权值最小所以就按 g 转。
			
			if (f[it][0] == f[it][1]) {
				g[id][0] += min (g[it][0], g[it][1]);
			} else if (f[it][0] > f[it][1]) {
				g[id][0] += g[it][0];
			} else {
				g[id][0] += g[it][1];
			}
			
			f[id][1] += f[it][0];
			g[id][1] += g[it][0];
		}
	}
}

void Flag (int id, int fa) {
	if (_Flg[fa]) {
		_Flg[id] = 0;
	} else {
		//因为我们要先保证个数最多，所以如果 f 不等，就要按照 f 那个构造；
		//反之，就要权值最小所以就按 g 构造。
		
		if (f[id][0] > f[id][1] || (f[id][0] == f[id][1] && g[id][0] < g[id][1])) {
			_Flg[id] = 0;
		} else {
			_Flg[id] = 1;
		}
	}
	
	for (auto it : _Mp[id]) {
		if (it ^ fa) {
			Flag (it, id);
		}
	}
}

signed main () {
	ios :: sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);
	
	cin >> n;
	
	for (register int i = 1; i ^ n; ++ i) {
		cin >> u >> v;
		_Mp[u].push_back (v);
		_Mp[v].push_back (u);
	}
	
	Dfs (1, 0);
	Flag (1, 0);
	
	if (f[1][0] == f[1][1]) {
		_Ansf = f[1][0];
		_Ansg = min (g[1][0], g[1][1]);
	} else if (f[1][0] > f[1][1]) {
		_Ansf = f[1][0];
		_Ansg = g[1][0];
	} else {
		_Ansf = f[1][1];
		_Ansg = g[1][1];
	}
	
	if (n == 2) {
		_Ansf = 2;
	}
	
	cout << _Ansf << ' ' << _Ansg << endl;
	
	for (register int i = 1; i <= n; ++ i) {
		if (_Flg[i]) {
			cout << _Mp[i].size () << ' ';
		} else {
			cout << 1 << ' ';
		}
	}
	
	cout << endl;
	return 0;
}
```

---

## 作者：Richard_Whr (赞：0)

一种另类做法。

首先发现除了两个点一条边之外，一条边连接的两个节点肯定不能同时是好点。

然后树上最大独立集 dp 求出第一问的答案。

对于第二问，发现可以这样构造，好点权值设为 $deg_u$，其余设为 $1$，这样在确定好点集合的时候一定最优。

那么就是要求恰好选出 $ans$ 个好点，权值按上述赋值，然后满足独立集要求，最小化权值和。

看到恰好 $k$ 个就想到了 wqs 二分，转念一想根本不用二分直接补偿 $-\infty$ 即可，因为最多就选 $ans$ 个，我们要求选 $ans$ 个。

然后像 wqs 二分一样 dp 一遍，记录路径就行了。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+10,Inf=1e9;
int f[N][2];
vector<int> e[N];
vector<PII> son[N][2];
int d[N];
int ans[N];
bool st[N];
int n;

void dfs(int u,int fa)
{
	f[u][0]=0,f[u][1]=1;
	for(auto v:e[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		f[u][0]+=max(f[v][1],f[v][0]);
		f[u][1]+=f[v][0];
	}
}

void Dfs(int u,int fa)
{
	f[u][0]=1,f[u][1]=d[u]-Inf;
	for(auto v:e[u])
	{
		if(v==fa) continue;
		Dfs(v,u);
		if(f[v][1]<f[v][0]) f[u][0]+=f[v][1],son[u][0].push_back({v,1});
		else f[u][0]+=f[v][0],son[u][0].push_back({v,0});
		f[u][1]+=f[v][0],son[u][1].push_back({v,0});
	}
}

void Mark(int u,int t)
{
	st[u]=t;
	for(auto Pir:son[u][t])
	{
		int v=Pir.first,c=Pir.second;
		Mark(v,c);
	}
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); 
	
	cin>>n;
	for(int i=1,a,b;i<n;i++)
	{
		cin>>a>>b;
		d[a]++,d[b]++;
		e[a].push_back(b),e[b].push_back(a);
	}
	
	if(n==2)
	{
		printf("%d %d\n%d %d\n",2,2,1,1);
		return 0;
	}
	
	dfs(1,0);
	
	int res=max(f[1][0],f[1][1]);
	
	Dfs(1,0); 
	
	int sum=min(f[1][0],f[1][1])+res*Inf;
	
	if(f[1][0]<f[1][1]) Mark(1,0);
	else Mark(1,1);
	
	for(int i=1;i<=n;i++) 
	{
		if(!st[i]) ans[i]=1;
		else ans[i]=d[i];
	}
	
	cout<<res<<" "<<sum<<"\n";
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0; 
}
```

---

## 作者：zhangxiao666 (赞：0)

## 题意：

给定一棵树，给每个点分配正整数权值，定义“好点”为权值等于相邻点权值之和的点，最大化好点个数，并在该前提下最小化节点权值和。

## 思路：

假设我们知道了哪些点是好点，那么显然把不是好点权值为 $1$，好点权值为相邻点的和，这样一定最优。

那问题转化成如何求出好点最多有多少个，考虑使用树形 dp 来做。

令 $f_{i,1/0}$ 表示在 $i$ 点的子树内，$i$ 为好点或非好点时好点的个数，由于 $i$ 点是好点时，它的子节点都不能是好点，所以有：$f_{i,1}=\sum f_{son_i,0}$。

当 $i$ 点不是好点时，它的子节点可以是好点也可以不是，所有又有：$f_{i,0}=\sum min(f_{son_i,0},f_{son_i,1})$。

最后在 dp 的过程中顺带记录权值，推路径算出哪些点是好点即可，即如果父节点为好点，该点不为好点，否则比较该点为好点或非好点哪个更优即可。

还要注意一个较坑的地方：$n=2$ 时答案为 $2$，需要特判一下。 

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, cnt;
int f[N][2], g[N][2], ans[N];
// f : point 1 : x good,  0 : x not good
// g : val   1 : x good,  0 : x not good
int head[N], nxt[2 * N], to[2 * N], du[N];

void add(int x, int y)
{
    du[x]++; //记录相邻点个数，便于统计
    nxt[++cnt] = head[x];
    to[cnt] = y;
    head[x] = cnt;
}

int cmp(int x)
{
    return f[x][0] ^ f[x][1] ? f[x][1] > f[x][0] : g[x][1] < g[x][0];
}
//比较哪一种方案更优，相同选择权值较少的

void dfs1(int u, int fa)
{
    f[u][1] = 1, f[u][0] = 0;
    g[u][1] = du[u], g[u][0] = 1;
//设置dp边界
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i], good;
        if (v == fa) continue;
        dfs1(v, u); good = cmp(v);
//good表示v取好点/不取更优
        f[u][1] += f[v][0];
        f[u][0] += f[v][good];
        g[u][1] += g[v][0];
        g[u][0] += g[v][good];
//dp转移
    }
}

void dfs2(int u, int fa, int good)
{
    ans[u] = good;
//推路径，记录方案
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs2(v, u, good ? 0 : cmp(v));
//父节点为1该点一定为0，否则取较优的
    }
}

void work()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int x, y; cin >> x >> y;
        add(x, y), add(y, x);
    }
    dfs1(1, 0);
    bool good = cmp(1);
    if (n == 2) f[1][good] = 2;
    cout << f[1][good] << " " << g[1][good] << "\n";
    dfs2(1, 0, good);
    for (int i = 1; i <= n; i++) cout << (ans[i] ? du[i] : 1) << " ";
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--) work();
    return 0;
}
```

---

## 作者：arrow_king (赞：0)

# 题意

给定一颗无根树，需要给第 $i$ 个点分配权值 $w_i$。

如果 $w_u=\sum\limits_{(u,v)\in E}w_v$，那么点 $u$ 是好的。

分配权值使得最大化好点个数的情况下最小化 $\sum w_i$。

# 思路

首先最大化好点个数可以想到树形 dp。

注意到当 $n>2$ 时，相邻的两个点不能都是好点。

> 如果 $u,v$ 都是好点且 $(u,v)\in E$，那么 $w_u=w_v+\sum\limits_{(u,k)\in E,k\not=v}w_k$，$w_v=w_u+\sum\limits_{(v,k)\in E,k\not=u}w_k$。注意到这里 $w_u$ 等于 $w_v$ 加一个正数，$w_v$ 也等于 $w_u$ 加另一个正数。这只有当 $w_u=w_v=0$ 时才能满足，与 $w_i\ge 1$ 的限制矛盾，因此得证。当 $n=2$ 时 $w_u=w_v$ 就可以，因此可以两个点都是好点。

所以当 $n=2$ 时直接特判输出就可以。

当 $n>2$ 时，令 $f_{u,0/1}$ 表示 $u$ 是否为好点时子树内好点个数最大值。

显然 $f_{u,0}=\sum\limits_{(u,v)\in E}\max\{f_{v,0},f_{v,1}\}$，$f_{u,1}=1+\sum\limits_{(u,v)\in E}f_{v,0}$。

但是这样是不足以构造方案的，于是再引入一个数组 $g_{u,0/1}$ 表示当 $u$ 是否为好点时，在 $u$ 子树内好点数量取最大时子树点权之和。这里点权已经由好点的标记决定了：好点的点权是 $d_u$，非好点的权是 $1$。

这样可以得到 $g$ 的转移方程

$g_{u,1}=\sum\limits_{(u,v)\in E}g_{v,0}$。

当 $f_{u,0}=f_{u,1}$ 时 $g_{u,0}=\sum\limits_{(u,v)\in E}\max\{g_{v,0},g_{v,1}\}$。

当 $f_{u,0}>f_{u,1}$ 时 $g_{u,0}=\sum\limits_{(u,v)\in E}g_{v,0}$。

当 $f_{u,0}<f_{u,1}$ 时 $g_{u,0}=\sum\limits_{(u,v)\in E}g_{v,1}$。

然后还原 dp 数组的路径来标记即可。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,d[N];
int f[N][2],a[N][2];		//a就是g数组，因为和存树的vector重名所以改了
vector<int> g[N];
il void dfs(int u,int fa) {		//dp来求解
	f[u][1]=1;
	a[u][1]=d[u];
	a[u][0]=1;
	for(int i=0;i<g[u].size();i++) {
		int v=g[u][i];
		if(v==fa) continue;
		dfs(v,u);
		f[u][1]+=f[v][0];
		a[u][1]+=a[v][0];
		f[u][0]+=max(f[v][0],f[v][1]);
		if(f[v][0]==f[v][1]) a[u][0]+=min(a[v][0],a[v][1]);
		else {
			if(f[v][0]>f[v][1]) a[u][0]+=a[v][0];
			else a[u][0]+=a[v][1];
		}
	}
}
bool vis[N];
il void solve(bool vi,int u,int fa) {
	if(vi) vis[u]=0;
	else {
		if(f[u][0]>f[u][1]||f[u][0]==f[u][1]&&a[u][0]<a[u][1]) vis[u]=0;
		else vis[u]=1;
        /*
        如果不取这个点的好点个数比取要多，那么一定不取；
        如果一样多但是总和要少，那么也一定不取；
        否则就取这个点为好点。
        这个过程和上面的dp是一样的。
        */
	}
	for(int i=0;i<g[u].size();i++) {
		int v=g[u][i];
		if(v==fa) continue;
		solve(vis[u],v,u);
	}
}
int main() {
	n=read();
	for(int i=1;i<n;i++) {
		int u=read(),v=read();
		g[u].push_back(v),g[v].push_back(u);
		d[u]++,d[v]++;
	}
	if(n==2) {
		printf("2 2\n1 1\n");
		return 0;
	}
	dfs(1,0);
	solve(0,1,0);
	printf("%d ",max(f[1][0],f[1][1]));
	if(f[1][0]==f[1][1]) printf("%d\n",min(a[1][0],a[1][1]));
	else {
		if(f[1][0]>f[1][1]) printf("%d\n",a[1][0]);
		else printf("%d\n",a[1][1]);
	}
	for(int i=1;i<=n;i++) {
		if(vis[i]) printf("%d ",d[i]);
		else printf("1 ");
	}
	return 0;
}
```

---

## 作者：slzx2022YuYihan (赞：0)

# Description

给你一颗树，你要给这棵树每个节点一个权值。如果当前节点的权值等于与它相邻的点的权值之和，称这个节点是好的。询问最多的好的节点的个数，并输出权值综合最小的方案。

# Solution

显然可以 dp。

$f_{u,0/1}$ 表示当前节点 $u$ 为不好的或者好的，他的子树最多有多少个好的，快速推出（~~如果你李姐不了就放掉这道题吧~~）：

$f_{u,1}=\sum_{v\in u}f_{v,0}+1$

$f_{u,0}=\sum_{v\in u}\max(f_{v,0},dp_{v,1})$

$g_{u,0/1}$ 表示当前节点 $u$ 为不好的或者好的，满足好的个数为 $f_{u,0}/f_{u,1}$，最少的权值之和，初始化：$g_{u,0}=1,g_{u,1}=deg_u$。

显然的，$g_{u,1}=\sum_{v\in u}g_{v,0}$。

接下来处理 $g_{u,0}$。

对于 $u$ 的儿子 $v$，

*	若 $f_{v,0}<f_{v,1}$，说明是从 $f_{v,1}$ 转移而来，``g[u][0] += g[u][1]``。
*	若 $f_{v,0}>f_{v,1}$，说明是从 $f_{v,0}$ 转移而来，``g[u][0] += g[u][0]``。
*	若 $f_{v,0}=f_{v,1}$，``g[u][0] += min(g[v][0], g[v][1])``。

接下来是输出的第一步，

*	若 $f_{1,0}>f_{1,1}$，输出 $g_{1,0}$。
*	若 $f_{1,0}<f_{1,1}$，输出 $g_{1,1}$。
*	若 $f_{1,0}=f_{1,1}$，输出 $\min(g_{1,0},g_{1,1})$。

输出第二步，我们可以从根节点开始深搜，根据从哪里转移来判断当前节点的权值究竟是 $deg_u$ 还是 $\mathbb 1$。

在测样例 3 的时候，我们发现了代码的漏洞，特判即可。

时间复杂度 $O(n)$。

# Code

下面是可食用代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T &x){
	x = 0; T w = 1; char ch = getchar();
	while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
	while (isdigit(ch))	x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	x *= w;
}
template<typename T>inline void write(T x){
	if (x < 0)	putchar('-'), x = ~(x - 1);
	if (x > 9)	write(x / 10);
	putchar(x % 10 ^ 48);
}

const int N = 2e5 + 5;

ll n;

ll num, h[N], to[N << 1], nxt[N << 1], deg[N];
void addedge(ll u, ll v){
	to[++num] = v, nxt[num] = h[u], h[u] = num, ++deg[u];
}

ll f[N][2], g[N][2];
bool ok[N];
bool pd(ll x){
	return f[x][1] == f[x][0] ? g[x][1] < g[x][0] : f[x][1] > f[x][0];
}

void dfs(ll u, ll pre){
	f[u][1] = 1, g[u][0] = 1, g[u][1] = deg[u];
	for (int i = h[u]; i; i = nxt[i]){
		ll v = to[i];
		if (v == pre)	continue;
		dfs(v, u);
		ok[v] = pd(v);
		f[u][1] += f[v][0], f[u][0] += f[v][ok[v]], g[u][1] += g[v][0], g[u][0] += g[v][ok[v]];
	}
}

ll w[N];
void dfsw(ll u, ll pre, bool p){
	w[u] = p ? deg[u] : 1;
	for (int i = h[u]; i; i = nxt[i]){
		ll v = to[i];
		if (v == pre)	continue;
		dfsw(v, u, p ? 0 : ok[v]);
	}
}

int main(){
//	freopen(".in", "r", stdin), freopen(".out", "w", stdout);
//	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

	read(n);
	for (int i = 1, u, v; i < n; ++i){
		read(u), read(v);
		addedge(u, v), addedge(v, u);
	}
	if (n == 2){
		puts("2 2"), puts("1 1");
		return 0;
	}
//	这里要特判 
	dfs(1, 0);
	ok[1] = pd(1);
	write(f[1][ok[1]]), putchar(' '), write(g[1][ok[1]]), putchar('\n');
	dfsw(1, 0, ok[1]);
	for (int i = 1; i <= n; ++i)	write(w[i]), putchar(' ');

	return 0;
}
/*
Notes	by slzx2022YuYihan

显然可以 dp。

$f_{u,0/1}$ 表示当前节点 $u$ 为不好的或者好的，他的子树最多有多少个好的，快速推出（~~如果你李姐不了就放掉这道题吧~~）：

$f_{u,1}=\sum_{v\in u}f_{v,0}+1$

$f_{u,0}=\sum_{v\in u}\max(f_{v,0},dp_{v,1})$

$g_{u,0/1}$ 表示当前节点 $u$ 为不好的或者好的，满足好的个数为 $f_{u,0}/f_{u,1}$，最少的权值之和，初始化：$g_{u,0}=1,g_{u,1}=deg_u$。

显然的，$g_{u,1}=\sum_{v\in u}g_{v,0}$。

接下来处理 $g_{u,0}$。

对于 $u$ 的儿子 $v$，

*	若 $f_{v,0}<f_{v,1}$，说明是从 $f_{v,1}$ 转移而来，``g[u][0] += g[u][1]``。
*	若 $f_{v,0}>f_{v,1}$，说明是从 $f_{v,0}$ 转移而来，``g[u][0] += g[u][0]``。
*	若 $f_{v,0}=f_{v,1}$，``g[u][0] += min(g[v][0], g[v][1])``。

接下来是输出的第一步，

*	若 $f_{1,0}>f_{1,1}$，输出 $g_{1,0}$。
*	若 $f_{1,0}<f_{1,1}$，输出 $g_{1,1}$。
*	若 $f_{1,0}=f_{1,1}$，输出 $\min(g_{1,0},g_{1,1}}$。

输出第二步，我们可以从根节点开始深搜，根据从哪里转移来判断当前节点的权值究竟是 $deg_u$ 还是 $\mathbb 1$。

时间复杂度 $O(n)$。
*/
```

---

## 作者：OIer_ACMer (赞：0)

~~这道题树上 DP 还蛮好做的。~~

------------
## 大致思路：
这道题是一道树形 DP 的经典题目，首先，我们只要稍微读一下题，就会发现：当 $n$ 等于 $2$ 的时候，我们为了权值尽量小，就都取 $1$ 和 $1$，同时**由于不管怎么分配只要两点的权值相同，就满足一个点的权值等于所有相邻点的权值之和**，因此我们可以毫不犹豫地将当 $n$ 等于 $2$ 的时候的情况直接输出出来。

接着，我们来思考如何来做之后的判断，我们先令 $\operatorname{f}(u, x)$ 和 $dp[u][x]$ 表示以 $u$ 为节点的子树，且 $u$ 取 $x$ 或者不取 $x$ 为好结点，的最大好结点数量，返回最大好结点数量以及需要的最小权值。接着，我们在比较之前要注意一个问题：由于我们要最小权值，而**权值为正整数**，所以开始比较前**所有的的权值都赋值为负数**。同时，我们还要注意到一个性质：**当两个点不同时，我们选择父节点为最好点时，子节点就不能选了**。因为我们要求最好点是这个点的权值要等于所有相邻点的权值之和，如果一个点的权值已经等于它相邻点的权值和，这其中也包括子节点，因此两者互相矛盾，只能任选其一。

综上所述，我**们可以将题目转化为求树上不相邻的最大的独立集**。求出独立集后，为使权值总和最小，我们给树上每个非好结点赋值为 $1$，**则好结点的权值，为它们的相邻的结点数量（即相连的边的数量）**。

转移方程笔者不会细讲，只是告诉各位转移方程就是不断往子节点进行搜索，同时记忆化记录每次结果，并在最终统计答案 $ans$ 时上传，并从左右儿子中选择结果更大的，放入 $res$ 变量中，并同时用 $ans$ 数组记录每个点的权值就可以了。

------------

## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int maxn = 2e5 + 1;
vector<int> edge[maxn];
pair<int, int> dp[maxn][2];
int ans[maxn];
int fa[maxn];
int n, u, v;
pair<int, int> f(int u, int x)
{
    if (dp[u][x].first != -1)
    {
        return dp[u][x];
    }
    dp[u][x].first = x;
    dp[u][x].second = x ? (int)edge[u].size() : 1;
    dp[u][x].second = -dp[u][x].second;
    pair<int, int> son;
    for (auto v : edge[u])
    {
        if (fa[u] == v)
        {
            continue;
        }
        fa[v] = u;
        if (x)
        {
            son = f(v, 0);
        }
        else
        {
            son = max(f(v, 0), f(v, 1));
        }
        dp[u][x].first += son.first;
        dp[u][x].second += son.second;
    }
    return dp[u][x];
}
void cal(pair<int, int> p, int u)
{
    if (dp[u][0] == p)
    {
        ans[u] = 1;
        for (auto v : edge[u])
        {
            if (fa[u] == v)
            {
                continue;
            }
            cal(max(dp[v][0], dp[v][1]), v);
        }
    }
    else
    {
        ans[u] = (int)edge[u].size();
        for (auto v : edge[u])
        {
            if (fa[u] == v)
            {
                continue;
            }
            cal(dp[v][0], v);
        }
    }
}
int main()
{
    n = read();
    for (int i = 1; i < n; i++)
    {
        u = read();
        v = read();
        u--;
        v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    if (n == 2)
    {
        cout << 2 << ' ' << 2 << endl << 1 << ' ' << 1;
        return 0;
    }
    for (int i = 0; i < n; ++i)
    {
        dp[i][0] = dp[i][1] = {-1, -1};
        fa[i] = -1;
    }
    pair<int, int> res = max(f(0, 0), f(0, 1));
    cout << res.first << ' ' << -res.second << endl;;
    cal(res, 0);
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122404787)

---

## 作者：DaiRuiChen007 (赞：0)

# CF1646D 题解



## 思路分析

注意到如下的观察：

> 观察：
>
> 对于任意 $n\ge 3$，树上不会有任何两个相邻的好节点。
>
> 假设树上有一条边 $(u,v)$，由于 $n\ge 3$，因此至少有一个点的度数 $\ge 2$，设 $deg(u)\ge 2$。
>
> 此时若 $u$ 和 $v$ 均为好节点，由于 $w_u=w_v+\sum_{(v',u)} w_{v'}$，而由于 $w_i\in\mathbb {Z^+}$，所以 $w_u>w_v$，同理由于 $v$ 是好节点，所以 $w_v\ge w_u$，故矛盾。
>
> 特别地，若 $n=2$ 则 $u,v$ 度数均为 $1$，所以 $w_u=w_v$ 时可以选择两个好节点相邻。

简单讨论剩下的情况：

- 若 $u$ 不为好节点，那么 $w_u$ 为任意正整数，由于我们要最小化答案，因此不妨令 $w_u=1$。
- 若 $u$ 为好节点，那么 $u$ 相邻的所有点都不是好节点，其权值都为 $1$，因此 $w_u=deg(u)$。

可以证明这样的方案是最优的，注意到只要确定所有非好节点的权值就可以确定所有的节点的权值，假如某个非好节点权值改变使得 $w_u\gets w_u+1$，那么所有与 $u$ 相邻的好节点的权值也要 $+1$，因此令 $w_u$ 尽可能小，显然选择 $1$ 最优。

剩下确定每个点是不是好节点的过程可以考虑使用 dp，令 $dp_{u,1/0}$ 表示以 $u$ 为根的子树中选择或没选择 $u$ 作为好节点时的好节点个数的最大值，由于两个好节点不能相邻，那么这个过程就变成了很经典的树上选点问题，可以写出转移方程：
$$
\begin{cases}
dp_{u,0}&=\sum_{v\in son(u)} \max(dp_{v,0},dp_{v,1})\\
dp_{u,1}&=1+\sum_{v\in son(u)} dp_{v,0}
\end{cases}
$$
而最小化权值只需要在比较两个方案优劣的时候作为比较的第二关键字顺便转移一下即可。

构造方案时按照转移顺序计算每个节点是由子节点的 $0$ 状态还是 $1$ 状态转移过来，递归构造即可。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=2e5+1;
vector <int> G[MAXN];
int val[MAXN];
struct node {
	int cnt,val;
	node(int _cnt,int _val) { cnt=_cnt,val=_val; }
	node() { node(0,0); }
	inline friend bool operator <(const node &A,const node &B) {
		if(A.cnt==B.cnt) return A.val<B.val;
		return A.cnt>B.cnt;
	}
	inline friend node operator +(const node &A,const node &B) {
		return node(A.cnt+B.cnt,A.val+B.val);
	}
}	dp[MAXN][2];
inline node _min(const node &A,const node &B) {
	return A<B?A:B;
}
inline void dfs(int p,int f) {
	dp[p][0]=node(0,1);
	dp[p][1]=node(1,(int)G[p].size());
	for(int v:G[p]) {
		if(v==f) continue;
		dfs(v,p);
		dp[p][0]=dp[p][0]+_min(dp[v][0],dp[v][1]);
		dp[p][1]=dp[p][1]+dp[v][0];
	}
}
inline void print(int p,int f,int col) {
	val[p]=col==1?G[p].size():1;
	for(int v:G[p]) {
		if(v==f) continue;
		if(col==1) print(v,p,0);
		else  print(v,p,dp[v][0]<dp[v][1]?0:1);
	}
}
signed main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	if(n==2) {
		puts("2 2");
		puts("1 1");
		return 0;
	}
	dfs(1,0);
	print(1,0,dp[1][0]<dp[1][1]?0:1);
	printf("%d %d\n",_min(dp[1][0],dp[1][1]).cnt,_min(dp[1][0],dp[1][1]).val);
	for(int i=1;i<=n;++i) printf("%d ",val[i]); puts("");
	return 0;
}
```



---

## 作者：glorious_dream (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1646D)

首先我们可以发现，当 $n \geq 2$ 的时候，任意两个相邻的点不可能同为好节点（因为一定有其它节点破坏他们两个相等）。当 $n = 2$ 的时候，特判掉即可。

我们考虑如何进行树形 DP，设 $f[u][1/0]$ 表示在以 $u$ 为根的子树中，$u$ 是好节点 ($f[u][1]$) 或者不是好节点（$f[u][0]$）的时候，最多能有多少个好节点。在转移的过程中 ，因为有上述的性质，所以当钦定 $u$ 为好节点时，它的孩子 $v$ 只能不是好节点，当 $u$ 不是好节点时，它的孩子 $v$ 可以是好节点，也可以不是好节点。

我们将 DP 的数组定义一个 pair，first 表示好节点的数目，second 表示在这个数目下所需要的和。转移的时候分别对于 first 和 second 转移，当 first 相同的时候，要转移 second 小的。我们贪心的想，最后的方案一定是，所有不是好节点的值是 $1$，所有是好节点的值是 $deg[u]$。

具体转移如下：
 $\begin{cases} f[u][1] = \sum{f[v][0]}+1\\ f[u][0] = \max(f[v][0],f[v][1]) \end{cases}$

最后就是输出方案了，先将根节点 (规定为 $1$) 是好节点还是不是好节点最优，然后往下 dfs，如果这个节点是好节点，那么孩子节点就都不能是好节点，一直把整棵树遍历完，最后输出答案即可。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#define re register
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 4e5+10;
typedef pair<int,int> pii;
int n,cnt;
int head[M],du[M],ans[M];
pii f[M][2];
struct edge{
    int to,nxt;
}e[M];
inline void add(int u,int v){
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
inline bool check(pii x,pii y){
    if(x.first != y.first) return x.first > y.first;
    return x.second < y.second;
}
inline void dfs(int u,int fa){
    f[u][1] = make_pair(1,du[u]);
    f[u][0] = make_pair(0,1);
    for(re int i(head[u]) ; i ; i=e[i].nxt){
        int v = e[i].to;
        if(v == fa) continue;
        dfs(v,u);
        f[u][1].first += f[v][0].first;
        f[u][1].second += f[v][0].second;
        if(check(f[v][0],f[v][1])) f[u][0].first += f[v][0].first,f[u][0].second += f[v][0].second;
        else f[u][0].first += f[v][1].first,f[u][0].second += f[v][1].second;
    }
}
inline void print(int u,int fa,int zt){
    if(zt) ans[u] = du[u];
    else ans[u] = 1;
    for(re int i(head[u]) ; i ; i=e[i].nxt){
        int v = e[i].to;
        if(v == fa) continue;
        if(zt) print(v,u,0);
        else{
            if(check(f[v][0],f[v][1])) print(v,u,0);
            else print(v,u,1);
        }
    }
}
signed main(){
    n = read();
    rep(i,1,n-1){
        int u = read(),v = read();
        add(u,v),add(v,u);
        du[u]++,du[v]++;
    }
    if(n == 2){
        printf("2 2\n");
        printf("1 1\n");
        return 0;
    }
    dfs(1,0);
    if(check(f[1][0],f[1][1])){
        printf("%d %d\n",f[1][0].first,f[1][0].second);
        print(1,0,0);
    }
    else{
        printf("%d %d\n",f[1][1].first,f[1][1].second);
        print(1,0,1);
    }
    rep(i,1,n) printf("%d ",ans[i]);
    return 0;
}
```


---

## 作者：Rad_Forever (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1646D)

## 题目大意

给定一棵树，你需要给树的每一个节点确定一个正整数权值 $w_i$。一个节点的 $u$ 的贡献就是 

$$
[w_u=\sum_{(u,v)}w_v]
$$

构造一种方案使得所有节点贡献总和最大，在最大的情况下，最小化 $\sum w$ 的值。

## 思路

先想一想树上相邻的两个点是否都可能造成 $1$ 的贡献。

答案是肯定的，但是只有一种情况就是

```
2
1 2
```

这组数据。

我们对这组数据进行特判之后，剩下的数据就有了一个特殊的性质——**相邻两个点至多只会有一个点造成贡献。**

接下来考虑树形 $dp$。默认以 $1$ 为根。

- 设 $f_{i,0}$ 表示 $i$ 造成 $1$ 的贡献的时候 $i$ 的子树内最多可以造成多少贡献。
- 设 $f_{i,1}$ 表示 $i$ 造成 $0$ 的贡献的时候 $i$ 的子树内最多可以造成多少贡献。
- 设 $g_{i,0}$ 表示在满足 $f_{i,0}$ 最大的情况下，$i$ 的子树中所有节点权值总和的最小值。
- 设 $g_{i,1}$ 表示在满足 $f_{i,1}$ 最大的情况下，$i$ 的子树中所有节点权值总和的最小值。

转移比较显然。

对于 $f_{i,0}$：

$$
f_{i,0}=\sum_{j \in son_i} f_{j,1} 
$$

对于 $f_{i,1}$：

$$
f_{i,1}=\sum_{j \in son_i} \max\{f_{j,0},f_{j,1}\}
$$

对于 $g$ 的转移讨论一下即可。

接下来考虑怎么给点确定权值。

我们计 $du_x$ 表示与 $x$ 相连的点的数量。

- 如果要 $x$ 产生 $1$ 的贡献，$w_x \leftarrow du_x$。
- 否则 $w_x \leftarrow 1$。

最后根据求出来的 $f,g$ 递归求解方案即可。

[评测记录](https://codeforces.live/problemset/submission/1646/148380498)

---

## 作者：daniEl_lElE (赞：0)

很有趣的一个树形 DP 问题。

## 思路

考虑 $dp_{i,j},minv_{i,j}$，表示看到第 $i$ 号节点，当前节点是否准备成为一个**好**节点用 $j$ 表示（$j=0,1$），最多可以有多少个节点是**好**的，以及在**好**节点最多的情况下，最少的和。易得，当某个节点不想成为**好**节点时，最好填得最小，即 $1$。

考虑转移，我要想成为一个**好**的节点，我的楼上楼下均不可以是一个**好**的节点，那么，$dp_{i,1}=\sum dp_{son_i,0}+1$，$minv_{i,1}=\sum minv_{son_i,0}+sonnum_i+1$，其中 $sonnum_i$ 表示 $i$ 的孩子个数。不想成为一个**好**的节点，就需要考虑我的儿子是或不是**好**的节点均可，此时，按照 $max(dp_{son_i,1},dp_{son_i,0})$ 来贡献，若两个相等，$minv_{son_i,0/1}$ 小的一方贡献给我。和成为**好**节点不同的是，这里 $dp_{i,0}$ 不能再增加 $1$ 了，同样，$minv_{i,0}$ 只能增加 $1$。

这样貌似已经解决问题了，但是我们只求出最多点数和对应的最小值，然而并不能构造出点权，此时我们就要考虑转移时记录 $choose$ 数组表示父亲是要我的 $0$ 或 $1$ 状态，这样就可以再深搜一遍获得答案。

总复杂度 $O(n)$，不能通过本题。

等等，为啥不能通过？考虑以下数据：

```
2
1 2
```

这时，$1,2$ 节点可以同时是**好**的。特判一下即可。加上特判即可通过本题。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct E{
	int to,next;
}edge[1000005];
int h[1000005],cnt;
void add(int u,int v){
	cnt++;
	edge[cnt].to=v;
	edge[cnt].next=h[u];
	h[u]=cnt;
} 
int f1[1000005],min1[1000005],f2[1000005],min2[1000005],xs[1000005];
void dfs(int now,int fa){
	int tot1=0,minv1=0;
	for(int i=h[now];i;i=edge[i].next){
		int u=edge[i].to;
		if(u==fa) continue;
		dfs(u,now);
		if(f1[u]>f2[u]){
			tot1+=f1[u];
			minv1+=min1[u];
			xs[u]=1;
		}
		else if(f1[u]==f2[u]){
			if(min1[u]<min2[u]){
				tot1+=f1[u];
				minv1+=min1[u];
				xs[u]=1;
			}
			else{
				tot1+=f2[u];
				minv1+=min2[u];
				xs[u]=2;
			}
		}
		else{
			tot1+=f2[u];
			minv1+=min2[u];
			xs[u]=2;
		}
	}
	f1[now]=tot1,min1[now]=minv1+1;
	int tot2=0,minv2=0,cn2=0;
	for(int i=h[now];i;i=edge[i].next){
		int u=edge[i].to;
		if(u==fa) continue;
		cn2++;
		tot2+=f1[u];
		minv2+=min1[u];
	}
	f2[now]=tot2+1,min2[now]=minv2+cn2+1;
}
int ans[1000005];
void dfs2(int now,int fa,int cs){
	if(cs==1){
		ans[now]=1;
		for(int i=h[now];i;i=edge[i].next){
			int u=edge[i].to;
			if(u==fa) continue;
			if(xs[u]==1) dfs2(u,now,1);
			else dfs2(u,now,2);
		}
	}
	else{
		int cn=0;
		for(int i=h[now];i;i=edge[i].next){
			int u=edge[i].to;
			if(u==fa) continue;
			dfs2(u,now,1);
			cn++;
		}
		ans[now]=cn+1;
	}
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	if(n==2){
		cout<<2<<" "<<2<<endl;
		cout<<"1 1";
		return 0;
	}
	dfs(1,0);
	if(f1[1]>f2[1]){
		cout<<f1[1]<<" "<<min1[1]<<endl;
		dfs2(1,0,1);
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
	}
	else if(f1[1]==f2[1]){
		if(min1[1]<min2[1]){
			cout<<f1[1]<<" "<<min1[1]<<endl;
			dfs2(1,0,1);
			for(int i=1;i<=n;i++){
				cout<<ans[i]<<" ";
			}
		}
		else{
			cout<<f2[1]<<" "<<min2[1]-1<<endl;
			dfs2(1,0,2);
			ans[1]--;
			for(int i=1;i<=n;i++){
				cout<<ans[i]<<" ";
			}	
		}
	}
	else{
		cout<<f2[1]<<" "<<min2[1]-1<<endl;
		dfs2(1,0,2);
		ans[1]--;
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}		
	}
	return 0;
}
```

---

## 作者：small_lemon_qwq (赞：0)

不难发现当 $n>2$ 时，相邻的节点不可能同为好点，并且我们固定一个好点的选择方式，只要满足相邻的节点不同为好点，就可以构造出一组权值满足这个答案，只要构造不是好点的点权值为 $1$，是好点的点权值为它的度数即可。

那么就是一个很简单的树形 dp 了，记得特判 $n=2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,f[200005][2],s[200005][2],w[200005];
vector<int>g[200005],g2[200005]/*存储每个子节点在该节点不是好点的情况下选不选为好点*/;
void dfs(int u,int fa){
	f[u][1]=1;
	s[u][0]=1;
	s[u][1]=g[u].size();
	for(int v:g[u]){
		if(v==fa)continue;
		dfs(v,u);
		if(f[v][1]>f[v][0]||(f[v][1]==f[v][0]&&s[v][1]<s[v][0])){
			g2[u].push_back(1);
			f[u][0]+=f[v][1];
			s[u][0]+=s[v][1];
		}else{
			g2[u].push_back(0);
			f[u][0]+=f[v][0];
			s[u][0]+=s[v][0];
		}
		f[u][1]+=f[v][0];
		s[u][1]+=s[v][0];
	}
}
void dfs2(int u,int fa,int p){
	if(p){
		w[u]=g[u].size();
	}else{
		w[u]=1;
	}
	int j=-1;
	for(int v:g[u]){
		if(v==fa)continue;
		j++;
		dfs2(v,u,g2[u][j]&&!p);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	if(n==2){
		cout<<R"(2 2
1 1)";
		return 0;
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,-1);
	if(f[1][1]>f[1][0]||(f[1][1]==f[1][0]&&s[1][1]<s[1][0])){
		cout<<f[1][1]<<" "<<s[1][1]<<"\n";
		dfs2(1,-1,1);
	}else{
		cout<<f[1][0]<<" "<<s[1][0]<<"\n";
		dfs2(1,-1,0);
	}
	for(int i=1;i<=n;i++){
		cout<<w[i]<<" ";
	}
	return 0;
}
```

---

