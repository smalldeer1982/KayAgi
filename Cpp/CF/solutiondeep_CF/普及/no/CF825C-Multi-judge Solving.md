# 题目信息

# Multi-judge Solving

## 题目描述

Makes solves problems on Decoforces and lots of other different online judges. Each problem is denoted by its difficulty — a positive integer number. Difficulties are measured the same across all the judges (the problem with difficulty $ d $ on Decoforces is as hard as the problem with difficulty $ d $ on any other judge).

Makes has chosen $ n $ problems to solve on Decoforces with difficulties $ a_{1},a_{2},...,a_{n} $ . He can solve these problems in arbitrary order. Though he can solve problem $ i $ with difficulty $ a_{i} $ only if he had already solved some problem with difficulty ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF825C/dcc3f539eeb6ae660df27e0ba4735db648eac084.png) (no matter on what online judge was it).

Before starting this chosen list of problems, Makes has already solved problems with maximum difficulty $ k $ .

With given conditions it's easy to see that Makes sometimes can't solve all the chosen problems, no matter what order he chooses. So he wants to solve some problems on other judges to finish solving problems from his list.

For every positive integer $ y $ there exist some problem with difficulty $ y $ on at least one judge besides Decoforces.

Makes can solve problems on any judge at any time, it isn't necessary to do problems from the chosen list one right after another.

Makes doesn't have too much free time, so he asked you to calculate the minimum number of problems he should solve on other judges in order to solve all the chosen problems from Decoforces.

## 说明/提示

In the first example Makes at first solves problems 1 and 2. Then in order to solve the problem with difficulty 9, he should solve problem with difficulty no less than 5. The only available are difficulties 5 and 6 on some other judge. Solving any of these will give Makes opportunity to solve problem 3.

In the second example he can solve every problem right from the start.

## 样例 #1

### 输入

```
3 3
2 1 9
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 20
10 3 6 3
```

### 输出

```
0
```

# AI分析结果



### 中文题目重写
# 多平台解题

## 题目描述

Makes在Decoforces和其他多个在线评测平台上解题。每个问题都有一个难度值（正整数）。所有平台的难度标准统一（Decoforces上难度为d的问题与其他平台难度为d的问题难度相同）。

Makes选择了n个Decoforces上的题目，难度分别为a₁,a₂,...,aₙ。他可以按任意顺序解题，但只有当已解决过难度≥d/2的问题时，才能解决难度为d的问题（无论该前置问题在哪个平台解决）。

初始时，Makes已解决过的最高难度问题为k。若无法按任何顺序解决全部选定题目，Makes需要在其他平台解题。每个其他平台都保证存在任意难度y的问题。

求Makes最少需要额外在其他平台解决多少问题才能完成所有Decoforces上的选定题目。

## 输入输出样例

### 样例1
输入：
3 3
2 1 9

输出：
1

### 样例2
输入：
4 20
10 3 6 3

输出：
0

---

### 算法分类
贪心

---

### 题解分析与结论

#### 核心思路
所有题解均采用**贪心策略**：
1. 将题目按难度升序排序
2. 按顺序处理题目，当当前能力k无法解题时（aᵢ > 2k），通过在其他平台解题提升能力
3. 每次解题后更新能力k为已解决题目的最大难度

#### 解决难点
- **排序必要性**：确保先解决简单题以最大化能力提升效果
- **动态更新策略**：每次解题后及时更新当前解题能力
- **效率证明**：通过数学归纳可证此策略的翻倍次数最少

#### 最优题解推荐

1. **dinghongsen（★★★★☆）**
   亮点：代码简洁，变量命名清晰，核心逻辑使用标准库函数实现排序
   ```cpp
   sort(a, a + n);
   for (int i = 0; i < n; i++) {
       while (2 * k < a[i]) {
           cnt++;
           k *= 2;
       }
       k = max(k, a[i]);
   }
   ```

2. **keep_shining（★★★★☆）**
   亮点：添加详细注释，使用更安全的循环结构
   ```cpp
   sort(a+1,a+1+n);
   for(int i=1;i<=n;i++){
       while(a[i]>2*k) k*=2,cnt++;
       k=max(k,a[i]);
   }
   ```

3. **Aw顿顿（★★★★☆）**
   亮点：采用快速读入优化，添加边界处理
   ```cpp
   sort(a+1,a+1+n);
   for(int i=1;i<=n;i++){
       while(a[i]>2*k)s++,k<<=1;
       k=mx(a[i],k);
   }
   ```

---

### 关键技巧总结
1. **排序预处理**：确保按难度递增顺序处理题目
2. **能力倍增策略**：当aᵢ > 2k时通过指数增长快速提升解题能力
3. **及时更新**：每次解题后立即更新当前最大解题能力

---

### 类似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 排序贪心优化等待时间
3. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 右端点排序的区间贪心

---

### 题解心得摘录
- **调试经验**：多位作者强调必须及时更新k为max(k,aᵢ)，否则会影响后续判断
- **顿悟时刻**：发现排序后的处理顺序能最大化利用已解决的题目提升能力
- **易错警示**：注意题目中2k的比较条件而非k的直接比较

---
处理用时：76.46秒