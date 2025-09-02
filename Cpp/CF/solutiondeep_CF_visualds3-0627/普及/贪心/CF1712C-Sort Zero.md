# 题目信息

# Sort Zero

## 题目描述

An array is sorted if it has no inversions

A Young Boy



You are given an array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ .

In one operation you do the following:

1. Choose any integer $ x $ .
2. For all $ i $ such that $ a_i = x $ , do $ a_i := 0 $ (assign $ 0 $ to $ a_i $ ).

Find the minimum number of operations required to sort the array in non-decreasing order.

## 说明/提示

In the first test case, you can choose $ x = 3 $ for the operation, the resulting array is $ [0, 0, 2] $ .

In the second test case, you can choose $ x = 1 $ for the first operation and $ x = 3 $ for the second operation, the resulting array is $ [0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
5
3
3 3 2
4
1 3 1 3
5
4 1 5 3 2
4
2 4 1 2
1
1```

### 输出

```
1
2
4
3
0```

# AI分析结果



## 综合分析与结论

### 核心思路与贪心策略
本题的核心在于通过最少的操作将数组变为非递减序列。贪心策略的关键在于找到必须处理的元素范围，确保所有可能破坏非降序的元素被置0。具体步骤如下：
1. **确定最长非递减后缀**：从后往前遍历，找到第一个破坏非递减的位置i，此时需处理区间[1, i]。
2. **扩展处理边界**：遍历该区间，记录每个元素的最远出现位置。若某个元素的最远位置超过当前边界，则扩展边界。
3. **统计不同元素数量**：区间内所有不同的元素数量即为最小操作次数。

### 题解对比与评分
- **LKY928261（5星）**  
  思路清晰，通过记录元素最晚出现位置，动态扩展处理边界，时间复杂度O(n)。代码简洁高效，可读性强。
- **hanyuchen2019（4星）**  
  使用“连锁反应”描述处理过程，代码直观，但部分实现冗余（如多次遍历）。
- **YYHDoggy（4星）**  
  逻辑明确，利用`lst`数组记录最后出现位置，通过一次遍历确定边界，代码简洁。

### 最优思路提炼
1. **逆向查找破坏点**：从后找到第一个a[i] > a[i+1]的位置i。
2. **动态边界扩展**：处理区间内的元素时，不断更新边界至元素的最远出现位置。
3. **统计唯一元素**：只需统计区间内不同元素的数量。

### 同类型题目
- 区间覆盖问题（如选择最少区间覆盖全部）
- 活动选择问题（贪心选最早结束）
- 删除数字使最小（单调栈）

### 推荐题目
1. P1223 排队接水（贪心排序）
2. P1803 线段覆盖（贪心选区间）
3. P1090 合并果子（优先队列贪心）

---

## 题解代码（LKY928261）

```cpp
#include<bits/stdc++.h>
using namespace std;

int T, n, t, ans, a[100005], nxt[100005];
bool f[100005];

void work() {
    cin >> n;
    for(int i = 1; i <= n; i++) nxt[i] = f[i] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        nxt[a[i]] = max(nxt[a[i]], i); // 记录最晚出现位置
    }
    int i;
    for(i = n; i > 1; i--) 
        if(a[i] < a[i-1]) break; // 找到破坏点
    t = i - 1; ans = 0;
    for(i = 1; i <= t; i++) {
        if(!f[a[i]]) ans++; // 统计不同元素
        f[a[i]] = 1;
        t = max(t, nxt[a[i]]); // 扩展边界
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); 
    cin >> T; 
    while(T--) work();
}
```

**核心思想**：通过`nxt`数组记录每个元素的最后出现位置，动态扩展处理边界`t`，确保所有相关元素被处理，统计不同元素数量即为答案。

---

## 可视化设计（贪心过程）

### 动画方案
1. **初始状态**：数组显示为不同颜色块，非递减后缀高亮为绿色。
2. **寻找破坏点**：红色标记第一个a[i] > a[i+1]的位置i。
3. **处理区间扩展**：
   - 遍历[1, t]元素，若元素未处理（黄色），将其变为红色并扩展t到最远出现位置。
   - 每次扩展后，更新处理边界为红色区域。
4. **统计操作次数**：显示不同颜色的数量。

### 复古像素风格
- **Canvas绘制**：数组元素为8位像素块，处理时闪烁并变灰。
- **音效**：处理元素时播放“哔”声，边界扩展时低音提示。
- **自动演示**：按步执行，间隔500ms，可暂停/调整速度。

### 交互示例
1. **步进按钮**：手动控制每一步处理。
2. **速度调节**：滑动条控制动画速度。
3. **高亮显示**：当前处理元素及最远位置动态标红。

---

通过此可视化，学习者可直观理解贪心策略的动态扩展过程及操作次数的统计逻辑，加深对贪心选择的理解。

---
处理用时：87.43秒