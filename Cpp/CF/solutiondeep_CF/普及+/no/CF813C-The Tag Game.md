# 题目信息

# The Tag Game

## 题目描述

Alice got tired of playing the tag game by the usual rules so she offered Bob a little modification to it. Now the game should be played on an undirected rooted tree of $ n $ vertices. Vertex 1 is the root of the tree.

Alice starts at vertex 1 and Bob starts at vertex $ x $ ( $ x≠1 $ ). The moves are made in turns, Bob goes first. In one move one can either stay at the current vertex or travel to the neighbouring one.

The game ends when Alice goes to the same vertex where Bob is standing. Alice wants to minimize the total number of moves and Bob wants to maximize it.

You should write a program which will determine how many moves will the game last.

## 说明/提示

In the first example the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF813C/b7ec0a99b40c82b622ba7707f0f0b2d0e630852a.png)The red vertex is Alice's starting position, the blue one is Bob's. Bob will make the game run the longest by standing at the vertex 3 during all the game. So here are the moves:

B: stay at vertex 3

A: go to vertex 2

B: stay at vertex 3

A: go to vertex 3

In the second example the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF813C/67357a90193bb980ddc9f6e8d8aabc3f3d4836ca.png)The moves in the optimal strategy are:

B: go to vertex 3

A: go to vertex 2

B: go to vertex 4

A: go to vertex 3

B: stay at vertex 4

A: go to vertex 4

## 样例 #1

### 输入

```
4 3
1 2
2 3
2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 2
1 2
2 3
3 4
2 5
```

### 输出

```
6
```

# AI分析结果

### 题目内容
# 标签游戏

## 题目描述
爱丽丝厌倦了按照常规规则玩标签游戏，所以她向鲍勃提出了一个小改动。现在游戏应该在一棵有 $n$ 个顶点的无向有根树上进行。顶点1是树的根。

爱丽丝从顶点1开始，鲍勃从顶点 $x$（$x≠1$）开始。移动是轮流进行的，鲍勃先行动。在一次移动中，玩家可以选择留在当前顶点，也可以移动到相邻的顶点。

当爱丽丝移动到与鲍勃相同的顶点时，游戏结束。爱丽丝希望最小化总移动次数，而鲍勃希望最大化总移动次数。

你需要编写一个程序，确定游戏将持续多少步。

## 说明/提示
在第一个示例中，树的结构如下：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF813C/b7ec0a99b40c82b622ba7707f0f0b2d0e630852a.png)
红色顶点是爱丽丝的起始位置，蓝色顶点是鲍勃的起始位置。鲍勃通过在整个游戏过程中都停留在顶点3，可以使游戏持续最长时间。以下是移动步骤：
- B：留在顶点3
- A：移动到顶点2
- B：留在顶点3
- A：移动到顶点3

在第二个示例中，树的结构如下：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF813C/67357a90193bb980ddc9f6e8d8aabc3f3d4836ca.png)
最优策略下的移动步骤如下：
- B：移动到顶点3
- A：移动到顶点2
- B：移动到顶点4
- A：移动到顶点3
- B：留在顶点4
- A：移动到顶点4

## 样例 #1
### 输入
```
4 3
1 2
2 3
2 4
```
### 输出
```
4
```

## 样例 #2
### 输入
```
5 2
1 2
2 3
3 4
2 5
```
### 输出
```
6
```

### 算法分类
搜索（深度优先搜索 DFS）

### 题解综合分析与结论
- **思路方面**：多数题解认为鲍勃的行动模式决定了游戏结果，主要有两种思路。一是分析鲍勃的路径，如一直往上走或往上走再拐弯往下走，通过深度优先搜索（DFS）计算相关距离来确定答案；二是通过两遍DFS分别计算爱丽丝和鲍勃到各点的距离，比较距离来确定鲍勃能停留且不被抓到的点，进而得出答案。
- **算法要点**：普遍利用DFS遍历树，计算节点深度、子树深度等信息。部分题解使用邻接表存图，还有题解用到LCA（最近公共祖先）算法，但不是核心思路。
- **解决难点**：关键在于理解鲍勃的最优策略，即如何躲避爱丽丝以最大化游戏步数。不同题解从不同角度分析鲍勃的移动路径，通过计算各种距离关系来解决该难点。

