# 题目信息

# Add Modulo 10

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \dots, a_n $

You can apply the following operation an arbitrary number of times:

- select an index $ i $ ( $ 1 \le i \le n $ ) and replace the value of the element $ a_i $ with the value $ a_i + (a_i \bmod 10) $ , where $ a_i \bmod 10 $ is the remainder of the integer dividing $ a_i $ by $ 10 $ .

For a single index (value $ i $ ), this operation can be applied multiple times. If the operation is applied repeatedly to the same index, then the current value of $ a_i $ is taken into account each time. For example, if $ a_i=47 $ then after the first operation we get $ a_i=47+7=54 $ , and after the second operation we get $ a_i=54+4=58 $ .

Check if it is possible to make all array elements equal by applying multiple (possibly zero) operations.

For example, you have an array $ [6, 11] $ .

- Let's apply this operation to the first element of the array. Let's replace $ a_1 = 6 $ with $ a_1 + (a_1 \bmod 10) = 6 + (6 \bmod 10) = 6 + 6 = 12 $ . We get the array $ [12, 11] $ .
- Then apply this operation to the second element of the array. Let's replace $ a_2 = 11 $ with $ a_2 + (a_2 \bmod 10) = 11 + (11 \bmod 10) = 11 + 1 = 12 $ . We get the array $ [12, 12] $ .

Thus, by applying $ 2 $ operations, you can make all elements of an array equal.

## 说明/提示

The first test case is clarified above.

In the second test case, it is impossible to make all array elements equal.

In the third test case, you need to apply this operation once to all elements equal to $ 5 $ .

In the fourth test case, you need to apply this operation to all elements until they become equal to $ 8 $ .

In the fifth test case, it is impossible to make all array elements equal.

In the sixth test case, you need to apply this operation to all elements until they become equal to $ 102 $ .

## 样例 #1

### 输入

```
10
2
6 11
3
2 18 22
5
5 10 5 10 5
4
1 2 4 8
2
4 5
3
93 96 102
2
40 6
2
50 30
2
22 44
2
1 5```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
No
Yes
No```

# AI分析结果


# 💡 Kay的C++算法解析：Add Modulo 10 深入学习指南 💡

<introduction>
大家好！我是Kay，今天我们一起挑战Codeforces题目"Add Modulo 10"。这道题看似简单，却蕴含了精妙的数学规律和分类思想。通过本指南，你将掌握数字变换的奥秘，学会如何通过操作使数组中所有元素相等。准备好了吗？让我们开始探索吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学规律`与`分类讨论`

🗣️ **初步分析**：
> 这道题就像一场数字变形记！想象每个数字都是探险家，在"数字环形跑道"上奔跑。个位数字决定了它们的奔跑路线：
> - **环形跑道（2→4→8→6→2）**：大多数数字（1,2,3,4,6,7,8,9）会进入这个循环，每跑完一圈（4步）增加20
> - **死胡同（0/5）**：这些数字只能移动一次就停止
> 
> 解题关键在于：
> 1. 先处理奇数（都变偶数）
> 2. 检查0/5结尾的数字（必须全部相同）
> 3. 非0/5的数字统一到环形跑道（模20判断）
>
> 可视化设计思路：
> - 像素风格：8-bit复古游戏界面，数字显示为像素方块
> - 关键动画：数字在环形跑道上移动时播放"叮"音效，每完成一圈方块上升20像素
> - 死胡同区域：红色停止标志，播放"哔"错误音效
> - 控制面板：调速滑块控制移动速度，"AI演示"模式自动完成解题

---

## 2. 精选优质题解参考

<eval_intro>
我们从思路清晰度、代码规范性和算法效率等维度，精选了三条优质题解（评分≥4★）。这些解法都抓住了数字变换的规律，但实现方式各有特色：

**题解一（作者：EXODUS）**
* **点评**：这份题解思路非常严谨，像一位经验丰富的侦探逐步揭开数字变换的奥秘。亮点在于用桶记录循环中所有可能位置（模20值），确保无遗漏。代码中`t[]`数组的设计巧妙，但分支判断稍多。作者用图示辅助说明（可惜链接失效），若配上动画将更直观。边界处理完整，可直接用于竞赛。

**题解二（作者：I_am_Accepted）**
* **点评**：解法如瑞士军刀般简洁锋利！核心函数`calc()`将数字统一为0或2结尾，`kind()`函数通过十位奇偶性分类。代码风格干净利落，变量名清晰（如`cnt`计数），特别适合竞赛中快速实现。但需注意非0/5的数需模20后判断相等。作者提到"这玩意有算法吗"的顿悟，提醒我们有时规律就在眼前。

**题解三（作者：Dry_ice）**
* **点评**：采用"最大值引导"策略，像登山队长带领队员登顶。排序后对最大值尝试4次循环操作，检查其他数能否达到当前值。亮点在`check()`函数验证差值是否合法（0/2/6/14），思路直观易懂。虽然效率稍低（O(4n)），但n较小时表现优秀。作者博客中的调试经验值得借鉴：多组测试验证边界。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题时，你会遇到三个关键难点。别担心，Kay为你准备了应对策略：

