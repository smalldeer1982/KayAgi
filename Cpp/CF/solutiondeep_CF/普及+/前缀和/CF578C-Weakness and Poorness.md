# 题目信息

# Weakness and Poorness

## 题目描述

You are given a sequence of n integers $ a_{1},a_{2},...,a_{n} $ .

Determine a real number $ x $ such that the weakness of the sequence $ a_{1}-x,a_{2}-x,...,a_{n}-x $ is as small as possible.

The weakness of a sequence is defined as the maximum value of the poorness over all segments (contiguous subsequences) of a sequence.

The poorness of a segment is defined as the absolute value of sum of the elements of segment.

## 说明/提示

For the first case, the optimal value of $ x $ is $ 2 $ so the sequence becomes $ -1 $ , $ 0 $ , $ 1 $ and the max poorness occurs at the segment "-1" or segment "1". The poorness value (answer) equals to $ 1 $ in this case.

For the second sample the optimal value of $ x $ is $ 2.5 $ so the sequence becomes $ -1.5,-0.5,0.5,1.5 $ and the max poorness occurs on segment "-1.5 -0.5" or "0.5 1.5". The poorness value (answer) equals to $ 2 $ in this case.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1.000000000000000
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
2.000000000000000
```

## 样例 #3

### 输入

```
10
1 10 2 9 3 8 4 7 5 6
```

### 输出

```
4.500000000000000
```

# AI分析结果



### 题目重写

# 弱点和贫穷度

## 题目描述

给定一个包含 $n$ 个整数的序列 $a_{1},a_{2},...,a_{n}$。

确定一个实数 $x$，使得调整后的序列 $a_{1}-x,a_{2}-x,...,a_{n}-x$ 的「弱点」尽可能小。

序列的「弱点」定义为所有连续子序列的「贫穷度」的最大值。

「贫穷度」定义为子序列元素和的绝对值。

## 说明/提示

第一个样例中，最优的 $x=2$，调整后序列为 $-1,0,1$，最大贫穷度出现在单个元素 "-1" 或 "1"，结果为 $1$。

第二个样例中，最优 $x=2.5$，调整后序列为 $-1.5,-0.5,0.5,1.5$，最大贫穷度出现在前两个或后两个元素，结果为 $2$。

## 样例 #1

### 输入
```
3
1 2 3
```

### 输出
```
1.000000000000000
```

## 样例 #2

### 输入
```
4
1 2 3 4
```

### 输出
```
2.000000000000000
```

---

### 题解综合分析

#### 关键思路总结
1. **函数单谷性**：调整后的序列最大绝对子段和关于x呈单谷函数，可通过三分法寻找极值点。
2. **动态规划优化**：在每次计算特定x的弱点值时，使用O(n)时间维护最大/最小子段和。
3. **精度控制**：通过固定迭代次数（如200次）或极小阈值（如1e-12）确保数值稳定性。

#### 推荐题解
1. **Prean（五星）**  
   - 亮点：简洁的三分实现，同时维护最大正子段和与最小负子段和，代码可读性极佳。  
   - 核心代码：
     ```cpp
     inline db f(const db&x){
         db f(0),g(0),ans(0);
         for(int i=1;i<=n;++i){
             f = max(f, 0) + a[i]-x;
             g = min(g, 0) + a[i]-x;
             ans = max(ans, max(fabs(f), fabs(g)));
         }
         return ans;
     }
     ```

2. **TernaryTree（四星半）**  
   - 亮点：显式维护以i结尾的最大/最小子段和，数学推导清晰，逻辑严谨。  
   - 核心代码：
     ```cpp
     double solve(double x) {
         double ans = 0;
         for(int i=1; i<=n; ++i) {
             f[i] = g[i] = a[i] - x;
             f[i] = min(f[i], f[i-1] + a[i] - x);
             g[i] = max(g[i], g[i-1] + a[i] - x);
             ans = max(ans, max(abs(f[i]), abs(g[i])));
         }
         return ans;
     }
     ```

3. **EnofTaiPeople（四星）**  
   - 亮点：采用前缀和极值差法，通过记录历史最小/最大前缀和优化计算，适合理解前缀和与极值关系的场景。  
   - 核心代码：
     ```cpp
     ID fuc(db x){
         db sum=0, res=0, mn=0, mx=0;
         for(int i=1; i<=n; ++i){
             sum += a[i]-x;
             res = max({res, fabs(sum-mn), fabs(sum-mx)});
             mn = min(mn, sum);
             mx = max(mx, sum);
         }
         return res;
     }
     ```

---

### 拓展练习
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   - 练习基础的最大子段和动态规划解法。

2. [CF939E Maximize!](https://www.luogu.com.cn/problem/CF939E)  
   - 单峰函数求极值的经典三分法题目。

3. [P3743 kotori的设备](https://www.luogu.com.cn/problem/P3743)  
   - 结合二分法与实数运算的典型能量管理问题。

---
处理用时：57.70秒