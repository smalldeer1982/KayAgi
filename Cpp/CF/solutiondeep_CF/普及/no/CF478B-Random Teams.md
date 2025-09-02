# 题目信息

# Random Teams

## 题目描述

 $ n $ participants of the competition were split into $ m $ teams in some manner so that each team has at least one participant. After the competition each pair of participants from the same team became friends.

Your task is to write a program that will find the minimum and the maximum number of pairs of friends that could have formed by the end of the competition.

## 说明/提示

In the first sample all the participants get into one team, so there will be exactly ten pairs of friends.

In the second sample at any possible arrangement one team will always have two participants and the other team will always have one participant. Thus, the number of pairs of friends will always be equal to one.

In the third sample minimum number of newly formed friendships can be achieved if participants were split on teams consisting of $ 2 $ people, maximum number can be achieved if participants were split on teams of $ 1 $ , $ 1 $ and $ 4 $ people.

## 样例 #1

### 输入

```
5 1
```

### 输出

```
10 10
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 1
```

## 样例 #3

### 输入

```
6 3
```

### 输出

```
3 6
```

# AI分析结果



# Random Teams

## 题目描述

$ n $ 名比赛参与者被分成 $ m $ 个组（每组至少一人）。比赛结束后，同一组的每对参与者成为朋友。

请编写程序计算比赛结束后可能形成的最小和最大朋友对数。

## 说明/提示

第一样例所有参与者在一个组，产生 10 对朋友。

第二样例无论怎么分组总有一组 2 人、另一组 1 人，朋友对数恒为 1。

第三样例最小朋友对数产生于每组 2 人，最大产生于分组方案为 [1,1,4]。

## 样例 #1

### 输入
```
5 1
```

### 输出
```
10 10
```

---

**算法分类**: 组合数学

---

### 题解综合分析

所有题解均基于组合数公式 $C(x,2)=\frac{x(x-1)}{2}$ 展开。核心思路高度一致：
- **最小值**通过尽可能均匀分配人数实现
- **最大值**通过构造单极大组实现

#### 最优思路提炼
1. **最大值**：将 $m-1$ 组设为 1 人，剩余 $n-m+1$ 人组成单组，计算 $C(n-m+1,2)$
2. **最小值**：
   - 基础分配：每组 $\lfloor n/m \rfloor$ 人
   - 剩余 $n\%m$ 人每人分配到不同组，使这些组人数为 $\lfloor n/m \rfloor+1$
   - 计算公式：$余数组数 \times C(\lfloor n/m \rfloor+1,2) + 其余组数 \times C(\lfloor n/m \rfloor,2)$

---

### 精选题解（评分≥4星）

#### 1. 作者：云浅知处（5星）
**关键亮点**：
- 完整数学推导：用柯西不等式证明最小值分配策略
- 使用函数增长性分析最大值构造原理
- 给出公式的取整处理细节

**代码核心**：
```cpp
// 核心计算逻辑
long long min_val = m * (n/m) * (n/m-1)/2 + (n/m)*(n%m);
long long max_val = (n-m+1)*(n-m)/2;
```

#### 2. 作者：wzhcsl（4星）
**关键亮点**：
- 代码封装组合数计算函数
- 包含特判n<m的边界情况
- 变量命名清晰易读

**核心代码**：
```cpp
long long calc(long long x) {
    return x * (x - 1) / 2;
}
// 主逻辑
ans1 = k * calc(n/m+1) + (m-k)*calc(n/m);
ans2 = calc(n-m+1);
```

#### 3. 作者：_Katyusha（4星）
**关键亮点**：
- 用数学归纳法证明分组策略
- 推导均分公式的详细展开式
- 代码简洁高效

**核心公式推导**：
```
最小值公式：
m*(n/m)*(n/m-1)/2 + (n%m)*(n/m)
```

---

### 相似题目推荐
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036) - 组合数应用
2. [CF1512B Almost Rectangle](https://www.luogu.com.cn/problem/CF1512B) - 构造极值分布
3. [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100) - 位运算与极值处理

---

### 关键实现技巧
**最小值计算优化**：
```cpp
long long base = n / m;   // 基础人数
long long extra = n % m;  // 需要+1的组数
min_val = extra * (base+1)*base/2 + (m-extra)*base*(base-1)/2;
```
通过将组合数展开为多项式运算，避免重复计算相同值。

---

### 调试心得摘录
> "注意n<m时需要特判输出0 0，否则计算n-m+1会出现负数" —— 作者：wzhcsl  
> "必须用long long防止乘法溢出，第一次提交没开WA了三个点" —— 作者：IGA_Indigo

这些经验强调了边界条件处理和数据类型选择的重要性。

---
处理用时：59.42秒