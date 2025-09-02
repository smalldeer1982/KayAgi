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

明天Peter要参加生物考试。虽然他不怎么喜欢这门科目，但$d$天前他知道必须参加这个考试。Peter严厉的父母要求他立即开始准备，规定第$i$天的学习时间必须在$minTime_i$到$maxTime_i$小时之间。今天父母要检查他的学习计划表，已知总学习时间为$sumTime$，请判断是否存在满足条件的时间表。

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
1 4
```

---

### 题解综合分析
所有题解均采用贪心算法，核心思路为：
1. **可行性判断**：检查sumTime是否在[∑minTime, ∑maxTime]区间
2. **贪心构造方案**：先取所有天的minTime，将剩余时间按天依次填充至maxTime

#### 最优思路提炼
- **双阶段处理**：先确定可行性，再构造具体方案
- **差值分配法**：计算总剩余时间后，按顺序给每个天分配不超过其maxTime的剩余时间
- **时间复杂度**：O(n)线性扫描，最优解法

---

### 精选题解（评分≥4★）

#### 1. Loner_Knowledge（5★）
**核心亮点**：
- 极简代码结构，直接操作差值数组
- 使用结构体清晰管理每日数据
- 实时计算并输出，避免存储中间结果

```cpp
struct Data { int min,max,delta; };
// 主逻辑部分
t -= sum.min;
for(int i=0; i<d; ++i) {
    if(t >= D[i].delta) {
        cout << D[i].max << " ";
        t -= D[i].delta;
    } else {
        cout << t + D[i].min << " ";
        t = 0;
    }
}
```

#### 2. Mars_Dingdang（4★）
**亮点**：
- 显式定义sub字段记录差值
- 使用flag控制循环提前终止
- 详细注释说明

```cpp
sum -= minn; // 待分配时间
for(int i=1; i<=d; i++){
    for(int j=1; j<=a[i].sub; j++){
        a[i].mint++;
        sum--;
        if(sum==0) { flag=1; break; }
    }
    if(flag) break;
}
```

#### 3. www2003（4★）
**创新点**：
- 前缀和预处理加速计算
- 从后往前逆向分配时间
- 数学方法确定每日值

```cpp
ans[i] = min(ma[i], d - qmin[i-1]); // 核心公式
d -= ans[i];
```

---

### 关键技巧总结
1. **差值预计算**：maxTime[i] - minTime[i]提前存储避免重复计算
2. **实时分配**：遍历时直接修改剩余时间，无需额外存储
3. **提前终止**：当剩余时间为0时立即跳出循环

---

### 类似题目推荐
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)  
   - 类型：贪心区间调度
2. [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)  
   - 类型：贪心选择策略
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   - 类型：优先队列贪心

---

### 题解心得摘录
1. **输出格式陷阱**（Michael_Kong）：
   > "特别要注意yes和no都要大写~~(我就是在这里被坑掉了一次的)~~"  
   → 仔细审题，注意输出格式细节

2. **构造策略**（konglk）：
   > "假设皮特是个把所有事情都推到最后的人，每天能最少就最少"  
   → 贪心策略的形象化理解

3. **调试经验**（Mars_Dingdang）：
   > "由于不符合条件的已经输出'NO'并结束程序，此处直接输出'YES'"  
   → 逻辑分层处理可减少判断嵌套

---
处理用时：53.68秒