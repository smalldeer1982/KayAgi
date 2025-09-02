# 题目信息

# Robert Hood and Mrs Hood

## 题目描述

Impress thy brother, yet fret not thy mother.



Robin's brother and mother are visiting, and Robin gets to choose the start day for each visitor.

All days are numbered from $ 1 $ to $ n $ . Visitors stay for $ d $ continuous days, all of those $ d $ days must be between day $ 1 $ and $ n $ inclusive.

Robin has a total of $ k $ risky 'jobs' planned. The $ i $ -th job takes place between days $ l_i $ and $ r_i $ inclusive, for $ 1 \le i \le k $ . If a job takes place on any of the $ d $ days, the visit overlaps with this job (the length of overlap is unimportant).

Robin wants his brother's visit to overlap with the maximum number of distinct jobs, and his mother's the minimum.

Find suitable start days for the visits of Robin's brother and mother. If there are multiple suitable days, choose the earliest one.

## 说明/提示

In the first test case, the only job fills all $ 2 $ days, both should visit on day $ 1 $ .

In the second test case, day $ 2 $ overlaps with $ 2 $ jobs and day $ 1 $ overlaps with only $ 1 $ .

In the third test case, Robert visits for days $ [1,2] $ , Mrs. Hood visits for days $ [4,5] $ .

## 样例 #1

### 输入

```
6
2 1 1
1 2
4 1 2
1 2
2 4
7 2 3
1 2
1 3
6 7
5 1 2
1 2
3 5
9 2 1
2 8
9 2 4
7 9
4 8
1 3
2 3```

### 输出

```
1 1
2 1
1 4
1 1
1 1
3 4```

# AI分析结果

### 题目内容重写

**题目描述**

Robin的兄弟和母亲要来拜访，Robin需要为每位访客选择一个开始访问的日期。

所有日期从1到n编号。访客会连续访问d天，所有这d天都必须在1到n之间。

Robin总共有k个危险的“工作”计划。第i个工作发生在第l_i天到第r_i天之间（1 ≤ i ≤ k）。如果某个工作发生在访客访问的d天中的任何一天，那么这次访问就会与这个工作重叠（重叠的长度不重要）。

Robin希望他兄弟的访问与尽可能多的不同工作重叠，而他母亲的访问则与尽可能少的工作重叠。

请为Robin的兄弟和母亲找到合适的开始访问的日期。如果有多个合适的日期，选择最早的一个。

**说明/提示**

在第一个测试用例中，唯一的工作占据了所有2天，因此兄弟和母亲都应该在第1天开始访问。

在第二个测试用例中，第2天与2个工作重叠，而第1天只与1个工作重叠。

在第三个测试用例中，兄弟访问第1天到第2天，母亲访问第4天到第5天。

### 题解综合分析与结论

本题的核心问题是如何高效地计算每个长度为d的区间与给定k个工作区间的重叠次数，并分别找到重叠次数最多和最少的区间。以下是各题解的思路对比：

1. **差分与前缀和**：大多数题解（如cly312、Temp113、sad_lin等）采用了差分与前缀和的技巧，将区间贡献转化为点贡献，通过差分数组记录每个区间的贡献，再通过前缀和计算每个区间的重叠次数。这种方法的时间复杂度为O(n)，非常高效。
   
2. **双指针与滑动窗口**：doumingze的题解使用了双指针与滑动窗口的技巧，通过维护两个指针L和R，动态计算每个区间的重叠次数。这种方法的时间复杂度也是O(n)，但实现上稍微复杂一些。

3. **树状数组与主席树**：Super_Cube和loser_seele的题解使用了树状数组和主席树来维护区间的重叠次数。这种方法的时间复杂度为O(n log n)，虽然效率稍低，但适用于更复杂的区间查询问题。

4. **暴力枚举与优化**：lyxxys和Meickol的题解通过暴力枚举每个区间，并优化了重叠次数的计算。这种方法的时间复杂度为O(n)，但实现上较为直接。

