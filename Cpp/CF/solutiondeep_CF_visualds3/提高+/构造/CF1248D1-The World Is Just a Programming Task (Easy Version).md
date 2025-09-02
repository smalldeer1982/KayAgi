# 题目信息

# The World Is Just a Programming Task (Easy Version)

## 题目描述

This is an easier version of the problem. In this version, $ n \le 500 $ .

Vasya is an experienced developer of programming competitions' problems. As all great minds at some time, Vasya faced a creative crisis. To improve the situation, Petya gifted him a string consisting of opening and closing brackets only. Petya believes, that the beauty of the bracket string is a number of its cyclical shifts, which form a correct bracket sequence.

To digress from his problems, Vasya decided to select two positions of the string (not necessarily distinct) and swap characters located at this positions with each other. Vasya will apply this operation exactly once. He is curious what is the maximum possible beauty he can achieve this way. Please help him.

We remind that bracket sequence $ s $ is called correct if:

- $ s $ is empty;
- $ s $ is equal to "( $ t $ )", where $ t $ is correct bracket sequence;
- $ s $ is equal to $ t_1 t_2 $ , i.e. concatenation of $ t_1 $ and $ t_2 $ , where $ t_1 $ and $ t_2 $ are correct bracket sequences.

For example, "(()())", "()" are correct, while ")(" and "())" are not.

The cyclical shift of the string $ s $ of length $ n $ by $ k $ ( $ 0 \leq k < n $ ) is a string formed by a concatenation of the last $ k $ symbols of the string $ s $ with the first $ n - k $ symbols of string $ s $ . For example, the cyclical shift of string "(())()" by $ 2 $ equals "()(())".

Cyclical shifts $ i $ and $ j $ are considered different, if $ i \ne j $ .

## 说明/提示

In the first example, we can swap $ 7 $ -th and $ 8 $ -th character, obtaining a string "()()()()()". The cyclical shifts by $ 0, 2, 4, 6, 8 $ of this string form a correct bracket sequence.

In the second example, after swapping $ 5 $ -th and $ 10 $ -th character, we obtain a string ")(())()()(()". The cyclical shifts by $ 11, 7, 5, 3 $ of this string form a correct bracket sequence.

In the third example, swap of any two brackets results in $ 0 $ cyclical shifts being correct bracket sequences.

## 样例 #1

### 输入

```
10
()()())(()
```

### 输出

```
5
8 7
```

## 样例 #2

### 输入

```
12
)(()(()())()
```

### 输出

```
4
5 10
```

## 样例 #3

### 输入

```
6
)))(()
```

### 输出

```
0
1 1
```

# AI分析结果

---
# 💡 Kay的C++算法解析：The World Is Just a Programming Task (Easy Version) 深入学习指南 💡

<introduction>
  今天我们来一起分析这道关于括号序列的C++编程题。题目要求我们通过一次交换两个字符，让字符串的“美丽值”最大化——也就是尽可能多的循环移位能形成合法括号序列。这道题能帮我们巩固**枚举思想**和**括号序列的经典前缀和技巧**，一起开始吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（枚举+括号序列前缀和结论）

