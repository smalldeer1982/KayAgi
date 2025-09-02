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



**算法分类选择**  
二分查找

---

**题解思路、算法要点与解决难点**  
题目要求找到最大天数 \(d\)，使得每个参与者每天吃同一类型食物，且总天数最大。核心思路是确定满足条件的最大 \(d\)，即各食物类型包数除以 \(d\) 的总和至少为 \(n\)。

1. **关键思路**  
   - **二分答案**：将 \(d\) 作为二分目标，检查每个 \(d\) 是否可行。若可行，尝试更大的 \(d\)；否则减小。
   - **贪心验证**：对于每个 \(d\)，计算所有类型的包数能支持的人数总和，判断是否满足 \(n\)。

2. **解决难点**  
   - **高效确定 \(d\) 的范围**：二分法的右边界设为最大包数类型的出现次数。
   - **特殊情况的快速处理**：如 \(n > m\) 直接返回 0。

---

**题解评分 (≥4星)**  
1. **作者：_Wind_Leaves_ShaDow_**（⭐️⭐️⭐️⭐️⭐️）  
   - **亮点**：正确设置二分边界，逻辑清晰，时间复杂度最优。  
   - **代码片段**：  
     ```cpp
     bool check(int x) {
         int sum = 0;
         for (int i = 0; i <= 100; i++) sum += (g[i] / x);
         return sum >= n;
     }
     // 主函数中二分逻辑
     ```

2. **作者：封禁用户**（⭐️⭐️⭐️⭐️）  
   - **亮点**：类似二分实现，边界处理正确，代码简洁。  

3. **作者：小闸蟹**（⭐️⭐️⭐️⭐️）  
   - **亮点**：从大到小枚举天数，提前终止循环优化时间。  

---

**最优思路或技巧提炼**  
1. **二分法优化**：将问题转化为二分答案模型，时间复杂度 \(O(100 \log \text{max\_count})\)。  
2. **贪心验证**：对每个 \(d\) 快速计算各类型的贡献总和。  
3. **边界处理技巧**：初始右边界设为最大包数，避免无效遍历。

---

**同类型题或类似算法套路**  
1. **分木材问题**：求能切割出的最大长度（二分答案）。  
2. **跳石头问题**：最小化跳跃距离的最大值（二分+贪心）。  
3. **汉堡制作问题**（Codeforces 371C）：确定最多汉堡数（二分答案）。

---

**推荐题目**  
1. 洛谷 P2440（木材加工）  
2. 洛谷 P2678（跳石头）  
3. Codeforces 371C（Hamburgers）

---

**个人心得摘录**  
- **调试教训**：枚举范围错误会导致答案错误，必须正确设置边界（如小闸蟹的 \(m/n\)）。  
- **顿悟**：当 \(d\) 增大时，总和单调递减，可提前终止循环。

---

**可视化与算法演示**  
1. **动画设计**：  
   - **Canvas 绘制**：显示当前 \(d\) 和各类型包数的分割情况。  
   - **颜色标记**：满足条件的 \(d\) 用绿色高亮，失败则红色。  
   - **步进控制**：手动调整二分区间或自动播放观察每一步决策。  
2. **复古像素风格**：  
   - **像素音效**：每次检查触发“滴”声，成功时播放 8-bit 胜利音效。  
   - **自动演示**：AI 模拟二分过程，动态展示区间缩小。  

```cpp
// 核心二分逻辑示例（_Wind_Leaves_ShaDow_ 的代码）
bool check(int x) {
    int sum = 0;
    for (int i = 0; i <= 100; i++) sum += (g[i] / x);
    return sum >= n;
}

int main() {
    // 初始化并统计各类型包数
    int l = 1, r = max_count;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << l - 1;
}
```

---

**总结**  
通过二分法或优化枚举，结合贪心验证，高效解决最大天数问题。关键在正确设置边界和利用单调性优化遍历过程。

---
处理用时：251.71秒