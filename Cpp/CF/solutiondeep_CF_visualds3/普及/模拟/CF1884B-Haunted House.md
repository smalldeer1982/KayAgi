# 题目信息

# Haunted House

## 题目描述

You are given a number in binary representation consisting of exactly $ n $ bits, possibly, with leading zeroes. For example, for $ n = 5 $ the number $ 6 $ will be given as $ 00110 $ , and for $ n = 4 $ the number $ 9 $ will be given as $ 1001 $ .

Let's fix some integer $ i $ such that $ 1 \le i \le n $ . In one operation you can swap any two adjacent bits in the binary representation. Your goal is to find the smallest number of operations you are required to perform to make the number divisible by $ 2^i $ , or say that it is impossible.

Please note that for each $ 1 \le i \le n $ you are solving the problem independently.

## 说明/提示

In the first test case, we cannot swap any elements, and the number $ 1 $ is not divisible by $ 2 $ .

In the second test case, the initial number is $ 1 $ . It is not divisible by $ 2 $ , but if we perform the operation, then we obtain the number with binary representation $ 10 $ , which is equal to $ 2 $ in decimal representation, thus, it is divisible by $ 2 $ . But this number is not divisible by $ 4 $ and we cannot obtain any other number using the operations.

In the third test case, the initial number is $ 2 $ . For $ i = 1 $ we do not have to perform any operations since the initial number is divisible by $ 2 $ . For $ i = 2 $ we can perform one operation swapping the first two bits (we would obtain $ 100 $ in binary representation, which corresponds to number $ 4 $ ). There is no answer for $ i = 3 $ .

## 样例 #1

### 输入

```
6
1
1
2
01
3
010
5
10101
7
0000111
12
001011000110```

### 输出

```
-1 
1 -1 
0 1 -1 
1 3 -1 -1 -1 
3 6 9 12 -1 -1 -1 
0 2 4 6 10 15 20 -1 -1 -1 -1 -1```

# AI分析结果



---
# 💡 Kay的C++算法解析：Haunted House 深入学习指南 💡

