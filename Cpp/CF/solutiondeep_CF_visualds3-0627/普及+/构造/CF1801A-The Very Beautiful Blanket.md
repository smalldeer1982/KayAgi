# 题目信息

# The Very Beautiful Blanket

## 题目描述

Kirill wants to weave the very beautiful blanket consisting of $ n \times m $ of the same size square patches of some colors. He matched some non-negative integer to each color. Thus, in our problem, the blanket can be considered a $ B $ matrix of size $ n \times m $ consisting of non-negative integers.

Kirill considers that the blanket is very beautiful, if for each submatrix $ A $ of size $ 4 \times 4 $ of the matrix $ B $ is true:

- $ A_{11} \oplus A_{12} \oplus A_{21} \oplus A_{22} = A_{33} \oplus A_{34} \oplus A_{43} \oplus A_{44}, $
- $ A_{13} \oplus A_{14} \oplus A_{23} \oplus A_{24} = A_{31} \oplus A_{32} \oplus A_{41} \oplus A_{42}, $

where $ \oplus $ means [bitwise exclusive OR](https://en.wikipedia.org/wiki/Exclusive_or)

Kirill asks you to help her weave a very beautiful blanket, and as colorful as possible!

He gives you two integers $ n $ and $ m $ .

Your task is to generate a matrix $ B $ of size $ n \times m $ , which corresponds to a very beautiful blanket and in which the number of different numbers maximized.

## 说明/提示

In the first test case, there is only 4 submatrix of size $ 4 \times 4 $ . Consider a submatrix whose upper-left corner coincides with the upper-left corner of the matrix $ B $ :

 $  \left[ {\begin{array}{cccc} 9740 & 1549 & 9744 & 1553 \\ 1550 & 1551 & 1554 & 1555 \\ 10252 & 2061 & 10256 & 2065 \\ 2062 & 2063 & 2066 & 2067 \\ \end{array} } \right]  $

 $ 9740 \oplus 1549 \oplus 1550 \oplus 1551 $ $ = $ $ 10256 \oplus 2065 \oplus 2066 \oplus 2067 $ $ = $ $ 8192 $ ;

 $ 10252 \oplus 2061 \oplus 2062 \oplus 2063 $ $ = $ $ 9744 \oplus 1553 \oplus 1554 \oplus 1555 $ $ = $ $ 8192 $ .

So, chosen submatrix fits the condition. Similarly, you can make sure that the other three submatrices also fit the condition.

## 样例 #1

### 输入

```
4
5 5
4 4
4 6
6 6```

### 输出

```
25
9740 1549 9744 1553 9748
1550 1551 1554 1555 1558
10252 2061 10256 2065 10260
2062 2063 2066 2067 2070
10764 2573 10768 2577 10772
16
3108 3109 3112 3113
3110 3111 3114 3115
3620 3621 3624 3625
3622 3623 3626 3627
24
548 549 552 553 556 557
550 551 554 555 558 559
1060 1061 1064 1065 1068 1069
1062 1063 1066 1067 1070 1071
36
25800 25801 25804 25805 25808 25809
25802 4294993099 25806 4294993103 25810 4294993107
26312 26313 26316 26317 26320 26321
26314 4294993611 26318 4294993615 26322 4294993619
26824 26825 26828 26829 26832 26833
26826 4294994123 26830 4294994127 26834 4294994131```

# AI分析结果



1. **算法分类选择**  
   构造、位运算

---

2. **题解思路、算法要点与解决难点**  
   - **核心思路**：构造每个元素为 `(i << k) ^ j`（k足够大），使得任意2x2子矩阵异或和为0，进而满足4x4条件  
   - **解决难点**：  
     - 通过位运算分离行和列的二进制位，避免不同元素重复  
     - 高位行偏移保证每行的数值区间不重叠  
     - 低位列变化保证每列数值连续且独立  
   - **关键变量**：`i << 9`（行索引高位化），`j`（列索引低位化）

---

3. **题解评分**  
   ⭐⭐⭐⭐⭐ 六楼溜刘（代码简洁，直接命中核心位运算构造）  
   ⭐⭐⭐⭐ olegekei（分块构造思路清晰，但实现稍复杂）  
   ⭐⭐⭐⭐ LJY_ljy（分治递归构造，数学证明严密但代码量大）

---

4. **最优思路或技巧提炼**  
   ```python
   # 核心构造公式（i从1开始计数）
   matrix[i][j] = (i << 9) ^ j
   ```
   - **位隔离**：行索引左移9位占据高10位，列索引占据低9位  
   - **异或归零性**：任意相邻2x2块的异或和为0  
   - **唯一性保证**：i和j的组合在高低位上互不干扰

---

5. **同类型题或类似算法套路**  
   - 棋盘覆盖问题（通过分块构造满足特殊条件）  
   - 格雷码生成（相邻元素仅一位不同，类似异或性质）

---

6. **推荐相似题目**  
   - P1118 [USACO06FEB] Backward Digit Sums（构造满足特定运算条件的序列）  
   - P2109 [NOI2005] 智慧珠游戏（位运算构造特殊图形）  
   - P2239 [NOI2016] 网格（二维矩阵构造与验证）

---

7. **个人心得摘录**  
   > "题目想多了会脑癖，要放置（doge）" —— LJY_ljy  
   > 构造题的关键在于发现位运算的对称性，而非暴力枚举

---

8. **可视化与算法演示**  
   **动画方案**：  
   - **网格绘制**：Canvas绘制n×m网格，每个格子显示计算后的数值  
   - **颜色标记**：  
     - 红色高亮当前生成的`(i, j)`坐标  
     - 绿色标记高位部分`(i<<9)`，蓝色标记低位部分`j`  
   - **异或归零演示**：点击任意4x4区域时，用不同颜色框标出左上/右下2x2区域，显示异或和计算结果  
   - **音效设计**：生成每个元素时播放8-bit音效，验证通过时播放胜利音效

---

9. **复古游戏化效果**  
   - **像素风格**：使用16色调色板，每个数字用8×8像素块显示  
   - **自动演示模式**：AI自动从左到右、从上到下填充数字，速度可调  
   - **积分系统**：每正确生成一行获得100分，连续正确生成触发连击倍率  
   - **音效**：  
     - 元素生成：短促"滴"声  
     - 验证通过：马里奥式的金币音效  
     - 错误提示：经典FC错误音效

---

**核心代码实现**  
```cpp
// 六楼溜刘的实现（核心逻辑）
for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
        printf("%d ", (i<<9) ^ j); // 行索引左移9位异或列索引
    }
    puts("");
}
```

---

**可视化关键逻辑**  
```javascript
// Canvas绘制示例（伪代码）
function drawMatrix() {
    for(let i=0; i<n; i++) {
        for(let j=0; j<m; j++) {
            let val = (i+1 << 9) ^ (j+1); // 注意题解从1开始计数
            ctx.fillStyle = getColor(i, j); // 根据高位和低位分配颜色
            draw8BitNumber(val, i*CELL_SIZE, j*CELL_SIZE);
        }
    }
}
```

---
处理用时：84.63秒