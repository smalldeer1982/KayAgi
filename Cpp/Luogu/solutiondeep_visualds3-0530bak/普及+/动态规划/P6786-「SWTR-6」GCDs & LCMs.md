# 题目信息

# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# AI分析结果



## 算法分类
**线性DP**

---

## 综合分析与结论

### 核心思路与难点
题目要求构造满足特定数学条件的子序列。通过推导发现，当两个数满足条件时，其比例必须为 2:3。基于此，合法子序列在排序后构成公比为 3/2 的等比数列。

**关键难点**：快速判断某个数的 3/2 倍是否存在于数组中，并高效计算最大和。

**解决思路**：  
1. 将数组排序并去重，统计每个数的出现次数  
2. 对每个数尝试构造等比数列，累加所有可能的数的总和  
3. 使用 DP 或贪心方法记录以每个数为结尾的最大和  

### 可视化设计思路
- **动态展示**：以网格形式展示排序后的数组，高亮当前处理的数，并用箭头标记其 3/2 倍的数是否存在  
- **颜色标记**：绿色表示当前数被选中，红色表示无法继续扩展序列  
- **复古像素风格**：用 8-bit 音效提示状态转移（如成功扩展时播放上升音调，失败时短促音效）  
- **自动模式**：模拟贪心过程自动遍历每个数作为起点，动态显示序列扩展过程  

---

## 题解评分（≥4星）

### [Alex_Wei] ★★★★☆  
- **亮点**：数学推导严谨，代码简洁高效（map + 贪心遍历）  
- **优化点**：利用 map 快速查找并标记已处理元素，时间复杂度 O(n log n)  

### [Konnyaku_LXZ] ★★★★  
- **亮点**：完整数学证明，二分查找实现 O(n log n)  
- **心得摘录**："通过因式分解将问题转化为整数解问题，是本题突破口"

### [Rubidium_Chloride] ★★★★  
- **亮点**：详细注释 + 离散化处理，适合初学者理解  
- **可视化适配**：其桶计数思路可直接映射到像素动画的网格填充  

---

## 最优思路提炼
**关键技巧**：  
1. **数学构造**：合法序列必为 {x, 3x/2, (3/2)^2x, ...}  
2. **贪心遍历**：从每个数出发，不断乘以 3/2 找下一个数  
3. **状态标记**：用 map 或数组标记已处理的数，避免重复计算  

**代码核心逻辑**：
```cpp
sort(a, a + n); // 排序
map<int, int> cnt;
for (int num : a) cnt[num]++; // 统计出现次数

ll max_sum = 0;
for (int i = 0; i < n; ++i) {
    if (vis[a[i]]) continue; // 已处理过
    ll current = a[i], sum = 0;
    while (cnt.count(current)) {
        sum += current * cnt[current];
        vis[current] = true;
        if (current % 2 != 0) break; // 无法继续扩展
        current = current / 2 * 3; // 找下一个数
    }
    max_sum = max(max_sum, sum);
}
```

---

## 相似题目推荐
1. **P1895 数字序列** - 构造特定数学规律的序列  
2. **P2306 被替换的素数** - 数论条件判断 + 高效查找  
3. **P2678 跳石头** - 二分答案 + 贪心验证  

---

## 可视化实现（核心 DP 动画）

### 像素风格设计
- **颜色方案**：  
  - 白色格子：未处理的数  
  - 绿色格子：当前处理的序列  
  - 黄色箭头：3/2 倍关系转移  
- **音效触发**：  
  - `coin.wav`：成功扩展序列  
  - `error.wav`：无法继续扩展  

### Canvas 动画伪代码
```javascript
// 初始化
const grid = new PixelGrid(nums); 
grid.draw();

// 自动遍历
nums.forEach(num => {
    if (grid.isVisited(num)) return;
    
    let current = num;
    let chain = [];
    while (current in cnt) {
        chain.push(current);
        grid.highlight(current, COLOR_GREEN);
        playSound('coin.wav');
        
        if (current % 2 !== 0) break;
        const next = current * 3 / 2;
        if (!(next in cnt)) {
            grid.flash(current, COLOR_RED);
            playSound('error.wav');
            break;
        }
        current = next;
    }
    grid.markVisited(chain);
});
```

---

**总结**：本题核心在于数学推导后的问题转化，通过贪心或 DP 快速构造合法序列。可视化设计可强化对等比数列扩展过程的理解，复古像素风格增加学习趣味性。

---
处理用时：74.41秒