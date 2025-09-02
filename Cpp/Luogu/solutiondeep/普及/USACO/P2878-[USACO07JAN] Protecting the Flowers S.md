# 题目信息

# [USACO07JAN] Protecting the Flowers S

## 题目描述

Farmer John went to cut some wood and left N (2 ≤ N ≤ 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 ≤ Ti ≤ 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 ≤ Di ≤ 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 × Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

有 $n$ 头奶牛跑到 FJ 的花园里去吃花儿了，它们分别在距离牛圈 $T_i$（这里指 FJ 到那里需要 $T_i$ 分钟) 处吃花，每分钟会吃掉 $D_i$ 朵花，FJ 现在要将它们给弄回牛圈，但是他每次只能弄一头回去，来回用时总共为 $2 \times T_i$ 分钟，在这段时间内，其它的奶牛会继续吃 FJ 的花，速度保持不变，当然正在被赶回牛圈的奶牛不能继续吃了。现在求在最好的方案下奶牛吃掉花的最小朵数。


## 说明/提示

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.


## 样例 #1

### 输入

```
6
3 1
2 5
2 3
3 2
4 1
1 6```

### 输出

```
86```

# AI分析结果



### 综合分析与结论
本题需通过贪心策略确定最优的赶牛顺序，使得总损失最小。各题解核心思路一致：通过比较两头牛的运输时间与破坏力的比值，按该比值升序排列。关键点在于推导出正确的排序条件（比较 `t_i/d_i` 或交叉相乘比较 `t_i*d_j < t_j*d_i`），并用前缀和优化计算总损失。所有正确题解均采用此方法，差异仅在于实现细节。

### 精选题解及评分
#### 1. 曦行夜落（5星）
- **关键亮点**：详细推导贪心策略，正确使用交叉相乘避免浮点误差，代码简洁高效，附带同类问题扩展。
- **核心代码**：
  ```cpp
  bool cmp(cows x, cows y) {
      return x.t * y.d < x.d * y.t;
  }
  // 前缀和计算总损失
  for (int i = 1; i <= n; i++)
      ans += 2 * a[i].t * (sum[n] - sum[i]);
  ```

#### 2. lzqy_（4星）
- **关键亮点**：强调前缀和实现，明确数据类型转换的注意事项，指出「运输时当前牛不再吃花」的易错点。
- **核心代码**：
  ```cpp
  bool cmp(p a, p b) {
      return (double)a.D / a.T > (double)b.D / b.T;
  }
  // 前缀和数组计算剩余破坏力
  ans += (p[n-1] - p[i]) * a[i].T * 2;
  ```

#### 3. 冰桨（4星）
- **关键亮点**：代码简洁，正确维护剩余破坏力总和，避免溢出。
- **核心代码**：
  ```cpp
  struct node { long long t, d; double dis; };
  // 按 t/d 升序排序
  sort(e+1, e+n+1);
  ans += sum * e[i].t * 2; // sum 为剩余总破坏力
  ```

### 关键思路与技巧
1. **贪心策略推导**：比较相邻两头牛交换顺序后的损失差异，推导出排序条件 `t_i/d_i` 升序或等价形式。
2. **前缀和优化**：预处理破坏力总和，快速计算剩余牛的破坏力。
3. **避免浮点误差**：用交叉相乘（`t_i*d_j < t_j*d_i`）替代除法比较。
4. **数据类型**：使用 `long long` 防止大数溢出。

### 同类题目推荐
1. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)（贪心+截止时间排序）
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列贪心）
3. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)（区间处理贪心）

### 个人心得摘录
- **调试教训**：多篇题解强调需注意「运输时间包含往返」（乘2），并确保计算剩余破坏力时排除当前牛。
- **优化技巧**：交叉相乘代替浮点除法，既避免精度问题又提升效率（曦行夜落）。
- **常见错误**：错误累加已运送牛的破坏力（Dawn_Sdy 题解中错误使用 `time` 变量）。

---
处理用时：143.22秒