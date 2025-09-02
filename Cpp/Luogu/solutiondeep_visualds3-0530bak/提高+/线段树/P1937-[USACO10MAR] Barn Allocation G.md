# 题目信息

# [USACO10MAR] Barn Allocation G

## 题目描述

Farmer John recently opened up a new barn and is now accepting stall allocation requests from the cows since some of the stalls have a better view of the pastures.

The barn comprises N (1 <= N <= 100,000) stalls conveniently numbered 1..N; stall i has capacity C\_i cows (1 <= C\_i <= 100,000). Cow i may request a contiguous interval of stalls (A\_i, B\_i) in which to roam (1 <= A\_i <= N; A\_i <= B\_i <= N), i.e., the cow would like to wander among all the stalls in the range A\_i..B\_i (and the stalls must always have the capacity for her to wander).

Given M (1 <= M <= 100,000) stall requests, determine the maximum number of them that can be satisfied without exceeding stall

capacities.

 
农夫约翰最近开了一个新的牲口棚屋，并且现在接受来自奶牛的分配畜栏请求因为其中的一些畜栏有更好风景。

畜栏包括N个畜栏(1 ≤ N ≤ 100,000)，方便起见，我们把它们编号为1..N，畜栏i能容纳Ci只牛(1 ≤ Ci ≤ 100,000)，第i只牛需要连续编号畜栏（从Ai到Bi）来漫步其中，

(1 ≤ Ai ≤ N; Ai ≤ Bi ≤ N)，换言之，这只牛想要在编号范围为Ai..Bi的畜栏漫步（所有它想要畜栏必须实施为它空出位置来供它散步）

给出M个畜栏分配请求（1 ≤ M ≤ 100,000），回答最多能满足多少只牛的要求（不增加另外畜栏）

考虑以下例子：

```cpp
畜栏号:    1   2   3   4   5
           +---+---+---+---+---+
容纳空间:  | 1 | 3 | 2 | 1 | 3 |  
           +---+---+---+---+---+
Cow 1       XXXXXXXXXXX             (1, 3)
Cow 2           XXXXXXXXXXXXXXX     (2, 5)
Cow 3           XXXXXXX             (2, 3)
Cow 4                   XXXXXXX     (4, 5)
```
约翰显然不能满足所有的牛，因为畜栏3，4请求太多了

经过试验，我们发现，我们能满足牛1，3，4需要，所以这组数据答案为3


## 说明/提示

Source: USACO 2010 March Gold

Translator: @chrome01


## 样例 #1

### 输入

```
5 4
1
3
2
1
3
1 3
2 5
2 3
4 5```

### 输出

```
3```

# AI分析结果



## 算法分类
**贪心算法 + 数据结构优化**

---

## 综合分析与结论

### 核心思路与难点
- **核心思路**：通过贪心策略优先选择右端点小且左端点大的区间，尽可能减少对后续请求的影响。用数据结构（线段树或优先队列）动态维护剩余容量。
- **难点**：
  1. **贪心正确性证明**：需证明按右端点排序的最优性，以及处理冲突时的策略（如优先队列中选择保留右端点小的请求）。
  2. **高效维护剩余容量**：通过线段树的区间操作或优先队列的动态调整实现。

### 可视化设计思路
- **动画方案**：
  - **线段树方法**：用颜色渐变表示畜栏剩余容量，每次处理请求时高亮对应的区间并显示线段树节点的更新过程。若区间最小值≥1，播放成功音效并减1；否则播放失败音效。
  - **优先队列方法**：显示当前扫描的畜栏位置，将新请求加入队列，队列溢出时弹出最大右端点的请求，用像素块表示队列中牛的分布。
- **复古风格**：
  - **8位像素UI**：畜栏用网格表示，容量用颜色深度（深色=满载，浅色=空闲）。
  - **音效设计**：区间减1时播放“哔”声，成功/失败时分别播放不同音调。
  - **AI演示**：自动按排序后的请求依次处理，用户可暂停观察线段树状态或队列变化。

---

## 题解评分（≥4星）

1. **Fading（5星）**  
   - 思路清晰，详细证明贪心正确性，代码使用线段树维护区间最小值，时间复杂度优秀。

2. **__JR_飘摇__（5星）**  
   - 优先队列实现巧妙，代码简洁高效，通过动态调整队列保证右端点小的请求优先保留。

3. **Sincerin（4星）**  
   - 详细解释贪心策略与线段树实现，附参考题目和调试建议，代码可读性强。

---

## 最优思路与技巧

### 线段树方法
- **关键代码**：
  ```cpp
  // 线段树区间查询与修改
  if (query(1, e[i].l, e[i].r) >= 1) {
      change(1, e[i].l, e[i].r);
      ans++;
  }
  ```
- **技巧**：按右端点排序后，每次只需检查区间最小值，确保剩余容量充足。

### 优先队列方法
- **关键代码**：
  ```cpp
  while (q.size() > s[i] + ans) {
      sum[q.top()]--;
      q.pop();
  }
  ```
- **技巧**：按左端点排序，扫描时动态维护优先队列，超出容量时移除右端点最大的请求。

---

## 相似题目推荐
1. **P1803 凌乱的yyy / 线段覆盖**  
   （经典贪心，按右端点排序选择不重叠区间）
2. **P2285 [HNOI2004]打鼹鼠**  
   （动态规划结合区间选择）
3. **P3373 线段树2**  
   （线段树区间操作练习，含延迟标记）

---

## 个人心得摘录
- **线段树调试**：注意延迟标记的下传时机，避免因未及时更新导致查询错误。
- **优先队列优化**：`sum`数组记录右端点出现次数，巧妙避免重复计算已释放的请求。

---

## 代码实现示例（线段树核心）

```cpp
struct SegmentTree {
    int dat, add;
} t[N << 2];

void pushdown(int p) {
    if (t[p].add) {
        t[p<<1].dat += t[p].add; t[p<<1|1].dat += t[p].add;
        t[p<<1].add += t[p].add; t[p<<1|1].add += t[p].add;
        t[p].add = 0;
    }
}

int query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return t[p].dat;
    pushdown(p);
    int mid = (l + r) >> 1, res = INF;
    if (ql <= mid) res = min(res, query(p<<1, l, mid, ql, qr));
    if (qr > mid) res = min(res, query(p<<1|1, mid+1, r, ql, qr));
    return res;
}

void update(int p, int l, int r, int ul, int ur) {
    if (ul <= l && r <= ur) {
        t[p].dat--; t[p].add--;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ul <= mid) update(p<<1, l, mid, ul, ur);
    if (ur > mid) update(p<<1|1, mid+1, r, ul, ur);
    t[p].dat = min(t[p<<1].dat, t[p<<1|1].dat);
}
```

---

## 可视化与游戏化设计
- **Canvas绘制**：每个畜栏为像素块，颜色由剩余容量决定。处理请求时，区间内像素短暂闪烁红色（成功）或灰色（失败）。
- **音效触发**：使用 `Web Audio API`，区间减1时触发 `beep(440Hz, 50ms)`，成功时 `beep(880Hz, 100ms)`。
- **自动演示**：按排序后的请求顺序逐步执行，用户可通过滑块调整速度（100ms~2s/步）。

---
处理用时：84.13秒