1.  **数字的"双重人格"（0/5 vs 循环数）**
    * **分析**：0/5像"宅男"不愿移动，循环数像"跑者"永不停歇。二者无法共存！优质题解都先检查是否混有这两类数字。
    * 💡 **学习笔记**：发现0/5立即检查其他数字身份，非我族类直接判No！

2.  **循环中的"等价转换"**
    * **分析**：跑者在环形跑道每圈+20，本质是模20等价。但起点不同（2/4/8/6）需统一。EXODUS用桶记录所有可能位置，I_am_Accepted则统一成2再模20。
    * 💡 **学习笔记**：模20是循环数字的通用语言，统一语言才能交流！

3.  **边界值处理陷阱**
    * **分析**：全相同数组、单个元素数组、全0数组等边界易漏。Dry_ice在题解中强调："多组测试验证边界"。
    * 💡 **学习笔记**：边界测试是优秀ACMer的护身符！

### ✨ 解题技巧总结
<summary_best_practices>
通关秘籍在此：
</summary_best_practices>
-   **技巧1：数字变形三步法** 
    1. 奇数→偶数（+个位）
    2. 0/5→统一终点（5→0）
    3. 循环数→模20等价类

-   **技巧2：分身桶策略** 
    当数字在环形跑道奔跑时，用桶记录它可能出现的所有位置（EXODUS方案），避免漏判

-   **技巧3：最大值引导法** 
    尝试让最大值走完循环的4步，检查其他数字能否跟上（Dry_ice方案）

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个完整解决方案，融合了优质题解的精华：

**本题通用核心C++实现参考**
* **说明**：综合EXODUS的桶计数和I_am_Accepted的分类处理，优化边界检查
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<long long> a(n);
        bool allEqual = true;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i > 0 && a[i] != a[i-1]) allEqual = false;
        }
        if (allEqual) { cout << "Yes\n"; continue; }

        bool hasZeroFive = false;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 1) a[i] += a[i] % 10; // 奇数变偶数
            if (a[i] % 10 == 0 || a[i] % 10 == 5) hasZeroFive = true;
        }

        // 0/5类检查
        if (hasZeroFive) {
            for (int i = 0; i < n; i++) 
                if (a[i] % 10 == 5) a[i] += 5; // 5变0
            
            bool valid = true;
            for (int i = 1; i < n; i++) 
                if (a[i] != a[0]) { valid = false; break; }
            
            cout << (valid ? "Yes" : "No") << '\n';
            continue;
        }

        // 循环数统一模20
        for (int i = 0; i < n; i++) {
            while (a[i] % 10 != 2) a[i] += a[i] % 10; // 统一成2结尾
            a[i] %= 20;
        }

        bool valid = true;
        for (int i = 1; i < n; i++) 
            if (a[i] != a[0]) { valid = false; break; }
        
        cout << (valid ? "Yes" : "No") << '\n';
    }
    return 0;
}
```
* **代码解读概要**：
  1. 快速检查全相等情况
  2. 处理奇数：+个位变偶数
  3. 0/5类：统一为0后判全等
  4. 循环类：统一为2结尾→模20→判全等

---
<code_intro_selected>
现在，让我们深入欣赏各优质题解的精华片段：

**题解一（EXODUS）**
* **亮点**：桶记录循环所有位置，确保无漏判
* **核心代码片段**：
```cpp
int t[44] = {0}; // 桶数组
for (int i = 1; i <= n; i++) {
    if (a[i] % 10 == 2) {
        t[a[i] % 20]++;
        t[(a[i] + 2) % 20]++;
        t[(a[i] + 6) % 20]++;
        t[(a[i] + 14) % 20]++;
    } // 类似处理其他个位...
}
for (int i = 0; i < 40; i++) 
    if (t[i] == n) { /* 成功 */ }
