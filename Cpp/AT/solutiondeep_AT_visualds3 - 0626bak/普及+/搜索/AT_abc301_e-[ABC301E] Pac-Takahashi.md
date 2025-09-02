# 题目信息

# [ABC301E] Pac-Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc301/tasks/abc301_e

$ H $ 行 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマス目を $ (i,j) $ と表します。 グリッドの各マスはスタートマス、ゴールマス、空マス、壁マス、お菓子マスのいずれかです。 $ (i,j) $ が何のマスであるかは文字 $ A_{i,j} $ によって表され、$ A_{i,j}= $ `S` のときスタートマス、 $ A_{i,j}= $ `G` のときゴールマス、 $ A_{i,j}= $ `.` のとき空マス、 $ A_{i,j}= $ `#` のとき壁マス、 $ A_{i,j}= $ `o` のときお菓子マスです。 ここで、スタートマスとゴールマスはちょうど $ 1 $ つずつあり、お菓子マスは **$ 18 $ 個以下**であることが保証されます。

高橋くんは現在スタートマスにいます。 高橋くんは、上下左右に隣接するマスであって壁マスでないマスに移動することを繰り返し行えます。 高橋くんは今から $ T $ 回以下の移動によってゴールマスに到達したいです。 そのようなことは可能かどうか判定してください。 可能な場合は、最終的にゴールマスにいるという条件のもとで、移動の途中に訪れるお菓子マスの数の最大値を求めてください。 ただし、$ 1 $ つのお菓子マスに複数回訪れた場合でも、カウントするのは $ 1 $ 回のみです。

## 说明/提示

### 制約

- $ 1\leq\ H,W\ \leq\ 300 $
- $ 1\ \leq\ T\ \leq\ 2\times\ 10^6 $
- $ H,W,T $ は整数
- $ A_{i,j} $ は `S`, `G`, `.`, `#`, `o` のいずれか
- $ A_{i,j}= $ `S` を満たす $ (i,j) $ の組がちょうど $ 1 $ つ存在する
- $ A_{i,j}= $ `G` を満たす $ (i,j) $ の組がちょうど $ 1 $ つ存在する
- $ A_{i,j}= $ `o` を満たす $ (i,j) $ の組は **$ 18 $ 個以下**
 
### Sample Explanation 1

$ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (1,3)\ \rightarrow\ (2,3)\ \rightarrow\ (1,3) $ と $ 4 $ 回移動すると、 $ 1 $ 個のお菓子マスを訪れた上で最終的にゴールマスにいることができます。 $ 5 $ 回以下の移動で $ 2 $ 個のお菓子マスを訪れた上で最終的にゴールマスにいることはできないので、$ 1 $ が答えです。 なお、$ (1,1)\ \rightarrow\ (2,1)\ \rightarrow\ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (1,3)\ \rightarrow\ (2,3) $ と移動すると $ 5 $ 回の移動で $ 2 $ 個のお菓子マスを訪れることができますが、最終的にゴールマスにいないため無効であることに注意してください。

### Sample Explanation 2

$ 1 $ 回以下の移動でゴールマスに到達することはできません。

## 样例 #1

### 输入

```
3 3 5

S.G

o#o

.#.```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3 1

S.G

.#o

o#.```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 10 2000000

S.o..ooo..

..o..o.o..

..o..ooo..

..o..o.o..

