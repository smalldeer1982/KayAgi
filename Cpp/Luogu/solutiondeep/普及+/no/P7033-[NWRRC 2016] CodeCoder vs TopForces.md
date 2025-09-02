# 题目信息

# [NWRRC 2016] CodeCoder vs TopForces

## 题目描述



Competitive programming is very popular in Byteland. In fact, every Bytelandian citizen is registered at two programming sites -- CodeCoder and TopForces. Each site maintains its own proprietary rating system. Each citizen has a unique integer rating at each site that approximates their skill. Greater rating corresponds to better skill.

People of Byteland are naturally optimistic. Citizen A thinks that he has a chance to beat citizen B in a programming competition if there exists a sequence of Bytelandian citizens $A = P_{0}, P_{1},...,P_{k} = B$ for some $k \ge 1$ such that for each $i (0 \le i < k) , P_{i}$ has higher rating than $P_{i+1}$ at one or both sites.

Each Bytelandian citizen wants to know how many other citizens they can possibly beat in a programming competition.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
4
2 3
3 2
1 1
4 5
```

### 输出

```
2
2
0
3
```

# AI分析结果

### 算法分类
图论

### 综合分析与结论
该题的核心在于利用图论中的有向图表示强弱关系，并通过深度优先搜索（DFS）来计算每个人能打败的人数。由于强弱关系具有传递性，题解中普遍采用了排序后建图的方式，确保每个点只与比自己弱的点相连，从而减少边的数量。通过DFS遍历图，利用传递性优化计算，避免重复遍历。

### 所选题解

#### 1. 作者：IDNo1 (5星)
**关键亮点**：
- 详细解释了如何通过排序和建图来表示强弱关系。
- 使用DFS进行遍历，并利用传递性优化计算。
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
void dfs(re now)
{
	vis[now]=1;//标记已访问
	sum+=1;//开始的时候令 sum=0，由于强具有传递性，所以用类似前缀和的思路即可解决
	for(re i=0;i<v[now].size();i++)//遍历其可以通以打败的人，解决传递性的问题
	{
		if(!vis[v[now][i]])//此人还没有计算过
		{
			dfs(v[now][i]);//搜索
		}
	}
}
```

#### 2. 作者：Fkxxx (4星)
**关键亮点**：
- 详细解释了如何通过排序和建图来表示强弱关系。
- 使用DFS进行遍历，并利用传递性优化计算。
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
void dfs( int u ){
    if( vis[u] ) return;
    res ++ ;
    vis[u] = true ;
    for( int i = head[u] ; i ; i = gra[i].lip ){
        dfs( gra[i].to ) ;
    }
}
```

#### 3. 作者：Doubeecat (4星)
**关键亮点**：
- 详细解释了如何通过排序和建图来表示强弱关系。
- 使用DFS进行遍历，并利用传递性优化计算。
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
void dfs(int x) {
    if (!vis[x]) ++ans;
    vis[x] = 1;
    for (int i = 0;i < G[x].size();++i) {
        int y = G[x][i];
        if (!vis[y]) dfs(y);
    }
}
```

### 最优关键思路或技巧
- **排序建图**：通过按能力值排序后，只与比自己弱的点相连，减少边的数量。
- **DFS优化**：利用传递性，避免重复遍历，提高计算效率。
- **全局变量记录**：使用全局变量记录访问过的点，减少重复计算。

### 可拓展之处
- **同类型题**：类似的问题可以扩展到其他具有传递性的关系，如社交网络中的影响力传播、任务依赖关系等。
- **算法套路**：排序+建图+DFS的套路可以应用于其他需要处理传递性关系的题目。

### 推荐题目
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
3. [P3381 【模板】最小费用最大流](https://www.luogu.com.cn/problem/P3381)

---
处理用时：19.28秒