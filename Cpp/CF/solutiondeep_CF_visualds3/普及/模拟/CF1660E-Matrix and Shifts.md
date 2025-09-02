# 题目信息

# Matrix and Shifts

## 题目描述

You are given a binary matrix $ A $ of size $ n \times n $ . Rows are numbered from top to bottom from $ 1 $ to $ n $ , columns are numbered from left to right from $ 1 $ to $ n $ . The element located at the intersection of row $ i $ and column $ j $ is called $ A_{ij} $ . Consider a set of $ 4 $ operations:

1. Cyclically shift all rows up. The row with index $ i $ will be written in place of the row $ i-1 $ ( $ 2 \le i \le n $ ), the row with index $ 1 $ will be written in place of the row $ n $ .
2. Cyclically shift all rows down. The row with index $ i $ will be written in place of the row $ i+1 $ ( $ 1 \le i \le n - 1 $ ), the row with index $ n $ will be written in place of the row $ 1 $ .
3. Cyclically shift all columns to the left. The column with index $ j $ will be written in place of the column $ j-1 $ ( $ 2 \le j \le n $ ), the column with index $ 1 $ will be written in place of the column $ n $ .
4. Cyclically shift all columns to the right. The column with index $ j $ will be written in place of the column $ j+1 $ ( $ 1 \le j \le n - 1 $ ), the column with index $ n $ will be written in place of the column $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1660E/12668e041dd8d5dbd1e7d6bac1040ded6cc9fc28.png)The $ 3 \times 3 $ matrix is shown on the left before the $ 3 $ -rd operation is applied to it, on the right — after.You can perform an arbitrary (possibly zero) number of operations on the matrix; the operations can be performed in any order.

After that, you can perform an arbitrary (possibly zero) number of new xor-operations:

- Select any element $ A_{ij} $ and assign it with new value $ A_{ij} \oplus 1 $ . In other words, the value of $ (A_{ij} + 1) \bmod 2 $ will have to be written into element $ A_{ij} $ .

Each application of this xor-operation costs one burl. Note that the $ 4 $ shift operations — are free. These $ 4 $ operations can only be performed before xor-operations are performed.

Output the minimum number of burles you would have to pay to make the $ A $ matrix unitary. A unitary matrix is a matrix with ones on the main diagonal and the rest of its elements are zeros (that is, $ A_{ij} = 1 $ if $ i = j $ and $ A_{ij} = 0 $ otherwise).

## 说明/提示

In the first test case, you can do the following: first, shift all the rows down cyclically, then the main diagonal of the matrix will contain only "1". Then it will be necessary to apply xor-operation to the only "1" that is not on the main diagonal.

In the second test case, you can make a unitary matrix by applying the operation $ 2 $ — cyclic shift of rows upward twice to the matrix.

## 样例 #1

### 输入

```
4

3
010
011
100

5
00010
00001
10000
01000
00100

2
10
10

4
1111
1011
1111
1111```

### 输出

```
1
0
2
11```

# AI分析结果



---
# 💡 Kay的C++算法解析：Matrix and Shifts 深入学习指南 💡

<introduction>
今天我们来一起分析“Matrix and Shifts”这道C++编程题。这道题需要我们通过矩阵移位和异或操作，将给定的01矩阵变为单位矩阵，并找到最小异或代价。本指南将帮助大家梳理核心思路，理解关键算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举+预处理优化

🗣️ **初步分析**：
> 解决这道题的关键在于“枚举所有可能的移位情况，快速计算每种情况下的异或代价”。简单来说，枚举就像“尝试所有可能的移位方式”，而预处理优化则是“用技巧快速算出每种移位后的代价”，避免重复计算。  
> 在本题中，我们需要通过行/列循环移位（上下左右）调整矩阵，使得调整后的矩阵与单位矩阵的差异最小。差异越小，需要的异或操作越少。核心难点在于：如何高效枚举所有可能的移位情况？如何快速计算每种移位后的对角线1的数量？  
> 优质题解给出的解决方案是：将原矩阵复制成2n×2n的大矩阵（相当于把原矩阵在水平和垂直方向各复制一次），这样每个n×n的子矩阵对应一种移位情况。然后通过前缀和预处理，快速查询子矩阵主对角线上的1的数量，从而计算出每种移位的异或代价，取最小值。  
> 可视化设计上，我们可以用8位像素风格展示矩阵复制、子矩阵选取和前缀和计算过程，用不同颜色标记对角线元素，配合“移位”音效（如“唰”的滑动声）和“计数”音效（如“叮”的提示音），让算法执行流程更直观。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：来源：XL4453（赞：6）**
* **点评**：这份题解思路非常清晰，巧妙地将矩阵复制为2n×2n，利用前缀和快速计算对角线1的数量。代码规范（如变量名`sum`、`cnt`含义明确），算法复杂度为O(n²)，高效且适合竞赛场景。特别是前缀和的设计，避免了重复计算，是本题的核心优化点。实践价值极高，代码可直接用于解决同类问题。

