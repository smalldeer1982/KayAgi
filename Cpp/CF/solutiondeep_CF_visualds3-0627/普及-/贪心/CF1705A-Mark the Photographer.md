# 题目信息

# Mark the Photographer

## 题目描述

Mark is asked to take a group photo of $ 2n $ people. The $ i $ -th person has height $ h_i $ units.

To do so, he ordered these people into two rows, the front row and the back row, each consisting of $ n $ people. However, to ensure that everyone is seen properly, the $ j $ -th person of the back row must be at least $ x $ units taller than the $ j $ -th person of the front row for each $ j $ between $ 1 $ and $ n $ , inclusive.

Help Mark determine if this is possible.

## 说明/提示

In the first test case, one possible order is to have the third, fifth, and sixth person on the back row and the second, first, and fourth on the front row. The heights of the people will look like this.

 Back $ 9 $  $ 12 $  $ 16 $ Front $ 3 $  $ 1 $  $ 10 $ It works because

- $ h_3-h_2 = 9-3 \geq 6 $ ,
- $ h_5-h_1 = 12-1\geq 6 $ , and
- $ h_6-h_4 = 16-10\geq 6 $ .

In the second test case, it can be shown there is no way to order people in a way that satisfies the condition.

In the third test case, the only way to arrange people to satisfy the condition is to have the first person on the back row and the second person on the front row.

## 样例 #1

### 输入

```
3
3 6
1 3 9 10 12 16
3 1
2 5 2 2 2 5
1 2
8 6```

### 输出

```
YES
NO
YES```

# AI分析结果



---

### **综合分析与结论**

**题目核心**：将 $2n$ 人分为前后两排，要求后排第 $j$ 人比前排第 $j$ 人高至少 $x$，判断是否存在合法排列。

**贪心策略**：将身高排序后，前 $n$ 人作为前排，后 $n$ 人作为后排，检查每对 $(h_i, h_{i+n})$ 是否满足差 $\ge x$。  
**正确性证明**：若存在某对 $(h_i, h_{i+n})$ 差 $<x$，则无法构造合法排列（鸽巢原理：前 $i+n$ 人中必有两人在同一列，最大差为 $h_{i+n}-h_i$）。

**可视化设计**：  
1. **动画演示**：排序后的数组分两行显示，前排为前 $n$ 元素，后排为后 $n$ 元素。  
2. **颜色标记**：绿色表示差 $\ge x$，红色表示差 $<x$。  
3. **交互控制**：步进检查每对元素，支持暂停/继续/重置。  
4. **复古像素风**：用 8-bit 风格绘制人物方块，音效提示成功/失败。  
5. **自动模式**：AI 自动遍历所有配对，动态展示结果。

---

### **题解评分 (≥4星)**

1. **FFTotoro（5★）**  
   - **亮点**：代码简洁，直接使用 STL 排序，逻辑清晰。  
   - **证明引用**：鸽巢原理，直观易懂。

2. **Jeremiahy（4★）**  
   - **亮点**：反证法解释贪心正确性，代码可读性强。  
   - **注意点**：数组从 1 开始索引，需注意越界问题。

3. **happy_dengziyue（4★）**  
   - **亮点**：视频题解辅助理解，代码规范，边界处理明确。

---

### **最优思路提炼**

1. **排序策略**：升序排序，确保最小可能差异。  
2. **配对规则**：前 $n$ 与后 $n$ 直接对应，保证每列差最大化。  
3. **剪枝优化**：任一配对不满足立即终止，减少计算量。

**关键代码片段**：
```cpp
sort(a, a + 2*n); // 排序是关键
bool valid = true;
for (int i = 0; i < n; i++) {
    if (a[i+n] - a[i] < x) {
        valid = false;
        break;
    }
}
```

---

### **同类型题与算法套路**

**常见贪心场景**：  
1. **区间调度**：选择不重叠区间的最大数量。  
2. **任务分配**：最小化完成时间或最大化收益。  
3. **配对问题**：如本题，需满足特定条件的配对。

**通用解法**：排序 + 贪心选择，证明局部最优导致全局最优。

---

### **推荐题目**

1. **P1090 [NOIP2004 提高组] 合并果子**（贪心 + 优先队列）  
2. **P1223 [JSOI2008] 排队接水**（排序最小化平均等待时间）  
3. **P1012 [NOIP1998 提高组] 拼数**（字符串排序贪心）

---

### **个人心得摘录**

- **MH_SLC**：提醒注意循环边界，曾因索引错误导致 WA。  
- **sunkuangzheng**：手写归并排序虽冗余，但加深排序理解。  
- **yinhy09**：通过交换分析证明贪心最优性，强化逻辑推导。

---

### **可视化算法演示（伪代码）**

```javascript
// 初始化 Canvas
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

// 绘制排序后的数组
function drawArray(sortedArray, n, x) {
    // 前排：前 n 元素，后排：后 n 元素
    for (let i = 0; i < 2*n; i++) {
        drawPixelBlock(i, sortedArray[i], i < n ? 'blue' : 'green');
    }
}

// 检查并高亮当前配对
function checkPair(i, sortedArray, n, x) {
    const front = sortedArray[i];
    const back = sortedArray[i + n];
    const diff = back - front;
    // 高亮颜色：diff >=x ? 'green' : 'red'
    // 播放音效：成功/失败
}

// 自动演示逻辑
function autoCheck(sortedArray, n, x) {
    for (let i = 0; i < n; i++) {
        checkPair(i, sortedArray, n, x);
        if (diff < x) break;
    }
}
```

**复古风格设计**：  
- **像素块**：每个身高用 16x16 像素块表示，颜色区分前后排。  
- **音效**：8-bit 风格音效，成功时“滴”声，失败时“嘟”声。  
- **自动模式**：模拟贪心 AI 逐步决策，用户可干预暂停。

---

**结论**：通过排序与贪心配对策略，结合可视化交互，可高效判断是否存在合法排列。

---
处理用时：79.99秒