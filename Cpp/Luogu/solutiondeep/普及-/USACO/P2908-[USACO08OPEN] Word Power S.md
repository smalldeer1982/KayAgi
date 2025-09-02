# 题目信息

# [USACO08OPEN] Word Power S

## 题目描述

Farmer John wants to evaluate the quality of the names of his N (1 <= N <= 1000) cows. Each name is a string with no more than 1000 characters, all of which are non-blank.

He has created a set of M (1 <= M <= 100) 'good' strings (no

longer than 30 characters and fully non-blank). If the sequence letters of a cow's name contains the letters of a 'good' string in the correct order as a subsequence (i.e., not necessarily all next to each other), the cow's name gets 1 quality point.

All strings is case-insensitive, i.e., capital letters and lower case letters are considered equivalent.  For example, the name 'Bessie' contains the letters of 'Be', 'sI', 'EE', and 'Es' in the correct order, but not 'is' or 'eB'. Help Farmer John determine the number of quality points in each of his cow's names.

约翰想要计算他那N(l < =N <= 1000)只奶牛的名字的能量.每只奶牛的名字由不超过1000个字 符构成，没有一个名字是空字体串.

约翰有一张“能量字符串表”，上面有M(1 < =M < =100)个代表能量的字符串.每个字符串 由不超过30个字体构成，同样不存在空字符串.一个奶牛的名字蕴含多少个能量字符串，这个名 字就有多少能量.所谓“蕴含”，是指某个能量字符串的所有字符都在名字串中按顺序出现（不 一定一个紧接着一个）.

所有的大写字母和小写字母都是等价的.比如，在贝茜的名字“Bessie”里，蕴含有“Be” “si” “EE”以及“Es”等等字符串，但不蕴含“Ls”或“eB” .请帮约翰计算他的奶牛的名字 的能量.


## 说明/提示

There are 5 cows, and their names are "Bessie", "Jonathan", "Montgomery", "Alicia", and "Angola". The 3 good strings are "se", "nGo", and "Ont".


"Bessie" contains "se", "Jonathan" contains "Ont", "Montgomery" contains both "nGo" and "Ont", Alicia contains none of the good strings, and "Angola" contains "nGo".


## 样例 #1

### 输入

```
5 3 
Bessie 
Jonathan 
Montgomery 
Alicia 
Angola 
se 
nGo 
Ont 
```

### 输出

```
1 
1 
2 
0 
1 
```

# AI分析结果



### 综合分析与结论
题目要求判断多个字符串中每个字符串包含多少给定子序列。所有题解均采用**预处理+双指针匹配**的核心思路，差异主要体现在代码实现细节与STL工具的使用。最优解法需满足时间复杂度可接受（O(N*M*L)）、代码简洁、可读性强。

---

### 精选题解分析

#### 1. 珅肐（4星）
**关键亮点**：  
- 使用`transform`函数统一转换大小写，代码简洁高效  
- 双指针实现子序列判断，逻辑清晰  
- 利用`string::npos`处理边界条件，增强鲁棒性  

**核心代码**：
```cpp
bool Check(string a, string b) {
    for(int i=0,j=0; i<a.length(); ++i) {
        if(a[i] == b[j]) ++j;
        if(j == b.length()) return true;
    }
    return false;
}
```

#### 2. B_Qu1e7（4星）
**关键亮点**：  
- 利用`string.find()`逐步定位字符位置，避免手动遍历  
- 显式处理`npos`提高代码可读性  
- 函数式封装增强代码复用性  

**核心代码**：
```cpp
int f(string nn, string ee) {
    int now = -1;
    for(int i=0; i<ee.size(); i++) {
        size_t pos = nn.find(ee[i], now+1);
        if(pos == string::npos) return 0;
        now = pos;
    }
    return 1;
}
```

#### 3. agicy（3.5星）
**关键亮点**：  
- C风格字符串处理，内存效率更高  
- 寄存器变量优化循环性能  
- 线性遍历实现子序列判断  

**不足**：C字符串操作可读性略差，未充分利用STL特性。

---

### 最优思路总结
1. **统一大小写预处理**：通过`tolower`或`transform`将所有字符转为小写，避免后续匹配时的大小写问题。  
2. **子序列高效判断**：  
   - **双指针法**：同时遍历母串和子串，匹配成功时移动子串指针。  
   - **find定位法**：通过`find(字符, 起始位置)`逐步推进，适合长母串场景。  
3. **时间复杂度优化**：O(N*M*L)在题目数据范围内可接受，无需更复杂数据结构。

---

### 拓展与同类题目
**优化思路**：若数据规模增大，可预处理母串的字符位置索引（如哈希表存储每个字符的出现位置），再用二分查找加速子序列判断。  
**推荐题目**：  
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（字符串匹配）  
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)（字符统计与格式化输出）  
3. [P3375 KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)（更高效的字符串匹配算法）  

---

### 调试心得摘录
- **珅肐**：`transform`需显式指定函数指针类型`(int(*)(int))`，否则编译器无法识别重载。  
- **B_Qu1e7**：`find`返回`size_t`类型，与`int`比较需注意符号问题，使用`string::size_type`更安全。  
- **天黑了ha**：双指针外层循环子串字符，可提前终止无效匹配，比循环母串更高效。

---
处理用时：57.33秒