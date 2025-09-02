# 题目信息

# Summer Homework

## 题目描述

By the age of three Smart Beaver mastered all arithmetic operations and got this summer homework from the amazed teacher:

You are given a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to perform on it $ m $ consecutive operations of the following type:

1. For given numbers $ x_{i} $ and $ v_{i} $ assign value $ v_{i} $ to element $ a_{xi} $ .
2. For given numbers $ l_{i} $ and $ r_{i} $ you've got to calculate sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316E1/095e734be6677a366eba0d190d121c644f5bca60.png), where $ f_{0}=f_{1}=1 $ and at $ i>=2 $ : $ f_{i}=f_{i-1}+f_{i-2} $ .
3. For a group of three numbers $ l_{i} $ $ r_{i} $ $ d_{i} $ you should increase value $ a_{x} $ by $ d_{i} $ for all $ x $ $ (l_{i}<=x<=r_{i}) $ .

Smart Beaver planned a tour around great Canadian lakes, so he asked you to help him solve the given problem.

## 样例 #1

### 输入

```
5 5
1 3 1 2 4
2 1 4
2 1 5
2 2 4
1 3 10
2 1 5
```

### 输出

```
12
32
8
50
```

## 样例 #2

### 输入

```
5 4
1 3 1 2 4
3 1 4 1
2 2 4
1 2 10
2 1 5
```

### 输出

```
12
45
```

# AI分析结果



# Summer Homework

## 题目描述

三岁的小海狸掌握了所有算术运算，老师布置了暑假作业：

给定整数序列 $a_1,a_2,...,a_n$，需要执行 $m$ 次操作：

1. 单点赋值：将 $a_{x_i}$ 设为 $v_i$
2. 区间查询：计算 $\sum_{i=0}^{r-l} f_i \times a_{l+i}$，其中 $f$ 是斐波那契数列（$f_0=f_1=1$）
3. 区间加法：给区间内所有元素增加 $d_i$

## 样例 #1

### 输入
```
5 5
1 3 1 2 4
2 1 4
2 1 5
2 2 4
1 3 10
2 1 5
```

### 输出
```
12
32
8
50
```

## 样例 #2

### 输入
```
5 4
1 3 1 2 4
3 1 4 1
2 2 4
1 2 10
2 1 5
```

### 输出
```
12
45
```

## 算法分类
线段树

## 题解分析与结论

### 题目核心难点
需要高效处理动态区间加权和问题，其中权值为斐波那契数列。直接暴力计算时间复杂度为 $O(nm)$，无法通过大数据量。

### 题解对比分析
1. **暴力解法（SSqwq_）**  
   - 思路：直接遍历区间计算加权和
   - 优点：代码简单
   - 缺点：无法处理大数据（$O(nm)$ 复杂度）
   - 评分：⭐️⭐️（仅适用于小数据）

2. **线段树维护双属性（Regimes）**  
   - 关键思路：线段树节点维护两个属性 Sum1（对应 $f_0$ 开始的加权和）和 Sum2（对应 $f_1$ 开始的加权和）
   - 合并策略：利用斐波那契递推公式 $f_{k+m} = f_{k-1}f_{m+1} + f_{k-2}f_m$ 合并子区间
   - 区间加法：通过预处理斐波那契前缀和计算增量
   - 评分：⭐️⭐️⭐️⭐️⭐️（完整处理所有操作，时间复杂度 $O(m \log n)$）

3. **线段树优化合并（liujiaxi123456）**  
   - 维护属性：每个节点存储 $g_0$（当前区间的 $f_0$ 加权和）和 $g_1$（$f_1$ 加权和）
   - 合并技巧：利用斐波那契性质推导出合并公式 $g_x = f_{x-1}g_1 + f_{x-2}g_0$
   - 懒标记处理：数学推导增量影响公式
   - 评分：⭐️⭐️⭐️⭐️⭐️（代码简洁，数学推导严谨）

### 最优题解代码
```cpp
// 线段树节点结构（Regimes 方案）
struct node {
    int Sum1, Sum2, siz; // siz为区间长度
};

node operator + (node a, node b) {
    node c;
    int k = a.siz;
    c.Sum1 = (a.Sum1 + f[k-1]*b.Sum2 + f[k-2]*b.Sum1) % MOD;
    c.Sum2 = (a.Sum2 + f[k]*b.Sum2 + f[k-1]*b.Sum1) % MOD;
    c.siz = a.siz + b.siz;
    return c;
}

// 区间加法的更新处理
void apply_add(int node, int d) {
    int len = tree[node].siz;
    tree[node].Sum1 = (tree[node].Sum1 + d * sumf[len-1]) % MOD;
    tree[node].Sum2 = (tree[node].Sum2 + d * (sumf[len] - 1)) % MOD;
    lazy[node] = (lazy[node] + d) % MOD;
}
```

### 关键思路总结
1. **数学建模**：将斐波那契加权和转化为可维护的区间属性
2. **线段树设计**：每个节点维护两个状态（当前区间起始为 $f_0$ 和 $f_1$ 的和）
3. **合并策略**：利用斐波那契数列的线性组合性质进行区间合并
4. **增量计算**：通过预处理斐波那契前缀和快速计算区间加法的影响

### 拓展应用
类似需要维护特殊数列加权和的区间查询问题，例如：
1. 等差数列/等比数列加权和
2. 多项式系数加权和
3. 自定义递推数列的区间查询

### 推荐练习题
1. P3372 【模板】线段树 1（区间加与求和）
2. P5278 算术天才⑨与等差数列（特殊区间性质维护）
3. P1471 方差（数学公式推导与线段树结合）

---
处理用时：163.47秒