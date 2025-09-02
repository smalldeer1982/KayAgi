# 题目信息

# [BalticOI 2008] 选举

## 题目描述

The citizens of Byteland have recently been voting in the parliamentary elections. Now, when the results
have been published, the parties have to decide on a coalition to form the government.

Each party received a certain number of seats in the parliament. The coalition must be a subset of the
parties such that together they have strictly more than half of all the seats in the parliament. It is desirable for
the coalition to have as many seats as possible, to ensure they can still pass their proposed laws even if a few
of their members are absent from a parliament session.
A coalition is called redundant if one of its parties can be removed with the remaining ones still having
more than half of the seats in the parliament. Of course, such a removable party would effectively have no
power — the other members of the coalition would be able to force the laws regardless of its opinion.


Write a program that:

- reads the election results from the standard input,
- finds a non-redundant coalition that has the maximal possible number of seats in the parliament,
- writes the description of this coalition to the standard output.

### Input

The first line of the standard input contains one integer $n\ (1\le n\le 300)$ — the number of parties that participated in the elections. The parties are numbered from $1$ to $n$.

The second line contains n nonnegative integers $a_1,\dots,a_n$, separated by single spaces, where $a_i$
is the
number of seats received by the $i$-th party. You may assume that the total number of seats in the parliament
will be positive and lower or equal to $100000$.

Additionally, in test cases worth $40\%$ of points, the number of parties will not exceed $20$.

### Output

The first line of the standard output should contain one integer $k$ — the number of parties in a non-redundant
coalition which has the maximal number of seats.
The second line should contain $k$ distinct integers separated by single spaces — the numbers of parties
that form the coalition.

If there are several non-redundant coalitions with the maximal number of seats, you may output any of
them. The member parties can be listed in any order.

### 题目翻译

Byteland 国的居民最近一直为议会选举投票。现在，当结果公布的时候，党派不得不决定联合组建政府。 

每个党派都会获得议会中的一定席位。联合政府由这些党派中的一部分组成，他们在议会中的席位数之和**严格大于**总席位数的一半。对于联合政府来说，席位越多越好。

一个**过剩**的联合政府是指联合政府中的一个党派被移出后，剩余的联合政府在国会中仍有过半数的席位。

请写一个程序能够：

-    读取选举结果；
-    找到一个在议会中有着**最大可能席位数**且**不过剩**的联合政府；
-    输出这个联合政府的描述。


## 说明/提示

对于 $40\%$ 的数据，$n\le 20$；

对于全部数据，$1\le n\le 300$。

## 样例 #1

### 输入

```
4
1 3 2 4```

### 输出

```
2
2 4```

# AI分析结果

# 💡 Kay的C++算法解析：[BalticOI 2008] 选举 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（01背包变种）+ 贪心策略  

🗣️ **初步分析**：  
解决“选举”问题的关键，是找到一个**非冗余**且**席位最多**的联合政府。非冗余的意思是：去掉联合政府中的任何一个党派，剩下的席位就不再超过总席位的一半。这相当于要求联合政府中的每个党派的席位，都必须**大于**“联合政府总席位减去总席位的一半”（比如总席位10，联合政府7席，那么每个党派的席位必须>7-5=2，这样去掉任何一个，剩下的都≤5）。  

怎么高效找到这样的联合政府？我们可以把问题转化为**带约束的01背包问题**：  
- 每个党派是一个“物品”，重量是它的席位。  
- 我们要选一组物品，使得总重量**严格大于总席位的一半**（满足联合政府条件），且总重量尽可能大（席位最多）。  
- 约束条件：每个选中的物品的重量，必须**大于**“总重量减去总席位的一半”（非冗余）。  

**核心技巧**：将党派按席位**从大到小排序**，然后用01背包求解。排序的作用是**消除后效性**——因为大的党派先选，当加入小党派时，前面的总重量一定≤总席位的一半（否则无法满足约束），这样就能保证所有选中的党派都满足非冗余条件。  

