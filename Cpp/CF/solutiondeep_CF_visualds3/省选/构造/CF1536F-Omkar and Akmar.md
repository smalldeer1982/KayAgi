# 题目信息

# Omkar and Akmar

## 题目描述

Omkar and Akmar are playing a game on a circular board with $ n $ ( $ 2 \leq n \leq 10^6 $ ) cells. The cells are numbered from $ 1 $ to $ n $ so that for each $ i $ ( $ 1 \leq i \leq n-1 $ ) cell $ i $ is adjacent to cell $ i+1 $ and cell $ 1 $ is adjacent to cell $ n $ . Initially, each cell is empty.

Omkar and Akmar take turns placing either an A or a B on the board, with Akmar going first. The letter must be placed on an empty cell. In addition, the letter cannot be placed adjacent to a cell containing the same letter.

A player loses when it is their turn and there are no more valid moves.

Output the number of possible distinct games where both players play optimally modulo $ 10^9+7 $ . Note that we only consider games where some player has lost and there are no more valid moves.

Two games are considered distinct if the number of turns is different or for some turn, the letter or cell number that the letter is placed on were different.

A move is considered optimal if the move maximizes the player's chance of winning, assuming the other player plays optimally as well. More formally, if the player who has to move has a winning strategy, they have to make a move after which they will still have a winning strategy. If they do not, they can make any move.

## 说明/提示

For the first sample case, the first player has $ 4 $ possible moves. No matter what the first player plays, the second player only has $ 1 $ possible move, so there are $ 4 $ possible games.

## 样例 #1

### 输入

```
2```

### 输出

```
4```

## 样例 #2

### 输入

```
69420```

### 输出

```
629909355```

## 样例 #3

### 输入

```
42069```

### 输出

```
675837193```

# AI分析结果

# 💡 Kay的C++算法解析：Omkar and Akmar 深入学习指南 💡

<introduction>
  今天我们来一起分析「Omkar and Akmar」这道C++编程题。这是一道**组合数学与博弈论结合**的问题，核心是通过证明「后手必胜」的结论，将问题转化为**计数符合条件的终止状态及游戏过程**。本指南会帮你梳理关键结论、组合数推导，以及如何用C++高效实现！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：组合数学（计数问题）+ 博弈论（最优策略分析）

🗣️ **初步分析**：
解决这道题的关键，在于先**破解博弈的胜负规律**，再用**组合数学计算合法游戏的数量**。简单来说：
- **博弈结论**：无论先手怎么下，后手一定赢！因为游戏的终止状态（无法再落子）必然满足「填了偶数个棋子」——后手走最后一步，直接让先手没有 moves 可走。
- **组合计数**：既然所有合法操作都是最优策略（后手躺赢，无需额外策略选择），我们只需计算「所有可能的终止状态」对应的游戏过程数。终止状态的条件是：
  1. 空格不连续（长度≤1）——否则还能在中间填一个不同的字母；
  2. 去掉空格后的环是「AB交替」的（比如 ABAB… 或 BABA…）——否则相邻会有相同字母，违反规则。

**核心算法流程**：
1. 预处理阶乘和逆元（用于快速计算组合数）；
2. 枚举终止状态中「填了的棋子数k」（k是偶数，因为后手赢）；
3. 计算每个k对应的「终止状态数」×「游戏过程数（k!）」×「AB排列的两种可能」；
4. 求和所有k的结果，模1e9+7。

**可视化设计思路**：
我会用**8位像素风环形棋盘**演示游戏过程——比如用红色像素块代表A，蓝色代表B，灰色代表空格。放置棋子时，当前位置会闪烁并伴随「叮」的音效；终止时，棋盘会用金色高亮AB交替的序列，播放胜利音效。你还能通过「单步执行」看组合数是如何计算的（比如用小方块模拟「插板法」选空格位置）！


## 2. 精选优质题解参考

<eval_intro>
我从「思路清晰度、代码可读性、推导详细度」三个维度筛选了3份优质题解，帮你从不同角度理解问题！
</eval_intro>

**题解一：(来源：一之濑帆波)**
* **点评**：这份题解直接给出了核心公式，代码简洁高效。作者抓住了「环形问题」的关键——用n（环的旋转方案数）×2（AB两种排列）×组合数×阶乘，一步到位。代码中的阶乘预处理、逆元计算都是组合计数的标准操作，非常适合作为「模板参考」。

**题解二：(来源：dead_X)**
* **点评**：作者用「sg函数」暴力验证了「后手必胜」的结论，虽然过程繁琐，但能帮你理解「状态转移」的逻辑——通过计算每个空格局面的sg值，发现所有结果都是「后手赢」。这种「暴力找规律→证明」的思路，在博弈论问题中很常用！

**题解三：(来源：SunsetLake)**
* **点评**：这份题解最适合初学者！作者详细推导了「不相邻空格的组合数」——用「插板法」解释为什么n个位置放k个不相邻空格的方案数是C(n−k+1, k)。比如，把k个空格当作「块」，中间插k−1个非空格，这样总长度是k + (k−1) = 2k−1，剩下的n−(2k−1)个位置可以自由分配，对应组合数C(n−k+1, k)。推导过程比公式本身更重要！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的「门槛」在于**将博弈问题转化为计数问题**，以下3个关键点是破解的关键：
</difficulty_intro>

