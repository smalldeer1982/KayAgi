# 题目信息

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
3
1 2 4
```

### 输出

```
1
4
```

# AI分析结果



**唯一算法分类**  
贪心算法

---

**综合分析与结论**  
本题的核心在于通过贪心策略，从高位到低位枚举可能的最大v值。对于每个v，收集所有二进制第v位为1的数，并检查这些数的按位与结果是否能被2^v整除（即低v位全为0）。若满足条件，则输出对应的数集。关键在于如何高效判断按位与结果的低v位是否为0，两位题解分别采用模运算和位掩码实现这一目标。

**可视化设计思路**  
- **枚举过程**：以二进制位网格展示当前枚举的v值，高亮第v位。  
- **数筛选**：动态标记所有第v位为1的数，显示其二进制形式。  
- **按位与计算**：实时显示选中数的按位与结果，低v位用不同颜色标记（如红色为非0，绿色为全0）。  
- **音效与动画**：选中数时播放“点击”音效，条件满足时播放胜利音效，背景采用8-bit风格音乐。

---

**题解清单 (≥4星)**  
1. **Rye_Catcher的题解（5星）**  
   - **关键亮点**：利用位掩码提前终止循环，高效判断低v位是否为0。代码简洁且效率高。  
   - **代码片段**：  
     ```cpp
     for (int k = 30; k >= 0; k--) {
         int x = (1 << k), y = x - 1;
         vector<int> q;
         for (int a_i : a) {
             if (a_i & x) {
                 y &= a_i;
                 q.push_back(a_i);
             }
         }
         if (y == 0) return q; // 满足条件
     }
     ```

2. **Graphcity的题解（4星）**  
   - **关键亮点**：直接计算按位与结果后取模判断，思路清晰易懂。  
   - **代码片段**：  
     ```cpp
     for (int i = 30; i >= 0; i--) {
         vector<int> candidates;
         int res = -1;
         for (int num : a) {
             if (num & (1 << i)) {
                 candidates.push_back(num);
                 res &= num; // 计算按位与
             }
         }
         if (res % (1 << i) == 0 && !candidates.empty()) {
             return candidates; // 满足条件
         }
     }
     ```

---

**最优思路或技巧提炼**  
1. **贪心枚举高位**：从最高位（如30）开始枚举，确保找到最大的v。  
2. **位掩码优化**：利用 `y = (1 << v) - 1` 初始化掩码，通过按位与操作快速判断低v位是否全为0。  
3. **提前终止**：在计算按位与时，若掩码已为0，可提前终止遍历，提升效率。

---

**同类型题或类似算法套路**  
- **位运算贪心**：常见于需要逐位确定最优解的问题，如最大异或对、位掩码动态规划等。  
- **子集筛选优化**：通过条件快速筛选候选数，减少无效计算。

---

**推荐相似题目**  
1. [P2114 起床困难综合症](https://www.luogu.com.cn/problem/P2114)  
2. [P4310 绝世好题](https://www.luogu.com.cn/problem/P4310)  
3. [P1594 护卫队](https://www.luogu.com.cn/problem/P1594)

---

**个人心得摘录**  
- **位运算陷阱**：注意运算符优先级，多用括号避免逻辑错误。  
- **初始值设置**：按位与的初始值应为全1（如掩码），避免初始0导致结果错误。  
- **调试技巧**：打印二进制中间结果，直观验证条件判断。

---

**可视化与算法演示**  
```javascript
// 伪代码示例：Canvas绘制二进制位与动画
function visualize() {
    const bits = 8; // 8位二进制展示
    let currentV = bits - 1;
    let candidates = [];

    function draw() {
        // 绘制当前v位高亮
        drawHighlight(currentV, 'yellow');
        // 绘制所有数的二进制表示
        numbers.forEach(num => {
            drawBinary(num, currentV, num & (1 << currentV) ? 'green' : 'gray');
        });
        // 显示按位与结果
        let mask = (1 << currentV) - 1;
        let result = candidates.reduce((acc, num) => acc & num, mask);
        drawBinary(result, currentV, (result & mask) === 0 ? 'blue' : 'red');
    }

    // 步进逻辑
    function step() {
        if (currentV < 0) return;
        candidates = numbers.filter(num => num & (1 << currentV));
        let mask = (1 << currentV) - 1;
        let result = candidates.reduce((acc, num) => acc & num, mask);
        if (result === 0 && candidates.length > 0) {
            playSuccessSound();
            drawFinalResult(currentV, candidates);
        } else {
            currentV--;
            draw();
        }
    }
}
```

**复古像素风格设计**  
- **调色板**：16色FC风格，绿色表示选中位，红色为错误，蓝色为正确结果。  
- **音效**：点击（8-bit "blip"），成功（上升音阶），失败（短促低音）。  
- **自动演示**：按帧逐步降低v值，模拟AI决策过程。

---
处理用时：424.78秒