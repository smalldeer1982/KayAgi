# 题目信息

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1
```

### 输出

```
1 2 3 0 3 
```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1
```

### 输出

```
2 2 2 1 1 0 4 3 4 4 
```

# AI分析结果

# 💡 Kay的C++算法解析：Petya's Exams 深入学习指南 💡

<introduction>
  今天我们来一起分析「Petya's Exams」这道C++编程题。这道题需要我们帮Petya安排每天的活动，让他既能复习完所有考试，又能顺利通过。本指南将梳理题目思路，理解核心贪心算法，并掌握解题技巧。
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法（Greedy Algorithm）

🗣️ **初步分析**：
> 解决「Petya's Exams」的关键是**贪心策略**——**优先处理考试时间更早的考试**。就像我们平时写作业，先做 deadline 更近的任务，否则后面会来不及。在本题中，贪心的核心逻辑是：**先安排考试时间早的复习，因为如果早的考试都没复习完，晚的考试更不可能有足够时间**。  
> - **题解思路**：所有题解都采用了「按考试时间排序 → 遍历安排复习时间 → 检查是否可行」的流程。  
> - **核心难点**：如何确保复习时间不冲突，且覆盖所有考试的要求。解决方法是**先标记考试天（不能复习），再从公布时间到考试前一天，优先填充早考试的复习时间**。  
> - **可视化设计思路**：用8位像素风格展示每天的安排（复习=蓝色、考试=红色、休息=灰色），高亮当前处理的考试（比如闪烁的黄色边框），动态显示复习天数的减少。  
> - **游戏化元素**：加入「复习音效」（叮~）、「考试音效」（咚！）、「休息音效」（嘘~），自动播放时像「时间管理游戏」一样逐步完成安排。


## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性等方面，筛选了以下3份优质题解（评分≥4星）：
</eval_intro>

**题解一：来源：风中の菜鸡（赞：6）**
* **点评**：这份题解思路非常清晰，直接抓住了「按考试时间排序」的贪心核心。代码结构规范，用`struct`存储考试信息（公布时间、考试时间、复习时间、编号），变量名（如`promulgate`、`start`）含义明确。最值得学习的是**提前标记考试天**（将考试天设为`m+1`），避免复习与考试冲突。边界处理严谨（如果复习天数不够直接输出-1），实践价值很高。

**题解二：来源：fls233666（赞：4）**
* **点评**：此题解的代码非常简洁，用`plan`数组记录每天的安排，逻辑直白。排序后遍历每个考试，从公布时间到考试前一天填充复习时间，一旦复习天数够了就break，效率高。亮点是**用`e[i].ci--`实时统计复习天数**，避免额外变量，代码更紧凑。

**题解三：来源：kimidonatsu（赞：1）**
* **点评**：这份题解的模块化设计很好（`read`、`work`、`write`函数分工明确），适合学习代码组织。注释详细，解释了「为什么要标记考试天」「为什么按考试时间排序」等关键问题。用`stable_sort`保证排序的稳定性，虽然本题不需要，但这种严谨性值得借鉴。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题时，我们通常会遇到以下3个核心难点。结合优质题解的共性，我为大家提炼了应对策略：
</difficulty_intro>

1. **难点1：如何确定贪心策略？**  
   * **分析**：贪心的关键是「选择当前最优的决策」。本题中，「考试时间更早的考试」是当前最紧急的，必须优先安排复习。如果先复习晚的考试，早的考试可能因为时间不够而失败。优质题解都通过「按考试时间排序」实现了这一点。  
   * 💡 **学习笔记**：贪心策略的选择要围绕「最紧急的任务」展开。

2. **难点2：如何安排复习时间？**  
   * **分析**：复习时间必须在「公布时间→考试前一天」之间，且不能与考试天冲突。优质题解的做法是：**先标记考试天（设为`m+1`），再遍历每个考试，从公布时间开始，填充空闲天为复习**。这样能确保复习时间不越界。  
   * 💡 **学习笔记**：先处理固定事件（考试天），再填充灵活事件（复习），避免冲突。

3. **难点3：如何处理边界条件？**  
   * **分析**：如果某个考试的复习时间不够（遍历完所有可用天仍没凑够`c_i`天），则输出-1。优质题解都在安排完每个考试后检查`c_i`是否为0，及时终止程序。  
   * 💡 **学习笔记**：边界条件要提前考虑，避免无用的后续计算。


