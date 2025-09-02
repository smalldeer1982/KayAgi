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
**二分法**

---

## 综合分析与结论
### 题目核心思路
题目要求找到能让所有参与者吃上尽可能多天数的最大天数。核心条件是：每个参与者每天必须吃同一种食物，不同参与者可以吃不同种类，但每个人必须连续吃同一种食物。关键点在于统计每种食物的数量，并判断在给定天数 `d` 下，所有食物能支撑的人数总和是否足够。

### 算法要点
1. **二分法确定天数**：通过二分搜索确定最大可行天数 `d`，初始范围为 `[1, max_count]`（`max_count` 是出现次数最多的食物数量）。
2. **检查函数 `check(d)`**：对于每个候选天数 `d`，遍历所有食物类型，计算每种类型能支撑的人数（`count_i // d`），总和若 ≥ `n` 则可行。
3. **提前处理特例**：如 `n > m`（天数必为 0）或 `n == m`（天数必为 1）。

### 解决难点
- **时间复杂度优化**：二分法时间复杂度为 `O(100 log m)`，显著优于枚举法的 `O(m//n * 100)`，尤其当 `m` 较大时。
- **边界条件处理**：通过初始化 `r` 为 `max_count`，并利用 `check` 函数自动排除不可能的 `d`，无需显式处理 `m//n`。

---

## ≥4星题解清单
1. **作者：_Wind_Leaves_ShaDow_（5星）**
   - **亮点**：代码简洁，正确初始化二分边界，逻辑清晰。
   - **核心代码**：
     ```cpp
     bool check(int x) {
         int sum = 0;
         for (int i = 0; i <= 100; i++) sum += (g[i] / x);
         return sum >= n;
     }
     ```
2. **作者：封禁用户（4星）**
   - **亮点**：明确二分对象，代码结构清晰，附带详细思路链接。
3. **作者：BYWYR（4星）**
   - **亮点**：变量命名规范，可读性高，初始化 `r` 为最大出现次数。

---

## 最优思路提炼
### 核心算法流程
1. **统计食物出现次数**：用桶数组记录每种食物的数量。
2. **二分搜索**：
   - **初始范围**：`l = 1`, `r = max_count`。
   - **终止条件**：`l > r`，此时 `l-1` 为最大可行天数。
3. **检查函数**：遍历所有食物类型，累加 `count_i // d`，判断总和是否足够。

### 关键优化与技巧
- **桶统计**：将食物类型映射到固定大小的数组，避免哈希表开销。
- **二分边界**：初始 `r` 设为最大出现次数，无需显式处理 `m//n`，依赖 `check` 函数自动排除非法值。

---

## 同类型题与算法套路
1. **通用解法**：二分答案常用于最大化最小值或最小化最大值问题（如资源分配）。
2. **类似题目**：
   - **洛谷 P2678 跳石头**（二分最小跳跃距离）
   - **洛谷 P1182 数列分段**（二分最大子段和）
   - **洛谷 P1316 丢瓶盖**（二分最小间距）

---

## 可视化与算法演示
### 动画设计
1. **二分过程可视化**：
   - **颜色标记**：当前 `mid` 值高亮为黄色，成功/失败状态用绿/红色区分。
   - **步进控制**：允许单步执行，观察每次 `mid` 的判定结果。
2. **贡献计算演示**：
   - **网格绘制**：每种食物类型显示为方块，数量用高度表示，当前 `d` 对应的贡献值（`count_i//d`）显示在方块顶部。
3. **复古像素风格**：
   - **8位音效**：每次二分步进播放“哔”声，成功时播放上扬音效。
   - **Canvas 绘制**：用像素块表示食物数量和贡献值，背景音乐循环播放。

### 交互设计
- **控制面板**：支持调整动画速度、暂停/继续、重置参数。
- **自动演示模式**：模拟 AI 逐步完成二分和检查流程。

---

## 代码片段（核心逻辑）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int g[N], n, m;

bool check(int x) {
    int sum = 0;
    for (int i = 0; i < N; i++) sum += g[i] / x;
    return sum >= n;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a; cin >> a;
        g[a]++;
    }
    int l = 1, r = *max_element(g, g + N), ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans;
}
```

---

## 个人心得摘录
- **调试教训**：需注意总和溢出或特例（如 `n=0`），提前处理避免逻辑错误。
- **顿悟点**：二分答案的边界初始化依赖问题特性，无需过度复杂化。

---

**推荐题目**：洛谷 P2678、P1182、P1316。

---
处理用时：373.65秒