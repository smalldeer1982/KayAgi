# 题目信息

# Multicolored Markers

## 题目描述

There is an infinite board of square tiles. Initially all tiles are white.

Vova has a red marker and a blue marker. Red marker can color $ a $ tiles. Blue marker can color $ b $ tiles. If some tile isn't white then you can't use marker of any color on it. Each marker must be drained completely, so at the end there should be exactly $ a $ red tiles and exactly $ b $ blue tiles across the board.

Vova wants to color such a set of tiles that:

- they would form a rectangle, consisting of exactly $ a+b $ colored tiles;
- all tiles of at least one color would also form a rectangle.

Here are some examples of correct colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/4e60c629e360885141e5179d3d4cdaf35671b392.png)Here are some examples of incorrect colorings:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1029F/8bb11d3a5c5094b0326713ae6edbddbecf3531f0.png)Among all correct colorings Vova wants to choose the one with the minimal perimeter. What is the minimal perimeter Vova can obtain?

It is guaranteed that there exists at least one correct coloring.

## 说明/提示

The first four examples correspond to the first picture of the statement.

Note that for there exist multiple correct colorings for all of the examples.

In the first example you can also make a rectangle with sides $ 1 $ and $ 8 $ , though its perimeter will be $ 18 $ which is greater than $ 8 $ .

In the second example you can make the same resulting rectangle with sides $ 3 $ and $ 4 $ , but red tiles will form the rectangle with sides $ 1 $ and $ 3 $ and blue tiles will form the rectangle with sides $ 3 $ and $ 3 $ .

## 样例 #1

### 输入

```
4 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 9
```

### 输出

```
14
```

## 样例 #3

### 输入

```
9 3
```

### 输出

```
14
```

## 样例 #4

### 输入

```
3 6
```

### 输出

```
12
```

## 样例 #5

### 输入

```
506 2708
```

### 输出

