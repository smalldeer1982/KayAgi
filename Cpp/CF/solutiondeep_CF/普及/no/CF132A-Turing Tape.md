# 题目信息

# Turing Tape

## 题目描述

INTERCAL is the oldest of esoteric programming languages. One of its many weird features is the method of character-based output, known as Turing Tape method. It converts an array of unsigned 8-bit integers into a sequence of characters to print, using the following method.

The integers of the array are processed one by one, starting from the first. Processing $ i $ -th element of the array is done in three steps:

1\. The 8-bit binary notation of the ASCII-code of the previous printed character is reversed. When the first element of the array is processed, the result of this step is considered to be 0.

2\. The $ i $ -th element of the array is subtracted from the result of the previous step modulo 256.

3\. The binary notation of the result of the previous step is reversed again to produce ASCII-code of the $ i $ -th character to be printed.

You are given the text printed using this method. Restore the array used to produce this text.

## 说明/提示

Let's have a closer look at the beginning of the example. The first character is "H" with ASCII-code $ 72=01001000_{2} $ . Its reverse is $ 00010010_{2}=18 $ , and this number should become the result of the second step of processing. The result of the first step is considered to be 0, so the first element of the array has to be $ (0-18) $ mod $ 256=238 $ , where $ a $ mod $ b $ is the remainder of division of $ a $ by $ b $ .

## 样例 #1

### 输入

```
Hello, World!
```

### 输出

```
238
108
112
0
64
194
48
26
244
168
24
16
162
```

# AI分析结果



### 题目重写
#### 题目名称：图灵磁带

**题目描述**  
INTERCAL 是最古老的深奥编程语言之一。其众多奇葩特性之一是基于字符的输出方法，称为图灵磁带法。该方法将无符号8位整数数组转换为要打印的字符序列，具体步骤如下：

处理数组的第 $i$ 个元素时：
1. 将上一个打印字符的ASCII码的8位二进制表示反转。处理第一个元素时，此步骤结果为0。
2. 用上一步的结果减去数组中第 $i$ 个元素的值，取模256。
3. 将第二步结果的二进制再次反转，得到第 $i$ 个要打印字符的ASCII码。

给定通过此方法打印的文本，还原原始数组。

**样例输入**  
```
Hello, World!
```

**样例输出**  
```
238
108
112
0
64
194
48
26
244
168
24
16
162
```

---

### 算法分类  
模拟

---

### 题解分析与结论  
**核心思路对比**  
所有题解均采用模拟流程，核心差异在于二进制反转的实现方式：  
1. **数学位操作法**（高效）：通过逐位取模和乘系数直接计算反转值，无需显式二进制转换。  
2. **字符串转换法**（低效）：将数值转为二进制字符串，反转后补零再转换回数值。  

**关键技巧**  
- **二进制快速反转**：对8位数值，从最低位开始逐位取出，乘以系数（128→64→32→...→1）累计结果。  
- **负数处理**：通过 `(last - x + 256) % 256` 确保结果非负。  
- **输入处理**：使用 `getline` 读取含空格的输入。  

**最优题解推荐**  

1. **作者：bj12z_donglinxi（5星）**  
   **亮点**  
   - 高效位运算实现二进制反转。  
   - 变量命名清晰，代码简洁。  
   **核心代码**  
   ```cpp
   for (int i = 0 ; i < s.size() ; i++) {
       x = 0;
       first = s[i];
       temp = 128;
       for (int j = 1 ; j <= 8 ; j++) {
           x += first % 2 * temp; // 取最低位并乘当前系数
           temp /= 2;
           first /= 2;
       }
       printf("%d\n", (last - x + 256) % 256);
       last = x;
   }
   ```

2. **作者：小恐（5星）**  
   **亮点**  
   - 代码极简，逻辑直白。  
   - 注释明确，调试友好。  
   **核心代码**  
   ```cpp
   for(int i=0;a[i]!='\0'&&a[i]!='\n';++i) {
       int t=128, x=a[i], y=0;
       for(int j=1;j<=8;++j) {
           y += x%2 * t; // 位操作累计反转值
           t /= 2;
           x /= 2;
       }
       printf("%d\n",(last-y+256)%256);
       last = y;
   }
   ```

3. **作者：_Wind_Leaves_ShaDow_（4星）**  
   **亮点**  
   - 详细解释二进制反转数学原理。  
   - 强调输入处理中的空格问题。  
   **代码片段**  
   ```cpp
   for(int i=0;i<s.size();i++){
       t=int(s[i]);
       x=0;
       tmp=128;
       for(int j=1;j<=8;j++) {
           x += t%2 * tmp; // 同上位操作
           tmp /= 2;
           t /= 2;
       }
       cout<<(last-x+256)%256<<endl;
       last=x;
   }
   ```

---

### 关键思路总结  
1. **二进制反转技巧**：通过逐位取模和系数累加，避免字符串操作。  
2. **循环不变式**：`last` 维护上一个字符的反转值，初始为0。  
3. **负数处理公式**：`(a - b + MOD) % MOD` 确保结果在 `[0, MOD-1]` 范围内。  

---

### 拓展与心得  
**个人心得摘录**  
- "反转压根不用快速幂，循环足够" → 避免过度设计。  
- "提交被卡因未重置x" → 重视变量初始化。  

**同类题目推荐**  
1. [P1017 进制转换](https://www.luogu.com.cn/problem/P1017)（负进制处理）  
2. [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)（位操作模拟）  
3. [P1143 进制转换](https://www.luogu.com.cn/problem/P1143)（通用进制转换实现）

---
处理用时：104.70秒