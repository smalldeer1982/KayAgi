# 题目信息

# Rescheduling the Exam

## 题目描述

Now Dmitry has a session, and he has to pass $ n $ exams. The session starts on day $ 1 $ and lasts $ d $ days. The $ i $ th exam will take place on the day of $ a_i $ ( $ 1 \le a_i \le d $ ), all $ a_i $ — are different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/80b5043cb96246fb12fe0316b7ae224994f04da5.png)Sample, where $ n=3 $ , $ d=12 $ , $ a=[3,5,9] $ . Orange — exam days. Before the first exam Dmitry will rest $ 2 $ days, before the second he will rest $ 1 $ day and before the third he will rest $ 3 $ days.For the session schedule, Dmitry considers a special value $ \mu $ — the smallest of the rest times before the exam for all exams. For example, for the image above, $ \mu=1 $ . In other words, for the schedule, he counts exactly $ n $ numbers — how many days he rests between the exam $ i-1 $ and $ i $ (for $ i=0 $ between the start of the session and the exam $ i $ ). Then it finds $ \mu $ — the minimum among these $ n $ numbers.

Dmitry believes that he can improve the schedule of the session. He may ask to change the date of one exam (change one arbitrary value of $ a_i $ ). Help him change the date so that all $ a_i $ remain different, and the value of $ \mu $ is as large as possible.

For example, for the schedule above, it is most advantageous for Dmitry to move the second exam to the very end of the session. The new schedule will take the form:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/ea72ffbaa1a469cfa577e07f4a541e64f273ed21.png)Now the rest periods before exams are equal to $ [2,2,5] $ . So, $ \mu=2 $ .Dmitry can leave the proposed schedule unchanged (if there is no way to move one exam so that it will lead to an improvement in the situation).

## 说明/提示

The first sample is parsed in statement.

One of the optimal schedule changes for the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/a8127e465b7998df08b0c9dd6be925e73333852b.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c109ce56a74359821f30b8b4de03ca418349d132.png)New schedule.

In the third sample, we need to move the exam from day $ 1 $ to any day from $ 4 $ to $ 100 $ .

In the fourth sample, any change in the schedule will only reduce $ \mu $ , so the schedule should be left as it is.

In the fifth sample, we need to move the exam from day $ 1 $ to any day from $ 100000000 $ to $ 300000000 $ .

One of the optimal schedule changes for the sixth sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c42982828b6b783bfe2b7287e37a4f2be5dfff0a.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/40bee0dd841380562f7e8f2d4a71c924f5f6fe41.png)New schedule.

In the seventh sample, every day is exam day, and it is impossible to rearrange the schedule.

## 样例 #1

### 输入

```
9

3 12
3 5 9

2 5
1 5

2 100
1 2

5 15
3 6 9 12 15

3 1000000000
1 400000000 500000000

2 10
3 4

2 2
1 2

4 15
6 11 12 13

2 20
17 20```

### 输出

```
2
1
1
2
99999999
3
0
1
9```

# AI分析结果



---

## 唯一算法分类  
**贪心**

---

## 综合分析与结论  

### 核心思路与难点  
- **核心思路**：所有题解均围绕「修改最小间隔附近的考试」展开。原问题的最小间隔限制了 μ 值的上限，必须通过调整该间隔或其相邻考试来提升 μ。  
- **关键难点**：  
  1. **确定调整对象**：必须找到当前所有间隔的最小值，并针对其相邻考试进行调整。  
  2. **最优插入位置**：调整后的考试可能插入到最大间隔的中段或最后一天，需计算两种情况的 μ 值并取最大。  
  3. **边界处理**：如原最小间隔在首尾时的特殊处理。  

### 算法流程与可视化设计  
1. **原数组排序**：所有考试日期按升序排列。  
2. **找到最小间隔**：遍历相邻考试间隔，记录最小间隔的位置。  
3. **模拟调整**：分别尝试删除最小间隔的左侧或右侧考试，计算插入后的 μ：  
   - **插入到最大间隔中点**：将当前最大间隔拆分为两个相等或接近的间隔。  
   - **插入到最后一天**：计算最后一天与末尾考试的间隔。  
4. **颜色标记**：  
   - **红色**：原最小间隔及其相邻考试。  
   - **蓝色**：最大间隔的插入位置。  
   - **绿色**：调整后的新间隔。  
5. **动画步进**：逐帧展示调整过程，对比原布局与新布局的间隔变化。  

---

## 题解清单 (≥4星)  

