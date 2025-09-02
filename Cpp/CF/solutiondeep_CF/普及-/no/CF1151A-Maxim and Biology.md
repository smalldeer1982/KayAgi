# 题目信息

# Maxim and Biology

## 题目描述

Today in the scientific lyceum of the Kingdom of Kremland, there was a biology lesson. The topic of the lesson was the genomes. Let's call the genome the string "ACTG".

Maxim was very boring to sit in class, so the teacher came up with a task for him: on a given string $ s $ consisting of uppercase letters and length of at least $ 4 $ , you need to find the minimum number of operations that you need to apply, so that the genome appears in it as a substring. For one operation, you can replace any letter in the string $ s $ with the next or previous in the alphabet. For example, for the letter "D" the previous one will be "C", and the next — "E". In this problem, we assume that for the letter "A", the previous one will be the letter "Z", and the next one will be "B", and for the letter "Z", the previous one is the letter "Y", and the next one is the letter "A".

Help Maxim solve the problem that the teacher gave him.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

In the first example, you should replace the letter "Z" with "A" for one operation, the letter "H" — with the letter "G" for one operation. You will get the string "ACTG", in which the genome is present as a substring.

In the second example, we replace the letter "A" with "C" for two operations, the letter "D" — with the letter "A" for three operations. You will get the string "ZACTG", in which there is a genome.

## 样例 #1

### 输入

```
4
ZCTH
```

### 输出

```
2```

## 样例 #2

### 输入

```
5
ZDATG
```

### 输出

```
5```

## 样例 #3

### 输入

```
6
AFBAKC
```

### 输出

```
16```

# AI分析结果



# 中文题目翻译  
**题目名称：Maxim and Biology**  

## 题目描述  
在克雷姆兰王国的科学院中，今天的生物课主题是基因组。我们定义基因组为字符串"ACTG"。  

Maxim 觉得上课很无聊，老师给他布置了一个任务：给定一个由大写字母组成且长度至少为4的字符串 $s$，找到使其包含基因组作为子串所需的最小操作次数。每次操作可以将字符串中的任意字母替换为字母表中的前一个或后一个字母（例如，'D'的前一个是'C'，后一个是'E'）。字母'A'的前一个字母是'Z'，'Z'的后一个字母是'A'。  

## 输入输出样例  
样例1：  
输入：  
4  
ZCTH  
输出：  
2  

样例2：  
输入：  
5  
ZDATG  
输出：  
5  

样例3：  
输入：  
6  
AFBAKC  
输出：  
16  

---

**算法分类**：模拟  

---

### 题解分析与结论  
所有题解均采用**滑动窗口枚举所有长度为4的子串**，并计算转换为"ACTG"的最小操作次数。核心技巧是：  
1. **循环字母距离计算**：对字符差取绝对值`d`，最小操作次数为`min(d, 26-d)`  
2. **暴力枚举优化**：利用字符串长度≤50的特性，时间复杂度为$O(n)$  

---

### 高分题解推荐  
#### 1. [chenyuchenghsefz]（★★★★★）  
**核心思路**：  
- 遍历所有连续4字符窗口，直接计算每个字符到目标字符的循环距离  
- 代码简洁，用一行公式计算最小操作次数  
```cpp  
for (int i=0; i<n-3; i++) {
    int t = 0;
    for (int j=i; j<=i+3; j++)
        t += min(26-abs(s1[j-i]-s[j]), abs(s1[j-i]-s[j]));
    m = min(m, t);
}
```

#### 2. [xh39]（★★★★☆）  
**亮点**：  
- 封装字符距离计算函数，增强代码复用性  
- 使用`swap`统一大小顺序，简化逻辑  
```cpp  
int cha(char a, char b) {
    if (a < b) swap(a, b);
    return min(a-b, b+26-a);
}
```

#### 3. [Erusel]（★★★★☆）  
**优化点**：  
- 函数命名清晰（`calc`），直观体现计算逻辑  
- 使用`INT_MAX`初始化最小值，符合编程规范  
```cpp  
int calc(char c1, char c2) {
    return min(abs(c1-c2), 26-abs(c1-c2));
}
```

---

### 关键技巧总结  
1. **循环字母处理**：用`min(正向差, 反向差)`解决字母表循环问题  
2. **滑动窗口优化**：只需遍历前$n-3$个字符即可覆盖所有可能子串  
3. **函数封装**：将字符距离计算独立为函数提升代码可读性  

---

### 拓展与同类题目  
1. **循环字符串处理**：[P1147 连续字符和](https://www.luogu.com.cn/problem/P1147)  
2. **最小操作次数**：[CF1328C Ternary XOR](https://codeforces.com/problemset/problem/1328/C)  
3. **滑动窗口应用**：[P1638 逛画展](https://www.luogu.com.cn/problem/P1638)  

---

### 题解心得摘录  
- **调试经验**：注意字母表循环特性，例如'A'到'Z'的逆向距离为1而非25  
- **代码简化**：直接计算绝对差与26-绝对差的最小值，避免复杂条件判断  
- **常见错误**：未处理窗口越界（需确保循环终止条件为`i ≤ n-4`）

---
处理用时：48.62秒