**可视化设计思路**：  
我们可以做一个“像素背包探险”动画：  
- 屏幕左侧是排序后的党派（像素方块，大小代表席位），右侧是“背包”（显示当前总席位）。  
- 每次选一个党派，方块会“跳”进背包，同时显示当前总席位是否满足条件（比如超过总席位的一半时，背包会闪烁绿色）。  
- 用不同颜色标记选中的党派（比如蓝色），未选中的（灰色），并实时显示约束条件（比如当前总席位-总席位的一半，判断选中的党派是否满足）。  
- 加入“单步执行”“自动播放”按钮，以及“胜利音效”（当找到最优解时）。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面，筛选了以下3份优质题解（评分≥4星）：
</eval_intro>

**题解一：来源：CodyTheWolf（赞：2）**  
* **点评**：这份题解的思路非常巧妙，用**排序+一维01背包**解决了非冗余问题。排序后按从大到小的顺序处理党派，保证了约束条件的满足。代码简洁（仅30行），用`bag`数组记录是否可达某个总席位，然后回溯路径。特别是`bag[k] = i`的设计，巧妙记录了到达`k`席位时选的最后一个党派，方便回溯。  

**题解二：来源：Irisany（赞：1）**  
* **点评**：此题解用`bitset`优化了背包的状态记录，空间效率极高（`bitset`将状态压缩为二进制位）。代码中`b[v]`记录了选哪些党派能达到`v`席位，通过`set`操作标记选中的党派。这种方法不仅快，而且容易理解，适合处理大规模数据。  

**题解三：来源：Hope2075（赞：1）**  
* **点评**：这份题解用二维`pr`数组（`char`类型）记录状态转移（1表示不选当前党派，2表示选），空间占用小（302×1e5=3e7字节，约30MB）。通过`pr`数组回溯路径，逻辑清晰，适合初学者理解状态转移的过程。  


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这个问题的核心难点在于**将非冗余条件转化为可计算的约束**，以及**高效求解带约束的背包问题**。结合优质题解，我总结了3个关键思考方向：
</difficulty_intro>

### 1.  **关键点1：如何将非冗余条件转化为数学约束？**  
* **分析**：非冗余条件要求“去掉任何一个党派后，剩下的席位≤总席位的一半”。假设联合政府总席位为`k`，总席位为`s`，则对每个选中的党派`a_i`，必须满足`k - a_i ≤ s/2` → `a_i ≥ k - s/2`。由于`k > s/2`（联合政府条件），所以`k - s/2 < k/2`，即每个选中的党派的席位必须大于`k`的一半？不对，比如`k=7`，`s=10`，`s/2=5`，则`k - s/2=2`，所以`a_i ≥2`。这时候`a_i`只要大于等于`k - s/2`即可。  
* 💡 **学习笔记**：非冗余条件的本质是“每个选中的党派都是‘必要的’”，即它的席位必须大于“联合政府总席位减去总席位的一半”。  

### 2.  **关键点2：如何用排序消除后效性？**  
* **分析**：如果直接做01背包，可能会选到不满足约束的党派（比如小党派先选，导致大党派无法满足`a_i ≥k - s/2`）。将党派按席位从大到小排序后，先处理大党派，这样当加入小党派时，前面的总重量`current_sum`一定≤`s/2`（否则无法满足约束），此时加入小党派`a_i`后，`k = current_sum + a_i > s/2`（因为`current_sum ≤s/2`，`a_i ≥1`），且`a_i ≥k - s/2`（因为`k - s/2 = current_sum + a_i - s/2 ≤a_i`）。  
* 💡 **学习笔记**：排序是解决带约束背包问题的常用技巧，能保证约束条件的满足。  

### 3.  **关键点3：如何记录路径？**  
* **分析**：优质题解中用了不同的方法记录路径：`bag[k] = i`（记录到达`k`时选的最后一个党派）、`bitset`（标记选中的党派）、`pr`数组（记录状态转移）。这些方法的核心都是**记录每个状态的来源**，方便回溯找到选中的党派。  
* 💡 **学习笔记**：路径记录的关键是“记住每个状态是怎么来的”，比如从哪个状态转移过来，选了哪个物品。  

### ✨ 解题技巧总结  
- **问题转化**：将非冗余条件转化为数学约束，转化为带约束的背包问题。  
- **排序优化**：按物品重量从大到小排序，消除后效性。  
- **状态记录**：用数组或`bitset`记录状态，方便回溯路径。  


## 4. C++核心代码实现赏析

