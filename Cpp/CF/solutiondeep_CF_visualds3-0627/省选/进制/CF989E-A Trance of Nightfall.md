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
**矩阵快速幂**

---

# 题解思路与难点分析

## 核心算法流程
1. **概率转移矩阵构建**  
   - 预处理所有可能直线，计算每个点在直线上的转移概率
   - 构造 $n \times n$ 转移矩阵 $P$，其中 $P[i][j]$ 表示从点 $i$ 移动到点 $j$ 的概率

2. **矩阵快速幂优化**  
   - 预处理转移矩阵的 $2^k$ 次幂矩阵（如 $pw[0], pw[1], ..., pw[13]$）
   - 对每个查询，将步数 $m$ 分解为二进制，用向量逐个乘对应幂次的矩阵（复杂度从 $O(n^3 \log m)$ 降为 $O(n^2 \log m)$）

3. **初始点优化策略**  
   - 初始点必在某个两点确定的直线上，且不在其他直线交点上
   - 枚举所有直线，计算该直线上所有点作为初始点的平均概率，取最大值

## 解决难点
- **概率转移的高效计算**：通过矩阵快速幂将指数级计算转化为对数级
- **初始点的最优选择**：利用几何性质排除交点，只需枚举所有直线
- **代码优化**：用向量乘矩阵代替完整矩阵乘法，降低时间复杂度

---

# 题解评分（≥4星）

**题解作者：asuldb（⭐⭐⭐⭐⭐）**  
- 亮点：完整推导初始点选择策略，实现矩阵快速幂与向量优化，代码清晰且包含详细注释
- 关键代码段：
  ```cpp
  // 矩阵快速幂预处理
  for(re int i=1;i<=13;i++)pw[i]=pw[i-1]*pw[i-1];
  // 查询时二进制分解步数
  for(re int i=13;i>=0;--i)if(m>>i&1) ans=ans*pw[i];
  ```

---

# 最优思路提炼

1. **初始点选择几何优化**  
   初始点必在某个两点确定的直线上，且不在交点上，可通过枚举所有直线快速计算

2. **向量乘矩阵优化**  
   将状态表示为向量，用向量连续乘预处理的矩阵，复杂度从 $O(n^3)$ 降为 $O(n^2)$

3. **直线去重与预处理**  
   使用两点唯一标识直线，并预先存储所有直线上的点集合

---

# 同类型题推荐
1. **P1939【模板】矩阵加速（数列）**  
   矩阵快速幂优化递推式的经典模板

2. **P2233 [HNOI2002]公交车路线**  
   带环状转移的概率问题，需矩阵快速幂优化

3. **P4159 [SCOI2009] 迷路**  
   带边权的图转移，矩阵快速幂变形应用

---

# 可视化设计

## 核心算法演示
1. **像素风格动画**  
   - **坐标系绘制**：用 8-bit 像素点表示平面上的 $n$ 个点
   - **直线高亮**：当前枚举的直线显示为黄色，其他直线为灰色
   - **概率热力图**：用颜色渐变（蓝→红）表示各点概率值

2. **关键步骤音效**  
   - 矩阵乘法完成时播放 "beep" 音效
   - 找到最大概率时播放胜利音效

3. **交互控制面板**  
   ```html
   <div id="control">
     <button onclick="step()">单步执行</button>
     <input type="range" id="speed" min="1" max="5">
   </div>
   ```

## 算法流程伪代码
```javascript
function visualize() {
  drawGrid(); // 绘制坐标系
  highlightCurrentLine(line); // 高亮当前处理的直线
  updateProbabilityHeatmap(prob); // 更新概率热力图
  playSound('step'); // 播放步进音效
}
```

---

# 个人心得摘录
- **调试经验**：初始点若在交点会导致概率被平均，必须排除（asuldb）
- **代码优化**：`vector * matrix` 比 `matrix * matrix` 快10倍以上（Thosaka_Forest）

---

# 相似算法套路
- **状态转移图 → 矩阵表示**：将图论问题转化为矩阵运算
- **二进制分解加速**：预处理 $2^k$ 次幂结果，快速组合任意次数操作

---
处理用时：59.09秒