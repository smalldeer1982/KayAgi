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



## 算法分类
贪心算法

## 题解思路与核心难点

### 核心问题
通过调整一个考试日期，最大化所有相邻考试间最小休息时间μ。  
**关键观察**：原始μ由最小间隔决定，修改该间隔或其相邻间隔能有效提升μ。

### 解决步骤
1. **定位最小间隔**：找到原始数组中最小的间隔及其位置。
2. **尝试两种修改**：
   - **修改最小间隔右端点**：计算删除该点后的最大可能间隔，将其拆分为两段或放到最后。
   - **修改最小间隔左端点**（若存在）：同理处理。
3. **评估最优解**：比较两种修改后的μ，取最大值。

### 难点分析
- **如何高效计算修改后的间隔**：需遍历数组，跳过被修改点，动态维护间隔的最小值和最大值。
- **候选插入位置的选择**：需考虑插入到最大间隔中间或最后一天两种情况。

## 题解评分（≥4星）

1. **DaiRuiChen007（5星）**  
   - 思路清晰，代码简洁高效。
   - 直接定位最小间隔，分情况讨论修改策略。
   - 时间复杂度O(n^2)，但实际表现优秀。

2. **Fislett（4星）**  
   - 与DaiRuiChen007思路一致，代码结构稍异。
   - 使用函数`f`封装逻辑，可读性良好。

3. **XL4453（4星）**  
   - 代码极简，核心逻辑与前述一致。
   - 省略部分注释，但实现高效。

## 最优思路提炼

### 关键步骤
1. **遍历原始数组**，找到最小间隔的位置`pos`。
2. **模拟删除`pos`对应的考试**，计算：
   - 剩余间隔的最小值`min_gap`
   - 最大间隔拆分为两段后的中间值`(max_gap-1)/2`
   - 插入到末尾的间隔`d - last -1`
3. 取三者最小值作为候选μ，比较左右端点修改后的结果。

### 代码片段
```cpp
int calc(int x) {
    int lst=0, min_gap=d, max_gap=0;
    for(int i=1; i<=n; ++i) {
        if(i==x) continue;
        int gap = a[i] - a[lst] -1;
        min_gap = min(min_gap, gap);
        max_gap = max(max_gap, gap);
        lst = i;
    }
    return min(min_gap, max( (max_gap-1)/2, d - a[lst]-1 ));
}
```

## 同类型题目
- **P1056 排座椅**：贪心选择间隔最大的位置分割。
- **P2216 [HAOI2007] 理想的正方形**：二维滑动窗口求极值。
- **P2899 [USACO08JAN] Cell Phone Network G**：贪心覆盖最小节点。

## 可视化设计

### 动画演示
1. **初始状态**：展示原始考试日期及间隔，红色高亮最小间隔。
2. **删除操作**：灰色标记被删除的考试，动态更新剩余间隔。
3. **插入候选**：
   - **最大间隔拆分**：绿色箭头指示插入位置，显示分割后的两段。
   - **末尾插入**：黄色标记最后一天，展示新增间隔。
4. **结果比较**：对比两种插入方式的μ，高亮最终最大值。

### 复古像素风格
- **颜色方案**：8位红（最小间隔）、绿（最大间隔）、黄（末尾插入）。
- **Canvas绘制**：网格化日期轴，方块表示考试，间隔用线段连接。
- **音效**：插入时播放短促"哔"声，找到最优解时播放胜利音效。

### 交互功能
- **步进控制**：按键逐步执行定位、删除、计算步骤。
- **参数调节**：可输入自定义考试日期，观察算法动态调整。

通过此设计，学习者可直观理解贪心策略的核心操作与决策过程。

---
处理用时：152.04秒