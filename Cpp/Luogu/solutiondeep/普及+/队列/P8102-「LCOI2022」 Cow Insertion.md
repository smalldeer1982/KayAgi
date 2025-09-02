# 题目信息

# 「LCOI2022」 Cow Insertion

## 题目背景

Farmer John 迎来了新奶牛——Bessie。每个奶牛都会有一定的开心值，Farmer John 希望 Bessie 能更幸福的生活在这里。

## 题目描述

牛棚里原来有 $n$ 头奶牛，开心值的感染距离 $m$，并且 $a_i$ 表示原来牛棚中第 $i(1\le i\le n)$ 头牛的开心值。并且，Bessie 同样拥有一个开心值 $A$。

整个牛棚的开心值是 $\sum\limits_{i=1}^{n-m+1}\ \max\limits_{i\le j\le i+m-1}\ a_j$，Bessie 可以住在任意两头牛的中间或起始以及最后。Farmer John 想知道：Bessie 来这里之后，整个牛棚的开心值最大为多少。

## 说明/提示

【样例解释】
- 当 Bessie 在第一个位置时（$50,60,100,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,50}+\max\cases{60,100}+\max\cases{100,70}$，即 $60+100+100=260$。
- 当 Bessie 在第二个位置时（$60,50,100,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,50}+\max\cases{50,100}+\max\cases{100,70}$，即 $60+100+100=260$。
- 当 Bessie 在第三个位置时（$60,100,50,70$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,100}+\max\cases{100,50}+\max\cases{50,70}$，即 $100+100+70=270$。
- 当 Bessie 在第四个位置时（$60,100,70,50$），整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{60,100}+\max\cases{100,70}+\max\cases{70,50}$，即 $70+100+100=270$。

