# 题目信息

# Escape The Maze (hard version)

## 题目描述

The only difference with E1 is the question of the problem.

Vlad built a maze out of $ n $ rooms and $ n-1 $ bidirectional corridors. From any room $ u $ any other room $ v $ can be reached through a sequence of corridors. Thus, the room system forms an undirected tree.

Vlad invited $ k $ friends to play a game with them.

Vlad starts the game in the room $ 1 $ and wins if he reaches a room other than $ 1 $ , into which exactly one corridor leads. Friends are placed in the maze: the friend with number $ i $ is in the room $ x_i $ , and no two friends are in the same room (that is, $ x_i \neq x_j $ for all $ i \neq j $ ). Friends win if one of them meets Vlad in any room or corridor before he wins.

For one unit of time, each participant of the game can go through one corridor. All participants move at the same time. Participants may not move. Each room can fit all participants at the same time.

Friends know the plan of a maze and intend to win. They don't want to waste too much energy. They ask you to determine if they can win and if they can, what minimum number of friends must remain in the maze so that they can always catch Vlad.

In other words, you need to determine the size of the minimum (by the number of elements) subset of friends who can catch Vlad or say that such a subset does not exist.

## 说明/提示

In the first set of inputs, even if all the friends stay in the maze, Vlad can still win. Therefore, the answer is "-1".

In the second set of inputs it is enough to leave friends from rooms $ 6 $ and $ 7 $ . Then Vlad will not be able to win. The answer is "2".

In the third and fourth sets of inputs Vlad cannot win only if all his friends stay in the maze. Therefore the answers are "1" and "2".

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

8 4
6 5 7 3
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

3 2
2 3
3 1
1 2```

### 输出

```
-1
2
1
2```

# AI分析结果

### 题目内容中文重写
# 逃离迷宫（困难版本）

## 题目描述
本题与 E1 的唯一区别在于问题本身。

弗拉德用 $n$ 个房间和 $n - 1$ 条双向走廊建造了一个迷宫。从任何一个房间 $u$ 都可以通过一系列走廊到达其他任何一个房间 $v$。因此，房间系统构成了一棵无向树。

弗拉德邀请了 $k$ 个朋友和他一起玩游戏。

弗拉德从 1 号房间开始游戏，如果他到达一个除 1 号房间外且只有一条走廊与之相连的房间，他就获胜。朋友们被安置在迷宫中：编号为 $i$ 的朋友在房间 $x_i$ 中，并且没有两个朋友在同一个房间（即对于所有 $i \neq j$，都有 $x_i \neq x_j$）。如果在弗拉德获胜之前，有任何一个朋友在任何房间或走廊遇到他，朋友们就获胜。

在一个单位时间内，游戏的每个参与者都可以通过一条走廊。所有参与者同时移动，参与者也可以选择不移动。每个房间可以同时容纳所有参与者。

朋友们知道迷宫的布局，并且想要获胜。他们不想浪费太多精力。他们要求你确定他们是否能够获胜，如果可以，最少需要多少个朋友留在迷宫中才能确保抓住弗拉德。

换句话说，你需要确定一个最小（元素数量最少）的朋友子集的大小，这个子集能够抓住弗拉德，或者说明这样的子集不存在。

## 说明/提示
在第一组输入中，即使所有朋友都留在迷宫中，弗拉德仍然可以获胜。因此，答案是“-1”。

在第二组输入中，只需要留下 6 号和 7 号房间的朋友。这样弗拉德就无法获胜。答案是“2”。

在第三组和第四组输入中，只有当所有朋友都留在迷宫中时，弗拉德才无法获胜。因此，答案分别是“1”和“2”。

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

8 4
6 5 7 3
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

3 2
2 3
3 1
1 2
```

