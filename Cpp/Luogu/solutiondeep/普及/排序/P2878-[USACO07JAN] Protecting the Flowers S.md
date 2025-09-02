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
这些题解均围绕贪心算法解决“保护花朵”问题。核心思路是通过比较不同牛的运输顺序对总损失的影响，确定排序规则，再计算最小损失。
- **思路**：多数题解通过比较两头牛不同运输顺序下的损失，得出排序关键指标，如`t * d`或`t / d`的大小关系。
- **算法要点**：定义结构体存储牛的信息，自定义比较函数进行排序，部分使用前缀和简化计算。
- **解决难点**：确定合理的贪心策略，即如何比较不同牛的运输顺序；处理大数据时使用`long long`避免溢出。

### 所选题解
1. **曦行夜落（5星）**
    - **关键亮点**：详细介绍贪心算法概念及常见类型，结合本题深入讲解贪心策略推导过程，代码规范，注释清晰。
    - **核心代码**：
```cpp
struct cows {
    long long d, t;
};
int cmp(cows x, cows y) {
    return x.t * y.d < x.d * y.t;
}
//...
sort(a + 1, a + 1 + n, cmp);
for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i].d;
long long ans = 0;
for (int i = 1; i <= n; ++i)
    ans += 2 * a[i].t * (sum[n] - sum[i]);
```
2. **lzqy_（4星）**
    - **关键亮点**：清晰阐述贪心思路和前缀和计算方法，对代码细节和坑点有明确提示。
    - **核心代码**：
```cpp
struct p {
    int D, T;
};
bool cmp(p a, p b) {
    return (double)a.D / a.T * 1.0 > (double)b.D / b.T * 1.0;
}
//...
sort(a, a + n, cmp);
p[0] = a[0].D;
for (int i = 1; i < n; i++)
    p[i] = p[i - 1] + a[i].D;
for (int i = 0; i < n; i++)
    ans += (p[n - 1] - p[i]) * a[i].T * 2;
```
3. **孑彧（4星）**
    - **关键亮点**：思路清晰，推导过程简洁明了，代码实现规范。
    - **核心代码**：
```cpp
struct Node {
    LL t, d;
    double v;
    bool operator < (Node a) const {
        return v < a.v;
    } 
};
//...
sort(a + 1, a + 1 + n);
for (int i = 1; i <= n; i++) {
    sum -= a[i].d;
    ans += 2 * a[i].t * sum;
}
```

### 最优关键思路或技巧
- **贪心策略推导**：通过比较相邻两头牛不同运输顺序下的损失，得出排序关键指标，推广到全局确定最优顺序。
- **前缀和优化**：使用前缀和数组记录剩余牛每分钟吃花总数，简化计算。

### 可拓展之处
同类型题多为贪心问题，通过比较相邻元素不同排列顺序的影响确定贪心策略，如区间调度问题、任务分配问题等。

### 洛谷相似题目推荐
- P1090 [NOIP2004 提高组] 合并果子
- P1803 凌乱的yyy / 线段覆盖
- P1208 [USACO1.3] 混合牛奶 Mixing Milk

### 个人心得摘录与总结
- **lzqy_**：提到“一个坑点，在$Ti*2$的时间里，第$i$头牛一直都不能吃花（这个坑了我好久）”，总结为在解题时要仔细理解题意，注意特殊条件，避免因细节失误导致错误。
- **冰桨**：“由于long long导致第一遍70”，提醒我们处理大数据时要注意数据类型，避免溢出问题。 

---
处理用时：30.40秒