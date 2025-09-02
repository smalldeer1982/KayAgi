# 题目信息

# [USACO18OPEN] Out of Sorts S

## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。

她到目前为止最喜欢的算法是“冒泡排序”。这是 Bessie 的对长度为 $N$ 的数组 $A$ 进行排序的奶牛码实现。

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
         sorted = false
```
显然，奶牛码中的“moo”指令的作用只是输出“moo”。奇怪的是，Bessie 看上去执着于在她的代码中的不同位置使用这个语句。

给定一个输入数组，请预测 Bessie 的代码会输出多少次“moo”。

## 说明/提示

供题：Brian Dean

## 样例 #1

### 输入

```
5
1
5
3
8
2```

### 输出

```
4
```

# AI分析结果



### 综合分析与结论
本题的核心是计算冒泡排序中需要执行的外层循环次数。所有题解均围绕两个核心思路展开：
1. **位置差法**：通过排序后元素位置与原位置的差计算最大移动次数。
2. **逆序对法**：计算每个元素前比它大的数的个数，取最大值作为趟数。

两种思路均正确且时间复杂度为 $O(n \log n)$，其中位置差法代码更简洁，逆序对法更具普适性。关键点在于最后一次循环检查需额外加 1。

---

### 高评分题解（≥4星）

#### 题解1：作者 t14Zack（5星）
**关键亮点**  
- 思路直观：通过排序后位置差直接计算最大移动次数。
- 代码简洁：仅需结构体排序和遍历求差。
- 正确处理元素相同的情况：排序时稳定处理相同元素。

**个人心得**  
原题解提到“添加1说明最后一次迭代”，通过样例分析得出位置差+1的正确性。

**核心代码**  
```cpp
struct node { int in, zhi; } a[100000];
sort(a, a+n, cmp); // 按值排序，相同则按原位置
for (int j=0; j<n; j++) 
    ans = max(ans, a[j].in - j);
printf("%d\n", ans+1);
```

#### 题解2：作者 ljc20020730（4星）
**关键亮点**  
- 逆序对角度：深入分析冒泡排序的逆序对消除机制。
- 树状数组优化：高效计算每个元素前的逆序对数。

**核心代码**  
```cpp
int ans = 0;
for (int i=1; i<=n; i++) {
    int w = lower_bound(tmp, a[i]) - tmp; // 离散化
    update(w); // 树状数组更新
    ans = max(i - query(w), ans); // 计算当前逆序对数
}
printf("%d\n", ans+1);
```

#### 题解3：作者 HsKr（4星）
**关键亮点**  
- 详细解释：博客中结合模拟说明逆序对与冒泡趟数的关系。
- 离散化技巧：通过两次排序实现离散化，避免值域过大问题。

**核心代码**  
```cpp
sort(p+1, p+n+1); // 第一次按值排序
for (int i=1; i<=n; i++) p[i].val = i; // 离散化赋值
sort(p+1, p+n+1, cmp); // 第二次按原位置排序
```

---

### 关键思路总结
**最优方法**：位置差法  
1. 对元素排序并记录原位置。
2. 计算排序后每个元素的**原位置与排序后位置差**。
3. 取最大差值加 1 即为答案。

**核心技巧**  
- 稳定排序处理相同元素：确保相同值的元素按原顺序排列。
- 离散化技巧：在逆序对法中处理大值域。

---

### 推荐相似题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
2. [P6186 冒泡排序](https://www.luogu.com.cn/problem/P6186)  
3. [P1774 最接近神的人](https://www.luogu.com.cn/problem/P1774)  

---

### 重点代码片段（位置差法）
```cpp
#include <cstdio>
#include <algorithm>
struct node { int in, zhi; } a[100000];
bool cmp(const node &a, const node &b) {
    return a.zhi < b.zhi || (a.zhi == b.zhi && a.in < b.in);
}
int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i=0; i<n; i++) 
        scanf("%d", &a[i].zhi), a[i].in = i;
    std::sort(a, a+n, cmp);
    for (int j=0; j<n; j++)
        ans = std::max(ans, a[j].in - j);
    printf("%d\n", ans+1);
}
```

---
处理用时：78.60秒