### 输出
```
-1
2
1
2
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解的核心思路都是围绕着判断朋友能否阻止弗拉德到达叶子节点，并计算最少需要的朋友数量。不同题解采用了不同的实现方法，但大多基于深度优先搜索（DFS），部分结合了最短路、树状数组等算法。

- **思路对比**：
    - Rushroom 的题解通过两次 DFS，第一次处理出朋友最多能走到的节点，第二次模拟弗拉德走路判断是否能获胜。
    - Lacrymabre 的题解先计算每个节点的深度和朋友到达的最短时间，再通过 DFS 判断是否能获胜。
    - swqdwq 的题解通过两次 Dijkstra 预处理最短路，再用 DFS 统计最少需要的朋友数量。
    - I_will_AKIOI 的题解用树状数组区间标记每个朋友能守住的子树，再通过 DFS 删去多余的朋友。
    - eb0ycn 的题解处理出朋友和弗拉德到每个节点的距离，通过 DFS 模拟走路判断是否能获胜。
    - Tx_Lcy 的题解预处理每个点的 DFS 序，通过排序和剪枝优化时间复杂度。

- **算法要点**：多数题解都利用了 DFS 来遍历树，部分题解结合了最短路算法、树状数组等数据结构来辅助计算。
- **解决难点**：主要难点在于如何判断朋友能否阻止弗拉德到达叶子节点，以及如何计算最少需要的朋友数量。不同题解通过不同的方法解决这些难点，如 Rushroom 的题解通过处理朋友最多能走到的节点，I_will_AKIOI 的题解通过树状数组区间标记等。

### 所选题解
- **Rushroom 的题解（4星）**：
    - **关键亮点**：思路清晰，通过两次 DFS 解决问题，代码可读性较高。
- **Lacrymabre 的题解（4星）**：
    - **关键亮点**：代码简洁，利用 DFS 和简单的计算解决问题。
- **swqdwq 的题解（4星）**：
    - **关键亮点**：结合最短路算法和 DFS，思路新颖。

### 重点代码
#### Rushroom 的题解
```cpp
void dfs(int s, int from) //第一次dfs
{
    rep(i, v[s].size())
    {
        int x = v[s][i];
        if (x == from)
            continue;
        dep[x] = dep[s] + 1;
        q.pb(x);
        if (f[x])
            num[x] = q[dep[x] / 2];
        dfs(x, s);
        q.pop_back();
    }
}
bool get_ans(int s, int from) //第二次dfs
{
    if (del[s])
    {
        ans++;
        return 1;
    }
    if (s && v[s].size() == 1)
        return 0;
    rep(i, v[s].size())
    {
        int x = v[s][i];
        if (x == from)
            continue;
        if (!get_ans(x, s))
            return 0;
    }
    return 1;
}
```
**核心实现思想**：第一次 DFS 处理出朋友最多能走到的节点，第二次 DFS 模拟弗拉德走路，遇到朋友就退回去，判断是否能到达叶子节点。

#### Lacrymabre 的题解
```cpp
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

void cheak(ll now,ll fa){
    ll len=s[now].size();
    if(len==1&&s[now][0]==fa){// had been arrived
        flag=1;
        return;
    }
    for(int i=0;i<len;i++){
        ll y=s[now][i];
        if(y==fa) continue;
        if(tline[y]>dep[y]) cheak(y,now);
        else need++;
    }
}
```
**核心实现思想**：`getime` 函数计算每个节点的深度和朋友到达的最短时间，`cheak` 函数通过 DFS 判断是否能到达叶子节点。

#### swqdwq 的题解
```cpp
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
dij(1);
auto dis2 = dis;

for (int i = 1; i <= m; i++) {
    g[0].push_back({ fr[i],0 });
    g[fr[i]].push_back({ 0,0 });
}
dij(0);

for (auto i : leaf) {
    if (dis2[i] < dis[i]) {
        cout << "-1\n";
        return;
    }
}

int ans = 0;
vector<int>flag(n + 1);
for (int i = 1; i <= n; i++) {
    if (dis[i] <= dis2[i]) {
        flag[i] = 1;
    }
}

auto dfs = [&] (auto self, int x, int fa)->void {
    for (auto [y, v] : g[x]) {
        if (y == fa)continue;
        if (flag[y]) {
            ans++;
            continue;
        }
        self(self, y, x);
    }
};
dfs(dfs, 1, -1);
```
**核心实现思想**：通过两次 Dijkstra 预处理 1 号点和所有朋友到叶子节点的最短路，再用 DFS 统计最少需要的朋友数量。

### 最优关键思路或技巧
- 利用 DFS 遍历树，结合一些预处理（如计算深度、最短路等）来判断朋友能否阻止弗拉德到达叶子节点。
- 利用树状数组等数据结构来优化计算，如区间标记每个朋友能守住的子树。

### 拓展思路
同类型题或类似算法套路：
- 树上的博弈问题，如判断先手或后手是否有必胜策略。
- 树上的路径问题，如计算两点之间的最短路径、最长路径等。

### 推荐题目
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)
- [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)

### 个人心得摘录与总结
- **Tx_Lcy**：提到这题细节众多，调了一个小时才过。总结为在处理这类细节较多的题目时，需要耐心调试，仔细检查代码的每一个部分。

---
处理用时：72.97秒