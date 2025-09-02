# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果

# 💡 Kay的C++算法解析：Fox And Jumping 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（map优化）/ 最短路（Dijkstra）  

🗣️ **初步分析**：  
解决“Fox And Jumping”的关键，在于理解**裴蜀定理**——要跳到所有格子，必须选择若干卡片，使其跳跃长度的**最大公约数（gcd）为1**。问题转化为：**选若干数，使它们的gcd为1，且总代价最小**。  

可以把问题比作“收集钥匙”：每个钥匙（卡片）能打开不同的锁（对应gcd的因数），只有当钥匙组合能打开所有锁（gcd=1）时，才能完成任务，而你要找**最便宜的钥匙组合**。  

### 核心算法思路  
- **动态规划（map优化）**：用`map`维护每个可能的gcd值的最小代价。遍历每个卡片，更新所有与该卡片组合后的gcd值的代价（例如，当前gcd为`x`，加入卡片`l[i]`后，新gcd为`gcd(x,l[i])`，代价为`当前代价 + c[i]`）。  
- **最短路（Dijkstra）**：将gcd值视为图的节点，选择卡片视为边（边权为卡片代价），从节点`0`（初始状态，gcd(0,l[i])=l[i]）出发，求到节点`1`的最短路径（最小代价）。  

### 可视化设计思路  
计划用**8位像素风格**动画演示map DP的过程：  
- **节点**：用不同颜色的像素块表示`map`中的gcd值（如红色表示`100`，蓝色表示`1`），代价显示在节点下方。  
- **转移**：处理每个卡片时，遍历所有已有的节点，用箭头连接旧节点（如`100`）和新节点（如`gcd(100,1)=1`），箭头颜色表示卡片（如绿色箭头代表`l=1`的卡片）。  
- **高亮与音效**：当前处理的节点闪烁，转移时播放“叮”的音效；更新代价时，节点颜色变亮，播放“滴”的音效；找到`gcd=1`时，节点绽放烟花，播放“胜利”音效。  


## 2. 精选优质题解参考

### 题解一：map优化的动态规划（作者：Kohakuwu，赞：21）  
* **点评**：  
  这份题解的思路**非常直白**，直接用`map`维护每个gcd值的最小代价。代码结构清晰，循环逻辑（遍历卡片→遍历已有gcd状态→更新新gcd代价）容易理解。**亮点**在于用`map`自动消去无用状态（只保留出现过的gcd值），避免了数组的空间浪费（因为`l[i]`可达1e9）。从实践角度看，代码简洁且能通过所有测试用例，适合初学者入门。  

### 题解二：Dijkstra最短路（作者：fanfansann，赞：8）  
* **点评**：  
  这道题的“最短路转化”思路**很有启发性**。将gcd值视为节点，选择卡片视为边（边权为卡片代价），用Dijkstra求从`0`到`1`的最短路径。**亮点**在于将动态规划问题转化为图论问题，拓宽了思维边界。代码中用`unordered_map`维护距离，处理大数值节点的问题，逻辑严谨。  

### 题解三：状压DP（作者：ZYF_B，赞：37）  
* **点评**：  
  这份题解针对`l[i]`的质因数较少（最多9个）的特点，用**状压DP**优化。状态`f[s]`表示质因数集合为`s`的最小代价，转移时合并两个数的质因数集合。**亮点**在于时间复杂度低（O(n²2⁹)），适合数据量大的情况。但需要理解质因数分解和状压的概念，适合有一定基础的学习者。  


## 3. 核心难点辨析与解题策略

### 1. **难点1：如何处理大数值的gcd状态？**  
- **分析**：`l[i]`可达1e9，无法用数组存储所有可能的gcd值。  
- **解决方案**：用`map`或`unordered_map`动态维护状态（只保留出现过的gcd值）。例如，Kohakuwu的题解中，`map<int,int>`存储每个gcd值的最小代价，避免了空间浪费。  

### 2. **难点2：如何设计状态转移？**  
- **分析**：状态转移需要考虑所有已有的gcd值与当前卡片的组合。  
- **解决方案**：遍历每个卡片，然后遍历`map`中的所有gcd值，计算新的gcd值（`gcd(当前gcd, l[i])`），并更新其最小代价。例如，Kohakuwu的代码中，`for(pair<int,int> x:mp)`遍历所有已有状态，更新新状态。  

### 3. **难点3：如何确保找到所有可能的gcd状态？**  
- **分析**：如果遗漏了某些gcd状态，可能导致无法找到最优解。  
- **解决方案**：每次处理卡片时，不仅要更新新的gcd状态，还要保留原有的状态（例如，不选当前卡片的情况）。例如，Kohakuwu的代码中，`mp[l[i]]`会保留选当前卡片的最小代价，而`mp[su]`会更新选当前卡片后的新状态。  

