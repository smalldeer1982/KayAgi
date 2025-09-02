# 题目信息

# Two Fairs

## 题目描述

There are $ n $ cities in Berland and some pairs of them are connected by two-way roads. It is guaranteed that you can pass from any city to any other, moving along the roads. Cities are numerated from $ 1 $ to $ n $ .

Two fairs are currently taking place in Berland — they are held in two different cities $ a $ and $ b $ ( $ 1 \le a, b \le n $ ; $ a \ne b $ ).

Find the number of pairs of cities $ x $ and $ y $ ( $ x \ne a, x \ne b, y \ne a, y \ne b $ ) such that if you go from $ x $ to $ y $ you will have to go through both fairs (the order of visits doesn't matter). Formally, you need to find the number of pairs of cities $ x,y $ such that any path from $ x $ to $ y $ goes through $ a $ and $ b $ (in any order).

Print the required number of pairs. The order of two cities in a pair does not matter, that is, the pairs $ (x,y) $ and $ (y,x) $ must be taken into account only once.

## 样例 #1

### 输入

```
3
7 7 3 5
1 2
2 3
3 4
4 5
5 6
6 7
7 5
4 5 2 3
1 2
2 3
3 4
4 1
4 2
4 3 2 1
1 2
2 3
4 1
```

### 输出

```
4
0
1
```

# AI分析结果

### 题目中文重写
# 两个集市

## 题目描述
在伯兰有 $n$ 个城市，其中一些城市对之间由双向道路相连。保证你可以沿着道路从任何一个城市到达其他任何城市。城市从 $1$ 到 $n$ 编号。

目前伯兰正在举办两个集市，分别在两个不同的城市 $a$ 和 $b$ 举行（$1 \le a, b \le n$；$a \ne b$）。

找出满足以下条件的城市对 $(x, y)$ 的数量：如果你从 $x$ 到 $y$，则必须经过这两个集市（访问顺序无关紧要）。形式上，你需要找出这样的城市对 $(x, y)$ 的数量，使得从 $x$ 到 $y$ 的任何路径都经过 $a$ 和 $b$（任意顺序）。

打印所需的城市对数量。城市对中两个城市的顺序无关紧要，即对 $(x, y)$ 和 $(y, x)$ 只应计算一次。

## 样例 #1
### 输入
```
3
7 7 3 5
1 2
2 3
3 4
4 5
5 6
6 7
7 5
4 5 2 3
1 2
2 3
3 4
4 1
4 2
4 3 2 1
1 2
2 3
4 1
```

### 输出
```
4
0
1
```

### 综合分析与结论
这些题解的核心思路一致，都是通过搜索（主要是 DFS，部分结合 BFS）找出图中被点 $a$ 和 $b$ 分隔开的两部分点集，然后根据乘法原理计算满足条件的点对数量。

#### 思路对比
- 多数题解先从 $a$ 出发搜索，碰到 $b$ 停止，标记经过的点，再从 $b$ 出发搜索，碰到 $a$ 停止，标记经过的点，最后通过标记情况区分出 $a$ 左边和 $b$ 右边的点集。
- 部分题解直接通过一次搜索未到达的点来确定 $a$ 左边或 $b$ 右边的点集。

#### 算法要点
- **图的存储**：主要使用邻接表（vector 或数组模拟）。
- **搜索算法**：DFS 为主，部分结合 BFS。
- **标记数组**：用于记录节点是否被访问。

#### 解决难点
- **区分点集**：通过设置搜索终止条件（碰到 $a$ 或 $b$ 停止）和标记数组来区分 $a$ 左边、$b$ 右边和 $a$、$b$ 中间的点集。
- **乘法原理应用**：理解满足条件的点对是由 $a$ 左边的点和 $b$ 右边的点组成，从而使用乘法原理计算点对数量。

### 所选题解
- **作者：Orange_qwq（5星）**
    - **关键亮点**：思路清晰，配有详细的图示说明，同时给出了 BFS 和 DFS 两种搜索方式的代码实现，代码结构清晰，注释详细。
    - **核心代码**：
```cpp
void bfs(int s) {
    int l = 0, r = 1;
    q[r] = s;    // 起点入队
    fl[s] = fl[b] = 1; //起点和终点打标记
    while (l < r) { // 手写队列：如果队列不为空
        ++l;
        int tmp = q[l];
        for (int k = h[tmp]; k; k = ne[k]) {
            int ch = e[k];
            if (!fl[ch]) fl[ch] = 1, q[++r] = ch; // 塞进队列并打上标记
        } 
    }
}

void dfs(int x) {
    for (int k = h[x]; k; k = ne[k]) {
        int ch = e[k];
        if (!fl[ch]) fl[ch] = 1, dfs(ch);
        // 只要没有访问到的，打上标记，继续 dfs
    }
}
```
核心实现思想：`bfs` 函数从起点开始，使用队列进行广度优先搜索，将未访问的节点加入队列并标记；`dfs` 函数从起点开始，递归地对未访问的节点进行深度优先搜索并标记。

- **作者：EdenSky（4星）**
    - **关键亮点**：通过分析样例数据，直观地展示了思路的推导过程，代码简洁，逻辑清晰。
    - **核心代码**：
```cpp
inline int dfsb(int x){
    vis[x]=1;
    int ret=1;
    if(x==a) {vis[x]=0; return 0;}
    for(int &i: g[x]){
        if(vis[i]) continue;
        int s=dfsb(i);
        if(s==0&&x!=b) {vis[x]=0; return 0;}
        ret+=s;
    }
    return ret;
}

inline int dfsa(int x){
    vis_[x]=1;
    int ret=1;
    if(x==b) {vis_[x]=0; return 0;}
    for(int &i: g[x]){
        if(vis_[i]) continue;
        int s=dfsa(i);
        if(s==0&&x!=a) {vis_[x]=0; return 0;}
        ret+=s;
    }
    return ret;
}
```
核心实现思想：`dfsb` 函数从 $b$ 开始搜索，若遇到 $a$ 则返回 0，否则递归搜索相邻节点并累加结果；`dfsa` 函数从 $a$ 开始搜索，若遇到 $b$ 则返回 0，否则递归搜索相邻节点并累加结果。

- **作者：formkiller（4星）**
    - **关键亮点**：详细阐述了图的分割原理，通过两次 DFS 分别标记节点，最后通过标记情况区分出 $a$ 左边和 $b$ 右边的点集，代码逻辑清晰。
    - **核心代码**：
```cpp
inline void Dfs1(int x)
{
    v1[x] = 1;
    for (int i = hd[x]; i ; i = nt[i])
    {
        int y = ver[i];
        if (v1[y]||y==t) continue;
        Dfs1(y);
    }
}

inline void Dfs2(int x)
{
    v2[x] = 1;
    for (int i = hd[x]; i ; i = nt[i])
    {
        int y = ver[i];
        if (v2[y]||y==s) continue;
        Dfs2(y);
    }
}
```
核心实现思想：`Dfs1` 函数从 $s$ 开始搜索，碰到 $t$ 停止，标记经过的节点；`Dfs2` 函数从 $t$ 开始搜索，碰到 $s$ 停止，标记经过的节点。

### 最优关键思路或技巧
- **图的分割思想**：将图通过点 $a$ 和 $b$ 分割成三部分，只关注 $a$ 左边和 $b$ 右边的点集，简化问题。
- **搜索终止条件**：在搜索过程中设置碰到 $a$ 或 $b$ 停止的条件，方便区分不同的点集。
- **乘法原理应用**：利用乘法原理计算满足条件的点对数量，避免了复杂的枚举。

### 拓展思路
同类型题或类似算法套路：
- 计算图中经过特定节点的路径数量问题，可采用类似的图分割和搜索方法。
- 割点相关问题，判断图中割点对图的连通性的影响，进而计算满足条件的路径或点对数量。

### 推荐题目
1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：考察图的染色和连通性判断。
2. [P2812 校园网络【[USACO]Network of Schools加强版](https://www.luogu.com.cn/problem/P2812)：涉及图的强连通分量和缩点。
3. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：模板题，用于练习图的缩点操作。

### 个人心得摘录与总结
- **formkiller**：提到自己在 Div 2 比赛中靠签到并做出此题上分，说明此题难度适中，适合在比赛中得分。
- **OIer_ACMer**：强调思路简单但未过多赘述证明和原理，同时提醒在代码实现中要注意避免重复遍历导致死循环，以及无向图存边时要双向存储。 

---
处理用时：43.88秒