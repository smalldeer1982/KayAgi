# 题目信息

# Kostya the Sculptor

## 题目描述

Kostya is a genial sculptor, he has an idea: to carve a marble sculpture in the shape of a sphere. Kostya has a friend Zahar who works at a career. Zahar knows about Kostya's idea and wants to present him a rectangular parallelepiped of marble from which he can carve the sphere.

Zahar has $ n $ stones which are rectangular parallelepipeds. The edges sizes of the $ i $ -th of them are $ a_{i} $ , $ b_{i} $ and $ c_{i} $ . He can take no more than two stones and present them to Kostya.

If Zahar takes two stones, he should glue them together on one of the faces in order to get a new piece of rectangular parallelepiped of marble. Thus, it is possible to glue a pair of stones together if and only if two faces on which they are glued together match as rectangles. In such gluing it is allowed to rotate and flip the stones in any way.

Help Zahar choose such a present so that Kostya can carve a sphere of the maximum possible volume and present it to Zahar.

## 说明/提示

In the first example we can connect the pairs of stones:

- $ 2 $ and $ 4 $ , the size of the parallelepiped: $ 3×2×5 $ , the radius of the inscribed sphere $ 1 $
- $ 2 $ and $ 5 $ , the size of the parallelepiped: $ 3×2×8 $ or $ 6×2×4 $ or $ 3×4×4 $ , the radius of the inscribed sphere $ 1 $ , or $ 1 $ , or $ 1.5 $ respectively.
- $ 2 $ and $ 6 $ , the size of the parallelepiped: $ 3×5×4 $ , the radius of the inscribed sphere $ 1.5 $
- $ 4 $ and $ 5 $ , the size of the parallelepiped: $ 3×2×5 $ , the radius of the inscribed sphere $ 1 $
- $ 5 $ and $ 6 $ , the size of the parallelepiped: $ 3×4×5 $ , the radius of the inscribed sphere $ 1.5 $

Or take only one stone:

- $ 1 $ the size of the parallelepiped: $ 5×5×5 $ , the radius of the inscribed sphere $ 2.5 $
- $ 2 $ the size of the parallelepiped: $ 3×2×4 $ , the radius of the inscribed sphere $ 1 $
- $ 3 $ the size of the parallelepiped: $ 1×4×1 $ , the radius of the inscribed sphere $ 0.5 $
- $ 4 $ the size of the parallelepiped: $ 2×1×3 $ , the radius of the inscribed sphere $ 0.5 $
- $ 5 $ the size of the parallelepiped: $ 3×2×4 $ , the radius of the inscribed sphere $ 1 $
- $ 6 $ the size of the parallelepiped: $ 3×3×4 $ , the radius of the inscribed sphere $ 1.5 $

It is most profitable to take only the first stone.

## 样例 #1

### 输入

```
6
5 5 5
3 2 4
1 4 1
2 1 3
3 2 4
3 3 4
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
7
10 7 8
5 10 3
4 2 6
5 5 5
10 2 8
4 2 1
7 7 7
```

### 输出

```
2
1 5
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Kostya the Sculptor 深入学习指南 💡

<introduction>
今天我们来一起分析“Kostya the Sculptor”这道题。这道题的核心是找到两个（或一个）长方体，通过拼接得到内接球半径最大的新长方体。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（基于map的状态记录与快速查询）`

🗣️ **初步分析**：
解决这道题的关键在于高效枚举可能的拼接组合。直接枚举所有两两长方体组合会超时（O(n²)），因此需要借助`map`记录每个可能的面，快速查找是否存在可拼接的长方体。简单来说，`map`在这里像一个“面仓库”，存储每个面（长和宽）对应的最大高度（第三维）及其编号。当处理新的长方体时，检查仓库中是否有相同的面，若有则计算拼接后的最短边（内接球直径），更新最大值。

- **题解思路**：所有题解的核心都是：对每个长方体的三个面（排序后），用`map`记录每个面的最大高度。处理每个面时，检查`map`中是否已有相同面，计算拼接后的最短边，同时维护单个长方体的最大最短边。
- **核心难点**：如何高效处理三个面、正确计算拼接后的最短边、避免重复枚举。
- **可视化设计**：设计像素动画模拟“面仓库”的存储与匹配过程。例如，用不同颜色的像素块表示长方体，面用矩形框标记，`map`仓库动态显示已存储的面，拼接时高亮匹配的面并计算最短边。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等方面筛选出以下优质题解：
</eval_intro>

**题解一：作者CaiXY06**
* **点评**：此题解思路清晰，代码结构工整。作者通过排序确保长方体的三个边为升序（a≤b≤c），然后枚举三个面（a×b, a×c, b×c），用`map`记录每个面的最大高度（第三维）。在处理每个面时，先检查`map`中是否已有相同面，计算拼接后的最短边，再更新`map`。代码变量名（如`a`, `b`, `c`）含义明确，循环逻辑直接，边界处理严谨（如排序后统一处理面），是典型的高效实现。

