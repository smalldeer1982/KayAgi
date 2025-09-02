# 题目信息

# Old Floppy Drive

## 题目描述

Polycarp was dismantling his attic and found an old floppy drive on it. A round disc was inserted into the drive with $ n $ integers written on it.

Polycarp wrote the numbers from the disk into the $ a $ array. It turned out that the drive works according to the following algorithm:

- the drive takes one positive number $ x $ as input and puts a pointer to the first element of the $ a $ array;
- after that, the drive starts rotating the disk, every second moving the pointer to the next element, counting the sum of all the elements that have been under the pointer. Since the disk is round, in the $ a $ array, the last element is again followed by the first one;
- as soon as the sum is at least $ x $ , the drive will shut down.

Polycarp wants to learn more about the operation of the drive, but he has absolutely no free time. So he asked you $ m $ questions. To answer the $ i $ -th of them, you need to find how many seconds the drive will work if you give it $ x_i $ as input. Please note that in some cases the drive can work infinitely.

For example, if $ n=3, m=3 $ , $ a=[1, -3, 4] $ and $ x=[1, 5, 2] $ , then the answers to the questions are as follows:

- the answer to the first query is $ 0 $ because the drive initially points to the first item and the initial sum is $ 1 $ .
- the answer to the second query is $ 6 $ , the drive will spin the disk completely twice and the amount becomes $ 1+(-3)+4+1+(-3)+4+1=5 $ .
- the answer to the third query is $ 2 $ , the amount is $ 1+(-3)+4=2 $ .

## 样例 #1

### 输入

```
3
3 3
1 -3 4
1 5 2
2 2
-2 0
1 2
2 2
0 1
1 2```

### 输出

```
0 6 2 
-1 -1 
1 3```

# AI分析结果

# 💡 Kay的C++算法解析：Old Floppy Drive 深入学习指南 💡

<introduction>
  今天我们来一起分析「Old Floppy Drive」这道C++编程题。它的核心是处理**循环数组的前缀和查询**，需要结合前缀和处理与二分查找优化。本指南会帮你梳理思路、理解核心算法，并掌握解题技巧～
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（前缀和处理 + 二分查找优化）

🗣️ **初步分析**：  
解决这道题，我们可以把**循环数组比作“环形跑道”**，把问题转化为：**蜗牛从起点出发，每跑一步累加跑道上的数字（高度），问第一次爬到高度x的时间**。关键思路是：  
1. **记录“一圈内的最高高度”**：计算前缀和的最大值数组`maxn`（`maxn[i]`是前i步的最高累加和），这样可以快速判断蜗牛是否在第一圈就能爬到x。  
2. **判断“圈的总增益”**：如果一圈的总和`sum`（数组所有元素之和）≤0，说明蜗牛每跑一圈都不会更高，永远爬不到x；如果`sum>0`，计算需要跑多少圈`r`，使得`r*sum + maxn[n] ≥x`，再找最后一圈的爬行时间。  

**核心算法流程**：  
- 预处理：计算前缀和`sum`数组 + 前缀和的最大值数组`maxn`（`maxn[i] = max(maxn[i-1], sum[i])`，保证单调递增）。  
- 查询处理：  
  - 若`maxn[n]≥x`：用二分找第一个`maxn[i]≥x`的位置，时间为`i-1`（时间从0开始）。  
  - 若`sum≤0`：输出`-1`（永远达不到）。  
  - 否则：计算圈数`r=(x - maxn[n] + sum -1)/sum`（向上取整），再找剩余`x-r*sum`的位置，总时间为`r*n + i-1`。  

**可视化设计思路**：  
用8位像素风（类似FC游戏）做“蜗牛爬环形井”动画——  
- 环形井用不同颜色像素块表示数组元素（正绿、负红），蜗牛用黄色块表示，当前累加和显示在旁。  
- 关键步骤高亮：`maxn`数组用黄色高亮，圈数增加时显示“圈数+1”提示。  
- 音效：每步“滴滴”声，达到x时“叮”的胜利声，无法达到时“嗡”的提示声。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等维度筛选了3份优质题解，帮你快速借鉴核心技巧～
</eval_intro>

