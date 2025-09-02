# 题目信息

# [USACO14JAN] Recording the Moolympics S

## 题目描述

Being a fan of all cold-weather sports (especially those involving cows),Farmer John wants to record as much of the upcoming winter Moolympics as possible.


The television schedule for the Moolympics consists of N different programs(1 <= N <= 150), each with a designated starting time and ending time.  FJ has a dual-tuner recorder that can record two programs simultaneously.

Please help him determine the maximum number of programs he can record in total.

农民约翰热衷于所有寒冷天气的运动（尤其是涉及到牛的运动）， 农民约翰想录下尽可能多的电视节目。 moolympics 的节目时间表有 $N$ 个不同的节目 （$1\le N\le 150$），每个节目给定开始时间和结束时间。FJ 有一个双调谐器录音机，可以同时录制两个节目。 请帮助他确定他能录制的节目的最大数量。


## 说明/提示

INPUT DETAILS:


The Moolympics broadcast consists of 6 programs.  The first runs from time 0 to time 3, and so on.


OUTPUT DETAILS:


FJ can record at most 4 programs.  For example, he can record programs 1 and 3 back-to-back on the first tuner, and programs 2 and 4 on the second tuner.


Source: USACO 2014 January Contest, Silver


## 样例 #1

### 输入

```
6
0 3
6 7
3 10
1 5
2 8
1 9```

### 输出

```
4```

# AI分析结果

### 综合分析与结论

本题的核心是贪心算法，通过按结束时间排序并维护两个录音机的结束时间，最大化可录制的节目数量。大部分题解都采用了类似的贪心策略，但在实现细节和优化思路上有所不同。部分题解还提供了动态规划的解法，虽然复杂度较高，但思路新颖。

### 所选高星题解

#### 1. 作者：shadowice1984 (★★★★★)
**关键亮点**：
- 通过交换两个录音机的优先级，简化了贪心策略的实现。
- 代码简洁且高效，逻辑清晰，易于理解。
- 提供了详细的思路解释，帮助读者理解贪心策略的正确性。

**核心代码**：
```cpp
for(int i=0;i<n;i++) {
    if(now1<=mis[i].st) {
        res++;now1=mis[i].ed;
    } else if(now2<=mis[i].st) {
        res++;now2=mis[i].ed;
        swap(now1,now2);
    }
}
```
**实现思想**：按结束时间排序后，优先选择结束时间较早的录音机进行录制，若无法录制则尝试另一个录音机，并交换优先级以保持最优。

#### 2. 作者：onepeople666 (★★★★☆)
**关键亮点**：
- 详细解释了区间贪心的基本思路，并扩展到双录音机的情况。
- 代码结构清晰，注释详细，便于初学者理解。
- 提供了与其他区间贪心题的对比，帮助读者举一反三。

**核心代码**：
```cpp
if(a[i].s>=p1&&p1>p2||(a[i].s>=p1&&a[i].s<p2)) {
    c++;p1=a[i].e;
} else if(a[i].s>=p2) {
    c++;p2=a[i].e;
}
```
**实现思想**：通过比较两个录音机的结束时间，选择最优的录音机进行录制，确保每次录制都尽可能减少录音机的空闲时间。

#### 3. 作者：ChenHacker (★★★★☆)
**关键亮点**：
- 强调了“潜力小的录音机优先”的贪心策略，优化了录制顺序。
- 代码简洁，逻辑清晰，易于实现。
- 提供了与其他贪心题的对比，帮助读者理解贪心策略的通用性。

**核心代码**：
```cpp
if(cpu0<cpu1) {int t=cpu0; cpu0=cpu1; cpu1=t;}
if(cpu0<=d[i].a) {cnt++; cpu0=d[i].b;}
else if(cpu1<=d[i].a) {cnt++; cpu1=d[i].b;}
```
**实现思想**：通过交换录音机的优先级，确保每次录制都选择结束时间较早的录音机，从而最大化录制数量。

### 最优关键思路与技巧
1. **按结束时间排序**：这是贪心策略的核心，确保每次选择结束时间最早的节目，以便为后续节目留出更多时间。
2. **双录音机维护**：通过维护两个录音机的结束时间，确保每次录制都选择最优的录音机，减少空闲时间。
3. **优先级交换**：在无法录制时，交换录音机的优先级，确保每次录制都尽可能减少录音机的空闲时间。

### 拓展思路与同类型题
- **同类型题**：类似的双资源调度问题，如多核CPU任务调度、多机调度等。
- **推荐题目**：
  1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
  2. [P2970 自私的放牧](https://www.luogu.com.cn/problem/P2970)
  3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)

### 个人心得总结
- **调试经历**：部分题解提到在实现过程中遇到的调试问题，如优先级交换的逻辑错误，通过逐步调试和验证，最终找到正确的实现方式。
- **顿悟感想**：贪心策略的正确性往往需要通过严格的证明来确保，尤其是在双资源调度问题中，交换优先级的策略能够有效减少空闲时间，提升整体效率。

---
处理用时：37.03秒