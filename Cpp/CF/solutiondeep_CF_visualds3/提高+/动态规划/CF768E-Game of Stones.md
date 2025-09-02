# 题目信息

# Game of Stones

## 题目描述

Sam has been teaching Jon the Game of Stones to sharpen his mind and help him devise a strategy to fight the white walkers. The rules of this game are quite simple:

- The game starts with $ n $ piles of stones indexed from $ 1 $ to $ n $ . The $ i $ -th pile contains $ s_{i} $ stones.
- The players make their moves alternatively. A move is considered as removal of some number of stones from a pile. Removal of $ 0 $ stones does not count as a move.
- The player who is unable to make a move loses.

Now Jon believes that he is ready for battle, but Sam does not think so. To prove his argument, Sam suggested that they play a modified version of the game.

In this modified version, no move can be made more than once on a pile. For example, if $ 4 $ stones are removed from a pile, $ 4 $ stones cannot be removed from that pile again.

Sam sets up the game and makes the first move. Jon believes that Sam is just trying to prevent him from going to battle. Jon wants to know if he can win if both play optimally.

## 说明/提示

In the first case, Sam removes all the stones and Jon loses.

In second case, the following moves are possible by Sam: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768E/4cf426c19e824968ff19a401a7802c8ac91cbb66.png)

In each of these cases, last move can be made by Jon to win the game as follows: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768E/dbfee646415d7f71d37ff9a2600935f88c5436ae.png)

## 样例 #1

### 输入

```
1
5
```

### 输出

```
NO```

## 样例 #2

### 输入

```
2
1
2
```

### 输出

```
YES```

# AI分析结果

---
# 💡 Kay的C++算法解析：Game of Stones 深入学习指南 💡

<introduction>
今天我们来一起分析经典的博弈论题目「Game of Stones」。这道题在普通取石子游戏的基础上增加了「同一堆不能取相同数量的石子两次」的限制，需要我们通过**问题转化**和**Nim游戏结论**来解决。本指南会帮你理清思路、掌握核心算法，并通过像素动画直观感受解题过程！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：博弈论（Nim游戏）、SG函数应用、问题转化技巧

🗣️ **初步分析**：
解决这道题的关键，在于把「有取法限制的石子堆」转化为「无限制的Nim堆」。我们可以用一个比喻理解：  
普通Nim堆就像「可以拿任意数量糖果的罐子」，而本题的限制相当于「每个罐子的糖果只能按1颗、2颗、3颗……的顺序拿，不能重复拿相同数量」。比如一堆10颗石子，最多能拿4次（1+2+3+4=10），所以它等效于一个**大小为4的普通Nim堆**。  

### 核心逻辑链：
1. **限制条件转化**：每堆石子最多能取`d`次（满足`1+2+…+d ≤ s_i`的最大`d`），因为每次取的数量必须递增且不重复。  
2. **Nim游戏结论**：将所有堆的`d`异或，如果结果为0，后手（Jon）赢；否则先手（Sam）赢。  

### 可视化设计思路：
我们会用**8位像素风**模拟石子堆的「取法转化」过程：  
- 用不同颜色的像素块表示「剩余石子」和「已取数量」（比如黄色代表剩余，灰色代表已取）；  
- 每取一次，像素块会「滑动消失」并播放轻微的「叮」声，同时在旁边显示已取的数量；  
- 当无法再取时，会弹出「等效Nim堆大小：d」的提示，并高亮该堆的`d`值；  
- 最后用二进制位的「异或动画」展示所有`d`的计算过程，结果为0时播放「胜利音效」。


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法有效性**三个维度筛选了4份优质题解，覆盖了「暴力计算」「SG函数推导」「数学优化」「打表验证」四种思路，帮你全面理解问题！
</eval_intro>

### 题解一（作者：pufanyi，赞11）
* **点评**：这份题解是「问题转化」的最直观实现！作者用**循环模拟取石子过程**（每次取最小的可能数量`j`），直到无法再取，从而得到等效的`d`。代码只有20行，逻辑直白到「看一遍就能懂」。比如对于`s_i=5`，循环会取1→剩4，取2→剩2，此时无法取3（因为2<3），所以`d=2`。这种写法的优势是**容易理解转化逻辑**，适合入门学习者。


