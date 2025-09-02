# 题目信息

# Anonymous Informant

## 题目描述

You are given an array $ b_1, b_2, \ldots, b_n $ .

An anonymous informant has told you that the array $ b $ was obtained as follows: initially, there existed an array $ a_1, a_2, \ldots, a_n $ , after which the following two-component operation was performed $ k $ times:

1. A fixed point $ ^{\dagger} $ $ x $ of the array $ a $ was chosen.
2. Then, the array $ a $ was cyclically shifted to the left $ ^{\ddagger} $ exactly $ x $ times.

As a result of $ k $ such operations, the array $ b_1, b_2, \ldots, b_n $ was obtained. You want to check if the words of the anonymous informant can be true or if they are guaranteed to be false.

 $ ^{\dagger} $ A number $ x $ is called a fixed point of the array $ a_1, a_2, \ldots, a_n $ if $ 1 \leq x \leq n $ and $ a_x = x $ .

 $ ^{\ddagger} $ A cyclic left shift of the array $ a_1, a_2, \ldots, a_n $ is the array $ a_2, \ldots, a_n, a_1 $ .

## 说明/提示

In the first test case, the array $ a $ could be equal to $ [3, 2, 3, 4, 3] $ . In the first operation, a fixed point $ x = 2 $ was chosen, and after $ 2 $ left shifts, the array became $ [3, 4, 3, 3, 2] $ . In the second operation, a fixed point $ x = 3 $ was chosen, and after $ 3 $ left shifts, the array became $ [3, 2, 3, 4, 3] $ . In the third operation, a fixed point $ x = 3 $ was chosen again, and after $ 3 $ left shifts, the array became $ [4, 3, 3, 2, 3] $ , which is equal to the array $ b $ .

In the second test case, the array $ a $ could be equal to $ [7, 2, 1] $ . After the operation with a fixed point $ x = 2 $ , the array became $ [1, 7, 2] $ . Then, after the operation with a fixed point $ x = 1 $ , the array returned to its initial state $ [7, 2, 1] $ . These same $ 2 $ operations (with $ x = 2 $ , and $ x = 1 $ ) were repeated $ 49 $ times. So, after $ 100 $ operations, the array returned to $ [7, 2, 1] $ .

In the third test case, it can be shown that there is no solution.

## 样例 #1

### 输入

```
6
5 3
4 3 3 2 3
3 100
7 2 1
5 5
6 1 1 1 1
1 1000000000
1
8 48
9 10 11 12 13 14 15 8
2 1
1 42```

### 输出

```
Yes
Yes
No
Yes
Yes
No```

# AI分析结果

---
# 💡 Kay的C++算法解析：Anonymous Informant 深入学习指南 💡

