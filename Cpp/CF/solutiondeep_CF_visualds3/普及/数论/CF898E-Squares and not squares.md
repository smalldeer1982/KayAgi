# 题目信息

# Squares and not squares

## 题目描述

Ann and Borya have $ n $ piles with candies and $ n $ is even number. There are $ a_{i} $ candies in pile with number $ i $ .

Ann likes numbers which are square of some integer and Borya doesn't like numbers which are square of any integer. During one move guys can select some pile with candies and add one candy to it (this candy is new and doesn't belong to any other pile) or remove one candy (if there is at least one candy in this pile).

Find out minimal number of moves that is required to make exactly $ n/2 $ piles contain number of candies that is a square of some integer and exactly $ n/2 $ piles contain number of candies that is not a square of any integer.

## 说明/提示

In first example you can satisfy condition in two moves. During each move you should add one candy to second pile. After it size of second pile becomes $ 16 $ . After that Borya and Ann will have two piles with number of candies which is a square of integer (second and fourth pile) and two piles with number of candies which is not a square of any integer (first and third pile).

In second example you should add two candies to any three piles.

## 样例 #1

### 输入

```
4
12 14 30 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 0 0 0 0 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6
120 110 23 34 25 45
```

### 输出

```
3
```

## 样例 #4

### 输入

```
10
121 56 78 81 45 100 1 0 54 78
```

### 输出

```
0
```

# AI分析结果


### 💡 Kay的C++算法解析：Squares and not squares 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`贪心策略与排序技巧`  
🗣️ **初步分析**：
> 解决本题的关键在于**最小化调整代价**。想象你有两堆积木：一堆是完美正方形（平方数），另一堆是不规则形状（非平方数）。目标是通过添加/移除积木（糖果），让两堆数量相等且总调整次数最少。  
> - **核心思路**：统计初始平方数个数`cnt`，若`cnt > n/2`，需将多余平方数转为非平方数（代价：非零平方数需1次操作，0需2次）；若`cnt < n/2`，则需将部分非平方数转为平方数（代价：取距离最近平方数的最小差值）。  
> - **可视化设计**：用像素方块表示糖果堆，绿色=平方数，红色=非平方数。动画高亮当前操作堆，展示代价计算过程（如0→2需两步动画），排序过程用冒泡式像素交换演示，成功调整时播放8-bit音效。

---

#### 2. 精选优质题解参考
**题解一（作者：shiziyu111）**  
* **点评**：  
  思路清晰直白，严格区分两类代价：平方数转非平方数时，0代价为2（需两步）、非零为1；非平方数转平方数时计算最小距离。代码规范（`s`/`ns`数组命名明确），边界处理严谨（特殊处理0）。算法高效（排序取最小代价），可直接用于竞赛，是初学者理解贪心策略的典范。

---

#### 3. 核心难点辨析与解题策略
1. **难点1：代价的精准计算**  
   * **分析**：非平方数→平方数的代价是到最近平方数的距离（如14→16代价2）；平方数→非平方数时，0必须变为2（代价2），非零平方数只需±1（代价1）。  
   * 💡 **学习笔记**：0是特殊平方数，需独立处理！

2. **难点2：调整方向的选择**  
   * **分析**：比较`cnt`与`n/2`：若`cnt > n/2`，优先选代价小的平方数调整（排序后取前`k`个）；反之则调整非平方数。  
   * 💡 **学习笔记**：贪心的核心是“排序后取最小代价子集”。

3. **难点3：避免重复计数**  
   * **分析**：部分题解（如ivyjiao）在调整平方数时重复累加代价。正确做法：仅累加目标调整数量的代价值。  
   * 💡 **学习笔记**：明确每个代价数组的用途，防止逻辑交叉。

✨ **解题技巧总结**  
- **技巧1：问题分解** → 拆解为“代价计算”和“调整策略”两步  
- **技巧2：边界测试** → 务必验证全0输入（样例2）  
- **技巧3：代码鲁棒性** → 用`long long`防溢出，`sqrt`后转整数避免浮点误差  

---

