# 题目信息

# Virus

## 题目描述

There are $ n $ houses numbered from $ 1 $ to $ n $ on a circle. For each $ 1 \leq i \leq n - 1 $ , house $ i $ and house $ i + 1 $ are neighbours; additionally, house $ n $ and house $ 1 $ are also neighbours.

Initially, $ m $ of these $ n $ houses are infected by a deadly virus. Each morning, Cirno can choose a house which is uninfected and protect the house from being infected permanently.

Every day, the following things happen in order:

- Cirno chooses an uninfected house, and protect it permanently.
- All uninfected, unprotected houses which have at least one infected neighbor become infected.

Cirno wants to stop the virus from spreading. Find the minimum number of houses that will be infected in the end, if she optimally choose the houses to protect.

Note that every day Cirno always chooses a house to protect before the virus spreads. Also, a protected house will not be infected forever.

## 说明/提示

In the first test case:

At the start of the first day, house $ 3 $ , $ 6 $ , $ 8 $ are infected. Choose house $ 2 $ to protect.

At the start of the second day, house $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , $ 7 $ , $ 8 $ , $ 9 $ are infected. Choose house $ 10 $ to protect.

At the start of the third day, no more houses are infected.

In the second test case:

At the start of the first day, house $ 2 $ , $ 5 $ are infected. Choose house $ 1 $ to protect.

At the start of the second day, house $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ are infected. No more available houses can be protected.

## 样例 #1

### 输入

```
8
10 3
3 6 8
6 2
2 5
20 3
3 7 12
41 5
1 11 21 31 41
10 5
2 4 6 8 10
5 5
3 2 5 4 1
1000000000 1
1
1000000000 4
1 1000000000 10 16```

### 输出

```
7
5
11
28
9
5
2
15```

# AI分析结果



### 综合分析与结论

**问题核心**：环形排列的房屋被初始感染点分割为多个未感染段。通过贪心策略选择保护点以最小化最终感染数。

**贪心策略**：
1. **段排序**：计算所有未被感染段的长度，按降序排列。
2. **按序处理**：优先处理最长段，每次保护操作减少其可能被感染的区域。
3. **动态更新**：每次保护后，其他段的剩余长度会随时间（操作次数）减少，需动态调整计算。

**关键难点**：
- **环形首尾处理**：需合并首尾段。
- **时间衰减模型**：已进行的保护操作会影响后续段的剩余有效长度。

**题解共性**：均采用降序处理段的策略，但实现方式不同。例如，Hovery的代码通过`now`变量跟踪已用操作次数，而yinhy09使用`k`变量累计减去的长度。

### 题解评分（≥4星）

1. **Hovery（5星）**  
   - **亮点**：思路清晰，代码简洁，直接计算每个段的剩余可保护量。动态维护`now`变量，逻辑直观。
   - **关键代码**：
     ```cpp
     sort(b + 1, b + cnt + 1, cmp);
     int now = 0, ans = 0;
     for (int i = 1; i <= cnt; i++) {
         if (now * 2 < b[i]) {
             ans += b[i] - now * 2 - ((b[i] - now * 2 == 1) ? 0 : 1);
             now += ((b[i] - now * 2 == 1) ? 1 : 2);
         }
     }
     ```

2. **yinhy09（4星）**  
   - **亮点**：引入`k`变量表示已处理次数，通过`4*k`计算长度衰减。代码注释详细，便于理解。
   - **关键代码**：
     ```cpp
     for(int i=tot-1; i>=1; i--) {
         k++;
         if(b[i] == 4*k+1) ans++;
         else if(b[i] >4*k+1) ans += b[i]-4*k-1;
     }
     ```

3. **happy_dengziyue（4星）**  
   - **亮点**：分情况讨论剩余长度，逻辑严谨。代码变量命名清晰，易维护。
   - **关键代码**：
     ```cpp
     if(b[i]-s <=0) continue;
     if(b[i]-s <=2) ans++, s++;
     else ans += b[i]-s-1, s +=2;
     ```

### 最优思路提炼

1. **排序策略**：将未感染段按长度降序排列，优先处理最长段。
2. **动态衰减模型**：每处理一个段，后续段的剩余有效长度需减去已用操作次数的两倍（或类似模型）。
3. **保护规则**：
   - 若剩余长度≤2，只能保护1个房子。
   - 否则，保护剩余长度-1个房子，需两次操作（保护两端）。

### 同类型题目推荐

1. **P1230 智力大冲浪**（贪心选择时间段）
2. **P1803 线段覆盖**（区间调度问题）
3. **P1094 纪念品分组**（双指针贪心）

### 可视化与算法演示

**动画设计**：
1. **像素风格**：使用Canvas绘制环形房屋，红色表示感染，绿色保护，灰色未感染。
2. **贪心过程**：
   - 高亮当前最长段，显示其长度。
   - 模拟保护操作：点击或自动选择保护点，播放“保护音效”。
   - 病毒传播：被感染区域向中间扩散，显示剩余段更新。
3. **控制面板**：支持暂停/继续、调整速度、重置案例。

**复古游戏化**：
- **音效**：8-bit音效，保护成功时“叮”，感染时“嘟”。
- **积分系统**：每正确保护一个段得分，连击加分。
- **自动演示**：AI自动选择最优策略，观察保护顺序。

**代码片段（JS）**：
```javascript
// 初始化段数据
let segments = [5, 3, 7]; // 示例段长度
segments.sort((a, b) => b - a);

// 自动演示逻辑
let now = 0, protected = 0;
segments.forEach(seg => {
    let remain = seg - now * 2;
    if (remain <= 0) return;
    if (remain <= 2) {
        protected += 1;
        now += 1;
    } else {
        protected += remain - 1;
        now += 2;
    }
    // 更新动画
    drawSegment(seg, remain);
    playSound('protect');
});
```

### 个人心得摘录

- **环的处理**：合并首尾段时易出错，需仔细计算。
- **边界条件**：当段长≤2时需特判，否则可能导致负数计算。
- **贪心正确性**：通过反例验证策略，如先处理小段会导致大段无法完全保护。

---
处理用时：98.56秒