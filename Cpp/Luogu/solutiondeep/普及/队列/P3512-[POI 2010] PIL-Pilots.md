# 题目信息

# [POI 2010] PIL-Pilots

## 题目描述

In the Byteotian Training Centre, the pilots prepare for missions requiring extraordinary precision and control.

One measure of a pilot's capability is the duration he is able to fly along a desired route without deviating too much -    simply put, whether he can fly steadily. This is not an easy task, as the simulator is so sensitive that it registers    even a slightest move of the yoke1.

At each moment the simulator stores a single parameter describing the yoke's position.

Before each training session a certain tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.1.png) is set.

The pilots' task then is to fly as long as they can in such a way that all the yoke's position measured during the    flight differ by at most ![](http://main.edu.pl/images/OI17/pil-en-tex.2.png). In other words, a fragment of the flight starting at time ![](http://main.edu.pl/images/OI17/pil-en-tex.3.png) and ending at time ![](http://main.edu.pl/images/OI17/pil-en-tex.4.png)    is within tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.5.png) if the position measurements, starting with ![](http://main.edu.pl/images/OI17/pil-en-tex.6.png)-th and ending with ![](http://main.edu.pl/images/OI17/pil-en-tex.7.png)-th,    form such a sequence ![](http://main.edu.pl/images/OI17/pil-en-tex.8.png) that for all elements ![](http://main.edu.pl/images/OI17/pil-en-tex.9.png) of this sequence, the inequality ![](http://main.edu.pl/images/OI17/pil-en-tex.10.png) holds.

Your task is to write a program that, given a number ![](http://main.edu.pl/images/OI17/pil-en-tex.11.png) and the sequence of yoke's position measurements,    determines the length of the longest fragment of the flight that is within the tolerance level ![](http://main.edu.pl/images/OI17/pil-en-tex.12.png).

给定 $n, k$ 和一个长度为 $n$ 的序列，求最长的最大值最小值相差不超过 $k$ 的子段。

## 说明/提示

样例解释：$5, 8, 6, 6$ 和 $8, 6, 6, 9$ 都是满足条件长度为 $4$ 的子段。

## 样例 #1

### 输入

```
3 9
5 1 3 5 8 6 6 9 10```

### 输出

```
4```

# AI分析结果

### 综合分析

题目要求在一个序列中找到最长的子段，使得该子段的最大值与最小值之差不超过给定的 $k$。由于序列长度 $n$ 可能达到 $3 \times 10^6$，算法的时间复杂度必须为 $O(n)$。大多数题解都采用了单调队列的思路，通过维护两个单调队列分别记录当前窗口的最大值和最小值，并通过双指针（滑动窗口）来动态调整窗口的大小。

### 最优思路与技巧

1. **单调队列**：通过维护两个单调队列，分别记录当前窗口的最大值和最小值。单调队列的核心思想是，当新元素加入时，移除队列中不可能成为最值的元素，从而保证队列的单调性。
2. **双指针（滑动窗口）**：通过两个指针（左指针和右指针）来维护当前窗口的边界。当窗口内的最大值与最小值之差超过 $k$ 时，移动左指针，缩小窗口，直到差值满足条件。
3. **时间复杂度优化**：由于单调队列的每个元素最多入队和出队一次，因此整体时间复杂度为 $O(n)$，能够处理大规模数据。

### 推荐题解

#### 1. 作者：alksdjhfg (5星)
- **关键亮点**：代码简洁，思路清晰，直接使用两个单调队列分别维护最大值和最小值，通过双指针动态调整窗口大小。
- **核心代码**：
  ```cpp
  while(head_mx<=tail_mx&&a[q_mx[tail_mx]]<a[i]) tail_mx--;
  while(head_mn<=tail_mn&&a[q_mn[tail_mn]]>a[i]) tail_mn--;
  q_mx[++tail_mx]=i; q_mn[++tail_mn]=i;
  while(a[q_mx[head_mx]]-a[q_mn[head_mn]]>k){
      if(q_mx[head_mx]<q_mn[head_mn]){pre=q_mx[head_mx]+1;head_mx++;}
      else {pre=q_mn[head_mn]+1;head_mn++;}
  }
  len=max(len,i-pre+1);
  ```

#### 2. 作者：Fan_Tuan (4星)
- **关键亮点**：代码结构清晰，通过两个单调队列分别维护最大值和最小值，并通过双指针动态调整窗口大小。
- **核心代码**：
  ```cpp
  while(frontn && frontn <= backn && a[i] < qn[backn]) --backn;
  while(frontm && frontm <= backm && a[i] > qm[backm]) --backm;
  qn[++backn] = a[i], qm[++backm] = a[i], qnid[backn] = i, qmid[backm] = i;
  while(qm[frontm] - qn[frontn] > k) {
      if(qnid[frontn] < qmid[frontm]) id = qnid[frontn] + 1, ++frontn;
      else id = qmid[frontm] + 1, ++frontm;
  }
  ans = max(ans, i - id + 1);
  ```

#### 3. 作者：HoshiuZ (4星)
- **关键亮点**：通过维护一个队列和两个单调队列，分别记录当前窗口的最大值和最小值，并通过双指针动态调整窗口大小。
- **核心代码**：
  ```cpp
  while(hid<=tid&&max(a[que_max[hmax]],a[i])-min(a[que_min[hmin]],a[i])>k) {
      if(que_id[hid]==que_max[hmax]) hmax++;
      if(que_id[hid]==que_min[hmin]) hmin++;
      hid++;
  }
  que_id[++tid]=i;
  while(hmax<=tmax&&a[i]>a[que_max[tmax]]) tmax--;
  que_max[++tmax]=i;
  while(hmin<=tmin&&a[i]<a[que_min[tmin]]) tmin--;
  que_min[++tmin]=i;
  ans=max(ans,tid-hid+1);
  ```

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
3. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)

### 总结
单调队列是解决区间最值问题的利器，尤其适合处理大规模数据。通过维护单调队列，可以在 $O(n)$ 的时间复杂度内解决滑动窗口类问题。掌握这一技巧后，可以轻松应对类似的题目。

---
处理用时：37.69秒