# 题目信息

# Moon Craters

## 题目描述

There are lots of theories concerning the origin of moon craters. Most scientists stick to the meteorite theory, which says that the craters were formed as a result of celestial bodies colliding with the Moon. The other version is that the craters were parts of volcanoes.

An extraterrestrial intelligence research specialist professor Okulov (the namesake of the Okulov, the author of famous textbooks on programming) put forward an alternate hypothesis. Guess what kind of a hypothesis it was –– sure, the one including extraterrestrial mind involvement. Now the professor is looking for proofs of his hypothesis.

Professor has data from the moon robot that moves linearly in one direction along the Moon surface. The moon craters are circular in form with integer-valued radii. The moon robot records only the craters whose centers lay on his path and sends to the Earth the information on the distance from the centers of the craters to the initial point of its path and on the radii of the craters.

According to the theory of professor Okulov two craters made by an extraterrestrial intelligence for the aims yet unknown either are fully enclosed one in the other or do not intersect at all. Internal or external tangency is acceptable. However the experimental data from the moon robot do not confirm this theory! Nevertheless, professor Okulov is hopeful. He perfectly understands that to create any logical theory one has to ignore some data that are wrong due to faulty measuring (or skillful disguise by the extraterrestrial intelligence that will be sooner or later found by professor Okulov!) That’s why Okulov wants to choose among the available crater descriptions the largest set that would satisfy his theory.

## 样例 #1

### 输入

```
4
1 1
2 2
4 1
5 1
```

### 输出

```
3
1 2 4
```

# AI分析结果



# Moon Craters 题解分析

## 唯一算法分类
**区间动态规划（区间DP）**

---

## 题解思路与算法要点

### 核心问题转化
将每个圆转化为数轴上的区间 $[c-r, c+r]$，问题转化为选择最大互不交叉的区间集合（允许完全包含或完全分离）。  
**关键性质**：若两区间相交但无包含关系，则无法同时选入集合。

### 题解思路对比
| 题解作者 | 核心思路 | 状态定义 | 预处理关键点 | 解决难点 |
|---------|----------|----------|--------------|----------|
| 封禁用户 | 左端点排序，分治式DP | $f(i,j)$ 表示从第 $i$ 个圆开始，右端点不超过 $j$ 的最大选择数 | 预处理每个圆的右端点映射（Rid）、下一个区间的起始位置（nxt） | 快速分割内外区间 |
| Durante | 右端点排序，自底向上DP | $w_i$ 表示第 $i$ 个圆内部能选的最大数 | 离散化 + 右端点分组（v1数组） | 确保子问题先被计算 |
| 向阳花木 | 离散化区间DP | $f_{i,j}$ 表示离散化后区间 $(i,j)$ 的最优解 | 离散化端点 + 区间分割点枚举 | 处理复杂区间关系 |
| Mihari | 记忆化搜索分割点 | $f[l][r]$ 存储离散化区间的最优解 | 离散化 + 右端点索引（g数组） | 递归分割点的选择 |
| 荣一鸣 | 区间DP+离散化 | $f[i][j]$ 表示离散区间 $i$ 到 $j$ 的最大数 | 离散化端点 + 右端点快速索引 | 分割点的优化枚举 |

### 核心算法流程（以封禁用户解法为例）
1. **预处理排序**：将圆按左端点升序、右端点降序排列，确保处理顺序最优。
2. **离散化映射**：将右端点压缩到连续整数（Rid数组）。
3. **nxt数组计算**：对每个圆，找到第一个左端点超过其右端点的圆。
4. **DP转移**：
   ```cpp
   for (i从n-1到0)
     for (j所有可能的右端点)
       dp[i][j] = max(不选i时的解, 选i时的解)
       // 选i时：内部区间解 + 外部区间解 + 1（当前圆）
   ```
5. **回溯路径**：根据dp值递归输出选中的圆。

---

## 题解评分（≥4星）
1. **封禁用户（★★★★☆）**  
   思路清晰，预处理巧妙（nxt数组加速分割），代码结构紧凑。回溯路径实现简洁，时间复杂度O(n²)优秀。

2. **Durante（★★★★☆）**  
   右端点排序确保子问题独立性，w_i的定义新颖。离散化处理得当，方案回溯逻辑清晰。

3. **向阳花木（★★★★☆）**  
   经典区间DP框架，离散化实现规范。分割点枚举直观，适合教学演示。

---

## 最优思路提炼
**关键技巧**：  
1. **排序策略**：左端点优先确保处理顺序，右端点降序避免交叉干扰。
2. **离散化压缩**：将坐标映射到连续整数，减少状态维度。
3. **预处理辅助数组**：如nxt数组快速定位分割点，Rid数组加速状态转移。
4. **分治式状态转移**：将大区间分解为互不干扰的子区间，利用包含性质避免重复计算。

**通用模式**：  
```text
sort(区间) → 离散化 → 预处理辅助结构 → DP状态转移 → 回溯方案
```

---

## 类似题目推荐
1. **P1880 [NOI1995] 石子合并**（区间DP经典）
2. **P1020 导弹拦截**（最长不升子序列，包含关系）
3. **P1090 合并果子**（贪心 + 优先队列，区间合并思想）

---

## 可视化设计要点
**动画演示方案**：  
1. **像素风格画布**：使用16色调色板，区间用不同颜色方块表示，当前操作区间高亮闪烁。
2. **核心步骤展示**：  
   - **排序阶段**：区间从左到右依次排列，右端点大的下沉。  
   - **DP转移**：显示当前处理的区间（红色边框），分割线（黄色虚线）划分内外区间。  
   - **路径回溯**：选中的区间播放绿色渐入效果，未选中的渐变透明。  
3. **音效触发**：  
   - 分割线绘制时播放“滴”声。  
   - 选中区间时播放“收集金币”音效。  
   - 错误选择时播放低沉“错误”音效。  

**交互功能**：  
- 速度滑块调节DP执行速度（0.5x~5x）。  
- 单步执行按钮观察每个状态更新。  
- 切换不同题解算法对比分割策略差异。

---

## 代码片段（封禁用户解法核心）
```cpp
// 预处理nxt数组
for(int i=0; i<n; ++i){
    nxt[i] = n;
    for(int j=0; j<n; ++j)
        if(node[i].r <= node[j].l){
            nxt[i] = j; break;
        }
}

// DP转移
for(int i=n-1; ~i; --i)
    for(int j=0; j<n; ++j){
        dp[i][j] = dp[i+1][j]; // 不选i
        if(node[i].r <= R[j])  // 选i
            getMax(dp[i][j], dp[i+1][Rid[i]] + dp[nxt[i]][j] + 1);
    }

// 回溯输出方案
void output(int i,int j){
    if(i == n) return;
    if(dp[i][j] == dp[i+1][j]) return output(i+1,j);
    printf("%d ",node[i].id+1);
    output(i+1,Rid[i]), output(nxt[i],j);
}
```

**关键注释**：  
- `nxt[i]` 表示选i后下一个可处理的区间起点。  
- `Rid[i]` 将右端点映射到离散化索引，加速状态查询。  
- 回溯时递归处理内部和外部区间，体现分治思想。

---
处理用时：82.56秒