# 题目信息

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 5 1
5 8
```

### 输出

```
9
```

# AI分析结果



## 唯一算法分类
二分答案 + 差分数组

---

## 综合分析与结论
### 题解核心思路
1. **二分答案框架**：通过二分查找确定可能的最大最小值，验证每个候选值是否可行。
2. **差分数组优化**：用差分数组记录区间浇水操作，将区间加减优化为O(1)操作，累计前缀和实时计算当前花的高度。
3. **贪心策略**：从左到右遍历，遇到不足目标值的花时，在其右侧连续w个位置进行浇水，确保每个位置达到目标值。

### 解决难点
- **高效区间更新**：传统暴力区间加时间复杂度高，差分数组将区间操作转换为两个端点操作。
- **边界处理**：当浇水区间的右端点超出数组范围时，需截断至数组末尾。
- **实时水量追踪**：通过维护当前已浇水量，避免重复计算。

### 可视化设计
- **动画方案**：展示二分过程，高亮当前检查的mid值。用不同颜色标记浇水区间，实时显示差分数组更新和前缀和计算。
- **像素风格**：用8-bit风格绘制花的高度条，浇水时显示绿色脉冲特效，音效触发区间操作和二分验证结果。
- **交互控制**：支持暂停/继续、调整二分步长，展示差分数组的数学表达式推导过程。

---

## 题解清单（≥4星）

### 1. YuRuiH_（★★★★★）
- **亮点**：差分数组与动态维护当前浇水量的实现简洁高效，代码可读性强。
- **代码片段**：
```cpp
bool can(int s){
    int a=0, b=m;
    for(int i=1;i<=n;i++){
        if(i>=w) a -= need[i-w];
        need[i] = max(0, s - a - f[i]);
        a += need[i]; b -= need[i];
        if(b<0) return false;
    }
    return true;
}
```

### 2. Karry5307（★★★★☆）
- **亮点**：清晰展示贪心策略与差分数组的结合，处理边界条件严谨。
- **关键变量**：`diff`数组记录差值，`cur`维护当前剩余天数。

### 3. Sol1（★★★★☆）
- **亮点**：详细注释与教学式代码结构，特别适合初学者理解差分机制。
- **可视化提示**：在代码中加入调试输出语句，直观展示差分数组变化。

---

## 核心代码实现
```cpp
bool check(int mid) {
    vector<int> diff(n + 2, 0); // 差分数组
    int current = 0, days_used = 0;
    for (int i = 0; i < n; ++i) {
        current += diff[i]; // 计算当前花的高度
        if (current < mid) {
            int add = mid - current; // 需要增加的天数
            days_used += add;
            if (days_used > m) return false;
            diff[i] += add;          // 左端点加add
            if(i + w < n) diff[i + w] -= add; // 右端点减add
            current = mid; // 当前花高度已达目标
        }
    }
    return true;
}
```

---

## 相似题目推荐
1. **P2879** Tallest Cow（差分数组应用）
2. **P1083** 借教室（二分答案+差分验证）
3. **P2216** 理想的正方形（二维滑动窗口）

---

## 可视化与算法演示
### 动画设计
1. **像素画布**：用16色像素块表示花的高度，红色标记当前检查的mid值。
2. **浇水特效**：绿色光波从左到右覆盖浇水区间，伴随"滴答"音效。
3. **差分可视化**：右侧面板显示差分数组数学表达式，实时更新端点操作。

### 复古元素
- **8-bit音效**：区间加减时播放FC游戏《超级马里奥》金币音效，二分成功时播放升级音效。
- **积分系统**：正确通过检查函数获得10分，优化浇水策略额外奖励5分。

---

## 个人心得摘录
> "差分数组的L到R全加D操作：b[L]+=x; b[R+1]-=x; 这题R可能会超边界，记得特殊处理" —— YuRuiH_  
> 调试时发现未处理右边界导致数组越界，通过`min(i + w, n)`解决，强调边界检查的重要性。

---

通过二分答案框架与差分数组的完美结合，该算法在时间效率与代码简洁性上达到最优，是处理区间操作类问题的经典范式。

---
处理用时：75.07秒