<introduction>
今天我们来一起分析“Haunted House”这道C++编程题。这道题的关键在于通过交换相邻位，让二进制数的末尾i位全为0，从而能被2ⁱ整除。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟与贪心策略` 

🗣️ **初步分析**：
解决“Haunted House”的关键在于理解：一个二进制数能被2ⁱ整除的条件是其末尾i位全为0。我们需要通过交换相邻位，用最少的操作次数将末尾i位变为0。这里用到了**贪心策略**——每次选择最右边的未使用的0来填充当前需要的位置，这样总移动次数最少。

- **题解思路**：首先统计字符串中0的总数cnt。对于每个i（1≤i≤n）：若i>cnt，无解（输出-1）；否则，找到倒数第i个0的位置，计算将其移动到目标位置（末尾第i位）所需的操作次数，并累加之前的操作次数。
- **核心难点**：如何高效记录0的位置并计算移动次数，以及处理多个i的递推关系。
- **可视化设计**：设计一个8位像素风格的动画，用不同颜色的方块表示0（绿色）和1（红色），动态展示0从原位置逐步移动到末尾i位的过程，高亮当前处理的0和目标位置，并实时显示操作次数的累加。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下题解评分均≥4星，值得重点参考：
</eval_intro>

**题解一：作者Novelist_**
* **点评**：此题解思路简洁直接，代码结构清晰。通过预处理0的位置并累加移动次数，高效解决了问题。变量命名规范（如b数组记录前缀和），边界处理严谨（如初始化b[0]=0），特别注意到了开long long防止溢出，实践价值高。

**题解二：作者Big_Dinosaur**
* **点评**：此题解抓住了问题本质——末尾i位全为0，明确提出“用最靠后的0调换”的贪心策略。公式推导（ans_i=ans_{i-1}+k_i-k）简洁明了，代码逻辑与思路高度一致，适合快速理解核心算法。

**题解三：作者N_Position**
* **点评**：此题解对问题的分情况讨论（i=1和i≠1）非常清晰，代码中通过指针j维护未使用的0的位置，逐步计算ans的方式高效且易懂。特别强调了“ans可能爆long long”的细节，体现了严谨的编程习惯。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下核心难点。结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何准确定位所需的0？**
    * **分析**：需要从右往左遍历字符串，记录每个0的位置。例如，用数组b记录前i个0的位置，其中b[i]表示第i个0（从右往左数）的原始位置。这样，当需要填充第i个末尾0时，直接取b[i]即可。
    * 💡 **学习笔记**：从右往左遍历能天然对齐“末尾i位”的需求，简化位置计算。

2.  **关键点2：如何计算最小操作次数？**
    * **分析**：每个0需要从原始位置移动到目标位置（末尾第i位）。目标位置从n-1开始（对应i=1时的末尾第1位），每填充一个0，目标位置左移一位（i=2时目标位置是n-2，依此类推）。移动次数为“目标位置 - 原始位置”，累加这些次数即可。
    * 💡 **学习笔记**：目标位置的左移是递推的，每次填充后更新目标位置，确保后续0的移动方向正确。

3.  **关键点3：如何处理无解情况？**
    * **分析**：当i超过字符串中0的总数cnt时，无法填充i个0，直接输出-1。因此，预处理阶段需要统计cnt，并在输出时判断i是否≤cnt。
    * 💡 **学习笔记**：预处理0的总数是快速判断无解的关键，避免无效计算。

### ✨ 解题技巧总结
<summary_best_practices>
- **预处理0的位置**：从右往左遍历字符串，记录每个0的位置，便于后续直接取用。
- **递推累加操作次数**：利用前缀和数组b，b[i]表示填充前i个0所需的总操作次数，避免重复计算。
- **开long long防溢出**：操作次数可能很大（如n=2e5时），必须使用long long类型。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解后提炼的通用核心C++实现，逻辑清晰且高效：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Novelist_和Big_Dinosaur的题解思路，通过预处理0的位置并递推计算操作次数，适合快速理解和实现。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t;
        cin >> t;
        while (t--) {
            int n;
            string s;
            cin >> n >> s;
            vector<long long> b(n + 1); // b[i]表示前i个0的总操作次数
            int cnt = 0; // 0的总数
            int target_pos = n - 1; // 目标位置（末尾第i位的位置）
            for (int i = n - 1; i >= 0; --i) { // 从右往左遍历
                if (s[i] == '0') {
                    ++cnt;
                    // 移动次数：target_pos - i（当前0的位置到目标位置的距离）
                    b[cnt] = b[cnt - 1] + (target_pos - i);
                    --target_pos; // 下一个0的目标位置左移一位
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (i <= cnt) cout << b[i] << ' ';
                else cout << "-1 ";
            }
            cout << '\n';
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，然后从右往左遍历字符串，统计0的个数cnt，并记录每个0移动到目标位置的累计操作次数（存入数组b）。最后，根据i是否超过cnt，输出对应的操作次数或-1。核心逻辑是通过预处理0的位置，递推计算总操作次数。

---
<code_intro_selected>
接下来，分析优质题解的核心代码片段：
</code_intro_selected>

**题解一：作者Novelist_**
* **亮点**：代码简洁，利用前缀和数组b直接存储前i个0的总操作次数，逻辑清晰。
* **核心代码片段**：
    ```cpp
    for(i = n - 1; i >= 0; --i)
        if(a[i] == '0') {
            ++tt;
            b[tt] = b[tt - 1] + ttt - i;
            --ttt;
        }
    ```
* **代码解读**：
    > 这里`tt`是0的计数，`ttt`是目标位置（初始为n-1）。每遇到一个0，计算该0移动到当前目标位置的次数（ttt - i），并累加到前缀和数组b中。然后目标位置左移一位（--ttt），为下一个0的目标位置做准备。
* 💡 **学习笔记**：前缀和数组b的设计避免了重复计算，时间复杂度为O(n)，非常高效。

**题解二：作者Big_Dinosaur**
* **亮点**：明确提出递推公式ans_i=ans_{i-1}+k_i-k，代码直接实现这一逻辑。
* **核心代码片段**：
    ```cpp
    ans += (n - i - j);
    ```
* **代码解读**：
    > `j`是当前0的位置，`n - i`是目标位置（末尾第i位的索引）。`n - i - j`表示将j位置的0移动到目标位置所需的操作次数。每次累加该值，得到ans_i=ans_{i-1}+(n - i - j)。
* 💡 **学习笔记**：递推公式的应用简化了计算，体现了贪心策略的核心——每次选择最近的0。

**题解三：作者N_Position**
* **亮点**：通过指针j维护未使用的0的位置，逐步计算ans，逻辑直观。
* **核心代码片段**：
    ```cpp
    while(s[j] != '0' && j >= 0) j--;
    if(j < 0) printf("-1 ");
    else {
        ans += (n - i - j);
        printf("%lld ", ans);
    }
    j--;
    ```
* **代码解读**：
    > 指针j从右往左寻找未使用的0（s[j]=='0'）。若找到，计算该0移动到目标位置（n-i）的次数（n-i-j），累加到ans并输出；若未找到（j<0），输出-1。j--表示该0已被使用，后续寻找下一个0。
* 💡 **学习笔记**：指针j的维护确保了每个0只被使用一次，避免了重复计算。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“贪心移动0”的过程，我们设计一个8位像素风格的动画，模拟0从原始位置移动到末尾i位的过程。
</visualization_intro>

  * **动画演示主题**：`像素小幽灵的0移动挑战`（复古FC风格，背景为紫色城堡，0是绿色小幽灵，1是红色小蝙蝠）

  * **核心演示内容**：展示对于每个i，如何将最右边的未使用的0（绿色幽灵）移动到末尾第i位（黄色标记位置），并累计操作次数。

  * **设计思路简述**：8位像素风格营造轻松氛围，颜色区分0和1便于观察；移动动画和音效强化操作记忆；关卡概念（每完成一个i视为“过关”）增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分：左边是长度为n的像素网格（每个格子16x16像素，绿色=0，红色=1）；右边是控制面板（单步/自动按钮、速度滑块、操作次数显示）。
          * 播放8位风格的背景音乐（类似《超级马里奥》的轻快旋律）。

    2.  **数据初始化**：
          * 高亮所有0（绿色幽灵），并在其上方显示原始位置索引。
          * 目标位置（末尾第i位）用黄色边框标记，初始i=1时目标位置是最右侧格子。

    3.  **核心步骤演示**：
          * **单步执行**：点击“单步”按钮，动画展示当前i对应的0的移动过程：绿色幽灵从原始位置逐格右移（每次移动一格，伴随“叮”的音效），直到到达目标位置。操作次数实时更新。
          * **自动播放**：选择速度（如0.5倍/1倍/2倍），动画自动按顺序处理i=1到i=n，每完成一个i播放“叮咚”音效，目标位置左移一位。
          * **高亮关键**：当前处理的0用闪烁的白色边框标记，目标位置用黄色闪烁提示；移动路径用虚线显示，帮助理解移动方向。

    4.  **目标达成/无解提示**：
          * 若i≤cnt（0足够），完成移动后，末尾i位变为绿色，播放“胜利”音效（上升调）；操作次数显示为b[i]。
          * 若i>cnt（0不足），所有红色蝙蝠闪烁，播放“警报”音效（短促低音），并在操作次数位置显示-1。

    5.  **游戏化积分**：
          * 每成功完成一个i（i≤cnt），获得10分，连续完成3个i触发“连击”特效（星星闪烁），额外加20分。积分显示在屏幕顶部，激励学习者观察完整过程。

  * **旁白提示**：
      * “看！绿色幽灵（0）需要移动到黄色格子（末尾第i位），每次交换相邻位，所以移动次数是它们的位置差～”
      * “如果没有绿色幽灵了（0不够），就无法完成挑战，输出-1哦！”

<visualization_conclusion>
通过这个像素动画，我们可以直观看到每个0的移动路径和操作次数的累加过程，轻松理解贪心策略的核心——每次选择最近的0，总操作次数最少。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以将“贪心移动特定字符到末尾”的思路迁移到其他问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 移动字符到指定位置的最小交换次数：如将字符串中的所有a移动到末尾，求最小交换次数（类似本题的0移动）。
      * 二进制数的性质应用：如判断二进制数的整除性（2ⁱ、3等），或通过交换位得到特定形式的数。
      * 前缀和与递推：通过预处理关键数据（如0的位置），递推计算结果，避免重复计算。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1115 最大子段和**  
        * 🗣️ **推荐理由**：练习前缀和与递推思想，与本题的前缀和数组b的设计有相似之处。
    2.  **洛谷 P1217 [USACO1.5]回文质数**  
        * 🗣️ **推荐理由**：练习二进制数的性质应用，理解数的整除性条件。
    3.  **洛谷 P2676 [USACO07DEC]Bookshelf B**  
        * 🗣️ **推荐理由**：练习贪心策略的选择，与本题“每次选最近的0”的贪心思路类似。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试中的经验，这些对我们很有参考价值：
</insights_intro>

> **参考经验 (来自多位题解作者)**：“记得开long long！操作次数可能很大，比如n=2e5时，累加的移动次数会超出int的范围，导致错误。”

**点评**：这是编程中常见的“血的教训”。在处理累加、计数类问题时，尤其是数据范围较大时（如n≤2e5），一定要使用long long类型。可以通过预先估计最大值（如本题中每个移动次数最多n，总次数最多n²=4e10，远超int的2e9）来判断是否需要开long long。

-----

<conclusion>
本次关于“Haunted House”的C++解题分析就到这里。通过理解贪心策略、预处理0的位置和递推计算操作次数，我们可以高效解决这类问题。希望大家通过练习和动画演示，真正掌握这一技巧！下次见～💪
</conclusion>

-----

---
处理用时：314.05秒