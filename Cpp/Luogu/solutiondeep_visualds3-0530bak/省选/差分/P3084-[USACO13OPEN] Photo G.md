# 题目信息

# [USACO13OPEN] Photo G

## 题目描述

Farmer John has decided to assemble a panoramic photo of a lineup of his N cows (1 <= N <= 200,000), which, as always, are conveniently numbered from 1..N.  Accordingly, he snapped M (1 <= M <= 100,000) photos, each covering a contiguous range of cows: photo i contains cows a\_i through b\_i inclusive.  The photos collectively may not necessarily cover every single cow.

After taking his photos, FJ notices a very interesting phenomenon: each photo he took contains exactly one cow with spots!  FJ was aware that he had some number of spotted cows in his herd, but he had never actually counted them.  Based on his photos, please determine the maximum possible number of spotted cows that could exist in his herd.  Output -1 if there is no possible assignment of spots to cows consistent with FJ's photographic results.

农夫约翰决定给站在一条线上的N(1 <= N <= 200,000)头奶牛制作一张全家福照片，N头奶牛编号1到N。


于是约翰拍摄了M(1 <= M <= 100,000)张照片，每张照片都覆盖了连续一段奶牛：第i张照片中包含了编号a\_i 到 b\_i的奶牛。但是这些照片不一定把每一只奶牛都拍了进去。


在拍完照片后，约翰发现了一个有趣的事情：每张照片中都**有且仅有**一只身上带有斑点的奶牛。约翰意识到他的牛群中有一些斑点奶牛，但他从来没有统计过它们的数量。 根据照片，请你帮约翰估算在他的牛群中最多可能有多少只斑点奶牛。如果无解，输出“-1”。


Input

## 说明/提示

There are 5 cows and 3 photos.  The first photo contains cows 1 through 4, etc.


From the last photo, we know that either cow 3 or cow 4 must be spotted. By choosing either of these, we satisfy the first two photos as well.


## 样例 #1

### 输入

```
5 3 
1 4 
2 5 
3 4 
```

### 输出

```
1 
```

# AI分析结果



## 唯一算法分类
**动态规划/单调队列优化**

---

## 题解思路与解决难点
### 核心思路
1. **状态定义**：设 `f[i]` 表示在位置 `i` 必须放置斑点牛时，前 `i` 个位置的最大斑点牛数量。
2. **转移范围约束**：
   - **上限**：`minl[i]` 表示所有包含 `i` 的区间中最小的左端点，即 `j` 的上界为 `minl[i]-1`（确保不与其他区间冲突）。
   - **下限**：`maxl[i]` 表示所有右端点小于 `i` 的区间中最大的左端点，即 `j` 的下界为 `maxl[i]`（确保覆盖所有前置区间）。
3. **单调队列优化**：在满足 `maxl[i] ≤ j < minl[i]` 的范围内，用单调队列维护 `f[j]` 的最大值，实现 O(1) 转移。

### 解决难点
1. **预处理数组**：
   - `minl[i]` 需从右向左扫描，取右端点等于 `i` 的区间的最小左端点。
   - `maxl[i]` 需从左向右扫描，取右端点小于 `i` 的区间的最大左端点。
2. **边界处理**：虚拟节点 `N+1` 用于统一处理无解情况。
3. **单调队列维护**：队列中存储下标 `j`，保持 `f[j]` 单调递减，动态移除越界元素。

---

## 题解评分（≥4星）
### 1. x义x（5星）
- **亮点**：预处理逻辑清晰，代码注释详细，虚拟节点设计巧妙。
- **核心代码**：
  ```cpp
  for (int i = N; i >= 1; i--)
      minl[i] = min(minl[i], minl[i+1]);
  for (int i = 1; i <= N+1; i++)
      maxl[i] = max(maxl[i], maxl[i-1]);
  ```

### 2. bztMinamoto（5星）
- **亮点**：代码简洁高效，双指针优化队列维护。
- **关键片段**：
  ```cpp
  while (j <= r[i] && j <= n) {
      if (f[j] != -1) {
          while (h <= t && f[j] > f[q[t]]) t--;
          q[++t] = j;
      }
      j++;
  }
  ```

