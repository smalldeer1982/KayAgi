# 题目信息

# Difference Row

## 题目描述

You want to arrange $ n $ integers $ a_{1},a_{2},...,a_{n} $ in some order in a row. Let's define the value of an arrangement as the sum of differences between all pairs of adjacent integers.

More formally, let's denote some arrangement as a sequence of integers $ x_{1},x_{2},...,x_{n} $ , where sequence $ x $ is a permutation of sequence $ a $ . The value of such an arrangement is $ (x_{1}-x_{2})+(x_{2}-x_{3})+...+(x_{n-1}-x_{n}) $ .

Find the largest possible value of an arrangement. Then, output the lexicographically smallest sequence $ x $ that corresponds to an arrangement of the largest possible value.

## 说明/提示

In the sample test case, the value of the output arrangement is $ (100-(-50))+((-50)-0)+(0-50)+(50-(-100))=200 $ . No other arrangement has a larger value, and among all arrangements with the value of $ 200 $ , the output arrangement is the lexicographically smallest one.

Sequence $ x_{1},x_{2},...\ ,x_{p} $ is lexicographically smaller than sequence $ y_{1},y_{2},...\ ,y_{p} $ if there exists an integer $ r $ $ (0<=r&lt;p) $ such that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ .

## 样例 #1

### 输入

```
5
100 -100 50 0 -50
```

### 输出

```
100 -50 0 50 -100 
```

# AI分析结果



# Difference Row

## 题目描述

给定 $n$ 个整数 $a_1,a_2,...,a_n$，将其排列为序列 $x_1,x_2,...,x_n$。定义排列的价值为相邻元素差的总和：$(x_1-x_2)+(x_2-x_3)+...+(x_{n-1}-x_n)$。求能获得最大价值的排列，若有多个解则输出字典序最小的那个。

## 样例解释

输入：`5 100 -100 50 0 -50`  
输出：`100 -50 0 50 -100`  
价值计算为：$(100-(-50)) + (-50-0) + (0-50) + (50-(-100)) = 200$，且该排列字典序最小。

---

**算法分类**：贪心

**核心思路**  
1. **公式化简**：价值表达式可化简为 $x_1 - x_n$，仅与首尾元素相关  
2. **贪心策略**：首元素取最大值，尾元素取最小值  
3. **字典序处理**：中间元素按升序排列以保证字典序最小  

---

### 精选题解分析

#### 1. Ryan_Yu（5星）
**关键亮点**  
- 公式推导简洁清晰，直接指出价值仅与首尾元素相关  
- 代码实现高效（排序后直接输出最大、中间升序、最小）  
- 代码可读性极佳，无冗余操作  

**核心代码**  
```cpp
sort(a+1,a+1+n);
printf("%lld ",a[n]);       // 输出最大值
for(i=2; i<n; i++)          // 中间元素升序
    printf("%lld ",a[i]);
printf("%lld\n",a[1]);      // 输出最小值
```

#### 2. JJA_（4星）
**关键亮点**  
- 详细推导公式合并过程  
- 代码注释完整，变量命名规范  
- 引入字典序的严格数学定义  

**实现技巧**  
通过两次排序确保中间元素的字典序（但实际只需一次排序）：  
```cpp
sort(a+1,a+n+1);
printf("%d ",a[n]);
for(int i=2; i<n; i++) 
    printf("%d ",a[i]);
```

#### 3. _Fatalis_（4星）
**关键亮点**  
- 利用排序后交换首尾的巧妙操作  
- 代码极简（仅需排序+交换+输出）  
- 隐含中间元素已满足字典序的特性  

**代码片段**  
```cpp
sort(a+1,a+n+1);
swap(a[1],a[n]);          // 交换首尾元素
for(int i=1;i<=n;i++) 
    cout<<a[i]<<" ";
```

---

### 最优思路总结
1. **公式化简思维**：通过数学推导将复杂问题简化为首尾元素的差  
2. **贪心选择策略**：直接选取极值点（最大头、最小尾）  
3. **字典序处理技巧**：利用排序后中间元素的天然升序性质  

**同类型题目推荐**  
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心策略的经典应用  
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：时间安排中的贪心排序  
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：字典序处理的进阶应用  

---

### 题解个人心得摘录
- **yinhy09**提到尝试优先队列优化，但实际直接排序即可解决  
- **呵呵侠**给出两种实现方式，验证了不同排序方向对中间元素的影响  
- **Mysterious_bird**强调本题的"大水题"特性，反映对公式化简的深刻理解  

**调试经验**：当公式化简后，需特别注意中间元素的排列是否天然满足字典序，避免不必要的二次排序操作。

---
处理用时：98.42秒