# 题目信息

# [USACO07NOV] Sunscreen G

## 题目描述

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

有C个奶牛去晒太阳 (1 <=C <= 2500)，每个奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。

而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。

那么为了不让奶牛烫伤，又不会没有效果。

给出了L种防晒霜。每种的数量和固定的阳光强度也给出来了

每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。


## 样例 #1

### 输入

```
3 2
3 10
2 5
1 5
6 2
4 1```

### 输出

```
2```

# AI分析结果



### 综合分析与结论
本题本质是区间覆盖问题，核心在于通过贪心策略最大化匹配数。各题解主要围绕以下思路展开：
1. **右端点优先策略**：将奶牛按右端点排序，防晒霜按SPF排序，优先匹配右端点小的区间（避免大区间占用高SPF）
2. **双降序策略**：将奶牛按minSPF降序排序，防晒霜按SPF降序排序，优先使用最大可用SPF
3. **网络流/优先队列**：存在理论解但效率较低，不适用于本题数据范围

最优策略为前两种贪心方法，时间复杂度均为O(CL)，在题目约束下均能AC。网络流解法虽正确但时空复杂度高，不推荐。

---

### 高分题解推荐

#### 1. 翼德天尊（★★★★☆）
**关键亮点**：
- 清晰的右端点排序策略与反例证明
- 简洁的代码实现（双重循环+提前break）
- 时间复杂度O(CL)完全可接受

**核心思路**：
```cpp
sort(cow+1,cow+c+1,cmp); // 按右端点排序
sort(fss+1,fss+l+1,cmp1); // 按SPF升序
for(奶牛遍历)
  for(防晒霜遍历)
    if(SPF在区间内) 匹配并退出
```

#### 2. 陷语（★★★★☆）
**关键亮点**：
- 严谨的贪心策略数学证明
- 双降序排序保证局部最优性
- 代码可读性高，逻辑清晰

**核心思路**：
```cpp
sort(a+1, a+1+c, cmp); // 奶牛按minSPF降序 
sort(b+1, b+1+l, cmp_s); // 防晒霜按SPF降序
for(奶牛遍历)
  for(防晒霜遍历)
    if(SPF在区间内) 选择最大可用SPF
```

#### 3. 小黑AWM（★★★☆☆）
**亮点**：
- 使用set维护可用防晒霜
- 通过lower_bound快速查找最优解
- 时间复杂度优化至O(ClogL)

**核心技巧**：
```cpp
set<int> spf; // 存储可用SPF值
for(防晒霜排序后处理)
  auto p = spf.lower_bound(maxSPF);
  while调整找到合法SPF
```

---

### 关键思路总结
1. **排序策略决定正确性**：
   - 右端点排序确保小范围优先使用低SPF
   - 双降序排序确保高需求区间优先使用高SPF
2. **贪心选择原则**：
   - 每个决策应为后续步骤保留最大可能性
   - 匹配时需严格证明无后效性
3. **实现优化技巧**：
   - 排序后使用双重循环暴力匹配即可AC
   - 优先队列/二分查找可优化常数

---

### 易错点与心得
1. **排序方向混淆**（追梦_Chen）：
   - 初始按左端点排序仅得38分，调整为右端点后AC
   - *教训：必须严格证明排序策略的正确性*
2. **循环变量误用**（shuiyuhan）：
   - 内层循环误写为`for(int j=1;j<=sun[i].total;i++)`导致死循环
   - *调试经验：警惕循环变量名相似导致的错误*
3. **边界条件处理**（AndyMo）：
   - 需先弹出maxSPF<当前SPF的无效奶牛
   - *技巧：使用优先队列时需动态维护合法区间*

---

### 拓展练习推荐
1. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)  
   （双关键字排序+贪心）
2. [P1209 [USACO1.3]修理牛棚](https://www.luogu.com.cn/problem/P1209)  
   （区间覆盖与缺口选择）
3. [P2883 [USACO07MAR]Face The Right Way](https://www.luogu.com.cn/problem/P2883)  
   （贪心策略与差分优化）

---
处理用时：62.29秒