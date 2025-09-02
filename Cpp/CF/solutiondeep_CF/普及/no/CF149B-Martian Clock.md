# 题目信息

# Martian Clock

## 题目描述

Having stayed home alone, Petya decided to watch forbidden films on the Net in secret. "What ungentlemanly behavior!" — you can say that, of course, but don't be too harsh on the kid. In his country films about the Martians and other extraterrestrial civilizations are forbidden. It was very unfair to Petya as he adored adventure stories that featured lasers and robots.

Today Petya is watching a shocking blockbuster about the Martians called "R2:D2". What can "R2:D2" possibly mean? It might be the Martian time represented in the Martian numeral system. Petya knows that time on Mars is counted just like on the Earth (that is, there are $ 24 $ hours and each hour has $ 60 $ minutes). The time is written as " $ a $ : $ b $ ", where the string $ a $ stands for the number of hours (from $ 0 $ to $ 23 $ inclusive), and string $ b $ stands for the number of minutes (from $ 0 $ to $ 59 $ inclusive). The only thing Petya doesn't know is in what numeral system the Martian time is written.

Your task is to print the radixes of all numeral system which can contain the time " $ a $ : $ b $ ".

## 说明/提示

Let's consider the first sample. String "11:20" can be perceived, for example, as time 4:6, represented in the ternary numeral system or as time 17:32 in hexadecimal system.

Let's consider the second sample test. String "2A:13" can't be perceived as correct time in any notation. For example, let's take the base-11 numeral notation. There the given string represents time 32:14 that isn't a correct time.

Let's consider the third sample. String "000B:00001" can be perceived as a correct time in the infinite number of numeral systems. If you need an example, you can take any numeral system with radix no less than 12.

## 样例 #1

### 输入

```
11:20
```

### 输出

```
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22```

## 样例 #2

### 输入

```
2A:13
```

### 输出

```
0
```

## 样例 #3

### 输入

```
000B:00001
```

### 输出

```
-1
```

# AI分析结果



### 中文题目重写

# 火星时钟

## 题目描述

Petya 偷偷观看被禁的关于火星的电影时，发现电影标题形如 "R2:D2"，推测可能是火星时间。火星时间与地球类似，采用24小时制（0-23时，0-59分）。给定形如 "a:b" 的时间字符串，找出所有可能的进制系统，使得该时间在此进制下合法。若不存在合法进制输出0，若有无穷多解输出-1。

## 输入输出样例

### 样例1
输入：`11:20`  
输出：`3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22`

### 样例2
输入：`2A:13`  
输出：`0`

### 样例3
输入：`000B:00001`  
输出：`-1`

---

### 算法分类
**进制转换 + 枚举**

---

### 题解分析与结论

#### 核心思路
1. **前导零处理**：去除时、分部分的前导零，保留有效数字。
2. **特判条件**：
   - 若时/分某位数值超过23/59则无解（因任何进制下该位数值必须小于进制基数）
   - 若有效部分均为单数字且合法，则存在无穷解（数值与进制无关）
3. **进制枚举**：从 `max(时最大数, 分最大数)+1` 开始，逐次增大进制，转换并验证合法性。

#### 关键难点
1. **溢出处理**：大进制转换时使用 `pow` 函数可能导致精度丢失或溢出，应改用逐位累乘。
2. **无限解判断**：需精确识别单数字有效部分的情况。
3. **边界处理**：需正确处理空字符串（如全零时保留一个零）。

---

### 精选题解

#### 题解作者：alan1118（★★★★☆）
**核心亮点**：  
- 前导零处理细致，分离时、分逻辑清晰
- 特判逻辑严密，正确处理了无穷解情况
- 自实现进制转换函数避免部分问题

**关键代码**：
```cpp
int toTen(string s, int jz) {
    int res = 0, m = 0;
    for(int i = s.size()-1; i >= 0; i--) {
        int x = isalpha(s[i]) ? s[i]-'A'+10 : s[i]-'0';
        res += x * pow(jz, m++);
    }
    return res;
}
```

#### 题解作者：PR_CYJ（★★★★☆）
**核心亮点**：  
- 使用 vector 存储有效数字，逻辑简洁
- 逐位累乘实现进制转换，避免 pow 的精度问题
- 预处理阶段计算最大数值，减少冗余判断

**关键代码**：
```cpp
for(int j=0; j<h.size(); j++) {
    a *= i; 
    a += h[j]; // 逐位累乘
}
if(a >=24 || ...) break; // 及时终止非法情况
```

#### 题解作者：liuli688（★★★★★）
**核心亮点**：
- 利用 C++17 的 `from_chars` 函数处理进制转换，避免手动实现
- 使用 `long long` 类型防止溢出
- 代码简洁高效，处理边界情况严谨

**关键代码**：
```cpp
from_chars(h, h+hlen, hv, i); // 标准库转换
from_chars(m, m+mlen, mv, i);
if(hv <24 && mv <60) ... // 验证合法性
```

---

### 举一反三
1. **进制转换类**：  
   - [P1143 进制转换](https://www.luogu.com.cn/problem/P1143)  
   - [P1066 图像模糊处理](https://www.luogu.com.cn/problem/P1066)（涉及数值范围判断）
2. **字符串处理类**：  
   - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)  
3. **边界特判类**：  
   - [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)

---

### 总结心得
- **调试教训**：多位数字转换时必须用 `long long` 防止溢出。
- **思维突破**：无限解条件需结合数值独立性和位数特性判断。
- **编码技巧**：善用标准库函数（如 `from_chars`）简化复杂转换逻辑。

---
处理用时：197.36秒