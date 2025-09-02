# 题目信息

# Cycle In Maze

## 题目描述

The Robot is in a rectangular maze of size $ n×m $ . Each cell of the maze is either empty or occupied by an obstacle. The Robot can move between neighboring cells on the side left (the symbol "L"), right (the symbol "R"), up (the symbol "U") or down (the symbol "D"). The Robot can move to the cell only if it is empty. Initially, the Robot is in the empty cell.

Your task is to find lexicographically minimal Robot's cycle with length exactly $ k $ , which begins and ends in the cell where the Robot was initially. It is allowed to the Robot to visit any cell many times (including starting).

Consider that Robot's way is given as a line which consists of symbols "L", "R", "U" and "D". For example, if firstly the Robot goes down, then left, then right and up, it means that his way is written as "DLRU".

In this task you don't need to minimize the length of the way. Find the minimum lexicographical (in alphabet order as in the dictionary) line which satisfies requirements above.

## 说明/提示

In the first sample two cyclic ways for the Robot with the length $ 2 $ exist — "UD" and "RL". The second cycle is lexicographically less.

In the second sample the Robot should move in the following way: down, left, down, down, left, left, left, right, right, right, up, up, right, up.

In the third sample the Robot can't move to the neighboring cells, because they are occupied by obstacles.

## 样例 #1

### 输入

```
2 3 2
.**
X..
```

### 输出

```
RL
```

## 样例 #2

### 输入

```
5 6 14
..***.
*...X.
..*...
..*.**
....*.
```

### 输出

```
DLDDLLLRRRUURU
```

## 样例 #3

### 输入

```
3 3 4
***
*X*
***
```

### 输出

```
IMPOSSIBLE
```

# AI分析结果

### 题目内容
# 迷宫中的循环

## 题目描述
机器人位于一个大小为 $n×m$ 的矩形迷宫中。迷宫的每个单元格要么为空，要么被障碍物占据。机器人可以在相邻单元格之间向左（符号“L”）、向右（符号“R”）、向上（符号“U”）或向下（符号“D”）移动。机器人只能移动到空单元格。最初，机器人位于一个空单元格中。

你的任务是找到字典序最小的、长度恰好为 $k$ 的机器人循环路径，该路径从机器人初始所在单元格开始并结束于该单元格。允许机器人多次访问任何单元格（包括起始单元格）。

假设机器人的路径表示为一个由符号“L”、“R”、“U”和“D”组成的字符串。例如，如果机器人首先向下移动，然后向左，然后向右，最后向上移动，则表示其路径的字符串为“DLRU”。

在这个任务中，你不需要最小化路径的长度。找到满足上述要求的字典序最小（按字母顺序，如同在字典中）的字符串。

## 说明/提示
在第一个样例中，机器人存在两个长度为 $2$ 的循环路径 —— “UD”和“RL”。第二个循环路径的字典序更小。

在第二个样例中，机器人应该按以下方式移动：向下、向左、向下、向下、向左、向左、向左、向右、向右、向右、向上、向上、向右、向上。

在第三个样例中，机器人无法移动到相邻单元格，因为它们被障碍物占据。

## 样例 #1
### 输入
```
2 3 2
.**
X..
```
### 输出
```
RL
```

## 样例 #2
### 输入
```
5 6 14
..***.
*...X.
..*...
..*.**
....*.
```
### 输出
```
DLDDLLLRRRUURU
```

## 样例 #3
### 输入
```
3 3 4
***
*X*
***
```
### 输出
```
IMPOSSIBLE
```

### 算法分类
深度优先搜索 DFS、广度优先搜索 BFS、剪枝

### 题解综合分析与结论
三道题解都围绕在给定的迷宫中寻找满足特定长度和字典序要求的循环路径展开，均采用了搜索结合剪枝的策略来优化搜索过程，以应对较大的 $k$ 值。不同之处在于剪枝的具体实现和搜索过程中的细节处理。

