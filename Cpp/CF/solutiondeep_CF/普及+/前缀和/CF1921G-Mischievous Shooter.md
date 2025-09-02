# 题目信息

# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#```

### 输出

```
3
4
5
2```

# AI分析结果



**题目重写**：

# 调皮的射手

## 题目描述

调皮的射手Shel发现自己身处一个 $n \times m$ 的矩形场地，每个单元格可能包含目标。他有一把幸运霰弹枪，可以朝四个对角线方向（右下、左下、左上、右上）射击。每次射击会命中所选方向上曼哈顿距离不超过$k$的所有目标。两个点$(x_1,y_1)$和$(x_2,y_2)$的曼哈顿距离为$|x_1-x_2|+|y_1-y_2|$。

请帮助Shel计算他最多能击中多少个目标。

## 样例与提示

（样例输入输出与原题一致，图示略）

---

**题解分析与结论**：

各解法核心思路均围绕**矩阵旋转+差分/前缀和**展开。最优解为sunkuangzheng的差分法，其亮点在于：

1. **旋转复用**：通过矩阵旋转将四个方向统一为右下方向处理
2. **阶梯差分**：使用二维差分维护阶梯型区域，O(nm)时间复杂度
3. **空间优化**：原地处理差分数组，避免额外空间开销

**精选题解**：

1. **sunkuangzheng（★★★★★）**
   - **亮点**：将四个方向统一为右下处理，使用行差分+标记传递机制
   - **技巧**：
     - 对每个目标点维护影响区域的差分标记
     - 行间差分转移：$a_{i,j} += a_{i-1,j}, b_{i,j} += b_{i-1,j+1}$
     - 旋转矩阵四次避免重复编码
   - **核心代码**：
     ```cpp
     // 矩阵旋转逻辑（伪代码）
     for(四次旋转){
         vector<vector<int>> tmp(m, vector<int>(n));
         for(i,j) tmp[j][n-1-i] = grid[i][j]; 
         grid = tmp;
         swap(n,m);
         // 处理右下方向
     }
     // 差分处理逻辑
     for 每行:
         for 每列:
             维护行差分数组a和b
             在(i+k+1,j)处打标记
     ```

2. **Segment_Treap（★★★★☆）**
   - **亮点**：使用梯形前缀和分解攻击区域
   - **技巧**：将三角形拆分为梯形+矩形，维护线段前缀和
   - **核心思路**：
     - 预处理线段前缀和（每行、每列）
     - 构建梯形前缀和数组
     - 通过矩阵旋转复用计算逻辑

**关键技巧总结**：
1. **方向统一化**：通过矩阵旋转将四个方向问题转化为单一方向处理
2. **差分标记法**：用两个差分数组分别处理阶梯区域的起始和终止边界
3. **行间传递**：差分标记通过行间传递实现O(1)的区间更新

**拓展建议**：
- 类似矩阵覆盖问题可考虑**旋转复用**技巧
- 阶梯型区域处理可联想**杨辉三角**型前缀和
- 练习题目推荐：
  1. P3397 地毯（二维差分）
  2. P1719 最大加权矩形（二维前缀和极值）
  3. CF1864D（类似阶梯差分）

**调试心得摘录**：
- sunkuangzheng：因数组未开足够大（应开nm而非max²）导致多次WA，强调注意旋转后的尺寸变化
- Annihilation_y：在处理j > m的转移时，未优化导致复杂度退化，需直接计算有效位置

---
处理用时：58.96秒