1.  **关键点1：为什么后手必胜？**
    * **分析**：终止状态的棋子数一定是偶数。假设终止时有k个棋子，去掉空格后的环是AB交替的（长度k），而环的AB交替序列长度必须是偶数（比如ABAB是4，BABA是4）——否则首尾会相同，违反规则。所以k是偶数，后手走最后一步，先手必输。
    * 💡 **学习笔记**：博弈论问题先找「终止状态的性质」，往往能直接得出胜负结论！

2.  **关键点2：终止状态的空格怎么计数？**
    * **分析**：终止状态的空格必须「不连续」（长度≤1）。对于k个棋子（偶数），剩下的n−k个空格要满足「两两不相邻」。用**插板法**计算：把k个棋子排成环，每个棋子之间最多放1个空格，总共有k个间隙，选n−k个间隙放空格，方案数是C(k, n−k)（非环形是C(k+1, n−k)，环形要减1）。
    * 💡 **学习笔记**：不相邻问题用「插板法」，环形问题记得调整间隙数！

3.  **关键点3：游戏过程数为什么是k!？**
    * **分析**：每个终止状态对应k!种游戏过程——因为k个棋子的放置顺序可以任意（只要满足规则）。比如，终止状态是A1B2A3B4，那么放置顺序可以是1→2→3→4，也可以是2→1→4→3，只要每一步都合法。
    * 💡 **学习笔记**：计数「过程数」时，若每个步骤的选择不影响结果（只要合法），往往用「阶乘」计算所有排列！

