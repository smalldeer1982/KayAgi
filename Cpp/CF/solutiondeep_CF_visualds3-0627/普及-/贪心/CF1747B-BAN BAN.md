# 题目信息

# BAN BAN

## 题目描述

You are given an integer $ n $ .

Let's define $ s(n) $ as the string "BAN" concatenated $ n $ times. For example, $ s(1) $ = "BAN", $ s(3) $ = "BANBANBAN". Note that the length of the string $ s(n) $ is equal to $ 3n $ .

Consider $ s(n) $ . You can perform the following operation on $ s(n) $ any number of times (possibly zero):

- Select any two distinct indices $ i $ and $ j $ $ (1 \leq i, j \leq 3n, i \ne j) $ .
- Then, swap $ s(n)_i $ and $ s(n)_j $ .

You want the string "BAN" to not appear in $ s(n) $ as a subsequence. What's the smallest number of operations you have to do to achieve this? Also, find one such shortest sequence of operations.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first testcase, $ s(1) =  $ "BAN", we can swap $ s(1)_1 $ and $ s(1)_2 $ , converting $ s(1) $ to "ABN", which does not contain "BAN" as a subsequence.

In the second testcase, $ s(2) =  $ "BANBAN", we can swap $ s(2)_2 $ and $ s(2)_6 $ , converting $ s(2) $ to "BNNBAA", which does not contain "BAN" as a subsequence.

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1
1 2
1
2 6```

# AI分析结果



---

### **综合分析与结论**

#### **题目核心**
给定由 `n` 个 `BAN` 组成的字符串，通过交换字符使得 `BAN` 不再作为子序列出现，求最小交换次数及方案。

#### **贪心策略与关键思路**
- **核心思路**：每次交换破坏两个 `BAN` 结构（前 `i` 个 `BAN` 的 `A` 和后 `n-i+1` 个 `BAN` 的 `N` 交换），使得每个操作消除两个潜在子序列。
- **数学推导**：最小交换次数为 $\lceil \frac{n}{2} \rceil$，向上取整处理奇数情况。
- **正确性验证**：交换后，`A` 左侧无足够 `B`，`N` 右侧无足够 `A`，从而无法形成 `BAN` 子序列。

#### **可视化设计思路**
1. **动画演示**：  
   - **像素风格网格**：将字符串 `BANBAN...` 拆分为 `n` 个 `BAN` 块，每个字符用像素块表示。
   - **交换高亮**：每次操作时，用不同颜色标记交换的 `A` 和 `N`，并动态展示交换后的字符串。
   - **步进控制**：用户可单步执行，观察每一步如何破坏两个 `BAN` 结构。
2. **复古游戏化效果**：  
   - **音效**：交换时播放 8-bit 音效，完成所有操作后播放通关音乐。
   - **积分系统**：每正确交换一次得 10 分，总得分反映操作次数和效率。

---

### **题解清单 (≥4星)**

1. **CR7_houyetong（5星）**  
   - **亮点**：代码简洁，直接输出交换位置公式，明确推导最小次数为 $\lceil \frac{n}{2} \rceil$。
   - **代码片段**：  
     ```cpp
     for (i=1;i<=(n+1)/2;i++)
       cout<<3*i-1<<" "<<(n-i+1)*3<<endl;
     ```

2. **ImNot6Dora（4星）**  
   - **亮点**：强调子序列特性，解释为何交换 `B` 和 `N` 而非其他字符。
   - **心得引用**：  
     > "将 `B` 放在最后，`N` 放在前面，确保无法形成 `B-A-N` 的顺序。"

3. **HNOIRPplusplus（4星）**  
   - **亮点**：从子序列定义出发，提出将所有 `A` 移到 `B` 左侧，逻辑严谨。
   - **关键公式**：  
     > "交换位置为 `i*3-2`（`B`）和 `(n-i+1)*3`（`N`）。"

---

### **最优思路与代码实现**

#### **核心贪心逻辑**
- **交换位置公式**：第 `i` 次交换的 `A` 位置为 `3i-1`，对应 `N` 位置为 `3(n-i+1)`。
- **代码实现**：  
  ```cpp
  #include <iostream>
  using namespace std;
  int main() {
    int t, n;
    cin >> t;
    while (t--) {
      cin >> n;
      cout << (n + 1) / 2 << "\n";
      for (int i = 1; i <= (n + 1) / 2; i++) {
        cout << 3 * i - 1 << " " << 3 * (n - i + 1) << "\n";
      }
    }
    return 0;
  }
  ```

---

### **同类型题目与算法套路**

#### **通用贪心策略**
- **配对消除**：通过交换或标记，每次操作处理多个潜在冲突（如区间覆盖、字符对调）。
- **数学优化**：利用对称性或周期性减少操作次数。

#### **推荐题目**
1. **CF1772C**：通过字符交换使字符串不包含重复子序列。
2. **洛谷 P1223**：贪心选择最小交换次数使队列有序。
3. **LeetCode 921**：最少添加使括号有效（贪心平衡计数）。

---

### **个人心得摘录**

- **CR7_houyetong**：  
  > "交换 `A` 和 `N` 是解决奇数的关键，避免无效操作。"
- **luogu_gza**：  
  > "样例分析发现交换一次可破坏两个 `BAN`，直接推广到一般情况。"

---

### **可视化与复古游戏设计**

#### **Canvas 实现伪代码**
```javascript
// 初始化像素网格
function drawString(s) {
  for (let i = 0; i < s.length; i++) {
    drawPixel(i, s[i], color);
  }
}

// 交换动画
function swapAnim(i, j) {
  highlight(i, 'red');
  highlight(j, 'blue');
  playSound('swap');
  setTimeout(() => updateString(), 500);
}

// 自动演示模式
function autoPlay(n) {
  let i = 1;
  const timer = setInterval(() => {
    if (i > Math.ceil(n / 2)) clearInterval(timer);
    swapAnim(3*i-1, 3*(n-i+1));
    i++;
  }, 1000);
}
```

#### **复古效果**
- **8-bit 音效**：使用 Web Audio API 生成方波音效，匹配交换和完成动作。
- **积分与连击**：每步操作增加连击数，错误操作重置连击，增强游戏感。

---

**END**

---
处理用时：77.68秒