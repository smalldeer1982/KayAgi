# 题目信息

# Escape The Maze (easy version)

## 题目描述

The only difference with E2 is the question of the problem..

Vlad built a maze out of $ n $ rooms and $ n-1 $ bidirectional corridors. From any room $ u $ any other room $ v $ can be reached through a sequence of corridors. Thus, the room system forms an undirected tree.

Vlad invited $ k $ friends to play a game with them.

Vlad starts the game in the room $ 1 $ and wins if he reaches a room other than $ 1 $ , into which exactly one corridor leads.

Friends are placed in the maze: the friend with number $ i $ is in the room $ x_i $ , and no two friends are in the same room (that is, $ x_i \neq x_j $ for all $ i \neq j $ ). Friends win if one of them meets Vlad in any room or corridor before he wins.

For one unit of time, each participant of the game can go through one corridor. All participants move at the same time. Participants may not move. Each room can fit all participants at the same time.

Friends know the plan of a maze and intend to win. Vlad is a bit afraid of their ardor. Determine if he can guarantee victory (i.e. can he win in any way friends play).

In other words, determine if there is such a sequence of Vlad's moves that lets Vlad win in any way friends play.

## 说明/提示

In the first test case, regardless of the strategy of his friends, Vlad can win by going to room $ 4 $ . The game may look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/0a8c76c1125e98bbe64e3bee85b654b8b00ed8d2.png)The original locations of Vlad and friends. Vlad is marked in green, friends — in red.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/a01da1e80c938fd2913aa4a19caf3932554dfd58.png)Locations after one unit of time.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/315079dc5161157c1dc8fb4c3b930b808460dd31.png)End of the game.Note that if Vlad tries to reach the exit at the room $ 8 $ , then a friend from the $ 3 $ room will be able to catch him.

## 样例 #1

### 输入

```
4

8 2
5 3
4 7
2 5
1 6
3 6
7 2
1 7
6 8

3 1
2
1 2
2 3

3 1
2
1 2
1 3

3 2
2 3
3 1
1 2```

### 输出

```
YES
NO
YES
NO```

# AI分析结果

### 题目内容翻译
# 逃离迷宫（简单版本）

## 题目描述
本题与 E2 版本的唯一区别在于问题本身。

弗拉德（Vlad）用 $n$ 个房间和 $n - 1$ 条双向走廊建造了一个迷宫。从任何一个房间 $u$ 出发，都可以通过一系列走廊到达其他任何房间 $v$。因此，房间系统构成了一棵无向树。

弗拉德邀请了 $k$ 个朋友来和他一起玩游戏。

弗拉德从 1 号房间开始游戏，如果他到达了除 1 号房间之外且只有一条走廊与之相连的房间，他就获胜。

朋友们被安置在迷宫中：编号为 $i$ 的朋友在房间 $x_i$ 中，并且没有两个朋友在同一个房间（即对于所有 $i \neq j$，都有 $x_i \neq x_j$）。如果在弗拉德获胜之前，有任何一个朋友在任何房间或走廊遇到他，朋友们就获胜。

在一个单位时间内，游戏的每个参与者都可以通过一条走廊。所有参与者同时移动，参与者也可以选择不移动。每个房间可以同时容纳所有参与者。

朋友们知道迷宫的布局，并且一心想要获胜。弗拉德有点害怕他们的热情。请确定他是否能够保证获胜（即无论朋友们如何行动，他都能获胜）。

换句话说，确定是否存在这样一个弗拉德的移动序列，使得无论朋友们如何行动，弗拉德都能获胜。

## 说明/提示
在第一个测试用例中，无论他的朋友们采取何种策略，弗拉德都可以通过前往 4 号房间获胜。游戏过程可能如下：

![初始状态](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/0a8c76c1125e98bbe64e3bee85b654b8b00ed8d2.png) 弗拉德和朋友们的初始位置。弗拉德用绿色标记，朋友们用红色标记。

![移动一个单位时间后的状态](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/a01da1e80c938fd2913aa4a19caf3932554dfd58.png) 一个单位时间后的位置。

![游戏结束状态](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611E1/315079dc5161157c1dc8fb4c3b930b808460dd31.png) 游戏结束。

请注意，如果弗拉德试图前往 8 号房间的出口，那么 3 号房间的朋友将能够抓住他。

## 样例 #1

### 输入
```
4

8 2
5 3
4 7
2 5
1 6
3 6
7 2
1 7
6 8

3 1
2
1 2
2 3

3 1
2
1 2
1 3

3 2
2 3
3 1
1 2
```

### 输出
```
YES
NO
YES
NO
```

### 算法分类
图论