<code_intro_overall>
下面是一个综合了优质题解思路的通用核心实现，用**排序+一维01背包**解决问题，代码简洁且高效：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码综合了CodyTheWolf和Hope2075的思路，用一维数组记录状态，回溯路径。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <algorithm>
  using namespace std;

  typedef pair<int, int> pii; // 第一个元素是席位，第二个是党派编号
  const int MAXN = 305;
  const int MAXT = 1e5 + 5;

  pii a[MAXN];
  int bag[MAXT]; // bag[k]表示到达k席位时选的最后一个党派的索引（从1开始）
  vector<int> ans;

  int main() {
      int n, s = 0;
      cin >> n;
      for (int i = 1; i <= n; ++i) {
          cin >> a[i].first;
          a[i].second = i;
          s += a[i].first;
      }
      // 按席位从大到小排序
      sort(a + 1, a + n + 1, [](const pii& x, const pii& y) {
          return x.first > y.first;
      });
      // 初始化bag数组，bag[0] = n+1表示初始状态（未选任何党派）
      fill(bag, bag + MAXT, 0);
      bag[0] = n + 1;
      // 01背包：从大到小处理党派
      for (int i = n; i >= 1; --i) {
          int weight = a[i].first;
          // 枚举背包容量：从s/2 + weight到weight（因为要满足current_sum <= s/2）
          for (int k = s / 2 + weight; k >= weight; --k) {
              if (bag[k - weight] != 0 && bag[k] == 0) {
                  bag[k] = i; // 记录到达k时选的最后一个党派是i
              }
          }
      }
      // 找最大的k>s/2且bag[k]!=0
      int max_k = 0;
      for (int k = s; k > s / 2; --k) {
          if (bag[k] != 0) {
              max_k = k;
              break;
          }
      }
      // 回溯路径
      while (max_k != 0) {
          int i = bag[max_k];
          ans.push_back(a[i].second);
          max_k -= a[i].first;
      }
      // 输出结果
      cout << ans.size() << endl;
      for (int id : ans) {
          cout << id << " ";
      }
      cout << endl;
      return 0;
  }
  ```
* **代码解读概要**：  
  1. **输入与排序**：读取党派席位，按从大到小排序。  
  2. **背包初始化**：`bag[0] = n+1`表示初始状态（未选任何党派）。  
  3. **01背包处理**：从大到小处理每个党派，枚举背包容量，记录到达每个容量时选的最后一个党派。  
  4. **找最大k**：找大于总席位一半的最大容量。  
  5. **回溯路径**：从最大k开始，依次减去选中的党派的席位，找到所有选中的党派。  


<code_intro_selected>
接下来，我们剖析优质题解中的核心片段：
</code_intro_selected>

**题解一：来源：CodyTheWolf**  
* **亮点**：用`bag[k] = i`记录路径，简洁高效。  
* **核心代码片段**：  
  ```cpp
  for (int i = n; i >= 1; i--)
      for (int k = s/2 + a[i].first; k >= a[i].first; k--)
          if (bag[k - a[i].first] && !bag[k]) bag[k] = i;
  ```
* **代码解读**：  
  这段代码是01背包的核心。`i`从大到小处理每个党派，`k`从`s/2 + a[i].first`到`a[i].first`枚举容量。如果`k - a[i].first`可达（`bag[k - a[i].first] != 0`），且`k`未被访问过（`bag[k] == 0`），则记录`bag[k] = i`（表示到达`k`时选的最后一个党派是`i`）。  
* 💡 **学习笔记**：`bag[k]`记录最后一个党派的索引，是回溯路径的关键。  

**题解二：来源：Irisany**  
* **亮点**：用`bitset`优化状态记录，空间效率高。  
* **核心代码片段**：  
  ```cpp
  bitset<MAXN> b[MAXM];
  for (int i = 1; i <= n; ++i) {
      for (int v = sum; v >= base[i].fr; --v) {
          if (!f[v] && f[v - base[i].fr]) {
              b[v] = b[v - base[i].fr];
              b[v].set(base[i].sc);
              f[v] = 1;
          }
      }
  }
  ```
* **代码解读**：  
  `b[v]`是一个`bitset`，其中第`j`位为1表示选了第`j`个党派。当`v - base[i].fr`可达时，`b[v]`等于`b[v - base[i].fr]`（未选当前党派的状态）加上当前党派的位（`set(base[i].sc)`）。  
* 💡 **学习笔记**：`bitset`能将状态压缩为二进制位，大大减少空间占用。  


## 5. 算法可视化：像素动画演示 (核心部分)

\<visualization\_intro\>
为了更直观地理解“排序+01背包”的过程，我设计了一个**像素背包探险**动画，用8位像素风格模拟算法执行流程：
\</visualization\_intro\>

### **动画演示主题**：像素探险家收集“席位宝石”  
- **场景**：屏幕左侧是排序后的“席位宝石”（像素方块，大小代表席位，颜色越深表示席位越大），右侧是“背包”（显示当前总席位）。  
- **角色**：一个像素探险家（小矮人），负责将宝石放进背包。  

### **核心演示内容**  
1. **初始化**：  
   - 屏幕显示总席位（比如样例中的10），总席位的一半（5）。  
   - 左侧排列着排序后的宝石（4、3、2、1），右侧背包显示0。  
   - 控制面板有“开始”“单步”“自动”“重置”按钮，以及速度滑块。  

2. **排序过程**：  
   - 宝石从大到小排列，动画显示“排序中”的提示，伴随“叮”的音效。  

3. **背包过程**：  
   - 探险家从最大的宝石（4）开始，尝试放进背包。此时背包总席位是0，加上4后是4，≤5（总席位的一半），所以可以放。背包显示4，宝石4变成蓝色（选中）。  
   - 接下来处理宝石3：探险家尝试放进背包，总席位变成4+3=7>5（满足联合政府条件）。此时检查约束条件：7-5=2，宝石3≥2，符合非冗余。背包闪烁绿色，伴随“胜利”音效。  
   - 动画停止，显示选中的宝石（4、3），以及联合政府的总席位（7）。  

4. **交互功能**：  
   - **单步执行**：点击“单步”，探险家移动一步，处理一个宝石。  
   - **自动播放**：点击“自动”，探险家自动处理所有宝石，速度可通过滑块调整。  
   - **重置**：点击“重置”，回到初始状态。  

### **设计思路**  
- **像素风格**：模拟FC红白机的画面，让学习者感到亲切。  
- **音效提示**：关键操作（如选宝石、满足条件）伴随音效，强化记忆。  
- **交互功能**：让学习者主动控制动画，加深对算法的理解。  


## 6. 拓展练习与相似问题思考

\<similar\_problems\_intro\>
“选举”问题的核心是**带约束的01背包**，这种思路可以迁移到很多类似问题中：
\</similar\_problems\_intro\>

### **通用思路/技巧迁移**  
- **场景1**：选物品使得总价值最大，且每个物品的重量大于总重量的1/3。  
- **场景2**：选课程使得总学分最高，且每门课程的学分大于总学分的1/4。  
- **场景3**：选零件使得总强度最大，且每个零件的强度大于总强度的1/5。  

### **练习推荐 (洛谷)**  
1. **洛谷 P4394** - 命运石之门的选择  
   * 🗣️ **推荐理由**：这道题是“选举”问题的变种，要求选物品使得总价值最大，且每个物品的重量大于总重量的1/2。可以巩固带约束背包的思路。  
2. **洛谷 P1048** - 采药  
   * 🗣️ **推荐理由**：经典的01背包问题，帮助理解背包的基本思想。  
3. **洛谷 P2347** - 砝码称重  
   * 🗣️ **推荐理由**：用背包解决砝码组合问题，强化状态记录的技巧。  


## 7. 学习心得与经验分享 (若有)

\<insights\_intro\>
从题解中，我发现了一些宝贵的学习心得：
\</insights\_intro\>

> **参考经验 (来自 CodyTheWolf)**：“我一开始没想到排序的作用，后来通过样例分析，发现大的党派先选才能保证约束条件。这让我意识到，排序是解决带约束问题的重要技巧。”  
> **点评**：这位作者的经验很典型。在解决带约束的问题时，排序往往能消除后效性，让问题变得容易处理。比如“选举”问题中的排序，就是关键的一步。  


\<conclusion\>
本次关于“[BalticOI 2008] 选举”的C++解题分析就到这里。希望这份指南能帮助你理解带约束背包的思路，掌握排序优化和路径记录的技巧。记住，编程的乐趣在于不断思考和尝试，下次我们再一起探索新的挑战！💪
\</conclusion\>

---
处理用时：147.33秒