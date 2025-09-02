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



**唯一算法分类**：数学 + BFS/暴力枚举

---

### 题解思路、算法要点与解决难点

#### 核心思路
1. **数学性质利用**：观察到互质对（尤其是质数）的分布特性，选择最大质数附近区域作为搜索起点。
2. **预处理素数表**：使用筛法预处理所有可能的质数，快速定位最大和次大质数。
3. **区域剪枝**：对于大范围数据，将搜索范围限制在最大质数附近的有限区域（如质数到n的矩形区域）。
4. **状态搜索**：通过BFS或暴力枚举，遍历可能的合法点对，计算最大得分。

#### 解决难点
- **互质条件维护**：每一步操作后必须保证gcd(W_L, W_F) ≤ 1。
- **高效搜索空间**：直接遍历所有点对不可行，利用质数性质缩小搜索范围是关键。
- **边界处理**：n较小时需直接暴力枚举，质数不存在时需特殊处理。

---

### 题解评分（≥4星）

1. **int08的BFS解法（★★★★☆）**
   - **亮点**：利用BFS高效探索状态空间，预处理质数表减少计算量。
   - **优化**：动态剪枝，仅扩展合法状态，避免重复计算。
   - **代码清晰**：队列实现简洁，状态标记明确。

---

### 最优思路或技巧提炼
- **质数跳板策略**：以最大质数作为起点，极大缩减搜索范围。
- **分层扩展（BFS）**：确保优先探索更优解（如更大坐标点）。
- **小范围暴力处理**：当n较小时直接枚举，避免复杂逻辑。

---

### 同类型题或类似算法套路
- **互质路径问题**：如LeetCode 914（卡牌分组），需维护路径上的gcd条件。
- **质数优化问题**：如统计区间内质数对数量，结合筛法预处理。
- **贪心+数学性质**：如选择质数作为关键点，结合动态规划或搜索。

---

### 推荐洛谷题目
1. **P1072 Hankson的趣味题**（数学条件判断）
2. **P2568 GCD**（互质对统计）
3. **P1372 又是毕业季I**（gcd应用与最优化）

---

### 可视化与算法演示设计
#### 核心动画方案
- **像素网格表示**：将点对(W_L, W_F)映射为网格坐标，合法点显示为绿色，当前探索点高亮为红色。
- **BFS扩展过程**：动态展示队列中待处理点的扩展方向（右/上移动），每步更新得分最大值。
- **音效反馈**：
  - **探索新点**：播放“滴”声。
  - **发现更高分**：播放上升音阶。
  - **非法点**：播放低沉音效。

#### 复古像素风格实现
- **Canvas绘制**：采用16色调色板，网格大小为16x16像素，模拟FC风格。
- **自动演示模式**：算法自动执行，每步延迟200ms，允许暂停/加速。
- **积分系统**：每探索100个点奖励10分，找到最优解时额外加分。

---

### 关键代码实现（int08解法）
```cpp
// 预处理素数表
vector<int> prime;
bool np[20000001];
void sieve() {
    for(int i=2; i<=2e7; i++) {
        if(!np[i]) prime.push_back(i);
        for(int p : prime) {
            if(i*p > 2e7) break;
            np[i*p] = 1;
            if(i%p == 0) break;
        }
    }
}

// BFS核心逻辑
int fp = largest_prime(n); // 最大质数
int sp = second_largest_prime(n); // 次大质数
queue<pair<int,int>> q;
q.push({1,1});
while(!q.empty()) {
    auto [i,j] = q.front(); q.pop();
    ans = max(ans, (fp+i-1)*l + (sp+j-1)*f);
    // 扩展右方和上方合法点
    if(valid(i+1,j)) markVisited(i+1,j), q.push({i+1,j});
    if(valid(i,j+1)) markVisited(i,j+1), q.push({i,j+1});
}
```

---

### 综合结论
通过预处理质数表与BFS结合，将问题转化为有限区域的最优路径搜索，有效平衡了时间效率与正确性，适用于大范围数据。核心思维在于数学性质与算法设计的深度结合。

---
处理用时：90.65秒