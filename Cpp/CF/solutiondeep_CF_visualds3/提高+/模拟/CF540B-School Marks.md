# 题目信息

# School Marks

## 题目描述

Little Vova studies programming in an elite school. Vova and his classmates are supposed to write $ n $ progress tests, for each test they will get a mark from 1 to $ p $ . Vova is very smart and he can write every test for any mark, but he doesn't want to stand out from the crowd too much. If the sum of his marks for all tests exceeds value $ x $ , then his classmates notice how smart he is and start distracting him asking to let them copy his homework. And if the median of his marks will be lower than $ y $ points (the definition of a median is given in the notes), then his mom will decide that he gets too many bad marks and forbid him to play computer games.

Vova has already wrote $ k $ tests and got marks $ a_{1},...,a_{k} $ . He doesn't want to get into the first or the second situation described above and now he needs to determine which marks he needs to get for the remaining tests. Help him do that.

## 说明/提示

The median of sequence $ a_{1} $ , ..., $ a_{n} $ where $ n $ is odd (in this problem $ n $ is always odd) is the element staying on $ (n+1)/2 $ position in the sorted list of $ a_{i} $ .

In the first sample the sum of marks equals 3 + 5 + 4 + 4 + 1 = 17, what doesn't exceed 18, that means that Vova won't be disturbed by his classmates. And the median point of the sequence {1, 3, 4, 4, 5} equals to 4, that isn't less than 4, so his mom lets him play computer games.

Please note that you do not have to maximize the sum of marks or the median mark. Any of the answers: "4 2", "2 4", "5 1", "1 5", "4 1", "1 4" for the first test is correct.

In the second sample Vova got three '5' marks, so even if he gets two '1' marks, the sum of marks will be 17, that is more than the required value of 16. So, the answer to this test is "-1".

## 样例 #1

### 输入

```
5 3 5 18 4
3 5 4
```

### 输出

```
4 1
```

## 样例 #2

### 输入

```
5 3 5 16 4
5 5 5
```

### 输出

```
-1
```

# AI分析结果

# 💡 Kay的C++算法解析：School Marks 深入学习指南 💡

<introduction>
今天我们来一起分析“School Marks”这道C++编程题。这道题结合了**贪心策略**和**中位数条件转化**，需要我们用“最小代价满足约束”的思路解决问题。本指南会帮你梳理核心逻辑、识别难点，并通过像素动画直观理解算法！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法（Greedy）

🗣️ **初步分析**：
解决“School Marks”的关键是**用最少的分数总和满足两个约束**：  
1. 总分不超过x；  
2. 中位数不低于y（中位数是排序后第$(n+1)/2$位的数）。  

贪心算法的核心思想像“捡最便宜的东西满足需求”——为了让总和最小，我们要尽可能填**最小的合法分数（1分）**，但必须保证有足够多的分数≥y（否则中位数会低于y）。具体来说：  
- 中位数要≥y → 排序后至少有$(n+1)/2$个数≥y（因为中位数是第$(n+1)/2$位，前面的数可以更小，但后面的数必须≥它）；  
- 剩余的分数中，先填足够的y来满足中位数条件，剩下的都填1（这样总和最小）。  

**核心算法流程**：  
1. 统计已考分数中≥y的数量（记为cnt）；  
2. 计算需要补充的≥y的数量：$t = max(0, (n+1)/2 - cnt)$（如果已够则t=0）；  
3. 剩余的$(n-k-t)$个分数填1，总和就是已考分数之和 + t*y + (n-k-t)*1；  
4. 检查总和是否≤x，且补充的y数量不超过剩余位置（否则无解）。  

**可视化设计思路**：  
我们会用**8位像素风**模拟分数填充过程：  
- 用不同颜色的像素块表示已考分数（蓝色）、待填的1（灰色）、待填的y（黄色）；  
- 实时显示当前总和（红色数字）和≥y的数量（绿色数字）；  
- 每填充一个分数，播放“滴”的像素音效；满足条件时播放“叮”的胜利音效，否则播放“ buzz”的失败音效。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，帮你快速掌握核心逻辑！
</eval_intro>

