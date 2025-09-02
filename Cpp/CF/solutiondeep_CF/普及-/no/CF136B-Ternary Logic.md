# 题目信息

# Ternary Logic

## 题目描述

Little Petya very much likes computers. Recently he has received a new "Ternatron IV" as a gift from his mother. Unlike other modern computers, "Ternatron IV" operates with ternary and not binary logic. Petya immediately wondered how the $ xor $ operation is performed on this computer (and whether there is anything like it).

It turned out that the operation does exist (however, it is called $ tor $ ) and it works like this. Suppose that we need to calculate the value of the expression $ a\ tor\ b $ . Both numbers $ a $ and $ b $ are written in the ternary notation one under the other one ( $ b $ under $ a $ ). If they have a different number of digits, then leading zeroes are added to the shorter number until the lengths are the same. Then the numbers are summed together digit by digit. The result of summing each two digits is calculated modulo 3. Note that there is no carry between digits (i. e. during this operation the digits aren't transferred). For example: $ 14_{10}\ tor\ 50_{10}=0112_{3}\ tor\ 1212_{3}=1021_{3}=34_{10} $ .

Petya wrote numbers $ a $ and $ c $ on a piece of paper. Help him find such number $ b $ , that $ a\ tor\ b=c $ . If there are several such numbers, print the smallest one.

## 样例 #1

### 输入

```
14 34
```

### 输出

```
50
```

## 样例 #2

### 输入

```
50 34
```

### 输出

```
14
```

## 样例 #3

### 输入

```
387420489 225159023
```

### 输出

```
1000000001
```

## 样例 #4

### 输入

```
5 5
```

### 输出

```
0
```

# AI分析结果



【中文重写题目】
# 三进制逻辑

## 题目描述

小Petya非常喜欢计算机。最近他收到了母亲赠送的新电脑"Ternatron IV"。与普通电脑不同，这台电脑使用三进制逻辑。Petya想了解其中的异或运算（这里称为tor运算）。

tor运算规则：将两个数写成三进制并右对齐（较短数补前导零），每位做不进位加法（即相加后模3）。例如：14₁₀ tor 50₁₀ = 0112₃ tor 1212₃ = 1021₃ = 34₁₀。

给定a和c，求满足a tor b = c的最小b。

## 样例

样例输入1：
14 34 → 输出：50  
样例输入2：
387420489 225159023 → 输出：1000000001

---

**算法分类**：进制

---

### 题解分析与结论

所有题解核心思路一致：将a、c转换为三进制，逐位计算b的最小可能值。关键公式：  
`b_i = (c_i - a_i + 3) % 3`，通过隐式补零处理位数差异，直接操作十进制数无需显式存储三进制数组。

---

### 高星题解推荐

1. **ikunTLE（5星）**  
   **亮点**：代码极度简洁（仅8行），利用循环隐式处理进制转换，通过取余和除法逐位计算。  
   **关键代码**：
   ```cpp
   while(a||c){
       b += (c%3 - a%3 +3)%3 * p;
       a /=3, c /=3, p *=3;
   }
   ```
   **思路**：每次取a、c的最低位计算b的对应位，权重p记录当前位值，自然处理位数差异。

2. **__O_v_O__（4星）**  
   **亮点**：清晰分类讨论，直接数学推导每位计算方式。  
   **心得**：指出当a位>c位时需+3借位，强调不进位特性。

3. **KyleShen1213（4星）**  
   **优化点**：使用pow函数替代累乘变量，代码更易理解，适合初学者。

---

### 关键思路

**核心技巧**：  
1. 逐位计算：利用取余运算`%3`获取当前位，除法`/3`右移处理下一位  
2. 隐式补零：循环条件`while(a||c)`自动处理不等长情况  
3. 最小化策略：`(c_i - a_i +3) %3`确保每位取最小值  

**实现要点**：  
- 权重变量p初始为1，每次乘3对应三进制位权  
- 累加结果时直接计算十进制值，避免显式转换  

---

### 拓展练习

1. **P1017**（负进制转换） - 练习特殊进制处理  
2. **P1143**（进制转换） - 常规进制转换问题  
3. **CF1328D**（Carousel） - 类似位运算构造题  

---

### 心得体会摘录

- "注意当a位数多于c时，需要继续处理高位，此时c的对应位视为0" —— 来自隐式补零实现的调试经验  
- "+3操作是为了防止负数，保证取模结果正确" —— 多位题解强调模运算处理技巧  
- "直接操作十进制数比转换三进制数组更高效" —— 代码优化心得

---
处理用时：72.61秒