**题解二：作者Yingluosanqian**
* **点评**：此题解逻辑简洁，通过轮换三个边处理三个面，确保每个面都被考虑。`map`的键为面的长和宽，值为长方体编号和高度，便于快速查询。代码中对单个长方体的处理（排序后取最小值）和拼接处理（计算最短边）均清晰，变量名（如`ans`, `ans1`, `ans2`）直观，实践价值高。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键在于处理以下三个核心难点：
</difficulty_intro>

1.  **关键点1：如何高效枚举可拼接的长方体？**
    * **分析**：直接枚举所有两两组合会超时（O(n²)），因此需要用`map`记录每个面的最大高度。每个长方体有三个面（排序后），将这些面存入`map`，后续处理时只需检查`map`中是否已有相同面，时间复杂度降为O(n log n)。
    * 💡 **学习笔记**：用哈希表（如`map`）记录关键状态（如面的长和宽）是优化枚举的常用技巧。

2.  **关键点2：如何统一处理长方体的三个面？**
    * **分析**：长方体的三个面（长宽、长高、宽高）需要统一表示（如长≤宽），否则无法正确匹配。通过排序长方体的三个边（a≤b≤c），确保每个面的长和宽是有序的（如a×b, a×c, b×c），避免重复或遗漏。
    * 💡 **学习笔记**：排序是统一数据表示的有效手段，能简化后续处理。

3.  **关键点3：如何正确计算拼接后的最短边？**
    * **分析**：拼接后的长方体的三个边为面的长（l）、面的宽（w）、两个长方体高度（h1 + h2）。最短边是这三者的最小值，即`min(l, w, h1 + h2)`。需要确保这一步计算准确，否则会影响最终结果。
    * 💡 **学习笔记**：内接球的直径等于长方体的最短边，因此计算时需特别注意取三者的最小值。

