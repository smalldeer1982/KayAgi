# 题目信息

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

# AI分析结果



**唯一算法分类**：数论

---

### **题解思路与算法要点**

1. **核心数学性质**：  
   - 两个数的公约数一定是其最大公约数（gcd）的因数。因此，只需枚举 gcd(a, b) 的因数，而非所有可能的数。
   - **证明**：设 d 是 a 和 b 的公约数，则 d | a 且 d | b。由 Bézout 定理，d 必须整除 gcd(a, b)，即 d | gcd(a, b)。

2. **关键步骤**：  
   - **步骤1**：计算 gcd(a, b)。  
   - **步骤2**：枚举所有可能的因数（1~√gcd），并存储成有序列表。  
   - **步骤3**：对每个查询，用二分法找到不超过 high 的最大因数，并判断是否在区间内。

3. **算法优化**：  
   - **因数枚举**：从 1 到 √gcd 枚举，若 i 是因数，则 gcd/i 也是因数。  
   - **二分查找**：利用 `upper_bound` 快速定位第一个大于 high 的位置，取前一个元素判断是否 ≥ low。

---

### **题解评分（≥4星）**

1. **ADay 题解（★★★★★）**  
   - **亮点**：利用 `__gcd` 快速求最大公约数，直接枚举因数后排序，使用 `upper_bound` 高效处理查询。代码简洁高效。  
   - **代码片段**：
     ```cpp
     vector<int> v;
     int g = __gcd(a, b);
     for (int i = 1; i * i <= g; i++) {
         if (g % i == 0) v.push_back(i), v.push_back(g / i);
     }
     sort(v.begin(), v.end());
     int pos = upper_bound(v.begin(), v.end(), high) - v.begin() - 1;
     ```

2. **tobie 题解（★★★★☆）**  
   - **亮点**：手写二分逻辑，适合理解二分底层原理。通过维护左右指针找到最大合法因数。  
   - **代码片段**：
     ```cpp
     int l = 1, r = cnt, ans = -1;
     while (l <= r) {
         int mid = (l + r) / 2;
         if (d[mid] > high) r = mid - 1;
         else {
             ans = d[mid];
             l = mid + 1;
         }
     }
     ```

3. **xiaoPanda 题解（★★★★☆）**  
   - **亮点**：使用 `set` 自动去重和排序，代码更简洁，但插入效率略低于 `vector`。  
   - **代码片段**：
     ```cpp
     set<int> s;
     for (int i = 1; i * i <= g; i++) {
         if (g % i == 0) s.insert(i), s.insert(g / i);
     }
     auto it = s.upper_bound(high);
     if (it != s.begin() && *--it >= low) cout << *it;
     ```

---

### **最优技巧提炼**

1. **因数枚举优化**：  
   - **核心代码**：`for (int i = 1; i * i <= g; i++)`，避免重复枚举，时间复杂度 O(√g)。

2. **二分查找技巧**：  
   - **核心逻辑**：利用 `upper_bound` 快速定位区间右端点，降维查询复杂度至 O(log d)。

3. **去重与排序**：  
   - 使用 `sort + unique` 或 `set` 确保因数有序且唯一，便于后续操作。

---

### **同类题目推荐**

1. **CF 762A - k-th divisor**  
   - **题号**：CF762A  
   - **关键点**：求数的第 k 小因数，需高效枚举并排序。

2. **洛谷 P1072 Hankson 的趣味题**  
   - **题号**：P1072  
   - **关键点**：结合 gcd 和 lcm 的性质，枚举因数验证条件。

3. **洛谷 P1414 又是毕业季II**  
   - **题号**：P1414  
   - **关键点**：统计多个数的公约数，预处理因数出现次数。

---

### **可视化与算法演示**

**动画设计思路**：  
1. **像素风格界面**：采用 8-bit 风格，用不同颜色块表示 gcd 的因数。  
2. **关键步骤高亮**：  
   - **步骤1**：显示计算 gcd(a, b) 的过程（如欧几里得算法）。  
   - **步骤2**：逐个生成因数，用绿色方块标记当前枚举的 i 和 g/i。  
   - **步骤3**：对每个查询，用红色框标出 [low, high]，蓝色指针动态移动展示二分过程。  
3. **音效与交互**：  
   - 每次找到因数时播放“叮”声，查询无解时播放“失败”音效。  
   - 用户可调整动画速度，单步观察二分细节。

**伪代码示例**（Canvas 绘制）：
```javascript
// 初始化像素画布
const canvas = document.getElementById("pixel-canvas");
// 绘制因数方块
for (let factor of factors) {
    drawSquare(factor, color.green);
    playSound("beep");
}
// 演示二分过程
let left = 0, right = factors.length - 1;
while (left <= right) {
    let mid = Math.floor((left + right) / 2);
    highlightSquare(factors[mid], color.yellow);
    if (factors[mid] > high) right = mid - 1;
    else left = mid + 1;
}
```

---

### **个人心得摘录**

- **调试教训**：未去重的因数会导致二分错误，需确保因数列表严格有序且唯一。  
- **优化顿悟**：直接枚举 gcd 的因数而非原数，时间复杂度从 O(√a + √b) 降至 O(√g)。

---
处理用时：80.17秒