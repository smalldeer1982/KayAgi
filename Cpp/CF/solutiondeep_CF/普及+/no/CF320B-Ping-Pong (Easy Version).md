# 题目信息

# Ping-Pong (Easy Version)

## 题目描述

In this problem at each moment you have a set of intervals. You can move from interval $ (a,b) $ from our set to interval $ (c,d) $ from our set if and only if $ c&lt;a&lt;d $ or $ c&lt;b&lt;d $ . Also there is a path from interval $ I_{1} $ from our set to interval $ I_{2} $ from our set if there is a sequence of successive moves starting from $ I_{1} $ so that we can reach $ I_{2} $ .

Your program should handle the queries of the following two types:

1. "1 x y" $ (x&lt;y) $ — add the new interval $ (x,y) $ to the set of intervals. The length of the new interval is guaranteed to be strictly greater than all the previous intervals.
2. "2 a b" $ (a≠b) $ — answer the question: is there a path from $ a $ -th (one-based) added interval to $ b $ -th (one-based) added interval?

Answer all the queries. Note, that initially you have an empty set of intervals.

## 样例 #1

### 输入

```
5
1 1 5
1 5 11
2 1 2
1 2 9
2 1 2
```

### 输出

```
NO
YES
```

# AI分析结果

### 题目内容
# Ping-Pong (Easy Version)

## 题目描述
在这个问题中，在每个时刻你都有一组区间。当且仅当 \( c < a < d \) 或者 \( c < b < d \) 时，你可以从我们集合中的区间 \( (a,b) \) 移动到集合中的区间 \( (c,d) \) 。此外，如果存在从集合中的区间 \( I_{1} \) 开始的一系列连续移动，使得我们能够到达区间 \( I_{2} \) ，那么从区间 \( I_{1} \) 到区间 \( I_{2} \) 就存在一条路径。

你的程序应该处理以下两种类型的查询：
1. “1 x y” \( (x < y) \) —— 将新的区间 \( (x,y) \) 添加到区间集合中。保证新区间的长度严格大于所有先前的区间。
2. “2 a b” \( (a ≠ b) \) —— 回答问题：从第 \( a \) 个（从1开始计数）添加的区间到第 \( b \) 个（从1开始计数）添加的区间是否存在路径？

回答所有查询。注意，最初你有一个空的区间集合。

## 样例 #1
### 输入
```
5
1 1 5
1 5 11
2 1 2
1 2 9
2 1 2
```
### 输出
```
NO
YES
```

### 算法分类
深度优先搜索 DFS、广度优先搜索 BFS

### 综合分析与结论
这些题解主要围绕深度优先搜索（DFS）和广度优先搜索（BFS）来解决问题。核心思路是将区间关系抽象为图的连接关系，通过搜索判断两个区间是否可达。各题解的思路和实现较为相似，主要差异在于代码细节和实现方式。

### 所选的题解
 - **作者：zjy111（5星）**
    - **关键亮点**：思路清晰，代码简洁明了，直接使用DFS解决问题，对题目中的区间转移条件把握准确，易于理解。
    - **重点代码 - 核心实现思想**：定义 `dfs` 函数进行深度优先搜索，在函数中标记当前区间已访问，遍历所有区间，若满足转移条件则递归调用 `dfs` 继续搜索。
```cpp
void dfs(int x){ //深搜
    vis[x]=1;  //标记为已搜索
    for(int i=1;i<=cnt;i++){  //枚举区间
        query y=q[i];
        if(vis[i])continue;  //已经被访问则跳过(递归调用自己的函数,不这么写会爆的!)
        if((y.a<q[x].a && q[x].a<y.b)||(y.a<q[x].b && q[x].b<y.b)) dfs(i);   //找到符合条件的点,转移
    } 
}
```
 - **作者：_Dynamic_Programming（4星）**
    - **关键亮点**：同样采用DFS，对做法和代码的各部分解释详细，适合初学者理解。
    - **重点代码 - 核心实现思想**：`dfs` 函数逻辑与zjy111的类似，标记当前区间，遍历其他区间，满足条件则递归搜索。
```cpp
void dfs(int x)
{ 
    vis[x] = 1; //标记为1 
    for(int i = 1; i <= cnt; i++)
    {  
        point y = q[i];
        if(vis[i] == 1) continue;  
        if((y.a < q[x].a && q[x].a < y.b) || (y.a < q[x].b && q[x].b < y.b)) dfs(i); //如果满足条件，就dfs枚举
    } 
}
```
 - **作者：YCSluogu（4星）**
    - **关键亮点**：采用BFS解决问题，与多数使用DFS的题解形成对比，为该题提供了不同的解决视角。
    - **重点代码 - 核心实现思想**：定义 `Record` 函数记录可转移的区间，`bfs` 函数中初始化队列和标记数组，通过队列进行广度优先搜索，判断是否能从起始区间到达目标区间。
```cpp
// 像这样写可以将转移写得更清晰
void Record(int u, int v) {
    if (vis[v] || u == v ||!((a[u].x > a[v].x && a[u].x < a[v].y) || (a[u].y > a[v].x && a[u].y < a[v].y))) {
        return;
    }
    vis[v] = true;
    q.push(v);
}

bool bfs() {
    memset(vis, false, sizeof(vis));
    while (q.size()) q.pop();
    vis[x] = true;
    q.push(x);
    while (!q.empty()) {
        int u = q.front();
        if (u == y) {
            return true;
        }
        for (int i = 1; i <= cnt; i++) {
            Record(u, i);
        }
        q.pop();
    }
    return false;
}
```

### 最优关键思路或技巧
将区间之间的转移关系抽象为图的边，利用深度优先搜索或广度优先搜索判断图中两点是否连通。在实现过程中，准确把握区间转移的条件，通过标记数组避免重复访问，提高搜索效率。

### 可拓展之处
同类型题通常围绕区间关系、图的连通性判断展开。类似算法套路是将实际问题中的关系抽象为图结构，再运用搜索算法解决。例如在一些任务调度问题中，任务之间的先后顺序依赖关系可抽象为图，通过搜索判断某个任务是否可达。

### 推荐洛谷题目
 - [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：通过图的广度优先搜索求最短路，与本题利用搜索判断连通性思路类似。
 - [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：同样使用BFS解决在特定规则下的可达性问题。
 - [P1451 求细胞数量](https://www.luogu.com.cn/problem/P1451)：利用DFS或BFS遍历二维数组中的连通区域，与本题搜索连通区间的思想有相通之处。

### 个人心得摘录与总结
部分题解提到注意在DFS中避免重复访问，否则可能导致程序爆栈，强调了标记数组在搜索算法中的重要性。这提示在使用递归搜索时，一定要注意控制递归深度，避免不必要的重复计算。 

---
处理用时：62.59秒