**题解一：来源：OIer_Hhy**  
* **点评**：这份题解的思路非常“直接”——先算已有的≥y的数量，再算需要补充的y的数量，最后检查总和。代码结构清晰，变量名（如cnt、sum、t）含义明确，边界条件（比如sum+(n-k)>x的提前判断）处理得很严谨。尤其值得学习的是**“先假设全部填1看是否超总和”**的预处理，避免了无效计算。

**题解二：来源：Graphcity**  
* **点评**：这题解的亮点是**输入优化**（用read函数代替cin，加快读取速度）和**数组模拟填充**（直接用a数组存储所有分数，最后输出剩余部分）。思路和题解一一致，但代码更贴近竞赛风格，适合学习“如何写高效的竞赛代码”。

**题解三：来源：ylch**  
* **点评**：这份题解的“宏定义”技巧很巧妙（用NOTOK代替重复的输出-1并返回），减少了代码冗余。同时，作者详细解释了中位数的概念，帮新手理清了“为什么需要$(n+1)/2$个≥y的数”，非常适合入门学习。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键是**把“中位数条件”转化为“数量条件”**，并学会用贪心找最小总和。以下是三个核心难点及解决策略：
</difficulty_intro>

1. **关键点1：如何将中位数条件转化为可计算的数量？**  
   * **分析**：中位数是排序后第$(n+1)/2$位的数，要让它≥y，必须保证至少有$(n+1)/2$个数≥y（比如n=5，需要至少3个数≥y，这样第3位才会≥y）。如果已考的≥y的数量加上剩余位置数都不够$(n+1)/2$，直接无解。  
   * 💡 **学习笔记**：中位数问题常转化为“数量约束”，要记住“奇数长度的数组需要至少$(n+1)/2$个≥中位数的数”。

2. **关键点2：如何用贪心找最小总和？**  
   * **分析**：要总和最小，剩余分数应尽可能填1，但必须先填足够的y满足中位数条件。比如需要补充t个y，剩下的都填1——这样既满足中位数，又让总和最小。  
   * 💡 **学习笔记**：贪心的核心是“优先满足硬约束（中位数），再最小化代价（总和）”。

3. **关键点3：如何判断无解？**  
   * **分析**：无解有三种情况：  
     1. 剩余位置全填1的总和已超x（sum + (n-k) > x）；  
     2. 即使剩余位置全填y，也不够$(n+1)/2$个≥y的数（cnt + (n-k) < (n+1)/2）；  
     3. 填t个y和剩下的1后的总和超x（sum + t*y + (n-k-t)*1 > x）。  
   * 💡 **学习笔记**：先判断“不可能满足的情况”可以提前终止程序，避免无效计算。

