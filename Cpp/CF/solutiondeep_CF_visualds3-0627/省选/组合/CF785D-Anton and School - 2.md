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



**唯一算法分类**: 组合数学 + 前缀和/后缀和

---

### **综合分析与结论**  
**核心思路**：  
1. **枚举分界点**：对每个左括号，视为子序列的最后一个左括号，避免重复计数。  
2. **前缀/后缀统计**：预处理每个位置左边的左括号数（包含自身）和右边的右括号数。  
3. **范德蒙德卷积**：将暴力枚举的 O(n²) 求和转化为组合数计算，公式为 `C(a+b-1, a)`，其中 `a` 为左侧左括号数，`b` 为右侧右括号数。  
4. **快速组合数计算**：预处理阶乘和逆元，实现 O(1) 查询组合数模值。

**难点与解决方案**：  
- **数学推导**：需将双重求和转化为组合数，利用范德蒙德恒等式简化计算。  
- **边界处理**：如空序列、奇数长度等，通过组合数定义直接过滤无效情况。  
- **模运算优化**：预处理阶乘逆元，避免重复计算。

**可视化设计要点**：  
- **动画效果**：  
  - 高亮当前处理的左括号，动态显示其左右括号数量。  
  - 展示组合数计算过程，如 `C(a+b-1, a)` 的分解步骤。  
- **像素风格**：用 8 位色块表示括号，红色块表示当前左括号，蓝色块表示右侧可选的右括号。  
- **音效提示**：计算贡献时播放短促“滴”声，累计答案时播放上扬音调。  

---

### **题解清单 (≥4星)**  
1. **作者：_Life_ (★★★★★)**  
   - **亮点**：代码简洁，线性预处理逆元，直接应用范德蒙德公式。  
   - **代码片段**：  
     ```cpp  
     for(int i=1;i<=n;i++)  
         if(str[i]=='(')  
             ans=(ans+C(x[i]+y[i]-1,x[i]))%mod;  
     ```  
2. **作者：YuntianZhao (★★★★☆)**  
   - **亮点**：详细推导组合数公式，代码注释清晰。  
   - **心得**：“必须选择当前左括号以避免重复，这是关键。”  
3. **作者：是个汉子 (★★★★☆)**  
   - **亮点**：强调避免重复的思路，强制选择最后一个左括号。  

---

### **核心代码实现**  
**预处理阶乘与逆元**：  
```cpp  
fac[0] = 1;  
for(int i=1; i<=n; i++) fac[i] = fac[i-1] * i % mod;  
inv[n] = fastpow(fac[n], mod-2);  
for(int i=n-1; i>=0; i--) inv[i] = inv[i+1] * (i+1) % mod;  
```  

**统计前缀与后缀**：  
```cpp  
for(int i=1; i<=n; i++)  
    x[i] = x[i-1] + (str[i] == '(');  
for(int i=n; i>=1; i--)  
    y[i] = y[i+1] + (str[i] == ')');  
```  

**计算贡献**：  
```cpp  
int C(int n, int m) {  
    return fac[n] * inv[m] % mod * inv[n-m] % mod;  
}  
ans = (ans + C(a + b - 1, a)) % mod;  
```  

---

### **同类型题目推荐**  
1. **CF1111D（组合数学+动态规划）**  
2. **洛谷P1771（组合数取模+隔板法）**  
3. **洛谷P2671（前缀和+组合优化）**  

---

### **个人心得摘录**  
- **调试教训**：初始未处理逆元导致答案错误，需注意 `inv[0] = 1`。  
- **思维突破**：“将最后一位左括号固定”是避免重复计数的关键，类似动态规划的“状态唯一性”。  

---

### **可视化与算法演示**  
**动画步骤**：  
1. **遍历字符串**：从左到右扫描，遇到左括号时高亮。  
2. **显示统计值**：动态更新当前左括号的左侧计数 `a` 和右侧计数 `b`。  
3. **组合数计算**：以像素风格展示公式 `C(a+b-1, a)`，分步展开阶乘计算。  
4. **累计答案**：每次计算后，将贡献值以数字动画累加到总答案区。  

**复古风格设计**：  
- **Canvas 绘制**：括号用 8x8 像素块表示，左括号绿色，右括号黄色。  
- **音效**：选择左括号时播放“选择”音效，计算组合数时播放“计算”音效。  
- **自动演示**：按空格键启动/暂停，方向键控制单步执行。  

---

**总结**：通过组合数学优化，将问题转化为线性复杂度，结合前缀和与范德蒙德公式，是此类问题的典型解法。

---
处理用时：72.46秒