# 题目信息

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()
```

### 输出

```
6
```

## 样例 #2

### 输入

```
()()()
```

### 输出

```
7
```

## 样例 #3

### 输入

```
)))
```

### 输出

```
0
```

# AI分析结果



## 【算法分类】
组合数学

## 【题解思路与难点】
### 核心思路
通过枚举每个左括号作为RSBS的最后一个左括号，利用范德蒙德卷积公式将原本O(n²)的复杂度优化到O(n)。关键步骤：
1. **前缀/后缀预处理**：计算每个位置左侧左括号数a、右侧右括号数b
2. **组合公式转化**：利用范德蒙德恒等式 $\sum C(a-1,i)C(b,i+1) = C(a+b-1,a)$
3. **模数优化**：预计算阶乘与逆元实现O(1)组合数查询

### 解决难点
1. **避免重复计算**：通过强制选择当前左括号作为子序列最后一个左括号，保证唯一性
2. **高效组合数计算**：预处理阶乘与逆元数组，利用快速幂求模逆元
3. **数学公式转化**：将暴力枚举的二维求和转化为单次组合数查询

## 【题解评分（≥4星）】
1. _Life_（5★）
   - 思路清晰，完整推导范德蒙德卷积转化过程
   - 代码简洁，使用线性逆元预处理
2. OIerBoy（4★）
   - 包含前置知识说明，适合组合数学基础较弱者
   - 代码模块化设计，变量命名清晰
3. wcyQwQ（4★）
   - 提供组合意义解释，强化数学直觉
   - 代码结构紧凑，逻辑流线型设计

## 【最优技巧提炼】
**关键公式推导**：  
对于每个左括号位置i，贡献量为 $\binom{a_i + b_i -1}{a_i}$  
推导路径：  
$\sum_{k=0}^{\min(a-1,b-1)} \binom{a-1}{k}\binom{b}{k+1} \xrightarrow{范德蒙德} \binom{a+b-1}{a}$

**实现优化**：  
预处理阶乘数组`fac[]`与逆元数组`inv[]`，通过 $C(n,m) = fac[n] \times inv[m] \times inv[n-m] \bmod P$ 实现O(1)查询

## 【同类题目推荐】
1. [CF1342E - Placing Rooks](https://www.luogu.com.cn/problem/CF1342E)（组合数学+容斥）
2. [P3197 越狱](https://www.luogu.com.cn/problem/P3197)（组合数快速幂）
3. [ARC110E - Shorten ABC](https://www.luogu.com.cn/problem/AT_arc110_e)（组合数学+位运算）

## 【代码片段】
```cpp
// 预处理阶乘与逆元
void init(int n) {
    fac[0] = 1;
    for(int i=1; i<=n; i++) fac[i] = fac[i-1] * i % mod;
    inv[n] = fpow(fac[n], mod-2);
    for(int i=n-1; i>=0; i--) inv[i] = inv[i+1] * (i+1) % mod;
}

// 主计算逻辑
for(int i=1; i<=n; i++) {
    if(s[i] == '(') {
        int a = prefix[i], b = suffix[i];
        ans = (ans + C(a + b - 1, a)) % mod;
    }
}
```

## 【可视化设计】
### 动画流程
1. **像素高亮**：用绿色方块标记当前左括号位置i
2. **动态统计**：左侧显示a值（蓝条增长），右侧显示b值（红条增长）
3. **公式展开**：在画布下方逐步显示 $\binom{a+b-1}{a}$ 计算过程
4. **音效反馈**：完成组合数计算时播放8bit音效

### 复古元素
- **调色板**：使用NES经典绿/红/蓝/黄四色
- **音效**：计算完成时播放《超级马里奥》金币音效片段
- **进度条**：用类似《魂斗罗》血条的样式展示a/b值

---

通过这种可视化设计，学习者可以直观理解每个左括号位置的贡献计算过程，同时复古元素的加入提升了学习趣味性。

---
处理用时：52.70秒