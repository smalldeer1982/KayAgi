# 题目信息

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
2
5
0
16
4
7
0
333606206```

# AI分析结果



### 题目重述
#### Expected Median

**题目描述**  
Arul 有一个长度为 $n$ 的二进制数组 $a$。  
他将取出该数组所有长度为 $k$（$k$ 为奇数）的子序列，并计算它们的中位数。  
求所有中位数的和，答案对 $10^9 + 7$ 取模。

**说明**  
- 二进制数组仅包含 0 和 1  
- 子序列通过删除若干元素得到，无需连续  
- 中位数定义为排序后第 $\frac{k+1}{2}$ 位的元素  

**样例解释**  
对于输入 `4 3 [1,0,0,1]`，所有长度为 3 的子序列中位数之和为 0+1+1+0=2。

---

### 题解综合分析

#### 核心思路
所有题解均基于以下观察：  
1. 中位数为 1 的充要条件是子序列中 1 的个数 ≥ $m=\frac{k+1}{2}$  
2. 答案转化为统计满足条件的子序列数量  
3. 使用组合数学公式：$\sum_{i=m}^k \binom{c_1}{i} \binom{c_0}{k-i}$，其中 $c_1$ 是原数组中 1 的个数，$c_0$ 是 0 的个数

#### 关键技巧
- **组合数预处理**：通过预处理阶乘和逆元实现 $O(1)$ 查询组合数  
- **边界处理**：当 $i > c_1$ 或 $k-i > c_0$ 时组合数为 0  
- **模运算优化**：使用快速幂和递推法预处理逆元

---

### 精选题解

#### 1. aeiouaoeiu（⭐⭐⭐⭐⭐）
**核心亮点**  
- 清晰的预处理实现  
- 简洁的边界条件处理  
- 完全匹配题意的循环范围

**关键代码**  
```cpp
ll C(ll a,ll b){return (a<b||b<0)?0:frac[a]*inv[b]%p*inv[a-b]%p;}

int main() {
    // 预处理阶乘和逆元
    frac[0]=1;
    for(int i=1;i<maxn;i++) frac[i]=frac[i-1]*i%p;
    inv[maxn-1]=qpow(frac[maxn-1],p-2);
    for(int i=maxn-1;i>=1;i--) inv[i-1]=inv[i]*i%p;
    
    // 计算答案
    for(int i=m;i<=k;i++) 
        ans = (ans + C(cnt,i)*C(n-cnt,k-i))%p;
}
```

#### 2. Pink_Cut_Tree（⭐⭐⭐⭐）
**核心亮点**  
- 使用独立函数计算逆元  
- 显式的变量命名提升可读性  
- 明确的边界检查

**关键代码**  
```cpp
int C(int n,int m){
    if(n<m) return 0;
    return f[n]*ksm(f[m],mod-2)%mod*ksm(f[n-m],mod-2)%mod; 
}

for(int i=m;i<=min(k,cnt);i++)
    ans += C(cnt,i)*C(n-cnt,k-i);
```

#### 3. cjh20090318（⭐⭐⭐⭐）
**核心亮点**  
- 预处理阶乘逆元的优化实现  
- 使用最小循环变量范围  
- 简洁的代码风格

**关键代码**  
```cpp
int C(int n,int m){return n<m?0:(LL)f[n]*v[m]%mod*v[n-m]%mod;}

for(int i=(k+1)>>1,mi=s<k?s:k;i<=mi;i++)
    ans = (ans + (LL)C(s,i)*C(n-s,k-i))%mod;
```

---

### 最优思路总结
**关键步骤**  
1. 预处理阶乘数组 `fact[]` 和逆元数组 `inv[]`  
2. 统计原数组中 1 的个数 `cnt`  
3. 循环计算 $\sum_{i=(k+1)/2}^k \binom{cnt}{i} \binom{n-cnt}{k-i}$  

**实现要点**  
- 预处理阶乘时计算到 $2 \times 10^5$ 量级  
- 逆元预处理采用费马小定理+快速幂  
- 组合数函数包含自动边界检查  

---

### 拓展应用
**类似问题套路**  
- 统计满足特定条件的子序列数量  
- 组合数模运算的快速计算  
- 中位数相关的最值问题  

**推荐练习题**  
1. P3811 【模板】乘法逆元（数论基础）  
2. P4369 [Code+#4]组合数问题（组合数性质）  
3. P2638 安全系统（二维组合数应用）

---

### 心得体会摘录
1. **边界检查**：多位题解强调当 `i > cnt_1` 或 `k-i > cnt_0` 时必须返回 0  
2. **预处理顺序**：逆元数组需要反向递推预处理  
3. **循环优化**：实际循环范围为 `max(m, k-(n-cnt_0))` 到 `min(k, cnt_1)` 可减少计算量  
4. **调试技巧**：验证小样例时手动计算组合数结果

---
处理用时：66.35秒