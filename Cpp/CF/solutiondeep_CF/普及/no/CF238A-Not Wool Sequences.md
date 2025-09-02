# 题目信息

# Not Wool Sequences

## 题目描述

A sequence of non-negative integers $ a_{1},a_{2},...,a_{n} $ of length $ n $ is called a wool sequence if and only if there exists two integers $ l $ and $ r $ $ (1<=l<=r<=n) $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF238A/2ec5f782c063d456c865928ec08f722fe4394a16.png). In other words each wool sequence contains a subsequence of consecutive elements with xor equal to 0.

The expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF238A/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the operation of a bitwise xor to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example, in languages C++ and Java it is marked as "^", in Pascal — as "xor".

In this problem you are asked to compute the number of sequences made of $ n $ integers from 0 to $ 2^{m}-1 $ that are not a wool sequence. You should print this number modulo $ 1000000009 $ $ (10^{9}+9) $ .

## 说明/提示

Sequences of length $ 3 $ made of integers 0, 1, 2 and 3 that are not a wool sequence are (1, 3, 1), (1, 2, 1), (2, 1, 2), (2, 3, 2), (3, 1, 3) and (3, 2, 3).

## 样例 #1

### 输入

```
3 2
```

### 输出

```
6
```

# AI分析结果



# 非羊毛序列

## 题目描述

给定长度为 $n$ 的非负整数序列 $a_1,a_2,...,a_n$，若存在区间 $[l,r]$ 使得子序列异或和为 0，则称为羊毛序列。要求计算取值范围在 $[0,2^m-1]$ 的非羊毛序列数量，结果对 $10^9+9$ 取模。

## 算法分类
组合数学

## 题解分析与结论
通过构造前缀异或数组 $b_i = a_1 \oplus ... \oplus a_i$，将问题转化为 $b$ 数组的严格递增约束。非羊毛序列等价于 $b$ 数组所有元素互不相同且不含 0（除初始的 $b_0=0$）。最终转化为从 $[1,2^m-1]$ 中选 $n$ 个不同数的排列问题，计算公式为 $\prod_{i=0}^{n-1}(2^m-1-i)$。

---

### 精选题解

#### 题解4：Vct14（★★★★★）
**关键亮点**：  
- 精炼的数学推导，直接指出核心公式 $A_{2^m-1}^n$  
- 代码简洁高效，无冗余计算

**核心代码**：
```cpp
int main(){
    int n,m;cin>>n>>m;
    long long pw=1,c=1;
    for(int i=1; i<=m; i++) pw=pw*2%mod;pw--;
    for(int i=0; i<n; i++) c=c*(pw-i)%mod;
    cout<<c;
    return 0;
}
```

#### 题解2：wloving（★★★★★）
**关键亮点**：  
- 详细的前缀异或性质分析  
- 包含快速幂实现，强化数学计算理解

**核心代码**：
```cpp
ll mypow(ll a,ll n){
    ll ans=1;
    while(n){
        if(n&1) ans=ans*a%M;
        a=a*a%M;
        n>>=1;
    }
    return ans;
}
int main(){
    ll tmp=mypow(2,m)-1;
    for(int i=0;i<n;i++) ans=ans*(tmp-i)%M;
    cout<<ans;
}
```

#### 题解6：czh___（★★★★☆）
**关键亮点**：  
- 简洁的快速幂实现  
- 直接应用排列公式，代码可读性强

**核心代码**：
```cpp
int main(){
    ll s=ksm(2,m,mod)-1;
    for(int i=0;i<n;i++) ans=ans*(s-i)%mod;
    cout<<ans;
}
```

---

## 关键思路
1. **前缀异或转换**：将连续子序列异或和转化为前缀数组的差分异或  
2. **组合数学建模**：将约束条件转化为排列问题，避免重复值  
3. **模运算优化**：在每一步乘法中及时取模防止溢出

## 拓展应用
类似问题可考虑前缀和性质与排列组合的结合，例如：  
- 限制子数组和的特殊条件  
- 避免特定元素重复出现的排列计数

## 推荐习题
1. [P1465](https://www.luogu.com.cn/problem/P1465) - 前缀统计  
2. [P2119](https://www.luogu.com.cn/problem/P2119) - 魔法阵（组合数学）  
3. [CF276D](https://codeforces.com/problemset/problem/276/D) - 位运算性质与极值问题  

## 心得摘录
> "构造前缀异或数组是本题的突破口，将复杂的子序列问题转化为简单的元素唯一性约束" —— 通过转换问题维度，将动态约束转化为静态排列问题，极大简化了分析难度。

---
处理用时：168.95秒