### 所选的题解
- **作者：Dzhao（5星）**
  - **关键亮点**：思路清晰，详细分析了鲍勃的两种路径情况，通过DFS计算节点深度 `dep` 和节点往下走的最远距离 `down`，逻辑严谨。代码实现简洁明了，使用邻接表存图，快读等优化。
  - **个人心得**：无
  ```cpp
  void dfs(int u,int fa)
  {
      f[u]=fa; 
      dep[u]=dep[fa]+1;
      for(int i=h[u];i;i=a[i].nxt)
      {
          int v=a[i].ed;
          if(v==fa) continue;
          dfs(v,u);
          down[u]=max(down[u],down[v]+1); 
      }
  }
  void solve(int u)
  {
      if(!u) return; 
      if(dep[t]-dep[u]>=dep[u]-dep[1]) return; 
      ans=max(ans,(dep[u]-dep[1]+down[u])*2); 
      solve(f[u]); 
  }
  ```
  核心代码实现思想：`dfs` 函数计算每个节点的父亲、深度以及往下走的最远距离；`solve` 函数从鲍勃的起始点往上遍历，判断在每个点拐弯的情况，更新最大步数。
- **作者：FwbAway（4星）**
  - **关键亮点**：代码简洁，直接通过两遍DFS计算爱丽丝和鲍勃到各点的距离，通过比较距离确定答案，思路直接。
  - **个人心得**：无
  ```cpp
  void dfs(int u, int fa, int step, int *d) {
      d[u] = step;
      for (int v : e[u]) if (v!= fa) dfs(v, u, step + 1, d);
  }
  int main() {
      scanf("%d%d", &n, &x);
      for (int i = 1; i < n; i++) {
          scanf("%d%d", &u, &v);
          e[u].push_back(v), e[v].push_back(u);
      }
      dfs(1, -1, 0, da), dfs(x, -1, 0, db);
      for (int i = 1; i <= n; i++) if (da[i] > db[i]) ans = max(ans, da[i] * 2);
      printf("%d", ans);
      return 0;
  }
  ```
  核心代码实现思想：`dfs` 函数用于计算从某个起始点到各点的距离，主函数中通过两次调用 `dfs` 分别计算爱丽丝和鲍勃到各点的距离，最后比较得出答案。
- **作者：Frank08（4星）**
  - **关键亮点**：与FwbAway思路类似，同样简洁明了，通过两遍DFS计算距离并比较，确定鲍勃能停留且不被抓到的点来得出答案。
  - **个人心得**：无
  ```cpp
  void dfs(int x,int from){
      d[x] = d[from] + 1;
      for(auto y : edge[x])
          if(y!= from)
              dfs(y,x);
  }
  int main(){
      int x; scanf("%d%d",&n,&x);
      for(int i = 1;i < n;i++){
          int u,v; scanf("%d%d",&u,&v);
          edge[u].push_back(v);
          edge[v].push_back(u);
      }d[0] = -1;
      dfs(x,0);
      for(int i = 1;i <= n;i++)
          f[i] = d[i];
      dfs(1,0);
      int ans = 0;
      for(int i = 1;i <= n;i++)
          if(f[i] < d[i])
              ans = max(d[i] * 2,ans);
      printf("%d",ans);
  }
  ```
  核心代码实现思想：`dfs` 函数计算从某个点到各点的距离，主函数中先计算鲍勃到各点的距离存于 `f` 数组，再计算爱丽丝到各点的距离存于 `d` 数组，最后比较得出答案。

### 最优关键思路或技巧
- **思维方式**：抓住鲍勃的行动模式来分析问题，确定其为了最大化游戏步数的最优移动策略。
- **算法实现**：利用深度优先搜索遍历树结构，高效计算节点的深度、子树深度等关键信息，通过比较距离来确定游戏结果。

### 可拓展之处
同类型题通常围绕树上的博弈或运动问题，类似算法套路是通过DFS或BFS遍历树，分析节点间的距离、深度关系等信息来解决问题。例如给定不同的起始条件或移动规则，分析游戏结果。

### 洛谷相似题目推荐
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及树上的策略分析，与本题类似，需考虑不同节点的状态和相互关系。
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)：同样是树上的策略问题，通过分析节点覆盖情况来求解，与本题分析树上角色移动策略思路类似。
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：在树结构上进行状态分析和决策，与本题在树上分析角色行动以得出最优解的思路有相似之处。 

---
处理用时：64.48秒