# 题目信息

# Cleaning

## 题目描述

During cleaning the coast, Alice found $ n $ piles of stones. The $ i $ -th pile has $ a_i $ stones.

Piles $ i $ and $ i + 1 $ are neighbouring for all $ 1 \leq i \leq n - 1 $ . If pile $ i $ becomes empty, piles $ i - 1 $ and $ i + 1 $ doesn't become neighbouring.

Alice is too lazy to remove these stones, so she asked you to take this duty. She allowed you to do only the following operation:

- Select two neighboring piles and, if both of them are not empty, remove one stone from each of them.

Alice understands that sometimes it's impossible to remove all stones with the given operation, so she allowed you to use the following superability:

- Before the start of cleaning, you can select two neighboring piles and swap them.

Determine, if it is possible to remove all stones using the superability not more than once.

## 说明/提示

In the first test case, you can remove all stones without using a superability: $ [1, 2, 1] \rightarrow [1, 1, 0] \rightarrow [0, 0, 0] $ .

In the second test case, you can apply superability to the second and the third piles and then act like in the first testcase.

In the third test case, you can apply superability to the fourth and the fifth piles, thus getting $ a = [2, 2, 2, 3, 1] $ .

In the fourth test case, you can apply superability to the first and the second piles, thus getting $ a = [1900, 2100, 1600, 3000, 1600] $ .

## 样例 #1

### 输入

```
5
3
1 2 1
3
1 1 2
5
2 2 2 1 3
5
2100 1900 1600 3000 1600
2
2443 2445```

### 输出

```
YES
YES
YES
YES
NO```

# AI分析结果


# 💡 Kay的C++算法解析：Cleaning 深入学习指南 💡

<introduction>
大家好，我是Kay！今天我们一起分析「Cleaning」这道有趣的C++编程题。题目描述在海岸清理中发现n堆石头，每次操作可以移除相邻两堆各一块石头，且允许在开始前交换相邻两堆一次（或不使用）。我们将一起探索解题思路，理解核心算法，并通过像素动画直观感受算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`预处理与贪心模拟`

🗣️ **初步分析**：
> 解决本题的关键在于**预处理前后缀信息+局部枚举验证**。想象你在玩一个像素游戏：屏幕上有n列石头堆，每次只能消去相邻两列顶部的各一块像素（石头）。交换相邻列就像短暂调换两列位置，而我们的目标是用像素动画展示如何高效判断能否清空屏幕。
>
> - **核心思路**：预处理从左到右(`b[]`)和从右到左(`c[]`)的模拟剩余值，枚举交换位置时只需检查局部条件：交换后中间部分能否完美衔接前后缀信息。
> - **难点**：避免每次交换后重新模拟整个序列，需设计高效验证策略。
> - **可视化设计**：动画将展示石头堆的像素块消减过程，交换时高亮两列并播放音效，关键步骤显示`b[i-1]`和`c[i+2]`的匹配逻辑。
> - **复古游戏化**：采用8位像素风格，石头用蓝色方块表示，操作时方块消失伴随“叮”音效，成功清空时播放胜利音乐，控制面板支持单步/自动模式（可调速）。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法效率和实践价值等维度筛选出以下优质题解（均≥4★）：

**题解一（来源：45dino）**
* **点评**：思路清晰直白，通过预处理`b[]`（前缀剩余）和`c[]`（后缀剩余）将问题转化为局部条件检查。代码中变量命名规范（如`b[i]`表示第i堆剩余），边界处理严谨（用-1标记无效状态）。亮点在于用O(n)预处理+O(n)枚举实现高效判断，代码可直接用于竞赛。推导过程展示了如何将全局问题分解为可管理的局部验证。

**题解二（来源：mango2011）**
* **点评**：采用类似思路但代码更模块化，定义`l[]`和`r[]`数组增强可读性。核心逻辑封装在`check()`函数内，边界条件处理完整。亮点在于详细注释和交换后的暴力回退检查，为学习者提供调试参考。实践时需注意数组初始化，但整体逻辑严谨高效。

**题解三（来源：RyexAwl）**
* **点评**：代码简洁但逻辑完备，使用`pre[]`和`suf[]`数组实现相同思想。亮点在于用递归关系解释状态转移（`pre[i]=a[i]-pre[i-1]`），并用常量`INF`标记无效状态。虽然变量名稍简略，但算法本质表达清晰，适合快速理解核心思路。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破以下三个关键难点，结合优质题解的共性策略如下：

1.  **难点1：如何避免全序列重模拟？**
    * **分析**：优质题解均通过预处理`b[]/c[]`数组存储前后缀剩余值。交换影响是局部的——只需检查交换位置前后缀能否衔接。例如45dino解法中，交换位置`i`后只需验证`b[i-1]`和`c[i+2]`的匹配关系。
    * 💡 **学习笔记**：预处理是优化重复计算的核心手段。

