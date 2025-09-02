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



## 唯一算法分类
**贪心算法 + 前缀异或和**

---

## 综合分析与结论

### 核心思路
题目要求最大化异或和非零的连续子数组数目。通过**正难则反**技巧，转化为最小化异或和为0的子数组数目。利用前缀异或和的性质，将问题转换为统计相同前缀和的出现次数，并通过贪心策略动态选择每个前缀和的取反状态，使得相同对的数目最少。

### 关键步骤与难点
1. **前缀异或和转换**：定义前缀异或和数组 `s`，将子数组异或和转换为 `s[r] ^ s[l-1]`。若 `s[r] = s[l-1]`，则该子数组异或和为0。
2. **取反操作的影响**：对元素 `a[i]` 取反相当于将后续所有前缀异或和异或上 `2^k - 1`。这使得每个前缀和有两种可能状态：原值或取反后的值。
3. **贪心选择**：每次选择当前前缀和状态中出现次数较少的那个，以最小化相同对的数目。通过 `map` 动态维护各状态的计数。

### 可视化设计
- **动画流程**：以网格形式展示数组元素，每个元素处理时显示两种可能的前缀和状态（原值/取反），用颜色标记选择的状态（绿色选原值，红色选取反）。右侧显示当前 `map` 中各状态的计数。
- **像素风格**：使用 8-bit 风格，每个前缀和状态用不同颜色的像素块表示，背景播放循环的芯片音乐。
- **音效触发**：选择状态时播放短促音效，更新计数时根据增减播放不同音调。

---

## 题解清单（≥4星）

### 灵茶山艾府（5星）
- **亮点**：数学推导严谨，组合计数优化明确，代码简洁高效。
- **关键代码**：通过 `min(s, s^m)` 统一处理原值与取反后的值，统计出现次数后计算组合数差值。

### 花里心爱（4.5星）
- **亮点**：动态贪心选择，代码简洁易懂，实时维护 `map` 计数。
- **关键代码**：比较当前前缀和两种状态的计数，选择较小的累加答案。

### crashed（4星）
- **亮点**：均值不等式证明贪心正确性，代码逻辑清晰。
- **关键代码**：动态选择 `s_i` 的状态，维护 `map` 并统计贡献。

---

## 核心代码实现

### 灵茶山艾府（Go）
```go
func main() {
    // ... 输入处理
    cnt := map[int]int{s: 1} // s[0] 初始化为1
    m := 1<<k - 1
    for ; n > 0; n-- {
        Fscan(in, &v)
        s ^= v
        cnt[min(s, s^m)]++ // 统一处理原值与取反后的值
    }
    for _, c := range cnt {
        ans -= c2(c/2) + c2(c - c/2) // 计算组合数差值
    }
    Print(ans)
}
```

### 花里心爱（C++）
```cpp
int main() {
    mp[0] = 1; // 初始化s[0]
    int mx = (1 << k) - 1;
    for (int i = 1; i <= n; ++i) {
        int a; cin >> a;
        int nowa = pre ^ a;
        int nowb = nowa ^ mx;
        if (mp[nowa] < mp[nowb]) { // 贪心选择较小计数
            ans += mp[nowa]++;
            pre = nowa;
        } else {
            ans += mp[nowb]++;
            pre = nowb;
        }
    }
    cout << (ll)n * (n + 1) / 2 - ans; // 总数减去异或为0的数目
}
```

---

## 相似题目推荐
1. **CF 276D** - 最大异或对（贪心与高位处理）
2. **洛谷 P1469** - 找筷子（异或性质应用）
3. **洛谷 P4884** - 多少个1（异或前缀和与模运算）

---

## 个人心得摘录
- **crashed**：均值不等式证明中，`cnt[x]` 越平均，总相同对数越小。这确保了贪心的正确性。
- **小周猪猪**：初始 `s[0] = 0` 的计数初始化容易被忽略，导致错误。

---

## 可视化与算法演示
### 动画设计
1. **数据结构**：Canvas 绘制数组元素，每个元素处理时分裂为两个像素块（原值/取反），根据选择高亮对应块。
2. **交互控制**：步进按钮允许单步执行，速度滑块调节动画速度，右侧面板显示当前统计的 `map` 计数。
3. **音效与反馈**：选择原值时播放高音，取反时低音，错误操作触发震动与警告音。

### 复古风格实现
```javascript
// 示例：绘制前缀和选择（伪代码）
function drawStep(i, chooseOriginal) {
    ctx.fillStyle = chooseOriginal ? '#00FF00' : '#FF0000';
    ctx.fillRect(i * 16, 0, 16, 16); // 16x16像素块
    playSound(chooseOriginal ? 'high' : 'low'); // 播放音效
}
```

---

通过上述分析与实现，本题的核心在于巧妙利用前缀异或和的性质与贪心策略，结合高效的数据结构维护，最终达到最优解。

---
处理用时：123.02秒