**题解一：来源henrytb**  
* **点评**：用“蜗牛爬井”比喻直击问题本质，思路清晰。代码用`map`存前缀和最大值及其对应时间，利用`map.lower_bound`快速查找第一圈的时间；多圈处理逻辑严谨，变量名（如`tim`记录时间、`row`记录一圈总和）易懂。亮点是将前缀和最大值与`map`结合，实践价值高。

**题解二：来源Special_Tony**  
* **点评**：代码极度简洁！直接将原数组修改为前缀和的最大值数组（`a[i] = max(a[i-1], sum += a[i])`），利用STL的`lower_bound`快速查找。边界处理（如判断`sum>0`才计算圈数）严谨，适合快速理解核心逻辑。

**题解三：来源绝顶我为峰**  
* **点评**：用二分法计算圈数，体现对二分优化的灵活运用。先特判第一圈和无解情况，再通过二分找最小圈数`ans`，最后找剩余`x`的位置。亮点是将二分从“数组查找”扩展到“圈数计算”，帮助理解二分的通用性。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的关键在于**处理循环数组的前缀和**与**高效查询**，以下是3个核心难点及解决策略：
</difficulty_intro>

1. **难点1：如何处理循环数组的前缀和？**  
   * **分析**：循环数组的前缀和是重复的，我们只需计算第一圈的前缀和，并记录**前缀和的最大值数组`maxn`**。`maxn`是单调递增的（每次取最大值），便于后续二分查找。  
   * 💡 **学习笔记**：前缀和的最大值数组是处理循环数组前缀和的“钥匙”——将非单调的前缀和转化为单调序列。

2. **难点2：如何计算需要多少个完整的循环？**  
   * **分析**：当第一圈爬不到x且`sum>0`时，每多跑一圈总增益增加`sum`。用**向上取整公式**计算圈数：`r=(x - maxn[n] + sum -1)/sum`，避免暴力循环。  
   * 💡 **学习笔记**：向上取整公式是处理“周期增益”问题的常用技巧，公式为`(目标值 - 当前值 + 周期增益 -1) / 周期增益`。

3. **难点3：如何高效查找第一个达到x的位置？**  
   * **分析**：`maxn`数组是单调递增的，用`lower_bound`函数可以在O(logn)时间内找到第一个≥x的元素位置。  
   * 💡 **学习笔记**：二分查找是处理单调序列查找的“神器”，适用于多次查询的场景（本题m可达2e5）。

