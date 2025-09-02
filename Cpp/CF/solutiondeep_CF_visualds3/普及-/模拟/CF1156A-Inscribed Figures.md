# 题目信息

# Inscribed Figures

## 题目描述

The math faculty of Berland State University has suffered the sudden drop in the math skills of enrolling students. This year the highest grade on the entrance math test was 8. Out of 100! Thus, the decision was made to make the test easier.

Future students will be asked just a single question. They are given a sequence of integer numbers $ a_1, a_2, \dots, a_n $ , each number is from $ 1 $ to $ 3 $ and $ a_i \ne a_{i + 1} $ for each valid $ i $ . The $ i $ -th number represents a type of the $ i $ -th figure:

1. circle;
2. isosceles triangle with the length of height equal to the length of base;
3. square.

The figures of the given sequence are placed somewhere on a Cartesian plane in such a way that:

- $ (i + 1) $ -th figure is inscribed into the $ i $ -th one;
- each triangle base is parallel to OX;
- the triangle is oriented in such a way that the vertex opposite to its base is at the top;
- each square sides are parallel to the axes;
- for each $ i $ from $ 2 $ to $ n $ figure $ i $ has the maximum possible length of side for triangle and square and maximum radius for circle.

Note that the construction is unique for some fixed position and size of just the first figure.

The task is to calculate the number of distinct points (not necessarily with integer coordinates) where figures touch. The trick is, however, that the number is sometimes infinite. But that won't make the task difficult for you, will it?

So can you pass the math test and enroll into Berland State University?

## 说明/提示

Here are the glorious pictures for the examples. Note that the triangle is not equilateral but just isosceles with the length of height equal to the length of base. Thus it fits into a square in a unique way.

The distinct points where figures touch are marked red.

In the second example the triangle and the square touch each other for the whole segment, it contains infinite number of points.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1156A/ecd8055b09d857a1401e35aa45bd638bb2a049f0.png)

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
Finite
7
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
Infinite
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Inscribed Figures 深入学习指南 💡

<introduction>
今天我们来一起分析“Inscribed Figures”这道C++编程题。这道题需要我们通过分析不同图形的嵌套规则，计算它们之间的交点数量。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟与分类讨论 (属于「编程技巧应用」)

🗣️ **初步分析**：
> 解决这道题的关键在于模拟图形嵌套的过程，并根据每对相邻图形的类型分类讨论交点数量。简单来说，“模拟”就像按步骤“复制”题目描述的过程——我们需要逐个检查相邻的两个图形，根据它们的类型（圆、三角形、正方形）确定交点数，同时处理特殊情况（如重复计算的交点）。  
> 题目中，每个图形必须尽可能大，因此相邻图形的交点数由它们的类型唯一确定（除一种特殊情况外）。核心难点在于：  
> 1. 准确记忆每对图形组合的交点数（有限或无限）；  
> 2. 识别并处理“正方形→圆→三角形”（3-1-2）序列中重复计算的交点；  
> 3. 一旦出现无限交点（如三角形→正方形或正方形→三角形），立即终止计算。  
> 可视化设计时，我们可以用像素风格的图形（圆形用○、三角形用▲、正方形用□）动态展示嵌套过程，每对图形的交点用红色小点标记，特殊情况（3-1-2）时用黄色闪烁提示重复点。动画支持单步播放，每步显示当前图形对的类型和交点数变化。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选出以下优质题解（≥4星），它们对分类讨论的逻辑和特殊情况的处理尤为出色。
</eval_intro>

**题解一：作者Doubeecat (赞：3)**  
* **点评**：此题解详细列举了所有图形组合的交点数，并通过图示辅助理解。代码结构清晰，变量命名直观（如`pre[i]`表示第i个图形类型），边界处理严谨（如输入读取函数`read()`避免了输入错误）。亮点在于作者分享了调试经历——最初因未考虑特殊情况（3-1-2）导致WA，后续通过画图发现重复点并添加特判，这对学习者有重要参考价值。

**题解二：作者PeaceSunset (赞：1)**  
* **点评**：此题解用简洁的代码实现了核心逻辑，通过`if`分支直接处理每对图形的交点数，并在注释中明确标注了每种情况的含义。代码可读性强（如`a[i-1]==1`表示外层是圆），特判逻辑（`a[i-2]==3 && a[i-1]==1 && a[i]==2`）位置合理，避免了逻辑混乱。

**题解三：作者wxwoo (赞：0)**  
* **点评**：此题解采用打表法（`res[4][4]`数组）存储每对图形的交点数，代码简洁且易于扩展。通过遍历数组累加交点数，并在后续检查特殊情况调整计数，逻辑清晰。打表法的使用是亮点，体现了“预处理”的编程技巧。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们需要重点关注以下三个核心难点，并掌握对应的解决策略：
</difficulty_intro>

