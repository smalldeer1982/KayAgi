# 题目信息

# Hilbert's Hotel

## 题目描述

Hilbert's Hotel is a very unusual hotel since the number of rooms is infinite! In fact, there is exactly one room for every integer, including zero and negative integers. Even stranger, the hotel is currently at full capacity, meaning there is exactly one guest in every room. The hotel's manager, David Hilbert himself, decides he wants to shuffle the guests around because he thinks this will create a vacancy (a room without a guest).

For any integer $ k $ and positive integer $ n $ , let $ k\bmod n $ denote the remainder when $ k $ is divided by $ n $ . More formally, $ r=k\bmod n $ is the smallest non-negative integer such that $ k-r $ is divisible by $ n $ . It always holds that $ 0\le k\bmod n\le n-1 $ . For example, $ 100\bmod 12=4 $ and $ (-1337)\bmod 3=1 $ .

Then the shuffling works as follows. There is an array of $ n $ integers $ a_0,a_1,\ldots,a_{n-1} $ . Then for each integer $ k $ , the guest in room $ k $ is moved to room number $ k+a_{k\bmod n} $ .

After this shuffling process, determine if there is still exactly one guest assigned to each room. That is, there are no vacancies or rooms with multiple guests.

## 说明/提示

In the first test case, every guest is shifted by $ 14 $ rooms, so the assignment is still unique.

In the second test case, even guests move to the right by $ 1 $ room, and odd guests move to the left by $ 1 $ room. We can show that the assignment is still unique.

In the third test case, every fourth guest moves to the right by $ 1 $ room, and the other guests move to the right by $ 5 $ rooms. We can show that the assignment is still unique.

In the fourth test case, guests $ 0 $ and $ 1 $ are both assigned to room $ 3 $ .

In the fifth test case, guests $ 1 $ and $ 2 $ are both assigned to room $ 2 $ .

## 样例 #1

### 输入

```
6
1
14
2
1 -1
4
5 5 5 1
3
3 2 1
2
0 1
5
-239 -2 -100 -3 -11```

### 输出

```
YES
YES
YES
NO
NO
YES```

# AI分析结果



---
# 💡 Kay的C++算法解析：Hilbert's Hotel 深入学习指南 💡

<introduction>
今天我们来分析“Hilbert's Hotel”这道题。题目围绕无限酒店的客人移动问题，核心是判断移动后是否每个房间仍仅有一位客人。通过数论中的模运算和同余分析，我们可以找到关键规律。本指南将带大家理清思路，掌握解题技巧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数论应用（模运算与同余分析）`

🗣️ **初步分析**：
解决这道题的关键在于理解“无限数轴上的移动是否会导致重复”。我们可以将无限问题转化为有限问题——通过模运算，观察每`n`个房间的循环规律。  
数论中的“模运算”像一个“循环计数器”，比如`k mod n`会将无限的整数`k`映射到`0~n-1`的有限范围。本题中，每个房间`k`的移动量由`a[k mod n]`决定，因此移动后的位置`k + a[k mod n]`的模`n`余数是关键。  

**核心思路**：若存在两个不同的初始房间`i`和`j`（`0≤i,j<n`），使得`(a_i + i) mod n`等于`(a_j + j) mod n`，则说明这两个房间所在的无限序列中会有客人移动到同一位置（冲突），此时输出`NO`；否则所有余数唯一，输出`YES`。  

**可视化设计**：我们将用8位像素风格动画演示“模n余数计算”和“冲突检测”过程。例如，每个`i`对应的`(a_i + i) mod n`值用像素方块表示，若出现重复方块颜色则触发“冲突警报”（红色闪烁+短音效），否则绿色通过。动画支持单步执行，可观察每个`i`的余数计算过程。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下题解值得重点参考：
</eval_intro>

**题解一：作者tommymio（赞13）**
* **点评**：此题解从数学推导入手，清晰展示了如何将无限问题转化为有限模运算问题。代码中使用数组记录余数出现次数，高效且易懂。亮点在于对负数取模的处理（`((read()+i)%n+n)%n`），确保了余数的非负性，避免了边界错误。代码简洁，适合竞赛场景。

**题解二：作者hujiasheng1234（赞2）**
* **点评**：此题解直接给出结论“所有`a_i + i`模`n`余数需唯一”，并通过`map`判断重复，逻辑直白。证明部分简明扼要，解释了为何余数重复会导致冲突，适合初学者理解核心逻辑。

