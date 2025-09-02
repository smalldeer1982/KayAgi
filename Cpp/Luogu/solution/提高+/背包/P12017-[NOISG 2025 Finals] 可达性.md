# [NOISG 2025 Finals] 可达性

## 题目描述

Sheepland 是一个有 $n$ 座城市的国家。有 $n - 1$ 条道路将各对城市连接在一起。第 $j$ 条道路直接连接城市 $u[j]$ 和 $v[j]$。最初，仅使用这些道路，可以从任意一个城市到达任意一个其他城市。

Sheepland 的所有 $n - 1$ 条道路都计划进行翻修。根据翻修计划，每条道路 $j$ 将处于以下四种状态之一：

1. 双向：城市 $u[j]$ 和 $v[j]$ 的市民可以通过这条道路前往对方的城市。
2. 从城市 $u[j]$ 到城市 $v[j]$ 的单向：只有来自城市 $u[j]$ 的市民可以通过这条道路前往城市 $v[j]$。
3. 从城市 $v[j]$ 到城市 $u[j]$ 的单向：只有来自城市 $v[j]$ 的市民可以通过这条道路前往城市 $u[j]$。
4. 关闭：城市 $u[j]$ 和 $v[j]$ 的市民都不能通过这条道路前往对方的城市。

不幸的是，翻修计划丢失了！

为了尝试恢复计划，你向每座城市的市长询问在翻修计划下从他们的城市可以到达多少座城市。第 $i$ 座城市的市长回答 $l[i]$。然而，一些市长可能提供了错误的数值。

如果存在一个序列 $c_1, c_2, c_3, \ldots, c_k$，其中 $c_1 = u$，$c_k = v$，并且对于所有 $1 \leq x \leq k - 1$，都存在一条可通行的道路从 $c_x$ 到 $c_{x+1}$，那么城市 $v$ 被认为可以从城市 $u$ 到达。特别地，每座城市都可以到达自身。

请帮助 Sheepland 确定是否存在一个翻修计划，使得每位市长报告的可到达城市数量都是正确的！


## 说明/提示


### 子任务

对于所有测试用例，输入将满足以下约束条件：

- $1 \leq n \leq 5000$
- 对于所有 $1 \leq i \leq n$，有 $1 \leq l[i] \leq n$
- 对于所有 $1 \leq j \leq n - 1$，有 $1 \leq u[j], v[j] \leq n$
- 对于所有 $1 \leq j \leq n − 1$，有 $u[j] \neq v[j]$
- 最初，仅使用道路，可以从任何城市到达任何其他城市。

你的程序将在满足以下特殊性质的输入数据上进行测试：

| 子任务 | 分数 | 特殊性质 |
| :-: | :-: | :-: |
| $0$ | $0$ | 样例 |
| $1$ | $4$ | $n \leq 7$ |
| $2$ | $5$ | $n \leq 15$ |
| $3$ | $11$ | $l[1] = l[2] = \cdots = l[n]$ |
| $4$ | $10$ | 如果存在一个翻修计划，则存在一个这样的计划没有双向道路 |
| $5$ | $45$ | $n \leq 400$ |
| $6$ | $25$ | 无 |

### 样例 1 解释

此样例适用于子任务 $2, 5, 6$。

请参考下方的图示。该翻修计划与所有市长报告的可到达城市数量一致。