1.  **关键点1：准确记忆每对图形的交点数**  
    * **分析**：不同图形组合的交点数由它们的几何特性决定。例如，圆套三角形时，三角形的三个顶点与圆相切，贡献3个交点；正方形套三角形时，三角形底边与正方形边重合，导致无限交点。优质题解通过分类讨论或打表法（如`res[4][4]`数组）清晰记录了这些规则。  
    * 💡 **学习笔记**：几何问题中，画图是理解交点数的关键！动手画几个嵌套示例，能快速总结规律。

2.  **关键点2：处理“正方形→圆→三角形”的特殊情况**  
    * **分析**：当图形序列为3（正方形）→1（圆）→2（三角形）时，圆与正方形的4个交点中，有一个会与圆与三角形的3个交点重复，导致总交点数多算1。优质题解通过检查`a[i-2]==3 && a[i-1]==1 && a[i]==2`并执行`ans--`解决此问题。  
    * 💡 **学习笔记**：特殊情况往往出现在连续三个图形的组合中，需要关注序列的局部模式。

3.  **关键点3：及时判断无限交点的情况**  
    * **分析**：当出现三角形套正方形（2→3）或正方形套三角形（3→2）时，两图形有一条边重合，交点数无限。此时需立即输出“Infinite”并终止程序。优质题解通过`if`判断在循环中提前退出，避免无效计算。  
    * 💡 **学习笔记**：无限交点的条件是“三角形和正方形相邻”，这是程序的终止条件，需优先判断。

