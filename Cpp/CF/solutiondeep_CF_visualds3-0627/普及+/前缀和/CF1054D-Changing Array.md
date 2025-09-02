# 题目信息

# Changing Array

## 题目描述

At a break Vanya came to the class and saw an array of $ n $ $ k $ -bit integers $ a_1, a_2, \ldots, a_n $ on the board. An integer $ x $ is called a $ k $ -bit integer if $ 0 \leq x \leq 2^k - 1 $ .

Of course, Vanya was not able to resist and started changing the numbers written on the board. To ensure that no one will note anything, Vanya allowed himself to make only one type of changes: choose an index of the array $ i $ ( $ 1 \leq i \leq n $ ) and replace the number $ a_i $ with the number $ \overline{a_i} $ . We define $ \overline{x} $ for a $ k $ -bit integer $ x $ as the $ k $ -bit integer such that all its $ k $ bits differ from the corresponding bits of $ x $ .

Vanya does not like the number $ 0 $ . Therefore, he likes such segments $ [l, r] $ ( $ 1 \leq l \leq r \leq n $ ) such that $ a_l \oplus a_{l+1} \oplus \ldots \oplus a_r \neq 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Determine the maximum number of segments he likes Vanya can get applying zero or more operations described above.

## 说明/提示

In the first example if Vasya does not perform any operations, he gets an array that has $ 5 $ segments that Vanya likes. If he performs the operation with $ i = 2 $ , he gets an array $ [1, 0, 0] $ , because $ \overline{3} = 0 $ when $ k = 2 $ . This array has $ 3 $ segments that Vanya likes. Also, to get an array with $ 5 $ segments that Vanya likes, he can perform two operations with $ i = 3 $ and with $ i = 2 $ . He then gets an array $ [1, 0, 3] $ . It can be proven that he can't obtain $ 6 $ or more segments that he likes.

In the second example, to get $ 19 $ segments that Vanya likes, he can perform $ 4 $ operations with $ i = 3 $ , $ i = 4 $ , $ i = 5 $ , $ i = 6 $ and get an array $ [1, 4, 3, 0, 4, 3] $ .

## 样例 #1

### 输入

```
3 2
1 3 0
```

### 输出

```
5```

## 样例 #2

### 输入

```
6 3
1 4 4 7 3 4
```

### 输出

```
19```

# AI分析结果



**唯一算法分类**: 贪心算法

---

## **综合分析与结论**

### **题解思路与核心难点**
1. **问题转化**  
   将求「异或和不为零的子区间数」转化为总子区间数减去「异或和为零的子区间数」，后者通过前缀异或和统计。
   
2. **贪心策略**  
   每个前缀和可翻转（异或全1数 `mask = 2^k-1`），动态选择当前前缀和或其翻转形式，使得相同值的出现次数尽量平均，减少相同对数目。

3. **关键数据结构**  
   使用 `map` 统计前缀和的出现次数，每次选择当前出现次数较少的版本（原值或翻转值）。

4. **难点解决**  
   - **动态调整**：每次处理元素时，根据当前前缀和的两种可能形式，选择已有次数更少的版本，确保全局最优。
   - **数学证明**：通过均值不等式，证明平分出现次数可最小化相同对数。

---

### **可视化设计思路**
1. **动画流程**  
   - **网格表示**：用网格展示前缀异或数组 `s` 的构建过程，每一步处理元素时，显示原值 `s[i]` 和翻转值 `s[i]^mask`。
   - **颜色标记**：当前选择的 `s[i]` 高亮为绿色，未选中的为红色，计数器用不同颜色区分。
   - **计数器更新**：动态显示 `map` 中每个值的计数变化。

2. **复古像素风格**  
   - **颜色方案**：8位色调色板，如 `#FF0000`（红）、`#00FF00`（绿）、`#0000FF`（蓝）表示不同状态。
   - **音效触发**：选择翻转时播放“哔”声，计数器更新时播放“滴”声。

3. **AI自动模式**  
   - **自动决策**：算法自动选择每一步的最优方向，用户可暂停观察当前状态。
   - **积分系统**：每减少一个相同对获得10分，总分显示在右上角。

