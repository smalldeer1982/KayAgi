# 题目信息

# Wrong Addition

## 题目描述

Tanya is learning how to add numbers, but so far she is not doing it correctly. She is adding two numbers $ a $ and $ b $ using the following algorithm:

1. If one of the numbers is shorter than the other, Tanya adds leading zeros so that the numbers are the same length.
2. The numbers are processed from right to left (that is, from the least significant digits to the most significant).
3. In the first step, she adds the last digit of $ a $ to the last digit of $ b $ and writes their sum in the answer.
4. At each next step, she performs the same operation on each pair of digits in the same place and writes the result to the left side of the answer.

For example, the numbers $ a = 17236 $ and $ b = 3465 $ Tanya adds up as follows:

 $ $$$ \large{ \begin{array}{r} + \begin{array}{r} 17236\\ 03465\\ \end{array} \\ \hline \begin{array}{r} 1106911 \end{array} \end{array}}  $ $ </p><ul> <li> calculates the sum of  $ 6 + 5 = 11 $  and writes  $ 11 $  in the answer. </li><li> calculates the sum of  $ 3 + 6 = 9 $  and writes the result to the left side of the answer to get  $ 911 $ . </li><li> calculates the sum of  $ 2 + 4 = 6 $  and writes the result to the left side of the answer to get  $ 6911 $ . </li><li> calculates the sum of  $ 7 + 3 = 10 $ , and writes the result to the left side of the answer to get  $ 106911 $ . </li><li> calculates the sum of  $ 1 + 0 = 1 $  and writes the result to the left side of the answer and get  $ 1106911 $ . </li></ul><p>As a result, she gets  $ 1106911 $ .</p><p>You are given two positive integers  $ a $  and  $ s $ . Find the number  $ b $  such that by adding  $ a $  and  $ b $  as described above, Tanya will get  $ s $ . Or determine that no suitable  $ b$$$ exists.

## 说明/提示

The first test case is explained in the main part of the statement.

In the third test case, we cannot choose $ b $ that satisfies the problem statement.

## 样例 #1

### 输入

```
6
17236 1106911
1 5
108 112
12345 1023412
1 11
1 20```

### 输出

```
3465
4
-1
90007
10
-1```

# AI分析结果



**算法分类**: 无算法分类（模拟、字符串处理）

---

### **题解思路与解决难点**

1. **核心思路**  
   将问题转化为逐位减法，模拟Tanya加法逆过程。从右到左处理每一位，若当前位不足则借位（需前一位为1），否则直接相减。

2. **关键步骤**  
   - **对齐处理**：补前导零使a与s等长。  
   - **逐位相减**：若s[i]≥a[i]，直接相减；否则检查前一位是否为1，借位后计算。  
   - **合法性校验**：借位后结果需在0~9范围内，否则无解。  

3. **难点对比**  
   - **借位处理**：部分题解未正确处理连续借位或高位剩余数字。  
   - **结果拼接**：需反转结果并去除前导零。  

---

### **题解评分（≥4星）**

1. **StayAlone（4.5星）**  
   - **亮点**：双指针模拟，简洁处理借位与长度差异，代码可读性强。  
   - **关键代码**：  
     ```cpp
     if (s[i] >= a[j]) ans += s[i] - a[j];
     else if (前一位为1) ans += s[i]+10 -a[j];
     ```

2. **yanhao40340（4星）**  
   - **亮点**：直接重载减法运算符，逻辑清晰，代码复用性高。  
   - **关键代码**：  
     ```cpp
     if (s[i] < a[j]) {
         if (前一位非1) return -1;
         ans += (s[i]+10 - a[j]);
     }
     ```

3. **Coros_Trusds（4星）**  
   - **亮点**：显式处理剩余高位，避免遗漏，适合初学者理解。  

---

### **最优思路提炼**

1. **逆向减法**  
   将问题视为s减去a，逐位处理：  
   ```python
   b = []
   i = len(s)-1, j = len(a)-1
   while j >=0:
       if s[i] >= a[j]:
           b.append(s[i]-a[j])
           i -=1
       else:
           if i==0 or s[i-1] != '1': return -1
           b.append(10 + s[i] - a[j])
           i -=2
       j -=1
   ```

2. **边界处理**  
   - 若s长度小于a，直接无解。  
   - 处理完a后，s剩余高位需全为0或拼接为b的高位。

---

### **类似题目推荐**

1. **P1601 高精度加法（字符串模拟进位）**  
2. **P2142 高精度减法（借位处理）**  
3. **P1255 数楼梯（逐位拼接思想）**  

---

### **可视化设计**

1. **动画演示**  
   - **步进流程**：显示当前处理位（红色高亮），若借位则标记前一位为黄色。  
   - **结果构建**：右侧动态生成b的每一位，绿色表示合法，红色表示错误。  

2. **复古像素风格**  
   - **颜色方案**：8位色（红、黄、绿、黑），Canvas绘制数字网格。  
   - **音效触发**：合法操作播放“叮”，错误时播放“哔”。  

---

### **核心代码示例**

```python
def find_b(a: str, s: str) -> str:
    a = a.zfill(len(s))  # 补前导零对齐
    s = s.zfill(len(a))
    a = a[::-1]
    s = s[::-1]
    b = []
    i = 0
    while i < len(s):
        if i >= len(a):
            digit_a = 0
        else:
            digit_a = int(a[i])
        digit_s = int(s[i])
        
        if digit_s >= digit_a:
            b.append(str(digit_s - digit_a))
            i += 1
        else:
            if i+1 >= len(s) or int(s[i+1]) != 1:
                return "-1"
            combined = 10 + digit_s
            b.append(str(combined - digit_a))
            i += 2
    # 处理剩余高位
    while i < len(s):
        b.append(s[i])
        i +=1
    res = ''.join(reversed(b)).lstrip('0')
    return res if res else "-1"
```

---

**总结**：本题核心为逆向模拟借位减法，需注意位数对齐与合法性校验。通过逐位处理与借位判断，可高效求解。

---
处理用时：89.27秒