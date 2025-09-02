# 题目信息

# New Year and the Treasure Geolocation

## 题目描述

Bob is a pirate looking for the greatest treasure the world has ever seen. The treasure is located at the point $ T $ , which coordinates to be found out.

Bob travelled around the world and collected clues of the treasure location at $ n $ obelisks. These clues were in an ancient language, and he has only decrypted them at home. Since he does not know which clue belongs to which obelisk, finding the treasure might pose a challenge. Can you help him?

As everyone knows, the world is a two-dimensional plane. The $ i $ -th obelisk is at integer coordinates $ (x_i, y_i) $ . The $ j $ -th clue consists of $ 2 $ integers $ (a_j, b_j) $ and belongs to the obelisk $ p_j $ , where $ p $ is some (unknown) permutation on $ n $ elements. It means that the treasure is located at $ T=(x_{p_j} + a_j, y_{p_j} + b_j) $ . This point $ T $ is the same for all clues.

In other words, each clue belongs to exactly one of the obelisks, and each obelisk has exactly one clue that belongs to it. A clue represents the vector from the obelisk to the treasure. The clues must be distributed among the obelisks in such a way that they all point to the same position of the treasure.

Your task is to find the coordinates of the treasure. If there are multiple solutions, you may print any of them.

Note that you don't need to find the permutation. Permutations are used only in order to explain the problem.

## 说明/提示

As $ n = 2 $ , we can consider all permutations on two elements.

If $ p = [1, 2] $ , then the obelisk $ (2, 5) $ holds the clue $ (7, -2) $ , which means that the treasure is hidden at $ (9, 3) $ . The second obelisk $ (-6, 4) $ would give the clue $ (-1,-3) $ and the treasure at $ (-7, 1) $ . However, both obelisks must give the same location, hence this is clearly not the correct permutation.

If the hidden permutation is $ [2, 1] $ , then the first clue belongs to the second obelisk and the second clue belongs to the first obelisk. Hence $ (-6, 4) + (7, -2) = (2,5) + (-1,-3) = (1, 2) $ , so $ T = (1,2) $ is the location of the treasure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091B/f03c880711f7b9805001588cb705f046f5d5dbf6.png)In the second sample, the hidden permutation is $ [2, 3, 4, 1] $ .

## 样例 #1

### 输入

```
2
2 5
-6 4
7 -2
-1 -3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
4
2 2
8 2
-7 0
-2 6
1 -14
16 -12
11 -18
7 -14
```

### 输出

```
9 -12
```

# AI分析结果



---
# 💡 Kay的C++算法解析：New Year and the Treasure Geolocation 深入学习指南 💡

<introduction>
今天我们来一起分析“New Year and the Treasure Geolocation”这道C++编程题。这道题的关键在于通过数学推导找到宝藏的坐标，本指南将帮助大家梳理思路，掌握核心解法，并通过有趣的可视化动画理解算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学（求和与平均值的应用）

🗣️ **初步分析**：
解决这道题的关键在于理解“所有线索和方尖碑的坐标之和等于n倍的宝藏坐标”这一数学关系。简单来说，就像分糖果：如果每个小朋友分到的糖果数量相同，那么总糖果数一定是“每人数量×小朋友人数”。本题中，宝藏坐标T是每个方尖碑坐标与对应线索向量的和，因此所有方尖碑和线索的坐标总和必然是n个T的和，即总和除以n就是T的坐标。

- **题解思路对比**：部分题解尝试枚举排列（O(n!)）或两两配对（O(n²)），但时间复杂度过高；正确的解法是通过数学推导，直接求和取平均（O(n)），高效且简洁。
- **核心算法流程**：读取所有方尖碑和线索的坐标，累加x和y的总和，最后除以n得到T的坐标。可视化时，重点展示“逐个累加坐标值”和“总和除以n”的过程，用高亮数字变化体现累加效果。
- **像素动画设计**：采用8位像素风格，用彩色方块表示每个坐标点（如方尖碑用蓝色，线索用红色），动画中这些方块逐个“飞”到总和框（黄色）中累加，最后总和框分裂成n个小框，每个小框显示相同的T坐标，伴随“叮”的音效提示完成。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下题解因高效、简洁且正确被选为优质题解（≥4星）：
</eval_intro>

**题解一：作者：installb**
* **点评**：此题解思路非常清晰，直接点出“所有坐标之和除以n”的核心数学关系，代码简洁规范（如用`LL`定义长整型避免溢出）。特别提醒“一定要开long long”，这对处理大数至关重要。代码可直接用于竞赛，边界处理严谨，是学习数学类问题的优秀参考。

