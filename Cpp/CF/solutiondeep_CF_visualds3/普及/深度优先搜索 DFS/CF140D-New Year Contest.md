# 题目信息

# New Year Contest

## 题目描述

As Gerald sets the table, Alexander sends the greeting cards, and Sergey and his twins create an army of clone snowmen, Gennady writes a New Year contest.

The New Year contest begins at 18:00 (6.00 P.M.) on December 31 and ends at 6:00 (6.00 A.M.) on January 1. There are $ n $ problems for the contest. The penalty time for each solved problem is set as the distance from the moment of solution submission to the New Year in minutes. For example, the problem submitted at 21:00 (9.00 P.M.) gets penalty time 180, as well as the problem submitted at 3:00 (3.00 A.M.). The total penalty time is calculated as the sum of penalty time for all solved problems. It is allowed to submit a problem exactly at the end of the contest, at 6:00 (6.00 A.M.).

Gennady opened the problems exactly at 18:00 (6.00 P.M.) and managed to estimate their complexity during the first 10 minutes of the contest. He believes that writing a solution for the $ i $ -th problem will take $ a_{i} $ minutes. Gennady can submit a solution for evaluation at any time after he completes writing it. Probably he will have to distract from writing some solution to send the solutions of other problems for evaluation. The time needed to send the solutions can be neglected, i.e. this time can be considered to equal zero. Gennady can simultaneously submit multiple solutions. Besides, he can move at any time from writing one problem to another, and then return to the first problem from the very same place, where he has left it. Thus the total solution writing time of the $ i $ -th problem always equals $ a_{i} $ minutes. Of course, Gennady does not commit wrong attempts, and his solutions are always correct and are accepted from the first attempt. He can begin to write the solutions starting from 18:10 (6.10 P.M.).

Help Gennady choose from the strategies that help him solve the maximum possible number of problems, the one with which his total penalty time will be minimum.

## 说明/提示

In the sample, one of Gennady's possible optimal strategies is as follows. At 18:10 (6:10 PM) he begins to write the first problem and solves it in 30 minutes (18:40 or 6.40 P.M.). At 18:40 (6.40 P.M.) he begins to write the second problem. There are 320 minutes left before the New Year, so Gennady does not have the time to finish writing the second problem before the New Year. At 0:00 (12.00 A.M.) he distracts from the second problem, submits the first one, and returns immediately to writing the second problem. At 0:10 (0.10 A.M.), he completes the solution for the second problem, submits it and gets 10 minute penalty time. Note that as the total duration of the contest is 720 minutes and Gennady has already spent 10 minutes on reading the problems, he will not have time to solve the third problem during the contest. Yes, such problems happen to exist.

Competitions by the given rules are held annually on the site http://b23.ru/3wvc

## 样例 #1

### 输入

```
3
30 330 720
```

### 输出

```
2 10
```

# AI分析结果

# 💡 Kay的C++算法解析：New Year Contest 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法（Greedy Algorithm）

🗣️ **初步分析**：  
解决“New Year Contest”这道题，关键在于**贪心思想**——就像收拾书包时，先装小物件能装更多，而且不会浪费空间。贪心算法的核心是“每次选当前最优的选择，最终得到全局最优”。在本题中，我们需要**优先做耗时短的题**，这样既能保证做最多的题，又能让罚时最少（零点前做完的题可以攒到零点提交，罚时为0；零点后做完的题，做完就提交，罚时等于做题时间超过零点的部分）。  

**核心思路**：  
1. 将所有题按耗时从小到大排序（贪心的关键，优先选耗时短的题）；  
2. 累加做题时间，判断是否超过总可用时间（710分钟，因为前10分钟用来估计难度）；  
3. 计算罚时：做题时间总和超过350分钟（零点前的可用时间）的部分，就是总罚时（因为每道题的提交时间等于做完的时间，零点后做完的题的罚时等于做完时间减去零点的时间）。  

**可视化设计思路**：  
我们可以用**8位像素风格**设计动画，比如：  
- 用不同颜色的像素块代表题目（灰色：未排序，蓝色：已排序，绿色：已做，红色：超时）；  
- 时间条从左到右增长，350分钟处有一条黄色分界线（代表零点）；  
- 罚时数值用跳动的像素数字显示，当时间超过分界线时，数值增加。  
- 交互设计：支持“单步执行”（每选一道题，动画走一步）、“自动播放”（按设定速度播放），并添加“排序叮”“选做题滴”“罚时咚”等音效，增强趣味性。