```
* **代码解读**：
  > 这段代码像撒网捕鱼，记录每个数字在循环中可能到达的4个位置（当前/下一步/再下一步）。`t[]`数组下标对应模20值，值表示能到达该位置的数字数。最终检查是否有桶装满所有数字。
  > 为什么是+2/+6/+14？对应循环中的累积增量：0步(0), 1步(2), 2步(2+4=6), 3步(2+4+8=14)
* 💡 **学习笔记**：桶计数法空间换时间，避免循环尝试

**题解二（I_am_Accepted）**
* **亮点**：函数化封装，代码如诗
* **核心代码片段**：
```cpp
void calc(int &x) { 
    while (x % 10 != 2 && x % 10 != 0) 
        x += x % 10; 
}
// 主逻辑
for (int i = 1; i <= n; i++) calc(a[i]);
if (cnt_5) { /* 处理0/5 */ }
else {
    for (int i = 1; i <= n; i++) a[i] %= 20;
    // 判断相等
}
```
* **代码解读**：
  > `calc()`函数是变形引擎：不断操作直到数字进入稳定状态（0或循环起点2）。主逻辑先统一变形，再模20判断。简洁如"把大象放冰箱分三步"。
  > 注意：实际需确保非0/5类才能模20（代码中`cnt_5`判断）
* 💡 **学习笔记**：功能封装让代码清晰如散文

**题解三（Dry_ice）**
* **亮点**：最大值循环尝试，步步为营
* **核心代码片段**：
```cpp
sort(a, a + n); // 排序
for (int i = 0; i < 4; i++) { // 尝试4步
    a[n-1] += rep[i]; // rep[i] = {0,2,4,8}
    bool valid = true;
    for (int j = 0; j < n-1; j++) {
        if (!check(a[n-1] - a[j])) // 检查差值
            { valid = false; break; }
    }
    if (valid) break;
}
```
* **代码解读**：
  > 让最大值走起来！`rep`数组存储循环各步的增量。对每个位置，检查其他数字能否通过若干操作达到当前最大值（差值需为0/2/6/14）。就像调整领跑者步伐让队伍整齐。
  > `check()`函数：差值为0(直接相等)/2(1步)/6(2步)/14(3步)时合法
* 💡 **学习笔记**：排序+尝试法直观，适合快速验证

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
想象一个8-bit风格的数学世界！数字们将在像素迷宫中完成变形之旅：

**动画设计**：
* **场景**：16x16像素网格，数字显示为8x8像素方块
* **角色**：
  - 蓝色方块：循环数字（初始个位1,3,7,9）
  - 绿色方块：循环数字（初始个位2,4,6,8）
  - 红色方块：0/5类数字
* **音效**：Chiptune风格（FC游戏音效）
  - 移动："叮"（短促）
  - 循环完成："当啷"（上升音阶）
  - 错误："哔——"

**关键帧演示**：
1. **初始化**：显示数字阵列（如[13, 7, 5]）
   ```plaintext
   +-----+-----+-----+
   | 13  |  7  |  5  |
   +-----+-----+-----+
   ```

2. **奇数变形**：蓝方块闪烁→+个位→变绿（13→16，7→14）
   ```plaintext
   13 -> 16（播放"叮"）
   7 -> 14（播放"叮"）
   ```

3. **0/5处理**：红方块闪烁→5→10（变红并停止）
   ```plaintext
   5 -> 10（播放"哔"）
   ```

4. **循环移动**：绿方块进入环形跑道
   ```plaintext
   16位于6号位 → 移动至2号位：
   16 → 22（+6，播放"当啷"）
   ```

5. **模20等价**：显示模20值（22%20=2，14%20=14）
   ```plaintext
   值显示：22→2，14→14
   ```

6. **判断结果**：值不同→显示红色"No"（播放错误音效）

**交互控制**：
- 步进/暂停/重置按钮
- 速度滑块（1x～10x）
- "AI演示"模式：自动完成解题路径

**可视化意义**：
> 通过像素动画直观展示数字的"生命轨迹"：蓝色数字蜕变为绿色进入循环，红色数字停滞不前。环形跑道上的位置关系清晰展现模20等价原理，帮助理解抽象数学概念。

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握数字变换规律后，试试这些相似问题巩固技能：

1.  **P2921 魔法照片**（数位操作+模运算）
    > 推荐理由：同样研究数位操作后的数学规律，强化模运算应用

2.  **P1143 进制转换**（数位循环特性）
    > 推荐理由：考察不同进制下的数位特性，拓展数字思维

3.  **P1014 Cantor表**（数字规律+分类）
    > 推荐理由：训练找规律和分类讨论能力，完美衔接本题

**洛谷推荐**：
1.  **P2921** - 魔法照片  
    🗣️ **Kay说**：巩固模运算技巧，就像给数字施魔法！

2.  **P1143** - 进制转换  
    🗣️ **Kay说**：在不同进制中发现循环规律，拓展思维维度

3.  **P1014** - Cantor表  
    🗣️ **Kay说**：训练模式识别能力，培养分类讨论直觉

---

## 7. 学习心得与经验分享

<insights_intro>
题解中藏宝无数！Kay为你提炼黄金经验：

> **EXODUS的调试经验**  
> "通过画图找规律时，我发现奇数操作一次的必要性"  
> → Kay点评：将抽象规律可视化是理解的关键，手绘或动画都能帮大忙！

> **Dry_ice的避坑指南**  
> "多组测试验证边界：全相同数组、单个元素等"  
> → Kay点评：边界是BUG的温床，测试用例要像侦探查案般全面

> **I_am_Accepted的顿悟时刻**  
> "这玩意有算法吗？—— 规律就在眼前！"  
> → Kay点评：简单问题可能隐藏精妙规律，保持开放思维

---

<conclusion>
今天我们揭开了Add Modulo 10的数学奥秘！记住Kay的三步口诀："奇变偶，0/5判，循环模20"。数字世界如同像素游戏，规律就藏在循环与分类中。多练习推荐的相似问题，你将成为数字变形大师！下次挑战见！🎮✨

—— 你的算法向导 Kay
</conclusion>
```

---
处理用时：258.61秒