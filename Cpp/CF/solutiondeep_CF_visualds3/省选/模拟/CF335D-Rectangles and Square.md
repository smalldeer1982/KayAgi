# 题目信息

# Rectangles and Square

## 题目描述

You are given $ n $ rectangles, labeled 1 through $ n $ . The corners of rectangles have integer coordinates and their edges are parallel to the $ Ox $ and $ Oy $ axes. The rectangles may touch each other, but they do not overlap (that is, there are no points that belong to the interior of more than one rectangle).

Your task is to determine if there's a non-empty subset of the rectangles that forms a square. That is, determine if there exists a subset of the rectangles and some square for which every point that belongs to the interior or the border of that square belongs to the interior or the border of at least one of the rectangles in the subset, and every point that belongs to the interior or the border of at least one rectangle in the subset belongs to the interior or the border of that square.

## 说明/提示

The first test case looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335D/b555a1b2f0fa9850a908273e7c5806edefd08e25.png)Note that rectangles 6, 8, and 9 form a square as well, and would be an acceptable answer.

The second test case looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335D/50fe7d9330ec3e3fa026a900ee9c84c7d3b58755.png)

## 样例 #1

### 输入

```
9
0 0 1 9
1 0 9 1
1 8 9 9
8 1 9 8
2 2 3 6
3 2 7 3
2 6 7 7
5 3 7 6
3 3 5 6
```

### 输出

```
YES 5
5 6 7 8 9
```

## 样例 #2

### 输入

```
4
0 0 1 9
1 0 9 1
1 8 9 9
8 1 9 8
```

### 输出

