# 题目信息

# Robot Factory

## 题目描述

You have received data from a Bubble bot. You know your task is to make factory facilities, but before you even start, you need to know how big the factory is and how many rooms it has. When you look at the data you see that you have the dimensions of the construction, which is in rectangle shape: N x M.

Then in the next N lines you have M numbers. These numbers represent factory tiles and they can go from 0 to 15. Each of these numbers should be looked in its binary form. Because from each number you know on which side the tile has walls. For example number 10 in it's binary form is 1010, which means that it has a wall from the North side, it doesn't have a wall from the East, it has a wall on the South side and it doesn't have a wall on the West side. So it goes North, East, South, West.

It is guaranteed that the construction always has walls on it's edges. The input will be correct.

Your task is to print the size of the rooms from biggest to smallest.

## 样例 #1

### 输入

```
4 5
9 14 11 12 13
5 15 11 6 7
5 9 14 9 14
3 2 14 3 14```

### 输出

```
9 4 4 2 1```

# AI分析结果

### 题目内容重写

#### 机器人工厂

##### 题目描述

你收到了来自泡泡机器人的数据。你知道你的任务是建造工厂设施，但在你开始之前，你需要知道工厂的大小以及它有多少个房间。当你查看数据时，你发现你有建筑的尺寸，它是一个矩形：$N \times M$。

接下来的 $N$ 行中，每行有 $M$ 个数字。这些数字代表工厂的瓷砖，它们的值可以从 $0$ 到 $15$。每个数字应该被看作其二进制形式。因为从每个数字中你可以知道瓷砖的哪一侧有墙。例如，数字 $10$ 的二进制形式是 $1010$，这意味着它的北侧有墙，东侧没有墙，南侧有墙，西侧没有墙。顺序是北、东、南、西。

保证建筑的边缘总是有墙。输入总是正确的。

你的任务是按从大到小的顺序输出房间的大小。

##### 样例 #1

###### 输入

```
4 5
9 14 11 12 13
5 15 11 6 7
5 9 14 9 14
3 2 14 3 14
```

###### 输出

```
9 4 4 2 1
```

### 算法分类
深度优先搜索 DFS、位运算

### 题解分析与结论

本题的核心是通过DFS遍历矩阵，找到所有连通块的大小，并按从大到小排序输出。难点在于如何通过位运算判断瓷砖的哪一侧有墙，从而决定DFS的遍历方向。

#### 关键思路与技巧
1. **位运算判断墙的方向**：通过将瓷砖的值与特定方向的掩码进行按位与操作，判断该方向是否有墙。例如，北方向的掩码是8（二进制1000），东方向是4（0100），南方向是2（0010），西方向是1（0001）。
2. **DFS遍历连通块**：对于每个未被访问的瓷砖，启动DFS，记录连通块的大小，并将所有访问过的瓷砖标记为已访问。
3. **排序输出**：将所有连通块的大小存入数组，排序后输出。

#### 可拓展之处
- 类似的问题可以出现在迷宫、连通块、图的遍历等场景中。
- 位运算的技巧可以应用于其他需要快速判断二进制位的场景，如状态压缩、权限控制等。

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 精选题解

#### 题解1：作者：GI录像机 (赞：3)

##### 星级：★★★★★
##### 关键亮点
- 使用位运算预处理每个瓷砖的墙信息，代码简洁高效。
- 使用优先队列存储连通块大小，便于排序输出。

##### 核心代码
```cpp
void dfs(int x, int y) {
    vis[x][y] = 1;
    cnt++;
    for (int i = 0; i <= 3; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (d[a[x][y]][i] || vis[xx][yy]) continue;
        dfs(xx, yy);
    }
}
```

#### 题解2：作者：tallnut (赞：2)

##### 星级：★★★★
##### 关键亮点
- 直接在DFS中使用位运算判断是否可扩展，代码简洁明了。
- 使用vector存储连通块大小，排序后输出。

##### 核心代码
```cpp
void dfs(int x, int y) {
    cnt++;
    visited[x][y] = true;
    if (x > 1 && (!visited[x - 1][y]) && ((a[x][y] & 8) == 0)) dfs(x - 1, y);
    if (x < n && (!visited[x + 1][y]) && ((a[x][y] & 2) == 0)) dfs(x + 1, y);
    if (y > 1 && (!visited[x][y - 1]) && ((a[x][y] & 1) == 0)) dfs(x, y - 1);
    if (y < m && (!visited[x][y + 1]) && ((a[x][y] & 4) == 0)) dfs(x, y + 1);
}
```

#### 题解3：作者：CommandSR (赞：1)

##### 星级：★★★★
##### 关键亮点
- 使用打表法预处理二进制信息，代码清晰易读。
- 使用数组存储连通块大小，排序后输出。

##### 核心代码
```cpp
void dfs(int x, int y) {
    res++;
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
        if (vis[xx][yy]) continue;
        if (bin[a[x][y]][i] - '0' == 1) continue;
        dfs(xx, yy);
    }
}
```

### 总结
本题的关键在于如何通过位运算快速判断瓷砖的墙信息，并结合DFS遍历连通块。推荐的题解均采用了这一思路，代码简洁高效，值得学习。

---
处理用时：40.66秒