# 题目信息

# [ABC213E] Stronger Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc213/tasks/abc213_e

$ H $ 行 $ W $ 列の格子状の区画に区切られた街があります。上から $ i $ 行目、左から $ j $ 列目の区画は、$ S_{i,j} $ が `.` のとき道、`#` のとき塀です。

高橋君は自分の家から魚屋に買い物に行くことにしました。高橋君の家は街の左上隅の区画にあり、魚屋は街の右下隅の区画にあります。

高橋君は、自分がいる区画から上下左右に隣接する道の区画に移動することができます。街の外に出ることはできません。  
 塀の区画に移動することはできませんが、高橋君は非常に腕力が強いため、パンチを $ 1 $ 回繰り出すことで任意の $ 2\times\ 2 $ の区画内の塀を壊して道にすることができます。

高橋君が魚屋にたどり着くためには、最低何回パンチを繰り出せばよいか求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,W\ \leq\ 500 $
- $ H,W $ は整数
- $ S_{i,j} $ は `.` または `#`
- $ S_{1,1} $ と $ S_{H,W} $ は `.`

### Sample Explanation 1

例えば、以下の `\*` で表す $ 2\times\ 2 $ の区画にある塀を破壊すると魚屋にたどり着くことができます。 ``` ..#.. #.\*\*# ##\*\*# #.#.# ..#.. ``` 破壊対象の $ 2\ \times\ 2 $ の区画の全てが塀である必要はありません。

### Sample Explanation 2

遠回りが必要ですが、塀を破壊することなく魚屋にたどり着くことができます。

## 样例 #1

### 输入

```
5 5

..#..

#.#.#

##.##

#.#.#

..#..```

### 输出

```
1```

## 样例 #2

### 输入

```
5 7

.......

######.

.......

.######

.......```

### 输出

```
0```

## 样例 #3

### 输入

```
8 8

.#######

########

########

########

########

########

########

#######.```

### 输出

```
5```

# AI分析结果

### 题目内容重写

#### [ABC213E] Stronger Takahashi

**题目描述**

有一个被划分为 $H$ 行 $W$ 列的格子状街区的城市。从上到下第 $i$ 行、从左到右第 $j$ 列的格子，如果 $S_{i,j}$ 是 `.` 则表示道路，`#` 表示墙壁。

高桥君决定从自己家出发去鱼市购物。高桥君的家位于城市左上角的格子，鱼市位于城市右下角的格子。

高桥君可以从当前所在的格子移动到上下左右相邻的道路格子。不能移动到城市外的格子，也不能移动到墙壁格子。但是，高桥君非常强壮，可以通过一次出拳将任意 $2 \times 2$ 的格子内的墙壁破坏，使其变为道路。

求高桥君到达鱼市所需的最少出拳次数。

**说明/提示**

**约束条件**

- $2 \leq H, W \leq 500$
- $H, W$ 是整数
- $S_{i,j}$ 是 `.` 或 `#`
- $S_{1,1}$ 和 $S_{H,W}$ 是 `.`

**样例解释 1**

例如，以下 `*` 表示的 $2 \times 2$ 格子内的墙壁被破坏后，高桥君可以到达鱼市：

```
..#..
#.**#
##**#
#.#.#
..#..
```

被破坏的 $2 \times 2$ 格子内的所有墙壁不必全部被破坏。

**样例解释 2**

虽然需要绕路，但高桥君可以在不破坏墙壁的情况下到达鱼市。

**样例 #1**

**输入**

```
5 5

..#..

#.#.#

##.##

#.#.#

..#..
```

**输出**

```
1
```

**样例 #2**

**输入**

```
5 7

.......

######.

.......

.######

.......
```

**输出**

```
0
```

**样例 #3**

**输入**

```
8 8

.#######

########

########

########

########

########

########

#######.
```

**输出**

```
5
```

### 算法分类

**广度优先搜索 BFS**

### 题解分析与结论

本题的核心是通过 BFS 求解从起点到终点的最少出拳次数。由于高桥君有两种移动方式：一种是普通的上下左右移动（不消耗出拳次数），另一种是通过出拳破坏 $2 \times 2$ 的墙壁（消耗一次出拳次数），因此需要使用双端队列（deque）来优先处理不消耗出拳次数的移动。

### 高星题解推荐

#### 题解1：xibaohe (4星)