**题解三：作者killer_queen4804（赞2）**
* **点评**：此题解通过排序验证余数是否覆盖`0~n-1`，思路巧妙。代码中对`a[i]`的预处理（`((a[i]+i)%n+n)%n`）确保了余数正确，排序后检查是否严格递增，直观高效。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题时，常见的难点和应对策略如下：
</difficulty_intro>

1.  **难点1：将无限问题转化为有限问题**  
    * **分析**：无限数轴的客人移动看似无法直接处理，但注意到`k mod n`的结果仅在`0~n-1`之间循环，因此只需检查这`n`个初始房间的移动情况。若这`n`个房间的移动后余数唯一，则所有无限房间的移动都不会冲突。  
    * 💡 **学习笔记**：无限问题常可通过周期性（如模运算）转化为有限问题。

2.  **难点2：推导同余条件**  
    * **分析**：要判断是否存在`x≠y`使得`x + a[x mod n] = y + a[y mod n]`，通过代数变形可得`(a_i + i) ≡ (a_j + j) mod n`（其中`i=x mod n`，`j=y mod n`）。这一步需要对数论中的同余性质有深刻理解。  
    * 💡 **学习笔记**：代数变形是连接问题现象与数学本质的桥梁。

3.  **难点3：处理负数取模**  
    * **分析**：C++中`%`运算对负数结果可能为负（如`-1%3=-1`），需调整为非负余数（如`(-1%3+3)%3=2`）。题解中常用`((x % n) + n) % n`处理，确保余数在`0~n-1`。  
    * 💡 **学习笔记**：负数取模时，需额外调整以满足题目要求的非负性。

