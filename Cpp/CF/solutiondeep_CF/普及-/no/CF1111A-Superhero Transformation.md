# 题目信息

# Superhero Transformation

## 题目描述

We all know that a superhero can transform to certain other superheroes. But not all Superheroes can transform to any other superhero. A superhero with name $ s $ can transform to another superhero with name $ t $ if $ s $ can be made equal to $ t $ by changing any vowel in $ s $ to any other vowel and any consonant in $ s $ to any other consonant. Multiple changes can be made.

In this problem, we consider the letters 'a', 'e', 'i', 'o' and 'u' to be vowels and all the other letters to be consonants.

Given the names of two superheroes, determine if the superhero with name $ s $ can be transformed to the Superhero with name $ t $ .

## 说明/提示

In the first sample, since both 'a' and 'u' are vowels, it is possible to convert string $ s $ to $ t $ .

In the third sample, 'k' is a consonant, whereas 'a' is a vowel, so it is not possible to convert string $ s $ to $ t $ .

## 样例 #1

### 输入

```
a
u
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
abc
ukm
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
akm
ua
```

### 输出

```
No
```

# AI分析结果



### 题目重写
# 超级英雄变身

## 题目描述  
我们知道超级英雄可以变身为其他特定超级英雄，但并非所有变身都能实现。当且仅当满足以下条件时，名字为 $s$ 的超级英雄可以变身为名字为 $t$ 的超级英雄：通过将 $s$ 中的元音字母改为任意其他元音字母，辅音字母改为任意其他辅音字母，可以使 $s$ 等于 $t$。可以执行多次修改。  

**元音字母**定义为 'a','e','i','o','u'，其余均为辅音。  
给定两个超级英雄的名字，判断能否完成变身。

## 样例解释  
样例3中 'k'（辅音）无法转换为 'a'（元音），故输出 No。

---

**算法分类**：字符串

---

### 题解分析与结论
**核心逻辑**：  
1. 长度不同直接返回 No  
2. 每个对应位置的字符类型必须一致（同为元音或同为辅音）

**关键实现技巧**：  
- 预处理元音字母表（布尔数组）提升判断效率  
- 使用异或运算快速验证类型一致性  
- 优先处理长度不同的边界情况  

---

### 精选题解
#### 1. HoshizoraZ（★★★★★）  
**亮点**：  
- 预处理元音布尔数组，O(1)时间判断字符类型  
- 巧用异或运算简化条件判断  
- 使用exit(0)提前终止程序  

**代码核心**：
```cpp
bool v[128] = {0}; // 预处理元音表
v['a'] = v['e'] = v['i'] = v['o'] = v['u'] = 1;
if(v[s[i]]^v[t[i]]) { // 异或判断类型差异
    puts("No");
    exit(0);
}
```

#### 2. Cym10x（★★★★☆）  
**亮点**：  
- 使用宏定义封装元音判断逻辑  
- 代码结构简洁清晰  

**代码核心**：
```cpp
#define judge(x) (x=='a'||x=='e'||x=='i'||x=='o'||x=='u')
if(judge(s[i])!=judge(t[i])) { // 直接宏判断
    printf("No");
    return 0;
}
```

#### 3. wuwenjiong（★★★★☆）  
**亮点**：  
- 独立判断函数提升可读性  
- 使用逻辑运算符直接比较类型  

**代码核心**：
```cpp
bool x(char s){ // 独立判断函数
    return s=='a'||s=='e'||s=='i'||s=='o'||s=='u';
}
if(x(a[i])!=x(b[i])) { // 直接比较类型
    puts("No");
    return 0;
}
```

---

### 拓展练习
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308) - 字符串模式匹配  
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598) - 字符频率统计  
3. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055) - 字符类型校验  

**同类技巧延伸**：布尔数组预处理可应用于各类字符分类问题，异或运算适用于快速验证二元状态一致性。在字符串处理题中，优先处理长度等边界条件能避免无效计算。

---
处理用时：46.35秒