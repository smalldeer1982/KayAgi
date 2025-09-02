# 题目信息

# Ramesses and Corner Inversion

## 题目描述

Ramesses came to university to algorithms practice, and his professor, who is a fairly known programmer, gave him the following task.

You are given two matrices $ A $ and $ B $ of size $ n \times m $ , each of which consists of $ 0 $ and $ 1 $ only. You can apply the following operation to the matrix $ A $ arbitrary number of times: take any submatrix of the matrix $ A $ that has at least two rows and two columns, and invert the values in its corners (i.e. all corners of the submatrix that contain $ 0 $ , will be replaced by $ 1 $ , and all corners of the submatrix that contain $ 1 $ , will be replaced by $ 0 $ ). You have to answer whether you can obtain the matrix $ B $ from the matrix $ A $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/07e01026afbc60b96857b7392bf73ad937a6aa47.png)An example of the operation. The chosen submatrix is shown in blue and yellow, its corners are shown in yellow.Ramesses don't want to perform these operations by himself, so he asks you to answer this question.

A submatrix of matrix $ M $ is a matrix which consist of all elements which come from one of the rows with indices $ x_1, x_1+1, \ldots, x_2 $ of matrix $ M $ and one of the columns with indices $ y_1, y_1+1, \ldots, y_2 $ of matrix $ M $ , where $ x_1, x_2, y_1, y_2 $ are the edge rows and columns of the submatrix. In other words, a submatrix is a set of elements of source matrix which form a solid rectangle (i.e. without holes) with sides parallel to the sides of the original matrix. The corners of the submatrix are cells $ (x_1, y_1) $ , $ (x_1, y_2) $ , $ (x_2, y_1) $ , $ (x_2, y_2) $ , where the cell $ (i,j) $ denotes the cell on the intersection of the $ i $ -th row and the $ j $ -th column.

## 说明/提示

The examples are explained below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/e8b2b05f1d91acad1dd27cd7e9d641b53a14a9dc.png)Example 1.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/a67a1a76d04df99ed90143acfb49e6763fb445d5.png)Example 2.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1119C/8179b88f909d57a1d5601735cc5b6ce16cfe2cb8.png)Example 3.

## 样例 #1

### 输入

```
3 3
0 1 0
0 1 0
1 0 0
1 0 0
1 0 0
1 0 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
6 7
0 0 1 1 0 0 1
0 1 0 0 1 0 1
0 0 0 1 0 0 1
1 0 1 0 1 0 0
0 1 0 0 1 0 1
0 1 0 1 0 0 1
1 1 0 1 0 1 1
0 1 1 0 1 0 0
1 1 0 1 0 0 1
1 0 1 0 0 1 0
0 1 1 0 1 0 0
0 1 1 1 1 0 1
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
3 4
0 1 0 1
1 0 1 0
0 1 0 1
1 1 1 1
1 1 1 1
1 1 1 1
```

### 输出

```
No
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Ramesses and Corner Inversion 深入学习指南 💡

<introduction>
今天我们来一起分析“Ramesses and Corner Inversion”这道C++编程题。这道题的关键在于理解矩阵变换的性质，通过观察操作对矩阵的影响，找到判断是否可转换的核心条件。本指南将帮助大家梳理思路，掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学（矩阵变换不变量分析）`

🗣️ **初步分析**：
解决这道题的关键在于发现矩阵变换中的“不变量”——即无论进行多少次操作，某些性质始终保持不变。简单来说，每次操作选择一个至少2×2的子矩阵，反转其四个角的值（0变1，1变0）。我们可以将问题转化为：比较原矩阵A和目标矩阵B的差异，判断是否存在一系列操作消除这些差异。

- **题解思路**：所有优质题解的核心思路一致：将A和B异或得到差异矩阵C（C[i][j] = A[i][j] ^ B[i][j]），若C中每行和每列的1的个数均为偶数，则输出Yes，否则No。这是因为每次操作会反转4个角（相当于每行和每列各反转2个位置），因此每行和每列的1的个数的奇偶性不会改变。若初始差异矩阵的某行或列1的个数为奇数，则无法通过操作消除。