### 综合分析与结论
这些题解主要围绕判断在树状迷宫中玩家是否能避开朋友到达叶子节点获胜展开。思路大多是计算玩家和朋友到各节点的距离，然后比较到叶子节点的距离来判断是否有获胜路径。
- **思路对比**：大部分题解采用 BFS 或 DFS 计算距离，如智子的题解跑两遍 BFS 分别计算玩家和朋友到各节点的最短距离；Lacrymabre 的题解用 DFS 维护时间和深度数组。也有独特思路，如 I_will_AKIOI 用树状数组标记不能走的子树。
- **算法要点**：主要算法为 BFS、DFS、最短路（Dijkstra）、树状数组等。BFS 和 DFS 用于遍历树计算距离，Dijkstra 用于求最短路，树状数组用于区间修改和单点查询。
- **解决难点**：核心难点在于判断玩家是否能在不被朋友拦截的情况下到达叶子节点。不同题解通过不同方式解决，如比较距离、标记不可走区域等。

### 所选题解
- **智子（5星）**
    - **关键亮点**：思路清晰，用两遍 BFS 分别计算玩家和朋友到各节点的最短距离，通过比较到叶子节点的距离判断是否能获胜，代码实现简洁易懂。
- **Lacrymabre（4星）**
    - **关键亮点**：使用 DFS 维护时间和深度数组，思路简洁，能有效解决问题。
- **swqdwq（4星）**
    - **关键亮点**：引入虚拟节点跑 Dijkstra 求最短路，思路新颖，能巧妙解决问题。

### 重点代码
#### 智子的题解
```cpp
// 计算玩家到各节点的最短距离
void bfs1() {
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        dis[i] = 0;
        vis[i] = false;
    }
    q.push(1);
    vis[1] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if(vis[v]) {
                continue;
            }
            dis[v] = dis[u] + 1;
            vis[v] = true;
            q.push(v);
        }
    }
    for(int i = 1; i <= n; i++) {
        tmp[i] = dis[i];
    }
}

// 计算朋友到各节点的最短距离
void bfs2() {
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        dis[i] = 0;
        vis[i] = false;
    }
    for(int i = 1; i <= k; i++) {
        q.push(pos[i]);
        vis[pos[i]] = true;
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if(vis[v]) {
                continue;
            }
            dis[v] = dis[u] + 1;
            vis[v] = true;
            q.push(v);
        }
    }
}
```
**核心实现思想**：bfs1 从玩家所在的 1 号节点开始 BFS，计算玩家到各节点的最短距离；bfs2 从朋友们所在的节点开始 BFS，计算朋友到各节点的最短距离。

#### Lacrymabre 的题解
```cpp
// 维护深度和朋友到达时间
void getime(ll now,ll fa){	
    ll len=s[now].size();
    for(int i=0;i<len;i++){
        ll y=s[now][i];
        if(y==fa) continue;
        dep[y]=dep[now]+1;
        getime(y,now);
        tline[now]=min(tline[now],tline[y]+1);
    }
}

// 检查是否能获胜
void cheak(ll now,ll fa){
    ll res=0,len=s[now].size();
    for(int i=0;i<len;i++){
        ll y=s[now][i];
        if(y==fa) continue;
        res=1;
        if(tline[y]>dep[y]) cheak(y,now);
    }
    if(res==0) flag=1;
}
```
**核心实现思想**：getime 函数通过 DFS 维护深度数组和朋友到达时间数组；cheak 函数检查是否存在能让玩家获胜的路径。

#### swqdwq 的题解
```cpp
// Dijkstra 求最短路
auto dij = [&] (int s)->void {
    for (int i = 0; i <= n; i++)dis[i] = INF, vis[i] = 0;
    dis[s] = 0;
    pq.push({ 0,s });
    while (pq.size()) {
        int x = pq.top().second;
        pq.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        for (auto i : g[x]) {
            if (dis[i.e] > dis[x] + i.v) {
                dis[i.e] = dis[x] + i.v;
                if (!vis[i.e])pq.push({ -dis[i.e],i.e });
            }
        }
    }
};
```
**核心实现思想**：使用 Dijkstra 算法求从起点到各节点的最短路。

### 最优关键思路或技巧
- 计算玩家和朋友到各节点的最短距离，通过比较到叶子节点的距离判断是否能获胜。
- 引入虚拟节点简化计算朋友到各节点的最短距离。
- 利用树状数组进行区间修改和单点查询，标记不能走的子树。

### 拓展思路
同类型题或类似算法套路：
- 树上博弈问题，如判断在树上的其他博弈场景中某一方是否有必胜策略。
- 树上路径问题，如求树上两点间的最短路径、最长路径等。

### 推荐题目
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)
- [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)
- [P2607 [ZJOI2008] 骑士](https://www.luogu.com.cn/problem/P2607)

### 个人心得
- **Tx_Lcy**：这题并不难，E1 和 E2 的难度差不多。但是细节众多，我调了一个小时才过的。
**总结**：该题虽然难度不高，但细节较多，需要仔细处理，调试可能会花费较多时间。 

---
处理用时：84.86秒