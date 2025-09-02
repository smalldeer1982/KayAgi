# 题目信息

# [ICPC 2018 Qingdao R] Plants vs. Zombies

## 题目描述

BaoBao and DreamGrid are playing the game $\textit{Plants vs. Zombies}$. In the game, DreamGrid grows plants to defend his garden against BaoBao's zombies.

![](https://cdn.luogu.com.cn/upload/image_hosting/9tyl9ix3.png)

$\textit{Plants vs. Zombies(?)} \\
\textit{(Image from pixiv. ID: 21790160; Artist: socha)}$

There are $n$ plants in DreamGrid's garden arranged in a line. From west to east, the plants are numbered from 1 to $n$ and the $i$-th plant lies $i$ meters to the east of DreamGrid's house. The $i$-th plant has a defense value of $d_i$ and a growth speed of $a_i$. Initially, $d_i = 0$ for all $1 \le i \le n$. 

DreamGrid uses a robot to water the plants. The robot is in his house initially. In one step of watering, DreamGrid will choose a direction (east or west) and the robot moves exactly 1 meter along the direction. After moving, if the $i$-th plant is at the robot's position, the robot will water the plant and $a_i$ will be added to $d_i$. Because the water in the robot is limited, at most $m$ steps can be done.

The defense value of the garden is defined as $\min\{d_i | 1 \le i \le n\}$. DreamGrid needs your help to maximize the garden's defense value and win the game.

- Each time the robot MUST move before watering a plant;
- It's OK for the robot to move more than $n$ meters to the east away from the house, or move back into the house, or even move to the west of the house.

## 说明/提示

In the explanation below, `E` indicates that the robot moves exactly 1 meter to the east from his current position, and `W` indicates that the robot moves exactly 1 meter to the west from his current position.

For the first test case, a candidate direction sequence is $\{E, E, W, E, E, W, E, E\}$, so that we have $d = \{6,6,12,6\}$ after the watering.

For the second test case, a candidate direction sequence is $\{E, E, E, E, W, E, W, E, W\}$, so that we have $d = \{10, 10, 4\}$ after the watering.

## 样例 #1

### 输入

```
2
4 8
3 2 6 6
3 9
10 10 1```

### 输出

```
6
4```

# AI分析结果



# 算法分类
**二分**

---

## 题解思路、算法要点与解决难点

### 核心思路
题目要求最大化所有植物防御值的最小值，采用**二分答案**策略。对可能的防御值进行二分，验证每个候选值是否能用不超过 `m` 步实现。

### 算法要点
1. **二分框架**：
   - **左边界**：`0`（所有植物防御值均为0）
   - **右边界**：`m * max(a_i)`（最大可能的防御值）
   - 每次计算 `mid`，用 `check` 函数验证是否可行

2. **验证函数 `check`**：
   - 计算每个植物达到 `mid` 所需的浇水次数 `c_i = ceil(mid / a_i)`
   - 贪心模拟机器人移动：
     - 从左到右遍历植物，若当前植物未达标，则在当前位置与下一位置之间来回移动，直到满足次数
     - 每次移动需累加步数，并更新下一个植物的浇水次数（因来回移动会顺带浇到下一个植物）

### 解决难点
1. **贪心移动策略的正确性**：
   - 当处理第 `i` 个植物时，若需要 `t` 次浇水，则总步数为 `2t - 1`（来回移动 `t` 次后停留在 `i`）
   - 同时，第 `i+1` 个植物会被顺带浇 `t-1` 次，需提前扣除这些次数

2. **边界处理**：
   - 最后一个植物无需向右移动，直接计算所需步数
   - 及时判断步数是否超过 `m`，避免溢出

---

## 题解评分 (≥4星)

1. **Alex_Wei（5星）**
   - **亮点**：提供严格的贪心策略证明，代码简洁高效，处理步数时及时终止避免溢出。
   - **代码片段**：
     ```cpp
     bool check(ll x) {
       ll nxt = 0, res = 0;
       for(int i = 1; i <= n; i++) {
         ll cnt = (x - 1) / a[i] + 1 - nxt;
         if(cnt > 0 || i < n) res++, cnt--;
         cnt = max(cnt, 0ll);
         res += cnt * 2, nxt = cnt;
         if(res > m) return 0;
       }
       return 1;
     }
     ```

2. **灵茶山艾府（4星）**
   - **亮点**：开区间二分实现，使用 `pre` 变量记录顺带浇水次数，逻辑清晰。
   - **代码片段**：
     ```cpp
     auto check = [&](long long low) -> bool {
       long long rem = m, pre = 0;
       for (int i = 0; i < n; i++) {
         long long k = (low - 1) / a[i] + 1 - pre;
         if (i == n - 1 && k <= 0) break;
         k = max(k, 1LL);
         rem -= k * 2 - 1;
         if (rem < 0) return false;
         pre = k - 1;
       }
       return true;
     };
     ```

3. **_sh1kong_（4星）**
   - **亮点**：直接处理相邻植物的浇水次数，代码逻辑直观，适合理解。
   - **代码片段**：
     ```cpp
     if (high[i] < x) {
       int t = (x - high[i] - 1) / a[i] + 1;
       high[i] += t * a[i];
       high[i + 1] += a[i + 1] * (t - 1);
       num -= (t << 1); ++num;
     }
     ```

---

## 最优思路或技巧提炼

1. **二分答案的区间设置**：
   - 右边界设为 `m * max(a_i)`，避免不必要的计算。
   - 在验证时及时终止，防止溢出。

2. **贪心移动的数学表达**：
   - 对于第 `i` 个植物，若需 `t` 次浇水，则总步数为 `2t-1`，并顺带浇 `i+1` 植物 `t-1` 次。

3. **边界处理技巧**：
   - 最后一个植物单独处理，无需向右移动。
   - 在遍历过程中实时判断步数是否超限，提升效率。

---

## 同类型题或类似算法套路

1. **二分答案的通用套路**：
   - 确定答案的单调性。
   - 设计高效的 `check` 函数，通常时间复杂度为 `O(n)` 或 `O(n log n)`。

2. **类似题目**：
   - **P1873 砍树**：二分最大切割高度。
   - **P2440 木材加工**：二分切割段的最大长度。
   - **P4344 [SHOI2015] 脑洞治疗仪**：二分答案结合区间操作。

---

## 推荐洛谷题目

1. **P1873 砍树**  
   - 二分最大高度，验证是否满足条件。

2. **P2678 跳石头**  
   - 二分最短跳跃距离，验证移走石头数。

3. **P1182 数列分段 Section II**  
   - 二分每段和的最大值，验证分段数。

---

## 可视化与算法演示

### 动画设计
- **像素风格界面**：  
  - 用色块表示植物，绿色表示达标，红色未达标。
  - 机器人用像素小人表示，移动时有动画帧。

- **二分过程可视化**：  
  - **Canvas 网格**：显示当前区间 `[left, right]`，`mid` 高亮为黄色。
  - **步进控制**：按钮控制单步执行或自动播放。

- **音效与提示**：  
  - **移动音效**：机器人移动时播放 8-bit 音效。
  - **成功/失败提示**：找到答案时播放胜利音效，失败则短促提示。

### 关键代码片段（伪代码）
```javascript
// 模拟二分过程
function binarySearch() {
  let left = 0, right = maxValue;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (check(mid)) {
      drawMid(mid, 'green');
      left = mid + 1;
    } else {
      drawMid(mid, 'red');
      right = mid - 1;
    }
  }
}
```

---

## 个人心得摘录

- **调试教训**：  
  > *“最后一个位置若不处理会导致步数计算错误，需单独判断。”* —— 灵茶山艾府

- **优化经验**：  
  > *“在累加步数时及时判断是否超限，避免不必要的计算。”* —— Alex_Wei

---

## 核心代码实现

```cpp
bool check(ll x) {
  ll res = 0, pre = 0;
  for (int i = 1; i <= n; i++) {
    ll cnt = (x - 1) / a[i] + 1;  // 计算总需浇水次数
    cnt -= pre;                   // 减去顺带浇的次数
    if (cnt <= 0 && i != n) {     // 当前已达标但需移动
      res++;
      pre = 0;
      continue;
    }
    cnt = max(cnt, 0LL);
    if (i != n) res++;            // 移动到i+1
    res += cnt * 2;               // 来回移动
    pre = cnt;                    // 下一个顺带浇的次数
    if (res > m) return false;
  }
  return true;
}
```

---
处理用时：100.04秒