🗣️ **初步分析**：
> 解决这道题的关键有两点：一是**暴力枚举所有可能的交换**（因为n≤500，n²次交换完全可行）；二是**利用括号序列的经典结论快速计算美丽值**。  
> 先给大家一个“魔法结论”：当括号序列的左右括号数量相等时，**美丽值等于前缀和最小值的出现次数**！什么是前缀和？我们把'('看成+1，')'看成-1，从左到右累加的结果就是前缀和。比如序列`)()(`的前缀和是`-1,0,-1,0`，最小值是-1，出现了2次，所以美丽值就是2——对应循环移位2次能得到合法序列。  
> 为什么这个结论成立？想象一下：如果我们把前缀和最小值的位置前面的部分移到字符串末尾，剩下的部分的前缀和就不会出现负数（因为最小值已经被移走了），而整个序列的总和是0（左右括号数量相等），所以这样的移位一定合法。反之，如果移位的位置不是前缀和最小值的位置，剩下的部分一定会出现负数前缀和，无法合法。  
> 核心算法流程是：① 先检查左右括号数量是否相等（不等的话美丽值直接为0）；② 枚举所有交换对（i,j），交换后计算新字符串的前缀和最小值出现次数；③ 记录最大的美丽值和对应的交换位置。  
> 可视化设计思路：我们可以用**8位像素风**展示括号序列和前缀和的变化——比如用蓝色像素块代表'('，红色代表')'，前缀和用绿色进度条显示，最小值的位置用黄色闪烁。交换时，两个像素块会“跳”到对方的位置，伴随“叮”的音效；计算美丽值时，最小值的位置会集体闪烁，数字面板显示当前美丽值。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和实践价值等方面筛选了3份优质题解，它们的核心逻辑一致，但各有亮点，适合不同阶段的学习者参考。
</eval_intro>

**题解一：来源（作者：big_news）**
* **点评**：这份题解的思路像“直线路径”一样清晰！作者先写了`checker`函数判断左右括号数量是否相等（直接避免无效计算），再用`GetAns`函数计算前缀和最小值的次数——逻辑链完整且没有冗余。代码风格非常简洁，变量名`cnt`（当前前缀和）、`mn`（前缀和最小值）、`sum`（最小值出现次数）都很直观。特别是枚举交换时，直接用两层循环覆盖所有i和j，然后交换、计算、恢复，步骤明确。对于刚开始学枚举的同学来说，这份题解是“标准模板”级别的参考！

**题解二：来源（作者：123zbk）**
* **点评**：这份题解的亮点是**代码规范性**——比如用`#define int long long`处理可能的溢出（虽然本题n小不需要，但习惯很好），`sum`数组从1开始索引（避免边界问题）。`query`函数的逻辑和题解一完全一致，但作者在检查左右括号数量时还加了`n&1`（n为奇数直接返回0），考虑更周全。对于注重代码严谨性的同学，这份题解能帮你养成“想边界”的好习惯。

**题解三：来源（作者：skyskyCCC）**
* **点评**：这份题解的优势是**结论推导的详细性**！作者在分析里解释了“为什么前缀和最小值的次数是美丽值”——通过置换前缀和的操作，说明移位后的序列合法条件对应前缀和最小值的位置。代码里的`totle`函数不仅计算前缀和，还先判断`s[n]`是否为0（即总括号数是否相等），逻辑闭环。对于想“知其所以然”的同学，这份题解能帮你理解结论的由来，而不是死记硬背。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，大家容易卡壳的地方其实是“结论的理解”和“枚举的勇气”。结合题解的共性，我提炼了3个核心关键点：
</difficulty_intro>

1.  **关键点1：如何理解“前缀和最小值的次数=美丽值”？**
    * **分析**：这个结论是题目的“钥匙”。我们可以用“欠债”的比喻理解：前缀和就像“当前的债务”——如果前缀和是-2，说明已经欠了2个右括号；而前缀和最小值就是“最大的债务”。要让移位后的序列合法，必须把“最大的债务”部分移到末尾（相当于先还清最大的债），这样剩下的部分就不会再欠债了。而“最大的债务”出现的次数，就是有多少种方式可以移走它。
    * 💡 **学习笔记**：括号序列的很多问题都能用“前缀和+极值”解决，记住这个经典结论！

2.  **关键点2：如何处理边界条件？**
    * **分析**：如果左右括号数量不等，或者n是奇数，不管怎么交换都不可能有合法序列（因为合法序列的长度必须是偶数，且左右括号数量相等）。所有优质题解都先处理了这个边界——比如`checker`函数、`num!=n/2||n&1`判断。这一步能帮我们直接跳过无效的枚举，节省时间。
    * 💡 **学习笔记**：解题前先想“不可能的情况”，能避免做无用功！

