# 题目信息

# Phillip and Trains

## 题目描述

The mobile application store has a new game called "Subway Roller".

The protagonist of the game Philip is located in one end of the tunnel and wants to get out of the other one. The tunnel is a rectangular field consisting of three rows and $ n $ columns. At the beginning of the game the hero is in some cell of the leftmost column. Some number of trains rides towards the hero. Each train consists of two or more neighbouring cells in some row of the field.

All trains are moving from right to left at a speed of two cells per second, and the hero runs from left to right at the speed of one cell per second. For simplicity, the game is implemented so that the hero and the trains move in turns. First, the hero moves one cell to the right, then one square up or down, or stays idle. Then all the trains move twice simultaneously one cell to the left. Thus, in one move, Philip definitely makes a move to the right and can move up or down. If at any point, Philip is in the same cell with a train, he loses. If the train reaches the left column, it continues to move as before, leaving the tunnel.

Your task is to answer the question whether there is a sequence of movements of Philip, such that he would be able to get to the rightmost column.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF585B/309f950d64c5a7d55f4952aae670b86363abc76b.png)

## 说明/提示

In the first set of the input of the first sample Philip must first go forward and go down to the third row of the field, then go only forward, then go forward and climb to the second row, go forward again and go up to the first row. After that way no train blocks Philip's path, so he can go straight to the end of the tunnel.

Note that in this problem the challenges are restricted to tests that contain only one testset.

## 样例 #1

### 输入

```
2
16 4
...AAAAA........
s.BBB......CCCCC
........DDDDD...
16 4
...AAAAA........
s.BBB....CCCCC..
.......DDDDD....
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
2
10 4
s.ZZ......
.....AAABB
.YYYYYY...
10 4
s.ZZ......
....AAAABB
.YYYYYY...
```

### 输出

```
YES
NO
```

# AI分析结果

### 题目内容重写

#### 题目描述

移动应用商店推出了一款名为“地铁跑酷”的新游戏。

游戏的主角菲利普位于隧道的一端，想要从另一端逃出。隧道是一个由三行和$n$列组成的矩形区域。游戏开始时，主角位于最左边列的某个单元格中。隧道中有一些火车向主角驶来。每列火车由某一行中的两个或更多相邻单元格组成。

所有火车都以每秒两格的速度从右向左移动，而主角以每秒一格的速度从左向右移动。为了简化游戏实现，游戏中的主角和火车的移动是交替进行的。首先，主角向右移动一格，然后可以选择向上、向下移动一格或保持不动。接着，所有火车同时向左移动两格。因此，在一次移动中，主角必须向右移动一格，并可以选择向上或向下移动。如果在任何时候，主角与火车处于同一单元格，主角就会失败。如果火车到达最左边的列，它会继续移动并离开隧道。

你的任务是回答是否存在一种菲利普的移动序列，使得他能够到达最右边的列。

#### 说明/提示

在第一个样例的第一组输入中，菲利普必须首先向前移动并向下移动到第三行，然后只向前移动，接着向前移动并向上移动到第二行，再次向前移动并向上移动到第一行。之后，没有火车阻挡菲利普的路径，因此他可以一直移动到隧道的尽头。

注意，本题的测试用例仅限于包含一个测试集的测试。

#### 样例 #1

##### 输入

```
2
16 4
...AAAAA........
s.BBB......CCCCC
........DDDDD...
16 4
...AAAAA........
s.BBB....CCCCC..
.......DDDDD....
```

##### 输出

```
YES
NO
```

#### 样例 #2

##### 输入

```
2
10 4
s.ZZ......
.....AAABB
.YYYYYY...
10 4
s.ZZ......
....AAAABB
.YYYYYY...
```

##### 输出