2.  **难点2：交换后如何验证？**
    * **分析**：需同时满足三个条件：(1) 交换位置前的前缀剩余`b[i-1]`有效（≥0）；(2) 交换位置后的后缀剩余`c[i+2]`有效；(3) 交换后两堆石头能互相消减：`a[i+1]-b[i-1] == a[i]-c[i+2]`。如mango2011的代码通过`if`条件精炼表达这一逻辑。
    * 💡 **学习笔记**：将复杂条件分解为独立可验证的子条件。

3.  **难点3：边界情况处理**
    * **分析**：需特殊处理首尾交换（如`i=1`或`i=n-1`）和全零校验。RyexAwl解法用`pre[0]=suf[n+1]=0`初始化，确保边界计算正确。
    * 💡 **学习笔记**：边界是BUG高发区，必须单独测试验证。

### ✨ 解题技巧总结
<summary_best_practices>
通过本题可提炼以下通用技巧：
</summary_best_practices>
-   **技巧1：前后缀分解**——将序列问题分解为前缀+当前值+后缀三部分独立处理。
-   **技巧2：局部化思想**——当操作影响有限时，避免全局重新计算，复用预处理结果。
-   **技巧3：条件完备性**——列出所有可能失败的分支（如负值、无效状态），集中处理。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下完整代码基于45dino解法优化，包含预处理、交换枚举和条件验证的全流程：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int t, n, a[N], b[N], c[N]; // b: 前缀剩余, c: 后缀剩余