### 最优关键思路与技巧

**差分与前缀和**是本题的最优解法。通过将区间贡献转化为点贡献，再利用前缀和快速计算每个区间的重叠次数，既高效又易于实现。具体步骤如下：

1. **差分数组**：对于每个工作区间[l, r]，在差分数组中，将max(1, l - d + 1)位置加1，r + 1位置减1。
2. **前缀和**：通过前缀和计算每个位置i的重叠次数，即cover[i] += cover[i - 1]。
3. **遍历区间**：遍历所有长度为d的区间，找到重叠次数最多和最少的区间。

### 可拓展之处

差分与前缀和的技巧可以广泛应用于区间覆盖、区间查询等问题。类似的问题包括：

1. **区间覆盖问题**：给定多个区间，求某个区间被覆盖的次数。
2. **区间查询问题**：给定多个区间，查询某个区间内有多少个点被覆盖。

### 推荐题目

1. **P2184 贪婪大陆**：考察区间覆盖与查询，适合练习差分与前缀和的应用。
2. **P3372 线段树 1**：考察区间修改与查询，适合练习线段树的应用。
3. **P3368 树状数组 1**：考察单点修改与区间查询，适合练习树状数组的应用。

### 个人心得

在实现差分与前缀和时，需要注意差分数组的边界处理，特别是当l - d + 1小于1时，需要将其调整为1。此外，前缀和的计算顺序也很重要，必须从左到右依次计算，以确保每个位置的值正确。

### 精选题解

#### 题解作者：cly312 (★★★★★)

**关键亮点**：使用差分与前缀和，代码简洁高效，时间复杂度为O(n)。

**核心代码**：
```cpp
vector<int> cover(n + 2, 0);
for (int i = 0; i < k; ++i) {
    int l, r;
    cin >> l >> r;
    cover[max(1, l - d + 1)]++;
    cover[r + 1]--;
}
for (int i = 1; i <= n; ++i) {
    cover[i] += cover[i - 1];
}
int bday = 1, mday = 1;
int maxn = -1, minn = INT_MAX;
for (int day = 1; day <= n - d + 1; ++day) {
    if (cover[day] > maxn) {
        maxn = cover[day];
        bday = day;
    }
    if (cover[day] < minn) {
        minn = cover[day];
        mday = day;
    }
}
cout << bday << ' ' << mday << '\n';
```

#### 题解作者：Temp113 (★★★★☆)

**关键亮点**：同样使用差分与前缀和，代码清晰，时间复杂度为O(n)。

**核心代码**：
```cpp
for(int i = 1; i <= k; i++){
    cin >> l >> r;
    a[max_(1, l - d + 1)]++;
    a[r + 1]--;
}
for(int i = 1; i <= n; i++) a[i] += a[i - 1];
for(int i = 1; i <= n - d + 1; i++){
    if(a[i] > maxa){
        maxa = a[i];
        ans1 = i;
    }
    if(a[i] < mina){
        mina = a[i];
        ans2 = i;
    }
}
cout << ans1 << ' ' << ans2 << '\n';
```

#### 题解作者：sad_lin (★★★★☆)

**关键亮点**：使用差分与前缀和，代码简洁，时间复杂度为O(n)。

**核心代码**：
```cpp
for(int i=1;i<=m;i++){
    int l,r;
    cin>>l>>r;
    a[max(1ll,l-d+1)]++;
    a[r+1]--;
}
for(int i=1;i<=n;i++){
    a[i]+=a[i-1];
}
int mx=0,mxid=0,mi=1e9,miid=0;
for(int i=1;i<=n-d+1;i++){
    if(a[i]>mx){
        mx=a[i];
        mxid=i;
    } 
    if(a[i]<mi){
        mi=a[i];
        miid=i;
    } 
} 
cout<<mxid<<" "<<miid<<"\n";
```

---
处理用时：49.51秒