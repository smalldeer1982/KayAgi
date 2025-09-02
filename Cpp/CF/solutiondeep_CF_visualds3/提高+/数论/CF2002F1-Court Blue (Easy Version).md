# 题目信息

# Court Blue (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ n=m $ and the time limit is lower. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Lelle wins, $ \gcd(2,3)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 2\cdot2+3\cdot5=19 $ .

In the third test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Lelle wins, $ \gcd(2,1)=1 $ .
- Lelle wins, $ \gcd(3,1)=1 $ .
- Lelle wins, $ \gcd(4,1)=1 $ .
- Lelle wins, $ \gcd(5,1)=1 $ .
- Flamm wins, $ \gcd(5,2)=1 $ .
- Flamm wins, $ \gcd(5,3)=1 $ .
- Flamm wins, $ \gcd(5,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 5\cdot2+4\cdot2=18 $ . Note that Lelle and Flamm can stop the match even if neither of them has $ n $ wins.

## 样例 #1

### 输入

```
8
3 3 2 5
4 4 1 4
6 6 2 2
7 7 2 3
9 9 9 1
2 2 1 4
5 5 1 4
8 8 6 7```

### 输出

```
19
17
18
33
86
9
24
86```

## 样例 #2

### 输入

```
1
20000000 20000000 1341 331```

### 输出

```
33439999007```

## 样例 #3

### 输入

```
2
1984 1984 19 84
9982 9982 44 35```

### 输出

```
204143
788403```

# AI分析结果


### 💡 Kay的C++算法解析：Court Blue (Easy Version) 深入学习指南 💡

#### 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`图遍历(BFS) + 数论(质数应用)`  

🗣️ **初步分析**：  
> 本题可比喻为"互质迷宫探险"：表演者需在网格中移动（每次增加W_L或W_F），要求每一步gcd(W_L,W_F)=1（如同踩在安全地砖上）。核心策略是利用质数的互质特性构建"安全起点"，再通过BFS探索局部最优路径。  
> - **题解思路**：先定位≤n的最大质数p和次大质数q（安全起点），在(p,q)到(n,n)的局部区域暴力搜索。当n≤16时直接全局BFS（难点：证明最优解必在质数附近）。  
> - **可视化设计**：像素网格中，质数位置显示为金色地砖，互质路径亮绿色，阻塞路径红色。BFS探索时显示队列扩散动画，伴随"叮"音效标记新节点入队，胜利音效在找到最优解时触发。  

---

#### 2. 精选优质题解参考  
**题解一（int08）**  
* **点评**：思路清晰解释了"质数安全区"原理（图例辅助理解），代码规范（`fp/sp`变量名明确指代质数）。亮点在于：  
  1. 预处理质数筛（埃氏筛）高效支持大范围查询  
  2. BFS前初始化边界条件严谨（`vis`数组过滤非互质点）  
  3. 实践价值高：直接处理2e7数据规模，边界`n≤16`的fallback设计合理  

**题解二（COsm0s）**  
* **点评**：核心思路与题解一一致，亮点在于简洁的状态转移设计：  
  - 用`q[i][j]`记录可达性，通过`q[i][j] = q[i-1][j] || q[i][j-1]`实现DP式递推  
  - 优化点：省去队列操作，以空间换代码简洁性  
  - 注意：未显式处理`n≤16`可能存在的边界风险  

---

#### 3. 核心难点辨析与解题策略  
1. **难点1：如何确定搜索起点？**  
   * **分析**：利用质数性质——质数p与所有<p的数互质。优质题解选取≤n的最大/次大质数作为安全起点，确保起点附近路径必然满足gcd条件。  
   * 💡 **学习笔记**：质数是天然的"互质安全港"  

2. **难点2：如何避免全图搜索？**  
   * **分析**：观察到最优解必在质数附近区域（相邻质数差≈O(log n)）。题解将搜索范围缩小到`[p, n]×[q, n]`，复杂度从O(n²)降为O(log²n)。  
   * 💡 **学习笔记**：数学性质可大幅剪枝  

3. **难点3：如何处理小规模数据？**  
   * **分析**：当n≤16时质数性质不显著，两题解均切换为暴力BFS。关键技巧是设计`vis`数组快速验证互质性。  
   * 💡 **学习笔记**：算法选择需适配数据规模  

**✨ 解题技巧总结**  
- **质数筛预处理**：埃氏筛/O(n)线性筛处理大范围质数查询  
- **状态可达性传递**：BFS队列扩展或DP递推`q[i][j]=q[i-1][j]||q[i][j-1]`  
- **边界fallback机制**：小规模数据切换暴力确保正确性  

---

#### 4. C++核心代码实现赏析  
**通用核心实现参考**  
```cpp
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 20000005;
vector<int> primes;
bool isComp[MAX]; // 合数标记

void initPrimes() { // 线性筛预处理
    for(int i=2; i<MAX; ++i) {
        if(!isComp[i]) primes.push_back(i);
        for(int p : primes) {
            if(i*p >= MAX) break;
            isComp[i*p] = true;
            if(i%p == 0) break;
        }
    }
}

int solve(int n, int l, int f) {
    if(n <= 16) { /* 暴力BFS */ }
    int p = *(lower_bound(primes.begin(), primes.end(), n) - 1); // 最大质数
    int q = *(lower_bound(primes.begin(), primes.end(), p) - 1); // 次大质数
    int ans = 0;
    // 局部区域BFS (代码见题解2)
    return ans;
}
```

**题解一（int08）片段赏析**  
```cpp
queue<pair<int,int>> q;
q.push({1, 1}); // 相对坐标起点
while(!q.empty()) {
    auto [i,j] = q.front(); q.pop();
    int x = fp-1+i, y = sp-1+j; // 绝对坐标
    ans = max(ans, x*l + y*f); // 更新得分
    if(vis[i+1][j]) { // 向右探索
        vis[i+1][j] = 0;
        q.push({i+1, j});
    }
    if(vis[i][j+1]) { // 向上探索
        vis[i][j+1] = 0;
        q.push({i, j+1});
    }
}
```
* **代码解读**：  
  > 1. BFS队列存储相对坐标`(i,j)`，映射到绝对坐标`(fp+i-1, sp+j-1)`  
  > 2. 每次扩展检查右/上两个方向（因W_L/W_F单增）  
  > 3. 实时更新最大得分`ans`，避免回溯存储路径  
* 💡 **学习笔记**：BFS队列自动按层扩展，天然满足路径最优性  

---

#### 5. 算法可视化：像素动画演示  
**主题**："质数迷宫探险"（8-bit像素风）  

**核心演示流程**：  
1. **场景初始化**：  
   - 网格地图：起点(0,0)为蓝色，质数位置金色，互质路径亮绿  
   - 控制面板：速度滑块/单步/自动播放按钮（复古游戏风格）  
   - 音效：背景8-bit音乐循环  

2. **BFS动态演示**：  
   ```mermaid
   graph LR
   A[当前节点闪烁] --> B[检查右/上邻居]
   B -- gcd=1 --> C[绿色路径延伸+入队音效]
   B -- gcd>1 --> D[红色阻塞+警示音效]
   C --> E[更新分数显示]
   ```

3. **游戏化元素**：  
   - 每扩展10个节点触发"关卡完成"音效，显示当前最高分  
   - 找到最优解时：金色路径闪烁 + 胜利音效 + 得分烟花动画  
   - 错误操作提示：尝试非互质移动时像素震动+短促警报音  

**技术实现**：  
- 用Canvas绘制网格，路径动画通过重绘色块实现  
- 音效触发：Web Audio API播放8-bit音效片段  

---

#### 6. 拓展练习与相似问题  
1. **洛谷 P1217**：利用质数性质构造回文数  
   → 巩固质数筛法应用  
2. **洛谷 P1443**：网格BFS求最短路径  
   → 练习基础BFS实现  
3. **洛谷 P3956**：带状态约束的路径优化  
   → 迁移互质条件处理思想  

---

#### 7. 学习心得与经验分享  
> **参考经验（int08）**：  
> *"BFS写挂吃了两发，务必检查队列初始化边界！"*  
> **Kay点评**：经典教训！BFS中未访问节点的初始状态必须显式设置，推荐：  
> 1. 使用`vis[][]`数组统一初始化  
> 2. 起点状态必须显式入队  
> 3. 优先处理边界条件（如n较小时）  

---  
💪 掌握质数性质与BFS结合技巧，此类路径约束问题将迎刃而解！下次见~

---
处理用时：98.26秒