## 2. 精选优质题解参考

为了帮助大家更好地理解，我从思路清晰度、代码可读性、算法有效性等方面，筛选了以下3份优质题解：


### **题解一：来自 naroto2022**  
* **点评**：这份题解的思路非常直白，完美体现了贪心的核心逻辑。代码风格简洁，变量名（`ans`：题数，`num`：罚时，`cnt`：总时间）清晰易懂，让人一眼就能看出每一步的目的。算法上，排序后循环累加时间，判断是否超过总时间（720分钟），并计算罚时（超过360分钟的部分，因为`cnt`包含前10分钟，所以`cnt-360`等于做题时间超过350分钟的部分）。从实践角度看，代码可以直接用于竞赛，边界处理（如`cnt>720`时break）非常严谨。


### **题解二：来自 Crism_qwq**  
* **点评**：这份题解的亮点是**分两天处理时间**——把零点前的350分钟（第一天）和零点后的360分钟（第二天）分开计算。先做第一天能做完的题，再用第一天剩余的时间补第二天的时间，最后计算第二天的罚时。这种分阶段的思路让逻辑更清晰，适合初学者理解“零点”这个时间节点的影响。代码中的`time1`（第一天时间）和`time2`（第二天时间）变量命名准确，容易跟踪。


### **题解三：来自 Eason_AC**  
* **点评**：这份题解用了**前缀和数组**（`s[i]`表示前`i`题的时间总和），让时间计算更直观。循环中判断`s[i-1]+a[i]`是否超过710（总可用做题时间），避免了重复累加。罚时计算用`max(0, s[i]-350)`，直接对应“做题时间超过零点的部分”，逻辑简洁。代码中的`_for`循环（自定义宏）让代码更紧凑，适合有一定基础的学习者借鉴。


## 3. 核心难点辨析与解题策略

在解决这个问题时，大家通常会遇到以下3个核心难点，结合优质题解的共性，我为大家提炼了应对策略：


### 1. **难点1：理解罚时的计算方式**  
**问题**：为什么罚时等于做题时间总和超过350分钟的部分？  
**分析**：零点是18:10加350分钟（5小时50分钟），所以做题时间总和≤350分钟时，所有题都在零点前做完，攒到零点提交，罚时为0；如果总和>350分钟，超过的部分就是零点后做的题的罚时（因为每道题做完就提交，所以总罚时等于所有题的提交时间与零点的差之和，而提交时间等于做题时间总和，所以总罚时=总和-350）。  
**💡 学习笔记**：罚时的本质是“做题时间超过零点的部分”，理解这一点就能快速计算罚时。


### 2. **难点2：贪心策略的正确性**  
**问题**：为什么优先做耗时短的题能保证最多题和最少罚时？  
**分析**：要做最多的题，肯定选耗时短的；而罚时方面，耗时短的题先做，能让零点后做的题的耗时尽可能少，从而罚时最少。比如，若有两道题，耗时100和200分钟，先做100的，零点后做200的，罚时200；若先做200的，零点后做100的，罚时100+200=300，显然前者更优。  
**💡 学习笔记**：贪心策略的正确性需要证明，本题通过“交换论证”（交换两个题的顺序，结果不会更优）可以证明。


### 3. **难点3：时间的处理（前10分钟与总时间）**  
**问题**：为什么总可用时间是710分钟？  
**分析**：比赛从18:00到6:00共720分钟，但前10分钟用来估计难度，所以实际做题时间从18:10开始，到6:00结束，共710分钟（720-10=710）。代码中需要注意：`cnt`（总时间）=10+做题时间总和，不能超过720；`s[i]`（做题时间总和）不能超过710。  
**💡 学习笔记**：读题时要注意“隐藏条件”，比如前10分钟的扣除，否则会导致结果错误。