**题解二：作者：woshishei（正解部分）**
* **点评**：此题解在枚举排列超时后，转向数学推导，正确总结出“总和除以n”的解法。代码简洁，仅需遍历所有坐标累加，时间复杂度O(n)，是高效的最优解。对算法优化的思考过程（从暴力到数学）对学习者有启发意义。

**题解三：作者：小黑AWM（正解部分）**
* **点评**：此题解先尝试O(n²)的枚举配对，发现问题后转向数学推导，最终得到正确解法。代码中强调“开long long”的重要性（因数据范围可能溢出int），这一调试经验对避免竞赛常见错误非常有用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的关键在于突破以下核心难点，掌握后能快速举一反三：
</difficulty_intro>

1.  **关键点1：如何发现总和与T的关系？**
    * **分析**：题目中每个线索对应一个方尖碑，且所有组合的结果都是T。假设排列为p，则T = (x_{p1}+a1, y_{p1}+b1) = ... = (x_{pn}+an, y_{pn}+bn)。将所有等式相加，左边是nT的x和y分量之和，右边是所有方尖碑和线索的x、y分量之和。因此，T的坐标是总和除以n。
    * 💡 **学习笔记**：当问题中存在“所有元素满足同一等式”的条件时，尝试对等式求和往往能简化问题。

2.  **关键点2：如何避免数据溢出？**
    * **分析**：题目中坐标范围是±2×10⁶，n最大为1e3，总和可能达到(2e6×2×1e3)=4e9，超出int范围（约2e9）。因此需要用long long存储总和。
    * 💡 **学习笔记**：处理大数时，优先使用long long类型，避免溢出错误。

3.  **关键点3：如何验证解法的正确性？**
    * **分析**：通过样例验证。例如样例1中，所有坐标之和是(2-6+7-1,5+4-2-3)=(2,4)，除以n=2得到(1,2)，与样例输出一致。
    * 💡 **学习笔记**：用样例数据手动计算是验证解法的有效方法。