..o..ooo.G```

### 输出

```
18```

# AI分析结果



### 唯一算法分类  
**BFS**

### 题解思路、算法要点与解决难点  
1. **核心思路**  
   预处理所有关键点（起点、终点、糖果）间的最短路径，构建状态压缩动态规划（状压DP）模型，求解在时间限制内的最大糖果收集数。

2. **算法要点**  
   - **BFS预处理**：对每个关键点（包括起点、终点、糖果）执行BFS，计算其到其他关键点的最短路径。  
   - **状压DP**：状态表示为 `dp[i][mask]`，其中 `i` 是当前所在点，`mask` 是已访问的糖果集合（二进制位表示）。转移方程为：  
     ```
     dp[j][mask | (1<<j)] = min(dp[j][mask | (1<<j)], dp[i][mask] + dis[i][j])
     ```
   - **路径合法性检查**：最终路径需满足总步数 ≤ T，且必须到达终点。

3. **解决难点**  
   - **状态爆炸**：糖果最多18个，状态数达 2^18 × 20 ≈ 5.2e6，需高效状态转移。  
   - **预处理复杂度**：BFS预处理的总复杂度为 O(20 × H × W)，H、W为网格行列数。  
   - **终点处理**：需确保路径最终到达终点，而非中途停留。

---

### 题解评分 (≥4星)  
1. **DengDuck (5星)**  
   - **亮点**：代码结构清晰，预处理与DP分离；状态初始化明确；利用位运算高效处理集合。  
   - **核心代码**：  
     ```cpp
     // BFS预处理所有关键点距离
     LL work(LL i, LL j) { ... }
     // 状压DP转移
     for (int k=1; k<=cnt; k++) {
         f[k][i|(1<<(k-1))] = min(f[k][i|(1<<(k-1))], f[j][i] + dis[j][k]);
     }
     ```

2. **sunzz3183 (4星)**  
   - **亮点**：按阶段（已选糖果数）分组处理状态，减少无效计算；代码注释详细。  
   - **核心代码**：  
     ```cpp
     // 按阶段转移
     for (int szz=1; szz<=cnt; szz++) {
         for (int cyl=0; cyl<vt[szz].size(); cyl++) {
             int i=vt[szz][cyl];
             for (int j=1; j<=cnt; j++) {
                 for (int l=1; l<=cnt; l++) {
                     f[i|(1<<(l-1))][l] = min(...);
                 }
             }
         }
     }
     ```

3. **Kylin_ZHH (4星)**  
   - **亮点**：DFS记忆化搜索实现状压DP，代码简洁；终点处理逻辑明确。  
   - **核心代码**：  
     ```cpp
     int dfs(int now, int ztm) {
         if (ztm==0) return dis[so][now];
         if (vis[now][ztm]) return dp[now][ztm];
         // 记忆化搜索转移
         for (int i=0; i<to; i++) if (ztm>>i&1) 
             dp[now][ztm] = min(...);
     }
     ```

---

### 最优思路或技巧提炼  
1. **关键点预处理**  
   - 将起点、终点、糖果统一编号，建立完全图。  
   - 对每个关键点执行BFS，计算其到其他点的最短距离，时间复杂度 O(20 × H × W)。  

2. **状态压缩DP优化**  
   - **状态定义**：`dp[i][mask]` 表示当前在点 `i`，已访问集合为 `mask` 的最小步数。  
   - **转移剪枝**：仅当 `dp[i][mask] + dis[i][j] ≤ T` 时更新状态，避免无效计算。  

3. **终点强制检查**  
   - 最终需遍历所有状态，检查 `dp[i][mask] + dis[i][终点] ≤ T`，确保路径合法。  

---

### 同类型题或类似算法套路  
- **旅行商问题（TSP）**：如洛谷 P1433（吃奶酪）、P1171（售货员的难题）。  
- **网格最短路径 + 状压DP**：如 AtCoder ABC180E（Traveling Salesman Problem）。  
- **多关键点路径规划**：如 Codeforces 1324E（Sleeping Schedule）。  

---

### 推荐相似题目  
1. **P1433 吃奶酪**  
   - **关键词**：状压DP、欧几里得距离、TSP变形。  
2. **ABC180E Traveling Salesman Problem**  
   - **关键词**：三维坐标、状压DP、TSP。  
3. **P2322 [HNOI2006] 最短距离**  
   - **关键词**：网格BFS、多关键点预处理。  

---

### 个人心得摘录  
- **DengDuck**：  
  > “注意起点和终点必须包含在状态中，否则可能漏判路径合法性。”  
- **sunzz3183**：  
  > “按阶段分组处理状态，避免重复计算，是减少时间复杂度的关键。”  
- **Kylin_ZHH**：  
  > “DFS记忆化写法比循环更直观，但需注意递归深度和栈空间限制。”  

---

### 可视化与算法演示  
#### 动画设计  
1. **BFS预处理阶段**  
   - **像素风格网格**：红色方块表示起点，绿色表示终点，黄色为糖果，灰色为障碍。  
   - **BFS扩散效果**：从当前关键点（如起点）出发，逐步扩散到周围节点，扩散颜色渐变（如蓝色→浅蓝）。  
   - **音效**：每次扩散到新节点时播放“滴”声，找到终点时播放“叮咚”声。  

2. **状压DP阶段**  
   - **状态转移可视化**：用二进制位显示当前已访问的糖果集合（如 `000101` 表示已访问第1、3个糖果）。  
   - **路径绘制**：在完全图上高亮当前转移的边（如从点 `i` 到 `j`），并显示累计步数。  

#### 交互功能  
- **速度调节**：滑动条控制BFS扩散速度和DP转移速度。  
- **单步执行**：支持暂停/继续，观察每一步的状态变化。  
- **失败提示**：若最终无解，播放低沉音效并显示“-1”。  

#### 复古风格代码片段（JavaScript）  
```javascript
// Canvas绘制关键点（8位风格）
function drawPixelGrid(ctx) {
    for (let i=0; i<H; i++) {
        for (let j=0; j<W; j++) {
            if (grid[i][j] === 'S') ctx.fillStyle = '#FF0000'; // 红色起点
            else if (grid[i][j] === 'G') ctx.fillStyle = '#00FF00'; // 绿色终点
            else if (grid[i][j] === 'o') ctx.fillStyle = '#FFFF00'; // 黄色糖果
            ctx.fillRect(j*10, i*10, 8, 8); // 8x8像素方块
        }
    }
}
```

---

### 完整代码（DengDuck题解）  
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL dx[4]={0,0,1,-1}, dy[4]={1,-1,0,0};
struct node { LL x,y,num; };
LL n,m,t,dis[25][25],a[305][305],vis[305][305],sx,sy,ex,ey,cnt,f[25][3000005],mx;
pair<LL,LL> pt[25];
queue<node>q;

LL work(LL i, LL j) { // BFS计算点i到点j的距离
    LL sx=pt[i].first, sy=pt[i].second, ex=pt[j].first, ey=pt[j].second;
    q.push({sx,sy,0});
    memset(vis,0,sizeof(vis));
    while (!q.empty()) {
        LL tx=q.front().x, ty=q.front().y, num=q.front().num; q.pop();
        for (int i=0; i<4; i++) {
            LL xx=tx+dx[i], yy=ty+dy[i];
            if (xx<1 || xx>n || yy<1 || yy>m || a[xx][yy] || vis[xx][yy]) continue;
            vis[xx][yy]=1;
            q.push({xx,yy,num+1});
            if (xx==ex && yy==ey) return num+1;
        }
    }
    return INT_MAX;
}

int main() {
    cin>>n>>m>>t;
    // 初始化关键点
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            char c; cin>>c;
            if (c=='S') sx=i, sy=j;
            else if (c=='G') ex=i, ey=j;
            else if (c=='o') pt[++cnt] = {i,j};
            else if (c=='#') a[i][j]=1;
        }
    }
    pt[++cnt] = {sx,sy}, pt[++cnt] = {ex,ey}; // 起点和终点编号为cnt-1和cnt
    // 预处理距离
    for (int i=1; i<=cnt; i++)
        for (int j=i+1; j<=cnt; j++)
            dis[i][j] = dis[j][i] = work(i,j);
    // 状压DP
    memset(f,127,sizeof(f));
    f[cnt-1][1<<(cnt-2)] = 0;
    for (int mask=(1<<(cnt-2)); mask<(1<<cnt); mask++) {
        for (int j=1; j<=cnt; j++) {
            if (!(mask & (1<<(j-1)))) continue;
            for (int k=1; k<=cnt; k++) {
                LL new_mask = mask | (1<<(k-1));
                f[k][new_mask] = min(f[k][new_mask], f[j][mask] + dis[j][k]);
            }
        }
    }
    // 统计答案
    for (int mask=0; mask<(1<<cnt); mask++) {
        if (!(mask & (1<<(cnt-1))) || !(mask & (1<<(cnt-2)))) continue;
        if (f[cnt][mask] > t) continue;
        LL sum = __builtin_popcount(mask) - 2; // 排除起点和终点
        mx = max(mx, sum);
    }
    cout << (mx >=0 ? mx : -1);
}
```

---
处理用时：117.42秒