- **核心算法流程**：计算差异矩阵→检查每行1的个数是否为偶数→检查每列1的个数是否为偶数→输出结果。

- **可视化设计思路**：用像素动画展示差异矩阵的生成（0为白色块，1为红色块），逐行扫描时用黄色边框高亮当前行，统计该行红色块数量；若数量为奇数则闪烁警告。列检查同理。关键步骤（如异或计算、奇偶性判断）配合“叮”的音效，目标达成时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解因逻辑简洁、实现高效被选为优质参考（≥4星）：
</eval_intro>

**题解一：作者xht (赞：5)**
* **点评**：此题解逻辑清晰，代码简洁规范。通过异或生成差异矩阵后，直接逐行、逐列检查奇偶性，时间复杂度O(nm)，非常高效。变量命名直观（如a数组存储差异矩阵），边界处理严谨（从1开始索引，避免越界）。代码可直接用于竞赛，是典型的“小而美”实现。

**题解二：作者tth37 (赞：1)**
* **点评**：此题解思路与xht一致，但通过单独统计每行每列的1的个数（x数组和y数组），逻辑更直观。代码中使用`register`关键字优化循环，提升运行效率。变量名（如flag标记结果）含义明确，适合新手学习。

**题解三：作者hpbl (赞：0)**
* **点评**：此题解另辟蹊径，直接计算原矩阵和目标矩阵每行每列的异或和，若两者异或和相同则输出Yes。这一方法利用了“每行每列异或和是不变量”的性质，代码更简洁（仅需两次遍历矩阵），体现了对问题本质的深刻理解。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，关键在于发现变换的“不变量”。结合优质题解的共性，以下是核心难点及解决策略：
</difficulty_intro>

1.  **关键点1**：如何将问题转化为可计算的数学条件？
    * **分析**：直接比较A和B的差异（异或矩阵C）是关键。C中1的位置表示需要反转的位置。每次操作反转4个角，相当于每行和每列各反转2个位置，因此每行和每列的1的个数的奇偶性不会改变。若初始C的某行或列1的个数为奇数，则无法通过操作消除。
    * 💡 **学习笔记**：异或操作能快速定位差异位置，是处理01矩阵问题的常用技巧。

2.  **关键点2**：如何验证“每行每列1的个数均为偶数”？
    * **分析**：遍历差异矩阵C的每一行，统计该行1的个数是否为偶数；同理检查每一列。若所有行和列均满足条件，则输出Yes。
    * 💡 **学习笔记**：奇偶性检查可通过异或累加实现（异或1次相当于+1模2），效率更高。

3.  **关键点3**：如何理解“操作的可组合性”？
    * **分析**：即使存在多个需要反转的位置，只要每行每列的奇偶性满足条件，总能通过组合不同的子矩阵操作（如2×2子矩阵）消除所有差异。例如，从左上到右下逐格处理，遇到差异则反转当前格所在的2×2子矩阵。
    * 💡 **学习笔记**：数学不变量是判断问题是否有解的核心依据。

