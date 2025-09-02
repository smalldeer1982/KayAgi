# 题目信息

# [BalticOI 2013] Tracks in the Snow

## 题目描述

有一个含 $H$ 行，$W$ 列的字符矩阵，初始全为 `.`。

有两种动物，狐狸和兔子，将会从左上角走到右下角，狐狸会留下 `F` 的痕迹，兔子会留下 `R` 的痕迹。

痕迹会相互覆盖。

走路规则如下：
- 可以往返走；
- 不可以走对角线；
- 不可以跳格子；
- 不可能有两只动物一起走。

现在您得到了这个被动物们走过的矩阵，请求出至少有几个动物走过了该矩阵。

## 说明/提示

#### 数据范围及限制
- 对于 $30$ 分的数据，保证答案 $\le 200$，$H,W\le 500$。
- 对于 $100\%$ 的数据，保证 $1\le H,W\le 4\times 10^3$，答案 $\ge 1$，读入的字符只会是 `.` 或 `R` 或 `F`。

#### 说明
本题译自 [Baltic Olympiad in Informatics 2013](https://boi.cses.fi/tasks.php) [Day 2](https://boi.cses.fi/files/boi2013_day2.pdf) T2 Tracks in the Snow。

## 样例 #1

### 输入

```
5 8
FFR.....
.FRRR...
.FFFFF..
..RRRFFR
.....FFF```

### 输出

```
2```

# AI分析结果

### 算法分类
广度优先搜索 BFS

### 综合分析与结论
本题的核心是通过倒推脚印覆盖的过程，确定最少需要多少只动物。大多数题解采用了BFS的思路，从终点开始，逐步扩展连通块，并通过交替取反脚印来模拟动物的交替行走。难点在于如何高效地处理大矩阵的BFS，避免重复搜索和内存溢出。优化方法包括使用队列存储下一次搜索的起点，减少递归深度，以及通过标记已访问节点来避免重复搜索。

### 所选题解
1. **作者：THM200000000 (5星)**
   - **关键亮点**：通过栈优化BFS，减少内存消耗，避免重复搜索，最终实现完美AC。
   - **个人心得**：作者在调试过程中经历了多次优化，最终通过栈代替递归解决了MLE问题，强调了优化的重要性。
   - **核心代码**：
     ```cpp
     void dfs(char tp) {
         while(l) {
             tmp = now[l--];
             if(a[tmp.x][tmp.y] == chg(tp)) {
                 nxt[++t] = tmp;
                 continue;
             }
             vis[tmp.x][tmp.y] = true;
             if(a[tmp.x + 1][tmp.y] != '.' && !vis[tmp.x + 1][tmp.y] && tmp.x != n)
                 now[++l] = {tmp.x + 1, tmp.y};
             if(a[tmp.x - 1][tmp.y] != '.' && !vis[tmp.x - 1][tmp.y] && tmp.x != 1)
                 now[++l] = {tmp.x - 1, tmp.y};
             if(a[tmp.x][tmp.y + 1] != '.' && !vis[tmp.x][tmp.y + 1] && tmp.y != m)
                 now[++l] = {tmp.x, tmp.y + 1};
             if(a[tmp.x][tmp.y - 1] != '.' && !vis[tmp.x][tmp.y - 1] && tmp.y != 1)
                 now[++l] = {tmp.x, tmp.y - 1};
         }
     }
     ```

2. **作者：zfhzzzzzzzzzzz (4星)**
   - **关键亮点**：使用双队列交替BFS，清晰简洁地实现了脚印的交替覆盖。
   - **核心代码**：
     ```cpp
     bool bfs(int s) {
         bool fl = 0;
         while (!q[s].empty()) {
             int x = q[s].front().first, y = q[s].front().second;
             q[s].pop();
             for(int i = 0; i < 4; i++) {
                 int fx = x + dx[i], fy = y + dy[i];
                 if(fx > 0 && fx <= n && fy > 0 && fy <= m && a[fx][fy] && !vis[fx][fy]){
                     vis[fx][fy] = 1;
                     if(a[x][y] == a[fx][fy]) 
                         q[s].push(make_pair(fx, fy));
                     else{
                         q[s^1].push(make_pair(fx, fy));
                         fl = 1;
                     }
                 }
             }
         }
         return fl;
     }
     ```

3. **作者：Starlight_Glimmer (4星)**
   - **关键亮点**：通过BFS扩展连通块，交替取反脚印，思路清晰，代码结构良好。
   - **核心代码**：
     ```cpp
     void bfs() {
         int now;
         if(s[1][1] == 'R') Q[0].push(1), now = 0;
         else Q[1].push(1), now = 1;
         while(!Q[now].empty()) {
             while(!Q[now].empty()) {
                 int x = Q[now].front(); Q[now].pop();
                 int j = x % m, i = x / m + 1;
                 if(j == 0) j = m, i--;
                 if(vis[i][j]) continue;
                 vis[i][j] = true;
                 for(int k = 0; k < 4; k++) {
                     int x = i + dx[k], y = j + dy[k];
                     if(!check(x, y)) continue;
                     if(s[x][y] == s[i][j]) Q[now].push((x - 1) * m + y);
                     else Q[now ^ 1].push((x - 1) * m + y);
                 }
             }
             now ^= 1;
             ans++;
         }
     }
     ```

### 最优关键思路
1. **倒推脚印覆盖**：从终点开始，逐步扩展连通块，并通过交替取反脚印来模拟动物的交替行走。
2. **优化BFS**：使用队列存储下一次搜索的起点，减少递归深度，避免重复搜索和内存溢出。
3. **交替取反**：通过交替取反脚印，确保每次扩展的连通块代表不同动物的足迹。

### 可拓展之处
类似的问题可以扩展到其他覆盖类问题，如地图染色、路径覆盖等。通过倒推和交替取反的思路，可以解决类似的覆盖问题。

### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)

### 个人心得摘录
- **THM200000000**：通过栈优化BFS，解决了MLE问题，强调了优化的重要性。
- **Starlight_Glimmer**：通过BFS扩展连通块，交替取反脚印，思路清晰，代码结构良好。

---
处理用时：46.72秒