### ✨ 解题技巧总结
- **预处理前缀和最大值数组**：将非单调前缀和转化为单调序列，便于查找。  
- **向上取整计算圈数**：避免暴力循环，提高效率。  
- **多次查询用二分**：将每次查询时间从O(n)降到O(logn)，应对大数据量。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心实现**，综合了优质题解的思路，清晰展示整体框架～
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码综合了Special_Tony和henrytb的思路，简洁高效地实现核心逻辑。  
* **完整核心代码**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  typedef long long ll;

  int main() {
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      int T;
      cin >> T;
      while (T--) {
          int n, m;
          cin >> n >> m;
          vector<ll> sum(n + 1), maxn(n + 1);
          sum[0] = 0;
          maxn[0] = -1e18; // 初始化为极小值
          for (int i = 1; i <= n; ++i) {
              ll a;
              cin >> a;
              sum[i] = sum[i - 1] + a;
              maxn[i] = max(maxn[i - 1], sum[i]); // 前缀和的最大值
          }
          while (m--) {
              ll x;
              cin >> x;
              if (maxn[n] >= x) {
                  // 第一圈找到，二分查找位置
                  int l = 1, r = n;
                  while (l < r) {
                      int mid = (l + r) / 2;
                      if (maxn[mid] >= x) r = mid;
                      else l = mid + 1;
                  }
                  cout << l - 1 << ' ';
              } else if (sum[n] <= 0) {
                  cout << "-1 ";
              } else {
                  // 计算圈数r（向上取整）
                  ll r = (x - maxn[n] + sum[n] - 1) / sum[n];
                  x -= r * sum[n];
                  // 找剩余x的位置
                  int l = 1, r_pos = n;
                  while (l < r_pos) {
                      int mid = (l + r_pos) / 2;
                      if (maxn[mid] >= x) r_pos = mid;
                      else l = mid + 1;
                  }
                  cout << r * n + l - 1 << ' ';
              }
          }
          cout << '\n';
      }
      return 0;
  }
  ```
* **代码解读概要**：  
  - 输入处理：读取测试用例数`T`，每个用例读取`n`（数组长度）和`m`（查询数）。  
  - 预处理：计算前缀和`sum`数组，以及前缀和的最大值数组`maxn`（`maxn[i]`是前i步的最高累加和）。  
  - 查询处理：分三种情况处理每个`x`，用二分快速找位置，输出总时间。

---

<code_intro_selected>
再剖析3份优质题解的核心片段，看它们的“亮点”在哪里～
</code_intro_selected>

**题解一：来源henrytb**  
* **亮点**：用`map`存前缀和最大值及其时间，利用`map.lower_bound`快速查找。  
* **核心代码片段**：
  ```cpp
  map<int, int> tim;
  int row = 0, mx = 0, mxid = 0;
  rep(i, 1, n) {
      scanf("%lld", &a[i]);
      row += a[i];
      if (row > mx) mx = row, mxid = i, tim[mx] = i; // 存最大值和时间
  }
  // 查询处理
  map<int, int>::iterator ii = tim.lower_bound(x);
  if (ii == tim.end() && row <= 0) { printf("-1 "); continue; }
  else if (ii == tim.end()) {
      map<int, int>::iterator lst = tim.end(); --lst;
      int ned = (x - lst->first + row - 1) / row; // 圈数
      ii = tim.lower_bound(x - ned * row);
      printf("%lld ", ii->second + ned * n - 1);
  } else {
      printf("%lld ", ii->second - 1);
  }
  ```
* **代码解读**：  
  - 预处理时，`tim`存前缀和的最大值`mx`及其对应的时间`mxid`（前`mxid`步达到`mx`）。  
  - 查询时，`tim.lower_bound(x)`找第一个≥x的`mx`，对应的时间是`ii->second-1`（时间从0开始）。  
  - 若没找到，计算圈数`ned`，再找剩余`x-ned*row`的位置，总时间是`ii->second + ned*n -1`。  
* 💡 **学习笔记**：`map`的`lower_bound`适合处理有序数据的查找，但要注意`map`的键唯一（只存最大值第一次出现的时间）。

**题解二：来源Special_Tony**  
* **亮点**：直接修改数组为前缀和最大值，代码极简。  
* **核心代码片段**：
  ```cpp
  for (int i = 1; i <= n; ++i)
      cin >> a[i], a[i] = max(a[i-1], sum += a[i]); // a数组变为前缀和最大值
  // 查询处理
  if (x <= a[n]) s = 0;
  else if (sum > 0) s = (x - a[n] + sum -1)/sum; // 圈数
  else { cout << "-1 "; continue; }
  x -= s * sum;
  cout << lower_bound(a+1, a+1+n, x) - a -1 + s*n << ' ';
  ```
* **代码解读**：  
  - 预处理时，`a`数组被重写为前缀和的最大值（`a[i] = max(a[i-1], sum += a[i])`），保证单调递增。  
  - 查询时，用`lower_bound`找`x`的位置，总时间是`位置-1 + s*n`（`s`是圈数）。  
* 💡 **学习笔记**：直接修改数组可以简化代码，STL的`lower_bound`是处理单调序列的“快捷方式”。

**题解三：来源绝顶我为峰**  
* **亮点**：用二分法计算圈数，扩展二分的应用场景。  
* **核心代码片段**：
  ```cpp
  int l=0, r=1e9, mid, ans=1e9;
  while (l < r) {
      mid = (l + r) >> 1;
      if (mid * sum[n] + maxn[n] >= x) { // 判断mid圈是否足够
          r = mid; ans = mid;
      } else l = mid + 1;
  }
  printf("%lld ", ans*n + (lower_bound(maxn+1, maxn+n+1, x-ans*sum[n]) - maxn -1));
  ```
* **代码解读**：  
  - 二分查找最小圈数`ans`，判断`mid*sum[n] + maxn[n]`是否≥x。  
  - 计算剩余`x-ans*sum[n]`，找对应的位置，总时间是`ans*n + 位置-1`。  
* 💡 **学习笔记**：二分不仅能找数组位置，还能计算“周期数”——只要条件满足单调性（这里`mid`越大，总高度越大）。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观理解“蜗牛爬环形井”的过程，我设计了一个**8位像素风动画**，结合复古游戏元素，帮你“看”到算法每一步！
</visualization_intro>

### 动画设计方案
#### 1. **主题与风格**  
- **主题**：像素蜗牛爬环形井（循环数组）。  
- **风格**：FC红白机风格，用16色调色板（如绿色代表正数、红色代表负数、黄色代表蜗牛），界面简洁。  

#### 2. **核心演示内容**  
- **环形井**：用3x3像素块组成环形，每个块代表数组元素（正绿、负红）。  
- **蜗牛**：黄色2x2像素块，初始在起点（第一个元素）。  
- **数据显示**：底部显示当前累加和、时间、目标x；右侧显示`maxn`数组（黄色高亮）。  

#### 3. **动画步骤与交互**  
1. **初始化**：  
   - 环形井显示数组元素，蜗牛在起点，累加和0，时间0。  
   - 控制面板：开始/暂停（红/绿按钮）、单步（蓝按钮）、重置（黄按钮）、速度滑块（1-10帧/秒）。  
   - 背景音乐：8位风格循环BGM（轻快钢琴声）。  

2. **单步执行**：  
   - 点击“单步”，蜗牛移动到下一个元素，累加和更新，时间+1。  
   - 若当前累加和是`maxn`的新最大值，对应元素高亮黄色，播放“叮”的提示声。  

3. **自动播放**：  
   - 点击“开始”，蜗牛自动移动，速度随滑块调整。  
   - 第一圈结束时暂停，显示“第一圈最高高度：maxn[n]”；若需要多圈，显示“圈数+1”并继续。  

4. **达到目标**：  
   - 当累加和≥x时，蜗牛停止，播放胜利音效（上扬“叮”声），高亮路径，显示“总时间：t”。  
   - 若无法达到，播放“嗡”声，显示“无法达到目标”。  

#### 4. **游戏化元素**  
- **关卡奖励**：每完成一圈，显示“圈数+1”并加10分；达到目标加50分，显示“胜利！”动画。  
- **AI演示**：点击“AI自动演示”，算法自动执行，展示完整解题过程（类似“贪吃蛇AI”）。  

<visualization_conclusion>
这个动画用复古游戏元素降低了算法的“抽象感”，让你直观看到`maxn`数组的作用、圈数的计算，以及二分查找的过程～
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的核心技巧后，我们可以将其迁移到**循环数组前缀和**、**二分查找优化**的问题中～
</similar_problems_intro>

### 通用思路迁移
- **前缀和最大值数组**：适用于“多次查询第一个前缀和≥x”的问题（如滑动窗口、循环任务）。  
- **向上取整公式**：适用于“计算周期数”的问题（如资源分配、重复任务）。  
- **二分查找**：适用于单调序列的查找（如数组插入位置、寻找最小值）。

### 洛谷练习推荐
1. **洛谷 P1824 进击的奶牛**  
   - 🗣️ **推荐理由**：二分查找的经典应用，锻炼“寻找最大的最小距离”的思路，巩固二分的实现。  
2. **洛谷 P2678 跳石头**  
   - 🗣️ **推荐理由**：类似进击的奶牛，练习二分的变形——“寻找最短跳跃距离的最大值”。  
3. **洛谷 CF1490G**（原题）  
   - 🗣️ **推荐理由**：直接应用本题的核心算法，检验对“前缀和最大值+二分+循环处理”的掌握程度。  


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“经验之谈”能帮我们避开坑点，快速成长～
</insights_intro>

> **参考经验（来自henrytb）**：“题目用蜗牛爬井解释更好理解一点。”  
> **点评**：这个比喻把抽象的“循环数组前缀和”变成了具象的“蜗牛爬井”，瞬间降低了理解难度。学习算法时，用生活中的比喻“翻译”抽象概念，是非常有效的技巧！  

> **参考经验（来自清烛）**：“因为s_i是不满足单调性的，所以没办法使用二分查找…把s_i单调递增的部分取出来，就可以使用二分了。”  
> **点评**：这是本题的“关键坑点”——前缀和本身非单调，但**前缀和的最大值数组是单调的**。这个经验提醒我们：处理非单调序列的查找问题时，要找“单调的子序列”！  


<conclusion>
本次关于「Old Floppy Drive」的分析就到这里～ 核心是**前缀和最大值数组 + 二分查找 + 循环处理**。记住：编程能力的提升在于“理解本质+反复练习”，下次我们再一起探索新的挑战！💪
</conclusion>

---
处理用时：196.10秒