### 题解二（作者：ωαηg，赞5）
* **点评**：这是一份「知其所以然」的题解！作者没有直接用转化结论，而是**推导了SG函数**：用`sg[i][j]`表示「剩i颗石子、上一次取j颗」的SG值，再用`all_sg[i]`表示「剩i颗石子」的全局SG值。通过状态转移和mex运算（求最小非负未出现值），最终得到的`all_sg[i]`刚好等于我们之前说的`d`！这种写法帮你**深入理解转化的原理**，适合想搞懂「为什么能转化」的同学。


### 题解三（作者：Dancing_Wave，赞2）
* **点评**：这是「数学优化」的典范！作者发现`d`满足`d(d+1)/2 ≤ s_i`，直接用**求根公式**计算`d = floor( (sqrt(8s_i +1) -1)/2 )`。比如`s_i=5`时，`sqrt(41)≈6.4`，`(6.4-1)/2≈2.7`，取整得`d=2`。这种写法的时间复杂度是`O(n)`，空间复杂度`O(1)`，**适合大输入场景**，是竞赛中的「最优写法」。


### 题解四（作者：Pecco，赞2）
* **点评**：这是「暴力验证」的巧妙应用！作者用DFS暴搜所有可能的取法，打表生成`sg`数组（比如`sg[5]=2`），然后直接查表计算异或结果。这种写法的优势是**快速验证结论**——比如通过表可以发现「sg值为k的数刚好有k+1个」，帮你更直观地理解转化规律。适合想「快速验证思路」的同学。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的「门槛」在于**将限制条件转化为Nim堆**，以下是三个核心难点及解决策略：
</difficulty_intro>

### 1. 难点1：如何理解「不能重复取相同数量」的限制？
* **分析**：这个限制等价于「每次取的数量必须严格递增」（比如第一次取1，第二次只能取≥2，第三次≥3……）。因为如果取过x，之后就不能再取x，所以最优策略是按最小的可能数量取（1→2→3→…），这样能取最多的次数`d`。  
* 💡 学习笔记：限制条件的本质是「取法的递增性」，转化为「最大可取次数」是关键。


### 2. 难点2：如何计算最大可取次数`d`？
* **分析**：`d`是满足`1+2+…+d ≤ s_i`的最大整数。有两种计算方式：  
  - 循环法（pufanyi）：每次加`j`，直到`s_i < j`，此时`j-1`就是`d`；  
  - 数学法（Dancing_Wave）：用求根公式直接计算，避免循环。  
* 💡 学习笔记：数学公式能大幅优化计算效率，记得推导时要「向下取整」。


### 3. 难点3：为什么转化为Nim游戏是正确的？
* **分析**：每堆石子的SG值等于`d`（通过题解二的SG函数推导验证），而Nim游戏的结论是「所有堆的SG值异或为0则后手赢」。这一步是「博弈论的核心结论」，需要记住并理解。  
* 💡 学习笔记：SG函数是博弈论的「语言」，将复杂问题转化为SG值的异或是常见技巧。


### ✨ 解题技巧总结
- **问题转化**：遇到限制条件，先想「能不能转化为已知模型」（比如本题转化为Nim游戏）；  
- **数学优化**：循环能解决的问题，试试用公式简化（比如求最大`d`的公式）；  
- **暴力验证**：不确定结论时，用DFS或打表验证（比如Pecco的打表）。


## 4. C++核心代码实现赏析

<code_intro_overall>
我们先看一份**综合了数学优化和Nim结论**的通用代码，它是竞赛中的「最优写法」！
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：本代码来自Dancing_Wave的题解，用数学公式计算`d`，时间复杂度`O(n)`，逻辑简洁高效。
* **完整核心代码**：
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int read() {
    int f = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
    while (isdigit(ch)) { f = f * 10 + (ch - '0'); ch = getchar(); }
    return f * w;
}

