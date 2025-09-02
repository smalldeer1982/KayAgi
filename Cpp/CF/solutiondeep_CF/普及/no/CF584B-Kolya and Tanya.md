# 题目信息

# Kolya and Tanya

## 题目描述

Kolya loves putting gnomes at the circle table and giving them coins, and Tanya loves studying triplets of gnomes, sitting in the vertexes of an equilateral triangle.

More formally, there are $ 3n $ gnomes sitting in a circle. Each gnome can have from $ 1 $ to $ 3 $ coins. Let's number the places in the order they occur in the circle by numbers from $ 0 $ to $ 3n-1 $ , let the gnome sitting on the $ i $ -th place have $ a_{i} $ coins. If there is an integer $ i $ ( $ 0<=i&lt;n $ ) such that $ a_{i}+a_{i+n}+a_{i+2n}≠6 $ , then Tanya is satisfied.

Count the number of ways to choose $ a_{i} $ so that Tanya is satisfied. As there can be many ways of distributing coins, print the remainder of this number modulo $ 10^{9}+7 $ . Two ways, $ a $ and $ b $ , are considered distinct if there is index $ i $ ( $ 0<=i&lt;3n $ ), such that $ a_{i}≠b_{i} $ (that is, some gnome got different number of coins in these two ways).

## 说明/提示

 $ 20 $ ways for $ n=1 $ (gnome with index $ 0 $ sits on the top of the triangle, gnome $ 1 $ on the right vertex, gnome $ 2 $ on the left vertex): ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF584B/e820d83cdfe0c59fc424109c332a1fb6000d6a18.png)

## 样例 #1

### 输入

```
1
```

### 输出

```
20```

## 样例 #2

### 输入

```
2
```

### 输出

```
680```

# AI分析结果



# Kolya and Tanya

## 题目描述

Kolya喜欢将地精围坐在圆桌旁并分给他们硬币，而Tanya喜欢研究构成等边三角形顶点的三个地精的组合。

具体来说，有$3n$个地精围成一圈。每个地精可以有$1$到$3$个硬币。将位置按顺时针编号为$0$到$3n-1$，设第$i$个位置的地精有$a_i$个硬币。如果存在整数$i$（$0 \le i < n$）使得$a_i + a_{i+n} + a_{i+2n} \neq 6$，则Tanya会满意。

计算满足条件的硬币分配方案数，结果对$10^9+7$取模。两种方案不同当且仅当至少存在一个位置硬币数不同。

## 说明/提示

当$n=1$时有20种合法方案（样例图示展示了一个三角形顶点的分配方式）。

## 输入输出样例

### 样例 #1
输入：1  
输出：20

### 样例 #2
输入：2  
输出：680

---

**算法分类**：数学（组合数学、快速幂）

---

### 题解综合分析

所有题解均采用**容斥原理**：总方案数$27^n$减去全不合法方案数$7^n$。核心在于：
1. 每个三元组的非法情况有7种（排列数6种+全2情况1种）
2. 快速幂计算大指数模值
3. 处理负数取模：$(a - b + mod) \% mod$

#### 最优思路提炼
- **逆向思维**：计算总合法数=全集-全不合法集合
- **快速幂优化**：$O(\log n)$时间计算大数幂模
- **组合数学**：每个三元组独立，方案数乘积性质

---

### 精选题解（评分≥4★）

#### 1. 云浅知处（5★）
**亮点**：
- 详细解释"正难则反"思想
- 指出易错点（错误计算为$20^n$的情况）
- 代码规范，带快速幂模板

**关键代码**：
```cpp
long long quickpower_and_remainder(long long x,long long y){
    long long ans=1,cnt=x;
    while(y){
        if(y&1) ans=ans*cnt%mod;
        cnt=cnt*cnt%mod;
        y>>=1;
    }
    return ans%mod;
}
```

#### 2. Lauzun（4★）
**亮点**：
- 简洁推导过程
- 代码精简，直接调用快速幂

**心得**：
> "正难则反思想在组合问题中非常实用，特别是当直接计算合法方案困难时"

#### 3. zhouzihe（4★）
**亮点**：
- 线性循环计算幂次，适合小规模数据
- 代码极简，适合快速实现

**代码片段**：
```cpp
for(int i=1;i<=n;i++){
    sum27 = sum27*27%mod;
    sum7 = sum7*7%mod;
}
```

---

### 关键实现技巧
1. **快速幂模板**：位运算加速幂计算
2. **负数处理**：减法后+mod再取模
3. **独立事件处理**：乘法原理分解每个三元组

---

### 拓展与相似题目
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226) - 快速幂基础
2. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313) - 组合数+快速幂
3. [P3197 越狱](https://www.luogu.com.cn/problem/P3197) - 同款容斥原理应用

---

### 个人心得摘录
> "当直接统计合法方案困难时，逆向计算非法方案往往能大幅简化问题" —— 云浅知处  
> "快速幂的位运算写法要注意取模时机，先乘再模保证不溢出" —— Mine_King  
> "循环计算幂次虽然效率稍低，但代码更易调试" —— HadrianZhang

---
处理用时：56.89秒