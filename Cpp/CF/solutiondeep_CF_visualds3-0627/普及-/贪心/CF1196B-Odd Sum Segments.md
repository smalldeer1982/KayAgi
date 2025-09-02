# 题目信息

# Odd Sum Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . You want to split it into exactly $ k $ non-empty non-intersecting subsegments such that each subsegment has odd sum (i. e. for each subsegment, the sum of all elements that belong to this subsegment is odd). It is impossible to rearrange (shuffle) the elements of a given array. Each of the $ n $ elements of the array $ a $ must belong to exactly one of the $ k $ subsegments.

Let's see some examples of dividing the array of length $ 5 $ into $ 3 $ subsegments (not necessarily with odd sums): $ [1, 2, 3, 4, 5] $ is the initial array, then all possible ways to divide it into $ 3 $ non-empty non-intersecting subsegments are described below:

- $ [1], [2], [3, 4, 5] $ ;
- $ [1], [2, 3], [4, 5] $ ;
- $ [1], [2, 3, 4], [5] $ ;
- $ [1, 2], [3], [4, 5] $ ;
- $ [1, 2], [3, 4], [5] $ ;
- $ [1, 2, 3], [4], [5] $ .

Of course, it can be impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements. In this case print "NO". Otherwise, print "YES" and any possible division of the array. See the output format for the detailed explanation.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```

### 输出

```
YES
1 3 5
NO
NO
```

# AI分析结果



### 综合分析与结论

**题目核心**：将数组分割为恰好 $k$ 个连续子段，每个子段和为奇数。  
**关键条件**：  
1. 奇数总数 $\text{sum} \geq k$  
2. $\text{sum} - k$ 为偶数（确保最后一子段奇数和）  

**贪心策略**：  
- 直接统计奇数位置，取前 $k-1$ 个奇数作为分割点，剩余部分到数组末尾。  
- 正确性：每个分割点后的子段至少含一个奇数，最后一子段奇数和由条件保证。

**可视化设计思路**：  
- **像素风格**：红色方块表示奇数，蓝色为偶数，绿色竖线为分割点。  
- **动画逻辑**：高亮前 $k-1$ 个奇数位置，最后一子段覆盖剩余部分，动态显示每段和。  
- **音效与交互**：正确时播放上扬音效，错误时短促音效，支持自动播放与步进控制。

---

### 题解评分（≥4星）

1. **__shadow__（5星）**  
   - 亮点：直接统计奇数位置，条件判断简洁，代码高效。  
   - 个人心得：通过奇偶性分析快速推导条件，避免复杂遍历。

2. **xh001（4星）**  
   - 亮点：代码清晰，条件处理明确，适合快速实现。  
   - 关键代码：统计奇数并验证 `(sum - k) % 2 == 0`。

3. **xukuan（4星）**  
   - 亮点：数学推导清晰，代码简洁，强调奇偶性本质。  
   - 代码片段：`if (sum >=k && (sum-k)%2==0)`。

---

### 核心代码实现

**__shadow__ 的代码片段**  
```cpp
int sum = 0, a[N]; // 存储奇数位置
if (sum >= k && (sum - k) % 2 == 0) {
    printf("YES\n");
    for (int i = 1; i < k; i++) printf("%d ", a[i]);
    printf("%d\n", n);
}
```

**代码逻辑**：  
1. 遍历数组，记录所有奇数位置。  
2. 检查条件：奇数数≥k且剩余奇数为偶数个。  
3. 输出前 $k-1$ 个奇数位置，最后一子段到末尾。

---

### 同类型题目与套路

**通用贪心思路**：  
- **奇偶性统计**：利用元素属性的奇偶性快速推导条件。  
- **分段验证**：通过局部最优（前 $k-1$ 段）保证全局最优。

**推荐题目**：  
1. **P1031 均分纸牌**（贪心移动策略）  
2. **P1220 关路灯**（区间选择与代价优化）  
3. **P1106 删数问题**（字符删除的贪心决策）

---

### 个人心得摘录

- **边界条件**：当 $k=1$ 时，整个数组和必须为奇数。  
- **调试技巧**：构造极例（全奇数或全偶数）验证条件。  
- **数学直觉**：奇偶性规律是解题突破口，避免复杂遍历。

---

### 可视化算法演示（伪代码）

```javascript
// 伪代码：Canvas 绘制数组与分割点
function drawSegments() {
    for (let i = 0; i < array.length; i++) {
        if (array[i] % 2 === 1) drawRedSquare(i);    // 奇数红色
        else drawBlueSquare(i);                      // 偶数蓝色
        if (i in splitPoints) drawGreenLine(i);      // 分割线绿色
    }
    if (valid) playSuccessSound();                   // 成功音效
}
```

**交互设计**：  
- **自动模式**：逐步显示分割点选择，动态计算每段和。  
- **关卡积分**：正确分割一段得10分，连击奖励翻倍。

---
处理用时：218.46秒