**关键亮点：**
- 使用双端队列（deque）进行 BFS，优先处理不消耗出拳次数的移动。
- 代码结构清晰，注释详细，易于理解。

**核心代码：**
```cpp
void bfs() {
    q.push_front(node{1, 1, 0});
    dis[1][1] = 0;
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y, t = q.front().t;
        q.pop_front();
        // 普通移动
        for (int i = 0; i <= 3; i++) {
            int x_new = x + dx[i], y_new = y + dy[i];
            if (x_new < 1 || x_new > h || y_new < 1 || y_new > w) continue;
            if (a[x_new][y_new] == '#') continue;
            if (dis[x_new][y_new] <= dis[x][y]) continue;
            q.push_front(node{x_new, y_new, t});
            dis[x_new][y_new] = t;
        }
        // 出拳移动
        for (int x_new = x - 2; x_new <= x + 2; x_new++)
            for (int y_new = y - 2; y_new <= y + 2; y_new++) {
                if (x_new < 1 || x_new > h || y_new < 1 || y_new > w) continue;
                if (dis[x_new][y_new] <= dis[x][y] + 1) continue;
                q.push_back(node{x_new, y_new, t + 1});
                dis[x_new][y_new] = t + 1;
            }
    }
}
```

#### 题解2：yangyang1000 (4星)

**关键亮点：**
- 同样使用双端队列进行 BFS，优先处理不消耗出拳次数的移动。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
void bfs() {
    q.push_front({1, 1});
    dis[1][1] = 0;
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y;
        q.pop_front();
        // 普通移动
        for (int i = 0; i < 4; i++) {
            int xnew = x + dx[i], ynew = y + dy[i];
            if (xnew < 1 || xnew > h || ynew < 1 || ynew > w || a[xnew][ynew] == '#' || dis[xnew][ynew] <= dis[x][y]) continue;
            q.push_front({xnew, ynew});
            dis[xnew][ynew] = dis[x][y];
        }
        // 出拳移动
        for (int xnew = x - 2; xnew <= x + 2; xnew++)
            for (int ynew = y - 2; ynew <= y + 2; ynew++) {
                if (abs(xnew - x) + abs(ynew - y) == 4) continue;
                if (xnew < 1 || xnew > h || ynew < 1 || ynew > w || dis[xnew][ynew] <= dis[x][y] + 1) continue;
                q.push_back({xnew, ynew});
                dis[xnew][ynew] = dis[x][y] + 1;
            }
    }
}
```

#### 题解3：无咕_ (4星)

**关键亮点：**
- 使用双端队列进行 BFS，优先处理不消耗出拳次数的移动。
- 代码结构清晰，注释详细，易于理解。

**核心代码：**
```cpp
void bfs() {
    memset(dis, 0x3f, sizeof(dis));
    q.push_front(make_pair(1, 1));
    dis[1][1] = 0;
    while (!q.empty()) {
        p = q.front();
        q.pop_front();
        int x = p.first, y = p.second;
        // 普通移动
        for (int k = 1; k <= 4; k++) {
            int tx = x + qx[k], ty = y + qy[k];
            if (check(x, y, tx, ty) && dis[tx][ty] > dis[x][y] && mp[tx][ty] == 1) {
                q.push_front(make_pair(tx, ty));
                dis[tx][ty] = dis[x][y];
            }
        }
        // 出拳移动
        for (int k = 1; k <= 18; k++) {
            int tx = x + fx[k], ty = y + fy[k];
            if (check(x, y, tx, ty) && dis[tx][ty] > dis[x][y] + 1) {
                q.push_back(make_pair(tx, ty));
                dis[tx][ty] = dis[x][y] + 1;
            }
        }
    }
}
```

### 最优关键思路

1. **双端队列 BFS**：通过双端队列（deque）实现 BFS，优先处理不消耗出拳次数的移动（插入队首），处理消耗出拳次数的移动（插入队尾）。
2. **状态转移**：在 BFS 过程中，分别处理普通移动和出拳移动，确保每次移动的优先级和出拳次数的正确更新。
3. **边界检查**：在移动和出拳时，确保不越界，并且不重复处理已经访问过的节点。

### 可拓展之处

- **类似题目**：可以扩展到其他需要处理不同优先级移动的 BFS 问题，例如在某些移动需要消耗资源或时间的情况下。
- **优化思路**：可以考虑使用优先队列（priority queue）来进一步优化 BFS 的优先级处理。

### 推荐题目

1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)

---
处理用时：57.21秒