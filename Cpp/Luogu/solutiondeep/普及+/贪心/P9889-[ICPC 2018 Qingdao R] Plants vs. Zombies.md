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



### 综合分析与结论
本题核心为二分答案+贪心模拟。所有题解均采用二分最小防御值的思路，关键在于如何高效计算满足条件所需步数。关键难点在于贪心策略的正确性证明及模拟实现的优化。

### 精选题解（评分≥4星）

1. **Alex_Wei（5星）**
   - **关键亮点**：唯一给出贪心正确性严格证明的题解，代码结构清晰，处理`nxt`变量避免重复计算，时间复杂度严格O(n logV)。
   - **代码核心**：计算每个植物所需次数`cnt`，维护`nxt`表示下一植物已浇次数，累加步数时提前判断溢出。
   ```cpp
   bool check(ll x) {
     ll nxt = 0, res = 0;
     for (int i = 1; i <= n; i++) {
       ll cnt = (x - 1) / a[i] + 1 - nxt;
       if (cnt > 0 || i < n) res++, cnt--;
       res += cnt * 2, nxt = max(cnt, 0ll);
       if (res > m) return 0;
     }
     return 1;
   }
   ```

2. **灵茶山艾府（4星）**
   - **关键亮点**：将移动抽象为左右横跳，代码简洁高效，利用`pre`变量传递相邻植物浇水次数。
   - **代码核心**：每次计算当前植物需求次数`k`，累加`2k-1`步，同时更新下一植物已浇次数。
   ```cpp
   auto check = [&](long long low) -> bool {
     long long rem = m, pre = 0;
     for (int i = 0; i < n; i++) {
       long long k = (low - 1) / a[i] + 1 - pre;
       k = max(k, 1LL);
       rem -= k * 2 - 1;
       if (rem < 0) return false;
       pre = k - 1;
     }
     return true;
   };
   ```

3. **_sh1kong_（4星）**
   - **关键亮点**：代码简洁易懂，直接模拟来回浇水过程，处理最后植物特殊情况。
   - **代码核心**：对每个植物计算需要来回次数`t`，更新下一植物已浇次数。
   ```cpp
   bool chk(int x) {
     for (int i = 1; i <= n; i++) high[i] = 0;
     int num = m;
     for (int i = 1; i <= n; i++) {
       if (high[i] < x) {
         int t = (x - high[i] - 1) / b[i] + 1;
         num -= (t << 1) - 1;
         if (num < 0) return false;
         high[i + 1] += b[i + 1] * (t - 1);
       } else if (i == n) return true;
       else num--;
     }
     return num >= 0;
   }
   ```

### 最优关键思路总结
1. **二分框架**：答案单调性明显，防御值越大所需步数越多，二分上界设为`max(a_i) * m`。
2. **贪心模拟**：从左到右处理每个植物，对每个位置计算所需浇水次数`k`，最优策略是在当前与下一位置间来回移动，共需`2k-1`步，同时下一植物会被顺带浇`k-1`次。
3. **步数优化**：在每次累加步数后立即检查是否超过`m`，避免无效计算。

### 拓展与相似题目推荐
- **同类题目套路**：二分答案+贪心验证，常用于最小值最大化问题（如 P2216、P4344）。
- **推荐题目**：
  1. [P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216) （二维滑动窗口+最值优化）
  2. [P4344 [SHOI2015] 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344) （二分+线段树维护）
  3. [P2898 [USACO08JAN] Haybale Guessing G](https://www.luogu.com.cn/problem/P2898) （二分答案+区间覆盖验证）

---
处理用时：73.03秒