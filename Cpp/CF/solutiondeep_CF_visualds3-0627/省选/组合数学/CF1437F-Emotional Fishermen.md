# 题目信息

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9```

### 输出

```
20```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3
4 2 1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97```

### 输出

```
19200```

# AI分析结果



---

### **算法分类**
动态规划、组合数学

---

### **题解思路与核心难点**
1. **核心思路**  
   所有解法均基于排序后的动态规划。将数组排序后，定义 `f[i]` 表示以 `a[i]` 为当前最大值时的合法排列数。通过预处理每个元素的限制条件（如 `lim[i]` 表示最大的 `j` 满足 `2a[j] ≤ a[i]`），利用排列组合公式计算剩余元素的排列方式。

2. **算法要点**  
   - **排序预处理**：确保后续动态规划的单调性，便于计算限制条件。  
   - **状态转移**：从满足条件的 `j` 转移到 `i`，计算 `f[i] += f[j] * A(剩余位置数, 待插入元素数)`。  
   - **组合优化**：通过阶乘和逆元预处理快速计算排列数，部分解法使用前缀和优化转移复杂度。

3. **解决难点**  
   - **正确推导转移方程**：需确保每次转移后所有元素满足条件。  
   - **排列数计算**：剩余元素需按特定规则插入，组合数学公式的正确应用是关键。  
   - **复杂度优化**：通过前缀和将复杂度从 `O(n^2)` 优化至 `O(n)`。

---

### **题解评分（≥4星）**
1. **LightningUZ（5星）**  
   - 思路清晰，代码简洁，通过阶乘预处理和前缀和优化显著提升效率。  
   - 核心代码片段：  
     ```cpp
     f[i] = (f[i] + fi[n - len[i]] * sum[mx] % mod) % mod;
     sum[i] = (sum[i - 1] + fc[n - 1 - len[i]] * f[i] % mod) % mod;
     ```

2. **George1123（4星）**  
   - 详细推导转移方程，数学表达严谨，但代码未完全优化。  
   - 关键转移逻辑：  
     ```cpp
     f[i] = (f[i] + 1ll * f[j] * A(n - 2 - lim[j], lim[i] - lim[j] - 1)) % mod;
     ```

3. **Alex_Wei（4星）**  
   - 代码简洁，直接通过阶乘和逆元快速计算排列数，适合快速实现。  
   - 核心代码：  
     ```cpp
     f[i] = (f[i] + 1ll * f[j] * A(n - 2 - lim[j], lim[i] - lim[j] - 1)) % mod;
     ```

---

### **最优思路与技巧**
1. **排序后动态规划**  
   通过排序保证后续元素单调性，简化条件判断。  
2. **组合数学优化**  
   预处理阶乘和逆元，快速计算排列数 `A(n, m)`。  
3. **前缀和优化**  
   将转移公式拆分为与 `i` 和 `j` 无关的部分，利用前缀和减少重复计算。

---

### **同类型题目**
1. **排列计数类**：如 [CF1515E Phoenix and Computers](https://codeforces.com/problemset/problem/1515/E)（动态规划结合组合数学）。  
2. **限制性排列**：如 [Luogu P3223 [HNOI2012] 排队](https://www.luogu.com.cn/problem/P3223)（组合数学与排列限制）。  
3. **递推优化**：如 [Luogu P2606 [ZJOI2010] 排列计数](https://www.luogu.com.cn/problem/P2606)（动态规划与树形结构）。

---

### **可视化设计**
1. **动画方案**  
   - **像素风格**：使用 8-bit 像素块表示排列元素，当前操作元素高亮为红色，已处理元素为绿色。  
   - **步进演示**：展示动态规划状态转移过程，每次选择 `a[i]` 时显示其对应的 `lim[i]` 范围。  
   - **音效提示**：在状态转移成功时播放“成功”音效，计算排列数时播放“点击”音效。

2. **交互设计**  
   - **Canvas 绘制**：以网格形式展示排序后的数组，动态高亮当前处理的元素及限制范围。  
   - **自动模式**：AI 自动执行状态转移，用户可调节速度观察每一步的 `f[i]` 更新。  
   - **控制面板**：提供暂停、步进、重置功能，支持切换不同题解算法的可视化对比。

---

### **核心代码实现**
```cpp
// 预处理阶乘和逆元
void Init() {
    fc[0] = fc[1] = fi[0] = fi[1] = iv[1] = 1;
    for (int i = 2; i <= n; i++) {
        iv[i] = iv[mod % i] * (mod - mod / i) % mod;
        fi[i] = fi[i - 1] * iv[i] % mod;
        fc[i] = fc[i - 1] * i % mod;
    }
}

// 动态规划转移
for (int i = 1; i <= n; i++) {
    while (2 * a[mx] <= a[i] && mx <= n) mx++;
    mx--;
    len[i] = mx + 1;
    f[i] = (f[i] + fi[n - len[i]] * sum[mx] % mod) % mod;
    sum[i] = (sum[i - 1] + fc[n - 1 - len[i]] * f[i] % mod) % mod;
}
```

---

### **个人心得摘录**
- **LightningUZ**：通过观察 `A(n, m)` 的数学性质，发现分母约简的可能性，实现高效前缀和优化。  
- **George1123**：强调将问题转化为子序列的插入过程，简化状态转移的推导。  
- **Alex_Wei**：直接通过预处理和快速幂计算逆元，减少代码冗余，适合竞赛快速实现。

---

### **复古游戏化效果（伪代码）**
```javascript
// Canvas 绘制像素块
function drawArray(a, highlightIdx) {
    ctx.fillStyle = "#000";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < a.length; i++) {
        ctx.fillStyle = (i === highlightIdx) ? "#FF0000" : "#00FF00";
        ctx.fillRect(i * 30, 100, 25, 25);
        ctx.fillText(a[i], i * 30 + 5, 120);
    }
}

// 音效触发
function playSound(effect) {
    const audio = new Audio(`sfx/${effect}.wav`);
    audio.play();
}

// 自动演示循环
function autoStep() {
    if (currentStep >= steps.length) return;
    const [i, j] = steps[currentStep];
    drawArray(sortedA, i);
    playSound("click");
    currentStep++;
    setTimeout(autoStep, speed);
}
```

---
处理用时：81.95秒