---

## **题解清单 (≥4星)**

### 1. [灵茶山艾府] ⭐⭐⭐⭐⭐  
**亮点**：  
- 数学推导清晰，利用组合数公式直接计算最小相同对。  
- 代码简洁，使用 `min(s, s^mask)` 统一统计分组。  
**代码片段**：  
```go
cnt := map[int]int{s: 1}
for ; n > 0; n-- {
    s ^= v
    cnt[min(s, s^m)]++
}
ans -= c2(c/2) + c2(c-c/2)
```

---

### 2. [花里心爱] ⭐⭐⭐⭐⭐  
**亮点**：  
- 动态贪心选择，实时维护前缀和的最优状态。  
- 代码易读，直接比较 `map[nowa]` 和 `map[nowb]`。  
**代码片段**：  
```cpp
if (mp[nowa] < mp[nowb]) {
    ans += (mp[nowa]++);
    pre = nowa;
} else {
    ans += (mp[nowb]++);
    pre = nowb;
}
```

---

### 3. [crashed] ⭐⭐⭐⭐  
**亮点**：  
- 结合数学推导与贪心实现，详细分析均值不等式的影响。  
- 代码高效，直接操作 `map` 实现最优分组。  
**代码片段**：  
```cpp
if( mp[fir] < mp[sec] ) res += mp[pXor = fir] ++;
else res += mp[pXor = sec] ++;
```

---

## **最优思路或技巧提炼**

1. **正难则反**  
   将原问题转化为求最小相同对数，利用总子区间数减去该值。

2. **贪心分组**  
   对每个前缀和 `s[i]`，统计其原值和翻转值的出现次数，选择较小的分组以均衡分布。

3. **数学优化**  
   通过组合数公式 `C(n,2) = n*(n-1)/2`，快速计算相同对数目。

---

## **同类型题推荐**

1. **[CF1187B] Subsequences (hard version)**  
   类似贪心策略，通过动态选择最优子序列。

2. **[LeetCode 1442] Count Triplets That Can Form Two Arrays of Equal XOR**  
   利用前缀异或和的性质统计子区间。

3. **[洛谷 P3917] 异或序列**  
   统计异或和为零的子区间，可用类似贪心优化。

---

## **代码实现（核心逻辑）**

```python
n, k = map(int, input().split())
mask = (1 << k) - 1
prefix_counts = {0: 1}
current_xor = 0
zero_pairs = 0

for num in list(map(int, input().split())):
    current_xor ^= num
    # 计算两种可能的前缀异或值
    original = current_xor
    flipped = original ^ mask
    
    # 贪心选择出现次数较少的版本
    if prefix_counts.get(original, 0) < prefix_counts.get(flipped, 0):
        chosen = original
    else:
        chosen = flipped
    
    # 累加相同对数目并更新计数器
    zero_pairs += prefix_counts.get(chosen, 0)
    prefix_counts[chosen] = prefix_counts.get(chosen, 0) + 1

total = n * (n + 1) // 2
print(total - zero_pairs)
```

---

## **复古游戏化动画设计**

1. **Canvas 绘制**  
   - 初始化 `400x200` 画布，每步操作对应横向移动的像素块。  
   - 前缀异或值用不同颜色块表示（原值蓝色，翻转值黄色）。

2. **音效设计**  
   - 选择原值时播放 `220Hz` 正弦波（短促），翻转时播放 `440Hz`。  
   - 发现相同对时播放“失败”音效（噪声波形）。

3. **自动演示模式**  
   - 按空格键切换自动/手动模式，自动模式每步延迟500ms。  
   - 积分显示在画布顶部，字体为8位像素风格。

---

**核心动画逻辑（伪代码）**  
```javascript
function drawStep(val, isFlipped) {
    ctx.fillStyle = isFlipped ? '#FFFF00' : '#0000FF';
    ctx.fillRect(xPos, 0, 20, 20);
    playSound(isFlipped ? 440 : 220);
    updateCounter(val);
}
```

---
处理用时：90.41秒