**题解二：来源：jijidawang（赞：3）**
* **点评**：此题解用通俗语言解释了题意和关键思路（如矩阵复制的作用），并推导了代价公式，对理解问题本质很有帮助。虽然未提供完整代码，但对移位操作的等价性分析（每个子矩阵对应一种移位）是解题的关键启发点，适合作为思路补充。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何表示所有可能的移位情况？
    * **分析**：行和列的循环移位共有n×n种可能（n种行移位，n种列移位）。直接枚举每种移位后重新计算对角线1的数量会非常耗时（O(n³)）。优质题解通过将原矩阵复制为2n×2n的大矩阵，使得每个n×n的子矩阵恰好对应一种移位情况（子矩阵左上角在(0~n, 0~n)范围内），从而将枚举复杂度降为O(n²)。
    * 💡 **学习笔记**：矩阵复制是处理循环移位的常用技巧，相当于将“循环”展开为“线性”，方便枚举。

2.  **关键点2**：如何快速计算移位后对角线的1的数量？
    * **分析**：直接遍历每个子矩阵的对角线（n个元素）计算1的数量需要O(n)时间，总复杂度为O(n³)。题解中使用前缀和数组`sum[i][j]`，表示从(0,0)到(i,j)的主对角线方向（i-j固定）的1的累计数量。通过前缀和的差分操作（`sum[i+n-1][j+n-1] - sum[i-1][j-1]`），可以在O(1)时间内得到子矩阵对角线的1的数量。
    * 💡 **学习笔记**：前缀和是处理“区域求和”问题的高效工具，合理设计前缀和的方向（如本题的主对角线方向）能大幅优化计算。

3.  **关键点3**：如何推导最小异或代价的公式？
    * **分析**：单位矩阵要求主对角线全1（共n个1），其余全0。假设移位后的矩阵主对角线有`cnt`个1，总共有`sum`个1（全局不变，因为移位不改变元素数量），则：
      - 主对角线需要将`n - cnt`个0变为1（代价`n - cnt`）。
      - 非对角线需要将`sum - cnt`个1变为0（代价`sum - cnt`）。
      总代价为`(n - cnt) + (sum - cnt) = sum + n - 2*cnt`。
    * 💡 **学习笔记**：数学推导是将问题转化为可计算式的关键，需明确各变量的含义（如`cnt`是移位后的对角线1的数量）。

