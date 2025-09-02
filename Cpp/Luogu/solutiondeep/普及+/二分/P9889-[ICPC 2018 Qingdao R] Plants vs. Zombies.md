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

本题的核心是通过二分答案结合贪心策略来求解最小值最大化问题。所有题解都采用了二分答案的思路，但在贪心策略的实现细节上有所不同。主要的难点在于如何高效地计算达到目标防御值所需的最少步数，并确保步数不超过给定的限制。

### 所选高星题解

#### 1. 作者：Alex_Wei (5星)
- **关键亮点**：提供了贪心策略的详细证明，确保了算法的正确性。代码实现清晰，时间复杂度为O(n log V)，适合大规模数据。
- **个人心得**：强调了贪心策略的正确性证明，避免了不求甚解的态度。

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

#### 2. 作者：_sh1kong_ (5星)
- **关键亮点**：代码简洁，贪心策略实现清晰，特别处理了最后一个植物的特殊情况，确保了算法的正确性。
- **个人心得**：强调了二分答案的单调性，并提供了详细的贪心策略实现。

```cpp
bool chk(int x) {
  for (int i = 1; i <= n; i ++ ) high[i] = 0;
  int num = m;
  for (int i = 1; i <= n; i ++ ) {
    if (high[i] < x) {
      int t = (x - high[i] - 1) / b[i] + 1;
      high[i] += t * b[i];
      high[i + 1] += b[i + 1] * (t - 1);
      num -= (t << 1);++ num;
    }
    else {
      if (i == n) return true;
      -- num;
    }
    if (num < 0) return false;
  }
  return num >= 0;
}
```

#### 3. 作者：CaiZi (4星)
- **关键亮点**：代码实现简洁，贪心策略清晰，特别处理了步数超过限制的情况，确保了算法的正确性。
- **个人心得**：强调了二分答案的单调性，并提供了详细的贪心策略实现。

```cpp
bool check(ll u) {
  ll cnt = 0;
  for (int i = 1; i <= n; i++) {
    t[i] = ceil(1.0 * u / d[i]);
  }
  for (int i = 1; i <= n; i++) {
    if (t[i] <= 0) {
      cnt++;
      continue;
    }
    cnt += 2 * t[i] - 1;
    t[i + 1] -= t[i] - 1;
    if (cnt > m) return false;
  }
  return true;
}
```

### 最优关键思路与技巧

1. **二分答案**：利用答案的单调性，通过二分法快速确定最大防御值。
2. **贪心策略**：从左到右遍历植物，计算达到目标防御值所需的最少步数，确保步数不超过限制。
3. **步数优化**：在计算步数时，提前判断是否超过限制，避免不必要的计算。

### 可拓展之处

- **类似问题**：可以应用于其他需要最大化最小值或最小化最大值的问题，如任务调度、资源分配等。
- **算法套路**：二分答案结合贪心策略是解决最优化问题的常见套路，适用于多种场景。

### 推荐题目

1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1316 丢瓶盖](https://www.luogu.com.cn/problem/P1316)

### 个人心得总结

- **调试经历**：在处理最后一个植物的特殊情况时，需要特别注意步数的计算，避免遗漏或重复计算。
- **踩坑教训**：在实现贪心策略时，确保每一步的计算都符合逻辑，避免因细节错误导致算法失效。
- **顿悟感想**：通过二分答案和贪心策略的结合，可以高效解决复杂的最优化问题，关键在于正确理解和实现贪心策略。

---
处理用时：36.34秒