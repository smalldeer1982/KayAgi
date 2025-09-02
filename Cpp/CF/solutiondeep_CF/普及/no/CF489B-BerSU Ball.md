# 题目信息

# BerSU Ball

## 题目描述

The Berland State University is hosting a ballroom dance in celebration of its 100500-th anniversary! $ n $ boys and $ m $ girls are already busy rehearsing waltz, minuet, polonaise and quadrille moves.

We know that several boy&girl pairs are going to be invited to the ball. However, the partners' dancing skill in each pair must differ by at most one.

For each boy, we know his dancing skills. Similarly, for each girl we know her dancing skills. Write a code that can determine the largest possible number of pairs that can be formed from $ n $ boys and $ m $ girls.

## 样例 #1

### 输入

```
4
1 4 6 2
5
5 1 5 7 9
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2 3 4
4
10 11 12 13
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
1 1 1 1 1
3
1 2 3
```

### 输出

```
2
```

# AI分析结果



# BerSU Ball

## 题目描述

伯兰州立大学正在举办百年校庆舞会！有 $n$ 个男生和 $m$ 个女生正在练习华尔兹、小步舞、波罗乃兹和四对方舞。

我们需要为尽可能多的男生女生配对，要求每对舞伴的舞技差值不超过 1。

已知每个男生的舞技值和每个女生的舞技值，请编写程序计算最大可组成的舞伴对数。

## 样例 #1

### 输入

```
4
1 4 6 2
5
5 1 5 7 9
```

### 输出

```
3
```

---

## 算法分类
贪心

---

## 题解分析

所有题解均采用排序后贪心匹配的策略，核心差异在于实现方式。最优解法为双指针线性扫描，时间复杂度为 $O(n \log n + m \log m)$。

### 精选题解

#### 1. 作者：UperFicial（★★★★★）
**核心思路**：排序后双指针同步扫描  
- 两数组升序排列，指针初始指向头部
- 差值≤1时匹配成功，双指针后移
- 否则移动较小值的指针（贪心保留较大值的匹配机会）

```cpp
sort(a, a+n); sort(b, b+m);
int i=0, j=0, ans=0;
while(i < n && j < m) {
    if(abs(a[i]-b[j]) <= 1) ans++, i++, j++;
    else a[i]<b[j] ? i++ : j++;
}
```

#### 2. 作者：MrFish（★★★★☆）
**创新点**：优先队列实现隐式排序  
- 使用小根堆存储数值
- 比较堆顶元素决定弹出对象
- 适合动态数据流场景

#### 3. 作者：infinities（★★★★☆）
**优化亮点**：条件判断优化  
- 将匹配条件拆解为范围判断
- 避免重复计算绝对值
- 代码简洁且运算效率高

---

## 关键技巧
1. **排序预处理**：将两数组排序是贪心策略的基础
2. **双指针贪心**：通过指针同步移动保证局部最优解
3. **差值处理优化**：用直接比较替代绝对值计算提升效率

---

## 拓展应用
类似双序列匹配问题可参考以下套路：  
- 区间调度问题（如 P1803 线段覆盖）
- 两个有序序列元素匹配（如 P1106 删数问题）
- 最大值最小化问题（如 P2678 跳石头）

---

## 推荐练习
1. P1106 删数问题（贪心策略）
2. P1803 线段覆盖（区间贪心）
3. P2678 跳石头（二分答案）

---

## 心得体会摘录
> "既然 $b$ 数列最小的已经不行了，那更不可能匹配更大的 $a$，所以移动指针" —— UperFicial  
> "贪心的正确性在于：排序后优先匹配小的值，保留大的值的匹配机会" —— 题解讨论共识  
> "条件拆解后发现不需要计算绝对值，运算速度提升一倍" —— infinites 代码注释

---
处理用时：63.81秒