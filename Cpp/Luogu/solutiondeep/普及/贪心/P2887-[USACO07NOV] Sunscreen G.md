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

该题目是一个典型的贪心算法问题，核心在于如何通过合理的排序和选择策略，最大化满足奶牛的需求。大多数题解都采用了贪心算法，但排序策略和实现细节有所不同。常见的思路包括：

1. **按右端点排序**：将奶牛的区间按右端点排序，防晒霜按SPF值排序，优先选择SPF值最小的防晒霜来满足奶牛的需求。这种策略可以确保尽可能多的奶牛被覆盖。
2. **按左端点排序**：将奶牛的区间按左端点排序，防晒霜按SPF值排序，优先选择SPF值最大的防晒霜来满足奶牛的需求。这种策略可以确保防晒霜的使用效率最大化。
3. **优先队列优化**：通过优先队列动态维护可用的防晒霜，进一步优化贪心算法的效率。

### 所选高星题解

#### 1. 作者：翼德天尊 (5星)
**关键亮点**：
- 详细解释了贪心策略的正确性，并通过反例证明了按右端点排序的优势。
- 代码简洁清晰，逻辑严谨，适合初学者理解。

**核心代码**：
```cpp
sort(cow+1,cow+c+1,cmp); // 奶牛按右端点排序
sort(fss+1,fss+l+1,cmp1); // 防晒霜按SPF值排序
for (int i=1;i<=c;i++){
    for (int j=1;j<=l;j++){
        if (fss[j].b>0&&fss[j].a>=cow[i].a&&fss[j].a<=cow[i].b){
            fss[j].b--,ans++; // 使用防晒霜
            break;
        }
    }
}
```
**个人心得**：
- 通过反例证明了按右端点排序的正确性，帮助读者更好地理解贪心策略。

#### 2. 作者：Lily_White (4星)
**关键亮点**：
- 详细阐述了贪心策略的证明过程，帮助读者理解为什么选择最大SPF值的防晒霜是最优的。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
sort(a+1,a+1+c,cmp); // 奶牛按minSPF递减排序
sort(b+1,b+1+l,cmp_s); // 防晒霜按SPF值递减排序
for(int i=1;i<=c;i++){
    for(int j=1;j<=l;j++){
        if(b[j].a>=a[i].a&&b[j].a<=a[i].b&&b[j].b){
            ans++; b[j].b--; // 使用防晒霜
            break;
        }
    }
}
```
**个人心得**：
- 通过分类讨论，详细解释了贪心策略的正确性，帮助读者深入理解问题。

#### 3. 作者：maike8shi (4星)
**关键亮点**：
- 使用了优先队列优化贪心算法，进一步提高了算法的效率。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
sort(a+1,a+1+n,cmp); // 奶牛按maxSPF排序
for(int i=maxl;i>=minr;i--){
    while (a[p].mx==i){
        q.push(a[p]); // 将符合条件的奶牛加入优先队列
        p++;
    }
    while (!q.empty()&&q.top().mn>i) q.pop(); // 移除不符合条件的奶牛
    while (res[i]&&!q.empty()){
        ans++; q.pop(); // 使用防晒霜
        res[i]--;
    }
}
```
**个人心得**：
- 通过优先队列优化了贪心算法的实现，提高了代码的效率。

### 最优关键思路总结

1. **排序策略**：无论是按左端点还是右端点排序，核心思想都是通过合理的排序策略，确保贪心算法的正确性和效率。
2. **贪心选择**：优先选择SPF值最小或最大的防晒霜，确保尽可能多的奶牛被覆盖或防晒霜的使用效率最大化。
3. **优先队列优化**：通过优先队列动态维护可用的防晒霜，进一步优化贪心算法的效率。

### 拓展思路与类似题目

1. **类似题目**：
   - [P2883 [USACO07NOV] Sunscreen G](https://www.luogu.com.cn/problem/P2883)
   - [P1231 教辅的组成](https://www.luogu.com.cn/problem/P1231)
   - [P2512 [HAOI2008] 糖果传递](https://www.luogu.com.cn/problem/P2512)

2. **拓展思路**：
   - 可以尝试将贪心算法与其他算法（如动态规划、网络流）结合，解决更复杂的问题。
   - 在类似问题中，可以考虑使用优先队列、堆等数据结构来优化贪心算法的实现。

### 个人心得总结

- **调试经历**：通过反例和分类讨论，帮助理解贪心策略的正确性。
- **踩坑教训**：排序策略的选择对算法的正确性和效率有重要影响，需谨慎选择。
- **顿悟感想**：贪心算法的核心在于局部最优解的选择，通过合理的排序和选择策略，可以确保全局最优解。

---
处理用时：46.33秒