### 3. ccsc（4星）
- **亮点**：代码可读性强，注释详细，适合新手学习。
- **代码片段**：
  ```cpp
  for (int i = 1; i <= n + 1; i++) {
      while (j < minl[i]) {
          if (f[j] != -1) add_to_queue(j);
          j++;
      }
      update_max_from_queue();
  }
  ```

---

## 最优思路与技巧提炼
### 关键步骤
1. **预处理 `minl` 和 `maxl`**：
   - `minl[i] = min(覆盖i的区间左端点)`，从右往左递推。
   - `maxl[i] = max(右端点<i的区间左端点)`，从左往右递推。
2. **单调队列维护窗口最大值**：
   - 队列中按 `f[j]` 递减存储，队头即当前窗口最大值。
   - 动态移除越界元素（`j < maxl[i]` 或 `j ≥ minl[i]`）。

### 代码核心实现
```cpp
// 预处理 minl 和 maxl
for (int i = n; i >= 1; i--) minl[i] = min(minl[i], minl[i+1]);
for (int i = 1; i <= n+1; i++) maxl[i] = max(maxl[i], maxl[i-1]);

// 单调队列转移
int j = 1, h = 1, t = 0;
for (int i = 1; i <= n+1; i++) {
    while (j < minl[i]) {
        if (f[j] != -1) {
            while (h <= t && f[j] >= f[q[t]]) t--;
            q[++t] = j;
        }
        j++;
    }
    while (h <= t && q[h] < maxl[i]) h++;
    f[i] = (h <= t) ? f[q[h]] + (i <= n) : -1;
}
```

---

## 同类题目推荐
1. **P1886 滑动窗口**：单调队列基础题，练习窗口最值维护。
2. **P3957 跳房子**：动态规划结合单调队列优化。
3. **P2569 股票交易**：区间限制下的动态规划优化。

---

## 可视化设计
### 动画方案
1. **网格绘制**：用 Canvas 绘制奶牛序列，斑点牛高亮为黄色。
2. **区间标记**：照片区间用红色框表示，动态展示约束范围。
3. **单调队列动态**：
   - **队列变化**：新元素入队时用绿色闪烁，旧元素出队用红色渐隐。
   - **当前窗口**：用半透明蓝色覆盖 `[maxl[i], minl[i])` 区间。
4. **音效设计**：
   - **入队/出队**：8-bit 电子音效（入队高音，出队低音）。
   - **无解提示**：播放短促“错误”音效。

### 复古像素风格
- **调色板**：16 色 FC 风格，背景深蓝，文本白色。
- **算法自动演示**：点击“Auto Run”后，自动步进并展示队列更新过程。
- **积分系统**：每正确转移一次获得 10 分，无解时扣 50 分。

---

## 个人心得摘录
> **x义x**：预处理顺序极易出错，需反复验证 `minl` 和 `maxl` 的递推方向。  
> **bztMinamoto**：虚拟节点 `N+1` 巧妙统一了边界判断，避免特例分支。  
> **Froggy**：差分约束需 SLF 优化 + 入队次数统计，否则难以通过极限数据。

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int N, M, minl[MAXN], maxl[MAXN], f[MAXN], q[MAXN];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N+1; i++) minl[i] = i;
    while (M--) {
        int l, r; scanf("%d%d", &l, &r);
        minl[r] = min(minl[r], l);
        maxl[r+1] = max(maxl[r+1], l);
    }
    for (int i = N; i >= 1; i--) minl[i] = min(minl[i], minl[i+1]);
    for (int i = 1; i <= N+1; i++) maxl[i] = max(maxl[i], maxl[i-1]);
    
    int h = 1, t = 0, j = 1; q[++t] = 0;
    for (int i = 1; i <= N+1; i++) {
        for (; j < minl[i]; j++) {
            if (f[j] == -1) continue;
            while (h <= t && f[j] >= f[q[t]]) t--;
            q[++t] = j;
        }
        while (h <= t && q[h] < maxl[i]) h++;
        f[i] = (h <= t) ? f[q[h]] + (i <= N) : -1;
    }
    printf("%d\n", f[N+1]);
    return 0;
}
```

---
处理用时：86.67秒