#### 4. C++核心代码实现赏析
**通用核心C++实现参考**  
* **说明**：综合优质题解思路，完整处理0和代价计算逻辑。  
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <cmath>
  #include <algorithm>
  using namespace std;
  int main() {
      long long n, cnt_sq = 0;
      cin >> n;
      long long s[200005], ns[200005], s_cnt = 0, ns_cnt = 0;
      
      for (int i = 0; i < n; i++) {
          long long a;
          cin >> a;
          long long root = sqrt(a);
          if (root * root == a) { // 平方数
              cnt_sq++;
              s[s_cnt++] = (a == 0) ? 2 : 1; // 0代价为2，其他为1
          } else { // 非平方数
              long long lower = root * root;
              long long upper = (root + 1) * (root + 1);
              ns[ns_cnt++] = min(a - lower, upper - a); // 取最小距离
          }
      }
      
      long long ans = 0;
      if (cnt_sq > n / 2) { // 平方数过多
          sort(s, s + s_cnt);
          for (int i = 0; i < cnt_sq - n/2; i++) 
              ans += s[i];
      } else if (cnt_sq < n / 2) { // 非平方数过多
          sort(ns, ns + ns_cnt);
          for (int i = 0; i < n/2 - cnt_sq; i++) 
              ans += ns[i];
      }
      cout << ans;
      return 0;
  }
  ```
* **代码解读概要**：  
  > 1. **输入处理**：判断是否为平方数（`root * root == a`）。  
  > 2. **代价分类**：平方数记录转非平方数的代价（0→2，其他→1）；非平方数记录到最近平方数的距离。  
  > 3. **贪心调整**：按需排序对应代价数组，累加最小代价。  

**题解一（shiziyu111）片段赏析**  
* **亮点**：独立处理0的代价，逻辑隔离清晰。  
* **核心代码片段**：
  ```cpp
  if (a == 0) s[++snum] = 2;  // 0的代价为2
  else s[++snum] = 1;         // 非零平方数代价为1
  ```
* **代码解读**：  
  > 为何0特殊？因为`0→1`仍是平方数，必须再操作一次到2才是非平方数。其他平方数（如4）只需+1变5（非平方数），一步到位。  
* 💡 **学习笔记**：特殊值独立处理是代码健壮性的关键！

---

#### 5. 算法可视化：像素动画演示
**主题**：像素糖果工厂大改造  
**核心演示**：  
1. **初始化**：  
   - 8-bit风格网格，每格代表糖果堆，绿色=平方数，红色=非平方数（图1）。  
   - 控制面板：速度滑块/单步/暂停/重置按钮。  
   ```plaintext
   初始状态：
   [12(红)] [14(红)] [30(红)] [4(绿)] 
   ```

2. **代价计算阶段**：  
   - 高亮当前堆，显示最近平方数（如14→16），像素箭头标注距离（图2）。  
   - 音效：计算时触发“嘀”声，0特殊标记时播放警告音。  

3. **排序与调整**：  
   - 代价数组可视化：像素方块数值冒泡排序（图3）。  
   - 调整动画：如4（绿）→5（红），糖果数+1，颜色渐变切换，伴随“叮”声。  

4. **完成反馈**：  
   - 目标达成时，合格堆闪烁绿光，播放胜利音效。  
   - 游戏化：每调整成功一堆得10分，实时显示总分。  

**设计思路**：  
> 像素风格降低理解门槛，动态高亮聚焦关键操作。游戏化积分激励逐步学习，音效强化记忆（如0的特殊音效提醒注意边界）。  

---

#### 6. 拓展练习与相似问题思考
1. **通用迁移场景**：  
   - 数组半数满足条件的最小操作 → 如半数偶数、半数质数等。  
   - 距离驱动的贪心问题 → 如P1094 纪念品分组（距离=价格差）。  
   - 边界特殊值处理 → 如0在数学特性中的特殊性。  

2. **洛谷练习推荐**：  
   - **P1094** [纪念品分组] → 巩固贪心+排序，理解“双指针逼近”。  
   - **P1209** [修理牛棚] → 距离最小化变体，强化区间处理能力。  
   - **P4995** 跳跳！ → 拓展排序贪心在复杂场景的应用。  

---

#### 7. 学习心得与经验分享
> 本次题解未包含作者调试心得，但需注意：  
> **经验提炼**：全0输入（样例2）是常见边界陷阱，独立测试可避免比赛失分。  

---
**结语**：掌握贪心策略的关键在于**问题分解+边界处理**，结合可视化理解操作本质。下次挑战见！ 💪

---
处理用时：225.99秒