# 题目信息

# [ABC177E] Coprime

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc177/tasks/abc177_e

$ N $ 個の整数があります。$ i $ 番目の数は $ A_i $ です。

「全ての $ 1\leq\ i\ <\ j\ \leq\ N $ について、$ GCD(A_i,A_j)=1 $」が成り立つとき、$ \{A_i\} $ は pairwise coprime であるといいます。

$ \{A_i\} $ が pairwise coprime ではなく、かつ、$ GCD(A_1,\ldots,A_N)=1 $ であるとき、$ \{A_i\} $ は setwise coprime であるといいます。

$ \{A_i\} $ が pairwise coprime、setwise coprime、そのどちらでもない、のいずれであるか判定してください。

ただし $ GCD(\ldots) $ は最大公約数を表します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ A_i\leq\ 10^6 $

### Sample Explanation 1

$ GCD(3,4)=GCD(3,5)=GCD(4,5)=1 $ なので pairwise coprime です。

### Sample Explanation 2

$ GCD(6,10)=2 $ なので pairwise coprime ではありませんが、$ GCD(6,10,15)=1 $ なので setwise coprime です。

### Sample Explanation 3

$ GCD(6,10,16)=2 $ なので、pairwise coprime でも setwise coprime でもありません。

## 样例 #1

### 输入

```
3

3 4 5```

### 输出

```
pairwise coprime```

## 样例 #2

### 输入

```
3

6 10 15```

### 输出

```
setwise coprime```

## 样例 #3

### 输入

```
3

6 10 16```

### 输出

```
not coprime```

# AI分析结果



【中文题目重写】

# [ABC177E] 互质

## 题目描述

给定包含 $N$ 个整数的数组 $\{A_i\}$，判断其属于以下哪种情况：

1. **两两互质**：所有数对的 GCD 均为 1  
2. **集合互质**：不满足两两互质，但整体 GCD 为 1  
3. **非互质**：上述两种情况均不满足  

## 输入格式

- 第一行为整数 $N$  
- 第二行包含 $N$ 个整数 $A_i$  

## 输出格式

输出判断结果：`pairwise coprime`、`setwise coprime` 或 `not coprime`  

## 样例

### 样例1
输入：  
3  
3 4 5  
输出：  
pairwise coprime  

### 样例2  
输入：  
3  
6 10 15  
输出：  
setwise coprime  

### 样例3  
输入：  
3  
6 10 16  
输出：  
not coprime  

---

**算法分类**：数学（质数/因数分析）

---

### 题解分析与结论

**核心思路**：  
通过统计每个数的倍数出现次数，避免直接计算所有数对的GCD。  
1. **桶计数**：记录每个数值的出现次数  
2. **因数筛查**：遍历所有可能的因数（2~1e6），统计其倍数总数  
   - 若某因数的倍数数 ≥2 → 存在非互质数对  
   - 若某因数的倍数数 =N → 整体GCD非1  
3. 综合上述条件判断结果  

**关键优化**：  
- 调和级数遍历倍数，复杂度 $O(M \log M)$（$M$ 为数值上限1e6）  
- 替代暴力 $O(N^2)$ 算法，适用于大规模数据  

---

### 精选题解（评分：4⭐）

**作者**：Elairin176  
**亮点**：  
- 巧用桶数组统计频次  
- 高效因数倍数筛查实现低复杂度  
- 逻辑清晰，代码简洁  

**核心代码**：  
```cpp
int res[1000001]; // 数值桶
bool a = true, b = true; // a:整体GCD是否为1, b:是否两两互质

for (int i = 2; i <= 1e6; ++i) {
    int cnt = 0;
    for (int j = i; j <= 1e6; j += i)  // 统计i的倍数总数
        cnt += res[j];
    if (cnt > 1) b = false;  // 存在数对不互质
    if (cnt == n) a = false; // 整体存在公共因数i
}

// 输出判断
if (b) cout << "pairwise coprime";
else if (a) cout << "setwise coprime"; 
else cout << "not coprime";
```

**实现要点**：  
- `a=true` 表示整体GCD为1（无公共因数覆盖所有数）  
- `b=false` 表示至少存在一对数不互质  

---

### 同类题目推荐

1. **P2158 [SDOI2008]仪仗队**（欧拉函数统计互质对）  
2. **P2440 木材加工**（二分答案结合因数分析）  
3. **P3912 素数个数**（质数筛法优化）  

---

**思维拓展**：  
本题的因数筛查思路可推广至以下场景：  
- 统计数组中存在公因数的数对数量  
- 快速判断多个数是否含有共同质因子  
- 求数组中所有数的最大公约数的快速方法

---
处理用时：110.18秒