![](https://cdn.luogu.com.cn/upload/image_hosting/h1yj84mf.png)

### 样例 2 解释

此样例适用于子任务 $2, 4, 5, 6$。

不存在一个与所有市长报告的可到达城市数量一致的翻修计划。

### 样例 3 解释

此样例适用于子任务 $1, 2, 5, 6$。


## 样例 #1

### 输入

```
9
5 2 3 5 2 3 1 1 1
1 4
4 5
2 5
3 6
5 6
6 9
7 8
4 7```

### 输出

```
YES```

## 样例 #2

### 输入

```
9
5 2 3 5 2 3 1 1 2
1 4
4 5
2 5
3 6
5 6
6 9
7 8
4 7```

### 输出

```
NO```

## 样例 #3

### 输入

```
7
3 3 1 3 2 1 2
3 4
1 2
6 2
7 3
5 6
4 2```

### 输出

```
YES```

# 题解

## 作者：Mr_Az (赞：4)

# [P12017 [NOISG 2025 Finals] Reachability](https://www.luogu.com.cn/problem/P12017)

### Algorithm:

树形背包。

### Solution:

被薄纱了。

看到这道题让我会想到了省选的岁月，但其实两道题目并没有任何相似之处。

观察到 $u \rightarrow v$ 的边相当于让 $u$ 能够到达的点加上 $v$ 能够到的点的数量。这能够让我们发现两点之间可能的边的限制。具体而言如下所示：

1. 当 $l_u=l_v$ 时，$u,v$ 之间的边要么为双向边或者没有连边，原因是若为单向边则两个点能够到达点的数量至少差 $1$。
2. 当 $l_u \neq l_v$ 是，$u,v$ 之间的便要么为单向边（$l$ 值大的点连向 $l$ 值小的点）或者没有连边。

加上之前的观察，不难发现是一个树上背包的形式。所以考虑设 $f_{u,i}$ 代表在计算到 $u$ 的时候，$u$ 能够到达的点数量为 $i$ 是否合法。转移只要按照上面的分类讨论一下即可，具体而言如下所示：（$siz_i$ 为 $i$ 这个点的子树大小）

1. 当 $l_u=l_v$ 时：
   1. $u \leftrightarrow v$： $f_{u,i+j}|=f_{u,i}\&f_{v,j}(i \in [0,siz_u],j \in [0,siz_v])$。
   2. $u \not \rightarrow v$：此时必须满足 $f_{v,l_v}=1$。
2. 当 $l_u > l_v$ 时：
   1. $u \rightarrow v$： $f_{u,i+l_v}|=f_{u,i}(i \in [0,siz_u])$。
   2. $u \not \rightarrow v$：此时必须满足 $f_{v,l_v}=1$。
3. 当 $l_u<l_v$ 时：
   1. $u \leftarrow v$：此时必须满足 $f_{v,l_v-l_u}=1$。
   2. $u \not \rightarrow v$：此时必须满足 $f_{v,l_v}=1$。

不满足的情况可以直接输出 `NO` 退出。最后检查根节点是否合法即可。在实际实现的过程中会遇到 $f_{u,i}$ 在一个儿子被更新后去更新其他状态，所以需要辅助数组 $g_i$ 用来暂时存储 $f_{u,i}$ 的状态，更新完后重新赋值。

### Code:

```cpp
namespace Mr_Az{
	const int N=5008;
	int T=1;
	int n;
	int l[N],siz[N];
	bool f[N][2*N],g[2*N];
	vector<int> e[N];
	void dfs(int u,int fa){
		siz[u]=1;
		for(auto v:e[u]){
			if(v==fa) continue;
			dfs(v,u);
			if(l[u]==l[v]){// 所达城市数量一致
				// 1. 连边
				for(rint i=0;i<=siz[u];i++)
					for(rint j=0;j<=siz[v];j++)
						g[i+j]|=(f[u][i]&f[v][j]);
						
				// 2. 断开(下面必须要满足要求)
				if(f[v][l[v]]){
					for(rint i=0;i<=siz[u];i++) g[i]|=f[u][i];
				}
			}
			else{// 所达城市数量不一致
				if(l[u]>l[v]){// 1. u->v 或不连边
					if(!f[v][l[v]]){puts("NO");exit(0);}
					else{
						for(rint i=0;i<=siz[u];i++){
							g[i+l[v]]|=f[u][i];
							g[i]|=f[u][i];
						}
					}
				}
				else{// 2. v->u 或不连边
					if(!f[v][l[v]]&&!f[v][l[v]-l[u]]){puts("NO");exit(0);}
					for(rint i=0;i<=siz[u];i++) g[i]|=f[u][i];
				}				
			}
			siz[u]+=siz[v];
			for(rint i=0;i<=siz[u];i++) f[u][i]=g[i];
			mem(g,0);
		}
	}
	inline void solve(){
		read(n);
		for(rint i=1;i<=n;i++) read(l[i]);
		for(rint i=1,u,v;i<n;i++){
			read(u,v);
			e[u].pb(v);e[v].pb(u);
		}
		for(rint i=1;i<=n;i++) f[i][1]=1;
		dfs(1,0);
		if(f[1][l[1]]) puts("YES");
		else puts("NO");
	}
	inline void mian(){if(!T) read(T);while(T--) solve();}
}
```

---

## 作者：快斗游鹿 (赞：3)

先观察一下：如果两点 $a_u=a_v$，那么这两点中间一定是双向边或者没有边，否则两点间要么没边，要么会有一条 $u\to v(a_u>a_v)$ 的边。

考虑把所有 $a_i$ 相等的连通块拎出来处理。可以发现连单向边的影响就是把 $a_v$ 的贡献加到 $u$ 上，明显是背包的形式。因此考虑对每个连通块做树上背包，设 $f_{i,j}$ 表示点 $i$，当前 $a_i=j$ 可不可行。转移分两类，假设现在要从点 $v$ 转移到点 $u$。如果点 $v$ 可以满足 $f_{v,a_v}=1$，那么这个点可以不选，直接断开，也可以与 $u$ 有边，否则必须要与 $u$ 有边。状态两维都是 $O(sz)$ 的，所以处理一个连通块需要 $O(sz^2)$，因为 $\sum sz =n$，所以总时间复杂度为 $O(n^2)$。

---

## 作者：clarify (赞：0)

树上 $$dp$$，难点在分类讨论。并查集或链表建图后需根据父子可达城市数量做判断。当子节点可达数大于当前节点，子节点必须独立可达部分城市，再考虑是否合并与单独；当子节点可达数小于当前节点，判断子节点是否独立可达即可；当子节点可达数等于当前节点，要么各自独立，要么合并可达。以 $$1$$ 为根节点深搜，使用**或**运算符保证不会打乱上一步 $$dp$$ 状态。

Code:
```
//T593210.cpp
#include <iostream>
#include <cstring>

using namespace std;
const int N = 5010, M = 2 * N;

int e[M], ne[M], h[N], idx;
int l[N], u[N], v[N], dp[N][N], siz[N], rea[N];

void add(int a, int b) // 尾插法邻接链表，也可以使用邻接矩阵
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int x, int pa)
{
    siz[x] = 1;
    dp[x][1] = 1; // x -> k个城市

    for (int i = h[x]; i != -1; i = ne[i])
    {
        int y = e[i];
        if (y == pa) continue;
        dfs(y, x);
        if (l[y] == l[x]) //1. xy相连，共同可达
        {
            for (int i = 0; i <= siz[x]; i ++ ) 
            {
                for (int j = 0; j <= siz[y]; j++ ) 
                {
                    rea[i + j] |= (dp[x][i] && dp[y][j]); 
                }
            }
            if (dp[y][l[y]]) //2. xy独立可达
            {  
                for (int i = 0; i <= siz[x]; i ++ ) {
                    rea[i] |= dp[x][i];  
                }
            }
        }
        else if (l[y] < l[x]) //子节点少
        {
            if (!dp[y][l[y]]) //no
            {
                for (int i = 0; i <= siz[x]; i ++ )
                    dp[x][i] = 0;
            }
            else
                for (int i = 0; i <= siz[x]; i ++ )  
                {
                    rea[i + l[y]] |= dp[x][i]; //两个城市合并 y加入x
                    rea[i] |= dp[x][i];  //xy独立可达
                }
        } 
        else if (l[y] > l[x]) //子节点多 1.独立的可达 2.合并一部分
        {
            if (!dp[y][l[y]] && !dp[y][l[y] - l[x]]) //就算合并 子节点必须有一部分可达
            {
                for (int i = 0; i <= siz[x]; i ++ ) 
                    dp[x][i] = 0;
            } 
            else
                for (int i = 0; i <= siz[x]; i ++ )   //x独立/合并可达， y剩余部分独立可达
                    rea[i] |= dp[x][i];
        }
        
        siz[x] += siz[y];
        for (int i = 0; i <= siz[x]; i ++ ) 
        {
            dp[x][i] = rea[i];
            rea[i] = 0;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; i ++ )
    {
        cin >> l[i]; 
    }
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i ++ ) 
    {
        cin >> u[i] >> v[i]; //需规划可达条件
        add(u[i], v[i]), add(v[i], u[i]);
    }
    dfs(1, 0);
    if (dp[1][l[1]]) //以1为根 成立则全部可达
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
```

---

