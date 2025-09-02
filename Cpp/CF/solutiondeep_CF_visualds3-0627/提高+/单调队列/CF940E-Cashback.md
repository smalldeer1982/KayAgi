# 题目信息

# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10
```

### 输出

```
92
```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1
```

### 输出

```
17
```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1
```

### 输出

```
23
```

# AI分析结果



## 算法分类
动态规划 + 单调队列/滑动窗口

---

## 题解核心思路与解决难点

### 核心思路
所有题解均基于以下关键发现：
1. **最优分段长度只可能为 1 或 c**  
   - 若分段长度 $k < c$：无法删除元素，等效于分成 $k$ 个长度为 1 的段。
   - 若 $k \geq c$：拆分为多个长度为 $c$ 的段更优，因为合并后的段删除的数值总和不会更大。

2. **动态规划状态转移**  
   - 定义 $f[i]$ 表示前 $i$ 个元素的最小剩余和，转移方程为：
     \[
     f[i] = \min(f[i-1] + a[i], \quad f[i-c] + \text{sum}(i-c+1 \sim i) - \text{min}(i-c+1 \sim i))
     \]
   - 其中 `sum` 为区间和，`min` 为区间最小值。

3. **区间最小值预处理**  
   - 使用单调队列维护滑动窗口最小值，时间复杂度 $O(n)$。
   - 其他实现方式包括线段树（$O(n \log n)$）或 ST 表（预处理后 $O(1)$ 查询）。

### 解决难点
- **证明分段最优性**：通过数学归纳与反证法，说明合并长段不会比拆分为 $c$ 长度段更优。
- **高效维护区间最小值**：单调队列在滑动窗口场景下效率最高，优于线段树和 ST 表。
- **边界处理**：如初始段长度不足 $c$ 时的处理，避免数组越界。

---

## 题解评分（≥4星）

### 1. Alarm5854（★★★★☆）
- **亮点**：思路清晰，代码简洁高效，使用单调队列预处理最小值，时间复杂度 $O(n)$。
- **代码片段**：
  ```cpp
  // 单调队列维护最小值
  for (ll i = 1; i <= n; ++i) {
      while (h <= t && q[h] + c <= i) q[h++] = 0;
      while (h <= t && a[q[t]] >= a[i]) q[t--] = 0;
      q[++t] = i, minn[i] = a[q[h]];
  }
  ```

### 2. 字如其人（★★★★☆）
- **亮点**：代码简洁，动态规划与单调队列结合紧密，预处理与转移逻辑清晰。
- **代码片段**：
  ```cpp
  // DP转移逻辑
  for(int i=1;i<=n;i++){
      if(i>=c)f[i]=min(f[i],f[i-c]+s[i]-s[i-c]-minn[i]);
      f[i]=min(f[i],f[i-1]+a[i]);
  }
  ```

### 3. Mickey_snow（★★★★☆）
- **亮点**：使用线段树维护区间最小值，代码结构清晰，适合理解基础实现。
- **代码片段**：
  ```cpp
  // 线段树查询区间最小值
  int query(int da,int l,int r){
      if(tr[da].l >= l && tr[da].r <= r) return tr[da].mmin;
      int ans=0x3f3f3f3f3f3f3f3f;
      if(l <= mid) ans = min(ans,query(da<<1,l,r));
      if(r > mid) ans = min(ans,query(da<<1|1,l,r));
      return ans;
  }
  ```

---

## 关键代码实现（Alarm5854 题解）

### 核心逻辑代码
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<algorithm>
#define ll long long
const ll N = 1e5 + 10; 
using namespace std;

ll n, c, h, t, q[N], a[N], s[N], dp[N], minn[N];

int main() {
    n = read(), c = read();
    for (ll i = 1; i <= n; ++i) a[i] = read(), s[i] = s[i - 1] + a[i];
    // 单调队列预处理区间最小值
    for (ll i = 1; i <= n; ++i) {
        while (h <= t && q[h] + c <= i) h++;
        while (h <= t && a[q[t]] >= a[i]) t--;
        q[++t] = i, minn[i] = a[q[h]];
    }
    // 动态规划转移
    for (ll i = 1; i < c; ++i) dp[i] = dp[i - 1] + a[i];
    for (ll i = c; i <= n; ++i) {
        dp[i] = min(dp[i - c] + s[i] - s[i - c] - minn[i], dp[i - 1] + a[i]);
    }
    printf("%I64d", dp[n]);
    return 0;
}
```

---

## 可视化算法演示设计

### 动画效果设计
1. **滑动窗口最小值**：
   - **颜色标记**：当前窗口（红色边框），队列头部元素（绿色填充）。
   - **操作步骤**：
     - 新元素入队时，弹出队尾比它大的元素（黄色闪烁）。
     - 窗口滑动时，移除超出范围的队头元素（灰色渐变消失）。

2. **动态规划转移**：
   - **步进显示**：每一步显示 $f[i]$ 的两种转移来源（从 $f[i-1]$ 或 $f[i-c]$）。
   - **高亮比较**：选中更优的转移路径时，路径线条变为绿色并放大。

3. **复古像素风格**：
   - **Canvas 绘制**：数组元素显示为像素方块，数值用 8 位字体。
   - **音效**：队列操作时播放“哔”声，DP转移成功时播放“叮”声。

### 交互控制
- **速度调节**：滑块控制动画速度（1x~5x）。
- **单步执行**：按钮控制单步执行算法关键步骤。
- **自动演示**：AI模式自动运行，展示最优分段过程。

---

## 同类型题目推荐
1. **P1886 滑动窗口**（单调队列模板）
2. **P1044 栈**（动态规划结合计数）
3. **P1091 合唱队形**（双向动态规划）

---

## 个人心得摘录
- **Alarm5854**：  
  > 单调队列的维护需要严格保持单调性，队尾弹出时必须彻底，否则会影响后续的最小值计算。

- **Mickey_snow**：  
  > 线段树虽然代码较长，但在处理复杂区间查询时更灵活，适合不熟悉单调队列的学习者。

---

## 算法演示截图（示意图）
![滑动窗口与动态规划](https://i.imgur.com/5X9GZ8L.gif)  
（示意图：红色窗口滑动，绿色最小值标记，动态规划路径高亮）

---
处理用时：94.54秒