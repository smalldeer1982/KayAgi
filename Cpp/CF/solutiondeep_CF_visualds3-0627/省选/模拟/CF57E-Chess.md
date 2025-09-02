# 题目信息

# Chess

## 题目描述

Brian the Rabbit adores chess. Not long ago he argued with Stewie the Rabbit that a knight is better than a king. To prove his point he tries to show that the knight is very fast but Stewie doesn't accept statements without evidence. He constructed an infinite chessboard for Brian, where he deleted several squares to add some more interest to the game. Brian only needs to count how many different board squares a knight standing on a square with coordinates of $ (0,0) $ can reach in no more than $ k $ moves. Naturally, it is forbidden to move to the deleted squares.

Brian doesn't very much like exact sciences himself and is not acquainted with programming, that's why he will hardly be able to get ahead of Stewie who has already started solving the problem. Help Brian to solve the problem faster than Stewie.

## 样例 #1

### 输入

```
1 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2 7
-1 2
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1
```

### 输出

```
9
```

# AI分析结果



---

## **唯一算法分类**  
**BFS + 数学分析**

---

## **综合分析与结论**  
### **核心思路与难点**  
1. **问题核心**：计算骑士在无限棋盘上，最多经过 `k` 步能到达的未被删除的格子数。  
2. **直接暴力 BFS 的缺陷**：无限棋盘导致状态爆炸，无法处理大 `k`。  
3. **关键观察**：当 `k` 足够大时（如 `k ≥ 5`），每步新增可达格子数趋于稳定，形成公差为 **28** 的等差数列。  
4. **解决难点**：  
   - **障碍处理**：障碍仅影响早期扩展，不影响稳定后的等差数列规律（需假设障碍稀疏且远离原点）。  
   - **数学建模**：通过打表发现稳定后的增量规律，结合 BFS 预处理早期步数。  

### **算法流程**  
1. **BFS 预处理**：对前 `step` 步（如 `step = 456`）进行 BFS，记录每步新增的可达格子数。  
2. **分情况计算**：  
   - 若 `k ≤ step`：直接累加预处理结果。  
   - 若 `k > step`：累加前 `step` 步结果，剩余步数按等差数列求和公式计算。  

### **可视化设计**  
- **动画方案**：  
  - **阶段 1（BFS 扩展）**：以网格展示骑士逐步扩展，颜色标记不同步数的可达区域（如红色表示初始位置，渐变色表示后续步数）。  
  - **阶段 2（等差数列）**：当步数超过 `step` 时，用动态增长的矩形框表示等差数列的线性增长，高亮公差 **28**。  
- **交互设计**：  
  - **速度控制**：允许调整 BFS 扩展速度，观察早期步数如何被障碍截断。  
  - **音效提示**：触发等差数列时播放上扬音效，增强规律发现的直观性。  

---

## **题解清单 (≥4星)**  
### **题解 1：ttq012（★★★★☆）**  
- **亮点**：简洁提出打表与公式结合，代码实现高效。  
- **关键代码**：  
  ```cpp  
  if (k < 500) { /* 累加前 k 步 */ }  
  else { /* 公式计算 */ }  
  ```

### **题解 2：封禁用户（★★★★☆）**  
- **亮点**：数学证明与区域分解，增强规律的可信度。  
- **结论**：当 `k ≥ 5`，答案公式为 `28k - 20`。  

### **题解 3：pufanyi（★★★★☆）**  
- **亮点**：详细打表验证，代码可复现性强。  
- **个人心得**：  
  > “经过多次验证，发现障碍不影响稳定后的公差，因此可以放心使用公式。”  

---

## **最优思路与技巧提炼**  
### **关键技巧**  
1. **打表找规律**：通过小规模 BFS 输出增量，观察等差数列的出现时机。  
2. **分阶段处理**：暴力处理早期步数，数学公式处理后期步数。  
3. **稀疏障碍假设**：假设障碍不影响稳定后的线性增长，简化问题复杂度。  

### **同类型题**  
- **CF 37D Lesson Timetable**：动态规划结合周期性规律。  
- **洛谷 P2735 [USACO3.4] 网 Electric Fences**：几何+BFS优化。  

---

## **推荐相似题目**  
1. **洛谷 P1219 八皇后**（BFS+对称性优化）  
2. **CF 13E Holes**（分块处理+数学分析）  
3. **洛谷 P1379 八数码难题**（BFS+哈希优化）  

---

## **代码实现（核心片段）**  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  
const int MAXN = 2003, MOD = 1e9+7;  
int mp[MAXN][MAXN], ans[MAXN];  
int dirx[] = {1,1,-1,-1,2,2,-2,-2};  
int diry[] = {2,-2,2,-2,1,-1,1,-1};  

struct Node { int x, y; };  
queue<Node> q;  

void bfs(int x0, int y0) {  
    mp[x0][y0] = 1;  
    q.push({x0, y0});  
    while (!q.empty()) {  
        Node u = q.front(); q.pop();  
        ans[mp[u.x][u.y]]++;  
        if (mp[u.x][u.y] > 456) break;  
        for (int i=0; i<8; i++) {  
            int nx = u.x + dirx[i], ny = u.y + diry[i];  
            if (nx<0 || ny<0 || nx>=MAXN || ny>=MAXN || mp[nx][ny]) continue;  
            mp[nx][ny] = mp[u.x][u.y] + 1;  
            q.push({nx, ny});  
        }  
    }  
}  

int main() {  
    int k, n; cin >> k >> n;  
    bfs(1001, 1001); // 中心点偏移  
    while (n--) {  
        int x, y; cin >> x >> y;  
        if (abs(x) > 1000 || abs(y) > 1000) continue;  
        mp[x+1001][y+1001] = 1; // 标记障碍  
    }  
    long long res = 0;  
    if (k <= 456) {  
        for (int i=0; i<=k; i++) res += ans[i];  
    } else {  
        for (int i=0; i<=456; i++) res += ans[i];  
        res = (res + 28LL * (k - 456) % MOD) % MOD;  
    }  
    cout << res % MOD;  
}  
```

---

## **可视化与游戏化设计**  
### **复古像素风格**  
- **颜色方案**：16色调色板，红色表示初始位置，绿色表示扩展区域，黑色表示障碍。  
- **Canvas 动画**：  
  - 绘制 `100x100` 网格，动态扩展骑士可达区域。  
  - 当步数超过 `456` 时，切换为线性增长的矩形动画。  
- **音效**：  
  - **扩展音效**：8-bit “哔”声，每扩展一步播放一次。  
  - **公式触发**：播放经典《超级马里奥》金币音效。  

### **自动演示模式**  
- **AI 决策**：自动运行 BFS 直到达到稳定步数，随后切换公式计算。  
- **关卡设计**：  
  - **关卡 1**：无障碍，观察等差数列形成。  
  - **关卡 2**：随机生成障碍，验证公式的鲁棒性。

---
处理用时：89.63秒