<introduction>
今天我们来一起分析“Anonymous Informant”这道C++编程题。这道题的核心是**逆向思维**和**模拟优化**，需要我们从结果倒推过程，还得巧妙处理“大次数操作”的问题。本指南会帮你理清思路，掌握关键技巧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟 (结合逆向思维与环检测)`

🗣️ **初步分析**：
解决这道题的关键，在于**把“正向操作”反过来想**——就像玩迷宫时从出口倒着走回入口！题目里说，正向操作是选一个“不动点x”（即a_x=x），然后把数组左移x次。那逆操作呢？其实每次正向操作后，**原来的x（不动点）会跑到数组的最后一位**！比如正向左移x次，原来的第x位元素会被移到最后一位。所以逆操作时，我们只需要看当前数组的**最后一位**（它就是之前操作的x），然后把数组“右移x次”（或者说“回退x步”）就行啦~

- **核心思路**：从结果数组b出发，逆向模拟k次操作。每次看当前“最后一位”的数y，如果y>n（不能作为不动点），直接输出No；否则回退y步，更新“最后一位”的位置。
- **大k的处理**：因为数组只有n个位置，最多模拟n次就会出现**循环**（比如某个位置重复出现）。如果出现循环，说明可以无限操作下去，直接输出Yes！
- **可视化设计思路**：我们用8位像素风展示数组，用高亮块标记当前“最后一位”的位置。每次逆操作时，高亮块会“跳回”y步，同时用不同颜色标记已访问的位置（避免循环）。如果跳回时y>n，屏幕会闪红并播放错误音效~

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和实践价值三个方面筛选了2份优质题解，帮你快速掌握核心技巧！
</eval_intro>

**题解一：(来源：EternityLove)**
* **点评**：这份题解的思路太“通透”了！作者直接点出“逆操作只需要跟踪最后一位的位置”，完全不用真的移动数组——用一个`now`变量标记当前最后一位在原数组中的索引（从0开始），每次用模运算`(now - a[now] + n) % n`更新位置，既高效又不容易错。而且用`flag`数组标记已访问的位置，一旦重复就说明有循环，直接输出Yes。代码风格超简洁，变量名`now`、`flag`一看就懂，边界处理（比如`+n`再取模）也很严谨，特别适合新手学习！

**题解二：(来源：fish_shit)**
* **点评**：这份题解的思路和题解一一致，但数组是从1开始索引的（更符合常规思维）。作者用`pos`变量从n（最后一位）开始，每次`pos -= b[pos]`，如果`pos<1`就调整回数组末尾。而且作者直接把操作次数限制为`min(k, n)`，避免了大k的超时问题。代码虽然比题解一稍繁琐，但胜在直观，适合刚接触“数组索引”的同学理解~

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的“坑”主要在**逆向思维的转换**和**大k的优化**。结合优质题解，我帮你提炼了3个核心关键点：
</difficulty_intro>

1.  **关键点1：为什么要逆向操作？**
    * **分析**：正向操作时，数组a每次都会变化，我们无法跟踪“下一次选哪个x”。但逆向操作时，**每次操作的x就是当前数组的最后一位**（正向操作的结果），这是题目隐藏的“密码”！比如正向左移x次后，原来的x位置元素会到最后一位——逆推时，最后一位的数就是之前的x，所以回退x步就能得到上一次的数组。
    * 💡 **学习笔记**：逆向思维是解决“操作序列”问题的常用技巧，尤其是当正向操作无法跟踪时！

2.  **关键点2：如何处理大k（比如1e9次）？**
    * **分析**：数组只有n个位置，最多模拟n次就会出现**循环**（比如`now`变量重复出现）。如果出现循环，说明可以无限操作下去，直接输出Yes。这样就把O(k)的时间复杂度降到了O(n)，完美解决超时问题！
    * 💡 **学习笔记**：遇到“大次数操作”，先想“是否有循环”——循环意味着可以无限重复，不需要模拟所有次数！

3.  **关键点3：如何正确计算回退的位置？**
    * **分析**：回退x步时，要避免位置变成负数。比如题解一用`(now - a[now] + n) % n`：`now - a[now]`是回退x步后的位置，`+n`是为了防止负数，再`%n`确保位置在0~n-1之间。题解二用`pos -= b[pos]`，如果`pos<1`就调整为`n - (1 - pos) + 1`，其实和模运算的效果一样~
    * 💡 **学习笔记**：处理数组循环问题，模运算（%）是“神器”，能帮你快速调整位置！

### ✨ 解题技巧总结
- **技巧A：逆向思维**：遇到“正向操作难跟踪”的问题，试试从结果倒推！
- **技巧B：环检测**：大次数操作先找循环，避免超时！
- **技巧C：模运算优化**：处理循环位置时，用模运算避免负数和越界！

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用核心实现**——综合了题解一的简洁和题解二的直观，帮你快速掌握整体框架！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自题解一的优化版，用0-based索引，逻辑清晰，效率超高！
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    using namespace std;

    const int N = 500010;
    int a[N], flag[N]; // flag标记是否访问过该位置

    void solve() {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        memset(flag, 0, sizeof(flag)); // 初始化标记数组
        int now = n - 1; // 初始最后一位的位置（0-based）
        while (k > 0 && !flag[now]) {
            flag[now] = 1; // 标记当前位置已访问
            if (a[now] > n) { // 不能作为不动点，直接No
                cout << "No" << endl;
                return;
            }
            now = (now - a[now] + n) % n; // 回退a[now]步，模运算调整位置
            k--;
        }
        cout << "Yes" << endl; // 完成k次或出现循环
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        int T;
        cin >> T;
        while (T--) {
            solve();
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码分为3部分：1. 读取输入（数组a、n、k）；2. 初始化标记数组`flag`和当前位置`now`（初始为最后一位）；3. 循环模拟逆操作：标记当前位置→检查是否合法→更新位置→减少k。如果循环结束还没返回No，说明可行！

---
<code_intro_selected>
接下来看**题解一的核心片段**——最能体现“逆操作+环检测”的精髓！
</code_intro_selected>

**题解一：(来源：EternityLove)**
* **亮点**：用`now`变量跟踪最后一位的位置，完全不用移动数组，效率O(n)！
* **核心代码片段**：
    ```cpp
    int now = n - 1;
    while (k > 0 && !flag[now]) {
        flag[now] = 1;
        if (a[now] > n) {
            cout << "No" << endl;
            return;
        }
        now = (now - a[now] + n) % n;
        k--;
    }
    ```
* **代码解读**：
    > 1. `now = n - 1`：初始时，`now`指向数组最后一位（0-based）。
    > 2. `while (k > 0 && !flag[now])`：只要还有操作次数，且当前位置没被访问过（没出现循环），就继续。
    > 3. `flag[now] = 1`：标记当前位置已访问，防止循环。
    > 4. `if (a[now] > n)`：如果当前最后一位的数大于n，说明不能作为不动点（因为x必须≤n），直接输出No。
    > 5. `now = (now - a[now] + n) % n`：回退a[now]步！比如now是5（n=6），a[now]是2，那么5-2=3，加上6再模6还是3——正确回退2步。
    > 6. `k--`：操作次数减1。
* 💡 **学习笔记**：用“位置指针”代替“移动数组”，是模拟题优化的关键！

**题解二：(来源：fish_shit)**
* **亮点**：用1-based索引，更符合常规思维，处理位置的方式直观！
* **核心代码片段**：
    ```cpp
    pos = n;
    k = min(k, n); // 最多操作n次
    for (int i = 1; i <= k; i++) {
        if (vis[pos]) { cout << "Yes\n"; break; }
        vis[pos] = 1;
        if (b[pos] > n) { cout << "No\n"; break; }
        pos -= b[pos];
        if (pos < 1) pos = n - (1 - pos) + 1;
    }
    ```
* **代码解读**：
    > 1. `pos = n`：初始时，pos指向数组最后一位（1-based）。
    > 2. `k = min(k, n)`：直接限制操作次数为n次，避免超时。
    > 3. `pos -= b[pos]`：回退b[pos]步，比如pos是5，b[pos]是2，pos变成3。
    > 4. `if (pos < 1)`：如果pos小于1，调整到数组末尾——比如pos是-1，那么1-pos=2，pos变成n-2+1=n-1。
* 💡 **学习笔记**：1-based索引的位置调整，可以用“补全法”（比如pos<1时，用n减去超出的部分）！

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地“看”到逆操作的过程，我设计了一个**8位像素风的动画**——像玩FC游戏一样学算法！
</visualization_intro>

  * **动画演示主题**：像素探险家“小K”在数组迷宫中“倒着走”，寻找初始数组的痕迹~
  * **核心演示内容**：展示逆操作的每一步——高亮当前最后一位的位置，回退时播放“滴”的音效，出现循环时播放“叮”的音效，出错时播放“ buzz”的音效。
  * **设计思路简述**：用FC风格的像素块代表数组元素，高亮块代表当前最后一位的位置。这样你能清晰看到“位置怎么变”“什么时候出现循环”，游戏化的音效能强化你的记忆！

  * **动画帧步骤与交互关键点**：
    1. **场景初始化**：
       - 屏幕显示一个8位像素风的数组（比如5个像素块，颜色分别是浅蓝、浅绿、浅黄、浅红、浅紫）。
       - 右下角有控制面板：开始/暂停按钮、单步按钮、速度滑块、重置按钮。
       - 播放轻松的8位BGM（比如《超级马里奥》的背景音）。
    2. **算法启动**：
       - 初始时，最后一位的像素块（比如第5个）会闪烁红色（高亮），旁边显示“当前最后一位：a[4] = 3”（假设n=5）。
    3. **逆操作步骤**：
       - 点击“单步”按钮：高亮块会“跳回”3步（比如从第5个跳到第2个），同时播放“滴”的音效。
       - 跳回后的位置会被标记为绿色（已访问），旁边显示“回退3步→新位置：a[1] = 2”。
       - 如果跳回时a[now] > n（比如a[now]=6，n=5），屏幕会闪红，播放“ buzz”的音效，同时显示“错误：x=6>5，无法作为不动点！”。
    4. **循环检测**：
       - 如果高亮块跳到已访问的位置（比如第2个已经是绿色），屏幕会闪黄，播放“叮”的音效，同时显示“发现循环！可以无限操作，输出Yes！”。
    5. **目标达成**：
       - 如果完成k次操作（比如k=3），屏幕会显示“完成3次逆操作，输出Yes！”，并播放胜利音效（比如《魂斗罗》的通关音）。

  * **旁白提示**：
    - （初始时）“小K要从最后一位倒着走啦！当前最后一位是a[4]，值是3~”
    - （跳回时）“回退3步！小K从第5个跳到第2个啦~”
    - （循环时）“哦，这里已经走过啦！说明有循环，可以无限走下去~”

<visualization_conclusion>
通过这个像素动画，你能“亲眼看到”逆操作的每一步，再也不用死记硬背公式啦！赶紧试试吧~
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了“逆向模拟+环检测”的技巧后，你可以试试以下题目，巩固所学！
</similar_problems_intro>

  * **通用思路迁移**：
    - 逆向思维可以解决很多“操作序列”问题，比如“字符串反转操作的逆操作”“数组旋转的逆操作”。
    - 环检测可以解决“大次数操作”问题，比如“计算经过1e9次操作后的数组状态”。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1028 数的计算**
          * 🗣️ **推荐理由**：这道题需要用递归+记忆化，和“环检测”一样，都是避免重复计算的技巧！
    2.  **洛谷 P2669 金币**
          * 🗣️ **推荐理由**：这道题需要模拟“每天得到的金币数”，大次数时也需要找循环，和本题的优化思路一样！
    3.  **洛谷 P1596 湖计数**
          * 🗣️ **推荐理由**：这道题需要用DFS检测连通性，和“环检测”一样，都是遍历所有可能的状态！

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解里有两个超有用的经验，帮你少踩坑！
</insights_intro>

> **参考经验 (来自 EternityLove)**：“我们每次操作不需要去移动数组，而只需要修改最后一个数的指针位置即可。”
>
> **点评**：这是模拟题的“黄金技巧”！移动数组需要O(n)时间，而修改指针只需要O(1)——比如本题n是5e5，移动数组会超时，但指针操作能轻松通过！

> **参考经验 (来自 fish_shit)**：“我们倒着去操作时最多操作n和k中较小者次。”
>
> **点评**：这是处理大k的关键！比如k是1e9，操作n次就够了——因为数组只有n个位置，最多n次就会出现循环！

---

<conclusion>
本次关于“Anonymous Informant”的分析就到这里啦！记住：**逆向思维找规律，环检测避超时，模运算调位置**——这三个技巧能帮你解决很多模拟题！下次我们再一起探索新的算法挑战~ 💪
</conclusion>

---

---
处理用时：131.50秒