int main() {
    int n = read(), ans = 0;
    for (int i = 1; i <= n; ++i) {
        int s = read();
        int d = (sqrt(8LL * s + 1) - 1) / 2; // 注意8LL避免溢出
        ans ^= d;
    }
    cout << (ans ? "NO" : "YES") << endl;
    return 0;
}
```
* **代码解读概要**：
  1. `read()`函数：快速读取输入（竞赛中常用，避免cin超时）；  
  2. 循环处理每堆石子：用公式计算`d`（`8LL`是为了避免整数溢出）；  
  3. 异或所有`d`，结果为0则Jon赢（输出YES），否则Sam赢（输出NO）。


<code_intro_selected>
接下来我们剖析其他优质题解的核心片段，看不同思路的实现细节！
</code_intro_selected>

### 题解一（pufanyi）：循环计算`d`
* **亮点**：用循环模拟取石子过程，直观展示`d`的计算逻辑。
* **核心代码片段**：
```cpp
int j = 1;
for (j = 1;; j++) {
    t -= j; // 每次取j颗（递增）
    if (t <= j) break; // 无法再取j+1颗，终止
}
sgg ^= j;
```
* **代码解读**：
  - `t`是当前堆的石子数，`j`从1开始递增；  
  - 每次取`j`颗（`t -= j`），直到`t ≤ j`（比如`t=2`，`j=3`时，无法取3颗）；  
  - 此时`j`就是最大可取次数`d`，异或到结果中。
* 💡 学习笔记：循环是「直观理解转化逻辑」的好方法，适合入门。


### 题解二（ωαηg）：SG函数推导
* **亮点**：用状态转移推导SG值，帮你理解「为什么`d`等于SG值」。
* **核心代码片段**：
```cpp
// 计算sg[i][j]：剩i颗，上一次取j颗的SG值
for (int i = 1; i <= 60; ++i)
    for (int j = 1; j <= i; ++j) {
        for (int k = j + 1; k <= i - j; ++k)
            vis1[sg[i - j][k]][1] = i, vis1[sg[i - j][k]][2] = j;
        for (sg[i][j] = 0; vis1[sg[i][j]][1] == i && vis1[sg[i][j]][2] == j; sg[i][j]++);
    }
