# 题目信息

# Birthday Gift

## 题目描述

Yarik's birthday is coming soon, and Mark decided to give him an array $ a $ of length $ n $ .

Mark knows that Yarik loves bitwise operations very much, and he also has a favorite number $ x $ , so Mark wants to find the maximum number $ k $ such that it is possible to select pairs of numbers \[ $ l_1, r_1 $ \], \[ $ l_2, r_2 $ \], $ \ldots $ \[ $ l_k, r_k $ \], such that:

- $ l_1 = 1 $ .
- $ r_k = n $ .
- $ l_i \le r_i $ for all $ i $ from $ 1 $ to $ k $ .
- $ r_i + 1 = l_{i + 1} $ for all $ i $ from $ 1 $ to $ k - 1 $ .
- $ (a_{l_1} \oplus a_{l_1 + 1} \oplus \ldots \oplus a_{r_1}) | (a_{l_2} \oplus a_{l_2 + 1} \oplus \ldots \oplus a_{r_2}) | \ldots | (a_{l_k} \oplus a_{l_k + 1} \oplus \ldots \oplus a_{r_k}) \le x $ , where $ \oplus $ denotes the operation of [bitwise XOR](https://en.wikipedia.org/wiki/Exclusive_or), and $ | $ denotes the operation of [bitwise OR](https://en.wikipedia.org/wiki/Logical_disjunction).

If such $ k $ does not exist, then output $ -1 $ .

## 说明/提示

In the first test case, you can take $ k $ equal to $ 2 $ and choose two segments \[ $ 1, 1 $ \] and \[ $ 2, 3 $ \], $ (1) | (2 \oplus 3) = 1 $ . It can be shown that $ 2 $ is the maximum possible answer.

In the second test case, the segments \[ $ 1, 1 $ \] and \[ $ 2, 2 $ \] are suitable, $ (1) | (1) = 1 $ . It is not possible to make more segments.

In the third test case, it is not possible to choose $ 2 $ segments, as $ (1) | (3) = 3 > 2 $ , so the optimal answer is $ 1 $ .

## 样例 #1

### 输入

```
8
3 1
1 2 3
2 2
1 1
2 2
1 3
2 3
0 0
3 2
0 0 1
4 2
1 3 3 7
2 2
2 3
5 0
0 1 2 2 1```

### 输出

```
2
2
1
2
3
-1
1
2```

# AI分析结果



**算法分类**  
位运算 + 贪心

---

### **题解思路与核心难点分析**

**题目核心**：将数组分割为最多段，使得各段异或值的按位或 ≤ x。

**关键难点**：  
1. **位运算特性**：高位决定数值大小，需优先处理高位约束。  
2. **动态分段**：需保证分割后的段满足所有位的约束，且尽可能多分。

**核心思路对比**：
1. **位分解策略**：所有题解均按位处理，从高位到低位枚举，优先满足高位约束。  
   - **lfxxx**：枚举x的每一位作为可能的最高有效位，检查该位以下是否可满足分段条件。  
   - **NightDiver**：若x某位为0，则强制所有段在该位的异或结果为0（需偶数个1）。  
   - **hao_zi6366**：通过掩码记录必须为0的位，贪心分割极短合法段。  

2. **贪心分段**：尽可能多分段的实现方式不同：  
   - **lfxxx**：维护当前位需为0的位集合，每次取最短合法前缀。  
   - **Exp10re**：类似数位DP，动态维护允许的分割点。  

---

### **题解评分（≥4星）**

1. **lfxxx（★★★★☆）**  
   - **亮点**：思路清晰，代码简洁，通过枚举x的每一位分情况处理。  
   - **优化点**：位分解与贪心结合，复杂度较低（O(n log²V)）。  

2. **NightDiver（★★★★☆）**  
   - **亮点**：图解直观，强调按位处理与强制分段条件。  
   - **不足**：代码未完整展示，但逻辑描述清晰。  

3. **hao_zi6366（★★★★☆）**  
   - **亮点**：掩码动态维护需处理的位，利用前缀异或和快速判断。  
   - **代码可读性**：逻辑简明，适合快速实现。  

---

### **最优思路提炼**

**关键步骤**：  
1. **位分解**：将x+1后，从高位到低位枚举每一位作为可能的最高有效位。  
2. **约束检查**：对于当前位及更高位，确保所有段的异或值在这些位上为0。  
3. **贪心分割**：从前向后扫描，每当当前段满足所有约束时立即分割，以最大化段数。  

**代码实现核心**：  
```cpp
int calc() {
    memset(cnt, 0, sizeof(cnt));
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        // 更新当前位的1的计数
        for (int x : dight) if (a[i] & (1LL << x)) cnt[x]++;
        // 检查是否所有约束位均为偶数
        bool valid = true;
        for (int x : dight) if (cnt[x] % 2) valid = false;
        if (valid) {
            memset(cnt, 0, sizeof(cnt)); // 重置计数器，分割段
            sum++;
        }
    }
    // 最终检查剩余位是否合法
    for (int x : dight) if (cnt[x] % 2) return -1;
    return sum;
}
```

---

### **同类问题推荐**

1. **CF1879D**：异或前缀和与位运算性质结合。  
2. **洛谷P2114**：位运算最大值问题，需逐位贪心。  
3. **CF1847C**：动态规划与异或性质结合的分段问题。  

---

### **可视化设计**

**动画方案**：  
1. **位分解展示**：  
   - 在Canvas中以二进制形式展示x和数组元素的每一位，高亮当前处理的位。  
   - 颜色标记：红色（当前处理位），绿色（已满足约束），灰色（未处理）。  

2. **分段过程**：  
   - 从左到右扫描数组，动态显示当前段的异或计算结果。  
   - 当段满足约束时，播放“分割”动画（如线段分割效果），并统计段数。  

3. **交互功能**：  
   - **步进控制**：允许单步执行，观察每位处理细节。  
   - **速度调节**：滑动条控制动画速度（0.5x~5x）。  

**复古像素风格**：  
- **8位音效**：分割成功时播放短促“叮”声，非法时播放“哔”声。  
- **像素网格**：数组元素显示为像素块，当前处理位闪烁提示。  

---

### **核心代码实现**

**贪心分割逻辑（lfxxx题解核心）**：  
```cpp
void work() {
    cin >> n >> x;
    x++; // 转换为严格小于
    for (int i = 1; i <= n; i++) cin >> a[i];
    ans = -1;
    vector<int> dight;
    for (int i = 30; i >= 0; i--) {
        if ((1LL << i) & x) { // 当前位是x的1，可能作为最高位
            dight.push_back(i);
            ans = max(ans, calc()); // 计算最大段数
            dight.pop_back();
        } else {
            dight.push_back(i); // 当前位必须为0
        }
    }
    cout << ans << '\n';
}
```

**完整代码**：见问题描述中lfxxx的代码部分。

---
处理用时：113.77秒