# 题目信息

# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8```

### 输出

```
-1
1 8 7 3 6 2 4 5```

# AI分析结果



**唯一算法分类**: 数论

---

### **题解思路与算法要点**

1. **核心思路**  
   - **奇偶分组**：将奇数和偶数分别集中排列，确保相邻数之和为偶数（除2外均为合数）。
   - **连接处处理**：在奇偶交界处插入5和4，使其和为9（最小的奇合数）。

2. **数学推导**  
   - 奇数+奇数=偶数，偶数+偶数=偶数，仅奇偶交界处需验证和为合数。
   - 最小奇合数9可分解为4+5，确保交界处合法。

3. **解决难点**  
   - **边界条件**：当n≤4时无解，需特判。
   - **构造验证**：通过分组和固定连接点，保证所有相邻和均为合数。

---

### **题解评分 (≥4星)**

1. **ridewind2013 (5星)**  
   - 思路清晰，直接分组并插入5和4。
   - 代码简洁，逻辑明确，可读性高。

2. **K_yuxiang_rose (4星)**  
   - 类似思路，先偶数后奇数，代码直观。
   - 通过样例验证正确性，但代码顺序与常规逻辑略有不同。

3. **DoubleQLzn (4星)**  
   - 详细数学分析，突出构造细节。
   - 代码实现与核心思路一致，注释清晰。

---

### **最优思路提炼**

- **分组策略**：奇数和偶数分组，内部相邻和为偶数（合数）。
- **连接优化**：固定使用4和5作为奇偶交界点，和为9（奇合数）。
- **特判处理**：n≤4时无解，直接返回-1。

---

### **类似题目推荐**

1. **CF1155C** - 构造连续数对满足条件。
2. **P1217** - 素数环问题（需DFS剪枝）。
3. **CF1342B** - 构造二进制串满足相邻条件。

---

### **可视化设计**

1. **动画流程**  
   - **步骤1**：将奇数和偶数分列两侧，颜色区分。
   - **步骤2**：高亮5和4，插入交界处，显示和为9。
   - **步骤3**：逐个验证相邻和，标记合数。

2. **复古风格**  
   - **像素块**：奇数用红色，偶数用蓝色，4和5用金色。
   - **音效**：插入4和5时播放合成音效，验证成功时播放胜利音效。

3. **交互设计**  
   - **单步执行**：逐步展示分组和插入过程。
   - **自动模式**：AI模拟构造流程，动态调整分组顺序。

---

### **代码片段（核心逻辑）**

```cpp
// 构造排列的核心代码（ridewind2013题解）
if (n <= 4) cout << -1 << "\n";
else {
    // 输出奇数（排除5）
    for (int i = 1; i <= n; i += 2) {
        if (i != 5) cout << i << " ";
    }
    // 插入5和4
    cout << "5 4 ";
    // 输出偶数（排除4）
    for (int i = 2; i <= n; i += 2) {
        if (i != 4) cout << i << " ";
    }
}
```

---

### **个人心得摘录**

- **关键验证**：手动验证小样例（如n=5）确保连接处正确。
- **调试技巧**：边界条件n=4需单独测试，避免遗漏。
- **思维突破**：将复杂排列问题简化为奇偶分组，固定连接点。

---

### **复古游戏化演示**

- **Canvas绘制**：用16位像素风格展示数字排列过程。
- **音效触发**：插入5和4时播放“哔”声，验证合数时播放“叮”声。
- **积分系统**：每正确构造一步得10分，错误则扣分，鼓励优化路径。

```javascript
// 伪代码：音效触发示例
function playSound(effect) {
    if (effect === 'step') new Audio('beep.wav').play();
    if (effect === 'success') new Audio('win.wav').play();
}
```

---
处理用时：92.40秒