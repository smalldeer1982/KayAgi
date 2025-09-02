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

本题的核心是贪心算法，通过对奶牛和防晒霜进行排序，确保每次选择最优的匹配方案。大多数题解采用了类似的思路：将奶牛按右端点排序，防晒霜按SPF值排序，然后依次匹配。部分题解还提供了贪心策略的证明，增强了算法的正确性。

### 所选高星题解

#### 1. **翼德天尊 (5星)**
- **关键亮点**：思路清晰，详细解释了贪心策略的正确性，并提供了反例证明。代码简洁，结构合理。
- **个人心得**：通过反例证明了按右端点排序的正确性，帮助读者更好地理解贪心策略。
- **核心代码**：
  ```cpp
  sort(cow+1,cow+c+1,cmp); // 奶牛按右端点排序
  sort(fss+1,fss+l+1,cmp1); // 防晒霜按SPF值排序
  for (int i=1;i<=c;i++){
      for (int j=1;j<=l;j++){
          if (fss[j].b>0&&fss[j].a>=cow[i].a&&fss[j].a<=cow[i].b){
              fss[j].b--,ans++; // 匹配成功，防晒霜数量减一，答案加一
              break;
          }
      }
  }
  ```

#### 2. **陷语 (4星)**
- **关键亮点**：提供了贪心策略的详细证明，解释了为什么按最小阳光需求度从大到小排序是最优的。
- **核心代码**：
  ```cpp
  sort(a + 1, a + 1 + c, cmp); // 奶牛按最小阳光需求度排序
  sort(b + 1, b + 1 + l, cmp_s); // 防晒霜按SPF值排序
  for(int i = 1; i <= c; ++i)
      for(int j = 1; j <= l; ++j) {
          if(b[j].a >= a[i].a && b[j].a <= a[i].b && b[j].b) {
              ans++;
              b[j].b--;
              break;
          }
      }
  ```

#### 3. **Werner_Yin (4星)**
- **关键亮点**：通过图例解释了贪心策略的正确性，代码实现清晰，适合初学者理解。
- **核心代码**：
  ```cpp
  sort(a + 1, a + 1 + c, cmp); // 奶牛按最小阳光需求度排序
  sort(b + 1, b + 1 + l, cmp_s); // 防晒霜按SPF值排序
  for(int i = 1; i <= c; ++i)
      for(int j = 1; j <= l; ++j) {
          if(b[j].a >= a[i].a && b[j].a <= a[i].b && b[j].b) {
              ans++;
              b[j].b--;
              break;
          }
      }
  ```

### 最优关键思路与技巧
1. **贪心策略**：将奶牛按右端点排序，防晒霜按SPF值排序，确保每次选择最优的匹配方案。
2. **反例证明**：通过反例证明按右端点排序的正确性，帮助理解贪心策略。
3. **代码优化**：使用双重循环进行匹配，确保时间复杂度在可接受范围内。

### 可拓展之处
- **类似题目**：可以拓展到其他区间覆盖问题，如线段覆盖、任务调度等。
- **算法套路**：贪心算法在区间问题中的应用，如按端点排序、优先选择最优解等。

### 推荐题目
1. **P2883 [USACO07NOV] Sunscreen G** - 本题的变种，考察贪心策略。
2. **P1233 木棍加工** - 区间覆盖问题，考察贪心与排序。
3. **P1090 合并果子** - 贪心算法的经典应用，考察优先队列的使用。

### 个人心得总结
- **调试经历**：部分题解提到在调试过程中遇到的坑，如防晒霜数量为0时的处理，提醒读者注意边界条件。
- **顿悟感想**：通过反例证明贪心策略的正确性，帮助读者更好地理解算法的本质。

---
处理用时：32.63秒