### 所选的题解
- **作者：qwqszxc45rtnhy678ikj（4星）**
  - **关键亮点**：先通过 BFS 预处理出每个点到障碍物“X”的距离，在 DFS 过程中，如果当前点到“X”的距离大于剩余可走步数则剪枝。考虑到字典序，按“DLRU”顺序搜索。
  - **个人心得**：最初尝试先 DFS 求前半部分再按规则得后半部分，在 test 49 出错，意识到原算法不对，从而改为 BFS 预处理距离结合 DFS 剪枝的方法。
```cpp
void bfs(long long ux, long long uy) { //bfs
    hx.push(ux);
    hy.push(uy);
    t[ux][uy] = 0;
    while(!hx.empty()) {
        for(int i = 0; i < 4; i++) {
            long long tx = hx.front() + xx[i], ty = hy.front() + yy[i];//下一步走的地方
            if((tx % (n + 1)) && (ty % (m + 1)) && c[tx][ty]!= '*' && t[tx][ty] > t[hx.front()][hy.front()] + 1) {//判断是否能走和有没有遍历过
                t[tx][ty] = t[hx.front()][hy.front()] + 1;
                hx.push(tx);
                hy.push(ty);
            }
        }
        hx.pop();
        hy.pop();
    }
}
void dfs(long long tx, long long ty, long long step) {//dfs
    if(step > k) {
        for(int i = 1; i <= k; i++) cout << p[ans[i]];//输出
        flag = 1;//标记已经得出答案了
        return;
    }
    for(int i = 0; i < 4; i++)
        if(((tx + xx[i]) % (n + 1)) && ((ty + yy[i]) % (m + 1)) && c[tx + xx[i]][ty + yy[i]]!= '*') {//判断是否能走和有没有遍历过
            if(t[tx + xx[i]][ty + yy[i]] > k - step + 1) continue;//如果到X的距离大于了剩下可走的步数，剪枝
            ans[step] = i;
            dfs(tx + xx[i], ty + yy[i], step + 1);
            if(flag) return;//如果已经得出答案了就return
        }
}
```
核心实现思想：BFS 函数通过队列遍历每个可达点并记录到起点的距离。DFS 函数在搜索过程中，依据 BFS 预处理的距离进行剪枝，同时按字典序顺序尝试不同方向，找到路径后标记并输出。

- **作者：ShanQing（4星）**
  - **关键亮点**：两次使用 BFS，第一次求出起点到所有点的最短路，用于在搜索过程中及时回溯；第二次在不得不回溯时，求出当前点到起点的最小字典序路径。搜索过程按“DLRU”顺序贪心选择方向。
```cpp
void bfs(int x,int y) {
    queue<pii> q;
    q.push({x,y});
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=m;++j) {
            vis[i][j]=0;
        }
    }
    vis[x][y]=1,dis[x][y]=0;
    while(!q.empty()) {
        pii now=q.front();q.pop();
        for(int i=0;i<4;++i) {
            int tx=now.fi+dr[i][0],ty=now.se+dr[i][1];
            if(in(tx,ty)&&a[tx][ty]!='*'&&!vis[tx][ty]) {
                vis[tx][ty]=1,fr[tx][ty]=i;
                dis[tx][ty]=dis[now.fi][now.se]+1;
                q.push({tx,ty});
            }
        }
    }
}
```
核心实现思想：BFS 函数通过队列遍历更新每个可达点的访问状态、前驱方向和到起点的距离，为后续的贪心搜索和回溯提供信息。

### 最优关键思路或技巧
利用 BFS 预处理距离信息，为 DFS 剪枝提供依据，减少不必要的搜索分支。同时，按“DLRU”的字典序顺序进行搜索，保证找到的路径字典序最小。

### 可拓展之处
同类型题常涉及在网格图中寻找满足特定条件的路径，类似算法套路为结合 BFS 和 DFS，BFS 预处理距离等信息辅助 DFS 剪枝，或多次使用 BFS 来解决不同阶段的问题，如寻找最短路径、最优路径等。

### 推荐洛谷题目
- [P1332 血色先锋队](https://www.luogu.com.cn/problem/P1332)
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)

---
处理用时：71.39秒