3.  **关键点3：为什么可以暴力枚举所有交换对？**
    * **分析**：n≤500时，枚举所有i和j的组合是500×500=250000次，每次计算前缀和是O(n)=500次，总操作量是125,000,000次——这在计算机里是“眨眼间”就能完成的（计算机每秒能处理上亿次操作）。所以不要害怕“暴力”，只要时间复杂度允许，暴力是最直接的解法！
    * 💡 **学习笔记**：小数据范围下，暴力枚举是“最聪明的办法”！

### ✨ 解题技巧总结
<summary_best_practices>
通过这道题，我们能学到3个通用技巧：
</summary_best_practices>
-   **技巧A：结论优先**：遇到括号序列问题，先想“前缀和+极值”的经典结论，能快速找到突破口。
-   **技巧B：边界前置**：先处理不可能的情况（如数量不等、奇数长度），减少后续计算量。
-   **技巧C：暴力可行**：小数据范围下，直接枚举所有可能，比“想优化”更高效。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合所有优质题解的通用核心代码**，它包含了所有关键逻辑，且结构清晰：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了big_news、123zbk和skyskyCCC的题解思路，保留了最核心的逻辑，去掉了冗余部分，适合初学者理解。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    using namespace std;

    const int CN = 550;
    int n;
    char ch[CN];

    // 计算当前字符串的美丽值
    int getBeauty() {
        int cnt = 0, mn = 0;
        // 第一次遍历找前缀和最小值
        for (int i = 0; i < n; ++i) {
            cnt += (ch[i] == '(') ? 1 : -1;
            if (cnt < mn) mn = cnt;
        }
        // 第二次遍历统计最小值出现的次数
        int sum = 0;
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += (ch[i] == '(') ? 1 : -1;
            if (cnt == mn) sum++;
        }
        return sum;
    }

    // 检查左右括号数量是否相等
    bool checkValid() {
        int left = 0, right = 0;
        for (int i = 0; i < n; ++i) {
            if (ch[i] == '(') left++;
            else right++;
        }
        return left == right;
    }

    int main() {
        cin >> n >> ch;
        int maxBeauty = 0, bestI = 1, bestJ = 1;

        if (!checkValid()) {
            cout << "0\n1 1" << endl;
            return 0;
        }

        // 枚举所有交换对
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(ch[i], ch[j]);
                int current = getBeauty();
                if (current > maxBeauty) {
                    maxBeauty = current;
                    bestI = i + 1; // 题目要求输出1-based索引
                    bestJ = j + 1;
                }
                swap(ch[i], ch[j]); // 恢复原字符串
            }
        }

        cout << maxBeauty << endl;
        cout << bestI << " " << bestJ << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码分为3部分：① `checkValid`检查左右括号数量是否相等（不等直接输出0）；② `getBeauty`计算前缀和最小值的次数（美丽值）；③ `main`函数枚举所有交换对，记录最大美丽值和对应的位置。核心逻辑是“枚举+计算”，没有复杂的数据结构，非常适合初学者模仿。

---
<code_intro_selected>
接下来看3份优质题解的核心片段，体会它们的亮点：
</code_intro_selected>

**题解一（作者：big_news）**
* **亮点**：`getBeauty`函数的“两次遍历”逻辑非常清晰，没有多余的变量。
* **核心代码片段**：
    ```cpp
    int GetAns(){
        int cnt = 0, sum = 0, mn = 0;
        for(int i=0;i<n;i++){
            if(ch[i] == '(') cnt++;
                else cnt--;
            mn = min(mn, cnt);
        }
        for(int i=0;i<n;i++){
            if(ch[i] == '(') cnt++;
                else cnt--;
            if(cnt == mn) sum++;
        }
        return sum;
    }
    ```
* **代码解读**：
    > 第一次遍历用`mn`记录前缀和的最小值——比如`cnt`从0开始，每一步都更新`mn`为当前最小的`cnt`。第二次遍历重新计算前缀和，统计等于`mn`的次数——这就是美丽值。为什么要两次遍历？因为第一次遍历需要先知道最小值，第二次才能统计次数。是不是很巧妙？
* 💡 **学习笔记**：两次遍历是计算“极值出现次数”的常用方法！