### ✨ 解题技巧总结
- **技巧A：博弈论先找终止状态**：不要直接想策略，先分析「无法操作时的状态」，往往能快速得出胜负结论。
- **技巧B：组合数预处理**：对于n≤1e6的问题，必须预处理阶乘和逆元（用费马小定理求逆元），否则会超时。
- **技巧C：环形问题转化**：环形问题可以通过「固定一个位置」转化为线性问题（比如固定第一个位置不是空格），避免重复计数。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心代码**——综合了所有优质题解的思路，结构清晰，适合直接复用！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码预处理阶乘和逆元，枚举所有偶数k，计算每个k对应的方案数，最后求和。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;

    typedef long long i64;
    const int MOD = 1e9 + 7;
    const int MAXN = 1e6 + 5;

    i64 fac[MAXN], inv[MAXN];

    i64 power(i64 a, int b) {
        i64 res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    void precompute(int n) {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i-1] * i % MOD;
        inv[n] = power(fac[n], MOD-2);
        for (int i = n-1; i >= 0; --i)
            inv[i] = inv[i+1] * (i+1) % MOD;
    }

    i64 C(int x, int y) {
        if (x < 0 || y < 0 || x < y) return 0;
        return fac[x] * inv[y] % MOD * inv[x - y] % MOD;
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int n;
        cin >> n;
        precompute(n);
        i64 ans = 0;
        for (int k = 2; k <= n; k += 2) { // k是填的棋子数（偶数）
            int space = n - k; // 空格数
            i64 ways = (C(k, space) + C(k-1, space-1)) % MOD; // 环形空格方案数
            ways = ways * 2 % MOD; // AB两种排列
            ways = ways * fac[k] % MOD; // 游戏过程数（k!）
            ans = (ans + ways) % MOD;
        }
        cout << ans << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 1. `precompute`函数预处理阶乘`fac`和逆元`inv`——`fac[i]`是i!模MOD，`inv[i]`是i!的逆元（用于组合数计算）；
    > 2. `C(x,y)`计算组合数C(x,y)，用公式`fac[x]/(fac[y] * fac[x-y])`，模运算下用逆元代替除法；
    > 3. 主函数枚举所有偶数k（填的棋子数），计算每个k对应的：
    >    - 空格方案数（环形问题分「第一个位置是空」和「不是空」两种情况，对应C(k, space) + C(k-1, space-1)）；
    >    - 乘以2（AB两种排列）和k!（游戏过程数）；
    > 4. 求和所有k的结果，输出答案。

---
<code_intro_selected>
再看**题解三（SunsetLake）**的核心片段——它清晰展示了「组合数的推导」！
</code_intro_selected>

**题解三：(来源：SunsetLake)**
* **亮点**：用「插板法」详细解释了不相邻空格的方案数，代码中的组合数计算直接对应推导过程。
* **核心代码片段**：
    ```cpp
    for(int i=0;i<=n;++i){
        if((n-i)&1)continue; // 只处理偶数i（填的棋子数）
        int space = n - i;
        ll ways = (C(i-1, space-1) + C(i, space)) % mod; // 环形空格方案数
        ways = ways * 2 % mod; // AB排列
        ways = ways * fac[i] % mod; // 过程数
        ans = (ans + ways) % mod;
    }
    ```
* **代码解读**：
    > 1. `(n-i)&1`判断i是否是偶数（填的棋子数必须是偶数）；
    > 2. `C(i-1, space-1)`对应「第一个位置是空」的情况——剩下的i-1个棋子排成环，选space-1个空格；
    > 3. `C(i, space)`对应「第一个位置不是空」的情况——i个棋子排成环，选space个空格；
    > 4. 乘以2是AB两种排列，乘以`fac[i]`是i!种过程数。
* 💡 **学习笔记**：环形问题的组合数计算，往往需要分「边界是否为空」两种情况，避免重复或遗漏！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了帮你「看清楚」组合数和游戏过程，我设计了一个**8位像素风的环形棋盘动画**——像玩FC游戏一样学算法！
</visualization_intro>

  * **动画演示主题**：像素探险家在环形棋盘上「放置字母」，逐步构建终止状态。
  * **设计思路**：用复古的红白机色彩（红A、蓝B、灰空格），结合音效和单步控制，让你直观理解「不相邻空格」和「AB交替」的规则。
  * **动画帧步骤与交互关键点**：

    1. **场景初始化**：
       - 屏幕中央显示一个8位像素的环形棋盘（比如n=6，6个灰色方块围成圈）；
       - 下方控制面板有「开始/暂停」「单步」「重置」按钮，以及速度滑块；
       - 背景播放轻快的8位BGM（比如《超级马里奥》的小关卡音乐）。

    2. **算法启动**：
       - 自动播放「放置字母」的过程：第一个位置放红A（闪烁+「叮」音效），第二个位置放蓝B（闪烁+「叮」），第三个位置放红A……直到形成AB交替的序列；
       - 每放一个字母，右侧面板显示当前的「组合数计算」（比如「选了2个空格，方案数C(4,2)=6」）。

    3. **核心逻辑演示**：
       - **空格选择**：当需要放空格时，候选位置会用黄色高亮（比如n=6，k=4，选2个空格），选中的空格变成灰色（伴随「咔嗒」音效）；
       - **终止状态**：当所有字母和空格都放置完成（满足AB交替、空格不连续），棋盘会用金色边框高亮，播放「胜利」音效（比如《塞尔达》的解谜成功音）。

    4. **交互控制**：
       - 「单步」按钮：逐帧观看每一步放置过程，适合仔细研究；
       - 「速度滑块」：调整自动播放的速度（从「慢」到「快」）；
       - 「重置」按钮：回到初始状态，重新演示。

  * **旁白提示**：
    - （放第一个A时）：「先手放A，位置1！注意相邻不能放相同字母~」；
    - （选空格时）：「现在要选2个不相邻的空格，候选位置是2、4、6，选哪两个？」；
    - （终止时）：「完成！这个终止状态对应4!×2=48种游戏过程~」。

<visualization_conclusion>
通过这个动画，你能直观看到「AB交替」「空格不连续」的规则，以及组合数是如何计算的。就像玩游戏一样，不知不觉就掌握了核心逻辑！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
组合数学是编程竞赛的「基础工具」，掌握了本题的思路，可以解决很多类似问题！
</similar_problems_intro>

  * **通用思路迁移**：
    - 「不相邻元素计数」：比如「在n个位置放k个路灯，不能相邻」，用插板法C(n−k+1, k)；
    - 「环形排列计数」：比如「n个人围坐，选k个不相邻的人」，用C(n−k, k) + C(n−k−1, k−1)；
    - 「过程数计数」：比如「计算所有合法的排列顺序」，用阶乘乘以状态数。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1025** - 数的划分
          * 🗣️ **推荐理由**：练习「插板法」的经典问题，帮你巩固「不相邻元素计数」的思路。
    2.  **洛谷 P2054** - 洗牌
          * 🗣️ **推荐理由**：组合数学与排列的结合，需要计算「洗牌后的位置」，锻炼模运算和逆元的应用。
    3.  **洛谷 P3901** - 数列找不同
          * 🗣️ **推荐理由**：虽然是模拟题，但需要用组合数计算「不同子序列的数量」，拓展你的计数思维。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中的「经验分享」能帮你避免踩坑，以下是2条宝贵的心得：
</insights_intro>

> **参考经验 (来自 dead_X)**：「我用sg函数暴力计算了前10个情况，发现结果全是后手赢，这才敢大胆证明结论。」
>
> **点评**：当你对结论不确定时，「暴力找规律」是个好方法！比如用小数据验证，再推导通用结论，比直接想证明更高效。

> **参考经验 (来自 SunsetLake)**：「环形问题的组合数要分两种情况，否则会漏算！」
>
> **点评**：环形问题的「边界条件」很容易被忽略，比如「第一个位置是否为空」，分情况讨论能避免错误。


<conclusion>
本次关于「Omkar and Akmar」的分析就到这里！这道题的核心是「将博弈问题转化为计数问题」——先证明后手必胜，再用组合数学计算所有合法情况。记住：**组合数的关键是「模型转化」，把问题变成「插板法」「排列」等熟悉的模型**。下次遇到计数问题，不妨先想想「能不能用阶乘、组合数解决」！💪
</conclusion>

---
处理用时：126.53秒