// 计算all_sg[i]：剩i颗的全局SG值
for (int i = 1; i <= 60; ++i) {
    for (int j = 1; j <= i; ++j) vis2[sg[i][j]] = i;
    for (all_sg[i] = 0; vis2[all_sg[i]] == i; all_sg[i]++);
}
```
* **代码解读**：
  - `sg[i][j]`通过mex运算（求最小未出现的非负整数）得到；  
  - `all_sg[i]`是所有`sg[i][j]`的mex，最终`all_sg[i]`等于`d`；  
  - 这部分代码验证了「`d`是堆的SG值」的结论。
* 💡 学习笔记：SG函数是博弈论的基础，理解它能解决更多复杂问题。


### 题解四（Pecco）：打表验证
* **亮点**：用DFS暴搜打表，快速验证结论的正确性。
* **核心代码片段**：
```cpp
// 打表代码（生成sg数组）
int dfs(int n) {
    bool A[70]{};
    for (int i = 1; i <= n; ++i)
        if (!block[i]) {
            block[i] = 1;
            A[dfs(n - i)] = 1;
            block[i] = 0;
        }
    for (int i = 0;; ++i) if (!A[i]) return i;
}
// 最终代码（查表）
int sg[] = {0,1,1,2,2,2,3,3,3,3,4,...}; // 省略部分值
int main() {
    int n, x, ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x, ans ^= sg[x];
    cout << (ans ? "NO" : "YES");
}
```
* **代码解读**：
  - `dfs(n)`通过暴搜所有取法，计算`n`颗石子的SG值；  
  - 打表生成`sg`数组后，直接查表计算异或结果；  
  - 这种写法适合「数据范围小」的题目，快速验证结论。
* 💡 学习笔记：打表是「快速验证思路」的有效方法，尤其适合博弈论问题。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地理解「限制条件转化」和「Nim游戏结论」，我设计了一个**8位像素风的动画**，结合复古游戏元素，让算法「动起来」！
</visualization_intro>

### 动画演示主题：像素石子堆的「转化大冒险」
**风格**：仿FC红白机风格，用16色调色板（比如黄色石子、灰色已取、蓝色等效堆），搭配8位BGM（循环的轻快旋律）。

### 核心演示步骤：
1. **初始化场景**：
   - 屏幕左侧显示3个像素石子堆（比如第一堆5颗，第二堆1颗，第三堆2颗）；  
   - 右侧是「控制面板」：单步/自动播放按钮、速度滑块、重置按钮；  
   - 底部显示「当前等效堆总和」（异或结果）。

2. **转化过程演示**（以第一堆5颗为例）：
   - **步骤1**：取1颗（黄色石子块「滑动消失」，播放「叮」声），剩余4颗；  
   - **步骤2**：取2颗（再消失2块，「叮」声），剩余2颗；  
   - **步骤3**：无法取3颗（剩余2<3），弹出提示「等效堆大小：2」（蓝色块显示）；  
   - **高亮**：第一堆的蓝色块闪烁，提示「这堆等效于2颗普通石子」。

3. **Nim结论演示**：
   - 所有堆转化完成后，底部显示每个堆的`d`值（比如2、1、1）；  
   - 用二进制位的「异或动画」展示：2(10) ^ 1(01) ^ 1(01) = 0(00)；  
   - 结果为0时，播放「胜利音效」（上扬的8位音调），屏幕弹出「Jon赢了！」的像素文字。

### 交互设计：
- **单步模式**：点击「下一步」，逐帧观看转化过程；  
- **自动模式**：拖动滑块调整速度（1x~5x），算法自动执行；  
- **重置**：恢复初始状态，重新演示。

### 为什么这么设计？
- **像素风格**：复古游戏感降低学习压力，让算法更「亲切」；  
- **音效提示**：关键操作（取石子、异或）用音效强化记忆；  
- **可视化转化**：直接看到「限制条件如何变成等效堆」，解决「为什么能转化」的疑惑。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
学会了「限制条件转化为Nim游戏」的技巧后，我们可以解决更多博弈论问题！
</similar_problems_intro>

### 通用思路迁移
- **适用场景1**：取石子游戏的变种（比如「每次取的数量是质数」「每次取的数量不超过上一次」）；  
- **适用场景2**：棋盘游戏（比如「轮流移动棋子，不能走重复路径」）；  
- **适用场景3**：组合游戏（比如「多个子游戏组合，每个子游戏有独立规则」）。


### 洛谷练习推荐
1. **洛谷 P2197** - Nim游戏  
   🗣️ 推荐理由：这是Nim游戏的基础题，帮你巩固「异或结论」的应用。  
2. **洛谷 P1247** - 取火柴游戏  
   🗣️ 推荐理由：需要找出Nim游戏的必胜策略，锻炼「构造解」的能力。  
3. **洛谷 P2575** - 高手过招  
   🗣️ 推荐理由：用SG函数解决「多堆取石子」的变种问题，深化对博弈论的理解。  
4. **洛谷 P4136** - 谁能赢呢？  
   🗣️ 推荐理由：将棋盘游戏转化为Nim游戏，练习「问题转化」的技巧。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
以下是题解中作者的「踩坑心得」，帮你避免同样的错误：
</insights_intro>

> **参考经验（来自JerryZiruiZhang）**：「我在求mex的时候一开始从1开始枚举，结果出错了！后来发现mex应该从0开始找最小的未出现值。」  
> **点评**：mex是「最小非负未出现整数」，从0开始枚举是关键！这个细节容易被忽略，作者的经验提醒我们：**写SG函数时，mex的循环起点要注意**。


<conclusion>
本次关于「Game of Stones」的分析就到这里！这道题的核心是「将限制条件转化为Nim游戏」，而理解转化的关键在于「最大可取次数d」。记住：博弈论问题的本质是「找SG值」，而转化是解决复杂问题的利器！  

下次遇到博弈论问题时，不妨先想：「能不能转化为已知的模型？」多练习、多思考，你会越来越熟练！💪
</conclusion>

---

---
处理用时：83.40秒