### ✨ 解题技巧总结
- **技巧A：排序统一表示**：将长方体的三个边排序（a≤b≤c），确保面的长和宽有序，避免重复处理。
- **技巧B：哈希表记录状态**：用`map`记录每个面的最大高度，快速查找可拼接的长方体，优化时间复杂度。
- **技巧C：边界条件处理**：单独考虑单个长方体的情况（取三个边的最小值），避免遗漏最优解。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，逻辑清晰且高效：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了CaiXY06和Yingluosanqian的题解思路，优化了变量命名和逻辑结构，确保清晰性和高效性。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        map<pair<int, int>, pair<int, int>> mp; // 键：面（长,宽），值：（高度,编号）
        int ans = 0, a1 = 0, a2 = 0;

        for (int i = 1; i <= n; ++i) {
            int e[3];
            scanf("%d%d%d", &e[0], &e[1], &e[2]);
            sort(e, e + 3); // 排序后e[0]≤e[1]≤e[2]

            // 单个长方体的情况：最短边是e[0]
            if (e[0] > ans) {
                ans = e[0];
                a1 = i;
                a2 = 0;
            }

            // 处理三个面：(e0,e1), (e0,e2), (e1,e2)
            for (int j = 0; j < 3; ++j) {
                int l = e[(j + 0) % 3], w = e[(j + 1) % 3];
                if (l > w) swap(l, w); // 确保长≤宽
                int h = e[(j + 2) % 3];

                auto key = make_pair(l, w);
                if (mp.count(key)) {
                    // 计算拼接后的最短边：min(l, w, h + mp[key].first)
                    int current = min({l, w, h + mp[key].first});
                    if (current > ans) {
                        ans = current;
                        a1 = mp[key].second;
                        a2 = i;
                    }
                }
                // 更新map：保留该面的最大高度
                if (!mp.count(key) || h > mp[key].first) {
                    mp[key] = {h, i};
                }
            }
        }

        if (a2 == 0) {
            printf("1\n%d\n", a1);
        } else {
            printf("2\n%d %d\n", a1, a2);
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入并排序每个长方体的三个边。然后处理每个长方体的三个面，用`map`记录每个面的最大高度。对于每个面，先检查`map`中是否已有相同面，若有则计算拼接后的最短边并更新答案，最后更新`map`。同时维护单个长方体的最大最短边，最终输出结果。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者CaiXY06**
* **亮点**：代码结构清晰，通过排序和循环处理三个面，`map`操作简洁高效。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[0],&a[1],&a[2]);
        sort(a,a+3); // 排序后a[0]≤a[1]≤a[2]
        // 处理三个面...
        // 更新map...
    }
    ```
* **代码解读**：
    > 这部分代码对每个长方体的三个边排序，确保后续处理面时的一致性。排序后，长方体的三个面为(a[0],a[1]), (a[0],a[2]), (a[1],a[2])，每个面的长和宽有序，避免重复。
* 💡 **学习笔记**：排序是统一数据表示的关键，能避免因面的顺序不同导致的匹配失败。

**题解二：作者Yingluosanqian**
* **亮点**：通过轮换三个边处理三个面，逻辑简洁，`map`更新逻辑明确。
* **核心代码片段**：
    ```cpp
    for(int mode=1;mode<=3;mode++){
        swap(e[0],e[1]); swap(e[1],e[2]); // 轮换三个边
        Key1.first=e[0]; Key1.second=e[1];
        // 检查map并更新...
    }
    ```
* **代码解读**：
    > 这段代码通过轮换三个边，依次处理每个面（e[0]×e[1]）。每次轮换后，e[0]和e[1]是当前面的长和宽，e[2]是高度。这种方式确保三个面都被处理，且无需重复排序。
* 💡 **学习笔记**：轮换是处理循环排列的简便方法，能减少代码冗余。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“面匹配”过程，我们设计一个8位像素风格的动画，模拟`map`仓库的存储与匹配。
</visualization_intro>

  * **动画演示主题**：`像素面仓库大冒险`
  * **核心演示内容**：长方体的面存入“面仓库”（map），当新长方体的面与仓库中的面匹配时，拼接并计算最短边，高亮最大结果。
  * **设计思路简述**：8位像素风格营造轻松氛围，“面仓库”用像素格子动态展示，匹配时播放“叮”音效，拼接成功时播放“胜利”音效，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕分为左右两部分：左侧是“长方体生成区”（像素方块表示长方体），右侧是“面仓库”（网格状，每个格子表示一个面）。
        - 控制面板包含“开始”“暂停”“单步”按钮和速度滑块。

    2.  **处理单个长方体**：
        - 长方体生成区出现一个像素方块（颜色随机），显示其三个边（如`3×2×4`）。
        - 方块旋转展示三个面（长宽、长高、宽高），每个面用不同颜色边框标记（如红色、绿色、蓝色）。

    3.  **存入面仓库**：
        - 每个面以小矩形形式（如`2×3`）飞入“面仓库”，若仓库中已有相同面，则比较高度，保留较高的（替换旧的或高亮提示）。

    4.  **匹配与拼接**：
        - 当处理新长方体的面时，仓库中对应位置的面闪烁（黄色），表示匹配成功。
        - 拼接后的长方体显示三个边（如`2×3×(4+5)`），计算最短边（`min(2,3,9)=2`），数值用大字体显示。

    5.  **结果高亮**：
        - 所有可能的拼接结果中，最大的那个用金色边框高亮，伴随“胜利”音效（如FC游戏的得分音）。

  * **旁白提示**：
    - “看！这个长方体的面`2×3`在仓库里找到啦，它们可以拼接！”
    - “拼接后的最短边是`2`，当前最大值更新为`2`！”

<visualization_conclusion>
通过这样的动画，我们能清晰看到`map`如何记录面，以及拼接过程的匹配逻辑，轻松理解算法核心。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是用哈希表优化枚举，这种技巧适用于需要快速查找匹配状态的问题。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 统计数组中两数之和等于目标值（用`unordered_map`记录已出现的数）。
      - 寻找重复子串（用`map`记录子串出现次数）。
      - 分组处理相似元素（如字母异位词分组，用排序后的字符串作为键）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1094** - `纪念品分组`  
        * 🗣️ **推荐理由**：需要排序后贪心匹配，锻炼对有序数据的处理能力。
    2.  **洛谷 P1102** - `A-B 数对`  
        * 🗣️ **推荐理由**：用`map`统计数对出现次数，与本题的哈希表应用类似。
    3.  **洛谷 P3811** - `乘法逆元`  
        * 🗣️ **推荐理由**：涉及数论与预处理，拓展哈希表在数学问题中的应用。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，例如：
</insights_intro>

> **参考经验 (来自作者Yingluosanqian)**：“一开始没有对长方体的边排序，导致面的长和宽顺序混乱，无法正确匹配。后来通过排序解决了问题。”
>
> **点评**：这位作者的经验提醒我们，数据的统一表示（如排序）是避免错误的关键。在处理类似需要匹配的问题时，确保键的一致性（如长≤宽）能有效减少bug。

-----

<conclusion>
本次关于“Kostya the Sculptor”的分析就到这里。通过理解`map`的状态记录技巧和长方体面的处理方法，相信大家能轻松解决类似问题。编程的关键在于多思考、多实践，下次见！💪
</conclusion>

---
处理用时：131.69秒