### ✨ 解题技巧总结  
- **技巧A：用map消去无用状态**：处理大数值问题时，用`map`动态维护状态，避免空间浪费。  
- **技巧B：状态转移的顺序**：遍历卡片→遍历已有状态→更新新状态，确保所有可能的组合都被考虑。  
- **技巧C：最短路转化**：将动态规划问题转化为图论问题，用Dijkstra求最短路径，拓宽思路。  


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考（map优化的DP）  
* **说明**：本代码综合了Kohakuwu的题解思路，用`map`维护gcd值的最小代价，逻辑清晰，适合初学者理解。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <map>
  using namespace std;
  
  int gcd(int a, int b) {
      return b == 0 ? a : gcd(b, a % b);
  }
  
  int main() {
      int n;
      cin >> n;
      int l[305], c[305];
      for (int i = 1; i <= n; ++i) cin >> l[i];
      for (int i = 1; i <= n; ++i) cin >> c[i];
      
      map<int, int> mp;
      for (int i = 1; i <= n; ++i) {
          // 先处理选当前卡片的情况（不与之前的状态组合）
          if (mp.find(l[i]) == mp.end() || c[i] < mp[l[i]]) {
              mp[l[i]] = c[i];
          }
          // 处理与之前状态组合的情况
          for (auto it = mp.begin(); it != mp.end(); ) {
              int current_gcd = it->first;
              int current_cost = it->second;
              int new_gcd = gcd(current_gcd, l[i]);
              int new_cost = current_cost + c[i];
              // 更新新gcd的最小代价
              if (mp.find(new_gcd) == mp.end() || new_cost < mp[new_gcd]) {
                  mp[new_gcd] = new_cost;
              }
              // 注意：这里不能修改迭代器，否则会失效，所以用临时变量存储
              ++it;
          }
      }
      
      if (mp.find(1) != mp.end()) {
          cout << mp[1] << endl;
      } else {
          cout << -1 << endl;
      }
      return 0;
  }
  ```  
* **代码解读概要**：  
  代码首先读取输入，然后用`map`维护每个gcd值的最小代价。遍历每个卡片时，先处理选当前卡片的情况（更新`mp[l[i]]`），再处理与之前状态组合的情况（遍历`map`中的所有gcd值，计算新的gcd值并更新代价）。最后，输出`mp[1]`（gcd=1的最小代价）。  


### 题解一：map优化的DP（作者：Kohakuwu）  
* **亮点**：用`map`动态维护状态，消去无用状态，代码简洁。  
* **核心代码片段**：  
  ```cpp
  for (int i = 1; i <= n; ++i) {
      for (pair<int, int> x : mp) {
          int num = __gcd(a[i], x.first), val = x.second + b[i];
          if (mp[num] == 0) mp[num] = val;
          else mp[num] = min(mp[num], val);
      }
      if (mp[a[i]] == 0) mp[a[i]] = b[i];
      else mp[a[i]] = min(mp[a[i]], b[i]);
  }
  ```  
* **代码解读**：  
  - 遍历每个卡片`i`，先遍历`map`中的所有状态（`x.first`是当前gcd值，`x.second`是当前代价）。  
  - 计算新的gcd值（`__gcd(a[i], x.first)`）和新的代价（`x.second + b[i]`）。  
  - 更新`mp[num]`为最小代价（如果`mp[num]`不存在，就设为新代价；否则取最小值）。  
  - 最后，处理选当前卡片的情况（不与之前的状态组合），更新`mp[a[i]]`。  
* 💡 **学习笔记**：`map`的遍历和更新是动态规划的关键，要注意处理“选”和“不选”当前卡片的情况。  


### 题解二：Dijkstra最短路（作者：fanfansann）  
* **亮点**：将动态规划转化为最短路问题，思路新颖。  
* **核心代码片段**：  
  ```cpp
  void dijkstra() {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
      q.push({0, 0});
      dist[0] = 0;
      while (!q.empty()) {
          int x = q.top().second;
          q.pop();
          if (x == 1) break;
          if (vis.find(x) != vis.end()) continue;
          vis[x] = true;
          for (int i = 1; i <= n; ++i) {
              int y = __gcd(x, l[i]), z = c[i];
              if (dist.find(y) == dist.end()) dist[y] = INF;
              if (dist[y] > dist[x] + z) {
                  dist[y] = dist[x] + z;
                  q.push({dist[y], y});
              }
          }
      }
  }
  ```  
* **代码解读**：  
  - 用优先队列（小根堆）实现Dijkstra算法，队列中存储（代价，gcd值）。  
  - 从节点`0`出发（初始状态，gcd(0,l[i])=l[i]），每次取出代价最小的节点`x`。  
  - 遍历所有卡片，计算新的gcd值`y`（`__gcd(x, l[i])`）和新的代价（`dist[x] + c[i]`）。  
  - 如果新代价更小，就更新`dist[y]`并将其加入队列。  
* 💡 **学习笔记**：最短路算法可以解决动态规划中的状态转移问题，尤其是当状态转移满足“最优子结构”时。  


## 5. 算法可视化：像素动画演示 (核心部分)

### 动画演示主题：像素钥匙收集游戏  
**设计思路**：用8位像素风格模拟“收集钥匙”的过程，将gcd值视为“锁”，卡片视为“钥匙”，收集钥匙组合打开所有锁（gcd=1）。  

### 动画帧步骤与交互关键点  
1. **场景初始化**：  
   - 屏幕左侧显示`map`中的gcd节点（如红色像素块表示`100`，蓝色表示`1`），代价显示在节点下方。  
   - 屏幕右侧显示当前处理的卡片（如`l=1`，`c=1`），用绿色像素块表示。  
   - 控制面板有“开始/暂停”“单步执行”“重置”按钮，以及速度滑块。  

2. **算法启动**：  
   - 初始状态：`map`中没有节点，屏幕显示“请选择第一张卡片”。  
   - 处理第一张卡片（如`l=100`，`c=99`）：`map`中添加节点`100`（红色），代价`99`，播放“叮”的音效。  

3. **核心步骤演示**：  
   - 处理第二张卡片（如`l=1`，`c=1`）：  
     - 遍历`map`中的节点`100`（红色），计算新gcd值`1`（`gcd(100,1)`），代价`99+1=100`。  
     - 用绿色箭头连接`100`和`1`（蓝色），箭头闪烁，播放“滴”的音效。  
     - 更新`map`中的节点`1`，代价`100`，蓝色像素块变亮。  

4. **目标达成**：  
   - 当`map`中出现节点`1`时，蓝色像素块绽放烟花，播放“胜利”音效，屏幕显示“成功！最小代价：100”。  

5. **交互控制**：  
   - “单步执行”：逐帧演示处理每个卡片的过程。  
   - “自动播放”：按设定速度（如1帧/秒）播放动画。  
   - “重置”：回到初始状态，重新开始。  


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移  
- **裴蜀定理**：用于判断是否能通过线性组合得到1（如本题）。  
- **map优化的DP**：用于处理大数值状态的动态规划问题（如求多个数的gcd最小代价）。  
- **最短路转化**：用于将动态规划问题转化为图论问题（如本题的Dijkstra解法）。  

### 练习推荐 (洛谷)  
1. **洛谷 P1082** - 同余方程  
   - 🗣️ **推荐理由**：直接考察裴蜀定理的应用，要求解`ax ≡ 1 (mod b)`的最小正整数解，有助于巩固本题的核心知识点。  

2. **洛谷 P2054** - 洗牌问题  
   - 🗣️ **推荐理由**：需要计算gcd来判断是否能洗到目标状态，拓展了gcd的应用场景。  

3. **洛谷 P3951** - 小凯的疑惑  
   - 🗣️ **推荐理由**：考察两个数的最大不能表示的数（`ab-a-b`），与裴蜀定理相关，有助于加深对gcd的理解。  

4. **洛谷 P4549** - 裴蜀定理  
   - 🗣️ **推荐理由**：直接考察裴蜀定理的应用，要求判断是否能通过线性组合得到1，是本题的简化版。  


## 7. 学习心得与经验分享 (若有)

### 参考经验 (来自Kohakuwu的题解)  
> “用map消去无用状态是处理大数值问题的关键。一开始我想用数组，但数组的空间不够，后来想到用map，只保留出现过的gcd值，这样就解决了空间问题。”  

**点评**：这位作者的经验很典型。在处理大数值状态时，`map`或`unordered_map`是很好的工具，能自动消去无用状态，避免空间浪费。这提醒我们，在编程时要灵活选择数据结构，根据问题的特点选择最合适的工具。  


## 结语  
本次关于“Fox And Jumping”的C++解题分析就到这里。希望这份学习指南能帮助大家更好地理解动态规划、最短路和裴蜀定理的应用。记住，编程能力的提升在于**持续学习、勤于思考和勇于实践**。下次我们再一起探索新的编程挑战！💪

---
处理用时：216.94秒