### ✨ 解题技巧总结
- **异或找差异**：01矩阵的差异可通过异或快速定位，简化后续分析。
- **奇偶性检查**：利用奇偶性不变量，将复杂的操作问题转化为简单的统计问题。
- **逐行逐列验证**：通过两次遍历（行→列）即可完成条件判断，时间复杂度低。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，代码简洁高效，适合直接学习使用。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了xht和tth37的思路，通过异或生成差异矩阵，逐行逐列检查奇偶性，逻辑清晰且效率高。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 505;
    int n, m;
    int a[N][N], b[N][N];

    int main() {
        cin >> n >> m;
        // 读取矩阵A
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> a[i][j];
        // 读取矩阵B并计算差异矩阵（异或）
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                cin >> b[i][j];
                a[i][j] ^= b[i][j]; // a现在存储差异矩阵C
            }
        // 检查每行1的个数是否为偶数
        for (int i = 1; i <= n; ++i) {
            int row_sum = 0;
            for (int j = 1; j <= m; ++j)
                row_sum += a[i][j];
            if (row_sum % 2 != 0) {
                cout << "No" << endl;
                return 0;
            }
        }
        // 检查每列1的个数是否为偶数
        for (int j = 1; j <= m; ++j) {
            int col_sum = 0;
            for (int i = 1; i <= n; ++i)
                col_sum += a[i][j];
            if (col_sum % 2 != 0) {
                cout << "No" << endl;
                return 0;
            }
        }
        cout << "Yes" << endl;
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取矩阵A和B，通过异或生成差异矩阵C（存储在a数组中）。然后逐行统计C中1的个数，若某行个数为奇数则输出No；同理检查每列。若所有行和列均满足条件，输出Yes。

---
<code_intro_selected>
以下是优质题解的核心片段赏析，展示不同实现的亮点：
</code_intro_selected>

**题解一：作者xht**
* **亮点**：代码极简，直接利用异或和奇偶性判断，无冗余操作。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; i++) {
        int o = 0;
        for (int j = 1; j <= m; j++)
            o ^= a[i][j];
        if (o) { puts("No"); return 0; }
    }
    ```
* **代码解读**：这段代码统计每行的异或和（相当于1的个数模2）。若异或和为1，说明该行1的个数为奇数，无法通过操作消除，直接输出No。异或操作比累加取模更高效，体现了位运算的巧妙应用。
* 💡 **学习笔记**：异或和可快速判断奇偶性，是处理01矩阵奇偶问题的常用技巧。

**题解二：作者hpbl**
* **亮点**：直接比较原矩阵和目标矩阵的行、列异或和，无需显式生成差异矩阵。
* **核心代码片段**：
    ```cpp
    for(int k=0,t;k<2;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=m;j++) {
                scanf("%d",&t);
                x[k][0][i]^=t; // 第k个矩阵第i行的异或和
                x[k][1][j]^=t; // 第k个矩阵第j列的异或和
            }
        }
    }
    ```
* **代码解读**：通过两次遍历（k=0和k=1分别处理A和B），计算每个矩阵的行、列异或和。若A和B的行、列异或和完全相同，则说明差异矩阵的每行每列1的个数均为偶数（因为异或和相同意味着差异矩阵的异或和为0）。这一方法避免了显式存储差异矩阵，空间复杂度更低。
* 💡 **学习笔记**：数学不变量的直接应用可简化代码实现。

**题解三：作者tth37**
* **亮点**：通过单独数组统计每行每列的1的个数，逻辑直观。
* **核心代码片段**：
    ```cpp
    for(register int i=1;i<=M;++i) {
        for(register int j=1;j<=N;++j) {
            c[i][j]=a[i][j]^b[i][j];
            x[i]+=c[i][j]; // 统计第i行1的个数
            y[j]+=c[i][j]; // 统计第j列1的个数
        }
    }
    ```
* **代码解读**：这段代码显式生成差异矩阵c，并分别用x数组和y数组统计每行、每列的1的个数。后续只需检查x和y数组中的值是否均为偶数即可。这种方法直观易懂，适合新手理解。
* 💡 **学习笔记**：显式统计有助于理解问题的数学本质。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“差异矩阵奇偶性检查”的过程，我们设计了一个8位像素风格的动画演示方案，让大家“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素矩阵大冒险——差异消除战`

  * **核心演示内容**：展示从输入矩阵A和B，生成差异矩阵C，到逐行、逐列检查C中1的个数是否为偶数的全过程。

  * **设计思路简述**：采用FC红白机风格的像素画面（8色调色板，如白色背景、红色块表示1、白色块表示0），通过动态高亮和音效强化关键步骤，帮助理解奇偶性检查的逻辑。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分，左侧显示矩阵A和B（像素块排列），右侧显示差异矩阵C（初始为空白）。
          * 控制面板包含“开始”、“单步”、“重置”按钮和速度滑块。
          * 播放8位风格的轻快背景音乐。

    2.  **差异矩阵生成**：
          * 点击“开始”后，矩阵A和B的对应位置同时高亮（黄色边框），计算异或结果：若A[i][j]≠B[i][j]，则C[i][j]位置出现红色块（表示1）；否则为白色块（表示0）。
          * 每生成一个C的像素块，播放“滴答”音效。

    3.  **行奇偶性检查**：
          * 从第一行开始，用绿色箭头逐列扫描C的当前行。每扫描一个红色块，计数器加1（显示在屏幕上方）。
          * 扫描完成后，若计数器为奇数（红色数字），该行整体闪烁红色并播放“警报”音效；若为偶数（绿色数字），播放“叮”音效，箭头下移到下一行。

    4.  **列奇偶性检查**：
          * 行检查通过后，用蓝色箭头逐行扫描C的当前列。逻辑与行检查类似，计数器统计列中红色块数量。
          * 若所有列检查通过，屏幕中央显示“胜利”动画（烟花像素特效）并播放上扬的胜利音效；若某列不通过，显示“失败”提示。

    5.  **交互功能**：
          * 支持“单步”模式：学习者可手动控制每一步（生成差异块、行扫描、列扫描），观察细节。
          * 速度滑块：调整扫描速度（0.5倍速到2倍速），适应不同学习节奏。

  * **旁白提示**：
      * （生成差异矩阵时）“看！A和B不同的位置变成了红色块，这些是需要消除的差异。”
      * （行扫描时）“现在检查第一行的红色块数量，如果是奇数，就无法消除哦！”
      * （胜利时）“所有行和列的红色块数量都是偶数，成功消除差异！”

