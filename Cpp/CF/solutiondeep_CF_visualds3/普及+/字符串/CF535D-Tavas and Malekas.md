# 题目信息

# Tavas and Malekas

## 题目描述

Tavas is a strange creature. Usually "zzz" comes out of people's mouth while sleeping, but string $ s $ of length $ n $ comes out from Tavas' mouth instead.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535D/edec2eae8d180d77009c457fa18d1007b3d9ea05.png)Today Tavas fell asleep in Malekas' place. While he was sleeping, Malekas did a little process on $ s $ . Malekas has a favorite string $ p $ . He determined all positions $ x_{1}&lt;x_{2}&lt;...&lt;x_{k} $ where $ p $ matches $ s $ . More formally, for each $ x_{i} $ ( $ 1<=i<=k $ ) he condition $ s_{xi}s_{xi}+1...\ s_{xi}+|p|-1=p $ is fullfilled.

Then Malekas wrote down one of subsequences of $ x_{1},x_{2},...\ x_{k} $ (possibly, he didn't write anything) on a piece of paper. Here a sequence $ b $ is a subsequence of sequence $ a $ if and only if we can turn $ a $ into $ b $ by removing some of its elements (maybe no one of them or all).

After Tavas woke up, Malekas told him everything. He couldn't remember string $ s $ , but he knew that both $ p $ and $ s $ only contains lowercase English letters and also he had the subsequence he had written on that piece of paper.

Tavas wonders, what is the number of possible values of $ s $ ? He asked SaDDas, but he wasn't smart enough to solve this. So, Tavas asked you to calculate this number for him.

Answer can be very large, so Tavas wants you to print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample test all strings of form "ioioi?" where the question mark replaces arbitrary English letter satisfy.

Here $ |x| $ denotes the length of string x.

Please note that it's possible that there is no such string (answer is 0).

## 样例 #1

### 输入

```
6 2
ioi
1 3
```

### 输出

```
26
```

## 样例 #2

### 输入

```
5 2
ioi
1 2
```

### 输出

```
0
```

# AI分析结果

# 💡 Kay的C++算法解析：Tavas and Malekas 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：字符串（匹配/前缀后缀处理）

🗣️ **初步分析**：  
解决这道题的关键，是**判断模式串在文本串中的重叠位置是否“兼容”**——就像拼图游戏里的两块拼图，重叠的部分必须完全一致才能拼在一起。而要快速判断“重叠部分是否一致”，我们需要用到字符串匹配中的**前缀后缀处理技巧**（比如KMP的border、Z函数或哈希）。  

简单来说，模式串的“前缀”是从开头开始的子串，“后缀”是从结尾开始的子串。如果两个模式串在文本串中重叠，重叠部分其实是前一个模式串的**后缀**和后一个模式串的**前缀**——只有当这两个子串完全相同时，才不会冲突。  

比如样例1中，模式串是`ioi`（长度3），两个位置是1和3：  
- 前一个模式串的后缀（从位置2开始，长度1）是`o`？不，等一下——位置1的模式串是`s[1..3] = "ioi"`，位置3的模式串是`s[3..5] = "ioi"`，重叠部分是`s[3]`（长度1）。这时候需要判断模式串的**前缀1位**（`i`）和**后缀1位**（`i`）是否相同——是的，所以合法！  

**核心算法流程**：  
1. 预处理模式串，得到判断前缀后缀是否匹配的工具（比如Z函数或KMP的next数组）；  
2. 检查所有给定的模式串位置：  
   - 若位置超出文本串长度，直接返回0；  
   - 若相邻位置重叠，用预处理的工具判断重叠部分是否匹配；  
3. 统计未被模式串覆盖的位置数，答案就是`26^未覆盖数`（模1e9+7）。  

**可视化设计思路**：  
我们会用**8位像素风**模拟文本串和模式串的拼接过程——比如文本串是6个像素格子，模式串`ioi`是3个彩色块（比如`i`是蓝色，`o`是黄色）。当放置第二个模式串时，重叠的格子会**闪烁对比**：如果匹配，格子保持颜色并播放“叮”的音效；如果不匹配，格子变红并播放“错误”音效。还会有“单步执行”按钮，让你一步步看重叠判断的过程~


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和算法有效性三个维度，筛选了以下4星以上的优质题解，帮你快速抓住核心！
</eval_intro>

**题解一：Z函数解法（作者：tuzhewen）**  
* **点评**：  
  这个解法用Z函数（求每个位置开始的最长前缀匹配）处理重叠判断，思路非常直接！代码里先计算模式串的Z数组，然后遍历每个位置：如果相邻位置重叠，就用Z数组判断“后一个模式串的起始位置相对于前一个的偏移”对应的最长前缀匹配是否≥重叠长度。比如偏移是`y-x`，重叠长度是`x+lenp - y`，只要Z数组在`y-x`位置的值≥重叠长度，就说明前缀和后缀匹配。代码里的`check`函数完美实现了这个逻辑，而且用差分数组统计未覆盖位置，效率很高~  

**题解二：KMP解法（作者：ycyaw）**  
* **点评**：  
  这个解法用KMP的next数组（求每个位置的最长border）处理重叠判断，非常严谨！作者指出了一个常见错误：不能只看最长border，要把所有可能的border都标记出来（比如`ababab`的border是6、4、2）。代码里用`vis`数组记录所有合法的重叠长度，只要重叠长度在`vis`里，就说明前缀后缀匹配。这种方法完全避免了“漏判”，很适合新手学习KMP的深层应用~  

**题解三：哈希解法（作者：Computer1828）**  
* **点评**：  
  这个解法用字符串哈希直接比较前缀和后缀，思路最“直观”！作者预处理了模式串的前缀哈希和后缀哈希，当相邻位置重叠时，直接计算重叠部分的哈希值并比较——如果相等，就说明匹配。虽然哈希可能被卡，但作者用了双哈希（两个模数），安全性很高。代码里的`pre`和`suf`数组分别存储前缀和后缀哈希，`vis`数组标记覆盖位置，逻辑清晰易懂~  


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键，在于突破三个“容易卡壳”的点。结合优质题解的经验，我帮你梳理了应对策略：
</difficulty_intro>

1.  **难点1：如何判断重叠部分是否匹配？**  
    * **分析**：重叠部分是前一个模式串的后缀、后一个模式串的前缀。要判断两者是否相同，有三种方法：  
      - **KMP的next数组**：找出模式串的所有border（前缀等于后缀的长度），只要重叠长度是border之一，就匹配；  
      - **Z函数**：计算模式串每个位置开始的最长前缀匹配，若偏移位置的Z值≥重叠长度，就匹配；  
      - **字符串哈希**：直接计算前缀和后缀的哈希值，相等则匹配。  
    * 💡 **学习笔记**：选自己最熟悉的方法，但要理解“前缀后缀匹配”的本质！

2.  **难点2：如何统计未被覆盖的位置？**  
    * **分析**：模式串的覆盖范围是`[pos_i, pos_i + lenp - 1]`。统计未被覆盖的位置，有两种方法：  
      - **差分数组**：用`sum[pos_i]++`、`sum[pos_i + lenp]--`，最后遍历计算前缀和，`sum[i] == 0`的位置就是未覆盖；  
      - **直接计算**：记录上一个模式串的结束位置，计算当前位置与上一个结束位置的间隔。  
    * 💡 **学习笔记**：差分数组更通用，适合处理多个区间的覆盖问题！

3.  **难点3：如何处理边界条件？**  
    * **分析**：常见的边界条件有：  
      - `m=0`（没有模式串）：直接返回`26^n`；  
      - 模式串结束位置超过`n`：返回0；  
      - 相邻位置重叠但不匹配：返回0。  
    * 💡 **学习笔记**：写代码前先列全所有边界条件，避免遗漏！

### ✨ 解题技巧总结
- **技巧A：预处理优先**：不管用KMP、Z函数还是哈希，先预处理模式串的信息，避免重复计算；  
- **技巧B：差分统计覆盖**：用差分数组快速统计未被覆盖的位置，比暴力遍历高效；  
- **技巧C：快速幂算结果**：`26^k`用快速幂计算，避免超时（`k`最多是1e6，快速幂是`O(logk)`）。  


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**Z函数解法的通用核心代码**——它综合了优质题解的思路，清晰易懂，适合入门！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自题解一（tuzhewen），用Z函数处理重叠判断，差分统计未覆盖位置，逻辑完整且高效。
* **完整核心代码**：
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  const int N = 1e6 + 5, MOD = 1e9 + 7;

  // 快速幂：计算a^b mod MOD
  long long qpow(long long a, long long b) {
      long long res = 1;
      while (b) {
          if (b & 1) res = res * a % MOD;
          a = a * a % MOD;
          b >>= 1;
      }
      return res;
  }

  // 计算Z数组：z[i]表示s[i..n-1]与s[0..n-1]的最长公共前缀长度
  void get_z(const string &s, vector<int> &z) {
      int n = s.size();
      z.resize(n, 0);
      z[0] = n; // 自身与自身的LCP是长度n
      int L = 0, R = 0;
      for (int i = 1; i < n; ++i) {
          if (i <= R) z[i] = min(z[i - L], R - i + 1);
          while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
          if (i + z[i] - 1 > R) {
              L = i;
              R = i + z[i] - 1;
          }
      }
  }

  int main() {
      int n, m;
      string p;
      cin >> n >> m >> p;
      int lenp = p.size();

      // 处理m=0的情况
      if (m == 0) {
          cout << qpow(26, n) << endl;
          return 0;
      }

      // 计算Z数组
      vector<int> z;
      get_z(p, z);

      // 读取位置（注意题目中的位置是1-based，转成0-based）
      vector<int> pos(m);
      for (int i = 0; i < m; ++i) {
          cin >> pos[i];
          pos[i]--; // 转0-based
      }

      // 检查相邻位置是否合法
      bool valid = true;
      for (int i = 1; i < m; ++i) {
          int x = pos[i-1], y = pos[i];
          if (x + lenp > y) { // 重叠
              int overlap = x + lenp - y; // 重叠长度
              int offset = y - x; // 后一个模式串相对于前一个的偏移
              if (z[offset] < overlap) { // 前缀后缀不匹配
                  valid = false;
                  break;
              }
          }
      }

      if (!valid) {
          cout << 0 << endl;
          return 0;
      }

      // 用差分统计覆盖位置
      vector<int> sum(n + 2, 0); // sum[i]表示位置i的覆盖次数变化
      for (int x : pos) {
          sum[x]++;
          sum[x + lenp]--;
      }

      // 计算未被覆盖的位置数
      int cnt = 0;
      int current = 0;
      for (int i = 0; i < n; ++i) {
          current += sum[i];
          if (current == 0) cnt++;
      }

      cout << qpow(26, cnt) << endl;
      return 0;
  }
  ```
* **代码解读概要**：  
  1. **快速幂**：计算`26^cnt`，避免超时；  
  2. **Z函数**：预处理模式串的Z数组，用于判断前缀后缀匹配；  
  3. **位置处理**：将输入的1-based位置转成0-based，方便计算；  
  4. **重叠判断**：遍历相邻位置，用Z数组判断重叠部分是否匹配；  
  5. **差分统计**：用`sum`数组统计每个位置的覆盖次数，最后计算未被覆盖的位置数；  
  6. **结果计算**：输出`26^cnt`模1e9+7的结果。


<code_intro_selected>
接下来，我们剖析几个优质题解的核心片段，看看它们的“亮点”！
</code_intro_selected>

**题解一：Z函数解法（作者：tuzhewen）**  
* **亮点**：用Z函数直接判断重叠部分的前缀后缀匹配，逻辑简洁。
* **核心代码片段**：
  ```cpp
  bool check(int x, int y) {
      if (y - x >= lenp) return true; // 不重叠，合法
      return z[y - x] >= x + lenp - y; // 重叠长度是x+lenp-y，判断Z值是否≥它
  }
  ```
* **代码解读**：  
  这个`check`函数是整个解法的“心脏”！`x`是前一个模式串的位置，`y`是后一个的位置：  
  - 如果`y - x >= lenp`，说明两个模式串不重叠，直接合法；  
  - 否则，重叠长度是`x + lenp - y`（比如x=0，y=2，lenp=3，重叠长度是0+3-2=1）；  
  - `z[y - x]`是模式串从位置`y-x`开始的最长前缀匹配长度——如果这个长度≥重叠长度，说明前缀和后缀匹配！
* 💡 **学习笔记**：Z函数的本质是“每个位置的最长前缀匹配”，刚好用来解决“前缀后缀是否匹配”的问题~

**题解二：KMP解法（作者：ycyaw）**  
* **亮点**：用KMP的next数组找出所有合法的border，避免漏判。
* **核心代码片段**：
  ```cpp
  // 计算next数组（border数组）
  int j = 0;
  p[1] = 0;
  for (int i = 2; i <= len; ++i) {
      while (j > 0 && s[i] != s[j+1]) j = p[j];
      if (s[i] == s[j+1]) j++;
      p[i] = j;
  }
  // 标记所有合法的border长度
  for (int i = len; i; i = p[i]) vis[i] = 1;
  ```
* **代码解读**：  
  1. **next数组**：`p[i]`表示`s[1..i]`的最长border长度（前缀等于后缀的最长长度）；  
  2. **标记border**：从`len`开始，不断跳`p[i]`，把所有可能的border长度标记为1（比如`ababab`的border是6、4、2，都会被标记）。  
  这样，当重叠长度是`overlap`时，只要`vis[overlap] == 1`，就说明前缀后缀匹配！
* 💡 **学习笔记**：KMP的next数组不仅能用于字符串匹配，还能找出所有可能的前缀后缀匹配长度~

**题解三：哈希解法（作者：Computer1828）**  
* **亮点**：用双哈希直接比较前缀和后缀，思路直观。
* **核心代码片段**：
  ```cpp
  // 预处理前缀哈希和后缀哈希
  pre[0] = 0;
  for (int i = 1; i <= len; ++i) 
      pre[i] = (pre[i-1] * 26 + (p[i] - 'a')) % mm;
  suf[len+1] = 0;
  for (int i = len; i >= 1; --i) 
      suf[i] = (suf[i+1] + 1LL * (p[i] - 'a') * pw[len - i]) % mm;
  // 判断重叠部分是否匹配
  if (suf[a[i] - a[i-1] + 1] != pre[a[i-1] + len - a[i]]) 
      return printf("0"), 0;
  ```
* **代码解读**：  
  1. **前缀哈希**：`pre[i]`是`s[1..i]`的哈希值（基数26）；  
  2. **后缀哈希**：`suf[i]`是`s[i..len]`的哈希值（基数26的幂次）；  
  3. **比较**：当重叠长度是`overlap = a[i-1] + len - a[i]`时，前一个模式串的后缀是`s[a[i]..a[i-1]+len]`，对应模式串的`s[1..overlap]`（前缀）；后一个模式串的前缀是`s[a[i]..a[i]+len-1]`，对应模式串的`s[overlap+1..len]`（后缀）？不，等一下——作者这里的逻辑是：重叠部分是模式串的前缀`overlap`位和后缀`overlap`位，所以直接比较`pre[overlap]`（前缀哈希）和`suf[len - overlap + 1]`（后缀哈希）是否相等！
* 💡 **学习笔记**：哈希的本质是“把字符串转成数字”，比较数字比比较字符串快得多~  


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地理解“重叠判断”的过程，我设计了一个**8位像素风的动画**——像玩FC游戏一样，看模式串如何“拼”进文本串！
</visualization_intro>

### **动画演示主题**：像素拼图游戏——模式串的“兼容测试”
### **核心演示内容**：模拟样例1的过程（文本串长度6，模式串`ioi`，位置1和3）

### **设计思路**：
用**8x8像素的网格**表示文本串（每个格子代表一个字符），模式串`ioi`用三种颜色表示：`i`是蓝色（#00F），`o`是黄色（#FF0）。动画会一步步展示：
1. 放置第一个模式串（位置1）：蓝色、黄色、蓝色的格子依次亮起；
2. 放置第二个模式串（位置3）：先显示“预放置”状态（半透明），然后检查重叠部分（位置3的格子）；
3. 重叠判断：如果模式串的前缀1位（蓝色）和后缀1位（蓝色）匹配，半透明格子变成实色，播放“叮”的音效；如果不匹配，格子变红，播放“错误”音效。

### **动画帧步骤与交互关键点**：
1. **场景初始化**：  
   - 屏幕左侧是6个像素格子（1~6号），右侧是“控制面板”（开始/暂停、单步、重置按钮，速度滑块）；  
   - 背景是FC风格的深蓝色，控制面板是浅灰色，按钮是橙色；  
   - 8位风格的背景音乐（轻快的钢琴声）开始播放。

2. **第一步：放置第一个模式串**：  
   - 格子1~3依次亮起：1号变蓝，2号变黄，3号变蓝；  
   - 伴随“滴”的音效（每个格子亮起时一次）。

3. **第二步：预放置第二个模式串**：  
   - 格子3~5变成半透明的蓝色、黄色、蓝色；  
   - 屏幕下方弹出提示框：“检查重叠部分（格子3）”。

4. **第三步：重叠判断**：  
   - 格子3的半透明蓝色变成实色（匹配成功）；  
   - 播放“叮”的音效，提示框变成：“重叠部分匹配！”。

5. **第四步：统计未覆盖位置**：  
   - 格子6保持白色（未被覆盖），屏幕右侧显示：“未覆盖位置数：1”；  
   - 最后显示结果：“26^1 = 26”，播放“胜利”音效。

### **交互设计**：
- **单步执行**：点击“单步”按钮，一步步看每个步骤；  
- **自动播放**：拖动速度滑块调整播放速度（最慢1秒/步，最快0.1秒/步）；  
- **重置**：点击“重置”按钮，回到初始状态重新演示。

### **为什么这么设计？**
- **像素风格**：唤起复古游戏的回忆，降低学习的“距离感”；  
- **颜色与音效**：用颜色区分不同字符，用音效强化关键操作（比如匹配成功的“叮”声）；  
- **分步演示**：把复杂的“重叠判断”拆成小步骤，让你看清楚每一步的逻辑！


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了“前缀后缀匹配”的技巧后，你可以解决很多类似的字符串问题！
</similar_problems_intro>

### **通用思路迁移**：
- **场景1**：判断一个字符串是否是另一个字符串的重复子串（比如`ababab`是`ab`的重复）；  
- **场景2**：找出字符串中所有可能的“回文前缀”（比如`abcba`的回文前缀是`a`、`abcba`）；  
- **场景3**：处理多个模式串的重叠匹配（比如本题的延伸）。

### **洛谷练习推荐**：
1. **洛谷 P3375** - KMP字符串匹配  
   🗣️ **推荐理由**：这是KMP的模板题，帮你巩固next数组的用法！  
2. **洛谷 P5410** - 扩展KMP（Z函数）  
   🗣️ **推荐理由**：这是Z函数的模板题，帮你熟悉Z数组的计算！  
3. **洛谷 P1368** - 最小表示法  
   🗣️ **推荐理由**：这题用到了前缀后缀的思想，帮你拓展思维！  


## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中，我发现了几个非常有用的“踩坑经验”，帮你避免走弯路：
</insights_intro>

> **经验1（来自ycyaw）**：“不要只看最长border，要把所有可能的border都标记出来！比如`ababab`的border是6、4、2，重叠长度为4时也需要判断。”  
> **点评**：这个经验太重要了！很多新手会误以为只有最长border才有效，但实际上所有可能的border都要考虑——否则会漏判合法的重叠情况！

> **经验2（来自米奇）**：“一定要特判`m=0`的情况！否则会WA第55个点。”  
> **点评**：边界条件是很多人的“死穴”——写代码前先列全所有可能的边界情况，比如`m=0`、模式串超出文本串长度等！

> **经验3（来自CaiXY06）**：“哈希容易被卡，建议用双哈希或三哈希！”  
> **点评**：哈希的安全性取决于模数和基数的选择——用双哈希（两个不同的模数）可以大大降低被卡的概率！  


<conclusion>
本次关于“Tavas and Malekas”的分析就到这里啦！这道题的核心是“前缀后缀匹配”，不管用KMP、Z函数还是哈希，本质都是一样的——判断两个子串是否相同。记住：**预处理优先，边界要全，统计要高效**！  

下次遇到字符串问题时，不妨想想今天学的技巧——比如用Z函数判断前缀匹配，用差分统计覆盖位置。编程的乐趣就在于把复杂的问题拆成一个个小步骤，然后用代码逐一解决！💪
</conclusion>

---
处理用时：156.65秒