### ✨ 解题技巧总结
<summary_best_practices>
- **循环移位的展开技巧**：将原矩阵复制为2n×2n，用子矩阵枚举所有移位情况。
- **前缀和的方向设计**：根据问题需求（如主对角线求和），设计前缀和数组的方向。
- **数学公式推导**：将问题转化为变量间的关系式（如`sum + n - 2*cnt`），简化计算。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了XL4453题解的思路，通过矩阵复制和前缀和优化，高效计算最小异或代价。
* **完整核心代码**：
    ```cpp
    #include <cstdio>
    #include <algorithm>
    using namespace std;

    const int MAX_N = 2005; // 2n最大为2000（原题n≤1000）
    int T, n;
    int a[2 * MAX_N][2 * MAX_N]; // 复制后的2n×2n矩阵
    int sum[2 * MAX_N][2 * MAX_N]; // 主对角线方向前缀和
    int total_ones; // 原矩阵中1的总数

    // 辅助函数：处理边界，防止越界
    int get_sum(int x, int y) {
        if (x < 0 || y < 0) return 0;
        if (x >= 2 * n || y >= 2 * n) return 0;
        return sum[x][y];
    }

    int main() {
        scanf("%d", &T);
        while (T--) {
            scanf("%d", &n);
            total_ones = 0;

            // 读取原矩阵并统计总1的数量
            for (int i = 0; i < n; ++i) {
                char row[1005];
                scanf("%s", row);
                for (int j = 0; j < n; ++j) {
                    a[i][j] = row[j] - '0';
                    total_ones += a[i][j];
                }
            }

            // 复制矩阵为2n×2n
            for (int i = 0; i < 2 * n; ++i) {
                for (int j = 0; j < 2 * n; ++j) {
                    a[i][j] = a[i % n][j % n];
                }
            }

            // 计算主对角线方向前缀和
            for (int i = 0; i < 2 * n; ++i) {
                for (int j = 0; j < 2 * n; ++j) {
                    sum[i][j] = get_sum(i - 1, j - 1) + a[i][j];
                }
            }

            // 枚举所有可能的子矩阵左上角(i,j)，计算最小代价
            int min_cost = 2e9;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    // 子矩阵右下角为(i+n-1, j+n-1)
                    int diagonal_ones = get_sum(i + n - 1, j + n - 1) - get_sum(i - 1, j - 1);
                    int cost = total_ones + n - 2 * diagonal_ones;
                    if (cost < min_cost) {
                        min_cost = cost;
                    }
                }
            }

            printf("%d\n", min_cost);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入并统计原矩阵中1的总数（`total_ones`）。然后将原矩阵复制为2n×2n的大矩阵（`a[i][j] = a[i%n][j%n]`），这样每个n×n的子矩阵对应一种移位情况。接着计算主对角线方向的前缀和（`sum[i][j]`），用于快速查询子矩阵对角线的1的数量。最后枚举所有可能的子矩阵左上角位置，计算每种情况下的异或代价，取最小值输出。

---
<code_intro_selected>
接下来，我们将剖析XL4453题解的核心代码片段，并点出其亮点和关键思路。
</code_intro_selected>

**题解一：来源：XL4453**
* **亮点**：通过矩阵复制和前缀和优化，将时间复杂度从O(n³)降至O(n²)，代码简洁高效。
* **核心代码片段**：
    ```cpp
    // 计算主对角线方向前缀和
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            sum[i][j] = get_sum(i - 1, j - 1) + a[i][j];
        }
    }

    // 枚举子矩阵并计算最小代价
    int min_cost = 2e9;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int diagonal_ones = get_sum(i + n - 1, j + n - 1) - get_sum(i - 1, j - 1);
            int cost = total_ones + n - 2 * diagonal_ones;
            min_cost = min(min_cost, cost);
        }
    }
    ```
* **代码解读**：
    > 这段代码的核心是前缀和的计算与应用。`sum[i][j]`表示从(0,0)到(i,j)的主对角线方向（i-j相同的元素）的1的累计数量。例如，当i=2、j=1时，`sum[2][1]`包含a[0][0]、a[1][1]、a[2][2]吗？不，这里的主对角线方向是“i-j固定”吗？其实，这里的`sum[i][j]`是按“i+j固定”吗？不，仔细看，`sum[i][j]`的计算是`sum[i-1][j-1] + a[i][j]`，这意味着每个位置的前缀和是其左上角（i-1,j-1）的前缀和加上当前值。因此，`sum[i][j]`实际上表示从(0,0)到(i,j)的“左上-右下”对角线上的所有元素的和（即i-j = 0的情况？不，i和j同时增加1，所以i-j的值是固定的）。例如，i=0,j=0时，sum[0][0] = a[0][0]；i=1,j=1时，sum[1][1] = sum[0][0] + a[1][1]；i=2,j=2时，sum[2][2] = sum[1][1] + a[2][2]。因此，`sum[i][j]`实际上是“主对角线”（i=j）方向的前缀和。  
    > 枚举子矩阵时，左上角为(i,j)，右下角为(i+n-1,j+n-1)，此时子矩阵的主对角线对应原大矩阵中的(i,j), (i+1,j+1), ..., (i+n-1,j+n-1)。通过`sum[i+n-1][j+n-1] - sum[i-1][j-1]`即可得到这条对角线上的1的总数（`diagonal_ones`）。  
    > 代价公式`total_ones + n - 2 * diagonal_ones`的推导：总共有`total_ones`个1，移位后对角线上有`diagonal_ones`个1。要让对角线全1，需要将`n - diagonal_ones`个0变为1；要让非对角线全0，需要将`total_ones - diagonal_ones`个1变为0。总代价为`(n - diagonal_ones) + (total_ones - diagonal_ones) = total_ones + n - 2*diagonal_ones`。
* 💡 **学习笔记**：前缀和的方向设计要与问题需求匹配（如本题的主对角线方向），这样才能快速查询目标区域的和。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“矩阵复制+前缀和优化”的过程，我设计了一个8位像素风格的动画演示方案，帮助大家“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素矩阵探险——寻找最优移位`

  * **核心演示内容**：展示原矩阵如何复制为2n×2n的大矩阵，枚举子矩阵时如何通过前缀和快速计算对角线1的数量，并最终找到最小异或代价。

  * **设计思路简述**：采用8位像素风格（如FC游戏画面），用不同颜色区分原矩阵、复制区域和子矩阵；通过“滑动”动画模拟行/列移位；用高亮和音效提示关键操作（如矩阵复制、前缀和计算、代价比较），增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧显示原n×n矩阵（像素方块，0为蓝色，1为红色），右侧显示控制面板（开始/暂停、单步、重置按钮，速度滑块）。
          * 播放8位风格的轻快背景音乐（如《超级马里奥》的经典旋律）。

    2.  **矩阵复制动画**：
          * 原矩阵右侧和下侧逐渐“生长”出复制的矩阵（像素方块逐个出现），最终形成2n×2n的大矩阵（颜色稍浅，区分原矩阵）。
          * 伴随“唰唰”的滑动音效，模拟行/列循环移位的效果。

    3.  **前缀和计算演示**：
          * 从大矩阵的(0,0)开始，逐个计算`sum[i][j]`的值（用数字显示在像素方块上方）。
          * 当前计算的`sum[i][j]`方块闪烁，并播放“滴答”音效，提示正在累加。

    4.  **枚举子矩阵与代价计算**：
          * 用绿色边框框选大矩阵中的每个n×n子矩阵（左上角从(0,0)到(n-1,n-1)移动），每移动一次播放“叮”的音效。
          * 子矩阵的对角线上的像素方块高亮（黄色），同时显示`diagonal_ones`的数值（如“当前对角线有3个1”）。
          * 计算并显示当前代价（如“代价=1+4-2*3= -1？哦，不对，应该是正确公式”），最终保留最小代价（红色高亮）。

    5.  **结果展示**：
          * 找到最小代价时，播放“胜利”音效（如《超级玛丽》的通关音乐），最小代价数字放大并闪烁。
          * 对应的子矩阵和移位方式（如“向下移2行，向右移1列”）用文字提示。

  * **旁白提示**：
      * （矩阵复制时）“看！原矩阵被复制到了右边和下边，这样每个n×n的小方块都对应一种移位方式哦～”
      * （前缀和计算时）“这里的sum[i][j]是前面所有对角线上1的总和，就像存钱罐一样，每次加一个硬币～”
      * （枚举子矩阵时）“现在我们在尝试第5种移位方式，看看这条对角线上有多少个1？”

