# 题目信息

# Hard Work

## 题目描述

After the contest in comparing numbers, Shapur's teacher found out that he is a real genius and that no one could possibly do the calculations faster than him even using a super computer!

Some days before the contest, the teacher took a very simple-looking exam and all his $ n $ students took part in the exam. The teacher gave them $ 3 $ strings and asked them to concatenate them. Concatenating strings means to put them in some arbitrary order one after the other. For example from concatenating Alireza and Amir we can get to AlirezaAmir or AmirAlireza depending on the order of concatenation.

Unfortunately enough, the teacher forgot to ask students to concatenate their strings in a pre-defined order so each student did it the way he/she liked.

Now the teacher knows that Shapur is such a fast-calculating genius boy and asks him to correct the students' papers.

Shapur is not good at doing such a time-taking task. He rather likes to finish up with it as soon as possible and take his time to solve 3-SAT in polynomial time. Moreover, the teacher has given some advice that Shapur has to follow. Here's what the teacher said:

- As I expect you know, the strings I gave to my students (including you) contained only lowercase and uppercase Persian Mikhi-Script letters. These letters are too much like Latin letters, so to make your task much harder I converted all the initial strings and all of the students' answers to Latin.
- As latin alphabet has much less characters than Mikhi-Script, I added three odd-looking characters to the answers, these include "-", ";" and "\_". These characters are my own invention of course! And I call them Signs.
- The length of all initial strings was less than or equal to $ 100 $ and the lengths of my students' answers are less than or equal to $ 600 $
- My son, not all students are genius as you are. It is quite possible that they make minor mistakes changing case of some characters. For example they may write ALiReZaAmIR instead of AlirezaAmir. Don't be picky and ignore these mistakes.
- Those signs which I previously talked to you about are not important. You can ignore them, since many students are in the mood for adding extra signs or forgetting about a sign. So something like Iran;;-- is the same as --;IRAN
- You should indicate for any of my students if his answer was right or wrong. Do this by writing "WA" for Wrong answer or "ACC" for a correct answer.
- I should remind you that none of the strings (initial strings or answers) are empty.
- Finally, do these as soon as possible. You have less than $ 2 $ hours to complete this.

## 样例 #1

### 输入

```
Iran_
Persian;
W_o;n;d;e;r;f;u;l;
7
WonderfulPersianIran
wonderful_PersIAN_IRAN;;_
WONDERFUL___IRAN__PERSIAN__;;
Ira__Persiann__Wonderful
Wonder;;fulPersian___;I;r;a;n;
__________IranPersianWonderful__________
PersianIran_is_Wonderful
```

### 输出

```
ACC
ACC
ACC
WA
ACC
ACC
WA
```

## 样例 #2

### 输入

```
Shapur;;
is___
a_genius
3
Shapur__a_is___geniUs
is___shapur___a__Genius;
Shapur;;is;;a;;geni;;us;;
```

### 输出

```
WA
ACC
ACC
```

# AI分析结果



### 中文重写题目
题目已为中文，无需重复翻译。

### 算法分类
**字符串**

---

### 题解综合分析
**核心逻辑**：预处理原始字符串与测试字符串（去除非字母字符并统一为小写），枚举三个原始字符串的 6 种排列组合，判断测试字符串是否匹配任一组合。  
**关键难点**：  
1. 正确处理非字母字符的过滤与大小写转换  
2. 高效验证所有可能的拼接顺序  

---

### 高星题解推荐
#### 1. 作者：yggdyy_（⭐⭐⭐⭐⭐）
**亮点**：  
- 使用函数封装字符串预处理逻辑，代码复用性高  
- 通过排列组合直接枚举所有可能，思路清晰  
- 函数优化后的代码简洁易懂  

**核心代码**：  
```cpp
void strcls(string &S) {
    string T;
    for (char c : S) {
        if (isalpha(c)) T += tolower(c);
    }
    S = T;
}

// 预处理并枚举排列组合
strcls(a); strcls(b); strcls(c);
bool valid = st == a+b+c || st == a+c+b || ...（共6种情况）;
```

#### 2. 作者：StarryWander（⭐⭐⭐⭐）
**亮点**：  
- 代码简洁，直接使用字符串操作函数  
- 统一转换为小写的逻辑清晰  
- 利用 `||` 快速判断 6 种情况  

**核心代码**：  
```cpp
string cl(string s) {
    string k;
    for (char c : s) {
        if (isalpha(c)) k += tolower(c);
    }
    return k;
}
// 预处理后直接比较
if (s == a+b+c || ...) cout << "ACC";
```

#### 3. 作者：黄文烽（⭐⭐⭐⭐）
**亮点**：  
- 使用 `toupper` 统一处理大小写  
- 函数式编程风格，逻辑紧凑  
- 完整处理所有边界条件  

**个人心得**：  
> "解决字符串问题的万能钥匙——分割(split)" —— 通过预处理明确核心字符，简化后续比较。

---

### 最优思路总结
1. **预处理**：去除非字母字符并统一大小写，生成原始字符串的纯净版本。  
2. **排列组合**：直接枚举所有 6 种拼接顺序，避免复杂匹配算法。  
3. **快速比较**：预处理后的字符串直接进行等值判断，时间复杂度为 O(1)。  

**优化点**：  
- 显式检查处理后字符串长度是否等于三个原始字符串长度之和，可提前排除无效情况。  

---

### 拓展与相似题
**同类题型**：  
1. 字符串匹配（如判断子序列、编辑距离）  
2. 排列组合验证（如密码破解、模式生成）  

**推荐题目**：  
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)  
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)  
3. [P3375 KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)

---
处理用时：97.66秒