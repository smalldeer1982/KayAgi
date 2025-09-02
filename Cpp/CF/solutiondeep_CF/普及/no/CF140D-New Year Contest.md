# 题目信息

# New Year Contest

## 题目描述

As Gerald sets the table, Alexander sends the greeting cards, and Sergey and his twins create an army of clone snowmen, Gennady writes a New Year contest.

The New Year contest begins at 18:00 (6.00 P.M.) on December 31 and ends at 6:00 (6.00 A.M.) on January 1. There are $ n $ problems for the contest. The penalty time for each solved problem is set as the distance from the moment of solution submission to the New Year in minutes. For example, the problem submitted at 21:00 (9.00 P.M.) gets penalty time 180, as well as the problem submitted at 3:00 (3.00 A.M.). The total penalty time is calculated as the sum of penalty time for all solved problems. It is allowed to submit a problem exactly at the end of the contest, at 6:00 (6.00 A.M.).

Gennady opened the problems exactly at 18:00 (6.00 P.M.) and managed to estimate their complexity during the first 10 minutes of the contest. He believes that writing a solution for the $ i $ -th problem will take $ a_{i} $ minutes. Gennady can submit a solution for evaluation at any time after he completes writing it. Probably he will have to distract from writing some solution to send the solutions of other problems for evaluation. The time needed to send the solutions can be neglected, i.e. this time can be considered to equal zero. Gennady can simultaneously submit multiple solutions. Besides, he can move at any time from writing one problem to another, and then return to the first problem from the very same place, where he has left it. Thus the total solution writing time of the $ i $ -th problem always equals $ a_{i} $ minutes. Of course, Gennady does not commit wrong attempts, and his solutions are always correct and are accepted from the first attempt. He can begin to write the solutions starting from 18:10 (6.10 P.M.).

Help Gennady choose from the strategies that help him solve the maximum possible number of problems, the one with which his total penalty time will be minimum.

## 说明/提示

In the sample, one of Gennady's possible optimal strategies is as follows. At 18:10 (6:10 PM) he begins to write the first problem and solves it in 30 minutes (18:40 or 6.40 P.M.). At 18:40 (6.40 P.M.) he begins to write the second problem. There are 320 minutes left before the New Year, so Gennady does not have the time to finish writing the second problem before the New Year. At 0:00 (12.00 A.M.) he distracts from the second problem, submits the first one, and returns immediately to writing the second problem. At 0:10 (0.10 A.M.), he completes the solution for the second problem, submits it and gets 10 minute penalty time. Note that as the total duration of the contest is 720 minutes and Gennady has already spent 10 minutes on reading the problems, he will not have time to solve the third problem during the contest. Yes, such problems happen to exist.

Competitions by the given rules are held annually on the site http://b23.ru/3wvc

## 样例 #1

### 输入

```
3
30 330 720
```

### 输出

```
2 10
```

# AI分析结果



### 题目重写
**题目名称**：新年比赛

**题目描述**  
Gennady 参加了一场跨年比赛，比赛从 18:00 开始持续到次日 6:00。共有 $n$ 道题目，每题的罚时为提交时间到 0 点的分钟差。Gennady 在比赛开始的前 10 分钟评估题目难度，之后开始解题。每题的解题时间为 $a_i$ 分钟，可以随时暂停或切换题目。求解最多能完成的题目数及对应的最小总罚时。

### 算法分类
**贪心**、**排序**

---

### 题解分析与结论
所有题解均采用贪心策略，按解题时间升序排列，优先解决耗时短的题目。核心思路为：
1. **时间分段处理**：在 0 点前完成的题目统一在 0 点提交（无罚时），0 点后完成的题目立即提交（按时间差累计罚时）。
2. **初始时间扣除**：总可用时间为 720 分钟，需扣除初始 10 分钟，剩余 710 分钟用于解题。
3. **边界处理**：精确计算跨 0 点的题目提交时间和罚时。

---

### 高星题解精选（≥4星）

#### 1. 题解作者：Crism_qwq（4.5星）
**关键亮点**  
- **时间分段清晰**：将总时间分为第一天 350 分钟和第二天 360 分钟，逻辑直观。
- **代码可读性高**：通过两个循环分别处理 0 点前和后的题目，罚时计算明确。
**核心代码**  
```cpp
sort(a+1,a+1+n);
int k=1;
while(k<=n && a[k]<=time1) {
    time1 -= a[k];
    k++;
}
time2 += time1; // 合并剩余时间到第二天
while(k<=n && a[k]<=time2) {
    time2 -= a[k];
    sum += 360 - time2; // 罚时为剩余时间的补数
    k++;
}
cout << k-1 << " " << sum;
```

#### 2. 题解作者：Eason_AC（4星）
**关键亮点**  
- **代码简洁高效**：直接通过一次遍历计算罚时，利用前缀和优化时间统计。
- **边界处理严谨**：通过 `max(0, s[i] - 350)` 避免负数罚时。
**核心代码**  
```cpp
sort(a + 1, a + n + 1);
int s[107] = {0}, ans = 0, res = 0;
for(int i=1; i<=n; i++) {
    if(s[i-1] + a[i] > 710) break;
    s[i] = s[i-1] + a[i];
    res += max(0, s[i] - 350);
}
cout << ans << " " << res;
```

#### 3. 题解作者：飞啾6373（4星）
**关键亮点**  
- **分阶段处理明确**：先处理 0 点前的题目，再单独处理跨 0 点的首题。
- **注释清晰**：通过注释强调 0 点提交的临界条件。
**核心代码**  
```cpp
int times = 0, ans = 0, anst = 0;
sort(a, a+n);
for(int i=0; i<n; i++) {
    times += a[i];
    if(times > 350) break;
    ans++;
}
times -= 350;
if(times > 0 && times <= 360) {
    ans++;
    anst += times;
}
for(; i<n; i++) {
    times += a[i];
    if(times > 360) break;
    anst += times;
    ans++;
}
```

---

### 最优思路总结
1. **贪心排序**：优先解决耗时短的题目以最大化解题数。
2. **时间分段计算**：将总时间分为 0 点前（350 分钟）和 0 点后（360 分钟），分别处理。
3. **罚时动态累加**：0 点后每题的罚时为其完成时间的累计值（即 `总耗时 - 350`）。

---

### 类似题目推荐
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)  
   **标签**：贪心、排序  
   **相似点**：通过排序优化等待时间总和。

2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   **标签**：贪心、优先队列  
   **相似点**：每次合并最小代价的果子，类似最小化总耗时。

3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)  
   **标签**：贪心、排序  
   **相似点**：交替选择最大最小值以最大化能量积累。

---
处理用时：58.51秒