```
YES
NO
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是通过搜索算法（DFS或BFS）来判断主角是否能够从起点移动到终点，同时避免与火车相撞。由于火车的移动速度是主角的两倍，因此可以将火车的移动转化为主角的移动，从而简化问题。具体来说，每次主角移动一格后，火车会向左移动两格，这可以等效为主角向右移动三格。通过这种方式，可以将火车的移动转化为主角的移动，从而简化搜索过程。

#### 题解评分与亮点

1. **作者：lraM41 (赞：5)**
   - **星级：4.5**
   - **关键亮点**：通过相对运动将火车的移动转化为主角的移动，简化了搜索过程。代码简洁，逻辑清晰，使用了DFS进行搜索，并通过标记数组避免重复访问。
   - **核心代码**：
     ```cpp
     void dfs(int x, int y) {
        if(y>=n){ f=1; return; }
        if(vis[x][y]||f)return;
        vis[x][y]=1;
        if(a[x][y+1])return;
        for(int i=x-1;i<=x+1;i++) {
           if(i<1||i>3)continue;
           if(!a[i][y+1]&&!a[i][y+2]&&!a[i][y+3])dfs(i,y+3);
        }
     }
     ```

2. **作者：installb (赞：4)**
   - **星级：4.0**
   - **关键亮点**：使用BFS进行搜索，通过队列实现广度优先搜索，逻辑清晰，代码结构良好。通过将火车的移动转化为主角的移动，简化了问题。
   - **核心代码**：
     ```cpp
     while(!q.empty()) {
        aa = q.front();
        if(aa.lin >= n) { flag = 1; break; }
        if(mp[aa.lin + 1][aa.col] == 1 || mp[aa.lin][aa.col] == 1) { q.pop(); continue; }
        for(int i = 0; i < 3; i++) {
           tx = aa.lin + 1; ty = aa.col + dirx[i];
           if(ty < 1 || ty > 3) continue;
           if(mp[tx][ty] == 1) continue;
           tx = aa.lin + 2; if(mp[tx][ty] == 1) continue;
           tx = aa.lin + 3; if(mp[tx][ty] == 1) continue;
           if(vis[tx][ty] == 1) continue;
           vis[tx][ty] = 1; bb.lin = tx; bb.col = ty; q.push(bb);
        }
        q.pop();
     }
     ```

3. **作者：Prurite (赞：2)**
   - **星级：3.5**
   - **关键亮点**：通过DFS进行搜索，使用了相对运动的思路，代码简洁，逻辑清晰。通过标记数组避免重复访问，并通过剪枝优化搜索过程。
   - **核心代码**：
     ```cpp
     inline void dfs(int nowx, int nowy) {
        if (nowy>=len) can_arrive=1;
        if (can_arrive) return;
        if (map[nowx][nowy]==0) return;
        if (vis[nowx][nowy]) return;
        vis[nowx][nowy]=1;
        for (int i=-1; i<=1; i++)
           if (map[nowx][nowy+1] && map[nowx+i][nowy+1] 
           && map[nowx+i][nowy+2] && map[nowx+i][nowy+3])
              dfs(nowx+i, nowy+3);
     }
     ```

#### 最优关键思路或技巧

1. **相对运动**：将火车的移动转化为主角的移动，从而简化搜索过程。通过将火车的移动速度与主角的移动速度进行对比，可以将火车的移动转化为主角的移动，从而减少搜索的复杂度。
2. **DFS/BFS搜索**：使用深度优先搜索（DFS）或广度优先搜索（BFS）进行路径搜索，通过标记数组避免重复访问，并通过剪枝优化搜索过程。
3. **剪枝优化**：在搜索过程中，通过判断当前路径是否合法，避免不必要的搜索，从而提高搜索效率。

#### 可拓展之处

1. **多线程搜索**：在更复杂的场景中，可以考虑使用多线程进行并行搜索，以进一步提高搜索效率。
2. **动态规划**：在某些情况下，可以使用动态规划来优化搜索过程，减少重复计算。

#### 推荐题目

1. **洛谷 P1002 [NOIP2002 普及组] 过河卒**（题号：P1002）
2. **洛谷 P1048 [NOIP2005 普及组] 采药**（题号：P1048）
3. **洛谷 P1219 [USACO1.5] 八皇后**（题号：P1219）

#### 个人心得摘录

- **作者：lraM41**：通过相对运动将火车的移动转化为主角的移动，简化了搜索过程，代码实现简洁，逻辑清晰。
- **作者：installb**：使用BFS进行搜索，通过队列实现广度优先搜索，逻辑清晰，代码结构良好，适合处理路径搜索问题。
- **作者：Prurite**：通过DFS进行搜索，使用了相对运动的思路，代码简洁，逻辑清晰，适合处理路径搜索问题。

---
处理用时：61.45秒