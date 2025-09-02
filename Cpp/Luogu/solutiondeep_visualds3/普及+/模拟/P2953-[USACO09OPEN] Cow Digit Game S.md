# 题目信息

# [USACO09OPEN] Cow Digit Game S

## 题目描述

Bessie is playing a number game against Farmer John, and she wants you to help her achieve victory.

Game i starts with an integer N\_i (1 <= N\_i <= 1,000,000). Bessie goes first, and then the two players alternate turns. On each turn, a player can subtract either the largest digit or the smallest non-zero digit from the current number to obtain a new number. For example, from 3014 we may subtract either 1 or 4 to obtain either 3013 or 3010, respectively. The game continues until the number becomes 0, at which point the last player to have taken a turn is the winner.

Bessie and FJ play G (1 <= G <= 100) games. Determine, for each game, whether Bessie or FJ will win, assuming that both play perfectly (that is, on each turn, if the current player has a move that will guarantee his or her win, he or she will take it).

Consider a sample game where N\_i = 13. Bessie goes first and takes 3, leaving 10. FJ is forced to take 1, leaving 9. Bessie takes the remainder and wins the game.

贝茜和约翰在玩一个数字游戏．贝茜需要你帮助她．

游戏一共进行了G(1≤G≤100)场．第i场游戏开始于一个正整数Ni(l≤Ni≤1,000,000)．游

戏规则是这样的：双方轮流操作，将当前的数字减去一个数，这个数可以是当前数字的最大数码，也可以是最小的非0数码．比如当前的数是3014，操作者可以减去1变成3013，也可以减去4变成3010．若干次操作之后，这个数字会变成0．这时候不能再操作的一方为输家．    贝茜总是先开始操作．如果贝茜和约翰都足够聪明，执行最好的策略．请你计算最后的赢家．

比如，一场游戏开始于13.贝茜将13减去3变成10．约翰只能将10减去1变成9．贝茜再将9减去9变成0．最后贝茜赢．


## 说明/提示

For the first game, Bessie simply takes the number 9 and wins. For the second game, Bessie must take 1 (since she cannot take 0), and then FJ can win by taking 9.


## 样例 #1

### 输入

```
2 
9 
10 
```

### 输出

```
YES 
NO 
```

# AI分析结果



---
# 💡 Kay的C++算法解析：[USACO09OPEN] Cow Digit Game S 深入学习指南 💡

