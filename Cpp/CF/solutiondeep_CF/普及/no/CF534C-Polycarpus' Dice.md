# 题目信息

# Polycarpus' Dice

## 题目描述

Polycarp has $ n $ dice $ d_{1},d_{2},...,d_{n} $ . The $ i $ -th dice shows numbers from $ 1 $ to $ d_{i} $ . Polycarp rolled all the dice and the sum of numbers they showed is $ A $ . Agrippina didn't see which dice showed what number, she knows only the sum $ A $ and the values $ d_{1},d_{2},...,d_{n} $ . However, she finds it enough to make a series of statements of the following type: dice $ i $ couldn't show number $ r $ . For example, if Polycarp had two six-faced dice and the total sum is $ A=11 $ , then Agrippina can state that each of the two dice couldn't show a value less than five (otherwise, the remaining dice must have a value of at least seven, which is impossible).

For each dice find the number of values for which it can be guaranteed that the dice couldn't show these values if the sum of the shown values is $ A $ .

## 说明/提示

In the first sample from the statement $ A $ equal to 8 could be obtained in the only case when both the first and the second dice show 4. Correspondingly, both dice couldn't show values 1, 2 or 3.

In the second sample from the statement $ A $ equal to 3 could be obtained when the single dice shows 3. Correspondingly, it couldn't show 1, 2, 4 or 5.

In the third sample from the statement $ A $ equal to 3 could be obtained when one dice shows 1 and the other dice shows 2. That's why the first dice doesn't have any values it couldn't show and the second dice couldn't show 3.

## 样例 #1

### 输入

```
2 8
4 4
```

### 输出

```
3 3 ```

## 样例 #2

### 输入

```
1 3
5
```

### 输出

```
4 ```

## 样例 #3

### 输入

```
2 3
2 3
```

### 输出

```
0 1 ```

# AI分析结果



### 中文重写题目
# Polycarpus的骰子

## 题目描述
Polycarp有$n$个骰子$d_1,d_2,...,d_n$，第$i$个骰子的面数范围为$1$到$d_i$。已知所有骰子朝上的点数之和为$A$。对于每个骰子，计算有多少个值可以确定其不可能出现（无论其他骰子如何投掷）。

## 样例 #1
### 输入
2 8  
4 4  
### 输出
3 3

## 样例 #2
### 输入
1 3  
5  
### 输出
4 

## 样例 #3
### 输入
2 3  
2 3  
### 输出
0 1 

---

**算法分类**: 数学

---

### 题解综合分析
所有题解均基于**极值分析法**，通过计算每个骰子的可能值区间，推导出不可能值的数量。关键公式为：  
不可能值数 = 总面数 - 可能值数 = d_i - (max_possible - min_possible + 1)

---

### 高星题解推荐

#### 1. 作者：lgx57（5星）
**关键亮点**：  
- 通过极值分析，清晰定义每个骰子的最小可能值`mi`和最大可能值`ma`  
- 代码简洁且变量命名合理（mi/ma）  
- 强调long long的重要性，避免整数溢出  

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    int mi = max(1ll, A - (sum - a[i])); // 最小值下限
    int ma = min(a[i], A - (n - 1));     // 最大值上限
    cout << a[i] - (ma - mi + 1) << ' ';
}
```

#### 2. 作者：wuyixiang（4星）
**关键亮点**：  
- 直接使用不等式推导出两种不可能情况  
- 代码简洁，公式推导步骤明确  
- 变量命名`sum`清晰体现总和概念  

**核心代码**：
```cpp
cout << max(k - (sum - a[i]) -1, 0LL) + max(a[i] - (k - n +1), 0LL);
```

#### 3. 作者：_Felix（4星）
**关键亮点**：  
- 通过`hhh`和`zzz`变量分别处理最大值和最小值情况  
- 使用`abs`简化可能值区间的计算  
- 代码注释帮助理解变量含义  

**核心代码**：
```cpp
long long hhh = min(a - n +1, d[i]); // 最大可能
long long zzz = max(1LL, a - (sum - d[i])); // 最小可能
cout << d[i] - (hhh - zzz +1);
```

---

### 最优解题思路
**关键技巧**：  
1. **极值分析法**：假设其他骰子全取最小值（1）或最大值（d_j）  
2. **公式推导**：  
   - 最大可能值 = min(d_i, A - (n-1))  
   - 最小可能值 = max(1, A - (总面数 - d_i))  
3. **边界处理**：通过max/min函数确保区间有效性  

---

### 同类题目推荐
1. [CF1345B - Card Constructions](https://www.luogu.com.cn/problem/CF1345B)（数学推导）  
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)（极值组合分析）  
3. [CF1520D - Same Differences](https://www.luogu.com.cn/problem/CF1520D)（数学公式转化）  

---

### 题解心得摘录
1. **lgx57**：  
   > "十年OI一场空，不开long long见祖宗" —— 强调大数运算的类型处理  
2. **Error_Eric**：  
   > "Python解法更简洁" —— 指出不同语言在数学题中的适用性差异  
3. **sto__Liyhzh__orz**：  
   > "最值问题只需考虑两种情况" —— 点明此类题目的核心分析维度

---
处理用时：52.88秒