**题解二（作者：123zbk）**
* **亮点**：用`sum`数组从1开始索引，避免了0索引的边界问题。
* **核心代码片段**：
    ```cpp
    int sum[maxn];
    int query() {
        int mn = 0x3f3f3f3f, res = 0;
        for(int i=1;i<=n;i++){
            sum[i] = sum[i-1] + (s[i] == '(' ? 1 : -1);
            mn = min(mn, sum[i]);
        }
        for(int i=1;i<=n;i++){
            if(sum[i] == mn) res++;
        }
        return res;
    }
    ```
* **代码解读**：
    > 这里`sum[0]`是0（默认初始值），`sum[1]`是第一个字符的前缀和，`sum[2]`是前两个的，以此类推。这样处理的好处是“前i个字符的前缀和”直接对应`sum[i]`，不需要调整索引。比如`sum[3]`就是前3个字符的和，逻辑更直观。
* 💡 **学习笔记**：数组从1开始索引，能减少边界错误！

**题解三（作者：skyskyCCC）**
* **亮点**：在`totle`函数里先判断`s[n]`是否为0，确保总括号数相等。
* **核心代码片段**：
    ```cpp
    int s[503];
    int totle(){
        for(int i=1;i<=n;i++){
            s[i] = s[i-1] + (a[i] == '(' ? 1 : -1);
        }
        if(s[n]) return 0; // 总括号数不等，美丽值为0
        int mn = *min_element(s+1, s+1+n);
        int sum = 0;
        for(int i=1;i<=n;i++){
            sum += (s[i] == mn);
        }
        return sum;
    }
    ```
* **代码解读**：
    > `s[n]`是整个序列的前缀和——如果`s[n]≠0`，说明左右括号数量不等，直接返回0。这里用了`*min_element`函数（来自`<algorithm>`头文件）快速找到前缀和的最小值，比手动遍历更简洁。对于想简化代码的同学，`min_element`是个好工具！
* 💡 **学习笔记**：STL函数能简化代码，比如`min_element`找数组最小值！

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让大家更直观地“看到”前缀和的变化和美丽值的计算，我设计了一个**8位像素风的动画演示**，风格像FC红白机的《超级马里奥》，既有复古感又能清楚展示逻辑！
</visualization_intro>

  * **动画演示主题**：像素括号探险队——帮助“括号小人”找到最多的合法移位位置！
  * **核心演示内容**：展示原字符串的前缀和变化→交换两个括号→重新计算前缀和→统计美丽值。
  * **设计思路简述**：用8位像素风是因为它简洁、有童年感，能降低学习的“距离感”；音效和闪烁效果能强化关键操作的记忆（比如交换时的“叮”声，最小值的黄色闪烁）；“关卡”设计能让学习像玩游戏一样有趣！

  * **动画帧步骤与交互关键点**：
    1.  **场景初始化（FC风格）**：
          * 屏幕左侧是**括号序列区**：每个括号用16×16的像素块表示——蓝色代表'('，红色代表')'。
          * 屏幕右侧是**数据面板**：显示当前前缀和（绿色进度条）、最小值（黄色数字）、美丽值（红色数字）。
          * 底部是**控制面板**：有“开始/暂停”“单步执行”“重置”按钮，还有速度滑块（从“慢”到“快”）。
          * 背景音是8位风格的《超级马里奥》开场音乐，轻快又熟悉！
    2.  **原字符串演示**：
          * 一个“像素指针”从左到右移动，每移动一步，括号块会闪烁，同时数据面板的前缀和进度条增长/减少，最小值数字更新。
          * 当指针走到末尾时，数据面板的美丽值数字会显示原字符串的美丽值（比如样例1的原字符串美丽值可能是2）。
    3.  **交换操作演示**：
          * 用户点击“单步执行”，屏幕会提示“选择要交换的两个括号”——用鼠标点击两个括号块，它们会“跳”到对方的位置，伴随“叮”的音效（像马里奥吃金币的声音）。
          * 交换完成后，括号序列区会显示新的字符串，数据面板清零，准备重新计算。
    4.  **新字符串计算演示**：
          * 像素指针再次从左到右移动，重新计算前缀和——进度条和最小值数字实时更新。
          * 当指针走到末尾时，数据面板的美丽值数字会闪烁（比如样例1交换后的美丽值是5），同时播放“胜利”音效（像马里奥通关的声音）。
    5.  **AI自动演示模式**：
          * 点击“AI自动演示”，动画会自动枚举所有交换对，快速展示每个交换后的美丽值变化——最优质的交换对会用“星星”标记，提醒用户注意。
    6.  **游戏式关卡设计**：
          * 将“计算美丽值”拆成3个小关卡：① 找前缀和最小值；② 统计最小值次数；③ 找到最大美丽值的交换对。完成每个关卡会弹出“过关！”的像素提示，增加成就感。

  * **旁白提示（像素气泡）**：
      * （指针移动时）“现在计算第i个字符的前缀和，进度条代表当前的和哦！”
      * （交换时）“交换这两个括号，看看新的序列能有多少合法移位！”
      * （美丽值更新时）“哇，美丽值变成5了！这是目前最大的结果～”

