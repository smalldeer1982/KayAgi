# 题目信息

# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 样例 #1

### 输入

```
1 48
5 7
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 5
0 1
3 5
```

### 输出

```
YES
1 4 ```

# AI分析结果



# Before an Exam

## 题目描述

明天彼得将参加生物考试。虽然他不怎么喜欢这门科目，但 $d$ 天前他得知必须参加这个考试。彼得的严格父母要求他立即开始复习，规定他第 $i$ 天的学习时间必须不少于 $minTime_i$ 小时且不超过 $maxTime_i$ 小时。考试前一天，父母会检查他的学习时间表是否合规。

现在彼得需要向父母展示一个包含 $d$ 个数字的时间表，其中第 $i$ 天的学习时间 $schedule_i$ 必须满足上述约束，且所有天的总时间恰好等于 $sumTime$。请判断是否存在这样的时间表。

---

## 题解分析与结论

### 综合题解分析
所有题解均采用贪心算法，核心思路分为两步：
1. **可行性判断**：检查总时间是否在最小时间总和与最大时间总和之间。
2. **贪心构造**：先分配每天最小时间，剩余时间按天逐步填充至最大值。

#### 关键算法要点
- **贪心策略的正确性**：若总时间合法，总能通过调整剩余时间构造出解。
- **时间复杂度**：$O(d)$，仅需线性遍历天数。
- **空间复杂度**：$O(d)$，存储每天的时间区间。

#### 解决难点
- **剩余时间分配**：按天顺序填充，保证每天不超过最大限制。
- **边界处理**：总和恰好等于最小或最大值时的特例无需额外处理。

---

## 精选题解（评分≥4星）

### 题解1. Loner_Knowledge（5星）
#### 亮点与评分理由
- 代码最简洁，逻辑清晰，无冗余操作。
- 直接通过差值计算剩余时间分配，无需嵌套循环。
- 变量命名合理，结构体设计清晰。

#### 核心代码
```cpp
sum -= sum_min; // 剩余待分配时间
for (int i = 0; i < d; ++i) {
    if (sum >= e[i].delta) {
        cout << e[i].max << " ";
        sum -= e[i].delta;
    } else {
        cout << e[i].min + sum << " ";
        sum = 0;
    }
}
```

### 题解2. Priori_Incantatem（4星）
#### 亮点与评分理由
- 直观的逐步填充思路，易于理解。
- 处理边界条件简洁，代码无冗余判断。

#### 核心代码
```cpp
s -= mins; // 计算剩余时间
i = 1;
while (s) {
    if (s > b[i] - a[i]) {
        s -= b[i] - a[i];
        a[i] = b[i];
    } else {
        a[i] += s;
        s = 0;
    }
    i++;
}
```

### 题解3. dfadfsafsdaf（4星）
#### 亮点与评分理由
- 代码紧凑，使用结构体提高可读性。
- 输出逻辑优化，避免冗余循环。

---

## 最优思路总结
1. **可行性验证**：计算 $\sum minTime_i$ 和 $\sum maxTime_i$，判断 $sumTime$ 是否在区间内。
2. **贪心填充**：从每天的最小值开始，按顺序将剩余时间分配到每天，直至达到最大值或分配完毕。

---

## 个人心得摘录
- **输出格式**：注意 `YES` 和 `NO` 必须全大写（Michael_kong）。
- **边界处理**：当剩余时间恰好为0时直接跳过循环（Priori_Incantatem）。
- **变量命名**：使用 `delta` 表示差值提升可读性（Loner_Knowledge）。

---

## 相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心选择最小堆。
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 区间调度问题。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 时间安排优化。

---
处理用时：78.64秒