### ✨ 解题技巧总结  
- **排序是贪心的基础**：大部分贪心问题都需要先排序，比如本题按耗时从小到大排序。  
- **分阶段处理时间**：把零点前和零点后的时间分开，更容易理解罚时的计算。  
- **用前缀和简化计算**：前缀和数组可以快速得到前`i`题的时间总和，避免重复累加。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：本代码综合了优质题解的思路，用最简洁的方式实现了贪心逻辑。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <algorithm>
  using namespace std;

  int main() {
      int n;
      cin >> n;
      int a[105];
      for (int i = 0; i < n; i++) {
          cin >> a[i];
      }
      sort(a, a + n); // 按耗时从小到大排序

      int sum = 0; // 做题时间总和（不包含前10分钟）
      int ans = 0; // 做的题数
      int penalty = 0; // 总罚时
      for (int i = 0; i < n; i++) {
          if (sum + a[i] > 710) { // 做题时间总和超过710分钟，break
              break;
          }
          sum += a[i];
          ans++;
          if (sum > 350) { // 做题时间总和超过350分钟，计算罚时
              penalty += sum - 350;
          }
      }

      cout << ans << " " << penalty << endl;
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. 读取输入并排序；  
  2. 循环累加做题时间，判断是否超过总可用时间（710分钟）；  
  3. 计算罚时：做题时间总和超过350分钟的部分；  
  4. 输出题数和罚时。


### 针对各优质题解的片段赏析

#### **题解一（naroto2022）**  
* **亮点**：用`cnt`变量包含前10分钟，直接判断是否超过总比赛时间（720分钟），逻辑简洁。  
* **核心代码片段**：  
  ```cpp
  int cnt = 10; // 前10分钟
  for (int i = 1; i <= n; i++) {
      cnt += a[i];
      if (cnt > 720) break; // 超过总比赛时间
      ans = i;
      if (cnt > 360) { // cnt-10>350，即做题时间总和超过350
          num += cnt - 360;
      }
  }
  ```  
* **代码解读**：  
  `cnt`初始为10（前10分钟），每次加`a[i]`（第`i`题的耗时）。当`cnt`超过720时，break（比赛结束）。`ans`记录做了`i`题。当`cnt`超过360时，`cnt-360`等于做题时间总和超过350的部分，加到`num`（罚时）中。  
* **💡 学习笔记**：用`cnt`包含前10分钟，可以直接判断是否超过总比赛时间，简化了逻辑。


#### **题解二（Crism_qwq）**  
* **亮点**：分两天处理时间，让零点的影响更直观。  
* **核心代码片段**：  
  ```cpp
  long long time1 = 350, time2 = 360; // 第一天350分钟，第二天360分钟
  while (k <= n && a[k] <= time1) {
      time1 -= a[k];
      k++;
  }
  time2 += time1; // 第一天剩余时间补到第二天
  while (k <= n && a[k] <= time2) {
      time2 -= a[k];
      k++;
      sum += 360 - time2; // 罚时=360-time2（第二天剩余时间）
  }
  ```  
* **代码解读**：  
  先做第一天能做完的题（`a[k] <= time1`），然后把第一天剩余的时间（`time1`）加到第二天（`time2`）。再做第二天能做完的题，罚时等于`360 - time2`（因为`time2`是第二天剩余的时间，所以做了的时间是`360 - time2`，即超过零点的时间）。  
* **💡 学习笔记**：分阶段处理时间，更容易理解零点前后的时间分配。


#### **题解三（Eason_AC）**  
* **亮点**：用前缀和数组`s`快速计算前`i`题的时间总和。  
* **核心代码片段**：  
  ```cpp
  int s[107]; // s[i]表示前i题的时间总和
  for (int i = 1; i <= n; i++) {
      if (s[i-1] + a[i] > 710) { // 前i-1题的时间+第i题的时间>710，break
          cout << i-1 << " " << res << endl;
          return 0;
      }
      s[i] = s[i-1] + a[i];
      res += max(0, s[i] - 350); // 罚时=max(0, 前i题时间总和-350)
  }
  ```  
* **代码解读**：  
  `s[i]`是前`i`题的时间总和，`s[i-1] + a[i]`是前`i`题的时间总和。当超过710时，输出前`i-1`题的结果。`res`累加`max(0, s[i]-350)`，即前`i`题的罚时总和。  
* **💡 学习笔记**：前缀和数组可以避免重复累加，让时间计算更高效。


## 5. 算法可视化：像素动画演示 (核心部分)

### 🎮 动画演示主题：《像素探险家的跨年挑战》  
**设计思路**：采用8位像素风格（类似FC红白机游戏），用“探险家”代表Gennady，“宝箱”代表题目，“时间条”代表剩余时间，“罚时数字”代表当前罚时。通过动画展示贪心算法的执行过程，让学习者直观看到“选短时间题”“攒零点提交”“计算罚时”的逻辑。


### 📊 动画帧步骤与交互关键点  
1. **场景初始化**：  
   - 屏幕左侧显示排序后的“宝箱”（蓝色：未做，绿色：已做）；  
   - 屏幕右侧显示“时间条”（从左到右，350分钟处有黄色分界线）；  
   - 屏幕下方显示“罚时数字”（初始为0）和“控制面板”（单步、自动、重置按钮，速度滑块）。  
   - 背景音乐：8位风格的《新年好》。

2. **算法启动**：  
   - 探险家站在第一个宝箱前，点击“开始”按钮，探险家开始“挖宝箱”（动画：探险家挥锄头，宝箱摇晃）。  
   - 每挖一个宝箱，时间条增长（绿色部分），宝箱变成绿色（已做）。

3. **核心步骤演示**：  
   - **零点前**：时间条未超过黄色分界线（350分钟），罚时数字不变（0）。  
   - **零点后**：时间条超过黄色分界线，罚时数字开始跳动（增加），同时播放“咚”的音效（罚时提示）。  
   - **超时**：如果时间条超过710分钟（红色部分），探险家停止挖宝箱，播放“错误”音效（短促的“哔”声）。

4. **交互设计**：  
   - **单步执行**：点击“单步”按钮，探险家挖一个宝箱，动画走一步。  
   - **自动播放**：点击“自动”按钮，探险家按设定速度（通过滑块调整）挖宝箱，适合快速观看整体流程。  
   - **重置动画**：点击“重置”按钮，场景恢复初始状态，重新开始。


### 📝 旁白提示（动画中的文字气泡）  
- “现在挖的是第1个宝箱，耗时30分钟，时间条还没到零点哦！”（零点前）  
- “时间条超过零点了，罚时增加10分钟！”（零点后）  
- “时间不够了，不能再挖了！”（超时）


## 6. 拓展练习与相似问题思考

### 🧠 通用思路/技巧迁移  
贪心算法的核心是“选当前最优”，本题的思路可以迁移到以下场景：  
- **合并果子**（P1090）：将果子按重量从小到大排序，每次合并最轻的两堆，总代价最小。  
- **皇后游戏**（P2123）：将皇后按“a_i + b_i”从小到大排序，总时间最小。  
- **小A的糖果**（P3817）：将糖果按数量从小到大排序，每次选最少的糖果，总数量最大。


### 📚 练习推荐（洛谷）  
1. **洛谷 P1090** - 合并果子  
   🗣️ **推荐理由**：这道题是贪心的经典题目，需要将果子按重量排序，每次合并最轻的两堆，总代价最小。与本题的“选短时间题”思路一致，能帮助你巩固贪心的核心逻辑。  

2. **洛谷 P2123** - 皇后游戏  
   🗣️ **推荐理由**：这道题需要将皇后按“a_i + b_i”排序，总时间最小。与本题的“排序+贪心”思路类似，能帮助你理解贪心策略的正确性证明。  

3. **洛谷 P3817** - 小A的糖果  
   🗣️ **推荐理由**：这道题需要将糖果按数量排序，每次选最少的糖果，总数量最大。与本题的“选短时间题”思路一致，能帮助你熟练掌握贪心的代码实现。


## 7. 学习心得与经验分享 (若有)

### 📝 参考经验（来自 infinities）  
> “我在解决这个问题时，最初没注意到‘前10分钟用来估计难度’这个条件，导致结果错误。后来通过读题解才发现这个隐藏条件，这让我意识到读题时要仔细，不能漏掉任何细节。”  

**点评**：这位作者的经验很典型。在编程问题中，“隐藏条件”（比如前10分钟的扣除）往往是导致错误的关键。读题时要逐句理解，必要时可以画思维导图或流程图，确保没有遗漏。


## 🎉 结语  
本次关于“New Year Contest”的C++解题分析就到这里。希望这份学习指南能帮助大家理解贪心算法的核心逻辑，掌握解题技巧。记住，贪心算法的关键是“选当前最优”，而排序是贪心的基础。下次遇到类似问题时，不妨试试“排序+累加”的思路，相信你能快速解决！💪  

如果有任何疑问，欢迎在评论区留言，我会尽力解答！😊

---
处理用时：185.09秒