signed main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        
        // 初始化并计算前缀剩余 b[]
        b[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (b[i-1] != -1 && a[i] >= b[i-1]) 
                b[i] = a[i] - b[i-1];
            else 
                b[i] = -1; // 标记无效状态
        }
        
        // 计算后缀剩余 c[]
        c[n+1] = 0;
        for (int i = n; i >= 1; --i) {
            if (c[i+1] != -1 && a[i] >= c[i+1]) 
                c[i] = a[i] - c[i+1];
            else 
                c[i] = -1;
        }
        
        // 情况1：无需交换即成功
        if (b[n] == 0) {
            cout << "YES\n";
            continue;
        }
        
        // 情况2：枚举交换位置
        bool success = false;
        for (int i = 1; i < n; ++i) {
            // 跳过无效前后缀
            if (b[i-1] == -1 || c[i+2] == -1) continue;
            
            // 验证交换条件
            if (a[i+1] >= b[i-1] && 
                a[i] >= c[i+2] && 
                a[i+1] - b[i-1] == a[i] - c[i+2]) {
                success = true;
                break;
            }
        }
        cout << (success ? "YES" : "NO") << '\n';
    }
    return 0;
}
```
**代码解读概要**：
1. **输入处理**：读入多组测试数据。
2. **预处理阶段**：
   - `b[]`从左到右计算：`b[i] = a[i] - b[i-1]`（若结果非负）
   - `c[]`从右到左计算：`c[i] = a[i] - c[i+1]`
3. **直接成功检查**：若`b[n]==0`则输出"YES"。
4. **枚举交换**：检查每个位置`i`交换后的三个条件。
5. **输出结果**：根据是否找到可行解输出答案。
</code_intro_overall>

<code_intro_selected>
### 优质题解片段赏析
**题解一（45dino）**
* **亮点**：用-1统一标记无效状态，简化条件判断。
* **核心代码片段**：
  ```cpp
  // 计算前缀剩余
  for(int i=1;i<=n;i++) {
      if(a[i]>=b[i-1] && b[i-1]!=-1) 
          b[i]=a[i]-b[i-1];
      else b[i]=-1;
  }
  ```
* **代码解读**：
  > 这段代码通过`b[i-1]!=-1`确保前序状态有效，再用`a[i]>=b[i-1]`保证当前可操作。若条件满足，计算剩余值；否则标记无效。这种**状态传递+短路判断**是处理序列依赖的经典模式。
* 💡 **学习笔记**：用常量标记无效状态可避免复杂错误处理。

**题解二（mango2011）**
* **亮点**：封装检查逻辑，增强可读性。
* **核心代码片段**：
  ```cpp
  bool chk4(int x, int y, int z, int w) {
      if (x > y) return false;     // 条件1：前面剩余需≤当前值
      return chk3(y - x, z, w);    // 条件2：递归检查后续
  }
  ```
* **代码解读**：
  > 将交换后的四值验证分解为独立函数：`x`（`l[i-1]`）需≤`y`（`a[i+1]`），然后递归检查`y-x`与后续值的关系。这种**分步验证+递归抽象**使复杂条件更易维护。
* 💡 **学习笔记**：将复杂条件拆解为小函数提升代码可读性。

**题解三（RyexAwl）**
* **亮点**：用INF避免边界误判。
* **核心代码片段**：
  ```cpp
  if (suf[i-1] != -1 && a[i] >= suf[i-1])
      pre[i] = a[i] - suf[i-1];
  else 
      pre[i] = INF; // 用极大值标记无效
  ```
* **代码解读**：
  > 用`INF`（而非-1）标记无效状态，避免与真实值冲突。计算中通过`a[i] >= suf[i-1]`保证非负，否则设为`INF`。**统一哨兵值+显式条件**确保逻辑清晰。
* 💡 **学习笔记**：选择哨兵值时需考虑数据范围，避免冲突。

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
为直观理解算法，我设计了**「像素海岸清理」**动画方案，采用8位复古风格，通过动态演示前后缀匹配过程帮助大家掌握核心逻辑。
</visualization_intro>

* **动画主题**：像素风格石头堆与动态消减效果（类似经典游戏《推石头》）

* **核心演示内容**：
  1. 初始化显示n列石头堆（每列高度=`a[i]`）
  2. 黄色高亮展示`b[]`和`c[]`的预处理过程
  3. 交换时红色闪烁目标列，绿色显示验证条件
  4. 成功时播放庆祝动画

* **设计思路**：通过颜色区分算法阶段（蓝色=正常，黄色=预处理，红色=交换），音效强化关键操作记忆，关卡式推进增强学习动力。

* **动画步骤与交互**：
  1. **场景初始化**：
     - 网格布局：每列代表一堆石头，高度=`a[i]`，蓝色像素块表示石头
     - 控制面板：开始/暂停、单步执行、速度滑块（1x-5x）
     - 背景：海滩像素画，播放8-bit风格BGM

  2. **预处理阶段**：
     - 从左到右计算`b[]`：从左端开始，绿色箭头扫描，显示`b[i]=a[i]-b[i-1]`
     - 从右到左计算`c[]`：从右端开始，紫色箭头扫描
     - 无效状态时整列闪烁红色并播放警告音

  3. **交换枚举阶段**：
     - 枚举位置`i`：红色边框闪烁第`i`和`i+1`列
     - 条件验证：显示`b[i-1]`（左侧绿色）、`c[i+2]`（右侧紫色）及中间公式`a[i+1]-b[i-1] == a[i]-c[i+2]`
     - 条件满足：目标列变绿并播放“叮”音效
     - 条件失败：目标列变灰并播放低沉音效

  4. **成功/失败效果**：
     - 成功：所有石头消失，烟花动画+胜利音效
     - 失败：显示“NO”像素字，鼓励性提示语

  5. **游戏化元素**：
     - 关卡制：将每组测试数据设计为独立关卡
     - 积分：根据操作步数和速度评分（S/A/B/C）
     - 成就系统：首次通过时解锁像素勋章

* **技术实现**：Canvas绘制网格和像素块，JavaScript更新状态，Web Audio API播放音效（操作声/背景乐）。

<visualization_conclusion>
通过这种游戏化演示，大家能直观感受前后缀预处理如何降低验证复杂度，并在趣味中掌握核心算法逻辑。
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的「前后缀分解+局部验证」思想后，可尝试以下相似问题：
</similar_problems_intro>

* **通用技巧迁移**：
  该模式适用于：① 序列操作影响局部的问题 ② 需要避免重复计算的场景 ③ 带约束的交换/修改问题

* **推荐练习（洛谷）**：
  1. **P1969 积木大赛**  
     🗣️ 直接应用前后缀思想，计算最小操作次数。
  2. **P5019 铺设道路**  
     🗣️ 类似积木大赛，强化序列操作的理解。
  3. **P1106 删数问题**  
     🗣️ 结合贪心思想，练习局部最优决策。

---

## 7. 学习心得与经验分享

<insights_intro>
题解中藏有宝贵经验，45dino提到：
</insights_intro>

> **参考经验**：  
> “交换验证时需注意前后缀的衔接条件，我最初忽略了`a[i+1]>=b[i-1]`的判断导致WA”

> **Kay的总结**：  
> 调试时应优先验证边界条件（如首尾交换、单元素序列），输出中间变量（如`b[]`/`c[]`）辅助定位逻辑漏洞。本题的优雅解法则展示了预处理如何化全局为局部。

---

<conclusion>
本次「Cleaning」的解析就到这里。记住：高效算法的核心在于减少重复工作——预处理是利器，而局部验证是突破口。大家可尝试用像素动画模拟自己的解法，加深理解。下次挑战见！💪
</conclusion>
```

---
处理用时：225.99秒