```
NO
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Rectangles and Square 深入学习指南 💡

<introduction>
今天我们来一起分析“Rectangles and Square”这道C++编程题。这道题的核心是判断是否存在一个非空的矩形子集能拼成正方形。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`枚举+几何处理` (编程技巧应用)

🗣️ **初步分析**：
解决这道题的关键在于高效枚举可能的正方形边界，并验证其是否满足“完全覆盖且边界对齐”的条件。简单来说，我们需要像“拼图游戏”一样，找到一组矩形，它们的组合刚好形成一个正方形——既不能多一块（因为矩形不重叠），也不能少一块（必须完全覆盖正方形区域）。

- **题解思路**：两种优质题解均采用“枚举关键顶点”的思路。Purslane的题解通过预处理多个辅助数组（如`tl`、`tr`等）和单调栈优化，高效枚举对角线；james1BadCreeper的题解则枚举正方形的右上角（矩形的右上角）和左下角（矩形的左下角），利用二维前缀和快速验证覆盖情况和边界条件。
- **核心难点**：如何避免暴力枚举所有可能的子集（复杂度极高），转而通过几何特性缩小枚举范围；如何高效验证“完全覆盖”和“边界对齐”两个条件。
- **可视化设计**：我们将设计一个“像素拼图”动画，用8位像素风格的网格展示矩形和正方形的位置。动画中会高亮枚举的正方形边界（如红色边框），动态显示覆盖区域的验证过程（绿色表示覆盖，红色表示未覆盖），并在关键步骤（如边界检查通过）播放“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面评估，筛选出以下2道优质题解（均≥4星）：
</eval_intro>

**题解一：Purslane的单调栈优化解法**
* **点评**：此题解通过预处理多个辅助数组（`tl`、`tr`、`tu`、`td`）记录矩形的扩展信息，结合单调栈优化枚举过程，将时间复杂度控制在O(k²)（k为坐标范围）。代码中变量命名规范（如`xl[i]`表示第i个矩形的左边界x坐标），逻辑结构清晰。亮点在于利用单调栈减少无效枚举，例如通过维护单调递减栈快速找到满足条件的左下角，避免了重复计算。实践价值高，适合学习几何问题中的预处理和优化技巧。

**题解二：james1BadCreeper的前缀和验证解法**
* **点评**：此题解思路直观——枚举正方形的右上角（矩形的右上角）和左下角（矩形的左下角），利用二维前缀和快速验证覆盖区域是否被完全填充，并通过边界数组（`b1`、`b2`等）检查正方形的四条边是否被矩形边界完全覆盖。代码结构简洁，变量命名易懂（如`s[x][y]`表示(x,y)点的覆盖次数），核心逻辑（`check`函数）清晰。亮点在于将几何条件转化为前缀和的数值判断，大大降低了验证复杂度，适合学习如何将几何问题转化为代数计算。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，我们通常会遇到以下核心难点。结合优质题解的思路，我为大家总结了应对策略：
</difficulty_intro>

1.  **关键点1：如何缩小枚举范围？**
    * **分析**：直接枚举所有可能的子集（2ⁿ种可能）显然不可行。优质题解利用几何特性缩小范围：正方形的右上角必是某个矩形的右上角，左下角必是某个矩形的左下角。这是因为正方形的边界必须由矩形的边界构成（否则无法完全覆盖）。
    * 💡 **学习笔记**：几何问题中，关键顶点（如矩形的角点）往往是枚举的突破口。

2.  **关键点2：如何高效验证“完全覆盖”？**
    * **分析**：验证正方形内的每个点都被至少一个矩形覆盖，直接遍历每个点会超时。james1BadCreeper的题解用二维前缀和数组`s[x][y]`记录每个点的覆盖次数，通过计算区域和快速判断是否所有点都被覆盖（区域和等于正方形面积）。
    * 💡 **学习笔记**：二维前缀和是处理二维区域覆盖问题的“神器”，能将O(k²)的验证复杂度降为O(1)。

3.  **关键点3：如何确保正方形的边界对齐？**
    * **分析**：正方形的四条边必须被矩形的边完全覆盖（否则边界会有空隙）。Purslane的题解通过预处理`tl`（左边界扩展长度）、`tr`（右边界扩展长度）等数组，快速判断边界是否对齐；james1BadCreeper的题解用`b1`（左边界覆盖数组）、`b3`（右边界覆盖数组）等记录边界覆盖次数，确保每条边的每个点都被矩形边覆盖。
    * 💡 **学习笔记**：预处理关键边界信息，能将复杂的边界检查转化为简单的数值比较。

### ✨ 解题技巧总结
<summary_best_practices>
- **几何特性缩小枚举范围**：利用矩形的顶点作为正方形的候选顶点，大幅减少枚举量。
- **前缀和加速验证**：二维前缀和快速计算区域覆盖情况，避免逐点检查。
- **预处理关键信息**：通过预处理数组（如边界扩展长度、边界覆盖次数），将复杂几何条件转化为数值判断。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们选择james1BadCreeper的题解作为通用核心实现，因其思路直观、代码简洁，适合初学者理解。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了james1BadCreeper的题解思路，通过枚举正方形的右上角（矩形的右上角）和左下角（矩形的左下角），利用二维前缀和和边界数组验证条件。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    const int MAX = 3005;
    int n, s[MAX][MAX]; // 二维前缀和数组，记录覆盖次数
    int xl[100005], yl[100005], xr[100005], yr[100005]; // 各矩形的坐标
    int b1[MAX][MAX], b2[MAX][MAX], b3[MAX][MAX], b4[MAX][MAX]; // 边界覆盖数组

    vector<int> a[6005]; // 按对角线偏移量分类存储矩形索引

    inline bool check(int xl0, int yl0, int xr0, int yr0) {
        // 检查正方形区域是否被完全覆盖且边界对齐
        if (xl0 > xr0 || yl0 > yr0) return false;
        int area = (xr0 - xl0 + 1) * (yr0 - yl0 + 1);
        int sum = s[xr0][yr0] - s[xl0-1][yr0] - s[xr0][yl0-1] + s[xl0-1][yl0-1];
        if (sum != area) return false; // 覆盖区域不完整

        // 检查左、右、下、上边界是否被矩形边完全覆盖
        if (b1[xr0][yl0] - b1[xl0-1][yl0] != xr0 - xl0 + 1) return false;
        if (b2[xl0][yr0] - b2[xl0][yl0-1] != yr0 - yl0 + 1) return false;
        if (b3[xr0][yr0] - b3[xl0-1][yr0] != xr0 - xl0 + 1) return false;
        if (b4[xr0][yr0] - b4[xr0][yl0-1] != yr0 - yl0 + 1) return false;

        // 收集符合条件的矩形并输出
        vector<int> ans;
        for (int i = 1; i <= n; ++i) {
            if (xl[i] >= xl0 && xr[i] <= xr0 && yl[i] >= yl0 && yr[i] <= yr0)
                ans.push_back(i);
        }
        cout << "YES " << ans.size() << "\n";
        for (int id : ans) cout << id << " ";
        return true;
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> xl[i] >> yl[i] >> xr[i] >> yr[i];
            xl[i]++; yl[i]++; // 坐标偏移，避免边界处理
            // 按对角线偏移量分类存储（左下角到右上角的对角线）
            int offset = xl[i] - yl[i] + 3000;
            a[offset].push_back(i);
            // 填充覆盖数组和边界数组
            for (int x = xl[i]; x <= xr[i]; ++x) {
                for (int y = yl[i]; y <= yr[i]; ++y) {
                    s[x][y]++;
                }
                b1[x][yl[i]]++; // 左边界覆盖次数+1
                b3[x][yr[i]]++; // 右边界覆盖次数+1
            }
            for (int y = yl[i]; y <= yr[i]; ++y) {
                b2[xl[i]][y]++; // 下边界覆盖次数+1
                b4[xr[i]][y]++; // 上边界覆盖次数+1
            }
        }
        // 计算前缀和
        for (int i = 1; i < MAX; ++i) {
            for (int j = 1; j < MAX; ++j) {
                s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
                b1[i][j] += b1[i-1][j];
                b2[i][j] += b2[i][j-1];
                b3[i][j] += b3[i-1][j];
                b4[i][j] += b4[i][j-1];
            }
        }
        // 枚举右上角（矩形的右上角），查找同对角线的左下角
        for (int i = 1; i <= n; ++i) {
            int offset = xr[i] - yr[i] + 3000;
            for (int x : a[offset]) {
                if (check(xl[x], yl[x], xr[i], yr[i])) {
                    return 0;
                }
            }
        }
        cout << "NO\n";
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取所有矩形的坐标，并按对角线偏移量分类存储。通过填充覆盖数组（`s`）和边界数组（`b1`-`b4`），预处理每个点的覆盖次数和边界覆盖次数。然后计算前缀和，将二维区域查询优化为O(1)。最后枚举每个矩形的右上角，查找同对角线的左下角，调用`check`函数验证是否形成正方形。

---
<code_intro_selected>
接下来，我们剖析两个优质题解的核心代码片段：
</code_intro_selected>

**题解一：Purslane的单调栈优化（核心片段）**
* **亮点**：利用单调栈优化枚举过程，减少无效计算。
* **核心代码片段**：
    ```cpp
    void solve(int x0, int y0, int x1, int y1) {
        stack<int> st;
        int covx = x0, covy = y0;
        int len = x1 - x0 + 1;
        ffor(i, 1, len) {
            while (cov[x0 + i - 1][y0 + i - 1] - cov[covx][y0 + i - 1] - cov[x0 + i - 1][covy] + cov[covx][covy]) 
                covx++, covy++;
            int l = max({covx - x0 + 1, i - tl[x0 + i - 1][y0 + i - 1], i - td[x0 + i - 1][y0 + i - 1]});
            while (!st.empty() && a[st.top()] < i) st.pop();
            if (!st.empty() && st.top() >= l) 
                output(x0 + st.top() - 1, y0 + st.top() - 1, x0 + i - 1, y0 + i - 1);
            a[i] = min(i + tr[x0 + i - 1][y0 + i - 1], i + tu[x0 + i - 1][y0 + i - 1]);
            while (!st.empty() && a[i] >= a[st.top()]) st.pop();
            st.push(i);
        }
    }
    ```
* **代码解读**：
    `solve`函数枚举正方形的对角线（从(x0,y0)到(x1,y1)），通过`cov`数组记录覆盖区域，`tl`、`tr`等数组记录边界扩展长度。`covx`和`covy`追踪当前未完全覆盖的区域，`l`计算有效左下角的最小索引。单调栈`st`维护可能的左下角候选，确保每次查询的是满足条件的最优解。当栈顶元素≥`l`时，说明找到合法正方形，调用`output`输出。
* 💡 **学习笔记**：单调栈适合处理“在枚举过程中维护候选集合”的问题，能有效减少重复计算。

**题解二：james1BadCreeper的前缀和验证（核心片段）**
* **亮点**：将几何条件转化为前缀和数值判断，验证高效。
* **核心代码片段**：
    ```cpp
    inline bool check(int xl0, int yl0, int xr0, int yr0) {
        if (xl0 > xr0 || yl0 > yr0) return false;
        int area = (xr0 - xl0 + 1) * (yr0 - yl0 + 1);
        int sum = s[xr0][yr0] - s[xl0-1][yr0] - s[xr0][yl0-1] + s[xl0-1][yl0-1];
        if (sum != area) return false;
        if (b1[xr0][yl0] - b1[xl0-1][yl0] != xr0 - xl0 + 1) return false;
        if (b2[xl0][yr0] - b2[xl0][yl0-1] != yr0 - yl0 + 1) return false;
        if (b3[xr0][yr0] - b3[xl0-1][yr0] != xr0 - xl0 + 1) return false;
        if (b4[xr0][yr0] - b4[xr0][yl0-1] != yr0 - yl0 + 1) return false;
        // 收集并输出结果...
    }
    ```
* **代码解读**：
    `check`函数是核心验证逻辑。首先计算正方形面积（`area`），然后用二维前缀和计算该区域的总覆盖次数（`sum`），若`sum`等于面积，说明所有点都被覆盖。接着通过边界数组（`b1`-`b4`）检查四条边是否被矩形的边完全覆盖（边界覆盖次数等于边长）。若所有条件满足，输出符合条件的矩形。
* 💡 **学习笔记**：将几何问题转化为数值计算（如面积、覆盖次数），能大幅降低代码复杂度。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“枚举正方形+前缀和验证”的过程，我设计了一个“像素拼图”动画方案，用8位复古风格展示算法步骤。
</visualization_intro>

  * **动画演示主题**：`像素拼图大挑战——寻找完美正方形`

  * **核心演示内容**：模拟枚举正方形的右上角和左下角，动态展示覆盖区域的验证过程，以及边界对齐的检查。

  * **设计思路简述**：采用FC红白机的8位像素风格（16色调色板，简洁的方块图形），让学习者在轻松的氛围中观察算法每一步。关键操作（如枚举顶点、覆盖验证）通过颜色高亮和音效提示，增强记忆点。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化 (8位像素风)**：
          - 屏幕左侧为20x20的像素网格（模拟坐标范围0-3000），用不同颜色区分矩形（蓝色）、空白（白色）、正方形候选区域（红色边框）。
          - 右侧为控制面板：单步/自动播放按钮、速度滑块（1-5倍速）、重置按钮。
          - 背景播放8位风格的轻快音乐（如《超级马里奥》的经典BGM）。

    2.  **输入与预处理**：
          - 输入矩形时，每个矩形以蓝色像素块“掉落”到网格中，伴随“唰”的音效。
          - 预处理阶段（计算前缀和、边界数组）用淡绿色文字在屏幕顶部滚动显示进度（如“预处理覆盖数组... 50%”）。

    3.  **枚举正方形顶点**：
          - 枚举右上角（矩形的右上角）时，该顶点用黄色像素箭头标记，并播放“滴答”音效。
          - 查找同对角线的左下角时，箭头从右上角向左下方滑动，经过的左下角顶点用橙色闪烁标记。

    4.  **覆盖验证 (关键步骤)**：
          - 选中候选正方形区域后，网格中该区域变为半透明红色，同时右侧弹出代码片段（如`s[xr][yr] - s[xl-1][yr]...`），高亮当前执行行。
          - 计算覆盖次数时，每个被覆盖的点闪烁绿色（覆盖成功），未覆盖的点闪烁红色（覆盖失败），伴随“叮”或“咚”的音效。

    5.  **边界检查**：
          - 检查左边界时，正方形的左边框用紫色高亮，每个被矩形边覆盖的点显示绿色勾，未覆盖的显示红色叉，伴随“咔嗒”音效。
          - 其他三边检查类似，颜色分别为青色（右）、粉色（下）、黄色（上）。

    6.  **成功/失败反馈**：
          - 找到合法正方形时，整个网格播放“烟花”动画（彩色像素点爆炸），伴随胜利音效（如《超级玛丽》的通关音乐），并弹出“恭喜找到完美正方形！”的文字。
          - 未找到时，屏幕中央显示“NO”字样，伴随短促的“呜呜”音效。

  * **旁白提示**：
      - （枚举顶点时）“看！我们正在检查这个矩形的右上角，寻找可能的左下角~”
      - （覆盖验证时）“现在计算这个区域的覆盖次数，如果等于面积，说明所有点都被覆盖啦！”
      - （边界检查时）“正方形的左边必须被矩形的边完全覆盖，否则会有空隙哦~”

<visualization_conclusion>
通过这样的动画，我们能直观看到算法如何一步步缩小范围、验证条件，就像在玩一个“像素拼图游戏”，既有趣又容易理解！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是“枚举关键顶点+几何验证”，这种思路在几何问题中非常通用。掌握后，我们可以尝试以下类似题目：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 枚举关键顶点的思路还可用于解决“寻找最大矩形”“判断矩形覆盖”等问题。
      - 前缀和数组是处理二维区域问题的通用工具，适用于“子矩阵和”“区域覆盖统计”等场景。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1379** - `八数码问题`
          * 🗣️ **推荐理由**：需要枚举所有可能的状态，练习状态枚举和剪枝技巧。
    2.  **洛谷 P1074** - `靶形数独`
          * 🗣️ **推荐理由**：结合枚举和剪枝，与本题的“缩小枚举范围”思路类似。
    3.  **洛谷 P1169** - `棋盘制作`
          * 🗣️ **推荐理由**：需要枚举矩形的边界，并用单调栈优化，与本题的预处理+优化思路相似。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分。
</insights_intro>

-----

<conclusion>
本次关于“Rectangles and Square”的C++解题分析就到这里。希望这份指南能帮助你理解如何通过枚举和几何验证解决此类问题。记住，多动手实践、多思考几何特性，你会越来越熟练！下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：169.15秒