# 题目信息

# Ilya and Matrix

## 题目描述

Ilya is a very good-natured lion. He likes maths. Of all mathematical objects, his favourite one is matrices. Now he's faced a complicated matrix problem he needs to solve.

He's got a square $ 2^{n}×2^{n} $ -sized matrix and $ 4^{n} $ integers. You need to arrange all these numbers in the matrix (put each number in a single individual cell) so that the beauty of the resulting matrix with numbers is maximum.

The beauty of a $ 2^{n}×2^{n} $ -sized matrix is an integer, obtained by the following algorithm:

1. Find the maximum element in the matrix. Let's denote it as $ m $ .
2. If $ n=0 $ , then the beauty of the matrix equals $ m $ . Otherwise, a matrix can be split into 4 non-intersecting $ 2^{n-1}×2^{n-1} $ -sized submatrices, then the beauty of the matrix equals the sum of number $ m $ and other four beauties of the described submatrices.

As you can see, the algorithm is recursive.

Help Ilya, solve the problem and print the resulting maximum beauty of the matrix.

## 说明/提示

Consider the second sample. You need to arrange the numbers in the matrix as follows:

`<br></br>1 2<br></br>3 4<br></br>`Then the beauty of the matrix will equal: 4 + 1 + 2 + 3 + 4 = 14.

## 样例 #1

### 输入

```
1
13
```

### 输出

```
13
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
14
```

# AI分析结果



# Ilya and Matrix

## 题目描述

Ilya 有一只性格很好的狮子，他喜欢数学。在所有数学对象中，他最喜欢矩阵。现在他遇到了一个需要解决的复杂矩阵问题。

他有一个大小为 $2^n×2^n$ 的方阵和 $4^n$ 个整数。需要将这些数填入矩阵的每个单元格（每个数字放入一个独立的单元格），使得矩阵的美丽值最大化。

矩阵的美丽值通过递归算法计算：
1. 找到矩阵中的最大元素 $m$
2. 若 $n=0$，美丽值为 $m$；否则将矩阵划分为四个 $2^{n-1}×2^{n-1}$ 的子矩阵，美丽值为 $m$ 加上四个子矩阵美丽值的总和

## 输入输出样例

### 样例 #1
#### 输入
```
0
13
```
#### 输出
```
13
```

### 样例 #2
#### 输入
```
2
1 2 3 4
```
#### 输出
```
14
```

---

**算法分类**：贪心

**综合分析与结论**：  
题目本质是寻找各层级递归中最大值的最优累加方式。通过贪心策略，将数字从大到小排序后，每个层级的贡献次数为 4 的幂次。关键思路是计算每个数在各层级的前缀和，最终累加得到最大美丽值。

---

### 精选题解（评分4星以上）

#### 题解作者：linxuanrui（4.5星）
**关键亮点**：  
- 使用快速幂精确计算 4 的幂次，避免浮点精度问题  
- 清晰的变量命名和代码结构  
- 正确使用 `greater<int>()` 进行降序排序  

**核心代码**：  
```cpp
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

// 主逻辑
sort(a + 1, a + n + 1, greater<int>());
for (int i = 0; qpow(4, i) <= n; i++) {
    for (int j = 1; j <= qpow(4, i); j++) {
        ans += a[j];
    }
}
```

#### 题解作者：very_easy（4星）
**关键亮点**：  
- 手写快速幂函数保证整数运算准确性  
- 详细的思路图解辅助理解递归结构  
- 明确的变量类型声明避免溢出  

**核心代码**：  
```cpp
int ksm(int a, int b) {
    if (b == 0) return 1;
    int t = ksm(a, b / 2);
    return (b & 1) ? t * t * a : t * t;
}

// 主逻辑
sort(a + 1, a + n + 1, cmp);
for (int i = 0; ksm(4, i) <= n; i++) {
    for (int j = 1; j <= ksm(4, i); j++) {
        ans += a[j];
    }
}
```

---

**最优技巧总结**：  
1. **贪心排序**：降序排列后，每个数的贡献次数由其在各层级的覆盖范围决定  
2. **幂次计算**：使用快速幂或循环乘法避免浮点精度问题  
3. **数据类型**：必须使用 `long long` 防止累加溢出  

**同类题目推荐**：  
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）  
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）  
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)（字典序贪心）  

**调试心得**：  
- 必须使用 `long long` 类型，否则在 n 较大时会溢出  
- 循环条件 `pow(4,i)` 的精度问题曾导致多个提交错误，改用整数运算后解决  
- 初始未考虑递归的层级贡献次数，通过画图分析层级结构后得到正确规律

---
处理用时：167.77秒