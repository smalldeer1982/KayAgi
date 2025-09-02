# 题目信息

# Increase and Decrease

## 题目描述

Polycarpus has an array, consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Polycarpus likes it when numbers in an array match. That's why he wants the array to have as many equal numbers as possible. For that Polycarpus performs the following operation multiple times:

- he chooses two elements of the array $ a_{i} $ , $ a_{j} $ $ (i≠j) $ ;
- he simultaneously increases number $ a_{i} $ by $ 1 $ and decreases number $ a_{j} $ by $ 1 $ , that is, executes $ a_{i}=a_{i}+1 $ and $ a_{j}=a_{j}-1 $ .

The given operation changes exactly two distinct array elements. Polycarpus can apply the described operation an infinite number of times.

Now he wants to know what maximum number of equal array elements he can get if he performs an arbitrary number of such operation. Help Polycarpus.

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 4 1
```

### 输出

```
3
```

# AI分析结果



# Increase and Decrease

## 题目描述

Polycarpus 有一个包含 $n$ 个整数的数组 $a_{1},a_{2},...,a_{n}$。Polycarpus 喜欢数组中数字相同的情况。因此，他希望尽可能多地让数组中的元素相等。为此，Polycarpus 可以多次执行以下操作：

- 选择数组中的两个元素 $a_{i}$ 和 $a_{j}$（$i≠j$）；
- 同时将 $a_{i}$ 增加 $1$，将 $a_{j}$ 减少 $1$，即执行 $a_{i}=a_{i}+1$ 和 $a_{j}=a_{j}-1$。

该操作每次会改变两个不同的数组元素。Polycarpus 可以无限次执行此操作。现在他想知道，通过任意次数的操作后，最多能得到多少个相同的数组元素。

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 4 1
```

### 输出

```
3
```

---

**算法分类**：数学

---

### 综合题解分析

所有题解均基于以下核心观察：**操作不改变数组总和**。通过数学推导得出：

1. 若总和是 $n$ 的倍数，则所有元素可调整为相同（最多 $n$ 个相同元素）
2. 否则，最多有 $n-1$ 个元素相同

关键难点在于证明当总和不是 $n$ 的倍数时，至少能构造 $n-1$ 个相同元素。题解通过贪心思路说明，多余的数值可以集中到某个元素上，其他元素则调整为统一值。

---

### 精选题解（评分≥4星）

#### 题解作者：TheCliffSwallow（评分：★★★★☆）
**关键亮点**：
- 通过多个样例验证结论，增强理解
- 详细解释"多余数值集中处理"的构造方法
- 代码简洁，直接计算总和取模判断

**核心代码**：
```cpp
int main() {
    int n, s = 0;
    cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        s += a[i];
    }
    cout << (s%n == 0 ? n : n-1);
}
```
**实现思想**：计算总和后直接模 $n$ 判断结果，输出 $n$ 或 $n-1$。

---

#### 题解作者：Vibration886（评分：★★★★☆）
**关键亮点**：
- 直击问题本质，给出清晰的数学结论
- 代码采用条件表达式简化输出逻辑
- 突出总和不变的核心性质

**核心代码**：
```cpp
sum%n==0 ? cout<<n : cout<<n-1;
```
**实现思想**：通过三元运算符实现简洁判断。

---

#### 题解作者：lrmlrm_（评分：★★★★☆）
**关键亮点**：
- 明确总结"舍弃一个数"的贪心策略
- 代码使用 `long long` 避免溢出风险
- 代码结构清晰，输入处理高效

**核心代码**：
```cpp
signed main() {
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lld",&x);
        sum+=x;
    }
    printf(sum%n==0 ? "%lld" : "%lld", sum%n==0 ? n : n-1);
}
```
**实现思想**：采用 `long long` 类型处理大数，逻辑与前述解法一致。

---

### 关键思路总结
**核心技巧**：利用总和不变的性质，通过模运算判断可能的最大相同元素数量。  
**思维模式**：识别操作中的不变量（总和），建立问题与数学模运算的直接联系。  
**实现技巧**：直接计算总和并取模，避免复杂模拟操作。

---

### 拓展应用
同类问题可关注以下特征：
- 操作中存在不变量（如总和、异或值等）
- 最终状态与初始状态的数学关系（如整除性）

**推荐练习题目**：
1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心+数学）
2. [CF1445A Array Rearrangment](https://codeforces.com/problemset/problem/1445/A)（数学性质+构造）
3. [AT_abc347_c Ideal Holidays](https://atcoder.jp/contests/abc347/tasks/abc347_c)（模运算应用）

---
处理用时：76.97秒