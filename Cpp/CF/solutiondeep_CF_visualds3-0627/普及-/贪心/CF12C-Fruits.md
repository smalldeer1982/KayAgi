# 题目信息

# Fruits

## 题目描述

The spring is coming and it means that a lot of fruits appear on the counters. One sunny day little boy Valera decided to go shopping. He made a list of $ m $ fruits he wanted to buy. If Valera want to buy more than one fruit of some kind, he includes it into the list several times.

When he came to the fruit stall of Ashot, he saw that the seller hadn't distributed price tags to the goods, but put all price tags on the counter. Later Ashot will attach every price tag to some kind of fruits, and Valera will be able to count the total price of all fruits from his list. But Valera wants to know now what can be the smallest total price (in case of the most «lucky» for him distribution of price tags) and the largest total price (in case of the most «unlucky» for him distribution of price tags).

## 样例 #1

### 输入

```
5 3
4 2 1 10 5
apple
orange
mango
```

### 输出

```
7 19
```

## 样例 #2

### 输入

```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```

### 输出

```
11 30
```

# AI分析结果



### 综合分析与结论

**题目核心**：将价格标签分配给水果，求总价的最小/最大值。关键在于贪心策略：数量多的水果分配更小（最小值）或更大（最大值）的价格。

**算法要点**：
1. **统计频次**：记录每种水果的出现次数。
2. **排序策略**：
   - 价格升序排列，频次降序排列 → 最小值（小价配高频）
   - 价格降序排列，频次降序排列 → 最大值（大价配高频）
3. **乘积求和**：按排序后的顺序相乘并累加。

**难点与解决**：
- 频次统计需高效去重 → 使用 `map` 或双重循环统计。
- 贪心正确性证明 → 通过排序不等式验证：有序数组乘积和的最值由同序/逆序相乘得到。

---

### 题解清单（评分≥4星）

1. **Fido_Puppy（★★★★☆）**
   - **亮点**：利用 `map` 快速统计频次，代码简洁；通过 `greater` 和 `less` 控制排序方向，逻辑清晰。
   - **代码可读性**：变量命名稍随意（如 `c` 数组），但整体结构紧凑。

2. **fls233666（★★★★☆）**
   - **亮点**：双重循环统计频次，避免 `map` 依赖；注释详细，适合教学。
   - **优化点**：手动去重效率略低，但数据规模下无影响。

---

### 最优思路与代码实现

**核心贪心逻辑**：
```cpp
// 统计频次后排序
sort(prices.begin(), prices.end());
sort(counts.rbegin(), counts.rend());

// 计算最小总价
int min_total = 0;
for (int i = 0; i < counts.size(); ++i) {
    min_total += counts[i] * prices[i];
}

// 计算最大总价（逆序取价格）
int max_total = 0;
for (int i = 0; i < counts.size(); ++i) {
    max_total += counts[i] * prices[prices.size() - 1 - i];
}
```

**完整代码（Fido_Puppy优化版）**：
```cpp
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> prices(n);
    for (int &p : prices) cin >> p;
    sort(prices.begin(), prices.end());

    map<string, int> freq_map;
    for (int i = 0; i < m; ++i) {
        string fruit;
        cin >> fruit;
        freq_map[fruit]++;
    }

    vector<int> counts;
    for (auto &entry : freq_map) {
        counts.push_back(entry.second);
    }
    sort(counts.rbegin(), counts.rend());

    int min_total = 0, max_total = 0;
    for (int i = 0; i < counts.size(); ++i) {
        min_total += counts[i] * prices[i];
        max_total += counts[i] * prices[n - 1 - i];
    }

    cout << min_total << " " << max_total << endl;
    return 0;
}
```

---

### 同类型题目与算法套路

**常见贪心场景**：
1. **区间调度**：选择不重叠的区间使数量最多（排序右端点）。
2. **最小代价合并**：如 Huffman 编码（优先队列）。
3. **任务分配**：按处理时间排序减少等待时间。

**洛谷推荐题目**：
1. **P1223 排队接水** - 贪心排序最小平均等待时间。
2. **P1094 纪念品分组** - 双指针贪心配对。
3. **P1080 国王游戏** - 贪心排序与高精度处理。

---

### 可视化设计要点（复古像素风格）

**动画流程**：
1. **初始网格**：用像素方块表示价格和频次数组，未排序时颜色为灰色。
2. **排序阶段**：
   - 价格升序排列 → 绿色渐变动画。
   - 频次降序排列 → 红色渐变动画。
3. **匹配阶段**：
   - 最小总价：黄色高亮当前频次与价格，连线并显示乘积。
   - 最大总价：紫色高亮，连线到价格数组末尾。
4. **音效触发**：
   - 排序完成：8-bit 上升音阶。
   - 匹配成功：短促“滴”声。

**交互功能**：
- **步进控制**：空格键单步执行排序和匹配。
- **自动播放**：AI 模式演示贪心过程，速度可调。
- **积分系统**：每正确匹配一次得10分，连击加成。

---

### 个人心得摘录

> **Fido_Puppy**：  
> “MAP 退役了，数组接上不就行了？” → 强调数据结构转换的灵活性。  
> **踩坑点**：未清空 `map` 会导致重复统计，需在存入数组后置零。

> **fls233666**：  
> “手动统计虽然笨，但胜在直观。” → 适合初学者的实现方式。

---
处理用时：78.33秒