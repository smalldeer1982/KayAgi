# 题目信息

# A Trance of Nightfall

## 题目描述

 The cool breeze blows gently, the flowing water ripples steadily."Flowing and passing like this, the water isn't gone ultimately; Waxing and waning like that, the moon doesn't shrink or grow eventually."

"Everything is transient in a way and perennial in another."

Kanno doesn't seem to make much sense out of Mino's isolated words, but maybe it's time that they enjoy the gentle breeze and the night sky — the inexhaustible gifts from nature.

Gazing into the sky of stars, Kanno indulges in a night's tranquil dreams.





There is a set $ S $ of $ n $ points on a coordinate plane.

Kanno starts from a point $ P $ that can be chosen on the plane. $ P $ is not added to $ S $ if it doesn't belong to $ S $ . Then the following sequence of operations (altogether called a move) is repeated several times, in the given order:

1. Choose a line $ l $ such that it passes through at least two elements in $ S $ and passes through Kanno's current position. If there are multiple such lines, one is chosen equiprobably.
2. Move to one of the points that belong to $ S $ and lie on $ l $ . The destination is chosen equiprobably among all possible ones, including Kanno's current position (if it does belong to $ S $ ).

There are $ q $ queries each consisting of two integers $ (t_i, m_i) $ . For each query, you're to help Kanno maximize the probability of the stopping position being the $ t_i $ -th element in $ S $ after $ m_i $ moves with a proper selection of $ P $ , and output this maximum probability. Note that according to rule 1, $ P $ should belong to at least one line that passes through at least two points from $ S $ .

## 说明/提示

The points in $ S $ and possible candidates for line $ l $ are depicted in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF989E/9dc6a2e53d51df32abc295e2febe0114d0e3d73f.png)For the first query, when $ P = (-1, -3) $ , $ l $ is uniquely determined to be $ 3x = y $ , and thus Kanno will move to $ (0, 0) $ with a probability of $ \frac 1 2 $ .

For the third query, when $ P = (2, 2) $ , $ l $ is chosen equiprobably between $ x + y = 4 $ and $ x = y $ . Kanno will then move to the other four points with a probability of $ \frac 1 2 \cdot \frac 1 3 = \frac 1 6 $ each, or stay at $ (2, 2) $ with a probability of $ \frac 1 3 $ .

## 样例 #1

### 输入

```
5
0 0
1 3
2 2
3 1
4 4
10
1 1
2 1
3 1
4 1
5 1
3 2
3 3
3 4
3 5
3 6
```

### 输出

```
0.50000000000000000000
0.50000000000000000000
0.33333333333333331483
0.50000000000000000000
0.50000000000000000000
0.18518518518518517491
0.15226337448559670862
0.14494741655235482414
0.14332164812274550414
0.14296036624949901017
```

# AI分析结果



# 算法分类  
**矩阵快速幂优化动态规划**  

---

# 题解思路与核心分析  

## 核心思路  
1. **状态建模**：将每个点视为状态，定义转移概率矩阵，表示从某点移动到另一点的概率。  
2. **矩阵快速幂**：用矩阵乘法表示多次移动的复合概率，快速幂优化计算。  
3. **直线枚举优化**：初始点选择必须位于某条直线上，预处理所有直线并计算各直线的平均概率。  

## 解决难点  
- **几何共线判断**：快速判断点是否共线（向量叉积法）。  
- **概率矩阵构造**：统计每条直线上点的数量，计算转移概率。  
- **矩阵优化技巧**：用二进制分解预处理转移矩阵的 2^k 次幂，将每次查询复杂度降为 O(n² logm)。  

---

# 题解评分（≥4星）  
### 1. asuldb（★★★★☆）  
- **亮点**：  
  - 简洁的反向概率建模（终点倒推）。  
  - 高效处理初始点选择（枚举直线而非交点）。  
  - 二进制优化矩阵乘法，复杂度最优。  

---

# 最优思路与技巧  
1. **矩阵快速幂优化**：将动态规划状态转移转化为矩阵乘法，用快速幂处理多次转移。  
2. **概率反向计算**：以终点为初始状态，反向计算各点概率，避免重复计算。  
3. **直线平均概率**：初始点选择只需枚举所有直线，计算直线上点的平均概率最大值。  

---

# 相似题目推荐  
1. **洛谷 P1939**（矩阵快速幂优化递推）  
2. **洛谷 P3758**（状态转移矩阵快速幂）  
3. **洛谷 P2233**（公交线路概率问题）  

---

# 可视化算法演示设计  
### 核心流程  
1. **点与直线绘制**：在 Canvas 中绘制所有点，用不同颜色标记当前处理的直线。  
2. **概率转移动画**：高亮当前转移的点和直线，动态显示概率数值变化。  
3. **矩阵快速幂步进**：展示二进制分解的矩阵幂次组合过程，单步执行观察状态更新。  

### 复古像素风格设计  
- **颜色方案**：使用 8-bit 调色板（红、蓝、绿）标记点、直线、当前操作。  
- **音效触发**：  
  - 移动时播放“哔”声（Web Audio API）。  
  - 找到最优直线时播放胜利音效。  
- **自动演示模式**：AI 自动选择最优直线并展示概率计算过程，按空格键暂停/继续。  

---

# 代码核心逻辑  
### 关键代码（asuldb 题解）  
```cpp  
// 预处理每条直线的转移概率  
for (int i=1; i<=n; ++i) {  
    for (int j=1; j<=n; ++j) {  
        if (i == j) continue;  
        if (vis[j]) continue;  
        vector<int> line;  
        for (int k=1; k<=n; ++k) {  
            if ((p[k]-p[i])*(p[j]-p[i]) == 0) {  
                line.push_back(k);  
                vis[k] = 1;  
            }  
        }  
        double p_val = 1.0 / line.size();  
        for (auto u : line) {  
            for (auto v : line) {  
                pw[0].a[u][v] += p_val;  
            }  
        }  
    }  
}  
// 矩阵快速幂预处理  
for (int i=1; i<=13; ++i) {  
    pw[i] = pw[i-1] * pw[i-1];  
}  
// 查询处理  
void calc(int t, int m) {  
    Vector ans;  
    ans.d[t] = 1.0;  
    for (int i=13; i>=0; --i) {  
        if (m & (1<<i)) {  
            ans = ans * pw[i];  
        }  
    }  
}  
```  

---

# 总结  
本题通过矩阵快速幂高效处理多次状态转移，结合几何共线判断优化初始点选择，是动态规划与线性代数结合的典型应用。可视化设计强调矩阵乘法步进与直线选择策略，复古像素风格增强交互趣味性。

---
处理用时：58.49秒