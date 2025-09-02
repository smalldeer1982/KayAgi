# 题目信息

# Monsters Attack!

## 题目描述

You are playing a computer game. The current level of this game can be modeled as a straight line. Your character is in point $ 0 $ of this line. There are $ n $ monsters trying to kill your character; the $ i $ -th monster has health equal to $ a_i $ and is initially in the point $ x_i $ .

Every second, the following happens:

- first, you fire up to $ k $ bullets at monsters. Each bullet targets exactly one monster and decreases its health by $ 1 $ . For each bullet, you choose its target arbitrary (for example, you can fire all bullets at one monster, fire all bullets at different monsters, or choose any other combination). Any monster can be targeted by a bullet, regardless of its position and any other factors;
- then, all alive monsters with health $ 0 $ or less die;
- then, all alive monsters move $ 1 $ point closer to you (monsters to the left of you increase their coordinates by $ 1 $ , monsters to the right of you decrease their coordinates by $ 1 $ ). If any monster reaches your character (moves to the point $ 0 $ ), you lose.

Can you survive and kill all $ n $ monsters without letting any of them reach your character?

## 说明/提示

In the first example, you can act as follows:

- during the $ 1 $ -st second, fire $ 1 $ bullet at the $ 1 $ -st monster and $ 1 $ bullet at the $ 3 $ -rd monster. Then the $ 1 $ -st monster dies, the $ 2 $ -nd and the $ 3 $ -rd monster move closer;
- during the $ 2 $ -nd second, fire $ 2 $ bullets at the $ 2 $ -nd monster. Then the $ 2 $ -nd monster dies, the $ 3 $ -rd monster moves closer;
- during the $ 3 $ -rd second, fire $ 2 $ bullets at the $ 3 $ -rd monster. Then the $ 3 $ -rd monster dies.

In the second example, you can fire only $ 1 $ bullet, so you can kill only one of the two monsters during the $ 1 $ -st second. Then, the remaining monster moves closer and kills your character.

## 样例 #1

### 输入

```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果



## 算法分类
**贪心**

---

## 综合分析与结论

### 核心思路与难点
**核心思路**：  
1. 将怪物按距原点的绝对值距离排序，优先处理最近的怪物。
2. 维护一个桶数组 `t`，统计每个距离对应的怪物总血量。
3. 逐秒累积子弹数，检查是否足够消灭当前距离的怪物总血量。

**解决难点**：  
- **时间窗口限制**：距离为 `d` 的怪物必须在 `d` 秒内被消灭，否则会抵达原点。
- **子弹分配策略**：贪心证明优先消灭最近的怪物是最优策略，因为若无法消灭最近的，更远的必然无法处理；反之若最近的能消灭，剩余子弹可分配给后续怪物。

**算法流程**：  
1. 输入怪物数据，取坐标绝对值并记录到桶数组。
2. 遍历距离 `1` 到 `n`，每秒累积 `k` 子弹。
3. 若累积子弹数 `<` 当前距离的总血量，输出 `NO`；否则减去该血量继续。

---

## 题解评分 (≥4星)

1. **Hacker_Cracker (4.5星)**  
   - **亮点**：桶计数避免显式排序，代码简洁高效。  
   - **关键代码**：  
     ```cpp
     for (int i = 1; i <= n; i ++) t[abs(x_i)] += a_i;
     for (int i = 1; i <= n; i ++) sum += k - t[i];
     ```

2. **2huk (4星)**  
   - **亮点**：逻辑清晰，维护剩余子弹变量 `lst`，直接比较判断。  
   - **核心逻辑**：  
     ```cpp
     lst += k;
     if (lst < x[i]) return "NO";
     ```

3. **QoQ_ (4星)**  
   - **亮点**：变量命名清晰，初始化处理严谨。  
   - **优化点**：使用 `s[x[i]]` 直接统计总血量，避免重复计算。

---

## 最优思路提炼

### 关键技巧
1. **桶计数优化**：将怪物按绝对距离存入桶数组，避免显式排序，时间复杂度降至 `O(n)`。
2. **逐秒累积子弹**：每处理一个距离 `i`，累积 `i*k` 子弹，检查是否足够消灭当前总血量。

### 代码片段
```cpp
// 桶统计每个距离的总血量
vector<long long> t(n + 1, 0);
for (int i = 0; i < n; ++i) {
    int x = abs(monsters[i].x);
    t[x] += monsters[i].a;
}

// 逐秒检查
long long bullets = 0;
for (int i = 1; i <= n; ++i) {
    bullets += k; // 每秒累积k子弹
    if (bullets < t[i]) return "NO";
    bullets -= t[i];
}
return "YES";
```

---

## 同类问题推荐

1. **CF1352C - K-th Not Divisible by n**  
   - 类似贪心策略，寻找第k个不被n整除的数。

2. **CF1462D - Add to Neighbour**  
   - 合并数组元素的最小操作次数，需贪心计算前缀和。

3. **洛谷P1090 [NOIP2004 提高组] 合并果子**  
   - 优先队列贪心合并最小代价。

---

## 可视化设计

### 动画方案
- **像素风格**：怪物用不同颜色方块表示，距离越近颜色越深。
- **子弹累积**：右侧显示当前秒数和累积子弹数，左侧显示各距离怪物血量。
- **高亮变化**：当前处理的怪物距离高亮红色，若子弹不足则闪烁警告。
- **音效**：成功消灭时播放“叮”声，失败时播放“爆炸”声。

### 交互设计
- **步进控制**：用户可点击“下一帧”观察每一步子弹与血量的变化。
- **参数调节**：输入框动态修改 `k` 值，实时观察结果变化。
- **自动演示**：点击“播放”按钮自动运行，速度可调。

---

## 个人心得摘录
- **Hacker_Cracker**：强调桶数组对坐标绝对值的处理，避免排序开销。
- **Elhaithan**：通过维护剩余子弹变量，直观展示子弹分配过程。
- **踩坑提醒**：必须用 `long long` 存储累积子弹，否则会溢出导致错误。

---
处理用时：56.38秒