### ✨ 解题技巧总结
- **条件转化**：把“中位数≥y”转化为“至少需要m个≥y的数”（m=(n+1)/2）；  
- **贪心策略**：优先填满足约束的最小可能值（y和1）；  
- **边界预处理**：先检查“全填1是否超总和”和“全填y是否够数量”，快速判断无解。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用核心实现**，它综合了优质题解的思路，代码简洁且覆盖所有情况：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自对多个优质题解的整合，逻辑清晰，覆盖所有边界条件。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  using namespace std;

  int main() {
      int n, k, p, x, y;
      cin >> n >> k >> p >> x >> y;
      
      int sum = 0, cnt = 0; // sum:已考总分, cnt:已考≥y的数量
      for (int i = 0; i < k; ++i) {
          int a;
          cin >> a;
          sum += a;
          if (a >= y) cnt++;
      }
      
      int m = (n + 1) / 2; // 需要的≥y的总数
      // 情况1：即使剩余全填y，也不够m个
      if (cnt + (n - k) < m) {
          cout << -1 << endl;
          return 0;
      }
      // 情况2：剩余全填1的总和已超x
      if (sum + (n - k) > x) {
          cout << -1 << endl;
          return 0;
      }
      
      int t = max(0, m - cnt); // 需要补充的y的数量
      sum += t * y + (n - k - t) * 1; // 计算总分
      
      // 情况3：补充后总和超x
      if (sum > x) {
          cout << -1 << endl;
          return 0;
      }
      
      // 输出结果
      for (int i = 0; i < n - k - t; ++i) cout << 1 << " ";
      for (int i = 0; i < t; ++i) cout << y << " ";
      cout << endl;
      
      return 0;
  }
  ```
* **代码解读概要**：  
  1. 读取输入并统计已考分数的总和和≥y的数量；  
  2. 计算需要的≥y的总数m=(n+1)/2；  
  3. 依次检查三种无解情况；  
  4. 计算需要补充的y的数量t，再计算总分；  
  5. 输出剩余的分数（先填1，再填y）。

---

<code_intro_selected>
接下来看优质题解的**核心片段**，学习它们的巧妙之处：
</code_intro_selected>

**题解一：来源：OIer_Hhy**
* **亮点**：提前判断“全填1是否超总和”，避免无效计算。
* **核心代码片段**：
  ```cpp
  if(sum+(n-k)>x){ // 剩余全填1的总和已超x
      puts("-1");
      return 0;
  }
  ```
* **代码解读**：  
  这行代码的意思是“如果已考分数加上剩余位置全填1的总和已经超过x，直接无解”。因为1是最小的分数，连全填1都超的话，填更大的数肯定也超——这是一个很聪明的**预处理**，减少了后续计算。
* 💡 **学习笔记**：预处理“最小可能的总和”可以快速排除无解情况。

**题解二：来源：Graphcity**
* **亮点**：用read函数优化输入，适合大数据量的竞赛场景。
* **核心代码片段**：
  ```cpp
  inline int read() {
      char ch=getchar();
      int f=1,x=0;
      while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
      while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
      return x*f;
  }
  ```
* **代码解读**：  
  这个read函数直接读取字符并转换为整数，比cin快很多（竞赛中常用来处理大数据）。比如输入“123”，它会依次读入'1'→'2'→'3'，计算x=1*10+2=12，再+3=15，返回15。
* 💡 **学习笔记**：竞赛中输入量大时，用getchar()实现的read函数更高效。

**题解三：来源：ylch**
* **亮点**：用宏定义简化重复代码，减少冗余。
* **核心代码片段**：
  ```cpp
  #define NOTOK return puts("-1"), 0;
  ...
  if (num+n-k < sum) NOTOK
  if (ans > x) NOTOK
  ```
* **代码解读**：  
  宏定义NOTOK代替了“输出-1并返回”的重复代码，让代码更简洁。比如当num+n-k < sum时，直接调用NOTOK，相当于执行`return puts("-1"), 0;`（逗号表达式，先执行puts，再返回0）。
* 💡 **学习笔记**：重复的代码可以用宏定义或函数简化，提高可读性。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“贪心填充分数”的过程，我设计了一个**8位像素风动画**，像玩FC游戏一样看算法运行！
</visualization_intro>

### 动画演示主题：《分数填充大挑战》
**风格**：仿FC红白机风格，用16色调色板（红、蓝、灰、黄为主），背景是像素化的教室。

### 核心演示内容
1. **初始化场景**：  
   - 屏幕左侧显示**已考分数条**（蓝色像素块，每个块显示分数）；  
   - 中间是**待填分数槽**（灰色空槽，共n-k个）；  
   - 右侧显示**状态面板**：总和（红色数字）、≥y的数量（绿色数字）、需要的y数量（黄色数字m）。  
   - 底部有**控制按钮**：单步执行、自动播放、重置。

2. **算法运行步骤**：  
   - **步骤1**：统计已考分数的总和和cnt（蓝色块闪烁，状态面板更新）；  
   - **步骤2**：计算m=(n+1)/2（黄色数字闪烁）；  
   - **步骤3**：检查无解情况（如果cnt+(n-k)<m，待填槽变红，播放“buzz”音效；如果sum+(n-k)>x，总和数字变红，播放“buzz”音效）；  
   - **步骤4**：填充分数（先填t个黄色块（y），再填灰色块（1），每填一个块播放“滴”音效，状态面板实时更新总和和cnt）；  
   - **步骤5**：完成填充（如果总和≤x，待填槽变绿，播放“叮”的胜利音效；否则变红，播放“buzz”音效）。

### 游戏化元素
- **AI自动演示**：点击“自动播放”，动画会像“贪吃蛇AI”一样自动填充分数，你可以观察每一步的变化；  
- **关卡奖励**：每完成一次填充（无论成功与否），会弹出像素星星（成功）或问号（失败），积累5颗星星可以解锁“快速填充”模式；  
- **音效设计**：  
  - 填充1：“滴”（低频方波）；  
  - 填充y：“叮”（高频方波）；  
  - 成功：“当当当”（三音上扬）；  
  - 失败：“ buzz”（短噪声）。

### 设计理由
- **像素风格**：复古游戏感让学习更轻松，减少“算法很抽象”的压力；  
- **状态面板**：实时显示关键数据，帮你理解“每一步为什么这么做”；  
- **音效提示**：用声音强化关键操作，比如填充y时的“叮”声，让你快速记住“y是满足中位数的关键”。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
贪心算法的核心是“每次选当前最优”，本题的思路可以迁移到很多场景。比如：
</similar_problems_intro>

### 通用思路迁移
- **资源分配**：用最少的资源满足约束（比如本题用最少的分数总和满足中位数和总分约束）；  
- **数量约束**：将“位置条件”（如中位数）转化为“数量条件”（如需要m个≥y的数）；  
- **预处理剪枝**：提前判断不可能的情况，减少计算量。

### 洛谷练习推荐
1. **洛谷 P1090** - 合并果子  
   * 🗣️ **推荐理由**：经典贪心问题，用优先队列找最小的两堆果子合并，练习“每次选最优”的思路。  
2. **洛谷 P1208** - 混合牛奶  
   * 🗣️ **推荐理由**：需要用最少的钱买足够的牛奶，练习“按单价排序，优先买便宜的”的贪心策略。  
3. **洛谷 P1803** - 线段覆盖  
   * 🗣️ **推荐理由**：选择最多的不重叠线段，练习“按结束时间排序，优先选早结束的”的贪心思路。  


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中提到的**“预处理剪枝”**和**“条件转化”**技巧非常有用，比如：
</insights_intro>

> **参考经验（来自OIer_Hhy）**：“我在写代码时，先判断了‘剩余全填1是否超总和’，这样可以提前终止，避免后面的无效计算。”  
> **点评**：这个经验很重要！预处理“最小可能的情况”（比如全填1）可以快速排除无解，减少代码运行时间，也让逻辑更清晰。

> **参考经验（来自ylch）**：“中位数的条件转化是关键，我一开始没搞懂为什么需要m个≥y的数，后来画了个例子（n=5，需要3个≥y的数）才明白。”  
> **点评**：遇到抽象的条件（如中位数），可以用**小例子模拟**（比如n=5，填3个y，2个1，排序后中位数是y），这样更容易理解。


<conclusion>
本次关于“School Marks”的分析就到这里！这道题的核心是**贪心策略+条件转化**，只要掌握“用最少的代价满足约束”的思路，就能轻松解决。记住：遇到中位数问题，先转化为数量约束；遇到总和最小问题，优先填最小的合法值。下次我们再一起探索更多贪心问题！💪
</conclusion>

---
处理用时：79.38秒