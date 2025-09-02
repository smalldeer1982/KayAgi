# 题目信息

# Berland National Library

## 题目描述

Berland National Library has recently been built in the capital of Berland. In addition, in the library you can take any of the collected works of Berland leaders, the library has a reading room.

Today was the pilot launch of an automated reading room visitors' accounting system! The scanner of the system is installed at the entrance to the reading room. It records the events of the form "reader entered room", "reader left room". Every reader is assigned a registration number during the registration procedure at the library — it's a unique integer from $ 1 $ to $ 10^{6} $ . Thus, the system logs events of two forms:

- "+ $ r_{i} $ " — the reader with registration number $ r_{i} $ entered the room;
- "- $ r_{i} $ " — the reader with registration number $ r_{i} $ left the room.

The first launch of the system was a success, it functioned for some period of time, and, at the time of its launch and at the time of its shutdown, the reading room may already have visitors.

Significant funds of the budget of Berland have been spent on the design and installation of the system. Therefore, some of the citizens of the capital now demand to explain the need for this system and the benefits that its implementation will bring. Now, the developers of the system need to urgently come up with reasons for its existence.

Help the system developers to find the minimum possible capacity of the reading room (in visitors) using the log of the system available to you.

## 说明/提示

In the first sample test, the system log will ensure that at some point in the reading room were visitors with registration numbers $ 1 $ , $ 1200 $ and $ 12001 $ . More people were not in the room at the same time based on the log. Therefore, the answer to the test is 3.

## 样例 #1

### 输入

```
6
+ 12001
- 12001
- 1
- 1200
+ 1
+ 7
```

### 输出

```
3```

## 样例 #2

### 输入

```
2
- 1
- 2
```

### 输出

```
2```

## 样例 #3

### 输入

```
2
+ 1
- 1
```

### 输出

```
1```

# AI分析结果



【题目内容中文翻译】
# Berland国家图书馆

## 题目描述

Berland国家图书馆最近在首都建成，馆内设有阅览室。自动化系统记录了读者的进出事件，格式为"+ r_i"（进入）或"- r_i"（离开）。读者编号为1到1e6的整数。要求根据日志计算阅览室的最小容量。

## 样例说明
样例1中，某时刻同时存在3人，故答案为3。样例2中初始有2人同时存在，故答案为2。

【算法分类】
模拟

【题解对比与结论】
核心难点在于处理初始存在的读者和动态维护最大人数。各题解均用标记数组记录读者状态，关键差异在于初始人数的计算方式：

1. **初始人数计算**：需统计所有未提前出现加号的减号操作对应的读者（这些读者必须在初始时存在）
2. **动态过程维护**：遍历操作序列时，实时更新当前人数并记录最大值

【高星题解推荐】

1. **wanggk（4星）**
   - **亮点**：预处理阶段明确分离初始人数计算与过程模拟，思路清晰
   - **关键代码**：
     ```cpp
     // 预处理初始人数
     for(int i=1;i<=n;i++) {
         if(a[i]>0) f[a[i]]=1;
         else if(a[i]<0 && f[-a[i]]==0) 
             f2[-a[i]]=1, cnt++;
     }
     // 动态过程
     for(int i=1;i<=n;i++) {
         if(a[i]>0) cnt++;
         else cnt--;
         ans = max(ans, cnt);
     }
     ```

2. **BYWYR（4星）**
   - **亮点**：实时处理初始人数，代码简洁高效
   - **关键代码**：
     ```cpp
     if(opt == '-') {
         if(!vis[x]) ans++; // 初始存在
         else vis[x] = false, now--;
     }
     ```

3. **zhicheng（4星）**
   - **亮点**：利用map动态维护状态，逻辑紧凑
   - **关键代码**：
     ```cpp
     if(book[s] == 0) ans++; 
     else book[s] = 0, d--;
     ```

【最优思路总结】
1. **预处理初始读者**：用标记数组记录所有未提前加号的减号读者
2. **实时更新最大值**：维护当前人数变量，在加号时立即更新最大值
3. **数据结构选择**：使用数组（或bitset）标记读者状态，O(1)时间查询

【拓展与类似题目】
- 类似初始状态处理的模拟题：CF847J（考试座位）、P3406（海底高铁）
- 动态维护最大值的场景：P2034 选择数字（滑动窗口）

【个人心得摘录】
- "注意初始存在读者可能在日志中被多次离开，但输入保证合法，无需处理重复减号"（wanggk调试心得）
- "减号时若读者未标记，说明是初始存在，直接增加容量而不影响当前人数"（BYWYR注释）

---
处理用时：289.10秒