<visualization_conclusion>
通过这样的像素动画，我们不仅能直观看到差异矩阵的生成和检查过程，还能在趣味互动中理解奇偶性不变量的关键作用。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是分析变换的不变量，这类思路在矩阵变换、图论等问题中广泛应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - **矩阵变换问题**：如“翻转矩阵中的子矩阵”“改变元素值的操作”，通常需找到不变量（如奇偶性、和的模等）。
      - **图论问题**：如“开关灯问题”（每次操作改变多个灯的状态），可通过分析操作对状态的影响找规律。
      - **数组操作问题**：如“翻转数组中的子数组”，需观察操作对数组性质（如逆序数、奇偶性）的影响。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1220 关路灯** - `关路灯`
          * 🗣️ **推荐理由**：涉及区间操作的最优策略，需分析操作对状态的影响，与本题的“不变量”思路类似。
    2.  **洛谷 P1896 [SCOI2005]互不侵犯** - `互不侵犯`
          * 🗣️ **推荐理由**：需通过状态压缩动态规划处理矩阵中的放置问题，锻炼对矩阵性质的分析能力。
    3.  **洛谷 P5367 [PKUWC2019]Minimax** - `Minimax`
          * 🗣️ **推荐理由**：涉及树结构的操作与统计，需分析操作对树节点值的影响，适合拓展不变量分析思维。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题时的思考过程，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自作者hpbl)**：“对于这种变换问题，关键是找变换前后的不变量。比如本题中，每次操作反转4个角，相当于每行和每列各反转2个位置，因此行和列的奇偶性不变。这启发我直接比较原矩阵和目标矩阵的行、列异或和。”

> **点评**：作者的经验点明了“找不变量”是解决此类问题的核心。在遇到类似的变换问题时，我们可以尝试分析每次操作对关键属性（如奇偶性、和的模）的影响，从而找到判断条件。

-----

<conclusion>
本次关于“Ramesses and Corner Inversion”的C++解题分析就到这里。通过理解差异矩阵的奇偶性不变量，我们掌握了判断矩阵是否可转换的关键。希望这份指南能帮助大家在类似问题中快速找到解题思路！下次再见～💪
</conclusion>

---
处理用时：136.85秒