显然，整个牛棚的开心值的最大值为 $\newcommand{\cases}[1]{\{#1\}}\max\cases{260,260,270,270}=270$。

【数据范围与约定】

|subtask|$n\le$|分值|
|:-:|:-:|:-:|
|$1$|$5\times10^2$|$10$|
|$2$|$5\times10^3$|$20$|
|$3$|$5\times10^6$|$70$|

对于 $100\%$ 的数据，$1\le m\le n$，$0\le a_i, A\le100$。

## 样例 #1

### 输入

```
3 2 50
60 100 70```

### 输出

```
270```

# AI分析结果

### 综合分析与结论
本题的核心在于计算插入新奶牛后牛棚开心值的最大值，关键在于高效处理插入位置变化对区间最大值和的影响。各题解均围绕单调队列展开，通过预处理不同长度区间的最大值，利用前缀和优化计算，枚举插入位置并分析其对结果的影响。

### 所选题解
- **作者：Suzt_ilymtics (赞：13) - 5星**
    - **关键亮点**：思路清晰，详细阐述了从暴力枚举到优化的过程，通过两次单调队列预处理出每个长度为 $m$ 和 $m - 1$ 的区间的贡献，再利用类似双指针的写法更新插入位置的结果，复杂度为 $O(n)$。
    - **核心代码**：
```cpp
// 预处理长度为 m 的区间的贡献
for(int i = 1; i < m; ++i) {
    while(head <= tail && a[q[tail]] < a[i]) tail --;
    q[++tail] = i;
}
for(int i = m; i <= n; ++i) {
    while(head <= tail && q[head] < i - m + 1) head ++;
    while(head <= tail && a[q[tail]] < a[i]) tail --;
    q[++tail] = i;
    b[i - m + 1] = a[q[head]];
}
// 预处理长度为 m - 1 的区间的贡献
head = 1, tail = 0;
int p = m - 1;
for(int i = 1; i < p; ++i) {
    while(head <= tail && a[q[tail]] < a[i]) tail --;
    q[++tail] = i;
}
for(int i = p; i <= n; ++i) {
    while(head <= tail && q[head] < i - p + 1) head ++;
    while(head <= tail && a[q[tail]] < a[i]) tail --;
    q[++tail] = i;
    c[i - p + 1] = a[q[head]];
}
for(int i = 1; i <= n - p + 1; ++i) {
    c[i] = max(c[i], A);
}
// 枚举插入位置
for(int i = 0; i <= n; ++i) {
    res -= b[i], res += c[i + 1];
    if(i - m + 1 >= 1) res += b[i - m + 1] - c[i - m + 1];
    Ans = max(Ans, ans + res);
}
```
- **作者：lalaouye (赞：4) - 4星**
    - **关键亮点**：通过画图分析插入位置对区间的影响，直观易懂。使用两次单调队列分别求出长度为 $m$ 和 $m - 1$ 的区间的最大值，再利用前缀和优化计算，复杂度为 $O(n)$。
    - **核心代码**：
```cpp
// 第一次单调队列，求长度为 m 的区间的最大值
for(int i = 1; i <= n; i++){
    while(tail >= head && i - q1[head] >= m) head++;
    while(tail >= head && a[q1[tail]] <= a[i]) tail--;
    q1[++tail]=i;
    if(i >= m)
        sum += a[q1[head]], b[i - m + 1] = a[q1[head]];
}
// 第二次单调队列，求长度为 m - 1 的区间的最大值
m--;
tail = 0, head = 1;
for(int i = 1; i <= n; i++){
    while(tail >= head && i - q2[head] >= m) head++;
    while(tail >= head && a[q2[tail]] <= a[i]) tail--;
    q2[++tail]=i;
    if(i >= m)
        c[i - m + 1] = a[q2[head]];
}
for(int i = 1; i <= n - m + 1; i++) c[i] = max(c[i], A);
for(int i = 1; i <= n; i++) s2[i] = s2[i - 1] + c[i];
m++;
for(int i = 1; i <= n; i++) s1[i] = s1[i - 1] + b[i];
// 枚举插入位置
for(int i = 0; i <= n; i++){
    int ret = c[i + 1];
    ret -= s1[i]; ret += s1[max(0, i - m + 1)];
    ret += (s2[i] - s2[max(0, i - m + 1)]);
    maxn = max(maxn, ret);
}
```
- **作者：Think (赞：2) - 4星**
    - **关键亮点**：思路清晰，通过预处理长度为 $m$ 和 $m - 1$ 的区间内元素最大值的前缀和，枚举插入位置并根据通项公式计算答案，注意判断边界越界问题，复杂度为 $O(n)$。
    - **核心代码**：
```cpp
// 预处理长度为 len 的区间内元素最大值的前缀和
void solve1(){
    memset(q, 0, sizeof(q));
    int head = 1, tail = 0;
    for(int i = 1; i <= n; i++){
        while(head <= tail && a[i] >= q[tail].val) tail--;
        q[++tail].val = a[i];
        q[tail].id = i;
        while(q[head].id <= i - len) head++;
        if(i >= len) pre1[i] = pre1[i - 1] + q[head].val;
    }
}
// 预处理长度为 len - 1 的区间内元素最大值的前缀和
void solve2(){
    memset(q, 0, sizeof(q));
    int head = 1, tail = 0;
    for(int i = 1; i <= n; i++){
        while(head <= tail && a[i] >= q[tail].val) tail--;
        q[++tail].val = a[i];
        q[tail].id = i;
        while(q[head].id <= i - len + 1) head++;
        if(i >= len - 1) pre2[i] = pre2[i - 1] + max(q[head].val, A);
    }
}
// 计算插入位置的影响
int influ(int i){
    int l = i, r = i + len - 1;
    if(l < 1) l = 1;
    if(r > n) r = n;
    return pre1[l] + (pre2[r] - pre2[l - 1]) + (pre1[n] - pre1[r]);
}
// 枚举插入点
for(int i = 0; i <= n; i++) ans = max(ans, influ(i));
```

### 最优关键思路或技巧
- **单调队列**：利用单调队列在 $O(n)$ 时间内预处理出不同长度区间的最大值，避免了暴力枚举的高复杂度。
- **前缀和**：通过计算前缀和，在枚举插入位置时可以 $O(1)$ 时间内计算区间和，进一步优化了时间复杂度。
- **分析影响范围**：仔细分析插入位置对区间的影响，只处理受影响的区间，减少不必要的计算。

### 可拓展之处
同类型题或类似算法套路：
- 区间最值问题：如滑动窗口最大值问题，可使用单调队列求解。
- 插入元素影响区间和问题：可参考本题思路，预处理区间信息，分析插入元素对区间的影响。

### 推荐题目
- [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)：经典的滑动窗口问题，可使用单调队列求解。
- [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)：涉及二维区间最值问题，可使用单调队列优化。
- [P2034 选择数字](https://www.luogu.com.cn/problem/P2034)：与本题类似，需要分析插入元素对结果的影响。

### 个人心得摘录与总结
- **SnowFlavour**：学校模拟赛选了此题，一开始用 ST 表，结果 MLE。后来通过画图分析插入元素对区间的影响，结合单调队列和尺取法优化，最终得到 $O(n)$ 复杂度的算法。总结：要根据数据范围选择合适的数据结构，遇到难题可通过研究样例、画图等方式寻找思路。
- **Proxima_Centauri**：一眼想到 ST 表，但空间开不下。后来使用单调队列，关键在于想到用两次单调队列求出 $f$ 和 $g$ 数组，然后进行计算，在考场容易写错。总结：要注意数据范围对算法选择的限制，对于复杂问题要仔细分析，避免出错。

---
处理用时：50.33秒