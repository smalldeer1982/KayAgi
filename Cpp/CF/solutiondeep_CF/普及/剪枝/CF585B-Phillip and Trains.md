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

### 题目翻译
### Phillip和火车

#### 题目描述
手机应用商店里有一款新游戏叫“地铁跑酷”。

游戏主角菲利普位于隧道的一端，想从另一端出去。隧道是一个由三行 $n$ 列组成的矩形区域。游戏开始时，主角位于最左边一列的某个单元格中。有若干列火车朝着主角驶来。每列火车由该区域某一行中两个或更多相邻的单元格组成。

所有火车以每秒两格的速度从右向左移动，而主角以每秒一格的速度从左向右移动。为了简化，游戏实现方式是主角和火车轮流移动。首先，主角向右移动一格，然后向上或向下移动一格，或者保持不动。然后所有火车同时向左移动两格。因此，在一次移动中，菲利普肯定会向右移动一格，并且可以向上或向下移动。如果在任何时候，菲利普和火车处于同一单元格，他就输了。如果火车到达最左边一列，它会继续像之前一样移动，离开隧道。

你的任务是回答是否存在菲利普的一系列移动方式，使他能够到达最右边一列。

#### 说明/提示
在第一个样例的第一组输入中，菲利普必须先向前移动并向下移动到区域的第三行，然后只向前移动，接着向前移动并爬到第二行，再向前移动并向上移动到第一行。在那之后，没有火车阻挡菲利普的路径，所以他可以直接到达隧道的尽头。

请注意，在这个问题中，挑战仅限于只包含一个测试集的测试。

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

### 综合分析与结论
这些题解主要围绕搜索算法（DFS和BFS）解决问题。核心思路是利用运动相对性，将火车向左移动转化为人向右多移动，简化问题。
- **思路对比**：多数题解采用DFS或BFS搜索路径，部分使用反向递推和记忆化搜索。
- **算法要点**：
    - 标记访问过的点避免重复搜索。
    - 每次搜索判断接下来三格是否有火车。
    - 多组数据时注意数组初始化。
- **难点解决**：
    - 运动相对性简化火车移动处理。
    - 考虑移动过程中是否撞到火车，避免不合法转移。

### 评分较高的题解
1. **作者：lraM41（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细注释，利用运动相对性简化问题，搜索过程明确。
    - **核心代码**：
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
2. **作者：installb（4星）**
    - **关键亮点**：采用BFS搜索，详细解释移动过程和判断条件，对多组数据处理清晰。
    - **核心代码**：
```cpp
while(!q.empty()) {
    aa = q.front();
    if(aa.lin >= n) { 
        flag = 1;
        while(!q.empty()) q.pop(); 
        break;
    }
    if(mp[aa.lin + 1][aa.col] == 1 || mp[aa.lin][aa.col] == 1) {
        q.pop();
        continue;
    } 
    for(int i = 0; i < 3; i ++) {
        tx = aa.lin + 1;
        ty = aa.col + dirx[i]; 
        if(ty < 1 || ty > 3) continue;
        if(mp[tx][ty] == 1) continue;
        tx = aa.lin + 2; 
        if(mp[tx][ty] == 1) continue; 
        tx = aa.lin + 3; 
        if(mp[tx][ty] == 1) continue;  
        if(vis[tx][ty] == 1) continue; 
        vis[tx][ty] = 1;
        bb.lin = tx;
        bb.col = ty;
        q.push(bb); 
    }
    q.pop();
}
```
3. **作者：Prurite（4星）**
    - **关键亮点**：明确提出搜索思路和注意事项，代码规范，使用命名空间防止重名冲突。
    - **核心代码**：
```cpp
inline void dfs( int nowx, int nowy )
{
    if ( nowy>=len ) 
        can_arrive=1;
    if ( can_arrive ) 
        return;
    if ( map[nowx][nowy]==0 ) 
        return;
    if ( vis[nowx][nowy] ) 
        return;
    vis[nowx][nowy]=1; 
    for ( int i=-1; i<=1; i++ )
        if ( map[nowx][nowy+1] && map[nowx+i][nowy+1] 
        && map[nowx+i][nowy+2] && map[nowx+i][nowy+3] )
            dfs( nowx+i, nowy+3 );
    return;
}
```

### 最优关键思路或技巧
- **运动相对性**：将火车向左移动转化为人向右多移动，避免处理火车移动，简化代码。
- **搜索剪枝**：使用标记数组记录访问过的点，避免重复搜索，提高效率。

### 可拓展之处
同类型题可能有不同地图形状、移动规则或障碍物类型，但都可使用搜索算法解决。类似算法套路是利用相对性简化问题，使用标记数组剪枝。

### 推荐题目
1. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：涉及搜索和状态转移，与本题搜索路径思路相似。
2. [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：经典的迷宫搜索问题，可使用DFS或BFS求解。
3. [P2895 [USACO08FEB]Meteor Shower S](https://www.luogu.com.cn/problem/P2895)：需要考虑时间和障碍物，使用搜索算法解决。

### 个人心得摘录与总结
- **dyc2022**：意识到题目中火车列数和火车具体表示无用，将火车左移转化为人右移简化操作和复杂度。
总结：解题时要分析题目条件，去除无用信息，利用相对性等方法简化问题。 

---
处理用时：45.11秒