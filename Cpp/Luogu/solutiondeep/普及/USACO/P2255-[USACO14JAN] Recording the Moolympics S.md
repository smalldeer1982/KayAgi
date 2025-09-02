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
本题为双调谐器区间调度问题，核心是贪心策略。最优解法将节目按结束时间排序，维护两个调谐器的最晚结束时间，每次优先选择保留更小结束时间的调谐器以最大化后续安排空间。动态规划解法虽可行但复杂度较高，贪心算法效率更优。

---

### 精选题解

#### 1. shadowice1984（⭐️⭐️⭐️⭐️⭐️）
**关键亮点**：  
- 每次选择后交换调谐器优先级，确保优先处理结束时间更早的调谐器。  
- 代码简洁高效，逻辑清晰，时间复杂度为O(n log n)。  

**代码核心**：
```cpp
sort(mis, mis+n); // 按结束时间排序
int now1 = -1, now2 = -1;
for(int i=0; i<n; i++) {
    if(now1 <= mis[i].st) { // 优先用第一调谐器
        now1 = mis[i].ed;
        res++;
    } else if(now2 <= mis[i].st) {
        now2 = mis[i].ed;
        res++;
        swap(now1, now2); // 交换以保持优先级
    }
}
```

#### 2. BFSBFSBFSBFS（⭐️⭐️⭐️⭐️）
**关键亮点**：  
- 严格数学证明贪心正确性，强调选择结束时间长的调谐器。  
- 代码直观，维护两个结束时间变量，处理逻辑明确。  

**代码核心**：
```pascal
sort(a, b); // 按结束时间排序
t := 0; t1 := 0;
for i := 1 to n do
    if a[i] >= t then
        // 优先放在t或t1中更大的位置
        if (t1 >= t) and (a[i] >= t1) then t1 := b[i]
        else t := b[i];
        s += 1;
    else if a[i] >= t1 then
        t1 := b[i];
        s += 1;
```

#### 3. A_Đark_Horcrux（⭐️⭐️⭐️⭐️）
**关键亮点**：  
- 直接类比经典单调谐器问题，扩展为双调谐器处理。  
- 处理逻辑简单，交换调谐器状态优化后续选择。  

**代码核心**：
```cpp
sort(a+1, a+n+1, cmp); // 按结束时间排序
int l = -1, t = -1;
for(int i=1; i<=n; i++) {
    if(a[i].x >= l) l = a[i].y, ans++;
    else if(a[i].x >= t) t = a[i].y, swap(l, t), ans++;
}
```

---

### 最优关键思路与技巧
1. **排序策略**：按节目结束时间升序排序，确保每次选择最早可用的调谐器。
2. **状态维护**：用两个变量记录调谐器结束时间，优先选择结束时间更晚的调谐器进行安排，以保留更小的结束时间。
3. **交换优化**：在安排第二个调谐器后交换两者顺序，确保后续处理始终优先考虑结束时间较早的调谐器。

---

### 同类题目推荐
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)（单调谐器版）
2. [P2970 [USACO09DEC]Selfish Grazing S](https://www.luogu.com.cn/problem/P2970)（区间贪心基础）
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)（二维区间调度扩展）

---
处理用时：60.74秒