<introduction>
今天我们来分析这道经典的博弈论题目——“Cow Digit Game S”。通过这道题，我们将学习如何用动态规划（DP）预处理必胜/必败态，掌握博弈论中状态转移的核心思路。让我们一起开启解题之旅吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划（博弈论中的必胜/必败态分析）`

🗣️ **初步分析**：
解决这道题的关键在于理解“博弈论中的必胜态与必败态”。简单来说，必胜态是指当前玩家存在一种操作，使得对手进入必败态；必败态则是无论当前玩家如何操作，对手都能进入必胜态。这就像“石头剪刀布”中，如果你能通过一步操作让对手处于必输的位置，那你当前就是必胜的。

在本题中，每个数字 \( N \) 的状态（必胜或必败）由它的两个后继状态决定：减去最大数码后的 \( N - \text{max\_dig} \) 和减去最小非零数码后的 \( N - \text{min\_dig} \)。我们需要预处理所有 \( 1 \leq N \leq 1,000,000 \) 的状态，从而快速回答每个查询。

- **题解思路**：所有优质题解均采用动态规划预处理。初始化 \( 1 \sim 9 \) 为必胜态（一步到0），然后从 \( 10 \) 到 \( 1,000,000 \) 依次计算每个 \( N \) 的状态：若两个后继状态均为必胜态，则当前为必败态；否则为必胜态。
- **核心难点**：正确计算每个 \( N \) 的最大数码（max_dig）和最小非零数码（min_dig），以及确保预处理顺序的正确性（从小到大计算，确保后继状态已处理）。
- **可视化设计**：我们将设计一个8位像素风格的动画，用不同颜色的像素块表示数字，动态展示 \( N \) 如何通过减去max_dig或min_dig转移到后继状态，并标记必胜/必败态（如绿色为必胜，红色为必败）。关键步骤会有“叮”的音效提示，完成预处理后用庆祝音效提示成功。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下题解表现突出（≥4星），值得重点学习：
</eval_intro>

**题解一：作者 konjacq**
* **点评**：此题解思路清晰，代码简洁高效。通过预处理数组 `f` 存储每个数字的状态，正确计算max_dig和min_dig，并利用动态规划递推状态。代码中使用 `inline` 函数优化计算数码的过程，时间复杂度为 \( O(N) \)，空间复杂度 \( O(N) \)，适用于 \( N \leq 1,000,000 \) 的范围。实践价值高，可直接用于竞赛。

**题解二：作者 UperFicial**
* **点评**：此题解在预处理时优化了范围，仅预处理到输入中的最大值，避免了不必要的计算。提出“离线处理”思路，减少时间浪费，特别适合多组查询且输入范围较大的场景。代码逻辑清晰，变量命名直观（如 `maxval` 表示输入最大值），体现了良好的编程习惯。

**题解三：作者 qzhwlyn**
* **点评**：此题解正确实现了动态规划的核心逻辑，通过遍历输入中的最大值来预处理状态，节省空间。代码中对max_dig和min_dig的计算简洁明了，边界处理（如min_dig可能为10的情况）严谨，适合初学者理解状态转移过程。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，我们需要突破以下核心难点：
</difficulty_intro>

1.  **关键点1：如何准确定义必胜/必败态？**
    * **分析**：必胜态的定义是“存在至少一个后继状态为必败态”，必败态的定义是“所有后继状态均为必胜态”。例如，数字 \( 13 \) 的后继是 \( 10 \)（减3）和 \( 12 \)（减1），若其中有一个是必败态，则 \( 13 \) 为必胜态。
    * 💡 **学习笔记**：必胜态与必败态的判断是博弈论问题的核心，需严格根据后继状态推导。

2.  **关键点2：如何高效计算每个数字的max_dig和min_dig？**
    * **分析**：通过取模运算逐位分解数字，分别记录最大值和最小非零值。例如，数字 \( 3014 \) 分解为 \( 3,0,1,4 \)，max_dig为4，min_dig为1（排除0）。
    * 💡 **学习笔记**：逐位取模是处理数位问题的常用方法，需注意排除0对min_dig的干扰。

3.  **关键点3：预处理顺序的正确性**
    * **分析**：必须从小到大预处理数字，因为计算 \( N \) 的状态时，需要 \( N - \text{max\_dig} \) 和 \( N - \text{min\_dig} \) 的状态已提前计算。例如，计算 \( N=10 \) 时，需要 \( 10 - 1=9 \)（已初始化）和 \( 10 - 1=9 \)（同一值）的状态。
    * 💡 **学习笔记**：动态规划的预处理顺序需确保依赖的子问题已解决。

### ✨ 解题技巧总结
- **预处理优化**：对于多组查询，预处理所有可能的 \( N \) 状态，使每次查询 \( O(1) \) 时间完成。
- **数位分解技巧**：通过 `while` 循环和取模运算逐位分解数字，高效计算max_dig和min_dig。
- **边界处理**：注意min_dig不能为0（题目要求减去最小非零数码），需单独判断。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼出一个通用的核心C++实现，便于大家理解整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了konjacq和UperFicial的题解思路，预处理所有 \( 1 \leq N \leq 1,000,000 \) 的状态，适用于多组查询。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm>
    using namespace std;

    const int MAX_N = 1000000;
    bool f[MAX_N + 1]; // f[i] = true 表示i为必胜态

    inline int max_dig(int x) {
        int res = 0;
        while (x) {
            res = max(res, x % 10);
            x /= 10;
        }
        return res;
    }

    inline int min_dig(int x) {
        int res = 10;
        while (x) {
            int d = x % 10;
            if (d != 0 && d < res) res = d;
            x /= 10;
        }
        return res == 10 ? 0 : res; // 若所有位都是0（不可能），返回0
    }

    int main() {
        // 初始化1~9为必胜态（一步到0）
        for (int i = 1; i <= 9; ++i) f[i] = true;
        // 预处理10~1e6的状态
        for (int i = 10; i <= MAX_N; ++i) {
            int maxd = max_dig(i);
            int mind = min_dig(i);
            // 若两个后继均为必胜态，则当前为必败态；否则为必胜态
            f[i] = !(f[i - maxd] && f[i - mind]);
        }
        // 处理查询
        int G, N;
        cin >> G;
        while (G--) {
            cin >> N;
            cout << (f[N] ? "YES" : "NO") << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先定义 `max_dig` 和 `min_dig` 函数计算数位的最大和最小非零值。初始化 \( 1 \sim 9 \) 为必胜态后，从 \( 10 \) 到 \( 1,000,000 \) 逐次计算每个数的状态：若减去max_dig或min_dig后的两个数均为必胜态，则当前数为必败态（`f[i] = false`），否则为必胜态（`f[i] = true`）。最后处理多组查询，直接输出结果。

---
<code_intro_selected>
接下来，我们分析优质题解中的核心代码片段，学习其亮点和实现思路。
</code_intro_selected>

**题解一：作者 konjacq**
* **亮点**：代码简洁，使用 `inline` 优化数位计算，预处理范围覆盖所有可能值，适合直接提交。
* **核心代码片段**：
    ```cpp
    inline int fmax(int x) {
        int m=0;
        while (x) { if (x%10>m) m=x%10; x/=10; }
        return m;
    }

    inline int fmin(int x) {
        int m=10;
        while (x) { if (x%10<m&&x%10) m=x%10; x/=10; }
        return m;
    }

    int main() {
        for (int i=1;i<10;i++) f[i]=true;
        for (int i=10;i<1000001;i++) {
            if (f[i-fmax(i)] && f[i-fmin(i)]) ; // 不做处理（f[i]默认为false）
            else f[i]=true;
        }
        // 处理查询...
    }
    ```
* **代码解读**：
    `fmax` 和 `fmin` 函数分别计算最大数码和最小非零数码。预处理时，若两个后继状态均为必胜态（`f[i-fmax(i)] && f[i-fmin(i)]` 为真），则当前状态为必败态（`f[i]` 保持默认的 `false`）；否则为必胜态（`f[i] = true`）。这直接体现了博弈论的状态转移逻辑。
* 💡 **学习笔记**：利用数组默认值（`false`）简化代码，避免显式赋值，提升效率。

**题解二：作者 UperFicial**
* **亮点**：离线处理，仅预处理到输入中的最大值，节省时间和空间。
* **核心代码片段**：
    ```cpp
    int main() {
        int g, maxval = 0;
        cin >> g;
        vector<int> queries(g);
        for (int i = 0; i < g; ++i) {
            cin >> queries[i];
            maxval = max(maxval, queries[i]);
        }
        // 预处理到maxval
        for (int i = 10; i <= maxval; ++i) {
            int maxd = max_dig(i), mind = min_dig(i);
            f[i] = !(f[i - maxd] && f[i - mind]);
        }
        // 输出结果...
    }
    ```
* **代码解读**：
    首先读取所有查询，找到最大值 `maxval`，仅预处理到 `maxval` 而非固定的 \( 1,000,000 \)，减少了不必要的计算。这种“离线处理”方法在多组查询且输入范围较大时非常实用。
* 💡 **学习笔记**：根据输入动态调整预处理范围，是优化时间和空间的重要技巧。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解动态规划预处理和状态转移的过程，我们设计一个“像素数字大战”8位风格动画，让大家“看”到每个数字的必胜/必败状态是如何推导出来的！
</visualization_intro>

  * **动画演示主题**：`像素数字大战——贝茜的胜利之路`

  * **核心演示内容**：展示从 \( 1 \) 到 \( 1,000,000 \) 的数字如何通过减去max_dig或min_dig转移状态，用颜色标记必胜（绿色）/必败（红色），并动态更新状态数组。

  * **设计思路简述**：采用8位像素风格（类似FC游戏），用像素方块表示数字，颜色区分状态。关键步骤（如计算max_dig、状态转移）伴随“叮”的音效，完成预处理后播放胜利音效，增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          - 屏幕左侧为“数字轨道”：100个像素方块横向排列（代表 \( 1 \sim 100 \)，可滚动查看更大数字）。
          - 右侧为“状态面板”：显示当前处理的数字 \( i \)、max_dig、min_dig，以及 \( i - \text{max\_dig} \) 和 \( i - \text{min\_dig} \) 的状态。
          - 控制面板：包含“单步”、“自动播放”（速度可调）、“重置”按钮。

    2.  **初始化阶段**：
          - \( 1 \sim 9 \) 的方块变为绿色（必胜态），伴随“滴”的音效。

    3.  **预处理阶段**（自动播放或单步）：
          - 处理 \( i=10 \) 时，计算max_dig=1（数字10的各位是1和0，max_dig=1），min_dig=1（非零最小是1）。
          - 高亮 \( 10 - 1 = 9 \) 的方块（绿色，必胜态）。
          - 由于两个后继均为必胜态，\( 10 \) 变为红色（必败态），音效“咚”。
          - 类似地，处理 \( i=11 \)：max_dig=1，min_dig=1，\( 11-1=10 \)（红色，必败态），因此 \( 11 \) 变为绿色（必胜态），音效“叮”。

    4.  **查询演示**：
          - 输入查询数字（如9），对应方块绿色闪烁，输出“YES”，播放胜利音效；输入10，红色闪烁，输出“NO”。

    5.  **交互功能**：
          - 单步播放：每点击一次，处理一个数字，显示计算过程。
          - 自动播放：以用户选择的速度（如100ms/步）连续处理，观察状态转移的整体规律。

  * **旁白提示**：
      - “现在处理数字 \( i=10 \)，它的最大数码是1，最小非零数码也是1。减去后得到9（必胜态）。两个后继都是必胜态，所以10是必败态！”
      - “看，数字11减去1得到10（必败态），所以11是必胜态，贝茜可以赢哦！”

<visualization_conclusion>
通过这个动画，我们不仅能直观看到每个数字的状态如何由后继推导而来，还能感受动态规划预处理的高效性。像素风格和音效设计让学习过程更有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以将博弈论的必胜态分析思路迁移到更多问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      本题的核心是“通过子问题状态推导当前状态”，这种思路适用于：
      - 取石子游戏（每次取1~k个石子，最后取完者胜）。
      - 棋盘移动游戏（每次移动若干步，无法移动者败）。
      - 数字操作游戏（如每次减去因数，最后到1者胜）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1288 取数游戏II**  
          * 🗣️ **推荐理由**：涉及博弈论中的必败态分析，需判断是否存在路径使对手进入必败态，与本题思路类似。
    2.  **洛谷 P1118 数字三角形游戏**  
          * 🗣️ **推荐理由**：动态规划与博弈论结合，需预处理每个位置的胜负状态，锻炼状态转移能力。
    3.  **洛谷 P2197 nim游戏**  
          * 🗣️ **推荐理由**：经典Nim游戏，学习异或运算在博弈论中的应用，拓展对必胜态的理解。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者提到预处理的重要性，例如：“预处理所有可能的状态，避免重复计算，是处理大数据范围题目的关键。” 这对我们有重要启示：
</insights_intro>

> **参考经验 (来自 konjacq)**：“一开始没预处理，直接对每个查询单独计算，结果超时了。后来想到预处理所有状态，时间复杂度降到了 \( O(N) \)，轻松通过。”

**点评**：预处理是解决大数据范围问题的常用技巧，通过空间换时间，将每次查询的时间复杂度降至 \( O(1) \)。在编程竞赛中，这种优化思路非常重要，尤其是当 \( N \) 达到 \( 10^6 \) 级别时，预处理能显著提升效率。

-----

<conclusion>
通过对“Cow Digit Game S”的分析，我们掌握了博弈论中必胜/必败态的动态规划预处理方法，学会了如何通过数位分解计算max_dig和min_dig，并设计了有趣的像素动画加深理解。希望大家能将这些思路应用到更多问题中，不断提升编程能力！下次见～ 💪
</conclusion>

---
处理用时：164.33秒