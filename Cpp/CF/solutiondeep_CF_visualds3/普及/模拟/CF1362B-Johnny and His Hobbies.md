# 题目信息

# Johnny and His Hobbies

## 题目描述

Among Johnny's numerous hobbies, there are two seemingly harmless ones: applying bitwise operations and sneaking into his dad's office. As it is usually the case with small children, Johnny is unaware that combining these two activities can get him in a lot of trouble.

There is a set $ S $ containing very important numbers on his dad's desk. The minute Johnny heard about it, he decided that it's a good idea to choose a positive integer $ k $ and replace each element $ s $ of the set $ S $ with $ s \oplus k $ ( $ \oplus $ denotes the [exclusive or](https://en.wikipedia.org/wiki/Exclusive_or#Computer_science) operation).

Help him choose such $ k $ that Johnny's dad will not see any difference after his son is done playing (i.e. Johnny will get the same set as before playing). It is possible that no such number exists. It is also possible that there are many of them. In such a case, output the smallest one. Note that the order of elements in a set doesn't matter, i.e. set $ \{1, 2, 3\} $ equals to set $ \{2, 1, 3\} $ .

Formally, find the smallest positive integer $ k $ such that $ \{s \oplus k | s \in S\} = S $ or report that there is no such number.

For example, if $ S = \{1, 3, 4\} $ and $ k = 2 $ , new set will be equal to $ \{3, 1, 6\} $ . If $ S = \{0, 1, 2, 3\} $ and $ k = 1 $ , after playing set will stay the same.

## 说明/提示

In the first test case, the answer is $ 1 $ because it is a minimum positive integer and it satisfies all the conditions.

## 样例 #1

### 输入

```
6
4
1 0 2 3
6
10 7 14 8 3 12
2
0 2
3
1 2 3
6
1 4 6 10 11 12
2
0 1023```

### 输出

```
1
4
2
-1
-1
1023```

# AI分析结果



---
# 💡 Kay的C++算法解析：Johnny and His Hobbies 深入学习指南 💡

<introduction>
今天我们来分析“Johnny and His Hobbies”这道题。它的核心是找到最小的正整数k，使得集合S中的每个数异或k后，新集合与原集合完全相同。通过这道题，我们可以掌握枚举法的灵活应用和位运算的特性。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举算法（暴力枚举+验证）

🗣️ **初步分析**：
解决这道题的关键在于“枚举+验证”。枚举法就像“试钥匙”——我们不知道哪把钥匙（k）能打开锁（满足条件），但可以逐个尝试。本题中，k的可能范围较小（最多到1024），所以枚举是高效的。

- **题解思路**：所有题解均采用枚举k（从1到1024），对每个k，计算S中每个数异或k后的结果，验证新集合是否等于原集合。差异主要在验证方式：部分题解排序后比较，部分用计数数组统计。
- **核心难点**：如何高效验证异或后的集合与原集合相等？排序后比较是最直观的方法（因为集合无序），而计数数组通过统计元素出现次数更高效。
- **可视化设计**：我们将设计一个8位像素动画，用彩色方块表示数组元素。枚举k时，方块颜色变化表示异或操作；排序时方块滑动到正确位置；比较时匹配的方块变绿，不匹配变红，配合“叮”的音效提示关键步骤。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选出以下3个优质题解：
</eval_intro>

**题解一：作者Jsxts_**
* **点评**：此题解巧妙使用计数数组验证集合相等，避免了排序的时间开销。代码中通过`c`数组记录元素出现次数，异或后直接更新计数并检查是否全零，逻辑简洁高效。变量命名清晰（如`mx`记录最大值优化循环范围），边界处理严谨（多组数据时`memset`初始化），实践价值高，适合竞赛快速实现。

**题解二：作者ShineEternal**
* **点评**：此题解预处理所有k的异或结果并排序，后续直接比对，思路直观。代码结构工整（嵌套循环层次分明），变量`b[j][i]`存储每个k的异或结果，便于后续排序和比较。适合新手理解枚举+排序验证的流程。

**题解三：作者OIerZhang**
* **点评**：此题解代码简洁易懂，强调排序的重要性（“不加就会满屏-1”）。通过`x`数组存储异或结果并排序，逐元素比较，逻辑直白。注释清晰（如“这里排序很重要”），适合刚接触枚举法的学习者模仿。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，我们常遇到以下关键问题，结合优质题解的共性，总结策略如下：
</difficulty_intro>

1.  **关键点1：确定k的枚举范围**
    * **分析**：k的最小可能为1，最大如何确定？观察到s_i最大为1023（样例最后一组输入为0和1023），而异或k后结果不超过s_i^k的最大值。题解中枚举到1024（覆盖所有可能），是经过验证的合理范围。
    * 💡 **学习笔记**：枚举范围需覆盖所有可能解，可通过分析数据范围或样例确定上限。

2.  **关键点2：高效验证集合相等**
    * **分析**：集合无序，直接比较顺序无意义。优质题解有两种方法：  
      - 排序后比较（如ShineEternal题解）：简单直观，适合新手；  
      - 计数数组统计（如Jsxts_题解）：避免排序的O(n logn)，时间更优。
    * 💡 **学习笔记**：验证集合相等时，排序或统计频次是常用方法，根据场景选择更高效的方式。

3.  **关键点3：多组数据的初始化处理**
    * **分析**：题目含多组测试用例，每次循环需重置临时数组（如计数数组`c`、异或结果数组`x`），否则残留数据会导致错误。Jsxts_题解使用`memset(c,0,sizeof c)`，OIerZhang题解每次循环重新计算`x`数组，都是严谨的处理。
    * 💡 **学习笔记**：多组数据时，务必初始化所有临时变量，避免“脏数据”干扰结果。

### ✨ 解题技巧总结
- **预处理排序**：原数组先排序，后续异或后的数组也排序，可直接逐元素比较。
- **计数数组优化**：用数组统计元素出现次数，异或后更新计数，检查是否全零，减少排序开销。
- **提前终止**：找到第一个满足条件的k后立即输出，避免无效枚举。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合多个优质题解，选择最简洁易懂的“排序后比较”方法，提供通用核心实现：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了OIerZhang和ShineEternal题解的思路，采用排序后比较的方法，逻辑清晰，适合新手学习。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    int a[1050], x[1050]; // a存储原数组，x存储异或后的临时数组

    int main() {
        int t;
        cin >> t;
        while (t--) {
            int n;
            bool found = false;
            cin >> n;
            for (int i = 1; i <= n; ++i)
                cin >> a[i];
            sort(a + 1, a + n + 1); // 原数组排序

            for (int k = 1; k <= 1024; ++k) { // 枚举k
                for (int i = 1; i <= n; ++i)
                    x[i] = a[i] ^ k; // 计算异或结果
                sort(x + 1, x + n + 1); // 临时数组排序

                bool match = true;
                for (int i = 1; i <= n; ++i) {
                    if (x[i] != a[i]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    cout << k << endl;
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "-1" << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先读取多组测试数据，对每组数据：  
  1. 输入原数组并排序；  
  2. 枚举k从1到1024，计算每个元素异或k后的结果存入临时数组；  
  3. 对临时数组排序，与原数组逐元素比较；  
  4. 找到第一个匹配的k输出，否则输出-1。

---
<code_intro_selected>
接下来赏析优质题解的核心片段：
</code_intro_selected>

**题解一：作者Jsxts_**
* **亮点**：使用计数数组替代排序，时间更优。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= 1024; i++) {
        for (int j = 1; j <= n; j++) a[j] ^= i, c[a[j]]--;
        for (int j = 0; j <= mx; j++) {
            if (c[j]) goto bre;
        }
        printf("%d\n", i);
        goto bre2;
        bre:;
        for (int j = 1; j <= n; j++) c[a[j]]++, a[j] ^= i;
    }
    ```
* **代码解读**：  
  这段代码枚举k时，直接修改原数组（异或k），并更新计数数组`c`（异或后元素的计数减1）。若所有`c[j]`为0，说明异或后的集合与原集合相同。若不匹配，再异或k恢复原数组并重置计数。这种方法避免了排序，时间复杂度更低（O(n)验证）。
* 💡 **学习笔记**：计数数组是统计频次的利器，适合元素范围较小的场景（如本题s_i<1024）。

**题解二：作者ShineEternal**
* **亮点**：预处理所有k的异或结果，减少重复计算。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 1024; j++) {
            b[j][i] = a[i] ^ j;
        }
    }
    for (int i = 1; i <= 1024; i++) {
        sort(b[i] + 1, b[i] + n + 1);
    }
    ```
* **代码解读**：  
  这段代码预先计算每个k对应的异或结果（存储在二维数组`b`中），并提前排序。后续只需比对排序后的`b[i]`和原数组，避免了重复异或和排序。适合需要多次验证不同k的场景。
* 💡 **学习笔记**：预处理关键步骤（如异或和排序），可减少重复计算，提升效率。

**题解三：作者OIerZhang**
* **亮点**：代码简洁，强调排序的必要性。
* **核心代码片段**：
    ```cpp
    sort(a + 1, a + 1 + n); // 原数组排序
    for (int k = 1; k <= 1024; k++) {
        for (int i = 1; i <= n; i++)
            x[i] = a[i] ^ k;
        sort(x + 1, x + 1 + n); // 临时数组排序
        for (int i = 1; i <= n; i++) {
            if (a[i] != x[i]) {
                f = false;
                break;
            }
        }
    }
    ```
* **代码解读**：  
  这段代码先对原数组排序，每次枚举k时计算异或结果并排序，直接比较排序后的数组。逻辑直白，适合新手理解“枚举+排序验证”的流程。
* 💡 **学习笔记**：排序是处理无序集合比较的常用手段，能将问题转化为有序数组的逐元素比对。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解枚举k和验证的过程，我们设计一个“像素钥匙试锁”的8位复古动画，用像素方块模拟数组操作！
</visualization_intro>

  * **动画演示主题**：像素锁与钥匙——寻找神奇的k值

  * **核心演示内容**：  
    主界面是一个像素化的“锁孔”场景，左侧显示原数组（彩色方块，如红色代表1，蓝色代表3），右侧显示当前k异或后的数组。枚举k时，右侧方块颜色变化（异或操作），然后滑动排序（像素滑动动画），最后与原数组比对（匹配的方块变绿，不匹配变红）。

  * **设计思路简述**：  
    8位像素风（如FC游戏的简洁色块）降低学习压力；异或时的颜色变化强化位运算的直观性；排序的滑动动画展示无序到有序的过程；音效（异或“叮”、匹配“成功”音）增强操作记忆；“小关卡”设计（每完成一个k的验证算一关）增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕分为左右两栏：左栏“原集合”显示排序后的原数组（如[0,1,2,3]用4个不同颜色的方块排列）；右栏“当前k异或结果”初始为空。  
        - 控制面板有“开始”“单步”“重置”按钮和速度滑块（1-5倍速）。  
        - 播放8位风格的轻快背景音乐（类似《超级玛丽》的简单旋律）。

    2.  **枚举k启动**：  
        - 点击“开始”，k从1开始枚举。当前k值显示在屏幕顶部（如“k=1”用像素字体）。  
        - 右栏每个方块执行异或动画：原方块颜色快速闪烁（如红色→紫色），表示异或k=1后的结果（如0^1=1，红色变蓝色）。

    3.  **排序过程演示**：  
        - 异或后的方块开始“滑动排序”：方块根据数值大小，从左到右滑动到正确位置（如[1,0,3,2]滑动后变为[0,1,2,3]）。  
        - 滑动时伴随“唰唰”的像素音效，每个方块到位后“叮”一声。

    4.  **比对验证**：  
        - 排序完成后，左右两栏方块逐位置比对：匹配的方块（如左1=右1）变绿色，不匹配的变红色（如左2≠右2）。  
        - 若全部变绿，播放“胜利”音效（上扬的“叮咚”），屏幕弹出“找到k=1！”的像素字幕；若有红色方块，播放“提示”音效（短促“滴”），进入下一个k的枚举。

    5.  **交互控制**：  
        - 单步模式：点击“单步”，每次执行一个k的枚举和验证；  
        - 自动模式：滑块调节速度（如慢速0.5倍，快速2倍），自动播放所有k的枚举；  
        - 重置：点击后清空右栏，k重置为1，重新开始。

  * **旁白提示**：  
    - （异或时）“看！原数字0异或k=1变成了1，颜色从红变蓝～”  
    - （排序时）“现在需要把异或后的数字排序，这样才能和原集合比较哦～”  
    - （比对时）“如果所有位置的数字都一样，说明k=1是正确的钥匙！”

<visualization_conclusion>
通过这个动画，我们能“看”到k的枚举过程、异或的颜色变化、排序的滑动，以及比对的结果，轻松理解枚举法的核心逻辑！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
枚举法和位运算的应用场景很广，掌握本题后，我们可以尝试以下拓展：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    枚举法适用于候选解范围小的问题（如求最小k、最短路径等）；位运算（异或、与、或）常用于处理数字的二进制特性（如找唯一出现奇数次的数、交换变量等）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1100 高低位交换**  
        * 🗣️ **推荐理由**：练习位运算的拆分与重组，理解二进制位的操作。
    2.  **洛谷 P1827 美国血统**  
        * 🗣️ **推荐理由**：结合枚举和二叉树遍历，训练综合解题能力。
    3.  **洛谷 P1558 色板游戏**  
        * 🗣️ **推荐理由**：涉及位运算和区间操作，巩固枚举法的灵活应用。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分。
</insights_intro>

-----

<conclusion>
通过这道题，我们掌握了枚举法的应用和位运算的特性。记住，遇到候选解范围小的问题，枚举+验证是简单有效的方法！多练习类似题目，你会更熟练哦～下次见！💪
</conclusion>

---
处理用时：130.93秒