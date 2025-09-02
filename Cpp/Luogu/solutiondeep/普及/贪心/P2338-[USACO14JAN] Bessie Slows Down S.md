# 题目信息

# [USACO14JAN] Bessie Slows Down S

## 题目背景

奶牛题


## 题目描述

Bessie the cow is competing in a cross-country skiing event at the winter Moolympic games.  She starts out at a speed of 1 meter per second. However, as she becomes more tired over time, she begins to slow down. Each time Bessie slows down, her speed decreases: she moves at 1/2 meter per second after slowing down once, then 1/3 meter per second after slowing down twice, and so on.

You are told when and where Bessie slows down, in terms of a series of events.  An event like this:

T 17
means that Bessie slows down at a specific time -- here, 17 seconds into the race.  An event like this:

D 10
means that Bessie slows down at a specific distance from the start -- in this case, 10 meters.

Given a list of N such events (1 <= N <= 10,000), please compute the amount of time, in seconds, for Bessie to travel an entire kilometer.  Round your answer to the nearest integer second (0.5 rounds up to 1).

贝西正在参加一项滑雪比赛。她从起点出发的时候，速度恒定为每秒 1 米。然而，随着比赛进程的增加，她会犯很多错误，每次失误都会使她的速度下降。当她第一次失误后，速度会下降到每秒1/2 米，第二次失误后，速度会下降到每秒 1/3 米，第 k 次失误后，速度会下降到每秒 1/(k + 1) 米。

约翰记录了贝西的所有失误，一共有 N 个。有两种失误，一种发生在比赛开始后的某个时间点，另一种发生在赛道的某个位置上。有时，贝西可能在某个时间点到达某个位置，而恰好在这个时间点和位置上都有一次失误的记录，这两个记录要算作不同的失误，会对贝西的速度造成两次影响。比赛的终点距离起点有 1000 米，请问贝西需要多少时间才能滑过终点？


## 说明/提示

前 10 秒，贝西的速度是每秒 1 米，她滑了 10 米。然后她遭遇了第一次失误，在接下

来的 20 秒内，她又滑了 10 米。之后她遭遇了第二次失误，还剩下 980 米，所以她共计花去

10 + 20 + 2940 = 2970 秒才完成比赛


## 样例 #1

### 输入

```
2
T 30
D 10```

### 输出

```
2970```

# AI分析结果

### 综合分析与结论

本题的核心是模拟Bessie在滑雪过程中速度的变化，并根据时间和距离的事件来计算她完成1000米所需的时间。所有题解都采用了类似的思路：将时间和距离事件分开存储并排序，然后通过模拟过程逐步计算时间和距离的变化。主要难点在于如何处理时间和距离事件的优先级，以及如何避免精度问题。

### 题解评分与亮点

1. **LevenKoko (4星)**
   - **关键亮点**：代码清晰，逻辑严谨，通过排序和模拟逐步处理时间和距离事件，避免了精度问题。
   - **个人心得**：作者提到第一次尝试时犯了“时间=路程*速度”的错误，提醒了读者在处理时间计算时要注意公式的正确性。
   - **核心代码**：
     ```cpp
     while(i<=lt||j<=ld) {
         v1=1.0/v;
         st=s+(t[i]*1.0-tot)*v1;
         sd=d[j];
         if(st<sd) {
             s=st;
             tot=t[i];
             i++;
         } else {
             tot+=(sd-s)/v1;
             s=sd;
             j++;
         }
         v++;
     }
     ```

2. **Yeji_ (4星)**
   - **关键亮点**：代码简洁，逻辑清晰，通过排序和模拟处理时间和距离事件，最后进行四舍五入。
   - **核心代码**：
     ```cpp
     for (int i=1;i<=n;i++)
         if ((r>tot2||(b[r]-y)*x+z>=a[l])&&(l<=tot1)) {
             if ((a[l]-z)/x+y>1000) break;
             y+=(a[l]-z)/x;
             z=a[l];x++;
             l++;
         } else {
             if (b[r]>1000) break;
             z+=(b[r]-y)*x;
             y=b[r];
             x++;
             r++;
         }
     ```

3. **moosssi (4星)**
   - **关键亮点**：代码结构清晰，通过排序和模拟处理时间和距离事件，最后进行四舍五入。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=D[0];i++){
         double temp=(T[j]-tim)*1.0*(1/k)+pos;
         while(temp<=D[i]&&j<=T[0]){
             tim=T[j++],pos=temp,k++;
             temp=(T[j]-tim)*1.0*(1/k)+pos;
         }
         tim+=(D[i]-pos)*1.0/(1/k);
         pos=D[i],k++;
     }
     ```

### 最优关键思路与技巧

1. **事件排序**：将时间和距离事件分开存储并排序，确保按顺序处理。
2. **模拟过程**：通过模拟逐步计算时间和距离的变化，确保每一步都正确处理。
3. **精度处理**：避免直接使用除法，通过公式变形减少精度误差。
4. **四舍五入**：在最终结果上进行四舍五入，确保输出符合要求。

### 可拓展之处

- **类似题目**：可以扩展到其他需要处理时间和距离变化的模拟题，如车辆行驶、运动员比赛等。
- **算法套路**：类似的事件驱动模拟题，可以通过排序和逐步模拟的方式解决。

### 推荐题目

1. **P2337 [USACO14JAN] Bessie Slows Down S**：本题的变种，考察类似的模拟思路。
2. **P2340 [USACO14JAN] Bessie Slows Down S**：另一道考察模拟和事件处理的题目。
3. **P2341 [USACO14JAN] Bessie Slows Down S**：进一步考察复杂事件处理的模拟题。

### 个人心得总结

- **调试经历**：多位作者提到在处理时间计算时容易犯“时间=路程*速度”的错误，提醒读者注意公式的正确性。
- **顿悟感想**：通过排序和模拟逐步处理事件，可以有效避免复杂的逻辑错误和精度问题。

---
处理用时：39.94秒