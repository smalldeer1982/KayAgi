# 题目信息

# Plus and xor

## 题目描述

Bitwise exclusive OR (or bitwise addition modulo two) is a binary operation which is equivalent to applying logical exclusive OR to every pair of bits located on the same positions in binary notation of operands. In other words, a binary digit of the result is equal to 1 if and only if bits on the respective positions in the operands are different.

For example, if $ X=109_{10}=1101101_{2} $ , $ Y=41_{10}=101001_{2} $ , then:

 $ X $ xor $ Y = 68_{10} = 1000100_{2} $ . Write a program, which takes two non-negative integers $ A $ and $ B $ as an input and finds two non-negative integers $ X $ and $ Y $ , which satisfy the following conditions:

- $ A=X+Y $
- $ B = X $ xor $ Y $ , where xor is bitwise exclusive or.
- $ X $ is the smallest number among all numbers for which the first two conditions are true.

## 样例 #1

### 输入

```
142
76
```

### 输出

```
33 109
```

# AI分析结果



**【题目翻译】**
# 加法与异或

## 题目描述

按位异或（或称模二加法）是一种二元运算，其效果相当于对两个操作数的每一位分别执行逻辑异或。换句话说，结果的某一位为1当且仅当两个操作数的对应位不同。

例如，若 $ X=109_{10}=1101101_{2} $，$ Y=41_{10}=101001_{2} $，则：
$ X $ xor $ Y = 68_{10} = 1000100_{2} $。编写程序，输入两个非负整数 $ A $ 和 $ B $，找出满足以下条件的两个非负整数 $ X $ 和 $ Y $：

- $ A = X + Y $
- $ B = X $ xor $ Y $
- $ X $ 是所有满足前两个条件中最小的数

## 样例 #1

### 输入
```
142
76
```

### 输出
```
33 109
```

---

**算法分类**：位运算、数学

---

### 题解综合分析
1. **核心逻辑**：利用异或与加法的位运算性质推导公式。异或相当于不进位加法，加法与异或的差值为进位部分的2倍，即 $X+Y = (X \oplus Y) + 2 \times (X \& Y)$。
2. **关键结论**：
   - 无解条件：$A < B$ 或 $(A-B)$ 为奇数
   - 有解时 $X = (A-B)/2$，$Y = A - X$
3. **验证步骤**：部分题解强调需验证 $(X \oplus Y) == B$，防止特殊进位导致错误

---

### 优质题解推荐

#### 1. 正负君（⭐⭐⭐⭐⭐）
**亮点**：
- 通过竖式对比直观展示加法与异或的差异
- 推导出 $(A-B)/2$ 即为X的最小值
- 代码简洁且包含数据范围说明

**代码核心**：
```cpp
unsigned long long A,B,X,Y;
if(A<B || (A-B)&1) cout<<-1;
else X=(A-B)/2, Y=A-X;
```

#### 2. rui_er（⭐⭐⭐⭐）
**亮点**：
- 明确给出无解的数学条件
- 强调二进制位的构造策略
- 包含正确性验证步骤

**关键实现**：
```cpp
if((x^y) != b) cout << -1; // 最终异或验证
```

#### 3. 流绪（⭐⭐⭐⭐）
**优化点**：
- 补充特判条件的推导过程
- 指出需再次验证异或结果
- 精简的代码结构

**代码片段**：
```cpp
ll x= a-b>>1;
if((x^y) !=b) cout << -1; // 结果验证
```

---

### 关键技巧总结
1. **位运算性质**：异或对应不进位加法，进位差为 $(A-B)/2$
2. **最小化策略**：X取公共进位部分的最小二进制表示
3. **防御性编程**：验证最终异或结果，处理边界情况

---

### 拓展练习
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469) - 异或性质应用
2. [P7072 异或序列](https://www.luogu.com.cn/problem/CF242B) - 位运算构造
3. [P2114 起床困难综合症](https://www.luogu.com.cn/problem/P2114) - 位运算贪心策略

---

### 心得体会摘录
> "异或是不进位的加法，差值的奇偶性直接决定解的存在性" —— 正负君  
> "当某一位同为1时，这个位置的进位会影响最终解的构造" —— 基地A_I  
> "十年OI一场空，不开unsigned long long见祖宗" —— 多篇题解共同强调数据范围的重要性

---
处理用时：49.09秒