### ✨ 解题技巧总结
<summary_best_practices>
- **分类讨论法**：将问题拆解为有限的图形组合，逐一处理，降低复杂度。  
- **打表预处理**：用数组存储每对图形的交点数（如`res[a][b]`），减少重复逻辑，提升代码可读性。  
- **特判局部序列**：关注连续三个图形的组合，检查是否存在重复计算的交点。  
- **提前终止**：一旦发现无限交点的条件（2→3或3→2），立即输出结果并退出，避免无效计算。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合了多个优质题解的通用核心实现，它清晰展示了分类讨论和特判的逻辑。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了Doubeecat和PeaceSunset的题解思路，通过分类讨论处理每对图形的交点数，并特判3-1-2序列的重复点。  
* **完整核心代码**：
    ```cpp
    #include <iostream>
    using namespace std;

    int main() {
        int n;
        cin >> n;
        int a[105];
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        int ans = 0;
        for (int i = 2; i <= n; ++i) {
            // 特判：正方形→圆→三角形，重复计算1个点
            if (i >= 3 && a[i-2] == 3 && a[i-1] == 1 && a[i] == 2) {
                ans--;
            }
            // 处理当前图形对的交点数
            if (a[i-1] == 1) { // 外层是圆
                if (a[i] == 2) ans += 3; // 圆套三角形
                else ans += 4; // 圆套正方形
            } else if (a[i-1] == 2) { // 外层是三角形
                if (a[i] == 1) ans += 3; // 三角形套圆
                else { // 三角形套正方形（无限交点）
                    cout << "Infinite" << endl;
                    return 0;
                }
            } else if (a[i-1] == 3) { // 外层是正方形
                if (a[i] == 1) ans += 4; // 正方形套圆
                else { // 正方形套三角形（无限交点）
                    cout << "Infinite" << endl;
                    return 0;
                }
            }
        }
        cout << "Finite" << endl << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取输入的图形序列，然后遍历每对相邻图形。对于每对图形，根据外层图形类型（圆、三角形、正方形）和内层图形类型，累加对应的交点数。若遇到三角形套正方形或正方形套三角形，立即输出“Infinite”并终止程序。最后，检查是否存在3-1-2序列，调整重复计算的交点数，输出最终结果。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段，学习其亮点和实现思路。
</code_intro_selected>

**题解一：作者Doubeecat**  
* **亮点**：通过注释和图示详细解释了每类图形组合的交点数，代码结构清晰，特判逻辑位置合理。  
* **核心代码片段**：
    ```cpp
    for (int i = 2; i <= n; ++i) {
        if (pre[i-2] == 3 && pre[i-1] == 1 && pre[i] == 2) {
            ans -= 1;
        }
        // 处理圆、三角形、正方形的嵌套情况...
    }
    ```
* **代码解读**：  
  这段代码在循环中先检查是否存在3-1-2序列（`pre[i-2] == 3 && pre[i-1] == 1 && pre[i] == 2`），若存在则将总交点数减1。这是因为在这种情况下，圆与正方形的一个交点会被圆与三角形的交点重复计算。通过提前调整计数，确保最终结果的准确性。  
* 💡 **学习笔记**：特判逻辑应尽可能靠近相关计算步骤，避免遗漏或错误。

**题解二：作者wxwoo**  
* **亮点**：使用打表法（`res[4][4]`数组）存储每对图形的交点数，代码简洁且易于维护。  
* **核心代码片段**：
    ```cpp
    const int res[4][4] = {0,0,0,0,
                          0,0,3,4,
                          0,3,0,inf,
                          0,4,inf,0};
    for (int i = 2; i <= n; ++i) {
        ans += res[a[i-1]][a[i]];
    }
    ```
* **代码解读**：  
  `res[a][b]`表示外层为a、内层为b时的交点数（`inf`表示无限）。通过遍历图形序列，累加每对图形的交点数。这种方法将复杂的`if`分支转化为数组查表，降低了代码复杂度，也方便后续修改或扩展（如新增图形类型时只需更新数组）。  
* 💡 **学习笔记**：当问题涉及固定的分类规则时，打表法能显著提升代码的可读性和可维护性。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解图形嵌套的交点计算过程，我设计了一个8位像素风格的动画演示方案，帮助大家“看”到每一步的交点变化。
</visualization_intro>

  * **动画演示主题**：`像素图形嵌套探险`  
  * **核心演示内容**：展示图形序列（如3-1-2）的嵌套过程，动态标记每对图形的交点，并用颜色变化提示重复点。  

  * **设计思路简述**：  
    采用FC红白机风格的像素画面（8色调色板，如红色、蓝色、黄色），每个图形用简单像素块表示（圆用○、三角形用▲、正方形用□）。通过单步播放，学习者可以观察每对图形的交点数如何累加，以及特殊情况（3-1-2）时的重复点调整。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左侧显示像素图形（从外到内排列），右侧显示“控制面板”（单步/自动按钮、速度滑块）。  
        - 顶部文本框显示当前处理的图形对（如“外层：正方形（3），内层：圆（1）”）。  

    2.  **图形嵌套动画**：  
        - 每点击“单步”按钮，内层图形（如圆）从外层图形（如正方形）中心“生长”出来，直到达到最大尺寸。  
        - 交点用红色像素点标记（如正方形套圆时，四个角的红色点出现），伴随“叮”的音效。  

    3.  **特殊情况提示**：  
        - 当处理3-1-2序列时，第三个图形（三角形）出现后，其中一个红色交点变为黄色并闪烁，同时旁白提示：“注意！这里有一个重复计算的交点，需要减1哦～”  

    4.  **无限交点处理**：  
        - 若遇到三角形套正方形（2-3），两图形的边重合为一条绿色线段，伴随“嗡”的长音效，旁白提示：“无限交点！程序终止。”  

    5.  **自动播放模式**：  
        - 点击“自动播放”，动画按设定速度自动演示整个图形序列的嵌套过程，学习者可观察总交点数的实时更新。  

  * **旁白提示**：  
    - “现在处理外层是圆（1），内层是三角形（2），它们的交点有3个！”  
    - “看，正方形（3）套三角形（2）时，它们的边重合了，所以有无限个交点～”  
    - “这里是正方形→圆→三角形的组合，有一个交点被重复计算，需要减1！”  

<visualization_conclusion>
通过这样的像素动画，我们可以直观看到每对图形的交点数如何产生，以及特殊情况的处理逻辑，大大降低了理解难度！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题的分类讨论和模拟思想后，我们可以尝试以下拓展练习，巩固相关技能。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    本题的分类讨论思想适用于许多需要“根据不同条件执行不同逻辑”的问题，例如：  
    - 统计不同类型数据的特征（如区分字母、数字、符号）；  
    - 处理游戏中的角色行为（如根据武器类型计算伤害）；  
    - 模拟现实中的规则（如交通信号灯的状态切换）。  

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1006** - `传纸条`  
          * 🗣️ **推荐理由**：需要分类讨论两条路径的重叠情况，锻炼分类与边界处理能力。  
    2.  **洛谷 P1012** - `拼数`  
          * 🗣️ **推荐理由**：通过比较字符串的字典序拼接数字，需分类讨论不同长度数字的拼接规则。  
    3.  **洛谷 P1047** - `校门外的树`  
          * 🗣️ **推荐理由**：模拟区间覆盖过程，需分类处理不同的挖坑和种树操作，巩固模拟能力。  

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
题解中作者Doubeecat分享了调试经历：最初因未考虑3-1-2序列的重复点导致WA，后来通过画图发现问题并添加特判。这对我们有重要启发：
</insights_intro>

> **参考经验 (来自 Doubeecat)**：“我一开始没考虑到3-1-2的情况，交了代码后WA了。后来画了图才发现，圆和正方形的一个交点被圆和三角形重复计算了，所以需要减1。”  

**点评**：Doubeecat的经验提醒我们，几何问题中画图是验证逻辑的重要手段。当代码结果与预期不符时，动手绘制图形（或用示例数据模拟）能快速定位问题。这对解决类似的几何或模拟问题非常实用！

---

<conclusion>
本次关于“Inscribed Figures”的C++解题分析就到这里。通过分类讨论、特判处理和可视化动画，我们掌握了图形嵌套交点数的计算方法。希望大家在练习中多画图、多测试，不断提升编程能力！下次再见～💪
</conclusion>

---

---
处理用时：114.75秒