<visualization_conclusion>
通过这个动画，你能清楚地看到“交换→计算前缀和→统计最小值次数”的完整流程，就像玩游戏一样记住算法逻辑！下次遇到括号序列问题，你一定会想起这个“像素括号探险队”的故事～
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
这道题的核心技巧（枚举+前缀和结论）能解决很多字符串和括号的问题。我们来看看它的“迁移能力”：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 场景1：判断一个括号序列是否能通过循环移位变成合法序列（只需计算前缀和最小值的次数是否≥1）；
      * 场景2：统计一个字符串的所有循环移位中，满足某种条件（如前缀和非负）的数量；
      * 场景3：通过一次修改（交换/替换）让字符串满足某个条件（如本题的美丽值最大化）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1739** - 表达式括号匹配
          * 🗣️ **推荐理由**：这是括号匹配的基础题，能帮你巩固“栈”或“前缀和”的应用，是本题的前置练习！
    2.  **洛谷 P2698** - 括号序列
          * 🗣️ **推荐理由**：这道题需要你用前缀和判断括号序列的合法性，还需要统计合法子序列的数量，是本题的进阶练习！
    3.  **洛谷 P3375** - 最长回文子串
          * 🗣️ **推荐理由**：虽然是回文问题，但同样需要“枚举+判断”的思路，能帮你巩固枚举的技巧！
    4.  **洛谷 P1957** - 口算练习题
          * 🗣️ **推荐理由**：这道题需要处理字符串的替换和计算，能帮你练习“枚举所有可能的修改”的思路！

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中几位作者的经验很值得借鉴，我选了两条最有用的：
</insights_intro>

> **参考经验 (来自 big_news)**：“n很小，显然可以枚举方案。剩下的问题是怎么找循环匹配个数——记住前缀和最小值的结论就好。”
>
> **点评**：这位作者的经验点出了本题的“核心”——小数据范围下枚举是可行的，而结论是解题的关键。很多时候，记住经典结论能让你跳过“想破头”的推导，直接解决问题！

> **参考经验 (来自 skyskyCCC)**：“我在写代码时，一开始忘记判断s[n]是否为0，结果样例3输出错了。后来加上这个判断就对了。”
>
> **点评**：这个错误很典型！边界条件（如总括号数不等）是最容易忽略的，但也是最致命的。写代码时，一定要先想“不可能的情况”，避免低级错误！

---

<conclusion>
本次关于“The World Is Just a Programming Task (Easy Version)”的分析就到这里啦！这道题让我们学会了“枚举+前缀和结论”的组合拳，还知道了小数据范围下暴力的力量。记住：编程不是“越复杂越好”，而是“能解决问题的方法就是好方法”！下次遇到括号序列问题，不妨先想想“前缀和最小值”，说不定能快速找到答案～ 💪
</conclusion>

---

---
处理用时：128.87秒