### ✨ 解题技巧总结
- **问题转化**：将无限问题转化为有限循环节（模n）的问题，简化计算。  
- **代数变形**：通过移项、同余分析，找到关键条件（余数唯一性）。  
- **边界处理**：对负数取模使用`((x % n) + n) % n`，确保余数正确。  

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，清晰展示了余数计算与冲突检测的核心逻辑。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了tommymio和hujiasheng1234的思路，通过数组记录余数出现次数，高效判断是否重复。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    using namespace std;

    const int MAX_N = 200010;
    bool vis[MAX_N]; // 记录余数是否已出现

    int main() {
        int T;
        cin >> T;
        while (T--) {
            int n;
            cin >> n;
            memset(vis, false, sizeof(vis)); // 初始化标记数组
            bool flag = true;

            for (int i = 0; i < n; ++i) {
                int a;
                cin >> a;
                // 计算 (a + i) mod n，确保非负
                int mod_val = (a + i) % n;
                mod_val = (mod_val + n) % n;

                if (vis[mod_val]) {
                    flag = false; // 余数重复，冲突
                }
                vis[mod_val] = true;
            }

            cout << (flag ? "YES" : "NO") << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取测试用例数`T`，对每个测试用例：  
  1. 初始化`vis`数组标记余数是否出现。  
  2. 遍历每个`i`（0~n-1），计算`(a_i + i) mod n`并调整为非负。  
  3. 若当前余数已被标记，说明冲突，标记`flag`为`false`。  
  4. 最终根据`flag`输出`YES`或`NO`。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者tommymio**
* **亮点**：使用数组记录余数，时间复杂度O(n)，适合大规模数据。
* **核心代码片段**：
    ```cpp
    for(register int i=0;i<n;++i) ++t[((read()+i)%n+n)%n];
    for(register int i=0;i<2*n;++i) if(t[i]>1) {flag=0;break;}
    ```
* **代码解读**：  
  `t`数组记录每个余数的出现次数。`((read()+i)%n+n)%n`确保余数非负。若某个余数出现次数>1，说明冲突。  
  为什么是`2*n`？因为`(a_i + i)`的范围可能为`-n+1`到`2n-1`，取模后范围是`0~n-1`，但代码中可能扩大数组避免越界（实际可优化为`n`）。  
* 💡 **学习笔记**：数组标记法是判断唯一性的高效方法。

**题解二：作者killer_queen4804**
* **亮点**：排序后检查余数是否覆盖`0~n-1`，直观易懂。
* **核心代码片段**：
    ```cpp
    for(int i=0;i<n;i++) a[i]=((a[i]+i)%n+n)%n;
    sort(a,a+n);
    for(int i=0;i<n;i++) if(a[i]!=i) {flag=0;break;}
    ```
* **代码解读**：  
  先计算每个`(a_i + i) mod n`，排序后若数组严格等于`0,1,...,n-1`，说明余数唯一。例如，n=3时，排序后应为`0,1,2`，否则冲突。  
* 💡 **学习笔记**：排序后检查连续性是验证唯一性的另一种思路。

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
我们设计一个“像素余数检测器”动画，用8位风格展示余数计算和冲突检测过程！
</visualization_intro>

  * **动画演示主题**：`像素余数大冒险`  
  * **核心演示内容**：展示`0~n-1`每个房间的`(a_i + i) mod n`计算过程，检测是否有重复余数。  
  * **设计思路简述**：8位像素风（如FC游戏画面）降低学习压力；余数方块的颜色变化和音效强化操作记忆；每检测到一个余数，视为“小关卡”完成，增加成就感。  

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕左侧显示`n`个像素方块（代表`0~n-1`的初始房间），右侧显示`n`个“余数槽”（初始为空）。  
        - 控制面板：单步/自动按钮、速度滑块（1-10倍速）、重置按钮。  
        - 背景音乐：8位风格的轻快旋律（如《超级玛丽》主题变奏）。

    2.  **计算余数**（单步执行示例）：  
        - 点击“单步”，当前处理房间`i`（用黄色边框高亮）。  
        - 计算`(a_i + i)`：像素数字从`a_i`和`i`位置弹出，相加得到临时值（如`a_i=3, i=2`则显示`3+2=5`）。  
        - 计算模`n`：临时值被“模运算机”（像素风格的小机器）处理，输出余数（如`5 mod 3=2`）。  
        - 余数方块（颜色随机，如红色代表余数0，蓝色代表余数1）滑入对应的余数槽，伴随“叮”音效。  

    3.  **冲突检测**：  
        - 若余数槽已存在同色方块，该槽闪烁红色，播放“警报”音效（短促的“滴滴”声），动画暂停并显示“冲突！”。  
        - 若所有余数槽填满且无重复，播放“胜利”音效（上扬的“啦~”），所有方块闪烁绿色。  

    4.  **自动演示模式**：  
        - 点击“自动播放”，动画自动执行，学习者可观察完整过程。速度滑块可调整节奏（如慢速适合初学，快速适合复习）。  

  * **旁白提示**：  
    - “现在处理房间i=2，计算a_i + i=3+2=5”  
    - “5模3等于2，余数槽2放入蓝色方块”  
    - “发现重复！余数槽1已有红色方块，冲突发生~”  

<visualization_conclusion>
通过这个动画，我们能直观看到每个余数的生成和冲突检测过程，理解“余数唯一”为何是解题的关键！
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是模运算与同余分析，这类思路还可用于以下场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 周期性问题（如循环队列、时间计算）。  
    - 哈希表冲突检测（判断键值是否唯一）。  
    - 无限序列的有限表示（如斐波那契数列模n的循环节）。  

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1082** - `同余方程`  
        * 🗣️ **推荐理由**：深入理解同余方程的解法，巩固数论基础。  
    2.  **洛谷 P2613** - `有理数取余`  
        * 🗣️ **推荐理由**：练习模运算的综合应用，处理负数和大数取余。  
    3.  **洛谷 P3811** - `乘法逆元`  
        * 🗣️ **推荐理由**：学习模运算中的逆元概念，拓展数论知识。  

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了处理负数取模的技巧，这对避免边界错误非常重要：
</insights_intro>

> **参考经验 (来自多位题解作者)**：“计算余数时，若`a_i + i`为负数，直接用`%`会得到负余数（如`-1%3=-1`），需用`((a_i + i) % n + n) % n`调整为非负。”  
> **点评**：负数取模是编程中常见的坑，这个技巧能确保余数在`0~n-1`范围内，避免因余数错误导致的冲突误判。大家在处理类似问题时，一定要注意这一步！

---

<conclusion>
通过对“Hilbert's Hotel”的分析，我们掌握了数论中模运算和同余分析的应用，学会了将无限问题转化为有限问题的关键技巧。希望大家通过练习巩固这些知识，下次挑战更难的算法题！💪
</conclusion>

---
处理用时：133.99秒