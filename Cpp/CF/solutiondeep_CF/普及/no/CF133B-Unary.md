# 题目信息

# Unary

## 题目描述

Unary is a minimalistic Brainfuck dialect in which programs are written using only one token.

Brainfuck programs use 8 commands: "+", "-", "\[", "\]", "<", ">", "." and "," (their meaning is not important for the purposes of this problem). Unary programs are created from Brainfuck programs using the following algorithm. First, replace each command with a corresponding binary code, using the following conversion table:

- ">" $ → $ 1000,
- "<" $ → $ 1001,
- "+" $ → $ 1010,
- "-" $ → $ 1011,
- "." $ → $ 1100,
- "," $ → $ 1101,
- "\[" $ → $ 1110,
- "\]" $ → $ 1111.

Next, concatenate the resulting binary codes into one binary number in the same order as in the program. Finally, write this number using unary numeral system — this is the Unary program equivalent to the original Brainfuck one.

You are given a Brainfuck program. Your task is to calculate the size of the equivalent Unary program, and print it modulo $ 1000003 $ $ (10^{6}+3) $ .

## 说明/提示

To write a number $ n $ in unary numeral system, one simply has to write 1 $ n $ times. For example, 5 written in unary system will be 11111.

In the first example replacing Brainfuck commands with binary code will give us 1101 1100. After we concatenate the codes, we'll get 11011100 in binary system, or 220 in decimal. That's exactly the number of tokens in the equivalent Unary program.

## 样例 #1

### 输入

```
,.
```

### 输出

```
220
```

## 样例 #2

### 输入

```
++++[&gt;,.&lt;-]
```

### 输出

```
61425
```

# AI分析结果



# Unary

## 题目描述

Unary 是 Brainfuck 的一种极简方言，程序仅使用一种符号编写。Brainfuck 程序使用 8 种命令：`+`, `-`, `[`, `]`, `<`, `>`, `.`, `,`。将 Brainfuck 程序转换为 Unary 的算法如下：

1. 将每个命令转换为对应的二进制码（四位长度）：
   - `>` → 1000
   - `<` → 1001  
   - `+` → 1010  
   - `-` → 1011  
   - `.` → 1100  
   - `,` → 1101  
   - `[` → 1110  
   - `]` → 1111  
2. 将所有二进制码拼接为一个大二进制数  
3. 将该二进制数转换为十进制，即为 Unary 程序的长度  

给定 Brainfuck 程序，求其 Unary 长度模 $1000003$ 的值。

## 说明/提示
样例 1 输入 `,.` 转换为二进制 `11011100`，十进制为 220。

**算法分类**  
进制

---

### 题解综合分析

各题解核心思路均基于**四位二进制转十六进制**技巧：  
1. 每个字符对应四位二进制，等价于一位十六进制  
2. 逐字符计算时，累加器先左移四位（即乘16），再加当前字符的十六进制值  
3. 全程取模避免溢出  

#### 精选题解

1. **Back_Stuff（5星）**  
   **亮点**：使用数组替代映射表，效率更优  
   ```cpp
   int k[200]; // ASCII码直接映射
   void k_init(){
       k['>']=8, k['<']=9;
       k['+']=10, k['-']=11;
       k['.']=12, k[',']=13;
       k['[']=14, k[']']=15;
   }
   int main(){
       sum_Unary = ((sum_Unary*16)%MOD + k[s[i]]) % MOD;
   }
   ```

2. **_xEr_（4星）**  
   **亮点**：通过映射表清晰展示转换逻辑  
   ```cpp
   map<char,int> a;
   a['>']=8; // 初始化映射
   ans = (ans*16 + a[c]) % mod;
   ```

3. **TRZ_2007（4星）**  
   **亮点**：位运算直观体现二进制移位  
   ```cpp
   ans = ((ans << 4) % mod + mp[ch]) % mod;
   ```

---

### 关键思路
- **进制转换优化**：四位二进制 → 一位十六进制，避免字符串拼接  
- **模运算技巧**：每一步计算即时取模，防止数值溢出  
- **数据结构选择**：数组替代映射表提升访问效率  

---

### 拓展练习
1. [P1017 进制转换](https://www.luogu.com.cn/problem/P1017)（负进制处理）  
2. [P1061 Jam的计数法](https://www.luogu.com.cn/problem/P1061)（字母进制序列）  
3. [P1553 数字反转](https://www.luogu.com.cn/problem/P1553)（多进制字符串处理）  

---

### 心得摘录
> "用数组替代map直接映射ASCII码，查询效率更高" —— Back_Stuff  
> "每个字符对应四位二进制，等价于乘16的操作，这是解题的关键" —— _xEr_

---
处理用时：72.45秒