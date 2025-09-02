# 题目信息

# [NWRRC 2015] Distribution in Metagonia

## 题目描述



There are one hundred noble families in the country of Metagonia, and each year some of these families receive several ritual cubes from the Seer of the One. The One has several rules about cube distribution: if a family receives at least one cube, every prime divisor of the number of cubes received should be either $2$ or $3$ , moreover if one family receives a $> 0$ cubes and another family in the same year receives $b > 0$ cubes then a should not be divisible by $b$ and vice versa.

You are the Seer of the One. You know in advance how many cubes would be available for distribution for the next $t$ years. You want to find any valid distribution of cubes for each of these years. Each year you have to distribute all cubes available for that year.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
4
1
2
3
10
```

### 输出

```
1
1
1
2
1
3
2
4 6
```

# AI分析结果



**算法分类**: 构造

**综合分析与结论**:  
题目要求将整数分解为多个互不整除的2^a*3^b形式数的和，核心思路是构造满足条件的数，确保分解过程中2的指数递增、3的指数递减。各题解均采用贪心策略，每次选取当前剩余值中最大的2^a*3^b数，保证后续分解的数满足条件。

---

### 精选题解

#### 1. **VitrelosTia 题解 (⭐⭐⭐⭐)**  
**关键亮点**:  
- 通过分离2和3的因子，动态维护当前的基值(`now`)，确保每次分解的数具有更高的2的指数。  
- 使用最大3的幂优化剩余值的处理，保证单调性。  

**核心代码**:  
```cpp
void solve() {
    ans.clear();
    ll now = 1; 
    while (n) { 
        ll m = 1;
        while (n % 2 == 0) now *= 2, n /= 2;
        while (n % 3 == 0) now *= 3, n /= 3;
        while (m * 3 <= n) m *= 3;
        ans.push_back(now * m);
        n -= m;
    }
}
```

#### 2. **Sheep_YCH 题解 (⭐⭐⭐⭐)**  
**关键亮点**:  
- 代码简洁高效，直接提取最大可能的2^a*3^b数。  
- 通过逐步分解剩余值，保证每一步的2的指数严格递增。  

**核心代码**:  
```cpp
while (n > 0) {
    tmp = 1; 
    tn = n;
    while (tn % 2 == 0) tmp *= 2, tn /= 2;
    while (tmp * 3 <= n) tmp *= 3;
    ans[++num] = tmp;
    n -= tmp;
}
```

#### 3. **Flaw_Owl 题解 (⭐⭐⭐½)**  
**关键亮点**:  
- 详细数学推导，验证单调性的正确性。  
- 强调分解后剩余值的偶性分析，确保构造过程严谨。  

---

### 最优关键思路  
**核心策略**:  
1. **最大因子优先**：每次分解时，提取当前剩余值中最大的2的因子作为基值。  
2. **动态调整3的幂**：在基值基础上，尽可能取最大的3的幂，保证后续分解数的3的指数递减。  
3. **单调性保证**：剩余值必然包含更高次数的2因子，确保后续数的2的指数递增，避免整除关系。  

**实现技巧**:  
- 利用`while`循环快速提取2和3的因子。  
- 分离基值(`now`)与剩余值(`n`)，避免重复计算。  

---

### 拓展与举一反三  
**同类题目推荐**:  
1. [P2118 比例简化](https://www.luogu.com.cn/problem/P2118) - 构造满足比例的分数分解。  
2. P1465 循环数 - 分解数满足特定循环性质。  
3. [P7960 [NOIP2021] 报数](https://www.luogu.com.cn/problem/P7960) - 数论构造与筛法结合。  

**个人心得摘录**:  
- *"分解后的剩余值必然是偶数，保证了后续步骤的可行性"* —— Flaw_Owl 题解中的数学验证是关键。  
- *"避免重复计算2和3的因子，动态维护基值`now`"* —— VitrelosTia 的代码优化思路值得借鉴。

---
处理用时：69.74秒