### ✨ 解题技巧总结
- **问题抽象**：将复杂的排列问题转化为数学求和问题，抓住“所有结果相同”的条件，通过等式求和找到规律。
- **数据类型选择**：根据数据范围选择合适的类型（如本题用long long），避免溢出。
- **样例验证**：用题目提供的样例手动计算，确认解法正确性。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，代码简洁高效，能直接解决问题。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了多个优质题解的思路，通过累加所有坐标并取平均得到T的坐标，时间复杂度O(n)，是最优解法。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    using namespace std;

    int main() {
        long long n, x, y, sum_x = 0, sum_y = 0;
        cin >> n;
        for (int i = 0; i < 2 * n; ++i) {
            cin >> x >> y;
            sum_x += x;
            sum_y += y;
        }
        cout << sum_x / n << " " << sum_y / n << endl;
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取n，然后循环读取2n个坐标（n个方尖碑和n个线索），累加它们的x和y值到sum_x和sum_y。最后输出sum_x和sum_y除以n的结果，即为宝藏的坐标T。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段，学习其亮点和实现思路：
</code_intro_selected>

**题解一：作者：installb**
* **亮点**：明确使用long long避免溢出，代码简洁，关键注释提醒“一定要开long long”。
* **核心代码片段**：
    ```cpp
    #define LL long long 
    using namespace std;
    LL x,y,X = 0,Y = 0;
    int main(){
        register LL n;
        cin >> n;
        for(int i = 1;i <= n + n;i ++){
            cin >> x >> y;
            X += x; 
            Y += y; 
        }
        cout << X / n << " " << Y / n << endl; 
        return 0;
    }
    ```
* **代码解读**：用`LL`别名简化long long的书写，`X`和`Y`累加所有坐标的x和y值。循环读取2n个坐标（n+n），确保所有数据都被处理。最后输出平均值。
* 💡 **学习笔记**：使用类型别名（如`#define LL long long`）可提高代码可读性，避免重复书写。

**题解二：作者：woshishei（正解部分）**
* **亮点**：代码极简，直接累加求和，无冗余操作。
* **核心代码片段**：
    ```cpp
    int n,x,y;
    ll sumx=0,sumy=0;
    int main()
    {
        scanf("%d",&n);
        for(int i=1;i<=2*n;i++)
        {
            scanf("%d %d",&x,&y);
            sumx+=x;
            sumy+=y;
        }
        printf("%lld %lld",sumx/n,sumy/n);
        return 0;
    }
    ```
* **代码解读**：用`ll`（long long的缩写）定义sumx和sumy，循环读取2n个坐标，累加后输出平均值。代码结构清晰，无多余逻辑。
* 💡 **学习笔记**：极简的代码往往意味着更高效的实现，避免不必要的变量和操作。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“求和取平均”的过程，我们设计一个8位像素风格的动画，让你“看”到坐标如何累加并得到T！
</visualization_intro>

  * **动画演示主题**：`像素宝藏大冒险——坐标累加小课堂`
  * **核心演示内容**：展示所有方尖碑和线索的坐标逐个累加到总和，最后总和除以n得到T的过程。
  * **设计思路简述**：8位像素风格（如FC游戏的方块造型）营造轻松氛围；用不同颜色区分方尖碑（蓝色）和线索（红色），累加时方块“飞”到总和框（黄色）中，配合“叮”的音效强化记忆；最终总和分裂为n个相同的T方块，播放胜利音效，增强成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：屏幕分为左右两部分，左边是“输入区”（显示n个蓝色方尖碑和n个红色线索方块），右边是“累加区”（黄色总和框，显示当前sum_x和sum_y）。控制面板有“开始”“单步”“重置”按钮和速度滑块。

    2.  **输入累加**：点击“开始”，输入区的方块逐个飞向累加区。每个方块移动时，其x和y值显示在方块上（如蓝色方块显示“(2,5)”，红色方块显示“(7,-2)”）。到达累加区时，sum_x和sum_y的数字动态更新（如sum_x从0→2→-4→3→…），伴随“叮”的音效。

    3.  **计算平均值**：所有方块累加完成后，累加区出现一个“÷n”的像素箭头，sum_x和sum_y分别除以n（如sum_x=2，n=2→1），结果显示为绿色的T方块“(1,2)”。此时播放上扬的胜利音效，T方块闪烁庆祝。

    4.  **交互控制**：支持“单步”播放（逐一方块累加），速度滑块调节方块移动速度；“重置”按钮可重新开始动画。

  * **旁白提示**：
      - （方块移动时）“看！这个蓝色方尖碑的坐标是(2,5)，它飞进总和框，sum_x变成2啦～”
      - （累加完成时）“所有坐标都累加到总和框了，现在需要把总和除以n，也就是2，得到最终的T坐标！”
      - （显示T时）“成功找到宝藏！坐标是(1,2)，和样例输出一样哦～”

<visualization_conclusion>
通过这个动画，我们不仅能直观看到坐标累加的过程，还能理解“总和除以n”的数学逻辑，让抽象的计算变得生动有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是利用“总和与平均值”的数学关系解决问题，这种思路在类似问题中也很常见：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 当问题中所有元素满足同一等式时（如所有数的平均数、所有向量的终点相同），可尝试对等式求和，通过总和找到规律。
      - 适用于统计问题（如求班级平均分）、几何问题（如多个点平移后重合的坐标）等。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1518** - `两只塔姆沃斯牛`
          * 🗣️ **推荐理由**：考察坐标移动与相遇条件，需要分析移动规律，锻炼数学推导能力。
    2.  **洛谷 P1089** - `津津的储蓄计划`
          * 🗣️ **推荐理由**：涉及每月收支总和与平均值的计算，适合练习基本的求和与取整操作。
    3.  **洛谷 P2670** - `扫雷游戏`
          * 🗣️ **推荐理由**：通过周围雷的数量推导当前格的数值，需要分析局部与整体的关系，与本题的“总和”思路有相似之处。

-----

## 7\. 学习心得与经验分享 

<insights_intro>
部分题解提到了调试中的经验，这些对我们很有参考价值：
</insights_intro>

> **参考经验 (来自 小黑AWM)**：“我用O(n²)的做法莫名第八点RE，后来发现是数据溢出int，改用long long后解决。”
>
> **点评**：小黑的经验提醒我们，处理大数时一定要注意数据类型的选择。本题中坐标范围大，n也较大，总和很容易超出int的范围（约2e9），用long long能避免溢出错误。这是竞赛中常见的“坑”，需要特别注意！

-----

<conclusion>
本次关于“New Year and the Treasure Geolocation”的分析就到这里。通过数学推导和求和取平均的方法，我们能高效解决问题。记住，遇到“所有元素满足同一条件”的问题时，试试求和找规律！下次我们再一起探索新的编程挑战～💪
</conclusion>

---
处理用时：129.72秒