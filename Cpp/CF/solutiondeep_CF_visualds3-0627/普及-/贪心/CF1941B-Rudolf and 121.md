# 题目信息

# Rudolf and 121

## 题目描述

Rudolf has an array $ a $ of $ n $ integers, the elements are numbered from $ 1 $ to $ n $ .

In one operation, he can choose an index $ i $ ( $ 2 \le i \le n - 1 $ ) and assign:

- $ a_{i - 1} = a_{i - 1} - 1 $
- $ a_i = a_i - 2 $
- $ a_{i + 1} = a_{i + 1} - 1 $

Rudolf can apply this operation any number of times. Any index $ i $ can be used zero or more times.

Can he make all the elements of the array equal to zero using this operation?

## 说明/提示

In the first example, the original array is $ [1, 3, 5, 5, 2] $ , to make all its elements zero, Rudolf can act as follows:

- apply the operation at $ i=4 $ and get the array $ [1, 3, 4, 3, 1] $ ;
- apply the operation at $ i=3 $ and get the array $ [1, 2, 2, 2, 1] $ ;
- apply the operation at $ i=2 $ and get the array $ [0, 0, 1, 2, 1] $ ;
- apply the operation at $ i=4 $ and get the array $ [0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7
5
1 3 5 5 2
5
2 4 4 5 1
5
0 1 3 3 1
6
5 6 0 2 3 0
4
1 2 7 2
3
7 1 0
4
1 1 1 1```

### 输出

```
YES
NO
YES
NO
NO
NO
NO```

# AI分析结果



### 一、题解思路与算法要点

#### 核心贪心策略与推导
1. **贪心选择依据**：从左到右处理每个元素，每次将当前元素清零，通过后续操作调整右侧元素。
2. **操作转换**：将原操作等价转换为对 `i`, `i+1`, `i+2` 的影响，使得处理顺序不影响已处理的左侧元素。
3. **数学推导**：每个元素 `a[i]` 的值必须由其右侧的 `i+1` 和 `i+2` 来消除。若过程中出现负数或最终剩余非零元素则无解。

#### 解决难点
- **操作顺序的不可逆性**：必须确保每个元素处理完成后，后续操作不会破坏已清零的状态。
- **负数检测**：在贪心过程中必须实时检测是否出现负数，若出现则直接终止。
- **边界处理**：最后两个元素需单独验证是否为零。

---

### 二、题解评分（≥4星的题解）

| 题解作者 | 评分 | 关键亮点 |
|---------|------|---------|
| littlebug (8赞) | ⭐⭐⭐⭐⭐ | 思路清晰，代码简洁，时间复杂度O(n)，通过操作转换简化问题 |
| lalaji2010 (1赞) | ⭐⭐⭐⭐ | 明确贪心顺序无关性，代码逻辑简明 |
| Stone_Xz (1赞) | ⭐⭐⭐⭐ | 详细推导操作转换过程，附可视化思路 |

---

### 三、最优思路与技巧提炼

#### 关键贪心步骤
1. **线性遍历**：从左到右处理每个元素 `i`（`1 ≤ i ≤ n-2`）。
2. **消除当前元素**：将 `a[i]` 的值通过后续操作完全消除：
   ```cpp
   a[i+1] -= a[i] * 2;
   a[i+2] -= a[i];
   a[i] = 0;
   ```
3. **实时检测负数**：若 `a[i+1]` 或 `a[i+2]` 变为负数，则立即判定无解。
4. **最终验证**：最后两个元素必须为零。

#### 实现细节
- **操作顺序不可逆**：处理完 `i` 后，其值不再变化。
- **边界处理**：无需处理最后两个元素，仅需最终验证。

---

### 四、同类型题与算法套路

#### 类似贪心问题
1. **区间覆盖**：每次操作影响连续区间（如CF1525B Permutation Sort）。
2. **元素归零**：通过固定模式操作将数组归零（如LeetCode 1347）。
3. **操作传播**：单个操作影响相邻元素（如LeetCode 995）。

#### 通用解法
- **线性贪心**：按固定顺序处理元素，保证局部最优性。
- **数学建模**：将操作转化为数学关系式，避免模拟每一步。

---

### 五、推荐相似题目
1. **CF1525B**：通过特定操作使数组有序。
2. **LeetCode 1347**：最小操作使字符串平衡。
3. **洛谷P1223**：贪心调度问题。

---

### 六、代码实现与核心逻辑

#### 关键代码片段（littlebug解法）
```cpp
for(int i=1; i<=n-2; ++i) {
    if(a[i]<0) return "NO";
    a[i+1] -= a[i]*2; // 消除当前元素的影响
    a[i+2] -= a[i];
}
return (a[n-1]==0 && a[n]==0) ? "YES" : "NO";
```

---

### 七、可视化与算法演示设计

#### 复古像素化动画方案
1. **Canvas网格**：数组元素以8位像素方块显示，颜色标记当前处理位置。
2. **步进控制**：
   - **高亮当前i**：黄色边框标记当前处理的 `i`。
   - **数值变化动画**：右侧元素 `i+1` 和 `i+2` 数值减少时显示红色闪烁。
3. **音效设计**：
   - **操作成功**：清脆的“滴”声。
   - **出现负数**：低沉的“嗡”声警告。
4. **自动模式**：AI逐步处理元素，速度可调（1x/2x/5x）。

#### 交互示例
```javascript
// 伪代码：Canvas绘制与动画逻辑
function drawArray(arr, currentIndex) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let i=0; i<arr.length; i++) {
        ctx.fillStyle = (i === currentIndex) ? "#FFFF00" : "#FFFFFF";
        ctx.fillRect(i*50, 0, 40, 40); // 绘制像素方块
        ctx.fillText(arr[i], i*50 + 15, 25); // 显示数值
    }
}
```

---

### 八、总结与结论
1. **贪心策略的有效性**：通过操作转换和线性遍历确保每一步的局部最优性。
2. **复杂度优势**：O(n)时间复杂度，无冗余计算。
3. **可视化价值**：通过复古风格动画和音效强化对贪心过程的理解。

---
处理用时：75.98秒