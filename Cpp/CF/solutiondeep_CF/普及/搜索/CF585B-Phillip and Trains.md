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

### 题目内容重写（中文）

#### 题目描述

移动应用商店推出了一款新游戏，名为“地铁滚轮”。

游戏的主角Philip位于隧道的一端，想要从另一端逃出。隧道是一个由三行和$n$列组成的矩形区域。游戏开始时，主角位于最左边一列的某个单元格中。一些火车正朝主角驶来。每列火车由两格或更多相邻的单元格组成，且位于隧道的某一行中。

所有火车以每秒两格的速度从右向左移动，而主角以每秒一格的速度从左向右移动。为了简化，游戏的实现方式是主角和火车交替移动。首先，主角向右移动一格，然后可以选择向上、向下移动一格或保持不动。接着，所有火车同时向左移动两格。因此，在每一步中，主角必须向右移动一格，并可以选择向上、向下移动或保持不动。如果在任何时候，主角与火车位于同一单元格，则游戏失败。如果火车到达最左边一列，它会继续移动并离开隧道。

你的任务是判断是否存在一种主角的移动序列，使得他能够到达最右边一列。

### 样例 #1

#### 输入

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

#### 输出

```
YES
NO
```

### 样例 #2

#### 输入

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

#### 输出

```
YES
NO
```

---

### 题解综合分析与结论

该题目主要考察搜索算法（DFS/BFS）的应用，难点在于如何简化火车的移动过程，避免复杂的模拟操作。大多数题解通过相对运动的思路，将火车的移动转化为主角的移动，从而简化问题。以下是各题解的要点对比：

1. **DFS/BFS的选择**：大多数题解使用DFS进行搜索，部分题解使用BFS。DFS的优点是代码简洁，但容易陷入深度过大的情况；BFS则更适合寻找最短路径，但代码复杂度稍高。
2. **相对运动的简化**：几乎所有题解都采用了相对运动的思路，将火车的移动转化为主角的移动，从而避免了复杂的火车移动模拟。
3. **剪枝与优化**：部分题解通过标记访问过的节点（`vis`数组）进行剪枝，避免重复搜索，提高效率。
4. **代码实现细节**：部分题解在实现时忽略了火车移动过程中的碰撞检测，导致逻辑错误。正确的做法是在每一步移动时都检测是否与火车发生碰撞。

### 评分较高的题解

#### 1. 作者：lraM41 (评分：4星)

**关键亮点**：
- 使用DFS进行搜索，代码简洁。
- 通过相对运动的思路，将火车的移动转化为主角的移动，简化了问题。
- 使用`vis`数组进行剪枝，避免重复搜索。

**核心代码**：
```cpp
void dfs(int x,int y)
{
   if(y>=n){//达到终点
      f=1;
      return;
   }
   if(vis[x][y]||f)return;//已走过或已经到了。
   vis[x][y]=1;//打标记。
   if(a[x][y+1])return;//如果前面有火车，结束。
   for(int i=x-1;i<=x+1;i++)//三行。
   {
      if(i<1||i>3)continue;//越界了。
      if(!a[i][y+1]&&!a[i][y+2]&&!a[i][y+3])dfs(i,y+3);//前面没火车。
   }
}
```

#### 2. 作者：installb (评分：4星)

**关键亮点**：
- 使用BFS进行搜索，适合寻找最短路径。
- 通过相对运动的思路，将火车的移动转化为主角的移动，简化了问题。
- 在每一步移动时都检测是否与火车发生碰撞，逻辑严谨。

**核心代码**：
```cpp
bool bfs(int tx, int ty) {
    memset(visit, 0, sizeof(visit));
    while (!que.empty())
        que.pop();
    que.push((node){tx, ty});  //起点
    while (!que.empty()) {
        node cac = que.front();
        que.pop();
        int &x = cac.first, &y = cac.second;
        if (visit[x][y])
            continue;
        visit[x][y] = true;
        if (y >= n - 1)  //跑出地图，即成功
            return true;
        if (train[x][++y])  //1.前进一格
            continue;
        if (y == n - 1)  //跑出地图，即成功
            return true;
        for (int i = -1; i < 2; i++) {  //2.尝试转向
            int tx = x + i;
            if (tx < 0 || tx > 2)
                continue;
            if (train[tx][y] || train[tx][y + 1] || train[tx][y + 2])
                continue;  //3.前进两格
            que.push((node){tx, y + 2});
        }
    }
    return false;
}
```

#### 3. 作者：Prurite (评分：4星)

**关键亮点**：
- 使用DFS进行搜索，代码简洁。
- 通过相对运动的思路，将火车的移动转化为主角的移动，简化了问题。
- 使用`vis`数组进行剪枝，避免重复搜索。

**核心代码**：
```cpp
inline void dfs( int nowx, int nowy )
{
	if ( nowy>=len ) //走到了隧道尽头 
		can_arrive=1;
	if ( can_arrive ) // 已经有合法路径 
		return;
	if ( map[nowx][nowy]==0 ) // 走到了不能走的格子 
		return;
	if ( vis[nowx][nowy] ) // 当前格子被访问过 
		return;
	vis[nowx][nowy]=1; // 记录访问 
	for ( int i=-1; i<=1; i++ )
		if ( map[nowx][nowy+1] && map[nowx+i][nowy+1] 
		&& map[nowx+i][nowy+2] && map[nowx+i][nowy+3] )
		// 判断路径上是否都是空格子，是再继续搜索 
			dfs( nowx+i, nowy+3 );
	return;
}
```

### 最优关键思路或技巧

1. **相对运动的简化**：将火车的移动转化为主角的移动，避免了复杂的模拟操作，大大简化了问题。
2. **剪枝与优化**：通过`vis`数组标记访问过的节点，避免重复搜索，提高效率。
3. **碰撞检测**：在每一步移动时都检测是否与火车发生碰撞，确保逻辑的正确性。

### 可拓展之处

该题目的思路可以拓展到其他类似的搜索问题，尤其是涉及到移动物体和碰撞检测的场景。例如，迷宫问题、路径规划问题等，都可以借鉴相对运动的思路，简化问题的复杂度。

### 推荐题目

1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 最小生成树](https://www.luogu.com.cn/problem/P1131)

### 个人心得总结

部分题解在实现时忽略了火车移动过程中的碰撞检测，导致逻辑错误。正确的做法是在每一步移动时都检测是否与火车发生碰撞，确保逻辑的正确性。此外，相对运动的思路是解决此类问题的关键，能够大大简化问题的复杂度。

---
处理用时：54.59秒