### 1. DaiRuiChen007 (★★★★☆)  
**关键亮点**：  
- 直接定位最小间隔，仅需两次 `calc` 计算。  
- 代码简洁，逻辑清晰，时间复杂度 O(n)。  
**核心代码**：  
```cpp
inline int calc(int x) {
    int lst=0, min_gap=d, max_gap=0;
    for(int i=1;i<=n;++i) {
        if(i==x) continue;
        int gap=a[i]-a[lst]-1;
        min_gap=min(min_gap, gap);
        max_gap=max(max_gap, gap);
        lst=i;
    }
    return min(min_gap, max( (max_gap-1)/2, d-a[lst]-1 ));
}
```

### 2. Fislett (★★★★☆)  
**关键亮点**：  
- 函数 `f` 复用率高，代码高度精简。  
- 显式处理边界条件（`minx != 1`）。  
**核心代码**：  
```cpp
int work(int pos){
    int minx=2e9, maxx=0, last=0;
    for(int i=1;i<=n;i++){
        if(i==pos) continue;
        minx = min(a[i]-a[last]-1, minx);
        maxx = max(a[i]-a[last]-1, maxx);
        last=i;
    }
    return min(minx, max( (maxx-1)/2, d-a[last]-1 ));
}
```

### 3. XL4453 (★★★★☆)  
**关键亮点**：  
- 代码极简，完全省略辅助函数，直接内联计算逻辑。  
- 变量命名清晰，适合快速理解。  

---

## 最优思路或技巧提炼  

### 核心贪心策略  
1. **最小间隔优先**：任何 μ 的提升必须修改当前最小间隔或其相邻考试。  
2. **插入位置分析**：  
   - **最大间隔中点**：将原最大间隔拆分为两个更小区间，提升整体最小值。  
   - **最后一天插入**：直接扩展末尾间隔，可能成为新的 μ 值。  

### 实现技巧  
- **预处理排序**：确保考试日期有序，简化间隔计算。  
- **双指针遍历**：删除一个元素后，通过遍历剩余元素快速计算新间隔。  

---

## 同类型题或类似算法套路  
- **最大化最小值问题**：如会议安排、资源分配等场景。  
- **关键操作插入**：如动态调整队列中的元素以优化目标函数。  

---

## 推荐类似题目  
1. [P2899 - Cell Phone Network](https://www.luogu.com.cn/problem/P2899)  
2. [P2678 - 跳石头](https://www.luogu.com.cn/problem/P2678)  
3. [P2115 - 破坏](https://www.luogu.com.cn/problem/P2115)  

---

## 个人心得摘录  
**DaiRuiChen007 调试经验**：  
> "最初漏掉了 `pos>1` 的判断，导致首元素无法调整。通过极端样例（如第一个间隔为最小值）验证后修正。"  

**Fislett 顿悟点**：  
> "意识到必须同时考虑插入中间和末尾两种情况，缺一不可。例如当最大间隔在中间时插入中点更优，但末尾有大量空闲时直接插入末尾可能更优。"  

---

## 可视化与算法演示  

### 动画设计方案  
**HTML/Canvas 实现**：  
1. **初始布局**：横向时间轴从 1 到 d，红色方块表示考试日期，灰色条表示间隔。  
2. **高亮操作**：  
   - **最小间隔**：红色闪烁提示。  
   - **候选插入位置**：蓝色虚线框标出最大间隔中点和末尾。  
3. **动态调整**：  
   - 拖拽考试方块到候选位置，实时更新间隔颜色。  
   - 绿色高亮新计算的最小间隔。  

**音效设计**：  
- **拖拽成功**：8-bit "确认" 音效（短促上升音调）。  
- **错误操作**：低沉蜂鸣声。  

**复古像素风格**：  
- 使用 16 色调色板，时间轴以 8x8 像素方块表示考试，间隔条为 2 像素线条。  

### 自动演示模式  
1. **初始扫描**：红色高亮最小间隔。  
2. **模拟调整**：  
   - 删除最小间隔右侧考试，计算插入到最大间隔中点。  
   - 显示新间隔分布，绿色标出 μ 值。  
3. **对比结果**：返回原布局，重复插入末尾操作，对比最终 μ。  

---

## 核心代码片段  
```cpp
// 计算删除第x个考试后的最优μ
int calc(int x) {
    int lst = 0, min_gap = d, max_gap = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == x) continue;
        int gap = a[i] - a[lst] - 1;
        min_gap = min(min_gap, gap);
        max_gap = max(max_gap, gap);
        lst = i;
    }
    return min(min_gap, max((max_gap - 1) / 2, d - a[lst] - 1));
}
```

---
处理用时：97.64秒