### ✨ 解题技巧总结
- **技巧A：结构体存储复杂信息**：用`struct`存储考试的`s_i`（公布时间）、`d_i`（考试时间）、`c_i`（复习时间）、`id`（编号），便于排序和处理。  
- **技巧B：提前标记固定事件**：考试天是固定的，先标记为`m+1`，避免复习与考试冲突。  
- **技巧C：实时检查可行性**：安排完每个考试后，立即检查复习天数是否足够，及时输出-1。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个通用的核心实现，它综合了优质题解的思路，结构清晰，便于理解：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了「风中の菜鸡」「fls233666」的思路，实现了「按考试时间排序→安排复习→输出结果」的完整流程。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <algorithm>
  using namespace std;

  struct Exam {
      int s, d, c, id; // 公布时间、考试时间、复习时间、编号
  };

  bool cmp(Exam a, Exam b) {
      return a.d < b.d; // 按考试时间升序排序
  }

  int main() {
      int n, m;
      cin >> n >> m;
      int plan[110] = {0}; // 0表示休息，m+1表示考试，1~m表示复习对应考试
      Exam exams[110];

      for (int i = 1; i <= m; i++) {
          cin >> exams[i].s >> exams[i].d >> exams[i].c;
          exams[i].id = i;
          plan[exams[i].d] = m + 1; // 标记考试天
      }

      sort(exams + 1, exams + m + 1, cmp); // 按考试时间排序

      for (int i = 1; i <= m; i++) {
          int need = exams[i].c;
          for (int j = exams[i].s; j < exams[i].d && need > 0; j++) {
              if (plan[j] == 0) { // 空闲天
                  plan[j] = exams[i].id; // 安排复习
                  need--;
              }
          }
          if (need > 0) { // 复习时间不够
              cout << -1 << endl;
              return 0;
          }
      }

      for (int i = 1; i <= n; i++) {
          cout << (plan[i] == m + 1 ? m + 1 : (plan[i] == 0 ? 0 : plan[i])) << " ";
      }
      return 0;
  }
  ```
* **代码解读概要**：  
  1. 读取输入，用`plan`数组标记考试天（`m+1`）。  
  2. 按考试时间排序，优先处理早的考试。  
  3. 遍历每个考试，从公布时间到考试前一天，填充空闲天为复习（`plan[j] = 考试id`）。  
  4. 检查复习时间是否足够，不够则输出-1。  
  5. 输出`plan`数组，0表示休息，`m+1`表示考试，1~m表示复习对应考试。


<code_intro_selected>
接下来，剖析优质题解的核心片段：
</code_intro_selected>

**题解一：来源：风中の菜鸡**
* **亮点**：用`struct`存储考试信息，变量名含义明确。
* **核心代码片段**：
  ```cpp
  struct Exam{
      int promulgate, start, review, place; // 公布时间、考试时间、复习时间、编号
  } exam[110];

  bool cmp(Exam x, Exam y){
      return x.start < y.start; // 按考试时间排序
  }
  ```
* **代码解读**：  
  用`promulgate`（公布时间）、`start`（考试时间）、`review`（复习时间）、`place`（编号）存储考试信息，变量名直观。`cmp`函数按`start`（考试时间）排序，符合贪心策略。  
* 💡 **学习笔记**：变量名要清晰，避免用`a`、`b`等无意义的名字。

**题解二：来源：fls233666**
* **亮点**：用`e[i].ci--`实时统计复习天数，代码紧凑。
* **核心代码片段**：
  ```cpp
  for (rgt i = 1; i <= m; i++) {
      for (rgt j = e[i].si; j < e[i].di; j++) {
          if (!plan[j]) { // 空闲天
              plan[j] = e[i].id;
              e[i].ci--; // 复习天数减1
              if (!e[i].ci) break; // 够了就break
          }
      }
      if (e[i].ci) { // 不够则输出-1
          printf("-1");
          return 0;
      }
  }
  ```
* **代码解读**：  
  遍历每个考试的可用天，一旦填充了一个复习天，就把`e[i].ci`减1，直到`e[i].ci`为0（够了）。这样避免了额外的`need`变量，代码更简洁。  
* 💡 **学习笔记**：尽量用现有变量存储状态，减少冗余。

**题解三：来源：kimidonatsu**
* **亮点**：模块化设计，函数分工明确。
* **核心代码片段**：
  ```cpp
  void read() {
      scanf("%d %d", &n, &m);
      for (re int i = 1; i <= m; i++) {
          scanf("%d %d %d", &exams[i].s, &exams[i].d, &exams[i].c);
          exams[i].id = i;
          ans[exams[i].d] = m + 1; // 标记考试天
      }
  }

  void work() {
      stable_sort(exams + 1, exams + m + 1, cmp);
      for (re int i = 1; i <= m; i++) {
          for (re int j = exams[i].s; j < exams[i].d; j++) {
              if (!ans[j]) {
                  ans[j] = exams[i].id;
                  exams[i].c--;
                  if (!exams[i].c) break;
              }
          }
          if (exams[i].c) {
              printf("-1\n");
              exit(0);
          }
      }
  }
  ```
* **代码解读**：  
  把「读取输入」「处理逻辑」分成`read`、`work`函数，代码结构清晰。`stable_sort`保证排序的稳定性（虽然本题不需要，但严谨）。  
* 💡 **学习笔记**：模块化设计能提高代码的可读性和可维护性。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解「贪心安排复习时间」的过程，我设计了一个8位像素风格的动画，像「时间管理游戏」一样展示每天的安排：
</visualization_intro>

### 🎮 动画演示主题：Petya的考试日程表（FC红白机风格）
### 🎨 设计思路
- **风格**：采用8位像素风（类似《超级马里奥》），用简单的色块表示每天的活动（复习=蓝色方块、考试=红色方块、休息=灰色方块）。  
- **趣味性**：加入「复习音效」（叮~）、「考试音效」（咚！）、「休息音效」（嘘~），自动播放时像游戏一样逐步完成安排。  
- **交互性**：控制面板有「单步执行」「自动播放」（速度滑块）、「重置」按钮，方便观察每一步。


### 📊 动画帧步骤
1. **初始化场景**：  
   - 屏幕左侧显示「时间轴」（1~n天，每个天是一个像素方块）。  
   - 右侧显示「考试列表」（按考试时间排序，红色标记当前处理的考试）。  
   - 控制面板在底部，有「开始」「暂停」「单步」「重置」按钮和速度滑块。  
   - 8位风格的背景音乐（轻快的电子乐）开始播放。

2. **标记考试天**：  
   - 考试天的方块变成红色，旁边显示「考试」字样。例如，样例1中的第3天和第5天变成红色。

3. **安排复习时间**：  
   - 按考试时间排序后，当前处理的考试（比如样例1中的考试1）用黄色边框高亮。  
   - 从公布时间（第1天）开始，遍历每个天：  
     - 如果是空闲天（灰色），变成蓝色，旁边显示「复习考试1」，播放「叮~」音效。  
     - 考试的复习天数（`c_i`）从1变成0，右侧考试列表中的`c_i`更新。  
   - 当复习天数够了，当前考试的黄色边框消失，处理下一个考试（考试2）。

4. **完成安排**：  
   - 所有考试的复习天数都为0，时间轴上的方块显示完整的安排（蓝色=复习、红色=考试、灰色=休息）。  
   - 播放「胜利音效」（上扬的电子音），屏幕显示「完成！」字样。

5. **无解情况**：  
   - 如果某个考试的复习天数不够，时间轴上的方块停止变化，播放「失败音效」（短促的电子音），屏幕显示「-1」字样。


### 🛠️ 技术实现要点
- **Canvas绘制**：用`ctx.fillRect`绘制每天的方块，`ctx.fillStyle`设置颜色（蓝色=="#00f"、红色=="#f00"、灰色=="#ccc"）。  
- **音效**：用`Audio`对象播放8位风格的音效（比如复习音效是`ping.mp3`，考试音效是`bang.mp3`）。  
- **交互**：用`addEventListener`处理按钮点击（比如「单步」按钮触发下一步操作，「自动播放」用`setInterval`定时执行）。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
贪心算法是解决「时间管理」「资源分配」问题的常用方法。掌握了本题的思路，可以解决更多类似问题：
</similar_problems_intro>

### 🧠 通用思路迁移
- **场景1**：作业安排（先做 deadline 近的作业）。  
- **场景2**：会议安排（选择最多的不冲突会议）。  
- **场景3**：资源分配（优先分配给最紧急的任务）。


### 📚 洛谷练习推荐
1. **洛谷 P1230** - 智力大冲浪  
   🗣️ **推荐理由**：这道题和本题思路几乎一样，都是「按 deadline 排序 → 安排任务」，能快速巩固贪心策略。  
2. **洛谷 P1090** - 合并果子  
   🗣️ **推荐理由**：考察「贪心+优先队列」，需要选择当前最小的两个果子合并，培养贪心的思维。  
3. **洛谷 P2123** - 皇后游戏  
   🗣️ **推荐理由**：考察「贪心的证明」，需要推导排序的条件，提升对贪心策略的理解。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的经验分享能帮助我们少走弯路：
</insights_intro>

> **参考经验（来自：风中の菜鸡）**：「排序是贪心的关键，我一开始没按考试时间排序，结果错了好几次。后来想通了，早的考试必须优先处理，否则后面没时间。」  
> **点评**：这位作者的经验很典型。贪心策略的选择直接决定了问题能否解决，一定要围绕「最紧急的任务」展开。  
> **参考经验（来自：fls233666）**：「提前标记考试天很重要，否则会把复习安排到考试天，导致错误。」  
> **点评**：固定事件（比如考试天）要先处理，避免与灵活事件（比如复习）冲突，这是时间管理问题的常见技巧。


<conclusion>
本次关于「Petya's Exams」的C++解题分析就到这里。希望这份指南能帮助大家理解贪心算法的核心思路，掌握时间管理问题的解题技巧。记住，贪心的关键是「选择当前最优的决策」，而实践是提升的关键。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：187.22秒