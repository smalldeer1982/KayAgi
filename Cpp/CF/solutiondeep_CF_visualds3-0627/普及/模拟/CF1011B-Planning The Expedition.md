# 题目信息

# Planning The Expedition

## 题目描述

Natasha is planning an expedition to Mars for $ n $ people. One of the important tasks is to provide food for each participant.

The warehouse has $ m $ daily food packages. Each package has some food type $ a_i $ .

Each participant must eat exactly one food package each day. Due to extreme loads, each participant must eat the same food type throughout the expedition. Different participants may eat different (or the same) types of food.

Formally, for each participant $ j $ Natasha should select his food type $ b_j $ and each day $ j $ -th participant will eat one food package of type $ b_j $ . The values $ b_j $ for different participants may be different.

What is the maximum possible number of days the expedition can last, following the requirements above?

## 说明/提示

In the first example, Natasha can assign type $ 1 $ food to the first participant, the same type $ 1 $ to the second, type $ 5 $ to the third and type $ 2 $ to the fourth. In this case, the expedition can last for $ 2 $ days, since each participant can get two food packages of his food type (there will be used $ 4 $ packages of type $ 1 $ , two packages of type $ 2 $ and two packages of type $ 5 $ ).

In the second example, there are $ 100 $ participants and only $ 1 $ food package. In this case, the expedition can't last even $ 1 $ day.

## 样例 #1

### 输入

```
4 10
1 5 2 1 1 1 2 5 7 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
100 1
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 5
5 4 3 2 1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3 9
42 42 42 42 42 42 42 42 42
```

### 输出

```
3
```

# AI分析结果



## 算法分类
二分答案

## 题解思路与解决难点
### 核心思路
题目要求找到探险的最大天数 `d`，使得 `n` 个人每天都能吃到同一种食物。转化为数学问题：对于每种食物类型 `i`，其数量 `cnt[i]` 能支持 `cnt[i] // d` 个人吃 `d` 天。总人数需满足 `sum(cnt[i] // d) ≥ n`。关键在于找到最大的 `d`。

### 关键步骤
1. **统计食物类型数量**：用数组或哈希表统计每种类型的出现次数。
2. **确定二分范围**：左边界为 `1`，右边界为所有类型中最大的数量 `max_cnt`。
3. **二分验证**：检查当前中间值 `mid` 是否满足 `sum(cnt[i] // mid) ≥ n`。若满足，说明可尝试更大的天数；否则减少天数。

### 解决难点
- **正确性验证**：需确保二分终止时得到最大可行天数。
- **数据结构选择**：使用足够大的数组或哈希表存储类型数量，避免越界。
- **边界处理**：处理人数多于食物总数的情况（直接输出 `0`）。

---

## 题解评分（≥4星）
1. **BYWYR（5星）**  
   使用二分法，数组大小合理（1e5+5），代码清晰，正确处理边界条件。
   ```cpp
   bool check(int x) {
     int l = 0;
     for (int i = 1; i <= maxans; i++) l += t[i] / x;
     return l >= n;
   }
   ```
2. **Wind_Leaves_ShaDow（4星）**  
   二分法实现简洁，但数组大小略小（105），适用于原题测试数据。
   ```cpp
   bool check(int x) {
     int sum = 0;
     for (int i = 0; i <= 100; i++) sum += (g[i] / x);
     return sum >= n;
   }
   ```
3. **封禁用户（4星）**  
   标准二分模板，通过排序优化检查逻辑，代码易读。
   ```cpp
   inline bool check(int x) {
     ll t = 0;
     for (int i = 1; i <= d; ++i) t += q[i] / x;
     return t >= n;
   }
   ```

---

## 最优思路提炼
1. **二分答案框架**：将问题转化为对天数 `d` 的二分查找。
2. **贪心验证**：用 `O(k)` 时间检查当前 `d` 是否可行（`k` 为食物类型数）。
3. **边界优化**：初始右边界设为最大类型数量，减少二分次数。

---

## 同类型题与类似套路
- **分木材问题（P2440）**：二分寻找最长木材段。
- **跳石头（P2678）**：最大化最小跳跃距离。
- **数列分段（P1182）**：最小化最大段和。

---

## 推荐题目
1. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)  
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)  
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

---

## 个人心得摘录
- **二分边界陷阱**：初始右边界需足够大，否则可能错过最优解。
- **数组越界教训**：需确保存储类型的数组大小覆盖所有可能的输入值。

---

## 可视化与算法演示
### 动画设计
1. **像素风格界面**：用 8-bit 风格显示食物包为不同颜色方块，数量标注在旁。
2. **动态二分过程**：
   - **当前区间高亮**：显示 `[left, right]`，中间值 `mid` 闪烁。
   - **计算贡献值**：遍历食物类型，计算 `cnt[i] // mid`，累加至总人数。
   - **反馈效果**：若满足条件，`mid` 变为绿色，右移左边界；否则变红色，左移右边界。
3. **音效提示**：成功验证播放上升音调，失败为下降音调。

### 交互功能
- **步进控制**：允许单步执行二分步骤，观察变量变化。
- **自动演示**：AI 模式自动完成二分过程，速度可调。

```javascript
// 伪代码示例：Canvas 绘制与二分逻辑
function drawFoodBlocks(cnt) {
  cnt.forEach((count, type) => {
    drawRect(type * 20, 0, 20, count * 10, COLORS[type % 10]);
    drawText(type * 20 + 5, 50, count);
  });
}

function binarySearch() {
  while (left <= right) {
    mid = (left + right) >> 1;
    let sum = cnt.reduce((acc, cur) => acc + Math.floor(cur / mid), 0);
    if (sum >= n) {
      left = mid + 1;
      playSuccessSound();
    } else {
      right = mid - 1;
      playFailSound();
    }
    updateCanvas();
  }
}
```

---
处理用时：240.93秒