<visualization_conclusion>
通过这样的像素动画，我们不仅能看到矩阵复制和前缀和的计算过程，还能直观理解每种移位方式对应的代价，真正“看”懂算法的核心！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考“矩阵移位+枚举优化”的适用场景和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的“矩阵复制+枚举子矩阵”技巧，可用于处理所有循环移位相关的问题（如求移位后的最大/最小特征值）。
      * 前缀和优化适用于需要快速计算“区域特征”（如和、最大值）的场景（如图像处理中的局部统计）。

  * **练习推荐 (洛谷)**：
    以下是几道洛谷上与本题思维方式相关的题目，建议大家尝试练习：

    1.  **洛谷 P1339** - `热浪`（差分约束）
          * 🗣️ **推荐理由**：这道题需要枚举可能的约束条件，并用前缀和思想处理区间问题，能巩固“枚举+预处理”的思维。
    2.  **洛谷 P2004** - `领地选择`（二维前缀和）
          * 🗣️ **推荐理由**：此题要求计算n×n子矩阵的最大和，与本题的前缀和应用类似，能强化二维前缀和的理解。
    3.  **洛谷 P1007** - `独木桥`（思维题）
          * 🗣️ **推荐理由**：此题通过“等效变换”将问题简化（类似本题的矩阵复制），能培养“转换思路”的解题技巧。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分。但根据解题过程，我们可以总结一些通用经验：
</insights_intro>

> 在处理循环移位问题时，“复制展开”是一个常用且有效的技巧。例如本题中，将原矩阵复制为2n×2n的大矩阵，使得枚举所有移位情况变得简单。此外，前缀和的方向设计要与问题需求紧密结合（如本题的主对角线方向），这样才能发挥其快速查询的优势。调试时，建议先手动计算小例子（如n=2），验证矩阵复制和前缀和的正确性，避免边界错误。

---

<conclusion>
本次关于“Matrix and Shifts”的C++解题分析就到这里。希望这份学习指南能帮助大家掌握“枚举+预处理优化”的核心技巧，以及矩阵移位问题的解决方法。记住，编程能力的提升在于多思考、多练习，下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：146.20秒