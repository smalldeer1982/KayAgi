# 题目信息

# Binary Search

## 题目描述

Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $ p $ of size $ n $ , and a number $ x $ that needs to be found. A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation no more than $ 2 $ times before running the algorithm: choose the indices $ i $ , $ j $ ( $ 1\le i, j \le n $ ) and swap the elements at positions $ i $ and $ j $ .

After that, the binary search is performed. At the beginning of the algorithm, two variables $ l = 1 $ and $ r = n + 1 $ are declared. Then the following loop is executed:

1. If $ r - l = 1 $ , end the loop
2. $ m = \lfloor \frac{r + l}{2} \rfloor $
3. If $ p_m \le x $ , assign $ l = m $ , otherwise $ r = m $ .

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $ p_l $ is equal to $ x $ . It can be shown that $ 2 $ operations are always sufficient.

## 样例 #1

### 输入

```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1```

### 输出

```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3```

# AI分析结果



### 题目内容
# 二分查找

## 题目描述

Anton在徒步旅行中感到无聊，想解决些问题。他问Kirill有没有新题目，Kirill正好有一个。

给定一个长度为$n$的排列$p$，以及需要查找的数字$x$。排列的定义是包含$1$到$n$的每个整数恰好一次的数组。例如，$[2,3,1,5,4]$是排列，但$[1,2,2]$和$[1,3,4]$不是。

你需要使用二分查找算法，但数组可能未排序。在运行算法前，最多可以执行两次交换操作（选择两个位置交换元素）。算法流程如下：

1. 初始化$l=1$, $r=n+1$
2. 循环直到$r-l=1$：
   - 计算$m=\lfloor \frac{r+l}{2} \rfloor$
   - 若$p[m] \le x$，令$l=m$，否则$r=m$

目标是通过最多两次交换，使得算法结束后$p[l]=x$。

---

### 题解综合分析

所有题解核心思路一致：**只需一次交换即可满足条件**。通过模拟原二分过程找到最终位置$l$，将$x$所在位置与$l$交换。关键证明：交换后不影响二分路径的判断条件，因此最终$l$位置必为$x$。

#### 关键算法要点：
1. 模拟原二分过程确定最终$l$位置
2. 若$p[l] \neq x$，交换$x$的原位置与$l$位置
3. 该操作不影响二分过程中的条件判断，因此正确性成立

---

### 高分题解推荐

#### 1. 作者：Sternenlicht（⭐⭐⭐⭐⭐）
**关键亮点**：
- 分类讨论不同情况，逻辑严密
- 指出交换操作不影响二分路径的判断条件
- 代码简洁高效，时间复杂度O(n)

**核心代码**：
```cpp
int l=1, r=n+1;
while(r-l>1){
    int mid=(l+r)>>1;
    if(a[mid]<=x) l=mid;
    else r=mid;
}
if(a[l]==x) puts("0");
else puts("1"), write(l, ' '), write(ans);
```

#### 2. 作者：__Floze3__（⭐⭐⭐⭐⭐）
**关键亮点**：
- 简明扼要证明三种情况的统一处理
- 强调二分路径中$l$的特性（若被更新则必满足$p[l]\le x$）
- 代码结构清晰，易读性强

**核心代码**：
```cpp
int l=1, r=n+1;
while(r-l>1){
    int mid=(l+r)>>1;
    if(a[mid]<=x) l=mid;
    else r=mid;
}
if(a[l]==x) write << "0\n";
else write << "1\n" << l << ' ' << pos << '\n';
```

#### 3. 作者：JOE_ZengYuQiao_0928（⭐⭐⭐⭐）
**关键亮点**：
- 直观解释"交换后不影响二分结果"的直觉理解
- 代码包含详细注释，适合初学者理解

**核心代码**：
```cpp
int l=1,r=n+1; 
while(l+1<r){
    int mid=(l+r)/2;
    if(a[mid]<=x)l=mid;
    else r=mid;
}
if(a[l]==x)cout<<"0\n";
else cout<<"1\n"<<l<<" "<<ans<<"\n";
```

---

### 最优关键思路
**核心思想**：  
无论原排列如何，最终只需交换$x$的原位置与二分结束后的$l$位置。由于二分过程中所有判断条件基于$p[mid]\le x$，交换后该条件仍保持成立，因此二分路径不变，最终$l$位置必为$x$。

**实现技巧**：  
- 预处理记录$x$的初始位置
- 单次遍历模拟二分过程
- 仅需判断最终位置是否已为$x$，决定是否需要交换

---

### 类似题目推荐
1. **P1020 导弹拦截** - 二分+贪心优化（考察二分维护序列特性）
2. **P2678 跳石头** - 二分答案经典题（二分判断条件设计）
3. **P1182 数列分段 Section II** - 二分答案与数组划分（类似条件判断）

---
处理用时：57.64秒