```
3218
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Multicolored Markers 深入学习指南 💡

<introduction>
今天我们来一起分析“Multicolored Markers”这道题。这道题需要我们找到用a个红色和b个蓝色方块组成的矩形的最小周长，且至少一种颜色的方块也能形成矩形。通过本指南，你将掌握如何高效枚举可能的矩形边长，并验证条件，最终找到最优解。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：枚举与数学判断结合的应用

🗣️ **初步分析**：
解决这道题的关键在于枚举所有可能的大矩形（由a+b个方块组成）的边长，并验证其中是否至少有一种颜色的方块能形成子矩形。  
简单来说，枚举就像“试穿衣服”——我们需要尝试不同的“尺寸”（大矩形的边长），找到最合身（周长最小）且满足条件（包含子矩形）的那一套。  

核心思路是：  
- 大矩形的面积为a+b，其边长i和j（i≤j）需满足i*j = a+b。  
- 从i=√(a+b)开始向下枚举（因为i越接近j，周长越小），找到第一个满足条件的i。  
- 条件验证：对于当前i，检查是否存在红色或蓝色方块的因数分解（如红色方块数a可分解为x*y，其中x≤i且y≤j=a+b/i）。  

可视化设计思路：  
用8位像素风格的网格展示大矩形，每个像素块代表一个方块。枚举i时，动态调整网格的宽i和高j=a+b/i。当找到满足条件的i时，用不同颜色高亮红色或蓝色的子矩形（如红色子矩形用红色边框闪烁），并播放“叮”的音效提示。控制面板支持单步/自动播放，可观察枚举过程。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法效率等，我筛选出以下优质题解：
</eval_intro>

**题解一：作者Siyuan**  
* **点评**：此题解思路清晰，代码简洁高效。作者利用枚举大矩形的边长i（从√(a+b)向下枚举），并预处理颜色方块的因数，快速验证条件。代码中通过vector存储因数，并用指针优化查找，时间复杂度为O(√a)，适合处理大数据范围。变量命名简洁（如tot表示a+b），边界处理严谨（如tot%i==0的判断），是竞赛中典型的高效解法。

**题解二：作者Bring**  
* **点评**：此题解优化了枚举过程，通过维护当前最大的因数（f和g），避免重复计算。代码中使用Frn_宏实现反向枚举，逻辑紧凑。特别是利用min(f,i)和while循环快速找到当前i下的最大因数，减少了冗余操作，时间复杂度接近O(√c)（c=a+b），适合追求效率的学习者参考。

**题解三：作者BLUESKY007**  
* **点评**：此题解逻辑直白，适合初学者理解。通过双重循环分别检查红色和蓝色方块的因数，虽然时间复杂度稍高（O(√c * √a)），但代码结构清晰（如check函数分离验证逻辑），变量命名直观（如u表示大矩形的宽，v表示高），适合作为入门学习的示例。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的核心难点在于如何高效枚举和验证。结合优质题解，我们提炼以下关键点：
</difficulty_intro>

1.  **关键点1：如何选择枚举顺序？**  
    * **分析**：大矩形的周长为2*(i+j)，当i和j越接近时周长越小。因此，应从i=√(a+b)开始向下枚举，找到第一个满足条件的i即可停止（因为后续的i会更小，周长更大）。  
    * 💡 **学习笔记**：枚举顺序的选择直接影响效率，优先尝试更优解（如更接近√(a+b)的i）能快速找到答案。

2.  **关键点2：如何快速验证颜色子矩形？**  
    * **分析**：颜色子矩形的条件是存在x≤i且y≤j（j=a+b/i），使得x*y等于颜色方块数（a或b）。优质题解通过预处理因数或维护当前最大因数（如Bring的f和g），避免重复计算，将验证时间优化到O(1)。  
    * 💡 **学习笔记**：预处理或维护状态（如当前最大因数）是优化枚举类问题的常用技巧。

3.  **关键点3：如何处理大数据范围？**  
    * **分析**：题目中a和b可达1e14，因此必须避免O(n)的算法。通过枚举i到√(a+b)（最多约1e7次），并利用因数分解的性质（因数成对出现），将时间复杂度控制在可接受范围。  
    * 💡 **学习笔记**：大数据范围的题目需关注时间复杂度，优先选择O(√n)级别的算法。

### ✨ 解题技巧总结
- **枚举优化**：从更优解（i接近√(a+b)）开始枚举，找到第一个符合条件的解即可停止。  
- **因数预处理**：预处理颜色方块的因数，或维护当前最大因数，快速验证子矩形条件。  
- **边界处理**：确保i*j=a+b（即i是a+b的因数），避免无效枚举。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
首先，我们看一个综合优质题解的通用核心实现，它结合了高效枚举和快速验证。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Siyuan和Bring的思路，通过反向枚举大矩形的边长i，并维护颜色方块的当前最大因数，快速验证条件。代码简洁高效，适合竞赛使用。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using LL = long long;

    LL check(LL tot, LL a) {
        LL f = sqrt(a); // 初始最大因数为√a
        for (LL i = sqrt(tot); i >= 1; --i) {
            if (tot % i != 0) continue; // 大矩形边长i必须是tot的因数
            LL j = tot / i; // 大矩形的另一边长
            f = min(f, i); // 确保f不超过当前i
            while (f > 0 && a % f != 0) --f; // 找到a的最大因数≤i
            if (f > 0 && a / f <= j) return 2 * (i + j); // 验证成功
        }
        return LLONG_MAX; // 无合法解（题目保证有解）
    }

    int main() {
        LL a, b;
        scanf("%lld%lld", &a, &b);
        LL tot = a + b;
        // 分别检查红色和蓝色作为子矩形的情况，取最小值
        printf("%lld\n", min(check(tot, a), check(tot, b)));
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先定义check函数，用于计算当颜色方块数为a时的最小周长。函数中反向枚举大矩形的边长i，维护当前最大因数f，快速验证是否存在子矩形。主函数中分别检查红色和蓝色，取最小值。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段。
</code_intro_selected>

**题解一：作者Siyuan**  
* **亮点**：预处理颜色方块的因数，用指针优化查找，时间复杂度低。  
* **核心代码片段**：
    ```cpp
    long long solve(long long tot, long long a) {
        vector<int> f;
        for (int i = 1; 1LL * i * i <= a; ++i) 
            if (a % i == 0) f.push_back(i); // 预处理a的因数
        int p = (int)f.size() - 1; // 指针指向最大因数
        for (int i = sqrt(tot); i >= 1; --i) {
            if (tot % i) continue;
            while (f[p] > i) --p; // 指针左移，找到≤i的最大因数
            if (a / f[p] <= tot / i) 
                return 2LL * (i + tot / i);
        }
        return 1LL << 60;
    }
    ```
* **代码解读**：  
  预处理a的所有因数存入vector，指针p初始指向最大因数。枚举大矩形的边长i时，若当前因数f[p]超过i，则左移p，直到找到≤i的最大因数。验证该因数对应的另一边是否≤大矩形的另一边长（tot/i），若满足则返回周长。  
* 💡 **学习笔记**：预处理因数并利用指针维护当前有效值，避免重复计算，是优化枚举的关键。

**题解二：作者Bring**  
* **亮点**：维护当前最大因数，动态调整，减少冗余操作。  
* **核心代码片段**：
    ```cpp
    signed main() {
        c = Rd(a) + Rd(b), f = sqrt(a), g = sqrt(b);
        Frn_(i, sqrt(c), 1) if (!(c % i)) { // 反向枚举i
            f = min(f, i), g = min(g, i); // 确保f/g不超过i
            while (a % f) --f; // 找到a的最大因数≤i
            if (a / f <= c / i) 
                wr((i + c / i) << 1), exit(0);
            while (b % g) --g; // 找到b的最大因数≤i
            if (b / g <= c / i) 
                wr((i + c / i) << 1), exit(0);
        }
    }
    ```
* **代码解读**：  
  变量f和g分别维护红色和蓝色方块的当前最大因数。每次枚举i时，先将f和g限制为≤i，然后通过while循环找到最大的因数（满足a%f==0）。若对应的另一边≤大矩形的高（c/i），则输出周长并结束。  
* 💡 **学习笔记**：动态调整当前最大因数，避免每次重新计算因数，提升效率。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解枚举和验证过程，我们设计一个“像素矩形探险”动画，用8位风格展示大矩形的枚举和子矩形的验证。
</visualization_intro>

  * **动画演示主题**：像素矩形探险  
  * **核心演示内容**：从i=√(a+b)开始，逐步减小i，展示大矩形的宽i和高j=a+b/i的变化。当找到满足条件的i时，高亮红色或蓝色的子矩形。  

  * **设计思路简述**：  
    8位像素风格（如FC游戏画面）营造轻松氛围；大矩形用灰色网格表示，红色/蓝色子矩形用对应颜色填充；关键步骤（如i的枚举、子矩形的验证）用音效提示（“叮”表示验证成功），增强操作记忆。

  * **动画帧步骤与交互关键点**：  
    1. **初始化**：屏幕显示“像素探险”标题，下方是一个可调整的灰色网格（初始宽高为√(a+b)）。控制面板包含“开始/暂停”“单步”“重置”按钮和速度滑块。  
    2. **枚举i**：点击“开始”后，i从√(a+b)开始递减。每个i对应网格的宽i，高j=a+b/i（用文字显示i和j）。  
    3. **验证子矩形**：对于当前i，检查红色方块是否能形成子矩形：  
       - 红色子矩形的宽x从i开始递减，找到最大的x使得x是a的因数（x≤i）。  
       - 若x*y=a（y=a/x≤j），则红色子矩形用红色填充，并播放“叮”音效。  
       - 若红色不满足，检查蓝色（类似步骤）。  
    4. **成功提示**：找到第一个满足条件的i时，大矩形边框变为绿色，子矩形闪烁，播放“胜利”音效（如FC游戏过关音）。  
    5. **交互控制**：支持单步执行（每点击一次“单步”，i减1并验证）、自动播放（按滑块速度运行）、重置（回到初始状态）。  

  * **旁白提示**：  
    - “当前尝试宽i=5，高j=8（因为5×8=40=a+b）。”  
    - “检查红色方块是否能形成子矩形：红色有4个方块，最大因数≤5的是4（4×1=4），但1≤8，满足！”  
    - “找到啦！周长是2×(5+8)=26，这是当前最优解！”  

<visualization_conclusion>
通过这个动画，你可以清晰看到枚举的每一步，以及子矩形的验证过程，就像跟着像素小人一起探险，轻松理解算法的核心逻辑！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，我们可以将枚举和因数分解的思路应用到更多问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    枚举+数学判断的思路适用于：  
    - 寻找矩形的最小周长（如给定面积，求满足特定条件的最小周长）。  
    - 因数分解相关问题（如寻找两个数的最大公约数、最小公倍数）。  
    - 大数据范围下的优化枚举（如通过√n限制枚举次数）。

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P1029** - 最大公约数和最小公倍数问题  
        * 🗣️ **推荐理由**：需要枚举可能的因数，结合最大公约数和最小公倍数的关系，巩固因数分解的应用。  
    2.  **洛谷 P1414** - 又是毕业季II  
        * 🗣️ **推荐理由**：涉及多个数的因数统计，需要枚举因数并统计出现次数，锻炼枚举与数学结合的能力。  
    3.  **洛谷 P2657** - [SCOI2009] windy数  
        * 🗣️ **推荐理由**：虽然是数位DP，但需要枚举数位上的数字，结合数学规律判断，拓展枚举的应用场景。  

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，以下是有价值的总结：
</insights_intro>

> **参考经验 (来自作者Siyuan)**：“在预处理因数时，一开始忘记将因数对（如i和a/i）都加入vector，导致遗漏了较大的因数，后来通过测试用例发现问题，修正后才通过。”  
> **点评**：因数分解时，i和a/i都是因数（i≤√a时，a/i≥√a），需要同时加入。这提醒我们，预处理因数时要考虑全面，避免遗漏可能的解。

---

<conclusion>
通过对“Multicolored Markers”的分析，我们掌握了枚举+数学判断的解题思路，以及如何优化枚举过程。记住，遇到类似问题时，优先考虑枚举更优解（如接近√n的i），并通过预处理或状态维护优化验证步骤。下次我们再一起挑战新的编程问题！💪
</conclusion>

---
处理用时：110.05秒